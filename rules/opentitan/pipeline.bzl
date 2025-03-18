# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

load(
    "@lowrisc_opentitan//rules/opentitan:transform.bzl",
    "obj_disassemble",
    "obj_transform",
)
load("@lowrisc_opentitan//rules:signing.bzl", "sign_binary")
load("@rules_cc//cc:find_cc_toolchain.bzl", "find_cc_toolchain")
load("//rules/opentitan:toolchain.bzl", "LOCALTOOLS_TOOLCHAIN")

OpenTitanPipelineInfo = provider(
    doc = "provider to export attributes of a building pipeline",
    fields = {
        "apply": """function which applies the pipeline.
            It's prototype is:
            ```py
            def apply_fn(pl_ctx)
            ```
            where `pl_ctx` is the execution context of the pipeline created by
            `create_pl_ctx`.
            The return value must be the same as for any rule: a list of providers.
            """,
    },
)

def get_default_file(msg, target):
    """
    Return the File in the DefaultInfo of Target. Error out if there more than
    one files.
    """
    files = target[DefaultInfo].files.to_list()
    if len(files) != 1:
        fail("{}: expected exactly one file".format(msg))
    return files[0]

def create_pl_ctx(ctx, vars):
    """
    Create a pipeline execution context:

    Args:
    - ctx: the rule context
    - vars: dictionary of variables
    """
    return struct(
        ctx = ctx,
        vars = vars,
    )

def remember_data_labels(data):
    """
    Given an array of label strings, return a dictionary where the
    keys are Label that maps to the corresponding label strings. This function
    is useful because when passing a label string to a label attribute, bazel
    will automatically resolved aliases and therefore the Target's label field
    will be that of resolved alias and not the original label. For example,
    ```py
    somerule(name = "mytarget")
    alias(name = "myalias", actual = "mytarget")
    # Pass to a data attribute:
    otherrule(name = "test", data = [":myalias"])
    # Inside the implementation of otherrule, ctx.attrs.data.label[0] will be
    # Label("/path/to/mytarget") and not Label("/path/to/myalias").
    ```
    This can be problematic if the rule wants to remember the original label, for
    example to perform expansion. This macro can be used to convert an array of label
    to a dictionary that remembers the original label. It should be used in a macro
    that wraps the actual rule. E.g.
    ```py
    # Rename rule to _otherrule, and define
    def otherrule(name, data):
        _otherrule(name = name, data = _remember_data_labels(data))
    ```
    where `data` is now a string_keyed_label_dict.
    """
    return {str(Label(label)): label for label in data}

def expand_locations_and_targets(ctx, string, targets):
    """
    Expand locations and targets. More precisely:
    - If a string contains `$(location <label>)` or `$(locations <label>)`, it will
      be expanded per https://bazel.build/rules/lib/builtins/ctx#expand_location
    - If a variable content is *exactly* of the form `$(target <label>)`, the
      correspond variable in the pipeline will be the Target of the associated label.
      This label string must be present as a key in the `targets` attribute.

    Args:
    - ctx: context (used for location expansion).
    - string: the string to expand.
    - targets: dictionary (label strings -> Target) used for target expansion,
               usually created by `remember_data_labels`.
    """
    if string.startswith("$(target ") and string.endswith(")"):
        string = string.removeprefix("$(target ").removesuffix(")").strip()
        res = targets.get(str(Label(string)), None)
        if res == None:
            fail("unknown target {}, make sure that it is listed in the data dependencies of the rule".format(string))
        return res
    return ctx.expand_location(string, targets.values())

def expand_vars(ctx, vars, targets):
    """
    Perform expansion (using `expand_locations_and_targets`) on every value of the key-value
    dictionary `vars`. The other arguments are passed as-in to `expand_locations_and_targets`.
    """
    def expand(val):
        if type(val) == "array":
            return [expand_locations_and_targets(ctx, x, targets) for x in val]
        else:
            return expand_locations_and_targets(ctx, val, targets)
    return {key: expand(value) for (key, value) in vars.items()}

def merge_attrs(orig, override, strategies):
    res = {}
    for (attr, strategy) in strategies.items():
        if strategy == "add":
            res[attr] = orig.get(attr, []) + override.get(attr, [])
        elif strategy == "replace":
            res[attr] = override.get(attr, None) or orig.get(attr, None)
        else:
            fail("unknown merging strategy {} for attribute {}".format(strategy, attr))
    return res

CC_BINARY_ATTRS = {
    "srcs": attr.label_list(
        allow_files = True,
        doc = "List of sources that will be added the compilation pipeline",
    ),
    "hdrs": attr.label_list(
        allow_files = True,
        doc = "List of headers that will be added the compilation pipeline",
    ),
    "deps": attr.label_list(
        doc = "List of dependencies that will be added the compilation pipeline",
    ),
    "copts": attr.string_list(
        doc = "List of compilation options that will be added to the compilation pipeline",
    ),
    "defines": attr.string_list(
        doc = "List of defines that will be added to the compilation pipeline",
    ),
    "linker_script": attr.label(
        providers = [CcInfo],
        doc = "Default linker script for linking this binary",
    ),
    "linkopts": attr.string_list(
        doc = "Linker flags for linking this binary.",
    ),
    # We also care of `features` but this is an implicit attribute of every bazel
    # rule already.
}

CC_BINARY_MERGE = {
    "srcs": "add",
    "hdrs": "add",
    "deps": "add",
    "copts": "add",
    "defines": "add",
    "linker_script": "replace",
    "linkopts": "add",
    "features": "add",
}

def cc_binary_attrs_to_vars(ctx):
    """
    For a rule accepting all attributes listed in `CC_BINARY_ATTRS`,
    convert those attributes to variables understood by `pl_cc_binary`.
    Those variables can be added to the pipeline context.
    """
    return {
        key: getattr(ctx.attr, key)
        for key in CC_BINARY_ATTRS.keys() + ["features"]
    }

def merge_cc_binary_attrs(orig, override):
    return merge_attrs(orig, override, CC_BINARY_MERGE)

OpenTitanRawBinary = provider(
    doc = "Result of the pl_cc_binary pipeline",
    fields = {
        "binary": "raw binary",
        "elf": "ELF file",
        "disassembly": "disassembled ELF file",
        "mapfile": "output map from the linker",
    }
)

def _pl_cc_binary_run(pl_ctx, attrs):
    # NOTE: the cc_toolchain will execute in the context of the rule executing the pipeline.
    # Unfortunately there seems to be no way to make it work by remembering the context
    # of pl_cc_binary because it bazel will complain that it tries to access fields outside
    # of the rule's implementation. This means that every pipeline runner need to depend
    # on the CC toolchain.
    ctx = pl_ctx.ctx
    cc_attrs = merge_cc_binary_attrs(attrs, pl_ctx.vars)

    cc_toolchain = find_cc_toolchain(ctx)
    features = [f for f in cc_attrs["features"] if not f.startswith("-")]
    disabled_features = [f.removeprefix("-") for f in cc_attrs["features"] if f.startswith("-")]
    features = cc_common.configure_features(
        ctx = ctx,
        cc_toolchain = cc_toolchain,
        requested_features = features,
        unsupported_features = disabled_features,
    )

    compilation_contexts = [
        dep[CcInfo].compilation_context
        for dep in cc_attrs["deps"]
    ]
    linker_script = cc_attrs["linker_script"]
    if linker_script:
        compilation_contexts.append(linker_script[CcInfo].compilation_context)

    name = ctx.attr.name
    all_srcs = [f for src in cc_attrs["srcs"] for f in src[DefaultInfo].files.to_list()]

    # cc_common.compile crashes if a header file is passed to srcs, so filter
    # those out and passed them as private headers instead.
    hdrs = [s for s in all_srcs if s.extension == "h"]
    srcs = [s for s in all_srcs if s.extension != "h"]
    cctx, cout = cc_common.compile(
        name = name,
        actions = ctx.actions,
        feature_configuration = features,
        cc_toolchain = cc_toolchain,
        compilation_contexts = compilation_contexts,
        srcs = srcs,
        private_hdrs = hdrs,
        user_compile_flags = ["-ffreestanding"] + cc_attrs["copts"],
        defines = [ctx.expand_location(define) for define in cc_attrs["defines"]],
    )

    linking_contexts = [
        dep[CcInfo].linking_context
        for dep in cc_attrs["deps"]
    ]
    if linker_script:
        linking_contexts.append(linker_script[CcInfo].linking_context)
    mapfile = "{}.map".format(name)
    mapfile = ctx.actions.declare_file(mapfile)
    linkopts = [
        "-Wl,-Map={}".format(mapfile.path),
        "-nostdlib",
    ] + [ctx.expand_location(define) for define in cc_attrs["linkopts"]]

    lout = cc_common.link(
        name = name + ".elf",
        actions = ctx.actions,
        feature_configuration = features,
        cc_toolchain = cc_toolchain,
        compilation_outputs = cout,
        linking_contexts = linking_contexts,
        user_link_flags = linkopts,
        additional_outputs = [mapfile],
    )
    elf = lout.executable
    binary = obj_transform(
        ctx,
        name = name,
        suffix = "bin",
        format = "binary",
        src = elf,
    )
    disassembly = obj_disassemble(
        ctx,
        name = name,
        src = elf,
    )

    return {
        "DefaultInfo": DefaultInfo(
            files = depset([binary, disassembly, elf, mapfile]),
        ),
        "OpenTitanRawBinary": OpenTitanRawBinary(
            binary = binary,
            elf = elf,
            disassembly = disassembly,
            mapfile = mapfile,
        )
    }

def _pl_cc_binary_impl(ctx):
    cc_attrs = cc_binary_attrs_to_vars(ctx)
    return [OpenTitanPipelineInfo(apply = lambda pl_ctx: _pl_cc_binary_run(pl_ctx, cc_attrs))]

pl_cc_binary = rule(
    implementation = _pl_cc_binary_impl,
    attrs = CC_BINARY_ATTRS,
    doc = """Pipeline step to create a binary from C/C++ sources.

    This pipeline step behaves like `cc_binary` except that in addition to its regular
    `srcs, `hdrs`, ... attributes, those attributes can be *extended* by passing variables
    in the pipeline context. The following variables will be processed and removed from
    the pipline:
    - `srcs`, `hdrs`, `deps`, `features`, `defines`, `linkopts`: extends the similarly named attribute.
    - `linker_script`: if provided, overrides the similarly named attribute.

    All unhandled variables will be ignored.

    TODO explain more
    """,
    provides = [OpenTitanPipelineInfo],
)

SIGN_BINARY_ATTRS = {
    "ecdsa_key": attr.label_keyed_string_dict(
        allow_files = True,
        doc = "ECDSA key to sign images",
    ),
    "rsa_key": attr.label_keyed_string_dict(
        allow_files = True,
        doc = "RSA key to sign images",
    ),
    "spx_key": attr.label_keyed_string_dict(
        allow_files = True,
        doc = "SPX key to sign images",
    ),
    "manifest": attr.label(
        allow_single_file = True,
        doc = "Manifest used when signing images",
    ),
}

SIGN_BINARY_MERGE = {
    "ecdsa_key": "replace",
    "rsa_key": "replace",
    "spx_key": "replace",
    "manifest": "replace",
}

def sign_binary_attrs_to_vars(ctx):
    """
    For a rule accepting all attributes listed in `SIGN_BINARY_ATTRS`,
    convert those attributes to variables understood by `pl_sign_binary`.
    Those variables can be added to the pipeline context.
    """
    return {
        key: getattr(ctx.attr, key, None)
        for key in SIGN_BINARY_ATTRS.keys()
    }

def merge_sign_binary_attrs(orig, override):
    return merge_attrs(orig, override, SIGN_BINARY_MERGE)

def _pl_sign_binary_run(pl_ctx, attrs, binary, tc):
    sign_attrs = merge_sign_binary_attrs(attrs, pl_ctx.vars)
    if OpenTitanPipelineInfo in binary:
        binary = binary[OpenTitanPipelineInfo].apply(pl_ctx)
        if "OpenTitanRawBinary" in binary:
            binary = binary["OpenTitanRawBinary"].binary
        else:
            # Could accept an arbitrary file here as well
            fail("expected a RawBinary")
    else:
        # Could accept an arbitrary file here as well
        fail("expected a pipeline")

    print(sign_attrs)
    signed = sign_binary(
        pl_ctx.ctx,
        opentitantool = tc.tools.opentitantool,
        bin = binary,
        ecdsa_key = sign_attrs["ecdsa_key"],
        rsa_key = sign_attrs["rsa_key"],
        spx_key = sign_attrs["spx_key"],
        manifest = get_default_file("manifest", sign_attrs["manifest"]),
    )
    return {
        "DefaultInfo": DefaultInfo(
            files = depset([signed.get("signed")]),
        )
    }

def _pl_sign_binary_impl(ctx):
    tc = ctx.toolchains[LOCALTOOLS_TOOLCHAIN]
    sign_attrs = sign_binary_attrs_to_vars(ctx)
    binary = ctx.attr.binary
    return [OpenTitanPipelineInfo(apply = lambda pl_ctx: _pl_sign_binary_run(pl_ctx, sign_attrs, binary, tc))]

pl_sign_binary = rule(
    implementation = _pl_sign_binary_impl,
    attrs = {
        "binary": attr.label(
            mandatory = True,
            doc = """Binary to sign. Can either be a raw file, an OpenTitanRawBinary, or
                    a pipeline returning of those.""",
        ),
    } | SIGN_BINARY_ATTRS,
    doc = """Pipeline step sign a binary using a manifest.
    """,
    toolchains = [LOCALTOOLS_TOOLCHAIN],
)

def _opentitan_new_binary_rule_impl(ctx):
    cc_binary_vars = cc_binary_attrs_to_vars(ctx)
    pl_ctx = create_pl_ctx(ctx, cc_binary_vars)
    return ctx.attr.pipeline[OpenTitanPipelineInfo].apply(pl_ctx).values()

opentitan_new_binary_rule = rule(
    implementation = _opentitan_new_binary_rule_impl,
    attrs = {
        "pipeline": attr.label(
            mandatory = True,
            doc = "Label of a pipeline",
            providers = [OpenTitanPipelineInfo],
        ),
        "data": attr.string_keyed_label_dict(
            doc = "Files needed at runtime. This is map from labels string to labels."
        ),
    } | CC_BINARY_ATTRS,
    # See _pl_cc_binary_run
    fragments = ["cpp"],
    toolchains = ["@rules_cc//cc:toolchain_type"],
)

def opentitan_new_binary(name, **kwargs):
    data = kwargs.pop("data", [])
    opentitan_new_binary_rule(name = name, data = remember_data_labels(data), **kwargs)

# For debugging. Could also be used for variable injection.
# def _pl_run_impl(ctx):
#     vars = {
#         key: json.decode(value)
#         for (key, value) in ctx.attr.vars
#     }
#     pl_ctx = create_pl_ctx(ctx, expand_vars(ctx, ctx.attr.vars, ctx.attr.data))
#     return maybe_apply_pipeline(pl_ctx, ctx.attr.pipeline)
#
# pl_run_rule = rule(
#     implementation = _pl_run_impl,
#     attrs = {
#         "pipeline": attr.label(
#             mandatory = True,
#             doc = "Label of a pipeline",
#             providers = [OpenTitanPipelineInfo],
#         ),
#         "vars": attr.string_dict(
#             doc = "Dictionary of variables. The values are JSON-encoded structures, whose content will expanded."
#         ),
#         "data": attr.string_keyed_label_dict(
#             doc = "Files needed at runtime. This is map from labels string to labels."
#         ),
#     },
#     doc = """Run a pipeline and provides the result. Optionally set
#     the variables of the pipeline context.
#
#     The variables are subject to expansion location. More precisely:
#     - If a string contains `$(location <label>)` or `$(locations <label>)`, it will
#       be expanded per https://bazel.build/rules/lib/builtins/ctx#expand_location
#     - If a variable content is *exactly* of the form `$(target <label>)`, the
#       correspond variable in the pipeline will be the Target of the associated label.
#       This label string must be present as a key in the `data` attribute of this rule.
#
#     You should use the `pl_run` macro instead of this rule directly.
#     """,
# )
#
# def pl_run(name, **kwargs):
#     """
#     See pl_run_rule() for documentation. The only difference is that `data` is an
#     array of label strings.
#     """
#     data = kwargs.pop("data", [])
#     vars = kwargs.pop("vars", {})
#     pl_run_rule(
#         name = name,
#         data = remember_data_labels(data),
#         vars = json.encode(vars),
#         **kwargs
#     )

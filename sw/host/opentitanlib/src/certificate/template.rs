// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

use anyhow::{bail, Result};
use serde::Deserialize;

use std::collections::HashMap;

/// A certificate template variable
#[derive(Clone, Debug)]
pub enum Variable {
    /// A string variable, with a maximum length.
    // FIXME specify encoding
    String {
        /// Maximum length in *bytes*.
        length: usize,
    },
    /// A byte array of fixed length.
    ByteArray {
        /// Length in bytes.
        length: usize,
    },
    /// A (signed) integer of fixed size.
    Integer {
        /// Maximum length in *bytes*.
        max_length: usize,
    }
}

/// A certificate template variable
#[derive(Clone, Debug)]
pub enum ConstantOrVar {
    /// A constant string
    /// FIXME clarify encodings, do we always assume UTF-8?
    String(String),
    /// A constant byte array.
    ByteArray(Vec<u8>),
    /// A constant integer.
    /// FIXME probably replace this by a big_num from some crate.
    Integer(u64),
    /// A variable.
    Variable(String),
}

#[derive(Clone, Debug)]
pub enum Algorithm {
    EcdsaWithSha256,
}

#[derive(Clone, Debug)]
pub enum PubKey {
    Ecdsa {
        // FIXME here we need algorithm parameters
        value: ConstantOrVar,
    }
}

#[derive(Clone, Debug)]
pub enum NameType {
    Country,
    CommonName,
    Organization,
    OrganizationUnit,
    Locality,
    State,
    SerialNumber,
}

#[derive(Clone, Debug)]
pub struct Name {
    values: HashMap<NameType, ConstantOrVar>,
}

#[derive(Clone, Debug)]
pub struct Certificate {
    serial_number: ConstantOrVar,
    signature_algorithm: Algorithm,
    issuer: Name,
    subject: Name,
    pub_key: PubKey,
}

/// A fully parsed HJSON certificate template.
///
/// TODO document the hjson
#[derive(Clone, Debug)]
pub struct Template {
    /// Map from variables names to variables information.
    variables: HashMap<String, Variable>,
    /// Certificate.
    certificate: Certificate,
}

impl Template {
    pub fn give_mem_template(s: &str) -> Result<Self> {
        // let template: Hjson = deser_hjson::from_str(&s)?;
        let variables: HashMap<String, Variable> = HashMap::new();
        let certificate = Certificate {
            serial_number: ConstantOrVar::String("".into()),
            signature_algorithm: Algorithm::EcdsaWithSha256,
            issuer: Name { values: HashMap::new() },
            subject: Name { values: HashMap::new() },
            pub_key: PubKey::Ecdsa { value: ConstantOrVar::String("".into())},
        };

        Ok(Template {
            variables,
            certificate,
        })
    }
}

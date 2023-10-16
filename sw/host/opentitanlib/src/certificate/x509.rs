// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

use anyhow::{bail, Result};
use openssl::bn::BigNum;
use openssl::asn1::{Asn1Integer, Asn1Time};
use openssl::x509::{X509, X509NameBuilder};
use openssl::x509::extension;
use openssl::pkey::{PKey, PKeyRef};
use openssl::hash::MessageDigest;
use openssl::ec::{EcKey, EcGroup};
use openssl::pkey::{Public, Private};
use openssl::nid::Nid;
use openssl::rsa::Rsa;

struct Algorithm {
    key_pair: PKey<Private>,
    hash: MessageDigest,
}

impl Algorithm {
    // Generate new ecdsa private/pub key pair
    fn new_ecdsa_with_hash(hash: MessageDigest) -> Result<Algorithm> {
        let nid = Nid::X9_62_PRIME256V1; // NIST P-256 curve
        let group = EcGroup::from_curve_name(nid)?;
        let key = EcKey::<Private>::generate(&group)?;
        let key_pair = PKey::try_from(key)?;
        Ok(Algorithm {
            key_pair,
            hash
        })
    }
}

fn get_algorithm(name: &str) -> Result<Algorithm> {
    match name {
        "ecdsa" => Ok(Algorithm::new_ecdsa_with_hash(MessageDigest::null())?),
        "ecdsa-with-sha256" => Ok(Algorithm::new_ecdsa_with_hash(MessageDigest::sha256())?),
        _ => bail!("unknown algorithm {}", name),
    }
}

pub fn generate() -> Result<X509> {
    let mut builder = X509::builder()?;

    let not_before = Asn1Time::from_str("20230101000000Z")?;
    builder.set_not_before(&not_before)?;
    let not_after = Asn1Time::from_str("99991231235959Z")?;
    builder.set_not_after(&not_after)?;

    builder.set_version(3)?;

    let serial_number = BigNum::from_u32(42)?;
    let serial_number_asn1 = Asn1Integer::from_bn(&serial_number)?;
    builder.set_serial_number(&serial_number_asn1)?;

    let mut issuer_name_builder = X509NameBuilder::new()?;
    issuer_name_builder.append_entry_by_text("CN", "LowRISC C.I.C")?;
    let issuer_name = issuer_name_builder.build();
    builder.set_issuer_name(&issuer_name)?;

    let mut subject_builder = X509NameBuilder::new()?;
    subject_builder.append_entry_by_text("serialNumber", "39087589393759")?;
    let subject = subject_builder.build();
    builder.set_subject_name(&subject)?;

    // Standard extensions.
    builder.append_extension(extension::BasicConstraints::new().critical().ca().build()?)?;

    builder.append_extension(
        extension::KeyUsage::new()
            .critical()
            .key_cert_sign()
            .build()?
    )?;

    // let auth_key_id = extension::AuthorityKeyIdentifier::new()
    //     .build(&builder.x509v3_context(None, None))?;
    // builder.append_extension(auth_key_id)?;

    // FIXME: the rust openssl binding does not allow to choose the subject key ID
    // and always defaults to the "hash" method of the standard. We will need to use
    // raw ASN1 here?
    let subj_key_id = extension::SubjectKeyIdentifier::new()
        .build(&builder.x509v3_context(None, None))?;
    builder.append_extension(subj_key_id)?;

    // Random public key.
    let algo = get_algorithm("ecdsa-with-sha256")?;
    builder.set_pubkey(&algo.key_pair)?;

    // Sign the Certificate
    let algo = get_algorithm("ecdsa-with-sha256")?;
    builder.sign(&algo.key_pair, algo.hash)?;

    Ok(builder.build())
}

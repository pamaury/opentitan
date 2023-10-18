// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

use anyhow::{bail, Result};
use openssl::bn::BigNum;
use openssl::asn1::{Asn1Integer, Asn1Time, Asn1Object, Asn1OctetString};
use openssl::x509::{X509, X509NameBuilder, X509Extension};
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



fn subject_key_id_extension(keyid: &[u8]) -> Result<X509Extension> {
    // From https://datatracker.ietf.org/doc/html/rfc5280#section-4.2.1
    // id-ce   OBJECT IDENTIFIER ::=  { joint-iso-ccitt(2) ds(5) 29 }
    //
    // From https://datatracker.ietf.org/doc/html/rfc5280#section-4.2.1.2
    // id-ce-subjectKeyIdentifier OBJECT IDENTIFIER ::=  { id-ce 14 }
    // SubjectKeyIdentifier ::= KeyIdentifier
    //
    // From https://datatracker.ietf.org/doc/html/rfc5280#section-4.2.1.1
    // KeyIdentifier ::= OCTET STRING
    let der = asn1::write(|w| {
        w.write_element(&keyid)
    })?;
    let octet_string = Asn1OctetString::new_from_bytes(&der)?;
    // Unfortunately, the rust binding does not seem to allow creating a Asn1Object
    // from a Nid so we have to manually create it from the OID string.
    let oid = Asn1Object::from_str("2.5.29.14")?;
    Ok(X509Extension::new_from_der(&oid, false, &octet_string)?)
}

// FIXME does not support any other fields of authorityKeyIdentifier for now
fn auth_key_id_extension(keyid: &[u8]) -> Result<X509Extension> {
    // From https://datatracker.ietf.org/doc/html/rfc5280#section-4.2.1
    // id-ce   OBJECT IDENTIFIER ::=  { joint-iso-ccitt(2) ds(5) 29 }
    //
    // From https://datatracker.ietf.org/doc/html/rfc5280#section-4.2.1.1
    // id-ce-authorityKeyIdentifier OBJECT IDENTIFIER ::=  { id-ce 35 }
    //
    // AuthorityKeyIdentifier ::= SEQUENCE {
    // keyIdentifier             [0] KeyIdentifier           OPTIONAL,
    // authorityCertIssuer       [1] GeneralNames            OPTIONAL,
    // authorityCertSerialNumber [2] CertificateSerialNumber OPTIONAL  }
    //
    // KeyIdentifier ::= OCTET STRING
    //
    // Note: this is part of the implicit tagged modules:
    // https://datatracker.ietf.org/doc/html/rfc5280#appendix-A.2
    #[derive(asn1::Asn1Write)]
    struct AuthorityKeyIdentifier<'a> {
        #[implicit(0)]
        keyid: Option<&'a [u8]>,
        // FIXME add more fields here if necessary
    }

    let der = asn1::write_single(&AuthorityKeyIdentifier { keyid: Some(keyid) })?;
    let octet_string = Asn1OctetString::new_from_bytes(&der)?;
    // Unfortunately, the rust binding does not seem to allow creating a Asn1Object
    // from a Nid so we have to manually create it from the OID string.
    let oid = Asn1Object::from_str("2.5.29.35")?;
    Ok(X509Extension::new_from_der(&oid, false, &octet_string)?)
}

// From DICE specification:
// https://trustedcomputinggroup.org/wp-content/uploads/DICE-Attestation-Architecture-r23-final.pdf
//
// tcg OBJECT IDENTIFIER ::= {2 23 133}
// tcg-dice OBJECT IDENTIFIER ::= { tcg platformClass(5) 4 }
// tcg-dice-TcbInfo OBJECT IDENTIFIER ::= {tcg-dice 1}
// DiceTcbInfo ::== SEQUENCE {
//     vendor [0] IMPLICIT UTF8String OPTIONAL,
//     model [1] IMPLICIT UTF8String OPTIONAL,
//     version [2] IMPLICIT UTF8String OPTIONAL,
//     svn [3] IMPLICIT INTEGER OPTIONAL,
//     layer [4] IMPLICIT INTEGER OPTIONAL,
//     index [5] IMPLICIT INTEGER OPTIONAL,
//     fwids [6] IMPLICIT FWIDLIST OPTIONAL,
//     flags [7] IMPLICIT OperationalFlags OPTIONAL,
//     vendorInfo [8] IMPLICIT OCTET STRING OPTIONAL,
//     type [9] IMPLICIT OCTET STRING OPTIONAL
// }
// FWIDLIST ::== SEQUENCE SIZE (1..MAX) OF FWID
//     FWID ::== SEQUENCE {
//     hashAlg OBJECT IDENTIFIER,
//     digest OCTET STRING
// }
// OperationalFlags ::= BIT STRING {
//     notConfigured (0),
//     notSecure (1),
//     recovery (2),
//     debug (3)
// }
#[derive(asn1::Asn1Write)]
struct Fwid<'a> {
    hash_alg: asn1::ObjectIdentifier,
    digest: &'a [u8],
}

#[derive(asn1::Asn1Write)]
struct DiceTcbInfo<'a> {
    #[implicit(0)]
    vendor: Option<asn1::Utf8String<'a>>,
    #[implicit(1)]
    model: Option<asn1::Utf8String<'a>>,
    #[implicit(2)]
    version: Option<asn1::Utf8String<'a>>,
    #[implicit(3)]
    svn: Option<asn1::BigInt<'a>>,
    #[implicit(4)]
    layer: Option<asn1::BigInt<'a>>,
    #[implicit(5)]
    index: Option<asn1::BigInt<'a>>,
    #[implicit(6)]
    //fwids: Option<&'a [Fwid<'a>]>,#
    fwids: Option<asn1::SequenceOfWriter<'a, Fwid<'a>>>,
    #[implicit(7)]
    flags: Option<asn1::BitString<'a>>,
    #[implicit(8)]
    vendor_info: Option<&'a [u8]>,
    #[implicit(9)]
    tcb_type: Option<&'a [u8]>,
}

fn dice_tcb_info_extension(
    dice_tcb_info: &DiceTcbInfo
) -> Result<X509Extension> {

    let der = asn1::write_single(dice_tcb_info)?;
    let octet_string = Asn1OctetString::new_from_bytes(&der)?;
    // Unfortunately, the rust binding does not seem to allow creating a Asn1Object
    // from a Nid so we have to manually create it from the OID string.
    let oid = Asn1Object::from_str("2.23.133.5.4.1")?;
    // From DICE specification:
    // The DiceTcbInfo extension SHOULD be marked critical.
    Ok(X509Extension::new_from_der(&oid, true, &octet_string)?)
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

    // FIXME: the rust openssl binding does not allow to choose the subject key ID
    // and always defaults to the "hash" method of the standard. We will need to use
    // raw ASN1 here?
    if false {
        let subj_key_id = extension::SubjectKeyIdentifier::new()
            .build(&builder.x509v3_context(None, None))?;
        builder.append_extension(subj_key_id)?;
    }
    else {
        // FIXME: derived from public_key in a non-standard way
        let key_id = vec![0xDA, 0x39, 0xA3, 0xEE, 0x5E, 0x6B, 0x4B, 0x0D, 0x32, 0x55, 0xBF, 0xEF, 0x95, 0x60, 0x18, 0x90, 0xAF, 0xD8, 0x07, 0x10];
        builder.append_extension(subject_key_id_extension(&key_id)?)?;
    }

    // FIXME: openssl does not support creating an auth key identifier extension without a CA
    // or without some low-level fiddling.
    let key_id = vec![1, 2, 3, 4, 5, 6, 7, 8, 9];
    builder.append_extension(auth_key_id_extension(&key_id)?)?;

    // From https://datatracker.ietf.org/doc/html/rfc4231#section-3.1
    let HAMC_WITH_SHA256 = asn1::ObjectIdentifier::from_string("1.2.840.113549.2.9").unwrap();
    let fwids = [
        Fwid { hash_alg: HAMC_WITH_SHA256.clone(), digest: &[42, 43, 44]},
        Fwid { hash_alg: HAMC_WITH_SHA256.clone(), digest: &[7, 8, 9]},
    ];
    let dice_tcb_info = DiceTcbInfo {
        vendor: Some(asn1::Utf8String::new("OpenTitan")),
        model: Some(asn1::Utf8String::new("Earlgrey")),
        version: Some(asn1::Utf8String::new("version blabla")),
        svn: None,
        index: None,
        layer: None,
        fwids: Some(asn1::SequenceOfWriter::new(&fwids)),
        flags: None,
        vendor_info: None,
        tcb_type: None,
    };
    builder.append_extension(dice_tcb_info_extension(&dice_tcb_info)?)?;

    // Random public key.
    let algo = get_algorithm("ecdsa-with-sha256")?;
    builder.set_pubkey(&algo.key_pair)?;

    // Sign the Certificate
    let algo = get_algorithm("ecdsa-with-sha256")?;
    builder.sign(&algo.key_pair, algo.hash)?;

    Ok(builder.build())
}

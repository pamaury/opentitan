 // Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

use anyhow::{Context, Result};
use clap::{Args, Subcommand, ValueEnum};
use serde_annotate::Annotate;
use std::any::Any;
use std::fs;
use std::path::PathBuf;

use opentitanlib::app::command::CommandDispatch;
use opentitanlib::app::TransportWrapper;
use opentitanlib::certificate::x509;

/// Commands for interacting with certificates.
#[derive(Debug, Subcommand, CommandDispatch)]
pub enum CertificateCommand {
    /// Generate a certificate template.
    GenTemplate(GenTplCommand),
}

/// Generate a certificate template.
#[derive(Clone, Debug, ValueEnum)]
pub enum CertFormat {
    X509,
}

/// Generate a certificate template.
#[derive(Debug, Args)]
pub struct GenTplCommand {
    /// Filename of the template.
    template: PathBuf,
    /// Certificate format
    #[arg(long, value_enum, default_value_t = CertFormat::X509)]
    cert_format: CertFormat,
    /// Filename of the output.
    output: PathBuf,
}

impl CommandDispatch for GenTplCommand {
    fn run(
        &self,
        _context: &dyn Any,
        _transport: &TransportWrapper,
    ) -> Result<Option<Box<dyn Annotate>>> {
        let _template_content = fs::read_to_string(&self.template).with_context(
            || format!("Could not load the template file {}", self.template.display()))?;
        // let template = template::Template::from_hjson_str(&template_content)?;
        // log::info!("template: {:?}", template);
        let x509 = x509::generate()?;
        log::info!("Certificate: {:?}", x509);
        let der = x509.to_der()?;
        fs::write(&self.output, der)?;
        Ok(None)
    }
}

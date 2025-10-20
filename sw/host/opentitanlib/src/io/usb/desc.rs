// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

use anyhow::{Result, anyhow};
use num_enum::{IntoPrimitive, TryFromPrimitive};
use zerocopy::byteorder::little_endian::U16;
use zerocopy::{FromBytes, Immutable, KnownLayout, Unaligned};

#[derive(Copy, Clone, Eq, PartialEq, Debug, TryFromPrimitive, IntoPrimitive)]
#[repr(u8)]
pub enum DescriptorType {
    Device = 1,
    Configuration,
    String,
    Interface,
    Endpoint,
}

#[derive(Copy, Clone, Eq, PartialEq, Debug, TryFromPrimitive, IntoPrimitive)]
#[repr(u8)]
pub enum TransferType {
    Control,
    Isochronous,
    Bulk,
    Interrupt,
}

#[derive(Copy, Clone, Eq, PartialEq, Debug)]
pub enum Direction {
    In,
    Out,
}

#[derive(Clone, FromBytes, KnownLayout, Immutable, Unaligned, Debug)]
#[repr(C)]
pub struct DeviceDescriptor {
    pub length: u8,
    pub desc_type: u8,
    pub usb_version: U16,
    pub class: u8,
    pub subclass: u8,
    pub protocol: u8,
    pub max_pkt_size: u8,
    pub vendor_id: U16,
    pub product_id: U16,
    pub dev_version: U16,
    pub manuf_idx: u8,
    pub product_idx: u8,
    pub serial_idx: u8,
    pub num_config: u8,
}

#[derive(Clone, FromBytes, KnownLayout, Immutable, Unaligned, Debug)]
#[repr(C)]
pub struct ConfigurationDescriptor {
    pub length: u8,
    pub desc_type: u8,
    pub tot_length: U16,
    pub num_intf: u8,
    pub config_val: u8,
    pub str_idx: u8,
    pub attr: u8,
    pub max_power: u8,
}

impl ConfigurationDescriptor {
    pub fn string_index(&self) -> Option<u8> {
        if self.str_idx == 0 {
            None
        } else {
            Some(self.str_idx)
        }
    }
}

#[derive(Clone, FromBytes, KnownLayout, Immutable, Unaligned, Debug)]
#[repr(C)]
pub struct InterfaceDescriptor {
    pub length: u8,
    pub desc_type: u8,
    pub intf_num: u8,
    pub alt_setting: u8,
    pub num_ep: u8,
    pub class: u8,
    pub subclass: u8,
    pub protocol: u8,
    pub str_idx: u8,
}

impl InterfaceDescriptor {
    pub fn string_index(&self) -> Option<u8> {
        if self.str_idx == 0 {
            None
        } else {
            Some(self.str_idx)
        }
    }
}

#[derive(Clone, FromBytes, KnownLayout, Immutable, Unaligned, Debug)]
#[repr(C)]
pub struct EndpointDescriptor {
    pub length: u8,
    pub desc_type: u8,
    pub addr: u8,
    pub attr: u8,
    pub max_pkt_size: U16,
    pub interval: u8,
}

impl EndpointDescriptor {
    pub fn transfer_type(&self) -> TransferType {
        // Conversation cannot fail (all cases are covered).
        (self.attr & 0x3).try_into().unwrap()
    }

    pub fn direction(&self) -> Direction {
        if (self.addr & 0x80) == 0 {
            Direction::Out
        } else {
            Direction::In
        }
    }
}

pub struct Configuration<'a> {
    bytes: &'a [u8],
}

impl<'a> Configuration<'a> {
    pub fn new(bytes: &'a [u8]) -> Self {
        Configuration { bytes }
    }

    pub fn as_bytes(&self) -> &'a [u8] {
        self.bytes
    }

    pub fn descriptor(&self) -> Result<&'a ConfigurationDescriptor> {
        ConfigurationDescriptor::ref_from_prefix(self.bytes)
            .map(|(desc, _)| desc)
            .map_err(|_err| anyhow!("Cannot parse configuration descriptor"))
    }

    pub fn interface_alt_settings(&'a self) -> impl Iterator<Item = Interface<'a>> {
        InterfaceIter {
            configuration: self,
            offset: 0,
        }
    }

    pub fn extra(&self) -> &'a [u8] {
        &[]
    }

    fn next_desc(&self, offset: usize) -> Option<usize> {
        // We need at least one byte to get the size of this descriptor.
        if offset >= self.bytes.len() {
            return None;
        }
        let desc_sz = self.bytes[offset] as usize;
        // If descriptor go beyond the end of buffer, stop here.
        if offset + desc_sz >= self.bytes.len() {
            None
        } else {
            Some(offset + desc_sz)
        }
    }

    fn next_desc_of_type(
        &self,
        offset: usize,
        desc_type: DescriptorType,
        stop_at: Option<DescriptorType>,
    ) -> Option<usize> {
        let mut cur_offset = offset;
        while let Some(next_offset) = self.next_desc(cur_offset) {
            // We need at least two bytes to get the type of this descriptor.
            if next_offset + 1 >= self.bytes.len() {
                break;
            }
            let r#type = self.bytes[next_offset + 1];
            if r#type == u8::from(desc_type) {
                return Some(next_offset);
            }
            if let Some(stop_at_type) = stop_at {
                if r#type == u8::from(stop_at_type) {
                    break;
                }
            }
            cur_offset = next_offset;
        }
        None
    }
}

pub struct Interface<'a> {
    configuration: &'a Configuration<'a>,
    offset: usize,
}

struct InterfaceIter<'a> {
    configuration: &'a Configuration<'a>,
    offset: usize,
}

impl<'a> Iterator for InterfaceIter<'a> {
    type Item = Interface<'a>;

    fn next(&mut self) -> Option<Self::Item> {
        match self.configuration.next_desc_of_type(
            self.offset,
            DescriptorType::Interface,
            Some(DescriptorType::Configuration),
        ) {
            None => None,
            Some(offset) => {
                self.offset = offset;
                Some(Interface {
                    configuration: self.configuration,
                    offset,
                })
            }
        }
    }
}

impl<'a> Interface<'a> {
    pub fn descriptor(&self) -> Result<&'a InterfaceDescriptor> {
        InterfaceDescriptor::ref_from_prefix(&self.configuration.bytes[self.offset..])
            .map(|(desc, _)| desc)
            .map_err(|_err| anyhow!("Cannot parse interface descriptor"))
    }

    pub fn endpoints(&self) -> impl Iterator<Item = Endpoint<'a>> {
        EndpointIter {
            configuration: self.configuration,
            offset: self.offset,
        }
    }

    pub fn extra(&self) -> &'a [u8] {
        &[]
    }
}

struct EndpointIter<'a> {
    configuration: &'a Configuration<'a>,
    offset: usize,
}

impl<'a> Iterator for EndpointIter<'a> {
    type Item = Endpoint<'a>;

    fn next(&mut self) -> Option<Self::Item> {
        match self.configuration.next_desc_of_type(
            self.offset,
            DescriptorType::Endpoint,
            Some(DescriptorType::Interface),
        ) {
            None => None,
            Some(offset) => {
                self.offset = offset;
                Some(Endpoint {
                    configuration: self.configuration,
                    offset,
                })
            }
        }
    }
}

pub struct Endpoint<'a> {
    configuration: &'a Configuration<'a>,
    offset: usize,
}

impl<'a> Endpoint<'a> {
    pub fn descriptor(&self) -> Result<&'a EndpointDescriptor> {
        EndpointDescriptor::ref_from_prefix(&self.configuration.bytes[self.offset..])
            .map(|(desc, _)| desc)
            .map_err(|_err| anyhow!("Cannot parse endpoint descriptor"))
    }
}

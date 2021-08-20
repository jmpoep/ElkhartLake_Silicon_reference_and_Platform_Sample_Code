/** @file
  Intel ACPI Sample Code for Discrete Connectivity module

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

OperationRegion(RPXX, PCI_Config, 0x00, 0x10)
Field(RPXX, AnyAcc, NoLock, Preserve)
{
  Offset(0),     // Vendor-Device ID
  VDID, 32,
}

OperationRegion (FLDR, PCI_Config, 0x44, 0x06)
Field (FLDR, ByteAcc, NoLock, Preserve)
{
  DCAP, 32,
  DCTR, 16,
}

// WIST (WiFi Device Presence Status)
//
// Check if a WiFi Device is present on the RootPort.
//
// Arguments: (0)
//   None
// Return Value:
//    0 - if a device is not present.
//    1 - if a device is present.
//
Method(WIST,0,Serialized)
{
  // check Vendor-Device ID for supported devices
  If(CondRefOf(VDID)){
    Switch(ToInteger(VDID)){
      Case(0x095A8086){Return(1)} // StonePeak
      Case(0x095B8086){Return(1)} // StonePeak
      Case(0x31658086){Return(1)} // StonePeak 1x1
      Case(0x31668086){Return(1)} // StonePeak 1x1
      Case(0x08B18086){Return(1)} // WilkinsPeak
      Case(0x08B28086){Return(1)} // WilkinsPeak
      Case(0x08B38086){Return(1)} // WilkinsPeak
      Case(0x08B48086){Return(1)} // WilkinsPeak
      Case(0x24F38086){Return(1)} // SnowfieldPeak
      Case(0x24F48086){Return(1)} // SnowfieldPeak
      Case(0x24F58086){Return(1)} // Lighting Peak 1x1
      Case(0x24F68086){Return(1)} // SnF/LnP/DgP SKUs
      Case(0x24FD8086){Return(1)} // Windstorm Peak
      Case(0x24FB8086){Return(1)} // Sandy Peak
      Case(0x25268086){Return(1)} // Intel Wireless-AC 9260(Thunder Peak 2)
      Case(0x271B8086){Return(1)} // Intel Wireless-AC 9260(Thunder Peak 1)
      Default{Return(0)}          // no supported device
    }
  }Else{
    Return(0)
  }
}

// WWST (WWAN Device Presence Status)
//
// Check if a WWAN Device is present on the RootPort.
//
// Arguments: (0)
//   None
// Return Value:
//    0 - if a device is not present.
//    1 - if a device is present.
//
Method(WWST,0,Serialized)
{
  // check Vendor-Device ID for supported devices
  If(CondRefOf(VDID)){
    Switch(ToInteger(VDID)){
      Case(0x73608086){Return(1)} // XMM7360 - Need to confirm with Target Platform Modem Team
      Case(0x75608086){Return(1)} // XMM7560 - Need to confirm with Target Platform Modem Team
      Default{Return(0)}          // no supported device
    }
  }Else{
    Return(0)
  }
}

//
// Load Wifi/BT/WiGig tables only the Vendor ID, Device ID matches
//
If (WIST())
{
  Include("Wifi.asl")
}

//
// Load WWAN tables only the Vendor ID, Device ID matches
//
If(WWST())
{
  Include("Wwan.asl")
}

//
// Load Platform-level device reset tables only the Vendor ID, Device ID matches
//
If (LOr(WIST(),WWST()))
{
  Include("DiscreteConnectivityReset.asl")
}
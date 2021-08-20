/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2017 Intel Corporation.

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
#include <Base.h>
#include <Uefi.h>
#include <IndustryStandard/Pci22.h>
#include <Protocol/PciIo.h>
#include <Library/DebugLib.h>

VOID
EFIAPI
OpromPatchPciIo (
  IN EFI_PCI_IO_PROTOCOL           *PciIo
  )
{
  PCI_DEVICE_INDEPENDENT_REGION  PciHeader;
  EFI_PCI_ROM_HEADER             RomHeader;
  PCI_DATA_STRUCTURE             *Pcir;
  UINTN                          Segment;
  UINTN                          Bus;
  UINTN                          Device;
  UINTN                          Function;

  if ((PciIo->RomSize == 0) || (PciIo->RomImage == NULL)) {
    return ;
  }
  PciIo->GetLocation (PciIo, &Segment, &Bus, &Device, &Function);
  PciIo->Pci.Read (
               PciIo,
               EfiPciIoWidthUint32,
               0,
               (sizeof (PciHeader.VendorId) + sizeof (PciHeader.DeviceId)) / sizeof (UINT32),
               &PciHeader
               );
  DEBUG ((DEBUG_INFO, "OpromPatchEntrypoint - %02x, %02x, %02x\n", Bus, Device, Function));
  DEBUG ((DEBUG_INFO, "OpromPatchEntrypoint - %04x:%04x\n", (UINTN)PciHeader.VendorId, (UINTN)PciHeader.DeviceId));
  DEBUG ((DEBUG_INFO, "OpromPatchEntrypoint - Rom: %08x:%08x\n", (UINTN)PciIo->RomImage, (UINTN)PciIo->RomSize));
  RomHeader.Raw = PciIo->RomImage;
  Pcir = (PCI_DATA_STRUCTURE *) (RomHeader.Raw + RomHeader.Generic->PcirOffset);
  DEBUG ((DEBUG_INFO, "OpromPatchEntrypoint - Pcir: %04x:%04x\n", (UINTN)Pcir->VendorId, (UINTN)Pcir->DeviceId));

  //
  // Fix MS-HD5770 video adapter can not work:
  // This device is not a OPROM 3.0 and does not have device id list as well.
  // It only have 1 device id in OPROM.
  // Device Id in OpROM is not same with the value in PCI configuration space
  // it will cause VBIOS fails to start
  //
  if ((PciHeader.VendorId == 0x1002) && (PciHeader.DeviceId == 0x68BE)) {
    DEBUG ((DEBUG_INFO, "MS-HD5770 video adapter\n"));
    if ((Pcir->VendorId == 0x1002) &&(Pcir->DeviceId ==0x68B8)) {
      //
      // Assign same device id in PCI configuration space
      //
      Pcir->DeviceId = PciHeader.DeviceId;
    }
  }

  return ;
}


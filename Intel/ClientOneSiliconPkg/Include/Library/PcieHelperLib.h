/** @file
  Header file for PCI Express helpers base library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _PCIE_HELPER_LIB_H_
#define _PCIE_HELPER_LIB_H_

#include <PcieRegs.h>
#include <Register/PchPcieRpMultiVcRegs.h>
#include <Library/PciSegmentLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <IndustryStandard/Pci.h>

/**
  Find the Offset to a given Capabilities ID
  CAPID list:
    0x01 = PCI Power Management Interface
    0x04 = Slot Identification
    0x05 = MSI Capability
    0x10 = PCI Express Capability

  @param[in] DeviceBase           device's base address
  @param[in] CapId                CAPID to search for

  @retval 0                       CAPID not found
  @retval Other                   CAPID found, Offset of desired CAPID
**/
UINT8
PcieBaseFindCapId (
  IN UINT64  DeviceBase,
  IN UINT8   CapId
  );

/**
  Find the Offset to a given Capabilities ID
  CAPID list:
    0x01 = PCI Power Management Interface
    0x04 = Slot Identification
    0x05 = MSI Capability
    0x10 = PCI Express Capability

  @param[in] Segment              Pci Segment Number
  @param[in] Bus                  Pci Bus Number
  @param[in] Device               Pci Device Number
  @param[in] Function             Pci Function Number
  @param[in] CapId                CAPID to search for

  @retval 0                       CAPID not found
  @retval Other                   CAPID found, Offset of desired CAPID
**/
UINT8
PcieFindCapId (
  IN UINT8   Segment,
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT8   CapId
  );

/**
  Search and return the offset of desired Pci Express Capability ID
  CAPID list:
    0x0001 = Advanced Error Reporting Capability
    0x0002 = Virtual Channel Capability
    0x0003 = Device Serial Number Capability
    0x0004 = Power Budgeting Capability

  @param[in] DeviceBase           device base address
  @param[in] CapId                Extended CAPID to search for

  @retval 0                       CAPID not found, this includes situation where device doesn't exist
  @retval Other                   CAPID found, Offset of desired CAPID
**/
UINT16
PcieBaseFindExtendedCapId (
  IN UINT64  DeviceBase,
  IN UINT16  CapId
  );

/**
  Search and return the offset of desired Pci Express Capability ID
  CAPID list:
    0x0001 = Advanced Error Rreporting Capability
    0x0002 = Virtual Channel Capability
    0x0003 = Device Serial Number Capability
    0x0004 = Power Budgeting Capability

  @param[in] Segment              Pci Segment Number
  @param[in] Bus                  Pci Bus Number
  @param[in] Device               Pci Device Number
  @param[in] Function             Pci Function Number
  @param[in] CapId                Extended CAPID to search for

  @retval 0                       CAPID not found
  @retval Other                   CAPID found, Offset of desired CAPID
**/
UINT16
PcieFindExtendedCapId (
  IN UINT8   Segment,
  IN UINT8   Bus,
  IN UINT8   Device,
  IN UINT8   Function,
  IN UINT16  CapId
  );

/*
  Checks device's Slot Clock Configuration

  @param[in] Base            device's base address
  @param[in] PcieCapOffset   devices Pci express capability list register offset

  @retval TRUE when device device uses slot clock, FALSE otherwise
*/
BOOLEAN
GetScc (
  UINT64    Base,
  UINT8     PcieCapOffset
  );

/*
  Sets Common Clock Configuration bit for given device.
  @param[in] PcieCapOffset   devices Pci express capability list register offset
  @param[in] Base            device's base address
*/
VOID
EnableCcc (
  UINT64    Base,
  UINT8     PcieCapOffset
  );

/*
  Retrains link behind given device.
  It only makes sense to call it for downstream ports.
  If called for upstream port nothing will happen, it won't enter infinite loop.

  @param[in] Base                 device's base address
  @param[in] PcieCapOffset        devices Pci express capability list register offset
  @param[boolean] WaitUnitlDone   when TRUE, function waits until link has retrained
*/
VOID
RetrainLink (
  UINT64  Base,
  UINT8   PcieCapOffset,
  BOOLEAN WaitUntilDone
  );

/*
  Checks if device at given address exists

  @param[in] Base            device's base address

  @retval TRUE when device exists; FALSE otherwise
*/
BOOLEAN
IsDevicePresent (
  UINT64 Base
  );

/*
  Checks if device is a multifunction device

  @param[in] Base            device's base address

  @retval TRUE if multifunction; FALSE otherwise
*/
BOOLEAN
IsMultifunctionDevice (
  UINT64 Base
  );
#endif // _PCIE_HELPER_LIB_H_

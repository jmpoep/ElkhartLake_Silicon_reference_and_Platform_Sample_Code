/**@file

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _PCI_HOT_PLUG_HELPERS_H_
#define _PCI_HOT_PLUG_HELPERS_H_

#include "PciHotPlug.h"
#include <Library/PciSegmentLib.h>

/**
  Find the Offset to a given Capabilities ID
  CAPID list:
    0x10 = PCI Express Capability

  @param[in] Segment              Segment Number
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
  Get the Parent Pci Address

  @param[in] Segment              Segment Number
  @param[in] CurrentRpBus         P2P Bridge Bus Number

  @retval ParentP2PBridgeBase     Parent Pci Address
**/
UINT64
GetParentPciAddress (
  IN  UINT8  Segment,
  IN  UINT64 CurrentRpBus
  );

/**
  Get the Parent Resource

  @param[in]  HpcPciAddress       The address of the Hot Plug Controller function on the PCI bus.
  @param[out] ParentBusNum        Parent Reserved Bus resource Number.
  @param[out] ParentPcieMegaMem   Parent Reserved Alignment of MEM resource.
  @param[out] ParentPciePMegaMem  Parent Reserved Alignment of PMEM resource.
  @param[out] ParentPcieKiloIo    Parent Reserved Pcie Kilo Io Number.

  @retval     EFI_SUCCESS.
**/
EFI_STATUS
GetParentResourceSize (
  IN  UINT64 HpcPciAddress,
  OUT UINT8  *ParentBusNum,
  OUT UINT16 *ParentPcieMegaMem,
  OUT UINT16 *ParentPciePMegaMem,
  OUT UINT8  *ParentPcieKiloIo
  );

/**
  Check the HotPlug Capable of P2P bridge at the same Bus

  @param[in]  Segment             Segment Number
  @param[in]  CurrentRpBus        P2P Bridge Bus Number.
  @param[out] *StrucIndex         Indxe number of NUMBER_OF_HOTPLUG_BRIDGE struct.

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_INVALID_PARAMETER   Invalid Bus number.
  @retval EFI_ABORTED             No matched P2P Bridge, exit without recorded.
**/
EFI_STATUS
GetCurrentBusP2pbHotPlug (
  IN  UINT8  Segment,
  IN  UINT8  CurrentRpBus,
  OUT UINT8  *StrucIndex
  );

#endif

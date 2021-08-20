/** @file
  Gbe Library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/SpiAccessLib.h>
#include <Library/GbeMdiLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/GbeRegs.h>

/**
  Check whether GbE region is valid
  Check SPI region directly since GbE might be disabled in SW.

  @retval TRUE                    Gbe Region is valid
  @retval FALSE                   Gbe Region is invalid
**/
BOOLEAN
IsGbeRegionValid (
  VOID
  )
{
  return SpiIsGbeRegionValid ();
}

/**
  Check whether GBE controller is enabled in the platform.

  @retval TRUE                    GbE is enabled
  @retval FALSE                   GbE is disabled
**/
BOOLEAN
IsGbePresent (
  VOID
  )
{
  //
  // Check PCH Support
  //
  if (!PchIsGbeSupported ()) {
    return FALSE;
  }
  //
  // Check PMC strap/fuse
  //
  if (!PmcIsGbeSupported ()) {
    return FALSE;
  }
  //
  // Check GbE NVM
  //
  if (IsGbeRegionValid () == FALSE) {
    return FALSE;
  }
  return TRUE;
}

/**
  Returns Gigabit Ethernet PCI Device Number

  @retval  GbE device number
**/
UINT8
GbeDevNumber (
  VOID
  )
{
  return PCI_DEVICE_NUMBER_GBE;
}

/**
  Returns Gigabit Ethernet PCI Function Number

  @retval  GbE function number
**/
UINT8
GbeFuncNumber (
  VOID
  )
{
  return PCI_FUNCTION_NUMBER_GBE;
}


/**
  Verifies Gigabit Ethernet PCI Class Code

  @param [in]  GbePciCfgBase      GbE PCI Config Space Address

  @retval TRUE                    GbE Class Code match
  @retval FALSE                   GbE Class Code does not match
**/
BOOLEAN
STATIC
GbeCheckClassCode (
  UINT64 GbePciCfgBase
  )
{
  UINT8 BaseCode;
  UINT8 SubClassCode;

  SubClassCode  = PciSegmentRead8 (GbePciCfgBase + PCI_CLASSCODE_OFFSET + 1);
  BaseCode      = PciSegmentRead8 (GbePciCfgBase + PCI_CLASSCODE_OFFSET + 2);

  if ((BaseCode != PCI_CLASS_NETWORK) || (SubClassCode != PCI_CLASS_NETWORK_ETHERNET)) {
    DEBUG ((DEBUG_ERROR, "GbeCheckClassCode : BaseCode(0x%x) or ClassCode(0x%x) is not supported\n", BaseCode, SubClassCode));
    ASSERT (FALSE);
    return FALSE;
  }
  return TRUE;
}

/**
  Checks if Gbe is Enabled or Disabled

  @retval  BOOLEAN    TRUE if device is enabled, FALSE otherwise.
**/
BOOLEAN
IsGbeEnabled (
  VOID
  )
{
  UINT64  GbePciBase;

  GbePciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 GbeDevNumber (),
                 GbeFuncNumber (),
                 0
                 );

  if (PciSegmentRead32 (GbePciBase) != 0xFFFFFFFF) {
    return GbeCheckClassCode (GbePciBase);
  }

  return FALSE;
}

/**
  Gets Phy Revision and Model Number

  @param [out] LanPhyRevision   Return Value

  @return EFI_SUCCESS           Phy Revision was obtained
          EFI_NOT_FOUND         Gbe is disabled or not present
          EFI_DEVICE_ERROR      Gbe class code check failed
          EFI_INVALID_PARAMETER When GbeBar is incorrect
                                When Phy register or address is out of bounds
**/
EFI_STATUS
GbeGetLanPhyRevision (
  OUT  UINT16  *LanPhyRevision
  )
{
  UINT64          GbePciBase;
  EFI_PCI_PMCSR   GbePciPmCsr;
  EFI_PCI_PMCSR   GbePciPmCsrTemp;
  UINT8           GbePciCmd;
  UINT32          GbeBar;
  EFI_STATUS      Status;

  GbePciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 GbeDevNumber (),
                 GbeFuncNumber (),
                 0
                 );

  if (PciSegmentRead32 (GbePciBase) == 0xFFFFFFFF) {
    return EFI_NOT_FOUND;
  }

  if (!GbeCheckClassCode (GbePciBase)) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Put Gbe in D0
  //
  GbePciPmCsr.Data = PciSegmentRead16 (GbePciBase + R_GBE_CFG_PMCS);
  GbePciPmCsrTemp.Data = GbePciPmCsr.Data;
  GbePciPmCsrTemp.Bits.PowerState = 0;

  PciSegmentWrite16 (GbePciBase + R_GBE_CFG_PMCS, GbePciPmCsrTemp.Data);

  GbeBar = PciSegmentRead32 (GbePciBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFE0000;
  if (GbeBar == 0) {
    return EFI_DEVICE_ERROR;
  }
  GbePciCmd = PciSegmentRead8 (GbePciBase + PCI_COMMAND_OFFSET);

  //
  // Overwrite previous state of the command register
  //
  PciSegmentWrite8 ((GbePciBase + PCI_COMMAND_OFFSET), EFI_PCI_COMMAND_MEMORY_SPACE);

  Status = GbeMdiGetLanPhyRevision (GbeBar, LanPhyRevision);

  //
  // Restore command register
  //
  PciSegmentWrite8 ((GbePciBase + PCI_COMMAND_OFFSET), GbePciCmd);

  //
  // Restore PMCS
  //
  PciSegmentWrite16 (GbePciBase + R_GBE_CFG_PMCS, GbePciPmCsr.Data);

  return Status;
}


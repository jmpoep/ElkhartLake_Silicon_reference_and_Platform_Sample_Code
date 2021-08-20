/** @file
  Initializes GBE Device in PEI

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/GbeLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PchFiaLib.h>
#include <Library/PeiItssLib.h>
#include <Library/PeiPchPcieClocksLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/SiScheduleResetLib.h>
#include "PchResetPlatformSpecific.h"
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/GbeRegs.h>

/**
  Check whether GbE is enabled in PMC.
**/
STATIC
BOOLEAN
PmcIsGbeEnabled (
  VOID
  )
{
  //
  // Is GbE disabled by PMC strap/fuse
  //
  if (!PmcIsGbeSupported ()) {
    return FALSE;
  }
  //
  // Is GbE disabled by static power gating
  //
  if (PmcIsGbeFunctionDisabled ()) {
    return FALSE;
  }

  return TRUE;
}

/**
  Schedules global reset required to change GbE static power gating state.
**/
STATIC
VOID
GbeGlobalReset (
  VOID
  )
{
  PCH_RESET_DATA             ResetData;

  DEBUG ((DEBUG_ERROR, "GbeGlobalReset\n"));

  CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
  StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
  SiScheduleResetSetType (EfiResetPlatformSpecific, &ResetData);
}

/**
  Enable GbE by disabling static power gating.
**/
STATIC
VOID
EnableGbe (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "Enabling internal LAN...\n"));

  //
  // Before modifying LAN Disable bit, make sure it's not locked.
  //
  ASSERT (!PmcIsFunctionDisableConfigLocked ());

  //
  // Enable the Internal GbE Controller
  //
  PmcEnableGbe ();
}


/**
  Disable the Internal GbE Controller

  BIOS has the ability to disable the LAN Controller functionality, in addition to
  configuring PMC to disable the LAN Controller BIOS need to set Disable bit in the
  LANDISCTRL register and then lock the LANDISCTRL register by setting the Lock bit in
  the LOCKLANDIS register.
**/
STATIC
VOID
DisableGbe (
  VOID
  )
{
  UINT64  GbePciBase;

  DEBUG ((DEBUG_INFO, "Disabling internal LAN...\n"));

  GbePciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 GbeDevNumber (),
                 GbeFuncNumber (),
                 0
                 );

  ASSERT (PciSegmentRead32 (GbePciBase) != 0xFFFFFFFF);

  //
  // Set LANDISCTRL, GbE PCI config + 0xA0 bit[0] to 1
  //
  PciSegmentOr32 (GbePciBase + R_GBE_CFG_LANDISCTRL, B_GBE_CFG_LANDISCTRL_DISABLE);
  ASSERT (PciSegmentRead32 (GbePciBase) != 0xFFFFFFFF);

  //
  // Set LOCKLANDIS, GbE PCI config + 0xA4 bit[0] to 1
  //
  PciSegmentOr32 (GbePciBase + R_GBE_CFG_LOCKLANDIS, B_GBE_CFG_LOCKLANDIS_LOCK);

  //
  // LAN function is hidden now
  //
  ASSERT (PciSegmentRead32 (GbePciBase) == 0xFFFFFFFF);

  //
  // Before modifying LAN Disable bit, make sure it's not locked and not disabled yet
  //
  ASSERT (!PmcIsFunctionDisableConfigLocked ());
  ASSERT (!PmcIsGbeFunctionDisabled ());

  //
  // Disable GbE Controller (static PG)
  //
  PmcStaticDisableGbe ();
}

/**
  Configure LAN device registers based on policy settings.
  @param[in] SiPolicy             The SI Policy PPI instance

**/
STATIC
VOID
ConfigureGbeRegisters (
  IN  SI_POLICY_PPI               *SiPolicy
  )
{
  UINT64          GbePciBase;
  UINT32          GbeMemBar;
  EFI_STATUS      Status;
  GBE_CONFIG      *GbeConfig;
  PCH_PM_CONFIG   *PmConfig;
  UINT8           InterruptPin;

  DEBUG ((DEBUG_INFO, "ConfigureGbe\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gGbeConfigGuid, (VOID *) &GbeConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);

  GbePciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 GbeDevNumber (),
                 GbeFuncNumber (),
                 0
                 );

  ASSERT (GbeConfig->Enable);
  ASSERT (PciSegmentRead32 (GbePciBase) != 0xFFFFFFFF);

  //
  // Set GbE PCI config + 0x80 (CPCE) bit[5] (HAE) = 1
  //
  PciSegmentOr32 (GbePciBase + R_GBE_CFG_CPCE, B_GBE_CFG_CPCE_HAE);

  //
  // Set GbE PCI config + 0x94 (clock control of GBE) to 0x1F
  // To avoid blocking PCH floor power measurement when GbE enabled.
  //
  PciSegmentWrite8 (GbePciBase + R_GBE_CFG_CLCTL, 0x1F);

  //
  // Set LOCKLANDIS, GbE PCI config + 0xA4 bit[0]
  //
  PciSegmentOr32 (GbePciBase + R_GBE_CFG_LOCKLANDIS, B_GBE_CFG_LOCKLANDIS_LOCK);

  //
  //
  // LAN LTR Programming
  // The maximum snoop/non-snoop platform latency values to 3ms
  // Program GbE controller's PCI LTR capability register at D31:F6:Reg 0A8h
  //
  if (GbeConfig->LtrEnable == TRUE) {
    PciSegmentWrite32 (GbePciBase + R_GBE_CFG_LTR_CAP, 0x10031003);
  }

  ///
  /// Configure GbE interrupt
  ///
  InterruptPin = ItssGetDevIntPin (SiPolicy, GbeDevNumber (), GbeFuncNumber ());

  PciSegmentWrite8 (GbePciBase + PCI_INT_PIN_OFFSET, InterruptPin);

  //
  // Assign MMIO resource to Gbe controller
  //
  GbeMemBar = PcdGet32 (PcdSiliconInitTempMemBaseAddr);
  PciSegmentWrite32 (GbePciBase + R_GBE_CFG_MBARA, GbeMemBar);
  PciSegmentOr16 (GbePciBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);

  //
  // Additional GbE Controller Configurations for WOL Support
  // System BIOS requires to program the registers listed below for internal GbE.
  // 1. Set MBARA + 2Ch[31] = 1b
  // 2. If WOL is enabled set MBARA + Offset 2Ch[30] = 1b
  //    Else if disabled set MBARA + 2Ch[30] = 0b
  //
  if (PmConfig->WakeConfig.WolEnableOverride) {
    MmioOr32 (GbeMemBar + R_GBE_MEM_CSR_FEXT, B_GBE_MEM_CSR_FEXT_WOL | B_GBE_MEM_CSR_FEXT_WOL_VALID);
  } else {
    MmioAndThenOr32 (GbeMemBar + R_GBE_MEM_CSR_FEXT, (UINT32) ~(B_GBE_MEM_CSR_FEXT_WOL), B_GBE_MEM_CSR_FEXT_WOL_VALID);
  }

  if (IsClkReqAssigned (PchClockUsageLan)) {
    MmioOr32 (GbeMemBar + R_GBE_MEM_CSR_FEXTNVM6, B_GBE_MEM_CSR_FEXTNVM6_K1OFF_EN);
    DEBUG((DEBUG_INFO, "K1Off enabled.\n"));
  } else {
    DEBUG ((DEBUG_ERROR, "Error: K1Off requires CLKREQ# support -- disabled!\n"));
  }

  //
  // Enable internal ECC for Gbe Controller
  // Set GbeMemBar + 0x100c [16] to 1b
  // Set GbeMemBar + 0 [19] to 1b
  //
  MmioOr32 (GbeMemBar + R_GBE_MEM_CSR_PBECCSTS, B_GBE_MEM_CSR_PBECCSTS_ECC_EN);
  MmioOr32 (GbeMemBar + R_GBE_MEM_CSR_CTRL, B_GBE_MEM_CSR_CTRL_MEHE);

  //
  // Disable memory space decoding
  //
  PciSegmentAnd16 (GbePciBase + PCI_COMMAND_OFFSET, (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE);
  PciSegmentWrite32 (GbePciBase + R_GBE_CFG_MBARA, 0);
}


/**
  Initialize LAN device.

  Global reset may be perfomed due to static power gating requirements.

  @param[in] SiPolicy             The SI Policy PPI instance

**/
VOID
GbeInit (
  IN  SI_POLICY_PPI               *SiPolicy
  )
{
  EFI_STATUS                      Status;
  GBE_CONFIG                      *GbeConfig;

  DEBUG ((DEBUG_INFO, "GbeInit() Start\n"));
  Status = GetConfigBlock ((VOID *) SiPolicy, &gGbeConfigGuid, (VOID *) &GbeConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "GbePmcEnabled:  %d\n",  PmcIsGbeEnabled ()));
  DEBUG ((DEBUG_INFO, "GbePortNumber:  %d\n",  PchFiaGetGbePortNumber ()));
  DEBUG ((DEBUG_INFO, "GbeRegionValid: %d\n",  IsGbeRegionValid ()));
  DEBUG ((DEBUG_INFO, "GbePresent:     %d\n",  IsGbePresent ()));

  //
  // Enable CLKREQ# if supported by board regardless of GbE being enabled
  // to allow clock shut-down.
  //
  EnableClkReq (PchClockUsageLan);

  if (PmcIsGbeEnabled ()) {
    if (GbeConfig->Enable && IsGbePresent ()) {
      //
      // Apply GbE settings
      //
      ConfigureGbeRegisters (SiPolicy);
    } else {
      //
      // GbE is not power gated by PMC but is not available in the platform or is disabled via policy
      // Perform GbE disabling flow
      //
      DisableGbe ();
      //
      // Global reset is required for GbE to enter static power gating
      //
      GbeGlobalReset();
    }
  } else {
    if (GbeConfig->Enable && IsGbePresent ()) {
      //
      // GbE is power gated but available in the platform and enabled with policy.
      // Perform enabling flow.
      //
      DEBUG ((DEBUG_INFO, "Gbe found disabled and requested to be enabled - clear PG bit in PMC and issue reset!\n"));
      EnableGbe ();
      //
      // Global reset is required to get GbE out of static power gating
      //
      GbeGlobalReset ();
    } else {
      DisableClock (PchClockUsageLan);
      PmcGbeModPhyPowerGating ();

      DEBUG ((DEBUG_INFO, "LAN disabled\n"));
    }
  }
  DEBUG ((DEBUG_INFO, "GbeInit() End\n"));
}


/** @file
  This file provides services for Pmc policy function

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
#include <Library/DebugLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PchInfoLib.h>
#include <Ppi/SiPolicy.h>
#include <PmConfig.h>

/**
  Print PCH_PM_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
PmcPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS    Status;
  PCH_PM_CONFIG *PmConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ PCH PM Config ------------------\n"));

  DEBUG ((DEBUG_INFO, " WakeConfig PmeB0S5Dis               = %x\n", PmConfig->WakeConfig.PmeB0S5Dis));
  DEBUG ((DEBUG_INFO, " WakeConfig WolEnableOverride        = %x\n", PmConfig->WakeConfig.WolEnableOverride));
  DEBUG ((DEBUG_INFO, " WakeConfig LanWakeFromDeepSx        = %x\n", PmConfig->WakeConfig.LanWakeFromDeepSx));
  DEBUG ((DEBUG_INFO, " WakeConfig PcieWakeFromDeepSx       = %x\n", PmConfig->WakeConfig.PcieWakeFromDeepSx));
  DEBUG ((DEBUG_INFO, " WakeConfig WoWlanEnable             = %x\n", PmConfig->WakeConfig.WoWlanEnable));
  DEBUG ((DEBUG_INFO, " WakeConfig WoWlanDeepSxEnable       = %x\n", PmConfig->WakeConfig.WoWlanDeepSxEnable));

  DEBUG ((DEBUG_INFO, " PchDeepSxPol                        = %x\n", PmConfig->PchDeepSxPol));
  DEBUG ((DEBUG_INFO, " PchSlpS3MinAssert                   = %x\n", PmConfig->PchSlpS3MinAssert));
  DEBUG ((DEBUG_INFO, " PchSlpS4MinAssert                   = %x\n", PmConfig->PchSlpS4MinAssert));
  DEBUG ((DEBUG_INFO, " PchSlpSusMinAssert                  = %x\n", PmConfig->PchSlpSusMinAssert));
  DEBUG ((DEBUG_INFO, " PchSlpAMinAssert                    = %x\n", PmConfig->PchSlpAMinAssert));
  DEBUG ((DEBUG_INFO, " SlpStrchSusUp                       = %x\n", PmConfig->SlpStrchSusUp));
  DEBUG ((DEBUG_INFO, " SlpLanLowDc                         = %x\n", PmConfig->SlpLanLowDc));
  DEBUG ((DEBUG_INFO, " PwrBtnOverridePeriod                = %x\n", PmConfig->PwrBtnOverridePeriod));
  DEBUG ((DEBUG_INFO, " DisableEnergyReport                 = %x\n", PmConfig->DisableEnergyReport));
  DEBUG ((DEBUG_INFO, " DisableDsxAcPresentPulldown         = %x\n", PmConfig->DisableDsxAcPresentPulldown));
  DEBUG ((DEBUG_INFO, " PchPwrCycDur                        = %x\n", PmConfig->PchPwrCycDur));
  DEBUG ((DEBUG_INFO, " PciePllSsc                          = %x\n", PmConfig->PciePllSsc));
  DEBUG ((DEBUG_INFO, " DisableNativePowerButton            = %x\n", PmConfig->DisableNativePowerButton));
  DEBUG ((DEBUG_INFO, " MeWakeSts                           = %x\n", PmConfig->MeWakeSts));
  DEBUG ((DEBUG_INFO, " WolOvrWkSts                         = %x\n", PmConfig->WolOvrWkSts));
  DEBUG ((DEBUG_INFO, " EnableTcoTimer                      = %x\n", PmConfig->EnableTcoTimer));
  DEBUG ((DEBUG_INFO, " VrAlert                             = %x\n", PmConfig->VrAlert));
  DEBUG ((DEBUG_INFO, " PowerButtonDebounce                 = %x\n", PmConfig->PowerButtonDebounce));
  DEBUG ((DEBUG_INFO, " PsOnEnable                          = %x\n", PmConfig->PsOnEnable));
  DEBUG ((DEBUG_INFO, " CpuC10GatePinEnable                 = %x\n", PmConfig->CpuC10GatePinEnable));
  DEBUG ((DEBUG_INFO, " PmcDbgMsgEn                         = %x\n", PmConfig->PmcDbgMsgEn));
  DEBUG ((DEBUG_INFO, " ModPhySusPgEnable                   = %x\n", PmConfig->ModPhySusPgEnable));
  DEBUG ((DEBUG_INFO, " Usb2PhySusPgEnable                  = %x\n", PmConfig->Usb2PhySusPgEnable));
  DEBUG ((DEBUG_INFO, " OsIdleEnable                        = %x\n", PmConfig->OsIdleEnable));
  DEBUG ((DEBUG_INFO, " GrTscEnable                         = %x\n", PmConfig->GrTscEnable));
  DEBUG ((DEBUG_INFO, " V1p05PhyExtFetControlEn             = %x\n", PmConfig->V1p05PhyExtFetControlEn));
  DEBUG ((DEBUG_INFO, " V1p05IsExtFetControlEn              = %x\n", PmConfig->V1p05IsExtFetControlEn));
  DEBUG ((DEBUG_INFO, " LpmS0ixSubStateEnable               = %x\n", PmConfig->LpmS0ixSubStateEnable.Val));
  DEBUG ((DEBUG_INFO, " S0ixAutoDemotion                    = %x\n", PmConfig->S0ixAutoDemotion));
  DEBUG ((DEBUG_INFO, " LatchEventsC10Exit                  = %x\n", PmConfig->LatchEventsC10Exit));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
PmcLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  PCH_PM_CONFIG  *PmConfig;
  PmConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "PmConfig->Header.GuidHob.Name = %g\n", &PmConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PmConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PmConfig->Header.GuidHob.Header.HobLength));

  PmConfig->MeWakeSts                            = TRUE;
  PmConfig->WolOvrWkSts                          = TRUE;

  PmConfig->WakeConfig.WolEnableOverride         = TRUE;
  PmConfig->WakeConfig.LanWakeFromDeepSx         = TRUE;

  PmConfig->PchSlpS3MinAssert                    = PchSlpS350ms;
  PmConfig->PchSlpS4MinAssert                    = PchSlpS41s;
  PmConfig->PchSlpSusMinAssert                   = PchSlpSus4s;
  PmConfig->PchSlpAMinAssert                     = PchSlpA2s;

  PmConfig->SlpLanLowDc                          = TRUE;
  PmConfig->PciePllSsc                           = 0xFF;
  PmConfig->CpuC10GatePinEnable                  = TRUE;
  PmConfig->OsIdleEnable                         = TRUE;

  if (IsPchLp ()) {
    PmConfig->ModPhySusPgEnable                  = TRUE;
  }
  PmConfig->S0ixAutoDemotion                     = TRUE;
  PmConfig->LpmS0ixSubStateEnable.Val            = 0xFF;

  PmConfig->Usb2PhySusPgEnable                   = TRUE;
  PmConfig->GrTscEnable                          = FALSE;
}

STATIC COMPONENT_BLOCK_ENTRY  mPmcBlocks = {
  &gPmConfigGuid,
  sizeof (PCH_PM_CONFIG),
  PM_CONFIG_REVISION,
  PmcLoadConfigDefault
};

/**
  Get Pmc config block table size.

  @retval      Size of config block
**/
UINT16
PmcGetConfigBlockTotalSize (
  VOID
  )
{
  return mPmcBlocks.Size;
}

/**
  Add Pmc ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
PmcAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mPmcBlocks, 1);
}

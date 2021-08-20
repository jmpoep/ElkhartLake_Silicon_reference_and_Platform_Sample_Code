/** @file
  This file provides services for Sata policy function

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
#include <Library/SataLib.h>
#include <Ppi/SiPolicy.h>
#include <SataConfig.h>

/**
  Print SATA_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
SataPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS    Status;
  SATA_CONFIG   *SataConfigPtr;
  SATA_CONFIG   *SataConfig;
  UINT32        SataCtrlIndex;
  UINT32        Index;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSataConfigGuid, (VOID *) &SataConfigPtr);
  ASSERT_EFI_ERROR (Status);

  for (SataCtrlIndex = 0; SataCtrlIndex < MaxSataControllerNum (); SataCtrlIndex++) {
    SataConfig = SataConfigPtr + SataCtrlIndex;

    DEBUG ((DEBUG_INFO, "--------------- SATA Config for controller %d -----------\n", SataCtrlIndex));
    DEBUG ((DEBUG_INFO, " Enable= %x\n", SataConfig->Enable));
    DEBUG ((DEBUG_INFO, " SataMode= %x\n", SataConfig->SataMode));

    for (Index = 0; Index < MaxSataPortNum (SataCtrlIndex); Index++) {
      DEBUG ((DEBUG_INFO, " PortSettings[%d] Enabled= %x\n", Index, SataConfig->PortSettings[Index].Enable));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] HotPlug= %x\n", Index, SataConfig->PortSettings[Index].HotPlug));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] InterlockSw= %x\n", Index, SataConfig->PortSettings[Index].InterlockSw));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] External= %x\n", Index, SataConfig->PortSettings[Index].External));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] SpinUp= %x\n", Index, SataConfig->PortSettings[Index].SpinUp));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] SolidStateDrive= %x\n", Index, SataConfig->PortSettings[Index].SolidStateDrive));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] DevSlp= %x\n", Index, SataConfig->PortSettings[Index].DevSlp));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] EnableDitoConfig= %x\n", Index, SataConfig->PortSettings[Index].EnableDitoConfig));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] DmVal= %x\n", Index, SataConfig->PortSettings[Index].DmVal));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] DitoVal= %x\n", Index, SataConfig->PortSettings[Index].DitoVal));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] ZpOdd= %x\n", Index, SataConfig->PortSettings[Index].ZpOdd));
      DEBUG ((DEBUG_INFO, " PortSettings[%d] RxPolarity= %x\n", Index, SataConfig->PortSettings[Index].RxPolarity));
    }

    DEBUG ((DEBUG_INFO, " SpeedSupport= %x\n", SataConfig->SpeedLimit));
    DEBUG ((DEBUG_INFO, " EsataSpeedLimit= %x\n", SataConfig->EsataSpeedLimit));
    DEBUG ((DEBUG_INFO, " LedEnable= %x\n", SataConfig->LedEnable));
    DEBUG ((DEBUG_INFO, " TestMode= %x\n", SataConfig->TestMode));
    DEBUG ((DEBUG_INFO, " PortMultiplier= %x\n", SataConfig->PortMultiplier));
    DEBUG ((DEBUG_INFO, " SalpSupport= %x\n", SataConfig->SalpSupport));
    DEBUG ((DEBUG_INFO, " PwrOptEnable= %x\n", SataConfig->PwrOptEnable));
    DEBUG ((DEBUG_INFO, " RaidDeviceId= %x\n", SataConfig->RaidDeviceId));
    DEBUG ((DEBUG_INFO, " SataRstInterrupt =  %x\n", SataConfig->SataRstInterrupt));

    DEBUG ((DEBUG_INFO, " ThermalThrottling P0T1M %x\n", SataConfig->ThermalThrottling.P0T1M));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P0T2M %x\n", SataConfig->ThermalThrottling.P0T2M));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P0T3M %x\n", SataConfig->ThermalThrottling.P0T3M));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P0TDisp %x\n", SataConfig->ThermalThrottling.P0TDisp));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P0Tinact %x\n", SataConfig->ThermalThrottling.P0Tinact));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P0TDispFinit %x\n", SataConfig->ThermalThrottling.P0TDispFinit));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P1T1M %x\n", SataConfig->ThermalThrottling.P1T1M));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P1T2M %x\n", SataConfig->ThermalThrottling.P1T2M));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P1T3M %x\n", SataConfig->ThermalThrottling.P1T3M));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P1TDisp %x\n", SataConfig->ThermalThrottling.P1TDisp));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P1Tinact %x\n", SataConfig->ThermalThrottling.P1Tinact));
    DEBUG ((DEBUG_INFO, " ThermalThrottling P1TDispFinit %x\n", SataConfig->ThermalThrottling.P1TDispFinit));
    DEBUG ((DEBUG_INFO, " ThermalThrottling SuggestedSetting %x\n", SataConfig->ThermalThrottling.SuggestedSetting));
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
SataLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINTN            PortIndex;
  UINT32           SataCtrlIndex;
  SATA_CONFIG      *SataConfig;

  SataConfig = (SATA_CONFIG *)ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "SataConfig->Header.GuidHob.Name = %g\n", &SataConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "SataConfig->Header.GuidHob.Header.HobLength = 0x%x\n", SataConfig->Header.GuidHob.Header.HobLength));

  for (SataCtrlIndex = 0; SataCtrlIndex < MaxSataControllerNum (); SataCtrlIndex++, SataConfig++) {
    /********************************
      SATA related settings
    ********************************/
    SataConfig->Enable               = TRUE;
    SataConfig->SalpSupport          = TRUE;
    SataConfig->PortMultiplier       = FALSE;
    SataConfig->SataMode             = SataModeAhci;

    for (PortIndex = 0; PortIndex < MaxSataPortNum (SataCtrlIndex); PortIndex++) {
      SataConfig->PortSettings[PortIndex].Enable           = TRUE;
      SataConfig->PortSettings[PortIndex].DmVal            = 15;
      SataConfig->PortSettings[PortIndex].DitoVal          = 625;
    }

    SataConfig->PwrOptEnable     = TRUE;
    SataConfig->ThermalThrottling.SuggestedSetting = TRUE;
  }
}

STATIC COMPONENT_BLOCK_ENTRY  mSataBlocks = {
  &gSataConfigGuid,
  sizeof (SATA_CONFIG),
  SATA_CONFIG_REVISION,
  SataLoadConfigDefault
};

/**
  Get Sata config block table size.

  @retval      Size of config block
**/
UINT16
SataGetConfigBlockTotalSize (
  VOID
  )
{
  return mSataBlocks.Size;
}

/**
  Add Sata ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
SataAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mSataBlocks, 1);
}

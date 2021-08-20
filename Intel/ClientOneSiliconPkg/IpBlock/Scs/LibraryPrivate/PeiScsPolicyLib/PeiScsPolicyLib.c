/** @file
  This file provides services for Scs policy function

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
#include <ScsConfig.h>

/**
  Print SCS_SDCARD_CONFIG to serial.

  @param[in] SiPolicyPpi  Pointer to SI_POLICY_PPI
**/
VOID
SdCardPrintConfig (
  IN SI_POLICY_PPI  *SiPolicyPpi
  )
{
  SCS_SDCARD_CONFIG  *SdCardConfig;
  EFI_STATUS         Status;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSdCardConfigGuid, (VOID *) &SdCardConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ SCS SdCard Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " Enable = %d\n", SdCardConfig->Enable));
  DEBUG ((DEBUG_INFO, " PowerEnableActiveHigh = %d\n", SdCardConfig->PowerEnableActiveHigh));
  DEBUG ((DEBUG_INFO, " Use tuned DLLs = %d\n", SdCardConfig->UseCustomDlls));
  if (SdCardConfig->UseCustomDlls) {
    DEBUG ((DEBUG_INFO, "  TxCmdDelayControl value = %X\n", SdCardConfig->CustomDllValues.TxCmdDelayControl));
    DEBUG ((DEBUG_INFO, "  TxDataDelayControl1 value = %X\n", SdCardConfig->CustomDllValues.TxDataDelayControl1));
    DEBUG ((DEBUG_INFO, "  TxDataDelayControl2 value = %X\n", SdCardConfig->CustomDllValues.TxDataDelayControl2));
    DEBUG ((DEBUG_INFO, "  RxCmdDataDelayControl1 value = %X\n", SdCardConfig->CustomDllValues.RxCmdDataDelayControl1));
    DEBUG ((DEBUG_INFO, "  RxCmdDataDelayControl2 value = %X\n", SdCardConfig->CustomDllValues.RxCmdDataDelayControl2));
  }
}

/**
  Print SCS_EMMC_CONFIG to serial.

  @param[in] SiPolicyPpi  Pointer to SI_POLICY_PPI
**/
VOID
EmmcPrintConfig (
  IN SI_POLICY_PPI  *SiPolicyPpi
  )
{
  SCS_EMMC_CONFIG  *EmmcConfig;
  EFI_STATUS       Status;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gEmmcConfigGuid, (VOID *) &EmmcConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ SCS eMMC Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " Enable = %d\n", EmmcConfig->Enable));
  DEBUG ((DEBUG_INFO, " HS400 Supported = %d\n", EmmcConfig->Hs400Supported));
  DEBUG ((DEBUG_INFO, " Use tuned DLLs = %d\n", EmmcConfig->UseCustomDlls));
  if (EmmcConfig->UseCustomDlls) {
    DEBUG ((DEBUG_INFO, "  TxCmdDelayControl value = %X\n", EmmcConfig->CustomDllValues.TxCmdDelayControl));
    DEBUG ((DEBUG_INFO, "  TxDataDelayControl1 value = %X\n", EmmcConfig->CustomDllValues.TxDataDelayControl1));
    DEBUG ((DEBUG_INFO, "  TxDataDelayControl2 value = %X\n", EmmcConfig->CustomDllValues.TxDataDelayControl2));
    DEBUG ((DEBUG_INFO, "  RxCmdDataDelayControl1 value = %X\n", EmmcConfig->CustomDllValues.RxCmdDataDelayControl1));
    DEBUG ((DEBUG_INFO, "  RxCmdDataDelayControl2 value = %X\n", EmmcConfig->CustomDllValues.RxCmdDataDelayControl2));
    DEBUG ((DEBUG_INFO, "  RxStrobeDelayControl value = %X\n", EmmcConfig->CustomDllValues.RxStrobeDelayControl));
  }
}

/**
  Print SCS_UFS_CONFIG to serial.

  @param[in] SiPolicyPpi  Pointer to SI_POLICY_PPI
**/
VOID
UfsPrintConfig (
  IN SI_POLICY_PPI  *SiPolicyPpi
  )
{
  SCS_UFS_CONFIG  *UfsConfig;
  EFI_STATUS      Status;
  UINT8           UfsIndex;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gUfsConfigGuid, (VOID *) &UfsConfig);
  ASSERT_EFI_ERROR (Status);

  for (UfsIndex = 0; UfsIndex < PchGetMaxUfsNum (); UfsIndex++) {
    DEBUG ((DEBUG_INFO, "------------------ SCS UFS%d Config ------------------\n", UfsIndex));
    DEBUG ((DEBUG_INFO, " Enable = %d\n", UfsConfig->UfsControllerConfig[UfsIndex].Enable));
  }
}

/**
  Print Scs configs and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
ScsPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  SdCardPrintConfig (SiPolicyPpi);
  EmmcPrintConfig (SiPolicyPpi);
  UfsPrintConfig (SiPolicyPpi);
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
SdCardLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  SCS_SDCARD_CONFIG  *SdCardConfig;

  SdCardConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "SdCardConfig->Header.GuidHob.Name = %g\n", &SdCardConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "SdCardConfig->Header.GuidHob.Header.HobLength = 0x%x\n", SdCardConfig->Header.GuidHob.Header.HobLength));

  SdCardConfig->Enable = IsPchSdCardSupported ();
  SdCardConfig->PowerEnableActiveHigh = TRUE;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
EmmcLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  SCS_EMMC_CONFIG  *EmmcConfig;

  EmmcConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "EmmcConfig->Header.GuidHob.Name = %g\n", &EmmcConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "EmmcConfig->Header.GuidHob.Header.HobLength = 0x%x\n", EmmcConfig->Header.GuidHob.Header.HobLength));
  EmmcConfig->Enable = IsPchEmmcSupported ();
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
UfsLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  SCS_UFS_CONFIG  *UfsConfig;
  UINT8           UfsIndex;

  UfsConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "UfsConfig->Header.GuidHob.Name = %g\n", &UfsConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "UfsConfig->Header.GuidHob.Header.HobLength = 0x%x\n", UfsConfig->Header.GuidHob.Header.HobLength));

  for (UfsIndex = 0; UfsIndex < PchGetMaxUfsNum (); UfsIndex++) {
    UfsConfig->UfsControllerConfig[UfsIndex].Enable = TRUE;
  }
}

STATIC COMPONENT_BLOCK_ENTRY  mScsBlocks [] = {
  {&gSdCardConfigGuid,  sizeof (SCS_SDCARD_CONFIG), SCS_SDCARD_CONFIG_REVISION, SdCardLoadConfigDefault},
  {&gEmmcConfigGuid,    sizeof (SCS_EMMC_CONFIG),   SCS_EMMC_CONFIG_REVISION,   EmmcLoadConfigDefault},
  {&gUfsConfigGuid,     sizeof (SCS_UFS_CONFIG),    SCS_UFS_CONFIG_REVISION,    UfsLoadConfigDefault}
};

/**
  Get Scs config block table size.

  @retval      Size of config block
**/
UINT16
ScsGetConfigBlockTotalSize (
  VOID
  )
{
  return GetComponentConfigBlockTotalSize (&mScsBlocks[0], sizeof (mScsBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  Add Scs ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
ScsAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mScsBlocks[0], sizeof (mScsBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

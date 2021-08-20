/** @file
  This file provides services for CNVi PEI policy function

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
#include <Library/GpioPrivateLib.h>
#include <Ppi/SiPolicy.h>
#include <CnviConfig.h>

/**
  Print CNVI_CONFIG settings.

  @param[in] SiPolicyPpi  Instance of SI_POLICY_PPI
**/
VOID
CnviPrintConfig (
  IN CONST SI_POLICY_PPI *SiPolicyPpi
  )
{
  EFI_STATUS  Status;
  CNVI_CONFIG *CnviConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gCnviConfigGuid, (VOID *) &CnviConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ CNVi Config ------------------\n"));
  DEBUG ((DEBUG_INFO, "CNVi Mode = %x\n", CnviConfig->Mode));
  DEBUG ((DEBUG_INFO, "BT Core = %x\n", CnviConfig->BtCore));
  DEBUG ((DEBUG_INFO, "BT Audio Offload = %x\n", CnviConfig->BtAudioOffload));
  DEBUG ((DEBUG_INFO, "Pin Muxing:\n"));
  DEBUG ((DEBUG_INFO, "  RF_RESET# = %a\n", GpioPinMuxName (CnviConfig->PinMux.RfReset)));
  DEBUG ((DEBUG_INFO, "  CLKREQ    = %a\n", GpioPinMuxName (CnviConfig->PinMux.Clkreq)));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer  Pointer to config block
**/
VOID
CnviLoadConfigDefault (
  IN VOID *ConfigBlockPointer
  )
{
  CNVI_CONFIG *CnviConfig;

  CnviConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "CnviConfig->Header.GuidHob.Name = %g\n", &CnviConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "CnviConfig->Header.GuidHob.Header.HobLength = 0x%x\n", CnviConfig->Header.GuidHob.Header.HobLength));

  /********************************
    Cnvi configuration.
  ********************************/
  CnviConfig->Mode   = CnviModeAuto; // Automatic detection
  CnviConfig->BtCore = TRUE;         // BT Core enabled
}

STATIC COMPONENT_BLOCK_ENTRY mCnviBlock = {
  &gCnviConfigGuid,
  sizeof (CNVI_CONFIG),
  CNVI_CONFIG_REVISION,
  CnviLoadConfigDefault
};

/**
  Get CNVi config block table size.

  @retval Size of config block
**/
UINT16
CnviGetConfigBlockTotalSize (
  VOID
  )
{
  return mCnviBlock.Size;
}

/**
  Add CNVi ConfigBlock.

  @param[in] ConfigBlockTableAddress The pointer to config block table

  @retval EFI_SUCCESS                The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES       Insufficient resources to create buffer
**/
EFI_STATUS
CnviAddConfigBlock (
  IN VOID *ConfigBlockTableAddress
  )
{
  EFI_STATUS Status;

  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mCnviBlock, 1);
  return Status;
}

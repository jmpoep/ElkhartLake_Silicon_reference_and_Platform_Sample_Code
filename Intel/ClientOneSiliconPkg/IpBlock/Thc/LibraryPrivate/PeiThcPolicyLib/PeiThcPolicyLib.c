/** @file
  This file provides services for Thc policy function

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
#include <ThcConfig.h>
#include <Library/GpioPrivateLib.h>

/**
  Print THC_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
ThcPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS    Status;
  THC_CONFIG    *ThcConfig;
  UINT8         Index;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gThcConfigGuid, (VOID *) &ThcConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ PCH Thc Config ------------------------\n"));
  DEBUG ((DEBUG_INFO, " THC ports: \n"));
  for (Index = 0; Index < GetPchMaxThcCount (); Index ++) {
    DEBUG ((DEBUG_INFO, " PORT%d Assignment: 0x%X\n", Index, ThcConfig->ThcPort[Index].Assignment));
    DEBUG ((DEBUG_INFO, " PORT%d Interrupt Pin Muxing: %a\n", Index, GpioPinMuxName (ThcConfig->ThcPort[Index].InterruptPinMuxing)));
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
ThcLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  THC_CONFIG  *ThcConfig;
  UINT8       Index;

  ThcConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "ThcConfig->Header.GuidHob.Name = %g\n", &ThcConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "ThcConfig->Header.GuidHob.Header.HobLength = 0x%x\n", ThcConfig->Header.GuidHob.Header.HobLength));
  for (Index = 0; Index < GetPchMaxThcCount (); Index ++) {
    ThcConfig->ThcPort[0].Assignment         = ThcAssignmentNone;
    ThcConfig->ThcPort[0].InterruptPinMuxing = 0;
  }
}

STATIC COMPONENT_BLOCK_ENTRY  mThcBlocks = {
  &gThcConfigGuid,
  sizeof (THC_CONFIG),
  THC_CONFIG_REVISION,
  ThcLoadConfigDefault
};

/**
  Get Thc config block table size.

  @retval      Size of config block
**/
UINT16
ThcGetConfigBlockTotalSize (
  VOID
  )
{
  return mThcBlocks.Size;
}

/**
  Add Thc ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
ThcAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mThcBlocks, 1);
}

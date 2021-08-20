/** @file
  This file provides services for RTC PEI policy function

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
#include <Ppi/SiPolicy.h>
#include <RtcConfig.h>

/**
  Print RTC_CONFIG settings.

  @param[in] SiPolicyPpi    Instance of SI_POLICY_PPI
**/
VOID
RtcPrintConfig (
  IN  SI_POLICY_PPI         *SiPolicyPpi
  )
{
  EFI_STATUS                Status;
  RTC_CONFIG                *RtcConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gRtcConfigGuid, (VOID *) &RtcConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ Rtc Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " BiosInterfaceLock = %x\n", RtcConfig->BiosInterfaceLock));
  DEBUG ((DEBUG_INFO, " MemoryLock = %x\n", RtcConfig->MemoryLock));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
RtcLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  RTC_CONFIG  *RtcConfig;
  RtcConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "RtcConfig->Header.GuidHob.Name = %g\n", &RtcConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "RtcConfig->Header.GuidHob.Header.HobLength = 0x%x\n", RtcConfig->Header.GuidHob.Header.HobLength));

  /********************************
    Rtc configuration.
  ********************************/
  RtcConfig->BiosInterfaceLock  = TRUE;
  RtcConfig->MemoryLock         = TRUE;
}

STATIC COMPONENT_BLOCK_ENTRY  mRtcBlocks = {
  &gRtcConfigGuid,
  sizeof (RTC_CONFIG),
  RTC_CONFIG_REVISION,
  RtcLoadConfigDefault
};

/**
  Get Rtc config block table size.

  @retval      Size of config block
**/
UINT16
RtcGetConfigBlockTotalSize (
  VOID
  )
{
  return mRtcBlocks.Size;
}

/**
  Add Rtc ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
RtcAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mRtcBlocks, 1);
  return Status;
}

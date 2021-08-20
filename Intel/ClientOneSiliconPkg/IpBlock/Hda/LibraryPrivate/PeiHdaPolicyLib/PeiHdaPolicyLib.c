/** @file
  This file provides services for Hda policy function

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include <HdAudioConfig.h>

/**
  Print HDAUDIO_CONFIG and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
HdaPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  EFI_STATUS        Status;
  HDAUDIO_CONFIG    *HdaConfig;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gHdAudioConfigGuid, (VOID *) &HdaConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ HDA Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " Pme                                            = %x\n", HdaConfig->Pme));
  DEBUG ((DEBUG_INFO, " Codec Sx Wake Capability                       = %x\n", HdaConfig->CodecSxWakeCapability));
  DEBUG ((DEBUG_INFO, " HD-A Link Frequency                            = %x\n", HdaConfig->HdAudioLinkFrequency));
  DEBUG ((DEBUG_INFO, " VerbTableEntryNum                              = %x\n", HdaConfig->VerbTableEntryNum));
  DEBUG ((DEBUG_INFO, " VerbTablePtr                                   = %x\n", HdaConfig->VerbTablePtr));
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
HdaLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  HDAUDIO_CONFIG   *HdaConfig;
  HdaConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "HdaConfig->Header.GuidHob.Name = %g\n", &HdaConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "HdaConfig->Header.GuidHob.Header.HobLength = 0x%x\n", HdaConfig->Header.GuidHob.Header.HobLength));
  /********************************
    HD-Audio configuration
  ********************************/
  HdaConfig->HdAudioLinkFrequency = HdaLinkFreq24MHz;
}

STATIC COMPONENT_BLOCK_ENTRY  mHdaBlocks = {
  &gHdAudioConfigGuid,
  sizeof (HDAUDIO_CONFIG),
  HDAUDIO_CONFIG_REVISION,
  HdaLoadConfigDefault
};

/**
  Get Hda config block table size.

  @retval      Size of config block
**/
UINT16
HdaGetConfigBlockTotalSize (
  VOID
  )
{
  return mHdaBlocks.Size;
}

/**
  Add Hda ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
HdaAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mHdaBlocks, 1);
}

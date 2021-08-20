/** @file
  This file provides services for Hda PreMem policy function

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
  Print PCH_HDAUDIO_PREMEM_CONFIG and serial out.

  @param[in] SiPreMemPolicyPpi            Pointer to a SI_PREMEM_POLICY_PPI
**/
VOID
HdaPreMemPrintConfig (
  IN SI_PREMEM_POLICY_PPI     *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                Status;
  HDAUDIO_PREMEM_CONFIG     *HdaPreMemConfig;
  UINTN                     Index;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gHdAudioPreMemConfigGuid, (VOID *) &HdaPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ HD Audio PreMem Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " Enable                                         = %x\n", HdaPreMemConfig->Enable));
  DEBUG ((DEBUG_INFO, " DSP Enable                                     = %x\n", HdaPreMemConfig->DspEnable));
  DEBUG ((DEBUG_INFO, " DSP UAA Compliance                             = %x\n", HdaPreMemConfig->DspUaaCompliance));
  DEBUG ((DEBUG_INFO, " Audio Link: HDA Link                           = %x\n", HdaPreMemConfig->AudioLinkHda.Enable));
  for (Index = 0; Index < GetPchHdaMaxDmicLinkNum (); Index++) {
    DEBUG ((DEBUG_INFO, " Audio Link: DMIC#%d                            = %x\n", Index, HdaPreMemConfig->AudioLinkDmic[Index].Enable));
  }
  for (Index = 0; Index < GetPchHdaMaxSspLinkNum (); Index++) {
    DEBUG ((DEBUG_INFO, " Audio Link: SSP#%d                             = %x\n", Index, HdaPreMemConfig->AudioLinkSsp[Index].Enable));
  }
  for (Index = 0; Index < GetPchHdaMaxSndwLinkNum (); Index++) {
    DEBUG ((DEBUG_INFO, " Audio Link: SoundWire#%d                       = %x\n", Index, HdaPreMemConfig->AudioLinkSndw[Index].Enable));
  }
  DEBUG ((DEBUG_INFO, " VC Type                                        = %x\n", HdaPreMemConfig->VcType));
  DEBUG ((DEBUG_INFO, " iDisp Codec Disconnect                         = %x\n", HdaPreMemConfig->IDispCodecDisconnect));
  DEBUG ((DEBUG_INFO, " iDisp Link Frequency                           = %x\n", HdaPreMemConfig->IDispLinkFrequency));
  DEBUG ((DEBUG_INFO, " iDisp Link T-Mode                              = %x\n", HdaPreMemConfig->IDispLinkTmode));
  DEBUG ((DEBUG_INFO, " ResetWaitTimer                                 = %x\n", HdaPreMemConfig->ResetWaitTimer));
  for (Index = 0; Index < PCH_MAX_HDA_SDI; Index++) {
    DEBUG ((DEBUG_INFO, " Hda Sdi%d Enable                              = %x\n", Index, HdaPreMemConfig->AudioLinkHda.SdiEnable[Index]));
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
HdaPreMemLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINTN                  Index;
  HDAUDIO_PREMEM_CONFIG  *HdaPreMemConfig;
  HdaPreMemConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "HdaPreMemConfig->Header.GuidHob.Name = %g\n", &HdaPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "HdaPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", HdaPreMemConfig->Header.GuidHob.Header.HobLength));
  HdaPreMemConfig->Enable                  = 1;
  HdaPreMemConfig->DspEnable               = TRUE;
  HdaPreMemConfig->AudioLinkHda.Enable     = TRUE;
  HdaPreMemConfig->AudioLinkDmic[0].Enable = TRUE;
  HdaPreMemConfig->AudioLinkDmic[1].Enable = TRUE;
  HdaPreMemConfig->AudioLinkSndw[0].Enable = TRUE;
  /********************************
    HD-Audio configuration
  ********************************/
  HdaPreMemConfig->IDispLinkFrequency   = HdaLinkFreq96MHz;
  for (Index = 0; Index < PCH_MAX_HDA_SDI; Index++) {
    HdaPreMemConfig->AudioLinkHda.SdiEnable[Index] = FALSE;
  }

  HdaPreMemConfig->IDispLinkTmode     = HdaIDispMode4T;
  HdaPreMemConfig->ResetWaitTimer          = 600; // Must be at least 521us (25 frames)
}


STATIC COMPONENT_BLOCK_ENTRY  mHdaPreMemBlocks = {
  &gHdAudioPreMemConfigGuid,
  sizeof (HDAUDIO_PREMEM_CONFIG),
  HDAUDIO_PREMEM_CONFIG_REVISION,
  HdaPreMemLoadConfigDefault
};

/**
  Get Hda config block table size.

  @retval      Size of config block
**/
UINT16
HdaPreMemGetConfigBlockTotalSize (
  VOID
  )
{
  return mHdaPreMemBlocks.Size;
}

/**
  Add Hda ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
HdaPreMemAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mHdaPreMemBlocks, 1);
}

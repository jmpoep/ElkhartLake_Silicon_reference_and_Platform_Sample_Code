/** @file
  This file is SampleCode of the library for Intel PCH PEI Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2020 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/PeiPchPolicyUpdate.h>
#include <Library/SiPolicyLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/HobLib.h>
#include <Guid/GlobalVariable.h>
#include <Library/PchInfoLib.h>
#include <Library/SataLib.h>
#include <Library/PchPcieRpLib.h>
#include <Library/DebugLib.h>
#include <Library/PchPolicyLib.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspmUpd.h>
#endif
#include <Pins/GpioPinsVer3.h>

//
// Sawtooth Peak
// Single SPD EEPROM at 0xA2 serves both C0D0 and C1D0 (LPDDR is 1DPC only)
//
#define DIMM_SMB_SPD_P0C0D0_STP 0xA2
#define DIMM_SMB_SPD_P0C0D1_STP 0xA0
#define DIMM_SMB_SPD_P0C1D0_STP 0xA2
#define DIMM_SMB_SPD_P0C1D1_STP 0xA0

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mSmbusSTPRsvdAddresses[] = {
  DIMM_SMB_SPD_P0C0D0_STP,
  DIMM_SMB_SPD_P0C0D1_STP,
  DIMM_SMB_SPD_P0C1D0_STP,
  DIMM_SMB_SPD_P0C1D1_STP
};

/**
  Update PCH General pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
  @param[in] PchSetup       Pointer to PCH_SETUP
**/
STATIC
VOID
UpdatePchGeneralPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  VOID                     *FspmUpd,
  IN  PCH_SETUP                *PchSetup
  )
{
  PCH_GENERAL_PREMEM_CONFIG       *PchGeneralPreMemConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPchGeneralPreMemConfigGuid, (VOID *) &PchGeneralPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PchGeneralPreMemConfig = NULL;
#endif

  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchPort80Route, PchGeneralPreMemConfig->Port80Route, PchSetup->IchPort80Route);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchMasterClockGating, PchGeneralPreMemConfig->PchMasterClockGating, PchSetup->PchMasterClockGating);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchMasterPowerGating, PchGeneralPreMemConfig->PchMasterPowerGating, PchSetup->PchMasterPowerGating);
}

/**
  Update DCI pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
  @param[in] PchSetup       Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateDciPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  VOID                     *FspmUpd,
  IN  PCH_SETUP                *PchSetup
  )
{
  PCH_DCI_PREMEM_CONFIG           *DciPreMemConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gDciPreMemConfigGuid, (VOID *) &DciPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  DciPreMemConfig = NULL;
#endif

  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DciEn,              DciPreMemConfig->DciEn,              PchSetup->DciEn);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DciDbcMode,         DciPreMemConfig->DciDbcMode,         PchSetup->DciDbcMode);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DciModphyPg,        DciPreMemConfig->DciModphyPg,        PchSetup->DciModphyPg);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.DciUsb3TypecUfpDbg, DciPreMemConfig->DciUsb3TypecUfpDbg, PchSetup->DciUsb3TypecUfpDbg);
}

/**
  Update Pch TraceHub pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
  @param[in] PchSetup       Pointer to PCH_SETUP
**/
STATIC
VOID
UpdatePchTraceHubPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  VOID                     *FspmUpd,
  IN  PCH_SETUP                *PchSetup
  )
{
  PCH_TRACE_HUB_PREMEM_CONFIG     *PchTraceHubPreMemConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPchTraceHubPreMemConfigGuid, (VOID *) &PchTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PchTraceHubPreMemConfig = NULL;
#endif

  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchTraceHubMode,        PchTraceHubPreMemConfig->TraceHub.EnableMode,  PchSetup->PchTraceHubMode);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchTraceHubMemReg0Size, PchTraceHubPreMemConfig->TraceHub.MemReg0Size, PchSetup->PchTraceHubMemReg0Size);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchTraceHubMemReg1Size, PchTraceHubPreMemConfig->TraceHub.MemReg1Size, PchSetup->PchTraceHubMemReg1Size);
}

/**
  Update Smbus pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
  @param[in] PchSetup       Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateSmbusPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  VOID                     *FspmUpd,
  IN  PCH_SETUP                *PchSetup
  )
{
  UINT8                           *SmBusReservedTable;
  UINT8                           SmBusReservedNum;
  PCH_SMBUS_PREMEM_CONFIG         *SmbusPreMemConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gSmbusPreMemConfigGuid, (VOID *) &SmbusPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  SmbusPreMemConfig = NULL;
#endif

  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.SmbusEnable,       SmbusPreMemConfig->Enable,         TRUE);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchSmbAlertEnable, SmbusPreMemConfig->SmbAlertEnable, PcdGetBool (PcdSmbusAlertEnable));

  SmBusReservedTable = NULL;
  SmBusReservedNum   = 0;
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchSmbusIoBase, SmbusPreMemConfig->SmbusIoBase, PcdGet16 (PcdSmbusBaseAddress));
  SmBusReservedTable = mSmbusSTPRsvdAddresses;
  SmBusReservedNum   = sizeof (mSmbusSTPRsvdAddresses);

  if (SmBusReservedTable != NULL) {
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchNumRsvdSmbusAddresses, SmbusPreMemConfig->NumRsvdSmbusAddresses, SmBusReservedNum);
#if FixedPcdGet8(PcdFspModeSelection) == 1
    ((FSPM_UPD *) FspmUpd)->FspmConfig.RsvdSmbusAddressTablePtr = (UINT32) SmBusReservedTable;
#else
    CopyMem (SmbusPreMemConfig->RsvdSmbusAddressTable, SmBusReservedTable, SmBusReservedNum);
#endif
  }
}

/**
  Update Lpc pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
  @param[in] PchSetup       Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateLpcPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  VOID                     *FspmUpd,
  IN  PCH_SETUP                *PchSetup
  )
{
  PCH_LPC_PREMEM_CONFIG           *LpcPreMemConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gLpcPreMemConfigGuid, (VOID *) &LpcPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  LpcPreMemConfig = NULL;
#endif

  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchLpcEnhancePort8xhDecoding, LpcPreMemConfig->EnhancePort8xhDecoding, PchSetup->EnhancePort8xhDecoding);
}

/**
  Update WatchDog pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
  @param[in] PchSetup       Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateWatchDogPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  VOID                     *FspmUpd,
  IN  PCH_SETUP                *PchSetup
  )
{
  PCH_WDT_PREMEM_CONFIG           *WatchDogPreMemConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gWatchDogPreMemConfigGuid, (VOID *) &WatchDogPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  WatchDogPreMemConfig = NULL;
#endif
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.WdtDisableAndLock, WatchDogPreMemConfig->DisableAndLock, !PchSetup->WdtEnable);
}

VOID
UpdatePcieClockInfo (
  PCH_PCIE_RP_PREMEM_CONFIG  *PcieRpPreMemConfig,
  IN VOID                    *FspmUpd,
  UINTN                      Index,
  UINT64                     Data
  )
{
  PCD64_BLOB Pcd64;

  Pcd64.Blob = Data;
  DEBUG ((DEBUG_INFO, "UpdatePcieClockInfo ClkIndex %x ClkUsage %x, Supported %x\n", Index, Pcd64.PcieClock.ClockUsage, Pcd64.PcieClock.ClkReqSupported));

  UPDATE_POLICY (((FSPM_UPD *)FspmUpd)->FspmConfig.PcieClkSrcUsage[Index], PcieRpPreMemConfig->PcieClock[Index].Usage, (UINT8)Pcd64.PcieClock.ClockUsage);
  UPDATE_POLICY (((FSPM_UPD *)FspmUpd)->FspmConfig.PcieClkSrcClkReq[Index], PcieRpPreMemConfig->PcieClock[Index].ClkReq, Pcd64.PcieClock.ClkReqSupported ? (UINT8)Index : 0xFF);
}

/**
  Update PcieRp pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
  @param[in] PchSetup       Pointer to PCH_SETUP
**/
STATIC
VOID
UpdatePcieRpPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  VOID                     *FspmUpd,
  IN  PCH_SETUP                *PchSetup,
  IN  SETUP_DATA               *SystemSetup
  )
{
  UINT32                          RpIndex;
  UINT32                          RpEnabledMask;
  PCH_PCIE_RP_PREMEM_CONFIG       *PcieRpPreMemConfig;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPcieRpPreMemConfigGuid, (VOID *) &PcieRpPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PcieRpPreMemConfig = NULL;
#endif

  GET_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PcieRpEnableMask, PcieRpPreMemConfig->RpEnabledMask, RpEnabledMask);

  for (RpIndex = 0; RpIndex < GetPchMaxPciePortNum (); RpIndex ++) {
    if (PchSetup->PcieRootPortEn[RpIndex]) {
      RpEnabledMask |=  (UINT32) (1 << RpIndex);
    } else {
      RpEnabledMask &= ~(UINT32) (1 << RpIndex);
    }
  }
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PcieRpEnableMask, PcieRpPreMemConfig->RpEnabledMask, RpEnabledMask);

  UpdatePcieClockInfo (PcieRpPreMemConfig, FspmUpd, 0, PcdGet64(PcdPcieClock0));
  UpdatePcieClockInfo (PcieRpPreMemConfig, FspmUpd, 1, PcdGet64(PcdPcieClock1));
  UpdatePcieClockInfo (PcieRpPreMemConfig, FspmUpd, 2, PcdGet64(PcdPcieClock2));
  UpdatePcieClockInfo (PcieRpPreMemConfig, FspmUpd, 3, PcdGet64(PcdPcieClock3));
  UpdatePcieClockInfo (PcieRpPreMemConfig, FspmUpd, 4, PcdGet64(PcdPcieClock4));
  UpdatePcieClockInfo (PcieRpPreMemConfig, FspmUpd, 5, PcdGet64(PcdPcieClock5));

  //Update Pcie clk src per board rework.
  if(SystemSetup->RVP1BoardWifiEnable) {
    DEBUG ((DEBUG_INFO, "Board rework F08 Enable\n"));
    UPDATE_POLICY (((FSPM_UPD *)FspmUpd)->FspmConfig.PcieClkSrcUsage[1], PcieRpPreMemConfig->PcieClock[1].Usage, (UINT8)(PCIE_PCH + 6));
    UPDATE_POLICY (((FSPM_UPD *)FspmUpd)->FspmConfig.PcieClkSrcUsage[3], PcieRpPreMemConfig->PcieClock[3].Usage, (UINT8)PCH_PCIE_NO_SUCH_CLOCK);
  }

  for (RpIndex = 0; RpIndex < GetPchMaxPcieClockNum(); RpIndex++) {
    if (PchSetup->PchPcieClkReqSupport[RpIndex] == 0xFF) {
      UPDATE_POLICY (((FSPM_UPD *)FspmUpd)->FspmConfig.PcieClkSrcClkReq[RpIndex], PcieRpPreMemConfig->PcieClock[RpIndex].ClkReq, (UINT8)PCH_PCIE_NO_SUCH_CLOCK);
    }
    if (PchSetup->PchPcieClockUsageOverride[RpIndex] == 1) {
      UPDATE_POLICY (((FSPM_UPD *)FspmUpd)->FspmConfig.PcieClkSrcUsage[RpIndex], PcieRpPreMemConfig->PcieClock[RpIndex].Usage, PchClockUsageUnspecified);
    } else if (PchSetup->PchPcieClockUsageOverride[RpIndex] == 2) {
      UPDATE_POLICY (((FSPM_UPD *)FspmUpd)->FspmConfig.PcieClkSrcUsage[RpIndex], PcieRpPreMemConfig->PcieClock[RpIndex].Usage, PchClockUsageNotUsed);
    }
  }

}

/**
  Update HD Audio pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
  @param[in] PchSetup       Pointer to PCH_SETUP
**/
STATIC
VOID
UpdateHdaPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  VOID                     *FspmUpd,
  IN  PCH_SETUP                *PchSetup
  )
{
  HDAUDIO_PREMEM_CONFIG           *HdaPreMemConfig;
  UINTN                           Index;
#if FixedPcdGet8(PcdFspModeSelection) == 0
  EFI_STATUS                      Status;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHdAudioPreMemConfigGuid, (VOID *) &HdaPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  HdaPreMemConfig = NULL;
#endif
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaEnable,                   HdaPreMemConfig->Enable,                 PchSetup->PchHdAudio);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaDspEnable,                HdaPreMemConfig->DspEnable,              PchSetup->PchHdAudioDsp);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaIDispLinkFrequency,       HdaPreMemConfig->IDispLinkFrequency,     PchSetup->PchHdaIDisplayLinkFreq);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaIDispLinkTmode,           HdaPreMemConfig->IDispLinkTmode,         PchSetup->PchHdaIDisplayLinkTmode);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaIDispCodecDisconnect,     HdaPreMemConfig->IDispCodecDisconnect,   PchSetup->PchHdaIDisplayCodecDisconnect);

  switch (PchSetup->PchHdAudioLinkMode) {
    case HDAUDIO_LINK_MODE_HDA:
      DEBUG ((DEBUG_INFO, "HDA Policy: HD Audio Link Mode\n"));
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkHdaEnable,   HdaPreMemConfig->AudioLinkHda.Enable,     TRUE);
      for (Index = 0; Index < GetPchHdaMaxDmicLinkNum (); Index++) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicEnable[Index], HdaPreMemConfig->AudioLinkDmic[Index].Enable, TRUE);
      }
      // Override default policy setting (PeiPchPolicyLib) due to conflict between Hda and Sndw0
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkSndwEnable[0], HdaPreMemConfig->AudioLinkSndw[0].Enable, FALSE);
      break;
    case HDAUDIO_LINK_MODE_I2S_SSP:
      DEBUG ((DEBUG_INFO, "HDA Policy: SSP/I2S Link Mode\n"));
      // Only enable SSP0 because other SSP pin overlapping pin with other function
      for (Index = 0; Index < GetPchHdaMaxSspLinkNum (); Index++) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkSspEnable[Index],   HdaPreMemConfig->AudioLinkSsp[Index].Enable,  FALSE);
      }
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkSspEnable[0],   HdaPreMemConfig->AudioLinkSsp[0].Enable,  TRUE);
      for (Index = 0; Index < GetPchHdaMaxDmicLinkNum (); Index++) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicEnable[Index],  HdaPreMemConfig->AudioLinkDmic[Index].Enable, TRUE);
      }
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkSndwEnable[0],  HdaPreMemConfig->AudioLinkSndw[0].Enable, TRUE);
      // Override default policy setting (PeiPchPolicyLib) due to conflict between Hda and Ssp0 links
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkHdaEnable,    HdaPreMemConfig->AudioLinkHda.Enable,     FALSE);
      break;
    case HDAUDIO_LINK_MODE_SNDW:
      DEBUG ((DEBUG_INFO, "HDA Policy: SoundWire Link Mode\n"));
      // Override default policy setting (PeiPchPolicyLib) due to conflict between Hda and Sndw0
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkHdaEnable,     HdaPreMemConfig->AudioLinkHda.Enable,     FALSE);
      for (Index = 0; Index < GetPchHdaMaxSndwLinkNum (); Index++) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkSndwEnable[Index], HdaPreMemConfig->AudioLinkSndw[Index].Enable, TRUE);
      }
      // Override default policy setting (PeiPchPolicyLib) due to conflict between Hda and Dmic0/1 with Sndw4/3
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkHdaEnable,     HdaPreMemConfig->AudioLinkHda.Enable,     FALSE);
      for (Index = 0; Index < GetPchHdaMaxDmicLinkNum (); Index++) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicEnable[Index],   HdaPreMemConfig->AudioLinkDmic[Index].Enable, FALSE);
      }
      break;
    case HDAUDIO_LINK_MODE_ADVANCED:
      DEBUG ((DEBUG_INFO, "HDA Policy: Advanced Link Mode Configuration\n"));
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkHdaEnable,   HdaPreMemConfig->AudioLinkHda.Enable,     PchSetup->PchHdAudioHdaLinkEnable);
      for (Index = 0; Index < GetPchHdaMaxSdiNum (); Index++) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaSdiEnable[Index], HdaPreMemConfig->AudioLinkHda.SdiEnable[Index], PchSetup->PchHdAudioHdaSdiEnable[Index]);
      }
      for (Index = 0; Index < GetPchHdaMaxDmicLinkNum (); Index++) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicEnable[Index], HdaPreMemConfig->AudioLinkDmic[Index].Enable, PchSetup->PchHdAudioDmicLinkEnable[Index]);
      }
      for (Index = 0; Index < GetPchHdaMaxSspLinkNum (); Index++) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkSspEnable[Index],  HdaPreMemConfig->AudioLinkSsp[Index].Enable,  PchSetup->PchHdAudioSspLinkEnable[Index]);
      }
      for (Index = 0; Index < GetPchHdaMaxSndwLinkNum (); Index++) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkSndwEnable[Index], HdaPreMemConfig->AudioLinkSndw[Index].Enable, PchSetup->PchHdAudioSndwLinkEnable[Index]);
      }
      break;
    default:
      DEBUG ((DEBUG_INFO, "HDA Policy Default: HD Audio Link Mode\n"));
      UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkHdaEnable,   HdaPreMemConfig->AudioLinkHda.Enable,     TRUE);
      for (Index = 0; Index < GetPchHdaMaxDmicLinkNum (); Index++) {
        UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicEnable[Index], HdaPreMemConfig->AudioLinkDmic[Index].Enable, TRUE);
      }
      break;
  }

  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicClkAPinMux[0], HdaPreMemConfig->AudioLinkDmic[0].PinMux.ClkA, GPIO_VER3_MUXING_DMIC0_CLKA_GPP_R6);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicClkBPinMux[0], HdaPreMemConfig->AudioLinkDmic[0].PinMux.ClkB, GPIO_VER3_MUXING_DMIC0_CLKB_GPP_G13);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicDataPinMux[0], HdaPreMemConfig->AudioLinkDmic[0].PinMux.Data, GPIO_VER3_MUXING_DMIC0_DATA_GPP_R7);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicClkAPinMux[1], HdaPreMemConfig->AudioLinkDmic[1].PinMux.ClkA, GPIO_VER3_MUXING_DMIC1_CLKA_GPP_R4);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicClkBPinMux[1], HdaPreMemConfig->AudioLinkDmic[1].PinMux.ClkB, GPIO_VER3_MUXING_DMIC1_CLKB_GPP_G14);
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchHdaAudioLinkDmicDataPinMux[1], HdaPreMemConfig->AudioLinkDmic[1].PinMux.Data, GPIO_VER3_MUXING_DMIC1_DATA_GPP_R5);
}

/**
  Update PSE pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
  @param[in] PchSetup       Pointer to PCH_SETUP
**/
STATIC
VOID
UpdatePsePreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  VOID                     *FspmUpd,
  IN  PCH_SETUP                *PchSetup
  )
{
  PSE_PREMEM_CONFIG               *PsePreMemConfig;
#if FixedPcdGetBool(PcdFspWrapperEnable) == 0
  EFI_STATUS                      Status;
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPsePreMemConfigGuid, (VOID *) &PsePreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
#else
  PsePreMemConfig = NULL;
#endif
  UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.PchPseEnable, PsePreMemConfig->Enable, PchSetup->PchPseEnable);
}

/**
  This function performs PCH PEI Policy initialization.

  @retval EFI_SUCCESS             The PPI is installed and initialized.
  @retval EFI ERRORS              The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
UpdatePeiPchPolicyPreMem (
  VOID
  )
{
  EFI_STATUS                      Status;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
  UINTN                           VariableSize;
  PCH_SETUP                       PchSetup;
  SETUP_DATA                      SetupVariables;
  VOID                            *FspmUpd;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicy;
  DEBUG ((DEBUG_INFO, "Update PeiPchPolicyUpdate Pre-Mem Start\n"));
  FspmUpd        = NULL;
  SiPreMemPolicy = NULL;

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = (FSPM_UPD *) PcdGet32 (PcdFspmUpdDataAddress);
  ASSERT (FspmUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }
#endif

  //
  // Retrieve Setup variable
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid, // GUID
             0,                                // INSTANCE
             NULL,                             // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &VariableServices       // PPI
             );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SETUP_DATA);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"Setup",
                               &gSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &SetupVariables
                               );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (PCH_SETUP);
  Status = VariableServices->GetVariable (
                               VariableServices,
                               L"PchSetup",
                               &gPchSetupVariableGuid,
                               NULL,
                               &VariableSize,
                               &PchSetup
                               );
  ASSERT_EFI_ERROR (Status);

  UpdatePchGeneralPreMemPolicy (SiPreMemPolicy, FspmUpd, &PchSetup);
  UpdateDciPreMemPolicy (SiPreMemPolicy, FspmUpd, &PchSetup);
  UpdatePchTraceHubPreMemPolicy (SiPreMemPolicy, FspmUpd, &PchSetup);
  UpdateSmbusPreMemPolicy (SiPreMemPolicy, FspmUpd, &PchSetup);
  UpdateLpcPreMemPolicy (SiPreMemPolicy, FspmUpd, &PchSetup);
  UpdateWatchDogPreMemPolicy (SiPreMemPolicy, FspmUpd, &PchSetup);
  UpdatePcieRpPreMemPolicy (SiPreMemPolicy, FspmUpd, &PchSetup,&SetupVariables);
  UpdateHdaPreMemPolicy (SiPreMemPolicy, FspmUpd, &PchSetup);

  return EFI_SUCCESS;
}

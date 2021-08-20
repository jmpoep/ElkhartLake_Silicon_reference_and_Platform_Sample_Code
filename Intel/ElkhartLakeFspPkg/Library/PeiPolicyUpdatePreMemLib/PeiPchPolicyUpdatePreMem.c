/** @file
  This file is SampleCode of the library for Intel PCH PEI Policy initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#include <Ppi/SiPolicy.h>
#include <Library/FspCommonLib.h>
#include <Library/ConfigBlockLib.h>
#include <FspmUpd.h>
#include <Library/PchInfoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

/**
  Update PchTraceHub pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdatePchTraceHubPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  EFI_STATUS                      Status;
  PCH_TRACE_HUB_PREMEM_CONFIG     *PchTraceHubPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPchTraceHubPreMemConfigGuid, (VOID *) &PchTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  if (EFI_ERROR (Status)) {
    return;
  }


  PchTraceHubPreMemConfig->TraceHub.EnableMode  = FspmUpd->FspmConfig.PchTraceHubMode;
  PchTraceHubPreMemConfig->TraceHub.MemReg0Size = FspmUpd->FspmConfig.PchTraceHubMemReg0Size;
  PchTraceHubPreMemConfig->TraceHub.MemReg1Size = FspmUpd->FspmConfig.PchTraceHubMemReg1Size;
}

/**
  Update Smbus pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdateSmbusPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  UINT8                           NumRsvdSmbusTable;
  UINT8                           *RsvdSmbusTable;
  EFI_STATUS                      Status;
  PCH_SMBUS_PREMEM_CONFIG         *SmbusPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gSmbusPreMemConfigGuid, (VOID *) &SmbusPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  SmbusPreMemConfig->Enable                = FspmUpd->FspmConfig.SmbusEnable;
  SmbusPreMemConfig->ArpEnable             = FspmUpd->FspmConfig.SmbusArpEnable;
  SmbusPreMemConfig->DynamicPowerGating    = FspmUpd->FspmConfig.SmbusDynamicPowerGating;
  SmbusPreMemConfig->SpdWriteDisable       = FspmUpd->FspmConfig.SmbusSpdWriteDisable;
  SmbusPreMemConfig->SmbAlertEnable        = FspmUpd->FspmConfig.PchSmbAlertEnable;
  SmbusPreMemConfig->SmbusIoBase           = FspmUpd->FspmConfig.PchSmbusIoBase;
  SmbusPreMemConfig->NumRsvdSmbusAddresses = FspmUpd->FspmConfig.PchNumRsvdSmbusAddresses;

  if (FspmUpd->FspmConfig.PchNumRsvdSmbusAddresses != 0) {
    NumRsvdSmbusTable = FspmUpd->FspmConfig.PchNumRsvdSmbusAddresses;
    RsvdSmbusTable = (UINT8 *)FspmUpd->FspmConfig.RsvdSmbusAddressTablePtr;
    ZeroMem (
      SmbusPreMemConfig->RsvdSmbusAddressTable,
      PCH_MAX_SMBUS_RESERVED_ADDRESS * sizeof (UINT8)
      );
    CopyMem (
      SmbusPreMemConfig->RsvdSmbusAddressTable,
      RsvdSmbusTable,
      NumRsvdSmbusTable * sizeof (UINT8)
      );
  }
}

/**
  Update Dci pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdatePeiDciPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  EFI_STATUS                      Status;
  PCH_DCI_PREMEM_CONFIG           *DciPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gDciPreMemConfigGuid, (VOID *) &DciPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  DciPreMemConfig->DciEn              = FspmUpd->FspmConfig.DciEn;
  DciPreMemConfig->DciDbcMode         = FspmUpd->FspmConfig.DciDbcMode;
  DciPreMemConfig->DciModphyPg        = FspmUpd->FspmConfig.DciModphyPg;
  DciPreMemConfig->DciUsb3TypecUfpDbg = FspmUpd->FspmConfig.DciUsb3TypecUfpDbg;
}

/**
  Update PCIe Root Port pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdatePcieRpPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  EFI_STATUS                      Status;
  PCH_PCIE_RP_PREMEM_CONFIG       *PcieRpPreMemConfig;
  UINTN                           MaxPcieRootPorts;
  UINTN                           Index;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPcieRpPreMemConfigGuid, (VOID *) &PcieRpPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  MaxPcieRootPorts = GetPchMaxPciePortNum ();
  PcieRpPreMemConfig->RpEnabledMask = FspmUpd->FspmConfig.PcieRpEnableMask & ((1 << MaxPcieRootPorts) - 1);
  for (Index = 0; Index < GetPchMaxPcieClockNum (); Index ++) {
    PcieRpPreMemConfig->PcieClock[Index].Usage = FspmUpd->FspmConfig.PcieClkSrcUsage[Index];
    PcieRpPreMemConfig->PcieClock[Index].ClkReq = FspmUpd->FspmConfig.PcieClkSrcClkReq[Index];
  }
}

/**
  Update HsioPcie pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdateHsioPciePreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  UINTN                           Index;
  EFI_STATUS                      Status;
  PCH_HSIO_PCIE_PREMEM_CONFIG     *HsioPciePreMemConfig;
  UINTN                           MaxPcieRootPorts;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHsioPciePreMemConfigGuid, (VOID *) &HsioPciePreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  MaxPcieRootPorts = GetPchMaxPciePortNum ();
  for (Index = 0; Index < MaxPcieRootPorts; Index ++) {
    HsioPciePreMemConfig->Lane[Index].HsioRxSetCtleEnable           = FspmUpd->FspmConfig.PchPcieHsioRxSetCtleEnable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioRxSetCtle                 = FspmUpd->FspmConfig.PchPcieHsioRxSetCtle[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmpEnable  = FspmUpd->FspmConfig.PchPcieHsioTxGen1DownscaleAmpEnable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen1DownscaleAmp        = FspmUpd->FspmConfig.PchPcieHsioTxGen1DownscaleAmp[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmpEnable  = FspmUpd->FspmConfig.PchPcieHsioTxGen2DownscaleAmpEnable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DownscaleAmp        = FspmUpd->FspmConfig.PchPcieHsioTxGen2DownscaleAmp[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmpEnable  = FspmUpd->FspmConfig.PchPcieHsioTxGen3DownscaleAmpEnable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen3DownscaleAmp        = FspmUpd->FspmConfig.PchPcieHsioTxGen3DownscaleAmp[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmphEnable        = FspmUpd->FspmConfig.PchPcieHsioTxGen1DeEmphEnable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen1DeEmph              = FspmUpd->FspmConfig.PchPcieHsioTxGen1DeEmph[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5Enable     = FspmUpd->FspmConfig.PchPcieHsioTxGen2DeEmph3p5Enable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph3p5           = FspmUpd->FspmConfig.PchPcieHsioTxGen2DeEmph3p5[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph6p0Enable     = FspmUpd->FspmConfig.PchPcieHsioTxGen2DeEmph6p0Enable[Index];
    HsioPciePreMemConfig->Lane[Index].HsioTxGen2DeEmph6p0           = FspmUpd->FspmConfig.PchPcieHsioTxGen2DeEmph6p0[Index];
  }
}

/**
  Update HsioSata pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdateHsioSataPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  UINTN                           Index;
  EFI_STATUS                      Status;
  PCH_HSIO_SATA_PREMEM_CONFIG     *HsioSataPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHsioSataPreMemConfigGuid, (VOID *) &HsioSataPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  for (Index = 0; Index < PCH_MAX_SATA_PORTS; Index ++) {
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMagEnable    = FspmUpd->FspmConfig.PchSataHsioRxGen1EqBoostMagEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen1EqBoostMag          = FspmUpd->FspmConfig.PchSataHsioRxGen1EqBoostMag[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMagEnable    = FspmUpd->FspmConfig.PchSataHsioRxGen2EqBoostMagEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen2EqBoostMag          = FspmUpd->FspmConfig.PchSataHsioRxGen2EqBoostMag[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen3EqBoostMagEnable    = FspmUpd->FspmConfig.PchSataHsioRxGen3EqBoostMagEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioRxGen3EqBoostMag          = FspmUpd->FspmConfig.PchSataHsioRxGen3EqBoostMag[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmpEnable  = FspmUpd->FspmConfig.PchSataHsioTxGen1DownscaleAmpEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DownscaleAmp        = FspmUpd->FspmConfig.PchSataHsioTxGen1DownscaleAmp[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmpEnable  = FspmUpd->FspmConfig.PchSataHsioTxGen2DownscaleAmpEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DownscaleAmp        = FspmUpd->FspmConfig.PchSataHsioTxGen2DownscaleAmp[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmpEnable  = FspmUpd->FspmConfig.PchSataHsioTxGen3DownscaleAmpEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DownscaleAmp        = FspmUpd->FspmConfig.PchSataHsioTxGen3DownscaleAmp[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmphEnable        = FspmUpd->FspmConfig.PchSataHsioTxGen1DeEmphEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen1DeEmph              = FspmUpd->FspmConfig.PchSataHsioTxGen1DeEmph[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmphEnable        = FspmUpd->FspmConfig.PchSataHsioTxGen2DeEmphEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen2DeEmph              = FspmUpd->FspmConfig.PchSataHsioTxGen2DeEmph[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmphEnable        = FspmUpd->FspmConfig.PchSataHsioTxGen3DeEmphEnable[Index];
    HsioSataPreMemConfig->PortLane[Index].HsioTxGen3DeEmph              = FspmUpd->FspmConfig.PchSataHsioTxGen3DeEmph[Index];
  }
}

/**
  Update Lpc pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdateLpcPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  EFI_STATUS                      Status;
  PCH_LPC_PREMEM_CONFIG           *LpcPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gLpcPreMemConfigGuid, (VOID *) &LpcPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  LpcPreMemConfig->EnhancePort8xhDecoding = FspmUpd->FspmConfig.PchLpcEnhancePort8xhDecoding;
}

/**
  Update PCH General pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdatePchGeneralPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  EFI_STATUS                      Status;
  PCH_GENERAL_PREMEM_CONFIG       *PchGeneralPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPchGeneralPreMemConfigGuid, (VOID *) &PchGeneralPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  PchGeneralPreMemConfig->Port80Route = FspmUpd->FspmConfig.PchPort80Route;
  PchGeneralPreMemConfig->PchMasterClockGating = FspmUpd->FspmConfig.PchMasterClockGating;
  PchGeneralPreMemConfig->PchMasterPowerGating = FspmUpd->FspmConfig.PchMasterPowerGating;
}

/**
  Update WatchDog pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdateWdtPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  EFI_STATUS                      Status;
  PCH_WDT_PREMEM_CONFIG           *WdtPreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gWatchDogPreMemConfigGuid, (VOID *) &WdtPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  WdtPreMemConfig->DisableAndLock = FspmUpd->FspmConfig.WdtDisableAndLock;
}

/**
  Update HD Audio pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdateHdaPreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  EFI_STATUS                      Status;
  HDAUDIO_PREMEM_CONFIG           *HdaPreMemConfig;
  UINTN                           Index;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHdAudioPreMemConfigGuid, (VOID *) &HdaPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  HdaPreMemConfig->Enable                = FspmUpd->FspmConfig.PchHdaEnable;
  HdaPreMemConfig->DspEnable             = FspmUpd->FspmConfig.PchHdaDspEnable;
  HdaPreMemConfig->VcType                = FspmUpd->FspmConfig.PchHdaVcType;
  HdaPreMemConfig->DspUaaCompliance      = FspmUpd->FspmConfig.PchHdaDspUaaCompliance;
  HdaPreMemConfig->AudioLinkHda.Enable   = FspmUpd->FspmConfig.PchHdaAudioLinkHdaEnable;

  for (Index = 0; Index < PCH_MAX_HDA_SDI; Index++) {
    HdaPreMemConfig->AudioLinkHda.SdiEnable[Index] = FspmUpd->FspmConfig.PchHdaSdiEnable[Index];
  }

  for (Index = 0; Index < PCH_MAX_HDA_DMIC_LINK_NUM; Index++) {
    HdaPreMemConfig->AudioLinkDmic[Index].Enable      = FspmUpd->FspmConfig.PchHdaAudioLinkDmicEnable[Index];
    HdaPreMemConfig->AudioLinkDmic[Index].PinMux.ClkA = FspmUpd->FspmConfig.PchHdaAudioLinkDmicClkAPinMux[Index];
    HdaPreMemConfig->AudioLinkDmic[Index].PinMux.ClkB = FspmUpd->FspmConfig.PchHdaAudioLinkDmicClkBPinMux[Index];
    HdaPreMemConfig->AudioLinkDmic[Index].PinMux.Data = FspmUpd->FspmConfig.PchHdaAudioLinkDmicDataPinMux[Index];
  }

  for (Index = 0; Index < PCH_MAX_HDA_SSP_LINK_NUM; Index++ ){
    HdaPreMemConfig->AudioLinkSsp[Index].Enable = FspmUpd->FspmConfig.PchHdaAudioLinkSspEnable[Index];
  }

  for (Index = 0; Index < PCH_MAX_HDA_SNDW_LINK_NUM; Index++) {
    HdaPreMemConfig->AudioLinkSndw[Index].Enable = FspmUpd->FspmConfig.PchHdaAudioLinkSndwEnable[Index];
  }
  HdaPreMemConfig->IDispLinkFrequency    = FspmUpd->FspmConfig.PchHdaIDispLinkFrequency;
  HdaPreMemConfig->IDispLinkTmode        = FspmUpd->FspmConfig.PchHdaIDispLinkTmode;
  HdaPreMemConfig->IDispCodecDisconnect  = FspmUpd->FspmConfig.PchHdaIDispCodecDisconnect;
}


/**
  Update PSE pre mem policies.

  @param[in] SiPreMemPolicy Pointer to SI_PREMEM_POLICY_PPI
  @param[in] FspsUpm        Pointer to FSPM_UPD
**/
STATIC
VOID
FspUpdatePsePreMemPolicy (
  IN  SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN  FSPM_UPD                 *FspmUpd
  )
{
  EFI_STATUS                      Status;
  PSE_PREMEM_CONFIG               *PsePreMemConfig;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPsePreMemConfigGuid, (VOID *) &PsePreMemConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  PsePreMemConfig->Enable = FspmUpd->FspmConfig.PchPseEnable;
}

/**
  This function performs PCH PEI Policy update in pre-memory.

  @param[in, out] SiPreMemPolicy  The SI PreMem Policy PPI instance
  @param[in]      FspmUpd         The pointer of MemoryInitUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiPchPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN     FSPM_UPD                 *FspmUpd
  )
{
  FspUpdatePeiDciPreMemPolicy (SiPreMemPolicy, FspmUpd);
  FspUpdatePchTraceHubPreMemPolicy (SiPreMemPolicy, FspmUpd);
  FspUpdateSmbusPreMemPolicy (SiPreMemPolicy, FspmUpd);
  FspUpdatePcieRpPreMemPolicy (SiPreMemPolicy, FspmUpd);
  FspUpdateHsioPciePreMemPolicy (SiPreMemPolicy, FspmUpd);
  FspUpdateHsioSataPreMemPolicy (SiPreMemPolicy, FspmUpd);
  FspUpdateLpcPreMemPolicy (SiPreMemPolicy, FspmUpd);
  FspUpdatePchGeneralPreMemPolicy (SiPreMemPolicy, FspmUpd);
  FspUpdateWdtPreMemPolicy (SiPreMemPolicy, FspmUpd);
  FspUpdateHdaPreMemPolicy (SiPreMemPolicy, FspmUpd);
  FspUpdatePsePreMemPolicy (SiPreMemPolicy, FspmUpd);

  return EFI_SUCCESS;
}

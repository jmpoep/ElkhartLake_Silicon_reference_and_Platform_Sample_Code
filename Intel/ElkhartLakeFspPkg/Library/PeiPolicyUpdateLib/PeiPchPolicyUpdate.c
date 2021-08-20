/** @file
  This file is SampleCode of the library for Intel PCH PEI Policy initialization.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2020 Intel Corporation.

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

#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/FspCommonLib.h>
#include <FspsUpd.h>
#include <Library/PchInfoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/SataLib.h>
#include <Library/PchPolicyLib.h>

/**
  Update GBE policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateGbePolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  GBE_CONFIG        *GbeConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gGbeConfigGuid, (VOID *) &GbeConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  GbeConfig->Enable          = FspsUpd->FspsConfig.PchLanEnable;
  GbeConfig->LtrEnable       = FspsUpd->FspsConfig.PchLanLtrEnable;
}
/**
  Update SIIP policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateSiipPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  SIIP_CONFIG       *SiipConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSiipConfigGuid, (VOID *) &SiipConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  SiipConfig->BaseAddress = FspsUpd->FspsConfig.SiipRegionBase;
  SiipConfig->Size        = FspsUpd->FspsConfig.SiipRegionSize;
}
/**
  Update TSN policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateTsnPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  TSN_CONFIG        *TsnConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gTsnConfigGuid, (VOID *) &TsnConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  TsnConfig->TsnSubRegion[0].BaseAddress       = FspsUpd->FspsConfig.TsnMacAddrBase;
  TsnConfig->TsnSubRegion[0].Size              = FspsUpd->FspsConfig.TsnMacAddrSize;
  TsnConfig->TsnSubRegion[1].BaseAddress       = FspsUpd->FspsConfig.PseTsnIpConfigBase;
  TsnConfig->TsnSubRegion[1].Size              = FspsUpd->FspsConfig.PseTsnIpConfigSize;
  TsnConfig->TsnSubRegion[2].BaseAddress       = FspsUpd->FspsConfig.TsnConfigBase;
  TsnConfig->TsnSubRegion[2].Size              = FspsUpd->FspsConfig.TsnConfigSize;
  TsnConfig->PchTsnEnable                      = FspsUpd->FspsConfig.PchTsnEnable;
  TsnConfig->PchTsnGbeMultiVcEnable            = FspsUpd->FspsConfig.PchTsnGbeMultiVcEnable;
  TsnConfig->PchTsnGbeLinkSpeed                = FspsUpd->FspsConfig.PchTsnGbeLinkSpeed;
  TsnConfig->PchTsnGbeSgmiiEnable              = FspsUpd->FspsConfig.PchTsnGbeSgmiiEnable;
  TsnConfig->PseTsnGbeMultiVcEnable[0]         = FspsUpd->FspsConfig.PseTsnGbeMultiVcEnable[0];
  TsnConfig->PseTsnGbeLinkSpeed[0]             = FspsUpd->FspsConfig.PseTsnGbeLinkSpeed[0];
  TsnConfig->PseTsnGbeSgmiiEnable[0]           = FspsUpd->FspsConfig.PseTsnGbeSgmiiEnable[0];
  TsnConfig->PseTsnGbeMultiVcEnable[1]         = FspsUpd->FspsConfig.PseTsnGbeMultiVcEnable[1];
  TsnConfig->PseTsnGbeLinkSpeed[1]             = FspsUpd->FspsConfig.PseTsnGbeLinkSpeed[1];
  TsnConfig->PseTsnGbeSgmiiEnable[1]           = FspsUpd->FspsConfig.PseTsnGbeSgmiiEnable[1];
}

/**
  Update HD Audio policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateHdAudioPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  HDAUDIO_CONFIG    *HdAudioConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gHdAudioConfigGuid, (VOID *) &HdAudioConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  HdAudioConfig->Pme                   = FspsUpd->FspsConfig.PchHdaPme;
  HdAudioConfig->HdAudioLinkFrequency  = FspsUpd->FspsConfig.PchHdaLinkFrequency;
  HdAudioConfig->CodecSxWakeCapability = FspsUpd->FspsConfig.PchHdaCodecSxWakeCapability;
  HdAudioConfig->VerbTableEntryNum     = FspsUpd->FspsConfig.PchHdaVerbTableEntryNum;
  HdAudioConfig->VerbTablePtr          = FspsUpd->FspsConfig.PchHdaVerbTablePtr;
}

/**
  Update Hsio policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateHsioPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PCH_HSIO_CONFIG    *HsioConfig;
  EFI_STATUS        Status;

  HsioConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gHsioConfigGuid, (VOID *) &HsioConfig);

  if (EFI_ERROR (Status) || HsioConfig == NULL) {
    return;
  }

  //
  // Update Pch HSIO policies
  //
  HsioConfig->ChipsetInitBinPtr = FspsUpd->FspsConfig.ChipsetInitBinPtr;
  HsioConfig->ChipsetInitBinLen = FspsUpd->FspsConfig.ChipsetInitBinLen;

}

/**
  Update FIA policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateFiaPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PCH_FIA_CONFIG     *FiaConfig;
  EFI_STATUS          Status;

  FiaConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gFiaConfigGuid, (VOID *) &FiaConfig);
  ASSERT_EFI_ERROR (Status);

  if (EFI_ERROR (Status)) {
    return;
  }

  FiaConfig->LaneReversalEnable = FspsUpd->FspsConfig.FiaLaneReversalEnable;
}

/**
  Update Cnvi policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateCnviPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  CNVI_CONFIG       *CnviConfig;
  EFI_STATUS        Status;

  CnviConfig = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicy, &gCnviConfigGuid, (VOID *) &CnviConfig);

  if (EFI_ERROR (Status) || CnviConfig == NULL) {
    return;
  }

  CnviConfig->Mode           = FspsUpd->FspsConfig.CnviMode;
  CnviConfig->BtCore         = FspsUpd->FspsConfig.CnviBtCore;
  CnviConfig->BtAudioOffload = FspsUpd->FspsConfig.CnviBtAudioOffload;
  CnviConfig->PinMux.RfReset = FspsUpd->FspsConfig.CnviRfResetPinMux;
  CnviConfig->PinMux.Clkreq  = FspsUpd->FspsConfig.CnviClkreqPinMux;

}

/**
  Update Espi policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateEspiPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PCH_ESPI_CONFIG   *EspiConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gEspiConfigGuid, (VOID *) &EspiConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  EspiConfig->LgmrEnable = FspsUpd->FspsConfig.PchEspiLgmrEnable;
  EspiConfig->BmeMasterSlaveEnabled = FspsUpd->FspsConfig.PchEspiBmeMasterSlaveEnabled;
  EspiConfig->HostC10ReportEnable = FspsUpd->FspsConfig.PchEspiHostC10ReportEnable;
}

/**
  Update SD policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateSdCardPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  SCS_SDCARD_CONFIG  *SdCardConfig;
  EFI_STATUS         Status;
  UINT8              Index;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSdCardConfigGuid, (VOID *) &SdCardConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  SdCardConfig->Enable = FspsUpd->FspsConfig.ScsSdCardEnabled;
  SdCardConfig->PowerEnableActiveHigh = FspsUpd->FspsConfig.SdCardPowerEnableActiveHigh;
  SdCardConfig->UseCustomDlls = FspsUpd->FspsConfig.SdCardUseCustomDlls;
  SdCardConfig->CustomDllValues.TxCmdDelayControl = FspsUpd->FspsConfig.SdCardTxCmdDelayRegValue;
  SdCardConfig->CustomDllValues.TxDataDelayControl1 = FspsUpd->FspsConfig.SdCardTxDataDelay1RegValue;
  SdCardConfig->CustomDllValues.TxDataDelayControl2 = FspsUpd->FspsConfig.SdCardTxDataDelay2RegValue;
  SdCardConfig->CustomDllValues.RxCmdDataDelayControl1 = FspsUpd->FspsConfig.SdCardRxCmdDataDelay1RegValue;
  SdCardConfig->CustomDllValues.RxCmdDataDelayControl2 = FspsUpd->FspsConfig.SdCardRxCmdDataDelay2RegValue;

  SdCardConfig->GpioConfig.PowerEnable.PinMux = FspsUpd->FspsConfig.SdCardGpioPrwEnBPinMux;
  SdCardConfig->GpioConfig.PowerEnable.PadTermination = FspsUpd->FspsConfig.SdCardGpioPrwEnBPadTermination;
  SdCardConfig->GpioConfig.Cmd.PinMux = FspsUpd->FspsConfig.SdCardGpioCmdPinMux;
  SdCardConfig->GpioConfig.Cmd.PadTermination = FspsUpd->FspsConfig.SdCardGpioCmdPadTermination;
  for (Index = 0; Index < SCS_SDCARD_MAX_DATA_GPIOS; Index++) {
    SdCardConfig->GpioConfig.Data[Index].PinMux = FspsUpd->FspsConfig.SdCardGpioDataPinMux[Index];
    SdCardConfig->GpioConfig.Data[Index].PadTermination = FspsUpd->FspsConfig.SdCardGpioDataPadTermination[Index];
  }
  SdCardConfig->GpioConfig.Cdb.PinMux = FspsUpd->FspsConfig.SdCardGpioCdbPinMux;
  SdCardConfig->GpioConfig.Cdb.PadTermination = FspsUpd->FspsConfig.SdCardGpioCdbPadTermination;
  SdCardConfig->GpioConfig.Clk.PinMux = FspsUpd->FspsConfig.SdCardGpioClkPinMux;
  SdCardConfig->GpioConfig.Clk.PadTermination = FspsUpd->FspsConfig.SdCardGpioClkPadTermination;
  SdCardConfig->GpioConfig.Wp.PinMux = FspsUpd->FspsConfig.SdCardGpioWpPinMux;
  SdCardConfig->GpioConfig.Wp.PadTermination = FspsUpd->FspsConfig.SdCardGpioWpPadTermination;
}

/**
  Update eMMC policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateEmmcPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  SCS_EMMC_CONFIG  *EmmcConfig;
  EFI_STATUS       Status;
  UINT8            Index;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gEmmcConfigGuid, (VOID *) &EmmcConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  EmmcConfig->Enable = FspsUpd->FspsConfig.ScsEmmcEnabled;
  EmmcConfig->Hs400Supported = FspsUpd->FspsConfig.ScsEmmcHs400Enabled;
  EmmcConfig->UseCustomDlls = FspsUpd->FspsConfig.EmmcUseCustomDlls;
  EmmcConfig->CustomDllValues.TxCmdDelayControl = FspsUpd->FspsConfig.EmmcTxCmdDelayRegValue;
  EmmcConfig->CustomDllValues.TxDataDelayControl1 = FspsUpd->FspsConfig.EmmcTxDataDelay1RegValue;
  EmmcConfig->CustomDllValues.TxDataDelayControl2 = FspsUpd->FspsConfig.EmmcTxDataDelay2RegValue;
  EmmcConfig->CustomDllValues.RxCmdDataDelayControl1 = FspsUpd->FspsConfig.EmmcRxCmdDataDelay1RegValue;
  EmmcConfig->CustomDllValues.RxCmdDataDelayControl2 = FspsUpd->FspsConfig.EmmcRxCmdDataDelay2RegValue;
  EmmcConfig->CustomDllValues.RxStrobeDelayControl = FspsUpd->FspsConfig.EmmcRxStrobeDelayRegValue;

  EmmcConfig->GpioConfig.Cmd.PinMux = FspsUpd->FspsConfig.EmmcGpioCmdPinMux;
  EmmcConfig->GpioConfig.Cmd.PadTermination = FspsUpd->FspsConfig.EmmcGpioCmdPadTermination;
  for (Index = 0; Index < SCS_EMMC_MAX_DATA_GPIOS; Index++) {
    EmmcConfig->GpioConfig.Data[Index].PinMux = FspsUpd->FspsConfig.EmmcGpioDataPinMux[Index];
    EmmcConfig->GpioConfig.Data[Index].PadTermination = FspsUpd->FspsConfig.EmmcGpioDataPadTermination[Index];
  }
  EmmcConfig->GpioConfig.Rclk.PinMux = FspsUpd->FspsConfig.EmmcGpioRclkPinMux;
  EmmcConfig->GpioConfig.Rclk.PadTermination = FspsUpd->FspsConfig.EmmcGpioRclkPadTermination;
  EmmcConfig->GpioConfig.Clk.PinMux = FspsUpd->FspsConfig.EmmcGpioClkPinMux;
  EmmcConfig->GpioConfig.Clk.PadTermination = FspsUpd->FspsConfig.EmmcGpioClkPadTermination;
  EmmcConfig->GpioConfig.Resetb.PinMux = FspsUpd->FspsConfig.EmmcGpioResetbPinMux;
  EmmcConfig->GpioConfig.Resetb.PadTermination = FspsUpd->FspsConfig.EmmcGpioResetbPadTermination;
  EmmcConfig->GpioConfig.HipMon.PinMux = FspsUpd->FspsConfig.EmmcGpioHipMonPinMux;
  EmmcConfig->GpioConfig.HipMon.PadTermination = FspsUpd->FspsConfig.EmmcGpioHipMonPadTermination;
}

/**
  Update UFS policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateUfsPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  SCS_UFS_CONFIG  *UfsConfig;
  UINT8           UfsIndex;
  EFI_STATUS      Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gUfsConfigGuid, (VOID *) &UfsConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  //
  // FSPS UPD has hard allocated configuration space for only 2 UFS controllers. Be sure to change this loop termination
  // condition after adding more space in FSPS UPD.
  //
  for (UfsIndex = 0; (UfsIndex < PchGetMaxUfsNum ()) && (UfsIndex < 2); UfsIndex++) {
    UfsConfig->UfsControllerConfig[UfsIndex].Enable = FspsUpd->FspsConfig.UfsEnable[UfsIndex];
  }
}
/**
  Update Pse policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdatePsePolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINTN             Index;
  PSE_CONFIG        *PseConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPseConfigGuid, (VOID *) &PseConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  PseConfig->PseLogOutputChannel  = FspsUpd->FspsConfig.PchPseLogOutputChannel;
  PseConfig->PseLogOutputSize     = FspsUpd->FspsConfig.PchPseLogOutputSize;
  PseConfig->PseLogOutputOffset   = FspsUpd->FspsConfig.PchPseLogOutputOffset;

  PseConfig->PseJtagEnabled       = (UINT32) FspsUpd->FspsConfig.PchPseJtagEnabled;
  PseConfig->PseJtagPinMux        = (UINT32) FspsUpd->FspsConfig.PchPseJtagPinMux;

  for (Index = 0; Index < GetPchMaxPseI2sControllersNum (); Index++) {
    PseConfig->I2s[Index].OwnerShip           = FspsUpd->FspsConfig.PchPseI2sEnable[Index];
    PseConfig->I2s[Index].SbInterruptEnable   = FspsUpd->FspsConfig.PchPseI2sSbInterruptEnable[Index];
    PseConfig->I2s[Index].PinMux.Tx           = FspsUpd->FspsConfig.PchPseI2sTxPinMux[Index];
    PseConfig->I2s[Index].PinMux.Rx           = FspsUpd->FspsConfig.PchPseI2sRxPinMux[Index];
    PseConfig->I2s[Index].PinMux.Sfrm         = FspsUpd->FspsConfig.PchPseI2sSfrmPinMux[Index];
    PseConfig->I2s[Index].PinMux.Clk          = FspsUpd->FspsConfig.PchPseI2sSclkPinMux[Index];
  }
  PseConfig->Pwm.OwnerShip            = FspsUpd->FspsConfig.PchPsePwmEnable;
  PseConfig->Pwm.SbInterruptEnable    = FspsUpd->FspsConfig.PchPsePwmSbInterruptEnable;
  for (Index = 0; Index < PCH_MAX_PSE_PWM_CONTROLLER_PINS; Index++) {
    PseConfig->Pwm.PinEnable[Index]           = FspsUpd->FspsConfig.PchPsePwmPinEnable[Index];
    PseConfig->Pwm.PinMux.Pin[Index]          = FspsUpd->FspsConfig.PchPsePwmPinMux[Index];
  }

  for (Index = 0; Index < GetPchMaxPseUartControllersNum (); Index++) {
    PseConfig->Uart[Index].OwnerShip          = FspsUpd->FspsConfig.PchPseUartEnable[Index];
    PseConfig->Uart[Index].SbInterruptEnable  = FspsUpd->FspsConfig.PchPseUartSbInterruptEnable[Index];
  }
  for (Index = 0; Index < GetPchMaxPseHsuartControllersNum (); Index++) {
    PseConfig->Hsuart[Index].OwnerShip        = FspsUpd->FspsConfig.PchPseHsuartEnable[Index];
  }
  for (Index = 0; Index < GetPchMaxPseQepControllersNum (); Index++) {
    PseConfig->Qep[Index].OwnerShip           = FspsUpd->FspsConfig.PchPseQepEnable[Index];
    PseConfig->Qep[Index].SbInterruptEnable   = FspsUpd->FspsConfig.PchPseQepSbInterruptEnable[Index];
  }
  for (Index = 0; Index < GetPchMaxPseI2cControllersNum (); Index++) {
    PseConfig->I2c[Index].OwnerShip           = FspsUpd->FspsConfig.PchPseI2cEnable[Index];
    PseConfig->I2c[Index].SbInterruptEnable   = FspsUpd->FspsConfig.PchPseI2cSbInterruptEnable[Index];
  }
  for (Index = 0; Index < GetPchMaxPseSpiControllersNum (); Index++) {
    PseConfig->Spi[Index].OwnerShip           = FspsUpd->FspsConfig.PchPseSpiEnable[Index];
    PseConfig->Spi[Index].SbInterruptEnable   = FspsUpd->FspsConfig.PchPseSpiSbInterruptEnable[Index];
    PseConfig->Spi[Index].CsEnable[0]         = FspsUpd->FspsConfig.PchPseSpiCs0Enable[Index];
    PseConfig->Spi[Index].CsEnable[1]         = FspsUpd->FspsConfig.PchPseSpiCs1Enable[Index];

    PseConfig->Spi[Index].PinMux.Mosi         = FspsUpd->FspsConfig.PchPseSpiMosiPinMux[Index];
    PseConfig->Spi[Index].PinMux.Miso         = FspsUpd->FspsConfig.PchPseSpiMisoPinMux[Index];
    PseConfig->Spi[Index].PinMux.Clk          = FspsUpd->FspsConfig.PchPseSpiClkPinMux[Index];
    PseConfig->Spi[Index].PinMux.Cs[0]        = FspsUpd->FspsConfig.PchPseSpiCs0PinMux[Index];
    PseConfig->Spi[Index].PinMux.Cs[1]        = FspsUpd->FspsConfig.PchPseSpiCs1PinMux[Index];
  }
  PseConfig->Adc.OwnerShip                    = FspsUpd->FspsConfig.PchPseAdcEnable;
  PseConfig->Adc.SbInterruptEnable            = FspsUpd->FspsConfig.PchPseAdcSbInterruptEnable;
  for (Index = 0; Index < GetPchMaxPseCanControllersNum (); Index++) {
    PseConfig->Can[Index].OwnerShip           = FspsUpd->FspsConfig.PchPseCanEnable[Index];
    PseConfig->Can[Index].SbInterruptEnable   = FspsUpd->FspsConfig.PchPseCanSbInterruptEnable[Index];
  }
  for (Index = 0; Index < GetPchMaxPseGbeControllersNum (); Index++) {
    PseConfig->Gbe[Index].OwnerShip           = FspsUpd->FspsConfig.PchPseGbeEnable[Index];
  }
  for (Index = 0; Index < GetPchMaxPseDmaControllersNum (); Index++) {
    PseConfig->Dma[Index].OwnerShip           = FspsUpd->FspsConfig.PchPseDmaEnable[Index];
    PseConfig->Dma[Index].SbInterruptEnable   = FspsUpd->FspsConfig.PchPseDmaSbInterruptEnable[Index];
  }
  PseConfig->Lh2Pse.SbInterruptEnable         = FspsUpd->FspsConfig.PchPseLh2PseSbInterruptEnable;
  for (Index = 0; Index < GetPchMaxPseTimedGpioControllersNum (); Index++) {
    PseConfig->TimedGpio[Index].OwnerShip     = FspsUpd->FspsConfig.PchPseTimedGpioEnable[Index];
    PseConfig->TimedGpio[Index].PinAllocation = FspsUpd->FspsConfig.PchPseTimedGpioPinAllocation[Index];
  }
  for (Index = 0; Index < GetPchMaxPseTimdedGpioPinsNum(); Index++) {
    PseConfig->TimedGpioPinEnable[Index] = FspsUpd->FspsConfig.PchPseTimedGpioPinEnable[Index];
  }
  PseConfig->TimedGpioPinMux.Pin[6]           = FspsUpd->FspsConfig.PchPseTgpio6PinMux;
  PseConfig->TimedGpioPinMux.Pin[7]           = FspsUpd->FspsConfig.PchPseTgpio7PinMux;
  PseConfig->TimedGpioPinMux.Pin[8]           = FspsUpd->FspsConfig.PchPseTgpio8PinMux;
  PseConfig->TimedGpioPinMux.Pin[9]           = FspsUpd->FspsConfig.PchPseTgpio9PinMux;
  PseConfig->TimedGpioPinMux.Pin[10]          = FspsUpd->FspsConfig.PchPseTgpio10PinMux;
  PseConfig->TimedGpioPinMux.Pin[11]          = FspsUpd->FspsConfig.PchPseTgpio11PinMux;
  PseConfig->TimedGpioPinMux.Pin[12]          = FspsUpd->FspsConfig.PchPseTgpio12PinMux;
  PseConfig->TimedGpioPinMux.Pin[13]          = FspsUpd->FspsConfig.PchPseTgpio13PinMux;
  PseConfig->TimedGpioPinMux.Pin[14]          = FspsUpd->FspsConfig.PchPseTgpio14PinMux;
  PseConfig->TimedGpioPinMux.Pin[15]          = FspsUpd->FspsConfig.PchPseTgpio15PinMux;
  PseConfig->TimedGpioPinMux.Pin[16]          = FspsUpd->FspsConfig.PchPseTgpio16PinMux;
  PseConfig->TimedGpioPinMux.Pin[17]          = FspsUpd->FspsConfig.PchPseTgpio17PinMux;
  PseConfig->TimedGpioPinMux.Pin[18]          = FspsUpd->FspsConfig.PchPseTgpio18PinMux;
  PseConfig->TimedGpioPinMux.Pin[19]          = FspsUpd->FspsConfig.PchPseTgpio19PinMux;
}
/**
  Update SATA Controllers policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateSataPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINTN             Index;
  UINTN             SataCtrlIndex;
  SATA_CONFIG       *SataConfig;

  for (SataCtrlIndex = 0; SataCtrlIndex < MaxSataControllerNum (); SataCtrlIndex++) {
    SataConfig                  = GetPchSataConfig (SiPolicy, SataCtrlIndex);

    SataConfig->Enable          = FspsUpd->FspsConfig.SataEnable;
    SataConfig->SalpSupport     = FspsUpd->FspsConfig.SataSalpSupport;
    SataConfig->PortMultiplier  = FspsUpd->FspsConfig.SataPortMultiplier;
    SataConfig->PwrOptEnable    = FspsUpd->FspsConfig.SataPwrOptEnable;
    SataConfig->EsataSpeedLimit = FspsUpd->FspsConfig.EsataSpeedLimit;
    SataConfig->LedEnable       = FspsUpd->FspsConfig.SataLedEnable;
    SataConfig->SataMode        = FspsUpd->FspsConfig.SataMode;
    SataConfig->SpeedLimit      = FspsUpd->FspsConfig.SataSpeedLimit;

    for (Index = 0; Index < MaxSataPortNum (SataCtrlIndex); Index++) {
      SataConfig->PortSettings[Index].Enable           = FspsUpd->FspsConfig.SataPortsEnable[Index];
      SataConfig->PortSettings[Index].HotPlug          = FspsUpd->FspsConfig.SataPortsHotPlug[Index];
      SataConfig->PortSettings[Index].InterlockSw      = FspsUpd->FspsConfig.SataPortsInterlockSw[Index];
      SataConfig->PortSettings[Index].External         = FspsUpd->FspsConfig.SataPortsExternal[Index];
      SataConfig->PortSettings[Index].SpinUp           = FspsUpd->FspsConfig.SataPortsSpinUp[Index];
      SataConfig->PortSettings[Index].SolidStateDrive  = FspsUpd->FspsConfig.SataPortsSolidStateDrive[Index];
      SataConfig->PortSettings[Index].DevSlp           = FspsUpd->FspsConfig.SataPortsDevSlp[Index];
      SataConfig->PortSettings[Index].EnableDitoConfig = FspsUpd->FspsConfig.SataPortsEnableDitoConfig[Index];
      SataConfig->PortSettings[Index].DmVal            = FspsUpd->FspsConfig.SataPortsDmVal[Index];
      SataConfig->PortSettings[Index].DitoVal          = FspsUpd->FspsConfig.SataPortsDitoVal[Index];
      SataConfig->PortSettings[Index].ZpOdd            = FspsUpd->FspsConfig.SataPortsZpOdd[Index];
      SataConfig->PortSettings[Index].RxPolarity       = FspsUpd->FspsConfig.SataPortsRxPolarity[Index];
    }
    SataConfig->RaidDeviceId       = FspsUpd->FspsConfig.SataRstRaidDeviceId;
    SataConfig->SataRstInterrupt   = FspsUpd->FspsConfig.SataRstInterrupt;

    SataConfig->ThermalThrottling.P0T1M            = FspsUpd->FspsConfig.SataP0T1M;
    SataConfig->ThermalThrottling.P0T2M            = FspsUpd->FspsConfig.SataP0T2M;
    SataConfig->ThermalThrottling.P0T3M            = FspsUpd->FspsConfig.SataP0T3M;
    SataConfig->ThermalThrottling.P0TDisp          = FspsUpd->FspsConfig.SataP0TDisp;
    SataConfig->ThermalThrottling.P1T1M            = FspsUpd->FspsConfig.SataP1T1M;
    SataConfig->ThermalThrottling.P1T2M            = FspsUpd->FspsConfig.SataP1T2M;
    SataConfig->ThermalThrottling.P1T3M            = FspsUpd->FspsConfig.SataP1T3M;
    SataConfig->ThermalThrottling.P1TDisp          = FspsUpd->FspsConfig.SataP1TDisp;
    SataConfig->ThermalThrottling.P0Tinact         = FspsUpd->FspsConfig.SataP0Tinact;
    SataConfig->ThermalThrottling.P0TDispFinit     = FspsUpd->FspsConfig.SataP0TDispFinit;
    SataConfig->ThermalThrottling.P1Tinact         = FspsUpd->FspsConfig.SataP1Tinact;
    SataConfig->ThermalThrottling.P1TDispFinit     = FspsUpd->FspsConfig.SataP1TDispFinit;
    SataConfig->ThermalThrottling.SuggestedSetting = FspsUpd->FspsConfig.SataThermalSuggestedSetting;

  }
}

/**
  Update RST policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateRstPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINTN             Index;
  RST_CONFIG        *RstConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gRstConfigGuid, (VOID *) &RstConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  RstConfig->Raid0              = FspsUpd->FspsConfig.SataRstRaid0;
  RstConfig->Raid1              = FspsUpd->FspsConfig.SataRstRaid1;
  RstConfig->Raid10             = FspsUpd->FspsConfig.SataRstRaid10;
  RstConfig->Raid5              = FspsUpd->FspsConfig.SataRstRaid5;
  RstConfig->Irrt               = FspsUpd->FspsConfig.SataRstIrrt;
  RstConfig->OromUiBanner       = FspsUpd->FspsConfig.SataRstOromUiBanner;
  RstConfig->OromUiDelay        = FspsUpd->FspsConfig.SataRstOromUiDelay;
  RstConfig->HddUnlock          = FspsUpd->FspsConfig.SataRstHddUnlock;
  RstConfig->LedLocate          = FspsUpd->FspsConfig.SataRstLedLocate;
  RstConfig->IrrtOnly           = FspsUpd->FspsConfig.SataRstIrrtOnly;
  RstConfig->SmartStorage       = FspsUpd->FspsConfig.SataRstSmartStorage;
  RstConfig->OptaneMemory       = FspsUpd->FspsConfig.SataRstOptaneMemory;
  RstConfig->LegacyOrom         = FspsUpd->FspsConfig.SataRstLegacyOrom;
  RstConfig->CpuAttachedStorage = FspsUpd->FspsConfig.SataRstCpuAttachedStorage;

  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
    RstConfig->HardwareRemappedStorageConfig[Index].Enable             = FspsUpd->FspsConfig.SataRstPcieEnable[Index];
    RstConfig->HardwareRemappedStorageConfig[Index].RstPcieStoragePort = FspsUpd->FspsConfig.SataRstPcieStoragePort[Index];
    RstConfig->HardwareRemappedStorageConfig[Index].DeviceResetDelay   = FspsUpd->FspsConfig.SataRstPcieDeviceResetDelay[Index];
  }
}

/**
  Update Usb policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateUsbPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINTN             Index;
  USB_CONFIG        *UsbConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsbConfigGuid, (VOID *) &UsbConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  UsbConfig->EnableComplianceMode   = FspsUpd->FspsConfig.PchEnableComplianceMode;
  UsbConfig->PdoProgramming         = FspsUpd->FspsConfig.UsbPdoProgramming;
  UsbConfig->OverCurrentEnable      = FspsUpd->FspsConfig.PchUsbOverCurrentEnable;
  if (FspsUpd->FspsConfig.PchEnableDbcObs) {
    UsbConfig->OverCurrentEnable    = FALSE;
  }
  UsbConfig->XhciOcLock             = FspsUpd->FspsConfig.PchXhciOcLock;
  for (Index = 0; Index < GetPchXhciMaxUsb2PortNum (); Index++) {
    UsbConfig->PortUsb20[Index].Enable         = FspsUpd->FspsConfig.PortUsb20Enable[Index];
    UsbConfig->PortUsb20[Index].OverCurrentPin = FspsUpd->FspsConfig.Usb2OverCurrentPin[Index];
    UsbConfig->USB20Otg[Index]                 = FspsUpd->FspsConfig.USB20Otg[Index];
  }
  for (Index = 0; Index < GetPchXhciMaxUsb3PortNum (); Index++) {
    UsbConfig->PortUsb30[Index].Enable         = FspsUpd->FspsConfig.PortUsb30Enable[Index];
    UsbConfig->PortUsb30[Index].OverCurrentPin = FspsUpd->FspsConfig.Usb3OverCurrentPin[Index];
    UsbConfig->USB30Otg[Index]                 = FspsUpd->FspsConfig.USB30Otg[Index];
  }

  UsbConfig->LtrOverrideEnable           = FspsUpd->FspsConfig.PchUsbLtrOverrideEnable;
  if (UsbConfig->LtrOverrideEnable) {
    UsbConfig->LtrHighIdleTimeOverride   = FspsUpd->FspsConfig.PchUsbLtrHighIdleTimeOverride;
    UsbConfig->LtrMediumIdleTimeOverride = FspsUpd->FspsConfig.PchUsbLtrMediumIdleTimeOverride;
    UsbConfig->LtrLowIdleTimeOverride    = FspsUpd->FspsConfig.PchUsbLtrLowIdleTimeOverride;
  }
  UsbConfig->UsbClockGatingEnable   = FspsUpd->FspsConfig.UsbClockGatingEnable;
  UsbConfig->UsbPowerGatingEnable   = FspsUpd->FspsConfig.UsbPowerGatingEnable;
  UsbConfig->USB3LinkSpeed          = FspsUpd->FspsConfig.USB3LinkSpeed;
  UsbConfig->XdciConfig.Enable      = FspsUpd->FspsConfig.XdciEnable;

}

/**
  Update Usb2Phy policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateUsb2PhyPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINTN             Index;
  USB2_PHY_CONFIG   *Usb2PhyConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsb2PhyConfigGuid, (VOID *) &Usb2PhyConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  for (Index = 0; Index < GetPchUsb2MaxPhysicalPortNum (); Index++) {
    Usb2PhyConfig->Port[Index].Petxiset   = FspsUpd->FspsConfig.Usb2PhyPetxiset[Index];
    Usb2PhyConfig->Port[Index].Txiset     = FspsUpd->FspsConfig.Usb2PhyTxiset[Index];
    Usb2PhyConfig->Port[Index].Predeemp   = FspsUpd->FspsConfig.Usb2PhyPredeemp[Index];
    Usb2PhyConfig->Port[Index].Pehalfbit  = FspsUpd->FspsConfig.Usb2PhyPehalfbit[Index];
  }
}

/**
  Update Usb3Hsio policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateUsb3HsioPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINTN             Index;
  USB3_HSIO_CONFIG  *Usb3HsioConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsb3HsioConfigGuid, (VOID *) &Usb3HsioConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  for (Index = 0; Index < GetPchXhciMaxUsb3PortNum (); Index++) {
    Usb3HsioConfig->Port[Index].HsioTxDeEmphEnable             = FspsUpd->FspsConfig.Usb3HsioTxDeEmphEnable[Index];
    Usb3HsioConfig->Port[Index].HsioTxDeEmph                   = FspsUpd->FspsConfig.Usb3HsioTxDeEmph[Index];

    Usb3HsioConfig->Port[Index].HsioTxDownscaleAmpEnable       = FspsUpd->FspsConfig.Usb3HsioTxDownscaleAmpEnable[Index];
    Usb3HsioConfig->Port[Index].HsioTxDownscaleAmp             = FspsUpd->FspsConfig.Usb3HsioTxDownscaleAmp[Index];

    Usb3HsioConfig->Port[Index].HsioCtrlAdaptOffsetCfgEnable   = FspsUpd->FspsConfig.PchUsb3HsioCtrlAdaptOffsetCfgEnable[Index];
    Usb3HsioConfig->Port[Index].HsioCtrlAdaptOffsetCfg         = FspsUpd->FspsConfig.PchUsb3HsioCtrlAdaptOffsetCfg[Index];

    Usb3HsioConfig->Port[Index].HsioFilterSelPEnable           = FspsUpd->FspsConfig.PchUsb3HsioFilterSelPEnable[Index];
    Usb3HsioConfig->Port[Index].HsioFilterSelP                 = FspsUpd->FspsConfig.PchUsb3HsioFilterSelP[Index];

    Usb3HsioConfig->Port[Index].HsioFilterSelNEnable           = FspsUpd->FspsConfig.PchUsb3HsioFilterSelNEnable[Index];
    Usb3HsioConfig->Port[Index].HsioFilterSelN                 = FspsUpd->FspsConfig.PchUsb3HsioFilterSelN[Index];

    Usb3HsioConfig->Port[Index].HsioOlfpsCfgPullUpDwnResEnable = FspsUpd->FspsConfig.PchUsb3HsioOlfpsCfgPullUpDwnResEnable[Index];
    Usb3HsioConfig->Port[Index].HsioOlfpsCfgPullUpDwnRes       = FspsUpd->FspsConfig.PchUsb3HsioOlfpsCfgPullUpDwnRes[Index];
    Usb3HsioConfig->Port[Index].HsioTxRate0UniqTranEnable      = FspsUpd->FspsConfig.Usb3HsioTxRate0UniqTranEnable[Index];
    Usb3HsioConfig->Port[Index].HsioTxRate0UniqTran            = FspsUpd->FspsConfig.Usb3HsioTxRate0UniqTran[Index];
    Usb3HsioConfig->Port[Index].HsioTxRate1UniqTranEnable      = FspsUpd->FspsConfig.Usb3HsioTxRate1UniqTranEnable[Index];
    Usb3HsioConfig->Port[Index].HsioTxRate1UniqTran            = FspsUpd->FspsConfig.Usb3HsioTxRate1UniqTran[Index];
    Usb3HsioConfig->Port[Index].HsioTxRate2UniqTranEnable      = FspsUpd->FspsConfig.Usb3HsioTxRate2UniqTranEnable[Index];
    Usb3HsioConfig->Port[Index].HsioTxRate2UniqTran            = FspsUpd->FspsConfig.Usb3HsioTxRate2UniqTran[Index];
    Usb3HsioConfig->Port[Index].HsioTxRate3UniqTranEnable      = FspsUpd->FspsConfig.Usb3HsioTxRate3UniqTranEnable[Index];
    Usb3HsioConfig->Port[Index].HsioTxRate3UniqTran            = FspsUpd->FspsConfig.Usb3HsioTxRate3UniqTran[Index];
  }
}

/**
  Update PcieRp policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdatePcieRpPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINTN             Index;
  UINTN             MaxPcieRootPorts;
  PCH_PCIE_CONFIG   *PcieRpConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  MaxPcieRootPorts = GetPchMaxPciePortNum ();
  for (Index = 0; Index < MaxPcieRootPorts; Index ++) {
    PcieRpConfig->RootPort[Index].HotPlug                  = FspsUpd->FspsConfig.PcieRpHotPlug[Index];
    PcieRpConfig->RootPort[Index].PmSci                    = FspsUpd->FspsConfig.PcieRpPmSci[Index];
    PcieRpConfig->RootPort[Index].TransmitterHalfSwing     = FspsUpd->FspsConfig.PcieRpTransmitterHalfSwing[Index];
    PcieRpConfig->RootPort[Index].ClkReqDetect             = FspsUpd->FspsConfig.PcieRpClkReqDetect[Index];
    PcieRpConfig->RootPort[Index].AdvancedErrorReporting   = FspsUpd->FspsConfig.PcieRpAdvancedErrorReporting[Index];
    PcieRpConfig->RootPort[Index].UnsupportedRequestReport = FspsUpd->FspsConfig.PcieRpUnsupportedRequestReport[Index];
    PcieRpConfig->RootPort[Index].FatalErrorReport         = FspsUpd->FspsConfig.PcieRpFatalErrorReport[Index];
    PcieRpConfig->RootPort[Index].NoFatalErrorReport       = FspsUpd->FspsConfig.PcieRpNoFatalErrorReport[Index];
    PcieRpConfig->RootPort[Index].CorrectableErrorReport   = FspsUpd->FspsConfig.PcieRpCorrectableErrorReport[Index];
    PcieRpConfig->RootPort[Index].SystemErrorOnFatalError  = FspsUpd->FspsConfig.PcieRpSystemErrorOnFatalError[Index];
    PcieRpConfig->RootPort[Index].SystemErrorOnNonFatalError    = FspsUpd->FspsConfig.PcieRpSystemErrorOnNonFatalError[Index];
    PcieRpConfig->RootPort[Index].SystemErrorOnCorrectableError = FspsUpd->FspsConfig.PcieRpSystemErrorOnCorrectableError[Index];
    PcieRpConfig->RootPort[Index].MaxPayload               = FspsUpd->FspsConfig.PcieRpMaxPayload[Index];
    PcieRpConfig->RootPort[Index].PcieSpeed                = FspsUpd->FspsConfig.PcieRpPcieSpeed[Index];
    PcieRpConfig->RootPort[Index].PhysicalSlotNumber       = FspsUpd->FspsConfig.PcieRpPhysicalSlotNumber[Index];
    PcieRpConfig->RootPort[Index].SlotImplemented          = FspsUpd->FspsConfig.PcieRpSlotImplemented[Index];
    PcieRpConfig->RootPort[Index].CompletionTimeout        = FspsUpd->FspsConfig.PcieRpCompletionTimeout[Index];
    PcieRpConfig->RootPort[Index].Aspm                     = FspsUpd->FspsConfig.PcieRpAspm[Index];
    PcieRpConfig->RootPort[Index].L1Substates              = FspsUpd->FspsConfig.PcieRpL1Substates[Index];
    PcieRpConfig->RootPort[Index].LtrEnable                = FspsUpd->FspsConfig.PcieRpLtrEnable[Index];
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrConfigLock  = FspsUpd->FspsConfig.PcieRpLtrConfigLock[Index];
    PcieRpConfig->RootPort[Index].AcsEnabled                       = FspsUpd->FspsConfig.PcieRpAcsEnabled[Index];
    PcieRpConfig->RootPort[Index].PcieRpCommonConfig.EnableCpm     = FspsUpd->FspsConfig.PcieRpEnableCpm[Index];
    PcieRpConfig->RootPort[Index].MultiVcEnabled                   = FspsUpd->FspsConfig.PcieRpMultiVcEnabled[Index];
    PcieRpConfig->RootPort[Index].DetectTimeoutMs                  = FspsUpd->FspsConfig.PcieRpDetectTimeoutMs[Index];
    PcieRpConfig->RootPort[Index].PtmEnabled = FspsUpd->FspsConfig.PciePtm[Index];
    PcieRpConfig->RootPort[Index].DpcEnabled = FspsUpd->FspsConfig.PcieDpc[Index];
    PcieRpConfig->RootPort[Index].RpDpcExtensionsEnabled = FspsUpd->FspsConfig.PcieEdpc[Index];

    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxSnoopLatency       = FspsUpd->FspsConfig.PcieRpLtrMaxSnoopLatency[Index];
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.LtrMaxNoSnoopLatency     = FspsUpd->FspsConfig.PcieRpLtrMaxNoSnoopLatency[Index];

    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.SnoopLatencyOverrideMode       = FspsUpd->FspsConfig.PcieRpSnoopLatencyOverrideMode[Index];
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.SnoopLatencyOverrideMultiplier = FspsUpd->FspsConfig.PcieRpSnoopLatencyOverrideMultiplier[Index];
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.SnoopLatencyOverrideValue      = FspsUpd->FspsConfig.PcieRpSnoopLatencyOverrideValue[Index];

    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.NonSnoopLatencyOverrideMode       = FspsUpd->FspsConfig.PcieRpNonSnoopLatencyOverrideMode[Index];
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.NonSnoopLatencyOverrideMultiplier = FspsUpd->FspsConfig.PcieRpNonSnoopLatencyOverrideMultiplier[Index];
    PcieRpConfig->RootPort[Index].PcieRpLtrConfig.NonSnoopLatencyOverrideValue      = FspsUpd->FspsConfig.PcieRpNonSnoopLatencyOverrideValue[Index];

    PcieRpConfig->RootPort[Index].SlotPowerLimitScale      = FspsUpd->FspsConfig.PcieRpSlotPowerLimitScale[Index];
    PcieRpConfig->RootPort[Index].SlotPowerLimitValue      = FspsUpd->FspsConfig.PcieRpSlotPowerLimitValue[Index];
  }

  //
  // Update PCIE RP policies
  //
  PcieRpConfig->EnablePort8xhDecode           = FspsUpd->FspsConfig.PcieEnablePort8xhDecode;
  PcieRpConfig->PchPciePort8xhDecodePortIndex = FspsUpd->FspsConfig.PchPciePort8xhDecodePortIndex;
  PcieRpConfig->EnablePeerMemoryWrite         = FspsUpd->FspsConfig.PcieEnablePeerMemoryWrite;
  PcieRpConfig->ComplianceTestMode            = FspsUpd->FspsConfig.PcieComplianceTestMode;
  PcieRpConfig->TestPcieClockGating           = FspsUpd->FspsConfig.TestPcieClockGating;
  PcieRpConfig->RpFunctionSwap                = FspsUpd->FspsConfig.PcieRpFunctionSwap;

  //
  // PCIe EQ settings
  //

  PcieRpConfig->OverrideEqualizationDefaults = FspsUpd->FspsConfig.PcieEqOverrideDefault;
  PcieRpConfig->PcieLinkEqPlatformSettings.PcieLinkEqMethod = FspsUpd->FspsConfig.PcieEqMethod;
  PcieRpConfig->PcieLinkEqPlatformSettings.PcieLinkEqMode = FspsUpd->FspsConfig.PcieEqMode;
  PcieRpConfig->PcieLinkEqPlatformSettings.Ph3NumberOfPresetsOrCoefficients = FspsUpd->FspsConfig.PcieEqPh3NumberOfPresetsOrCoefficients;
  for (Index = 0; Index < PCIE_LINK_EQ_COEFFICIENTS_MAX; Index++) {
    PcieRpConfig->PcieLinkEqPlatformSettings.Ph3CoefficientsList[Index].PreCursor = FspsUpd->FspsConfig.PcieEqPh3PreCursorList[Index];
    PcieRpConfig->PcieLinkEqPlatformSettings.Ph3CoefficientsList[Index].PostCursor = FspsUpd->FspsConfig.PcieEqPh3PostCursorList[Index];
  }
  for (Index = 0; Index < PCIE_LINK_EQ_PRESETS_MAX; Index++) {
    PcieRpConfig->PcieLinkEqPlatformSettings.Ph3PresetList[Index] = FspsUpd->FspsConfig.PcieEqPh3PresetList[Index];
  }
  PcieRpConfig->PcieLinkEqPlatformSettings.Ph1DownstreamPortTransmitterPreset = FspsUpd->FspsConfig.PcieEqPh1DownstreamPortTransmitterPreset;
  PcieRpConfig->PcieLinkEqPlatformSettings.Ph1UpstreamPortTransmitterPreset = FspsUpd->FspsConfig.PcieEqPh1UpstreamPortTransmitterPreset;


}

/**
  Update Serial IO policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateSerialIoPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINTN                 Index;
  UINTN                 CsIndex;
  SERIAL_IO_CONFIG      *SerialIoConfig;
  EFI_STATUS            Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gSerialIoConfigGuid, (VOID *) &SerialIoConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  for (Index = 0; Index < GetPchMaxSerialIoSpiControllersNum (); Index++) {
    SerialIoConfig->SpiDeviceConfig[Index].Mode            = FspsUpd->FspsConfig.SerialIoSpiMode[Index];
    SerialIoConfig->SpiDeviceConfig[Index].DefaultCsOutput = FspsUpd->FspsConfig.SerialIoSpiDefaultCsOutput[Index];
    SerialIoConfig->SpiDeviceConfig[Index].MisoEnable      = FspsUpd->FspsConfig.SerialIoSpiMisoEnable[Index];
    SerialIoConfig->SpiDeviceConfig[Index].CsMode          = FspsUpd->FspsConfig.SerialIoSpiCsMode[Index];
    SerialIoConfig->SpiDeviceConfig[Index].CsState         = FspsUpd->FspsConfig.SerialIoSpiCsState[Index];
    for (CsIndex = 0; CsIndex < PCH_MAX_SERIALIO_SPI_CHIP_SELECTS; CsIndex++) {
      SerialIoConfig->SpiDeviceConfig[Index].CsEnable[CsIndex]   = FspsUpd->FspsConfig.SerialIoSpiCsEnable[Index * PCH_MAX_SERIALIO_SPI_CHIP_SELECTS + CsIndex];
      SerialIoConfig->SpiDeviceConfig[Index].CsPolarity[CsIndex] = FspsUpd->FspsConfig.SerialIoSpiCsPolarity[Index * PCH_MAX_SERIALIO_SPI_CHIP_SELECTS + CsIndex];
    }
  }

  for (Index = 0; Index < GetPchMaxSerialIoUartControllersNum (); Index++) {
    SerialIoConfig->UartDeviceConfig[Index].Mode                = FspsUpd->FspsConfig.SerialIoUartMode[Index];
    SerialIoConfig->UartDeviceConfig[Index].Attributes.BaudRate = FspsUpd->FspsConfig.SerialIoUartBaudRate[Index];
    SerialIoConfig->UartDeviceConfig[Index].Attributes.Parity   = FspsUpd->FspsConfig.SerialIoUartParity[Index];
    SerialIoConfig->UartDeviceConfig[Index].Attributes.DataBits = FspsUpd->FspsConfig.SerialIoUartDataBits[Index];
    SerialIoConfig->UartDeviceConfig[Index].Attributes.StopBits = FspsUpd->FspsConfig.SerialIoUartStopBits[Index];
    SerialIoConfig->UartDeviceConfig[Index].Attributes.AutoFlow = FspsUpd->FspsConfig.SerialIoUartAutoFlow[Index];
    SerialIoConfig->UartDeviceConfig[Index].PinMux.Rx           = FspsUpd->FspsConfig.SerialIoUartRxPinMuxPolicy[Index];
    SerialIoConfig->UartDeviceConfig[Index].PinMux.Tx           = FspsUpd->FspsConfig.SerialIoUartTxPinMuxPolicy[Index];
    SerialIoConfig->UartDeviceConfig[Index].PinMux.Rts          = FspsUpd->FspsConfig.SerialIoUartRtsPinMuxPolicy[Index];
    SerialIoConfig->UartDeviceConfig[Index].PinMux.Cts          = FspsUpd->FspsConfig.SerialIoUartCtsPinMuxPolicy[Index];
    SerialIoConfig->UartDeviceConfig[Index].PowerGating         = FspsUpd->FspsConfig.SerialIoUartPowerGating[Index];
    SerialIoConfig->UartDeviceConfig[Index].DmaEnable           = FspsUpd->FspsConfig.SerialIoUartDmaEnable[Index];
    SerialIoConfig->UartDeviceConfig[Index].DBG2                = FspsUpd->FspsConfig.SerialIoUartDbg2[Index];
  }

  for (Index = 0; Index < GetPchMaxSerialIoI2cControllersNum (); Index++) {
    SerialIoConfig->I2cDeviceConfig[Index].Mode           = FspsUpd->FspsConfig.SerialIoI2cMode[Index];
    SerialIoConfig->I2cDeviceConfig[Index].PinMux.Sda     = FspsUpd->FspsConfig.PchSerialIoI2cSdaPinMux[Index];
    SerialIoConfig->I2cDeviceConfig[Index].PinMux.Scl     = FspsUpd->FspsConfig.PchSerialIoI2cSclPinMux[Index];
    SerialIoConfig->I2cDeviceConfig[Index].PadTermination = FspsUpd->FspsConfig.PchSerialIoI2cPadsTermination[Index];
  }
}

/**
  Update Interrupt policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateInterruptPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINT8                        NumOfDevIntConfig;
  PCH_DEVICE_INTERRUPT_CONFIG  *DevIntConfg;
  PCH_INTERRUPT_CONFIG         *InterruptConfig;
  EFI_STATUS                   Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gInterruptConfigGuid, (VOID *) &InterruptConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  if (FspsUpd->FspsConfig.NumOfDevIntConfig != 0) {
    DevIntConfg = (PCH_DEVICE_INTERRUPT_CONFIG *)FspsUpd->FspsConfig.DevIntConfigPtr;
    NumOfDevIntConfig = FspsUpd->FspsConfig.NumOfDevIntConfig;
    ASSERT (NumOfDevIntConfig <= PCH_MAX_DEVICE_INTERRUPT_CONFIG);

    InterruptConfig->NumOfDevIntConfig = NumOfDevIntConfig;
    ZeroMem (
      InterruptConfig->DevIntConfig,
      PCH_MAX_DEVICE_INTERRUPT_CONFIG * sizeof (PCH_DEVICE_INTERRUPT_CONFIG)
      );
    CopyMem (
      InterruptConfig->DevIntConfig,
      DevIntConfg,
      NumOfDevIntConfig * sizeof (PCH_DEVICE_INTERRUPT_CONFIG)
      );
  }
  InterruptConfig->GpioIrqRoute = FspsUpd->FspsConfig.GpioIrqRoute;
  InterruptConfig->SciIrqSelect = FspsUpd->FspsConfig.SciIrqSelect;
  InterruptConfig->TcoIrqSelect = FspsUpd->FspsConfig.TcoIrqSelect;
  InterruptConfig->TcoIrqEnable = FspsUpd->FspsConfig.TcoIrqEnable;
}

/**
  Update LockDown policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateLockDownPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PCH_LOCK_DOWN_CONFIG   *LockDownConfig;
  EFI_STATUS             Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gLockDownConfigGuid, (VOID *) &LockDownConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  LockDownConfig->GlobalSmi       = FspsUpd->FspsConfig.PchLockDownGlobalSmi;
  LockDownConfig->BiosInterface   = FspsUpd->FspsConfig.PchLockDownBiosInterface;
  LockDownConfig->BiosLock        = FspsUpd->FspsConfig.PchLockDownBiosLock;

  LockDownConfig->UnlockGpioPads  = FspsUpd->FspsConfig.PchUnlockGpioPads;
}

/**
  Update Rtc policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateRtcPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  RTC_CONFIG        *RtcConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gRtcConfigGuid, (VOID *) &RtcConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  RtcConfig->BiosInterfaceLock    = FspsUpd->FspsConfig.RtcBiosInterfaceLock;
  RtcConfig->MemoryLock           = FspsUpd->FspsConfig.RtcMemoryLock;
}

/**
  Update DMI policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateDmiPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PCH_DMI_CONFIG    *DmiConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchDmiConfigGuid, (VOID *) &DmiConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  DmiConfig->DmiAspmCtrl  = FspsUpd->FspsConfig.PchDmiAspmCtrl;
  DmiConfig->PwrOptEnable = FspsUpd->FspsConfig.PchPwrOptEnable;
  DmiConfig->CwbEnable    = FspsUpd->FspsConfig.PchDmiCwbEnable;
}

/**
  Update Thc policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateThcPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  THC_CONFIG    *ThcConfig;
  EFI_STATUS    Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gThcConfigGuid, (VOID *) &ThcConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  ThcConfig->ThcPort[0].Assignment         = FspsUpd->FspsConfig.ThcPort0Assignment;
  ThcConfig->ThcPort[0].InterruptPinMuxing = FspsUpd->FspsConfig.ThcPort0InterruptPinMuxing;
  ThcConfig->ThcPort[1].Assignment         = FspsUpd->FspsConfig.ThcPort1Assignment;
  ThcConfig->ThcPort[1].InterruptPinMuxing = FspsUpd->FspsConfig.ThcPort1InterruptPinMuxing;

}

/**
  Update IEH policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateIehPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  IEH_CONFIG        *IehConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gIehConfigGuid, (VOID *) &IehConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  IehConfig->Mode = FspsUpd->FspsConfig.IehMode;
}


/**
  Update FlashProtection policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateFlashProtectionPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINTN                        Index;
  PCH_FLASH_PROTECTION_CONFIG  *FlashProtectionConfig;
  EFI_STATUS                   Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gFlashProtectionConfigGuid, (VOID *) &FlashProtectionConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  for (Index = 0; Index < PCH_FLASH_PROTECTED_RANGES; Index ++) {
    FlashProtectionConfig->ProtectRange[Index].WriteProtectionEnable = FspsUpd->FspsConfig.PchWriteProtectionEnable[Index];
    FlashProtectionConfig->ProtectRange[Index].ReadProtectionEnable  = FspsUpd->FspsConfig.PchReadProtectionEnable[Index];
    FlashProtectionConfig->ProtectRange[Index].ProtectedRangeLimit   = FspsUpd->FspsConfig.PchProtectedRangeLimit[Index];
    FlashProtectionConfig->ProtectRange[Index].ProtectedRangeBase    = FspsUpd->FspsConfig.PchProtectedRangeBase[Index];
  }
}

/**
  Update IO APIC policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateIoApicPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PCH_IOAPIC_CONFIG *IoApicConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gIoApicConfigGuid, (VOID *) &IoApicConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  IoApicConfig->IoApicEntry24_119          = FspsUpd->FspsConfig.PchIoApicEntry24_119;
  IoApicConfig->Enable8254ClockGating      = FspsUpd->FspsConfig.Enable8254ClockGating;
  IoApicConfig->Enable8254ClockGatingOnS3  = FspsUpd->FspsConfig.Enable8254ClockGatingOnS3;
  IoApicConfig->IoApicId                   = FspsUpd->FspsConfig.PchIoApicId;
}

/**
  Update P2sb policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateP2sbPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PCH_P2SB_CONFIG   *P2sbConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gP2sbConfigGuid, (VOID *) &P2sbConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  P2sbConfig->SbAccessUnlock  = FspsUpd->FspsConfig.PchSbAccessUnlock;
}

/**
  Update PCH General policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdatePchGeneralPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PCH_GENERAL_CONFIG *PchGeneralConfig;
  EFI_STATUS         Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  PchGeneralConfig->Crid                 = FspsUpd->FspsConfig.PchCrid;
  PchGeneralConfig->LegacyIoLowLatency   = FspsUpd->FspsConfig.PchLegacyIoLowLatency;
  PchGeneralConfig->PchMasterClockGating = FspsUpd->FspsConfig.PchMasterClockGating;
  PchGeneralConfig->PchMasterPowerGating = FspsUpd->FspsConfig.PchMasterPowerGating;
  PchGeneralConfig->SciPinMuxEnable      = FspsUpd->FspsConfig.SciPinMuxEnable;
}

/**
  Update Power Management policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdatePmPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PCH_PM_CONFIG     *PmConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  PmConfig->WakeConfig.PmeB0S5Dis         = FspsUpd->FspsConfig.PchPmPmeB0S5Dis;
  PmConfig->WakeConfig.WolEnableOverride  = FspsUpd->FspsConfig.PchPmWolEnableOverride;
  PmConfig->WakeConfig.PcieWakeFromDeepSx = FspsUpd->FspsConfig.PchPmPcieWakeFromDeepSx;
  PmConfig->WakeConfig.WoWlanEnable       = FspsUpd->FspsConfig.PchPmWoWlanEnable;
  PmConfig->WakeConfig.WoWlanDeepSxEnable = FspsUpd->FspsConfig.PchPmWoWlanDeepSxEnable;
  PmConfig->WakeConfig.LanWakeFromDeepSx  = FspsUpd->FspsConfig.PchPmLanWakeFromDeepSx;

  PmConfig->PchDeepSxPol       = FspsUpd->FspsConfig.PchPmDeepSxPol;
  PmConfig->PchSlpS3MinAssert  = FspsUpd->FspsConfig.PchPmSlpS3MinAssert;
  PmConfig->PchSlpS4MinAssert  = FspsUpd->FspsConfig.PchPmSlpS4MinAssert;
  PmConfig->PchSlpSusMinAssert = FspsUpd->FspsConfig.PchPmSlpSusMinAssert;
  PmConfig->PchSlpAMinAssert   = FspsUpd->FspsConfig.PchPmSlpAMinAssert;
  PmConfig->SlpStrchSusUp        = FspsUpd->FspsConfig.PchPmSlpStrchSusUp;
  PmConfig->SlpLanLowDc          = FspsUpd->FspsConfig.PchPmSlpLanLowDc;
  PmConfig->PwrBtnOverridePeriod = FspsUpd->FspsConfig.PchPmPwrBtnOverridePeriod;
  PmConfig->DisableEnergyReport  = FspsUpd->FspsConfig.PchPmDisableEnergyReport;
  PmConfig->DisableDsxAcPresentPulldown = FspsUpd->FspsConfig.PchPmDisableDsxAcPresentPulldown;
  PmConfig->DisableNativePowerButton = FspsUpd->FspsConfig.PchPmDisableNativePowerButton;
  PmConfig->PowerButtonDebounce  = FspsUpd->FspsConfig.PmcPowerButtonDebounce;
  PmConfig->MeWakeSts            = FspsUpd->FspsConfig.PchPmMeWakeSts;
  PmConfig->WolOvrWkSts          = FspsUpd->FspsConfig.PchPmWolOvrWkSts;
  PmConfig->EnableTcoTimer       = FspsUpd->FspsConfig.EnableTcoTimer;
  PmConfig->EnableTimedGpio0     = FspsUpd->FspsConfig.EnableTimedGpio0;
  PmConfig->EnableTimedGpio1     = FspsUpd->FspsConfig.EnableTimedGpio1;
  PmConfig->VrAlert              = FspsUpd->FspsConfig.PchPmVrAlert;
  PmConfig->PchPwrCycDur         = FspsUpd->FspsConfig.PchPmPwrCycDur;
  PmConfig->PciePllSsc           = FspsUpd->FspsConfig.PchPmPciePllSsc;
  PmConfig->PmcDbgMsgEn           = FspsUpd->FspsConfig.PmcDbgMsgEn;
  PmConfig->PsOnEnable            = FspsUpd->FspsConfig.PsOnEnable;
  PmConfig->CpuC10GatePinEnable   = FspsUpd->FspsConfig.PmcCpuC10GatePinEnable;
  PmConfig->ModPhySusPgEnable     = FspsUpd->FspsConfig.PmcModPhySusPgEnable;
  PmConfig->Usb2PhySusPgEnable    = FspsUpd->FspsConfig.PmcUsb2PhySusPgEnable;
  PmConfig->OsIdleEnable          = 0;
  PmConfig->GrTscEnable           = FspsUpd->FspsConfig.PmcGrTscEnable;
  PmConfig->LpmS0ixSubStateEnable.Val = FspsUpd->FspsConfig.PmcLpmS0ixSubStateEnableMask;
  PmConfig->V1p05PhyExtFetControlEn = FspsUpd->FspsConfig.PmcV1p05PhyExtFetControlEn;
  PmConfig->V1p05IsExtFetControlEn = FspsUpd->FspsConfig.PmcV1p05IsExtFetControlEn;
  PmConfig->S0ixAutoDemotion       = FspsUpd->FspsConfig.PchS0ixAutoDemotion;
  PmConfig->LatchEventsC10Exit     = FspsUpd->FspsConfig.PchPmLatchEventsC10Exit;

}
/**
  Update Thermal policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateThermalPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  UINTN             Index;
  THERMAL_CONFIG    *ThermalConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gThermalConfigGuid, (VOID *) &ThermalConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  ThermalConfig->PchHotEnable = FspsUpd->FspsConfig.PchHotEnable;

  ThermalConfig->TTLevels.T0Level            = FspsUpd->FspsConfig.PchT0Level;
  ThermalConfig->TTLevels.T1Level            = FspsUpd->FspsConfig.PchT1Level;
  ThermalConfig->TTLevels.T2Level            = FspsUpd->FspsConfig.PchT2Level;
  ThermalConfig->TTLevels.TTEnable           = FspsUpd->FspsConfig.PchTTEnable;
  ThermalConfig->TTLevels.TTState13Enable    = FspsUpd->FspsConfig.PchTTState13Enable;
  ThermalConfig->TTLevels.TTLock             = FspsUpd->FspsConfig.PchTTLock;
  ThermalConfig->TTLevels.SuggestedSetting   = FspsUpd->FspsConfig.TTSuggestedSetting;
  ThermalConfig->TTLevels.PchCrossThrottling = FspsUpd->FspsConfig.TTCrossThrottling;

  ThermalConfig->DmiHaAWC.DmiTsawEn        = FspsUpd->FspsConfig.PchDmiTsawEn;
  ThermalConfig->DmiHaAWC.SuggestedSetting = FspsUpd->FspsConfig.DmiSuggestedSetting;
  ThermalConfig->DmiHaAWC.TS0TW            = FspsUpd->FspsConfig.DmiTS0TW;
  ThermalConfig->DmiHaAWC.TS1TW            = FspsUpd->FspsConfig.DmiTS1TW;
  ThermalConfig->DmiHaAWC.TS2TW            = FspsUpd->FspsConfig.DmiTS2TW;
  ThermalConfig->DmiHaAWC.TS3TW            = FspsUpd->FspsConfig.DmiTS3TW;

  ThermalConfig->MemoryThrottling.Enable = FspsUpd->FspsConfig.PchMemoryThrottlingEnable;

  for (Index = 0; Index < 2; Index++) {
    ThermalConfig->MemoryThrottling.TsGpioPinSetting[Index].PmsyncEnable     = FspsUpd->FspsConfig.PchMemoryPmsyncEnable[Index];
    ThermalConfig->MemoryThrottling.TsGpioPinSetting[Index].C0TransmitEnable = FspsUpd->FspsConfig.PchMemoryC0TransmitEnable[Index];
    ThermalConfig->MemoryThrottling.TsGpioPinSetting[Index].PinSelection     = FspsUpd->FspsConfig.PchMemoryPinSelection[Index];
  }

  ThermalConfig->PchHotLevel = FspsUpd->FspsConfig.PchTemperatureHotLevel;

}

/**
  Update Psf policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdatePsfPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PSF_CONFIG        *PsfConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPsfConfigGuid, (VOID *) &PsfConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  PsfConfig->TccEnable = FspsUpd->FspsConfig.PsfTccEnable;
}

/**
  Update Fusa policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateFusaPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
#if FixedPcdGet8(PcdEmbeddedEnable) == 1
  FUSA_CONFIG       *FusaConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gFusaConfigGuid, (VOID *) &FusaConfig);
  if (EFI_ERROR (Status)) {
    return;
  }

  FusaConfig->PsfFusaConfigEnable = FspsUpd->FspsConfig.PsfFusaConfigEnable;
#endif
}


/**
  Update Fivr policies.

  @param[in] SiPolicy  Pointer to SI_POLICY_PPI
  @param[in] FspsUpd   Pointer to FSPS_UPD
**/
STATIC
VOID
FspUpdateFivrPolicy (
  IN SI_POLICY_PPI  *SiPolicy,
  IN FSPS_UPD       *FspsUpd
  )
{
  PCH_FIVR_CONFIG   *FivrConfig;
  EFI_STATUS        Status;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gFivrConfigGuid, (VOID *) &FivrConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  FivrConfig->ExtV1p05Rail.EnabledStates           = FspsUpd->FspsConfig.PchFivrExtV1p05RailEnabledStates;
  FivrConfig->ExtV1p05Rail.SupportedVoltageStates  = FspsUpd->FspsConfig.PchFivrExtV1p05RailSupportedVoltageStates;
  FivrConfig->ExtV1p05Rail.Voltage                 = FspsUpd->FspsConfig.PchFivrExtV1p05RailVoltage;
  FivrConfig->ExtV1p05Rail.IccMax                  = FspsUpd->FspsConfig.PchFivrExtV1p05RailIccMax;
  FivrConfig->ExtV1p05Rail.CtrlRampTmr   = FspsUpd->FspsConfig.PchFivrExtV1p05RailCtrlRampTmr;
  FivrConfig->ExtVnnRail.EnabledStates          = FspsUpd->FspsConfig.PchFivrExtVnnRailEnabledStates;
  FivrConfig->ExtVnnRail.SupportedVoltageStates = FspsUpd->FspsConfig.PchFivrExtVnnRailSupportedVoltageStates;
  FivrConfig->ExtVnnRail.Voltage                = FspsUpd->FspsConfig.PchFivrExtVnnRailVoltage;
  FivrConfig->ExtVnnRail.IccMax                 = FspsUpd->FspsConfig.PchFivrExtVnnRailIccMax;
  FivrConfig->ExtVnnRail.CtrlRampTmr     = FspsUpd->FspsConfig.PchFivrExtVnnRailCtrlRampTmr;
  FivrConfig->ExtVnnRailSx.EnabledStates = FspsUpd->FspsConfig.PchFivrExtVnnRailSxEnabledStates;
  FivrConfig->ExtVnnRailSx.Voltage       = FspsUpd->FspsConfig.PchFivrExtVnnRailSxVoltage;
  FivrConfig->ExtVnnRailSx.IccMax        = FspsUpd->FspsConfig.PchFivrExtVnnRailSxIccMax;

  FivrConfig->VccinAux.LowToHighCurModeVolTranTime = FspsUpd->FspsConfig.PchFivrVccinAuxLowToHighCurModeVolTranTime;
  FivrConfig->VccinAux.RetToHighCurModeVolTranTime = FspsUpd->FspsConfig.PchFivrVccinAuxRetToHighCurModeVolTranTime;
  FivrConfig->VccinAux.RetToLowCurModeVolTranTime  = FspsUpd->FspsConfig.PchFivrVccinAuxRetToLowCurModeVolTranTime;
  FivrConfig->VccinAux.OffToHighCurModeVolTranTime = FspsUpd->FspsConfig.PchFivrVccinAuxOffToHighCurModeVolTranTime;
  FivrConfig->FivrDynPm                            = FspsUpd->FspsConfig.PchFivrDynPm;
}

/**
  This function performs PCH PEI Policy update.

  @param[in, out] SiPolicy       The SI Policy PPI instance
  @param[in]      FspsUpd        The pointer of FspsUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiPchPolicy (
  IN OUT SI_POLICY_PPI     *SiPolicy,
  IN     FSPS_UPD          *FspsUpd
  )
{
  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP UpdatePeiPchPolicy\n"));

  FspUpdateGbePolicy (SiPolicy, FspsUpd);
  FspUpdateTsnPolicy (SiPolicy, FspsUpd);
  FspUpdateHdAudioPolicy (SiPolicy, FspsUpd);
  FspUpdateCnviPolicy (SiPolicy, FspsUpd);
  FspUpdateHsioPolicy (SiPolicy, FspsUpd);
  FspUpdateFiaPolicy (SiPolicy, FspsUpd);
  FspUpdateEspiPolicy (SiPolicy, FspsUpd);
  FspUpdateSdCardPolicy (SiPolicy, FspsUpd);
  FspUpdateEmmcPolicy (SiPolicy, FspsUpd);
  FspUpdateUfsPolicy (SiPolicy, FspsUpd);
  FspUpdatePsePolicy (SiPolicy, FspsUpd);
  FspUpdateSiipPolicy (SiPolicy, FspsUpd);
  FspUpdateSataPolicy (SiPolicy, FspsUpd);
  FspUpdateUsbPolicy (SiPolicy, FspsUpd);
  FspUpdateUsb2PhyPolicy (SiPolicy, FspsUpd);
  FspUpdateUsb3HsioPolicy (SiPolicy, FspsUpd);
  FspUpdatePcieRpPolicy (SiPolicy, FspsUpd);
  FspUpdateSerialIoPolicy (SiPolicy, FspsUpd);
  FspUpdateInterruptPolicy (SiPolicy, FspsUpd);
  FspUpdateLockDownPolicy (SiPolicy, FspsUpd);
  FspUpdateRtcPolicy (SiPolicy, FspsUpd);
  FspUpdateDmiPolicy (SiPolicy, FspsUpd);
  FspUpdateThcPolicy (SiPolicy, FspsUpd);
  FspUpdateIehPolicy (SiPolicy, FspsUpd);
  FspUpdateFlashProtectionPolicy (SiPolicy, FspsUpd);
  FspUpdateIoApicPolicy (SiPolicy, FspsUpd);
  FspUpdateP2sbPolicy (SiPolicy, FspsUpd);
  FspUpdatePchGeneralPolicy (SiPolicy, FspsUpd);
  FspUpdatePmPolicy (SiPolicy, FspsUpd);
  FspUpdateThermalPolicy (SiPolicy, FspsUpd);
  FspUpdatePsfPolicy (SiPolicy, FspsUpd);
  FspUpdateFusaPolicy (SiPolicy, FspsUpd);

  FspUpdateFivrPolicy (SiPolicy, FspsUpd);

  return EFI_SUCCESS;
}


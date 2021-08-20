/** @file
  Initializes/updates PCH related HOBs in PEI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2020 Intel Corporation.

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

#include "PchInitPei.h"
#include <Library/GbeLib.h>
#include <Library/PeiPmcPrivateLib.h>
#include <PchPcieRpInfo.h>
#include <Register/PchPcieRpRegs.h>
#include <Register/P2sbRegs.h>
#include <Register/PchPcieRpMultiVcRegs.h>
#include <Register/PchPcieRpMultiVcRegs.h>

/**
  The function update pch info hob in the end of PchInit.
**/
VOID
BuildPchInfoHob (
  VOID
  )
{
  EFI_STATUS  Status;
  UINT32      StrapFuseCfg;
  UINT32      MaxCtrl;
  UINT32      CtrlIndex;
  UINT32      RpIndex;
  UINT8       TsnIndex;
  UINT32      SpxPcd;
  PCH_INFO_HOB *PchInfoHob;
  BOOLEAN     CridSupport;
  UINT8       OrgRid;
  UINT8       NewRid;
  UINT8       NumTsnControllers;
  UINT8       LaneNum;

  PchInfoHob = BuildGuidHob (&gPchInfoHobGuid, sizeof (PCH_INFO_HOB));
  ASSERT (PchInfoHob != 0);
  if (PchInfoHob == NULL) {
    return;
  }

  PchInfoHob->Revision = PCH_INFO_HOB_REVISION;

  PchInfoHob->PciePortFuses = 0;

  PchInfoHob->PciePortLaneEnabled = 0;
  for (RpIndex = 0; RpIndex < GetPchMaxPciePortNum (); RpIndex++) {
    if (PchFiaIsPcieRootPortLaneConnected (RpIndex, 0)) {
      PchInfoHob->PciePortLaneEnabled |= BIT0 << RpIndex;
    }
  }

  //
  // Get PCIE Port disable value for each RP
  //
  MaxCtrl = GetPchMaxPcieControllerNum ();

  for (CtrlIndex = 0; CtrlIndex < MaxCtrl; CtrlIndex++) {
    if (IsCtrlMultiVC (CtrlIndex)) {
      SpxPcd = PchPcrRead32 (PchGetPcieControllerSbiPid (CtrlIndex), R_SPX_MVC_PCR_PCD);
      for (RpIndex = 0; RpIndex < GetControllerMaxRp ((UINT8) CtrlIndex); RpIndex++) {
        if ((SpxPcd & (B_SPX_MVC_PCR_PCD_P1D << RpIndex)) != 0) {
          PchInfoHob->PciePortFuses |= BIT0 << (RpIndex + GetControllerFirstRpIndex (CtrlIndex));
        }
      }
    } else {
      SpxPcd = PchPcrRead32 (PchGetPcieControllerSbiPid (CtrlIndex), R_SPX_PCR_PCD);
      for (RpIndex = 0; RpIndex < GetControllerMaxRp ((UINT8)CtrlIndex); RpIndex++) {
        if ((SpxPcd & (B_SPX_PCR_PCD_P1D << RpIndex)) != 0) {
          PchInfoHob->PciePortFuses |= BIT0 << (RpIndex + GetControllerFirstRpIndex (CtrlIndex));
        }
      }
    }
  }

  MaxCtrl = GetPchMaxPcieControllerNum ();
  for (CtrlIndex = 0; CtrlIndex < MaxCtrl; CtrlIndex++) {
    if (PchInfoHob->PciePortFuses & (BIT0 << GetControllerFirstRpIndex (CtrlIndex))) {
      PchInfoHob->PcieControllerCfg[CtrlIndex] = 0;
    } else {
      Status = PchSbiRpPciRead32 (GetControllerFirstRpIndex (CtrlIndex) , R_PCH_PCIE_CFG_STRPFUSECFG, &StrapFuseCfg);
      ASSERT_EFI_ERROR (Status);
      PchInfoHob->PcieControllerCfg[CtrlIndex] = (UINT8) ((StrapFuseCfg & B_PCH_PCIE_CFG_STRPFUSECFG_RPC) >> N_PCH_PCIE_CFG_STRPFUSECFG_RPC);
    }
  }

  if (IsGbePresent ()) {
    PchInfoHob->GbePciePortNumber  = (UINT8)PchFiaGetGbePortNumber ();
  } else {
    PchInfoHob->GbePciePortNumber  = 0;
  }


  LaneNum = 0;
  NumTsnControllers = PCH_MAX_TSN_GBE_CONTROLLERS;

  for (TsnIndex = 0; TsnIndex < NumTsnControllers; TsnIndex++) {
    PchInfoHob->TsnPortLaneEnabled[TsnIndex] = PchFiaGetTsnLaneNum (TsnIndex, &LaneNum);
    PchInfoHob->TsnPortLaneNum[TsnIndex]     = LaneNum;
  }

  PchInfoHob->Thc0Strap = PmcIsThcEnabled (0);

  PchInfoHob->HpetBusNum    = V_P2SB_CFG_HBDF_BUS;
  PchInfoHob->HpetDevNum    = V_P2SB_CFG_HBDF_DEV;
  PchInfoHob->HpetFuncNum   = V_P2SB_CFG_HBDF_FUNC;
  PchInfoHob->IoApicBusNum  = V_P2SB_CFG_IBDF_BUS;
  PchInfoHob->IoApicDevNum  = V_P2SB_CFG_IBDF_DEV;
  PchInfoHob->IoApicFuncNum = V_P2SB_CFG_IBDF_FUNC;

  //
  // This must be done before PMC hidden.
  //
  CridSupport = FALSE;
  OrgRid      = 0;
  NewRid      = 0;
  Status = PmcDetectCrid0 (&CridSupport, &OrgRid, &NewRid);
  DEBUG ((DEBUG_INFO, "CridSupport = %x %x %x\n", CridSupport, OrgRid, NewRid));
  if (!EFI_ERROR (Status)) {
    PchInfoHob->CridSupport = CridSupport;
    PchInfoHob->CridOrgRid  = OrgRid;
    PchInfoHob->CridNewRid  = NewRid;
  }
}

/**
  The function update pch config hob in the end of PchInit.

  @param[in]      SiPolicy               The SI Policy PPI instance
**/
VOID
BuildPchConfigHob (
  IN     SI_POLICY_PPI          *SiPolicy
  )
{
  PCH_CONFIG_HOB               *PchConfigHob;
  SI_PREMEM_POLICY_PPI         *SiPreMemPolicy;
  PCH_SMBUS_PREMEM_CONFIG      *SmbusPreMemConfig;
  PCH_GENERAL_CONFIG           *PchGeneralConfig;
  PCH_INTERRUPT_CONFIG         *InterruptConfig;
  SERIAL_IO_CONFIG             *SerialIoConfig;
  PCH_PCIE_CONFIG              *PcieRpConfig;
  SCS_EMMC_CONFIG              *EmmcConfig;
  SCS_SDCARD_CONFIG            *SdCardConfig;
  HDAUDIO_CONFIG               *HdAudioConfig;
  HDAUDIO_PREMEM_CONFIG        *HdAudioPreMemConfig;
  PCH_DMI_CONFIG               *PchDmiConfig;
  PCH_LOCK_DOWN_CONFIG         *LockDownConfig;
  PCH_PM_CONFIG                *PmConfig;
  SATA_CONFIG                  *SataConfig;
  PCH_FLASH_PROTECTION_CONFIG  *FlashProtectionConfig;
  THC_CONFIG                   *ThcConfig;
  GBE_CONFIG                   *GbeConfig;
  PCH_TRACE_HUB_PREMEM_CONFIG  *PchTraceHubPreMemConfig;
  PCH_FIVR_CONFIG              *FivrConfig;
  EFI_STATUS                   Status;
  UINT32                       SataCtrlIndex;
  PCH_ESPI_CONFIG              *EspiConfig;
  USB_CONFIG                   *UsbConfig;
  PSE_CONFIG                   *PseConfig;
  UINT8                        Index;
  PCH_PCIE_RP_PREMEM_CONFIG    *PchPcieRpPreMemConfig;

  PchConfigHob = BuildGuidHob (&gPchConfigHobGuid, sizeof (PCH_CONFIG_HOB));
  ASSERT (PchConfigHob != 0);
  if (PchConfigHob == NULL) {
    return;
  }

  //
  // Get Policy settings through the SiPreMemPolicy PPI
  //
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicy
             );
  if (Status != EFI_SUCCESS) {
    //
    // SI_PREMEM_POLICY_PPI must be installed at this point
    //
    ASSERT (FALSE);
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gSmbusPreMemConfigGuid, (VOID *) &SmbusPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPchTraceHubPreMemConfigGuid, (VOID *) &PchTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gHdAudioPreMemConfigGuid, (VOID *) &HdAudioPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPcieRpPreMemConfigGuid, (VOID *) &PchPcieRpPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gInterruptConfigGuid, (VOID *) &InterruptConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSerialIoConfigGuid, (VOID *) &SerialIoConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchPcieRpConfigGuid, (VOID *) &PcieRpConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gEmmcConfigGuid, (VOID *) &EmmcConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gSdCardConfigGuid, (VOID *) &SdCardConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gHdAudioConfigGuid, (VOID *) &HdAudioConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchDmiConfigGuid, (VOID *) &PchDmiConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gLockDownConfigGuid, (VOID *) &LockDownConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPmConfigGuid, (VOID *) &PmConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gFlashProtectionConfigGuid, (VOID *) &FlashProtectionConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gGbeConfigGuid, (VOID *) &GbeConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gEspiConfigGuid, (VOID *) &EspiConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gThcConfigGuid, (VOID *) &ThcConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gFivrConfigGuid, (VOID *) &FivrConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gUsbConfigGuid, (VOID *) &UsbConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPolicy, &gPseConfigGuid, (VOID *) &PseConfig);
  ASSERT_EFI_ERROR (Status);

  PchConfigHob->Smbus.NumRsvdSmbusAddresses = SmbusPreMemConfig->NumRsvdSmbusAddresses;
  CopyMem (
    PchConfigHob->Smbus.RsvdSmbusAddressTable,
    SmbusPreMemConfig->RsvdSmbusAddressTable,
    sizeof (PchConfigHob->Smbus.RsvdSmbusAddressTable)
    );

  PchConfigHob->General.Crid = PchGeneralConfig->Crid;
  PchConfigHob->Interrupt.NumOfDevIntConfig = InterruptConfig->NumOfDevIntConfig;
  PchConfigHob->Interrupt.GpioIrqRoute = InterruptConfig->GpioIrqRoute;
  CopyMem (
    PchConfigHob->Interrupt.DevIntConfig,
    InterruptConfig->DevIntConfig,
    sizeof (PchConfigHob->Interrupt.DevIntConfig)
    );

 CopyMem (
    PchConfigHob->SerialIo.SpiDeviceConfig,
    SerialIoConfig->SpiDeviceConfig,
    sizeof (PchConfigHob->SerialIo.SpiDeviceConfig)
    );
  CopyMem (
    PchConfigHob->SerialIo.UartDeviceConfig,
    SerialIoConfig->UartDeviceConfig,
    sizeof (PchConfigHob->SerialIo.UartDeviceConfig)
    );
  CopyMem (
    PchConfigHob->SerialIo.I2cDeviceConfig,
    SerialIoConfig->I2cDeviceConfig,
    sizeof (PchConfigHob->SerialIo.I2cDeviceConfig)
    );
  CopyMem (
    PchConfigHob->Thc.ThcPort,
    ThcConfig->ThcPort,
    sizeof (PchConfigHob->Thc.ThcPort)
    );
  CopyMem (
    PchConfigHob->PcieRp.RootPort,
    PcieRpConfig->RootPort,
    sizeof (PchConfigHob->PcieRp.RootPort)
    );
  CopyMem (
    PchConfigHob->PcieRp.PcieClock,
    PchPcieRpPreMemConfig->PcieClock,
    sizeof (PchPcieRpPreMemConfig->PcieClock)
    );

  PchConfigHob->SdCard.Enabled = SdCardConfig->Enable;
  PchConfigHob->Emmc.Enabled = EmmcConfig->Enable;
  PchConfigHob->HdAudio.DspEnable             = HdAudioPreMemConfig->DspEnable;
  PchConfigHob->HdAudio.DspUaaCompliance      = HdAudioPreMemConfig->DspUaaCompliance;
  PchConfigHob->HdAudio.AudioLinkSndw1        = HdAudioPreMemConfig->AudioLinkSndw[0].Enable;
  PchConfigHob->HdAudio.AudioLinkSndw2        = HdAudioPreMemConfig->AudioLinkSndw[1].Enable;
  PchConfigHob->HdAudio.AudioLinkSndw3        = HdAudioPreMemConfig->AudioLinkSndw[2].Enable;
  PchConfigHob->HdAudio.AudioLinkSndw4        = HdAudioPreMemConfig->AudioLinkSndw[3].Enable;
  PchConfigHob->HdAudio.CodecSxWakeCapability = HdAudioConfig->CodecSxWakeCapability;
  PchConfigHob->HdAudio.Pme                   = HdAudioConfig->Pme;
  PchConfigHob->LockDown.GlobalSmi = LockDownConfig->GlobalSmi;
  PchConfigHob->LockDown.BiosInterface = LockDownConfig->BiosInterface;
  PchConfigHob->LockDown.BiosLock = LockDownConfig->BiosLock;
  PchConfigHob->Pm.PsOnEnable            = PmConfig->PsOnEnable;
  PchConfigHob->Pm.EnableTimedGpio0      = PmConfig->EnableTimedGpio0;
  PchConfigHob->Pm.EnableTimedGpio1      = PmConfig->EnableTimedGpio1;
  PchConfigHob->Espi.BmeMasterSlaveEnabled = EspiConfig->BmeMasterSlaveEnabled;
  for (SataCtrlIndex = 0; SataCtrlIndex < MaxSataControllerNum (); SataCtrlIndex++) {
    SataConfig = GetPchSataConfig (SiPolicy, SataCtrlIndex);
    PchConfigHob->Sata[SataCtrlIndex].Enable = SataConfig->Enable;
    PchConfigHob->Sata[SataCtrlIndex].TestMode = SataConfig->TestMode;
    CopyMem (
      PchConfigHob->Sata[SataCtrlIndex].PortSettings,
      SataConfig->PortSettings,
      sizeof (PchConfigHob->Sata[SataCtrlIndex].PortSettings)
      );
  }
  CopyMem (
    PchConfigHob->ProtectRange,
    FlashProtectionConfig->ProtectRange,
    sizeof (PchConfigHob->ProtectRange)
    );

  PchConfigHob->PchTraceHub.PchTraceHubMode = PchTraceHubPreMemConfig->TraceHub.EnableMode;

  PchConfigHob->Fivr.ExtVnnRailSx.EnabledStates = FivrConfig->ExtVnnRailSx.EnabledStates;
  PchConfigHob->Fivr.ExtVnnRailSx.Voltage = FivrConfig->ExtVnnRailSx.Voltage;
  PchConfigHob->Fivr.ExtVnnRailSx.IccMax = FivrConfig->ExtVnnRailSx.IccMax;

  PchConfigHob->Usb.EnableUsbComplianceMode = UsbConfig->EnableComplianceMode;
  for (Index = 0; Index < GetPchXhciMaxUsb2PortNum (); Index++) {
    PchConfigHob->Usb.PortUsb20[Index].Enable = UsbConfig->PortUsb20[Index].Enable;
    PchConfigHob->Usb.PortUsb20[Index].OverCurrentPin = UsbConfig->PortUsb20[Index].OverCurrentPin;
  }
  for (Index = 0; Index < GetPchXhciMaxUsb3PortNum (); Index++) {
    PchConfigHob->Usb.PortUsb30[Index].Enable = UsbConfig->PortUsb30[Index].Enable;
    PchConfigHob->Usb.PortUsb30[Index].OverCurrentPin = UsbConfig->PortUsb30[Index].OverCurrentPin;
  }

  for (Index = 0; Index < GetPchMaxPseDmaControllersNum (); Index++) {
    PchConfigHob->Pse.PseDmaEnable[Index] = PseConfig->Dma[Index].OwnerShip;
  }

}

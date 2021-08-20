/** @file
  This file provides services for Usb policy function

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
#include <Usb2PhyConfig.h>
#include <Usb3HsioConfig.h>
#include <UsbConfig.h>

/**
  Print USB_CONFIG to serial.

  @param[in] SiPolicyPpi  Pointer to SI_POLICY_PPI
**/
VOID
UsbConfPrintConfig (
  IN SI_POLICY_PPI  *SiPolicyPpi
  )
{
  USB_CONFIG    *UsbConfig;
  EFI_STATUS    Status;
  UINT32        Index;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gUsbConfigGuid, (VOID *) &UsbConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ USB Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " EnableComplianceMode  = %x\n", UsbConfig->EnableComplianceMode));
  DEBUG ((DEBUG_INFO, " PdoProgramming        = %x\n", UsbConfig->PdoProgramming));
  DEBUG ((DEBUG_INFO, " OverCurrentEnable     = %x\n", UsbConfig->OverCurrentEnable));
  DEBUG ((DEBUG_INFO, " XhciOcLock            = %x\n", UsbConfig->XhciOcLock));

  for (Index = 0; Index < GetPchUsb2MaxPhysicalPortNum (); Index++) {
    DEBUG ((DEBUG_INFO, " PortUsb20[%d].Enabled        = %x\n", Index, UsbConfig->PortUsb20[Index].Enable));
    DEBUG ((DEBUG_INFO, " PortUsb20[%d].OverCurrentPin = OC%x\n", Index, UsbConfig->PortUsb20[Index].OverCurrentPin));
  }

  for (Index = 0; Index < GetPchXhciMaxUsb3PortNum (); Index++) {
    DEBUG ((DEBUG_INFO, " PortUsb30[%d] Enabled        = %x\n", Index, UsbConfig->PortUsb30[Index].Enable));
    DEBUG ((DEBUG_INFO, " PortUsb30[%d].OverCurrentPin = OC%x\n", Index, UsbConfig->PortUsb30[Index].OverCurrentPin));
  }

  DEBUG ((DEBUG_INFO, " LtrOverrideEnable             = %x\n", UsbConfig->LtrOverrideEnable));
  if (UsbConfig->LtrOverrideEnable) {
    DEBUG ((DEBUG_INFO, " LtrHighIdleTimeOverride       = 0x%4X\n", UsbConfig->LtrHighIdleTimeOverride));
    DEBUG ((DEBUG_INFO, " LtrMediumIdleTimeOverride     = 0x%4X\n", UsbConfig->LtrMediumIdleTimeOverride));
    DEBUG ((DEBUG_INFO, " LtrLowIdleTimeOverride        = 0x%4X\n", UsbConfig->LtrLowIdleTimeOverride));
  }

  DEBUG ((DEBUG_INFO, " UsbClockGatingEnable             = %x\n", UsbConfig->UsbClockGatingEnable));
  DEBUG ((DEBUG_INFO, " UsbPowerGatingEnable             = %x\n", UsbConfig->UsbPowerGatingEnable));
  DEBUG ((DEBUG_INFO, " USB3LinkSpeed                    = %x\n", UsbConfig->USB3LinkSpeed));

  DEBUG ((DEBUG_INFO, " XdciConfig.Enable= %x\n", UsbConfig->XdciConfig.Enable));

}

/**
  Print USB2_PHY_CONFIG to serial.

  @param[in] SiPolicyPpi  Pointer to SI_POLICY_PPI
**/
VOID
Usb2PhyPrintConfig (
  IN SI_POLICY_PPI  *SiPolicyPpi
  )
{
  USB2_PHY_CONFIG   *Usb2PhyConfig;
  EFI_STATUS        Status;
  UINT32            Index;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gUsb2PhyConfigGuid, (VOID *) &Usb2PhyConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ USB2 PHY Config ------------------\n"));

  for (Index = 0; Index < GetPchUsb2MaxPhysicalPortNum (); Index++) {
    DEBUG ((DEBUG_INFO, " Port[%d].Petxiset   = %x\n", Index, Usb2PhyConfig->Port[Index].Petxiset));
    DEBUG ((DEBUG_INFO, " Port[%d].Txiset     = %x\n", Index, Usb2PhyConfig->Port[Index].Txiset));
    DEBUG ((DEBUG_INFO, " Port[%d].Predeemp   = %x\n", Index, Usb2PhyConfig->Port[Index].Predeemp));
    DEBUG ((DEBUG_INFO, " Port[%d].Pehalfbit  = %x\n", Index, Usb2PhyConfig->Port[Index].Pehalfbit));
  }
}

/**
  Print USB3_HSIO_CONFIG to serial.

  @param[in] SiPolicyPpi  Pointer to SI_POLICY_PPI
**/
VOID
Usb3HsioPrintConfig (
  IN SI_POLICY_PPI  *SiPolicyPpi
  )
{
  USB3_HSIO_CONFIG  *Usb3HsioConfig;
  EFI_STATUS        Status;
  UINT32            Index;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gUsb3HsioConfigGuid, (VOID *) &Usb3HsioConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ USB3 HSIO Config ------------------\n"));

  for (Index = 0; Index < GetPchXhciMaxUsb3PortNum (); Index++) {
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxDeEmphEnable       = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxDeEmphEnable));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxDeEmph             = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxDeEmph));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxDownscaleAmpEnable = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxDownscaleAmpEnable));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxDownscaleAmp       = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxDownscaleAmp));

    DEBUG ((DEBUG_INFO, " Port[%d].HsioCtrlAdaptOffsetCfgEnable   = %x\n", Index, Usb3HsioConfig->Port[Index].HsioCtrlAdaptOffsetCfgEnable));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioCtrlAdaptOffsetCfg         = %x\n", Index, Usb3HsioConfig->Port[Index].HsioCtrlAdaptOffsetCfg));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioFilterSelNEnable           = %x\n", Index, Usb3HsioConfig->Port[Index].HsioFilterSelNEnable));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioFilterSelN                 = %x\n", Index, Usb3HsioConfig->Port[Index].HsioFilterSelN));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioFilterSelPEnable           = %x\n", Index, Usb3HsioConfig->Port[Index].HsioFilterSelPEnable));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioFilterSelP                 = %x\n", Index, Usb3HsioConfig->Port[Index].HsioFilterSelP));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioOlfpsCfgPullUpDwnResEnable = %x\n", Index, Usb3HsioConfig->Port[Index].HsioOlfpsCfgPullUpDwnResEnable));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioOlfpsCfgPullUpDwnRes       = %x\n", Index, Usb3HsioConfig->Port[Index].HsioOlfpsCfgPullUpDwnRes));

    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxRate0UniqTranEnable      = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxRate0UniqTranEnable));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxRate0UniqTran            = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxRate0UniqTran));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxRate1UniqTranEnable      = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxRate1UniqTranEnable));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxRate1UniqTran            = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxRate1UniqTran));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxRate2UniqTranEnable      = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxRate2UniqTranEnable));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxRate2UniqTran            = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxRate2UniqTran));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxRate3UniqTranEnable      = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxRate3UniqTranEnable));
    DEBUG ((DEBUG_INFO, " Port[%d].HsioTxRate3UniqTran            = %x\n", Index, Usb3HsioConfig->Port[Index].HsioTxRate3UniqTran));
  }
}

/**
  Print Usb configs and serial out.

  @param[in] SiPolicyPpi            Pointer to a SI_POLICY_PPI
**/
VOID
UsbPrintConfig (
  IN SI_POLICY_PPI     *SiPolicyPpi
  )
{
  UsbConfPrintConfig (SiPolicyPpi);
  Usb2PhyPrintConfig (SiPolicyPpi);
  Usb3HsioPrintConfig (SiPolicyPpi);
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
UsbConfLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINTN           PortIndex;
  USB_CONFIG      *UsbConfig;
  UsbConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "UsbConfig->Header.GuidHob.Name = %g\n", &UsbConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "UsbConfig->Header.GuidHob.Header.HobLength = 0x%x\n", UsbConfig->Header.GuidHob.Header.HobLength));

  /********************************
    USB related configuration
  ********************************/
  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb2PortNum (); PortIndex++) {
    UsbConfig->PortUsb20[PortIndex].Enable  = TRUE;
  }

  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb3PortNum (); PortIndex++) {
    UsbConfig->PortUsb30[PortIndex].Enable  = TRUE;
  }

  //
  // BIOS should program PDO in PEI phase by default
  //
  UsbConfig->PdoProgramming = TRUE;

  UsbConfig->XhciOcLock = TRUE;

  //
  // xDCI configuration
  //
  UsbConfig->XdciConfig.Enable = FALSE;

  //
  // Compliance Mode
  //
  UsbConfig->EnableComplianceMode = FALSE;

  //
  // USB3 Link Speed
  //
  UsbConfig->USB3LinkSpeed = 0;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
Usb2PhyLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINTN             PortIndex;
  USB2_PHY_CONFIG   *Usb2PhyConfig;
  Usb2PhyConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "Usb2PhyConfig->Header.GuidHob.Name = %g\n", &Usb2PhyConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "Usb2PhyConfig->Header.GuidHob.Header.HobLength = 0x%x\n", Usb2PhyConfig->Header.GuidHob.Header.HobLength));

  /********************************
    USB2 PHY related configuration
  ********************************/
  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb2PortNum (); PortIndex++) {
    Usb2PhyConfig->Port[PortIndex].Pehalfbit = 1;
    Usb2PhyConfig->Port[PortIndex].Petxiset  = 6;
    Usb2PhyConfig->Port[PortIndex].Txiset    = 5;
    Usb2PhyConfig->Port[PortIndex].Predeemp  = 3;
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
Usb3HsioLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINTN             PortIndex;
  USB3_HSIO_CONFIG  *Usb3HsioConfig;
  Usb3HsioConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "Usb3HsioConfig->Header.GuidHob.Name = %g\n", &Usb3HsioConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "Usb3HsioConfig->Header.GuidHob.Header.HobLength = 0x%x\n", Usb3HsioConfig->Header.GuidHob.Header.HobLength));

  for (PortIndex = 0; PortIndex < GetPchXhciMaxUsb3PortNum (); PortIndex++) {
    Usb3HsioConfig->Port[PortIndex].HsioOlfpsCfgPullUpDwnRes = 3;
    Usb3HsioConfig->Port[PortIndex].HsioTxRate3UniqTran      = 0x4C;
    Usb3HsioConfig->Port[PortIndex].HsioTxRate2UniqTran      = 0x4C;
    Usb3HsioConfig->Port[PortIndex].HsioTxRate1UniqTran      = 0x4C;
    Usb3HsioConfig->Port[PortIndex].HsioTxRate0UniqTran      = 0x4C;
  }
}

STATIC COMPONENT_BLOCK_ENTRY  mUsbBlocks [] = {
  {&gUsbConfigGuid,         sizeof (USB_CONFIG),        USB_CONFIG_REVISION,        UsbConfLoadConfigDefault},
  {&gUsb2PhyConfigGuid,     sizeof (USB2_PHY_CONFIG),   USB2_PHY_CONFIG_REVISION,   Usb2PhyLoadConfigDefault},
  {&gUsb3HsioConfigGuid,    sizeof (USB3_HSIO_CONFIG),  USB3_HSIO_CONFIG_REVISION,  Usb3HsioLoadConfigDefault}
};

/**
  Get Usb config block table size.

  @retval      Size of config block
**/
UINT16
UsbGetConfigBlockTotalSize (
  VOID
  )
{
  return GetComponentConfigBlockTotalSize (&mUsbBlocks[0], sizeof (mUsbBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  Add Usb ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
UsbAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mUsbBlocks[0], sizeof (mUsbBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

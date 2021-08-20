/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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

#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/SiliconInitLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Library/BoardConfigLib.h>
#include "GpioTableEhlPostMem.h"
#include <Library/PeiServicesLib.h>
#include <Library/GpioLib.h>
#include <PlatformBoardId.h>
#include <PlatformBoardConfig.h>
#include <UsbTypeC.h>
#include "BoardSaConfigPostMem.h"
#include "PchUsbOcMappingTable.h"

/**
  Elkhartlake boards configuration init function for PEI post memory phase.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
EhlInit (
  VOID
  )
{
  UINT16            GpioCount;
  UINTN             Size;
  EFI_STATUS        Status;
  GPIO_INIT_CONFIG  *GpioTable;
  UINT16    BoardId;
  //
  // GPIO Table Init
  //
  Status = EFI_SUCCESS;
  GpioCount = 0;
  Size = 0;
  GpioTable = NULL;
  //
  // GPIO Table Init
  //
  BoardId = PcdGet16 (PcdBoardId);

  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
      GpioTable = mGpioTableEhlRvp;
      if (IsSimicsEnvironment ()) {
        DEBUG ((DEBUG_INFO, "Simics Environment : GpioTableEhlSimics Update\n"));
        GpioTable = mGpioTableEhlSimics;
      }
      break;
    case BoardIdJslLp4xType4Rvp1:
      GpioTable = mGpioTableJslEhlRvp;
      break;
    case BoardIdJslLp4xErb:
      GpioTable = mGpioTableJslLp4x;
      break;
    default:
    case BoardIdEhlLp4xType3Crb:
      GpioTable = mGpioTableEhlCrb;
      break;
  }

  if (GpioTable != NULL) {
    GetGpioTableSize (GpioTable, &GpioCount);
    //
    // Increase GpioCount for the zero terminator.
    //
    GpioCount ++;
    Size = (UINTN) (GpioCount * sizeof (GPIO_INIT_CONFIG));
    Status = PcdSetPtrS (PcdBoardGpioTable, &Size, GpioTable);
    ASSERT_EFI_ERROR (Status);
  } else {
    DEBUG ((DEBUG_ERROR, "Cannot find BoardID result in GpioTable = NULL, Assert!\n"));
    ASSERT(FALSE);
  }

  PcdSet8S (PcdSataPortsEnable0, 0x1);

  return Status;
}

/**
  Board USB related configuration init function for PEI pre-memory phase.

  @param[in]  VOID

  @retval EFI_SUCCESS   The function completed successfully.
**/
EFI_STATUS
EhlUsbConfigInit (
  VOID
  )
{
  UINT16    BoardId;
  BoardId = PcdGet16 (PcdBoardId);

  USB_OC_MAP_TABLE   *Usb2OcMappingTable;
  USB_OC_MAP_TABLE   *Usb3OcMappingTable;

  //
  // USB2 PHY settings.
  //
  PcdSet32S (PcdUsb2PhyTuningTable, (UINT32) &mUsb2PhyTuningTable);
  //
  // USB Port Over Current Pin
  //
  Usb2OcMappingTable = &mUsb2OverCurrentMappingTable;
  Usb3OcMappingTable = &mUsb3OverCurrentMappingTable;

  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
      Usb2OcMappingTable = &mEhlErbRvpUsb2OverCurrentMappingTable;
      Usb3OcMappingTable = &mEhlErbRvpUsb3OverCurrentMappingTable;
      break;
    case BoardIdEhlLp4xType3Crb:
      Usb2OcMappingTable = &mEhlCrbUsb2OverCurrentMappingTable;
      Usb3OcMappingTable = &mEhlCrbUsb3OverCurrentMappingTable;
      break;
    case BoardIdJslLp4xErb:
    case BoardIdJslLp4xType4Rvp1:
      Usb2OcMappingTable = &mJslUsb2OverCurrentMappingTable;
      Usb3OcMappingTable = &mJslUsb3OverCurrentMappingTable;
    default:
      break;
  }

  PcdSet32S (PcdUsb2OverCurrentPinTable, (UINT32) Usb2OcMappingTable);
  PcdSet32S (PcdUsb3OverCurrentPinTable, (UINT32) Usb3OcMappingTable);

  return EFI_SUCCESS;
}

/**
  Board I2C pads termination configuration init function for PEI pre-memory phase.
**/
VOID
EhlSerialIoI2cPadsTerminationInit (
  VOID
  )
{
}

/**
  Touch panel GPIO init function for PEI post memory phase.
**/
VOID
EhlTouchPanelGpioInit (
  VOID
  )
{
  UINT16    BoardId;
  BoardId = PcdGet16 (PcdBoardId);

  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
      PcdSet32S (PcdBoardGpioTableTouchPanel1,  (UINTN) mEhlTouchPanel1GpioTableRvp);
      PcdSet16S (PcdBoardGpioTableTouchPanel1Size,  sizeof(mEhlTouchPanel1GpioTableRvp)/ sizeof(GPIO_INIT_CONFIG));
      break;
    case BoardIdEhlLp4xType3Crb:
      PcdSet32S (PcdBoardGpioTableTouchPanel1,  (UINTN) mEhlTouchPanel1GpioTableCrb);
      PcdSet16S (PcdBoardGpioTableTouchPanel1Size,  sizeof(mEhlTouchPanel1GpioTableCrb)/ sizeof(GPIO_INIT_CONFIG));
      break;
    default:
      break;
  }

  return;
}

/**
  Tsn device GPIO init function for PEI post memory phase.
**/
VOID
EhlTsnDeviceGpioInit (
  VOID
  )
{
  PcdSet32S (PcdBoardGpioTablePchTsnDevice,  (UINTN) mEhlPchTsnDeviceGpioTable);
  PcdSet16S (PcdBoardGpioTablePchTsnDeviceSize,  sizeof(mEhlPchTsnDeviceGpioTable)/ sizeof(GPIO_INIT_CONFIG));
  PcdSet32S (PcdBoardGpioTablePseTsn0Device,  (UINTN) mEhlPseTsn0DeviceGpioTable);
  PcdSet16S (PcdBoardGpioTablePseTsn0DeviceSize,  sizeof(mEhlPseTsn0DeviceGpioTable)/ sizeof(GPIO_INIT_CONFIG));
  PcdSet32S (PcdBoardGpioTablePseTsn1Device,  (UINTN) mEhlPseTsn1DeviceGpioTable);
  PcdSet16S (PcdBoardGpioTablePseTsn1DeviceSize,  sizeof(mEhlPseTsn1DeviceGpioTable)/ sizeof(GPIO_INIT_CONFIG));
}

/**
  HDA VerbTable init function for PEI post memory phase.
**/
VOID
EhlHdaVerbTableInit (
  VOID
  )
{
  HDAUDIO_VERB_TABLE *VerbTable;
  HDAUDIO_VERB_TABLE *VerbTable2;

  VerbTable  = NULL;
  VerbTable2 = NULL;

  DEBUG ((DEBUG_INFO, "HDA: Init default verb tables (Realtek ALC700 and ALC701)\n"));
  VerbTable = &HdaVerbTableAlc711;
  VerbTable2 = &HdaVerbTableAlc701;

  PcdSet32S (PcdHdaVerbTable, (UINT32) VerbTable);
  PcdSet32S (PcdHdaVerbTable2, (UINT32) VerbTable2);

  PcdSet32S (PcdDisplayAudioHdaVerbTable, (UINT32) &HdaVerbTableDisplayAudio);

  // EHL POR Codecs - Realtek ALC700, ALC701, ALC274 (external - connected via HDA header)
  PcdSet32S (PcdCommonHdaVerbTable1, (UINT32) &HdaVerbTableAlc711);

  PcdSet32S (PcdCommonHdaVerbTable2, (UINT32) &HdaVerbTableAlc298);

  PcdSet32S (PcdCommonHdaVerbTable3, (UINT32) &HdaVerbTableAlc274);

  return;
}

/**
  Misc. init function for PEI post memory phase.
**/
VOID
EhlBoardMiscInit (
  VOID
  )
{
  UINT16    BoardId;
  BoardId = PcdGet16 (PcdBoardId);

  PcdSetBoolS (PcdSataLedEnable, FALSE);
  PcdSetBoolS (PcdVrAlertEnable, FALSE);
  PcdSetBoolS (PcdPchThermalHotEnable, FALSE);
  PcdSetBoolS (PcdMemoryThermalSensorGpioCPmsyncEnable, FALSE);
  PcdSetBoolS (PcdMemoryThermalSensorGpioDPmsyncEnable, FALSE);

  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdJslLp4xType4Rvp1:
      //
      // For PCIe Slot1 - x2 Connector
      //
      PcdSet8S (PcdPcieSlot1RootPort, 1);
      PcdSet32S (PcdPcieSlot1WakeGpioPin, GPIO_VER3_GPP_E2);
      //
      // For PCIe Slot2 - x2 Connector
      //
      PcdSetBoolS (PcdPchPCIeSlot2PwrEnableGpioPolarity, PIN_GPIO_ACTIVE_HIGH);
      PcdSetBoolS (PcdPchPCIeSlot2RstGpioPolarity, PIN_GPIO_ACTIVE_HIGH);
      PcdSet8S (PcdPcieSlot2RootPort, 7);
      PcdSet32S (PcdPcieSlot2WakeGpioPin, GPIO_VER3_GPP_F4);
      break;
    case BoardIdEhlLp4xType3Crb:
      //
      // For PCIe Slot1 - x2 Connector
      //
      PcdSet8S (PcdPcieSlot1RootPort, 1);
      PcdSet32S (PcdPcieSlot1WakeGpioPin, GPIO_VER3_GPP_E2);
      PcdSet8S (PcdPcieSlot2RootPort, 7);
      PcdSet32S (PcdPcieSlot2WakeGpioPin, GPIO_VER3_GPP_F4);
      break;
    default:
      break;
  }

  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdEhlLp4xType3Crb:
      //
      // Touch Panel
      //
      PcdSet32S (PcdTouchpanelIrqGpio, GPIO_VER3_GPP_E17);  // Touch 0 Interrupt Pin
      PcdSet32S (PcdTouchpanelPwrEnableGpio, GPIO_VER3_GPP_B16);  // Touch 0 power enable pin
      PcdSetBoolS (PcdTouchpanelIrqGpioPolarity, PIN_GPIO_ACTIVE_HIGH);  // Touch 0 Interrupt Pin polarity
      PcdSetBoolS (PcdTouchpanelPwrEnableGpioPolarity, PIN_GPIO_ACTIVE_HIGH);  // Touch 0 power enable pin polarity
      //
      // WLAN
      //
      PcdSet32S(PcdWlanWakeGpio, GPIO_VER3_GPP_F4);  // Sata port power pin
      break;

    case BoardIdJslLp4xErb:
    case BoardIdJslLp4xType4Rvp1:
    default:
      break;
  }

  //
  // SCI requires certain pins to be configured
  //
  PcdSet32S (PcdGpioTableSci, (UINTN)mEhlSciGpioTable);
  PcdSet16S (PcdGpioTableSciSize, sizeof(mEhlSciGpioTable) / sizeof(GPIO_INIT_CONFIG));
  return;
}

/**
  Tbt init function for PEI post memory phase.
**/
VOID
EhlBoardTbtInit (
  VOID
  )
{
  PcdSet8S (PcdCpuUsb30OverCurrentPinPort0, UsbOverCurrentPinSkip);
  PcdSet8S (PcdCpuUsb30OverCurrentPinPort1, UsbOverCurrentPinSkip);
  PcdSet8S (PcdCpuUsb30OverCurrentPinPort2, UsbOverCurrentPinSkip);
  PcdSet8S (PcdCpuUsb30OverCurrentPinPort3, UsbOverCurrentPinSkip);
  PcdSet8S (PcdCpuUsb30OverCurrentPinPort4, UsbOverCurrentPinSkip);
  PcdSet8S (PcdCpuUsb30OverCurrentPinPort5, UsbOverCurrentPinSkip);

  //
  // Clear ALL port setting by default.
  //
  PcdSet8S (PcdCpuUsb30PortEnable, 0);
}

/**
  Board Specific Init for PEI post memory phase.
**/
VOID
PeiEhlBoardSpecificInitPostMemNull (
  VOID
  )
{
}

/**
  Board's PCD function hook init function for PEI post memory phase.
**/
VOID
EhlBoardFunctionInit (
  VOID
)
{
  PcdSet32S (PcdFuncPeiBoardSpecificInitPostMem, (UINTN) PeiEhlBoardSpecificInitPostMemNull);
}

/**
  PMC-PD solution enable init lib
**/
VOID
EhlBoardPmcPdInit (
  VOID
  )
{
  PcdSetBoolS (PcdBoardPmcPdEnable, 1);
}


/**
  Configure GPIO, TouchPanel, HDA, PMC, TBT etc.

  @retval  EFI_SUCCESS   Operation success.
**/
EFI_STATUS
EFIAPI
EhlBoardInitBeforeSiliconInit (
  VOID
  )
{
  EhlInit ();

  EhlUsbConfigInit ();
  EhlSerialIoI2cPadsTerminationInit ();
  EhlTouchPanelGpioInit ();
  EhlHdaVerbTableInit ();
  EhlBoardMiscInit ();
  EhlBoardTbtInit ();
  EhlBoardFunctionInit();
  EhlBoardPmcPdInit ();
  EhlSaDisplayConfigInit ();
  EhlTsnDeviceGpioInit ();
  GpioInit (PcdGetPtr (PcdBoardGpioTable));
  ///
  /// Do Late PCH init
  ///
  LateSiliconInit ();

  return EFI_SUCCESS;
}

VOID
EhlBoardSpecificGpioInitPostMem (
  VOID
  )
{
  UINT16    BoardId;
  BoardId = PcdGet16 (PcdBoardId);
  //
  // Update OEM table ID
  //
  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdEhlLp4xType3Crb:
    case BoardIdJslLp4xErb:
    case BoardIdJslLp4xType4Rvp1:
      PcdSet64S (PcdXhciAcpiTableSignature, SIGNATURE_64 ('x', 'h', '_', 't', 'u', 'd', 'd', '4'));
      break;
    default:
      break;
  }

  //
  // Modify Preferred_PM_Profile field based on Board SKU's. Default is set to Mobile
  //
  PcdSet8S (PcdPreferredPmProfile, EFI_ACPI_2_0_PM_PROFILE_MOBILE);
  if (PcdGet8 (PcdPlatformFlavor) == FlavorUpServer) {
    PcdSet8S (PcdPreferredPmProfile, EFI_ACPI_2_0_PM_PROFILE_ENTERPRISE_SERVER);
  }
  //
  // Set home button, volume up button and volume down button interrupt to
  // zero by default
  //
  PcdSet32S (PcdHomeButtonInterrupt, 0);
  PcdSet32S (PcdVolumeUpButtonInterrupt, 0);
  PcdSet32S (PcdVolumeDownButtonInterrupt, 0);
  //
  // Assign FingerPrint, Gnss, Bluetooth & TouchPanel relative GPIO.
  //
  switch (BoardId) {
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
      PcdSet32S (PcdFingerPrintIrqGpio,   GPIO_VER3_GPP_V15);        // Finger Print Sensor Interrupt Pin
      PcdSet32S (PcdFingerPrintSleepGpio, GPIO_VER3_GPP_V14);        // Finger Print Sensor Reset Pin
      PcdSet32S (PcdTouchpanelIrqGpio,    GPIO_VER3_GPP_E17);        // Touch Interrupt Pin
      PcdSet32S (PcdHdaI2sCodecIrqGpio,   GPIO_VER3_GPP_B15);        // Audio I2S Codec IRQ Pin
      PcdSet8S  (PcdHdaI2sCodecI2cBusNumber, 3);                     // Audio I2S Codec conntected to I2C0
      PcdSet32S (PcdWwanModemBaseBandResetGpio, GPIO_VER3_GPP_V13);  // WWAN/Modem Base Band Reset pin
      PcdSet8S  (PcdBleUsbPortNumber,           10);                 // Bluetooth USB Port
      //
      // Configure GPIOs for Discrete BT Module - UART or USB
      //
      if (PcdGet8 (PcdDiscreteBtModule)) {
        PcdSet32S(PcdBtRfKillGpio, GPIO_VER3_GPP_E11);   // Bluetooth RF Kill Pin
        if (PcdGet8 (PcdDiscreteBtModule) == 2) {        // Only for BT Over UART Selection
          PcdSet32S(PcdBtIrqGpio, GPIO_VER3_GPP_F20);    // Bluetooth IRQ Pin
        }
      }
      PcdSet32S   (PcdPchSsdPwrEnableGpioNo, GPIO_VER3_GPP_F21);             // PCH M.2 SSD power enable gpio pin
      PcdSet32S   (PcdPchSsdRstGpioNo, GPIO_VER3_GPP_V13);                   // PCH M.2 SSD reset gpio pin
      PcdSetBoolS (PcdPchSsdPwrEnableGpioPolarity, PIN_GPIO_ACTIVE_HIGH);    // PCH M.2 SSD power enable gpio pin polarity
      PcdSetBoolS (PcdPchSsdRstGpioPolarity, PIN_GPIO_ACTIVE_LOW);           // PCH M.2 SSD reset gpio pin polarity
      PcdSet32S   (PcdPchSataPortPwrEnableGpioNo, GPIO_VER3_GPP_F21);        // Sata port power pin
      PcdSetBoolS (PcdPchSataPortPwrEnableGpioPolarity, PIN_GPIO_ACTIVE_HIGH);  // Sata port power pin polarity
      PcdSetBoolS (PcdEhlRvpRtd3TableEnable, TRUE);
      //
      // These PCDs are used to specify interrupt values for button array in EC less/ECLite platforms.
      //
      PcdSet32S (PcdHomeButtonInterrupt, GPIO_VER3_GPP_E9);
      PcdSet32S (PcdVolumeUpButtonInterrupt, GPIO_VER3_GPP_E12);
      PcdSet32S (PcdVolumeDownButtonInterrupt, GPIO_VER3_GPP_C8);
      break;
    case BoardIdEhlLp4xType3Crb:
      PcdSet32S (PcdFingerPrintIrqGpio,   GPIO_VER3_GPP_V15);        // Finger Print Sensor Interrupt Pin
      PcdSet32S (PcdFingerPrintSleepGpio, GPIO_VER3_GPP_V14);        // Finger Print Sensor Reset Pin
      PcdSet32S (PcdTouchpanelIrqGpio,    GPIO_VER3_GPP_E17);        // Touch Interrupt Pin
      PcdSet32S (PcdHdaI2sCodecIrqGpio,   GPIO_VER3_GPP_B15);        // Audio I2S Codec IRQ Pin
      PcdSet8S  (PcdHdaI2sCodecI2cBusNumber, 3);                     // Audio I2S Codec conntected to I2C0
      PcdSet32S (PcdWwanModemBaseBandResetGpio, GPIO_VER3_GPP_V13);  // WWAN/Modem Base Band Reset pin
      PcdSet8S  (PcdBleUsbPortNumber,           10);                 // Bluetooth USB Port
      //
      // Configure GPIOs for Discrete BT Module - UART or USB
      //
      if (PcdGet8 (PcdDiscreteBtModule)) {
        PcdSet32S(PcdBtRfKillGpio, GPIO_VER3_GPP_E11);   // Bluetooth RF Kill Pin
        if (PcdGet8 (PcdDiscreteBtModule) == 2) {        // Only for BT Over UART Selection
          PcdSet32S(PcdBtIrqGpio, GPIO_VER3_GPP_F20);    // Bluetooth IRQ Pin
        }
      }
      PcdSet32S   (PcdPchSsdPwrEnableGpioNo, GPIO_VER3_GPP_F21);             // PCH M.2 SSD power enable gpio pin
      PcdSet32S   (PcdPchSsdRstGpioNo, GPIO_VER3_GPP_V13);                   // PCH M.2 SSD reset gpio pin
      PcdSetBoolS (PcdPchSsdPwrEnableGpioPolarity, PIN_GPIO_ACTIVE_HIGH);    // PCH M.2 SSD power enable gpio pin polarity
      PcdSetBoolS (PcdPchSsdRstGpioPolarity, PIN_GPIO_ACTIVE_LOW);           // PCH M.2 SSD reset gpio pin polarity
      PcdSet32S   (PcdPchSataPortPwrEnableGpioNo, GPIO_VER3_GPP_F21);        // Sata port power pin
      PcdSetBoolS (PcdPchSataPortPwrEnableGpioPolarity, PIN_GPIO_ACTIVE_HIGH);  // Sata port power pin polarit
      PcdSetBoolS (PcdEhlCrbRtd3TableEnable, TRUE);
      break;
    case BoardIdJslLp4xErb:
      //PcdSetBoolS(PcdEhlRvpRtd3TableEnable, TRUE);

      //PcdSet32S (PcdFingerPrintIrqGpio,         GPIO_VER1_N_GPP_H0);   // Finger Print Sensor Interrupt Pin
      PcdSet32S (PcdTouchpanelIrqGpio,          GPIO_VER1_N_GPP_B15);  // Touch Interrupt Pin
      PcdSet32S (PcdTouchpadIrqGpio,            GPIO_VER1_N_GPP_C15);  // Force Pad Interrupt Pin
      PcdSetBoolS (PcdTouchpadIrqGpioPolarity, PIN_GPIO_ACTIVE_LOW);  // Touch Pad Interrupt pin polarity
      PcdSetBoolS (PcdTouchpanelIrqGpioPolarity, PIN_GPIO_ACTIVE_HIGH);  // Touch 0 Interrupt Pin polarity
      PcdSet32S (PcdHdaI2sCodecIrqGpio,         GPIO_VER1_N_GPP_B3);   // Audio I2S Codec IRQ Pin
      PcdSet8S  (PcdHdaI2sCodecI2cBusNumber,    3);                    // Audio I2S Codec conntected to I2C3
      PcdSet32S (PcdWwanModemBaseBandResetGpio, GPIO_VER1_N_GPP_S0);   // WWAN/Gnss Reset pin
      PcdSet32S (PcdBtRfKillGpio,               GPIO_VER1_N_GPP_D1);   // Bluetooth RF-KILL# pin
      PcdSet8S  (PcdBleUsbPortNumber,           4);                    // Bluetooth USB Port
      break;
    case BoardIdJslLp4xType4Rvp1:
      PcdSet32S (PcdTouchpanelIrqGpio,          GPIO_VER1_N_GPP_B15);  // Touch Interrupt Pin
      PcdSet32S (PcdTouchpadIrqGpio,            GPIO_VER1_N_GPP_C15);  // Force Pad Interrupt Pin
      PcdSetBoolS (PcdTouchpadIrqGpioPolarity, PIN_GPIO_ACTIVE_LOW);  // Touch Pad Interrupt pin polarity
      PcdSetBoolS (PcdTouchpanelIrqGpioPolarity, PIN_GPIO_ACTIVE_HIGH);  // Touch 0 Interrupt Pin polarity
      PcdSet32S (PcdHdaI2sCodecIrqGpio,         GPIO_VER1_N_GPP_B3);   // Audio I2S Codec IRQ Pin
      PcdSet8S  (PcdHdaI2sCodecI2cBusNumber,    3);                    // Audio I2S Codec conntected to I2C3
      PcdSet32S (PcdWwanModemBaseBandResetGpio, GPIO_VER1_N_GPP_H17);  // WWAN/Gnss Reset pin
      PcdSet32S (PcdBtRfKillGpio,               GPIO_VER1_N_GPP_D1);   // Bluetooth RF-KILL# pin
      PcdSet8S  (PcdBleUsbPortNumber,           4);                    // Bluetooth USB Port
      break;
    default:
      break;
  }
}

VOID
EhlInitCommonPlatformPcdPostMem (
  VOID
  )
{
  UINT16                          BoardId;
  BoardId = PcdGet16 (PcdBoardId);

  PcdSetBoolS (PcdPssReadSN, FALSE);
  PcdSet8S (PcdPssI2cSlaveAddress, 0x6E);
  PcdSet8S (PcdPssI2cBusNumber, 0x05);
  PcdSetBoolS (PcdSpdAddressOverride, FALSE);

  switch (BoardId) {
    case BoardIdJslLp4xErb:
      PcdSet32S (PcdEcSmiGpio, GPIO_VER1_N_GPP_D2);
      PcdSet32S (PcdEcLowPowerExitGpio,GPIO_VER1_N_GPP_C11);
      PcdSetBoolS (PcdPssReadSN, TRUE);
      PcdSet8S (PcdPssI2cSlaveAddress, 0x6E);
      PcdSet8S (PcdPssI2cBusNumber, 0x05);
      PcdSetBoolS (PcdSpdAddressOverride, FALSE);
      PcdSetBoolS (PcdUsbTypeCSupport, TRUE);
      break;
    case BoardIdJslLp4xType4Rvp1:
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdEhlLp4xType3Crb:
    default:
      PcdSetBoolS (PcdPssReadSN, FALSE);
      PcdSet8S (PcdPssI2cSlaveAddress, 0x6E);
      PcdSet8S (PcdPssI2cBusNumber, 0x05);
      PcdSetBoolS (PcdSpdAddressOverride, FALSE);
      PcdSetBoolS (PcdUsbTypeCSupport, FALSE);
      break;
  }

  switch (BoardId) {
    //
    //   Board             Type C port     CPU Port    PCH Port    Split support
    //   EHL U DDR4             1            0            1            Yes
    //   ERB                    2            1            5            Yes
    //                          3            2            6            Yes
    //                          4            3            7            Yes
    case BoardIdJslLp4xErb:
      PcdSetBoolS (PcdUsbTypeCSupport, TRUE);
      // Number of ports supported
      PcdSet8S(PcdTypeCPortsSupported, 4);
      // Type C port 1 mapping
      PcdSet8S(PcdUsbTypeCPort1, 0);
      PcdSet8S(PcdUsbTypeCPort1Pch, 1);
      PcdSet8S(PcdUsbCPort1Properties, (0 | USB_TYPEC_CPU << 1 | SPLIT_SUPPORTED));
      // Type C port 2 mapping
      PcdSet8S(PcdUsbTypeCPort2, 1);
      PcdSet8S(PcdUsbTypeCPort2Pch, 5);
      PcdSet8S(PcdUsbCPort2Properties, (0 | USB_TYPEC_CPU << 1 | SPLIT_SUPPORTED));
      // Type C port 3 mapping
      PcdSet8S(PcdUsbTypeCPort3, 2);
      PcdSet8S(PcdUsbTypeCPort3Pch, 6);
      PcdSet8S(PcdUsbCPort3Properties, (0 | USB_TYPEC_CPU << 1 | SPLIT_SUPPORTED));
      // Type C port 4 mapping
      PcdSet8S(PcdUsbTypeCPort4, 3);
      PcdSet8S(PcdUsbTypeCPort4Pch, 7);
      PcdSet8S(PcdUsbCPort4Properties, (0 | USB_TYPEC_CPU << 1 | SPLIT_SUPPORTED));
      break;
    case BoardIdEhlLp4xType4Erb:
    case BoardIdEhlLp4xType4Rvp1:
    case BoardIdEhlDdr4Type3Rvp2:
    case BoardIdEhlLp4xType3Crb:
    case BoardIdJslLp4xType4Rvp1:
    default:
      PcdSetBoolS (PcdUsbTypeCSupport, FALSE);
      break;
  }

  //
  // Battery Present
  // Real & Virtual battery is need to supported in all except Desktop
  //
  PcdSet8S (PcdBatteryPresent, BOARD_REAL_BATTERY_SUPPORTED | BOARD_VIRTUAL_BATTERY_SUPPORTED);
  //
  // Real Battery 1 Control & Real Battery 2 Control
  //
  PcdSet8S (PcdRealBattery1Control, 1);
  PcdSet8S (PcdRealBattery2Control, 2);

  //
  // Sky Camera Sensor
  //
  PcdSetBoolS (PcdMipiCamSensor, FALSE);

  //
  // H8S2113 SIO
  //
  PcdSetBoolS (PcdH8S2113SIO, FALSE);

  //
  // NCT6776F COM, SIO & HWMON
  //
  PcdSetBoolS (PcdNCT6776FCOM, FALSE);
  PcdSetBoolS (PcdNCT6776FSIO, FALSE);
  PcdSetBoolS (PcdNCT6776FHWMON, FALSE);
  //
  // ZPODD
  //
  PcdSet8S (PcdZPoddConfig, 0);
  //
  // SMC Runtime Sci Pin
  // EC will use eSpi interface to generate SCI
  //
  PcdSet32S (PcdSmcRuntimeSciPin, 0x00);
  //
  // Convertable Dock Support
  // Not supported only for S & H SKU's
  PcdSetBoolS (PcdConvertableDockSupport, TRUE);
  //
  // Ec Hotkey F3, F4, F5, F6, F7 and F8 Support
  //
  PcdSet8S (PcdEcHotKeyF3Support, FALSE);
  PcdSet8S (PcdEcHotKeyF4Support, FALSE);
  PcdSet8S (PcdEcHotKeyF5Support, FALSE);
  PcdSet8S (PcdEcHotKeyF6Support, FALSE);
  PcdSet8S (PcdEcHotKeyF7Support, FALSE);
  PcdSet8S (PcdEcHotKeyF8Support, FALSE);

  //
  // Virtual Button Volume Up & Done Support
  // Virtual Button Home Button Support
  // Virtual Button Rotation Lock Support
  //
  PcdSetBoolS (PcdVirtualButtonVolumeUpSupport, TRUE);
  PcdSetBoolS (PcdVirtualButtonVolumeDownSupport, TRUE);
  PcdSetBoolS (PcdVirtualButtonHomeButtonSupport, TRUE);
  PcdSetBoolS (PcdVirtualButtonRotationLockSupport, TRUE);
  //
  // Slate Mode Switch Support
  //
  PcdSetBoolS (PcdSlateModeSwitchSupport, TRUE);
  //
  // Virtual Gpio Button Support
  //
  PcdSetBoolS (PcdVirtualGpioButtonSupport, TRUE);
  //
  // Ac Dc Auto Switch Support
  //
  PcdSetBoolS (PcdAcDcAutoSwitchSupport, TRUE);

  //
  // Pm Power Button Gpio Pin
  //
  PcdSet32S (PcdPmPowerButtonGpioPin, GPIO_VER3_GPD2);
  //
  // Acpi Enable All Button Support
  //
  PcdSetBoolS (PcdAcpiEnableAllButtonSupport, TRUE);
  //
  // Acpi Hid Driver Button Support
  //
  PcdSetBoolS (PcdAcpiHidDriverButtonSupport, TRUE);
}


/**
  Board init for PEI after Silicon initialized

  @retval  EFI_SUCCESS   Operation success.
**/
EFI_STATUS
EFIAPI
EhlBoardInitAfterSiliconInit (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "EhlBoardInitAfterSiliconInit\n"));
  EhlBoardSpecificGpioInitPostMem ();
  EhlInitCommonPlatformPcdPostMem ();
  return EFI_SUCCESS;
}

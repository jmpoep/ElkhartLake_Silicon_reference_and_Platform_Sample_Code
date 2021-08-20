/** @file
  PCH Serial IO Lib implementation.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

#include "MrcOemPlatform.h"
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include "PciSegmentLib.h"
#include <Library/PchSerialIoLib.h>
#include <Private/Library/PchPsfPrivateLib.h>
#include <PchLimits.h>
#include <Register/PchRegs.h>
#include <Register/PchRegsPcr.h>
#include <Register/PchRegsSerialIo.h>
#include <Register/PchRegsSerialIoUart.h>

GLOBAL_REMOVE_IF_UNREFERENCED SERIAL_IO_CONTROLLER_DESCRIPTOR mSerialIoAcpiAddress [PCH_MAX_SERIALIO_CONTROLLERS] =
{
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x0000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x1000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x2000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x3000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x4000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x5000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x6000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x7000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x8000,  PCH_SERIAL_IO_BASE_ADDRESS + 0x9000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0xA000,  PCH_SERIAL_IO_BASE_ADDRESS + 0xB000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x12000, PCH_SERIAL_IO_BASE_ADDRESS + 0x13000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x14000, PCH_SERIAL_IO_BASE_ADDRESS + 0x15000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x16000, PCH_SERIAL_IO_BASE_ADDRESS + 0x17000},
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x18000, PCH_SERIAL_IO_BASE_ADDRESS + 0x19000}, //SPI0
  {PCH_SERIAL_IO_BASE_ADDRESS + 0x1A000, PCH_SERIAL_IO_BASE_ADDRESS + 0x1B000}  //SPI1
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchSerialIoPciCfgCtrAddr [PCH_MAX_SERIALIO_CONTROLLERS] =
{
  R_SERIAL_IO_PCR_PCICFGCTRL1,
  R_SERIAL_IO_PCR_PCICFGCTRL2,
  R_SERIAL_IO_PCR_PCICFGCTRL3,
  R_SERIAL_IO_PCR_PCICFGCTRL4,
  R_SERIAL_IO_PCR_PCICFGCTRL5,
  R_SERIAL_IO_PCR_PCICFGCTRL6,
  R_SERIAL_IO_PCR_PCICFGCTRL9,
  R_SERIAL_IO_PCR_PCICFGCTRL10,
  R_SERIAL_IO_PCR_PCICFGCTRL11,
  R_SERIAL_IO_PCR_PCICFGCTRL13, // SPI0
  R_SERIAL_IO_PCR_PCICFGCTRL14, // SPI1
};

/**
  Returns Serial IO Controller Type  I2C or UART

  @param[in] Number  Number of SerialIo controller

  @retval            I2C or UART
  @retval            UNKNOWN - in case if undefined controller
**/
PCH_SERIAL_IO_CONTROLLER_TYPE
GetSerialIoControllerType (
  IN PCH_SERIAL_IO_CONTROLLER  Controller
  )
{
  if (Controller >= PchSerialIoIndexI2C0 && Controller <= GetMaxI2cNumber ()) {
    return SERIAL_IO_I2C;
  } else if (Controller >= PchSerialIoIndexUart0 && Controller <= PchSerialIoIndexUart2) {
    return SERIAL_IO_UART;
  } else if (Controller >= PchSerialIoIndexSpi0 && Controller <= PchSerialIoIndexSpi1) {
    return SERIAL_IO_SPI;
  }
  return SERIAL_IO_UNKNOWN;
}

/**
  Checks if given Serial IO Controller Function equals 0

  @param[in] SerialIoNumber             Serial IO device

  @retval                               TRUE if SerialIO Function is equal to 0
                                        FALSE if Function is higher then 0
**/
BOOLEAN
IsSerialIoFunctionZero (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoNumber
  )
{
  if (GetSerialIoFunctionNumber (SerialIoNumber) > 0) {
    return FALSE;
  }
  return TRUE;
}

/**
  Checks if given Serial IO Controller is enabled or not

  @param[in] DeviceNumber               device number
  @param[in] FunctionNumber             function number

  @retval TRUE                          TRUE if given serial io device is enabled.
  @retval FALSE                         FALSE if given serial io device is disabled.
**/
BOOLEAN
IsSerialIoDeviceEnabled (
  IN UINT8  DeviceNumber,
  IN UINT8  FunctionNumber
  )
{
  if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, DeviceNumber, FunctionNumber, PCI_DEVICE_ID_OFFSET)) != 0xFFFF) {
    return TRUE;
  }
  return FALSE;
}

/**
  Gets Pci Config control offset

  @param[in] DeviceNumber               device number
  @param[in] FunctionNumber             function number

  @retval    CfgCtrAddr                 Offset of Pci config control
                                        0 if Device and Function do not correspond to Serial IO
**/
UINT16
GetSerialIoConfigControlOffset (
  IN UINT8  DeviceNumber,
  IN UINT8  FunctionNumber
  )
{
  PCH_SERIAL_IO_CONTROLLER  Controller;

  for (Controller = 0; Controller < (GetPchMaxSerialIoControllersNum () - GetPchMaxSerialIoSpiControllersNum ()); Controller++) {
    if ((DeviceNumber == GetSerialIoDeviceNumber (Controller)) &&
        (FunctionNumber == GetSerialIoFunctionNumber (Controller))) {
      return mPchSerialIoPciCfgCtrAddr[Controller];
    }
  }

  return 0;
}

#ifndef MRC_MINIBIOS_BUILD
/**
  Checks if Device with given AcpiHid string is one of SerialIo I2C controllers
  If yes, its number is returned through I2cIndex parameter, otherwise I2cIndex is not updated

  @param[in]  AcpiHid                   String
  @param[out] I2cIndex                  Number of SerialIo I2C controller

  @retval TRUE                          yes it is a SerialIo I2C controller
  @retval FALSE                         no it isn't a SerialIo I2C controller
**/
BOOLEAN
IsSerialIoI2cAcpiHid (
  IN CHAR8                      *AcpiHid,
  OUT PCH_SERIAL_IO_CONTROLLER  *I2cIndex
  )
{
  UINT8   Controller;

  for (Controller = 0; Controller < GetMaxI2cNumber (); Controller++) {
    if (!AsciiStrCmp ((const CHAR8 *) AcpiHid, GetSerialIoAcpiHid(Controller))) {
      *I2cIndex = Controller;
      return TRUE;
    }
  }
  return FALSE;
}
#endif // MRC_MINIBIOS_BUILD
/**
  Finds BAR values of SerialIo devices.
  SerialIo devices can be configured to not appear on PCI so traditional method of reading BAR might not work.
  If the SerialIo device is in PCI mode, a request for BAR1 will return its PCI CFG space instead

  @param[in] SerialIoDevice             Serial IO device
  @param[in] BarNumber                  0=BAR0, 1=BAR1

  @retval                               SerialIo Bar value
**/
UINTN
FindSerialIoBar (
  IN PCH_SERIAL_IO_CONTROLLER           SerialIoDevice,
  IN UINT8                              BarNumber
  )
{
  UINT64 Bar;
  UINTN  PcieBase;
  UINT32 VenId;

  PcieBase = MmPciBase (DEFAULT_PCI_BUS_NUMBER_PCH, GetSerialIoDeviceNumber (SerialIoDevice), GetSerialIoFunctionNumber (SerialIoDevice));
  VenId = MmioRead32 (PcieBase + PCI_VENDOR_ID_OFFSET) & 0xFFFF;
  if (VenId == V_PCH_INTEL_VENDOR_ID) {
    if (BarNumber == 1) {
      return PcieBase;
    }
    Bar = MmioRead32 (PcieBase + PCI_BASE_ADDRESSREG_OFFSET);
    // For 64-Bit Memory Space BARs ((BAR[x] & 0xFFFFFFF0) + ((BAR[x+1] & 0xFFFFFFFF) << 32)
    if ((Bar & B_PCI_BAR_MEMORY_TYPE_MASK) == B_PCI_BAR_MEMORY_TYPE_64) {
      Bar = (Bar & 0xFFFFF000) + (UINTN) MrcOemMemoryLeftShiftU64 ((UINT64) (MmioRead32 (PcieBase + PCI_BASE_ADDRESSREG_OFFSET + 4) & 0xFFFFFFFF), 32);
      return (UINTN) Bar;
    }
    return (UINTN) (Bar & 0xFFFFF000);
  }
  //PCI mode failed? Try hardcoded addresses from ACPI
  if (BarNumber == 0) {
    Bar = mSerialIoAcpiAddress[SerialIoDevice].Bar0;
  } else {
    Bar = mSerialIoAcpiAddress[SerialIoDevice].Bar1;
  }
  return (UINTN) Bar;
}

/**
  Get PSF_PORT for a given Serial IO Controller

  @param[in] Controller    Serial IO controller number
**/
STATIC
PSF_PORT
SerialIoPsfPort (
  IN PCH_SERIAL_IO_CONTROLLER Controller
  )
{
  switch (GetSerialIoControllerType (Controller)) {
    case SERIAL_IO_I2C:
      return PsfSerialIoI2cPort (Controller - PchSerialIoIndexI2C0);
    case SERIAL_IO_UART:
      return PsfSerialIoUartPort (Controller - PchSerialIoIndexUart0);
    case SERIAL_IO_UNKNOWN:
    default:
      return (PSF_PORT){0};
  }
}

/**
  Configures Serial IO Controller

  @param[in] Controller    Serial IO controller number
  @param[in] DeviceMode    Device operation mode
  @param[in] PsfDisable    Disable device at PSF level

  @retval None
**/
VOID
ConfigureSerialIoController (
  IN PCH_SERIAL_IO_CONTROLLER Controller,
  IN PCH_SERIAL_IO_MODE       DeviceMode,
  IN BOOLEAN                  PsfDisable
  )
{
  UINT64          PciCfgBase;
  UINT32          Data32And;
  UINT32          Data32Or;
  UINT16          *SerialIoPciCfgCtrAddr;

/*
  Please do not add DEBUG message here because this routine is configuring SerialIoUart.
  Printing DEBUG message before SerialIoUart initialization may cause system hang (in Debug build).
*/

  //
  // This is to prevent from overflow of array access.
  //
  if (Controller >= PCH_MAX_SERIALIO_CONTROLLERS) {
    return;
  }

  if (GetSerialIoControllerType (Controller) == SERIAL_IO_UNKNOWN) {
    return;
  }

  PciCfgBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 GetSerialIoDeviceNumber (Controller),
                 GetSerialIoFunctionNumber (Controller),
                 0
                 );
  //
  // Do not modify a device that has already been disabled/hidden
  //
  if (PciSegmentRead16 (PciCfgBase + PCI_VENDOR_ID_OFFSET) != V_PCH_INTEL_VENDOR_ID) {
    return;
  }

  ///
  /// Step 0. set Bit 16,17,18.
  ///
  PciSegmentOr32 (PciCfgBase + R_SERIAL_IO_CFG_D0I3MAXDEVPG, BIT18 | BIT17 | BIT16);

  SerialIoPciCfgCtrAddr = mPchSerialIoPciCfgCtrAddr;

  switch (DeviceMode) {
    case PchSerialIoDisabled:
      ///
      /// Step 1. Put device in D3
      /// Step 2. Function Disable in PSF
      ///
      PciSegmentOr32 (PciCfgBase + R_SERIAL_IO_CFG_PME_CTRL_STS, BIT1 | BIT0);

      if (PsfDisable) {
        PsfDisableDevice (SerialIoPsfPort (Controller));
      }
      break;
    case PchSerialIoAcpi:
    case PchSerialIoHidden:
      ///
      /// reenable BAR1 in case it was disabled earlier
      /// Read back is needed to enforce the sideband and primary ordering.
      ///
      PchPcrAndThenOr32WithReadback (
        PID_SERIALIO,
        SerialIoPciCfgCtrAddr[Controller],
        (UINT32) ~(B_SERIAL_IO_PCR_PCICFGCTRL_BAR1_DIS),
        0
        );
      PsfEnableDeviceBar (SerialIoPsfPort (Controller), BIT3 | BIT2);
      ///
      /// Step 1. Assign BAR0
      /// Step 2. Assign BAR1
      ///
      PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR0_LOW,  mSerialIoAcpiAddress[Controller].Bar0);
      PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR0_HIGH, 0x0);
      PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR1_LOW,  mSerialIoAcpiAddress[Controller].Bar1);
      PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR1_HIGH, 0x0);
      ///
      /// Step 3. Set Memory space Enable
      ///
      PciSegmentOr32 (PciCfgBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
      ///
      /// Step 4. Disable device's PciCfg and enable ACPI interrupts
      ///         Read back is needed to enforce the sideband and primary ordering.
      ///
      PchPcrAndThenOr32WithReadback (
        PID_SERIALIO,
        SerialIoPciCfgCtrAddr[Controller],
        ~0u,
        (B_SERIAL_IO_PCR_PCICFGCTRL_PCI_CFG_DIS | B_SERIAL_IO_PCR_PCICFGCTRL_ACPI_INTR_EN)
        );
      ///
      /// Step 5. Disable device's PciCfg in PSF
      ///
      PsfHideDevice (SerialIoPsfPort (Controller));
      ///
      /// get controller out of reset
      ///
      MmioOr32 (
        mSerialIoAcpiAddress[Controller].Bar0 + R_SERIAL_IO_MEM_PPR_RESETS,
        B_SERIAL_IO_MEM_PPR_RESETS_FUNC | B_SERIAL_IO_MEM_PPR_RESETS_APB | B_SERIAL_IO_MEM_PPR_RESETS_IDMA
        );
      break;
    case PchSerialIoPci:
      //
      //  Check If device is already initialized
      //
      if (PciSegmentRead32 (PciCfgBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFF000) {
        return;
      }
      ///
      /// reenable PciCfg in case it was disabled earlier
      /// Read back is needed to enforce the sideband and primary ordering.
      ///
      PchPcrAndThenOr32WithReadback (
        PID_SERIALIO,
        SerialIoPciCfgCtrAddr[Controller],
        (UINT32) ~(B_SERIAL_IO_PCR_PCICFGCTRL_PCI_CFG_DIS | B_SERIAL_IO_PCR_PCICFGCTRL_ACPI_INTR_EN),
        0
        );
      PsfUnhideDevice (SerialIoPsfPort (Controller));
      ///
      /// Disable Bar1
      /// Disable Bar1 in PSF
      /// Read back is needed to enforce the sideband and primary ordering.
      ///
      PchPcrAndThenOr32WithReadback (
        PID_SERIALIO,
        SerialIoPciCfgCtrAddr[Controller], ~0u,
        B_SERIAL_IO_PCR_PCICFGCTRL_BAR1_DIS
        );
      PsfDisableDeviceBar (SerialIoPsfPort (Controller), BIT3 | BIT2);

      //
      // Assign BAR0 and Set Memory space Enable
      //
      PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR0_LOW,  mSerialIoAcpiAddress[Controller].Bar0);
      PciSegmentWrite32 (PciCfgBase + R_SERIAL_IO_CFG_BAR0_HIGH, 0x0);
      PciSegmentOr32    (PciCfgBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
      ///
      /// get controller out of reset
      ///
      MmioOr32 (
        mSerialIoAcpiAddress[Controller].Bar0 + R_SERIAL_IO_MEM_PPR_RESETS,
        B_SERIAL_IO_MEM_PPR_RESETS_FUNC | B_SERIAL_IO_MEM_PPR_RESETS_APB | B_SERIAL_IO_MEM_PPR_RESETS_IDMA
        );
      break;
    default:
      return;
  }

  ///
  /// Step X. Program clock dividers for UARTs
  /// Step Y. Enable Byte addressing for UARTs in legacy mode
  ///
  if ((Controller >= PchSerialIoIndexUart0 && Controller <= PchSerialIoIndexUart2) && (DeviceMode != PchSerialIoDisabled)) {
    MmioWrite32 (mSerialIoAcpiAddress[Controller].Bar0 + R_SERIAL_IO_MEM_PPR_CLK,
      (UINT32) (B_SERIAL_IO_MEM_PPR_CLK_UPDATE | (V_SERIAL_IO_MEM_PPR_CLK_N_DIV << 16) |
       (V_SERIAL_IO_MEM_PPR_CLK_M_DIV << 1) | B_SERIAL_IO_MEM_PPR_CLK_EN )
      );

    Data32And = (UINT32) (~(B_SERIAL_IO_PCR_GPPRVRW7_UART0_BYTE_ADDR_EN << (Controller - PchSerialIoIndexUart0)));
    Data32Or = 0x0;
    if (DeviceMode == PchSerialIoHidden) {
      Data32Or = (B_SERIAL_IO_PCR_GPPRVRW7_UART0_BYTE_ADDR_EN << (Controller - PchSerialIoIndexUart0));
    }
    PchPcrAndThenOr32 (PID_SERIALIO, R_SERIAL_IO_PCR_GPPRVRW7,Data32And,Data32Or);
    //
    // Dummy read after setting any of GPPRVRW7.
    // Required for UART 16550 8-bit Legacy mode to become active
    //
    MmioRead32 (mSerialIoAcpiAddress[Controller].Bar0 + R_SERIAL_IO_MEM_PPR_CLK);
  }
  ///
  /// Step Z. Program I2C SDA hold registers
  ///
  if (Controller >= PchSerialIoIndexI2C0 && Controller <= GetMaxI2cNumber ()) {
    if (DeviceMode != PchSerialIoDisabled) {
      MmioOr32 (mSerialIoAcpiAddress[Controller].Bar0 + R_SERIAL_IO_MEM_I2C_SDA_HOLD, V_SERIAL_IO_MEM_I2C_SDA_HOLD_VALUE);
    }
  }

}


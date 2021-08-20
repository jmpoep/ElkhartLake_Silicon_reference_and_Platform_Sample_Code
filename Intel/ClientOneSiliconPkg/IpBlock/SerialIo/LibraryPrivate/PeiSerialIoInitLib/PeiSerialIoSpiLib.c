/** @file
  Initializes Serial IO Spi Controllers.

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

#include <Ppi/SiPolicy.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PeiItssLib.h>
#include <Library/SerialIoAccessLib.h>
#include <Library/SerialIoPrivateLib.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/GpioNativePads.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PsfLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/SerialIoRegs.h>
#include <Register/PchPcrRegs.h>
#include "PeiSerialIoInitPrivateLib.h"

/**
  0x224 ChipSelect Control - R_SERIAL_IO_MEM_SPI_CS_CONTROL
**/
typedef union {
  struct {
    /**
    SPI Chip Select Mode Section.
    0 = HW Mode - CS is under SSP control,
    1 = SW Mode - CS is under SW Control using CsState bit
    **/
    UINT32  CsMode         : 1;    //[RW][0]
    /**
    Manual SW control of SPI Chip Select (CS)
    0 = CS is set to low, 1 = CS is set to high
    The state of this bit 0=>CS asserted; 1 => CS de-asserted. The
    state of the CS pin also includes the polarity setting in bits 15:12 of this register.
    **/
    UINT32  CsState        : 1;    //[RW][1]
    UINT32  Reserved0      : 6;    //[N/A][2:7]
    /**
    These Bits select which SPI CS Signal is to be driven by the SSP Frame (CS).
    The steering logic will ensure that when switching to another active SPI CS port
    the inactive port will be forced to the inactive polarity defined by the
    corresponding SPI CS Polarity Bit
    **/
    UINT32  CsOutputSelect : 2;    //[RW][8:9]
    UINT32  Reserved1      : 2;    //[N/A][10:11]
    /**
    Sets Inactive/Idle polarity of CS0.
    When switching to another active SPI CS port the inactive port
    will be forced to the inactive polarity 0 = Low, 1 = High
    **/
    UINT32  Cs0Polarity    : 1;    //[RW][12]
    /**
    Sets Inactive/Idle polarity of CS1.
    When switching to another active SPI CS port the inactive port
    will be forced to the inactive polarity 0 = Low, 1 = High
    **/
    UINT32  Cs1Polarity    : 1;    //[RW][13]
    /**
    Sets Inactive/Idle polarity of CS2.
    When switching to another active SPI CS port the inactive port
    will be forced to the inactive polarity 0 = Low, 1 = High
    **/
    UINT32  Cs2Polarity    : 1;    //[RW][14]
    /**
    Sets Inactive/Idle polarity of CS3.
    When switching to another active SPI CS port the inactive port
    will be forced to the inactive polarity 0 = Low, 1 = High
    **/
    UINT32  Cs3Polarity    : 1;    //[RW][15]
    UINT32  Reserved2      : 15;   //[N/A][16:31]
  } Fields;
  UINT32 Data;
} SERIAL_IO_SPI_CS_CONTROL_REG;


/**
  Configure M/N Divider settings

  @param[in] Base              SPI MMIO BAR0

**/
VOID
STATIC
SerialIoSpiMNDividerConfig (
  IN UINT64                    MmioBase
  )
{
  UINT32      Data;
  Data = MmioRead32 ((UINTN) (MmioBase + R_SERIAL_IO_MEM_PPR_CLK));
  DEBUG ((DEBUG_INFO, "SPI clk address read from %x gets value %x\n",
    MmioBase + R_SERIAL_IO_MEM_PPR_CLK,
    Data));

  MmioWrite32 ((UINTN) (MmioBase + R_SERIAL_IO_MEM_PPR_CLK),
    Data | V_SERIAL_IO_MEM_PPR_CLK_M_VAL | V_SERIAL_IO_MEM_PPR_CLK_N_VAL);
  DEBUG ((DEBUG_INFO, "Written %x to MMIO address %x\n",
    Data | V_SERIAL_IO_MEM_PPR_CLK_M_VAL | V_SERIAL_IO_MEM_PPR_CLK_N_VAL,
    MmioBase + R_SERIAL_IO_MEM_PPR_CLK));

  Data = MmioRead32 ((UINTN) (MmioBase + R_SERIAL_IO_MEM_PPR_CLK));
  DEBUG ((DEBUG_INFO, "Readback from address %x gets value %x\n",
    MmioBase + R_SERIAL_IO_MEM_PPR_CLK,
    Data));
}

/**
  Configure Chip Select settings

  @param[in] Base              SPI MMIO BAR0
  @param[in] SpiDeviceConfig   SerialIo SPI Config

**/
VOID
STATIC
SerialIoSpiChipSelectConfig (
  IN UINT64                    MmioBase,
  IN SERIAL_IO_SPI_CONFIG      *SpiDeviceConfig
  )
{
  UINT8                         Index;
  SERIAL_IO_SPI_CS_CONTROL_REG  SpiCsControl;

  SpiCsControl.Data = MmioRead32 ((UINTN) (MmioBase + R_SERIAL_IO_MEM_SPI_CS_CONTROL));

  //
  // Set CS mode
  //
  SpiCsControl.Fields.CsMode = SpiDeviceConfig->CsMode;

  for (Index = 0; Index < GetPchMaxSerialIoSpiChipSelectsNum (); Index++) {
    if (SpiDeviceConfig->CsEnable[Index]) {
      //
      // Set CS polarity
      //
      if (Index == 0) {
        SpiCsControl.Fields.Cs0Polarity = SpiDeviceConfig->CsPolarity[Index];
      }
      if (Index == 1) {
        SpiCsControl.Fields.Cs1Polarity = SpiDeviceConfig->CsPolarity[Index];
      }
    }
  }

  //
  // Set CS Output Select
  //
  SpiCsControl.Fields.CsOutputSelect = SpiDeviceConfig->DefaultCsOutput;

  //
  // Set CS state
  //
  SpiCsControl.Fields.CsState = SpiDeviceConfig->CsState;

  MmioWrite32 ((UINTN) (MmioBase + R_SERIAL_IO_MEM_SPI_CS_CONTROL), SpiCsControl.Data);
}

/**
  Configures GPIO for each Serial IO SPI Controller

  @param[in] SpiNumber         SPI Number
  @param[in] SpiDeviceConfig   SerialIo SPI Config

**/
VOID
STATIC
SerialIoSpiGpioConfiguration (
  IN UINT8                 SpiNumber,
  IN SERIAL_IO_SPI_CONFIG  *SpiDeviceConfig
  )
{
  UINT8                       Index;

  GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (SpiNumber), 0);
  GpioSetInputInversion (GpioGetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_MOSI (SpiNumber)), 0);
  if (SpiDeviceConfig->MisoEnable) {
    GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_MISO (SpiNumber), 0);
    GpioSetInputInversion (GpioGetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_MISO (SpiNumber)), 0);
  }
  GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_CLK (SpiNumber), 0);
  GpioSetInputInversion (GpioGetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_CLK (SpiNumber)), 0);

  for (Index = 0; Index < GetPchMaxSerialIoSpiChipSelectsNum (); Index++) {
    if (SpiDeviceConfig->CsEnable[Index]) {
      GpioSetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_CS (SpiNumber, Index), 0);
      GpioSetInputInversion (GpioGetNativePadByFunction (GPIO_FUNCTION_SERIAL_IO_SPI_CS (SpiNumber, Index)), 0);
    }
  }
}

/**
  Configures Serial IO Controller

  @param[in] SpiNumber         SPI Number
  @param[in] SpiDeviceConfig   SerialIo SPI Config
  @param[in] PsfDisable        Applies only for SerialIoSpiDisabled devices.
                               TRUE  - Device will be disabled in PSF, and will no longer enumerate on PCI.
                               FALSE - PSF configuration is left unmodified.
  @param[in] PchMasterPowerGating  PchMasterPowerGating

**/
VOID
SerialIoSpiConfiguration (
  IN UINT8                      SpiNumber,
  IN SERIAL_IO_SPI_CONFIG       *SpiDeviceConfig,
  IN BOOLEAN                    PsfDisable,
  IN BOOLEAN                    PchMasterPowerGating
  )
{
  SERIAL_IO_PCI_DEVICE_STATE  PciState;
  UINT64                      PciCfgBase;
  UINT64                      Base;
  BOOLEAN                     TempBar;
  BOOLEAN                     Hidden;

  PciState.PciCfgBar0 = 0x0;
  TempBar             = FALSE;
  Hidden              = FALSE;
  Base                = 0x0;

  //
  // This is to prevent from overflow of array access.
  //
  if (SpiNumber >= PCH_MAX_SERIALIO_SPI_CONTROLLERS) {
    return;
  }

  //
  // Override previous SPI configuration
  //
  SerialIoPciPsfEnable (GetSerialIoSpiConfigControlOffset (SpiNumber), PsfSerialIoSpiPort (SpiNumber));

  PciCfgBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 GetSerialIoSpiDeviceNumber (SpiNumber),
                 GetSerialIoSpiFunctionNumber (SpiNumber),
                 0
                 );
  if (PciSegmentRead32 (PciCfgBase + PCI_VENDOR_ID_OFFSET) == 0xFFFFFFFF) {
    return;
  }
  SerialIoEnablePowerGating (PciCfgBase, PchMasterPowerGating);

  switch (SpiDeviceConfig->Mode) {
    case SerialIoSpiDisabled:
      SerialIoSetD3 (PciCfgBase);
      if (PsfDisable) {
        PsfDisableDevice (PsfSerialIoSpiPort (SpiNumber));
      }
      return;
    case SerialIoSpiHidden:
      SerialIoSetFixedMmio (PciCfgBase,
                            GetSerialIoSpiFixedMmioAddress (SpiNumber),
                            GetSerialIoSpiFixedPciCfgAddress (SpiNumber),
                            GetSerialIoSpiConfigControlOffset (SpiNumber),
                            PsfSerialIoSpiPort (SpiNumber)
                            );
      PciCfgBase = GetSerialIoSpiFixedPciCfgAddress (SpiNumber);
      Hidden     = TRUE;
      break;
    case SerialIoSpiPci:
      SerialIoPciSave (PciCfgBase, &PciState);
      SerialIoPciEnable (GetSerialIoSpiConfigControlOffset (SpiNumber), PsfSerialIoSpiPort (SpiNumber));
      TempBar = TRUE;
      break;
    default:
      return;
  }

  if (SerialIoMmioEnable (PciCfgBase, TempBar, Hidden, &Base)) {
    SerialIoSpiChipSelectConfig (Base, SpiDeviceConfig);
    SerialIoSpiMNDividerConfig (Base);
    if (SpiDeviceConfig->Mode == SerialIoSpiPci) {
      if (PciState.PciCfgBar0 == 0x0) {
        SerialIoSetD3 (PciCfgBase);
        SerialIoMmioDisable (PciCfgBase, TempBar);
      } else {
        SerialIoPciRestore (PciCfgBase, &PciState);
      }
    }
  }

  SerialIoSpiGpioConfiguration (SpiNumber, SpiDeviceConfig);
}

/**
  Configures Serial IO Spi Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoSpiInit (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  )
{
  UINT8               SpiNumber;
  UINT8               InterruptPin;
  UINT8               Irq;
  EFI_STATUS          Status;
  PCH_GENERAL_CONFIG  *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "SerialIoSpiInit() Start\n"));

  for (SpiNumber = 0; SpiNumber < GetPchMaxSerialIoSpiControllersNum (); SpiNumber++) {
    if ((SerialIoConfig->SpiDeviceConfig[SpiNumber].Mode == SerialIoSpiDisabled) &&
        (GetSerialIoSpiFunctionNumber (SpiNumber) == 0x0)) {
      continue;
    }
    if (SerialIoConfig->SpiDeviceConfig[SpiNumber].Mode != SerialIoSpiDisabled) {
      ItssGetDevIntConfig (SiPolicy, GetSerialIoSpiDeviceNumber (SpiNumber), GetSerialIoSpiFunctionNumber (SpiNumber), &InterruptPin, &Irq);
      SerialIoInterruptSet (GetSerialIoSpiConfigControlOffset (SpiNumber), InterruptPin, Irq);
    }
    if (SerialIoConfig->SpiDeviceConfig[SpiNumber].Mode == SerialIoSpiHidden) {
      DEBUG ((DEBUG_INFO, "Skipped LPSS SPI%d configuration as it is in Hidden mode\n", SpiNumber + 1));
      continue;
    }
    SerialIoSpiConfiguration (SpiNumber, &SerialIoConfig->SpiDeviceConfig[SpiNumber], TRUE, (BOOLEAN) PchGeneralConfig->PchMasterPowerGating);
  }

  DEBUG ((DEBUG_INFO, "SerialIoSpiInit() End\n"));
}

/**
  Configures Serial IO Spi Function 0 Disabled Controllers

  @param[in] SiPolicy         Silicon policy
  @param[in] SerialIoConfig   SerialIo Config Block

**/
VOID
SerialIoSpiFunction0Disable (
  IN SI_POLICY_PPI               *SiPolicy,
  IN SERIAL_IO_CONFIG            *SerialIoConfig
  )
{
  UINT8    SpiNumber;
  BOOLEAN  PsfDisable;
  UINT8    InterruptPin;
  UINT8    Irq;

  for (SpiNumber = 0; SpiNumber < GetPchMaxSerialIoSpiControllersNum (); SpiNumber++) {
    PsfDisable = TRUE;
    if ((SerialIoConfig->SpiDeviceConfig[SpiNumber].Mode == SerialIoSpiDisabled) &&
        (GetSerialIoSpiFunctionNumber (SpiNumber) == 0x0)) {
      if (SerialIoHigherFunctionsEnabled (GetSerialIoSpiDeviceNumber (SpiNumber))) {
        SerialIoBar1Disable (GetSerialIoSpiConfigControlOffset (SpiNumber), PsfSerialIoSpiPort (SpiNumber));
        ItssGetDevIntConfig (SiPolicy, GetSerialIoSpiDeviceNumber (SpiNumber), GetSerialIoSpiFunctionNumber (SpiNumber), &InterruptPin, &Irq);
        SerialIoInterruptSet (GetSerialIoSpiConfigControlOffset (SpiNumber), InterruptPin, Irq);
        PsfDisable = FALSE;
      }
      SerialIoSpiConfiguration (SpiNumber, &SerialIoConfig->SpiDeviceConfig[SpiNumber], PsfDisable, TRUE);
    }
  }
}


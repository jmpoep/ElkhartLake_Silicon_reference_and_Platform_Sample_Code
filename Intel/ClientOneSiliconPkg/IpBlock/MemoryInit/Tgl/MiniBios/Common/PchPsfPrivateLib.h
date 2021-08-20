/** @file
  Header file for PchPsfPrivateLib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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
#ifndef _PCH_PSF_PRIVATE_LIB_H_
#define _PCH_PSF_PRIVATE_LIB_H_

#include "PchSerialIoLib.h"

/**
  This procedure will enable SerialIO device BAR1 at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)
**/
VOID
PsfEnableSerialIoDeviceBar1 (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  );

/**
  This procedure will disable SerialIO device BAR1 at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)
**/
VOID
PsfDisableSerialIoDeviceBar1 (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  );

/**
  This procedure will disable SerailIO device at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)
**/
VOID
PsfDisableSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  );

/**
  This procedure will hide SerialIo device PciCfgSpace at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)
**/
VOID
PsfHideSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  );

/**
  This procedure will reveal SerialIo device PciCfgSpace at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)
**/
VOID
PsfRevealSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  );

/**
  This procedure will set BARx value for TraceHub ACPI device at PSF level

  @param[in] BarNum          BAR Number (0:BAR0, 1:BAR1)
  @param[in] BarValue        32bit BAR value
**/
VOID
PsfSetTraceHubAcpiDeviceBarValue (
  IN UINT8   BarNum,
  IN UINT32  BarValue
  );

/**
  This procedure will enable MSE for TraceHub ACPI device at PSF level
**/
VOID
PsfEnableTraceHubAcpiDeviceMemorySpace (
  VOID
  );

/**
  Enable HECI device at PSF level

  @param[in] HeciDevice       HECIx Device (HECI1-4)
**/
VOID
PsfEnableHeciDevice (
  IN UINT8      HeciDevice
  );

/**
  Disable HECI device at PSF level

  @param[in] HeciDevice       HECIx Device (HECI1-4)
**/
VOID
PsfDisableHeciDevice (
  IN UINT8      HeciDevice
  );

/**
  Disable IDER device at PSF level
**/
VOID
PsfDisableIderDevice (
  VOID
  );

/**
  Enable SOL device at PSF level
**/
VOID
PsfEnableSolDevice (
  VOID
  );

/**
  Disable SOL device at PSF level
**/
VOID
PsfDisableSolDevice (
  VOID
  );

/**
  Set PMC ABASE value in PSF

  @param[in] Address     Address for ACPI base.
**/
VOID
PsfSetPmcAbase (
  IN  UINT16       Address
  );

/**
  Get PMC ABASE value from PSF

  @retval Address     Address for ACPI base.
**/
UINT16
PsfGetPmcAbase (
  VOID
  );

/**
  Get PMC PWRMBASE value from PSF

  @retval Address     Address for PWRM base.
**/
UINT32
PsfGetPmcPwrmBase (
  VOID
  );

/**
  Hide Cnvi WiFi device's PciCfgSpace at PSF level
**/
VOID
PsfHideCnviWifiDevice (
  VOID
  );

/**
  Disable Cnvi Wifi device at PSF level
**/
VOID
PsfDisableCnviWifiDevice (
  VOID
  );

/**
  Disable HDAudio device at PSF level
**/
VOID
PsfDisableHdaDevice (
  VOID
  );

/**
  Disable xDCI device at PSF level
**/
VOID
PsfDisableXdciDevice (
  VOID
  );

/**
  Disable xHCI device at PSF level
**/
VOID
PsfDisableXhciDevice (
  VOID
  );

/**
  Disable xHCI VTIO Phantom device at PSF level
**/
VOID
PsfDisableXhciVtioDevice (
  VOID
  );

/**
  Disable SATA device at PSF level

  @param[in]  SataCtrlIndex     SATA controller index
**/
VOID
PsfDisableSataDevice (
  IN UINT32     SataCtrlIndex
  );

typedef enum {
  PchPsfEmmc = 0,
  PchPsfSdio,
  PchPsfSdcard,
  PchPsfUfs,
  PchPsfMaxScsDevNum
} PCH_PSF_SCS_DEV_NUM;

/**
  Disable SCS device at PSF level

  @param[in] ScsDevNum   SCS Device
**/
VOID
PsfDisableScsDevice (
  IN PCH_PSF_SCS_DEV_NUM  ScsDevNum
  );

/**
  Disable SCS devices BAR1 PSF level

  @param[in] ScsDevNum   SCS Device
**/
VOID
PsfDisableScsBar1 (
  IN PCH_PSF_SCS_DEV_NUM  ScsDevNum
  );

/**
  Disable ISH device at PSF level
**/
VOID
PsfDisableIshDevice (
  VOID
  );

/**
  Disable ISH BAR1 at PSF level
**/
VOID
PsfDisableIshBar1 (
  VOID
  );

/**
  Disable GbE device at PSF level
**/
VOID
PsfDisableGbeDevice (
  VOID
  );

/**
  Disable SMBUS device at PSF level
**/
VOID
PsfDisableSmbusDevice (
  VOID
  );

/**
  Hide TraceHub ACPI devices PciCfgSpace at PSF level
**/
VOID
PsfHideTraceHubAcpiDevice (
  VOID
  );

/**
  This procedure will hide TraceHub PciCfgSpace at PSF level
**/
VOID
PsfHideTraceHubDevice (
  VOID
  );

/**
  This procedure will reveal TraceHub PciCfgSpace at PSF level
**/
VOID
PsfRevealTraceHubDevice (
  VOID
  );

/**
  This procedure will disable TraceHub device at PSF level
**/
VOID
PsfDisableTraceHubDevice (
  VOID
  );

/**
  Configures rootspace 3 bus number for PCIe IMR use

  @param[in] Rs3Bus        bus number
**/
VOID
PsfSetRs3Bus (
  UINT8 Rs3Bus
  );

/**
  Disable PCIe Root Port at PSF level

  @param[in] RpIndex        PCIe Root Port Index (0 based)
**/
VOID
PsfDisablePcieRootPort (
  IN UINT32  RpIndex
  );

/**
  Program PSF grant counts for SATA
  Call this before SATA ports are accessed for enumeration
**/
VOID
PsfConfigureSataGrantCounts (
  VOID
  );

typedef enum {
  PsfPcieCtrl4x1,
  PsfPcieCtrl1x2_2x1,
  PsfPcieCtrl2x2,
  PsfPcieCtrl1x4
} PSF_PCIE_CTRL_CONFIG;

/**
  Program PSF grant counts for PCI express depending on controllers configuration

  @param[in] PsfPcieCtrlConfigTable   Table with PCIe controllers configuration
  @param[in] NumberOfPcieControllers  Number of PCIe controllers. This is also the size of PsfPcieCtrlConfig table
**/
VOID
PsfConfigurePcieGrantCounts (
  IN PSF_PCIE_CTRL_CONFIG  *PsfPcieCtrlConfigTable,
  IN UINT32                NumberOfPcieControllers
  );

/**
  Program PSF EOI Multicast configuration for ITSS
**/
VOID
PsfConfigurEoiForItss (
  VOID
  );

/**
  This function enables EOI message forwarding in PSF for PCIe ports
  for cases where IOAPIC is present behind this root port.

  @param[in] RpIndex        Root port index (0 based)

  @retval Status
**/
EFI_STATUS
PsfConfigurEoiForPciePort (
  IN  UINT32   RpIndex
  );

/**
  PSF early initialization.
**/
VOID
PsfEarlyInit (
  VOID
  );

/**
  Assign new function number for PCIe Port Number.

  @param[in] RpIndex        PCIe Root Port Index (0 based)
  @param[in] NewFunction    New Function number
**/
VOID
PsfSetPcieFunction (
  IN UINT32  RpIndex,
  IN UINT32  NewFunction
  );

/**
  This function enables PCIe Relaxed Order in PSF
**/
VOID
PsfEnablePcieRelaxedOrder (
  VOID
  );

/**
  Configure PSF power management.
  Must be called after all PSF configuration is completed.
**/
VOID
PsfConfigurePowerManagement (
  VOID
  );

/**
  Enable VTd support in PSF.
**/
VOID
PchPsfEnableVtd (
  VOID
  );

/**
  Disable PSF address-based peer-to-peer decoding.
**/
VOID
PchPsfDisableP2pDecoding (
  VOID
  );


/**
  This procedure will hide PMC device at PSF level
**/
VOID
PsfHidePmcDevice (
  VOID
  );

/**
  This procedure will disable D3:F0 device at PSF level for PCH-LP
**/
VOID
PsfDisableD3F0 (
  VOID
  );

/**
  This procedure will disable PSF upstream completion tracking for HDAudio on PCH-LP
**/
VOID
PsfDisableUpstreamCompletionTrackingForHda (
  VOID
  );

#endif // _PCH_PSF_PRIVATE_LIB_H_

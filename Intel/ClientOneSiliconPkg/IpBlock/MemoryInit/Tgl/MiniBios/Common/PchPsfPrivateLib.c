/** @file
  This file contains PSF routines for RC usage

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#include "PchAccess.h"
#include "PchPcrLib.h"
#include "PsfLib.h"
#include "PsfLibInternal.h"
#include "PchSerialIoLib.h"

/**
  Disable device at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort  PSF PORT data structure
**/
VOID
PsfDisableDevice (
  IN PSF_PORT  PsfPort
  )
{
  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    0xFFFFFFFF,
    B_PCH_PSFX_PCR_T0_SHDW_PCIEN_FUNDIS
    );
}

/**
  Enable device at PSF level

  @param[in] PsfPort  PSF PORT data structure
**/
VOID
PsfEnableDevice (
  IN PSF_PORT  PsfPort
  )
{
  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    (UINT32) ~(B_PCH_PSFX_PCR_T0_SHDW_PCIEN_FUNDIS),
    0
    );
}

/**
  Hide PciCfgSpace of device at PSF level

  @param[in] PsfPort  PSF PORT data structure
**/
VOID
PsfHideDevice (
  IN PSF_PORT  PsfPort
  )
{
  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_CFG_DIS,
    0xFFFFFFFF,
    B_PCH_PSFX_PCR_T0_SHDW_CFG_DIS_CFGDIS
    );
}

/**
  Reveal PciCfgSpace of device at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort  PSF PORT data structure
**/
VOID
PsfRevealDevice (
  IN PSF_PORT  PsfPort
  )
{
  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_CFG_DIS,
    (UINT32) ~(B_PCH_PSFX_PCR_T0_SHDW_CFG_DIS_CFGDIS),
    0
    );
}

/**
  Configures rootspace 3 bus number for PCIe IMR use

  @param[in] Rs3Bus        bus number
**/
VOID
PsfSetRs3Bus (
  UINT8 Rs3Bus
  )
{
  PchPcrWrite32 (PID_PSF1, R_PCH_PSF_PCR_BUS_SHADOW_RS3, Rs3Bus);
}

/**
  Disable device BARs at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort     PSF PORT data structure
  @param[in] BarDisMask  BIT0-BAR0, BIT1-BAR1,...
                         Mask corresponds to 32bit wide BARs
**/
VOID
PsfDisableDeviceBar (
  IN PSF_PORT  PsfPort,
  IN UINT32    BarDisMask
  )
{
  //
  // BAR0-5 supported
  //
  ASSERT (BarDisMask < BIT6);

  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    0xFFFFFFFF,
    BarDisMask << N_PCH_PSFX_PCR_T0_SHDW_PCIEN_BARXDIS
    );
}

/**
  Enable device BARs at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort     PSF PORT data structure
  @param[in] BarEnMask   BIT0-BAR0, BIT1-BAR1,...
                         Mask corresponds to 32bit wide BARs
**/
VOID
PsfEnableDeviceBar (
  IN PSF_PORT  PsfPort,
  IN UINT32    BarEnMask
  )
{
  //
  // BAR0-5 supported
  //
  ASSERT (BarEnMask < BIT6);

  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    (UINT32)~(BarEnMask << N_PCH_PSFX_PCR_T0_SHDW_PCIEN_BARXDIS),
    0
    );
}

/**
  Disable device IOSpace at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort     PSF PORT data structure
**/
VOID
PsfDisableDeviceIoSpace (
  IN PSF_PORT  PsfPort
  )
{
  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    ~(UINT32)(B_PCH_PSFX_PCR_T0_SHDW_PCIEN_IOEN),
    0
    );
}

/**
  Enable device IOSpace at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort     PSF PORT data structure
**/
VOID
PsfEnableDeviceIoSpace (
  IN PSF_PORT  PsfPort
  )
{
  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    0xFFFFFFFF,
    B_PCH_PSFX_PCR_T0_SHDW_PCIEN_IOEN
    );
}

/**
  Disable device Memory Space at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort     PSF PORT data structure
**/
VOID
PsfDisableDeviceMemSpace (
  IN PSF_PORT  PsfPort
  )
{
  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    ~(UINT32)(B_PCH_PSFX_PCR_T0_SHDW_PCIEN_MEMEN),
    0
    );
}

/**
  Enable device Memory Space at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort     PSF PORT data structure
**/
VOID
PsfEnableDeviceMemSpace (
  IN PSF_PORT  PsfPort
  )
{
  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    0xFFFFFFFF,
    B_PCH_PSFX_PCR_T0_SHDW_PCIEN_MEMEN
    );
}

/**
  Set device BARx address at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort     PSF PORT data structure
  @param[in] BarNum      BAR Number (0:BAR0, 1:BAR1, ...)
  @param[in] BarValue    32bit BAR value
**/
VOID
PsfSetDeviceBarValue (
  IN PSF_PORT  PsfPort,
  IN UINT8     BarNum,
  IN UINT32    BarValue
  )
{
  //ASSERT (BarNum < 6);

  PchPcrAndThenOr32 (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_BAR0 + BarNum * 0x4,
    0x0,
    BarValue
    );
}

/**
  This procedure will enable SerialIO device BAR1 at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)
**/
VOID
PsfEnableSerialIoDeviceBar1 (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  )
{
  //
  // Set AGNT_T0_SHDW_PCIEN[19:18] = 00b
  // SerialIo device BAR is 64bit wide so to enable BAR1
  // at PSF both BAR2 (32bit wide) and BAR3 (32bit wide) need to be enabled
  //
  PsfEnableDeviceBar (PsfSerialIoPort (SerialIoDevice), (BIT3 | BIT2));
}

/**
  Disable SerialIO device BAR1 at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)
**/
VOID
PsfDisableSerialIoDeviceBar1 (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  )
{
  //
  // Set AGNT_T0_SHDW_PCIEN[19:18] = 11b
  // SerialIo device BAR is 64bit wide so to disable BAR1
  // at PSF both BAR2 (32bit wide) and BAR3 (32bit wide) need to be disabled
  //
  PsfDisableDeviceBar (PsfSerialIoPort (SerialIoDevice), (BIT3 | BIT2));
}

/**
  Disable SerailIO device at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)
**/
VOID
PsfDisableSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  )
{
  PsfDisableDevice (PsfSerialIoPort (SerialIoDevice));
}

/**
  Hide SerialIo device PciCfgSpace at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)
**/
VOID
PsfHideSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  )
{
  PsfHideDevice (PsfSerialIoPort (SerialIoDevice));
}

/**
  Reveal SerialIo device PciCfgSpace at PSF level

  @param[in] SerialIoDevice  SERIAL IO device (I2C0-5, SPI0-1, UART0-2)
**/
VOID
PsfRevealSerialIoDevice (
  IN PCH_SERIAL_IO_CONTROLLER  SerialIoDevice
  )
{
  PsfRevealDevice (PsfSerialIoPort (SerialIoDevice));
}

/**
  Hide TraceHub PciCfgSpace at PSF level
**/
VOID
PsfHideTraceHubDevice (
  VOID
  )
{
  PsfHideDevice (PsfTraceHubPort ());
}

/**
  Reveal TraceHub PciCfgSpace at PSF level
**/
VOID
PsfRevealTraceHubDevice (
  VOID
  )
{
  PsfRevealDevice (PsfTraceHubPort ());
}

/**
  Disable and hide TraceHub device at PSF level
**/
VOID
PsfDisableTraceHubDevice (
  VOID
  )
{
  PsfDisableDevice (PsfTraceHubPort ());
}

/**
  Hide TraceHub ACPI devices PciCfgSpace at PSF level
**/
VOID
PsfHideTraceHubAcpiDevice (
  VOID
  )
{
  PsfHideDevice (PsfTraceHubAcpiDevPort ());
}

/**
  Set BARx value for TraceHub ACPI device at PSF level

  @param[in] BarNum          BAR Number (0:BAR0, 1:BAR1)
  @param[in] BarValue        32bit BAR value
**/
VOID
PsfSetTraceHubAcpiDeviceBarValue (
  IN UINT8   BarNum,
  IN UINT32  BarValue
  )
{
  if (BarNum > 1) {
    ASSERT (FALSE);
  }

  PsfSetDeviceBarValue (PsfTraceHubAcpiDevPort (), BarNum, BarValue);
}

/**
  Enable MSE for TraceHub ACPI device at PSF level
**/
VOID
PsfEnableTraceHubAcpiDeviceMemorySpace (
  VOID
  )
{
  PsfEnableDeviceMemSpace (PsfTraceHubAcpiDevPort ());
}

/**
  Enable HECI device at PSF level

  @param[in] HeciDevice       HECIx Device (HECI1-4)
**/
VOID
PsfEnableHeciDevice (
  IN UINT8      HeciDevice
  )
{
  PsfEnableDevice (PsfHeciPort (HeciDevice));
}

/**
  Disable HECI device at PSF level

  @param[in] HeciDevice       HECIx Device (HECI1-4)
**/
VOID
PsfDisableHeciDevice (
  IN UINT8      HeciDevice
  )
{
  PsfDisableDevice (PsfHeciPort (HeciDevice));
}

/**
  Enable SOL device at PSF level
**/
VOID
PsfEnableSolDevice (
  VOID
  )
{
  PsfEnableDevice (PsfSolPort ());
}

/**
  Disable SOL device at PSF level
**/
VOID
PsfDisableSolDevice (
  VOID
  )
{
  PsfDisableDevice (PsfSolPort ());
}



/**
  Disable SCS device at PSF level

  @param[in] ScsDevNum   SCS Device
**/
VOID
PsfDisableScsDevice (
  IN PCH_PSF_SCS_DEV_NUM  ScsDevNum
  )
{
  if (ScsDevNum >= PchPsfMaxScsDevNum) {
    ASSERT (FALSE);
    return;
  }

  PsfDisableDevice (PsfScsPort (ScsDevNum));
}

/**
  Disable SCS devices BAR1 PSF level

  @param[in] ScsDevNum   SCS Device
**/
VOID
PsfDisableScsBar1 (
  IN PCH_PSF_SCS_DEV_NUM  ScsDevNum
  )
{
  if (ScsDevNum >= PchPsfMaxScsDevNum) {
    ASSERT (FALSE);
    return;
  }

  //
  // Set AGNT_T0_SHDW_PCIEN[19:18] = 11b
  // SCS device BAR is 64bit wide so to disable BAR1
  // at PSF both BAR2 (32bit wide) and BAR3 (32bit wide) need to be disabled
  //
  PsfDisableDeviceBar (PsfScsPort (ScsDevNum), (BIT3 | BIT2));
}



/**
  Check if PCIe Root Port is enabled at PSF1

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval TRUE              PCIe Root Port is enabled
          FALSE             PCIe Root Port is disabled
**/
BOOLEAN
PsfIsPcieRootPortEnabled (
  IN UINT32  RpIndex
  )
{
  return FALSE;
}

/**
  PSF PCIe channel grant counts

  @param[in]  PsfPcieCtrlConfig        PCIe controller configuration
  @param[out] ChannelGrant             4 item array with PCIe Channel Grant Count values
**/
STATIC
VOID
PsfPcieChannelGrantCounts (
  IN  PSF_PCIE_CTRL_CONFIG  PsfPcieCtrlConfig,
  OUT UINT32                *ChannelGrant
  )
{
  switch (PsfPcieCtrlConfig) {
    case PsfPcieCtrl4x1: //Pcie4x1
      ChannelGrant[0] = 1;
      ChannelGrant[1] = 1;
      ChannelGrant[2] = 1;
      ChannelGrant[3] = 1;
      break;
    case PsfPcieCtrl1x2_2x1: //Pcie1x2_2x1
      ChannelGrant[0] = 2;
      ChannelGrant[1] = DEFAULT_PCIE_GRANT_COUNT;
      ChannelGrant[2] = 1;
      ChannelGrant[3] = 1;
      break;
    case PsfPcieCtrl2x2: //Pcie2x2
      ChannelGrant[0] = 2;
      ChannelGrant[1] = DEFAULT_PCIE_GRANT_COUNT;
      ChannelGrant[2] = 2;
      ChannelGrant[3] = DEFAULT_PCIE_GRANT_COUNT;
      break;
    case PsfPcieCtrl1x4: //Pcie1x4
      ChannelGrant[0] = 4;
      ChannelGrant[1] = DEFAULT_PCIE_GRANT_COUNT;
      ChannelGrant[2] = DEFAULT_PCIE_GRANT_COUNT;
      ChannelGrant[3] = DEFAULT_PCIE_GRANT_COUNT;
      break;
    default:
      ASSERT (FALSE);
      break;
  }
}

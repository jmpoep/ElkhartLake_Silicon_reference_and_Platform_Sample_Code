/** @file
  This file contains internal PSF routines for PCH PSF EHL lib usage

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/SataLib.h>
#include <Library/BaseMemoryLib.h>
#include <Register/PchRegsPsf.h>
#include <Register/PsfRegsVer3.h>
#include "PsfLibInternal.h"
#include <PchPcieRpInfo.h>

GLOBAL_REMOVE_IF_UNREFERENCED PSF_PORT mPchLpSerialIoI2cPsfPort[] =
{
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C0_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C1_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C2_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C3_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C4_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C5_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C6_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C7_REG_BASE}
};

// Arrangement of this array is based on PCH_PSE_IO_CONTROLLER enum,
// not based on the sequence of the REG_BASE value.
GLOBAL_REMOVE_IF_UNREFERENCED PSF_PORT mPchPsePsfPort[] =
{
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C0_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C1_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C2_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C3_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C4_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C5_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C6_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C7_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART0_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART1_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART2_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART3_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART4_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART5_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_SPI0_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_SPI1_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_SPI2_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_SPI3_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_TSN_GBE0_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_TSN_GBE1_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_CAN0_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_CAN1_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_GPIO0_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_GPIO1_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_DMA0_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_DMA1_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_DMA2_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_QEP0_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_QEP1_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_QEP2_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_QEP3_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2S0_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2S1_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_PWM_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_ADC_REG_BASE},
  {PID_PSF1, R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_LH2PSE_IPC_REG_BASE}
};

/**
  Return PSF_PORT for SerialIO I2C device

  @param[in] I2cNum  Serial IO I2C device (I2C0, I2C1, ....)

  @retval  PsfPort   PSF PORT structure for SerialIO I2C device
**/
PSF_PORT
PsfSerialIoI2cPort (
  IN UINT32  I2cNum
  )
{
  if (IsPchLp ()) {
    if (I2cNum < ARRAY_SIZE(mPchLpSerialIoI2cPsfPort)) {
      return mPchLpSerialIoI2cPsfPort[I2cNum];
    }
  }

  ASSERT(FALSE);
  return PSF_PORT_NULL;
}

GLOBAL_REMOVE_IF_UNREFERENCED PSF_PORT mPchLpSerialIoSpiPsfPort[] =
{
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SPI0_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SPI1_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SPI2_REG_BASE}
};

/**
  Return PSF_PORT for SerialIO SPI device

  @param[in] I2cNum  Serial IO SPI device (SPI0, SPI1, ....)

  @retval  PsfPort   PSF PORT structure for SerialIO SPI device
**/
PSF_PORT
PsfSerialIoSpiPort (
  IN UINT32  SpiNum
  )
{
  if (IsPchLp ()) {
    if (SpiNum < ARRAY_SIZE(mPchLpSerialIoSpiPsfPort)) {
      return mPchLpSerialIoSpiPsfPort[SpiNum];
    }
  }

  ASSERT(FALSE);
  return PSF_PORT_NULL;
}

GLOBAL_REMOVE_IF_UNREFERENCED PSF_PORT mPchLpSerialIoUartPsfPort[] =
{
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_UART0_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_UART1_REG_BASE},
  {PID_PSF3, R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_UART2_REG_BASE}
};

/**
  Return PSF_PORT for SerialIO UART device

  @param[in] UartNum  Serial IO UART device (UART0, UART1, ....)

  @retval  PsfPort   PSF PORT structure for SerialIO UART device
**/
PSF_PORT
PsfSerialIoUartPort (
  IN UINT32  UartNum
  )
{
  if (IsPchLp ()) {
    if (UartNum < ARRAY_SIZE(mPchLpSerialIoUartPsfPort)) {
      return mPchLpSerialIoUartPsfPort[UartNum];
    }
  }

  ASSERT(FALSE);
  return PSF_PORT_NULL;
}

/**
  Return PSF_PORT for TraceHub device

  @retval    PsfPort         PSF PORT structure for TraceHub device
**/
PSF_PORT
PsfTraceHubPort (
  VOID
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  if (IsPchLp ()) {
    PsfPort.PsfPid = PID_PSF1;
    PsfPort.RegBase = R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_TRACEHUB_REG_BASE;
  }
  return PsfPort;
}

/**
  Return PSF_PORT for TraceHub ACPI device

  @retval    PsfPort         PSF PORT structure for TraceHub ACPI device
**/
PSF_PORT
PsfTraceHubAcpiDevPort (
  VOID
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  if (IsPchLp ()) {
    PsfPort.PsfPid = PID_PSF1;
    PsfPort.RegBase = R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_NPK_PHANTOM_REG_BASE;
  }
  return PsfPort;
}

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchLpHeciPsfRegBase[] =
{
  R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_HECI1_REG_BASE,
  R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_HECI2_REG_BASE,
  R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_HECI3_REG_BASE,
  R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_HECI4_REG_BASE
};

/**
  Return PSF_PORT for HECI device

  @param[in] HeciDevice      HECIx Device (HECI1-4)

  @retval    PsfPort         PSF PORT structure for HECI device
**/
PSF_PORT
PsfHeciPort (
  IN UINT8      HeciDevice
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));

  if ((HeciDevice < 1) || (HeciDevice > 4)) {
    ASSERT (FALSE);
    return PSF_PORT_NULL;
  }

  PsfPort.PsfPid = PID_PSF2;

  if (IsPchLp ()) {
    PsfPort.RegBase = mPchLpHeciPsfRegBase[HeciDevice - 1];
  }
  return PsfPort;
}

/**
  Return PSF_PORT for SOL device

  @retval    PsfPort         PSF PORT structure for SOL device
**/
PSF_PORT
PsfSolPort (
  VOID
  )
{
  return PSF_PORT_NULL;
}

/**
  Disable IDER device at PSF level
**/
VOID
PsfDisableIderDevice (
  VOID
  )
{

}

/**
  Disable HDAudio device at PSF level
**/
VOID
PsfDisableHdaDevice (
  VOID
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  if (IsPchLp ()) {
    PsfPort.PsfPid = PID_PSF3;
    PsfPort.RegBase = R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_AUD_REG_BASE;
  }
  PsfDisableDevice (PsfPort);
}

/**
  Disable DSP Bar (HdAudio BAR4 and BAR5) at PSF level.
**/
VOID
PsfDisableDspBar (
  VOID
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  if (IsPchLp ()) {
    PsfPort.PsfPid = PID_PSF3;
    PsfPort.RegBase = R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_AUD_REG_BASE;
  }
  PsfDisableDeviceBar (PsfPort, (R_PCH_PSFX_PCR_T0_SHDW_BAR5 | R_PCH_PSFX_PCR_T0_SHDW_BAR4));
}

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchLpThcPsfRegBase[] =
{
  R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_THC0_REG_BASE,
  R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_THC1_REG_BASE
};

/**
  Disable THC device at PSF level

  @param[in]  ThcNumber                Touch Host Controller Number THC0 or THC1
**/
VOID
PsfDisableThcDevice (
  IN  UINT32        ThcNumber
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  if (IsPchLp () && ThcNumber < ARRAY_SIZE (mPchLpThcPsfRegBase)) {
    PsfPort.PsfPid  = PID_PSF2;
    PsfPort.RegBase = mPchLpThcPsfRegBase[ThcNumber];
  }
  // @todo: add conditions for TGL-PCH-H/K
  PsfDisableDevice (PsfPort);
}

/**
  Disable xDCI device at PSF level
**/
VOID
PsfDisableXdciDevice (
  VOID
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  if (IsPchLp ()) {
    PsfPort.PsfPid = PID_PSF2;
    PsfPort.RegBase = R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_XDCI_REG_BASE;
  }
  PsfDisableDevice (PsfPort);
}

/**
  Enable xDCI device at PSF level
**/
VOID
PsfEnableXdciDevice (
  VOID
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  if (IsPchLp ()) {
    PsfPort.PsfPid = PID_PSF2;
    PsfPort.RegBase = R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_XDCI_REG_BASE;
  }
  PsfEnableDevice (PsfPort);
}

/**
  Disable xHCI device at PSF level
**/
VOID
PsfDisableXhciDevice (
  VOID
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  if (IsPchLp ()) {
    PsfPort.PsfPid = PID_PSF1;
    PsfPort.RegBase = R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_XHCI_REG_BASE;
  }
  PsfDisableDevice (PsfPort);
}

/**
  Disable xHCI VTIO Phantom device at PSF level
**/
VOID
PsfDisableXhciVtioDevice (
  VOID
  )
{
  // Not applicable for EHL platform
}

/**
  Disable SATA device at PSF level

  @param[in]  SataCtrlIndex     SATA controller index
**/
VOID
PsfDisableSataDevice (
  IN UINT32     SataCtrlIndex
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  ASSERT (SataCtrlIndex < 1);

  PsfPort.PsfPid = PID_PSF1;

  if (IsPchLp ()) {
    PsfPort.RegBase = R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_SATA_REG_BASE;
  }
  PsfDisableDevice (PsfPort);
}


/**
  Program PSF grant counts for SATA
  Call this before SATA ports are accessed for enumeration
**/
VOID
PsfConfigureSataGrantCounts (
  VOID
  )
{
  // No configuration needed for EHL-PCH
  return;
}


/**
  Return PSF_PORT for ISH device

  @retval    PsfPort         PSF PORT structure for ISH device
**/
PSF_PORT
PsfIshPort (
  VOID
  )
{
  return PSF_PORT_NULL;
}

/**
  Disable FPAK device at PSF level
**/
VOID
PsfDisableFpakDevice (
  VOID
  )
{
  return;
}

/**
  Return PSF_PORT for PSE device

  @param[in]  PseCtrlIndex    PSE controller index
  @retval     PsfPort         PSF PORT structure for PSE device
**/
PSF_PORT
PsfPsePort (
  IN UINT32  PseCtrlIndex
  )
{
  PSF_PORT PsfPort;

  if (PseCtrlIndex < ARRAY_SIZE(mPchPsePsfPort)) {
    PsfPort = mPchPsePsfPort[PseCtrlIndex];
    return PsfPort;
  } else {
    return PSF_PORT_NULL;
  }
}

/**
  Return PSF_PORT for Gbe TSN device

  @retval    PsfPort         PSF PORT structure for Gbe TSN device
**/
PSF_PORT
PsfTsnPort (
  VOID
  )
{
  PSF_PORT PsfPort;

  PsfPort.PsfPid = PID_PSF2;
  PsfPort.RegBase = R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_GBETSN_REG_BASE;
  return PsfPort;
}

/**
  Disable GbE device at PSF level
**/
VOID
PsfDisableGbeDevice (
  VOID
  )
{

}

/**
  Disable SMBUS device at PSF level
**/
VOID
PsfDisableSmbusDevice (
  VOID
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  PsfPort.PsfPid = PID_PSF3;
  if (IsPchLp ()) {
    PsfPort.RegBase = R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SMBUS_REG_BASE;
  }

  PsfDisableDevice (PsfPort);
}

/**
  Return PSF_PORT for SCS eMMC device

  @retval    PsfPort      PSF PORT structure for SCS eMMC device
**/
PSF_PORT
PsfScsEmmcPort (
  VOID
  )
{
  PSF_PORT PsfPort;

  if (IsPchLp ()) {
    PsfPort.RegBase = R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_EMMC_REG_BASE;
    PsfPort.PsfPid = PID_PSF3;
    return PsfPort;
  }

  ASSERT (FALSE);
  return PSF_PORT_NULL;
}

/**
  Return PSF_PORT for SCI device

  @retval    PsfPort      PSF PORT structure for SCI device
**/
PSF_PORT
PsfSciPort (
  VOID
  )
{
  PSF_PORT PsfPort;

  if (IsPchLp ()) {
    PsfPort.RegBase = R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_ISI_REG_BASE;
    PsfPort.PsfPid = PID_PSF3;
    return PsfPort;
  }

  ASSERT (FALSE);
  return PSF_PORT_NULL;
}

/**
  Return PSF_PORT for SCS SD Card device

  @retval    PsfPort      PSF PORT structure for SCS SD Card device
**/
PSF_PORT
PsfScsSdCardPort (
  VOID
  )
{
  PSF_PORT PsfPort;

  PsfPort.PsfPid = PID_PSF3;

  PsfPort.RegBase = R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SDCARD_REG_BASE;

  return PsfPort;
}

GLOBAL_REMOVE_IF_UNREFERENCED PSF_PORT mPchLpScsUfsPsfPort[] =
{
  {PID_PSF2, R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_UFS1_REG_BASE},  // UFS #1
  {PID_PSF2, R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_UFS2_REG_BASE}   // UFS #2
};

/**
  Return PSF_PORT for SCS UFS device

  @param[in] UfsNum       UFS Device

  @retval    PsfPort      PSF PORT structure for SCS UFS device
**/
PSF_PORT
PsfScsUfsPort (
  IN UINT32  UfsNum
  )
{
  if (IsPchLp ()) {
    if (UfsNum < ARRAY_SIZE(mPchLpScsUfsPsfPort)) {
      return mPchLpScsUfsPsfPort[UfsNum];
    }
  }

  ASSERT(FALSE);
  return PSF_PORT_NULL;
}

//
// RS0 PSF1_T1_SHDW_PCIExx_REG_BASE registers for PCH-LP
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchLpPsf1PcieRegBase[] =
{
  R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE01_RS0_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE02_RS0_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE03_RS0_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE04_RS0_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE05_RS0_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE06_RS0_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE07_RS0_REG_BASE
};

//
// RS3 PSF1_T0_SHDW_PCIExx_REG_BASE registers for PCH-LP
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchLpPsf1Rs3PcieRegBase[] =
{
  R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE01_RS3_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE02_RS3_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE03_RS3_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE04_RS3_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE05_RS3_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE06_RS3_REG_BASE,
  R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE07_RS3_REG_BASE
};

/**
  Return second level PSF_PORT to which PCIE Root Port device is connected (directly)

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval    PsfPort        PSF PORT structure for PCIe
**/
PSF_PORT
PsfPcieSecondLevelPort (
  IN UINT32  RpIndex
  )
{
  // Not applicable for EHL platform
  return PSF_PORT_NULL;
}

/**
  Return PSF_PORT at root PSF level to which PCIe Root Port device is connected

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval    PsfPort        PSF PORT structure for PCIe

**/
PSF_PORT
PsfRootPciePort (
  IN UINT32  RpIndex
  )
{
  PSF_PORT PsfPort;

  if (IsPchLp ()) {
    if (RpIndex < ARRAY_SIZE (mPchLpPsf1PcieRegBase)) {
      PsfPort.PsfPid = PID_PSF1;
      PsfPort.RegBase = mPchLpPsf1PcieRegBase[RpIndex];
      return PsfPort;
    }
  }

  ASSERT (FALSE);
  return PSF_PORT_NULL;
}

/**
  Return RS3 PSF_PORT at root PSF level to which PCIe Root Port device is connected

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval    PsfPort        PSF PORT structure for PCIe
**/
PSF_PORT
PsfRootRs3PciePort (
  IN UINT32  RpIndex
  )
{
  PSF_PORT PsfPort;

  if (IsPchLp ()) {
    if (RpIndex > 3) {
      return PSF_PORT_NULL;
    }

    if (RpIndex < ARRAY_SIZE (mPchLpPsf1Rs3PcieRegBase)) {
      PsfPort.PsfPid = PID_PSF1;
      PsfPort.RegBase = mPchLpPsf1Rs3PcieRegBase[RpIndex];
      return PsfPort;
    }
  }

  ASSERT (FALSE);
  return PSF_PORT_NULL;
}

/**
  Grant count regs data for PSF that is directly connected to PCIe Root Ports

  @param[in]  Controller     PCIe Root Port Controller index (0 based)
  @param[out] GrantCountReg  Structure with PSF Grant Count register data
**/
VOID
PsfPcieGrantCountBaseReg (
  IN  UINT8                Controller,
  OUT PSF_GRANT_COUNT_REG  *GrantCountReg
  )
{
  if (IsPchLp ()) {
    GrantCountReg->PsfPid = PID_PSF1;
    GrantCountReg->DevGntCnt0Base = R_VER3_PCH_LP_PSF1_PCR_DEV_GNTCNT_RELOAD_DGCR0;
    GrantCountReg->TargetGntCntPg1Tgt0Base = R_VER3_PCH_LP_PSF1_PCR_TARGET_GNTCNT_RELOAD_PG1_TGT0;
  }
  // @todo: add support for TGL-PCH-H/K
}

GLOBAL_REMOVE_IF_UNREFERENCED CONST UINT8 mDgcrLp [][PCH_PCIE_CONTROLLER_PORTS] = {
    { 11, 12, 13, 14 }, //SPA
    {  1, 15, 18, 21 }, //SPB
    {  9, 16, 19, 22 }, //SPC
    {  8, 17, 20, 23 }  //SPD
  };

GLOBAL_REMOVE_IF_UNREFERENCED CONST UINT8 mPgTgtLp [][PCH_PCIE_CONTROLLER_PORTS] = {
    {  0,  1,  2,  3 }, //SPA
    {  5,  6,  7,  8 }, //SPB
    { 10, 11, 12, 13 }, //SPC
    { 15, 16, 17, 18 }  //SPD
  };

/**
  Get Grant Count number (Device Grant Count and Target Grant Count)
  for PSF that is directly connected to PCIe Root Ports

  @param[in]  Controller    PCIe Root Port Controller index
  @param[in]  Channel       PCIe Root Port Channel index
  @param[out] DgcrNo        Device Grant Count number
  @param[out] PgTgtNo       Target Grant Count number
**/
VOID
PsfPcieGrantCountNumber (
  IN  UINT8 Controller,
  IN  UINT8 Channel,
  OUT UINT8 *DgcrNo,
  OUT UINT8 *PgTgtNo
  )
{
  if (IsPchLp ()) {
    if ((Channel < ARRAY_SIZE (mDgcrLp[0])) && (Controller < ARRAY_SIZE (mDgcrLp))) {
      *DgcrNo = mDgcrLp[Controller][Channel];
      *PgTgtNo = mPgTgtLp[Controller][Channel];
      return;
    }
  }

  ASSERT (FALSE);
}

/**
  Grant count regs data for a given PSF-to-PSF port.

  @param[in] PsfTopoPort         PSF-to-PSF port

  @param[out] GrantCountReg      Structure with PSF Grant Count register data
**/
VOID
PsfSegmentGrantCountBaseReg (
  IN PSF_TOPO_PORT         PsfTopoPort,
  OUT PSF_GRANT_COUNT_REG  *GrantCountReg
  )
{
  ASSERT (FALSE);
}

/**
  Grant Count number (Device Grant Count and Target Grant Count) for a given PSF-to-PSF port.

  @param[in] PsfTopoPort         PSF-to-PSF port
  @param[out] DgcrNo             Device Grant Count number
  @param[out] PgTgtNo            Target Grant Count number
**/
VOID
PsfSegmentGrantCountNumber (
  IN PSF_TOPO_PORT PsfTopoPort,
  OUT UINT8        *DgcrNo,
  OUT UINT8        *PgTgtNo
  )
{
  *DgcrNo = 0;
  *PgTgtNo = 0;
}

//
// PCH-LP PSF topology for PCIe
//
GLOBAL_REMOVE_IF_UNREFERENCED CONST PSF_TOPOLOGY mPchLpPsf1PcieTreeTopo[] = {
  //{PsfId, Port}, PortType, Child, PcieCtrlIndex
  {{1, 0}, PsfPcieCtrlPort, NULL, {0}}, // SPA
  {{1, 1}, PsfPcieCtrlPort, NULL, {1}}, // SPB
  {{1, 2}, PsfPcieCtrlPort, NULL, {2}}, // SPC
  {{1, 3}, PsfPcieCtrlPort, NULL, {3}}, // SPD
  PSF_TOPOLOGY_END
};

GLOBAL_REMOVE_IF_UNREFERENCED CONST PSF_TOPOLOGY mPchLpPsfPcieTreeTopo[] = {
  {{0, 0}, PsfToPsfPort, mPchLpPsf1PcieTreeTopo}, // Abstract root of PSF topology
  PSF_TOPOLOGY_END
};

/**
  Get PSF Pcie Tree topology

  @param[in] PsfTopology          PSF Port from PSF PCIe tree topology

  @retval PsfTopology             PSF PCIe tree topology
**/
CONST PSF_TOPOLOGY*
PsfGetRootPciePsfTopology (
  VOID
  )
{
  if (IsPchLp ()) {
    return mPchLpPsfPcieTreeTopo;
  }
  return NULL;
}

/**
  Get EOI register data for given PSF ID

  @param[in]  PsfId           PSF ID (1 - PSF1, 2 - PSF2, ...)
  @param[out] EoiTargetBase   EOI Target register
  @param[out] EoiControlBase  EOI Control register

  @retval MaxTargets          Number of supported targets

**/
UINT8
PsfEoiRegData (
  UINT32        PsfId,
  UINT16        *EoiTargetBase,
  UINT16        *EoiControlBase
  )
{
  UINT8  MaxTargets;

  MaxTargets = 0;
  *EoiTargetBase = 0;
  *EoiControlBase = 0;

  switch (PsfId) {
    case 1:
      *EoiTargetBase = R_VER3_PCH_LP_PSF1_PCR_MC_AGENT_MCAST0_TGT0_EOI;
      *EoiControlBase = R_VER3_PCH_LP_PSF1_PCR_MC_CONTROL_MCAST0_EOI;
      MaxTargets = 8;
      break;

    case 3:
      *EoiTargetBase = R_VER3_PCH_LP_PSF3_PCR_MC_AGENT_MCAST0_TGT0_EOI;
      *EoiControlBase = R_VER3_PCH_LP_PSF3_PCR_MC_CONTROL_MCAST0_EOI;

      MaxTargets = 1;
      break;

  }
  return MaxTargets;
}

/**
  Get MCTP register data for given PSF ID

  @param[in]  PsfId            PSF ID (1 - PSF1, 2 - PSF2, ...)
  @param[out] MctpTargetBase   MCTP Target register
  @param[out] MctpControlBase  MCTP Control register

  @retval MaxTargets           Number of supported targets

**/
UINT8
PsfMctpRegData (
  UINT32        PsfId,
  UINT16        *MctpTargetBase,
  UINT16        *MctpControlBase
  )
{
  UINT8  MaxTargets;

  MaxTargets = 0;
  *MctpTargetBase = 0;
  *MctpControlBase = 0;

  switch (PsfId) {
    case 1:
      if (IsPchLp ()) {
        // ToDo: EHL no MCAST1 info in RDL
        *MctpTargetBase = 0;
        *MctpControlBase = 0;
        MaxTargets = 0;
        /*
        *MctpTargetBase = R_VER3_PCH_LP_PSF1_PCR_MC_AGENT_MCAST1_RS0_TGT0_MCTP1;
        *MctpControlBase = R_VER3_PCH_LP_PSF1_PCR_MC_CONTROL_MCAST1_RS0_MCTP1;
        MaxTargets = 13;
        */
      }
      break;
  }
  return MaxTargets;
}

/**
  P2SB PSF port Destination ID (psf_id:port_group_id:port_id:channel_id)

  @retval P2SB Destination ID
**/
PSF_PORT_DEST_ID
PsfP2sbDestinationId (
  VOID
  )
{
  PSF_PORT_DEST_ID P2sbTarget;

  P2sbTarget.RegVal = 0;

  if (IsPchLp ()) {
    P2sbTarget.RegVal = V_VER3_PCH_LP_PSFX_PCR_PSF_MC_AGENT_MCAST_TGT_P2SB;
  }
  return P2sbTarget;
}

/**
  DMI PSF port Destination ID (psf_id:port_group_id:port_id:channel_id)

  @retval DMI Destination ID
**/
PSF_PORT_DEST_ID
PsfDmiDestinationId (
  VOID
  )
{
  PSF_PORT_DEST_ID DmiTarget;

  DmiTarget.RegVal = V_VER3_PCH_PSFX_PSF_PCR_MC_AGENT_MCAST_TGT_DMI;

  return DmiTarget;
}

GLOBAL_REMOVE_IF_UNREFERENCED PSF_PORT_DEST_ID PchLpRpDestId[] =
{
  {0x18000}, {0x18001}, {0x18002}, {0x18003}, // SPA: PSF1, PortID = 0
  {0x18100}, {0x18101}, {0x18102}, {0x18103}, // SPB: PSF1, PortID = 1
  {0x18200}, {0x18201}, {0x18202}, {0x18203}, // SPC: PSF1, PortID = 2
  {0x18300}, {0x18301}, {0x18302}, {0x18303}, // SPD: PSF1, PortID = 3
};

/**
  PCIe PSF port destination ID (psf_id:port_group_id:port_id:channel_id)

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval Destination ID
**/
PSF_PORT_DEST_ID
PsfPcieDestinationId (
  IN UINT32  RpIndex
  )
{
  if (IsPchLp ()) {
    if (RpIndex < ARRAY_SIZE(PchLpRpDestId)) {
      return PchLpRpDestId[RpIndex];
    }
  }

  ASSERT (FALSE);
  return (PSF_PORT_DEST_ID){0};
}

//
// RS0 PSF1_T1_AGENT_FUNCTION_CONFIG_SPx_Dxx_Fx registers for PCH-LP
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchLpPsf1PcieFuncCfgBase[] =
{
  R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F0,
  R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F1,
  R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F2,
  R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F3,
  R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_RS0_D28_F4,
  R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_RS0_D28_F5,
  R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPD_RS0_D28_F6
};
//
// RS3 PSF1_T0_AGENT_FUNCTION_CONFIG_SPx_Dxx_Fx registers for PCH-LP
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchLpPsf1Rs3PcieFuncCfgBase[] =
{
  R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F0,
  R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F1,
  R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F2,
  R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F3,
  R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPB_RS3_D28_F4,
  R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPC_RS3_D28_F5,
  R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPD_RS3_D28_F6
};

/**
  Return the PSF (Root level) Function Config PSF_PORT for PCIe Root Port

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval    PsfPort        PSF PORT structure for PCIe Function Config
**/
PSF_PORT
PsfRootPcieFunctionConfigPort (
  IN UINT32  RpIndex
  )
{
  PSF_PORT  PsfPort;

  PsfPort.PsfPid = PID_PSF1;

  if (IsPchLp ()) {
    if (RpIndex < ARRAY_SIZE (mPchLpPsf1PcieFuncCfgBase)) {
      PsfPort.RegBase = mPchLpPsf1PcieFuncCfgBase[RpIndex];
      return PsfPort;
    }
  }

  ASSERT (FALSE);
  return PSF_PORT_NULL;
}

/**
  Return the PSF (Root level) RS3 Function Config PSF_PORT for PCIe Root Port

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval    PsfPort        PSF PORT structure for PCIe Function Config
**/
PSF_PORT
PsfRootRs3PcieFunctionConfigPort (
  IN UINT32  RpIndex
  )
{
  PSF_PORT  PsfPort;

  PsfPort.PsfPid = PID_PSF1;

  if (IsPchLp ()) {
    if (RpIndex < ARRAY_SIZE (mPchLpPsf1Rs3PcieFuncCfgBase)) {
      PsfPort.RegBase = mPchLpPsf1Rs3PcieFuncCfgBase[RpIndex];
      return PsfPort;
    }
  }

  ASSERT (FALSE);
  return PSF_PORT_NULL;
}

/**
  Return the PSF Function Config Second Level PSF_PORT for PCIe Root Port

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval    PsfPort        PSF PORT structure for PCIe Function Config
**/
PSF_PORT
PsfPcieFunctionConfigSecondLevelPort (
  IN UINT32  RpIndex
  )
{
  return PSF_PORT_NULL;
}

/**
  This function enables PCIe Relaxed Order in PSF
**/
VOID
PsfEnablePcieRelaxedOrder (
  VOID
  )
{
  //
  // PCH BIOS Spec Section 8.2.9
  //
  PchPcrAndThenOr32 (
    PID_PSF1,
    R_VER3_PCH_PSF_PCR_PORT_CONFIG_PG0_PORT0,
    ~0u,
    BIT1
    );
}

/**
  Return PSF_PORT for CNVi device

  @retval    PsfPort         PSF PORT structure for CNVi device
**/
PSF_PORT
PsfCnviPort (
  VOID
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  if (IsPchLp ()) {
    PsfPort.PsfPid = PID_PSF3;
    PsfPort.RegBase = R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_CNVI_REG_BASE;
  }
  return PsfPort;
}

/**
  Return PSF_PORT for PMC device

  @retval    PsfPort         PSF PORT structure for PMC device
**/
PSF_PORT
PsfPmcPort (
  VOID
  )
{
  PSF_PORT PsfPort;
  ZeroMem (&PsfPort, sizeof (PsfPort));
  PsfPort.PsfPid = PID_PSF3;

  if (IsPchLp ()) {
    PsfPort.RegBase = R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_PMC_REG_BASE;
  }
  return PsfPort;
}

GLOBAL_REMOVE_IF_UNREFERENCED PSF_SEGMENT mPchLpPsfTable[] =
{
  {1, PID_PSF1},
  {2, PID_PSF2},
  {3, PID_PSF3},
  {4, PID_PSF4},
  {5, PID_PSF5}
};

/**
  Get list of supported PSF segments.

  @param[out] PsfTable        Array of supported PSF segments
  @param[out] PsfTableLength  Length of PsfTable
**/
VOID
PsfSegments (
  OUT PSF_SEGMENT  **PsfTable,
  OUT UINT32       *PsfTableLength
  )
{
  if (IsPchLp ()) {
    *PsfTable = mPchLpPsfTable;
    *PsfTableLength = ARRAY_SIZE (mPchLpPsfTable);
  }
}

/**
  Disable PSF upstream completion tracking for HDAudio on PCH-LP
**/
VOID
PsfDisableUpstreamCompletionTrackingForHda (
  VOID
  )
{
  // Not applicable to TGL platform
  return;
}

/**
  Disable D3:F0 device at PSF level for PCH-LP
**/
VOID
PsfDisableD3F0 (
  VOID
  )
{
  // Not applicable to TGL platform
  // @todo: revise for ALPHA release
  return;
}

/**
  Check if MCTP is supported

  @retval TRUE              MCTP is supported
          FALSE             MCTP is not supported
**/
BOOLEAN
PsfIsMctpSupported (
  VOID
  )
{
  return (IsPchLp () || IsPchH ());
}

#if FixedPcdGetBool(PcdBfxEnable) == 1
/**
  Enable RS3 Channel Mapping for UFS
**/
VOID
PsfRs3ChannelMapEnable (
  VOID
  )
{
  if (PchStepping() == PCH_A0) {
    PchPcrAndThenOr32WithReadback (
      PID_PSF2,
      R_VER3_PCH_LP_A0_PSF2_PCR_CHANMAP_SC_PG0_PORT0_CHAN0_RS3_CHMAP2,
      (UINT32)~(0x0),
      BIT8
      );
    PchPcrAndThenOr32WithReadback (
      PID_PSF2,
      R_VER3_PCH_LP_A0_PSF2_PCR_CHANMAP_SC_PG0_PORT0_CHAN2_RS3_CHMAP2,
      (UINT32)~(BIT8),
      0
      );
  } else {
    PchPcrAndThenOr32WithReadback (
      PID_PSF2,
      R_VER3_PCH_LP_B0_PSF2_PCR_CHANMAP_SC_PG0_PORT0_CHAN0_RS3_CHMAP2,
      (UINT32)~(0x0),
      BIT8
      );
    PchPcrAndThenOr32WithReadback (
      PID_PSF2,
      R_VER3_PCH_LP_B0_PSF2_PCR_CHANMAP_SC_PG0_PORT0_CHAN2_RS3_CHMAP2,
      (UINT32)~(BIT8),
      0
      );
  }
}
#endif

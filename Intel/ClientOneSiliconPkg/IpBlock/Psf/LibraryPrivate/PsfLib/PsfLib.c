/** @file
  This file contains PSF routines for RC usage

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2020 Intel Corporation.

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
#include <Library/BaseMemoryLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/SataLib.h>
#include <Library/SaPlatformLib.h>
#include <Library/PsfLib.h>
#include <Library/PchPseIoLib.h>
#include <PchLimits.h>
#include <Register/PchRegsPsf.h>
#include <PchPcieRpInfo.h>
#include "PsfLibInternal.h"
#if FixedPcdGetBool(PcdBfxEnable) == 1
#include <HeciContextLib.h>
#endif

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
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    ~0u,
    B_PCH_PSFX_PCR_T0_SHDW_PCIEN_FUNDIS
    );
}

/**
  Disable bridge (e.g. PCIe Root Port) at PSF level

  @param[in] PsfPort  PSF PORT data structure
**/
VOID
PsfDisableBridge (
  IN PSF_PORT  PsfPort
  )
{
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T1_SHDW_PCIEN,
    ~0u,
    B_PCH_PSFX_PCR_T1_SHDW_PCIEN_FUNDIS
    );
}

/**
  Disable bridge (e.g. PCIe Root Port) at PSF level in RS3

  @param[in] PsfPort  PSF PORT data structure
**/
VOID
PsfRs3DisableBridge (
  IN PSF_PORT  PsfPort
  )
{
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    ~0u,
    B_PCH_PSFX_PCR_T0_SHDW_PCIEN_FUNDIS
    );
}

/**
  Check if bridge (e.g. PCIe Root Port) is enabled at PSF level

  @param[in] PsfPort  PSF PORT data structure

  @retval TRUE        Bridge behind PSF Port is enabled
          FALSE       Bridge behind PSF Port is disabled
**/
BOOLEAN
PsfIsBridgeEnabled (
  IN PSF_PORT  PsfPort
  )
{
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return FALSE;
  }

  return ((PchPcrRead32 (PsfPort.PsfPid, PsfPort.RegBase + R_PCH_PSFX_PCR_T1_SHDW_PCIEN)
           & B_PCH_PSFX_PCR_T1_SHDW_PCIEN_FUNDIS) == 0);
}

/**
  Enable device at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort  PSF PORT data structure
**/
VOID
PsfEnableDevice (
  IN PSF_PORT  PsfPort
  )
{
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    (UINT32) ~(B_PCH_PSFX_PCR_T0_SHDW_PCIEN_FUNDIS),
    0
    );
}

/**
  Hide PciCfgSpace of device at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort  PSF PORT data structure
**/
VOID
PsfHideDevice (
  IN PSF_PORT  PsfPort
  )
{
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  // If there is PCI access right after the PSF hide device, the device might
  // still be accessible since the PSF cycle is not completed yet, and causes
  // the race condition between sideband and primary cycles.
  //
  PchPcrAndThenOr32WithReadback (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_CFG_DIS,
    ~0u,
    B_PCH_PSFX_PCR_T0_SHDW_CFG_DIS_CFGDIS
    );
}

/**
  Unhide PciCfgSpace of device at PSF level
  Method not for bridges (e.g. PCIe Root Port)

  @param[in] PsfPort  PSF PORT data structure
**/
VOID
PsfUnhideDevice (
  IN PSF_PORT  PsfPort
  )
{
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
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
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // BAR0-5 supported
  //
  ASSERT (BarDisMask < BIT6);

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    ~0u,
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
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // BAR0-5 supported
  //
  ASSERT (BarEnMask < BIT6);

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
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
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
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
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    ~0u,
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
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
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
  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_PCIEN,
    ~0u,
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
  ASSERT (BarNum < 6);

  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    PsfPort.PsfPid,
    PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_BAR0 + BarNum * 0x4,
    0x0,
    BarValue
    );
}

/**
  Set Function number for PSF_PORT
  Method works both in RS0 and RS3 for devices and bridges

  @param[in] PsfPort        PSF PORT data structure
  @param[in] FunctionNumber Function Number
**/
VOID
PsfSetFunctionNumber (
  IN PSF_PORT  PsfPort,
  IN UINT32    FunctionNumber
  )
{
  ASSERT (FunctionNumber < 8);

  if (PSF_IS_PORT_NULL (PsfPort)) {
    ASSERT (FALSE);
    return;
  }

  //
  // Read back is needed to enforce the sideband and primary ordering.
  //
  PchPcrAndThenOr32WithReadback (
    PsfPort.PsfPid,
    PsfPort.RegBase,
    (UINT32)~B_PCH_PSFX_PCR_TX_AGENT_FUNCTION_CONFIG_FUNCTION,
    FunctionNumber << N_PCH_PSFX_PCR_TX_AGENT_FUNCTION_CONFIG_FUNCTION
    );
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
  Unhide TraceHub PciCfgSpace at PSF level
**/
VOID
PsfUnhideTraceHubDevice (
  VOID
  )
{
  PsfUnhideDevice (PsfTraceHubPort ());
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
  Disable TraceHub ACPI devices at PSF level
**/
VOID
PsfDisableTraceHubAcpiDevice (
  VOID
  )
{
  PsfDisableDevice (PsfTraceHubAcpiDevPort ());
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
#if FixedPcdGetBool(PcdBfxEnable) == 1
  SetHeciContextInitialized (HeciDevice, TRUE);
#endif
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
#if FixedPcdGetBool(PcdBfxEnable) == 1
  SetHeciContextInitialized (HeciDevice, FALSE);
#endif
}

/**
  Hide HECI device at PSF level

  @param[in] HeciDevice       HECIx Device (HECI1-4)
**/
VOID
PsfHideHeciDevice (
  IN UINT8      HeciDevice
  )
{
  PsfHideDevice (PsfHeciPort (HeciDevice));
#if FixedPcdGetBool(PcdBfxEnable) == 1
  SetHeciContextHidden (HeciDevice, TRUE);
#endif
}

/**
  Enable SOL device at PSF level
**/
VOID
PsfEnableSolDevice (
  VOID
  )
{
}

/**
  Disable SOL device at PSF level
**/
VOID
PsfDisableSolDevice (
  VOID
  )
{
}

/**
  Disable TSN device at PSF level
**/
VOID
PsfDisableTsnDevice (
  VOID
  )
{
  PsfDisableDevice (PsfTsnPort ());
}

/**
  Disable PSE device at PSF level
**/
VOID
PsfDisablePseDevice (
  IN UINT32  PseCtrlIndex
  )
{
  DEBUG ((DEBUG_INFO, "Disabling PSE controller device %d.\n", PseCtrlIndex));
  PsfDisableDevice (PsfPsePort (PseCtrlIndex));
}

/**
  Hide PSE DMA devices at PSF level
**/
VOID
PsfHidePseDmaDevices (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "Hiding PSE DMA0, DMA1, DMA2 devices\n"));
  PsfHidePseDevice(PchPseIoIndexDma0);
  PsfHidePseDevice(PchPseIoIndexDma1);
  PsfHidePseDevice(PchPseIoIndexDma2);
}

/**
  Hide PSE device at PSF level
**/
VOID
PsfHidePseDevice (
  IN UINT32  PseCtrlIndex
  )
{
  DEBUG ((DEBUG_INFO, "Hiding PSE controller device %d.\n", PseCtrlIndex));
  PsfHideDevice (PsfPsePort (PseCtrlIndex));
}

/**
  Disable PSE BAR1 at PSF level
**/
VOID
PsfDisablePseBar1 (
  IN UINT32  PseCtrlIndex
  )
{
  //
  // Set AGNT_T0_SHDW_PCIEN[19:18] = 11b
  // PSE device BAR is 64bit wide so to disable BAR1
  // at PSF both BAR2 (32bit wide) and BAR3 (32bit wide) need to be disabled
  //
  DEBUG ((DEBUG_INFO, "Disabling PSE device %d BAR1.\n", PseCtrlIndex));
  PsfDisableDeviceBar (PsfPsePort (PseCtrlIndex), (BIT3 | BIT2));
}

/**
  Disable ISH device at PSF level
**/
VOID
PsfDisableIshDevice (
  VOID
  )
{
}

/**
  Disable ISH BAR1 at PSF level
**/
VOID
PsfDisableIshBar1 (
  VOID
  )
{
}

/**
  Disable CNVi WiFi device at PSF level
**/
VOID
PsfDisableCnviWifiDevice (
  VOID
  )
{
  PsfDisableDevice (PsfCnviPort ());
}

/**
  Hide CNVi WiFi device PciCfgSpace at PSF level
**/
VOID
PsfHideCnviWifiDevice (
  VOID
  )
{
  PsfHideDevice (PsfCnviPort ());
}

/**
  Hide PMC device at PSF level
**/
VOID
PsfHidePmcDevice (
  VOID
  )
{
  PsfHideDevice (PsfPmcPort ());
}

/**
  Set PMC ABASE value in PSF

  @param[in] Address     Address for ACPI base address.
**/
VOID
PsfSetPmcAbase (
  IN  UINT16       Address
  )
{
  PSF_PORT PsfPort;

  PsfPort = PsfPmcPort ();

  ASSERT (PchPcrRead32 (PsfPort.PsfPid, PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_BAR4) != 0xFFFFFFFF);

  //
  // Disable IOSpace before changing the address
  //
  PsfDisableDeviceIoSpace (PsfPort);

  //
  // Program ABASE in PSF PMC space BAR4
  //
  PsfSetDeviceBarValue (PsfPort, 4, Address);

  //
  // Enable IOSpace
  //
  PsfEnableDeviceIoSpace (PsfPort);
}

/**
  Get PMC ABASE value from PSF

  @retval Address     Address for ACPI base.
**/
UINT16
PsfGetPmcAbase (
  VOID
  )
{
  UINT16    Address;
  PSF_PORT  PsfPort;

  PsfPort = PsfPmcPort ();
  //
  // Read ABASE from PSF PMC space BAR4
  //
  Address = PchPcrRead16 (
              PsfPort.PsfPid,
              PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_BAR4
              );

  ASSERT (Address != 0xFFFF);

  return Address;
}

/**
  Get PMC PWRMBASE value from PSF

  @retval Address     Address for PWRM base.
**/
UINT32
PsfGetPmcPwrmBase (
  VOID
  )
{
  UINT32    Address;
  PSF_PORT  PsfPort;

  PsfPort = PsfPmcPort ();
  //
  // Read PWRMBASE from PSF PMC space BAR0
  //
  Address = PchPcrRead32 (
              PsfPort.PsfPid,
              PsfPort.RegBase + R_PCH_PSFX_PCR_T0_SHDW_BAR0
              );

  ASSERT (Address != 0xFFFFFFFF);

  return Address;
}

/**
  Disable PCIe Root Port at PSF level

  @param[in] RpIndex        PCIe Root Port Index (0 based)
**/
VOID
PsfDisablePcieRootPort (
  IN UINT32  RpIndex
  )
{
  PSF_PORT  PsfSecondLevelPort;
  PSF_PORT  PsfRootRs3Port;

  PsfSecondLevelPort = PsfPcieSecondLevelPort (RpIndex);
  if (PsfSecondLevelPort.PsfPid != 0) {
    //
    // Disable PCIe Root Port also in second level PSF segment.
    // In such 2-level configuration this is the one to which
    // PCIe Root Port is directly connected
    //
    PsfDisableBridge (PsfSecondLevelPort);
  }
  //
  // Disable PCIe Root Ports at PSF root level
  // for RS0
  //
  PsfDisableBridge (PsfRootPciePort (RpIndex));

  //
  // Some projects don't support access to root port in root space 3.
  // In such event PSF_PORT is going to be NULL and we have to skip RS3 access disabling
  //
  PsfRootRs3Port = PsfRootRs3PciePort (RpIndex);
  if (!PSF_IS_PORT_NULL (PsfRootRs3Port)) {
    //
    // Disable PCIe Root Ports at PSF root level
    // for RS3
    //
    PsfRs3DisableBridge (PsfRootRs3Port);
  }
}

/**
  Check if PCIe Root Port is enabled

  @param[in] RpIndex        PCIe Root Port Index (0 based)

  @retval TRUE              PCIe Root Port is enabled
          FALSE             PCIe Root Port is disabled
**/
BOOLEAN
PsfIsPcieRootPortEnabled (
  IN UINT32  RpIndex
  )
{
  return PsfIsBridgeEnabled (PsfRootPciePort (RpIndex));
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
    case PsfPcieCtrl1x1: //Pcie1x1
      ChannelGrant[0] = 1;
      ChannelGrant[1] = 1;
      ChannelGrant[2] = DEFAULT_PCIE_GRANT_COUNT;
      ChannelGrant[3] = DEFAULT_PCIE_GRANT_COUNT;
      break;
    default:
      ASSERT (FALSE);
      break;
  }
}

/**
  Program PSF grant counts for PCI express PSF ports

  @param[in] PsfTopology              PSF Topology for PCIe controller for which grant counts are to be programmed
  @param[in] PsfPcieCtrlConfigTable   Table with PCIe controllers configuration
  @param[in] NumberOfPcieControllers  Number of PCIe controllers. This is also the size of PsfPcieCtrlConfig table

  @retval GrantCount  GrantCount value that was programmed for given PSF Port (PsfPort)
**/
STATIC
UINT32
PsfSetPcieControllerGrantCount (
  IN CONST PSF_TOPOLOGY    *PsfTopology,
  IN PSF_PCIE_CTRL_CONFIG  *PsfPcieCtrlConfigTable,
  IN UINT32                NumberOfPcieControllers
  )
{
  UINT8                DgcrNo;
  UINT8                PgTgtNo;
  UINT8                Channel;
  UINT32               ChannelGrant[PCH_PCIE_CONTROLLER_PORTS];
  UINT8                Controller;
  PSF_GRANT_COUNT_REG  GrantCountReg;
  UINT32               TotalGrantCount;

  Controller = (UINT8)PsfTopology->PortData.PcieCtrlIndex;

  if ((Controller >= NumberOfPcieControllers) ||
      (PsfPcieCtrlConfigTable == NULL)) {
    ASSERT (FALSE);
    return 0;
  }

  PsfPcieChannelGrantCounts (PsfPcieCtrlConfigTable[Controller], &ChannelGrant[0]);

  PsfPcieGrantCountBaseReg (Controller, &GrantCountReg);

  TotalGrantCount = 0;

  for (Channel = 0; Channel < GetControllerMaxRp (Controller); ++Channel) {
    if (ChannelGrant[Channel] == DEFAULT_PCIE_GRANT_COUNT) {
      //
      // If HW default move to next channel
      //
      continue;
    }

    PsfPcieGrantCountNumber (Controller, Channel, &DgcrNo, &PgTgtNo);

    DEBUG ((DEBUG_INFO, "SP%c[%d] - DGCR%d = %d\n", 'A' + Controller, Channel, DgcrNo, ChannelGrant[Channel]));
    PchPcrAndThenOr32 (
      GrantCountReg.PsfPid,
      (UINT16) (GrantCountReg.DevGntCnt0Base + (DgcrNo * S_PCH_PSFX_PCR_DEV_GNTCNT_RELOAD_DGCR)),
      (UINT32) ~B_PCH_PSFX_PCR_DEV_GNTCNT_RELOAD_DGCR_GNT_CNT_RELOAD,
      ChannelGrant[Channel]
      );

    DEBUG ((DEBUG_INFO, "SP%c[%d] - PG1_TGT%d = %d\n", 'A' + Controller, Channel, PgTgtNo, ChannelGrant[Channel]));
    PchPcrAndThenOr32 (
      GrantCountReg.PsfPid,
      (UINT16) (GrantCountReg.TargetGntCntPg1Tgt0Base + (PgTgtNo * S_PCH_PSFX_PCR_TARGET_GNTCNT_RELOAD)),
      (UINT32) ~B_PCH_PSFX_PCR_TARGET_GNTCNT_RELOAD_GNT_CNT_RELOAD,
      ChannelGrant[Channel]
      );

    if (PsfIsPcieRootPortEnabled (Channel + Controller * GetControllerMaxRp (Controller))) {
      TotalGrantCount += ChannelGrant[Channel];
    }
  }
  return TotalGrantCount;
}

/**
  Program PSF grant counts for PSF to PSF port

  @param[in] PsfTopology           PSF Topology for PSF-to-PSF port for which Grant Counts are to be programmed

  @param[in] GrantCount            GrantCount value that is to be programmed for given PSF Port

  @retval GrantCount  GrantCount value that was programmed for given PSF Port (PsfPort)
**/
STATIC
UINT32
PsfSetSegmentGrantCounts (
  IN CONST PSF_TOPOLOGY   *PsfTopology,
  IN UINT32               GrantCount
  )
{
  UINT32               GrantCountMax;
  UINT8                DgcrNo;
  UINT8                PgTgtNo;
  PSF_GRANT_COUNT_REG  GrantCountReg;

  ZeroMem (&GrantCountReg, sizeof (GrantCountReg));
  GrantCountMax = MIN (V_PCH_PSFX_PCR_DEV_GNTCNT_MAX, GrantCount);

  PsfSegmentGrantCountBaseReg (PsfTopology->PsfPort, &GrantCountReg);
  PsfSegmentGrantCountNumber (PsfTopology->PsfPort, &DgcrNo, &PgTgtNo);

  DEBUG ((DEBUG_INFO, "PSF%d - DGCR%d = %d\n", PsfTopology->PsfPort.PortId, DgcrNo, GrantCountMax));
  PchPcrAndThenOr32 (
    GrantCountReg.PsfPid,
    (UINT16) (GrantCountReg.DevGntCnt0Base + (DgcrNo * S_PCH_PSFX_PCR_DEV_GNTCNT_RELOAD_DGCR)),
    (UINT32) ~B_PCH_PSFX_PCR_DEV_GNTCNT_RELOAD_DGCR_GNT_CNT_RELOAD,
    GrantCountMax
    );

  DEBUG ((DEBUG_INFO, "PSF%d - PG1_TGT%d = %d\n", PsfTopology->PsfPort.PortId, PgTgtNo, GrantCountMax));
  PchPcrAndThenOr32 (
    GrantCountReg.PsfPid,
    (UINT16) (GrantCountReg.TargetGntCntPg1Tgt0Base + (PgTgtNo * S_PCH_PSFX_PCR_TARGET_GNTCNT_RELOAD)),
    (UINT32) ~B_PCH_PSFX_PCR_TARGET_GNTCNT_RELOAD_GNT_CNT_RELOAD,
    GrantCountMax
    );

  return GrantCountMax;
}

/**
  Program PSF grant counts for PCI express tree in PSF topology. This tree consists of PSF ports
  for PCIe controllers and PSF segments under which PCIe controllers reside indirectly
  through other PSF segments.

  @param[in] PsfTopology              PSF Topology for which grant counts are to be programmed
  @param[in] PsfPcieCtrlConfigTable   Table with PCIe controllers configuration
  @param[in] NumberOfPcieControllers  Number of PCIe controllers. This is also the size of PsfPcieCtrlConfig table

  @retval GrantCount  GrantCount value that was programmed for given PSF Port (PsfPort)
**/
STATIC
UINT32
PsfTopologyConfigurePcieGrantCounts (
  IN CONST PSF_TOPOLOGY    *PsfTopology,
  IN PSF_PCIE_CTRL_CONFIG  *PsfPcieCtrlConfigTable,
  IN UINT32                NumberOfPcieControllers
  )
{
  UINT32               GrantCount;
  CONST PSF_TOPOLOGY   *ChildSegment;

  if (PsfTopology == NULL) {
    ASSERT (FALSE);
    return 0;
  }

  GrantCount = 0;

  if (PsfTopology->PortType == PsfPcieCtrlPort) {
    GrantCount = PsfSetPcieControllerGrantCount (
                   PsfTopology,
                   PsfPcieCtrlConfigTable,
                   NumberOfPcieControllers
                   );
  } else if (PsfTopology->PortType == PsfToPsfPort) {

    ChildSegment = PsfTopology->Child;

    while (!PSF_IS_TOPO_PORT_NULL (ChildSegment->PsfPort)) {
      GrantCount += PsfTopologyConfigurePcieGrantCounts (
                      ChildSegment,
                      PsfPcieCtrlConfigTable,
                      NumberOfPcieControllers
                      );

      ChildSegment++;
    }

    if (!PSF_IS_TOPO_PORT_NULL (PsfTopology->PsfPort) && GrantCount > 0) {
      GrantCount = PsfSetSegmentGrantCounts (
                     PsfTopology,
                     GrantCount
                     );
    }
  }

  return GrantCount;
}

/**
  Program PSF grant counts for PCI express depending on controllers configuration

  @param[in] PsfPcieCtrlConfigTable   Table with PCIe controllers configuration
  @param[in] NumberOfPcieControllers  Number of PCIe controllers. This is also the size of PsfPcieCtrlConfig table
**/
VOID
PsfConfigurePcieGrantCounts (
  IN PSF_PCIE_CTRL_CONFIG  *PsfPcieCtrlConfigTable,
  IN UINT32                NumberOfPcieControllers
  )
{
  DEBUG ((DEBUG_INFO, "PsfConfigurePcieGrantCounts() Start\n"));

  PsfTopologyConfigurePcieGrantCounts (
    PsfGetRootPciePsfTopology (),
    PsfPcieCtrlConfigTable,
    NumberOfPcieControllers
    );

  DEBUG ((DEBUG_INFO, "PsfConfigurePcieGrantCounts() End\n"));
}

/**
  Reload default RP PSF function number.
  The PSF register doesn't got reset after system reset, which will result in mismatch between
  PSF register setting and PCIE PCR PCD register setting. Reset PSF register in early phase
  to avoid cycle decoding confusing.
**/
STATIC
VOID
PsfReloadDefaultPcieRpFunc (
  VOID
  )
{
  UINT32   PortIndex;
  UINT32   RootPortFunction;
  PSF_PORT PsfSecondLevelPort;
  PSF_PORT PsfRootRs3Port;

  //
  // Reload PSF function config registers to restore default function numbers for PCIe Root Ports
  //
  for (PortIndex = 0; PortIndex < GetPchMaxPciePortNum (); PortIndex++) {
    RootPortFunction = PortIndex % 8;

    PsfSecondLevelPort = PsfPcieFunctionConfigSecondLevelPort (PortIndex);

    if (PsfSecondLevelPort.PsfPid != 0) {
      //
      // Configure PCIe Root Port also in second level PSF segment.
      // In such 2-level configuration this is the one to which
      // PCIe Root Port is directly connected
      //
      PsfSetFunctionNumber (
        PsfSecondLevelPort,
        RootPortFunction
        );
    }

    //
    // Configure PSF (Root level) in RS0
    //
    PsfSetFunctionNumber (
      PsfRootPcieFunctionConfigPort (PortIndex),
      RootPortFunction
      );

    //
    // Some projects don't support access to root port in root space 3.
    // In such event PSF_PORT is going to be NULL and we have to skip resetting
    // RS3 root port function number to default value
    //
    PsfRootRs3Port = PsfRootRs3PciePort (PortIndex);
    if (!PSF_IS_PORT_NULL (PsfRootRs3Port)) {
      //
      // Configure PSF (Root level) in RS3
      //
      PsfSetFunctionNumber (
        PsfRootRs3PcieFunctionConfigPort (PortIndex),
        RootPortFunction
        );
    }
  }
}

/**
  Assign new function number for PCIe Port Number.

  @param[in] RpIndex        PCIe Root Port Index (0 based)
  @param[in] NewFunction    New Function number
**/
VOID
PsfSetPcieFunction (
  IN UINT32  RpIndex,
  IN UINT32  NewFunction
  )
{
  PSF_PORT PsfSecondLevelPort;
  PSF_PORT  PsfRootRs3Port;

  PsfSecondLevelPort = PsfPcieFunctionConfigSecondLevelPort (RpIndex);

  if (PsfSecondLevelPort.PsfPid != 0) {
    //
    // Configure PCIe Root Port also in second level PSF segment.
    // In such 2-level configuration this is the one to which
    // PCIe Root Port is directly connected
    //
    PsfSetFunctionNumber (
      PsfSecondLevelPort,
      NewFunction
      );
  }

  //
  // Configure PSF (Root level) in RS0
  //
  PsfSetFunctionNumber (
    PsfRootPcieFunctionConfigPort (RpIndex),
    NewFunction
    );

  //
  // Some projects don't support access to root port in root space 3.
  // In such event PSF_PORT is going to be NULL and we have to skip setting
  // new function number for RS3 root port
  //
  PsfRootRs3Port = PsfRootRs3PciePort (RpIndex);
  if (!PSF_IS_PORT_NULL (PsfRootRs3Port)) {
    //
    // Configure PSF (Root level) in RS3
    //
    PsfSetFunctionNumber (
      PsfRootRs3PcieFunctionConfigPort (RpIndex),
      NewFunction
      );
  }
}

/**
  Get PSF SideBand Port ID from PSF ID (1 - PSF1, 2 - PSF2, ...)

  @param[in] PsfId             PSF ID (1 - PSF1, 2 - PSF2, ...)

  @retval PSF SideBand Port ID
**/
PCH_SBI_PID
PsfSbPortId (
  UINT32        PsfId
  )
{
  UINT32          PsfTableIndex;
  PSF_SEGMENT     *PsfTable;
  UINT32          PsfTableSize;

  PsfSegments (&PsfTable, &PsfTableSize);

  for (PsfTableIndex = 0; PsfTableIndex < PsfTableSize; PsfTableIndex++) {
    if (PsfTable[PsfTableIndex].Id == PsfId) {
      return PsfTable[PsfTableIndex].SbPid;
    }
  }

  ASSERT (FALSE);
  return 0;
}


/**
  Get PCH Root PSF ID. This is the PSF segment to which OPDMI/DMI is connected.

  @retval PsfId             Root PSF ID
**/
UINT32
PsfRootId (
  VOID
  )
{
  PSF_SEGMENT     *PsfTable;
  UINT32          PsfTableSize;

  PsfSegments (&PsfTable, &PsfTableSize);

  return PsfTable[0].Id;
}

/**
  Add EOI Target in a given PSF

  @param[in] PsfId             PSF ID (1 - PSF1, 2 - PSF2, ...)
  @param[in] TargetId          EOI Target ID
**/
STATIC
VOID
PsfAddEoiTarget (
  UINT32           PsfId,
  PSF_PORT_DEST_ID TargetId
  )
{
  UINT16      EoiTargetBase;
  UINT16      EoiControlBase;
  UINT8       NumOfEnabledTargets;
  UINT8       MaximalNumberOfTargets;
  PCH_SBI_PID PsfSbiPortId;
  UINT32      Data32;
  UINT8       TargetIndex;

  MaximalNumberOfTargets = PsfEoiRegData (PsfId, &EoiTargetBase, &EoiControlBase);
  PsfSbiPortId = PsfSbPortId (PsfId);

  //
  // Get number of enabled agents from PSF_x_PSF_MC_CONTROL_MCAST0_RS0_EOI register
  //
  Data32 = PchPcrRead32 (PsfSbiPortId, EoiControlBase);
  NumOfEnabledTargets = (UINT8) (Data32 >> N_PCH_PSFX_PCR_MC_CONTROL_MCASTX_NUMMC);

  //
  // Check if target was not already enabled
  // Targets from a different PSF segment are aggregated into single destination on
  // current PSF segment.
  //
  for (TargetIndex = 0; TargetIndex < NumOfEnabledTargets; TargetIndex++) {
    Data32 = PchPcrRead32 (PsfSbiPortId, EoiTargetBase + TargetIndex * 4);
    //
    // If target already added don't add it again
    //
    if (Data32 == TargetId.RegVal) {
      ASSERT (FALSE);
      return;
    }
    //
    // If target is from different PSF segment than currently being analyzed
    // it is enough that its PsfID is matching
    //
    if ((Data32 & B_PCH_PSFX_PCR_TARGET_PSFID) >> N_PCH_PSFX_PCR_TARGET_PSFID == TargetId.Fields.PsfId) {
      return;
    }
  }

  //
  // Check if next one can be added
  //
  if (NumOfEnabledTargets >= MaximalNumberOfTargets) {
    ASSERT (FALSE);
    return;
  }

  //
  // Add next target
  // Configure Multicast Destination ID register with target device on PSF.
  // Configuration must be done in next available PSF_MC_AGENT_MCAST0_RS0_TGT<x>_EOI register
  // so that other targets  are not overridden. <x> is known from the number of multicast agents
  // in Multicast Control Register. Value programmed is based on
  // PsfID, PortGroupID, PortID and ChannelID of the target
  //
  PchPcrWrite32 (PsfSbiPortId, EoiTargetBase + NumOfEnabledTargets * 4, TargetId.RegVal);

  //
  // Enable new target
  // Configure PSF_x_PSF_MC_CONTROL_MCAST0_RS0_EOI, increase NumMc and set MultCEn
  //
  NumOfEnabledTargets++;
  Data32 = (NumOfEnabledTargets << N_PCH_PSFX_PCR_MC_CONTROL_MCASTX_NUMMC) | B_PCH_PSFX_PCR_MC_CONTROL_MCASTX_MULTCEN;
  PchPcrWrite32 (PsfSbiPortId, EoiControlBase, Data32);
}

/**
  Enable EOI Target

  @param[in] TargetId  Target ID
**/
STATIC
VOID
PsfEnableEoiTarget (
  PSF_PORT_DEST_ID     TargetId
  )
{
  UINT32 RootLevelPsf;

  RootLevelPsf = PsfRootId ();

  //
  // Enable EOI target in root PSF
  //
  PsfAddEoiTarget (RootLevelPsf, TargetId);

  //
  // Enable EOI target on other PSF segment if target
  // is not located on root PSF
  //
  if (TargetId.Fields.PsfId != RootLevelPsf) {
    PsfAddEoiTarget (TargetId.Fields.PsfId, TargetId);
  }
}

/**
  Program PSF EOI Multicast configuration for ITSS
**/
VOID
PsfConfigurEoiForItss (
  VOID
  )
{
  //
  // P2SB needs to be set as EOI Target
  // because interrupt controller (ITSS) is a sideband device
  // located behind P2SB
  //
  PsfEnableEoiTarget (PsfP2sbDestinationId ());
}

/**
  This function enables EOI message forwarding in PSF for PCIe ports
  for cases where IOAPIC is present behind this root port.

  @param[in] RpIndex        Root port index (0 based)

  @retval Status
**/
EFI_STATUS
PsfConfigurEoiForPciePort (
  IN  UINT32  RpIndex
  )
{
  ASSERT (RpIndex < GetPchMaxPciePortNum ());

  //
  // If there is an IOAPIC discovered behind root port program PSF Multicast registers
  // accordingly to CNL PCH BWG PSF EOI Multicast Configuration
  // Since there is a device behind RootPort to which EOI needs to be forwarded
  // enable multicast (MULTCEN) and increase the number of multicast agents (NUMMC)
  // in Multicast Control Register.
  //
  PsfEnableEoiTarget (PsfPcieDestinationId (RpIndex));

  return EFI_SUCCESS;
}

/**
  This function disables all EOI targets and restores back HW default configuration.
  Function is needed because MCAST_CONTROL_EOI and MCAST_TARGET_EOI registers do not
  get back to HW default in all types of resets
**/
STATIC
VOID
PsfResetEoiTargets (
  VOID
  )
{
  UINT16          EoiTargetBase;
  UINT16          EoiControlBase;
  UINT8           NumOfEnabledTargets;
  UINT8           TargetIndex;
  UINT32          Data32;
  UINT32          PsfTableIndex;
  PSF_SEGMENT     *PsfTable;
  UINT32          PsfTableSize;

  PsfSegments (&PsfTable, &PsfTableSize);

  for (PsfTableIndex = 0; PsfTableIndex < PsfTableSize; PsfTableIndex++) {

    if (PsfEoiRegData (PsfTable[PsfTableIndex].Id, &EoiTargetBase, &EoiControlBase)) {

      //
      // Get number of enabled agents from EOI control register on this PSF
      //
      Data32 = PchPcrRead32 (PsfTable[PsfTableIndex].SbPid, EoiControlBase);
      NumOfEnabledTargets = (UINT8) (Data32 >> N_PCH_PSFX_PCR_MC_CONTROL_MCASTX_NUMMC);

      if (NumOfEnabledTargets > 0) {
        //
        // Disable EOI targets
        //
        PchPcrWrite32 (PsfTable[PsfTableIndex].SbPid, EoiControlBase, 0);

        for (TargetIndex = 0; TargetIndex < NumOfEnabledTargets; TargetIndex++) {
          //
          // Clear EOI target configuration
          //
          PchPcrWrite32 (PsfTable[PsfTableIndex].SbPid, EoiTargetBase + TargetIndex * 4, 0);
        }
      }
    }
  }
}

/**
  Perform registers programming required for
  Management Component Transport Protocol Broadcast Cycle.

  Agent Destination Addresses are being programmed only when adequate
  PCIe root port controllers are function enabled.

  Function sets CSME PMT as a message broadcaster and programs the targets
  of the message in registers only if adequate PCIe root port controllers
  are function enabled. Conditionally, if the CPU PEG exist and is function
  enabled, DMI is also a target.
**/
VOID
PsfConfigureMctpCycle (
  VOID
  )
{
  UINT32            RpIndex;
  UINT32            RootPsfId;
  UINT32            PsfId;
  PSF_PORT_DEST_ID  TargetId;
  UINT8             NumOfEnabledTargets[PCH_MAX_PSF_SEGMENTS];
  UINT16            MctpTargetBase;
  UINT16            MctpControlBase;
  UINT8             Index;

  if (!PsfIsMctpSupported ()) {
    ASSERT (FALSE);
    return;
  }

  ZeroMem (NumOfEnabledTargets, sizeof (NumOfEnabledTargets));

  RootPsfId = PsfRootId ();

  //
  // Configure each enabled Root Port as MCTP target
  //
  for (RpIndex = 0; RpIndex < GetPchMaxPciePortNum (); RpIndex++) {
    if (PsfIsPcieRootPortEnabled (RpIndex)) {

      TargetId = PsfPcieDestinationId (RpIndex);

      PsfId = TargetId.Fields.PsfId;
      PsfMctpRegData (PsfId, &MctpTargetBase, &MctpControlBase);

      //
      // Add next target in PSF segment directly connected to this endpoint
      // Configure Multicast Destination ID register with target device on PSF.
      //
      PchPcrWrite32 (
        PsfSbPortId (PsfId),
        MctpTargetBase + NumOfEnabledTargets[PsfId - RootPsfId] * 4,
        TargetId.RegVal
        );

      NumOfEnabledTargets[PsfId - RootPsfId]++;
    }
  }

  if (IsPegPresent ()) { // if PEG graphics is enabled
    TargetId = PsfDmiDestinationId ();
    PsfId = TargetId.Fields.PsfId;
    PsfMctpRegData (PsfId, &MctpTargetBase, &MctpControlBase);
    //
    // Add PEG (behind DMI) as target.
    // Configure Multicast Destination ID register with target device on PSF.
    //
    PchPcrWrite32 (
      PsfSbPortId (PsfId),
      MctpTargetBase + NumOfEnabledTargets[PsfId - RootPsfId] * 4,
      TargetId.RegVal
      );

    NumOfEnabledTargets[PsfId - RootPsfId]++;
  }

  //
  // If targets on other segments than Root PSF have targets enabled those segments
  // need to be added as one of target in Root PSF.
  //
  for (Index = 1; Index < ARRAY_SIZE (NumOfEnabledTargets); Index++) {
    if (NumOfEnabledTargets[Index] > 0) {
      //
      // Add next target in Root PSF segment
      // Configure Multicast Destination ID register with target device on PSF.
      //
      PsfId = Index + RootPsfId;
      PsfMctpRegData (RootPsfId, &MctpTargetBase, &MctpControlBase);

      PchPcrWrite32 (
        PsfSbPortId (RootPsfId),
        MctpTargetBase + NumOfEnabledTargets[0] * 4,
        B_PCH_PSFX_PCR_TARGET_PORTGROUPID | (PsfId << N_PCH_PSFX_PCR_TARGET_PSFID)
        );

      NumOfEnabledTargets[0]++;
    }
  }

  //
  // Configure MCTP Control with a number of targets on a given PSF segment
  // and assign MCTP ownership to PMT
  //
  for (Index = 0; Index < ARRAY_SIZE (NumOfEnabledTargets); Index++) {
    if (NumOfEnabledTargets[Index] > 0) {
      PsfId = Index + RootPsfId;

      PsfMctpRegData (PsfId, &MctpTargetBase, &MctpControlBase);

      PchPcrWrite32 (
        PsfSbPortId (PsfId),
        MctpControlBase,
        (NumOfEnabledTargets[Index] << N_PCH_PSFX_PCR_MC_CONTROL_MCASTX_NUMMC) | B_PCH_PSFX_PCR_MC_CONTROL_MCASTX_MULTCEN
        );

      PchPcrWrite32 (
        PsfSbPortId (PsfId),
        R_PCH_PSFX_PCR_RC_OWNER_RS0,
        V_PCH_PSFX_PCR_RC_OWNER_PMT
        );
    }
  }
}

/**
  This function disables all MCTP targets and restores back HW default for MCTP configuration.
  Function is needed because MCAST_CONTROL_MCTP and MCAST_TARGET_MCTP registers do not
  get back to HW default in all types of resets
**/
STATIC
VOID
PsfResetMctpTargets (
  VOID
  )
{
  UINT16          MctpTargetBase;
  UINT16          MctpControlBase;
  UINT8           NumOfEnabledTargets;
  UINT8           TargetIndex;
  UINT32          Data32;
  UINT32          PsfTableIndex;
  PSF_SEGMENT     *PsfTable;
  UINT32          PsfTableSize;

  PsfSegments (&PsfTable, &PsfTableSize);

  for (PsfTableIndex = 0; PsfTableIndex < PsfTableSize; PsfTableIndex++) {

    if (PsfMctpRegData (PsfTable[PsfTableIndex].Id, &MctpTargetBase, &MctpControlBase)) {

      //
      // Get number of enabled agents from MCTP control register on this PSF
      //
      Data32 = PchPcrRead32 (PsfTable[PsfTableIndex].SbPid, MctpControlBase);
      NumOfEnabledTargets = (UINT8) (Data32 >> N_PCH_PSFX_PCR_MC_CONTROL_MCASTX_NUMMC);

      if (NumOfEnabledTargets > 0) {
        //
        // Disable MCTP targets
        //
        PchPcrWrite32 (PsfTable[PsfTableIndex].SbPid, MctpControlBase, 0);

        //
        // Clear MCTP bus ownership
        //
        PchPcrWrite32 (PsfTable[PsfTableIndex].SbPid, R_PCH_PSFX_PCR_RC_OWNER_RS0, 0);

        for (TargetIndex = 0; TargetIndex < NumOfEnabledTargets; TargetIndex++) {
          //
          // Clear MCTP target configuration
          //
          PchPcrWrite32 (PsfTable[PsfTableIndex].SbPid, MctpTargetBase + TargetIndex * 4, 0);
        }
      }
    }
  }
}

/**
  Enable VTd support in PSF.
**/
VOID
PchPsfEnableVtd (
  VOID
  )
{
  UINT32          PsfTableIndex;
  PSF_SEGMENT     *PsfTable;
  UINT32          PsfTableSize;

  PsfSegments (&PsfTable, &PsfTableSize);

  for (PsfTableIndex = 0; PsfTableIndex < PsfTableSize; PsfTableIndex++) {
    PchPcrAndThenOr32 (
      PsfTable[PsfTableIndex].SbPid,
      R_PCH_PSF_PCR_ROOTSPACE_CONFIG_RS0,
      ~0u,
      B_PCH_PSF_PCR_ROOTSPACE_CONFIG_RSX_VTDEN
      );
  }
}

/**
  Disable PSF address-based peer-to-peer decoding.
**/
VOID
PchPsfDisableP2pDecoding (
  VOID
  )
{
  UINT32          PsfTableIndex;
  PSF_SEGMENT     *PsfTable;
  UINT32          PsfTableSize;

  PsfSegments (&PsfTable, &PsfTableSize);

  for (PsfTableIndex = 0; PsfTableIndex < PsfTableSize; PsfTableIndex++) {
    PchPcrAndThenOr32 (
      PsfTable[PsfTableIndex].SbPid,
      R_PCH_PSF_PCR_ROOTSPACE_CONFIG_RS0,
      (UINT32)~B_PCH_PSF_PCR_ROOTSPACE_CONFIG_RSX_ENADDRP2P,
      0
      );

    PchPcrAndThenOr32 (
      PsfTable[PsfTableIndex].SbPid,
      R_PCH_PSF_PCR_ROOTSPACE_CONFIG_RS1,
      (UINT32)~B_PCH_PSF_PCR_ROOTSPACE_CONFIG_RSX_ENADDRP2P,
      0
      );
  }
}

/**
  PSF early initialization.
**/
VOID
PsfEarlyInit (
  VOID
  )
{
#if FixedPcdGetBool(PcdBfxEnable) == 1
  PsfRs3ChannelMapEnable ();
#endif
  PsfReloadDefaultPcieRpFunc ();
  PsfResetEoiTargets ();
  if (PsfIsMctpSupported ()) {
    PsfResetMctpTargets ();
  }
}

/** @file
  Pei/Dxe/Smm Pch TraceHub Lib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PostCodeLib.h>
#include <Library/MeFwStsLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/PsfLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PchTraceHubLib.h>
#include <TraceHubConfig.h>
#include <IndustryStandard/Pci30.h>
#include <PchReservedResources.h>
#include <Register/UsbRegs.h>
#include <Register/PchRegs.h>
#include <Register/PchPcrRegs.h>
#include <Register/TraceHubRegs.h>

/**
  Enable FW BAR MMIO. FW_BAR is not part of PCI standard BAR.
  As such, it requires a separate phantom device for BIOS to configure its MMIO as FW_BAR.
  Anything that goes to this FW_BAR address will be routed by the phantom device to TraceHub.

  Programming steps:
  1. Program FW_BAR to TraceHub PCI Offset 0x70~0x77 as 64-bit base address.
  2. Program FW_BAR to TraceHub phantom device BAR0 and BAR1 as FW_LBAR and FW_UBAR from PSF
  3. Enable MSE of TraceHub phantom device from PSF

  @param[in] AddressHi                   High 32-bits for TraceHub base address.
  @param[in] AddressLo                   Low 32-bits for TraceHub base address.
  @retval EFI_SUCCESS                   Successfully completed.
**/
EFI_STATUS
TraceHubBaseSet (
  UINT32                                AddressHi,
  UINT32                                AddressLo
  )
{
  UINT64                                TraceHubBase;

  //
  // check address valid
  //
  if ((AddressLo & 0x0003FFFF) != 0) {
    DEBUG ((DEBUG_ERROR, "TraceHubBaseSet Error. Invalid Address: %x%x", AddressHi, AddressLo));
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }

  TraceHubBase = PCI_SEGMENT_LIB_ADDRESS (
                   DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_TRACE_HUB,
                   PCI_FUNCTION_NUMBER_PCH_TRACE_HUB,
                   0
                   );
  if (PciSegmentRead16 (TraceHubBase) == 0xFFFF) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }
  //
  // Program TraceHub PCI Offset 0x70~0x77 to base address.
  //
  PciSegmentWrite32 (TraceHubBase + R_TRACE_HUB_CFG_FW_LBAR, AddressLo);
  PciSegmentWrite32 (TraceHubBase + R_TRACE_HUB_CFG_FW_UBAR, AddressHi);
  //
  // Program FW_BAR to TraceHub phantom device BAR0 and BAR1 as FW_LBAR and FW_UBAR from PSF
  //
  PsfSetTraceHubAcpiDeviceBarValue (0, AddressLo);
  PsfSetTraceHubAcpiDeviceBarValue (1, AddressHi);
  //
  // Enable MSE of TraceHub phantom device from PSF
  //
  PsfEnableTraceHubAcpiDeviceMemorySpace ();
  //
  // Hide TraceHub phantom Device
  //
  PsfHideTraceHubAcpiDevice ();

  return EFI_SUCCESS;
}

/**
  Used to program xHCI DCI MMIO registers via SBI.

  @param[in] Offset          DbC offset
  @param[in] Data            Data

**/
STATIC
VOID
SbiDbcSet (
  UINT16                     Offset,
  UINT32                     Data
  )
{
  UINT8                      Response;

  PchSbiExecutionEx (
    PID_XHCI,
    Offset,
    MemoryWrite,
    FALSE,
    0xf,
    0x5,
    (PCI_DEVICE_NUMBER_PCH_XHCI << 3) + PCI_FUNCTION_NUMBER_PCH_XHCI,
    &Data,
    &Response
    );
  DEBUG ((DEBUG_INFO, "[0x%x] = 0x%08x\n", Offset, Data));

  if (Response != SBI_SUCCESSFUL) {
    DEBUG ((DEBUG_INFO, "Write [0x%x] Failed!" , Offset));
  }
}

/**
  Read MTB_BAR MMIO offset with SBI, used when MSE is not enabled yet

  @param[in] Offset          offset
  @param[in] Data            Data

**/
STATIC
VOID
SbiMtbRead (
  UINT32                     Offset,
  UINT32                     *Data
  )
{
  UINT8                      Response;

  PchSbiExecutionEx (
    PID_NPK,
    Offset,
    MemoryRead,
    FALSE,
    0x0F,
    0,
    (PCI_DEVICE_NUMBER_PCH_TRACE_HUB << 3) + PCI_FUNCTION_NUMBER_PCH_TRACE_HUB,
    Data,
    &Response
    );
  if (Response != SBI_SUCCESSFUL) {
    DEBUG ((DEBUG_INFO, "Read MTB BAR offset 0x%x Failed!" , Offset));
  }
}

/**
  Write MTB_BAR MMIO offset with SBI, used when MSE is not enabled yet

  @param[in] Offset          offset
  @param[in] Data            Data

**/
STATIC
VOID
SbiMtbWrite (
  UINT32                     Offset,
  UINT32                     Data
  )
{
  UINT8                      Response;

  PchSbiExecutionEx (
    PID_NPK,
    Offset,
    MemoryWrite,
    FALSE,
    0x0F,
    0,
    (PCI_DEVICE_NUMBER_PCH_TRACE_HUB << 3) + PCI_FUNCTION_NUMBER_PCH_TRACE_HUB,
    &Data,
    &Response
    );
  if (Response != SBI_SUCCESSFUL) {
    DEBUG ((DEBUG_INFO, "Write MTB BAR offset 0x%x Failed!" , Offset));
  }
}

/**
  For xHCI.DbC.Trace does not survive across Sx, that FW agent is responsible to resume tracing back or DbC3 would be suspended.
**/
STATIC
VOID
ConfigureXhciDbcTrace (
  VOID
  )
{
  UINT64                TraceHubBaseAddress;
  UINT32                MtbLBar;
  UINT32                MtbUBar;
  UINT32                Data;

  TraceHubBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                          DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_TRACE_HUB,
                          PCI_FUNCTION_NUMBER_PCH_TRACE_HUB,
                          0
                          );
  MtbLBar = PciSegmentRead32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_LBAR) & B_TRACE_HUB_CFG_CSR_MTB_RBAL;
  MtbUBar = PciSegmentRead32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_UBAR) & B_TRACE_HUB_CFG_CSR_MTB_RBAL;
  //
  // Set DbC Trace in Payload and Status Base
  //
  SbiDbcSet (R_XHCI_PCR_DCI_DBC_TRACE_IN_PAYLOAD_BP_LOW, MtbLBar + R_TRACE_HUB_MEM_MTB_80000);
  SbiDbcSet (R_XHCI_PCR_DCI_DBC_TRACE_IN_PAYLOAD_BP_HIGH, MtbUBar);

  SbiDbcSet (R_XHCI_PCR_DCI_DBC_TRACE_IN_STATUS_BP_LOW, MtbLBar + R_TRACE_HUB_MEM_MTB_DBCSTSCMD);
  SbiDbcSet (R_XHCI_PCR_DCI_DBC_TRACE_IN_STATUS_BP_HIGH, MtbUBar);

  //
  // Set Trace Hub DbC base and offset
  Data = V_PCH_TRACE_HUB_MEM_MTB_DBC_BASE_LO;
  SbiMtbWrite (R_TRACE_HUB_MEM_MTB_DBC_BASE_LO, Data);

  SbiMtbRead (R_TRACE_HUB_MEM_MTB_STREAMCFG2, &Data);
  Data |= (V_TRACE_HUB_MEM_MTB_STREAMCFG2_DBC_OFFSET << N_TRACE_HUB_MEM_MTB_STREAMCFG2_DBC_OFFSET);
  SbiMtbWrite (R_TRACE_HUB_MEM_MTB_STREAMCFG2, Data);
  //
  // Reserve DbC MMIO for Trace Hub - this is done in InstallEfiMemory() in MRC
  //
}

/**
  This function performs basic initialization for TraceHub, and return if trace hub needs to be power gated.

  This routine will consume address range 0xFE100000 - 0xFE400000 and 0xFC800000 - FD000000 for BARs usage.
  Although controller allows access to a 64bit address resource, PEI phase is a 32-bit environment,
  addresses greater than 4G is not allowed by CPU address space.
  So, the addresses must be limited to below 4G and UBARs should be set to 0.
  If scratchpad0 bit24 is set, which indicates trace hub is used by tool that implies probe is connected and capturing traces.
  With such assumption, BIOS may not power gate trace hub but initialize trace hub as host debugger mode despite what trace hub policy it is.

  @param[in] EnableMode              Trace Hub Enable Mode from policy

  @retval TRUE                       Need to power gate trace hub
  @retval FALSE                      No need to power gate trace hub
**/
BOOLEAN
TraceHubInitialize (
  IN UINT8                           EnableMode
  )
{
  UINT64                  TraceHubBaseAddress;
  UINT32                  Data32;
  UINT32                  MtbUBar;
  UINT32                  MtbLBar;
  UINT32                  SwUBar;
  UINT32                  SwLBar;
  UINT32                  FwUBar;
  UINT32                  FwLBar;
  UINT32                  Scrpd0;

  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Start\n"));
  Data32 = 0;
  Scrpd0 = 0;
  MtbUBar = 0;
  MtbLBar = PCH_TRACE_HUB_MTB_BASE_ADDRESS;
  SwUBar = 0;
  SwLBar = PCH_TRACE_HUB_SW_BASE_ADDRESS;
  FwUBar = 0;
  FwLBar = PCH_TRACE_HUB_FW_BASE_ADDRESS;
  //
  // Check if Trace Hub Device is present
  //
  TraceHubBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                          DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_TRACE_HUB,
                          PCI_FUNCTION_NUMBER_PCH_TRACE_HUB,
                          0
                          );
  if (PciSegmentRead16 (TraceHubBaseAddress) == 0xFFFF) {
    if (EnableMode == TraceHubModeDisabled) {
      DEBUG ((DEBUG_INFO, "TraceHubInitialize() - End. TraceHub device is not present due to TH mode is disabled\n"));
      return FALSE;
    }
    //
    // We are here assuming TH is in PG state, but user opt-in TH enabled, so we un-gate trace hub via PMC IPC1 command.
    // Noted: Trace hub PG state preserves until G3 / global reset.
    // No need to check tool ownership via SCRPD0[24], for it can only be set when TH is active (un-gated).
    //
    DEBUG ((DEBUG_INFO, "TraceHubInitialize - un-gate trace hub due to user opt-in PCH trace hub mode from disabled to enabled.\n"));
    PmcEnableTraceHub ();
  }

  if (IsCpuDebugDisabled ()) {
    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - End. DCD bit is set, disable ITH\n"));
    return TRUE;
  }

  ///
  /// Read SCRPD0[24] via SBI for MTB BAR and MSE are not set yet.
  ///
  /// MSE needs to be set until all BARs have been configured otherwise PSF decoding for uninitialized PCI BARs may result in failures
  ///
  SbiMtbRead (R_TRACE_HUB_MEM_CSR_MTB_SCRPD0, &Scrpd0);
  DEBUG ((DEBUG_INFO, "SCRPD0 = 0x%08x\n", Scrpd0));
  ///
  /// Check if STT is disconnected and if user requested disabling of Trace Hub
  ///
  if ((((Scrpd0 & B_TRACE_HUB_MEM_CSR_MTB_SCRPD0_DEBUGGER_IN_USE) == 0) && (EnableMode == TraceHubModeDisabled)) ||
      (Scrpd0 == 0xffffffff)) {
    if (Scrpd0 == 0xffffffff) {
      DEBUG ((DEBUG_INFO, "Pch TraceHub MTB BAR MMIO inaccessible, disable it\n"));
    }
    ///
    /// Clear MSE
    ///
    PciSegmentWrite8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, 0);
    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - End. STT disconnected and Trace Hub requested to be disable\n"));
    return TRUE;
  }
  ///
  /// Clear LPMEN bit in R_TRACE_HUB_CFG_CSR_MTB_LPP_CTL register
  ///
  SbiMtbRead (R_TRACE_HUB_MEM_CSR_MTB_LPP_CTL, &Data32);
  DEBUG ((DEBUG_INFO, "LPP_CTL old = 0x%08x\n", Data32));
  Data32 &= ~B_TRACE_HUB_MEM_CSR_MTB_LPP_CTL_LPMEN;
  SbiMtbWrite (R_TRACE_HUB_MEM_CSR_MTB_LPP_CTL, Data32);
  DEBUG ((DEBUG_INFO, "LPP_CTL new = 0x%08x\n", Data32));

  ///
  /// Program inbound bus timer timeout value for error handling
  ///
  PciSegmentWrite32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_ISTOT, 0xF4240);
  PciSegmentWrite32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_ICTOT, 0xF4240);

  ///
  /// Enable TraceHub debug for Sx
  ///
  PmcEnableTraceHubDebugForSx ();

  ///
  /// Program the MTB Base Address Register
  ///
  // Set MTB_LBAR (PCI offset 0x10)
  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Setting MTB_BAR\n"));
  PciSegmentWrite32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_LBAR, MtbLBar);
  //
  // Set MTB_UBAR (PCI offset 0x14)
  //
  PciSegmentWrite32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_UBAR, MtbUBar);
  ///
  /// Setup xHCI DbC for Trace Hub tracing, it needs to be ready before setting MSE
  ///
  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Setup USB3 DbC Tracing\n"));
  ConfigureXhciDbcTrace ();
  ///
  /// Program the SW Base Address Register with fixed BAR
  ///
  //
  // SW_LBAR (PCI offset 0x18)
  //
  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Setting SW_BAR\n"));
  PciSegmentWrite32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_SW_LBAR, SwLBar);
  //
  // SW_UBAR (PCI offset 0x1C)
  //
  PciSegmentWrite32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_SW_UBAR, SwUBar);

  ///
  /// Program the FW BAR and Shadow PCI Device
  ///
  DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Setting FW_BAR\n"));
  TraceHubBaseSet (FwUBar, FwLBar);
  CpuWriteTraceHubAcpiBase ((UINT64) (LShiftU64 ((UINT64)FwUBar, 32) + FwLBar));

  ///
  /// Enable MSE and BME
  ///
  if ((Scrpd0 & B_TRACE_HUB_MEM_CSR_MTB_SCRPD0_DEBUGGER_IN_USE) && (Scrpd0 & B_TRACE_HUB_MEM_CSR_MTB_SCRPD0_MEM_IS_PRIM_DEST)) {
    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Trace to memory is activated by tool, postpone setting MSE and BME until memory is ready\n"));
  } else {
    DEBUG ((DEBUG_INFO, "TraceHubInitialize() - Enabling MSE and BME\n"));
    PciSegmentOr8 (TraceHubBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER);
  }

  DEBUG ((DEBUG_INFO, "TraceHubInitialize () Assigned BARs:\n"));
  DEBUG ((DEBUG_INFO, "TraceHubInitialize () FW_LBAR  = 0x%08x\n", PciSegmentRead32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_FW_LBAR) & B_TRACE_HUB_CFG_FW_RBAL));
  DEBUG ((DEBUG_INFO, "TraceHubInitialize () MTB_LBAR = 0x%08x\n", PciSegmentRead32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_LBAR) & B_TRACE_HUB_CFG_CSR_MTB_RBAL));
  DEBUG ((DEBUG_INFO, "TraceHubInitialize () SW_LBAR  = 0x%08x\n", PciSegmentRead32 (TraceHubBaseAddress + R_TRACE_HUB_CFG_SW_LBAR) & B_TRACE_HUB_CFG_SW_RBAL));

  ///
  /// Lock power gate control register
  ///
  DEBUG ((DEBUG_INFO, "TraceHubInitialize() Locking HSWPGCR1\n"));
  PmcLockHostSwPgCtrl ();

  DEBUG ((DEBUG_INFO, "TraceHubInitialize () - End\n"));
  return FALSE;
}

/**
  Disable and power gate Pch trace hub

  @retval     EFI_SUCCESS       The function completed successfully.
  @retval     EFI_UNSUPPORTED   The device is not supported
**/
EFI_STATUS
PchTraceHubDisable (
  VOID
  )
{
  UINT64                  TraceHubBaseAddress;
  ///
  /// Check if Trace Hub Device is present
  ///
  TraceHubBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                          DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                          DEFAULT_PCI_BUS_NUMBER_PCH,
                          PCI_DEVICE_NUMBER_PCH_TRACE_HUB,
                          PCI_FUNCTION_NUMBER_PCH_TRACE_HUB,
                          0
                          );
  if (PciSegmentRead16 (TraceHubBaseAddress) == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "PchTraceHubDisable() TraceHub device is not present\n"));
    return EFI_UNSUPPORTED;
  }
  ///
  /// Disable trace hub phantom device via PSF
  ///
  PsfDisableTraceHubAcpiDevice ();
  ///
  /// Disable trace hub via PSF
  ///
  DEBUG ((DEBUG_INFO, "PchTraceHubDisable() disable Trace Hub device via PSF\n"));
  PsfDisableTraceHubDevice ();
  ///
  /// Disable Trace Hub
  ///
  PostCode (0xB50);
  DEBUG ((DEBUG_INFO, "PchTraceHubDisable() Power gate Trace Hub device via PMC\n"));
  PmcDisableTraceHub ();
  ///
  /// Lock power gate control register
  ///
  DEBUG ((DEBUG_INFO, "PchTraceHubDisable() Locking HSWPGCR1\n"));
  PmcLockHostSwPgCtrl ();

  return EFI_SUCCESS;
}

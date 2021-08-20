/** @file
  This code provides an instance of CPU TraceHub Lib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/PeiCpuTraceHubLib.h>
#include <Library/MeFwStsLib.h>
#include <Library/CpuRegbarAccessLib.h>
#include <Register/TraceHubRegs.h>
#include <TraceHubDataHob.h>
#include <Library/BaseMemoryLib.h>
#include <CpuSbInfo.h>
#include <Register/CpuPsfRegs.h>

/*
  Hide CPU Trace Hub device via PSF
*/
VOID
HideCpuTraceHub (
  VOID
)
{
  CpuRegbarAndThenOr32 (
    CPU_SB_PID_PSF1,
    R_SA_PSF1_T0_SHDW_TRACE_HUB_D9F0_ACPI_REG_BASE + R_SA_PSF1_T0_SHDW_CFG_DIS,
    0xFFFFFFFF,
    B_SA_PSF1_T0_SHDW_CFG_DIS_CFGDIS
    );
}

/**
  Installs TraceHub Data Hob

  @retval EFI_SUCCESS           The HOB was successfully created.
  @retval EFI_OUT_OF_RESOURCES  There is no additional space for HOB creation.
**/
EFI_STATUS
InstallCpuTraceHubDataHob (
  VOID
  )
{
  EFI_STATUS                  Status;
  TRACEHUB_DATA_HOB           *TraceHubDataHob;

  ///
  /// Create HOB for TraceHub Data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (TRACEHUB_DATA_HOB),
             (VOID **) &TraceHubDataHob
             );
  ASSERT_EFI_ERROR (Status);
  ///
  /// Initialize default HOB data
  ///
  TraceHubDataHob->EfiHobGuidType.Name = gTraceHubDataHobGuid;
  DEBUG ((DEBUG_INFO, "TraceHubDataHob->EfiHobGuidType.Name: %g\n", &TraceHubDataHob->EfiHobGuidType.Name));
  ZeroMem (&(TraceHubDataHob->CpuTraceHubMode), sizeof (TRACEHUB_DATA_HOB) - sizeof (EFI_HOB_GUID_TYPE));

  DEBUG ((DEBUG_INFO, "TraceHubDataHob @ %X\n", TraceHubDataHob));
  DEBUG ((DEBUG_INFO, "TraceHubDataHobSize - HobHeader: %X\n", sizeof (TRACEHUB_DATA_HOB) - sizeof (EFI_HOB_GUID_TYPE)));
  DEBUG ((DEBUG_INFO, "TraceHubDataHobSize: %X\n", sizeof (TRACEHUB_DATA_HOB)));

  return Status;
}

/*
  Set Trace Hub DbC base and offset
*/
STATIC
VOID
SetTraceHubDbcBase (
  VOID
  )
{
  MmioWrite32 (PcdGet32 (PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_MTB_DBC_BASE_LO, V_CPU_TRACE_HUB_MEM_MTB_DBC_BASE_LO);
  MmioOr32 (PcdGet32 (PcdCpuTraceHubMtbBarBase) + V_TRACE_HUB_MEM_MTB_STREAMCFG2_DBC_OFFSET, V_TRACE_HUB_MEM_MTB_STREAMCFG2_DBC_OFFSET << N_TRACE_HUB_MEM_MTB_STREAMCFG2_DBC_OFFSET);
  //
  // DbC MMIO reservation is done in SaInitPreMem.c for doing here is too late (post mem) to be valid
  // For Resource HOB to be valid for FspApiMode, must be created before PostFspmHobProcess ()
  //
}


/**
  Configure CPU Trace Hub

  @param[in] EnableMode              Trace Hub Enable Mode from policy

  @retval EFI_SUCCESS.
  @retval EFI_OUT_OF_RESOURCES.
**/
EFI_STATUS
ConfigureCpuTraceHub (
  IN UINT8     EnableMode
  )
{
  EFI_STATUS   Status;
  UINT16       DeviceId;
  UINT64       CpuTraceHubBaseAddress;
  UINT32       ScratchpadReg;
  UINT32       LowPowerModeEnable;
  BOOLEAN      RtitExist;

  DEBUG ((DEBUG_INFO, "ConfigureCpuTraceHub () - Start\n"));

  Status = InstallCpuTraceHubDataHob();
  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "Fail to install Cpu TraceHub Data Hob\n"));
  }
  CpuTraceHubBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PCI_BUS_NUMBER_CPU_TRACE_HUB, PCI_DEVICE_NUMBER_CPU_TRACE_HUB, PCI_FUNCTION_NUMBER_CPU_TRACE_HUB, 0);

  //
  // If debugger mode is disabled, write CPU Trace Hub DEVEN to 0.
  //
  if (IsCpuDebugDisabled ()) {
    DEBUG ((DEBUG_INFO, "DCD bit is set, disable CPU Trace Hub\n"));
    PciSegmentAnd32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), (UINT32) ~(B_SA_DEVEN_ITH_MASK));
    PciSegmentWrite8 (CpuTraceHubBaseAddress + PCI_COMMAND_OFFSET, 0);
    return EFI_SUCCESS;
  }
  //
  // Step 1 : Read Device ID from (0, 9, 0) to make sure CPU Intel Trace Hub exists.
  //
  DeviceId = PciSegmentRead16 (CpuTraceHubBaseAddress + PCI_DEVICE_ID_OFFSET);
  if (DeviceId == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "CPU Intel Trace Hub does not exist in the system\n."));
    return EFI_SUCCESS;
  }

  //
  // Step 2 : Enable the device in DEVEN[12] to keep CPU Intel Trace Hub enabled.
  //
  PciSegmentOr32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), (UINT32)(B_SA_DEVEN_ITH_MASK));
  DEBUG ((DEBUG_INFO, "Program MTB/SW/RTIT BAR\n"));

  //
  // Check if RTIT exist
  //
  RtitExist = TRUE;
  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_RTIT_LBAR, 0xFFFFFFFF);
  if (PciSegmentRead32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_RTIT_LBAR) == 0) {
    RtitExist = FALSE;
  }

  //
  // Step3: Program the MTB/SW/RTIT Base Address Register fixed BAR and enable MSE
  //
  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_LBAR, (UINT32) PcdGet32 (PcdCpuTraceHubMtbBarBase));
  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_UBAR, 0);

  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_SW_LBAR, (UINT32) PcdGet32 (PcdCpuTraceHubSwBarBase));
  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_SW_UBAR, 0);

  if (RtitExist == TRUE) {
    PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_RTIT_LBAR, (UINT32) PcdGet32 (PcdCpuTraceHubRtitBarBase));
    PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_RTIT_UBAR, 0);
  }

  DEBUG ((DEBUG_INFO, "Enable MSE\n"));
  PciSegmentOr8 (CpuTraceHubBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);

  //
  // Clear LPP_CTL.LPMEN bit before initializing Trace Hub
  //
  DEBUG ((DEBUG_INFO, "Clearing LPP_CTL_LPME\n"));
  MmioAnd32 (PcdGet32 (PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_CSR_MTB_LPP_CTL, (UINT32) ~(B_TRACE_HUB_MEM_CSR_MTB_LPP_CTL_LPMEN));

  //
  // Step 4 : Check if LPMEN bit in LPP_CTL is set, or SCRPD0[24] is 0 and BIOS Setup disable the CPU Trace Hub, BIOS should stop.
  //
  LowPowerModeEnable = MmioRead32 (PcdGet32 (PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_CSR_MTB_LPP_CTL);
  ScratchpadReg = MmioRead32 (PcdGet32 (PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_CSR_MTB_SCRPD0);
  DEBUG((DEBUG_INFO, "LPP_CTL = %x, SCRPD0 = %x EnableMode %x \n", LowPowerModeEnable, ScratchpadReg, EnableMode));
  if (((LowPowerModeEnable & B_TRACE_HUB_MEM_CSR_MTB_LPP_CTL_LPMEN) == B_TRACE_HUB_MEM_CSR_MTB_LPP_CTL_LPMEN)
       || (((ScratchpadReg & B_TRACE_HUB_MEM_CSR_MTB_SCRPD0_DEBUGGER_IN_USE) == 0) && (EnableMode == TraceHubModeDisabled)))
  {
    //
    // Clear MSE
    //
    PciSegmentWrite8 (CpuTraceHubBaseAddress + PCI_COMMAND_OFFSET, 0);
    //
    // Clear MTB/SW/RTIT BAR
    //
    PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_LBAR, 0);
    PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_SW_LBAR, 0);
    PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_RTIT_LBAR, 0);

    DEBUG ((DEBUG_INFO, "CPU Intel Trace Hub is in Low Power Mode or not connected and is disabled by SETUP menu . Stop the initialization.\n"));
    PciSegmentAnd32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), (UINT32) ~(B_SA_DEVEN_ITH_MASK));
    return EFI_SUCCESS;
  }

  //
  // Program RTIT BAR to WC if RTIT exist
  //
  if (RtitExist == TRUE) {
    Status = MtrrSetMemoryAttribute ((EFI_PHYSICAL_ADDRESS) PcdGet32 (PcdCpuTraceHubRtitBarBase) , PcdGet32 (PcdCpuTraceHubRtitBarSize) , CacheWriteCombining);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "Setting RTIT_BAR USWC failed!\n"));
      ASSERT_EFI_ERROR (Status);
      return Status;
    }
  }

  //
  // Set Trace Hub DbC base and offset
  //
  SetTraceHubDbcBase ();

  //
  // Step 5. Program the FW BAR and Shadow PCI Device
  // (PCI offset 0x70+0x74)
  //
  // At this point, a shadow PCI device (0/9/1) within the backbone PSF needs to be programmed
  // with the value of FW BAR, have its memory space enabled, and then hide the shadow device
  //
  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_FW_LBAR, (UINT32) PcdGet32 (PcdCpuTraceHubFwBarBase));
  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_FW_UBAR, 0);
  Status = MtrrSetMemoryAttribute ((EFI_PHYSICAL_ADDRESS) PcdGet32 (PcdCpuTraceHubFwBarBase) , PcdGet32 (PcdCpuTraceHubFwBarSize) , CacheUncacheable);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Setting FW_BAR UNCACHEABLE failed!\n"));
    ASSERT_EFI_ERROR (Status);
    return Status;
  }

  CpuRegbarWrite32 (CPU_SB_PID_PSF1, R_SA_PSF1_T0_SHDW_TRACE_HUB_D9F1_ACPI_REG_BASE + R_SA_PSF1_T0_SHDW_BAR0, PcdGet32 (PcdCpuTraceHubFwBarBase));
  CpuRegbarWrite32 (CPU_SB_PID_PSF1, R_SA_PSF1_T0_SHDW_TRACE_HUB_D9F1_ACPI_REG_BASE + R_SA_PSF1_T0_SHDW_BAR1, 0);
  CpuRegbarAndThenOr32 (CPU_SB_PID_PSF1, R_SA_PSF1_T0_SHDW_TRACE_HUB_D9F1_ACPI_REG_BASE + R_SA_PSF1_T0_SHDW_PCIEN, 0xFFFFFFFF, B_SA_PSF1_T0_SHDW_PCIEN_MEMEN);
  CpuRegbarAndThenOr32 (CPU_SB_PID_PSF1, R_SA_PSF1_T0_SHDW_TRACE_HUB_D9F1_ACPI_REG_BASE + R_SA_PSF1_T0_SHDW_CFG_DIS, 0xFFFFFFFF, B_SA_PSF1_T0_SHDW_CFG_DIS_CFGDIS);

  CpuWriteTraceHubAcpiBase (PcdGet32 (PcdCpuTraceHubFwBarBase));

  DEBUG ((DEBUG_INFO, "CPU TraceHub BARs:\n"));
  DEBUG ((DEBUG_INFO, "FW_LBAR   = 0x%08x\n", PciSegmentRead32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_FW_LBAR) & B_TRACE_HUB_CFG_FW_RBAL));
  DEBUG ((DEBUG_INFO, "MTB_LBAR  = 0x%08x\n", PciSegmentRead32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_LBAR) & B_TRACE_HUB_CFG_CSR_MTB_RBAL));
  DEBUG ((DEBUG_INFO, "RTIT_LBAR = 0x%08x\n", PciSegmentRead32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_RTIT_LBAR) & B_TRACE_HUB_CFG_RTIT_RBAL));
  DEBUG ((DEBUG_INFO, "SW_LBAR   = 0x%08x\n", PciSegmentRead32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_SW_LBAR) & B_TRACE_HUB_CFG_SW_RBAL));

  //
  // Enable BME
  //
  DEBUG ((DEBUG_INFO, "Enabling BME\n"));
  PciSegmentOr8 (CpuTraceHubBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_BUS_MASTER);

  //
  // BIOS is required to set SDC.CE (CHAP Enable) bit for Punit to perform save/restore without checking the bit.
  //
  MmioOr32 (PcdGet32 (PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_MTB_SDC, B_TRACE_HUB_MEM_MTB_SDC_CE_MASK);


  MmioAnd32(PcdGet32(PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_MTB_PMTCS, (UINT32)(~B_TRACE_HUB_MEM_MTB_PMTCS_WSYNC));
  DEBUG((DEBUG_INFO, "R_TRACE_HUB_MEM_MTB_PMTCS = 0x%08x\n", *((UINT32 *)(PcdGet32(PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_MTB_PMTCS))));
  //
  // BIOS is required to set PMCTS.BLKDRNEN (Block and Drain Enable) bit to enable Automatic Block and Drain/Unblock feature in ICL CPU.
  //
  MmioOr32 (PcdGet32 (PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_MTB_PMTCS, B_TRACE_HUB_MEM_MTB_PMTCS_BLKDRNEN);

  DEBUG ((DEBUG_INFO, "ConfigureCpuTraceHub () - End\n"));

  return EFI_SUCCESS;
}

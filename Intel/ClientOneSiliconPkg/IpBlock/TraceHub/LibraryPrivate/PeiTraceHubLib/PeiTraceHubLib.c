/** @file
  This code provides functions for Trace Hub.

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
#include <Base.h>
#include <Library/PciSegmentLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/SiPolicyLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/MtrrLib.h>
#include <Library/MemoryAllocationLib.h>
#include <PchResetPlatformSpecific.h>
#include <Library/PeiCpuTraceHubLib.h>
#include <Library/PeiTraceHubLib.h>
#include <Library/PsfLib.h>
#include <Register/TraceHubRegs.h>
#include <Library/MeFwStsLib.h>
#include <Library/PeiItssLib.h>
#include <Library/SiScheduleResetLib.h>

typedef struct {
  UINT8 DevNum;
  UINT8 FuncNum;
} TRACE_HUB_DEVICE_INFO;

TRACE_HUB_DEVICE_INFO TraceHubDeviceTable[2] = {
  {PCI_DEVICE_NUMBER_CPU_TRACE_HUB, PCI_FUNCTION_NUMBER_CPU_TRACE_HUB},
  {PCI_DEVICE_NUMBER_PCH_TRACE_HUB, PCI_FUNCTION_NUMBER_PCH_TRACE_HUB}
};

UINT32 TraceHubBufferSizeTab[8] = {0, SIZE_1MB, SIZE_8MB, SIZE_64MB, SIZE_128MB, SIZE_256MB, SIZE_512MB, SIZE_1GB};

/**
  Configure PCH tracehub interrup
**/
VOID
ConfigurePchTraceHubInterrupt (
  VOID
  )
{
  SI_POLICY_PPI           *SiPolicy;
  EFI_STATUS              Status;
  UINT8                   InterruptPin;
  UINT64                  TraceHubBaseAddress;

  SiPolicy = NULL;
  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicy);
  ASSERT_EFI_ERROR(Status);

  TraceHubBaseAddress = GetTraceHubPciBase (PchTraceHub);
  if (PciSegmentRead32 (TraceHubBaseAddress) == 0xffffffff) {
    return;
  }

  InterruptPin = ItssGetDevIntPin (SiPolicy, PCI_DEVICE_NUMBER_PCH_TRACE_HUB, PCI_FUNCTION_NUMBER_PCH_TRACE_HUB);
  PciSegmentWrite8 (TraceHubBaseAddress + PCI_INT_PIN_OFFSET, InterruptPin);
}


/**
  Do a Global Reset for TraceHub
**/
VOID
TraceHubGlobalReset (
  VOID
  )
{
  PCH_RESET_DATA             ResetData;

  CopyMem (&ResetData.Guid, &gPchGlobalResetGuid, sizeof (EFI_GUID));
  StrCpyS (ResetData.Description, PCH_RESET_DATA_STRING_MAX_LENGTH, PCH_PLATFORM_SPECIFIC_RESET_STRING);
  SiScheduleResetSetType (EfiResetPlatformSpecific, &ResetData);
}

/**
  Do Secure Boot Configuration for CPU Trace Hub

  @param[in]  CpuTraceHubConfig    ConfigBlock of CPU TraceHub
**/
VOID
SecureBootConfigurationForCpuTraceHub (
  IN TRACE_HUB_CONFIG             *CpuTraceHubConfig
  )
{
  UINT32                            MsuSpareReg;
  UINT32                            OrgMscBar[2];
  UINT32                            OrgMscSize[2];
  UINT32                            MtbBar;

  DEBUG ((DEBUG_INFO, "SecureBootConfigurationForCpuTraceHub Entry\n"));

  MsuSpareReg = 0;
  ZeroMem (&OrgMscBar, sizeof (OrgMscBar));
  ZeroMem (&OrgMscSize, sizeof (OrgMscSize));
  MtbBar = GetTraceHubMtbBar (CpuTraceHub);
  if (CpuTraceHubConfig->EnableMode != TraceHubModeDisabled) {
    if (IsCpuDebugDisabled ()) {
      DEBUG ((DEBUG_INFO, "DCD Bit is set, Perform Secure Boot Configuration for CpuTraceHub\n"));
      if (CpuTraceHubConfig->MemReg0Size == 0) {
        MmioWrite32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC0BAR, 0);
        MmioWrite32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC0SIZE, 0);
      }
      OrgMscBar[0] = MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC0BAR);
      OrgMscSize[0] = MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC0SIZE);
      MmioWrite32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC1BAR, 0);
      MmioWrite32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC1SIZE, 0);
      OrgMscBar[1] = MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC1BAR);
      OrgMscSize[1] = MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC1SIZE);

      MmioWrite32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC0CTL, MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC0CTL) & ~(B_TRACE_HUB_MEM_MTB_MSCCTL_MSCEN));
      MmioWrite32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC1CTL, MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC1CTL) & ~(B_TRACE_HUB_MEM_MTB_MSCCTL_MSCEN));

      MsuSpareReg = MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MSUSPARE);
      MsuSpareReg &= ~(B_TRACE_HUB_MEM_MSUAPARE_ALLOW_MEM_ACCESS);
      MsuSpareReg |= B_TRACE_HUB_MEM_MSUAPARE_MSC0_LOCK;
      MmioWrite32 (MtbBar + R_TRACE_HUB_MEM_MSUSPARE, MsuSpareReg);

      if ( OrgMscBar[0] != MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC0BAR)
           || OrgMscSize[0] != MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC0SIZE)
           || OrgMscBar[1] != MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC1BAR)
           || OrgMscSize[1] != MmioRead32 (MtbBar + R_TRACE_HUB_MEM_MTB_MSC1SIZE)
         )
      {
        DEBUG ((DEBUG_INFO, "MSCnBAR and MSCnSIZE registers' value is different with the programming value, do a Global Reset\n"));
        TraceHubGlobalReset ();
      }
    }
  }
}

/**
  Get Trace Hub PCI address

  @param[in]  TraceHubDevice    Specify CPU or PCH trace hub device

  @retval UINT64                Trace Hub Pci address
**/
UINT64
GetTraceHubPciBase (
  IN   TRACE_HUB_DEVICE     TraceHubDevice
  )
{
  return PCI_SEGMENT_LIB_ADDRESS (
           0,
           0,
           TraceHubDeviceTable[TraceHubDevice].DevNum,
           TraceHubDeviceTable[TraceHubDevice].FuncNum,
           0
           );
}

/**
  Get Trace Hub MTB Bar

  @param[in]  TraceHubDevice    Specify CPU or PCH trace hub device

  @retval UINT32                Trace Hub MTB bar
**/
UINT32
GetTraceHubMtbBar (
  IN   TRACE_HUB_DEVICE     TraceHubDevice
  )
{
  return (PciSegmentRead32 (GetTraceHubPciBase (TraceHubDevice) + R_TRACE_HUB_CFG_CSR_MTB_LBAR) & 0xFFF00000);
}


/**
  Check if debugger is in use

  @param[in] TraceHubDevice    Specify CPU or PCH trace hub device

  @retval TRUE                 debugger is in use
  @retval FALSE                debugger is NOT in use
**/
BOOLEAN
IsDebuggerInUse (
  IN TRACE_HUB_DEVICE          TraceHubDevice
  )
{
  UINT64                       TraceHubPciBase;
  UINT32                       TraceHubMtbBar= 0xFF;
  UINT8                        CmdData;
  UINT32                       MtbBar;
  UINT32                       Scrpd0;

  TraceHubPciBase = GetTraceHubPciBase (TraceHubDevice);

  if (IsCpuDebugDisabled ()) {
    return FALSE;
  }

  if (PciSegmentRead16 (TraceHubPciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    //
    // if device is hidden, used fixed MTB bar to get SCRPD0
    //
    if (TraceHubDevice == CpuTraceHub) {
      TraceHubMtbBar = PcdGet32 (PcdCpuTraceHubMtbBarBase);
    }
    if (TraceHubDevice == PchTraceHub) {
      TraceHubMtbBar = PCH_TRACE_HUB_MTB_BASE_ADDRESS;
    }
    if (MmioRead32 (TraceHubMtbBar) == 0xFFFFFFFF) {
      DEBUG ((DEBUG_INFO, "Trace hub does not exist\n"));
      return FALSE;
    } else {
      DEBUG ((DEBUG_INFO, "Trace hub is hidden\n"));
      Scrpd0 = MmioRead32 (TraceHubMtbBar + R_TRACE_HUB_MEM_CSR_MTB_SCRPD0);
    }
  } else {
    //
    // if device is exposed, read MTB bar from PCI to get SCRPD0
    //
    CmdData = PciSegmentRead8 (TraceHubPciBase + PCI_COMMAND_OFFSET);
    MtbBar  = GetTraceHubMtbBar (TraceHubDevice);
    if (MtbBar == 0) {
      PciSegmentWrite8 (TraceHubPciBase + PCI_COMMAND_OFFSET, 0);
      if (TraceHubDevice == CpuTraceHub) {
        TraceHubMtbBar = PcdGet32 (PcdCpuTraceHubMtbBarBase);
      }
      if (TraceHubDevice == PchTraceHub) {
        TraceHubMtbBar = PCH_TRACE_HUB_MTB_BASE_ADDRESS;
      }
      PciSegmentWrite32 (TraceHubPciBase + R_TRACE_HUB_CFG_CSR_MTB_UBAR, 0);
      PciSegmentWrite32 (TraceHubPciBase + R_TRACE_HUB_CFG_CSR_MTB_LBAR, TraceHubMtbBar);
    }
    if ((PciSegmentRead8 (TraceHubPciBase + PCI_COMMAND_OFFSET) & EFI_PCI_COMMAND_MEMORY_SPACE) == 0) {
      PciSegmentOr8 (TraceHubPciBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
    }
    Scrpd0 = MmioRead32 (GetTraceHubMtbBar (TraceHubDevice) + R_TRACE_HUB_MEM_CSR_MTB_SCRPD0);
    DEBUG ((DEBUG_INFO, "%s\t", ((TraceHubDevice == CpuTraceHub) ? L"CpuTraceHub" : L"PchTraceHub")));
    DEBUG ((DEBUG_INFO, "Scrpd0 = %x\n", Scrpd0));

    PciSegmentWrite8 (TraceHubPciBase + PCI_COMMAND_OFFSET, CmdData);
    PciSegmentWrite32 (TraceHubPciBase + R_TRACE_HUB_CFG_CSR_MTB_LBAR, MtbBar);
  }
  if (Scrpd0 == 0xffffffff) {
    return FALSE;
  }
  if (Scrpd0 & B_TRACE_HUB_MEM_CSR_MTB_SCRPD0_DEBUGGER_IN_USE) {
    return TRUE;
  } else {
    return FALSE;
  }
}


/**
  Configure trace hub to ACPI mode - hide PCI config space via PSF

  @param[in] CpuTraceHubMode      CPU Trace Hub Mode
  @param[in] PchTraceHubMode      PCH Trace Hub Mode
**/
VOID
ConfigureTraceHubMode (
  TRACE_HUB_ENABLE_MODE       CpuTraceHubMode,
  TRACE_HUB_ENABLE_MODE       PchTraceHubMode
  )
{
  if (IsDebuggerInUse (CpuTraceHub) || (!IsDebuggerInUse (CpuTraceHub) && CpuTraceHubMode == TraceHubModeHostDebugger)) {
    ///
    /// Hide CPU Trace Hub Device
    ///
    DEBUG ((DEBUG_INFO, "ConfigureTraceHubMode() hide CPU trace hub\n"));
    HideCpuTraceHub ();
  }

  if (IsDebuggerInUse (PchTraceHub) || (!IsDebuggerInUse (PchTraceHub) && PchTraceHubMode == TraceHubModeHostDebugger)) {
    ///
    /// Hide PCH Trace Hub Device
    ///
    DEBUG ((DEBUG_INFO, "ConfigureTraceHubMode() hide PCH trace hub\n"));
    PsfHideTraceHubDevice ();
  }
}

/**
  Configure Trace Hub Msc operational region regarding to buffer base and size

  @param[in] TraceHubDevice         Specify CPU or PCH trace hub device
  @param[in] Msc0Base               Base Address of MSC0BAR
  @param[in] Msc0Size               Size of MSC0Size
  @param[in] Msc1Base               Base Address of MSC1BAR
  @param[in] Msc1Size               Size of MSC1Size
**/
VOID
ConfigureMscForTraceHub (
  IN  TRACE_HUB_DEVICE              TraceHubDevice,
  IN  UINT32                        Msc0Base,
  IN  UINT32                        Msc0Size,
  IN  UINT32                        Msc1Base,
  IN  UINT32                        Msc1Size
  )
{
  UINT32                            TraceHubMtbBar;

  TraceHubMtbBar = GetTraceHubMtbBar (TraceHubDevice);
  ///
  ///  Program MSC0BAR, MSC0SIZE, MSC1BAR, MAS1SIZE
  ///
  ///  Write the base address and buffer size for Memory Region 0 to the the MSC0BAR and MSC0SIZE registers.
  ///  Write the base address and buffer size for Memory Region 1 to the the MSC1BAR and MSC1SIZE registers.
  ///  Note that BAR and Size are shifted left 12 bits by the hardware to arrive at physical starting address and size.
  ///  BIOS, therefore, should shift-right by 12 bits before writing a value to these registers.
  ///  This also forces the starting address and size to be on 4kB boundaries.
  ///

  if (Msc0Size) {
    MmioWrite32 (TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC0BAR, (Msc0Base) >> 12);
    MmioWrite32 (TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC0SIZE, (Msc0Size) >> 12);
    DEBUG ((DEBUG_INFO, "[%x] = 0x%08x\n", TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC0BAR, MmioRead32 (TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC0BAR)));
    DEBUG ((DEBUG_INFO, "[%x] = 0x%08x\n", TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC0SIZE, MmioRead32 (TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC0SIZE)));
  }
  if (Msc1Size) {
    MmioWrite32 (TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC1BAR, (Msc1Base) >> 12);
    MmioWrite32 (TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC1SIZE, (Msc1Size) >> 12);
    DEBUG ((DEBUG_INFO, "[%x] = 0x%08x\n", TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC1BAR, MmioRead32 (TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC1BAR)));
    DEBUG ((DEBUG_INFO, "[%x] = 0x%08x\n", TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC1SIZE, MmioRead32 (TraceHubMtbBar + R_TRACE_HUB_MEM_MTB_MSC1SIZE)));
  }
}

/**
  Sets power gating configuration specific to PCH TraceHub.

  @param[in] SiPolicyPpi     Pointer to SI_POLICY_PPI
  @param[in] TraceHubDevice  Specify CPU or PCH trace hub device
**/
STATIC
VOID
ConfigureTraceHubPowerGating (
  IN  TRACE_HUB_DEVICE TraceHubDevice,
  IN  BOOLEAN          PchMasterPowerGating
  )
{
  UINT64              TraceHubPciBase;

  if (TraceHubDevice == CpuTraceHub) {
    return;
  }

  TraceHubPciBase = GetTraceHubPciBase (TraceHubDevice);

  if (!PchMasterPowerGating) {
    PciSegmentAnd32 (
      TraceHubPciBase + R_TRACE_HUB_CFG_DEVIDLEPCE,
      (UINT32)~(B_TRACE_HUB_CFG_DEVIDLEPCE_HAE | B_TRACE_HUB_CFG_DEVIDLEPCE_SE | B_TRACE_HUB_CFG_DEVIDLEPCE_D3HEN | B_TRACE_HUB_CFG_DEVIDLEPCE_DEVIDLEN | B_TRACE_HUB_CFG_DEVIDLEPCE_PMCRE)
      );
  }
}

/**
  This function performs CPU and PCH Trace Hub Buffer initialization.
  Trace memopry buffers need to be allocated as reserved memory with UC attribute.

  @param[in] TraceHubMemBase       Allocated Trace Hub memory base address
  @param[in[ PchMasterPowerGating  Enable or disable Pch Master Power Gating
**/
VOID
ConfigureMscForCpuAndPchTraceHub (
  IN  UINT32                    TraceHubMemBase,
  IN  BOOLEAN                   PchMasterPowerGating
  )
{
  SI_PREMEM_POLICY_PPI         *SiPreMemPolicy;
  SI_PREMEM_CONFIG             *SiPreMemConfig;
  CPU_TRACE_HUB_PREMEM_CONFIG  *CpuTraceHubPreMemConfig;
  PCH_TRACE_HUB_PREMEM_CONFIG  *PchTraceHubPreMemConfig;
  UINT32                       TraceHubMemSize;
  EFI_STATUS                   Status;
  EFI_BOOT_MODE                BootMode;

  DEBUG ((DEBUG_INFO, "ConfigureMscForCpuAndPchTraceHub() Start\n"));
  SiPreMemPolicy = NULL;
  SiPreMemConfig = NULL;
  CpuTraceHubPreMemConfig = NULL;
  PchTraceHubPreMemConfig = NULL;
  TraceHubMemSize = 0;
  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);
  //
  // Get Policy settings through the SiPreMemPolicy PPI
  //
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicy);
  ASSERT_EFI_ERROR(Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gSiPreMemConfigGuid, (VOID *) &SiPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gPchTraceHubPreMemConfigGuid, (VOID *) &PchTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) SiPreMemPolicy, &gCpuTraceHubPreMemConfigGuid, (VOID *) &CpuTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  if (BootMode != BOOT_ON_S3_RESUME) {
    TraceHubMemSize = TraceHubCalculateTotalBufferSize (
                        (UINT8) SiPreMemConfig->PlatformDebugConsent,
                        (UINT8) CpuTraceHubPreMemConfig->TraceHub.EnableMode,
                        (UINT8) CpuTraceHubPreMemConfig->TraceHub.MemReg0Size,
                        (UINT8) CpuTraceHubPreMemConfig->TraceHub.MemReg1Size,
                        (UINT8) PchTraceHubPreMemConfig->TraceHub.EnableMode,
                        (UINT8) PchTraceHubPreMemConfig->TraceHub.MemReg0Size,
                        (UINT8) PchTraceHubPreMemConfig->TraceHub.MemReg1Size
                        );
    DEBUG ((DEBUG_INFO, "Trace Hub Mem Size = 0x%08x\n", TraceHubMemSize));
    if (TraceHubMemSize > 0) {
      if (TraceHubMemBase > 0) {
        DEBUG ((DEBUG_INFO, "Trace Hub Mem Base = 0x%08x\n", TraceHubMemBase));
        Status = MtrrSetMemoryAttribute (TraceHubMemBase , TraceHubMemSize, CacheUncacheable);
        if (Status != EFI_SUCCESS) {
          DEBUG ((DEBUG_ERROR, "Set MTRR attribute fail, Status = %r\n", Status));
        }
        if ((CpuTraceHubPreMemConfig->TraceHub.EnableMode != TraceHubModeDisabled) || (IsDebuggerInUse (CpuTraceHub))) {
          ConfigureMscForTraceHub (
            CpuTraceHub,
            (UINT32) TraceHubMemBase,
            (UINT32) TraceHubBufferSizeTab[CpuTraceHubPreMemConfig->TraceHub.MemReg0Size],
            (UINT32) TraceHubMemBase + TraceHubBufferSizeTab[CpuTraceHubPreMemConfig->TraceHub.MemReg0Size],
            (UINT32) TraceHubBufferSizeTab[CpuTraceHubPreMemConfig->TraceHub.MemReg1Size]
            );
          TraceHubMemBase += TraceHubBufferSizeTab[CpuTraceHubPreMemConfig->TraceHub.MemReg0Size] + TraceHubBufferSizeTab[CpuTraceHubPreMemConfig->TraceHub.MemReg1Size];
          SecureBootConfigurationForCpuTraceHub (&CpuTraceHubPreMemConfig->TraceHub);
        }
        if ((PchTraceHubPreMemConfig->TraceHub.EnableMode != TraceHubModeDisabled) || (IsDebuggerInUse (PchTraceHub))) {
          ConfigureMscForTraceHub (
            PchTraceHub,
            (UINT32) TraceHubMemBase,
            (UINT32) TraceHubBufferSizeTab[PchTraceHubPreMemConfig->TraceHub.MemReg0Size],
            (UINT32) TraceHubMemBase + TraceHubBufferSizeTab[PchTraceHubPreMemConfig->TraceHub.MemReg0Size],
            (UINT32) TraceHubBufferSizeTab[PchTraceHubPreMemConfig->TraceHub.MemReg1Size]);
        }
      } else {
        DEBUG ((DEBUG_ERROR, "Trace Hub Memory is not allocated, skip configure MSC!!\n"));
      }
    }
  } else {
    DEBUG ((DEBUG_INFO, "skip configure MSC for S3 path\n"));
  }
  ConfigureTraceHubPowerGating (PchTraceHub, PchMasterPowerGating);

  ConfigurePchTraceHubInterrupt ();

  ConfigureTraceHubMode (
    CpuTraceHubPreMemConfig->TraceHub.EnableMode,
    PchTraceHubPreMemConfig->TraceHub.EnableMode
    );

  DEBUG ((DEBUG_INFO, "ConfigureMscForCpuAndPchTraceHub() End\n"));
}

/** @file
  This code provides an instance of Pei PSMI Init Lib.

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
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PsmiInitLib.h>
#include <Library/MtrrLib.h>
#include <Register/TraceHubRegs.h>
#include <MemInfoHob.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <PsmiConfig.h>
#include <SaCommonDefinitions.h>
#include <Library/PeiServicesLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci.h>
#include <IndustryStandard/Pci22.h>
#include <Base.h>
#include <PsmiDataHob.h>
#include <Library/MemoryAllocationLib.h>
//
// Size Definitions for PSMI handler and Trace Region
//
UINT32  PsmiHandlerSizeTab[4] = {0, SIZE_256KB, SIZE_512KB, SIZE_1MB};
UINT64  TraceSizeTab[16] = {0, SIZE_1MB, SIZE_2MB, SIZE_4MB, SIZE_8MB, SIZE_16MB, SIZE_32MB, SIZE_64MB, SIZE_128MB, SIZE_256MB, SIZE_512MB, SIZE_1GB, SIZE_2GB, SIZE_4GB, SIZE_8GB, SIZE_16GB};

/**
  Enables Cpu TraceHub MTB Bar

  @retval EFI_SUCCESS           MTB BAR enabled successfully
  @retval EFI_UNSUPPORTED       CPU TH doesn't exist
**/
EFI_STATUS
EnableTraceHubMtbBar (
  VOID
  )
{
  UINT32             CpuTraceHubBaseAddress;
  UINT16             DeviceId;

  CpuTraceHubBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PCI_BUS_NUMBER_CPU_TRACE_HUB, PCI_DEVICE_NUMBER_CPU_TRACE_HUB, PCI_FUNCTION_NUMBER_CPU_TRACE_HUB, 0);
  //
  // Read Device ID from (0, 9, 0) to make sure CPU Intel Trace Hub exists before reading SCRPD1 register
  //
  DeviceId = PciSegmentRead16 (CpuTraceHubBaseAddress + PCI_DEVICE_ID_OFFSET);
  if (DeviceId == 0xFFFF) {
    DEBUG ((DEBUG_INFO, "CPU Intel Trace Hub does not exist, PSMI SCRPD1 register not readable \n."));
    return EFI_UNSUPPORTED;
  }
  //
  // Program the MTB Base Address Register fixed BAR and enable MSE
  //
  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_LBAR, (UINT32) PcdGet32 (PcdCpuTraceHubMtbBarBase));
  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_UBAR, 0);
  PciSegmentOr8 (CpuTraceHubBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);

  return EFI_SUCCESS;
}

/**
  Initializes PSMI Handler and Trace memory size

  @retval EFI_SUCCESS           PsmiInit Function executed successfully
  @retval EFI_UNSUPPORTED       PsmiInit failed to execute
**/
EFI_STATUS
PsmiInit (
  IN    SI_PREMEM_POLICY_PPI      *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                 Status;
  PSMI_INPUT_SCRPD1_REGISTER Scrpd1;
  PSMI_DATA_HOB              *PsmiDataHob;
  UINT32                     CpuTraceHubBaseAddress;
  UINT8                      Index;
  UINT8                      TraceRegion;
  UINT64                     TraceRegionSize;
  UINT8                      TraceRegionCacheType;
  UINT64                     TotalTraceRegionUc=0;
  UINT64                     TotalTraceRegionWc=0;
  UINT64                     TotalTraceRegionDontCare=0;

  PsmiDataHob = NULL;
  DEBUG ((DEBUG_INFO, "PsmiInit () - Start\n"));
  //
  // Install PSMI Data Hob
  //
  DEBUG ((DEBUG_INFO, "Install PSMI DATA HOB\n"));
  InstallPsmiHob (SiPreMemPolicyPpi, &PsmiDataHob);

  //
  // Enables Trace Hub MTB Bar if Trace Hub present , else return
  //
  Status = EnableTraceHubMtbBar ();
  if (Status != EFI_SUCCESS) {
    return Status;
  }
  //
  // Locate the PSMI Data hob, if not found , return
  //
  PsmiDataHob = (PSMI_DATA_HOB *) GetFirstGuidHob (&gPsmiDataHobGuid);
  if (PsmiDataHob == NULL) {
    return EFI_UNSUPPORTED;
  }
  //
  // Read SCRPD1 register to get PSMI handler, trace memory sizes , Trace Region Cache Type
  //
  Scrpd1.RegValue = MmioRead32 (PcdGet32 (PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_CSR_MTB_SCRPD1);
  DEBUG((DEBUG_INFO, "PSMI SCRPD1 = 0x%x \n",Scrpd1.RegValue));

  CpuTraceHubBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PCI_BUS_NUMBER_CPU_TRACE_HUB, PCI_DEVICE_NUMBER_CPU_TRACE_HUB, PCI_FUNCTION_NUMBER_CPU_TRACE_HUB, 0);
  //
  // Clear MSE and MTB_BAR
  //
  PciSegmentWrite8 (CpuTraceHubBaseAddress + PCI_COMMAND_OFFSET, 0);
  //
  // Clear MTB_BAR
  //
  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_LBAR, 0);

  //
  // Use Scratchpad only when Psmihandler size is greater than zero
  //
  if (Scrpd1.Bits.PsmiHandler !=  0)
  {
    PsmiDataHob->PsmiConfig.PsmiInputRegValue = Scrpd1.RegValue;
    /*
    //
    // SCPRD1 bit field description for decoding handler, trace region size and cacheability
    //
    Bit range     Field Name                  Description

    01:00     PSMI_HANDLER_SIZE         Size of the PSMI Handler;
    05:02     TRACE_REGION_0_SIZE       Size of tracing region 0;
    07:06     TRACE_REGION_0_MEMTYPE    Cacheability of tracing region 0;
    11:08     TRACE_REGION_1_SIZE       Size of tracing region 1
    13:12     TRACE_REGION_1_MEMTYPE    Cacheability of tracing region 1
    17:14     TRACE_REGION_2_SIZE       Size of tracing region 2
    19:18     TRACE_REGION_2_MEMTYPE    Cacheability of tracing region 2
    23:20     TRACE_REGION_3_SIZE       Size of tracing region 3
    25:24     TRACE_REGION_3_MEMTYPE    Cacheability of tracing region 3
    29:26     TRACE_REGION_4_SIZE       Size of tracing region 4
    31:30     TRACE_REGION_4_MEMTYPE    Cacheability of tracing region 4
    */
    PsmiDataHob->PsmiConfig.HandlerInfo.HandlerSize      = (UINT8)Scrpd1.Bits.PsmiHandler;
    PsmiDataHob->PsmiConfig.TraceRegionInfo[0].CacheType = (UINT8)Scrpd1.Bits.TraceRegion0CacheType;
    PsmiDataHob->PsmiConfig.TraceRegionInfo[0].Size      = Scrpd1.Bits.TraceRegion0Size;
    PsmiDataHob->PsmiConfig.TraceRegionInfo[1].CacheType = (UINT8)Scrpd1.Bits.TraceRegion1CacheType;
    PsmiDataHob->PsmiConfig.TraceRegionInfo[1].Size      = Scrpd1.Bits.TraceRegion1Size;
    PsmiDataHob->PsmiConfig.TraceRegionInfo[2].CacheType = (UINT8)Scrpd1.Bits.TraceRegion2CacheType;
    PsmiDataHob->PsmiConfig.TraceRegionInfo[2].Size      = Scrpd1.Bits.TraceRegion2Size;
    PsmiDataHob->PsmiConfig.TraceRegionInfo[3].CacheType = (UINT8)Scrpd1.Bits.TraceRegion3CacheType;
    PsmiDataHob->PsmiConfig.TraceRegionInfo[3].Size      = Scrpd1.Bits.TraceRegion3Size;
    PsmiDataHob->PsmiConfig.TraceRegionInfo[4].CacheType = (UINT8)Scrpd1.Bits.TraceRegion4CacheType;
    PsmiDataHob->PsmiConfig.TraceRegionInfo[4].Size      = Scrpd1.Bits.TraceRegion4Size;
  }
  //
  // No PSMI reservation needed , return
  //
  if (PsmiDataHob->PsmiConfig.HandlerInfo.HandlerSize == 0) {
    DEBUG ((DEBUG_INFO, "No PSMI Reservation Request \nPsmiInit () - End \n"));
    return EFI_SUCCESS;
  }
  DEBUG ((DEBUG_INFO, "PSMI Handler size 0x%x \n", PsmiHandlerSizeTab[PsmiDataHob->PsmiConfig.HandlerInfo.HandlerSize]));

  for (Index = 0; Index < MAX_TRACE_REGION; Index++ ) {
    TraceRegion = (UINT8)PsmiDataHob->PsmiConfig.TraceRegionInfo[Index].Size;
    //
    // Trace Region should be allocated only for TraceRegion(N) > 0
    //
    if (TraceRegion == 0) {
      continue;
    }
    TraceRegionSize = TraceSizeTab[TraceRegion];
    TraceRegionCacheType = (UINT8)PsmiDataHob->PsmiConfig.TraceRegionInfo[Index].CacheType;
    DEBUG ((DEBUG_INFO, "PSMI Trace %d Size 0x%lx \n", Index, TraceRegionSize));
    DEBUG ((DEBUG_INFO, "PSMI Trace %d Cache 0x%x \n", Index, TraceRegionCacheType));

    switch( TraceRegionCacheType ) {
      case RegionUncacheable:
        TotalTraceRegionUc += TraceRegionSize;
        break;
      case RegionWriteCombine:
        TotalTraceRegionWc += TraceRegionSize;
        break;
      case RegionDonotCare:
        TotalTraceRegionDontCare += TraceRegionSize;
        break;
    }
  }

  //
  // Fill the PSMI MRC Info block to which will be later consumed MRC
  //
  PsmiDataHob->PsmiConfig.PsmiMrcParam[0].CacheType = RegionDonotCare;
  PsmiDataHob->PsmiConfig.PsmiMrcParam[0].TotalSize = TotalTraceRegionDontCare;
  PsmiDataHob->PsmiConfig.PsmiMrcParam[1].CacheType = RegionUncacheable;
  PsmiDataHob->PsmiConfig.PsmiMrcParam[1].TotalSize = TotalTraceRegionUc;
  PsmiDataHob->PsmiConfig.PsmiMrcParam[2].CacheType = RegionWriteCombine;
  PsmiDataHob->PsmiConfig.PsmiMrcParam[2].TotalSize = TotalTraceRegionWc;

  DEBUG ((DEBUG_INFO, "PSMI Total Dont care Size requested 0x%lx \n", PsmiDataHob->PsmiConfig.PsmiMrcParam[0].TotalSize));
  DEBUG ((DEBUG_INFO, "PSMI Total UC Size requested 0x%lx \n", PsmiDataHob->PsmiConfig.PsmiMrcParam[1].TotalSize));
  DEBUG ((DEBUG_INFO, "PSMI Total WC Size requested 0x%lx \n", PsmiDataHob->PsmiConfig.PsmiMrcParam[2].TotalSize));

  DEBUG ((DEBUG_INFO, "PsmiInit () - End\n"));

  return EFI_SUCCESS;
}

/**
  Configures PSMI Handler/Trace Memory

  @retval EFI_SUCCESS           ConfigurePsmi Function executed successfully
  @retval EFI_UNSUPPORTED       ConfigurePsmi failed to execute
**/
EFI_STATUS
ConfigurePsmi (
  VOID
)
{
  UINT32                         PsmiHandlerSize;
  UINT32                         PsmiHandlerBase;
  EFI_STATUS                     Status;
  PSMI_DATA_HOB                  *PsmiDataHob;
  PSMI_OUTPUT_SCRPD1_REGISTER    Scrpd1;
  PSMI_HANDLER_SPACE_OFFSET      PsmiHandlerSpace;
  MEMORY_PLATFORM_DATA_HOB       *MemInfoHob;
  UINT8                          Index;
  UINT8                          Index1;
  UINT64                         Size;
  UINT64                         BaseAddress;
  UINT32                         CpuTraceHubBaseAddress;
  UINT8                          HandlerErrCode;

  PsmiDataHob    = NULL;
  HandlerErrCode = 0;
  DEBUG ((DEBUG_INFO, "ConfigurePsmi () - Start\n"));
  //
  // Locate the PSMI Data hob, if not found , return
  //
  PsmiDataHob = (PSMI_DATA_HOB *)GetFirstGuidHob(&gPsmiDataHobGuid);
  if (PsmiDataHob == NULL) {
    return EFI_UNSUPPORTED;
  }

  if (PsmiDataHob->PsmiConfig.HandlerInfo.HandlerSize == 0) {
    DEBUG ((DEBUG_INFO, "ConfigurePsmi () - PSMI disabled \n"));
    return EFI_SUCCESS;
  }
  //
  // Enables Trace Hub MTB Bar if Trace Hub present , else skip PSMI reservation and return
  //
  Status = EnableTraceHubMtbBar ();
  if (Status != EFI_SUCCESS) {
    return Status;
  }
  MemInfoHob = (MEMORY_PLATFORM_DATA_HOB *) GetFirstGuidHob (&gSiMemoryPlatformDataGuid);
  if (MemInfoHob == NULL) {
    DEBUG ((DEBUG_INFO, "MemoryPlatformData hob not found, returning from PSMI Configuration \n"));
    return EFI_UNSUPPORTED;
  }
  PsmiHandlerSize = PsmiHandlerSizeTab[PsmiDataHob->PsmiConfig.HandlerInfo.HandlerSize];
  //
  // Allocate aligned PSMI base Address
  //
  HandlerErrCode  = PSMI_ALLOCATION_SUCCESS;
  PsmiHandlerBase = (UINT32) (UINTN) AllocateAlignedReservedPages (EFI_SIZE_TO_PAGES (PsmiHandlerSize), PsmiHandlerSize);
  if (PsmiHandlerBase == 0) {
    DEBUG ((DEBUG_ERROR, "AllocateAlignedReservedPages for PSMI Handler failed\n"));
    HandlerErrCode = ERROR_OUT_OF_RESOURCES;
  } else {
    DEBUG ((DEBUG_INFO, "PSMI Handler Base 0x%x Size 0x%x \n",PsmiHandlerBase,PsmiHandlerSize));
    //
    // Configure the PSMI Handler base memory type as Writeback(WB)
    //
    Status = MtrrSetMemoryAttribute ((EFI_PHYSICAL_ADDRESS) PsmiHandlerBase , PsmiHandlerSize , CacheWriteBack);
    if (EFI_ERROR (Status)) {
      // No Assert required, publish the error code
      DEBUG ((DEBUG_INFO, "Setting PSMI Handler Base Writeback failed!\n"));
      HandlerErrCode = ERROR_MTRR_SHORTAGE;
    }
  }

  for (Index = 0; Index < MAX_TRACE_CACHE_TYPE; Index++) {
    //
    // Pass the MRC Hob Info structure for Size not equal to zero
    //
    if (PsmiDataHob->PsmiConfig.PsmiMrcParam[Index].TotalSize == 0) {
      continue;
    }
    Size        = PsmiDataHob->PsmiConfig.PsmiMrcParam[Index].TotalSize;
    BaseAddress = MemInfoHob->Data.PsmiInfo[Index].BaseAddress;
    //
    // Distribute the combined Base Address from Hob into Trace Region
    //
    for (Index1 = 0; Index1 < MAX_TRACE_REGION; Index1++) {
      if (PsmiDataHob->PsmiConfig.TraceRegionInfo[Index1].Size == 0) {
        continue;
      }
      if (MemInfoHob->Data.PsmiInfo[Index].CacheType == PsmiDataHob->PsmiConfig.TraceRegionInfo[Index1].CacheType) {
        //
        // Update the trace region if BaseAddress is valid else copy the error code
        //
        if (MemInfoHob->Data.PsmiInfo[Index].BaseAddress != 0) {
          PsmiDataHob->PsmiConfig.TraceRegionInfo[Index1].TraceRegionBase = BaseAddress;
          //
          // Increment the BaseAddress and reduce size
          //
          DEBUG ((DEBUG_INFO, "Trace Region %d Base 0x%lx \n",Index1, PsmiDataHob->PsmiConfig.TraceRegionInfo[Index1].TraceRegionBase));
          BaseAddress = BaseAddress + TraceSizeTab[PsmiDataHob->PsmiConfig.TraceRegionInfo[Index1].Size];
          Size = Size - TraceSizeTab[PsmiDataHob->PsmiConfig.TraceRegionInfo[Index1].Size];
          PsmiDataHob->PsmiConfig.TraceRegionInfo[Index1].ErrCode = PSMI_ALLOCATION_SUCCESS;
        } else {
          PsmiDataHob->PsmiConfig.TraceRegionInfo[Index1].ErrCode = MemInfoHob->Data.PsmiInfo[Index].ErrorCode;
          DEBUG ((DEBUG_INFO, "Error Trace Region %d Error 0x%x \n",Index1, PsmiDataHob->PsmiConfig.TraceRegionInfo[Index1].ErrCode ));
        }
      } else {
         continue;
      }
      //
      // Increment to next Memory BaseAddress in Hob
      //
      if (Size == 0) {
        break;
      }
    }
  }
  //
  // Update PSMI SCPRD1 register with PSMI outputs info, zero the register first to override before MRC value
  //
  Scrpd1.RegValue = 0;
  Scrpd1.Bits.PsmiHandlerBase = (PsmiHandlerBase >> 18);
  Scrpd1.Bits.PsmiHandlerResultCode  = HandlerErrCode;
  Scrpd1.Bits.TraceRegion0ResultCode = PsmiDataHob->PsmiConfig.TraceRegionInfo[0].ErrCode;
  Scrpd1.Bits.TraceRegion1ResultCode = PsmiDataHob->PsmiConfig.TraceRegionInfo[1].ErrCode;
  Scrpd1.Bits.TraceRegion2ResultCode = PsmiDataHob->PsmiConfig.TraceRegionInfo[2].ErrCode;
  Scrpd1.Bits.TraceRegion3ResultCode = PsmiDataHob->PsmiConfig.TraceRegionInfo[3].ErrCode;
  Scrpd1.Bits.TraceRegion4ResultCode = PsmiDataHob->PsmiConfig.TraceRegionInfo[4].ErrCode;
  //
  // Write SCRPD1 register to output PSMI handler Base and Trace Error Info
  //
  CpuTraceHubBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PCI_BUS_NUMBER_CPU_TRACE_HUB, PCI_DEVICE_NUMBER_CPU_TRACE_HUB, PCI_FUNCTION_NUMBER_CPU_TRACE_HUB, 0);
  MmioWrite32 (PcdGet32 (PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_CSR_MTB_SCRPD1, Scrpd1.RegValue);
  DEBUG((DEBUG_INFO, "SCRPD1 Output = 0x%x \n",Scrpd1.RegValue));

  //
  // Clear MSE
  //
  PciSegmentWrite8 (CpuTraceHubBaseAddress + PCI_COMMAND_OFFSET, 0);
  //
  // Clear MTB_BAR
  //
  PciSegmentWrite32 (CpuTraceHubBaseAddress + R_TRACE_HUB_CFG_CSR_MTB_LBAR, 0);
  //
  // Output the Trace Region Base Address at Handler Memory offset 0x1000
  //
  PsmiHandlerSpace.PsmiHandlerBaseAddress =  (UINT64)PsmiHandlerBase;
  PsmiHandlerSpace.TraceRegion0BaseAddress = PsmiDataHob->PsmiConfig.TraceRegionInfo[0].TraceRegionBase;
  PsmiHandlerSpace.TraceRegion1BaseAddress = PsmiDataHob->PsmiConfig.TraceRegionInfo[1].TraceRegionBase;
  PsmiHandlerSpace.TraceRegion2BaseAddress = PsmiDataHob->PsmiConfig.TraceRegionInfo[2].TraceRegionBase;
  PsmiHandlerSpace.TraceRegion3BaseAddress = PsmiDataHob->PsmiConfig.TraceRegionInfo[3].TraceRegionBase;
  PsmiHandlerSpace.TraceRegion4BaseAddress = PsmiDataHob->PsmiConfig.TraceRegionInfo[4].TraceRegionBase;
  PsmiHandlerSpace.PsmiInputRegValue       = PsmiDataHob->PsmiConfig.PsmiInputRegValue;

  CopyMem ((VOID *) (UINTN)(PsmiHandlerBase + PSMI_HANDLER_MEMORY_OFFSET_1000), (VOID *)&(PsmiHandlerSpace.PsmiHandlerBaseAddress), sizeof (PSMI_HANDLER_SPACE_OFFSET));

  DEBUG ((DEBUG_INFO, "ConfigurePsmi () - End \n"));
  return EFI_SUCCESS;
}

/**
  Override policies relevant to CPU Trace Hub to enable PSMI debug in PreMem.

  @param[in] SiPreMemPolicyPpi         The Silicon PreMem Policy PPI instance
**/
VOID
PsmiTraceHubPolicyOverride (
  IN  SI_PREMEM_POLICY_PPI             *SiPreMemPolicyPpi
  )
{
  EFI_STATUS                           Status;
  CPU_TRACE_HUB_PREMEM_CONFIG          *CpuTraceHubPreMemConfig;
  PSMI_DATA_HOB                          *PsmiDataHob;

  CpuTraceHubPreMemConfig            = NULL;
  PsmiDataHob                        = NULL;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuTraceHubPreMemConfigGuid, (VOID *) &CpuTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  PsmiDataHob = (PSMI_DATA_HOB *)GetFirstGuidHob (&gPsmiDataHobGuid);
  if (PsmiDataHob != NULL) {
  //
  // CPU Trace Hub settings for PSMI (Force HostDebugger Mode)
  //
    if (PsmiDataHob->PsmiConfig.HandlerInfo.HandlerSize != 0) {

      DEBUG ((DEBUG_INFO, "PSMI Force CPU Trace Hub in HostDebugger mode \n"));
      DEBUG ((DEBUG_INFO, "Override CPU Trace Hub MemSize 0/1 to 0 \n"));

      CpuTraceHubPreMemConfig->TraceHub.MemReg0Size = TraceBufferNone;
      CpuTraceHubPreMemConfig->TraceHub.MemReg1Size = TraceBufferNone;
      CpuTraceHubPreMemConfig->TraceHub.EnableMode  = TraceHubModeHostDebugger;

      DEBUG ((DEBUG_INFO, "CpuTraceHubPreMemConfig->TraceHub.EnableMode = %x\n", CpuTraceHubPreMemConfig->TraceHub.EnableMode));
      DEBUG ((DEBUG_INFO, "CpuTraceHubPreMemConfig->TraceHub.MemReg0Size = %x\n", CpuTraceHubPreMemConfig->TraceHub.MemReg0Size));
      DEBUG ((DEBUG_INFO, "CpuTraceHubPreMemConfig->TraceHub.MemReg1Size = %x\n", CpuTraceHubPreMemConfig->TraceHub.MemReg1Size));
    }
  }
}

/**
  Init and Install PSMI Hob
  @param[in] SiPreMemPolicyPpi       - The Silicon PreMem Policy PPI instance
  @param[out] PSMI_DATA_HOB           - PSMI_DATA_HOB instance installed by this function

  @retval EFI_SUCCESS
**/
EFI_STATUS
InstallPsmiHob (
  IN    SI_PREMEM_POLICY_PPI      *SiPreMemPolicyPpi,
  OUT   PSMI_DATA_HOB             **PsmiDataHobOut
  )
{
  EFI_STATUS                    Status;
  PSMI_DATA_HOB                 *PsmiDataHob;

  ///
  /// Create HOB for PSMI Data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (PSMI_DATA_HOB),
             (VOID **) &PsmiDataHob
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize default HOB data
  ///
  ///
  /// PSMI_DATA_HOB
  ///
  PsmiDataHob->EfiHobGuidType.Name = gPsmiDataHobGuid;
  DEBUG ((DEBUG_INFO, "PsmiDataHob->EfiHobGuidType.Name: %g\n", &PsmiDataHob->EfiHobGuidType.Name));
  ZeroMem (&(PsmiDataHob->PsmiConfig), sizeof (PSMI_DATA_HOB) - sizeof (EFI_HOB_GUID_TYPE));
  DEBUG ((DEBUG_INFO, "PsmiDataHob @ %X\n", PsmiDataHob));
  DEBUG ((DEBUG_INFO, "PsmiDataHobSize - HobHeader: %X\n", sizeof (PSMI_DATA_HOB) - sizeof (EFI_HOB_GUID_TYPE)));
  DEBUG ((DEBUG_INFO, "PsmiDataHobSize: %X\n", sizeof (PSMI_DATA_HOB)));

  (*PsmiDataHobOut)   = PsmiDataHob;

  DEBUG ((DEBUG_INFO, "PSMI HOB installed\n"));

  return EFI_SUCCESS;
}
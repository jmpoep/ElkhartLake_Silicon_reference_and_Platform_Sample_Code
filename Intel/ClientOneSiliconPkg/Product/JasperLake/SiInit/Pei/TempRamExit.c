/** @file
  Silicon Program MTRR PPI is used for initializing MTRR values
  after memory initialization complete.

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

@par Specification
**/
#include "SiInitPreMem.h"
#include <PiPei.h>
#include <CpuRegs.h>
#include <SaRegs.h>
#include <Register/Msr.h>
#include <Register/Cpuid.h>
#include <Register/TraceHubRegs.h>
#include <ConfigBlock.h>
#include <TraceHubConfig.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/MtrrLib.h>
#include <Library/DebugLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/ConfigBlockLib.h>
#include <IndustryStandard/Pci.h>
#include <SmramMemoryReserve.h>
#include <Library/PeiServicesTablePointerLib.h>
#ifdef FSP_FLAG
#include <Library/FspCommonLib.h>
#endif

/**
  Get system memory resource descriptor by owner.

  @param[in] OwnerGuid   resource owner guid
**/
EFI_HOB_RESOURCE_DESCRIPTOR *
EFIAPI
GetResourceDescriptorByOwner (
  IN EFI_GUID   *OwnerGuid
  )
{
  EFI_PEI_HOB_POINTERS    Hob;

  //
  // Get the HOB list for processing
  //
  Hob.Raw = GetHobList ();

  //
  // Collect memory ranges
  //
  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_RESOURCE_DESCRIPTOR) {
      if ((Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_MEMORY_RESERVED) && \
          (CompareGuid (&Hob.ResourceDescriptor->Owner, OwnerGuid))) {
        return  Hob.ResourceDescriptor;
      }
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
  }

  return NULL;
}

/**
  Get system memory from HOB.

  @param[in,out] LowMemoryLength   less than 4G memory length
  @param[in,out] HighMemoryLength  greater than 4G memory length
**/
VOID
GetSystemMemorySize (
  IN OUT UINT64              *LowMemoryLength,
  IN OUT UINT64              *HighMemoryLength
  )
{
  EFI_STATUS                  Status;
  EFI_BOOT_MODE               BootMode;
  EFI_RESOURCE_ATTRIBUTE_TYPE ResourceAttribute;
  EFI_PEI_HOB_POINTERS        Hob;
  CONST EFI_PEI_SERVICES      **PeiServices;

  ResourceAttribute = (
                       EFI_RESOURCE_ATTRIBUTE_PRESENT |
                       EFI_RESOURCE_ATTRIBUTE_INITIALIZED |
                       EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE |
                       EFI_RESOURCE_ATTRIBUTE_WRITE_COMBINEABLE |
                       EFI_RESOURCE_ATTRIBUTE_WRITE_THROUGH_CACHEABLE |
                       EFI_RESOURCE_ATTRIBUTE_WRITE_BACK_CACHEABLE
                       );

  PeiServices = GetPeiServicesTablePointer ();
  Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
  ASSERT_EFI_ERROR (Status);

  if (BootMode != BOOT_ON_S3_RESUME) {
    ResourceAttribute |= EFI_RESOURCE_ATTRIBUTE_TESTED;
  }

  *HighMemoryLength = 0;
  *LowMemoryLength  = SIZE_1MB;
  //
  // Get the HOB list for processing
  //
  Hob.Raw = GetHobList ();

  //
  // Collect memory ranges
  //
  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_RESOURCE_DESCRIPTOR) {
      if ((Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY) ||
          ((Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_MEMORY_RESERVED) &&
           (Hob.ResourceDescriptor->ResourceAttribute == ResourceAttribute))) {
        //
        // Need memory above 1MB to be collected here
        //
        if (Hob.ResourceDescriptor->PhysicalStart >= BASE_1MB &&
            Hob.ResourceDescriptor->PhysicalStart < (EFI_PHYSICAL_ADDRESS) BASE_4GB) {
          *LowMemoryLength += (UINT64) (Hob.ResourceDescriptor->ResourceLength);
        } else if (Hob.ResourceDescriptor->PhysicalStart >= (EFI_PHYSICAL_ADDRESS) BASE_4GB) {
          *HighMemoryLength += (UINT64) (Hob.ResourceDescriptor->ResourceLength);
        }
      }
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
  }
}

UINT8
CalculatingMtrrReservedNumber (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT32                          Data32;
  UINT8                           ReservedNum;
  UINT64                          CpuTraceHubBaseAddr;
  CONST EFI_PEI_SERVICES          **PeiServices;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  CPU_TRACE_HUB_PREMEM_CONFIG     *CpuTraceHubPreMemConfig;
  PCH_TRACE_HUB_PREMEM_CONFIG     *PchTraceHubPreMemConfig;

  ReservedNum = 0;
  CpuTraceHubPreMemConfig = NULL;
  PchTraceHubPreMemConfig = NULL;

  PeiServices = GetPeiServicesTablePointer ();
  //
  // Reserve variable MTRRs for TraceHub and Processor Trace (RTIT) if required
  //
  Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gSiPreMemPolicyPpiGuid,
                             0,
                             NULL,
                             (VOID **) &SiPreMemPolicyPpi
                             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuTraceHubPreMemConfigGuid, (VOID *) &CpuTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPchTraceHubPreMemConfigGuid, (VOID *) &PchTraceHubPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  if (PchTraceHubPreMemConfig->TraceHub.EnableMode == 1) {
    ReservedNum++;
  }
  if ((CpuTraceHubPreMemConfig->TraceHub.EnableMode == 1) &&
      (PchTraceHubPreMemConfig->TraceHub.EnableMode == 0)) {
    ReservedNum++;
  }

  //
  // Check if Processor Trace is supported
  //
  CpuTraceHubBaseAddr = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, PCI_BUS_NUMBER_CPU_TRACE_HUB, PCI_DEVICE_NUMBER_CPU_TRACE_HUB, PCI_FUNCTION_NUMBER_CPU_TRACE_HUB, 0);
  PciSegmentWrite32 (CpuTraceHubBaseAddr + R_TRACE_HUB_CFG_CSR_MTB_LBAR, (UINT32) PcdGet32 (PcdCpuTraceHubMtbBarBase));
  PciSegmentWrite32 (CpuTraceHubBaseAddr + R_TRACE_HUB_CFG_CSR_MTB_UBAR, 0);
  PciSegmentOr8 (CpuTraceHubBaseAddr + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
  Data32 = MmioRead32 (PcdGet32 (PcdCpuTraceHubMtbBarBase) + R_TRACE_HUB_MEM_MTB_STHCAP1);
  if (Data32 & B_TRACE_HUB_MEM_MTB_STHCAP1_RTITCNT_MASK) {
    ReservedNum++;
  }

  //
  // Clear MSE and MTB_BAR
  //
  PciSegmentWrite8 (CpuTraceHubBaseAddr + PCI_COMMAND_OFFSET, 0);
  PciSegmentWrite32 (CpuTraceHubBaseAddr + R_TRACE_HUB_CFG_CSR_MTB_LBAR, 0);

  return ReservedNum;
}

/**
  This function programs Cache Attributes.
**/
VOID
ProgramCacheAttributes (
  VOID
  )
{
  EFI_STATUS                  Status;
  UINTN                       Index;
  UINT64                      LowMemoryLength;
  UINT64                      HighMemoryLength;
  UINT64                      TopHighMemory;
  UINT64                      MaxLowMemoryLength;
  UINT32                      VariableMtrrCount;
  UINT8                       MtrrReserved;
  MTRR_SETTINGS               MtrrSetting;
  EFI_PHYSICAL_ADDRESS        TsegBaseAddress;
#ifdef FSP_FLAG
  FSP_GLOBAL_DATA             *FspData;
  EFI_HOB_RESOURCE_DESCRIPTOR *Descriptor;
#else
  EFI_PEI_HOB_POINTERS        Hob;
  UINT64                      SmramSize;
  UINT64                      SmramBase;
  CONST EFI_PEI_SERVICES      **PeiServices;
  EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *SmramHobDescriptorBlock;
#endif

  TsegBaseAddress = 0;
#ifdef FSP_FLAG
  Descriptor = NULL;
#endif
  ///
  /// Reset all MTRR setting.
  ///
  ZeroMem (&MtrrSetting, sizeof (MTRR_SETTINGS));

  ///
  /// Cache the Flash area as WP to boost performance
  /// Set WP cache size to fixed at 16MB for saving MTRR usage.
  ///
  Status = MtrrSetMemoryAttributeInMtrrSettings (
             &MtrrSetting,
             0xff000000,
             0x01000000,
             CacheWriteProtected
             );
  ASSERT_EFI_ERROR (Status);

  MtrrSetAllMtrrs (&MtrrSetting);

#ifdef FSP_FLAG
  FspData = GetFspGlobalDataPointer ();
  if (FspData->Reserved3[0] == TRUE) {
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "MicrocodeRegionBase : 0x%08x\n", FspData->PlatformData.MicrocodeRegionBase));
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "MicrocodeRegionSize : 0x%08x\n", FspData->PlatformData.MicrocodeRegionSize));
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "CodeRegionBase      : 0x%08x\n", FspData->PlatformData.CodeRegionBase));
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "CodeRegionSize      : 0x%08x\n", FspData->PlatformData.CodeRegionSize));
  }
#endif

  //
  // Get system memory from HOB
  //
  GetSystemMemorySize (&LowMemoryLength, &HighMemoryLength);
  DEBUG ((DEBUG_INFO, "Memory Length (Below 4GB) = %lx.\n", LowMemoryLength));
  DEBUG ((DEBUG_INFO, "Memory Length (Above 4GB) = %lx.\n", HighMemoryLength));

  //
  // Set fixed MTRR values
  //
  Status = MtrrSetMemoryAttributeInMtrrSettings (
              &MtrrSetting,
              0x00000,
              0xA0000,
              CacheWriteBack
              );
  ASSERT_EFI_ERROR (Status);

  Status = MtrrSetMemoryAttributeInMtrrSettings (
              &MtrrSetting,
              0xA0000,
              0x20000,
              CacheUncacheable
              );
  ASSERT_EFI_ERROR (Status);

  Status = MtrrSetMemoryAttributeInMtrrSettings (
              &MtrrSetting,
              0xC0000,
              0x40000,
              CacheWriteProtected
              );
  ASSERT_EFI_ERROR (Status);

  MaxLowMemoryLength = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_TOLUD)) & B_SA_TOLUD_TOLUD_MASK;

  //
  // Set 1M - Tolud as WB.
  // Set TSEG - Tolud later to avoid MTRR hole.
  //
  Status = MtrrSetMemoryAttributeInMtrrSettings (
              &MtrrSetting,
              0x100000,
              MaxLowMemoryLength - 0x100000,
              CacheWriteBack
              );
  ASSERT_EFI_ERROR (Status);

#ifdef FSP_FLAG
  Descriptor = GetResourceDescriptorByOwner (&gFspReservedMemoryResourceHobTsegGuid);
  if (Descriptor != NULL) {
    TsegBaseAddress = Descriptor->PhysicalStart;
  }
#else

  SmramSize = 0;
  SmramBase = 0;
  PeiServices = GetPeiServicesTablePointer ();
  Status = (*PeiServices)->GetHobList (PeiServices, (VOID **) &Hob.Raw);
  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_GUID_EXTENSION) {
      if (CompareGuid (&Hob.Guid->Name, &gEfiSmmPeiSmramMemoryReserveGuid)) {
        SmramHobDescriptorBlock = (EFI_SMRAM_HOB_DESCRIPTOR_BLOCK *) (Hob.Guid + 1);
        for (Index = 0; Index < SmramHobDescriptorBlock->NumberOfSmmReservedRegions; Index++) {
          if (SmramHobDescriptorBlock->Descriptor[Index].PhysicalStart > 0x100000) {
            SmramSize += SmramHobDescriptorBlock->Descriptor[Index].PhysicalSize;
            if (SmramBase == 0 || SmramBase > SmramHobDescriptorBlock->Descriptor[Index].CpuStart) {
              SmramBase = SmramHobDescriptorBlock->Descriptor[Index].CpuStart;
            }
          }
        }
        break;
      }
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
  }
  TsegBaseAddress = (EFI_PHYSICAL_ADDRESS) SmramBase;
#endif

  //
  // Set TSEG - TOLUD to UC to reduce MTRR register usage
  //
  if (TsegBaseAddress != 0) {
    Status = MtrrSetMemoryAttributeInMtrrSettings (
                &MtrrSetting,
                TsegBaseAddress,
                MaxLowMemoryLength - TsegBaseAddress,
                CacheUncacheable
                );
    ASSERT_EFI_ERROR (Status);
  }

  if (HighMemoryLength) {
    //
    // Enlarge above 4GB memory size to be power of two aligned.
    // Note: above 4GB MMIO resource region should not overlap this memory address
    //
    TopHighMemory = GetPowerOfTwo64 (HighMemoryLength + SIZE_4GB);
    if (TopHighMemory != (HighMemoryLength + SIZE_4GB)) {
      TopHighMemory = LShiftU64 (TopHighMemory, 1);
    }

    do {
      Status = MtrrSetMemoryAttributeInMtrrSettings (
                 &MtrrSetting,
                 SIZE_4GB,
                 TopHighMemory - SIZE_4GB,
                 CacheWriteBack
                 );
      if (TopHighMemory > SIZE_4GB) {
        TopHighMemory = RShiftU64 (TopHighMemory, 1);
      }
    } while ((EFI_SUCCESS != Status) && (TopHighMemory > SIZE_4GB));
  }

  //
  // When key features needed we will free some MTRR for them later and sacrifice some of above 4GB coverage.
  // In later phase boot loader code can re-configure MTRR to exclude flash region and get back above 4GB coverage.
  //
  VariableMtrrCount = GetVariableMtrrCount ();
  MtrrReserved = CalculatingMtrrReservedNumber ();
  for (Index = VariableMtrrCount - 1; MtrrReserved > 0; Index--, MtrrReserved--) {
    MtrrSetting.Variables.Mtrr[Index].Base = 0;
    MtrrSetting.Variables.Mtrr[Index].Mask = 0;
  }

  ///
  /// Update MTRR setting from MTRR buffer
  ///
  MtrrSetAllMtrrs (&MtrrSetting);
}

/**
  This function prints MTRRs.
**/
VOID
PrintMtrrs (
  VOID
  )
{
  DEBUG_CODE_BEGIN();

  typedef struct {
    char    *Desc;
    UINT32  Msr;
  } MTRR_INFO;

  MSR_IA32_MTRRCAP_REGISTER Msr;
  UINT32                    Index;
  UINT32                    Mtrr;

  static MTRR_INFO MtrrInfo[] = {
    {"MSR_IA32_MTRR_FIX64K_00000",  MSR_IA32_MTRR_FIX64K_00000},
    {"MSR_IA32_MTRR_FIX16K_80000",  MSR_IA32_MTRR_FIX16K_80000},
    {"MSR_IA32_MTRR_FIX16K_A0000",  MSR_IA32_MTRR_FIX16K_A0000},
    {"MSR_IA32_MTRR_FIX4K_C0000 ",  MSR_IA32_MTRR_FIX4K_C0000},
    {"MSR_IA32_MTRR_FIX4K_C8000 ",  MSR_IA32_MTRR_FIX4K_C8000},
    {"MSR_IA32_MTRR_FIX4K_D0000 ",  MSR_IA32_MTRR_FIX4K_D0000},
    {"MSR_IA32_MTRR_FIX4K_D8000 ",  MSR_IA32_MTRR_FIX4K_D8000},
    {"MSR_IA32_MTRR_FIX4K_E0000 ",  MSR_IA32_MTRR_FIX4K_E0000},
    {"MSR_IA32_MTRR_FIX4K_E8000 ",  MSR_IA32_MTRR_FIX4K_E8000},
    {"MSR_IA32_MTRR_FIX4K_F0000 ",  MSR_IA32_MTRR_FIX4K_F0000},
    {"MSR_IA32_MTRR_FIX4K_F8000 ",  MSR_IA32_MTRR_FIX4K_F8000}
  };

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "MTRR programming:\n"));

  for (Index = 0; Index < sizeof(MtrrInfo) / sizeof(MTRR_INFO); ++Index) {
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "%a Msr %x = %016llx\n", MtrrInfo[Index].Desc, MtrrInfo[Index].Msr, AsmReadMsr64(MtrrInfo[Index].Msr)));
  }

  Msr.Uint64 = AsmReadMsr64(MSR_IA32_MTRRCAP);
  for (Index = 0; Index < Msr.Bits.VCNT; ++Index) {
    Mtrr = MSR_IA32_MTRR_PHYSBASE0 + (2 * Index);
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "MSR_IA32_MTRR_PHYSBASE%d Msr %x = %016llx\n",
        Index, Mtrr, AsmReadMsr64(Mtrr)
    ));

    DEBUG ((DEBUG_INFO | DEBUG_INIT, "MSR_IA32_MTRR_PHYSMASK%d Msr %x = %016llx\n",
        Index, Mtrr + 1, AsmReadMsr64(Mtrr + 1)
    ));
  }
  DEBUG_CODE_END();
}

/**
  Program MTRR values and print MTRRs.
**/
EFI_STATUS
EFIAPI
TempRamExit (
  IN  VOID    *TempRamExitParamPtr
  )
{
  //
  // Disable CAR
  //
  DisableCacheAsRam (TRUE);
  //
  // Program MTRR values.
  //
  ProgramCacheAttributes ();
  //
  // Print MTRR values.
  //
  PrintMtrrs ();

  return EFI_SUCCESS;
}


/** @file
  Source code file for FSP Init Pre-Memory PEI module

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2020 Intel Corporation.

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

#include <PiPei.h>
#include <FspInitPreMem.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuRegs.h>
#include <Library/BootMediaLib.h>
#include <Library/PcdLib.h>
#include <Library/PeiMeLib.h>
#include <Library/PostCodeLib.h>
#include <Library/FspCommonLib.h>
#include <Library/PerformanceLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/FspInfoLib.h>
#include <PchResetPlatformSpecific.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Ppi/TempRamExitPpi.h>
#include <Ppi/PlatformSpecificResetHandler.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/Reset2.h>
#include <Ppi/FspmArchConfigPpi.h>
#include <Ppi/PeiPreMemSiDefaultPolicy.h>

extern EFI_GUID gFspSiliconFvGuid;
extern EFI_GUID gFspPerformanceDataGuid;

EFI_PEI_RESET_PPI mResetPpi = {
  FspResetSystem
};

static EFI_PEI_PPI_DESCRIPTOR mPreMemPpiList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_PPI| EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiResetPpiGuid,
    &mResetPpi
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_PPI_DESCRIPTOR mPpiBootMode = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMasterBootModePpiGuid,
  NULL
};

EFI_PEI_NOTIFY_DESCRIPTOR mMemoryDiscoveredNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMemoryDiscoveredPpiGuid,
  MemoryDiscoveredPpiNotifyCallback
};

/**
  This function reset the entire platform, including all processor and devices, and
  reboots the system.

  @param  PeiServices General purpose services available to every PEIM.

  @retval EFI_SUCCESS if it completed successfully.
**/
EFI_STATUS
EFIAPI
FspResetSystem (
  IN CONST EFI_PEI_SERVICES **PeiServices
  )
{


    FspApiReturnStatusReset (FSP_STATUS_RESET_REQUIRED_WARM);
  return EFI_SUCCESS;
}


/**
  Resets the entire platform.

  @param[in] ResetType            UEFI defined reset type.
  @param[in] ResetStatus          The status code for the reset.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.

**/
VOID
FspResetSystem2 (
  IN EFI_RESET_TYPE     ResetType,
  IN EFI_STATUS         ResetStatus,
  IN UINTN              DataSize,
  IN VOID               *ResetData OPTIONAL
  )
{
  EFI_GUID            *GuidPtr;
  UINT32              FspReturnStatusResetType;

  GuidPtr = NULL;
  FspReturnStatusResetType = 0;

  DEBUG ((DEBUG_ERROR, "[FspResetSystem2] FSP Reset Initiated\n"));

  switch (ResetType) {
  case EfiResetWarm:
    FspReturnStatusResetType = FSP_STATUS_RESET_REQUIRED_WARM;
    break;

  case EfiResetCold:
    FspReturnStatusResetType = FSP_STATUS_RESET_REQUIRED_COLD;
    break;

  case EfiResetPlatformSpecific:
    if (ResetData == NULL) {
      DEBUG ((DEBUG_ERROR, "[FspResetSystem2] ResetData is not available.\n"));
      return;
    }
    GuidPtr = (EFI_GUID *) ((UINT8 *) ResetData + DataSize - sizeof (EFI_GUID));
    if (!CompareGuid (GuidPtr, &gPchGlobalResetGuid)) {
      return;
    }
    FspReturnStatusResetType = FSP_STATUS_RESET_REQUIRED_3;
    break;

  default:
    DEBUG ((DEBUG_ERROR, "[FspResetSystem2] Reset Type = %x triggered by FSP is not supported.\n",ResetType));
    return;
  }

  FspApiReturnStatusReset (FspReturnStatusResetType);

}

/**
  Dummy reset handler.

  @param[in] ResetType            UEFI defined reset type.
  @param[in] ResetStatus          The status code for the reset.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.
**/
VOID
NullReset (
  IN EFI_RESET_TYPE     ResetType,
  IN EFI_STATUS         ResetStatus,
  IN UINTN              DataSize,
  IN VOID               *ResetData OPTIONAL
  )
{
  DEBUG ((DEBUG_INFO, "%a was called to skip resets\n", __FUNCTION__));
}


EFI_PEI_RESET2_PPI mNullResetPpi = {
  NullReset
};
/**
  This function register reset handler ppi for platform

  @param[in]  PeiServices      Pointer to PEI Services Table.
  @param[in]  NotifyDescriptor Pointer to the descriptor for the Notification event that
                               caused this function to execute.
  @param[in]  Interface        Pointer to the PPI data associated with this function.

  @retval     EFI_SUCCESS  The function completes successfully
  @retval     others

**/
EFI_STATUS
EFIAPI
Reset2ReadyCallBack (
  IN CONST EFI_PEI_SERVICES     **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Interface
  )
{
  EFI_STATUS                    Status;
  EDKII_PLATFORM_SPECIFIC_RESET_HANDLER_PPI *ResetHandlerPpi;
    Status = PeiServicesLocatePpi (
               &gEdkiiPlatformSpecificResetHandlerPpiGuid,
               0,
               NULL,
               (VOID **) &ResetHandlerPpi
               );

    ASSERT_EFI_ERROR (Status);

    Status = ResetHandlerPpi->RegisterResetNotify (ResetHandlerPpi,FspResetSystem2);

  return EFI_SUCCESS;
}


GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_NOTIFY_DESCRIPTOR  mReset2Ready = {
  EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gEfiPeiReset2PpiGuid,
  (EFI_PEIM_NOTIFY_ENTRY_POINT) Reset2ReadyCallBack
};

/**
  This function Installs the PPI in the list if not already installed. If Installed reinstall the PPI with new instance

  @retval EFI_SUCCESS if it completed successfully.

**/
EFI_STATUS
InstallReinstallFspResetPpiServices (
  VOID
  )
{
  VOID                            *OldPpi;
  EFI_PEI_PPI_DESCRIPTOR          *OldPpiDescriptor;
  EFI_STATUS                      Status;
  UINT8                           Index;

  PeiServicesNotifyPpi (&mReset2Ready);

  for (Index =0; Index < (sizeof(mPreMemPpiList)/sizeof(EFI_PEI_PPI_DESCRIPTOR)); Index++) {
    //
    // Locate PPI to see if already installed if installed reinstall with new instance
    //
    Status = PeiServicesLocatePpi (
              mPreMemPpiList[Index].Guid,
              0,
              &OldPpiDescriptor,
              &OldPpi
              );
    if(EFI_ERROR (Status)) {
      Status = PeiServicesInstallPpi (&mPreMemPpiList[Index]);
      if(EFI_ERROR(Status)) {
        return Status;
      }
    } else {
      //
      // Re-install the PPI
      //
      Status = PeiServicesReInstallPpi (OldPpiDescriptor, &mPreMemPpiList[Index]);
      if(EFI_ERROR(Status)) {
        return Status;
      }
    }
  }
  return EFI_SUCCESS;
}

/**
  This function retrieves the top of usable low memory.

  @param    HobListPtr   A HOB list pointer.

  @retval                Usable low memory top.

**/
UINT32
GetUsableLowMemTop (
  CONST VOID       *HobStart
  )
{
  EFI_PEI_HOB_POINTERS  Hob;
  UINT32                MemLen;
  /*
   * Get the HOB list for processing
   */
  Hob.Raw = (VOID *)HobStart;

  /*
   * Collect memory ranges
   */
  MemLen = 0x100000;
  while (!END_OF_HOB_LIST (Hob)) {
    if (Hob.Header->HobType == EFI_HOB_TYPE_RESOURCE_DESCRIPTOR) {
      if (Hob.ResourceDescriptor->ResourceType == EFI_RESOURCE_SYSTEM_MEMORY) {
        /*
         * Need memory above 1MB to be collected here
         */
        if (Hob.ResourceDescriptor->PhysicalStart >= 0x100000 &&
            Hob.ResourceDescriptor->PhysicalStart < (EFI_PHYSICAL_ADDRESS) 0x100000000) {
          MemLen += (UINT32) (Hob.ResourceDescriptor->ResourceLength);
        }
      }
    }
    Hob.Raw = GET_NEXT_HOB (Hob);
  }

  return MemLen;
}

/**
  This function determines if any MTRRs have been programmed.

  @retval  TRUE if any MTRRs have been programmed.
  @retval  FALSE if no MTRRs have been programmed.
**/
BOOLEAN
CheckIfMtrrsProgrammed()
{
  static UINT32 FixedMtrrs[] = {
    MSR_IA32_MTRR_FIX64K_00000,
    MSR_IA32_MTRR_FIX16K_80000,
    MSR_IA32_MTRR_FIX16K_A0000,
    MSR_IA32_MTRR_FIX4K_C0000,
    MSR_IA32_MTRR_FIX4K_C8000,
    MSR_IA32_MTRR_FIX4K_D0000,
    MSR_IA32_MTRR_FIX4K_D8000,
    MSR_IA32_MTRR_FIX4K_E0000,
    MSR_IA32_MTRR_FIX4K_E8000,
    MSR_IA32_MTRR_FIX4K_F0000,
    MSR_IA32_MTRR_FIX4K_F8000
  };

  MSR_IA32_MTRRCAP_REGISTER Msr;
  UINT32                    Index;
  UINT32                    Mtrr;

  for (Index = 0; Index < sizeof(FixedMtrrs) / sizeof(UINT32); ++Index) {
    if (AsmReadMsr64(FixedMtrrs[Index]) != 0) return TRUE;
  }

  Msr.Uint64 = AsmReadMsr64(MSR_IA32_MTRRCAP);
  for (Index = 0; Index < Msr.Bits.VCNT * 2; ++Index) {
    Mtrr = MSR_IA32_MTRR_PHYSBASE0 + Index;
    if (AsmReadMsr64(Mtrr) != 0) return TRUE;
  }

  return FALSE;
}

/**
  Migrate FSP-M UPD data before destroying CAR.
**/
VOID
EFIAPI
MigrateFspmUpdData (
  VOID
  )
{
  FSP_INFO_HEADER           *FspInfoHeaderPtr;
  VOID                      *FspmUpdPtrPostMem;
  VOID                      *FspmUpdPtrPreMem;

  FspInfoHeaderPtr = GetFspInfoHeader();
  FspmUpdPtrPostMem = (VOID *)AllocatePages (EFI_SIZE_TO_PAGES ((UINTN)FspInfoHeaderPtr->CfgRegionSize));
  ASSERT(FspmUpdPtrPostMem != NULL);

  FspmUpdPtrPreMem = (VOID *)GetFspMemoryInitUpdDataPointer ();
  CopyMem (FspmUpdPtrPostMem, (VOID *)FspmUpdPtrPreMem, (UINTN)FspInfoHeaderPtr->CfgRegionSize);

  //
  // Update FSP-M UPD pointer in FSP Global Data
  //
  SetFspMemoryInitUpdDataPointer((VOID *)FspmUpdPtrPostMem);

  DEBUG ((DEBUG_INFO, "Migrate FSP-M UPD from %X to %X\n", FspmUpdPtrPreMem, FspmUpdPtrPostMem));
}

/**
  This function reports and installs new FV

  @retval     EFI_SUCCESS          The function completes successfully
**/
EFI_STATUS
ReportAndInstallNewFv (
  VOID
  )
{
  EFI_FIRMWARE_VOLUME_EXT_HEADER *FwVolExtHeader;
  FSP_INFO_HEADER                *FspInfoHeader;
  EFI_FIRMWARE_VOLUME_HEADER     *FvHeader;
  UINT8                          *CurPtr;
  UINT8                          *EndPtr;
  FSP_GLOBAL_DATA                *FspData;

  FspData = GetFspGlobalDataPointer ();
  if (FspData->FspMode == FSP_IN_API_MODE) {
    FspInfoHeader = GetFspInfoHeaderFromApiContext();
    if (FspInfoHeader->Signature != FSP_INFO_HEADER_SIGNATURE) {
      DEBUG ((DEBUG_ERROR, "The signature of FspInfoHeader getting from API context is invalid.\n"));
      FspInfoHeader = GetFspInfoHeader();
    }

    CurPtr = (UINT8 *)FspInfoHeader->ImageBase;
    EndPtr = CurPtr + FspInfoHeader->ImageSize - 1;

    while (CurPtr < EndPtr) {
      FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)CurPtr;
      if (FvHeader->Signature != EFI_FVH_SIGNATURE) {
        break;
      }

      if (FvHeader->ExtHeaderOffset != 0) {
        //
        // Searching for the silicon FV in the FSP image.
        //
        FwVolExtHeader = (EFI_FIRMWARE_VOLUME_EXT_HEADER *) ((UINT8 *) FvHeader + FvHeader->ExtHeaderOffset);
        if (CompareGuid(&FwVolExtHeader->FvName, &gFspSiliconFvGuid)) {
          PeiServicesInstallFvInfoPpi (
            NULL,
            (VOID *)FvHeader,
            (UINTN) FvHeader->FvLength,
            NULL,
            NULL
            );
        }
      }
      CurPtr += FvHeader->FvLength;
    }
  }

  return EFI_SUCCESS;
}


/**
  This function will be called when MRC is done.

  @param  PeiServices General purpose services available to every PEIM.

  @param  NotifyDescriptor Information about the notify event..

  @param  Ppi The notify context.

  @retval EFI_SUCCESS If the function completed successfully.
**/
EFI_STATUS
EFIAPI
MemoryDiscoveredPpiNotifyCallback (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                     Status;
  UINT8                          PhysicalAddressBits;
  CPUID_VIR_PHY_ADDRESS_SIZE_EAX Eax;
  FSP_GLOBAL_DATA                *FspData;
  VOID                           **HobListPtr;
  FSP_INFO_HOB                   *FspInfo;
  FSP_TEMP_RAM_EXIT_PPI          *TempRamExitPpi;

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "Memory Discovered Notify invoked ...\n"));

  //
  // Create FSP Information HOB.
  //
  FspInfo = NULL;
  FspInfo = BuildGuidHob (&gFspInfoGuid, sizeof (FSP_INFO_HOB));
  ASSERT (FspInfo != NULL);
  if (FspInfo != NULL) {
    Status = GetFspInfo (FspInfo);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Get FSP Information Failed!, Status = %r\n", Status));
      ZeroMem (FspInfo, sizeof (FSP_INFO_HOB));
    }
  } else {
    DEBUG ((DEBUG_ERROR, "Create FSP Information HOB Failed!\n"));
  }

  FspData = GetFspGlobalDataPointer ();
  if (FspData->FspMode == FSP_IN_API_MODE) {
    AsmCpuid (CPUID_EXTENDED_FUNCTION, &Eax.Uint32, NULL, NULL, NULL);
    if (Eax.Uint32 >= CPUID_VIR_PHY_ADDRESS_SIZE) {
      AsmCpuid (CPUID_VIR_PHY_ADDRESS_SIZE, &Eax.Uint32, NULL, NULL, NULL);
      PhysicalAddressBits = (UINT8) Eax.Bits.PhysicalAddressBits;
    } else {
      PhysicalAddressBits = 36;
    }

    ///
    /// Create a CPU hand-off information
    ///
    BuildCpuHob (PhysicalAddressBits, 16);

    //
    // Migrate FSP-M UPD data before destroying CAR
    //
    MigrateFspmUpdData ();

    //
    // Calling use FspMemoryInit API
    // Return the control directly
    //
    HobListPtr = (VOID **)GetFspApiParameter2 ();
    if (HobListPtr != NULL) {
      *HobListPtr = (VOID *)GetHobList ();
    }
#if FixedPcdGetBool(PcdBfxEnable) == 1
    //
    // Request NVM handoff
    //
    if (BootMediaIsUfs ()) {
      Status = PeiHeciRequestDeviceOwnership ();
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
        CpuDeadLoop ();
      }
    }
#endif
    //
    // This is the end of the FspMemoryInit API
    // Give control back to the boot loader
    //
    DEBUG ((DEBUG_INFO | DEBUG_INIT, "FspMemoryInitApi() - End\n"));

    //
    // PerfData bits [0:55] specify the timing, use the same to record initial timestamps for performance
    //
    PERF_START_EX(&gFspPerformanceDataGuid, "EventRec", NULL, (FspData->PerfData[0] & FSP_PERFORMANCE_DATA_TIMER_MASK), 0xF000);
    PERF_END_EX(&gFspPerformanceDataGuid, "EventRec", NULL, (FspData->PerfData[1] & FSP_PERFORMANCE_DATA_TIMER_MASK), 0xF07F);
    PERF_START_EX(&gFspPerformanceDataGuid, "EventRec", NULL, (FspData->PerfData[2] & FSP_PERFORMANCE_DATA_TIMER_MASK), 0xD000);
    PERF_END_EX(&gFspPerformanceDataGuid, "EventRec", NULL, 0, 0xD07F);

    //Memory Init Api Exit PostCode
    //FSP Common Module(0x800) | Api Exit(0x7F)
    PostCode (0x87F);
    SetFspApiReturnStatus (EFI_SUCCESS);
    Pei2LoaderSwitchStack ();

    if (GetFspApiCallingIndex () == TempRamExitApiIndex) {
      PERF_START_EX(&gFspPerformanceDataGuid, "EventRec", NULL, 0, 0xB000);
      //TempRamExit Phase PostCode Set
      SetPhaseStatusCode (0xB000);
      //TempRamExit Api Entry PostCode
      //FSP Common Module(0x800) | Api Entry(0x00)
      PostCode (0x800);

      //
      // Program MTRR values.
      //
      Status = PeiServicesLocatePpi (
                 &gFspTempRamExitPpiGuid,
                 0,
                 NULL,
                 (VOID **) &TempRamExitPpi
                 );
      ASSERT_EFI_ERROR (Status);
      if (EFI_ERROR (Status)) {
        SetFspApiReturnStatus (Status);
        Pei2LoaderSwitchStack ();
      }
      TempRamExitPpi->TempRamExit (NULL);

      //
      // This is the end of the TempRamExit API
      // Give control back to the boot loader
      //
      DEBUG ((DEBUG_INFO | DEBUG_INIT, "TempRamExitApi() - End\n"));
      PERF_END_EX(&gFspPerformanceDataGuid, "EventRec", NULL, 0, 0xB07F);
      //TempRamExit Api Exit PostCode
      //FSP Common Module(0x800) | Api Exit(0x7F)
      PostCode (0x87F);
      SetFspApiReturnStatus (EFI_SUCCESS);
      Pei2LoaderSwitchStack ();
    }

    PERF_START_EX(&gFspPerformanceDataGuid, "EventRec", NULL, 0, 0x9000);
    //SiliconInit Phase PostCode set
    SetPhaseStatusCode (0x9000);
    //SiliconInt Api Entry PostCode
    //FSP Common Module(0x800) | Api Entry(0x00)
    PostCode (0x800);
    //
    // MTRRs are not already programmed in FSP flow 1.1.
    //
    if (!CheckIfMtrrsProgrammed ()) {
      Status = PeiServicesLocatePpi (
                 &gFspTempRamExitPpiGuid,
                 0,
                 NULL,
                 (VOID **) &TempRamExitPpi
                 );
      ASSERT_EFI_ERROR (Status);
      if (EFI_ERROR (Status)) {
        SetFspApiReturnStatus (Status);
        Pei2LoaderSwitchStack ();
      }
      TempRamExitPpi->TempRamExit (NULL);
    }

    //
    // Install FSP silicon FV
    //
    ReportAndInstallNewFv ();
  }

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "Memory Discovered Notify completed ...\n"));

  return EFI_SUCCESS;
}

/**
  FSP Init before memory PEI module entry point

  @param[in]  FileHandle           Not used.
  @param[in]  PeiServices          General purpose services available to every PEIM.

  @retval     EFI_SUCCESS          The function completes successfully
  @retval     EFI_OUT_OF_RESOURCES Insufficient resources to create database
**/
EFI_STATUS
EFIAPI
FspInitPreMemEntryPoint (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                            Status;
  SI_PREMEM_POLICY_PPI                  *SiPreMemPolicyPpi;
  EFI_BOOT_MODE                         BootMode;
  FSPM_UPD                              *FspmUpdDataPtr;
  FSPM_ARCH_CONFIG_PPI                  *FspmArchConfigPpi;
  EFI_PEI_PPI_DESCRIPTOR                *FspmArchConfigPpiDesc;
  PEI_PREMEM_SI_DEFAULT_POLICY_INIT_PPI *PeiPreMemSiDefaultPolicyInitPpi;

  DEBUG ((DEBUG_INFO, "FspInitPreMemEntryPoint () - Start\n"));
  PeiPreMemSiDefaultPolicyInitPpi = NULL;

#if FixedPcdGetBool(PcdBfxEnable) == 1
  BOOLEAN                 FirstEntry;

  Status = PeiServicesRegisterForShadow (FileHandle);

  FirstEntry = TRUE;

  if (Status == EFI_NOT_FOUND) {
    ASSERT_EFI_ERROR (Status);
    return Status;
  } else if (Status == EFI_ALREADY_STARTED) {
    FirstEntry = FALSE;
  }

  if (FirstEntry) {
#endif
  //MemoryInit Phase Postcode set
  SetPhaseStatusCode (0xD000);
  //MemoryInit API Entry PostCode
  //FSP Common Module(0x800) | Api Entry(0x00)
  PostCode (0x800);

  //
  // Silicon code will produce Default Policy Init PPI in PrePolicy phase,
  // different owners will consume this PPI to create policy.
  // -----------------------------------------------------------------------
  // |Task                               |Owner for API |Owner for Dispatch|
  // -----------------------------------------------------------------------
  // |Consume Default Policy Init PPI to | FSP          | Boot loader      |
  // |create default policy.             |              |                  |
  // -----------------------------------------------------------------------
  // |Update policy as needed.           | FSP by UPD   | Boot loader      |
  // -----------------------------------------------------------------------
  // |Install PolicyReady PPI to start   | FSP          | Boot loader      |
  // |silicon OnPolicy callbacks.        |              |                  |
  // -----------------------------------------------------------------------
  //
  if (GetFspGlobalDataPointer()->FspMode == FSP_IN_API_MODE) {
    //
    // Install Fsp Instance of ResetPpi to handle reset case.
    //
    Status = InstallReinstallFspResetPpiServices ();
    ASSERT_EFI_ERROR (Status);
#if FixedPcdGetBool(PcdBfxEnable) == 0
    ///
    /// Install Stall PPI
    ///
    Status = InstallStallPpi();
    ASSERT_EFI_ERROR (Status);
#endif
    FspmUpdDataPtr = NULL;

    //
    // Get the UPD pointer.
    //
    FspmUpdDataPtr = (FSPM_UPD *) GetFspMemoryInitUpdDataPointer ();
    SetFspSiliconInitUpdDataPointer ((void *)NULL);

    DEBUG_CODE_BEGIN ();
      UINT32  Index;
      DEBUG ((DEBUG_INFO, "Dumping FSPM_UPD - Size: 0x%8X", sizeof(FSPM_UPD)));
      for (Index = 0; Index < sizeof (FSPM_UPD); ++Index) {
        if (Index % 0x10 == 0) {
          DEBUG ((DEBUG_INFO, "\n0x%8X:", Index));
        }
        DEBUG ((DEBUG_INFO, " 0x%02X", *(((UINT8 *)FspmUpdDataPtr) + Index)));
      }
      DEBUG ((DEBUG_INFO, "\n"));
    DEBUG_CODE_END ();

    //
    // Get the Boot Mode
    //
    BootMode = FspmUpdDataPtr->FspmArchUpd.BootMode;
#if FixedPcdGetBool(PcdBfxEnable) == 1
    if (PcdGetBool (PcdNvVariableEmulationMode)) {
      //
      // Emulated variables must load defaults each boot
      //
      BootMode = BOOT_WITH_DEFAULT_SETTINGS;
    }
#endif
    PeiServicesSetBootMode (BootMode);

    Status = PeiServicesInstallPpi (&mPpiBootMode);
    ASSERT_EFI_ERROR (Status);

    FspmArchConfigPpi = NULL;
    FspmArchConfigPpi = (FSPM_ARCH_CONFIG_PPI *) AllocateZeroPool (sizeof (FSPM_ARCH_CONFIG_PPI));
    if (FspmArchConfigPpi == NULL) {
      ASSERT (FALSE);
      return EFI_OUT_OF_RESOURCES;
    }
    FspmArchConfigPpi->Revision            = 1;
    FspmArchConfigPpi->NvsBufferPtr        = FspmUpdDataPtr->FspmArchUpd.NvsBufferPtr;
    FspmArchConfigPpi->BootLoaderTolumSize = FspmUpdDataPtr->FspmArchUpd.BootLoaderTolumSize;

    FspmArchConfigPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
    if (FspmArchConfigPpiDesc == NULL) {
      ASSERT (FALSE);
      return EFI_OUT_OF_RESOURCES;
    }
    FspmArchConfigPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    FspmArchConfigPpiDesc->Guid  = &gFspmArchConfigPpiGuid;
    FspmArchConfigPpiDesc->Ppi   = FspmArchConfigPpi;
    //
    // Install FSP-M Arch Config PPI
    //
    Status = PeiServicesInstallPpi (FspmArchConfigPpiDesc);
    ASSERT_EFI_ERROR (Status);

    //
    // Locate Policy init PPI to install default silicon policy
    //
    Status = PeiServicesLocatePpi (
               &gSiPreMemDefaultPolicyInitPpiGuid,
               0,
               NULL,
               (VOID **) &PeiPreMemSiDefaultPolicyInitPpi
               );
    ASSERT_EFI_ERROR (Status);
    if (PeiPreMemSiDefaultPolicyInitPpi != NULL) {
      Status = PeiPreMemSiDefaultPolicyInitPpi->PeiPreMemPolicyInit ();
      ASSERT_EFI_ERROR (Status);
      if (Status == EFI_SUCCESS) {
        Status = PeiServicesLocatePpi (
                   &gSiPreMemPolicyPpiGuid,
                   0,
                   NULL,
                   (VOID **) &SiPreMemPolicyPpi
                   );
        ASSERT_EFI_ERROR (Status);
        if ((Status == EFI_SUCCESS) && (SiPreMemPolicyPpi != NULL)) {
          FspUpdatePeiPchPolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);
          FspUpdatePeiCpuPolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);
          FspUpdatePeiSecurityPolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr); //Security Policy also needs to be updated before CpuInstallPolicyPpi
          FspUpdatePeiMePolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);
          FspUpdatePeiSaPolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);
          FspUpdatePeiSiPolicyPreMem (SiPreMemPolicyPpi, FspmUpdDataPtr);

          //
          // In FSP API mode, no policy update from boot loader so FSP should install
          // PolicyReady PPI to trigger silicon initialization OnPolicy callbacks.
          //
          Status = SiPreMemInstallPolicyReadyPpi ();
          ASSERT_EFI_ERROR (Status);
        }
      }
    }
  }
#if FixedPcdGetBool(PcdBfxEnable) == 1
  }

  if (!FirstEntry) {
#endif
  ///
  /// Now that all of the pre-permament memory activities have
  /// been taken care of, post a call-back for the permament-memory
  /// resident services, such as HOB construction.
  /// PEI Core will switch stack after this PEIM exit.  After that the MTRR
  /// can be set.
  ///
  Status = PeiServicesNotifyPpi (&mMemoryDiscoveredNotifyList);
  ASSERT_EFI_ERROR (Status);

if (GetFspGlobalDataPointer()->FspMode == FSP_IN_DISPATCH_MODE) {
#if FixedPcdGetBool(PcdBfxEnable) == 1
    //
    // Request NVM handoff
    //
    if (BootMediaIsUfs ()) {
      Status = PeiHeciRequestDeviceOwnership ();
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
        CpuDeadLoop ();
      }
    }
#endif
}

#if FixedPcdGetBool(PcdBfxEnable) == 1
    ///
    /// Install Stall PPI
    ///
    Status = InstallStallPpi();
    ASSERT_EFI_ERROR (Status);
  }
#endif
  DEBUG ((DEBUG_INFO, "FspInitPreMemEntryPoint () - End\n"));
  return Status;
}

/** @file
  Source file for FSP Init PEI module

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

#include "FspInit.h"
#include <Library/PcdLib.h>
#include <Ppi/SecPlatformInformation.h>
#include <Ppi/PeiSiDefaultPolicy.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciSegmentLib.h>

EFI_STATUS
FspInitOnPciEnumerationComplete (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  );

EFI_PEI_PPI_DESCRIPTOR mFspReadyToInstallMp = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiReadyToInstallMpPpiGuid,
  NULL
};

EFI_SEC_PLATFORM_INFORMATION2_PPI mFspSecPlatformInformation2 = {
  FspSecPlatformInformation2
};

EFI_PEI_PPI_DESCRIPTOR mFspPeiSecPlatformInformation2 = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiSecPlatformInformation2PpiGuid,
  &mFspSecPlatformInformation2
};

STATIC
EFI_PEI_NOTIFY_DESCRIPTOR  mOnPciEnumerationCompleteNotifyList[] = {
  {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK  | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPciEnumerationCompleteProtocolGuid,
    FspInitOnPciEnumerationComplete
  }
};

EFI_PEI_PPI_DESCRIPTOR      mS3SmmInitDonePpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEdkiiS3SmmInitDoneGuid,
  NULL
};

/**
  This routine is used to get Sec Platform Information Record Pointer.

  @param[in] PeiServices    Pointer to the PEI services table

  @retval GetSecPlatformInformation2 - The pointer of Sec Platform Information Record Pointer.
**/
EFI_SEC_PLATFORM_INFORMATION_RECORD2 *
GetSecPlatformInformationInfoInFormat2 (
  IN EFI_PEI_SERVICES **PeiServices
  )
{
  EFI_STATUS                           Status;
  UINT64                               InformationSize;
  EFI_SEC_PLATFORM_INFORMATION_PPI     *SecPlatformInformationPpi;
  EFI_SEC_PLATFORM_INFORMATION_RECORD  *SecPlatformInformation = NULL;
  EFI_SEC_PLATFORM_INFORMATION_RECORD2 *SecPlatformInformation2;

  //
  // Get BIST information from Sec Platform Information
  //
  Status = PeiServicesLocatePpi (
             &gEfiSecPlatformInformationPpiGuid,    // GUID
             0,                                     // Instance
             NULL,                                  // EFI_PEI_PPI_DESCRIPTOR
             (VOID **) &SecPlatformInformationPpi   // PPI
             );

  DEBUG ((DEBUG_INFO, "LocatePpi SecPlatformInformationPpi Status - %r\n", Status));
  if (EFI_ERROR(Status)) {
    return NULL;
  }

  InformationSize = 0;
  Status = SecPlatformInformationPpi->PlatformInformation (
                                        (CONST EFI_PEI_SERVICES **) PeiServices,
                                        &InformationSize,
                                        SecPlatformInformation
                                        );

  ASSERT (Status == EFI_BUFFER_TOO_SMALL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return NULL;
  }

  SecPlatformInformation = AllocatePool((UINTN)InformationSize);
  ASSERT (SecPlatformInformation != NULL);
  if (SecPlatformInformation == NULL) {
    return NULL;
  }

  //
  // Retrieve BIST data from SecPlatform
  //
  Status = SecPlatformInformationPpi->PlatformInformation (
                                        (CONST EFI_PEI_SERVICES**) PeiServices,
                                        &InformationSize,
                                        SecPlatformInformation
                                        );
  DEBUG ((DEBUG_INFO, "FSP  SecPlatformInformation2Ppi->PlatformInformation Status - %r\n", Status));
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return NULL;
  }

  SecPlatformInformation2 = AllocatePool (sizeof (EFI_SEC_PLATFORM_INFORMATION_RECORD2));
  ASSERT (SecPlatformInformation2 != NULL);
  if (SecPlatformInformation2 == NULL) {
    return NULL;
  }

  SecPlatformInformation2->NumberOfCpus = 1;
  SecPlatformInformation2->CpuInstance[0].CpuLocation = 0;
  SecPlatformInformation2->CpuInstance[0].InfoRecord.x64HealthFlags.Uint32 = SecPlatformInformation->x64HealthFlags.Uint32;

  FreePool(SecPlatformInformation);

  return SecPlatformInformation2;
}

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4090)
#endif
/**
  Implementation of the FspPlatformInformation2 service in EFI_SEC_PLATFORM_INFORMATION2_PPI.

  @param  PeiServices                The pointer to the PEI Services Table.
  @param  StructureSize              The pointer to the variable describing size of the input buffer.
  @param  PlatformInformationRecord2 The pointer to the EFI_SEC_PLATFORM_INFORMATION_RECORD2.

  @retval EFI_SUCCESS                The data was successfully returned.
  @retval EFI_BUFFER_TOO_SMALL       The buffer was too small. The current buffer size needed to
                                     hold the record is returned in StructureSize.

**/
EFI_STATUS
EFIAPI
FspSecPlatformInformation2 (
  IN CONST EFI_PEI_SERVICES                   **PeiServices,
  IN OUT UINT64                               *StructureSize,
     OUT EFI_SEC_PLATFORM_INFORMATION_RECORD2 *PlatformInformationRecord2
  )
{
  if (GetFspGlobalDataPointer()->FspMode == FSP_IN_API_MODE) {
    FSP_S_CONFIG                         *FspsConfigUpd;
    UINTN                                InformationDataSize;
    EFI_SEC_PLATFORM_INFORMATION_RECORD2 *PlatformInformationRecord2temp;

    FspsConfigUpd = &((FSPS_UPD *) GetFspSiliconInitUpdDataPointer())->FspsConfig;
    PlatformInformationRecord2temp = (EFI_SEC_PLATFORM_INFORMATION_RECORD2 *)FspsConfigUpd->CpuBistData;
    InformationDataSize = sizeof (EFI_SEC_PLATFORM_INFORMATION_RECORD2) + sizeof (EFI_SEC_PLATFORM_INFORMATION_CPU) * (PlatformInformationRecord2temp->NumberOfCpus - 1);
    if (*StructureSize < InformationDataSize) {
      *StructureSize = InformationDataSize;
      return EFI_BUFFER_TOO_SMALL;
    }

    CopyMem((EFI_SEC_PLATFORM_INFORMATION_RECORD2 *) PlatformInformationRecord2, (VOID*) FspsConfigUpd->CpuBistData, InformationDataSize);

  } else {
    UINTN                                InformationDataSize;
    EFI_SEC_PLATFORM_INFORMATION_RECORD2 *SecPlatformInformation2;

    SecPlatformInformation2 = NULL;
    SecPlatformInformation2 = GetSecPlatformInformationInfoInFormat2 ((EFI_PEI_SERVICES **) PeiServices);
    ASSERT (SecPlatformInformation2 != NULL);

    if (SecPlatformInformation2 != NULL) {
      InformationDataSize = sizeof (EFI_SEC_PLATFORM_INFORMATION_RECORD2) + sizeof (EFI_SEC_PLATFORM_INFORMATION_CPU) * (SecPlatformInformation2->NumberOfCpus - 1);
      if (*StructureSize < InformationDataSize) {
        *StructureSize = InformationDataSize;
        return EFI_BUFFER_TOO_SMALL;
      }

      CopyMem ((VOID *) PlatformInformationRecord2, (VOID *) SecPlatformInformation2, InformationDataSize);
    }
  }

DEBUG_CODE_BEGIN ();
  EFI_STATUS                      Status;
  FSP_M_CONFIG                    *FspmConfigUpd;
  UINTN                           Index;
  UINTN                           BistResetPolicy;
  CPU_CONFIG_LIB_PREMEM_CONFIG    *CpuConfigLibPreMemConfig;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;

  if (GetFspGlobalDataPointer()->FspMode == FSP_IN_API_MODE) {
    FspmConfigUpd = &((FSPM_UPD *) GetFspMemoryInitUpdDataPointer())->FspmConfig;
    BistResetPolicy = FspmConfigUpd->BistOnReset;
  } else {
    Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
    ASSERT_EFI_ERROR (Status);
    Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuConfigLibPreMemConfigGuid, (VOID *) &CpuConfigLibPreMemConfig);
    ASSERT_EFI_ERROR (Status);

    BistResetPolicy = CpuConfigLibPreMemConfig->BistOnReset;
  }
  DEBUG ((DEBUG_INFO, "BIST On Reset Policy - %x\n", BistResetPolicy));
  DEBUG ((DEBUG_INFO, "BIST From PPI NumberOfCpus - %x\n\n", PlatformInformationRecord2->NumberOfCpus));

  for (Index = 0; Index < PlatformInformationRecord2->NumberOfCpus; Index++) {
    DEBUG ((DEBUG_INFO, "BIST From PPI IA32HealthFlags Instance(%x)- %x\n", Index, PlatformInformationRecord2->CpuInstance[Index].InfoRecord.x64HealthFlags.Uint32));
    DEBUG ((DEBUG_INFO, "BIST From PPI CpuLocation Instance(%x) - %x\n",    Index, PlatformInformationRecord2->CpuInstance[Index].CpuLocation));
  }
DEBUG_CODE_END ();

  return EFI_SUCCESS;
}

#ifdef _MSC_VER
#pragma warning (pop)
#endif

/**
  This function gets registered as a callback

  @param[in]  PeiServices       An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation
  @param[in]  NotifyDescriptor  Address of the notification descriptor data structure.
  @param[in]  Ppi               Address of the PPI that was installed.

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    No enough buffer to allocate
**/
EFI_STATUS
FspInitOnPciEnumerationComplete (
  IN  EFI_PEI_SERVICES            **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR   *NotifyDescriptor,
  IN  VOID                        *Ppi
  )
{

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP S3 SMM INIT DONE ...\n"));
  PeiServicesInstallPpi (&mS3SmmInitDonePpi);

  return EFI_SUCCESS;
}

/**
  To install PolicyReadyPpi to invoke Silicon initialization.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  SiPolicy PPI.

  @retval EFI_STATUS              The return status from sub function
**/
EFI_STATUS
EFIAPI
FspInitMpServicePpiCallback (
  IN  EFI_PEI_SERVICES             **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR    *NotifyDescriptor,
  IN  VOID                         *Ppi
  )
{
  EFI_STATUS  Status;
  Status = SiInstallPolicyReadyPpi ();
  ASSERT_EFI_ERROR (Status);
  return Status;
}

static EFI_PEI_NOTIFY_DESCRIPTOR  mFspInitMpServicePpiCallbackNotifyList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_DISPATCH | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
    &gEfiPeiMpServicesPpiGuid,
    FspInitMpServicePpiCallback
  }
};

/**
  FSP Init PEI module entry point

  @param[in]  FileHandle           Not used.
  @param[in]  PeiServices          General purpose services available to every PEIM.

  @retval     EFI_SUCCESS          The function completes successfully
  @retval     EFI_OUT_OF_RESOURCES Insufficient resources to create database
**/
EFI_STATUS
EFIAPI
FspInitEntryPoint (
  IN       EFI_PEI_FILE_HANDLE    FileHandle,
  IN CONST EFI_PEI_SERVICES       **PeiServices
  )
{
  EFI_STATUS                     Status;
  FSPS_UPD                       *FspsUpd;
  SI_POLICY_PPI                  *SiPolicyPpi;
  FSP_INFO_HEADER                *FspInfoHeader;
  UINT32                         MaxLogicProcessors;
  EFI_PEI_PPI_DESCRIPTOR         *PpiDescriptor;
  UINT64                         CpuMpHob;
  EFI_PEI_MP_SERVICES_PPI        *CpuMpPpi;
  EFI_BOOT_MODE                  BootMode;
  PEI_SI_DEFAULT_POLICY_INIT_PPI *PeiSiDefaultPolicyInitPpi;

  Status = EFI_SUCCESS;
  FspsUpd = NULL;

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

    FspInfoHeader = GetFspInfoHeaderFromApiContext ();
    SetFspInfoHeader (FspInfoHeader);
    MaxLogicProcessors = 1;

    FspsUpd = (FSPS_UPD *) GetFspApiParameter ();
    if (FspsUpd == NULL) {
      //
      // Use the UpdRegion as default
      //
      FspsUpd = (FSPS_UPD *) (FspInfoHeader->ImageBase + FspInfoHeader->CfgRegionOffset);
    }
    SetFspUpdDataPointer(FspsUpd);
    SetFspSiliconInitUpdDataPointer (FspsUpd);

    DEBUG_CODE_BEGIN ();
      UINT32  Index;
      DEBUG ((DEBUG_INFO, "Dumping FSPS_UPD - Size: 0x%8X", sizeof(FSPS_UPD)));
      for (Index = 0; Index < sizeof (FSPS_UPD); ++Index) {
        if (Index % 0x10 == 0) {
          DEBUG ((DEBUG_INFO, "\n0x%8X:", Index));
        }
        DEBUG ((DEBUG_INFO, " 0x%02X", *(((UINT8 *)FspsUpd) + Index)));
      }
      DEBUG ((DEBUG_INFO, "\n"));
    DEBUG_CODE_END ();

    DEBUG ((DEBUG_INFO, "Updating UPDs consumed in FspSiliconInitApi...\n"));

    //
    // Locate Policy init PPI to install default silicon policy
    //
    Status = PeiServicesLocatePpi (
               &gSiDefaultPolicyInitPpiGuid,
               0,
               NULL,
               (VOID **) &PeiSiDefaultPolicyInitPpi
               );
    ASSERT_EFI_ERROR (Status);
    if (PeiSiDefaultPolicyInitPpi != NULL) {
      Status = PeiSiDefaultPolicyInitPpi->PeiPolicyInit ();
      ASSERT_EFI_ERROR (Status);
      if (Status == EFI_SUCCESS) {
        Status = PeiServicesLocatePpi (
                   &gSiPolicyPpiGuid,
                   0,
                   NULL,
                   (VOID **) &SiPolicyPpi
                   );
        ASSERT_EFI_ERROR (Status);
        if ((Status == EFI_SUCCESS) && (SiPolicyPpi != NULL)) {
          FspUpdatePeiPchPolicy (SiPolicyPpi, FspsUpd);
          FspUpdatePeiCpuPolicy (SiPolicyPpi, FspsUpd);
          //
          // Update Security Policy before install CpuPolicyPpi
          //
          FspUpdatePeiSecurityPolicy (SiPolicyPpi, FspsUpd);
          FspUpdatePeiMePolicy (SiPolicyPpi, FspsUpd);
          FspUpdatePeiSaPolicy (SiPolicyPpi, FspsUpd);
#if FixedPcdGetBool(PcdAmtEnable) == 1
          FspUpdatePeiAmtPolicy (SiPolicyPpi, FspsUpd);
#endif
          FspUpdatePeiSiPolicy (SiPolicyPpi, FspsUpd);
        }
      }
    }

    //
    // If FSP UPD SkipMpInit is enabled, PcdCpuMaxLogicalProcessorNumber is to 1. When set to 1, driver CpuMpPei doesn't start APs.
    //

    if (FspsUpd->FspsConfig.SkipMpInit) {
      PcdSet32S (PcdCpuMaxLogicalProcessorNumber, MaxLogicProcessors);
    } else {
      ///
      /// Set PcdCpuMaxLogicalProcessorNumber to max number of logical processors enabled
      /// Read MSR_CORE_THREAD_COUNT (0x35) to check the total active Threads
      ///
      MaxLogicProcessors = (UINT32) (AsmReadMsr64 (MSR_CORE_THREAD_COUNT) & B_MSR_CORE_THREAD_COUNT_THREADCOUNT_MASK);
      DEBUG ((DEBUG_INFO, "MaxLogicProcessors = %d\n", MaxLogicProcessors));
      PcdSet32S (PcdCpuMaxLogicalProcessorNumber, MaxLogicProcessors);
    }

    //
    // Install an instance of SecPlatformInformation2 with BIST data
    //
    if (FspsUpd->FspsConfig.CpuBistData) {
      Status = PeiServicesInstallPpi (&mFspPeiSecPlatformInformation2);
      ASSERT_EFI_ERROR (Status);
    }

    //
    // Wrapper can use CpuMpPpi to transfer PPI to FSP, we use it to install MP service. (optional)
    // Otherwise, CpuMpPei will be dispatched when gPeiReadyToInstallMpPpiGuid is installed.
    //
    if (FspsUpd->FspsConfig.CpuMpPpi) {
      PpiDescriptor = AllocatePool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
      if (PpiDescriptor != NULL) {
        PpiDescriptor->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
        PpiDescriptor->Ppi   = (VOID *) FspsUpd->FspsConfig.CpuMpPpi;
        PpiDescriptor->Guid  = &gEfiPeiMpServicesPpiGuid;
        Status = PeiServicesInstallPpi (PpiDescriptor);
        if (FspsUpd->FspsConfig.CpuMpHob) {
          //
          // Create cpu mp handoff HOB for mp library.
          //
          CpuMpHob = (UINT64)FspsUpd->FspsConfig.CpuMpHob;
          BuildGuidDataHob (
            &gCpuInitMpLibHobGuid,
            (VOID *) &CpuMpHob,
            sizeof (UINT64)
            );
        }
      }
    } else {
      Status = PeiServicesInstallPpi (&mFspReadyToInstallMp);
      ASSERT_EFI_ERROR (Status);
    }

    Status = PeiServicesGetBootMode (&BootMode);
    ASSERT_EFI_ERROR (Status);

    if (BootMode == BOOT_ON_S3_RESUME) {
      Status = PeiServicesNotifyPpi (mOnPciEnumerationCompleteNotifyList);
      ASSERT_EFI_ERROR (Status);
    }

    //
    // In FSP API mode, no policy update from boot loader so FSP should install
    // PolicyReady PPI to trigger silicon initialization OnPolicy callbacks.
    // However, MpService PPI is required by post memory silicon initialization so
    // register a callback for MpService PPI to make sure it is ready.
    //
    Status = PeiServicesNotifyPpi (mFspInitMpServicePpiCallbackNotifyList);
    ASSERT_EFI_ERROR (Status);
  } else {
    //
    // If gEfiPeiMpServicesPpiGuid is not installed in bootloader, install it in FSP.
    //
    Status = PeiServicesLocatePpi (
               &gEfiPeiMpServicesPpiGuid,
               0,
               NULL,
               (VOID **)&CpuMpPpi
               );
    if (EFI_ERROR (Status)) {
      Status = PeiServicesInstallPpi (&mFspReadyToInstallMp);
      ASSERT_EFI_ERROR (Status);
    }
  }

  //
  // Installs the Report Status Code PPI
  //
  InstallMonoStatusCode (FileHandle, PeiServices);

  DEBUG ((DEBUG_INFO, "SI PEI Policy Initialization Done in Post-Memory\n"));

  return Status;
}

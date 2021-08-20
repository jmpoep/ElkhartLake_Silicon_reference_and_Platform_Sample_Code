/** @file
  This file is SampleCode for Intel PEI Platform Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2020 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include "PeiPolicyInit.h"
#include <Ppi/PeiPreMemSiDefaultPolicy.h>

/**
  Initialize Intel PEI Platform Policy

  @param[in]  FirmwareConfiguration  It uses to skip specific policy init that depends
                                     on the 'FirmwareConfiguration' varaible.
**/
VOID
EFIAPI
PeiPolicyInitPreMem (
  IN UINT8                     FirmwareConfiguration
  )
{
  EFI_STATUS                   Status;
  SI_PREMEM_POLICY_PPI         *SiPreMemPolicyPpi;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  UINTN                        *SourceData;
  FSP_INFO_HEADER              *FspmHeaderPtr;
  FSPM_UPD_COMMON              *FspmUpdDataPtr;
#else
  PEI_PREMEM_SI_DEFAULT_POLICY_INIT_PPI *PeiPreMemSiDefaultPolicyInitPpi;
#endif

  Status = EFI_SUCCESS;
  SiPreMemPolicyPpi = NULL;

  DEBUG ((DEBUG_INFO, "Silicon PEI Policy Initialization Start in Pre-Memory...\n"));

#if FixedPcdGet8(PcdFspModeSelection) == 1
  //
  // Copy default FSP-M UPD data from Flash
  //
  FspmHeaderPtr = (FSP_INFO_HEADER *) FspFindFspHeader (PcdGet32 (PcdFspmBaseAddress));
  if (FspmHeaderPtr == NULL){
    return;
  }
  DEBUG ((DEBUG_INFO, "FspmHeaderPtr - 0x%x\n", FspmHeaderPtr));
  ASSERT (FspmHeaderPtr != NULL);

  FspmUpdDataPtr = (FSPM_UPD_COMMON *) AllocateZeroPool ((UINTN)FspmHeaderPtr->CfgRegionSize);
  ASSERT (FspmUpdDataPtr != NULL);
  SourceData = (UINTN *) ((UINTN)FspmHeaderPtr->ImageBase + (UINTN)FspmHeaderPtr->CfgRegionOffset);
  CopyMem (FspmUpdDataPtr, SourceData, (UINTN)FspmHeaderPtr->CfgRegionSize);

  PcdSet32S (PcdFspmUpdDataAddress, (UINT32) FspmUpdDataPtr);
  //
  // Call SiCreatePreMemConfigBlocks to initialize platform policy structure
  // and get all intel default policy settings.
  //
  Status = SiCreatePreMemConfigBlocks (&SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);
#else
  //
  // Install SiPreMemPolicyPpi.
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
    }
  }
#endif
  if (SiPreMemPolicyPpi == NULL) {
    DEBUG ((DEBUG_ERROR, "Fail to create default policy!\n"));
    return;
  }

  //
  // Update policy by board configuration
  //
  UpdatePeiPchPolicyBoardConfigPreMem ();
  UpdatePeiMePolicyBoardConfigPreMem ();
  UpdatePeiSaPolicyBoardConfigPreMem ();
  UpdatePeiCpuPolicyBoardConfigPreMem ();

  if (FirmwareConfiguration != FwConfigDefault) {
    //
    // Update and override all platform related and customized settings below.
    //
    UpdatePeiSiPolicyPreMem ();
    UpdatePeiPchPolicyPreMem ();
    UpdatePeiMePolicyPreMem ();
    UpdatePeiSaPolicyPreMem ();
    UpdatePeiCpuPolicyPreMem ();
    if ((FirmwareConfiguration >= FwConfigTest) && (FirmwareConfiguration < FwConfigMax)) {
      // Update Debug Policies
      UpdatePeiPchPolicyDebugPreMem ();
      UpdatePeiSaPolicyDebugPreMem ();
      UpdatePeiCpuPolicyDebugPreMem ();
    }

  }

  //
  // To install PolicyReady PPI after PolicyUpdate completed.
  //
  Status = SiPreMemInstallPolicyReadyPpi ();
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "Silicon PEI Policy Initialization Done in Pre-Memory\n"));
}

/**
  Reinstalls Intel PEI Platform Policies

  @retval    EFI_SUCCESS    All platform policies were reinstalled successfully.
  @retval    EFI_NOT_FOUND  An expected Intel platform policy could not be found.
**/
EFI_STATUS
EFIAPI
PeiPolicyReinstall (
  VOID
  )
{
  EFI_STATUS              Status;
  EFI_PEI_PPI_DESCRIPTOR  *OldSiPolicyPreMemPpiDesc;
  EFI_PEI_PPI_DESCRIPTOR  *NewSiPolicyPreMemPpiDesc;
  SI_PREMEM_POLICY_PPI    *SiPreMemPolicyPpi;

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             &OldSiPolicyPreMemPpiDesc,
             (VOID **) &SiPreMemPolicyPpi
             );

  if (Status == EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "Reinstalling SiPreMemPolicyPpi...\n"));
    NewSiPolicyPreMemPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateCopyPool (sizeof (EFI_PEI_PPI_DESCRIPTOR), OldSiPolicyPreMemPpiDesc);
    if (NewSiPolicyPreMemPpiDesc == NULL) {
      DEBUG ((DEBUG_ERROR, "Not enough resources to allocate the new SiPreMemPolicy descriptor buffer!\n"));
      return EFI_OUT_OF_RESOURCES;
    }
    NewSiPolicyPreMemPpiDesc->Guid = &gSiPreMemPolicyPpiGuid;
    Status = PeiServicesReInstallPpi (
               OldSiPolicyPreMemPpiDesc,
               NewSiPolicyPreMemPpiDesc
               );
  }

  return Status;
}

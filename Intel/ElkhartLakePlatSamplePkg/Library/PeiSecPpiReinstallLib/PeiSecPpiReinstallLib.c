/** @file
  Reinstalls PPIs installed during the SEC phase.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include <Base.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/SecPpiReinstallLib.h>

#include "SecPpiReinstall.h"

GLOBAL_REMOVE_IF_UNREFERENCED EFI_SEC_PLATFORM_INFORMATION_PPI  mSecPlatformInformationPostMemoryPpi = {
                                                                  SecPlatformInformationPostMemory
                                                                  };

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_TEMPORARY_RAM_DONE_PPI mSecTemporaryRamDonePostMemoryPpi = {
                                                               SecTemporaryRamDonePostMemory
                                                               };

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_PPI_DESCRIPTOR mSecPlatformInformationPostMemoryDescriptor = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiSecPlatformInformationPpiGuid,
  &mSecPlatformInformationPostMemoryPpi
  };

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PEI_PPI_DESCRIPTOR mSecTemporaryRamDonePostMemoryDescriptor = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiTemporaryRamDonePpiGuid,
  &mSecTemporaryRamDonePostMemoryPpi
  };

/**
  Disables the use of Temporary RAM.

  If present, this service is invoked by the PEI Foundation after
  the EFI_PEI_PERMANANT_MEMORY_INSTALLED_PPI is installed.

  @retval EFI_SUCCESS           Use of Temporary RAM was disabled.
  @retval EFI_INVALID_PARAMETER Temporary RAM could not be disabled.

**/
EFI_STATUS
EFIAPI
SecTemporaryRamDonePostMemory (
  VOID
  )
{
  //
  // Temporary RAM is already done in post-memory
  // install a stub function that is located in permanent memory
  //
  return EFI_SUCCESS;
}

/**
  This interface conveys state information out of the Security (SEC) phase into PEI.

  @param[in]     PeiServices               Pointer to the PEI Services Table.
  @param[in,out] StructureSize             Pointer to the variable describing size of the input buffer.
  @param[out]    PlatformInformationRecord Pointer to the EFI_SEC_PLATFORM_INFORMATION_RECORD.

  @retval EFI_SUCCESS           The data was successfully returned.
  @retval EFI_BUFFER_TOO_SMALL  The buffer was too small.

**/
EFI_STATUS
EFIAPI
SecPlatformInformationPostMemory (
  IN CONST EFI_PEI_SERVICES                     **PeiServices,
  IN OUT   UINT64                               *StructureSize,
     OUT   EFI_SEC_PLATFORM_INFORMATION_RECORD  *PlatformInformationRecord
  )
{
  SEC_PLATFORM_INFORMATION_CONTEXT_HOB  *SecPlatformInformationContexHob;

  if (StructureSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  SecPlatformInformationContexHob = GetFirstGuidHob (&gSecPlatformInformationHobGuid);
  if (SecPlatformInformationContexHob == NULL) {
    return EFI_NOT_FOUND;
  }

  if (*StructureSize < SecPlatformInformationContexHob->Context.StructureSize) {
    *StructureSize = SecPlatformInformationContexHob->Context.StructureSize;
    return EFI_BUFFER_TOO_SMALL;
  }

  if (PlatformInformationRecord == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *StructureSize             = SecPlatformInformationContexHob->Context.StructureSize;
  *PlatformInformationRecord = *(SecPlatformInformationContexHob->Context.PlatformInformationRecord);

  return EFI_SUCCESS;
}

/**
  Reinstalls PPIs whose PPI descriptors reside within SEC modules.

  This function should only be called after permanent memory is initialized.

  @retval EFI_SUCCESS       The SEC PPIs were reinstalled successfully.
  @retval Others            An error occurred while reinstalling the SEC PPIs.

**/
EFI_STATUS
EFIAPI
ReinstallSecCorePpis (
  VOID
  )
{
  EFI_STATUS                            Status;
  EFI_PEI_PPI_DESCRIPTOR                *PeiPpiDescriptor;
  VOID                                  *PeiPpi;
  SEC_PLATFORM_INFORMATION_CONTEXT_HOB  *SecPlatformInformationContextHob;
  EFI_SEC_PLATFORM_INFORMATION_RECORD   *SecPlatformInformationPtr;
  UINT64                                SecStructureSize;

  SecPlatformInformationPtr = NULL;
  SecStructureSize          = 0;

  DEBUG ((DEBUG_INFO, "ReinstallSecCorePpis () - Start\n"));

  Status = PeiServicesLocatePpi (
             &gEfiTemporaryRamDonePpiGuid,
             0,
             &PeiPpiDescriptor,
             (VOID **) &PeiPpi
             );
  DEBUG ((DEBUG_INFO, "Locate gEfiTemporaryRamDonePpiGuid Status: %r\n",Status));
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Reinstalling EfiTemporaryRamDonePpi\n"));
    Status = PeiServicesReInstallPpi (
               PeiPpiDescriptor,
               &mSecTemporaryRamDonePostMemoryDescriptor
               );
    ASSERT_EFI_ERROR (Status);
  }

  Status = PeiServicesLocatePpi (
             &gEfiSecPlatformInformationPpiGuid,
             0,
             &PeiPpiDescriptor,
             (VOID **) &PeiPpi
             );
  DEBUG ((DEBUG_INFO, "Locate gEfiSecPlatformInformationPpiGuid Status: %r\n",Status));
  if (!EFI_ERROR (Status)) {
    Status = ((EFI_SEC_PLATFORM_INFORMATION_PPI *) PeiPpi)->PlatformInformation (
                                                              GetPeiServicesTablePointer (),
                                                              &SecStructureSize,
                                                              SecPlatformInformationPtr
                                                              );
    ASSERT (Status == EFI_BUFFER_TOO_SMALL);
    if (Status != EFI_BUFFER_TOO_SMALL) {
      return EFI_NOT_FOUND;
    }

    Status = PeiServicesCreateHob (
               EFI_HOB_TYPE_GUID_EXTENSION,
               sizeof (SEC_PLATFORM_INFORMATION_CONTEXT_HOB),
               (VOID **) &SecPlatformInformationContextHob
               );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "SecPlatformInformation HOB could not be created.\n"));
      return Status;
    }

    SecPlatformInformationContextHob->Header.Name = gSecPlatformInformationHobGuid;
    SecPlatformInformationContextHob->Revision    = 1;

    ZeroMem ((VOID *) &(SecPlatformInformationContextHob->Context), sizeof (SEC_PLATFORM_INFORMATION_CONTEXT));
    SecPlatformInformationContextHob->Context.PlatformInformationRecord = AllocatePool ((UINTN) SecStructureSize);
    ASSERT (SecPlatformInformationContextHob->Context.PlatformInformationRecord != NULL);
    if (SecPlatformInformationContextHob->Context.PlatformInformationRecord == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    SecPlatformInformationContextHob->Context.StructureSize = SecStructureSize;

    Status = ((EFI_SEC_PLATFORM_INFORMATION_PPI *) PeiPpi)->PlatformInformation (
                                                              GetPeiServicesTablePointer (),
                                                              &(SecPlatformInformationContextHob->Context.StructureSize),
                                                              SecPlatformInformationContextHob->Context.PlatformInformationRecord
                                                              );
    ASSERT_EFI_ERROR (Status);
    if (!EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "Reinstalling the SecPlatformInformationPpi\n"));
      Status = PeiServicesReInstallPpi (
                 PeiPpiDescriptor,
                 &mSecPlatformInformationPostMemoryDescriptor
                 );
      ASSERT_EFI_ERROR (Status);
    }
  }

  DEBUG ((DEBUG_INFO, "ReinstallSecCorePpis () - End\n"));

  return EFI_SUCCESS;
}

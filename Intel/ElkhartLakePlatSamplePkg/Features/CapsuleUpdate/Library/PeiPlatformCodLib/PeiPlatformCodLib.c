/** @file
  Capsule on Disk library implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include <Library/PeiServicesLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Ppi/DeviceRecoveryModule.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/PrintLib.h>
#include <Ppi/CapsuleOnDiskPpi.h>
#include <Guid/SysFwUpdateProgress.h>

#define MAX_CAPSULE_ON_DISK_FILE_INDEX 63

EFI_STATUS
EFIAPI
PlatformGetCapsuleFromDisk (
  IN EFI_PEI_SERVICES            **PeiServices,
  IN PEI_CAPSULE_ON_DISK_PPI *This
  );

/**
  A dummy function to serve GetCapsuleFromDisk PPI and indicate that a capsule has been loaded from disk.

  @param  PeiServices   General-purpose services that are available to every PEIM.
  @param  This          Indicates the PEI_CAPSULE_ON_DISK_PPI instance.

  @retval EFI_SUCCESS        The capsule was loaded correctly.

**/
EFI_STATUS
EFIAPI
DummyPlatformGetCapsuleFromDisk (
  IN EFI_PEI_SERVICES            **PeiServices,
  IN PEI_CAPSULE_ON_DISK_PPI     *This
  );

static PEI_CAPSULE_ON_DISK_PPI mCapsuleOnDiskPpi = {
  PlatformGetCapsuleFromDisk
};

static PEI_CAPSULE_ON_DISK_PPI mDummyCapsuleOnDiskPpi = {
  DummyPlatformGetCapsuleFromDisk
};

static EFI_PEI_PPI_DESCRIPTOR mCodPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiCapsuleOnDiskPpiGuid,
  &mCapsuleOnDiskPpi
};

static EFI_PEI_PPI_DESCRIPTOR mDummyCodPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiCapsuleOnDiskPpiGuid,
  &mDummyCapsuleOnDiskPpi
};

/**
  A dummy function to serve GetCapsuleFromDisk PPI and indicate that a capsule has been loaded from disk.

  @param  PeiServices   General-purpose services that are available to every PEIM.
  @param  This          Indicates the PEI_CAPSULE_ON_DISK_PPI instance.

  @retval EFI_SUCCESS        The capsule was loaded correctly.

**/
EFI_STATUS
EFIAPI
DummyPlatformGetCapsuleFromDisk (
  IN EFI_PEI_SERVICES               **PeiServices,
  PEI_CAPSULE_ON_DISK_PPI           *This
  )
{
  DEBUG ((DEBUG_INFO | DEBUG_LOAD, "Capsule image has been found. Return directly.\n"));
  return EFI_SUCCESS;
}

/**
  Get Capsule image from external storage.

  @param[in]  PeiServices  General purpose services available to every PEIM.

  @retval     Status       EFI_SUCCESS if the recovery image is successfully found.

**/
EFI_STATUS
GetCapsuleImage (
  IN EFI_PEI_SERVICES               **PeiServices
  )
{
  EFI_STATUS                             Status;
  EFI_PEI_DEVICE_RECOVERY_MODULE_PPI     *DeviceRecoveryModule;
  UINTN                                  NumberOfImageProviders;
  UINTN                                  CapsuleSize;
  EFI_GUID                               DeviceId;
  EFI_PHYSICAL_ADDRESS                   Address;
  UINTN                                  CapsuleInstance;
  UINTN                                  NumberCapsules;
  UINTN                                  FileIndex;
  UINTN                                  CodFileNameSize;
  CHAR16                                 CodFileName[30];
  VOID                                   *CapsuleBuffer;
  UINTN                                  ProcessedCapsuleCount;

  Status = EFI_SUCCESS;

  DeviceRecoveryModule    = NULL;
  NumberOfImageProviders  = 0;
  ProcessedCapsuleCount   = 0;
  NumberCapsules          = 0;
  FileIndex               = 0;

  DEBUG ((DEBUG_INFO | DEBUG_LOAD, "GetCapsuleImage Entry\n"));

  Status = PeiServicesLocatePpi (
             &gEfiPeiDeviceRecoveryModulePpiGuid,
             NumberOfImageProviders,
             NULL,
             (VOID **) &DeviceRecoveryModule
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR,"Failed to locate PeiDeviceRecoveryModulePpiGuid, Status: %r\n", Status));
    return EFI_NOT_FOUND;
  }

  StrCpyS (CodFileName, sizeof(CodFileName)/sizeof(CHAR16), L"COD.cap");
  while (TRUE) {
    if (FileIndex > 0) {
      ZeroMem (CodFileName,  sizeof (CodFileName));
      UnicodeSPrint (
        CodFileName,
        sizeof (CodFileName),
        L"COD%d.cap",
        FileIndex
        );
    }

    CodFileNameSize = StrnSizeS (CodFileName, 200);
    PcdSetPtrS (PcdRecoveryFileName, &CodFileNameSize, CodFileName);

    Status = DeviceRecoveryModule->GetNumberRecoveryCapsules (
                                     PeiServices,
                                     DeviceRecoveryModule,
                                     &NumberCapsules
                                     );

    if ((Status == EFI_NOT_FOUND) || (FileIndex >= MAX_CAPSULE_ON_DISK_FILE_INDEX)) {
      //
      // There is no COD files, quit
      //
      Status = EFI_SUCCESS;
      break;
    }

    for (CapsuleInstance = 1; CapsuleInstance <= NumberCapsules; CapsuleInstance++) {
      CapsuleSize = 0;

      Status = DeviceRecoveryModule->GetRecoveryCapsuleInfo (
                                       PeiServices,
                                       DeviceRecoveryModule,
                                       FeaturePcdGet (PcdFrameworkCompatibilitySupport) ? CapsuleInstance - 1 : CapsuleInstance,
                                       &CapsuleSize,
                                       &DeviceId
                                       );

      if (EFI_ERROR (Status)) {
        continue;
      }

      CapsuleBuffer = NULL;
      Status = PeiServicesAllocatePages (
                 EfiBootServicesCode,
                 EFI_SIZE_TO_PAGES (CapsuleSize),
                 &Address
                 );

      if (EFI_ERROR (Status)) {
        continue;
      }

      CapsuleBuffer = (UINT8*)(UINTN) Address;
      Status = DeviceRecoveryModule->LoadRecoveryCapsule (
                                       PeiServices,
                                       DeviceRecoveryModule,
                                       FeaturePcdGet (PcdFrameworkCompatibilitySupport) ? CapsuleInstance - 1 : CapsuleInstance,
                                       CapsuleBuffer
                                       );

      if (EFI_ERROR (Status)) {
        ZeroMem ((VOID*)(UINTN) Address, EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (CapsuleSize)));
        continue;
      }

      BuildCvHob ((UINTN) CapsuleBuffer, CapsuleSize);
      ProcessedCapsuleCount++;
      DEBUG ((DEBUG_INFO | DEBUG_LOAD, "Capsule File (%s) Address:(0x%08x), Size:(0x%08x)\n", CodFileName, CapsuleBuffer, CapsuleSize));
      break;
    }

    FileIndex++;

    //
    // TODO: Logic to delete capsules from disk after creating the Hob.
    //
    // Currently these capsules are deleted in DXE phase since no support to DeleteFile by
    // FatPei driver.
    //
  }

  if (ProcessedCapsuleCount > 0) {
    DEBUG ((DEBUG_INFO, "Capsule Hob installed for %u Capsules\n", ProcessedCapsuleCount));
    return EFI_SUCCESS;
  }
  return Status;
}

/**
  Get Capsule image from external storage and build a Capsule HOB to pass to DXE.

  @param[in]  PeiServices  General purpose services available to every PEIM.

  @retval     Status       EFI_SUCCESS if the capsule image is successfully found.

**/
EFI_STATUS
PlatformGetCapsuleFromDisk (
  IN EFI_PEI_SERVICES               **PeiServices,
  PEI_CAPSULE_ON_DISK_PPI           *This
  )
{
  EFI_STATUS                             Status;

  Status = GetCapsuleImage (PeiServices);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "GetCapsuleImage returns %r\n", Status));
    return Status;
  }

  //
  // Since Capsule file has been found. Reinstall CodPpiList with a dummy interface to avoid installing duplicated capsules.
  //
  Status = PeiServicesReInstallPpi (&mCodPpiList, &mDummyCodPpiList);

  return EFI_SUCCESS;
}

/**
  Provide the functionality of the Capsule on Disk Module.

  @retval  Status  EFI_SUCCESS if the interface could be successfully
                   installed
**/
EFI_STATUS
EFIAPI
InitializeCodPpis (
  VOID
  )
{
  EFI_STATUS  Status;

  Status = PeiServicesInstallPpi (&mCodPpiList);

  return Status;
}

/** @file
  Platform recovery library implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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
#include <Ppi/RecoveryModule.h>
#include <Ppi/DeviceRecoveryModule.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/BaseCryptLib.h>
#include <Guid/SysFwUpdateProgress.h>

EFI_STATUS
EFIAPI
PlatformRecoveryModule (
  IN EFI_PEI_SERVICES            **PeiServices,
  IN EFI_PEI_RECOVERY_MODULE_PPI *This
  );

/**
  A dummy function to serve LoadRecoveryCapsule PPI and indicate that a recovery capsule has been found.

  @param  PeiServices   General-purpose services that are available to every PEIM.
  @param  This          Indicates the EFI_PEI_RECOVERY_MODULE_PPI instance.

  @retval EFI_SUCCESS        The capsule was loaded correctly.

**/
EFI_STATUS
EFIAPI
DummyPlatformRecoveryModule (
  IN EFI_PEI_SERVICES            **PeiServices,
  IN EFI_PEI_RECOVERY_MODULE_PPI *This
  );

// @todo The set of PCDs for FlashFV has been changed in MinPlatform, the relevant code need to be redesign.
// @todo Needs to be updated with capsule feature implementation.
static EFI_PEI_RECOVERY_MODULE_PPI mRecoveryPpi = {
  PlatformRecoveryModule
};

static EFI_PEI_RECOVERY_MODULE_PPI mDummyRecoveryPpi = {
  DummyPlatformRecoveryModule
};

static EFI_PEI_PPI_DESCRIPTOR mRecoveryPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiRecoveryModulePpiGuid,
  &mRecoveryPpi
};

static EFI_PEI_PPI_DESCRIPTOR mDummyRecoveryPpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiRecoveryModulePpiGuid,
  &mDummyRecoveryPpi
};

/**
  Dump raw data.

  @param[in]  Data  raw data
  @param[in]  Size  raw data size

**/
VOID
InternalDumpData (
  IN UINT8   *Data8,
  IN UINTN   DataSize
  )
{
  DEBUG_CODE_BEGIN();

  UINTN      Index;

  for (Index = 0; Index < DataSize; Index++) {
    if (Index % 0x10 == 0) {
      DEBUG ((DEBUG_INFO, "\n%08X:", Index));
    }
    DEBUG ((DEBUG_INFO, " %02X", *Data8++));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG_CODE_END();
}

/**
  Calculate SHA256 Hash

  @param[in]  Data   data
  @param[in]  Size   data size
  @param[out] Digest SHA256 digest

**/
VOID
CreateSha256Hash (
  IN  UINT8     *Data,
  IN  UINTN     Size,
  OUT UINT8     *Digest
  )
{
  UINTN       CtxSize;
  VOID        *HashCtx;

  CtxSize = Sha256GetContextSize ();
  HashCtx = AllocatePool (CtxSize);
  ASSERT (HashCtx != NULL);
  Sha256Init (HashCtx);
  Sha256Update (HashCtx, Data, Size);
  Sha256Final (HashCtx, Digest);

  InternalDumpData (Digest, 32);

  FreePool (HashCtx);
}

/**
  Get recovery image from external storage.

  @param[in]  PeiServices  General purpose services available to every PEIM.
  @param[out] Buffer       Point to the recovery image buffer.
  @param[out] BufferSize   Size of the recovery image buffer.

  @retval     Status       EFI_SUCCESS if the recovery image is successfully found.

**/
EFI_STATUS
GetRecoveryImage (
  IN EFI_PEI_SERVICES               **PeiServices,
  OUT VOID                          **Buffer,
  OUT UINTN                         *BufferSize
  )
{
  EFI_STATUS                             Status;
  EFI_PEI_DEVICE_RECOVERY_MODULE_PPI     *DeviceRecoveryModule;
  UINTN                                  NumberOfImageProviders;
  BOOLEAN                                ProviderAvailable;
  UINTN                                  NumberRecoveryCapsules;
  UINTN                                  RecoveryCapsuleSize;
  EFI_GUID                               DeviceId;
  EFI_PHYSICAL_ADDRESS                   Address;
  UINTN                                  CapsuleInstance;

  Status = EFI_SUCCESS;

  ProviderAvailable = TRUE;
  NumberOfImageProviders = 0;
  DeviceRecoveryModule = NULL;

  DEBUG ((DEBUG_INFO | DEBUG_LOAD, "GetRecoveryImage Entry\n"));

  //
  // Search the platform for some recovery capsule if the DXE IPL
  // discovered a recovery condition and has requested a load.
  //
  while (ProviderAvailable) {
    Status = PeiServicesLocatePpi (
               &gEfiPeiDeviceRecoveryModulePpiGuid,
               NumberOfImageProviders,
               NULL,
               (VOID **) &DeviceRecoveryModule
               );
    if (!EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO | DEBUG_LOAD, "Device Recovery PPI located\n"));
      NumberOfImageProviders++;
      Status = DeviceRecoveryModule->GetNumberRecoveryCapsules (
                                       PeiServices,
                                       DeviceRecoveryModule,
                                       &NumberRecoveryCapsules
                                       );

      DEBUG ((DEBUG_INFO | DEBUG_LOAD, "Number Of Recovery Capsules: %d\n", NumberRecoveryCapsules));

      if (NumberRecoveryCapsules != 0) {
        break;
      }
    } else {
      ProviderAvailable = FALSE;
    }
  }

  //
  // If there is an image provider, get the capsule ID
  //
  if (!ProviderAvailable) {
    return Status;
  }

  for (CapsuleInstance = 1; CapsuleInstance <= NumberRecoveryCapsules; CapsuleInstance++) {

    RecoveryCapsuleSize = 0;
    DEBUG ((DEBUG_INFO, "before GetRecoveryCapsuleInfo \n"));

    Status = DeviceRecoveryModule->GetRecoveryCapsuleInfo (
                                     PeiServices,
                                     DeviceRecoveryModule,
                                     CapsuleInstance,
                                     &RecoveryCapsuleSize,
                                     &DeviceId
                                     );

    if (EFI_ERROR (Status)) {
      continue;
    }

    DEBUG ((DEBUG_INFO | DEBUG_LOAD, "Recovery Capsule Size: %d\n", RecoveryCapsuleSize));

    *Buffer = NULL;
    Status = PeiServicesAllocatePages (
               EfiBootServicesCode,
               EFI_SIZE_TO_PAGES (RecoveryCapsuleSize),
               &Address
               );

    DEBUG ((DEBUG_INFO | DEBUG_LOAD, "AllocatePage Returns: %r\n", Status));

    if (EFI_ERROR (Status)) {
      continue;
    }

    *Buffer = (UINT8*)(UINTN) Address;
    Status = DeviceRecoveryModule->LoadRecoveryCapsule (
                                     PeiServices,
                                     DeviceRecoveryModule,
                                     CapsuleInstance,
                                     *Buffer
                                     );

    DEBUG ((DEBUG_INFO | DEBUG_LOAD, "LoadRecoveryCapsule Returns: %r\n", Status));

    if (EFI_ERROR (Status)) {
      ZeroMem ((VOID*)(UINTN) Address, EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (RecoveryCapsuleSize)));
      continue;
    }

    *BufferSize = RecoveryCapsuleSize;
    return EFI_SUCCESS;
  }

  return EFI_NOT_FOUND;
}

/**
  Get capsule image from external storage and build a Capsule HOB to pass to DXE.

  @param[in]  PeiServices  General purpose services available to every PEIM.

  @retval     Status       EFI_SUCCESS if the capsule image is successfully found.

**/
EFI_STATUS
LoadCapsuleImage (
  IN EFI_PEI_SERVICES               **PeiServices
  )
{
  EFI_STATUS                             Status;
  UINTN                                  RecoveryCapsuleSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI        *PeiReadOnlyVarPpi;
  UINTN                                  VarSize;
  UINT8                                  Sha256[SHA256_DIGEST_SIZE];
  UINT8                                  Sha256Variable[SHA256_DIGEST_SIZE];
  VOID                                   *Buffer;
  CHAR16                                 *String;
  UINTN                                  StringSize;

  Status = EFI_SUCCESS;
  PeiReadOnlyVarPpi = NULL;

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &PeiReadOnlyVarPpi
             );

  ASSERT_EFI_ERROR (Status);

  //
  // Load Capsule image digest from NV variable
  //
  VarSize = SHA256_DIGEST_SIZE;
  ZeroMem (Sha256Variable, SHA256_DIGEST_SIZE);
  Status = PeiReadOnlyVarPpi->GetVariable (
                                PeiReadOnlyVarPpi,
                                SYSFW_UPDATE_CAPSULE_DIGEST_VARIABLE_NAME,
                                &gSysFwUpdateProgressGuid,
                                NULL,
                                &VarSize,
                                Sha256Variable
                                );

  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Find Capsule digest from variable:\n"));
    InternalDumpData (Sha256Variable, VarSize);
  } else {
    DEBUG ((DEBUG_ERROR, "Cannot find Capsule digest variable.\n"));
    return EFI_NOT_FOUND;
  }

  //
  // Load Capsule image
  //
  String = SYSFW_UPDATE_CAPSULE_BACKUP_FILE_NAME;
  StringSize = StrnSizeS (String, 200);
  PcdSetPtrS (PcdRecoveryFileName, &StringSize, String);
  Status = GetRecoveryImage (PeiServices, &Buffer, &RecoveryCapsuleSize);
  DEBUG ((DEBUG_INFO, "Loading Capsule image file %s (%r)\n", (CHAR16 *)PcdGetPtr (PcdRecoveryFileName), Status));

  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (Sha256, SHA256_DIGEST_SIZE);
  DEBUG ((DEBUG_INFO, "Capsule file digest:\n"));
  CreateSha256Hash ((UINT8 *)Buffer, RecoveryCapsuleSize, Sha256);

  if (CompareMem (Sha256Variable, Sha256, SHA256_DIGEST_SIZE) != 0) {
    DEBUG ((DEBUG_ERROR, "Capsule image loaded from media is corrupted.\n"));
    return EFI_NOT_FOUND;
  }

  BuildCvHob ((UINTN) Buffer, RecoveryCapsuleSize);
  DEBUG ((DEBUG_INFO | DEBUG_LOAD, "Capsule module address(0x%08x), Size:(0x%08x)\n", Buffer, RecoveryCapsuleSize));

  //
  // Load UX Capsule image if found
  //
  String = SYSFW_UPDATE_WINDOWS_UX_CAPSULE_FILE_NAME;
  StringSize = StrnSizeS (String, 200);
  PcdSetPtrS (PcdRecoveryFileName, &StringSize, String);
  Status = GetRecoveryImage (PeiServices, &Buffer, &RecoveryCapsuleSize);
  DEBUG ((DEBUG_INFO, "Loading Windows UX Capsule image file %s (%r)\n", (CHAR16 *)PcdGetPtr (PcdRecoveryFileName), Status));
  if (!EFI_ERROR (Status)) {
    BuildCvHob ((UINTN) Buffer, RecoveryCapsuleSize);
    DEBUG ((DEBUG_INFO | DEBUG_LOAD, "Windows UX Capsule module address(0x%08x), Size:(0x%08x)\n", Buffer, RecoveryCapsuleSize));
  }

  return EFI_SUCCESS;
}

/**
  A dummy function to serve LoadRecoveryCapsule PPI and indicate that a recovery capsule has been found.

  @param  PeiServices   General-purpose services that are available to every PEIM.
  @param  This          Indicates the EFI_PEI_RECOVERY_MODULE_PPI instance.

  @retval EFI_SUCCESS        The capsule was loaded correctly.

**/
EFI_STATUS
EFIAPI
DummyPlatformRecoveryModule (
  IN EFI_PEI_SERVICES               **PeiServices,
  EFI_PEI_RECOVERY_MODULE_PPI       *This
  )
{
  DEBUG ((DEBUG_INFO | DEBUG_LOAD, "PlatformRecoveryModule image has been found. Return directly.\n"));
  return EFI_SUCCESS;
}
/**
  Loads a DXE capsule from some media into memory and updates the HOB table with the DXE firmware volume information.
  If system firmware update is in progress, also loads Capsule image from media and create Capsule HOB to continue
  the update process.
  The integrity of Capsule image is checked by message digest.

  @param  PeiServices   General-purpose services that are available to every PEIM.
  @param  This          Indicates the EFI_PEI_RECOVERY_MODULE_PPI instance.

  @retval EFI_SUCCESS        The capsule was loaded correctly.
  @retval Outhers            A recovery DXE capsule cannot be found.

**/
EFI_STATUS
EFIAPI
PlatformRecoveryModule (
  IN EFI_PEI_SERVICES               **PeiServices,
  EFI_PEI_RECOVERY_MODULE_PPI       *This
  )
{
// @todo The set of PCDs for FlashFV has been changed in MinPlatform, the relevant code need to be redesign.
// @todo Needs to be updated with capsule feature implementation.
  EFI_STATUS                             Status;
  UINTN                                  RecoveryCapsuleSize;
  VOID                                   *Buffer;
  UINTN                                  RecoveryCapsuleSize1;
  VOID                                   *Buffer1;
  UINTN                                  RecoveryCapsuleSize2;
  VOID                                   *Buffer2;
  UINTN                                  Offset = 0;
  UINTN                                  Size = 0;
  CHAR16                                 *String;
  CHAR16                                 *String1;
  CHAR16                                 *String2;
  UINTN                                  StringSize;
  EFI_HOB_GUID_TYPE                      *GuidHob;
  SYSTEM_FIRMWARE_UPDATE_PROGRESS        *UpdateProgress;
  UINT8                                  Sha256[SHA256_DIGEST_SIZE];
  EFI_PEI_FILE_HANDLE                    DigestFileHandle;
  VOID                                   *DigestFileBuffer;
  BOOLEAN                                InstallFvMainFromBootMedia;

  DEBUG ((DEBUG_INFO | DEBUG_LOAD, "PlatformRecoveryModule Entry\n"));

  Buffer  = NULL;
  Buffer1 = NULL;
  Buffer2 = NULL;
  String  = NULL;
  String1 = NULL;
  String2 = NULL;

  RecoveryCapsuleSize  = 0;
  RecoveryCapsuleSize1 = 0;
  RecoveryCapsuleSize2 = 0;

  InstallFvMainFromBootMedia = FALSE;

  //
  // Load FvMain digest on ROM
  //
  DigestFileHandle = NULL;
  DigestFileBuffer = NULL;

  //
  // Decide Recovery filename to be loaded.
  //
  GuidHob = GetFirstGuidHob (&gSysFwUpdateProgressGuid);
  if (GuidHob != NULL) {
    UpdateProgress = (SYSTEM_FIRMWARE_UPDATE_PROGRESS *) GET_GUID_HOB_DATA (GuidHob);
    ASSERT (UpdateProgress->Component < UpdatingTypeMax);

    if (UpdateProgress->Component == UpdatingBios) {
      Status = PeiServicesFfsFindFileByName (&gObbSha256HashFileGuid, (EFI_PEI_FV_HANDLE) FixedPcdGet32 (PcdFlashFvPreMemoryBase), &DigestFileHandle);
      if (!EFI_ERROR (Status)) {
        //
        // Search RAW section.
        //
        Status = PeiServicesFfsFindSectionData (EFI_SECTION_RAW, DigestFileHandle, &DigestFileBuffer);
        if (!EFI_ERROR (Status)) {
          DEBUG ((DEBUG_INFO, "Find FvMain digest on ROM:\n"));
          InternalDumpData (DigestFileBuffer, SHA256_DIGEST_SIZE);
        }
      }

      if (DigestFileBuffer == NULL) {
        DEBUG ((DEBUG_ERROR, "Failed to located FvMain digest file on ROM\n"));
        return EFI_NOT_FOUND;
      }

      //
      // BIOS update is in progress, load backup FvMain from storage accordingly
      //
      if (UpdateProgress->Progress < BiosIbb) {
        String = SYSFW_UPDATE_CURRENT_FVADV_BACKUP_FILE_NAME;
        String1 = SYSFW_UPDATE_CURRENT_FVUEFI_BACKUP_FILE_NAME;
        String2 = SYSFW_UPDATE_CURRENT_FVOS_BACKUP_FILE_NAME;
      } else {
        String = SYSFW_UPDATE_NEW_FVADV_BACKUP_FILE_NAME;
        String1 = SYSFW_UPDATE_NEW_FVUEFI_BACKUP_FILE_NAME;
        String2 = SYSFW_UPDATE_NEW_FVOS_BACKUP_FILE_NAME;
      }
    } else {
      //
      // Update of components other than BIOS is in progress,
      // BIOS region is not supposed to be currupted.
      //
      InstallFvMainFromBootMedia = TRUE;
    }
  } else {
    Status = PeiServicesFfsFindFileByName (&gObbRSha256HashFileGuid, (EFI_PEI_FV_HANDLE) FixedPcdGet32 (PcdFlashFvPreMemoryBase), &DigestFileHandle);
    if (!EFI_ERROR (Status)) {
      //
      // Search RAW section.
      //
      Status = PeiServicesFfsFindSectionData (EFI_SECTION_RAW, DigestFileHandle, &DigestFileBuffer);
      if (!EFI_ERROR (Status)) {
        DEBUG ((DEBUG_INFO, "Find OBB digest on ROM:\n"));
        InternalDumpData (DigestFileBuffer, SHA256_DIGEST_SIZE);
      }
    }

    if (DigestFileBuffer == NULL) {
      DEBUG ((DEBUG_ERROR, "Failed to located Obb digest file on ROM\n"));
      return EFI_NOT_FOUND;
    }

    String = SYSBIOS_UPDATE_CAPSULE_BACKUP_FILE_NAMEN1;
    Offset = FixedPcdGet32 (PcdFlashFvAdvancedOffset);
    Size = FixedPcdGet32 (PcdFlashFvAdvancedSize);
  }

  if (InstallFvMainFromBootMedia) {
    //
    // Install FV info of FvMain on ROM
    //
    Buffer = (VOID *)(UINTN) FixedPcdGet32 (PcdFlashFvAdvancedBase);
    RecoveryCapsuleSize = FixedPcdGet32 (PcdFlashFvAdvancedSize);
  } else {
    //
    // Load FvMain module from external storage media
    //
    StringSize = StrnSizeS (String, 200);
    PcdSetPtrS (PcdRecoveryFileName, &StringSize, String);
    Status = GetRecoveryImage (PeiServices, &Buffer, &RecoveryCapsuleSize);
    DEBUG ((DEBUG_INFO, "Loading FvAdvanced recovery file %s (%r)\n", (CHAR16 *)PcdGetPtr (PcdRecoveryFileName), Status));
    if (EFI_ERROR (Status)) {
      return Status;
    }
    if (String1 != NULL) {
      StringSize = StrnSizeS (String1, 200);
      PcdSetPtrS (PcdRecoveryFileName, &StringSize, String1);
      Status = GetRecoveryImage (PeiServices, &Buffer1, &RecoveryCapsuleSize1);
      DEBUG ((DEBUG_INFO, "Loading FvUefiBoot recovery file %s (%r)\n", (CHAR16 *)PcdGetPtr (PcdRecoveryFileName), Status));
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
    if (String2 != NULL) {
      StringSize = StrnSizeS (String2, 200);
      PcdSetPtrS (PcdRecoveryFileName, &StringSize, String2);
      Status = GetRecoveryImage (PeiServices, &Buffer2, &RecoveryCapsuleSize2);
      DEBUG ((DEBUG_INFO, "Loading FvOsBoot recovery file %s (%r)\n", (CHAR16 *)PcdGetPtr (PcdRecoveryFileName), Status));
      if (EFI_ERROR (Status)) {
        return Status;
      }
    }
  }

  //
  // Calculate message digest of the FvMain module from media
  //
  ZeroMem (Sha256, SHA256_DIGEST_SIZE);
  DEBUG ((DEBUG_INFO, "FvMain file digest:\n"));
  CreateSha256Hash ((UINT8 *) Buffer, RecoveryCapsuleSize, Sha256);

  //
  // Check the integrity of FvMain module
  //
  if (CompareMem (DigestFileBuffer, Sha256, SHA256_DIGEST_SIZE) != 0) {
    DEBUG ((DEBUG_ERROR, "FvMain loaded from media is corrupted.\n"));
    return EFI_NOT_FOUND;
  }

  DEBUG ((DEBUG_INFO | DEBUG_LOAD, "PlatformRecoveryModule: FoundFvMain and install fv info ppi. \n"));

  PeiServicesInstallFvInfo2Ppi (
    &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN)Buffer)->FileSystemGuid),
    (VOID *) ((UINTN) Buffer + Offset),
    (Offset == 0) ? RecoveryCapsuleSize : Size,
    NULL,
    NULL,
    0
    );

  if (Buffer1 != NULL) {
    PeiServicesInstallFvInfo2Ppi (
      &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN)Buffer)->FileSystemGuid),
      (VOID *) ((UINTN) Buffer1 + Offset),
      (Offset == 0) ? RecoveryCapsuleSize1 : Size,
      NULL,
      NULL,
      0
      );
  }

  if (Buffer2 != NULL) {
    PeiServicesInstallFvInfo2Ppi (
      &(((EFI_FIRMWARE_VOLUME_HEADER *) (UINTN)Buffer)->FileSystemGuid),
      (VOID *) ((UINTN) Buffer2 + Offset),
      (Offset == 0) ? RecoveryCapsuleSize2 : Size,
      NULL,
      NULL,
      0
      );
  }

  DEBUG ((DEBUG_INFO | DEBUG_LOAD, "FoundFvMain address(0x%08x), Size:(0x%08x)\n", Buffer, RecoveryCapsuleSize));

  Status = LoadCapsuleImage (PeiServices);
  if (Status == EFI_SUCCESS) {
    //
    // Since recovery file has been found. Reinstall RecoveryPpi with a dummy interface to avoid installing duplicated capsules.
    //
    Status = PeiServicesReInstallPpi (&mRecoveryPpiList, &mDummyRecoveryPpiList);
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}

/**
  Provide the functionality of the Recovery Module.

  @retval  Status  EFI_SUCCESS if the interface could be successfully
                   installed
**/
EFI_STATUS
EFIAPI
InitializeRecovery (
  VOID
  )
{
// @todo The set of PCDs for FlashFV has been changed in MinPlatform, the relevant code need to be redesign.
// @todo Needs to be updated with capsule feature implementation.

  EFI_STATUS  Status;

  Status = PeiServicesInstallPpi (&mRecoveryPpiList);

  return Status;
}
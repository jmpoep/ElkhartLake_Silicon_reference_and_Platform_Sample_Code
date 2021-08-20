/** @file
  Implementation of Setup variable initialization in PEI.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/SetupInitLib.h>
#include <Library/UefiVariableDefaultHobLib.h>

EFI_STATUS
EFIAPI
SetupVariableCallback (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

static EFI_PEI_NOTIFY_DESCRIPTOR mSetupVariableNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMasterBootModePpiGuid,
  SetupVariableCallback
};

/**
  Callback on gEfiPeiMasterBootModePpiGuidiGuid so Setup Variables are initialized.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The MasterBootMode PPI.  Not used.

  @retval EFI_SUCCESS          - The function completed successfully.
  @retval EFI_NOT_FOUND        - The matched default data is not found on CreateDefaultVariableHob
  @retval EFI_OUT_OF_RESOURCES - No enough resource to create HOB on CreateDefaultVariableHob
  @retval Others               - An error occurred locating the UEFI variables.
**/
EFI_STATUS
EFIAPI
SetupVariableCallback (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                      Status;
  EFI_BOOT_MODE                   BootMode;
  BOOLEAN                         CreateUefiVariableDefaultHob;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  UINT32     ExtraDefaultVariableHobSpace;

  if (
    (!PcdGetBool (PcdEnableCseVariableStorage) || PcdGetBool (PcdEnableFvbVariableStorage)) &&
    !PcdGetBool (PcdNvVariableEmulationMode)
    ) {
    ExtraDefaultVariableHobSpace = 0;
  } else {
    //
    // Add 13 bytes for padding to the end of the HOB variable store
    //
    ExtraDefaultVariableHobSpace = PcdGet32 (PcdNvStorageVpdSize) + 13;
  }
#endif
  DEBUG ((DEBUG_INFO, "Preparing to initialize the Setup UEFI variable...\n"));

  CreateUefiVariableDefaultHob = FALSE;
  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    if (BootMode == BOOT_IN_RECOVERY_MODE || BootMode == BOOT_WITH_DEFAULT_SETTINGS) {
      CreateUefiVariableDefaultHob = TRUE;
      DEBUG ((DEBUG_INFO, "Creating default UEFI variable HOB due to boot mode.\n"));
    }
  }

  // @todo: Add CMOS corruption check (checksum is bad) and clear diagnostic status
  //        Hint: Need ResetBoardDefaultVariableHob () in PlatformNvRamHookLibCmos.c

  // @todo: The CMOS check and check for the Setup structures should be moved to the BootModeLib
  //        when created. The only input to this module that is used to determine whether to
  //        create the default HOB is the boot mode.
  if (!CreateUefiVariableDefaultHob && !IsSetupStructuresFound ()) {
    CreateUefiVariableDefaultHob = TRUE;
    DEBUG ((DEBUG_INFO, "Creating default UEFI variable HOB since Setup variable was not found.\n"));

  }

  if (CreateUefiVariableDefaultHob) {
    Status = CreateDefaultVariableHob (
               EFI_HII_DEFAULT_CLASS_STANDARD
#if FixedPcdGetBool(PcdBfxEnable) == 1
               , ExtraDefaultVariableHobSpace
#endif
               );
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      return Status;
    }

    // Update revision ID for the Setup variable structures
    Status = UpdateAllSetupVariableRevisions ();
    ASSERT_EFI_ERROR (Status);
  }

  if (IsSetupStructuresFound ()) {
    DEBUG ((DEBUG_INFO, "Setup structures successfully found.\n"));
#if 0
    DEBUG ((DEBUG_INFO, "Dumping Setup structures:\n"));
    Status = PrintSetupStructures ();
#endif
  } else {
    Status = EFI_NOT_FOUND;
    DEBUG ((DEBUG_ERROR, "Setup structures not found at end of Setup initialization.\n"));
  }

  return Status;
}

/**
  Entry point of this module.

  @param[in] FileHandle   Handle of the file being invoked.
  @param[in] PeiServices  Describes the list of possible PEI Services.

  @retval EFI_SUCCESS     The function completed successfully.

**/
EFI_STATUS
EFIAPI
SetupVariableEntryPoint (
  IN       EFI_PEI_FILE_HANDLE      FileHandle,
  IN CONST EFI_PEI_SERVICES         **PeiServices
  )
{
  PeiServicesNotifyPpi(&mSetupVariableNotifyList);
  return EFI_SUCCESS;
}

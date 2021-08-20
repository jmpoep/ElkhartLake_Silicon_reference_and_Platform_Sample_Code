/** @file
  This is the driver that saves AMT Mebx Config data to NVRAM.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
#include <Uefi.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Protocol/AmtSaveMebxProtocol.h>

EFI_STATUS
EFIAPI
SaveMebxConfig (
  IN  UINTN                        DataSize,
  IN  VOID                         *Data
  );

AMT_SAVE_MEBX_PROTOCOL                mAmtSaveMebx = {
  SaveMebxConfig
};

/**
  This function is used to save MEBX setting to NVRAM.

  @param[in]  DataSize           The size in bytes of the Mebx Data buffer.
  @param[in]  Data               The contents for the Mebx Data.

  @retval EFI_SUCCESS            Mebx config saved.
  @retval EFI_OUT_OF_RESOURCES   Not enough storage is available to hold the variable and its data.
  @retval EFI_DEVICE_ERROR       The variable could not be retrieved due to a hardware error.
**/
EFI_STATUS
EFIAPI
SaveMebxConfig (
  IN  UINTN                        DataSize,
  IN  VOID                         *Data
  )
{
  EFI_STATUS    Status;
  VOID          *MebxSavedData;
  UINTN         VariableSize;

  DEBUG ((DEBUG_INFO, "SaveMebxConfig enter\n"));

  VariableSize = 0;
  MebxSavedData = NULL;
  Status = gRT->GetVariable (
                  L"MeBiosExtensionSetup",
                  &gMeBiosExtensionSetupGuid,
                  NULL,
                  &VariableSize,
                  MebxSavedData
                  );
  if (Status == EFI_BUFFER_TOO_SMALL) {
    MebxSavedData = AllocateZeroPool (VariableSize);
    ASSERT (MebxSavedData != NULL);

    DEBUG ((DEBUG_INFO, "VariableSize is 0x%x\n", VariableSize));
    Status = gRT->GetVariable (
                    L"MeBiosExtensionSetup",
                    &gMeBiosExtensionSetupGuid,
                    NULL,
                    &VariableSize,
                    MebxSavedData
                    );
  }

  if ((!EFI_ERROR (Status) && ((CompareMem (&Data, MebxSavedData, VariableSize) != 0) || (VariableSize != DataSize))) ||
      (Status == EFI_NOT_FOUND)) {
    DEBUG ((DEBUG_INFO, "Update ME BIOS EXTENSION SETUP Variable.\n"));
    Status = gRT->SetVariable (
                    L"MeBiosExtensionSetup",
                    &gMeBiosExtensionSetupGuid,
                    EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                    DataSize,
                    Data
                    );
  }

  if (MebxSavedData != NULL) {
    FreePool (MebxSavedData);
  }

  DEBUG ((DEBUG_INFO, "SaveMebxConfig - %r.\n", Status));
  return Status;
}

/**
  This is the standard EFI driver entrypoint to install protocol to save MEBX data from silicon package.

  @param[in] ImageHandle         Handle for the image of this driver
  @param[in] SystemTable         Pointer to the EFI System Table

  @retval EFI_SUCCESS            The protocol interface was installed.
  @retval EFI_OUT_OF_RESOURCES   Space for a new handle could not be allocated.
  @retval EFI_INVALID_PARAMETER  Handle or Protocol is NULL.
**/
EFI_STATUS
EFIAPI
AmtSaveMebxConfigEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  EFI_STATUS        Status;

  Status = gBS->InstallProtocolInterface (
                  &ImageHandle,
                  &gAmtSaveMebxProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mAmtSaveMebx
                  );
  ASSERT_EFI_ERROR (Status);
  return Status;
}

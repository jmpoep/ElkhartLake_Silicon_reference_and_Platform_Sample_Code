/** @file
  This driver updates boot order for fast boot.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

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

@par Specification
**/

#include <Base.h>
#include <Uefi.h>
#include <Library/PcdLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Protocol/FastBootException.h>
#include <Library/UefiBootManagerLib.h>
#include <Library/PrintLib.h>
#include <Guid/GlobalVariable.h>
#include <SetupVariable.h>
#include <Library/HobLib.h>
#include <Library/DxeAsfLib.h>
#include <MeBiosPayloadHob.h>
#include <AttemptUsbFirst.h>

#define BOOT_MANAGER_USB_ENTRY L"USB Entry for Windows To Go"
#define INTERNAL_EDK_SHELL_NAME L"Internal EDK Shell"

GLOBAL_REMOVE_IF_UNREFERENCED SETUP_DATA             *mSystemConfiguration = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                 mAsfBootOptionsPresent = FALSE;

/**
  Check Fast Boot is enabled or not

  @retval TRUE                   Fast Boot is enabled
  @retval FALSE                  Fast Boot is disabled
**/
BOOLEAN
FastBootEnabled (
  VOID
  )
{
  if (mSystemConfiguration == NULL) {
    GetVariable2 (L"Setup", &gSetupVariableGuid, (VOID **) &mSystemConfiguration, NULL);
    if (mSystemConfiguration == NULL) {
      return FALSE;
    }
  }

  return mSystemConfiguration->FastBoot != 0 ;
}


/**
  Raise Fast Boot Exception with specified exception type & category

  @param[in] ExceptionType      Fast Boot Exception type
  @param[in] ExceptionCategory  Fast Boot Exception category

  @retval    EFI_SUCCESS        Fast Boot Exception successfully raised
  @retval    others             Fast Boot Exception protocol installation failed
**/
EFI_STATUS
RaiseFastBootException (
  FAST_BOOT_EXCEPTION_TYPE      ExceptionType,
  FAST_BOOT_EXCEPTION_CATEGORY  ExceptionCategory
  )
{
  FAST_BOOT_EXCEPTION_PROTOCOL  *FastBootException;
  EFI_HANDLE                    Handle;

  if (!FastBootEnabled ()) {
    return EFI_SUCCESS;
  }

  FastBootException = AllocatePool (sizeof (FAST_BOOT_EXCEPTION_PROTOCOL));
  ASSERT (FastBootException != NULL);
  if (FastBootException == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  FastBootException->FbExceptionType     = ExceptionType;
  FastBootException->FbExceptionCategory = ExceptionCategory;

  Handle = NULL;
  return gBS->InstallProtocolInterface (
                &Handle,
                &gFastBootExceptionProtocolGuid,
                EFI_NATIVE_INTERFACE,
                FastBootException
                );
}

/**
  Raise Fast Boot Exception if ASF Boot Options is available

  @param[in] Event    The Event this notify function registered to.
  @param[in] Context  Pointer to the context data registered to the Event.
**/
VOID
EFIAPI
AsfBootOptionsEventCallBack (
  EFI_EVENT Event,
  VOID      *Context
  )
{
  if (AsfIsBootOptionsPresent ()) {
    RaiseFastBootException (ExceptionType2, SpecialBoot);
    mAsfBootOptionsPresent = TRUE;
  }
}

/**
  Raise Fast Boot Exception if ME FW requests to push media table

  @param[in] Event    The Event this notify function registered to
  @param[in] Context  Pointer to the context data registered to the Event.
**/
VOID
RaiseFastBootExceptionOnMediaTableRequest (
  VOID
  )
{
  ME_BIOS_PAYLOAD_HOB   *MbpHob;

  MbpHob = NULL;

  //
  // Get Mbp Protocol
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob != NULL) {
    //
    // During FastBoot, when the BIOS detects an Indication from the ME Firmware,the BIOS shall
    // enumerate all media devices and send all asset tables to the ME Firmware.
    //
    if ((MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType != IntelMeConsumerFw)
      && (MbpHob->MeBiosPayload.HwaRequest.Available == TRUE) && (MbpHob->MeBiosPayload.HwaRequest.Data.Fields.MediaTablePush == TRUE)) {
      DEBUG((DEBUG_INFO,"Set FB ExceptionType1 for MediaTablePush\n"));
      RaiseFastBootException (ExceptionType1, SpecialBoot);
    }
  }
}

/**
  Put current boot option to the 1st option in the boot option list

  @param[in] Event    The Event this notify function registered to.
  @param[in] Context  Pointer to the context data registered to the Event.
**/
VOID
EFIAPI
FastBootUpdateBootOrder (
  EFI_EVENT Event,
  VOID      *Context
  )
{
  EFI_STATUS                          Status;
  UINT16                              *BootCurrent;
  UINT16                              *BootOrder;
  UINT16                              *NewBootOrder;
  UINTN                               Size;
  UINTN                               BootOptionCount;
  CHAR16                              OptionName[sizeof ("Boot####")];
  EFI_BOOT_MANAGER_LOAD_OPTION        BootOption;
  UINTN                               DataSize;
  ATTEMPT_USB_FIRST_RUNTIME_VARIABLE  AttemptUsbFirstRuntimeVarInfo;

  //
  // Skip updating boot order for special boot types
  //
  if (mAsfBootOptionsPresent) {
    return;
  }

  AttemptUsbFirstRuntimeVarInfo.RevisonId = 0;
  AttemptUsbFirstRuntimeVarInfo.UsbFirstEnable = 0;

  //
  // Read 'AttemptUSBFirstRuntime' variable
  //
  DataSize = sizeof (ATTEMPT_USB_FIRST_RUNTIME_VARIABLE);
  Status = gRT->GetVariable (
                  L"AttemptUSBFirstRuntime",
                  &gAttemptUsbFirstRuntimeVarInfoGuid,
                  NULL,
                  &DataSize,
                  &AttemptUsbFirstRuntimeVarInfo
                  );
  if(AttemptUsbFirstRuntimeVarInfo.UsbFirstEnable) {
    //
    // Don't update 'BootOrder' variable if 'Attempt USB First' is enabled
    //
    return;
  }

  GetEfiGlobalVariable2 (L"BootCurrent", (VOID **) &BootCurrent, NULL);
  if (BootCurrent == NULL) {
    return;
  }

  UnicodeSPrint (OptionName, sizeof (OptionName), L"Boot%04X", *BootCurrent);
  Status = EfiBootManagerVariableToLoadOption (OptionName, &BootOption);
  ASSERT_EFI_ERROR (Status);

  //
  // Skip boot order update for following cases -
  // 1) Windows To Go feature is enabled
  // 2) In fast boot mode and last boot was to EFI shell.
  //    When BIOS successfully boots to any boot option, the BIOS shall store
  //    the successful boot target at the beginning of the boot list for subsequent boots.
  //    EFI Shell is considered as EFI application and still uses boot services.
  //    Booting to shell will not trigger exit boot services which will actually trigger the
  //    boot order change for subsequent boots. It is expected that "Shell" boot option will not
  //    move to top of boot order even after successfully booting to shell in fast boot mode.
  //
  if ((StrCmp(BootOption.Description, BOOT_MANAGER_USB_ENTRY) == 0) ||
     (StrCmp(BootOption.Description, INTERNAL_EDK_SHELL_NAME) == 0)) {
       EfiBootManagerFreeLoadOption (&BootOption);
       FreePool (BootCurrent);
       return;
  }

  //
  //  Skip application type
  //
  if ((BootOption.Attributes & LOAD_OPTION_CATEGORY) != LOAD_OPTION_CATEGORY_BOOT) {
    EfiBootManagerFreeLoadOption (&BootOption);
    FreePool (BootCurrent);
    return;
  }

  GetEfiGlobalVariable2 (L"BootOrder", (VOID **) &BootOrder, &Size);
  if (BootOrder == NULL) {
    FreePool (BootCurrent);
    return;
  }

  if (*BootCurrent != BootOrder[0] ) {
    UINTN Index;
    UINTN Index2;

    BootOptionCount = Size / sizeof(UINT16);
    //
    // Check overflow error for BootOptionCount
    //
    if ((Size != 0 && BootOptionCount) / (Size != sizeof (UINT16))) {
      FreePool(BootCurrent);
      FreePool(BootOrder);
      return;
    }

    NewBootOrder = AllocatePool ((BootOptionCount + 1) * sizeof (UINT16) );
    ASSERT (NewBootOrder != NULL);
    if (NewBootOrder == NULL) {
      FreePool (BootCurrent);
      FreePool (BootOrder);
      return;
    }

    NewBootOrder[0] = *BootCurrent;
    for (Index = 0, Index2 = 1; Index2 < BootOptionCount; Index++) {
      if (BootOrder[Index] != *BootCurrent) {
        NewBootOrder[Index2++] = BootOrder[Index];
      }
    }

    Size = BootOptionCount * sizeof (UINT16);
    gRT->SetVariable (
           L"BootOrder",
           &gEfiGlobalVariableGuid,
           EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
           Size,
           NewBootOrder
           );
    FreePool (NewBootOrder);
  }

  FreePool (BootCurrent);
  FreePool (BootOrder);
}



/**
  This function is the entry point of the Fast Boot Exception Handler driver.

  @param[in] ImageHandle A handle for the image that is initializing this driver
  @param[in] SystemTable  A pointer to the EFI system table

  @retval    EFI_SUCCESS  The initialization finished successfully.
**/
EFI_STATUS
EFIAPI
FastBootHandlerInitialize (
  IN EFI_HANDLE                           ImageHandle,
  IN EFI_SYSTEM_TABLE                     *SystemTable
  )
{
  EFI_STATUS  Status;
  EFI_EVENT   Event;
  VOID        *Registration;

  Status = EFI_SUCCESS;

  if (FastBootEnabled ()) {
    //
    // Register protocol notification for ASF to check whether ASF Boot Options
    // is available or not
    //
    EfiCreateProtocolNotifyEvent (
      &gAlertStandardFormatProtocolGuid,
      TPL_CALLBACK,
      AsfBootOptionsEventCallBack,
      NULL,
      &Registration
      );

    RaiseFastBootExceptionOnMediaTableRequest ();

    //
    // Create ReadyToBoot event for Fast Boot to update the current boot device
    // to the 1st in the boot list
    //
    Status = EfiCreateEventReadyToBootEx (
               TPL_CALLBACK,
               FastBootUpdateBootOrder,
               NULL,
               &Event
               );
  }

  return Status;
}

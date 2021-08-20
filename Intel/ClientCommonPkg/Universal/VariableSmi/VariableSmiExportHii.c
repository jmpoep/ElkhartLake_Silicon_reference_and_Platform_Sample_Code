//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Source that will collect the Hii database.

  Copyright (c) 2011 - 2016, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#include <Uefi.h>

#include <Protocol/HiiDatabase.h>
#include <Guid/VariableSmi.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

//
// Use same definition as EPCSutil
//
#define MAXVARNAME  128
CHAR16 mVarName[MAXVARNAME];

#define MAXVARLIST 128
EFI_VARSTORE_ID mVarList[MAXVARLIST];
UINTN           mVarListCount;

EFI_VARSTORE_ID mVarFailList[MAXVARLIST];
UINTN           mVarFailListCount;

#define MAXVARPAES 4
EFI_PHYSICAL_ADDRESS  mVariableBufferAddress;
UINTN                 mVariableBufferPages;

/**
  Return if VarStoreId is in UEFI variable.

  @param HiiPackageHeader  HII database package header pointer.
  @param VarStoreId        VarStoreId in HII database.

  @retval TRUE  VarStoreId is in UEFI variable.
  @retval FALSE VarStoreId is not in UEFI variable.
**/
BOOLEAN
IsVarStoreIdInVariable (
  IN EFI_HII_PACKAGE_HEADER   *HiiPackageHeader,
  IN EFI_VARSTORE_ID          VarStoreId
  )
{
  EFI_IFR_OP_HEADER             *IfrOpCodeHeader;
  EFI_IFR_VARSTORE              *IfrVarStore;
  EFI_IFR_VARSTORE_EFI          *IfrEfiVarStore;
  UINTN                         VariableSize;
  EFI_STATUS                    Status;
  UINT32                        Attributes;
  UINTN                         Index;

  //
  // Check cache
  //
  for (Index = 0; Index < mVarListCount; Index++) {
    if (mVarList[Index] == VarStoreId) {
      return TRUE;
    }
  }
  for (Index = 0; Index < mVarFailListCount; Index++) {
    if (mVarFailList[Index] == VarStoreId) {
      return FALSE;
    }
  }

  IfrOpCodeHeader = (EFI_IFR_OP_HEADER *) (HiiPackageHeader + 1);
  while ((UINTN) IfrOpCodeHeader < (UINTN) HiiPackageHeader + HiiPackageHeader->Length) {

    switch (IfrOpCodeHeader->OpCode) {
    case EFI_IFR_VARSTORE_OP:
      IfrVarStore = (EFI_IFR_VARSTORE *) IfrOpCodeHeader;
      if (IfrVarStore->VarStoreId == VarStoreId) {
        //
        // Find it
        //
        SetMem (mVarName, sizeof (mVarName), 0);
        for (Index = 0; (Index < MAXVARNAME - 1) && (IfrVarStore->Name[Index] != 0); Index++) {
          mVarName[Index] = IfrVarStore->Name[Index];
        }
        VariableSize = EFI_PAGES_TO_SIZE (mVariableBufferPages);
        Status = gRT->GetVariable (
          mVarName,
          (EFI_GUID *) (VOID *) &IfrVarStore->Guid,
          &Attributes,
          &VariableSize,
          (VOID *) (UINTN) mVariableBufferAddress
          );
        if (Status == EFI_BUFFER_TOO_SMALL) {
          gBS->FreePages (mVariableBufferAddress, mVariableBufferPages);
          mVariableBufferPages = EFI_SIZE_TO_PAGES (VariableSize);
          Status = gBS->AllocatePages (AllocateAnyPages, EfiBootServicesData, mVariableBufferPages, &mVariableBufferAddress);
          ASSERT_EFI_ERROR (Status);

          VariableSize = EFI_PAGES_TO_SIZE (mVariableBufferPages);
          Status = gRT->GetVariable (
            mVarName,
            (EFI_GUID *) (VOID *) &IfrVarStore->Guid,
            &Attributes,
            &VariableSize,
            (VOID *) (UINTN) mVariableBufferAddress
            );
        }
        if (Status == EFI_SUCCESS) {
          if ((Attributes & EFI_VARIABLE_NON_VOLATILE) != 0) {
            //
            // Save to cache
            //
            if (mVarListCount < MAXVARLIST) {
              mVarList[mVarListCount] = VarStoreId;
              mVarListCount++;
            }
            return TRUE;
          }
        }

        //
        // Save to cache
        //
        if (mVarFailListCount < MAXVARLIST) {
          mVarFailList[mVarFailListCount] = VarStoreId;
          mVarFailListCount++;
        }
        return FALSE;
      }
      break;
    case EFI_IFR_VARSTORE_EFI_OP:
      IfrEfiVarStore = (EFI_IFR_VARSTORE_EFI *) IfrOpCodeHeader;
      if (IfrEfiVarStore->Header.Length >= sizeof (EFI_IFR_VARSTORE_EFI) &&
          IfrEfiVarStore->VarStoreId == VarStoreId) {
        //
        // EFI VarStore are saved to EFI Variable.
        //
        if ((IfrEfiVarStore->Attributes & EFI_VARIABLE_NON_VOLATILE) != 0) {
          //
          // Save to cache
          //
          if (mVarListCount < MAXVARLIST) {
            mVarList[mVarListCount] = VarStoreId;
            mVarListCount++;
          }
          return TRUE;
        }

        //
        // Save to cache
        //
        if (mVarFailListCount < MAXVARLIST) {
          mVarFailList[mVarFailListCount] = VarStoreId;
          mVarFailListCount++;
        }
        return FALSE;
      }
      break;
    default:
      break;
    }
    IfrOpCodeHeader = (EFI_IFR_OP_HEADER *) ((UINTN) IfrOpCodeHeader + IfrOpCodeHeader->Length);
  }
  //
  // Not found
  //
  return FALSE;
}

/**
  Patch HII database to pass EPCS utility.

  @param TableHeader  HII database header pointer.
**/
VOID
PatchHiiDatabase (
  IN EFI_HII_PACKAGE_EXPORT_HEADER  *TableHeader
  )
{
  EFI_HII_PACKAGE_LIST_HEADER   *HiiPackageListHeader;
  EFI_HII_PACKAGE_HEADER        *HiiPackageHeader;
  EFI_IFR_OP_HEADER             *IfrOpCodeHeader;
  EFI_STATUS                    Status;

  mVariableBufferPages = MAXVARPAES;
  Status = gBS->AllocatePages (AllocateAnyPages, EfiBootServicesData, mVariableBufferPages, &mVariableBufferAddress);
  ASSERT_EFI_ERROR (Status);

  HiiPackageListHeader = (EFI_HII_PACKAGE_LIST_HEADER *) (TableHeader + 1);

  while ((UINTN) HiiPackageListHeader < (UINTN) (TableHeader + 1) + TableHeader->HiiDatabaseSize) {
    HiiPackageHeader = (EFI_HII_PACKAGE_HEADER *) (HiiPackageListHeader + 1);

    while ((UINTN) HiiPackageHeader < (UINTN) HiiPackageListHeader + HiiPackageListHeader->PackageLength - sizeof (*HiiPackageListHeader)) {

      switch (HiiPackageHeader->Type) {
      case EFI_HII_PACKAGE_FORMS:

        //
        // Init cache
        //
        mVarListCount = 0;
        mVarFailListCount = 0;

        IfrOpCodeHeader = (EFI_IFR_OP_HEADER *) (HiiPackageHeader + 1);

        while ((UINTN) IfrOpCodeHeader < (UINTN) HiiPackageHeader + HiiPackageHeader->Length) {

          switch (IfrOpCodeHeader->OpCode) {
          case EFI_IFR_ONE_OF_OP:
          case EFI_IFR_CHECKBOX_OP:
          case EFI_IFR_NUMERIC_OP:
          case EFI_IFR_ORDERED_LIST_OP:
            if ((!IsVarStoreIdInVariable (HiiPackageHeader, ((EFI_IFR_ONE_OF *) IfrOpCodeHeader)->Question.VarStoreId)) ||
                //
                // BUGBUG: Patch it to cheat EPCSutil, if it is not in non-volatile variable.
                //
                ((((EFI_IFR_ONE_OF *) IfrOpCodeHeader)->Question.Header.Prompt == 0) && (((EFI_IFR_ONE_OF *) IfrOpCodeHeader)->Question.Header.Help == 0))) {
              //
              // BUGBUG: Patch it, for meanless IFR item introduced by ECP.
              //
              IfrOpCodeHeader->OpCode = EFI_IFR_GUID_OP;
              if (IfrOpCodeHeader->Scope != 0) {
                //
                // We need remove followed opcode as well, until end of scope
                //
                IfrOpCodeHeader = (EFI_IFR_OP_HEADER *) ((UINTN) IfrOpCodeHeader + IfrOpCodeHeader->Length);
                while (IfrOpCodeHeader->OpCode != EFI_IFR_END_OP) {
                  IfrOpCodeHeader->OpCode = EFI_IFR_GUID_OP;
                  IfrOpCodeHeader = (EFI_IFR_OP_HEADER *) ((UINTN) IfrOpCodeHeader + IfrOpCodeHeader->Length);
                }
              }
            }
            break;
          default:
            break;
          }
          IfrOpCodeHeader = (EFI_IFR_OP_HEADER *) ((UINTN) IfrOpCodeHeader + IfrOpCodeHeader->Length);
        }
        break;
      default:
        break;
      }

      HiiPackageHeader = (EFI_HII_PACKAGE_HEADER *) ((UINTN) HiiPackageHeader + HiiPackageHeader->Length);
    }

    HiiPackageListHeader = (EFI_HII_PACKAGE_LIST_HEADER *) ((UINTN) HiiPackageListHeader + HiiPackageListHeader->PackageLength);
  }
}

typedef struct {
  UINT8                    OpCode;
  CHAR8                    *OpCodeStr;
} IFR_OPCODE_STRING_STRUCT;

GLOBAL_REMOVE_IF_UNREFERENCED IFR_OPCODE_STRING_STRUCT  mIfrOpCodeStringTable[] = {
  {EFI_IFR_ONE_OF_OP,       "EFI_IFR_ONE_OF_OP"},
  {EFI_IFR_CHECKBOX_OP,     "EFI_IFR_CHECKBOX_OP"},
  {EFI_IFR_NUMERIC_OP,      "EFI_IFR_NUMERIC_OP"},
  {EFI_IFR_ORDERED_LIST_OP, "EFI_IFR_ORDERED_LIST_OP"},
};


/**
  This is signaled before booting or shell.
  This function will export HII Database before OS boot.

  @param Event    Event that triggers the function.
  @param Context  Event specific Context.

**/
VOID
EFIAPI
VariableSmiExportHii (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS                     Status;
  UINTN                          BufferSize;
  VOID                           *Buffer;
  EFI_PHYSICAL_ADDRESS           BufferAddress;
  EFI_HII_DATABASE_PROTOCOL      *HiiDatabase;
  EFI_HII_PACKAGE_EXPORT_HEADER  *TableHeader;

  //
  // This routine could be called multiple times right before booting.
  //
  gBS->CloseEvent (Event);

  //
  // Locate HII protocol
  //
  Status = gBS->LocateProtocol (&gEfiHiiDatabaseProtocolGuid, NULL, (VOID **) &HiiDatabase);
  ASSERT_EFI_ERROR (Status);

  //
  // Call first time with zero buffer length.
  // Should fail with EFI_BUFFER_TOO_SMALL.
  //
  BufferSize = 0;
  Buffer = NULL;
  Status = HiiDatabase->ExportPackageLists (HiiDatabase, 0, &BufferSize, Buffer);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    //
    // Allocate buffer in ACPI NVS region to hold the HII database.
    //
    BufferAddress = SIZE_4GB - 1;
    Status = gBS->AllocatePages (
                    AllocateMaxAddress,
                    EfiACPIMemoryNVS,
                    EFI_SIZE_TO_PAGES (BufferSize + sizeof (EFI_HII_PACKAGE_EXPORT_HEADER)),
                    &BufferAddress
                    );
    ASSERT_EFI_ERROR (Status);
    Buffer = (VOID *) (UINTN) (BufferAddress + sizeof (EFI_HII_PACKAGE_EXPORT_HEADER));

    //
    // Export HII database into the buffer.
    //
    Status = HiiDatabase->ExportPackageLists (HiiDatabase, 0, &BufferSize, Buffer);
    ASSERT_EFI_ERROR (Status);

    //
    // Fill table header
    //
    TableHeader = (EFI_HII_PACKAGE_EXPORT_HEADER *) (UINTN) BufferAddress;
    CopyGuid (&TableHeader->HiiProtocolGuid, &gEfiHiiDatabaseProtocolGuid);
    TableHeader->HiiDatabaseSize = (UINT32) BufferSize;

    //
    // Update buffer pointer - save to ACPINvs
    //
    Buffer = (VOID *) (UINTN) BufferAddress;
    //
    // Add work-around for EPCSutil - remove the VarStore which is not in Variable.
    //
    PatchHiiDatabase (TableHeader);
    //
    // Create a variable that will hold the pointer to the HII Database.
    //
    DEBUG ((
      EFI_D_INFO,
      "VariableSmiExportHii(): Whole HII Database exported at ACPINvs 0x%X, 0x%X bytes\n",
      Buffer, BufferSize
      ));
    Status = gRT->SetVariable (
                    VARIABLE_SMI_HII_DATABASE_VARIABLE_NAME,
                    &gVariableSmiGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                    sizeof (Buffer),
                    &Buffer
                    );
    ASSERT_EFI_ERROR (Status);
  }
}

/**
  Initialize SmiVariableInstallInt15.

  @param ImageHandle   Pointer to the loaded image protocol for this driver
  @param SystemTable   Pointer to the EFI System Table

  @retval EFI_SUCCESS  The driver initializes correctly.

**/
EFI_STATUS
EFIAPI
VariableSmiExportHiiEntrypoint (
  IN    EFI_HANDLE                  ImageHandle,
  IN    EFI_SYSTEM_TABLE            *SystemTable
  )
{
  EFI_STATUS                        Status;
  EFI_EVENT                         ReadyToBootEvent;

  //
  // Register a callback function to export HII Database before OS boot.
  //
  Status = EfiCreateEventReadyToBootEx (
             TPL_CALLBACK,
             VariableSmiExportHii,
             NULL,
             &ReadyToBootEvent
             );
  ASSERT_EFI_ERROR (Status);
  return Status;
}

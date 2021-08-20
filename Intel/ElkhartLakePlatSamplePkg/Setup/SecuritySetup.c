/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2003 - 2017 Intel Corporation.

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


#include <SetupPrivate.h>
#include <Library/BaseMemoryLib.h>

#include <Library/PttHeciLib.h>
#include <Tcg2ConfigNvData.h>// TCG2 implementation

#include <Protocol/HeciProtocol.h>
#include "MeSetup.h"
#include <CoreBiosMsg.h>
#include <Register/PttPtpRegs.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID mTcg2ConfigFormSetGuid = TCG2_CONFIG_FORM_SET_GUID;

extern BOOLEAN   mMeReset;

/**
  Return the Tcg form handle.

  @return  Tcg form handle.

**/
EFI_HII_HANDLE
GetTcgFormHandle (
  VOID
  )
{
  EFI_STATUS                   Status;
  UINTN                        BufferSize;
  EFI_HII_PACKAGE_LIST_HEADER  *HiiPackageList;
  UINT8                        *Package;
  UINT8                        *OpCodeData;
  UINT32                       Offset;
  UINT32                       Offset2;
  UINT32                       PackageListLength;
  EFI_HII_PACKAGE_HEADER       PackageHeader;
  EFI_HII_DATABASE_PROTOCOL    *HiiDatabase;
  UINTN                        HandleBufferLength;
  EFI_HII_HANDLE               *HiiHandleBuffer;
  UINTN                        Index;
  EFI_HII_HANDLE               TcgHandle;
  EFI_GUID                     TcgFormGuid = TCG_FORM_SET_GUID;

  Status = gBS->LocateProtocol (&gEfiHiiDatabaseProtocolGuid, NULL, (VOID **) &HiiDatabase);
  ASSERT_EFI_ERROR (Status);

  HandleBufferLength = 0;
  Status = HiiDatabase->ListPackageLists (
                           HiiDatabase,
                           EFI_HII_PACKAGE_TYPE_ALL,
                           NULL,
                           &HandleBufferLength,
                           NULL
                           );
  ASSERT (Status == EFI_BUFFER_TOO_SMALL);
  HiiHandleBuffer = AllocateZeroPool (HandleBufferLength);
  if (HiiHandleBuffer == NULL) {
    return NULL;
  }

  Status = HiiDatabase->ListPackageLists (
                           HiiDatabase,
                           EFI_HII_PACKAGE_TYPE_ALL,
                           NULL,
                           &HandleBufferLength,
                           HiiHandleBuffer
                           );
  ASSERT_EFI_ERROR (Status);

  for (Index = 0; Index < HandleBufferLength / sizeof (EFI_HII_HANDLE); Index++) {
    //
    // Get HII PackageList
    //
    BufferSize = 0;
    HiiPackageList = NULL;
    Status = HiiDatabase->ExportPackageLists (HiiDatabase, HiiHandleBuffer[Index], &BufferSize, HiiPackageList);
    //
    // Handle is a invalid handle. Check if Handle is corrupted.
    //
    ASSERT (Status != EFI_NOT_FOUND);
    //
    // The return status should always be EFI_BUFFER_TOO_SMALL as input buffer's size is 0.
    //
    ASSERT (Status == EFI_BUFFER_TOO_SMALL);

    HiiPackageList = AllocatePool (BufferSize);
    ASSERT (HiiPackageList != NULL);
    if (HiiPackageList == NULL) {
      return NULL;
    }

    Status = HiiDatabase->ExportPackageLists (HiiDatabase, HiiHandleBuffer[Index], &BufferSize, HiiPackageList);
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Get Form package from this HII package List
    //
    PackageListLength = ReadUnaligned32 (&HiiPackageList->PackageLength);

    for ( Offset = sizeof (EFI_HII_PACKAGE_LIST_HEADER)
        ; Offset < PackageListLength
        ; Offset += PackageHeader.Length
        ) {
      Package = ((UINT8 *) HiiPackageList) + Offset;
      CopyMem (&PackageHeader, Package, sizeof (EFI_HII_PACKAGE_HEADER));

      if (PackageHeader.Type == EFI_HII_PACKAGE_FORMS) {
        //
        // Search FormSet Opcode in this Form Package
        //
        for ( Offset2 = sizeof (EFI_HII_PACKAGE_HEADER)
            ; Offset2 < PackageHeader.Length
            ; Offset2 += ((EFI_IFR_OP_HEADER *) OpCodeData)->Length
            ) {
          OpCodeData = Package + Offset2;

          if ((((EFI_IFR_OP_HEADER *) OpCodeData)->OpCode == EFI_IFR_FORM_SET_OP) &&
              CompareGuid ((GUID *)(VOID *)&((EFI_IFR_FORM_SET *) OpCodeData)->Guid, &TcgFormGuid)) {
          //
          // Find TCG FormSet
          //
            break;
          }
        }

        if (Offset2 < PackageHeader.Length) {
          break;
        }
      }
    }

    FreePool (HiiPackageList);

    if (Offset < PackageListLength) {
      break;
    }
  }

  if (Index < HandleBufferLength / sizeof (EFI_HII_HANDLE)) {
    TcgHandle = HiiHandleBuffer[Index];
  } else {
    TcgHandle = NULL;
  }

  FreePool (HiiHandleBuffer);

  return TcgHandle;
}

EFI_STATUS
SaveTpmDeviceSelection (
  IN UINT8                         TpmDeviceSelection
  )
{
  EFI_STATUS                       Status;
  UINTN                            Size;
  TCG2_CONFIGURATION               Tcg2Configuration;
  UINT32                           Tcg2VarAttr;
  BOOLEAN                          GlobalReset;
  BOOLEAN                          ResetRequired;
  ME_SETUP_STORAGE                 MeSetupStorage;
  UINT32                           MeSetupStorageAttr;

  ResetRequired = FALSE;
  GlobalReset = FALSE;

  Size = sizeof (TCG2_CONFIGURATION);
  Status = gRT->GetVariable(
                  TCG2_STORAGE_NAME,
                  &mTcg2ConfigFormSetGuid,
                  &Tcg2VarAttr,
                  &Size,
                  &Tcg2Configuration
                  );
  if (EFI_ERROR (Status)) {
    ZeroMem( &Tcg2Configuration, Size );
    Tcg2VarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS;
    Tcg2Configuration.TpmDevice = TPM_DEVICE_DEFAULT;

  }

  if (Tcg2Configuration.TpmDevice != TpmDeviceSelection) {
    ResetRequired = TRUE;

    if ((Tcg2Configuration.TpmDevice == TPM_DEVICE_PTT) || (TpmDeviceSelection == TPM_DEVICE_PTT)) {
      Size = sizeof (ME_SETUP_STORAGE);
      Status = gRT->GetVariable (
                      L"MeSetupStorage",
                      &gMeSetupVariableGuid,
                      &MeSetupStorageAttr,
                      &Size,
                      &MeSetupStorage
                      );
      ASSERT_EFI_ERROR (Status);

      MeSetupStorage.PttState = (BOOLEAN) TpmDeviceSelection;

      Status = gRT->SetVariable (
                      L"MeSetupStorage",
                      &gMeSetupVariableGuid,
                      MeSetupStorageAttr,
                      sizeof (ME_SETUP_STORAGE),
                      &MeSetupStorage
                      );
      ASSERT_EFI_ERROR (Status);

      GlobalReset = TRUE;
    }

    if (TpmDeviceSelection == TPM_DEVICE_PTT) {
      PttHeciSetState(TRUE);
    } else {
      PttHeciSetState(FALSE);
    }
  }

  Tcg2Configuration.TpmDevice = TpmDeviceSelection;

  Size = sizeof (TCG2_CONFIGURATION);
  Status = gRT->SetVariable (
                  TCG2_STORAGE_NAME,
                  &mTcg2ConfigFormSetGuid,
                  Tcg2VarAttr,
                  Size,
                  &Tcg2Configuration
                  );
  ASSERT_EFI_ERROR (Status);

  if (ResetRequired) {
    if (GlobalReset == TRUE) {
      mMeReset = TRUE;
    } else {
      gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  return EFI_SUCCESS;
}

/**
  Return the TrEE form handle.

  @return  TrEE form handle.

**/
EFI_HII_HANDLE
GetTcg2FormHandle(
VOID
)
{
  EFI_STATUS                   Status;
  UINTN                        BufferSize;
  EFI_HII_PACKAGE_LIST_HEADER  *HiiPackageList;
  UINT8                        *Package;
  UINT8                        *OpCodeData;
  UINT32                       Offset;
  UINT32                       Offset2;
  UINT32                       PackageListLength;
  EFI_HII_PACKAGE_HEADER       PackageHeader;
  EFI_HII_DATABASE_PROTOCOL    *HiiDatabase;
  UINTN                        HandleBufferLength;
  EFI_HII_HANDLE               *HiiHandleBuffer;
  UINTN                        Index;
  EFI_HII_HANDLE               Tcg2Handle;
  EFI_GUID                     Tcg2FormGuid = {
    0x6339d487, 0x26ba, 0x424b, { 0x9a, 0x5d, 0x68, 0x7e, 0x25, 0xd7, 0x40, 0xbc }
  };

  Status = gBS->LocateProtocol(&gEfiHiiDatabaseProtocolGuid, NULL, (VOID **) &HiiDatabase);
  ASSERT_EFI_ERROR(Status);

  DEBUG((DEBUG_INFO, "Tcg2FormGuid = %g\n", &Tcg2FormGuid));

  HandleBufferLength = 0;
  Status = HiiDatabase->ListPackageLists(
    HiiDatabase,
    EFI_HII_PACKAGE_TYPE_ALL,
    NULL,
    &HandleBufferLength,
    NULL
    );
  ASSERT(Status == EFI_BUFFER_TOO_SMALL);
  HiiHandleBuffer = AllocateZeroPool(HandleBufferLength);
  if (HiiHandleBuffer == NULL) {
    return NULL;
  }

  Status = HiiDatabase->ListPackageLists(
    HiiDatabase,
    EFI_HII_PACKAGE_TYPE_ALL,
    NULL,
    &HandleBufferLength,
    HiiHandleBuffer
    );
  ASSERT_EFI_ERROR(Status);

  for (Index = 0; Index < HandleBufferLength / sizeof (EFI_HII_HANDLE); Index++) {
    //
    // Get HII PackageList
    //
    BufferSize = 0;
    HiiPackageList = NULL;
    Status = HiiDatabase->ExportPackageLists (HiiDatabase, HiiHandleBuffer[Index], &BufferSize, HiiPackageList);
    //
    // Handle is a invalid handle. Check if Handle is corrupted.
    //
    ASSERT (Status != EFI_NOT_FOUND);
    //
    // The return status should always be EFI_BUFFER_TOO_SMALL as input buffer's size is 0.
    //
    ASSERT (Status == EFI_BUFFER_TOO_SMALL);

    HiiPackageList = AllocatePool (BufferSize);
    ASSERT (HiiPackageList != NULL);
    if (HiiPackageList == NULL) {
      return NULL;
    }

    Status = HiiDatabase->ExportPackageLists (HiiDatabase, HiiHandleBuffer[Index], &BufferSize, HiiPackageList);
    if (EFI_ERROR (Status)) {
      continue;
    }

    //
    // Get Form package from this HII package List
    //
    PackageListLength = ReadUnaligned32 (&HiiPackageList->PackageLength);

    for ( Offset = sizeof (EFI_HII_PACKAGE_LIST_HEADER)
        ; Offset < PackageListLength
        ; Offset += PackageHeader.Length
        ) {
      Package = ((UINT8 *) HiiPackageList) + Offset;
      CopyMem (&PackageHeader, Package, sizeof (EFI_HII_PACKAGE_HEADER));

      if (PackageHeader.Type == EFI_HII_PACKAGE_FORMS) {
        //
        // Search FormSet Opcode in this Form Package
        //
        for ( Offset2 = sizeof (EFI_HII_PACKAGE_HEADER)
            ; Offset2 < PackageHeader.Length
            ; Offset2 += ((EFI_IFR_OP_HEADER *) OpCodeData)->Length
            ) {
          OpCodeData = Package + Offset2;

          if ((((EFI_IFR_OP_HEADER *)OpCodeData)->OpCode == EFI_IFR_FORM_SET_OP) &&
            CompareGuid((GUID *)(VOID *)&((EFI_IFR_FORM_SET *)OpCodeData)->Guid, &Tcg2FormGuid)) {
            //
            // Find TCG FormSet
            //
            break;
          }
        }

        if (Offset2 < PackageHeader.Length) {
          break;
        }
      }
    }

    FreePool (HiiPackageList);

    if (Offset < PackageListLength) {
      break;
    }
  }

  if (Index < HandleBufferLength / sizeof(EFI_HII_HANDLE)) {
    Tcg2Handle = HiiHandleBuffer[Index];
  }
  else {
    Tcg2Handle = NULL;
  }

  FreePool(HiiHandleBuffer);

  return Tcg2Handle;
}


EFI_STATUS
EFIAPI
TpmOptionCallback (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION Action,
  IN EFI_QUESTION_ID KeyValue,
  IN UINT8 Type,
  IN EFI_IFR_TYPE_VALUE *Value,
  OUT EFI_BROWSER_ACTION_REQUEST *ActionRequest
  )
/*++

Routine Description:

  This is the function that is called to provide results data to the driver.  This data
  consists of a unique key which is used to identify what data is either being passed back
  or being asked for.

Arguments:

  KeyValue -        A unique value which is sent to the original exporting driver so that it
                    can identify the type of data to expect.  The format of the data tends to
                    vary based on the op-code that geerated the callback.

  Data -            A pointer to the data being sent to the original exporting driver.

Returns:


--*/
{
  EFI_STATUS                  Status;
  EFI_HII_HANDLE              TcgHandle;
  EFI_HII_HANDLE              Tcg2Handle;
  EFI_FORM_BROWSER2_PROTOCOL  *FormBrowser2;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    return EFI_UNSUPPORTED;
  }
  Status        = EFI_SUCCESS;

  if (Value == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  switch (KeyValue) {
  case KEY_TPM_GOTO:
    TcgHandle = GetTcgFormHandle ();
    if (TcgHandle != NULL) {
      Status = gBS->LocateProtocol (&gEfiFormBrowser2ProtocolGuid, NULL, (VOID **) &FormBrowser2);
      ASSERT_EFI_ERROR (Status);
      Status = FormBrowser2->SendForm (
                            FormBrowser2,
                            &TcgHandle,
                            1,
                            NULL,
                            0,
                            NULL,
                            NULL
                            );
    }
    break;

    case KEY_TPM2_GOTO:
      Tcg2Handle = GetTcg2FormHandle ();
      if (Tcg2Handle != NULL) {
    DEBUG((DEBUG_ERROR, "Tcg2Handle is NOT NULL, send Form"));
        Status = gBS->LocateProtocol (&gEfiFormBrowser2ProtocolGuid, NULL, (VOID **) &FormBrowser2);
        ASSERT_EFI_ERROR (Status);
        Status = FormBrowser2->SendForm (
                              FormBrowser2,
                              &Tcg2Handle,
                              1,
                              NULL,
                              0,
                              NULL,
                              NULL
                              );
      }
    DEBUG((DEBUG_ERROR, "Tcg2Handle is NULL!!!"));
      break;

    case KEY_TPM_DEVICE_SELECT:
      if (Action == EFI_BROWSER_ACTION_CHANGED) {
        SaveTpmDeviceSelection (Value->u8);
      }
      break;
  };

  return Status;
}

VOID
TpmExtractConfig (
  VOID
  )
{
  EFI_STATUS               Status;
  TCG2_CONFIGURATION       Tcg2Configuration;
  UINT32                   Tcg2Attr;
  UINTN                    Tcg2Size;
  UINT32                   TpmStsFtif;
  DEBUG ((DEBUG_INFO, "MeExtractConfig\n"));

  Tcg2Size = sizeof(Tcg2Configuration);
  Status = gRT->GetVariable (
                    TCG2_STORAGE_NAME,
                    &gTcg2ConfigFormSetGuid,
                    &Tcg2Attr,
                    &Tcg2Size,
                    &Tcg2Configuration
                    );
  if (EFI_ERROR (Status)) {
    Tcg2Configuration.TpmDevice           = TPM_DEVICE_NULL;
    DEBUG ((DEBUG_INFO, "Unable To Get Tcg2Configuration variable %r\n",Status));
    return;
  }

  if (CompareGuid(PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceNoneGuid)){
    //
    // No TPM available
    //
    Tcg2Configuration.TpmDevice           = TPM_DEVICE_NULL;
  } else if (CompareGuid(PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceTpm12Guid)) {
    Tcg2Configuration.TpmDevice = TPM_DEVICE_1_2;
  } else if (CompareGuid(PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceTpm20DtpmGuid)) {
    TpmStsFtif = MmioRead32 (R_PTT_TXT_STS_FTIF);

      if ((TpmStsFtif & V_FTIF_FTPM_PRESENT) == ((UINT32) V_FTIF_FTPM_PRESENT)) {
        DEBUG ((DEBUG_INFO, "PTT (fTPM) present\n"));
        Tcg2Configuration.TpmDevice = TPM_DEVICE_PTT;
      } else {
        DEBUG ((DEBUG_INFO, "dTPM present\n"));
        Tcg2Configuration.TpmDevice = TPM_DEVICE_2_0_DTPM;
      }
  }

   Status = gRT->SetVariable(
                    TCG2_STORAGE_NAME,
                    &gTcg2ConfigFormSetGuid,
                    Tcg2Attr,
                    sizeof(Tcg2Configuration),
                    &Tcg2Configuration
                    );
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_ERROR, "Fail to set TCG2_STORAGE_NAME\n"));
  }

}

/** @file
  FrontPage routines to handle the callbacks and browser calls

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2018 Intel Corporation.

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

#include "FrontPage.h"
#include "Language.h"
#include <Protocol/AmtWrapperProtocol.h>

#define MAX_STRING_LEN        200

EFI_GUID  mFrontPageGuid      = FRONT_PAGE_FORMSET_GUID;

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN   gConnectAllHappened = FALSE;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN     gCallbackKey;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN   mFeaturerSwitch = TRUE;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN   mResetRequired  = FALSE;

GLOBAL_REMOVE_IF_UNREFERENCED EFI_HII_HANDLE                         mHiiHandle = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_FORM_BROWSER2_PROTOCOL             *gFormBrowser2;
GLOBAL_REMOVE_IF_UNREFERENCED EDKII_FORM_BROWSER_EXTENSION2_PROTOCOL *gFormBrowserEx2;

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN   mModeInitialized = FALSE;
GLOBAL_REMOVE_IF_UNREFERENCED CHAR8     *mLanguageString;
//
// Boot video resolution and text mode.
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mBootHorizontalResolution    = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mBootVerticalResolution      = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mBootTextModeColumn          = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mBootTextModeRow             = 0;
//
// BIOS setup video resolution and text mode.
//
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mSetupTextModeColumn         = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mSetupTextModeRow            = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mSetupHorizontalResolution   = 0;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32    mSetupVerticalResolution     = 0;

GLOBAL_REMOVE_IF_UNREFERENCED FRONT_PAGE_CALLBACK_DATA  gFrontPagePrivate = {
  FRONT_PAGE_CALLBACK_DATA_SIGNATURE,
  NULL,
  NULL,
  NULL,
  {
    FakeExtractConfig,
    FakeRouteConfig,
    FrontPageCallback
  }
};

GLOBAL_REMOVE_IF_UNREFERENCED HII_VENDOR_DEVICE_PATH  mFrontPageHiiVendorDevicePath = {
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    //
    // {8E6D99EE-7531-48f8-8745-7F6144468FF2}
    //
    { 0x8e6d99ee, 0x7531, 0x48f8, { 0x87, 0x45, 0x7f, 0x61, 0x44, 0x46, 0x8f, 0xf2 } }
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    {
      (UINT8) (END_DEVICE_PATH_LENGTH),
      (UINT8) ((END_DEVICE_PATH_LENGTH) >> 8)
    }
  }
};

/**
  This function allows a caller to extract the current configuration for one
  or more named elements from the target driver.


  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Request         A null-terminated Unicode string in <ConfigRequest> format.
  @param Progress        On return, points to a character in the Request string.
                         Points to the string's null terminator if request was successful.
                         Points to the most recent '&' before the first failing name/value
                         pair (or the beginning of the string if the failure is in the
                         first name/value pair) if the request was not successful.
  @param Results         A null-terminated Unicode string in <ConfigAltResp> format which
                         has all values filled in for the names in the Request string.
                         String to be allocated by the called function.

  @retval  EFI_SUCCESS            The Results is filled with the requested values.
  @retval  EFI_OUT_OF_RESOURCES   Not enough memory to store the results.
  @retval  EFI_INVALID_PARAMETER  Request is illegal syntax, or unknown name.
  @retval  EFI_NOT_FOUND          Routing data doesn't match any storage in this driver.

**/
EFI_STATUS
EFIAPI
FakeExtractConfig (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  CONST EFI_STRING                       Request,
  OUT EFI_STRING                             *Progress,
  OUT EFI_STRING                             *Results
  )
{
  if (Progress == NULL || Results == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *Progress = Request;
  return EFI_NOT_FOUND;
}

/**
  This function processes the results of changes in configuration.


  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Configuration   A null-terminated Unicode string in <ConfigResp> format.
  @param Progress        A pointer to a string filled in with the offset of the most
                         recent '&' before the first failing name/value pair (or the
                         beginning of the string if the failure is in the first
                         name/value pair) or the terminating NULL if all was successful.

  @retval  EFI_SUCCESS            The Results is processed successfully.
  @retval  EFI_INVALID_PARAMETER  Configuration is NULL.
  @retval  EFI_NOT_FOUND          Routing data doesn't match any storage in this driver.

**/
EFI_STATUS
EFIAPI
FakeRouteConfig (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  CONST EFI_STRING                       Configuration,
  OUT EFI_STRING                             *Progress
  )
{
  if (Configuration == NULL || Progress == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *Progress = Configuration;
  if (!HiiIsConfigHdrMatch (Configuration, &mBootMaintGuid, mBootMaintStorageName)
      && !HiiIsConfigHdrMatch (Configuration, &mFileExplorerGuid, mFileExplorerStorageName)) {
    return EFI_NOT_FOUND;
  }

  *Progress = Configuration + StrLen (Configuration);
  return EFI_SUCCESS;
}

/**
  This function processes the results of changes in configuration.


  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Action          Specifies the type of action taken by the browser.
  @param QuestionId      A unique value which is sent to the original exporting driver
                         so that it can identify the type of data to expect.
  @param Type            The type of value for the question.
  @param Value           A pointer to the data being sent to the original exporting driver.
  @param ActionRequest   On return, points to the action requested by the callback function.

  @retval  EFI_SUCCESS           The callback successfully handled the action.
  @retval  EFI_OUT_OF_RESOURCES  Not enough storage is available to hold the variable and its data.
  @retval  EFI_DEVICE_ERROR      The variable could not be saved.
  @retval  EFI_UNSUPPORTED       The specified Action is not supported by the callback.

**/
EFI_STATUS
EFIAPI
FrontPageCallback (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  EFI_BROWSER_ACTION                     Action,
  IN  EFI_QUESTION_ID                        QuestionId,
  IN  UINT8                                  Type,
  IN  EFI_IFR_TYPE_VALUE                     *Value,
  OUT EFI_BROWSER_ACTION_REQUEST             *ActionRequest
  )
{
  CHAR8                         *LangCode;
  CHAR8                         *Lang;
  UINTN                         Index;
  EFI_STATUS                    Status;

  if (Action != EFI_BROWSER_ACTION_CHANGING && Action != EFI_BROWSER_ACTION_CHANGED) {
    //
    // Do nothing for other UEFI Action. Only do call back when data is changed.
    //
    return EFI_UNSUPPORTED;
  }

  gCallbackKey = QuestionId;

  if (Action == EFI_BROWSER_ACTION_CHANGED) {
    if ((Value == NULL) || (ActionRequest == NULL)) {
      return EFI_INVALID_PARAMETER;
    }
    //
    // The first 4 entries in the Front Page are to be GUARANTEED to remain constant so IHV's can
    // describe to their customers in documentation how to find their setup information (namely
    // under the device manager and specific buckets)
    //
    switch (QuestionId) {
    case FRONT_PAGE_KEY_CONTINUE:
      //
      // This is the continue - clear the screen and return an error to get out of FrontPage loop
      //
      *ActionRequest = SetupChangesReminder(FALSE);
      break;

    case FRONT_PAGE_KEY_LANGUAGE:
      //
      // Allocate working buffer for RFC 4646 language in supported LanguageString.
      //
      Lang = AllocatePool (AsciiStrSize (mLanguageString));
      ASSERT (Lang != NULL);
      if (Lang == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }

      Index = 0;
      LangCode = mLanguageString;
      while (*LangCode != 0) {
        GetNextLanguage (&LangCode, Lang);

        if (Index == Value->u8) {
          break;
        }

        Index++;
      }

      if (Index == Value->u8) {
        Status = gRT->SetVariable (
                        L"PlatformLang",
                        &gEfiGlobalVariableGuid,
                        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                        AsciiStrSize (Lang),
                        Lang
                        );
        ASSERT_EFI_ERROR(Status);
      } else {
        ASSERT (FALSE);
      }
      *ActionRequest = EFI_BROWSER_ACTION_REQUEST_EXIT;

      FreePool (Lang);
      break;

    case FRONT_PAGE_KEY_RESET:
      //
      // Check changes and Reset
      //
      *ActionRequest = SetupChangesReminder(FALSE);
      if (*ActionRequest == EFI_BROWSER_ACTION_REQUEST_EXIT) {
        gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
      }
      return EFI_UNSUPPORTED;

    default:
      break;
    }

  } else {
    switch (QuestionId) {
    case FRONT_PAGE_KEY_BOOT_MANAGER:
      //
      // Boot Manager
      //
      break;

    case FRONT_PAGE_KEY_DEVICE_MANAGER:
      //
      // Device Manager
      //
      break;

    case FRONT_PAGE_KEY_BOOT_MAINTAIN:
      //
      // Boot Maintenance Manager
      //
      break;

    default:
      if ((gCallbackKey >= FRONT_PAGE_KEY_OFFSET) && (gCallbackKey < FRONT_PAGE_KEY_OFFSET + FRONT_PAGE_KEY_SECTION)) {
        break;
      }
      gCallbackKey = 0;
      break;
    }
  }

  return EFI_SUCCESS;
}

/**
  Initialize HII information for the FrontPage


  @retval  EFI_SUCCESS        The operation is successful.
  @retval  EFI_DEVICE_ERROR   If the dynamic opcode creation failed.

**/
EFI_STATUS
InitializeFrontPage (
  VOID
  )
{
  EFI_STATUS                  Status;
  CHAR8                       *LangCode;
  CHAR8                       *Lang;
  CHAR8                       *CurrentLang;
  UINTN                       OptionCount;
  CHAR16                      *StringBuffer;
  EFI_HII_HANDLE              HiiHandle;
  VOID                        *OptionsOpCodeHandle;
  VOID                        *StartOpCodeHandle;
  VOID                        *EndOpCodeHandle;
  EFI_IFR_GUID_LABEL          *StartLabel;
  EFI_IFR_GUID_LABEL          *EndLabel;
  UINTN                       Index;
  EFI_STRING_ID               FormSetTitle;
  EFI_STRING_ID               FormSetHelp;
  EFI_STRING                  String;
  EFI_STRING_ID               Token;
  EFI_STRING_ID               TokenHelp;
  EFI_HII_HANDLE              *HiiHandles;
  EFI_HII_STRING_PROTOCOL     *HiiString;
  UINTN                       StringSize;
  UINTN                       BufferSize;

  Lang                = NULL;
  CurrentLang         = NULL;
  StringBuffer        = NULL;
  StartOpCodeHandle   = NULL;
  EndOpCodeHandle     = NULL;
  HiiHandles          = NULL;
  OptionsOpCodeHandle = NULL;
  gCallbackKey  = 0;

  //
  // Locate Hii relative protocols
  //
  Status = gBS->LocateProtocol (&gEfiFormBrowser2ProtocolGuid, NULL, (VOID **) &gFormBrowser2);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Install Device Path Protocol and Config Access protocol to driver handle
  //
  gFrontPagePrivate.DriverHandle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &gFrontPagePrivate.DriverHandle,
                  &gEfiDevicePathProtocolGuid,
                  &mFrontPageHiiVendorDevicePath,
                  &gEfiHiiConfigAccessProtocolGuid,
                  &gFrontPagePrivate.ConfigAccess,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Publish our HII data
  //
  gFrontPagePrivate.HiiHandle = HiiAddPackages (
                                  &mFrontPageGuid,
                                  gFrontPagePrivate.DriverHandle,
                                  FrontPageVfrBin,
                                  UiAppStrings,
                                  NULL
                                  );
  ASSERT (gFrontPagePrivate.HiiHandle != NULL);


  //
  // Init OpCode Handle and Allocate space for creation of UpdateData Buffer
  //
  StartOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (StartOpCodeHandle != NULL);
  if (StartOpCodeHandle == NULL) goto EXIT;

  EndOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (EndOpCodeHandle != NULL);
  if (EndOpCodeHandle == NULL) goto EXIT;

  OptionsOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (OptionsOpCodeHandle != NULL);
  if (OptionsOpCodeHandle == NULL) goto EXIT;

  //
  // Create Hii Extend Label OpCode as the start opcode
  //
  StartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (StartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  StartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  StartLabel->Number       = LABEL_SELECT_LANGUAGE;

  //
  // Create Hii Extend Label OpCode as the end opcode
  //
  EndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (EndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  EndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  EndLabel->Number       = LABEL_END;

  //
  // Collect the languages from what our current Language support is based on our VFR
  //
  HiiHandle = gFrontPagePrivate.HiiHandle;

  GetEfiGlobalVariable2 (L"PlatformLang", (VOID **) &CurrentLang, NULL);

  if (mLanguageString == NULL) {
    //
    // Get Support language list from variable.
    //
    GetEfiGlobalVariable2 (L"PlatformLangCodes", (VOID **) &mLanguageString, NULL);
    if (mLanguageString == NULL) {
      mLanguageString = AllocateCopyPool (
                                 AsciiStrSize ((CHAR8 *) PcdGetPtr (PcdUefiVariableDefaultPlatformLangCodes)),
                                 (CHAR8 *) PcdGetPtr (PcdUefiVariableDefaultPlatformLangCodes)
                                 );
      ASSERT (mLanguageString != NULL);
      if (mLanguageString == NULL) goto EXIT;
    }
  }

  if (gFrontPagePrivate.LanguageToken == NULL) {
    //
    // Count the language list number.
    //
    LangCode      = mLanguageString;
    Lang          = AllocatePool (AsciiStrSize (mLanguageString));
    ASSERT (Lang != NULL);
    if (Lang == NULL) goto EXIT;
    OptionCount = 0;
    while (*LangCode != 0) {
      GetNextLanguage (&LangCode, Lang);
      OptionCount ++;
    }

    //
    // Allocate extra 1 as the end tag.
    //
    gFrontPagePrivate.LanguageToken = AllocateZeroPool ((OptionCount + 1) * sizeof (EFI_STRING_ID));
    ASSERT (gFrontPagePrivate.LanguageToken != NULL);
    if (gFrontPagePrivate.LanguageToken == NULL) goto EXIT;

    Status = gBS->LocateProtocol (&gEfiHiiStringProtocolGuid, NULL, (VOID **) &HiiString);
    ASSERT_EFI_ERROR (Status);

    LangCode     = mLanguageString;
    OptionCount  = 0;
    while (*LangCode != 0) {
      GetNextLanguage (&LangCode, Lang);

      StringSize = 0;
      Status = HiiString->GetString (HiiString, Lang, HiiHandle, PRINTABLE_LANGUAGE_NAME_STRING_ID, StringBuffer, &StringSize, NULL);
      if (Status == EFI_BUFFER_TOO_SMALL) {
        StringBuffer = AllocateZeroPool (StringSize);
        ASSERT (StringBuffer != NULL);
        if (StringBuffer == NULL) goto EXIT;

        Status = HiiString->GetString (HiiString, Lang, HiiHandle, PRINTABLE_LANGUAGE_NAME_STRING_ID, StringBuffer, &StringSize, NULL);
        ASSERT_EFI_ERROR (Status);
      }

      if (EFI_ERROR (Status)) {
        BufferSize = AsciiStrSize (Lang) * sizeof (CHAR16);
        StringBuffer = AllocatePool(BufferSize);
        ASSERT (StringBuffer != NULL);
        if (StringBuffer == NULL) goto EXIT;
        AsciiStrToUnicodeStrS (Lang, StringBuffer, BufferSize);
      }

      ASSERT (StringBuffer != NULL);
      gFrontPagePrivate.LanguageToken[OptionCount] = HiiSetString (HiiHandle, 0, StringBuffer, NULL);
      FreePool (StringBuffer);

      OptionCount++;
    }
  }

  ASSERT (gFrontPagePrivate.LanguageToken != NULL);
  LangCode     = mLanguageString;
  OptionCount  = 0;
  if (Lang == NULL) {
    Lang = AllocatePool (AsciiStrSize (mLanguageString));
    ASSERT (Lang != NULL);
    if (Lang == NULL) goto EXIT;
  }
  while (*LangCode != 0) {
    GetNextLanguage (&LangCode, Lang);

    if (CurrentLang != NULL && AsciiStrCmp (Lang, CurrentLang) == 0) {
      HiiCreateOneOfOptionOpCode (
        OptionsOpCodeHandle,
        gFrontPagePrivate.LanguageToken[OptionCount],
        EFI_IFR_OPTION_DEFAULT,
        EFI_IFR_NUMERIC_SIZE_1,
        (UINT8) OptionCount
        );
    } else {
      HiiCreateOneOfOptionOpCode (
        OptionsOpCodeHandle,
        gFrontPagePrivate.LanguageToken[OptionCount],
        0,
        EFI_IFR_NUMERIC_SIZE_1,
        (UINT8) OptionCount
        );
    }

    OptionCount++;
  }

  if (CurrentLang != NULL) {
    FreePool (CurrentLang);
  }
  FreePool (Lang);

  HiiCreateOneOfOpCode (
    StartOpCodeHandle,
    FRONT_PAGE_KEY_LANGUAGE,
    0,
    0,
    STRING_TOKEN (STR_LANGUAGE_SELECT),
    STRING_TOKEN (STR_LANGUAGE_SELECT_HELP),
    EFI_IFR_FLAG_CALLBACK,
    EFI_IFR_NUMERIC_SIZE_1,
    OptionsOpCodeHandle,
    NULL
    );

  Status = HiiUpdateForm (
             HiiHandle,
             &mFrontPageGuid,
             FRONT_PAGE_FORM_ID,
             StartOpCodeHandle, // LABEL_SELECT_LANGUAGE
             EndOpCodeHandle    // LABEL_END
             );

  HiiFreeOpCodeHandle (StartOpCodeHandle);
  HiiFreeOpCodeHandle (EndOpCodeHandle);
  HiiFreeOpCodeHandle (OptionsOpCodeHandle);

  //
  // Allocate space for creation of UpdateData Buffer
  //
  StartOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (StartOpCodeHandle != NULL);
  if (StartOpCodeHandle == NULL) goto EXIT;

  EndOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (EndOpCodeHandle != NULL);
  if (EndOpCodeHandle == NULL) goto EXIT;

  //
  // Create Hii Extend Label OpCode as the start opcode
  //
  StartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (StartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  StartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  StartLabel->Number       = LABEL_PLATFORM_INFORMATION;

  //
  // Create Hii Extend Label OpCode as the end opcode
  //
  EndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (EndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  EndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  EndLabel->Number       = LABEL_END;

  //
  // Get all the Hii handles
  //
  HiiHandles = HiiGetHiiHandles (NULL);
  ASSERT (HiiHandles != NULL);
  if (HiiHandles == NULL) goto EXIT;

  //
  // Search for formset of each class type
  //
  for (Index = 0; HiiHandles[Index] != NULL; Index++) {
    if (!ExtractDisplayedHiiFormFromHiiHandle (HiiHandles[Index], &gIfrFrontPageGuid, &FormSetTitle, &FormSetHelp)) {
      continue;
    }

    String = HiiGetString (HiiHandles[Index], FormSetTitle, NULL);
    if (String == NULL) {
      String = HiiGetString (HiiHandle, STR_MISSING_STRING, NULL);
      ASSERT (String != NULL);
      if (String == NULL) goto EXIT;
    }
    Token = HiiSetString (HiiHandle, 0, String, NULL);
    FreePool (String);

    String = HiiGetString (HiiHandles[Index], FormSetHelp, NULL);
    if (String == NULL) {
      String = HiiGetString (HiiHandle, STR_MISSING_STRING, NULL);
      ASSERT (String != NULL);
      if (String == NULL) goto EXIT;
    }
    TokenHelp = HiiSetString (HiiHandle, 0, String, NULL);
    FreePool (String);

    HiiCreateGotoOpCode (
      StartOpCodeHandle,
      INVALID_FORM_ID,
      Token,
      TokenHelp,
      EFI_IFR_FLAG_CALLBACK,
      (EFI_QUESTION_ID) (Index + FRONT_PAGE_KEY_OFFSET)
      );
  }

  HiiUpdateForm (
    HiiHandle,
    &mFrontPageGuid,
    FRONT_PAGE_FORM_ID,
    StartOpCodeHandle,
    EndOpCodeHandle
    );

EXIT:

  if (StartOpCodeHandle != NULL) {
    HiiFreeOpCodeHandle (StartOpCodeHandle);
  }

  if (EndOpCodeHandle != NULL) {
    HiiFreeOpCodeHandle (EndOpCodeHandle);
  }

  if (HiiHandles != NULL) {
    FreePool (HiiHandles);
  }

  return Status;
}

/**
  Call the browser and display the front page

  @return   Status code that will be returned by
            EFI_FORM_BROWSER2_PROTOCOL.SendForm ().

**/
EFI_STATUS
CallFrontPage (
  VOID
  )
{
  EFI_STATUS                  Status;
  EFI_BROWSER_ACTION_REQUEST  ActionRequest;

  //
  // Begin waiting for USER INPUT
  //
  REPORT_STATUS_CODE (
    EFI_PROGRESS_CODE,
    (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_PC_INPUT_WAIT)
    );

  ActionRequest = EFI_BROWSER_ACTION_REQUEST_NONE;
  Status = gFormBrowser2->SendForm (
                            gFormBrowser2,
                            &gFrontPagePrivate.HiiHandle,
                            1,
                            &mFrontPageGuid,
                            0,
                            NULL,
                            &ActionRequest
                            );
  //
  // Check whether user change any option setting which needs a reset to be effective
  //
  if (ActionRequest == EFI_BROWSER_ACTION_REQUEST_RESET) {
    EnableResetRequired ();
  }

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  gFrontPagePrivate.DriverHandle,
                  &gEfiDevicePathProtocolGuid,
                  &mFrontPageHiiVendorDevicePath,
                  &gEfiHiiConfigAccessProtocolGuid,
                  &gFrontPagePrivate.ConfigAccess,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Publish our HII data
  //
  HiiRemovePackages (gFrontPagePrivate.HiiHandle);
  if (gFrontPagePrivate.LanguageToken != NULL) {
    FreePool (gFrontPagePrivate.LanguageToken);
    gFrontPagePrivate.LanguageToken = NULL;
  }
  return Status;
}

/**
  Convert Processor Frequency Data to a string.

  @param ProcessorFrequency The frequency data to process
  @param Base10Exponent     The exponent based on 10
  @param String             The string that is created

**/
VOID
ConvertProcessorToString (
  IN  UINT16                               ProcessorFrequency,
  IN  UINT16                               Base10Exponent,
  OUT CHAR16                               **String
  )
{
  CHAR16  *StringBuffer;
  UINTN   Index;
  UINTN   DestMax;
  UINT32  FreqMhz;

  if (Base10Exponent >= 6) {
    FreqMhz = ProcessorFrequency;
    for (Index = 0; Index < (UINTN) (Base10Exponent - 6); Index++) {
      FreqMhz *= 10;
    }
  } else {
    FreqMhz = 0;
  }
  DestMax = 0x20 / sizeof (CHAR16);
  StringBuffer = AllocateZeroPool (0x20);
  ASSERT (StringBuffer != NULL);
  if (StringBuffer == NULL) {
    return;
  }
  UnicodeValueToStringS (StringBuffer, sizeof (CHAR16) * DestMax, LEFT_JUSTIFY, FreqMhz / 1000, 3);
  Index = StrnLenS (StringBuffer, DestMax);
  StrCatS (StringBuffer, DestMax, L".");
  UnicodeValueToStringS (
    StringBuffer + Index + 1,
    sizeof (CHAR16) * (DestMax - (Index + 1)),
    PREFIX_ZERO,
    (FreqMhz % 1000) / 10,
    2
    );
  StrCatS (StringBuffer, DestMax, L" GHz");
  *String = (CHAR16 *) StringBuffer;
  return ;
}


/**
  Convert Memory Size to a string.

  @param MemorySize      The size of the memory to process
  @param String          The string that is created

**/
VOID
ConvertMemorySizeToString (
  IN  UINT32          MemorySize,
  OUT CHAR16          **String
  )
{
  CHAR16  *StringBuffer;

  StringBuffer = AllocateZeroPool (0x24);
  ASSERT (StringBuffer != NULL);
  if (StringBuffer == NULL) {
    return;
  }
  UnicodeValueToStringS (StringBuffer, 0x24, LEFT_JUSTIFY, MemorySize, 10);
  StrCatS (StringBuffer, 0x24 / sizeof (CHAR16), L" MB RAM");

  *String = (CHAR16 *) StringBuffer;

  return ;
}

/**

  Acquire the string associated with the Index from smbios structure and return it.
  The caller is responsible for free the string buffer.

  @param    OptionalStrStart  The start position to search the string
  @param    Index             The index of the string to extract
  @param    String            The string that is extracted

  @retval   EFI_SUCCESS       The function returns EFI_SUCCESS always.

**/
EFI_STATUS
GetOptionalStringByIndex (
  IN      CHAR8                   *OptionalStrStart,
  IN      UINT8                   Index,
  OUT     CHAR16                  **String
  )
{
  UINTN          StrSize;

  if (Index == 0) {
    *String = AllocateZeroPool (sizeof (CHAR16));
    return EFI_SUCCESS;
  }

  StrSize = 0;
  do {
    Index--;
    OptionalStrStart += StrSize;
    StrSize           = AsciiStrSize (OptionalStrStart);
  } while (OptionalStrStart[StrSize] != 0 && Index != 0);

  if ((Index != 0) || (StrSize == 1)) {
    //
    // Meet the end of strings set but Index is non-zero, or
    // Find an empty string
    //
    *String = GetStringById (STRING_TOKEN (STR_MISSING_STRING));
  } else {
    *String = AllocatePool (StrSize * sizeof (CHAR16));
    ASSERT (*String != NULL);
    if (*String != NULL){
      AsciiStrToUnicodeStrS (OptionalStrStart, *String, StrSize * sizeof (CHAR16));
    }
  }

  return EFI_SUCCESS;
}


/**
  Update the banner information for the Front Page based on DataHub information.

**/
VOID
UpdateFrontPageStrings (
  VOID
  )
{
  UINT8                             StrIndex;
  CHAR16                            *NewString;
  BOOLEAN                           Find[5];
  EFI_STATUS                        Status;
  EFI_STRING_ID                     TokenToUpdate;
  EFI_SMBIOS_HANDLE                 SmbiosHandle;
  EFI_SMBIOS_PROTOCOL               *Smbios;
  SMBIOS_TABLE_TYPE0                *Type0Record;
  SMBIOS_TABLE_TYPE1                *Type1Record;
  SMBIOS_TABLE_TYPE4                *Type4Record;
  SMBIOS_TABLE_TYPE19               *Type19Record;
  EFI_SMBIOS_TABLE_HEADER           *Record;

  ZeroMem (Find, sizeof (Find));

  //
  // Update Front Page strings
  //
  Status = gBS->LocateProtocol (
                  &gEfiSmbiosProtocolGuid,
                  NULL,
                  (VOID **) &Smbios
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
  do {
    Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Record, NULL);
    if (EFI_ERROR(Status)) {
      break;
    }

    if (Record->Type == EFI_SMBIOS_TYPE_BIOS_INFORMATION) {
      Type0Record = (SMBIOS_TABLE_TYPE0 *) Record;
      StrIndex = Type0Record->BiosVersion;
      GetOptionalStringByIndex ((CHAR8*)((UINT8*)Type0Record + Type0Record->Hdr.Length), StrIndex, &NewString);
      TokenToUpdate = STRING_TOKEN (STR_FRONT_PAGE_BIOS_VERSION);
      HiiSetString (gFrontPagePrivate.HiiHandle, TokenToUpdate, NewString, NULL);
      FreePool (NewString);
      Find[0] = TRUE;
    }

    if (Record->Type == EFI_SMBIOS_TYPE_SYSTEM_INFORMATION) {
      Type1Record = (SMBIOS_TABLE_TYPE1 *) Record;
      StrIndex = Type1Record->ProductName;
      GetOptionalStringByIndex ((CHAR8*)((UINT8*)Type1Record + Type1Record->Hdr.Length), StrIndex, &NewString);
      TokenToUpdate = STRING_TOKEN (STR_FRONT_PAGE_COMPUTER_MODEL);
      HiiSetString (gFrontPagePrivate.HiiHandle, TokenToUpdate, NewString, NULL);
      FreePool (NewString);
      Find[1] = TRUE;
    }

    if (Record->Type == EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION) {
      Type4Record = (SMBIOS_TABLE_TYPE4 *) Record;
      StrIndex = Type4Record->ProcessorVersion;
      GetOptionalStringByIndex ((CHAR8*)((UINT8*)Type4Record + Type4Record->Hdr.Length), StrIndex, &NewString);
      TokenToUpdate = STRING_TOKEN (STR_FRONT_PAGE_CPU_MODEL);
      HiiSetString (gFrontPagePrivate.HiiHandle, TokenToUpdate, NewString, NULL);
      FreePool (NewString);
      Find[2] = TRUE;
    }

    if (Record->Type == EFI_SMBIOS_TYPE_PROCESSOR_INFORMATION) {
      Type4Record = (SMBIOS_TABLE_TYPE4 *) Record;
      ConvertProcessorToString(Type4Record->CurrentSpeed, 6, &NewString);
      TokenToUpdate = STRING_TOKEN (STR_FRONT_PAGE_CPU_SPEED);
      HiiSetString (gFrontPagePrivate.HiiHandle, TokenToUpdate, NewString, NULL);
      FreePool (NewString);
      Find[3] = TRUE;
    }

    if ( Record->Type == EFI_SMBIOS_TYPE_MEMORY_ARRAY_MAPPED_ADDRESS ) {
      Type19Record = (SMBIOS_TABLE_TYPE19 *) Record;
      ConvertMemorySizeToString (
        (UINT32)(RShiftU64((Type19Record->EndingAddress - Type19Record->StartingAddress + 1), 10)),
        &NewString
        );
      TokenToUpdate = STRING_TOKEN (STR_FRONT_PAGE_MEMORY_SIZE);
      HiiSetString (gFrontPagePrivate.HiiHandle, TokenToUpdate, NewString, NULL);
      FreePool (NewString);
      Find[4] = TRUE;
    }
  } while ( !(Find[0] && Find[1] && Find[2] && Find[3] && Find[4]));
  return ;
}

/**
  This function will change video resolution and text mode
  according to defined setup mode or defined boot mode

  @param  IsSetupMode   Indicate mode is changed to setup mode or boot mode.

  @retval  EFI_SUCCESS  Mode is changed successfully.
  @retval  Others       Mode failed to be changed.

**/
EFI_STATUS
EFIAPI
BdsSetConsoleMode (
  BOOLEAN  IsSetupMode
  )
{
  EFI_GRAPHICS_OUTPUT_PROTOCOL          *GraphicsOutput;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL       *SimpleTextOut;
  UINTN                                 SizeOfInfo;
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  *Info;
  UINT32                                MaxGopMode;
  UINT32                                MaxTextMode;
  UINT32                                ModeNumber;
  UINT32                                NewHorizontalResolution;
  UINT32                                NewVerticalResolution;
  UINT32                                NewColumns;
  UINT32                                NewRows;
  UINTN                                 HandleCount;
  EFI_HANDLE                            *HandleBuffer;
  EFI_STATUS                            Status;
  UINTN                                 Index;
  UINTN                                 CurrentColumn;
  UINTN                                 CurrentRow;

  MaxGopMode  = 0;
  MaxTextMode = 0;

  //
  // Get current video resolution and text mode
  //
  Status = gBS->HandleProtocol (
                  gST->ConsoleOutHandle,
                  &gEfiGraphicsOutputProtocolGuid,
                  (VOID**)&GraphicsOutput
                  );
  if (EFI_ERROR (Status)) {
    GraphicsOutput = NULL;
  }

  Status = gBS->HandleProtocol (
                  gST->ConsoleOutHandle,
                  &gEfiSimpleTextOutProtocolGuid,
                  (VOID**)&SimpleTextOut
                  );
  if (EFI_ERROR (Status)) {
    SimpleTextOut = NULL;
  }

  if ((GraphicsOutput == NULL) || (SimpleTextOut == NULL)) {
    return EFI_UNSUPPORTED;
  }

  if (IsSetupMode) {
    //
    // The requried resolution and text mode is setup mode.
    //
    NewHorizontalResolution = mSetupHorizontalResolution;
    NewVerticalResolution   = mSetupVerticalResolution;
    NewColumns              = mSetupTextModeColumn;
    NewRows                 = mSetupTextModeRow;
  } else {
    //
    // The required resolution and text mode is boot mode.
    //
    NewHorizontalResolution = mBootHorizontalResolution;
    NewVerticalResolution   = mBootVerticalResolution;
    NewColumns              = mBootTextModeColumn;
    NewRows                 = mBootTextModeRow;
  }

  if (GraphicsOutput != NULL) {
    MaxGopMode  = GraphicsOutput->Mode->MaxMode;
  }

  if (SimpleTextOut != NULL) {
    MaxTextMode = SimpleTextOut->Mode->MaxMode;
  }

  //
  // 1. If current video resolution is same with required video resolution,
  //    video resolution need not be changed.
  //    1.1. If current text mode is same with required text mode, text mode need not be changed.
  //    1.2. If current text mode is different from required text mode, text mode need be changed.
  // 2. If current video resolution is different from required video resolution, we need restart whole console drivers.
  //
  for (ModeNumber = 0; ModeNumber < MaxGopMode; ModeNumber++) {
    Status = GraphicsOutput->QueryMode (
                       GraphicsOutput,
                       ModeNumber,
                       &SizeOfInfo,
                       &Info
                       );
    if (!EFI_ERROR (Status)) {
      if ((Info->HorizontalResolution == NewHorizontalResolution) &&
          (Info->VerticalResolution == NewVerticalResolution)) {
        if ((GraphicsOutput->Mode->Info->HorizontalResolution == NewHorizontalResolution) &&
            (GraphicsOutput->Mode->Info->VerticalResolution == NewVerticalResolution)) {
          //
          // Current resolution is same with required resolution, check if text mode need be set
          //
          Status = SimpleTextOut->QueryMode (SimpleTextOut, SimpleTextOut->Mode->Mode, &CurrentColumn, &CurrentRow);
          ASSERT_EFI_ERROR (Status);
          if (CurrentColumn == NewColumns && CurrentRow == NewRows) {
            //
            // If current text mode is same with required text mode. Do nothing
            //
            FreePool (Info);
            return EFI_SUCCESS;
          } else {
            //
            // If current text mode is different from requried text mode.  Set new video mode
            //
            for (Index = 0; Index < MaxTextMode; Index++) {
              Status = SimpleTextOut->QueryMode (SimpleTextOut, Index, &CurrentColumn, &CurrentRow);
              if (!EFI_ERROR(Status)) {
                if ((CurrentColumn == NewColumns) && (CurrentRow == NewRows)) {
                  //
                  // Required text mode is supported, set it.
                  //
                  Status = SimpleTextOut->SetMode (SimpleTextOut, Index);
                  ASSERT_EFI_ERROR (Status);
                  //
                  // Update text mode PCD.
                  //
                  PcdSet32S (PcdConOutColumn, mSetupTextModeColumn);
                  PcdSet32S (PcdConOutRow, mSetupTextModeRow);
                  FreePool (Info);
                  return EFI_SUCCESS;
                }
              }
            }
            if (Index == MaxTextMode) {
              //
              // If requried text mode is not supported, return error.
              //
              FreePool (Info);
              return EFI_UNSUPPORTED;
            }
          }
        } else {
          //
          // If current video resolution is not same with the new one, set new video resolution.
          // In this case, the driver which produces simple text out need be restarted.
          //
          Status = GraphicsOutput->SetMode (GraphicsOutput, ModeNumber);
          if (!EFI_ERROR (Status)) {
            FreePool (Info);
            break;
          }
        }
      }
      FreePool (Info);
    }
  }

  if (ModeNumber == MaxGopMode) {
    //
    // If the resolution is not supported, return error.
    //
    return EFI_UNSUPPORTED;
  }

  //
  // Set PCD to Inform GraphicsConsole to change video resolution.
  // Set PCD to Inform Consplitter to change text mode.
  //
  PcdSet32S (PcdVideoHorizontalResolution, NewHorizontalResolution);
  PcdSet32S (PcdVideoVerticalResolution, NewVerticalResolution);
  PcdSet32S (PcdConOutColumn, NewColumns);
  PcdSet32S (PcdConOutRow, NewRows);


  //
  // Video mode is changed, so restart graphics console driver and higher level driver.
  // Reconnect graphics console driver and higher level driver.
  // Locate all the handles with GOP protocol and reconnect it.
  //
  Status = gBS->LocateHandleBuffer (
                   ByProtocol,
                   &gEfiSimpleTextOutProtocolGuid,
                   NULL,
                   &HandleCount,
                   &HandleBuffer
                   );
  if (!EFI_ERROR (Status)) {
    for (Index = 0; Index < HandleCount; Index++) {
      gBS->DisconnectController (HandleBuffer[Index], NULL, NULL);
    }
    for (Index = 0; Index < HandleCount; Index++) {
      gBS->ConnectController (HandleBuffer[Index], NULL, NULL, TRUE);
    }
    if (HandleBuffer != NULL) {
      FreePool (HandleBuffer);
    }
  }

  return EFI_SUCCESS;
}

/**
  The user Entry Point for Application. The user code starts with this function
  as the real entry point for the image goes into a library that calls this
  function.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
InitializeUserInterface (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                         Status;
  EFI_GRAPHICS_OUTPUT_PROTOCOL       *GraphicsOutput;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *SimpleTextOut;
  UINTN                              BootTextColumn;
  UINTN                              BootTextRow;

  if (!mModeInitialized) {
    //
    // After the console is ready, get current video resolution
    // and text mode before launching setup at first time.
    //
    Status = gBS->HandleProtocol (
                    gST->ConsoleOutHandle,
                    &gEfiGraphicsOutputProtocolGuid,
                    (VOID**)&GraphicsOutput
                    );
    if (EFI_ERROR (Status)) {
      GraphicsOutput = NULL;
    }

    Status = gBS->HandleProtocol (
                    gST->ConsoleOutHandle,
                    &gEfiSimpleTextOutProtocolGuid,
                    (VOID**)&SimpleTextOut
                    );
    if (EFI_ERROR (Status)) {
      SimpleTextOut = NULL;
    }

    if (GraphicsOutput != NULL) {
      //
      // Get current video resolution and text mode.
      //
      mBootHorizontalResolution = GraphicsOutput->Mode->Info->HorizontalResolution;
      mBootVerticalResolution   = GraphicsOutput->Mode->Info->VerticalResolution;
    }

    if (SimpleTextOut != NULL) {
      Status = SimpleTextOut->QueryMode (
                                SimpleTextOut,
                                SimpleTextOut->Mode->Mode,
                                &BootTextColumn,
                                &BootTextRow
                                );
      mBootTextModeColumn = (UINT32)BootTextColumn;
      mBootTextModeRow    = (UINT32)BootTextRow;
    }

    //
    // Get user defined text mode for setup.
    //
    mSetupHorizontalResolution = PcdGet32 (PcdSetupVideoHorizontalResolution);
    mSetupVerticalResolution   = PcdGet32 (PcdSetupVideoVerticalResolution);
    mSetupTextModeColumn       = PcdGet32 (PcdSetupConOutColumn);
    mSetupTextModeRow          = PcdGet32 (PcdSetupConOutRow);

    mModeInitialized           = TRUE;
  }

  gBS->SetWatchdogTimer (0x0000, 0x0000, 0x0000, NULL);
  gST->ConOut->ClearScreen (gST->ConOut);

  //
  // Install customized fonts needed by Front Page
  //

  mHiiHandle = ExportFonts ();
  ASSERT (mHiiHandle != NULL);

  InitializeStringSupport ();

  //
  // For each bootable device, BlockIo/DiskIo/SimpleFileSystem protocols need
  // to be installed on the controller handle. When we enter setup via F2
  // hotkey these protocols are not installed and so EfiBootManagerConnectAll()
  // is needed to achieve it
  //
  EfiBootManagerConnectAll ();

  BdsSetConsoleMode (TRUE);
  UiEntry (FALSE);
  BdsSetConsoleMode (FALSE);

  UninitializeStringSupport ();
  HiiRemovePackages (mHiiHandle);

  return EFI_SUCCESS;
}

/**
  Call the menu add according the classguid of gIfrFrontPageGuid.

**/
VOID
CallOtherMenuItem (
  VOID
  )
{
  EFI_BROWSER_ACTION_REQUEST  ActionRequest;
  EFI_HII_HANDLE              *HiiHandles;

  HiiHandles = HiiGetHiiHandles (NULL);
  ASSERT (HiiHandles != NULL);

  //
  // We will have returned from processing a callback - user either hit ESC to exit, or selected
  // a target to display
  //
  // The HiiHandle offset is get from "gCallbackKey - FRONT_PAGE_KEY_OFFSET". Because when update the menu
  // in the "InitializeFrontPage", the menu's QuestionId = Offset + FRONT_PAGE_KEY_OFFSET, and in callback
  // function, gCallbackKey = QuestionId.
  //
  if ((gCallbackKey >= FRONT_PAGE_KEY_OFFSET) && (gCallbackKey < FRONT_PAGE_KEY_OFFSET + FRONT_PAGE_KEY_SECTION)) {
    ActionRequest = EFI_BROWSER_ACTION_REQUEST_NONE;
    gFormBrowser2->SendForm (
                     gFormBrowser2,
                     &HiiHandles[gCallbackKey - FRONT_PAGE_KEY_OFFSET],
                     1,
                     &gIfrFrontPageGuid,
                     0,
                     NULL,
                     &ActionRequest
                     );

    if (ActionRequest == EFI_BROWSER_ACTION_REQUEST_RESET) {
      EnableResetRequired ();
    }
  }

  FreePool (HiiHandles);
}

VOID
SignalEnterSetupEvent (
  VOID
  )
{
  EFI_HANDLE                 Handle;
  EFI_STATUS                 Status;

  Handle = NULL;
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gSetupEnterGuid,
                  EFI_NATIVE_INTERFACE,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);
}

/**
  This function is the main entry of the UI entry.
  The function will present the main menu of the system UI.

  @param ConnectAllHappened Caller passes the value to UI to avoid unnecessary connect-all.

**/
VOID
EFIAPI
UiEntry (
  IN BOOLEAN                      ConnectAllHappened
  )
{
  EFI_STATUS                    Status;
  EFI_INPUT_KEY                 HotKey;
  EFI_STRING                    HelpString;
  EFI_BOOT_LOGO_PROTOCOL        *BootLogo;

  SignalEnterSetupEvent ();
  //
  // Indicate if the connect all has been performed before.
  //
  if (ConnectAllHappened) {
    gConnectAllHappened = TRUE;
  }

  //
  // The boot option enumeration time is acceptable in Ui driver
  //
  EfiBootManagerRefreshAllBootOption ();

  //
  // BdsDxe doesn't group the legacy boot options for the same device type
  // It's UI's choice.
  //
  GroupMultipleLegacyBootOption4SameType ();

  //
  // Boot Logo is corrupted, report it using Boot Logo protocol.
  //
  Status = gBS->LocateProtocol (&gEfiBootLogoProtocolGuid, NULL, (VOID **) &BootLogo);
  if (!EFI_ERROR (Status) && (BootLogo != NULL)) {
    BootLogo->SetBootLogo (BootLogo, NULL, 0, 0, 0, 0);
  }

  Status = gBS->LocateProtocol (&gEdkiiFormBrowserEx2ProtocolGuid, NULL, (VOID **) &gFormBrowserEx2);
  ASSERT_EFI_ERROR (Status);

  //
  // Register Browser Hot Key
  //

  //
  // First unregister the default hot key F9 and F10.
  //
  HotKey.UnicodeChar = CHAR_NULL;
  HotKey.ScanCode    = SCAN_F9;
  gFormBrowserEx2->RegisterHotKey (&HotKey, BROWSER_ACTION_UNREGISTER, 0, NULL);
  HotKey.ScanCode    = SCAN_F10;
  gFormBrowserEx2->RegisterHotKey (&HotKey, BROWSER_ACTION_UNREGISTER, 0, NULL);

  //
  // Register the global HotKey F2, F3 and F4.
  //
  gFormBrowserEx2->SetScope (SystemLevel);
  HotKey.ScanCode    = SCAN_F4;
  HelpString = HiiGetString (mHiiHandle, STRING_TOKEN (SAVE_CHANGES_STRING), NULL);
  gFormBrowserEx2->RegisterHotKey (&HotKey, BROWSER_ACTION_SUBMIT, 0, HelpString);
  FreePool (HelpString);

  HotKey.ScanCode    = SCAN_F3;
  HelpString = HiiGetString (mHiiHandle, STRING_TOKEN (RESTORE_DEFAULTS_STRING), NULL);
  gFormBrowserEx2->RegisterHotKey (&HotKey, BROWSER_ACTION_DEFAULT, EFI_HII_DEFAULT_CLASS_STANDARD, HelpString);
  FreePool (HelpString);

  HotKey.ScanCode    = SCAN_F2;
  HelpString = HiiGetString (mHiiHandle, STRING_TOKEN (DISCARD_CHANGES_STRING), NULL);
  gFormBrowserEx2->RegisterHotKey (&HotKey, BROWSER_ACTION_DISCARD, 0, HelpString);
  FreePool (HelpString);

  //
  // Install BM HiiPackages.
  // Keep BootMaint HiiPackage, so that it can be covered by global setting.
  //
  InitBMPackage ();

  do {

    InitializeFrontPage ();

    //
    // Update Front Page strings
    //
    UpdateFrontPageStrings ();

    gCallbackKey = 0;
    CallFrontPage ();

    //
    // If gCallbackKey is greater than 1 and less or equal to 5,
    // it will launch configuration utilities.
    // 2 = set language
    // 3 = boot manager
    // 4 = device manager
    // 5 = boot maintenance manager
    //
    if (gCallbackKey != 0) {
      REPORT_STATUS_CODE (
        EFI_PROGRESS_CODE,
        (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_PC_USER_SETUP)
        );
    }
    //
    // Based on the key that was set, we can determine what to do
    //
    switch (gCallbackKey) {
    //
    // The first 4 entries in the Front Page are to be GUARANTEED to remain constant so IHV's can
    // describe to their customers in documentation how to find their setup information (namely
    // under the device manager and specific buckets)
    //
    // These entries consist of the Continue, Select language, Boot Manager, and Device Manager
    //
    case FRONT_PAGE_KEY_CONTINUE:
      //
      // User hit continue
      //
      break;

    case FRONT_PAGE_KEY_LANGUAGE:
      //
      // User made a language setting change - display front page again
      //
      break;

    case FRONT_PAGE_KEY_BOOT_MANAGER:
      //
      // Remove the installed BootMaint HiiPackages before entering into Boot Manager.
      //
      FreeBMPackage ();

      //
      // User chose to run the Boot Manager
      //
      CallBootManager ();

      //
      // Reinstall BootMaint HiiPackages after exiting from Boot Manager.
      //
      InitBMPackage ();
      break;

    case FRONT_PAGE_KEY_DEVICE_MANAGER:
      //
      // Display the Device Manager
      //
      do {
        CallDeviceManager ();
      } while (gCallbackKey == FRONT_PAGE_KEY_DEVICE_MANAGER);
      break;

    case FRONT_PAGE_KEY_BOOT_MAINTAIN:
      //
      // Display the Boot Maintenance Manager
      //
      BdsStartBootMaint ();
      break;
    default:
      if ((gCallbackKey >= FRONT_PAGE_KEY_OFFSET) && (gCallbackKey < FRONT_PAGE_KEY_OFFSET + FRONT_PAGE_KEY_SECTION)) {
        CallOtherMenuItem();
      }
      break;
    }

  } while (gCallbackKey != FRONT_PAGE_KEY_CONTINUE);

  //
  // Will leave browser, check any changes. If yes, pop up reminder for user to make decision.
  // Then, check any reset required change is applied? if yes, reset system.
  //
  SetupChangesReminder(TRUE);

  if (mLanguageString != NULL) {
    FreePool (mLanguageString);
    mLanguageString = NULL;
  }

  //
  // Remove the installed BootMaint HiiPackages when exit.
  //
  FreeBMPackage ();

  //
  // Unregister HotKey when leave UI
  //
  HotKey.ScanCode    = SCAN_F4;
  gFormBrowserEx2->RegisterHotKey (&HotKey, BROWSER_ACTION_UNREGISTER, 0, NULL);
  HotKey.ScanCode    = SCAN_F3;
  gFormBrowserEx2->RegisterHotKey (&HotKey, BROWSER_ACTION_UNREGISTER, 0, NULL);
  HotKey.ScanCode    = SCAN_F2;
  gFormBrowserEx2->RegisterHotKey (&HotKey, BROWSER_ACTION_UNREGISTER, 0, NULL);

}

/**
  Check whether this driver shows in platform setup form.

  When the class guid is gEfiHiiPlatformSetupFormsetGuid, need to check whether
  include other class guid before decide whether can show this formset.

  @param SetupClassGuid  The class guid specifies which form set will be displayed.
  @param ClassGuidList   The class guid list saved in formset.
  @param ClassGuidNum    The class guid number saved in formset.

  @retval  TRUE          The formset for given HII handle will be displayed.
  @retval  FALSE         The formset for given HII handle will not be displayed.

**/
BOOLEAN
IsShowsInPlatformSetupForm (
  IN      EFI_GUID            *SetupClassGuid,
  IN      EFI_GUID            *ClassGuidList,
  IN      UINT8               ClassGuidNum
  )
{
  EFI_GUID     *ClassGuid;
  UINT8        GuidCount;

  ClassGuid = ClassGuidList;
  GuidCount = ClassGuidNum;

  while (GuidCount > 0) {
    if (CompareGuid (SetupClassGuid, ClassGuid)) {
      break;
    }
    ClassGuid ++;
    GuidCount --;
  }

  if (GuidCount == 0) {
    return FALSE;
  }

  //
  // Special for gEfiHiiPlatformSetupFormsetGuid.
  // Only when not include the other three guids, this dirver can show
  // in platform setup menu.
  //
  ClassGuid = ClassGuidList;
  GuidCount = ClassGuidNum;
  if (CompareGuid (SetupClassGuid, &gEfiHiiPlatformSetupFormsetGuid)) {
    while (GuidCount > 0) {
      if (CompareGuid (&gIfrBootMaintenanceGuid, ClassGuid) ||
          CompareGuid (&gIfrFrontPageGuid, ClassGuid) ||
          CompareGuid (&gIfrNotInTpvPageGuid, ClassGuid)) {
        return FALSE;
      }
      ClassGuid ++;
      GuidCount --;
    }
  }

  return TRUE;
}

/**
  Extract the displayed formset for given HII handle and class guid.

  @param Handle          The HII handle.
  @param SetupClassGuid  The class guid specifies which form set will be displayed.
  @param FormSetTitle    Formset title string.
  @param FormSetHelp     Formset help string.

  @retval  TRUE          The formset for given HII handle will be displayed.
  @retval  FALSE         The formset for given HII handle will not be displayed.

**/
BOOLEAN
ExtractDisplayedHiiFormFromHiiHandle (
  IN      EFI_HII_HANDLE      Handle,
  IN      EFI_GUID            *SetupClassGuid,
  OUT     EFI_STRING_ID       *FormSetTitle,
  OUT     EFI_STRING_ID       *FormSetHelp
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
  EFI_GUID                     *ClassGuid;
  UINT8                        ClassGuidNum;

  ASSERT (Handle != NULL);
  ASSERT (SetupClassGuid != NULL);
  ASSERT (FormSetTitle != NULL);
  ASSERT (FormSetHelp != NULL);

  if ((Handle == NULL) || (SetupClassGuid == NULL) || (FormSetTitle == NULL) || (FormSetHelp == NULL)) {
    return FALSE;
  }

  *FormSetTitle = 0;
  *FormSetHelp  = 0;
  ClassGuidNum  = 0;
  ClassGuid     = NULL;

  //
  // Get HII PackageList
  //
  BufferSize = 0;
  HiiPackageList = NULL;
  Status = gHiiDatabase->ExportPackageLists (gHiiDatabase, Handle, &BufferSize, HiiPackageList);
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
    return FALSE;
  }

  Status = gHiiDatabase->ExportPackageLists (gHiiDatabase, Handle, &BufferSize, HiiPackageList);
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  //
  // Get Form package from this HII package List
  //
  Offset = sizeof (EFI_HII_PACKAGE_LIST_HEADER);
  Offset2 = 0;
  PackageListLength = ReadUnaligned32 (&HiiPackageList->PackageLength);

  while (Offset < PackageListLength) {
    Package = ((UINT8 *) HiiPackageList) + Offset;
    CopyMem (&PackageHeader, Package, sizeof (EFI_HII_PACKAGE_HEADER));

    if (PackageHeader.Type == EFI_HII_PACKAGE_FORMS) {
      //
      // Search FormSet Opcode in this Form Package
      //
      Offset2 = sizeof (EFI_HII_PACKAGE_HEADER);
      while (Offset2 < PackageHeader.Length) {
        OpCodeData = Package + Offset2;

        if (((EFI_IFR_OP_HEADER *) OpCodeData)->OpCode == EFI_IFR_FORM_SET_OP) {
          if (((EFI_IFR_OP_HEADER *) OpCodeData)->Length > OFFSET_OF (EFI_IFR_FORM_SET, Flags)) {
            //
            // Find FormSet OpCode
            //
            ClassGuidNum = (UINT8) (((EFI_IFR_FORM_SET *) OpCodeData)->Flags & 0x3);
            ClassGuid = (EFI_GUID *) (VOID *)(OpCodeData + sizeof (EFI_IFR_FORM_SET));
            if (IsShowsInPlatformSetupForm (SetupClassGuid, ClassGuid, ClassGuidNum)) {
              CopyMem (FormSetTitle, &((EFI_IFR_FORM_SET *) OpCodeData)->FormSetTitle, sizeof (EFI_STRING_ID));
              CopyMem (FormSetHelp, &((EFI_IFR_FORM_SET *) OpCodeData)->Help, sizeof (EFI_STRING_ID));
              FreePool (HiiPackageList);
              return TRUE;
            }
          } else if (CompareGuid (SetupClassGuid, &gEfiHiiPlatformSetupFormsetGuid)) {
             CopyMem (FormSetTitle, &((EFI_IFR_FORM_SET *) OpCodeData)->FormSetTitle, sizeof (EFI_STRING_ID));
             CopyMem (FormSetHelp, &((EFI_IFR_FORM_SET *) OpCodeData)->Help, sizeof (EFI_STRING_ID));
             FreePool (HiiPackageList);
             return TRUE;
          }
        }

        //
        // Go to next opcode
        //
        Offset2 += ((EFI_IFR_OP_HEADER *) OpCodeData)->Length;
      }
    }

    //
    // Go to next package
    //
    Offset += PackageHeader.Length;
  }

  FreePool (HiiPackageList);

  return FALSE;
}

//
//  Following are BDS Lib functions which contain all the code about setup browser reset reminder feature.
//  Setup Browser reset reminder feature is that an reset reminder will be given before user leaves the setup browser  if
//  user change any option setting which needs a reset to be effective, and  the reset will be applied according to  the user selection.
//


/**
  Enable the setup browser reset reminder feature.
  This routine is used in platform tip. If the platform policy need the feature, use the routine to enable it.

**/
VOID
EFIAPI
EnableResetReminderFeature (
  VOID
  )
{
  mFeaturerSwitch = TRUE;
}


/**
  Disable the setup browser reset reminder feature.
  This routine is used in platform tip. If the platform policy do not want the feature, use the routine to disable it.

**/
VOID
EFIAPI
DisableResetReminderFeature (
  VOID
  )
{
  mFeaturerSwitch = FALSE;
}


/**
  Record the info that a reset is required.
  A module boolean variable is used to record whether a reset is required.

**/
VOID
EFIAPI
EnableResetRequired (
  VOID
  )
{
  mResetRequired = TRUE;
}


/**
  Record the info that no reset is required.
  A module boolean variable is used to record whether a reset is required.

**/
VOID
EFIAPI
DisableResetRequired (
  VOID
  )
{
  mResetRequired = FALSE;
}


/**
  Check whether platform policy enable the reset reminder feature. The default is enabled.

**/
BOOLEAN
EFIAPI
IsResetReminderFeatureEnable (
  VOID
  )
{
  return mFeaturerSwitch;
}


/**
  Check if user changed any option setting which needs a system reset to be effective.

**/
BOOLEAN
EFIAPI
IsResetRequired (
  VOID
  )
{
  return mResetRequired;
}

/**
  Create reminder to let user to choose save or discard the changed browser data.
  If user save the changes, this fucntion may need to reset based on changes attribute.

  @param NeedReset                                    Whether need to do the reset action.

  @retval EFI_BROWSER_ACTION_REQUEST_EXIT             Browser exit request.
  @retval EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD     Browser discard request.

**/
UINTN
EFIAPI
SetupChangesReminder (
  IN  BOOLEAN         NeedReset
  )
{
  EFI_INPUT_KEY                 Key;
  CHAR16                        *StringBuffer1;
  CHAR16                        *StringBuffer2;
  CHAR16                        *YesString;
  CHAR16                        *NoString;
  CHAR16                        YesResponse;
  CHAR16                        NoResponse;
  UINTN                         ActionRequest;

  ActionRequest = EFI_BROWSER_ACTION_REQUEST_EXIT;

  if (gFormBrowserEx2->IsBrowserDataModified()) {
    //
    //Browser has data changed and not saved, popup a message to let user process.
    //
    StringBuffer1 = GetStringById (STRING_TOKEN (SAVE_CHANGES));
    StringBuffer2 = GetStringById (STRING_TOKEN (ARE_YOU_SURE));
    ASSERT (StringBuffer1 != NULL && StringBuffer2 != NULL);

    YesString = GetStringById (STRING_TOKEN (ARE_YOU_SURE_YES));
    NoString  = GetStringById (STRING_TOKEN (ARE_YOU_SURE_NO));
    ASSERT (YesString != NULL && NoString != NULL);

    if (StringBuffer1 == NULL || StringBuffer2 == NULL || YesString == NULL || NoString == NULL) {
      return EFI_BROWSER_ACTION_REQUEST_NONE;
    }

    YesResponse = YesString[0];
    NoResponse  = NoString[0];

    //
    // Popup a menu to notice user
    //
    do {
      CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, StringBuffer1, StringBuffer2, NULL);
    } while (
      ((Key.UnicodeChar | UPPER_LOWER_CASE_OFFSET) != (NoResponse  | UPPER_LOWER_CASE_OFFSET)) &&
      ((Key.UnicodeChar | UPPER_LOWER_CASE_OFFSET) != (YesResponse | UPPER_LOWER_CASE_OFFSET)) &&
      ((Key.UnicodeChar != CHAR_CARRIAGE_RETURN) && (Key.ScanCode != SCAN_ESC))
      );

    if ((Key.UnicodeChar | UPPER_LOWER_CASE_OFFSET) == (YesResponse | UPPER_LOWER_CASE_OFFSET)) {
      gFormBrowserEx2->ExecuteAction (BROWSER_ACTION_SUBMIT, 0);
      if (NeedReset && IsResetReminderFeatureEnable () && IsResetRequired ()) {
        gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
      }
    } else if ((Key.UnicodeChar | UPPER_LOWER_CASE_OFFSET) == (NoResponse | UPPER_LOWER_CASE_OFFSET)) {
      gFormBrowserEx2->ExecuteAction (BROWSER_ACTION_EXIT, 0);
      if (NeedReset && IsResetReminderFeatureEnable () && IsResetRequired ()) {
        gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
      }
    } else {
      ActionRequest = EFI_BROWSER_ACTION_REQUEST_FORM_DISCARD;
    }

    FreePool (StringBuffer1);
    FreePool (StringBuffer2);
    FreePool (YesString);
    FreePool (NoString);

  } else if (NeedReset) {
    //
    //check any reset required change is applied? if yes, notice the user and reset system
    //
    if (IsResetReminderFeatureEnable () && IsResetRequired ()) {
      StringBuffer1 = GetStringById (STRING_TOKEN (STR_CONFIRM_RESET_INFO));
      StringBuffer2 = GetStringById (STRING_TOKEN (STR_RESET_INPUT));
      ASSERT (StringBuffer1 != NULL && StringBuffer2 != NULL);

      //
      // Popup a menu to notice user
      //
      do {
        CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, StringBuffer1, StringBuffer2, NULL);
      } while (Key.UnicodeChar != CHAR_CARRIAGE_RETURN);

      FreePool (StringBuffer1);
      FreePool (StringBuffer2);

      gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
  }

  return ActionRequest;
}


/**
  This function converts an input device structure to a Unicode string.

  @param DevPath                  A pointer to the device path structure.

  @return A new allocated Unicode string that represents the device path.

**/
CHAR16 *
UiDevicePathToStr (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevPath
  )
{
  EFI_STATUS                       Status;
  CHAR16                           *ToText;
  EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *DevPathToText;

  if (DevPath == NULL) {
    return NULL;
  }

  Status = gBS->LocateProtocol (
                  &gEfiDevicePathToTextProtocolGuid,
                  NULL,
                  (VOID **) &DevPathToText
                  );
  ASSERT_EFI_ERROR (Status);
  ToText = DevPathToText->ConvertDevicePathToText (
                            DevPath,
                            FALSE,
                            TRUE
                            );
  ASSERT (ToText != NULL);
  return ToText;
}

/** @file
 Setup functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

#include <SetupCallbackList.h>
#include <SetupCallbackExList.h>
#include <InitStringList.h>
#include <Protocol/HiiConfigRouting.h>
#include <Protocol/HiiConfigAccess.h>
#include <Protocol/HiiString.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/DevicePath.h>
#include <Protocol/DxeSmmReadyToLock.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/HiiLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/DevicePathLib.h>
#include <Guid/GlobalVariable.h>
#include <Guid/MdeModuleHii.h>

#include <CommonDefinitions.h>
#include <Library/BiosIdLib.h>
#include "SetupPrivate.h"
#include <CpuRegs.h>
#include <PlatformNvRamHookLib.h>
#include <Protocol/MePlatformGetResetType.h>
#include "PlatformBoardId.h"
#include <Library/PciSegmentLib.h>
#include <Library/GpioLib.h>
#include <Protocol/VariableLock.h>
#include <ITbtInfoHob.h>
#include <DTbtInfoHob.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/PeiDxeSmmTwoLmLib.h>
#include <Library/CpuPlatformLib.h>
#include <Register/SaRegsHostBridge.h>
#include <Library/PchInfoLib.h>
#define GetSupportedLanguages(HiiHandle) HiiGetSupportedLanguages(HiiHandle)

#include <FspInfoHob.h>

#if FixedPcdGetBool(PcdITbtEnable) == 1
#include <TcssDataHob.h>
#endif

extern UINT8 SetupStrings[];
extern UINT8 MainBin[];
extern UINT8 AdvancedBin[];
extern UINT8 BootBin[];

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                         IsFirstBoot = FALSE;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                         HiiUpdateAtSetupEnter = FALSE;
GLOBAL_REMOVE_IF_UNREFERENCED SYSTEM_ACCESS                   SystemAccess;
GLOBAL_REMOVE_IF_UNREFERENCED SA_SETUP                        mSaSetup;
GLOBAL_REMOVE_IF_UNREFERENCED ME_SETUP                        mMeSetup;
GLOBAL_REMOVE_IF_UNREFERENCED CPU_SETUP                       mCpuSetup;
GLOBAL_REMOVE_IF_UNREFERENCED PCH_SETUP                       mPchSetup;
GLOBAL_REMOVE_IF_UNREFERENCED SETUP_DATA                      mSetupData;
GLOBAL_REMOVE_IF_UNREFERENCED SETUP_VOLATILE_DATA             mSetupVolatileData;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_HII_STRING_PROTOCOL         *gIfrLibHiiString = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_HII_DATABASE_PROTOCOL       *gIfrLibHiiDatabase = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_HII_CONFIG_ROUTING_PROTOCOL *mConfigRouting = NULL;
GLOBAL_REMOVE_IF_UNREFERENCED ME_PLATFORM_GET_RESET_TYPE_PROTOCOL mMePlatformGetResetType;

//
// Limited buffer size recommended by RFC4646 (4.3.  Length Considerations)
// (42 characters plus a NULL terminator)
//
#define RFC_3066_ENTRY_SIZE             (42 + 1)

typedef struct {
  EFI_HII_CONFIG_ACCESS_PROTOCOL Callback;
  UINT16 Class, SubClass;
} SETUP_CALLBACK;

typedef struct {
  EFI_GUID            FormSetGuid;
  UINT8               *IfrPack;
  UINT16              Class;
  UINT16              SubClass;
  EFI_HANDLE          DriverHandle;
} FORM_SET_INFO;

EFI_STATUS
EFIAPI
Callback (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN  EFI_BROWSER_ACTION                   Action,
  IN  EFI_QUESTION_ID                      KeyValue,
  IN  UINT8                                Type,
  IN  EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST           *ActionRequest
  );

VOID
EFIAPI
UpdateCallBack (
  CALLBACK_INFO *pCallBackFound
  );

CHAR8 *
EFIAPI
HiiLibGetBestLanguage (
  IN CHAR8        *SupportedLanguages,
  IN BOOLEAN      Iso639Language,
  ...
  );

VOID
InstallPlatfromReset (
  VOID
  );

extern
EFI_STATUS
EFIAPI
InitCpuMntrDefault (
  IN VOID
  );


/**
This function updates the Mem boot mode in setup back to 1LM if the current boot
mode is fallen back to 1LM. in this scenario it will also rest the EPOC 2LM bit and reset the system.

@retval EFI_SUCCESS            if the reboot is not required.
**/
EFI_STATUS
EFIAPI
UpdateTwoLmInfo (
  ) {
  EFI_STATUS                      Status;
  UINTN                           VariableSize;
  UINT32                          VariableAttributes;
  SA_SETUP                        SaSetup;
  TWOLM_INFO_HOB                  *TwoLmInfoHob;

  DEBUG ((EFI_D_INFO, "2LM: UpdateTwoLmSetupInfo\n"));
  TwoLmInfoHob = (TWOLM_INFO_HOB *)GetFirstGuidHob (&gTwoLmInfoHobGuid);
  if (TwoLmInfoHob == NULL) {
    DEBUG ((EFI_D_INFO, "2LM Info Hob not found\n"));
    return EFI_NOT_FOUND;
  }
  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  &VariableAttributes,
                  &VariableSize,
                  &SaSetup
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "2LM: Getvariable status = %r\n", Status));
    return Status;
  }
  if (TwoLmInfoHob->TwoLmInfo.CurrentMemBootMode == MEM_BOOT_MODE_1LM && SaSetup.MemBootMode == MEM_BOOT_MODE_2LM) {
    DEBUG ((EFI_D_INFO, "2LM: Update 2LM setup option to 1LM and reset the system\n"));

    SaSetup.MemBootMode = MEM_BOOT_MODE_1LM;
    DEBUG ((EFI_D_INFO, "2LM: updated setup to boot mode %d\n", SaSetup.MemBootMode));
    Status = gRT->SetVariable (
                    L"SaSetup",
                    &gSaSetupVariableGuid,
                    VariableAttributes,
                    VariableSize,
                    &SaSetup
                    );
    ASSERT_EFI_ERROR (Status);

    //Modify EPOC value
    UINT32 EpocValue = TwoLmGetEpoc ();
    DEBUG ((EFI_D_INFO, "2LM:  EPOC val is 0x%x\n", EpocValue));
    if (EpocValue & 0x1) {
      DEBUG ((EFI_D_INFO, "2LM: changing EPOC to 1LM\n"));
      TwoLmSetEpoc (EpocValue & (~0x1));
      DEBUG ((DEBUG_INFO, "EPOC is set to 0\n"));
    }
    //
    //RESET is Required since the EPOC/Setup value has changed
    //
    DEBUG ((DEBUG_INFO, "EPOC / Setup changed, triggering Reset\n"));
    gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
  }
  return EFI_SUCCESS;
}

SETUP_CALLBACK MainCallbackProtocol = {{NULL,NULL,Callback},MAIN_FORM_SET_CLASS,0};
SETUP_CALLBACK AdvancedCallbackProtocol = {{NULL,NULL,Callback},ADVANCED_FORM_SET_CLASS,0};
SETUP_CALLBACK BootCallbackProtocol = {{NULL,NULL,Callback},BOOT_FORM_SET_CLASS,0};

CALLBACK_INFO SetupCallBack[] = {
  // Last field in every structure will be filled by the Setup
  { NULL, &MainCallbackProtocol.Callback, MAIN_FORM_SET_CLASS, 0, 0},
  { NULL, &AdvancedCallbackProtocol.Callback, ADVANCED_FORM_SET_CLASS, 0, 0},
  { NULL, &BootCallbackProtocol.Callback, BOOT_FORM_SET_CLASS, 0, 0},
};

FORM_SET_INFO SetupFormSets[] = {
  {MAIN_FORM_SET_GUID, MainBin, MAIN_FORM_SET_CLASS, 0, NULL},
  {ADVANCED_FORM_SET_GUID, AdvancedBin, ADVANCED_FORM_SET_CLASS, 0, NULL},
  {BOOT_FORM_SET_GUID, BootBin, BOOT_FORM_SET_CLASS, 0, NULL},
};

BOOLEAN FormsetVisible[] = {
  TRUE, //Main formset is always displayed
  SHOW_ADVANCED_FORMSET, //Advanced formset
  TRUE, //Boot formset is always displayed; the Boot Manager part is diabled because of the conflict with EDKII BDS' one
  TRUE
};

#define NUMBER_OF_FORMSETS (sizeof(SetupCallBack) / sizeof(CALLBACK_INFO))

#pragma pack(1)
typedef struct {
  VENDOR_DEVICE_PATH             VendorDevicePath;
  EFI_DEVICE_PATH_PROTOCOL       End;
} HII_VENDOR_DEVICE_PATH;
#pragma pack()

HII_VENDOR_DEVICE_PATH  mHiiVendorDevicePathTemplate = {
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    ADVANCED_FORM_SET_GUID
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

EFI_STATUS
LocateHiiStringProtocol (
  OUT  EFI_HII_STRING_PROTOCOL **HiiStrProtocol
  )
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  if (NULL == (*HiiStrProtocol)) {
    Status = gBS->LocateProtocol (
                    &gEfiHiiStringProtocolGuid,
                    NULL,
                    (VOID **) HiiStrProtocol
                    );
  }
  return Status;
}

EFI_STATUS
LocateHiiDataBaseProtocol (
  OUT EFI_HII_DATABASE_PROTOCOL **HiiDataBaseProtocol
  )
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  if (NULL == (*HiiDataBaseProtocol)) {
    Status = gBS->LocateProtocol (
                    &gEfiHiiDatabaseProtocolGuid,
                    NULL,
                    (VOID **) HiiDataBaseProtocol
                    );
  }
  return Status;
}

VOID
EFIAPI
InitString (
  EFI_HII_HANDLE HiiHandle,
  EFI_STRING_ID  StrRef,
  CHAR16         *sFormat,
  ...
  )
{
  CHAR16      StringBuffer[1024];
  VA_LIST     ArgList;
  CHAR8       PlatformLanguage[RFC_3066_ENTRY_SIZE];
  CHAR8       *SupportedLanguages;
  CHAR8       *BestLanguage;
  UINTN       Size;
  EFI_STATUS  Status;

  //
  // Get current language setting
  //
  Size = sizeof (PlatformLanguage);
  Status = gRT->GetVariable (
                  L"PlatformLang",
                  &gEfiGlobalVariableGuid,
                  NULL,
                  &Size,
                  PlatformLanguage
                  );
  if (EFI_ERROR (Status)) {
    AsciiStrCpyS (PlatformLanguage, sizeof (PlatformLanguage) / sizeof (CHAR8), (CHAR8 *) "en-US");
  }

  SupportedLanguages = GetSupportedLanguages (HiiHandle);
  if (SupportedLanguages == NULL) {
    //
    // No supported language.
    //
    return;
  }
  //
  // Get the best matching language from SupportedLanguages
  //
  BestLanguage = HiiLibGetBestLanguage (
                   SupportedLanguages,
                   FALSE,                                             // RFC 4646 mode
                   PlatformLanguage,                                  // Highest priority
                   SupportedLanguages,                                // Lowest priority
                   NULL
                   );

  //
  // Construct string value.
  //
  VA_START(ArgList,sFormat);
  UnicodeVSPrint (StringBuffer,sizeof(StringBuffer),sFormat,ArgList);
  VA_END(ArgList);

  //
  // Set string
  //
  if (NULL == gIfrLibHiiString) {
    Status = gBS->LocateProtocol (
                    &gEfiHiiStringProtocolGuid,
                    NULL,
                    (VOID **) &gIfrLibHiiString
                    );
    if (EFI_ERROR (Status)) {
      return;
    }
  }

  gIfrLibHiiString->SetString (
                     gIfrLibHiiString,
                     HiiHandle,
                     StrRef,
                     BestLanguage,
                     StringBuffer,
                     NULL
                     );

  if (SupportedLanguages != NULL) {
    FreePool (SupportedLanguages);
  }

  if (BestLanguage != NULL) {
    FreePool (BestLanguage);
  }
}

#if FixedPcdGetBool(PcdFspWrapperEnable) == 1

EFI_STATUS
GetFspInformation (
  IN OUT FSP_INFO_HOB **FspInfo
  )
{
  EFI_HOB_GUID_TYPE  *GuidHob;

  GuidHob = NULL;
  GuidHob = GetFirstGuidHob (&gFspInfoGuid);
  ASSERT (GuidHob != NULL);
  if (GuidHob == NULL) {
    return EFI_NOT_FOUND;
  }

  *FspInfo = (FSP_INFO_HOB *) GET_GUID_HOB_DATA (GuidHob);

  return EFI_SUCCESS;
}

VOID
GetFspReleaseTime (
  IN OUT FSP_INFO_HOB  *FspInfo,
  CHAR16               FspReleaseDate[17]
  )
{
  FspReleaseDate[0] = FspInfo->TimeStamp[8];
  FspReleaseDate[1] = FspInfo->TimeStamp[9];
  FspReleaseDate[2] = (CHAR16) ((UINT8) (':'));
  FspReleaseDate[3] = FspInfo->TimeStamp[10];
  FspReleaseDate[4] = FspInfo->TimeStamp[11];
  FspReleaseDate[5] = ' ';
  FspReleaseDate[6] = FspInfo->TimeStamp[4];
  FspReleaseDate[7] = FspInfo->TimeStamp[5];
  FspReleaseDate[8] = (CHAR16) ((UINT8) ('/'));
  FspReleaseDate[9] = FspInfo->TimeStamp[6];
  FspReleaseDate[10] = FspInfo->TimeStamp[7];
  FspReleaseDate[11] = (CHAR16) ((UINT8) ('/'));
  FspReleaseDate[12] = FspInfo->TimeStamp[0];
  FspReleaseDate[13] = FspInfo->TimeStamp[1];
  FspReleaseDate[14] = FspInfo->TimeStamp[2];
  FspReleaseDate[15] = FspInfo->TimeStamp[3];
  FspReleaseDate[16] = (CHAR16) ((UINT8) ('\0'));
}

#endif

EFI_STATUS InitMain(EFI_HII_HANDLE HiiHandle, UINT16 Class)
{
  EFI_STATUS                        Status;
  CHAR16                            Version[100];         //Assuming that strings are < 100 UCHAR
  CHAR16                            ReleaseDate[100];     //Assuming that strings are < 100 UCHAR
  CHAR16                            ReleaseTime[100];     //Assuming that strings are < 100 UCHAR
#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
  CHAR16                            FspReleaseTime[17];
  FSP_INFO_HOB                      *FspInfo;
#endif

  if (Class != MAIN_FORM_SET_CLASS) {
    return EFI_SUCCESS;
  }

  ///////////////// BIOS /////////////////////////////////////
  if (gST->FirmwareVendor)
    InitString(
      HiiHandle,STRING_TOKEN(STR_BIOS_VENDOR_VALUE),
      L"%s", gST->FirmwareVendor
    );
  else
    InitString(
      HiiHandle,STRING_TOKEN(STR_BIOS_VENDOR_VALUE),
      L"%s", L"Intel "
    );

  if (PcdGet8 (PcdClientCommonVersionRCRev) == 0xFF) {
    InitString(
      HiiHandle,STRING_TOKEN(STR_BIOS_CORE_VERSION_VALUE),
      L"%0d.%0d.%0d.%0d RP0%0d",
      PcdGet8 (PcdClientCommonVersionMajor),
      PcdGet8 (PcdClientCommonVersionMinor),
      PcdGet8 (PcdClientCommonVersionRevision),
      PcdGet8 (PcdClientCommonVersionBuild),
      PcdGet8 (PcdClientCommonVersionRoyalParkBuild)
    );
  } else {
    InitString(
      HiiHandle,STRING_TOKEN(STR_BIOS_CORE_VERSION_VALUE),
      L"%0d.%0d.%0d.%0d RC0%0d RP0%0d",
      PcdGet8 (PcdClientCommonVersionMajor),
      PcdGet8 (PcdClientCommonVersionMinor),
      PcdGet8 (PcdClientCommonVersionRevision),
      PcdGet8 (PcdClientCommonVersionBuild),
      PcdGet8 (PcdClientCommonVersionRCRev),
      PcdGet8 (PcdClientCommonVersionRoyalParkBuild)
    );
  }

  InitString(
    HiiHandle,STRING_TOKEN(STR_BIOS_CLIENT_SILICON_VERSION_VALUE),
    L"%0d.%0d.%0d.%0d",
    PcdGet8 (PcdClientSiliconVersionMajor),
    PcdGet8 (PcdClientSiliconVersionMinor),
    PcdGet8 (PcdClientSiliconVersionRevision),
    PcdGet8 (PcdClientSiliconVersionBuild)
  );

  Status = GetBiosVersionDateTime (Version, ReleaseDate, ReleaseTime);
  if (!EFI_ERROR (Status)) {
    InitString(
      HiiHandle,STRING_TOKEN(STR_BIOS_VERSION_VALUE),
      L"%s", Version
    );
    InitString(
      HiiHandle,STRING_TOKEN(STR_BIOS_DATE_VALUE),
      L"%s %s", ReleaseTime, ReleaseDate
    );
  }

#if FixedPcdGetBool(PcdFspWrapperEnable) == 1

  //
  // Update FSP Information.
  //
  Status = GetFspInformation (&FspInfo);
  if (! EFI_ERROR (Status)) {
    InitString (
      HiiHandle,STRING_TOKEN (STR_FSP_VERSION_VALUE),
      L"%02x.%02x.%02x.%02x",
      FspInfo->SiliconInitVersionMajor,
      FspInfo->SiliconInitVersionMinor,
      FspInfo->FspVersionRevision,
      FspInfo->FspVersionBuild
      );

    InitString (
      HiiHandle,STRING_TOKEN (STR_RC_VERSION_VALUE),
      L"%02x.%02x.%02x.%02x",
      FspInfo->SiliconInitVersionMajor,
      FspInfo->SiliconInitVersionMinor,
      FspInfo->SiliconInitVersionRevision,
      FspInfo->SiliconInitVersionBuild
      );

    GetFspReleaseTime (FspInfo,FspReleaseTime);
    InitString (
      HiiHandle,STRING_TOKEN (STR_BUILD_DATE_VALUE),
      L"%s", FspReleaseTime
      );
  } else {
    DEBUG ((DEBUG_ERROR, "Get FSP Information Failed : %r\n", Status));
  }
#endif

  return EFI_SUCCESS;
}

typedef EFI_STATUS (INIT_FUNCTION)(EFI_HII_HANDLE HiiHandle, UINT16 Class);

extern INIT_FUNCTION INIT_LIST EndOfInitList;
#if FixedPcdGetBool(PcdNct677FPresent) == 1
extern INIT_FUNCTION NctUpdateHwmonString;
#endif

INIT_FUNCTION* InitList[] = { InitMain, INIT_LIST
#if FixedPcdGetBool(PcdNct677FPresent) == 1
                              NctUpdateHwmonString,
#endif
                              NULL };


VOID InitParts(EFI_HII_HANDLE HiiHandle, UINT16 Class)
{
  UINTN i;
  for(i=0; InitList[i]; i++) InitList[i](HiiHandle,Class);
}

VOID
EFIAPI
InitStrings (
  IN EFI_EVENT Event,
  IN VOID *Context
  )
{
  EFI_STATUS Status;
  UINTN      Index;
  VOID       *Protocol;

  if (!HiiUpdateAtSetupEnter) {
    Status = gBS->LocateProtocol(
                    &gBdsAllDriversConnectedProtocolGuid,
                    NULL,
                    &Protocol
                    );
    if (EFI_ERROR (Status)) {
      return ;
    }
  } else {
    Status = gBS->LocateProtocol(
                    &gSetupEnterGuid,
                    NULL,
                    &Protocol
                    );
    if (EFI_ERROR (Status)) {
      return ;
    }
  }

  for (Index = 0; Index < NUMBER_OF_FORMSETS; Index ++) {
    if (SetupCallBack[Index].HiiHandle == NULL) {
      continue;
    }

    InitParts(SetupCallBack[Index].HiiHandle, SetupCallBack[Index].Class);
  }

  gBS->CloseEvent (Event);
}

VOID
InstallHiiResources (
  VOID
  )
{
  CALLBACK_INFO          *pCallBackFound;
  UINTN                  Index;
  EFI_HII_HANDLE         HiiHandle;
  EFI_HANDLE             DriverHandle;
  EFI_STATUS             Status;
  HII_VENDOR_DEVICE_PATH *mHiiVendorDevicePath;

  pCallBackFound = NULL;

  for (Index = 0; Index < NUMBER_OF_FORMSETS; Index++) {
    pCallBackFound = &SetupCallBack[Index];
    UpdateCallBack (pCallBackFound);
    DEBUG ((DEBUG_INFO, " InstallHiiResources: UpdateCallBack was done.\n"));

    DriverHandle = NULL;
    mHiiVendorDevicePath = NULL;
    mHiiVendorDevicePath = AllocateCopyPool (sizeof (HII_VENDOR_DEVICE_PATH), &mHiiVendorDevicePathTemplate);
    ASSERT (mHiiVendorDevicePath != NULL);
    if (mHiiVendorDevicePath == NULL) {
      return;
    }
    mHiiVendorDevicePath->VendorDevicePath.Guid = SetupFormSets[Index].FormSetGuid;

    //
    // Install Config Access protocol
    //
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &DriverHandle,
                    &gEfiDevicePathProtocolGuid,
                    mHiiVendorDevicePath,
                    &gEfiHiiConfigAccessProtocolGuid,
                    pCallBackFound->pFormCallback,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);

    //
    // Publish our HII data
    //
    HiiHandle = HiiAddPackages (
                   &SetupFormSets[Index].FormSetGuid,
                   DriverHandle,
                   SetupStrings,
                   SetupFormSets[Index].IfrPack,
                   NULL
                   );
    ASSERT (HiiHandle != NULL);
    DEBUG ((DEBUG_INFO, " InstallHiiResources: HiiPackages was added.\n"));

    if (pCallBackFound) {
      pCallBackFound->HiiHandle = HiiHandle;
    }

    pCallBackFound = NULL;
  }

}

VOID
EFIAPI
BackupSetupDataAndCheckForPassword (
  IN EFI_EVENT Event,
  IN VOID *Context
  )
{
  UINTN                VariableSize;
  SA_SETUP             SaSetup;
  ME_SETUP             MeSetup;
  CPU_SETUP            CpuSetup;
  PCH_SETUP            PchSetup;
  SI_SETUP             SiSetup;
  SETUP_DATA           SetupData;
  EFI_STATUS           Status;
  VOID                 *Protocol;

  Status = gBS->LocateProtocol (
                  &gSetupEnterGuid,
                  NULL,
                  &Protocol
                  );
  if (EFI_ERROR (Status)) {
    return ;
  }

  //
  // Signal check for password
  //
  REPORT_STATUS_CODE (
    EFI_PROGRESS_CODE,
    (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_PC_USER_SETUP)
    );

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupData
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gRT->SetVariable (
                  L"ColdReset",
                  &gSetupVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  VariableSize,
                  &SetupData
                  );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SaSetup
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gRT->SetVariable (
                  L"SaColdReset",
                  &gSaSetupVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  VariableSize,
                  &SaSetup
                  );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (ME_SETUP);
  Status = gRT->GetVariable (
                  L"MeSetup",
                  &gMeSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &MeSetup
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gRT->SetVariable (
                  L"MeColdReset",
                  &gMeSetupVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  VariableSize,
                  &MeSetup
                  );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &CpuSetup
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gRT->SetVariable (
                  L"CpuColdReset",
                  &gCpuSetupVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  VariableSize,
                  &CpuSetup
                  );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (PCH_SETUP);
  Status = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &PchSetup
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gRT->SetVariable (
                  L"PchColdReset",
                  &gPchSetupVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  VariableSize,
                  &PchSetup
                  );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (SI_SETUP);
  Status = gRT->GetVariable(
                  L"SiSetup",
                  &gSiSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SiSetup
                  );
  ASSERT_EFI_ERROR(Status);

  Status = gRT->SetVariable(
                  L"SiColdReset",
                  &gSiSetupVariableGuid,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  VariableSize,
                  &SiSetup
                  );
  ASSERT_EFI_ERROR(Status);

  gBS->CloseEvent (Event);
}

VOID
SetupCallback (
  IN EFI_EVENT   Event,
  IN VOID        *Context
  )
{
  static BOOLEAN         ResourcesLoaded = FALSE;
  UINT32                 Index;
  EFI_STATUS             Status;
  UINTN                  VariableSize;
  SETUP_DATA             SetupData;
  VOID                   *SetupRegistration;
  VOID                   *BdsDriverConnectRegistration;
  EFI_BOOT_MODE          BootMode;

  if (!ResourcesLoaded) {
    ResourcesLoaded = TRUE;

    Status = gBS->LocateProtocol (
                    &gEfiHiiConfigRoutingProtocolGuid,
                    NULL,
                    (VOID **) &mConfigRouting
                    );
    ASSERT_EFI_ERROR (Status);
    DEBUG ((DEBUG_INFO, " SetupCallback: EfiHiiConfigRoutingProtocolGuid was found.\n"));

    InitCpuMntrDefault();

    InstallHiiResources();
    DEBUG ((DEBUG_INFO, " SetupCallback: HiiResources was installed.\n"));

    VariableSize = sizeof(SETUP_DATA);
    Status = gRT->GetVariable (
                    L"Setup",
                    &gSetupVariableGuid,
                    NULL,
                    &VariableSize,
                    &SetupData
                    );
    ASSERT_EFI_ERROR (Status);
    DEBUG ((DEBUG_INFO, " SetupCallback: SetupVar was found.\n"));

    if (!EFI_ERROR(Status) && (SetupData.FastBoot)) {
      BootMode = GetBootModeHob();
      DEBUG ((DEBUG_INFO, " BootModeHob was found.\n"));

      if ((SetupData.SkipHIIUpdate) &&
         ((BootMode == BOOT_WITH_MINIMAL_CONFIGURATION) ||
          (BootMode == BOOT_ON_S4_RESUME) ||
          (BootMode == BOOT_ASSUMING_NO_CONFIGURATION_CHANGES))) {
        HiiUpdateAtSetupEnter = TRUE;
      }
    }

    if (!HiiUpdateAtSetupEnter) {
      EfiCreateProtocolNotifyEvent(
         &gBdsAllDriversConnectedProtocolGuid,
         TPL_CALLBACK,
         InitStrings,
         NULL,
         &BdsDriverConnectRegistration
         );
    } else {
      EfiCreateProtocolNotifyEvent(
         &gSetupEnterGuid,
         TPL_CALLBACK,
         InitStrings,
         NULL,
         &SetupRegistration
         );
    }

    EfiCreateProtocolNotifyEvent(
       &gSetupEnterGuid,
       TPL_CALLBACK,
       BackupSetupDataAndCheckForPassword,
       NULL,
       &SetupRegistration
       );
  }

  for (Index = 0; Index < NUMBER_OF_FORMSETS; Index++) {
    if (!FormsetVisible[Index] && SetupCallBack[Index].HiiHandle != NULL) {
      gIfrLibHiiDatabase->RemovePackageList (gIfrLibHiiDatabase, SetupCallBack[Index].HiiHandle);
      SetupCallBack[Index].HiiHandle = NULL;
    }
  }

  DEBUG ((DEBUG_INFO, " SetupCallback was done.\n"));
}

EFI_STATUS
EFIAPI
SetupEntry (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
#if ( FORCE_USER_TO_SETUP_ON_FIRST_BOOT || FORCE_USER_TO_SETUP_IF_BOOT_WITH_DEFAULT )
  static UINT32 BootFlow = BOOT_FLOW_CONDITION_FIRST_BOOT;
#endif

  UINTN                           Size;
  EFI_STATUS                      Status;
  UINT32                          RegEAX, RegEBX, RegECX, RegEDX;
  SA_SETUP                        *pSaSetup;
  PCH_SETUP                       *pPchSetup;
  CPU_SETUP_VOLATILE_DATA         CpuSetupVolData;
  CPU_SETUP_VOLATILE_DATA         *pCpuSetupVolData;
  UINT8                           InitSetupFlag;
  OS_PROFILE                      OsProfileData;
  UINTN                           OsProfileSize;
  UINT32                          OsProfileAttr;
  UINT32                          VariableAttributes;
  UINT32                          SetupVolVarAttr;
  UINT32                          CpuSetupVolVarAttr;
  UINT32                          TbtSetupVolatileDataAttr;
  TBT_SETUP_VOLATILE_DATA         TbtSetupVolatileVar;
  TBT_SETUP_VOLATILE_DATA         *pTbtSetupVolatileVar;
  UINT32                          InitSetupVolVarAttr;
  EFI_HANDLE                      DriverHandle;
  EDKII_VARIABLE_LOCK_PROTOCOL    *VariableLockProtocol;
  UINT64                          HbPciD0F0RegBase;
  UINT8                           Index;
#if FixedPcdGetBool(PcdITbtEnable) == 1
  BOOLEAN                         SetupItbtDataModified;
  UINT32                          Data32;
  TCSS_DATA_HOB                   *TcssHob;
#endif

#if FixedPcdGetBool(PcdITbtEnable) == 1
  TcssHob = NULL;
#endif
  ZeroMem (&mSetupData, sizeof(mSetupData));
  ZeroMem (&mSetupVolatileData, sizeof(mSetupVolatileData));
  ZeroMem (&SystemAccess, sizeof(SystemAccess));
  ZeroMem (&TbtSetupVolatileVar, sizeof(TbtSetupVolatileVar));

  // Init gIfrLibHiiString
  Status = LocateHiiStringProtocol (&gIfrLibHiiString);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  // Init gIfrLibHiiDatabase
  Status = LocateHiiDataBaseProtocol (&gIfrLibHiiDatabase);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get SetupVolatileData Variable
  //
  Size = sizeof (SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  &SetupVolVarAttr,
                  &Size,
                  &mSetupVolatileData
                  );
  ASSERT_EFI_ERROR (Status);

  CpuSetupVolVarAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
  Size = sizeof (CPU_SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable (
                  L"CpuSetupVolatileData",
                  &gCpuSetupVariableGuid,
                  &CpuSetupVolVarAttr,
                  &Size,
                  &CpuSetupVolData
                  );
  if (Status == EFI_NOT_FOUND) {
    Status = gRT->SetVariable (
                    L"CpuSetupVolatileData",
                    &gCpuSetupVariableGuid,
                    CpuSetupVolVarAttr,
                    sizeof (CpuSetupVolData),
                    &CpuSetupVolData
                    );
    ASSERT_EFI_ERROR (Status);
  }

  TbtSetupVolatileDataAttr = EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
  Size = sizeof(TBT_SETUP_VOLATILE_DATA);
  Status = gRT->GetVariable(
                  L"TbtSetupVolatileData",
                  &gSetupVariableGuid,
                  &TbtSetupVolatileDataAttr,
                  &Size,
                  &TbtSetupVolatileVar
                  );
  if (Status == EFI_NOT_FOUND) {
    Status = gRT->SetVariable(
                    L"TbtSetupVolatileData",
                    &gSetupVariableGuid,
                    TbtSetupVolatileDataAttr,
                    sizeof(TbtSetupVolatileVar),
                    &TbtSetupVolatileVar
                    );
     ASSERT_EFI_ERROR(Status);
  }
  //
  // Get VTd status
  //
  HbPciD0F0RegBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  mSetupVolatileData.VTdAvailable = (PciSegmentRead32 (HbPciD0F0RegBase + 0xe4) & BIT23) ? 0 : 1;

  //
  // Set SetupVolatileData Variable
  //
  Status = gRT->SetVariable (
                  L"SetupVolatileData",
                  &gSetupVariableGuid,
                  SetupVolVarAttr,
                  sizeof (mSetupVolatileData),
                  &mSetupVolatileData
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Check whether first boot.
  //
  InitSetupVolVarAttr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
  Size = sizeof (InitSetupFlag);
  Status = gRT->GetVariable (L"InitSetupVariable", &gSetupVariableGuid, &InitSetupVolVarAttr, &Size, &InitSetupFlag);
  if (Status == EFI_NOT_FOUND) {
    IsFirstBoot   = TRUE;
    InitSetupFlag = 1;
    gRT->SetVariable (
           L"InitSetupVariable",
           &gSetupVariableGuid,
           InitSetupVolVarAttr,
           sizeof (InitSetupFlag),
           &InitSetupFlag
           );
  }

  //
  // Check Setup Variable.
  // Setup Variable should always exist, because post build will create the default setup variable.
  //
#if FixedPcdGetBool(PcdITbtEnable) == 1
  Size = sizeof (mSetupData);
  Status = gRT->GetVariable(L"Setup", &gSetupVariableGuid, &VariableAttributes, &Size, &mSetupData);
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR(Status)) {
      SetupItbtDataModified = FALSE;
      //
      // Get status of each iTBT PCIe RP is enabled or not.
      //
      TcssHob = (TCSS_DATA_HOB *)GetFirstGuidHob(&gTcssHobGuid);
      if (TcssHob != NULL) {
        for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
          //
          // Check each iTBT PCIe RP is enabled or not.
          //
          if (mSetupData.ITbtPcieRootPortSupported[Index] != TcssHob->TcssData.ItbtPcieRpEn[Index]) {
            mSetupData.ITbtPcieRootPortSupported[Index] = TcssHob->TcssData.ItbtPcieRpEn[Index];
            SetupItbtDataModified = TRUE;
          }
        }
      }

      if (SetupItbtDataModified) {
          gRT->SetVariable(
              L"Setup",
              &gSetupVariableGuid,
              VariableAttributes,
              sizeof(mSetupData),
              &mSetupData
              );
      }
  }
#endif

  Size = sizeof (mMeSetup);
  Status = gRT->GetVariable(L"MeSetup", &gMeSetupVariableGuid, &VariableAttributes, &Size, &mMeSetup);
  ASSERT_EFI_ERROR (Status);

  Size = sizeof (mCpuSetup);
  Status = gRT->GetVariable(L"CpuSetup", &gCpuSetupVariableGuid, &VariableAttributes, &Size, &mCpuSetup);
  ASSERT_EFI_ERROR (Status);

  Size = sizeof (mPchSetup);
  Status = gRT->GetVariable(L"PchSetup", &gPchSetupVariableGuid, &VariableAttributes, &Size, &mPchSetup);
  ASSERT_EFI_ERROR (Status);

  //
  // Check whether exist the "SystemAccess" info, if not exist, initialize it to Zero.
  //
  Size = sizeof (SystemAccess);
  Status = gRT->GetVariable(L"SystemAccess", &gSystemAccessGuid, NULL, &Size, &SystemAccess);

  //
  // Need to lock SystemAccess variable to prevent changing by some malicious software
  //
  Status = gBS->LocateProtocol (&gEdkiiVariableLockProtocolGuid, NULL, (VOID **)&VariableLockProtocol);
  if (!EFI_ERROR (Status)) {
    Status = VariableLockProtocol->RequestToLock (
                                     VariableLockProtocol,
                                     L"SystemAccess",
                                     &gSystemAccessGuid
                                     );
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "System Access Variable unable to be locked: Status = %r\n", Status));
    }
  }

  DEBUG ((DEBUG_INFO, " SetupEntry: Setup variables were found\n"));

  //
  // Update SaSetup variables
  //
  Size = sizeof (mSaSetup);
  Status = gRT->GetVariable(L"SaSetup", &gSaSetupVariableGuid, &VariableAttributes, &Size, &mSaSetup);
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR (Status)) {
    pSaSetup = (SA_SETUP *) &mSaSetup;
    pSaSetup->GtDid = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 2, 0, 2));
    gRT->SetVariable (
           L"SaSetup",
           &gSaSetupVariableGuid,
           VariableAttributes,
           sizeof (mSaSetup),
           &mSaSetup
           );
  }

  //
  // Update CPU Volatile variables
  //
  AsmCpuid(1, &RegEAX, &RegEBX, &RegECX, &RegEDX);

  pPchSetup = (PCH_SETUP *) &mPchSetup;
  pCpuSetupVolData = (CPU_SETUP_VOLATILE_DATA *) &CpuSetupVolData;
  pTbtSetupVolatileVar = (TBT_SETUP_VOLATILE_DATA *)&TbtSetupVolatileVar;
  pPchSetup->RootPortDid = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0, 0, 2)); // @todo: fix RP DID.
  for (Index = 0; Index < PCH_MAX_PCIE_ROOT_PORTS ; Index++) {
    pPchSetup->PcieRootPortMVCESupported[Index] = (UINT8) IsRpMultiVC (Index);
  }
  pCpuSetupVolData->CpuFamilyModel = (UINT16) RegEAX & 0x3FF0;  // @todo to use the CPU lib instead of reading the registers directly
  pCpuSetupVolData->CpuExtendedFamilyModel = (UINT16) ((RegEAX >> 16) & 0x0FFF);
  pCpuSetupVolData->CpuStepping = (UINT8) RegEAX & 0xF;


  if ((AsmReadMsr64(MSR_PLATFORM_INFO) & B_MSR_PLATFORM_INFO_EDRAM_ENABLE_MASK) == B_MSR_PLATFORM_INFO_EDRAM_ENABLE_MASK) {
    pCpuSetupVolData->EdramSupported = TRUE;
  } else {
    pCpuSetupVolData->EdramSupported = FALSE;
  }

  pTbtSetupVolatileVar->DTbtContollersNumber = PcdGet8(PcdDTbtControllerNumber);
  pTbtSetupVolatileVar->ITbtRootPortsNumber = PcdGet8(PcdITbtRootPortNumber);

  gRT->SetVariable (
         L"PchSetup",
         &gPchSetupVariableGuid,
         VariableAttributes,
         sizeof (mPchSetup),
         &mPchSetup
         );

  gRT->SetVariable (
         L"CpuSetupVolatileData",
         &gCpuSetupVariableGuid,
         CpuSetupVolVarAttr,
         sizeof (CpuSetupVolData),
         &CpuSetupVolData
         );
  Status = gRT->SetVariable(
         L"TbtSetupVolatileData",
         &gSetupVariableGuid,
         TbtSetupVolatileDataAttr,
         sizeof(TbtSetupVolatileVar),
         &TbtSetupVolatileVar
         );

  DEBUG ((DEBUG_INFO, " SetupEntry: Setup variables were updated\n"));

  //
  // Always install HII resources
  //
  SetupCallback(NULL, NULL);

  DEBUG ((DEBUG_INFO, " SetupEntry: SetupCallback was done.\n"));

  Status = gIfrLibHiiDatabase->GetPackageListHandle (gIfrLibHiiDatabase, SetupCallBack[1].HiiHandle, &DriverHandle);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, " SetupEntry: Not found driver handle for SetupCallBack[1]\n"));
    return EFI_INVALID_PARAMETER;
  }

#if FORCE_USER_TO_SETUP_ON_FIRST_BOOT
  if (IsFirstBoot) {
    Status = gRT->GetVariable(L"BootFlow", &gBootFlow, NULL, &Size, NULL);
    if (Status == EFI_NOT_FOUND) {
    ClearDiagnosticStatus ();
      return gRT->SetVariable (
                    L"BootFlow",
                    &gBootFlow,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS,
                    sizeof(BootFlow),
                    &BootFlow
                    );
    }
  }
#endif

  DEBUG ((DEBUG_INFO, " SetupEntry: HII resources was installed\n"));
  //
  // Register platform reset callback
  //
  InstallPlatfromReset ();

  DEBUG ((DEBUG_INFO, " SetupEntry: PlatformReset was installed\n"));

#if FORCE_USER_TO_SETUP_IF_BOOT_WITH_DEFAULT
  if (IsChecksumBad() || (BOOT_WITH_DEFAULT_SETTINGS == GetBootModeHob())) {
    DEBUG ((DEBUG_INFO, "Secondary NvRam bad, force user to enter setup.\n"));
  ClearDiagnosticStatus ();

  if (!IsChecksumBad()) {
      //
      // Setup configuration is changed to default, system reset is required
      //
      gRT->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
    }
    return gRT->SetVariable (
                  L"BootFlow",
                  &gBootFlow,
                  EFI_VARIABLE_BOOTSERVICE_ACCESS,
                  sizeof(BootFlow),
                  &BootFlow
                  );
  }
#endif

  // OS Profile related update:
  // Need to check this in every boot
  OsProfileSize = sizeof (OS_PROFILE);
  Status = gRT->GetVariable(
                  L"OsProfile",
                  &gOsProfileGuid,
                  &OsProfileAttr,
                  &OsProfileSize,
                  &OsProfileData
                  );
  DEBUG((DEBUG_INFO, "\n In Setup Entry, GetVariable OsProfile Status = %r, attributes = %X \n", Status, OsProfileAttr));

  if (EFI_ERROR(Status)) {
    if (Status == EFI_NOT_FOUND) {
      OsProfileData.OsProfile = OsNone;
      OsProfileData.PrevOs = OsNone;
      OsProfileAttr = EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS;
      OsProfileSize = sizeof (OS_PROFILE);

      Status = gRT->SetVariable (
                      L"OsProfile",
                      &gOsProfileGuid,
                      OsProfileAttr,
                      OsProfileSize,
                      &OsProfileData
                      );
      DEBUG(( DEBUG_INFO, "SetVariable OsProfile Status = %r \n", Status ));
    }
  } else if ( OsProfileData.PrevOs != OsProfileData.OsProfile ) {
    OsProfileData.PrevOs = OsProfileData.OsProfile;

    Status = gRT->SetVariable (
                    L"OsProfile",
                    &gOsProfileGuid,
                    OsProfileAttr,
                    OsProfileSize,
                    &OsProfileData
                    );
    DEBUG(( DEBUG_INFO, "SetVariable OsProfile Status = %r \n", Status ));
  }

  return EFI_SUCCESS;
}

typedef VOID (UPDATE_ITEM)(EFI_HII_HANDLE HiiHandle, UINT16 Class, UINT16 SubClass, UINT16 Key);

typedef struct {
  UINT16 Class, SubClass, Key;
  UPDATE_ITEM *UpdateItem;
} SETUP_ITEM_CALLBACK;

#define ITEM_CALLBACK(Class,Subclass,Key,Callback) Callback
extern UPDATE_ITEM SETUP_ITEM_CALLBACK_LIST EndOfList;
#undef ITEM_CALLBACK

#define ITEM_CALLBACK(Class,Subclass,Key,Callback) {Class,Subclass,Key,&Callback}
SETUP_ITEM_CALLBACK SetupItemCallback[] = { SETUP_ITEM_CALLBACK_LIST {0,0,0,NULL} };
#undef ITEM_CALLBACK

typedef EFI_STATUS (UPDATE_ITEM_EX)(CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This, EFI_BROWSER_ACTION Action, EFI_QUESTION_ID KeyValue, UINT8 Type, EFI_IFR_TYPE_VALUE *Value, EFI_BROWSER_ACTION_REQUEST *ActionRequest );

typedef struct {
  UINT16 Class, SubClass, Key;
  UPDATE_ITEM_EX *UpdateItemEx;
} SETUP_ITEM_CALLBACK_EX;

#define ITEM_CALLBACK_EX(Class,Subclass,Key,Callback) Callback
extern UPDATE_ITEM_EX SETUP_ITEM_CALLBACK_LIST_EX EndOfListEx;
#undef ITEM_CALLBACK_EX

#define ITEM_CALLBACK_EX(Class,Subclass,Key,Callback) {Class,Subclass,Key,&Callback}
SETUP_ITEM_CALLBACK_EX SetupItemCallbackEx[] = { SETUP_ITEM_CALLBACK_LIST_EX {0,0,0,NULL} };
#undef ITEM_CALLBACK_EX

EFI_STATUS
EFIAPI
Callback (
  IN CONST EFI_HII_CONFIG_ACCESS_PROTOCOL *This,
  IN EFI_BROWSER_ACTION                   Action,
  IN EFI_QUESTION_ID                      KeyValue,
  IN UINT8                                Type,
  IN EFI_IFR_TYPE_VALUE                   *Value,
  OUT EFI_BROWSER_ACTION_REQUEST          *ActionRequest
  )
{
  UINTN                  Index;
  SETUP_CALLBACK         *pCallback = (SETUP_CALLBACK*)This;
  EFI_STATUS             Status = EFI_UNSUPPORTED;
  SETUP_ITEM_CALLBACK    *pItemCallback = SetupItemCallback;
  SETUP_ITEM_CALLBACK_EX *pItemCallbackEx = SetupItemCallbackEx;

  for (Index = 0; Index < NUMBER_OF_FORMSETS; Index++) {
    if (SetupCallBack[Index].Class == pCallback->Class && SetupCallBack[Index].SubClass == pCallback->SubClass)
    {
      while (pItemCallback->UpdateItem)
      {
        if (pItemCallback->Class == pCallback->Class &&
            pItemCallback->SubClass == pCallback->SubClass &&
            pItemCallback->Key == KeyValue) {
          pItemCallback->UpdateItem (
                           SetupCallBack[Index].HiiHandle,
                           pItemCallback->Class,
                           pItemCallback->SubClass,
                           KeyValue
                           );
        }
        pItemCallback++;
      }
      while (pItemCallbackEx->UpdateItemEx)
      {
        if (pItemCallbackEx->Class == pCallback->Class &&
            pItemCallbackEx->SubClass == pCallback->SubClass &&
            pItemCallbackEx->Key == KeyValue) {
          Status = pItemCallbackEx->UpdateItemEx(This, Action, KeyValue, Type, Value, ActionRequest);
        }
        pItemCallbackEx++;
      }
    }
  }
  return Status;
}


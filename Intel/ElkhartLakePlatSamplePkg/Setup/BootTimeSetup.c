/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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
#include <BootTime.h>

/**
  Print boot time to HII

  @param[in]  HiiHandle
**/
VOID
PrintBootTimeToHii (
  IN EFI_HII_HANDLE HiiHandle
  )
{
  UINTN           i;
  EFI_STATUS      Status;
  UINTN           VariableSize;
  BOOTTIME_TABLE  BoottimeLogs;
  BOOTTIME_ENTRY  *Entry;
  CHAR16          StringBuffer[32];
  CHAR16          HelpString[256];
  UINTN           ms;

  DEBUG ((DEBUG_INFO, "<PrintBootTime_START>"));

  VariableSize = sizeof (BOOTTIME_TABLE);
  Status = gRT->GetVariable (
                  L"BootTimeLog",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &BoottimeLogs
                  );
  if (EFI_ERROR (Status)) {
    BoottimeLogs.Length = 0;
  }

  StrCpyS (HelpString, sizeof (HelpString) / sizeof (CHAR16), L"");
  for (i = 0; i < BoottimeLogs.Length; i++) {
    Entry = &BoottimeLogs.Buffer[i];
    ms = Entry->Time;
    UnicodeSPrint (StringBuffer,32, L"%d:%dms", i+1, ms);
//    if (Entry->Flags & QUIET_BOOT)
//      StrCat (StringBuffer, L",QB");
//    if (Entry->Flags & FAST_BOOT)
//      StrCat (StringBuffer, L",FB");
    if (Entry->Flags & LEGACY_BOOT)
      StrCatS (StringBuffer, sizeof (StringBuffer) / sizeof (CHAR16), L",I19");
//    if (Entry->Flags & EFI_BOOT)
//      StrCat (StringBuffer, L",EFI");
    if (Entry->Flags & TSC_TIMER)
      StrCatS (StringBuffer, sizeof (StringBuffer) / sizeof (CHAR16), L",TSC");
    StrCatS (StringBuffer, sizeof (StringBuffer) / sizeof (CHAR16), L"\n");
    StrCatS (HelpString, sizeof (HelpString) / sizeof (CHAR16), StringBuffer);
  }

  if (StrLen (HelpString) == 0) {
    StrCatS (HelpString, sizeof (HelpString) / sizeof (CHAR16), L"N/A");
  } else {
//    StrCat (HelpString, L"QB/FB : Quiet/Fast Boot\n");
    StrCatS (HelpString, sizeof (HelpString) / sizeof (CHAR16), L"I19 : INT19h Boot\n");
//    StrCat (HelpString, L"EFI : EFI Boot");
  }

  InitString (
    HiiHandle,
    STRING_TOKEN (STR_ENABLE_BOOTTIME_HELP),
    L"%s", HelpString
    );

  DEBUG ((DEBUG_INFO, "<PrintBootTime_END>"));
}


/**
  Init boot time strings

  @param[in]  HiiHandle
  @param[in]  Class
**/
VOID
InitBootTimeStrings (
  IN EFI_HII_HANDLE HiiHandle,
  IN UINT16         Class
  )
{
  EFI_STATUS                      Status;
  UINTN                           VariableSize;
  BOOTTIME_SETUP                  BootTimeSetup;

  if (Class != BOOT_FORM_SET_CLASS) {
    return ;
  }

  DEBUG ((DEBUG_INFO, "<InitBootTimeStrings>"));

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"BootTime",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &BootTimeSetup
                  );
  if (!EFI_ERROR (Status)) {
    if (BootTimeSetup.BootTime == 1) {
      PrintBootTimeToHii (HiiHandle);
    }
  }
}

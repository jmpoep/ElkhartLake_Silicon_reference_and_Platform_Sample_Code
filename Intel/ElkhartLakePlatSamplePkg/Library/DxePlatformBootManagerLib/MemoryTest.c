/** @file
  Perform the platform memory test

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

#include "BdsPlatform.h"
#include "FastBootSupport.h"
#include "String.h"

//
// BDS Platform Functions
//
/**
  Perform the memory test base on the memory test intensive level,
  and update the memory resource.

  @param  Level         The memory test intensive level.

  @retval EFI_STATUS    Success test all the system memory and update
                        the memory resource

**/
EFI_STATUS
MemoryTest (
  IN EXTENDMEM_COVERAGE_LEVEL Level
  )
{
  EFI_STATUS                        Status;
  EFI_STATUS                        KeyStatus;
  EFI_STATUS                        InitStatus;
  EFI_STATUS                        ReturnStatus;
  BOOLEAN                           RequireSoftECCInit;
  EFI_GENERIC_MEMORY_TEST_PROTOCOL  *GenMemoryTest;
  UINT64                            TestedMemorySize;
  UINT64                            TotalMemorySize;
  UINTN                             TestPercent;
  UINT64                            PreviousValue;
  BOOLEAN                           ErrorOut;
  BOOLEAN                           TestAbort;
  EFI_INPUT_KEY                     Key;
  CHAR16                            StrPercent[80];
  CHAR16                            *StrTotalMemory;
  UINTN                             StrTotalMemoryLen;
  CHAR16                            *Pos;
  CHAR16                            *TmpStr;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL     Foreground;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL     Background;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL     Color;
  UINT32                            TempData;

  ReturnStatus = EFI_SUCCESS;
  ZeroMem (&Key, sizeof (EFI_INPUT_KEY));

  StrTotalMemoryLen = 64;

  Pos = AllocatePool (StrTotalMemoryLen * sizeof (CHAR16));

  if (Pos == NULL) {
    return ReturnStatus;
  }

  StrTotalMemory    = Pos;

  TestedMemorySize  = 0;
  TotalMemorySize   = 0;
  PreviousValue     = 0;
  ErrorOut          = FALSE;
  TestAbort         = FALSE;
  TestPercent       = 0;

  SetMem (&Foreground, sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL), 0xff);
  SetMem (&Background, sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL), 0x0);
  SetMem (&Color, sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL), 0xff);

  RequireSoftECCInit = FALSE;

  Status = gBS->LocateProtocol (
                  &gEfiGenericMemTestProtocolGuid,
                  NULL,
                  (VOID **) &GenMemoryTest
                  );
  if (EFI_ERROR (Status)) {
    FreePool (Pos);
    return EFI_SUCCESS;
  }

  InitStatus = GenMemoryTest->MemoryTestInit (
                                GenMemoryTest,
                                Level,
                                &RequireSoftECCInit
                                );
  if (InitStatus == EFI_NO_MEDIA) {
    //
    // The PEI codes also have the relevant memory test code to check the memory,
    // it can select to test some range of the memory or all of them. If PEI code
    // checks all the memory, this BDS memory test will has no not-test memory to
    // do the test, and then the status of EFI_NO_MEDIA will be returned by
    // "MemoryTestInit". So it does not need to test memory again, just return.
    //
    FreePool (Pos);
    return EFI_SUCCESS;
  }

  if (GetDisplayBootMode () == NORMAL_BOOT) {
    TmpStr = GetStringById (STRING_TOKEN (STR_ESC_TO_SKIP_MEM_TEST));

    if (TmpStr != NULL) {
      PrintXY (10, 10, NULL, NULL, TmpStr);
      FreePool (TmpStr);
    }
  }

  do {
    Status = GenMemoryTest->PerformMemoryTest (
                              GenMemoryTest,
                              &TestedMemorySize,
                              &TotalMemorySize,
                              &ErrorOut,
                              TestAbort
                              );
    if (ErrorOut && (Status == EFI_DEVICE_ERROR)) {
      if (GetDisplayBootMode () == NORMAL_BOOT) {
        TmpStr = GetStringById (STRING_TOKEN (STR_SYSTEM_MEM_ERROR));
        if (TmpStr != NULL) {
          PrintXY (10, 10, NULL, NULL, TmpStr);
          FreePool (TmpStr);
        }
      }

      ASSERT (0);
    }

    if (GetDisplayBootMode () == NORMAL_BOOT) {
      TempData = (UINT32) DivU64x32 (TotalMemorySize, 16);
      TestPercent = (UINTN) DivU64x32 (
                              DivU64x32 (MultU64x32 (TestedMemorySize, 100), 16),
                              TempData
                              );
      if (TestPercent != PreviousValue) {
        UnicodeValueToStringS (StrPercent, sizeof (StrPercent), 0, TestPercent, 0);
        TmpStr = GetStringById (STRING_TOKEN (STR_MEMORY_TEST_PERCENT));
        if (TmpStr != NULL) {
          //
          // TmpStr size is 64, StrPercent is reserved to 16.
          //
          StrCatS (StrPercent, sizeof (StrPercent) / sizeof (CHAR16), TmpStr);
          PrintXY (10, 10, NULL, NULL, StrPercent);
          FreePool (TmpStr);
        }

        TmpStr = GetStringById (STRING_TOKEN (STR_PERFORM_MEM_TEST));
        if (TmpStr != NULL) {
          ShowProgress (
            Foreground,
            Background,
            TmpStr,
            Color,
            TestPercent,
            (UINTN) PreviousValue
            );
          FreePool (TmpStr);
        }
      }
    }

    PreviousValue = TestPercent;

    if (!PcdGetBool (PcdConInConnectOnDemand)) {
      KeyStatus     = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
      if (!EFI_ERROR (KeyStatus) && (Key.ScanCode == SCAN_ESC)) {
        if (!RequireSoftECCInit) {
          if (GetDisplayBootMode () == NORMAL_BOOT) {
            TmpStr = GetStringById (STRING_TOKEN (STR_PERFORM_MEM_TEST));
            if (TmpStr != NULL) {
              ShowProgress (
                Foreground,
                Background,
                TmpStr,
                Color,
                100,
                (UINTN) PreviousValue
                );
              FreePool (TmpStr);
            }

            PrintXY (10, 10, NULL, NULL, L"100");
          }
          Status = GenMemoryTest->Finished (GenMemoryTest);
          goto Done;
        }

        TestAbort = TRUE;
      }
    }
  } while (Status != EFI_NOT_FOUND);

  Status = GenMemoryTest->Finished (GenMemoryTest);

Done:
  if (GetDisplayBootMode () == NORMAL_BOOT) {
    UnicodeValueToStringS (StrTotalMemory, StrTotalMemoryLen * sizeof (CHAR16), COMMA_TYPE, TotalMemorySize, 0);
    if (StrTotalMemory[0] == L',') {
      StrTotalMemory++;
    }

    TmpStr = GetStringById (STRING_TOKEN (STR_MEM_TEST_COMPLETED));
    if (TmpStr != NULL) {
      StrCatS (StrTotalMemory, 128 / sizeof (CHAR16), TmpStr);
      FreePool (TmpStr);
    }

    PrintXY (10, 10, NULL, NULL, StrTotalMemory);
    ShowProgress (
      Foreground,
      Background,
      StrTotalMemory,
      Color,
      100,
      (UINTN) PreviousValue
      );
    }
  FreePool (Pos);

  return ReturnStatus;
}

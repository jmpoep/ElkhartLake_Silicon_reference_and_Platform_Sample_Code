/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

GLOBAL_REMOVE_IF_UNREFERENCED EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL     *mOriginalStConOut;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL     *mFastBootConOut;


EFI_STATUS
EFIAPI
DummyOutputString (
  IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *This,
  IN  CHAR16                             *WString
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DummyTestString (
  IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *This,
  IN  CHAR16                             *WString
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DummySetAttribute (
  IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL        *This,
  IN UINTN                                  Attribute
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DummySetMode (
  IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *This,
  IN  UINTN                              ModeNumber
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DummySetCursorPosition (
  IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *This,
  IN  UINTN                              Column,
  IN  UINTN                              Row
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DummyEnableCursor (
  IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *This,
  IN  BOOLEAN                            Visible
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
DummyClearScreen (
  IN  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL    *This
  )
{
  return EFI_SUCCESS;
}

VOID
InstallFastBootConOut (
  VOID
  )
/*++

Routine Description:

    This function hooks gST->ConOut to supress text display if FastBoot is enabled

Arguments:

    None

--*/
{
   mFastBootConOut = AllocatePool (sizeof (EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL));
   ASSERT (mFastBootConOut != NULL);
   CopyMem(mFastBootConOut, mOriginalStConOut, sizeof (EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL));

   mOriginalStConOut->OutputString = DummyOutputString;
   mOriginalStConOut->TestString = DummyTestString;
   mOriginalStConOut->SetMode = DummySetMode;
   mOriginalStConOut->SetAttribute = DummySetAttribute;
   mOriginalStConOut->ClearScreen = DummyClearScreen;
   mOriginalStConOut->SetCursorPosition = DummySetCursorPosition;
   mOriginalStConOut->EnableCursor = DummyEnableCursor;
}

VOID
FastBootHookConOut (
  VOID
  )
/*++

Routine Description:

    This function hooks gST->ConOut to supress text display after Console Out is installed
    if FastBoot is enabled

Arguments:

    None

--*/
{
  if ((FastBootEnabled()) && (!IsExceptionType2Detected())) {
    mOriginalStConOut = gST->ConOut;
    InstallFastBootConOut ();
  }
}

VOID
FastBootRestoreConOut (
  VOID
  )
/*++

Routine Description:

    This function will be called to restore gST->ConOut after all drivers have been connected

Arguments:

    None

--*/
{
  if ((FastBootEnabled()) && (!IsExceptionType2Detected())) {
    ASSERT (mFastBootConOut != NULL);
    CopyMem(mOriginalStConOut, mFastBootConOut, sizeof (EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL));
    FreePool(mFastBootConOut);
  }
}
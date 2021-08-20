/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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
#include "Ui.h"

UINTN                                  mConOutCols;
UINTN                                  mConOutRows;
CHAR16                                *mScreenTitle;

/**
  This function will change video resolution and text mode
  according to defined setup mode or defined boot mode

  @param  IsSetupMode   Indicate mode is changed to setup mode or boot mode.

  @retval  EFI_SUCCESS  Mode is changed successfully.
  @retval  Others             Mode failed to be changed.

**/
EFI_STATUS
EFIAPI
SetSecureEraseConsoleMode (
  VOID
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

  //
  // Set The requried resolution for Secure Erase Screen
  //
  NewHorizontalResolution = SECURE_ERASE_HORIZONTAL_RESOLUTION;
  NewVerticalResolution   = SECURE_ERASE_VERTICAL_RESOLUTION;
  NewColumns              = SECURE_ERASE_COLUMNS_NUMBER;
  NewRows                 = SECURE_ERASE_ROWS_NUMBER;


  MaxGopMode  = GraphicsOutput->Mode->MaxMode;
  MaxTextMode = SimpleTextOut->Mode->MaxMode;


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
                  PcdSet32S (PcdConOutColumn, SECURE_ERASE_COLUMNS_NUMBER);
                  PcdSet32S (PcdConOutRow, SECURE_ERASE_ROWS_NUMBER);
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
  Initializes the library. Required to be used before calling any other function
  from this library.
**/
VOID
InitUiLib (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "SecureErase::Ui::InitUiLib\n"));
  SetSecureEraseConsoleMode ();
  gST->ConOut->EnableCursor (gST->ConOut, FALSE);
  gST->ConOut->QueryMode (gST->ConOut, gST->ConOut->Mode->Mode, &mConOutCols, &mConOutRows);

  mScreenTitle = NULL;
  DEBUG ((DEBUG_INFO, "std out terminal : %d x %d\n", mConOutCols, mConOutRows));
}

/**
  Get password input from the pop up windows.

  @param[in, out]  Password     The buffer to hold the input user password.

  @retval EFI_ABORTED           It is given up by pressing 'ESC' key.
  @retval EFI_NOT_READY         Not a valid input at all.
  @retval EFI_SUCCESS           Get a user name successfully.

**/
EFI_STATUS
PopupHddPasswordInputWindows (
  IN OUT CHAR8                        *Password
  )
{
  EFI_INPUT_KEY                        Key;
  UINTN                                Length;
  CHAR16                               Mask[32 + 1];
  CHAR16                               Unicode[32 + 1];
  CHAR8                                Ascii[32 + 1];

  DEBUG ((DEBUG_INFO, "SecureErase::Ui::PopupHddPasswordInputWindows\n"));
  ZeroMem (Unicode, sizeof (Unicode));
  ZeroMem (Ascii, sizeof (Ascii));
  ZeroMem (Mask, sizeof (Mask));

  Length = 0;
  while (TRUE) {
    Mask[Length] = L'_';
    CreatePopUp (
      EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE,
      &Key,
      L"Secure erase",
      L"-----------------------------------------------------",
      L"Enter hard drives master password to erase the device:",
      Mask,
      NULL
      );
    //
    // Check key.
    //
    if (Key.ScanCode == SCAN_NULL) {
      if (Key.UnicodeChar == CHAR_CARRIAGE_RETURN) {
        //
        // Add the null terminator.
        //
        Unicode[Length] = 0;
        Length++;
        break;
      } else if ((Key.UnicodeChar == CHAR_NULL) ||
                 (Key.UnicodeChar == CHAR_TAB) ||
                 (Key.UnicodeChar == CHAR_LINEFEED)
                 ) {
        continue;
      } else {
        if (Key.UnicodeChar == CHAR_BACKSPACE) {
          if (Length > 0) {
            Unicode[Length] = 0;
            Mask[Length] = 0;
            Length--;
          }
        } else {
          Unicode[Length] = Key.UnicodeChar;
          Mask[Length] = L'*';
          Length++;
          if (Length == 32) {
            //
            // Add the null terminator.
            //
            Unicode[Length] = 0;
            Mask[Length] = 0;
            break;
          }
        }
      }
    }

    if (Key.ScanCode == SCAN_ESC) {
      if (Length == 0) {
        return EFI_ABORTED;
      } else {
        return EFI_NOT_READY;
      }
    }
  }

  if (Length <= 1) {
    return EFI_NOT_READY;
  }

  UnicodeStrToAsciiStrS (Unicode, Ascii, sizeof (Ascii));
  CopyMem (Password, Ascii, 32);
  ZeroMem (Unicode, sizeof (Unicode));
  ZeroMem (Ascii, sizeof (Ascii));

  return EFI_SUCCESS;
}

/**
  Allocates a buffer to hold one line of char16 type and fills it with a given
  character.

  @param[in]       Filler              Character to fill the buffer with

  @retval pointer to a newly allocated buffer
 */
CHAR16*
AlocateFilledLine (
  IN CHAR16                            Filler
  )
{
  CHAR16                              *Line;
  UINTN                                i;

  Line = AllocatePool ((mConOutCols+1)*sizeof (CHAR16));
  ASSERT (Line != NULL);

  if (Line != NULL) {
    for (i=0; i<mConOutCols ; i++){
      Line[i] = Filler;
    }
    Line[mConOutCols]=L'\0';
  }

  return Line;
}

/**
  Counts number of chars in an Unicode string

  @param[in]       Str       String to count chars in

  @retval number of chars in the string
 */
UINTN
UStrLen (
  IN CHAR16                              *Str
  ){
  UINTN                                Len;

  for (Len=0; Str[Len]!=L'\0'; Len++){}
  return Len-1;
}

/**
  Creates a copy of the current ConOut mode.

  @param[in]       Mode      pointer to a preallocated buffer
 */
VOID
PreserveConsoleMode (
  IN EFI_SIMPLE_TEXT_OUTPUT_MODE      *Mode
  ) {
  CopyMem (&Mode, gST->ConOut->Mode, sizeof (Mode));
}

/**
  Restores ConOut console mode using the given variable.

  @param[in]       Mode      Previously preserved console mode to restore
 */
VOID
RestoreConsoleMode (
  IN EFI_SIMPLE_TEXT_OUTPUT_MODE      *Mode
  ) {
  gST->ConOut->EnableCursor      (gST->ConOut, gST->ConOut->Mode->CursorVisible);
  gST->ConOut->SetCursorPosition (
          gST->ConOut,
          gST->ConOut->Mode->CursorColumn,
          gST->ConOut->Mode->CursorRow
          );
  gST->ConOut->SetAttribute      (gST->ConOut, gST->ConOut->Mode->Attribute);
}

/**
  Creates a horizontal bar to put on the screen

  @param[out]      Line      Pointer to a newly allocated buffer containing the bar

  @retval Pointer to a newly allocated buffer containing the bar
 */
CHAR16*
CreateRedYellowStripe (
  OUT CHAR16                          *Line
  ) {
  UINTN                                i;
  gST->ConOut->SetAttribute (gST->ConOut, EFI_YELLOW | EFI_BACKGROUND_RED);
  for (i=0; i<mConOutCols; i++) {
    if (i%2) {
      Line[i] = L' ';
    } else {
      Line[i] = BLOCKELEMENT_FULL_BLOCK;
    }
  }
  Line[mConOutCols]=L'\0';
  return Line;
}

/**
  Sets screen title which is displayed at top of the screen

  @param[in]       Title     Null terminated unicode string
 */
VOID
SetScreenTitle (
  IN CHAR16                           *Title
) {
  UINTN                                TitleSize;

  TitleSize = (UStrLen (Title)+1) * sizeof (CHAR16);
  mScreenTitle = AllocatePool (TitleSize);
  ASSERT (mScreenTitle != NULL);
  if (mScreenTitle != NULL){
    CopyMem (mScreenTitle, Title, TitleSize);
  }
}

/**
  Displays a footer on the screen
 */
VOID
PrintFooter (
  VOID
  ) {
  EFI_SIMPLE_TEXT_OUTPUT_MODE          SavedConsoleMode;
  CHAR16                              *Line;

  Line = AlocateFilledLine (L' ');
  if (Line == NULL) {
    return;
  }

  PreserveConsoleMode (&SavedConsoleMode);

  gST->ConOut->SetAttribute (gST->ConOut, EFI_WHITE | EFI_BACKGROUND_BLUE);

  gST->ConOut->SetCursorPosition (gST->ConOut, 0, mConOutRows-3);
  gST->ConOut->OutputString (gST->ConOut, Line);

  gST->ConOut->SetCursorPosition (gST->ConOut, 0, mConOutRows-2);
  gST->ConOut->OutputString (gST->ConOut, Line);

  gST->ConOut->SetCursorPosition (gST->ConOut, 0, mConOutRows-1);
  gST->ConOut->OutputString (gST->ConOut, Line);

  CreateRedYellowStripe (Line);
  gST->ConOut->SetCursorPosition (gST->ConOut, 0, mConOutRows-4);
  gST->ConOut->OutputString (gST->ConOut, Line);

  FreePool (Line);
  RestoreConsoleMode (&SavedConsoleMode);
}

/**
  Fills the screens background
 */
VOID
FillBackground (
  VOID
  ) {
  UINTN                                I;
  EFI_SIMPLE_TEXT_OUTPUT_MODE          SavedConsoleMode;
  CHAR16                              *Line;

  Line = AlocateFilledLine (L' ');
  if (Line == NULL) {
    return;
  }

  PreserveConsoleMode (&SavedConsoleMode);

  gST->ConOut->SetAttribute (gST->ConOut,EFI_WHITE | EFI_BACKGROUND_BLACK);
  for (I=5; I < mConOutRows-3; I++) {
    gST->ConOut->SetCursorPosition (gST->ConOut, 0, I);
    gST->ConOut->OutputString (gST->ConOut, Line);
  }
  FreePool (Line);
  RestoreConsoleMode (&SavedConsoleMode);
}


/**
  Prints header at top of the screen and displays the screen title
 */
VOID
PrintHeader (
  VOID
  ){
  EFI_SIMPLE_TEXT_OUTPUT_MODE          SavedConsoleMode;
  CHAR16                              *Line;

  Line = AlocateFilledLine (L' ');
  if (Line == NULL) {
    return;
  }

  PreserveConsoleMode (&SavedConsoleMode);
  gST->ConOut->SetAttribute (gST->ConOut, EFI_WHITE | EFI_BACKGROUND_BLUE);

  gST->ConOut->SetCursorPosition (gST->ConOut, 0, 1);
  gST->ConOut->OutputString (gST->ConOut, Line);
  gST->ConOut->SetCursorPosition (gST->ConOut, 0, 3);
  gST->ConOut->OutputString (gST->ConOut, Line);

  if (NULL != mScreenTitle) {
    CopyMem (
        &Line[(mConOutCols - UStrLen (mScreenTitle))/2],
        mScreenTitle,
        UStrLen (mScreenTitle) * sizeof (CHAR16)
        );
  }

  gST->ConOut->SetCursorPosition (gST->ConOut, 0, 2);
  gST->ConOut->OutputString (gST->ConOut, Line);

  CreateRedYellowStripe (Line);
  gST->ConOut->SetCursorPosition (gST->ConOut, 0, 4);
  gST->ConOut->OutputString (gST->ConOut, Line);

  RestoreConsoleMode (&SavedConsoleMode);

  FreePool (Line);
}

/*
  Fill screen with white spaces.

  @param[in]       Attribute           The attribute to set. Bits 0..3 are the
                                       foreground color, and bits 4..6 are the
                                       background color. All other bits are
                                       undefined and must be zero. The valid
                                       Attributes are defined in this file.
 */
VOID
FillScreen (
  UINTN                                Attribute
  )
{
  EFI_SIMPLE_TEXT_OUTPUT_MODE          SavedConsoleMode;
  CHAR16                              *Line;
  UINTN                                Row;

  Line = AlocateFilledLine (L' ');
  if (Line == NULL) {
    return;
  }

  PreserveConsoleMode (&SavedConsoleMode);

  gST->ConOut->SetAttribute (gST->ConOut, Attribute);
  gST->ConOut->SetCursorPosition (gST->ConOut, 0, 0);

  for (Row=0; Row < mConOutRows; Row++) {
    gST->ConOut->SetCursorPosition (gST->ConOut, 0, Row);
    gST->ConOut->OutputString(gST->ConOut, Line);
  }

  FreePool (Line);
  RestoreConsoleMode (&SavedConsoleMode);
}

/*
  Outputs provided c string on the given position.

  @param[in]       String              C string to be printed
  @param[in]       Column              Column number to put first char in
  @param[in]       Row                 Row number to put first char in
  @param[in]       Attribute           The attribute to set. Bits 0..3 are the
                                       foreground color, and bits 4..6 are the
                                       background color. All other bits are
                                       undefined and must be zero. The valid
                                       Attributes are defined in this file.
 */
VOID
OutputString (
  CHAR16                              *String,
  UINTN                                Column,
  UINTN                                Row,
  UINTN                                Attribute
  )
{
  EFI_SIMPLE_TEXT_OUTPUT_MODE          SavedConsoleMode;
  PreserveConsoleMode (&SavedConsoleMode);
  gST->ConOut->SetCursorPosition (gST->ConOut, Column, Row);
  gST->ConOut->SetAttribute (gST->ConOut, Attribute);
  gST->ConOut->OutputString (gST->ConOut, String);

  RestoreConsoleMode (&SavedConsoleMode);
}

/**
  Redraws an empty screen with title only
 */
VOID
ClearScreen (
  VOID
  ) {
  gST->ConOut->EnableCursor (gST->ConOut ,FALSE);
  gST->ConOut->ClearScreen (gST->ConOut);
  PrintHeader ();
  FillBackground ();
  PrintFooter ();
  gST->ConOut->SetCursorPosition (gST->ConOut, 5, 5);
}
/**
  Displays a progress bar dialog to indicate ongoing operation. Function takes
  three seconds to complete.

  @param[in]       Message   A unicode string to display above the bar
 */
VOID
ProgressBarDialog (
  IN CHAR16                           *Message
) {
  EFI_SIMPLE_TEXT_OUTPUT_MODE          SavedConsoleMode;
  UINTN                                BarXPos;
  UINTN                                BarYPos;
  UINTN                                BarLen;
  UINTN                                IterationTime;
  CHAR16                              *Bar;
  UINTN                                DotPos;
  UINTN                                i;

  PreserveConsoleMode (&SavedConsoleMode);

  BarLen = mConOutCols / 3;
  BarXPos = (mConOutCols - BarLen)/2;
  BarYPos = (mConOutRows / 2) + 1;
  Bar = AllocateZeroPool ((BarLen+1)*2);
  if (Bar == NULL) {
    ASSERT (FALSE);
    return;
  }

  DotPos = 0;
  IterationTime = 3000000 / BarLen;

  if (NULL != Message){
    gST->ConOut->SetAttribute (gST->ConOut, EFI_BLACK | EFI_BACKGROUND_LIGHTGRAY);
    gST->ConOut->SetCursorPosition (gST->ConOut, (mConOutCols-UStrLen (Message))/2, (mConOutRows/2)-1);
    gST->ConOut->OutputString (gST->ConOut, Message);
  }
  gST->ConOut->SetAttribute (gST->ConOut, EFI_YELLOW | EFI_BACKGROUND_RED);
  for (i=BarLen-1; i; i--){
    Bar[i] = L' ';
  }
  while (TRUE){
    Bar[DotPos] = L' ';
    DotPos++;
    if (DotPos==BarLen){
      break;
    }
    Bar[DotPos] = BLOCKELEMENT_FULL_BLOCK;
    if (DotPos+1<BarLen){
      Bar[DotPos+1] = BLOCKELEMENT_FULL_BLOCK;
    }
    gST->ConOut->SetCursorPosition (gST->ConOut, BarXPos, BarYPos);
    gST->ConOut->OutputString (gST->ConOut, Bar);
    gST->ConOut->SetCursorPosition (gST->ConOut, BarXPos, BarYPos+1);
    gST->ConOut->OutputString (gST->ConOut, Bar);
    gBS->Stall (IterationTime);
  }

  RestoreConsoleMode (&SavedConsoleMode);
  FreePool (Bar);
}

/**
  Prints summary message after the secure erase procedure has ended

  @param[in]       Status    Secure erase procedures completion result

 */
VOID
PrintSummary (
  EFI_STATUS                           Status
  )
{
  UINTN                                i=4;

  DEBUG ((DEBUG_INFO, "SecureErase::PrintSummary\n"));
  ClearScreen ();
  for (; i ; i--) {
    if (EFI_ERROR (Status)) {
      ProgressBarDialog (L"System has failed to erase the device. Power off in 10 seconds");
    } else {
      ProgressBarDialog (L"Disk erase completed. System shutdown in 10 seconds");
    }
  }
}


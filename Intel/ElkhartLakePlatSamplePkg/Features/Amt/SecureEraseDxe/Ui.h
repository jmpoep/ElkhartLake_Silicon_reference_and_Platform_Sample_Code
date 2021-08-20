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

#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/GraphicsOutput.h>

#define SECURE_ERASE_HORIZONTAL_RESOLUTION 800
#define SECURE_ERASE_VERTICAL_RESOLUTION   600
#define SECURE_ERASE_COLUMNS_NUMBER        100
#define SECURE_ERASE_ROWS_NUMBER           31

/**
  Initializes the library. Required to be used before calling any other function
  from this library.
**/
VOID
InitUiLib (
  VOID
  );

/**
  Redraws an empty screen with title only
**/
VOID
ClearScreen (
  VOID
  );

/**
  Displays a progress bar dialog to indicate ongoing operation. Function takes
  three seconds to complete.

  @param[in]       Message   A unicode string to display above the bar
**/
VOID
ProgressBarDialog (
  IN CHAR16                           *Message
);

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
  );

/**
  Sets screen title which is displayed at top of the screen

  @param[in]       Title     Null terminated unicode string
**/
VOID
SetScreenTitle (
  IN CHAR16                           *Title
);

/**
  Fill screen with white spaces.

  @param[in]       Attribute           The attribute to set. Bits 0..3 are the
                                       foreground color, and bits 4..6 are the
                                       background color. All other bits are
                                       undefined and must be zero. The valid
                                       Attributes are defined in this file.
**/
VOID
FillScreen (
  UINTN                                Attribute
  );

/**
  Outputs provided c string on the given position.

  @param[in]       String              C string to be printed
  @param[in]       Column              Column number to put first char in
  @param[in]       Row                 Row number to put first char in
  @param[in]       Attribute           The attribute to set. Bits 0..3 are the
                                       foreground color, and bits 4..6 are the
                                       background color. All other bits are
                                       undefined and must be zero. The valid
                                       Attributes are defined in this file.
**/
VOID
OutputString (
  CHAR16                              *String,
  UINTN                                Column,
  UINTN                                Row,
  UINTN                                Attribute
  );

/**
Prints summary message after the secure erase procedure has ended

@param[in]       Status    Secure erase procedures completion result

**/
VOID
PrintSummary (
EFI_STATUS                           Status
);

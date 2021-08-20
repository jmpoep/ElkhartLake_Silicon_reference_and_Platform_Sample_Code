//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
Definitions for the GenBiosId tool.

Copyright (c) 1999 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _GEN_BIOS_ID_
#define _GEN_BIOS_ID_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <Common/UefiBaseTypes.h>

#if defined(_MSC_VER) && _MSC_VER < 1900
#define snprintf _snprintf
#endif

#define FILE_NAME_SIZE  256
#define MAX_LINE_SIZE   256
#define MAX_FORMAT_STRING_SIZE  64

#define ATOU(a)         (CHAR16) ((UINT8) (a))
#define UTOA(a)         (CHAR8) ((UINT16) (a))

//
// BIOS ID field names.
//
#define NAME_BOARD_ID       "BOARD_ID"
#define NAME_BOARD_REV      "BOARD_REV"
#define NAME_BOARD_EXT      "BOARD_EXT"
#define NAME_BUILD_TYPE     "BUILD_TYPE"
#define NAME_VERSION_MAJOR  "VERSION_MAJOR"
#define NAME_VERSION_MINOR  "VERSION_MINOR"
#define NAME_DATE           "DATE"
#define NAME_TIME           "TIME"

//
// Number of ASCII characters in each field
//
#define CHARS_BOARD_ID      7
#define CHARS_BOARD_REV     1
#define CHARS_BOARD_EXT     3
#define CHARS_BUILD_TYPE    1
#define CHARS_VERSION_MAJOR 4
#define CHARS_VERSION_MINOR 2
#define CHARS_DATE          6
#define CHARS_TIME          4

#define FIELD_BOARD_ID      0x0001
#define FIELD_BOARD_REV     0x0002
#define FIELD_BOARD_EXT     0x0004
#define FIELD_BUILD_TYPE    0x0008
#define FIELD_VERSION_MAJOR 0x0010
#define FIELD_VERSION_MINOR 0x0020
#define FIELD_DATE          0x0040
#define FIELD_TIME          0x0080

#define FIELD_ALL (     \
  FIELD_BOARD_ID      | \
  FIELD_BOARD_REV     | \
  FIELD_BOARD_EXT     | \
  FIELD_BUILD_TYPE    | \
  FIELD_VERSION_MAJOR | \
  FIELD_VERSION_MINOR | \
  FIELD_DATE          | \
  FIELD_TIME)

//
// BIOS ID string format:
//
// $(BOARD_ID)$(BOARD_REV).$(BOARD_EXT).$(VERSION_MAJOR).$(BUILD_TYPE)$(VERSION_MINOR).YYMMDDHHMM
//
// Example: "TRFTCRB1.000.0008.D03.1501301017"
//
// The format should be same as platform BIOS ID definition
//
#pragma pack(1)

typedef struct {
  CHAR16    BoardId[7];             // "TRFTCRB"
  CHAR16    BoardRev;               // "1"
  CHAR16    Dot1;                   // "."
  CHAR16    BoardExt[3];            // "000"
  CHAR16    Dot2;                   // "."
  CHAR16    VersionMajor[4];        // "0008"
  CHAR16    Dot3;                   // "."
  CHAR16    BuildType;              // "D"
  CHAR16    VersionMinor[2];        // "03"
  CHAR16    Dot4;                   // "."
  CHAR16    TimeStamp[10];          // "YYMMDDHHMM"
  CHAR16    NullTerminator;         // 0x0000
} BIOS_ID_STRING;

//
// A signature precedes the BIOS ID string in the FV to enable search by external tools.
//
typedef struct {
  UINT8             Signature[8];   // "$IBIOSI$"
  BIOS_ID_STRING    BiosIdString;   // "TRFTCRB1.000.0008.D03.1501301017"
} BIOS_ID_IMAGE;

#pragma pack()

int
main (
  IN  int   argc,
  IN  CHAR8 *argv[]
  );

VOID
PrintBanner (
  VOID
  );

VOID
PrintUsage (
  VOID
  );

EFI_STATUS
ParseInputFile (
  VOID
  );

EFI_STATUS
WriteOutputFile (
  VOID
  );

EFI_STATUS
WriteOutputBatchFile (
  VOID
  );

CHAR8 *
StripLeadingWhiteSpace (
  IN CHAR8 *StrInput
  );

VOID
ConvertToUnicode (
  IN  CHAR8  *StrAscii,
  OUT CHAR16 *StrUnicode
  );

VOID
ConvertToAscii (
  IN  CHAR16 *StrUnicode,
  OUT CHAR8  *StrAscii
  );

VOID
PrintUnicodeString (
  IN CHAR16 *StrUnicode
  );

VOID
FillTimeStamp (
  OUT CHAR16  *StrTimeStampUnicode
  );

#endif // _GEN_BIOS_ID_

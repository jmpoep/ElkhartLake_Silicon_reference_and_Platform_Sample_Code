//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  GUID and definitions for BIOS ID.

  Copyright (c) 2015, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef _BIOS_ID_GUID_H_
#define _BIOS_ID_GUID_H_

#include <Pi/PiHob.h>

#define BIOS_ID_GUID \
  { \
    0xC3E36D09, 0x8294, 0x4b97, { 0xA8, 0x57, 0xD5, 0x28, 0x8F, 0xE3, 0x3E, 0x28 } \
  }

extern EFI_GUID gBiosIdGuid;

//
// BIOS ID string format conforms to "BIOS Revision Identification Specification", Rev. 2.0, 01/30/2015.
//
// $(BOARD_ID)$(BOARD_REV).$(BOARD_EXT).$(VERSION_MAJOR).$(BUILD_TYPE)$(VERSION_MINOR).YYMMDDHHMM
//
// Example: "TRFTCRB1.000.0008.D03.1501301017"
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

typedef struct {
  EFI_HOB_GUID_TYPE GuidType;
  BIOS_ID_IMAGE     BiosIdImage;
} BIOS_ID_HOB;

#endif


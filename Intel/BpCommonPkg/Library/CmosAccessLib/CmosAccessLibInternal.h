//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  CmosAccessLib internal header file.

Copyright (c) 2015, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _CMOS_ACCESS_LIB_INTERNALS_
#define _CMOS_ACCESS_LIB_INTERNALS_

#include <Base.h>
#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/CmosAccessLib.h>
#include <Library/PlatformCmosAccessLib.h>

// CMOS access Port address

#define PORT_70            0x70
#define PORT_71            0x71
#define PORT_72            0x72
#define PORT_73            0x73

#define CMOS_BANK0_LIMIT   0x7F
#define CMOS_BANK1_LIMIT   0xFF

typedef struct {
   UINT8  Length;
   UINT8  LowByteAddress;
   UINT8  HighByteAddress;
} CMOS_CHECKSUM_LOCATION_INFO;

#endif // _CMOS_ACCESS_LIB_INTERNALS_

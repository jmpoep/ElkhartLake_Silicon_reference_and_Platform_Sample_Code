//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor. This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/**@file
Definitions for the FitGen utility.

Copyright (c) 2010 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _FIT_GEN_H
#define _FIT_GEN_H

#include <stdio.h>
#include <stdlib.h>
#define PI_SPECIFICATION_VERSION  0x00010000
#define EFI_FVH_PI_REVISION       EFI_FVH_REVISION
#include <Common/UefiBaseTypes.h>
#include <Common/PiFirmwareFile.h>
#include <Common/PiFirmwareVolume.h>
#include <Guid/PiFirmwareFileSystem.h>
#include "EfiUtilityMsgs.c"
#include "CommonLib.h"
#include "ParseInf.h"
#include "FvLib.h"

//
// Utility Name
//
#define UTILITY_NAME  "FitGen"

//
// Utility version information
//
#define UTILITY_MAJOR_VERSION 0
#define UTILITY_MINOR_VERSION 55
#define UTILITY_DATE          __DATE__

//
// The minimum number of arguments accepted from the command line.
//
#define MIN_VIEW_ARGS   3
#define MIN_ARGS        4
#define BUF_SIZE        (8 * 1024)

#define GETOCCUPIEDSIZE(ActualSize, Alignment) \
  (ActualSize) + (((Alignment) - ((ActualSize) & ((Alignment) - 1))) & ((Alignment) - 1))

VOID
PrintUtilityInfo (
  VOID
  )
/*++

Routine Description:

  Displays the standard utility information to SDTOUT

Arguments:

  None

Returns:

  None

--*/
;

VOID
PrintUsage (
  VOID
  )
/*++

Routine Description:

  Displays the utility usage syntax to STDOUT

Arguments:

  None

Returns:

  None

--*/
;


#endif

//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  Platform CMOS Access Library.

Copyright (c) 2015, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include <Base.h>
#include <Library/PlatformCmosAccessLib.h>

/**
  Return the platform CMOS entries.

  @param [out] EntryCount Return the count of platform CMOS entries.

  @return Platform CMOS entries.
**/
CMOS_ENTRY *
EFIAPI
PlatformCmosGetEntry (
  OUT UINTN       *EntryCount
  )
{
  *EntryCount = 0;
  return NULL;
}

/**
  Return the NMI enable status.
**/
BOOLEAN
EFIAPI
PlatformCmosGetNmiState (
  VOID
  )
{
  return FALSE;
}

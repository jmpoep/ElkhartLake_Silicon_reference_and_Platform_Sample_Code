/*++
  This file contains 'Framework Code' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may not be modified, except as allowed by
  additional terms of your license agreement.
--*/
/** @file
  Boot service PEI BIOS ID library implementation.

  Copyright (c) 2015 - 2018, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/OobRegionLib.h>
#include <PseOob.h>

/**
  This function returns OobRegion by searching HOB or FV.
  It also debug print the OOB data found.

  @param[out] OobRegion     The OOB data got from HOB or FV. It is optional,
                            no OOB data will be returned if it is NULL as input.

  @retval EFI_SUCCESS               OOB data has been got successfully.
  @retval EFI_NOT_FOUND             OOB data is not found, and no parameter will be modified.

**/
EFI_STATUS
EFIAPI
GetOobRegion (
  OUT OOB_DATA        *OobRegion OPTIONAL
  )
{
  return EFI_NOT_FOUND;
}


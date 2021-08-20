//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  BIOS ID library functions.

  This library provides functions to get BIOS ID, VERSION, DATE and TIME.

  Copyright (c) 2015 - 2018, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef _BIOS_ID_LIB_H_
#define _BIOS_ID_LIB_H_

#include <Guid/BiosId.h>

/**
  This function returns BIOS ID by searching HOB or FV.
  It also debug print the BIOS ID found.

  @param[out] BiosIdImage   The BIOS ID got from HOB or FV. It is optional,
                            no BIOS ID will be returned if it is NULL as input.

  @retval EFI_SUCCESS               BIOS ID has been got successfully.
  @retval EFI_NOT_FOUND             BIOS ID image is not found, and no parameter will be modified.

**/
EFI_STATUS
EFIAPI
GetBiosId (
  OUT BIOS_ID_IMAGE     *BiosIdImage OPTIONAL
  );

/**
  This function returns the BIOS Version & Release Date and Time by getting and converting BIOS ID.

  @param[out] BiosVersion       The Bios Version out of the conversion.
  @param[out] BiosReleaseDate   The Bios Release Date out of the conversion.
  @param[out] BiosReleaseTime   The Bios Release Time out of the conversion.

  @retval EFI_SUCCESS               BIOS Version & Release Date and Time have been got successfully.
  @retval EFI_NOT_FOUND             BIOS ID image is not found, and no parameter will be modified.
  @retval EFI_INVALID_PARAMETER     All the parameters are NULL.

**/
EFI_STATUS
EFIAPI
GetBiosVersionDateTime (
  OUT CHAR16    *BiosVersion, OPTIONAL
  OUT CHAR16    *BiosReleaseDate, OPTIONAL
  OUT CHAR16    *BiosReleaseTime OPTIONAL
  );

#endif


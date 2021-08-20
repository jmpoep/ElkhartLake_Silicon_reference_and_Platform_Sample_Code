/** @file
  Header file for the BFX Temp RAM Library.

@copyright
 Copyright (c) 2018 - 2019 Intel Corporation. All rights reserved
 This software and associated documentation (if any) is furnished
 under a license and may only be used or copied in accordance
 with the terms of the license. Except as permitted by the
 license, no part of this software or documentation may be
 reproduced, stored in a retrieval system, or transmitted in any
 form or by any means without the express written consent of
 Intel Corporation.
 This file contains an 'Intel Peripheral Driver' and is uniquely
 identified as "Intel Reference Module" and is licensed for Intel
 CPUs and chipsets under the terms of your license agreement with
 Intel or your vendor. This file may be modified by the user, subject
 to additional terms of the license agreement.

@par Specification
**/

#ifndef _BFX_TEMP_RAM_LIB_H_
#define _BFX_TEMP_RAM_LIB_H_

/**
  Obtain Temporary RAM Base for BFX

  @retval Temporary RAM Base address
**/
UINT32
BfxGetTempRamBase (
  VOID
  );

/**
  Obtain Temporary RAM Size for BFX

  @retval Temporary RAM Size
**/
UINT32
BfxGetTempRamSize (
  VOID
  );

#endif

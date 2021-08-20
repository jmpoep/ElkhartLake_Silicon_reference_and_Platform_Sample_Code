//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/**
  Header file for Unaligned Operations used in KeyEnroll Tool.

Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _UN_ALIGNED_H
#define _UN_ALIGNED_H

#include "KeyEnroll.h"

UINT32
KeyEnrollWriteUnaligned32 (
  OUT     UINT32                *Buffer,
  IN      UINT32                Value
  );

UINT32
ReadUnaligned32 (
  IN CONST UINT32               *Buffer
  );

#endif

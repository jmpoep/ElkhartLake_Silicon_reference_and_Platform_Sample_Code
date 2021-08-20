//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/**
  Unaligned Operations used in KeyEnroll Tool.

Copyright (c) 2017 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "Unaligned.h"

UINT16
KeyEnrollWriteUnaligned16 (
  OUT   UINT16                *Buffer,
  IN    UINT16                Value
  )
{
  ASSERT (Buffer != NULL);

  ((UINT8*)Buffer)[0] = (UINT8)Value;
  ((UINT8*)Buffer)[1] = (UINT8)(Value >> 8);

  return Value;
}

UINT32
KeyEnrollWriteUnaligned32 (
  OUT     UINT32                *Buffer,
  IN      UINT32                Value
  )
{
  ASSERT (Buffer != NULL);

  KeyEnrollWriteUnaligned16 ((UINT16*)Buffer, (UINT16)Value);
  KeyEnrollWriteUnaligned16 ((UINT16*)Buffer + 1, (UINT16)(Value >> 16));
  return Value;
}

UINT16
KeyEnrollReadUnaligned16 (
  IN CONST UINT16               *Buffer
  )
{
  volatile UINT8 LowerByte;
  volatile UINT8 HigherByte;

  ASSERT (Buffer != NULL);

  LowerByte = ((UINT8*)Buffer)[0];
  HigherByte = ((UINT8*)Buffer)[1];

  return (UINT16)(LowerByte | (HigherByte << 8));
}

UINT32
ReadUnaligned32 (
  IN CONST UINT32               *Buffer
  )
{
  UINT16  LowerBytes;
  UINT16  HigherBytes;

  ASSERT (Buffer != NULL);

  LowerBytes  = KeyEnrollReadUnaligned16 ((UINT16*) Buffer);
  HigherBytes = KeyEnrollReadUnaligned16 ((UINT16*) Buffer + 1);

  return (UINT32) (LowerBytes | (HigherBytes << 16));
}

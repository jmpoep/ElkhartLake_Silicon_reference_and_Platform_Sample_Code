/** @file
  Implementation of debug functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary and
  confidential information of Intel Corporation and its suppliers and licensors,
  and is protected by worldwide copyright and trade secret laws and treaty
  provisions. No part of the Material may be used, copied, reproduced, modified,
  published, uploaded, posted, transmitted, distributed, or disclosed in any way
  without Intel's prior express written permission.

  No license under any patent, copyright, trade secret or other intellectual
  property right is granted to or conferred upon you by disclosure or delivery
  of the Materials, either expressly, by implication, inducement, estoppel or
  otherwise. Any license under such intellectual property rights must be
  express and approved by Intel in writing.

  Unless otherwise agreed by Intel in writing, you may not remove or alter
  this notice or any other notice embedded in Materials by Intel or
  Intel's suppliers or licensors in any way.

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/


#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>

#include "MsgPrintf.h"


/**
  Check the ASCII character is digital or not.

  @param[in] c                    The ASCII character to be checked.

  @retval TRUE                    The ASCII character is digital.
  @retval FALSE                   The ASCII character is not digital.
**/
BOOLEAN
AsciiIsDigit (
  IN CHAR8 c
)
{
  return (('0' <= (c)) && ((c) <= '9'));
}

/**
  Check the ASCII character is alphabet or not.

  @param[in] c                    The ASCII character to be checked.

  @retval TRUE                    The ASCII character is alphabet.
  @retval FALSE                   The ASCII character is not alphabet.
**/
BOOLEAN
AsciiIsAlphabet (
  IN CHAR8 c
)
{
  //
  // <alnum> ::= [0-9] | [a-z] | [A-Z]
  //
  return (/* (('0' <= (c)) && ((c) <= '9')) || */
          (('a' <= (c)) && ((c) <= 'z')) ||
          (('A' <= (c)) && ((c) <= 'Z')));
}

/**
  Dump content of buffer on screen.

  @param[in] Buffer               Pointer to the buffer for dump.
  @param[in] Size                 This Size of the buffer.
**/
VOID
RawdataDump (
  IN VOID *Buffer,
  IN UINTN Size
)
{
  UINTN i;
  UINTN remain;
  UINT8 *p;
  CHAR16 sz[(RAWDATADUMP_COLNUM_PER_ROW + 1)];
  CHAR16 *q;

  p = (UINT8 *)Buffer;
  q = sz;

  MSGPRINTF ((_T("           00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F - 0123456789ABCDEF\r\n")));
  for(i = 0; i < Size; i++) {
    if((i % RAWDATADUMP_COLNUM_PER_ROW) == 0) {
      MSGPRINTF ((_T("[%08x] "), i));
    }

    MSGPRINTF ((_T("%02x "),p[i]));
    if(AsciiIsDigit (p[i]) || AsciiIsAlphabet (p[i])) {
      AsciiSPrint ((char *)q++, RAWDATADUMP_COLNUM_PER_ROW+1, "%c", p[i]);
    } else {
      AsciiSPrint ((char *)q++, RAWDATADUMP_COLNUM_PER_ROW+1, "%c", '.');
    }

    if(((i+1) % RAWDATADUMP_COLNUM_PER_ROW) == 0) {
      remain = (i+1) % RAWDATADUMP_COLNUM_PER_ROW;
      *q = 0;
      MSGPRINTF ((_T("- %s\r\n"), sz));
      q = sz;
    }
  }

  remain = i % RAWDATADUMP_COLNUM_PER_ROW;
  if (remain != 0) {
    for (i = 0; i < (RAWDATADUMP_COLNUM_PER_ROW - remain); i++) {
      MSGPRINTF ((_T("   ")));
    }
    *q = 0;
    MSGPRINTF ((_T("- %s\r\n"), sz));
  }
}

/**
  Dump content of buffer from serial output.

  @param[in] Buffer               Pointer to the buffer for dump.
  @param[in] Size                 This Size of the buffer.
**/
VOID
DbgRawdataDump (
  IN VOID *Buffer,
  IN UINTN Size
)
{
  UINTN i;
  UINTN remain;
  UINT8 *p;
  CHAR16 sz[(RAWDATADUMP_COLNUM_PER_ROW + 1)];
  CHAR16 *q;

  p = (UINT8 *)Buffer;
  q = sz;

  DEBUG ((DEBUG_INFO, "           00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F - 0123456789ABCDEF\r\n"));
  for(i = 0; i < Size; i++) {
    if((i % RAWDATADUMP_COLNUM_PER_ROW) == 0) {
      DEBUG ((DEBUG_INFO, "[%08x] ", i));
    }

    DEBUG ((DEBUG_INFO, "%02x ",p[i]));
    if(AsciiIsDigit (p[i]) || AsciiIsAlphabet (p[i])) {
      AsciiSPrint ((char *)q++, RAWDATADUMP_COLNUM_PER_ROW+1, "%c", p[i]);
    } else {
      AsciiSPrint ((char *)q++, RAWDATADUMP_COLNUM_PER_ROW+1, "%c", '.');
    }

    if(((i+1) % RAWDATADUMP_COLNUM_PER_ROW) == 0) {
      remain = (i+1) % RAWDATADUMP_COLNUM_PER_ROW;
      *q = 0;
      DEBUG ((DEBUG_INFO, "- %s\r\n", sz));
      q = sz;
    }
  }

  remain = i % RAWDATADUMP_COLNUM_PER_ROW;
  if (remain != 0) {
    for (i = 0; i < (RAWDATADUMP_COLNUM_PER_ROW - remain); i++) {
      DEBUG ((DEBUG_INFO, "   "));
    }
    *q = 0;
    DEBUG ((DEBUG_INFO, "- %s\r\n", sz));
  }
}


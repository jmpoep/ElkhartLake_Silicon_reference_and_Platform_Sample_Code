/** @file
  Implementation file for ASCII related functionality.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <Uefi.h>

#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Protocol/JhiProtocol.h>
#include "JhiInternal.h"

/**
  Convert ASCII character to upper case.

  @param[in] c                    The ASCII character to be converted.

  @retval                         The upper case of this ASCII character.
**/
CHAR8
InternalAsciiToUpper (
  IN CHAR8 c
  )
{
  if ('a' <= c && c <= 'z') {
    c = (c - 0x20);
  }

  return c;
}

/**
  Convert ASCII character to lower case.

  @param[in] c                    The ASCII character to be converted.

  @retval                         The lower case of this ASCII character.
**/
CHAR8
AsciiToLower (
  IN CHAR8 c
  )
{
  if (('A' <= (c)) && ((c) <= 'Z')) {
    return (c - ('A' - 'a'));
  }

  return (c);
}

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
  return (
    /* (('0' <= (c)) && ((c) <= '9')) || */
    (('a' <= (c)) && ((c) <= 'z')) ||
    (('A' <= (c)) && ((c) <= 'Z')));
}

/**
  Convert ASCII character to hex value.

  @param[in] c                    The ASCII character to be converted.

  @retval                         The hex value of this ASCII character.
**/
UINT8
AsciiChar2Hex (
  IN CHAR8 c
  )
{
  if (AsciiIsDigit (c)) {
    return (c - '0');
  } else {
    return (InternalAsciiToUpper (c) - 'A' + 0xA);
  }
}

/**
  Convert hex value to ASCII character.

  @param[in] h                    The hex value to be converted.

  @retval                         The ASCII character of this hex value.
**/
CHAR8
AsciiHex2Char (
  UINT8 h
  )
{
  if (h < 10)
    return '0' + h;
  else
    return 'a' + h - 10;
}

/**
  Check the ASCII string is UUID format#1 or not.
  EX: UUID format#1: "A9AB50A7222C434D943BEBB886186BF0"

  @param[in] str                  The ASCII string to be checked.

  @retval TRUE                    The ASCII string is UUID format.
  @retval FALSE                   The ASCII string is not UUID format.
**/
BOOLEAN
AsciiStrIsUuid1 (  // string_check1_uuid
  IN CONST CHAR8 *str
  )
{
  UINTN i;

  if (AsciiStrLen (str) != APPID_STR_LENGTH)
    return FALSE;

  for (i=0; i<APPID_STR_LENGTH; i++, str++)
    if (! ((*str >= '0' && *str <= '9') ||
        (*str >= 'a' && *str <= 'f') ||
        (*str >= 'A' && *str <= 'F')))
    return FALSE;

  return TRUE;
}

/**
  Check the ASCII string is UUID format#2 or not.
  EX: UUID format#1: "A9AB50A7-222C-434D-943B-EBB886186BF0"

  @param[in] str                  The ASCII string to be checked.

  @retval TRUE                    The ASCII string is UUID format.
  @retval FALSE                   The ASCII string is not UUID format.
**/
BOOLEAN
AsciiStrIsUuid2 (  // string_check2_uuid
  IN CONST CHAR8 *str
  )
{
  UINTN i;

  if (AsciiStrLen (str) != APPID_STR_LENGTH + 4)
    return FALSE;

  for (i=0; i<APPID_STR_LENGTH; i++, str++) {
    if (*str == '-' && (i==8 || i==12 || i==16 || i== 20))
      str++;
    if (! ((*str >= '0' && *str <= '9') ||
           (*str >= 'a' && *str <= 'f') ||
           (*str >= 'A' && *str <= 'F')))
      return FALSE;
  }

  return TRUE;
}

/**
  Convert the ASCII string to UUID format.

  @param[in] str                  The ASCII string to be converted.
  @param[out] uuid                The pointer of buffer to store UUID format.

  @retval TRUE                    The conversion is successful.
  @retval FALSE                   The conversion is failed.
**/
BOOLEAN
AsciiStr2Uuid ( // string_to_uuid
  IN CONST CHAR8 *str,
  OUT UINT8 *uuid
  )
{
  UINTN i;

  if (!AsciiStrIsUuid1 (str) && !AsciiStrIsUuid2 (str))
    return FALSE;

  for (i=0; i<APPID_BIN_LENGTH; i++, uuid++) {
    if (*str == '-')
      str++;

    *uuid = (UINT8) AsciiChar2Hex (*str++);
    *uuid <<= 4;
    *uuid += (UINT8) AsciiChar2Hex (*str++);
  }

  return TRUE;
}

/**
  Convert the UUID format to ASCII string.

  @param[in] uuid                 The pointer to the UUID format to be converted.
  @param[out] str                 The pointer to the converted ASCII string.

  @retval TRUE                    The conversion is successful.
  @retval FALSE                   The conversion is failed.
**/
BOOLEAN
AsciiUuid2Str ( // uuid_to_string
  IN UINT8 *uuid,
  OUT CHAR8 *str
  )
{
  UINTN Index;

  str [APPID_STR_LENGTH] = 0;
  for (Index = 0; Index < APPID_BIN_LENGTH; Index++, uuid++) {
    *str++ = AsciiHex2Char ((*uuid & 0xf0) >> 4);
    *str++ = AsciiHex2Char (*uuid & 0xf);
  }

  return TRUE;
}


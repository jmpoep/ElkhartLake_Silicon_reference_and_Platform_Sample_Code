/** @file
  Header file for JHI helper functionality.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef __DXE_JHI_SUPPORT_LIB_H__
#define __DXE_JHI_SUPPORT_LIB_H__


//
// File
//
#include <Protocol/SimpleFileSystem.h>
#include <Guid/FileInfo.h>


/**
  Open file.

  @param[in] Filename             The file to be opened.
                                  Filename should be absolute path+filename, ie: L"\\Jhi\\TestApplet.sign"
  @param[out] FileHandle          Pointer to the file handle.

  @retval EFI_SUCCESS             File open successfully.
  @retval EFI_INVALID_PARAMETER   Input parameters are invalid.
  @retval                         Others for error status code of LocateHandleBuffer, HandleProtocol,  OpenVolume, and Open functions.
**/
EFI_STATUS
FileOpen (
  IN  CHAR16 *Filename,
  OUT EFI_FILE **FileHandle
);

/**
  Close file and relase all allocated resource.

  @param[in] FileHandle          Pointer to the file handle.

  @retval EFI_SUCCESS             File close successfully.
  @retval EFI_INVALID_PARAMETER   Input parameters are invalid.
  @retval                         Others for error status code of Close function.
**/
EFI_STATUS
FileClose (
  IN  EFI_FILE *FileHandle
);

/**
  Read file contents to the buffer.

  @param[in] FileHandle           Pointer to the file handle.
  @param[out] Buffer              Pointer to the buffer for read.
  @param[out] BufferSize          Pointer to the buffer size for read.

  @retval EFI_SUCCESS             File read successfully.
  @retval EFI_INVALID_PARAMETER   Input parameters are invalid.
  @retval EFI_OUT_OF_RESOURCES    Memory allocation fail.
  @retval                         Others for error status code of GetInfo, and Read functions.
**/
EFI_STATUS
FileRead (
  IN  EFI_FILE *FileHandle,
  OUT VOID    **Buffer,
  OUT UINTN   *BufferSize
);

//
// StrHelper
//
/**
  Convert ASCII character to upper case.

  @param[in] c                    The ASCII character to be converted.

  @retval                         The upper case of this ASCII character.
**/
CHAR8
InternalAsciiToUpper (
  IN CHAR8 c
);

/**
  Convert ASCII character to lower case.

  @param[in] c                    The ASCII character to be converted.

  @retval                         The lower case of this ASCII character.
**/
CHAR8
AsciiToLower (
  IN CHAR8 c
);

/**
  Check the ASCII character is digital or not.

  @param[in] c                    The ASCII character to be checked.

  @retval TRUE                    The ASCII character is digital.
  @retval FALSE                   The ASCII character is not digital.
**/
BOOLEAN
AsciiIsDigit (
  IN CHAR8 c
);

/**
  Check the ASCII character is alphabet or not.

  @param[in] c                    The ASCII character to be checked.

  @retval TRUE                    The ASCII character is alphabet.
  @retval FALSE                   The ASCII character is not alphabet.
**/
BOOLEAN
AsciiIsAlphabet (
  IN CHAR8 c
);

/**
  Convert ASCII character to hex value.

  @param[in] c                    The ASCII character to be converted.

  @retval                         The hex value of this ASCII character.
**/
UINT8
AsciiChar2Hex (
  IN CHAR8 c
);

/**
  Convert hex value to ASCII character.

  @param[in] h                    The hex value to be converted.

  @retval                         The ASCII character of this hex value.
**/
CHAR8
AsciiHex2Char (
  UINT8 h
);

/**
  Check the ASCII string is UUID format#1 or not.
  EX: UUID format#1: "A9AB50A7222C434D943BEBB886186BF0"

  @param[in] str                  The ASCII string to be checked.

  @retval TRUE                    The ASCII string is UUID format.
  @retval FALSE                   The ASCII string is not UUID format.
**/
BOOLEAN
AsciiStrIsUuid1 (
  IN CONST CHAR8 *str
);

/**
  Check the ASCII string is UUID format#2 or not.
  EX: UUID format#2: "A9AB50A7-222C-434D-943B-EBB886186BF0"

  @param[in] str                  The ASCII string to be checked.

  @retval TRUE                    The ASCII string is UUID format.
  @retval FALSE                   The ASCII string is not UUID format.
**/
BOOLEAN
AsciiStrIsUuid2 (
  IN CONST CHAR8 *str
);

/**
  Convert the ASCII string to UUID format.

  @param[in] str                  The ASCII string to be converted.
  @param[out] uuid                The pointer of buffer to store UUID format.

  @retval TRUE                    The conversion is successful.
  @retval FALSE                   The conversion is failed.
**/
BOOLEAN
AsciiStr2Uuid (
  IN CONST CHAR8 *str,
  OUT UINT8 *uuid
);

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
);


//
// MsgPrint
//
#include <Library/PrintLib.h>

#define MSGPRINTF(s)                  Print s
#ifndef _T
#define _T(x)                         L##x
#endif
#define MSGRAWDUMP(s)                 RawdataDump s

#define RAWDATADUMP_COLNUM_PER_ROW    16

VOID
RawdataDump (
  IN VOID *buff,
  IN UINTN size
);

VOID
DbgRawdataDump (
  IN VOID *buff,
  IN UINTN size
);

#endif // __DXE_JHI_SUPPORT_LIB_H__


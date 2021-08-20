/** @file
  Header file for functionality of file access

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

#ifndef __FILE_H__
#define __FILE_H__


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


#endif // __FILE_H__


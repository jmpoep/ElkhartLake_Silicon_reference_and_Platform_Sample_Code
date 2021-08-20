/** @file
  Miscellaneous services internal to RAM debug implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>

/**
  Initialize for RamDebugLib library instance.

  Initialization including: RAM.

**/
VOID
EFIAPI
RamDebugInitialize (
  VOID
  )
{
  return;
}

/**
  Write data from buffer to RAM debug.

  This function must be called post memory.
  Writes NumberOfBytes data bytes from Buffer to the RAM device.
  The number of bytes actually written to the RAM device is returned.
  If the return value is less than NumberOfBytes, then the write operation failed.
  If Buffer is NULL, then ASSERT().
  If NumberOfBytes is zero, then return 0.

  @param  Buffer           Pointer to the data buffer to be written.
  @param  NumberOfBytes    Number of bytes to written to the RAM device.

  @retval 0                NumberOfBytes is 0.
  @retval >0               The number of bytes written to the RAM device.
                           If this value is less than NumberOfBytes, then the read operation failed.

**/
UINTN
EFIAPI
RamDebugWrite (
  IN UINT8     *Buffer,
  IN UINTN     NumberOfBytes
  )
{
  CHAR8   *CharPtr;
  UINT32  *LenPtr;
  UINT32  LogLen;
  UINT16  LogOffset;
  UINTN   Index;

  //
  // RamDebug buffer layout for this instance:
  // +---------------------+
  // |Length| DebugMessage |
  // +---------------------+
  // Length is UINT32, it is total debug message received plug UINT32 Length field.
  // The first UINT16 is regarded as offset, because total buffer length is 0x10000.
  //

  LenPtr  = (UINT32 *)(UINTN)(PcdGet32 (PcdRamLogBaseAddress));
  LogLen  = *LenPtr;
  LogOffset = (UINT16)LogLen;
  if (LogOffset == 0) {
    LogLen += sizeof(LogLen);
    LogOffset += sizeof(LogLen);
  }
  CharPtr = (CHAR8 *)(UINTN)(PcdGet32 (PcdRamLogBaseAddress) + LogOffset);

  for (Index = 0; Index < NumberOfBytes; Index++) {
    if (LogOffset == 0) {
      //
      // Roll back for 16bit Len field
      //
      LogLen += sizeof(LogLen);
      LogOffset += sizeof(LogLen);
      CharPtr = (CHAR8 *)(UINTN)(PcdGet32 (PcdRamLogBaseAddress) + LogOffset);
    }
    *CharPtr++ = *Buffer++;
    LogOffset ++;
    LogLen ++;
  }

  //
  // Update the buffer length word.
  //
  *LenPtr = LogLen;

  return NumberOfBytes;
}

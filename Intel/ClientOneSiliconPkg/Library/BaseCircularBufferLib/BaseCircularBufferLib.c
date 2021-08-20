/** @file
  Implementation file for the Circular Buffer Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/CircularBufferLib.h>

/**
  Returns the number of bytes in the circular buffer.

  @param[in]    CircularBufferPtr  A pointer to a circular buffer of type CIRCULAR_BUFFER

  @retval       UINTN              The number of bytes in the circular buffer
**/
UINTN
EFIAPI
CircularBufferGetUsedSpace (
  IN  CIRCULAR_BUFFER* CONST  CircularBufferPtr
  )
{
  if (CircularBufferPtr == NULL) {
    return 0;
  }

  return (CircularBufferPtr->Head >= CircularBufferPtr->Tail)  ?
           (CircularBufferPtr->Head - CircularBufferPtr->Tail) :
           (CircularBufferPtr->Capacity - CircularBufferPtr->Tail + CircularBufferPtr->Head);
}

/**
  Returns the number of available bytes in the circular buffer.

  @param[in]    CircularBufferPtr  A pointer to a circular buffer of type CIRCULAR_BUFFER

  @retval       UINTN              The number of bytes free in the circular buffer
**/
UINTN
EFIAPI
CircularBufferGetFreeSpace (
  IN  CIRCULAR_BUFFER* CONST  CircularBufferPtr
  )
{
  if (CircularBufferPtr == NULL) {
    return 0;
  }

  return (CircularBufferPtr->Head < CircularBufferPtr->Tail)   ?
           (CircularBufferPtr->Tail - CircularBufferPtr->Head) :
           (CircularBufferPtr->Capacity - CircularBufferPtr->Head + CircularBufferPtr->Tail);
}

/**
  Resets the circular buffer to an initial state and clears all buffer data.

  @param[in]    CircularBufferPtr      A pointer to a circular buffer of type CIRCULAR_BUFFER

  @retval       EFI_INVALID_PARAMETER  The CircularBufferPtr or the internal buffer is null
  @retval       EFI_SUCCESS            The circular buffer was reset successfully
**/
EFI_STATUS
EFIAPI
CircularBufferReset (
  IN OUT  CIRCULAR_BUFFER* CONST CircularBufferPtr
  )
{
  if (CircularBufferPtr == NULL || CircularBufferPtr->Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (CircularBufferPtr->Buffer, CircularBufferPtr->Capacity);

  CircularBufferPtr->Head  = 0;
  CircularBufferPtr->Tail  = 0;
  CircularBufferPtr->Count = 0;

  return EFI_SUCCESS;
}

/**
  Updates a circular buffer index (ie. head, tail)

  @param[in]    CircularBufferPtr      A pointer to a circular buffer of type CIRCULAR_BUFFER
  @param[in]    Index                  A pointer to the index to update
  @param[in]    DataSize               The number of bytes to apply to the index

  @retval       EFI_INVALID_PARAMETER  The CircularBufferPtr or IndexPtr parameter is null
  @retval       EFI_SUCCESS            The index was updated successfully
**/
EFI_STATUS
EFIAPI
CircularBufferUpdateIndex (
  IN     CIRCULAR_BUFFER* CONST     CircularBufferPtr,
  IN OUT UINTN* CONST               IndexPtr,
  IN     UINTN                      DataSize
  )
{
  if (CircularBufferPtr == NULL || IndexPtr == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (CircularBufferPtr->Capacity - *IndexPtr <= DataSize) {
    *IndexPtr = *IndexPtr + DataSize - CircularBufferPtr->Capacity;
  } else {
    *IndexPtr += DataSize;
  }

  return EFI_SUCCESS;
}

/**
  Adds a buffer of data to the circular buffer.

  @param[in,out]  CircularBufferPtr      A pointer to a circular buffer of type CIRCULAR_BUFFER
  @param[in]      DataBufferPtr          A pointer to a source data buffer
  @param[in]      DataSize               The number of bytes to copy from DataBufferPtr to the circular buffer

  @retval         EFI_INVALID_PARAMETER  The CircularBufferPtr or DataBufferPtr parameter is null
  @retval         EFI_OUT_OF_RESOURCES   The source DataSize is too big for the circular buffer
  @retval         EFI_SUCCESS            The data was added to the circular buffer successfully
**/
EFI_STATUS
EFIAPI
CircularBufferEnqueue (
  IN OUT       CIRCULAR_BUFFER* CONST     CircularBufferPtr,
  IN     CONST UINT8                      *DataBufferPtr,
  IN           UINTN                      DataSize
  )
{
  UINTN  RemainingBufferSpace;
  UINTN  EnqueueSizeInitialHalf;

  if (CircularBufferPtr == NULL || CircularBufferPtr->Buffer == NULL || DataBufferPtr == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (DataSize == 0) {
    return EFI_SUCCESS;
  }

  RemainingBufferSpace = CircularBufferGetFreeSpace (CircularBufferPtr);
  if (RemainingBufferSpace < DataSize) {
    return EFI_OUT_OF_RESOURCES;
  }

  DataSize               = MIN (DataSize, RemainingBufferSpace);
  EnqueueSizeInitialHalf = MIN (DataSize, CircularBufferPtr->Capacity - CircularBufferPtr->Head);

  CopyMem (&CircularBufferPtr->Buffer[CircularBufferPtr->Head], DataBufferPtr, EnqueueSizeInitialHalf);
  CopyMem (&CircularBufferPtr->Buffer[0], &DataBufferPtr[EnqueueSizeInitialHalf], DataSize - EnqueueSizeInitialHalf);

  CircularBufferPtr->Count++;

  return CircularBufferUpdateIndex (CircularBufferPtr, &(CircularBufferPtr->Head), DataSize);
}

/**
  Adds a data buffer to the circular buffer in a particular alignment.

  @param[in,out]  CircularBufferPtr      A pointer to a circular buffer of type CIRCULAR_BUFFER
  @param[in]      DataBufferPtr          A pointer to a source data buffer
  @param[in]      DataSize               The number of bytes to copy from DataBufferPtr to the circular buffer
  @param[in]      ByteAlignment          Specifies a particular alignment boundary (in bytes)

  @retval         EFI_INVALID_PARAMETER  The CircularBufferPtr or DataBufferPtr parameter is null
  @retval         EFI_OUT_OF_RESOURCES   The source DataSize is too big for the circular buffer
  @retval         EFI_SUCCESS            The data was added to the circular buffer successfully
**/
EFI_STATUS
EFIAPI
CircularBufferEnqueueAligned (
  IN OUT       CIRCULAR_BUFFER* CONST     CircularBufferPtr,
  IN     CONST UINT8                      *DataBufferPtr,
  IN           UINTN                      DataSize,
  IN           UINT8                      ByteAlignment
  )
{
  if (CircularBufferPtr == NULL || CircularBufferPtr->Buffer == NULL || DataBufferPtr == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (DataSize == 0) {
    return EFI_SUCCESS;
  }

  CircularBufferPtr->Head = CIRCULAR_BUFFER_DATA_ALIGN (CircularBufferPtr->Head, ByteAlignment);
  return CircularBufferEnqueue (CircularBufferPtr, DataBufferPtr, DataSize);
}

/**
  Returns a buffer of data from the circular buffer.

  @param[in,out]  CircularBufferPtr      A pointer to a circular buffer of type CIRCULAR_BUFFER
  @param[out]     DataBufferPtr          A pointer to a destination data buffer
  @param[in]      DataSize               The number of bytes to copy from the circular buffer to DataBufferPtr

  @retval         EFI_INVALID_PARAMETER  The CircularBufferPtr or DataBufferPtr parameter is null
  @retval         EFI_BUFFER_TOO_SMALL   The DataSize is larger than data in the circular buffer
  @retval         EFI_SUCCESS            The data was retrieved from the circular buffer successfully
**/
EFI_STATUS
EFIAPI
CircularBufferDequeue (
  IN OUT CIRCULAR_BUFFER* CONST      CircularBufferPtr,
  OUT    UINT8* CONST                DataBufferPtr,
  IN     UINTN                       DataSize
  )
{
  UINTN  UsedBufferSpace;
  UINTN  DequeueSizeInitialHalf;

  if (CircularBufferPtr == NULL || CircularBufferPtr->Buffer == NULL || DataBufferPtr == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (DataSize == 0) {
    return EFI_SUCCESS;
  }

  UsedBufferSpace = CircularBufferGetUsedSpace (CircularBufferPtr);
  if (DataSize > UsedBufferSpace) {
    return EFI_BUFFER_TOO_SMALL;
  }

  DataSize               = MIN (DataSize, UsedBufferSpace);
  DequeueSizeInitialHalf = MIN (DataSize, CircularBufferPtr->Capacity - CircularBufferPtr->Tail);

  CopyMem (DataBufferPtr, &CircularBufferPtr->Buffer[CircularBufferPtr->Tail], DequeueSizeInitialHalf);
  CopyMem (&DataBufferPtr[DequeueSizeInitialHalf], &CircularBufferPtr->Buffer[0], DataSize - DequeueSizeInitialHalf);

  CircularBufferPtr->Count--;

  return CircularBufferUpdateIndex (CircularBufferPtr, &(CircularBufferPtr->Tail), DataSize);
}
/** @file
  Memory controller buffer allocation routines.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
//
// Include files
//
#include "MrcMalloc.h"

typedef struct {
  UINT8 *BufBase;
  UINT32  BufLimit;
  union {
    struct {
      UINT8 Occupied : 1;
      UINT8 HeapEnd  : 1;
    } Bits;
    UINT8 Data;
  } BufFlags;
} HeapBufHeader;

/**
  Function used to initialize the MRC memory used for heap.

  @param[in, out] MrcData  - The MRC global data area.
  @param[in]      Base     - The base address of the heap.
  @param[in]      Size     - Amount of memory in bytes to allocate.

  @retval Returns a pointer to an allocated memory block on success or NULL on failure.
**/
MrcStatus
MrcHeapInitialize (
  MrcParameters *const MrcData,
  void          *Base,
  UINT32        Size
  )
{
  MrcInput       *Inputs;
  UINT8          *HeapLimitPtr;
  HeapBufHeader  *HeapBase;
  UINT8          *BaseAddr;

  Inputs = &MrcData->Inputs;

  //
  // If heap is provided
  //
  if ((Base != NULL) && (Size > 0)) {
    BaseAddr     = (UINT8 *) Base;
    HeapLimitPtr = BaseAddr + Size;

    //
    // Initialize the start header
    //
    HeapBase                 = (HeapBufHeader *) BaseAddr;
    HeapBase->BufBase        = BaseAddr + sizeof (HeapBufHeader);
    HeapBase->BufLimit       = Size - (2 * sizeof (HeapBufHeader));
    HeapBase->BufFlags.Data  = 0;

    //
    // Initialize the end header
    //
    HeapBase                        = (HeapBufHeader *) (HeapLimitPtr - sizeof (HeapBufHeader));
    HeapBase->BufBase               = HeapLimitPtr;
    HeapBase->BufLimit              = 0;
    HeapBase->BufFlags.Bits.HeapEnd = 1;
  }
  Inputs->HeapBase.Ptr  = Base;
  Inputs->HeapSize      = Size;
  return (((Base != NULL) && (Size > 0)) ? mrcSuccess : mrcFail);
}

/**
  Function used to dynamically allocate memory.

  @param[in, out] MrcData - The MRC global data area.
  @param[in]         Size - Amount of memory in bytes to allocate.

  @retval Returns a pointer to an allocated memory block on success or NULL on failure.
**/
void *
MrcHeapMalloc (
  MrcParameters *const MrcData,
  UINT32               Size
  )
{
  const MrcInput *Inputs;
  HeapBufHeader  *HeaderPtr;
  HeapBufHeader  *NextHeaderPtr;
  void           *Allocated;

  Allocated = NULL;
  Inputs    = &MrcData->Inputs;
  if ((Size != 0) && (Inputs->HeapSize != 0)) {
    //
    // Round size up to a QWORD integral.
    //
    Size += sizeof (UINT64) - (Size % sizeof (UINT64));

    //
    // Check to see if request exceeds available heap size.
    //
    if (Size <= (Inputs->HeapSize - (3 * sizeof (HeapBufHeader)))) {
      HeaderPtr = (HeapBufHeader *) Inputs->HeapBase.Ptr;

      //
      // Walk the heap looking for an available buffer.
      //
      while ((HeaderPtr->BufFlags.Bits.Occupied > 0) || ((HeaderPtr->BufLimit < Size) && (HeaderPtr->BufFlags.Bits.HeapEnd == 0))) {
        HeaderPtr = (HeapBufHeader *) (HeaderPtr->BufBase + HeaderPtr->BufLimit);
      }

      //
      // Check for the end of heap space.
      //
      if (HeaderPtr->BufFlags.Bits.HeapEnd <= 0) {
        //
        // Lock memory for the buffer.
        //
        HeaderPtr->BufFlags.Bits.Occupied = 1;

        //
        // Initialize the current size and next header if required.
        //
        if ((HeaderPtr->BufLimit - Size) > sizeof (HeapBufHeader)) {
          NextHeaderPtr                = (HeapBufHeader *) (HeaderPtr->BufBase + Size);
          NextHeaderPtr->BufBase       = (UINT8 *) NextHeaderPtr + sizeof (HeapBufHeader);
          NextHeaderPtr->BufLimit      = HeaderPtr->BufLimit - Size - sizeof (HeapBufHeader);
          NextHeaderPtr->BufFlags.Data = 0;
          HeaderPtr->BufLimit          = Size;
        }

        //
        // Return the current base.
        //
        Allocated = (void *) HeaderPtr->BufBase;
      }
    }
  }
  return (Allocated);
}

/**
  Function used to release memory allocated using MrcMalloc.

  @param[in, out] MrcData - The MRC global data area.
  @param[in]      Buffer  - The buffer to return to the free pool.

  @retval Nothing.
**/
void
MrcHeapFree (
  MrcParameters *const MrcData,
  void                 *Buffer
  )
{
  const MrcInput *Inputs;
  HeapBufHeader  *HeaderPtr;
  HeapBufHeader  *TempPtr;

  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "MRC free base = %08Xh\n", Buffer);
  Inputs  = &MrcData->Inputs;
  if ((Inputs->HeapBase.Ptr != 0) && (Inputs->HeapSize > 0)) {
    //
    // Initialize a pointer to the given buffer header.
    //
    HeaderPtr = (HeapBufHeader *) ((UINT8 *) Buffer - sizeof (HeapBufHeader));

    //
    // Validate the given pointer before proceeding.
    //
    if (HeaderPtr->BufBase == Buffer) {
      //
      // Free the given buffer.
      //
      HeaderPtr->BufFlags.Bits.Occupied = 0;

      //
      // Initialize the root header.
      //
      HeaderPtr = (HeapBufHeader *) Inputs->HeapBase.Ptr;

      //
      // Walk the heap looking for holes to merge.
      //
      do {
        //
        // Find the next hole.
        //
        while (HeaderPtr->BufFlags.Bits.Occupied > 0) {
          HeaderPtr = (HeapBufHeader *) (HeaderPtr->BufBase + HeaderPtr->BufLimit);
        }

        //
        // Check for the end of heap space.
        //
        if (HeaderPtr->BufFlags.Bits.HeapEnd > 0) {
          break;
        }

        //
        // Look for adjacent holes to merge.
        //
        TempPtr = (HeapBufHeader *) (HeaderPtr->BufBase + HeaderPtr->BufLimit);
        while ((TempPtr->BufFlags.Bits.Occupied == 0) && (TempPtr->BufFlags.Bits.HeapEnd == 0)) {
          //
          // Add this buffer to the current limit and move to the next buffer.
          //
          HeaderPtr->BufLimit += TempPtr->BufLimit + sizeof (HeapBufHeader);
          TempPtr = (HeapBufHeader *) (TempPtr->BufBase + TempPtr->BufLimit);
        }
        //
        // Move to the next buffer.
        //
        HeaderPtr = (HeapBufHeader *) (HeaderPtr->BufBase + HeaderPtr->BufLimit);

      } while (HeaderPtr->BufFlags.Bits.HeapEnd == 0);
    }
  }
  return;
}

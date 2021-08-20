/** @file
  Handles non-volatile variable store garbage collection, using FTW
  (Fault Tolerant Write) protocol.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016-2018 Intel Corporation.

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

@par Specification
**/

#include "FvbVariableStorage.h"

/**
  Gets LBA of block and offset by given address.

  This function gets the Logical Block Address (LBA) of a firmware
  volume block containing the given address, and the offset of the
  address on the block.

  @param  Address        Address which should be contained
                         by returned FVB handle.
  @param  Lba            Pointer to LBA for output.
  @param  Offset         Pointer to offset for output.

  @retval EFI_SUCCESS    LBA and offset successfully returned.
  @retval EFI_NOT_FOUND  Fail to find FVB handle by address.
  @retval EFI_ABORTED    Fail to find valid LBA and offset.

**/
EFI_STATUS
GetLbaAndOffsetByAddress (
  IN  EFI_PHYSICAL_ADDRESS   Address,
  OUT EFI_LBA                *Lba,
  OUT UINTN                  *Offset
  )
{
  EFI_STATUS                          Status;
  EFI_PHYSICAL_ADDRESS                FvbBaseAddress;
  EFI_FIRMWARE_VOLUME_BLOCK_PROTOCOL  *Fvb;
  EFI_FIRMWARE_VOLUME_HEADER          *FwVolHeader;
  EFI_FV_BLOCK_MAP_ENTRY              *FvbMapEntry;
  UINT32                              LbaIndex;

  Fvb     = NULL;
  *Lba    = (EFI_LBA) (-1);
  *Offset = 0;

  //
  // Get the proper FVB protocol.
  //
  Status = GetFvbInfoByAddress (Address, NULL, &Fvb);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the Base Address of FV.
  //
  Status = Fvb->GetPhysicalAddress (Fvb, &FvbBaseAddress);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  FwVolHeader = (EFI_FIRMWARE_VOLUME_HEADER *) ((UINTN) FvbBaseAddress);

  //
  // Get the (LBA, Offset) of Address.
  //
  if ((FwVolHeader->FvLength) > (FwVolHeader->HeaderLength)) {
    //
    // BUGBUG: Assume one FV has one type of BlockLength.
    //
    FvbMapEntry = &FwVolHeader->BlockMap[0];
    for (LbaIndex = 1; LbaIndex <= FvbMapEntry->NumBlocks; LbaIndex += 1) {
      if (Address < (FvbBaseAddress + FvbMapEntry->Length * LbaIndex)) {
        //
        // Found the (Lba, Offset).
        //
        *Lba    = LbaIndex - 1;
        *Offset = (UINTN) (Address - (FvbBaseAddress + FvbMapEntry->Length * (LbaIndex - 1)));
        return EFI_SUCCESS;
     }
    }
  }

  return EFI_ABORTED;
}

/**
  Writes a buffer to variable storage space, in the working block.

  This function writes a buffer to variable storage space into a firmware
  volume block device. The destination is specified by parameter
  VariableBase. Fault Tolerant Write protocol is used for writing.

  @param  VariableBase   Base address of variable to write
  @param  VariableBuffer Point to the variable data buffer.

  @retval EFI_SUCCESS    The function completed successfully.
  @retval EFI_NOT_FOUND  Fail to locate Fault Tolerant Write protocol.
  @retval EFI_ABORTED    The function could not complete successfully.

**/
EFI_STATUS
FtwVariableSpace (
  IN EFI_PHYSICAL_ADDRESS   VariableBase,
  IN VARIABLE_STORE_HEADER  *VariableBuffer
  )
{
  EFI_STATUS                         Status;
  EFI_HANDLE                         FvbHandle;
  EFI_LBA                            VarLba;
  UINTN                              VarOffset;
  UINTN                              FtwBufferSize;
  EFI_FAULT_TOLERANT_WRITE_PROTOCOL  *FtwProtocol;

  //
  // Locate fault tolerant write protocol.
  //
  Status = GetFtwProtocol ((VOID **) &FtwProtocol);
  if (EFI_ERROR (Status)) {
    return EFI_NOT_FOUND;
  }
  //
  // Locate Fvb handle by address.
  //
  Status = GetFvbInfoByAddress (VariableBase, &FvbHandle, NULL);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //
  // Get LBA and Offset by address.
  //
  Status = GetLbaAndOffsetByAddress (VariableBase, &VarLba, &VarOffset);
  if (EFI_ERROR (Status)) {
    return EFI_ABORTED;
  }

  FtwBufferSize = ((VARIABLE_STORE_HEADER *) ((UINTN) VariableBase))->Size;
  ASSERT (FtwBufferSize == VariableBuffer->Size);

  //
  // FTW write record.
  //
  Status = FtwProtocol->Write (
                          FtwProtocol,
                          VarLba,         // LBA
                          VarOffset,      // Offset
                          FtwBufferSize,  // NumBytes
                          NULL,           // PrivateData NULL
                          FvbHandle,      // Fvb Handle
                          (VOID *) VariableBuffer // write buffer
                          );

  return Status;
}

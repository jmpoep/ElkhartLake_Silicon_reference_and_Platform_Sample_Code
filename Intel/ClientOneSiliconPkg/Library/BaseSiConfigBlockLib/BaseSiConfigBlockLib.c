/** @file
  This file is BaseSiConfigBlockLib library is used to add config blocks
  to config block header.

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
#include <ConfigBlock.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/SiConfigBlockLib.h>


/**
  GetComponentConfigBlockTotalSize get config block table total size.

  @param[in] ComponentBlocks    Component blocks array
  @param[in] TotalBlockCount    Number of blocks

  @retval                       Size of config block table
**/
UINT16
EFIAPI
GetComponentConfigBlockTotalSize (
  IN COMPONENT_BLOCK_ENTRY *ComponentBlocks,
  IN UINT16                TotalBlockCount
  )
{
  UINT16            TotalBlockSize;
  UINT16            BlockCount;

  TotalBlockSize = 0;
  for (BlockCount = 0 ; BlockCount < TotalBlockCount; BlockCount++) {
    TotalBlockSize += (UINT32) ComponentBlocks[BlockCount].Size;
    DEBUG ((DEBUG_INFO, "TotalBlockSize after adding Block[0x%x]= 0x%x\n", BlockCount, TotalBlockSize));
  }

  return TotalBlockSize;
}

/**
  AddComponentConfigBlocks add all config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add config blocks
  @param[in] ComponentBlocks            Config blocks array
  @param[in] TotalBlockCount            Number of blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
AddComponentConfigBlocks (
  IN VOID                  *ConfigBlockTableAddress,
  IN COMPONENT_BLOCK_ENTRY *ComponentBlocks,
  IN UINT16                TotalBlockCount
  )
{
  UINT16            BlockCount;
  VOID              *ConfigBlockPointer;
  CONFIG_BLOCK      ConfigBlockBuf;
  EFI_STATUS        Status;

  Status = EFI_SUCCESS;

  //
  // Initialize ConfigBlockPointer to NULL
  //
  ConfigBlockPointer = NULL;
  //
  // Loop to identify each config block from ComponentBlocks[] Table and add each of them
  //
  for (BlockCount = 0; BlockCount < TotalBlockCount; BlockCount++) {
    ZeroMem (&ConfigBlockBuf, sizeof (CONFIG_BLOCK));
    CopyMem (&(ConfigBlockBuf.Header.GuidHob.Name), ComponentBlocks[BlockCount].Guid, sizeof (EFI_GUID));
    ConfigBlockBuf.Header.GuidHob.Header.HobLength = ComponentBlocks[BlockCount].Size;
    ConfigBlockBuf.Header.Revision        = ComponentBlocks[BlockCount].Revision;
    ConfigBlockPointer = (VOID *)&ConfigBlockBuf;
    Status = AddConfigBlock ((VOID *)ConfigBlockTableAddress, (VOID *)&ConfigBlockPointer);
    ASSERT_EFI_ERROR (Status);
    ComponentBlocks[BlockCount].LoadDefault (ConfigBlockPointer);
  }
  return Status;
}

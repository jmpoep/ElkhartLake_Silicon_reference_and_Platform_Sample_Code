/** @file
  Platform Info driver to install protocol for DXE and
  creat a PlatformInfo varible.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#include "PlatformInfoDxe.h"

/**
  Entry point for the driver.

  This routine gets info from the PlatformInfo and produces a protocol
  to be consumed by DXE drivers to identify platforms.

  @param[in]  ImageHandle  Image Handle.
  @param[in]  SystemTable  EFI System Table.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
EFIAPI
PlatformInfoInit (
  IN EFI_HANDLE               ImageHandle,
  IN EFI_SYSTEM_TABLE         *SystemTable
  )
{
  EFI_STATUS                             Status;
  DXE_BOARD_CONFIG_INIT                  BoardConfigInit;

  //
  // Init Board Config.
  //
  BoardConfigInit = (DXE_BOARD_CONFIG_INIT) (UINTN) PcdGet64 (PcdFuncBoardConfigInit);
  ASSERT (BoardConfigInit != NULL);
  if (BoardConfigInit == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Status = BoardConfigInit (NULL);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/** @file
  PEI Multi-Board Initialization in Post-Memory PEI Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/BoardInitLib.h>
#include <Library/MultiBoardInitSupportLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>

#include <PlatformBoardId.h>

EFI_STATUS
EFIAPI
EhlBoardInitBeforeSiliconInit (
  VOID
  );

EFI_STATUS
EFIAPI
EhlBoardInitAfterSiliconInit (
  VOID
  );

BOARD_POST_MEM_INIT_FUNC  mEhlBoardInitFunc = {
  EhlBoardInitBeforeSiliconInit,
  EhlBoardInitAfterSiliconInit,
};

EFI_STATUS
EFIAPI
PeiEhlMultiBoardInitLibConstructor (
  VOID
  )
{
  if (LibPcdGetSku () == BoardIdEhlLp4xType4Erb ||
      LibPcdGetSku () == BoardIdEhlLp4xType4Rvp1 ||
      LibPcdGetSku () == BoardIdEhlDdr4Type3Rvp2 ||
      LibPcdGetSku () == BoardIdEhlLp4xType3Crb ||
      LibPcdGetSku () == BoardIdJslLp4xType4Rvp1 ||
      LibPcdGetSku () == BoardIdJslLp4xErb) {
    DEBUG ((DEBUG_INFO, "SKU_ID: 0x%x\n", LibPcdGetSku()));
    return RegisterBoardPostMemInit (&mEhlBoardInitFunc);
  }
  return EFI_SUCCESS;
}

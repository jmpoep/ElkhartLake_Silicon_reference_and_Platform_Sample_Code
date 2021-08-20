/** @file
  Platform FV address library instance to support TopSwap based fault tolerance case.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/SpiAccessLib.h>

/**
  Get Firmware Binary FV base address

  @return FvBase associated with FvBinary FV.
**/
UINT32
GetFvBinaryBase (
  VOID
  )
{
  UINT32 FvBase;
  FvBase = FixedPcdGet32 (PcdFlashFvFirmwareBinariesBase);
  DEBUG ((DEBUG_INFO, "GetFvBinaryBase - :0x%x  ......\n", FvBase));
  return FvBase;
}

/**
  Get Microcode FV base address

  @return FvBase associated with Microcode FV.
**/
UINT32
GetFvMicrocodeBase (
  VOID
  )
{
  UINT32 FvBase;
  FvBase = FixedPcdGet32 (PcdFlashMicrocodeFvBase);
  DEBUG ((DEBUG_INFO, "GetFvMicrocodeBase - :0x%x  ......\n", FvBase));
  return FvBase;
}


/**
  Get Fsp-S base address

  @return FvBase associated with Fsp-S FV.
**/
UINT32
GetFvFspsBase (
  VOID
  )
{
  UINT32 FvBase;
  FvBase = FixedPcdGet32 (PcdFlashFvFspSBase);
  DEBUG ((DEBUG_INFO, "GetFvFspsBase - :0x%x.....\n", FvBase));
  return FvBase;
}

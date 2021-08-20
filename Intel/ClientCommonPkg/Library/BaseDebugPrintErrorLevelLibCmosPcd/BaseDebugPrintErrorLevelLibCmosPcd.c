/** @file
  DebugPrintErrorLevelCmosPcd access library instance.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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
#include <Library/PcdLib.h>
#include <Library/CmosAccessLib.h>

/**
  Returns the debug print error level mask for the current module.

  @retval  Debug print error level mask for the current module.
**/
UINT32
EFIAPI
GetDebugPrintErrorLevel (
  VOID
  )
{
  return CmosRead32 (PcdGet8 (PcdDebugPrintLevelCmosIndex));
}


/**
  Sets the global debug print error level mask fpr the entire platform.

  @param[in]  ErrorLevel     Global debug print error level

  @retval     TRUE           The debug print error level mask was sucessfully set.
  @retval     FALSE          The debug print error level mask could not be set.
**/
BOOLEAN
EFIAPI
SetDebugPrintErrorLevel (
  IN UINT32 ErrorLevel
  )
{
  CmosWrite32 (PcdGet8 (PcdDebugPrintLevelCmosIndex), ErrorLevel);
  return TRUE;
}

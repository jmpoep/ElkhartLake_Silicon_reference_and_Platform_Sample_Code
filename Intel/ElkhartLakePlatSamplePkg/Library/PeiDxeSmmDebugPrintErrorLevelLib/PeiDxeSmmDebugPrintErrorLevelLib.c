/** @file
  Pei/Dxe/Smm DebugPrintErrorLevel library implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 Intel Corporation.

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

#include <Uefi.h>
#include <Pi/PiMultiPhase.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/DebugPrintErrorLevelLib.h>
#include <Setup.h>

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN     mDebugPrintErrorLevelInited = FALSE;
GLOBAL_REMOVE_IF_UNREFERENCED UINT32      mDebugPrintErrorLevel = 0xffffffff;

/**
  Returns the debug print error level mask for the current module.

  @return  Debug print error level mask for the current module.

**/
UINT32
EFIAPI
GetDebugPrintErrorLevel (
  VOID
  )
{
  EFI_HOB_GUID_TYPE            *GuidHob;
  DEBUG_CONFIG_DATA_HOB        *DebugConfigData;
  UINT32                       DebugPrintErrorLevel;

  if (mDebugPrintErrorLevelInited == TRUE) {
    return mDebugPrintErrorLevel;
  }

  GuidHob = NULL;
  DebugConfigData = NULL;
  DebugPrintErrorLevel = 0;

  GuidHob = GetFirstGuidHob (&gDebugConfigHobGuid);
  if (GuidHob != NULL) {
    DebugConfigData = (DEBUG_CONFIG_DATA_HOB *) GET_GUID_HOB_DATA (GuidHob);
    if (DebugConfigData != NULL) {
      switch (DebugConfigData->SerialDebug) {
      case 0:
        DebugPrintErrorLevel = 0;
        break;
      case 1:
        DebugPrintErrorLevel = DEBUG_ERROR;
        break;
      case 2:
        DebugPrintErrorLevel = DEBUG_ERROR | DEBUG_WARN;
        break;
      case 4:
        DebugPrintErrorLevel = DEBUG_ERROR | DEBUG_WARN | DEBUG_INFO | DEBUG_EVENT | DEBUG_LOAD;
        break;
      case 5:
        DebugPrintErrorLevel = DEBUG_ERROR | DEBUG_WARN | DEBUG_INFO | DEBUG_VERBOSE | DEBUG_LOAD;
        break;
      default:
        DebugPrintErrorLevel = DEBUG_ERROR | DEBUG_WARN | DEBUG_INFO | DEBUG_LOAD;
        break;
      }
      mDebugPrintErrorLevel = DebugPrintErrorLevel;
      mDebugPrintErrorLevelInited = TRUE;
      return DebugPrintErrorLevel;
    }
  }

  return PcdGet32 (PcdDebugPrintErrorLevel);
}

/**
  Sets the global debug print error level mask for the entire platform.

  @param   ErrorLevel     Global debug print error level.

  @retval  TRUE           The debug print error level mask was sucessfully set.
  @retval  FALSE          The debug print error level mask could not be set.

**/
BOOLEAN
EFIAPI
SetDebugPrintErrorLevel (
  UINT32  ErrorLevel
  )
{
  return FALSE;
}

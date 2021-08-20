/** @file
  Heci Context Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include <HeciContextLib.h>


/**
  This function obtains the BAR0 of the selected HECI context.

  @param[in] HeciDev              HECI device to be accessed.

  @retval Bar0                    HECI Memory BAR.
                                  0 - invalid BAR value returned.
**/
UINT64
GetHeciContextBar0 (
  IN HECI_DEVICE HeciDev
  )
{
  HECI_CONTEXT_HOB     *HeciContextHob;
  HECI_CONTEXT_DEVICE  DeviceIndex;
  UINT64               HeciContextBar0;

  HeciContextBar0 = 0;
  HeciContextHob  = NULL;

  HeciContextHob  = (HECI_CONTEXT_HOB *) GetFirstGuidHob (&gHeciContextHobGuid);
  DeviceIndex     = (HECI_CONTEXT_DEVICE) HECI_DEV_TO_CONTEXT_MAP (HeciDev);

  if (DeviceIndex >= HeciMax) {
    return HeciContextBar0;
  }

  if (HeciContextHob != NULL) {
    if ((HeciContextHob->HeciDeviceContext[DeviceIndex].Bar0Address != 0) &&
        (HeciContextHob->HeciDeviceContext[DeviceIndex].ContextInitialized != FALSE) &&
        (HeciContextHob->HeciDeviceContext[DeviceIndex].IsHeciHidden != FALSE)) {
      HeciContextBar0 = HeciContextHob->HeciDeviceContext[DeviceIndex].Bar0Address;
      DEBUG ((DEBUG_INFO, "HECI%d Context BAR: 0x%08llX\n", DeviceIndex + 1, HeciContextBar0));
      return HeciContextBar0;
    }
  } else {
    DEBUG ((DEBUG_ERROR, "GetHeciContextBar0() - HECI Context Hob GUID not found!\n"));
  }
  return HeciContextBar0;
}

/**
  This function stores the BAR0 of the selected HECI context.

  @param[in] HeciDev              HECI device to be accessed.

  @retval Bar0                    HECI Memory BAR.
                                  0 - invalid BAR value returned.
**/
VOID
SetHeciContextBar0 (
  IN HECI_DEVICE HeciDev,
  IN UINT64      HeciContextBar0
  )
{
  HECI_CONTEXT_HOB     *HeciContextHob;
  HECI_CONTEXT_DEVICE  DeviceIndex;

  HeciContextHob  = NULL;

  HeciContextHob  = (HECI_CONTEXT_HOB *) GetFirstGuidHob (&gHeciContextHobGuid);
  DeviceIndex     = (HECI_CONTEXT_DEVICE) HECI_DEV_TO_CONTEXT_MAP (HeciDev);

  if (DeviceIndex >= HeciMax) {
    return;
  }
  //
  // Set HECI Context BAR
  //
  if (HeciContextHob != NULL) {
    if (HeciContextHob->HeciDeviceContext[DeviceIndex].Bar0Address != HeciContextBar0) {
      HeciContextHob->HeciDeviceContext[DeviceIndex].Bar0Address = HeciContextBar0;
      HeciContextHob->HeciDeviceContext[DeviceIndex].ContextInitialized = TRUE;
      DEBUG ((DEBUG_INFO, "HECI%d Context BAR set to 0x%08llX\n", DeviceIndex + 1, HeciContextBar0));
    }
  } else {
    DEBUG ((DEBUG_ERROR, "SetHeciContextBar0() - HECI Context Hob GUID not found!\n"));
  }
}

/**
  This function set or clear the selected HECI context initialized state.

  @param[in] HeciDev              HECI device to be accessed.
  @param[in] ContextInitialized   Set or clear HECI context initialized parameter.
**/
VOID
SetHeciContextInitialized (
  UINT8    HeciDevice,
  BOOLEAN  ContextInitialized
  )
{
  HECI_CONTEXT_HOB     *HeciContextHob;
  HECI_CONTEXT_DEVICE  DeviceIndex;

  HeciContextHob = NULL;
  HeciContextHob = (HECI_CONTEXT_HOB *) GetFirstGuidHob (&gHeciContextHobGuid);
  DeviceIndex = HeciDevice - 1;

  if (DeviceIndex >= HeciMax) {
    return;
  }

  if (HeciContextHob != NULL) {
    HeciContextHob->HeciDeviceContext[DeviceIndex].ContextInitialized = ContextInitialized;
    HeciContextHob->HeciDeviceContext[DeviceIndex].IsHeciHidden = FALSE;
  } else {
    DEBUG ((DEBUG_ERROR, "SetHeciContextInitialized() - HECI Context Hob GUID not found!\n"));
  }
}

/**
  This function set or clear the selected HECI context hidden state.

  @param[in] HeciDev              HECI device to be accessed.
  @param[in] IsHeciHidden         Set or clear HECI context IsHeciHidden parameter.
**/
VOID
SetHeciContextHidden (
  UINT8    HeciDevice,
  BOOLEAN  IsHeciHidden
  )
{
  HECI_CONTEXT_HOB     *HeciContextHob;
  HECI_CONTEXT_DEVICE  DeviceIndex;

  HeciContextHob = NULL;
  HeciContextHob = (HECI_CONTEXT_HOB *) GetFirstGuidHob (&gHeciContextHobGuid);
  DeviceIndex = HeciDevice - 1;

  if (DeviceIndex >= HeciMax) {
    return;
  }

  if (HeciContextHob != NULL) {
    if (HeciContextHob->HeciDeviceContext[DeviceIndex].Bar0Address != 0) {
      HeciContextHob->HeciDeviceContext[DeviceIndex].ContextInitialized = TRUE;
      HeciContextHob->HeciDeviceContext[DeviceIndex].IsHeciHidden = IsHeciHidden;
    } else {
      HeciContextHob->HeciDeviceContext[DeviceIndex].ContextInitialized = FALSE;
      HeciContextHob->HeciDeviceContext[DeviceIndex].IsHeciHidden = FALSE;
    }
  } else {
    DEBUG ((DEBUG_ERROR, "SetHeciContextHidden() - HECI Context Hob GUID not found!\n"));
  }
}

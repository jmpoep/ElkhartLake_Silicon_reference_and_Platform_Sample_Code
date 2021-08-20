/** @file
  CSE Variable Storage OS Proxy Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include <Register/MeRegs.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/CseVariableStorageOsProxyLib.h>

/**
  Requests the OS proxy driver state.

  @param[in]     OsProxyHeciBaseAddress The OS proxy HECI device base address.
  @param[out]    OsProxyState           The state of the OS proxy.

  @retval        EFI_SUCCESS            An error did not occur attempting to get proxy state.
  @retval        EFI_INVALID_PARAMETER  The OS proxy HECI device base address given is invalid.
**/
EFI_STATUS
EFIAPI
CseVariableStorageReadOsProxyState (
  IN  UINTN                   OsProxyHeciBaseAddress,
  OUT HECI_PROXY_STATE        *OsProxyState
  )
{
  UINTN                       HostGeneralStatus2;

  *OsProxyState = HeciProxyStateUnknown;
  if (OsProxyHeciBaseAddress == 0 || OsProxyHeciBaseAddress == (UINT32) -1) {
    return EFI_INVALID_PARAMETER;
  }
  HostGeneralStatus2 = OsProxyHeciBaseAddress + R_ME_H_GS_SHDW2;

  if ((MmioRead32 (HostGeneralStatus2) & B_ME_H_GS_SHDW2_PROXY_PRESENT) != 0) {
    *OsProxyState = HeciProxyStatePresent;
  } else {
    *OsProxyState = HeciProxyStateNotPresent;
  }

  return EFI_SUCCESS;
}

/**
  Requests the OS proxy driver state and blocks for CSE_VARIABLE_MAX_PROXY_WAIT_SECS seconds to wait for a response.

  @param[in]     OsProxyHeciBaseAddress The OS proxy HECI device base address.
  @param[out]    OsProxyState           The state of the OS proxy.

  @retval        EFI_SUCCESS            An error did not occur attempting to get proxy state.
  @retval        EFI_INVALID_PARAMETER  The OS proxy HECI device base address given is invalid.
**/
EFI_STATUS
EFIAPI
CseVariableStorageWaitForOsProxyState (
  IN  UINTN                   OsProxyHeciBaseAddress,
  OUT HECI_PROXY_STATE        *OsProxyState
  )
{
  UINTN                       HostGeneralStatus2;
  UINTN                       StallCount;
  CONST UINTN                 MaxStallCount = CSE_VARIABLE_MAX_PROXY_WAIT_SECS * 100;

  *OsProxyState = HeciProxyStateUnknown;
  if (OsProxyHeciBaseAddress == 0 || OsProxyHeciBaseAddress == (UINT32) -1) {
    return EFI_INVALID_PARAMETER;
  }
  HostGeneralStatus2 = OsProxyHeciBaseAddress + R_ME_H_GS_SHDW2;

  for (StallCount = 0; StallCount < MaxStallCount; StallCount++) {
    if ((MmioRead32 (HostGeneralStatus2) & B_ME_H_GS_SHDW2_PROXY_PRESENT) != 0) {
      *OsProxyState = HeciProxyStatePresent;
      return EFI_SUCCESS;
    }
    // Delay for ten milliseconds (OS proxy may take seconds to load)
    MicroSecondDelay (10000);
  }
  *OsProxyState = HeciProxyStateNotPresent;

  return EFI_SUCCESS;
}
/** @file
  The GUID definition for HeciContextLib

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

#ifndef _HECI_CONTEXT_LIB_H_
#define _HECI_CONTEXT_LIB_H_

#include <Uefi.h>
#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Register/MeRegs.h>

extern EFI_GUID gHeciContextHobGuid;

#pragma pack (push, 1)

typedef struct {
  UINT64  Bar0Address;
  BOOLEAN ContextInitialized;
  BOOLEAN IsHeciHidden;
} HECI_DEVICE_CONTEXT;

typedef struct {
  EFI_HOB_GUID_TYPE     EfiHobGuidType;
  HECI_DEVICE_CONTEXT   HeciDeviceContext[HeciMax];
} HECI_CONTEXT_HOB;

#pragma pack (pop)

/**
  This function obtains the BAR0 of the selected HECI context.

  @param[in] HeciDev              HECI device to be accessed.

  @retval Bar0                    HECI Memory BAR.
                                  0 - invalid BAR value returned.
**/
UINT64
GetHeciContextBar0 (
  IN HECI_DEVICE HeciDev
  );

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
  );

/**
  This function set or clear the selected HECI context initialized state.

  @param[in] HeciDev              HECI device to be accessed.
  @param[in] ContextInitialized   Set or clear HECI context initialized parameter.
**/
VOID
SetHeciContextInitialized (
  UINT8    HeciDevice,
  BOOLEAN  ContextInitialized
  );

/**
  This function set or clear the selected HECI context hidden state.

  @param[in] HeciDev              HECI device to be accessed.
  @param[in] IsHeciHidden         Set or clear HECI context IsHeciHidden parameter.
**/
VOID
SetHeciContextHidden (
  UINT8    HeciDevice,
  BOOLEAN  IsHeciHidden
  );

/**
  The function install HECI Context HOB.
**/
EFI_STATUS
InstallHeciContextHob (
  VOID
  );

#endif

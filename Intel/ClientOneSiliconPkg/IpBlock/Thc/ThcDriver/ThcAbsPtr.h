/** @file
  Touch Host Controller Absolute Pointer API

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

#include "ThcPrivate.h"

/**
  AbsPtr protocol's WaitForInput (called when a consumer of AbsPtr protocol waits for new data)

  @param[in]  Event              Pointer to event that triggered this callback
  @param[in]  Context            Device context
**/
VOID
EFIAPI
AbsPtrWaitForInput (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

/**
  Reset touch panel
  Function required by AbsPtr protocol.

  @param[in]  This
  @param[in]  ExtendedVerification

  @retval EFI_UNSUPPORTED
**/
EFI_STATUS
EFIAPI
AbsPtrReset (
  IN EFI_ABSOLUTE_POINTER_PROTOCOL *This,
  IN BOOLEAN                       ExtendedVerification
  );

/**
  If not-yet-consumed touch data is available, GetState() returns it and marks it unavailable
  If such data is not available, error will be returned. User should wait until WaitForInput event gets signalled

  @param[in]      This
  @param[in/out]  State

  @retval EFI_SUCCESS     Data consumed
  @retval EFI_NOT_READY   Data not available
**/
EFI_STATUS
EFIAPI
AbsPtrGetState (
  IN      EFI_ABSOLUTE_POINTER_PROTOCOL  *This,
  IN OUT  EFI_ABSOLUTE_POINTER_STATE     *State
  );

/**
  Installs AbsolutePointerProtocol
  Assigns TouchPanel Guid for Virtual Keyboard support

  @param[in]  ThcDev            Context of Thc device

  @retval EFI_SUCCESS           Absolute Pointer Protocol Installed
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
ThcInstallAbsPtr (
  IN THC_DEV                *ThcDev
  );

/**
  Closes and uninstalls Absolute Pointer Protocol

  @param[in]  ThcDev            Context of Thc device

**/
VOID
EFIAPI
ThcStopAbsPtr (
  IN THC_DEV                *ThcDev
  );


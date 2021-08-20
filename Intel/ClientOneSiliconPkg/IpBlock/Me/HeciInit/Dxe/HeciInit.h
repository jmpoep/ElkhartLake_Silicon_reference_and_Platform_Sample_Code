/** @file
  Definitions for HECI driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2020 Intel Corporation.

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
#ifndef _HECI_INIT_H
#define _HECI_INIT_H

#include <Protocol/HeciProtocol.h>
#include <Library/TimerLib.h>

///
/// HECI private data structure
///
typedef struct {
  UINTN                   Signature;
  EFI_HANDLE              Handle;
  UINT64                  HeciMBAR;
  UINT16                  DeviceInfo;
  UINT32                  RevisionInfo;
  HECI_PROTOCOL           HeciCtlr;
  volatile UINT32         *HpetTimer;
  UINT8                   MeFwImageType;
} HECI_INSTANCE;

/**
  Create the FWSTS info to the SMBIOS table using the SMBIOS protocol
  Invoke this routine to add the table entry when all the FWSTS data is finalized.

  @param[in]  Event               - A pointer to the Event that triggered the callback.
  @param[in]  Context             - A pointer to private data registered with the callback
                                    If the Context is TRUE, invoke DisableAllMeDevices () before exit
                                    because it is set TRUE when registered function failed to install HeciProtocol.

  @retval EFI_SUCCESS             - if the data is successfully reported.
  @retval EFI_OUT_OF_RESOURCES    - if not able to get resources.
  @retval EFI_UNSUPPORTED         - if required DataHub or SMBIOS protocol is not available.
**/
VOID
EFIAPI
AddFwStsSmbiosEntry (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *Context
  );

/*
  Installs HECI_FLOW_PROTOCOL and registers a callback to uninstall it on exit boot services

  @retval EFI_SUCCESS       Protocol was installed, error otherwise
*/
EFI_STATUS
EFIAPI
InitializeHeciFlow (
  VOID
  );

/**
  Register ME reset handler.

**/
VOID
RegisterMeReset (
  VOID
  );

#endif

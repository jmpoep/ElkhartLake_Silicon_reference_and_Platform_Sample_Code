/** @file
  HECI SMM driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

#include <Base.h>
#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/HeciRuntimeLib.h>
#include "HeciInitSmm.h"

//
// Global driver data
//
GLOBAL_REMOVE_IF_UNREFERENCED HECI_INSTANCE         *mHeciContext;

/**
  Returns if HECI timeouts are enabled.

  @retval FALSE                   HECI timeouts is disabled.
  @retval TRUE                    HECI timeouts is enabled.
**/
BOOLEAN
MeHeciTimeoutsEnabled (
  VOID
  )
{
  return TRUE;
}

/**
  Returns if HECI retry is enabled.

  @retval TRUE             HECI retry is enabled
  @retval FALSE            HECI retry is disabled
**/
BOOLEAN
MeHeciRetryEnabled (
  VOID
  )
{
  return TRUE;
}

/**
  Returns if HECI message check is enabled for Bios Boot Path.

  @retval TRUE             HECI message check is enabled
  @retval FALSE            HECI message check is disabled
**/
BOOLEAN
MeHeciMessageCheckEnabled (
  VOID
  )
{
  return FALSE;
}

/**
  HECI driver entry point used to initialize support for the HECI device.

  @param[in] ImageHandle          Standard entry point parameter.
  @param[in] SystemTable          Standard entry point parameter.

  @retval EFI_SUCCESS             Always return EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
InitializeHeciSmm (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS                      Status;

  DEBUG ((DEBUG_INFO, "ME-BIOS: HECI SMM Protocol Entry.\n"));

  mHeciContext = AllocateZeroPool (sizeof (HECI_INSTANCE));

  ///
  /// Initialize HECI protocol pointers
  ///
  if (mHeciContext == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    DEBUG ((DEBUG_ERROR, "ME-BIOS: HECI SMM Protocol Exit - Error by lack of memory for HECI_INSTANCE.\n"));
    goto Exit;
  }
  mHeciContext->HeciCtlr.ResetHeci    = ResetHeciInterface;
  mHeciContext->HeciCtlr.SendwAck     = HeciSendwAck;
  mHeciContext->HeciCtlr.ReadMsg      = HeciReceive;
  mHeciContext->HeciCtlr.SendMsg      = HeciSend;
  mHeciContext->HeciCtlr.InitHeci     = HeciInitialize;
  mHeciContext->HeciCtlr.ReInitHeci   = HeciReInitialize;
  mHeciContext->HeciCtlr.MeResetWait  = MeResetWait;
  mHeciContext->HeciCtlr.GetMeStatus  = HeciGetMeStatus;
  mHeciContext->HeciCtlr.GetMeMode    = HeciGetMeMode;

  ///
  /// Install the HECI interface
  ///
  Status = gSmst->SmmInstallProtocolInterface (
                    &mHeciContext->Handle,
                    &gHeciProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mHeciContext->HeciCtlr
                    );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: HECI SMM Protocol Exit - Error by install HECI protocol fail, Status: %r\n", Status));
    goto Exit;
  }

  DEBUG ((DEBUG_INFO, "ME-BIOS: HECI SMM Protocol Exit - Success.\n"));

Exit:
  return Status;
}

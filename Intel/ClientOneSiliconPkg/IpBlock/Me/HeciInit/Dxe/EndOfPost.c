/** @file
  ME End Of Post message and process implementation prior to boot OS

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PerformanceLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PostCodeLib.h>
#include <Library/HeciInitLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Protocol/HeciProtocol.h>
#include <MkhiMsgs.h>
#include <MeiBusMsg.h>
#include <Register/MeRegs.h>
#include <Register/HeciRegs.h>

/**
  Send End of Post Request Message through HECI.

  @param[out] RequestedActions    Action request returned by EOP ACK
                                    0x00 (HECI_EOP_STATUS_SUCCESS) - Continue to boot
                                    0x01 (HECI_EOP_PERFORM_GLOBAL_RESET) - Global reset

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
**/
EFI_STATUS
HeciSendEndOfPostMessage (
  OUT UINT32                      *RequestedActions
  )
{
  EFI_STATUS         Status;
  UINT32             Length;
  UINT32             RecvLength;
  END_OF_POST_BUFFER EndOfPost;

  EndOfPost.Request.MkhiHeader.Data           = 0;
  EndOfPost.Request.MkhiHeader.Fields.Command = GEN_END_OF_POST_CMD;
  EndOfPost.Request.MkhiHeader.Fields.GroupId = MKHI_GEN_GROUP_ID;

  Length                                      = sizeof (END_OF_POST);
  RecvLength                                  = sizeof (END_OF_POST_ACK);

  PERF_START_EX (NULL, "EventRec", NULL, AsmReadTsc (), 0x3030);
  Status = HeciSendwAck (
             HECI1_DEVICE,
             (UINT32 *) &EndOfPost,
             Length,
             &RecvLength,
             BIOS_FIXED_HOST_ADDR,
             HECI_MKHI_MESSAGE_ADDR
             );
  PERF_END_EX (NULL, "EventRec", NULL, AsmReadTsc (), 0x3031);

  if (!EFI_ERROR (Status)) {
    *RequestedActions = EndOfPost.Response.Data.RequestedActions;
    if (EndOfPost.Response.Data.RequestedActions == HeciEopPerformGlobalReset) {
      DEBUG ((DEBUG_INFO, "HeciSendEndOfPostMessage(): Global Reset requested by FW EOP ACK\n"));
    }
  }

  return Status;
}

/**
  This message is sent by the BIOS if EOP-ACK not received to force ME to disable
  HECI interfaces.

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             HECI interfaces disabled by ME
**/
EFI_STATUS
HeciDisableHeciBusMsg (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINT32                          Length;
  UINT32                          RespLength;
  HECI_BUS_DISABLE_CMD_ACK        MsgHeciBusDisable;

  ZeroMem (&MsgHeciBusDisable, sizeof (HECI_BUS_DISABLE_CMD_ACK));

  MsgHeciBusDisable.Command.Data = HECI_BUS_DISABLE_OPCODE;
  Length     = sizeof (HECI_BUS_DISABLE_CMD);
  RespLength = sizeof (HECI_BUS_DISABLE_CMD_ACK);

  Status = HeciSendwAck (
             HECI1_DEVICE,
             (UINT32 *) &MsgHeciBusDisable,
             Length,
             &RespLength,
             BIOS_FIXED_HOST_ADDR,
             HECI_HBM_MESSAGE_ADDR
             );

  if (!EFI_ERROR (Status) &&
      ((MsgHeciBusDisable.Command.Fields.Command != HECI_BUS_DISABLE_OPCODE) ||
       (MsgHeciBusDisable.Command.Fields.IsResponse == 0) ||
       (MsgHeciBusDisable.Status != 0))) {
    Status = EFI_ABORTED;
  }

  return Status;
}

/**
  Send ME the BIOS end of Post message.

  @param[out] RequestedActions    Action request returned by EOP ACK
                                    0x00 (HECI_EOP_STATUS_SUCCESS) - Continue to boot
                                    0x01 (HECI_EOP_PERFORM_GLOBAL_RESET) - Global reset

  @retval EFI_SUCCESS             Platform reached End of Post successfully
  @retval EFI_DEVICE_ERROR        An error has occured by EoP message
**/
EFI_STATUS
MeEndOfPostEvent (
  OUT UINT32                          *RequestedActions
  )
{
  EFI_STATUS                          Status;
  UINT8                               EopSendRetries;

  DEBUG ((DEBUG_INFO, "ME-BIOS: EOP Entry.\n"));
  PostCode (0xE05);

  for (EopSendRetries = 0; EopSendRetries < MAX_EOP_SEND_RETRIES; EopSendRetries++) {
    Status = HeciSendEndOfPostMessage (RequestedActions);
    if (!EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "ME-BIOS: EOP Exit - Success.\n"));
      PostCode (0xE25);
      return EFI_SUCCESS;
    }
  }

  REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_EOP_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (Status));
  DEBUG ((DEBUG_ERROR, "ME-BIOS: EOP Exit - Error by sending EOP message. Forcing HECI interface closure\n"));
  HeciDisableHeciBusMsg ();
  PostCode (0xE85);

  return EFI_DEVICE_ERROR;
}

/**
  Perform Cf9Gr Lock Config
      - PCH BIOS Spec Rev 0.9 Section 18.4  Additional Power Management Programming
        Set "Power Management Initialization Register (PMIR) Field 1", D31:F0:ACh[31] = 1b
        for production machine according to "RS - PCH Intel Management Engine
        (Intel(r) ME) BIOS Writer's Guide".
**/
VOID
LockConfig (
  VOID
  )
{
  UINT32                          MeMode;
  HECI_FWS_REGISTER               MeFirmwareStatus;

  DEBUG ((DEBUG_INFO, "LockConfig () - Start\n"));
  HeciGetMeMode (&MeMode);

  MeFirmwareStatus.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS));

  ///
  /// PCH BIOS Spec Rev 0.9 Section 18.4  Additional Power Management Programming
  /// Step 2
  ///   Set "Power Management Initialization Register (PMIR) Field 1", D31:F0:ACh[31] = 1b
  ///   for production machine according to "RS - PCH Intel Management Engine
  ///  (Intel(r) ME) BIOS Writer's Guide".
  ///
  /// PCH ME BWG section 4.5.1
  /// The IntelR FPT tool /GRST option uses CF9GR bit to trigger global reset.
  /// Based on above reason, the BIOS should not lock down CF9GR bit during Manufacturing and
  /// Re-manufacturing environment.
  ///
  if (((MeMode == ME_MODE_NORMAL) || (MeMode == ME_MODE_TEMP_DISABLED)) && !(MeFirmwareStatus.r.ManufacturingMode)) {
    ///
    /// PCH ME BWG section 4.4.1
    /// BIOS must also ensure that CF9GR is cleared and locked (via bit31 of the same register) before
    /// handing control to the OS in order to prevent the host from issuing global resets and reseting
    /// Intel Management Engine.
    ///
    PmcDisableCf9GlobalResetWithLock ();
  } else {
    PmcDisableCf9GlobalReset ();
  }
}


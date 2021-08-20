/** @file
  This is a library for Amt Heci Message functionality.

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
#include <PiDxe.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/HeciProtocol.h>
#include <Library/HobLib.h>
#include <Library/BaseLib.h>
#include <Library/TimerLib.h>
#include <Library/DxeMeLib.h>
#include <AsfMsgs.h>
#include <CoreBiosMsg.h>
#include <AmtConfig.h>

//
// ME Client - AMT/ASF
//

//
// Management Control Command
//

/**
  Start ASF Watch Dog Timer.
  The WDT will be started only if AMT WatchDog policy is enabled and corresponding timer value is not zero.

  @param[in] WatchDogType         Which kind of WatchDog, ASF OS WatchDog Timer setting or ASF BIOS WatchDog Timer setting

**/
VOID
AsfStartWatchDog (
  IN  UINT8                       WatchDogType
  )
{
  EFI_STATUS        Status;
  UINT32            Length;
  ASF_START_WDT     AsfStartWdt;
  HECI_PROTOCOL     *Heci;
  UINT32            MeStatus;
  UINT32            MeMode;
  UINT16            WaitTimer;
  EFI_HOB_GUID_TYPE *GuidHob;
  AMT_PEI_CONFIG    *AmtPeiConfig;

  GuidHob = GetFirstGuidHob (&gAmtPolicyHobGuid);
  if (GuidHob == NULL) {
    DEBUG ((DEBUG_INFO, "Get AMT WatchDog policy fail, don't start ASF WDT\n"));
    return;
  }
  AmtPeiConfig = (AMT_PEI_CONFIG *) GET_GUID_HOB_DATA (GuidHob);

  if (WatchDogType == ASF_START_BIOS_WDT) {
    WaitTimer = AmtPeiConfig->WatchDogTimerBios;
  } else {
    WaitTimer = AmtPeiConfig->WatchDogTimerOs;
  }
  if (WaitTimer == 0) {
    DEBUG ((DEBUG_ERROR, "Timeout value is 0, unable to start ASF WDT\n"));
    return;
  }

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Heci protocol does not exist, unable to start ME WDT\n"));
    return;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    DEBUG ((DEBUG_ERROR, "MeMode is %x, unable to start ASF WDT\n", MeMode));
    return;
  }

  ///
  /// Send WDT message when ME is ready.  Do not care about if ME FW INIT is completed.
  ///
  Status = Heci->GetMeStatus (&MeStatus);
  if (EFI_ERROR (Status) || (ME_STATUS_ME_STATE_ONLY (MeStatus) != ME_READY)) {
    DEBUG ((DEBUG_ERROR, "MeStatus is %x, unable to start ASF WDT\n", MeStatus));
    return;
  }

  DEBUG ((DEBUG_INFO, "AsfStartWatchDog () - Starting ASF WDT with timeout %d seconds \n", WaitTimer));

  AsfStartWdt.AsfHeader.Fields.Command           = ASF_MESSAGE_COMMAND_MANAGEMENT_CONTROL;
  AsfStartWdt.AsfHeader.Fields.ByteCount         = ASF_MESSAGE_BYTE_COUNT_MAP (ASF_START_WDT);
  AsfStartWdt.AsfHeader.Fields.SubCommand        = ASF_MESSAGE_SUBCOMMAND_START_WATCH_DOG_TIMER;
  AsfStartWdt.AsfHeader.Fields.VersionNumber     = ASF_VERSION;
  AsfStartWdt.EventSensorType                    = ASF_EVENT_SENSOR_TYPE_WATCHDOG2;
  AsfStartWdt.EventType                          = ASF_EVENT_TYPE_SENSOR_SPECIFIC;
  AsfStartWdt.EventOffset                        = ASF_EVENT_OFFSET_TIMER_EXPIRED;
  AsfStartWdt.EventSeverity                      = ASF_EVENT_SEVERITY_CODE_CRITICAL;
  AsfStartWdt.SensorDevice                       = ASF_SENSOR_DEVICE;
  AsfStartWdt.SensorNumber                       = ASF_SENSOR_NUMBER;
  AsfStartWdt.Entity                             = ASF_ENTITY_UNSPECIFIED;
  AsfStartWdt.EntityInstance                     = ASF_ENTITY_INSTANCE_UNSPECIFIED;
  AsfStartWdt.EventData[0]                       = ASF_WD_EVENT_DATA1;
  if (WatchDogType == ASF_START_BIOS_WDT) {
    AsfStartWdt.EventSourceType                  = ASF_EVENT_SOURCE_TYPE_PLATFORM_FIRMWARE;
    AsfStartWdt.EventData[1]                     = ASF_WD_EVENT_DATA2_BIOS_TIMEOUT;
  } else {
    AsfStartWdt.EventSourceType                  = ASF_EVENT_SOURCE_TYPE_OS;
    AsfStartWdt.EventData[1]                     = ASF_WD_EVENT_DATA2_OS_TIMEOUT;
  }

  AsfStartWdt.TimeoutLow                         = (UINT8) WaitTimer;
  AsfStartWdt.TimeoutHigh                        = (UINT8) (WaitTimer >> 8);
  Length                                         = sizeof (ASF_START_WDT);

  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32 *) &AsfStartWdt,
                   Length,
                   BIOS_ASF_HOST_ADDR,
                   HECI_ASF_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to start ASF WDT, Status = %r\n", Status));
  }

}

/**
  Stop ASF Watch Dog Timer HECI message.

**/
VOID
AsfStopWatchDog (
  VOID
  )
{
  EFI_STATUS           Status;
  UINT32               Length;
  ASF_STOP_WDT         AsfStopWdt;
  UINT32               MeStatus;
  UINT32               MeMode;
  HECI_PROTOCOL        *Heci;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Heci protocol does not exist, unable to stop ASF WDT\n"));
    return;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    DEBUG ((DEBUG_ERROR, "MeMode is %x, unable to stop ASF WDT\n", MeMode));
    return;
  }

  ///
  /// Send WDT message when ME is ready. Do not care about if ME FW INIT is completed.
  ///
  Status = Heci->GetMeStatus (&MeStatus);
  if (EFI_ERROR (Status) || (ME_STATUS_ME_STATE_ONLY (MeStatus) != ME_READY)) {
    DEBUG ((DEBUG_ERROR, "MeStatus is %x, unable to stop ASF WDT\n", MeStatus));
    return;
  }

  DEBUG ((DEBUG_INFO, "AsfStopWatchDog () - Stopping ASF WDT...\n"));
  AsfStopWdt.AsfHeader.Fields.Command        = ASF_MESSAGE_COMMAND_MANAGEMENT_CONTROL;
  AsfStopWdt.AsfHeader.Fields.ByteCount      = ASF_MESSAGE_BYTE_COUNT_MAP (ASF_STOP_WDT);
  AsfStopWdt.AsfHeader.Fields.SubCommand     = ASF_MESSAGE_SUBCOMMAND_STOP_WATCH_DOG_TIMER;
  AsfStopWdt.AsfHeader.Fields.VersionNumber  = ASF_VERSION;
  Length                                     = sizeof (ASF_STOP_WDT);

  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32 *) &AsfStopWdt,
                   Length,
                   BIOS_ASF_HOST_ADDR,
                   HECI_ASF_MESSAGE_ADDR
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Unable to stop ASF WDT, Status = %r\n", Status));
  }
}

/**
  Use ASF_GetRsePassword to get disk password from the FW

  @param[in,out]   Password            Preallocated buffer to save c string
                                       password to. It has to be at least 32
                                       characters wide.

  @retval EFI_SUCCESS                  Buffer Password contains returned password
  @retval EFI_NOT_FOUND                Either there is no password in AMT memory
                                       or Heci communication failed
  @retval EFI_DEVICE_ERROR             Failed to initialize HECI
  @retval EFI_TIMEOUT                  HECI is not ready for communication
  @retval EFI_UNSUPPORTED              Current ME mode doesn't support send this function
**/
EFI_STATUS
GetRsePassword (
  IN OUT CHAR16                       *Password
  )
{
  EFI_STATUS                           Status;
  HECI_PROTOCOL                        *Heci;
  UINT32                               Length;
  GET_RSE_PASSWORD                     GetRsePassword;
  GET_RSE_PASSWORD_RESPONSE            Response;
  UINT32                               MeMode;
  CHAR8                                PasswordCString[RSE_PASSWORD_MAX_LENGTH + 1];

  DEBUG ((DEBUG_INFO, "SecureErase::AsfGetRsePassword \n" ));

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &Heci);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  GetRsePassword.AsfHeader.Fields.Command       = ASF_MESSAGE_COMMAND_ASF_CONFIGURATION;
  GetRsePassword.AsfHeader.Fields.ByteCount     = ASF_MESSAGE_BYTE_COUNT_MAP (GET_RSE_PASSWORD);
  GetRsePassword.AsfHeader.Fields.SubCommand    = ASF_MESSAGE_SUBCOMMAND_GET_RSE_PASSWORD;
  GetRsePassword.AsfHeader.Fields.VersionNumber = ASF_VERSION;

  Length = sizeof (GET_RSE_PASSWORD);
  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32*)&GetRsePassword,
                   Length,
                   BIOS_ASF_HOST_ADDR,
                   HECI_ASF_MESSAGE_ADDR
                   );
  DEBUG ((DEBUG_INFO, "Get RSE Password status : %r\n", Status));
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Length = sizeof (GET_RSE_PASSWORD_RESPONSE);
  Status = Heci->ReadMsg (
                   HECI1_DEVICE,
                   BLOCKING,
                   (UINT32 *) &Response,
                   &Length
                   );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ASF Get RSE Password failed!(ReadMsg), Status = %r\n", Status));
    return EFI_NOT_FOUND;
  }

  if (Response.AsfHeader.Fields.Command       != ASF_MESSAGE_COMMAND_ASF_CONFIGURATION ||
      Response.AsfHeader.Fields.ByteCount      > ASF_MESSAGE_BYTE_COUNT_MAP (GET_RSE_PASSWORD_RESPONSE) ||
      Response.AsfHeader.Fields.SubCommand    != ASF_MESSAGE_SUBCOMMAND_GET_RSE_PASSWORD ||
      Response.AsfHeader.Fields.VersionNumber != ASF_VERSION) {
    ZeroMem (&Response, sizeof (GET_RSE_PASSWORD_RESPONSE));
    return EFI_NOT_FOUND;
  }

  DEBUG ((DEBUG_INFO, "Received %d long password.\n", Response.PasswordLength));

  if (Response.PasswordLength > RSE_PASSWORD_MAX_LENGTH || Response.PasswordLength == 0) {
    ZeroMem (&Response, sizeof (GET_RSE_PASSWORD_RESPONSE));
    return EFI_NOT_FOUND;
  }

  //
  // Turn AMT_ANSI_STRING into a standard NULL terminated C String and convert
  // to a unicode NULL terminated string
  //
  ZeroMem (PasswordCString, sizeof (CHAR8)*(RSE_PASSWORD_MAX_LENGTH + 1));
  CopyMem (PasswordCString, Response.Password, Response.PasswordLength);
  AsciiStrToUnicodeStrS (PasswordCString, Password, RSE_PASSWORD_MAX_LENGTH + 1);
  //
  // Erase temporary passwords from memory
  //
  ZeroMem (PasswordCString, Response.PasswordLength);
  ZeroMem (&Response, sizeof (GET_RSE_PASSWORD_RESPONSE));

  return EFI_SUCCESS;
}


//
// Messaging Command
//

/**
  Send secure erase operation status using PET

  @param[in]    OperationResult   Status of secure erase operation

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
SendRsePetAlert (
  IN EFI_STATUS                        OperationResult
  )
{
  EFI_STATUS                           Status;
  PET_ALERT                            RsePetAlert;
  HECI_PROTOCOL                        *Heci;
  UINT32                               Length;
  UINT32                               MeMode;

  DEBUG ((DEBUG_INFO, "SecureErase::SendRsePetAlert (%r)\n", OperationResult));

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &Heci);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  RsePetAlert.AsfHeader.Fields.Command         = ASF_MESSAGE_COMMAND_MESSAGE;
  RsePetAlert.AsfHeader.Fields.ByteCount       = ASF_MESSAGE_BYTE_COUNT_MAP (PET_ALERT);
  RsePetAlert.AsfHeader.Fields.SubCommand      = ASF_MESSAGE_SUBCOMMAND_NORETRANSMIT;
  RsePetAlert.AsfHeader.Fields.VersionNumber   = ASF_VERSION;
  RsePetAlert.EventSensorType                  = ASF_EVENT_SENSOR_TYPE_SYS_FW_ERR_PROG;
  RsePetAlert.EventType                        = ASF_EVENT_TYPE_SENSOR_SPECIFIC;
  RsePetAlert.EventSourceType                  = ASF_EVENT_SOURCE_TYPE_ASF10;
  RsePetAlert.SensorDevice                     = ASF_SENSOR_DEVICE;
  RsePetAlert.Sensornumber                     = ASF_SENSOR_NUMBER;
  RsePetAlert.Entity                           = ASF_ENTITY_BIOS;
  RsePetAlert.EntityInstance                   = 0xFF;
  RsePetAlert.EventData1                       = ASF_RSE_EVENT_DATA0_EVENT_DATA_SET_BY_OEM;
  RsePetAlert.EventData2                       = ASF_RSE_EVENT_DATA1_REMOTE_SECURE_ERASE;
  RsePetAlert.EventData4                       = 0x00;
  RsePetAlert.EventData5                       = 0x00;

  if (EFI_ERROR (OperationResult)) {
    RsePetAlert.EventOffset                    = ASF_EVENT_OFFSET_REMOTE_SECURE_ERASE_FW_ERROR;
    RsePetAlert.EventSeverity                  = ASF_EVENT_SEVERITY_CODE_CRITICAL;
    if (OperationResult == EFI_UNSUPPORTED) {
      RsePetAlert.EventData3                   = ASF_RSE_EVENT_DATA2_UNSUPPORTED;
    } else if (OperationResult == EFI_ACCESS_DENIED) {
      RsePetAlert.EventData3                   = ASF_RSE_EVENT_DATA2_DRIVE_AUTH_FAILURE;
    } else if (OperationResult == EFI_DEVICE_ERROR) {
      RsePetAlert.EventData3                   = ASF_RSE_EVENT_DATA2_GENERAL_FAILURE;
    } else {
      RsePetAlert.EventData3                   = ASF_RSE_EVENT_DATA2_GENERAL_FAILURE;
    }
  } else {
    RsePetAlert.EventOffset                    = ASF_EVENT_OFFSET_REMOTE_SECURE_ERASE_FW_PROGRESS;
    RsePetAlert.EventSeverity                  = ASF_EVENT_SEVERITY_CODE_NONCRITICAL;
    RsePetAlert.EventData3                     = ASF_RSE_EVENT_DATA2_SECURE_ERASE_SUCCESS;
  }

  Length = sizeof (PET_ALERT);
  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32*)&RsePetAlert,
                   Length,
                   BIOS_ASF_HOST_ADDR,
                   HECI_ASF_MESSAGE_ADDR
                   );

  return Status;

}

//
// KVM Command
//

/**
  This is used to send KVM request message to Intel ME. When
  Bootoptions indicate that a KVM session is requested then BIOS
  will send this message before any graphical display output to
  ensure that FW is ready for KVM session.

  @param[in] QueryType            0 - Query Request
                                  1 - Cancel Request
  @param[out] ResponseCode        1h - Continue, KVM session established.
                                  2h - Continue, KVM session cancelled.

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
AmtQueryKvm (
  IN  UINT32                      QueryType,
  OUT UINT32                      *ResponseCode
  )
{
  EFI_STATUS                      Status;
  HECI_PROTOCOL                   *Heci;
  AMT_QUERY_KVM_BUFFER            QueryKvm;
  UINT32                          RecvLength;
  UINT16                          TimeOut;
  UINT32                          MeMode;

  TimeOut = 0;
  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  QueryKvm.Request.AsfHeader.Data                 = 0;
  QueryKvm.Request.AsfHeader.Fields.Command       = ASF_MESSAGE_COMMAND_KVM;
  QueryKvm.Request.AsfHeader.Fields.ByteCount     = ASF_MESSAGE_BYTE_COUNT_MAP (AMT_QUERY_KVM);
  QueryKvm.Request.AsfHeader.Fields.SubCommand    = ASF_MESSAGE_SUBCOMMAND_KVM_QUERY;
  QueryKvm.Request.AsfHeader.Fields.VersionNumber = ASF_VERSION;
  QueryKvm.Request.QueryType                      = QueryType;
  RecvLength                                      = sizeof (AMT_QUERY_KVM_RESPONSE);

  if (QueryType == QueryRequest) {
    Status = Heci->SendMsg (
                     HECI1_DEVICE,
                     (UINT32 *) &QueryKvm,
                     sizeof (AMT_QUERY_KVM),
                     BIOS_ASF_HOST_ADDR,
                     HECI_ASF_MESSAGE_ADDR
                     );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Send Query KVM failed %r\n", Status));
      return Status;
    }

    //
    // BIOS starts counting up to 8 minutes to wait for Query Request response.
    //
    TimeOut = 0;
    do {
      RecvLength = sizeof (AMT_QUERY_KVM_RESPONSE);
      Status = Heci->ReadMsg (
                       HECI1_DEVICE,
                       NON_BLOCKING,
                       (UINT32 *) &QueryKvm,
                       &RecvLength
                       );

      MicroSecondDelay (KVM_STALL_1_SECOND);
      TimeOut++;
      if (TimeOut > KVM_MAX_WAIT_TIME) {
        DEBUG ((DEBUG_ERROR, "Read Query KVM timeout\n"));
        return EFI_TIMEOUT;
      }
    } while (EFI_ERROR (Status));
  } else {
    //
    // BIOS follows common requirement (wait 5 seconds with max 3 retries) for Cancel Request.
    //
    Status = Heci->SendwAck (
                     HECI1_DEVICE,
                     (UINT32 *) &QueryKvm,
                     sizeof (AMT_QUERY_KVM),
                     &RecvLength,
                     BIOS_ASF_HOST_ADDR,
                     HECI_ASF_MESSAGE_ADDR
                     );
  }

  *ResponseCode = QueryKvm.Response.ResponseCode;

  return Status;
}


/**
  This message is sent by the BIOS on the boot where the host wants to get the firmware provisioning state.
  The firmware will respond to AMT BIOS SYNC INFO message even after the End of Post.

  @param[out] RuleData            Bit [1:0] Reserved
                                  Bit [2]   Corporate provisioning is available.
                                  Bit [4:3] Provisioning State
                                    00 - Pre - Provisioning
                                    01 - In - Provisioning
                                    02 - Post - Provisioning
                                  Bit [31:5] Reserved

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
HeciAmtBiosSyncInfo (
  OUT UINT32               *RuleData
  )
{
  return HeciFwCapsGetRuleData (AMT_BIOS_SYNC_INFO_RULE_ID, RuleData);
}


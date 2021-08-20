/** @file
  This is a library for Asf Heci Message functionality.

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
#include <PiDxe.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/HeciProtocol.h>
#include <Library/HobLib.h>
#include <Library/BaseLib.h>
#include <Library/TimerLib.h>
#include <AsfMsgs.h>
#include <CoreBiosMsg.h>

//
// ME Client - ASF
//

//
// ASF Configuration Command
//

/**
  Clears boot options by sending a proper ASF command through HECI

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
ClearBootOptions (
  VOID
  )
{
  EFI_STATUS                           Status;
  HECI_PROTOCOL                        *Heci;
  UINT32                               Length;
  UINT32                               MeMode;
  CLEAR_BOOT_OPTIONS                   ClearBootOptions;

  DEBUG ((DEBUG_INFO, "Clearing boot options\n"));

  ClearBootOptions.AsfHeader.Fields.Command       = ASF_MESSAGE_COMMAND_ASF_CONFIGURATION;
  ClearBootOptions.AsfHeader.Fields.ByteCount     = ASF_MESSAGE_BYTE_COUNT_MAP (CLEAR_BOOT_OPTIONS);
  ClearBootOptions.AsfHeader.Fields.SubCommand    = ASF_MESSAGE_SUBCOMMAND_CLEAR_BOOT_OPT;
  ClearBootOptions.AsfHeader.Fields.VersionNumber = ASF_VERSION;
  Length                                          = sizeof (ClearBootOptions);

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &Heci);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32*)&ClearBootOptions,
                   Length,
                   BIOS_ASF_HOST_ADDR,
                   HECI_ASF_MESSAGE_ADDR
                   );

  DEBUG ((DEBUG_INFO, "Clear boot options status : %r\n", Status));

  return Status;
}

/**
  Get boot options by sending a proper ASF command through HECI

  @param[out] AsfBootOptions      Boot Options returned from HECI

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
  @retval EFI_INVALID_PARAMETER   BootOptionsResponse is a NULL pointer
**/
EFI_STATUS
GetBootOptions (
  OUT ASF_BOOT_OPTIONS                 *AsfBootOptions
  )
{
  EFI_STATUS                           Status;
  HECI_PROTOCOL                        *Heci;
  UINT32                               RecvLength;
  UINT32                               MeMode;
  GET_BOOT_OPTIONS_BUFFER              GetBootOptions;

  DEBUG ((DEBUG_INFO, "Get boot options\n"));

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &Heci);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  if (AsfBootOptions == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  GetBootOptions.Request.AsfHeader.Data                 = 0;
  GetBootOptions.Request.AsfHeader.Fields.Command       = ASF_MESSAGE_COMMAND_ASF_CONFIGURATION;
  GetBootOptions.Request.AsfHeader.Fields.ByteCount     = ASF_MESSAGE_BYTE_COUNT_MAP (GET_BOOT_OPTIONS);
  GetBootOptions.Request.AsfHeader.Fields.SubCommand    = ASF_MESSAGE_SUBCOMMAND_RETURN_BOOT_OPT;
  GetBootOptions.Request.AsfHeader.Fields.VersionNumber = ASF_VERSION;
  RecvLength                                            = sizeof (GET_BOOT_OPTIONS_RESPONSE);

  Status = Heci->SendwAck (
                   HECI1_DEVICE,
                   (UINT32 *)&GetBootOptions,
                   sizeof (GET_BOOT_OPTIONS),
                   &RecvLength,
                   BIOS_ASF_HOST_ADDR,
                   HECI_ASF_MESSAGE_ADDR
                   );
  CopyMem (AsfBootOptions, &GetBootOptions.Response.AsfBootOptions, sizeof (ASF_BOOT_OPTIONS));

  return Status;
}


/**
  Send ASF_ReportBiosStatus message

  @param[in] BiosStatus           Current Bios status

  @retval EFI_UNSUPPORTED         Current ME mode doesn't support this function
  @retval EFI_SUCCESS             Command succeeded
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_TIMEOUT             HECI does not return the buffer before timeout
  @retval EFI_BUFFER_TOO_SMALL    Message Buffer is too small for the Acknowledge
**/
EFI_STATUS
ReportBiosStatus (
  IN EFI_STATUS                           BiosStatus
  )
{
  EFI_STATUS                           Status;
  HECI_PROTOCOL                        *Heci;
  REPORT_BIOS_STATUS                   ReportBiosStatus;
  UINT32                               Length;
  UINT32                               MeMode;

  DEBUG ((DEBUG_INFO, "ReportBiosStatus (%r)\n", BiosStatus));

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &Heci);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    return EFI_UNSUPPORTED;
  }

  ReportBiosStatus.AsfHeader.Fields.Command       = ASF_MESSAGE_COMMAND_ASF_CONFIGURATION;
  ReportBiosStatus.AsfHeader.Fields.ByteCount     = ASF_MESSAGE_BYTE_COUNT_MAP (REPORT_BIOS_STATUS);
  ReportBiosStatus.AsfHeader.Fields.SubCommand    = ASF_MESSAGE_SUBCOMMAND_REPORT_BIOS_STATUS;
  ReportBiosStatus.AsfHeader.Fields.VersionNumber = ASF_VERSION;
  if (BiosStatus == EFI_SUCCESS) {
    ReportBiosStatus.BiosStatus                   = ASF_RBS_BIOS_STATUS_SUCCESS;
    ReportBiosStatus.StatusCause                  = ASF_RBS_STATUS_CAUSE_SUCCESS_INPROGRESS;
  } else {
    ReportBiosStatus.BiosStatus                   = ASF_RBS_BIOS_STATUS_FAILED;
    if (BiosStatus == EFI_UNSUPPORTED) {
      ReportBiosStatus.StatusCause                = ASF_RBS_STATUS_CAUSE_UNSUPPORTED;
    } else if (BiosStatus == EFI_ACCESS_DENIED) {
      ReportBiosStatus.StatusCause                = ASF_RBS_STATUS_CAUSE_AUTHENTICATION_FAILURE;
    } else {
      ReportBiosStatus.StatusCause                = ASF_RBS_STATUS_CAUSE_GENERAL_FAILURE;
    }
  }

  Length = sizeof (REPORT_BIOS_STATUS);
  Status = Heci->SendMsg (
                   HECI1_DEVICE,
                   (UINT32*)&ReportBiosStatus,
                   Length,
                   BIOS_ASF_HOST_ADDR,
                   HECI_ASF_MESSAGE_ADDR
                   );
  return Status;
}
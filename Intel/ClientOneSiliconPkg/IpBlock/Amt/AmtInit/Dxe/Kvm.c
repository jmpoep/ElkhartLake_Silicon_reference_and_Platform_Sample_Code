/** @file
  KVM Initialization function.

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

#include "AmtInitDxe.h"

/**
  Initialize KVM by sending HECI message to ME

  @param[in] Event                The event registered.
  @param[in] Context              Event context. Not used in this event handler.
**/
VOID
EFIAPI
QueryKvm (
  IN EFI_EVENT                    Event,
  IN VOID                         *Context
  )
{
  EFI_STATUS                      Status;
  UINT32                          ResponseCode;
  AMT_POLICY_PROTOCOL             *AmtPolicy;
  AMT_DXE_CONFIG                  *AmtDxeConfig;
  AMT_REPORT_ERROR                ReportError;

  gBS->CloseEvent (Event);

  ReportError  = NULL;
  AmtDxeConfig = NULL;
  Status = gBS->LocateProtocol (&gDxeAmtPolicyGuid, NULL, (VOID **) &AmtPolicy);
  if (!EFI_ERROR (Status)) {
    Status = GetConfigBlock ((VOID *) AmtPolicy, &gAmtDxeConfigGuid, (VOID *) &AmtDxeConfig);
  }
  if (!EFI_ERROR (Status) && (AmtDxeConfig->AmtReportError != NULL)) {
    ReportError = AmtDxeConfig->AmtReportError;
  }

  if (ReportError != NULL) {
    ReportError (MSG_KVM_WAIT);
  }

  Status = AmtQueryKvm (QueryRequest, &ResponseCode);
  if (EFI_ERROR (Status)) {
    if (ReportError != NULL) {
      ReportError (MSG_KVM_TIMES_UP);
    }
    AmtQueryKvm (CancelRequest, &ResponseCode);
  } else if (ResponseCode == KvmSessionCancelled) {
    if (ReportError != NULL) {
      ReportError (MSG_KVM_REJECTED);
    }
  }

  return;
}


/**
  Register KVM Notification on ConsoltOut Device installed.

  @retval EFI_SUCCESS             The function executed without error.
  @retval EFI_INVALID_PARAMETER   One or more parameters are invalid.
  @retval EFI_OUT_OF_RESOURCES    The event could not be allocated.
**/
EFI_STATUS
KvmInit (
  VOID
  )
{
  EFI_STATUS        Status;
  VOID              *AfterConsolOutNotifyReg;
  EFI_EVENT         AfterConsolOutInstalledEvent;

  DEBUG ((DEBUG_INFO, "KvmInit start\n"));
  ///
  /// Set up Event for KVM for when Output Display Console is installed
  ///
  Status = gBS->CreateEvent (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  QueryKvm,
                  NULL,
                  &AfterConsolOutInstalledEvent
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->RegisterProtocolNotify (
                  &gEfiConsoleOutDeviceGuid,
                  AfterConsolOutInstalledEvent,
                  &AfterConsolOutNotifyReg
                  );
  ASSERT_EFI_ERROR (Status);
  return Status;
}


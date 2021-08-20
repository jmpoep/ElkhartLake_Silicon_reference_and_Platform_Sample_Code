/** @file
  Header file for AMT functionality

@copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2019 Intel Corporation.

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
#ifndef _DXE_AMT_HECI_LIB_H_
#define _DXE_AMT_HECI_LIB_H_

/**
  Stop ASF Watch Dog Timer HECI message.

**/
VOID
AsfStopWatchDog (
  VOID
  );

/**
  Start ASF Watch Dog Timer

  @param[in] WatchDogType         Which kind of WatchDog, ASF OS WatchDog Timer setting or ASF BIOS WatchDog Timer setting

**/
VOID
AsfStartWatchDog (
  IN  UINT8                       WatchDogType
  );

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
  );

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
  );

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
  );

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
  );

#endif

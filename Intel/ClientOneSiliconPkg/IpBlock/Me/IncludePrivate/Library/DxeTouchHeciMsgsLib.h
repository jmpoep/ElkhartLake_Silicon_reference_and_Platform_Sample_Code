/** @file
  Touch HECI Message definitions

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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

#ifndef _DXE_TOUCH_HECI_MSGS_LIB_H
#define _DXE_TOUCH_HECI_MSGS_LIB_H

#include <Register/MeRegs.h>
#include "TouchHeciMsgs.h"

#define HECI_ITOUCH_MESSAGE_ADDR  0x0000000C

/**
  Resets and initialized HECI3 device to prepare iTouch communication

  @retval EFI_SUCCESS
**/
EFI_STATUS
TouchResetHeci3 (
  VOID
  );

/**
  Sends notification that touchpanel should start to initialize

  @retval EFI_SUCCESS             Notification message was sent
  @retval EFI_DEVICE_ERROR        Failed to initialize HECI
  @retval EFI_TIMEOUT             HECI is not ready for communication
  @retval EFI_UNSUPPORTED         Current ME mode doesn't support send this message through this HECI
**/
EFI_STATUS
TouchSensorNotifyDevReady (
  VOID
  );

/**
  Retrieves touchpanel info, such as size of communication buffers

  @param[out] DataBufferSize      Size of data buffer.
  @param[out] FeedbackBufferSize  size of feedback buffer.

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
TouchSensorGetDeviceInfo (
  OUT UINT32* DataBufferSize,
  OUT UINT32* FeedbackBufferSize
  );

/**
  Sets touchpanel mode to single touch. Other modes exist but are not supported in BIOS.

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
TouchSensorSetSingleTouchMode (
  VOID
  );


/**
  Tells CSME about addresses and sizes of memory buffers used for exchanging data

  @param[in] DataBuffer      address of data buffer.
  @param[in] FeedbackBuffer  address of feedback buffer.
  @param[in] Hid2MeBuffer    address of driver-to-panel data buffer.
  @param[in] FeedBackSize    Size of the FeedBack Buffer.

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
TouchSensorSetMemWindow (
  IN UINT8   *DataBuffer,
  IN UINT8   *FeedbackBuffer,
  IN UINT8   *Hid2MeBuffer,
  IN UINT32  FeedBackSize
  );

/**
  Clear the memory created in TouchSensorSetmemWindow

  @retval EFI_SUCCESS                     The function completes successfully
**/
EFI_STATUS
TouchSensorClearMemWindow (
  VOID
  );

/**
  Tells CSME that BIOS is ready to accept new data packet from touch panel
  This function only sends a message and doesn't wait for response

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
TouchSensorSendHidReadyForData (
  VOID
  );

/**
  Sends feedback from BIOS to touch panel.

  @retval EFI_SUCCESS       There was a response from CSME, which means touch data packet is available
  @retval EFI_NO_RESPONSE   Data packet is not available
**/
EFI_STATUS
TouchSensorFeedbackReady (
  IN UINT8 FeedbackIndex
  );

/**
  Receives HECI responses from CSME
  This function is designed to be run in a fast loop. It uses NON_BLOCKING mechanism,
  which means in case there's no new message to receive it will return immediately
  instead of busy-waiting for a specified timeout period.
  Unlike any HECI exchange going over HECI 1 interface, this function doesn't expect
  single, certain message ID. iTouch can spontaneously send messages of different kinds, in random order,
  so BIOS must be able to accommodate them all

  @param[out] ReceiveBuffer    buffer where received data will be placed.

  @retval EFI_SUCCESS          Data was received
  @retval any other status     No data was received
**/
EFI_STATUS
TouchSensorHeciReceive (
  OUT TOUCH_SENSOR_MSG_M2H *ReceiveBuffer
  );

/**
  Checks for notification that touchpanel is ready

  @retval EFI_SUCCESS       Touch Panel ready
  @retval EFI_NO_RESPONSE   Touch is still initializing
  @retval EFI_DEVICE_ERROR  Command code is different then TOUCH_SENSOR_NOTIFY_DEV_READY_RSP
**/
EFI_STATUS
TouchSensorCheckDevReady (
  VOID
  );

#endif //_DXE_TOUCH_HECI_MSGS_LIB_H

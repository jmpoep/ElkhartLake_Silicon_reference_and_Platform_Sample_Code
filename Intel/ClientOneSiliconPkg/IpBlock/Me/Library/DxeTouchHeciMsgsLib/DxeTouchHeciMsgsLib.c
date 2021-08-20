/** @file
  Implements Integrated Touchpanel HECI Interface Library.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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

#include <Uefi.h>
#include <PiDxe.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/DxeMeLib.h>
#include "Library/DxeTouchHeciMsgsLib.h"
#include "TouchHeciMsgs.h"

//
// Global variables
//
TOUCH_SENSOR_MSG_H2M  mHost2MeMsg;
TOUCH_SENSOR_MSG_M2H  mMe2HostMsg;

//
// Architecture of iTouch allows that responses to HECI messages
// may arrive out-of-order. Specifically, ReadyForData response
// may arrive at any time. In order to allow BIOS to receive the response
// it wants and at the same time not forget the ReadyForData, the
// ReadyForData will be cached.
//

BOOLEAN gDataReady = FALSE;

#define DELAY_AFTER_NOTIFY_SEND 10 // milliseconds

/**
  Resets and initialized HECI3 device to prepare iTouch communication

  @retval EFI_SUCCESS
**/
EFI_STATUS
TouchResetHeci3 (
  VOID
  )
{
  EFI_STATUS         Status;
  HECI_PROTOCOL      *HeciProtocol = NULL;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &HeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = HeciProtocol->ResetHeci (HECI3_FUNCTION_NUMBER);

  return Status;
}


/**
  Checks for notification that touchpanel is ready

  @retval EFI_SUCCESS       Touch Panel ready
  @retval EFI_NO_RESPONSE   Touch is still initializing
  @retval EFI_DEVICE_ERROR  Command code is different then TOUCH_SENSOR_NOTIFY_DEV_READY_RSP
**/
EFI_STATUS
TouchSensorCheckDevReady (
  VOID
  )
{
  EFI_STATUS        Status;
  UINT32            RespLength;
  HECI_PROTOCOL     *HeciProtocol = NULL;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &HeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (&mMe2HostMsg, sizeof (mMe2HostMsg));

  gBS->Stall (EFI_TIMER_PERIOD_MILLISECONDS(DELAY_AFTER_NOTIFY_SEND)); // 10 msec

  Status = HeciProtocol->ReadMsg (
                           HECI3_FUNCTION_NUMBER,
                           NON_BLOCKING,
                           (UINT32 *) &mMe2HostMsg,
                           &RespLength
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorCheckDevReadyResponse: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  if (mMe2HostMsg.CommandCode != TOUCH_SENSOR_NOTIFY_DEV_READY_RSP) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorCheckDevReadyResponse: Message failed! Unexpected Response from ME.\n"));
    DEBUG ((DEBUG_ERROR, "(iTouch) Expected: %x, Received: %x\n", TOUCH_SENSOR_NOTIFY_DEV_READY_RSP, mMe2HostMsg.CommandCode));
    Status = EFI_DEVICE_ERROR;
  }

  return Status;
}


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
  )
{
  EFI_STATUS        Status;
  UINT32            Length;
  HECI_PROTOCOL     *HeciProtocol = NULL;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &HeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (&mHost2MeMsg, sizeof (mHost2MeMsg)); //to prevent sending garbage in fields we don't use

  mHost2MeMsg.CommandCode   = TOUCH_SENSOR_NOTIFY_DEV_READY_CMD;
  Length                    = sizeof (mHost2MeMsg.CommandCode);

  Status = HeciProtocol->SendMsg (
                           HECI3_FUNCTION_NUMBER,
                           (UINT32 *) &mHost2MeMsg,
                           Length,
                           BIOS_FIXED_HOST_ADDR,
                           HECI_ITOUCH_MESSAGE_ADDR
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorNotifyDevReadyCmd: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  return Status;
}

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
  )
{
  EFI_STATUS         Status;
  UINT32             Length;
  UINT32             RespLength;
  HECI_PROTOCOL      *HeciProtocol = NULL;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &HeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (&mHost2MeMsg, sizeof (mHost2MeMsg)); //to prevent sending garbage in fields we don't use
  ZeroMem (&mMe2HostMsg, sizeof (mMe2HostMsg));
  mHost2MeMsg.CommandCode   = TOUCH_SENSOR_NOTIFY_DEV_READY_CMD;
  Length                    = sizeof (mHost2MeMsg.CommandCode);
  RespLength                = sizeof (TOUCH_SENSOR_NOTIFY_DEV_READY_RSP_DATA) + sizeof(mMe2HostMsg.CommandCode);
  HeciProtocol->ReadMsg (
                   HECI3_FUNCTION_NUMBER,
                   NON_BLOCKING,
                   (UINT32 *) &mMe2HostMsg,
                   &RespLength
                   );

  ZeroMem (&mHost2MeMsg, sizeof(mHost2MeMsg));
  ZeroMem (&mMe2HostMsg, sizeof(mMe2HostMsg));
  mHost2MeMsg.CommandCode   = TOUCH_SENSOR_GET_DEVICE_INFO_CMD;
  Length                    = sizeof(mHost2MeMsg.CommandCode);
  RespLength                = sizeof(TOUCH_SENSOR_GET_DEVICE_INFO_RSP_DATA) + sizeof(mHost2MeMsg.CommandCode);

  Status = HeciProtocol->SendMsg (
                           HECI3_FUNCTION_NUMBER,
                           (UINT32 *) &mHost2MeMsg,
                           Length,
                           BIOS_FIXED_HOST_ADDR,
                           HECI_ITOUCH_MESSAGE_ADDR
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "(iTouch) TouchSensorGetDeviceInfoCmd: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  Status = HeciProtocol->ReadMsg (
                           HECI3_FUNCTION_NUMBER,
                           BLOCKING,
                           (UINT32 *) &mMe2HostMsg,
                           &RespLength
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "(iTouch) TouchSensorGetDeviceInfoResponse: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  if (mMe2HostMsg.CommandCode != TOUCH_SENSOR_GET_DEVICE_INFO_RSP) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorGetDeviceInfoResponse: Message failed! Unexpected Response from ME.\n"));
    DEBUG ((DEBUG_ERROR, "(iTouch) Expected: %x, Received: %x\n", TOUCH_SENSOR_GET_DEVICE_INFO_RSP, mMe2HostMsg.CommandCode));
    return EFI_DEVICE_ERROR;
  }


  if (mMe2HostMsg.M2HData.DeviceInfoRspData.Status != TOUCH_STATUS_SUCCESS && mMe2HostMsg.M2HData.DeviceInfoRspData.Status != TOUCH_STATUS_COMPAT_CHECK_FAIL) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorGetDeviceInfoResponse, TOUCH_STATUS = 0x%x\n", mMe2HostMsg.M2HData.SetMemWindowRspData.Status));
    return EFI_DEVICE_ERROR;
  }

  *DataBufferSize = mMe2HostMsg.M2HData.DeviceInfoRspData.FrameSize;
  *FeedbackBufferSize = mMe2HostMsg.M2HData.DeviceInfoRspData.FeedbackSize;
  DEBUG ((DEBUG_INFO, "(iTouch) TouchSensorGetDeviceInfoResponse: data %d + fb %d\n", *DataBufferSize, *FeedbackBufferSize));
  return EFI_SUCCESS;
}

/**
  Sets touchpanel mode to single touch. Other modes exist but are not supported in BIOS.

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
TouchSensorSetSingleTouchMode (
  VOID
  )
{
  EFI_STATUS         Status;
  UINT32             Length;
  UINT32             RespLength;
  HECI_PROTOCOL      *HeciProtocol = NULL;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &HeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (&mHost2MeMsg, sizeof (mHost2MeMsg)); //to prevent sending garbage
  ZeroMem (&mMe2HostMsg, sizeof (mMe2HostMsg));

  mHost2MeMsg.CommandCode                       = TOUCH_SENSOR_SET_MODE_CMD;
  mHost2MeMsg.H2MData.SetModeCmdData.SensorMode = TOUCH_SENSOR_MODE_HID;
  Length                                        = sizeof (mHost2MeMsg.CommandCode) + sizeof (TOUCH_SENSOR_SET_MODE_CMD_DATA);
  RespLength                                    = sizeof (mHost2MeMsg.CommandCode) + sizeof (TOUCH_SENSOR_SET_MODE_RSP_DATA);

  //
  // SendTouch Sensor Set Mode Command
  //
  Status = HeciProtocol->SendMsg (
                           HECI3_FUNCTION_NUMBER,
                           (UINT32 *) &mHost2MeMsg,
                           Length,
                           BIOS_FIXED_HOST_ADDR,
                           HECI_ITOUCH_MESSAGE_ADDR
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "(iTouch) TouchSensorSetModeCmd: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  //
  // Read Touch Sensor Set Mode Response
  //
  Status = HeciProtocol->ReadMsg (
                           HECI3_FUNCTION_NUMBER,
                           BLOCKING,
                           (UINT32 *) &mMe2HostMsg,
                           &RespLength
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "(iTouch) TouchSensorSetModeResponse: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  if (mMe2HostMsg.CommandCode != TOUCH_SENSOR_SET_MODE_RSP) {
    DEBUG ((DEBUG_WARN, "(iTouch) TouchSensorSetModeResponse: Message failed! Unexpected Response from ME.\n"));
    DEBUG ((DEBUG_WARN, "(iTouch) Expected: %x, Received: %x\n", TOUCH_SENSOR_SET_MODE_RSP, mMe2HostMsg.CommandCode));
  }

  return EFI_SUCCESS;
}


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
  )
{
  EFI_STATUS         Status;
  UINT32             Length;
  UINT32             RespLength;
  HECI_PROTOCOL      *HeciProtocol = NULL;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &HeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (&mHost2MeMsg, sizeof (mHost2MeMsg)); //to prevent sending garbage in fields we don't use
  ZeroMem (&mMe2HostMsg, sizeof (mMe2HostMsg));

  Length                    = sizeof (mHost2MeMsg.CommandCode) + sizeof (TOUCH_SENSOR_SET_MEM_WINDOW_CMD_DATA);
  RespLength                = sizeof (mHost2MeMsg.CommandCode) + sizeof (TOUCH_SENSOR_SET_MEM_WINDOW_RSP_DATA);


  //
  // there is no use for TailOffset yet it must be non-zero, so pointer to a local variable is provided
  //
  mHost2MeMsg.CommandCode = TOUCH_SENSOR_SET_MEM_WINDOW_CMD;
  mHost2MeMsg.H2MData.SetMemWindowCmdData.TouchDataBufferAddrLower[0] = (UINTN) (DataBuffer) & 0xFFFFFFFF;
  mHost2MeMsg.H2MData.SetMemWindowCmdData.TouchDataBufferAddrUpper[0] = (UINTN) (DataBuffer) >> 32;
  mHost2MeMsg.H2MData.SetMemWindowCmdData.FeedbackBufferAddrLower[0]  = (UINTN) (FeedbackBuffer) & 0xFFFFFFFF;
  mHost2MeMsg.H2MData.SetMemWindowCmdData.FeedbackBufferAddrUpper[0]  = (UINTN) (FeedbackBuffer) >> 32;
  mHost2MeMsg.H2MData.SetMemWindowCmdData.Hid2MeBufferAddrLower       = (UINTN) (Hid2MeBuffer) & 0xFFFFFFFF;
  mHost2MeMsg.H2MData.SetMemWindowCmdData.Hid2MeBufferAddrUpper       = (UINTN) (Hid2MeBuffer) >> 32;
  mHost2MeMsg.H2MData.SetMemWindowCmdData.Hid2MeBufferSize            = MIN (TOUCH_HID_2_ME_BUFFER_SIZE_MAX, FeedBackSize);

  Status = HeciProtocol->SendMsg (
                           HECI3_FUNCTION_NUMBER,
                           (UINT32 *) &mHost2MeMsg,
                           Length,
                           BIOS_FIXED_HOST_ADDR,
                           HECI_ITOUCH_MESSAGE_ADDR
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorSetMemWindowCmd: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  Status = HeciProtocol->ReadMsg (
                           HECI3_FUNCTION_NUMBER,
                           BLOCKING,
                           (UINT32 *) &mMe2HostMsg,
                           &RespLength
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorSetMemWindowResponse: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  if (mMe2HostMsg.CommandCode != TOUCH_SENSOR_SET_MEM_WINDOW_RSP) {
    DEBUG ((DEBUG_WARN, "(iTouch) TouchSensorSetMemWindowRsp: Message failed! Unexpected Response from ME.\n"));
    DEBUG ((DEBUG_WARN, "(iTouch) Expected: %x, Received: %x\n", TOUCH_SENSOR_SET_MEM_WINDOW_RSP, mMe2HostMsg.CommandCode));
  }
  if (mMe2HostMsg.M2HData.SetMemWindowRspData.Status != TOUCH_STATUS_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorSetMemWindowRsp, TOUCH_STATUS = 0x%x\n", mMe2HostMsg.M2HData.SetMemWindowRspData.Status));
    return EFI_DEVICE_ERROR;
  }
  return Status;
}

/**
  Clear the memory created in TouchSensorSetmemWindow

  @retval EFI_SUCCESS                     The function completes successfully
**/
EFI_STATUS
TouchSensorClearMemWindow (
  VOID
  )
{
  EFI_STATUS         Status;
  UINT32             Length;
  UINT32             RespLength;
  HECI_PROTOCOL      *HeciProtocol = NULL;

  DEBUG ((DEBUG_INFO, "(iTouch) TouchSensorClearMemWindow\n"));

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &HeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (&mHost2MeMsg, sizeof (mHost2MeMsg)); // clear memory of potentially corrupt data

  mHost2MeMsg.CommandCode   = TOUCH_SENSOR_CLEAR_MEM_WINDOW_CMD;
  Length                    = sizeof (mHost2MeMsg.CommandCode);

  Status = HeciProtocol->SendMsg (
                           HECI3_FUNCTION_NUMBER,
                           (UINT32 *) &mHost2MeMsg,
                           Length,
                           BIOS_FIXED_HOST_ADDR,
                           HECI_ITOUCH_MESSAGE_ADDR
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorClearMemWindowCmd: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  RespLength = sizeof (mHost2MeMsg.CommandCode) +
    MAX (sizeof (TOUCH_SENSOR_HID_READY_FOR_DATA_RSP_DATA), sizeof (TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP_DATA));

  //
  // If BIOS sent HidReadyForData and/or FeedbackReady messages before clearing mem window, then
  // CSME may respond the other messages before replying to ClearMemWindowResp.
  // That's why here we read & discard all responses until the correct response is found
  do {
    ZeroMem (&mMe2HostMsg, sizeof (mMe2HostMsg));
    RespLength = sizeof (mHost2MeMsg.CommandCode) +
      MAX (sizeof (TOUCH_SENSOR_HID_READY_FOR_DATA_RSP_DATA), sizeof (TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP_DATA));

    Status = HeciProtocol->ReadMsg (HECI3_FUNCTION_NUMBER,BLOCKING,(UINT32 *) &mMe2HostMsg,&RespLength);

  } while (!EFI_ERROR (Status) && (mMe2HostMsg.CommandCode != TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP));

  RespLength = sizeof (mHost2MeMsg.CommandCode) + sizeof (TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP_DATA);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorClearMemWindowRspData: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  if (mMe2HostMsg.CommandCode != TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP) {
    DEBUG ((DEBUG_WARN, "(iTouch) TouchSensorClearMemWindowRsp: Message failed! Unexpected Response from ME.\n"));
    DEBUG ((DEBUG_WARN, "(iTouch) Expected: %x, Received: %x\n", TOUCH_SENSOR_CLEAR_MEM_WINDOW_RSP, mMe2HostMsg.CommandCode));
  }
  if (mMe2HostMsg.M2HData.ClearMemWindowRspData.Status != TOUCH_STATUS_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "(iTouch) ClearMemWindowRspData, TOUCH_STATUS = 0x%x\n", mMe2HostMsg.M2HData.ClearMemWindowRspData.Status));
    return EFI_DEVICE_ERROR;
  }
  return Status;
}

/**
  Tells CSME that BIOS is ready to accept new data packet from touch panel
  Notice that this only sends the message and does not try to read the response.
  This operation mode is specific to HECI3 interface and its iTouch messages.
  Unlike anything that goes over HECI1, in iTouch the CSME is master, can send any message at any time
  so BIOS cannot expect to receive responses in any specific order.

  @retval EFI_SUCCESS       Data was sent successfully
**/
EFI_STATUS
TouchSensorSendHidReadyForData (
  VOID
  )
{
  EFI_STATUS         Status;
  UINT32             Length;
  HECI_PROTOCOL      *HeciProtocol = NULL;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &HeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  mHost2MeMsg.CommandCode = TOUCH_SENSOR_HID_READY_FOR_DATA_CMD;
  Length                  = sizeof (mHost2MeMsg.CommandCode);

  Status = HeciProtocol->SendMsg (
                           HECI3_FUNCTION_NUMBER,
                           (UINT32 *) &mHost2MeMsg,
                           Length,
                           BIOS_FIXED_HOST_ADDR,
                           HECI_ITOUCH_MESSAGE_ADDR
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "(iTouch) TouchSensorHidReadyForDataCmd: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Sends feedback from BIOS to touch panel.
  Notice that this only sends the message and does not try to read the response.
  This operation mode is specific to HECI3 interface and its iTouch messages.
  Unlike anything that goes over HECI1, in iTouch the CSME is master, can send any message at any time
  so BIOS cannot expect to receive responses in any specific order.

  @retval EFI_SUCCESS       Data was sent successfully
**/
EFI_STATUS
TouchSensorFeedbackReady (
  IN UINT8 FeedbackIndex
  )
{
  EFI_STATUS         Status;
  UINT32             Length;
  HECI_PROTOCOL      *HeciProtocol = NULL;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &HeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  ZeroMem (&mHost2MeMsg, sizeof (mHost2MeMsg)); //to prevent sending garbage in fields we don't use
  ZeroMem (&mMe2HostMsg, sizeof (mMe2HostMsg));

  mHost2MeMsg.CommandCode = TOUCH_SENSOR_FEEDBACK_READY_CMD;
  mHost2MeMsg.H2MData.FeedbackReadyCmdData.FeedbackIndex = FeedbackIndex;
  Length                  = sizeof (TOUCH_SENSOR_FEEDBACK_READY_CMD_DATA) + sizeof (mHost2MeMsg.CommandCode);

  Status = HeciProtocol->SendMsg (
                           HECI3_FUNCTION_NUMBER,
                           (UINT32 *) &mHost2MeMsg,
                           Length,
                           BIOS_FIXED_HOST_ADDR,
                           HECI_ITOUCH_MESSAGE_ADDR
                           );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(iTouch) TouchSensorFeedbackReadyCmd: Message failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  return Status;
}

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
  )
{
  UINT32        RespLength;
  EFI_STATUS    Status;
  HECI_PROTOCOL *HeciProtocol = NULL;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &HeciProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  RespLength = sizeof (TOUCH_SENSOR_MSG_M2H);
  return HeciProtocol->ReadMsg (HECI3_FUNCTION_NUMBER,NON_BLOCKING,(UINT32 *) ReceiveBuffer,&RespLength);
}


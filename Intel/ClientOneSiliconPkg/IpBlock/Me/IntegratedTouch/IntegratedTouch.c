/** @file
  Touch Panel Driver
  This is an UEFI driver module. In its entry point it installs DriverBinding protocol, and that causes UEFI infrastructure to
  try to Connect() it to various handles. Handles means devices such as PCI. This particular driver will only report that it supports
  HECI3 device (see Supported() function). Inside Start() function, it will install AbsolutePointer protocol on that HECI3 device.
  Having AbsolutePointer protocol is enough for VirtualKeyboard driver to use this device.
  Start() also initializes internal data structures for the device.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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
#include "IntegratedTouchPrivate.h"
#include "TouchSensorRegs.h"
#include "TouchHeciMsgs.h"
#include "Library/DxeTouchHeciMsgsLib.h"
#include <Library/DxeMeLib.h>
#include <Guid/EventGroup.h>
#include <Guid/EventLegacyBios.h>
#include <MeBiosPayloadHob.h>
#include <Library/HobLib.h>
#include <Library/TimerLib.h>
#include <Protocol/IntegratedTouch.h>

///
/// Driver Support EFI Version Protocol instance
///
GLOBAL_REMOVE_IF_UNREFERENCED
EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL gIntegratedTouchDriverSupportedEfiVersion = {
  sizeof (EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL),
  0x0002001E
};

///
/// Driver Binding Protocol instance
///
GLOBAL_REMOVE_IF_UNREFERENCED EFI_DRIVER_BINDING_PROTOCOL gIntegratedTouchDriverBinding = {
  IntegratedTouchDriverBindingSupported,
  IntegratedTouchDriverBindingStart,
  IntegratedTouchDriverBindingStop,
  TOUCH_DRIVER_VERSION,
  NULL,
  NULL
};

#define TOUCH_DATA_BUFFER_ID             0
#define TOUCH_EVENT_REPORT_ID            0x40
#define MAX_WAIT_FOR_ITOUCH_READY_COUNT  24   // wait for iTouch to report back 12 seconds in total
#define WAIT_FOR_ITOUCH_READY_DELAY      500  // milliseconds

#ifndef MDEPKG_NDEBUG
#define GET_SET_FEATURE_TIMEOUT 5000    // milliseconds
#define ITOUCH_POLLING_PERIOD   1000000 // 10^6 * 100ns = 100 ms
#else
#define GET_SET_FEATURE_TIMEOUT 1000    // milliseconds
#define ITOUCH_POLLING_PERIOD   1000    // 10^3 * 100ns = 100us
#endif

typedef enum {
  GET_FEATURE = 0,
  SET_FEATURE = 1
} HID_REQUEST_TYPE;

/**
  Sends feedback to CSME.
  Fills Hid2Me buffer with data provided by input parameters, then sends HECI message
  telling CSME to consume it. Contents of buffer may either be a new data packet
  for CSME or a notification that data in another buffer, previously sent from CSME to BIOS,
  had been consumed and that other buffer can be reused

  @param  iTouchDev          Pointer to driver context
  @param  BufferId           ID of buffer that this message is about
  @param  FeedbackCmdType    command type
  @param  FeedbackDataType   data type
  @param  PayloadSize        payload size
  @param  *Buffer            pointer to source of payload

  @retval EFI_SUCCESS
**/
EFI_STATUS
SendFeedback (
  IN INTEGRATED_TOUCH_DEV      *iTouchDev,
  IN UINT8                     BufferId,
  IN TOUCH_FEEDBACK_CMD_TYPES  FeedbackCmdType,
  IN TOUCH_FEEDBACK_DATA_TYPES FeedbackDataType,
  IN UINT32                    PayloadSize,
  IN UINT8                     *Buffer
  )
{
  ZeroMem (iTouchDev->Hid2MeBuffer, sizeof (TOUCH_FEEDBACK_HDR));
  ((TOUCH_FEEDBACK_HDR*) (iTouchDev->Hid2MeBuffer))->BufferId = BufferId;
  ((TOUCH_FEEDBACK_HDR*) (iTouchDev->Hid2MeBuffer))->FeedbackCmdType = FeedbackCmdType;
  ((TOUCH_FEEDBACK_HDR*) (iTouchDev->Hid2MeBuffer))->PayloadSizeBytes = PayloadSize;
  ((TOUCH_FEEDBACK_HDR*) (iTouchDev->Hid2MeBuffer))->ProtocolVer = 0;
  ((TOUCH_FEEDBACK_HDR*) (iTouchDev->Hid2MeBuffer))->FeedbackDataType = FeedbackDataType;

  if (Buffer != NULL && PayloadSize != 0) {
    CopyMem (iTouchDev->Hid2MeBuffer + sizeof (TOUCH_FEEDBACK_HDR), Buffer, PayloadSize);
  }
  return TouchSensorFeedbackReady (BufferId);
}

/**
  Tells CSME that data in Me2HidBuffer was consumed and CSME can send new packet

  @param  iTouchDev    Pointer to driver context
**/
VOID
Me2HidBufferConsumed (
  INTEGRATED_TOUCH_DEV *iTouchDev
  )
{
  SendFeedback (iTouchDev, TOUCH_DATA_BUFFER_ID, TOUCH_FEEDBACK_CMD_TYPE_NONE, TOUCH_FEEDBACK_DATA_TYPE_FEEDBACK, 0, NULL);
  TouchSensorSendHidReadyForData ();
  iTouchDev->Me2HidBufferFull = FALSE;
}

/**
  Checks if incoming data is a touch event or something else

  @param  iTouchDev    Pointer to driver context

  @retval TRUE         This is touch event
  @retval FALSE        This is not a touch event, could be response to Set/GetFeature
**/
BOOLEAN
IsTouchEvent (
  IN INTEGRATED_TOUCH_DEV *iTouchDev
  )
{
  SINGLE_FINGER_REPORT* Report;

  Report = (SINGLE_FINGER_REPORT*) (iTouchDev->Me2HidBuffer);

  if (Report->Header.DataType == HID_REPORT && Report->ReportId == TOUCH_EVENT_REPORT_ID) {
    return TRUE;
  }
  return FALSE;
}

/**
  Polls HECI3 for incoming iTouch related data

  @param  Event              Pointer to event that triggered this callback
  @param  Context            Device context
**/
VOID
EFIAPI
HeciPolling (
  IN EFI_EVENT Event,
  IN VOID *Context
  )
{
  INTEGRATED_TOUCH_DEV *iTouchDev;
  TOUCH_SENSOR_MSG_M2H  Me2HostMsg;

  iTouchDev = (INTEGRATED_TOUCH_DEV *) Context;

  if (EFI_ERROR (TouchSensorHeciReceive (&Me2HostMsg))) {
    return;
  }

  switch (Me2HostMsg.CommandCode) {
    case TOUCH_SENSOR_FEEDBACK_READY_RSP:
      if (Me2HostMsg.M2HData.FeedbackReadyRspData.FeedbackIndex == TOUCH_HID_2_ME_BUFFER_ID) {
        //
        // CSME consumed Hid2Me buffer so BIOS can use it again.
        //
        iTouchDev->Hid2MeBufferFull = FALSE;
      } else if (Me2HostMsg.M2HData.FeedbackReadyRspData.FeedbackIndex == TOUCH_DATA_BUFFER_ID) {
        //
        // This is irrelevant response for a message where BIOS told CSME that it consumed touch data.
        //
      }
      break;
    case TOUCH_SENSOR_HID_READY_FOR_DATA_RSP:
      //
      // new data arrived from CSME
      //
      iTouchDev->Me2HidBufferFull = TRUE;
      //
      // if the new data is Set/GetFeature response and there's an application that waits for response, it will be consumed by HidGetSetFeature
      // however if the data is Set/GetFeature response but no one is awaiting it, then it must be discarded, otherwise it would block the flow
      //
      if (iTouchDev->HidProtocolActive == FALSE && !IsTouchEvent (iTouchDev)) {
        Me2HidBufferConsumed (iTouchDev);
      } else if (IsTouchEvent (iTouchDev)) {
        IntegratedTouchParseInput (&iTouchDev->TouchData, (SINGLE_FINGER_REPORT*) (iTouchDev->Me2HidBuffer));
        Me2HidBufferConsumed (iTouchDev);
        iTouchDev->TouchDataAvailable = TRUE;
        gBS->SignalEvent (iTouchDev->AbsPtrProtocol.WaitForInput);
      }
      break;
    case TOUCH_SENSOR_RESET_RSP:
    default:
      break;
  }
}

/**
  Common implementation for GetFeature and SetFeature functions as described in Human Interface Device spec

  @param  This       Pointer to instance of protocol
  @param  Length     Size of buffer
  @param  Buffer     On input, contains data to be sent to iTouch
  @param  TimeOutVal Parameter added to support Capsule Update. If provided value is 0 default is set GET_SET_FEATURE_TIMEOUT (5000)

  @retval EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
HidGetSetFeature (
  IN ITOUCH_HID_PROTOCOL  *This,
  IN UINT32               Length,
  IN UINT8                *Buffer,
  IN HID_REQUEST_TYPE     RequestType,
  IN UINTN                TimeOutVal
  )
{
  INTEGRATED_TOUCH_DEV       *iTouchDev;
  TOUCH_FEEDBACK_DATA_TYPES  DataType;
  UINTN                      Timeout;
  UINT32                     MaxBufferLength;

  iTouchDev  = INTEGRATED_TOUCH_CONTEXT_FROM_HID_PROTOCOL (This);

  if (iTouchDev->Hid2MeBufferFull == TRUE) {
    //
    // can't start new operation if previous one is underway
    //
    return EFI_ALREADY_STARTED;
  }

  MaxBufferLength = MIN (TOUCH_HID_2_ME_BUFFER_SIZE_MAX, iTouchDev->FeedbackBufferSize) - sizeof (TOUCH_FEEDBACK_HDR);

  if (Length > MaxBufferLength) {
    DEBUG ((DEBUG_INFO, "HidGetSetFeature() Buffer Length invalid  Max:%d current:%d [bytes]\n", MaxBufferLength, Length));
    return EFI_BAD_BUFFER_SIZE;
  }

  iTouchDev->HidProtocolActive = TRUE;

  if (RequestType == GET_FEATURE) {
    DataType = TOUCH_FEEDBACK_DATA_TYPE_GET_FEATURES;
  } else {
    DataType = TOUCH_FEEDBACK_DATA_TYPE_SET_FEATURES;
  }
  iTouchDev->Hid2MeBufferFull = TRUE;
  SendFeedback (iTouchDev, TOUCH_HID_2_ME_BUFFER_ID, TOUCH_FEEDBACK_CMD_TYPE_NONE, DataType, Length, Buffer);
  //
  // Wait for response for both Get and SetFeature, but since some panels don't respond to SetData, a timeout is implemented
  //
  if (TimeOutVal == 0x00) {
    Timeout = GET_SET_FEATURE_TIMEOUT;
  } else {
    Timeout = TimeOutVal;
  }
  do {
    if (iTouchDev->Me2HidBufferFull == TRUE && !IsTouchEvent (iTouchDev)) {
      CopyMem (Buffer, iTouchDev->Me2HidBuffer + sizeof (TOUCH_FEEDBACK_HDR), Length);
      Me2HidBufferConsumed (iTouchDev);
      iTouchDev->HidProtocolActive = FALSE;
      return EFI_SUCCESS;
    }

    MicroSecondDelay (1000);
    Timeout--;
  } while (Timeout > 0);

  DEBUG ((DEBUG_INFO, "TIMEOUT\n"));
  iTouchDev->HidProtocolActive = FALSE;
  return EFI_TIMEOUT;
}

/**
  Performs SetFeature function as described in Human Interface Device spec.
  Must be called with priority of CALLBACK or lower.
  WARNING! Some iTouch panels respond to SetFeature with data and some don't.
  The only way to not miss possible response is to wait for the data for some time
  The disadvantage is that in case of no response, driver wastes time waiting for one.

  @param  This       Pointer to instance of protocol
  @param  Length     Size of buffer
  @param  Buffer     On input, contains data to be sent to iTouch
  @param  TimeOutVal Parameter added to support Capsule Update. If provided value is 0 default is set GET_SET_FEATURE_TIMEOUT (5000)

  @retval EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
HidSetFeature (
  IN ITOUCH_HID_PROTOCOL  *This,
  IN UINT32               Length,
  IN OUT UINT8            *Buffer,
  IN UINTN                Timeout
  )
{
  return HidGetSetFeature (This, Length, Buffer, SET_FEATURE, Timeout);
}

/**
  Performs GetFeature function as described in Human Interface Device spec
  Must be called with priority of CALLBACK or lower.

  @param  This       Pointer to instance of protocol
  @param  Length     Size of buffer
  @param  Buffer     On input, contains ReportId in 1st byte. On output, filled with Feature data from iTouch
  @param  TimeOutVal Parameter added to support Capsule Update. If provided value is 0 default is set GET_SET_FEATURE_TIMEOUT (5000)

  @retval EFI_SUCCESS when iTouch responded with data
  @retval EFI_TIMEOUT when there was no response
**/
EFI_STATUS
EFIAPI
HidGetFeature (
  IN ITOUCH_HID_PROTOCOL  *This,
  IN UINT32               Length,
  IN OUT UINT8            *Buffer,
  IN UINTN                Timeout
  )
{
  return HidGetSetFeature (This, Length, Buffer, GET_FEATURE, Timeout);
}


/**
  Parses data stream from touch device and decodes it into X/Y/Z coordinates + button

  @param[in, out]  Output                Pointer to memory buffer containing output pointer state
  @param[in]       InputStream           Pointer to memory buffer containing HID data

  @retval ABSOLUTE_POINTER_STATE structure filled with decoded HID data

**/
VOID
IntegratedTouchParseInput (
  IN OUT EFI_ABSOLUTE_POINTER_STATE *Output,
  IN     SINGLE_FINGER_REPORT*      InputStream
  )
{
  Output->CurrentX = (InputStream->HigherXbyte << 8) + InputStream->LowerXbyte;
  Output->CurrentY = (InputStream->HigherYbyte << 8) + InputStream->LowerYbyte;
  Output->CurrentZ = 0;
  Output->ActiveButtons = InputStream->TouchSts;
}

/**
  Unloads an image.

  @param  ImageHandle           Handle that identifies the image to be unloaded.

  @retval EFI_SUCCESS           The image has been unloaded.
  @retval EFI_INVALID_PARAMETER ImageHandle is not a valid image handle.

**/
EFI_STATUS
EFIAPI
IntegratedTouchUnload (
  IN EFI_HANDLE  ImageHandle
  )
{
  EFI_STATUS  Status;
  EFI_HANDLE  *HandleBuffer;
  UINTN       HandleCount;
  UINTN       Index;

  Status = EFI_SUCCESS;

  //
  // Retrieve array of all handles in the handle database
  //
  Status = gBS->LocateHandleBuffer (
                  AllHandles,
                  NULL,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Disconnect the current driver from handles in the handle database
  //
  for (Index = 0; Index < HandleCount; Index++) {
    Status = gBS->DisconnectController (HandleBuffer[Index], ImageHandle, NULL);
  }

  //
  // Free the array of handles
  //
  FreePool (HandleBuffer);

  //
  // Uninstall the driver version protocol
  //
  Status = gBS->UninstallMultipleProtocolInterfaces (
                  ImageHandle,
                  &gEfiDriverSupportedEfiVersionProtocolGuid, &gIntegratedTouchDriverSupportedEfiVersion,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Uninstall protocols installed in the driver entry point
  //
  Status = gBS->UninstallMultipleProtocolInterfaces (
                  ImageHandle,
                  &gEfiDriverBindingProtocolGuid,  &gIntegratedTouchDriverBinding,
                  &gEfiComponentNameProtocolGuid,  &gIntegratedTouchDriverComponentName,
                  &gEfiComponentName2ProtocolGuid, &gIntegratedTouchDriverComponentName2,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  return EFI_SUCCESS;
}


/**
  AbsPtr protocol's WaitForInput (called when a consumer of AbsPtr protocol waits for new data)

  @param  Event              Pointer to event that triggered this callback
  @param  Context            Device context
**/
VOID
EFIAPI
AbsPtrWaitForInput (
  IN EFI_EVENT Event,
  IN VOID *Context
  )
{

}

/**
  Reset touch panel
  Function required by AbsPtr protocol. We don't support any error flows yet, so no need to reset anything.

  @param  This
  @param  ExtendedVerification

  @retval EFI_UNSUPPORTED
**/
EFI_STATUS
EFIAPI
AbsPtrReset (
  IN EFI_ABSOLUTE_POINTER_PROTOCOL *This,
  IN BOOLEAN                       ExtendedVerification
  )
{
  DEBUG ((DEBUG_INFO, "iTOUCH reset attempted\n"));
  return EFI_UNSUPPORTED;
}

/**
  If not-yet-consumed touch data is available, GetState() returns it and marks it unavailable
  If such data is not available, error will be returned. User should wait until WaitForInput event gets signalled

  @param  This
  @param  State

  @retval EFI_SUCCESS     means data was available and has been consumed
  @retval EFI_NOT_READY   data not available
**/
EFI_STATUS
EFIAPI
AbsPtrGetState (
  IN      EFI_ABSOLUTE_POINTER_PROTOCOL  *This,
  IN OUT  EFI_ABSOLUTE_POINTER_STATE     *State
  )
{
  INTEGRATED_TOUCH_DEV     *iTouchDev;

  if (State == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  iTouchDev  = INTEGRATED_TOUCH_CONTEXT_FROM_ABSPTR_PROTOCOL (This);

  if (iTouchDev->TouchDataAvailable) {
    CopyMem (State, &iTouchDev->TouchData, sizeof (EFI_ABSOLUTE_POINTER_STATE));
    iTouchDev->TouchDataAvailable = FALSE;
    return EFI_SUCCESS;
  } else {
    return EFI_NOT_READY;
  }
}


/**
  Stops Integrated Touch driver from using HECI3 Protocol.
  Does not unload the driver.

  @param[in]  This       Pointer to instance of protocol

  @retval EFI_SUCCESS        when iTouch successfully stopped
  @retval EFI_DEVICE_ERROR   when failed to get device context, or device has a problem
  @retval EFI_NOT_READY      when iTouch is still trying to initialize
**/
EFI_STATUS
EFIAPI
IntegratedTouchStop (
  IN  INTEGRATED_TOUCH_PROTOCOL  *This
  )
{
  INTEGRATED_TOUCH_DEV     *iTouchDev;

  DEBUG ((DEBUG_INFO, "IntegratedTouchStop Start \n"));

  //
  // Get iTouchDevice context from Protocol
  //
  iTouchDev = INTEGRATED_TOUCH_CONTEXT_FROM_PROTOCOL (This);

  if (iTouchDev->Signature != INTEGRATED_TOUCH_SIGNATURE || iTouchDev->IntegratedTouchProtocol.DeviceStatus == EFI_DEVICE_ERROR) {
    return EFI_DEVICE_ERROR;
  }

  if (iTouchDev->Initialized != TRUE) {
    return EFI_NOT_READY;
  }

  gBS->CloseEvent (iTouchDev->WaitReadyEvent);
  gBS->CloseEvent (iTouchDev->AbsPtrProtocol.WaitForInput);
  gBS->CloseEvent (iTouchDev->HeciPollingEvent);

  iTouchDev->TouchDataAvailable = FALSE;
  iTouchDev->Me2HidBufferFull   = FALSE;
  iTouchDev->IntegratedTouchProtocol.DeviceStatus = EFI_NOT_READY;

  //
  // Clear Memory Window. Must be called after HeciPollingEvent is stopped,
  // otherwise HeciPollingEvent could consume the HECI response needed in ClearMemWindow
  //
  if (iTouchDev->Initialized) {
    TouchSensorClearMemWindow ();
  }
  iTouchDev->Initialized        = FALSE;

  DEBUG ((DEBUG_INFO, "IntegratedTouchStop End\n"));

  return EFI_SUCCESS;
}

/**
  Initialize integrated touch according to procedure described in EDS

  @param  iTouchDev       context of iTouch device

  @retval EFI_SUCCESS     iTouch initialized successfully
  @retval other           error during initialization
**/
EFI_STATUS
IntegratedTouchInitialize (
  INTEGRATED_TOUCH_DEV                *iTouchDev
  )
{
  EFI_STATUS Status;
  UINTN      NumberOfBytes;

  //
  // HID driver initiates TOUCH_SENSOR_GET_VENDOR_INFO_CMD command and gets response from ME.
  //
  Status = TouchSensorGetDeviceInfo (&iTouchDev->TouchBufferSize, &iTouchDev->FeedbackBufferSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchInitialize TouchSensorGetDeviceInfo Status=%r\n", Status));
    return Status;
  }

  Status = TouchSensorSetSingleTouchMode ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchInitialize TouchSensorSetMode Status=%r\n", Status));
    return Status;
  }

  //
  // HID driver allocates contiguous buffers for Me2Hid and Feedback based on info from TOUCH_SENSOR_GET_VENDOR_INFO_RSP_DATA. The number of each
  // type of buffer can be 1 to TOUCH_SENSOR_MAX_DATA_BUFFERS.
  //
  Status = iTouchDev->PciIo->AllocateBuffer (
                               iTouchDev->PciIo,
                               AllocateAnyPages,
                               EfiBootServicesData,
                               EFI_SIZE_TO_PAGES (iTouchDev->TouchBufferSize),
                               (VOID **) &iTouchDev->Me2HidBuffer,
                               0
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchInitialize AllocateTouchBuffer: PciIo->AllocateBuffer failed! EFI_STATUS = %r\n", Status));
    return Status;
  }
  NumberOfBytes = iTouchDev->TouchBufferSize;
  Status = iTouchDev->PciIo->Map (
                               iTouchDev->PciIo,
                               EfiPciIoOperationBusMasterCommonBuffer,
                               iTouchDev->Me2HidBuffer,
                               &NumberOfBytes,
                               &iTouchDev->Me2HidBufferDevAddr,
                               &iTouchDev->Me2HidBufferMapping
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchInitialize AllocateTouchBuffer: PciIo->Map failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  Status = iTouchDev->PciIo->AllocateBuffer (
                               iTouchDev->PciIo,
                               AllocateAnyPages,
                               EfiBootServicesData,
                               EFI_SIZE_TO_PAGES (iTouchDev->FeedbackBufferSize),
                               (VOID **) &iTouchDev->FeedbackBuffer,
                               0
                               );
   if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchInitialize AllocateFeedbackBuffer: PciIo->AllocateBuffer failed! EFI_STATUS = %r\n", Status));
    return Status;
  }
  NumberOfBytes = iTouchDev->FeedbackBufferSize;
  Status = iTouchDev->PciIo->Map (
                               iTouchDev->PciIo,
                               EfiPciIoOperationBusMasterCommonBuffer,
                               iTouchDev->FeedbackBuffer,
                               &NumberOfBytes,
                               &iTouchDev->FeedbackBufferDevAddr,
                               &iTouchDev->FeedbackBufferMapping
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchInitialize AllocateFeedbackBuffer: PciIo->Map failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  //
  // Hid2Me has the same size as feedback buffer
  //
  Status = iTouchDev->PciIo->AllocateBuffer (
                               iTouchDev->PciIo,
                               AllocateAnyPages,
                               EfiBootServicesData,
                               EFI_SIZE_TO_PAGES (iTouchDev->FeedbackBufferSize),
                               (VOID **) &iTouchDev->Hid2MeBuffer,
                               0
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchInitialize AllocateHid2MeBuffer: PciIo->AllocateBuffer failed! EFI_STATUS = %r\n", Status));
    return Status;
  }
  Status = iTouchDev->PciIo->Map (
                               iTouchDev->PciIo,
                               EfiPciIoOperationBusMasterCommonBuffer,
                               iTouchDev->Hid2MeBuffer,
                               &NumberOfBytes,
                               &iTouchDev->Hid2MeBufferDevAddr,
                               &iTouchDev->Hid2MeBufferMapping
                               );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchInitialize AllocateHid2MeBuffer: PciIo->Map failed! EFI_STATUS = %r\n", Status));
    return Status;
  }

  ZeroMem (iTouchDev->Hid2MeBuffer, iTouchDev->FeedbackBufferSize);
  ZeroMem (iTouchDev->FeedbackBuffer, iTouchDev->FeedbackBufferSize);
  //
  // HID driver sends TOUCH_SENSOR_SET_MEM_WINDOW_CMD command with address of contiguous DMA buffers. This must
  // always include at least one Me2Hid/Feedback Buffer pair, and Hid2Me Buffer. Tail Offset, DoorbellCookie
  // and WorkQueue sizes are only required for multi-touch but not single-finger HID mode. ME will respond with
  // a status code in TOUCH_SENSOR_SET_MEM_WINDOW_RSP.
  //
  Status = TouchSensorSetMemWindow ((UINT8 *)(UINTN)iTouchDev->Me2HidBufferDevAddr, (UINT8 *)(UINTN)iTouchDev->FeedbackBufferDevAddr, (UINT8 *)(UINTN)iTouchDev->Hid2MeBufferDevAddr, iTouchDev->FeedbackBufferSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchInitialize TouchSensorSetMemWindow Status=%r\n", Status));
    return Status;
  }

  //
  // Send initial request for data
  // HID driver sends TOUCH_SENSOR_HID_READY_FOR_DATA_CMD to wait for ME to DMA data.
  //
  Status = TouchSensorSendHidReadyForData ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchInitialize TouchSensorHidReadyForData Status=%r\n", Status));
    return Status;
  }

  return Status;
}


/**
  Starts Heci and Pointer polling on Integrated Touch

  @param  iTouchDev       context of iTouch device

  @retval EFI_SUCCESS     iTouch initialized successfully
  @retval other           error during initialization
**/
EFI_STATUS
IntegratedTouchStartPolling (
  INTEGRATED_TOUCH_DEV                *iTouchDev
  )
{
  EFI_STATUS    Status;

  Status = gBS->CreateEvent (EVT_NOTIFY_WAIT, TPL_NOTIFY, AbsPtrWaitForInput, (VOID*) iTouchDev, &iTouchDev->AbsPtrProtocol.WaitForInput);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchStartPolling error, cannot create polling event, %r\n", Status));
    return Status;
  }

  //
  // periodic events run with NOTIFY priority to guarantee driver works fine when called from code that runs with CALLBACK priority
  //
  Status = gBS->CreateEvent (EVT_TIMER | EVT_NOTIFY_SIGNAL, TPL_NOTIFY, HeciPolling, (VOID*) iTouchDev, &iTouchDev->HeciPollingEvent);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchStartPolling error, cannot create HeciPollingEvent timer event, %r\n", Status));
    return Status;
  }

  Status = gBS->SetTimer (iTouchDev->HeciPollingEvent, TimerPeriodic, ITOUCH_POLLING_PERIOD);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchStartPolling error, cannot enable HeciPollingEvent timer, %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Event designated to start Integrated Touch Initialization after CSME reports
  that it is ready.
  Gets invoked for the first time by signal notify, later on called by Timer after TriggerTime expires.

  @param  EFI_EVENT             Handle to an event structure
  @param  VOID                  Pointer to the notification functions context,
                                iTouchDevice

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
VOID
EFIAPI
IntegratedTouchWaitReadyEvent (
  IN EFI_EVENT   Event,
  IN VOID        *Context
  )
{
  EFI_STATUS             Status;
  INTEGRATED_TOUCH_DEV   *iTouchDev;

  DEBUG ((DEBUG_INFO, "IntegratedTouchWaitReadyEvent Start() \n"));

  iTouchDev = Context;
  if (iTouchDev == NULL) {
    return;
  }

  if (iTouchDev->WaitReadyCount > MAX_WAIT_FOR_ITOUCH_READY_COUNT) {
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchWaitReadyEvent Ready Counter exceeded. iTouch initialization failed.\n"));
    goto ERROR_EXIT;
  }

  //
  // HID driver sends TOUCH_SENSOR_NOTIFY_DEV_READY_CMD during Start procedure and waits for response.
  // No Response might be expected since integrated Touch needs some time to initialize
  //
  Status = TouchSensorCheckDevReady ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "  IntegratedTouchWaitReadyEvent TouchSensorCheckDevReady Status=%r WaitReadyCount: %d\n", Status, iTouchDev->WaitReadyCount));
    iTouchDev->WaitReadyCount++;
    return;
  }

  DEBUG ((DEBUG_INFO, "  IntegratedTouchWaitReadyEvent closing Wait Ready Event \n"));
  gBS->CloseEvent (Event);

  //
  // Initialize Integrated Touch
  //
  Status = IntegratedTouchInitialize (iTouchDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchWaitReadyEvent Initialize failed with Status=%r\n", Status));
    goto ERROR_EXIT;
  }

  //
  // Start Polling
  //
  Status = IntegratedTouchStartPolling (iTouchDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchWaitReadyEvent Start Polling failed with Status=%r\n", Status));
    goto ERROR_EXIT;
  }

  //
  // Install Protocols
  //
  Status = IntegratedTouchInstallProtocols (iTouchDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchWaitReadyEvent Install Protocols failed with Status=%r\n", Status));
    goto ERROR_EXIT;
  }

  iTouchDev->Initialized                           = TRUE;
  iTouchDev->IntegratedTouchProtocol.DeviceStatus  = EFI_SUCCESS;
  iTouchDev->HidProtocol.MaxBufferLength  = MIN (TOUCH_HID_2_ME_BUFFER_SIZE_MAX, iTouchDev->FeedbackBufferSize) - sizeof (TOUCH_FEEDBACK_HDR);

  gBS->ConnectController (iTouchDev->ControllerHandle, NULL, NULL, TRUE);
  return;

ERROR_EXIT:
  iTouchDev->IntegratedTouchProtocol.DeviceStatus  = EFI_DEVICE_ERROR;
  //
  // Integrated Touch driver context is unloaded during gBS->ExitBootServices()
  //
  DEBUG ((DEBUG_ERROR, "IntegratedTouchWaitReadyEvent End() \n"));
}


/**
  This is the declaration of an EFI image entry point. This entry point is
  the same for UEFI Applications, UEFI OS Loaders, and UEFI Drivers including
  both device drivers and bus drivers.

  @param  ImageHandle           The firmware allocated handle for the UEFI image.
  @param  SystemTable           A pointer to the EFI System Table.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
IntegratedTouchEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS    Status;

  Status = EFI_SUCCESS;
  //
  // Install UEFI Driver Model protocol(s).
  //
  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gIntegratedTouchDriverBinding,
             ImageHandle,
             &gIntegratedTouchDriverComponentName,
             &gIntegratedTouchDriverComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Install Driver Supported EFI Version Protocol onto ImageHandle
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gEfiDriverSupportedEfiVersionProtocolGuid, &gIntegratedTouchDriverSupportedEfiVersion,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Tests to see if this driver supports a given controller. If a child device is provided,
  it further tests to see if this driver supports creating a handle for the specified child device.

  This function checks to see if the driver specified by This supports the device specified by
  ControllerHandle. Drivers will typically use the device path attached to
  ControllerHandle and/or the services from the bus I/O abstraction attached to
  ControllerHandle to determine if the driver supports ControllerHandle. This function
  may be called many times during platform initialization. In order to reduce boot times, the tests
  performed by this function must be very small, and take as little time as possible to execute. This
  function must not change the state of any hardware devices, and this function must be aware that the
  device specified by ControllerHandle may already be managed by the same driver or a
  different driver. This function must match its calls to AllocatePages() with FreePages(),
  AllocatePool() with FreePool(), and OpenProtocol() with CloseProtocol().
  Because ControllerHandle may have been previously started by the same driver, if a protocol is
  already in the opened state, then it must not be closed with CloseProtocol(). This is required
  to guarantee the state of ControllerHandle is not modified by this function.

  @param[in]  This                 A pointer to the EFI_DRIVER_BINDING_PROTOCOL instance.
  @param[in]  ControllerHandle     The handle of the controller to test. This handle
                                   must support a protocol interface that supplies
                                   an I/O abstraction to the driver.
  @param[in]  RemainingDevicePath  A pointer to the remaining portion of a device path.  This
                                   parameter is ignored by device drivers, and is optional for bus
                                   drivers. For bus drivers, if this parameter is not NULL, then
                                   the bus driver must determine if the bus controller specified
                                   by ControllerHandle and the child controller specified
                                   by RemainingDevicePath are both supported by this
                                   bus driver.

  @retval EFI_SUCCESS              The device specified by ControllerHandle and
                                   RemainingDevicePath is supported by the driver specified by This.
  @retval EFI_ALREADY_STARTED      The device specified by ControllerHandle and
                                   RemainingDevicePath is already being managed by the driver
                                   specified by This.
  @retval EFI_ACCESS_DENIED        The device specified by ControllerHandle and
                                   RemainingDevicePath is already being managed by a different
                                   driver or an application that requires exclusive access.
                                   Currently not implemented.
  @retval EFI_UNSUPPORTED          The device specified by ControllerHandle and
                                   RemainingDevicePath is not supported by the driver specified by This.
**/
EFI_STATUS
EFIAPI
IntegratedTouchDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
  INTEGRATED_TOUCH_PROTOCOL       *IntegratedTouchProtocol;
  EFI_STATUS                      Status;
  EFI_PCI_IO_PROTOCOL             *PciIo;
  UINTN                           Seg;
  UINTN                           Bus;
  UINTN                           Dev;
  UINTN                           Fun;

  //
  // Verify that this driver is not already running on this device
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gIntegratedTouchProtocolGuid,
                  (VOID **)&IntegratedTouchProtocol,
                  NULL,
                  NULL,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    return EFI_ALREADY_STARTED;
  }

  //
  // this driver installs directly on HECI3 PCI device
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &PciIo,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return EFI_UNSUPPORTED;
  }

  PciIo->GetLocation (PciIo,&Seg,&Bus,&Dev,&Fun);
  //
  // Close the PCI I/O Protocol that was opened with PROTOCOL_BY_DRIVER
  //
  gBS->CloseProtocol (ControllerHandle, &gEfiPciIoProtocolGuid, This->DriverBindingHandle, ControllerHandle);

  if ((Bus == ME_BUS) && (Dev == ME_DEVICE_NUMBER) && (Fun == HECI3_FUNCTION_NUMBER)) {
    DEBUG ((DEBUG_INFO, "IntegratedTouchDriverBindingSupported on BDF - %d:%d:%d\n", Bus, Dev, Fun));
    return EFI_SUCCESS;
  }
  return EFI_UNSUPPORTED;
}


/**
  Starts a device controller or a bus controller.

  The Start() function is designed to be invoked from the EFI boot service ConnectController().
  As a result, much of the error checking on the parameters to Start() has been moved into this
  common boot service. It is legal to call Start() from other locations,
  but the following calling restrictions must be followed, or the system behavior will not be deterministic.
  1. ControllerHandle must be a valid EFI_HANDLE.
  2. If RemainingDevicePath is not NULL, then it must be a pointer to a naturally aligned
     EFI_DEVICE_PATH_PROTOCOL.
  3. Prior to calling Start(), the Supported() function for the driver specified by This must
     have been called with the same calling parameters, and Supported() must have returned EFI_SUCCESS.

  @param[in]  This                 A pointer to the EFI_DRIVER_BINDING_PROTOCOL instance.
  @param[in]  ControllerHandle     The handle of the controller to start. This handle
                                   must support a protocol interface that supplies
                                   an I/O abstraction to the driver.
  @param[in]  RemainingDevicePath  A pointer to the remaining portion of a device path.  This
                                   parameter is ignored by device drivers, and is optional for bus
                                   drivers. For a bus driver, if this parameter is NULL, then handles
                                   for all the children of Controller are created by this driver.
                                   If this parameter is not NULL and the first Device Path Node is
                                   not the End of Device Path Node, then only the handle for the
                                   child device specified by the first Device Path Node of
                                   RemainingDevicePath is created by this driver.
                                   If the first Device Path Node of RemainingDevicePath is
                                   the End of Device Path Node, no child handle is created by this
                                   driver.

  @retval EFI_SUCCESS              The device was started.
  @retval EFI_DEVICE_ERROR         The device could not be started due to a device error.Currently not implemented.
  @retval EFI_OUT_OF_RESOURCES     The request could not be completed due to a lack of resources.
  @retval Others                   The driver failed to start the device.

**/
EFI_STATUS
EFIAPI
IntegratedTouchDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath OPTIONAL
  )
{
  INTEGRATED_TOUCH_DEV            *iTouchDev;
  EFI_STATUS                      Status;
  ME_BIOS_PAYLOAD_HOB             *MbpHob;
  UINT64                          Supports;
  UINT64                          OriginalPciAttributes;

  OriginalPciAttributes  = 0;
  MbpHob                 = NULL;

  DEBUG ((DEBUG_INFO, "IntegratedTouchDriverBindingStart Start()\n"));

  //
  // Get the MBP Data and check if iTouch is supported by CSME
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);

  if (MbpHob != NULL) {
    if (!MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.IntegratedTouch) {
      DEBUG ((DEBUG_WARN, "  IntegratedTouchDriverBindingStart error, iTouch not available in MBP\n"));
      return EFI_UNSUPPORTED;
    }
  } else {
    Status = EFI_NOT_FOUND;
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchDriverBindingStart error, cannot read Fw Capabilities Status: %r\n", Status));
    return Status;
  }

  //
  // Allocate the driver context
  //
  iTouchDev = AllocateZeroPool (sizeof (INTEGRATED_TOUCH_DEV));
  if (iTouchDev == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Save PciIo Protocol instance for DMA usage
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gEfiPciIoProtocolGuid,
                  (VOID **) &iTouchDev->PciIo,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Save Controllers Pci Configuration state
  //
  Status = iTouchDev->PciIo->Attributes (iTouchDev->PciIo, EfiPciIoAttributeOperationGet, 0, &OriginalPciAttributes);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  iTouchDev->PciAttributes = OriginalPciAttributes;

  //
  // Enable Controller
  //
  Status = iTouchDev->PciIo->Attributes (iTouchDev->PciIo, EfiPciIoAttributeOperationSupported, 0, &Supports);
  if (!EFI_ERROR (Status)) {
    Supports &= (UINT64) EFI_PCI_DEVICE_ENABLE;
    Status = iTouchDev->PciIo->Attributes (iTouchDev->PciIo, EfiPciIoAttributeOperationEnable, Supports, NULL);
  }
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Install only IntegrateTouch Protocol to avoid Binding Start getting invoked for second time.
  // Other protocols will be installed after integrated Touch successful Initialization
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ControllerHandle,
                  &gIntegratedTouchProtocolGuid,
                  &iTouchDev->IntegratedTouchProtocol,
                  NULL,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ERROR - iTOUCH failed to install upper protocol, Status: %r\n", Status));
    FreePool (iTouchDev);
    return Status;
  }

  //
  // Initialize the driver context
  //
  iTouchDev->Signature               = INTEGRATED_TOUCH_SIGNATURE;
  iTouchDev->ControllerHandle        = ControllerHandle;
  iTouchDev->Initialized             = FALSE;

  iTouchDev->HidProtocol.Revision    = ITOUCH_HID_PROTOCOL_REVISION;
  iTouchDev->HidProtocol.GetFeature  = HidGetFeature;
  iTouchDev->HidProtocol.SetFeature  = HidSetFeature;
  iTouchDev->HidProtocol.MaxBufferLength  = 0;

  iTouchDev->AbsPtrProtocol.Reset    = AbsPtrReset;
  iTouchDev->AbsPtrProtocol.GetState = AbsPtrGetState;
  iTouchDev->AbsPtrProtocol.Mode     = &(iTouchDev->Mode);

  iTouchDev->IntegratedTouchProtocol.Revision     = INTEGRATED_TOUCH_PROTOCOL_REVISION;
  iTouchDev->IntegratedTouchProtocol.DeviceStatus = EFI_NOT_READY;
  iTouchDev->IntegratedTouchProtocol.DriverStop   = IntegratedTouchStop;

  iTouchDev->HidProtocolActive       = FALSE;
  iTouchDev->TouchDataAvailable      = FALSE;
  iTouchDev->Me2HidBufferFull        = FALSE;
  iTouchDev->Hid2MeBufferFull        = FALSE;

  AddUnicodeString2 ("eng", gIntegratedTouchDriverComponentName.SupportedLanguages,  &iTouchDev->ControllerNameTable, L"Integrated Touchpanel Driver", TRUE);
  AddUnicodeString2 ("en",  gIntegratedTouchDriverComponentName2.SupportedLanguages, &iTouchDev->ControllerNameTable, L"Integrated Touchpanel Driver", FALSE);

  // resolution is hardcoded because CSME doesn't fully support HID protocol and is unable to report anything besides raw touch data
  iTouchDev->Mode.AbsoluteMinX = 0;
  iTouchDev->Mode.AbsoluteMinY = 0;
  iTouchDev->Mode.AbsoluteMinZ = 0;
  iTouchDev->Mode.AbsoluteMaxX = 0x7FFF;
  iTouchDev->Mode.AbsoluteMaxY = 0x7FFF;
  iTouchDev->Mode.AbsoluteMaxZ = 0;
  iTouchDev->Mode.Attributes   = 0;

  iTouchDev->WaitReadyCount    = 0;

  //
  // HID driver initiates HECI Link Reset sequence (see HECI HPS or C-Spec).
  //
  Status = TouchResetHeci3 ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchDriverBindingStart TouchResetHeci3 failed with Status=%r\n", Status));
    return Status;
  }

  Status = IntegratedTouchCreateStartAndExitEvents (iTouchDev);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchDriverBindingStart CreateStartAndExitEvents failed with Status=%r\n", Status));
    return Status;
  }

  //
  // Program the timer event to be signalled every WAIT_FOR_ITOUCH_READY_DELAY until MAX_WAIT_FOR_ITOUCH_READY_COUNT reached
  //
  DEBUG ((DEBUG_INFO, "  IntegratedTouchDriverBindingStart start timer on Wait Ready Event each %d milliseconds\n", WAIT_FOR_ITOUCH_READY_DELAY));
  Status = gBS->SetTimer (iTouchDev->WaitReadyEvent, TimerPeriodic, EFI_TIMER_PERIOD_MILLISECONDS (WAIT_FOR_ITOUCH_READY_DELAY));
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchDriverBindingStart failed to start timer on Wait Ready Event with Status=%r\n", Status));
    return Status;
  }

  //
  // Signal Event to start it for the first time
  //
  //
  // HID driver sends TOUCH_SENSOR_NOTIFY_DEV_READY_CMD during Start procedure and waits for response.
  // No Response might be expeted since integrated Touch needs some time to initialize
  //
  Status = TouchSensorNotifyDevReady ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchDriverBindingStart failed to send TOUCH_SENSOR_NOTIFY_DEV_READY_CMD with Status=%r\n", Status));
    return Status;
  }
  gBS->SignalEvent (iTouchDev->WaitReadyEvent);

  DEBUG ((DEBUG_INFO, "IntegratedTouchDriverBindingStart End()\n"));

  return Status;
}


/**
  Stops a device controller or a bus controller.

  The Stop() function is designed to be invoked from the EFI boot service DisconnectController().
  As a result, much of the error checking on the parameters to Stop() has been moved
  into this common boot service. It is legal to call Stop() from other locations,
  but the following calling restrictions must be followed, or the system behavior will not be deterministic.
  1. ControllerHandle must be a valid EFI_HANDLE that was used on a previous call to this
     same driver's Start() function.
  2. The first NumberOfChildren handles of ChildHandleBuffer must all be a valid
     EFI_HANDLE. In addition, all of these handles must have been created in this driver's
     Start() function, and the Start() function must have called OpenProtocol() on
     ControllerHandle with an Attribute of EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER.

  @param[in]  This              A pointer to the EFI_DRIVER_BINDING_PROTOCOL instance.
  @param[in]  ControllerHandle  A handle to the device being stopped. The handle must
                                support a bus specific I/O protocol for the driver
                                to use to stop the device.
  @param[in]  NumberOfChildren  The number of child device handles in ChildHandleBuffer.
  @param[in]  ChildHandleBuffer An array of child handles to be freed. May be NULL
                                if NumberOfChildren is 0.

  @retval EFI_SUCCESS           The device was stopped.
  @retval EFI_DEVICE_ERROR      The device could not be stopped due to a device error.

**/
EFI_STATUS
EFIAPI
IntegratedTouchDriverBindingStop (
  IN EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN EFI_HANDLE                   ControllerHandle,
  IN UINTN                        NumberOfChildren,
  IN EFI_HANDLE                   *ChildHandleBuffer OPTIONAL
  )
{
  INTEGRATED_TOUCH_PROTOCOL       *IntegratedTouchProtocol;
  INTEGRATED_TOUCH_DEV            *iTouchDev;
  EFI_STATUS                      Status;

  DEBUG ((DEBUG_INFO, "IntegratedTouchDriverBindingStop Start\n"));

  //
  // Check if IntegratedTouchProtocol is installed
  //
  Status = gBS->OpenProtocol (
                  ControllerHandle,
                  &gIntegratedTouchProtocolGuid,
                  (VOID **) &IntegratedTouchProtocol,
                  This->DriverBindingHandle,
                  ControllerHandle,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchDriverBindingStop Failed to get IntegratedTouchNullProtocol, Status: %r\n", Status));
    return EFI_UNSUPPORTED;
  }

  //
  // Get iTouchDevice context from Protocol
  //
  iTouchDev = INTEGRATED_TOUCH_CONTEXT_FROM_PROTOCOL (IntegratedTouchProtocol);
  if (iTouchDev == NULL) {
    return EFI_DEVICE_ERROR;
  }

  Status = gBS->UninstallMultipleProtocolInterfaces (
                  ControllerHandle,
                  &gIntegratedTouchProtocolGuid,
                  &iTouchDev->IntegratedTouchProtocol,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "  IntegratedTouchDriverBindingStop Failed to Uninstall IntegratedTouchProtocol, Status: %r\n", Status));
  }

  //
  //  Uninstall all installed protocols
  //
  if (iTouchDev->Initialized) {
    Status = gBS->UninstallMultipleProtocolInterfaces (
                    ControllerHandle,
                    &gEfiAbsolutePointerProtocolGuid,
                    &iTouchDev->AbsPtrProtocol,
                    NULL
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_WARN, "  IntegratedTouchDriverBindingStop Failed to Uninstall AbsolutePointerProtocoll, Status: %r\n", Status));
    }
    Status = gBS->UninstallMultipleProtocolInterfaces (
                    ControllerHandle,
                    &gIntegratedTouchHidProtocolGuid,
                    &iTouchDev->HidProtocol,
                    NULL
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_WARN, "  IntegratedTouchDriverBindingStop Failed to Uninstall IntegratedTouchHidProtocol, Status: %r\n", Status));
    }
  }

  //
  // Free all the structures that were allocated on behalf of ControllerHandle in Start().
  //
  IntegratedTouchCleanUp (iTouchDev);

  DEBUG ((DEBUG_INFO, "IntegratedTouchDriverBindingStop End\n"));

  return Status;
}

/**
  Function to unload Integrated Touch Driver when
  gBS->ExitBootServices() called or LegacyBoot event.

  @param  Event                   Pointer to this event
  @param  Context                 Event handler private data

**/
VOID
EFIAPI
IntegratedTouchExitEvent (
  IN EFI_EVENT     Event,
  IN VOID          *Context
  )
{
  INTEGRATED_TOUCH_DEV     *iTouchDev;

  iTouchDev = Context;

  DEBUG ((DEBUG_INFO, "IntegratedTouchExitEvent Start \n"));

  IntegratedTouchCleanUp (iTouchDev);

  if (Event != NULL) {
    gBS->CloseEvent (Event);
  }

  DEBUG ((DEBUG_INFO, "IntegratedTouchExitEvent End \n"));
  return;
}


/**
  Free IntegratedTouch structure allocated in Start()
  Close all Events except exit event
  Free allocated Unicode Strings
  Calls TouchSensorClearMemWindow

  @param[in]  iTouchDev       context of iTouch device

**/
VOID
EFIAPI
IntegratedTouchCleanUp (
  IN INTEGRATED_TOUCH_DEV                *iTouchDev
  )
{
  DEBUG ((DEBUG_INFO, "IntegratedTouchCleanUp Start \n"));

  //
  // Check if CleanUp is required
  //
  if (iTouchDev->Signature != INTEGRATED_TOUCH_SIGNATURE) {
    DEBUG ((DEBUG_INFO, "IntegratedTouchCleanUp Integrated Touch Structure already freed. End \n"));
    return;
  }

  //
  // Done with the events
  //
  gBS->CloseEvent (iTouchDev->WaitReadyEvent);
  gBS->CloseEvent (iTouchDev->AbsPtrProtocol.WaitForInput);
  gBS->CloseEvent (iTouchDev->HeciPollingEvent);

  //
  // Clear Memory Window. Must be called after HeciPollingEvent is stopped,
  // otherwise HeciPollingEvent could consume the HECI response needed in ClearMemWindow
  //
  if (iTouchDev->Initialized) {

    TouchSensorClearMemWindow ();

    iTouchDev->PciIo->Unmap (
                        iTouchDev->PciIo,
                        iTouchDev->FeedbackBufferMapping
                        );
    iTouchDev->PciIo->FreeBuffer (
                        iTouchDev->PciIo,
                        EFI_SIZE_TO_PAGES (iTouchDev->FeedbackBufferSize),
                        iTouchDev->FeedbackBuffer
                        );
    iTouchDev->PciIo->Unmap (
                        iTouchDev->PciIo,
                        iTouchDev->Hid2MeBufferMapping
                        );
    iTouchDev->PciIo->FreeBuffer (
                        iTouchDev->PciIo,
                        EFI_SIZE_TO_PAGES (iTouchDev->FeedbackBufferSize),
                        iTouchDev->Hid2MeBuffer
                        );
    iTouchDev->PciIo->Unmap (
                        iTouchDev->PciIo,
                        iTouchDev->Me2HidBufferMapping
                        );
    iTouchDev->PciIo->FreeBuffer (
                        iTouchDev->PciIo,
                        EFI_SIZE_TO_PAGES (iTouchDev->TouchBufferSize),
                        iTouchDev->Me2HidBuffer
                        );
  }

  //
  // Restore original PCI attributes
  //
  iTouchDev->PciIo->Attributes (
                      iTouchDev->PciIo,
                      EfiPciIoAttributeOperationSet,
                      iTouchDev->PciAttributes,
                      NULL
                      );

  //
  // Close and Uninstall PCI I/O Protocol that was opened with PROTOCOL_BY_DRIVER
  //
  gBS->CloseProtocol (iTouchDev->ControllerHandle, &gEfiPciIoProtocolGuid, &iTouchDev->PciIo, iTouchDev->ControllerHandle);
  gBS->UninstallMultipleProtocolInterfaces (
         iTouchDev->ControllerHandle,
         &gEfiPciIoProtocolGuid,
         &iTouchDev->PciIo,
         NULL
         );

  //
  // Done with the controller name table
  //
  FreeUnicodeStringTable (iTouchDev->ControllerNameTable);

  //
  //  Done with the driver context
  //
  ZeroMem (iTouchDev, sizeof (INTEGRATED_TOUCH_DEV));
  FreePool (iTouchDev);

  DEBUG ((DEBUG_INFO, "IntegratedTouchCleanUp End \n"));
}


/**
  Creates WaitReadyEvent responsible for iTouch Initialization
  and ExitEvent responsible for ExitBootServices clean up

  @param[in]  iTouchDev       context of iTouch device

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
IntegratedTouchCreateStartAndExitEvents (
  IN INTEGRATED_TOUCH_DEV                *iTouchDev
  )
{
  EFI_STATUS                      Status;

  ///
  /// Create WaitReady Event for calling the IntegratedToucInitialize and StartPolling procedures
  ///
  Status = gBS->CreateEvent (
                  EVT_TIMER | EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  IntegratedTouchWaitReadyEvent,
                  iTouchDev,
                  &iTouchDev->WaitReadyEvent
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "  IntegratedTouchCreateStartAndExitEvents failed to create Wait Ready Event with Status=%r\n", Status));
    return Status;
  }

  ///
  /// Create ExitBootServices/LegacyBootEvent for calling the IntegratedTouchDriverBindingStop procedure
  ///
  DEBUG ((DEBUG_INFO, "  IntegratedTouchCreateStartAndExitEvents Create ExitBootServices/LegacyBoot Event\n"));
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  IntegratedTouchExitEvent,
                  iTouchDev,
                  &gEfiEventExitBootServicesGuid,
                  &iTouchDev->ExitEvent
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  IntegratedTouchExitEvent,
                  iTouchDev,
                  &gEfiEventLegacyBootGuid,
                  &iTouchDev->ExitEvent
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}


/**
  Installs AbsolutePointerProtocol and IntegratedTouchHidProtocol
  Assigns TouchPanel Guid for Virtual Keyboard support

  @param[in]  iTouchDev       context of iTouch device

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval Others                An unexpected error occurred.
**/
EFI_STATUS
EFIAPI
IntegratedTouchInstallProtocols (
  IN INTEGRATED_TOUCH_DEV                *iTouchDev
  )
{
  EFI_STATUS                      Status;

  //
  // Install Absolute Pointer Protocol and TouchPanelGuid onto ImageHandle
  // It is assumed TouchPanelGuid lets clients (virtual keyboard driver?) distinguish
  // between touchpanels which support VK and touchpads which don't.
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &iTouchDev->ControllerHandle,
                  &gEfiAbsolutePointerProtocolGuid,
                  &iTouchDev->AbsPtrProtocol,
                  &gEfiTouchPanelGuid,
                  NULL,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchStartPolling ERROR - iTOUCH failed to install AbsolutePointerProtocol, Status: %r\n", Status));
    return Status;
  }

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &iTouchDev->ControllerHandle,
                  &gIntegratedTouchHidProtocolGuid,
                  &iTouchDev->HidProtocol,
                  NULL,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "IntegratedTouchStartPolling ERROR - iTOUCH failed to install IntegratedTouchHidProtocol, Status: %r\n", Status));
    return Status;
  }
  return Status;
}


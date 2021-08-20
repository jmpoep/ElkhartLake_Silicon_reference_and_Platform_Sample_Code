/** @file
  HID interface for IntegratedTouch feature

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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
#ifndef _INTEGRATED_TOUCH_HID_PROTOCOL_H_
#define _INTEGRATED_TOUCH_HID_PROTOCOL_H_

typedef struct _ITOUCH_HID_PROTOCOL ITOUCH_HID_PROTOCOL;

#define ITOUCH_HID_PROTOCOL_REVISION 1

/**
  Performs GetFeature function as described in Human Interface Device spec

  @param[in]  This       Pointer to instance of protocol
  @param[in]  Length     Size of buffer
  @param[in]  Buffer     On input, contains ReportId in 1st byte. On output, filled with Feature data from iTouch
  @param[in]  Timeout    Parameter added to support Capsule Update. If provided value is 0 default is set GET_SET_FEATURE_TIMEOUT (5000)

  @retval EFI_SUCCESS when iTouch responded with data
  @retval EFI_TIMEOUT when there was no response
**/
typedef
EFI_STATUS
(EFIAPI *ITOUCH_HID_GET_FEATURE)(
  IN ITOUCH_HID_PROTOCOL *This,
  IN UINT32              Length,
  IN OUT UINT8           *Buffer,
  IN UINTN               Timeout
);

/**
  Performs SetFeature function as described in Human Interface Device spec

  @param[in]  This       Pointer to instance of protocol
  @param[in]  Length     Size of buffer
  @param[in]  Buffer     On input, contains data to be sent to iTouch
  @param[in]  Timeout    Parameter added to support Capsule Update. If provided value is 0 default is set GET_SET_FEATURE_TIMEOUT (5000)

  @retval EFI_SUCCESS
**/
typedef
EFI_STATUS
(EFIAPI *ITOUCH_HID_SET_FEATURE)(
  IN ITOUCH_HID_PROTOCOL *This,
  IN UINT32              Length,
  IN UINT8               *Buffer,
  IN UINTN               Timeout
);

/**
  IntegratedTouchHid protocol is installed by iTouch driver on HECI3 device handle apart from
  AbsolutePointer protocol.

  To avoid any buffer overflows, Get/Set Feature Buffer Lengths will be limited to the devices buffer size
  or maximum CSME supported buffer length = 1024. From the Limited buffer, Length of  TOUCH_FEEDBACK_HDR
  has to be substructed from the available space.
  MaxBufferLength = MIN (maximum CSME supported length,  DevicesFeedbackBufferSize) - sizeof (TOUCH_FEEDBACK_HDR);
  Get/Set Feature will validate input buffer size and return EFI_BAD_BUFFER_SIZE if it is not right.
**/
struct _ITOUCH_HID_PROTOCOL {
  UINT8                   Revision;
  ITOUCH_HID_GET_FEATURE  GetFeature;
  ITOUCH_HID_SET_FEATURE  SetFeature;
  UINT32                  MaxBufferLength;
};

extern EFI_GUID gIntegratedTouchHidProtocolGuid;

#endif

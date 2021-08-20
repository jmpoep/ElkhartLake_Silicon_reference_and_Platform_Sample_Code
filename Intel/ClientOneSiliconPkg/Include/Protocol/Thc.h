/** @file
  Touch Host Controller Protocol for Thc feature

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#ifndef _THC_PROTOCOL_H_
#define _THC_PROTOCOL_H_

typedef struct _THC_PROTOCOL THC_PROTOCOL;

#define THC_PROTOCOL_REVISION 1

/**
  Performs GetFeature function as described in Human Interface Device specification.

  @param[in]  This       Pointer to instance of protocol.
  @param[in]  Length     Size of buffer.
  @param[in]  Buffer     On input, contains ReportId in 1st byte. On output, filled with Feature data from external device.
  @param[in]  Timeout    0 - No timeout, do not wait for response
                         1 or higher - will wait for that amount of time and copy response results to the same buffer.

  @retval EFI_NOT_READY         THC is not ready
  @retval EFI_ALREADY_STARTED   HID transaction is still active
  @retval EFI_NOT_AVAILABLE_YET THC read transaction is ongoing
  @retval EFI_BAD_BUFFER_SIZE   DW alignment is not met
  @retval EFI_TIMEOUT           a) Response did not come in time OR
                                b) DMA transaction did not finish in time
  @retval EFI_BUFFER_TOO_SMALL  THC DMA buffer is unable to fit that much data
  @retval EFI_SUCCESS           Get feature completed
**/
typedef
EFI_STATUS
(EFIAPI *HID_GET_FEATURE)(
  IN THC_PROTOCOL        *This,
  IN UINT32              Length,
  IN OUT UINT8           *Buffer,
  IN UINTN               Timeout
  );

/**
  Performs SetFeature function as described in Human Interface Device specification.

  @param[in]  This       Pointer to instance of protocol.
  @param[in]  Length     Size of buffer.
  @param[in]  Buffer     On input, contains ReportId in 1st byte. On output, filled with Feature data from external device.
  @param[in]  Timeout    0 - No timeout, do not wait for response
                         1 or higher - will wait for that amount of time and copy response results to the same buffer.

  @retval EFI_NOT_READY         THC is not ready
  @retval EFI_ALREADY_STARTED   HID transaction is still active
  @retval EFI_NOT_AVAILABLE_YET THC read transaction is ongoing
  @retval EFI_BAD_BUFFER_SIZE   DW alignment is not met
  @retval EFI_TIMEOUT           a) Response did not come in time OR
                                b) DMA transaction did not finish in time
  @retval EFI_BUFFER_TOO_SMALL  THC DMA buffer is unable to fit that much data
  @retval EFI_SUCCESS           Set feature completed
**/
typedef
EFI_STATUS
(EFIAPI *HID_SET_FEATURE)(
  IN THC_PROTOCOL        *This,
  IN UINT32              Length,
  IN UINT8               *Buffer,
  IN UINTN               Timeout
  );

/**
  Protocol used by Thc
  Once installed allows to detect if it is already running on given device
  Also used for obtaining Thc context
**/
struct _THC_PROTOCOL {
  UINT8               Revision;
  /**
    Devices Status:
      EFI_NOT_READY    - Thc initialization is still in progress
      EFI_DEVICE_ERROR - Thc Initialization failed
      EFI_SUCCESS      - Thc is functional
  **/
  EFI_STATUS          DeviceStatus;
  HID_GET_FEATURE     HidGetFeature;
  HID_SET_FEATURE     HidSetFeature;
};

extern EFI_GUID gThcProtocolGuid;

#endif // _THC_PROTOCOL_H_

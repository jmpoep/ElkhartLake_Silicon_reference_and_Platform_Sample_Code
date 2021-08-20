/** @file
  Touch Host Controller Human Interface Device API

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

#include "ThcPrivate.h"
#include "ThcDriver.h"

/**
  Performs Sanity Checks before write transfer starts

  @param[in]  ThcDev            Context of Thc device
  @param[in]  Length            Size of the buffer

  @retval EFI_NOT_READY         THC is not ready
  @retval EFI_ALREADY_STARTED   HID transaction is still active
  @retval EFI_NOT_AVAILABLE_YET THC read transaction is ongoing
  @retval EFI_BAD_BUFFER_SIZE   DW alignment is not met
  @retval EFI_SUCCESS           All checks passed
**/
EFI_STATUS
STATIC
HidSanityCheck (
  IN THC_DEV        *ThcDev,
  IN UINT32         Length
  )
{
  if (ThcDev->ThcProtocol.DeviceStatus != EFI_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "ThcProtocol HidSanityCheck Error Thc Status: %r\n", ThcDev->ThcProtocol.DeviceStatus));
    return EFI_NOT_READY;
  }

  if (ThcDev->HidActive == TRUE) {
    DEBUG ((DEBUG_ERROR, "ThcProtocol HidSanityCheck Error HID transaction is still active: %r\n", EFI_ALREADY_STARTED));
    return EFI_ALREADY_STARTED;
  }

  if (ThcDev->ReadDone == FALSE) {
    DEBUG ((DEBUG_ERROR, "ThcProtocol HidSanityCheck Error THC is still recieving data: %r\n", EFI_NOT_AVAILABLE_YET));
    return EFI_NOT_AVAILABLE_YET;
  }

  if ((Length % 4) > 0) {
    DEBUG ((DEBUG_ERROR, "ThcProtocol HidSanityCheck Error Length is not DW alligned %r\n", EFI_BAD_BUFFER_SIZE));
    return EFI_BAD_BUFFER_SIZE;
  }

  return EFI_SUCCESS;
}

/**
  Wrapper function for Set/Get Feauture support

  @param[in]  ThcDev       Context of Thc device
  @param[in]  WriteData    Write Data Header
  @param[in]  Buffer       Data Container that will be sent to external device
  @param[in]  Timeout      0 - No timeout, do not wait for response
                           1 or higher - will wait for that amount of time and copy response results to the same buffer.
  @param[in]  Length     Size of buffer.

  @retval EFI_NOT_READY         THC is not ready
  @retval EFI_ALREADY_STARTED   HID transaction is still active
  @retval EFI_NOT_AVAILABLE_YET THC read transaction is ongoing
  @retval EFI_BAD_BUFFER_SIZE   DW alignment is not met
  @retval EFI_TIMEOUT           a) Response did not come in time OR
                                b) DMA transaction did not finish in time
  @retval EFI_BUFFER_TOO_SMALL  THC DMA buffer is unable to fit that much data
  @retval EFI_SUCCESS           Hid Operation Completed
**/
EFI_STATUS
STATIC
HidGetSetFeature (
  IN THC_DEV             *ThcDev,
  IN THC_WRITE_DATA_HDR  *WriteData,
  IN OUT UINT8           *Buffer,
  IN UINTN               Timeout,
  IN UINT32              Length
  )
{
  EFI_STATUS  Status;

  //
  // Sanity checks before transfer
  //
  Status = HidSanityCheck (ThcDev, Length);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (Timeout > 0) {
    ThcDev->HidDataAvailable = FALSE;
    ThcDev->HidActive        = TRUE;
    ThcDev->HidBuffer        = Buffer;
  }

  Status = ThcDmaWriteTx (ThcDev, Buffer, WriteData);
  if (EFI_ERROR (Status)) {
    goto THC_HID_EXIT;
  }

  //
  // Wait for Response only if Timeout was set
  //
  if (Timeout > 0) {
    THC_LOCAL_DEBUG(L"ThcProtocol HidGetSetFeature Waiting for Response \n")
    DEBUG ((DEBUG_INFO, "ThcProtocol HidGetSetFeature Waiting for Response \n"));

    do {
      if (ThcDev->HidDataAvailable == TRUE && ThcDev->ReadDone == TRUE) {
        Status = EFI_SUCCESS;
        break;
      }
      MicroSecondDelay (1000);
      Timeout--;
    } while (Timeout > 0);

    if (Timeout == 0) {
      Status = EFI_TIMEOUT;
      THC_LOCAL_DEBUG(L"ThcProtocol HidGetSetFeature Response Timeout\n")
      DEBUG ((DEBUG_ERROR, "ThcProtocol HidGetSetFeature Response Timeout\n"));
    }
  }

THC_HID_EXIT:
  //
  // Restore Thc Hid state to default
  //
  ThcDev->HidDataAvailable = FALSE;
  ThcDev->HidActive        = FALSE;
  ThcDev->HidBuffer        = NULL;

  return Status;
}

/**
  Performs SetFeature function as described in Human Interface Device specification.

  @param[in]  This       Pointer to instance of protocol.
  @param[in]  Length     Size of the buffer.
  @param[in]  Buffer     On input, contains data to be sent to external device. If timeout is set BIOS expects response for which same buffer is consumed.
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
EFI_STATUS
EFIAPI
HidSetFeature (
  IN THC_PROTOCOL   *This,
  IN UINT32         Length,
  IN OUT UINT8      *Buffer,
  IN UINTN          Timeout
  )
{
  THC_DEV             *ThcDev;
  THC_WRITE_DATA_HDR  WriteData;
  EFI_STATUS          Status;

  ThcDev = THC_CONTEXT_FROM_THC_PROTOCOL (This);

  WriteData.WriteDataType   = SET_FEATURES_DATA;
  WriteData.WriteDataLength = Length;

  Status = HidGetSetFeature (ThcDev, &WriteData, Buffer, Timeout, Length);

  return Status;
}


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
EFI_STATUS
EFIAPI
HidGetFeature (
  IN THC_PROTOCOL  *This,
  IN UINT32        Length,
  IN OUT UINT8     *Buffer,
  IN UINTN         Timeout
  )
{
  THC_DEV             *ThcDev;
  THC_WRITE_DATA_HDR  WriteData;
  EFI_STATUS          Status;

  ThcDev = THC_CONTEXT_FROM_THC_PROTOCOL (This);

  WriteData.WriteDataType   = GET_FEATURES_DATA;
  WriteData.WriteDataLength = Length;

  Status = HidGetSetFeature (ThcDev, &WriteData, Buffer, Timeout, Length);

  return Status;
}


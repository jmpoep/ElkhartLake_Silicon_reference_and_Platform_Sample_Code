/** @file
  BaseEcTcss library implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/
#include <Library/EcLib.h>
#include <Library/EcTcssLib.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>

/**
  USBC EC Timeout Retry Message. Used to send messages to EC with predefined
  timeout and retry times.

  @param[in][out]  DataBuffer
  @param[in]       Command
  @param[in]       Timeout
  @param[in]       RetryTime

  @retval          EFI_SUCCESS       Command success
  @retval          EFI_TIMEOUT       Command timeout
  @retval          EFI_DEVICE_ERROR  Command error
**/
EFI_STATUS
UsbcEcTimeoutRetryMessage (
    IN OUT UINT8   *DataBuffer,
    IN     UINT8   Command,
    IN     UINT32  Timeout,
    IN     UINT32  RetryTime
    )
{
  UINT8  DataSize;
  UINT8  DataBufferIn;
  UINT32 NumRetries;
  EFI_STATUS Status;

  DataSize = 1;
  NumRetries = Timeout / RetryTime;
  DataBufferIn = *DataBuffer;

  DEBUG ((DEBUG_INFO, "\nUsbcEcTimeoutRetryMessage: %x, Timeout: %u, RetryTime: %u\n", Command, Timeout, RetryTime));
  do {
    //
  // Send the command to EC
  //
    Status = EcInterface (EcId0, Command, &DataSize, DataBuffer);

    if (Status != EFI_SUCCESS) {
      return Status;
    }
  //
    // If USB connection status is successful (0x00) or failed (0x02) then return
    // If in progress (0x01) then retry after 10 ms
  //
    if (*DataBuffer == 0x00 || *DataBuffer == 0x02) {
      return EFI_SUCCESS;
    } else if (*DataBuffer == 0x01) {
      *DataBuffer = DataBufferIn;
      MicroSecondDelay(RetryTime * 1000);
      NumRetries--;
    } else {
      return EFI_DEVICE_ERROR;
    }

  } while (NumRetries != 0);

  DEBUG ((DEBUG_INFO, "\nUsbcEcTimeoutRetryMessage %x timed out\n", Command));
  return EFI_TIMEOUT;
}

/**
  USBC IOM Ready Notify

  @param[in][out]  DataBuffer

  @retval          EFI_SUCCESS       Command success
  @retval          EFI_DEVICE_ERROR  Command error
**/
EFI_STATUS
UsbcIomReadyNotify (
  IN OUT UINT8     *DataBuffer
  )
{
  UINT8  DataSize;
  DataSize = 1;
  return (EcInterface (EcId0, EC_C_USBC_IOM_READY_NOTIFY, &DataSize, DataBuffer));
}

/**
  USBC Get USB Connection Status

  @param[in][out]  DataBuffer
  @param[in]       Timeout

  @retval          EFI_SUCCESS       Command success
  @retval          EFI_TIMEOUT       Command timeout
  @retval          EFI_DEVICE_ERROR  Command error
**/
EFI_STATUS
UsbcGetUsbConnStatus (
  IN OUT UINT8     *DataBuffer,
  IN     UINT32    Timeout
  )
{
  UINT32 RetryTime;
  //
  // Retry after 10ms
  //
  RetryTime = EC_TCSS_RETRY_TIME_GET_USB_CONN_STATUS;
  return (UsbcEcTimeoutRetryMessage(DataBuffer, EC_C_USBC_GET_USB_CONN_STATUS, Timeout, RetryTime));
}

/**
  USBC Sx Entry Wait

  @param[in][out]  DataBuffer
  @param[in]       Timeout

  @retval          EFI_SUCCESS       Command success
  @retval          EFI_TIMEOUT       Command timeout
  @retval          EFI_DEVICE_ERROR  Command error
**/
EFI_STATUS
UsbcSxEntry (
  IN OUT UINT8     *DataBuffer,
  IN     UINT32    Timeout
  )
{
  UINT32 RetryTime;
  //
  // Retry after 100ms
  //
  RetryTime = EC_TCSS_RETRY_TIME_SX_ENTRY_WAIT;
  return (UsbcEcTimeoutRetryMessage(DataBuffer, EC_C_USBC_SX_ENTRY_WAIT, Timeout, RetryTime));
}


/**
  USBC Sx Exit Wait

  @param[out]     DataBuffer
  @param[in]      Timeout

  @retval         EFI_SUCCESS         Command success
  @retval         EFI_TIMEOUT       Command timeout
  @retval         EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
UsbcSxExit (
  OUT    UINT8     *DataBuffer,
  IN     UINT32    Timeout
  )
{
  UINT32 RetryTime;
  //
  // Retry after 100ms
  //
  RetryTime = EC_TCSS_RETRY_TIME_SX_EXIT_WAIT;
  return (UsbcEcTimeoutRetryMessage(DataBuffer, EC_C_USBC_SX_EXIT_WAIT, Timeout, RetryTime));
}


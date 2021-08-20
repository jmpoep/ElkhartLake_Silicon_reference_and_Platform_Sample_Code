/** @file
  Base EC library implementation for H/W layer.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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

#include <Base.h>
#include <Uefi.h>
#include <Library/EcHwLib.h>
#include <Library/EcLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/DebugLib.h>

#ifndef STALL_ONE_MICRO_SECOND
#define STALL_ONE_MICRO_SECOND  1
#endif
#ifndef STALL_ONE_MILLI_SECOND
#define STALL_ONE_MILLI_SECOND  1000
#endif

#ifndef EC_INIT_TIME_OUT
#define EC_INIT_TIME_OUT       0x200
#endif

EFI_STATUS
EcId0Interface (
  IN UINT8                     Command,
  IN OUT UINT8                 *DataSize,
  IN OUT UINT8                 *DataBuffer
  );

//
// Function implementations
//
/**
  Sends command to EC.

  @param[in] Command           Command byte to send
  @param[in] Timeout           Timeout in microseonds

  @retval    EFI_SUCCESS       Command success
  @retval    EFI_DEVICE_ERROR  Command error
  @retval    EFI_TIMEOUT       Command timeout
**/
EFI_STATUS
SendEcCommandTimeout (
  IN UINT8                  Command,
  IN UINT32                 Timeout
  )
{
  UINTN         Index;
  UINT8         EcStatus;

  Index = 0;
  EcStatus = 0;
  //
  // Wait for EC to be ready (with a timeout)
  //
  ReceiveEcStatus (&EcStatus);
  //
  // Check if output buffer bit(OBF) is set.
  // Read and discard the output buffer data so that next BIOS-EC cmd is in sync
  // OBF is cleared by h/w after all data in output buffer is read by BIOS.
  //
  while (((EcStatus & EC_S_OBF) != 0) && (Index < Timeout)) {
    //
    // Read EC data
    //
    MicroSecondDelay (10 * STALL_ONE_MICRO_SECOND);
    IoRead8 (EC_D_PORT);
    ReceiveEcStatus (&EcStatus);
    Index+=10;
  }

  if (Index >= Timeout) {
    return EFI_TIMEOUT;
  }

  Index = 0;

  while (((EcStatus & EC_S_IBF) != 0) && (Index < Timeout)) {
    MicroSecondDelay (10 * STALL_ONE_MICRO_SECOND);
    ReceiveEcStatus (&EcStatus);
    Index+=10;
  }

  if (Index >= Timeout) {
    return EFI_TIMEOUT;
  }

  //Printing EC Command Sent
  DEBUG ((DEBUG_INFO, "Sending EC Command: %02X\n", Command));

  //
  // Send the EC command
  //
  IoWrite8 (EC_C_PORT, Command);

  DEBUG ((DEBUG_INFO, "SendEcDataTimeout sent %x \n", Command));

  return EFI_SUCCESS;
}


/**
  Sends command to EC.

  @param[in] Command           Command byte to send

  @retval    EFI_SUCCESS       Command success
  @retval    EFI_DEVICE_ERROR  Command error
  @retval    EFI_TIMEOUT       Command timeout
**/
EFI_STATUS
SendEcCommand (
  IN UINT8                  Command
  )
{
  return SendEcCommandTimeout (Command, EC_TIME_OUT);
}


/**
  Receives status from EC.

  @param[out] EcStatus       Status byte to receive

  @retval     EFI_SUCCESS
  @retval     EFI_DEVICE_ERROR
**/
EFI_STATUS
ReceiveEcStatus (
  OUT UINT8                 *EcStatus
  )
{
  //
  // Read and return the status
  //
  *EcStatus = IoRead8 (EC_C_PORT);

  return EFI_SUCCESS;
}


/**
  Sends data to EC.

  @param[in] Data          Data byte to send

  @retval    EFI_SUCCESS
  @retval    EFI_DEVICE_ERROR
**/
EFI_STATUS
SendEcData (
  IN UINT8                 Data
  )
{
  UINTN         Index;
  UINT8         EcStatus;

  Index = 0;

  //
  // Wait for EC to be ready (with a timeout)
  //
  ReceiveEcStatus (&EcStatus);
  while (((EcStatus & EC_S_IBF) != 0) && (Index < EC_TIME_OUT)) {
    MicroSecondDelay (15);
    ReceiveEcStatus (&EcStatus);
    Index++;
  }
  if (Index >= EC_TIME_OUT) {
    return EFI_DEVICE_ERROR;
  }

  //
  //Printing EC Data Sent
  //
  DEBUG ((DEBUG_INFO, "Sending EC Data: %02X\n", Data));

  //
  // Send the data and return
  //
  IoWrite8 (EC_D_PORT, Data);

  DEBUG ((DEBUG_INFO, "EC Data: %02X sent\n", Data));
  return EFI_SUCCESS;
}


/**
  Receives data from EC.

  @param[out] Data              Data byte received
  @param[in]  Timeout           Timeout in microseonds

  @retval     EFI_SUCCESS       Read success
  @retval     EFI_DEVICE_ERROR  Read error
  @retval     EFI_TIMEOUT       Command timeout
--*/
EFI_STATUS
ReceiveEcDataTimeout (
  OUT UINT8                  *Data,
  IN  UINT32                 Timeout
 )
{
  UINTN         Index;
  UINT8         EcStatus;

  Index = 0;

  //
  // Wait for EC to be ready (with a timeout)
  //
  ReceiveEcStatus (&EcStatus);
  while (((EcStatus & EC_S_OBF) == 0) && (Index < Timeout)) {
    MicroSecondDelay (15 * STALL_ONE_MICRO_SECOND);
    ReceiveEcStatus (&EcStatus);
    Index++;
  }
  DEBUG ((DEBUG_INFO, "ReceiveEcDataTimeout Read %x \n",EcStatus));

  if (Index >= Timeout) {
    return EFI_TIMEOUT;
  }
  //
  // Read EC data and return
  //
  *Data = IoRead8 (EC_D_PORT);

  //Printing EC Data Received
  DEBUG ((DEBUG_INFO, "Receiving EC Data: %02X\n", *Data));

  return EFI_SUCCESS;
}
/**
  Receives data from EC.

  @param[out] Data              Data byte received

  @retval     EFI_SUCCESS       Read success
  @retval     EFI_DEVICE_ERROR  Read error
  @retval     EFI_TIMEOUT       Command timeout
**/
EFI_STATUS
ReceiveEcData (
  OUT UINT8                  *Data
 )
{
  return ReceiveEcDataTimeout (Data, EC_TIME_OUT);
}

/**
  Detect EC

  @param[out] EcMajorRevision
  @param[out] EcMinorRevision

  @retval     TRUE            EC is present on the system.
  @retval     FALSE           EC is NOT present on the system.
**/
BOOLEAN
DetectEc (
  OUT UINT8           *EcMajorRevision,
  OUT UINT8           *EcMinorRevision
  )
{
  EFI_STATUS          Status;
  UINT8               EcDetectionData;
  UINT8               EcStatus;
  BOOLEAN             EcPresent;

  //
  // Send command to detect EC with EC_INIT_TIME_OUT
  // EC_C_SMC_GET_MODE is the first EC command which produces data. Since we expect timeout and need to retry on boards w/o EC power sequencing
  // there is a race condition where BIOS timeouts but EC will receive the command.Since there is no command to flush EC data buffer we retry basing
  // on first byte of response only so we either consume whole response or none of it. This means that after retry we might get two responses in the
  // buffer when race occurs. We recover from this by flushing EC buffer after successfully received first response.
  //
  Status = SendEcCommandTimeout (EC_C_SMC_GET_MODE, EC_INIT_TIME_OUT);
  DEBUG ((DEBUG_INFO, "SendEcCommandTimeOut status %x\n", Status));
  if (Status != EFI_SUCCESS) {
    return FALSE;
  }
  //
  // Check data return from EC with EC_TIME_OUT
  // First data return must be 'K'
  //
  Status = ReceiveEcDataTimeout (&EcDetectionData, EC_TIME_OUT);
  if (Status != EFI_SUCCESS || EcDetectionData != 'K') {
    return FALSE;
  }

  Status = ReceiveEcData (&EcDetectionData);
  if (Status == EFI_SUCCESS && EcDetectionData == 'S') {
    Status = ReceiveEcData (&EcDetectionData);
    if (Status == EFI_SUCCESS && EcDetectionData == 'C') {
      ReceiveEcData (&EcDetectionData);
    }
  }

  //
  // Flush the EC output data buffer
  //
  ReceiveEcStatus (&EcStatus);
  while (EcStatus & EC_S_OBF) {
    IoRead8 (EC_D_PORT);
    ReceiveEcStatus (&EcStatus);
  }

  if (!EFI_ERROR(Status)) {
    EcPresent = TRUE;
  } else {
    EcPresent = FALSE;
  }

  if (EcPresent) {
    Status = SendEcCommand (EC_C_EC_REVISION);
    if (Status == EFI_SUCCESS) {
      Status = ReceiveEcData (EcMajorRevision);
      if (Status == EFI_SUCCESS) {
        Status = ReceiveEcData (EcMinorRevision);
        if (Status == EFI_SUCCESS) {
            DEBUG ((DEBUG_INFO, "+==============================================+\n"));
            DEBUG ((DEBUG_INFO, "| EC Major Revision: %02X  EC Minor Revision: %02X |\n", *EcMajorRevision, *EcMinorRevision));
            DEBUG ((DEBUG_INFO, "+==============================================+\n"));
        }
      }
    }
  }

  return EcPresent;
}

/**

  Initiate EC reset sequence. EC is in Normal Mode.

  @retval  EFI_SUCCESS         Command success
  @retval  EFI_DEVICE_ERROR    Command error
**/
EFI_STATUS
LpcEcResetEcInNormalMode (
  VOID
  )
{
  EFI_STATUS Status;
  UINT8 Data8;
  Status = SendEcCommand(0xFF);
  if(EFI_ERROR(Status)) {
    return Status;
  }
  Status = ReceiveEcData(&Data8);
  if((EFI_ERROR(Status)) || (Data8 != 0xA5)) {
    return EFI_DEVICE_ERROR;
  } else {
    Status = SendEcData(0x5A);
  }
  return Status;
}

/**
  Sends data to the Embedded Controler.
    Four use-cases:
    1.Send command to EC (DataSize and DataBuffer can be NULL)
    2.Send command to EC and send data to EC
    3.Send command to EC and receive data from EC
    4.Send command to EC, send data to EC and receive data from EC

  @param[in]      EcId        Embedded Controller identification - in case there is more then one.
  @param[in]      Interface   Interface used to access the EC HW
  @param[in]      Command     Command value to send to the EC
  @param[in][out] DataSize    Size of data to send to the EC.
                              If the command retuned data - size of buffer returned by the EC.
                              Be aware of the DataSize must euqal to size of DataBuffer and cannot smaller
                              than number of send data or number of receive data, whichever is the grater.
  @param[in][out] DataBuffer  Pointer to the data buffer including data to be sent to the EC.
                              If the command returned data - pointer to the buffer including the data.
                              The buffer size should be the max of receive and transmit data.

  @retval         EFI_SUCCESS Success
  @retval         Other       Failed - EFI_TIMEOUT, EFI_INVALID_PARAMETER, EFI_UNSUPPORTED,
                                       EFI_BUFFER_TOO_SMALL, etc.
**/
EFI_STATUS
EcInterface (
  IN EC_ID                     EcId,
  IN UINT8                     Command,
  IN OUT UINT8                 *DataSize,
  IN OUT UINT8                 *DataBuffer
  )
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;

  if(EcId >= EcIdMax) {
    return EFI_INVALID_PARAMETER;
  }

  switch (EcId) {

    case EcId0:
      DEBUG ((DEBUG_INFO, "SLP S0 Command: %02X\n", Command));
      DEBUG ((DEBUG_INFO, "SLP S0 DataSize: %02X\n", DataSize));
      DEBUG ((DEBUG_INFO, "SLP S0 DataBuffer: %02X\n", DataBuffer));
      Status = EcId0Interface (Command, DataSize, DataBuffer);
      break;

    default:
      Status = EFI_INVALID_PARAMETER;
      break;
  }

  return Status;
}

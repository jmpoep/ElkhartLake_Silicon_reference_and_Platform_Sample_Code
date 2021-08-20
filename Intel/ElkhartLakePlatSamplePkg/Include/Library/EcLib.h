/** @file
  EC library functions and definitions.

  This library provides basic EC interface.

  There may be different libraries for different environments (PEI, BS, RT, SMM).
  Make sure you meet the requirements for the library (protocol dependencies, use
  restrictions, etc).

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


#ifndef _BASE_EC_LIB_H_
#define _BASE_EC_LIB_H_

//
// Include files
//
#include <Base.h>
#include <Uefi.h>
#include "EcCommands.h"
#include <Library/EcHwLib.h>

//
// Function declarations
//
/**
  Detect EC

  @param[out] EcMajorRevision
  @param[out] EcMinorRevision

  @retval     TRUE            EC is present on the system.
  @retval     FALSE           EC is NOT present on the system.
**/

BOOLEAN
DetectEc (
  OUT UINT8            *EcMajorRevision,
  OUT UINT8            *EcMinorRevision
  );

/**

  Initiate EC reset sequence. EC is in Normal Mode.

  @retval  EFI_SUCCESS         Command success
  @retval  EFI_DEVICE_ERROR    Command error
**/

EFI_STATUS
LpcEcResetEcInNormalMode (
  VOID
  );

/**
  Send a command to the Keyboard System Controller.

  @param[in] Command      Command byte to send

  @retval    EFI_SUCCESS  Command success
  @retval    EFI_TIMEOUT  Command timeout
  @retval    Other        Command failed
**/
EFI_STATUS
SendEcCommand (
  IN UINT8   Command
  );


/**
  Sends data to Keyboard System Controller.

  @param[in] Data          Data byte to send

  @retval    EFI_SUCCESS   Success
  @retval    EFI_TIMEOUT   Timeout
  @retval    Other         Failed
**/
EFI_STATUS
SendEcData (
  IN UINT8   Data
  );


/**
  Receives data from Keyboard System Controller.

  @param[out] Data          Data byte received

  @retval     EFI_SUCCESS   Read success
  @retval     EFI_TIMEOUT   Read timeout
  @retval     Other         Read failed
**/
EFI_STATUS
ReceiveEcData (
  OUT UINT8   *Data
  );


/**
  Receives status from Keyboard System Controller.

  @param[out] Status       Status byte to receive

  @retval     EFI_SUCCESS  Success
  @retval     Other        Failed
**/
EFI_STATUS
ReceiveEcStatus (
  OUT UINT8   *EcStatus
  );

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
  );

#endif

/** @file
  This library class provides capability to get/set serial port baud rate.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

#ifndef __SERIAL_PORT_PARAMETER_LIB__
#define __SERIAL_PORT_PARAMETER_LIB__

#define STATUS_CODE_USE_RAM        BIT0
#define STATUS_CODE_USE_ISA_SERIAL BIT1
#define STATUS_CODE_USE_USB        BIT2
#define STATUS_CODE_USE_USB3       BIT3
#define STATUS_CODE_USE_SERIALIO   BIT4
#define STATUS_CODE_USE_TRACEHUB   BIT5
#define STATUS_CODE_CMOS_INVALID   BIT6
#define STATUS_CODE_CMOS_VALID     BIT7


/**
  Returns the serial port baud rate.
  
  @return  Baud rate of serial port.

**/
UINT32
EFIAPI
GetSerialPortBaudRate (
  VOID
  );

/**
  Sets the serial port baud rate value.
  
  @param[in] BaudRate     Baud rate value to be set.

  @retval  TRUE           The baud rate of serial port was sucessfully set.
  @retval  FALSE          The baud rate of serial port could not be set.

**/
BOOLEAN
EFIAPI
SetSerialPortBaudRate (
  UINT32        BaudRate
  );

/**
  Returns enabled debug interfaces.
  
  @retval  Enabled debug interfaces bitmask.

**/
UINT8
GetDebugInterface (
  VOID
  );

/**
  Sets debug interfaces.
  
  @param[in] DebugInterface  Debug interfaces to be set.

**/
VOID
SetDebugInterface (
  UINT8 DebugInterface
  );


#endif

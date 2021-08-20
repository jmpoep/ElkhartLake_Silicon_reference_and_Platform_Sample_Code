/**@file

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include "PlatformSetup.h"

#ifndef _PLATFORM_SETUP_KEYBOARD_SETUP_H_
#define _PLATFORM_SETUP_KEYBOARD_SETUP_H_

//
// PS/2 Keyboard Controller registers
//
#define KEYBOARD_8042_DATA_REGISTER     0x60
#define KEYBOARD_8042_STATUS_REGISTER   0x64
#define KEYBOARD_8042_COMMAND_REGISTER  0x64

#define KEYBOARD_STATUS_REGISTER_HAS_OUTPUT_DATA     BIT0        ///< 0 - Output register has no data; 1 - Output register has data
#define KEYBOARD_STATUS_REGISTER_HAS_INPUT_DATA      BIT1        ///< 0 - Input register has no data;  1 - Input register has data
#define KEYBOARD_STATUS_REGISTER_SYSTEM_FLAG         BIT2        ///< Set to 0 after power on reset
#define KEYBOARD_STATUS_REGISTER_INPUT_DATA_TYPE     BIT3        ///< 0 - Data in input register is data; 1 - Data in input register is command
#define KEYBOARD_STATUS_REGISTER_ENABLE_FLAG         BIT4        ///< 0 - Keyboard is disable; 1 - Keyboard is enable
#define KEYBOARD_STATUS_REGISTER_TRANSMIT_TIMEOUT    BIT5        ///< 0 - Transmit is complete without timeout; 1 - Transmit is timeout without complete
#define KEYBOARD_STATUS_REGISTER_RECEIVE_TIMEOUT     BIT6        ///< 0 - Receive is complete without timeout; 1 - Receive is timeout without complete
#define KEYBOARD_STATUS_REGISTER_PARITY              BIT7        ///< 0 - Odd parity; 1 - Even parity

#define KEYBOARD_8048_COMMAND_CLEAR_OUTPUT_DATA             0xF4
#define KEYBOARD_8048_COMMAND_SET_DEFAULT                   0xF6
#define KEYBOARD_8048_COMMAND_RESET                         0xFF
#define KEYBOARD_8048_COMMAND_SELECT_SCAN_CODE_SET          0xF0

#define KEYBOARD_MAX_TRY                256     // 256
#define KEYBOARD_TIMEOUT                65536   // 0.07s
#define KEYBOARD_WAITFORVALUE_TIMEOUT   1000000 // 1s

#define KEYBOARD_8048_RETURN_8042_ACK                       0xFA

#endif

/** @file
  Lpc driver's sio interface.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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
#ifndef _REGISTER_H
#define _REGISTER_H

//
// Define some fixed platform device location information
//
#define LPC_SIO_CONFIG_DEFAULT_PORT 0x2E
#define LPC_SIO_INDEX_DEFAULT_PORT  0x2E
#define SIO_BASE_ADDRESS                          0x0680

//
// Port address for SMSC LPC 1007 at Calpella platform
//
#define SIO_CONFIG_PORT LPC_SIO_CONFIG_DEFAULT_PORT
#define SIO_INDEX_PORT  LPC_SIO_INDEX_DEFAULT_PORT
#define SIO_DATA_PORT   SIO_INDEX_PORT + 1

//
// Global register in SMSC LPC 1007
//
#define REG_VALID_CONFIG_CYCLE              0x00
#define REG_CR_LOCK                         0x01
#define REG_UARTS_POWER_CONTROL             0x02
#define REG_UART_MISC                       0x04
#define REG_AUTO_POWER_MGT                  0x07
#define REG_IR_MUX                          0x0A
#define REG_UART_MODE                       0x0C
#define REG_DEVICE_ID                       0x0D
#define REG_UART1_FCR_SHADOW                0x15
#define REG_UART2_FCR_SHADOW                0x16

#define REG_UART1_BASE_ADDRESS              0x24
#define REG_UART2_BASE_ADDRESS              0x25
#define REG_UART_IRQ_SELECT                 0x28
#define REG_IRQIN1_HPMODE_SIRQ_CLKRUN_EN    0x29
#define REG_IRQIN2                          0x2A
#define REG_SCE_BASE_ADDRESS                0x2B
#define REG_SCE_DMA_SELECT                  0x2C
#define REG_RUNTIME_REGISTER_BLOCK_ADDRESS  0x30
#define REG_GPIO_DIRECTION_REG1             0x31
#define REG_GPIO_POLARITY_REG1              0x32
#define REG_GPIO_OUTPUT_TYPE_REG1           0x33
#define REG_ALTERNATE_FUNCTION_REG          0x34
#define REG_GPIO_DIRECTION_REG3             0x35
#define REG_GPIO_POLARITY_REG3              0x36
#define REG_GPIO_PULLUP_REG3                0x37
#define REG_GPIO_PULLUP_REG1                0x38
#define REG_GPIO_OUTPUT_TYPE_REG3           0x39
#define REG_LPC_ACTIVATE_POWER              0x3A
#define REG_LPC_DOCKING_BASE_ADDR_HIGH      0x3B
#define REG_LPC_DOCKING_BASE_ADDR_LOW       0x3C
#define EFI_SIO_OR                          0x00
#define EFI_SIO_AND                         0x01


//
// Register for COM1
//
#define SERIAL_MODE 0xF0

//
// Register for Parallel Port
//
#define PARALLEL_MODE 0xF8

//
// Bit definition for parallel mode
//
#define PARALLEL_MODE_MASK    0x0F
#define PARALLEL_MODE_SPP     0x01
#define PARALLEL_MODE_EPP     0x02
#define PARALLEL_MODE_ECP     0x04
#define PARALLEL_MODE_PRINTER 0x08

//
// Register for Keyboard Controller
//
#define KRESET_GATE20_SELECT            0xF0

#define LPC_RUNTIME_REGISTER_BLOCK_BASE SIO_BASE_ADDRESS
#define LPC_SERIAL_PORT1_BASE           0x3F8
#define LPC_SERIAL_PORT2_BASE           0x2F8
#define LPC_SCE_PORT_BASE               0x7E8

//
// Default Base Addresses for logical devices
//
#define GPIO_BASE       0x0680
#define PWR_CNTRL_BASE  (GPIO_BASE + 0x40)
#define FAN_CNTRL_BASE  (PWR_CNTRL_BASE + 0x20)

#endif

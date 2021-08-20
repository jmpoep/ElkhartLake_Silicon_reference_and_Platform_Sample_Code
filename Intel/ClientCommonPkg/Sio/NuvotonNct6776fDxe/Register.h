/** @file
  Nuvoton Lpc Super I/O register definitions

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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
#define DESKTOP_LPC_SIO_CONFIG_DEFAULT_PORT 0x2E
#define DESKTOP_LPC_SIO_INDEX_DEFAULT_PORT  0x2E
#define DESKTOP_LPC_SIO_DATA_DEFAULT_PORT   0x2F

//
// Port address for LPC
//
#define SIO_CONFIG_PORT    DESKTOP_LPC_SIO_CONFIG_DEFAULT_PORT
#define SIO_INDEX_PORT     DESKTOP_LPC_SIO_INDEX_DEFAULT_PORT
#define SIO_DATA_PORT      DESKTOP_LPC_SIO_DATA_DEFAULT_PORT

//
// logical device in LPC
//
#define SIO_FLOPPY                      0x00
#define SIO_PARA                        0x01
#define SIO_COM1                        0x02
#define SIO_COM2                        0x03
#define SIO_KYBD_MOUSE                  0x05
#define SIO_CIR                         0x06
#define SIO_POWER_CONTROL               0x04
#define SIO_GPIO_GROUP1                 0x07
#define SIO_GPIO_GROUP2                 0x08
#define SIO_GPIO_GROUP3                 0x09
#define SIO_ACPI                        0x0A
#define SIO_HWMON                       0x0B
#define SIO_VID                         0x0D
#define SIO_CIRWAKEUP                   0x0E
#define SIO_GPIO_GROUP4                 0x0F
#define SIO_SVID                        0x14
#define SIO_DEEP_SLEEP                  0x16
#define SIO_GPIO_GROUP5                 0x17

//
// Global register in LPC
//
#define REG_CONFIG_CONTROL              0x02
#define REG_SIO_LOGICAL_DEVICE          0x07
#define REG_IRQ_TYPE_SELECT_1           0x10
#define REG_IRQ_TYPE_SELECT_2           0x11
#define REG_IRQ_POLARITY_SELECT_1       0x12
#define REG_IRQ_POLARITY_SELECT_2       0x13
#define REG_SIO_PIN_FUNCTION_1          0x1A
#define REG_SIO_PIN_FUNCTION_2          0x1B
#define REG_SIO_PIN_FUNCTION_3          0x1C
#define REG_DEVICE_ID                   0x20
#define REG_DEVICE_REV                  0x21
#define REG_POWER_CONTROL               0x22
#define REG_SIO_PIN_FUNCTION_4          0x24
#define REG_TRI_STATE_CONTROL           0x25
#define REG_GLOBAL_OPTIONS              0x26
#define REG_SIO_PIN_FUNCTION_5          0x27
#define REG_SIO_PIN_FUNCTION_6          0x2A
#define REG_SIO_PIN_FUNCTION_7          0x2B
#define REG_SIO_PIN_FUNCTION_8          0x2C
#define REG_SIO_PIN_FUNCTION_9          0x2D

#define R_SIO_ACTIVATE                  0x30
#define R_SIO_BASE_ADDRESS_HIGH         0x60
#define R_SIO_BASE_ADDRESS_LOW          0x61
#define R_SIO_BASE_ADDRESS_HIGH2        0x62
#define R_SIO_BASE_ADDRESS_LOW2         0x63
#define R_SIO_PRIMARY_INTERRUPT_SELECT  0x70
#define R_SIO_SECOND_INTERRUPT_SELECT   0x72
#define R_SIO_DMA_CHANNEL_SELECT        0x74

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
#define KRESET_GATE20_SELECT  0xF0

//Registers for Nuvoton GPIO
#define REG_DIRECTION_GPIO7             0xE0
#define REG_DATA_GPIO7                  0xE1
#define REG_INVERTION_GPIO7             0xE2
#define REG_DIRECTION_GPIO8             0xE4
#define REG_DATA_GPIO8                  0xE5
#define REG_INVERTION_GPIO8             0xE6
#define REG_DIRECTION_GPIO9             0xE8
#define REG_DATA_GPIO9                  0xE9
#define REG_INVERTION_GPIO9             0xEA
#define REG_GPIO7_MULTIFUNCTION         0xEC
#define REG_GPIO8_MULTIFUNCTION         0xED
#define REG_GPIO9_MULTIFUNCTION         0xEE
#define REG_DIRECTION_GPIO6             0xF4
#define REG_DATA_GPIO6                  0xF5
#define REG_INVERTION_GPIO6             0xF6
#define REG_GPIO6_MULTIFUNCTION         0xF8

#define REG_DIRECTION_GPIO2             0xE0
#define REG_DATA_GPIO2                  0xE1
#define REG_INVERTION_GPIO2             0xE2
#define REG_DIRECTION_GPIO3             0xE4
#define REG_DATA_GPIO3                  0xE5
#define REG_INVERTION_GPIO3             0xE6
#define REG_GPIO2_MULTIFUNCTION         0xE9
#define REG_GPIO3_MULTIFUNCTION         0xEA
#define REG_GPIO5_MULTIFUNCTION         0xEB
#define REG_GPIO4_MULTIFUNCTION         0xEE
#define REG_DIRECTION_GPIO4             0xF0
#define REG_DATA_GPIO4                  0xF1
#define REG_INVERTION_GPIO4             0xF2
#define REG_DIRECTION_GPIO5             0xF4
#define REG_DATA_GPIO5                  0xF5
#define REG_INVERTION_GPIO5             0xF6
#define REG_INPUT_DETECT_TYPE           0xFE

//
// Hardware Monitor registers
//
#define HWMON_BANK_SELECT               0x4e

#endif // _REGISTER_H

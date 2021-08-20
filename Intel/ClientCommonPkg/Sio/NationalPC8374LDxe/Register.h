/** @file
  Smsc Lpc Super I/O register definitions

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
#define SIO_FLOPPY        0x0
#define SIO_PARA          0x1
#define SIO_COM2          0x2
#define SIO_COM1          0x3
#define SIO_MOUSE         0x5
#define SIO_KYBD          0x6
#define SIO_POWER_CONTROL 0x4
#define SIO_GPIO          0x7
#define SIO_FAN           0x9

//
// Global register in LPC
//
#define REG_CONFIG_CONTROL  0x02
#define R_SIO_LOGICAL_DEVICE  0x07
#define REG_DEVICE_ID       0x20
#define REG_DEVICE_REV      0x21
#define REG_POWER_CONTROL   0x22
#define SIO_FLOPPY_POWER    0x01
#define SIO_PARA_POWER      0x08
#define SIO_COM1_POWER      0x10
#define SIO_COM2_POWER      0x20
//
// #define REG_POWER_MGMT           0x23
//
#define REG_OSC                   0x24
#define REG_CONFIGPORT_LOW        0x26
#define REG_CONFIGPORT_HIGH       0x27

#define SMSC_TEST5                0x2C
#define NSC_SIOCF2                0x22
#define NSC_SIOCF4                0x24
#define NSC_CLOCKCF               0x29
#define NSC_HMSMBCFG              0x2A
#define NSC_CLOCKSELECT           0x2D

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

//Registers for National GPIO
#define NSC_GPSEL                   0xF0
#define NSC_GPCFG1                  0xF1
#define NSC_GPMODE                  0xF8
//
// Default Base Addresses for logical devices
//
#define GPIO_BASE       0x0680
#define PWR_CNTRL_BASE  (GPIO_BASE + 0x40)
#define FAN_CNTRL_BASE  (PWR_CNTRL_BASE + 0x20)

// Power Control Runtime registers
#define SIO_PME_STS   0x00
#define SIO_PME_EN    0x04
#define SIO_PME_STS3  0x08
#define SIO_PME_STS2  0x09
#define SIO_PME_STS1  0x0A
#define SIO_PME_EN3   0x0C
#define SIO_PME_EN2   0x0D
#define SIO_PME_EN1   0x0E
#define SIO_LED       0x10
#endif

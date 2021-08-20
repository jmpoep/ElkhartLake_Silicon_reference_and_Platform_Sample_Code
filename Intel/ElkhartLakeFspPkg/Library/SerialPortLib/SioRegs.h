/** @file
  Lpc driver's sio interface for National SIO PC87423 and 427
  Copied from Platform\IntelEpg\Common\Chipset\Sio\PilotIIPc8374\Dxe\SioRegs.h

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification
**/

#ifndef _SIO_REG_H_
#define _SIO_REG_H_

#define REG_LOGICAL_DEVICE        0x07
#define ACTIVATE                  0x30

#define BASE_ADDRESS_HIGH0        0x60
#define BASE_ADDRESS_LOW0         0x61
#define BASE_ADDRESS_HIGH1        0x62
#define BASE_ADDRESS_LOW1         0x63
#define BASE_ADDRESS_HIGH2        0x64
#define BASE_ADDRESS_LOW2         0x65
#define BASE_ADDRESS_HIGH3        0x66
#define BASE_ADDRESS_LOW3         0x67
#define PRIMARY_INTERRUPT_SELECT  0x70
#define WAKEUP_ON_IRQ_EN          0x70
#define INTERRUPT_TYPE            0x71
#define DMA_CHANNEL_SELECT0       0x74
#define DMA_CHANNEL_SELECT1       0x75

//
// Port address for PILOT-II
//
#define PILOTII_CHIP_ID         0x02
#define PILOTII_SIO_INDEX_PORT  0x04E
#define PILOTII_SIO_DATA_PORT   (PILOTII_SIO_INDEX_PORT+1)

#define PILOTII_SIO_UNLOCK      0x5A
#define PILOTII_SIO_LOCK        0xA5

//
// logical device in PILOT-II
//
#define PILOTII_SIO_PSR     0x00
#define PILOTII_SIO_COM2    0x01
#define PILOTII_SIO_COM1    0x02
#define PILOTII_SIO_SWCPII  0x03
#define PILOTII_SIO_GPIO    0x04
#define PILOTII_SIO_WDT     0x05
#define PILOTII_SIO_KCS1    0x06
#define PILOTII_SIO_KCS2    0x07
#define PILOTII_SIO_KCS3    0x08
#define PILOTII_SIO_KCS4    0x09
#define PILOTII_SIO_KCS5    0x0A
#define PILOTII_SIO_BT      0x0B
#define PILOTII_SIO_SMIC    0x0C
#define PILOTII_SIO_MAILBOX 0x0D
#define PILOTII_SIO_RTC     0x0E
#define PILOTII_SIO_SPI     0x0F
#define PILOTII_SIO_TAP     0x10

//
// Regisgers for PilotII
//
#define PILOTII_CHIP_ID_REG               0x20
#define PILOTII_LOGICAL_DEVICE            REG_LOGICAL_DEVICE
#define PILOTII_ACTIVATE                  ACTIVATE
#define PILOTII_BASE_ADDRESS_HIGH0        BASE_ADDRESS_HIGH0
#define PILOTII_BASE_ADDRESS_LOW0         BASE_ADDRESS_LOW0
#define PILOTII_BASE_ADDRESS_HIGH1        BASE_ADDRESS_HIGH1
#define PILOTII_BASE_ADDRESS_LOW1         BASE_ADDRESS_LOW1
#define PILOTII_PRIMARY_INTERRUPT_SELECT  PRIMARY_INTERRUPT_SELECT

#define PILOTII_LOCK        0xA5
#define PILOTII_UNLOCK      0x5A

//
// Port address for PC8374
//
#define PC8374_SIO_INDEX_PORT  0x02E
#define PC8374_SIO_DATA_PORT   (PC8374_SIO_INDEX_PORT+1)

//
// Logical device in PC8374
//
#define PC8374_SIO_FLOPPY  0x00
#define PC8374_SIO_PARA    0x01
#define PC8374_SIO_COM2    0x02
#define PC8374_SIO_COM1    0x03
#define PC8374_SIO_MOUSE   0x05
#define PC8374_SIO_KYBD    0x06
#define PC8374_SIO_GPIO    0x07

//
// Registers specific for PC8374
//
#define PC8374_CLOCK_SELECT  0x2D
#define PC8374_CLOCK_CONFIG  0x29

//
// Registers for PC8374
//
#define PC8374_LOGICAL_DEVICE            REG_LOGICAL_DEVICE
#define PC8374_ACTIVATE                  ACTIVATE
#define PC8374_BASE_ADDRESS_HIGH0        BASE_ADDRESS_HIGH0
#define PC8374_BASE_ADDRESS_LOW0         BASE_ADDRESS_LOW0
#define PC8374_PRIMARY_INTERRUPT_SELECT  PRIMARY_INTERRUPT_SELECT
#define PC8374_DMA_CHANNEL_SELECT        DMA_CHANNEL_SELECT0

#define PC87427_SERVERIO_CNF2           0x22

//
// Pilot II Mailbox Data Register definitions
//
#define MBDAT00_OFFSET                  0x00
#define MBDAT01_OFFSET                  0x01
#define MBDAT02_OFFSET                  0x02
#define MBDAT03_OFFSET                  0x03
#define MBDAT04_OFFSET                  0x04
#define MBDAT05_OFFSET                  0x05
#define MBDAT06_OFFSET                  0x06
#define MBDAT07_OFFSET                  0x07
#define MBDAT08_OFFSET                  0x08
#define MBDAT09_OFFSET                  0x09
#define MBDAT10_OFFSET                  0x0A
#define MBDAT11_OFFSET                  0x0B
#define MBDAT12_OFFSET                  0x0C
#define MBDAT13_OFFSET                  0x0D
#define MBDAT14_OFFSET                  0x0E
#define MBDAT15_OFFSET                  0x0F
#define MBST0_OFFSET                    0x10
#define MBST1_OFFSET                    0x11

//
// If both are there, use the default one
//
#define  PILOTII_EXIST    BIT0
#define  PC8374_EXIST     BIT1
#define  DEFAULT_SIO      PILOTII_EXIST

#define IPMI_DEFAULT_SMM_IO_BASE        0xca4
#define PILOTII_MAILBOX_BASE_ADDRESS    0x0600

#endif

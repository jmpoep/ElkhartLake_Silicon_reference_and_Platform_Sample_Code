/** @file
  Register names for Serial IO UART Controllers

  Conventions:

  - Register definition format:
    Prefix_[GenerationName]_[ComponentName]_SubsystemName_RegisterSpace_RegisterName
  - Prefix:
    Definitions beginning with "R_" are registers
    Definitions beginning with "B_" are bits within registers
    Definitions beginning with "V_" are meaningful values within the bits
    Definitions beginning with "S_" are register size
    Definitions beginning with "N_" are the bit position
  - [GenerationName]:
    Three letter acronym of the generation is used (e.g. SKL,KBL,CNL etc.).
    Register name without GenerationName applies to all generations.
  - [ComponentName]:
    This field indicates the component name that the register belongs to (e.g. PCH, SA etc.)
    Register name without ComponentName applies to all components.
    Register that is specific to -H denoted by "_PCH_H_" in component name.
    Register that is specific to -LP denoted by "_PCH_LP_" in component name.
  - SubsystemName:
    This field indicates the subsystem name of the component that the register belongs to
    (e.g. PCIE, USB, SATA, GPIO, PMC etc.).
  - RegisterSpace:
    MEM - MMIO space register of subsystem.
    IO  - IO space register of subsystem.
    PCR - Private configuration register of subsystem.
    CFG - PCI configuration space register of subsystem.
  - RegisterName:
    Full register name.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#ifndef _SERIAL_IO_UART_REGS_H_
#define _SERIAL_IO_UART_REGS_H_

//
//  MMIO
//
#define R_PCH_SERIAL_IO_8BIT_UART_RXBUF      0x00
#define R_PCH_SERIAL_IO_8BIT_UART_TXBUF      0x00
#define R_PCH_SERIAL_IO_8BIT_UART_BAUD_LOW   0x00

#define R_PCH_SERIAL_IO_8BIT_UART_BAUD_HIGH  0x01

#define R_PCH_SERIAL_IO_8BIT_UART_FCR        0x02
#define B_PCH_SERIAL_IO_UART_FCR_FCR         BIT0

#define R_PCH_SERIAL_IO_8BIT_UART_IIR        0x02
#define B_PCH_SERIAL_IO_UART_IIR_FIFOSE      (BIT7 | BIT6)

#define R_PCH_SERIAL_IO_8BIT_UART_LCR        0x03
#define B_PCH_SERIAL_IO_UART_LCR_DLAB        BIT7

#define R_PCH_SERIAL_IO_8BIT_UART_MCR        0x04
#define B_PCH_SERIAL_IO_UART_MCR_AFCE        BIT5
#define B_PCH_SERIAL_IO_UART_MCR_RTS         BIT1
#define B_PCH_SERIAL_IO_UART_MCR_DTRC        BIT0

#define R_PCH_SERIAL_IO_8BIT_UART_LSR        0x05
#define B_PCH_SERIAL_IO_UART_LSR_TEMT        BIT6
#define B_PCH_SERIAL_IO_UART_LSR_TXRDY       BIT5
#define B_PCH_SERIAL_IO_UART_LSR_BI          BIT4
#define B_PCH_SERIAL_IO_UART_LSR_RXDA        BIT0

#define R_PCH_SERIAL_IO_8BIT_UART_MSR        0x06
#define B_PCH_SERIAL_IO_UART_MSR_DCD         BIT7
#define B_PCH_SERIAL_IO_UART_MSR_RI          BIT6
#define B_PCH_SERIAL_IO_UART_MSR_DSR         BIT5
#define B_PCH_SERIAL_IO_UART_MSR_CTS         BIT4

#define R_PCH_SERIAL_IO_8BIT_UART_USR        0x1F
#define B_PCH_SERIAL_IO_UART_USR_TFNF        BIT1

#define R_PCH_SERIAL_IO_32BIT_UART_CTR       0xFC //Component Type Register contains identification code
#define UART_COMPONENT_IDENTIFICATION_CODE   0x44570110

//
//  General Purpose
//
#define R_SERIAL_IO_PCR_GPPRVRW7                    0x618
#define B_SERIAL_IO_PCR_GPPRVRW7_UART0_BYTE_ADDR_EN BIT0
#define B_SERIAL_IO_PCR_GPPRVRW7_UART1_BYTE_ADDR_EN BIT1
#define B_SERIAL_IO_PCR_GPPRVRW7_UART2_BYTE_ADDR_EN BIT2

#define R_SERIAL_IO_MEM_PPR_RESETS_8BIT             0x81

#endif // _SERIAL_IO_UART_REGS_H_

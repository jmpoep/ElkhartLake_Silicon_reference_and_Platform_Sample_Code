/** @file
  Device IDs for Serial IO Controllers for EHL PCH

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
    Register that is specific to -N denoted by "_PCH_N_" in component name.
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
  Copyright 2019 Intel Corporation.

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
#ifndef _SERIAL_IO_REGS_VER3_H_
#define _SERIAL_IO_REGS_VER3_H_

#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_I2C0     0x200
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_I2C1     0x204
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_I2C2     0x208
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_I2C3     0x20C
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_I2C4     0x210
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_I2C5     0x214
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_I2C6     0x218
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_I2C7     0x21C

#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_SPI0     0x23C
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_SPI1     0x240
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_SPI2     0x244

#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_UART0    0x220
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_UART1    0x224
#define R_VER3_SERIAL_IO_PCR_PCICFGCTRL_UART2    0x228

//
//  Serial IO I2C0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C0            21
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C0          0

#define V_VER3_SERIAL_IO_CFG_I2C0_DEVICE_ID             0x4B78

//
//  Serial IO I2C1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C1            21
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C1          1

#define V_VER3_SERIAL_IO_CFG_I2C1_DEVICE_ID             0x4B79

//
//  Serial IO I2C2 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C2            21
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C2          2

#define V_VER3_SERIAL_IO_CFG_I2C2_DEVICE_ID             0x4B7A

//
//  Serial IO I2C3 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C3            21
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C3          3

#define V_VER3_SERIAL_IO_CFG_I2C3_DEVICE_ID             0x4B7B

//
//  Serial IO I2C4 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C4            25
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C4          0

#define V_VER3_SERIAL_IO_CFG_I2C4_DEVICE_ID             0x4B4B

//
//  Serial IO I2C5 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C5            25
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C5          1

#define V_VER3_SERIAL_IO_CFG_I2C5_DEVICE_ID             0x4B4C

//
//  Serial IO I2C6 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C6            16
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C6          0

#define V_VER3_SERIAL_IO_CFG_I2C6_DEVICE_ID             0x4B44

//
//  Serial IO I2C7 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_I2C7            16
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_I2C7          1

#define V_VER3_SERIAL_IO_CFG_I2C7_DEVICE_ID             0x4B45

//
//  Serial IO SPI0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI0            30
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI0          2

#define V_VER3_SERIAL_IO_CFG_SPI0_DEVICE_ID             0x4B2A

//
//  Serial IO SPI1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI1            30
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI1          3

#define V_VER3_SERIAL_IO_CFG_SPI1_DEVICE_ID             0x4B2B

//
//  Serial IO SPI2 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_SPI2            18
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_SPI2          0

#define V_VER3_SERIAL_IO_CFG_SPI2_DEVICE_ID             0x4B37

//
//  Serial IO UART0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART0           30
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART0         0

#define V_VER3_SERIAL_IO_CFG_UART0_DEVICE_ID            0x4B28

//
//  Serial IO UART1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART1           30
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART1         1

#define V_VER3_SERIAL_IO_CFG_UART1_DEVICE_ID            0x4B29

//
//  Serial IO UART2 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_SERIAL_IO_UART2           25
#define PCI_FUNCTION_NUMBER_PCH_SERIAL_IO_UART2         2

#define V_VER3_SERIAL_IO_CFG_UART2_DEVICE_ID            0x4B4D

#endif //_SERIAL_IO_REGS_VER3_H_

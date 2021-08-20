/** @file
  Register names for PCH Integrated Sensor Hub (ISH3.0)

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
  Copyright 2014 - 2018 Intel Corporation.

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
#ifndef _PCH_REGS_ISH_H_
#define _PCH_REGS_ISH_H_

//
// ISH Controller Registers
//
// ICL-PCH D18:F0
#define PCI_DEVICE_NUMBER_PCH_ISH             18
#define PCI_FUNCTION_NUMBER_PCH_ISH           0

#define V_ISH_CFG_DEVICE_ID                   0x9DFC

// PCI Configuration Space Registers
#define R_ISH_CFG_BAR0_LOW                    0x10
#define R_ISH_CFG_BAR0_HIGH                   0x14
#define V_ISH_CFG_BAR0_SIZE                   0x100000
#define N_ISH_CFG_BAR0_ALIGNMENT              20
#define R_ISH_CFG_BAR1_LOW                    0x18
#define R_ISH_CFG_BAR1_HIGH                   0x1C
#define V_ISH_CFG_BAR1_SIZE                   0x1000
#define N_ISH_CFG_BAR1_ALIGNMENT              12
#define R_ISH_CFG_D0I3_MAX_PW_ON_LATENCY      0xA0
#define R_ISH_CFG_PCE                         0xA2
#define B_ISH_CFG_PCE_HAE                     BIT5
//
// ISH Private Configuration Space Registers (IOSF2OCP)
// (PID:ISH)
//
#define R_ISH_PCR_PMCTL                   0x1D0                         ///< Power Management
#define R_ISH_PCR_PCICFGCTRL              0x200                         ///< PCI Configuration Control
#define B_ISH_PCR_PCICFGCTR_PCI_IRQ       0x0FF00000                    ///< PCI IRQ number
#define N_ISH_PCR_PCICFGCTR_PCI_IRQ       20
#define B_ISH_PCR_PCICFGCTR_ACPI_IRQ      0x000FF000                    ///< ACPI IRQ number
#define N_ISH_PCR_PCICFGCTR_ACPI_IRQ      12
#define B_ISH_PCR_PCICFGCTR_IPIN1         (BIT11 | BIT10 | BIT9 | BIT8) ///< Interrupt Pin
#define N_ISH_PCR_PCICFGCTR_IPIN1         8
#define B_ISH_PCR_PCICFGCTRL_BAR1DIS      BIT7                          ///< BAR1 Disable
#define R_ISH_PCR_RSCTRL                  0x300                         ///< Root Space Control
#define B_ISH_PCR_RSCTRL_OTHER_RS_US_EN   BIT1

//
// Number of pins used by ISH controllers
//
#define PCH_ISH_PINS_PER_I2C_CONTROLLER               2
#define PCH_ISH_PINS_PER_UART_CONTROLLER              4
#define PCH_ISH_PINS_PER_SPI_CONTROLLER               4



//
// Memory mapped IO space registers
//
#define R_ISH_MEM_FW_STS         0x34       ///< ISH Host Firmware status Register
#define B_ISH_MEM_FW_STS_STATUS  0x0000F000 ///< mask to get fw state bits(12:15)
#define N_ISH_MEM_FW_STS_STATUS  12

#define R_ISH_MEM_HOST_COMM              0x38 ///< Host Communication Register
#define B_ISH_MEM_HOST_COMM_HOST_READY   BIT7 ///< bit corresponds host ready bit in Host Status Register (HOST_COMM)
#define B_ISH_MEM_HOST_COMM_DRIVER_READY BIT1

#define R_ISH_MEM_HOST2ISH_DRBL    0x48  ///< Inbound doorbell register Host to ISH
#define R_ISH_MEM_ISH2HOST_DRBL    0x54  ///< Outbound doorbell register ISH to Host
#define B_ISH_MEM_DRBL_BUSY        BIT31 ///< Busy bit, common for both doorbells

#define R_ISH_MEM_HOST2ISH_MSG     0xE0  ///< HOST to ISH message registers
#define R_ISH_MEM_ISH2HOST_MSG     0x60  ///< ISH to HOST message registers
#define R_ISH_MEM_REMAP2           0x368
#define DRIVER_LOADED_BIT          BIT0
#define R_ISH_MEM_REMAP3           0x36C

#endif

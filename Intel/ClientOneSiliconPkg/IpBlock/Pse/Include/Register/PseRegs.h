/** @file
  Register names for PCH Programmable Service Engine (PSE)

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
#ifndef _PSE_REGS_H_
#define _PSE_REGS_H_

//
//  PSE UART0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_UART0       17
#define PCI_FUNCTION_NUMBER_PCH_PSE_UART0     0

#define PSE_CFG_UART0_DEVICE_ID               0x4B96

//
//  PSE UART1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_UART1       17
#define PCI_FUNCTION_NUMBER_PCH_PSE_UART1     1

#define PSE_CFG_UART1_DEVICE_ID               0x4B97

//
//  PSE UART2 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_UART2       17
#define PCI_FUNCTION_NUMBER_PCH_PSE_UART2     2

#define PSE_CFG_UART2_DEVICE_ID               0x4B98

//
//  PSE UART3 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_UART3       17
#define PCI_FUNCTION_NUMBER_PCH_PSE_UART3     3

#define PSE_CFG_UART3_DEVICE_ID               0x4B99

//
//  PSE UART4 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_UART4       17
#define PCI_FUNCTION_NUMBER_PCH_PSE_UART4     4

#define PSE_CFG_UART4_DEVICE_ID               0x4B9A

//
//  PSE UART5 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_UART5       17
#define PCI_FUNCTION_NUMBER_PCH_PSE_UART5     5

#define PSE_CFG_UART5_DEVICE_ID               0x4B9B

//
//  PSE I2S0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_I2S0        17
#define PCI_FUNCTION_NUMBER_PCH_PSE_I2S0      6

#define PSE_CFG_I2S0_DEVICE_ID                0x4B9C

//
//  PSE I2S1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_I2S1        17
#define PCI_FUNCTION_NUMBER_PCH_PSE_I2S1      7

#define PSE_CFG_I2S1_DEVICE_ID                0x4B9D

//
//  PSE SPI0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_SPI0        19
#define PCI_FUNCTION_NUMBER_PCH_PSE_SPI0      0

#define PSE_CFG_SPI0_DEVICE_ID                0x4B84

//
//  PSE SPI1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_SPI1        19
#define PCI_FUNCTION_NUMBER_PCH_PSE_SPI1      1
#define PSE_CFG_SPI1_DEVICE_ID                0x4B85

//
//  PSE SPI2 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_SPI2        19
#define PCI_FUNCTION_NUMBER_PCH_PSE_SPI2      2

#define PSE_CFG_SPI2_DEVICE_ID                0x4B86

//
//  PSE SPI3 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_SPI3        19
#define PCI_FUNCTION_NUMBER_PCH_PSE_SPI3      3

#define PSE_CFG_SPI3_DEVICE_ID                0x4B87

//
// PSE TGPIO Controller Block Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_GPIO0       19
#define PCI_FUNCTION_NUMBER_PCH_PSE_GPIO0     4

#define V_PSE_GPIO0_CFG_DEVICE_ID             0x4B88

//
// PSE TGPIO Controller Block Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_GPIO1       19
#define PCI_FUNCTION_NUMBER_PCH_PSE_GPIO1     5

#define V_PSE_GPIO1_CFG_DEVICE_ID             0x4B89

//
//  PSE I2C7 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_I2C7        24
#define PCI_FUNCTION_NUMBER_PCH_PSE_I2C7      0

#define PSE_CFG_I2C7_DEVICE_ID                0x4BC0

//
//  PSE CAN0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_CAN0        24
#define PCI_FUNCTION_NUMBER_PCH_PSE_CAN0      1

#define PSE_CFG_CAN0_DEVICE_ID                0x4BC1

//
//  PSE CAN1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_CAN1        24
#define PCI_FUNCTION_NUMBER_PCH_PSE_CAN1      2

#define PSE_CFG_CAN1_DEVICE_ID                0x4BC2

//
//  PSE QEP0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_QEP0        24
#define PCI_FUNCTION_NUMBER_PCH_PSE_QEP0      3

#define PSE_CFG_QEP0_DEVICE_ID                0x4BC3

//
//  PSE QEP1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_QEP1        24
#define PCI_FUNCTION_NUMBER_PCH_PSE_QEP1      4

#define PSE_CFG_QEP1_DEVICE_ID                0x4B81

//
//  PSE QEP2 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_QEP2        24
#define PCI_FUNCTION_NUMBER_PCH_PSE_QEP2      5

#define PSE_CFG_QEP2_DEVICE_ID                0x4B82

//
//  PSE QEP3 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_QEP3        24
#define PCI_FUNCTION_NUMBER_PCH_PSE_QEP3      6

#define PSE_CFG_QEP3_DEVICE_ID                0x4B83

//
//  PSE I2C0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_I2C0        27
#define PCI_FUNCTION_NUMBER_PCH_PSE_I2C0      0

#define PSE_CFG_I2C0_DEVICE_ID                0x4BB9

//
//  PSE I2C1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_I2C1        27
#define PCI_FUNCTION_NUMBER_PCH_PSE_I2C1      1

#define PSE_CFG_I2C1_DEVICE_ID                0x4BBA

//
//  PSE I2C2 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_I2C2        27
#define PCI_FUNCTION_NUMBER_PCH_PSE_I2C2      2

#define PSE_CFG_I2C2_DEVICE_ID                0x4BBB

//
//  PSE I2C3 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_I2C3        27
#define PCI_FUNCTION_NUMBER_PCH_PSE_I2C3      3

#define PSE_CFG_I2C3_DEVICE_ID                0x4BBC

//
//  PSE I2C4 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_I2C4        27
#define PCI_FUNCTION_NUMBER_PCH_PSE_I2C4      4

#define PSE_CFG_I2C4_DEVICE_ID                0x4BBD

//
//  PSE I2C5 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_I2C5        27
#define PCI_FUNCTION_NUMBER_PCH_PSE_I2C5      5

#define PSE_CFG_I2C5_DEVICE_ID                0x4BBE

//
//  PSE I2C6 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_I2C6        27
#define PCI_FUNCTION_NUMBER_PCH_PSE_I2C6      6

#define PSE_CFG_I2C6_DEVICE_ID                0x4BBF

//
// PSE Controller Registers
//
// EHL-PCH D29:F0
#define PCI_DEVICE_NUMBER_PCH_PSE_LH2PSE      29
#define PCI_FUNCTION_NUMBER_PCH_PSE_LH2PSE    0

#define V_PSE_CFG_LH2PSE_DEVICE_ID            0x4BB3

//
//  PSE GBE0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_GBE0        29
#define PCI_FUNCTION_NUMBER_PCH_PSE_GBE0      1

#define PSE_CFG_GBE0_DEVICE_ID                0x4BA2

//
//  PSE GBE1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_GBE1        29
#define PCI_FUNCTION_NUMBER_PCH_PSE_GBE1      2

#define PSE_CFG_GBE1_DEVICE_ID                0x4BB2

//
//  PSE DMA0 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_DMA0        29
#define PCI_FUNCTION_NUMBER_PCH_PSE_DMA0      3

#define PSE_CFG_DMA0_DEVICE_ID                0x4BB4

//
//  PSE DMA1 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_DMA1        29
#define PCI_FUNCTION_NUMBER_PCH_PSE_DMA1      4

#define PSE_CFG_DMA1_DEVICE_ID                0x4BB5

//
//  PSE DMA2 Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_DMA2        29
#define PCI_FUNCTION_NUMBER_PCH_PSE_DMA2      5

#define PSE_CFG_DMA2_DEVICE_ID                0x4BB6

//
//  PSE PWM Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_PWM         29
#define PCI_FUNCTION_NUMBER_PCH_PSE_PWM       6

#define PSE_CFG_PWM_DEVICE_ID                 0x4BB7

//
//  PSE ADC Controller Registers
//
#define PCI_DEVICE_NUMBER_PCH_PSE_ADC         29
#define PCI_FUNCTION_NUMBER_PCH_PSE_ADC       7

#define PSE_CFG_ADC_DEVICE_ID                 0x4BB8

//
// IMR10 is allocated for PSE
//
#define R_IOP_IMR10_ADDRESS_OFFSET            0x7A40
#define R_IOP_IMR10_SIZE_OFFSET               0x7A44

// PSE PCI Configuration Space Registers
#define R_PSE_CFG_BAR0_LOW                    0x10
#define R_PSE_CFG_BAR0_HIGH                   0x14
#define B_PSE_CFG_BAR0_MASK                   0x0FFF
#define V_PSE_CFG_BAR0_SIZE                   0x100000
#define N_PSE_CFG_BAR0_ALIGNMENT              20
#define R_PSE_CFG_BAR1_LOW                    0x18
#define R_PSE_CFG_BAR1_HIGH                   0x1C
#define V_PSE_CFG_BAR1_SIZE                   0x1000
#define N_PSE_CFG_BAR1_ALIGNMENT              12
#define R_PSE_CFG_D0I3_MAX_PW_ON_LATENCY      0xA0
#define R_PSE_CFG_PCE                         0xA2
#define B_PSE_CFG_PCE_HAE                     BIT5

//
// PSE Private Configuration Space Registers (IOSF2OCP)
// (PID:PSE)
//
#define R_PSE_PCR_PMCTL                       0x1D0                         ///< Power Management
#define R_PSE_PCR_PCICFGCTRL                  0x200                         ///< PCI Configuration Control
#define R_PSE_PCR_FPAK_PCICFGCTRL             0x204                         ///< FPAK PCI Configuration Control
#define B_PSE_PCR_PCICFGCTRL_PCI_IRQ          0x0FF00000                    ///< PCI IRQ number
#define N_PSE_PCR_PCICFGCTRL_PCI_IRQ          20
#define B_PSE_PCR_PCICFGCTRL_ACPI_IRQ         0x000FF000                    ///< ACPI IRQ number
#define N_PSE_PCR_PCICFGCTRL_ACPI_IRQ         12
#define B_PSE_PCR_PCICFGCTRL_INT_PIN          (BIT11 | BIT10 | BIT9 | BIT8) ///< Interrupt Pin
#define N_PSE_PCR_PCICFGCTRL_IPIN1            8
#define B_PSE_PCR_PCICFGCTRL_BAR1DIS          BIT7                          ///< BAR1 Disable
#define B_PSE_PCR_PCICFGCTRL_PCI_CFG_DIS      BIT0
#define R_PSE_PCR_RSCTRL                      0x300                         ///< Root Space Control
#define B_PSE_PCR_RSCTRL_OTHER_RS_US_EN       BIT1

//
// Memory mapped IO space registers
//
#define R_PSE_MEM_FW_STS                      0x34       ///< PSE Host Firmware status Register
#define B_PSE_MEM_FW_STS_STATUS               0x0000F000 ///< mask to get fw state bits(12:15)
#define N_PSE_MEM_FW_STS_STATUS               12

#define R_PSE_MEM_HOST_COMM                   0x38       ///< Host Communication Register
#define B_PSE_MEM_HOST_COMM_HOST_READY        BIT7       ///< bit corresponds host ready bit in Host Status Register (HOST_COMM)
#define B_PSE_MEM_HOST_COMM_DRIVER_READY      BIT1

#define R_PSE_MEM_HOST2PSE_DRBL               0x48       ///< Inbound doorbell register Host to PSE
#define R_PSE_MEM_PSE2HOST_DRBL               0x54       ///< Outbound doorbell register PSE to Host
#define B_PSE_MEM_DRBL_BUSY                   BIT31      ///< Busy bit, common for both doorbells

#define R_PSE_MEM_HOST2PSE_MSG                0xE0       ///< HOST to PSE message registers
#define R_PSE_MEM_PSE2HOST_MSG                0x60       ///< PSE to HOST message registers
#define R_PSE_MEM_REMAP2                      0x368
#define DRIVER_LOADED_BIT                     BIT0
#define R_PSE_MEM_REMAP3                      0x36C

// PSE MMIO Space Registers Offset
#define R_PSE_MMIO_IPC_OFFSET                 0x0
#define R_PSE_MMIO_PIMR_OFFSET                0x8
#define B_PSE_MMIO_PIMR_BUSY_CLEAR            BIT8
#define R_PSE_MMIO_LOADER_OFFSET              0x5000
#define R_PSE_MMIO_VERIFER_OFFSET             0x4000
#define R_PSE_MMIO_FWSTS_OFFSET               0x34
#define R_FW_STATUS_OFFSET                    12
#define B_FW_STATUS_MASK                      BIT15 | BIT14 | BIT13 | BIT12
#define R_PSE_MMIO_OWNERSHIP0_OFFSET          0x900   // Device from I2C0-I2C7
#define R_PSE_MMIO_OWNERSHIP1_OFFSET          0x904   // Device from UART0-UART5, SPI0-SPI1
#define R_PSE_MMIO_OWNERSHIP2_OFFSET          0x908   // Device from SPI2-SPI3, GBE0-1, CAN0-1, TGPIO0-1
#define R_PSE_MMIO_OWNERSHIP3_OFFSET          0x90C   // Device from PSE_DMA0-2, QEP0-3, I2S0
#define R_PSE_MMIO_OWNERSHIP4_OFFSET          0x910   // Device from I2S1, PWM, ADC, LH2PSE
#define R_PSE_MMIO_OWNERSHIP5_OFFSET          0x914
#define R_PSE_MMIO_OWNERSHIP6_OFFSET          0x918
#define R_PSE_MMIO_OWNERSHIP7_OFFSET          0x91C
#define R_PSE_MMIO_MTL_ECC_CONTROL            0xCC0
#define R_PSE_MMIO_MTL_ECC_CONTROL_INTREN     0xCC8
#define R_PSE_MMIO_DMA_ECC_CONTROL_INTREN     0x1084
#define B_PSE_MMIO_MTLTX_ECC_EN               BIT0
#define B_PSE_MMIO_MTLRX_ECC_EN               BIT1
#define B_PSE_MMIO_MTLEST_ECC_EN              BIT2
#define B_PSE_MMIO_TSOMEM_ECC_EN              BIT4
#define B_PSE_MMIO_MTL_ECC_ADROVR             BIT8
#define B_PSE_MMIO_TXMEM_INTREN               BIT0
#define B_PSE_MMIO_RXMEM_INTREN               BIT4
#define B_PSE_MMIO_ESTMEM_INTREN              BIT8
#define B_PSE_MMIO_TSOMEM_INTREN              BIT0

#define R_PSE_PME_ENABLE                      0x84
#define B_PSE_PME_ENABLE                      BIT8

// Ownerships and interrupts related registers masks
#define DEVICE_0_INDEX                        0x0
#define DEVICE_1_INDEX                        0x1
#define DEVICE_2_INDEX                        0x2
#define DEVICE_3_INDEX                        0x3
#define DEVICE_4_INDEX                        0x4
#define DEVICE_5_INDEX                        0x5
#define DEVICE_6_INDEX                        0x6
#define DEVICE_7_INDEX                        0x7

#define S_OWNERSHIP_CTRL                      0x4
#define V_DEV0_OWNERSHIP_MASK                 0x00000007  // 1 is LH owned, 0 is PSE owned (default)
#define V_DEV1_OWNERSHIP_MASK                 0x00000070  // 1 is LH owned, 0 is PSE owned (default)
#define V_DEV2_OWNERSHIP_MASK                 0x00000700  // 1 is LH owned, 0 is PSE owned (default)
#define V_DEV3_OWNERSHIP_MASK                 0x00007000  // 1 is LH owned, 0 is PSE owned (default)
#define V_DEV4_OWNERSHIP_MASK                 0x00070000  // 1 is LH owned, 0 is PSE owned (default)
#define V_DEV5_OWNERSHIP_MASK                 0x00700000  // 1 is LH owned, 0 is PSE owned (default)
#define V_DEV6_OWNERSHIP_MASK                 0x07000000  // 1 is LH owned, 0 is PSE owned (default)
#define V_DEV7_OWNERSHIP_MASK                 0x70000000  // 1 is LH owned, 0 is PSE owned (default)

#define V_DEV0_INTERRUPT_MASK                 0x00000008  // 1 is IOSF, 0 is MSI Message (default)
#define V_DEV1_INTERRUPT_MASK                 0x00000080  // 1 is IOSF, 0 is MSI Message (default)
#define V_DEV2_INTERRUPT_MASK                 0x00000800  // 1 is IOSF, 0 is MSI Message (default)
#define V_DEV3_INTERRUPT_MASK                 0x00008000  // 1 is IOSF, 0 is MSI Message (default)
#define V_DEV4_INTERRUPT_MASK                 0x00080000  // 1 is IOSF, 0 is MSI Message (default)
#define V_DEV5_INTERRUPT_MASK                 0x00800000  // 1 is IOSF, 0 is MSI Message (default)
#define V_DEV6_INTERRUPT_MASK                 0x08000000  // 1 is IOSF, 0 is MSI Message (default)
#define V_DEV7_INTERRUPT_MASK                 0x80000000  // 1 is IOSF, 0 is MSI Message (default)

#define R_PSE_IO_PCR_PCICFGCTRL1                 0x200 //I2C0
#define R_PSE_IO_PCR_PCICFGCTRL2                 0x204 //I2C1
#define R_PSE_IO_PCR_PCICFGCTRL3                 0x208 //I2C2
#define R_PSE_IO_PCR_PCICFGCTRL4                 0x20C //I2C3
#define R_PSE_IO_PCR_PCICFGCTRL5                 0x210 //I2C4
#define R_PSE_IO_PCR_PCICFGCTRL6                 0x214 //I2C5
#define R_PSE_IO_PCR_PCICFGCTRL7                 0x218 //I2C6
#define R_PSE_IO_PCR_PCICFGCTRL8                 0x21C //I2C7
#define R_PSE_IO_PCR_PCICFGCTRL9                 0x220 //UA00
#define R_PSE_IO_PCR_PCICFGCTRL10                0x224 //UA01
#define R_PSE_IO_PCR_PCICFGCTRL11                0x228 //UA02
#define R_PSE_IO_PCR_PCICFGCTRL12                0x22C //UA03
#define R_PSE_IO_PCR_PCICFGCTRL13                0x230 //UA04
#define R_PSE_IO_PCR_PCICFGCTRL14                0x234 //UA05
#define R_PSE_IO_PCR_PCICFGCTRL15                0x238 //SPI0
#define R_PSE_IO_PCR_PCICFGCTRL16                0x23C //SPI1
#define R_PSE_IO_PCR_PCICFGCTRL17                0x240 //SPI2
#define R_PSE_IO_PCR_PCICFGCTRL18                0x244 //SPI3
#define R_PSE_IO_PCR_PCICFGCTRL19                0x248 //GBE0
#define R_PSE_IO_PCR_PCICFGCTRL20                0x24C //GBE1
#define R_PSE_IO_PCR_PCICFGCTRL21                0x250 //CAN0
#define R_PSE_IO_PCR_PCICFGCTRL22                0x254 //CAN1
#define R_PSE_IO_PCR_PCICFGCTRL23                0x258 //GPIO0
#define R_PSE_IO_PCR_PCICFGCTRL24                0x25C //GPIO1
#define R_PSE_IO_PCR_PCICFGCTRL25                0x260 //DMA0
#define R_PSE_IO_PCR_PCICFGCTRL26                0x264 //DMA1
#define R_PSE_IO_PCR_PCICFGCTRL27                0x268 //DMA2
#define R_PSE_IO_PCR_PCICFGCTRL28                0x26C //DEQ0
#define R_PSE_IO_PCR_PCICFGCTRL29                0x270 //DEQ1
#define R_PSE_IO_PCR_PCICFGCTRL30                0x274 //DEQ2
#define R_PSE_IO_PCR_PCICFGCTRL31                0x278 //DEQ3
#define R_PSE_IO_PCR_PCICFGCTRL32                0x27C //I2S0
#define R_PSE_IO_PCR_PCICFGCTRL33                0x280 //I2S1
#define R_PSE_IO_PCR_PCICFGCTRL34                0x284 //PWM
#define R_PSE_IO_PCR_PCICFGCTRL35                0x288 //ADC
#define R_PSE_IO_PCR_PCICFGCTRL36                0x28C //LH2PSE

// PSE LH2PSE MMIO Space Registers
#define R_PSE_LH2PSE_MEM_TGPIO_MUX_SEL0          0xB00 //< TGPIO_MUX_SEL_REG_0_LH2PSE
#define R_PSE_LH2PSE_MEM_TGPIO_MUX_SEL1          0xB04 //< TGPIO_MUX_SEL_REG_1_LH2PSE

// PSE DMA registers
#define R_PCH_PSE_DMAC_BAR            0x10
#define B_PCH_PSE_DMAC_BAR_BA         0xFFFFC000
#define V_PCH_PSE_DMAC_BAR_SIZE       0x4000
#endif

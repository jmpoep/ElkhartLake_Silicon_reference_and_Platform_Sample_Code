/** @file
  Register names for PCH THC Controllers

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
  Copyright 2017 - 2019 Intel Corporation.

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
#ifndef _THC_REGS_
#define _THC_REGS_

//
// PCI Config
//
#define R_THC_CFG_PMD_PMCSRBSE_PMCSR                       0x74
#define  V_THC_CFG_PMD_PMCSRBSE_PMCSR_PWRST_D3             (BIT1| BIT0)
#define R_THC_CFG_PCE                                      0xA4
#define  B_THC_CFG_PCE_D3HE                                BIT2

//
// Port Control
//
#define R_THC_MEM_PORT_CONTROL                             0x1008        // Touch Host Controller Control Register (THC_M_PRT_CONTROL)
#define  B_THC_MEM_PORT_CONTROL_PORT_SPI_IO_RDY            BIT29         // 0: This SPI port IO is not ready for operation 1: This SPI port IO is ready for operation[
                                                                         // This bit is used by driver to decide whether the SPI port is ready to use.
                                                                         // SW needs to wait this bit to be 1 once on D0 entry (boot or D3 exit) before running any PIO/DMA cycles on SPI bus.
#define  B_THC_MEM_PORT_CONTROL_PORT_SUPPORTED             BIT28         // Set to 1 only for the first port under each controller.
                                                                         // Driver will not operate the other ports where the PORT_SUPPORTED bit is 0.
#define  B_THC_MEM_PORT_CONTROL_BIOS_LOCK_EN               BIT27         // Locks all THC_M_PRT_GUC_VDM* registers until driver takes
#define  B_THC_MEM_PORT_CONTROL_THC_DEVINT_DEVRST          BIT3          // 1: Deassert Device reset/power on through GPIO. 0: Assert Device reset/power off through GPIO.
#define  B_THC_MEM_PORT_CONTROL_THC_DEVINT_QUIESCE_HW_STS  BIT2          // HW will set this bit once RX sequencer is IDLE, after completing processing of any microframe that started before the THC_DEVINT_QUIESCE_EN.
                                                                         // SW cannot clear THC_DEVINT_QUIESCE_EN until it sees this bit set
#define  B_THC_MEM_PORT_CONTROL_THC_DEVINT_QUIESCE_EN      BIT1          // When SW writes 1 to this bit, THC is expected to complete processing the current microframe and then set THC_DEVINT_QUIESCE_HW_STS
#define R_THC_MEM_PORT_SPI_CONFIG                          0x1010        // THC SPI Bus Configuration Register (THC_M_PRT_SPI_CFG)
#define  B_THC_MEM_PORT_SPI_CONFIG_LOW_FREQ_EN             BIT23         // Enable SPI Clock Divide by 8 to support low freq device. (SPI_LOW_FREQ_EN)
                                                                         // 1: All the SPI read/write clock frequency (defined in SPI_TCWF/SPI_TCRF)
                                                                         //    will be divided further by 8 SPI_TCWF
                                                                         // 0: No further divider is supported.
#define  N_THC_MEM_PORT_SPI_CONFIG_WRITE_FREQUENCY         20
#define  N_THC_MEM_PORT_SPI_CONFIG_TWMODE                  18
#define  B_THC_MEM_PORT_SPI_CONFIG_FREQUENCY               (BIT0|BIT1|BIT2)   // Mask for both read and write freq
#define  V_THC_MEM_PORT_SPI_CONFIG_HIGH_FREQ_30MHZ         (BIT2)             // 30 MHz 100b Divide by 4, SPI_LOW_FREQ_EN = 0
#define  V_THC_MEM_PORT_SPI_CONFIG_HIGH_FREQ_24MHZ         (BIT0|BIT2)        // 24 MHz 101b Divide by 5, SPI_LOW_FREQ_EN = 0
#define  V_THC_MEM_PORT_SPI_CONFIG_HIGH_FREQ_20MHZ         (BIT1|BIT2)        // 20 MHZ 110b Divide by 6, SPI_LOW_FREQ_EN = 0
#define  V_THC_MEM_PORT_SPI_CONFIG_HIGH_FREQ_17MHZ         (BIT0|BIT1|BIT2)   // 17 MHZ 111b Divide by 7, SPI_LOW_FREQ_EN = 0
#define  V_THC_MEM_PORT_SPI_CONFIG_LOW_FREQ_15MHZ          (BIT0)             // 15 MHz 001b Divide by 8, SPI_LOW_FREQ_EN = 1
#define  V_THC_MEM_PORT_SPI_CONFIG_LOW_FREQ_7P5MHZ         (BIT1)             // 7.5 MHz 010b Divide by 16, SPI_LOW_FREQ_EN = 1
#define  V_THC_MEM_PORT_SPI_CONFIG_LOW_FREQ_5MHZ           (BIT0|BIT1)        // 5 MHz 011b Divide by 24, SPI_LOW_FREQ_EN = 1
#define  V_THC_MEM_PORT_SPI_CONFIG_LOW_FREQ_3P75MHZ        (BIT2)             // 3.75 MHz 100b Divide by 32, SPI_LOW_FREQ_EN = 1
#define  V_THC_MEM_PORT_SPI_CONFIG_LOW_FREQ_3MHZ           (BIT0|BIT2)        // 3 MHz 101b Divide by 40, SPI_LOW_FREQ_EN = 1
#define  V_THC_MEM_PORT_SPI_CONFIG_LOW_FREQ_2P5MHZ         (BIT1|BIT2)        // 2.5 MHz 110b Divide by 48, SPI_LOW_FREQ_EN = 1
#define  V_THC_MEM_PORT_SPI_CONFIG_LOW_FREQ_2P1MHZ         (BIT0|BIT1|BIT2)   // 2.1 MHz 111b Divide by 56, SPI_LOW_FREQ_EN = 1
#define  N_THC_MEM_PORT_SPI_CONFIG_READ_FREQUENCY          4
#define  N_THC_MEM_PORT_SPI_CONFIG_TRMODE                  2
#define  B_THC_MEM_PORT_SPI_CONFIG_MODE                    (BIT0|BIT1)        // Mask for both read and write mode
#define  V_THC_MEM_PORT_SPI_CONFIG_SINLGE_IO               0
#define R_THC_MEM_PORT_SW_SEQ_CNTRL                        0x1040         // THC SW sequencing Control
#define  B_THC_MEM_PORT_SW_SEQ_CNTRL_TSSGO                 BIT0           // THC SW Sequence Cycle Go  RW/1S/V
#define  B_THC_MEM_PORT_SW_SEQ_CNTRL_THC_SS_CD_IE          BIT1           //
#define R_THC_MEM_PORT_SW_SEQ_STS                          0x1044         // THC SW sequencing Status
#define  B_THC_MEM_PORT_SW_SEQ_STS_TSSDONE                 BIT0           // 1 when the SW Touch Cycle completes after software previously set the TSSGO bit.
                                                                          // This bit remains asserted until cleared by software writing a 1 or host partition reset.
#define  B_THC_MEM_PORT_SW_SEQ_STS_THC_SS_ERR              BIT1           // This bit remains asserted until cleared by software writing a 1 or until a partition reset occurs.
                                                                          // Software must clear this bit before setting the THC Cycle GO bit in this register.n reset.
#define  B_THC_MEM_PORT_SW_SEQ_STS_THC_CIP                 BIT3           // Hardware sets this bit when software sets the THC Cycle Go (TSSGO) bit.
                                                                          // This bit remains set until the cycle completes on the bus interface.
                                                                          // Hardware automatically sets and clears this bit so that software can determine when read data is valid.
                                                                          // And/Or when it is safe to begin programming the next command. Software must only program the next command when this bit is 0.
#define R_THC_MEM_PORT_SW_SEQ_DATA0_ADDR                   0x1048         // THC SW Sequencing Data DW0 or SPI Address Register
#define R_THC_MEM_PORT_SW_SEQ_DATA1                        0x104C         // THC SW sequencing Data DW1
#define R_THC_MEM_PORT_WPRD_BA_LOW                         0x1090         // THC Write PRD Base Address Register Low
#define R_THC_MEM_PORT_WPRD_BA_HI                          0x1094         // THC Write PRD Base Address Register High
#define R_THC_MEM_PORT_WRITE_DMA_CNTRL                     0x1098         // THC Write DMA Control
#define R_THC_MEM_PORT_DEV_INT_CAUSE_REG_VAL               0x10BC         // THC Device Interrupt Cause Register Value
#define R_THC_MEM_PORT_TSEQ_CNTRL_1                        0x1128         // Touch Sequencer Control for the 1st DMA
#define R_THC_MEM_PORT_RPRD_BA_LOW_2                       0x1200         // THC Read PRD Base Address Low for the 2nd RXDMA
#define R_THC_MEM_PORT_RPRD_BA_HI_2                        0x1204         // THC Read PRD Base Address High for the 2nd RXDMA
#define R_THC_MEM_PORT_RPRD_CNTRL_2                        0x1208         // THC Read PRD Control for the 2nd RXDMA
#define R_THC_MEM_PORT_READ_DMA_CNTRL_2                    0x120C         // THC Read DMA Control for the 2nd RXDMA

//
//  Clocks
//
#define R_THC_PCR_SB_SPI_CTRL                              0x40           // SPI Interface Control Register
#define  B_THC_PCR_SB_SPI_CTRL_SPI_DFX_CLK_EN              BIT0           // Enables the SPI DFX clock in HVM mode
                                                                          // 0: Use the functional clock for SPI interface clock
                                                                          // 1: Use the Dfx_spi_clock input for SPI interface clock.
//
// D0I2 Entry Timer
//
#define R_THC_PCR_SB_PM_CTRL                               0x48           // THC Power Management Control Register
#define  B_THC_PCR_SB_PM_CTRL_D0I2_ENTRY_TIMER             (BIT8|BIT9|BIT10|BIT11)   // This timer defines how long the THC must be idle before power gating due to D0i2. This timer is NOT used for D3 or SW PG.
                                                                          // 4'b0000: 0us
                                                                          // 4'b0001: 100ns
                                                                          // 4'b0010: 1us
#define  V_THC_PCR_SB_PM_CTRL_D0I2_ENTRY_TIMER_10US        (BIT0|BIT1)    // 4'b0011: 10us
                                                                          // 4'b0100: 100us
                                                                          // 4'b0101: 1ms
                                                                          // 4'b0110: 10ms
                                                                          // 4'b0111: 100ms
                                                                          // 4'b1000: 1s
                                                                          // 4'b1001: 10s
#define  N_THC_PCR_SB_PM_CTRL_D0I2_ENTRY_TIMER             0x8            // Number of Bits to shift Left the V_THC_PCR_SB_PM_CTRL_D0I2_ENTRY_TIMER_10US to postion the value at [8:11]

//
// Device Registers
//
#define R_THC_DEV_TOUCH_INT_CAUSE                          0x00
#define R_THC_DEV_TOUCH_CFG                                0x0C


#endif //_THC_REGS_

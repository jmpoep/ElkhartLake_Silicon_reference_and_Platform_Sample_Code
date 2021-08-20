/** @file
  Register definition for VER3 PSF component

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
#ifndef _PSF_REGS_VER3_H_
#define _PSF_REGS_VER3_H_

//
// Private chipset register (Memory space) offset definition
// The PCR register defines is used for PCR MMIO programming and PCH SBI programming as well.
//

//
// PSFx segment registers
//
#define R_VER3_PCH_PSF_PCR_PORT_CONFIG_PG0_PORT0         0x4020                  ///< PSF Segment Port Configuration Register
#define R_VER3_PCH_PSF_PCR_PORT_CONFIG_PG1_PORT0         0x4024
#define R_VER3_PCH_PSF_PCR_PORT_CONFIG_PG1_PORT1         0x4028
#define R_VER3_PCH_PSF_PCR_PORT_CONFIG_PG1_PORT2         0x402C

//
// PSFx PCRs definitions
//
#define V_VER3_PCH_LP_PSFX_PCR_PSF_MC_AGENT_MCAST_TGT_P2SB   0x38D00
#define V_VER3_PCH_PSFX_PSF_PCR_MC_AGENT_MCAST_TGT_DMI       0x10000

//
// PSF1 PCRs
//
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_ADC_REG_BASE        0x0100                  ///< D29F7 PSF base address (PSE ADC)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_CAN0_REG_BASE       0x0180                  ///< D24F1 PSF base address (PSE CAN #0)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_CAN1_REG_BASE       0x0200                  ///< D24F2 PSF base address (PSE CAN #1)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_TSN_GBE0_REG_BASE   0x0280                  ///< D29F1 PSF base address (PSE TSN GBE #0)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_TSN_GBE1_REG_BASE   0x0300                  ///< D29F2 PSF base address (PSE TSN GBE #1)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_GPIO0_REG_BASE      0x0380                  ///< D19F4 PSF base address (PSE GPIO #0)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_GPIO1_REG_BASE      0x0400                  ///< D19F5 PSF base address (PSE GPIO #1)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C0_REG_BASE       0x0480                  ///< D27F0 PSF base address (PSE I2C #0)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C1_REG_BASE       0x0500                  ///< D27F1 PSF base address (PSE I2C #1)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C2_REG_BASE       0x0580                  ///< D27F2 PSF base address (PSE I2C #2)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C3_REG_BASE       0x0600                  ///< D27F3 PSF base address (PSE I2C #3)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C4_REG_BASE       0x0680                  ///< D27F4 PSF base address (PSE I2C #4)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C5_REG_BASE       0x0700                  ///< D27F5 PSF base address (PSE I2C #5)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C6_REG_BASE       0x0780                  ///< D27F6 PSF base address (PSE I2C #6)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2C7_REG_BASE       0x0800                  ///< D24F0 PSF base address (PSE I2C #7)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2S0_REG_BASE       0x0880                  ///< D17F6 PSF base address (PSE I2S #0)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_I2S1_REG_BASE       0x0900                  ///< D17F7 PSF base address (PSE I2S #1)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_LH2PSE_IPC_REG_BASE 0x0980                  ///< D29F0 PSF base address (PSE LH2PSE IPC)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_DMA0_REG_BASE       0x0A00                  ///< D29F3 PSF base address (PSE DMA #0)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_DMA1_REG_BASE       0x0A80                  ///< D29F4 PSF base address (PSE DMA #1)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_DMA2_REG_BASE       0x0B00                  ///< D29F5 PSF base address (PSE DMA #2)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_PWM_REG_BASE        0x0B80                  ///< D29F6 PSF base address (PSE PWM #0)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_QEP0_REG_BASE       0x0C00                  ///< D24F3 PSF base address (PSE QEP #0)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_QEP1_REG_BASE       0x0C80                  ///< D24F4 PSF base address (PSE QEP #1)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_QEP2_REG_BASE       0x0D00                  ///< D24F5 PSF base address (PSE QEP #2)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_QEP3_REG_BASE       0x0D80                  ///< D24F6 PSF base address (PSE QEP #3)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_SPI0_REG_BASE       0x0E00                  ///< D19F0 PSF base address (PSE SPI #0)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_SPI1_REG_BASE       0x0E80                  ///< D19F1 PSF base address (PSE SPI #1)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_SPI2_REG_BASE       0x0F00                  ///< D19F2 PSF base address (PSE SPI #2)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_SPI3_REG_BASE       0x0F80                  ///< D19F3 PSF base address (PSE SPI #3)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART0_REG_BASE      0x1000                  ///< D17F0 PSF base address (PSE UART #0)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART1_REG_BASE      0x1080                  ///< D17F1 PSF base address (PSE UART #1)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART2_REG_BASE      0x1100                  ///< D17F2 PSF base address (PSE UART #2)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART3_REG_BASE      0x1180                  ///< D17F3 PSF base address (PSE UART #3)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART4_REG_BASE      0x1200                  ///< D17F4 PSF base address (PSE UART #4)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PSE_UART5_REG_BASE      0x1280                  ///< D17F5 PSF base address (PSE UART #5)


#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_NPK_PHANTOM_REG_BASE    0x1600                  ///< D21F7 PSF base address (Northpeak Phantom (ACPI) Function)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_TRACEHUB_REG_BASE       0x1680                  ///< D31F7 PSF base address (TraceHub)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_XHCI_REG_BASE           0x1700                  ///< D20F0 PSF base address (XHCI)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_SATA_REG_BASE           0x1800                  ///< PCH-LP D23F0 PSF base address (SATA)


#define R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE01_RS0_REG_BASE     0x2000                  ///< PCH-LP D28F0 PSF base address (PCIE PORT 01)
#define R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE02_RS0_REG_BASE     0x2080                  ///< PCH-LP D28F1 PSF base address (PCIE PORT 02)
#define R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE03_RS0_REG_BASE     0x2100                  ///< PCH-LP D28F2 PSF base address (PCIE PORT 03)
#define R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE04_RS0_REG_BASE     0x2180                  ///< PCH-LP D28F3 PSF base address (PCIE PORT 04)
#define R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE05_RS0_REG_BASE     0x2200                  ///< PCH-LP D28F4 PSF base address (PCIE PORT 05)
#define R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE06_RS0_REG_BASE     0x2280                  ///< PCH-LP D28F5 PSF base address (PCIE PORT 06)
#define R_VER3_PCH_LP_PSF1_PCR_T1_SHDW_PCIE07_RS0_REG_BASE     0x2300                  ///< PCH-LP D28F6 PSF base address (PCIE PORT 07)

#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE01_RS3_REG_BASE     0x1380                  ///< PCH-LP D28F0 PSF base address (PCIE PORT 01)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE02_RS3_REG_BASE     0x1400                  ///< PCH-LP D28F1 PSF base address (PCIE PORT 02)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE03_RS3_REG_BASE     0x1480                  ///< PCH-LP D28F2 PSF base address (PCIE PORT 03)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE04_RS3_REG_BASE     0x1500                  ///< PCH-LP D28F3 PSF base address (PCIE PORT 04)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE05_RS3_REG_BASE     0x1400                  ///< PCH-LP D28F4 PSF base address (PCIE PORT 05)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE06_RS3_REG_BASE     0x1480                  ///< PCH-LP D28F5 PSF base address (PCIE PORT 06)
#define R_VER3_PCH_LP_PSF1_PCR_T0_SHDW_PCIE07_RS3_REG_BASE     0x1500                  ///< PCH-LP D28F6 PSF base address (PCIE PORT 07)

// Other PSF1 PCRs definition

//PSF 1 Multicast Message Configuration
#define R_VER3_PCH_LP_PSF1_PCR_MC_CONTROL_MCAST0_EOI                     0x4044      ///< Multicast Control Register
#define R_VER3_PCH_LP_PSF1_PCR_MC_AGENT_MCAST0_TGT0_EOI                  0x4050      ///< Destination ID

//
// controls the PCI configuration header of a PCI function
//
#define R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPD_RS0_D28_F6   0x43BC   ///< SPD
#define R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPC_RS0_D28_F5   0x43C0   ///< SPC
#define R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPB_RS0_D28_F4   0x43C4   ///< SPB
#define R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F3   0x43C8   ///< SPA
#define R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F2   0x43CC   ///< SPA
#define R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F1   0x43D0   ///< SPA
#define R_VER3_PCH_LP_PSF1_PCR_T1_AGENT_FUNCTION_CONFIG_SPA_RS0_D28_F0   0x43D4   ///< SPA

#define R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPD_RS3_D28_F6   0x4900   /// ToDo: SPD Not in RDL, need to update
#define R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPC_RS3_D28_F5   0x4904   /// ToDo: SPC Not in RDL, need to update
#define R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPB_RS3_D28_F4   0x4908   /// ToDo: SPB Not in RDL, need to update
#define R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F3   0x4318   ///< SPA
#define R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F2   0x431C   ///< SPA
#define R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F1   0x4320   ///< SPA
#define R_VER3_PCH_LP_PSF1_PCR_T0_AGENT_FUNCTION_CONFIG_SPA_RS3_D28_F0   0x4324   ///< SPA

//
// PSF1 grant count registers
//
#define R_VER3_PCH_LP_PSF1_PCR_DEV_GNTCNT_RELOAD_DGCR0           0x43DC
#define R_VER3_PCH_LP_PSF1_PCR_TARGET_GNTCNT_RELOAD_PG1_TGT0     0x4574

//
// PSF2 PCRs (PID:PSF2)
//
#define R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_HECI1_REG_BASE           0x0180               ///< D22F0 PSF base address (CSME: HECI1)
#define R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_HECI2_REG_BASE           0x0200               ///< D22F1 PSF base address (CSME: HECI2)
#define R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_HECI3_REG_BASE           0x0280               ///< D22F4 PSF base address (CSME: HECI3)
#define R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_HECI4_REG_BASE           0x0300               ///< D22F5 PSF base address (CSME: HECI4)
#define R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_GBETSN_REG_BASE          0x0480               ///< D30F4 PSF base address (GBE TSN)
#define R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_THC0_REG_BASE            0x0500               ///< D16F6 PSF base address (THC#0)
#define R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_THC1_REG_BASE            0x0580               ///< D16F7 PSF base address (THC#1)
#define R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_UFS1_REG_BASE            0x0600               ///< D18F5 PSF base address (SCC: UFS#1)
#define R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_UFS2_REG_BASE            0x0680               ///< D18F7 PSF base address (SCC: UFS#2)
#define R_VER3_PCH_LP_PSF2_PCR_T0_SHDW_XDCI_REG_BASE            0x0780               ///< D20F1 PSF base address (XDCI)

//
// PSF3 PCRs (PID:PSF3)
//
// PSF3 PCH-LP Specific Base Address
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_AUD_REG_BASE             0x0100                  ///< D31F3 PSF base address (HDAudio)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_BTCORE_REG_BASE          0x0200                  ///< D16F2 PSF base address (CNVi: BT)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_EMMC_REG_BASE            0x0300                  ///< D26F0 PSF base address (EMMC)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C0_REG_BASE            0x0400                  ///< D21F0 PSF base address (I2C #0)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C1_REG_BASE            0x0480                  ///< D21F1 PSF base address (I2C #1)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C2_REG_BASE            0x0500                  ///< D21F2 PSF base address (I2C #2)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C3_REG_BASE            0x0580                  ///< D21F3 PSF base address (I2C #3)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C4_REG_BASE            0x0600                  ///< D25F0 PSF base address (I2C #4)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C5_REG_BASE            0x0680                  ///< D25F1 PSF base address (I2C #5)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C6_REG_BASE            0x0700                  ///< D16F0 PSF base address (I2C #6)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_I2C7_REG_BASE            0x0780                  ///< D16F1 PSF base address (I2C #7)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SPI0_REG_BASE            0x0800                  ///< D30F2 PSF base address (SPI #0)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SPI1_REG_BASE            0x0880                  ///< D30F3 PSF base address (SPI #1)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SPI2_REG_BASE            0x0900                  ///< D18F0 PSF base address (SPI #2)


#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_UART0_REG_BASE           0x0980                  ///< D30F0 PSF base address (UART #0)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_UART1_REG_BASE           0x0A00                  ///< D30F1 PSF base address (UART #1)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_UART2_REG_BASE           0x0A80                  ///< D25F2 PSF base address (UART #2)

#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_P2S_REG_BASE             0x0B80                  ///< D31F1 PSF base address (P2SB)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_PMC_REG_BASE             0x0C00                  ///< D31F2 PSF base address (PMC)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SHARED_SRAM_REG_BASE     0x0C80                  ///< D20F2 PSF base address (Shared SRAM)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_ISI_REG_BASE             0x0D80                  ///< D26F3 PSF base address (ISI)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SDCARD_REG_BASE          0x0E80                  ///< D26F1 PSF base address (SD Card)
//#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SDIO_REG_BASE            0x0F00                  ///< D26F2 PSF base address (SDIO)

#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SMBUS_REG_BASE           0x0F00                  ///< D31F4 PSF base address (SMBus)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_SPI_REG_BASE             0x0F80                  ///< D31F5 PSF base address (SPI Controller)
#define R_VER3_PCH_LP_PSF3_PCR_T0_SHDW_CNVI_REG_BASE            0x1180                  ///< D20F3 PSF base address (CNVi: WiFi)

#define R_VER3_PCH_LP_PSF3_PCR_MC_CONTROL_MCAST0_EOI            0x405C                  ///< Multicast Control Register
#define R_VER3_PCH_LP_PSF3_PCR_MC_AGENT_MCAST0_TGT0_EOI         0x4068                  ///< Destination ID

//
// PSF4 PCRs (PID:PSF4)
//
//
// PSF4 grant count registers
//
#define R_VER3_PCH_LP_PSF4_PCR_DEV_GNTCNT_RELOAD_DGCR0         0x4030                  ///< Grant Count Reload Register

#endif

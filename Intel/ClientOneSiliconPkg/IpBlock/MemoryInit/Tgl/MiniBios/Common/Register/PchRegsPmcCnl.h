/** @file
  Register names for CNL PCH PMC device

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
  Copyright 2017 Intel Corporation.

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
#ifndef _PCH_REGS_PMC_CNL_H_
#define _PCH_REGS_PMC_CNL_H_

//
// PMC SSRAM Registers (D20:F2)
//
#define PCI_DEVICE_NUMBER_PCH_PMC_SSRAM                             20
#define PCI_FUNCTION_NUMBER_PCH_PMC_SSRAM                           2

#define PMC_SSRAM_CFG_DATA_BAR                                      0xFFFFE000

//
// Crash Log Size on PMC SSRAM
//

// CNP
#define CRASHLOG_SIZE_PMC_CNP                                       0xC00  // 3KB
#define CRASHLOG_SIZE_PUNIT_CNP                                     0      // No PUNIT Crashlog Support in CNL
#define CRASHLOG_SIZE_CPU_CNP                                       0      // No CPU Crashlog Support in CNL
// ICP
#define CRASHLOG_SIZE_PMC_ICP                                       0x240  // 576 Bytes
#define CRASHLOG_SIZE_PUNIT_ICP                                     0x420  // 1056 Bytes
#define CRASHLOG_SIZE_CPU_ICP                                       0x5A0  // 1440 Bytes

//
// PMC Registers (D31:F2)
//
#define PCI_DEVICE_NUMBER_PCH_PMC                                   31
#define PCI_FUNCTION_NUMBER_PCH_PMC                                 2

#define B_PMC_CFG_PM_DATA_BAR                                       0xFFFFC000
#define V_CNL_PCH_H_PMC_PWRM_DEVICE_ID                              0xA2A1
#define V_CNL_PCH_LP_PMC_PWRM_DEVICE_ID                             0x9DA1

#define B_CNL_PCH_PMC_CFG_PM_DATA_BAR                               0xFFFFE000

#define R_CNL_PCH_PMC_PWRM_ACPI_CNT                                 0x1BD8                        ///< in CNL located in PWRM

#define R_CNL_PCH_PMC_CFG_BASE                                      0x10

#define R_CNL_PCH_PMC_PWRM_GEN_PMCON_A                              0x1020                        ///< in CNL located in PWRM

#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_DC_PP_DIS                    BIT30
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_DSX_PP_DIS                   BIT29
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_AG3_PP_EN                    BIT28
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SX_PP_EN                     BIT27
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_ALLOW_ICLK_PLL               BIT26
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_MPHY_CRICLK_GATE_OVR         BIT25
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_GBL_RST_STS                  BIT24
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_DISB                         BIT23
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_ALLOW_OPI_PLL_SD_INC0        BIT22
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_MEM_SR                       BIT21
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_ALLOW_SPXB_CG_INC0           BIT20
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_ALLOW_L1LOW_C0               BIT19
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_MS4V                         BIT18
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_ALLOW_L1LOW_OPI_ON           BIT17
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SUS_PWR_FLR                  BIT16
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_PME_B0_S5_DIS                BIT15
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_PWR_FLR                      BIT14
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_ALLOW_L1LOW_BCLKREQ_ON       BIT13
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_DISABLE_SX_STRETCH           BIT12
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_HOST_RST_STS                 BIT9
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_ESPI_SMI_LOCK                BIT8
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S4_ASE                   BIT3
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_AFTERG3_EN                   BIT0
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S3_MAW                   0xC00
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S3_MAW_60US              0x000
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S3_MAW_1MS               0x400
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S3_MAW_50MS              0x800
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S3_MAW_2S                0xC00
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SWSMI_RTSL                   0xC0
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SWSMI_RTSL_64MS              0xC0
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SWSMI_RTSL_32MS              0x80
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SWSMI_RTSL_16MS              0x40
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SWSMI_RTSL_1_5MS             0x00
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S4_MAW                   0x30
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S4_MAW_1S                0x30
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S4_MAW_2S                0x20
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S4_MAW_3S                0x10
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_SLP_S4_MAW_4S                0x00

#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_A_PER_SMI_SEL                  0x6
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_PER_SMI_64S                  0x0000
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_PER_SMI_32S                  0x0002
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_PER_SMI_16S                  0x0004
#define V_CNL_PCH_PMC_PWRM_GEN_PMCON_A_PER_SMI_8S                   0x0006

#define R_CNL_PCH_PMC_PWRM_GEN_PMCON_B                              0x1024
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_B_SLPSX_STR_POL_LOCK           BIT18            ///< Lock down SLP_S3/SLP_S4 Minimum Assertion width
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_B_WOL_EN_OVRD                  BIT13
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_B_BIOS_PCI_EXP_EN              BIT10
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_B_PWRBTN_LVL                   BIT9
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_B_SMI_LOCK                     BIT4
#define B_CNL_PCH_PMC_PWRM_GEN_PMCON_B_RTC_PWR_STS                  BIT2

#define R_CNL_PCH_PMC_PWRM_SSML                                     0x104C           ///< Set Strap Msg Lock
#define B_CNL_PCH_PMC_PWRM_SSML_SSL                                 BIT0             ///< Set_Strap Lock
#define R_CNL_PCH_PMC_PWRM_SSMC                                     0x1050           ///< Set Strap Msg Control
#define B_CNL_PCH_PMC_PWRM_SSMC_SSMS                                BIT0             ///< Set_Strap Mux Select
#define R_CNL_PCH_PMC_PWRM_SSMD                                     0x1054           ///< Set Strap Msg Data

#define R_CNL_PCH_PMC_PWRM_BM_CX_CNF                                0x1BDC           ///< in CNL this is PWRM register

#define R_CNL_PCH_PMC_PWRM_ETR3                                     0x1048          ///< in CNL this is PWRM register

//
// ACPI and legacy I/O register offsets from ACPIBASE
//

#define R_CNL_PCH_ACPI_IO_GPE0_STS_31_0                             0x60
#define R_CNL_PCH_ACPI_IO_GPE0_STS_63_32                            0x64
#define R_CNL_PCH_ACPI_IO_GPE0_STS_95_64                            0x68
#define R_CNL_PCH_ACPI_IO_GPE0_STS_127_96                           0x6C

#define R_CNL_PCH_ACPI_IO_GPE0_EN_31_0                              0x70
#define R_CNL_PCH_ACPI_IO_GPE0_EN_63_32                             0x74
#define R_CNL_PCH_ACPI_IO_GPE0_EN_95_64                             0x78
#define R_CNL_PCH_ACPI_IO_GPE0_EN_127_96                            0x7C

//
// PWRM Registers
//
#define R_CNL_PCH_PMC_PWRM_IPC_CMD                                  0x00                        ///< IPC command
#define N_CNL_PCH_PMC_PWRM_IPC_CMD_CMD_ID                           12                          ///< IPC command.cmd.ID
#define N_CNL_PCH_PMC_PWRM_IPC_CMD_SIZE                             16                          ///< IPC command.size
#define B_CNL_PCH_PMC_PWRM_IPC_CMD_SIZE_MASK                        0x00FF0000                  ///< IPC command.size mask Bits[23:16]
#define B_CNL_PCH_PMC_PWRM_IPC_CMD_MSI                              BIT8                        ///< IPC command MSI bit
#define N_CNL_PCH_PMC_PWRM_IPC_CMD_COMMAND                          0                           ///< IPC command.cmd.Command
#define B_CNL_PCH_PMC_PWRM_IPC_CMD_COMMAND_MASK                     0x000000FF                  ///< IPC command.size mask Bits[07:00]
#define V_CNL_PCH_PMC_PWRM_IPC_CMD_COMMAND_SLP_CTRL                 0xA1                        ///< IPC commmand to control S0ix policies
#define V_CNL_PCH_PMC_PWRM_IPC_CMD_COMMAND_SNDW_RCOMP               0xA2                        ///< IPC commmand to control platform Soundwire buffer RCOMP
#define V_ICL_PCH_PMC_PWRM_IPC_CMD_COMMAND_FIVR                     0xA3                        ///< IPC commmand to control FIVR Configuration
#define V_CNL_PCH_PMC_PWRM_IPC_CMD_COMMAND_NPK_STATE                0xA4                        ///< IPC commmand to control NPK Power State
#define V_CNL_PCH_PMC_PWRM_IPC_SRC_CLK_CMD                          0xA8                        ///< IPC to PMC SRCCLK command
#define R_CNL_PCH_PMC_PWRM_IPC_STS                                  0x04                        ///< IPC Status
#define B_CNL_PCH_PMC_PWRM_IPC_STS_BUSY                             BIT0                        ///< IPC Status Busy Bit
#define B_CNL_PCH_PMC_PWRM_IPC_STS_ERROR                            BIT1                        ///< IPC Status Error Bit
#define N_CNL_PCH_PMC_PWRM_IPC_STS_ERR_CODE                         BIT16                       ///< IPC Status Error status
#define B_CNL_PCH_PMC_PWRM_IPC_STS_ERR_CODE_MASK                    0x00FF0000                  ///< IPC Status Error status mask[23:16]
#define R_CNL_PCH_PMC_PWRM_IPC_SPTR                                 0x08                        ///< IPC Source Pointer
#define R_CNL_PCH_PMC_PWRM_IPC_DPTR                                 0x0C                        ///< IPC Destination Pointer
#define R_CNL_PCH_PMC_PWRM_IPC_WBUF0                                0x80                        ///< IPC Write Buffer
#define R_CNL_PCH_PMC_PWRM_IPC_WBUF1                                0x84                        ///< IPC Write Buffer
#define R_CNL_PCH_PMC_PWRM_IPC_WBUF2                                0x88                        ///< IPC Write Buffer
#define R_CNL_PCH_PMC_PWRM_IPC_WBUF3                                0x8C                        ///< IPC Write Buffer
#define R_CNL_PCH_PMC_PWRM_IPC_RBUF0                                0x90                        ///< IPC Read Buffer
#define R_CNL_PCH_PMC_PWRM_IPC_RBUF1                                0x94                        ///< IPC Read Buffer
#define R_CNL_PCH_PMC_PWRM_IPC_RBUF2                                0x98                        ///< IPC Read Buffer
#define R_CNL_PCH_PMC_PWRM_IPC_RBUF3                                0x9C                        ///< IPC Read Buffer

//
// PMC IPC command opcodes for CRASHLOG
//
#define PMC_IPC_COMMAND_ID_CRASHLOG                                 0xA6                        ///< CrashLog Command
//Sub Command
#define PMC_IPC_SUB_COMMAND_ID_CRASHLOG_DISCOVERY                   0x01                        ///< CrashLog Discovery
#define PMC_IPC_SUB_COMMAND_ID_CRASHLOG_DISABLE                     0x02                        ///< Disable CrashLog
#define PMC_IPC_SUB_COMMAND_ID_CRASHLOG_UPDATE                      0x03                        ///< Manual Trigger CrashLog
#define PMC_IPC_SUB_COMMAND_ID_CRASHLOG_ERASE                       0x04                        ///< Clear CrashLog record
#define PMC_IPC_SUB_COMMAND_ID_CRASHLOG_ON_RESET                    0x05                        ///< Collect on all resets

#define R_ICL_PCH_PMC_PWRM_EXT_RAIL_CONFIG                          0x11B8                      ///< External Rail Config
#define B_ICL_PCH_PMC_PWRM_EXT_RAIL_CONFIG_V1P05_S0IX_SX            0x1F00                      ///< Enable External V1P05 Rail in S0x/Sx
#define N_ICL_PCH_PMC_PWRM_EXT_RAIL_CONFIG_V1P05_S0IX_SX            8                           ///< Enable External V1P05 Rail in S0x/Sx
#define B_ICL_PCH_PMC_PWRM_EXT_RAIL_CONFIG_VNN_S0IX_SX              0x1F                        ///< Enable External VNN Rail in S0ix/Sx
#define N_ICL_PCH_PMC_PWRM_EXT_RAIL_CONFIG_VNN_S0IX_SX              0                           ///< Enable External VNN Rail in S0ix/Sx

#define R_ICL_PCH_PMC_PWRM_EXT_V1P05_VR_CONFIG                      0x11C0                      ///< External v1p05 Rail Config
#define B_ICL_PCH_PMC_PWRM_EXT_V1P05_VR_CONFIG_VOLTAGE              0x7FF0000                   ///< External v1p05 Voltage Value
#define N_ICL_PCH_PMC_PWRM_EXT_V1P05_VR_CONFIG_VOLTAGE              16                          ///< External v1p05 Voltage Value
#define B_ICL_PCH_PMC_PWRM_EXT_V1P05_VR_CONFIG_ICC_MAX              0xFFFF                      ///< External v1p05 Icc Max Value
#define N_ICL_PCH_PMC_PWRM_EXT_V1P05_VR_CONFIG_ICC_MAX              0                           ///< External v1p05 Icc Max Value

#define R_ICL_PCH_PMC_PWRM_EXT_VNN_VR_CONFIG                        0x11C4                      ///< External VNN Rail Config
#define B_ICL_PCH_PMC_PWRM_EXT_VNN_VR_CONFIG_VOLTAGE                0x7FF0000                   ///< External VNN Voltage Value
#define N_ICL_PCH_PMC_PWRM_EXT_VNN_VR_CONFIG_VOLTAGE                16                          ///< External VNN Voltage Value
#define B_ICL_PCH_PMC_PWRM_EXT_VNN_VR_CONFIG_ICC_MAX                0xFFFF                      ///< External VNN Icc Max Value
#define N_ICL_PCH_PMC_PWRM_EXT_VNN_VR_CONFIG_ICC_MAX                0                           ///< External VNN Icc Max Value

#define R_ICL_PCH_PMC_PWRM_VCCIN_AUX_CFG1                           0x11D0                      ///< VCCIN AUX CONFIG Register1
#define B_ICL_PCH_PMC_PWRM_VCCIN_AUX_CFG1_LCM_HCM_VOLT_TRANS_TIME   0xFF0000                    ///< Low Current Mode Voltage to High Current Mode Voltage Transition Time
#define N_ICL_PCH_PMC_PWRM_VCCIN_AUX_CFG1_LCM_HCM_VOLT_TRANS_TIME   16                          ///< Low Current Mode Voltage to High Current Mode Voltage Transition Time
#define B_ICL_PCH_PMC_PWRM_VCCIN_AUX_CFG1_RMV_HCM_VOLT_TRANS_TIME   0xFF00                      ///< Retention Mode Voltage to High Current Mode Voltage Transition Time
#define N_ICL_PCH_PMC_PWRM_VCCIN_AUX_CFG1_RMV_HCM_VOLT_TRANS_TIME   8                           ///< Retention Mode Voltage to High Current Mode Voltage Transition Time
#define B_ICL_PCH_PMC_PWRM_VCCIN_AUX_CFG1_RMV_LCM_VOLT_TRANS_TIME   0xFF                        ///< Retention Mode Voltage to Low Current Mode Voltage Transition Time
#define N_ICL_PCH_PMC_PWRM_VCCIN_AUX_CFG1_RMV_LCM_VOLT_TRANS_TIME   0                           ///< Retention Mode Voltage to Low Current Mode Voltage Transition Time

#define R_ICL_PCH_PMC_PWRM_VCCIN_AUX_CFG2                           0x11D4                      ///< VCCIN AUX CONFIG Register2
#define B_ICL_PCH_PMC_PWRM_VCCIN_AUX_CFG2_OFF_HCM_VOLT_TRANS_TIME   0x3FF                       ///< Voltage transition time when PCH changes the VCCIN_AUX regulator from 0V to the high current mode voltage
#define N_ICL_PCH_PMC_PWRM_VCCIN_AUX_CFG2_OFF_HCM_VOLT_TRANS_TIME   0                           ///< Voltage transition time when PCH changes the VCCIN_AUX regulator from 0V to the high current mode voltage

#define R_ICL_PCH_PMC_PWRM_CPPM_FIVR_POL1A                          0x11F0                      ///< Register Configures If And How CPPM Interacts With FIVR
#define B_ICL_PCH_PMC_PWRM_CPPM_FIVR_POL1A_CPPM_FIVR_VOLT_QUAL      BIT30                       ///< CPPM Qualifier Enable for FIVR
#define B_ICL_PCH_PMC_PWRM_CPPM_FIVR_POL1A_LTR_FIVR_VOLT_SEL        BIT29                       ///< ASLT/PLT SELECTION for FIVR
#define B_ICL_PCH_PMC_PWRM_CPPM_FIVR_POL1A_LTR_FIVR_VOLT_THRESH     0x1FF                       ///<  LTR Threshold for FIVR
#define V_ICL_PCH_PMC_PWRM_CPPM_FIVR_POL1A_LTR_FIVR_VOLT_THRESH     0x4
#define R_ICL_PCH_PMC_PWRM_CPPM_FIVR_POL1B                          0x11F4                      ///< Register Configures If And How CPPM Interacts With FIVR
#define B_ICL_PCH_PMC_PWRM_CPPM_FIVR_POL1B_TNE_FIVR_VOLT_PRE_WAKE   0x1FFFF                     ///< TNTE PreWake for FIVR Voltage

#define R_CNL_PCH_PMC_PWRM_PRSTS                                    0x1810                      ///< Power and Reset Status

#define R_CNL_PCH_PMC_PWRM_1814                                     0x1814
#define R_CNL_PCH_PMC_PWRM_CFG                                      0x1818                      ///< Power Management Configuration
#define B_CNL_PCH_PMC_PWRM_CFG_ER_LOCK                              BIT24                       ///< Energy Reporting Lock
#define B_CNL_PCH_PMC_PWRM_CFG_EN_PMC_UNC_ERR                       BIT23                       ///< Enable Global Reset on Uncorrectable Parity Error on PMC SRAM Interface

#define B_CNL_PCH_PMC_PWRM_CFG_COCS                                 BIT5                        ///< CPU OC Strap
#define B_CNL_PCH_PMC_PWRM_CFG_ER_EN                                BIT2                        ///< Energy Reporting Enable

#define R_CNL_PCH_PMC_PWRM_S3_PWRGATE_POL                           0x1828                      ///< S3 Power Gating Policies
#define R_CNL_PCH_PMC_PWRM_S4_PWRGATE_POL                           0x182C                      ///< Deep S4 Power Policies
#define R_CNL_PCH_PMC_PWRM_S5_PWRGATE_POL                           0x1830                      ///< Deep S5 Power Policies
#define R_CNL_PCH_PMC_PWRM_DSX_CFG                                  0x1834                      ///< Deep SX Configuration
#define R_CNL_PCH_PMC_PWRM_CFG2                                     0x183C                      ///< Power Management Configuration Reg 2
#define R_CNL_PCH_PMC_PWRM_EN_SN_SLOW_RING                          0x1848                      ///< Enable Snoop Request to SLOW_RING
#define R_CNL_PCH_PMC_PWRM_EN_SN_SLOW_RING2                         0x184C                      ///< Enable Snoop Request to SLOW_RING 2nd Reg
#define R_CNL_PCH_PMC_PWRM_EN_SN_SA                                 0x1850                      ///< Enable Snoop Request to SA
#define R_CNL_PCH_PMC_PWRM_EN_SN_SA2                                0x1854                      ///< Enable Snoop Request to SA 2nd Reg
#define R_CNL_PCH_PMC_PWRM_EN_SN_SLOW_RING_CF                       0x1858                      ///< Enable Snoop Request to SLOW_RING_CF
#define R_CNL_PCH_PMC_PWRM_EN_NS_SA                                 0x1868                      ///< Enable Non-Snoop Request to SA
#define R_CNL_PCH_PMC_PWRM_EN_CW_SLOW_RING                          0x1880                      ///< Enable Clock Wake to SLOW_RING
#define R_CNL_PCH_PMC_PWRM_EN_CW_SLOW_RING2                         0x1884                      ///< Enable Clock Wake to SLOW_RING 2nd Reg
#define R_CNL_PCH_PMC_PWRM_EN_CW_SA                                 0x1888                      ///< Enable Clock Wake to SA
#define R_CNL_PCH_PMC_PWRM_EN_CW_SA2                                0x188C                      ///< Enable Clock Wake to SA 2nd Reg
#define R_CNL_PCH_PMC_PWRM_EN_CW_SLOW_RING_CF                       0x1898                      ///< Enable Clock Wake to SLOW_RING_CF
#define R_CNL_PCH_PMC_PWRM_EN_PA_SLOW_RING                          0x18A8                      ///< Enable Pegged Active to SLOW_RING
#define R_CNL_PCH_PMC_PWRM_EN_PA_SLOW_RING2                         0x18AC                      ///< Enable Pegged Active to SLOW_RING 2nd Reg
#define R_CNL_PCH_PMC_PWRM_EN_PA_SA                                 0x18B0                      ///< Enable Pegged Active to SA
#define R_CNL_PCH_PMC_PWRM_EN_PA_SA2                                0x18B4                      ///< Enable Pegged Active to SA 2nd Reg
#define R_CNL_PCH_PMC_PWRM_EN_MISC_EVENT                            0x18C0                      ///< Enable Misc PM_SYNC Events
#define R_CNL_PCH_PMC_PWRM_PMSYNC_TPR_CONFIG                        0x18C4
#define R_CNL_PCH_PMC_PWRM_SLP_S0_RESIDENCY_COUNTER                 0x193C
#define R_CNL_PCH_PMC_PWRM_PMSYNC_MISC_CFG                          0x18C8
#define R_CNL_PCH_PMC_PWRM_PM_SYNC_STATE_HYS                        0x18D0                      ///< PM_SYNC State Hysteresis
#define R_CNL_PCH_PMC_PWRM_PM_SYNC_MODE                             0x18D4                      ///< PM_SYNC Pin Mode
#define R_CNL_PCH_PMC_PWRM_CFG3                                     0x18E0                      ///< Power Management Configuration Reg 3
#define B_ICL_PCH_PMC_PWRM_CFG3_BIOS_FIVR_DYN_EN                    BIT28                       ///< Enable Dynamic FIVR Management
#define B_CNL_PCH_PMC_PWRM_CFG3_HOST_MISC_CORE_CFG_CPU_VCC_MAP      BIT2                        ///< Enable CPU Vcc Mapping

#define R_CNL_PCH_PMC_PWRM_PM_DOWN_PPB_CFG                          0x18E4                      ///< PM_DOWN PCH_POWER_BUDGET CONFIGURATION
#define R_CNL_PCH_PMC_PWRM_CFG4                                     0x18E8                      ///< Power Management Configuration Reg 4
#define R_CNL_PCH_PMC_PWRM_CPU_EPOC                                 0x18EC
#define R_CNL_PCH_PMC_PWRM_PM_SYNC_MODE_C0                          0x18F4
#define R_CNL_PCH_PMC_PWRM_ACPI_TMR_CTL                             0x18FC

#define R_CNL_PCH_PMC_PWRM_GPIO_CFG                                 0x1920

#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_A                        0x0
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_B                        0x1
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_C                        0xD
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_D                        0x4
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_E                        0xE
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_F                        0x5
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_G                        0x2
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_H                        0x6
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_GPD                          0xA
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_VGPIO                        0x7
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_SPI                          0x3
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_AZA                          0xB
#define V_CNL_PCH_LP_PMC_PWRM_GPIO_CFG_JTAG                         0xF

#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_A                         0x0
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_B                         0x1
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_C                         0x2
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_D                         0x3
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_E                         0xA
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_F                         0xB
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_G                         0x4
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_H                         0x9
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_I                         0xC
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_J                         0xD
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPP_K                         0x8
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_GPD                           0x7
#define V_CNL_PCH_H_PMC_PWRM_GPIO_CFG_VGPIO                         0x5

#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_A                        0x2
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_B                        0x1
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_C                        0xA
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_D                        0x7
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_E                        0xB
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_F                        0x8
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_G                        0x0
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_H                        0x6
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_R                        0x3
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPP_S                        0x4
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_GPD                          0x5
#define V_ICL_PCH_LP_PMC_PWRM_GPIO_CFG_VGPIO                        0x9

#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_GPP_A                         0x2
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_GPP_B                         0x1
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_GPP_C                         0x9
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_GPP_D                         0x7
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_GPP_E                         0xA
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_GPP_G                         0x0
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_GPP_H                         0x6
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_GPP_R                         0x4
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_GPP_S                         0x3
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_GPD                           0x5
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_VGPIO                         0x8
#define V_ICL_PCH_N_PMC_PWRM_GPIO_CFG_VGPIO_4                       0xB

#define R_CNL_PCH_PMC_PWRM_1924                                     0x1924
#define R_CNL_PCH_PMC_PWRM_PMLDOCTRL                                0x1A00   ///< PMC LDO Control Register
#define B_CNL_PCH_PMC_PWRM_PMLDOCTRL_CNVIP24LDOLPEN                 BIT9
#define B_CNL_PCH_PMC_PWRM_PMLDOCTRL_USB2TS1P3LDODSEN               BIT0
#define R_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG1                           0x10C0
#define R_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG2                           0x10C4
#define R_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG2_MLSXSWPGP                 0xFFFFFFFF
#define R_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG3                           0x10C8   ///< modPHY Power Management Configuration Reg 2
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG3_MLSPDDGE                  BIT30    ///< ModPHY Lane SUS Power Domain Dynamic Gating Enable
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG3_EMFC                      BIT29    ///< Enable ModPHY FET Control
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG3_EFRT                      (BIT28 | BIT27 | BIT26 | BIT25 | BIT24)    ///< External FET Ramp Time
#define N_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG3_EFRT                      24
#define V_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG3_EFRT_200US                0x0A
#define R_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG4                           0x10CC
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG4_ASLOR_UFS                 BIT16    ///< UFS ModPHY SPD SPD Override
#define R_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5                           0x10D0
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_UFS2            BIT26
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_DMI             BIT25
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_E3              BIT24
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_E2              BIT23
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_E1              BIT22
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_E0              BIT21
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_D3              BIT20
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_D2              BIT19
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_D1              BIT18
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_D0              BIT17
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_UFS             BIT16    ///< UFS ModPHY SPD RT Request
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_XDCI            BIT15    ///< xDCI ModPHY SPD RT Request
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_XHCI            BIT14    ///< xHCI ModPHY SPD RT Request
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_GBE             BIT13    ///< GbE ModPHY SPD RT Request
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_SATA            BIT12    ///< SATA ModPHY SPD RT Request
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_C3              BIT11
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_C2              BIT10
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_C1              BIT9
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_C0              BIT8
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_B3              BIT7
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_B2              BIT6
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_B1              BIT5
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_B0              BIT4
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_A3              BIT3
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_A2              BIT2
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_A1              BIT1
#define B_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG5_MSPDRTREQ_A0              BIT0
#define R_CNL_PCH_PMC_PWRM_MODPHY_PM_CFG6                           0x10D4
#define R_CNL_PCH_PMC_PWRM_OBFF_CFG                                 0x1B14            ///< OBFF Configuration
#define R_CNL_PCH_PMC_PWRM_1B1C                                     0x1B1C
#define R_CNL_PCH_PMC_PWRM_CPPM_MISC_CFG                            0x1B20            ///< CPPM Miscellaneous Configuration
#define R_CNL_PCH_PMC_PWRM_CPPM_CG_POL1A                            0x1B24            ///< CPPM Clock Gating Policy Reg 1
#define R_CNL_PCH_PMC_PWRM_CPPM_CG_POL2A                            0x1B40            ///< CPPM Clock Gating Policy Reg 3
#define R_CNL_PCH_PMC_PWRM_1B4C                                     0x1B4C
#define R_CNL_PCH_PMC_PWRM_CPPM_CG_POL3A                            0x1BA8            ///< CPPM Clock Gating Policy Reg 5

#define B_CNL_PCH_PMC_PWRM_CPPM_CG_POLXA_LT_GX_SEL                  BIT29             ///< ASLT/PLT Selection for Clock Source Group 1
#define R_CNL_PCH_PMC_PWRM_1BD0                                     0x1BD0
#define R_CNL_PCH_PMC_PWRM_THROT_1                                  0x1BE0
#define B_CNL_PCH_PMC_PWRM_THROT_1_VR_ALERT                         BIT0
#define R_CNL_PCH_PMC_PWRM_CPPM_MPG_POL1A                           0x10E0            ///< CPPM modPHY Gating Policy Reg 1A
#define B_CNL_PCH_PMC_PWRM_CPPM_MPG_POL1A_LT_MODPHY_SEL             BIT29             ///< ASLT/PLT Selection for modPHY
#define R_CNL_PCH_PMC_PWRM_CS_SD_CTL1                               0x1BE8            ///< Clock Source Shutdown Control Reg 1
#define R_CNL_PCH_PMC_PWRM_CS_SD_CTL2                               0x1BEC ///< Clock Source Shutdown Control Reg 2
#define B_CNL_PCH_PMC_PWRM_CS_SD_CTL2_CS3_OVR_EN                    BIT18  ///< Clock Source 3 Override Enable

#define R_CNL_PCH_PMC_PWRM_HSWPGCR1                                 0x1DD0
#define B_CNL_PCH_PMC_PWRM_NPK_AON_SW_PG_CTRL                       BIT1
#define B_CNL_PCH_PMC_PWRM_NPK_VNN_SW_PG_CTRL                       BIT0
#define R_CNL_PCH_PMC_PWRM_1E00                                     0x1E00
#define R_CNL_PCH_PMC_PWRM_1E04                                     0x1E04
#define R_CNL_PCH_PMC_PWRM_ST_PG_FDIS_PMC_1                         0x1E20 ///< Static PG Related Function Disable Register 1
#define B_CNL_PCH_PMC_PWRM_ST_PG_FDIS_PMC_1_CNVI_FDIS_PMC           BIT1   ///< CNVi Function Disable (PMC Version) (CNVI_FDIS_PMC)
#define R_CNL_PCH_PMC_PWRM_ST_PG_FDIS_PMC_2                         0x1E24 ///< Static Function Disable Control Register 2
#define B_CNL_PCH_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO                0xFFF  ///< SerialIo Devices Disable Mask

#define R_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1                            0x1E28
#define B_CNL_PCH_H_PMC_PWRM_NST_PG_FDIS_1_PCIE_F3_FDIS_PMC         BIT31  ///< PCIe Controller F Port 3 Function Disable
#define B_CNL_PCH_H_PMC_PWRM_NST_PG_FDIS_1_PCIE_F2_FDIS_PMC         BIT30  ///< PCIe Controller F Port 2 Function Disable
#define B_CNL_PCH_H_PMC_PWRM_NST_PG_FDIS_1_PCIE_F1_FDIS_PMC         BIT29  ///< PCIe Controller F Port 1 Function Disable
#define B_CNL_PCH_H_PMC_PWRM_NST_PG_FDIS_1_PCIE_F0_FDIS_PMC         BIT28  ///< PCIe Controller F Port 0 Function Disable
#define B_CNL_PCH_LP_PMC_PWRM_NST_PG_FDIS_1_SDCARD_FDIS_PMC         BIT29  ///< SD Card Function Disable
#define B_CNL_PCH_H_PMC_PWRM_NST_PG_FDIS_1_SDCARD_FDIS_PMC          BIT27  ///< SD Card Function Disable
#define B_CNL_PCH_LP_PMC_PWRM_NST_PG_FDIS_1_EMMC_FDIS_PMC           BIT28  ///< eMMC Function Disable
#define B_CNL_PCH_LP_PMC_PWRM_NST_PG_FDIS_1_UFS_FDIS_PMC            BIT27  ///< UFS Function Disable
/// @todo SERVER - CDF - Update SATA 1..3 function disable bits
#define B_CDF_PCH_PMC_PWRM_NST_PG_FDIS_1_SATA_1_FDIS_PMC            BIT27  ///< SATA 1 Function Disable (CDF PCH)
#define B_CDF_PCH_PMC_PWRM_NST_PG_FDIS_1_SATA_2_FDIS_PMC            BIT27  ///< SATA 2 Function Disable (CDF PCH)
#define B_CDF_PCH_PMC_PWRM_NST_PG_FDIS_1_SATA_3_FDIS_PMC            BIT27  ///< SATA 3 Function Disable (CDF PCH)
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_XDCI_FDIS_PMC              BIT26  ///< XDCI Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_SMBUS_FDIS_PMC             BIT25  ///< Smbus Function Disable

#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_ADSP_FDIS_PMC              BIT23  ///< ADSP Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_SATA_FDIS_PMC              BIT22  ///< SATA Function Disable

#define B_CNL_PCH_H_PMC_PWRM_NST_PG_FDIS_1_PCIE_E3_FDIS_PMC         BIT21  ///< PCIe Controller E Port 3 Function Disable
#define B_CNL_PCH_H_PMC_PWRM_NST_PG_FDIS_1_PCIE_E2_FDIS_PMC         BIT20  ///< PCIe Controller E Port 2 Function Disable
#define B_CNL_PCH_H_PMC_PWRM_NST_PG_FDIS_1_PCIE_E1_FDIS_PMC         BIT19  ///< PCIe Controller E Port 1 Function Disable
#define B_CNL_PCH_H_PMC_PWRM_NST_PG_FDIS_1_PCIE_E0_FDIS_PMC         BIT18  ///< PCIe Controller E Port 0 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_D3_FDIS_PMC           BIT17  ///< PCIe Controller D Port 3 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_D2_FDIS_PMC           BIT16  ///< PCIe Controller D Port 2 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_D1_FDIS_PMC           BIT15  ///< PCIe Controller D Port 1 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_D0_FDIS_PMC           BIT14  ///< PCIe Controller D Port 0 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_C3_FDIS_PMC           BIT13  ///< PCIe Controller C Port 3 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_C2_FDIS_PMC           BIT12  ///< PCIe Controller C Port 2 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_C1_FDIS_PMC           BIT11  ///< PCIe Controller C Port 1 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_C0_FDIS_PMC           BIT10  ///< PCIe Controller C Port 0 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_B3_FDIS_PMC           BIT9   ///< PCIe Controller B Port 3 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_B2_FDIS_PMC           BIT8   ///< PCIe Controller B Port 2 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_B1_FDIS_PMC           BIT7   ///< PCIe Controller B Port 1 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_B0_FDIS_PMC           BIT6   ///< PCIe Controller B Port 0 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_A3_FDIS_PMC           BIT5   ///< PCIe Controller A Port 3 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_A2_FDIS_PMC           BIT4   ///< PCIe Controller A Port 2 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_A1_FDIS_PMC           BIT3   ///< PCIe Controller A Port 1 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_PCIE_A0_FDIS_PMC           BIT2   ///< PCIe Controller A Port 0 Function Disable
#define B_CNL_PCH_PMC_PWRM_NST_PG_FDIS_1_XHCI_FDIS_PMC              BIT0   ///< XHCI Function Disable

#define R_CNL_PCH_PMC_PWRM_FUSE_DIS_RD_1                            0x1E40 ///< Fuse Disable Read 1 Register
#define R_CNL_PCH_PMC_PWRM_FUSE_DIS_RD_2                            0x1E44 ///< Fuse Disable Read 2 Register
/// @todo SERVER - CDF - Update SATA 1..3 fuse/ss disable bits
#define B_CDF_PCH_PMC_PWRM_FUSE_DIS_RD_2_SATA_1_FUSE_SS_DIS         BIT15  ///< SATA 1 Fuse or Soft Strap Disable (CDF PCH)
#define B_CDF_PCH_PMC_PWRM_FUSE_DIS_RD_2_SATA_2_FUSE_SS_DIS         BIT15  ///< SATA 2 Fuse or Soft Strap Disable (CDF PCH)
#define B_CDF_PCH_PMC_PWRM_FUSE_DIS_RD_2_SATA_3_FUSE_SS_DIS         BIT15  ///< SATA 3 Fuse or Soft Strap Disable (CDF PCH)
#define B_CNL_PCH_PMC_PWRM_FUSE_DIS_RD_2_UFSX2_FUSE_SS_DIS          BIT7   ///< UFSX2 Fuse or Soft Strap Disable
#define B_CNL_PCH_PMC_PWRM_FUSE_DIS_RD_2_EMMC_FUSE_SS_DIS           BIT5   ///< EMMC Fuse or Soft Strap Disable
#define B_CNL_PCH_PMC_PWRM_FUSE_DIS_RD_2_CNVI_FUSE_SS_DIS           BIT4   ///< CNVi Fuse or Soft Strap Disable
#define B_CNL_PCH_PMC_PWRM_FUSE_DIS_RD_2_SDX_FUSE_SS_DIS            BIT2   ///< SD Conroller Fuse or Soft Strap Disable
#define R_CNL_PCH_PMC_PWRM_FUSE_DIS_RD_3                            0x1E48 ///< Static PG Fuse and Soft Strap Disable Read Register 3
#define R_CNL_PCH_PMC_PWRM_1E4C                                     0x1E4C

//
// ICLK Registers
//
#define R_ICLK_PCR_CMU_ONE_DWORD0                       0x2280
#define B_ICLK_PCR_CMU_ONE_DWORD0_MUXSEL_CPUBCLK        (BIT3 | BIT2)
#define N_ICLK_PCR_CMU_ONE_DWORD0_MUXSEL_CPUBCLK        2
#define V_ICLK_PCR_CMU_ONE_DWORD0_MUXSEL_CPUBCLK_OCPLL  1
#define B_ICLK_PCR_CMU_ONE_DWORD0_MUXSEL_ITPXDP         (BIT5 | BIT4)
#define N_ICLK_PCR_CMU_ONE_DWORD0_MUXSEL_ITPXDP         4

#define R_ICLK_PCR_CMU_ONE_DWORD3                       0x228C
#define B_ICLK_PCR_CMU_ONE_DWORD3_CGCTRL_CLKGATEDEF     BIT9
#define R_ICLK_PCR_CMU_ONE_DWORD16                      0x22C0
#define B_ICLK_PCR_CMU_ONE_DWORD16_CK_HDAPLLBMC_MODECTRL BIT28
#define R_ICLK_PCR_CMU_ONE_DWORD25                      0x22E4
#define R_ICLK_PCR_CMU_ONE_DWORD26                      0x22E8
#define S_ICLK_PCR_MUXSEL_BITS_PER_FIELD                4      // CLKREQ number is encoded in 4 bits
#define B_ICLK_PCR_MUXSEL_BITS_PER_FIELD                0xF    // CLKREQ number is encoded in 4 bits
#define S_ICLK_PCR_MUXSEL_FIELDS_PER_REG                8      // each CMU_ONE_DWORD register contains bitfields for 8 CLK_SRC

#define R_ICLK_PCR_DBUFF_SRC0                           0x6280 // DBUFF register for CLKSRC0
#define R_ICLK_PCR_DBUFF_SRC1                           0x6300 // DBUFF register for CLKSRC1
#define R_ICLK_PCR_DBUFF_SRC2                           0x6380 // DBUFF register for CLKSRC2
#define R_ICLK_PCR_DBUFF_SRC3                           0x6400 // DBUFF register for CLKSRC3
#define R_ICLK_PCR_DBUFF_SRC4                           0x6480 // DBUFF register for CLKSRC4
#define R_ICLK_PCR_DBUFF_SRC5                           0x6500 // DBUFF register for CLKSRC5
#define R_ICLK_PCR_DBUFF_SRC6                           0x6580 // DBUFF register for CLKSRC6
#define R_ICLK_PCR_DBUFF_SRC7                           0x6600 // DBUFF register for CLKSRC7
#define R_ICLK_PCR_DBUFF_SRC8                           0x6680 // DBUFF register for CLKSRC8
#define R_ICLK_PCR_DBUFF_SRC9                           0x6700 // DBUFF register for CLKSRC9
#define R_ICLK_PCR_DBUFF_SRC10                          0x6780 // DBUFF register for CLKSRC10
#define R_ICLK_PCR_DBUFF_SRC11                          0x6800 // DBUFF register for CLKSRC11
#define R_ICLK_PCR_DBUFF_SRC12                          0x6880 // DBUFF register for CLKSRC12
#define R_ICLK_PCR_DBUFF_SRC13                          0x6900 // DBUFF register for CLKSRC13
#define R_ICLK_PCR_DBUFF_SRC14                          0x6980 // DBUFF register for CLKSRC14
#define R_ICLK_PCR_DBUFF_SRC15                          0x6A00 // DBUFF register for CLKSRC15
#define R_ICLK_PCR_DBUFF_SRC_EN                         BIT29  // Enable bit for clock source

#define R_ICLK_PCR_CAMERA1                              0x8000
#define R_ICLK_PCR_CAMERA2                              0x8080
#define B_ICLK_PCR_FREQUENCY                            BIT0
#define B_ICLK_PCR_REQUEST                              BIT1

#endif // _PCH_REGS_PMC_CNL_H_

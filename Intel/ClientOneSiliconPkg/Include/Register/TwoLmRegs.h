/** @file
  Header file for FMHC and Far Memory Registers.

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

#ifndef TWOLM_REGS_H_
#define TWOLM_REGS_H_

#define TWOLM_DEVICE_NUM        3           // When EPOC bit is set, 2LM device is enabled as Device 3 on root bus
#define TWOLM_FUNC_0            0

//
// FMHC Mailbox Registers
//
#define R_SA_FMHC_BIOS_MAIL_BOX_FRSP              0x0020    //<FM Mailbox Response Phase : default value: 0x0>//
#define R_SA_FMHC_BIOS_MAIL_BOX_FRQC              0x0024    //<FM Mailbox Request Control : default value: 0x0>//
#define R_SA_FMHC_BIOS_MAIL_BOX_FRPA              0x0028    //<FM Mailbox Request Phase Attribute, 64bit : default value: 0x00200FD400188086>//
#define R_SA_FMHC_BIOS_MAIL_BOX_FHD               0x0030    //<FM Mailbox Host Initiated Data Phase Index Data : default value: 0x0>//
#define R_SA_FMHC_BIOS_MAIL_BOX_FDD               0x0038    //<FM Mailbox Device-Data Index Data : default value: 0x0>//

#define  R_FMHC_REGACC                            0x18      // Register Access Control
 #define  B_FMHC_REGACC_MAPLCK                    BIT5
 #define  B_FMHC_REGACC_RMPBARLCK                 BIT4
 #define  B_FMHC_REGACC_PMBARLCK                  BIT1
 #define  B_FMHC_REGACC_LCK                       BIT0

#define R_FMHC_GC03                               0x78      // FMHC General Control 03
 #define B_FMHC_GC03_DCG_AES_DIS                  BIT31     // Disable clock gating for FME AES-XTS blocks
 #define B_FMHC_GC03_DCG_MTU_DIS                  BIT30     // Disable clock gating for memory traffic block
 #define B_FMHC_GC03_DCG_STU_DIS                  BIT29     // Disable clock gating for storage traffic
 #define B_FMHC_GC03_DCG_CMIEP_DIS                BIT28     // Disable clock gating for CMI end point
 #define B_FMHC_GC03_DCG_HBIF_DIS                 BIT27     // Disable clock gating for Host bypass interface block
 #define B_FMHC_GC03_DCG_SBREG_DIS                BIT26     // Disable clock gating for sideband and regiter related block
 #define B_FMHC_GC03_DCG_PMU_DIS                  BIT25     // Disable clock gating for power management block
 #define B_FMHC_GC03_DCG_IPDYN_DIS                BIT24     // Disable FMHC IP level prim_clk clock gating

#define  R_FMHC_FMAP                              0x80      // FM Region Mapping
 #define  B_FMHC_FMAP_PMRID                       BIT16     // Astro Persistent Memory FM Region ID
 #define  B_FMHC_FMAP_PMRID_OFFSET                16
 #define  B_FMHC_FMAP_PMRID_MASK                  0xF0000
 #define  B_FMHC_FMAP_IRRID                       BIT8      // IRR Region ID
 #define  B_FMHC_FMAP_IRRID_OFFSET                8
 #define  B_FMHC_FMAP_IRRID_MASK                  0xF00
 #define  B_FMHC_FMAP_MRID                        BIT0      // Astro Volatile Memory FM Region ID
 #define  B_FMHC_FMAP_MRID_OFFSET                 0
 #define  B_FMHC_FMAP_MRID_MASK                   0xF

#define  R_FMHC_FMAXOUTR                          0x90      // FM Max Supported Outstanding Requests
 #define  B_FMHC_FMAXOUTR_LOADCV                  BIT31     // Load Credit Value
 #define  B_FMHC_FMAXOUTR_MRTS                    BIT15     // Maximum amount of Far Memory MRd TLP outstanding supported
 #define  B_FMHC_FMAXOUTR_MRTS_OFFSET             15
 #define  B_FMHC_FMAXOUTR_MRTS_MASK               0xF8000
 #define  B_FMHC_FMAXOUTR_MWSS                    BIT8      // Maximum amount of Far Memory Write Slice outstanding supported
 #define  B_FMHC_FMAXOUTR_MWSS_OFFSET             8
 #define  B_FMHC_FMAXOUTR_MWSS_MASK               0x1F00
 #define  B_FMHC_FMAXOUTR_MCSRTS                  BIT0      // Maximum amount of CSR register access VDM TLP
 #define  B_FMHC_FMAXOUTR_MCSRTS_OFFSET           0
 #define  B_FMHC_FMAXOUTR_MCSRTS_MASK             0xF

#define  R_FMHC_DEVLTR                            0xB0

#define  R_TPOWER_ON_PMSTATES                     0xC0
 #define  B_TPOWER_ON_PMSTATES_VALUE_PM5          BIT11
 #define  B_TPOWER_ON_PMSTATES_VALUE_PM5_OFFSET   11
 #define  B_TPOWER_ON_PMSTATES_VALUE_PM5_MASK     0xF000
 #define  B_TPOWER_ON_PMSTATES_SCALE_PM5          BIT8
 #define  B_TPOWER_ON_PMSTATES_SCALE_PM5_OFFSET   8
 #define  B_TPOWER_ON_PMSTATES_SCALE_PM5_MASK     0x300
 #define  B_TPOWER_ON_PMSTATES_VALUE_PM4          BIT3
 #define  B_TPOWER_ON_PMSTATES_VALUE_PM4_OFFSET   3
 #define  B_TPOWER_ON_PMSTATES_VALUE_PM4_MASK     0xF8
 #define  B_TPOWER_ON_PMSTATES_SCALE_PM4          BIT0
 #define  B_TPOWER_ON_PMSTATES_SCALE_PM4_OFFSET   0
 #define  B_TPOWER_ON_PMSTATES_SCALE_PM4_MASK     0x3

#define  R_FMHC_CCRDC                             0x104
 #define B_FMHC_CCRDC_M_CREDITS_CONFIG_DONE       BIT29

#define  R_FMHC_RCIEPL1PMMFVC                     0x110     // Root Complex Integrated End Point L1PM MFVC
 #define  B_FMHC_RCIEPL1PMMFVC_MFVC_CAPOFFEN      BIT28     // Multi-Function Virtual Channel Extended Capability Offset Enable
 #define  B_FMHC_RCIEPL1PMMFVC_MFVC_CAPOFF        BIT16     // Multi-Function Virtual Channel Extended Capability Offset
 #define  B_FMHC_RCIEPL1PMMFVC_MFVC_CAPOFF_OFFSET 16
 #define  B_FMHC_RCIEPL1PMMFVC_MFVC_CAPOFF_MASK   0xFFF0000
 #define  B_FMHC_RCIEPL1PMMFVC_L1PM_CAPOFFEN      BIT12     // L1 PM Substates Extended Capability Offset Enable
 #define  B_FMHC_RCIEPL1PMMFVC_L1PM_CAPOFF        BIT0      // L1 PM Substates Extended Capability Offset
 #define  B_FMHC_RCIEPL1PMMFVC_L1PM_CAPOFF_OFFSET 0
 #define  B_FMHC_RCIEPL1PMMFVC_L1PM_CAPOFF_MASK   0xFFF

#define  R_FMHC_RCIEPL1PMMFVC2                            0x114
 #define  B_FMHC_RCIEPL1PMMFVC2_MFVC_CAPOFFLIM            BIT16
 #define  B_FMHC_RCIEPL1PMMFVC2_MFVC_CAPOFFLIM_OFFSET     16
 #define  B_FMHC_RCIEPL1PMMFVC2_MFVC_CAPOFFLIM_MASK       0xFFF0000
 #define  B_FMHC_RCIEPL1PMMFVC2_L1PM_CAPOFFLIM            BIT0
 #define  B_FMHC_RCIEPL1PMMFVC2_L1PM_CAPOFFLIM_OFFSET     0
 #define  B_FMHC_RCIEPL1PMMFVC2_L1PM_CAPOFFLIM_MASK       0xFFF

#define  R_FMHC_RCIEPPCIE                                 0x118     // Root Complex Integrated End Point PCIE
 #define  B_FMHC_RCIEPPCIE_PMCSR_CAPOFF                   BIT20     // Power Management Status/Control Register Offset
 #define  B_FMHC_RCIEPPCIE_PMCSR_CAPOFF_OFFSET            20
 #define  B_FMHC_RCIEPPCIE_PMCSR_CAPOFF_MASK              0xFFF00000
 #define  B_FMHC_RCIEPPCIE_DEVTYP                         BIT16     // RCIEP Device/Port Type Value
 #define  V_FMHC_RCIEPPCIE_DEVTYP                         0x9
 #define  B_FMHC_RCIEPPCIE_DEVTYP_OFFSET                  16
 #define  B_FMHC_RCIEPPCIE_DEVTYP_MASK                    0xF0000
 #define  B_FMHC_RCIEPPCIE_PCIE_CAPOFFEN                  BIT12     // PCI Express Extended Capability Extended Capability Offset Enable
 #define  B_FMHC_RCIEPPCIE_PCIE_CAPOFF                    BIT0      // PCI Express Extended Capability Extended Capability Offset
 #define  B_FMHC_RCIEPPCIE_PCIE_CAPOFF_OFFSET             0
 #define  B_FMHC_RCIEPPCIE_PCIE_CAPOFF_MASK               0xFFF

#define R_FMHC_RCIEPPCIE2                                 0x11C
 #define B_FMHC_RCIEPPCIE2_PCIE_CAPOFFLIM                 BIT0
 #define B_FMHC_RCIEPPCIE2_PCIE_CAPOFFLIM_OFFSET          0
 #define B_FMHC_RCIEPPCIE2_PCIE_CAPOFFLIM_MASK            0xFFF

#define R_FMHC_RCIEPLCAPAB                                0x120
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFFEN          BIT28
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFF            BIT16
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFF_OFFSET     16
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFF_MASK       0xFFF0000
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFFEN          BIT12
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFF            BIT0
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFF_OFFSET     0
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFF_MASK       0xFFF

#define R_FMHC_RCIEPLCAPAB2                               0x124
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFFLIM         BIT16
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFFLIM_OFFSET  16
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_B_CAPOFFLIM_MASK    0xFFF0000
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFFLIM         BIT0
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFFLIM_OFFSET  0
 #define B_FMHC_RCIEPLCAPAB_CAPSTRUCT_A_CAPOFFLIM_MASK    0xFFF

#define R_FMHC_RCIEPLCAPCD                                0x128
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFFEN          BIT28
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFF            BIT16
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFF_OFFSET     16
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFF_MASK       0xFFF0000
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFFEN          BIT12
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFF            BIT0
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFF_OFFSET     0
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFF_MASK       0xFFF

#define R_FMHC_RCIEPLCAPCD2                               0x12C
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFFLIM         BIT16
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFFLIM_OFFSET  16
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_D_CAPOFFLIM_MASK    0xFFF0000
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFFLIM         BIT0
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFFLIM_OFFSET  0
 #define B_FMHC_RCIEPLCAPCD_CAPSTRUCT_C_CAPOFFLIM_MASK    0xFFF

#define  R_FMHC_HBIFCREDIT_VC1                            0x164
 #define  B_FMHC_HBIFCREDIT_VC1_M_CREDITS_CONFIG_DONE     BIT31

#define  R_FMHC_HMRMPB                            0x200     // High System Memory Logical Remap Base
#define  R_FMHC_HMRMPL                            0x208     // High System Memory Logical Remap Limit
#define  R_FMHC_HMRMPNEW                          0x210     // High System Memory Logical Remap New
#define  R_FMHC_PMRBL                             0x220     // Persistent Memory Region Address Base Lower
#define  R_FMHC_PMRBU                             0x224     // Persistent Memory Region Address Base Upper
#define  R_FMHC_PMRLL                             0x228     // Persistent Memory Region Address Limit Lower
#define  R_FMHC_PMRLU                             0x22C     // Persistent Memory Region Address Limit Upper

#define  R_FMHC_PCE                               0x308     // Power Control Enables Register
 #define  B_FMHC_PCE_PMCRE                        BIT0      // PMC Request Enable

#define R_FMHC_PRI_CDCB                           0x318
 #define B_FMHC_PRI_CDCB_CCD                      BIT0
 #define B_FMHC_PRI_CDCB_DDCGD                    BIT1

#define R_FMHC_SB_CDCB                            0x320
 #define B_FMHC_SB_CDCB_CCD                       BIT0
 #define B_FMHC_SB_CDCB_DDCGD                     BIT1

//
// Far Memory Device (3DXP) VDM Registers for Mailbox Interface
//
#define R_SA_FMSS_VDM_MAIL_BOX_FMPMM                0x0010    //<FMSS Power Management Mode>//
 #define B_SA_FMSS_VDM_MAIL_BOX_FMPMM_FMPMMEN       BIT0      //<FMSS Power Management Mode Enable>//
 #define B_SA_FMSS_VDM_MAIL_BOX_NVME_HOLD_DISABLE   BIT1      //<NVMe_hold_disable bit>//

#define R_SA_FMSS_VDM_MAIL_BOX_POWER_STATE_CONTROL  0x0014    //<Power State Control>//

#define R_SA_FMSS_VDM_MAIL_BOX_DEVHWS               0x0020    //<Device HW Status>//
 #define B_SA_FMSS_VDM_MAIL_BOX_DEVHWS_FWLOADED     BIT31     //<Device FW Status Bit>//

#define R_SA_FMSS_VDM_MAIL_BOX_TPOWER_ON_SUPPORT    0x0030    //<2LM L1.2 Tpower On Support>//
#define R_SA_FMSS_VDM_MAIL_BOX_TPOWER_ON_CONTROL    0x0034    //<2LM L1.2 Tpower On Control>//
 #define B_T_POWER_ON_SCALE_PM4_OFFSET                   0
 #define B_T_POWER_ON_SCALE_PM4_MASK                   0x3   // Bit[1:0]
 #define B_T_POWER_ON_VALUE_PM4_OFFSET                   3
 #define B_T_POWER_ON_VALUE_PM4_MASK                  0x1F   // Bit[7:3]
 #define B_T_POWER_ON_SCALE_PM5_OFFSET                   8
 #define B_T_POWER_ON_SCALE_PM5_MASK                   0x3   // Bit[9:8]
 #define B_T_POWER_ON_VALUE_PM5_OFFSET                  12
 #define B_T_POWER_ON_VALUE_PM5_MASK                  0x1F   // Bit[15:11]

#define R_SA_FMSS_VDM_MAIL_BOX_MBCMD0             0x0800    //<Mailbox Command Register DW0 [31:00] : default value: 0x0000_0000>//
#define R_SA_FMSS_VDM_MAIL_BOX_MBCMD1             0x0804    //<Mailbox Command Register DW1 [63:32] : default value: 0x0000_0000>//

#define R_SA_FMSS_VDM_MAIL_BOX_MBNCE0             0x0A00    //<Mailbox Nonce Register DW0 [31:0] : default value: 0x0000_0000>//
#define R_SA_FMSS_VDM_MAIL_BOX_MBNCE1             0x0A04    //<Mailbox Nonce Register DW1 [63:32] : default value: 0x0000_0000>//

#define R_SA_FMSS_VDM_MAIL_BOX_MBSTS0             0x1000    //<Mailbox Status Register DW0 [31:0] : default value: 0x0000_0001>//
#define R_SA_FMSS_VDM_MAIL_BOX_MBSTS1             0x1004    //<Mailbox Status Register DW1 [63:32] : default value: 0x0000_0000>//

#define R_SA_FMSS_VDM_MAIL_BOX_INBOXDW0           0x2000    //<Inbox Data Byte [3:0] to RAM : default value: N/A>//
#define R_SA_FMSS_VDM_MAIL_BOX_INBOXDW1           0x2004    //<Inbox Data Byte [7:4] to RAM : default value: N/A>//

#define R_SA_FMSS_VDM_MAIL_BOX_INBOXDW127         0x21FC    //<Inbox Data Byte [511:508] to RAM : default value: N/A>//

#define R_SA_FMSS_VDM_MAIL_BOX_OUTBOXDW0          0x3000    //<Outbox Data Byte [3:0] to RAM : default value: N/A>//
#define R_SA_FMSS_VDM_MAIL_BOX_OUTBOXDW1          0x3004    //<Outbox Data Byte [7:4] to RAM : default value: N/A>//

#define R_SA_FMSS_VDM_MAIL_BOX_OUTBOXDW127        0x31FC    //<Outbox Data Byte [511:508] to RAM : default value: N/A>//


//
// Astro Controller Registers
//
#define  R_ASTRO_NMEM                                  0x0510      // Astro NMEM
#define  B_ENABLE_NMEM_MODE                            BIT0

#define  R_ASTRO_NMEM_STATUS                           0x0634      // Astro NMEM status
#define  B_NMEM_FAILED_STATUS                          BIT0
#define  R_ASTRO_TAG_RT_INIT                           0x067C      // Astro power up actions

#define  R_ASTRO_DDR_CONFIG                            0x0678      // Astro_ddr_memory_configuration
#define  B_DDR_SIZE_MASK                               0xFFFF      // Bit[15:0]
#define  B_DDR_SIZE_OFFSET                             0

#define  R_ASTRO_SXP_CONFIG_1                          0x0668      // Astro_sxp_memory_configuration
#define  R_ASTRO_SXP_CONFIG_2                          0x0500      // Astro_sxp_memory_configuration
#define  B_SXP_SIZE_MASK                               0xFFFFFF    // Bit[23:0]
#define  B_SXP_SIZE_OFFSET                             0
#define  B_PMEM_EN                                     BIT31
#define  B_PMEM_SIZE_MASK                              0xFFFFFF00000000    // Bit[55:32]
#define  B_PMEM_SIZE_OFFSET                            32


//
// Willard PCIe device Registers
//

// MFVC capability registers
#define R_PORT_VC_CONTROL_REGISTER                     0x0C
#define B_LOAD_VC_ARBITRATION_TABLE                    BIT0
#define B_VC_ARBITRATION_SELECT_OFFSET                 1

#define R_PORT_VC_STATUS_REGISTER                      0x0E
#define R_VC1_RESOURCE_CONTROL_REGISTER                0x20
#define R_VC1_RESOURCE_STATUS_REGISTER                 0x24
#define B_VC1_NEGOTIATION_PENDING_OFFSET               17

#define R_MFVC_VC_ARB_TABLE_0_REGISTER                 0x30
#define R_MFVC_VC_ARB_TABLE_1_REGISTER                 0x34
#define R_MFVC_VC_ARB_TABLE_2_REGISTER                 0x38
#define R_MFVC_VC_ARB_TABLE_3_REGISTER                 0x3C
#define R_MFVC_VC_ARB_TABLE_4_REGISTER                 0x40
#define R_MFVC_VC_ARB_TABLE_5_REGISTER                 0x44
#define R_MFVC_VC_ARB_TABLE_6_REGISTER                 0x48
#define R_MFVC_VC_ARB_TABLE_7_REGISTER                 0x4C
#define R_MFVC_VC_ARB_TABLE_8_REGISTER                 0x50
#define R_MFVC_VC_ARB_TABLE_9_REGISTER                 0x54
#define R_MFVC_VC_ARB_TABLE_10_REGISTER                0x58
#define R_MFVC_VC_ARB_TABLE_11_REGISTER                0x5C
#define R_MFVC_VC_ARB_TABLE_12_REGISTER                0x60
#define R_MFVC_VC_ARB_TABLE_13_REGISTER                0x64
#define R_MFVC_VC_ARB_TABLE_14_REGISTER                0x68
#define R_MFVC_VC_ARB_TABLE_15_REGISTER                0x6C
#define B_VC_ID0_OFFSET                                0
#define B_RSVD0                                        BIT3
#define B_VC_ID1_OFFSET                                4
#define B_RSVD1                                        BIT7
#define B_VC_ID2_OFFSET                                8
#define B_RSVD2                                        BIT11
#define B_VC_ID3_OFFSET                                12
#define B_RSVD3                                        BIT15
#define B_VC_ID4_OFFSET                                16
#define B_RSVD4                                        BIT19
#define B_VC_ID5_OFFSET                                20
#define B_RSVD5                                        BIT23
#define B_VC_ID6_OFFSET                                24
#define B_RSVD6                                        BIT27
#define B_VC_ID7_OFFSET                                28
#define B_RSVD7                                        BIT31

#define R_DEVICE_CAPABILITIES_REGISTER                 0x04
#define R_DEVICE_CONTROL_REGISTER                      0x08
#define B_CORRECTABLE_ERROR_EN                         BIT0
#define B_NON_FATAL_ERROR_EN                           BIT1
#define B_FATAL_ERROR_EN                               BIT2
#define B_UNSUPPORTED_REQUEST_EN                       BIT3
#define B_ENABLE_RELAXED_ORDERING                      BIT4
#define B_MAX_PAYLOAD_SIZE_OFFSET                      5
#define B_MAX_READ_REQUEST_SIZE_OFFSET                 11

#define R_LINK_CAPABILITIES_REGISTER                   0x0C
#define B_ASPM_SUPPORT_OFFSET                          10

#define R_LINK_CONTROL_REGISTER                        0x10
#define B_L0_ENTRY_ENABLED                             BIT0
#define B_L1_ENTRY_ENABLED                             BIT1

#define R_DEVICE_CONTROL2_REGISTER                     0x28
#define B_IDO_COMPLETION_EN                            BIT9
#define B_LTR_MECHANISM_EN                             BIT10

#define R_L1PM_SUBSTATES_CAPABILITIES_REGISTER         0x04
#define B_ASPM_L1_2_SUPPORTED_OFFSET                   2
#define B_ASPM_L1_1_SUPPORTED_OFFSET                   3
#define B_PORT_T_POWER_ON_SCALE_OFFSET                 16
#define B_PORT_T_POWER_ON_SCALE_MASK                   0x3  // Bit[17:16]
#define B_PORT_T_POWER_ON_VALUE_OFFSET                 19
#define B_PORT_T_POWER_ON_VALUE_MASK                   0x1F  // Bit[23:19]

#define R_L1PM_SUBSTATES_CONTROL_1_REGISTER            0x08
#define R_L1PM_SUBSTATES_CONTROL_2_REGISTER            0x0C
#define B_PORT_T_POWER_ON_VALUE_CONTROL_OFFSET         3
#define B_PORT_T_POWER_ON_SCALE_CONTROL_OFFSET         0

#endif /* TWOLM_REGS_H_ */

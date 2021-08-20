/** @file
  Register names for PCH PMC device

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
#ifndef _PCH_REGS_PMC_H_
#define _PCH_REGS_PMC_H_

//
// PMC Registers (D31:F2)
//
#define PCI_DEVICE_NUMBER_PCH_PMC                           31
#define PCI_FUNCTION_NUMBER_PCH_PMC                         2

#define R_PMC_PWRM_PM_DATA_BAR                               0x10
#define B_PMC_PWRM_PM_DATA_BAR                               0xFFFFE000

#define B_PMC_CFG_PWRM_BASE_MASK                             0xFFFF0000                    ///< PWRM must be 64KB alignment to align the source decode.

#define B_PMC_PWRM_ACPI_CNT_PWRM_EN                          BIT8                          ///< PWRM enable
#define B_PMC_PWRM_ACPI_CNT_ACPI_EN                          BIT7                          ///< ACPI eanble
#define B_PMC_PWRM_ACPI_CNT_SCIS                             (BIT2 | BIT1 | BIT0)          ///< SCI IRQ select
#define V_PMC_PWRM_ACPI_CNT_SCIS_IRQ9                        0
#define V_PMC_PWRM_ACPI_CNT_SCIS_IRQ10                       1
#define V_PMC_PWRM_ACPI_CNT_SCIS_IRQ11                       2
#define V_PMC_PWRM_ACPI_CNT_SCIS_IRQ20                       4
#define V_PMC_PWRM_ACPI_CNT_SCIS_IRQ21                       5
#define V_PMC_PWRM_ACPI_CNT_SCIS_IRQ22                       6
#define V_PMC_PWRM_ACPI_CNT_SCIS_IRQ23                       7

#define B_PMC_PWRM_BM_CX_CNF_STORAGE_BREAK_EN                BIT31
#define B_PMC_PWRM_BM_CX_CNF_PCIE_BREAK_EN                   BIT30
#define B_PMC_PWRM_BM_CX_CNF_AZ_BREAK_EN                     BIT24
#define B_PMC_PWRM_BM_CX_CNF_DPSN_BREAK_EN                   BIT19
#define B_PMC_PWRM_BM_CX_CNF_XHCI_BREAK_EN                   BIT17
#define B_PMC_PWRM_BM_CX_CNF_SATA3_BREAK_EN                  BIT16
#define B_PMC_PWRM_BM_CX_CNF_SCRATCHPAD                      BIT15
#define B_PMC_PWRM_BM_CX_CNF_PHOLD_BM_STS_BLOCK              BIT14
#define B_PMC_PWRM_BM_CX_CNF_MASK_CF                         BIT11
#define B_PMC_PWRM_BM_CX_CNF_BM_STS_ZERO_EN                  BIT10
#define B_PMC_PWRM_BM_CX_CNF_PM_SYNC_MSG_MODE                BIT9
#define B_PMC_PWRM_ETR3_CF9LOCK                              BIT31           ///< CF9h Lockdown
#define B_PMC_PWRM_ETR3_LATCH_EVENTS_C10_EXIT                BIT30
#define B_PMC_PWRM_ETR3_USB_CACHE_DIS                        BIT21
#define B_PMC_PWRM_ETR3_CF9GR                                BIT20           ///< CF9h Global Reset
#define B_PMC_PWRM_ETR3_SKIP_HOST_RST_HS                     BIT19
#define B_PMC_PWRM_ETR3_CWORWRE                              BIT18
#define B_PMC_PWRM_THROT_1_VR_ALERT                          BIT0

//
// ACPI and legacy I/O register offsets from ACPIBASE
//
#define R_ACPI_IO_PM1_STS                        0x00
#define S_ACPI_IO_PM1_STS                        2
#define B_ACPI_IO_PM1_STS_WAK                    BIT15
#define B_ACPI_IO_PM1_STS_PCIEXP_WAKE_STS        BIT14
#define B_ACPI_IO_PM1_STS_PRBTNOR                BIT11
#define B_ACPI_IO_PM1_STS_RTC                    BIT10
#define B_ACPI_IO_PM1_STS_PWRBTN                 BIT8
#define B_ACPI_IO_PM1_STS_GBL                    BIT5
#define B_ACPI_IO_PM1_STS_BM                     BIT4
#define B_ACPI_IO_PM1_STS_TMROF                  BIT0
#define N_ACPI_IO_PM1_STS_WAK                    15
#define N_ACPI_IO_PM1_STS_PCIEXP_WAKE_STS        14
#define N_ACPI_IO_PM1_STS_PRBTNOR                11
#define N_ACPI_IO_PM1_STS_RTC                    10
#define N_ACPI_IO_PM1_STS_PWRBTN                 8
#define N_ACPI_IO_PM1_STS_GBL                    5
#define N_ACPI_IO_PM1_STS_BM                     4
#define N_ACPI_IO_PM1_STS_TMROF                  0

#define R_ACPI_IO_PM1_EN                         0x02
#define S_ACPI_IO_PM1_EN                         2
#define B_ACPI_IO_PM1_EN_RTC                     BIT10
#define B_ACPI_IO_PM1_EN_PWRBTN                  BIT8
#define B_ACPI_IO_PM1_EN_GBL                     BIT5
#define B_ACPI_IO_PM1_EN_TMROF                   BIT0
#define N_ACPI_IO_PM1_EN_RTC                     10
#define N_ACPI_IO_PM1_EN_PWRBTN                  8
#define N_ACPI_IO_PM1_EN_GBL                     5
#define N_ACPI_IO_PM1_EN_TMROF                   0

#define R_ACPI_IO_PM1_CNT                        0x04
#define S_ACPI_IO_PM1_CNT                        4
#define B_ACPI_IO_PM1_CNT_SLP_EN                 BIT13
#define B_ACPI_IO_PM1_CNT_SLP_TYP                (BIT12 | BIT11 | BIT10)
#define V_ACPI_IO_PM1_CNT_S0                     0
#define V_ACPI_IO_PM1_CNT_S1                     BIT10
#define V_ACPI_IO_PM1_CNT_S3                     (BIT12 | BIT10)
#define V_ACPI_IO_PM1_CNT_S4                     (BIT12 | BIT11)
#define V_ACPI_IO_PM1_CNT_S5                     (BIT12 | BIT11 | BIT10)
#define B_ACPI_IO_PM1_CNT_GBL_RLS                BIT2
#define B_ACPI_IO_PM1_CNT_BM_RLD                 BIT1
#define B_ACPI_IO_PM1_CNT_SCI_EN                 BIT0

#define R_ACPI_IO_PM1_TMR                        0x08
#define V_ACPI_IO_PM1_TMR_FREQUENCY              3579545
#define B_ACPI_IO_PM1_TMR_VAL                    0xFFFFFF
#define V_ACPI_IO_PM1_TMR_MAX_VAL                0x1000000       ///< The timer is 24 bit overflow

#define R_ACPI_IO_SMI_EN                              0x30
#define S_ACPI_IO_SMI_EN                              4
#define B_ACPI_IO_SMI_EN_LEGACY_USB3                  BIT31
#define B_ACPI_IO_SMI_EN_GPIO_UNLOCK_SMI              BIT27
#define B_ACPI_IO_SMI_EN_LEGACY_USB2                  BIT17
#define B_ACPI_IO_SMI_EN_PERIODIC                     BIT14
#define B_ACPI_IO_SMI_EN_TCO                          BIT13
#define B_ACPI_IO_SMI_EN_MCSMI                        BIT11
#define B_ACPI_IO_SMI_EN_BIOS_RLS                     BIT7
#define B_ACPI_IO_SMI_EN_SWSMI_TMR                    BIT6
#define B_ACPI_IO_SMI_EN_APMC                         BIT5
#define B_ACPI_IO_SMI_EN_ON_SLP_EN                    BIT4
#define B_ACPI_IO_SMI_EN_LEGACY_USB                   BIT3
#define B_ACPI_IO_SMI_EN_BIOS                         BIT2
#define B_ACPI_IO_SMI_EN_EOS                          BIT1
#define B_ACPI_IO_SMI_EN_GBL_SMI                      BIT0
#define N_ACPI_IO_SMI_EN_LEGACY_USB3                  31
#define N_ACPI_IO_SMI_EN_ESPI                         28
#define N_ACPI_IO_SMI_EN_GPIO_UNLOCK                  27
#define N_ACPI_IO_SMI_EN_INTEL_USB2                   18
#define N_ACPI_IO_SMI_EN_LEGACY_USB2                  17
#define N_ACPI_IO_SMI_EN_PERIODIC                     14
#define N_ACPI_IO_SMI_EN_TCO                          13
#define N_ACPI_IO_SMI_EN_MCSMI                        11
#define N_ACPI_IO_SMI_EN_BIOS_RLS                     7
#define N_ACPI_IO_SMI_EN_SWSMI_TMR                    6
#define N_ACPI_IO_SMI_EN_APMC                         5
#define N_ACPI_IO_SMI_EN_ON_SLP_EN                    4
#define N_ACPI_IO_SMI_EN_LEGACY_USB                   3
#define N_ACPI_IO_SMI_EN_BIOS                         2
#define N_ACPI_IO_SMI_EN_EOS                          1
#define N_ACPI_IO_SMI_EN_GBL_SMI                      0

#define R_ACPI_IO_SMI_STS                             0x34
#define S_ACPI_IO_SMI_STS                             4
#define B_ACPI_IO_SMI_STS_LEGACY_USB3                 BIT31
#define B_ACPI_IO_SMI_STS_GPIO_UNLOCK                 BIT27
#define B_ACPI_IO_SMI_STS_SPI                         BIT26
#define B_ACPI_IO_SMI_STS_MONITOR                     BIT21
#define B_ACPI_IO_SMI_STS_PCI_EXP                     BIT20
#define B_ACPI_IO_SMI_STS_PATCH                       BIT19
#define B_ACPI_IO_SMI_STS_INTEL_USB2                  BIT18
#define B_ACPI_IO_SMI_STS_LEGACY_USB2                 BIT17
#define B_ACPI_IO_SMI_STS_SMBUS                       BIT16
#define B_ACPI_IO_SMI_STS_SERIRQ                      BIT15
#define B_ACPI_IO_SMI_STS_PERIODIC                    BIT14
#define B_ACPI_IO_SMI_STS_TCO                         BIT13
#define B_ACPI_IO_SMI_STS_DEVMON                      BIT12
#define B_ACPI_IO_SMI_STS_MCSMI                       BIT11
#define B_ACPI_IO_SMI_STS_GPIO_SMI                    BIT10
#define B_ACPI_IO_SMI_STS_GPE0                        BIT9
#define B_ACPI_IO_SMI_STS_PM1_STS_REG                 BIT8
#define B_ACPI_IO_SMI_STS_SWSMI_TMR                   BIT6
#define B_ACPI_IO_SMI_STS_APM                         BIT5
#define B_ACPI_IO_SMI_STS_ON_SLP_EN                   BIT4
#define B_ACPI_IO_SMI_STS_LEGACY_USB                  BIT3
#define B_ACPI_IO_SMI_STS_BIOS                        BIT2
#define N_ACPI_IO_SMI_STS_LEGACY_USB3                 31
#define N_ACPI_IO_SMI_STS_ESPI                        28
#define N_ACPI_IO_SMI_STS_GPIO_UNLOCK                 27
#define N_ACPI_IO_SMI_STS_SPI                         26
#define N_ACPI_IO_SMI_STS_MONITOR                     21
#define N_ACPI_IO_SMI_STS_PCI_EXP                     20
#define N_ACPI_IO_SMI_STS_PATCH                       19
#define N_ACPI_IO_SMI_STS_INTEL_USB2                  18
#define N_ACPI_IO_SMI_STS_LEGACY_USB2                 17
#define N_ACPI_IO_SMI_STS_SMBUS                       16
#define N_ACPI_IO_SMI_STS_SERIRQ                      15
#define N_ACPI_IO_SMI_STS_PERIODIC                    14
#define N_ACPI_IO_SMI_STS_TCO                         13
#define N_ACPI_IO_SMI_STS_DEVMON                      12
#define N_ACPI_IO_SMI_STS_MCSMI                       11
#define N_ACPI_IO_SMI_STS_GPIO_SMI                    10
#define N_ACPI_IO_SMI_STS_GPE0                        9
#define N_ACPI_IO_SMI_STS_PM1_STS_REG                 8
#define N_ACPI_IO_SMI_STS_SWSMI_TMR                   6
#define N_ACPI_IO_SMI_STS_APM                         5
#define N_ACPI_IO_SMI_STS_ON_SLP_EN                   4
#define N_ACPI_IO_SMI_STS_LEGACY_USB                  3
#define N_ACPI_IO_SMI_STS_BIOS                        2

#define R_ACPI_IO_GPE_CNTL                            0x40
#define B_ACPI_IO_GPE_CNTL_SWGPE_CTRL                 BIT17

#define R_ACPI_IO_DEVACT_STS                          0x44
#define S_ACPI_IO_DEVACT_STS                          2
#define B_ACPI_IO_DEVACT_STS_MASK                     0x13E1
#define B_ACPI_IO_DEVACT_STS_KBC                      BIT12
#define B_ACPI_IO_DEVACT_STS_PIRQDH                   BIT9
#define B_ACPI_IO_DEVACT_STS_PIRQCG                   BIT8
#define B_ACPI_IO_DEVACT_STS_PIRQBF                   BIT7
#define B_ACPI_IO_DEVACT_STS_PIRQAE                   BIT6
#define B_ACPI_IO_DEVACT_STS_D0_TRP                   BIT0
#define N_ACPI_IO_DEVACT_STS_KBC                      12
#define N_ACPI_IO_DEVACT_STS_PIRQDH                   9
#define N_ACPI_IO_DEVACT_STS_PIRQCG                   8
#define N_ACPI_IO_DEVACT_STS_PIRQBF                   7
#define N_ACPI_IO_DEVACT_STS_PIRQAE                   6

#define R_ACPI_IO_PM2_CNT                             0x50
#define B_ACPI_IO_PM2_CNT_ARB_DIS                     BIT0

#define R_ACPI_IO_OC_WDT_CTL                          0x54
#define B_ACPI_IO_OC_WDT_CTL_RLD                      BIT31
#define B_ACPI_IO_OC_WDT_CTL_ICCSURV_STS              BIT25
#define B_ACPI_IO_OC_WDT_CTL_NO_ICCSURV_STS           BIT24
#define B_ACPI_IO_OC_WDT_CTL_FORCE_ALL                BIT15
#define B_ACPI_IO_OC_WDT_CTL_EN                       BIT14
#define B_ACPI_IO_OC_WDT_CTL_ICCSURV                  BIT13
#define B_ACPI_IO_OC_WDT_CTL_LCK                      BIT12
#define B_ACPI_IO_OC_WDT_CTL_TOV_MASK                 0x3FF
#define B_ACPI_IO_OC_WDT_CTL_FAILURE_STS              BIT23
#define B_ACPI_IO_OC_WDT_CTL_UNXP_RESET_STS           BIT22
#define B_ACPI_IO_OC_WDT_CTL_AFTER_POST               0x3F0000
#define V_ACPI_IO_OC_WDT_CTL_STATUS_FAILURE           1
#define V_ACPI_IO_OC_WDT_CTL_STATUS_OK                0

#define S_ACPI_IO_GPE0_STS_127_96                  4
#define B_ACPI_IO_GPE0_STS_127_96_WADT             BIT18
#define B_ACPI_IO_GPE0_STS_127_96_USB_CON_DSX_STS  BIT17
#define B_ACPI_IO_GPE0_STS_127_96_LAN_WAKE         BIT16
#define B_ACPI_IO_GPE0_STS_127_96_GPIO_TIER_2      BIT15
#define B_ACPI_IO_GPE0_STS_127_96_PME_B0           BIT13
#define B_ACPI_IO_GPE0_STS_127_96_ME_SCI           BIT12
#define B_ACPI_IO_GPE0_STS_127_96_PME              BIT11
#define B_ACPI_IO_GPE0_STS_127_96_BATLOW           BIT10
#define B_ACPI_IO_GPE0_STS_127_96_PCI_EXP          BIT9
#define B_ACPI_IO_GPE0_STS_127_96_RI               BIT8
#define B_ACPI_IO_GPE0_STS_127_96_SMB_WAK          BIT7
#define B_ACPI_IO_GPE0_STS_127_96_TC0SCI           BIT6
#define B_ACPI_IO_GPE0_STS_127_96_SWGPE            BIT2
#define B_ACPI_IO_GPE0_STS_127_96_HOT_PLUG         BIT1
#define N_ACPI_IO_GPE0_STS_127_96_GPIO_TIER_2      15
#define N_ACPI_IO_GPE0_STS_127_96_PME_B0           13
#define N_ACPI_IO_GPE0_STS_127_96_PME              11
#define N_ACPI_IO_GPE0_STS_127_96_BATLOW           10
#define N_ACPI_IO_GPE0_STS_127_96_PCI_EXP          9
#define N_ACPI_IO_GPE0_STS_127_96_RI               8
#define N_ACPI_IO_GPE0_STS_127_96_SMB_WAK          7
#define N_ACPI_IO_GPE0_STS_127_96_TC0SCI           6
#define N_ACPI_IO_GPE0_STS_127_96_SWGPE            2
#define N_ACPI_IO_GPE0_STS_127_96_HOT_PLUG         1

#define S_ACPI_IO_GPE0_EN_127_96                   4
#define B_ACPI_IO_GPE0_EN_127_96_WADT              BIT18
#define B_ACPI_IO_GPE0_EN_127_96_USB_CON_DSX_EN    BIT17
#define B_ACPI_IO_GPE0_EN_127_96_LAN_WAKE          BIT16
#define B_ACPI_IO_GPE0_EN_127_96_PME_B0            BIT13
#define B_ACPI_IO_GPE0_EN_127_96_ME_SCI            BIT12
#define B_ACPI_IO_GPE0_EN_127_96_PME               BIT11
#define B_ACPI_IO_GPE0_EN_127_96_BATLOW            BIT10
#define B_ACPI_IO_GPE0_EN_127_96_PCI_EXP           BIT9
#define B_ACPI_IO_GPE0_EN_127_96_RI                BIT8
#define B_ACPI_IO_GPE0_EN_127_96_TC0SCI            BIT6
#define B_ACPI_IO_GPE0_EN_127_96_SWGPE             BIT2
#define B_ACPI_IO_GPE0_EN_127_96_HOT_PLUG          BIT1
#define N_ACPI_IO_GPE0_EN_127_96_PME_B0            13
#define N_ACPI_IO_GPE0_EN_127_96_USB3              12
#define N_ACPI_IO_GPE0_EN_127_96_PME               11
#define N_ACPI_IO_GPE0_EN_127_96_BATLOW            10
#define N_ACPI_IO_GPE0_EN_127_96_PCI_EXP           9
#define N_ACPI_IO_GPE0_EN_127_96_RI                8
#define N_ACPI_IO_GPE0_EN_127_96_TC0SCI            6
#define N_ACPI_IO_GPE0_EN_127_96_SWGPE             2
#define N_ACPI_IO_GPE0_EN_127_96_HOT_PLUG          1


//
// TCO register I/O map
//
#define R_TCO_IO_RLD                                 0x0
#define R_TCO_IO_DAT_IN                              0x2
#define R_TCO_IO_DAT_OUT                             0x3
#define R_TCO_IO_TCO1_STS                            0x04
#define S_TCO_IO_TCO1_STS                            2
#define B_TCO_IO_TCO1_STS_DMISERR                    BIT12
#define B_TCO_IO_TCO1_STS_DMISMI                     BIT10
#define B_TCO_IO_TCO1_STS_DMISCI                     BIT9
#define B_TCO_IO_TCO1_STS_BIOSWR                     BIT8
#define B_TCO_IO_TCO1_STS_NEWCENTURY                 BIT7
#define B_TCO_IO_TCO1_STS_TIMEOUT                    BIT3
#define B_TCO_IO_TCO1_STS_TCO_INT                    BIT2
#define B_TCO_IO_TCO1_STS_SW_TCO_SMI                 BIT1
#define B_TCO_IO_TCO1_STS_NMI2SMI                    BIT0
#define N_TCO_IO_TCO1_STS_DMISMI                     10
#define N_TCO_IO_TCO1_STS_BIOSWR                     8
#define N_TCO_IO_TCO1_STS_NEWCENTURY                 7
#define N_TCO_IO_TCO1_STS_TIMEOUT                    3
#define N_TCO_IO_TCO1_STS_SW_TCO_SMI                 1
#define N_TCO_IO_TCO1_STS_NMI2SMI                    0

#define R_TCO_IO_TCO2_STS                            0x06
#define S_TCO_IO_TCO2_STS                            2
#define B_TCO_IO_TCO2_STS_SMLINK_SLV_SMI             BIT4
#define B_TCO_IO_TCO2_STS_BAD_BIOS                   BIT3
#define B_TCO_IO_TCO2_STS_BOOT                       BIT2
#define B_TCO_IO_TCO2_STS_SECOND_TO                  BIT1
#define B_TCO_IO_TCO2_STS_INTRD_DET                  BIT0
#define N_TCO_IO_TCO2_STS_INTRD_DET                  0

#define R_TCO_IO_TCO1_CNT                            0x08
#define S_TCO_IO_TCO1_CNT                            2
#define B_TCO_IO_TCO1_CNT_LOCK                       BIT12
#define B_TCO_IO_TCO1_CNT_TMR_HLT                    BIT11
#define B_TCO_IO_TCO1_CNT_NMI2SMI_EN                 BIT9
#define B_TCO_IO_TCO1_CNT_NMI_NOW                    BIT8
#define N_TCO_IO_TCO1_CNT_NMI2SMI_EN                 9

#define R_TCO_IO_TCO2_CNT                            0x0A
#define S_TCO_IO_TCO2_CNT                            2
#define B_TCO_IO_TCO2_CNT_OS_POLICY                  0x0030
#define B_TCO_IO_TCO2_CNT_GPI11_ALERT_DISABLE        0x0008
#define B_TCO_IO_TCO2_CNT_INTRD_SEL                  0x0006
#define N_TCO_IO_TCO2_CNT_INTRD_SEL                  2

#define R_TCO_IO_MESSAGE1                            0x0C
#define R_TCO_IO_MESSAGE2                            0x0D
#define R_TCO_IO_TWDS                                0x0E           ///< TCO_WDSTATUS register.
#define R_TCO_IO_LE                                  0x10           ///< LEGACY_ELIM register
#define B_TCO_IO_LE_IRQ12_CAUSE                      BIT1
#define B_TCO_IO_LE_IRQ1_CAUSE                       BIT0
#define R_TCO_IO_TMR                                 0x12

//
// PWRM Registers
//
#define B_PMC_PWRM_PRSTS_VE_WD_TMR_STS                      BIT7                        ///< VE Watchdog Timer Status
#define B_PMC_PWRM_PRSTS_WOL_OVR_WK_STS                     BIT5
#define B_PMC_PWRM_PRSTS_FIELD_1                            BIT4
#define B_PMC_PWRM_PRSTS_ME_WAKE_STS                        BIT0
#define B_PMC_PWRM_CFG_ALLOW_24_OSC_SD                      BIT29                       ///< Allow 24MHz Crystal Oscillator Shutdown
#define B_PMC_PWRM_CFG_DBG_MODE_LOCK                        BIT27                       ///< Debug Mode Lock
#define B_PMC_PWRM_CFG_ALLOW_USB2_CORE_PG                   BIT25                       ///< Allow USB2 Core Power Gating
#define B_PMC_PWRM_CFG_PMCREAD_DISABLE                      BIT22                       ///< Disable Reads to PMC
#define B_PMC_PWRM_CFG_RTC_DS_WAKE_DIS                      BIT21                       ///< RTC Wake from Deep S4/S5 Disable
#define B_PMC_PWRM_CFG_SSMAW_MASK                           (BIT19 | BIT18)             ///< SLP_SUS# Min Assertion Width
#define V_PMC_PWRM_CFG_SSMAW_4S                             (BIT19 | BIT18)             ///< 4 seconds
#define V_PMC_PWRM_CFG_SSMAW_1S                             BIT19                       ///< 1 second
#define V_PMC_PWRM_CFG_SSMAW_0_5S                           BIT18                       ///< 0.5 second (500ms)
#define V_PMC_PWRM_CFG_SSMAW_0S                             0                           ///< 0 second
#define B_PMC_PWRM_CFG_SAMAW_MASK                           (BIT17 | BIT16)             ///< SLP_A# Min Assertion Width
#define V_PMC_PWRM_CFG_SAMAW_2S                             (BIT17 | BIT16)             ///< 2 seconds
#define V_PMC_PWRM_CFG_SAMAW_98ms                           BIT17                       ///< 98ms
#define V_PMC_PWRM_CFG_SAMAW_4S                             BIT16                       ///< 4 seconds
#define V_PMC_PWRM_CFG_SAMAW_0S                             0                           ///< 0 second
#define B_PMC_PWRM_CFG_RPCD_MASK                            (BIT9 | BIT8)               ///< Reset Power Cycle Duration
#define V_PMC_PWRM_CFG_RPCD_1S                              (BIT9 | BIT8)               ///< 1-2 seconds
#define V_PMC_PWRM_CFG_RPCD_2S                              BIT9                        ///< 2-3 seconds
#define V_PMC_PWRM_CFG_RPCD_3S                              BIT8                        ///< 3-4 seconds
#define V_PMC_PWRM_CFG_RPCD_4S                              0                           ///< 4-5 seconds (Default)
#define B_PMC_PWRM_CFG_TIMING_TPCH25                        (BIT1 | BIT0)               ///< tPCH25 timing
#define B_PMC_PWRM_PCH_PM_STS_PMC_MSG_FULL_STS              BIT24                       ///< MTPMC transport mechanism full indication
#define R_PMC_PWRM_MTPMC                                    0x20                        ///< Message to PMC
#define V_PMC_PWRM_MTPMC_COMMAND_PG_LANE_0_15               0xE                         ///< Command to override lanes 0-15 power gating
#define V_PMC_PWRM_MTPMC_COMMAND_PG_LANE_16_31              0xF                         ///< Command to override lanes 16-31 power gating
#define B_PMC_PWRM_MTPMC_PG_CMD_DATA                        0xFFFF0000                  ///< Data part of PowerGate Message to PMC
#define N_PMC_PWRM_MTPMC_PG_CMD_DATA                        16
#define B_PMC_PWRM_S3DC_GATE_SUS                            BIT1                        ///< Deep S3 Enable in DC Mode
#define B_PMC_PWRM_S3AC_GATE_SUS                            BIT0                        ///< Deep S3 Enable in AC Mode
#define B_PMC_PWRM_S4DC_GATE_SUS                            BIT1                        ///< Deep S4 Enable in DC Mode
#define B_PMC_PWRM_S4AC_GATE_SUS                            BIT0                        ///< Deep S4 Enable in AC Mode
#define B_PMC_PWRM_S5DC_GATE_SUS                            BIT15                       ///< Deep S5 Enable in DC Mode
#define B_PMC_PWRM_S5AC_GATE_SUS                            BIT14                       ///< Deep S5 Enable in AC Mode
#define B_PMC_PWRM_DSX_CFG_WAKE_PIN_DSX_EN                  BIT2                        ///< WAKE# Pin DeepSx Enable
#define B_PMC_PWRM_DSX_CFG_ACPRES_PD_DSX_DIS                BIT1                        ///< AC_PRESENT pin pulldown in DeepSx disable
#define B_PMC_PWRM_DSX_CFG_LAN_WAKE_EN                      BIT0                        ///< LAN_WAKE Pin DeepSx Enable
#define B_PMC_PWRM_CFG2_PBOP                                (BIT31 | BIT30 | BIT29)     ///< Power Button Override Period (PBOP)
#define N_PMC_PWRM_CFG2_PBOP                                29                          ///< Power Button Override Period (PBOP)
#define B_PMC_PWRM_CFG2_PB_DIS                              BIT28                       ///< Power Button Native Mode Disable (PB_DIS)
#define B_PMC_PWRM_CFG2_DRAM_RESET_CTL                      BIT26                       ///< DRAM RESET# control
#define N_PMC_PWRM_CFG2_DRAM_RESET_CTL                      26
#define B_PMC_PWRM_PMSYNC_TPR_CONFIG_LOCK                   BIT31
#define B_PMC_PWRM_PMSYNC_PCH2CPU_TT_EN                     BIT26
#define B_PMC_PWRM_PMSYNC_PCH2CPU_TT_STATE                  (BIT25 | BIT24)
#define N_PMC_PWRM_PMSYNC_PCH2CPU_TT_STATE                  24
#define V_PMC_PWRM_PMSYNC_PCH2CPU_TT_STATE_1                1
#define B_PMC_PWRM_PMSYNC_PM_SYNC_LOCK                      BIT15                       ///< PM_SYNC Configuration Lock
#define B_PMC_PWRM_PMSYNC_GPIO_D_SEL                        BIT11
#define B_PMC_PWRM_PMSYNC_GPIO_C_SEL                        BIT10
#define B_PMC_PWRM_CFG3_DSX_WLAN_PP_EN                      BIT16                       ///< Deep-Sx WLAN Phy Power Enable
#define B_PMC_PWRM_CFG3_HOST_WLAN_PP_EN                     BIT17                       ///< Host Wireless LAN Phy Power Enable
#define B_PMC_PWRM_CFG3_PWRG_LOCK                           BIT2                        ///< Lock power gating override messages
#define B_PMC_PWRM_CFG4_CEC_EN                              BIT31                       ///< CEC_EN
#define B_PMC_PWRM_CFG4_U2_PHY_PG_EN                        BIT30                       ///< USB2 PHY SUS Well Power Gating Enable
#define B_PMC_PWRM_CFG4_SLPS0_PSON_TMR                      (BIT29 | BIT28 | BIT27 | BIT26 | BIT25 | BIT24 | BIT23)  ///< SLPS0_PSON_TMR
#define N_PMC_PWRM_CFG4_SLPS0_PSON_TMR                      23
#define V_PMC_PWRM_CFG4_SLPS0_PSON_TMR_5MS                  0xA
#define B_PMC_PWRM_CFG4_PSON_SLPS0_TMR                      (BIT22 | BIT21 | BIT20 | BIT19 | BIT18)                  ///< PSON_SLPS0_TMR
#define N_PMC_PWRM_CFG4_PSON_SLPS0_TMR                      18
#define V_PMC_PWRM_CFG4_PSON_SLPS0_TMR_100MS                0x5
#define B_PMC_PWRM_CFG4_CPU_IOVR_RAMP_DUR                   (0x000001FF)                ///< CPU I/O VR Ramp Duration, [8:0]
#define N_PMC_PWRM_CFG4_CPU_IOVR_RAMP_DUR                   0
#define V_PMC_PWRM_CFG4_CPU_IOVR_RAMP_DUR_70US              0x007
#define V_PMC_PWRM_CFG4_CPU_IOVR_RAMP_DUR_240US             0x018
#define N_PMC_PWRM_CPU_EPOC_DATA_17                         17
#define B_PMC_PWRM_VR_MISC_CTL_VIDSOVEN                     BIT3
#define B_PMC_PWRM_GPIO_CFG_GPE0_DW2                        (BIT11 | BIT10 | BIT9 | BIT8)
#define N_PMC_PWRM_GPIO_CFG_GPE0_DW2                        8
#define B_PMC_PWRM_GPIO_CFG_GPE0_DW1                        (BIT7 | BIT6 | BIT5 | BIT4)
#define N_PMC_PWRM_GPIO_CFG_GPE0_DW1                        4
#define B_PMC_PWRM_GPIO_CFG_GPE0_DW0                        (BIT3 | BIT2 | BIT1 | BIT0)
#define N_PMC_PWRM_GPIO_CFG_GPE0_DW0                        0
#define B_PMC_PWRM_ACPI_TMR_DIS                             BIT1
#define B_PMC_PWRM_MODPHY_PM_CFG2_MLSPDDGE                  BIT30    ///< ModPHY Lane SUS Power Domain Dynamic Gating Enable
#define B_PMC_PWRM_MODPHY_PM_CFG2_EMFC                      BIT29    ///< Enable ModPHY FET Control
#define B_PMC_PWRM_MODPHY_PM_CFG2_EFRT                      (BIT28 | BIT27 | BIT26 | BIT25 | BIT24)    ///< External FET Ramp Time
#define N_PMC_PWRM_MODPHY_PM_CFG2_EFRT                      24
#define V_PMC_PWRM_MODPHY_PM_CFG2_EFRT_200US                0x0A
#define B_PMC_PWRM_MODPHY_PM_CFG2_ASLOR_UFS                 BIT16    ///< UFS ModPHY SPD SPD Override
#define B_PMC_PWRM_MODPHY_PM_CFG3_MSPDRTREQ_UFS             BIT16    ///< UFS ModPHY SPD RT Request
#define B_PMC_PWRM_MODPHY_PM_CFG3_MSPDRTREQ_XDCI            BIT15    ///< xDCI ModPHY SPD RT Request
#define B_PMC_PWRM_MODPHY_PM_CFG3_MSPDRTREQ_XHCI            BIT14    ///< xHCI ModPHY SPD RT Request
#define B_PMC_PWRM_MODPHY_PM_CFG3_MSPDRTREQ_GBE             BIT13    ///< GbE ModPHY SPD RT Request
#define B_PMC_PWRM_MODPHY_PM_CFG3_MSPDRTREQ_SATA            BIT12    ///< SATA ModPHY SPD RT Request
#define B_PMC_PWRM_CPPM_CG_POLXA_CPPM_GX_QUAL               BIT30             ///< CPPM Shutdown Qualifier Enable for Clock Source Group X
#define B_PMC_PWRM_CPPM_CG_POLXA_LTR_GX_THRESH              (0x000001FF)      ///< LTR Threshold for Clock Source Group X, [8:0]
#define B_PMC_PWRM_CPPM_MPG_POL1A_CPPM_MODPHY_QUAL          BIT30             ///< CPPM Shutdown Qualifier Enable for ModPHY
#define B_PMC_PWRM_CPPM_MPG_POL1A_LT_MODPHY_SEL             BIT29             ///< ASLT/PLT Selection for ModPHY
#define B_PMC_PWRM_CPPM_MPG_POL1A_LTR_MODPHY_THRESH         (0x000001FF)      ///< LTR Threshold for ModPHY, [8:0]
#define B_PMC_PWRM_CS_SD_CTL1_CS5_CTL_CFG                   (BIT22 | BIT21 | BIT20)    ///< Clock Source 5 Control Configuration
#define N_PMC_PWRM_CS_SD_CTL1_CS5_CTL_CFG                   20
#define B_PMC_PWRM_CS_SD_CTL1_CS1_CTL_CFG                   (BIT2 | BIT1 | BIT0)       ///< Clock Source 1 Control Configuration
#define N_PMC_PWRM_CS_SD_CTL1_CS1_CTL_CFG                   0
#define B_PMC_PWRM_SW_PG_CTRL_LOCK                          BIT31
#define B_PMC_PWRM_DFX_SW_PG_CTRL                           BIT0
#define B_PMC_PWRM_ST_PG_FDIS_PMC_1_ST_FDIS_LK              BIT31 ///< Static Function Disable Lock (ST_FDIS_LK)
#define B_PMC_PWRM_ST_PG_FDIS_PMC_1_CAM_FDIS_PMC            BIT6  ///< Camera Function Disable (PMC Version) (CAM_FDIS_PMC)
#define B_PMC_PWRM_ST_PG_FDIS_PMC_1_ISH_FDIS_PMC            BIT5  ///< SH Function Disable (PMC Version) (ISH_FDIS_PMC)
#define B_PMC_PWRM_ST_PG_FDIS_PMC_1_GBE_FDIS_PMC            BIT0  ///< GBE Function Disable (PMC Version) (GBE_FDIS_PMC)
#define R_PMC_PWRM_ST_PG_FDIS_PMC_2                         0x624 ///< Static Function Disable Control Register 2
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO                0x7FF ///< SerialIo Devices Disable Mask
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_GSPI2_FDIS_PMC BIT11 ///< SerialIo Controller GSPI Device 2 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_GSPI1_FDIS_PMC BIT10 ///< SerialIo Controller GSPI Device 1 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_GSPI0_FDIS_PMC BIT9  ///< SerialIo Controller GSPI Device 0 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_UART2_FDIS_PMC BIT8  ///< SerialIo Controller UART Device 2 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_UART1_FDIS_PMC BIT7  ///< SerialIo Controller UART Device 1 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_UART0_FDIS_PMC BIT6  ///< SerialIo Controller UART Device 0 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C5_FDIS_PMC  BIT5  ///< SerialIo Controller I2C Device 5 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C4_FDIS_PMC  BIT4  ///< SerialIo Controller I2C Device 4 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C3_FDIS_PMC  BIT3  ///< SerialIo Controller I2C Device 3 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C2_FDIS_PMC  BIT2  ///< SerialIo Controller I2C Device 2 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C1_FDIS_PMC  BIT1  ///< SerialIo Controller I2C Device 1 Function Disable
#define B_PMC_PWRM_ST_PG_FDIS_PMC_2_SERIALIO_I2C0_FDIS_PMC  BIT0  ///< SerialIo Controller I2C Device 0 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_SCC_FDIS_PMC               BIT25 ///< SCC Function Disable. This is only avaiable in B0 onward.
#define B_PMC_PWRM_NST_PG_FDIS_1_XDCI_FDIS_PMC              BIT24 ///< XDCI Function Disable. This is only avaiable in B0 onward.
#define B_PMC_PWRM_NST_PG_FDIS_1_ADSP_FDIS_PMC              BIT23 ///< ADSP Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_SATA_FDIS_PMC              BIT22 ///< SATA Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_C3_FDIS_PMC           BIT13 ///< PCIe Controller C Port 3 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_C2_FDIS_PMC           BIT12 ///< PCIe Controller C Port 2 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_C1_FDIS_PMC           BIT11 ///< PCIe Controller C Port 1 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_C0_FDIS_PMC           BIT10 ///< PCIe Controller C Port 0 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_B3_FDIS_PMC           BIT9  ///< PCIe Controller B Port 3 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_B2_FDIS_PMC           BIT8  ///< PCIe Controller B Port 2 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_B1_FDIS_PMC           BIT7  ///< PCIe Controller B Port 1 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_B0_FDIS_PMC           BIT6  ///< PCIe Controller B Port 0 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_A3_FDIS_PMC           BIT5  ///< PCIe Controller A Port 3 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_A2_FDIS_PMC           BIT4  ///< PCIe Controller A Port 2 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_A1_FDIS_PMC           BIT3  ///< PCIe Controller A Port 1 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_PCIE_A0_FDIS_PMC           BIT2  ///< PCIe Controller A Port 0 Function Disable
#define B_PMC_PWRM_NST_PG_FDIS_1_XHCI_FDIS_PMC              BIT0  ///< XHCI Function Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_SPC_SS_DIS                 BIT25 ///< SPC Fuse Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_SPB_SS_DIS                 BIT24 ///< SPB Fuse Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_SPA_SS_DIS                 BIT23 ///< SPA Fuse Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_PSTH_FUSE_SS_DIS           BIT21 ///< PSTH Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_DMI_FUSE_SS_DIS            BIT20 ///< DMI Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_OTG_FUSE_SS_DIS            BIT19 ///< OTG Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_XHCI_SS_DIS                BIT18 ///< XHCI Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_FIA_FUSE_SS_DIS            BIT17 ///< FIA Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_DSP_FUSE_SS_DIS            BIT16 ///< DSP Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_SATA_FUSE_SS_DIS           BIT15 ///< SATA Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_ICC_FUSE_SS_DIS            BIT14 ///< ICC Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_LPC_FUSE_SS_DIS            BIT13 ///< LPC Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_RTC_FUSE_SS_DIS            BIT12 ///< RTC Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_P2S_FUSE_SS_DIS            BIT11 ///< P2S Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_TRSB_FUSE_SS_DIS           BIT10 ///< TRSB Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_SMB_FUSE_SS_DIS            BIT9  ///< SMB Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_ITSS_FUSE_SS_DIS           BIT8  ///< ITSS Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_SERIALIO_FUSE_SS_DIS       BIT6  ///< SerialIo Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_P2D_FUSE_SS_DIS            BIT3  ///< P2D Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_ISH_FUSE_SS_DIS            BIT1  ///< ISH Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_2_GBE_FUSE_SS_DIS            BIT0  ///< GBE Fuse or Soft Strap Disable
#define R_PMC_PWRM_FUSE_DIS_RD_3                            0x648 ///< Static PG Fuse and Soft Strap Disable Read Register 3
#define B_PMC_PWRM_FUSE_DIS_RD_3_PNCRA3_FUSE_SS_DIS         BIT3  ///< PNCRA3 Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_3_PNCRA2_FUSE_SS_DIS         BIT2  ///< PNCRA2 Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_3_PNCRA1_FUSE_SS_DIS         BIT1  ///< PNCRA1 Fuse or Soft Strap Disable
#define B_PMC_PWRM_FUSE_DIS_RD_3_PNCRA_FUSE_SS_DIS          BIT0  ///< PNCRA Fuse or Soft Strap Disable


#endif

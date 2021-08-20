/** @file
  Register definition for PSF component

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
#ifndef _PCH_REGS_PSF_H_
#define _PCH_REGS_PSF_H_

//
// Private chipset register (Memory space) offset definition
// The PCR register defines is used for PCR MMIO programming and PCH SBI programming as well.
//

#define R_PCH_PSF_PCR_BUS_SHADOW_RS3                    0x0008                  ///< RS3 bus shadow register
//
// PSFx segment registers
//
#define R_PCH_PSF_PCR_GLOBAL_CONFIG                     0x4000                  ///< PSF Segment Global Configuration Register
#define B_PCH_PSF_PCR_GLOBAL_CONFIG_ENPCG               BIT12
#define B_PCH_PSF_PCR_GLOBAL_CONFIG_ENTCG               BIT4
#define B_PCH_PSF_PCR_GLOBAL_CONFIG_ENLCG               BIT3
#define R_PCH_PSF_PCR_ROOTSPACE_CONFIG_RS0              0x4014                  ///< PSF Segment Rootspace Configuration Register
#define R_PCH_PSF_PCR_ROOTSPACE_CONFIG_RS1              0x4018
#define B_PCH_PSF_PCR_ROOTSPACE_CONFIG_RSX_ENADDRP2P    BIT1
#define B_PCH_PSF_PCR_ROOTSPACE_CONFIG_RSX_VTDEN        BIT0

#define S_PCH_PSFX_PCR_DEV_GNTCNT_RELOAD_DGCR                4
#define S_PCH_PSFX_PCR_TARGET_GNTCNT_RELOAD                  4
#define B_PCH_PSFX_PCR_DEV_GNTCNT_RELOAD_DGCR_GNT_CNT_RELOAD 0x1F
#define B_PCH_PSFX_PCR_TARGET_GNTCNT_RELOAD_GNT_CNT_RELOAD   0x1F

#define N_PCH_PSFX_PCR_MC_CONTROL_MCASTX_NUMMC          1
#define B_PCH_PSFX_PCR_MC_CONTROL_MCASTX_MULTCEN        BIT0

//
// PSFx PCRs definitions
//
#define R_PCH_PSFX_PCR_T0_SHDW_BAR0                     0                       ///< PCI BAR0
#define R_PCH_PSFX_PCR_T0_SHDW_BAR1                     0x04                    ///< PCI BAR1
#define R_PCH_PSFX_PCR_T0_SHDW_BAR2                     0x08                    ///< PCI BAR2
#define R_PCH_PSFX_PCR_T0_SHDW_BAR3                     0x0C                    ///< PCI BAR3
#define R_PCH_PSFX_PCR_T0_SHDW_BAR4                     0x10                    ///< PCI BAR4
#define R_PCH_PSFX_PCR_T0_SHDW_PCIEN                    0x1C                    ///< PCI configuration space enable bits
#define N_PCH_PSFX_PCR_T0_SHDW_PCIEN_BARXDIS            16
#define B_PCH_PSFX_PCR_T0_SHDW_PCIEN_BAR0DIS            BIT16                   ///< Disable BAR0
#define B_PCH_PSFX_PCR_T0_SHDW_PCIEN_BAR1DIS            BIT17                   ///< Disable BAR1
#define B_PCH_PSFX_PCR_T0_SHDW_PCIEN_BAR2DIS            BIT18                   ///< Disable BAR2
#define B_PCH_PSFX_PCR_T0_SHDW_PCIEN_BAR3DIS            BIT19                   ///< Disable BAR3
#define B_PCH_PSFX_PCR_T0_SHDW_PCIEN_BAR4DIS            BIT20                   ///< Disable BAR4
#define B_PCH_PSFX_PCR_T0_SHDW_PCIEN_BAR5DIS            BIT21                   ///< Disable BAR5
#define B_PCH_PSFX_PCR_T0_SHDW_PCIEN_FUNDIS             BIT8                    ///< Function disable
#define B_PCH_PSFX_PCR_T0_SHDW_PCIEN_MEMEN              BIT1                    ///< Memory decoding enable
#define B_PCH_PSFX_PCR_T0_SHDW_PCIEN_IOEN               BIT0                    ///< IO decoding enable
#define R_PCH_PSFX_PCR_T0_SHDW_PMCSR                    0x20                    ///< PCI power management configuration
#define B_PCH_PSFX_PCR_T0_SHDW_PMCSR_PWRST              (BIT1 | BIT0)           ///< Power status
#define R_PCH_PSFX_PCR_T0_SHDW_CFG_DIS                  0x38                    ///< PCI configuration disable
#define B_PCH_PSFX_PCR_T0_SHDW_CFG_DIS_CFGDIS           BIT0                    ///< config disable

#define R_PCH_PSFX_PCR_T1_SHDW_PCIEN                    0x3C                    ///< PCI configuration space enable bits
#define B_PCH_PSFX_PCR_T1_SHDW_PCIEN_FUNDIS             BIT8                    ///< Function disable
#define B_PCH_PSFX_PCR_T1_SHDW_PCIEN_MEMEN              BIT1                    ///< Memory decoding enable
#define B_PCH_PSFX_PCR_T1_SHDW_PCIEN_IOEN               BIT0                    ///< IO decoding enable

#define B_PCH_PSFX_PCR_TX_AGENT_FUNCTION_CONFIG_DEVICE    0x01F0                 ///< device number
#define N_PCH_PSFX_PCR_TX_AGENT_FUNCTION_CONFIG_DEVICE    4
#define B_PCH_PSFX_PCR_TX_AGENT_FUNCTION_CONFIG_FUNCTION  (BIT3 | BIT2 | BIT1)   ///< function number
#define N_PCH_PSFX_PCR_TX_AGENT_FUNCTION_CONFIG_FUNCTION  1

#define B_PCH_PSFX_PCR_TARGET_CHANNELID                 0xFF
#define B_PCH_PSFX_PCR_TARGET_PORTID                    0x7F00
#define N_PCH_PSFX_PCR_TARGET_PORTID                    8
#define B_PCH_PSFX_PCR_TARGET_PORTGROUPID               BIT15
#define N_PCH_PSFX_PCR_TARGET_PORTGROUPID               15
#define B_PCH_PSFX_PCR_TARGET_PSFID                     0xFF0000
#define N_PCH_PSFX_PCR_TARGET_PSFID                     16
#define B_PCH_PSFX_PCR_TARGET_CHANMAP                   BIT31

#define V_PCH_PSFX_PCR_DEV_GNTCNT_MAX                   4

//PSFX Multicast Message Configuration
#define R_PCH_PSFX_PCR_RC_OWNER_RS0                     0x4008
#define V_PCH_PSFX_PCR_RC_OWNER_PMT                     0x50201

#endif

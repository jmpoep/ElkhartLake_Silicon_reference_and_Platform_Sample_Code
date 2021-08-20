/** @file
  Register names for GbE device

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
  Copyright 1999 - 2018 Intel Corporation.

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
#ifndef _GBE_REGS_H_
#define _GBE_REGS_H_

//
// Gigabit Ethernet LAN Controller configuration registers (D31:F6)
//
#define PCI_DEVICE_NUMBER_GBE     31
#define PCI_FUNCTION_NUMBER_GBE   6

#define R_GBE_CFG_MBARA               0x10
#define B_GBE_CFG_MBARA_BA            0xFFFE0000
#define N_GBE_CFG_MBARA_ALIGN         17
#define R_GBE_CFG_LTR_CAP             0xA8
#define R_GBE_CFG_CLIST1              0xC8
#define B_GBE_CFG_CLIST1_NEXT         0xFF00
#define B_GBE_CFG_CLIST1_CID          0x00FF
#define R_GBE_CFG_PMC                 0xCA
#define B_GBE_CFG_PMC_PMES            0xF800
#define B_GBE_CFG_PMC_D2S             BIT10
#define B_GBE_CFG_PMC_D1S             BIT9
#define B_GBE_CFG_PMC_AC              (BIT8 | BIT7 | BIT6)
#define B_GBE_CFG_PMC_DSI             BIT5
#define B_GBE_CFG_PMC_PMEC            BIT3
#define B_GBE_CFG_PMC_VS              (BIT2 | BIT1 | BIT0)
#define R_GBE_CFG_PMCS                0xCC
#define B_GBE_CFG_PMCS_PMES           BIT15
#define B_GBE_CFG_PMCS_DSC            (BIT14 | BIT13)
#define B_GBE_CFG_PMCS_DSL            0x1E00
#define V_GBE_CFG_PMCS_DSL0           0x0000
#define V_GBE_CFG_PMCS_DSL3           0x0600
#define V_GBE_CFG_PMCS_DSL4           0x0800
#define V_GBE_CFG_PMCS_DSL7           0x0E00
#define V_GBE_CFG_PMCS_DSL8           0x1000
#define B_GBE_CFG_PMCS_PMEE           BIT8
#define B_GBE_CFG_PMCS_PS             (BIT1 | BIT0)
#define V_GBE_CFG_PMCS_PS0            0x00
#define V_GBE_CFG_PMCS_PS3            0x03
#define R_GBE_CFG_DR                  0xCF
#define B_GBE_CFG_DR                  0xFF
#define R_GBE_CFG_CLIST2              0xD0
#define B_GBE_CFG_CLIST2_NEXT         0xFF00
#define B_GBE_CFG_CLIST2_CID          0x00FF
#define R_GBE_CFG_MCTL                0xD2
#define B_GBE_CFG_MCTL_CID            BIT7
#define B_GBE_CFG_MCTL_MME            (BIT6 | BIT5 | BIT4)
#define B_GBE_CFG_MCTL_MMC            (BIT3 | BIT2 | BIT1)
#define B_GBE_CFG_MCTL_MSIE           BIT0
#define R_GBE_CFG_MADDL               0xD4
#define B_GBE_CFG_MADDL               0xFFFFFFFF
#define R_GBE_CFG_MADDH               0xD8
#define B_GBE_CFG_MADDH               0xFFFFFFFF
#define R_GBE_CFG_MDAT                0xDC
#define B_GBE_CFG_MDAT                0xFFFFFFFF
#define R_GBE_CFG_FLRCAP              0xE0
#define B_GBE_CFG_FLRCAP_NEXT         0xFF00
#define B_GBE_CFG_FLRCAP_CID          0x00FF
#define V_GBE_CFG_FLRCAP_CID_SSEL0    0x13
#define V_GBE_CFG_FLRCAP_CID_SSEL1    0x09
#define R_GBE_CFG_FLRCLV              0xE2
#define B_GBE_CFG_FLRCLV_FLRC_SSEL0   BIT9
#define B_GBE_CFG_FLRCLV_TXP_SSEL0    BIT8
#define B_GBE_CFG_FLRCLV_VSCID_SSEL1  0xF000
#define B_GBE_CFG_FLRCLV_CAPVER_SSEL1 0x0F00
#define B_GBE_CFG_FLRCLV_CAPLNG       0x00FF
#define R_GBE_CFG_DEVCTRL             0xE4
#define B_GBE_CFG_DEVCTRL             BIT0
#define R_GBE_CFG_CPCE                0x80
#define B_GBE_CFG_CPCE_HAE            BIT5
#define B_GBE_CFG_CPCE_SE             BIT3
#define B_GBE_CFG_CPCE_D3HE           BIT2
#define B_GBE_CFG_CPCE_I3E            BIT1
#define B_GBE_CFG_CPCE_PCMCRE         BIT0
#define R_GBE_CFG_CD0I3               0x84
#define B_GBE_CFG_CD0I3_RR            BIT3
#define B_GBE_CFG_CD0I3_D0I3          BIT2
#define R_GBE_CFG_CLCTL               0x94
#define R_GBE_CFG_LANDISCTRL          0xA0
#define B_GBE_CFG_LANDISCTRL_DISABLE  BIT0
#define R_GBE_CFG_LOCKLANDIS          0xA4
#define B_GBE_CFG_LOCKLANDIS_LOCK     BIT0
//
// Gigabit Ethernet LAN Capabilities and Status Registers (Memory space)
//
#define R_GBE_MEM_CSR_CTRL                 0
#define B_GBE_MEM_CSR_CTRL_MEHE            BIT19
#define R_GBE_MEM_CSR_STRAP                0x000C
#define B_GBE_MEM_CSR_STRAP_NVM_VALID      BIT11
#define R_GBE_MEM_CSR_FEXTNVM6             0x0010
#define B_GBE_MEM_CSR_FEXTNVM6_K1OFF_EN    BIT31
#define R_GBE_MEM_CSR_CTRL_EXT             0x0018
#define B_GBE_MEM_CSR_CTRL_EXT_FORCE_SMB   BIT11
#define R_GBE_MEM_CSR_MDIC                 0x0020
#define B_GBE_MEM_CSR_MDIC_RB              BIT28
#define B_GBE_MEM_CSR_MDIC_DATA            0xFFFF
#define R_GBE_MEM_CSR_FEXT                 0x002C
#define B_GBE_MEM_CSR_FEXT_WOL             BIT30
#define B_GBE_MEM_CSR_FEXT_WOL_VALID       BIT31
#define R_GBE_MEM_CSR_EXTCNF_CTRL          0x0F00
#define B_GBE_MEM_CSR_EXTCNF_CTRL_SWFLAG   BIT5
#define B_GBE_MEM_CSR_EXTCNF_K1OFF_EN      BIT8
#define R_GBE_MEM_CSR_PHY_CTRL             0x0F10
#define B_GBE_MEM_CSR_PHY_CTRL_GGD         BIT6
#define B_GBE_MEM_CSR_PHY_CTRL_GBEDIS      BIT3
#define B_GBE_MEM_CSR_PHY_CTRL_LPLUND      BIT2
#define B_GBE_MEM_CSR_PHY_CTRL_LPLUD       BIT1
#define R_GBE_MEM_CSR_PBECCSTS             0x100C
#define B_GBE_MEM_CSR_PBECCSTS_ECC_EN      BIT16
#define R_GBE_MEM_CSR_RAL                  0x5400
#define R_GBE_MEM_CSR_RAH                  0x5404
#define B_GBE_MEM_CSR_RAH_RAH              0x0000FFFF
#define R_GBE_MEM_CSR_WUC                  0x5800
#define B_GBE_MEM_CSR_WUC_APME             BIT0

#endif

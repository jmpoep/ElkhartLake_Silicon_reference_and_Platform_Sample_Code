/** @file
  Register names for PCH PCI-E root port devices

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
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _PCH_REGS_PCIE_H_
#define _PCH_REGS_PCIE_H_

#define V_PCH_PCIE_CFG_VENDOR_ID                  V_PCH_INTEL_VENDOR_ID


#define R_PCH_PCIE_CFG_INTR_BCTRL                     0x3C

#define R_PCH_PCIE_CFG_CLIST                          0x40
#define R_PCH_PCIE_CFG_XCAP                           (R_PCH_PCIE_CFG_CLIST + R_PCIE_XCAP_OFFSET)
#define R_PCH_PCIE_CFG_DCAP                           (R_PCH_PCIE_CFG_CLIST + R_PCIE_DCAP_OFFSET)
#define R_PCH_PCIE_CFG_DCTL                           (R_PCH_PCIE_CFG_CLIST + R_PCIE_DCTL_OFFSET)
#define R_PCH_PCIE_CFG_DSTS                           (R_PCH_PCIE_CFG_CLIST + R_PCIE_DSTS_OFFSET)
#define R_PCH_PCIE_CFG_LCAP                           (R_PCH_PCIE_CFG_CLIST + R_PCIE_LCAP_OFFSET)
#define B_PCH_PCIE_CFG_LCAP_PN                        0xFF000000
#define N_PCH_PCIE_CFG_LCAP_PN                        24
#define R_PCH_PCIE_CFG_LCTL                           (R_PCH_PCIE_CFG_CLIST + R_PCIE_LCTL_OFFSET)
#define R_PCH_PCIE_CFG_LSTS                           (R_PCH_PCIE_CFG_CLIST + R_PCIE_LSTS_OFFSET)
#define R_PCH_PCIE_CFG_SLCAP                          (R_PCH_PCIE_CFG_CLIST + R_PCIE_SLCAP_OFFSET)
#define R_PCH_PCIE_CFG_SLCTL                          (R_PCH_PCIE_CFG_CLIST + R_PCIE_SLCTL_OFFSET)
#define R_PCH_PCIE_CFG_SLSTS                          (R_PCH_PCIE_CFG_CLIST + R_PCIE_SLSTS_OFFSET)
#define R_PCH_PCIE_CFG_RCTL                           (R_PCH_PCIE_CFG_CLIST + R_PCIE_RCTL_OFFSET)
#define R_PCH_PCIE_CFG_RSTS                           (R_PCH_PCIE_CFG_CLIST + R_PCIE_RSTS_OFFSET)
#define R_PCH_PCIE_CFG_DCAP2                          (R_PCH_PCIE_CFG_CLIST + R_PCIE_DCAP2_OFFSET)
#define R_PCH_PCIE_CFG_DCTL2                          (R_PCH_PCIE_CFG_CLIST + R_PCIE_DCTL2_OFFSET)
#define R_PCH_PCIE_CFG_LCTL2                          (R_PCH_PCIE_CFG_CLIST + R_PCIE_LCTL2_OFFSET)
#define R_PCH_PCIE_CFG_LSTS2                          (R_PCH_PCIE_CFG_CLIST + R_PCIE_LSTS2_OFFSET)

#define R_PCH_PCIE_CFG_DCTL_DSTS                      0x48

#define R_PCH_PCIE_CFG_DCTL2_DSTS2                    0x68

#define R_PCH_PCIE_CFG_MID                            0x80
#define S_PCH_PCIE_CFG_MID                            2
#define R_PCH_PCIE_CFG_MC                             0x82
#define S_PCH_PCIE_CFG_MC                             2
#define R_PCH_PCIE_CFG_MA                             0x84
#define S_PCH_PCIE_CFG_MA                             4
#define R_PCH_PCIE_CFG_MD                             0x88
#define S_PCH_PCIE_CFG_MD                             2

#define R_PCH_PCIE_CFG_SVCAP                          0x90
#define S_PCH_PCIE_CFG_SVCAP                          2
#define R_PCH_PCIE_CFG_SVID                           0x94
#define S_PCH_PCIE_CFG_SVID                           4

#define R_PCH_PCIE_CFG_PMCAP                          0xA0
#define R_PCH_PCIE_CFG_PMCS                           (R_PCH_PCIE_CFG_PMCAP + R_PCIE_PMCS_OFFST)

#define R_PCH_PCIE_CFG_CCFG                           0xD0
#define B_PCH_PCIE_CFG_CCFG_UPMWPD                    BIT25
#define B_PCH_PCIE_CFG_CCFG_UPSD                      BIT24
#define B_PCH_PCIE_CFG_CCFG_UNSD                      BIT23
#define B_PCH_PCIE_CFG_CCFG_DCGEISMA                  BIT15
#define B_PCH_PCIE_CFG_CCFG_UNRD                      (BIT13 | BIT12)
#define N_PCH_PCIE_CFG_CCFG_UNRD                      12
#define B_PCH_PCIE_CFG_CCFG_UNRS                      (BIT6 | BIT5 | BIT4)
#define N_PCH_PCIE_CFG_CCFG_UNRS                      4
#define V_PCH_PCIE_CFG_CCFG_UNRS_128B                 0
#define V_PCH_PCIE_CFG_CCFG_UNRS_256B                 1
#define V_PCH_PCIE_CFG_CCFG_UNRS_64B                  7
#define B_PCH_PCIE_CFG_CCFG_UPRS                      (BIT2 | BIT1 | BIT0)
#define N_PCH_PCIE_CFG_CCFG_UPRS                      0
#define V_PCH_PCIE_CFG_CCFG_UPRS_128B                 0
#define V_PCH_PCIE_CFG_CCFG_UPRS_256B                 1
#define V_PCH_PCIE_CFG_CCFG_UPRS_64B                  7

#define R_PCH_PCIE_CFG_MPC2                           0xD4
#define B_PCH_PCIE_CFG_MPC2_L1SSESE                   BIT30
#define B_PCH_PCIE_CFG_MPC2_DISPLLEWL1SE              BIT16
#define S_PCH_PCIE_CFG_MPC2                           4
#define B_PCH_PCIE_CFG_MPC2_PTNFAE                    BIT12
#define B_PCH_PCIE_CFG_MPC2_LSTP                      BIT6
#define B_PCH_PCIE_CFG_MPC2_IEIME                     BIT5
#define B_PCH_PCIE_CFG_MPC2_ASPMCOEN                  BIT4
#define B_PCH_PCIE_CFG_MPC2_ASPMCO                    (BIT3 | BIT2)
#define V_PCH_PCIE_CFG_MPC2_ASPMCO_DISABLED           0
#define V_PCH_PCIE_CFG_MPC2_ASPMCO_L0S                (1 << 2)
#define V_PCH_PCIE_CFG_MPC2_ASPMCO_L1                 (2 << 2)
#define V_PCH_PCIE_CFG_MPC2_ASPMCO_L0S_L1             (3 << 2)
#define B_PCH_PCIE_CFG_MPC2_EOIFD                     BIT1

#define R_PCH_PCIE_CFG_MPC                            0xD8
#define S_PCH_PCIE_CFG_MPC                            4
#define B_PCH_PCIE_CFG_MPC_PMCE                       BIT31
#define B_PCH_PCIE_CFG_MPC_HPCE                       BIT30
#define B_PCH_PCIE_CFG_MPC_MMBNCE                     BIT27
#define B_PCH_PCIE_CFG_MPC_P8XDE                      BIT26
#define B_PCH_PCIE_CFG_MPC_IRRCE                      BIT25
#define B_PCH_PCIE_CFG_MPC_SRL                        BIT23
#define B_PCH_PCIE_CFG_MPC_UCEL                       (BIT20 | BIT19 | BIT18)
#define N_PCH_PCIE_CFG_MPC_UCEL                       18
#define B_PCH_PCIE_CFG_MPC_CCEL                       (BIT17 | BIT16 | BIT15)
#define N_PCH_PCIE_CFG_MPC_CCEL                       15
#define B_PCH_PCIE_CFG_MPC_PCIESD                     (BIT14 | BIT13)
#define N_PCH_PCIE_CFG_MPC_PCIESD                     13
#define V_PCH_PCIE_CFG_MPC_PCIESD_GEN1                1
#define V_PCH_PCIE_CFG_MPC_PCIESD_GEN2                2
#define B_PCH_PCIE_CFG_MPC_MCTPSE                     BIT3
#define B_PCH_PCIE_CFG_MPC_HPME                       BIT1
#define N_PCH_PCIE_CFG_MPC_HPME                       1
#define B_PCH_PCIE_CFG_MPC_PMME                       BIT0

#define R_PCH_PCIE_CFG_SMSCS                          0xDC
#define S_PCH_PCIE_CFG_SMSCS                          4
#define B_PCH_PCIE_CFG_SMSCS_PMCS                     BIT31
#define N_PCH_PCIE_CFG_SMSCS_LERSMIS                  5
#define N_PCH_PCIE_CFG_SMSCS_HPLAS                    4
#define N_PCH_PCIE_CFG_SMSCS_HPPDM                    1

#define R_PCH_PCIE_CFG_SPR                            0xE0

#define R_PCH_PCIE_CFG_RPDCGEN                        0xE1
#define S_PCH_PCIE_CFG_RPDCGEN                        1
#define B_PCH_PCIE_CFG_RPDCGEN_RPSCGEN                BIT7
#define B_PCH_PCIE_CFG_RPDCGEN_PTOCGE                 BIT6
#define B_PCH_PCIE_CFG_RPDCGEN_LCLKREQEN              BIT5
#define B_PCH_PCIE_CFG_RPDCGEN_BBCLKREQEN             BIT4
#define B_PCH_PCIE_CFG_RPDCGEN_SRDBCGEN               BIT2
#define B_PCH_PCIE_CFG_RPDCGEN_RPDLCGEN               BIT1
#define B_PCH_PCIE_CFG_RPDCGEN_RPDBCGEN               BIT0

#define R_PCH_PCIE_CFG_RPPGEN                         0xE2
#define B_PCH_PCIE_CFG_RPPGEN_PTOTOP                  BIT6
#define B_PCH_PCIE_CFG_RPPGEN_SEOSCGE                 BIT4

#define R_PCH_PCIE_CFG_PWRCTL                         0xE8
#define B_PCH_PCIE_CFG_PWRCTL_LTSSMRTC                BIT20
#define B_PCH_PCIE_CFG_PWRCTL_WPDMPGEP                BIT17
#define B_PCH_PCIE_CFG_PWRCTL_DBUPI                   BIT15
#define B_PCH_PCIE_CFG_PWRCTL_TXSWING                 BIT13
#define B_PCH_PCIE_CFG_PWRCTL_RPL1SQPOL               BIT1
#define B_PCH_PCIE_CFG_PWRCTL_RPDTSQPOL               BIT0

#define R_PCH_PCIE_CFG_DC                             0xEC
#define B_PCH_PCIE_CFG_DC_PCIBEM                      BIT2

#define R_PCH_PCIE_CFG_IPCS                           0xF0
#define B_PCH_PCIE_CFG_IPCS_IMPS                      (BIT10 | BIT9 | BIT8)
#define N_PCH_PCIE_CFG_IPCS_IMPS                      8
#define V_PCH_PCIE_CFG_IPCS_IMPS_64B                  7

#define R_PCH_PCIE_CFG_PHYCTL2                        0xF5
#define B_PCH_PCIE_CFG_PHYCTL2_TDFT                   (BIT7 | BIT6)
#define B_PCH_PCIE_CFG_PHYCTL2_TXCFGCHGWAIT           (BIT5 | BIT4)
#define N_PCH_PCIE_CFG_PHYCTL2_TXCFGCHGWAIT           4
#define B_PCH_PCIE_CFG_PHYCTL2_PXPG3PLLOFFEN          BIT1
#define B_PCH_PCIE_CFG_PHYCTL2_PXPG2PLLOFFEN          BIT0

#define R_PCH_PCIE_CFG_IOSFSBCS                       0xF7
#define B_PCH_PCIE_CFG_IOSFSBCS_SCPTCGE               BIT6
#define B_PCH_PCIE_CFG_IOSFSBCS_SIID                  (BIT3 | BIT2)

#define R_PCH_PCIE_CFG_STRPFUSECFG                    0xFC
#define B_PCH_PCIE_CFG_STRPFUSECFG_PXIP               (BIT27 | BIT26 | BIT25 | BIT24)
#define N_PCH_PCIE_CFG_STRPFUSECFG_PXIP               24
#define B_PCH_PCIE_CFG_STRPFUSECFG_RPC                (BIT15 | BIT14)
#define V_PCH_PCIE_CFG_STRPFUSECFG_RPC_1_1_1_1        0
#define V_PCH_PCIE_CFG_STRPFUSECFG_RPC_2_1_1          1
#define V_PCH_PCIE_CFG_STRPFUSECFG_RPC_2_2            2
#define V_PCH_PCIE_CFG_STRPFUSECFG_RPC_4              3
#define N_PCH_PCIE_CFG_STRPFUSECFG_RPC                14
#define B_PCH_PCIE_CFG_STRPFUSECFG_MODPHYIOPMDIS      BIT9
#define B_PCH_PCIE_CFG_STRPFUSECFG_PLLSHTDWNDIS       BIT8
#define B_PCH_PCIE_CFG_STRPFUSECFG_STPGATEDIS         BIT7
#define B_PCH_PCIE_CFG_STRPFUSECFG_ASPMDIS            BIT6
#define B_PCH_PCIE_CFG_STRPFUSECFG_LDCGDIS            BIT5
#define B_PCH_PCIE_CFG_STRPFUSECFG_LTCGDIS            BIT4
#define B_PCH_PCIE_CFG_STRPFUSECFG_CDCGDIS            BIT3
#define B_PCH_PCIE_CFG_STRPFUSECFG_DESKTOPMOB         BIT2

//
//PCI Express Extended Capability Registers
//

#define R_PCH_PCIE_CFG_EXCAP_OFFSET                   0x100

#define R_PCH_PCIE_CFG_EX_AECH                        0x100 ///< Advanced Error Reporting Capability Header
#define V_PCH_PCIE_CFG_EX_AEC_CV                      0x1
#define R_PCH_PCIE_CFG_EX_UEM                         (R_PCH_PCIE_CFG_EX_AECH + R_PCIE_EX_UEM_OFFSET) // Uncorrectable Error Mask

#define R_PCH_PCIE_CFG_UEM                            0x108

#define R_PCH_PCIE_CFG_EX_CES                         0x110 ///< Correctable Error Status
#define B_PCH_PCIE_CFG_EX_CES_BD                      BIT7  ///< Bad DLLP Status
#define B_PCH_PCIE_CFG_EX_CES_BT                      BIT6  ///< Bad TLP Status
#define B_PCH_PCIE_CFG_EX_CES_RE                      BIT0  ///< Receiver Error Status

#define R_PCH_PCIE_CFG_CEM                            0x114

//CES.RE, CES.BT, CES.BD

#define R_PCH_PCIE_CFG_EX_ACSECH                      0x220 ///< ACS Extended Capability Header
#define V_PCH_PCIE_CFG_EX_ACS_CV                      0x1
#define R_PCH_PCIE_CFG_EX_ACSCAPR                     (R_PCH_PCIE_CFG_EX_ACSECH + R_PCIE_EX_ACSCAPR_OFFSET)

#define R_PCH_PCIE_CFG_EX_PTMECH                      0x150 ///< PTM Extended Capability Header
#define V_PCH_PCIE_CFG_EX_PTM_CV                      0x1
#define R_PCH_PCIE_CFG_EX_PTMCAPR                     (R_PCH_PCIE_CFG_EX_PTMECH + R_PCIE_EX_PTMCAP_OFFSET)

#define R_PCH_PCIE_CFG_EX_L1SECH                      0x200 ///< L1 Sub-States Extended Capability Header
#define V_PCH_PCIE_CFG_EX_L1S_CV                      0x1
#define R_PCH_PCIE_CFG_EX_L1SCAP                      (R_PCH_PCIE_CFG_EX_L1SECH + R_PCIE_EX_L1SCAP_OFFSET)
#define R_PCH_PCIE_CFG_EX_L1SCTL1                     (R_PCH_PCIE_CFG_EX_L1SECH + R_PCIE_EX_L1SCTL1_OFFSET)
#define R_PCH_PCIE_CFG_EX_L1SCTL2                     (R_PCH_PCIE_CFG_EX_L1SECH + R_PCIE_EX_L1SCTL2_OFFSET)

#define R_PCH_PCIE_CFG_EX_SPEECH                      0xA30 ///< Secondary PCI Express Extended Capability Header
#define V_PCH_PCIE_CFG_EX_SPEECH_CV                   0x1
#define R_PCH_PCIE_CFG_EX_LCTL3                       (R_PCH_PCIE_CFG_EX_SPEECH + R_PCIE_EX_LCTL3_OFFSET)
#define R_PCH_PCIE_CFG_EX_LES                         (R_PCH_PCIE_CFG_EX_SPEECH + R_PCIE_EX_LES_OFFSET)
#define R_PCH_PCIE_CFG_EX_LECTL                       (R_PCH_PCIE_CFG_EX_SPEECH + R_PCIE_EX_L01EC_OFFSET)
#define B_PCH_PCIE_CFG_EX_LECTL_UPTPH                 (BIT14 | BIT13 | BIT12)
#define N_PCH_PCIE_CFG_EX_LECTL_UPTPH                 12
#define B_PCH_PCIE_CFG_EX_LECTL_UPTP                  0x0F00
#define N_PCH_PCIE_CFG_EX_LECTL_UPTP                  8
#define B_PCH_PCIE_CFG_EX_LECTL_DPTPH                 (BIT6 | BIT5 | BIT4)
#define N_PCH_PCIE_CFG_EX_LECTL_DPTPH                 4
#define B_PCH_PCIE_CFG_EX_LECTL_DPTP                  0x000F
#define N_PCH_PCIE_CFG_EX_LECTL_DPTP                  0

#define R_PCH_PCIE_CFG_EX_DPCECH                      0xA00 ///< Downstream Port Containment
#define V_PCH_PCIE_CFG_EX_DPCECH_CV                   0x1

#define R_PCH_PCIE_CFG_EX_L01EC                       (R_PCH_PCIE_CFG_EX_SPEECH + R_PCIE_EX_L01EC_OFFSET)
#define B_PCH_PCIE_CFG_EX_L01EC_TP                    0xF ///< Bits used for each transmitter preset value
#define S_PCH_PCIE_CFG_EX_L01EC_TP                    8 ///< Each of the transmitter presets configuration fields

#define R_PCH_PCIE_CFG_PCIERTP1                       0x300
#define R_PCH_PCIE_CFG_PCIERTP2                       0x304
#define R_PCH_PCIE_CFG_PCIENFTS                       0x314
#define R_PCH_PCIE_CFG_PCIEL0SC                       0x318

#define R_PCH_PCIE_CFG_PCIECFG2                       0x320
#define B_PCH_PCIE_CFG_PCIECFG2_LBWSSTE               BIT30
#define B_PCH_PCIE_CFG_PCIECFG2_RLLG3R                BIT27
#define B_PCH_PCIE_CFG_PCIECFG2_CROAOV                BIT24
#define B_PCH_PCIE_CFG_PCIECFG2_CROAOE                BIT23
#define B_PCH_PCIE_CFG_PCIECFG2_CRSREN                BIT22
#define B_PCH_PCIE_CFG_PCIECFG2_PMET                  (BIT21 | BIT20)
#define V_PCH_PCIE_CFG_PCIECFG2_PMET                  1
#define N_PCH_PCIE_CFG_PCIECFG2_PMET                  20

#define R_PCH_PCIE_CFG_PCIEDBG                        0x324
#define B_PCH_PCIE_CFG_PCIEDBG_LBWSSTE                BIT30
#define B_PCH_PCIE_CFG_PCIEDBG_USSP                   (BIT27 | BIT26)
#define B_PCH_PCIE_CFG_PCIEDBG_LGCLKSQEXITDBTIMERS    (BIT25 | BIT24)
#define B_PCH_PCIE_CFG_PCIEDBG_CTONFAE                BIT14
#define B_PCH_PCIE_CFG_PCIEDBG_LDSWQRP                BIT13
#define B_PCH_PCIE_CFG_PCIEDBG_SQOL0                  BIT7
#define B_PCH_PCIE_CFG_PCIEDBG_SPCE                   BIT5
#define B_PCH_PCIE_CFG_PCIEDBG_LR                     BIT4

#define R_PCH_PCIE_CFG_PCIESTS1                              0x328
#define B_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE                    0xFF000000
#define N_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE                    24
#define V_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE_DETRDY             0x01
#define V_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE_DETRDYECINP1CG     0x0E
#define V_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE_L0                 0x33
#define V_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE_DISWAIT            0x5E
#define V_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE_DISWAITPG          0x60
#define V_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE_RECOVERYSPEEDREADY 0x6C
#define V_PCH_PCIE_CFG_PCIESTS1_LTSMSTATE_RECOVERYLNK2DETECT 0x6F


#define B_PCH_PCIE_CFG_PCIESTS1_LNKSTAT               (BIT22 | BIT21 | BIT20 | BIT19)
#define N_PCH_PCIE_CFG_PCIESTS1_LNKSTAT               19
#define V_PCH_PCIE_CFG_PCIESTS1_LNKSTAT_L0            0x7

#define R_PCH_PCIE_CFG_PCIESTS2                       0x32C
#define B_PCH_PCIE_CFG_PCIESTS2_P4PNCCWSSCMES         BIT31
#define B_PCH_PCIE_CFG_PCIESTS2_P3PNCCWSSCMES         BIT30
#define B_PCH_PCIE_CFG_PCIESTS2_P2PNCCWSSCMES         BIT29
#define B_PCH_PCIE_CFG_PCIESTS2_P1PNCCWSSCMES         BIT28
#define B_PCH_PCIE_CFG_PCIESTS2_CLRE                  0x0000F000
#define N_PCH_PCIE_CFG_PCIESTS2_CLRE                  12

#define R_PCH_PCIE_CFG_PCIEALC                        0x338
#define B_PCH_PCIE_CFG_PCIEALC_ITLRCLD                BIT29
#define B_PCH_PCIE_CFG_PCIEALC_ILLRCLD                BIT28
#define B_PCH_PCIE_CFG_PCIEALC_BLKDQDA                BIT26
#define B_PCH_PCIE_CFG_PCIEALC_RTD3PDSP               BIT20

#define R_PCH_PCIE_CFG_PTMPD                          0x390 ///< PTM Propagation Delay
#define R_PCH_PCIE_CFG_PTMLLMT                        0x394 ///< PTM Lower Local Master Time
#define R_PCH_PCIE_CFG_PTMULMT                        0x398 ///< PTM Upper Local Master Time
#define R_PCH_PCIE_CFG_PTMPSDC1                       0x39C ///< PTM Pipe Stage Delay Configuration 1
#define R_PCH_PCIE_CFG_PTMPSDC2                       0x3A0 ///< PTM Pipe Stage Delay Configuration 2
#define R_PCH_PCIE_CFG_PTMPSDC3                       0x3A4 ///< PTM Pipe Stage Delay Configuration 3
#define R_PCH_PCIE_CFG_PTMPSDC4                       0x3A8 ///< PTM Pipe Stage Delay Configuration 4
#define R_PCH_PCIE_CFG_PTMPSDC5                       0x3AC ///< PTM Pipe Stage Delay Configuration 5
#define R_PCH_PCIE_CFG_PTMECFG                        0x3B0 ///< PTM Extended Configuration
#define B_PCH_PCIE_CFG_PTMECFG_IOSFMADP               0xF   ///< IOSF Max Allowed Delay programming. bit0~bit3

#define R_PCH_PCIE_CFG_LTROVR                         0x400
#define B_PCH_PCIE_CFG_LTROVR_LTRNSROVR               BIT31 ///< LTR Non-Snoop Requirement Bit Override
#define B_PCH_PCIE_CFG_LTROVR_LTRSROVR                BIT15 ///< LTR Snoop Requirement Bit Override

#define R_PCH_PCIE_CFG_LTROVR2                        0x404
#define B_PCH_PCIE_CFG_LTROVR2_FORCE_OVERRIDE         BIT3 ///< LTR Force Override Enable
#define B_PCH_PCIE_CFG_LTROVR2_LOCK                   BIT2 ///< LTR Override Lock
#define B_PCH_PCIE_CFG_LTROVR2_LTRNSOVREN             BIT1 ///< LTR Non-Snoop Override Enable
#define B_PCH_PCIE_CFG_LTROVR2_LTRSOVREN              BIT0 ///< LTR Snoop Override Enable

#define R_PCH_PCIE_CFG_PHYCTL4                        0x408
#define B_PCH_PCIE_CFG_PHYCTL4_SQDIS                  BIT27

#define R_PCH_PCIE_CFG_TNPT                           0x418 ///< Thermal and Power Throttling
#define B_PCH_PCIE_CFG_TNPT_DRXLTE                    BIT1
#define B_PCH_PCIE_CFG_TNPT_DTXLTE                    BIT0
#define N_PCH_PCIE_CFG_TNPT_TP                        24
#define V_PCH_PCIE_CFG_TNPT_TP_3_MS                   0x2
#define R_PCH_PCIE_CFG_PCIEPMECTL                     0x420
#define B_PCH_PCIE_CFG_PCIEPMECTL_FDPPGE              BIT31
#define B_PCH_PCIE_CFG_PCIEPMECTL_DLSULPPGE           BIT30
#define B_PCH_PCIE_CFG_PCIEPMECTL_DLSULDLSD           BIT29
#define B_PCH_PCIE_CFG_PCIEPMECTL_L1LE                BIT17
#define B_PCH_PCIE_CFG_PCIEPMECTL_L1LTRTLV            (BIT13 | BIT12 | BIT11 | BIT10 | BIT9 | BIT8 | BIT7 | BIT6 | BIT5 | BIT4)
#define N_PCH_PCIE_CFG_PCIEPMECTL_L1LTRTLV            4
#define V_PCH_PCIE_CFG_PCIEPMECTL_L1LTRTLV            0x32
#define B_PCH_PCIE_CFG_PCIEPMECTL_L1FSOE              BIT0

#define R_PCH_PCIE_CFG_PCIEPMECTL2                    0x424
#define B_PCH_PCIE_CFG_PCIEPMECTL2_PHYCLPGE           BIT11
#define B_PCH_PCIE_CFG_PCIEPMECTL2_FDCPGE             BIT8
#define B_PCH_PCIE_CFG_PCIEPMECTL2_DETSCPGE           BIT7
#define B_PCH_PCIE_CFG_PCIEPMECTL2_L23RDYSCPGE        BIT6
#define B_PCH_PCIE_CFG_PCIEPMECTL2_DISSCPGE           BIT5
#define B_PCH_PCIE_CFG_PCIEPMECTL2_L1SCPGE            BIT4

#define R_PCH_PCIE_CFG_PCE                            0x428
#define B_PCH_PCIE_CFG_PCE_HAE                        BIT5
#define B_PCH_PCIE_CFG_PCE_PMCRE                      BIT0

#define R_PCH_PCIE_CFG_PGCBCTL1                       0x42C

#define R_PCH_PCIE_CFG_EQCFG1                         0x450
#define S_PCH_PCIE_CFG_EQCFG1                         4
#define B_PCH_PCIE_CFG_EQCFG1_REC                     0xFF000000
#define N_PCH_PCIE_CFG_EQCFG1_REC                     24
#define B_PCH_PCIE_CFG_EQCFG1_REIFECE                 BIT23
#define N_PCH_PCIE_CFG_EQCFG1_LERSMIE                 21
#define B_PCH_PCIE_CFG_EQCFG1_LEP23B                  BIT18
#define B_PCH_PCIE_CFG_EQCFG1_LEP3B                   BIT17
#define B_PCH_PCIE_CFG_EQCFG1_RTLEPCEB                BIT16
#define B_PCH_PCIE_CFG_EQCFG1_RTPCOE                  BIT15
#define B_PCH_PCIE_CFG_EQCFG1_HPCMQE                  BIT13
#define B_PCH_PCIE_CFG_EQCFG1_HAED                    BIT12
#define V_PCH_PCIE_CFG_EQCFG1_RWTNEVE                 0xF
#define N_PCH_PCIE_CFG_EQCFG1_RWTNEVE                 8
#define B_PCH_PCIE_CFG_EQCFG1_EQTS2IRRC               BIT7
#define B_PCH_PCIE_CFG_EQCFG1_TUPP                    BIT1

#define R_PCH_PCIE_CFG_RTPCL1                         0x454
#define B_PCH_PCIE_CFG_RTPCL1_PCM                     BIT31
#define B_PCH_PCIE_CFG_RTPCL1_RTPRECL2PL4             0x3F000000
#define B_PCH_PCIE_CFG_RTPCL1_RTPOSTCL1PL3            0xFC0000
#define B_PCH_PCIE_CFG_RTPCL1_RTPRECL1PL2             0x3F000
#define B_PCH_PCIE_CFG_RTPCL1_RTPOSTCL0PL1            0xFC0
#define B_PCH_PCIE_CFG_RTPCL1_RTPRECL0PL0             0x3F

#define R_PCH_PCIE_CFG_RTPCL2                         0x458
#define B_PCH_PCIE_CFG_RTPCL2_RTPOSTCL3PL             0x3F000
#define B_PCH_PCIE_CFG_RTPCL2_RTPRECL3PL6             0xFC0
#define B_PCH_PCIE_CFG_RTPCL2_RTPOSTCL2PL5            0x3F

#define R_PCH_PCIE_CFG_RTPCL3                         0x45C
#define B_PCH_PCIE_CFG_RTPCL3_RTPRECL7                0x3F000000
#define B_PCH_PCIE_CFG_RTPCL3_RTPOSTCL6               0xFC0000
#define B_PCH_PCIE_CFG_RTPCL3_RTPRECL6                0x3F000
#define B_PCH_PCIE_CFG_RTPCL3_RTPOSTCL5               0xFC0
#define B_PCH_PCIE_CFG_RTPCL3_RTPRECL5PL10            0x3F

#define R_PCH_PCIE_CFG_RTPCL4                         0x460
#define B_PCH_PCIE_CFG_RTPCL4_RTPOSTCL9               0x3F000000
#define B_PCH_PCIE_CFG_RTPCL4_RTPRECL9                0xFC0000
#define B_PCH_PCIE_CFG_RTPCL4_RTPOSTCL8               0x3F000
#define B_PCH_PCIE_CFG_RTPCL4_RTPRECL8                0xFC0
#define B_PCH_PCIE_CFG_RTPCL4_RTPOSTCL7               0x3F

#define R_PCH_PCIE_CFG_FOMS                           0x464
#define B_PCH_PCIE_CFG_FOMS_I                         (BIT30 | BIT29)
#define N_PCH_PCIE_CFG_FOMS_I                         29
#define B_PCH_PCIE_CFG_FOMS_LN                        0x1F000000
#define N_PCH_PCIE_CFG_FOMS_LN                        24
#define B_PCH_PCIE_CFG_FOMS_FOMSV                     0x00FFFFFF
#define B_PCH_PCIE_CFG_FOMS_FOMSV0                    0x000000FF
#define N_PCH_PCIE_CFG_FOMS_FOMSV0                    0
#define B_PCH_PCIE_CFG_FOMS_FOMSV1                    0x0000FF00
#define N_PCH_PCIE_CFG_FOMS_FOMSV1                    8
#define B_PCH_PCIE_CFG_FOMS_FOMSV2                    0x00FF0000
#define N_PCH_PCIE_CFG_FOMS_FOMSV2                    16

#define R_PCH_PCIE_CFG_HAEQ                           0x468
#define N_PCH_PCIE_CFG_HAEQ_DL                        8
#define B_PCH_PCIE_CFG_HAEQ_HAPCCPI                   (BIT31 | BIT30 | BIT29 | BIT28)
#define N_PCH_PCIE_CFG_HAEQ_HAPCCPI                   28
#define B_PCH_PCIE_CFG_HAEQ_MACFOMC                   BIT19

#define R_PCH_PCIE_CFG_LTCO1                          0x470
#define B_PCH_PCIE_CFG_LTCO1_L1TCOE                   BIT25
#define B_PCH_PCIE_CFG_LTCO1_L0TCOE                   BIT24
#define B_PCH_PCIE_CFG_LTCO1_L1TPOSTCO                0xFC0000
#define N_PCH_PCIE_CFG_LTCO1_L1TPOSTCO                18
#define B_PCH_PCIE_CFG_LTCO1_L1TPRECO                 0x3F000
#define N_PCH_PCIE_CFG_LTCO1_L1TPRECO                 12
#define B_PCH_PCIE_CFG_LTCO1_L0TPOSTCO                0xFC0
#define N_PCH_PCIE_CFG_LTCO1_L0TPOSTCO                6
#define B_PCH_PCIE_CFG_LTCO1_L0TPRECO                 0x3F
#define N_PCH_PCIE_CFG_LTCO1_L0TPRECO                 0

#define R_PCH_PCIE_CFG_LTCO2                          0x474
#define B_PCH_PCIE_CFG_LTCO2_L3TCOE                   BIT25
#define B_PCH_PCIE_CFG_LTCO2_L2TCOE                   BIT24
#define B_PCH_PCIE_CFG_LTCO2_L3TPOSTCO                0xFC0000
#define B_PCH_PCIE_CFG_LTCO2_L3TPRECO                 0x3F000
#define B_PCH_PCIE_CFG_LTCO2_L2TPOSTCO                0xFC0
#define B_PCH_PCIE_CFG_LTCO2_L2TPRECO                 0x3F

#define R_PCH_PCIE_CFG_G3L0SCTL                       0x478
#define B_PCH_PCIE_CFG_G3L0SCTL_G3UCNFTS              0x0000FF00
#define B_PCH_PCIE_CFG_G3L0SCTL_G3CCNFTS              0x000000FF

#define R_PCH_PCIE_CFG_EQCFG2                         0x47C
#define B_PCH_PCIE_CFG_EQCFG2_NTIC                    0xFF000000
#define B_PCH_PCIE_CFG_EQCFG2_EMD                     BIT23
#define B_PCH_PCIE_CFG_EQCFG2_NTSS                    (BIT22 | BIT21 | BIT20)
#define B_PCH_PCIE_CFG_EQCFG2_PCET                    (BIT19 | BIT18 | BIT17 | BIT16)
#define N_PCH_PCIE_CFG_EQCFG2_PCET                    16
#define B_PCH_PCIE_CFG_EQCFG2_HAPCSB                  (BIT15 | BIT14 | BIT13 | BIT12)
#define N_PCH_PCIE_CFG_EQCFG2_HAPCSB                  12
#define B_PCH_PCIE_CFG_EQCFG2_NTEME                   BIT11
#define B_PCH_PCIE_CFG_EQCFG2_MPEME                   BIT10
#define B_PCH_PCIE_CFG_EQCFG2_REWMETM                 (BIT9 | BIT8)
#define B_PCH_PCIE_CFG_EQCFG2_REWMET                  0xFF

#define R_PCH_PCIE_CFG_MM                             0x480
#define B_PCH_PCIE_CFG_MM_MSST                        0xFFFFFF00
#define N_PCH_PCIE_CFG_MM_MSST                        8
#define B_PCH_PCIE_CFG_MM_MSS                         0xFF

#define R_PCH_PCIE_CFG_LANE0_PRESETS                  0x500
#define S_PCH_PCIE_CFG_SINGLE_LANE_PRESETS            0x20
#define R_PCH_PCIE_CFG_LFFS_OFFSET_FROM_LANE_BASE     0x1C   ///< This register offset is taken from base of the lane presets configuration
                                                             ///< starting with R_PCH_PCIE_CFG_LANE0_PRESETS register.
#define N_PCH_PCIE_CFG_LFFS_FS                        8

#define R_PCH_PCIE_CFG_GDR                            0x690
#define B_PCH_PCIE_CFG_GDR_GPIOALD                    BIT10

#define R_PCH_PCIE_CFG_VNNREMCTL                        0xC70
#define B_PCH_PCIE_CFG_VNNREMCTL_LRSLFVNNRE             (BIT1 | BIT0)
#define V_PCH_PCIE_CFG_VNNREMCTL_LRSLFVNNRE_4_OSC_CLK   0x0
#define V_PCH_PCIE_CFG_VNNREMCTL_LRSLFVNNRE_8_OSC_CLK   0x1
#define V_PCH_PCIE_CFG_VNNREMCTL_LRSLFVNNRE_16_OSC_CLK  0x2
#define V_PCH_PCIE_CFG_VNNREMCTL_LRSLFVNNRE_32_OSC_CLK  0x3
#define B_PCH_PCIE_CFG_VNNREMCTL_ISPLFVNNRE             (BIT3 | BIT2)
#define N_PCH_PCIE_CFG_VNNREMCTL_ISPLFVNNRE             2
#define V_PCH_PCIE_CFG_VNNREMCTL_ISPLFVNNRE_8_OSC_CLK   0x0
#define V_PCH_PCIE_CFG_VNNREMCTL_ISPLFVNNRE_16_OSC_CLK  0x1
#define V_PCH_PCIE_CFG_VNNREMCTL_ISPLFVNNRE_32_OSC_CLK  0x2
#define V_PCH_PCIE_CFG_VNNREMCTL_ISPLFVNNRE_64_OSC_CLK  0x3
#define B_PCH_PCIE_CFG_VNNREMCTL_LDVNNRE                BIT4
#define B_PCH_PCIE_CFG_VNNREMCTL_RTD3VNNRE              BIT5
#define B_PCH_PCIE_CFG_VNNREMCTL_DNPVNNRE               BIT6
#define B_PCH_PCIE_CFG_VNNREMCTL_HPVNNRE                BIT7
#define B_PCH_PCIE_CFG_VNNREMCTL_FDVNNRE                BIT8

#define R_PCH_PCIE_CFG_VNNRSNRC1                        0xC74
//
// PCIE PCRs (PID:SPA SPB SPC SPD SPE SPF)
//
#define R_SPX_PCR_PCD                         0                       ///< Port configuration and disable
#define B_SPX_PCR_PCD_RP1FN                   (BIT2 | BIT1 | BIT0)    ///< Port 1 Function Number
#define B_SPX_PCR_PCD_RP1CH                   BIT3                    ///< Port 1 config hide
#define B_SPX_PCR_PCD_RP2FN                   (BIT6 | BIT5 | BIT4)    ///< Port 2 Function Number
#define B_SPX_PCR_PCD_RP2CH                   BIT7                    ///< Port 2 config hide
#define B_SPX_PCR_PCD_RP3FN                   (BIT10 | BIT9 | BIT8)   ///< Port 3 Function Number
#define B_SPX_PCR_PCD_RP3CH                   BIT11                   ///< Port 3 config hide
#define B_SPX_PCR_PCD_RP4FN                   (BIT14 | BIT13 | BIT12) ///< Port 4 Function Number
#define B_SPX_PCR_PCD_RP4CH                   BIT15                   ///< Port 4 config hide
#define S_SPX_PCR_PCD_RP_FIELD                4                       ///< 4 bits for each RP FN
#define B_SPX_PCR_PCD_P1D                     BIT16                   ///< Port 1 disable
#define B_SPX_PCR_PCD_P2D                     BIT17                   ///< Port 2 disable
#define B_SPX_PCR_PCD_P3D                     BIT18                   ///< Port 3 disable
#define B_SPX_PCR_PCD_P4D                     BIT19                   ///< Port 4 disable
#define B_SPX_PCR_PCD_SRL                     BIT31                   ///< Secured Register Lock

#define R_SPX_PCR_PCIEHBP                     0x0004                  ///< PCI Express high-speed bypass
#define B_SPX_PCR_PCIEHBP_PCIEHBPME           BIT0                    ///< PCIe HBP mode enable
#define B_SPX_PCR_PCIEHBP_PCIEGMO             (BIT2 | BIT1)           ///< PCIe gen mode override
#define B_SPX_PCR_PCIEHBP_PCIETIL0O           BIT3                    ///< PCIe transmitter-in-L0 override
#define B_SPX_PCR_PCIEHBP_PCIERIL0O           BIT4                    ///< PCIe receiver-in-L0 override
#define B_SPX_PCR_PCIEHBP_PCIELRO             BIT5                    ///< PCIe link recovery override
#define B_SPX_PCR_PCIEHBP_PCIELDO             BIT6                    ///< PCIe link down override
#define B_SPX_PCR_PCIEHBP_PCIESSM             BIT7                    ///< PCIe SKP suppression mode
#define B_SPX_PCR_PCIEHBP_PCIESST             BIT8                    ///< PCIe suppress SKP transmission
#define B_SPX_PCR_PCIEHBP_PCIEHBPPS           (BIT13 | BIT12)         ///< PCIe HBP port select
#define B_SPX_PCR_PCIEHBP_CRCSEL              (BIT15 | BIT14)         ///< CRC select
#define B_SPX_PCR_PCIEHBP_PCIEHBPCRC          0xFFFF0000              ///< PCIe HBP CRC

#define R_SPX_PCR_IMRAMBL                     0x10                    ///< IMR access memory base and limit
#define B_SPX_PCR_IMRAMBL_RS3BN               0x000000FF              ///< Bus Number for RS3
#define N_SPX_PCR_IMRAMBL_RS3BN               0
#define B_SPX_PCR_IMRAMBL_IAMB                0x000FFF00              ///< IMR access memory base, lower bits
#define N_SPX_PCR_IMRAMBL_IAMB                8
#define B_SPX_PCR_IMRAMBL_IAML                0xFFF00000              ///< IMR access memory limit, lower bits
#define N_SPX_PCR_IMRAMBL_IAML                20

#define R_SPX_PCR_IMRAMBU32                   0x14                    ///< IMR access memory base, upper bits

#define R_SPX_PCR_IMRAMLU32                   0x18                    ///< IMR access memory limit, upper bits

#define R_SPX_PCR_IMRAMLE                     0x1C                    ///< IMR access memory lock & enable
#define B_SPX_PCR_IMRAMLE_IAE1                BIT0                    ///< IMR access enable for port 1 of given controller
#define B_SPX_PCR_IMRAMLE_IAE2                BIT1                    ///< IMR access enable for port 1 of given controller
#define B_SPX_PCR_IMRAMLE_IAE3                BIT2                    ///< IMR access enable for port 1 of given controller
#define B_SPX_PCR_IMRAMLE_IAE4                BIT3                    ///< IMR access enable for port 1 of given controller
#define B_SPX_PCR_IMRAMLE_SRL                 BIT31                   ///< IMR register lock

//
// ICC PCR (PID: ICC)
//
#define R_ICC_PCR_TMCSRCCLK                   0x1000                  ///< Timing Control SRC Clock Register
#define R_ICC_PCR_TMCSRCCLK2                  0x1004                  ///< Timing Control SRC Clock Register 2
#define R_ICC_PCR_MSKCKRQ                     0x100C                  ///< Mask Control CLKREQ
#endif

/** @file
  This file contains definitions of  PCIe Configuration

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

#ifndef _SA_PCI_REGS_H_
#define _SA_PCI_REGS_H_


#define  R_PCIE_CLIST                             0x40
 #define  B_PCIE_CLIST_NEXT                       BIT8
 #define  B_PCIE_CLIST_NEXT_OFFSET                8
 #define  B_PCIE_CLIST_NEXT_MASK                  0xFF00
 #define  B_PCIE_CLIST_CID                        BIT0
 #define  B_PCIE_CLIST_CID_OFFSET                 0
 #define  B_PCIE_CLIST_CID_MASK                   0xFF

#define  R_PCIE_XCAP                              0x42
 #define  B_PCIE_XCAP_IMN                         BIT9
 #define  B_PCIE_XCAP_IMN_OFFSET                  9
 #define  B_PCIE_XCAP_IMN_MASK                    0x3E00
 #define  B_PCIE_XCAP_SI                          BIT8
 #define  B_PCIE_XCAP_SI_OFFSET                   8
 #define  B_PCIE_XCAP_DT_SIP                      BIT4
 #define  B_PCIE_XCAP_DT_OFFSET                   4
 #define  B_PCIE_XCAP_DT_MASK                     0xF0
 #define  B_PCIE_XCAP_CV                          BIT0
 #define  B_PCIE_XCAP_CV_OFFSET                   0
 #define  B_PCIE_XCAP_CV_MASK                     0xF

#define  R_PCIE_DCAP                              0x44
 #define  B_PCIE_DCAP_FLRC                        BIT28
 #define  B_PCIE_DCAP_FLRC_OFFSET                 28
 #define  B_PCIE_DCAP_CSPS                        BIT26
 #define  B_PCIE_DCAP_CSPS_OFFSET                 26
 #define  B_PCIE_DCAP_CSPS_MASK                   0xC000000
 #define  B_PCIE_DCAP_CSPV                        BIT18
 #define  B_PCIE_DCAP_CSPV_OFFSET                 18
 #define  B_PCIE_DCAP_CSPV_MASK                   0x3FC0000
 #define  B_PCIE_DCAP_RBER                        BIT15
 #define  B_PCIE_DCAP_RBER_OFFSET                 15
 #define  B_PCIE_DCAP_PIP                         BIT14
 #define  B_PCIE_DCAP_PIP_OFFSET                  14
 #define  B_PCIE_DCAP_AIP                         BIT13
 #define  B_PCIE_DCAP_AIP_OFFSET                  13
 #define  B_PCIE_DCAP_ABP                         BIT12
 #define  B_PCIE_DCAP_ABP_OFFSET                  12
 #define  B_PCIE_DCAP_E1AL_SIP                    BIT9
 #define  B_PCIE_DCAP_E1AL_OFFSET                 9
 #define  B_PCIE_DCAP_E1AL_MASK                   0xE00
 #define  B_PCIE_DCAP_E0AL_SIP                    BIT6
 #define  B_PCIE_DCAP_E0AL_OFFSET                 6
 #define  B_PCIE_DCAP_E0AL_MASK                   0x1C0
 #define  B_PCIE_DCAP_ETFS                        BIT5
 #define  B_PCIE_DCAP_ETFS_OFFSET                 5
 #define  B_PCIE_DCAP_PFS                         BIT3
 #define  B_PCIE_DCAP_PFS_OFFSET                  3
 #define  B_PCIE_DCAP_PFS_MASK                    0x18
 #define  B_PCIE_DCAP_MPS_SIP                     BIT0
 #define  B_PCIE_DCAP_MPS_OFFSET                  0
 #define  B_PCIE_DCAP_MPS_MASK                    0x7

#define  R_PCIE_DCTL                              0x48
 #define  B_PCIE_DCTL_MRRS                        BIT12
 #define  B_PCIE_DCTL_MRRS_OFFSET                 12
 #define  B_PCIE_DCTL_MRRS_MASK                   0x7000
 #define  B_PCIE_DCTL_ENS                         BIT11
 #define  B_PCIE_DCTL_ENS_OFFSET                  11
 #define  B_PCIE_DCTL_APME                        BIT10
 #define  B_PCIE_DCTL_APME_OFFSET                 10
 #define  B_PCIE_DCTL_PFE                         BIT9
 #define  B_PCIE_DCTL_PFE_OFFSET                  9
 #define  B_PCIE_DCTL_ETFE                        BIT8
 #define  B_PCIE_DCTL_ETFE_OFFSET                 8
 #define  B_PCIE_DCTL_MPS_SIP                     BIT5
 #define  B_PCIE_DCTL_MPS_OFFSET                  5
 #define  B_PCIE_DCTL_MPS_MASK                    0xE0
 #define  B_PCIE_DCTL_ERO                         BIT4
 #define  B_PCIE_DCTL_ERO_OFFSET                  4
 #define  B_PCIE_DCTL_URE                         BIT3
 #define  B_PCIE_DCTL_URE_OFFSET                  3
 #define  B_PCIE_DCTL_FEE                         BIT2
 #define  B_PCIE_DCTL_FEE_OFFSET                  2
 #define  B_PCIE_DCTL_NFE                         BIT1
 #define  B_PCIE_DCTL_NFE_OFFSET                  1
 #define  B_PCIE_DCTL_CEE                         BIT0
 #define  B_PCIE_DCTL_CEE_OFFSET                  0

#define  R_PCIE_DSTS                              0x4A
 #define  B_PCIE_DSTS_TDP                         BIT5
 #define  B_PCIE_DSTS_TDP_OFFSET                  5
 #define  B_PCIE_DSTS_APD                         BIT4
 #define  B_PCIE_DSTS_APD_OFFSET                  4
 #define  B_PCIE_DSTS_URD                         BIT3
 #define  B_PCIE_DSTS_URD_OFFSET                  3
 #define  B_PCIE_DSTS_FED                         BIT2
 #define  B_PCIE_DSTS_FED_OFFSET                  2
 #define  B_PCIE_DSTS_NFED                        BIT1
 #define  B_PCIE_DSTS_NFED_OFFSET                 1
 #define  B_PCIE_DSTS_CED                         BIT0
 #define  B_PCIE_DSTS_CED_OFFSET                  0

#define  R_PCIE_LCAP                              0x4C
 #define  B_PCIE_LCAP_PN                          BIT24
 #define  B_PCIE_LCAP_PN_OFFSET                   24
 #define  B_PCIE_LCAP_PN_MASK                     0xFF000000
 #define  B_PCIE_LCAP_ASPMOC                      BIT22
 #define  B_PCIE_LCAP_ASPMOC_OFFSET               22
 #define  B_PCIE_LCAP_LBNC                        BIT21
 #define  B_PCIE_LCAP_LBNC_OFFSET                 21
 #define  B_PCIE_LCAP_LARC                        BIT20
 #define  B_PCIE_LCAP_LARC_OFFSET                 20
 #define  B_PCIE_LCAP_SDERC                       BIT19
 #define  B_PCIE_LCAP_SDERC_OFFSET                19
 #define  B_PCIE_LCAP_CPM                         BIT18
 #define  B_PCIE_LCAP_CPM_OFFSET                  18
 #define  B_PCIE_LCAP_EL1_SIP                     BIT15
 #define  B_PCIE_LCAP_EL1_OFFSET                  15
 #define  B_PCIE_LCAP_EL1_MASK                    0x38000
 #define  B_PCIE_LCAP_EL0_SIP                     BIT12
 #define  B_PCIE_LCAP_EL0_OFFSET                  12
 #define  B_PCIE_LCAP_EL0_MASK                    0x7000
 #define  B_PCIE_LCAP_APMS_SIP                    BIT10
 #define  B_PCIE_LCAP_APMS_OFFSET                 10
 #define  B_PCIE_LCAP_APMS_MASK                   0xC00
 #define  B_PCIE_LCAP_MLW_SIP                     BIT4
 #define  B_PCIE_LCAP_MLW_OFFSET                  4
 #define  B_PCIE_LCAP_MLW_MASK                    0x3F0
 #define  B_PCIE_LCAP_MLS_SIP                     BIT0
 #define  B_PCIE_LCAP_MLS_OFFSET                  0
 #define  B_PCIE_LCAP_MLS_MASK                    0xF

#define  R_PCIE_LCTL                              0x50
 #define  B_PCIE_LCTL_LABIE                       BIT11
 #define  B_PCIE_LCTL_LABIE_OFFSET                11
 #define  B_PCIE_LCTL_LBMIE                       BIT10
 #define  B_PCIE_LCTL_LBMIE_OFFSET                10
 #define  B_PCIE_LCTL_HAWD                        BIT9
 #define  B_PCIE_LCTL_HAWD_OFFSET                 9
 #define  B_PCIE_LCTL_ECPM                        BIT8
 #define  B_PCIE_LCTL_ECPM_OFFSET                 8
 #define  B_PCIE_LCTL_ES                          BIT7
 #define  B_PCIE_LCTL_ES_OFFSET                   7
 #define  B_PCIE_LCTL_CCC                         BIT6
 #define  B_PCIE_LCTL_CCC_OFFSET                  6
 #define  B_PCIE_LCTL_RL                          BIT5
 #define  B_PCIE_LCTL_RL_OFFSET                   5
 #define  B_PCIE_LCTL_LD                          BIT4
 #define  B_PCIE_LCTL_LD_OFFSET                   4
 #define  B_PCIE_LCTL_RCBC                        BIT3
 #define  B_PCIE_LCTL_RCBC_OFFSET                 3
 #define  B_PCIE_LCTL_ASPM_SIP                    BIT0
 #define  B_PCIE_LCTL_ASPM_OFFSET                 0
 #define  B_PCIE_LCTL_ASPM_MASK                   0x3

#define  R_PCIE_LSTS                              0x52
 #define  B_PCIE_LSTS_LABS                        BIT15
 #define  B_PCIE_LSTS_LABS_OFFSET                 15
 #define  B_PCIE_LSTS_LBMS                        BIT14
 #define  B_PCIE_LSTS_LBMS_OFFSET                 14
 #define  B_PCIE_LSTS_LA                          BIT13
 #define  B_PCIE_LSTS_LA_OFFSET                   13
 #define  B_PCIE_LSTS_SCC                         BIT12
 #define  B_PCIE_LSTS_SCC_OFFSET                  12
 #define  B_PCIE_LSTS_LT                          BIT11
 #define  B_PCIE_LSTS_LT_OFFSET                   11
 #define  B_PCIE_LSTS_NLW_SIP                     BIT4
 #define  B_PCIE_LSTS_NLW_OFFSET                  4
 #define  B_PCIE_LSTS_NLW_MASK                    0x3F0
 #define  B_PCIE_LSTS_CLS_SIP                     BIT0
 #define  B_PCIE_LSTS_CLS_OFFSET                  0
 #define  B_PCIE_LSTS_CLS_MASK                    0xF

#define  R_PCIE_SLCAP                             0x54
 #define  B_PCIE_SLCAP_PSN_SIP                    BIT19
 #define  B_PCIE_SLCAP_PSN_OFFSET                 19
 #define  B_PCIE_SLCAP_PSN_MASK                   0xFFF80000
 #define  B_PCIE_SLCAP_NCCS                       BIT18
 #define  B_PCIE_SLCAP_NCCS_OFFSET                18
 #define  B_PCIE_SLCAP_EMIP                       BIT17
 #define  B_PCIE_SLCAP_EMIP_OFFSET                17
 #define  B_PCIE_SLCAP_SLS_SIP                    BIT15
 #define  B_PCIE_SLCAP_SLS_OFFSET                 15
 #define  B_PCIE_SLCAP_SLS_MASK                   0x18000
 #define  B_PCIE_SLCAP_SLV_SIP                    BIT7
 #define  B_PCIE_SLCAP_SLV_OFFSET                 7
 #define  B_PCIE_SLCAP_SLV_MASK                   0x7F80
 #define  B_PCIE_SLCAP_HPC                        BIT6
 #define  B_PCIE_SLCAP_HPC_OFFSET                 6
 #define  B_PCIE_SLCAP_HPS                        BIT5
 #define  B_PCIE_SLCAP_HPS_OFFSET                 5
 #define  B_PCIE_SLCAP_PIP                        BIT4
 #define  B_PCIE_SLCAP_PIP_OFFSET                 4
 #define  B_PCIE_SLCAP_AIP                        BIT3
 #define  B_PCIE_SLCAP_AIP_OFFSET                 3
 #define  B_PCIE_SLCAP_MSP                        BIT2
 #define  B_PCIE_SLCAP_MSP_OFFSET                 2
 #define  B_PCIE_SLCAP_PCP                        BIT1
 #define  B_PCIE_SLCAP_PCP_OFFSET                 1
 #define  B_PCIE_SLCAP_ABP                        BIT0
 #define  B_PCIE_SLCAP_ABP_OFFSET                 0

#define  R_PCIE_SLCTL                             0x58
 #define  B_PCIE_SLCTL_ASPLD                      BIT13
 #define  B_PCIE_SLCTL_ASPLD_OFFSET               13
 #define  B_PCIE_SLCTL_DLLSCE                     BIT12
 #define  B_PCIE_SLCTL_DLLSCE_OFFSET              12
 #define  B_PCIE_SLCTL_EMIC                       BIT11
 #define  B_PCIE_SLCTL_EMIC_OFFSET                11
 #define  B_PCIE_SLCTL_PCC                        BIT10
 #define  B_PCIE_SLCTL_PCC_OFFSET                 10
 #define  B_PCIE_SLCTL_PIC                        BIT8
 #define  B_PCIE_SLCTL_PIC_OFFSET                 8
 #define  B_PCIE_SLCTL_PIC_MASK                   0x300
 #define  B_PCIE_SLCTL_AIC                        BIT6
 #define  B_PCIE_SLCTL_AIC_OFFSET                 6
 #define  B_PCIE_SLCTL_AIC_MASK                   0xC0
 #define  B_PCIE_SLCTL_HPE                        BIT5
 #define  B_PCIE_SLCTL_HPE_OFFSET                 5
 #define  B_PCIE_SLCTL_CCE                        BIT4
 #define  B_PCIE_SLCTL_CCE_OFFSET                 4
 #define  B_PCIE_SLCTL_PDE                        BIT3
 #define  B_PCIE_SLCTL_PDE_OFFSET                 3
 #define  B_PCIE_SLCTL_MSE                        BIT2
 #define  B_PCIE_SLCTL_MSE_OFFSET                 2
 #define  B_PCIE_SLCTL_PFE                        BIT1
 #define  B_PCIE_SLCTL_PFE_OFFSET                 1
 #define  B_PCIE_SLCTL_ABE                        BIT0
 #define  B_PCIE_SLCTL_ABE_OFFSET                 0

#define  R_PCIE_SLSTS                             0x5A
 #define  B_PCIE_SLSTS_DLLSC                      BIT8
 #define  B_PCIE_SLSTS_DLLSC_OFFSET               8
 #define  B_PCIE_SLSTS_EMIS                       BIT7
 #define  B_PCIE_SLSTS_EMIS_OFFSET                7
 #define  B_PCIE_SLSTS_PDS                        BIT6
 #define  B_PCIE_SLSTS_PDS_OFFSET                 6
 #define  B_PCIE_SLSTS_MS                         BIT5
 #define  B_PCIE_SLSTS_MS_OFFSET                  5
 #define  B_PCIE_SLSTS_CC                         BIT4
 #define  B_PCIE_SLSTS_CC_OFFSET                  4
 #define  B_PCIE_SLSTS_PDC                        BIT3
 #define  B_PCIE_SLSTS_PDC_OFFSET                 3
 #define  B_PCIE_SLSTS_MSC                        BIT2
 #define  B_PCIE_SLSTS_MSC_OFFSET                 2
 #define  B_PCIE_SLSTS_PFD                        BIT1
 #define  B_PCIE_SLSTS_PFD_OFFSET                 1
 #define  B_PCIE_SLSTS_ABP                        BIT0
 #define  B_PCIE_SLSTS_ABP_OFFSET                 0

#define  R_PCIE_RCTL                              0x5C
 #define  B_PCIE_RCTL_PIE                         BIT3
 #define  B_PCIE_RCTL_PIE_OFFSET                  3
 #define  B_PCIE_RCTL_SFE                         BIT2
 #define  B_PCIE_RCTL_SFE_OFFSET                  2
 #define  B_PCIE_RCTL_SNE                         BIT1
 #define  B_PCIE_RCTL_SNE_OFFSET                  1
 #define  B_PCIE_RCTL_SCE                         BIT0
 #define  B_PCIE_RCTL_SCE_OFFSET                  0

#define  R_PCIE_RSTS                              0x60
 #define  B_PCIE_RSTS_PP                          BIT17
 #define  B_PCIE_RSTS_PP_OFFSET                   17
 #define  B_PCIE_RSTS_PS                          BIT16
 #define  B_PCIE_RSTS_PS_OFFSET                   16
 #define  B_PCIE_RSTS_RID                         BIT0
 #define  B_PCIE_RSTS_RID_OFFSET                  0
 #define  B_PCIE_RSTS_RID_MASK                    0xFFFF

#define  R_PCIE_DCAP2                             0x64
 #define  B_PCIE_DCAP2_OBFFS                     (BIT19 | BIT18) ///< OBFF Supported
 #define  B_PCIE_DCAP2_OBFFS_SIP                  BIT18
 #define  B_PCIE_DCAP2_OBFFS_OFFSET               18
 #define  V_PCIE_DCAP2_OBFFS_WAKE_ONLY            2
 #define  B_PCIE_DCAP2_PX10BTRS                   BIT17
 #define  B_PCIE_DCAP2_PX10BTCS                   BIT16
 #define  B_PCIE_DCAP2_OBFFS_MASK                 0xC0000
 #define  B_PCIE_DCAP2_LTRMS                      BIT11
 #define  B_PCIE_DCAP2_LTRMS_OFFSET               11
 #define  B_PCIE_DCAP2_AC128BS                    BIT9
 #define  B_PCIE_DCAP2_AC128BS_OFFSET             9
 #define  B_PCIE_DCAP2_AC64BS                     BIT8
 #define  B_PCIE_DCAP2_AC64BS_OFFSET              8
 #define  B_PCIE_DCAP2_AC32BS                     BIT7
 #define  B_PCIE_DCAP2_AC32BS_OFFSET              7
 #define  B_PCIE_DCAP2_ARS                        BIT6
 #define  B_PCIE_DCAP2_ARS_OFFSET                 6
 #define  B_PCIE_DCAP2_AFS                        BIT5
 #define  B_PCIE_DCAP2_AFS_OFFSET                 5
 #define  B_PCIE_DCAP2_CTDS                       BIT4
 #define  B_PCIE_DCAP2_CTDS_OFFSET                4
 #define  B_PCIE_DCAP2_CTRS                       BIT0
 #define  B_PCIE_DCAP2_CTRS_OFFSET                0
 #define  B_PCIE_DCAP2_CTRS_MASK                  0xF

#define  R_PCIE_DCTL2                             0x68
 #define  B_PCIE_DCTL2_OBFFEN_SIP                 BIT13
 #define  B_PCIE_DCTL2_OBFFEN_OFFSET              13
 #define  B_PCIE_DCTL2_OBFFEN_MASK                0x6000
 #define  B_PCIE_DCTL2_PX10BTRE                   BIT11
 #define  B_PCIE_DCTL2_LTREN                      BIT10
 #define  B_PCIE_DCTL2_LTREN_OFFSET               10
 #define  B_PCIE_DCTL2_AEB                        BIT7
 #define  B_PCIE_DCTL2_AEB_OFFSET                 7
 #define  B_PCIE_DCTL2_ARE                        BIT6
 #define  B_PCIE_DCTL2_ARE_OFFSET                 6
 #define  B_PCIE_DCTL2_AFE                        BIT5
 #define  B_PCIE_DCTL2_AFE_OFFSET                 5
 #define  B_PCIE_DCTL2_CTD                        BIT4
 #define  B_PCIE_DCTL2_CTD_OFFSET                 4
 #define  B_PCIE_DCTL2_CTV_SIP                    BIT0
 #define  B_PCIE_DCTL2_CTV_OFFSET                 0
 #define  B_PCIE_DCTL2_CTV_MASK                   0xF

#define  R_PCIE_DSTS2                             0x6A

#define  R_PCIE_LCAP2                             0x6C
 #define  B_PCIE_LCAP2_TRPDS                      BIT24
 #define  B_PCIE_LCAP2_RPDS                       BIT23
 #define  B_PCIE_LCAP2_LSOSRSS                    BIT16
 #define  B_PCIE_LCAP2_LSOSRSS_OFFSET             16
 #define  B_PCIE_LCAP2_LSOSRSS_MASK               0x7F0000
 #define  B_PCIE_LCAP2_LSOSGSSV                   BIT9
 #define  B_PCIE_LCAP2_LSOSGSSV_OFFSET            9
 #define  B_PCIE_LCAP2_LSOSGSSV_MASK              0xFE00
 #define  B_PCIE_LCAP2_CS                         BIT8
 #define  B_PCIE_LCAP2_CS_OFFSET                  8
 #define  B_PCIE_LCAP2_SLSV                       BIT1
 #define  B_PCIE_LCAP2_SLSV_OFFSET                1
 #define  B_PCIE_LCAP2_SLSV_MASK                  0xFE

#define  R_PCIE_LCTL2                             0x70
 #define  B_PCIE_LCTL2_CD                         BIT12
 #define  B_PCIE_LCTL2_CD_OFFSET                  12
 #define  B_PCIE_LCTL2_CD_MASK                    0xF000
 #define  B_PCIE_LCTL2_CSOS                       BIT11
 #define  B_PCIE_LCTL2_CSOS_OFFSET                11
 #define  B_PCIE_LCTL2_EMC                        BIT10
 #define  B_PCIE_LCTL2_EMC_OFFSET                 10
 #define  B_PCIE_LCTL2_TM                         BIT7
 #define  B_PCIE_LCTL2_TM_OFFSET                  7
 #define  B_PCIE_LCTL2_TM_MASK                    0x380
 #define  B_PCIE_LCTL2_SD                         BIT6
 #define  B_PCIE_LCTL2_SD_OFFSET                  6
 #define  B_PCIE_LCTL2_HASD                       BIT5
 #define  B_PCIE_LCTL2_HASD_OFFSET                5
 #define  B_PCIE_LCTL2_EC                         BIT4
 #define  B_PCIE_LCTL2_EC_OFFSET                  4
 #define  B_PCIE_LCTL2_TLS_SIP                    BIT0
 #define  B_PCIE_LCTL2_TLS_OFFSET                 0
 #define  B_PCIE_LCTL2_TLS_MASK                   0xF
  #define V_PCIE_LCTL2_TLS_GEN1                   1

#define  R_PCIE_LSTS2                             0x72
 #define  B_PCIE_LSTS2_LER                        BIT5
 #define  B_PCIE_LSTS2_LER_OFFSET                 5
 #define  B_PCIE_LSTS2_EQP3S                      BIT4
 #define  B_PCIE_LSTS2_EQP3S_OFFSET               4
 #define  B_PCIE_LSTS2_EQP2S                      BIT3
 #define  B_PCIE_LSTS2_EQP2S_OFFSET               3
 #define  B_PCIE_LSTS2_EQP1S                      BIT2
 #define  B_PCIE_LSTS2_EQP1S_OFFSET               2
 #define  B_PCIE_LSTS2_EQC                        BIT1
 #define  B_PCIE_LSTS2_EQC_OFFSET                 1
 #define  B_PCIE_LSTS2_CDL                        BIT0
 #define  B_PCIE_LSTS2_CDL_OFFSET                 0

#define  R_PCIE_SLCAP2                            0x74

#define  R_PCIE_SLCTL2                            0x78

#define  R_PCIE_SLSTS2                            0x7A

#define  R_PCIE_MID                               0x80
 #define  B_PCIE_MID_NEXT                         BIT8
 #define  B_PCIE_MID_NEXT_OFFSET                  8
 #define  B_PCIE_MID_NEXT_MASK                    0xFF00
 #define  B_PCIE_MID_CID                          BIT0
 #define  B_PCIE_MID_CID_OFFSET                   0
 #define  B_PCIE_MID_CID_MASK                     0xFF

#define  R_PCIE_MC                                0x82
 #define  B_PCIE_MC_C64                           BIT7
 #define  B_PCIE_MC_C64_OFFSET                    7
 #define  B_PCIE_MC_MME                           BIT4
 #define  B_PCIE_MC_MME_OFFSET                    4
 #define  B_PCIE_MC_MME_MASK                      0x70
 #define  B_PCIE_MC_MMC                           BIT1
 #define  B_PCIE_MC_MMC_OFFSET                    1
 #define  B_PCIE_MC_MMC_MASK                      0xE
 #define  B_PCIE_MC_MSIE                          BIT0
 #define  B_PCIE_MC_MSIE_OFFSET                   0

#define  R_PCIE_MA                                0x84
 #define  B_PCIE_MA_ADDR                          BIT2
 #define  B_PCIE_MA_ADDR_OFFSET                   2
 #define  B_PCIE_MA_ADDR_MASK                     0xFFFFFFFC

#define  R_PCIE_MD                                0x88
 #define  B_PCIE_MD_DATA                          BIT0
 #define  B_PCIE_MD_DATA_OFFSET                   0
 #define  B_PCIE_MD_DATA_MASK                     0xFFFF

#define  R_PCIE_SVCAP                             0x90
 #define  B_PCIE_SVCAP_NEXT                       BIT8
 #define  B_PCIE_SVCAP_NEXT_OFFSET                8
 #define  B_PCIE_SVCAP_NEXT_MASK                  0xFF00
 #define  B_PCIE_SVCAP_CID                        BIT0
 #define  B_PCIE_SVCAP_CID_OFFSET                 0
 #define  B_PCIE_SVCAP_CID_MASK                   0xFF

#define  R_PCIE_SVID                              0x94
 #define  B_PCIE_SVID_SID                         BIT16
 #define  B_PCIE_SVID_SID_OFFSET                  16
 #define  B_PCIE_SVID_SID_MASK                    0xFFFF0000
 #define  B_PCIE_SVID_SVID                        BIT0
 #define  B_PCIE_SVID_SVID_OFFSET                 0
 #define  B_PCIE_SVID_SVID_MASK                   0xFFFF

#define  R_PCIE_PMCAP                             0xA0
 #define  B_PCIE_PMCAP_NEXT                       BIT8
 #define  B_PCIE_PMCAP_NEXT_OFFSET                8
 #define  B_PCIE_PMCAP_NEXT_MASK                  0xFF00
 #define  B_PCIE_PMCAP_CID                        BIT0
 #define  B_PCIE_PMCAP_CID_OFFSET                 0
 #define  B_PCIE_PMCAP_CID_MASK                   0xFF

#define  R_PCIE_PMC                               0xA2
 #define  B_PCIE_PMC_PMES_SIP                     BIT11
 #define  B_PCIE_PMC_PMES_OFFSET                  11
 #define  B_PCIE_PMC_PMES_MASK                    0xF800
 #define  B_PCIE_PMC_D2S                          BIT10
 #define  B_PCIE_PMC_D2S_OFFSET                   10
 #define  B_PCIE_PMC_D1S                          BIT9
 #define  B_PCIE_PMC_D1S_OFFSET                   9
 #define  B_PCIE_PMC_AC                           BIT6
 #define  B_PCIE_PMC_AC_OFFSET                    6
 #define  B_PCIE_PMC_AC_MASK                      0x1C0
 #define  B_PCIE_PMC_DSI                          BIT5
 #define  B_PCIE_PMC_DSI_OFFSET                   5
 #define  B_PCIE_PMC_PMEC                         BIT3
 #define  B_PCIE_PMC_PMEC_OFFSET                  3
 #define  B_PCIE_PMC_VS                           BIT0
 #define  B_PCIE_PMC_VS_OFFSET                    0
 #define  B_PCIE_PMC_VS_MASK                      0x7

#define  R_PCIE_PMCS                              0xA4
 #define  B_PCIE_PMCS_DTA                         BIT24
 #define  B_PCIE_PMCS_DTA_OFFSET                  24
 #define  B_PCIE_PMCS_DTA_MASK                    0xFF000000
 #define  B_PCIE_PMCS_BPCE                        BIT23
 #define  B_PCIE_PMCS_BPCE_OFFSET                 23
 #define  B_PCIE_PMCS_B23S                        BIT22
 #define  B_PCIE_PMCS_B23S_OFFSET                 22
 #define  B_PCIE_PMCS_PMES                        BIT15
 #define  B_PCIE_PMCS_PMES_OFFSET                 15
 #define  B_PCIE_PMCS_DSC                         BIT13
 #define  B_PCIE_PMCS_DSC_OFFSET                  13
 #define  B_PCIE_PMCS_DSC_MASK                    0x6000
 #define  B_PCIE_PMCS_DSEL                        BIT9
 #define  B_PCIE_PMCS_DSEL_OFFSET                 9
 #define  B_PCIE_PMCS_DSEL_MASK                   0x1E00
 #define  B_PCIE_PMCS_PMEE                        BIT8
 #define  B_PCIE_PMCS_PMEE_OFFSET                 8
 #define  B_PCIE_PMCS_NSR                         BIT3
 #define  B_PCIE_PMCS_NSR_OFFSET                  3
 #define  B_PCIE_PMCS_PS_SIP                      BIT0
 #define  B_PCIE_PMCS_PS_OFFSET                   0
 #define  B_PCIE_PMCS_PS_MASK                     0x3

#define  R_PCIE_CCFG                              0xD0
 #define  B_PCIE_CCFG_CRE                         BIT31
 #define  B_PCIE_CCFG_CRE_OFFSET                  31
 #define  B_PCIE_CCFG_IORE                        BIT30
 #define  B_PCIE_CCFG_IORE_OFFSET                 30
 #define  B_PCIE_CCFG_UMRPD                       BIT26
 #define  B_PCIE_CCFG_UMRPD_OFFSET                26
 #define  B_PCIE_CCFG_UPMWPD                      BIT25
 #define  B_PCIE_CCFG_UPMWPD_OFFSET               25
 #define  B_PCIE_CCFG_UPSD                        BIT24
 #define  B_PCIE_CCFG_UPSD_OFFSET                 24
 #define  B_PCIE_CCFG_UNSD                        BIT23
 #define  B_PCIE_CCFG_UNSD_OFFSET                 23
 #define  B_PCIE_CCFG_NPAS                        BIT17
 #define  B_PCIE_CCFG_NPAS_OFFSET                 17
 #define  B_PCIE_CCFG_NPAS_MASK                   0x7E0000
 #define  B_PCIE_CCFG_NPAP                        BIT16
 #define  B_PCIE_CCFG_NPAP_OFFSET                 16
 #define  B_PCIE_CCFG_DCGEISMA                    BIT15
 #define  B_PCIE_CCFG_DCGEISMA_OFFSET             15
 #define  B_PCIE_CCFG_UNRD                        BIT12
 #define  B_PCIE_CCFG_UNRD_OFFSET                 12
 #define  B_PCIE_CCFG_UNRD_MASK                   0x3000
 #define  B_PCIE_CCFG_RBMS                        BIT11
 #define  B_PCIE_CCFG_RBMS_OFFSET                 11
 #define  B_PCIE_CCFG_MRNPC                       BIT9
 #define  B_PCIE_CCFG_MRNPC_OFFSET                9
 #define  B_PCIE_CCFG_MRPC                        BIT8
 #define  B_PCIE_CCFG_MRPC_OFFSET                 8
 #define  B_PCIE_CCFG_UNRS                        BIT4
 #define  B_PCIE_CCFG_UNRS_OFFSET                 4
 #define  B_PCIE_CCFG_UNRS_MASK                   0x70
 #define  V_PCIE_CCFG_UNRS_128B                   0
 #define  V_PCIE_CCFG_UNRS_512B                   2
 #define  V_PCIE_CCFG_UNRS_256B                   1
 #define  V_PCIE_CCFG_UNRS_64B                    7
 #define  B_PCIE_CCFG_UPRS                        BIT0
 #define  B_PCIE_CCFG_UPRS_OFFSET                 0
 #define  B_PCIE_CCFG_UPRS_MASK                   0x7
 #define  V_PCIE_CCFG_UPRS_128B                   0
 #define  V_PCIE_CCFG_UPRS_256B                   1
 #define  V_PCIE_CCFG_UPRS_512B                   2
 #define  V_PCIE_CCFG_UPRS_64B                    7


#define  R_PCIE_MPC2                              0xD4
 #define  B_PCIE_MPC2_L1SSESE                     BIT30
 #define  B_PCIE_MPC2_G1G2AUTOINVERT              BIT28
 #define  B_PCIE_MPC2_G1G2AUTOINVERT_OFFSET       28
 #define  B_PCIE_MPC2_PLLWAIT                     BIT24
 #define  B_PCIE_MPC2_PLLWAIT_OFFSET              24
 #define  B_PCIE_MPC2_PLLWAIT_MASK                0x7000000
 #define  B_PCIE_MPC2_RUD                         BIT23
 #define  B_PCIE_MPC2_RUD_OFFSET                  23
 #define  B_PCIE_MPC2_MIPIPLLC                    BIT22
 #define  B_PCIE_MPC2_MIPIPLLC_OFFSET             22
 #define  B_PCIE_MPC2_GEN2PLLC                    BIT21
 #define  B_PCIE_MPC2_GEN2PLLC_OFFSET             21
 #define  B_PCIE_MPC2_GEN3PLLC                    BIT20
 #define  B_PCIE_MPC2_GEN3PLLC_OFFSET             20
 #define  B_PCIE_MPC2_DNPRL                       BIT19
 #define  B_PCIE_MPC2_DNPRL_OFFSET                19
 #define  B_PCIE_MPC2_MACPHYIMPGHPU               BIT18
 #define  B_PCIE_MPC2_MACPHYIMPGHPU_OFFSET        18
 #define  B_PCIE_MPC2_RXL0SEBPRO                  BIT17
 #define  B_PCIE_MPC2_RXL0SEBPRO_OFFSET           17
 #define  B_PCIE_MPC2_DISPLLEWL1SE                BIT16
 #define  B_PCIE_MPC2_DISPLLEWL1SE_OFFSET         16
 #define  B_PCIE_MPC2_ORCE                        BIT14
 #define  B_PCIE_MPC2_ORCE_OFFSET                 14
 #define  B_PCIE_MPC2_ORCE_MASK                   0xC000
 #define  B_PCIE_MPC2_ORCR                        BIT13
 #define  B_PCIE_MPC2_ORCR_OFFSET                 13
 #define  B_PCIE_MPC2_PTNFAE                      BIT12
 #define  B_PCIE_MPC2_PTNFAE_OFFSET               12
 #define  B_PCIE_MPC2_IPF                         BIT11
 #define  B_PCIE_MPC2_IPF_OFFSET                  11
 #define  B_PCIE_MPC2_ITCUM                       BIT10
 #define  B_PCIE_MPC2_ITCUM_OFFSET                10
 #define  B_PCIE_MPC2_TLPF                        BIT9
 #define  B_PCIE_MPC2_TLPF_OFFSET                 9
 #define  B_PCIE_MPC2_CAM                         BIT8
 #define  B_PCIE_MPC2_CAM_OFFSET                  8
 #define  B_PCIE_MPC2_CDRM                        BIT7
 #define  B_PCIE_MPC2_CDRM_OFFSET                 7
 #define  B_PCIE_MPC2_LSTP                        BIT6
 #define  B_PCIE_MPC2_LSTP_OFFSET                 6
 #define  B_PCIE_MPC2_IEIME                       BIT5
 #define  B_PCIE_MPC2_IEIME_OFFSET                5
 #define  B_PCIE_MPC2_ASPMCOEN                    BIT4
 #define  B_PCIE_MPC2_ASPMCOEN_OFFSET             4
 #define  B_PCIE_MPC2_ASPMCO                      BIT2
 #define  B_PCIE_MPC2_ASPMCO_OFFSET               2
 #define  B_PCIE_MPC2_ASPMCO_MASK                 0xC
 #define  B_PCIE_MPC2_EOIFD                       BIT1
 #define  B_PCIE_MPC2_EOIFD_OFFSET                1
 #define  B_PCIE_MPC2_L1CTM                       BIT0
 #define  B_PCIE_MPC2_L1CTM_OFFSET                0

#define  R_PCIE_MPC                               0xD8
 #define  B_PCIE_MPC_PMCE                         BIT31
 #define  B_PCIE_MPC_PMCE_OFFSET                  31
 #define  B_PCIE_MPC_HPCE                         BIT30
 #define  B_PCIE_MPC_HPCE_OFFSET                  30
 #define  B_PCIE_MPC_LHO                          BIT29
 #define  B_PCIE_MPC_LHO_OFFSET                   29
 #define  B_PCIE_MPC_ATE                          BIT28
 #define  B_PCIE_MPC_ATE_OFFSET                   28
 #define  B_PCIE_MPC_MMBNCE                       BIT27
 #define  B_PCIE_MPC_MMBNCE_OFFSET                27
 #define  B_PCIE_MPC_P8XDE                        BIT26
 #define  B_PCIE_MPC_P8XDE_OFFSET                 26
 #define  B_PCIE_MPC_IRRCE                        BIT25
 #define  B_PCIE_MPC_IRRCE_OFFSET                 25
 #define  B_PCIE_MPC_BMERCE                       BIT24
 #define  B_PCIE_MPC_BMERCE_OFFSET                24
 #define  B_PCIE_MPC_FORCEDET                     BIT22
 #define  B_PCIE_MPC_FORCEDET_OFFSET              22
 #define  B_PCIE_MPC_FCDL1E                       BIT21
 #define  B_PCIE_MPC_FCDL1E_OFFSET                21
 #define  B_PCIE_MPC_UCEL                         BIT18
 #define  B_PCIE_MPC_UCEL_OFFSET                  18
 #define  B_PCIE_MPC_UCEL_MASK                    0x1C0000
 #define  B_PCIE_MPC_CCEL                         BIT15
 #define  B_PCIE_MPC_CCEL_OFFSET                  15
 #define  B_PCIE_MPC_CCEL_MASK                    0x38000
 #define  B_PCIE_MPC_PCIESD                       BIT13
 #define  B_PCIE_MPC_PCIESD_OFFSET                13
 #define  B_PCIE_MPC_PCIESD_MASK                  0x6000
 #define  B_PCIE_MPC_SERL                         BIT12
 #define  B_PCIE_MPC_SERL_OFFSET                  12
 #define  B_PCIE_MPC_AT                           BIT8
 #define  B_PCIE_MPC_AT_OFFSET                    8
 #define  B_PCIE_MPC_AT_MASK                      0xF00
 #define  B_PCIE_MPC_PAE                          BIT7
 #define  B_PCIE_MPC_PAE_OFFSET                   7
 #define  B_PCIE_MPC_FCP                          BIT4
 #define  B_PCIE_MPC_FCP_OFFSET                   4
 #define  B_PCIE_MPC_FCP_MASK                     0x70
 #define  B_PCIE_MPC_MCTPSE                       BIT3
 #define  B_PCIE_MPC_MCTPSE_OFFSET                3
 #define  B_PCIE_MPC_BT                           BIT2
 #define  B_PCIE_MPC_BT_OFFSET                    2
 #define  B_PCIE_MPC_HPME                         BIT1
 #define  B_PCIE_MPC_HPME_OFFSET                  1
 #define  B_PCIE_MPC_PMME                         BIT0
 #define  B_PCIE_MPC_PMME_OFFSET                  0
 #define  V_PCIE_MPC_PCIESD_GEN1                  1
 #define  V_PCIE_MPC_PCIESD_GEN2                  2
 #define  V_PCIE_MPC_PCIESD_GEN3                  3
 #define  V_PCIE_MPC_PCIESD_GEN4                  4

#define  R_PCIE_SMSCS                             0xDC
 #define  B_PCIE_SMSCS_PMCS                       BIT31
 #define  B_PCIE_SMSCS_PMCS_OFFSET                31
 #define  B_PCIE_SMSCS_HPCS                       BIT30
 #define  B_PCIE_SMSCS_HPCS_OFFSET                30
 #define  B_PCIE_SMSCS_PMRVSCIS                   BIT12
 #define  B_PCIE_SMSCS_PMRVSCIS_OFFSET            12
 #define  B_PCIE_SMSCS_PMRVSMIS                   BIT11
 #define  B_PCIE_SMSCS_PMRVSMIS_OFFSET            11
 #define  B_PCIE_SMSCS_DPCSCIS                    BIT10
 #define  B_PCIE_SMSCS_DPCSCIS_OFFSET             10
 #define  B_PCIE_SMSCS_DPCSMIS                    BIT9
 #define  B_PCIE_SMSCS_DPCSMIS_OFFSET             9
 #define  B_PCIE_SMSCS_RPPIOERRSCIS               BIT8
 #define  B_PCIE_SMSCS_RPPIOERRSCIS_OFFSET        8
 #define  B_PCIE_SMSCS_RPPIOERRSMIS               BIT7
 #define  B_PCIE_SMSCS_RPPIOERRSMIS_OFFSET        7
 #define  B_PCIE_SMSCS_LERSCIS                    BIT6
 #define  B_PCIE_SMSCS_LERSCIS_OFFSET             6
 #define  B_PCIE_SMSCS_LERSMIS                    BIT5
 #define  B_PCIE_SMSCS_LERSMIS_OFFSET             5
 #define  B_PCIE_SMSCS_HPLAS                      BIT4
 #define  B_PCIE_SMSCS_HPLAS_OFFSET               4
 #define  B_PCIE_SMSCS_HPCCM                      BIT3
 #define  B_PCIE_SMSCS_HPCCM_OFFSET               3
 #define  B_PCIE_SMSCS_HPABM                      BIT2
 #define  B_PCIE_SMSCS_HPABM_OFFSET               2
 #define  B_PCIE_SMSCS_HPPDM                      BIT1
 #define  B_PCIE_SMSCS_HPPDM_OFFSET               1
 #define  B_PCIE_SMSCS_PMMS                       BIT0
 #define  B_PCIE_SMSCS_PMMS_OFFSET                0

#define  R_PCIE_SPR                               0xE0
 #define  B_PCIE_SPR_NSCB                         BIT6
 #define  B_PCIE_SPR_NSCB_OFFSET                  6
 #define  B_PCIE_SPR_NSCB_MASK                    0xC0
 #define  B_PCIE_SPR_DLRFAD                       BIT5
 #define  B_PCIE_SPR_DLRFAD_OFFSET                5
 #define  B_PCIE_SPR_BDFCP                        BIT4
 #define  B_PCIE_SPR_BDFCP_OFFSET                 4
 #define  B_PCIE_SPR_SCB                          BIT0
 #define  B_PCIE_SPR_SCB_OFFSET                   0
 #define  B_PCIE_SPR_SCB_MASK                     0xF

#define  R_PCIE_RPDCGEN                           0xE1
 #define  B_PCIE_RPDCGEN_RPSCGEN                  BIT7
 #define  B_PCIE_RPDCGEN_PTOCGE                   BIT6
 #define  B_PCIE_RPDCGEN_PTOCGE_OFFSET            6
 #define  B_PCIE_RPDCGEN_LCLKREQEN                BIT5
 #define  B_PCIE_RPDCGEN_LCLKREQEN_OFFSET         5
 #define  B_PCIE_RPDCGEN_BBCLKREQEN               BIT4
 #define  B_PCIE_RPDCGEN_BBCLKREQEN_OFFSET        4
 #define  B_PCIE_RPDCGEN_SRDBCGEN                 BIT2
 #define  B_PCIE_RPDCGEN_SRDBCGEN_OFFSET          2
 #define  B_PCIE_RPDCGEN_RPDLCGEN                 BIT1
 #define  B_PCIE_RPDCGEN_RPDLCGEN_OFFSET          1
 #define  B_PCIE_RPDCGEN_RPDBCGEN                 BIT0
 #define  B_PCIE_RPDCGEN_RPDBCGEN_OFFSET          0

#define  R_PCIE_RPPGEN                            0xE2
 #define  B_PCIE_RPPGEN_MCWPGS                    BIT7
 #define  B_PCIE_RPPGEN_MCWPGS_OFFSET             7
 #define  B_PCIE_RPPGEN_PTOTOP                    BIT6
 #define  B_PCIE_RPPGEN_PTOTOP_OFFSET             6
 #define  B_PCIE_RPPGEN_MDLSWPGEXA                BIT5
 #define  B_PCIE_RPPGEN_MDLSWPGEXA_OFFSET         5
 #define  B_PCIE_RPPGEN_SEOSCGE                   BIT4
 #define  B_PCIE_RPPGEN_SEOSCGE_OFFSET            4
 #define  B_PCIE_RPPGEN_L23R2DT                   BIT3
 #define  B_PCIE_RPPGEN_L23R2DT_OFFSET            3
 #define  B_PCIE_RPPGEN_L23ER                     BIT2
 #define  B_PCIE_RPPGEN_L23ER_OFFSET              2
 #define  B_PCIE_RPPGEN_MDLSWPGEA                 BIT1
 #define  B_PCIE_RPPGEN_MDLSWPGEA_OFFSET          1
 #define  B_PCIE_RPPGEN_MDLSWPR                   BIT0
 #define  B_PCIE_RPPGEN_MDLSWPR_OFFSET            0

#define  R_PCIE_LTRL                              0xE4
 #define  B_PCIE_LTRL_LTRNSLF                     BIT16
 #define  B_PCIE_LTRL_LTRNSLF_OFFSET              16
 #define  B_PCIE_LTRL_LTRNSLF_MASK                0xFFFF0000
 #define  B_PCIE_LTRL_LTRSLF                      BIT0
 #define  B_PCIE_LTRL_LTRSLF_OFFSET               0
 #define  B_PCIE_LTRL_LTRSLF_MASK                 0xFFFF

#define  R_PCIE_PWRCTL                            0xE8
 #define  B_PCIE_PWRCTL_L1SSVNNRE                 BIT26
 #define  B_PCIE_PWRCTL_L1SSVNNRE_OFFSET          26
 #define  B_PCIE_PWRCTL_ECF128B130B               BIT24
 #define  B_PCIE_PWRCTL_ECF128B130B_OFFSET        24
 #define  B_PCIE_PWRCTL_LIFECF                    BIT23
 #define  B_PCIE_PWRCTL_LIFECF_OFFSET             23
 #define  B_PCIE_PWRCTL_ISHCF                     BIT22
 #define  B_PCIE_PWRCTL_ISHCF_OFFSET              22
 #define  B_PCIE_PWRCTL_BISHB                     BIT21
 #define  B_PCIE_PWRCTL_BISHB_OFFSET              21
 #define  B_PCIE_PWRCTL_LTSSMRTC                  BIT20
 #define  B_PCIE_PWRCTL_LTSSMRTC_OFFSET           20
 #define  B_PCIE_PWRCTL_LWUED                     BIT19
 #define  B_PCIE_PWRCTL_LWUED_OFFSET              19
 #define  B_PCIE_PWRCTL_G3SNB                     BIT18
 #define  B_PCIE_PWRCTL_G3SNB_OFFSET              18
 #define  B_PCIE_PWRCTL_WPDMPGEP                  BIT17
 #define  B_PCIE_PWRCTL_WPDMPGEP_OFFSET           17
 #define  B_PCIE_PWRCTL_DLP                       BIT16
 #define  B_PCIE_PWRCTL_DLP_OFFSET                16
 #define  B_PCIE_PWRCTL_DBUPI                     BIT15
 #define  B_PCIE_PWRCTL_DBUPI_OFFSET              15
 #define  B_PCIE_PWRCTL_ILSVRX                    BIT14
 #define  B_PCIE_PWRCTL_ILSVRX_OFFSET             14
 #define  B_PCIE_PWRCTL_TXSWING                   BIT13
 #define  B_PCIE_PWRCTL_TXSWING_OFFSET            13
 #define  B_PCIE_PWRCTL_EFSOSTOETR                BIT12
 #define  B_PCIE_PWRCTL_EFSOSTOETR_OFFSET         12
 #define  B_PCIE_PWRCTL_ATODEDTT                  BIT11
 #define  B_PCIE_PWRCTL_ATODEDTT_OFFSET           11
 #define  B_PCIE_PWRCTL_HRBF                      BIT10
 #define  B_PCIE_PWRCTL_HRBF_OFFSET               10
 #define  B_PCIE_PWRCTL_SELAQ                     BIT9
 #define  B_PCIE_PWRCTL_SELAQ_OFFSET              9
 #define  B_PCIE_PWRCTL_RPTFSMWI                  BIT8
 #define  B_PCIE_PWRCTL_RPTFSMWI_OFFSET           8
 #define  B_PCIE_PWRCTL_SCTEM                     BIT7
 #define  B_PCIE_PWRCTL_SCTEM_OFFSET              7
 #define  B_PCIE_PWRCTL_PCSCEIOST                 BIT6
 #define  B_PCIE_PWRCTL_PCSCEIOST_OFFSET          6
 #define  B_PCIE_PWRCTL_ISCT                      BIT5
 #define  B_PCIE_PWRCTL_ISCT_OFFSET               5
 #define  B_PCIE_PWRCTL_LTRR                      BIT4
 #define  B_PCIE_PWRCTL_LTRR_OFFSET               4
 #define  B_PCIE_PWRCTL_RPSEWL                    BIT2
 #define  B_PCIE_PWRCTL_RPSEWL_OFFSET             2
 #define  B_PCIE_PWRCTL_RPSEWL_MASK               0xC
 #define  B_PCIE_PWRCTL_RPL1SQPOL                 BIT1
 #define  B_PCIE_PWRCTL_RPL1SQPOL_OFFSET          1
 #define  B_PCIE_PWRCTL_RPDTSQPOL                 BIT0
 #define  B_PCIE_PWRCTL_RPDTSQPOL_OFFSET          0

#define  R_PCIE_DC                                0xEC
 #define  B_PCIE_DC_IOAPICRL                      BIT24
 #define  B_PCIE_DC_IOAPICRL_OFFSET               24
 #define  B_PCIE_DC_IOAPICRL_MASK                 0xFF000000
 #define  B_PCIE_DC_IOAPICRB                      BIT16
 #define  B_PCIE_DC_IOAPICRB_OFFSET               16
 #define  B_PCIE_DC_IOAPICRB_MASK                 0xFF0000
 #define  B_PCIE_DC_DCT1C                         BIT15
 #define  B_PCIE_DC_DCT1C_OFFSET                  15
 #define  B_PCIE_DC_DCT0C                         BIT14
 #define  B_PCIE_DC_DCT0C_OFFSET                  14
 #define  B_PCIE_DC_COM                           BIT13
 #define  B_PCIE_DC_COM_OFFSET                    13
 #define  B_PCIE_DC_ECD                           BIT3
 #define  B_PCIE_DC_ECD_OFFSET                    3
 #define  B_PCIE_DC_PCIBEM                        BIT2
 #define  B_PCIE_DC_PCIBEM_OFFSET                 2
 #define  B_PCIE_DC_VC0NSAO                       BIT1
 #define  B_PCIE_DC_VC0NSAO_OFFSET                1
 #define  B_PCIE_DC_VC0NSAOV                      BIT0
 #define  B_PCIE_DC_VC0NSAOV_OFFSET               0

#define  R_PCIE_IPCS                              0xF0
 #define  B_PCIE_IPCS_HBPCIBSN                    BIT20
 #define  B_PCIE_IPCS_HBPCIBSN_OFFSET             20
 #define  B_PCIE_IPCS_HBPCIBSN_MASK               0xF00000
 #define  B_PCIE_IPCS_PPPCIBSN                    BIT16
 #define  B_PCIE_IPCS_PPPCIBSN_OFFSET             16
 #define  B_PCIE_IPCS_PPPCIBSN_MASK               0xF0000
 #define  B_PCIE_IPCS_PRIC                        BIT12
 #define  B_PCIE_IPCS_PRIC_OFFSET                 12
 #define  B_PCIE_IPCS_PRIC_MASK                   0x7000
 #define  B_PCIE_IPCS_IMPS                        BIT8
 #define  B_PCIE_IPCS_IMPS_OFFSET                 8
 #define  B_PCIE_IPCS_IMPS_MASK                   0x700
 #define  V_PCIE_IPCS_IMPS                        0x7
 #define  B_PCIE_IPCS_IMRS                        BIT4
 #define  B_PCIE_IPCS_IMRS_OFFSET                 4
 #define  B_PCIE_IPCS_IMRS_MASK                   0x70
 #define  B_PCIE_IPCS_URD                         BIT1
 #define  B_PCIE_IPCS_URD_OFFSET                  1
 #define  B_PCIE_IPCS_URRE                        BIT0
 #define  B_PCIE_IPCS_URRE_OFFSET                 0

#define  R_PCIE_PHYCTL2                           0xF5
 #define  B_PCIE_PHYCTL2_TDFT                     BIT6
 #define  B_PCIE_PHYCTL2_TDFT_OFFSET              6
 #define  B_PCIE_PHYCTL2_TDFT_MASK                0xC0
 #define  B_PCIE_PHYCTL2_TXCFGCHGWAIT             BIT4
 #define  B_PCIE_PHYCTL2_TXCFGCHGWAIT_OFFSET      4
 #define  B_PCIE_PHYCTL2_TXCFGCHGWAIT_MASK        0x30
 #define  B_PCIE_PHYCTL2_BLKPLLEN                 BIT2
 #define  B_PCIE_PHYCTL2_BLKPLLEN_OFFSET          2
 #define  B_PCIE_PHYCTL2_PXPG3PLLOFFEN            BIT1
 #define  B_PCIE_PHYCTL2_PXPG3PLLOFFEN_OFFSET     1
 #define  B_PCIE_PHYCTL2_PXPG2PLLOFFEN            BIT0
 #define  B_PCIE_PHYCTL2_PXPG2PLLOFFEN_OFFSET     0

#define  R_PCIE_PHYCTL3                           0xF6
 #define  B_PCIE_PHYCTL3_SQDIROVREN               BIT2
 #define  B_PCIE_PHYCTL3_SQDIROVREN_OFFSET        2
 #define  B_PCIE_PHYCTL3_SQDIRCTRL                BIT1
 #define  B_PCIE_PHYCTL3_SQDIRCTRL_OFFSET         1
 #define  B_PCIE_PHYCTL3_TXHSDEEMPCTL             BIT0
 #define  B_PCIE_PHYCTL3_TXHSDEEMPCTL_OFFSET      0

#define  R_PCIE_IOSFSBCS                          0xF7
 #define  B_PCIE_IOSFSBCS_SCPTCGE                 BIT6
 #define  B_PCIE_IOSFSBCS_SCPTCGE_OFFSET          6
 #define  B_PCIE_IOSFSBCS_ISFSIDED                BIT5
 #define  B_PCIE_IOSFSBCS_ISFSIDED_OFFSET         5
 #define  B_PCIE_IOSFSBCS_ISURD                   BIT4
 #define  B_PCIE_IOSFSBCS_ISURD_OFFSET            4
 #define  B_PCIE_IOSFSBCS_SIID                    BIT2
 #define  B_PCIE_IOSFSBCS_SIID_OFFSET             2
 #define  B_PCIE_IOSFSBCS_SIID_MASK               0xC
 #define  B_PCIE_IOSFSBCS_SBIC                    BIT0
 #define  B_PCIE_IOSFSBCS_SBIC_OFFSET             0
 #define  B_PCIE_IOSFSBCS_SBIC_MASK               0x3

#define  R_PCIE_MANID                             0xF8
 #define  B_PCIE_MANID_DPID                       BIT24
 #define  B_PCIE_MANID_DPID_OFFSET                24
 #define  B_PCIE_MANID_DPID_MASK                  0xF000000
 #define  B_PCIE_MANID_SID                        BIT16
 #define  B_PCIE_MANID_SID_OFFSET                 16
 #define  B_PCIE_MANID_SID_MASK                   0xFF0000
 #define  B_PCIE_MANID_MID                        BIT8
 #define  B_PCIE_MANID_MID_OFFSET                 8
 #define  B_PCIE_MANID_MID_MASK                   0xFF00
 #define  B_PCIE_MANID_PD                         BIT0
 #define  B_PCIE_MANID_PD_OFFSET                  0
 #define  B_PCIE_MANID_PD_MASK                    0xFF

#define  R_PCIE_STRPFUSECFG                       0xFC
 #define  B_PCIE_STRPFUSECFG_BLKPLLEN_RSTVALUE    BIT31
 #define  B_PCIE_STRPFUSECFG_BLKPLLEN_RSTVALUE_OFFSET 31
 #define  B_PCIE_STRPFUSECFG_BLKDQDA_RSTVALUE     BIT30
 #define  B_PCIE_STRPFUSECFG_BLKDQDA_RSTVALUE_OFFSET 30
 #define  B_PCIE_STRPFUSECFG_SERM                 BIT29
 #define  B_PCIE_STRPFUSECFG_SERM_OFFSET          29
 #define  B_PCIE_STRPFUSECFG_DRPC                 BIT28
 #define  B_PCIE_STRPFUSECFG_DRPC_OFFSET          28
 #define  B_PCIE_STRPFUSECFG_PXIP                 BIT24
 #define  B_PCIE_STRPFUSECFG_PXIP_OFFSET          24
 #define  B_PCIE_STRPFUSECFG_PXIP_MASK            0xF000000
 #define  V_PCIE_STRPFUSECFG_PXIP_INTD            BIT26
 #define  V_PCIE_STRPFUSECFG_PXIP_INTC            (BIT25 | BIT24)
 #define  V_PCIE_STRPFUSECFG_PXIP_INTB            BIT25
 #define  V_PCIE_STRPFUSECFG_PXIP_INTA            BIT24
 #define  B_PCIE_STRPFUSECFG_MPHYPGD              BIT22
 #define  B_PCIE_STRPFUSECFG_MPHYPGD_OFFSET       22
 #define  B_PCIE_STRPFUSECFG_FTM                  BIT19
 #define  B_PCIE_STRPFUSECFG_FTM_OFFSET           19
 #define  B_PCIE_STRPFUSECFG_FTM_MASK             0x180000
 #define  B_PCIE_STRPFUSECFG_XOSCF                BIT17
 #define  B_PCIE_STRPFUSECFG_XOSCF_OFFSET         17
 #define  B_PCIE_STRPFUSECFG_XOSCF_MASK           0x60000
 #define  B_PCIE_STRPFUSECFG_RPC                  BIT14
 #define  B_PCIE_STRPFUSECFG_RPC_OFFSET           14
 #define  B_PCIE_STRPFUSECFG_RPC_MASK             0x1C000
 #define  B_PCIE_STRPFUSECFG_LR                   BIT13
 #define  B_PCIE_STRPFUSECFG_LR_OFFSET            13
 #define  B_PCIE_STRPFUSECFG_MPHYIOPMDIS          BIT9
 #define  B_PCIE_STRPFUSECFG_MPHYIOPMDIS_OFFSET   9
 #define  B_PCIE_STRPFUSECFG_PLLSHTDWNDIS         BIT8
 #define  B_PCIE_STRPFUSECFG_PLLSHTDWNDIS_OFFSET  8
 #define  B_PCIE_STRPFUSECFG_ASPMDIS              BIT6
 #define  B_PCIE_STRPFUSECFG_ASPMDIS_OFFSET       6
 #define  B_PCIE_STRPFUSECFG_LDCGDIS              BIT5
 #define  B_PCIE_STRPFUSECFG_LDCGDIS_OFFSET       5
 #define  B_PCIE_STRPFUSECFG_LTCGDIS              BIT4
 #define  B_PCIE_STRPFUSECFG_LTCGDIS_OFFSET       4
 #define  B_PCIE_STRPFUSECFG_CDCGDIS              BIT3
 #define  B_PCIE_STRPFUSECFG_CDCGDIS_OFFSET       3
 #define  B_PCIE_STRPFUSECFG_DESKTOPMOB           BIT2
 #define  B_PCIE_STRPFUSECFG_DESKTOPMOB_OFFSET    2

#define  R_PCIE_AECH                              0x100
 #define  B_PCIE_AECH_NCO                         BIT20
 #define  B_PCIE_AECH_NCO_OFFSET                  20
 #define  B_PCIE_AECH_NCO_MASK                    0xFFF00000
 #define  B_PCIE_AECH_CV                          BIT16
 #define  B_PCIE_AECH_CV_OFFSET                   16
 #define  B_PCIE_AECH_CV_MASK                     0xF0000
 #define  V_PCIE_AECH_CV                          0x1
 #define  B_PCIE_AECH_CID                         BIT0
 #define  B_PCIE_AECH_CID_OFFSET                  0
 #define  B_PCIE_AECH_CID_MASK                    0xFFFF

#define  R_PCIE_UES                               0x104
 #define  B_PCIE_UES_PTLPEBS                      BIT26
 #define  B_PCIE_UES_PTLPEBS_OFFSET               26
 #define  B_PCIE_UES_AEBS                         BIT24
 #define  B_PCIE_UES_AEBS_OFFSET                  24
 #define  B_PCIE_UES_AVS                          BIT21
 #define  B_PCIE_UES_AVS_OFFSET                   21
 #define  B_PCIE_UES_URE                          BIT20
 #define  B_PCIE_UES_URE_OFFSET                   20
 #define  B_PCIE_UES_EE                           BIT19
 #define  B_PCIE_UES_EE_OFFSET                    19
 #define  B_PCIE_UES_MT                           BIT18
 #define  B_PCIE_UES_MT_OFFSET                    18
 #define  B_PCIE_UES_RO                           BIT17
 #define  B_PCIE_UES_RO_OFFSET                    17
 #define  B_PCIE_UES_UC                           BIT16
 #define  B_PCIE_UES_UC_OFFSET                    16
 #define  B_PCIE_UES_CA                           BIT15
 #define  B_PCIE_UES_CA_OFFSET                    15
 #define  B_PCIE_UES_CT                           BIT14
 #define  B_PCIE_UES_CT_OFFSET                    14
 #define  B_PCIE_UES_FCPE                         BIT13
 #define  B_PCIE_UES_FCPE_OFFSET                  13
 #define  B_PCIE_UES_PT                           BIT12
 #define  B_PCIE_UES_PT_OFFSET                    12
 #define  B_PCIE_UES_SDE                          BIT5
 #define  B_PCIE_UES_SDE_OFFSET                   5
 #define  B_PCIE_UES_DLPE                         BIT4
 #define  B_PCIE_UES_DLPE_OFFSET                  4
 #define  B_PCIE_UES_TE                           BIT0
 #define  B_PCIE_UES_TE_OFFSET                    0

#define  R_PCIE_UEM                               0x108
 #define  B_PCIE_UEM_PTLPEBM                      BIT26
 #define  B_PCIE_UEM_PTLPEBM_OFFSET               26
 #define  B_PCIE_UEM_AEBM                         BIT24
 #define  B_PCIE_UEM_AEBM_OFFSET                  24
 #define  B_PCIE_UEM_AVM                          BIT21
 #define  B_PCIE_UEM_AVM_OFFSET                   21
 #define  B_PCIE_UEM_URE                          BIT20
 #define  B_PCIE_UEM_URE_OFFSET                   20
 #define  B_PCIE_UEM_EE                           BIT19
 #define  B_PCIE_UEM_EE_OFFSET                    19
 #define  B_PCIE_UEM_MT                           BIT18
 #define  B_PCIE_UEM_MT_OFFSET                    18
 #define  B_PCIE_UEM_RO                           BIT17
 #define  B_PCIE_UEM_RO_OFFSET                    17
 #define  B_PCIE_UEM_UC                           BIT16
 #define  B_PCIE_UEM_UC_OFFSET                    16
 #define  B_PCIE_UEM_CM                           BIT15
 #define  B_PCIE_UEM_CM_OFFSET                    15
 #define  B_PCIE_UEM_CT                           BIT14
 #define  B_PCIE_UEM_CT_OFFSET                    14
 #define  B_PCIE_UEM_FCPE                         BIT13
 #define  B_PCIE_UEM_FCPE_OFFSET                  13
 #define  B_PCIE_UEM_PT                           BIT12
 #define  B_PCIE_UEM_PT_OFFSET                    12
 #define  B_PCIE_UEM_SDE                          BIT5
 #define  B_PCIE_UEM_SDE_OFFSET                   5
 #define  B_PCIE_UEM_DLPE                         BIT4
 #define  B_PCIE_UEM_DLPE_OFFSET                  4
 #define  B_PCIE_UEM_TE                           BIT0
 #define  B_PCIE_UEM_TE_OFFSET                    0

#define  R_PCIE_UEV                               0x10C
 #define  B_PCIE_UEV_PTLPEBS                      BIT26
 #define  B_PCIE_UEV_PTLPEBS_OFFSET               26
 #define  B_PCIE_UEV_AEBS                         BIT24
 #define  B_PCIE_UEV_AEBS_OFFSET                  24
 #define  B_PCIE_UEV_AVS                          BIT21
 #define  B_PCIE_UEV_AVS_OFFSET                   21
 #define  B_PCIE_UEV_URE                          BIT20
 #define  B_PCIE_UEV_URE_OFFSET                   20
 #define  B_PCIE_UEV_EE                           BIT19
 #define  B_PCIE_UEV_EE_OFFSET                    19
 #define  B_PCIE_UEV_MT                           BIT18
 #define  B_PCIE_UEV_MT_OFFSET                    18
 #define  B_PCIE_UEV_RO                           BIT17
 #define  B_PCIE_UEV_RO_OFFSET                    17
 #define  B_PCIE_UEV_UC                           BIT16
 #define  B_PCIE_UEV_UC_OFFSET                    16
 #define  B_PCIE_UEV_CA                           BIT15
 #define  B_PCIE_UEV_CA_OFFSET                    15
 #define  B_PCIE_UEV_CT                           BIT14
 #define  B_PCIE_UEV_CT_OFFSET                    14
 #define  B_PCIE_UEV_FCPE                         BIT13
 #define  B_PCIE_UEV_FCPE_OFFSET                  13
 #define  B_PCIE_UEV_PT                           BIT12
 #define  B_PCIE_UEV_PT_OFFSET                    12
 #define  B_PCIE_UEV_SDE                          BIT5
 #define  B_PCIE_UEV_SDE_OFFSET                   5
 #define  B_PCIE_UEV_DLPE                         BIT4
 #define  B_PCIE_UEV_DLPE_OFFSET                  4
 #define  B_PCIE_UEV_TE                           BIT0
 #define  B_PCIE_UEV_TE_OFFSET                    0

#define  R_PCIE_CES                               0x110
 #define  B_PCIE_CES_ANFES                        BIT13
 #define  B_PCIE_CES_ANFES_OFFSET                 13
 #define  B_PCIE_CES_RTT                          BIT12
 #define  B_PCIE_CES_RTT_OFFSET                   12
 #define  B_PCIE_CES_RNR                          BIT8
 #define  B_PCIE_CES_RNR_OFFSET                   8
 #define  B_PCIE_CES_BD                           BIT7
 #define  B_PCIE_CES_BD_OFFSET                    7
 #define  B_PCIE_CES_BT                           BIT6
 #define  B_PCIE_CES_BT_OFFSET                    6
 #define  B_PCIE_CES_RE                           BIT0
 #define  B_PCIE_CES_RE_OFFSET                    0

#define  R_PCIE_CEM                               0x114
 #define  B_PCIE_CEM_ANFEM                        BIT13
 #define  B_PCIE_CEM_ANFEM_OFFSET                 13
 #define  B_PCIE_CEM_RTT                          BIT12
 #define  B_PCIE_CEM_RTT_OFFSET                   12
 #define  B_PCIE_CEM_RNR                          BIT8
 #define  B_PCIE_CEM_RNR_OFFSET                   8
 #define  B_PCIE_CEM_BD                           BIT7
 #define  B_PCIE_CEM_BD_OFFSET                    7
 #define  B_PCIE_CEM_BT                           BIT6
 #define  B_PCIE_CEM_BT_OFFSET                    6
 #define  B_PCIE_CEM_RE                           BIT0
 #define  B_PCIE_CEM_RE_OFFSET                    0

#define  R_PCIE_AECC                              0x118
 #define  B_PCIE_AECC_CTPHLC                      BIT12
 #define  B_PCIE_AECC_CTPHLC_OFFSET               12
 #define  B_PCIE_AECC_ECE                         BIT8
 #define  B_PCIE_AECC_ECE_OFFSET                  8
 #define  B_PCIE_AECC_ECC                         BIT7
 #define  B_PCIE_AECC_ECC_OFFSET                  7
 #define  B_PCIE_AECC_EGE                         BIT6
 #define  B_PCIE_AECC_EGE_OFFSET                  6
 #define  B_PCIE_AECC_EGC                         BIT5
 #define  B_PCIE_AECC_EGC_OFFSET                  5
 #define  B_PCIE_AECC_FEP                         BIT0
 #define  B_PCIE_AECC_FEP_OFFSET                  0
 #define  B_PCIE_AECC_FEP_MASK                    0x1F

#define  R_PCIE_HL_DW1                            0x11C
 #define  B_PCIE_HL_DW1_DW1                       BIT0
 #define  B_PCIE_HL_DW1_DW1_OFFSET                0
 #define  B_PCIE_HL_DW1_DW1_MASK                  0xFFFFFFFF

#define  R_PCIE_HL_DW2                            0x120
 #define  B_PCIE_HL_DW2_DW2                       BIT0
 #define  B_PCIE_HL_DW2_DW2_OFFSET                0
 #define  B_PCIE_HL_DW2_DW2_MASK                  0xFFFFFFFF

#define  R_PCIE_HL_DW3                            0x124
 #define  B_PCIE_HL_DW3_DW3                       BIT0
 #define  B_PCIE_HL_DW3_DW3_OFFSET                0
 #define  B_PCIE_HL_DW3_DW3_MASK                  0xFFFFFFFF

#define  R_PCIE_HL_DW4                            0x128
 #define  B_PCIE_HL_DW4_DW4                       BIT0
 #define  B_PCIE_HL_DW4_DW4_OFFSET                0
 #define  B_PCIE_HL_DW4_DW4_MASK                  0xFFFFFFFF

#define  R_PCIE_REC                               0x12C
 #define  B_PCIE_REC_FERE                         BIT2
 #define  B_PCIE_REC_FERE_OFFSET                  2
 #define  B_PCIE_REC_NERE                         BIT1
 #define  B_PCIE_REC_NERE_OFFSET                  1
 #define  B_PCIE_REC_CERE                         BIT0
 #define  B_PCIE_REC_CERE_OFFSET                  0

#define  R_PCIE_RES                               0x130
 #define  B_PCIE_RES_AEMN                         BIT27
 #define  B_PCIE_RES_AEMN_OFFSET                  27
 #define  B_PCIE_RES_AEMN_MASK                    0xF8000000
 #define  B_PCIE_RES_FEMR                         BIT6
 #define  B_PCIE_RES_FEMR_OFFSET                  6
 #define  B_PCIE_RES_NFEMR                        BIT5
 #define  B_PCIE_RES_NFEMR_OFFSET                 5
 #define  B_PCIE_RES_FUF                          BIT4
 #define  B_PCIE_RES_FUF_OFFSET                   4
 #define  B_PCIE_RES_MENR                         BIT3
 #define  B_PCIE_RES_MENR_OFFSET                  3
 #define  B_PCIE_RES_ENR                          BIT2
 #define  B_PCIE_RES_ENR_OFFSET                   2
 #define  B_PCIE_RES_MCR                          BIT1
 #define  B_PCIE_RES_MCR_OFFSET                   1
 #define  B_PCIE_RES_CR                           BIT0
 #define  B_PCIE_RES_CR_OFFSET                    0

#define  R_PCIE_ESID                              0x134
 #define  B_PCIE_ESID_EFNFSID                     BIT16
 #define  B_PCIE_ESID_EFNFSID_OFFSET              16
 #define  B_PCIE_ESID_EFNFSID_MASK                0xFFFF0000
 #define  B_PCIE_ESID_ECSID                       BIT0
 #define  B_PCIE_ESID_ECSID_OFFSET                0
 #define  B_PCIE_ESID_ECSID_MASK                  0xFFFF

#define  R_PCIE_PTMECH                            0x150
 #define  B_PCIE_PTMECH_NCO                       BIT20
 #define  B_PCIE_PTMECH_NCO_OFFSET                20
 #define  B_PCIE_PTMECH_NCO_MASK                  0xFFF00000
 #define  B_PCIE_PTMECH_CV                        BIT16
 #define  B_PCIE_PTMECH_CV_OFFSET                 16
 #define  B_PCIE_PTMECH_CV_MASK                   0xF0000
 #define  V_PCIE_PTMECH_CV                        0x1
 #define  B_PCIE_PTMECH_CID                       BIT0
 #define  B_PCIE_PTMECH_CID_OFFSET                0
 #define  B_PCIE_PTMECH_CID_MASK                  0xFFFF

#define  R_PCIE_PTMCAPR                           0x154
 #define  B_PCIE_PTMCAPR_LCG                      BIT8
 #define  B_PCIE_PTMCAPR_LCG_OFFSET               8
 #define  B_PCIE_PTMCAPR_LCG_MASK                 0xFF00
 #define  B_PCIE_PTMCAPR_PTMRC                    BIT2
 #define  B_PCIE_PTMCAPR_PTMRC_OFFSET             2
 #define  B_PCIE_PTMCAPR_PTMRSPC                  BIT1
 #define  B_PCIE_PTMCAPR_PTMRSPC_OFFSET           1
 #define  B_PCIE_PTMCAPR_PTMREQC                  BIT0
 #define  B_PCIE_PTMCAPR_PTMREQC_OFFSET           0

#define  R_PCIE_PTMCTLR                           0x158
 #define  B_PCIE_PTMCTLR_EG                       BIT8
 #define  B_PCIE_PTMCTLR_EG_OFFSET                8
 #define  B_PCIE_PTMCTLR_EG_MASK                  0xFF00
 #define  B_PCIE_PTMCTLR_RS                       BIT1
 #define  B_PCIE_PTMCTLR_RS_OFFSET                1
 #define  B_PCIE_PTMCTLR_PTME                     BIT0
 #define  B_PCIE_PTMCTLR_PTME_OFFSET              0

#define  R_PCIE_L1SECH                            0x200 ///< L1 Sub-States Extended Capability Header
 #define  V_PCIE_L1S_CV                           0x1

#define  R_PCIE_L1SCAP                            0x204 ///< L1 Sub-States Capability Register
 #define  B_PCIE_L1SCAP_PTV                       BIT19
 #define  B_PCIE_L1SCAP_PTV_OFFSET                19
 #define  B_PCIE_L1SCAP_PTV_MASK                  0xF80000
 #define  V_PCIE_L1SCAP_PTV                       0x4
 #define  B_PCIE_L1SCAP_PTPOS                     BIT16
 #define  B_PCIE_L1SCAP_PTPOS_OFFSET              16
 #define  B_PCIE_L1SCAP_PTPOS_MASK                0x30000
 #define  V_PCIE_L1SCAP_PTPOS                     0x2
 #define  B_PCIE_L1SCAP_L1SSES                    BIT5
 #define  B_PCIE_L1SCAP_L1PSS                     BIT4
 #define  B_PCIE_L1SCAP_AL11S                     BIT3
 #define  B_PCIE_L1SCAP_AL12S                     BIT2
 #define  B_PCIE_L1SCAP_PPL11S                    BIT1
 #define  B_PCIE_L1SCAP_PPL12S                    BIT0

#define  R_PCIE_L1SCTL1                           0x208 ///< L1 Sub-States Control 1
 #define  B_PCIE_L1SCTL1_L1SSEIE                  BIT4

#define  R_PCIE_ACSECH                            0x220
 #define  B_PCIE_ACSECH_NCO                       BIT20
 #define  B_PCIE_ACSECH_NCO_OFFSET                20
 #define  B_PCIE_ACSECH_NCO_MASK                  0xFFF00000
 #define  B_PCIE_ACSECH_CV                        BIT16
 #define  B_PCIE_ACSECH_CV_OFFSET                 16
 #define  B_PCIE_ACSECH_CV_MASK                   0xF0000
 #define  V_PCIE_ACSECH_CV                        0x1
 #define  B_PCIE_ACSECH_CID                       BIT0
 #define  B_PCIE_ACSECH_CID_OFFSET                0
 #define  B_PCIE_ACSECH_CID_MASK                  0xFFFF

#define  R_PCIE_ACSCAPR                           0x224
 #define  B_PCIE_ACSCAPR_T                        BIT6
 #define  B_PCIE_ACSCAPR_T_OFFSET                 6
 #define  B_PCIE_ACSCAPR_E                        BIT5
 #define  B_PCIE_ACSCAPR_E_OFFSET                 5
 #define  B_PCIE_ACSCAPR_U                        BIT4
 #define  B_PCIE_ACSCAPR_U_OFFSET                 4
 #define  B_PCIE_ACSCAPR_C                        BIT3
 #define  B_PCIE_ACSCAPR_C_OFFSET                 3
 #define  B_PCIE_ACSCAPR_R                        BIT2
 #define  B_PCIE_ACSCAPR_R_OFFSET                 2
 #define  B_PCIE_ACSCAPR_B                        BIT1
 #define  B_PCIE_ACSCAPR_B_OFFSET                 1
 #define  B_PCIE_ACSCAPR_V                        BIT0
 #define  B_PCIE_ACSCAPR_V_OFFSET                 0

#define  R_PCIE_ACSCTLR                           0x226
 #define  B_PCIE_ACSCTLR_TE                       BIT6
 #define  B_PCIE_ACSCTLR_TE_OFFSET                6
 #define  B_PCIE_ACSCTLR_EE                       BIT5
 #define  B_PCIE_ACSCTLR_EE_OFFSET                5
 #define  B_PCIE_ACSCTLR_UE                       BIT4
 #define  B_PCIE_ACSCTLR_UE_OFFSET                4
 #define  B_PCIE_ACSCTLR_CE                       BIT3
 #define  B_PCIE_ACSCTLR_CE_OFFSET                3
 #define  B_PCIE_ACSCTLR_RE                       BIT2
 #define  B_PCIE_ACSCTLR_RE_OFFSET                2
 #define  B_PCIE_ACSCTLR_BE                       BIT1
 #define  B_PCIE_ACSCTLR_BE_OFFSET                1
 #define  B_PCIE_ACSCTLR_VE                       BIT0
 #define  B_PCIE_ACSCTLR_VE_OFFSET                0

#define R_PCIE_VCECH                              0x280

#define  R_PCIE_PCIERTP1                          0x300
 #define  B_PCIE_PCIERTP1_G2X1                    BIT20
 #define  B_PCIE_PCIERTP1_G2X1_OFFSET             20
 #define  B_PCIE_PCIERTP1_G2X1_MASK               0xF00000
 #define  B_PCIE_PCIERTP1_G2X2                    BIT16
 #define  B_PCIE_PCIERTP1_G2X2_OFFSET             16
 #define  B_PCIE_PCIERTP1_G2X2_MASK               0xF0000
 #define  B_PCIE_PCIERTP1_G2X4                    BIT12
 #define  B_PCIE_PCIERTP1_G2X4_OFFSET             12
 #define  B_PCIE_PCIERTP1_G2X4_MASK               0xF000
 #define  B_PCIE_PCIERTP1_G1X1                    BIT8
 #define  B_PCIE_PCIERTP1_G1X1_OFFSET             8
 #define  B_PCIE_PCIERTP1_G1X1_MASK               0xF00
 #define  B_PCIE_PCIERTP1_G1X2                    BIT4
 #define  B_PCIE_PCIERTP1_G1X2_OFFSET             4
 #define  B_PCIE_PCIERTP1_G1X2_MASK               0xF0
 #define  B_PCIE_PCIERTP1_G1X4                    BIT0
 #define  B_PCIE_PCIERTP1_G1X4_OFFSET             0
 #define  B_PCIE_PCIERTP1_G1X4_MASK               0xF

#define  R_PCIE_PCIERTP2                          0x304
 #define  B_PCIE_PCIERTP2_G3X1                    BIT8
 #define  B_PCIE_PCIERTP2_G3X1_OFFSET             8
 #define  B_PCIE_PCIERTP2_G3X1_MASK               0xF00
 #define  B_PCIE_PCIERTP2_G3X2                    BIT4
 #define  B_PCIE_PCIERTP2_G3X2_OFFSET             4
 #define  B_PCIE_PCIERTP2_G3X2_MASK               0xF0
 #define  B_PCIE_PCIERTP2_G3X4                    BIT0
 #define  B_PCIE_PCIERTP2_G3X4_OFFSET             0
 #define  B_PCIE_PCIERTP2_G3X4_MASK               0xF

#define  R_PCIE_G4L0SCTL                          0x310
 #define  B_PCIE_G4L0SCTL_G4ASL0SPL               BIT24
 #define  B_PCIE_G4L0SCTL_G4ASL0SPL_OFFSET        24
 #define  B_PCIE_G4L0SCTL_G4ASL0SPL_MASK          0xFF000000
 #define  V_PCIE_G4L0SCTL_G4ASL0SPL               0x28
 #define  B_PCIE_G4L0SCTL_G4L0SIC                 BIT22
 #define  B_PCIE_G4L0SCTL_G4L0SICL_OFFSET         22
 #define  B_PCIE_G4L0SCTL_G4L0SICL_MASK           0x00C00000
 #define  B_PCIE_G4L0SCTL_G4UCNFTS                BIT8
 #define  B_PCIE_G4L0SCTL_G4UCNFTS_OFFSET         8
 #define  B_PCIE_G4L0SCTL_G4UCNFTS_MASK           0x0000FF00
 #define  V_PCIE_G4L0SCTL_G4UCNFTS                0x80
 #define  B_PCIE_G4L0SCTL_G4CCNFTS                BIT0
 #define  B_PCIE_G4L0SCTL_G4CCNFTS_OFFSET         0
 #define  B_PCIE_G4L0SCTL_G4CCNFTS_MASK           0x000000FF
 #define  V_PCIE_G4L0SCTL_G4CCNFTS                0x5B

#define  R_PCIE_PCIENFTS                          0x314
 #define  B_PCIE_PCIENFTS_G2UCNFTS                BIT24
 #define  B_PCIE_PCIENFTS_G2UCNFTS_OFFSET         24
 #define  B_PCIE_PCIENFTS_G2UCNFTS_MASK           0xFF000000
 #define  B_PCIE_PCIENFTS_G2CCNFTS                BIT16
 #define  B_PCIE_PCIENFTS_G2CCNFTS_OFFSET         16
 #define  B_PCIE_PCIENFTS_G2CCNFTS_MASK           0xFF0000
 #define  B_PCIE_PCIENFTS_G1UCNFTS                BIT8
 #define  B_PCIE_PCIENFTS_G1UCNFTS_OFFSET         8
 #define  B_PCIE_PCIENFTS_G1UCNFTS_MASK           0xFF00
 #define  B_PCIE_PCIENFTS_G1CCNFTS                BIT0
 #define  B_PCIE_PCIENFTS_G1CCNFTS_OFFSET         0
 #define  B_PCIE_PCIENFTS_G1CCNFTS_MASK           0xFF

#define  R_PCIE_PCIEL0SC                          0x318
 #define  B_PCIE_PCIEL0SC_G2ASL0SPL               BIT24
 #define  B_PCIE_PCIEL0SC_G2ASL0SPL_OFFSET        24
 #define  B_PCIE_PCIEL0SC_G2ASL0SPL_MASK          0xFF000000
 #define  V_PCIE_PCIEL0SC_G2ASL0SPL               0x14
 #define  B_PCIE_PCIEL0SC_G1ASL0SPL               BIT16
 #define  B_PCIE_PCIEL0SC_G1ASL0SPL_OFFSET        16
 #define  B_PCIE_PCIEL0SC_G1ASL0SPL_MASK          0xFF0000
 #define  V_PCIE_PCIEL0SC_G1ASL0SPL               0x14
 #define  B_PCIE_PCIEL0SC_ANFTSO                  BIT8
 #define  B_PCIE_PCIEL0SC_ANFTSO_OFFSET           8
 #define  B_PCIE_PCIEL0SC_ANFTSO_MASK             0xFF00
 #define  B_PCIE_PCIEL0SC_ANFTSEN                 BIT7
 #define  B_PCIE_PCIEL0SC_ANFTSEN_OFFSET          7
 #define  B_PCIE_PCIEL0SC_TXL0SRXENTRY            BIT6
 #define  B_PCIE_PCIEL0SC_TXL0SRXENTRY_OFFSET     6
 #define  B_PCIE_PCIEL0SC_TXL0SRXEXIT             BIT4
 #define  B_PCIE_PCIEL0SC_TXL0SRXEXIT_OFFSET      4
 #define  B_PCIE_PCIEL0SC_TXL0SRXEXIT_MASK        0x30
 #define  B_PCIE_PCIEL0SC_G2L0SIC                 BIT2
 #define  B_PCIE_PCIEL0SC_G2L0SIC_OFFSET          2
 #define  B_PCIE_PCIEL0SC_G2L0SIC_MASK            0xC
 #define  B_PCIE_PCIEL0SC_G1L0SIC                 BIT0
 #define  B_PCIE_PCIEL0SC_G1L0SIC_OFFSET          0
 #define  B_PCIE_PCIEL0SC_G1L0SIC_MASK            0x3

#define  R_PCIE_PCIEATL                           0x31C
 #define  B_PCIE_PCIEATL_G3X1                     BIT24
 #define  B_PCIE_PCIEATL_G3X1_OFFSET              24
 #define  B_PCIE_PCIEATL_G3X1_MASK                0x7000000
 #define  B_PCIE_PCIEATL_G3X2                     BIT21
 #define  B_PCIE_PCIEATL_G3X2_OFFSET              21
 #define  B_PCIE_PCIEATL_G3X2_MASK                0xE00000
 #define  B_PCIE_PCIEATL_G3X4                     BIT18
 #define  B_PCIE_PCIEATL_G3X4_OFFSET              18
 #define  B_PCIE_PCIEATL_G3X4_MASK                0x1C0000
 #define  B_PCIE_PCIEATL_G2X1                     BIT15
 #define  B_PCIE_PCIEATL_G2X1_OFFSET              15
 #define  B_PCIE_PCIEATL_G2X1_MASK                0x38000
 #define  B_PCIE_PCIEATL_G2X2                     BIT12
 #define  B_PCIE_PCIEATL_G2X2_OFFSET              12
 #define  B_PCIE_PCIEATL_G2X2_MASK                0x7000
 #define  B_PCIE_PCIEATL_G2X4                     BIT9
 #define  B_PCIE_PCIEATL_G2X4_OFFSET              9
 #define  B_PCIE_PCIEATL_G2X4_MASK                0xE00
 #define  B_PCIE_PCIEATL_G1X1                     BIT6
 #define  B_PCIE_PCIEATL_G1X1_OFFSET              6
 #define  B_PCIE_PCIEATL_G1X1_MASK                0x1C0
 #define  B_PCIE_PCIEATL_G1X2                     BIT3
 #define  B_PCIE_PCIEATL_G1X2_OFFSET              3
 #define  B_PCIE_PCIEATL_G1X2_MASK                0x38
 #define  B_PCIE_PCIEATL_G1X4                     BIT0
 #define  B_PCIE_PCIEATL_G1X4_OFFSET              0
 #define  B_PCIE_PCIEATL_G1X4_MASK                0x7

#define  R_PCIE_PCIECFG2                          0x320
 #define  B_PCIE_PCIECFG2_G3L0SEDP                BIT31
 #define  B_PCIE_PCIECFG2_G3L0SEDP_OFFSET         31
 #define  B_PCIE_PCIECFG2_LBWSSTE                 BIT30
 #define  B_PCIE_PCIECFG2_LBWSSTE_OFFSET          30
 #define  B_PCIE_PCIECFG2_RRCP                    BIT29
 #define  B_PCIE_PCIECFG2_RRCP_OFFSET             29
 #define  B_PCIE_PCIECFG2_LSIEID                  BIT28
 #define  B_PCIE_PCIECFG2_LSIEID_OFFSET           28
 #define  B_PCIE_PCIECFG2_RLLG3R                  BIT27
 #define  B_PCIE_PCIECFG2_RLLG3R_OFFSET           27
 #define  B_PCIE_PCIECFG2_RPAGC                   BIT25
 #define  B_PCIE_PCIECFG2_RPAGC_OFFSET            25
 #define  B_PCIE_PCIECFG2_CROAOV                  BIT24
 #define  B_PCIE_PCIECFG2_CROAOV_OFFSET           24
 #define  B_PCIE_PCIECFG2_CROAOE                  BIT23
 #define  B_PCIE_PCIECFG2_CROAOE_OFFSET           23
 #define  B_PCIE_PCIECFG2_CRSREN                  BIT22
 #define  B_PCIE_PCIECFG2_CRSREN_OFFSET           22
 #define  B_PCIE_PCIECFG2_PMET                    BIT20
 #define  B_PCIE_PCIECFG2_PMET_OFFSET             20
 #define  B_PCIE_PCIECFG2_PMET_MASK               0x300000
 #define  B_PCIE_PCIECFG2_G12SKPOSL               BIT9
 #define  B_PCIE_PCIECFG2_G12SKPOSL_OFFSET        9
 #define  B_PCIE_PCIECFG2_G12SKPOSL_MASK          0xFFE00
 #define  B_PCIE_PCIECFG2_LATGC                   BIT6
 #define  B_PCIE_PCIECFG2_LATGC_OFFSET            6
 #define  B_PCIE_PCIECFG2_LATGC_MASK              0x1C0
 #define  B_PCIE_PCIECFG2_LAFGC                   BIT3
 #define  B_PCIE_PCIECFG2_LAFGC_OFFSET            3
 #define  B_PCIE_PCIECFG2_LAFGC_MASK              0x38
 #define  B_PCIE_PCIECFG2_LAANGC                  BIT0
 #define  B_PCIE_PCIECFG2_LAANGC_OFFSET           0
 #define  B_PCIE_PCIECFG2_LAANGC_MASK             0x7
 #define  V_PCIE_PCIECFG2_PMET                    1

#define  R_PCIE_PCIEDBG                           0x324
 #define  B_PCIE_PCIEDBG_TXNFTSADD                BIT29
 #define  B_PCIE_PCIEDBG_TXNFTSADD_OFFSET         29
 #define  B_PCIE_PCIEDBG_TXNFTSADD_MASK           0xE0000000
 #define  B_PCIE_PCIEDBG_REUTLPBKME               BIT28
 #define  B_PCIE_PCIEDBG_REUTLPBKME_OFFSET        28
 #define  B_PCIE_PCIEDBG_USSP                     BIT26
 #define  B_PCIE_PCIEDBG_USSP_OFFSET              26
 #define  B_PCIE_PCIEDBG_USSP_MASK                0xC000000
 #define  V_PCIE_PCIEDBG_USSP_32NS                2
 #define  B_PCIE_PCIEDBG_LGCLKSQEXITDBTIMERS      BIT24
 #define  B_PCIE_PCIEDBG_LGCLKSQEXITDBTIMERS_OFFSET 24
 #define  B_PCIE_PCIEDBG_LGCLKSQEXITDBTIMERS_MASK 0x3000000
 #define  B_PCIE_PCIEDBG_TALS                     BIT16
 #define  B_PCIE_PCIEDBG_TALS_OFFSET              16
 #define  B_PCIE_PCIEDBG_TALS_MASK                0xFF0000
 #define  B_PCIE_PCIEDBG_REUTFLPBKME              BIT15
 #define  B_PCIE_PCIEDBG_REUTFLPBKME_OFFSET       15
 #define  B_PCIE_PCIEDBG_CTONFAE                  BIT14
 #define  B_PCIE_PCIEDBG_CTONFAE_OFFSET           14
 #define  B_PCIE_PCIEDBG_LDSWQRP                  BIT13
 #define  B_PCIE_PCIEDBG_LDSWQRP_OFFSET           13
 #define  B_PCIE_PCIEDBG_G3CSOS                   BIT12
 #define  B_PCIE_PCIEDBG_G3CSOS_OFFSET            12
 #define  B_PCIE_PCIEDBG_NEDLBE                   BIT11
 #define  B_PCIE_PCIEDBG_NEDLBE_OFFSET            11
 #define  B_PCIE_PCIEDBG_IRFELB                   BIT10
 #define  B_PCIE_PCIEDBG_IRFELB_OFFSET            10
 #define  B_PCIE_PCIEDBG_DSB                      BIT9
 #define  B_PCIE_PCIEDBG_DSB_OFFSET               9
 #define  B_PCIE_PCIEDBG_REPID                    BIT8
 #define  B_PCIE_PCIEDBG_REPID_OFFSET             8
 #define  B_PCIE_PCIEDBG_SQOL0                    BIT7
 #define  B_PCIE_PCIEDBG_SQOL0_OFFSET             7
 #define  B_PCIE_PCIEDBG_CMPLRX                   BIT6
 #define  B_PCIE_PCIEDBG_CMPLRX_OFFSET            6
 #define  B_PCIE_PCIEDBG_SPCE                     BIT5
 #define  B_PCIE_PCIEDBG_SPCE_OFFSET              5
 #define  B_PCIE_PCIEDBG_DMIL1EDM                 BIT3
 #define  B_PCIE_PCIEDBG_DMIL1EDM_OFFSET          3
 #define  B_PCIE_PCIEDBG_SCMBB                    BIT2
 #define  B_PCIE_PCIEDBG_SCMBB_OFFSET             2
 #define  B_PCIE_PCIEDBG_CRCD                     BIT1
 #define  B_PCIE_PCIEDBG_CRCD_OFFSET              1
 #define  B_PCIE_PCIEDBG_SNCD                     BIT0
 #define  B_PCIE_PCIEDBG_SNCD_OFFSET              0

#define  R_PCIE_PCIESTS1                          0x328
 #define  B_PCIE_PCIESTS1_LTSMSTATE               BIT24
 #define  B_PCIE_PCIESTS1_LTSMSTATE_OFFSET        24
 #define  B_PCIE_PCIESTS1_LTSMSTATE_MASK          0xFF000000
 #define  B_PCIE_PCIESTS1_LNKSTAT                 BIT19
 #define  B_PCIE_PCIESTS1_LNKSTAT_OFFSET          19
 #define  B_PCIE_PCIESTS1_LNKSTAT_MASK            0x780000
 #define  B_PCIE_PCIESTS1_REPLAYNUM               BIT17
 #define  B_PCIE_PCIESTS1_REPLAYNUM_OFFSET        17
 #define  B_PCIE_PCIESTS1_REPLAYNUM_MASK          0x60000
 #define  B_PCIE_PCIESTS1_DLLRETRY                BIT16
 #define  B_PCIE_PCIESTS1_DLLRETRY_OFFSET         16
 #define  B_PCIE_PCIESTS1_NXTTXSEQNUM             BIT0
 #define  B_PCIE_PCIESTS1_NXTTXSEQNUM_OFFSET      0
 #define  B_PCIE_PCIESTS1_NXTTXSEQNUM_MASK        0xFFF
 #define  V_PCIE_PCIESTS1_LTSMSTATE_DETRDY        0x01

#define  R_PCIE_PCIESTS2                          0x32C
 #define  B_PCIE_PCIESTS2_P4PNCCWSSCMES           BIT31
 #define  B_PCIE_PCIESTS2_P4PNCCWSSCMES_OFFSET    31
 #define  B_PCIE_PCIESTS2_P3PNCCWSSCMES           BIT30
 #define  B_PCIE_PCIESTS2_P3PNCCWSSCMES_OFFSET    30
 #define  B_PCIE_PCIESTS2_P2PNCCWSSCMES           BIT29
 #define  B_PCIE_PCIESTS2_P2PNCCWSSCMES_OFFSET    29
 #define  B_PCIE_PCIESTS2_P1PNCCWSSCMES           BIT28
 #define  B_PCIE_PCIESTS2_P1PNCCWSSCMES_OFFSET    28
 #define  B_PCIE_PCIESTS2_NXTRCVSEQ               BIT16
 #define  B_PCIE_PCIESTS2_NXTRCVSEQ_OFFSET        16
 #define  B_PCIE_PCIESTS2_NXTRCVSEQ_MASK          0xFFF0000
 #define  B_PCIE_PCIESTS2_LASTACKSEQNUM           BIT0
 #define  B_PCIE_PCIESTS2_LASTACKSEQNUM_OFFSET    0
 #define  B_PCIE_PCIESTS2_LASTACKSEQNUM_MASK      0xFFF

#define  R_PCIE_PCIECMMPC                         0x330
 #define  B_PCIE_PCIECMMPC_G3ICMMSB               BIT31
 #define  B_PCIE_PCIECMMPC_G3ICMMSB_OFFSET        31
 #define  B_PCIE_PCIECMMPC_SYM3SEL                BIT29
 #define  B_PCIE_PCIECMMPC_SYM3SEL_OFFSET         29
 #define  B_PCIE_PCIECMMPC_SYM2SEL                BIT28
 #define  B_PCIE_PCIECMMPC_SYM2SEL_OFFSET         28
 #define  B_PCIE_PCIECMMPC_SYM1SEL                BIT27
 #define  B_PCIE_PCIECMMPC_SYM1SEL_OFFSET         27
 #define  B_PCIE_PCIECMMPC_SYM0SEL                BIT26
 #define  B_PCIE_PCIECMMPC_SYM0SEL_OFFSET         26
 #define  B_PCIE_PCIECMMPC_CMMSH                  BIT24
 #define  B_PCIE_PCIECMMPC_CMMSH_OFFSET           24
 #define  B_PCIE_PCIECMMPC_CMMSH_MASK             0x3000000
 #define  B_PCIE_PCIECMMPC_ERRLANENUM             BIT20
 #define  B_PCIE_PCIECMMPC_ERRLANENUM_OFFSET      20
 #define  B_PCIE_PCIECMMPC_ERRLANENUM_MASK        0xF00000
 #define  B_PCIE_PCIECMMPC_INVERT                 BIT15
 #define  B_PCIE_PCIECMMPC_INVERT_OFFSET          15
 #define  B_PCIE_PCIECMMPC_INVERT_MASK            0x78000
 #define  B_PCIE_PCIECMMPC_SYMERRNUMINV           BIT12
 #define  B_PCIE_PCIECMMPC_SYMERRNUMINV_OFFSET    12
 #define  B_PCIE_PCIECMMPC_SYMERRNUMINV_MASK      0x7000
 #define  B_PCIE_PCIECMMPC_SYMERRNUM              BIT10
 #define  B_PCIE_PCIECMMPC_SYMERRNUM_OFFSET       10
 #define  B_PCIE_PCIECMMPC_SYMERRNUM_MASK         0xC00
 #define  B_PCIE_PCIECMMPC_ERRDET                 BIT9
 #define  B_PCIE_PCIECMMPC_ERRDET_OFFSET          9
 #define  B_PCIE_PCIECMMPC_SLNINVCMM              BIT5
 #define  B_PCIE_PCIECMMPC_SLNINVCMM_OFFSET       5
 #define  B_PCIE_PCIECMMPC_SLNINVCMM_MASK         0xE0
 #define  B_PCIE_PCIECMMPC_AUTOINVERT             BIT4
 #define  B_PCIE_PCIECMMPC_AUTOINVERT_OFFSET      4
 #define  B_PCIE_PCIECMMPC_STAT                   BIT3
 #define  B_PCIE_PCIECMMPC_STAT_OFFSET            3
 #define  B_PCIE_PCIECMMPC_INVEN                  BIT2
 #define  B_PCIE_PCIECMMPC_INVEN_OFFSET           2
 #define  B_PCIE_PCIECMMPC_START                  BIT0
 #define  B_PCIE_PCIECMMPC_START_OFFSET           0

#define  R_PCIE_PCIECMMSB                         0x334
 #define  B_PCIE_PCIECMMSB_DATA3                  BIT24
 #define  B_PCIE_PCIECMMSB_DATA3_OFFSET           24
 #define  B_PCIE_PCIECMMSB_DATA3_MASK             0xFF000000
 #define  B_PCIE_PCIECMMSB_DATA2                  BIT16
 #define  B_PCIE_PCIECMMSB_DATA2_OFFSET           16
 #define  B_PCIE_PCIECMMSB_DATA2_MASK             0xFF0000
 #define  B_PCIE_PCIECMMSB_DATA1                  BIT8
 #define  B_PCIE_PCIECMMSB_DATA1_OFFSET           8
 #define  B_PCIE_PCIECMMSB_DATA1_MASK             0xFF00
 #define  B_PCIE_PCIECMMSB_DATA0                  BIT0
 #define  B_PCIE_PCIECMMSB_DATA0_OFFSET           0
 #define  B_PCIE_PCIECMMSB_DATA0_MASK             0xFF

#define  R_PCIE_PCIEALC                           0x338
 #define  B_PCIE_PCIEALC_CSSAIF                   BIT31
 #define  B_PCIE_PCIEALC_CSSAIF_OFFSET            31
 #define  B_PCIE_PCIEALC_DPCHSERM                 BIT30
 #define  B_PCIE_PCIEALC_DPCHSERM_OFFSET          30
 #define  B_PCIE_PCIEALC_ITLRCLD                  BIT29
 #define  B_PCIE_PCIEALC_ITLRCLD_OFFSET           29
 #define  B_PCIE_PCIEALC_ILLRCLD                  BIT28
 #define  B_PCIE_PCIEALC_ILLRCLD_OFFSET           28
 #define  B_PCIE_PCIEALC_BLKPAPC                  BIT27
 #define  B_PCIE_PCIEALC_BLKPAPC_OFFSET           27
 #define  B_PCIE_PCIEALC_BLKDQDA                  BIT26
 #define  B_PCIE_PCIEALC_BLKDQDA_OFFSET           26
 #define  B_PCIE_PCIEALC_BLKDQDASD                BIT25
 #define  B_PCIE_PCIEALC_BLKDQDASD_OFFSET         25
 #define  B_PCIE_PCIEALC_SSRLD                    BIT24
 #define  B_PCIE_PCIEALC_SSRLD_OFFSET             24
 #define  B_PCIE_PCIEALC_SSRRS                    BIT23
 #define  B_PCIE_PCIEALC_SSRRS_OFFSET             23
 #define  B_PCIE_PCIEALC_RRPTLPC                  BIT22
 #define  B_PCIE_PCIEALC_RRPTLPC_OFFSET           22
 #define  B_PCIE_PCIEALC_RTD3PDSP                 BIT21
 #define  B_PCIE_PCIEALC_RTD3PDSP_OFFSET          21
 #define  B_PCIE_PCIEALC_PDSP                     BIT20
 #define  B_PCIE_PCIEALC_PDSP_OFFSET              20
 #define  B_PCIE_PCIEALC_CLG3FE                   BIT16
 #define  B_PCIE_PCIEALC_CLG3FE_OFFSET            16
 #define  B_PCIE_PCIEALC_CLG3FE_MASK              0xF0000
 #define  B_PCIE_PCIEALC_ACKNAKGH                 BIT9
 #define  B_PCIE_PCIEALC_ACKNAKGH_OFFSET          9
 #define  B_PCIE_PCIEALC_G3SKPOSL                 BIT0
 #define  B_PCIE_PCIEALC_G3SKPOSL_OFFSET          0
 #define  B_PCIE_PCIEALC_G3SKPOSL_MASK            0x1FF

#define  R_PCIE_VC0PCF                            0x340
 #define  B_PCIE_VC0PCF_VC0PCFH                   BIT16
 #define  B_PCIE_VC0PCF_VC0PCFH_OFFSET            16
 #define  B_PCIE_VC0PCF_VC0PCFH_MASK              0xFF0000
 #define  B_PCIE_VC0PCF_VC0PCFD                   BIT0
 #define  B_PCIE_VC0PCF_VC0PCFD_OFFSET            0
 #define  B_PCIE_VC0PCF_VC0PCFD_MASK              0xFFF

#define  R_PCIE_VC0NPCF                           0x344
 #define  B_PCIE_VC0NPCF_VC0NPCFH                 BIT16
 #define  B_PCIE_VC0NPCF_VC0NPCFH_OFFSET          16
 #define  B_PCIE_VC0NPCF_VC0NPCFH_MASK            0xFF0000
 #define  B_PCIE_VC0NPCF_VC0NPCFD                 BIT0
 #define  B_PCIE_VC0NPCF_VC0NPCFD_OFFSET          0
 #define  B_PCIE_VC0NPCF_VC0NPCFD_MASK            0xFFF

#define  R_PCIE_VC0CPCF                           0x348
 #define  B_PCIE_VC0CPCF_VC0CPCFH                 BIT16
 #define  B_PCIE_VC0CPCF_VC0CPCFH_OFFSET          16
 #define  B_PCIE_VC0CPCF_VC0CPCFH_MASK            0xFF0000
 #define  B_PCIE_VC0CPCF_VC0CPCFD                 BIT0
 #define  B_PCIE_VC0CPCF_VC0CPCFD_OFFSET          0
 #define  B_PCIE_VC0CPCF_VC0CPCFD_MASK            0xFFF

#define  R_PCIE_PTMPD                             0x390
 #define  B_PCIE_PTMPD_CPTMPDV                    BIT0
 #define  B_PCIE_PTMPD_CPTMPDV_OFFSET             0
 #define  B_PCIE_PTMPD_CPTMPDV_MASK               0xFFFFFFFF

#define  R_PCIE_PTMLLMT                           0x394
 #define  B_PCIE_PTMLLMT_CPTMLLMTV                BIT0
 #define  B_PCIE_PTMLLMT_CPTMLLMTV_OFFSET         0
 #define  B_PCIE_PTMLLMT_CPTMLLMTV_MASK           0xFFFFFFFF

#define  R_PCIE_PTMULMT                           0x398
 #define  B_PCIE_PTMULMT_CPTMULMTV                BIT0
 #define  B_PCIE_PTMULMT_CPTMULMTV_OFFSET         0
 #define  B_PCIE_PTMULMT_CPTMULMTV_MASK           0xFFFFFFFF

#define R_SA_PCIE_CFG_PTMPSDC1                    0x39C ///< PEG PTM Pipe Stage Delay Configuration 1
#define R_SA_PCIE_CFG_PTMPSDC2                    0x3A0 ///< PEG PTM Pipe Stage Delay Configuration 2
#define R_SA_PCIE_CFG_PTMPSDC3                    0x3A4 ///< PEG PTM Pipe Stage Delay Configuration 3
#define R_SA_PCIE_CFG_PTMPSDC4                    0x3A8 ///< PEG PTM Pipe Stage Delay Configuration 4
#define R_SA_PCIE_CFG_PTMPSDC5                    0x3AC ///< PEG PTM Pipe Stage Delay Configuration 5

#define  R_PCIE_PTMECFG                           0x3B0
 #define  B_PCIE_PTMECFG_PTMMMC                   BIT21
 #define  B_PCIE_PTMECFG_PTMMMC_OFFSET            21
 #define  B_PCIE_PTMECFG_PTMMMC_MASK              0x600000
 #define  B_PCIE_PTMECFG_PLTLFF                   BIT18
 #define  B_PCIE_PTMECFG_PLTLFF_OFFSET            18
 #define  B_PCIE_PTMECFG_PLTLFF_MASK              0x1C0000
 #define  B_PCIE_PTMECFG_GTFRC                    BIT15
 #define  B_PCIE_PTMECFG_GTFRC_OFFSET             15
 #define  B_PCIE_PTMECFG_GTFRC_MASK               0x38000
 #define  B_PCIE_PTMECFG_GTFFC                    BIT13
 #define  B_PCIE_PTMECFG_GTFFC_OFFSET             13
 #define  B_PCIE_PTMECFG_GTFFC_MASK               0x6000
 #define  B_PCIE_PTMECFG_GTFSPC                   BIT12
 #define  B_PCIE_PTMECFG_GTFSPC_OFFSET            12
 #define  B_PCIE_PTMECFG_PGTSCFF                  BIT9
 #define  B_PCIE_PTMECFG_PGTSCFF_OFFSET           9
 #define  B_PCIE_PTMECFG_PGTSCFF_MASK             0xE00
 #define  B_PCIE_PTMECFG_PGTSCFE                  BIT8
 #define  B_PCIE_PTMECFG_PGTSCFE_OFFSET           8
 #define  B_PCIE_PTMECFG_TGTSCF                   BIT7
 #define  B_PCIE_PTMECFG_TGTSCF_OFFSET            7
 #define  B_PCIE_PTMECFG_PTMRPAE                  BIT6
 #define  B_PCIE_PTMECFG_PTMRPAE_OFFSET           6
 #define  B_PCIE_PTMECFG_PTMRNOPAD                BIT4
 #define  B_PCIE_PTMECFG_PTMRNOPAD_OFFSET         4
 #define  B_PCIE_PTMECFG_PTMRNOPAD_MASK           0x30
 #define  B_PCIE_PTMECFG_IOSFMADP                 BIT0
 #define  B_PCIE_PTMECFG_IOSFMADP_OFFSET          0
 #define  B_PCIE_PTMECFG_IOSFMADP_MASK            0xF

#define  R_PCIE_PTMLT2TSTMP                       0x3B4
 #define  B_PCIE_PTMLT2TSTMP_LCLT2TS              BIT0
 #define  B_PCIE_PTMLT2TSTMP_LCLT2TS_OFFSET       0
 #define  B_PCIE_PTMLT2TSTMP_LCLT2TS_MASK         0xFFFFFFFF

#define  R_PCIE_PTMT2TSTMP                        0x3B8
 #define  B_PCIE_PTMT2TSTMP_LCUT2TS               BIT0
 #define  B_PCIE_PTMT2TSTMP_LCUT2TS_OFFSET        0
 #define  B_PCIE_PTMT2TSTMP_LCUT2TS_MASK          0xFFFFFFFF

#define  R_PCIE_DPCECTL                           0x3BC
 #define  B_PCIE_DPCECTL_DPCTSCIEN                BIT3
 #define  B_PCIE_DPCECTL_DPCTSCIEN_OFFSET         3
 #define  B_PCIE_DPCECTL_DPCTSMIEN                BIT2
 #define  B_PCIE_DPCECTL_DPCTSMIEN_OFFSET         2
 #define  B_PCIE_DPCECTL_RPPIOERRSCIEN            BIT1
 #define  B_PCIE_DPCECTL_RPPIOERRSCIEN_OFFSET     1
 #define  B_PCIE_DPCECTL_RPPIOERRSMIEN            BIT0
 #define  B_PCIE_DPCECTL_RPPIOERRSMIEN_OFFSET     0

#define  R_PCIE_DLS                               0x3C0
 #define  B_PCIE_DLS_LO                           BIT2
 #define  B_PCIE_DLS_LO_OFFSET                    2
 #define  B_PCIE_DLS_LSR                          BIT1
 #define  B_PCIE_DLS_LSR_OFFSET                   1
 #define  B_PCIE_DLS_PCLKW                        BIT0
 #define  B_PCIE_DLS_PCLKW_OFFSET                 0

#define  R_PCIE_BWCHGDBUG                         0x3C4
 #define  B_PCIE_BWCHGDBUG_LSMC                   BIT24
 #define  B_PCIE_BWCHGDBUG_LSMC_OFFSET            24
 #define  B_PCIE_BWCHGDBUG_LSMC_MASK              0xFF000000
 #define  B_PCIE_BWCHGDBUG_LWMC                   BIT16
 #define  B_PCIE_BWCHGDBUG_LWMC_OFFSET            16
 #define  B_PCIE_BWCHGDBUG_LWMC_MASK              0xFF0000
 #define  B_PCIE_BWCHGDBUG_LSCC                   BIT8
 #define  B_PCIE_BWCHGDBUG_LSCC_OFFSET            8
 #define  B_PCIE_BWCHGDBUG_LSCC_MASK              0xFF00
 #define  B_PCIE_BWCHGDBUG_LWCC                   BIT0
 #define  B_PCIE_BWCHGDBUG_LWCC_OFFSET            0
 #define  B_PCIE_BWCHGDBUG_LWCC_MASK              0xFF

#define  R_PCIE_LNKDBUG                           0x3C8
 #define  B_PCIE_LNKDBUG_LTF                      BIT20
 #define  B_PCIE_LNKDBUG_LTF_OFFSET               20
 #define  B_PCIE_LNKDBUG_LTF_MASK                 0x300000
 #define  B_PCIE_LNKDBUG_SCF                      BIT18
 #define  B_PCIE_LNKDBUG_SCF_OFFSET               18
 #define  B_PCIE_LNKDBUG_SCF_MASK                 0xC0000
 #define  B_PCIE_LNKDBUG_LWCF                     BIT16
 #define  B_PCIE_LNKDBUG_LWCF_OFFSET              16
 #define  B_PCIE_LNKDBUG_LWCF_MASK                0x30000
 #define  B_PCIE_LNKDBUG_NRTLPC                   BIT12
 #define  B_PCIE_LNKDBUG_NRTLPC_OFFSET            12
 #define  B_PCIE_LNKDBUG_NRTLPC_MASK              0xF000
 #define  B_PCIE_LNKDBUG_RTLPCRCEC                BIT8
 #define  B_PCIE_LNKDBUG_RTLPCRCEC_OFFSET         8
 #define  B_PCIE_LNKDBUG_RTLPCRCEC_MASK           0xF00
 #define  B_PCIE_LNKDBUG_RDIRC                    BIT4
 #define  B_PCIE_LNKDBUG_RDIRC_OFFSET             4
 #define  B_PCIE_LNKDBUG_RDIRC_MASK               0xF0
 #define  B_PCIE_LNKDBUG_RRDNC                    BIT0
 #define  B_PCIE_LNKDBUG_RRDNC_OFFSET             0
 #define  B_PCIE_LNKDBUG_RRDNC_MASK               0xF

#define  R_PCIE_RECDBUG                           0x3CC
 #define  B_PCIE_RECDBUG_CREE7                    BIT28
 #define  B_PCIE_RECDBUG_CREE7_OFFSET             28
 #define  B_PCIE_RECDBUG_CREE7_MASK               0xF0000000
 #define  B_PCIE_RECDBUG_CREE6                    BIT24
 #define  B_PCIE_RECDBUG_CREE6_OFFSET             24
 #define  B_PCIE_RECDBUG_CREE6_MASK               0xF000000
 #define  B_PCIE_RECDBUG_CREE5                    BIT20
 #define  B_PCIE_RECDBUG_CREE5_OFFSET             20
 #define  B_PCIE_RECDBUG_CREE5_MASK               0xF00000
 #define  B_PCIE_RECDBUG_CREE4                    BIT16
 #define  B_PCIE_RECDBUG_CREE4_OFFSET             16
 #define  B_PCIE_RECDBUG_CREE4_MASK               0xF0000
 #define  B_PCIE_RECDBUG_CREE3                    BIT12
 #define  B_PCIE_RECDBUG_CREE3_OFFSET             12
 #define  B_PCIE_RECDBUG_CREE3_MASK               0xF000
 #define  B_PCIE_RECDBUG_CREE2                    BIT8
 #define  B_PCIE_RECDBUG_CREE2_OFFSET             8
 #define  B_PCIE_RECDBUG_CREE2_MASK               0xF00
 #define  B_PCIE_RECDBUG_CREE1                    BIT4
 #define  B_PCIE_RECDBUG_CREE1_OFFSET             4
 #define  B_PCIE_RECDBUG_CREE1_MASK               0xF0
 #define  B_PCIE_RECDBUG_CREE0                    BIT0
 #define  B_PCIE_RECDBUG_CREE0_OFFSET             0
 #define  B_PCIE_RECDBUG_CREE0_MASK               0xF

#define  R_PCIE_LTROVR                            0x400
 #define  B_PCIE_LTROVR_LTRNSROVR                 BIT31
 #define  B_PCIE_LTROVR_LTRNSROVR_OFFSET          31
 #define  B_PCIE_LTROVR_LTRNSLSOVRV               BIT26
 #define  B_PCIE_LTROVR_LTRNSLSOVRV_OFFSET        26
 #define  B_PCIE_LTROVR_LTRNSLSOVRV_MASK          0x1C000000
 #define  B_PCIE_LTROVR_LTRNSLOVRV                BIT16
 #define  B_PCIE_LTROVR_LTRNSLOVRV_OFFSET         16
 #define  B_PCIE_LTROVR_LTRNSLOVRV_MASK           0x3FF0000
 #define  B_PCIE_LTROVR_LTRSROVR                  BIT15
 #define  B_PCIE_LTROVR_LTRSROVR_OFFSET           15
 #define  B_PCIE_LTROVR_LTRSLSOVRV                BIT10
 #define  B_PCIE_LTROVR_LTRSLSOVRV_OFFSET         10
 #define  B_PCIE_LTROVR_LTRSLSOVRV_MASK           0x1C00
 #define  B_PCIE_LTROVR_LTRSLOVRV                 BIT0
 #define  B_PCIE_LTROVR_LTRSLOVRV_OFFSET          0
 #define  B_PCIE_LTROVR_LTRSLOVRV_MASK            0x3FF

#define  R_PCIE_LTROVR2                           0x404
 #define  B_PCIE_LTROVR2_LTROVRPLCY               BIT3
 #define  B_PCIE_LTROVR2_LTROVRPLCY_OFFSET        3
 #define  B_PCIE_LTROVR2_LTRCFGLOCK               BIT2
 #define  B_PCIE_LTROVR2_LTRCFGLOCK_OFFSET        2
 #define  B_PCIE_LTROVR2_LTRNSOVREN               BIT1
 #define  B_PCIE_LTROVR2_LTRNSOVREN_OFFSET        1
 #define  B_PCIE_LTROVR2_LTRSOVREN                BIT0
 #define  B_PCIE_LTROVR2_LTRSOVREN_OFFSET         0

#define  R_PCIE_PHYCTL4                           0x408
 #define  B_PCIE_PHYCTL4_SQDIS                    BIT27
 #define  B_PCIE_PHYCTL4_SQDIS_OFFSET             27
 #define  B_PCIE_PHYCTL4_G12CTSDP                 BIT0
 #define  B_PCIE_PHYCTL4_G12CTSDP_OFFSET          0

#define  R_PCIE_STRPFUSECFG2                      0x414
 #define  B_PCIE_STRPFUSECFG2_EBM                 BIT14
 #define  B_PCIE_STRPFUSECFG2_EBM_OFFSET          14
 #define  B_PCIE_STRPFUSECFG2_PCIESL              BIT10
 #define  B_PCIE_STRPFUSECFG2_PCIESL_OFFSET       10
 #define  B_PCIE_STRPFUSECFG2_PCIESL_MASK         0xC00
 #define  B_PCIE_STRPFUSECFG2_FORCEL              BIT7
 #define  B_PCIE_STRPFUSECFG2_FORCEL_OFFSET       7
 #define  B_PCIE_STRPFUSECFG2_FORCEL_MASK         0x380
 #define  B_PCIE_STRPFUSECFG2_VTDTE               BIT6
 #define  B_PCIE_STRPFUSECFG2_VTDTE_OFFSET        6
 #define  B_PCIE_STRPFUSECFG2_FDSV                BIT3
 #define  B_PCIE_STRPFUSECFG2_FDSV_OFFSET         3
 #define  B_PCIE_STRPFUSECFG2_FDSV_MASK           0x38
 #define  B_PCIE_STRPFUSECFG2_DMITXSWING          BIT2
 #define  B_PCIE_STRPFUSECFG2_DMITXSWING_OFFSET   2
 #define  B_PCIE_STRPFUSECFG2_CPUSEL              BIT1
 #define  B_PCIE_STRPFUSECFG2_CPUSEL_OFFSET       1
 #define  B_PCIE_STRPFUSECFG2_LTLPPDIS            BIT0
 #define  B_PCIE_STRPFUSECFG2_LTLPPDIS_OFFSET     0

#define  R_PCIE_PCIEPMECTL                        0x420
 #define  B_PCIE_PCIEPMECTL_FDPPGE                BIT31
 #define  B_PCIE_PCIEPMECTL_FDPPGE_OFFSET         31
 #define  B_PCIE_PCIEPMECTL_DLSULPPGE             BIT30
 #define  B_PCIE_PCIEPMECTL_DLSULPPGE_OFFSET      30
 #define  B_PCIE_PCIEPMECTL_DLSULDLSD             BIT29
 #define  B_PCIE_PCIEPMECTL_DLSULDLSD_OFFSET      29
 #define  B_PCIE_PCIEPMECTL_L1OCREWD              BIT28
 #define  B_PCIE_PCIEPMECTL_L1OCREWD_OFFSET       28
 #define  B_PCIE_PCIEPMECTL_L1OEXPC               BIT27
 #define  B_PCIE_PCIEPMECTL_L1OEXPC_OFFSET        27
 #define  B_PCIE_PCIEPMECTL_L1OENTPC              BIT26
 #define  B_PCIE_PCIEPMECTL_L1OENTPC_OFFSET       26
 #define  B_PCIE_PCIEPMECTL_L1ORMRT               BIT24
 #define  B_PCIE_PCIEPMECTL_L1ORMRT_OFFSET        24
 #define  B_PCIE_PCIEPMECTL_L1ORMRT_MASK          0x3000000
 #define  B_PCIE_PCIEPMECTL_L1OFFMRT              BIT22
 #define  B_PCIE_PCIEPMECTL_L1OFFMRT_OFFSET       22
 #define  B_PCIE_PCIEPMECTL_L1OFFMRT_MASK         0xC00000
 #define  B_PCIE_PCIEPMECTL_IPIEP                 BIT21
 #define  B_PCIE_PCIEPMECTL_IPIEP_OFFSET          21
 #define  B_PCIE_PCIEPMECTL_IPACPE                BIT20
 #define  B_PCIE_PCIEPMECTL_IPACPE_OFFSET         20
 #define  B_PCIE_PCIEPMECTL_POFFWT                BIT18
 #define  B_PCIE_PCIEPMECTL_POFFWT_OFFSET         18
 #define  B_PCIE_PCIEPMECTL_POFFWT_MASK           0xC0000
 #define  B_PCIE_PCIEPMECTL_L1LE                  BIT17
 #define  B_PCIE_PCIEPMECTL_L1LE_OFFSET           17
 #define  B_PCIE_PCIEPMECTL_L1LTRTLSV             BIT14
 #define  B_PCIE_PCIEPMECTL_L1LTRTLSV_OFFSET      14
 #define  B_PCIE_PCIEPMECTL_L1LTRTLSV_MASK        0x1C000
 #define  B_PCIE_PCIEPMECTL_L1LTRTLV              BIT4
 #define  B_PCIE_PCIEPMECTL_L1LTRTLV_OFFSET       4
 #define  B_PCIE_PCIEPMECTL_L1LTRTLV_MASK         0x3FF0
 #define  V_PCIE_PCIEPMECTL_L1LTRTLV              0x32
 #define  B_PCIE_PCIEPMECTL_L1SNZCREWD            BIT3
 #define  B_PCIE_PCIEPMECTL_L1SNZCREWD_OFFSET     3
 #define  B_PCIE_PCIEPMECTL_L1SNZPPGEXPC          BIT2
 #define  B_PCIE_PCIEPMECTL_L1SNZPPGEXPC_OFFSET   2
 #define  B_PCIE_PCIEPMECTL_L1SNZPPGENTPC         BIT1
 #define  B_PCIE_PCIEPMECTL_L1SNZPPGENTPC_OFFSET  1
 #define  B_PCIE_PCIEPMECTL_L1FSOE                BIT0
 #define  B_PCIE_PCIEPMECTL_L1FSOE_OFFSET         0

#define  R_PCIE_PCIEPMECTL2                       0x424
 #define  B_PCIE_PCIEPMECTL2_MEXL1PGLTRTLSV       BIT29
 #define  B_PCIE_PCIEPMECTL2_MEXL1PGLTRTLSV_OFFSET 29
 #define  B_PCIE_PCIEPMECTL2_MEXL1PGLTRTLSV_MASK  0xE0000000
 #define  B_PCIE_PCIEPMECTL2_PGCBBLD              BIT28
 #define  B_PCIE_PCIEPMECTL2_PGCBBLD_OFFSET       28
 #define  B_PCIE_PCIEPMECTL2_CPMCSRE              BIT27
 #define  B_PCIE_PCIEPMECTL2_CPMCSRE_OFFSET       27
 #define  B_PCIE_PCIEPMECTL2_L1SPPGE              BIT26
 #define  B_PCIE_PCIEPMECTL2_L1SPPGE_OFFSET       26
 #define  B_PCIE_PCIEPMECTL2_MEXL1PGLTRTLV        BIT16
 #define  B_PCIE_PCIEPMECTL2_MEXL1PGLTRTLV_OFFSET 16
 #define  B_PCIE_PCIEPMECTL2_MEXL1PGLTRTLV_MASK   0x3FF0000
 #define  B_PCIE_PCIEPMECTL2_CPGEXH               BIT14
 #define  B_PCIE_PCIEPMECTL2_CPGEXH_OFFSET        14
 #define  B_PCIE_PCIEPMECTL2_CPGEXH_MASK          0xC000
 #define  B_PCIE_PCIEPMECTL2_CPGENH               BIT12
 #define  B_PCIE_PCIEPMECTL2_CPGENH_OFFSET        12
 #define  B_PCIE_PCIEPMECTL2_CPGENH_MASK          0x3000
 #define  B_PCIE_PCIEPMECTL2_PHYCLPGE             BIT11
 #define  B_PCIE_PCIEPMECTL2_PHYCLPGE_OFFSET      11
 #define  B_PCIE_PCIEPMECTL2_L1SPHYDLPGE          BIT9
 #define  B_PCIE_PCIEPMECTL2_L1SPHYDLPGE_OFFSET   9
 #define  B_PCIE_PCIEPMECTL2_FDCPGE               BIT8
 #define  B_PCIE_PCIEPMECTL2_FDCPGE_OFFSET        8
 #define  B_PCIE_PCIEPMECTL2_DETSCPGE             BIT7
 #define  B_PCIE_PCIEPMECTL2_DETSCPGE_OFFSET      7
 #define  B_PCIE_PCIEPMECTL2_L23RDYSCPGE          BIT6
 #define  B_PCIE_PCIEPMECTL2_L23RDYSCPGE_OFFSET   6
 #define  B_PCIE_PCIEPMECTL2_DISSCPGE             BIT5
 #define  B_PCIE_PCIEPMECTL2_DISSCPGE_OFFSET      5
 #define  B_PCIE_PCIEPMECTL2_L1SCPGE              BIT4
 #define  B_PCIE_PCIEPMECTL2_L1SCPGE_OFFSET       4
 #define  B_PCIE_PCIEPMECTL2_DSPM                 BIT3
 #define  B_PCIE_PCIEPMECTL2_DSPM_OFFSET          3
 #define  B_PCIE_PCIEPMECTL2_L1OTCMRP             BIT2
 #define  B_PCIE_PCIEPMECTL2_L1OTCMRP_OFFSET      2
 #define  B_PCIE_PCIEPMECTL2_DLPM                 BIT1
 #define  B_PCIE_PCIEPMECTL2_DLPM_OFFSET          1
 #define  B_PCIE_PCIEPMECTL2_SL1OEE               BIT0
 #define  B_PCIE_PCIEPMECTL2_SL1OEE_OFFSET        0

#define  R_PCIE_PCE                               0x428
 #define  B_PCIE_PCE_HAE                          BIT5
 #define  B_PCIE_PCE_HAE_OFFSET                   5
 #define  B_PCIE_PCE_SE                           BIT3
 #define  B_PCIE_PCE_SE_OFFSET                    3
 #define  B_PCIE_PCE_PMCRE                        BIT0
 #define  B_PCIE_PCE_PMCRE_OFFSET                 0

#define  R_PCIE_PGCBCTL1                          0x42C
 #define  B_PCIE_PGCBCTL1_TRSTUP2FRCCLKS          BIT28
 #define  B_PCIE_PGCBCTL1_TRSTUP2FRCCLKS_OFFSET   28
 #define  B_PCIE_PGCBCTL1_TRSTUP2FRCCLKS_MASK     0x30000000
 #define  B_PCIE_PGCBCTL1_TCLKSONACK_CP           BIT26
 #define  B_PCIE_PGCBCTL1_TCLKSONACK_CP_OFFSET    26
 #define  B_PCIE_PGCBCTL1_TCLKSONACK_CP_MASK      0xC000000
 #define  B_PCIE_PGCBCTL1_TPOKUP                  BIT20
 #define  B_PCIE_PGCBCTL1_TPOKUP_OFFSET           20
 #define  B_PCIE_PGCBCTL1_TPOKUP_MASK             0x300000
 #define  B_PCIE_PGCBCTL1_TPOKDOWN                BIT18
 #define  B_PCIE_PGCBCTL1_TPOKDOWN_OFFSET         18
 #define  B_PCIE_PGCBCTL1_TPOKDOWN_MASK           0xC0000
 #define  B_PCIE_PGCBCTL1_TLATCHDIS               BIT16
 #define  B_PCIE_PGCBCTL1_TLATCHDIS_OFFSET        16
 #define  B_PCIE_PGCBCTL1_TLATCHDIS_MASK          0x30000
 #define  B_PCIE_PGCBCTL1_TSLEEPINACTIV           BIT14
 #define  B_PCIE_PGCBCTL1_TSLEEPINACTIV_OFFSET    14
 #define  B_PCIE_PGCBCTL1_TSLEEPINACTIV_MASK      0xC000
 #define  B_PCIE_PGCBCTL1_TINACCRSTUP             BIT12
 #define  B_PCIE_PGCBCTL1_TINACCRSTUP_OFFSET      12
 #define  B_PCIE_PGCBCTL1_TINACCRSTUP_MASK        0x3000
 #define  B_PCIE_PGCBCTL1_TACCRSTUP               BIT10
 #define  B_PCIE_PGCBCTL1_TACCRSTUP_OFFSET        10
 #define  B_PCIE_PGCBCTL1_TACCRSTUP_MASK          0xC00
 #define  B_PCIE_PGCBCTL1_TLATCHEN                BIT8
 #define  B_PCIE_PGCBCTL1_TLATCHEN_OFFSET         8
 #define  B_PCIE_PGCBCTL1_TLATCHEN_MASK           0x300
 #define  B_PCIE_PGCBCTL1_TDEISOLATE              BIT6
 #define  B_PCIE_PGCBCTL1_TDEISOLATE_OFFSET       6
 #define  B_PCIE_PGCBCTL1_TDEISOLATE_MASK         0xC0
 #define  B_PCIE_PGCBCTL1_TRSTDOWN                BIT4
 #define  B_PCIE_PGCBCTL1_TRSTDOWN_OFFSET         4
 #define  B_PCIE_PGCBCTL1_TRSTDOWN_MASK           0x30
 #define  B_PCIE_PGCBCTL1_TISOLATE                BIT2
 #define  B_PCIE_PGCBCTL1_TISOLATE_OFFSET         2
 #define  B_PCIE_PGCBCTL1_TISOLATE_MASK           0xC
 #define  B_PCIE_PGCBCTL1_TSLEEPACT               BIT0
 #define  B_PCIE_PGCBCTL1_TSLEEPACT_OFFSET        0
 #define  B_PCIE_PGCBCTL1_TSLEEPACT_MASK          0x3

#define  R_PCIE_PGCBCTL2                          0x430

#define R_PCIE_PCIEPMECTL3                        0x434
 #define B_PCIE_PCIEPMECTL3_L1PGAUTOPGEN          BIT4
 #define B_PCIE_PCIEPMECTL3_OSCCGH                BIT2
 #define B_PCIE_PCIEPMECTL3_OSCCGH_OFFSET         2
 #define B_PCIE_PCIEPMECTL3_OSCCGH_MASK          (BIT3 | BIT2)
 #define V_PCIE_PCIEPMECTL3_OSCCGH_1US           1
 #define B_PCIE_PCIEPMECTL3_PMREQCPGEXH          BIT0
 #define B_PCIE_PCIEPMECTL3_PMREQCPGEXH_MASK     0x3
 #define B_PCIE_PCIEPMECTL3_PMREQCPGEXH_OFFSET   0
 #define V_PCIE_PCIEPMECTL3_PMREQCPGEXH          0x1

#define  R_PCIE_EQCFG1                            0x450
 #define  S_PCIE_EQCFG1                           4
 #define  B_PCIE_EQCFG1_REC                       0xFF000000
 #define  B_PCIE_EQCFG1_REC_OFFSET                24
 #define  B_PCIE_EQCFG1_REIFECE                   BIT23
 #define  B_PCIE_EQCFG1_LERSMIE                   21
 #define  B_PCIE_EQCFG1_LEB                       BIT19
 #define  B_PCIE_EQCFG1_LEP23B                    BIT18
 #define  B_PCIE_EQCFG1_LEP3B                     BIT17
 #define  B_PCIE_EQCFG1_RTLEPCEB                  BIT16
 #define  B_PCIE_EQCFG1_RTPCOE                    BIT15
 #define  B_PCIE_EQCFG1_HPCMQE                    BIT13
 #define  B_PCIE_EQCFG1_HAED                      BIT12
 #define  B_PCIE_EQCFG1_RWTNEVE                   BIT8
 #define  B_PCIE_EQCFG1_RWTNEVE_MASK              0x00000F00
 #define  V_PCIE_EQCFG1_RWTNEVE_1US               1
 #define  B_PCIE_EQCFG1_EQTS2IRRC                 BIT7
 #define  B_PCIE_EQCFG1_HAPCCPIE                  BIT5
 #define  B_PCIE_EQCFG1_MEQSMMFLNTL               BIT4
 #define  B_PCIE_EQCFG1_MFLNTL                    BIT2
 #define  B_PCIE_EQCFG1_TUPP                      BIT1
 #define  B_PCIE_EQCFG1_RUPP                      BIT0

#define  R_PCIE_RTPCL1                            0x454
 #define  B_PCIE_RTPCL1_PCM                       BIT31
 #define  B_PCIE_RTPCL1_RTPRECL2PL4               0x3F000000
 #define  B_PCIE_RTPCL1_RTPOSTCL1PL3              0xFC0000
 #define  B_PCIE_RTPCL1_RTPRECL1PL2               0x3F000
 #define  B_PCIE_RTPCL1_RTPOSTCL0PL1              0xFC0
 #define  B_PCIE_RTPCL1_RTPRECL0PL0               0x3F

#define  R_PCIE_RTPCL2                            0x458
 #define  B_PCIE_RTPCL2_RTPOSTCL3PL               0x3F000
 #define  B_PCIE_RTPCL2_RTPRECL3PL6               0xFC0
 #define  B_PCIE_RTPCL2_RTPOSTCL2PL5              0x3F
#define  R_PCIE_RTPCL3                            0x45C
#define  R_PCIE_RTPCL4                            0x460
#define  R_PCIE_RTPCL5                            0x4D0
#define  R_PCIE_RTPCL6                            0x4D4
#define  R_PCIE_RTPCL7                            0x4D8

#define  R_PCIE_FOMS                              0x464
 #define  B_PCIE_FOMS_I                           (BIT30 | BIT29)
 #define  B_PCIE_FOMS_I_OFFSET                    29
 #define  B_PCIE_FOMS_LN                          0x1F000000
 #define  B_PCIE_FOMS_LN_OFFSET                   24
 #define  B_PCIE_FOMS_FOMSV                       0x00FFFFFF
 #define  B_PCIE_FOMS_FOMSV0                      0x000000FF
 #define  B_PCIE_FOMS_FOMSV0_OFFSET               0
 #define  B_PCIE_FOMS_FOMSV1                      0x0000FF00
 #define  B_PCIE_FOMS_FOMSV1_OFFSET               8
 #define  B_PCIE_FOMS_FOMSV2                      0x00FF0000
 #define  B_PCIE_FOMS_FOMSV2_OFFSET               16

#define  R_PCIE_HAEQ                              0x468
 #define  B_PCIE_HAEQ_HAPCCPI                     (BIT31 | BIT30 | BIT29 | BIT28)
 #define  B_PCIE_HAEQ_HAPCCPI_OFFSET              28
 #define  B_PCIE_HAEQ_FOMEM                       0x0FF00000
 #define  B_PCIE_HAEQ_FOMEM_OFFSET                20
 #define  B_PCIE_HAEQ_MACFOMC                     BIT19
 #define  B_PCIE_HAEQ_SL                          (BIT18 | BIT17 | BIT16)
 #define  B_PCIE_HAEQ_SL_OFFSET                   16
 #define  B_PCIE_HAEQ_DL                          0x0000FF00
 #define  B_PCIE_HAEQ_DL_OFFSET                   8
 #define  B_PCIE_HAEQ_SFOMFM                      0x000000FF
 #define  B_PCIE_HAEQ_SFOMFM_OFFSET               0

#define  R_PCIE_LTCO1                             0x470
 #define  B_PCIE_LTCO1_L1TCOE                     BIT25
 #define  B_PCIE_LTCO1_L0TCOE                     BIT24
 #define  B_PCIE_LTCO1_L1TPOSTCO                  0xFC0000
 #define  B_PCIE_LTCO1_L1TPOSTCO_OFFSET           18
 #define  B_PCIE_LTCO1_L1TPRECO                   0x3F000
 #define  B_PCIE_LTCO1_L1TPRECO_OFFSET            12
 #define  B_PCIE_LTCO1_L0TPOSTCO                  0xFC0
 #define  B_PCIE_LTCO1_L0TPOSTCO_OFFSET           6
 #define  B_PCIE_LTCO1_L0TPRECO                   0x3F
 #define  B_PCIE_LTCO1_L0TPRECO_OFFSET            0

#define  R_PCIE_LTCO2                             0x474
 #define  B_PCIE_LTCO2_L3TCOE                     BIT25
 #define  B_PCIE_LTCO2_L2TCOE                     BIT24
 #define  B_PCIE_LTCO2_L3TPOSTCO                  0xFC0000
 #define  B_PCIE_LTCO2_L3TPRECO                   0x3F000
 #define  B_PCIE_LTCO2_L2TPOSTCO                  0xFC0
 #define  B_PCIE_LTCO2_L2TPRECO                   0x3F

#define  R_PCIE_G3L0SCTL                          0x478
 #define  B_PCIE_G3L0SCTL_G3ASL0SPL               BIT24
 #define  B_PCIE_G3L0SCTL_G3ASL0SPL_OFFSET        24
 #define  B_PCIE_G3L0SCTL_G3ASL0SPL_MASK          0xFF000000
 #define  V_PCIE_G3L0SCTL_G3ASL0SPL               0x28
 #define  B_PCIE_G3L0SCTL_G3UCNFTS                BIT8
 #define  B_PCIE_G3L0SCTL_G3UCNFTS_OFFSET         8
 #define  B_PCIE_G3L0SCTL_G3UCNFTS_MASK           0x0000FF00
 #define  V_PCIE_G3L0SCTL_G3UCNFTS                0x40
 #define  B_PCIE_G3L0SCTL_G3CCNFTS                BIT0
 #define  B_PCIE_G3L0SCTL_G3CCNFTS_OFFSET         0
 #define  B_PCIE_G3L0SCTL_G3CCNFTS_MASK           0x000000FF
 #define  V_PCIE_G3L0SCTL_G3CCNFTS                0x2C

#define R_PCIE_EQCFG2                             0x47C
 #define  B_PCIE_EQCFG2_NTIC                      0xFF000000
 #define  B_PCIE_EQCFG2_EMD                       BIT23
 #define  B_PCIE_EQCFG2_NTSS                      (BIT22 | BIT21 | BIT20)
 #define  B_PCIE_EQCFG2_PCET                      (BIT19 | BIT18 | BIT17 | BIT16)
 #define  B_PCIE_EQCFG2_PCET_OFFSET               16
 #define  B_PCIE_EQCFG2_HAPCSB                    (BIT15 | BIT14 | BIT13 | BIT12)
 #define  B_PCIE_EQCFG2_HAPCSB_OFFSET             12
 #define  B_PCIE_EQCFG2_NTEME                     BIT11
 #define  B_PCIE_EQCFG2_MPEME                     BIT10
 #define  B_PCIE_EQCFG2_REWMETM                   (BIT9 | BIT8)
 #define  B_PCIE_EQCFG2_REWMETM_OFFSET            8
 #define  B_PCIE_EQCFG2_REWMET                    0xFF

#define  R_PCIE_MM                                0x480
 #define  B_PCIE_MM_MSST                          BIT8
 #define  B_PCIE_MM_MSST_OFFSET                   8
 #define  B_PCIE_MM_MSST_MASK                     0xFFFFFF00
 #define  B_PCIE_MM_MSS                           BIT0
 #define  B_PCIE_MM_MSS_OFFSET                    0
 #define  B_PCIE_MM_MSS_MASK                      0xFF

#define R_PCIE_CDM                                0x484
 #define B_PCIE_CDM_MSS                           BIT4
 #define B_PCIE_CDM_MSS_OFFSET                    4
 #define B_PCIE_CDM_MSS_MASK                      0x0F000000

#define  R_PCIE_EQCFG4                            0x48C
 #define  B_PCIE_EQCFG4_PX16GTSWLPCE              BIT27
 #define  B_PCIE_EQCFG4_PX8GTSWLPCE               BIT24
 #define  B_PCIE_EQCFG4_PX16GREIC                 BIT20
 #define  B_PCIE_EQCFG4_PX16GLEP23B               BIT18
 #define  B_PCIE_EQCFG4_PX16GLEP3B                BIT17
 #define  B_PCIE_EQCFG4_PX16GLEPCEB               BIT16
 #define  B_PCIE_EQCFG4_PX16GRTPCOE               BIT15
 #define  B_PCIE_EQCFG4_PX16GRWTNEVE              BIT8
 #define  B_PCIE_EQCFG4_PX16GRWTNEVE_MASK         0x00000F00
 #define  V_PCIE_EQCFG4_PX16GRWTNEVE_1US          1
 #define  V_PCIE_EQCFG4_PX16GRWTNEVE_3US          3
 #define  B_PCIE_EQCFG4_PX16GHAED                 BIT12
 #define  B_PCIE_EQCFG4_PX16GEQTS2IRRC            BIT7
 #define  B_PCIE_EQCFG4_PX16GHAPCCPI              BIT3
 #define  B_PCIE_EQCFG4_PX16GHAPCCPI_OFFSET       3
 #define  B_PCIE_EQCFG4_PX16GHAPCCPI_MASK         (BIT6 | BIT5 | BIT4 | BIT3)
 #define  B_PCIE_EQCFG4_PX16GHAPCCPIE             BIT2
 #define  B_PCIE_EQCFG4_PX16GMEQSMMFLNTL          BIT1
 #define  B_PCIE_EQCFG4_PX16GMFLNTL               BIT0

// 2LM
#define  R_PCIE_CONTROL1                          0x4A0
 #define  B_PCIE_CONTROL1_L0SPFCUF                BIT15
 #define  B_PCIE_CONTROL1_L0SPFCUF_OFFSET         15
 #define  B_PCIE_CONTROL1_L0SPFCUF_MASK           0x18000

#define  R_PCIE_PELC1                             0x4B4
 #define  B_PCIE_PELC1_L7LN                       BIT28
 #define  B_PCIE_PELC1_L7LN_OFFSET                28
 #define  B_PCIE_PELC1_L7LN_MASK                  0xF0000000
 #define  B_PCIE_PELC1_L6LN                       BIT24
 #define  B_PCIE_PELC1_L6LN_OFFSET                24
 #define  B_PCIE_PELC1_L6LN_MASK                  0xF000000
 #define  B_PCIE_PELC1_L5LN                       BIT20
 #define  B_PCIE_PELC1_L5LN_OFFSET                20
 #define  B_PCIE_PELC1_L5LN_MASK                  0xF00000
 #define  B_PCIE_PELC1_L4LN                       BIT16
 #define  B_PCIE_PELC1_L4LN_OFFSET                16
 #define  B_PCIE_PELC1_L4LN_MASK                  0xF0000
 #define  B_PCIE_PELC1_L3LN                       BIT12
 #define  B_PCIE_PELC1_L3LN_OFFSET                12
 #define  B_PCIE_PELC1_L3LN_MASK                  0xF000
 #define  B_PCIE_PELC1_L2LN                       BIT8
 #define  B_PCIE_PELC1_L2LN_OFFSET                8
 #define  B_PCIE_PELC1_L2LN_MASK                  0xF00
 #define  B_PCIE_PELC1_L1LN                       BIT4
 #define  B_PCIE_PELC1_L1LN_OFFSET                4
 #define  B_PCIE_PELC1_L1LN_MASK                  0xF0
 #define  B_PCIE_PELC1_L0LN                       BIT0
 #define  B_PCIE_PELC1_L0LN_OFFSET                0
 #define  B_PCIE_PELC1_L0LN_MASK                  0xF

#define  R_PCIE_PELC2                             0x4B8
 #define  B_PCIE_PELC2_L15LN                      BIT28
 #define  B_PCIE_PELC2_L15LN_OFFSET               28
 #define  B_PCIE_PELC2_L15LN_MASK                 0xF0000000
 #define  B_PCIE_PELC2_L14LN                      BIT24
 #define  B_PCIE_PELC2_L14LN_OFFSET               24
 #define  B_PCIE_PELC2_L14LN_MASK                 0xF000000
 #define  B_PCIE_PELC2_L13LN                      BIT20
 #define  B_PCIE_PELC2_L13LN_OFFSET               20
 #define  B_PCIE_PELC2_L13LN_MASK                 0xF00000
 #define  B_PCIE_PELC2_L12LN                      BIT16
 #define  B_PCIE_PELC2_L12LN_OFFSET               16
 #define  B_PCIE_PELC2_L12LN_MASK                 0xF0000
 #define  B_PCIE_PELC2_L11LN                      BIT12
 #define  B_PCIE_PELC2_L11LN_OFFSET               12
 #define  B_PCIE_PELC2_L11LN_MASK                 0xF000
 #define  B_PCIE_PELC2_L10LN                      BIT8
 #define  B_PCIE_PELC2_L10LN_OFFSET               8
 #define  B_PCIE_PELC2_L10LN_MASK                 0xF00
 #define  B_PCIE_PELC2_L9LN                       BIT4
 #define  B_PCIE_PELC2_L9LN_OFFSET                4
 #define  B_PCIE_PELC2_L9LN_MASK                  0xF0
 #define  B_PCIE_PELC2_L8LN                       BIT0
 #define  B_PCIE_PELC2_L8LN_OFFSET                0
 #define  B_PCIE_PELC2_L8LN_MASK                  0xF

#define  R_PCIE_IOSFC0TC                          0x4BC

#define  R_PCIE_PX16GRTPCL1                      0x4DC
#define  B_PCIE_PX16GRTPCL1_PCM                  BIT31
#define  B_PCIE_PX16GRTPCL1_RTPRECL2PL4          0x3F000000
#define  B_PCIE_PX16GRTPCL1_RTPOSTCL1PL3         0xFC0000
#define  B_PCIE_PX16GRTPCL1_RTPRECL1PL2          0x3F000
#define  B_PCIE_PX16GRTPCL1_RTPOSTCL0PL1         0xFC0
#define  B_PCIE_PX16GRTPCL1_RTPRECL0PL0          0x3F

#define  R_PCIE_PX16GRTPCL2                      0x4E0
#define  B_PCIE_PX16GRTPCL2_RTPOSTCL3PL          0x3F000
#define  B_PCIE_PX16GRTPCL2_RTPRECL3PL6          0xFC0
#define  B_PCIE_PX16GRTPCL2_RTPOSTCL2PL5         0x3F

#define  R_PCIE_PX16GRTPCL3                      0x45C
#define  R_PCIE_PX16GRTPCL4                      0x460
#define  R_PCIE_PX16GRTPCL5                      0x4D0
#define  R_PCIE_PX16GRTPCL6                      0x4D4
#define  R_PCIE_PX16GRTPCL7                      0x4D8

#define  R_PCIE_EQCFG5                           0x4F8
 #define  B_PCIE_EQCFG5_NTIC                     BIT24
 #define  B_PCIE_EQCFG5_NTIC_MASK                0xFF000000
 #define  B_PCIE_EQCFG5_EMD                      BIT23
 #define  B_PCIE_EQCFG5_PCET                     BIT16
 #define  B_PCIE_EQCFG5_PCET_MASK                (BIT19 | BIT18 | BIT17 | BIT16)
 #define  B_PCIE_EQCFG5_PCET_OFFSET              16
 #define  B_PCIE_EQCFG5_HAPCSB                   BIT12
 #define  B_PCIE_EQCFG5_HAPCSB_OFFSET            12
 #define  B_PCIE_EQCFG5_HAPCSB_MASK              (BIT15 | BIT14 | BIT13 | BIT12)
 #define  B_PCIE_EQCFG5_NTEME                     BIT11
 #define  B_PCIE_EQCFG5_MPEME                     BIT10

#define  R_PCIE_L0P0P1PCM                         0x500
#define  R_PCIE_L0P1P2P3PCM                       0x504
#define  R_PCIE_L0P3P4PCM                         0x508
#define  R_PCIE_L0P5P6PCM                         0x50C
#define  R_PCIE_L0P6P7P8PCM                       0x510
#define  R_PCIE_L0P8P9PCM                         0x514
#define  R_PCIE_L0P10PCM                          0x518
#define  R_PCIE_L0LFFS                            0x51C

#define  R_PCIE_PX16GP0P1PCM                      0x520
#define  R_PCIE_PX16GP1P2P3PCM                    0x524
#define  R_PCIE_PX16GP3P4PCM                      0x528
#define  R_PCIE_PX16GP5P6PCM                      0x52C
#define  R_PCIE_PX16GP6P7P8PCM                    0x530
#define  R_PCIE_PX16GP8P9PCM                      0x534
#define  R_PCIE_PX16GP10PCM                       0x538
#define  R_PCIE_PX16GLFFS                         0x53C

#define  R_PCIE_L0P0P1PCM                         0x500
#define  R_PCIE_L0P1P2P3PCM                       0x504
#define  R_PCIE_L0P3P4PCM                         0x508
#define  R_PCIE_L0P5P6PCM                         0x50C
#define  R_PCIE_L0P6P7P8PCM                       0x510
#define  R_PCIE_L0P8P9PCM                         0x514
#define  R_PCIE_L0P10PCM                          0x518
#define  R_PCIE_L0LFFS                            0x51C

#define  R_PCIE_IOMMUCTL                          0x580
 #define  B_PCIE_IOMMUCTL_CCTBM                   BIT6
 #define  B_PCIE_IOMMUCTL_CCTBM_OFFSET            6
 #define  B_PCIE_IOMMUCTL_PMRVSRPM                BIT5
 #define  B_PCIE_IOMMUCTL_PMRVSRPM_OFFSET         5
 #define  B_PCIE_IOMMUCTL_PMRVSUT                 BIT4
 #define  B_PCIE_IOMMUCTL_PMRVSUT_OFFSET          4
 #define  B_PCIE_IOMMUCTL_DMAVTDTP                BIT2
 #define  B_PCIE_IOMMUCTL_DMAVTDTP_OFFSET         2
 #define  B_PCIE_IOMMUCTL_DMAVTDTP_MASK           0xC
 #define  B_PCIE_IOMMUCTL_MSIVTDTP                BIT0
 #define  B_PCIE_IOMMUCTL_MSIVTDTP_OFFSET         0
 #define  B_PCIE_IOMMUCTL_MSIVTDTP_MASK           0x3

#define  R_PCIE_IOMMUCTL2                         0x584
 #define  B_PCIE_IOMMUCTL2_DMAFZLRA               BIT0
 #define  B_PCIE_IOMMUCTL2_DMAFZLRA_OFFSET        0
 #define  B_PCIE_IOMMUCTL2_DMAFZLRA_MASK          0xFFFFFFFF

#define  R_PCIE_IOMMUCTL3                         0x588
 #define  B_PCIE_IOMMUCTL3_HIOMMUFSB              BIT31
 #define  B_PCIE_IOMMUCTL3_HIOMMUFSB_OFFSET       31
 #define  B_PCIE_IOMMUCTL3_IOMMUPTEFATP           BIT30
 #define  B_PCIE_IOMMUCTL3_IOMMUPTEFATP_OFFSET    30
 #define  B_PCIE_IOMMUCTL3_TLBTPE                 BIT15
 #define  B_PCIE_IOMMUCTL3_TLBTPE_OFFSET          15
 #define  B_PCIE_IOMMUCTL3_TLBTPE_MASK            0x3FFF8000
 #define  B_PCIE_IOMMUCTL3_TLBDPE                 BIT0
 #define  B_PCIE_IOMMUCTL3_TLBDPE_OFFSET          0
 #define  B_PCIE_IOMMUCTL3_TLBDPE_MASK            0x7FFF

#define  R_PCIE_VTDBADDRH                         0x58C
 #define  B_PCIE_VTDBADDRH_PCIEVTDBARH            BIT0
 #define  B_PCIE_VTDBADDRH_PCIEVTDBARH_OFFSET     0
 #define  B_PCIE_VTDBADDRH_PCIEVTDBARH_MASK       0x7F

#define  R_PCIE_VTDBADDRL                         0x590
 #define  B_PCIE_VTDBADDRL_PCIEVTDBARL            BIT12
 #define  B_PCIE_VTDBADDRL_PCIEVTDBARL_OFFSET     12
 #define  B_PCIE_VTDBADDRL_PCIEVTDBARL_MASK       0xFFFFF000
 #define  B_PCIE_VTDBADDRL_PCIEVTDBAREN           BIT0
 #define  B_PCIE_VTDBADDRL_PCIEVTDBAREN_OFFSET    0

#define  R_PCIE_COCTL                             0x594
 #define  B_PCIE_COCTL_NPCLM                      BIT15
 #define  B_PCIE_COCTL_NPCLM_OFFSET               15
 #define  B_PCIE_COCTL_NPCLM_MASK                 0x18000
 #define  B_PCIE_COCTL_PCLM                       BIT13
 #define  B_PCIE_COCTL_PCLM_OFFSET                13
 #define  B_PCIE_COCTL_PCLM_MASK                  0x6000
 #define  B_PCIE_COCTL_MAGPARCD                   BIT12
 #define  B_PCIE_COCTL_MAGPARCD_OFFSET            12
 #define  B_PCIE_COCTL_ROAOP                      BIT11
 #define  B_PCIE_COCTL_ROAOP_OFFSET               11
 #define  B_PCIE_COCTL_CTE                        BIT10
 #define  B_PCIE_COCTL_CTE_OFFSET                 10
 #define  B_PCIE_COCTL_CT                         BIT2
 #define  B_PCIE_COCTL_CT_OFFSET                  2
 #define  B_PCIE_COCTL_CT_MASK                    0x3FC
 #define  B_PCIE_COCTL_DDCE                       BIT1
 #define  B_PCIE_COCTL_DDCE_OFFSET                1
 #define  B_PCIE_COCTL_PWCE                       BIT0
 #define  B_PCIE_COCTL_PWCE_OFFSET                0

#define  R_PCIE_ADVMCTRL                          0x5BC
 #define  B_PCIE_ADVMCTRL_F10BTSE                 BIT24
 #define  B_PCIE_ADVMCTRL_CCBE                    BIT23
 #define  B_PCIE_ADVMCTRL_CCBE_OFFSET             23
 #define  B_PCIE_ADVMCTRL_INRXL0CTRL              BIT22
 #define  B_PCIE_ADVMCTRL_INRXL0CTRL_OFFSET       22
 #define  B_PCIE_ADVMCTRL_ACCRM                   BIT21
 #define  B_PCIE_ADVMCTRL_ACCRM_OFFSET            21
 #define  B_PCIE_ADVMCTRL_EIOSDISDS               BIT20
 #define  B_PCIE_ADVMCTRL_EIOSDISDS_OFFSET        20
 #define  B_PCIE_ADVMCTRL_EIOSMASKRX              BIT19
 #define  B_PCIE_ADVMCTRL_EIOSMASKRX_OFFSET       19
 #define  B_PCIE_ADVMCTRL_PMREQCWC                BIT16
 #define  B_PCIE_ADVMCTRL_PMREQCWC_OFFSET         16
 #define  B_PCIE_ADVMCTRL_PMREQCWC_MASK           0x70000
 #define  B_PCIE_ADVMCTRL_RXL0DC                  BIT15
 #define  B_PCIE_ADVMCTRL_RXL0DC_OFFSET           15
 #define  B_PCIE_ADVMCTRL_CLKREQSM                BIT14
 #define  B_PCIE_ADVMCTRL_CLKREQSM_OFFSET         14
 #define  B_PCIE_ADVMCTRL_G3STFER                 BIT13
 #define  B_PCIE_ADVMCTRL_G3STFER_OFFSET          13
 #define  B_PCIE_ADVMCTRL_STLPRS                  BIT12
 #define  B_PCIE_ADVMCTRL_STLPRS_OFFSET           12
 #define  B_PCIE_ADVMCTRL_RRLLCL                  BIT11
 #define  B_PCIE_ADVMCTRL_RRLLCL_OFFSET           11
 #define  B_PCIE_ADVMCTRL_RLLG12R                 BIT10
 #define  B_PCIE_ADVMCTRL_RLLG12R_OFFSET          10
 #define  B_PCIE_ADVMCTRL_LMEQTS1E                BIT9
 #define  B_PCIE_ADVMCTRL_LMEQTS1E_OFFSET         9
 #define  B_PCIE_ADVMCTRL_LMEQCE                  BIT8
 #define  B_PCIE_ADVMCTRL_LMEQCE_OFFSET           8
 #define  B_PCIE_ADVMCTRL_PMREQBLKPGRSPT          BIT5
 #define  B_PCIE_ADVMCTRL_PMREQBLKPGRSPT_OFFSET   5
 #define  B_PCIE_ADVMCTRL_PMREQBLKPGRSPT_MASK     0xE0
 #define  B_PCIE_ADVMCTRL_RTD3PFETDIS             BIT4
 #define  B_PCIE_ADVMCTRL_RTD3PFETDIS_OFFSET      4
 #define  B_PCIE_ADVMCTRL_RTD3PERST               BIT3
 #define  B_PCIE_ADVMCTRL_RTD3PERST_OFFSET        3
 #define  B_PCIE_ADVMCTRL_PL1MIT                  BIT0
 #define  B_PCIE_ADVMCTRL_PL1MIT_OFFSET           0
 #define  B_PCIE_ADVMCTRL_PL1MIT_MASK             0x7

#define  R_PCIE_PGTHRES                           0x5C0
 #define  B_PCIE_PGTHRES_L1PGLTRTLSV              BIT29
 #define  B_PCIE_PGTHRES_L1PGLTRTLSV_OFFSET       29
 #define  B_PCIE_PGTHRES_L1PGLTRTLSV_MASK         0xE0000000
 #define  B_PCIE_PGTHRES_L1PGLTRTLV               BIT16
 #define  B_PCIE_PGTHRES_L1PGLTRTLV_OFFSET        16
 #define  B_PCIE_PGTHRES_L1PGLTRTLV_MASK          0x3FF0000
 #define  B_PCIE_PGTHRES_L1PGLTREN                BIT0
 #define  B_PCIE_PGTHRES_L1PGLTREN_OFFSET         0

#define  R_PCIE_IOMMUCTL4                         0x5C4
 #define  B_PCIE_IOMMUCTL4_VTDTFD                 BIT2
 #define  B_PCIE_IOMMUCTL4_VTDTFD_OFFSET          2
 #define  B_PCIE_IOMMUCTL4_PMRVSMIE               BIT1
 #define  B_PCIE_IOMMUCTL4_PMRVSMIE_OFFSET        1
 #define  B_PCIE_IOMMUCTL4_PMRVSCIE               BIT0
 #define  B_PCIE_IOMMUCTL4_PMRVSCIE_OFFSET        0

#define  R_PCIE_PMER                              0x5C8
 #define  B_PCIE_PMER_EPM                         BIT31
 #define  B_PCIE_PMER_EPM_OFFSET                  31
 #define  B_PCIE_PMER_PRS                         BIT0
 #define  B_PCIE_PMER_PRS_OFFSET                  0

#define  R_PCIE_PLMB                              0x5CC
 #define  B_PCIE_PLMB_PLMB                        BIT0
 #define  B_PCIE_PLMB_PLMB_OFFSET                 0
 #define  B_PCIE_PLMB_PLMB_MASK                   0xFFFFFFFF

#define  R_PCIE_PLML                              0x5D0
 #define  B_PCIE_PLML_PLML                        BIT0
 #define  B_PCIE_PLML_PLML_OFFSET                 0
 #define  B_PCIE_PLML_PLML_MASK                   0xFFFFFFFF

#define  R_PCIE_PHMB1                             0x5D4
 #define  B_PCIE_PHMB1_PHMB1                      BIT0
 #define  B_PCIE_PHMB1_PHMB1_OFFSET               0
 #define  B_PCIE_PHMB1_PHMB1_MASK                 0xFFFFFFFF

#define  R_PCIE_PHMB2                             0x5D8
 #define  B_PCIE_PHMB2_PHMB2                      BIT0
 #define  B_PCIE_PHMB2_PHMB2_OFFSET               0
 #define  B_PCIE_PHMB2_PHMB2_MASK                 0xFFFFFFFF

#define  R_PCIE_PHML1                             0x5DC
 #define  B_PCIE_PHML1_PHML1                      BIT0
 #define  B_PCIE_PHML1_PHML1_OFFSET               0
 #define  B_PCIE_PHML1_PHML1_MASK                 0xFFFFFFFF

#define  R_PCIE_PHML2                             0x5E0
 #define  B_PCIE_PHML2_PHML2                      BIT0
 #define  B_PCIE_PHML2_PHML2_OFFSET               0
 #define  B_PCIE_PHML2_PHML2_MASK                 0xFFFFFFFF

#define  R_PCIE_LSR                               0x5E4
 #define  B_PCIE_LSR_LANESTAT                     BIT0
 #define  B_PCIE_LSR_LANESTAT_OFFSET              0
 #define  B_PCIE_LSR_LANESTAT_MASK                0xFFFF

#define  R_PCIE_HWSNR                             0x5F0
 #define  B_PCIE_HWSNR_READY4PG                   BIT10
 #define  B_PCIE_HWSNR_READY4PG_OFFSET            10
 #define  B_PCIE_HWSNR_EEH                        BIT8
 #define  B_PCIE_HWSNR_EEH_OFFSET                 8
 #define  B_PCIE_HWSNR_EEH_MASK                   0x300
 #define  B_PCIE_HWSNR_REPW                       BIT4
 #define  B_PCIE_HWSNR_REPW_OFFSET                4
 #define  B_PCIE_HWSNR_REPW_MASK                  0xF0
 #define  B_PCIE_HWSNR_BEPW                       BIT0
 #define  B_PCIE_HWSNR_BEPW_OFFSET                0
 #define  B_PCIE_HWSNR_BEPW_MASK                  0xF
 #define  B_PCIE_HWSNR_BEPW_8_CLKS                0x5

#define  R_PCIE_PGCTRL                            0x5F4
 #define  B_PCIE_PGCTRL_PMREQBLKRSPT              BIT0
 #define  B_PCIE_PGCTRL_PMREQBLKRSPT_OFFSET       0
 #define  B_PCIE_PGCTRL_PMREQBLKRSPT_MASK         0x7
 #define  B_PCIE_PGCTRL_PMREQBLKRSPT_5MICRO_SEC   0x2

#define  R_PCIE_G0SAICPL                          0x630
 #define  B_PCIE_G0SAICPL_G0SAICPL                BIT0
 #define  B_PCIE_G0SAICPL_G0SAICPL_OFFSET         0
 #define  B_PCIE_G0SAICPL_G0SAICPL_MASK           0xFFFFFFFF

#define  R_PCIE_G0SAICPH                          0x634
 #define  B_PCIE_G0SAICPH_G0SAICPH                BIT0
 #define  B_PCIE_G0SAICPH_G0SAICPH_OFFSET         0
 #define  B_PCIE_G0SAICPH_G0SAICPH_MASK           0xFFFFFFFF

#define  R_PCIE_G0SAIWACPL                        0x638
 #define  B_PCIE_G0SAIWACPL_G0SAIWACPL            BIT0
 #define  B_PCIE_G0SAIWACPL_G0SAIWACPL_OFFSET     0
 #define  B_PCIE_G0SAIWACPL_G0SAIWACPL_MASK       0xFFFFFFFF

#define  R_PCIE_G0SAIWACPH                        0x63C
 #define  B_PCIE_G0SAIWACPH_G0SAIWACPH            BIT0
 #define  B_PCIE_G0SAIWACPH_G0SAIWACPH_OFFSET     0
 #define  B_PCIE_G0SAIWACPH_G0SAIWACPH_MASK       0xFFFFFFFF

#define  R_PCIE_G0SAIRACPL                        0x640
 #define  B_PCIE_G0SAIRACPL_G0SAIRACPL            BIT0
 #define  B_PCIE_G0SAIRACPL_G0SAIRACPL_OFFSET     0
 #define  B_PCIE_G0SAIRACPL_G0SAIRACPL_MASK       0xFFFFFFFF

#define  R_PCIE_G0SAIRACPH                        0x644
 #define  B_PCIE_G0SAIRACPH_G0SAIRACPH            BIT0
 #define  B_PCIE_G0SAIRACPH_G0SAIRACPH_OFFSET     0
 #define  B_PCIE_G0SAIRACPH_G0SAIRACPH_MASK       0xFFFFFFFF

#define  R_PCIE_G1SAICPL                          0x648
 #define  B_PCIE_G1SAICPL_G1SAICPL                BIT0
 #define  B_PCIE_G1SAICPL_G1SAICPL_OFFSET         0
 #define  B_PCIE_G1SAICPL_G1SAICPL_MASK           0xFFFFFFFF

#define  R_PCIE_G1SAICPH                          0x64C
 #define  B_PCIE_G1SAICPH_G1SAICPH                BIT0
 #define  B_PCIE_G1SAICPH_G1SAICPH_OFFSET         0
 #define  B_PCIE_G1SAICPH_G1SAICPH_MASK           0xFFFFFFFF

#define  R_PCIE_G1SAIWACPL                        0x650
 #define  B_PCIE_G1SAIWACPL_G1SAIWACPL            BIT0
 #define  B_PCIE_G1SAIWACPL_G1SAIWACPL_OFFSET     0
 #define  B_PCIE_G1SAIWACPL_G1SAIWACPL_MASK       0xFFFFFFFF

#define  R_PCIE_G1SAIWACPH                        0x654
 #define  B_PCIE_G1SAIWACPH_G1SAIWACPH            BIT0
 #define  B_PCIE_G1SAIWACPH_G1SAIWACPH_OFFSET     0
 #define  B_PCIE_G1SAIWACPH_G1SAIWACPH_MASK       0xFFFFFFFF

#define  R_PCIE_G1SAIRACPL                        0x658
 #define  B_PCIE_G1SAIRACPL_G1SAIRACPL            BIT0
 #define  B_PCIE_G1SAIRACPL_G1SAIRACPL_OFFSET     0
 #define  B_PCIE_G1SAIRACPL_G1SAIRACPL_MASK       0xFFFFFFFF

#define  R_PCIE_G1SAIRACPH                        0x65C
 #define  B_PCIE_G1SAIRACPH_G1SAIRACPH            BIT0
 #define  B_PCIE_G1SAIRACPH_G1SAIRACPH_OFFSET     0
 #define  B_PCIE_G1SAIRACPH_G1SAIRACPH_MASK       0xFFFFFFFF

#define  R_PCIE_G2SAICPL                          0x660
 #define  B_PCIE_G2SAICPL_G2SAICPL                BIT0
 #define  B_PCIE_G2SAICPL_G2SAICPL_OFFSET         0
 #define  B_PCIE_G2SAICPL_G2SAICPL_MASK           0xFFFFFFFF

#define  R_PCIE_G2SAICPH                          0x664
 #define  B_PCIE_G2SAICPH_G2SAICPH                BIT0
 #define  B_PCIE_G2SAICPH_G2SAICPH_OFFSET         0
 #define  B_PCIE_G2SAICPH_G2SAICPH_MASK           0xFFFFFFFF

#define  R_PCIE_G2SAIWACPL                        0x668
 #define  B_PCIE_G2SAIWACPL_G2SAIWACPL            BIT0
 #define  B_PCIE_G2SAIWACPL_G2SAIWACPL_OFFSET     0
 #define  B_PCIE_G2SAIWACPL_G2SAIWACPL_MASK       0xFFFFFFFF

#define  R_PCIE_G2SAIWACPH                        0x66C
 #define  B_PCIE_G2SAIWACPH_G2SAIWACPH            BIT0
 #define  B_PCIE_G2SAIWACPH_G2SAIWACPH_OFFSET     0
 #define  B_PCIE_G2SAIWACPH_G2SAIWACPH_MASK       0xFFFFFFFF

#define  R_PCIE_G2SAIRACPL                        0x670
 #define  B_PCIE_G2SAIRACPL_G2SAIRACPL            BIT0
 #define  B_PCIE_G2SAIRACPL_G2SAIRACPL_OFFSET     0
 #define  B_PCIE_G2SAIRACPL_G2SAIRACPL_MASK       0xFFFFFFFF

#define  R_PCIE_G2SAIRACPH                        0x674
 #define  B_PCIE_G2SAIRACPH_G2SAIRACPH            BIT0
 #define  B_PCIE_G2SAIRACPH_G2SAIRACPH_OFFSET     0
 #define  B_PCIE_G2SAIRACPH_G2SAIRACPH_MASK       0xFFFFFFFF

#define  R_PCIE_G3SAICPL                          0x678
 #define  B_PCIE_G3SAICPL_G3SAICPL                BIT0
 #define  B_PCIE_G3SAICPL_G3SAICPL_OFFSET         0
 #define  B_PCIE_G3SAICPL_G3SAICPL_MASK           0xFFFFFFFF

#define  R_PCIE_G3SAICPH                          0x67C
 #define  B_PCIE_G3SAICPH_G3SAICPH                BIT0
 #define  B_PCIE_G3SAICPH_G3SAICPH_OFFSET         0
 #define  B_PCIE_G3SAICPH_G3SAICPH_MASK           0xFFFFFFFF

#define  R_PCIE_G3SAIWACPL                        0x680
 #define  B_PCIE_G3SAIWACPL_G3SAIWACPL            BIT0
 #define  B_PCIE_G3SAIWACPL_G3SAIWACPL_OFFSET     0
 #define  B_PCIE_G3SAIWACPL_G3SAIWACPL_MASK       0xFFFFFFFF

#define  R_PCIE_G3SAIWACPH                        0x684
 #define  B_PCIE_G3SAIWACPH_G3SAIWACPH            BIT0
 #define  B_PCIE_G3SAIWACPH_G3SAIWACPH_OFFSET     0
 #define  B_PCIE_G3SAIWACPH_G3SAIWACPH_MASK       0xFFFFFFFF

#define  R_PCIE_G3SAIRACPL                        0x688
 #define  B_PCIE_G3SAIRACPL_G3SAIRACPL            BIT0
 #define  B_PCIE_G3SAIRACPL_G3SAIRACPL_OFFSET     0
 #define  B_PCIE_G3SAIRACPL_G3SAIRACPL_MASK       0xFFFFFFFF

#define  R_PCIE_G3SAIRACPH                        0x68C
 #define  B_PCIE_G3SAIRACPH_G3SAIRACPH            BIT0
 #define  B_PCIE_G3SAIRACPH_G3SAIRACPH_OFFSET     0
 #define  B_PCIE_G3SAIRACPH_G3SAIRACPH_MASK       0xFFFFFFFF

#define  R_PCIE_GDR                               0x690
 #define  B_PCIE_GDR_LDVWMDESTID                  BIT23
 #define  B_PCIE_GDR_LDVWMDESTID_OFFSET           23
 #define  B_PCIE_GDR_LDVWMDESTID_MASK             0x7F800000
 #define  B_PCIE_GDR_LDVWMBITLOC                  BIT20
 #define  B_PCIE_GDR_LDVWMBITLOC_OFFSET           20
 #define  B_PCIE_GDR_LDVWMBITLOC_MASK             0x700000
 #define  B_PCIE_GDR_LDVWMIDX                     BIT12
 #define  B_PCIE_GDR_LDVWMIDX_OFFSET              12
 #define  B_PCIE_GDR_LDVWMIDX_MASK                0xFF000
 #define  B_PCIE_GDR_VGPIOALDE                    BIT11
 #define  B_PCIE_GDR_VGPIOALDE_OFFSET             11

#define  R_PCIE_ACRG3                             0x6CC
 #define  B_PCIE_ACRG3_VSPFB                      BIT26
 #define  B_PCIE_ACRG3_VSPFB_OFFSET               26
 #define  B_PCIE_ACRG3_VSPFSCG                    BIT25
 #define  B_PCIE_ACRG3_VSPFSCG_OFFSET             25
 #define  B_PCIE_ACRG3_VRXCDDD                    BIT24
 #define  B_PCIE_ACRG3_VRXCDDD_OFFSET             24
 #define  B_PCIE_ACRG3_CPGWAKECTRL                BIT22
 #define  B_PCIE_ACRG3_CPGWAKECTRL_OFFSET         22
 #define  B_PCIE_ACRG3_CPGWAKECTRL_MASK           0xC00000
 #define  V_PCIE_ACRG3_CPGWAKECTRL                0x2
 #define  B_PCIE_ACRG3_CBGM                       BIT21
 #define  B_PCIE_ACRG3_CBGM_OFFSET                21
 #define  B_PCIE_ACRG3_SASV                       BIT20
 #define  B_PCIE_ACRG3_SASV_OFFSET                20
 #define  B_PCIE_ACRG3_PASV                       BIT19
 #define  B_PCIE_ACRG3_PASV_OFFSET                19
 #define  B_PCIE_ACRG3_PPTMTMUCFE                 BIT18
 #define  B_PCIE_ACRG3_PPTMTMUCFE_OFFSET          18
 #define  B_PCIE_ACRG3_PPTMTMUCF                  BIT14
 #define  B_PCIE_ACRG3_PPTMTMUCF_OFFSET           14
 #define  B_PCIE_ACRG3_PPTMTMUCF_MASK             0x3C000
 #define  B_PCIE_ACRG3_LNRSTCTL                   BIT11
 #define  B_PCIE_ACRG3_LNRSTCTL_OFFSET            11
 #define  B_PCIE_ACRG3_LNRSTCTL_MASK              0x3800
 #define  B_PCIE_ACRG3_TXACC                      BIT8
 #define  B_PCIE_ACRG3_TXACC_OFFSET               8
 #define  B_PCIE_ACRG3_TXACC_MASK                 0x300
 #define  B_PCIE_ACRG3_LTSMSTATEOSC               BIT2
 #define  B_PCIE_ACRG3_LTSMSTATEOSC_OFFSET        2
 #define  B_PCIE_ACRG3_LTSMSTATEOSC_MASK          0x7C

#define  R_PCIE_TBTPTMBCTRL                       0x6D0
 #define  B_PCIE_TBTPTMBCTRL_TL                   BIT21
 #define  B_PCIE_TBTPTMBCTRL_TL_OFFSET            21
 #define  B_PCIE_TBTPTMBCTRL_TL_MASK              0x3E00000
 #define  B_PCIE_TBTPTMBCTRL_TMUSC                BIT16
 #define  B_PCIE_TBTPTMBCTRL_TMUSC_OFFSET         16
 #define  B_PCIE_TBTPTMBCTRL_TMUSC_MASK           0x1F0000
 #define  B_PCIE_TBTPTMBCTRL_CP                   BIT8
 #define  B_PCIE_TBTPTMBCTRL_CP_OFFSET            8
 #define  B_PCIE_TBTPTMBCTRL_CP_MASK              0xFF00
 #define  B_PCIE_TBTPTMBCTRL_FS                   BIT3
 #define  B_PCIE_TBTPTMBCTRL_FS_OFFSET            3
 #define  B_PCIE_TBTPTMBCTRL_FS_MASK              0xF8
 #define  B_PCIE_TBTPTMBCTRL_FIE                  BIT2
 #define  B_PCIE_TBTPTMBCTRL_FIE_OFFSET           2
 #define  B_PCIE_TBTPTMBCTRL_PME                  BIT1
 #define  B_PCIE_TBTPTMBCTRL_PME_OFFSET           1
 #define  B_PCIE_TBTPTMBCTRL_PTMBE                BIT0
 #define  B_PCIE_TBTPTMBCTRL_PTMBE_OFFSET         0

#define  R_PCIE_DPCECH                            0xA00
 #define  B_PCIE_DPCECH_NCO                       BIT20
 #define  B_PCIE_DPCECH_NCO_OFFSET                20
 #define  B_PCIE_DPCECH_NCO_MASK                  0xFFF00000
 #define  B_PCIE_DPCECH_CV                        BIT16
 #define  B_PCIE_DPCECH_CV_OFFSET                 16
 #define  B_PCIE_DPCECH_CV_MASK                   0xF0000
 #define  V_PCIE_DPCECH_CV                        1
 #define  B_PCIE_DPCECH_CID                       BIT0
 #define  B_PCIE_DPCECH_CID_OFFSET                0
 #define  B_PCIE_DPCECH_CID_MASK                  0xFFFF

#define  R_PCIE_DPCCAPR                           0xA04
 #define  B_PCIE_DPCCAPR_DLAECSS                  BIT12
 #define  B_PCIE_DPCCAPR_DLAECSS_OFFSET           12
 #define  B_PCIE_DPCCAPR_RPPIOLS                  BIT8
 #define  B_PCIE_DPCCAPR_RPPIOLS_OFFSET           8
 #define  B_PCIE_DPCCAPR_RPPIOLS_MASK             0xF00
 #define  B_PCIE_DPCCAPR_DPCSTS                   BIT7
 #define  B_PCIE_DPCCAPR_DPCSTS_OFFSET            7
 #define  B_PCIE_DPCCAPR_PTLPEBS                  BIT6
 #define  B_PCIE_DPCCAPR_PTLPEBS_OFFSET           6
 #define  B_PCIE_DPCCAPR_RPEFDPC                  BIT5
 #define  B_PCIE_DPCCAPR_RPEFDPC_OFFSET           5
 #define  B_PCIE_DPCCAPR_DPCIMN                   BIT0
 #define  B_PCIE_DPCCAPR_DPCIMN_OFFSET            0
 #define  B_PCIE_DPCCAPR_DPCIMN_MASK              0x1F

#define  R_PCIE_DPCCTLR                           0xA06
 #define  B_PCIE_DPCCTLR_DLAECE                   BIT7
 #define  B_PCIE_DPCCTLR_DLAECE_OFFSET            7
 #define  B_PCIE_DPCCTLR_DPCST                    BIT6
 #define  B_PCIE_DPCCTLR_DPCST_OFFSET             6
 #define  B_PCIE_DPCCTLR_PTLPEBE                  BIT5
 #define  B_PCIE_DPCCTLR_PTLPEBE_OFFSET           5
 #define  B_PCIE_DPCCTLR_DPCECE                   BIT4
 #define  B_PCIE_DPCCTLR_DPCECE_OFFSET            4
 #define  B_PCIE_DPCCTLR_DPCIE                    BIT3
 #define  B_PCIE_DPCCTLR_DPCIE_OFFSET             3
 #define  B_PCIE_DPCCTLR_DPCCC                    BIT2
 #define  B_PCIE_DPCCTLR_DPCCC_OFFSET             2
 #define  B_PCIE_DPCCTLR_DPCTE                    BIT0
 #define  B_PCIE_DPCCTLR_DPCTE_OFFSET             0
 #define  B_PCIE_DPCCTLR_DPCTE_MASK               0x3

#define  R_PCIE_DPCSR                             0xA08
 #define  B_PCIE_DPCSR_RPPIOFEP                   BIT8
 #define  B_PCIE_DPCSR_RPPIOFEP_OFFSET            8
 #define  B_PCIE_DPCSR_RPPIOFEP_MASK              0x1F00
 #define  B_PCIE_DPCSR_DPCTE                      BIT5
 #define  B_PCIE_DPCSR_DPCTE_OFFSET               5
 #define  B_PCIE_DPCSR_DPCTE_MASK                 0x60
 #define  B_PCIE_DPCSR_DPCRPB                     BIT4
 #define  B_PCIE_DPCSR_DPCRPB_OFFSET              4
 #define  B_PCIE_DPCSR_DPCIS                      BIT3
 #define  B_PCIE_DPCSR_DPCIS_OFFSET               3
 #define  B_PCIE_DPCSR_DPCTR                      BIT1
 #define  B_PCIE_DPCSR_DPCTR_OFFSET               1
 #define  B_PCIE_DPCSR_DPCTR_MASK                 0x6
 #define  B_PCIE_DPCSR_DPCTS                      BIT0
 #define  B_PCIE_DPCSR_DPCTS_OFFSET               0

#define  R_PCIE_DPCESIDR                          0xA0A
 #define  B_PCIE_DPCESIDR_DPCESID                 BIT0
 #define  B_PCIE_DPCESIDR_DPCESID_OFFSET          0
 #define  B_PCIE_DPCESIDR_DPCESID_MASK            0xFFFF

#define  R_PCIE_RPPIOSR                           0xA0C
 #define  B_PCIE_RPPIOSR_MCTS                     BIT18
 #define  B_PCIE_RPPIOSR_MCTS_OFFSET              18
 #define  B_PCIE_RPPIOSR_MCACS                    BIT17
 #define  B_PCIE_RPPIOSR_MCACS_OFFSET             17
 #define  B_PCIE_RPPIOSR_MURCS                    BIT16
 #define  B_PCIE_RPPIOSR_MURCS_OFFSET             16
 #define  B_PCIE_RPPIOSR_IOCTS                    BIT10
 #define  B_PCIE_RPPIOSR_IOCTS_OFFSET             10
 #define  B_PCIE_RPPIOSR_IOCACS                   BIT9
 #define  B_PCIE_RPPIOSR_IOCACS_OFFSET            9
 #define  B_PCIE_RPPIOSR_IOURCS                   BIT8
 #define  B_PCIE_RPPIOSR_IOURCS_OFFSET            8
 #define  B_PCIE_RPPIOSR_CCTS                     BIT2
 #define  B_PCIE_RPPIOSR_CCTS_OFFSET              2
 #define  B_PCIE_RPPIOSR_CCACS                    BIT1
 #define  B_PCIE_RPPIOSR_CCACS_OFFSET             1
 #define  B_PCIE_RPPIOSR_CURCS                    BIT0
 #define  B_PCIE_RPPIOSR_CURCS_OFFSET             0

#define  R_PCIE_RPPIOMR                           0xA10
 #define  B_PCIE_RPPIOMR_MCTM                     BIT18
 #define  B_PCIE_RPPIOMR_MCTM_OFFSET              18
 #define  B_PCIE_RPPIOMR_MCACM                    BIT17
 #define  B_PCIE_RPPIOMR_MCACM_OFFSET             17
 #define  B_PCIE_RPPIOMR_MURCM                    BIT16
 #define  B_PCIE_RPPIOMR_MURCM_OFFSET             16
 #define  B_PCIE_RPPIOMR_IOCTM                    BIT10
 #define  B_PCIE_RPPIOMR_IOCTM_OFFSET             10
 #define  B_PCIE_RPPIOMR_IOCACM                   BIT9
 #define  B_PCIE_RPPIOMR_IOCACM_OFFSET            9
 #define  B_PCIE_RPPIOMR_IOURCM                   BIT8
 #define  B_PCIE_RPPIOMR_IOURCM_OFFSET            8
 #define  B_PCIE_RPPIOMR_CCTM                     BIT2
 #define  B_PCIE_RPPIOMR_CCTM_OFFSET              2
 #define  B_PCIE_RPPIOMR_CCACM                    BIT1
 #define  B_PCIE_RPPIOMR_CCACM_OFFSET             1
 #define  B_PCIE_RPPIOMR_CURCM                    BIT0
 #define  B_PCIE_RPPIOMR_CURCM_OFFSET             0

#define  R_PCIE_RPPIOVR                           0xA14
 #define  B_PCIE_RPPIOVR_MCTSV                    BIT18
 #define  B_PCIE_RPPIOVR_MCTSV_OFFSET             18
 #define  B_PCIE_RPPIOVR_MCACSV                   BIT17
 #define  B_PCIE_RPPIOVR_MCACSV_OFFSET            17
 #define  B_PCIE_RPPIOVR_MURCSV                   BIT16
 #define  B_PCIE_RPPIOVR_MURCSV_OFFSET            16
 #define  B_PCIE_RPPIOVR_IOCTSV                   BIT10
 #define  B_PCIE_RPPIOVR_IOCTSV_OFFSET            10
 #define  B_PCIE_RPPIOVR_IOCACSV                  BIT9
 #define  B_PCIE_RPPIOVR_IOCACSV_OFFSET           9
 #define  B_PCIE_RPPIOVR_IOURCSV                  BIT8
 #define  B_PCIE_RPPIOVR_IOURCSV_OFFSET           8
 #define  B_PCIE_RPPIOVR_CCTSV                    BIT2
 #define  B_PCIE_RPPIOVR_CCTSV_OFFSET             2
 #define  B_PCIE_RPPIOVR_CCACSV                   BIT1
 #define  B_PCIE_RPPIOVR_CCACSV_OFFSET            1
 #define  B_PCIE_RPPIOVR_CURCSV                   BIT0
 #define  B_PCIE_RPPIOVR_CURCSV_OFFSET            0

#define  R_PCIE_RPPIOSER                          0xA18
 #define  B_PCIE_RPPIOSER_MCTSE                   BIT18
 #define  B_PCIE_RPPIOSER_MCTSE_OFFSET            18
 #define  B_PCIE_RPPIOSER_MCACSE                  BIT17
 #define  B_PCIE_RPPIOSER_MCACSE_OFFSET           17
 #define  B_PCIE_RPPIOSER_MURCSE                  BIT16
 #define  B_PCIE_RPPIOSER_MURCSE_OFFSET           16
 #define  B_PCIE_RPPIOSER_IOCTSE                  BIT10
 #define  B_PCIE_RPPIOSER_IOCTSE_OFFSET           10
 #define  B_PCIE_RPPIOSER_IOCACSE                 BIT9
 #define  B_PCIE_RPPIOSER_IOCACSE_OFFSET          9
 #define  B_PCIE_RPPIOSER_IOURCSE                 BIT8
 #define  B_PCIE_RPPIOSER_IOURCSE_OFFSET          8
 #define  B_PCIE_RPPIOSER_CCTSE                   BIT2
 #define  B_PCIE_RPPIOSER_CCTSE_OFFSET            2
 #define  B_PCIE_RPPIOSER_CCACSE                  BIT1
 #define  B_PCIE_RPPIOSER_CCACSE_OFFSET           1
 #define  B_PCIE_RPPIOSER_CURCSE                  BIT0
 #define  B_PCIE_RPPIOSER_CURCSE_OFFSET           0

#define  R_PCIE_RPPIOER                           0xA1C
 #define  B_PCIE_RPPIOER_MCTE                     BIT18
 #define  B_PCIE_RPPIOER_MCTE_OFFSET              18
 #define  B_PCIE_RPPIOER_MCACE                    BIT17
 #define  B_PCIE_RPPIOER_MCACE_OFFSET             17
 #define  B_PCIE_RPPIOER_MURCE                    BIT16
 #define  B_PCIE_RPPIOER_MURCE_OFFSET             16
 #define  B_PCIE_RPPIOER_IOCTE                    BIT10
 #define  B_PCIE_RPPIOER_IOCTE_OFFSET             10
 #define  B_PCIE_RPPIOER_IOCACE                   BIT9
 #define  B_PCIE_RPPIOER_IOCACE_OFFSET            9
 #define  B_PCIE_RPPIOER_IOURCE                   BIT8
 #define  B_PCIE_RPPIOER_IOURCE_OFFSET            8
 #define  B_PCIE_RPPIOER_CCTE                     BIT2
 #define  B_PCIE_RPPIOER_CCTE_OFFSET              2
 #define  B_PCIE_RPPIOER_CCACE                    BIT1
 #define  B_PCIE_RPPIOER_CCACE_OFFSET             1
 #define  B_PCIE_RPPIOER_CURCE                    BIT0
 #define  B_PCIE_RPPIOER_CURCE_OFFSET             0

#define  R_PCIE_RPPIOHLR_DW1                      0xA20
 #define  B_PCIE_RPPIOHLDW1_DW1                   BIT0
 #define  B_PCIE_RPPIOHLDW1_DW1_OFFSET            0
 #define  B_PCIE_RPPIOHLDW1_DW1_MASK              0xFFFFFFFF

#define  R_PCIE_RPPIOHLR_DW2                      0xA24
 #define  B_PCIE_RPPIOHLDW2_DW2                   BIT0
 #define  B_PCIE_RPPIOHLDW2_DW2_OFFSET            0
 #define  B_PCIE_RPPIOHLDW2_DW2_MASK              0xFFFFFFFF

#define  R_PCIE_RPPIOHLR_DW3                      0xA28
 #define  B_PCIE_RPPIOHLDW3_DW3                   BIT0
 #define  B_PCIE_RPPIOHLDW3_DW3_OFFSET            0
 #define  B_PCIE_RPPIOHLDW3_DW3_MASK              0xFFFFFFFF

#define  R_PCIE_RPPIOHLR_DW4                      0xA2C
 #define  B_PCIE_RPPIOHLDW4_DW4                   BIT0
 #define  B_PCIE_RPPIOHLDW4_DW4_OFFSET            0
 #define  B_PCIE_RPPIOHLDW4_DW4_MASK              0xFFFFFFFF

#define  R_PCIE_SPEECH                            0xA30
 #define  B_PCIE_SPEECH_NCO                       BIT20
 #define  B_PCIE_SPEECH_NCO_OFFSET                20
 #define  B_PCIE_SPEECH_NCO_MASK                  0xFFF00000
 #define  B_PCIE_SPEECH_CV                        BIT16
 #define  B_PCIE_SPEECH_CV_OFFSET                 16
 #define  B_PCIE_SPEECH_CV_MASK                   0xF0000
 #define  V_PCIE_SPEECH_CV                        0x1
 #define  B_PCIE_SPEECH_PCIEECID                  BIT0
 #define  B_PCIE_SPEECH_PCIEECID_OFFSET           0
 #define  B_PCIE_SPEECH_PCIEECID_MASK             0xFFFF

#define  R_PCIE_LCTL3                             0xA34
 #define  B_PCIE_LCTL3_ELSOSGV                    BIT9
 #define  B_PCIE_LCTL3_ELSOSGV_OFFSET             9
 #define  B_PCIE_LCTL3_ELSOSGV_MASK               0xFE00
 #define  B_PCIE_LCTL3_LERIE                      BIT1
 #define  B_PCIE_LCTL3_LERIE_OFFSET               1
 #define  B_PCIE_LCTL3_PE                         BIT0
 #define  B_PCIE_LCTL3_PE_OFFSET                  0

#define  R_PCIE_LES                               0xA38
 #define  B_PCIE_LES_L15ES                        BIT15
 #define  B_PCIE_LES_L15ES_OFFSET                 15
 #define  B_PCIE_LES_L14ES                        BIT14
 #define  B_PCIE_LES_L14ES_OFFSET                 14
 #define  B_PCIE_LES_L13ES                        BIT13
 #define  B_PCIE_LES_L13ES_OFFSET                 13
 #define  B_PCIE_LES_L12ES                        BIT12
 #define  B_PCIE_LES_L12ES_OFFSET                 12
 #define  B_PCIE_LES_L11ES                        BIT11
 #define  B_PCIE_LES_L11ES_OFFSET                 11
 #define  B_PCIE_LES_L10ES                        BIT10
 #define  B_PCIE_LES_L10ES_OFFSET                 10
 #define  B_PCIE_LES_L9ES                         BIT9
 #define  B_PCIE_LES_L9ES_OFFSET                  9
 #define  B_PCIE_LES_L8ES                         BIT8
 #define  B_PCIE_LES_L8ES_OFFSET                  8
 #define  B_PCIE_LES_L7ES                         BIT7
 #define  B_PCIE_LES_L7ES_OFFSET                  7
 #define  B_PCIE_LES_L6ES                         BIT6
 #define  B_PCIE_LES_L6ES_OFFSET                  6
 #define  B_PCIE_LES_L5ES                         BIT5
 #define  B_PCIE_LES_L5ES_OFFSET                  5
 #define  B_PCIE_LES_L4ES                         BIT4
 #define  B_PCIE_LES_L4ES_OFFSET                  4
 #define  B_PCIE_LES_L3ES                         BIT3
 #define  B_PCIE_LES_L3ES_OFFSET                  3
 #define  B_PCIE_LES_L2ES                         BIT2
 #define  B_PCIE_LES_L2ES_OFFSET                  2
 #define  B_PCIE_LES_L1ES                         BIT1
 #define  B_PCIE_LES_L1ES_OFFSET                  1
 #define  B_PCIE_LES_L0ES                         BIT0
 #define  B_PCIE_LES_L0ES_OFFSET                  0

#define  R_PCIE_L01EC                             0xA3C
 #define  B_PCIE_L01EC_UPL1RPH                    BIT28
 #define  B_PCIE_L01EC_UPL1RPH_OFFSET             28
 #define  B_PCIE_L01EC_UPL1RPH_MASK               0x70000000
 #define  B_PCIE_L01EC_UPL1TP                     BIT24
 #define  B_PCIE_L01EC_UPL1TP_OFFSET              24
 #define  B_PCIE_L01EC_UPL1TP_MASK                0xF000000
 #define  B_PCIE_L01EC_DPL1RPH                    BIT20
 #define  B_PCIE_L01EC_DPL1RPH_OFFSET             20
 #define  B_PCIE_L01EC_DPL1RPH_MASK               0x700000
 #define  B_PCIE_L01EC_DPL1TP                     BIT16
 #define  B_PCIE_L01EC_DPL1TP_OFFSET              16
 #define  B_PCIE_L01EC_DPL1TP_MASK                0xF0000
 #define  B_PCIE_L01EC_UPL0RPH                    BIT12
 #define  B_PCIE_L01EC_UPL0RPH_OFFSET             12
 #define  B_PCIE_L01EC_UPL0RPH_MASK               0x7000
 #define  B_PCIE_L01EC_UPL0TP                     BIT8
 #define  B_PCIE_L01EC_UPL0TP_OFFSET              8
 #define  B_PCIE_L01EC_UPL0TP_MASK                0xF00
 #define  B_PCIE_L01EC_DPL0RPH                    BIT4
 #define  B_PCIE_L01EC_DPL0RPH_OFFSET             4
 #define  B_PCIE_L01EC_DPL0RPH_MASK               0x70
 #define  B_PCIE_L01EC_DPL0TP                     BIT0
 #define  B_PCIE_L01EC_DPL0TP_OFFSET              0
 #define  B_PCIE_L01EC_DPL0TP_MASK                0xF

#define  R_PCIE_L23EC                             0xA40
 #define  B_PCIE_L23EC_UPL3RPH                    BIT28
 #define  B_PCIE_L23EC_UPL3RPH_OFFSET             28
 #define  B_PCIE_L23EC_UPL3RPH_MASK               0x70000000
 #define  B_PCIE_L23EC_UPL3TP                     BIT24
 #define  B_PCIE_L23EC_UPL3TP_OFFSET              24
 #define  B_PCIE_L23EC_UPL3TP_MASK                0xF000000
 #define  B_PCIE_L23EC_DPL3RPH                    BIT20
 #define  B_PCIE_L23EC_DPL3RPH_OFFSET             20
 #define  B_PCIE_L23EC_DPL3RPH_MASK               0x700000
 #define  B_PCIE_L23EC_DPL3TP                     BIT16
 #define  B_PCIE_L23EC_DPL3TP_OFFSET              16
 #define  B_PCIE_L23EC_DPL3TP_MASK                0xF0000
 #define  B_PCIE_L23EC_UPL2RPH                    BIT12
 #define  B_PCIE_L23EC_UPL2RPH_OFFSET             12
 #define  B_PCIE_L23EC_UPL2RPH_MASK               0x7000
 #define  B_PCIE_L23EC_UPL2TP                     BIT8
 #define  B_PCIE_L23EC_UPL2TP_OFFSET              8
 #define  B_PCIE_L23EC_UPL2TP_MASK                0xF00
 #define  B_PCIE_L23EC_DPL2RPH                    BIT4
 #define  B_PCIE_L23EC_DPL2RPH_OFFSET             4
 #define  B_PCIE_L23EC_DPL2RPH_MASK               0x70
 #define  B_PCIE_L23EC_DPL2TP                     BIT0
 #define  B_PCIE_L23EC_DPL2TP_OFFSET              0
 #define  B_PCIE_L23EC_DPL2TP_MASK                0xF

#define  R_PCIE_L45EC                             0xA44
 #define  B_PCIE_L45EC_UPL5RPH                    BIT28
 #define  B_PCIE_L45EC_UPL5RPH_OFFSET             28
 #define  B_PCIE_L45EC_UPL5RPH_MASK               0x70000000
 #define  B_PCIE_L45EC_UPL5TP                     BIT24
 #define  B_PCIE_L45EC_UPL5TP_OFFSET              24
 #define  B_PCIE_L45EC_UPL5TP_MASK                0xF000000
 #define  B_PCIE_L45EC_DPL5RPH                    BIT20
 #define  B_PCIE_L45EC_DPL5RPH_OFFSET             20
 #define  B_PCIE_L45EC_DPL5RPH_MASK               0x700000
 #define  B_PCIE_L45EC_DPL5TP                     BIT16
 #define  B_PCIE_L45EC_DPL5TP_OFFSET              16
 #define  B_PCIE_L45EC_DPL5TP_MASK                0xF0000
 #define  B_PCIE_L45EC_UPL4RPH                    BIT12
 #define  B_PCIE_L45EC_UPL4RPH_OFFSET             12
 #define  B_PCIE_L45EC_UPL4RPH_MASK               0x7000
 #define  B_PCIE_L45EC_UPL4TP                     BIT8
 #define  B_PCIE_L45EC_UPL4TP_OFFSET              8
 #define  B_PCIE_L45EC_UPL4TP_MASK                0xF00
 #define  B_PCIE_L45EC_DPL4RPH                    BIT4
 #define  B_PCIE_L45EC_DPL4RPH_OFFSET             4
 #define  B_PCIE_L45EC_DPL4RPH_MASK               0x70
 #define  B_PCIE_L45EC_DPL4TP                     BIT0
 #define  B_PCIE_L45EC_DPL4TP_OFFSET              0
 #define  B_PCIE_L45EC_DPL4TP_MASK                0xF

#define  R_PCIE_L67EC                             0xA48
 #define  B_PCIE_L67EC_UPL7RPH                    BIT28
 #define  B_PCIE_L67EC_UPL7RPH_OFFSET             28
 #define  B_PCIE_L67EC_UPL7RPH_MASK               0x70000000
 #define  B_PCIE_L67EC_UPL7TP                     BIT24
 #define  B_PCIE_L67EC_UPL7TP_OFFSET              24
 #define  B_PCIE_L67EC_UPL7TP_MASK                0xF000000
 #define  B_PCIE_L67EC_DPL7RPH                    BIT20
 #define  B_PCIE_L67EC_DPL7RPH_OFFSET             20
 #define  B_PCIE_L67EC_DPL7RPH_MASK               0x700000
 #define  B_PCIE_L67EC_DPL7TP                     BIT16
 #define  B_PCIE_L67EC_DPL7TP_OFFSET              16
 #define  B_PCIE_L67EC_DPL7TP_MASK                0xF0000
 #define  B_PCIE_L67EC_UPL6RPH                    BIT12
 #define  B_PCIE_L67EC_UPL6RPH_OFFSET             12
 #define  B_PCIE_L67EC_UPL6RPH_MASK               0x7000
 #define  B_PCIE_L67EC_UPL6TP                     BIT8
 #define  B_PCIE_L67EC_UPL6TP_OFFSET              8
 #define  B_PCIE_L67EC_UPL6TP_MASK                0xF00
 #define  B_PCIE_L67EC_DPL6RPH                    BIT4
 #define  B_PCIE_L67EC_DPL6RPH_OFFSET             4
 #define  B_PCIE_L67EC_DPL6RPH_MASK               0x70
 #define  B_PCIE_L67EC_DPL6TP                     BIT0
 #define  B_PCIE_L67EC_DPL6TP_OFFSET              0
 #define  B_PCIE_L67EC_DPL6TP_MASK                0xF

#define  R_PCIE_L89EC                             0xA4C
 #define  B_PCIE_L89EC_UPL9RPH                    BIT28
 #define  B_PCIE_L89EC_UPL9RPH_OFFSET             28
 #define  B_PCIE_L89EC_UPL9RPH_MASK               0x70000000
 #define  B_PCIE_L89EC_UPL9TP                     BIT24
 #define  B_PCIE_L89EC_UPL9TP_OFFSET              24
 #define  B_PCIE_L89EC_UPL9TP_MASK                0xF000000
 #define  B_PCIE_L89EC_DPL9RPH                    BIT20
 #define  B_PCIE_L89EC_DPL9RPH_OFFSET             20
 #define  B_PCIE_L89EC_DPL9RPH_MASK               0x700000
 #define  B_PCIE_L89EC_DPL9TP                     BIT16
 #define  B_PCIE_L89EC_DPL9TP_OFFSET              16
 #define  B_PCIE_L89EC_DPL9TP_MASK                0xF0000
 #define  B_PCIE_L89EC_UPL8RPH                    BIT12
 #define  B_PCIE_L89EC_UPL8RPH_OFFSET             12
 #define  B_PCIE_L89EC_UPL8RPH_MASK               0x7000
 #define  B_PCIE_L89EC_UPL8TP                     BIT8
 #define  B_PCIE_L89EC_UPL8TP_OFFSET              8
 #define  B_PCIE_L89EC_UPL8TP_MASK                0xF00
 #define  B_PCIE_L89EC_DPL8RPH                    BIT4
 #define  B_PCIE_L89EC_DPL8RPH_OFFSET             4
 #define  B_PCIE_L89EC_DPL8RPH_MASK               0x70
 #define  B_PCIE_L89EC_DPL8TP                     BIT0
 #define  B_PCIE_L89EC_DPL8TP_OFFSET              0
 #define  B_PCIE_L89EC_DPL8TP_MASK                0xF

#define  R_PCIE_L1011EC                           0xA50
 #define  B_PCIE_L1011EC_UPL11RPH                 BIT28
 #define  B_PCIE_L1011EC_UPL11RPH_OFFSET          28
 #define  B_PCIE_L1011EC_UPL11RPH_MASK            0x70000000
 #define  B_PCIE_L1011EC_UPL11TP                  BIT24
 #define  B_PCIE_L1011EC_UPL11TP_OFFSET           24
 #define  B_PCIE_L1011EC_UPL11TP_MASK             0xF000000
 #define  B_PCIE_L1011EC_DPL11RPH                 BIT20
 #define  B_PCIE_L1011EC_DPL11RPH_OFFSET          20
 #define  B_PCIE_L1011EC_DPL11RPH_MASK            0x700000
 #define  B_PCIE_L1011EC_DPL11TP                  BIT16
 #define  B_PCIE_L1011EC_DPL11TP_OFFSET           16
 #define  B_PCIE_L1011EC_DPL11TP_MASK             0xF0000
 #define  B_PCIE_L1011EC_UPL10RPH                 BIT12
 #define  B_PCIE_L1011EC_UPL10RPH_OFFSET          12
 #define  B_PCIE_L1011EC_UPL10RPH_MASK            0x7000
 #define  B_PCIE_L1011EC_UPL10TP                  BIT8
 #define  B_PCIE_L1011EC_UPL10TP_OFFSET           8
 #define  B_PCIE_L1011EC_UPL10TP_MASK             0xF00
 #define  B_PCIE_L1011EC_DPL10RPH                 BIT4
 #define  B_PCIE_L1011EC_DPL10RPH_OFFSET          4
 #define  B_PCIE_L1011EC_DPL10RPH_MASK            0x70
 #define  B_PCIE_L1011EC_DPL10TP                  BIT0
 #define  B_PCIE_L1011EC_DPL10TP_OFFSET           0
 #define  B_PCIE_L1011EC_DPL10TP_MASK             0xF

#define  R_PCIE_L1213EC                           0xA54
 #define  B_PCIE_L1213EC_UPL13RPH                 BIT28
 #define  B_PCIE_L1213EC_UPL13RPH_OFFSET          28
 #define  B_PCIE_L1213EC_UPL13RPH_MASK            0x70000000
 #define  B_PCIE_L1213EC_UPL13TP                  BIT24
 #define  B_PCIE_L1213EC_UPL13TP_OFFSET           24
 #define  B_PCIE_L1213EC_UPL13TP_MASK             0xF000000
 #define  B_PCIE_L1213EC_DPL13RPH                 BIT20
 #define  B_PCIE_L1213EC_DPL13RPH_OFFSET          20
 #define  B_PCIE_L1213EC_DPL13RPH_MASK            0x700000
 #define  B_PCIE_L1213EC_DPL13TP                  BIT16
 #define  B_PCIE_L1213EC_DPL13TP_OFFSET           16
 #define  B_PCIE_L1213EC_DPL13TP_MASK             0xF0000
 #define  B_PCIE_L1213EC_UPL12RPH                 BIT12
 #define  B_PCIE_L1213EC_UPL12RPH_OFFSET          12
 #define  B_PCIE_L1213EC_UPL12RPH_MASK            0x7000
 #define  B_PCIE_L1213EC_UPL12TP                  BIT8
 #define  B_PCIE_L1213EC_UPL12TP_OFFSET           8
 #define  B_PCIE_L1213EC_UPL12TP_MASK             0xF00
 #define  B_PCIE_L1213EC_DPL12RPH                 BIT4
 #define  B_PCIE_L1213EC_DPL12RPH_OFFSET          4
 #define  B_PCIE_L1213EC_DPL12RPH_MASK            0x70
 #define  B_PCIE_L1213EC_DPL12TP                  BIT0
 #define  B_PCIE_L1213EC_DPL12TP_OFFSET           0
 #define  B_PCIE_L1213EC_DPL12TP_MASK             0xF

#define  R_PCIE_L1415EC                           0xA58
 #define  B_PCIE_L1415EC_UPL15RPH                 BIT28
 #define  B_PCIE_L1415EC_UPL15RPH_OFFSET          28
 #define  B_PCIE_L1415EC_UPL15RPH_MASK            0x70000000
 #define  B_PCIE_L1415EC_UPL15TP                  BIT24
 #define  B_PCIE_L1415EC_UPL15TP_OFFSET           24
 #define  B_PCIE_L1415EC_UPL15TP_MASK             0xF000000
 #define  B_PCIE_L1415EC_DPL15RPH                 BIT20
 #define  B_PCIE_L1415EC_DPL15RPH_OFFSET          20
 #define  B_PCIE_L1415EC_DPL15RPH_MASK            0x700000
 #define  B_PCIE_L1415EC_DPL15TP                  BIT16
 #define  B_PCIE_L1415EC_DPL15TP_OFFSET           16
 #define  B_PCIE_L1415EC_DPL15TP_MASK             0xF0000
 #define  B_PCIE_L1415EC_UPL14RPH                 BIT12
 #define  B_PCIE_L1415EC_UPL14RPH_OFFSET          12
 #define  B_PCIE_L1415EC_UPL14RPH_MASK            0x7000
 #define  B_PCIE_L1415EC_UPL14TP                  BIT8
 #define  B_PCIE_L1415EC_UPL14TP_OFFSET           8
 #define  B_PCIE_L1415EC_UPL14TP_MASK             0xF00
 #define  B_PCIE_L1415EC_DPL14RPH                 BIT4
 #define  B_PCIE_L1415EC_DPL14RPH_OFFSET          4
 #define  B_PCIE_L1415EC_DPL14RPH_MASK            0x70
 #define  B_PCIE_L1415EC_DPL14TP                  BIT0
 #define  B_PCIE_L1415EC_DPL14TP_OFFSET           0
 #define  B_PCIE_L1415EC_DPL14TP_MASK             0xF

#define  R_PCIE_PL16L01EC                        0xABC
 #define  B_PCIE_PL16L01EC_UP16L1TP_MASK         0x00F00000
 #define  B_PCIE_PL16L01EC_UP16L1TP              BIT20
 #define  B_PCIE_PL16L01EC_UP16L1TP_OFFSET       20
 #define  B_PCIE_PL16L01EC_DP16L1TP_MASK         0x000F0000
 #define  B_PCIE_PL16L01EC_DP16L1TP              BIT16
 #define  B_PCIE_PL16L01EC_DP16L1TP_OFFSET       16
 #define  B_PCIE_PL16L01EC_UP16L0TP_MASK         0xF0
 #define  B_PCIE_PL16L01EC_UP16L0TP              BIT4
 #define  B_PCIE_PL16L01EC_UP16L0TP_OFFSET       4
 #define  B_PCIE_PL16L01EC_DP16L0TP              BIT0
 #define  B_PCIE_PL16L01EC_DP16L0TP_OFFSET       0
 #define  B_PCIE_PL16L01EC_DP16L0TP_MASK         0xF

#define  R_PCIE_PL16L23EC                        0xAC0
 #define  B_PCIE_PL16L23EC_UP16L3TP_MASK         0x00F00000
 #define  B_PCIE_PL16L23EC_UP16L3TP              BIT20
 #define  B_PCIE_PL16L23EC_UP16L3TP_OFFSET       20
 #define  B_PCIE_PL16L23EC_DP16L3TP_MASK         0x000F0000
 #define  B_PCIE_PL16L23EC_DP16L3TP              BIT16
 #define  B_PCIE_PL16L23EC_DP16L3TP_OFFSET       16
 #define  B_PCIE_PL16L23EC_UP16L2TP_MASK         0xF0
 #define  B_PCIE_PL16L23EC_UP16L2TP              BIT4
 #define  B_PCIE_PL16L23EC_UP16L2TP_OFFSET       4
 #define  B_PCIE_PL16L23EC_DP16L2TP              BIT0
 #define  B_PCIE_PL16L23EC_DP16L2TP_OFFSET       0
 #define  B_PCIE_PL16L23EC_DP16L2TP_MASK         0xF

#define  R_PCIE_PL16L45EC                        0xAC4
 #define  B_PCIE_PL16L45EC_UP16L5TP_MASK         0x00F00000
 #define  B_PCIE_PL16L45EC_UP16L5TP              BIT20
 #define  B_PCIE_PL16L45EC_UP16L5TP_OFFSET       20
 #define  B_PCIE_PL16L45EC_DP16L5TP_MASK         0x000F0000
 #define  B_PCIE_PL16L45EC_DP16L5TP              BIT16
 #define  B_PCIE_PL16L45EC_DP16L5TP_OFFSET       16
 #define  B_PCIE_PL16L45EC_UP16L4TP_MASK         0xF0
 #define  B_PCIE_PL16L45EC_UP16L4TP              BIT4
 #define  B_PCIE_PL16L45EC_UP16L4TP_OFFSET       4
 #define  B_PCIE_PL16L45EC_DP16L4TP              BIT0
 #define  B_PCIE_PL16L45EC_DP16L4TP_OFFSET       0
 #define  B_PCIE_PL16L45EC_DP16L4TP_MASK         0xF

#define  R_PCIE_PL16L67EC                        0xAC8
 #define  B_PCIE_PL16L67EC_UP16L7TP_MASK         0x00F00000
 #define  B_PCIE_PL16L67EC_UP16L7TP              BIT20
 #define  B_PCIE_PL16L67EC_UP16L7TP_OFFSET       20
 #define  B_PCIE_PL16L67EC_DP16L7TP_MASK         0x000F0000
 #define  B_PCIE_PL16L67EC_DP16L7TP              BIT16
 #define  B_PCIE_PL16L67EC_DP16L7TP_OFFSET       16
 #define  B_PCIE_PL16L67EC_UP16L6TP_MASK         0xF0
 #define  B_PCIE_PL16L67EC_UP16L6TP              BIT4
 #define  B_PCIE_PL16L67EC_UP16L6TP_OFFSET       4
 #define  B_PCIE_PL16L67EC_DP16L6TP              BIT0
 #define  B_PCIE_PL16L67EC_DP16L6TP_OFFSET       0
 #define  B_PCIE_PL16L67EC_DP16L6TP_MASK         0xF

#define  R_PCIE_PL16L89EC                        0xACC
 #define  B_PCIE_PL16L89EC_UP16L9TP_MASK         0x00F00000
 #define  B_PCIE_PL16L89EC_UP16L9TP              BIT20
 #define  B_PCIE_PL16L89EC_UP16L9TP_OFFSET       20
 #define  B_PCIE_PL16L89EC_DP16L9TP_MASK         0x000F0000
 #define  B_PCIE_PL16L89EC_DP16L9TP              BIT16
 #define  B_PCIE_PL16L89EC_DP16L9TP_OFFSET       16
 #define  B_PCIE_PL16L89EC_UP16L8TP_MASK         0xF0
 #define  B_PCIE_PL16L89EC_UP16L8TP              BIT4
 #define  B_PCIE_PL16L89EC_UP16L8TP_OFFSET       4
 #define  B_PCIE_PL16L89EC_DP16L8TP              BIT0
 #define  B_PCIE_PL16L89EC_DP16L8TP_OFFSET       0
 #define  B_PCIE_PL16L89EC_DP16L8TP_MASK         0xF

#define  R_PCIE_PL16L1011EC                      0xAD0
 #define  B_PCIE_PL16L1011EC_UP16L11TP_MASK       0x00F00000
 #define  B_PCIE_PL16L1011EC_UP16L11TP            BIT20
 #define  B_PCIE_PL16L1011EC_UP16L11TP_OFFSET     20
 #define  B_PCIE_PL16L1011EC_DP16L11TP_MASK       0x000F0000
 #define  B_PCIE_PL16L1011EC_DP16L11TP            BIT16
 #define  B_PCIE_PL16L1011EC_DP16L11TP_OFFSET     16
 #define  B_PCIE_PL16L1011EC_UP16L10TP_MASK       0xF0
 #define  B_PCIE_PL16L1011EC_UP16L10TP            BIT4
 #define  B_PCIE_PL16L1011EC_UP16L10TP_OFFSET     4
 #define  B_PCIE_PL16L1011EC_DP16L10TP            BIT0
 #define  B_PCIE_PL16L1011EC_DP16L10TP_OFFSET     0
 #define  B_PCIE_PL16L1011EC_DP16L10TP_MASK       0xF

#define  R_PCIE_PL16L1213EC                       0xAD4
 #define  B_PCIE_PL16L1213EC_UP16L13TP_MASK       0x00F00000
 #define  B_PCIE_PL16L1213EC_UP16L13TP            BIT20
 #define  B_PCIE_PL16L1213EC_UP16L13TP_OFFSET     20
 #define  B_PCIE_PL16L1213EC_DP16L13TP_MASK       0x000F0000
 #define  B_PCIE_PL16L1213EC_DP16L13TP            BIT16
 #define  B_PCIE_PL16L1213EC_DP16L13TP_OFFSET     16
 #define  B_PCIE_PL16L1213EC_UP16L12TP_MASK       0xF0
 #define  B_PCIE_PL16L1213EC_UP16L12TP            BIT4
 #define  B_PCIE_PL16L1213EC_UP16L12TP_OFFSET     4
 #define  B_PCIE_PL16L1213EC_DP16L12TP            BIT0
 #define  B_PCIE_PL16L1213EC_DP16L12TP_OFFSET     0
 #define  B_PCIE_PL16L1213EC_DP16L12TP_MASK       0xF

#define  R_PCIE_PL16L1415EC                       0xAD8
 #define  B_PCIE_PL16L1415EC_UP16L15TP_MASK       0x00F00000
 #define  B_PCIE_PL16L1415EC_UP16L15TP            BIT20
 #define  B_PCIE_PL16L1415EC_UP16L15TP_OFFSET     20
 #define  B_PCIE_PL16L1415EC_DP16L15TP_MASK       0x000F0000
 #define  B_PCIE_PL16L1415EC_DP16L15TP            BIT16
 #define  B_PCIE_PL16L1415EC_DP16L15TP_OFFSET     16
 #define  B_PCIE_PL16L1415EC_UP16L14TP_MASK       0xF0
 #define  B_PCIE_PL16L1415EC_UP16L14TP            BIT4
 #define  B_PCIE_PL16L1415EC_UP16L14TP_OFFSET     4
 #define  B_PCIE_PL16L1415EC_DP16L14TP            BIT0
 #define  B_PCIE_PL16L1415EC_DP16L14TP_OFFSET     0
 #define  B_PCIE_PL16L1415EC_DP16L14TP_MASK       0xF

#define  R_PCIE_IOMMUCAPECAPDIS                   0xC00
 #define  B_PCIE_IOMMUCAPECAPDIS_EAFSCAPDIS       BIT24
 #define  B_PCIE_IOMMUCAPECAPDIS_EAFSCAPDIS_OFFSET 24
 #define  B_PCIE_IOMMUCAPECAPDIS_NWFSCAPDIS       BIT23
 #define  B_PCIE_IOMMUCAPECAPDIS_NWFSCAPDIS_OFFSET 23
 #define  B_PCIE_IOMMUCAPECAPDIS_POT              BIT22
 #define  B_PCIE_IOMMUCAPECAPDIS_POT_OFFSET       22
 #define  B_PCIE_IOMMUCAPECAPDIS_SRS              BIT21
 #define  B_PCIE_IOMMUCAPECAPDIS_SRS_OFFSET       21
 #define  B_PCIE_IOMMUCAPECAPDIS_ERS              BIT20
 #define  B_PCIE_IOMMUCAPECAPDIS_ERS_OFFSET       20
 #define  B_PCIE_IOMMUCAPECAPDIS_PRSCAPDIS        BIT19
 #define  B_PCIE_IOMMUCAPECAPDIS_PRSCAPDIS_OFFSET 19
 #define  B_PCIE_IOMMUCAPECAPDIS_PASIDCAPDIS      BIT18
 #define  B_PCIE_IOMMUCAPECAPDIS_PASIDCAPDIS_OFFSET 18
 #define  B_PCIE_IOMMUCAPECAPDIS_DISCAPDIS        BIT17
 #define  B_PCIE_IOMMUCAPECAPDIS_DISCAPDIS_OFFSET 17
 #define  B_PCIE_IOMMUCAPECAPDIS_NSTCAPDIS        BIT16
 #define  B_PCIE_IOMMUCAPECAPDIS_NSTCAPDIS_OFFSET 16
 #define  B_PCIE_IOMMUCAPECAPDIS_MTSCAPDIS        BIT15
 #define  B_PCIE_IOMMUCAPECAPDIS_MTSCAPDIS_OFFSET 15
 #define  B_PCIE_IOMMUCAPECAPDIS_ECSCAPDIS        BIT14
 #define  B_PCIE_IOMMUCAPECAPDIS_ECSCAPDIS_OFFSET 14
 #define  B_PCIE_IOMMUCAPECAPDIS_SCCAPDIS         BIT13
 #define  B_PCIE_IOMMUCAPECAPDIS_SCCAPDIS_OFFSET  13
 #define  B_PCIE_IOMMUCAPECAPDIS_PTCAPDIS         BIT12
 #define  B_PCIE_IOMMUCAPECAPDIS_PTCAPDIS_OFFSET  12
 #define  B_PCIE_IOMMUCAPECAPDIS_EIM              BIT11
 #define  B_PCIE_IOMMUCAPECAPDIS_EIM_OFFSET       11
 #define  B_PCIE_IOMMUCAPECAPDIS_IRCAPDIS         BIT10
 #define  B_PCIE_IOMMUCAPECAPDIS_IRCAPDIS_OFFSET  10
 #define  B_PCIE_IOMMUCAPECAPDIS_DTCAPDIS         BIT9
 #define  B_PCIE_IOMMUCAPECAPDIS_DTCAPDIS_OFFSET  9
 #define  B_PCIE_IOMMUCAPECAPDIS_QICAPDIS         BIT8
 #define  B_PCIE_IOMMUCAPECAPDIS_QICAPDIS_OFFSET  8
 #define  B_PCIE_IOMMUCAPECAPDIS_C                BIT7
 #define  B_PCIE_IOMMUCAPECAPDIS_C_OFFSET         7
 #define  B_PCIE_IOMMUCAPECAPDIS_FL1GPCAPDIS      BIT6
 #define  B_PCIE_IOMMUCAPECAPDIS_FL1GPCAPDIS_OFFSET 6
 #define  B_PCIE_IOMMUCAPECAPDIS_PSI              BIT5
 #define  B_PCIE_IOMMUCAPECAPDIS_PSI_OFFSET       5
 #define  B_PCIE_IOMMUCAPECAPDIS_SSPSCAPCTRL      BIT1
 #define  B_PCIE_IOMMUCAPECAPDIS_SSPSCAPCTRL_OFFSET 1
 #define  B_PCIE_IOMMUCAPECAPDIS_SSPSCAPCTRL_MASK 0x1E
 #define  B_PCIE_IOMMUCAPECAPDIS_ZLR              BIT0
 #define  B_PCIE_IOMMUCAPECAPDIS_ZLR_OFFSET       0

#define  R_PCIE_IOMMUIOTLBDIS                     0xC04
 #define  B_PCIE_IOMMUIOTLBDIS_IOTLBDIS           BIT0
 #define  B_PCIE_IOMMUIOTLBDIS_IOTLBDIS_OFFSET    0
 #define  B_PCIE_IOMMUIOTLBDIS_IOTLBDIS_MASK      0xFFFF

#define  R_PCIE_IOMMUPWSTRDIS                     0xC08
 #define  B_PCIE_IOMMUPWSTRDIS_PQDIS              BIT12
 #define  B_PCIE_IOMMUPWSTRDIS_PQDIS_OFFSET       12
 #define  B_PCIE_IOMMUPWSTRDIS_PQDIS_MASK         0x3000
 #define  B_PCIE_IOMMUPWSTRDIS_PWTDIS             BIT10
 #define  B_PCIE_IOMMUPWSTRDIS_PWTDIS_OFFSET      10
 #define  B_PCIE_IOMMUPWSTRDIS_PWTDIS_MASK        0xC00
 #define  B_PCIE_IOMMUPWSTRDIS_RCCDIS             BIT8
 #define  B_PCIE_IOMMUPWSTRDIS_RCCDIS_OFFSET      8
 #define  B_PCIE_IOMMUPWSTRDIS_RCCDIS_MASK        0x300
 #define  B_PCIE_IOMMUPWSTRDIS_SL5DIS             BIT6
 #define  B_PCIE_IOMMUPWSTRDIS_SL5DIS_OFFSET      6
 #define  B_PCIE_IOMMUPWSTRDIS_SL5DIS_MASK        0xC0
 #define  B_PCIE_IOMMUPWSTRDIS_SL4DIS             BIT4
 #define  B_PCIE_IOMMUPWSTRDIS_SL4DIS_OFFSET      4
 #define  B_PCIE_IOMMUPWSTRDIS_SL4DIS_MASK        0x30
 #define  B_PCIE_IOMMUPWSTRDIS_SL3DIS             BIT2
 #define  B_PCIE_IOMMUPWSTRDIS_SL3DIS_OFFSET      2
 #define  B_PCIE_IOMMUPWSTRDIS_SL3DIS_MASK        0xC
 #define  B_PCIE_IOMMUPWSTRDIS_SL2DIS             BIT0
 #define  B_PCIE_IOMMUPWSTRDIS_SL2DIS_OFFSET      0
 #define  B_PCIE_IOMMUPWSTRDIS_SL2DIS_MASK        0x3

#define  R_PCIE_IOMMUMISCDIS                      0xC0C
 #define  B_PCIE_IOMMUMISCDIS_DFXASME             BIT31
 #define  B_PCIE_IOMMUMISCDIS_DFXASME_OFFSET      31
 #define  B_PCIE_IOMMUMISCDIS_DFXASMA             BIT23
 #define  B_PCIE_IOMMUMISCDIS_DFXASMA_OFFSET      23
 #define  B_PCIE_IOMMUMISCDIS_DFXASMA_MASK        0x7F800000
 #define  B_PCIE_IOMMUMISCDIS_PWTFULLSTALLCB      BIT22
 #define  B_PCIE_IOMMUMISCDIS_PWTFULLSTALLCB_OFFSET 22
 #define  B_PCIE_IOMMUMISCDIS_PWTBANKDIS          BIT21
 #define  B_PCIE_IOMMUMISCDIS_PWTBANKDIS_OFFSET   21
 #define  B_PCIE_IOMMUMISCDIS_COLORLIM            BIT18
 #define  B_PCIE_IOMMUMISCDIS_COLORLIM_OFFSET     18
 #define  B_PCIE_IOMMUMISCDIS_COLORLIM_MASK       0x1C0000
 #define  B_PCIE_IOMMUMISCDIS_PQPRIOARB           BIT16
 #define  B_PCIE_IOMMUMISCDIS_PQPRIOARB_OFFSET    16
 #define  B_PCIE_IOMMUMISCDIS_PQPRIOARB_MASK      0x30000
 #define  B_PCIE_IOMMUMISCDIS_PWTPRIOARB          BIT13
 #define  B_PCIE_IOMMUMISCDIS_PWTPRIOARB_OFFSET   13
 #define  B_PCIE_IOMMUMISCDIS_PWTPRIOARB_MASK     0xE000
 #define  B_PCIE_IOMMUMISCDIS_SP1                 BIT10
 #define  B_PCIE_IOMMUMISCDIS_SP1_OFFSET          10
 #define  B_PCIE_IOMMUMISCDIS_SP1_MASK            0x1C00
 #define  B_PCIE_IOMMUMISCDIS_PRQCOHDIS           BIT9
 #define  B_PCIE_IOMMUMISCDIS_PRQCOHDIS_OFFSET    9
 #define  B_PCIE_IOMMUMISCDIS_QICOHDIS            BIT8
 #define  B_PCIE_IOMMUMISCDIS_QICOHDIS_OFFSET     8
 #define  B_PCIE_IOMMUMISCDIS_H2PDIS              BIT7
 #define  B_PCIE_IOMMUMISCDIS_H2PDIS_OFFSET       7
 #define  B_PCIE_IOMMUMISCDIS_SP2                 BIT6
 #define  B_PCIE_IOMMUMISCDIS_SP2_OFFSET          6
 #define  B_PCIE_IOMMUMISCDIS_SP3                 BIT4
 #define  B_PCIE_IOMMUMISCDIS_SP3_OFFSET          4
 #define  B_PCIE_IOMMUMISCDIS_SP3_MASK            0x30
 #define  B_PCIE_IOMMUMISCDIS_STALLFETCHFIFODIS   BIT3
 #define  B_PCIE_IOMMUMISCDIS_STALLFETCHFIFODIS_OFFSET 3
 #define  B_PCIE_IOMMUMISCDIS_STALLCBFIFODIS      BIT2
 #define  B_PCIE_IOMMUMISCDIS_STALLCBFIFODIS_OFFSET 2
 #define  B_PCIE_IOMMUMISCDIS_CTXPARTINVDIS       BIT1
 #define  B_PCIE_IOMMUMISCDIS_CTXPARTINVDIS_OFFSET 1
 #define  B_PCIE_IOMMUMISCDIS_IOTLBPARTINVDIS     BIT0
 #define  B_PCIE_IOMMUMISCDIS_IOTLBPARTINVDIS_OFFSET 0

#define  R_PCIE_IOMMUPWRDNOVRD                    0xC10
 #define  B_PCIE_IOMMUPWRDNOVRD_PWRDNOVRD         BIT0
 #define  B_PCIE_IOMMUPWRDNOVRD_PWRDNOVRD_OFFSET  0
 #define  B_PCIE_IOMMUPWRDNOVRD_PWRDNOVRD_MASK    0xFFFFFFFF

#define  R_PCIE_IOMMUPARITYINJ                    0xC14
 #define  B_PCIE_IOMMUPARITYINJ_PARITYINJ         BIT0
 #define  B_PCIE_IOMMUPARITYINJ_PARITYINJ_OFFSET  0
 #define  B_PCIE_IOMMUPARITYINJ_PARITYINJ_MASK    0xFFFFFFFF

#define  R_PCIE_IOMMUPWTPRIORSV                   0xC18
 #define  B_PCIE_IOMMUPWTPRIORSV_PRIORSV          BIT16
 #define  B_PCIE_IOMMUPWTPRIORSV_PRIORSV_OFFSET   16
 #define  B_PCIE_IOMMUPWTPRIORSV_PRIORSV_MASK     0xFFFF0000
 #define  B_PCIE_IOMMUPWTPRIORSV_HI_PRIO_RSV      BIT8
 #define  B_PCIE_IOMMUPWTPRIORSV_HI_PRIO_RSV_OFFSET 8
 #define  B_PCIE_IOMMUPWTPRIORSV_HI_PRIO_RSV_MASK 0xFF00
 #define  B_PCIE_IOMMUPWTPRIORSV_LO_PRIO_RSV      BIT0
 #define  B_PCIE_IOMMUPWTPRIORSV_LO_PRIO_RSV_OFFSET 0
 #define  B_PCIE_IOMMUPWTPRIORSV_LO_PRIO_RSV_MASK 0xFF

#define  R_PCIE_EATMC1                            0xC1C
 #define  B_PCIE_EATMC1_ATME                      BIT31
 #define  B_PCIE_EATMC1_ATME_OFFSET               31
 #define  B_PCIE_EATMC1_ATMAM                     BIT28
 #define  B_PCIE_EATMC1_ATMAM_OFFSET              28
 #define  B_PCIE_EATMC1_ATMAM_MASK                0x30000000
 #define  B_PCIE_EATMC1_ATMA                      BIT26
 #define  B_PCIE_EATMC1_ATMA_OFFSET               26
 #define  B_PCIE_EATMC1_ATMA_MASK                 0xC000000
 #define  B_PCIE_EATMC1_ATMTCM                    BIT23
 #define  B_PCIE_EATMC1_ATMTCM_OFFSET             23
 #define  B_PCIE_EATMC1_ATMTCM_MASK               0x3800000
 #define  B_PCIE_EATMC1_ATMTC                     BIT20
 #define  B_PCIE_EATMC1_ATMTC_OFFSET              20
 #define  B_PCIE_EATMC1_ATMTC_MASK                0x700000
 #define  B_PCIE_EATMC1_ATMADM                    BIT19
 #define  B_PCIE_EATMC1_ATMADM_OFFSET             19
 #define  B_PCIE_EATMC1_ATMADMD                   BIT0
 #define  B_PCIE_EATMC1_ATMADMD_OFFSET            0
 #define  B_PCIE_EATMC1_ATMADMD_MASK              0x7FFFF

#define  R_PCIE_EATMC2                            0xC20
 #define  B_PCIE_EATMC2_ATMXORT                   BIT31
 #define  B_PCIE_EATMC2_ATMXORT_OFFSET            31
 #define  B_PCIE_EATMC2_ATMMARIDR                 BIT30
 #define  B_PCIE_EATMC2_ATMMARIDR_OFFSET          30
 #define  B_PCIE_EATMC2_ATMMAURCB                 BIT29
 #define  B_PCIE_EATMC2_ATMMAURCB_OFFSET          29
 #define  B_PCIE_EATMC2_ATMCIDCB                  BIT28
 #define  B_PCIE_EATMC2_ATMCIDCB_OFFSET           28
 #define  B_PCIE_EATMC2_ATMTTHO                   BIT27
 #define  B_PCIE_EATMC2_ATMTTHO_OFFSET            27
 #define  B_PCIE_EATMC2_ATMRTHO                   BIT26
 #define  B_PCIE_EATMC2_ATMRTHO_OFFSET            26
 #define  B_PCIE_EATMC2_ATMDC                     BIT24
 #define  B_PCIE_EATMC2_ATMDC_OFFSET              24
 #define  B_PCIE_EATMC2_ATM_FLOWTYPE              BIT20
 #define  B_PCIE_EATMC2_ATM_FLOWTYPE_OFFSET       20
 #define  B_PCIE_EATMC2_ATM_FLOWTYPE_MASK         0xF00000
 #define  B_PCIE_EATMC2_ATMF                      BIT17
 #define  B_PCIE_EATMC2_ATMF_OFFSET               17
 #define  B_PCIE_EATMC2_ATMF_MASK                 0x60000
 #define  B_PCIE_EATMC2_ATMFM                     BIT16
 #define  B_PCIE_EATMC2_ATMFM_OFFSET              16
 #define  B_PCIE_EATMC2_ATMLT                     BIT1
 #define  B_PCIE_EATMC2_ATMLT_OFFSET              1
 #define  B_PCIE_EATMC2_ATMLT_MASK                0x3FE
 #define  B_PCIE_EATMC2_ATMLTE                    BIT0
 #define  B_PCIE_EATMC2_ATMLTE_OFFSET             0

#define  R_PCIE_EATMC3                            0xC24
 #define  B_PCIE_EATMC3_TLTT0HSS                  BIT31
 #define  B_PCIE_EATMC3_TLTT0HSS_OFFSET           31
 #define  B_PCIE_EATMC3_TLTT0HCV                  BIT19
 #define  B_PCIE_EATMC3_TLTT0HCV_OFFSET           19
 #define  B_PCIE_EATMC3_TLTT0HCV_MASK             0x7FF80000
 #define  B_PCIE_EATMC3_TLTT0HFO                  BIT18
 #define  B_PCIE_EATMC3_TLTT0HFO_OFFSET           18
 #define  B_PCIE_EATMC3_TLTT0HAE                  BIT17
 #define  B_PCIE_EATMC3_TLTT0HAE_OFFSET           17
 #define  B_PCIE_EATMC3_TLTT0HR                   BIT16
 #define  B_PCIE_EATMC3_TLTT0HR_OFFSET            16
 #define  B_PCIE_EATMC3_TLTT0HS                   BIT0
 #define  B_PCIE_EATMC3_TLTT0HS_OFFSET            0
 #define  B_PCIE_EATMC3_TLTT0HS_MASK              0xFFFF

#define  R_PCIE_EATMC4                            0xC28
 #define  B_PCIE_EATMC4_TLTT0DSS                  BIT31
 #define  B_PCIE_EATMC4_TLTT0DSS_OFFSET           31
 #define  B_PCIE_EATMC4_TLTT0DCV                  BIT19
 #define  B_PCIE_EATMC4_TLTT0DCV_OFFSET           19
 #define  B_PCIE_EATMC4_TLTT0DCV_MASK             0x7FF80000
 #define  B_PCIE_EATMC4_TLTT0DFO                  BIT18
 #define  B_PCIE_EATMC4_TLTT0DFO_OFFSET           18
 #define  B_PCIE_EATMC4_TLTT0DAE                  BIT17
 #define  B_PCIE_EATMC4_TLTT0DAE_OFFSET           17
 #define  B_PCIE_EATMC4_TLTT0DR                   BIT16
 #define  B_PCIE_EATMC4_TLTT0DR_OFFSET            16
 #define  B_PCIE_EATMC4_TLTT0DS                   BIT0
 #define  B_PCIE_EATMC4_TLTT0DS_OFFSET            0
 #define  B_PCIE_EATMC4_TLTT0DS_MASK              0xFFFF

#define  R_PCIE_EATMC5                            0xC2C
 #define  B_PCIE_EATMC5_TLTT1HSS                  BIT31
 #define  B_PCIE_EATMC5_TLTT1HSS_OFFSET           31
 #define  B_PCIE_EATMC5_TLTT1HCV                  BIT19
 #define  B_PCIE_EATMC5_TLTT1HCV_OFFSET           19
 #define  B_PCIE_EATMC5_TLTT1HCV_MASK             0x7FF80000
 #define  B_PCIE_EATMC5_TLTT1HFO                  BIT18
 #define  B_PCIE_EATMC5_TLTT1HFO_OFFSET           18
 #define  B_PCIE_EATMC5_TLTT1HAE                  BIT17
 #define  B_PCIE_EATMC5_TLTT1HAE_OFFSET           17
 #define  B_PCIE_EATMC5_TLTT1HR                   BIT16
 #define  B_PCIE_EATMC5_TLTT1HR_OFFSET            16
 #define  B_PCIE_EATMC5_TLTT1HS                   BIT0
 #define  B_PCIE_EATMC5_TLTT1HS_OFFSET            0
 #define  B_PCIE_EATMC5_TLTT1HS_MASK              0xFFFF

#define  R_PCIE_EATMC6                            0xC30
 #define  B_PCIE_EATMC6_TLTT1DSS                  BIT31
 #define  B_PCIE_EATMC6_TLTT1DSS_OFFSET           31
 #define  B_PCIE_EATMC6_TLTT1DCV                  BIT19
 #define  B_PCIE_EATMC6_TLTT1DCV_OFFSET           19
 #define  B_PCIE_EATMC6_TLTT1DCV_MASK             0x7FF80000
 #define  B_PCIE_EATMC6_TLTT1DFO                  BIT18
 #define  B_PCIE_EATMC6_TLTT1DFO_OFFSET           18
 #define  B_PCIE_EATMC6_TLTT1DAE                  BIT17
 #define  B_PCIE_EATMC6_TLTT1DAE_OFFSET           17
 #define  B_PCIE_EATMC6_TLTT1DR                   BIT16
 #define  B_PCIE_EATMC6_TLTT1DR_OFFSET            16
 #define  B_PCIE_EATMC6_TLTT1DS                   BIT0
 #define  B_PCIE_EATMC6_TLTT1DS_OFFSET            0
 #define  B_PCIE_EATMC6_TLTT1DS_MASK              0xFFFF

#define  R_PCIE_EATMC7                            0xC34
 #define  B_PCIE_EATMC7_LLTTSS                    BIT31
 #define  B_PCIE_EATMC7_LLTTSS_OFFSET             31
 #define  B_PCIE_EATMC7_LLTTCV                    BIT19
 #define  B_PCIE_EATMC7_LLTTCV_OFFSET             19
 #define  B_PCIE_EATMC7_LLTTCV_MASK               0x7FF80000
 #define  B_PCIE_EATMC7_LLTTFO                    BIT18
 #define  B_PCIE_EATMC7_LLTTFO_OFFSET             18
 #define  B_PCIE_EATMC7_LLTTAE                    BIT17
 #define  B_PCIE_EATMC7_LLTTAE_OFFSET             17
 #define  B_PCIE_EATMC7_LLTTR                     BIT16
 #define  B_PCIE_EATMC7_LLTTR_OFFSET              16

#define  R_PCIE_EATMC8                            0xC38
 #define  B_PCIE_EATMC8_TLRTHSS                   BIT31
 #define  B_PCIE_EATMC8_TLRTHSS_OFFSET            31
 #define  B_PCIE_EATMC8_TLRTHCV                   BIT19
 #define  B_PCIE_EATMC8_TLRTHCV_OFFSET            19
 #define  B_PCIE_EATMC8_TLRTHCV_MASK              0x7FF80000
 #define  B_PCIE_EATMC8_TLRTHFO                   BIT18
 #define  B_PCIE_EATMC8_TLRTHFO_OFFSET            18
 #define  B_PCIE_EATMC8_TLRTHAE                   BIT17
 #define  B_PCIE_EATMC8_TLRTHAE_OFFSET            17
 #define  B_PCIE_EATMC8_TLRTHR                    BIT16
 #define  B_PCIE_EATMC8_TLRTHR_OFFSET             16
 #define  B_PCIE_EATMC8_TLRTHS                    BIT0
 #define  B_PCIE_EATMC8_TLRTHS_OFFSET             0
 #define  B_PCIE_EATMC8_TLRTHS_MASK               0xFFFF

#define  R_PCIE_EATMC9                            0xC3C
 #define  B_PCIE_EATMC9_TLRTDSS                   BIT31
 #define  B_PCIE_EATMC9_TLRTDSS_OFFSET            31
 #define  B_PCIE_EATMC9_TLRTDCV                   BIT19
 #define  B_PCIE_EATMC9_TLRTDCV_OFFSET            19
 #define  B_PCIE_EATMC9_TLRTDCV_MASK              0x7FF80000
 #define  B_PCIE_EATMC9_TLRTDFO                   BIT18
 #define  B_PCIE_EATMC9_TLRTDFO_OFFSET            18
 #define  B_PCIE_EATMC9_TLRTDAE                   BIT17
 #define  B_PCIE_EATMC9_TLRTDAE_OFFSET            17
 #define  B_PCIE_EATMC9_TLRTDR                    BIT16
 #define  B_PCIE_EATMC9_TLRTDR_OFFSET             16
 #define  B_PCIE_EATMC9_TLRTDS                    BIT0
 #define  B_PCIE_EATMC9_TLRTDS_OFFSET             0
 #define  B_PCIE_EATMC9_TLRTDS_MASK               0xFFFF

#define  R_PCIE_EATMC10                           0xC40
 #define  B_PCIE_EATMC10_LLRT0HSS                 BIT31
 #define  B_PCIE_EATMC10_LLRT0HSS_OFFSET          31
 #define  B_PCIE_EATMC10_LLRT0HCV                 BIT19
 #define  B_PCIE_EATMC10_LLRT0HCV_OFFSET          19
 #define  B_PCIE_EATMC10_LLRT0HCV_MASK            0x7FF80000
 #define  B_PCIE_EATMC10_LLRT0HFO                 BIT18
 #define  B_PCIE_EATMC10_LLRT0HFO_OFFSET          18
 #define  B_PCIE_EATMC10_LLRT0HAE                 BIT17
 #define  B_PCIE_EATMC10_LLRT0HAE_OFFSET          17
 #define  B_PCIE_EATMC10_LLRT0HR                  BIT16
 #define  B_PCIE_EATMC10_LLRT0HR_OFFSET           16
 #define  B_PCIE_EATMC10_LLRT0HS                  BIT0
 #define  B_PCIE_EATMC10_LLRT0HS_OFFSET           0
 #define  B_PCIE_EATMC10_LLRT0HS_MASK             0xFFFF

#define  R_PCIE_EATMC11                           0xC44
 #define  B_PCIE_EATMC11_LLRT0DSS                 BIT31
 #define  B_PCIE_EATMC11_LLRT0DSS_OFFSET          31
 #define  B_PCIE_EATMC11_LLRT0DCV                 BIT19
 #define  B_PCIE_EATMC11_LLRT0DCV_OFFSET          19
 #define  B_PCIE_EATMC11_LLRT0DCV_MASK            0x7FF80000
 #define  B_PCIE_EATMC11_LLRT0DFO                 BIT18
 #define  B_PCIE_EATMC11_LLRT0DFO_OFFSET          18
 #define  B_PCIE_EATMC11_LLRT0DAE                 BIT17
 #define  B_PCIE_EATMC11_LLRT0DAE_OFFSET          17
 #define  B_PCIE_EATMC11_LLRT0DR                  BIT16
 #define  B_PCIE_EATMC11_LLRT0DR_OFFSET           16
 #define  B_PCIE_EATMC11_LLRT0DS                  BIT0
 #define  B_PCIE_EATMC11_LLRT0DS_OFFSET           0
 #define  B_PCIE_EATMC11_LLRT0DS_MASK             0xFFFF

#define  R_PCIE_EATMC12                           0xC48
 #define  B_PCIE_EATMC12_LLRTLP1HSS               BIT31
 #define  B_PCIE_EATMC12_LLRTLP1HSS_OFFSET        31
 #define  B_PCIE_EATMC12_LLRT1HCV                 BIT19
 #define  B_PCIE_EATMC12_LLRT1HCV_OFFSET          19
 #define  B_PCIE_EATMC12_LLRT1HCV_MASK            0x7FF80000
 #define  B_PCIE_EATMC12_LLRT1HFO                 BIT18
 #define  B_PCIE_EATMC12_LLRT1HFO_OFFSET          18
 #define  B_PCIE_EATMC12_LLRT1HAE                 BIT17
 #define  B_PCIE_EATMC12_LLRT1HAE_OFFSET          17
 #define  B_PCIE_EATMC12_LLRT1HR                  BIT16
 #define  B_PCIE_EATMC12_LLRT1HR_OFFSET           16
 #define  B_PCIE_EATMC12_LLRT1HS                  BIT0
 #define  B_PCIE_EATMC12_LLRT1HS_OFFSET           0
 #define  B_PCIE_EATMC12_LLRT1HS_MASK             0xFFFF

#define  R_PCIE_EATMC13                           0xC4C
 #define  B_PCIE_EATMC13_LLRTLP1DSS               BIT31
 #define  B_PCIE_EATMC13_LLRTLP1DSS_OFFSET        31
 #define  B_PCIE_EATMC13_LLRT1DCV                 BIT19
 #define  B_PCIE_EATMC13_LLRT1DCV_OFFSET          19
 #define  B_PCIE_EATMC13_LLRT1DCV_MASK            0x7FF80000
 #define  B_PCIE_EATMC13_LLRT1DFO                 BIT18
 #define  B_PCIE_EATMC13_LLRT1DFO_OFFSET          18
 #define  B_PCIE_EATMC13_LLRT1DAE                 BIT17
 #define  B_PCIE_EATMC13_LLRT1DAE_OFFSET          17
 #define  B_PCIE_EATMC13_LLRT1DR                  BIT16
 #define  B_PCIE_EATMC13_LLRT1DR_OFFSET           16
 #define  B_PCIE_EATMC13_LLRT1DS                  BIT0
 #define  B_PCIE_EATMC13_LLRT1DS_OFFSET           0
 #define  B_PCIE_EATMC13_LLRT1DS_MASK             0xFFFF

#define  R_PCIE_ACGR3S2                                0xC50
 #define  B_PCIE_ACGR3S2_SRL                           BIT5
 #define  B_PCIE_ACGR3S2_CLKREQMSGTXVLMDESTID          BIT10
 #define  B_PCIE_ACGR3S2_CLKREQMSGTXVLMDESTID_OFFSET   10
 #define  B_PCIE_ACGR3S2_CLKREQMSGTXVLMDESTID_MASK     0x0003FC00

#define  R_PCIE_CLTRSUB                           0xC54
#define  B_PCIE_CLTRSUB_LTRNSLSUBEN              BIT31
#define  B_PCIE_CLTRSUB_LTRNSLSUBEN_OFFSET       31
#define  B_PCIE_CLTRSUB_LTRNSLSSUBV              BIT26
#define  B_PCIE_CLTRSUB_LTRNSLSSUBV_OFFSET       26
#define  B_PCIE_CLTRSUB_LTRNSLSSUBV_MASK         0x1C000000
#define  B_PCIE_CLTRSUB_LTRNSLSUBV               BIT16
#define  B_PCIE_CLTRSUB_LTRNSLSUBV_OFFSET        16
#define  B_PCIE_CLTRSUB_LTRNSLSUBV_MASK          0x3FF0000
#define  B_PCIE_CLTRSUB_LTRSLSUBEN               BIT15
#define  B_PCIE_CLTRSUB_LTRSLSUBEN_OFFSET        15
#define  B_PCIE_CLTRSUB_LTRSLSSUBV               BIT10
#define  B_PCIE_CLTRSUB_LTRSLSSUBV_OFFSET        10
#define  B_PCIE_CLTRSUB_LTRSLSSUBV_MASK          0x1C00
#define  B_PCIE_CLTRSUB_LTRSLSUBV                BIT0
#define  B_PCIE_CLTRSUB_LTRSLSUBV_OFFSET         0
#define  B_PCIE_CLTRSUB_LTRSLSUBV_MASK           0x3FF

#define  R_PCIE_CLKREQMP                                0xC58
 #define  B_PCIE_CLKREQMP_CLKREQMSGDL2DEBM              BIT27
 #define  B_PCIE_CLKREQMP_CLKREQMSGDL2DEBM_OFFSET       27
 #define  B_PCIE_CLKREQMP_CLKREQMSGL1EBM                BIT26
 #define  B_PCIE_CLKREQMP_CLKREQMSGL1EBM_OFFSET         26
 #define  B_PCIE_CLKREQMP_CLKREQMSGRXVLMI               BIT18
 #define  B_PCIE_CLKREQMP_CLKREQMSGRXVLMI_OFFSET        18
 #define  B_PCIE_CLKREQMP_CLKREQMSGRXVLMI_MASK          0x03FC0000
 #define  B_PCIE_CLKREQMP_CLKREQMSGTXVLMI1              BIT10
 #define  B_PCIE_CLKREQMP_CLKREQMSGTXVLMI1_OFFSET       10
 #define  B_PCIE_CLKREQMP_CLKREQMSGTXVLMI1_MASK         0x0003FC00
 #define  B_PCIE_CLKREQMP_CLKREQMSGTXVLMI0              BIT2
 #define  B_PCIE_CLKREQMP_CLKREQMSGTXVLMI0_OFFSET       2
 #define  B_PCIE_CLKREQMP_CLKREQMSGTXVLMI0_MASK         0x000003FC
 #define  B_PCIE_CLKREQMP_ASRTCLKREQP                   BIT1
 #define  B_PCIE_CLKREQMP_ASRTCLKREQP_OFFSET            1
 #define  B_PCIE_CLKREQMP_CKREQMPEN                     BIT0
 #define  B_PCIE_CLKREQMP_CKREQMPEN_OFFSET              0

#define  R_PCIE_LTRSUBL1STD                             0xC5C
 #define  B_PCIE_LTRSUBL1STD_LTRNSLSUBEN                BIT31
 #define  B_PCIE_LTRSUBL1STD_LTRNSLSSUBV                BIT26
 #define  B_PCIE_LTRSUBL1STD_LTRNSLSSUBV_OFFSET         26
 #define  B_PCIE_LTRSUBL1STD_LTRNSLSSUBV_MASK           (BIT28 | BIT27 | BIT26)
 #define  V_PCIE_LTRSUBL1STD_LTRNSLSSUBV                0x2
 #define  B_PCIE_LTRSUBL1STD_LTRNSLSUBV                 BIT16
 #define  B_PCIE_LTRSUBL1STD_LTRNSLSUBV_OFFSET          16
 #define  B_PCIE_LTRSUBL1STD_LTRNSLSUBV_MASK            0x03FF0000
 #define  V_PCIE_LTRSUBL1STD_LTRNSLSUBV                 0x1E
 #define  B_PCIE_LTRSUBL1STD_LTRSLSUBEN                 BIT15
 #define  B_PCIE_LTRSUBL1STD_LTRSLSSUBV                 BIT10
 #define  B_PCIE_LTRSUBL1STD_LTRSLSSUBV_OFFSET          10
 #define  B_PCIE_LTRSUBL1STD_LTRSLSSUBV_MASK            (BIT12 | BIT11 | BIT10)
 #define  V_PCIE_LTRSUBL1STD_LTRSLSSUBV                 0x2
 #define  B_PCIE_LTRSUBL1STD_LTRSLSUBV                  BIT0
 #define  B_PCIE_LTRSUBL1STD_LTRSLSUBV_OFFSET           0
 #define  B_PCIE_LTRSUBL1STD_LTRSLSUBV_MASK             0x000003FF
 #define  V_PCIE_LTRSUBL1STD_LTRSLSUBV                  0x1E

#define  R_PCIE_LTRSUBL11                               0xC60
#define  B_PCIE_LTRSUBL11_LTRNSLSUBEN                   BIT31
#define  B_PCIE_LTRSUBL11_LTRNSLSSUBV                   BIT26
#define  B_PCIE_LTRSUBL11_LTRNSLSSUBV_OFFSET            26
#define  B_PCIE_LTRSUBL11_LTRNSLSSUBV_MASK              (BIT28 | BIT27 | BIT26)
#define  V_PCIE_LTRSUBL11_LTRNSLSSUBV                   0x2
#define  B_PCIE_LTRSUBL11_LTRNSLSUBV                    BIT16
#define  B_PCIE_LTRSUBL11_LTRNSLSUBV_OFFSET             16
#define  B_PCIE_LTRSUBL11_LTRNSLSUBV_MASK               0x03FF0000
#define  V_PCIE_LTRSUBL11_LTRNSLSUBV                    0x28
#define  B_PCIE_LTRSUBL11_LTRSLSUBEN                    BIT15
#define  B_PCIE_LTRSUBL11_LTRSLSSUBV                    BIT10
#define  B_PCIE_LTRSUBL11_LTRSLSSUBV_OFFSET             10
#define  B_PCIE_LTRSUBL11_LTRSLSSUBV_MASK               (BIT12 | BIT11 | BIT10)
#define  V_PCIE_LTRSUBL11_LTRSLSSUBV                    0x2
#define  B_PCIE_LTRSUBL11_LTRSLSUBV                     BIT0
#define  B_PCIE_LTRSUBL11_LTRSLSUBV_OFFSET              0
#define  B_PCIE_LTRSUBL11_LTRSLSUBV_MASK                0x000003FF
#define  V_PCIE_LTRSUBL11_LTRSLSUBV                     0x28

#define  R_PCIE_LTRSUBL12                               0xC64
#define  B_PCIE_LTRSUBL12_LTRNSLSUBEN                   BIT31
#define  B_PCIE_LTRSUBL12_LTRNSLSSUBV                   BIT26
#define  B_PCIE_LTRSUBL12_LTRNSLSSUBV_OFFSET            26
#define  B_PCIE_LTRSUBL12_LTRNSLSSUBV_MASK              (BIT28 | BIT27 | BIT26)
#define  V_PCIE_LTRSUBL12_LTRNSLSSUBV                   0x2
#define  B_PCIE_LTRSUBL12_LTRNSLSUBV                    BIT16
#define  B_PCIE_LTRSUBL12_LTRNSLSUBV_OFFSET             16
#define  B_PCIE_LTRSUBL12_LTRNSLSUBV_MASK               0x03FF0000
#define  V_PCIE_LTRSUBL12_LTRNSLSUBV                    0x64
#define  B_PCIE_LTRSUBL12_LTRSLSUBEN                    BIT15
#define  B_PCIE_LTRSUBL12_LTRSLSSUBV                    BIT10
#define  B_PCIE_LTRSUBL12_LTRSLSSUBV_OFFSET             10
#define  B_PCIE_LTRSUBL12_LTRSLSSUBV_MASK               (BIT12 | BIT11 | BIT10)
#define  V_PCIE_LTRSUBL12_LTRSLSSUBV                    0x2
#define  B_PCIE_LTRSUBL12_LTRSLSUBV                     BIT0
#define  B_PCIE_LTRSUBL12_LTRSLSUBV_OFFSET              0
#define  B_PCIE_LTRSUBL12_LTRSLSUBV_MASK                0x000003FF
#define  V_PCIE_LTRSUBL12_LTRSLSUBV                     0x64

#define  R_PCIE_LPCR                                    0xC8C
 #define  B_PCIE_LPCR_DIDOVR_LOCK                       BIT24
 #define  B_PCIE_LPCR_LTRCFGLOCK                        BIT16
 #define  B_PCIE_LPCR_SERL                              BIT8
 #define  B_PCIE_LPCR_SRL                               BIT0


#define R_SA_PCIE_CFG_PTMPSDC9                    0xCB0 ///< PEG PTM Pipe Stage Delay Configuration 9
#define R_SA_PCIE_CFG_PTMPSDC10                   0xCB4 ///< PEG PTM Pipe Stage Delay Configuration 10

// 2LM
#define  R_PCIE_TLADVCTLST                        0xCC4
 #define  B_PCIE_TLADVCTLST_VC0TXARBGC            BIT0
 #define  B_PCIE_TLADVCTLST_VC0TXARBGC_OFFSET     0
 #define  B_PCIE_TLADVCTLST_VC0TXARBGC_MASK       0x1F
 #define  B_PCIE_TLADVCTLST_VC1TXARBGC            BIT5
 #define  B_PCIE_TLADVCTLST_VC1TXARBGC_OFFSET     5
 #define  B_PCIE_TLADVCTLST_VC1TXARBGC_MASK       0x3E0
 #define  B_PCIE_TLADVCTLST_VC0REQPUTARBGC        BIT10
 #define  B_PCIE_TLADVCTLST_VC0REQPUTARBGC_OFFSET 10
 #define  B_PCIE_TLADVCTLST_VC0REQPUTARBGC_MASK   0x7C00
 #define  B_PCIE_TLADVCTLST_VC1REQPUTARBGC        BIT15
 #define  B_PCIE_TLADVCTLST_VC1REQPUTARBGC_OFFSET 15
 #define  B_PCIE_TLADVCTLST_VC1REQPUTARBGC_MASK   0xF8000

// 2LM
#define  R_PCIE_FMMCTLST                          0xCC8
 #define  B_PCIE_FMMCTLST_FMMPS                   BIT0
 #define  B_PCIE_FMMCTLST_FMMPS_OFFSET            0
 #define  B_PCIE_FMMCTLST_FMMPS_MASK              0x7

//
// PCIE PCRs (PID:SPA SPB SPC SPD SPE SPF)
//
#define R_SA_SPX_PCR_PCD                             0x3E00                  ///< Port configuration and disable
 #define  B_SA_SPX_PCR_PCD_RP0FN                     (BIT2 | BIT1 | BIT0)    ///< Port 1 Function Number
 #define  B_SA_SPX_PCR_PCD_RP0CH                     BIT3                    ///< Port 1 config hide
 #define  B_SA_SPX_PCR_PCD_RP1FN                     (BIT6 | BIT5 | BIT4)    ///< Port 2 Function Number
 #define  B_SA_SPX_PCR_PCD_RP1CH                     BIT7                    ///< Port 2 config hide
 #define  B_SA_SPX_PCR_PCD_RP2FN                     (BIT10 | BIT9 | BIT8)   ///< Port 3 Function Number
 #define  B_SA_SPX_PCR_PCD_RP2CH                     BIT11                   ///< Port 3 config hide
 #define  B_SA_SPX_PCR_PCD_RP3FN                     (BIT14 | BIT13 | BIT12) ///< Port 4 Function Number
 #define  B_SA_SPX_PCR_PCD_RP3CH                     BIT15                   ///< Port 4 config hide
 #define  S_SA_SPX_PCR_PCD_RP_FIELD                  4                       ///< 4 bits for each RP FN
 #define  B_SA_SPX_PCR_PCD_P0D                       BIT16                   ///< Port 1 disable
 #define  B_SA_SPX_PCR_PCD_P1D                       BIT17                   ///< Port 2 disable
 #define  B_SA_SPX_PCR_PCD_P2D                       BIT18                   ///< Port 3 disable
 #define  B_SA_SPX_PCR_PCD_P3D                       BIT19                   ///< Port 4 disable
#define R_SA_SPX_PCR_SRL                             0x3E24                  ///< Secured Register Lock
 #define  B_SA_SPX_PCR_PCD_SRL                       BIT0                    ///< Secured Register Lock bit

///
/// Device 1 Register Equates
///
#define R_SA_PEG_DID_OFFSET            0x02  ///< Device ID
#define R_SA_PEG_BCTRL_OFFSET          0x3E  ///< Bridge Control
#define R_SA_PEG_SS_OFFSET             0x8C  ///< Subsystem ID
#define R_SA_PEG_LCTL_OFFSET           0xB0  ///< Link Control
#define R_SA_PEG_LSTS_OFFSET           0xB2  ///< Link Status
#define R_SA_PEG_SLOTSTS_OFFSET        0xBA  ///< Slot Status
#define R_SA_PEG_DCAP2_OFFSET          0xC4  ///< Device Capability 2
#define R_SA_PEG_DCTL2_OFFSET          0xC8  ///< Device Control 2
#define R_SA_PEG_VC0RSTS_OFFSET        0x11A ///< PEG VC0 Resource Status
#define R_SA_PEG_L0SLAT_OFFSET         0x22C ///< PEG L0s Control
#define R_SA_PEG_CFG4_OFFSET           0x258 ///< PEG Config 4
#define R_SA_PEG_EQPH3_OFFSET          0x384 ///< PEG Phase 3
#define R_SA_PEG_AFEBND0CFG1_OFFSET    0x904 ///< PEG AFE Bundle Config 1
#define R_SA_PEG_AFEBND0CFG2_OFFSET    0x908 ///< PEG AFE Bundle Config 2
#define R_SA_PEG_AFEBND0CFG3_OFFSET    0x90C ///< PEG AFE Bundle Config 3
#define R_SA_PEG_AFEBND0CFG4_OFFSET    0x910 ///< PEG AFE Bundle Config 4
#define R_SA_PEG_G3CTL0_OFFSET         0x918 ///< PEG Gen3 Control
#define R_SA_PEG_BND0SPARE_OFFSET      0x91C ///< PEG Bundle 0 Spare Register
#define R_SA_PEG_AFELN0CFG0_OFFSET     0xA00 ///< PEG AFE Lane Config 0
#define R_SA_PEG_AFELN0CFG1_OFFSET     0xA04 ///< PEG AFE Lane Config 1
#define R_SA_PEG_AFEOVR_OFFSET         0xC20 ///< PEG AFE Override
#define R_SA_PEG_CMNSPARE_OFFSET       0xC38 ///< PEG Common Spare
#define R_SA_PEG_LCTL3_OFFSET          0xD98 ///< PEG Link Control 3
#define R_SA_PEG_EQCTL0_1_OFFSET       0xDA0 ///< PEG Lane Equalization
#define R_SA_PEG_EQPRESET1_2_OFFSET    0xDC0 ///< PEG Coefficients for P1 and P2
#define R_SA_PEG_EQPRESET2_3_4_OFFSET  0xDC4 ///< PEG Coefficients for P2, P3, and P4
#define R_SA_PEG_EQPRESET4_5_OFFSET    0xDC8 ///< PEG Coefficients for P4 and P5
#define R_SA_PEG_EQPRESET6_7_OFFSET    0xDCC ///< PEG Coefficients for P6 and P7
#define R_SA_PEG_EQPRESET7_8_9_OFFSET  0xDD0 ///< PEG Coefficients for P7, P8, and P9
#define R_SA_PEG_EQPRESET9_10_OFFSET   0xDD4 ///< PEG Coefficients for P9 and P10
#define R_SA_PEG_EQCFG_OFFSET          0xDD8 ///< PEG Equalization Config
#define R_SA_PEG_EQPRESET11_OFFSET     0xDDC ///< PEG Coefficients for P11

#define R_SA_PEG_BND10_CRI2_FUSE_DWORD14_OFFSET   0x2338 ///< PEG Bundle 10(DMI) CRI2 FUSE register DWORD 14

#define R_SA_PEG_BND0_CRI0_CR_DWORD22_OFFSET      0x0058 ///< PEG Bundle 0 CRI0 CR register DWORD 22
#define R_SA_PEG_BND10_CRI0_CR_DWORD22_OFFSET     0x2258 ///< PEG Bundle 10(DMI) CRI0 CR register DWORD 22

#define R_SA_PEG_BND0_CRI2_FUSE_DWORD15_OFFSET    0x013C ///< PEG Bundle 0 CRI2 FUSE register DWORD 15
#define R_SA_PEG_BND10_CRI2_FUSE_DWORD15_OFFSET   0x233C ///< PEG Bundle 10(DMI) CRI2 FUSE register DWORD 15

#define R_SA_PEG_BND0_CRI0_CR_DWORD24_OFFSET      0x0060 ///< PEG Bundle 0 CRI0 CR register DWORD 24
#define R_SA_PEG_BND10_CRI0_CR_DWORD24_OFFSET     0x2260 ///< PEG Bundle 10(DMI) CRI0 CR register DWORD 24

#define R_SA_PEG_BND0_CRI0_CR_DWORD26_OFFSET      0x0068 ///< PEG Bundle 0 CRI0 CR register DWORD 26
#define R_SA_PEG_BND10_CRI0_CR_DWORD26_OFFSET     0x2268 ///< PEG Bundle 10(DMI) CRI0 CR register DWORD 26

#define R_SA_PEG_BND0_CRI0_CR_DWORD28_OFFSET      0x0070 ///< PEG Bundle 0 CRI0 CR register DWORD 28
#define R_SA_PEG_BND10_CRI0_CR_DWORD28_OFFSET     0x2270 ///< PEG Bundle 10(DMI) CRI0 CR register DWORD 28

#define R_SA_PEG_BND10_CRI2_FUSE_DWORD16_OFFSET   0x2340 ///< PEG Bundle 10(DMI) CRI2 FUSE register DWORD 16

#define R_SA_DEKEL_CMN_LANE_OFFSET                     0x3F00 ///< PEG Common Lane address offset DWORD 32
#define R_SA_DEKEL_FW_VERSION_OFFSET                   0x3F7C ///< Firmware Version offset DWORD 32
#define R_SA_DEKEL_DL_SUSWELL_PWRGATE_CNTRL_OFFSET     0x120
#define R_SA_DEKEL_CL_SUS_CLK_CRWELL_CNTRL_OFFSET      0xF98
#define R_SA_DEKEL_PCS_PMD_RX_TMRS_OFFSET              0x150
#define R_SA_DEKEL_SQUELCH_CTRL_OFFSET                 0xD0C
#define R_SA_DEKEL_PMD_LANE_ANA_CTRL_OFFSET            0x6B4
#define R_SA_DEKEL_NOMEMPTY_UNDFLW_THRESOLD_OFFSET     0x4
#define R_SA_DEKEL_REDO_RX_CALIB_EQ_TRAIN_OFFSET       0xC

#define R_PCIE_IMRAMBL                         0x3E10                    ///< IMR access memory base and limit
#define B_PCIE_IMRAMBL_RS3BN                   0x000000FF                ///< Bus Number for RS3
#define N_PCIE_IMRAMBL_RS3BN                   0
#define B_PCIE_IMRAMBL_IAMB                    0x000FFF00                ///< IMR access memory base, lower bits
#define N_PCIE_IMRAMBL_IAMB                    8
#define B_PCIE_IMRAMBL_IAML                    0xFFF00000                ///< IMR access memory limit, lower bits
#define N_PCIE_IMRAMBL_IAML                    20

#define R_PCIE_IMRAMBU32                       0x3E14                    ///< IMR access memory base, upper bits

#define R_PCIE_IMRAMLU32                       0x3E18                    ///< IMR access memory limit, upper bits

#define R_PCIE_IMRAMLE                         0x3E1C                    ///< IMR access memory lock & enable
#define B_PCIE_IMRAMLE_IAE1                    BIT0                      ///< IMR access enable for port 1 of given controller
#define B_PCIE_IMRAMLE_IAE2                    BIT1                      ///< IMR access enable for port 1 of given controller
#define B_PCIE_IMRAMLE_IAE3                    BIT2                      ///< IMR access enable for port 1 of given controller
#define B_PCIE_IMRAMLE_IAE4                    BIT3                      ///< IMR access enable for port 1 of given controller
#define B_PCIE_IMRAMLE_SRL                     BIT31                     ///< IMR register lock
#endif

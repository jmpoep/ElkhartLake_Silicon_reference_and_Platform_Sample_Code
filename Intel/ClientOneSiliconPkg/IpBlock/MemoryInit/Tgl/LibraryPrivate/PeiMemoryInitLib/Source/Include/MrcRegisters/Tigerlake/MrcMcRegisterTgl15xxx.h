#ifndef __MrcMcRegisterTgl15xxx_h__
#define __MrcMcRegisterTgl15xxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

@copyright
  Copyright (c) 2010 - 2019 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by the
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Peripheral Driver' and is uniquely
  identified as "Intel Reference Module" and is licensed for Intel
  CPUs and chipsets under the terms of your license agreement with
  Intel or your vendor. This file may be modified by the user, subject
  to additional terms of the license agreement.

@par Specification Reference:
**/

#pragma pack(push, 1)


#define MC1_MAD_INTER_CHANNEL_REG                                      (0x00015000)
//Duplicate of MC0_MAD_INTER_CHANNEL_REG

#define MC1_MAD_INTRA_CH0_REG                                          (0x00015004)
//Duplicate of MC0_MAD_INTRA_CH0_REG

#define MC1_MAD_INTRA_CH1_REG                                          (0x00015008)
//Duplicate of MC0_MAD_INTRA_CH0_REG

#define MC1_MAD_DIMM_CH0_REG                                           (0x0001500C)
//Duplicate of MC0_MAD_DIMM_CH0_REG

#define MC1_MAD_DIMM_CH1_REG                                           (0x00015010)
//Duplicate of MC0_MAD_DIMM_CH0_REG

#define MC1_MCDECS_MISC_REG                                            (0x00015018)
//Duplicate of MC0_MCDECS_MISC_REG

#define MC1_MCDECS_CBIT_REG                                            (0x0001501C)
//Duplicate of MC0_MCDECS_CBIT_REG

#define MC1_CHANNEL_HASH_REG                                           (0x00015024)
//Duplicate of MC0_CHANNEL_HASH_REG

#define MC1_CHANNEL_EHASH_REG                                          (0x00015028)
//Duplicate of MC0_CHANNEL_EHASH_REG

#define MC1_MC_INIT_STATE_G_REG                                        (0x00015030)
//Duplicate of MC0_MC_INIT_STATE_G_REG

#define MC1_MRC_REVISION_REG                                           (0x00015034)
//Duplicate of MC0_MRC_REVISION_REG

#define MC1_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_REG                       (0x0001503C)
//Duplicate of MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_REG

#define MC1_PWM_TOTAL_REQCOUNT_REG                                     (0x00015040)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC1_PWM_TOTAL_REQCOUNT_A0_REG                                  (0x00015040)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC1_PWM_PROGRAMMABLE_REQCOUNT_0_REG                            (0x00015048)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC1_PWM_PROGRAMMABLE_REQCOUNT_0_A0_REG                         (0x00015048)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC1_PWM_PROGRAMMABLE_REQCOUNT_1_A0_REG                         (0x0001504C)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC1_PWM_PROGRAMMABLE_REQCOUNT_1_REG                            (0x00015050)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC1_PWM_RDCAS_COUNT_REG                                        (0x00015058)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC1_PWM_RDCAS_COUNT_A0_REG                                     (0x00015058)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC1_PM_SREF_CONFIG_REG                                         (0x00015060)
//Duplicate of MC0_PM_SREF_CONFIG_REG

#define MC1_ATMC_STS_REG                                               (0x00015064)
//Duplicate of MC0_ATMC_STS_REG

#define MC1_READ_OCCUPANCY_COUNT_REG                                   (0x00015068)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC1_READ_OCCUPANCY_COUNT_A0_REG                                (0x00015068)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC1_STALL_DRAIN_REG                                            (0x00015074)
//Duplicate of MC0_STALL_DRAIN_REG

#define MC1_IPC_MC_ARB_REG                                             (0x00015078)
//Duplicate of MC0_IPC_MC_ARB_REG

#define MC1_IPC_MC_DEC_ARB_REG                                         (0x0001507C)
//Duplicate of MC0_IPC_MC_ARB_REG

#define MC1_QUEUE_CREDIT_C_REG                                         (0x00015080)
//Duplicate of MC0_QUEUE_CREDIT_C_REG

#define MC1_ECC_INJ_ADDR_COMPARE_REG                                   (0x00015088)
//Duplicate of MC0_ECC_INJ_ADDR_COMPARE_REG

#define MC1_REMAPBASE_REG                                              (0x00015090)
//Duplicate of MC0_REMAPBASE_REG

#define MC1_REMAPLIMIT_REG                                             (0x00015098)
//Duplicate of MC0_REMAPLIMIT_REG

#define MC1_PWM_WRCAS_COUNT_REG                                        (0x000150A0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC1_PWM_WRCAS_COUNT_A0_REG                                     (0x000150A0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC1_PWM_COMMAND_COUNT_REG                                      (0x000150A8)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC1_PWM_COMMAND_COUNT_A0_REG                                   (0x000150A8)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC1_PWM_NON_SR_COUNT_REG                                       (0x000150B0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC1_PWM_NON_SR_COUNT_A0_REG                                    (0x000150B0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_A0_REG

#define MC1_TOLUD_REG                                                  (0x000150BC)
//Duplicate of MC0_TOLUD_REG

#define MC1_PWM_GLB_DRV_OFF_COUNT_REG                                  (0x000150C0)
//Duplicate of MC0_PWM_TOTAL_REQCOUNT_REG

#define MC1_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG                         (0x00015100)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC1_GDXC_DDR_SYS_ADD_FILTER_MASK_1_REG                         (0x00015108)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC1_GDXC_DDR_SYS_ADD_FILTER_MATCH_0_REG                        (0x00015110)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC1_GDXC_DDR_SYS_ADD_FILTER_MATCH_1_REG                        (0x00015118)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC1_GDXC_DDR_SYS_ADD_TRIGGER_MASK_REG                          (0x00015120)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC1_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_REG                         (0x00015128)
//Duplicate of MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_REG

#define MC1_SC_QOS_REG                                                 (0x00015130)
//Duplicate of MC0_SC_QOS_REG

#define MC1_MCMAINS_GLOBAL_DRIVER_GATE_CFG_REG                         (0x00015138)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC1_PWM_COUNTERS_DURATION_REG                                  (0x00015148)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG

#define MC1_PWM_COUNTERS_DURATION_A0_REG                               (0x0001514C)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG

#define MC1_MCDECS_SECOND_CBIT_REG                                     (0x00015154)
//Duplicate of MC0_MCDECS_SECOND_CBIT_REG

#define MC1_ECC_INJ_ADDR_MASK_REG                                      (0x00015158)
//Duplicate of MC0_ECC_INJ_ADDR_MASK_REG

#define MC1_SC_QOS2_REG                                                (0x00015160)
//Duplicate of MC0_SC_QOS2_REG

#define MC1_SC_QOS3_REG                                                (0x00015168)
//Duplicate of MC0_SC_QOS3_REG

#define MC1_NORMALMODE_CFG_REG                                         (0x0001516C)
//Duplicate of MC0_NORMALMODE_CFG_REG

#define MC1_MC_CPGC_CMI_REG                                            (0x00015170)
//Duplicate of MC0_MC_CPGC_CMI_REG

#define MC1_MC_CPGC_MISC_DFT_REG                                       (0x00015174)
//Duplicate of MC0_MC_CPGC_MISC_DFT_REG

#define MC1_PARITYERRLOG_REG                                           (0x000151A0)
//Duplicate of MC0_PARITYERRLOG_REG

#define MC1_PARITY_ERR_INJ_REG                                         (0x000151A8)
//Duplicate of MC0_PARITY_ERR_INJ_REG

#define MC1_PARITY_CONTROL_REG                                         (0x000151B4)
//Duplicate of MC0_PARITY_CONTROL_REG

#define MC1_DDRPL_CFG_DTF_REG                                          (0x00015200)
//Duplicate of MC0_DDRPL_CFG_DTF_REG

#define MC1_DDRPL_FILTER_DTF_REG                                       (0x00015204)
//Duplicate of MC0_DDRPL_FILTER_DTF_REG

#define MC1_DDRPL_DEBUG_DTF_REG                                        (0x00015208)
//Duplicate of MC0_DDRPL_DEBUG_DTF_REG

#define MC1_DDRPL_VISA_LANES_REG                                       (0x0001520C)
//Duplicate of MC0_DDRPL_VISA_LANES_REG

#define MC1_DDRPL_VISA_CFG_DTF_REG                                     (0x00015210)
//Duplicate of MC0_DDRPL_VISA_CFG_DTF_REG
#pragma pack(pop)
#endif

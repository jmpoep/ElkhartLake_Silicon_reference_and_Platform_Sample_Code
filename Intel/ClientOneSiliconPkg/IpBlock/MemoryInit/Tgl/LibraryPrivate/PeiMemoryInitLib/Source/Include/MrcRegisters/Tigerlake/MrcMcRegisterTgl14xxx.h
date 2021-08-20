#ifndef __MrcMcRegisterTgl14xxx_h__
#define __MrcMcRegisterTgl14xxx_h__
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


#define MC1_CH0_CR_TC_PRE_REG                                          (0x00014000)
//Duplicate of MC0_CH0_CR_TC_PRE_REG

#define MC1_CH0_CR_TC_ACT_REG                                          (0x00014008)
//Duplicate of MC0_CH0_CR_TC_ACT_REG

#define MC1_CH0_CR_TC_RDRD_REG                                         (0x0001400C)
//Duplicate of MC0_CH0_CR_TC_RDRD_REG

#define MC1_CH0_CR_TC_RDWR_REG                                         (0x00014010)
//Duplicate of MC0_CH0_CR_TC_RDWR_REG

#define MC1_CH0_CR_TC_WRRD_REG                                         (0x00014014)
//Duplicate of MC0_CH0_CR_TC_WRRD_REG

#define MC1_CH0_CR_TC_WRWR_REG                                         (0x00014018)
//Duplicate of MC0_CH0_CR_TC_WRWR_REG

#define MC1_CH0_CR_SC_ROUNDTRIP_LATENCY_REG                            (0x00014020)
//Duplicate of MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_REG

#define MC1_CH0_CR_SCHED_CBIT_REG                                      (0x00014028)
//Duplicate of MC0_CH0_CR_SCHED_CBIT_REG

#define MC1_CH0_CR_SCHED_SECOND_CBIT_REG                               (0x0001402C)
//Duplicate of MC0_CH0_CR_SCHED_SECOND_CBIT_REG

#define MC1_CH0_CR_DFT_MISC_REG                                        (0x00014030)
//Duplicate of MC0_CH0_CR_DFT_MISC_REG

#define MC1_CH0_CR_SC_PCIT_REG                                         (0x00014034)
//Duplicate of MC0_CH0_CR_SC_PCIT_REG

#define MC1_CH0_CR_ECC_DFT_REG                                         (0x00014038)
//Duplicate of MC0_CH0_CR_ECC_DFT_REG

#define MC1_CH0_CR_PM_PDWN_CONFIG_REG                                  (0x00014040)
//Duplicate of MC0_CH0_CR_PM_PDWN_CONFIG_REG

#define MC1_CH0_CR_WMM_READ_CONFIG_REG                                 (0x00014044)
//Duplicate of MC0_CH0_CR_WMM_READ_CONFIG_REG

#define MC1_CH0_CR_ECCERRLOG0_REG                                      (0x00014048)
//Duplicate of MC0_CH0_CR_ECCERRLOG0_REG

#define MC1_CH0_CR_ECCERRLOG1_REG                                      (0x0001404C)
//Duplicate of MC0_CH0_CR_ECCERRLOG1_REG

#define MC1_CH0_CR_TC_PWRDN_REG                                        (0x00014050)
//Duplicate of MC0_CH0_CR_TC_PWRDN_REG

#define MC1_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_REG                         (0x00014058)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_REG

#define MC1_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_REG                         (0x0001405C)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_REG

#define MC1_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_REG                         (0x00014060)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_REG

#define MC1_CH0_CR_SC_WDBWM_REG                                        (0x00014068)
//Duplicate of MC0_CH0_CR_SC_WDBWM_REG

#define MC1_CH0_CR_TC_ODT_REG                                          (0x00014070)
//Duplicate of MC0_CH0_CR_TC_ODT_REG

#define MC1_CH0_CR_MCSCHEDS_SPARE_REG                                  (0x00014078)
//Duplicate of MC0_CH0_CR_MCSCHEDS_SPARE_REG

#define MC1_CH0_CR_SC_ODT_MATRIX_REG                                   (0x00014080)
//Duplicate of MC0_CH0_CR_SC_ODT_MATRIX_REG

#define MC1_CH0_CR_DFT_BLOCK_REG                                       (0x00014084)
//Duplicate of MC0_CH0_CR_DFT_BLOCK_REG

#define MC1_CH0_CR_SC_GS_CFG_REG                                       (0x00014088)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_REG

#define MC1_CH0_CR_SC_PH_THROTTLING_0_REG                              (0x00014090)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_0_REG

#define MC1_CH0_CR_SC_PH_THROTTLING_1_REG                              (0x00014094)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_1_REG

#define MC1_CH0_CR_SC_PH_THROTTLING_2_REG                              (0x00014098)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_2_REG

#define MC1_CH0_CR_SC_PH_THROTTLING_3_REG                              (0x0001409C)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_3_REG

#define MC1_CH0_CR_SC_WPQ_THRESHOLD_REG                                (0x000140A0)
//Duplicate of MC0_CH0_CR_SC_WPQ_THRESHOLD_REG

#define MC1_CH0_CR_SC_PR_CNT_CONFIG_REG                                (0x000140A8)
//Duplicate of MC0_CH0_CR_SC_PR_CNT_CONFIG_REG

#define MC1_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG                           (0x000140B0)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG

#define MC1_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG                           (0x000140B4)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG

#define MC1_CH0_CR_SPID_LOW_POWER_CTL_REG                              (0x000140B8)
//Duplicate of MC0_CH0_CR_SPID_LOW_POWER_CTL_REG

#define MC1_CH0_CR_SC_GS_CFG_TRAINING_REG                              (0x000140BC)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_TRAINING_REG

#define MC1_CH0_CR_SCHED_THIRD_CBIT_REG                                (0x000140C0)
//Duplicate of MC0_CH0_CR_SCHED_THIRD_CBIT_REG

#define MC1_CH0_CR_DEADLOCK_BREAKER_REG                                (0x000140C4)
//Duplicate of MC0_CH0_CR_DEADLOCK_BREAKER_REG

#define MC1_CH0_CR_XARB_TC_BUBBLE_INJ_REG                              (0x000140C8)
//Duplicate of MC0_CH0_CR_XARB_TC_BUBBLE_INJ_REG

#define MC1_CH0_CR_XARB_CFG_BUBBLE_INJ_REG                             (0x000140CC)
//Duplicate of MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_REG

#define MC1_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG                 (0x000140D0)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC1_CH0_CR_SC_BLOCKING_RULES_CFG_REG                           (0x000140D4)
//Duplicate of MC0_CH0_CR_SC_BLOCKING_RULES_CFG_REG

#define MC1_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG                      (0x000140D8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC1_CH0_CR_PWM_DDR_SUBCH1_ACT_COUNTER_REG                      (0x000140E0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC1_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG            (0x000140E8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC1_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG           (0x000140E8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC1_CH0_CR_PWM_DDR_SUBCH1_REQ_OCCUPANCY_COUNTER_REG            (0x000140F0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC1_CH0_CR_PWM_DDR_SUBCH1_DCLK_ACTIVE_COUNTER_A0_REG           (0x000140F0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC1_CH0_CR_WCK_CONFIG_REG                                      (0x000140F8)
//Duplicate of MC0_CH0_CR_WCK_CONFIG_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG                       (0x00014120)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_1_REG                       (0x00014124)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_2_REG                       (0x00014128)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_3_REG                       (0x0001412C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_4_REG                       (0x00014130)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_5_REG                       (0x00014134)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_6_REG                       (0x00014138)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_7_REG                       (0x0001413C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_8_REG                       (0x00014140)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_9_REG                       (0x00014144)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_10_REG                      (0x00014148)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_11_REG                      (0x0001414C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_12_REG                      (0x00014150)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_13_REG                      (0x00014154)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_14_REG                      (0x00014158)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_15_REG                      (0x0001415C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_16_REG                      (0x00014160)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_17_REG                      (0x00014164)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_18_REG                      (0x00014168)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_19_REG                      (0x0001416C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_20_REG                      (0x00014170)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_21_REG                      (0x00014174)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_22_REG                      (0x00014178)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_23_REG                      (0x0001417C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_24_REG                      (0x00014180)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_25_REG                      (0x00014184)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_26_REG                      (0x00014188)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_27_REG                      (0x0001418C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG               (0x00014190)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_1_REG               (0x00014194)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_2_REG               (0x00014198)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_3_REG               (0x0001419C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_4_REG               (0x000141A0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_5_REG               (0x000141A4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_6_REG               (0x000141A8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_7_REG               (0x000141AC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_8_REG               (0x000141B0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_9_REG               (0x000141B4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_10_REG              (0x000141B8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_11_REG              (0x000141BC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG                 (0x000141C0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_1_REG                 (0x000141C4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_2_REG                 (0x000141C8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_3_REG                 (0x000141CC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_4_REG                 (0x000141D0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_5_REG                 (0x000141D4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_6_REG                 (0x000141D8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG                  (0x000141E0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG

#define MC1_CH0_CR_MCMNTS_RDDATA_CTL_REG                               (0x000141E8)
//Duplicate of MC0_CH0_CR_MCMNTS_RDDATA_CTL_REG

#define MC1_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG                       (0x00014204)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG

#define MC1_CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG                            (0x00014208)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG

#define MC1_CH0_CR_DDR_MR_PARAMS_REG                                   (0x00014210)
//Duplicate of MC0_CH0_CR_DDR_MR_PARAMS_REG

#define MC1_CH0_CR_DDR_MR_COMMAND_REG                                  (0x00014214)
//Duplicate of MC0_CH0_CR_DDR_MR_COMMAND_REG

#define MC1_CH0_CR_DDR_MR_RESULT_0_REG                                 (0x00014218)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_0_REG

#define MC1_CH0_CR_DDR_MR_RESULT_1_REG                                 (0x0001421C)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_1_REG

#define MC1_CH0_CR_DDR_MR_RESULT_2_REG                                 (0x00014220)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_2_REG

#define MC1_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG                      (0x00014224)
//Duplicate of MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG

#define MC1_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG                       (0x00014228)
//Duplicate of MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG

#define MC1_CH0_CR_DESWIZZLE_LOW_ERM_REG                               (0x00014230)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC1_CH0_CR_TC_RFP_REG                                          (0x00014238)
//Duplicate of MC0_CH0_CR_TC_RFP_REG

#define MC1_CH0_CR_TC_RFTP_REG                                         (0x0001423C)
//Duplicate of MC0_CH0_CR_TC_RFTP_REG

#define MC1_CH0_CR_TC_SRFTP_REG                                        (0x00014240)
//Duplicate of MC0_CH0_CR_TC_SRFTP_REG

#define MC1_CH0_CR_MC_REFRESH_STAGGER_REG                              (0x00014244)
//Duplicate of MC0_CH0_CR_MC_REFRESH_STAGGER_REG

#define MC1_CH0_CR_TC_ZQCAL_REG                                        (0x00014248)
//Duplicate of MC0_CH0_CR_TC_ZQCAL_REG

#define MC1_CH0_CR_TC_MR2_SHADDOW_REG                                  (0x0001424C)
//Duplicate of MC0_CH0_CR_TC_MR2_SHADDOW_REG

#define MC1_CH0_CR_TC_MR4_SHADDOW_REG                                  (0x00014250)
//Duplicate of MC0_CH0_CR_TC_MR4_SHADDOW_REG

#define MC1_CH0_CR_MC_INIT_STATE_REG                                   (0x00014254)
//Duplicate of MC0_CH0_CR_MC_INIT_STATE_REG

#define MC1_CH0_CR_WDB_VISA_SEL_REG                                    (0x00014258)
//Duplicate of MC0_CH0_CR_WDB_VISA_SEL_REG

#define MC1_CH0_CR_PM_DIMM_IDLE_ENERGY_REG                             (0x00014260)
//Duplicate of MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_REG

#define MC1_CH0_CR_PM_DIMM_PD_ENERGY_REG                               (0x00014264)
//Duplicate of MC0_CH0_CR_PM_DIMM_PD_ENERGY_REG

#define MC1_CH0_CR_PM_DIMM_ACT_ENERGY_REG                              (0x00014268)
//Duplicate of MC0_CH0_CR_PM_DIMM_ACT_ENERGY_REG

#define MC1_CH0_CR_PM_DIMM_RD_ENERGY_REG                               (0x0001426C)
//Duplicate of MC0_CH0_CR_PM_DIMM_RD_ENERGY_REG

#define MC1_CH0_CR_PM_DIMM_WR_ENERGY_REG                               (0x00014270)
//Duplicate of MC0_CH0_CR_PM_DIMM_WR_ENERGY_REG

#define MC1_CH0_CR_SC_WR_DELAY_REG                                     (0x00014278)
//Duplicate of MC0_CH0_CR_SC_WR_DELAY_REG

#define MC1_CH0_CR_READ_RETURN_DFT_REG                                 (0x0001427C)
//Duplicate of MC0_CH0_CR_READ_RETURN_DFT_REG

#define MC1_CH0_CR_DESWIZZLE_LOW_REG                                   (0x00014280)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC1_CH0_CR_SC_PBR_REG                                          (0x00014288)
//Duplicate of MC0_CH0_CR_SC_PBR_REG

#define MC1_CH0_CR_LPDDR_PASR_REG                                      (0x00014290)
//Duplicate of MC0_CH0_CR_LPDDR_PASR_REG

#define MC1_CH0_CR_TC_LPDDR4_MISC_REG                                  (0x00014294)
//Duplicate of MC0_CH0_CR_TC_LPDDR4_MISC_REG

#define MC1_CH0_CR_DESWIZZLE_HIGH_ERM_REG                              (0x00014298)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC1_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG                      (0x000142B0)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG

#define MC1_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG                   (0x000142B0)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG

#define MC1_CH0_CR_DESWIZZLE_HIGH_REG                                  (0x000142B8)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC1_CH0_CR_TC_SREXITTP_REG                                     (0x000142C0)
//Duplicate of MC0_CH0_CR_TC_SREXITTP_REG

#define MC1_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG                       (0x000142C8)
//Duplicate of MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG

#define MC1_CH0_CR_WDB_RD_WR_DFX_DATA_REG                              (0x000142D8)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_DATA_REG

#define MC1_CH0_CR_WDB_RD_WR_DFX_CTL_REG                               (0x000142E0)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_CTL_REG

#define MC1_CH0_CR_REF_FSM_STATUS_REG                                  (0x000142E4)
//Duplicate of MC0_CH0_CR_REF_FSM_STATUS_REG

#define MC1_CH0_CR_WDB_MBIST_0_REG                                     (0x000142E8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC1_CH0_CR_WDB_MBIST_1_REG                                     (0x000142EC)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC1_CH0_CR_RDB_MBIST_REG                                       (0x000142F8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC1_CH0_CR_ECC_INJECT_COUNT_REG                                (0x000142FC)
//Duplicate of MC0_CH0_CR_ECC_INJECT_COUNT_REG

#define MC1_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG                   (0x00014300)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC1_CH0_CR_PWM_DDR_SUBCH1_RDDATA_COUNTER_REG                   (0x00014308)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC1_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG                   (0x00014310)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC1_CH0_CR_PWM_DDR_SUBCH1_WRDATA_COUNTER_REG                   (0x00014318)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC1_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG                   (0x00014320)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH0_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_REG                    (0x00014328)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG                    (0x00014330)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_REG                    (0x00014338)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG                      (0x00014344)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC1_CH0_CR_DDR4_MR5_RTT_PARK_VALUES_REG                        (0x00014348)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH0_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_REG                  (0x00014350)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH0_CR_DDR4_MR1_RTT_NOM_VALUES_REG                         (0x00014358)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG                     (0x00014360)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_1_REG                     (0x00014368)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_2_REG                     (0x00014370)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_3_REG                     (0x00014378)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_4_REG                     (0x00014380)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_5_REG                     (0x00014388)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_6_REG                     (0x00014390)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_7_REG                     (0x00014398)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH0_CR_DDR4_MR0_MR1_CONTENT_REG                            (0x000143A0)
//Duplicate of MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_REG

#define MC1_CH0_CR_DDR4_MR2_MR3_CONTENT_REG                            (0x000143A4)
//Duplicate of MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_REG

#define MC1_CH0_CR_DDR4_MR4_MR5_CONTENT_REG                            (0x000143A8)
//Duplicate of MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_REG

#define MC1_CH0_CR_DDR4_MR6_MR7_CONTENT_REG                            (0x000143AC)
//Duplicate of MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_REG

#define MC1_CH0_CR_DDR4_MR2_RTT_WR_VALUES_REG                          (0x000143B0)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH0_CR_DDR4_MR6_VREF_VALUES_0_REG                          (0x000143B8)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_CH0_CR_DDR4_MR6_VREF_VALUES_1_REG                          (0x000143C0)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_CH0_CR_LPDDR_MR_CONTENT_REG                                (0x000143C8)
//Duplicate of MC0_CH0_CR_LPDDR_MR_CONTENT_REG

#define MC1_CH0_CR_MRS_FSM_CONTROL_REG                                 (0x000143D0)
//Duplicate of MC0_CH0_CR_MRS_FSM_CONTROL_REG

#define MC1_CH0_CR_MRS_FSM_RUN_REG                                     (0x000143D8)
//Duplicate of MC0_CH0_CR_MRS_FSM_RUN_REG

#define MC1_CH0_CR_DDR4_MR1_ODIC_VALUES_REG                            (0x000143DC)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC1_CH0_CR_PL_AGENT_CFG_DTF_REG                                (0x000143E0)
//Duplicate of MC0_CH0_CR_PL_AGENT_CFG_DTF_REG

#define MC1_CH0_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_REG                   (0x000143E4)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC1_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG                          (0x000143E8)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC1_CH0_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_REG                    (0x000143F0)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC1_CH0_CR_MCMNTS_SPARE_REG                                    (0x000143FC)
//Duplicate of MC0_CH0_CR_MCMNTS_SPARE_REG

#define MC1_CH1_CR_TC_PRE_REG                                          (0x00014400)
//Duplicate of MC0_CH0_CR_TC_PRE_REG

#define MC1_CH1_CR_TC_ACT_REG                                          (0x00014408)
//Duplicate of MC0_CH0_CR_TC_ACT_REG

#define MC1_CH1_CR_TC_RDRD_REG                                         (0x0001440C)
//Duplicate of MC0_CH0_CR_TC_RDRD_REG

#define MC1_CH1_CR_TC_RDWR_REG                                         (0x00014410)
//Duplicate of MC0_CH0_CR_TC_RDWR_REG

#define MC1_CH1_CR_TC_WRRD_REG                                         (0x00014414)
//Duplicate of MC0_CH0_CR_TC_WRRD_REG

#define MC1_CH1_CR_TC_WRWR_REG                                         (0x00014418)
//Duplicate of MC0_CH0_CR_TC_WRWR_REG

#define MC1_CH1_CR_SC_ROUNDTRIP_LATENCY_REG                            (0x00014420)
//Duplicate of MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_REG

#define MC1_CH1_CR_SCHED_CBIT_REG                                      (0x00014428)
//Duplicate of MC0_CH0_CR_SCHED_CBIT_REG

#define MC1_CH1_CR_SCHED_SECOND_CBIT_REG                               (0x0001442C)
//Duplicate of MC0_CH0_CR_SCHED_SECOND_CBIT_REG

#define MC1_CH1_CR_DFT_MISC_REG                                        (0x00014430)
//Duplicate of MC0_CH0_CR_DFT_MISC_REG

#define MC1_CH1_CR_SC_PCIT_REG                                         (0x00014434)
//Duplicate of MC0_CH0_CR_SC_PCIT_REG

#define MC1_CH1_CR_ECC_DFT_REG                                         (0x00014438)
//Duplicate of MC0_CH0_CR_ECC_DFT_REG

#define MC1_CH1_CR_PM_PDWN_CONFIG_REG                                  (0x00014440)
//Duplicate of MC0_CH0_CR_PM_PDWN_CONFIG_REG

#define MC1_CH1_CR_WMM_READ_CONFIG_REG                                 (0x00014444)
//Duplicate of MC0_CH0_CR_WMM_READ_CONFIG_REG

#define MC1_CH1_CR_ECCERRLOG0_REG                                      (0x00014448)
//Duplicate of MC0_CH0_CR_ECCERRLOG0_REG

#define MC1_CH1_CR_ECCERRLOG1_REG                                      (0x0001444C)
//Duplicate of MC0_CH0_CR_ECCERRLOG1_REG

#define MC1_CH1_CR_TC_PWRDN_REG                                        (0x00014450)
//Duplicate of MC0_CH0_CR_TC_PWRDN_REG

#define MC1_CH1_CR_QUEUE_ENTRY_DISABLE_RPQ_REG                         (0x00014458)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_REG

#define MC1_CH1_CR_QUEUE_ENTRY_DISABLE_IPQ_REG                         (0x0001445C)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_REG

#define MC1_CH1_CR_QUEUE_ENTRY_DISABLE_WPQ_REG                         (0x00014460)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_REG

#define MC1_CH1_CR_SC_WDBWM_REG                                        (0x00014468)
//Duplicate of MC0_CH0_CR_SC_WDBWM_REG

#define MC1_CH1_CR_TC_ODT_REG                                          (0x00014470)
//Duplicate of MC0_CH0_CR_TC_ODT_REG

#define MC1_CH1_CR_MCSCHEDS_SPARE_REG                                  (0x00014478)
//Duplicate of MC0_CH0_CR_MCSCHEDS_SPARE_REG

#define MC1_CH1_CR_SC_ODT_MATRIX_REG                                   (0x00014480)
//Duplicate of MC0_CH0_CR_SC_ODT_MATRIX_REG

#define MC1_CH1_CR_DFT_BLOCK_REG                                       (0x00014484)
//Duplicate of MC0_CH0_CR_DFT_BLOCK_REG

#define MC1_CH1_CR_SC_GS_CFG_REG                                       (0x00014488)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_REG

#define MC1_CH1_CR_SC_PH_THROTTLING_0_REG                              (0x00014490)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_0_REG

#define MC1_CH1_CR_SC_PH_THROTTLING_1_REG                              (0x00014494)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_1_REG

#define MC1_CH1_CR_SC_PH_THROTTLING_2_REG                              (0x00014498)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_2_REG

#define MC1_CH1_CR_SC_PH_THROTTLING_3_REG                              (0x0001449C)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_3_REG

#define MC1_CH1_CR_SC_WPQ_THRESHOLD_REG                                (0x000144A0)
//Duplicate of MC0_CH0_CR_SC_WPQ_THRESHOLD_REG

#define MC1_CH1_CR_SC_PR_CNT_CONFIG_REG                                (0x000144A8)
//Duplicate of MC0_CH0_CR_SC_PR_CNT_CONFIG_REG

#define MC1_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG                           (0x000144B0)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG

#define MC1_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG                           (0x000144B4)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG

#define MC1_CH1_CR_SPID_LOW_POWER_CTL_REG                              (0x000144B8)
//Duplicate of MC0_CH0_CR_SPID_LOW_POWER_CTL_REG

#define MC1_CH1_CR_SC_GS_CFG_TRAINING_REG                              (0x000144BC)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_TRAINING_REG

#define MC1_CH1_CR_SCHED_THIRD_CBIT_REG                                (0x000144C0)
//Duplicate of MC0_CH0_CR_SCHED_THIRD_CBIT_REG

#define MC1_CH1_CR_DEADLOCK_BREAKER_REG                                (0x000144C4)
//Duplicate of MC0_CH0_CR_DEADLOCK_BREAKER_REG

#define MC1_CH1_CR_XARB_TC_BUBBLE_INJ_REG                              (0x000144C8)
//Duplicate of MC0_CH0_CR_XARB_TC_BUBBLE_INJ_REG

#define MC1_CH1_CR_XARB_CFG_BUBBLE_INJ_REG                             (0x000144CC)
//Duplicate of MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_REG

#define MC1_CH1_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG                 (0x000144D0)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC1_CH1_CR_SC_BLOCKING_RULES_CFG_REG                           (0x000144D4)
//Duplicate of MC0_CH0_CR_SC_BLOCKING_RULES_CFG_REG

#define MC1_CH1_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG                      (0x000144D8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC1_CH1_CR_PWM_DDR_SUBCH1_ACT_COUNTER_REG                      (0x000144E0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC1_CH1_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG            (0x000144E8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC1_CH1_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG           (0x000144E8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC1_CH1_CR_PWM_DDR_SUBCH1_REQ_OCCUPANCY_COUNTER_REG            (0x000144F0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC1_CH1_CR_PWM_DDR_SUBCH1_DCLK_ACTIVE_COUNTER_A0_REG           (0x000144F0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC1_CH1_CR_WCK_CONFIG_REG                                      (0x000144F8)
//Duplicate of MC0_CH0_CR_WCK_CONFIG_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_0_REG                       (0x00014520)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_1_REG                       (0x00014524)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_2_REG                       (0x00014528)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_3_REG                       (0x0001452C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_4_REG                       (0x00014530)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_5_REG                       (0x00014534)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_6_REG                       (0x00014538)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_7_REG                       (0x0001453C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_8_REG                       (0x00014540)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_9_REG                       (0x00014544)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_10_REG                      (0x00014548)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_11_REG                      (0x0001454C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_12_REG                      (0x00014550)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_13_REG                      (0x00014554)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_14_REG                      (0x00014558)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_15_REG                      (0x0001455C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_16_REG                      (0x00014560)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_17_REG                      (0x00014564)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_18_REG                      (0x00014568)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_19_REG                      (0x0001456C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_20_REG                      (0x00014570)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_21_REG                      (0x00014574)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_22_REG                      (0x00014578)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_23_REG                      (0x0001457C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_24_REG                      (0x00014580)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_25_REG                      (0x00014584)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_26_REG                      (0x00014588)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_27_REG                      (0x0001458C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG               (0x00014590)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_1_REG               (0x00014594)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_2_REG               (0x00014598)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_3_REG               (0x0001459C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_4_REG               (0x000145A0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_5_REG               (0x000145A4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_6_REG               (0x000145A8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_7_REG               (0x000145AC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_8_REG               (0x000145B0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_9_REG               (0x000145B4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_10_REG              (0x000145B8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_11_REG              (0x000145BC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG                 (0x000145C0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_1_REG                 (0x000145C4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_2_REG                 (0x000145C8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_3_REG                 (0x000145CC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_4_REG                 (0x000145D0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_5_REG                 (0x000145D4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_6_REG                 (0x000145D8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_CH1_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG                  (0x000145E0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG

#define MC1_CH1_CR_MCMNTS_RDDATA_CTL_REG                               (0x000145E8)
//Duplicate of MC0_CH0_CR_MCMNTS_RDDATA_CTL_REG

#define MC1_CH1_CR_REUT_CH_MISC_REFRESH_CTRL_REG                       (0x00014604)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG

#define MC1_CH1_CR_REUT_CH_MISC_ZQ_CTRL_REG                            (0x00014608)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG

#define MC1_CH1_CR_DDR_MR_PARAMS_REG                                   (0x00014610)
//Duplicate of MC0_CH0_CR_DDR_MR_PARAMS_REG

#define MC1_CH1_CR_DDR_MR_COMMAND_REG                                  (0x00014614)
//Duplicate of MC0_CH0_CR_DDR_MR_COMMAND_REG

#define MC1_CH1_CR_DDR_MR_RESULT_0_REG                                 (0x00014618)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_0_REG

#define MC1_CH1_CR_DDR_MR_RESULT_1_REG                                 (0x0001461C)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_1_REG

#define MC1_CH1_CR_DDR_MR_RESULT_2_REG                                 (0x00014620)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_2_REG

#define MC1_CH1_CR_LPDDR_MR4_RANK_TEMPERATURE_REG                      (0x00014624)
//Duplicate of MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG

#define MC1_CH1_CR_DDR4_MPR_RANK_TEMPERATURE_REG                       (0x00014628)
//Duplicate of MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG

#define MC1_CH1_CR_DESWIZZLE_LOW_ERM_REG                               (0x00014630)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC1_CH1_CR_TC_RFP_REG                                          (0x00014638)
//Duplicate of MC0_CH0_CR_TC_RFP_REG

#define MC1_CH1_CR_TC_RFTP_REG                                         (0x0001463C)
//Duplicate of MC0_CH0_CR_TC_RFTP_REG

#define MC1_CH1_CR_TC_SRFTP_REG                                        (0x00014640)
//Duplicate of MC0_CH0_CR_TC_SRFTP_REG

#define MC1_CH1_CR_MC_REFRESH_STAGGER_REG                              (0x00014644)
//Duplicate of MC0_CH0_CR_MC_REFRESH_STAGGER_REG

#define MC1_CH1_CR_TC_ZQCAL_REG                                        (0x00014648)
//Duplicate of MC0_CH0_CR_TC_ZQCAL_REG

#define MC1_CH1_CR_TC_MR2_SHADDOW_REG                                  (0x0001464C)
//Duplicate of MC0_CH0_CR_TC_MR2_SHADDOW_REG

#define MC1_CH1_CR_TC_MR4_SHADDOW_REG                                  (0x00014650)
//Duplicate of MC0_CH0_CR_TC_MR4_SHADDOW_REG

#define MC1_CH1_CR_MC_INIT_STATE_REG                                   (0x00014654)
//Duplicate of MC0_CH0_CR_MC_INIT_STATE_REG

#define MC1_CH1_CR_WDB_VISA_SEL_REG                                    (0x00014658)
//Duplicate of MC0_CH0_CR_WDB_VISA_SEL_REG

#define MC1_CH1_CR_PM_DIMM_IDLE_ENERGY_REG                             (0x00014660)
//Duplicate of MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_REG

#define MC1_CH1_CR_PM_DIMM_PD_ENERGY_REG                               (0x00014664)
//Duplicate of MC0_CH0_CR_PM_DIMM_PD_ENERGY_REG

#define MC1_CH1_CR_PM_DIMM_ACT_ENERGY_REG                              (0x00014668)
//Duplicate of MC0_CH0_CR_PM_DIMM_ACT_ENERGY_REG

#define MC1_CH1_CR_PM_DIMM_RD_ENERGY_REG                               (0x0001466C)
//Duplicate of MC0_CH0_CR_PM_DIMM_RD_ENERGY_REG

#define MC1_CH1_CR_PM_DIMM_WR_ENERGY_REG                               (0x00014670)
//Duplicate of MC0_CH0_CR_PM_DIMM_WR_ENERGY_REG

#define MC1_CH1_CR_SC_WR_DELAY_REG                                     (0x00014678)
//Duplicate of MC0_CH0_CR_SC_WR_DELAY_REG

#define MC1_CH1_CR_READ_RETURN_DFT_REG                                 (0x0001467C)
//Duplicate of MC0_CH0_CR_READ_RETURN_DFT_REG

#define MC1_CH1_CR_DESWIZZLE_LOW_REG                                   (0x00014680)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC1_CH1_CR_SC_PBR_REG                                          (0x00014688)
//Duplicate of MC0_CH0_CR_SC_PBR_REG

#define MC1_CH1_CR_LPDDR_PASR_REG                                      (0x00014690)
//Duplicate of MC0_CH0_CR_LPDDR_PASR_REG

#define MC1_CH1_CR_TC_LPDDR4_MISC_REG                                  (0x00014694)
//Duplicate of MC0_CH0_CR_TC_LPDDR4_MISC_REG

#define MC1_CH1_CR_DESWIZZLE_HIGH_ERM_REG                              (0x00014698)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC1_CH1_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG                      (0x000146B0)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG

#define MC1_CH1_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG                   (0x000146B0)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG

#define MC1_CH1_CR_DESWIZZLE_HIGH_REG                                  (0x000146B8)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC1_CH1_CR_TC_SREXITTP_REG                                     (0x000146C0)
//Duplicate of MC0_CH0_CR_TC_SREXITTP_REG

#define MC1_CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_REG                       (0x000146C8)
//Duplicate of MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG

#define MC1_CH1_CR_WDB_RD_WR_DFX_DATA_REG                              (0x000146D8)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_DATA_REG

#define MC1_CH1_CR_WDB_RD_WR_DFX_CTL_REG                               (0x000146E0)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_CTL_REG

#define MC1_CH1_CR_REF_FSM_STATUS_REG                                  (0x000146E4)
//Duplicate of MC0_CH0_CR_REF_FSM_STATUS_REG

#define MC1_CH1_CR_WDB_MBIST_0_REG                                     (0x000146E8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC1_CH1_CR_WDB_MBIST_1_REG                                     (0x000146EC)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC1_CH1_CR_RDB_MBIST_REG                                       (0x000146F8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC1_CH1_CR_ECC_INJECT_COUNT_REG                                (0x000146FC)
//Duplicate of MC0_CH0_CR_ECC_INJECT_COUNT_REG

#define MC1_CH1_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG                   (0x00014700)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC1_CH1_CR_PWM_DDR_SUBCH1_RDDATA_COUNTER_REG                   (0x00014708)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC1_CH1_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG                   (0x00014710)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC1_CH1_CR_PWM_DDR_SUBCH1_WRDATA_COUNTER_REG                   (0x00014718)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC1_CH1_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG                   (0x00014720)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH1_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_REG                    (0x00014728)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH1_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG                    (0x00014730)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_CH1_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_REG                    (0x00014738)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_CH1_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG                      (0x00014744)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC1_CH1_CR_DDR4_MR5_RTT_PARK_VALUES_REG                        (0x00014748)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH1_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_REG                  (0x00014750)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH1_CR_DDR4_MR1_RTT_NOM_VALUES_REG                         (0x00014758)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG                     (0x00014760)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_1_REG                     (0x00014768)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_2_REG                     (0x00014770)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_3_REG                     (0x00014778)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_4_REG                     (0x00014780)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_5_REG                     (0x00014788)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_6_REG                     (0x00014790)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH1_CR_LPDDR4_DISCRETE_MR_VALUES_7_REG                     (0x00014798)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_CH1_CR_DDR4_MR0_MR1_CONTENT_REG                            (0x000147A0)
//Duplicate of MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_REG

#define MC1_CH1_CR_DDR4_MR2_MR3_CONTENT_REG                            (0x000147A4)
//Duplicate of MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_REG

#define MC1_CH1_CR_DDR4_MR4_MR5_CONTENT_REG                            (0x000147A8)
//Duplicate of MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_REG

#define MC1_CH1_CR_DDR4_MR6_MR7_CONTENT_REG                            (0x000147AC)
//Duplicate of MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_REG

#define MC1_CH1_CR_DDR4_MR2_RTT_WR_VALUES_REG                          (0x000147B0)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_CH1_CR_DDR4_MR6_VREF_VALUES_0_REG                          (0x000147B8)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_CH1_CR_DDR4_MR6_VREF_VALUES_1_REG                          (0x000147C0)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_CH1_CR_LPDDR_MR_CONTENT_REG                                (0x000147C8)
//Duplicate of MC0_CH0_CR_LPDDR_MR_CONTENT_REG

#define MC1_CH1_CR_MRS_FSM_CONTROL_REG                                 (0x000147D0)
//Duplicate of MC0_CH0_CR_MRS_FSM_CONTROL_REG

#define MC1_CH1_CR_MRS_FSM_RUN_REG                                     (0x000147D8)
//Duplicate of MC0_CH0_CR_MRS_FSM_RUN_REG

#define MC1_CH1_CR_DDR4_MR1_ODIC_VALUES_REG                            (0x000147DC)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC1_CH1_CR_PL_AGENT_CFG_DTF_REG                                (0x000147E0)
//Duplicate of MC0_CH0_CR_PL_AGENT_CFG_DTF_REG

#define MC1_CH1_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_REG                   (0x000147E4)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC1_CH1_CR_DDR4_ECC_DEVICE_VALUES_REG                          (0x000147E8)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC1_CH1_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_REG                    (0x000147F0)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC1_CH1_CR_MCMNTS_SPARE_REG                                    (0x000147FC)
//Duplicate of MC0_CH0_CR_MCMNTS_SPARE_REG

#define MC1_BC_CR_TC_PRE_REG                                           (0x00014C00)
//Duplicate of MC0_CH0_CR_TC_PRE_REG

#define MC1_BC_CR_TC_ACT_REG                                           (0x00014C08)
//Duplicate of MC0_CH0_CR_TC_ACT_REG

#define MC1_BC_CR_TC_RDRD_REG                                          (0x00014C0C)
//Duplicate of MC0_CH0_CR_TC_RDRD_REG

#define MC1_BC_CR_TC_RDWR_REG                                          (0x00014C10)
//Duplicate of MC0_CH0_CR_TC_RDWR_REG

#define MC1_BC_CR_TC_WRRD_REG                                          (0x00014C14)
//Duplicate of MC0_CH0_CR_TC_WRRD_REG

#define MC1_BC_CR_TC_WRWR_REG                                          (0x00014C18)
//Duplicate of MC0_CH0_CR_TC_WRWR_REG

#define MC1_BC_CR_SC_ROUNDTRIP_LATENCY_REG                             (0x00014C20)
//Duplicate of MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_REG

#define MC1_BC_CR_SCHED_CBIT_REG                                       (0x00014C28)
//Duplicate of MC0_CH0_CR_SCHED_CBIT_REG

#define MC1_BC_CR_SCHED_SECOND_CBIT_REG                                (0x00014C2C)
//Duplicate of MC0_CH0_CR_SCHED_SECOND_CBIT_REG

#define MC1_BC_CR_DFT_MISC_REG                                         (0x00014C30)
//Duplicate of MC0_CH0_CR_DFT_MISC_REG

#define MC1_BC_CR_SC_PCIT_REG                                          (0x00014C34)
//Duplicate of MC0_CH0_CR_SC_PCIT_REG

#define MC1_BC_CR_ECC_DFT_REG                                          (0x00014C38)
//Duplicate of MC0_CH0_CR_ECC_DFT_REG

#define MC1_BC_CR_PM_PDWN_CONFIG_REG                                   (0x00014C40)
//Duplicate of MC0_CH0_CR_PM_PDWN_CONFIG_REG

#define MC1_BC_CR_WMM_READ_CONFIG_REG                                  (0x00014C44)
//Duplicate of MC0_CH0_CR_WMM_READ_CONFIG_REG

#define MC1_BC_CR_ECCERRLOG0_REG                                       (0x00014C48)
//Duplicate of MC0_CH0_CR_ECCERRLOG0_REG

#define MC1_BC_CR_ECCERRLOG1_REG                                       (0x00014C4C)
//Duplicate of MC0_CH0_CR_ECCERRLOG1_REG

#define MC1_BC_CR_TC_PWRDN_REG                                         (0x00014C50)
//Duplicate of MC0_CH0_CR_TC_PWRDN_REG

#define MC1_BC_CR_QUEUE_ENTRY_DISABLE_RPQ_REG                          (0x00014C58)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_REG

#define MC1_BC_CR_QUEUE_ENTRY_DISABLE_IPQ_REG                          (0x00014C5C)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_REG

#define MC1_BC_CR_QUEUE_ENTRY_DISABLE_WPQ_REG                          (0x00014C60)
//Duplicate of MC0_CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_REG

#define MC1_BC_CR_SC_WDBWM_REG                                         (0x00014C68)
//Duplicate of MC0_CH0_CR_SC_WDBWM_REG

#define MC1_BC_CR_TC_ODT_REG                                           (0x00014C70)
//Duplicate of MC0_CH0_CR_TC_ODT_REG

#define MC1_BC_CR_MCSCHEDS_SPARE_REG                                   (0x00014C78)
//Duplicate of MC0_CH0_CR_MCSCHEDS_SPARE_REG

#define MC1_BC_CR_SC_ODT_MATRIX_REG                                    (0x00014C80)
//Duplicate of MC0_CH0_CR_SC_ODT_MATRIX_REG

#define MC1_BC_CR_DFT_BLOCK_REG                                        (0x00014C84)
//Duplicate of MC0_CH0_CR_DFT_BLOCK_REG

#define MC1_BC_CR_SC_GS_CFG_REG                                        (0x00014C88)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_REG

#define MC1_BC_CR_SC_PH_THROTTLING_0_REG                               (0x00014C90)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_0_REG

#define MC1_BC_CR_SC_PH_THROTTLING_1_REG                               (0x00014C94)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_1_REG

#define MC1_BC_CR_SC_PH_THROTTLING_2_REG                               (0x00014C98)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_2_REG

#define MC1_BC_CR_SC_PH_THROTTLING_3_REG                               (0x00014C9C)
//Duplicate of MC0_CH0_CR_SC_PH_THROTTLING_3_REG

#define MC1_BC_CR_SC_WPQ_THRESHOLD_REG                                 (0x00014CA0)
//Duplicate of MC0_CH0_CR_SC_WPQ_THRESHOLD_REG

#define MC1_BC_CR_SC_PR_CNT_CONFIG_REG                                 (0x00014CA8)
//Duplicate of MC0_CH0_CR_SC_PR_CNT_CONFIG_REG

#define MC1_BC_CR_REUT_CH_MISC_CKE_CTRL_REG                            (0x00014CB0)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG

#define MC1_BC_CR_REUT_CH_MISC_ODT_CTRL_REG                            (0x00014CB4)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG

#define MC1_BC_CR_SPID_LOW_POWER_CTL_REG                               (0x00014CB8)
//Duplicate of MC0_CH0_CR_SPID_LOW_POWER_CTL_REG

#define MC1_BC_CR_SC_GS_CFG_TRAINING_REG                               (0x00014CBC)
//Duplicate of MC0_CH0_CR_SC_GS_CFG_TRAINING_REG

#define MC1_BC_CR_SCHED_THIRD_CBIT_REG                                 (0x00014CC0)
//Duplicate of MC0_CH0_CR_SCHED_THIRD_CBIT_REG

#define MC1_BC_CR_DEADLOCK_BREAKER_REG                                 (0x00014CC4)
//Duplicate of MC0_CH0_CR_DEADLOCK_BREAKER_REG

#define MC1_BC_CR_XARB_TC_BUBBLE_INJ_REG                               (0x00014CC8)
//Duplicate of MC0_CH0_CR_XARB_TC_BUBBLE_INJ_REG

#define MC1_BC_CR_XARB_CFG_BUBBLE_INJ_REG                              (0x00014CCC)
//Duplicate of MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_REG

#define MC1_BC_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG                  (0x00014CD0)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC1_BC_CR_SC_BLOCKING_RULES_CFG_REG                            (0x00014CD4)
//Duplicate of MC0_CH0_CR_SC_BLOCKING_RULES_CFG_REG

#define MC1_BC_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG                       (0x00014CD8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC1_BC_CR_PWM_DDR_SUBCH1_ACT_COUNTER_REG                       (0x00014CE0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_ACT_COUNTER_REG

#define MC1_BC_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG             (0x00014CE8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC1_BC_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG            (0x00014CE8)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC1_BC_CR_PWM_DDR_SUBCH1_REQ_OCCUPANCY_COUNTER_REG             (0x00014CF0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_REQ_OCCUPANCY_COUNTER_REG

#define MC1_BC_CR_PWM_DDR_SUBCH1_DCLK_ACTIVE_COUNTER_A0_REG            (0x00014CF0)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_DCLK_ACTIVE_COUNTER_A0_REG

#define MC1_BC_CR_WCK_CONFIG_REG                                       (0x00014CF8)
//Duplicate of MC0_CH0_CR_WCK_CONFIG_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_0_REG                        (0x00014D20)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_1_REG                        (0x00014D24)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_2_REG                        (0x00014D28)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_3_REG                        (0x00014D2C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_4_REG                        (0x00014D30)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_5_REG                        (0x00014D34)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_6_REG                        (0x00014D38)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_7_REG                        (0x00014D3C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_8_REG                        (0x00014D40)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_9_REG                        (0x00014D44)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_10_REG                       (0x00014D48)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_11_REG                       (0x00014D4C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_12_REG                       (0x00014D50)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_13_REG                       (0x00014D54)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_14_REG                       (0x00014D58)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_15_REG                       (0x00014D5C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_16_REG                       (0x00014D60)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_17_REG                       (0x00014D64)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_18_REG                       (0x00014D68)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_19_REG                       (0x00014D6C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_20_REG                       (0x00014D70)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_21_REG                       (0x00014D74)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_22_REG                       (0x00014D78)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_23_REG                       (0x00014D7C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_24_REG                       (0x00014D80)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_25_REG                       (0x00014D84)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_26_REG                       (0x00014D88)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_27_REG                       (0x00014D8C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG                (0x00014D90)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_1_REG                (0x00014D94)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_2_REG                (0x00014D98)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_3_REG                (0x00014D9C)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_4_REG                (0x00014DA0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_5_REG                (0x00014DA4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_6_REG                (0x00014DA8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_7_REG                (0x00014DAC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_8_REG                (0x00014DB0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_9_REG                (0x00014DB4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_10_REG               (0x00014DB8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_11_REG               (0x00014DBC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG                  (0x00014DC0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_1_REG                  (0x00014DC4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_2_REG                  (0x00014DC8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_3_REG                  (0x00014DCC)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_4_REG                  (0x00014DD0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_5_REG                  (0x00014DD4)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_SHADOW_VALUES_6_REG                  (0x00014DD8)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG

#define MC1_BC_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG                   (0x00014DE0)
//Duplicate of MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG

#define MC1_BC_CR_MCMNTS_RDDATA_CTL_REG                                (0x00014DE8)
//Duplicate of MC0_CH0_CR_MCMNTS_RDDATA_CTL_REG

#define MC1_BC_CR_REUT_CH_MISC_REFRESH_CTRL_REG                        (0x00014E04)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG

#define MC1_BC_CR_REUT_CH_MISC_ZQ_CTRL_REG                             (0x00014E08)
//Duplicate of MC0_CH0_CR_REUT_CH_MISC_ZQ_CTRL_REG

#define MC1_BC_CR_DDR_MR_PARAMS_REG                                    (0x00014E10)
//Duplicate of MC0_CH0_CR_DDR_MR_PARAMS_REG

#define MC1_BC_CR_DDR_MR_COMMAND_REG                                   (0x00014E14)
//Duplicate of MC0_CH0_CR_DDR_MR_COMMAND_REG

#define MC1_BC_CR_DDR_MR_RESULT_0_REG                                  (0x00014E18)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_0_REG

#define MC1_BC_CR_DDR_MR_RESULT_1_REG                                  (0x00014E1C)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_1_REG

#define MC1_BC_CR_DDR_MR_RESULT_2_REG                                  (0x00014E20)
//Duplicate of MC0_CH0_CR_DDR_MR_RESULT_2_REG

#define MC1_BC_CR_LPDDR_MR4_RANK_TEMPERATURE_REG                       (0x00014E24)
//Duplicate of MC0_CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG

#define MC1_BC_CR_DDR4_MPR_RANK_TEMPERATURE_REG                        (0x00014E28)
//Duplicate of MC0_CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG

#define MC1_BC_CR_DESWIZZLE_LOW_ERM_REG                                (0x00014E30)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC1_BC_CR_TC_RFP_REG                                           (0x00014E38)
//Duplicate of MC0_CH0_CR_TC_RFP_REG

#define MC1_BC_CR_TC_RFTP_REG                                          (0x00014E3C)
//Duplicate of MC0_CH0_CR_TC_RFTP_REG

#define MC1_BC_CR_TC_SRFTP_REG                                         (0x00014E40)
//Duplicate of MC0_CH0_CR_TC_SRFTP_REG

#define MC1_BC_CR_MC_REFRESH_STAGGER_REG                               (0x00014E44)
//Duplicate of MC0_CH0_CR_MC_REFRESH_STAGGER_REG

#define MC1_BC_CR_TC_ZQCAL_REG                                         (0x00014E48)
//Duplicate of MC0_CH0_CR_TC_ZQCAL_REG

#define MC1_BC_CR_TC_MR2_SHADDOW_REG                                   (0x00014E4C)
//Duplicate of MC0_CH0_CR_TC_MR2_SHADDOW_REG

#define MC1_BC_CR_TC_MR4_SHADDOW_REG                                   (0x00014E50)
//Duplicate of MC0_CH0_CR_TC_MR4_SHADDOW_REG

#define MC1_BC_CR_MC_INIT_STATE_REG                                    (0x00014E54)
//Duplicate of MC0_CH0_CR_MC_INIT_STATE_REG

#define MC1_BC_CR_WDB_VISA_SEL_REG                                     (0x00014E58)
//Duplicate of MC0_CH0_CR_WDB_VISA_SEL_REG

#define MC1_BC_CR_PM_DIMM_IDLE_ENERGY_REG                              (0x00014E60)
//Duplicate of MC0_CH0_CR_PM_DIMM_IDLE_ENERGY_REG

#define MC1_BC_CR_PM_DIMM_PD_ENERGY_REG                                (0x00014E64)
//Duplicate of MC0_CH0_CR_PM_DIMM_PD_ENERGY_REG

#define MC1_BC_CR_PM_DIMM_ACT_ENERGY_REG                               (0x00014E68)
//Duplicate of MC0_CH0_CR_PM_DIMM_ACT_ENERGY_REG

#define MC1_BC_CR_PM_DIMM_RD_ENERGY_REG                                (0x00014E6C)
//Duplicate of MC0_CH0_CR_PM_DIMM_RD_ENERGY_REG

#define MC1_BC_CR_PM_DIMM_WR_ENERGY_REG                                (0x00014E70)
//Duplicate of MC0_CH0_CR_PM_DIMM_WR_ENERGY_REG

#define MC1_BC_CR_SC_WR_DELAY_REG                                      (0x00014E78)
//Duplicate of MC0_CH0_CR_SC_WR_DELAY_REG

#define MC1_BC_CR_READ_RETURN_DFT_REG                                  (0x00014E7C)
//Duplicate of MC0_CH0_CR_READ_RETURN_DFT_REG

#define MC1_BC_CR_DESWIZZLE_LOW_REG                                    (0x00014E80)
//Duplicate of MC0_CH0_CR_DESWIZZLE_LOW_ERM_REG

#define MC1_BC_CR_SC_PBR_REG                                           (0x00014E88)
//Duplicate of MC0_CH0_CR_SC_PBR_REG

#define MC1_BC_CR_LPDDR_PASR_REG                                       (0x00014E90)
//Duplicate of MC0_CH0_CR_LPDDR_PASR_REG

#define MC1_BC_CR_TC_LPDDR4_MISC_REG                                   (0x00014E94)
//Duplicate of MC0_CH0_CR_TC_LPDDR4_MISC_REG

#define MC1_BC_CR_DESWIZZLE_HIGH_ERM_REG                               (0x00014E98)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC1_BC_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG                       (0x00014EB0)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_REG

#define MC1_BC_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG                    (0x00014EB0)
//Duplicate of MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_A0_REG

#define MC1_BC_CR_DESWIZZLE_HIGH_REG                                   (0x00014EB8)
//Duplicate of MC0_CH0_CR_DESWIZZLE_HIGH_ERM_REG

#define MC1_BC_CR_TC_SREXITTP_REG                                      (0x00014EC0)
//Duplicate of MC0_CH0_CR_TC_SREXITTP_REG

#define MC1_BC_CR_LP4_DQS_OSCILLATOR_PARAMS_REG                        (0x00014EC8)
//Duplicate of MC0_CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG

#define MC1_BC_CR_WDB_RD_WR_DFX_DATA_REG                               (0x00014ED8)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_DATA_REG

#define MC1_BC_CR_WDB_RD_WR_DFX_CTL_REG                                (0x00014EE0)
//Duplicate of MC0_CH0_CR_WDB_RD_WR_DFX_CTL_REG

#define MC1_BC_CR_REF_FSM_STATUS_REG                                   (0x00014EE4)
//Duplicate of MC0_CH0_CR_REF_FSM_STATUS_REG

#define MC1_BC_CR_WDB_MBIST_0_REG                                      (0x00014EE8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC1_BC_CR_WDB_MBIST_1_REG                                      (0x00014EEC)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC1_BC_CR_RDB_MBIST_REG                                        (0x00014EF8)
//Duplicate of MC0_CH0_CR_WDB_MBIST_0_REG

#define MC1_BC_CR_ECC_INJECT_COUNT_REG                                 (0x00014EFC)
//Duplicate of MC0_CH0_CR_ECC_INJECT_COUNT_REG

#define MC1_BC_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG                    (0x00014F00)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC1_BC_CR_PWM_DDR_SUBCH1_RDDATA_COUNTER_REG                    (0x00014F08)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_RDDATA_COUNTER_REG

#define MC1_BC_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG                    (0x00014F10)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC1_BC_CR_PWM_DDR_SUBCH1_WRDATA_COUNTER_REG                    (0x00014F18)
//Duplicate of MC0_CH0_CR_PWM_DDR_SUBCH0_WRDATA_COUNTER_REG

#define MC1_BC_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG                    (0x00014F20)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_BC_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_REG                     (0x00014F28)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_BC_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG                     (0x00014F30)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_BC_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_REG                     (0x00014F38)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_BC_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG                       (0x00014F44)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC1_BC_CR_DDR4_MR5_RTT_PARK_VALUES_REG                         (0x00014F48)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_BC_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_REG                   (0x00014F50)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_BC_CR_DDR4_MR1_RTT_NOM_VALUES_REG                          (0x00014F58)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_BC_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG                      (0x00014F60)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_BC_CR_LPDDR4_DISCRETE_MR_VALUES_1_REG                      (0x00014F68)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_BC_CR_LPDDR4_DISCRETE_MR_VALUES_2_REG                      (0x00014F70)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_BC_CR_LPDDR4_DISCRETE_MR_VALUES_3_REG                      (0x00014F78)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_BC_CR_LPDDR4_DISCRETE_MR_VALUES_4_REG                      (0x00014F80)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_BC_CR_LPDDR4_DISCRETE_MR_VALUES_5_REG                      (0x00014F88)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_BC_CR_LPDDR4_DISCRETE_MR_VALUES_6_REG                      (0x00014F90)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_BC_CR_LPDDR4_DISCRETE_MR_VALUES_7_REG                      (0x00014F98)
//Duplicate of MC0_CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_REG

#define MC1_BC_CR_DDR4_MR0_MR1_CONTENT_REG                             (0x00014FA0)
//Duplicate of MC0_CH0_CR_DDR4_MR0_MR1_CONTENT_REG

#define MC1_BC_CR_DDR4_MR2_MR3_CONTENT_REG                             (0x00014FA4)
//Duplicate of MC0_CH0_CR_DDR4_MR2_MR3_CONTENT_REG

#define MC1_BC_CR_DDR4_MR4_MR5_CONTENT_REG                             (0x00014FA8)
//Duplicate of MC0_CH0_CR_DDR4_MR4_MR5_CONTENT_REG

#define MC1_BC_CR_DDR4_MR6_MR7_CONTENT_REG                             (0x00014FAC)
//Duplicate of MC0_CH0_CR_DDR4_MR6_MR7_CONTENT_REG

#define MC1_BC_CR_DDR4_MR2_RTT_WR_VALUES_REG                           (0x00014FB0)
//Duplicate of MC0_CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_REG

#define MC1_BC_CR_DDR4_MR6_VREF_VALUES_0_REG                           (0x00014FB8)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_BC_CR_DDR4_MR6_VREF_VALUES_1_REG                           (0x00014FC0)
//Duplicate of MC0_CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_REG

#define MC1_BC_CR_LPDDR_MR_CONTENT_REG                                 (0x00014FC8)
//Duplicate of MC0_CH0_CR_LPDDR_MR_CONTENT_REG

#define MC1_BC_CR_MRS_FSM_CONTROL_REG                                  (0x00014FD0)
//Duplicate of MC0_CH0_CR_MRS_FSM_CONTROL_REG

#define MC1_BC_CR_MRS_FSM_RUN_REG                                      (0x00014FD8)
//Duplicate of MC0_CH0_CR_MRS_FSM_RUN_REG

#define MC1_BC_CR_DDR4_MR1_ODIC_VALUES_REG                             (0x00014FDC)
//Duplicate of MC0_CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_REG

#define MC1_BC_CR_PL_AGENT_CFG_DTF_REG                                 (0x00014FE0)
//Duplicate of MC0_CH0_CR_PL_AGENT_CFG_DTF_REG

#define MC1_BC_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_REG                    (0x00014FE4)
//Duplicate of MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_REG

#define MC1_BC_CR_DDR4_ECC_DEVICE_VALUES_REG                           (0x00014FE8)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC1_BC_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_REG                     (0x00014FF0)
//Duplicate of MC0_CH0_CR_DDR4_ECC_DEVICE_VALUES_REG

#define MC1_BC_CR_MCMNTS_SPARE_REG                                     (0x00014FFC)
//Duplicate of MC0_CH0_CR_MCMNTS_SPARE_REG
#pragma pack(pop)
#endif

#ifndef __MrcMcRegisterStructTgl5xxx_h__
#define __MrcMcRegisterStructTgl5xxx_h__
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
typedef union {
  struct {
    UINT32 DDR_TYPE                                :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 CH_L_MAP                                :  1;  // Bits 4:4
    UINT32                                         :  7;  // Bits 11:5
    UINT32 CH_S_SIZE                               :  8;  // Bits 19:12
    UINT32                                         :  7;  // Bits 26:20
    UINT32 CH_WIDTH                                :  2;  // Bits 28:27
    UINT32                                         :  2;  // Bits 30:29
    UINT32 HalfCacheLineMode                       :  1;  // Bits 31:31
  } Bits;
  struct {
    UINT32 DDR_TYPE                                :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 CH_L_MAP                                :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 STKD_MODE                               :  1;  // Bits 8:8
    UINT32 STKD_MODE_CH1                           :  1;  // Bits 9:9
    UINT32                                         :  2;  // Bits 11:10
    UINT32 CH_S_SIZE                               :  8;  // Bits 19:12
    UINT32                                         :  4;  // Bits 23:20
    UINT32 STKD_MODE_CH_BITS                       :  3;  // Bits 26:24
    UINT32 CH_WIDTH                                :  2;  // Bits 28:27
    UINT32                                         :  2;  // Bits 30:29
    UINT32 HalfCacheLineMode                       :  1;  // Bits 31:31
  } A0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MAD_INTER_CHANNEL_STRUCT;
typedef union {
  struct {
    UINT32 DIMM_L_MAP                              :  1;  // Bits 0:0
    UINT32                                         :  7;  // Bits 7:1
    UINT32 EIM                                     :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 ECC                                     :  2;  // Bits 13:12
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  struct {
    UINT32 DIMM_L_MAP                              :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 RI                                      :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 EIM                                     :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 ECC                                     :  2;  // Bits 13:12
    UINT32                                         :  18;  // Bits 31:14
  } A0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MAD_INTRA_CH0_STRUCT;

typedef MC0_MAD_INTRA_CH0_STRUCT MC0_MAD_INTRA_CH1_STRUCT;
typedef union {
  struct {
    UINT32 DIMM_L_SIZE                             :  7;  // Bits 6:0
    UINT32 DLW                                     :  2;  // Bits 8:7
    UINT32 DLNOR                                   :  2;  // Bits 10:9
    UINT32                                         :  5;  // Bits 15:11
    UINT32 DIMM_S_SIZE                             :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 DSW                                     :  2;  // Bits 25:24
    UINT32 DSNOR                                   :  2;  // Bits 27:26
    UINT32                                         :  1;  // Bits 28:28
    UINT32 DLS_BG0_on_bit_11                       :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MAD_DIMM_CH0_STRUCT;

typedef MC0_MAD_DIMM_CH0_STRUCT MC0_MAD_DIMM_CH1_STRUCT;
typedef union {
  struct {
    UINT32 Spare_RW                                :  12;  // Bits 11:0
    UINT32 VISAByteSel                             :  4;  // Bits 15:12
    UINT32 spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MCDECS_MISC_STRUCT;
typedef union {
  struct {
    UINT32 increase_rcomp                          :  1;  // Bits 0:0
    UINT32 rank2_to_rank1                          :  1;  // Bits 1:1
    UINT32 ovrd_pcu_sr_exit                        :  1;  // Bits 2:2
    UINT32 psmi_freeze_pwm_counters                :  1;  // Bits 3:3
    UINT32 dis_single_ch_sr                        :  1;  // Bits 4:4
    UINT32 dis_other_ch_stolen_ref                 :  1;  // Bits 5:5
    UINT32 ForceSREntry_dft                        :  1;  // Bits 6:6
    UINT32 reserved                                :  2;  // Bits 8:7
    UINT32 ForceSREntry_dft_is_sticky              :  1;  // Bits 9:9
    UINT32                                         :  1;  // Bits 10:10
    UINT32 iosfsb_keep_ISM_active                  :  1;  // Bits 11:11
    UINT32 ignoreRefBetweenSRX2SRE                 :  1;  // Bits 12:12
    UINT32                                         :  1;  // Bits 13:13
    UINT32 dis_cmi_spec_req_early_valid            :  1;  // Bits 14:14
    UINT32 Dis_EFLOW_fwd_data_hack                 :  1;  // Bits 15:15
    UINT32 freeze_visa_values                      :  1;  // Bits 16:16
    UINT32 freeze_visa_values_on_RTB               :  1;  // Bits 17:17
    UINT32 dis_cmi_ep_power_flows                  :  1;  // Bits 18:18
    UINT32 dis_iosf_sb_error_opcodes               :  1;  // Bits 19:19
    UINT32 dis_iosf_sb_error_bar                   :  1;  // Bits 20:20
    UINT32 dis_iosf_sb_error_range                 :  1;  // Bits 21:21
    UINT32 dis_iosf_sb_error_sai                   :  1;  // Bits 22:22
    UINT32 delay_normal_mode_when_temp_read        :  1;  // Bits 23:23
    UINT32 dis_cmi_spec_rsp_cpl_early_valid        :  1;  // Bits 24:24
    UINT32 force_sb_ep_clk_req                     :  1;  // Bits 25:25
    UINT32 dis_cmi_wr_rsp                          :  1;  // Bits 26:26
    UINT32 dis_iosf_sb_clk_gate                    :  1;  // Bits 27:27
    UINT32 dis_glbdrv_clk_gate                     :  1;  // Bits 28:28
    UINT32 dis_reg_clk_gate                        :  1;  // Bits 29:29
    UINT32                                         :  1;  // Bits 30:30
    UINT32 dis_clk_gate                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MCDECS_CBIT_STRUCT;
typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 HASH_MASK                               :  14;  // Bits 19:6
    UINT32                                         :  4;  // Bits 23:20
    UINT32 HASH_LSB_MASK_BIT                       :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 HASH_MODE                               :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_CHANNEL_HASH_STRUCT;
typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 EHASH_MASK                              :  14;  // Bits 19:6
    UINT32                                         :  4;  // Bits 23:20
    UINT32 EHASH_LSB_MASK_BIT                      :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 EHASH_MODE                              :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_CHANNEL_EHASH_STRUCT;
typedef union {
  struct {
    UINT32                                         :  1;  // Bits 0:0
    UINT32 ddr_reset                               :  1;  // Bits 1:1
    UINT32                                         :  1;  // Bits 2:2
    UINT32 refresh_enable                          :  1;  // Bits 3:3
    UINT32                                         :  1;  // Bits 4:4
    UINT32 mc_init_done_ack                        :  1;  // Bits 5:5
    UINT32                                         :  1;  // Bits 6:6
    UINT32 mrc_done                                :  1;  // Bits 7:7
    UINT32                                         :  1;  // Bits 8:8
    UINT32 pure_srx                                :  1;  // Bits 9:9
    UINT32                                         :  1;  // Bits 10:10
    UINT32 mrc_save_gv_point_0                     :  1;  // Bits 11:11
    UINT32 mrc_save_gv_point_1                     :  1;  // Bits 12:12
    UINT32 mrc_save_gv_point_2                     :  1;  // Bits 13:13
    UINT32 mrc_save_gv_point_3                     :  1;  // Bits 14:14
    UINT32                                         :  7;  // Bits 21:15
    UINT32 dclk_enable                             :  1;  // Bits 22:22
    UINT32                                         :  1;  // Bits 23:23
    UINT32 override_sr_enable                      :  1;  // Bits 24:24
    UINT32 override_sr_enable_value                :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MC_INIT_STATE_G_STRUCT;
typedef union {
  struct {
    UINT32 REVISION                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MRC_REVISION_STRUCT;
typedef union {
  struct {
    UINT32 CMI_Source_ID0                          :  5;  // Bits 4:0
    UINT32 CMI_Source_ID1                          :  5;  // Bits 9:5
    UINT32 CMI_Source_ID2                          :  5;  // Bits 14:10
    UINT32 CMI_Source_ID3                          :  5;  // Bits 19:15
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_PWM_PROGRAMMABLE_REQCOUNT_CONFIG_STRUCT;
typedef union {
  struct {
    UINT32 countLow                                :  32;  // Bits 31:0
    UINT32 countHigh                               :  32;  // Bits 63:32
  } Bits;
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } A0Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_PWM_TOTAL_REQCOUNT_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_STRUCT MC0_PWM_PROGRAMMABLE_REQCOUNT_0_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_STRUCT MC0_PWM_PROGRAMMABLE_REQCOUNT_1_A0_STRUCT;
typedef MC0_PWM_TOTAL_REQCOUNT_STRUCT MC0_PWM_PROGRAMMABLE_REQCOUNT_1_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_STRUCT MC0_PWM_RDCAS_COUNT_STRUCT;
typedef union {
  struct {
    UINT32 Idle_timer                              :  16;  // Bits 15:0
    UINT32 SR_Enable                               :  1;  // Bits 16:16
    UINT32 delay_qsync                             :  2;  // Bits 18:17
    UINT32                                         :  13;  // Bits 31:19
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_PM_SREF_CONFIG_STRUCT;
typedef union {
  struct {
    UINT32 VC1_WR_CNFLT                            :  1;  // Bits 0:0
    UINT32 VC1_RD_CNFLT                            :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_ATMC_STS_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_STRUCT MC0_READ_OCCUPANCY_COUNT_STRUCT;
typedef union {
  struct {
    UINT32 stall_until_drain                       :  1;  // Bits 0:0
    UINT32 stall_input                             :  1;  // Bits 1:1
    UINT32                                         :  2;  // Bits 3:2
    UINT32 mc_drained                              :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 sr_state                                :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 stall_state                             :  1;  // Bits 12:12
    UINT32                                         :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_STALL_DRAIN_STRUCT;
typedef union {
  struct {
    UINT32 NonVC1Threshold                         :  4;  // Bits 3:0
    UINT32 VC1RdThreshold                          :  4;  // Bits 7:4
    UINT32 FixedRateEn                             :  1;  // Bits 8:8
    UINT32 HIGH_PRIO_LIM                           :  3;  // Bits 11:9
    UINT32 LOW_PRIO_LIM                            :  3;  // Bits 14:12
    UINT32 spare                                   :  8;  // Bits 22:15
    UINT32                                         :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_IPC_MC_ARB_STRUCT;

typedef MC0_IPC_MC_ARB_STRUCT MC0_IPC_MC_DEC_ARB_STRUCT;
typedef union {
  struct {
    UINT32 RPQ_count                               :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 WPQ_count                               :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 IPQ_count                               :  5;  // Bits 20:16
    UINT32 WPQ_MinSlotsToReq                       :  4;  // Bits 24:21
    UINT32 IPQ_MinSlotsToReq                       :  3;  // Bits 27:25
    UINT32 RPQ_MinSlotsToReq                       :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_QUEUE_CREDIT_C_STRUCT;
typedef union {
  struct {
    UINT32 AddressLow                              :  32;  // Bits 31:0
    UINT32 AddressHigh                             :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_ECC_INJ_ADDR_COMPARE_STRUCT;
typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 REMAPBASELow                            :  12;  // Bits 31:20
    UINT32 REMAPBASEHigh                           :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_REMAPBASE_STRUCT;
typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 REMAPLMTLow                             :  12;  // Bits 31:20
    UINT32 REMAPLMTHigh                            :  7;  // Bits 38:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_REMAPLIMIT_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_STRUCT MC0_PWM_WRCAS_COUNT_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_STRUCT MC0_PWM_COMMAND_COUNT_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_STRUCT MC0_PWM_NON_SR_COUNT_STRUCT;
typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 TOLUD                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_TOLUD_STRUCT;

typedef MC0_PWM_TOTAL_REQCOUNT_STRUCT MC0_PWM_GLB_DRV_OFF_COUNT_STRUCT;
typedef union {
  struct {
    UINT32 sys_addrLow                             :  32;  // Bits 31:0
    UINT32 sys_addrHigh                            :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_STRUCT;

typedef MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_STRUCT MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_1_STRUCT;

typedef MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_STRUCT MC0_GDXC_DDR_SYS_ADD_FILTER_MATCH_0_STRUCT;

typedef MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_STRUCT MC0_GDXC_DDR_SYS_ADD_FILTER_MATCH_1_STRUCT;

typedef MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_STRUCT MC0_GDXC_DDR_SYS_ADD_TRIGGER_MASK_STRUCT;

typedef MC0_GDXC_DDR_SYS_ADD_FILTER_MASK_0_STRUCT MC0_GDXC_DDR_SYS_ADD_TRIGGER_MATCH_STRUCT;
typedef union {
  struct {
    UINT32 Isoch_time_window                       :  17;  // Bits 16:0
    UINT32 Write_starvation_window                 :  11;  // Bits 27:17
    UINT32 VC1_Read_starvation_en                  :  1;  // Bits 28:28
    UINT32 Write_starvation_in_Isoc_en             :  1;  // Bits 29:29
    UINT32 Read_starvation_in_Isoch_en             :  1;  // Bits 30:30
    UINT32 VC0_counter_disable                     :  1;  // Bits 31:31
    UINT32 Read_starvation_window                  :  11;  // Bits 42:32
    UINT32 VC0_read_count                          :  9;  // Bits 51:43
    UINT32 Force_MCVC1Demote                       :  1;  // Bits 52:52
    UINT32 Disable_MCVC1Demote                     :  1;  // Bits 53:53
    UINT32 MC_Ignore_VC1Demote                     :  1;  // Bits 54:54
    UINT32 Ignore_RGBSync                          :  1;  // Bits 55:55
    UINT32 Force_MC_WPriority                      :  1;  // Bits 56:56
    UINT32 Disable_MC_WPriority                    :  1;  // Bits 57:57
    UINT32 allow_cross_vc_blocking                 :  1;  // Bits 58:58
    UINT32 VC1_block_VC0                           :  1;  // Bits 59:59
    UINT32 VC0_block_VC1                           :  1;  // Bits 60:60
    UINT32 Delay_VC1_on_read_starvation            :  1;  // Bits 61:61
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_SC_QOS_STRUCT;

typedef MC0_CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_STRUCT MC0_MCMAINS_GLOBAL_DRIVER_GATE_CFG_STRUCT;

typedef MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_STRUCT MC0_PWM_COUNTERS_DURATION_STRUCT;

typedef MC0_CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_STRUCT MC0_PWM_COUNTERS_DURATION_A0_STRUCT;
typedef union {
  struct {
    UINT32 cmi_req_stall_enable                    :  1;  // Bits 0:0
    UINT32 cmi_req_stall_phase                     :  1;  // Bits 1:1
    UINT32 block_scheduler                         :  4;  // Bits 5:2
    UINT32 pwm_clock_enable                        :  1;  // Bits 6:6
    UINT32 Mock_InSR                               :  1;  // Bits 7:7
    UINT32 dis_other_mc_stolen_ref                 :  1;  // Bits 8:8
    UINT32 allow_blockack_on_pending_srx           :  1;  // Bits 9:9
    UINT32 two_cyc_early_ca_valid_dis              :  1;  // Bits 10:10
    UINT32 two_cyc_early_ckstop_dis                :  1;  // Bits 11:11
    UINT32 dis_spid_cmd_clk_gate                   :  1;  // Bits 12:12
    UINT32                                         :  3;  // Bits 15:13
    UINT32 init_complete_override                  :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MCDECS_SECOND_CBIT_STRUCT;
typedef union {
  struct {
    UINT32 AddressLow                              :  32;  // Bits 31:0
    UINT32 AddressHigh                             :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_ECC_INJ_ADDR_MASK_STRUCT;
typedef union {
  struct {
    UINT32 RW_Isoch_time_window                    :  17;  // Bits 16:0
    UINT32 RW_Write_starvation_window              :  11;  // Bits 27:17
    UINT32                                         :  4;  // Bits 31:28
    UINT32 RW_Read_starvation_window               :  11;  // Bits 42:32
    UINT32 Isoc_during_demote_period_x8            :  8;  // Bits 50:43
    UINT32 Isoc_during_demote_window               :  8;  // Bits 58:51
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_SC_QOS2_STRUCT;
typedef union {
  struct {
    UINT32 Yellow_Decay_x128                       :  9;  // Bits 8:0
    UINT32 Yellow_Threshold                        :  10;  // Bits 18:9
    UINT32                                         :  13;  // Bits 31:19
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_SC_QOS3_STRUCT;
typedef union {
  struct {
    UINT32 normalmode                              :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_NORMALMODE_CFG_STRUCT;
typedef union {
  struct {
    UINT32                                         :  24;  // Bits 23:0
    UINT32 CPGC_ACTIVE                             :  1;  // Bits 24:24
    UINT32                                         :  3;  // Bits 27:25
    UINT32 CPGC_ECC_BYTE                           :  3;  // Bits 30:28
    UINT32 Stall_CPGC_CMI_Req                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MC_CPGC_CMI_STRUCT;
typedef union {
  struct {
    UINT32 Concat_Row2Col                          :  1;  // Bits 0:0
    UINT32 Col_align                               :  3;  // Bits 3:1
    UINT32 Concat_Bank2Row                         :  1;  // Bits 4:4
    UINT32 Concat_Col2Row                          :  1;  // Bits 5:5
    UINT32 Row_align                               :  3;  // Bits 8:6
    UINT32 Concat_BG2Bank                          :  1;  // Bits 9:9
    UINT32 dis_BankGroup                           :  1;  // Bits 10:10
    UINT32 Rank_as_it                              :  1;  // Bits 11:11
    UINT32 channel_is_CID_Zero                     :  1;  // Bits 12:12
    UINT32 Inverse_channel                         :  1;  // Bits 13:13
    UINT32 Delay_cpl_info                          :  1;  // Bits 14:14
    UINT32 Delay_cpl_data                          :  1;  // Bits 15:15
    UINT32 Reset_CPGC                              :  1;  // Bits 16:16
    UINT32 Lock_On_Active_CPGC_CMI_ISM             :  1;  // Bits 17:17
    UINT32 BG1_mask                                :  1;  // Bits 18:18
    UINT32 Rank1_as_ERM_BG1                        :  1;  // Bits 19:19
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_MC_CPGC_MISC_DFT_STRUCT;
typedef union {
  struct {
    UINT32 ERR_ADDRESSLow                          :  32;  // Bits 31:0
    UINT32 ERR_ADDRESSHigh                         :  7;  // Bits 38:32
    UINT32 RESERVED                                :  21;  // Bits 59:39
    UINT32 ERR_SRC                                 :  1;  // Bits 60:60
    UINT32 ERR_TYPE                                :  2;  // Bits 62:61
    UINT32 ERR_STS                                 :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} MC0_PARITYERRLOG_STRUCT;
typedef union {
  struct {
    UINT32 DATA_ERR_EN                             :  8;  // Bits 7:0
    UINT32 ADDR_ERR_EN                             :  1;  // Bits 8:8
    UINT32 BE_ERR_EN                               :  2;  // Bits 10:9
    UINT32 RSVD                                    :  5;  // Bits 15:11
    UINT32 ERR_INJ_MASK                            :  5;  // Bits 20:16
    UINT32 RSVD2                                   :  10;  // Bits 30:21
    UINT32 DATA_ERR_INJ_SRC                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_PARITY_ERR_INJ_STRUCT;
typedef union {
  struct {
    UINT32 ADDR_PARITY_EN                          :  1;  // Bits 0:0
    UINT32 WBE_PARITY_EN                           :  1;  // Bits 1:1
    UINT32 WDATA_PARITY_EN                         :  2;  // Bits 3:2
    UINT32 RDATA_PARITY_EN                         :  1;  // Bits 4:4
    UINT32 RSVD_0                                  :  3;  // Bits 7:5
    UINT32 DIS_PARITY_PCH_EVENT                    :  1;  // Bits 8:8
    UINT32 DIS_PARITY_LOG                          :  1;  // Bits 9:9
    UINT32 RSVD_1                                  :  21;  // Bits 30:10
    UINT32 PARITY_EN                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_PARITY_CONTROL_STRUCT;
typedef union {
  struct {
    UINT32                                         :  4;  // Bits 3:0
    UINT32 MCHTrace                                :  1;  // Bits 4:4
    UINT32 SCHTrace                                :  1;  // Bits 5:5
    UINT32 ECC_EN                                  :  1;  // Bits 6:6
    UINT32 ECC_BYTE_replace                        :  3;  // Bits 9:7
    UINT32 RSVD_16_10                              :  7;  // Bits 16:10
    UINT32 Enable_ACC_Trace                        :  1;  // Bits 17:17
    UINT32 Enable_ReadData_Trace                   :  1;  // Bits 18:18
    UINT32 Enable_WriteData_Trace                  :  1;  // Bits 19:19
    UINT32 DDRPL_Activate                          :  1;  // Bits 20:20
    UINT32 DDRPL_GLB_DRV_GATE_DIS                  :  1;  // Bits 21:21
    UINT32 RSVD_23_22                              :  2;  // Bits 23:22
    UINT32 DTF_ENC_CB                              :  1;  // Bits 24:24
    UINT32                                         :  1;  // Bits 25:25
    UINT32 ddr4_bypass_trace_read                  :  1;  // Bits 26:26
    UINT32 ddr4_bypass_trace_write                 :  1;  // Bits 27:27
    UINT32 Trace_2LM_Tag                           :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_DDRPL_CFG_DTF_STRUCT;
typedef union {
  struct {
    UINT32 Enable_ACC_Window_Filtering             :  1;  // Bits 0:0
    UINT32 Filter_Window_Depth                     :  8;  // Bits 8:1
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_DDRPL_FILTER_DTF_STRUCT;
typedef union {
  struct {
    UINT32                                         :  16;  // Bits 15:0
    UINT32 Read_Data_UserDefined_Bits              :  8;  // Bits 23:16
    UINT32 Write_Data_UserDefined_Bits             :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_DDRPL_DEBUG_DTF_STRUCT;
typedef union {
  struct {
    UINT32 Visa_Qclk_Lane_1_out                    :  8;  // Bits 7:0
    UINT32 Visa_Qclk_Lane_0_out                    :  8;  // Bits 15:8
    UINT32 Visa_Dclk_Lane_1_out                    :  8;  // Bits 23:16
    UINT32 Visa_Dclk_Lane_0_out                    :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_DDRPL_VISA_LANES_STRUCT;
typedef union {
  struct {
    UINT32 VisaLane0_Data_Stage_Dclk_tree          :  2;  // Bits 1:0
    UINT32 VisaLane1_Data_Stage_Dclk_tree          :  2;  // Bits 3:2
    UINT32 VisaLane0_Data_Stage_Qclk_tree          :  2;  // Bits 5:4
    UINT32 VisaLane1_Data_Stage_Qclk_tree          :  2;  // Bits 7:6
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC0_DDRPL_VISA_CFG_DTF_STRUCT;
typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CAMARILLO_MAILBOX_DATA0_PCU_STRUCT;

typedef CAMARILLO_MAILBOX_DATA0_PCU_STRUCT CAMARILLO_MAILBOX_DATA1_PCU_STRUCT;
typedef union {
  struct {
    UINT32 COMMAND                                 :  8;  // Bits 7:0
    UINT32 PARAM1                                  :  8;  // Bits 15:8
    UINT32 PARAM2                                  :  14;  // Bits 29:16
    UINT32                                         :  1;  // Bits 30:30
    UINT32 RUN_BUSY                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CAMARILLO_MAILBOX_INTERFACE_PCU_STRUCT;
typedef union {
  struct {
    UINT32 HIGH_TEMP_INT_ENABLE                    :  1;  // Bits 0:0
    UINT32 LOW_TEMP_INT_ENABLE                     :  1;  // Bits 1:1
    UINT32 PROCHOT_INT_ENABLE                      :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 OUT_OF_SPEC_INT_ENABLE                  :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 THRESHOLD_1_REL_TEMP                    :  7;  // Bits 14:8
    UINT32 THRESHOLD_1_INT_ENABLE                  :  1;  // Bits 15:15
    UINT32 THRESHOLD_2_REL_TEMP                    :  7;  // Bits 22:16
    UINT32 THRESHOLD_2_INT_ENABLE                  :  1;  // Bits 23:23
    UINT32 POWER_INT_ENABLE                        :  1;  // Bits 24:24
    UINT32 TEMPERATURE_AVERAGING_TIME_WINDOW       :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PACKAGE_THERM_CAMARILLO_INTERRUPT_PCU_STRUCT;
typedef union {
  struct {
    UINT32 PostCode                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BIOS_POST_CODE_PCU_STRUCT;
typedef union {
  struct {
    UINT32 EDRAM_EN                                :  1;  // Bits 0:0
    UINT32                                         :  26;  // Bits 26:1
    UINT32 EOPIO_LINK_SPEED_PREFERENCE             :  1;  // Bits 27:27
    UINT32 PKGC_FLUSH_LEVEL                        :  2;  // Bits 29:28
    UINT32 POLICY                                  :  1;  // Bits 30:30
    UINT32 MODE                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} EDRAM_PM_CONTROL_PCU_STRUCT;
typedef union {
  struct {
    UINT32 OLTM_ENABLE                             :  1;  // Bits 0:0
    UINT32 CLTM_ENABLE                             :  1;  // Bits 1:1
    UINT32 REFRESH_2X_MODE                         :  2;  // Bits 3:2
    UINT32 EXTTS_ENABLE                            :  1;  // Bits 4:4
    UINT32 LOCK_PTM_REGS_PCU                       :  1;  // Bits 5:5
    UINT32 PDWN_CONFIG_CTL                         :  1;  // Bits 6:6
    UINT32 DISABLE_DRAM_TS                         :  1;  // Bits 7:7
    UINT32 DDR4_SKIP_REFRESH_EN                    :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_PTM_CTL_PCU_STRUCT;
typedef union {
  struct {
    UINT32 BANDWIDTH_THROTTLE                      :  4;  // Bits 3:0
    UINT32                                         :  28;  // Bits 31:4
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_BANDWIDTH_CONTROL_PCU_STRUCT;
typedef union {
  struct {
    UINT32 THRESHOLD1_INT_ENABLE                   :  1;  // Bits 0:0
    UINT32 THRESHOLD2_INT_ENABLE                   :  1;  // Bits 1:1
    UINT32                                         :  6;  // Bits 7:2
    UINT32 THRESHOLD1                              :  8;  // Bits 15:8
    UINT32 THRESHOLD2                              :  8;  // Bits 23:16
    UINT32 TIME_WINDOW                             :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_THERM_CAMARILLO_INTERRUPT_PCU_STRUCT;
typedef union {
  struct {
    UINT32 DDR_VOLTAGE                             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_VOLTAGE_PCU_STRUCT;
typedef union {
  struct {
    UINT32 LIMIT1_POWER                            :  15;  // Bits 14:0
    UINT32 LIMIT1_ENABLE                           :  1;  // Bits 15:15
    UINT32                                         :  1;  // Bits 16:16
    UINT32 LIMIT1_TIME_WINDOW_Y                    :  5;  // Bits 21:17
    UINT32 LIMIT1_TIME_WINDOW_X                    :  2;  // Bits 23:22
    UINT32                                         :  8;  // Bits 31:24
    UINT32 LIMIT2_POWER                            :  15;  // Bits 46:32
    UINT32 LIMIT2_ENABLE                           :  1;  // Bits 47:47
    UINT32                                         :  1;  // Bits 48:48
    UINT32 LIMIT2_TIME_WINDOW_Y                    :  5;  // Bits 53:49
    UINT32 LIMIT2_TIME_WINDOW_X                    :  2;  // Bits 55:54
    UINT32                                         :  7;  // Bits 62:56
    UINT32 LOCKED                                  :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} DDR_RAPL_LIMIT_PCU_STRUCT;
typedef union {
  struct {
    UINT32 JOULES_CONSUMED                         :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_ENERGY_STATUS_PCU_STRUCT;
typedef union {
  struct {
    UINT32 DURATION                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_RAPL_PERF_STATUS_PCU_STRUCT;
typedef union {
  struct {
    UINT32 COUNTS                                  :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PACKAGE_RAPL_PERF_STATUS_PCU_STRUCT;
typedef union {
  struct {
    UINT32 COST_ESTIMATE                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} EDRAM_COST_ESTIMATE_PCU_STRUCT;
typedef union {
  struct {
    UINT32 STATE                                   :  1;  // Bits 0:0
    UINT32 POLICY                                  :  1;  // Bits 1:1
    UINT32 EOPIO_LINK_SPEED                        :  1;  // Bits 2:2
    UINT32 EOPIO_LINK_SPEED_CHANGE_AVAILABLE       :  1;  // Bits 3:3
    UINT32                                         :  28;  // Bits 31:4
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} EDRAM_STATUS_PCU_STRUCT;
typedef union {
  struct {
    UINT32 PERF_ESTIMATE                           :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} EDRAM_PERF_ESTIMATE_PCU_STRUCT;
typedef union {
  struct {
    UINT32 PRIPTP                                  :  5;  // Bits 4:0
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PRIP_TURBO_PLCY_PCU_STRUCT;
typedef union {
  struct {
    UINT32 SECPTP                                  :  5;  // Bits 4:0
    UINT32                                         :  27;  // Bits 31:5
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} SECP_TURBO_PLCY_PCU_STRUCT;

typedef CAMARILLO_MAILBOX_DATA0_PCU_STRUCT PRIP_NRG_STTS_PCU_STRUCT;

typedef CAMARILLO_MAILBOX_DATA0_PCU_STRUCT SECP_NRG_STTS_PCU_STRUCT;
typedef union {
  struct {
    UINT32 PKG_TDP                                 :  15;  // Bits 14:0
    UINT32                                         :  1;  // Bits 15:15
    UINT32 PKG_MIN_PWR                             :  15;  // Bits 30:16
    UINT32                                         :  1;  // Bits 31:31
    UINT32 PKG_MAX_PWR                             :  15;  // Bits 46:32
    UINT32                                         :  1;  // Bits 47:47
    UINT32 PKG_MAX_WIN                             :  7;  // Bits 54:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PACKAGE_POWER_SKU_PCU_STRUCT;
typedef union {
  struct {
    UINT32 PWR_UNIT                                :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 ENERGY_UNIT                             :  5;  // Bits 12:8
    UINT32                                         :  3;  // Bits 15:13
    UINT32 TIME_UNIT                               :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PACKAGE_POWER_SKU_UNIT_PCU_STRUCT;

typedef CAMARILLO_MAILBOX_DATA0_PCU_STRUCT PACKAGE_ENERGY_STATUS_PCU_STRUCT;
typedef union {
  struct {
    UINT32 DATA                                    :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} EDRAM_TEMPERATURE_PCU_STRUCT;
typedef union {
  struct {
    UINT32                                      : 32;  // Bits 49:0
    UINT32                                         :  18;  // Bits 49:0
    UINT32 PLATFORMID                              :  3;  // Bits 52:50
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PLATFORM_ID_PCU_STRUCT;
typedef union {
  struct {
    UINT32                                         :  8;  // Bits 7:0
    UINT32 MAX_NON_TURBO_LIM_RATIO                 :  8;  // Bits 15:8
    UINT32 SMM_SAVE_CAP                            :  1;  // Bits 16:16
    UINT32                                         :  6;  // Bits 22:17
    UINT32 PPIN_CAP                                :  1;  // Bits 23:23
    UINT32 OCVOLT_OVRD_AVAIL                       :  1;  // Bits 24:24
    UINT32                                         :  1;  // Bits 25:25
    UINT32 DCU_16K_MODE_AVAIL                      :  1;  // Bits 26:26
    UINT32 SAMPLE_PART                             :  1;  // Bits 27:27
    UINT32 PRG_TURBO_RATIO_EN                      :  1;  // Bits 28:28
    UINT32 PRG_TDP_LIM_EN                          :  1;  // Bits 29:29
    UINT32 PRG_TJ_OFFSET_EN                        :  1;  // Bits 30:30
    UINT32 CPUID_FAULTING_EN                       :  1;  // Bits 31:31
    UINT32 LPM_SUPPORT                             :  1;  // Bits 32:32
    UINT32 CONFIG_TDP_LEVELS                       :  2;  // Bits 34:33
    UINT32 PFAT_ENABLE                             :  1;  // Bits 35:35
    UINT32 PEG2DMIDIS_EN                           :  1;  // Bits 36:36
    UINT32 TIMED_MWAIT_ENABLE                      :  1;  // Bits 37:37
    UINT32                                         :  2;  // Bits 39:38
    UINT32 MAX_EFFICIENCY_RATIO                    :  8;  // Bits 47:40
    UINT32 MIN_OPERATING_RATIO                     :  8;  // Bits 55:48
    UINT32 PushPatch_EN                            :  1;  // Bits 56:56
    UINT32 EDRAM_ENABLE                            :  1;  // Bits 57:57
    UINT32 SXP_2LM_EN                              :  1;  // Bits 58:58
    UINT32 SMM_SUPOVR_STATE_LOCK_ENABLE            :  1;  // Bits 59:59
    UINT32 TIO_ENABLE                              :  1;  // Bits 60:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PLATFORM_INFO_PCU_STRUCT;

typedef EDRAM_TEMPERATURE_PCU_STRUCT PACKAGE_TEMPERATURE_PCU_STRUCT;

typedef EDRAM_TEMPERATURE_PCU_STRUCT PP0_TEMPERATURE_PCU_STRUCT;

typedef EDRAM_TEMPERATURE_PCU_STRUCT PP1_TEMPERATURE_PCU_STRUCT;
typedef union {
  struct {
    UINT32 RESERVED                                :  1;  // Bits 0:0
    UINT32 VALID                                   :  1;  // Bits 1:1
    UINT32 RESERVED_BITS                           :  4;  // Bits 5:2
    UINT32 OD                                      :  1;  // Bits 6:6
    UINT32 IM                                      :  1;  // Bits 7:7
    UINT32 NEXT_DEVICE_ACTIVITY                    :  21;  // Bits 28:8
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DEVICE_SHARED_IDLE_DURATION_PCU_STRUCT;
typedef union {
  struct {
    UINT32 USED                                    :  1;  // Bits 0:0
    UINT32 VALID                                   :  1;  // Bits 1:1
    UINT32 RESERVED_BITS                           :  4;  // Bits 5:2
    UINT32 OD                                      :  1;  // Bits 6:6
    UINT32 IM                                      :  1;  // Bits 7:7
    UINT32 NEXT_DEVICE_ACTIVITY                    :  21;  // Bits 28:8
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DEVICE_DEDICATED_IDLE_DURATION_PCU_STRUCT;
typedef union {
  struct {
    UINT32 RPSTT_LIM                               :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RP_STATE_LIMITS_PCU_STRUCT;
typedef union {
  struct {
    UINT32 PKG_PWR_LIM_1                           :  15;  // Bits 14:0
    UINT32 PKG_PWR_LIM_1_EN                        :  1;  // Bits 15:15
    UINT32 PKG_CLMP_LIM_1                          :  1;  // Bits 16:16
    UINT32 PKG_PWR_LIM_1_TIME                      :  7;  // Bits 23:17
    UINT32                                         :  8;  // Bits 31:24
    UINT32 PKG_PWR_LIM_2                           :  15;  // Bits 46:32
    UINT32 PKG_PWR_LIM_2_EN                        :  1;  // Bits 47:47
    UINT32 PKG_CLMP_LIM_2                          :  1;  // Bits 48:48
    UINT32 PKG_PWR_LIM_2_TIME                      :  7;  // Bits 55:49
    UINT32                                         :  7;  // Bits 62:56
    UINT32 PKG_PWR_LIM_LOCK                        :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PACKAGE_RAPL_LIMIT_PCU_STRUCT;
typedef union {
  struct {
    UINT32 IA_PP_PWR_LIM                           :  15;  // Bits 14:0
    UINT32 PWR_LIM_CTRL_EN                         :  1;  // Bits 15:15
    UINT32 PP_CLAMP_LIM                            :  1;  // Bits 16:16
    UINT32 CTRL_TIME_WIN                           :  7;  // Bits 23:17
    UINT32                                         :  7;  // Bits 30:24
    UINT32 PP_PWR_LIM_LOCK                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PRIP_TURBO_PWR_LIM_PCU_STRUCT;
typedef union {
  struct {
    UINT32 NON_IA_PP_PWR_LIM                       :  15;  // Bits 14:0
    UINT32 PWR_LIM_CTRL_EN                         :  1;  // Bits 15:15
    UINT32 PP_CLAMP_LIM                            :  1;  // Bits 16:16
    UINT32 CTRL_TIME_WIN                           :  7;  // Bits 23:17
    UINT32                                         :  7;  // Bits 30:24
    UINT32 SP_PWR_LIM_LOCK                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} SECP_TURBO_PWR_LIM_PCU_STRUCT;
typedef union {
  struct {
    UINT32 MRC_Saving_Rd                           :  8;  // Bits 7:0
    UINT32 MRC_Saving_Wt                           :  8;  // Bits 15:8
    UINT32 MRC_Saving_Cmd                          :  8;  // Bits 23:16
    UINT32 RESERVED                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MRC_ODT_POWER_SAVING_PCU_STRUCT;
typedef union {
  struct {
    UINT32 RESERVED                                :  1;  // Bits 0:0
    UINT32 VALID                                   :  1;  // Bits 1:1
    UINT32 RESERVED_BITS                           :  4;  // Bits 5:2
    UINT32 OD                                      :  1;  // Bits 6:6
    UINT32 IM                                      :  1;  // Bits 7:7
    UINT32 NEXT_DEVICE_ACTIVITY                    :  21;  // Bits 28:8
    UINT32 DISABLE_MDID_EVALUATION                 :  1;  // Bits 29:29
    UINT32 FORCE_MDID_OVERRIDE                     :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DEVICE_IDLE_DURATION_OVERRIDE_PCU_STRUCT;
typedef union {
  struct {
    UINT32                                         :  4;  // Bits 3:0
    UINT32 PECI_CMD                                :  8;  // Bits 11:4
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CHAP_CONFIG_PCU_STRUCT;

typedef CAMARILLO_MAILBOX_DATA0_PCU_STRUCT FFFC_EMI_CONTROL_PCU_STRUCT;

typedef CAMARILLO_MAILBOX_DATA0_PCU_STRUCT FFFC_RFI_CONTROL_PCU_STRUCT;

typedef CAMARILLO_MAILBOX_DATA0_PCU_STRUCT FFFC_RFI_STATUS_PCU_STRUCT;

typedef CAMARILLO_MAILBOX_DATA0_PCU_STRUCT FFFC_FAULT_STATUS_PCU_STRUCT;

typedef CAMARILLO_MAILBOX_DATA0_PCU_STRUCT FFFC_RFI_CONTROL2_PCU_STRUCT;
typedef union {
  struct {
    UINT32 DEBUG_ENERGY_PP0_VALUE                  :  10;  // Bits 9:0
    UINT32 DEBUG_ENERGY_PP1_VALUE                  :  10;  // Bits 19:10
    UINT32 DEBUG_ENERGY_SA_VALUE                   :  10;  // Bits 29:20
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} ENERGY_DEBUG_PCU_STRUCT;
typedef union {
  struct {
    UINT32 SKPDLow                                 :  32;  // Bits 31:0
    UINT32 SKPDHigh                                :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} SSKPD_PCU_STRUCT;
typedef union {
  struct {
    UINT32 PPDN_INIT                               :  12;  // Bits 11:0
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} C2C3TT_PCU_STRUCT;
typedef union {
  struct {
    UINT32 DDR_TIMER_VALUE                         :  13;  // Bits 12:0
    UINT32                                         :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} C2_DDR_TT_PCU_STRUCT;
typedef union {
  struct {
    UINT32 NSTL                                    :  10;  // Bits 9:0
    UINT32 MULTIPLIER                              :  3;  // Bits 12:10
    UINT32                                         :  1;  // Bits 13:13
    UINT32 FORCE_NL                                :  1;  // Bits 14:14
    UINT32 NL_V                                    :  1;  // Bits 15:15
    UINT32 SXL                                     :  10;  // Bits 25:16
    UINT32 SXLM                                    :  3;  // Bits 28:26
    UINT32                                         :  1;  // Bits 29:29
    UINT32 FORCE_SXL                               :  1;  // Bits 30:30
    UINT32 SXL_V                                   :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCIE_ILTR_OVRD_PCU_STRUCT;
typedef union {
  struct {
    UINT32 NL_VALUE                                :  10;  // Bits 9:0
    UINT32 NL_SCALE                                :  3;  // Bits 12:10
    UINT32 NL_RESERVED                             :  2;  // Bits 14:13
    UINT32 NL_VALID                                :  1;  // Bits 15:15
    UINT32 SXL_VALUE                               :  10;  // Bits 25:16
    UINT32 SXL_SCALE                               :  3;  // Bits 28:26
    UINT32 SXL_RESERVED                            :  2;  // Bits 30:29
    UINT32 SXL_VALID                               :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PCIE_ILTR_VAL_PCU_0_STRUCT;

typedef PCIE_ILTR_VAL_PCU_0_STRUCT PCIE_ILTR_VAL_PCU_1_STRUCT;

typedef PCIE_ILTR_VAL_PCU_0_STRUCT PCIE_ILTR_VAL_PCU_2_STRUCT;

typedef PCIE_ILTR_VAL_PCU_0_STRUCT PCIE_ILTR_VAL_PCU_3_STRUCT;

typedef CAMARILLO_MAILBOX_DATA0_PCU_STRUCT BIOS_MAILBOX_DATA_PCU_STRUCT;
typedef union {
  struct {
    UINT32 COMMAND                                 :  8;  // Bits 7:0
    UINT32 PARAM1                                  :  8;  // Bits 15:8
    UINT32 PARAM2                                  :  13;  // Bits 28:16
    UINT32                                         :  2;  // Bits 30:29
    UINT32 RUN_BUSY                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BIOS_MAILBOX_INTERFACE_PCU_STRUCT;
typedef union {
  struct {
    UINT32 RST_CPL                                 :  1;  // Bits 0:0
    UINT32 PCIE_ENUMERATION_DONE                   :  1;  // Bits 1:1
    UINT32 C7_ALLOWED                              :  1;  // Bits 2:2
    UINT32 ENABLE_PCIE_NDA_PG                      :  1;  // Bits 3:3
    UINT32                                         :  28;  // Bits 31:4
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BIOS_RESET_CPL_PCU_STRUCT;
typedef union {
  struct {
    UINT32 REQ_DATA                                :  8;  // Bits 7:0
    UINT32 REQ_TYPE                                :  4;  // Bits 11:8
    UINT32                                         :  4;  // Bits 15:12
    UINT32 GEAR_TYPE                               :  1;  // Bits 16:16
    UINT32 REQ_VDDQ_TX_VOLTAGE                     :  10;  // Bits 26:17
    UINT32 REQ_VDDQ_TX_ICCMAX                      :  4;  // Bits 30:27
    UINT32 RUN_BUSY                                :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC_BIOS_REQ_PCU_STRUCT;
typedef union {
  struct {
    UINT32 MC_FREQ                                 :  8;  // Bits 7:0
    UINT32 MC_FREQ_TYPE                            :  4;  // Bits 11:8
    UINT32                                         :  4;  // Bits 15:12
    UINT32 GEAR_TYPE                               :  1;  // Bits 16:16
    UINT32 VDDQ_TX_VOLTAGE                         :  10;  // Bits 26:17
    UINT32 VDDQ_TX_ICCMAX                          :  4;  // Bits 30:27
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC_BIOS_DATA_PCU_STRUCT;
typedef union {
  struct {
    UINT32 SACG_ENA                                :  1;  // Bits 0:0
    UINT32 MPLL_OFF_ENA                            :  1;  // Bits 1:1
    UINT32 PPLL_OFF_ENA                            :  1;  // Bits 2:2
    UINT32                                         :  5;  // Bits 7:3
    UINT32 SACG_SEN                                :  1;  // Bits 8:8
    UINT32 MPLL_OFF_SEN                            :  1;  // Bits 9:9
    UINT32 MDLL_OFF_SEN                            :  1;  // Bits 10:10
    UINT32 SACG_SREXIT                             :  1;  // Bits 11:11
    UINT32 NSWAKE_SREXIT                           :  1;  // Bits 12:12
    UINT32 SACG_MPLL                               :  1;  // Bits 13:13
    UINT32 MPLL_ON_DE                              :  1;  // Bits 14:14
    UINT32 MDLL_ON_DE                              :  1;  // Bits 15:15
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} SAPMCTL_PCU_STRUCT;
typedef union {
  struct {
    UINT32 COMP_DISABLE                            :  1;  // Bits 0:0
    UINT32 COMP_INTERVAL                           :  4;  // Bits 4:1
    UINT32                                         :  3;  // Bits 7:5
    UINT32 COMP_FORCE                              :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} P_COMP_PCU_STRUCT;
typedef union {
  struct {
    UINT32 COMP_DISABLE                            :  1;  // Bits 0:0
    UINT32 COMP_INTERVAL                           :  4;  // Bits 4:1
    UINT32                                         :  3;  // Bits 7:5
    UINT32 COMP_FORCE                              :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} M_COMP_PCU_STRUCT;
typedef union {
  struct {
    UINT32 UMCNF_CATERR_DIS                        :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} FUSA_CONFIG_PCU_STRUCT;
typedef union {
  struct {
    UINT32 COMPLETION_COUNTER                      :  24;  // Bits 23:0
    UINT32 CRC8                                    :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} FUSA_TASK_COMPLETION_COUNTER_PCU_STRUCT;
typedef union {
  struct {
    UINT32 PCIE_PWR_STATUS                         :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} SAPM_PG_STATUS_PCU_STRUCT;
typedef union {
  struct {
    UINT32 TDP_RATIO                               :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CONFIG_TDP_NOMINAL_PCU_STRUCT;
typedef union {
  struct {
    UINT32 PKG_TDP                                 :  15;  // Bits 14:0
    UINT32                                         :  1;  // Bits 15:15
    UINT32 TDP_RATIO                               :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
    UINT32 PKG_MAX_PWR                             :  15;  // Bits 46:32
    UINT32                                         :  1;  // Bits 47:47
    UINT32 PKG_MIN_PWR                             :  15;  // Bits 62:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CONFIG_TDP_LEVEL1_PCU_STRUCT;

typedef CONFIG_TDP_LEVEL1_PCU_STRUCT CONFIG_TDP_LEVEL2_PCU_STRUCT;
typedef union {
  struct {
    UINT32 TDP_LEVEL                               :  2;  // Bits 1:0
    UINT32                                         :  29;  // Bits 30:2
    UINT32 CONFIG_TDP_LOCK                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CONFIG_TDP_CONTROL_PCU_STRUCT;
typedef union {
  struct {
    UINT32 MAX_NON_TURBO_RATIO                     :  8;  // Bits 7:0
    UINT32                                         :  23;  // Bits 30:8
    UINT32 TURBO_ACTIVATION_RATIO_LOCK             :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} TURBO_ACTIVATION_RATIO_PCU_STRUCT;
typedef union {
  struct {
    UINT32 MC_TIMING_RUNTIME_OC_ENABLED            :  1;  // Bits 0:0
    UINT32 RSVD_0                                  :  1;  // Bits 1:1
    UINT32 RSVD_1                                  :  1;  // Bits 2:2
    UINT32 RSVD_2                                  :  1;  // Bits 3:3
    UINT32                                         :  28;  // Bits 31:4
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} OC_STATUS_PCU_STRUCT;

#pragma pack(pop)
#endif

#ifndef __MrcMcRegisterStructIcl5xxx_h__
#define __MrcMcRegisterStructIcl5xxx_h__
/** @file
  This file was automatically generated. Modify at your own risk.
  Note that no error checking is done in these functions so ensure that the correct values are passed.

@copyright
  Copyright (c) 2010 - 2017 Intel Corporation. All rights reserved
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
    UINT32 ECHM                                    :  1;  // Bits 3:3
    UINT32 CH_L_MAP                                :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 STKD_MODE                               :  1;  // Bits 8:8
    UINT32 STKD_MODE_CH1                           :  1;  // Bits 9:9
    UINT32                                         :  2;  // Bits 11:10
    UINT32 CH_S_SIZE                               :  8;  // Bits 19:12
    UINT32                                         :  4;  // Bits 23:20
    UINT32 STKD_MODE_CH_BITS                       :  3;  // Bits 26:24
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MAD_INTER_CHANNEL_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_MAP                              :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 RI                                      :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 EIM                                     :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 ECC                                     :  2;  // Bits 13:12
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MAD_INTRA_CH0_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_MAP                              :  1;  // Bits 0:0
    UINT32                                         :  3;  // Bits 3:1
    UINT32 RI                                      :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 EIM                                     :  1;  // Bits 8:8
    UINT32                                         :  3;  // Bits 11:9
    UINT32 ECC                                     :  2;  // Bits 13:12
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MAD_INTRA_CH1_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_SIZE                             :  7;  // Bits 6:0
    UINT32 DLW                                     :  2;  // Bits 8:7
    UINT32 DLNOR                                   :  2;  // Bits 10:9
    UINT32 DL8Gb                                   :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 DIMM_S_SIZE                             :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 DSW                                     :  2;  // Bits 25:24
    UINT32 DSNOR                                   :  2;  // Bits 27:26
    UINT32 DS8Gb                                   :  1;  // Bits 28:28
    UINT32 DLS_BG0_on_bit_11                       :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MAD_DIMM_CH0_STRUCT;

typedef union {
  struct {
    UINT32 DIMM_L_SIZE                             :  7;  // Bits 6:0
    UINT32 DLW                                     :  2;  // Bits 8:7
    UINT32 DLNOR                                   :  2;  // Bits 10:9
    UINT32 DL8Gb                                   :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 DIMM_S_SIZE                             :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 DSW                                     :  2;  // Bits 25:24
    UINT32 DSNOR                                   :  2;  // Bits 27:26
    UINT32 DS8Gb                                   :  1;  // Bits 28:28
    UINT32 DLS_BG0_on_bit_11                       :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MAD_DIMM_CH1_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  16;  // Bits 15:0
    UINT32 spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_MISC_STRUCT;

typedef union {
  struct {
    UINT32 increase_rcomp                          :  1;  // Bits 0:0
    UINT32 rank2_to_rank1                          :  1;  // Bits 1:1
    UINT32 ovrd_pcu_sr_exit                        :  1;  // Bits 2:2
    UINT32 psmi_freeze_pwm_counters                :  1;  // Bits 3:3
    UINT32 dis_single_ch_sr                        :  1;  // Bits 4:4
    UINT32 dis_other_ch_stolen_ref                 :  1;  // Bits 5:5
    UINT32 ForceSREntry_dft                        :  1;  // Bits 6:6
    UINT32 delay_qsync                             :  2;  // Bits 8:7
    UINT32 ForceSREntry_dft_is_sticky              :  1;  // Bits 9:9
    UINT32 iosfsb_npclaim_as_in_cnl_a0             :  1;  // Bits 10:10
    UINT32 iosfsb_keep_ISM_active                  :  1;  // Bits 11:11
    UINT32 ignoreRefBetweenSRX2SRE                 :  1;  // Bits 12:12
    UINT32 Dec_Bypass_Dis                          :  1;  // Bits 13:13
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
    UINT32 ignore_spid_lp4_calc_in_prgs            :  1;  // Bits 30:30
    UINT32 dis_clk_gate                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_CBIT_STRUCT;

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
} CHANNEL_HASH_STRUCT;

typedef union {
  struct {
    UINT32                                         :  6;  // Bits 5:0
    UINT32 EHASH_MASK                              :  14;  // Bits 19:6
    UINT32                                         :  4;  // Bits 23:20
    UINT32 EHASH_LSB_MASK_BIT                      :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 EHASH_MODE                              :  1;  // Bits 28:28
    UINT32 MLMC_IS_BA0                             :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CHANNEL_EHASH_STRUCT;

typedef union {
  struct {
    UINT32 pu_mrc_done                             :  1;  // Bits 0:0
    UINT32 ddr_reset                               :  1;  // Bits 1:1
    UINT32                                         :  1;  // Bits 2:2
    UINT32 refresh_enable                          :  1;  // Bits 3:3
    UINT32                                         :  1;  // Bits 4:4
    UINT32 mc_init_done_ack                        :  1;  // Bits 5:5
    UINT32                                         :  1;  // Bits 6:6
    UINT32 mrc_done                                :  1;  // Bits 7:7
    UINT32 safe_sr                                 :  1;  // Bits 8:8
    UINT32 pure_srx                                :  1;  // Bits 9:9
    UINT32                                         :  1;  // Bits 10:10
    UINT32 mrc_save_low                            :  1;  // Bits 11:11
    UINT32 mrc_save_med                            :  1;  // Bits 12:12
    UINT32 mrc_save_high                           :  1;  // Bits 13:13
    UINT32                                         :  8;  // Bits 21:14
    UINT32 dclk_enable                             :  1;  // Bits 22:22
    UINT32                                         :  1;  // Bits 23:23
    UINT32 override_sr_enable                      :  1;  // Bits 24:24
    UINT32 override_sr_enable_value                :  1;  // Bits 25:25
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC_INIT_STATE_G_STRUCT;

typedef union {
  struct {
    UINT32 REVISION                                :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MRC_REVISION_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PWM_GT_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PWM_IA_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PWM_IO_REQCOUNT_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PWM_RDDATA_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PWM_WRDATA_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PWM_COMMAND_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PWM_NON_SR_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 Idle_timer                              :  16;  // Bits 15:0
    UINT32 SR_Enable                               :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PM_SREF_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 VC1_WR_CNFLT                            :  1;  // Bits 0:0
    UINT32 VC1_RD_CNFLT                            :  1;  // Bits 1:1
    UINT32                                         :  30;  // Bits 31:2
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} ATMC_STS_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} READ_OCCUPANCY_COUNT_STRUCT;

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
} STALL_DRAIN_STRUCT;

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
} IPC_MC_ARB_STRUCT;

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
} IPC_MC_DEC_ARB_STRUCT;

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
} QUEUE_CREDIT_C_STRUCT;

typedef union {
  struct {
    UINT32 count                                   :  16;  // Bits 15:0
    UINT32 First_Rcomp_done                        :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RCOMP_TIMER_STRUCT;

typedef union {
  struct {
    UINT32 AddressLow                              :  32;  // Bits 31:0
    UINT32 AddressHigh                             :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} ECC_INJ_ADDR_COMPARE_STRUCT;

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
} REMAPBASE_STRUCT;

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
} REMAPLIMIT_STRUCT;

typedef union {
  struct {
    UINT32                                         :  20;  // Bits 19:0
    UINT32 TOLUD                                   :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} TOLUD_STRUCT;

typedef union {
  struct {
    UINT32 lock_addr_map                           :  1;  // Bits 0:0
    UINT32 lock_mc_config                          :  1;  // Bits 1:1
    UINT32 lock_iosav_init                         :  1;  // Bits 2:2
    UINT32 lock_pwr_mngment                        :  1;  // Bits 3:3
    UINT32                                         :  3;  // Bits 6:4
    UINT32 lock_mc_dft                             :  1;  // Bits 7:7
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MC_LOCK_STRUCT;

typedef union {
  struct {
    UINT32 sys_addrLow                             :  32;  // Bits 31:0
    UINT32 sys_addrHigh                            :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} GDXC_DDR_SYS_ADD_FILTER_MASK_0_STRUCT;

typedef union {
  struct {
    UINT32 sys_addrLow                             :  32;  // Bits 31:0
    UINT32 sys_addrHigh                            :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} GDXC_DDR_SYS_ADD_FILTER_MASK_1_STRUCT;

typedef union {
  struct {
    UINT32 sys_addrLow                             :  32;  // Bits 31:0
    UINT32 sys_addrHigh                            :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} GDXC_DDR_SYS_ADD_FILTER_MATCH_0_STRUCT;

typedef union {
  struct {
    UINT32 sys_addrLow                             :  32;  // Bits 31:0
    UINT32 sys_addrHigh                            :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} GDXC_DDR_SYS_ADD_FILTER_MATCH_1_STRUCT;

typedef union {
  struct {
    UINT32 sys_addrLow                             :  32;  // Bits 31:0
    UINT32 sys_addrHigh                            :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} GDXC_DDR_SYS_ADD_TRIGGER_MASK_STRUCT;

typedef union {
  struct {
    UINT32 sys_addrLow                             :  32;  // Bits 31:0
    UINT32 sys_addrHigh                            :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} GDXC_DDR_SYS_ADD_TRIGGER_MATCH_STRUCT;

typedef union {
  struct {
    UINT32 Isoch_time_window                       :  17;  // Bits 16:0
    UINT32 Write_starvation_window                 :  11;  // Bits 27:17
    UINT32 Read_starvation_windowLow               :  4;  // Bits 31:28
    UINT32 Read_starvation_windowHigh              :  7;  // Bits 38:32
    UINT32 VC0_read_count                          :  9;  // Bits 47:39
    UINT32 VC1_Read_starvation_en                  :  1;  // Bits 48:48
    UINT32 Write_starvation_in_Isoc_en             :  1;  // Bits 49:49
    UINT32 Read_starvation_in_Isoch_en             :  1;  // Bits 50:50
    UINT32 VC0_counter_disable                     :  1;  // Bits 51:51
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
} SC_QOS_STRUCT;

typedef union {
  struct {
    UINT32 GLB_GRACE_CNT                           :  8;  // Bits 7:0
    UINT32 GLB_DRV_GATE_DIS                        :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCMAINS_GLOBAL_DRIVER_GATE_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PWM_COUNTERS_DURATION_STRUCT;

typedef union {
  struct {
    UINT32 cmi_req_stall_enable                    :  1;  // Bits 0:0
    UINT32 cmi_req_stall_phase                     :  1;  // Bits 1:1
    UINT32 block_scheduler                         :  4;  // Bits 5:2
    UINT32 Mock_InSR                               :  1;  // Bits 6:6
    UINT32 allow_blockack_on_pending_srx           :  1;  // Bits 7:7
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MCDECS_SECOND_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 AddressLow                              :  32;  // Bits 31:0
    UINT32 AddressHigh                             :  1;  // Bits 32:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} ECC_INJ_ADDR_MASK_STRUCT;

typedef union {
  struct {
    UINT32 RW_Isoch_time_window                    :  17;  // Bits 16:0
    UINT32 RW_Write_starvation_window              :  11;  // Bits 27:17
    UINT32 RW_Read_starvation_windowLow            :  4;  // Bits 31:28
    UINT32 RW_Read_starvation_windowHigh           :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Isoc_during_demote_period_x8            :  8;  // Bits 47:40
    UINT32 Isoc_during_demote_window               :  8;  // Bits 55:48
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} SC_QOS2_STRUCT;

typedef union {
  struct {
    UINT32 Yellow_Decay_x128                       :  9;  // Bits 8:0
    UINT32 Yellow_Threshold                        :  10;  // Bits 18:9
    UINT32                                         :  13;  // Bits 31:19
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} SC_QOS3_STRUCT;

typedef union {
  struct {
    UINT32 normalmode                              :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} NORMALMODE_CFG_STRUCT;

typedef union {
  struct {
    UINT32 DRAM_technology                         :  3;  // Bits 2:0 // Keep for ICL A0 compatibility
    UINT32 ECHM                                    :  1;  // Bits 3:3 // Keep for ICL A0 compatibility
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
} DDRPL_CFG_DTF_STRUCT;

typedef union {
  struct {
    UINT32 Enable_ACC_Window_Filtering             :  1;  // Bits 0:0
    UINT32 Filter_Window_Depth                     :  8;  // Bits 8:1
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_FILTER_DTF_STRUCT;

typedef union {
  struct {
    UINT32                                         :  16;  // Bits 15:0
    UINT32 Read_Data_UserDefined_Bits              :  8;  // Bits 23:16
    UINT32 Write_Data_UserDefined_Bits             :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDRPL_DEBUG_DTF_STRUCT;

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
} DDRPL_VISA_LANES_STRUCT;

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
} DDRPL_VISA_CFG_DTF_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CAMARILLO_MAILBOX_DATA0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CAMARILLO_MAILBOX_DATA1_PCU_STRUCT;

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
    UINT32 SCALEFACTOR                             :  3;  // Bits 2:0
    UINT32                                         :  29;  // Bits 31:3
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_ENERGY_SCALEFACTOR_PCU_STRUCT;

typedef union {
  struct {
    UINT32 CH0                                     :  8;  // Bits 7:0
    UINT32 CH1                                     :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_STRUCT;

typedef union {
  struct {
    UINT32 CH0_DIMM0                               :  2;  // Bits 1:0
    UINT32 CH0_DIMM1                               :  2;  // Bits 3:2
    UINT32                                         :  4;  // Bits 7:4
    UINT32 CH1_DIMM0                               :  2;  // Bits 9:8
    UINT32 CH1_DIMM1                               :  2;  // Bits 11:10
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_THERM_PERDIMM_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_WARM_THRESHOLD_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_WARM_THRESHOLD_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_HOT_THRESHOLD_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_HOT_THRESHOLD_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 ENABLE_WARM_INTERRUPT                   :  1;  // Bits 0:0
    UINT32                                         :  1;  // Bits 1:1
    UINT32 ENABLE_HOT_INTERRUPT                    :  1;  // Bits 2:2
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ENABLE_2X_REFRESH_INTERRUPT             :  1;  // Bits 4:4
    UINT32                                         :  1;  // Bits 5:5
    UINT32 ENABLE_OOS_TEMP_INTERRUPT               :  1;  // Bits 6:6
    UINT32                                         :  1;  // Bits 7:7
    UINT32 ENABLE_THRESHOLD1_INTERRUPT             :  1;  // Bits 8:8
    UINT32                                         :  1;  // Bits 9:9
    UINT32 ENABLE_THRESHOLD2_INTERRUPT             :  1;  // Bits 10:10
    UINT32                                         :  5;  // Bits 15:11
    UINT32 POLICY_FREE_THRESHOLD1                  :  8;  // Bits 23:16
    UINT32 POLICY_FREE_THRESHOLD2                  :  8;  // Bits 31:24
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
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_DIMM_TEMPERATURE_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_DIMM_TEMPERATURE_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 TEMPERATURE                             :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_DIMM_HOTTEST_ABSOLUTE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 TEMPERATURE                             :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_DIMM_HOTTEST_RELATIVE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  16;  // Bits 15:0
    UINT32 DIMM1                                   :  16;  // Bits 31:16
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} DDR_THROTTLE_DURATION_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  16;  // Bits 15:0
    UINT32 DIMM1                                   :  16;  // Bits 31:16
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} DDR_THROTTLE_DURATION_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_WARM_BUDGET_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_WARM_BUDGET_CH1_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_HOT_BUDGET_CH0_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0                                   :  8;  // Bits 7:0
    UINT32 DIMM1                                   :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} DDR_HOT_BUDGET_CH1_PCU_STRUCT;

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

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PRIP_NRG_STTS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} SECP_NRG_STTS_PCU_STRUCT;

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

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PACKAGE_ENERGY_STATUS_PCU_STRUCT;

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

typedef union {
  struct {
    UINT32 DATA                                    :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PACKAGE_TEMPERATURE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PP0_TEMPERATURE_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PP1_TEMPERATURE_PCU_STRUCT;

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
    UINT32 RP0_CAP                                 :  8;  // Bits 7:0
    UINT32 RP1_CAP                                 :  8;  // Bits 15:8
    UINT32 RPN_CAP                                 :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} RP_STATE_CAP_PCU_STRUCT;

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

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} FFFC_EMI_CONTROL_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} FFFC_RFI_CONTROL_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} FFFC_RFI_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} FFFC_FAULT_STATUS_PCU_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} FFFC_RFI_CONTROL2_PCU_STRUCT;

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
} PCIE_ILTR_VAL_PCU_1_STRUCT;

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
} PCIE_ILTR_VAL_PCU_2_STRUCT;

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
} PCIE_ILTR_VAL_PCU_3_STRUCT;

typedef union {
  struct {
    UINT32 DATA                                    :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BIOS_MAILBOX_DATA_PCU_STRUCT;

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
    UINT32                                         :  14;  // Bits 30:17
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
    UINT32                                         :  15;  // Bits 31:17
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
} CONFIG_TDP_LEVEL2_PCU_STRUCT;

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

typedef union {
  struct {
    UINT32 BCLK_FREQ                               :  32;  // Bits 31:0
    UINT32 PCIECLK_FREQ                            :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BCLK_FREQ_STRUCT;

#pragma pack(pop)
#endif

#ifndef __MrcMcRegisterStructIcl4xxx_h__
#define __MrcMcRegisterStructIcl4xxx_h__
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
    UINT32 tRP                                     :  6;  // Bits 5:0
    UINT32 tRPab_ext                               :  3;  // Bits 8:6
    UINT32 tRAS                                    :  7;  // Bits 15:9
    UINT32 tRDPRE                                  :  5;  // Bits 20:16
    UINT32 tPPD                                    :  3;  // Bits 23:21
    UINT32 tWRPRE                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_PRE_STRUCT;

typedef union {
  struct {
    UINT32 tFAW                                    :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 tRRD_sg                                 :  5;  // Bits 12:8
    UINT32 tRRD_dg                                 :  5;  // Bits 17:13
    UINT32 derating_ext                            :  3;  // Bits 20:18
    UINT32 tRCD_wr                                 :  6;  // Bits 26:21
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_ACT_STRUCT;

typedef union {
  struct {
    UINT32 tRDRD_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDRD_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_RDRD_STRUCT;

typedef union {
  struct {
    UINT32 tRDWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_RDWR_STRUCT;

typedef union {
  struct {
    UINT32 tWRRD_sg                                :  8;  // Bits 7:0
    UINT32 tWRRD_dg                                :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 tWRRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_WRRD_STRUCT;

typedef union {
  struct {
    UINT32 tWRWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tWRWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tWRWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_WRWR_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_latency                          :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank_1_latency                          :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank_2_latency                          :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank_3_latency                          :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank_4_latency                          :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank_5_latency                          :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank_6_latency                          :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank_7_latency                          :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_SC_ROUNDTRIP_LATENCY_STRUCT;

typedef union {
  struct {
    UINT32 dis_opp_cas                             :  1;  // Bits 0:0
    UINT32 dis_opp_is_cas                          :  1;  // Bits 1:1
    UINT32 dis_opp_ras                             :  1;  // Bits 2:2
    UINT32 dis_opp_is_ras                          :  1;  // Bits 3:3
    UINT32 dis_2c_byp                              :  1;  // Bits 4:4
    UINT32 dis_deprd_opt                           :  1;  // Bits 5:5
    UINT32 dis_pt_it                               :  1;  // Bits 6:6
    UINT32 dis_prcnt_ring                          :  1;  // Bits 7:7
    UINT32 dis_prcnt_sa                            :  1;  // Bits 8:8
    UINT32 dis_blkr_ph                             :  1;  // Bits 9:9
    UINT32 dis_blkr_pe                             :  1;  // Bits 10:10
    UINT32 dis_blkr_pm                             :  1;  // Bits 11:11
    UINT32 dis_odt                                 :  1;  // Bits 12:12
    UINT32 OE_alw_off                              :  1;  // Bits 13:13
    UINT32 block_rpq                               :  1;  // Bits 14:14
    UINT32 block_ipq                               :  1;  // Bits 15:15
    UINT32 block_wpq                               :  1;  // Bits 16:16
    UINT32 dis_zq                                  :  1;  // Bits 17:17
    UINT32 dis_tt                                  :  1;  // Bits 18:18
    UINT32 dis_opp_ref                             :  1;  // Bits 19:19
    UINT32 long_zq                                 :  1;  // Bits 20:20
    UINT32 dis_srx_zq                              :  1;  // Bits 21:21
    UINT32 serialize_zq                            :  1;  // Bits 22:22
    UINT32 zq_fast_exec                            :  1;  // Bits 23:23
    UINT32 dis_starved_read_rank_block             :  1;  // Bits 24:24
    UINT32 dis_idle_preempt                        :  1;  // Bits 25:25
    UINT32 find_first_allocation                   :  1;  // Bits 26:26
    UINT32 duplicate_spid_rank                     :  1;  // Bits 27:27
    UINT32 wio_merge_lpmode_2_3                    :  1;  // Bits 28:28
    UINT32 dis_5cyc_write_gap                      :  1;  // Bits 29:29
    UINT32 dis_5cyc_read_gap                       :  1;  // Bits 30:30
    UINT32 dis_clk_gate                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SCHED_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 dis_srx_mr4                             :  1;  // Bits 0:0
    UINT32 dis_ck_tristate                         :  1;  // Bits 1:1
    UINT32 dis_burst_ref_limit                     :  1;  // Bits 2:2
    UINT32 dis_bus_retain                          :  1;  // Bits 3:3
    UINT32 dis_async_odt                           :  1;  // Bits 4:4
    UINT32 dis_SRX_reset                           :  1;  // Bits 5:5
    UINT32 SPARE_CBIT                              :  1;  // Bits 6:6
    UINT32 dis_SRX_MRS_MR4                         :  1;  // Bits 7:7
    UINT32 dis_opp_ref_idle_delay                  :  1;  // Bits 8:8
    UINT32 dis_ignore_1st_trefi                    :  1;  // Bits 9:9
    UINT32 echo_mask                               :  9;  // Bits 18:10
    UINT32 dis_early_go                            :  1;  // Bits 19:19
    UINT32 dis_new_wr_to_full                      :  1;  // Bits 20:20
    UINT32 WIO2_DBIac_Dis                          :  1;  // Bits 21:21
    UINT32 drainless_SAGV_do_zq                    :  1;  // Bits 22:22
    UINT32 do_temp_reading_after_drainless_SAGV    :  1;  // Bits 23:23
    UINT32 ignore_refresh_between_SR               :  1;  // Bits 24:24
    UINT32 DisWrActThrottleOnAnyRead               :  1;  // Bits 25:25
    UINT32 enable_fdata_nak                        :  1;  // Bits 26:26
    UINT32 spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SCHED_SECOND_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 WDAR                                    :  1;  // Bits 0:0
    UINT32 WDB_Block_En                            :  1;  // Bits 1:1
    UINT32                                         :  2;  // Bits 3:2
    UINT32 isolate_data_return                     :  1;  // Bits 4:4
    UINT32                                         :  12;  // Bits 16:5
    UINT32 dft_block_enable                        :  1;  // Bits 17:17
    UINT32 SAM_overloading                         :  3;  // Bits 20:18
    UINT32                                         :  3;  // Bits 23:21
    UINT32 Stretch_mode_en                         :  1;  // Bits 24:24
    UINT32 STF                                     :  5;  // Bits 29:25
    UINT32 Stretch_delay_from_write                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DFT_MISC_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Inject                              :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ECC_correction_disable                  :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 DIS_MCA_LOG                             :  1;  // Bits 8:8
    UINT32 DIS_PCH_EVENT                           :  1;  // Bits 9:9
    UINT32 DIS_RCH_POISON                          :  1;  // Bits 10:10
    UINT32 DIS_RCH_ERROR                           :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 ECC_trigger                             :  2;  // Bits 17:16
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_ECC_DFT_STRUCT;

typedef union {
  struct {
    UINT32 PCIT                                    :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 PCIT_GT                                 :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_PCIT_STRUCT;

typedef union {
  struct {
    UINT32 PDWN_idle_counter                       :  12;  // Bits 11:0
    UINT32 APD                                     :  1;  // Bits 12:12
    UINT32 PPD                                     :  1;  // Bits 13:13
    UINT32 Slow_Exit                               :  1;  // Bits 14:14
    UINT32 Global_PD                               :  1;  // Bits 15:15
    UINT32 TT_idle_counter                         :  8;  // Bits 23:16
    UINT32 dis_cke_tt                              :  1;  // Bits 24:24
    UINT32 write_threshold                         :  6;  // Bits 30:25
    UINT32 allow_opp_ref_below_write_threhold      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_PM_PDWN_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Dis_Opp_rd                              :  1;  // Bits 0:0
    UINT32 ACT_Enable                              :  1;  // Bits 1:1
    UINT32 PRE_Enable                              :  1;  // Bits 2:2
    UINT32 MAX_RPQ_CAS                             :  4;  // Bits 6:3
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_WMM_READ_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 CERRSTS                                 :  1;  // Bits 0:0
    UINT32 MERRSTS                                 :  1;  // Bits 1:1
    UINT32                                         :  14;  // Bits 15:2
    UINT32 ERRSYND                                 :  8;  // Bits 23:16
    UINT32 ERRCHUNK                                :  3;  // Bits 26:24
    UINT32 ERRRANK                                 :  2;  // Bits 28:27
    UINT32 ERRBANK                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_ECCERRLOG0_STRUCT;

typedef union {
  struct {
    UINT32 ERRROW                                  :  17;  // Bits 16:0
    UINT32 ERRCOL                                  :  12;  // Bits 28:17
    UINT32 ERRBANKGROUP                            :  2;  // Bits 30:29
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_ECCERRLOG1_STRUCT;

typedef union {
  struct {
    UINT32 tCKE                                    :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 tXP                                     :  5;  // Bits 12:8
    UINT32                                         :  3;  // Bits 15:13
    UINT32 tXPDLL                                  :  6;  // Bits 21:16
    UINT32 tPRPDEN                                 :  2;  // Bits 23:22
    UINT32 tRDPDEN                                 :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 tWRPDEN                                 :  8;  // Bits 39:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_TC_PWRDN_STRUCT;

typedef union {
  struct {
    UINT32 RPQ_disable                             :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_QUEUE_ENTRY_DISABLE_RPQ_STRUCT;

typedef union {
  struct {
    UINT32 IPQ_disable                             :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_QUEUE_ENTRY_DISABLE_IPQ_STRUCT;

typedef union {
  struct {
    UINT32 WPQ_disableLow                          :  32;  // Bits 31:0
    UINT32 WPQ_disableHigh                         :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_QUEUE_ENTRY_DISABLE_WPQ_STRUCT;

typedef union {
  struct {
    UINT32 WMM_entry_wm                            :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WMM_exit_wm                             :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 WIM_wm                                  :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Write_Isoc_CAS_count                    :  8;  // Bits 31:24
    UINT32 Read_CAS_count                          :  8;  // Bits 39:32
    UINT32 Write_CAS_count                         :  8;  // Bits 47:40
    UINT32 Write_CAS_count_for_VC1                 :  8;  // Bits 55:48
    UINT32 Write_threshold_for_lp_read_bklr        :  7;  // Bits 62:56
    UINT32 En_Wr_in_WIM_during_TT                  :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_SC_WDBWM_STRUCT;

typedef union {
  struct {
    UINT32 ODT_read_duration                       :  4;  // Bits 3:0
    UINT32 ODT_Read_Delay                          :  4;  // Bits 7:4
    UINT32 ODT_write_duration                      :  4;  // Bits 11:8
    UINT32 ODT_Write_Delay                         :  4;  // Bits 15:12
    UINT32 tCL                                     :  6;  // Bits 21:16
    UINT32 tCWL                                    :  6;  // Bits 27:22
    UINT32 Write_Early_ODT                         :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
    UINT32 tAONPD                                  :  5;  // Bits 36:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_TC_ODT_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  16;  // Bits 15:0
    UINT32 WMM_exit_wm_for_FBRMM                   :  7;  // Bits 22:16
    UINT32 Spare_RW_V                              :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_MCSCHEDS_SPARE_STRUCT;

typedef union {
  struct {
    UINT32 Read_Rank_0                             :  4;  // Bits 3:0
    UINT32 Read_Rank_1                             :  4;  // Bits 7:4
    UINT32 Read_Rank_2                             :  4;  // Bits 11:8
    UINT32 Read_Rank_3                             :  4;  // Bits 15:12
    UINT32 Write_Rank_0                            :  4;  // Bits 19:16
    UINT32 Write_Rank_1                            :  4;  // Bits 23:20
    UINT32 Write_Rank_2                            :  4;  // Bits 27:24
    UINT32 Write_Rank_3                            :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_ODT_MATRIX_STRUCT;

typedef union {
  struct {
    UINT32 dft_block_cycles                        :  16;  // Bits 15:0
    UINT32 dft_nonblock_cycles                     :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DFT_BLOCK_STRUCT;

typedef union {
  struct {
    UINT32 DRAM_technology                         :  3;  // Bits 2:0
    UINT32 CMD_stretch                             :  2;  // Bits 4:3
    UINT32 N_to_1_ratio                            :  3;  // Bits 7:5
    UINT32 Address_mirror                          :  4;  // Bits 11:8
    UINT32 tCPDED                                  :  3;  // Bits 14:12
    UINT32 disable_tristate                        :  1;  // Bits 15:15
    UINT32 ck_to_cke                               :  3;  // Bits 18:16
    UINT32 tCAL                                    :  3;  // Bits 21:19
    UINT32 frequency_point                         :  2;  // Bits 23:22
    UINT32 enable_odt_matrix                       :  1;  // Bits 24:24
    UINT32 cs_to_cke                               :  3;  // Bits 27:25
    UINT32 x8_device                               :  2;  // Bits 29:28
    UINT32 no_gear2_param_divide                   :  1;  // Bits 30:30
    UINT32 gear2                                   :  1;  // Bits 31:31
    UINT32 ddr4_1dpc                               :  2;  // Bits 33:32
    UINT32 Limit_MM_Transitions                    :  1;  // Bits 34:34
    UINT32 pl_trace_only_cs_cmd                    :  1;  // Bits 35:35
    UINT32 two_cycle_cke_idle                      :  1;  // Bits 36:36
    UINT32 disable_ca_tristate                     :  1;  // Bits 37:37
    UINT32 disable_ck_tristate                     :  1;  // Bits 38:38
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_SC_GS_CFG_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_PH_THROTTLING_0_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_PH_THROTTLING_1_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_PH_THROTTLING_2_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_PH_THROTTLING_3_STRUCT;

typedef union {
  struct {
    UINT32 Low_WM                                  :  6;  // Bits 5:0
    UINT32 Med_WM                                  :  6;  // Bits 11:6
    UINT32 High_WM                                 :  6;  // Bits 17:12
    UINT32 PHs_allowed_under_low_wm                :  4;  // Bits 21:18
    UINT32 PHs_allowed_under_med_wm                :  4;  // Bits 25:22
    UINT32 PHs_allowed_under_high_wm               :  4;  // Bits 29:26
    UINT32 RPQ_PHs_weight                          :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_WPQ_THRESHOLD_STRUCT;

typedef union {
  struct {
    UINT32 Ring                                    :  10;  // Bits 9:0
    UINT32 SA                                      :  10;  // Bits 19:10
    UINT32 VC0_latency_guard_timer_x16             :  9;  // Bits 28:20
    UINT32 VC1_latency_guard_timer_x8Low           :  3;  // Bits 31:29
    UINT32 VC1_latency_guard_timer_x8High          :  8;  // Bits 39:32
    UINT32 VC1_Isoc_latency_guard_timer_x8         :  11;  // Bits 50:40
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_SC_PR_CNT_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 CKE_Override                            :  4;  // Bits 3:0
    UINT32                                         :  12;  // Bits 15:4
    UINT32 CKE_On                                  :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_REUT_CH_MISC_CKE_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ODT_Override                            :  4;  // Bits 3:0
    UINT32                                         :  12;  // Bits 15:4
    UINT32 ODT_On                                  :  4;  // Bits 19:16
    UINT32                                         :  11;  // Bits 30:20
    UINT32 MPR_Train_DDR_On                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_REUT_CH_MISC_ODT_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 raise_cke_after_exit_latency            :  1;  // Bits 0:0
    UINT32 idle_latency                            :  3;  // Bits 3:1
    UINT32 idle_length                             :  4;  // Bits 7:4
    UINT32 powerdown_latency                       :  4;  // Bits 11:8
    UINT32 powerdown_length                        :  4;  // Bits 15:12
    UINT32 selfrefresh_latency                     :  4;  // Bits 19:16
    UINT32 selfrefresh_length                      :  4;  // Bits 23:20
    UINT32 ckevalid_length                         :  4;  // Bits 27:24
    UINT32 ckevalid_enable                         :  1;  // Bits 28:28
    UINT32 idle_enable                             :  1;  // Bits 29:29
    UINT32 powerdown_enable                        :  1;  // Bits 30:30
    UINT32 selfrefresh_enable                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SPID_LOW_POWER_CTL_STRUCT;

typedef union {
  struct {
    UINT32 LPDDR_2N_CS_MRW                         :  1;  // Bits 0:0
    UINT32 reset_on_command                        :  4;  // Bits 4:1
    UINT32 reset_delay                             :  3;  // Bits 7:5
    UINT32 ignore_cke                              :  1;  // Bits 8:8
    UINT32 mask_cs                                 :  1;  // Bits 9:9
    UINT32 lp4_fifo_rd_wr                          :  1;  // Bits 10:10
    UINT32 disable_tristate                        :  1;  // Bits 11:11
    UINT32 cpgc_in_order                           :  1;  // Bits 12:12
    UINT32 cadb_enable                             :  1;  // Bits 13:13
    UINT32 deselect_enable                         :  1;  // Bits 14:14
    UINT32 Reset_CADB                              :  1;  // Bits 15:15
    UINT32 bus_retain_on_n_to_1_bubble             :  1;  // Bits 16:16
    UINT32 Block_xarb                              :  1;  // Bits 17:17
    UINT32 cadb_ispid_rank_control                 :  1;  // Bits 18:18
    UINT32                                         :  13;  // Bits 31:19
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_GS_CFG_TRAINING_STRUCT;

typedef union {
  struct {
    UINT32 dis_isoc_block_relaxation               :  1;  // Bits 0:0
    UINT32 lp_read_blkr                            :  1;  // Bits 1:1
    UINT32 pe_read_for_pe_blkr                     :  1;  // Bits 2:2
    UINT32 write_ph_blocks_read_pre                :  1;  // Bits 3:3
    UINT32 Read_threshold_for_lp_read_bklr         :  6;  // Bits 9:4
    UINT32 dis_ignore_1st_zqcs                     :  1;  // Bits 10:10
    UINT32 preempt_vc1_during_demote               :  1;  // Bits 11:11
    UINT32 dis_idle_ref_start                      :  1;  // Bits 12:12
    UINT32 invert_ALERT_n                          :  1;  // Bits 13:13
    UINT32 dis_oldest_isoch_pre_over_ph            :  1;  // Bits 14:14
    UINT32 dis_seperate_zq_block                   :  1;  // Bits 15:15
    UINT32 dis_cke_off_in_refresh                  :  1;  // Bits 16:16
    UINT32 allow_ecc_dft_overrides                 :  1;  // Bits 17:17
    UINT32 dis_wdb_clk_gate                        :  1;  // Bits 18:18
    UINT32 dis_mnt_clk_gate                        :  1;  // Bits 19:19
    UINT32 dis_scheds_clk_gate                     :  1;  // Bits 20:20
    UINT32 dis_lpmode_on_sagv                      :  1;  // Bits 21:21
    UINT32 ignore_fragment_safe_in_ref             :  1;  // Bits 22:22
    UINT32 cmi_short_rmw_stall                     :  1;  // Bits 23:23
    UINT32 ipq_ignore_write_ph                     :  1;  // Bits 24:24
    UINT32 spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SCHED_THIRD_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 No_CAS_threshold                        :  16;  // Bits 15:0
    UINT32 No_CAS_threshold_en                     :  1;  // Bits 16:16
    UINT32 Preemption_threshold_en                 :  1;  // Bits 17:17
    UINT32 Stop_count_during_tt                    :  1;  // Bits 18:18
    UINT32 Attempt_refresh_on_deadlock             :  1;  // Bits 19:19
    UINT32 MajorMode_force_duration                :  8;  // Bits 27:20
    UINT32 MajorMode_force_en                      :  1;  // Bits 28:28
    UINT32 Disable_blocking_rules                  :  1;  // Bits 29:29
    UINT32 Rank_join                               :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DEADLOCK_BREAKER_STRUCT;

typedef union {
  struct {
    UINT32 max_tRDWR                               :  6;  // Bits 5:0
    UINT32 bubble_cnt_visa_out_bits01              :  2;  // Bits 7:6
    UINT32 max_tWRWR                               :  6;  // Bits 13:8
    UINT32 bubble_cnt_visa_out_bit2                :  1;  // Bits 14:14
    UINT32                                         :  1;  // Bits 15:15
    UINT32 max_tWRRD                               :  8;  // Bits 23:16
    UINT32 max_tRDRD                               :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_XARB_TC_BUBBLE_INJ_STRUCT;

typedef union {
  struct {
    UINT32 bubble_inj_enable_read_switch           :  1;  // Bits 0:0
    UINT32 bubble_inj_enable_write_switch          :  1;  // Bits 1:1
    UINT32 bubble_inj_enable_any_cas_switch        :  1;  // Bits 2:2
    UINT32 Rank_mode                               :  1;  // Bits 3:3
    UINT32 DIMM_mode                               :  1;  // Bits 4:4
    UINT32 DIMM_mode_multiplier                    :  2;  // Bits 6:5
    UINT32 Dis_MRR_Bubble                          :  1;  // Bits 7:7
    UINT32 bubble_inj_read_switch_num_cas          :  8;  // Bits 15:8
    UINT32 bubble_inj_write_switch_num_cas         :  8;  // Bits 23:16
    UINT32 bubble_inj_any_cas_switch_num_cas       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_XARB_CFG_BUBBLE_INJ_STRUCT;

typedef union {
  struct {
    UINT32 GLB_GRACE_CNT                           :  8;  // Bits 7:0
    UINT32 GLB_DRV_GATE_DIS                        :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_STRUCT;

typedef union {
  struct {
    UINT32 dis_legacy_ph_blkr                      :  1;  // Bits 0:0
    UINT32 dis_legacy_pe_blkr                      :  1;  // Bits 1:1
    UINT32 low_wm_allowed_preempt_priorities       :  3;  // Bits 4:2
    UINT32 med_wm_allowed_preempt_priorities       :  3;  // Bits 7:5
    UINT32 high_wm_allowed_preempt_priorities      :  3;  // Bits 10:8
    UINT32 ph_block_pe                             :  1;  // Bits 11:11
    UINT32 blkr_effect_major_mode                  :  1;  // Bits 12:12
    UINT32 RIM_BW_optimization                     :  1;  // Bits 13:13
    UINT32 RIM_BW_prefer_VC1                       :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_BLOCKING_RULES_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Refresh_Rank_Mask                       :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 RefZQ_En_Start_Test_Sync                :  1;  // Bits 8:8
    UINT32                                         :  22;  // Bits 30:9
    UINT32 Panic_Refresh_Only                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_REUT_CH_MISC_REFRESH_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ZQ_Rank_Mask                            :  4;  // Bits 3:0
    UINT32                                         :  27;  // Bits 30:4
    UINT32 Always_Do_ZQ                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_REUT_CH_MISC_ZQ_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_width                            :  2;  // Bits 1:0
    UINT32 Rank_1_width                            :  2;  // Bits 3:2
    UINT32 Rank_2_width                            :  2;  // Bits 5:4
    UINT32 Rank_3_width                            :  2;  // Bits 7:6
    UINT32 MR4_PERIOD                              :  16;  // Bits 23:8
    UINT32 DDR4_TS_readout_en                      :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR_MR_PARAMS_STRUCT;

typedef union {
  struct {
    UINT32 Address                                 :  8;  // Bits 7:0
    UINT32 Data                                    :  8;  // Bits 15:8
    UINT32 Rank                                    :  2;  // Bits 17:16
    UINT32 Command                                 :  2;  // Bits 19:18
    UINT32 DRAM_mask                               :  9;  // Bits 28:20
    UINT32 Assume_idle                             :  1;  // Bits 29:29
    UINT32 DDR4_MA13                               :  1;  // Bits 30:30
    UINT32 Busy                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR_MR_COMMAND_STRUCT;

typedef union {
  struct {
    UINT32 Device_0                                :  8;  // Bits 7:0
    UINT32 Device_1                                :  8;  // Bits 15:8
    UINT32 Device_2                                :  8;  // Bits 23:16
    UINT32 Device_3                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR_MR_RESULT_0_STRUCT;

typedef union {
  struct {
    UINT32 Device_4                                :  8;  // Bits 7:0
    UINT32 Device_5                                :  8;  // Bits 15:8
    UINT32 Device_6                                :  8;  // Bits 23:16
    UINT32 Device_7                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR_MR_RESULT_1_STRUCT;

typedef union {
  struct {
    UINT32 Device_8                                :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR_MR_RESULT_2_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 Rank_1                                  :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Rank_2                                  :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 Rank_3                                  :  3;  // Bits 26:24
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  2;  // Bits 1:0
    UINT32                                         :  6;  // Bits 7:2
    UINT32 Rank_1                                  :  2;  // Bits 9:8
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Rank_2                                  :  2;  // Bits 17:16
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Rank_3                                  :  2;  // Bits 25:24
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR4_MPR_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Bit_0                                   :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_1                                   :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_2                                   :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_16                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_17                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_18                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_0                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_2                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DESWIZZLE_LOW_STRUCT;

typedef union {
  struct {
    UINT32 Bit_32                                  :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_33                                  :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_34                                  :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_48                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_49                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_50                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_4                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_6                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DESWIZZLE_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 OREF_RI                                 :  8;  // Bits 7:0
    UINT32 Refresh_HP_WM                           :  4;  // Bits 11:8
    UINT32 Refresh_panic_wm                        :  4;  // Bits 15:12
    UINT32 CounttREFIWhileRefEnOff                 :  1;  // Bits 16:16
    UINT32 HPRefOnMRS                              :  1;  // Bits 17:17
    UINT32 AlwaysRefOnMRS                          :  1;  // Bits 18:18
    UINT32                                         :  6;  // Bits 24:19
    UINT32 tREFIx9                                 :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_RFP_STRUCT;

typedef union {
  struct {
    UINT32 tREFI                                   :  16;  // Bits 15:0
    UINT32 tRFC                                    :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_RFTP_STRUCT;

typedef union {
  struct {
    UINT32 tXSDLL                                  :  12;  // Bits 11:0
    UINT32                                         :  4;  // Bits 15:12
    UINT32 tZQOPER                                 :  10;  // Bits 25:16
    UINT32 tMOD                                    :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_SRFTP_STRUCT;

typedef union {
  struct {
    UINT32 Ref_Interval                            :  11;  // Bits 10:0
    UINT32 Ref_Stagger_En                          :  1;  // Bits 11:11
    UINT32 Ref_Stagger_Mode                        :  1;  // Bits 12:12
    UINT32 Disable_Stolen_Refresh                  :  1;  // Bits 13:13
    UINT32 En_Ref_Type_Display                     :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_MC_REFRESH_STAGGER_STRUCT;

typedef union {
  struct {
    UINT32 ZQCS_period                             :  10;  // Bits 9:0
    UINT32 tZQCS                                   :  10;  // Bits 19:10
    UINT32 tZQCAL                                  :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_ZQCAL_STRUCT;

typedef union {
  struct {
    UINT32 MR2_shaddow                             :  14;  // Bits 13:0
    UINT32 SRT_avail                               :  2;  // Bits 15:14
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_MR2_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 MR4_sh_low                              :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 MR4_sh_high                             :  10;  // Bits 13:4
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_MR4_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 Rank_occupancy                          :  8;  // Bits 7:0
    UINT32 SRX_reset                               :  1;  // Bits 8:8
    UINT32 LPDDR4_current_FSP                      :  1;  // Bits 9:9
    UINT32 LPDDR4_current_FSP_tracking             :  1;  // Bits 10:10
    UINT32 Reset_refresh_debt                      :  1;  // Bits 11:11
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_MC_INIT_STATE_STRUCT;

typedef union {
  struct {
    UINT32 VISAByteSel                             :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 RefFSMRankSel                           :  2;  // Bits 9:8
    UINT32 Ref_counterSel                          :  3;  // Bits 12:10
    UINT32 Enable_Ref_Status_Sample                :  1;  // Bits 13:13
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_WDB_VISA_SEL_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_IDLE_ENERGY                       :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_IDLE_ENERGY                       :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_PM_DIMM_IDLE_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_PD_ENERGY                         :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_PD_ENERGY                         :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_PM_DIMM_PD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_ACT_ENERGY                        :  8;  // Bits 7:0
    UINT32 DIMM1_ACT_ENERGY                        :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_PM_DIMM_ACT_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_RD_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_RD_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_PM_DIMM_RD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_WR_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_WR_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_PM_DIMM_WR_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_ECC_INJECT_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 Dec_tCWL                                :  6;  // Bits 5:0
    UINT32 Add_tCWL                                :  6;  // Bits 11:6
    UINT32 Add_1Qclk_delay                         :  1;  // Bits 12:12
    UINT32                                         :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_WR_DELAY_STRUCT;

typedef union {
  struct {
    UINT32 ECC                                     :  8;  // Bits 7:0
    UINT32 RRD_DFT_Mode                            :  2;  // Bits 9:8
    UINT32 LFSR_Seed_Index                         :  5;  // Bits 14:10
    UINT32 Inversion_Mode                          :  1;  // Bits 15:15
    UINT32 AddressBased                            :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_READ_RETURN_DFT_STRUCT;

typedef union {
  struct {
    UINT32 Bit_0                                   :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_1                                   :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_2                                   :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_16                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_17                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_18                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_0                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_2                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DESWIZZLE_LOW_ERM_STRUCT;

typedef union {
  struct {
    UINT32 Bit_32                                  :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_33                                  :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_34                                  :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_48                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_49                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_50                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_4                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_6                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DESWIZZLE_HIGH_ERM_STRUCT;

typedef union {
  struct {
    UINT32 PBR_Disable                             :  1;  // Bits 0:0
    UINT32 PBR_OOO_Dis                             :  1;  // Bits 1:1
    UINT32 PBR_Issue_NOP                           :  1;  // Bits 2:2
    UINT32 PBR_Disable_on_hot                      :  1;  // Bits 3:3
    UINT32 PBR_Exit_on_Idle_Cnt                    :  6;  // Bits 9:4
    UINT32 tRFCpb                                  :  10;  // Bits 19:10
    UINT32 Refresh_ABR_release                     :  4;  // Bits 23:20
    UINT32 PBR_extended_disable_while_DQS_OSC      :  1;  // Bits 24:24
    UINT32 SPARE                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_SC_PBR_STRUCT;

typedef union {
  struct {
    UINT32 CPGC2MC_RD_CREDITS                      :  8;  // Bits 7:0
    UINT32 CPGC2MC_WR_CREDITS                      :  8;  // Bits 15:8
    UINT32 MC2CPGC_RD_CREDITS                      :  8;  // Bits 23:16
    UINT32 CPGC_ACTIVE                             :  1;  // Bits 24:24
    UINT32 CPGC_sync_cpl                           :  1;  // Bits 25:25
    UINT32 CPGC_sync_phase                         :  1;  // Bits 26:26
    UINT32 CPGC_Dis_Allow_CPL_interleave           :  1;  // Bits 27:27
    UINT32 CPGC_ECC_BYTE                           :  3;  // Bits 30:28
    UINT32 Stall_CPGC_CMI_Req                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_MC_CPGC_CMI_STRUCT;

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
    UINT32 DDR4_alert                              :  1;  // Bits 20:20
    UINT32                                         :  11;  // Bits 31:21
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_MC_CPGC_MISC_DFT_STRUCT;

typedef union {
  struct {
    UINT32 tOSCO                                   :  7;  // Bits 6:0
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_LPDDR4_MISC_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_PM_ALL_RANKS_CKE_LOW_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 tXSR                                    :  10;  // Bits 9:0
    UINT32 count_block_wr_on_srx                   :  7;  // Bits 16:10
    UINT32 serial_zq_between_sub_ch                :  1;  // Bits 17:17
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_TC_SREXITTP_STRUCT;

typedef union {
  struct {
    UINT32 DQSOSCL_PERIOD                          :  16;  // Bits 15:0
    UINT32 MR19toBlockAckPeriod                    :  8;  // Bits 23:16
    UINT32 DIS_SRX_DQSOSCL                         :  1;  // Bits 24:24
    UINT32                                         :  1;  // Bits 25:25
    UINT32 disable_wr_on_pkgc_exit                 :  1;  // Bits 26:26
    UINT32 disable_wr_on_SR_exit                   :  1;  // Bits 27:27
    UINT32 disable_PMreqWaitForMR19                :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT;

typedef union {
  struct {
    UINT32 Enable_WDB_Capture                      :  1;  // Bits 0:0
    UINT32                                         :  7;  // Bits 7:1
    UINT32 WDB_Starting_Capture_Pointer            :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_Ending_Capture_Pointer              :  6;  // Bits 21:16
    UINT32 WDB_Capture_Block_SubCh                 :  2;  // Bits 23:22
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_REUT_CH_WDB_CAPTURE_CTL_STRUCT;

typedef union {
  struct {
    UINT32 WDB_SC0_Current_Capture_Pointer         :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 WDB_SC1_Current_Capture_Pointer         :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_REUT_CH_WDB_CAPTURE_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 DATALow                                 :  32;  // Bits 31:0
    UINT32 DATAHigh                                :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_WDB_RD_WR_DFX_DATA_STRUCT;

typedef union {
  struct {
    UINT32 GO                                      :  1;  // Bits 0:0
    UINT32 Chunk_Sel                               :  8;  // Bits 8:1
    UINT32 Op                                      :  1;  // Bits 9:9
    UINT32 SubCh                                   :  1;  // Bits 10:10
    UINT32 WID                                     :  6;  // Bits 16:11
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_WDB_RD_WR_DFX_CTL_STRUCT;

typedef union {
  struct {
    UINT32 DQS_INTERVAL_FSM_status                 :  4;  // Bits 3:0
    UINT32 TEMP_RD_FSM_status                      :  5;  // Bits 8:4
    UINT32 REFRATE_CHNG_FSM_status                 :  2;  // Bits 10:9
    UINT32 ZQCS_FSM_status                         :  3;  // Bits 13:11
    UINT32 EXE_REF_FSM_status                      :  3;  // Bits 16:14
    UINT32 MAIN_REF_FSM_status                     :  3;  // Bits 19:17
    UINT32 MAIN_SR_FSM_status                      :  4;  // Bits 23:20
    UINT32 counter_status                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_REF_FSM_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR4_MR1_ODIC_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_MR5_RTT_PARK_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_MR1_RTT_NOM_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  3;  // Bits 25:23
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_STRUCT_A0;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_LPDDR4_DISCRETE_MR_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_LPDDR4_DISCRETE_MR_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_LPDDR4_DISCRETE_MR_VALUES_2_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_LPDDR4_DISCRETE_MR_VALUES_3_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_LPDDR4_DISCRETE_MR_VALUES_4_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_LPDDR4_DISCRETE_MR_VALUES_5_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_LPDDR4_DISCRETE_MR_VALUES_6_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_LPDDR4_DISCRETE_MR_VALUES_7_STRUCT;

typedef union {
  struct {
    UINT32 MR0                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR1                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR4_MR0_MR1_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR2                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR3                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR4_MR2_MR3_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR4                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR5                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR4_MR4_MR5_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR6                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR7                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR4_MR6_MR7_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_MR2_RTT_WR_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_MR6_VREF_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_MR6_VREF_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 MR1                                     :  8;  // Bits 7:0
    UINT32 MR2                                     :  8;  // Bits 15:8
    UINT32 MR3                                     :  8;  // Bits 23:16
    UINT32 MR11                                    :  8;  // Bits 31:24
    UINT32 MR12                                    :  8;  // Bits 39:32
    UINT32 MR13                                    :  8;  // Bits 47:40
    UINT32 MR22                                    :  8;  // Bits 55:48
    UINT32 MR23                                    :  8;  // Bits 63:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_LPDDR_MR_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 DDR4_Restore_MR                         :  8;  // Bits 7:0
    UINT32 DDR4_Restore_MR1_ODIC_Per_Device        :  1;  // Bits 8:8
    UINT32 DDR4_Restore_MR2_Per_Device             :  1;  // Bits 9:9
    UINT32 DDR4_Restore_MR6_Per_Device             :  1;  // Bits 10:10
    UINT32 DDR4_PDA_VREF_Initial                   :  1;  // Bits 11:11
    UINT32 DDR4_Short_VREF_Exit                    :  1;  // Bits 12:12
    UINT32 LPDDR_Restore_MR                        :  9;  // Bits 21:13
    UINT32 do_ZQCL                                 :  1;  // Bits 22:22
    UINT32 zero_rank1_MR11                         :  1;  // Bits 23:23
    UINT32 reset_flow                              :  1;  // Bits 24:24
    UINT32 vref_time_per_byte                      :  1;  // Bits 25:25
    UINT32 do_pda_for_1R1R                         :  1;  // Bits 26:26
    UINT32 add_initial_vref                        :  1;  // Bits 27:27
    UINT32 LPDDR4_switch_FSP                       :  1;  // Bits 28:28
    UINT32 do_dq_osc_start                         :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
    UINT32 tVREFDQ                                 :  10;  // Bits 41:32
    UINT32 cbit_count_each_rank                    :  1;  // Bits 42:42
    UINT32 do_PDA_for_ECC                          :  1;  // Bits 43:43
    UINT32 DDR4_Restore_MR5_Per_Device             :  1;  // Bits 44:44
    UINT32 TwoDPC_support                          :  1;  // Bits 45:45
    UINT32 DDR4_Restore_MR1_RTTNOM_Per_Device      :  1;  // Bits 46:46
    UINT32 Fast_PDA                                :  1;  // Bits 47:47
    UINT32 always_count_tFC                        :  1;  // Bits 48:48
    UINT32 PDA_wr_delay                            :  6;  // Bits 54:49
    UINT32 LPDDR4_per_byte_vref                    :  1;  // Bits 55:55
    UINT32 Clear_VRCG                              :  1;  // Bits 56:56
    UINT32 GV_auto_enable                          :  1;  // Bits 57:57
    UINT32 LPDDR4_split_transition                 :  1;  // Bits 58:58
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_MRS_FSM_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Run                                     :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_MRS_FSM_RUN_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_DDR4_MR1_ODIC_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 data_trace_mode                         :  2;  // Bits 1:0
    UINT32 UI_to_trace                             :  3;  // Bits 4:2
    UINT32 byte_to_trace                           :  3;  // Bits 7:5
    UINT32 ECC_EN                                  :  1;  // Bits 8:8
    UINT32 ECC_BYTE_replace                        :  3;  // Bits 11:9
    UINT32 trace_read_data                         :  1;  // Bits 12:12
    UINT32 trace_write_data                        :  1;  // Bits 13:13
    UINT32 DDRPL_Activate                          :  1;  // Bits 14:14
    UINT32 SCHTrace                                :  1;  // Bits 15:15
    UINT32 dis_early_ind_override                  :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_PL_AGENT_CFG_DTF_STRUCT;

typedef union {
  struct {
    UINT32 GLB_GRACE_CNT                           :  8;  // Bits 7:0
    UINT32 GLB_DRV_GATE_DIS                        :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_STRUCT;

typedef union {
  struct {
    UINT32 ODIC_Rank0                              :  2;  // Bits 1:0
    UINT32 ODIC_Rank1                              :  2;  // Bits 3:2
    UINT32 RTT_WR_Rank0                            :  3;  // Bits 6:4
    UINT32 RTT_WR_Rank1                            :  3;  // Bits 9:7
    UINT32 VREF_Rank0                              :  7;  // Bits 16:10
    UINT32 VREF_Rank1                              :  7;  // Bits 23:17
    UINT32 RTT_NOM_Rank0                           :  3;  // Bits 26:24
    UINT32 RTT_NOM_Rank1                           :  3;  // Bits 29:27
    UINT32 RTT_PARK_Rank0Low                       :  2;  // Bits 31:30
    UINT32 RTT_PARK_Rank0High                      :  1;  // Bits 32:32
    UINT32 RTT_PARK_Rank1                          :  3;  // Bits 35:33
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_ECC_DEVICE_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 ODIC_Rank0                              :  2;  // Bits 1:0
    UINT32 ODIC_Rank1                              :  2;  // Bits 3:2
    UINT32 RTT_WR_Rank0                            :  3;  // Bits 6:4
    UINT32 RTT_WR_Rank1                            :  3;  // Bits 9:7
    UINT32 VREF_Rank0                              :  7;  // Bits 16:10
    UINT32 VREF_Rank1                              :  7;  // Bits 23:17
    UINT32 RTT_NOM_Rank0                           :  3;  // Bits 26:24
    UINT32 RTT_NOM_Rank1                           :  3;  // Bits 29:27
    UINT32 RTT_PARK_Rank0Low                       :  2;  // Bits 31:30
    UINT32 RTT_PARK_Rank0High                      :  1;  // Bits 32:32
    UINT32 RTT_PARK_Rank1                          :  3;  // Bits 35:33
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH0_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  8;  // Bits 7:0
    UINT32 ForceX2Ref                              :  1;  // Bits 8:8
    UINT32 ForceX4Ref                              :  1;  // Bits 9:9
    UINT32 DisLowRefRate                           :  1;  // Bits 10:10
    UINT32 disRegardZQonSRtime                     :  1;  // Bits 11:11
    UINT32 Decoder_EBH                             :  2;  // Bits 13:12
    UINT32                                         :  1;  // Bits 14:14
    UINT32 DisSREXcnt                              :  1;  // Bits 15:15
    UINT32 Spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH0_CR_MCMNTS_SPARE_STRUCT;

typedef union {
  struct {
    UINT32 tRP                                     :  6;  // Bits 5:0
    UINT32 tRPab_ext                               :  3;  // Bits 8:6
    UINT32 tRAS                                    :  7;  // Bits 15:9
    UINT32 tRDPRE                                  :  5;  // Bits 20:16
    UINT32 tPPD                                    :  3;  // Bits 23:21
    UINT32 tWRPRE                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_PRE_STRUCT;

typedef union {
  struct {
    UINT32 tFAW                                    :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 tRRD_sg                                 :  5;  // Bits 12:8
    UINT32 tRRD_dg                                 :  5;  // Bits 17:13
    UINT32 derating_ext                            :  3;  // Bits 20:18
    UINT32 tRCD_wr                                 :  6;  // Bits 26:21
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_ACT_STRUCT;

typedef union {
  struct {
    UINT32 tRDRD_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDRD_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_RDRD_STRUCT;

typedef union {
  struct {
    UINT32 tRDWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_RDWR_STRUCT;

typedef union {
  struct {
    UINT32 tWRRD_sg                                :  8;  // Bits 7:0
    UINT32 tWRRD_dg                                :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 tWRRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_WRRD_STRUCT;

typedef union {
  struct {
    UINT32 tWRWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tWRWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tWRWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_WRWR_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_latency                          :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank_1_latency                          :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank_2_latency                          :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank_3_latency                          :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank_4_latency                          :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank_5_latency                          :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank_6_latency                          :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank_7_latency                          :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_SC_ROUNDTRIP_LATENCY_STRUCT;

typedef union {
  struct {
    UINT32 dis_opp_cas                             :  1;  // Bits 0:0
    UINT32 dis_opp_is_cas                          :  1;  // Bits 1:1
    UINT32 dis_opp_ras                             :  1;  // Bits 2:2
    UINT32 dis_opp_is_ras                          :  1;  // Bits 3:3
    UINT32 dis_2c_byp                              :  1;  // Bits 4:4
    UINT32 dis_deprd_opt                           :  1;  // Bits 5:5
    UINT32 dis_pt_it                               :  1;  // Bits 6:6
    UINT32 dis_prcnt_ring                          :  1;  // Bits 7:7
    UINT32 dis_prcnt_sa                            :  1;  // Bits 8:8
    UINT32 dis_blkr_ph                             :  1;  // Bits 9:9
    UINT32 dis_blkr_pe                             :  1;  // Bits 10:10
    UINT32 dis_blkr_pm                             :  1;  // Bits 11:11
    UINT32 dis_odt                                 :  1;  // Bits 12:12
    UINT32 OE_alw_off                              :  1;  // Bits 13:13
    UINT32 block_rpq                               :  1;  // Bits 14:14
    UINT32 block_ipq                               :  1;  // Bits 15:15
    UINT32 block_wpq                               :  1;  // Bits 16:16
    UINT32 dis_zq                                  :  1;  // Bits 17:17
    UINT32 dis_tt                                  :  1;  // Bits 18:18
    UINT32 dis_opp_ref                             :  1;  // Bits 19:19
    UINT32 long_zq                                 :  1;  // Bits 20:20
    UINT32 dis_srx_zq                              :  1;  // Bits 21:21
    UINT32 serialize_zq                            :  1;  // Bits 22:22
    UINT32 zq_fast_exec                            :  1;  // Bits 23:23
    UINT32 dis_starved_read_rank_block             :  1;  // Bits 24:24
    UINT32 dis_idle_preempt                        :  1;  // Bits 25:25
    UINT32 find_first_allocation                   :  1;  // Bits 26:26
    UINT32 duplicate_spid_rank                     :  1;  // Bits 27:27
    UINT32 wio_merge_lpmode_2_3                    :  1;  // Bits 28:28
    UINT32 dis_5cyc_write_gap                      :  1;  // Bits 29:29
    UINT32 dis_5cyc_read_gap                       :  1;  // Bits 30:30
    UINT32 dis_clk_gate                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SCHED_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 dis_srx_mr4                             :  1;  // Bits 0:0
    UINT32 dis_ck_tristate                         :  1;  // Bits 1:1
    UINT32 dis_burst_ref_limit                     :  1;  // Bits 2:2
    UINT32 dis_bus_retain                          :  1;  // Bits 3:3
    UINT32 dis_async_odt                           :  1;  // Bits 4:4
    UINT32 dis_SRX_reset                           :  1;  // Bits 5:5
    UINT32 SPARE_CBIT                              :  1;  // Bits 6:6
    UINT32 dis_SRX_MRS_MR4                         :  1;  // Bits 7:7
    UINT32 dis_opp_ref_idle_delay                  :  1;  // Bits 8:8
    UINT32 dis_ignore_1st_trefi                    :  1;  // Bits 9:9
    UINT32 echo_mask                               :  9;  // Bits 18:10
    UINT32 dis_early_go                            :  1;  // Bits 19:19
    UINT32 dis_new_wr_to_full                      :  1;  // Bits 20:20
    UINT32 WIO2_DBIac_Dis                          :  1;  // Bits 21:21
    UINT32 drainless_SAGV_do_zq                    :  1;  // Bits 22:22
    UINT32 do_temp_reading_after_drainless_SAGV    :  1;  // Bits 23:23
    UINT32 ignore_refresh_between_SR               :  1;  // Bits 24:24
    UINT32 DisWrActThrottleOnAnyRead               :  1;  // Bits 25:25
    UINT32 enable_fdata_nak                        :  1;  // Bits 26:26
    UINT32 spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SCHED_SECOND_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 WDAR                                    :  1;  // Bits 0:0
    UINT32 WDB_Block_En                            :  1;  // Bits 1:1
    UINT32                                         :  2;  // Bits 3:2
    UINT32 isolate_data_return                     :  1;  // Bits 4:4
    UINT32                                         :  12;  // Bits 16:5
    UINT32 dft_block_enable                        :  1;  // Bits 17:17
    UINT32 SAM_overloading                         :  3;  // Bits 20:18
    UINT32                                         :  3;  // Bits 23:21
    UINT32 Stretch_mode_en                         :  1;  // Bits 24:24
    UINT32 STF                                     :  5;  // Bits 29:25
    UINT32 Stretch_delay_from_write                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DFT_MISC_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Inject                              :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ECC_correction_disable                  :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 DIS_MCA_LOG                             :  1;  // Bits 8:8
    UINT32 DIS_PCH_EVENT                           :  1;  // Bits 9:9
    UINT32 DIS_RCH_POISON                          :  1;  // Bits 10:10
    UINT32 DIS_RCH_ERROR                           :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 ECC_trigger                             :  2;  // Bits 17:16
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_ECC_DFT_STRUCT;

typedef union {
  struct {
    UINT32 PCIT                                    :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 PCIT_GT                                 :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_PCIT_STRUCT;

typedef union {
  struct {
    UINT32 PDWN_idle_counter                       :  12;  // Bits 11:0
    UINT32 APD                                     :  1;  // Bits 12:12
    UINT32 PPD                                     :  1;  // Bits 13:13
    UINT32 Slow_Exit                               :  1;  // Bits 14:14
    UINT32 Global_PD                               :  1;  // Bits 15:15
    UINT32 TT_idle_counter                         :  8;  // Bits 23:16
    UINT32 dis_cke_tt                              :  1;  // Bits 24:24
    UINT32 write_threshold                         :  6;  // Bits 30:25
    UINT32 allow_opp_ref_below_write_threhold      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_PM_PDWN_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Dis_Opp_rd                              :  1;  // Bits 0:0
    UINT32 ACT_Enable                              :  1;  // Bits 1:1
    UINT32 PRE_Enable                              :  1;  // Bits 2:2
    UINT32 MAX_RPQ_CAS                             :  4;  // Bits 6:3
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_WMM_READ_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 CERRSTS                                 :  1;  // Bits 0:0
    UINT32 MERRSTS                                 :  1;  // Bits 1:1
    UINT32                                         :  14;  // Bits 15:2
    UINT32 ERRSYND                                 :  8;  // Bits 23:16
    UINT32 ERRCHUNK                                :  3;  // Bits 26:24
    UINT32 ERRRANK                                 :  2;  // Bits 28:27
    UINT32 ERRBANK                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_ECCERRLOG0_STRUCT;

typedef union {
  struct {
    UINT32 ERRROW                                  :  17;  // Bits 16:0
    UINT32 ERRCOL                                  :  12;  // Bits 28:17
    UINT32 ERRBANKGROUP                            :  2;  // Bits 30:29
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_ECCERRLOG1_STRUCT;

typedef union {
  struct {
    UINT32 tCKE                                    :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 tXP                                     :  5;  // Bits 12:8
    UINT32                                         :  3;  // Bits 15:13
    UINT32 tXPDLL                                  :  6;  // Bits 21:16
    UINT32 tPRPDEN                                 :  2;  // Bits 23:22
    UINT32 tRDPDEN                                 :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 tWRPDEN                                 :  8;  // Bits 39:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_TC_PWRDN_STRUCT;

typedef union {
  struct {
    UINT32 RPQ_disable                             :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_QUEUE_ENTRY_DISABLE_RPQ_STRUCT;

typedef union {
  struct {
    UINT32 IPQ_disable                             :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_QUEUE_ENTRY_DISABLE_IPQ_STRUCT;

typedef union {
  struct {
    UINT32 WPQ_disableLow                          :  32;  // Bits 31:0
    UINT32 WPQ_disableHigh                         :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_QUEUE_ENTRY_DISABLE_WPQ_STRUCT;

typedef union {
  struct {
    UINT32 WMM_entry_wm                            :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WMM_exit_wm                             :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 WIM_wm                                  :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Write_Isoc_CAS_count                    :  8;  // Bits 31:24
    UINT32 Read_CAS_count                          :  8;  // Bits 39:32
    UINT32 Write_CAS_count                         :  8;  // Bits 47:40
    UINT32 Write_CAS_count_for_VC1                 :  8;  // Bits 55:48
    UINT32 Write_threshold_for_lp_read_bklr        :  7;  // Bits 62:56
    UINT32 En_Wr_in_WIM_during_TT                  :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_SC_WDBWM_STRUCT;

typedef union {
  struct {
    UINT32 ODT_read_duration                       :  4;  // Bits 3:0
    UINT32 ODT_Read_Delay                          :  4;  // Bits 7:4
    UINT32 ODT_write_duration                      :  4;  // Bits 11:8
    UINT32 ODT_Write_Delay                         :  4;  // Bits 15:12
    UINT32 tCL                                     :  6;  // Bits 21:16
    UINT32 tCWL                                    :  6;  // Bits 27:22
    UINT32 Write_Early_ODT                         :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
    UINT32 tAONPD                                  :  5;  // Bits 36:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_TC_ODT_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  16;  // Bits 15:0
    UINT32 WMM_exit_wm_for_FBRMM                   :  7;  // Bits 22:16
    UINT32 Spare_RW_V                              :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_MCSCHEDS_SPARE_STRUCT;

typedef union {
  struct {
    UINT32 Read_Rank_0                             :  4;  // Bits 3:0
    UINT32 Read_Rank_1                             :  4;  // Bits 7:4
    UINT32 Read_Rank_2                             :  4;  // Bits 11:8
    UINT32 Read_Rank_3                             :  4;  // Bits 15:12
    UINT32 Write_Rank_0                            :  4;  // Bits 19:16
    UINT32 Write_Rank_1                            :  4;  // Bits 23:20
    UINT32 Write_Rank_2                            :  4;  // Bits 27:24
    UINT32 Write_Rank_3                            :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_ODT_MATRIX_STRUCT;

typedef union {
  struct {
    UINT32 dft_block_cycles                        :  16;  // Bits 15:0
    UINT32 dft_nonblock_cycles                     :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DFT_BLOCK_STRUCT;

typedef union {
  struct {
    UINT32 DRAM_technology                         :  3;  // Bits 2:0
    UINT32 CMD_stretch                             :  2;  // Bits 4:3
    UINT32 N_to_1_ratio                            :  3;  // Bits 7:5
    UINT32 Address_mirror                          :  4;  // Bits 11:8
    UINT32 tCPDED                                  :  3;  // Bits 14:12
    UINT32 disable_tristate                        :  1;  // Bits 15:15
    UINT32 ck_to_cke                               :  3;  // Bits 18:16
    UINT32 tCAL                                    :  3;  // Bits 21:19
    UINT32 frequency_point                         :  2;  // Bits 23:22
    UINT32 enable_odt_matrix                       :  1;  // Bits 24:24
    UINT32 cs_to_cke                               :  3;  // Bits 27:25
    UINT32 x8_device                               :  2;  // Bits 29:28
    UINT32 no_gear2_param_divide                   :  1;  // Bits 30:30
    UINT32 gear2                                   :  1;  // Bits 31:31
    UINT32 ddr4_1dpc                               :  2;  // Bits 33:32
    UINT32 Limit_MM_Transitions                    :  1;  // Bits 34:34
    UINT32 pl_trace_only_cs_cmd                    :  1;  // Bits 35:35
    UINT32 two_cycle_cke_idle                      :  1;  // Bits 36:36
    UINT32 disable_ca_tristate                     :  1;  // Bits 37:37
    UINT32 disable_ck_tristate                     :  1;  // Bits 38:38
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_SC_GS_CFG_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_PH_THROTTLING_0_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_PH_THROTTLING_1_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_PH_THROTTLING_2_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_PH_THROTTLING_3_STRUCT;

typedef union {
  struct {
    UINT32 Low_WM                                  :  6;  // Bits 5:0
    UINT32 Med_WM                                  :  6;  // Bits 11:6
    UINT32 High_WM                                 :  6;  // Bits 17:12
    UINT32 PHs_allowed_under_low_wm                :  4;  // Bits 21:18
    UINT32 PHs_allowed_under_med_wm                :  4;  // Bits 25:22
    UINT32 PHs_allowed_under_high_wm               :  4;  // Bits 29:26
    UINT32 RPQ_PHs_weight                          :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_WPQ_THRESHOLD_STRUCT;

typedef union {
  struct {
    UINT32 Ring                                    :  10;  // Bits 9:0
    UINT32 SA                                      :  10;  // Bits 19:10
    UINT32 VC0_latency_guard_timer_x16             :  9;  // Bits 28:20
    UINT32 VC1_latency_guard_timer_x8Low           :  3;  // Bits 31:29
    UINT32 VC1_latency_guard_timer_x8High          :  8;  // Bits 39:32
    UINT32 VC1_Isoc_latency_guard_timer_x8         :  11;  // Bits 50:40
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_SC_PR_CNT_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 CKE_Override                            :  4;  // Bits 3:0
    UINT32                                         :  12;  // Bits 15:4
    UINT32 CKE_On                                  :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_REUT_CH_MISC_CKE_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ODT_Override                            :  4;  // Bits 3:0
    UINT32                                         :  12;  // Bits 15:4
    UINT32 ODT_On                                  :  4;  // Bits 19:16
    UINT32                                         :  11;  // Bits 30:20
    UINT32 MPR_Train_DDR_On                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_REUT_CH_MISC_ODT_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 raise_cke_after_exit_latency            :  1;  // Bits 0:0
    UINT32 idle_latency                            :  3;  // Bits 3:1
    UINT32 idle_length                             :  4;  // Bits 7:4
    UINT32 powerdown_latency                       :  4;  // Bits 11:8
    UINT32 powerdown_length                        :  4;  // Bits 15:12
    UINT32 selfrefresh_latency                     :  4;  // Bits 19:16
    UINT32 selfrefresh_length                      :  4;  // Bits 23:20
    UINT32 ckevalid_length                         :  4;  // Bits 27:24
    UINT32 ckevalid_enable                         :  1;  // Bits 28:28
    UINT32 idle_enable                             :  1;  // Bits 29:29
    UINT32 powerdown_enable                        :  1;  // Bits 30:30
    UINT32 selfrefresh_enable                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SPID_LOW_POWER_CTL_STRUCT;

typedef union {
  struct {
    UINT32 LPDDR_2N_CS_MRW                         :  1;  // Bits 0:0
    UINT32 reset_on_command                        :  4;  // Bits 4:1
    UINT32 reset_delay                             :  3;  // Bits 7:5
    UINT32 ignore_cke                              :  1;  // Bits 8:8
    UINT32 mask_cs                                 :  1;  // Bits 9:9
    UINT32 lp4_fifo_rd_wr                          :  1;  // Bits 10:10
    UINT32 disable_tristate                        :  1;  // Bits 11:11
    UINT32 cpgc_in_order                           :  1;  // Bits 12:12
    UINT32 cadb_enable                             :  1;  // Bits 13:13
    UINT32 deselect_enable                         :  1;  // Bits 14:14
    UINT32 Reset_CADB                              :  1;  // Bits 15:15
    UINT32 bus_retain_on_n_to_1_bubble             :  1;  // Bits 16:16
    UINT32 Block_xarb                              :  1;  // Bits 17:17
    UINT32 cadb_ispid_rank_control                 :  1;  // Bits 18:18
    UINT32                                         :  13;  // Bits 31:19
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_GS_CFG_TRAINING_STRUCT;

typedef union {
  struct {
    UINT32 dis_isoc_block_relaxation               :  1;  // Bits 0:0
    UINT32 lp_read_blkr                            :  1;  // Bits 1:1
    UINT32 pe_read_for_pe_blkr                     :  1;  // Bits 2:2
    UINT32 write_ph_blocks_read_pre                :  1;  // Bits 3:3
    UINT32 Read_threshold_for_lp_read_bklr         :  6;  // Bits 9:4
    UINT32 dis_ignore_1st_zqcs                     :  1;  // Bits 10:10
    UINT32 preempt_vc1_during_demote               :  1;  // Bits 11:11
    UINT32 dis_idle_ref_start                      :  1;  // Bits 12:12
    UINT32 invert_ALERT_n                          :  1;  // Bits 13:13
    UINT32 dis_oldest_isoch_pre_over_ph            :  1;  // Bits 14:14
    UINT32 dis_seperate_zq_block                   :  1;  // Bits 15:15
    UINT32 dis_cke_off_in_refresh                  :  1;  // Bits 16:16
    UINT32 allow_ecc_dft_overrides                 :  1;  // Bits 17:17
    UINT32 dis_wdb_clk_gate                        :  1;  // Bits 18:18
    UINT32 dis_mnt_clk_gate                        :  1;  // Bits 19:19
    UINT32 dis_scheds_clk_gate                     :  1;  // Bits 20:20
    UINT32 dis_lpmode_on_sagv                      :  1;  // Bits 21:21
    UINT32 ignore_fragment_safe_in_ref             :  1;  // Bits 22:22
    UINT32 cmi_short_rmw_stall                     :  1;  // Bits 23:23
    UINT32 ipq_ignore_write_ph                     :  1;  // Bits 24:24
    UINT32 spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SCHED_THIRD_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 No_CAS_threshold                        :  16;  // Bits 15:0
    UINT32 No_CAS_threshold_en                     :  1;  // Bits 16:16
    UINT32 Preemption_threshold_en                 :  1;  // Bits 17:17
    UINT32 Stop_count_during_tt                    :  1;  // Bits 18:18
    UINT32 Attempt_refresh_on_deadlock             :  1;  // Bits 19:19
    UINT32 MajorMode_force_duration                :  8;  // Bits 27:20
    UINT32 MajorMode_force_en                      :  1;  // Bits 28:28
    UINT32 Disable_blocking_rules                  :  1;  // Bits 29:29
    UINT32 Rank_join                               :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DEADLOCK_BREAKER_STRUCT;

typedef union {
  struct {
    UINT32 max_tRDWR                               :  6;  // Bits 5:0
    UINT32 bubble_cnt_visa_out_bits01              :  2;  // Bits 7:6
    UINT32 max_tWRWR                               :  6;  // Bits 13:8
    UINT32 bubble_cnt_visa_out_bit2                :  1;  // Bits 14:14
    UINT32                                         :  1;  // Bits 15:15
    UINT32 max_tWRRD                               :  8;  // Bits 23:16
    UINT32 max_tRDRD                               :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_XARB_TC_BUBBLE_INJ_STRUCT;

typedef union {
  struct {
    UINT32 bubble_inj_enable_read_switch           :  1;  // Bits 0:0
    UINT32 bubble_inj_enable_write_switch          :  1;  // Bits 1:1
    UINT32 bubble_inj_enable_any_cas_switch        :  1;  // Bits 2:2
    UINT32 Rank_mode                               :  1;  // Bits 3:3
    UINT32 DIMM_mode                               :  1;  // Bits 4:4
    UINT32 DIMM_mode_multiplier                    :  2;  // Bits 6:5
    UINT32 Dis_MRR_Bubble                          :  1;  // Bits 7:7
    UINT32 bubble_inj_read_switch_num_cas          :  8;  // Bits 15:8
    UINT32 bubble_inj_write_switch_num_cas         :  8;  // Bits 23:16
    UINT32 bubble_inj_any_cas_switch_num_cas       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_XARB_CFG_BUBBLE_INJ_STRUCT;

typedef union {
  struct {
    UINT32 GLB_GRACE_CNT                           :  8;  // Bits 7:0
    UINT32 GLB_DRV_GATE_DIS                        :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_STRUCT;

typedef union {
  struct {
    UINT32 dis_legacy_ph_blkr                      :  1;  // Bits 0:0
    UINT32 dis_legacy_pe_blkr                      :  1;  // Bits 1:1
    UINT32 low_wm_allowed_preempt_priorities       :  3;  // Bits 4:2
    UINT32 med_wm_allowed_preempt_priorities       :  3;  // Bits 7:5
    UINT32 high_wm_allowed_preempt_priorities      :  3;  // Bits 10:8
    UINT32 ph_block_pe                             :  1;  // Bits 11:11
    UINT32 blkr_effect_major_mode                  :  1;  // Bits 12:12
    UINT32 RIM_BW_optimization                     :  1;  // Bits 13:13
    UINT32 RIM_BW_prefer_VC1                       :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_BLOCKING_RULES_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Refresh_Rank_Mask                       :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 RefZQ_En_Start_Test_Sync                :  1;  // Bits 8:8
    UINT32                                         :  22;  // Bits 30:9
    UINT32 Panic_Refresh_Only                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_REUT_CH_MISC_REFRESH_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ZQ_Rank_Mask                            :  4;  // Bits 3:0
    UINT32                                         :  27;  // Bits 30:4
    UINT32 Always_Do_ZQ                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_REUT_CH_MISC_ZQ_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_width                            :  2;  // Bits 1:0
    UINT32 Rank_1_width                            :  2;  // Bits 3:2
    UINT32 Rank_2_width                            :  2;  // Bits 5:4
    UINT32 Rank_3_width                            :  2;  // Bits 7:6
    UINT32 MR4_PERIOD                              :  16;  // Bits 23:8
    UINT32 DDR4_TS_readout_en                      :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR_MR_PARAMS_STRUCT;

typedef union {
  struct {
    UINT32 Address                                 :  8;  // Bits 7:0
    UINT32 Data                                    :  8;  // Bits 15:8
    UINT32 Rank                                    :  2;  // Bits 17:16
    UINT32 Command                                 :  2;  // Bits 19:18
    UINT32 DRAM_mask                               :  9;  // Bits 28:20
    UINT32 Assume_idle                             :  1;  // Bits 29:29
    UINT32 DDR4_MA13                               :  1;  // Bits 30:30
    UINT32 Busy                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR_MR_COMMAND_STRUCT;

typedef union {
  struct {
    UINT32 Device_0                                :  8;  // Bits 7:0
    UINT32 Device_1                                :  8;  // Bits 15:8
    UINT32 Device_2                                :  8;  // Bits 23:16
    UINT32 Device_3                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR_MR_RESULT_0_STRUCT;

typedef union {
  struct {
    UINT32 Device_4                                :  8;  // Bits 7:0
    UINT32 Device_5                                :  8;  // Bits 15:8
    UINT32 Device_6                                :  8;  // Bits 23:16
    UINT32 Device_7                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR_MR_RESULT_1_STRUCT;

typedef union {
  struct {
    UINT32 Device_8                                :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR_MR_RESULT_2_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 Rank_1                                  :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Rank_2                                  :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 Rank_3                                  :  3;  // Bits 26:24
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_LPDDR_MR4_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  2;  // Bits 1:0
    UINT32                                         :  6;  // Bits 7:2
    UINT32 Rank_1                                  :  2;  // Bits 9:8
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Rank_2                                  :  2;  // Bits 17:16
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Rank_3                                  :  2;  // Bits 25:24
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR4_MPR_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Bit_0                                   :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_1                                   :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_2                                   :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_16                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_17                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_18                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_0                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_2                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DESWIZZLE_LOW_STRUCT;

typedef union {
  struct {
    UINT32 Bit_32                                  :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_33                                  :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_34                                  :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_48                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_49                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_50                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_4                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_6                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DESWIZZLE_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 OREF_RI                                 :  8;  // Bits 7:0
    UINT32 Refresh_HP_WM                           :  4;  // Bits 11:8
    UINT32 Refresh_panic_wm                        :  4;  // Bits 15:12
    UINT32 CounttREFIWhileRefEnOff                 :  1;  // Bits 16:16
    UINT32 HPRefOnMRS                              :  1;  // Bits 17:17
    UINT32 AlwaysRefOnMRS                          :  1;  // Bits 18:18
    UINT32                                         :  6;  // Bits 24:19
    UINT32 tREFIx9                                 :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_RFP_STRUCT;

typedef union {
  struct {
    UINT32 tREFI                                   :  16;  // Bits 15:0
    UINT32 tRFC                                    :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_RFTP_STRUCT;

typedef union {
  struct {
    UINT32 tXSDLL                                  :  12;  // Bits 11:0
    UINT32                                         :  4;  // Bits 15:12
    UINT32 tZQOPER                                 :  10;  // Bits 25:16
    UINT32 tMOD                                    :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_SRFTP_STRUCT;

typedef union {
  struct {
    UINT32 Ref_Interval                            :  11;  // Bits 10:0
    UINT32 Ref_Stagger_En                          :  1;  // Bits 11:11
    UINT32 Ref_Stagger_Mode                        :  1;  // Bits 12:12
    UINT32 Disable_Stolen_Refresh                  :  1;  // Bits 13:13
    UINT32 En_Ref_Type_Display                     :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_MC_REFRESH_STAGGER_STRUCT;

typedef union {
  struct {
    UINT32 ZQCS_period                             :  10;  // Bits 9:0
    UINT32 tZQCS                                   :  10;  // Bits 19:10
    UINT32 tZQCAL                                  :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_ZQCAL_STRUCT;

typedef union {
  struct {
    UINT32 MR2_shaddow                             :  14;  // Bits 13:0
    UINT32 SRT_avail                               :  2;  // Bits 15:14
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_MR2_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 MR4_sh_low                              :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 MR4_sh_high                             :  10;  // Bits 13:4
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_MR4_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 Rank_occupancy                          :  8;  // Bits 7:0
    UINT32 SRX_reset                               :  1;  // Bits 8:8
    UINT32 LPDDR4_current_FSP                      :  1;  // Bits 9:9
    UINT32 LPDDR4_current_FSP_tracking             :  1;  // Bits 10:10
    UINT32 Reset_refresh_debt                      :  1;  // Bits 11:11
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_MC_INIT_STATE_STRUCT;

typedef union {
  struct {
    UINT32 VISAByteSel                             :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 RefFSMRankSel                           :  2;  // Bits 9:8
    UINT32 Ref_counterSel                          :  3;  // Bits 12:10
    UINT32 Enable_Ref_Status_Sample                :  1;  // Bits 13:13
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_WDB_VISA_SEL_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_IDLE_ENERGY                       :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_IDLE_ENERGY                       :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_PM_DIMM_IDLE_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_PD_ENERGY                         :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_PD_ENERGY                         :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_PM_DIMM_PD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_ACT_ENERGY                        :  8;  // Bits 7:0
    UINT32 DIMM1_ACT_ENERGY                        :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_PM_DIMM_ACT_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_RD_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_RD_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_PM_DIMM_RD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_WR_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_WR_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_PM_DIMM_WR_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_ECC_INJECT_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 Dec_tCWL                                :  6;  // Bits 5:0
    UINT32 Add_tCWL                                :  6;  // Bits 11:6
    UINT32 Add_1Qclk_delay                         :  1;  // Bits 12:12
    UINT32                                         :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_WR_DELAY_STRUCT;

typedef union {
  struct {
    UINT32 ECC                                     :  8;  // Bits 7:0
    UINT32 RRD_DFT_Mode                            :  2;  // Bits 9:8
    UINT32 LFSR_Seed_Index                         :  5;  // Bits 14:10
    UINT32 Inversion_Mode                          :  1;  // Bits 15:15
    UINT32 AddressBased                            :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_READ_RETURN_DFT_STRUCT;

typedef union {
  struct {
    UINT32 Bit_0                                   :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_1                                   :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_2                                   :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_16                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_17                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_18                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_0                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_2                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DESWIZZLE_LOW_ERM_STRUCT;

typedef union {
  struct {
    UINT32 Bit_32                                  :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_33                                  :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_34                                  :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_48                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_49                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_50                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_4                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_6                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DESWIZZLE_HIGH_ERM_STRUCT;

typedef union {
  struct {
    UINT32 PBR_Disable                             :  1;  // Bits 0:0
    UINT32 PBR_OOO_Dis                             :  1;  // Bits 1:1
    UINT32 PBR_Issue_NOP                           :  1;  // Bits 2:2
    UINT32 PBR_Disable_on_hot                      :  1;  // Bits 3:3
    UINT32 PBR_Exit_on_Idle_Cnt                    :  6;  // Bits 9:4
    UINT32 tRFCpb                                  :  10;  // Bits 19:10
    UINT32 Refresh_ABR_release                     :  4;  // Bits 23:20
    UINT32 PBR_extended_disable_while_DQS_OSC      :  1;  // Bits 24:24
    UINT32 SPARE                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_SC_PBR_STRUCT;

typedef union {
  struct {
    UINT32 CPGC2MC_RD_CREDITS                      :  8;  // Bits 7:0
    UINT32 CPGC2MC_WR_CREDITS                      :  8;  // Bits 15:8
    UINT32 MC2CPGC_RD_CREDITS                      :  8;  // Bits 23:16
    UINT32 CPGC_ACTIVE                             :  1;  // Bits 24:24
    UINT32 CPGC_sync_cpl                           :  1;  // Bits 25:25
    UINT32 CPGC_sync_phase                         :  1;  // Bits 26:26
    UINT32 CPGC_Dis_Allow_CPL_interleave           :  1;  // Bits 27:27
    UINT32 CPGC_ECC_BYTE                           :  3;  // Bits 30:28
    UINT32 Stall_CPGC_CMI_Req                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_MC_CPGC_CMI_STRUCT;

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
    UINT32 DDR4_alert                              :  1;  // Bits 20:20
    UINT32                                         :  11;  // Bits 31:21
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_MC_CPGC_MISC_DFT_STRUCT;

typedef union {
  struct {
    UINT32 tOSCO                                   :  7;  // Bits 6:0
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_LPDDR4_MISC_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_PM_ALL_RANKS_CKE_LOW_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 tXSR                                    :  10;  // Bits 9:0
    UINT32 count_block_wr_on_srx                   :  7;  // Bits 16:10
    UINT32 serial_zq_between_sub_ch                :  1;  // Bits 17:17
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_TC_SREXITTP_STRUCT;

typedef union {
  struct {
    UINT32 DQSOSCL_PERIOD                          :  16;  // Bits 15:0
    UINT32 MR19toBlockAckPeriod                    :  8;  // Bits 23:16
    UINT32 DIS_SRX_DQSOSCL                         :  1;  // Bits 24:24
    UINT32                                         :  1;  // Bits 25:25
    UINT32 disable_wr_on_pkgc_exit                 :  1;  // Bits 26:26
    UINT32 disable_wr_on_SR_exit                   :  1;  // Bits 27:27
    UINT32 disable_PMreqWaitForMR19                :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT;

typedef union {
  struct {
    UINT32 Enable_WDB_Capture                      :  1;  // Bits 0:0
    UINT32                                         :  7;  // Bits 7:1
    UINT32 WDB_Starting_Capture_Pointer            :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_Ending_Capture_Pointer              :  6;  // Bits 21:16
    UINT32 WDB_Capture_Block_SubCh                 :  2;  // Bits 23:22
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_REUT_CH_WDB_CAPTURE_CTL_STRUCT;

typedef union {
  struct {
    UINT32 WDB_SC0_Current_Capture_Pointer         :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 WDB_SC1_Current_Capture_Pointer         :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_REUT_CH_WDB_CAPTURE_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 DATALow                                 :  32;  // Bits 31:0
    UINT32 DATAHigh                                :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_WDB_RD_WR_DFX_DATA_STRUCT;

typedef union {
  struct {
    UINT32 GO                                      :  1;  // Bits 0:0
    UINT32 Chunk_Sel                               :  8;  // Bits 8:1
    UINT32 Op                                      :  1;  // Bits 9:9
    UINT32 SubCh                                   :  1;  // Bits 10:10
    UINT32 WID                                     :  6;  // Bits 16:11
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_WDB_RD_WR_DFX_CTL_STRUCT;

typedef union {
  struct {
    UINT32 DQS_INTERVAL_FSM_status                 :  4;  // Bits 3:0
    UINT32 TEMP_RD_FSM_status                      :  5;  // Bits 8:4
    UINT32 REFRATE_CHNG_FSM_status                 :  2;  // Bits 10:9
    UINT32 ZQCS_FSM_status                         :  3;  // Bits 13:11
    UINT32 EXE_REF_FSM_status                      :  3;  // Bits 16:14
    UINT32 MAIN_REF_FSM_status                     :  3;  // Bits 19:17
    UINT32 MAIN_SR_FSM_status                      :  4;  // Bits 23:20
    UINT32 counter_status                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_REF_FSM_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR4_MR1_ODIC_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_MR5_RTT_PARK_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_MR1_RTT_NOM_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_LPDDR4_DISCRETE_MR_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_LPDDR4_DISCRETE_MR_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_LPDDR4_DISCRETE_MR_VALUES_2_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_LPDDR4_DISCRETE_MR_VALUES_3_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_LPDDR4_DISCRETE_MR_VALUES_4_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_LPDDR4_DISCRETE_MR_VALUES_5_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_LPDDR4_DISCRETE_MR_VALUES_6_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_LPDDR4_DISCRETE_MR_VALUES_7_STRUCT;

typedef union {
  struct {
    UINT32 MR0                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR1                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR4_MR0_MR1_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR2                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR3                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR4_MR2_MR3_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR4                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR5                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR4_MR4_MR5_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR6                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR7                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR4_MR6_MR7_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_MR2_RTT_WR_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_MR6_VREF_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_MR6_VREF_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 MR1                                     :  8;  // Bits 7:0
    UINT32 MR2                                     :  8;  // Bits 15:8
    UINT32 MR3                                     :  8;  // Bits 23:16
    UINT32 MR11                                    :  8;  // Bits 31:24
    UINT32 MR12                                    :  8;  // Bits 39:32
    UINT32 MR13                                    :  8;  // Bits 47:40
    UINT32 MR22                                    :  8;  // Bits 55:48
    UINT32 MR23                                    :  8;  // Bits 63:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_LPDDR_MR_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 DDR4_Restore_MR                         :  8;  // Bits 7:0
    UINT32 DDR4_Restore_MR1_ODIC_Per_Device        :  1;  // Bits 8:8
    UINT32 DDR4_Restore_MR2_Per_Device             :  1;  // Bits 9:9
    UINT32 DDR4_Restore_MR6_Per_Device             :  1;  // Bits 10:10
    UINT32 DDR4_PDA_VREF_Initial                   :  1;  // Bits 11:11
    UINT32 DDR4_Short_VREF_Exit                    :  1;  // Bits 12:12
    UINT32 LPDDR_Restore_MR                        :  9;  // Bits 21:13
    UINT32 do_ZQCL                                 :  1;  // Bits 22:22
    UINT32 zero_rank1_MR11                         :  1;  // Bits 23:23
    UINT32 reset_flow                              :  1;  // Bits 24:24
    UINT32 vref_time_per_byte                      :  1;  // Bits 25:25
    UINT32 do_pda_for_1R1R                         :  1;  // Bits 26:26
    UINT32 add_initial_vref                        :  1;  // Bits 27:27
    UINT32 LPDDR4_switch_FSP                       :  1;  // Bits 28:28
    UINT32 do_dq_osc_start                         :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
    UINT32 tVREFDQ                                 :  10;  // Bits 41:32
    UINT32 cbit_count_each_rank                    :  1;  // Bits 42:42
    UINT32 do_PDA_for_ECC                          :  1;  // Bits 43:43
    UINT32 DDR4_Restore_MR5_Per_Device             :  1;  // Bits 44:44
    UINT32 TwoDPC_support                          :  1;  // Bits 45:45
    UINT32 DDR4_Restore_MR1_RTTNOM_Per_Device      :  1;  // Bits 46:46
    UINT32 Fast_PDA                                :  1;  // Bits 47:47
    UINT32 always_count_tFC                        :  1;  // Bits 48:48
    UINT32 PDA_wr_delay                            :  6;  // Bits 54:49
    UINT32 LPDDR4_per_byte_vref                    :  1;  // Bits 55:55
    UINT32 Clear_VRCG                              :  1;  // Bits 56:56
    UINT32 GV_auto_enable                          :  1;  // Bits 57:57
    UINT32 LPDDR4_split_transition                 :  1;  // Bits 58:58
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_MRS_FSM_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Run                                     :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_MRS_FSM_RUN_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_DDR4_MR1_ODIC_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 data_trace_mode                         :  2;  // Bits 1:0
    UINT32 UI_to_trace                             :  3;  // Bits 4:2
    UINT32 byte_to_trace                           :  3;  // Bits 7:5
    UINT32 ECC_EN                                  :  1;  // Bits 8:8
    UINT32 ECC_BYTE_replace                        :  3;  // Bits 11:9
    UINT32 trace_read_data                         :  1;  // Bits 12:12
    UINT32 trace_write_data                        :  1;  // Bits 13:13
    UINT32 DDRPL_Activate                          :  1;  // Bits 14:14
    UINT32 SCHTrace                                :  1;  // Bits 15:15
    UINT32 dis_early_ind_override                  :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_PL_AGENT_CFG_DTF_STRUCT;

typedef union {
  struct {
    UINT32 GLB_GRACE_CNT                           :  8;  // Bits 7:0
    UINT32 GLB_DRV_GATE_DIS                        :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_STRUCT;

typedef union {
  struct {
    UINT32 ODIC_Rank0                              :  2;  // Bits 1:0
    UINT32 ODIC_Rank1                              :  2;  // Bits 3:2
    UINT32 RTT_WR_Rank0                            :  3;  // Bits 6:4
    UINT32 RTT_WR_Rank1                            :  3;  // Bits 9:7
    UINT32 VREF_Rank0                              :  7;  // Bits 16:10
    UINT32 VREF_Rank1                              :  7;  // Bits 23:17
    UINT32 RTT_NOM_Rank0                           :  3;  // Bits 26:24
    UINT32 RTT_NOM_Rank1                           :  3;  // Bits 29:27
    UINT32 RTT_PARK_Rank0Low                       :  2;  // Bits 31:30
    UINT32 RTT_PARK_Rank0High                      :  1;  // Bits 32:32
    UINT32 RTT_PARK_Rank1                          :  3;  // Bits 35:33
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_ECC_DEVICE_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 ODIC_Rank0                              :  2;  // Bits 1:0
    UINT32 ODIC_Rank1                              :  2;  // Bits 3:2
    UINT32 RTT_WR_Rank0                            :  3;  // Bits 6:4
    UINT32 RTT_WR_Rank1                            :  3;  // Bits 9:7
    UINT32 VREF_Rank0                              :  7;  // Bits 16:10
    UINT32 VREF_Rank1                              :  7;  // Bits 23:17
    UINT32 RTT_NOM_Rank0                           :  3;  // Bits 26:24
    UINT32 RTT_NOM_Rank1                           :  3;  // Bits 29:27
    UINT32 RTT_PARK_Rank0Low                       :  2;  // Bits 31:30
    UINT32 RTT_PARK_Rank0High                      :  1;  // Bits 32:32
    UINT32 RTT_PARK_Rank1                          :  3;  // Bits 35:33
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} CH1_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  8;  // Bits 7:0
    UINT32 ForceX2Ref                              :  1;  // Bits 8:8
    UINT32 ForceX4Ref                              :  1;  // Bits 9:9
    UINT32 DisLowRefRate                           :  1;  // Bits 10:10
    UINT32 disRegardZQonSRtime                     :  1;  // Bits 11:11
    UINT32 Decoder_EBH                             :  2;  // Bits 13:12
    UINT32                                         :  1;  // Bits 14:14
    UINT32 DisSREXcnt                              :  1;  // Bits 15:15
    UINT32 Spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} CH1_CR_MCMNTS_SPARE_STRUCT;

typedef union {
  struct {
    UINT32 tRP                                     :  6;  // Bits 5:0
    UINT32 tRPab_ext                               :  3;  // Bits 8:6
    UINT32 tRAS                                    :  7;  // Bits 15:9
    UINT32 tRDPRE                                  :  5;  // Bits 20:16
    UINT32 tPPD                                    :  3;  // Bits 23:21
    UINT32 tWRPRE                                  :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_PRE_STRUCT;

typedef union {
  struct {
    UINT32 tFAW                                    :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 tRRD_sg                                 :  5;  // Bits 12:8
    UINT32 tRRD_dg                                 :  5;  // Bits 17:13
    UINT32 derating_ext                            :  3;  // Bits 20:18
    UINT32 tRCD_wr                                 :  6;  // Bits 26:21
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_ACT_STRUCT;

typedef union {
  struct {
    UINT32 tRDRD_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDRD_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_RDRD_STRUCT;

typedef union {
  struct {
    UINT32 tRDWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tRDWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tRDWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tRDWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_RDWR_STRUCT;

typedef union {
  struct {
    UINT32 tWRRD_sg                                :  8;  // Bits 7:0
    UINT32 tWRRD_dg                                :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 tWRRD_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRRD_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_WRRD_STRUCT;

typedef union {
  struct {
    UINT32 tWRWR_sg                                :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 tWRWR_dg                                :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 tWRWR_dr                                :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 tWRWR_dd                                :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_WRWR_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_latency                          :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank_1_latency                          :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank_2_latency                          :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank_3_latency                          :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank_4_latency                          :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank_5_latency                          :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank_6_latency                          :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank_7_latency                          :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_SC_ROUNDTRIP_LATENCY_STRUCT;

typedef union {
  struct {
    UINT32 dis_opp_cas                             :  1;  // Bits 0:0
    UINT32 dis_opp_is_cas                          :  1;  // Bits 1:1
    UINT32 dis_opp_ras                             :  1;  // Bits 2:2
    UINT32 dis_opp_is_ras                          :  1;  // Bits 3:3
    UINT32 dis_2c_byp                              :  1;  // Bits 4:4
    UINT32 dis_deprd_opt                           :  1;  // Bits 5:5
    UINT32 dis_pt_it                               :  1;  // Bits 6:6
    UINT32 dis_prcnt_ring                          :  1;  // Bits 7:7
    UINT32 dis_prcnt_sa                            :  1;  // Bits 8:8
    UINT32 dis_blkr_ph                             :  1;  // Bits 9:9
    UINT32 dis_blkr_pe                             :  1;  // Bits 10:10
    UINT32 dis_blkr_pm                             :  1;  // Bits 11:11
    UINT32 dis_odt                                 :  1;  // Bits 12:12
    UINT32 OE_alw_off                              :  1;  // Bits 13:13
    UINT32 block_rpq                               :  1;  // Bits 14:14
    UINT32 block_ipq                               :  1;  // Bits 15:15
    UINT32 block_wpq                               :  1;  // Bits 16:16
    UINT32 dis_zq                                  :  1;  // Bits 17:17
    UINT32 dis_tt                                  :  1;  // Bits 18:18
    UINT32 dis_opp_ref                             :  1;  // Bits 19:19
    UINT32 long_zq                                 :  1;  // Bits 20:20
    UINT32 dis_srx_zq                              :  1;  // Bits 21:21
    UINT32 serialize_zq                            :  1;  // Bits 22:22
    UINT32 zq_fast_exec                            :  1;  // Bits 23:23
    UINT32 dis_starved_read_rank_block             :  1;  // Bits 24:24
    UINT32 dis_idle_preempt                        :  1;  // Bits 25:25
    UINT32 find_first_allocation                   :  1;  // Bits 26:26
    UINT32 duplicate_spid_rank                     :  1;  // Bits 27:27
    UINT32 wio_merge_lpmode_2_3                    :  1;  // Bits 28:28
    UINT32 dis_5cyc_write_gap                      :  1;  // Bits 29:29
    UINT32 dis_5cyc_read_gap                       :  1;  // Bits 30:30
    UINT32 dis_clk_gate                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SCHED_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 dis_srx_mr4                             :  1;  // Bits 0:0
    UINT32 dis_ck_tristate                         :  1;  // Bits 1:1
    UINT32 dis_burst_ref_limit                     :  1;  // Bits 2:2
    UINT32 dis_bus_retain                          :  1;  // Bits 3:3
    UINT32 dis_async_odt                           :  1;  // Bits 4:4
    UINT32 dis_SRX_reset                           :  1;  // Bits 5:5
    UINT32 SPARE_CBIT                              :  1;  // Bits 6:6
    UINT32 dis_SRX_MRS_MR4                         :  1;  // Bits 7:7
    UINT32 dis_opp_ref_idle_delay                  :  1;  // Bits 8:8
    UINT32 dis_ignore_1st_trefi                    :  1;  // Bits 9:9
    UINT32 echo_mask                               :  9;  // Bits 18:10
    UINT32 dis_early_go                            :  1;  // Bits 19:19
    UINT32 dis_new_wr_to_full                      :  1;  // Bits 20:20
    UINT32 WIO2_DBIac_Dis                          :  1;  // Bits 21:21
    UINT32 drainless_SAGV_do_zq                    :  1;  // Bits 22:22
    UINT32 do_temp_reading_after_drainless_SAGV    :  1;  // Bits 23:23
    UINT32 ignore_refresh_between_SR               :  1;  // Bits 24:24
    UINT32 DisWrActThrottleOnAnyRead               :  1;  // Bits 25:25
    UINT32 enable_fdata_nak                        :  1;  // Bits 26:26
    UINT32 spare                                   :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SCHED_SECOND_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 WDAR                                    :  1;  // Bits 0:0
    UINT32 WDB_Block_En                            :  1;  // Bits 1:1
    UINT32                                         :  2;  // Bits 3:2
    UINT32 isolate_data_return                     :  1;  // Bits 4:4
    UINT32                                         :  12;  // Bits 16:5
    UINT32 dft_block_enable                        :  1;  // Bits 17:17
    UINT32 SAM_overloading                         :  3;  // Bits 20:18
    UINT32                                         :  3;  // Bits 23:21
    UINT32 Stretch_mode_en                         :  1;  // Bits 24:24
    UINT32 STF                                     :  5;  // Bits 29:25
    UINT32 Stretch_delay_from_write                :  1;  // Bits 30:30
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DFT_MISC_STRUCT;

typedef union {
  struct {
    UINT32 ECC_Inject                              :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 ECC_correction_disable                  :  1;  // Bits 4:4
    UINT32                                         :  3;  // Bits 7:5
    UINT32 DIS_MCA_LOG                             :  1;  // Bits 8:8
    UINT32 DIS_PCH_EVENT                           :  1;  // Bits 9:9
    UINT32 DIS_RCH_POISON                          :  1;  // Bits 10:10
    UINT32 DIS_RCH_ERROR                           :  1;  // Bits 11:11
    UINT32                                         :  4;  // Bits 15:12
    UINT32 ECC_trigger                             :  2;  // Bits 17:16
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_ECC_DFT_STRUCT;

typedef union {
  struct {
    UINT32 PCIT                                    :  8;  // Bits 7:0
    UINT32                                         :  8;  // Bits 15:8
    UINT32 PCIT_GT                                 :  8;  // Bits 23:16
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_PCIT_STRUCT;

typedef union {
  struct {
    UINT32 PDWN_idle_counter                       :  12;  // Bits 11:0
    UINT32 APD                                     :  1;  // Bits 12:12
    UINT32 PPD                                     :  1;  // Bits 13:13
    UINT32 Slow_Exit                               :  1;  // Bits 14:14
    UINT32 Global_PD                               :  1;  // Bits 15:15
    UINT32 TT_idle_counter                         :  8;  // Bits 23:16
    UINT32 dis_cke_tt                              :  1;  // Bits 24:24
    UINT32 write_threshold                         :  6;  // Bits 30:25
    UINT32 allow_opp_ref_below_write_threhold      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_PM_PDWN_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 Dis_Opp_rd                              :  1;  // Bits 0:0
    UINT32 ACT_Enable                              :  1;  // Bits 1:1
    UINT32 PRE_Enable                              :  1;  // Bits 2:2
    UINT32 MAX_RPQ_CAS                             :  4;  // Bits 6:3
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_WMM_READ_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 CERRSTS                                 :  1;  // Bits 0:0
    UINT32 MERRSTS                                 :  1;  // Bits 1:1
    UINT32                                         :  14;  // Bits 15:2
    UINT32 ERRSYND                                 :  8;  // Bits 23:16
    UINT32 ERRCHUNK                                :  3;  // Bits 26:24
    UINT32 ERRRANK                                 :  2;  // Bits 28:27
    UINT32 ERRBANK                                 :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_ECCERRLOG0_STRUCT;

typedef union {
  struct {
    UINT32 ERRROW                                  :  17;  // Bits 16:0
    UINT32 ERRCOL                                  :  12;  // Bits 28:17
    UINT32 ERRBANKGROUP                            :  2;  // Bits 30:29
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_ECCERRLOG1_STRUCT;

typedef union {
  struct {
    UINT32 tCKE                                    :  5;  // Bits 4:0
    UINT32                                         :  3;  // Bits 7:5
    UINT32 tXP                                     :  5;  // Bits 12:8
    UINT32                                         :  3;  // Bits 15:13
    UINT32 tXPDLL                                  :  6;  // Bits 21:16
    UINT32 tPRPDEN                                 :  2;  // Bits 23:22
    UINT32 tRDPDEN                                 :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 tWRPDEN                                 :  8;  // Bits 39:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_TC_PWRDN_STRUCT;

typedef union {
  struct {
    UINT32 RPQ_disable                             :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_QUEUE_ENTRY_DISABLE_RPQ_STRUCT;

typedef union {
  struct {
    UINT32 IPQ_disable                             :  16;  // Bits 15:0
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_QUEUE_ENTRY_DISABLE_IPQ_STRUCT;

typedef union {
  struct {
    UINT32 WPQ_disableLow                          :  32;  // Bits 31:0
    UINT32 WPQ_disableHigh                         :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_QUEUE_ENTRY_DISABLE_WPQ_STRUCT;

typedef union {
  struct {
    UINT32 WMM_entry_wm                            :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 WMM_exit_wm                             :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 WIM_wm                                  :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Write_Isoc_CAS_count                    :  8;  // Bits 31:24
    UINT32 Read_CAS_count                          :  8;  // Bits 39:32
    UINT32 Write_CAS_count                         :  8;  // Bits 47:40
    UINT32 Write_CAS_count_for_VC1                 :  8;  // Bits 55:48
    UINT32 Write_threshold_for_lp_read_bklr        :  7;  // Bits 62:56
    UINT32 En_Wr_in_WIM_during_TT                  :  1;  // Bits 63:63
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_SC_WDBWM_STRUCT;

typedef union {
  struct {
    UINT32 ODT_read_duration                       :  4;  // Bits 3:0
    UINT32 ODT_Read_Delay                          :  4;  // Bits 7:4
    UINT32 ODT_write_duration                      :  4;  // Bits 11:8
    UINT32 ODT_Write_Delay                         :  4;  // Bits 15:12
    UINT32 tCL                                     :  6;  // Bits 21:16
    UINT32 tCWL                                    :  6;  // Bits 27:22
    UINT32 Write_Early_ODT                         :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
    UINT32 tAONPD                                  :  5;  // Bits 36:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_TC_ODT_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  16;  // Bits 15:0
    UINT32 WMM_exit_wm_for_FBRMM                   :  7;  // Bits 22:16
    UINT32 Spare_RW_V                              :  9;  // Bits 31:23
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_MCSCHEDS_SPARE_STRUCT;

typedef union {
  struct {
    UINT32 Read_Rank_0                             :  4;  // Bits 3:0
    UINT32 Read_Rank_1                             :  4;  // Bits 7:4
    UINT32 Read_Rank_2                             :  4;  // Bits 11:8
    UINT32 Read_Rank_3                             :  4;  // Bits 15:12
    UINT32 Write_Rank_0                            :  4;  // Bits 19:16
    UINT32 Write_Rank_1                            :  4;  // Bits 23:20
    UINT32 Write_Rank_2                            :  4;  // Bits 27:24
    UINT32 Write_Rank_3                            :  4;  // Bits 31:28
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_ODT_MATRIX_STRUCT;

typedef union {
  struct {
    UINT32 dft_block_cycles                        :  16;  // Bits 15:0
    UINT32 dft_nonblock_cycles                     :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DFT_BLOCK_STRUCT;

typedef union {
  struct {
    UINT32 DRAM_technology                         :  3;  // Bits 2:0
    UINT32 CMD_stretch                             :  2;  // Bits 4:3
    UINT32 N_to_1_ratio                            :  3;  // Bits 7:5
    UINT32 Address_mirror                          :  4;  // Bits 11:8
    UINT32 tCPDED                                  :  3;  // Bits 14:12
    UINT32 disable_tristate                        :  1;  // Bits 15:15
    UINT32 ck_to_cke                               :  3;  // Bits 18:16
    UINT32 tCAL                                    :  3;  // Bits 21:19
    UINT32 frequency_point                         :  2;  // Bits 23:22
    UINT32 enable_odt_matrix                       :  1;  // Bits 24:24
    UINT32 cs_to_cke                               :  3;  // Bits 27:25
    UINT32 x8_device                               :  2;  // Bits 29:28
    UINT32 no_gear2_param_divide                   :  1;  // Bits 30:30
    UINT32 gear2                                   :  1;  // Bits 31:31
    UINT32 ddr4_1dpc                               :  2;  // Bits 33:32
    UINT32 Limit_MM_Transitions                    :  1;  // Bits 34:34
    UINT32 pl_trace_only_cs_cmd                    :  1;  // Bits 35:35
    UINT32 two_cycle_cke_idle                      :  1;  // Bits 36:36
    UINT32 disable_ca_tristate                     :  1;  // Bits 37:37
    UINT32 disable_ck_tristate                     :  1;  // Bits 38:38
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_SC_GS_CFG_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_PH_THROTTLING_0_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_PH_THROTTLING_1_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_PH_THROTTLING_2_STRUCT;

typedef union {
  struct {
    UINT32 loaded_same_rank                        :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 unloaded_same_rank                      :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 loaded_different_rank                   :  6;  // Bits 21:16
    UINT32                                         :  2;  // Bits 23:22
    UINT32 unloaded_different_rank                 :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_PH_THROTTLING_3_STRUCT;

typedef union {
  struct {
    UINT32 Low_WM                                  :  6;  // Bits 5:0
    UINT32 Med_WM                                  :  6;  // Bits 11:6
    UINT32 High_WM                                 :  6;  // Bits 17:12
    UINT32 PHs_allowed_under_low_wm                :  4;  // Bits 21:18
    UINT32 PHs_allowed_under_med_wm                :  4;  // Bits 25:22
    UINT32 PHs_allowed_under_high_wm               :  4;  // Bits 29:26
    UINT32 RPQ_PHs_weight                          :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_WPQ_THRESHOLD_STRUCT;

typedef union {
  struct {
    UINT32 Ring                                    :  10;  // Bits 9:0
    UINT32 SA                                      :  10;  // Bits 19:10
    UINT32 VC0_latency_guard_timer_x16             :  9;  // Bits 28:20
    UINT32 VC1_latency_guard_timer_x8Low           :  3;  // Bits 31:29
    UINT32 VC1_latency_guard_timer_x8High          :  8;  // Bits 39:32
    UINT32 VC1_Isoc_latency_guard_timer_x8         :  11;  // Bits 50:40
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_SC_PR_CNT_CONFIG_STRUCT;

typedef union {
  struct {
    UINT32 CKE_Override                            :  4;  // Bits 3:0
    UINT32                                         :  12;  // Bits 15:4
    UINT32 CKE_On                                  :  4;  // Bits 19:16
    UINT32                                         :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_REUT_CH_MISC_CKE_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ODT_Override                            :  4;  // Bits 3:0
    UINT32                                         :  12;  // Bits 15:4
    UINT32 ODT_On                                  :  4;  // Bits 19:16
    UINT32                                         :  11;  // Bits 30:20
    UINT32 MPR_Train_DDR_On                        :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_REUT_CH_MISC_ODT_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 raise_cke_after_exit_latency            :  1;  // Bits 0:0
    UINT32 idle_latency                            :  3;  // Bits 3:1
    UINT32 idle_length                             :  4;  // Bits 7:4
    UINT32 powerdown_latency                       :  4;  // Bits 11:8
    UINT32 powerdown_length                        :  4;  // Bits 15:12
    UINT32 selfrefresh_latency                     :  4;  // Bits 19:16
    UINT32 selfrefresh_length                      :  4;  // Bits 23:20
    UINT32 ckevalid_length                         :  4;  // Bits 27:24
    UINT32 ckevalid_enable                         :  1;  // Bits 28:28
    UINT32 idle_enable                             :  1;  // Bits 29:29
    UINT32 powerdown_enable                        :  1;  // Bits 30:30
    UINT32 selfrefresh_enable                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SPID_LOW_POWER_CTL_STRUCT;

typedef union {
  struct {
    UINT32 LPDDR_2N_CS_MRW                         :  1;  // Bits 0:0
    UINT32 reset_on_command                        :  4;  // Bits 4:1
    UINT32 reset_delay                             :  3;  // Bits 7:5
    UINT32 ignore_cke                              :  1;  // Bits 8:8
    UINT32 mask_cs                                 :  1;  // Bits 9:9
    UINT32 lp4_fifo_rd_wr                          :  1;  // Bits 10:10
    UINT32 disable_tristate                        :  1;  // Bits 11:11
    UINT32 cpgc_in_order                           :  1;  // Bits 12:12
    UINT32 cadb_enable                             :  1;  // Bits 13:13
    UINT32 deselect_enable                         :  1;  // Bits 14:14
    UINT32 Reset_CADB                              :  1;  // Bits 15:15
    UINT32 bus_retain_on_n_to_1_bubble             :  1;  // Bits 16:16
    UINT32 Block_xarb                              :  1;  // Bits 17:17
    UINT32 cadb_ispid_rank_control                 :  1;  // Bits 18:18
    UINT32                                         :  13;  // Bits 31:19
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_GS_CFG_TRAINING_STRUCT;

typedef union {
  struct {
    UINT32 dis_isoc_block_relaxation               :  1;  // Bits 0:0
    UINT32 lp_read_blkr                            :  1;  // Bits 1:1
    UINT32 pe_read_for_pe_blkr                     :  1;  // Bits 2:2
    UINT32 write_ph_blocks_read_pre                :  1;  // Bits 3:3
    UINT32 Read_threshold_for_lp_read_bklr         :  6;  // Bits 9:4
    UINT32 dis_ignore_1st_zqcs                     :  1;  // Bits 10:10
    UINT32 preempt_vc1_during_demote               :  1;  // Bits 11:11
    UINT32 dis_idle_ref_start                      :  1;  // Bits 12:12
    UINT32 invert_ALERT_n                          :  1;  // Bits 13:13
    UINT32 dis_oldest_isoch_pre_over_ph            :  1;  // Bits 14:14
    UINT32 dis_seperate_zq_block                   :  1;  // Bits 15:15
    UINT32 dis_cke_off_in_refresh                  :  1;  // Bits 16:16
    UINT32 allow_ecc_dft_overrides                 :  1;  // Bits 17:17
    UINT32 dis_wdb_clk_gate                        :  1;  // Bits 18:18
    UINT32 dis_mnt_clk_gate                        :  1;  // Bits 19:19
    UINT32 dis_scheds_clk_gate                     :  1;  // Bits 20:20
    UINT32 dis_lpmode_on_sagv                      :  1;  // Bits 21:21
    UINT32 ignore_fragment_safe_in_ref             :  1;  // Bits 22:22
    UINT32 cmi_short_rmw_stall                     :  1;  // Bits 23:23
    UINT32 ipq_ignore_write_ph                     :  1;  // Bits 24:24
    UINT32 spare                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SCHED_THIRD_CBIT_STRUCT;

typedef union {
  struct {
    UINT32 No_CAS_threshold                        :  16;  // Bits 15:0
    UINT32 No_CAS_threshold_en                     :  1;  // Bits 16:16
    UINT32 Preemption_threshold_en                 :  1;  // Bits 17:17
    UINT32 Stop_count_during_tt                    :  1;  // Bits 18:18
    UINT32 Attempt_refresh_on_deadlock             :  1;  // Bits 19:19
    UINT32 MajorMode_force_duration                :  8;  // Bits 27:20
    UINT32 MajorMode_force_en                      :  1;  // Bits 28:28
    UINT32 Disable_blocking_rules                  :  1;  // Bits 29:29
    UINT32 Rank_join                               :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DEADLOCK_BREAKER_STRUCT;

typedef union {
  struct {
    UINT32 max_tRDWR                               :  6;  // Bits 5:0
    UINT32 bubble_cnt_visa_out_bits01              :  2;  // Bits 7:6
    UINT32 max_tWRWR                               :  6;  // Bits 13:8
    UINT32 bubble_cnt_visa_out_bit2                :  1;  // Bits 14:14
    UINT32                                         :  1;  // Bits 15:15
    UINT32 max_tWRRD                               :  8;  // Bits 23:16
    UINT32 max_tRDRD                               :  6;  // Bits 29:24
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_XARB_TC_BUBBLE_INJ_STRUCT;

typedef union {
  struct {
    UINT32 bubble_inj_enable_read_switch           :  1;  // Bits 0:0
    UINT32 bubble_inj_enable_write_switch          :  1;  // Bits 1:1
    UINT32 bubble_inj_enable_any_cas_switch        :  1;  // Bits 2:2
    UINT32 Rank_mode                               :  1;  // Bits 3:3
    UINT32 DIMM_mode                               :  1;  // Bits 4:4
    UINT32 DIMM_mode_multiplier                    :  2;  // Bits 6:5
    UINT32 Dis_MRR_Bubble                          :  1;  // Bits 7:7
    UINT32 bubble_inj_read_switch_num_cas          :  8;  // Bits 15:8
    UINT32 bubble_inj_write_switch_num_cas         :  8;  // Bits 23:16
    UINT32 bubble_inj_any_cas_switch_num_cas       :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_XARB_CFG_BUBBLE_INJ_STRUCT;

typedef union {
  struct {
    UINT32 GLB_GRACE_CNT                           :  8;  // Bits 7:0
    UINT32 GLB_DRV_GATE_DIS                        :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_MCSCHEDS_GLOBAL_DRIVER_GATE_CFG_STRUCT;

typedef union {
  struct {
    UINT32 dis_legacy_ph_blkr                      :  1;  // Bits 0:0
    UINT32 dis_legacy_pe_blkr                      :  1;  // Bits 1:1
    UINT32 low_wm_allowed_preempt_priorities       :  3;  // Bits 4:2
    UINT32 med_wm_allowed_preempt_priorities       :  3;  // Bits 7:5
    UINT32 high_wm_allowed_preempt_priorities      :  3;  // Bits 10:8
    UINT32 ph_block_pe                             :  1;  // Bits 11:11
    UINT32 blkr_effect_major_mode                  :  1;  // Bits 12:12
    UINT32 RIM_BW_optimization                     :  1;  // Bits 13:13
    UINT32 RIM_BW_prefer_VC1                       :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_BLOCKING_RULES_CFG_STRUCT;

typedef union {
  struct {
    UINT32 Refresh_Rank_Mask                       :  4;  // Bits 3:0
    UINT32                                         :  4;  // Bits 7:4
    UINT32 RefZQ_En_Start_Test_Sync                :  1;  // Bits 8:8
    UINT32                                         :  22;  // Bits 30:9
    UINT32 Panic_Refresh_Only                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_REUT_CH_MISC_REFRESH_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 ZQ_Rank_Mask                            :  4;  // Bits 3:0
    UINT32                                         :  27;  // Bits 30:4
    UINT32 Always_Do_ZQ                            :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_REUT_CH_MISC_ZQ_CTRL_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0_width                            :  2;  // Bits 1:0
    UINT32 Rank_1_width                            :  2;  // Bits 3:2
    UINT32 Rank_2_width                            :  2;  // Bits 5:4
    UINT32 Rank_3_width                            :  2;  // Bits 7:6
    UINT32 MR4_PERIOD                              :  16;  // Bits 23:8
    UINT32 DDR4_TS_readout_en                      :  1;  // Bits 24:24
    UINT32                                         :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR_MR_PARAMS_STRUCT;

typedef union {
  struct {
    UINT32 Address                                 :  8;  // Bits 7:0
    UINT32 Data                                    :  8;  // Bits 15:8
    UINT32 Rank                                    :  2;  // Bits 17:16
    UINT32 Command                                 :  2;  // Bits 19:18
    UINT32 DRAM_mask                               :  9;  // Bits 28:20
    UINT32 Assume_idle                             :  1;  // Bits 29:29
    UINT32 DDR4_MA13                               :  1;  // Bits 30:30
    UINT32 Busy                                    :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR_MR_COMMAND_STRUCT;

typedef union {
  struct {
    UINT32 Device_0                                :  8;  // Bits 7:0
    UINT32 Device_1                                :  8;  // Bits 15:8
    UINT32 Device_2                                :  8;  // Bits 23:16
    UINT32 Device_3                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR_MR_RESULT_0_STRUCT;

typedef union {
  struct {
    UINT32 Device_4                                :  8;  // Bits 7:0
    UINT32 Device_5                                :  8;  // Bits 15:8
    UINT32 Device_6                                :  8;  // Bits 23:16
    UINT32 Device_7                                :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR_MR_RESULT_1_STRUCT;

typedef union {
  struct {
    UINT32 Device_8                                :  8;  // Bits 7:0
    UINT32                                         :  24;  // Bits 31:8
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR_MR_RESULT_2_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 Rank_1                                  :  3;  // Bits 10:8
    UINT32                                         :  5;  // Bits 15:11
    UINT32 Rank_2                                  :  3;  // Bits 18:16
    UINT32                                         :  5;  // Bits 23:19
    UINT32 Rank_3                                  :  3;  // Bits 26:24
    UINT32                                         :  5;  // Bits 31:27
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_LPDDR_MR4_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Rank_0                                  :  2;  // Bits 1:0
    UINT32                                         :  6;  // Bits 7:2
    UINT32 Rank_1                                  :  2;  // Bits 9:8
    UINT32                                         :  6;  // Bits 15:10
    UINT32 Rank_2                                  :  2;  // Bits 17:16
    UINT32                                         :  6;  // Bits 23:18
    UINT32 Rank_3                                  :  2;  // Bits 25:24
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR4_MPR_RANK_TEMPERATURE_STRUCT;

typedef union {
  struct {
    UINT32 Bit_0                                   :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_1                                   :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_2                                   :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_16                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_17                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_18                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_0                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_2                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DESWIZZLE_LOW_STRUCT;

typedef union {
  struct {
    UINT32 Bit_32                                  :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_33                                  :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_34                                  :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_48                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_49                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_50                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_4                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_6                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DESWIZZLE_HIGH_STRUCT;

typedef union {
  struct {
    UINT32 OREF_RI                                 :  8;  // Bits 7:0
    UINT32 Refresh_HP_WM                           :  4;  // Bits 11:8
    UINT32 Refresh_panic_wm                        :  4;  // Bits 15:12
    UINT32 CounttREFIWhileRefEnOff                 :  1;  // Bits 16:16
    UINT32 HPRefOnMRS                              :  1;  // Bits 17:17
    UINT32 AlwaysRefOnMRS                          :  1;  // Bits 18:18
    UINT32                                         :  6;  // Bits 24:19
    UINT32 tREFIx9                                 :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_RFP_STRUCT;

typedef union {
  struct {
    UINT32 tREFI                                   :  16;  // Bits 15:0
    UINT32 tRFC                                    :  10;  // Bits 25:16
    UINT32                                         :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_RFTP_STRUCT;

typedef union {
  struct {
    UINT32 tXSDLL                                  :  12;  // Bits 11:0
    UINT32                                         :  4;  // Bits 15:12
    UINT32 tZQOPER                                 :  10;  // Bits 25:16
    UINT32 tMOD                                    :  6;  // Bits 31:26
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_SRFTP_STRUCT;

typedef union {
  struct {
    UINT32 Ref_Interval                            :  11;  // Bits 10:0
    UINT32 Ref_Stagger_En                          :  1;  // Bits 11:11
    UINT32 Ref_Stagger_Mode                        :  1;  // Bits 12:12
    UINT32 Disable_Stolen_Refresh                  :  1;  // Bits 13:13
    UINT32 En_Ref_Type_Display                     :  1;  // Bits 14:14
    UINT32                                         :  17;  // Bits 31:15
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_MC_REFRESH_STAGGER_STRUCT;

typedef union {
  struct {
    UINT32 ZQCS_period                             :  10;  // Bits 9:0
    UINT32 tZQCS                                   :  10;  // Bits 19:10
    UINT32 tZQCAL                                  :  12;  // Bits 31:20
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_ZQCAL_STRUCT;

typedef union {
  struct {
    UINT32 MR2_shaddow                             :  14;  // Bits 13:0
    UINT32 SRT_avail                               :  2;  // Bits 15:14
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_MR2_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 MR4_sh_low                              :  2;  // Bits 1:0
    UINT32                                         :  2;  // Bits 3:2
    UINT32 MR4_sh_high                             :  10;  // Bits 13:4
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_MR4_SHADDOW_STRUCT;

typedef union {
  struct {
    UINT32 Rank_occupancy                          :  8;  // Bits 7:0
    UINT32 SRX_reset                               :  1;  // Bits 8:8
    UINT32 LPDDR4_current_FSP                      :  1;  // Bits 9:9
    UINT32 LPDDR4_current_FSP_tracking             :  1;  // Bits 10:10
    UINT32 Reset_refresh_debt                      :  1;  // Bits 11:11
    UINT32                                         :  20;  // Bits 31:12
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_MC_INIT_STATE_STRUCT;

typedef union {
  struct {
    UINT32 VISAByteSel                             :  3;  // Bits 2:0
    UINT32                                         :  5;  // Bits 7:3
    UINT32 RefFSMRankSel                           :  2;  // Bits 9:8
    UINT32 Ref_counterSel                          :  3;  // Bits 12:10
    UINT32 Enable_Ref_Status_Sample                :  1;  // Bits 13:13
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_WDB_VISA_SEL_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_IDLE_ENERGY                       :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_IDLE_ENERGY                       :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_PM_DIMM_IDLE_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_PD_ENERGY                         :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 DIMM1_PD_ENERGY                         :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_PM_DIMM_PD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_ACT_ENERGY                        :  8;  // Bits 7:0
    UINT32 DIMM1_ACT_ENERGY                        :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_PM_DIMM_ACT_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_RD_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_RD_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_PM_DIMM_RD_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 DIMM0_WR_ENERGY                         :  8;  // Bits 7:0
    UINT32 DIMM1_WR_ENERGY                         :  8;  // Bits 15:8
    UINT32                                         :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_PM_DIMM_WR_ENERGY_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_ECC_INJECT_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 Dec_tCWL                                :  6;  // Bits 5:0
    UINT32 Add_tCWL                                :  6;  // Bits 11:6
    UINT32 Add_1Qclk_delay                         :  1;  // Bits 12:12
    UINT32                                         :  19;  // Bits 31:13
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_WR_DELAY_STRUCT;

typedef union {
  struct {
    UINT32 ECC                                     :  8;  // Bits 7:0
    UINT32 RRD_DFT_Mode                            :  2;  // Bits 9:8
    UINT32 LFSR_Seed_Index                         :  5;  // Bits 14:10
    UINT32 Inversion_Mode                          :  1;  // Bits 15:15
    UINT32 AddressBased                            :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_READ_RETURN_DFT_STRUCT;

typedef union {
  struct {
    UINT32 Bit_0                                   :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_1                                   :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_2                                   :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_16                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_17                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_18                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_0                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_2                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DESWIZZLE_LOW_ERM_STRUCT;

typedef union {
  struct {
    UINT32 Bit_32                                  :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Bit_33                                  :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Bit_34                                  :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Bit_48                                  :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Bit_49                                  :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Bit_50                                  :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte_4                                  :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Byte_6                                  :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DESWIZZLE_HIGH_ERM_STRUCT;

typedef union {
  struct {
    UINT32 PBR_Disable                             :  1;  // Bits 0:0
    UINT32 PBR_OOO_Dis                             :  1;  // Bits 1:1
    UINT32 PBR_Issue_NOP                           :  1;  // Bits 2:2
    UINT32 PBR_Disable_on_hot                      :  1;  // Bits 3:3
    UINT32 PBR_Exit_on_Idle_Cnt                    :  6;  // Bits 9:4
    UINT32 tRFCpb                                  :  10;  // Bits 19:10
    UINT32 Refresh_ABR_release                     :  4;  // Bits 23:20
    UINT32 PBR_extended_disable_while_DQS_OSC      :  1;  // Bits 24:24
    UINT32 SPARE                                   :  7;  // Bits 31:25
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_SC_PBR_STRUCT;

typedef union {
  struct {
    UINT32 CPGC2MC_RD_CREDITS                      :  8;  // Bits 7:0
    UINT32 CPGC2MC_WR_CREDITS                      :  8;  // Bits 15:8
    UINT32 MC2CPGC_RD_CREDITS                      :  8;  // Bits 23:16
    UINT32 CPGC_ACTIVE                             :  1;  // Bits 24:24
    UINT32 CPGC_sync_cpl                           :  1;  // Bits 25:25
    UINT32 CPGC_sync_phase                         :  1;  // Bits 26:26
    UINT32 CPGC_Dis_Allow_CPL_interleave           :  1;  // Bits 27:27
    UINT32 CPGC_ECC_BYTE                           :  3;  // Bits 30:28
    UINT32 Stall_CPGC_CMI_Req                      :  1;  // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_MC_CPGC_CMI_STRUCT;

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
    UINT32 DDR4_alert                              :  1;  // Bits 20:20
    UINT32                                         :  11;  // Bits 31:21
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_MC_CPGC_MISC_DFT_STRUCT;

typedef union {
  struct {
    UINT32 tOSCO                                   :  7;  // Bits 6:0
    UINT32                                         :  25;  // Bits 31:7
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_LPDDR4_MISC_STRUCT;

typedef union {
  struct {
    UINT32 Count                                   :  32;  // Bits 31:0
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_PM_ALL_RANKS_CKE_LOW_COUNT_STRUCT;

typedef union {
  struct {
    UINT32 tXSR                                    :  10;  // Bits 9:0
    UINT32 count_block_wr_on_srx                   :  7;  // Bits 16:10
    UINT32 serial_zq_between_sub_ch                :  1;  // Bits 17:17
    UINT32                                         :  14;  // Bits 31:18
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_TC_SREXITTP_STRUCT;

typedef union {
  struct {
    UINT32 DQSOSCL_PERIOD                          :  16;  // Bits 15:0
    UINT32 MR19toBlockAckPeriod                    :  8;  // Bits 23:16
    UINT32 DIS_SRX_DQSOSCL                         :  1;  // Bits 24:24
    UINT32                                         :  1;  // Bits 25:25
    UINT32 disable_wr_on_pkgc_exit                 :  1;  // Bits 26:26
    UINT32 disable_wr_on_SR_exit                   :  1;  // Bits 27:27
    UINT32 disable_PMreqWaitForMR19                :  1;  // Bits 28:28
    UINT32                                         :  3;  // Bits 31:29
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT;

typedef union {
  struct {
    UINT32 Enable_WDB_Capture                      :  1;  // Bits 0:0
    UINT32                                         :  7;  // Bits 7:1
    UINT32 WDB_Starting_Capture_Pointer            :  6;  // Bits 13:8
    UINT32                                         :  2;  // Bits 15:14
    UINT32 WDB_Ending_Capture_Pointer              :  6;  // Bits 21:16
    UINT32 WDB_Capture_Block_SubCh                 :  2;  // Bits 23:22
    UINT32                                         :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_REUT_CH_WDB_CAPTURE_CTL_STRUCT;

typedef union {
  struct {
    UINT32 WDB_SC0_Current_Capture_Pointer         :  6;  // Bits 5:0
    UINT32                                         :  2;  // Bits 7:6
    UINT32 WDB_SC1_Current_Capture_Pointer         :  6;  // Bits 13:8
    UINT32                                         :  18;  // Bits 31:14
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_REUT_CH_WDB_CAPTURE_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 DATALow                                 :  32;  // Bits 31:0
    UINT32 DATAHigh                                :  32;  // Bits 63:32
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_WDB_RD_WR_DFX_DATA_STRUCT;

typedef union {
  struct {
    UINT32 GO                                      :  1;  // Bits 0:0
    UINT32 Chunk_Sel                               :  8;  // Bits 8:1
    UINT32 Op                                      :  1;  // Bits 9:9
    UINT32 SubCh                                   :  1;  // Bits 10:10
    UINT32 WID                                     :  6;  // Bits 16:11
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_WDB_RD_WR_DFX_CTL_STRUCT;

typedef union {
  struct {
    UINT32 DQS_INTERVAL_FSM_status                 :  4;  // Bits 3:0
    UINT32 TEMP_RD_FSM_status                      :  5;  // Bits 8:4
    UINT32 REFRATE_CHNG_FSM_status                 :  2;  // Bits 10:9
    UINT32 ZQCS_FSM_status                         :  3;  // Bits 13:11
    UINT32 EXE_REF_FSM_status                      :  3;  // Bits 16:14
    UINT32 MAIN_REF_FSM_status                     :  3;  // Bits 19:17
    UINT32 MAIN_SR_FSM_status                      :  4;  // Bits 23:20
    UINT32 counter_status                          :  8;  // Bits 31:24
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_REF_FSM_STATUS_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_MR1_RTT_NOM_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_MR2_RTT_WR_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_MR6_VREF_DIMM1_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_MR6_VREF_DIMM1_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR4_MR1_ODIC_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_MR5_RTT_PARK_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_MR5_RTT_PARK_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_MR1_RTT_NOM_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_LPDDR4_DISCRETE_MR_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_LPDDR4_DISCRETE_MR_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_LPDDR4_DISCRETE_MR_VALUES_2_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_LPDDR4_DISCRETE_MR_VALUES_3_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_LPDDR4_DISCRETE_MR_VALUES_4_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_LPDDR4_DISCRETE_MR_VALUES_5_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_LPDDR4_DISCRETE_MR_VALUES_6_STRUCT;

typedef union {
  struct {
    UINT32 PDDS                                    :  3;  // Bits 2:0
    UINT32 DQ_ODT                                  :  3;  // Bits 5:3
    UINT32 CA_ODT                                  :  3;  // Bits 8:6
    UINT32 CA_VREF                                 :  7;  // Bits 15:9
    UINT32 DQ_VREF                                 :  7;  // Bits 22:16
    UINT32 CODT                                    :  6;  // Bits 28:23
    UINT32 CA_VREF_HighLow                         :  3;  // Bits 31:29
    UINT32 CA_VREF_HighHigh                        :  4;  // Bits 35:32
    UINT32 DQ_VREF_High                            :  7;  // Bits 42:36
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_LPDDR4_DISCRETE_MR_VALUES_7_STRUCT;

typedef union {
  struct {
    UINT32 MR0                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR1                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR4_MR0_MR1_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR2                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR3                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR4_MR2_MR3_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR4                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR5                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR4_MR4_MR5_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 MR6                                     :  14;  // Bits 13:0
    UINT32                                         :  2;  // Bits 15:14
    UINT32 MR7                                     :  14;  // Bits 29:16
    UINT32                                         :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR4_MR6_MR7_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  3;  // Bits 2:0
    UINT32                                         :  1;  // Bits 3:3
    UINT32 Rank0_Byte1                             :  3;  // Bits 6:4
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Rank0_Byte2                             :  3;  // Bits 10:8
    UINT32                                         :  1;  // Bits 11:11
    UINT32 Rank0_Byte3                             :  3;  // Bits 14:12
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Rank0_Byte4                             :  3;  // Bits 18:16
    UINT32                                         :  1;  // Bits 19:19
    UINT32 Rank0_Byte5                             :  3;  // Bits 22:20
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Rank0_Byte6                             :  3;  // Bits 26:24
    UINT32                                         :  1;  // Bits 27:27
    UINT32 Rank0_Byte7                             :  3;  // Bits 30:28
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Rank1_Byte0                             :  3;  // Bits 34:32
    UINT32                                         :  1;  // Bits 35:35
    UINT32 Rank1_Byte1                             :  3;  // Bits 38:36
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Rank1_Byte2                             :  3;  // Bits 42:40
    UINT32                                         :  1;  // Bits 43:43
    UINT32 Rank1_Byte3                             :  3;  // Bits 46:44
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Rank1_Byte4                             :  3;  // Bits 50:48
    UINT32                                         :  1;  // Bits 51:51
    UINT32 Rank1_Byte5                             :  3;  // Bits 54:52
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Rank1_Byte6                             :  3;  // Bits 58:56
    UINT32                                         :  1;  // Bits 59:59
    UINT32 Rank1_Byte7                             :  3;  // Bits 62:60
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_MR2_RTT_WR_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_MR6_VREF_VALUES_0_STRUCT;

typedef union {
  struct {
    UINT32 Byte0                                   :  7;  // Bits 6:0
    UINT32                                         :  1;  // Bits 7:7
    UINT32 Byte1                                   :  7;  // Bits 14:8
    UINT32                                         :  1;  // Bits 15:15
    UINT32 Byte2                                   :  7;  // Bits 22:16
    UINT32                                         :  1;  // Bits 23:23
    UINT32 Byte3                                   :  7;  // Bits 30:24
    UINT32                                         :  1;  // Bits 31:31
    UINT32 Byte4                                   :  7;  // Bits 38:32
    UINT32                                         :  1;  // Bits 39:39
    UINT32 Byte5                                   :  7;  // Bits 46:40
    UINT32                                         :  1;  // Bits 47:47
    UINT32 Byte6                                   :  7;  // Bits 54:48
    UINT32                                         :  1;  // Bits 55:55
    UINT32 Byte7                                   :  7;  // Bits 62:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_MR6_VREF_VALUES_1_STRUCT;

typedef union {
  struct {
    UINT32 MR1                                     :  8;  // Bits 7:0
    UINT32 MR2                                     :  8;  // Bits 15:8
    UINT32 MR3                                     :  8;  // Bits 23:16
    UINT32 MR11                                    :  8;  // Bits 31:24
    UINT32 MR12                                    :  8;  // Bits 39:32
    UINT32 MR13                                    :  8;  // Bits 47:40
    UINT32 MR22                                    :  8;  // Bits 55:48
    UINT32 MR23                                    :  8;  // Bits 63:56
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_LPDDR_MR_CONTENT_STRUCT;

typedef union {
  struct {
    UINT32 DDR4_Restore_MR                         :  8;  // Bits 7:0
    UINT32 DDR4_Restore_MR1_ODIC_Per_Device        :  1;  // Bits 8:8
    UINT32 DDR4_Restore_MR2_Per_Device             :  1;  // Bits 9:9
    UINT32 DDR4_Restore_MR6_Per_Device             :  1;  // Bits 10:10
    UINT32 DDR4_PDA_VREF_Initial                   :  1;  // Bits 11:11
    UINT32 DDR4_Short_VREF_Exit                    :  1;  // Bits 12:12
    UINT32 LPDDR_Restore_MR                        :  9;  // Bits 21:13
    UINT32 do_ZQCL                                 :  1;  // Bits 22:22
    UINT32 zero_rank1_MR11                         :  1;  // Bits 23:23
    UINT32 reset_flow                              :  1;  // Bits 24:24
    UINT32 vref_time_per_byte                      :  1;  // Bits 25:25
    UINT32 do_pda_for_1R1R                         :  1;  // Bits 26:26
    UINT32 add_initial_vref                        :  1;  // Bits 27:27
    UINT32 LPDDR4_switch_FSP                       :  1;  // Bits 28:28
    UINT32 do_dq_osc_start                         :  1;  // Bits 29:29
    UINT32                                         :  2;  // Bits 31:30
    UINT32 tVREFDQ                                 :  10;  // Bits 41:32
    UINT32 cbit_count_each_rank                    :  1;  // Bits 42:42
    UINT32 do_PDA_for_ECC                          :  1;  // Bits 43:43
    UINT32 DDR4_Restore_MR5_Per_Device             :  1;  // Bits 44:44
    UINT32 TwoDPC_support                          :  1;  // Bits 45:45
    UINT32 DDR4_Restore_MR1_RTTNOM_Per_Device      :  1;  // Bits 46:46
    UINT32 Fast_PDA                                :  1;  // Bits 47:47
    UINT32 always_count_tFC                        :  1;  // Bits 48:48
    UINT32 PDA_wr_delay                            :  6;  // Bits 54:49
    UINT32 LPDDR4_per_byte_vref                    :  1;  // Bits 55:55
    UINT32 Clear_VRCG                              :  1;  // Bits 56:56
    UINT32 GV_auto_enable                          :  1;  // Bits 57:57
    UINT32 LPDDR4_split_transition                 :  1;  // Bits 58:58
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_MRS_FSM_CONTROL_STRUCT;

typedef union {
  struct {
    UINT32 Run                                     :  1;  // Bits 0:0
    UINT32                                         :  31;  // Bits 31:1
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_MRS_FSM_RUN_STRUCT;

typedef union {
  struct {
    UINT32 Rank0_Byte0                             :  2;  // Bits 1:0
    UINT32 Rank0_Byte1                             :  2;  // Bits 3:2
    UINT32 Rank0_Byte2                             :  2;  // Bits 5:4
    UINT32 Rank0_Byte3                             :  2;  // Bits 7:6
    UINT32 Rank0_Byte4                             :  2;  // Bits 9:8
    UINT32 Rank0_Byte5                             :  2;  // Bits 11:10
    UINT32 Rank0_Byte6                             :  2;  // Bits 13:12
    UINT32 Rank0_Byte7                             :  2;  // Bits 15:14
    UINT32 Rank1_Byte0                             :  2;  // Bits 17:16
    UINT32 Rank1_Byte1                             :  2;  // Bits 19:18
    UINT32 Rank1_Byte2                             :  2;  // Bits 21:20
    UINT32 Rank1_Byte3                             :  2;  // Bits 23:22
    UINT32 Rank1_Byte4                             :  2;  // Bits 25:24
    UINT32 Rank1_Byte5                             :  2;  // Bits 27:26
    UINT32 Rank1_Byte6                             :  2;  // Bits 29:28
    UINT32 Rank1_Byte7                             :  2;  // Bits 31:30
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_DDR4_MR1_ODIC_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 data_trace_mode                         :  2;  // Bits 1:0
    UINT32 UI_to_trace                             :  3;  // Bits 4:2
    UINT32 byte_to_trace                           :  3;  // Bits 7:5
    UINT32 ECC_EN                                  :  1;  // Bits 8:8
    UINT32 ECC_BYTE_replace                        :  3;  // Bits 11:9
    UINT32 trace_read_data                         :  1;  // Bits 12:12
    UINT32 trace_write_data                        :  1;  // Bits 13:13
    UINT32 DDRPL_Activate                          :  1;  // Bits 14:14
    UINT32 SCHTrace                                :  1;  // Bits 15:15
    UINT32 dis_early_ind_override                  :  1;  // Bits 16:16
    UINT32                                         :  15;  // Bits 31:17
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_PL_AGENT_CFG_DTF_STRUCT;

typedef union {
  struct {
    UINT32 GLB_GRACE_CNT                           :  8;  // Bits 7:0
    UINT32 GLB_DRV_GATE_DIS                        :  1;  // Bits 8:8
    UINT32                                         :  23;  // Bits 31:9
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_MCMNTS_GLOBAL_DRIVER_GATE_CFG_STRUCT;

typedef union {
  struct {
    UINT32 ODIC_Rank0                              :  2;  // Bits 1:0
    UINT32 ODIC_Rank1                              :  2;  // Bits 3:2
    UINT32 RTT_WR_Rank0                            :  3;  // Bits 6:4
    UINT32 RTT_WR_Rank1                            :  3;  // Bits 9:7
    UINT32 VREF_Rank0                              :  7;  // Bits 16:10
    UINT32 VREF_Rank1                              :  7;  // Bits 23:17
    UINT32 RTT_NOM_Rank0                           :  3;  // Bits 26:24
    UINT32 RTT_NOM_Rank1                           :  3;  // Bits 29:27
    UINT32 RTT_PARK_Rank0Low                       :  2;  // Bits 31:30
    UINT32 RTT_PARK_Rank0High                      :  1;  // Bits 32:32
    UINT32 RTT_PARK_Rank1                          :  3;  // Bits 35:33
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_ECC_DEVICE_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 ODIC_Rank0                              :  2;  // Bits 1:0
    UINT32 ODIC_Rank1                              :  2;  // Bits 3:2
    UINT32 RTT_WR_Rank0                            :  3;  // Bits 6:4
    UINT32 RTT_WR_Rank1                            :  3;  // Bits 9:7
    UINT32 VREF_Rank0                              :  7;  // Bits 16:10
    UINT32 VREF_Rank1                              :  7;  // Bits 23:17
    UINT32 RTT_NOM_Rank0                           :  3;  // Bits 26:24
    UINT32 RTT_NOM_Rank1                           :  3;  // Bits 29:27
    UINT32 RTT_PARK_Rank0Low                       :  2;  // Bits 31:30
    UINT32 RTT_PARK_Rank0High                      :  1;  // Bits 32:32
    UINT32 RTT_PARK_Rank1                          :  3;  // Bits 35:33
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} BC_CR_DDR4_ECC_DEVICE_DIMM1_VALUES_STRUCT;

typedef union {
  struct {
    UINT32 Spare_RW                                :  8;  // Bits 7:0
    UINT32 ForceX2Ref                              :  1;  // Bits 8:8
    UINT32 ForceX4Ref                              :  1;  // Bits 9:9
    UINT32 DisLowRefRate                           :  1;  // Bits 10:10
    UINT32 disRegardZQonSRtime                     :  1;  // Bits 11:11
    UINT32 Decoder_EBH                             :  2;  // Bits 13:12
    UINT32                                         :  1;  // Bits 14:14
    UINT32 DisSREXcnt                              :  1;  // Bits 15:15
    UINT32 Spare_RW_V                              :  16;  // Bits 31:16
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} BC_CR_MCMNTS_SPARE_STRUCT;

#pragma pack(pop)
#endif

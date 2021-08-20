/** @file
  This file defines all the MRC debug hooks.

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
#ifndef _MrcDebugHook_h_
#define _MrcDebugHook_h_
//Place Holder
//#define MRC_                            (0xDD)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

#define MRC_FAILURE_INDICATION          (0x0080)  /// This value is or'ed with below "*_ERROR" codes
#define MRC_INITIALIZATION_START        (0xDD00)
#define MRC_INITIALIZATION_END          (MRC_INITIALIZATION_START + MRC_FAILURE_INDICATION - 1)

#define MRC_INTERPRETER                 (0xDD01)

#define MRC_SAFE_MODE                   (0xDD02)

#define MRC_EARLY_OVERRIDES             (0xDD03)

#define MRC_VDDQ                        (0xDD04)
#define MRC_VDDQ_ERROR                  (MRC_VDDQ | MRC_FAILURE_INDICATION)

#define MRC_CMD_EQ                      (0xDD05)
#define MRC_CMD_EQ_ERROR                (MRC_CMD_EQ | MRC_FAILURE_INDICATION)

#define MRC_CMD_DS                      (0xDD06)
#define MRC_CMD_DS_ERROR                (MRC_CMD_DS | MRC_FAILURE_INDICATION)

#define MRC_CMD_SR                      (0xDD07)
#define MRC_CMD_SR_ERROR                (MRC_CMD_SR | MRC_FAILURE_INDICATION)

#define MRC_VCCDLL_BYPASS               (0xDD08)
#define MRC_VCCDLL_BYPASS_ERROR         (MRC_VCCDLL_BYPASS | MRC_FAILURE_INDICATION)

#define MRC_DDRIO_PREINIT               (0xDD09)
#define MRC_DDRIO_PREINIT_ERROR         (MRC_DDRIO_PREINIT | MRC_FAILURE_INDICATION)

#define MRC_FLL_INIT                    (0xDD0A)
#define MRC_FLL_INIT_ERROR              (MRC_FLL_INIT | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD0B)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD0C)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD0D)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD0E)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD0F)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

#define MRC_CMD_PLOT_2D                 (0xDD10)
#define MRC_CMD_PLOT_2D_ERROR           (MRC_CMD_PLOT_2D | MRC_FAILURE_INDICATION)

#define MRC_FREQ_LOCK                   (0xDD11)
#define MRC_FREQ_LOCK_ERROR             (MRC_FREQ_LOCK | MRC_FAILURE_INDICATION)

#define MRC_DDRIO_INIT                  (0xDD12)
#define MRC_DDRIO_INIT_ERROR            (MRC_DDRIO_INIT | MRC_FAILURE_INDICATION)

#define MRC_DDRSCOMP_INIT               (0xDD13)
#define MRC_DDRSCOMP_INIT_ERROR         (MRC_DDRSCOMP_INIT | MRC_FAILURE_INDICATION)

#define MRC_DDRCOMP_CAL_PRE             (0xDD14)
#define MRC_DDRCOMP_CAL_PRE_ERROR       (MRC_DDRCOMP_CAL_PRE | MRC_FAILURE_INDICATION)

#define MRC_MEMORY_SS_INIT              (0xDD15)
#define MRC_MEMORY_SS_INIT_ERROR        (MRC_MEMORY_SS_INIT | MRC_FAILURE_INDICATION)

#define MRC_READ_VREF_DECAP             (0xDD16)
#define MRC_READ_VREF_DECAP_ERROR       (MRC_READ_VREF_DECAP | MRC_FAILURE_INDICATION)

#define MRC_PANIC_VTT_DN_LP             (0xDD17)
#define MRC_PANIC_VTT_DN_LP_ERROR       (MRC_PANIC_VTT_DN_LP | MRC_FAILURE_INDICATION)

#define MRC_TXDQTCO_COMP_TRAINING        (0xDD18)
#define MRC_TXDQTCO_COMP_TRAINING_ERROR  (MRC_TXDQTCO_COMP_TRAINING | MRC_FAILURE_INDICATION)

#define MRC_TXDQSTCO_COMP_TRAINING       (0xDD19)
#define MRC_TXDQSTCO_COMP_TRAINING_ERROR (MRC_TXDQSTCO_COMP_TRAINING | MRC_FAILURE_INDICATION)

#define MRC_DCC_INIT                    (0xDD1A)
#define MRC_DCC_INIT_ERROR              (MRC_DCC_INIT | MRC_FAILURE_INDICATION)

#define MRC_FAST_BOOT_PERMITTED         (0xDD1B)
#define MRC_FAST_BOOT_PERMITTED_ERROR   (MRC_FAST_BOOT_PERMITTED | MRC_FAILURE_INDICATION)

#define MRC_RESTORE_NON_TRAINING        (0xDD1C)
#define MRC_RESTORE_NON_TRAINING_ERROR  (MRC_RESTORE_NON_TRAINING | MRC_FAILURE_INDICATION)

#define MRC_PRINT_INPUT_PARAMS          (0xDD1D)
#define MRC_PRINT_INPUT_PARAMS_ERROR    (MRC_PRINT_INPUT_PARAMS | MRC_FAILURE_INDICATION)

#define MRC_SET_OVERRIDES_PSPD          (0xDD1E)
#define MRC_SET_OVERRIDES_PSPD_ERROR    (MRC_SET_OVERRIDES_PSPD | MRC_FAILURE_INDICATION)

#define MRC_OFFSET_CORRECTION_PRE       (0xDD1F)
#define MRC_OFFSET_CORRECTION_PRE_ERROR (MRC_OFFSET_CORRECTION_PRE | MRC_FAILURE_INDICATION)

#define MRC_SPD_PROCESSING              (0xDD20)
#define MRC_SPD_PROCESSING_ERROR        (MRC_SPD_PROCESSING | MRC_FAILURE_INDICATION)

#define MRC_SET_OVERRIDES               (0xDD21)
#define MRC_SET_OVERRIDES_ERROR         (MRC_SET_OVERRIDES | MRC_FAILURE_INDICATION)

#define MRC_MC_CAPABILITY               (0xDD22)
#define MRC_MC_CAPABILITY_ERROR         (MRC_MC_CAPABILITY | MRC_FAILURE_INDICATION)

#define MRC_MC_CONFIG                   (0xDD23)
#define MRC_MC_CONFIG_ERROR             (MRC_MC_CONFIG | MRC_FAILURE_INDICATION)

#define MRC_MC_MEMORY_MAP               (0xDD24)
#define MRC_MC_MEMORY_MAP_ERROR         (MRC_MC_MEMORY_MAP | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD25)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

#define MRC_RESET_SEQUENCE              (0xDD26)
#define MRC_RESET_ERROR                 (MRC_RESET_SEQUENCE | MRC_FAILURE_INDICATION)

#define MRC_PRE_TRAINING                (0xDD27)
#define MRC_PRE_TRAINING_ERROR          (MRC_PRE_TRAINING | MRC_FAILURE_INDICATION)

///
/// TRAINING STEPS START
///
#define MRC_EARLY_COMMAND               (0xDD28)
#define MRC_EARLY_COMMAND_ERROR         (MRC_EARLY_COMMAND | MRC_FAILURE_INDICATION)

#define MRC_SENSE_AMP_OFFSET            (0xDD29)
#define MRC_SENSE_AMP_OFFSET_ERROR      (MRC_SENSE_AMP_OFFSET | MRC_FAILURE_INDICATION)

#define MRC_READ_MPR                    (0xDD2A)
#define MRC_READ_MPR_ERROR              (MRC_READ_MPR | MRC_FAILURE_INDICATION)

#define MRC_RECEIVE_ENABLE              (0xDD2B)
#define MRC_RECEIVE_ENABLE_ERROR        (MRC_RECEIVE_ENABLE | MRC_FAILURE_INDICATION)

#define MRC_JEDEC_WRITE_LEVELING        (0xDD2C)
#define MRC_JEDEC_WRITE_LEVELING_ERROR  (MRC_JEDEC_WRITE_LEVELING | MRC_FAILURE_INDICATION)

#define MRC_LPDDR_LATENCY_SET_B         (0xDD2D)
#define MRC_LPDDR_LATENCY_SET_B_ERROR   (MRC_LPDDR_LATENCY_SET_B | MRC_FAILURE_INDICATION)

#define MRC_WRITE_TIMING_1D             (0xDD2E)
#define MRC_WRITE_TIMING_1D_ERROR       (MRC_WRITE_TIMING_1D | MRC_FAILURE_INDICATION)

#define MRC_READ_TIMING_1D              (0xDD2F)
#define MRC_READ_TIMING_1D_ERROR        (MRC_READ_TIMING_1D | MRC_FAILURE_INDICATION)

#define MRC_DIMM_ODT                    (0xDD30)
#define MRC_DIMM_ODT_ERROR              (MRC_DIMM_ODT | MRC_FAILURE_INDICATION)

#define MRC_EARLY_WRITE_TIMING_2D       (0xDD31)
#define MRC_EARLY_WRITE_TIMING_ERROR    (MRC_EARLY_WRITE_TIMING_2D | MRC_FAILURE_INDICATION)

#define MRC_WRITE_DS                    (0xDD32)
#define MRC_WRITE_DS_ERROR              (MRC_WRITE_DS | MRC_FAILURE_INDICATION)

#define MRC_WRITE_EQ                    (0xDD33)
#define MRC_WRITE_EQ_ERROR              (MRC_WRITE_EQ | MRC_FAILURE_INDICATION)

#define MRC_EARLY_READ_TIMING_2D        (0xDD34)
#define MRC_EARLY_READ_TIMING_ERROR     (MRC_EARLY_READ_TIMING_2D | MRC_FAILURE_INDICATION)

#define MRC_READ_ODT                    (0xDD35)
#define MRC_READ_ODT_ERROR              (MRC_READ_ODT | MRC_FAILURE_INDICATION)

#define MRC_READ_EQ                     (0xDD36)
#define MRC_READ_EQ_ERROR               (MRC_READ_EQ | MRC_FAILURE_INDICATION)

#define MRC_READ_AMP_POWER              (0xDD37)
#define MRC_READ_AMP_POWER_ERROR        (MRC_READ_AMP_POWER | MRC_FAILURE_INDICATION)

#define MRC_WRITE_TIMING_2D             (0xDD38)
#define MRC_WRITE_TIMING_2D_ERROR       (MRC_WRITE_TIMING_2D | MRC_FAILURE_INDICATION)

#define MRC_READ_TIMING_2D              (0xDD39)
#define MRC_READ_TIMING_2D_ERROR        (MRC_READ_TIMING_2D | MRC_FAILURE_INDICATION)

#define MRC_CMD_VREF                    (0xDD3A)
#define MRC_CMD_VREF_ERROR              (MRC_CMD_VREF | MRC_FAILURE_INDICATION)

#define MRC_WRITE_VREF_2D               (0xDD3B)
#define MRC_WRITE_VREF_2D_ERROR         (MRC_WRITE_VREF_2D | MRC_FAILURE_INDICATION)

#define MRC_READ_VREF_2D                (0xDD3C)
#define MRC_READ_VREF_2D_ERROR          (MRC_READ_VREF_2D | MRC_FAILURE_INDICATION)

#define MRC_POST_TRAINING               (0xDD3D)
#define MRC_POST_TRAINING_ERROR         (MRC_POST_TRAINING | MRC_FAILURE_INDICATION)

#define MRC_LATE_COMMAND                (0xDD3E)
#define MRC_LATE_COMMAND_ERROR          (MRC_LATE_COMMAND | MRC_FAILURE_INDICATION)

#define MRC_ROUND_TRIP_LAT              (0xDD3F)
#define MRC_ROUND_TRIP_LAT_ERROR        (MRC_ROUND_TRIP_LAT | MRC_FAILURE_INDICATION)

#define MRC_TURN_AROUND                 (0xDD40)
#define MRC_TURN_AROUND_ERROR           (MRC_TURN_AROUND | MRC_FAILURE_INDICATION)

#define MRC_CMP_OPT                     (0xDD41)
#define MRC_CMP_OPT_ERROR               (MRC_CMP_OPT | MRC_FAILURE_INDICATION)

#define MRC_SAVE_MC_VALUES              (0xDD42)
#define MRC_SAVE_MC_VALUES_ERROR        (MRC_SAVE_MC_VALUES | MRC_FAILURE_INDICATION)

#define MRC_RESTORE_TRAINING            (0xDD43)
#define MRC_RESTORE_TRAINING_ERROR      (MRC_RESTORE_TRAINING | MRC_FAILURE_INDICATION)

#define MRC_RMT_TOOL                    (0xDD44)
#define MRC_RMT_TOOL_ERROR              (MRC_RMT_TOOL | MRC_FAILURE_INDICATION)

#define MRC_WRITE_SR                    (0xDD45)
#define MRC_WRITE_SR_ERROR              (MRC_WRITE_SR | MRC_FAILURE_INDICATION)

#define MRC_DIMM_RON                    (0xDD46)
#define MRC_DIMM_RON_ERROR              (MRC_DIMM_RON | MRC_FAILURE_INDICATION)

#define MRC_RCVEN_TIMING_1D             (0xDD47)
#define MRC_RCVEN_TIMING_1D_ERROR       (MRC_RCVEN_TIMING_1D | MRC_FAILURE_INDICATION)

#define MRC_MR_FILL                     (0xDD48)
#define MRC_MR_FILL_ERROR               (MRC_MR_FILL | MRC_FAILURE_INDICATION)

#define MRC_PWR_MTR                     (0xDD49)
#define MRC_PWR_MTR_ERROR               (MRC_PWR_MTR | MRC_FAILURE_INDICATION)

#define MRC_DDR4_MAPPING                (0xDD4A)
#define MRC_DDR4_MAPPING_ERROR          (MRC_DDR4_MAPPING | MRC_FAILURE_INDICATION)

#define MRC_WRITE_VOLTAGE_1D            (0xDD4B)
#define MRC_WRITE_VOLTAGE_1D_ERROR      (MRC_WRITE_VOLTAGE_1D | MRC_FAILURE_INDICATION)

#define MRC_EARLY_RDMPR_TIMING_2D       (0xDD4C)
#define MRC_EARLY_RDMPR_TIMING_2D_ERROR (MRC_EARLY_RDMPR_TIMING_2D | MRC_FAILURE_INDICATION)

#define MRC_FORCE_OLTM                  (0xDD4D)
#define MRC_FORCE_OLTM_ERROR            (MRC_FORCE_OLTM | MRC_FAILURE_INDICATION)

#define MRC_WRITE_LEVELING_FLYBY        (0xDD4E)
#define MRC_WRITE_LEVELING_ERROR        (MRC_WRITE_LEVELING_FLYBY | MRC_FAILURE_INDICATION)

#define MRC_COMP_OVERRIDE               (0xDD4F)
#define MRC_COMP_OVERRIDE_ERROR         (MRC_COMP_OVERRIDE | MRC_FAILURE_INDICATION)

#define MRC_MC_ACTIVATE                 (0xDD50)
#define MRC_MC_ACTIVATE_ERROR           (MRC_MC_ACTIVATE | MRC_FAILURE_INDICATION)

#define MRC_RH_PREVENTION               (0xDD51)
#define MRC_RH_PREVENTION_ERROR         (MRC_RH_PREVENTION | MRC_FAILURE_INDICATION)

#define MRC_GET_MRC_DATA                (0xDD52)
#define MRC_GET_MRC_DATA_ERROR          (MRC_GET_MRC_DATA | MRC_FAILURE_INDICATION)

#define MRC_WRITE_DQ_DQS_RETRAINING     (0xDD53)
#define MRC_WRITE_DQ_DQS_ERROR          (MRC_WRITE_DQ_DQS_RETRAINING | MRC_FAILURE_INDICATION)


///
/// To have distinct post codes for debuggin purposes, do not define a training step
/// value to have the same lower byte value as MRC_MEM_INIT_DONE.  This value is
/// specific to signal the completion of the module.  This holds higher signifiance
/// on systems that do not use the high byte.
///
/// #define MRC_DO_NOT_USE                (0x__55)
///
#define MRC_MEM_INIT_DONE               (0x0055)
#define MRC_MEM_INIT_DONE_WITH_ERRORS   (MRC_MEM_INIT_DONE | MRC_FAILURE_INDICATION)

#define MRC_TXTCO_COMP_TRAINING         (0xDD56)
#define MRC_TXTCO_COMP_TRAINING_ERROR   (MRC_TXTCO_COMP_TRAINING | MRC_FAILURE_INDICATION)

#define MRC_READ_VOLTAGE_1D             (0xDD57)
#define MRC_READ_VOLTAGE_1D_ERROR       (MRC_READ_VOLTAGE_1D | MRC_FAILURE_INDICATION)

#define MRC_RETRAIN_CHECK               (0xDD58)
#define MRC_RETRAIN_CHECK_ERROR         (MRC_RETRAIN_CHECK | MRC_FAILURE_INDICATION)

#define MRC_RMT_TOOL_BIT                (0xDD59)
#define MRC_RMT_TOOL_BIT_ERROR          (MRC_RMT_TOOL_BIT | MRC_FAILURE_INDICATION)

#define MRC_SA_GV_SWITCH                (0xDD5A)
#define MRC_SA_GV_SWITCH_ERROR          (MRC_SA_GV_SWITCH | MRC_FAILURE_INDICATION)

#define MRC_ALIAS_CHECK                 (0xDD5B)
#define MRC_ALIAS_CHECK_ERROR           (MRC_ALIAS_CHECK | MRC_FAILURE_INDICATION)

#define MRC_ECC_CLEAN_START             (0xDD5C)
#define MRC_ECC_CLEAN_ERROR             (MRC_ECC_CLEAN_START | MRC_FAILURE_INDICATION)

#define MRC_DONE                        (0xDD5D)
#define MRC_DONE_WITH_ERROR             (MRC_DONE | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD5E)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

#define MRC_CPGC_MEMORY_TEST            (0xDD5F)
#define MRC_CPGC_MEMORY_TEST_ERROR      (MRC_CPGC_MEMORY_TEST | MRC_FAILURE_INDICATION)

#define MRC_TXT_ALIAS_CHECK             (0xDD60)
#define MRC_TXT_ALIAS_CHECK_ERROR       (MRC_TXT_ALIAS_CHECK | MRC_FAILURE_INDICATION)

#define MRC_ENG_PERF_GAIN               (0xDD61)
#define MRC_ENG_PERF_GAIN_ERROR         (MRC_ENG_PERF_GAIN | MRC_FAILURE_INDICATION)

#define MRC_CLKTCO_COMP_TRAINING        (0xDD62)
#define MRC_CLKTCO_COMP_TRAINING_ERROR  (MRC_CLKTCO_COMP_TRAINING | MRC_FAILURE_INDICATION)

#define MRC_PBD_DESKEW_CAL              (0xDD63)
#define MRC_PBD_DESKEW_CAL_ERROR        (MRC_PBD_DESKEW_CAL | MRC_FAILURE_INDICATION)

#define MRC_DCC_FINAL                   (0xDD64)
#define MRC_DCC_FINAL_ERROR             (MRC_DCC_FINAL | MRC_FAILURE_INDICATION)

#define MRC_DIMM_ODT_CA                 (0xDD67)
#define MRC_DIMM_ODT_CA_ERROR           (MRC_DIMM_ODT_CA | MRC_FAILURE_INDICATION)

#define MRC_MEMORY_TEST                 (0xDD68)
#define MRC_MEMORY_TEST_ERROR           (MRC_MEMORY_TEST | MRC_FAILURE_INDICATION)

#define MRC_FILL_RMT_STRUCTURE          (0xDD69)
#define MRC_FILL_RMT_STRUCTURE_ERROR    (MRC_FILL_RMT_STRUCTURE | MRC_FAILURE_INDICATION)

#define MRC_WCK_LEVELING                (0xDD6A)
#define MRC_WCK_LEVELING_ERROR          (MRC_WCK_LEVELING | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD6B)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD6C)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD6D)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD6E)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD6F)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

#define MRC_SELF_REFRESH_EXIT           (0xDD70)
#define MRC_SELF_REFRESH_EXIT_ERROR     (MRC_SELF_REFRESH_EXIT | MRC_FAILURE_INDICATION)

#define MRC_NORMAL_MODE                 (0xDD71)
#define MRC_MRC_NORMAL_MODE_ERROR       (MRC_NORMAL_MODE | MRC_FAILURE_INDICATION)

#define MRC_THERMAL_CONFIG              (0xDD72)
#define MRC_THERMAL_CONFIG_ERROR        (MRC_THERMAL_CONFIG | MRC_FAILURE_INDICATION)

#define MRC_VCCDLL_FFOFFSETCORRECTION   (0xDD73)
#define MRC_VCCDLL_FFOFFSETCORRECTION_ERROR  (MRC_VCCDLL_FFOFFSETCORRECTION | MRC_FAILURE_INDICATION)

#define MRC_VCCDLL_FFTIMING             (0xDD74)
#define MRC_VCCDLL_FFTIMING_ERROR       (MRC_VCCDLL_FFTIMING | MRC_FAILURE_INDICATION)

#define MRC_VCCDLL_KBNCORRECTION         (0xDD75)
#define MRC_VCCDLL_KBNCORRECTION_ERROR   (MRC_VCCDLL_KBNCORRECTION | MRC_FAILURE_INDICATION)

#define MRC_VSXHI_FFTUNING               (0xDD76)
#define MRC_VSXHI_FFTUNING_ERROR         (MRC_VSXHI_FFTUNING | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD77)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD78)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD79)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD7A)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD7B)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD7C)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD7D)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)

#define MRC_NO_MEMORY_DETECTED          (0xDD7E | MRC_FAILURE_INDICATION)

//Place Holder
//#define MRC_                            (0xDD7F)
//#define MRC__ERROR                      (MRC_ | MRC_FAILURE_INDICATION)
#endif

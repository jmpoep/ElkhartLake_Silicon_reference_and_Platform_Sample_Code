/** @file
  Register names for CPU registers

  <b>Conventions</b>
  - Definitions beginning with "MSR_" are MSRs
  - Definitions beginning with "R_" are registers
  - Definitions beginning with "B_" are bits within registers
  - Definitions beginning with "V_" are meaningful values of bits within the registers
  - Definitions beginning with "S_" are register sizes
  - Definitions beginning with "N_" are the bit position

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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
#ifndef _CPU_REGS_H_
#define _CPU_REGS_H_
#pragma pack (push, 1)

#ifndef TRIGGER_MODE_EDGE
#define TRIGGER_MODE_EDGE             0x00
#endif
#ifndef TRIGGER_MODE_LEVEL
#define TRIGGER_MODE_LEVEL            0x01
#endif

#define CACHE_UNCACHEABLE               0
#define CACHE_WRITECOMBINING            1
#define CACHE_WRITETHROUGH              4
#define CACHE_WRITEPROTECTED            5
#define CACHE_WRITEBACK                 6

//
// MSR defines
//
#define PIC_THREAD_CONTROL                                            0x0000002E
#define B_PIC_THREAD_CONTROL_TPR_DIS                                  MRC_BIT10
#define MSR_CORE_THREAD_COUNT                                         0x00000035
#define N_MSR_CORE_THREAD_COUNT_CORECOUNT_OFFSET                                           16
#define B_THREAD_COUNT_MASK                                           0xFFFF
#define MSR_SOCKET_ID_MSR                                             0x00000039
#define MSR_IA32_SMM_SAVE_CONTROL                                     0x0000003E
#define B_MSR_IA32_SMM_SAVE_CONTROL_SFPPE                             MRC_BIT0
#define MSR_IA32_BIOS_ENBL_XU                                         0x0000007A
#define MSR_IA32_MTRRCAP                                              0x000000FE
#define MSR_PRMRR_BASE_0                                              0x000002A0
#define MSR_PRMRR_MASK                                                0x000001F5
#define B_MSR_PRMRR_BASE_0_CONFIGURED_MASK                            MRC_BIT3
#define B_MSR_PRMRR_MASK_L_MASK                                       MRC_BIT10
#define MSR_PRMRR_VALID_CONFIG                                        0x000001FB
#define PRMRR_MAX_SIZE                                                0x10000000
#define B_MSR_PRMRR_PHYS_MASK_LOCK                                    MRC_BIT10
#define B_MSR_PRMRR_VALID_BIT                                         MRC_BIT11
#define MSR_IA32_BIOS_MEM_DUMP_XU                                     0x0000030B

//#define MSR_PLATFORM_INFO                                             0x000000CE
#define V_MSR_PRMRR_MASK                                              0x0000007FFFFFFFFF
#define N_PLATFORM_INFO_MIN_RATIO                                     40
#define B_PLATFORM_INFO_RATIO_MASK                                    0xFF
#define N_PLATFORM_INFO_MAX_RATIO                                     8
#define B_MSR_PLATFORM_INFO_BIOSGUARD_AVAIL                           MRC_BIT35
#define N_MSR_PLATFORM_INFO_CONFIG_TDP_NUM_LEVELS_OFFSET              33
#define V_CONFIG_TDP_NUM_LEVELS_MASK                                  (MRC_BIT34 | MRC_BIT33)
#define B_PLATFORM_INFO_TDC_TDP_LIMIT                                 MRC_BIT29
#define N_PLATFORM_INFO_RATIO_LIMIT                                   28
#define B_PLATFORM_INFO_RATIO_LIMIT                                   MRC_BIT28
#define B_PLATFORM_INFO_SMM_SAVE_CONTROL                              MRC_BIT16
#define N_PLATFORM_INFO_PROG_TCC_ACTIVATION_OFFSET                    30
#define B_PLATFORM_INFO_PROG_TCC_ACTIVATION_OFFSET                    MRC_BIT30
#define B_PLATFORM_INFO_TIMED_MWAIT_SUPPORTED                         MRC_BIT37
#define B_TIMED_MWAIT_ENABLE                                          MRC_BIT31 ///< @todo Remove when bitfield definition is available.
#define V_CSTATE_LIMIT_C1                                             0x01
#define V_CSTATE_LIMIT_C3                                             0x02
#define V_CSTATE_LIMIT_C6                                             0x03
#define V_CSTATE_LIMIT_C7                                             0x04
#define V_CSTATE_LIMIT_C7S                                            0x05
#define V_CSTATE_LIMIT_C8                                             0x06
#define V_CSTATE_LIMIT_C9                                             0x07
#define V_CSTATE_LIMIT_C10                                            0x08
#define MSR_PMG_IO_CAPTURE_BASE                                       0x000000E4
#define B_MSR_PMG_CST_RANGE                                           (MRC_BIT18 | MRC_BIT17 | MRC_BIT16)
#define V_IO_CAPT_LVL2                                                (0x0 << 16)   ///< C3
#define V_IO_CAPT_LVL3                                                (0x1 << 16)   ///< C6
#define V_IO_CAPT_LVL4                                                (0x2 << 16)   ///< C7
#define V_IO_CAPT_LVL5                                                (0x3 << 16)   ///< C8
#define V_IO_CAPT_LVL6                                                (0x4 << 16)   ///< C9
#define V_IO_CAPT_LVL7                                                (0x5 << 16)   ///< C10
#define V_IO_CAPT_LVL2_BASE_ADDR_MASK                                 0xFFFF
#define MSR_PLAT_FRMW_PROT_CTRL                                       0x00000110
#define B_MSR_PLAT_FRMW_PROT_CTRL_LK                                  MRC_BIT0
#define B_MSR_PLAT_FRMW_PROT_CTRL_EN                                  MRC_BIT1
#define B_MSR_PLAT_FRMW_PROT_CTRL_S1                                  MRC_BIT2
#define MSR_PLAT_FRMW_PROT_HASH_0                                     0x00000111
#define MSR_PLAT_FRMW_PROT_HASH_1                                     0x00000112
#define MSR_PLAT_FRMW_PROT_HASH_2                                     0x00000113
#define MSR_PLAT_FRMW_PROT_HASH_3                                     0x00000114
#define MSR_PLAT_FRMW_PROT_TRIG_PARAM                                 0x00000115
#define N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_STATUS_OFFSET                 0
#define V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_STATUS_MASK                   0x000000000000FFFF
#define N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_DATA_OFFSET                   16
#define V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_DATA_MASK                     0x000000000000FFFF
#define N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_TERMINAL_OFFSET               32
#define V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_TERMINAL_MASK                 0x000000000000FFFF
#define B_MSR_PLAT_FRMW_PROT_TRIG_PARAM_SE                            MRC_BIT62
#define N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_SE_OFFSET                     62
#define MSR_PLAT_FRMW_PROT_TRIGGER                                    0x00000116
#define MSR_PLAT_FRMW_PROT_PASSWD                                     0x00000117
#define MSR_PLAT_BIOS_INFO_FLAGS                                      0x0000011F
#define MSR_SPCL_CHIPSET_USAGE_ADDR                                   0x000001FE
#define MSR_IA32_FEATURE_CONFIG                                       0x0000013C
#define B_IA32_FEATURE_CONFIG_AES_DIS                                 MRC_BIT1
#define B_IA32_FEATURE_CONFIG_LOCK                                    MRC_BIT0
#define MSR_FLEX_RATIO                                                0x00000194
#define N_FLEX_RATIO                                                  8
#define B_FLEX_RATIO                                                  (0xFF << 8)
#define B_FLEX_EN                                                     MRC_BIT16
#define B_MAX_EXTRA_VOLTAGE                                           0xFF
#define N_OVERCLOCKING_BINS                                           17
#define B_OVERCLOCKING_BINS                                           (0x7 << 17)
#define B_OVERCLOCKING_LOCK                                           MRC_BIT20
#define RATIO_FLEX_CLEAR_MASK                                         0xFFFFFFFFFFFF00FFULL
#define N_IA32_PERF_STSP_STATE_TARGET                                 8
#define B_IA32_PERF_STSP_STATE_MASK                                   0xFF
#define N_IA32_PERF_CTRLP_STATE_TARGET                                8
#define B_IA32_PERF_CTRLP_STATE_TARGET                                (0x7F << 8)
#define B_MSR_IA32_MISC_DISABLE_TURBO                                 MRC_BIT38
#define MSR_TEMPERATURE_TARGET                                        0x000001A2
#define N_MSR_TEMPERATURE_TARGET_TCC_OFFSET_LIMIT                     24
#define N_MSR_TEMPERATURE_TARGET_TCC_ACTIVATION_TEMPERATURE_OFFSET    (16)
#define B_MSR_TEMPERATURE_TARGET_TCC_ACTIVATION_TEMPERATURE_MASK      (0xFF << 16)
#define N_MSR_TEMPERATURE_TARGET_FAN_TEMP_TARGET_OFFSET               8
#define B_MSR_TEMPERATURE_TARGET_FAN_TEMP_TARGET_OFFSET               (0xFF << 8)
#define B_MSR_TEMPERATURE_TARGET_TCC_OFFSET_TIME_WINDOW               (0x7F)
#define B_MSR_TEMPERATURE_TARGET_TCC_OFFSET_MASK                      0xFF
#define B_MSR_TEMPERATURE_TARGET_TCC_OFFSET_CLAMP_ENABLE              MRC_BIT7
#define MISC_FEATURE_CONTROL                                          0x000001A4
#define B_MISC_FEATURE_CONTROL_MLC_STRP                               MRC_BIT0
#define B_MISC_FEATURE_CONTROL_MLC_SPAP                               MRC_BIT1
#define B_MISC_FEATURE_CONTROL_DCU_STRP                               MRC_BIT2
#define B_MISC_FEATURE_CONTROL_DCU_IPP                                MRC_BIT3
#define B_MISC_FEATURE_CONTROL_3_STRIKE_CNT                           MRC_BIT11
#define MSR_MISC_PWR_MGMT                                             0x000001AA
#define B_MISC_PWR_MGMT_SINGLE_PCTL_EN                                MRC_BIT0
#define B_MISC_PWR_MGMT_ENABLE_HWP                                    MRC_BIT6
#define B_MSR_MISC_PWR_MGMT_ENABLE_HWP_INTERRUPT_MASK                          MRC_BIT7
#define B_MISC_PWR_MGMT_ENABLE_OUT_OF_BAND_AUTONOMOUS                 MRC_BIT8
#define B_MISC_PWR_MGMT_ENABLE_SDC_OOB                                MRC_BIT9
#define N_MISC_PWR_MGMT_ENABLE_SDC_OOB                                9
#define B_MISC_PWR_MGMT_ENABLE_SDC                                    MRC_BIT10
#define N_MISC_PWR_MGMT_ENABLE_SDC                                    10
#define B_MISC_PWR_MGMT_SDC_OOB_CAPABLE                               MRC_BIT11
#define B_MISC_PWR_MGMT_LOCK_TERM_INT                                 MRC_BIT22
#define MSR_TURBO_RATIO_LIMIT                                         0x000001AD
#define N_MSR_TURBO_RATIO_LIMIT_1C                                    0
#define B_MSR_TURBO_RATIO_LIMIT_1C                                    (0xFF << 0)
#define N_MSR_TURBO_RATIO_LIMIT_2C                                    8
#define B_MSR_TURBO_RATIO_LIMIT_2C                                    (0xFF << 8)
#define N_MSR_TURBO_RATIO_LIMIT_3C                                    16
#define B_MSR_TURBO_RATIO_LIMIT_3C                                    (0xFF << 16)
#define N_MSR_TURBO_RATIO_LIMIT_4C                                    24
#define B_MSR_TURBO_RATIO_LIMIT_4C                                    (0xFF << 24)
#define MSR_POWER_CTL                                                 0x000001FC
#define B_MSR_POWER_CTL_BI_PROCHOT                                    MRC_BIT0
#define B_MSR_POWER_CTL_C1E                                           MRC_BIT1
#define B_ENERGY_EFFICIENT_P_STATE_FEATURE_ENABLE                     MRC_BIT18
#define B_MSR_POWER_CTL_DISABLE_PROCHOT_OUT                           MRC_BIT21
#define B_MSR_POWER_CTL_PROCHOT_RESPONSE                              MRC_BIT22
#define B_MSR_POWER_CTL_PROCHOT_LOCK                                  MRC_BIT23
#define B_MSR_POWER_CTL_DISABLE_VR_THERMAL_ALERT                      MRC_BIT24
#define B_MSR_POWER_CTL_CSTATE_PRE_WAKE_DISABLE                       MRC_BIT30
#define MSR_LT_UNLOCK_MEMORY                                          0x000002E6
#define MSR_LT_LOCK_MEMORY                                            0x000002E7
#define B_MSR_LT_LOCK_MEMORY_CONFIG_LOCK                              MRC_BIT0
#define B_MSR_LT_LOCK_MEMORY_MEM_LOCK_CPU                             MRC_BIT1
#define B_MSR_LT_LOCK_MEMORY_MEM_LOCK_DEV                             MRC_BIT2
#define MSR_PL4_CONTROL                                               0x00000601
#define V_POWER_LIMIT_4_MASK                                          (0x1FFF)
#define MSR_PACKAGE_POWER_SKU_UNIT                                    0x606
#define PACKAGE_POWER_UNIT_MASK                                       0xF
#define MSR_C_STATE_LATENCY_CONTROL_0                                 0x60A
#define MSR_C_STATE_LATENCY_CONTROL_1                                 0x60B
#define MSR_C_STATE_LATENCY_CONTROL_2                                 0x60C
#define MSR_C_STATE_LATENCY_CONTROL_3                                 0x633
#define MSR_C_STATE_LATENCY_CONTROL_4                                 0x634
#define MSR_C_STATE_LATENCY_CONTROL_5                                 0x635
#define B_PKG_IRTL_VALID                                              MRC_BIT15
#define B_INTERRUPT_RESPONSE_TIME_LIMIT_MASK                          0x3FF
#define B_TIME_UNIT_MASK                                              (0x7 << 10)
#define N_TIME_UNIT_OFFSET                                            10
#define MSR_PACKAGE_POWER_LIMIT                                       0x610
#define MSR_PACKAGE_POWER_SKU                                         0x614
#define B_POWER_LIMIT_ENABLE                                          MRC_BIT15
#define B_CRITICAL_POWER_CLAMP_ENABLE                                 MRC_BIT16
#define B_POWER_LIMIT_LOCK                                            MRC_BIT31
#define POWER_LIMIT_MASK                                              (0x7FFF)
#define POWER_LIMIT_1_TIME_MASK                                       (0xFE0000)
#define PACKAGE_TDP_POWER_MASK                                        (0x7FFF)
#define PACKAGE_MIN_POWER_MASK                                        (0x7FFF0000)
#define PACKAGE_MAX_POWER_MASK                                        (0x7FFF)
#define MSR_PL3_CONTROL                                               0x615
#define POWER_LIMIT_3_TIME_MASK                                       (0xFE0000)
#define POWER_LIMIT_3_DUTY_CYCLE_MASK                                 (0x7F000000)
#define MSR_DDR_RAPL_LIMIT                                            0x618
#define MSR_RING_RATIO_LIMIT                                          0x620
#define V_MSR_RING_RATIO_LIMIT_MASK                                   0x7F
#define MSR_CONFIG_TDP_NOMINAL                                        0x648
#define CONFIG_TDP_NOMINAL_RATIO_MASK                                 0xFF
#define MSR_CONFIG_TDP_LEVEL1                                           0x649
#define CONFIG_TDP_LVL1_RATIO_OFFSET                                  16
#define CONFIG_TDP_LVL1_RATIO_MASK                                    (0xFF << 16)
#define CONFIG_TDP_LVL1_PKG_TDP_MASK                                  (0x7FFF)
#define MSR_CONFIG_TDP_LEVEL2                                           0x64A
#define CONFIG_TDP_LVL2_RATIO_OFFSET                                  16
#define CONFIG_TDP_LVL2_RATIO_MASK                                    (0xFF << 16)
#define CONFIG_TDP_LVL2_PKG_TDP_MASK                                  (0x7FFF)
#define MSR_CONFIG_TDP_CONTROL                                        0x64B
#define CONFIG_TDP_CONTROL_LOCK                                       (1 << 31)
#define CONFIG_TDP_CONTROL_LVL_MASK                                   0x3
#define CONFIG_TDP_NOMINAL                                            0
#define CONFIG_TDP_LEVEL1                                             1
#define CONFIG_TDP_LEVEL2                                             2
#define MSR_TURBO_ACTIVATION_RATIO                                    0x64C
#define MSR_TURBO_ACTIVATION_RATIO_LOCK                               (1 << 31)
#define MSR_TURBO_ACTIVATION_RATIO_MASK                               0xFF
#define MSR_PLATFORM_POWER_LIMIT                                      0x65C
#define MSR_PKG_HDC_CONFIG_CTL                                        0x00000652
#define B_PKG_HDC_CONFIG_CTL_SDC_CX_MONITOR                           (MRC_BIT0 | MRC_BIT1 | MRC_BIT2)
#define N_PKG_HDC_CONFIG_CTL_SDC_CX_MONITOR                           0
#define B_PKG_HDC_CONFIG_CTL_SDC_MCNT_COUNT_METHOD                    MRC_BIT3
#define N_PKG_HDC_CONFIG_CTL_SDC_MCNT_COUNT_METHOD                    3
#define B_PKG_HDC_CONFIG_CTL_SDC_MAX_FORCE_IDLE_DURATION_TIME         (MRC_BIT5 | MRC_BIT6 | MRC_BIT7 | MRC_BIT8 | MRC_BIT9 | MRC_BIT10)
#define N_PKG_HDC_CONFIG_CTL_SDC_MAX_FORCE_IDLE_DURATION_TIME         5
#define B_PKG_HDC_CONFIG_CTL_SDC_DIRECT_CONTROL                       (MRC_BIT12 | MRC_BIT13 | MRC_BIT14 | MRC_BIT15 | MRC_BIT16 | MRC_BIT17 | MRC_BIT18)
#define N_PKG_HDC_CONFIG_CTL_SDC_DIRECT_CONTROL                       12
#define B_PKG_HDC_CONFIG_CTL_MIN_ACTIVE_TIME                          (MRC_BIT19 | MRC_BIT20 | MRC_BIT21 | MRC_BIT22 | MRC_BIT23 | MRC_BIT24 | MRC_BIT25 | MRC_BIT26)
#define N_PKG_HDC_CONFIG_CTL_MIN_ACTIVE_TIME                          19
#define B_HDC_PKG_CTL_SDC_PACKAGE_ENABLE                              MRC_BIT0
#define N_HDC_PKG_CTL_SDC_PACKAGE_ENABLE                              0
#define B_HDC_PKG_CTL_SDC_WAS_ONCE_ENABLED                            MRC_BIT1
#define N_HDC_PKG_CTL_SDC_WAS_ONCE_ENABLED                            1
#define MSR_IA32_PM_CTL1                                              0x00000DB1
#define B_PM_CTL1_SDC_ALLOWED                                         MRC_BIT0
#define N_PM_CTL1_SDC_ALLOWED                                         0
#define B_MSR_EMRR_PHYS_MASK_EN                                       MRC_BIT11
#define B_MSR_EMRR_PHYS_MASK_LOCK                                     MRC_BIT10
#define V_MAXIMUM_VARIABLE_MTRR_NUMBER                                10
#define V_FIXED_MTRR_NUMBER                                           11
#define MSR_IA32_CR_PAT                                               0x00000277
#define B_CACHE_MTRR_VALID                                            MRC_BIT11
#define B_CACHE_FIXED_MTRR_VALID                                      MRC_BIT10
#define NO_EVICT_MODE                                                 0x000002E0
#define B_NO_EVICT_MODE_SETUP                                         MRC_BIT0
#define B_NO_EVICT_MODE_RUN                                           MRC_BIT1
#define UNCORE_CR_MEMLOCK_COMMANDS                                    0x000002E2
#define B_LOCK_MEM_CFG                                                MRC_BIT1
#define EFI_PCIEXBAR                                                  0x00000300
#define B_PCIEXBAR_EN                                                 MRC_BIT0
#define B_PCIEXBAR_SIZE                                               (MRC_BIT1 | MRC_BIT2 | MRC_BIT3)
#define N_PCIEXBAR_SIZE                                               1
#define MSR_IA32_VMX_BASIC                                            0x00000480
#define MSR_IA32_VMX_MISC                                             0x00000485
#define APIC_GLOBAL_ENABLE                                            0x00000800
#define B_RTIT_CTL_TRACE_ENABLE                                       MRC_BIT0

//
// MSRs for SMM State Save Register
//
#define MSR_SMM_MCA_CAP                                               0x17D
#define B_TARGETED_SMI                                                MRC_BIT56
#define N_TARGETED_SMI                                                56
#define B_SMM_CPU_SVRSTR                                              MRC_BIT57
#define N_SMM_CPU_SVRSTR                                              57
#define B_SMM_CODE_ACCESS_CHK                                         MRC_BIT58
#define N_SMM_CODE_ACCESS_CHK                                         58
#define B_LONG_FLOW_INDICATION                                        MRC_BIT59
#define N_LONG_FLOW_INDICATION                                        59
#define MSR_SMM_FEATURE_CONTROL                                       0x4E0
#define B_SMM_FEATURE_CONTROL_LOCK                                    MRC_BIT0
#define B_SMM_CPU_SAVE_EN                                             MRC_BIT1
#define B_SMM_CODE_CHK_EN                                             MRC_BIT2
#define MSR_SMM_ENABLE                                                0x4E1
#define MSR_SMM_DELAYED                                               0x4E2
#define MSR_SMM_BLOCKED                                               0x4E3
#define MSR_CR0                                                       0xC00
#define MSR_CR3                                                       0xC01
#define MSR_EFLAGS                                                    0xC02
#define MSR_RIP                                                       0xC04
#define MSR_DR6                                                       0xC05
#define MSR_DR7                                                       0xC06
#define MSR_TR_LDTR                                                   0xC07
#define MSR_GS_FS                                                     0xC08
#define MSR_DS_SS                                                     0xC09
#define MSR_CS_ES                                                     0xC0A
#define MSR_IO_MISC_INFO                                              0xC0B
#define MSR_IO_MEM_ADDR                                               0xC0C
#define MSR_RDI                                                       0xC0D
#define MSR_RSI                                                       0xC0E
#define MSR_RBP                                                       0xC0F
#define MSR_RSP                                                       0xC10
#define MSR_RBX                                                       0xC11
#define MSR_RDX                                                       0xC12
#define MSR_RCX                                                       0xC13
#define MSR_RAX                                                       0xC14
#define MSR_R8                                                        0xC15
#define MSR_R9                                                        0xC16
#define MSR_R10                                                       0xC17
#define MSR_R11                                                       0xC18
#define MSR_R12                                                       0xC19
#define MSR_R13                                                       0xC1A
#define MSR_R14                                                       0xC1B
#define MSR_R15                                                       0xC1C
#define MSR_EVENT_CTL_HLT_IO                                          0xC1F
#define MSR_SMBASE                                                    0xC20
#define MSR_SMM_REVID                                                 0xC21
#define MSR_IEDBASE                                                   0xC22
#define MSR_EPTP_ENABLE                                               0xC23
#define MSR_EPTP                                                      0xC24
#define MSR_LDTR_BASE                                                 0xC2C
#define MSR_IDTR_BASE                                                 0xC2D
#define MSR_GDTR_BASE                                                 0xC2E
#define MSR_CR4                                                       0xC37
#define MSR_IO_RSI                                                    0xC40
#define MSR_IO_RCX                                                    0xC41
#define MSR_IO_RIP                                                    0xC42
#define MSR_IO_RDI                                                    0xC43
#define MSR_BC_PBEC                                                   0x139
#define B_STOP_PBET                                                   MRC_BIT0

#define MSR_BOOT_GUARD_SACM_INFO                                      0x13A
#define B_BOOT_GUARD_SACM_INFO_NEM_ENABLED                            MRC_BIT0
#define V_TPM_PRESENT_MASK                                            0x06
#define V_TPM_PRESENT_NO_TPM                                          0
#define V_TPM_PRESENT_DTPM_12                                         1
#define V_TPM_PRESENT_DTPM_20                                         2
#define V_TPM_PRESENT_PTT                                             3
#define B_BOOT_GUARD_SACM_INFO_TPM_SUCCESS                            MRC_BIT3
#define B_BOOT_GUARD_SACM_INFO_MEASURED_BOOT                          MRC_BIT5
#define B_BOOT_GUARD_SACM_INFO_VERIFIED_BOOT                          MRC_BIT6
#define B_BOOT_GUARD_SACM_INFO_CAPABILITY                             MRC_BIT32
#define TXT_PUBLIC_BASE                                               0xFED30000
#define R_CPU_BOOT_GUARD_ERRORCODE                                    0x30
#define R_CPU_BOOT_GUARD_BOOTSTATUS                                   0xA0
#define R_CPU_BOOT_GUARD_ACM_STATUS                                   0x328
#define V_CPU_BOOT_GUARD_LOAD_ACM_SUCCESS                             0x8000000000000000
#define B_BOOT_GUARD_ACM_ERRORCODE_MASK                               0x00007FF0

#define B_IA32_HWP_CHANGE_TO_GUARANTEED                               MRC_BIT0
#define B_IA32_HWP_EXCURSION_TO_MINIMUM                               MRC_BIT1


#define B_HWP_CHANGE_TO_GUARANTEED                                    MRC_BIT0
#define B_HWP_EXCURSION_TO_MINIMUM                                    MRC_BIT2

///
/// Local APIC definitions
///
#define MMIO_LOCAL_APIC_THERMAL_DEF                                   0xFEE00330
#define B_INTERRUPT_MASK                                              (1 << 16)
#define B_DELIVERY_MODE                                               (0x07 << 8)
#define V_MODE_SMI                                                    (0x02 << 8)
#define B_VECTOR                                                      (0xFF << 0)
//
// Processor Definitions
//
#define CPUID_FULL_STEPPING                         0x0000000F
#define CPUID_FULL_FAMILY_MODEL                     0x0FFF0FF0
#define CPUID_FULL_FAMILY_MODEL_STEPPING            0x0FFF0FFF
#define CPUID_FULL_FAMILY_MODEL_TIGERLAKE_ULT_ULX   0x000806C0
#define CPUID_FULL_FAMILY_MODEL_TIGERLAKE_DT_HALO   0x000806D0

#ifndef STALL_ONE_MICRO_SECOND
#define STALL_ONE_MICRO_SECOND 1
#endif
#ifndef STALL_ONE_MILLI_SECOND
#define STALL_ONE_MILLI_SECOND 1000
#endif

#define BITS(x) (1 << (x))

//
// TME MSRs
//
#define MSR_IA32_TME_CAPABILITY                                       0x981
#define B_TME_CAPABILITY_AES_XTS                                      BIT0
#define MSR_IA32_TME_ACTIVATE                                         0x982
#define V_TME_ACTIVATE_TME_POLICY_AES_XTS                             0x0000
#define N_TME_ACTIVATE_TME_POLICY_OFFSET                              4
#define B_TME_ACTIVATE_TME_ENABLE                                     BIT1
#define B_TME_ACTIVATE_KEY_SELECT                                     BIT2
#define B_TME_ACTIVATE_SAVE_KEY                                       BIT3
#define MSR_IA32_TME_EXCLUDE_MASK                                     0x983
#define B_TME_EXCLUDE_MASK_ENABLE                                     BIT11
#define MSR_IA32_TME_EXCLUDE_BASE                                     0x984

/**
Notes :
  1.  Bit position always starts at 0.
  2.  Following macros are applicable only for Word aligned integers.
**/
#define BIT(Pos, Value)               (1 << (Pos) & (Value))
#define BITRANGE(From, Width, Value)  (((Value) >> (From)) & ((1 << (Width)) - 1))

typedef enum {
  // TigerLake ULX/ULT Steppings
  EnumTglA0 = 0,
  EnumTglB0 = 1,

  // TigerLake DT/HALO Steppings
  EnumTglP0 = 0,
  EnumTglQ0 = 1,

  /// Max Stepping
  EnumCpuSteppingMax  = CPUID_FULL_STEPPING
} CPU_STEPPING;

typedef enum {
  EnumCpuUlt        = 0,
  EnumCpuTrad,
  EnumCpuUlx,
  EnumCpuHalo,
  EnumCpuUnknown
} CPU_SKU;
#pragma pack (pop)
#endif // _CPU_REGS_H_


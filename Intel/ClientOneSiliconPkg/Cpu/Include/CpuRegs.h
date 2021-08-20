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
  Copyright 2004 - 2019 Intel Corporation.

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

#include "Register/CoreMsrcommon.h"
#include "Register/FscpMsrcommon.h"
#include "Register/Pcucommon.h"
#include "Register/VirtualMsrcommon.h"


#define MSR_UCODE_CR_ROP_DETECT_CAPS                                  0x00000352
#define CPUID_SGX_ENABLED                                             0x12

#define B_IA32_MTRR_CAP_PRMRR_SUPPORT                                 BIT12

#define MSR_GT_SLEEP_CMDSTS                                           0x00000118
#define B_MSR_MAILBOX_INTERNAL_PCODE_KEEP_GT_RC6                      BIT0

/**
  Available ways vectors for class of service for small core
**/
#define MSR_IA32_CR_LLC_QOS_MASK0                                     0xC90
#define MSR_IA32_CR_LLC_QOS_MASK1                                     0xC91
#define MSR_IA32_CR_LLC_QOS_MASK2                                     0xC92
#define MSR_IA32_CR_LLC_QOS_MASK3                                     0xC93
#define B_MSR_IA32_CR_LLC_QOS_MASK                                    0x000000000000FFFF

#define PRMRR_MAX_SIZE                                                0x10000000

#define MSR_PRMRR_VALID_CONFIG                                        0x000001FB
#define B_MSR_PRMRR_PHYS_MASK_LOCK                                    BIT10
#define MSR_PLAT_FRMW_PROT_PASSWD                                     0x00000117
#define MSR_PLAT_BIOS_INFO_FLAGS                                      0x0000011F
#define V_BIOS_UCODE_PM_TMR_EMULATION_CFG_CORRECTION_FACTOR_19_MHZ    0x2FBA2E26
#define V_BIOS_UCODE_PM_TMR_EMULATION_CFG_CORRECTION_FACTOR_24_MHZ    0x262E8B52
#define V_BIOS_UCODE_PM_TMR_EMULATION_CFG_CORRECTION_FACTOR_38_MHZ    0x17DD1713
#define V_BIOS_UCODE_PM_TMR_EMULATION_CFG_DELAY_VALUE                 0x13

#define NO_EVICT_MODE                                                 0x000002E0
#define B_NO_EVICT_MODE_SETUP                                         BIT0
#define B_NO_EVICT_MODE_RUN                                           BIT1

#define MSR_LT_LOCK_MEMORY                                            0x000002E7
#define B_MSR_LT_LOCK_MEMORY_CONFIG_LOCK                              BIT0
#define B_MSR_LT_LOCK_MEMORY_MEM_LOCK_CPU                             BIT1
#define B_MSR_LT_LOCK_MEMORY_MEM_LOCK_DEV                             BIT2

#define MSR_UNCORE_PERF_STATUS                                        0x00000621
#define N_MSR_UNCORE_PERF_LLC_RING_VOLTAGE_OFFSET                     16
#define V_MSR_UNCORE_PERF_LLC_RING_VOLTAGE_MASK                       0xFFFF0000
#define V_MSR_UNCORE_PERF_LLC_RING_VOLTAGE_MSB_MASK                   0x7

#define MSR_IA32_TME_CAPABILITY                                       0x981
#define B_TME_CAPABILITY_AES_XTS                                      BIT0
#define V_TME_ACTIVATE_TME_POLICY_AES_XTS                             0x0
#define N_TME_ACTIVATE_TME_POLICY_OFFSET                              0x4
#define MSR_IA32_TME_ACTIVATE                                         0x982
#define B_TME_ACTIVATE_TME_ENABLE                                     BIT1
#define B_TME_ACTIVATE_KEY_SELECT                                     BIT2
#define B_TME_ACTIVATE_SAVE_KEY                                       BIT3
#define MSR_IA32_TME_EXCLUDE_MASK                                     0x983
#define B_TME_EXCLUDE_MASK_ENABLE                                     BIT11
#define MSR_IA32_TME_EXCLUDE_BASE                                     0x984
//
// 2LM Far Memory Encryption MSR
//
#define MSR_IA32_FME_ACTIVATE                                         0x81
#define B_FME_ACTIVATE_FME_LOCK                                       BIT0
#define B_FME_ACTIVATE_FME_ENABLE                                     BIT1
#define B_FME_ACTIVATE_KEY_SELECT                                     BIT2
#define B_FME_ACTIVATE_SAVE_KEY                                       BIT3

#define MSR_BC_PBEC                                                   0x00000139
#define B_STOP_PBET                                                   BIT0
#define MSR_BOOT_GUARD_SACM_INFO                                      0x0000013A
#define B_BOOT_GUARD_SACM_INFO_NEM_ENABLED                            BIT0
#define V_TPM_PRESENT_MASK                                            0x06
#define V_TPM_PRESENT_NO_TPM                                          0
#define V_TPM_PRESENT_DTPM_12                                         1
#define V_TPM_PRESENT_DTPM_20                                         2
#define V_TPM_PRESENT_PTT                                             3
#define B_BOOT_GUARD_SACM_INFO_TPM_SUCCESS                            BIT3
#define B_BOOT_GUARD_SACM_INFO_MEASURED_BOOT                          BIT5
#define B_BOOT_GUARD_SACM_INFO_VERIFIED_BOOT                          BIT6
#define B_BOOT_GUARD_SACM_INFO_CAPABILITY                             BIT32

#define N_MSR_TURBO_RATIO_LIMIT_MAX_TURBO_5_CORES_OFFSET (32)
#define N_MSR_TURBO_RATIO_LIMIT_MAX_TURBO_6_CORES_OFFSET (40)
#define N_MSR_TURBO_RATIO_LIMIT_MAX_TURBO_7_CORES_OFFSET (48)
#define N_MSR_TURBO_RATIO_LIMIT_MAX_TURBO_8_CORES_OFFSET (56)

#define B_ATOM_COS_ENABLE                    1
/**
  Resource Association Register (R/W). If ( (CPUID.(EAX=07H, ECX=0):EBX[12]
  =1) or (CPUID.(EAX=07H, ECX=0):EBX[15] =1 ) ).

  @param  ECX  MSR_IA32_PQR_ASSOC (0x00000C8F)
  @param  EAX  Lower 32-bits of MSR value.
               Described by the type MSR_IA32_PQR_ASSOC_REGISTER.
  @param  EDX  Upper 32-bits of MSR value.
               Described by the type MSR_IA32_PQR_ASSOC_REGISTER.

  <b>Example usage</b>
  @code
  MSR_IA32_PQR_ASSOC_REGISTER  Msr;

  Msr.Uint64 = AsmReadMsr64 (MSR_IA32_PQR_ASSOC);
  AsmWriteMsr64 (MSR_IA32_PQR_ASSOC, Msr.Uint64);
  @endcode
  @note MSR_IA32_PQR_ASSOC is defined as IA32_PQR_ASSOC in SDM.
**/
#define MSR_ATOM_CORE_IA32_PQR_ASSOC                       0x00000C8F

/**
  MSR information returned for MSR index #MSR_IA32_PQR_ASSOC
**/
typedef union {
  ///
  /// Individual bit fields
  ///
  struct {
    UINT32  Reserved:32;
    ///
    /// [Bits 35:32] COS (R/W). The class of service (COS) to enforce (on
    /// writes); returns the current COS when read.
    ///
    UINT32  COS:4;
    UINT32  Reserved1:28;
  } Bits;
  ///
  /// All bit fields as a 64-bit value
  ///
  UINT64  Uint64;
} MSR_ATOM_CORE_IA32_PQR_ASSOC_REGISTER;

//
// MSRs for SMM State Save Register
//
#define MSR_SMM_FEATURE_CONTROL                                       0x000004E0
#define B_SMM_FEATURE_CONTROL_LOCK                                    BIT0
#define B_SMM_CPU_SAVE_EN                                             BIT1
#define B_SMM_CODE_CHK_EN                                             BIT2



#define V_MSR_RING_RATIO_LIMIT_MASK                                   0x7F
#define PACKAGE_POWER_UNIT_MASK                                       0xF
#define B_POWER_LIMIT_ENABLE                                          BIT15
#define B_CRITICAL_POWER_CLAMP_ENABLE                                 BIT16
#define B_POWER_LIMIT_LOCK                                            BIT31
#define POWER_LIMIT_MASK                                              (0x7FFF)
#define POWER_LIMIT_1_TIME_MASK                                       (0xFE0000)
#define PACKAGE_TDP_POWER_MASK                                        (0x7FFF)
#define PACKAGE_MIN_POWER_MASK                                        (0x7FFF0000)
#define PACKAGE_MAX_POWER_MASK                                        (0x7FFF)
#define B_RAPL_LIMIT_LOCK                                             BIT63
#define V_MSR_TEMPERATURE_TARGET_TCC_ACTIVATION_OFFSET_MASK           0x3F

#define B_TIMED_MWAIT_ENABLE                                          BIT31 ///< @todo Remove when bitfield definition is available.
#define V_CSTATE_LIMIT_C1                                             0x01
#define V_CSTATE_LIMIT_C3                                             0x02
#define V_CSTATE_LIMIT_C6                                             0x03
#define V_CSTATE_LIMIT_C7                                             0x04
#define V_CSTATE_LIMIT_C7S                                            0x05
#define V_CSTATE_LIMIT_C8                                             0x06
#define V_CSTATE_LIMIT_C9                                             0x07
#define V_CSTATE_LIMIT_C10                                            0x08

#define V_IO_CAPT_LVL2                                                (0x0 << 16)   ///< C3
#define V_IO_CAPT_LVL3                                                (0x1 << 16)   ///< C6
#define V_IO_CAPT_LVL4                                                (0x2 << 16)   ///< C7
#define V_IO_CAPT_LVL5                                                (0x3 << 16)   ///< C8
#define V_IO_CAPT_LVL6                                                (0x4 << 16)   ///< C9
#define V_IO_CAPT_LVL7                                                (0x5 << 16)   ///< C10

#define B_CAP_MSR_HWP_REQ                                             BIT0

#define MSR_FAST_UNCORE_MSR_CTL_MASK                                  BIT0

//
// Bit defines for MSR_IA32_PERF_STATUS
//
#define N_IA32_PERF_STSP_STATE_TARGET                                 8
#define B_IA32_PERF_STSP_STATE_MASK                                   0xFF
//
// Bit defines for MSR_IA32_PERF_CTL
//
#define N_IA32_PERF_CTRLP_STATE_TARGET                                8
#define B_IA32_PERF_CTRLP_STATE_TARGET                                (0x7F << 8)

//
// Bit defines for MSR_IA32_MISC_ENABLE
//
#define B_MSR_IA32_MISC_DISABLE_TURBO                                 BIT38

//
// Number of fixed MTRRs
//
#define V_FIXED_MTRR_NUMBER                                           11

//
// Bit defines for MSR_IA32_MTRR_DEF_TYPE
//
#define B_CACHE_FIXED_MTRR_VALID                                      BIT10
#define B_CACHE_MTRR_VALID                                            BIT11

//
// Bit defines for MSR_IA32_X2APIC_LVT_THERMAL
//
#define MMIO_LOCAL_APIC_THERMAL_DEF                                   0xFEE00330
#define B_INTERRUPT_MASK                                              (1 << 16)
#define B_DELIVERY_MODE                                               (0x07 << 8)
#define V_MODE_SMI                                                    (0x02 << 8)
#define B_VECTOR                                                      (0xFF << 0)

//
// Bit define for Intel Turbo Boost Max Technology 3.0
//
#define B_ITBM_ENABLE                                                 BIT14
//
// Bit defines for MSR_IA32_PKG_HDC_CTL
//
#define B_HDC_PKG_CTL_SDC_PACKAGE_ENABLE                              BIT0
#define N_HDC_PKG_CTL_SDC_PACKAGE_ENABLE                              0
#define B_HDC_PKG_CTL_SDC_WAS_ONCE_ENABLED                            BIT1
#define N_HDC_PKG_CTL_SDC_WAS_ONCE_ENABLED                            1

//#define MSR_SMM_SAVE_CONTROL (0x0000003E)
//#define B_MSR_SMM_SAVE_CONTROL_SAVE_FP_STATE_MASK BIT0

#define MSR_FIT_BIOS_ERROR                                            0x000000A5
#define N_MSR_FIT_BIOS_ERROR_ERROR_CODE_OFFSET                        0
#define B_MSR_FIT_BIOS_ERROR_ERROR_CODE_MASK                          0x000000FF
#define N_MSR_FIT_BIOS_ERROR_ENTRY_TYPE_OFFSET                        8
#define B_MSR_FIT_BIOS_ERROR_ENTRY_TYPE_MASK                          0x0000FF00

#define FIT_HEADER_ENTRY                                              0x0
#define FIT_SUCCESSFUL                                                0x0
#define FIT_SIZE_CHECK                                                0x1
#define FIT_RESERVED_FIELD_CHECK                                      0x2
#define FIT_VERSION_AND_TYPE_CHECK                                    0x3

#define FIT_MICROCODE_UPDATE_ENTRY                                    0x1
#define FIT_NO_MICROCODE_UPDATE                                       0x1
#define FIT_MICROCODE_UPDATE_FAIL                                     0x2

#define FIT_STARTUP_ACM_ENTRY                                         0x2
#define FIT_STARTUP_ACM_NOT_SUPPORTED                                 0x1
#define FIT_FATAL_ERROR_DURING_ACM                                    0x2
#define FIT_CPU_DOES_NOT_SUPPORT_LT                                   0x3
#define FIT_BIST_ERRORS                                               0x4
#define FIT_BEYOND_END_OF_FIT                                         0x5
#define FIT_NO_FIT_ACM_TYPE_MISMATCH                                  0x6
#define FIT_ACM_BASE_SIZE_AND_CHECKS                                  0x7

#define FIT_GENERAL_CHECKS                                            0x7F
#define FIT_DISABLED_BY_CPU                                           0x1
#define FIT_POINTER_ERROR                                             0x2
#define FIT_FIRST_FIT_ENTRY_MISMATCH                                  0x3

//#define MSR_BIOS_UCODE_PM_TMR_EMULATION_CFG (0x00000121)
//#define B_MSR_BIOS_UCODE_PM_TMR_EMULATION_CFG_VALID_MASK BIT16
//#define N_MSR_BIOS_UCODE_PM_TMR_EMULATION_CFG_RSP_DELAY_LOOP_COUNT_OFFSET (20)
//#define N_MSR_BIOS_UCODE_PM_TMR_EMULATION_CFG_CORRECTION_FACTOR_OFFSET (32)

//#define MSR_FEATURE_CONFIG (0x0000013C)
//#define B_MSR_FEATURE_CONFIG_LOCK_MASK BIT0
//#define B_MSR_FEATURE_CONFIG_AES_DISABLE_MASK BIT1

//#define MSR_BIOS_DONE (0x00000151)
//#define B_MSR_BIOS_DONE_ENABLE_IA_UNTRUSTED_MASK BIT0

//#define MSR_LT_UNLOCK_MEMORY (0x000002E6)

//#define MSR_PL3_CONTROL (0x00000615)
//#define B_MSR_PL3_CONTROL_TIMEWINDOW_MASK (0x00FE0000)
//#define B_MSR_PL3_CONTROL_DUTYCYLE_MASK (0x7F000000)

//#define MSR_PRMRR_MASK (0x000001F5)
//#define B_MSR_PRMRR_MASK_L_MASK BIT10
//#define B_MSR_PRMRR_MASK_VLD_MASK BIT11


//#define MSR_VR_CURRENT_CONFIG (0x00000601)
//#define B_MSR_VR_CURRENT_CONFIG_CURRENT_LIMIT_MASK (0x0000000000001FFF)

//#define MSR_UNCORE_RATIO_LIMIT (0x00000620)

//#define MSR_CONFIG_TDP_NOMINAL (0x00000648)
//#define N_MSR_PLATFORM_INFO_CONFIG_TDP_LEVELS_OFFSET (33)
//#define B_MSR_PLATFORM_INFO_CONFIG_TDP_LEVELS_MASK (BIT34 | BIT33)

#define B_MSR_PLATFORM_INFO_SMM_SAVE_CAP_MASK BIT16

#define B_MSR_PLATFORM_INFO_SAMPLE_PART_MASK BIT27

//#define B_MSR_TEMPERATURE_TARGET_TCC_OFFSET_CLAMPING_BIT_MASK BIT7
//#define B_MSR_TEMPERATURE_TARGET_TCC_OFFSET_TIME_WINDOW_MASK (0x0000007F)
//#define N_MSR_TEMPERATURE_TARGET_FAN_TEMP_TARGET_OFST_OFFSET (8)
//#define B_MSR_TEMPERATURE_TARGET_FAN_TEMP_TARGET_OFST_MASK (0x0000FF00)

//#define N_MSR_TEMPERATURE_TARGET_TJ_MAX_TCC_OFFSET_OFFSET (24)
//#define B_MSR_PLATFORM_INFO_PRG_TJ_OFFSET_EN_MASK BIT30

#define N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_STATUS_OFFSET                 0
#define V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_STATUS_MASK                   0x000000000000FFFF
#define N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_DATA_OFFSET                   16
#define V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_DATA_MASK                     0x000000000000FFFF
#define N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_TERMINAL_OFFSET               32
#define V_MSR_PLAT_FRMW_PROT_TRIG_PARAM_TERMINAL_MASK                 0x000000000000FFFF
#define B_MSR_PLAT_FRMW_PROT_TRIG_PARAM_SE                            BIT62
#define N_MSR_PLAT_FRMW_PROT_TRIG_PARAM_SE_OFFSET                     62

///
/// Other defines
///

#ifndef TRIGGER_MODE_EDGE
#define TRIGGER_MODE_EDGE             0x00
#endif
#ifndef TRIGGER_MODE_LEVEL
#define TRIGGER_MODE_LEVEL            0x01
#endif

#ifndef CPU_FEATURE_DISABLE
#define CPU_FEATURE_DISABLE  0
#endif
#ifndef CPU_FEATURE_ENABLE
#define CPU_FEATURE_ENABLE   1
#endif

#define CACHE_UNCACHEABLE               0
#define CACHE_WRITECOMBINING            1
#define CACHE_WRITETHROUGH              4
#define CACHE_WRITEPROTECTED            5
#define CACHE_WRITEBACK                 6

#define V_MSR_PRMRR_MASK                                              0x0000007FFFFFFFFF
#define V_MAXIMUM_VARIABLE_MTRR_NUMBER                                10

#define TXT_PUBLIC_BASE                                               0xFED30000
#define R_CPU_BOOT_GUARD_ERRORCODE                                    0x30
#define R_CPU_BOOT_GUARD_BOOTSTATUS                                   0xA0
#define R_CPU_BOOT_GUARD_ACM_STATUS                                   0x328
#define R_CPU_ACM_POLICY_STATUS                                       0x378
#define MMIO_ACM_POLICY_STATUS                                        (TXT_PUBLIC_BASE + R_CPU_ACM_POLICY_STATUS)
#define B_CPU_BOOT_GUARD_ACM_STATUS_DCD                               BIT21
#define V_CPU_BOOT_GUARD_LOAD_ACM_SUCCESS                             0x8000000000000000
#define B_BOOT_GUARD_ACM_ERRORCODE_MASK                               0x00007FF0
#define B_CPU_BOOT_GUARD_BOOTSTATUS_BLOCK_BOOT_ENABLED                BIT0
#define V_CPU_BOOT_GUARD_BOOTSTATUS_BLOCK_BOOT_ENABLED                0x01
#define R_CPU_BOOT_GUARD_NEM_MAP_STRUCTURE_ADDRESS                    0x320
#define R_CPU_BOOT_GUARD_ACM_STATUS_POLICY                            0x728
#define B_CPU_BOOT_GUARD_ACM_STATUS_POLICY_BOOT_MODE                  BIT8

//
// Processor Definitions
//
#define CPUID_FULL_STEPPING                        0x0000000F
#define CPUID_FULL_FAMILY_MODEL                    0x0FFF0FF0
#define CPUID_FULL_FAMILY_MODEL_STEPPING           0x0FFF0FFF
#define CPUID_FULL_FAMILY_MODEL_COFFEELAKE_ULT_ULX 0x000806E0
#define CPUID_FULL_FAMILY_MODEL_ICELAKE_ULT_ULX    0x000706E0
#define CPUID_FULL_FAMILY_MODEL_ICELAKE_DT_HALO_R  0x000906F0
#define CPUID_FULL_FAMILY_MODEL_ICELAKE_DT_HALO    0x000706D0
#define CPUID_FULL_FAMILY_MODEL_ICELAKE_DT         0x000706D0
#define CPUID_FULL_FAMILY_MODEL_ICELAKE_AIPG       0x000906D0
#define CPUID_FULL_FAMILY_MODEL_ELKHARTLAKE        0x00090660
#define CPUID_FULL_FAMILY_MODEL_JASPERLAKE         0x000906C0
#define CPUID_FULL_FAMILY_MODEL_TIGERLAKE_ULT_ULX  0x000806C0
#define CPUID_FULL_FAMILY_MODEL_TIGERLAKE_DT_HALO  0x000806D0

#ifndef STALL_ONE_MICRO_SECOND
#define STALL_ONE_MICRO_SECOND 1
#endif
#ifndef STALL_ONE_MILLI_SECOND
#define STALL_ONE_MILLI_SECOND 1000
#endif

#define BITS(x) (1 << (x))

/**
Notes :
  1.  Bit position always starts at 0.
  2.  Following macros are applicable only for Word aligned integers.
**/
#define BIT(Pos, Value)               (1 << (Pos) & (Value))
#define BITRANGE(From, Width, Value)  (((Value) >> (From)) & ((1 << (Width)) - 1))

///
/// Enums for CPU Family IDs
///
typedef enum {
  EnumCpuCflUltUlx    = CPUID_FULL_FAMILY_MODEL_COFFEELAKE_ULT_ULX,
  EnumCpuIclUltUlx    = CPUID_FULL_FAMILY_MODEL_ICELAKE_ULT_ULX,
  EnumCpuIclDtHaloR   = CPUID_FULL_FAMILY_MODEL_ICELAKE_DT_HALO_R,
  EnumCpuIclDtHalo    = CPUID_FULL_FAMILY_MODEL_ICELAKE_DT_HALO,
  EnumCpuIclDt        = CPUID_FULL_FAMILY_MODEL_ICELAKE_DT,
  EnumCpuIclAipg      = CPUID_FULL_FAMILY_MODEL_ICELAKE_AIPG,
  EnumCpuJsl          = CPUID_FULL_FAMILY_MODEL_JASPERLAKE,
  EnumCpuEhl          = CPUID_FULL_FAMILY_MODEL_ELKHARTLAKE,
  EnumCpuTglUltUlx    = CPUID_FULL_FAMILY_MODEL_TIGERLAKE_ULT_ULX,
  EnumCpuTglDtHalo    = CPUID_FULL_FAMILY_MODEL_TIGERLAKE_DT_HALO,
  EnumCpuMax          = CPUID_FULL_FAMILY_MODEL
} CPU_FAMILY;

///
/// Enums for CPU Stepping IDs
///
typedef enum {
  /// Whiskey Lake ULT Steppings
  EnumCflW0         = 0xB,
  EnumCflV0         = 0xC,

  EnumCflMaxUltUlxStep = EnumCflW0,
  ///
  /// Icelake ULX/ULT Steppings
  ///
  EnumIclA0         = 0,
  EnumIclB0         = 1,
  EnumIclB4         = 2,
  EnumIclC0         = 3,
  EnumIclD0         = 4,
  EnumIclD1         = 5,


  ///
  /// Icelake DT/Halo Refresh Steppings
  ///
  EnumIclG0         = 0,
  EnumIclH0         = 1,

  ///
  /// Icelake DT/Halo Steppings
  ///
  EnumIclP0         = 1,
  EnumIclQ0         = 2,
  ///
  /// Icelake DT Steppings
  ///
  EnumIclS0         = 1,

  ///
  /// Icelake AIPG Steppings
  ///
  EnumIclI0         = 0,
  ///
  /// Elkhartlake Steppings
  ///
  EnumEhlA0 = 0,
  EnumEhlB0 = 1,
  ///
  ///
  /// Jasperlake Steppings
  ///
  EnumJslA0 = 0,
  ///
  /// Tigerlake ULX/ULT Steppings
  ///
  EnumTglA0 = 0,
  EnumTglB0 = 1,

  ///
  /// Tigerlake DT/Halo Steppings
  ///
  EnumTglP0 = 1,
  EnumTglQ0 = 2,

///
///

  ///
  /// Max Stepping
  ///
  EnumCpuSteppingMax  = CPUID_FULL_STEPPING
} CPU_STEPPING;

///
/// Enums for CPU SKU IDs
///
typedef enum {
  EnumCpuUlt        = 0,
  EnumCpuTrad,
  EnumCpuUlx,
  EnumCpuHalo,
  EnumCpuUnknown
} CPU_SKU;

///
/// Enums for CPU Generation
///
typedef enum {
  EnumCflCpu  = 0,
  EnumIclCpu,
  EnumTglCpu,
  EnumJslCpu,
  EnumEhlCpu,
  EnumRklCpu,
  EnumCpuUnknownGeneration = 255
} CPU_GENERATION;
#endif

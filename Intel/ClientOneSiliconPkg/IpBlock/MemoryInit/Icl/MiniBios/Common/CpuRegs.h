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
// CPU ID Instruction defines not in Register/Cpuid.h from UefiCpuPkg
//
#define CPUID_SGX_ENABLED                                             0x12

//
// MSR defines
//
#define MSR_IA32_BIOS_SIGN_ID                                         0x008B
#define MSR_IA32_MTRRCAP                                              0x000000FE
#define MSR_PRMRR_BASE_0                                              0x000002A0
#define B_MSR_PRMRR_BASE_0_CONFIGURED_MASK                            MRC_BIT3
#define MSR_PRMRR_MASK                                                0x000001F5
#define B_MSR_PRMRR_MASK_L_MASK                                       MRC_BIT10
#define MSR_PRMRR_VALID_CONFIG                                        0x000001FB
#define MSR_POWER_CTL1                                                0x000001FC
#define PRMRR_MAX_SIZE                                                0x10000000
#define B_MSR_PRMRR_PHYS_MASK_LOCK                                    MRC_BIT10
#define B_MSR_PRMRR_VALID_BIT                                         MRC_BIT11
#define V_MSR_PRMRR_MASK                                              0x0000007FFFFFFFFF

#define V_MAXIMUM_VARIABLE_MTRR_NUMBER                                10
#define V_FIXED_MTRR_NUMBER                                           11

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
#define CPUID_FULL_FAMILY_MODEL_CANNONLAKE_ULT_ULX  0x00060660
#define CPUID_FULL_FAMILY_MODEL_CANNONLAKE_DT_HALO  0x00060670
#define CPUID_FULL_FAMILY_MODEL_ICELAKE_ULT_ULX     0x000706E0
#define CPUID_FULL_FAMILY_MODEL_ICELAKE_DT_HALO_R   0x000906F0
#define CPUID_FULL_FAMILY_MODEL_ICELAKE_DT_HALO     0x000706D0
#define CPUID_FULL_FAMILY_MODEL_ELKHARTLAKE         0x00090660

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

typedef enum {
  /// Icelake ULX/ULT Steppings
  EnumIclA0         = 0,
  EnumIclB0         = 1,
  EnumIclB4         = 2,
  EnumIclC0         = 3,
  EnumIclD0         = 4,
  EnumIclD1         = 5,

  /// Icelake DT/Halo Steppings
  EnumIclP0         = 0,
  EnumIclQ0         = 1,
///
///

  /// Icelake DT/Halo Refresh Steppings
  EnumIclG0         = 0,
  EnumIclH0         = 1,
  /// Elkhartlake Steppings
  EnumEhlA0         = 0,
  EnumEhlB0         = 1,

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


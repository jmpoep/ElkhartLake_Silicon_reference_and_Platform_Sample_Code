/** @file

  Include the the general MRC types

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
#ifndef _MRC_TYPES_H_
#define _MRC_TYPES_H_

#ifdef MRC_MINIBIOS_BUILD
#include "MrcMiniBiosEfiDefs.h"
#else
#include <Base.h>
#endif // MRC_MINIBIOS_BUILD

//
// Data Types
//
#ifndef UINT64_STRUCT_T
#define UINT64_STRUCT_T
typedef union {
  struct {
    UINT32  Low;
    UINT32  High;
  } Data32;
  UINT64 Data;
} UINT64_STRUCT;
#endif // UINT64_STRUCT_T


typedef union {
  struct {
    INT32  Low;
    INT32  High;
  } Data32;
  INT64 Data;
} INT64_STRUCT;

typedef union {
  VOID    *Ptr;
  UINTN   DataN;
  UINT64  Data64;
} POINTER_STRUCT;

#define UNSUPPORT 0
#define SUPPORT   1

typedef enum {
  mrcSuccess,
  mrcFail,
  mrcWrongInputParameter,
  mrcCasError,
  mrcTimingError,
  mrcSenseAmpErr,
  mrcReadMPRErr,
  mrcReadLevelingError,
  mrcWriteLevelingError,
  mrcDataTimeCentering1DErr,
  mrcWriteVoltage2DError,
  mrcReadVoltage2DError,
  mrcMiscTrainingError,
  mrcWrError,
  mrcDimmNotSupport,
  mrcChannelNotSupport,
  mrcPiSettingError,
  mrcDqsPiSettingError,
  mrcDeviceBusy,
  mrcFrequencyChange,
  mrcReutSequenceError,
  mrcCrcError,
  mrcFrequencyError,
  mrcDimmNotExist,
  mrcColdBootRequired,
  mrcRoundTripLatencyError,
  mrcMixedDimmSystem,
  mrcAliasDetected,
  mrcRetrain,
  mrcRtpError,
  mrcUnsupportedTechnology,
  mrcMappingError,
  mrcSocketNotSupported,
  mrcControllerNotSupported,
  mrcRankNotSupported,
  mrcParamSaturation,
  mrcComplexParamDone,
  mrcInstanceDoesNotExist,
  mrcStatusMax
} MrcStatus;

//
// general  macros
//
#ifndef MIN
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef ABS
#define ABS(x)  (((x) < 0) ? (-(x)) : (x))
#endif

//
// Make sure x is inside the range of [a..b]
//
#ifndef RANGE
#define RANGE(x, a, b) (MIN ((b), MAX ((x), (a))))
#endif

#ifndef DIVIDECEIL
#define DIVIDECEIL(a, b)   (((a) + (b) - 1) / (b))
#endif

#ifndef DIVIDEROUND
#define DIVIDEROUND(a, b)  (((a) * (b) > 0) ? ((a) + (b) / 2) / (b) : ((a) - (b) / 2) / (b))
#endif

// Use to make slightly smaller code when only working with unsigned numbers.
#ifndef UDIVIDEROUND
#define UDIVIDEROUND(a, b)  (((a) + (b) / 2) / (b))
#endif

#ifndef DIVIDEFLOOR
#define DIVIDEFLOOR(a, b)  ((a) / (b))
#endif

// @todo remove SUB_CH_MASK_CHECK, it's deprecated
#ifndef SUB_CH_MASK_CHECK
#define SUB_CH_MASK_CHECK(Mask, Channel, SubChannel) ((Mask) & (1 << ((Channel) * MAX_SUB_CHANNEL + (SubChannel))))
#endif

#ifndef MC_CH_IDX
#define MC_CH_IDX(Mc, Ch, MaxCh) ((Mc) * (MaxCh) + (Ch))
#endif

/// This define checks if this specific channel and controller is set in the BitMask.
/// It will return the & result of the operation.
#ifndef MC_CH_MASK_CHECK
#define MC_CH_MASK_CHECK(Mask, Mc, Ch, MaxCh) ((Mask) & (1 << MC_CH_IDX ((Mc), (Ch), (MaxCh))))
#endif
// Number of elements in a 1D array
#ifndef ARRAY_COUNT
#define ARRAY_COUNT(a) (sizeof (a) / sizeof (a[0]))
#endif
// Number of elements in a 2D array
#ifndef ARRAY_COUNT2D
#define ARRAY_COUNT2D(a) (sizeof (a) / sizeof (a[0][0]))
#endif
// Macros to define all [Controller/Channel/SubChannel/Rank] bits in the mask
#ifndef ALL_CONTROLLER_MASK
#define ALL_CONTROLLER_MASK ((1 << MAX_CONTROLLER) - 1)
#endif

#ifndef ALL_CHANNEL_MASK
#define ALL_CHANNEL_MASK ((1 << MAX_CHANNEL) - 1)
#endif

#ifndef ALL_SUB_CH_MASK
#define ALL_SUB_CH_MASK ((1 << MAX_SUB_CHANNEL) - 1)
#endif

#ifndef ALL_RANK_MASK
#define ALL_RANK_MASK  ((1 << MAX_RANK_IN_CHANNEL) - 1)
#endif

#if _MSC_EXTENSIONS
//
// Disable warning that make it impossible to compile at /W4
// This only works for Microsoft* tools
//
//
// Disabling bitfield type checking warnings.
//
#pragma warning (disable : 4214)
//
// Unreferenced formal parameter - We are object oriented, so we pass parameters even
//  if we don't need them.
//
#pragma warning (disable : 4100)
//
// ASSERT(FALSE) or while (TRUE) are legal constructs so supress this warning
//
#pragma warning(disable : 4127)
//
// The given function was selected for inline expansion, but the compiler did not perform the inlining.
//
#pragma warning(disable : 4710)

#endif // _MSC_EXTENSIONS
#define MRC_BIT0          0x00000001
#define MRC_BIT1          0x00000002
#define MRC_BIT2          0x00000004
#define MRC_BIT3          0x00000008
#define MRC_BIT4          0x00000010
#define MRC_BIT5          0x00000020
#define MRC_BIT6          0x00000040
#define MRC_BIT7          0x00000080
#define MRC_BIT8          0x00000100
#define MRC_BIT9          0x00000200
#define MRC_BIT10         0x00000400
#define MRC_BIT11         0x00000800
#define MRC_BIT12         0x00001000
#define MRC_BIT13         0x00002000
#define MRC_BIT14         0x00004000
#define MRC_BIT15         0x00008000
#define MRC_BIT16         0x00010000
#define MRC_BIT17         0x00020000
#define MRC_BIT18         0x00040000
#define MRC_BIT19         0x00080000
#define MRC_BIT20         0x00100000
#define MRC_BIT21         0x00200000
#define MRC_BIT22         0x00400000
#define MRC_BIT23         0x00800000
#define MRC_BIT24         0x01000000
#define MRC_BIT25         0x02000000
#define MRC_BIT26         0x04000000
#define MRC_BIT27         0x08000000
#define MRC_BIT28         0x10000000
#define MRC_BIT29         0x20000000
#define MRC_BIT30         0x40000000
#define MRC_BIT31         0x80000000
#define MRC_BIT32        0x100000000ULL
#define MRC_BIT33        0x200000000ULL
#define MRC_BIT34        0x400000000ULL
#define MRC_BIT35        0x800000000ULL
#define MRC_BIT36       0x1000000000ULL
#define MRC_BIT37       0x2000000000ULL
#define MRC_BIT38       0x4000000000ULL
#define MRC_BIT39       0x8000000000ULL
#define MRC_BIT40      0x10000000000ULL
#define MRC_BIT41      0x20000000000ULL
#define MRC_BIT42      0x40000000000ULL
#define MRC_BIT43      0x80000000000ULL
#define MRC_BIT44     0x100000000000ULL
#define MRC_BIT45     0x200000000000ULL
#define MRC_BIT46     0x400000000000ULL
#define MRC_BIT47     0x800000000000ULL
#define MRC_BIT48    0x1000000000000ULL
#define MRC_BIT49    0x2000000000000ULL
#define MRC_BIT50    0x4000000000000ULL
#define MRC_BIT51    0x8000000000000ULL
#define MRC_BIT52   0x10000000000000ULL
#define MRC_BIT53   0x20000000000000ULL
#define MRC_BIT54   0x40000000000000ULL
#define MRC_BIT55   0x80000000000000ULL
#define MRC_BIT56  0x100000000000000ULL
#define MRC_BIT57  0x200000000000000ULL
#define MRC_BIT58  0x400000000000000ULL
#define MRC_BIT59  0x800000000000000ULL
#define MRC_BIT60 0x1000000000000000ULL
#define MRC_BIT61 0x2000000000000000ULL
#define MRC_BIT62 0x4000000000000000ULL
#define MRC_BIT63 0x8000000000000000ULL

  #define MRC_DEADLOOP() { volatile int __iii; __iii = 1; while (__iii); }

#ifndef ASM
#define ASM __asm
#endif

///
/// Type Max/Min Values
///
#define MRC_INT32_MAX   (0x7FFFFFFF)
#define MRC_INT32_MIN   (0x80000000)
#define MRC_INT64_MAX   (0x7FFFFFFFFFFFFFFFLL)
#define MRC_INT64_MIN   (0x8000000000000000LL)
#define MRC_UINT8_MAX   (0xFF)
#define MRC_UINT16_MAX  (0xFFFF)
#define MRC_UINT32_MAX  (0xFFFFFFFF)
#define MRC_UINT64_MAX  (0xFFFFFFFFFFFFFFFFULL)
#define MRC_UINT_MIN    (0x0)

#define MRC_GET (1)
#define MRC_SET (0)
#define MRC_ENABLE  (1)
#define MRC_DISABLE (0)

#endif // _MRC_TYPES_H_


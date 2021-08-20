/** @file
  This file contains the memory operation related definitions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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
#ifndef _MemoryUtils_h_
#define _MemoryUtils_h_

#include <MrcTypes.h>

extern
void
SetMem(
  IN OUT UINT8 * const Dest,
  IN const UINT32      NumBytes,
  IN const UINT32      Value
  );

extern
void
CopyMem(
  IN OUT UINT8 * const   Dest,
  IN const UINT8 * const Src,
  IN const UINT32        NumBytes
  );

extern
UINT64
LShiftU64 (
  IN const UINT64 Data,
  IN const UINT32 Count
  );

extern
UINT64
RShiftU64 (
  IN const UINT64  Data,
  IN const UINT32  Count
  );

extern
UINT64
MultU64x32 (
  IN const UINT64  Multiplicand,
  IN const UINT32  Multiplier
  );

extern
UINT64
MrcDivideU64ByU64 (
  IN const UINT64  Dividend,
  IN const UINT64  Divisor
  );

extern
UINT64
DivU64x64Remainder (
  IN const UINT64 Dividend,
  IN const UINT64 Divisor,
  IN OUT UINT64 * Remainder
  );

extern
UINT64
AsmReadMsr64 (
  IN UINT32 Offset
  );

extern
void
AsmWriteMsr64 (
  IN UINT32  Index,
  IN UINT64  Value
  );

extern
UINT64
AsmReadTsc (
  void
  );

#endif // _MemoryUtils_h_

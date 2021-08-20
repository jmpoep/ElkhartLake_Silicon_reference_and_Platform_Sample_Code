/** @file
  This file contains the memory operation related functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#include <MrcTypes.h>
#include "MemoryUtils.h"

void
SetMem(
  IN OUT UINT8 * const Dest,
  IN const UINT32      NumBytes,
  IN const UINT32      Value
  )
/*++

Routine Description:

  Set byte sized memory locations to the specified value.

Arguments:

  Dest        - destination
  Value       - value to set
  NumBytes    - number of bytes to set

Returns:

  N/A

--*/
{
   ASM {
      pushf

      cld
      mov   edi, Dest
      mov   eax, Value
      mov   ecx, NumBytes
      rep   stosb

      popf
   }
   return;
}

void
CopyMem(
  IN OUT UINT8 * const   Dest,
  IN const UINT8 * const Src,
  IN const UINT32        NumBytes
  )
/*++

Routine Description:

  Copy memory byte for byte.

Arguments:

  Dest      - destination
  Src       - source
  NumBytes  - number of bytes to copy

Returns:

  N/A

--*/
{
  ASM {
    pushf

    cld
    mov   esi, Src
    mov   edi, Dest
    mov   ecx, NumBytes
    rep   movsb

    popf
  }
  return;
}

UINT64
LShiftU64 (
  IN const UINT64 Data,
  IN const UINT32 Count
  )
/*++

Routine Description:

  Shift left UINT64 number.

Arguments:

  Data  -         - UINT64 number to shift
  Count -         - number of bits to shift (0..63)

Returns:

  Returns the shifted UINT64 value.

--*/
{
  UINT32 Lower;
  UINT32 Upper;
  UINT32 RetData[2];

  ASM {
    mov     eax, dword ptr Data[0]
    mov     Lower, eax

    mov     eax, dword ptr Data[4]
    mov     Upper, eax

    mov     ecx, Count
    xor     eax, eax
    mov     edx, Lower
    test    cl, 32
    cmovz   eax, edx
    cmovz   edx, Upper
    shld    edx, eax, cl
    shl     eax, cl
    mov     RetData[0], eax
    mov     RetData[4], edx
  }
  return ((UINT64 *) RetData)[0];
}

UINT64
RShiftU64 (
  IN const UINT64  Data,
  IN const UINT32  Count
  )
/*++

Routine Description:

  Shift right UINT64 number.

Arguments:

  Data            - UINT64 number to shift
  Count           - number of bits to shift (0..63)

Returns:

  Returns the shifted UINT64 value.

--*/
{
  UINT32 Lower;
  UINT32 Upper;
  UINT32 RetData[2];

  ASM {
    mov     eax, dword ptr Data[0]
    mov     Lower, eax

    mov     eax, dword ptr Data[4]
    mov     Upper, eax

    mov     ecx, Count
    xor     eax, eax
    mov     edx, Upper
    test    cl,  32
    cmovz   eax, edx
    cmovz   edx, Lower
    shrd    edx, eax, cl
    shr     eax, cl
    mov     RetData[0], edx
    mov     RetData[4], eax
  }
  return ((UINT64 *) RetData)[0];
}

UINT64
MultU64x32 (
  IN const UINT64  Multiplicand,
  IN const UINT32  Multiplier
  )
/*++

Routine Description:

  Multiply UINT64 with a UINT32 number. Result is <= 64 bits

Arguments:

  Multiplicand    UINT64 number to be multiplied with
  Multiplier      UINT32 number to multiply

Returns:

  Returns the multiplication result UINT64 value.

--*/
{
  UINT32 TempUpper;
  UINT32 RetData[2];

  ASM {
    mov     eax, dword ptr Multiplicand[0]
    mul     Multiplier                   // saves value in edx:eax - most significant bits in edx

    mov     RetData[0], eax
    mov     TempUpper, edx

    mov     eax, dword ptr Multiplicand[4]
    mul     Multiplier                   // saves value in edx:eax - most significant bits in edx

    add     eax, TempUpper
    mov     RetData[4], eax
  }
  return ((UINT64 *) RetData)[0];
}

UINT64
MrcDivideU64ByU64 (
  IN const UINT64  Dividend,
  IN const UINT64  Divisor
  )
/*++

Routine Description:

  Divide UINT64 with a UINT64 number. Result is <= 64 bits

Arguments:

  Dividend  -     UINT64 number to be divided
  Divisor   -     UINT64 number to divide with

Returns:

  Returns the division quotient UINT64 value.

--*/
{
  UINT32 RetData[2];
  UINT32 Dividend64[2];
  UINT32 Divisor32;

  RetData[0]    = 0;
  RetData[1]    = 0;
  Dividend64[0] = 0;
  Dividend64[1] = 0;
  Divisor32     = 0;
  ASM {
    mov     edx, dword ptr Divisor[0]
    mov     Divisor32, edx
    mov     ecx, dword ptr Dividend[0]
    mov     Dividend64[0], ecx
    mov     ecx, dword ptr Dividend[4]
    mov     Dividend64[4], ecx
    mov     ecx, dword ptr Divisor[4]

    // check if we only div by 32bit
    cmp     ecx,0
    je      div64by32 // div 64by32

    // 64by64 div
    mov     ebx, ecx

    bsr     ecx,ebx
    inc     ecx
    mov     eax, Divisor32
    mov     edx, dword ptr Divisor[4]
    shrd    eax, edx, cl
    mov     Divisor32,eax

    mov     eax, Dividend64[0]
    mov     edx, Dividend64[4]

    shrd    eax, edx, cl
    mov     Dividend64[0],eax
    shr     edx,cl
    mov     Dividend64[4],edx

div64by32:
    // 64by32 fast div
    mov     eax, Dividend64[4]
    mov     ebx, Divisor32
    sub     edx, edx
    div     ebx
    mov     RetData[4], eax
    mov     eax, Dividend64[0]
    div     ebx
    mov     RetData[0], eax
  }
  return ((UINT64 *) RetData)[0];
}

UINT64
DivU64x64Remainder (
  IN const UINT64 Dividend,
  IN const UINT64 Divisor,
  IN OUT UINT64 * Remainder
)
/*++

Routine Description:

  Divide UINT64 with a UINT64 number. Result is <= 32 bits

Arguments:

  Dividend  - 64-bit number to be divided by divisor
  Divisor   - Divide 64-bit number by this 64-bit value.
  Remainder - Optional, remainder returned when not NULL.

Returns:

  Returns the quotient result of UINT32 value.

--*/
{
  UINT32 RetData[2];
  UINT32 Dividend64[2];
  UINT32 Divisor32;
  UINT64_STRUCT Remain;
  UINT32 Rem[2];

  RetData[0]    = 0;
  RetData[1]    = 0;
  Dividend64[0] = 0;
  Dividend64[1] = 0;
  Divisor32     = 0;
  ASM {
    mov     edx, dword ptr Divisor[0]
    mov     Divisor32, edx
    mov     ecx, dword ptr Dividend[0]
    mov     Dividend64[0], ecx
    mov     ecx, dword ptr Dividend[4]
    mov     Dividend64[4], ecx
    mov     ecx, dword ptr Divisor[4]

    // check if we only div by 32bit
    cmp     ecx, 0
    je      div64by32 // div 64by32

    // 64by64 div
    mov     ebx, ecx

    bsr     ecx, ebx
    inc     ecx
    mov     eax, Divisor32
    mov     edx, dword ptr Divisor[4]
    shrd    eax, edx, cl
    mov     Divisor32, eax

    mov     eax, Dividend64[0]
    mov     edx, Dividend64[4]

    shrd    eax, edx, cl
    mov     Dividend64[0], eax
    shr     edx, cl
    mov     Dividend64[4], edx

div64by32:
    // 64by32 fast div
    mov     eax, Dividend64[4]
    mov     ebx, Divisor32
    sub     edx, edx
    div     ebx
    mov     Rem[1], edx
    mov     RetData[4], eax
    mov     eax, Dividend64[0]
    div     ebx
    mov     Rem[0], edx
    mov     RetData[0], eax
  }
  if (Remainder != NULL) {
    Remain.Data32.Low  = Rem[0];
    Remain.Data32.High = Rem[1];
    *Remainder         = Remain.Data;
  }
  return ((UINT64 *) RetData)[0];
}

UINT64
AsmReadMsr64 (
  IN UINT32 Address
  )
/*++

Routine Description:

  Gets the 64-bit MSR value.

Arguments:

  Address - MSR address

Returns:

  The 64-bit value

--*/
{
  UINT64 MsrValue;

  ASM {
    mov   ecx, Address
    rdmsr
    mov dword ptr MsrValue[0], eax
    mov dword ptr MsrValue[4], edx
  }
  return MsrValue;
}

void
AsmWriteMsr64 (
  IN UINT32  Index,
  IN UINT64  Value
  )
{
#if defined __GNUC__  // GCC compiler
  __asm__ __volatile__ (
    "wrmsr"
    :
    : "c" (Index),
      "A" (Value)
    );
#else // MSFT compiler
  _asm {
    mov     edx, dword ptr [Value + 4]
    mov     eax, dword ptr [Value + 0]
    mov     ecx, Index
    wrmsr
  }
#endif
}

UINT64
AsmReadTsc (
  void
  )
/*++

Routine Description:

  Gets the 64-bit CPU timestamp value.

Arguments:

  None.

Returns:

  The 64-bit CPU timestamp value.

--*/
{
  UINT64 TscValue;

  ASM {
    rdtsc
    mov dword ptr TscValue[0], eax
    mov dword ptr TscValue[4], edx
  }
  return TscValue;
}

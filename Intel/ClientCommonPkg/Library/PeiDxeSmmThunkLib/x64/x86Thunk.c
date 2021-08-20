/** @file
  Real Mode Thunk Functions for IA32 and X64

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>

#include <Library/ThunkLib.h>
#define _THUNK_INTERRUPT  0x10000

extern const UINTN mCode16Size;

extern
IA32_REGISTER_SET *
EFIAPI
_Thunk16 (
  IN OUT IA32_REGISTER_SET *RegisterSet,
  IN UINT32                ThunkFlags,
  IN UINT32                RealModeCs
  );

extern
VOID
EFIAPI
_Code16Addr (
  VOID
  );

extern
void
EFIAPI
AsmFxRestore (
  IN CONST IA32_FX_BUFFER *Buffer
  );

extern
void
EFIAPI
AsmFxSave (
  OUT IA32_FX_BUFFER *Buffer
  );

/**
  Returns the properties of this real mode thunk implementation. Currently
  there are 2 properties has been defined, the minimum real mode buffer size
  and the minimum stack size.

  @param[in] MinimumStackSize  - The minimum size required for a 16-bit stack.

  @retval The minimum size of the real mode buffer needed by this thunk implementation
  @retval is returned.
**/
UINTN
EFIAPI
AsmThunk16GetProperties (
  OUT UINTN *MinimumStackSize
  )
{
  ///
  /// This size should be large enough to hold the register set as well as saved
  /// CPU contexts including GDTR, CR0 and CR4
  ///
  if (MinimumStackSize) {
    *MinimumStackSize = sizeof (IA32_REGISTER_SET) + 0x200;
  }

  return mCode16Size;
}

/**
  Tell this real mode thunk implementation the address and size of the real
  mode buffer needed.

  @param[in] ThunkContext    - The thunk context whose properties to set.
  @param[in] RealModeBuffer  - The address of the buffer allocated by caller. It should be
                    aligned on a 16-byte boundary.
                    This buffer must be in identity mapped pages.
  @param[in] BufferSize      - The size of RealModeBuffer. Must be larger than the minimum
                    size required as returned by R8AsmThunk16GetProperties().
**/
THUNK16_CONTEXT *
EFIAPI
AsmThunk16SetProperties (
  OUT THUNK16_CONTEXT *ThunkContext,
  IN VOID             *RealModeBuffer,
  IN UINTN            BufferSize
  )
{
  BufferSize &= (UINTN) ~3;

  ASSERT ((UINTN) RealModeBuffer < 0x100000);
  ASSERT (((UINTN) RealModeBuffer & 0xf) == 0);
  ASSERT (BufferSize >= mCode16Size);

  ThunkContext->RealModeBuffer  = (UINT32) (UINTN) RealModeBuffer;
  ThunkContext->DefaultStack    = (UINT32) (ThunkContext->RealModeBuffer + BufferSize);
  CopyMem (RealModeBuffer, (VOID *) (UINTN) _Code16Addr, mCode16Size);
  return ThunkContext;
}

/**
  Reset all internal states to their initial values. The caller should not
  release the real mode buffer until after a call to this function.

  @param[in] ThunkContext  - The thunk context to destroy.
**/
VOID
EFIAPI
AsmThunk16Destroy (
  IN OUT THUNK16_CONTEXT *ThunkContext
  )
{
  ThunkContext->RealModeBuffer = 0;
}

/**
  Do the 16-bit thunk code.

  NOTE: This function must be called on TPL_HIGH_LEVEL or with interrupts
        disabled because of GDTR and IDTR manipulations.
  This function must be placed in identity mapped pages.

  @param[in] ThunkContext  - Thunk context to use.
  @param[in] RegisterSet   - CPU registers would be set to the values contained in this
                  structure before making the far call. Then CPU registers are
                  copied back to this structure.
                  SS:ESP points to the real mode stack if THUNK_USER_STACK is
                  set on input, otherwise ignored.
                  EFlages is ignored on input.
                  On output, values of CS, EIP, SS and ESP should be ignored.
  @param[in] ThunkFlags    - 2 flags have currently been defined, THUNK_SAVE_FP_STATE and
                  THUNK_USER_STACK.
                  THUNK_SAVE_FP_STATE - FPU state would be saved/restored
                                        before/after calling real mode code.
                  THUNK_USER_STACK    - The stack specified by SS:ESP would be
                                        used instead of the default stack.

  @retval RegisterSet is returned.
**/
static
IA32_REGISTER_SET *
EFIAPI
x86AsmThunk16 (
  IN THUNK16_CONTEXT       *ThunkContext,
  IN OUT IA32_REGISTER_SET *RegisterSet,
  IN UINT32                ThunkFlags
  )
{
  IA32_FX_BUFFER *FpSavedState;
  UINT8          FpBuffer[sizeof (*FpSavedState) + 0x10];

  ASSERT (ThunkContext->RealModeBuffer != 0);
  ASSERT ((ThunkContext->RealModeBuffer & 0xf) == 0);

  FpSavedState = (IA32_FX_BUFFER *) (((UINTN) FpBuffer + 0xf) &~0xf);

  if (!(ThunkFlags & THUNK_USER_STACK)) {
    RegisterSet->E.ESP  = (UINT16) ThunkContext->DefaultStack;
    RegisterSet->E.SS   = (UINT16) ((ThunkContext->DefaultStack >> 4) & 0xf000);
  }

  if (ThunkFlags & THUNK_SAVE_FP_STATE) {
    AsmFxSave (FpSavedState);
  }

  ASSERT ((RegisterSet->E.ESP >> 16) == 0);

  CopyMem (
          RegisterSet,
          _Thunk16 (RegisterSet,
                    (UINT16) (ThunkFlags >> 16),
                    ThunkContext->RealModeBuffer >> 4),
          sizeof (*RegisterSet)
          );

  if (ThunkFlags & THUNK_SAVE_FP_STATE) {
    AsmFxRestore (FpSavedState);
  }

  return RegisterSet;
}

/**
  Make a far call to 16-bit code.

  NOTE: This function must be called on TPL_HIGH_LEVEL or with interrupts
        disabled because of GDTR and IDTR manipulations.
  This function must be placed in identity mapped pages.

  @param[in] ThunkContext  - Thunk context to use.
  @param[in] RegisterSet   - CPU registers would be set to the values contained in this
                  structure before making the far call. Then CPU registers are
                  copied back to this structure.
                  CS:EIP points to the real mode code being called on input.
                  SS:ESP points to the real mode stack if THUNK_USER_STACK is
                  set on input, otherwise ignored.
                  EFlages is ignored on input.
                  On output, values of CS, EIP, SS and ESP should be ignored.
  @param[in] Flags         - 2 flags have currently been defined, THUNK_SAVE_FP_STATE and
                  THUNK_USER_STACK.
                  THUNK_SAVE_FP_STATE - FPU state would be saved/restored
                                        before/after calling real mode code.
                  THUNK_USER_STACK    - The stack specified by SS:ESP would be
                                        used instead of the default stack.

  @retval RegisterSet is returned.
**/
IA32_REGISTER_SET *
EFIAPI
AsmThunk16FarCall86 (
  IN THUNK16_CONTEXT       *ThunkContext,
  IN OUT IA32_REGISTER_SET *RegisterSet,
  IN UINT32                Flags
  )
{
  return x86AsmThunk16 (ThunkContext, RegisterSet, Flags);
}

/**
  Invoke a 16-bit interrupt handler.

  NOTE: This function must be called on TPL_HIGH_LEVEL or with interrupts
        disabled because of GDTR and IDTR manipulations.
  This function must be placed in identity mapped pages.

  @param[in] ThunkContext  - Thunk context to use.
  @param[in] IntNumber     - The ordinal of the interrupt handler ranging from 0 to 255.
  @param[in] RegisterSet   - CPU registers would be set to the values contained in this
                  structure before making the far call. Then CPU registers are
                  copied back to this structure.
                  SS:ESP points to the real mode stack if THUNK_USER_STACK is
                  set on input, otherwise ignored.
                  EFlages is ignored on input.
                  On output, values of CS, EIP, SS and ESP should be ignored.
  @param[in] Flags         - 2 flags have currently been defined, THUNK_SAVE_FP_STATE and
                  THUNK_USER_STACK.
                  THUNK_SAVE_FP_STATE - FPU state would be saved/restored
                                        before/after calling real mode code.
                  THUNK_USER_STACK    - The stack specified by SS:ESP would be
                                        used instead of the default stack.

  @retval RegisterSet is returned.
**/
IA32_REGISTER_SET *
EFIAPI
AsmThunk16Int86 (
  IN THUNK16_CONTEXT       *ThunkContext,
  IN UINT8                 IntNumber,
  IN OUT IA32_REGISTER_SET *RegisterSet,
  IN UINT32                Flags
  )
{
  RegisterSet->E.Eip  = (UINT16) ((volatile UINT32 *) NULL)[IntNumber];
  RegisterSet->E.CS   = (UINT16) (((volatile UINT32 *) NULL)[IntNumber] >> 16);
  return x86AsmThunk16 (ThunkContext, RegisterSet, Flags | _THUNK_INTERRUPT);
}

/** @file
  Real Mode Thunk Functions for IA32 and X64

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2016 Intel Corporation.

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

#ifndef __THUNK_LIB__
#define __THUNK_LIB__

///
/// Byte packed structure for an 16-bit real mode thunks
///
typedef struct {
  UINT32 RealModeBuffer;
  UINT32 DefaultStack;
} THUNK16_CONTEXT;

//
// 16-bit thunking services
//
#define THUNK_SAVE_FP_STATE 0x1
#define THUNK_USER_STACK    0x2
#define THUNK_INTERRUPT     0x10000

//
// Function Prototypes
//
/**
  Returns the properties of this real mode thunk implementation. Currently
  there are 2 properties has been defined, the minimum real mode buffer size
  and the minimum stack size.

  @param[in] *MinimumStackSize  The minimum size required for a 16-bit stack.

  @retval The minimum size of the real mode buffer needed by this thunk implementation is returned.
**/
UINTN
EFIAPI
AsmThunk16GetProperties (
  OUT UINTN *MinimumStackSize OPTIONAL
  );

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
  );

/**
  Reset all internal states to their initial values. The caller should not
  release the real mode buffer until after a call to this function.

  @param[in] *ThunkContext  - The thunk context to destroy.
**/
VOID
EFIAPI
AsmThunk16Destroy (
  IN OUT THUNK16_CONTEXT *ThunkContext
  );

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
  @param[in] ThunkFlags    - 2 flags have currently been defined, THUNK_SAVE_FP_STATE and THUNK_USER_STACK.
                  THUNK_SAVE_FP_STATE - FPU state would be saved/restored before/after calling real mode code.
                  THUNK_USER_STACK    - The stack specified by SS:ESP would be used instead of the default stack.

  @retval RegisterSet is returned.
**/
IA32_REGISTER_SET *
EFIAPI
AsmThunk16FarCall86 (
  IN THUNK16_CONTEXT       *ThunkContext,
  IN OUT IA32_REGISTER_SET *RegisterSet,
  IN UINT32                ThunkFlags
  );

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
  @param[in] ThunkFlags    - 2 flags have currently been defined, THUNK_SAVE_FP_STATE and
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
  IN UINT32                ThunkFlags
  );

#endif

/** @file
  SMM CPU misc functions for x64 arch specific.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include "SmmCpuFeatures.h"

//
// Code select value
//
// BUGBUG: Need to figure out how to get these values from
// GDT produces by SMM module
//
#define PROTECT_MODE_CODE_SEGMENT          0x08
#define SMMSEG_PROTECT_MODE_CODE_SEGMENT   0x10
#define LONG_MODE_CODE_SEGMENT             0x38

#define EXCEPTION_VECTOR_NUMBER     0x20

//
// IA32_IDT_GATE_DESCRIPTOR is aliased here for X64 build benefit
//
typedef union {
  struct {
    UINT32  OffsetLow:16;   ///< Offset bits 15..0.
    UINT32  Selector:16;    ///< Selector.
    UINT32  Reserved_0:8;   ///< Reserved.
    UINT32  GateType:8;     ///< Gate Type.  See #defines above.
    UINT32  OffsetHigh:16;  ///< Offset bits 31..16.
  } Bits;
  UINT64  Uint64;
} SMM_PM_IA32_IDT_GATE_DESCRIPTOR;

UINTN                         mMceHandlerLongMode;
IA32_DESCRIPTOR               mSmiPMIdtr;
UINT32                        gProtModeIdtr = 0;
extern UINTN                  SmiPMExceptionEntryPoints;
extern UINT32                 gSmiExceptionCr3;

extern BOOLEAN                             gSmmFeatureCetSupported;
extern UINT32                              gSmmFeatureCetPl0Ssp;
extern UINT32                              gSmmFeatureCetInterruptSsp;
extern UINT32                              gSmmFeatureCetInterruptSspTable;

UINTN  mSmmFeatureInterruptSspTables;

/**
  Protected Mode IDT handler of machine check.
**/
VOID
EFIAPI
PMIdtHandlerMachineCheck (
  VOID
  );

/**
  Protected Mode IDT handler.
**/
VOID
EFIAPI
PMIdtHandler (
  VOID
  );

/**
  Initialize SMM Protected Mode IDT table.

  @param[in]  Cr3      CR3 value.
**/
VOID
InitProtectedModeIdt (
  IN UINT32  Cr3
  )
{
  UINTN                             Index;
  UINTN                             PmIdtSize;
  SMM_PM_IA32_IDT_GATE_DESCRIPTOR   *PmIdtEntry;
  UINTN                             InterruptHandler;
  IA32_IDT_GATE_DESCRIPTOR          *IdtEntry;

  if (gProtModeIdtr != 0) {
    return;
  }

  //
  // Patch CR3 for SMM Protected Mode
  //
  gSmiExceptionCr3 = (UINT32)(UINTN)Cr3;

  //
  // Allocate IDT table size
  //
  PmIdtSize = sizeof (SMM_PM_IA32_IDT_GATE_DESCRIPTOR) * (EXCEPT_IA32_MACHINE_CHECK + 1) * 2;
  mSmiPMIdtr.Base  = (UINTN) SmmFeatureAllocateCodePages (EFI_SIZE_TO_PAGES(PmIdtSize));
  ASSERT (mSmiPMIdtr.Base != 0);
  if (mSmiPMIdtr.Base == 0) {
    return;
  }

  ZeroMem ((VOID *)mSmiPMIdtr.Base, PmIdtSize);
  mSmiPMIdtr.Limit = (UINT16) PmIdtSize - 1;
  PmIdtEntry =  (SMM_PM_IA32_IDT_GATE_DESCRIPTOR *)(mSmiPMIdtr.Base);

  gProtModeIdtr = (UINT32)(UINTN)&mSmiPMIdtr;
  //
  // Set up IA32 IDT handler
  //
  for (Index = 0; Index < EXCEPTION_VECTOR_NUMBER; Index++) {
    if (Index == EXCEPT_IA32_MACHINE_CHECK) {
      InterruptHandler = (UINTN)PMIdtHandlerMachineCheck;
    } else {
      InterruptHandler = (UINTN)PMIdtHandler;
    }
    PmIdtEntry[Index].Bits.Selector   = PROTECT_MODE_CODE_SEGMENT;
    PmIdtEntry[Index].Bits.GateType   = IA32_IDT_GATE_TYPE_INTERRUPT_32;
    PmIdtEntry[Index].Bits.OffsetLow  = (UINT16) (0x0000FFFF & InterruptHandler);
    PmIdtEntry[Index].Bits.OffsetHigh = (UINT16) (0x0000FFFF & (InterruptHandler >> 16));
  }
  //
  // Set X64 MCA IDT handler at location 0x24&0x25 in IA32 IDT Table. In case, MCA issues
  // before X64 IDT table is loaded in long mode, this MCA IDT handler will be invoked.
  //
  IdtEntry  = (IA32_IDT_GATE_DESCRIPTOR *) mSmiPMIdtr.Base;
  IdtEntry += EXCEPT_IA32_MACHINE_CHECK;
  mMceHandlerLongMode = IdtEntry->Bits.OffsetLow + (((UINTN) IdtEntry->Bits.OffsetHigh)  << 16) +
                                    (((UINTN) IdtEntry->Bits.OffsetUpper) << 32);
  IdtEntry  = (IA32_IDT_GATE_DESCRIPTOR *) mSmiPMIdtr.Base;
  IdtEntry += EXCEPT_IA32_MACHINE_CHECK;
  IdtEntry->Bits.Selector       = LONG_MODE_CODE_SEGMENT;
  IdtEntry->Bits.OffsetLow      = (UINT16)mMceHandlerLongMode;
  IdtEntry->Bits.Reserved_0     = 0;
  IdtEntry->Bits.GateType       = IA32_IDT_GATE_TYPE_INTERRUPT_32;
  IdtEntry->Bits.OffsetHigh     = (UINT16)(mMceHandlerLongMode >> 16);
  IdtEntry->Bits.OffsetUpper    = (UINT32)(mMceHandlerLongMode >> 32);
  IdtEntry->Bits.Reserved_1     = 0;
}

/**
  This function initializes CPU Shadow Stack.

  @param[in]  CpuIndex    The processor index.
  @param[in]  ShadowStack A pointer to Shadow Stack.
**/
VOID
SmmCpuFeaturesInitShadowStack (
  IN UINTN   CpuIndex,
  IN VOID    *ShadowStack
  )
{
  UINTN       SmmShadowStackSize;
  UINT64      *InterruptSspTable;

  if (PcdGet32 (PcdControlFlowEnforcementPropertyMask) && gSmmFeatureCetSupported) {
    SmmShadowStackSize = EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (PcdGet32 (PcdCpuSmmShadowStackSize)));
    if (FeaturePcdGet (PcdCpuSmmStackGuard)) {
      SmmShadowStackSize += EFI_PAGES_TO_SIZE (2);
    }

    gSmmFeatureCetPl0Ssp = (UINT32)((UINTN)ShadowStack + SmmShadowStackSize - sizeof(UINT64));
    DEBUG ((DEBUG_INFO, "gSmmFeatureCetPl0Ssp - 0x%x\n", gSmmFeatureCetPl0Ssp));
    DEBUG ((DEBUG_INFO, "ShadowStack - 0x%x\n", ShadowStack));
    DEBUG ((DEBUG_INFO, "  SmmShadowStackSize - 0x%x\n", SmmShadowStackSize));
    if (FeaturePcdGet (PcdCpuSmmStackGuard)) {
      if (mSmmFeatureInterruptSspTables == 0) {
        mSmmFeatureInterruptSspTables = (UINTN)AllocateZeroPool(sizeof(UINT64) * 8 * PcdGet32 (PcdCpuMaxLogicalProcessorNumber));
        ASSERT (mSmmFeatureInterruptSspTables != 0);
        DEBUG ((DEBUG_INFO, "mSmmFeatureInterruptSspTables - 0x%x\n", mSmmFeatureInterruptSspTables));
      }
      gSmmFeatureCetInterruptSsp = (UINT32)((UINTN)ShadowStack + EFI_PAGES_TO_SIZE(1) - sizeof(UINT64));
      gSmmFeatureCetInterruptSspTable = (UINT32)(UINTN)(mSmmFeatureInterruptSspTables + sizeof(UINT64) * 8 * CpuIndex);
      InterruptSspTable = (UINT64 *)(UINTN)(gSmmFeatureCetInterruptSspTable);
      InterruptSspTable[1] = gSmmFeatureCetInterruptSsp;
    }
  }
}


/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file
  Provide legacy interrupt reverse thunk support.

  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#include <PiDxe.h>

#include <Protocol/LegacyInterruptHandler.h>
#include <Protocol/LegacyBiosReverseThunk.h>

#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/LegacyInterruptSupportLib.h>

#define NOP  0x90
#define OSP  0x66
#define VAL  0xFF

UINT8  mIntHandlerTemplate[] = {
  '$', 'F', 'I', 'X',             // NextVectorOffset/NextVectorSeg
  0xEB, 0x04,                     // jmp Start
  'R', 'F', 'I', 'X',             // ReverseThunkVectorOffset/ReverseThunkVectorSeg
// Start:
  NOP,  NOP,  NOP,  NOP,
  0x80, 0xFC, VAL,                // cmp     ah, 0xFF ; To be patched
  0x74, 0x05,                     // je      Func
  0x2E, 0xFF, 0x2E, 0x00, 0x00,   // jmp DWORD PTR cs:[OldIntHandler]
// Func:
  //0xEB, 0xFE,  // JMP $ ; DEBUG
  0x66, 0x68, 'H', 'F', 'I', 'X', // push <high part of address>
  0x66, 0x68, 'L', 'F', 'I', 'X', // push <low part of address>
  0x2E, 0xFF, 0x1E, 0x06, 0x00,   // call DWORD PTR cs:[ReverseThunk]
  0x83, 0xC4, 0x08,               // add sp, 8 ; drop parameter
  0xCF,                           // iret
};

typedef struct {
  UINT8   CompareInstruction[7];
  UINTN   Size;
} PATCH_COMPARE_TEMPLATE_STRUCT;

PATCH_COMPARE_TEMPLATE_STRUCT  mCompareTemplate[] = {
  // cmp al
  {{NOP,  NOP,  NOP,  NOP,  NOP,  0x3C, VAL}, sizeof(UINT8)},
  // cmp ah
  {{NOP,  NOP,  NOP,  NOP,  0x80, 0xFC, VAL}, sizeof(UINT8)},
  // cmp ax
  {{NOP,  NOP,  NOP,  NOP,  0x3D, VAL,  VAL}, sizeof(UINT16)},
  // cmp eax
  {{OSP,  NOP,  0x3D, VAL,  VAL,  VAL,  VAL}, sizeof(UINT32)},

  // cmp bl
  {{NOP,  NOP,  NOP,  NOP,  0x80, 0xFB, VAL}, sizeof(UINT8)},
  // cmp bh
  {{NOP,  NOP,  NOP,  NOP,  0x80, 0xFF, VAL}, sizeof(UINT8)},
  // cmp bx
  {{NOP,  NOP,  NOP,  0x81, 0xFB,  VAL, VAL}, sizeof(UINT16)},
  // cmp eax
  {{OSP,  0x81, 0xFB, VAL,  VAL,  VAL,  VAL}, sizeof(UINT32)},

  // cmp cl
  {{NOP,  NOP,  NOP,  NOP,  0x80, 0xF9, VAL}, sizeof(UINT8)},
  // cmp ch
  {{NOP,  NOP,  NOP,  NOP,  0x80, 0xFD, VAL}, sizeof(UINT8)},
  // cmp cx
  {{NOP,  NOP,  NOP,  0x81, 0xF9, VAL,  VAL}, sizeof(UINT16)},
  // cmp ecx
  {{OSP,  0x81, 0xF9, VAL,  VAL,  VAL,  VAL}, sizeof(UINT32)},

  // cmp dl
  {{NOP,  NOP,  NOP,  NOP,  0x80, 0xFA, VAL}, sizeof(UINT8)},
  // cmp dh
  {{NOP,  NOP,  NOP,  NOP,  0x80, 0xFE, VAL}, sizeof(UINT8)},
  // cmp dx
  {{NOP,  NOP,  NOP,  0x81, 0xFA, VAL,  VAL}, sizeof(UINT16)},
  // cmp edx
  {{OSP,  0x81, 0xFA, VAL,  VAL,  VAL,  VAL}, sizeof(UINT32)},
};

/**
  Install Legacy Interrupt with reverse thunk.

  @param IntNumber         The number of interrupt.
                           For exampel, TCG INT1A or VARIABLE INT15.
  @param RegValue          The register value as signature to compare.
                           For example, TCG INT1A is 0xBB (AH), VARIABLE INT15 is 0xFE (AH).
  @param RegType           The register value as signature to compare.
                           For example, TCG INT1A is AH (0xBB), VARIABLE INT15 is AH (0xFE).
  @param NativeEntrypoint  The native entrypoint of reverse thunk.

  @retval RETURN_SUCCESS              Legacy Interrupt with reverse thunk is installed.
**/
RETURN_STATUS
EFIAPI
InstallLegacyInterruptWithReverseThunk (
  IN UINT8                                          IntNumber,
  IN UINT32                                         RegValue,
  IN LEGACY_REGISTER_TYPE                           RegType,
  IN LEGACY_BIOS_REVERSE_THUNK_NATIVE_ENTRY_POINT   NativeEntrypoint
  )
{
  EFI_STATUS                            Status;
  LEGACY_BIOS_REVERSE_THUNK_PROTOCOL    *LegacyBiosReverseThunk;
  EFI_LEGACY_INTERRUPT_HANDLER_PROTOCOL *InterruptHandler;
  EFI_HANDLE                            Handle;
  UINT8                                 *Ptr;

  if ((UINT32)RegType >= LegacyRegisterMax) {
    ASSERT(FALSE);
    return EFI_INVALID_PARAMETER;
  }

  InterruptHandler = AllocatePool (sizeof(*InterruptHandler));
  ASSERT (InterruptHandler != NULL);

  InterruptHandler->Number = IntNumber;
  InterruptHandler->Handler = AllocateCopyPool (sizeof(mIntHandlerTemplate), (VOID *)mIntHandlerTemplate);
  ASSERT (InterruptHandler->Handler != NULL);
  InterruptHandler->Length = sizeof(mIntHandlerTemplate);
  ASSERT (*(UINT32 *) InterruptHandler->Handler == SIGNATURE_32 ('$', 'F', 'I', 'X'));

  // Patch compare
  CopyMem (
    (UINT8 *)InterruptHandler->Handler + 10,
    mCompareTemplate[RegType].CompareInstruction,
    sizeof(mCompareTemplate[RegType].CompareInstruction)
    );
  CopyMem (
    (UINT8 *)InterruptHandler->Handler + 10
      + sizeof(mCompareTemplate[RegType].CompareInstruction)
      - mCompareTemplate[RegType].Size,
    &RegValue,
    mCompareTemplate[RegType].Size
    );

  //
  // Patch reverse thunk
  //
  Status = gBS->LocateProtocol (&gLegacyBiosReverseThunkProtocolGuid, NULL, (VOID **) &LegacyBiosReverseThunk);
  ASSERT_EFI_ERROR (Status);

  for (Ptr = (UINT8 *)InterruptHandler->Handler;
       Ptr < (UINT8 *)InterruptHandler->Handler + InterruptHandler->Length;
       Ptr++) {
    if (*(UINT32 *)(Ptr) == SIGNATURE_32 ('R', 'F', 'I', 'X')) {
      *(UINT16 *)(Ptr) = LegacyBiosReverseThunk->ReverseThunkCallOffset;
      *(UINT16 *)(Ptr + 2) = LegacyBiosReverseThunk->ReverseThunkCallSegment;
    }
    if (*(UINT32 *)(Ptr) == SIGNATURE_32 ('L', 'F', 'I', 'X')) {
      *(UINT32 *)(Ptr) = (UINT32)(UINTN)NativeEntrypoint;
    }
    if (*(UINT32 *)(Ptr) == SIGNATURE_32 ('H', 'F', 'I', 'X')) {
      *(UINT32 *)(Ptr) = (UINT32)RShiftU64 ((UINTN)NativeEntrypoint, 32);
    }
  }

  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gEfiLegacyInterruptHandlerProtocolGuid,  InterruptHandler,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  return RETURN_SUCCESS;
}

//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  The Legacy BIOS Reverse Thunk Protocol is used by the 16bit BiosExtension
  code which can be plugged in both legacy BIOS and UEFI BIOS CSM.

  Thunk - A thunk is a transition from one processor mode to another. A Thunk
          is a transition from native EFI mode to 16-bit mode. A reverse thunk
          would be a transition from 16-bit mode to native EFI mode.

  Reverse Thunk Rule:
    1) Do not touch any UEFI services
         No RT
         No BS
         No protocol database
         No memory allocation
    2) Only have software logic code
         Access memory, IO, CPU/chipset register
         Trigger SMI

  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef _LEGACY_BIOS_REVERSE_THUNK_PROTOCOL_H_
#define _LEGACY_BIOS_REVERSE_THUNK_PROTOCOL_H_

#include <Protocol/LegacyBios.h>

#define LEGACY_BIOS_REVERSE_THUNK_PROTOCOL_GUID \
  { \
    0xa7b41da5, 0x6667, 0x43c0, { 0x8c, 0xc6, 0x67, 0x89, 0xa6, 0x5c, 0x76, 0x67 } \
  }

/**
  Native entrypoint for ReverseThunk call.

  The reverse thunk saves register set at entry, and restores them at exit.
  The native code may update them, and the update will be applied when reverse thunk return.

  This interface is called at runtime. Do not use any BS or RT services.
  Do not enable interrupt.

  @param RegSet  Register set context for reverse thunk call.
**/
typedef
VOID
(EFIAPI *LEGACY_BIOS_REVERSE_THUNK_NATIVE_ENTRY_POINT) (
  IN OUT EFI_IA32_REGISTER_SET                      *RegSet
  );

/**
  The reverse thunk far call format.

  There is no need to construct EFI_IA32_REGISTER_SET parameter.
  The reservse thunk will do it, and make sure GP registers are updated when return.

  @param  EntryPoint  native code entry point
**/
typedef
VOID
(EFIAPI *LEGACY_BIOS_REVERSE_THUNK_FAR_CALL) (
  IN EFI_PHYSICAL_ADDRESS               EntryPoint
  );

/**

  The reverse thunk producer should:
  1) prepare the 16bit reverse thunk generic code below 1M
  2) prepare environment switch context (GDT/IDT, CR3, ...)
  3) install reverse thunk protocol
  when in runtime, it will:
  1) save all registers in EFI_IA32_REGISTER_SET
  2) switch to native mode (32bit protected mode/64bit long mode)
  3) prepare parameter (native entrypoint and EFI_IA32_REGISTER_SET) in native stack
  4) call the native entrypoint
  5) switch back to 16bit mode
  6) restore all regsiteres in EFI_IA32_REGISTER_SET
  7) far return

  The reverse thunk consumer should:
  1) prepare the 16bit customized code below 1M
  2) patch the native entrypoint (64bit) and push to stack
  3) get reverse thunk protocol, patch the reverse thunk far call
  when in runtime, it will:
  1) push native entrypoint to stack
  2) far call to reverse thunk code
  3) balance stack after call

  ReverseThunkCallSegment - The segment of the reverse thunk call code.
  ReverseThunkCallOffset  - The offset of the reverse thunk call code.
**/
typedef struct {
  UINT16       ReverseThunkCallSegment;
  UINT16       ReverseThunkCallOffset;
} LEGACY_BIOS_REVERSE_THUNK_PROTOCOL;

extern EFI_GUID gLegacyBiosReverseThunkProtocolGuid;

#endif

//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
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

#ifndef __LEGACY_INTERRUPT_SUPPORT_LIB_H__
#define __LEGACY_INTERRUPT_SUPPORT_LIB_H__

#include <Protocol/LegacyBios.h>
#include <Protocol/LegacyBiosReverseThunk.h>

typedef enum {
  LegacyRegisterAL,
  LegacyRegisterAH,
  LegacyRegisterAX,
  LegacyRegisterEAX,
  LegacyRegisterBL,
  LegacyRegisterBH,
  LegacyRegisterBX,
  LegacyRegisterEBX,
  LegacyRegisterCL,
  LegacyRegisterCH,
  LegacyRegisterCX,
  LegacyRegisterECX,
  LegacyRegisterDL,
  LegacyRegisterDH,
  LegacyRegisterDX,
  LegacyRegisterEDX,
  LegacyRegisterMax,
} LEGACY_REGISTER_TYPE;

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
  );

/**
  Issue SWSMI with EFI_IA32_REGISTER_SET context.

  RegSet.H.AL is SwSmi number.

  @param RegSet  EFI_IA32_REGISTER_SET context.
**/
VOID
EFIAPI
IssueSwSmi (
  IN OUT EFI_IA32_REGISTER_SET *RegSet
  );

#endif

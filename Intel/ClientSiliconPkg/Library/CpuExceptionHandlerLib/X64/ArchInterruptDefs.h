/*++
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
--*/
/** @file
  X64 arch definition for CPU Exception Handler Library.

  Copyright (c) 2016, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef _ARCH_CPU_INTERRUPT_DEFS_H_
#define _ARCH_CPU_INTERRUPT_DEFS_H_

typedef struct {
  EFI_SYSTEM_CONTEXT_X64  SystemContext;
  BOOLEAN                 ExceptionDataFlag;
  UINTN                   OldIdtHandler;
} EXCEPTION_HANDLER_CONTEXT;

//
// Register Structure Definitions
//
typedef struct {
  EFI_STATUS_CODE_DATA      Header;
  EFI_SYSTEM_CONTEXT_X64    SystemContext;
} CPU_STATUS_CODE_TEMPLATE;

typedef struct {
  SPIN_LOCK   SpinLock;
  UINT32      ApicId;
  UINT32      Attribute;
  UINTN       ExceptonHandler;
  UINTN       OldSs;
  UINTN       OldSp;
  UINTN       OldFlags;
  UINTN       OldCs;
  UINTN       OldIp;
  UINTN       ExceptionData;
  UINT8       HookAfterStubHeaderCode[HOOKAFTER_STUB_SIZE];
} RESERVED_VECTORS_DATA;

#endif

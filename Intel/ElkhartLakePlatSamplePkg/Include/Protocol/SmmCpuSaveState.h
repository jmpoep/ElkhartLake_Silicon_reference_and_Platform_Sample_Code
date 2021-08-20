/** @file
  This file declares the SMM CPU Save State protocol, which provides the processor
  save-state information for IA-32 and Itanium processors.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification
  This Protocol is defined in Framework of EFI SMM Core Interface Spec
  Version 0.91.
**/

#ifndef _SMM_CPU_SAVE_STATE_H_
#define _SMM_CPU_SAVE_STATE_H_

#define EFI_SMM_CPU_SAVE_STATE_PROTOCOL_GUID \
  { \
    0x1413d458, 0x4e61, 0x9531, {0x1e, 0xf2, 0xfb, 0x89, 0x39, 0xa8, 0xa0, 0xea} \
  }

typedef struct _EFI_SMM_CPU_SAVE_STATE_PROTOCOL  EFI_SMM_CPU_SAVE_STATE_PROTOCOL;

#define EFI_SMM_MIN_REV_ID_x64  0x30006

#pragma pack (1)

///
/// CPU save-state strcuture for IA32 and X64.
///
/// This struct declaration does not exctly match the Framework SMM CIS 0.91 because the
/// union in the Framework SMM CIS 0.91 contains an unnamed union member that causes build
/// breaks on many compilers with high warning levels.  Instead, the UINT8 Reserved[0x200]
/// field has been moved into EFI_SMM_CPU_STATE32.  This maintains binary compatibility for
/// the layout and also maintains source comaptibility for access of all fields in this
/// union.
///
/// This struct declaration does not exctly match the Framework SMM CIS 0.91 because
/// the Framework SMM CIS 0.91 uses ASM_XXX for base types in this structure.  These
/// have been changed to use the base types defined in the UEFI Specification.
///
typedef struct {
  UINT8   Reserved[0x200];
  UINT8   Reserved1[0xf8];  // fe00h
  UINT32  SMBASE;           // fef8h
  UINT32  SMMRevId;         // fefch
  UINT16  IORestart;        // ff00h
  UINT16  AutoHALTRestart;  // ff02h
  UINT32  IEDBASE;          // ff04h
  UINT8   Reserved2[0x98];  // ff08h
  UINT32  IOMemAddr;        // ffa0h
  UINT32  IOMisc;           // ffa4h
  UINT32  _ES;
  UINT32  _CS;
  UINT32  _SS;
  UINT32  _DS;
  UINT32  _FS;
  UINT32  _GS;
  UINT32  _LDTBase;
  UINT32  _TR;
  UINT32  _DR7;
  UINT32  _DR6;
  UINT32  _EAX;
  UINT32  _ECX;
  UINT32  _EDX;
  UINT32  _EBX;
  UINT32  _ESP;
  UINT32  _EBP;
  UINT32  _ESI;
  UINT32  _EDI;
  UINT32  _EIP;
  UINT32  _EFLAGS;
  UINT32  _CR3;
  UINT32  _CR0;
} EFI_SMM_CPU_STATE32;

///
/// This struct declaration does not exctly match the Framework SMM CIS 0.91 because
/// the Framework SMM CIS 0.91 uses ASM_XXX for base types in this structure.  These
/// have been changed to use the base types defined in the UEFI Specification.
///
typedef struct {
  UINT8   Reserved1[0x1d0];  // fc00h
  UINT32  GdtBaseHiDword;    // fdd0h
  UINT32  LdtBaseHiDword;    // fdd4h
  UINT32  IdtBaseHiDword;    // fdd8h
  UINT8   Reserved2[0xc];    // fddch
  UINT64  IO_EIP;            // fde8h
  UINT8   Reserved3[0x50];   // fdf0h
  UINT32  _CR4;              // fe40h
  UINT8   Reserved4[0x48];   // fe44h
  UINT32  GdtBaseLoDword;    // fe8ch
  UINT32  GdtLimit;          // fe90h
  UINT32  IdtBaseLoDword;    // fe94h
  UINT32  IdtLimit;          // fe98h
  UINT32  LdtBaseLoDword;    // fe9ch
  UINT32  LdtLimit;          // fea0h
  UINT32  LdtInfo;           // fea4h
  UINT8   Reserved5[0x50];   // fea8h
  UINT32  SMBASE;            // fef8h
  UINT32  SMMRevId;          // fefch
  UINT16  AutoHALTRestart;   // ff00h
  UINT16  IORestart;         // ff02h
  UINT32  IEDBASE;           // ff04h
  UINT8   Reserved6[0x14];   // ff08h
  UINT64  _R15;              // ff1ch
  UINT64  _R14;
  UINT64  _R13;
  UINT64  _R12;
  UINT64  _R11;
  UINT64  _R10;
  UINT64  _R9;
  UINT64  _R8;
  UINT64  _RAX;              // ff5ch
  UINT64  _RCX;
  UINT64  _RDX;
  UINT64  _RBX;
  UINT64  _RSP;
  UINT64  _RBP;
  UINT64  _RSI;
  UINT64  _RDI;
  UINT64  IOMemAddr;         // ff9ch
  UINT32  IOMisc;            // ffa4h
  UINT32  _ES;               // ffa8h
  UINT32  _CS;
  UINT32  _SS;
  UINT32  _DS;
  UINT32  _FS;
  UINT32  _GS;
  UINT32  _LDTR;             // ffc0h
  UINT32  _TR;
  UINT64  _DR7;              // ffc8h
  UINT64  _DR6;
  UINT64  _RIP;              // ffd8h
  UINT64  IA32_EFER;         // ffe0h
  UINT64  _RFLAGS;           // ffe8h
  UINT64  _CR3;              // fff0h
  UINT64  _CR0;              // fff8h
} EFI_SMM_CPU_STATE64;

///
/// Union of CPU save-state strcutures for IA32 and X64.
///
/// This union declaration does not exctly match the Framework SMM CIS 0.91 because the
/// union in the Framework SMM CIS 0.91 contains an unnamed union member that causes build
/// breaks on many compilers with high warning levels.  Instead, the UINT8 Reserved[0x200]
/// field has been moved into EFI_SMM_CPU_STATE32.  This maintains binary compatibility for
/// the layout and also maintains source comaptibility for access of all fields in this
/// union.
///
typedef union  {
  EFI_SMM_CPU_STATE32  x86;
  EFI_SMM_CPU_STATE64  x64;
} EFI_SMM_CPU_STATE;

#pragma pack ()

///
/// Provides a programatic means to access SMM save state.
///
struct _EFI_SMM_CPU_SAVE_STATE_PROTOCOL {
  ///
  /// Reference to a list of save states.
  ///
  EFI_SMM_CPU_STATE  **CpuSaveState;
};

#endif

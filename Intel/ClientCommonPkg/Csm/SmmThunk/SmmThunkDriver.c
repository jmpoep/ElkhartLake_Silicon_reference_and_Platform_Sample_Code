/** @file
SMM Thunk Driver

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/
#include "SmmThunkDriver.h"
///
/// Global variables
///

GLOBAL_REMOVE_IF_UNREFERENCED SMM_THUNK_PRIVATE_DATA mPrivateData = {
  EFI_SMM_THUNK_SIGNATURE,
  NULL,
  {
    SmmFarCall86,
    SmmIntCall86
  },
  {0, 0},
  0,
  0
};

///
/// EFI_DRIVER_ENTRY_POINT (InitializeSmmThunkProtocol)
///
/**
  Initializes the SMM Thunk Driver

  @param[in] ImageHandle - Handle for the image of this driver
  @param[in] SystemTable - Pointer to the EFI System Table

  @retval EFI_SUCCESS - SMM thunk driver has been initialized successfully
  @retval Other       - SMM thunk driver init failed
**/
EFI_STATUS
EFIAPI
InitializeSmmThunkProtocol (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS Status;
  UINTN      AddressBelow1M;

  mPrivateData.RealModeBuffer = (UINT64) (-1);
  Status = gSmst->SmmAllocatePages (
                  AllocateMaxAddress,
                  EfiRuntimeServicesData,
                  EFI_SIZE_TO_PAGES (LOW_STACK_SIZE),
                  &mPrivateData.RealModeBuffer
                  );
  ASSERT_EFI_ERROR (Status);
    ///
    ///  Reserved any space in SMM instead of the address below 1M
    ///  since no A, B segment available in SMM, this space will stored the data
    ///  copyied from space below 1M
    ///  this space could be modified by specific platform design
    ///
  AddressBelow1M = (UINTN) ((0x100000 - LOW_STACK_SIZE - 16) &~0xf);
  CopyMem ((VOID *) (UINTN) mPrivateData.RealModeBuffer, (VOID *) AddressBelow1M, LOW_STACK_SIZE);

  ///
  /// Get the real mode thunk implementation the address and size of the real
  /// mode buffer needed.
  ///
  mPrivateData.BufferSize = EFI_PAGE_SIZE;
  AsmThunk16SetProperties (
          &mPrivateData.ThunkContext,
          (VOID *) (UINTN) AddressBelow1M,
          mPrivateData.BufferSize
          );
  Status = gSmst->SmmInstallProtocolInterface (
                    &mPrivateData.Handle,
                    &gSmmThunkProtocolGuid,
                    EFI_NATIVE_INTERFACE,
                    &mPrivateData.SmmThunk
                    );
  ASSERT_EFI_ERROR (Status);
  return EFI_SUCCESS;
}

/**
  Convert EFI_IA32_REGISTER_SET to IA32_REGISTER_SET

    @param[in] Regs       - Register context passed into (and returned) from thunk to
                16-bit mode
    @param[in] Register  - Register context will be used in Thunk16Lib
**/
VOID
ConvertRegister (
  IN EFI_IA32_REGISTER_SET *Regs,
  OUT IA32_REGISTER_SET    *Register
  )
{
  Register->E.EDI = Regs->E.EDI;
  Register->E.ESI = Regs->E.ESI;
  Register->E.EBP = Regs->E.EBP;
  Register->E.ESP = Regs->E.ESP;
  Register->E.EBX = Regs->E.EBX;
  Register->E.EDX = Regs->E.EDX;
  Register->E.ECX = Regs->E.ECX;
  Register->E.EAX = Regs->E.EAX;
  Register->E.DS  = Regs->E.DS;
  Register->E.ES  = Regs->E.ES;
  Register->E.FS  = Regs->E.FS;
  Register->E.GS  = Regs->E.GS;
  Register->E.CS  = Regs->E.CS;
  Register->E.SS  = Regs->E.SS;
  CopyMem (&Register->E.EFLAGS, &Regs->E.EFlags, sizeof (UINT32));

  return;
}

/**
  Convert IA32_REGISTER_SET to EFI_IA32_REGISTER_SET

    @param[in] Regs      - Register context used in Thunk16Lib
    @param[in] Register  - Register context passed into (and returned) from thunk to 16-bit mode
**/
VOID
ConvertRegisterRet (
  IN IA32_REGISTER_SET      *Regs,
  OUT EFI_IA32_REGISTER_SET *Register
  )
{
  Register->E.EDI = Regs->E.EDI;
  Register->E.ESI = Regs->E.ESI;
  Register->E.EBP = Regs->E.EBP;
  Register->E.ESP = Regs->E.ESP;
  Register->E.EBX = Regs->E.EBX;
  Register->E.EDX = Regs->E.EDX;
  Register->E.ECX = Regs->E.ECX;
  Register->E.EAX = Regs->E.EAX;
  Register->E.DS  = Regs->E.DS;
  Register->E.ES  = Regs->E.ES;
  Register->E.FS  = Regs->E.FS;
  Register->E.GS  = Regs->E.GS;
  Register->E.CS  = Regs->E.CS;
  Register->E.SS  = Regs->E.SS;
  CopyMem (&Register->E.EFlags, &Regs->E.EFLAGS, sizeof (UINT32));

  return;
}

/**
  Thunk to 16-bit real mode and call Segment:Offset. Regs will contain the
    16-bit register context on entry and exit. Arguments can be passed on
    the Stack argument

    @param[in] This      - Protocol instance pointer.
    @param[in] Segment   - Segemnt of 16-bit mode call
    @param[in] Offset    - Offset of 16-bit mdoe call
    @param[in] Reg       - Register context passed into (and returned) from thunk to
                16-bit mode
    @param[in] Stack     - Caller allocated stack used to pass arguments
    @param[in] StackSize - Size of Stack in bytes

    @retval FALSE     - Thunk completed, and there were no BIOS errors in the target code.
                See Regs for status.
    @retval TRUE      - There was a BIOS error in the target code.
**/
BOOLEAN
EFIAPI
SmmFarCall86 (
  IN EFI_SMM_THUNK_PROTOCOL          *This,
  IN UINT16                          Segment,
  IN UINT16                          Offset,
  IN OUT EFI_IA32_REGISTER_SET       *Regs OPTIONAL,
  IN VOID                            *Stack OPTIONAL,
  IN UINTN                           StackSize
  )
{
  UINT32            ThunkFlag;
  IA32_REGISTER_SET Register;

  ThunkFlag = 0;

  ///
  /// Transfer the EFI_IA32_REGISTER_SET register set to
  /// IA32_REGISTER_SET register set
  ///
  if (Regs != NULL) {
    ConvertRegister (Regs, &Register);
  }
  ///
  /// Fill the far call address
  ///
  Register.E.CS   = Segment;
  Register.E.Eip  = Offset;

  ///
  /// Far Call
  ///
  AsmThunk16FarCall86 (&mPrivateData.ThunkContext, &Register, (UINT32) ThunkFlag);

  ///
  /// Transfer the IA32_REGISTER_SET register set to
  /// EFI_IA32_REGISTER_SET register set
  ///
  if (Regs != NULL) {
    ConvertRegisterRet (&Register, Regs);
  }

  return TRUE;
}

/**
  Thunk to 16-bit real mode and call Segment:Offset of INT service entry
    in INT way for IRET.
    Regs will contain the 16-bit register context on entry and exit.
    Arguments can be passed on the Stack argument

    @param[in] This      - Protocol instance pointer.
    @param[in] Segment   - Segemnt of 16-bit mode call of INT call service
    @param[in] Offset    - Offset of 16-bit mdoe call of INT call service
    @param[in] Reg       - Register context passed into (and returned) from thunk to
                16-bit mode
    @param[in] Stack     - Caller allocated stack used to pass arguments
    @param[in] StackSize - Size of Stack in bytes

    @retval FALSE     - Thunk completed, and there were no BIOS errors in the target code.
                See Regs for status.
    @retval TRUE      - There was a BIOS error in the target code.
**/
BOOLEAN
EFIAPI
SmmIntCall86 (
  IN EFI_SMM_THUNK_PROTOCOL          *This,
  IN UINT16                          Segment,
  IN UINT16                          Offset,
  IN OUT EFI_IA32_REGISTER_SET       *Regs OPTIONAL,
  IN VOID                            *Stack OPTIONAL,
  IN UINTN                           StackSize
  )
{
  UINT32            ThunkFlag;
  IA32_REGISTER_SET Register;

  ///
  /// Transfer the EFI_IA32_REGISTER_SET register set to
  /// IA32_REGISTER_SET register set
  ///
  if (Regs != NULL) {
    ConvertRegister (Regs, &Register);
  }
  ///
  /// Set the flag that talk to thunk code
  /// this far call will return by iret instruction
  ///
  ThunkFlag = THUNK_INTERRUPT;

  ///
  /// Fill the far call address
  ///
  Register.E.CS   = Segment;
  Register.E.Eip  = Offset;

  ///
  /// Far Call
  ///
  AsmThunk16FarCall86 (&mPrivateData.ThunkContext, &Register, (UINT32) ThunkFlag);

  ///
  /// Transfer the IA32_REGISTER_SET register set to
  /// EFI_IA32_REGISTER_SET register set
  ///
  if (Regs != NULL) {
    ConvertRegisterRet (&Register, Regs);
  }

  return TRUE;
}

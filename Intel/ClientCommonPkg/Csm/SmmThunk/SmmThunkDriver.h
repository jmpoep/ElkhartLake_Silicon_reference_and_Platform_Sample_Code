/** @file
  Header file for SMM Thunk Driver.

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

@par Specification
**/

#ifndef _SMM_THUNK_DRIVER_H
#define _SMM_THUNK_DRIVER_H

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/ThunkLib.h>
#include <Protocol/SmmThunk.h>

#define LOW_STACK_SIZE          (EFI_PAGE_SIZE * 1)
#define EFI_SMM_THUNK_SIGNATURE SIGNATURE_32 ('S', 'M', 'T', 'H')

typedef struct {
  UINT32                 Signature;
  EFI_HANDLE             Handle;
  EFI_SMM_THUNK_PROTOCOL SmmThunk;
  THUNK16_CONTEXT        ThunkContext;
  EFI_PHYSICAL_ADDRESS   RealModeBuffer;
  UINTN                  BufferSize;
} SMM_THUNK_PRIVATE_DATA;

///
/// Prototypes
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
  );

/**
  Thunk to 16-bit real mode and call Segment:Offset. Regs will contain the
    16-bit register context on entry and exit. Arguments can be passed on
    the Stack argument

    @param[in] This      - Protocol instance pointer.
    @param[in] Segment   - Segment of 16-bit mode call
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
  );

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
  );

#endif

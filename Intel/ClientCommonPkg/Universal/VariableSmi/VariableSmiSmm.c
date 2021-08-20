//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Source that Provides Access to EFI Variable Services through SMI.

  Copyright (c) 2010 - 2019, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#include <PiSmm.h>

#include <Protocol/SmmVariable.h>
#include <Protocol/SmmCpu.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmAccess2.h>

#include <Guid/VariableSmi.h>
#include <Guid/SmmVariableCommon.h>
#include <Guid/VariableFormat.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/PcdLib.h>
#include <Library/SmmMemLib.h>

#define CARRY_FLAG 0x01

EFI_SMM_VARIABLE_PROTOCOL       *mSmmVariable;
EFI_SMM_CPU_PROTOCOL            *mSmmCpu;
UINT32                          mHiiDbAddress;
SMM_VARIABLE_COMMUNICATE_HEADER *mCommBuffer;
UINTN                           mCommBufferSize;

/**
  Read the specified register from SMM Save State.

  @param  Register  Specifies the CPU register to read from the save state.
  @param  CpuIndex  Specifies the zero-based index of the CPU save state.

  @retval 4-byte register value.
**/
UINT32
ReadRegister32 (
  EFI_SMM_SAVE_STATE_REGISTER  Register,
  UINTN                        CpuIndex
  )
{
  EFI_STATUS                  Status;
  UINT32                      Uint32;

  Status = mSmmCpu->ReadSaveState (
                      mSmmCpu,
                      sizeof (UINT32),
                      Register,
                      CpuIndex,
                      &Uint32
                      );
  ASSERT_EFI_ERROR (Status);

  return Uint32;
}

/**
  This function writes 32bit register value to SMM Save State.

  @param Register  Save State register index.
  @param CpuIndex  Cpu Index.
  @param Uint32    32bit value.
**/
VOID
WriteRegister32 (
  EFI_SMM_SAVE_STATE_REGISTER  Register,
  UINTN                        CpuIndex,
  UINT32                       Uint32
  )
{
  EFI_STATUS                   Status;

  Status = mSmmCpu->WriteSaveState (
                        mSmmCpu,
                        sizeof (UINT32),
                        Register,
                        CpuIndex,
                        &Uint32
                        );
  ASSERT_EFI_ERROR (Status);
}

/**
  This function check if the null terminated unicode string is valid
  per processor architecture and not overlap with SMRAM.

  @param Buffer  The string start address to be checked.

  @retval TRUE  This string is valid per processor architecture and not overlap with SMRAM.
  @retval FALSE This string is not valid per processor architecture or overlap with SMRAM.
**/
BOOLEAN
SmmIsStringOutsideSmmValid (
  IN EFI_PHYSICAL_ADDRESS  Buffer
  )
{
  UINTN                    Index;
  for (Index = 0; SmmIsBufferOutsideSmmValid (Buffer, (Index + 1) * sizeof (CHAR16)); Index++) {
    if (((CHAR16 *) (UINTN) Buffer)[Index] == L'\0') {
      return TRUE;
    }
  }
  return FALSE;
}

/**
  Calling the SMI Interface.

  @attention This function handles TOC/TOU race condition and may receive
   untrusted input.
   Variable/GetNextVariable is copied from non-SMRAM to local SMRAM, checked,
   used, then copied the final result to original non-SMRAM.

  Caution: This function may receive untrusted input.
  Variable INT15 parameter is external input, so this function will do basic validation.
  Each sub function GET_VARIABLE_SUBFUNCTION, GET_NEXT_VARIABLE_SUBFUNCTION,
   SET_VARIABLE_SUBFUNCTION, EXPORT_HII_DB_SUBFUNCTION
  should also do validation based on its own knowledge.
  The basic rule is that the function need make sure the input and outout buffer will not
  override the SMRAM.

  The caller will write AL (the value 0xef) to the SMI Command Port as
  defined in the ACPI FADT.
  The SMI handler will update the callers' buffer(s) and return.
  Notes:
  The function will clear the carry bit if it is successful (CF = 0).
  If the function is unsuccessful, it will set the carry bit and set the
  error code in the AH register as indicated by the error table below.
  The function returns the following data in the provided parameter block.

  @param DispatchHandle   Handle of Disaptcher.
  @param Context          Context when the Disaptcher calls the function.
  @param SwContext        Software SMI Context
  @param CommBufferSize   Software SMI Context buffer size

  @return EFI_STATUS

**/
EFI_STATUS
EFIAPI
VariableInterface (
  IN EFI_HANDLE                            DispatchHandle,
  IN CONST EFI_SMM_SW_REGISTER_CONTEXT     *Context,
  IN OUT EFI_SMM_SW_CONTEXT                *SwContext,
  IN OUT UINTN                             *CommBufferSize
  )
{
  EFI_STATUS                               Status;
  VARIABLE_BLOCK                           *VariableBlock;
  VARIABLE_BLOCK                           Variable;
  GET_NEXT_VARIABLE_BLOCK                  *GetNextVariableBlock;
  GET_NEXT_VARIABLE_BLOCK                  GetNextVariable;
  SMM_VARIABLE_COMMUNICATE_ACCESS_VARIABLE *SetVariable;
  UINTN                                    BufferSize;
  UINT8                                    SubFunction;
  UINTN                                    VariableSize;
  UINTN                                    TempSize;
  VOID                                     *HiiDbAddress;
  UINT32                                   Data32;
  CHAR16                                   *VariableName;
  VOID                                     *VariableData;
  UINTN                                    NameSize;

  VariableBlock        = NULL;
  GetNextVariableBlock = NULL;
  VariableName         = NULL;
  VariableData         = NULL;

  //
  // Extract the subfunction number from AH,
  // and process the requested subfunction.
  //
  Data32 = ReadRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RAX, SwContext->SwSmiCpuIndex);
  SubFunction = (UINT8) ((Data32 & 0xFF00) >> 8);

  switch (SubFunction) {
    case GET_VARIABLE_SUBFUNCTION:
      //
      // EBX = address of the VARIABLE_BLOCK parameter block
      //
      VariableBlock = (VARIABLE_BLOCK *) (UINTN) ReadRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RBX, SwContext->SwSmiCpuIndex);
      CopyMem (&Variable, VariableBlock, sizeof (VARIABLE_BLOCK));
      VariableName = AllocateCopyPool (StrSize ((CHAR16 *)(UINTN)Variable.VariableName), (CHAR16 *)(UINTN)Variable.VariableName);
      TempSize = Variable.DataSize;
      //
      // Check if variable block range is in the range of SMRAM
      //
      if (!SmmIsBufferOutsideSmmValid ((UINTN) VariableBlock, sizeof (VARIABLE_BLOCK)) ||
          !SmmIsStringOutsideSmmValid ((UINTN) Variable.VariableName) ||
          !SmmIsBufferOutsideSmmValid ((UINTN) Variable.Data, TempSize)) {
        DEBUG ((EFI_D_ERROR, "Get variable block range is in SMRAM or overflow!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else {
        Status = mSmmVariable->SmmGetVariable (
                                 VariableName,
                                 &Variable.VendorGuid,
                                 &Variable.Attributes,
                                 &TempSize,
                                 (VOID *) (UINTN) Variable.Data
                                 );
        VariableBlock->DataSize = (UINT32)TempSize;
      }
      break;

    case GET_NEXT_VARIABLE_SUBFUNCTION:
      //
      // EBX = address of the GET_NEXT_VARIABLE_BLOCK parameter block
      //
      GetNextVariableBlock = (GET_NEXT_VARIABLE_BLOCK *) (UINTN) ReadRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RBX, SwContext->SwSmiCpuIndex);
      CopyMem (&GetNextVariable, GetNextVariableBlock, sizeof (GET_NEXT_VARIABLE_BLOCK));
      VariableName = AllocateZeroPool (GetNextVariable.VariableNameSize);
      StrCpyS (VariableName, GetNextVariable.VariableNameSize, (CHAR16 *)(UINTN)GetNextVariable.VariableName);
      TempSize = GetNextVariable.VariableNameSize;
      //
      // Check if get next variable block range is in the range of SMRAM
      //
      if ((!SmmIsBufferOutsideSmmValid ((UINTN) GetNextVariableBlock, sizeof (GET_NEXT_VARIABLE_BLOCK))) ||
          (!SmmIsBufferOutsideSmmValid ((UINTN) GetNextVariable.VariableName, TempSize))) {
        DEBUG ((EFI_D_ERROR, "Get next variable block range is in SMRAM or overflow!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else {
        Status = mSmmVariable->SmmGetNextVariableName (
                                 &TempSize,
                                 VariableName,
                                 &GetNextVariable.VendorGuid
                                 );
        if (!EFI_ERROR (Status)) {
          StrCpyS ((CHAR16 *)(UINTN)GetNextVariableBlock->VariableName, GetNextVariable.VariableNameSize, VariableName);
          CopyGuid (&GetNextVariableBlock->VendorGuid, &GetNextVariable.VendorGuid);
        }
        GetNextVariableBlock->VariableNameSize = (UINT32) TempSize;
      }
      break;

    case SET_VARIABLE_SUBFUNCTION:
      //
      // EBX = address of the VARIABLE_BLOCK parameter block
      //
      VariableBlock = (VARIABLE_BLOCK *) (UINTN) ReadRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RBX, SwContext->SwSmiCpuIndex);
      CopyMem (&Variable, VariableBlock, sizeof (VARIABLE_BLOCK));
      NameSize = StrSize ((CHAR16 *)(UINTN)Variable.VariableName);
      VariableName = AllocateCopyPool (NameSize, (CHAR16 *)(UINTN)Variable.VariableName);
      if (VariableName == NULL) {
        DEBUG ((EFI_D_ERROR, "Set variable with variable name is NULL!\n"));
        Status = EFI_INVALID_PARAMETER;
      } else {
        Status = EFI_SUCCESS;
        if (Variable.DataSize != 0) {
          VariableData = AllocateCopyPool (Variable.DataSize, (CHAR16 *)(UINTN)Variable.Data);
          ASSERT (VariableData != NULL);
          if (VariableData == NULL) {
            DEBUG ((EFI_D_ERROR, "Allocate buffer failure!\n"));
            Status = EFI_OUT_OF_RESOURCES;
          }
        }
        if (Status != EFI_OUT_OF_RESOURCES) {
          //
          // Check if set variable block range is in the range of SMRAM
          //
          if (!SmmIsBufferOutsideSmmValid ((UINTN) VariableBlock, sizeof (VARIABLE_BLOCK)) ||
              !SmmIsStringOutsideSmmValid ((UINTN) Variable.VariableName) ||
              !SmmIsBufferOutsideSmmValid ((UINTN) Variable.Data, (UINTN) Variable.DataSize)) {
            DEBUG ((EFI_D_ERROR, "Set variable block range is in SMRAM or overflow!\n"));
            Status = EFI_INVALID_PARAMETER;
          } else {
            SetVariable = (SMM_VARIABLE_COMMUNICATE_ACCESS_VARIABLE *) mCommBuffer->Data;

            SetVariable->Attributes = Variable.Attributes;
            SetVariable->DataSize = Variable.DataSize;
            SetVariable->NameSize = NameSize;

            if ((SetVariable->NameSize > mCommBufferSize) || (SetVariable->DataSize > mCommBufferSize) ||
                (SMM_VARIABLE_COMMUNICATE_HEADER_SIZE + OFFSET_OF (SMM_VARIABLE_COMMUNICATE_ACCESS_VARIABLE, Name) >
                 mCommBufferSize - SetVariable->NameSize) ||
                (SMM_VARIABLE_COMMUNICATE_HEADER_SIZE + OFFSET_OF (SMM_VARIABLE_COMMUNICATE_ACCESS_VARIABLE, Name) +
                 SetVariable->NameSize > mCommBufferSize - SetVariable->DataSize)
                ) {
              DEBUG ((EFI_D_ERROR, "Set variable block range is too big!\n"));
              Status = EFI_INVALID_PARAMETER;
            } else {
              CopyMem (SetVariable->Name, VariableName, SetVariable->NameSize);
              if (SetVariable->DataSize != 0) {
                CopyMem ((UINT8 *) SetVariable->Name + SetVariable->NameSize, VariableData, SetVariable->DataSize);
              }
              CopyGuid (&SetVariable->Guid, &Variable.VendorGuid);

              BufferSize = mCommBufferSize;
              Status = gSmst->SmiManage (
                                &gEfiSmmVariableProtocolGuid,
                                NULL,
                                mCommBuffer,
                                &BufferSize
                                );
              ASSERT_EFI_ERROR (Status);
              Status = mCommBuffer->ReturnStatus;
            }
          }
        }
      }
      break;

    case EXPORT_HII_DB_SUBFUNCTION:
      //
      // Read the HII Database address from the variable.
      //
      if (mHiiDbAddress == 0) {
        HiiDbAddress = NULL;
        VariableSize = sizeof (HiiDbAddress);
        Status = mSmmVariable->SmmGetVariable (
                                 VARIABLE_SMI_HII_DATABASE_VARIABLE_NAME,
                                 &gVariableSmiGuid,
                                 NULL,
                                 &VariableSize,
                                 &HiiDbAddress
                                 );
        if (!EFI_ERROR (Status)) {
          //
          // Cache it, no need to read again and again.
          //
          mHiiDbAddress = (UINT32) (UINTN) HiiDbAddress;
        }
      } else {
        Status = EFI_SUCCESS;
      }
      //
      // Return the HII Database address in DX:BX
      //
      Data32 = ReadRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RDX, SwContext->SwSmiCpuIndex);
      Data32 &= 0xFFFF0000;
      Data32 |= (((UINT32) (UINTN) mHiiDbAddress) >> 16) & 0xFFFF;
      WriteRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RDX, SwContext->SwSmiCpuIndex, Data32);

      Data32 = ReadRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RBX, SwContext->SwSmiCpuIndex);
      Data32 &= 0xFFFF0000;
      Data32 |= ((UINT32) (UINTN) mHiiDbAddress) & 0xFFFF;
      WriteRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RBX, SwContext->SwSmiCpuIndex, Data32);

      break;

    case COPY_MEMORY_SUBFUNCTION:
      DEBUG ((EFI_D_ERROR, "ERROR: CopyMemory subfunction is no longer supported due to security concern!\n"));
      Status = EFI_UNSUPPORTED;
      break;

    default:
      Status = EFI_INVALID_PARAMETER;
      break;
  }

  //
  // Set CF in case of error, clear on success
  //
  Data32 = ReadRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RFLAGS, SwContext->SwSmiCpuIndex);
  if (EFI_ERROR (Status)) {
    Data32 |= CARRY_FLAG;
  } else {
    Data32 &= ~CARRY_FLAG;
  }
  WriteRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RFLAGS, SwContext->SwSmiCpuIndex, Data32);

  //
  // Put the error code in AH
  //
  Data32 = ReadRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RAX, SwContext->SwSmiCpuIndex);
  Data32 &= 0xFFFF00FF;

  switch (Status) {
    case EFI_INVALID_PARAMETER: Data32 |= (INVALID_VALUE    << 8); break;
    case EFI_BUFFER_TOO_SMALL:  Data32 |= (BUFFER_TOO_SMALL << 8); break;
    case EFI_UNSUPPORTED:       Data32 |= (NOT_SUPPORTED    << 8); break;
    case EFI_NOT_FOUND:         Data32 |= (NOT_FOUND        << 8); break;
    case EFI_DEVICE_ERROR:      Data32 |= (DEVICE_ERROR     << 8); break;
    case EFI_WRITE_PROTECTED:   Data32 |= (INVALID_VALUE    << 8); break;
    default: break;
  }

  WriteRegister32 (EFI_SMM_SAVE_STATE_REGISTER_RAX, SwContext->SwSmiCpuIndex, Data32);

  if (VariableName != NULL) {
    FreePool (VariableName);
  }

  if (VariableData != NULL) {
    FreePool (VariableData);
  }

  return EFI_SUCCESS;
}

/**
  Entry point of the SMI variable DXE driver.

  @param ImageHandle    ImageHandle
  @param SystemTable    Pointer to System Table

  @return EFI_STATUS

**/
EFI_STATUS
EFIAPI
VariableSmiEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS                    Status;
  EFI_SMM_SW_DISPATCH2_PROTOCOL *SwDispatch;
  EFI_SMM_SW_REGISTER_CONTEXT   SwContext;
  EFI_HANDLE                    Handle;

  Status = gSmst->SmmLocateProtocol (&gEfiSmmVariableProtocolGuid, NULL, (VOID **) &mSmmVariable);
  ASSERT_EFI_ERROR (Status);

  Status = gSmst->SmmLocateProtocol (&gEfiSmmCpuProtocolGuid, NULL, (VOID **) &mSmmCpu);
  ASSERT_EFI_ERROR (Status);

  Status = gSmst->SmmLocateProtocol (&gEfiSmmSwDispatch2ProtocolGuid, NULL, (VOID **) &SwDispatch);
  ASSERT_EFI_ERROR (Status);

  SwContext.SwSmiInputValue = SW_SMI_VARIABLE_SERVICES;
  Status = SwDispatch->Register (SwDispatch, (EFI_SMM_HANDLER_ENTRY_POINT2) VariableInterface, &SwContext, &Handle);
  ASSERT_EFI_ERROR (Status);

  mCommBufferSize = SMM_VARIABLE_COMMUNICATE_HEADER_SIZE + sizeof (SMM_VARIABLE_COMMUNICATE_GET_PAYLOAD_SIZE);
  Status = gBS->AllocatePool (EfiBootServicesData, mCommBufferSize, (VOID **) &mCommBuffer);
  ASSERT_EFI_ERROR (Status);

  mCommBuffer->Function = SMM_VARIABLE_FUNCTION_GET_PAYLOAD_SIZE;
  Status = gSmst->SmiManage (
                    &gEfiSmmVariableProtocolGuid,
                    NULL,
                    mCommBuffer,
                    &mCommBufferSize
                    );
  ASSERT_EFI_ERROR (Status);
  ASSERT_EFI_ERROR (mCommBuffer->ReturnStatus);

  mCommBufferSize = SMM_VARIABLE_COMMUNICATE_HEADER_SIZE
                  + ((SMM_VARIABLE_COMMUNICATE_GET_PAYLOAD_SIZE *) mCommBuffer->Data)->VariablePayloadSize;
  FreePool (mCommBuffer);

  Status = gBS->AllocatePool (EfiReservedMemoryType, mCommBufferSize, (VOID **) &mCommBuffer);
  ASSERT_EFI_ERROR (Status);
  ASSERT (mCommBuffer != NULL);

  mCommBuffer->Function = SMM_VARIABLE_FUNCTION_SET_VARIABLE;
  return Status;
}

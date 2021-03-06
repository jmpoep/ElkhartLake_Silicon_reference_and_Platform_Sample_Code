/*++
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor.  This file may
  be modified by the user, subject to additional terms of the
  license agreement
--*/
/** @file
  CPU exception handler library implementation for PEIM module.

Copyright (c) 2016 - 2017, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#include <PiPei.h>
#include "CpuExceptionCommon.h"
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryAllocationLib.h>

CONST UINTN    mSmmFlag  = 0;

EFI_GUID mCpuExceptrionHandlerLibHobGuid = CPU_EXCEPTION_HANDLER_LIB_HOB_GUID;

/**
  Get exception handler data pointer from GUIDed HOb.

  @return  pointer to exception handler data.
**/
EXCEPTION_HANDLER_DATA *
GetExceptionHandlerData (
  VOID
  )
{
  EFI_HOB_GUID_TYPE       *GuidHob;
  VOID                    *DataInHob;
  EXCEPTION_HANDLER_DATA  *ExceptionHandlerData;

  ExceptionHandlerData = NULL;
  GuidHob = GetFirstGuidHob (&mCpuExceptrionHandlerLibHobGuid);
  if (GuidHob != NULL) {
    DataInHob = GET_GUID_HOB_DATA (GuidHob);
    ExceptionHandlerData = (EXCEPTION_HANDLER_DATA *)(*(UINTN *)DataInHob);
  }
  ASSERT (ExceptionHandlerData != NULL);
  return ExceptionHandlerData;
}

/**
  Common exception handler.

  @param ExceptionType  Exception type.
  @param SystemContext  Pointer to EFI_SYSTEM_CONTEXT.
**/
VOID
EFIAPI
CommonExceptionHandler (
  IN EFI_EXCEPTION_TYPE   ExceptionType,
  IN EFI_SYSTEM_CONTEXT   SystemContext
  )
{
  EXCEPTION_HANDLER_DATA  *ExceptionHandlerData;

  ExceptionHandlerData = GetExceptionHandlerData ();
  CommonExceptionHandlerWorker (ExceptionType, SystemContext, ExceptionHandlerData);
}

/**
  Initializes all CPU exceptions entries and provides the default exception handlers.

  Caller should try to get an array of interrupt and/or exception vectors that are in use and need to
  persist by EFI_VECTOR_HANDOFF_INFO defined in PI 1.3 specification.
  If caller cannot get reserved vector list or it does not exists, set VectorInfo to NULL.
  If VectorInfo is not NULL, the exception vectors will be initialized per vector attribute accordingly.
  Note: Before invoking this API, caller must allocate memory for IDT table and load
        IDTR by AsmWriteIdtr().

  @param[in]  VectorInfo    Pointer to reserved vector list.

  @retval EFI_SUCCESS           CPU Exception Entries have been successfully initialized
                                with default exception handlers.
  @retval EFI_INVALID_PARAMETER VectorInfo includes the invalid content if VectorInfo is not NULL.
  @retval EFI_UNSUPPORTED       This function is not supported.

**/
EFI_STATUS
EFIAPI
InitializeCpuExceptionHandlers (
  IN EFI_VECTOR_HANDOFF_INFO       *VectorInfo OPTIONAL
  )
{
  EFI_STATUS                       Status;
  EXCEPTION_HANDLER_DATA           *ExceptionHandlerData;
  RESERVED_VECTORS_DATA            *ReservedVectors;

  ReservedVectors = AllocatePool (sizeof (RESERVED_VECTORS_DATA) * CPU_EXCEPTION_NUM);
  ASSERT (ReservedVectors != NULL);

  ExceptionHandlerData = AllocatePool (sizeof (EXCEPTION_HANDLER_DATA));
  ASSERT (ExceptionHandlerData != NULL);
  ExceptionHandlerData->ReservedVectors          = ReservedVectors;
  ExceptionHandlerData->ExternalInterruptHandler = NULL;
  InitializeSpinLock (&ExceptionHandlerData->DisplayMessageSpinLock);

  Status = InitializeCpuExceptionHandlersWorker (VectorInfo, ExceptionHandlerData);
  if (EFI_ERROR (Status)) {
    FreePool (ReservedVectors);
    FreePool (ExceptionHandlerData);
    return Status;
  }

  //
  // Build location of CPU MP DATA buffer in HOB
  //
  BuildGuidDataHob (
    &mCpuExceptrionHandlerLibHobGuid,
    (VOID *)&ExceptionHandlerData,
    sizeof(UINT64)
    );

  return EFI_SUCCESS;
}

/**
  Initializes all CPU interrupt/exceptions entries and provides the default interrupt/exception handlers.

  Caller should try to get an array of interrupt and/or exception vectors that are in use and need to
  persist by EFI_VECTOR_HANDOFF_INFO defined in PI 1.3 specification.
  If caller cannot get reserved vector list or it does not exists, set VectorInfo to NULL.
  If VectorInfo is not NULL, the exception vectors will be initialized per vector attribute accordingly.

  @param[in]  VectorInfo    Pointer to reserved vector list.

  @retval EFI_SUCCESS           All CPU interrupt/exception entries have been successfully initialized
                                with default interrupt/exception handlers.
  @retval EFI_INVALID_PARAMETER VectorInfo includes the invalid content if VectorInfo is not NULL.
  @retval EFI_UNSUPPORTED       This function is not supported.

**/
EFI_STATUS
EFIAPI
InitializeCpuInterruptHandlers (
  IN EFI_VECTOR_HANDOFF_INFO       *VectorInfo OPTIONAL
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Registers a function to be called from the processor interrupt handler.

  This function registers and enables the handler specified by InterruptHandler for a processor
  interrupt or exception type specified by InterruptType. If InterruptHandler is NULL, then the
  handler for the processor interrupt or exception type specified by InterruptType is uninstalled.
  The installed handler is called once for each processor interrupt or exception.
  NOTE: This function should be invoked after InitializeCpuExceptionHandlers() or
  InitializeCpuInterruptHandlers() invoked, otherwise EFI_UNSUPPORTED returned.

  @param[in]  InterruptType     Defines which interrupt or exception to hook.
  @param[in]  InterruptHandler  A pointer to a function of type EFI_CPU_INTERRUPT_HANDLER that is called
                                when a processor interrupt occurs. If this parameter is NULL, then the handler
                                will be uninstalled.

  @retval EFI_SUCCESS           The handler for the processor interrupt was successfully installed or uninstalled.
  @retval EFI_ALREADY_STARTED   InterruptHandler is not NULL, and a handler for InterruptType was
                                previously installed.
  @retval EFI_INVALID_PARAMETER InterruptHandler is NULL, and a handler for InterruptType was not
                                previously installed.
  @retval EFI_UNSUPPORTED       The interrupt specified by InterruptType is not supported,
                                or this function is not supported.
**/
EFI_STATUS
EFIAPI
RegisterCpuInterruptHandler (
  IN EFI_EXCEPTION_TYPE            InterruptType,
  IN EFI_CPU_INTERRUPT_HANDLER     InterruptHandler
  )
{
  return EFI_UNSUPPORTED;
}

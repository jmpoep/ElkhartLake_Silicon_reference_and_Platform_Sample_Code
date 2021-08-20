//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  DXE/Runtime/SMM instance of TraceHub Debug Lib.

  Copyright (c) 2014 - 2018, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#include <PiDxe.h>
#include <Library/PcdLib.h>
#include <Library/TraceHubDebugLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include "sventx/sventx.h"
#include "EnableTraceHubData.h"

psven_handle_t    mTraceHubHandle = NULL;

/**
  Get internal TraceHub Handle.
**/
psven_handle_t
GetInternalTraceHubHandle (
  )
{
  TRACE_HUB_PLATFORM_DATA    TraceHubPlatformData;
  psven_header_t             TraceHubHandleHeaderBuffer;

  if (mTraceHubHandle == NULL) {
    TraceHubPlatformData.Master = PcdGet32 (PcdTraceHubDebugLibMaster);
    TraceHubPlatformData.Channel = PcdGet32 (PcdTraceHubDebugLibChannel);

    TraceHubHandleHeaderBuffer = AllocateRuntimePool (sizeof (sven_header_t));
    SVEN_INIT_STATE (TraceHubHandleHeaderBuffer, sventx_platform_init, NULL);
    mTraceHubHandle = SVEN_ALLOC_HANDLE_STATE (TraceHubHandleHeaderBuffer, &TraceHubPlatformData);

    SVEN_SET_HANDLE_GUID_UNIT (
      mTraceHubHandle,
      *((sven_guid_t *)(VOID *) &gEfiCallerIdGuid),
      0
      );
  }

  if (mTraceHubHandle->svh_platform.TraceHubPlatformData.MmioAddr == NULL) {
    return NULL;
  }
  return mTraceHubHandle;
}

/**
  Write data from buffer and Severity to TraceHub.

  Writes NumberOfBytes data bytes from Buffer and Severity to TraceHub.
  If Buffer is NULL and NumberOfBytes is larger than zero, then ASSERT().
  If NumberOfBytes is zero, no buffer is written.

  @param  SeverityType     Severity type of the written data buffer.
  @param  Buffer           Pointer to the data buffer to be written.
  @param  NumberOfBytes    Number of bytes to written to TraceHub device.

  @retval RETURN_SUCCESS   The number of bytes written to TraceHub.
  @retval Other            Fail to write the buffer to TraceHub.

**/
RETURN_STATUS
EFIAPI
TraceHubDebugWrite (
  IN TRACE_HUB_SEVERITY_TYPE    SeverityType,
  IN UINT8                      *Buffer,
  IN UINTN                      NumberOfBytes
  )
{
  psven_handle_t            TraceHubHandle;

  ASSERT (Buffer != NULL || NumberOfBytes == 0);

  if (NumberOfBytes == 0) {
    //
    // Nothing to TraceHub
    //
    return RETURN_SUCCESS;
  }

  if (EnableTraceHubData (SeverityType) == FALSE) {
    return RETURN_ABORTED;
  }

  TraceHubHandle = GetInternalTraceHubHandle ();
  if (TraceHubHandle == NULL) {
    return RETURN_DEVICE_ERROR;
  }

  SVEN_DEBUG (TraceHubHandle, (sven_severity_t) SeverityType, (const char *)Buffer, (sven_u16_t) NumberOfBytes);

  return RETURN_SUCCESS;
}

/**
  Write catalog64 message SVEN event with 0 parameters to TraceHub

  @param  SeverityType   Severity type of the catid message event.
  @param  Id             Catalog ID

**/
VOID
EFIAPI
TraceHubWriteCataLog64_0 (
  IN TRACE_HUB_SEVERITY_TYPE    SeverityType,
  IN UINT64                     Id
  )
{
  psven_handle_t            TraceHubHandle;

  TraceHubHandle = GetInternalTraceHubHandle ();

  if (TraceHubHandle != NULL) {
    SVEN_CATALOG64_0 (TraceHubHandle, (sven_severity_t)SeverityType, Id);
  }
}

/**
  Write catalog64 message SVEN event with 1 parameters to TraceHub

  @param  SeverityType   Severity type of the catid message event.
  @param  Id             Catalog ID
  @param  Param1         Parameter 1 passed to catid message event.

**/
VOID
EFIAPI
TraceHubWriteCataLog64_1 (
  IN TRACE_HUB_SEVERITY_TYPE    SeverityType,
  IN UINT64                     Id,
  IN UINT32                     Param1
  )
{
  psven_handle_t            TraceHubHandle;

  TraceHubHandle = GetInternalTraceHubHandle ();

  if (TraceHubHandle != NULL) {
    SVEN_CATALOG64_1 (TraceHubHandle, (sven_severity_t)SeverityType, Id, Param1);
  }
}

/**
  Write catalog64 message SVEN event with 2 parameters to TraceHub

  @param  SeverityType   Severity type of the catid message event.
  @param  Id             Catalog ID
  @param  Param1         Parameter 1 passed to catid message event.
  @param  Param2         Parameter 2 passed to catid message event.

**/
VOID
EFIAPI
TraceHubWriteCataLog64_2 (
  IN TRACE_HUB_SEVERITY_TYPE    SeverityType,
  IN UINT64                     Id,
  IN UINT32                     Param1,
  IN UINT32                     Param2
  )
{
  psven_handle_t            TraceHubHandle;

  TraceHubHandle = GetInternalTraceHubHandle ();

  if (TraceHubHandle != NULL) {
    SVEN_CATALOG64_2 (TraceHubHandle, (sven_severity_t)SeverityType, Id, Param1, Param2);
  }
}

/**
  Write catalog64 message SVEN event with 3 parameters to TraceHub

  @param  SeverityType   Severity type of the catid message event.
  @param  Id             Catalog ID
  @param  Param1         Parameter 1 passed to catid message event.
  @param  Param2         Parameter 2 passed to catid message event.
  @param  Param3         Parameter 3 passed to catid message event.

**/
VOID
EFIAPI
TraceHubWriteCataLog64_3 (
  IN TRACE_HUB_SEVERITY_TYPE    SeverityType,
  IN UINT64                     Id,
  IN UINT32                     Param1,
  IN UINT32                     Param2,
  IN UINT32                     Param3
  )
{
  psven_handle_t            TraceHubHandle;

  TraceHubHandle = GetInternalTraceHubHandle ();

  if (TraceHubHandle != NULL) {
    SVEN_CATALOG64_3 (TraceHubHandle, (sven_severity_t)SeverityType, Id, Param1, Param2, Param3);
  }
}

/**
  Write catalog64 message SVEN event with 4 parameters to TraceHub

  @param  SeverityType   Severity type of the catid message event.
  @param  Id             Catalog ID
  @param  Param1         Parameter 1 passed to catid message event.
  @param  Param2         Parameter 2 passed to catid message event.
  @param  Param3         Parameter 3 passed to catid message event.
  @param  Param4         Parameter 4 passed to catid message event.

**/
VOID
EFIAPI
TraceHubWriteCataLog64_4 (
  IN TRACE_HUB_SEVERITY_TYPE    SeverityType,
  IN UINT64                     Id,
  IN UINT32                     Param1,
  IN UINT32                     Param2,
  IN UINT32                     Param3,
  IN UINT32                     Param4
  )
{
  psven_handle_t            TraceHubHandle;

  TraceHubHandle = GetInternalTraceHubHandle ();

  if (TraceHubHandle != NULL) {
    SVEN_CATALOG64_4 (TraceHubHandle, (sven_severity_t)SeverityType, Id, Param1, Param2, Param3, Param4);
  }
}

/**
  Write catalog64 message SVEN event with 5 parameters to TraceHub

  @param  SeverityType   Severity type of the catid message event.
  @param  Id             Catalog ID
  @param  Param1         Parameter 1 passed to catid message event.
  @param  Param2         Parameter 2 passed to catid message event.
  @param  Param3         Parameter 3 passed to catid message event.
  @param  Param4         Parameter 4 passed to catid message event.
  @param  Param5         Parameter 5 passed to catid message event.

**/
VOID
EFIAPI
TraceHubWriteCataLog64_5 (
  IN TRACE_HUB_SEVERITY_TYPE    SeverityType,
  IN UINT64                     Id,
  IN UINT32                     Param1,
  IN UINT32                     Param2,
  IN UINT32                     Param3,
  IN UINT32                     Param4,
  IN UINT32                     Param5
  )
{
  psven_handle_t            TraceHubHandle;

  TraceHubHandle = GetInternalTraceHubHandle ();

  if (TraceHubHandle != NULL) {
    SVEN_CATALOG64_5 (TraceHubHandle, (sven_severity_t)SeverityType, Id, Param1, Param2, Param3, Param4, Param5);
  }
}

/**
  Write catalog64 message SVEN event with 6 parameters to TraceHub

  @param  SeverityType   Severity type of the catid message event.
  @param  Id             Catalog ID
  @param  Param1         Parameter 1 passed to catid message event.
  @param  Param2         Parameter 2 passed to catid message event.
  @param  Param3         Parameter 3 passed to catid message event.
  @param  Param4         Parameter 4 passed to catid message event.
  @param  Param5         Parameter 5 passed to catid message event.
  @param  Param6         Parameter 6 passed to catid message event.

**/
VOID
EFIAPI
TraceHubWriteCataLog64_6 (
  IN TRACE_HUB_SEVERITY_TYPE    SeverityType,
  IN UINT64                     Id,
  IN UINT32                     Param1,
  IN UINT32                     Param2,
  IN UINT32                     Param3,
  IN UINT32                     Param4,
  IN UINT32                     Param5,
  IN UINT32                     Param6
  )
{
  psven_handle_t            TraceHubHandle;

  TraceHubHandle = GetInternalTraceHubHandle ();

  if (TraceHubHandle != NULL) {
    SVEN_CATALOG64_6 (TraceHubHandle, (sven_severity_t)SeverityType, Id, Param1, Param2, Param3, Param4, Param5, Param6);
  }
}

/**
  Allocates a buffer of type EfiRuntimeServicesData.

  Allocates the number bytes specified by AllocationSize of type EfiRuntimeServicesData
  and returns a pointer to the allocated buffer.  If AllocationSize is 0, then a
  valid buffer of 0 size is returned.  If there is not enough memory remaining to
  satisfy the request, then NULL is returned.

  @param  AllocationSize        The number of bytes to allocate.

  @return A pointer to the allocated buffer or NULL if allocation fails.

**/
VOID *
EFIAPI
SvenHeapAllocatePool (
  IN UINTN  AllocationSize
  )
{
  return AllocateRuntimePool (AllocationSize);
}

/**
  Frees a buffer that was previously allocated with one of the pool allocation functions in the
  Memory Allocation Library.

  Frees the buffer specified by Buffer.  Buffer must have been allocated on a previous call to the
  pool allocation services of the Memory Allocation Library.  If it is not possible to free pool
  resources, then this function will perform no actions.

  If Buffer was not allocated with a pool allocation function in the Memory Allocation Library,
  then ASSERT().

  @param  Buffer                The pointer to the buffer to free.

**/
VOID
EFIAPI
SvenHeapFreePool (
  IN VOID   *Buffer
  )
{
  FreePool (Buffer);
}

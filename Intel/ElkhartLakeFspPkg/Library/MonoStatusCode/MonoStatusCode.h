/*++

Copyright (c) 2017 Intel Corporation. All rights reserved
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  MonoStatusCode.h

Abstract:

  Contains Platform specific implementations required to use status codes.

--*/

#ifndef _MONO_STATUS_CODE_H_
#define _MONO_STATUS_CODE_H_

#include "PiPei.h"
#include "Ppi/StatusCode.h"
#include "Ppi/MemoryDiscovered.h"

#include "Library/HobLib.h"
#include "Library/DebugLib.h"
#include "Library/IoLib.h"
#include "Library/SerialPortLib.h"
#include "Protocol/StatusCode.h"


#include <Guid/StatusCodeDataTypeId.h>
#include <Guid/StatusCodeDataTypeDebug.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/PrintLib.h>
#include <Library/BaseMemoryLib.h>


//
// Status code reporting function
//
EFI_STATUS
SerialReportStatusCode (
  IN CONST EFI_PEI_SERVICES         **PeiServices,
  IN EFI_STATUS_CODE_TYPE     CodeType,
  IN EFI_STATUS_CODE_VALUE    Value,
  IN UINT32                   Instance,
  IN CONST EFI_GUID                 * CallerId,
  IN CONST EFI_STATUS_CODE_DATA     * Data OPTIONAL
  )
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  PeiServices - GC_TODO: add argument description
  CodeType    - GC_TODO: add argument description
  Value       - GC_TODO: add argument description
  Instance    - GC_TODO: add argument description
  CallerId    - GC_TODO: add argument description
  Data        - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
;

//
// This is the platform function that calls all of the listeners desired by the
// platform.
//
EFI_STATUS
EFIAPI
PlatformReportStatusCode (
  IN CONST EFI_PEI_SERVICES         **PeiServices,
  IN EFI_STATUS_CODE_TYPE     CodeType,
  IN EFI_STATUS_CODE_VALUE    Value,
  IN UINT32                   Instance,
  IN CONST EFI_GUID                 * CallerId,
  IN CONST EFI_STATUS_CODE_DATA     * Data OPTIONAL
  )
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  PeiServices - GC_TODO: add argument description
  CodeType    - GC_TODO: add argument description
  Value       - GC_TODO: add argument description
  Instance    - GC_TODO: add argument description
  CallerId    - GC_TODO: add argument description
  Data        - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
;

//
// Initialize the status code listeners and publish the status code PPI.
//

VOID
EFIAPI
InitializeMonoStatusCode (
  IN EFI_FFS_FILE_HEADER       *FfsHeader,
  IN const EFI_PEI_SERVICES          **PeiServices
  )
/*++

Routine Description:

  GC_TODO: Add function description

Arguments:

  FfsHeader   - GC_TODO: add argument description
  PeiServices - GC_TODO: add argument description

Returns:

  GC_TODO: add return values

--*/
;

extern EFI_PEI_PROGRESS_CODE_PPI    mStatusCodePpi;
extern EFI_PEI_PPI_DESCRIPTOR       mPpiListStatusCode;

#endif

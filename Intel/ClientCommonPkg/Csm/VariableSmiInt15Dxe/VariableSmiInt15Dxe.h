/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file
  This header file contains the Includes, Definitions, typedefs,
  Variable and External Declarations, Structure and
  function prototypes needed by the VariableSmi drivers

Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _VARIABLE_SMI_INT15_H_
#define _VARIABLE_SMI_INT15_H_


#include <PiDxe.h>

#include <Guid/GlobalVariable.h>
#include <Guid/VariableSmi.h>
#include <Guid/MemoryProfile.h>
#include <Guid/SmmVariableCommon.h>

#include <Protocol/LegacyBios.h>
#include <Protocol/SmmCommunication.h>
#include <Protocol/SmmVariable.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesLib.h>
#include <Library/PcdLib.h>
#include <Library/LegacyInterruptSupportLib.h>
#include <Library/PeCoffLib.h>
#include <Library/CacheMaintenanceLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DxeServicesTableLib.h>

//---------------------------------------------------------------------------

#pragma pack(1)

typedef struct _ASM_VARIABLE_BLOCK {
    EFI_GUID VendorGuid;
    UINT16   VariableNameSegment;
    UINT16   VariableNameOffset;
    UINT32   Attributes;
    UINT32   DataSize;
    UINT16   DataSegment;
    UINT16   DataOffset;
} ASM_VARIABLE_BLOCK;

typedef struct _ASM_GET_NEXT_VARIABLE_BLOCK {
    EFI_GUID VendorGuid;
    UINT16   VariableNameSegment;
    UINT16   VariableNameOffset;
    UINT32   VariableNameSize;
} ASM_GET_NEXT_VARIABLE_BLOCK;

#pragma pack()

#endif

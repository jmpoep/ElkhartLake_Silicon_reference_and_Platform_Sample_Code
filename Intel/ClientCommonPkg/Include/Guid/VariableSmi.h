//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/** @file
  Defines GUID for HII Export Database variable.

  Copyright (c) 2010 - 2016, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#ifndef _VARIABLE_SMI_H_
#define _VARIABLE_SMI_H_
#define VARIABLE_SMI_GUID { 0x1b838190, 0x4625, 0x4ead, {0xab, 0xc9, 0xcd, 0x5e, 0x6a, 0xf1, 0x8f, 0xe0 }}

#define VARIABLE_SMI_HII_DATABASE_VARIABLE_NAME  L"HiiDB"

extern EFI_GUID gVariableSmiGuid;

#define SW_SMI_VARIABLE_SERVICES      0xef

#define GET_VARIABLE_SUBFUNCTION      0x01
#define GET_NEXT_VARIABLE_SUBFUNCTION 0x02
#define SET_VARIABLE_SUBFUNCTION      0x03
#define EXPORT_HII_DB_SUBFUNCTION     0x04
#define COPY_MEMORY_SUBFUNCTION       0x05 // deprecated

//---------------------------------------------------------------------------
// Name: ErrorCodes
//
// Description:
// This table contains the list of error codes are supported by this function
//
// Fields: Value Name Description
//---------------------------------------------------------------------------
//
// 00h NO_ERROR No error. Maps to EFI_SUCCESS
// 82h INVALID_VALUE One of the parameters has an invalid value. Maps to EFI_INVALID_PARAMETER.
// 85h BUFFER_TOO_SMALL The VariableNameSize is too small for the result. VariableNameSize has been updated with the size needed to complete the request. Maps to EFI_BUFFER_TOO_SMALL.
// 86h NOT_SUPPORTED Interface not supported. Maps to standard INT 0x15 error codes.
// 87h DEVICE_ERROR The variable could not be retrieved due to a hardware error. Maps to EFI_DEVICE_ERROR.
// 8Eh NOT_FOUND The variable was not found. Maps to EFI_NOT_FOUND.
//
//---------------------------------------------------------------------------

#define NO_ERROR         0x00
#define INVALID_VALUE    0x82
#define BUFFER_TOO_SMALL 0x85
#define NOT_SUPPORTED    0x86
#define DEVICE_ERROR     0x87
#define NOT_FOUND        0x8e

#pragma pack(push, 1)
typedef struct {
  EFI_GUID HiiProtocolGuid;
  UINT32   HiiDatabaseSize;
} EFI_HII_PACKAGE_EXPORT_HEADER;

//---------------------------------------------------------------------------
// Name: VARIABLE_BLOCK
//
// Description: Description of the VARIABLE_BLOCK variables
//
// Fields: Name Type Description
//---------------------------------------------------------------------------
//
// VendorGuid EFI_GUID A unique identifier for the vendor.
// VariableName UINT32 32-bit physical address of the null-terminated Unicode string that is the name of the vendor's variable. The caller must ensure natural alignment.
// VariableNameSize UINT32 On input, the size in bytes of the Variable Name buffer. Updated with the actual size needed if the input size was too small.
// Attributes UINT32 The attributes bitmask for the variable. This information is always returned to the caller. The corresponding EFI function defined this as an optional parameter. The attributes are defined in the EFI specification.
// DataSize UINT32 On input, the size in bytes of the return Data buffer. On output the size of data returned in Data.
// Data UINT32 32-bit physical address of the buffer for returning the value of the variable. No specific alignment requirements exist.
//
//---------------------------------------------------------------------------

typedef struct _VARIABLE_BLOCK {
    EFI_GUID VendorGuid;
    UINT32   VariableName;
    UINT32   Attributes;
    UINT32   DataSize;
    UINT32   Data;
} VARIABLE_BLOCK;

//---------------------------------------------------------------------------
// Name: GET_NEXT_VARIABLE_BLOCK
//
// Description: Description of the GET_NEXT_VARIABLE_BLOCK variables
//
// Fields: Name Type Description
//---------------------------------------------------------------------------
//
// VendorGuid EFI_GUID A unique identifier for the vendor.
// VariableName UINT32 32-bit physical address of the null-terminated Unicode string that is the name of the vendor's variable. The caller must ensure natural alignment.
// VariableNameSize UINT32 On input, the size in bytes of the Variable Name buffer. Updated with the actual size needed if the input size was too small.
//
//---------------------------------------------------------------------------

typedef struct _GET_NEXT_VARIABLE_BLOCK {
    EFI_GUID VendorGuid;
    UINT32   VariableName;
    UINT32   VariableNameSize;
} GET_NEXT_VARIABLE_BLOCK;

#pragma pack()

#endif

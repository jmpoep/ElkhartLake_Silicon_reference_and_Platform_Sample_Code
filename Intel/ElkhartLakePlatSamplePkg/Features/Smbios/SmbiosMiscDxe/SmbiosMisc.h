/** @file
  Header file for the SmbiosMisc Driver.

  @par Revision Reference:
  SMBIOS Specification from DMTF: http://www.dmtf.org/standards/smbios
  Intel Framework Specifications, all available at: http://www.intel.com/technology/framework/spec.htm
  Unified Extensible Firmware Interface (UEFI) Specifications: http://www.uefi.org/specs/

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

@par Specification Reference:
**/

#ifndef _SMBIOS_MISC_DRIVER_H
#define _SMBIOS_MISC_DRIVER_H

#include "SmbiosMiscStrings.h"

#define T14_FVI_STRING          "Firmware Version Info"
#define MISC_MAX_SMBIOS_TABLE_STRINGS          10

/**
  The Generic Smbios Function to handle all SMBIOS records.

  @param  RecordData                 Pointer to copy of RecordData from the Data Table.

  @retval EFI_SUCCESS                All parameters were valid.
  @retval EFI_UNSUPPORTED            Unexpected RecordType value.
  @retval EFI_INVALID_PARAMETER      Invalid parameter was found.

**/
EFI_STATUS EFIAPI MiscCommonSmbiosFunction(
  IN  VOID                  *RecordData,
  IN  VOID                  *RecordStrings,
  IN  UINTN                 StringCount,
  IN  BOOLEAN               NeedToFreePoolMem,
  IN  UINTN                 MaxInstances,
  IN  EFI_SMBIOS_PROTOCOL   *Smbios
  );

/**
  Add an SMBIOS record.

  @param  Smbios                The EFI_SMBIOS_PROTOCOL instance.
  @param  SmbiosHandle          A unique handle will be assigned to the SMBIOS record.
  @param  Record                The data for the fixed portion of the SMBIOS record. The format of the record is
                                determined by EFI_SMBIOS_TABLE_HEADER.Type. The size of the formatted area is defined
                                by EFI_SMBIOS_TABLE_HEADER.Length and either followed by a double-null (0x0000) or
                                a set of null terminated strings and a null.

  @retval EFI_SUCCESS           Record was added.
  @retval EFI_OUT_OF_RESOURCES  Record was not added due to lack of system resources.

**/
EFI_STATUS
AddSmbiosRecord (
  IN EFI_SMBIOS_PROTOCOL        *Smbios,
  OUT EFI_SMBIOS_HANDLE         *SmbiosHandle,
  IN EFI_SMBIOS_TABLE_HEADER    *Record
  );

/**
  Initialize SMBIOS table strings.

  @param[out] **Destination            The pointer for the destination.
  @param[in]  *Source                  The pointer for the source date.
  @param[out] **StrBuffer              The pointer for string buffer.
  @param[out] *Count                   The accumulated number of strings.
  @param[out] *SizeOfStrings           The accumulated number of strings length.
  @param[in, out]  *StrBuffSize         Size of StrBuffer.

  @retval     EFI_SUCCESS              Successful.
  @retval     EFI_INVALID_PARAMETER    Distination pointer is not NULL.
  @retval     EFI_BUFFER_TOO_SMALL     StrBuffSize is zero.

**/
EFI_STATUS
SmbiosStrInit (
  OUT CHAR16        **Destination,
  IN  CHAR16  CONST *Source,
  OUT CHAR16        **StrBuffer,
  OUT UINTN         *Count,
  OUT UINTN         *SizeOfStrings,
  IN OUT UINTN      *StrBuffSize
  );

/**
  Update SMBIOS strings.

  @param[in]  **StringArray             The strings to be updated.
  @param[in]  *StarAddr                 The pointer of strat location.
  @param[in]  NumOfStrings              The number of strings.
**/
VOID
SmbiosStringsUpdate (
  CHAR16            **StringArray,
  UINT8             *StartAddr,
  UINTN             NumOfStrings,
  UINTN             BufferSize
  );

/**
  Create Dynamic SMBIOS Table and store data.

  @retval EFI_SUCCESS                Structure created sucessfully.
  @retval EFI_NOT_READY              Some of The SMBIOS records was not available yet.
  @retval EFI_OUT_OF_RESOURCES       No enough memory. sdg

**/
EFI_STATUS
EFIAPI
CreateDynamicSmbiosTable (
  VOID
  );

/**
  Add SMBIOS Table at Dynamically.

  @param[in] Event   - Event whose notification function is being invoked (Ready To Boot).
  @param[in] Context - Pointer to the notification functions context, which is implementation dependent.

**/
VOID
EFIAPI
DynamicTable(
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

//
// BUGBUG: Following definitions are defined in Smbios spec and should be defined in IndustryStardard/Smbios.h
//

//
// Misc. Hardware Security - SMBIOS Type 24
//

typedef enum {
  EfiHardwareSecurityStatusDisabled       = 0,
  EfiHardwareSecurityStatusEnabled        = 1,
  EfiHardwareSecurityStatusNotImplemented = 2,
  EfiHardwareSecurityStatusUnknown        = 3
} EFI_MISC_HARDWARE_SECURITY_STATUS;
#endif

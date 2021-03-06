/** @file
  A library for managing the UEFI Variable default data HOB in PEI.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#ifndef _UEFI_VARIABLE_DEFAULT_HOB_LIB_H_
#define _UEFI_VARIABLE_DEFAULT_HOB_LIB_H_

#include <PiPei.h>
#include <Uefi.h>
#include <Guid/VariableFormat.h>

/**
  Find variable from default variable HOB.

  @param[in]  VariableName      A Null-terminated string that is the name of the vendor's
                                variable.
  @param[in]  VendorGuid        A unique identifier for the vendor.
  @param[out] AuthFlag          Pointer to output Authenticated variable flag.

  @return Pointer to variable header, NULL if not found.

**/
AUTHENTICATED_VARIABLE_HEADER *
EFIAPI
FindVariableFromHob (
  IN CHAR16                     *VariableName,
  IN EFI_GUID                   *VendorGuid,
  OUT BOOLEAN                   *AuthFlag
  );

/**
  Get variable from default variable HOB.

  @param[in]      VariableName  A Null-terminated string that is the name of the vendor's
                                variable.
  @param[in]      VendorGuid    A unique identifier for the vendor.
  @param[out]     Attributes    If not NULL, a pointer to the memory location to return the
                                attributes bitmask for the variable.
  @param[in, out] DataSize      On input, the size in bytes of the return Data buffer.
                                On output the size of data returned in Data.
  @param[out]     Data          The buffer to return the contents of the variable.

  @retval EFI_SUCCESS           The function completed successfully.
  @retval EFI_NOT_FOUND         The variable was not found.
  @retval EFI_BUFFER_TOO_SMALL  The DataSize is too small for the result.
  @retval EFI_INVALID_PARAMETER VariableName is NULL.
  @retval EFI_INVALID_PARAMETER VendorGuid is NULL.
  @retval EFI_INVALID_PARAMETER DataSize is NULL.
  @retval EFI_INVALID_PARAMETER The DataSize is not too small and Data is NULL.

**/
EFI_STATUS
EFIAPI
GetVariableFromHob (
  IN     CHAR16                 *VariableName,
  IN     EFI_GUID               *VendorGuid,
  OUT    UINT32                 *Attributes, OPTIONAL
  IN OUT UINTN                  *DataSize,
  OUT    VOID                   *Data
  );

/**
  Set variable to default variable HOB.

  @param[in] VariableName       A Null-terminated string that is the name of the vendor's
                                variable.
  @param[in] VendorGuid         A unique identifier for the vendor.
  @param[in] Attributes         If not NULL, a pointer to the memory location to set the
                                attributes bitmask for the variable.
  @param[in] DataSize           On input, the size in bytes of the return Data buffer.
                                On output the size of data returned in Data.
  @param[in] Data               The buffer to return the contents of the variable.

  @retval EFI_SUCCESS           The function completed successfully.
  @retval EFI_NOT_FOUND         The variable was not found.
  @retval EFI_INVALID_PARAMETER VariableName is NULL.
  @retval EFI_INVALID_PARAMETER VendorGuid is NULL.
  @retval EFI_INVALID_PARAMETER Attributes is not NULL, but attributes value is 0.
  @retval EFI_INVALID_PARAMETER DataSize is not equal to the variable data size.
  @retval EFI_INVALID_PARAMETER The DataSize is equal to the variable data size, but Data is NULL.

**/
EFI_STATUS
EFIAPI
SetVariableToHob (
  IN CHAR16                     *VariableName,
  IN EFI_GUID                   *VendorGuid,
  IN UINT32                     *Attributes, OPTIONAL
  IN UINTN                      DataSize,
  IN VOID                       *Data
  );

/**
  Convert Authenticated variable to normal variable data.

  @param PeiServices       General purpose services available to every PEIM.
  @param NotifyDescriptor  Notify that this module published.
  @param Ppi               PPI that was installed.

  @return EFI_SUCCESS      The function completed successfully.

**/
EFI_STATUS
EFIAPI
BuildDefaultDataHobForRecoveryVariable (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  );

/**
  This function finds the matched default data and create GUID hob for it.

  @param[in] DefaultId         - Specifies the type of defaults to retrieve.

  @return EFI_SUCCESS          - The matched default data is found.
  @return EFI_NOT_FOUND        - The matched default data is not found.
  @return EFI_OUT_OF_RESOURCES - No enough resource to create HOB.

**/
EFI_STATUS
EFIAPI
CreateDefaultVariableHob (
  IN UINT16  DefaultId
#if FixedPcdGetBool(PcdBfxEnable) == 1
  , IN  UINTN  ExtraHobSpace   OPTIONAL
#endif
  );

#endif

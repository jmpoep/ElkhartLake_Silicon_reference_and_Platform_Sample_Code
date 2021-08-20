/** @file
  Implementation of managing the UEFI Variable default data HOB in PEI.

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

#include "UefiVariableDefaultHob.h"

#include <PiPei.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/UefiVariableDefaultHobLib.h>
#include <Library/UefiVariableHelperLib.h>
#include <Ppi/ReadOnlyVariable2.h>

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

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mMemoryNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiMemoryDiscoveredPpiGuid,
  BuildDefaultDataHobForRecoveryVariable
};

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
  )
{
  EFI_HOB_GUID_TYPE             *GuidHob;
  VARIABLE_STORE_HEADER         *VariableStoreHeader;
  AUTHENTICATED_VARIABLE_HEADER *StartPtr;
  AUTHENTICATED_VARIABLE_HEADER *EndPtr;
  AUTHENTICATED_VARIABLE_HEADER *CurrPtr;
  VOID                          *Point;

  VariableStoreHeader = NULL;

  GuidHob = GetFirstGuidHob (&gEfiAuthenticatedVariableGuid);
  if (GuidHob != NULL) {
    VariableStoreHeader = (VARIABLE_STORE_HEADER *) GET_GUID_HOB_DATA (GuidHob);
    *AuthFlag = TRUE;
  } else {
    GuidHob = GetFirstGuidHob (&gEfiVariableGuid);
    if (GuidHob != NULL) {
      VariableStoreHeader = (VARIABLE_STORE_HEADER *) GET_GUID_HOB_DATA (GuidHob);
      *AuthFlag = FALSE;
    }
  }
  ASSERT (VariableStoreHeader != NULL);
  if (VariableStoreHeader == NULL) {
    return NULL;
  }

  StartPtr = GetStartPointer (VariableStoreHeader);
  EndPtr   = GetEndPointer (VariableStoreHeader);
  for ( CurrPtr = StartPtr
      ; (CurrPtr < EndPtr) && IsValidVariableHeader (CurrPtr)
      ; CurrPtr = GetNextVariablePtr (CurrPtr, *AuthFlag)
      ) {
    if (CurrPtr->State == VAR_ADDED) {
      if (CompareGuid (VendorGuid, GetVendorGuidPtr (CurrPtr, *AuthFlag))) {
        Point = (VOID *) GetVariableNamePtr (CurrPtr, *AuthFlag);

        ASSERT (NameSizeOfVariable (CurrPtr, *AuthFlag) != 0);
        if (CompareMem (VariableName, Point, NameSizeOfVariable (CurrPtr, *AuthFlag)) == 0) {
          return CurrPtr;
        }
      }
    }
  }

  return NULL;
}

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
  )
{
  BOOLEAN                       AuthFlag;
  AUTHENTICATED_VARIABLE_HEADER *Variable;
  UINTN                         VarDataSize;

  if ((VariableName == NULL) || (VendorGuid == NULL) || (DataSize == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Variable = FindVariableFromHob (VariableName, VendorGuid, &AuthFlag);
  if (Variable == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Get data size
  //
  VarDataSize = DataSizeOfVariable (Variable, AuthFlag);
  if (*DataSize >= VarDataSize) {
    if (Data == NULL) {
      return EFI_INVALID_PARAMETER;
    }

    CopyMem (Data, GetVariableDataPtr (Variable, AuthFlag), VarDataSize);

    if (Attributes != NULL) {
      *Attributes = Variable->Attributes;
    }

    *DataSize = VarDataSize;
    return EFI_SUCCESS;
  } else {
    *DataSize = VarDataSize;
    return EFI_BUFFER_TOO_SMALL;
  }
}

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
  )
{
  BOOLEAN                       AuthFlag;
  AUTHENTICATED_VARIABLE_HEADER *Variable;
  UINTN                         VarDataSize;

  if (VariableName == NULL || VariableName[0] == 0 || VendorGuid == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Variable = FindVariableFromHob (VariableName, VendorGuid, &AuthFlag);
  if (Variable == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Get data size
  //
  VarDataSize = DataSizeOfVariable (Variable, AuthFlag);
  if (DataSize == VarDataSize) {
    if (Data == NULL) {
      return EFI_INVALID_PARAMETER;
    }

    if (Attributes != NULL) {
      if (*Attributes == 0) {
        return EFI_INVALID_PARAMETER;
      }
      Variable->Attributes = *Attributes;
    }

    CopyMem (GetVariableDataPtr (Variable, AuthFlag), Data, VarDataSize);

    return EFI_SUCCESS;
  } else {
    return EFI_INVALID_PARAMETER;
  }
}

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
  )
{
  EFI_HOB_GUID_TYPE             *GuidHob;
  VARIABLE_STORE_HEADER         *AuthVarStoreHeader;
  VARIABLE_STORE_HEADER         *VarStoreHeader;
  UINT32                        VarStoreSize;
  AUTHENTICATED_VARIABLE_HEADER *AuthStartPtr;
  AUTHENTICATED_VARIABLE_HEADER *AuthEndPtr;
  AUTHENTICATED_VARIABLE_HEADER *AuthVariable;
  VARIABLE_HEADER               *Variable;
  UINT8                         *AuthVariablePtr;
  UINT8                         *VariablePtr;

  GuidHob = GetFirstGuidHob (&gEfiAuthenticatedVariableGuid);
  AuthVarStoreHeader = (VARIABLE_STORE_HEADER *) GET_GUID_HOB_DATA (GuidHob);
  //
  // Go through AuthVarStore to calculate the required size for normal varstore.
  //
  VarStoreSize = sizeof (VARIABLE_STORE_HEADER);
  AuthStartPtr = GetStartPointer (AuthVarStoreHeader);
  AuthEndPtr   = GetEndPointer (AuthVarStoreHeader);
  AuthVariable = AuthStartPtr;
  while ((AuthVariable < AuthEndPtr) && IsValidVariableHeader (AuthVariable)) {
    if (AuthVariable->State == VAR_ADDED) {
      VarStoreSize = HEADER_ALIGN (VarStoreSize);
      VarStoreSize += sizeof (VARIABLE_HEADER);
      VarStoreSize += AuthVariable->NameSize + GET_PAD_SIZE (AuthVariable->NameSize);
      VarStoreSize += AuthVariable->DataSize + GET_PAD_SIZE (AuthVariable->DataSize);
    }
    AuthVariable = GetNextVariablePtr (AuthVariable, TRUE);
  }

  //
  // Create HOB data for normal variable storage.
  // Allocate more data for header alignment.
  //
  VarStoreSize   = VarStoreSize + HEADER_ALIGNMENT - 1;
  VarStoreHeader = (VARIABLE_STORE_HEADER *) BuildGuidHob (&gEfiVariableGuid, VarStoreSize);
  ASSERT (VarStoreHeader != NULL);
  if (VarStoreHeader == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  CopyGuid (&VarStoreHeader->Signature, &gEfiVariableGuid);
  VarStoreHeader->Format = AuthVarStoreHeader->Format;
  VarStoreHeader->State  = AuthVarStoreHeader->State;

  //
  // Copy variable data from AuthVarStore to NormalVarStore
  //
  AuthVariable = AuthStartPtr;
  VariablePtr  = (UINT8 *) (VarStoreHeader + 1);
  while ((AuthVariable < AuthEndPtr) && IsValidVariableHeader (AuthVariable)) {
    if (AuthVariable->State == VAR_ADDED) {
      Variable = (VARIABLE_HEADER *) HEADER_ALIGN ((UINTN) VariablePtr);
      //
      // Copy variable header
      //
      Variable->StartId    = AuthVariable->StartId;
      Variable->State      = AuthVariable->State;
      Variable->Reserved   = AuthVariable->Reserved;
      Variable->Attributes = AuthVariable->Attributes;
      Variable->NameSize   = AuthVariable->NameSize;
      Variable->DataSize   = AuthVariable->DataSize;
      CopyGuid (&Variable->VendorGuid, &AuthVariable->VendorGuid);
      //
      // Copy variable Name and Data
      //
      VariablePtr     = (UINT8 *) (Variable + 1);
      AuthVariablePtr = (UINT8 *) (AuthVariable + 1);
      CopyMem (VariablePtr, AuthVariablePtr, Variable->NameSize);
      VariablePtr     = VariablePtr + Variable->NameSize + GET_PAD_SIZE (Variable->NameSize);
      AuthVariablePtr = AuthVariablePtr + AuthVariable->NameSize + GET_PAD_SIZE (AuthVariable->NameSize);
      CopyMem (VariablePtr, AuthVariablePtr, Variable->DataSize);
      VariablePtr     = VariablePtr + Variable->DataSize + GET_PAD_SIZE (Variable->DataSize);
    }
    AuthVariable = GetNextVariablePtr (AuthVariable, TRUE);
  }

  //
  // Update Variable Storage Size
  //
  VarStoreHeader->Size = (UINT32) ((UINTN) VariablePtr - (UINTN) VarStoreHeader);

  return EFI_SUCCESS;
}

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
  IN  UINT16  DefaultId
#if FixedPcdGetBool(PcdBfxEnable) == 1
  ,IN  UINTN   ExtraHobSpace   OPTIONAL
#endif
  )
{
  UINTN                      FvInstance;
  EFI_FIRMWARE_VOLUME_HEADER *FvHeader;
  EFI_FFS_FILE_HEADER        *FfsHeader;
  UINT32                     FileSize;
  EFI_COMMON_SECTION_HEADER  *Section;
  UINT32                     SectionLength;
  EFI_STATUS                 Status;
  BOOLEAN                    DefaultSettingIsFound;
  DEFAULT_DATA               *DefaultData;
  DEFAULT_INFO               *DefaultInfo;
  VARIABLE_STORE_HEADER      *VarStoreHeader;
  VARIABLE_STORE_HEADER      *VarStoreHeaderHob;
  UINT8                      *VarHobPtr;
  UINT8                      *VarPtr;
  UINT32                     VarDataOffset;
  UINT32                     VarHobDataOffset;
  EFI_BOOT_MODE              BootMode;
  BOOLEAN                    IsFirstSection;
  DATA_DELTA                 *DataDelta;
  UINTN                      DataDeltaSize;
  UINTN                      Index;
  CONST EFI_PEI_SERVICES     **PeiServices;

  //
  // Get PeiService pointer
  //
  PeiServices = GetPeiServicesTablePointer ();

  //
  // Find the FFS file that stores all default data.
  //
  DefaultSettingIsFound = FALSE;
  FvInstance            = 0;
  FfsHeader             = NULL;
  while (((*PeiServices)->FfsFindNextVolume (PeiServices, FvInstance, (VOID **) &FvHeader) == EFI_SUCCESS) &&
         (!DefaultSettingIsFound)) {
    FfsHeader = NULL;
    while ((*PeiServices)->FfsFindNextFile (PeiServices, EFI_FV_FILETYPE_FREEFORM, FvHeader, (VOID **) &FfsHeader) == EFI_SUCCESS) {
      if (CompareGuid ((EFI_GUID *) FfsHeader, &gDefaultDataOptSizeFileGuid)) {
        DefaultSettingIsFound = TRUE;
        break;
      }
    }
    FvInstance++;
  }

  //
  // FFS file is not found.
  //
  if (!DefaultSettingIsFound) {
    return EFI_NOT_FOUND;
  }

  //
  // Find the matched default data for the input default ID and plat ID.
  //
  DefaultSettingIsFound = FALSE;
  VarStoreHeaderHob     = NULL;
  VarHobPtr             = NULL;
  DataDelta             = NULL;
  DataDeltaSize         = 0;
  IsFirstSection        = TRUE;
  VarStoreHeader        = NULL;
  Section               = (EFI_COMMON_SECTION_HEADER *)(FfsHeader + 1);
  FileSize              = *(UINT32 *)(FfsHeader->Size) & 0x00FFFFFF;

  while (((UINTN) Section < (UINTN) FfsHeader + FileSize) && !DefaultSettingIsFound) {
    DefaultData   = (DEFAULT_DATA *) (Section + 1);
    DefaultInfo   = &(DefaultData->DefaultInfo[0]);
    SectionLength = *(UINT32 *)Section->Size & 0x00FFFFFF;

    if (IsFirstSection) {
      //
      // Create HOB to store default data so that Variable driver can use it.
      // Allocate more data for header alignment.
      //
      VarStoreHeader = (VARIABLE_STORE_HEADER *) ((UINT8 *) DefaultData + DefaultData->HeaderSize);
      VarStoreHeaderHob = (VARIABLE_STORE_HEADER *) BuildGuidHob (
                                                      &VarStoreHeader->Signature,
                                                      (VarStoreHeader->Size
#if FixedPcdGetBool(PcdBfxEnable) == 1
                                                       + ExtraHobSpace
#endif
                                                      ) + HEADER_ALIGNMENT - 1
                                                      );
      if (VarStoreHeaderHob == NULL) {
        //
        // No enough hob resource.
        //
        return EFI_OUT_OF_RESOURCES;
      }

      //
      // Copy variable storage header.
      //
      CopyMem (VarStoreHeaderHob, VarStoreHeader, sizeof (VARIABLE_STORE_HEADER));
      //
      // Copy variable data.
      //
      VarPtr           = (UINT8 *) HEADER_ALIGN ((UINTN) (VarStoreHeader + 1));
      VarDataOffset    = (UINT32) ((UINTN) VarPtr - (UINTN) VarStoreHeader);
      VarHobPtr        = (UINT8 *) HEADER_ALIGN ((UINTN) (VarStoreHeaderHob + 1));
      VarHobDataOffset = (UINT32) ((UINTN) VarHobPtr - (UINTN) VarStoreHeaderHob);
      CopyMem (VarHobPtr, VarPtr, VarStoreHeader->Size - VarDataOffset);
      //
      // Update variable size.
      //
      VarStoreHeaderHob->Size = VarStoreHeader->Size - VarDataOffset + VarHobDataOffset;

      //
      // Update Delta Data
      //
      VarHobPtr = (UINT8 *) VarStoreHeaderHob - VarDataOffset + VarHobDataOffset;
    } else {
      //
      // Apply delta setting
      //
      DataDelta     = (DATA_DELTA *) ((UINT8 *) DefaultData + DefaultData->HeaderSize);
      DataDeltaSize = SectionLength - sizeof (EFI_COMMON_SECTION_HEADER) - DefaultData->HeaderSize;
      for (Index = 0; Index < DataDeltaSize / sizeof (DATA_DELTA); Index++) {
        *((UINT8 *) VarHobPtr + DataDelta[Index].Offset) = DataDelta[Index].Value;
      }
    }

    //
    // Find the matched DefaultId
    //
    while ((UINTN) DefaultInfo < (UINTN) DefaultData + DefaultData->HeaderSize) {
      if (DefaultInfo->DefaultId == DefaultId) {
        DefaultSettingIsFound = TRUE;
        break;
      }
      DefaultInfo++;
    }
    //
    // Size is 24 bits wide so mask upper 8 bits.
    // SectionLength is adjusted it is 4 byte aligned.
    // Go to the next section
    //
    SectionLength = (SectionLength + 3) & (~3);
    ASSERT (SectionLength != 0);
    Section = (EFI_COMMON_SECTION_HEADER *)((UINT8 *)Section + SectionLength);
    IsFirstSection = FALSE;
  }
  //
  // Matched default data is not found.
  //
  if (!DefaultSettingIsFound) {
    //
    // Change created HOB type to be unused.
    //
    if (VarStoreHeaderHob != NULL) {
      ((EFI_HOB_GUID_TYPE *)((UINT8 *) VarStoreHeaderHob - sizeof (EFI_HOB_GUID_TYPE)))->Header.HobType = EFI_HOB_TYPE_UNUSED;
    }
    return EFI_NOT_FOUND;
  }

  //
  // On recovery boot mode, emulation variable driver will be used.
  // But, Emulation variable only knows normal variable data format.
  // So, if the default variable data format is authenticated, it needs to be converted to normal data.
  //
  Status = (*PeiServices)->GetBootMode (PeiServices, &BootMode);
  if (BootMode == BOOT_IN_RECOVERY_MODE &&
      CompareGuid (&VarStoreHeader->Signature, &gEfiAuthenticatedVariableGuid)) {
    Status = (**PeiServices).NotifyPpi (PeiServices, &mMemoryNotifyList);
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}

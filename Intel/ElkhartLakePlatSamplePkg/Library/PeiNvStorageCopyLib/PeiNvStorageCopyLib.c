/** @file
  This file contains the implementation of the NvStorageCopy library.

  The library copies data from the NvStorage Firmware Volume to the default
  variable HOB.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification
**/

#include <Uefi.h>
#include <Guid/SystemNvDataGuid.h>
#include <Guid/VariableFormat.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>


/**
  Copies UEFI variable data from the given firmware volume to the default variable HOB.

  The default variable HOB must have been created with a size to accommodate the variable data
  copied by this function.

  @param[in]  NvStorageFvHeader   Pointer to the NV Storage firmware volume.

  @retval EFI_SUCCESS             The function completed successfully.
  @retval EFI_INVALID_PARAMETER   The NvStorageFvHeader firmware volume is invalid or the variable store is invalid.
  @retval EFI_NOT_READY           The default variable HOB was not found or the data in the HOB is invalid.

**/
EFI_STATUS
EFIAPI
CopyNvStorageDataToDefaultVariableHob (
  IN CONST EFI_FIRMWARE_VOLUME_HEADER *NvStorageFvHeader
  )
{
  EFI_HOB_GUID_TYPE                 *GuidHob;
  EFI_PHYSICAL_ADDRESS              VariableStoreBase;
  EFI_GUID                          VariableGuid;
  UINT8                             VariableState;

  BOOLEAN                           AuthenticatedVariableStore  = FALSE;

  UINT32                            VariableHeaderSize          = 0;
  UINT32                            VariableNameSize            = 0;
  UINT32                            VariableDataSize            = 0;

  CHAR16                            *VariableName               = NULL;
  UINT8                             *VariableDataPtr            = NULL;
  UINT8                             *UnusedHobSpaceStartPtr     = NULL;

  VARIABLE_STORE_HEADER             *NvStoreHeader              = NULL;
  VARIABLE_STORE_HEADER             *VariableHobHeader          = NULL;
  VARIABLE_HEADER                   *StartPtr                   = NULL;
  VARIABLE_HEADER                   *CurrPtr                    = NULL;
  VARIABLE_HEADER                   *EndPtr                     = NULL;

  //
  // We only need to copy the contents of NvStorage to the default HOB if CSE-assisted or emulated variables are used
  //
  if (
    (!PcdGetBool (PcdEnableCseVariableStorage) || PcdGetBool (PcdEnableFvbVariableStorage)) &&
    !PcdGetBool (PcdNvVariableEmulationMode)
    ) {
    DEBUG ((DEBUG_INFO, "Skipping NvStorage Vital Product Data copy due to boot type.\n"));
    return EFI_SUCCESS;
  }

  if (
    NvStorageFvHeader == NULL ||
    NvStorageFvHeader->Signature != EFI_FVH_SIGNATURE ||
    !CompareGuid (&gEfiSystemNvDataFvGuid, &NvStorageFvHeader->FileSystemGuid)
    ) {
    DEBUG ((DEBUG_ERROR, "The NvStorage firmware volume is invalid!\n"));
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((DEBUG_INFO, "Preparing to copy NvStorage Vital Product Data to the default variable HOB.\n"));
  DEBUG ((DEBUG_INFO, "  NvStorageFvHeader at 0x%x\n", (UINTN) NvStorageFvHeader));

  VariableStoreBase = (EFI_PHYSICAL_ADDRESS) ((UINTN) NvStorageFvHeader + NvStorageFvHeader->HeaderLength);
  NvStoreHeader     = (VARIABLE_STORE_HEADER *) (UINTN) VariableStoreBase;

  AuthenticatedVariableStore = (BOOLEAN) CompareGuid (&NvStoreHeader->Signature, &gEfiAuthenticatedVariableGuid);
  VariableHeaderSize = (AuthenticatedVariableStore) ? sizeof (AUTHENTICATED_VARIABLE_HEADER) : sizeof (VARIABLE_HEADER);

  GuidHob = GetFirstGuidHob (&gEfiAuthenticatedVariableGuid);
  if (GuidHob != NULL) {
    ASSERT (AuthenticatedVariableStore);
    if (!AuthenticatedVariableStore) {
      return EFI_INVALID_PARAMETER;
    }
    VariableHobHeader           = (VARIABLE_STORE_HEADER *) GET_GUID_HOB_DATA (GuidHob);
    AuthenticatedVariableStore  = TRUE;
  } else {
    GuidHob = GetFirstGuidHob (&gEfiVariableGuid);
    if (GuidHob != NULL) {
      ASSERT (!AuthenticatedVariableStore);
      if (AuthenticatedVariableStore) {
        return EFI_INVALID_PARAMETER;
      }
      VariableHobHeader           = (VARIABLE_STORE_HEADER *) GET_GUID_HOB_DATA (GuidHob);
      AuthenticatedVariableStore  = FALSE;
    }
  }
  if (GuidHob != NULL) {
    ASSERT (VariableHobHeader != NULL);
  } else {
    //
    // If the default variable HOB is not found no data needs to be copied
    //
    return EFI_SUCCESS;
  }
  if (VariableHobHeader == NULL) {
    return EFI_NOT_READY;
  }

  //
  // Find the Setup variable within the HOB, as well as the start pointer of the unused space in the HOB
  //
  StartPtr  = (VARIABLE_HEADER *) HEADER_ALIGN (VariableHobHeader + 1);
  EndPtr    = (VARIABLE_HEADER *) HEADER_ALIGN (
                                    (CHAR8 *) VariableHobHeader + VariableHobHeader->Size + PcdGet32 (PcdNvStorageVpdSize)
                                    );
  DEBUG ((DEBUG_INFO, "  Default variable HOB StartPtr at 0x%x. EndPtr at 0x%x\n", (UINTN) StartPtr, (UINTN) EndPtr));
  ASSERT (StartPtr < EndPtr);

  CurrPtr = StartPtr;
  while (
    (CurrPtr != NULL) &&
    (CurrPtr <= EndPtr) &&
    (CurrPtr->StartId == VARIABLE_DATA)
    ) {
    VariableName = (CHAR16 *) ((CHAR8 *) ((CHAR8 *) CurrPtr + VariableHeaderSize));
    if (!AuthenticatedVariableStore) {
      VariableNameSize = CurrPtr->NameSize;
      VariableDataSize = CurrPtr->DataSize;
      VariableGuid     = CurrPtr->VendorGuid;
      VariableState    = CurrPtr->State;
    } else {
      VariableNameSize = ((AUTHENTICATED_VARIABLE_HEADER *) CurrPtr)->NameSize;
      VariableDataSize = ((AUTHENTICATED_VARIABLE_HEADER *) CurrPtr)->DataSize;
      VariableGuid     = ((AUTHENTICATED_VARIABLE_HEADER *) CurrPtr)->VendorGuid;
      VariableState    = ((AUTHENTICATED_VARIABLE_HEADER *) CurrPtr)->State;
    }
    VariableDataPtr = (UINT8 *) (((CHAR8 *) CurrPtr + VariableHeaderSize) +
                                  VariableNameSize + GET_PAD_SIZE (VariableNameSize));

    DEBUG ((DEBUG_INFO, "  VariableDataPtr at 0x%x.\n", (UINTN) VariableDataPtr));
    DEBUG ((DEBUG_INFO, "    Variable name is %s.\n", VariableName));
    DEBUG ((DEBUG_INFO, "    Variable data size is %d bytes.\n", VariableDataSize));

    CurrPtr = (VARIABLE_HEADER *) HEADER_ALIGN (
                                    (CHAR8 *) VariableDataPtr +
                                    VariableDataSize +
                                    GET_PAD_SIZE (VariableDataSize)
                                    );
  }
  UnusedHobSpaceStartPtr = (UINT8 *) CurrPtr;

  ASSERT (PcdGet32 (PcdNvStorageVpdSize) <= ((UINTN) EndPtr) - ((UINTN) UnusedHobSpaceStartPtr));
  if (PcdGet32 (PcdNvStorageVpdSize) > ((UINTN) EndPtr) - ((UINTN) UnusedHobSpaceStartPtr)) {
    return EFI_NOT_READY;
  }
  CopyMem ((VOID *) UnusedHobSpaceStartPtr, (VOID *) HEADER_ALIGN (NvStoreHeader + 1), PcdGet32 (PcdNvStorageVpdSize));
  VariableHobHeader->Size += PcdGet32 (PcdNvStorageVpdSize);

  return EFI_SUCCESS;
}
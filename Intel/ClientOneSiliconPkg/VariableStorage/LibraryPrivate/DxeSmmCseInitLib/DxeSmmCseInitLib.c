/** @file
  DXE/SMM CSE Variable Storage Initialization Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

@par Specification Reference:
**/

#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/VariableNvmStorageLib.h>
#include <Library/CseVariableStorageGeneralDataLib.h>
#include <Library/CseVariableStorageLib.h>

/**
  Loads the CSE variable storage store index area from a HOB.

  @param[in]      CseVariableStorageStore     A pointer to a structure that contains CSE variable storage info.
  @param[out]     IndexAreaBuffer             A pointer to the caller allocated buffer for the index area contents.
  @param[in,out]  IndexAreaBufferLength       The size in bytes of the caller allocated buffer for the index area contents.

  @retval         EFI_SUCCESS                 The variable store was loaded successfully.
  @retval         EFI_INVALID_PARAMETER       A pointer parameter given was NULL.
  @retval         EFI_BUFFER_TOO_SMALL        The buffer length given is too small to hold the index area.
  @retval         EFI_NOT_FOUND               The HOB was not found or the HOB data was empty.
  @retval         EFI_LOAD_ERROR              The HOB data was found but the variable store is not valid.
  @retval         Others                      An error occurred loading the variable store.
**/
EFI_STATUS
EFIAPI
CseVariableStorageLoadIndexAreaFromHob (
  IN CONST  CSE_VARIABLE_STORAGE_STORE  *CseVariableStorageStore,
  OUT       VOID                        *IndexAreaBuffer,
  IN OUT    UINTN                       *IndexAreaBufferLength
  )
{
  UINTN                       HobDataSize;
  VOID                        *HobIndexArea = NULL;
  EFI_HOB_GUID_TYPE           *IndexAreaHob = NULL;

  DEBUG ((DEBUG_INFO, "Checking for a %a variable store in a HOB.\n", CseVariableStorageStore->Info.Name));

  if (CseVariableStorageStore == NULL || IndexAreaBuffer == NULL || IndexAreaBufferLength == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (*IndexAreaBufferLength < sizeof (VARIABLE_NVM_STORE_HEADER)) {
    return EFI_BUFFER_TOO_SMALL;
  }

  IndexAreaHob = GetFirstGuidHob (&CseVariableStorageStore->Info.Guid);
  if (IndexAreaHob == NULL) {
    return EFI_NOT_FOUND;
  }

  HobDataSize = GET_GUID_HOB_DATA_SIZE (IndexAreaHob);
  if (*IndexAreaBufferLength < HobDataSize) {
    *IndexAreaBufferLength = HobDataSize;
    return EFI_BUFFER_TOO_SMALL;
  }

  HobIndexArea = GET_GUID_HOB_DATA (IndexAreaHob);
  if (HobIndexArea == NULL) {
    return EFI_NOT_FOUND;
  } else if (GetVariableStoreStatus ((VARIABLE_NVM_STORE_HEADER *) HobIndexArea) != EfiValid) {
    return EFI_LOAD_ERROR;
  }

  CopyMem (IndexAreaBuffer, HobIndexArea, HobDataSize);

  return EFI_SUCCESS;
}

/**
  Loads a variable Data from the specified CSE non-volatile store.

  @param[in]      CseVariableStorageStore     A pointer to a structure that contains CSE variable storage info.
  @param[out]     IndexAreaBuffer             A pointer to the caller allocated buffer for the index area contents.
  @param[in,out]  DataAreaBufferLength       The size in bytes of the caller allocated buffer for the index area contents.
  @param[in ]     DataAreaBufferOffset       Data Offset to read the Data from Cse Variable store

  @retval         EFI_SUCCESS                 The variable store was loaded successfully.
  @retval         EFI_INVALID_PARAMETER       A pointer parameter given was NULL.
  @retval         EFI_BUFFER_TOO_SMALL        The buffer length given is too small to hold the index area.
  @retval         EFI_NOT_FOUND               A valid variable store was not found.
  @retval         Others                      An error occurred loading the variable store.
**/
EFI_STATUS
EFIAPI
CseVariableStorageLoadDataAreaFromNvm (
  IN CONST  CSE_VARIABLE_STORAGE_STORE  *CseVariableStorageStore,
  OUT       UINT8                       *DataAreaBuffer,
  IN OUT    UINTN                       *DataAreaBufferLength,
  IN        UINTN                       DataAreaBufferOffset
  )
{
  EFI_STATUS                  Status;
  UINTN                       DataSize;
  UINTN                       TotalDataProcessed;

 if (CseVariableStorageStore == NULL || DataAreaBuffer == NULL || DataAreaBufferLength == NULL || (DataAreaBufferOffset > CseVariableStorageStore->Info.MaximumSize)) {
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((DEBUG_INFO, "Checking for a %a variable Data on non-volatile media.\n", CseVariableStorageStore->Info.Name));
  TotalDataProcessed = 0;
  DataSize = 0;

  while (TotalDataProcessed < *DataAreaBufferLength) {
    if ((*DataAreaBufferLength - TotalDataProcessed) > CSE_VARIABLE_MAX_DMA_SIZE) {
      DataSize = CSE_VARIABLE_MAX_DMA_SIZE;
    } else {
      DataSize = *DataAreaBufferLength - TotalDataProcessed;
    }

    Status = CseVariableStorageStore->Read (
      CseVariableStorageStore,
      (VOID *)(DataAreaBuffer + TotalDataProcessed),
      &DataSize,
      (UINT32)(TotalDataProcessed + DataAreaBufferOffset),
      NULL
      );
    if (EFI_ERROR (Status)) {
      DEBUG ((
        DEBUG_ERROR,
        "Error occurred reading from the %a CSE variable store. Read operation aborted. Status = %r.\n",
        CseVariableStorageStore->Info.Name,
        Status
        ));
      ASSERT_EFI_ERROR(Status);
      goto Done;
    }

    TotalDataProcessed += DataSize;
  }
Done:
  return Status;
}

/**
  Loads a variable store from the specified CSE non-volatile store.

  @param[in]      CseVariableStorageStore     A pointer to a structure that contains CSE variable storage info.
  @param[out]     IndexAreaBuffer             A pointer to the caller allocated buffer for the index area contents.
  @param[in,out]  IndexAreaBufferLength       The size in bytes of the caller allocated buffer for the index area contents.

  @retval         EFI_SUCCESS                 The variable store was loaded successfully.
  @retval         EFI_INVALID_PARAMETER       A pointer parameter given was NULL.
  @retval         EFI_BUFFER_TOO_SMALL        The buffer length given is too small to hold the index area.
  @retval         EFI_NOT_FOUND               A valid variable store was not found.
  @retval         Others                      An error occurred loading the variable store.
**/
EFI_STATUS
EFIAPI
CseVariableStorageLoadIndexAreaFromNvm (
  IN CONST  CSE_VARIABLE_STORAGE_STORE  *CseVariableStorageStore,
  OUT       VOID                        *IndexAreaBuffer,
  IN OUT    UINTN                       *IndexAreaBufferLength
  )
{
  EFI_STATUS                  Status;
  UINTN                       VariableStoreHeaderRegionSize;
  VARIABLE_NVM_STORE_HEADER   VariableStoreHeader;

  DEBUG ((DEBUG_INFO, "Checking for a %a variable store on non-volatile media.\n", CseVariableStorageStore->Info.Name));

  if (CseVariableStorageStore == NULL || IndexAreaBuffer == NULL || IndexAreaBufferLength == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (*IndexAreaBufferLength < sizeof (VARIABLE_NVM_STORE_HEADER)) {
    return EFI_BUFFER_TOO_SMALL;
  }

  //
  // Attempt to read a variable store header to check if a variable store exists
  //
  VariableStoreHeaderRegionSize = sizeof (VARIABLE_NVM_STORE_HEADER);
  Status = CseVariableStorageStore->Read (
                                      CseVariableStorageStore,
                                      (VOID *) &VariableStoreHeader,
                                      &VariableStoreHeaderRegionSize,
                                      0,
                                      NULL
                                      );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  ASSERT (VariableStoreHeaderRegionSize >= sizeof (VARIABLE_NVM_STORE_HEADER));

  if (GetVariableStoreStatus (&VariableStoreHeader) == EfiValid) {
    VariableStoreHeaderRegionSize += VariableStoreHeader.VariableHeaderTotalLength +
                                       NVM_GET_PAD_SIZE (VariableStoreHeader.VariableHeaderTotalLength);

    if (*IndexAreaBufferLength < VariableStoreHeaderRegionSize) {
      *IndexAreaBufferLength = VariableStoreHeaderRegionSize;
      return EFI_BUFFER_TOO_SMALL;
    }
    *IndexAreaBufferLength = VariableStoreHeaderRegionSize;

    //
    // Read the whole index area based on the length found in the store header
    //
    Status = CseVariableStorageStore->Read (CseVariableStorageStore, IndexAreaBuffer, IndexAreaBufferLength, 0, NULL);
  } else {
    Status = EFI_NOT_FOUND;
  }

  return Status;
}

/**
  Loads variable index data for all enabled variable stores that exist.

  If an enabled variable store does not exist, a new one will be created if possible.

  @param[in,out]    CseVariableStorageStores  A pointer to a structure that contains CSE variable storage stores info.

  @retval           EFI_SUCCESS               The variable store was established successfully.
  @retval           EFI_OUT_OF_RESOURCES      Not enough memory resources available for memory allocation needed.
  @retval           Others                    The variable store could not be established.
**/
EFI_STATUS
EFIAPI
EstablishAndLoadCseVariableStores (
  IN OUT CSE_VARIABLE_STORAGE_STORE   **CseVariableStorageStores
  )
{
  EFI_STATUS                  Status;
  CSE_VARIABLE_STORAGE_TYPE   Type;
  UINTN                       IndexRegionBufferSize;
  VOID                        *VariableIndexRegionBuffer = NULL;
  UINTN                       DataRegionBufferSize;
  UINT8                       *VariableDataRegionBuffer = NULL;

  Status = EFI_SUCCESS;

  for (Type = (CSE_VARIABLE_STORAGE_TYPE) 0; Type < CseVariableStorageTypeMax; Type++) {
    if (!CseVariableStorageStores[Type]->Info.Enabled || CseVariableStorageStores[Type]->Info.Established) {
      DEBUG ((
        DEBUG_INFO,
        "Skipping establishment of %a CSE store since it is disabled or already enabled.\n",
        CseVariableStorageStores[Type]->Info.Name
        ));
      continue;
    }

    IndexRegionBufferSize = CalculateMaximumIndexRegionSize (
                              (UINTN) CseVariableStorageStores[Type]->Info.MaximumSize,
                              sizeof (VARIABLE_NVM_STORE_HEADER),
                              GetVariableHeaderSize (TRUE)
                              );
    DEBUG ((
      DEBUG_INFO,
      "Maximum index region size calculated for %a CSE store is 0x%x.\n",
      CseVariableStorageStores[Type]->Info.Name,
      IndexRegionBufferSize
      ));
    VariableIndexRegionBuffer = AllocateRuntimeZeroPool (IndexRegionBufferSize);
    if (VariableIndexRegionBuffer == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Attempt to load an existing store from a HOB if already loaded
    //
    Status = CseVariableStorageLoadIndexAreaFromHob (
               CseVariableStorageStores[Type],
               VariableIndexRegionBuffer,
               &IndexRegionBufferSize
               );
    if (!EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "Loaded the %a CSE variable store from a HOB.\n", CseVariableStorageStores[Type]->Info.Name));
    } else if (Status == EFI_NOT_FOUND) {
      //
      // Attempt to load an existing non-volatile store
      //
      Status = CseVariableStorageLoadIndexAreaFromNvm (
                 CseVariableStorageStores[Type],
                 VariableIndexRegionBuffer,
                 &IndexRegionBufferSize
                 );
      if (!EFI_ERROR (Status)) {
        DataRegionBufferSize = (((UINTN) CseVariableStorageStores[Type]->Info.MaximumSize) - IndexRegionBufferSize);

        DEBUG ((
          DEBUG_INFO,
          "Maximum Data region size calculated for %a CSE store is 0x%x.\n",
          CseVariableStorageStores[Type]->Info.Name,
          DataRegionBufferSize
          ));
        VariableDataRegionBuffer = AllocateZeroPool (DataRegionBufferSize);
        if (VariableDataRegionBuffer == NULL) {
          Status = EFI_OUT_OF_RESOURCES;
          ASSERT_EFI_ERROR (Status);
          return Status;
        }
        Status = CseVariableStorageLoadDataAreaFromNvm (
          CseVariableStorageStores[Type],
          VariableDataRegionBuffer,
          &DataRegionBufferSize,
          IndexRegionBufferSize
          );
      }
    }
    if (Status == EFI_NOT_FOUND || Status == EFI_LOAD_ERROR) {
      DEBUG ((DEBUG_INFO, "Constructing a new %a CSE variable store.\n", CseVariableStorageStores[Type]->Info.Name));
      //
      // Construct and attempt to write out an empty variable store
      //
      Status =  CseVariableStorageStores[Type]->CreateNewStore (
                                                  CseVariableStorageStores[Type],
                                                  VariableIndexRegionBuffer,
                                                  &IndexRegionBufferSize
                                                  );
    }
    if (EFI_ERROR (Status)) {
      FreePool (VariableIndexRegionBuffer);
      FreePool (VariableDataRegionBuffer);
      DEBUG ((
        DEBUG_ERROR,
        "An error occurred establishing the %a CSE variable store.\n",
        CseVariableStorageStores[Type]->Info.Name
        ));
      break;
    }
    CseVariableStorageStores[Type]->Info.Established = TRUE;
    CseVariableStorageStores[Type]->Info.Header = VariableIndexRegionBuffer;
    CseVariableStorageStores[Type]->Info.Data = (VOID *) VariableDataRegionBuffer;
    DEBUG ((DEBUG_INFO, "Established the %a CSE variable store.\n", CseVariableStorageStores[Type]->Info.Name));
  }

  return Status;
}

/**
  Initializes all CSE variable storage stores.

  @param[out]     CseVariableStorageStores  A pointer to a structure that contains CSE variable storage stores.

  @retval         EFI_SUCCESS               The CSE variable storage stores were initialized successfully.
  @retval         EFI_OUT_OF_RESOURCES      Not enough memory resources needed for allocation were available.
  @retval         Others                    An error occurred initializing the CSE variable storage stores.
**/
EFI_STATUS
EFIAPI
InitializeCseVariableStorage (
  OUT CSE_VARIABLE_STORAGE_STORE  **CseVariableStorageStores
  )
{
  EFI_STATUS                 Status;
  CSE_VARIABLE_STORAGE_TYPE  Type;

  for (Type = (CSE_VARIABLE_STORAGE_TYPE) 0; Type < CseVariableStorageTypeMax; Type++) {
    CseVariableStorageStores[Type] = AllocateRuntimeZeroPool (sizeof (CSE_VARIABLE_STORAGE_STORE));

    if (CseVariableStorageStores[Type] == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    switch (Type) {
      case CseVariableStorageTypeSecurePreMemoryArea:
        Status = InitializeCseVariableStorageSecurePreMemoryDataArea (CseVariableStorageStores[Type]);
        break;
      case CseVariableStorageTypeGeneralDataArea:
        Status = InitializeCseVariableStorageGeneralDataArea (CseVariableStorageStores[Type]);
        break;
      default:
        ASSERT (FALSE);
        break;
    }
    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      break;
    }

    DEBUG ((DEBUG_INFO, "Finished initializing the %a CSE variable store.\n", CseVariableStorageStores[Type]->Info.Name));
  }

  return Status;
}

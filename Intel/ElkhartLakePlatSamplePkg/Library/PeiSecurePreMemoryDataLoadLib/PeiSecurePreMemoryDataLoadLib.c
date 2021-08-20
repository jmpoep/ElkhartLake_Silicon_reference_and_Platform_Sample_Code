/** @file
  PEI Secure Pre-Memory Data Load Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#include <Base.h>

#include <IndustryStandard/FirmwareInterfaceTable.h>
#include <IndustryStandard/Pci.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/NemMapLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/SecurePreMemoryDataLoadLib.h>
#include <Library/VariableCacheLib.h>
#include <Register/MeRegs.h>

/**
  Wait for the IBB Data Ready bit to be set.

    @retval       EFI_SUCCESS                   The IBB Data Ready bit was set as expected.
    @retval       EFI_NOT_FOUND                 The HECI1 device could not be found so the bit could not be checked.
**/
EFI_STATUS
EFIAPI
WaitForIbbDataReady (
  VOID
  )
{
  if (PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, PCI_VENDOR_ID_OFFSET)) == 0xFFFFFFFF) {
    DEBUG ((DEBUG_ERROR, "HECI1 device not found or disabled. Cannot retrieve SPMD.\n"));
    return EFI_NOT_FOUND;
  }

  DEBUG ((DEBUG_INFO, "Preparing to load Secure Pre-Memory Data. Waiting for IBB Data Ready...\n"));
  while (
    (PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_H_GS_SHDW2)) &
    B_ME_H_GS_SHDW2_IBB_DATA_READY) == 0
    );
  DEBUG ((DEBUG_INFO, "Received IBB Data Ready.\n"));

  return EFI_SUCCESS;
}

/**
  Finds the Secure Pre-Memory Data Table and returns a pointer to the table.

  @param[out]   SecurePreMemoryDataTable      A pointer to a pointer to the Secure Pre-Memory Data Table. The pointer
                                              is NULL if SPMD was not found.

  @retval       EFI_SUCCESS                   The table was successfully located.
  @retval       EFI_NOT_FOUND                 The table could not be located.
**/
EFI_STATUS
EFIAPI
FindSecurePreMemoryData (
  OUT SECURE_PRE_MEMORY_DATA_TABLE **SecurePreMemoryDataTable
  )
{
  EFI_STATUS                      Status;
  UINT32                          EntryNum;
  UINT32                          Index;
  UINTN                           FitBase;
  FIRMWARE_INTERFACE_TABLE_ENTRY  *FitEntry;

  Status = GetFitBase (&FitBase);
  ASSERT_EFI_ERROR (Status);

  FitEntry = (FIRMWARE_INTERFACE_TABLE_ENTRY *) FitBase;
  *SecurePreMemoryDataTable = NULL;

  //
  // Basic FIT validation
  //
  if (FitEntry[0].Address != *(UINT64 *) "_FIT_   ") {
    return EFI_NOT_FOUND;
  } else if (FitEntry[0].Type != FIT_TYPE_00_HEADER) {
    return EFI_NOT_FOUND;
  }

  EntryNum = *(UINT32 *) (&FitEntry[0].Size[0]) & 0xFFFFFF;
  for (Index = 1; Index < EntryNum; Index++) {
    if (FitEntry[Index].Type == FIT_TYPE_10_CSE_SECURE_BOOT && FitEntry[Index].Reserved == SECURE_PRE_MEMORY_DATA_FIT_ENTRY_RSVD_TYPE) {
      *SecurePreMemoryDataTable = (SECURE_PRE_MEMORY_DATA_TABLE *) (VOID *) ((UINTN) FitEntry[Index].Address);
      return EFI_SUCCESS;
    }
  }

  return EFI_NOT_FOUND;
}

/**
  Prints a binary buffer of data.

  @param[in]    Buffer            A pointer to the buffer of data.
  @param[in]    BufferSize        The size of the buffer of data.

  @retval       None
**/
STATIC
VOID
EFIAPI
PrintBinaryBuffer (
  IN        UINT8*      Buffer,
  IN        UINTN       BufferSize
  )
{
  UINTN     CurrentByte = 0;

  if (BufferSize == 0) {
    DEBUG ((DEBUG_INFO, "Skipping print of 0 size buffer\n"));
    return;
  }

  DEBUG ((DEBUG_INFO, "  Base  0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n"));
  DEBUG ((DEBUG_INFO, "  %4d %2x ", CurrentByte / 16, Buffer[0]));

  for (CurrentByte = 1; CurrentByte < BufferSize; CurrentByte++) {
    if ((CurrentByte % 16) == 0) {
      DEBUG ((DEBUG_INFO, "\n  %4d %2x ", CurrentByte / 16, Buffer[CurrentByte]));
    } else {
      DEBUG ((DEBUG_INFO, "%2x ", Buffer[CurrentByte]));
    }
  }
  DEBUG ((DEBUG_INFO, "\n"));
}

/**
  Locates a Secure Pre-Memory Data Sub Structure with the given signature.

  @param[in]  Signature                       Signature of the SPMD substructure to locate.
  @param[in]  SecurePreMemoryDataTableHeader  The Secure Pre-Memory Data table to search.
  @param[out] SecurePreMemoryDataSubStructure A point to the substructure if successfully found.


  @retval     EFI_SUCCESS             The substructure was successfully located.
  @retval     EFI_INVALID_PARAMETER   A parameter to the function is invalid such as a NULL pointer.
  @retval     EFI_NOT_FOUND           The substructure was not found in the given table.
*/
EFI_STATUS
EFIAPI
LocateSubStructure (
  IN  UINT32                                      Signature,
  IN  CONST SECURE_PRE_MEMORY_DATA_TABLE_HEADER   *SecurePreMemoryDataTableHeader,
  OUT SECURE_PRE_MEMORY_DATA_SUB_STRUCTURE        **SecurePreMemoryDataSubStructure
  )
{
  UINT32                                Count;
  SECURE_PRE_MEMORY_DATA_SUB_STRUCTURE  *CurrentSubStructure;

  if (SecurePreMemoryDataTableHeader == NULL) {
    return EFI_INVALID_PARAMETER;
  } else if (SecurePreMemoryDataTableHeader->NumberOfSubStructures == 0) {
    return EFI_NOT_FOUND;
  }

  CurrentSubStructure = (SECURE_PRE_MEMORY_DATA_SUB_STRUCTURE *) (SecurePreMemoryDataTableHeader + 1);
  for (Count = 0; Count < SecurePreMemoryDataTableHeader->NumberOfSubStructures; Count++, CurrentSubStructure++) {
    if (Signature == CurrentSubStructure->Signature) {
      *SecurePreMemoryDataSubStructure = CurrentSubStructure;
      return EFI_SUCCESS;
    }
  }

  return EFI_NOT_FOUND;
}

/**
  Loads the secure pre-memory data (SPMD) from the CSE Shared SRAM on a block media boot. This data will contain
  a UEFI variable store that serves read requests in PEI on a block media boot.

  @param      None

  @retval     EFI_SUCCESS    The secure pre-memory data was loaded successfully.
  @retval     EFI_LOAD_ERROR The secure pre-memory data UEFI variable store failed to load.
  @retval     EFI_NOT_FOUND  The secure pre-memory data was not found.
*/
EFI_STATUS
EFIAPI
LoadSecurePreMemoryData (
  VOID
  )
{
  EFI_STATUS                            Status;
  SECURE_PRE_MEMORY_DATA_TABLE          *SecurePreMemoryDataTable;
  SECURE_PRE_MEMORY_DATA_SUB_STRUCTURE  *SecurePreMemoryDataSubStructure;
  CONST CHAR8                           *NoSecurePreMemoryDataString = SECURE_PRE_MEMORY_DATA_NOT_PRESENT_STRING;

  WaitForIbbDataReady ();

  Status = FindSecurePreMemoryData (&SecurePreMemoryDataTable);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (AsciiStrnCmp ((CHAR8 *) SecurePreMemoryDataTable, NoSecurePreMemoryDataString, AsciiStrSize (NoSecurePreMemoryDataString)) != 0) {
    DEBUG ((DEBUG_INFO, "Secure Pre-Memory Data (SPMD) found. Loading the UEFI variable store...\n"));
    DEBUG ((DEBUG_INFO, "SPMD at 0x%x.\n", (UINTN) SecurePreMemoryDataTable));

    Status =  LocateSubStructure (
                SECURE_PRE_MEMORY_DATA_UEFI_VAR_STORE_STRUCT_SIGNATURE,
                (CONST SECURE_PRE_MEMORY_DATA_TABLE_HEADER *) SecurePreMemoryDataTable,
                &SecurePreMemoryDataSubStructure
                );
    if (!EFI_ERROR (Status)) {
      Status =  CreateVariableCacheHob (
                  (VARIABLE_NVM_STORE_HEADER *) (VOID *) ((UINT8 *) SecurePreMemoryDataTable + SecurePreMemoryDataSubStructure->Offset)
                  );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "The SPMD UEFI variable store failed to load. Variables are unavailable.\n"));
      }
    }
    ASSERT_EFI_ERROR (Status);
    return Status;
  } else {
    DEBUG ((DEBUG_INFO, "SPMD contents not found. This is considered a first boot.\n"));
  }

  return EFI_SUCCESS;
}
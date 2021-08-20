/** @file
  PEI Non-Eviction Mode (NEM) Map Library

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Acm.h>
#include <Base.h>
#include <CpuRegs.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BootMediaLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/NemMapLib.h>
#include <Library/PcdLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BfxTempRamLib.h>

#include <IndustryStandard/FirmwareInterfaceTable.h>

#define FIT_ALIGNMENT 16

//
// The NEM_MAP_STRUCTURE created by S-ACM on block media boot
//
#pragma pack(push, 1)
typedef struct {
  EFI_GUID StructureGuid; // GUID
  UINT16   Version;       // Major:Minor
  UINT16   Reserved;      // Alignment
  UINT32   NemBase;       // NEM Base address
  UINT32   NemSize;       // NEM Size
  UINT32   IbbBase;       // IBB Base in NEM
  UINT32   IbbSize;       // IBB Size in NEM
  UINT32   FitBase;       // FIT Base address
  UINT32   TempRamBase;   // PEI TempRamBase for stack data
  UINT32   TempRamSize;   // PEI TempRamSize
} NEM_MAP_STRUCTURE;

typedef struct {
  EFI_HOB_GUID_TYPE                 Header;
  UINT8                             Revision;
  UINT8                             Reserved[3];
  FIRMWARE_INTERFACE_TABLE_ENTRY    *Fit;
} FIT_HOB_STRUCTURE;
#pragma pack(pop)

UINT8 FitHobFitEntryTypeExclusions[] = {
  FIT_TYPE_01_MICROCODE,
  FIT_TYPE_07_BIOS_STARTUP_MODULE
};

UINT8 FitHobFitObjectTypeExclusions[] = {
  FIT_TYPE_00_HEADER,
  FIT_TYPE_01_MICROCODE,
  FIT_TYPE_07_BIOS_STARTUP_MODULE,
  FIT_TYPE_10_CSE_SECURE_BOOT
};

/**
  Determine whether an entry of a given FIT record type should be used.

  @param[in]  FitEntryType          A FIT record type.

  @retval     TRUE                  The FIT entry is not in the exclusion list and should be used.
  @retval     FALSE                 The FIT entry is in the exclusion list and should not be used.
**/
BOOLEAN
EFIAPI
UseFitTypeEntry (
  UINT8 FitEntryType
  )
{
  UINT32 Index;

  for (Index = 0; Index < ARRAY_SIZE (FitHobFitEntryTypeExclusions); Index++) {
    if (FitHobFitEntryTypeExclusions[Index] == FitEntryType) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
  Determine whether an object in a given FIT record type should be used.

  @param[in]  FitObjectType         A FIT record type.

  @retval     TRUE                  The FIT object is not in the exclusion list and should be used.
  @retval     FALSE                 The FIT object is in the exclusion list and should not be used.
**/
BOOLEAN
EFIAPI
UseFitObjectEntry (
  UINT8 FitObjectType
  )
{
  UINT32 Index;

  for (Index = 0; Index < ARRAY_SIZE (FitHobFitObjectTypeExclusions); Index++) {
    if (FitHobFitObjectTypeExclusions[Index] == FitObjectType) {
      return FALSE;
    }
  }

  return TRUE;
}

/**
  Finds the base and size of ACM FW.

  The residing memory of the ACM binary should be valid while the FIT containing its address is valid. For example,
  a FIT that can be found in post-memory should not point to an ACM FW in CPU cache given cache is invalidated
  when permanent memory is enabled.

  @param[out] AcmBase               A pointer to a pointer to the ACM base.
  @param[out] AcmSize               The size of the ACM FW in bytes.

  @retval     EFI_SUCCESS           The ACM FW base address was determined successfully.
  @retval     EFI_INVALID_PARAMETER An NULL pointer was given.
  @retval     EFI_NOT_FOUND         The ACM FW base address could not be determined.
**/
EFI_STATUS
EFIAPI
GetAcmBaseAndSize (
  OUT VOID  **AcmBase,
  OUT UINTN *AcmSize
  )
{
  EFI_STATUS          Status;
  EFI_STATUS          FindFvStatus;
  UINTN               FvInstance;
  EFI_PEI_FV_HANDLE   FvHandle;
  EFI_PEI_FILE_HANDLE FileHandle;
  ACM_HEADER          *AcmHeader;

  if (AcmBase == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  for (FvInstance = 0, FindFvStatus = EFI_SUCCESS; !EFI_ERROR (FindFvStatus); FvInstance++) {
    FindFvStatus = PeiServicesFfsFindNextVolume (FvInstance, &FvHandle);
    if (!EFI_ERROR (FindFvStatus)) {
      ASSERT (((EFI_FIRMWARE_VOLUME_HEADER *) FvHandle)->Signature == EFI_FVH_SIGNATURE);
      FileHandle = NULL;
      Status = PeiServicesFfsFindFileByName (&gStartupAcmPeiFileGuid, FvHandle, &FileHandle);
      if (!EFI_ERROR (Status)) {
        if (IS_FFS_FILE2 (FileHandle)) {
          AcmHeader = (ACM_HEADER *) ((UINT8 *) FileHandle + sizeof (EFI_FFS_FILE_HEADER2));
        } else {
          AcmHeader = (ACM_HEADER *) ((UINT8 *) FileHandle + sizeof (EFI_FFS_FILE_HEADER));
        }
        if (!EFI_ERROR (Status) && AcmHeader->ModuleType == ACM_MODULE_TYPE_CHIPSET_ACM) {
          DEBUG ((DEBUG_INFO, "ACM discovered at memory location 0x%x.\n", (UINTN) AcmHeader));
          DEBUG ((DEBUG_INFO, "  ACM Chipset ID: 0x%x\n", AcmHeader->ChipsetId));
          DEBUG ((DEBUG_INFO, "  ACM Date: 0x%x\n", AcmHeader->Date));
          DEBUG ((DEBUG_INFO, "  ACM Size: 0x%x\n", AcmHeader->Size));
          *AcmBase = (VOID *) AcmHeader;
          *AcmSize = AcmHeader->Size;

          return EFI_SUCCESS;
        }
      }
    }
  }

  return EFI_NOT_FOUND;
}

/**
  Calculates the number of FIT entries and total size for the FIT entries and associated objects.

  @param[in]  Fit                   A pointer to the Fit table to be used in the calculation.
  @param[in]  NemBase               The NEM base address.
  @param[in]  SourceFitEntries      The number of entries to process in SourceFit.
  @param[out] FitEntries            The number of FIT entries found not in the exclusion list.
  @param[out] FitSize               The total size needed for the FIT entries and FIT objects not in the
                                    exclusion lists.

  @retval     EFI_SUCCESS           The FIT entry and object calculation was performed successfully.
  @retval     EFI_INVALID_PARAMETER A given parameter is invalid.
**/
EFI_STATUS
EFIAPI
CalculateFitEntriesAndSize (
  IN  CONST FIRMWARE_INTERFACE_TABLE_ENTRY  *Fit,
  IN  UINTN                                 NemBase,
  IN  UINT8                                 FitSourceEntries,
  OUT UINT8                                 *FitEntries,
  OUT UINT16                                *FitSize
  )
{
  UINT32  Index;

  if (Fit == NULL || NemBase == 0 || FitSourceEntries == 0 || FitEntries == NULL || FitSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  for (*FitEntries = 0, *FitSize = 0, Index = 0; Index < FitSourceEntries; Index++) {
    if (UseFitTypeEntry (Fit[Index].Type)) {
      DEBUG ((DEBUG_INFO, "[%d] - Found FIT entry of type %d.\n", Index, Fit[Index].Type));

      //
      // Do not include ACM binary in the HOB buffer allocation as it is too large and will cause the buffer to exceed
      // the maximum HOB size. ACM will be pointed to in its discovered location within the BIOS image from this FIT.
      //
      if (
        UseFitObjectEntry (Fit[Index].Type) && Fit[Index].Address >= (UINT64) NemBase &&
        Fit[Index].Type != FIT_TYPE_02_STARTUP_ACM
        ) {
        DEBUG ((
          DEBUG_INFO,
          "  Found FIT object. Size 0x%x. Address 0x%x.\n",
          (UINTN) *(UINT32 *) (&Fit[Index].Size[0]) & 0xFFFFFF,
          Fit[Index].Address
          ));
        *FitSize += *(UINT16 *) (&Fit[Index].Size[0]) & 0xFFFFFF;
        *FitSize += FIT_ALIGNMENT;
      }
      (*FitEntries)++;
    } else {
      DEBUG ((DEBUG_INFO, "[%d] - Found but ignoring FIT entry of type %d.\n", Index, Fit[Index].Type));
    }
  }
  *FitSize += ((*FitEntries + 1) * sizeof (FIRMWARE_INTERFACE_TABLE_ENTRY));
  *FitSize = ALIGN_VALUE (*FitSize, FIT_ALIGNMENT);

  return EFI_SUCCESS;
}

/**
  Copies FIT entries and objects from a source FIT to a destination FIT.

  @param[in]  SourceFit             The source FIT buffer.
  @param[out] DesinationFit         The destination FIT buffer.
  @param[in]  SourceFitEntries      The number of entries to process in SourceFit.
  @param[in]  DestinationFitEntries The total number of entries in DestinationFit.
  @param[in]  NemBase               The NEM base address.

  @retval     EFI_SUCCESS           The FIT entries and objects were copied successfully.
  @retval     EFI_INVALID_PARAMETER A given parameter is invalid.
**/
EFI_STATUS
EFIAPI
CopyFitEntriesAndObjects (
  IN CONST FIRMWARE_INTERFACE_TABLE_ENTRY *SourceFit,
  OUT      FIRMWARE_INTERFACE_TABLE_ENTRY *DestinationFit,
  IN       UINT8                          SourceFitEntries,
  IN       UINT8                          DestinationFitEntries,
  IN       UINTN                          NemBase
  )
{
  EFI_STATUS  Status;
  UINT32      DestinationIndex;
  UINT32      Index;
  UINTN       FitObjectSize;
  VOID        *DestinationFitObjectPtr;
  VOID        *SourceFitObjectPtr;

  if (SourceFit == NULL || DestinationFit == NULL || SourceFitEntries == 0 || NemBase == 0) {
    return EFI_INVALID_PARAMETER;
  }

  DestinationFitObjectPtr = (VOID *) &(DestinationFit[DestinationFitEntries + 1]);
  DestinationFitObjectPtr = ALIGN_POINTER (DestinationFitObjectPtr, FIT_ALIGNMENT);

  for (DestinationIndex = 0, Index = 0; Index < SourceFitEntries; Index++) {
    if (UseFitTypeEntry (SourceFit[Index].Type)) {
      DEBUG ((
        DEBUG_INFO,
        "Copying FIT entry of type %d from 0x%x to 0x%x.\n",
        SourceFit[Index].Type,
        (UINTN) &SourceFit[Index],
        (UINTN) &DestinationFit[DestinationIndex]
        ));
      CopyMem (
        (VOID *) &DestinationFit[DestinationIndex],
        (VOID *) &SourceFit[Index],
        sizeof (FIRMWARE_INTERFACE_TABLE_ENTRY)
        );

      if (UseFitObjectEntry (SourceFit[Index].Type)) {
        if (SourceFit[Index].Type == FIT_TYPE_02_STARTUP_ACM) {
          Status = GetAcmBaseAndSize (&SourceFitObjectPtr, &FitObjectSize);
          if (EFI_ERROR (Status)) {
            DestinationFit[DestinationIndex].Address = 0;
            DestinationFit[DestinationIndex].Size[0] = 0;
          } else {
            DestinationFit[DestinationIndex].Address = (UINT64) SourceFitObjectPtr;
            DestinationFit[DestinationIndex].Size[0] = (UINT8) (FitObjectSize / 16);
          }
        } else if (SourceFit[Index].Address >= (UINT64) NemBase) {
          FitObjectSize = *(UINTN *) (&SourceFit[Index].Size[0]) & 0xFFFFFF;
          SourceFitObjectPtr = (VOID *) (UINTN) SourceFit[Index].Address;
          DEBUG ((
            DEBUG_INFO,
            "Copying FIT object for entry of type %d of size 0x%x from 0x%x to 0x%x.\n",
            SourceFit[Index].Type,
            FitObjectSize,
            (UINTN) SourceFitObjectPtr,
            (UINTN) DestinationFitObjectPtr
            ));
          CopyMem (DestinationFitObjectPtr, SourceFitObjectPtr, FitObjectSize);
          DestinationFit[DestinationIndex].Address = (UINT64) DestinationFitObjectPtr;
          DestinationFitObjectPtr = (VOID *) ((UINT8 *) DestinationFitObjectPtr + FitObjectSize);
          DestinationFitObjectPtr = ALIGN_POINTER (DestinationFitObjectPtr, FIT_ALIGNMENT);
        }
      }
      DestinationIndex++;
    }
  }

  return EFI_SUCCESS;
}

/**
  Copies FIT data from a pre-existing FIT location to a FIT HOB.

  Future FIT API requests will return information from the FIT HOB after this API is invoked. The FIT entries
  may be trimmed to BIOS-relevant entries to reduce memory consumption. This allows the total HOB size to be less
  than the maximum HOB size and reduces memory usage if this API is used in pre-memory.

  @param[in]  FitSourceBase         The base address of a pre-existing FIT.

  @retval     EFI_SUCCESS           The FIT HOB was produced successfully.
  @retval     EFI_INVALID_PARAMETER The parameter given is invalid.
  @retval     EFI_NOT_FOUND         The source FIT table could not be found.
**/
EFI_STATUS
EFIAPI
ProduceFitHob (
  IN UINTN FitSourceBase
  )
{
  EFI_STATUS                      Status;
  UINT8                           FitSourceEntries;
  UINT8                           FitDestinationEntries;
  UINT16                          FitDestinationSize;
  UINTN                           NemBase;
  UINT32                          NemSize;
  FIRMWARE_INTERFACE_TABLE_ENTRY  *FitSourceEntry;
  FIRMWARE_INTERFACE_TABLE_ENTRY  *BackupFit;
  FIT_HOB_STRUCTURE               *FitHobStructureHob;

  BackupFit = NULL;

  if (FitSourceBase == 0) {
    return EFI_INVALID_PARAMETER;
  }

  FitSourceEntry = (FIRMWARE_INTERFACE_TABLE_ENTRY *) FitSourceBase;
  if (FitSourceEntry[0].Address != *(UINT64 *) "_FIT_   ") {
    return EFI_NOT_FOUND;
  } else if (FitSourceEntry[0].Type != FIT_TYPE_00_HEADER) {
    return EFI_NOT_FOUND;
  }

  FitSourceEntries = *(UINT8 *) (&FitSourceEntry[0].Size[0]) & 0xFFFFFF;
  ASSERT (FitSourceEntries > 0);

  Status = GetNemBaseAndSize (&NemBase, &NemSize);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status =  CalculateFitEntriesAndSize (
              FitSourceEntry,
              NemBase,
              FitSourceEntries,
              &FitDestinationEntries,
              &FitDestinationSize
              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DEBUG ((DEBUG_INFO, "Source FIT entries = 0x%x.\n", FitSourceEntries));
  DEBUG ((DEBUG_INFO, "Destination FIT entries = 0x%x.\n", FitDestinationEntries));
  DEBUG ((DEBUG_INFO, "Destination FIT size = 0x%x\n", FitDestinationSize));

  //
  // There can only be a single FIT HOB. If a FIT HOB already exists reuse the HOB buffer.
  // It may be recreated to refresh the FIT pointers such as needed during the permanent memory transition.
  //
  FitHobStructureHob = GetFirstGuidHob (&gFitStructureGuid);
  if (FitHobStructureHob == NULL) {
    Status =  PeiServicesCreateHob (
                EFI_HOB_TYPE_GUID_EXTENSION,
                ALIGN_VALUE ((UINT16) sizeof (FIT_HOB_STRUCTURE) + FitDestinationSize, FIT_ALIGNMENT),
                (VOID **) &FitHobStructureHob
                );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    ZeroMem (GET_GUID_HOB_DATA (FitHobStructureHob), GET_GUID_HOB_DATA_SIZE (FitHobStructureHob));
    CopyGuid (&(FitHobStructureHob->Header.Name), &gFitStructureGuid);
    FitHobStructureHob->Revision = 1;
    FitHobStructureHob->Fit = (FIRMWARE_INTERFACE_TABLE_ENTRY *) ALIGN_POINTER ((FitHobStructureHob + 1), FIT_ALIGNMENT);
  } else {
    //
    // Copy a pre-existing FIT HOB to a temporary location so it is not mutated during the copy.
    //
    BackupFit = AllocatePool (GET_GUID_HOB_DATA_SIZE (FitHobStructureHob));
    if (BackupFit == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    CopyMem (
      (VOID *) BackupFit,
      (VOID *) FitHobStructureHob->Fit,
      GET_GUID_HOB_DATA_SIZE (FitHobStructureHob) - OFFSET_OF (FIT_HOB_STRUCTURE, Fit)
      );
    ASSERT (BackupFit[0].Address == *(UINT64 *) "_FIT_   ");
    ASSERT (BackupFit[0].Type == FIT_TYPE_00_HEADER);
    FitSourceEntry = BackupFit;
  }
  ASSERT (FitDestinationSize <= GET_GUID_HOB_DATA_SIZE (FitHobStructureHob));

  Status =  CopyFitEntriesAndObjects (
              FitSourceEntry,
              FitHobStructureHob->Fit,
              FitSourceEntries,
              FitDestinationEntries,
              NemBase
              );
  if (EFI_ERROR (Status)) {
    return Status;
  }

 FitHobStructureHob->Fit[0].Size[0] = FitDestinationEntries;
  if (FitHobStructureHob->Fit[0].C_V == 1) {
    FitHobStructureHob->Fit[0].Chksum = CalculateCheckSum8 (
                                      (UINT8 *) &FitHobStructureHob->Fit[0],
                                      sizeof (FIRMWARE_INTERFACE_TABLE_ENTRY) * FitDestinationEntries
                                      );
  }

  if (BackupFit != NULL) {
    FreePool (BackupFit);
  }

  return EFI_SUCCESS;
}

/**
  Produces the NEM Map Configuration HOB which contains the NEM map structure in host memory.

  @retval     EFI_NOT_FOUND     The boot device indicator could not be found.
  @retval     EFI_DEVICE_ERROR  The NEM map structure signature is invalid.
  @retval     EFI_SUCCESS       The boot device indicator was found successfully.
**/
EFI_STATUS
EFIAPI
ProduceNemMapConfigHob (
  VOID
  )
{
  NEM_MAP_STRUCTURE   *NemMapStructurePtr;

  NemMapStructurePtr = (NEM_MAP_STRUCTURE *) (VOID *) MmioRead32 (TXT_PUBLIC_BASE + R_CPU_BOOT_GUARD_NEM_MAP_STRUCTURE_ADDRESS);
  if (NemMapStructurePtr == NULL) {
    return EFI_NOT_FOUND;
  } else if (!CompareGuid (&NemMapStructurePtr->StructureGuid, &gNemMapStructureGuid)) {
    ASSERT (CompareGuid (&NemMapStructurePtr->StructureGuid, &gNemMapStructureGuid) == TRUE);
    return EFI_DEVICE_ERROR;
  }

  if (BuildGuidDataHob (&gNemMapStructureHobGuid, NemMapStructurePtr, sizeof (NEM_MAP_STRUCTURE)) == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  return EFI_SUCCESS;
}

/**
  Returns a pointer to the NEM map structure which must exist on a block media boot.

  @param[out]   NemMapStructureAddress    A pointer to the NEM_MAP_STRUCTURE.

  @retval       EFI_SUCCESS               The NEM map structure was located and returned successfully.
  @retval       EFI_NOT_FOUND             The gNemMapStructureHobGuid was not found.
  @retval       EFI_DEVICE_ERROR          The GUID in the NEM map structure is invalid.
**/
EFI_STATUS
EFIAPI
GetNemMapStructure (
  OUT NEM_MAP_STRUCTURE     **NemMapStructure
  )
{
  EFI_STATUS                Status;
  EFI_HOB_GUID_TYPE         *GuidHobPtr;
  NEM_MAP_STRUCTURE         *NemMapStructurePtr;

  GuidHobPtr  = GetFirstGuidHob (&gNemMapStructureHobGuid);
  if (GuidHobPtr == NULL) {
    Status = ProduceNemMapConfigHob ();
    GuidHobPtr  = GetFirstGuidHob (&gNemMapStructureHobGuid);

    if (EFI_ERROR (Status) || GuidHobPtr == NULL) {
      DEBUG ((DEBUG_ERROR, "NemMapLib Error: NEM map structure HOB does not exist!\n"));
      ASSERT (!EFI_ERROR (Status) && GuidHobPtr != NULL);
      //
      // The block media boot cannot continue if the NEM map information is unknown
      //
      CpuDeadLoop ();
    }
  }

  NemMapStructurePtr = (NEM_MAP_STRUCTURE *) GET_GUID_HOB_DATA (GuidHobPtr);

  if (!CompareGuid (&(NemMapStructurePtr->StructureGuid), &gNemMapStructureGuid)) {
    DEBUG ((DEBUG_ERROR, "NEM Map signature is invalid!\n"));
    return EFI_DEVICE_ERROR;
  }

  *NemMapStructure = NemMapStructurePtr;

  return EFI_SUCCESS;
}

/**
  Checks if an existing FIT HOB exists before producing a new FIT HOB.

  @param[out]   FitHobStructure             A pointer to a pointer to the FIT_HOB_STRUCTURE. The pointer will be
                                            udpdated to point to a FIT_HOB_STRUCTURE instance.

  @retval       EFI_SUCCESS                 The FIT HOB structure was located and returned successfully.
  @retval       EFI_NOT_FOUND               The gFitStructureGuid was not found.
  @retval       EFI_DEVICE_ERROR            The GUID in the NEM map structure is invalid.
**/
EFI_STATUS
EFIAPI
CheckAndProduceFitHob (
  OUT FIT_HOB_STRUCTURE **FitHobStructure
  )
{
  EFI_STATUS          Status;
  FIT_HOB_STRUCTURE   *FitHobStructurePtr;
  NEM_MAP_STRUCTURE   *NemMapStructurePtr;

  FitHobStructurePtr  = GetFirstGuidHob (&gFitStructureGuid);
  if (FitHobStructurePtr == NULL) {
    Status = GetNemMapStructure (&NemMapStructurePtr);
    if (EFI_ERROR (Status) || NemMapStructurePtr == NULL) {
      return EFI_NOT_FOUND;
    }

    Status = ProduceFitHob ((UINTN) NemMapStructurePtr->FitBase);
    FitHobStructurePtr = GetFirstGuidHob (&gFitStructureGuid);

    if (EFI_ERROR (Status) || FitHobStructurePtr == NULL) {
      DEBUG ((DEBUG_ERROR, "NemMapLib Error: FIT structure HOB does not exist!\n"));
      ASSERT (!EFI_ERROR (Status) && FitHobStructurePtr != NULL);
      //
      // The block media boot cannot continue if the FIT information cannot be published properly
      //
      CpuDeadLoop ();
    }
  }

  if (!CompareGuid (&(FitHobStructurePtr->Header.Name), &gFitStructureGuid)) {
    DEBUG ((DEBUG_ERROR, "FIT HOB signature is invalid!\n"));
    return EFI_DEVICE_ERROR;
  }

  *FitHobStructure = FitHobStructurePtr;

  return EFI_SUCCESS;
}

/**
  Returns a pointer to the FIT HOB if it exists.

  @param[out]   FitHobStructure             A pointer to a pointer to the FIT_HOB_STRUCTURE. The pointer will be
                                            udpdated to point to a FIT_HOB_STRUCTURE instance if the FIT HOB
                                            can be located.

  @retval       EFI_SUCCESS                 The FIT HOB structure was located and returned successfully.
  @retval       EFI_NOT_FOUND               The gFitStructureGuid was not found.
**/
EFI_STATUS
EFIAPI
GetFitHob (
  OUT FIT_HOB_STRUCTURE **FitHobStructure
  )
{
  FIT_HOB_STRUCTURE   *FitHobStructurePtr;

  FitHobStructurePtr = GetFirstGuidHob (&gFitStructureGuid);
  if (FitHobStructurePtr != NULL) {
    *FitHobStructure = FitHobStructurePtr;
  } else {
    return EFI_NOT_FOUND;
  }

  return EFI_SUCCESS;
}

/**
  Determines the Intel Boot Block (IBB) base address and size.

  @param[out] IbbBase         The IBB base address.
  @param[out] IbbSize         The IBB size.

  @retval       EFI_SUCCESS       The operation completed successfully.
  @retval       EFI_NOT_FOUND     The gNemMapStructureHobGuid was not found.
  @retval       EFI_DEVICE_ERROR  The GUID in the NEM map structure is invalid.
**/
EFI_STATUS
EFIAPI
GetIbbBaseAndSize (
  OUT UINTN    *IbbBase, OPTIONAL
  OUT UINT32   *IbbSize  OPTIONAL
  )
{
  EFI_STATUS        Status;
  NEM_MAP_STRUCTURE *NemMapStructurePtr = NULL;

  if (BootMediaIsSpi ()) {
    if (IbbBase != NULL) {
      *IbbBase = (UINTN) (FixedPcdGet32 (PcdBiosAreaBaseAddress) + FixedPcdGet32 (PcdNemCodeCacheBase));
    }
    if (IbbSize != NULL) {
      *IbbSize = FixedPcdGet32 (PcdFlashFvPreMemorySize);
    }
  } else {
    Status = GetNemMapStructure (&NemMapStructurePtr);
    if (EFI_ERROR (Status)) {
      return Status;
    } else if (NemMapStructurePtr == NULL) {
      return EFI_NOT_FOUND;
    }

    if (IbbBase != NULL) {
      *IbbBase = NemMapStructurePtr->IbbBase;
    }
    if (IbbSize != NULL) {
      *IbbSize = NemMapStructurePtr->IbbSize;
    }
  }

  return EFI_SUCCESS;
}

/**
  Determines the Non-Eviction Mode (NEM) region base address and size.

  @param[out] NemBase         The NEM region base address.
  @param[out] NemSize         The NEM region size.

  @retval       EFI_SUCCESS       The operation completed successfully.
  @retval       EFI_NOT_FOUND     The gNemMapStructureHobGuid was not found.
  @retval       EFI_DEVICE_ERROR  The GUID in the NEM map structure is invalid.
**/
EFI_STATUS
EFIAPI
GetNemBaseAndSize (
  OUT UINTN     *NemBase, OPTIONAL
  OUT UINT32    *NemSize  OPTIONAL
  )
{
  EFI_STATUS        Status;
  UINT32            IbbCodeSize;
  NEM_MAP_STRUCTURE *NemMapStructurePtr = NULL;

  // For SPI what is the NEM base? T-RAM base or BIOS image base?
  if (BootMediaIsSpi ()) {
    if (NemBase != NULL) {
#if FixedPcdGetBool(PcdBfxEnable) == 1
      *NemBase = (UINTN) BfxGetTempRamBase ();
#else
      *NemBase = (UINTN) FixedPcdGet32 (PcdTemporaryRamBase);
#endif
    }

    if (NemSize != NULL) {
      Status = GetIbbBaseAndSize (NULL, &IbbCodeSize);
      if (EFI_ERROR (Status)) {
        ASSERT_EFI_ERROR (Status);
      }
#if FixedPcdGetBool(PcdBfxEnable) == 1
      *NemSize = IbbCodeSize + BfxGetTempRamSize ();
#else
      *NemSize = IbbCodeSize + FixedPcdGet32 (PcdTemporaryRamSize);
#endif
    }
  } else {
    Status = GetNemMapStructure (&NemMapStructurePtr);
    if (EFI_ERROR (Status)) {
      return Status;
    } else if (NemMapStructurePtr == NULL) {
      return EFI_NOT_FOUND;
    }

    if (NemBase != NULL) {
      *NemBase = NemMapStructurePtr->NemBase;
    }
    if (NemSize != NULL) {
      *NemSize = NemMapStructurePtr->NemSize;
    }
  }

  return EFI_SUCCESS;
}

/**
  Determines the Temporary RAM (T-RAM) base address and size.

  @param[out] TempRamBase     The T-RAM base address.
  @param[out] TempRamSize     The T-RAM size.

  @retval       EFI_SUCCESS       The operation completed successfully.
  @retval       EFI_NOT_FOUND     The gNemMapStructureHobGuid was not found.
  @retval       EFI_DEVICE_ERROR  The GUID in the NEM map structure is invalid.
**/
EFI_STATUS
EFIAPI
GetTempRamBaseAndSize (
  OUT UINTN     *TempRamBase, OPTIONAL
  OUT UINT32    *TempRamSize  OPTIONAL
  )
{
  EFI_STATUS        Status;
  NEM_MAP_STRUCTURE *NemMapStructurePtr = NULL;

  if (BootMediaIsSpi ()) {
    if (TempRamBase != NULL) {
#if FixedPcdGetBool(PcdBfxEnable) == 1
      *TempRamBase = (UINTN) BfxGetTempRamBase ();
#else
      *TempRamBase = (UINTN) FixedPcdGet32 (PcdTemporaryRamBase);
#endif
    }

    if (TempRamSize != NULL) {
#if FixedPcdGetBool(PcdBfxEnable) == 1
      *TempRamSize = BfxGetTempRamSize ();
#else
      *TempRamSize = FixedPcdGet32 (PcdTemporaryRamSize);
#endif
    }
  } else {
    Status = GetNemMapStructure (&NemMapStructurePtr);
    if (EFI_ERROR (Status)) {
      return Status;
    } else if (NemMapStructurePtr == NULL) {
      return EFI_NOT_FOUND;
    }

    if (TempRamBase != NULL) {
      *TempRamBase = NemMapStructurePtr->TempRamBase;
    }
    if (TempRamSize != NULL) {
      *TempRamSize = NemMapStructurePtr->TempRamSize;
    }
  }

  return EFI_SUCCESS;
}

/**
  Determines the Firmware Interface Table (FIT) base address.

  @param[out]   FitBase           The FIT base address.

  @retval       EFI_SUCCESS       The operation completed successfully.
  @retval       EFI_NOT_FOUND     The gNemMapStructureHobGuid was not found
  @retval       EFI_NOT_FOUND     The FIT table could not be found (or is no longer available)
  @retval       EFI_DEVICE_ERROR  The GUID in the NEM map structure is invalid.
**/
EFI_STATUS
EFIAPI
GetFitBase (
  OUT UINTN    *FitBase
  )
{
  EFI_STATUS                      Status;
  FIRMWARE_INTERFACE_TABLE_ENTRY  *FitEntry;
  FIT_HOB_STRUCTURE               *FitHobStructurePtr;
  NEM_MAP_STRUCTURE               *NemMapStructurePtr;
  UINTN                           FitBaseAddress;

  if (BootMediaIsSpi ()) {
    FitBaseAddress = *(UINTN *) (UINTN) (BASE_4GB - 0x40);
  } else {
    Status = GetFitHob (&FitHobStructurePtr);
    if (Status == EFI_NOT_FOUND) {
      Status = GetNemMapStructure (&NemMapStructurePtr);
      if (EFI_ERROR (Status)) {
        return Status;
      } else if (NemMapStructurePtr == NULL) {
        return EFI_NOT_FOUND;
      }
      FitBaseAddress = (UINTN) NemMapStructurePtr->FitBase;
    } else if (EFI_ERROR (Status)) {
      return Status;
    } else if (FitHobStructurePtr == NULL) {
      return EFI_NOT_FOUND;
    } else {
      FitBaseAddress = (UINTN) FitHobStructurePtr->Fit;
    }
  }

  FitEntry = (FIRMWARE_INTERFACE_TABLE_ENTRY *) FitBaseAddress;
  if (FitEntry[0].Address != *(UINT64 *) "_FIT_   ") {
    return EFI_NOT_FOUND;
  } else {
    *FitBase = FitBaseAddress;
  }

  return EFI_SUCCESS;
}

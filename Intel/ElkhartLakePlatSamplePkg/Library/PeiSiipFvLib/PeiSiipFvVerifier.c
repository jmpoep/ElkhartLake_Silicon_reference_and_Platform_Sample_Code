/**@file
  PSE FV Verification

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

@par Specification
**/

#include <PiPei.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/PeiSiipFvLib.h>
#include <Library/BootMediaLib.h>
#include <Library/BaseCryptLib.h>
#include <SiipManifest.h>
#include <Library/MemoryAllocationLib.h>

#define SECURE_BOOT_ENABLED               1
#define SECURE_BOOT_DISABLED              0

/**
  Calculates the size of the hash based on algorithm.

  @param[in]  HashAlg   Algorithm used for hash calculation.
  @param[out] HashSize  Pointer to a buffer that receives the total size of hash in bytes.

**/
VOID
GetHashSize (
  IN  UINT32              HashAlg,
  OUT UINTN               *HashSize
  )
{
  switch (HashAlg) {
    case SIIP_HASHALG_SHA1:
      //
      // SHA1 Hash
      //
      *HashSize = SHA1_DIGEST_SIZE;
      break;
    case SIIP_HASHALG_SHA256:
      //
      // SHA256 Hash
      //
      *HashSize = SHA256_DIGEST_SIZE;
      break;
    case SIIP_HASHALG_SHA384:
      //
      // SHA384 Hash
      //
      *HashSize = SHA384_DIGEST_SIZE;
      break;
    case SIIP_HASHALG_SHA512:
      //
      // SHA512 Hash
      //
      *HashSize = SHA512_DIGEST_SIZE;
      break;
    default:
      *HashSize = 0;
      break;
  }
}

VOID
DumpCpdHdrStruct (
  IN  CPD_HEADER_STRUCT *CpdHdrData
  )
{
  if (CpdHdrData == NULL) {
    DEBUG ((DEBUG_INFO, "Get null from CpdHdrData\n"));
    return;
  }
  DEBUG ((DEBUG_INFO, "\n\n===========================================\nLooking into DumpCpdHdrStruct\n"));
  DEBUG ((DEBUG_INFO, "sizeof (CPD_HEADER_STRUCT)   : 0x%04x\n",  sizeof (CPD_HEADER_STRUCT)));
  DEBUG ((DEBUG_INFO, "CpdHdrData->HeaderMarker     : 0x%04x\n",  CpdHdrData->HeaderMarker));
  DEBUG ((DEBUG_INFO, "CpdHdrData->NumberOfEntries  : 0x%04x\n",  CpdHdrData->NumberOfEntries));
  DEBUG ((DEBUG_INFO, "CpdHdrData->HeaderVersion    : 0x%04x\n",  CpdHdrData->HeaderVersion));
  DEBUG ((DEBUG_INFO, "CpdHdrData->EntryVersion     : 0x%04x\n",  CpdHdrData->EntryVersion));
  DEBUG ((DEBUG_INFO, "CpdHdrData->HeaderLength     : 0x%04x\n",  CpdHdrData->HeaderLength));
  DEBUG ((DEBUG_INFO, "CpdHdrData->Reserved         : 0x%04x\n",  CpdHdrData->Reserved));
  DEBUG ((DEBUG_INFO, "CpdHdrData->SubPartitionName : 0x%04x\n",  CpdHdrData->SubPartitionName));
  DEBUG ((DEBUG_INFO, "CpdHdrData->Crc32Checksum    : 0x%04x\n",  CpdHdrData->Crc32Checksum));
  DEBUG ((DEBUG_INFO, "===========================================\n\n\n"));
}

VOID
DumpCpdEntryStruct (
  IN  CPD_ENTRY_STRUCT  *CpdEntryData
  )
{
  if (CpdEntryData == NULL) {
    DEBUG ((DEBUG_INFO, "Get null from CpdEntryData\n"));
    return;
  }
  DEBUG ((DEBUG_INFO, "\n\n===========================================\nLooking into CpdEntryData\n"));
  DEBUG ((DEBUG_INFO, "sizeof (CPD_ENTRY_STRUCT)        : 0x%04x\n",  sizeof (CPD_ENTRY_STRUCT)));
  DEBUG ((DEBUG_INFO, "CpdEntryData->EntryName:\n"));
  for (UINT32 Count = 0; Count < ENTRY_NAME_LENGTH; Count++) {
    DEBUG ((DEBUG_INFO, "%x", CpdEntryData->EntryName[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));
  DEBUG ((DEBUG_INFO, "CpdEntryData->Offset     : 0x%04x\n",  CpdEntryData->Offset));
  DEBUG ((DEBUG_INFO, "CpdEntryData->Length     : 0x%04x\n",  CpdEntryData->Length));
  DEBUG ((DEBUG_INFO, "CpdEntryData->ModuleType : 0x%04x\n",  CpdEntryData->ModuleType));
  DEBUG ((DEBUG_INFO, "===========================================\n\n\n"));
}

/**
  Calculates the hash of the given data based on the input hash algorithm.

  @param[in]  HashAlg   Algorithm used for hash calculation.
  @param[in]  Data      Pointer to the data buffer to be hashed.
  @param[in]  DataSize  The size of data buffer in bytes.
  @param[out] HashValue Pointer to a buffer that receives the hash result.
  @param[in]  HashSize  The total size of hash in bytes.

  @retval TRUE          Data hash calculation succeeded.
  @retval FALSE         Data hash calculation failed.

**/
BOOLEAN
CreateHash (
  IN  UINT32              HashAlg,
  IN  VOID                *Data,
  IN  UINTN               DataSize,
  OUT UINT8               *HashValue,
  IN  UINTN               HashSize          OPTIONAL
  )
{
  BOOLEAN  Status;

  Status  = FALSE;

  switch (HashAlg) {
    case SIIP_HASHALG_SHA1:
      //
      // SHA1 Hash
      //
      Status  = Sha1HashAll (Data, DataSize, HashValue);
      break;
    case SIIP_HASHALG_SHA256:
      //
      // SHA256 Hash
      //
      Status  = Sha256HashAll (Data, DataSize, HashValue);
      break;
    case SIIP_HASHALG_SHA384:
      //
      // SHA384 Hash
      //
      Status  = Sha384HashAll (Data, DataSize, HashValue);
      break;
    case SIIP_HASHALG_SHA512:
      //
      // SHA512 Hash
      //
      Status  = Sha512HashAll (Data, DataSize, HashValue);
      break;
    default:
      break;
  }
  return Status;
}

/**
  Verify SIIP manifest

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       SIIP manifest was not found
**/
EFI_STATUS
VerifyManifest (
  IN OUT VOID     *ManifestBuffer,
  IN OUT UINTN    ManifestSize
  )
{
  UINTN                       IupSize;
  UINT32                      *IupBuffer;
  UINT32                      *CpdHeaderPointer;
  UINT32                      *CpdEntryPointer;
  CPD_HEADER_STRUCT           *CpdHdrStruct;
  CPD_ENTRY_STRUCT            *CpdEntryStruct;
  UINT8                       Index;
  UINT32                      Checksum;
  UINTN                       NumberOfBytesToCheckSum;
  UINT32                      *Data32Ptr;
  UINT32                      Crc32Checksum;

  IupBuffer = (UINT32 *) ManifestBuffer;
  IupSize = ManifestSize;

  DEBUG ((DEBUG_INFO, "\n===========================\n"));
  DEBUG ((DEBUG_INFO, "Verifying SIIP manifest\n"));
  DEBUG ((DEBUG_INFO, "===========================\n"));

  CpdHeaderPointer = IupBuffer; // Offset 0 of IUP which points to first CPD header
  CpdHdrStruct = (CPD_HEADER_STRUCT *)CpdHeaderPointer;

  // Checksum check implementation
  NumberOfBytesToCheckSum = sizeof(CPD_HEADER_STRUCT) + (CpdHdrStruct->NumberOfEntries * sizeof (CPD_ENTRY_STRUCT));
  DumpCpdHdrStruct(CpdHdrStruct);
  Checksum = 0;
  Data32Ptr = (UINT32 *) IupBuffer;
  Crc32Checksum = 0;
  if (NumberOfBytesToCheckSum < 0x100000) {
    for (Index = 0; Index < NumberOfBytesToCheckSum; Index += 4, Data32Ptr++) {
      if (Index == CRC32_CHECKSUM_INDEX) {
        Crc32Checksum = *Data32Ptr;
        DEBUG ((DEBUG_INFO, "Crc32Checksum from Manifest: 0x%04x\n", Crc32Checksum));
        continue;
      }
      Checksum += *Data32Ptr;
    }
  }
  DEBUG ((DEBUG_INFO, "Crc32Checksum (calculated) : 0x%04x\n", Checksum));

  if (Checksum != Crc32Checksum) {
    DEBUG ((DEBUG_INFO, "Checksum comparison FAILED\n"));
    return EFI_SECURITY_VIOLATION;
  } else {
    DEBUG ((DEBUG_INFO, "Checksum comparison PASSED\n"));
  }

  // Check for VALID_HEADER
  if ((CpdHdrStruct->HeaderMarker == CPD_HEADER_MARKER) && (CpdHdrStruct->NumberOfEntries > 0)) {
    CpdEntryPointer = CpdHeaderPointer + sizeof (CPD_HEADER_STRUCT); // Point to First Entry
    DEBUG ((DEBUG_INFO, "CpdEntryPointer now at 0x%x\n", CpdEntryPointer));
    CpdEntryStruct = (CPD_ENTRY_STRUCT *)CpdEntryPointer;
    for (Index = 0; Index < CpdHdrStruct->NumberOfEntries; Index++) { // Traverse all Entries
      DEBUG ((DEBUG_INFO, "Index %x\n",    Index));
      DumpCpdEntryStruct(CpdEntryStruct);
      if (CpdEntryStruct->ModuleType == FkmType) {
        DEBUG ((DEBUG_INFO, "FKM found!\n"));
      }
      CpdEntryPointer += sizeof(CPD_ENTRY_STRUCT); // Point to next entry
      CpdEntryStruct = (CPD_ENTRY_STRUCT *)CpdEntryPointer;
    }
  }
  return EFI_SUCCESS;
}

/**
  Verify SIIP firmware

  @param[out]  SubRegion Pointer to sub region data.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       SIIP firmware/manifest was not found
**/
EFI_STATUS
VerifyFirmware (
  IN OUT VOID     *ManifestBuffer,
  IN OUT UINTN    ManifestSize,
  IN OUT VOID     *FwBuffer,
  IN OUT UINTN    FwSize
  )
{
  EFI_STATUS             Status;
  UINTN                  Index;
  UINT8                  *CpdHeaderPointer;
  CPD_HEADER_STRUCT      *CpdHdrStruct;
  CPD_ENTRY_STRUCT       *CpdEntryStruct;
  UINT32                 Checksum;
  UINTN                  NumberOfBytesToCheckSum;
  UINT32                 *Data32Ptr;
  UINT32                 Crc32Checksum = 0;
  VOID                   *FbBuffer;
  UINT8                  *CpdEntryPointer;
  UINTN                  IupSize;
  UINT32                 *IupBuffer;
  META_DATA_STRUCT1      *MetadataStruct1;
  META_DATA_STRUCT2      *MetadataStruct2;
  UINT8                  *Data8Ptr;
  UINT32                 NoOfModules;
  UINT32                 HashAlg = 0;
  UINT32                 HashDataSize = 0;
  UINT8                  *MessageHash = NULL;
  UINTN                  MessageHashSize;
  UINT8                  *HashData = NULL;
  VOID                   *ModuleBuffer = NULL;
  UINTN                  ModuleSize = 0;
  UINT8                  SecureBootState;
  UINTN                  VarSize = 0;
  UINT32                 VarAttributes;
  BOOLEAN                SecureBootEnabled = FALSE;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;

  //
  // Locate Setup variables
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "PeiServicesLocatePpi failed\n"));
  }
  Status = VariableServices->GetVariable (
                  VariableServices,
                  L"SecureBootEnable",
                  &gEfiSecureBootEnableDisableGuid,
                  &VarAttributes,
                  &VarSize,
                  &SecureBootState
                  );
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_INFO, "ERROR! Secure Boot related UEFI variable are not found!\n"));
    SecureBootEnabled = FALSE;
  } else {
    if (SecureBootState == SECURE_BOOT_ENABLED) {
      DEBUG ((DEBUG_INFO, "Secured boot enabled! Verification process will be enforced.\n"));
      SecureBootEnabled = TRUE;
    }
  }

  DEBUG ((DEBUG_INFO, "\n===========================\n"));
  DEBUG ((DEBUG_INFO, "Verifying SIIP Firmware\n"));
  DEBUG ((DEBUG_INFO, "===========================\n"));

  if (ManifestBuffer == NULL || FwBuffer == NULL || ManifestSize == 0 || FwSize == 0) {
    DEBUG ((DEBUG_INFO, "ERROR: Some of the buffer is null or size is 0\n"));
    return EFI_NOT_FOUND;
  }

  IupBuffer = (UINT32 *)FwBuffer;
  CpdHeaderPointer = (UINT8 *)FwBuffer; // Offset 0 of IUP which points to first CPD header
  CpdHdrStruct = (CPD_HEADER_STRUCT *)CpdHeaderPointer;

  NumberOfBytesToCheckSum = sizeof(CPD_HEADER_STRUCT) + (CpdHdrStruct->NumberOfEntries * sizeof (CPD_ENTRY_STRUCT));
  IupSize = FwSize;

  Checksum = 0;
  Data32Ptr = (UINT32 *) FwBuffer;
  if (NumberOfBytesToCheckSum < 0x100000) {
    for (Index = 0; Index<NumberOfBytesToCheckSum; Index += 4, Data32Ptr++) {
      if (Index == CRC32_CHECKSUM_INDEX) {
        Crc32Checksum = *Data32Ptr;
        DEBUG ((DEBUG_INFO, "Crc32Checksum from manifest : 0x%04x\n", Crc32Checksum));
        continue;
      }
      Checksum += *Data32Ptr;
    }
  }
  DEBUG ((DEBUG_INFO, "Crc32Checksum (calculated) : 0x%04x\n", Checksum));

  if (Checksum != Crc32Checksum) {
    DEBUG ((DEBUG_INFO, "Checksum comparison FAILED\n"));
  } else {
    DEBUG ((DEBUG_INFO, "Checksum comparison PASSED\n"));
  }

  // Check for VALID_HEADER
  if ((CpdHdrStruct->HeaderMarker == CPD_HEADER_MARKER) && (CpdHdrStruct->NumberOfEntries > 0)) {
    CpdEntryPointer = CpdHeaderPointer + sizeof (CPD_HEADER_STRUCT); // Point to First Entry
    CpdEntryStruct = (CPD_ENTRY_STRUCT *)CpdEntryPointer;

    for (Index = 0; Index < CpdHdrStruct->NumberOfEntries; Index++) { // Traverse all Entries
      DEBUG ((DEBUG_INFO, "Entry %x\n", Index));
      DumpCpdEntryStruct(CpdEntryStruct);
      if (CpdEntryStruct->ModuleType == FbmType) {
        DEBUG ((DEBUG_INFO, "Found FBM type!\n"));
      } else if (CpdEntryStruct->ModuleType == MetadataType) {
        DEBUG ((DEBUG_INFO, "Found MetaData type!\n"));
        FbBuffer = AllocatePages (EFI_SIZE_TO_PAGES (CpdEntryStruct->Length));
        if (FbBuffer == NULL) {
          Status = EFI_OUT_OF_RESOURCES;
          DEBUG ((DEBUG_INFO, "ERROR: could not allocate page for MetaData buffer\n"));
        } else {
          CopyMem (FbBuffer, (VOID *) (UINTN) (CpdHeaderPointer + (CpdEntryStruct->Offset & CPD_ENTRY_OFFSET_MASK)), CpdEntryStruct->Length);

          IupBuffer = (UINT32 *)FbBuffer;
          Data8Ptr = (UINT8 *) (UINTN) (IupBuffer);
          MetadataStruct1 = (META_DATA_STRUCT1 *)Data8Ptr;
          NoOfModules = MetadataStruct1->NoOfModules;
          DEBUG ((DEBUG_INFO, "No Of Modules : 0x%x\n", NoOfModules));
          Data8Ptr += sizeof(META_DATA_STRUCT1);

          //
          // Read Hash info from Metadata
          //
          for (Index = 0; Index < NoOfModules; Index++) {
            MetadataStruct2 = (META_DATA_STRUCT2 *)Data8Ptr;
            //
            // Create Hash for input firmware blob
            //
            HashAlg = MetadataStruct2->HashAlgo;
            DEBUG ((DEBUG_INFO, "Hash Algorithm : 0x%x\n", HashAlg));
            if (HashAlg == SIIP_HASHALG_RESERVED) {
              // No need to perform integrity check
              Status = EFI_SUCCESS;
            }
            HashDataSize = MetadataStruct2->HashSize;
            DEBUG ((DEBUG_INFO, "Hash Data Size : 0x%x\n", HashDataSize));
            GetHashSize (HashAlg, &MessageHashSize);
            DEBUG ((DEBUG_INFO, "Message Hash Size : 0x%x\n", HashDataSize));
            if (MessageHashSize != HashDataSize) {
              Status = EFI_SECURITY_VIOLATION;
              DEBUG ((DEBUG_INFO, "Message Hash Size and Hash Data Size DOES NOT MATCH.\n"));
            } else {
              DEBUG ((DEBUG_INFO, "Message Hash Size and Hash Data Size MATCHES!\n"));
            }

            MessageHash = AllocatePages (EFI_SIZE_TO_PAGES (MessageHashSize));
            if (MessageHash == NULL) {
              Status = EFI_OUT_OF_RESOURCES;
              DEBUG ((DEBUG_INFO, "ERROR: Unable to allocate memory for Message Hashes\n"));
            }
            HashData = AllocatePages (EFI_SIZE_TO_PAGES (HashDataSize));
            CopyMem (HashData, MetadataStruct2->Hash, HashDataSize);
            IupBuffer = (UINT32 *)HashData;
            DEBUG ((EFI_D_INFO, "Hash Data @ %x\n", IupBuffer));
            for (UINT32 fw_i = 0; fw_i < HashDataSize/4; fw_i++) {
              if ((fw_i % 10) == 0){
                DEBUG ((EFI_D_INFO, "\n"));
              }
              DEBUG ((EFI_D_INFO, "0x%08x ",*(IupBuffer + fw_i)));
            }
          }
        }
        DEBUG ((DEBUG_INFO, "\n\n\n"));
      } else if (CpdEntryStruct->ModuleType == ModuleType) {
        DEBUG ((DEBUG_INFO, "Found Module (code/static data) type\n"));
        FbBuffer = AllocatePages (EFI_SIZE_TO_PAGES (CpdEntryStruct->Length));
        if (FbBuffer == NULL) {
          Status = EFI_OUT_OF_RESOURCES;
          DEBUG ((DEBUG_INFO, "ERROR: Unable to allocate memory for module\n"));
        } else {
          CopyMem (FbBuffer, (VOID *) (UINTN) (CpdHeaderPointer + (CpdEntryStruct->Offset & CPD_ENTRY_OFFSET_MASK)), CpdEntryStruct->Length);

          IupBuffer = (UINT32 *)FbBuffer;
          DEBUG ((EFI_D_INFO, "Check Module dump %x\n", IupBuffer));
          for (UINT32 fw_i = 0; fw_i < 20; fw_i++) {
            if ((fw_i % 10) == 0){
              DEBUG ((EFI_D_INFO, "\n"));
            }
            DEBUG ((EFI_D_INFO, "0x%08x ",*(IupBuffer + fw_i)));
          }
          ModuleBuffer = (VOID *)IupBuffer;
          ModuleSize = CpdEntryStruct->Length;
          FwBuffer = ModuleBuffer;
          FwSize = ModuleSize;
        }
        DEBUG ((DEBUG_INFO, "\n\n\n"));
      }
      CpdEntryPointer += sizeof(CPD_ENTRY_STRUCT); // Point to next entry
      CpdEntryStruct = (CPD_ENTRY_STRUCT *)CpdEntryPointer;
    }
    if (SecureBootEnabled) {
      Status = CreateHash (HashAlg, ModuleBuffer, ModuleSize, MessageHash, MessageHashSize);
      if (!Status) {
        Status = EFI_SECURITY_VIOLATION;
        DEBUG ((DEBUG_INFO, "SECURITY VIOLATION when creating hash!\n"));
      }
      IupBuffer = (UINT32 *)MessageHash;
      DEBUG ((EFI_D_INFO, "Generated hash @ 0x%x\nMessage Hash Size generated is 0x%x\n", IupBuffer,MessageHashSize/4));
      for (UINT32 fw_i = 0; fw_i < MessageHashSize/4; fw_i++) {
        DEBUG ((EFI_D_INFO, "0x%08x ",*(IupBuffer + fw_i)));
      }
      DEBUG ((DEBUG_INFO, "\n"));
      //
      // Compare the hashes between input Vs computed
      //
      if (CompareMem (HashData, MessageHash, HashDataSize) != 0) {
        DEBUG ((DEBUG_INFO, "\n\nERROR! Compared hashes and failed!\n"));
        Status = EFI_SECURITY_VIOLATION;
        FwBuffer = 0;
        FwSize = 0;
      } else {
        DEBUG ((DEBUG_INFO, "\n\nCompared hashes and it matches!\n"));
        Status = EFI_SUCCESS;
        FwBuffer = ModuleBuffer;
        FwSize = ModuleSize;
      }
    } else {
      DEBUG ((DEBUG_INFO, "Verification skipped as Secure Boot are not enabled.\n"));
      Status = EFI_SUCCESS;
    }
    if (MessageHash != NULL) {
      FreePages (MessageHash, EFI_SIZE_TO_PAGES (MessageHashSize));
    }
    if (HashData != NULL) {
      FreePages (HashData, EFI_SIZE_TO_PAGES (HashDataSize));
    }
  } else {
    DEBUG ((DEBUG_INFO, "Correct header are not found. Did you sign?\n"));
    Status = EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "Verifying SIIP firmware\n"));
  return Status;
}

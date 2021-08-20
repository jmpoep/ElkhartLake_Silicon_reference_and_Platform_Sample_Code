/** @file
  This file contains the implementation of BpdtLib library.

  The library exposes an abstract interface for accessing boot data
  stored in the BPDT format on the Logical Boot Partition of the boot device.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include <PiPei.h>
#include <Ppi/BlockIo.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BpdtLib.h>

#define UFS_BOOT_LUN          1
#define STR_PLATFORM_SETTINGS   "PLTS"
//#define UFS_MAX_READ_SIZE     0x0
#define UFS_MAX_READ_SIZE     0x80000

/**
  Print FV name based on GUID
**/
VOID
PrintFvName (
  EFI_GUID  *FvName
)
{
  if (CompareGuid (FvName, &gEfiAuthenticatedVariableGuid)) {
    DEBUG ((DEBUG_INFO, "gEfiAuthenticatedVariableGuid"));
  } else if (CompareGuid (FvName, &gFspMemoryFvGuid)) {
    DEBUG ((DEBUG_INFO, "gFspMemoryFvGuid"));
  } else if (CompareGuid (FvName, &gFspTempRamFvGuid)) {
    DEBUG ((DEBUG_INFO, "gFspTempRamFvGuid"));
  } else if (CompareGuid (FvName, &gFspSiliconFvGuid)) {
    DEBUG ((DEBUG_INFO, "gFspSiliconFvGuid"));
  } else if (CompareGuid (FvName, &gFspSiliconRebasedFvGuid)) {
    DEBUG ((DEBUG_INFO, "gFspSiliconRebasedFvGuid"));
  } else if (CompareGuid (FvName, &gFvPreMemoryGuid)) {
    DEBUG ((DEBUG_INFO, "gFvPreMemoryGuid"));
  } else if (CompareGuid (FvName, &gFvPostMemoryUncompactGuid)) {
    DEBUG ((DEBUG_INFO, "gFvPostMemoryUncompactGuid"));
  } else if (CompareGuid (FvName, &gFvPostMemoryGuid)) {
    DEBUG ((DEBUG_INFO, "gFvPostMemoryGuid"));
  } else if (CompareGuid (FvName, &gFvFwBinariesGuid)) {
    DEBUG ((DEBUG_INFO, "gFvFwBinariesGuid"));
  } else if (CompareGuid (FvName, &gFvAdvancedUncompactGuid)) {
    DEBUG ((DEBUG_INFO, "gFvAdvancedUncompactGuid"));
  } else if (CompareGuid (FvName, &gFvAdvancedGuid)) {
    DEBUG ((DEBUG_INFO, "gFvAdvancedGuid"));
  } else if (CompareGuid (FvName, &gFvUefiBootUncompactGuid)) {
    DEBUG ((DEBUG_INFO, "gFvUefiBootUncompactGuid"));
  } else if (CompareGuid (FvName, &gFvUefiBootGuid)) {
    DEBUG ((DEBUG_INFO, "gFvUefiBootGuid"));
  } else if (CompareGuid (FvName, &gFvOsBootUncompactGuid)) {
    DEBUG ((DEBUG_INFO, "gFvOsBootUncompactGuid"));
  } else if (CompareGuid (FvName, &gFvOsBootGuid)) {
    DEBUG ((DEBUG_INFO, "gFvOsBootGuid"));
  } else if (CompareGuid (FvName, &gFvMicrocodeGuid)) {
    DEBUG ((DEBUG_INFO, "gFvMicrocodeGuid"));
  } else if (CompareGuid (FvName, &gFvTsnMacAddressGuid)) {
    DEBUG ((DEBUG_INFO, "gFvTsnMacAddressGuid"));
  } else if (CompareGuid (FvName, &gFvPseTsnIpConfigGuid)) {
    DEBUG ((DEBUG_INFO, "gFvPseTsnIpConfigGuid"));
  } else if (CompareGuid (FvName, &gFvTsnConfigGuid)) {
    DEBUG ((DEBUG_INFO, "gFvTsnConfigGuid"));
  } else if (CompareGuid (FvName, &gFvTccConfigGuid)) {
    DEBUG ((DEBUG_INFO, "gFvTccConfigGuid"));
  } else if (CompareGuid (FvName, &gFvOobConfigGuid)) {
    DEBUG ((DEBUG_INFO, "gFvOobConfigGuid"));
  } else if (CompareGuid (FvName, &gFvSiipFwGuid)) {
    DEBUG ((DEBUG_INFO, "gFvSiipFwGuid"));
  } else if (CompareGuid (FvName, &gFvSecurityGuid)) {
    DEBUG ((DEBUG_INFO, "gFvSecurityGuid"));
  } else if (CompareGuid (FvName, &gFvReserved1)) {
    DEBUG ((DEBUG_INFO, "gFvReserved1"));
  } else if (CompareGuid (FvName, &gFvReserved2)) {
    DEBUG ((DEBUG_INFO, "gFvReserved2"));
  }
}

/**
  Copy Length bytes from Source to Destination using SSE4.

  @param[out] Dst           The target of the copy request.
  @param[in]  Src           The place to copy from.
  @param[in]  SizeInBytes   The number of bytes to copy.
**/
VOID
CopyMemSse4 (
  OUT VOID  *Dst,
  IN  VOID  *Src,
  IN  UINTN SizeInBytes
  )
{
#if defined __GNUC__  // GCC compiler
  __asm__ __volatile__ (
    // Initialize pointers to start of the USWC memory
    "\n\t mov  %1, %%esi"  //mov esi, Src
    "\n\t mov  %1, %%edx"  //mov edx, Src

    // Initialize pointer to end of the USWC memory
    "\n\t add  %2, %%edx"  //add edx, SizeInBytes

    // Initialize pointer to start of the cacheable WB buffer
    "\n\t mov  %0, %%edi"  //mov edi, Dst

    // save xmm0 ~ xmm3 to stack
    "\n\t sub  $0x40, %%esp"
    "\n\t movdqu  %%xmm0, 0x00(%%esp)"
    "\n\t movdqu  %%xmm1, 0x10(%%esp)"
    "\n\t movdqu  %%xmm2, 0x20(%%esp)"
    "\n\t movdqu  %%xmm3, 0x30(%%esp)"

    // Start of Bulk Load loop
    "\n\t inner_start:"
    // Load data from USWC Memory using Streaming Load
    "\n\t MOVNTDQA  0x00(%%esi), %%xmm0"
    "\n\t MOVNTDQA  0x10(%%esi), %%xmm1"
    "\n\t MOVNTDQA  0x20(%%esi), %%xmm2"
    "\n\t MOVNTDQA  0x30(%%esi), %%xmm3"

    // Copy data to buffer
    "\n\t MOVDQA  %%xmm0, 0x00(%%edi)"
    "\n\t MOVDQA  %%xmm1, 0x10(%%edi)"
    "\n\t MOVDQA  %%xmm2, 0x20(%%edi)"
    "\n\t MOVDQA  %%xmm3, 0x30(%%edi)"

    // Increment pointers by cache line size and test for end of loop
    "\n\t add  $0x40, %%esi"
    "\n\t add  $0x40, %%edi"
    "\n\t cmp  %%edx, %%esi"
    "\n\t jne inner_start"

    // restore xmm0 ~ xmm3
    "\n\t mfence"
    "\n\t movdqu  0x00(%%esp), %%xmm0"
    "\n\t movdqu  0x10(%%esp), %%xmm1"
    "\n\t movdqu  0x20(%%esp), %%xmm2"
    "\n\t movdqu  0x30(%%esp), %%xmm3"
    "\n\t add  $0x40, %%esp" // stack cleanup
    ::"a"(Dst),"b"(Src),"c"(SizeInBytes)
    :"%esi", "%edi", "%edx"
  );
#else //MSFT compiler
  _asm {
    // Initialize pointers to start of the USWC memory
    mov esi, Src
    mov edx, Src

    // Initialize pointer to end of the USWC memory
    add edx, SizeInBytes

    // Initialize pointer to start of the cacheable WB buffer
    mov edi, Dst

    // save xmm0 ~ xmm3 to stack
    sub     esp, 040h
    movdqu  [esp], xmm0
    movdqu  [esp + 16], xmm1
    movdqu  [esp + 32], xmm2
    movdqu  [esp + 48], xmm3

    // Start of Bulk Load loop
    inner_start:
    // Load data from USWC Memory using Streaming Load
    MOVNTDQA xmm0, xmmword ptr [esi]
    MOVNTDQA xmm1, xmmword ptr [esi + 16]
    MOVNTDQA xmm2, xmmword ptr [esi + 32]
    MOVNTDQA xmm3, xmmword ptr [esi + 48]

    // Copy data to buffer
    MOVDQA xmmword ptr [edi], xmm0
    MOVDQA xmmword ptr [edi + 16], xmm1
    MOVDQA xmmword ptr [edi + 32], xmm2
    MOVDQA xmmword ptr [edi + 48], xmm3

    // Increment pointers by cache line size and test for end of loop
    add esi, 040h
    add edi, 040h
    cmp esi, edx
    jne inner_start

    // restore xmm0 ~ xmm3
    mfence
    movdqu  xmm0, [esp]
    movdqu  xmm1, [esp + 16]
    movdqu  xmm2, [esp + 32]
    movdqu  xmm3, [esp + 48]
    add     esp, 040h // stack cleanup
  }
#endif
}

/**
  Read data from UFS into Memory.
  The caller is responsible for calling FreePages on DataBuffer if necessary.

  @param    DataBuffer              A pointer to the buffer address
  @param    Offset                  Offset of the data to read (4k aligned)
  @param    DataSize                Size of the data to read

  @retval   EFI_SUCCESS             The operation completed successfully
  @retval   EFI_INVALID_PARAMETER   DataBuffer was NULL
  @retval   EFI_NOT_FOUND           Problems reading from UFS
  @retval   EFI_OUT_OF_RESOURCES    Couldn't allocate the buffer
**/
EFI_STATUS
EFIAPI
ReadFromUfs (
  IN OUT  VOID                  **DataBuffer,
  IN      UINT32                Offset,
  IN      UINTN                 DataSize
  )
{
  EFI_STATUS                    Status;
  EFI_PEI_SERVICES              **PeiServices;
  EFI_PEI_RECOVERY_BLOCK_IO_PPI *BlockIoPpi;
  EFI_PEI_BLOCK_IO_MEDIA        Media;
  EFI_PEI_LBA                   StartBlock;
  UINTN                         UfsBufferSize;
  VOID                          *UfsBuffer;
  UINTN                         DeviceIndex;

  DeviceIndex = UFS_BOOT_LUN + 1;
  if (DataBuffer == NULL) {
    DEBUG ((DEBUG_ERROR, "DataBuffer pointer is NULL!\n"));
    return EFI_INVALID_PARAMETER;
  }
  if (Offset % SIZE_4KB) {
    DEBUG ((DEBUG_ERROR, "Offset is not 4k aligned!\n"));
    return EFI_INVALID_PARAMETER;
  }

  *DataBuffer = NULL;
  if (DataSize == 0) {
    return EFI_SUCCESS;
  }

  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer();

  //Find UFS Block IO PPI
  Status = PeiServicesLocatePpi (
            &gEfiPeiVirtualBlockIoPpiGuid,
            0,
            NULL,
            (VOID **) &BlockIoPpi
            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Virtual Block IO PPI not found!\n"));
    ASSERT_EFI_ERROR (Status);
    return EFI_NOT_FOUND;
  }

  // Check if boot media is present
  ZeroMem (&Media, sizeof(Media));
  Status = BlockIoPpi->GetBlockDeviceMediaInfo (
                        PeiServices,
                        BlockIoPpi,
                        DeviceIndex,
                        &Media
                        );
  if (EFI_ERROR (Status) || !Media.MediaPresent) {
    DEBUG ((DEBUG_ERROR, "Fail to get MediaInfo or boot media not present\n"));
    return EFI_NOT_FOUND;
  }

  //Execute the read operation
  StartBlock =         (EFI_PEI_LBA) EFI_SIZE_TO_PAGES (Offset);
  UfsBufferSize = EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (DataSize));
  UfsBuffer =         AllocatePages (EFI_SIZE_TO_PAGES (DataSize));
  if (UfsBuffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  Status = BlockIoPpi->ReadBlocks (
                        PeiServices,
                        BlockIoPpi,
                        DeviceIndex,
                        StartBlock,
                        UfsBufferSize,
                        UfsBuffer
                        );

  *DataBuffer = UfsBuffer;
  return Status;
}

/**
  Read the UFS Descriptor region.

  @param[out] DescriptorRegionOffset The address of Descriptor region in IFWI.
  @param[out] DescriptorRegionSize   The size of Descriptor region in bytes.

  @retval EFI_SUCCESS           The operation returns successfully.
  @retval others                If get descriptor region fails.
**/
EFI_STATUS
EFIAPI
GetUfsDescriptorRegion (
  OUT UINT32 *DescriptorRegionOffset,
  OUT UINT32 *DescriptorRegionSize
  )
{
  VOID                          *GuidHobPtr;
  CSE_LAYOUT_POINTERS           *CseLayoutPointers;
  FLASH_PARTITION_TABLE_HEADER  *FptHeader;
  FLASH_PARTITION_TABLE_ENTRY   *FptEntry;
  VOID                          *Buffer;
  UINT32                        Index;
  EFI_STATUS                    Status = EFI_SUCCESS;

  GuidHobPtr = GetFirstGuidHob (&gIfwiCseLayoutPointersHobGuid);
  if (GuidHobPtr == NULL) {
  DEBUG ((DEBUG_ERROR, "IfwiCseLayoutPointerHob Error: IFWI CSE Layout Pointer HOB does not exist!\n"));
    Status = EFI_INVALID_PARAMETER;
    goto Exit;

  }
  CseLayoutPointers = (CSE_LAYOUT_POINTERS *) GET_GUID_HOB_DATA (GuidHobPtr);

  //
  // Read Platform Settings FTP
  //
  Buffer = AllocatePool (0x1000);
  if (Buffer == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Exit;
  }
  Status = ReadFromUfs (&Buffer, CseLayoutPointers->Lbp5Offset, (UINT32) 0x1000);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "FPT Header read failed - %r\n", Status));
    goto Exit;

  }

  FptHeader = (FLASH_PARTITION_TABLE_HEADER*) Buffer;
  FptEntry = (FLASH_PARTITION_TABLE_ENTRY *) (FptHeader + 1);

  //
  // Get Platform Settings Offset and Size
  //
  for (Index = 0; Index < FptHeader->NumberOfEntries; Index++) {
    if (AsciiStrCmp ((CONST CHAR8 *) FptEntry->PartitionName, STR_PLATFORM_SETTINGS) == 0) {
      DEBUG ((DEBUG_ERROR, "Descriptor region found\n"));
      *DescriptorRegionOffset = CseLayoutPointers->Lbp5Offset + FptEntry->Offset;
      *DescriptorRegionSize = FptEntry->Length;
      break;
    }
    DEBUG ((DEBUG_ERROR, "FPT Entry offset: 0x%X\n", FptEntry->Offset));
    FptEntry++;
  }
  DEBUG ((DEBUG_ERROR, "Descriptor region offset: 0x%X\n", *DescriptorRegionOffset));
  if (Index == FptHeader->NumberOfEntries) {
    DEBUG ((DEBUG_ERROR, "Descriptor region not found\n"));
    Status = EFI_NOT_FOUND;
    goto Exit;
  }
Exit:
  if (Buffer != NULL) {
    FreePool (Buffer);
  }
  DEBUG ((DEBUG_INFO, "GetUfsDescriptorRegion - %r\n", Status));
  return Status;
  }

/**
  Provides a pointer to the CSE Layout Pointers structure, which is stored in a HOB.
  If the HOB does not exist, the HOB is created by reading from UFS.

  @param[out]  CseLayoutPointers      Pointer to the CSE Layout Pointers HOB data.

  @retval      EFI_SUCCESS            The CSE Layout Pointers structure was retrieved.
  @retval      EFI_OUT_OF_RESOURCES   Could not create a HOB to store the data.
  @retval      Others                 An error occurred reading from UFS.
**/
EFI_STATUS
EFIAPI
GetCseLayoutPointers (
  OUT CSE_LAYOUT_POINTERS   **CseLayoutPointers
  )
{
  EFI_STATUS            Status;
  VOID                  *UfsBuffer;
  EFI_HOB_GUID_TYPE     *GuidHobPtr;

  //Default to NULL to allow failure-checking from caller
  *CseLayoutPointers = NULL;
  Status = EFI_SUCCESS;

  //Check if data has already been retrieved
  GuidHobPtr = GetFirstGuidHob (&gIfwiCseLayoutPointersHobGuid);

  if (GuidHobPtr != NULL) {
    //Retrieve a pointer to the data
    *CseLayoutPointers = (CSE_LAYOUT_POINTERS *) GET_GUID_HOB_DATA (GuidHobPtr);
  } else {
    //Get the data from UFS
    Status = ReadFromUfs (&UfsBuffer, 0, sizeof (CSE_LAYOUT_POINTERS));
    if (EFI_ERROR (Status)) {
      return Status;
    }
    //Store the data in a HOB
    *CseLayoutPointers = (CSE_LAYOUT_POINTERS *) BuildGuidDataHob (
                                                  &gIfwiCseLayoutPointersHobGuid,
                                                  UfsBuffer,
                                                  sizeof (CSE_LAYOUT_POINTERS)
                                                  );
    //Cleanup
    FreePages(UfsBuffer, EFI_SIZE_TO_PAGES (sizeof (CSE_LAYOUT_POINTERS)));
    if (*CseLayoutPointers == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
  }

  return Status;
}

/**
  Provides a pointer to the BIOS region of the IFWI (BPDT 4).
  The BIOS region is stored in memory.
  The pointer is stored in a HOB.
  If the HOB does not exist, the HOB is created by reading from UFS.

  @param[out]  BiosRegion             Pointer to the BIOS region stored in memory.

  @retval      EFI_SUCCESS            The BIOS region was retrieved.
  @retval      EFI_OUT_OF_RESOURCES   Could not create a HOB to store the pointer.
  @retval      Others                 An error occurred retrieving CSE Layout pointers,
                                      or reading from UFS.
**/
EFI_STATUS
EFIAPI
GetBiosRegion (
  IN OUT VOID           **BiosRegion
  )
{
  EFI_STATUS                        Status;
  VOID                              *GuidHobPtr;
  CSE_LAYOUT_POINTERS               *CseLayoutPointers;
  EFI_PEI_SERVICES                  **PeiServices;
  EFI_PEI_RECOVERY_BLOCK_IO_PPI     *BlockIoPpi;
  EFI_PEI_LBA                       StartBlock;
  UINTN                             UfsReadBufferSize;
  VOID                              *UfsBuffer;
  VOID                              *TempBuffer;
  VOID                              **DataBuffer;
  UINTN                             DeviceIndex;
  UINT32                            UfsMaxReadSize;
  UINT32                            RemainingReadSize;
  UINT32                            CurrentReadSize;
  UINT32                            CurrentReadAddress;

  UfsReadBufferSize  = 0;
  UfsMaxReadSize     = UFS_MAX_READ_SIZE;
  DeviceIndex        = UFS_BOOT_LUN + 1;
  RemainingReadSize  = 0;
  CurrentReadSize    = 0;
  CurrentReadAddress = 0;

  PeiServices = (EFI_PEI_SERVICES **) GetPeiServicesTablePointer();

  //Find UFS Block IO PPI
  Status = PeiServicesLocatePpi (
            &gEfiPeiVirtualBlockIoPpiGuid,
            0,
            NULL,
            (VOID **) &BlockIoPpi
            );

  DEBUG ((DEBUG_INFO, "GetBiosRegion () - Start\n"));

  if (BiosRegion == NULL) {
    DEBUG ((DEBUG_ERROR, "BiosRegion pointer is NULL!\n"));
    return EFI_INVALID_PARAMETER;
  }

  //Default to NULL to allow failure-checking from caller
  *BiosRegion = NULL;
  Status = EFI_SUCCESS;

  //Check if data has already been retrieved
  GuidHobPtr = GetFirstGuidHob (&gIfwiBiosRegionPointerHobGuid);
  if (GuidHobPtr != NULL) {
    //Retrieve a pointer to the data
    *BiosRegion = *((VOID **) GET_GUID_HOB_DATA (GuidHobPtr));
    DEBUG ((DEBUG_INFO, "*BiosRegion =  0x%08X\n", *BiosRegion));
    return Status;
  }

  //Retrieve CSE Layout Pointers to find BIOS region location and build HOB
  Status = GetCseLayoutPointers (&CseLayoutPointers);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  //Read the BIOS region from UFS
  DEBUG ((DEBUG_INFO, "Lbp4Offset = 0x%08X\n", CseLayoutPointers->Lbp4Offset));
  DEBUG ((DEBUG_INFO, "Lbp4Size   = 0x%08X\n", CseLayoutPointers->Lbp4Size));

  if (UfsMaxReadSize > 0) {
    UfsBuffer          = AllocatePages (EFI_SIZE_TO_PAGES (CseLayoutPointers->Lbp4Size));
    RemainingReadSize  = CseLayoutPointers->Lbp4Size;
    CurrentReadAddress = CseLayoutPointers->Lbp4Offset;
    TempBuffer         = (UINT8 *) UfsBuffer;
    if (UfsMaxReadSize > CseLayoutPointers->Lbp4Size) {
      UfsMaxReadSize = CseLayoutPointers->Lbp4Size;
    }
    while (RemainingReadSize > 0) {
      if (RemainingReadSize >= UfsMaxReadSize) {
        CurrentReadSize = UfsMaxReadSize;
      } else {
        CurrentReadSize = RemainingReadSize;
      }
      UfsReadBufferSize = EFI_PAGES_TO_SIZE (EFI_SIZE_TO_PAGES (CurrentReadSize));
      StartBlock =  (EFI_PEI_LBA) EFI_SIZE_TO_PAGES (CurrentReadAddress);
      DEBUG ((DEBUG_INFO, "Reading UFS Address: 0x%X to Buffer Address: 0x%X with Size: 0x%X\n", CurrentReadAddress, TempBuffer, CurrentReadSize));

      Status = BlockIoPpi->ReadBlocks (
                             PeiServices,
                             BlockIoPpi,
                             DeviceIndex,
                             StartBlock,
                             UfsReadBufferSize,
                             TempBuffer
                             );
      RemainingReadSize -= CurrentReadSize;
      if (RemainingReadSize > CseLayoutPointers->Lbp4Size) {
        return EFI_INVALID_PARAMETER;
      }
      CurrentReadAddress += CurrentReadSize;
      TempBuffer = (UINT8 *) TempBuffer + CurrentReadSize;
    }

    DataBuffer = BiosRegion;
    *DataBuffer = UfsBuffer;
  } else {
    Status = ReadFromUfs (
              BiosRegion,
              CseLayoutPointers->Lbp4Offset,
              CseLayoutPointers->Lbp4Size
              );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "ReadFromUfs() - %r\n", Status));
      return Status;
    }
  }
  //Store the pointer in a HOB
  GuidHobPtr = BuildGuidDataHob (
                &gIfwiBiosRegionPointerHobGuid,
                BiosRegion,
                sizeof (VOID *)
                );
  if (GuidHobPtr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  if (*BiosRegion != *((VOID **) GuidHobPtr)) {
    DEBUG ((DEBUG_ERROR, "BIOS REGION POINTER MISMATCH!\n"));
  }
  DEBUG ((DEBUG_INFO, "GetBiosRegion () - End\n"));
  return Status;
}

/**
  Returns an Entry of a specific Type from the provided BPDT.

  @param[in]   Type                   Entry type to return.
  @param[in]   Bpdt                   Pointer to a BPDT.
  @param[out]  BpdtEntry              Pointer to a BPDT Entry.

  @retval      EFI_SUCCESS            The BPDT Entry was found.
  @retval      EFI_NOT_FOUND          The BPDT Entry was not found.
  @retval      Others                 An error occurred.
**/
EFI_STATUS
EFIAPI
GetEntryFromBpdt (
  IN  BPDT_ENTRY_TYPE   Type,
  IN  BPDT_HEADER       *Bpdt,
  OUT BPDT_ENTRY        **Entry
  )
{
  UINTN                 Index;
  BPDT_ENTRY            *EntryList;

  if (Type >= BpdtMaxType) {
    DEBUG((DEBUG_ERROR, "BPDT Entry Type %d is greater than max type %d!\n", Type, BpdtMaxType-1));
    return EFI_INVALID_PARAMETER;
  }

  if ((Bpdt == NULL) || (Entry == NULL)) {
    DEBUG((DEBUG_ERROR, "Parameter is NULL!\n"));
    return EFI_INVALID_PARAMETER;
  }

  //Default to NULL to allow failure-checking from caller
  *Entry = NULL;

  if (Bpdt->Signature != BPDT_SIGN_GREEN) {
    DEBUG ((DEBUG_INFO, "Signature of BPDT Header is invalid - stop parsing\n"));
    return EFI_INVALID_PARAMETER;
  }

  //Walk BPDT Entry List
  EntryList = (BPDT_ENTRY *) (Bpdt + 1);
  for (Index = 0; Index < Bpdt->DescriptorCount; Index++) {
    *Entry = &EntryList[Index];
    if ((BPDT_ENTRY_TYPE) (*Entry)->Type == Type) {
      DEBUG ((DEBUG_INFO, "Entry Type %d Offset = 0x%08X\n", Type, (*Entry)->SubPartitionOffset));
      DEBUG ((DEBUG_INFO, "Entry Type %d Size   = 0x%08X\n", Type, (*Entry)->SubPartitionSize));
      return EFI_SUCCESS;
    }
  }

  return EFI_NOT_FOUND;
}

/**
  Populates a SUB_PARTITION_DATA struct from the provided BPDT & EntryType.

  @param[in]      Type                Entry type to return.
  @param[in]      Bpdt                Pointer to a BPDT.
  @param[in, out] PayloadData         Pointer to SUB_PARTITION_DATA struct.

  @retval      EFI_SUCCESS            The BPDT Entry was found.
  @retval      EFI_NOT_FOUND          The BPDT Entry was not found.
  @retval      Others                 An error occurred.
**/
EFI_STATUS
EFIAPI
GetSubPartitionData (
  IN      BPDT_ENTRY_TYPE     Type,
  IN      BPDT_HEADER         *Bpdt,
  IN OUT  SUB_PARTITION_DATA  *PayloadData
  )
{
  EFI_STATUS            Status;
  BPDT_ENTRY            *BpdtEntry;

  if ((Bpdt == NULL) || (PayloadData == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Status = GetEntryFromBpdt (Type, Bpdt, &BpdtEntry);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  PayloadData->Address = (VOID *) ((UINT32) Bpdt + BpdtEntry->SubPartitionOffset);
  PayloadData->Size = BpdtEntry->SubPartitionSize;

  return Status;
}


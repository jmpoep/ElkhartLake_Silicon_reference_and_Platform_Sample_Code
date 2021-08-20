/** @file
  Routines supporting partition discovery and
  logical device reading

Copyright (c) 2006 - 2019, Intel Corporation. All rights reserved.<BR>

This program and the accompanying materials are licensed and made available
under the terms and conditions of the BSD License which accompanies this
distribution. The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <IndustryStandard/Mbr.h>
#include <IndustryStandard/ElTorito.h>
#include "FatLitePeim.h"

//
// RPPO-CNL-0087: RoyalParkOverrideBegin
//
//
// GPT Partition Entry Status
//
typedef struct {
  BOOLEAN OutOfRange :2;
  BOOLEAN Overlap :2;
  BOOLEAN OsSpecific:4;
} EFI_PARTITION_ENTRY_STATUS;

UINT32 *mCrcTablePtr;

/**
  The CalculateCrc32 routine.

  @param[in]      Data        The buffer contaning the data to be processed
  @param[in]      DataSize    The size of data to be processed
  @param[in,out]  CrcOut      A pointer to the caller allocated UINT32 that on
                              contains the CRC32 checksum of Data

  @retval EFI_SUCCESS               Calculation is successful.
  @retval EFI_INVALID_PARAMETER     Data / CrcOut = NULL, or DataSize = 0

**/
EFI_STATUS
PartitionCalculateCrc32 (
  IN  UINT8                             *Data,
  IN  UINTN                             DataSize,
  IN OUT UINT32                         *CrcOut
  )
{
  UINT32  Crc;
  UINTN   Index;
  UINT8   *Ptr;

  if ((DataSize == 0) || (Data == NULL) || (CrcOut == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  Crc = 0xffffffff;
  for (Index = 0, Ptr = Data; Index < DataSize; Index++, Ptr++) {
    Crc = (Crc >> 8) ^ mCrcTablePtr[(UINT8) Crc ^ *Ptr];
  }

  *CrcOut = Crc ^ 0xffffffff;

  return EFI_SUCCESS;
}
/**
  This function finds GPT partitions. Main algorithm
  is ported from DXE partition driver.

  @param  PrivateData       The global memory map
  @param  ParentBlockDevNo  The parent block device

  @retval TRUE              New partitions are detected and logical block devices
                            are  added to block device array
  @retval FALSE             No New partitions are added;

**/
BOOLEAN
FatFindGptPartitions (
  IN  PEI_FAT_PRIVATE_DATA *PrivateData,
  IN  UINTN                ParentBlockDevNo
  );
//
// RPPO-CNL-0087: RoyalParkOverrideEnd
//

/**
  This function finds Mbr partitions. Main algorithm
  is ported from DXE partition driver.

  @param  PrivateData       The global memory map
  @param  ParentBlockDevNo  The parent block device

  @retval TRUE              New partitions are detected and logical block devices
                            are  added to block device array
  @retval FALSE             No New partitions are added;

**/
BOOLEAN
FatFindMbrPartitions (
  IN  PEI_FAT_PRIVATE_DATA *PrivateData,
  IN  UINTN                ParentBlockDevNo
  );


/**
  This function finds partitions (logical devices) in physical block devices.

  @param  PrivateData       Global memory map for accessing global variables.

**/
VOID
FatFindPartitions (
  IN  PEI_FAT_PRIVATE_DATA  *PrivateData
  )
{
  BOOLEAN Found;
  UINTN   Index;

  do {
    Found = FALSE;

    for (Index = 0; Index < PrivateData->BlockDeviceCount; Index++) {
      if (!PrivateData->BlockDevice[Index].PartitionChecked) {
        Found = FatFindGptPartitions (PrivateData, Index); // RPPO-CNL-0087: RoyalParkOverrideContent
        if (!Found) {
          Found = FatFindMbrPartitions (PrivateData, Index); // RPPO-CNL-0087: RoyalParkOverrideContent
        }
      }
    }
  } while (Found && PrivateData->BlockDeviceCount <= PEI_FAT_MAX_BLOCK_DEVICE);
}


/**
  This function finds Eltorito partitions. Main algorithm
  is ported from DXE partition driver.

  @param  PrivateData       The global memory map
  @param  ParentBlockDevNo  The parent block device

  @retval TRUE              New partitions are detected and logical block devices
                            are  added to block device array
  @retval FALSE             No New partitions are added;

**/
BOOLEAN
FatFindEltoritoPartitions (
  IN  PEI_FAT_PRIVATE_DATA *PrivateData,
  IN  UINTN                ParentBlockDevNo
  )
{
  EFI_STATUS              Status;
  BOOLEAN                 Found;
  PEI_FAT_BLOCK_DEVICE    *BlockDev;
  PEI_FAT_BLOCK_DEVICE    *ParentBlockDev;
  UINT32                  VolDescriptorLba;
  UINT32                  Lba;
  CDROM_VOLUME_DESCRIPTOR *VolDescriptor;
  ELTORITO_CATALOG        *Catalog;
  UINTN                   Check;
  UINTN                   Index;
  UINTN                   MaxIndex;
  UINT16                  *CheckBuffer;
  UINT32                  SubBlockSize;
  UINT32                  SectorCount;
  UINT32                  VolSpaceSize;

  if (ParentBlockDevNo > PEI_FAT_MAX_BLOCK_DEVICE - 1) {
    return FALSE;
  }

  Found           = FALSE;
  ParentBlockDev  = &(PrivateData->BlockDevice[ParentBlockDevNo]);
  VolSpaceSize    = 0;

  //
  // CD_ROM has the fixed block size as 2048 bytes
  //
  if (ParentBlockDev->BlockSize != 2048) {
    return FALSE;
  }

  VolDescriptor = (CDROM_VOLUME_DESCRIPTOR *) PrivateData->BlockData;
  Catalog       = (ELTORITO_CATALOG *) VolDescriptor;

  //
  // the ISO-9660 volume descriptor starts at 32k on the media
  // and CD_ROM has the fixed block size as 2048 bytes, so...
  //
  VolDescriptorLba = 15;
  //
  // ((16*2048) / Media->BlockSize) - 1;
  //
  // Loop: handle one volume descriptor per time
  //
  while (TRUE) {

    VolDescriptorLba += 1;
    if (VolDescriptorLba > ParentBlockDev->LastBlock) {
      //
      // We are pointing past the end of the device so exit
      //
      break;
    }

    Status = FatReadBlock (
              PrivateData,
              ParentBlockDevNo,
              VolDescriptorLba,
              ParentBlockDev->BlockSize,
              VolDescriptor
              );
    if (EFI_ERROR (Status)) {
      break;
    }
    //
    // Check for valid volume descriptor signature
    //
    if (VolDescriptor->Unknown.Type == CDVOL_TYPE_END ||
        CompareMem (VolDescriptor->Unknown.Id, CDVOL_ID, sizeof (VolDescriptor->Unknown.Id)) != 0
        ) {
      //
      // end of Volume descriptor list
      //
      break;
    }
    //
    // Read the Volume Space Size from Primary Volume Descriptor 81-88 byte
    //
    if (VolDescriptor->Unknown.Type == CDVOL_TYPE_CODED) {
      VolSpaceSize = VolDescriptor->PrimaryVolume.VolSpaceSize[1];
    }
    //
    // Is it an El Torito volume descriptor?
    //
    if (CompareMem (
          VolDescriptor->BootRecordVolume.SystemId,
          CDVOL_ELTORITO_ID,
          sizeof (CDVOL_ELTORITO_ID) - 1
          ) != 0) {
      continue;
    }
    //
    // Read in the boot El Torito boot catalog
    //
    Lba = UNPACK_INT32 (VolDescriptor->BootRecordVolume.EltCatalog);
    if (Lba > ParentBlockDev->LastBlock) {
      continue;
    }

    Status = FatReadBlock (
              PrivateData,
              ParentBlockDevNo,
              Lba,
              ParentBlockDev->BlockSize,
              Catalog
              );
    if (EFI_ERROR (Status)) {
      continue;
    }
    //
    // We don't care too much about the Catalog header's contents, but we do want
    // to make sure it looks like a Catalog header
    //
    if (Catalog->Catalog.Indicator != ELTORITO_ID_CATALOG || Catalog->Catalog.Id55AA != 0xAA55) {
      continue;
    }

    Check       = 0;
    CheckBuffer = (UINT16 *) Catalog;
    for (Index = 0; Index < sizeof (ELTORITO_CATALOG) / sizeof (UINT16); Index += 1) {
      Check += CheckBuffer[Index];
    }

    if ((Check & 0xFFFF) != 0) {
      continue;
    }

    MaxIndex = ParentBlockDev->BlockSize / sizeof (ELTORITO_CATALOG);
    for (Index = 1; Index < MaxIndex; Index += 1) {
      //
      // Next entry
      //
      Catalog += 1;

      //
      // Check this entry
      //
      if (Catalog->Boot.Indicator != ELTORITO_ID_SECTION_BOOTABLE || Catalog->Boot.Lba == 0) {
        continue;
      }

      SubBlockSize  = 512;
      SectorCount   = Catalog->Boot.SectorCount;

      switch (Catalog->Boot.MediaType) {

      case ELTORITO_NO_EMULATION:
        SubBlockSize  = ParentBlockDev->BlockSize;
        SectorCount   = Catalog->Boot.SectorCount;
        break;

      case ELTORITO_HARD_DISK:
        break;

      case ELTORITO_12_DISKETTE:
        SectorCount = 0x50 * 0x02 * 0x0F;
        break;

      case ELTORITO_14_DISKETTE:
        SectorCount = 0x50 * 0x02 * 0x12;
        break;

      case ELTORITO_28_DISKETTE:
        SectorCount = 0x50 * 0x02 * 0x24;
        break;

      default:
        SectorCount   = 0;
        SubBlockSize  = ParentBlockDev->BlockSize;
        break;
      }

      if (SectorCount < 2) {
        SectorCount = (VolSpaceSize > ParentBlockDev->LastBlock + 1) ? (UINT32) (ParentBlockDev->LastBlock - Catalog->Boot.Lba + 1) : (UINT32) (VolSpaceSize - Catalog->Boot.Lba);
      }
      //
      // Register this partition
      //
      if (PrivateData->BlockDeviceCount < PEI_FAT_MAX_BLOCK_DEVICE) {

        Found                       = TRUE;

        BlockDev                    = &(PrivateData->BlockDevice[PrivateData->BlockDeviceCount]);

        BlockDev->BlockSize         = SubBlockSize;
        BlockDev->LastBlock         = SectorCount - 1;
        BlockDev->IoAlign           = ParentBlockDev->IoAlign;
        BlockDev->Logical           = TRUE;
        BlockDev->PartitionChecked  = FALSE;
        BlockDev->StartingPos       = MultU64x32 (Catalog->Boot.Lba, ParentBlockDev->BlockSize);
        BlockDev->ParentDevNo       = ParentBlockDevNo;

        PrivateData->BlockDeviceCount++;
      }
    }
  }

  ParentBlockDev->PartitionChecked = TRUE;

  return Found;

}


/**
  Test to see if the Mbr buffer is a valid MBR

  @param  Mbr               Parent Handle
  @param  LastLba           Last Lba address on the device.

  @retval TRUE              Mbr is a Valid MBR
  @retval FALSE             Mbr is not a Valid MBR

**/
BOOLEAN
PartitionValidMbr (
  IN  MASTER_BOOT_RECORD      *Mbr,
  IN  EFI_PEI_LBA             LastLba
  )
{
  UINT32  StartingLBA;
  UINT32  EndingLBA;
  UINT32  NewEndingLBA;
  INTN    Index1;
  INTN    Index2;
  BOOLEAN MbrValid;

  if (Mbr->Signature != MBR_SIGNATURE) {
    return FALSE;
  }
  //
  // The BPB also has this signature, so it can not be used alone.
  //
  MbrValid = FALSE;
  for (Index1 = 0; Index1 < MAX_MBR_PARTITIONS; Index1++) {
    if (Mbr->Partition[Index1].OSIndicator == 0x00 || UNPACK_UINT32 (Mbr->Partition[Index1].SizeInLBA) == 0) {
      continue;
    }

    MbrValid    = TRUE;
    StartingLBA = UNPACK_UINT32 (Mbr->Partition[Index1].StartingLBA);
    EndingLBA   = StartingLBA + UNPACK_UINT32 (Mbr->Partition[Index1].SizeInLBA) - 1;
    if (EndingLBA > LastLba) {
      //
      // Compatability Errata:
      //  Some systems try to hide drive space with thier INT 13h driver
      //  This does not hide space from the OS driver. This means the MBR
      //  that gets created from DOS is smaller than the MBR created from
      //  a real OS (NT & Win98). This leads to BlockIo->LastBlock being
      //  wrong on some systems FDISKed by the OS.
      //
      //  return FALSE Because no block devices on a system are implemented
      //  with INT 13h
      //
      return FALSE;
    }

    for (Index2 = Index1 + 1; Index2 < MAX_MBR_PARTITIONS; Index2++) {
      if (Mbr->Partition[Index2].OSIndicator == 0x00 || UNPACK_INT32 (Mbr->Partition[Index2].SizeInLBA) == 0) {
        continue;
      }

      NewEndingLBA = UNPACK_UINT32 (Mbr->Partition[Index2].StartingLBA) + UNPACK_UINT32 (Mbr->Partition[Index2].SizeInLBA) - 1;
      if (NewEndingLBA >= StartingLBA && UNPACK_UINT32 (Mbr->Partition[Index2].StartingLBA) <= EndingLBA) {
        //
        // This region overlaps with the Index1'th region
        //
        return FALSE;
      }
    }
  }
  //
  // Non of the regions overlapped so MBR is O.K.
  //
  return MbrValid;
}


/**
  This function finds Mbr partitions. Main algorithm
  is ported from DXE partition driver.

  @param  PrivateData       The global memory map
  @param  ParentBlockDevNo  The parent block device

  @retval TRUE              New partitions are detected and logical block devices
                            are  added to block device array
  @retval FALSE             No New partitions are added;

**/
BOOLEAN
FatFindMbrPartitions (
  IN  PEI_FAT_PRIVATE_DATA *PrivateData,
  IN  UINTN                ParentBlockDevNo
  )
{
  EFI_STATUS            Status;
  MASTER_BOOT_RECORD    *Mbr;
  UINTN                 Index;
  BOOLEAN               Found;
  PEI_FAT_BLOCK_DEVICE  *ParentBlockDev;
  PEI_FAT_BLOCK_DEVICE  *BlockDev;

  if (ParentBlockDevNo > PEI_FAT_MAX_BLOCK_DEVICE - 1) {
    return FALSE;
  }

  ParentBlockDev  = &(PrivateData->BlockDevice[ParentBlockDevNo]);

  Found           = FALSE;
  Mbr             = (MASTER_BOOT_RECORD *) PrivateData->BlockData;

  Status = FatReadBlock (
            PrivateData,
            ParentBlockDevNo,
            0,
            ParentBlockDev->BlockSize,
            Mbr
            );

  if (EFI_ERROR (Status) || !PartitionValidMbr (Mbr, ParentBlockDev->LastBlock)) {
    goto Done;
  }
  //
  // We have a valid mbr - add each partition
  //
  for (Index = 0; Index < MAX_MBR_PARTITIONS; Index++) {
    if (Mbr->Partition[Index].OSIndicator == 0x00 || UNPACK_INT32 (Mbr->Partition[Index].SizeInLBA) == 0) {
      //
      // Don't use null MBR entries
      //
      continue;
    }
    //
    // Register this partition
    //
    if (PrivateData->BlockDeviceCount < PEI_FAT_MAX_BLOCK_DEVICE) {

      Found                       = TRUE;

      BlockDev                    = &(PrivateData->BlockDevice[PrivateData->BlockDeviceCount]);

      BlockDev->BlockSize         = MBR_SIZE;
      BlockDev->LastBlock         = UNPACK_INT32 (Mbr->Partition[Index].SizeInLBA) - 1;
      BlockDev->IoAlign           = ParentBlockDev->IoAlign;
      BlockDev->Logical           = TRUE;
      BlockDev->PartitionChecked  = FALSE;
      BlockDev->StartingPos = MultU64x32 (
                                UNPACK_INT32 (Mbr->Partition[Index].StartingLBA),
                                ParentBlockDev->BlockSize
                                );
      BlockDev->ParentDevNo = ParentBlockDevNo;

      PrivateData->BlockDeviceCount++;
    }
  }

Done:

  ParentBlockDev->PartitionChecked = TRUE;
  return Found;
}
//
// RPPO-CNL-0087: RoyalParkOverrideBegin
//
/**
  Checks the CRC32 value in the table header.

  @param  MaxSize   Max Size limit
  @param  Size      The size of the table
  @param  Hdr       Table to check

  @return TRUE    CRC Valid
  @return FALSE   CRC Invalid

**/
BOOLEAN
PartitionCheckCrcAltSize (
  IN UINTN                 MaxSize,
  IN UINTN                 Size,
  IN OUT EFI_TABLE_HEADER  *Hdr
  )
{
  UINT32      Crc;
  UINT32      OrgCrc;
  EFI_STATUS  Status;

  Crc = 0;

  if (Size == 0) {
    //
    // If header size is 0 CRC will pass so return FALSE here
    //
    return FALSE;
  }

  if ((MaxSize != 0) && (Size > MaxSize)) {
    DEBUG ((DEBUG_ERROR, "CheckCrc32: Size > MaxSize\n"));
    return FALSE;
  }
  //
  // clear old crc from header
  //
  OrgCrc      = Hdr->CRC32;
  Hdr->CRC32  = 0;

  Status      = PartitionCalculateCrc32 ((UINT8 *) Hdr, Size, &Crc);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "CheckCrc32: Crc calculation failed\n"));
    return FALSE;
  }
  //
  // set results
  //
  Hdr->CRC32 = Crc;

  //
  // return status
  //
  DEBUG_CODE_BEGIN ();
    if (OrgCrc != Crc) {
      DEBUG ((DEBUG_ERROR, "CheckCrc32: Crc check failed\n"));
    }
  DEBUG_CODE_END ();

  return (BOOLEAN) (OrgCrc == Crc);
}


/**
  Checks the CRC32 value in the table header.

  @param  MaxSize   Max Size limit
  @param  Hdr       Table to check

  @return TRUE      CRC Valid
  @return FALSE     CRC Invalid

**/
BOOLEAN
PartitionCheckCrc (
  IN UINTN                 MaxSize,
  IN OUT EFI_TABLE_HEADER  *Hdr
  )
{
  return PartitionCheckCrcAltSize (MaxSize, Hdr->HeaderSize, Hdr);
}

/**
  Check if the CRC field in the Partition table header is valid
  for Partition entry array.

  @param[in]  BlockIo     Parent BlockIo interface
  @param[in]  DiskIo      Disk Io Protocol.
  @param[in]  PartHeader  Partition table header structure

  @retval TRUE      the CRC is valid
  @retval FALSE     the CRC is invalid

**/
BOOLEAN
PartitionCheckGptEntryArrayCRC (
  IN  PEI_FAT_PRIVATE_DATA *PrivateData,
  IN  UINTN                            ParentBlockDevNo,
  IN  EFI_PARTITION_TABLE_HEADER  *PartHeader
  )
{
  EFI_STATUS  Status;
  UINT8       *Ptr;
  UINT32      Crc;
  UINTN       Size;
  UINTN       Pages;
  UINT64      Memory;

  Pages = PartHeader->NumberOfPartitionEntries * PartHeader->SizeOfPartitionEntry/EFI_PAGE_SIZE;
  Pages = (Pages > 0 ? Pages : 1);

  //
  // Read the EFI Partition Entries
  //
  PeiServicesAllocatePages (EfiBootServicesData, Pages, &Memory);
  Ptr = (UINT8 *)((UINTN)Memory);

  if (Ptr == NULL) {
    DEBUG ((DEBUG_ERROR, " Allocate pool error\n"));
    return FALSE;
  }

  Status = FatReadBlock (
             PrivateData,
             ParentBlockDevNo,
             PartHeader->PartitionEntryLBA,
             PartHeader->NumberOfPartitionEntries * PartHeader->SizeOfPartitionEntry,
             Ptr
             );

  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  Size   = PartHeader->NumberOfPartitionEntries * PartHeader->SizeOfPartitionEntry;

  Status = PartitionCalculateCrc32 (Ptr, Size, &Crc);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "CheckPEntryArrayCRC: Crc calculation failed\n"));
    return FALSE;
  }

  return (BOOLEAN) (PartHeader->PartitionEntryArrayCRC32 == Crc);
}

/**
  Install child handles if the Handle supports GPT partition structure.

  @param[in]  BlockIo     Parent BlockIo interface.
  @param[in]  DiskIo      Disk Io protocol.
  @param[in]  Lba         The starting Lba of the Partition Table
  @param[out] PartHeader  Stores the partition table that is read

  @retval TRUE      The partition table is valid
  @retval FALSE     The partition table is not valid

**/
BOOLEAN
PartitionValidGptTable (
  IN  PEI_FAT_PRIVATE_DATA        *PrivateData,
  IN  UINTN                       ParentBlockDevNo,
  IN  EFI_LBA                     Lba,
  OUT EFI_PARTITION_TABLE_HEADER  *PartHeader
  )
{
  EFI_STATUS                  Status;
  UINT32                      BlockSize;
  EFI_PARTITION_TABLE_HEADER  *PartHdr;
  PEI_FAT_BLOCK_DEVICE  *ParentBlockDev;

  PartHdr        = (EFI_PARTITION_TABLE_HEADER *) PrivateData->BlockData;
  ParentBlockDev = &(PrivateData->BlockDevice[ParentBlockDevNo]);
  BlockSize      = ParentBlockDev->BlockSize;

  //
  // Read the EFI Partition Table Header
  //
  Status = FatReadBlock (
             PrivateData,
             ParentBlockDevNo,
             Lba,
             ParentBlockDev->BlockSize,
             PartHdr
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "FatReadBlock error\n"));
    return FALSE;
  }

  if ((PartHdr->Header.Signature != EFI_PTAB_HEADER_ID) ||
      !PartitionCheckCrc (BlockSize, &PartHdr->Header) ||
      PartHdr->MyLBA != Lba
      ) {
    DEBUG ((DEBUG_INFO, "Invalid efi partition table header\n"));
    return FALSE;
  }
  CopyMem (PartHeader, PartHdr, sizeof (EFI_PARTITION_TABLE_HEADER));
  if (!PartitionCheckGptEntryArrayCRC (PrivateData, ParentBlockDevNo, PartHeader)) {
    return FALSE;
  }
  DEBUG ((DEBUG_INFO, " Valid efi partition table header\n"));
  return TRUE;
}

/**
  Restore Partition Table to its alternate place.
  (Primary -> Backup or Backup -> Primary)

  @param[in]    PartHeader    Partition table header structure
  @param[in]    PartEntry     The partition entry array
  @param[out]   PEntryStatus  the partition entry status array
                              recording the status of each partition

**/
VOID
PartitionCheckGptEntry (
  IN  EFI_PARTITION_TABLE_HEADER  *PartHeader,
  IN  EFI_PARTITION_ENTRY         *PartEntry,
  OUT EFI_PARTITION_ENTRY_STATUS  *PEntryStatus
  )
{
  EFI_LBA StartingLBA;
  EFI_LBA EndingLBA;
  UINTN   Index1;
  UINTN   Index2;
  UINT64  Attributes;

  DEBUG ((DEBUG_INFO, " start check partition entries\n"));

  for (Index1 = 0; Index1 < PartHeader->NumberOfPartitionEntries; Index1++) {
    if (CompareGuid (&PartEntry[Index1].PartitionTypeGUID, &gEfiPartTypeUnusedGuid)) {
      continue;
    }

    PEntryStatus[Index1].OutOfRange  = FALSE;
    PEntryStatus[Index1].Overlap  = FALSE;
    PEntryStatus[Index1].OsSpecific= FALSE;

    StartingLBA = PartEntry[Index1].StartingLBA;
    EndingLBA   = PartEntry[Index1].EndingLBA;

    if (StartingLBA > EndingLBA ||
        StartingLBA < PartHeader->FirstUsableLBA ||
        StartingLBA > PartHeader->LastUsableLBA ||
        EndingLBA < PartHeader->FirstUsableLBA ||
        EndingLBA > PartHeader->LastUsableLBA
        ) {
      PEntryStatus[Index1].OutOfRange = TRUE;
      continue;
    }

    for (Index2 = Index1 + 1; Index2 < PartHeader->NumberOfPartitionEntries; Index2++) {
      if (CompareGuid (&PartEntry[Index2].PartitionTypeGUID, &gEfiPartTypeUnusedGuid)) {
        continue;
      }

      if (PartEntry[Index2].EndingLBA >= StartingLBA && PartEntry[Index2].StartingLBA <= EndingLBA) {
        //
        // This region overlaps with the Index1'th region
        //
        PEntryStatus[Index1].Overlap  = TRUE;
        PEntryStatus[Index2].Overlap  = TRUE;
        continue;
      }
    }

    Attributes = PartEntry[Index1].Attributes;
    if ((Attributes & BIT1) != 0) {
      //
      // If Bit 1 is set, this indicate that this is an OS specific GUID partition.
      //
      PEntryStatus[Index1].OsSpecific = TRUE;
    }
  }

  DEBUG ((DEBUG_INFO, " End check partition entries\n"));
}

/**
  This internal function reverses bits for 32bit data.

  @param  Value                 The data to be reversed.

  @return                       Data reversed.

**/
UINT32
ReverseBits (
  UINT32  Value
  )
{
  UINTN   Index;
  UINT32  NewValue;

  NewValue = 0;
  for (Index = 0; Index < 32; Index++) {
    if ((Value & (1 << Index)) != 0) {
      NewValue = NewValue | (1 << (31 - Index));
    }
  }

  return NewValue;
}

/**
  Initialize CRC32 table.

**/
VOID
InitializeCrc32Table (
  VOID
  )
{
  UINTN   TableEntry;
  UINTN   Index;
  UINT32  Value;

  for (TableEntry = 0; TableEntry < 256; TableEntry++) {
    Value = ReverseBits ((UINT32) TableEntry);
    for (Index = 0; Index < 8; Index++) {
      if ((Value & 0x80000000) != 0) {
        Value = (Value << 1) ^ 0x04c11db7;
      } else {
        Value = Value << 1;
      }
    }

    mCrcTablePtr[TableEntry] = ReverseBits (Value);
  }
}

/**
  This function finds Mbr partitions. Main algorithm
  is ported from DXE partition driver.

  @param  PrivateData       The global memory map
  @param  ParentBlockDevNo  The parent block device

  @retval TRUE              New partitions are detected and logical block devices
                            are  added to block device array
  @retval FALSE             No New partitions are added;

**/
BOOLEAN
FatFindGptPartitions (
  IN  PEI_FAT_PRIVATE_DATA *PrivateData,
  IN  UINTN                ParentBlockDevNo
  )
{
  EFI_STATUS                       Status;
  UINTN                            Index;
  BOOLEAN                          Found;
  PEI_FAT_BLOCK_DEVICE             *ParentBlockDev;
  PEI_FAT_BLOCK_DEVICE             *BlockDev;
  MASTER_BOOT_RECORD               *ProtectiveMbr;
  EFI_PARTITION_TABLE_HEADER       *PrimaryHeader;
  EFI_PARTITION_ENTRY              *PartEntry;
  EFI_PARTITION_ENTRY_STATUS       *PEntryStatus;
  UINTN                            Pages;
  UINT64                           Memory;


  if (ParentBlockDevNo > PEI_FAT_MAX_BLOCK_DEVICE - 1) {
    return FALSE;
  }

  ParentBlockDev = &(PrivateData->BlockDevice[ParentBlockDevNo]);

  Found          = FALSE;
  ProtectiveMbr  = (MASTER_BOOT_RECORD *) PrivateData->BlockData;

  //
  // Read the Protective MBR from LBA #0
  //
  Status = FatReadBlock (
             PrivateData,
             ParentBlockDevNo,
             0,
             ParentBlockDev->BlockSize,
             ProtectiveMbr
             );

  if (EFI_ERROR (Status)) {
    goto Done;
  }

  //
  // Verify that the Protective MBR is valid
  //
  for (Index = 0; Index < MAX_MBR_PARTITIONS; Index++) {
    if (ProtectiveMbr->Partition[Index].BootIndicator == 0x00 &&
        ProtectiveMbr->Partition[Index].OSIndicator == PMBR_GPT_PARTITION &&
        UNPACK_UINT32 (ProtectiveMbr->Partition[Index].StartingLBA) == 1
        ) {
      DEBUG ((DEBUG_ERROR, "Protective MBR is valid\n"));
      break;
    }
  }
  if (Index == MAX_MBR_PARTITIONS) {
    goto Done;
  }

  PeiServicesAllocatePages (EfiBootServicesData, 1, &Memory);
  PrimaryHeader = (EFI_PARTITION_TABLE_HEADER  *)((UINTN)Memory);
  mCrcTablePtr = (UINT32 *)(((UINTN) Memory) + sizeof (EFI_PARTITION_TABLE_HEADER));

  InitializeCrc32Table ();
  //
  // Check primary and partition tables
  //
  if (PartitionValidGptTable (PrivateData, ParentBlockDevNo, PRIMARY_PART_HEADER_LBA, PrimaryHeader)) {
    //
    // Read the EFI Partition Entries
    //
    Pages = (PrimaryHeader->NumberOfPartitionEntries * sizeof (EFI_PARTITION_ENTRY))/EFI_PAGE_SIZE;
    Pages = (Pages > 0? Pages : 1);

    DEBUG ((EFI_D_ERROR, "NumberOfPartitionEntries = %x  Pages=%x\n", PrimaryHeader->NumberOfPartitionEntries,Pages));
    PeiServicesAllocatePages (EfiBootServicesData, Pages, &Memory);
    PartEntry = (EFI_PARTITION_ENTRY *)((UINTN)Memory);

    if (PartEntry == NULL) {
      DEBUG ((DEBUG_ERROR, "Allocate pool error\n"));
      goto Done;
    }

    Status = FatReadBlock (
               PrivateData,
               ParentBlockDevNo,
               PrimaryHeader->PartitionEntryLBA,
               PrimaryHeader->NumberOfPartitionEntries * (PrimaryHeader->SizeOfPartitionEntry),
               PartEntry
               );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, " Partition Entry ReadDisk error\n"));
      goto Done;
    }

    DEBUG ((DEBUG_INFO, " Partition entries read block success\n"));

    Pages = (PrimaryHeader->NumberOfPartitionEntries * sizeof (EFI_PARTITION_ENTRY_STATUS))/EFI_PAGE_SIZE;
    Pages = (Pages > 0? Pages : 1);
    DEBUG ((DEBUG_ERROR, "NumberOfPartitionEntries = %x  Pages=%x\n", PrimaryHeader->NumberOfPartitionEntries,Pages));
    PeiServicesAllocatePages (EfiBootServicesData, Pages, &Memory);
    PEntryStatus = (EFI_PARTITION_ENTRY_STATUS  *)((UINTN)Memory);

    if (PEntryStatus == NULL) {
      DEBUG ((DEBUG_ERROR, "Allocate pool error\n"));
      goto Done;
    }

    //
    // Check the integrity of partition entries
    //
    PartitionCheckGptEntry (PrimaryHeader, PartEntry, PEntryStatus);

    //
    // Create child device handles
    //
    for (Index = 0; Index < PrimaryHeader->NumberOfPartitionEntries; Index++) {
      if (CompareGuid (&PartEntry[Index].PartitionTypeGUID, &gEfiPartTypeUnusedGuid) ||
          PEntryStatus[Index].OutOfRange ||
          PEntryStatus[Index].Overlap ||
          PEntryStatus[Index].OsSpecific
          ) {
        //
        // Don't use null EFI Partition Entries, Invalid Partition Entries or OS specific
        // partition Entries
        //
        continue;
      }

      //
      // Register this partition
      //
      if (PrivateData->BlockDeviceCount < PEI_FAT_MAX_BLOCK_DEVICE) {
        Found                       = TRUE;
        BlockDev                    = &(PrivateData->BlockDevice[PrivateData->BlockDeviceCount]);
        BlockDev->BlockSize         = ParentBlockDev->BlockSize;
        BlockDev->LastBlock         = PartEntry[Index].EndingLBA;
        BlockDev->IoAlign           = ParentBlockDev->IoAlign;
        BlockDev->Logical           = TRUE;
        BlockDev->PartitionChecked  = FALSE;
        BlockDev->StartingPos = MultU64x32 (
                                  PartEntry[Index].StartingLBA,
                                  ParentBlockDev->BlockSize
                                  );
        BlockDev->ParentDevNo = ParentBlockDevNo;
        PrivateData->BlockDeviceCount++;
      }
    }
  }
Done:

  ParentBlockDev->PartitionChecked = TRUE;
  return Found;
}
//
// RPPO-CNL-0087: RoyalParkOverrideEnd
//

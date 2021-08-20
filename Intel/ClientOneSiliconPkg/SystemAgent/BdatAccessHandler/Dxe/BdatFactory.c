/** @file
  Copies the memory related timing and configuration information into the
  Compatible BIOS data (BDAT) table.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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
#include "BdatAccessHandler.h"

#if FixedPcdGetBool(PcdBdatEnable) == 1
#include <Bdat4.h>
#define CRC_SEED                  (0)
#define CRC_XOR_MASK              (0x1021)

#ifndef BIT15
#define BIT15                     (1 << 15)
#endif

#ifndef MIN
#define MIN(a, b)                 (((a) < (b)) ? (a) : (b))
#endif
#define NCDECS_CR_SCRATCHPAD_NCU_2_REG (0x00005430)

extern EFI_GUID gSchemaListGuid;

///
/// Bdat Access Handler instance data structure
///
STATIC EFI_BDAT_ACPI_DESCRIPTION_TABLE  mRmtAcpiTable = {
  {
    EFI_BDAT_TABLE_SIGNATURE,                 ///< Signature
    sizeof (EFI_BDAT_ACPI_DESCRIPTION_TABLE), ///< Length
    0x01,                                     ///< Revision [01]
    0,                                        ///< Checksum
    {
      ' ',                                    ///< OEM ID
      ' ',                                    ///< .
      ' ',                                    ///< .
      ' ',                                    ///< .
      ' ',                                    ///< .
      ' '                                     ///< .
    },
    0,                                        ///< OEM Table ID
    0,                                        ///< OEM Revision [0x00000000]
    0,                                        ///< Creator ID
    0                                         ///< Creator Revision
  },
  {
    0,                                        ///< System Memory Address Space ID
    0,
    0,
    0,
    EFI_BDAT_ACPI_POINTER
  }
};

/**
  Calculate the CRC16 of the provided data. CRC16 formula is the same
  one that is used for calculating the CRC16 stored in the memory SPD.

  @param[in]  Buffer - Pointer to the start of the data.
  @param[in]  Size   - Amount of data in the buffer, in bytes.

  @retval The calculated CRC16 value.
**/
static
UINT16
GetCrc16 (
  IN  CONST UINT8  *CONST Buffer,
  IN  CONST UINT32        Size
  )
{
  CONST UINT8  *Data;
  UINT32       Value;
  UINT32       Byte;
  UINT8        Bit;

  Data  = Buffer;
  Value = CRC_SEED;
  for (Byte = 0; Byte < Size; Byte++) {
    Value ^= (UINT32) *Data++ << 8;
    for (Bit = 0; Bit < 8; Bit++) {
      Value = (Value & BIT15) ? (Value << 1) ^ CRC_XOR_MASK : Value << 1;
    }
  }

  return ((UINT16) Value);
}

/**
@brief
  Generate the header data for the BDAT structure

  @param[in]  SchemaCount : The number of schemas in the BDAT structure
  @param[out] Bdat        : A pointer to a pre-allocated memory area for the BDAT
                            structure. BDAT header data will be written to this address

  @retval EFI_SUCCESS:              BDAT header generated successfully
  @retval EFI_OUT_OF_RESOURCES:     Could not allocate needed resources
**/
EFI_STATUS
CreateBdatHeader (
  IN  UINT16         SchemaCount,
  OUT BDAT_STRUCTURE *Bdat
  )
{
  CONST UINT8                BdatHeaderSign[] = {'B', 'D', 'A', 'T', 'H', 'E', 'A', 'D'};
  EFI_STATUS                 Status;
  BDAT_HEADER_STRUCTURE      *BdatHeader;
  BDAT_SCHEMA_LIST_STRUCTURE *BdatSchemas;
  EFI_TIME                   CurrentTime;

  //
  // Initialize the header area of the BDAT structure.
  //
  BdatHeader = &Bdat->Header;
  CopyMem (&BdatHeader->BiosDataSignature[0], (UINT8 *) BdatHeaderSign, sizeof (BdatHeader->BiosDataSignature));
  BdatHeader->BiosDataStructSize    = sizeof (BDAT_STRUCTURE) + (SchemaCount * sizeof (UINT32));
  BdatHeader->Version.Rev.Primary   = BDAT_PRIMARY_VERSION;
  BdatHeader->Version.Rev.Secondary = BDAT_SECONDARY_VERSION;
  BdatHeader->OemOffset             = OEM_OFFSET;

  //
  // Initialize the schema list of the BDAT structure.
  //
  Status = gRT->GetTime (&CurrentTime, NULL);
  if (!EFI_ERROR (Status)) {
    BdatSchemas                   = &Bdat->Schemas;
    BdatSchemas->SchemaListLength = SchemaCount;
    BdatSchemas->Time.Hour        = CurrentTime.Hour;
    BdatSchemas->Time.Minute      = CurrentTime.Minute;
    BdatSchemas->Time.Second      = CurrentTime.Second;
    BdatSchemas->Time.Year        = CurrentTime.Year;
    BdatSchemas->Time.Month       = CurrentTime.Month;
    BdatSchemas->Time.Day         = CurrentTime.Day;
  } else {
    Status = EFI_UNSUPPORTED;
  }

  return Status;
}
#endif

/**
  Entry point of the Bdat table factory.

  @param[in] SaPolicy      : A pointer to Dxe policy
  @param[in] HobList       : A pointer to the HOB list
  @param[in] AcpiTable     : A pointer to ACPI table

  @retval EFI_SUCCESS:              Driver initialized successfully
  @exception EFI_UNSUPPORTED:       A needed driver was not located
  @retval EFI_OUT_OF_RESOURCES:     Could not allocate needed resources
**/
EFI_STATUS
CreateBdatTable (
  IN SA_POLICY_PROTOCOL              *SaPolicy,
  IN VOID                            *HobList,
  IN EFI_ACPI_TABLE_PROTOCOL         *AcpiTable
  )
{
#if FixedPcdGetBool(PcdBdatEnable) == 1
  VOID                 *Buffer;
  BDAT_STRUCTURE       *Bdat;
  BDAT_SCHEMA_LIST_HOB *BdatSchemaListHob;
  UINT32               *ScratchPad;
  UINT32               MchBar;
  EFI_GUID             *Guid;
  EFI_HOB_GUID_TYPE    *Schema[MAX_SCHEMA_LIST_LENGTH];
  UINT32               *SchemaOffsetList;
  UINT8                *NextBlock;
  UINT8                *SchemaData;
  EFI_STATUS           Status;
  UINT64               TempBuffer;
  UINTN                AcpiTableKey;
  UINT32               DataSize;
  UINT32               BufferSize;
  UINT32               BdatHeaderSize;
  UINT16               SchemaListIndex;
  UINT8                NextSchema;
  UINT8                SchemaCount;
  UINT8                Check;
  UINT8                Index;

  Status = EFI_SUCCESS;
  while (Status == EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "Creating BDAT Table...\n"));

    ///
    /// Get the memory information HOB so we can locate the BDAT information.
    ///
    BdatSchemaListHob = GetNextGuidHob (&gSchemaListGuid, HobList);
    if (BdatSchemaListHob == NULL) {
      DEBUG ((DEBUG_INFO, "No BDAT data exists, exiting without creating table\n"));
      Status = EFI_UNSUPPORTED;
      break;
    }
    DEBUG ((DEBUG_INFO, "Found Schema List HOB\n"));

    ///
    /// Gather up all the BDAT specific HOBs.
    /// We need to get pointers to them and determine the buffer size needed to store them into the ACPI table.
    ///
    BufferSize  = 0;
    SchemaCount = 0;
    for (SchemaListIndex = 0; SchemaListIndex < BdatSchemaListHob->SchemaHobCount; SchemaListIndex++) {
      Guid = (EFI_GUID *) &(BdatSchemaListHob->SchemaHobGuids[SchemaListIndex]);

      Schema[SchemaListIndex] = NULL;
      if (Guid != NULL) {
        DEBUG ((DEBUG_INFO, "Checking GUID: "));
        for (Index = 0, Check = 0; Index < sizeof (EFI_GUID); Index++) {
          Check |= ((UINT8 *) Guid) [Index];
        }
        DEBUG ((DEBUG_INFO, "%d\n", (UINT32) Check));
        DEBUG ((DEBUG_INFO, "GUID = %g\n", Guid));
        if (Check != 0) {
          Schema[SchemaListIndex] = GetNextGuidHob (Guid, HobList);
          DEBUG ((DEBUG_INFO, "Schema HOB pointer: %x\n", (UINT32) (UINTN) Schema[SchemaListIndex]));
          if (Schema[SchemaListIndex] != NULL) {
            BufferSize += Schema[SchemaListIndex]->Header.HobLength - sizeof (EFI_HOB_GUID_TYPE);
            DEBUG ((DEBUG_INFO, "HOB Length = %d\n", Schema[SchemaListIndex]->Header.HobLength));
            SchemaCount++;
          }
        } else {
          DEBUG ((DEBUG_INFO, "BDAT Schema List HOB is corrupted, aborting\n"));
          Status = EFI_UNSUPPORTED;
          break;
        }
      }
    }
    DEBUG ((DEBUG_INFO, "BdatSchemaListHob->SchemaHobCount = %d, SchemaCount = %d\n", (UINT32) BdatSchemaListHob->SchemaHobCount, (UINT32) SchemaCount));

    ///
    /// Return if we did not find any schemas
    ///
    if (SchemaCount == 0) {
      DEBUG ((DEBUG_INFO, "No BDAT data exists, exiting without creating table\n"));
      Status = EFI_UNSUPPORTED;
      break;
    }

    ///
    /// Allocate and clear memory, in 4kb pages. This memory is used to store the BDAT into the ACPI table.
    ///
    Buffer         = NULL;
    BdatHeaderSize = sizeof (BDAT_HEADER_STRUCTURE) + sizeof (BDAT_SCHEMA_LIST_STRUCTURE) + (SchemaCount * sizeof (UINT32));
    BufferSize    += BdatHeaderSize;
    DEBUG ((DEBUG_INFO, "BufferSize = %d\n", BufferSize));
    Buffer = AllocateReservedPages (EFI_SIZE_TO_PAGES (BufferSize));
    if (Buffer == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      break;
    }
    ZeroMem (Buffer, BufferSize);
    DEBUG ((DEBUG_INFO, "Buffer = 0x%X\n", (UINT32) (UINTN) Buffer));
    ///
    /// Copy the BDAT structure into the memory specified for the ACPI table.
    ///
    Bdat       = (BDAT_STRUCTURE *) Buffer;
    NextBlock  = (UINT8 *) ((UINTN) Buffer + BdatHeaderSize);
    DEBUG ((DEBUG_INFO, "NextBlock = 0x%X\n", NextBlock));
    NextSchema = 0;
    SchemaOffsetList = (UINT32*) (((UINTN) Buffer) + sizeof (BDAT_STRUCTURE));
    Status = CreateBdatHeader (SchemaCount, Bdat);
    ASSERT_EFI_ERROR (Status);
    for (SchemaListIndex = 0; SchemaListIndex < SchemaCount; SchemaListIndex++) {
      if (Schema[SchemaListIndex] != NULL) {
        DataSize = Schema[SchemaListIndex]->Header.HobLength - sizeof (EFI_HOB_GUID_TYPE);
        DEBUG ((DEBUG_INFO, "DataSize = %d\n", DataSize));
        SchemaData = (UINT8*) Schema[SchemaListIndex];
        SchemaData += sizeof (EFI_HOB_GUID_TYPE);
        DEBUG ((DEBUG_INFO, "SchemaData = 0x%X\n", (UINT32) ((UINTN) SchemaData)));
        CopyMem (NextBlock, SchemaData, DataSize);
        SchemaOffsetList[NextSchema++] = (UINT32) ((UINTN) NextBlock  - (UINTN) Bdat);
        NextBlock = (UINT8 *) ((UINTN) NextBlock + DataSize);
        DEBUG ((DEBUG_INFO, "NextBlock = 0x%X\n", NextBlock));
      }
    }
    ///
    /// Initialize the Size and CRC of the BDAT structure.
    /// Ensure that the CRC calculation is the last field initialized.
    ///
    Bdat->Header.BiosDataStructSize = BufferSize;
    Bdat->Header.Crc16 = GetCrc16 ((CONST UINT8 * CONST) Bdat, BdatHeaderSize);

    ///
    /// RMT ACPI table
    ///
    DEBUG ((DEBUG_INFO, "In RMT ACPI table\n"));
    TempBuffer = SIGNATURE_64 ('I', 'N', 'T', 'E', 'L', 0, 0, 0);
    CopyMem (&mRmtAcpiTable.Header.OemId, &TempBuffer, sizeof (mRmtAcpiTable.Header.OemId));
    mRmtAcpiTable.Header.OemTableId       = SIGNATURE_64 ('B', 'D', 'W', '-', 'W', 'P', 'T', 0);
    mRmtAcpiTable.Header.CreatorId        = CREATOR_ID_INTEL;
    mRmtAcpiTable.Header.CreatorRevision  = CREATOR_REV_INTEL;
    mRmtAcpiTable.Header.OemRevision      = ACPI_BDAT_OEM_REV;
    ///
    /// Copy pointer to RMT ACPI BDAT structure and protocol.
    ///
    mRmtAcpiTable.BdatGas.Address = (EFI_PHYSICAL_ADDRESS) Buffer;
    ///
    /// Install RMT BDAT into RMT ACPI table
    ///
    AcpiTableKey = 0;
    Status = AcpiTable->InstallAcpiTable (
                          AcpiTable,
                          &mRmtAcpiTable,
                          sizeof (EFI_BDAT_ACPI_DESCRIPTION_TABLE),
                          &AcpiTableKey
                          );
    ASSERT_EFI_ERROR (Status);

    ///
    /// Write scratchpad register into the MCHBAR space with address of the ACPI BDAT structure.
    ///
    MchBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, 0, 0, 0, MCHBAR_OFFSET)) & ~BIT0;
    ScratchPad  = (UINT32 *) (UINTN) (MchBar + NCDECS_CR_SCRATCHPAD_NCU_2_REG);
    *ScratchPad = (UINT32) ((UINTN) Buffer);
    break;
  }
  return Status;
#else
  return EFI_UNSUPPORTED;
#endif
}

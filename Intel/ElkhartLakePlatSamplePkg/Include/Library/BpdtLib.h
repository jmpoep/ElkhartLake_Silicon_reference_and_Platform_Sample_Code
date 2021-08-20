/** @file
    This is the header file for the Boot Partition Descriptor Table Library.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2019 Intel Corporation.

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

#ifndef __BPDT_LIB_H__
#define __BPDT_LIB_H__

//Please do not put #includes here, they should be with the implementation code

#define BPDT_SIGN_GREEN       0x000055AA    //Normal Boot
#define BPDT_SIGN_YELLOW      0x00AA55AA    //Recovery Boot
#define BPDT_SIGN_RED         0xFFFFFFFF    //any value, ie !(GREEN || YELLOW)
#define BPDT_TABLE_SIZE       0x1000

#define DIRECTORY_HEADER_MARKER     SIGNATURE_32('$', 'C', 'P', 'D')
#define DIRECTORY_ENTRY_NAME_SIZE   12

typedef struct {
  UINT8   RomBypassVector[16];
  UINT16  Size;
  UINT8   Reserved[2];
  UINT32  Checksum;
  UINT32  DataPartitionOffset;
  UINT32  DataPartitionSize;
  UINT32  Lbp1Offset;
  UINT32  Lbp1Size;
  UINT32  Lbp2Offset;
  UINT32  Lbp2Size;
  UINT32  Lbp3Offset;
  UINT32  Lbp3Size;
  UINT32  Lbp4Offset;
  UINT32  Lbp4Size;
  UINT32  Lbp5Offset;
  UINT32  Lbp5Size;
  UINT32  Lbp6Offset;
  UINT32  Lbp6Size;
  UINT32  TempPagesAddress;
  UINT32  TempPagesSize;
} CSE_LAYOUT_POINTERS;

typedef struct {
  UINT32  Signature;
  UINT16  DescriptorCount;
  UINT8   Version;
  UINT8   BpdtConfiguration;
  UINT32  Checksum;
  UINT32  IfwiVersion;
  UINT64  FitToolVersion;
} BPDT_HEADER;

typedef struct {
  UINT16  Type;
  UINT16  Flags;
  UINT32  SubPartitionOffset;
  UINT32  SubPartitionSize;
} BPDT_ENTRY;

typedef struct {
  VOID    *Address;
  UINT32  Size;
} SUB_PARTITION_DATA;

typedef enum {
  BpdtOemSmip = 0,        // 0
  BpdtCseRbe,             // 1
  BpdtCseBup,             // 2
  BpdtUcode,              // 3
  BpdtIbb,                // 4
  BpdtSbpdt,              // 5
  BpdtObb,                // 6
  BpdtCseMain,            // 7
  BpdtIsh,                // 8
  BpdtCseIdlm,            // 9
  BpdtUep,                //10
  BpdtDebugTokens,        //11
  BpdtUfsPhyConfig,       //12
  BpdtUfsGppLunId,        //13
  BpdtPmc,                //14
  BpdtIunit,              //15
  BpdtNvmConfig,          //16
  BpdtReserved,           //17
  BpdtWlanUcode,          //18
  BpdtLoclSprites,        //19
  BpdtCseOemKeyManifest,  //20
  BpdtCseDefaults,        //21
  BpdtPavp,               //22
  BpdtIomFw,              //23
  BpdtPhyFw,              //24
  BpdtTbt,                //25
  BpdtReserved2,          //26
  BpdtAcm,                //27
  BpdtBtgPolicyManifest,  //28
  BpdtBtgKeyManifest,     //29
  BpdtFitTable,           //30
  BpdtMaxType
} BPDT_ENTRY_TYPE;

typedef struct {
  UINT32  HeaderMarker;
  UINT32  NumberOfEntries;
  UINT8   HeaderVersion;
  UINT8   EntryVersion;
  UINT8   HeaderLength;
  UINT8   Reserved;
  UINT32  SubPartitionName;
  UINT32  Checksum;
} SUB_PARTITION_DIRECTORY_HEADER;

typedef struct {
  CHAR8   EntryName[12];
  UINT32  Offset:25;
  UINT32  Huffman:1;
  UINT32  Reserved1:6;
  UINT32  Length;
  UINT32  Reserved2;
} SUB_PARTITION_DIRECTORY_ENTRY;

typedef struct {
  UINT32  HeaderMarker;
  UINT32  NumberOfEntries;
  UINT8   HeaderVersion;
  UINT8   EntryVersion;
  UINT8   HeaderLength;
  UINT8   FptRedundancyReserved;
  UINT16  TicksToAdd;
  UINT16  TokensToAdd;
  UINT32  Checksum;
  UINT32  Reserved;
  UINT64  FlashToolVersion;
} FLASH_PARTITION_TABLE_HEADER;

typedef struct {
  CHAR8   PartitionName[4];
  UINT32  Reserved1;
  UINT32  Offset;
  UINT32  Length;
  UINT8   Reserved2[12];
  UINT32  PartitionFlags;
} FLASH_PARTITION_TABLE_ENTRY;

typedef enum {
  Bpdt1 = 0,        // 0
  Bpdt2,            // 1
  BpdtMax
} BPDT_TABLE_NUM;

/**
  Print FV name based on GUID
**/
VOID
PrintFvName (
  EFI_GUID  *FvName
);

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
  );

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
  );

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
  );

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
  );

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
  );

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
  );

/**
   Read the UFS Descriptor region.

   @param[out] DescriptorRegionOffset The address of Descriptor region in IFWI.
   @param[out] DescriptorRegionSize   The size of Descriptor region in bytes.

   @retval EFI_SUCCESS           The operation returns successfully.
   @retval others                If get descriptor region fails.
 **/
EFI_STATUS
EFIAPI
GetUfsDescriptorRegion(
  OUT UINT32 *DescriptorRegionOffset,
  OUT UINT32 *DescriptorRegionSize
  );

#endif


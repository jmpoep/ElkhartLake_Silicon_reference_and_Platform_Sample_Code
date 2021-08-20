//
// This file contains 'Framework Code' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor. This file may not be modified, except as allowed by
// additional terms of your license agreement.
//
/**@file
This utility is part of build process for IA32/X64 FD.
It parses FIT table and generates signature and hash for TXT BPM.

Copyright (c) 2010 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "BpmGen.h"

#pragma pack (1)

//
// BPM Policy:
//   FIT record type 12 points to Boot Policy Manifest.
//   FIT record type 11 points to Key Manifest.
//

//
// Manifest definition
//
#define TPM_ALG_SHA1        0x4
#define TPM_ALG_SHA256      0xB
#define SHA1_DIGEST_SIZE    20
#define SHA256_DIGEST_SIZE  32

typedef struct {
  UINT16   HashAlg;
  UINT16   Size;
  UINT8    HashBuffer[SHA256_DIGEST_SIZE];
} HASH_STRUCTURE;

#define ALG_RSA             0x1
#define ALG_RSASSA          0x14

#define RSA_PUBLIC_KEY_STRUCT_VERSION  0x10
#define RSA_PUBLIC_KEY_STRUCT_KEY_SIZE_DEFAULT  2048
#define RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT   (RSA_PUBLIC_KEY_STRUCT_KEY_SIZE_DEFAULT/8)
//#define RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_DEFAULT  0x11 // 0x10001
#define RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE  4
typedef struct {
  UINT8    Version;
  UINT16   KeySize;
  UINT32   Exponent;
  UINT8    Modulus[RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT];
} RSA_PUBLIC_KEY_STRUCT;

#define RSASSA_SIGNATURE_STRUCT_VERSION  0x10
#define RSASSA_SIGNATURE_STRUCT_KEY_SIZE_DEFAULT  2048
#define RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT   (RSASSA_SIGNATURE_STRUCT_KEY_SIZE_DEFAULT/8)
typedef struct {
  UINT8    Version;
  UINT16   KeySize;
  UINT16   HashAlg;
  UINT8    Signature[RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT];
} RSASSA_SIGNATURE_STRUCT;

#define KEY_SIGNATURE_STRUCT_VERSION  0x10
typedef struct {
  UINT8                    Version;
  UINT16                   KeyAlg;
  RSA_PUBLIC_KEY_STRUCT    Key;
  UINT16                   SigScheme;
  RSASSA_SIGNATURE_STRUCT  Signature;
} KEY_SIGNATURE_STRUCT;

#define BP_KEY_TYPE_BOOT_POLICY_MANIFEST  0
#define BP_KEY_TYPE_KEY_MANIFEST          1

#define BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_ID  (*(UINT64 *)"__ACBP__")
#define BOOT_POLICY_MANIFEST_STRUCTURE_VERSION              0x10
#define BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_VERSION       0x01
typedef struct {
  UINT8              StructureID[8];
  UINT8              StructVersion;
  UINT8              HdrStructVersion;
  UINT8              PMBPMVersion;
  UINT8              BPSVN;
  UINT8              ACMSVN;
  UINT8              Reserved;
  UINT16             NEMDataStack;
} BOOT_POLICY_MANIFEST_HEADER;

#define IBB_SEGMENT_FLAG_IBB     0x0
#define IBB_SEGMENT_FLAG_NON_IBB 0x1
#define IBB_ALIGNMENT  0x3F  // 64 bytes for AnC
typedef struct {
  UINT8    Reserved[2];
  UINT16   Flags;
  UINT32   Base;
  UINT32   Size;
} IBB_SEGMENT_ELEMENT;

#define BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__IBBS__")
#define BOOT_POLICY_MANIFEST_IBB_ELEMENT_VERSION       0x10
#define IBB_FLAG_ENABLE_VTD            0x1
#define IBB_FLAG_INITIAL_MEASURE_LOC3  0x2
#define IBB_FLAG_AUTHORITY_MEASURE     0x4
#define IBB_ENTRYPOINT_MIN   0xFFFFFFC0
typedef struct {
  UINT8               StructureID[8];
  UINT8               StructVersion;
  UINT8               SetNumber;
  UINT8               Reserved;
  UINT8               PBETValue;
  UINT32              Flags;
  UINT64              IBB_MCHBAR;
  UINT64              VTD_BAR;
  UINT32              PMRL_Base;
  UINT32              PMRL_Limit;
  UINT64              PMRH_Base;
  UINT64              PMRH_Limit;
  HASH_STRUCTURE      PostIbbHash;
  UINT32              EntryPoint;
  HASH_STRUCTURE      Digest;
  UINT8               SegmentCount; // 1 ~ 8
  IBB_SEGMENT_ELEMENT IBBSegment[1];
} IBB_ELEMENT;

#define BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__PMDA__")
#define BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_VERSION       0x10
#define PLATFORM_DATA_ALIGNMENT  0x3  // 4 bytes
typedef struct {
  UINT8    StructureID[8];
  UINT8    StructVersion;
  UINT16   PMDataSize;
//UINT8    PMData[PMDataSize];
} PLATFORM_MANUFACTURER_ELEMENT;

#define BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__PMSG__")
#define BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_VERSION       0x10
typedef struct {
  UINT8                 StructureID[8];
  UINT8                 StructVersion;
  KEY_SIGNATURE_STRUCT  KeySignature;
} BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT;

#define KEY_MANIFEST_STRUCTURE_ID  (*(UINT64 *)"__KEYM__")
#define KEY_MANIFEST_VERSION       0x10
typedef struct {
  UINT8                  StructureID[8];
  UINT8                  StructVersion;
  UINT8                  KeyManifestVersion;
  UINT8                  KMSVN;
  UINT8                  KeyManifestID;
  HASH_STRUCTURE         BPKey;
  KEY_SIGNATURE_STRUCT   KeyManifestSignature;
} KEY_MANIFEST_STRAUCTURE;

#define BIOS_DATA_AREA_STRUCTURE_ID  (*(UINT64 *)"__BDAS__")
#define BIOS_DATA_AREA_VERSION       0x00010000


#define BDAS_DATA_ENTRY_TYPE_RESERVED              0
#define BDAS_DATA_ENTRY_TYPE_TPM_ACTIVATION_STATUS 1
#define BDAS_DATA_ENTRY_DATA_TPM_DEACTIVATED    0x1
typedef struct {
  UINT64   Enumeration:16;
  UINT64   Data:48;
} BDAS_DATA_ENTRY;

typedef struct {
  UINT8                  StructureID[8];
  UINT32                 StructVersion;
  UINT32                 BDAS_DataEntryCount;
  BDAS_DATA_ENTRY        BDAS_DataEntry[1];
} BIOS_DATA_AREA_STRAUCTURE;

#pragma pack ()

//
// Internal data structure
//

#define BP_KEY_MAX_COUNT         1
#define PLATFOMR_DATA_MAX_COUNT  0x20

typedef struct {
  // 1.1 Value to be filed for Bpm
  UINT8                PMBPMVersion;
  UINT8                BootPolicyRevocation;
  UINT8                AcmRecocation;
  UINT16               NEMDataStack;

  UINT8                PBETValue;
  UINT32               Flags;
  UINT64               IBB_MCHBAR;
  UINT64               VTD_BAR;
  UINT32               PMRL_Base;
  UINT32               PMRL_Limit;
  UINT64               PMRH_Base;
  UINT64               PMRH_Limit;
  UINT32               EntryPoint;
  UINT8                SegmentCount;

  UINT32               PlatformDataCount;
  UINT32               PlatformDataTotalSize;
  UINT32               PlatformDataSize[PLATFOMR_DATA_MAX_COUNT];
  VOID                 *PlatformData[PLATFOMR_DATA_MAX_COUNT]; // Buffer allocated

  // 1.2 Bpm Value
  VOID                 *BootPolicyManifest; // Buffer allocated
  UINT32               BootPolicyManifestSize;
  UINT8                BootPolicySign[RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT * 2 + RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE];

  // 1.3 Key Info
  CHAR8                *PrivKeyName;
  CHAR8                *PubKeyName;

  // 1.4 Batch Info
  CHAR8                *ExternalBatchName;
  CHAR8                *DataFileName;
  CHAR8                *SignatureFileName;

  // 2.1 Value to be filed for KeyManifest
  UINT8                KeyManifestVersion;
  UINT8                KeyManifestRevocation;
  UINT8                KeyManifestID;

  UINT32               BPKeyCount;
  CHAR8                *BPKeyFile[BP_KEY_MAX_COUNT];
  CHAR8                *BPKeyFileBin[BP_KEY_MAX_COUNT];

  // 2.2 KeyManifest Value
  VOID                 *KeyManifest; // Buffer allocated
  UINT32               KeyManifestSize;
  UINT8                KeySign[RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT * 2 + RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE];

  // 2.3 Key Info
  CHAR8                *KeyPrivKeyName;
  CHAR8                *KeyPubKeyName;

  // 2.4 Batch Info
  CHAR8                *KeyExternalBatchName;
  CHAR8                *KeyDataFileName;
  CHAR8                *KeySignatureFileName;

  // 3.1 Value to be filed for BiosDataArea
  UINT8                TpmDeactivated;
  UINT32               BDASEntryCount;
  // 3.2 BiosDataArea Value
  VOID                 *BiosDataArea; // Buffer allocated
  UINT32               BiosDataAreaSize;
} MBIOS_CONTEXT;

MBIOS_CONTEXT   gMBiosContext;

#pragma pack (1)
typedef struct {
  UINT64     Address;
  UINT8      Size[3];
  UINT8      Rsvd;
  UINT16     Version;
  UINT8      Type:7;
  UINT8      C_V:1;
  UINT8      Checksum;
} FIRMWARE_INTERFACE_TABLE_ENTRY;

//
// Struct for policy
//
typedef struct {
  UINT16     IndexPort;
  UINT16     DataPort;
  UINT8      Width;
  UINT8      Bit;
  UINT16     Index;
  UINT8      Size[3];
  UINT8      Rsvd;
  UINT16     Version; // == 0
  UINT8      Type:7;
  UINT8      C_V:1;
  UINT8      Checksum;
} FIRMWARE_INTERFACE_TABLE_ENTRY_PORT;

#pragma pack ()

//
// BIOS INFO data structure
// This is self contained data structure for BIOS info
//
#pragma pack (1)
#define BIOS_INFO_SIGNATURE  SIGNATURE_64 ('$', 'B', 'I', 'O', 'S', 'I', 'F', '$')
typedef struct {
  UINT64            Signature;
  UINT32            EntryCount;
  UINT32            Reserved;
//BIOS_INFO_STRUCT  Struct[EntryCount];
} BIOS_INFO_HEADER;

//
// BIOS_INFO_STRUCT attributes
// bits[0:3] means general attributes
// bits[4:7] means type specific attributes
//
#define BIOS_INFO_STRUCT_ATTRIBUTE_GENERAL_EXCLUDE_FROM_FIT  0x01
#define BIOS_INFO_STRUCT_ATTRIBUTE_MICROCODE_WHOLE_REGION    0x10
#define BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_POST_IBB             0x10
#define BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_NON_IBB              0x20

typedef struct {
  //
  // FitTable entry type
  //
  UINT8    Type;
  //
  // BIOS_INFO_STRUCT attributes
  //
  UINT8    Attributes;
  //
  // FitTable entry version
  //
  UINT16   Version;
  //
  // FitTable entry real size
  //
  UINT32   Size;
  //
  // FitTable entry address
  //
  UINT64   Address;
} BIOS_INFO_STRUCT;

#pragma pack ()

#define MAX_BIOS_MODULE_ENTRY  0x20
#define MAX_MICROCODE_ENTRY    0x20
#define MAX_OPTIONAL_ENTRY     0x20
#define MAX_PORT_ENTRY         0x20

#define DEFAULT_FIT_TABLE_POINTER_OFFSET  0x40
#define DEFAULT_FIT_ENTRY_VERSION         0x0100

#define MEMORY_TO_FLASH(FileBuffer, FvBuffer, FvSize)  \
                 (UINTN)(0x100000000 - ((UINTN)(FvBuffer) + (UINTN)(FvSize) - (UINTN)(FileBuffer)))
#define FLASH_TO_MEMORY(Address, FvBuffer, FvSize)  \
                 (VOID *)(UINTN)((UINTN)(FvBuffer) + (UINTN)(FvSize) - (0x100000000 - (UINTN)(Address)))

#define FIT_TABLE_TYPE_HEADER         0
#define FIT_TABLE_TYPE_MICROCODE      1
#define FIT_TABLE_TYPE_STARTUP_ACM    2
#define FIT_TABLE_TYPE_BIOS_MODULE    7
#define FIT_TABLE_TYPE_TPM_POLICY     8
#define FIT_TABLE_TYPE_BIOS_POLICY    9
#define FIT_TABLE_TYPE_TXT_POLICY     10
#define FIT_TABLE_TYPE_KEY_MANIFEST           11
#define FIT_TABLE_TYPE_BOOT_POLICY_MANIFEST   12
#define FIT_TABLE_TYPE_BIOS_DATA_AREA         13

typedef struct {
  UINT32  Type;
  UINT32  Address;
  UINT32  Size;
  UINT32  Version; // Used by OptionalModule only
} FIT_TABLE_CONTEXT_ENTRY;

typedef struct {
  UINT32                     FitTablePointerOffset;
  UINT32                     FitEntryNumber;
  UINT32                     BiosModuleNumber;
  UINT32                     NonIbbBiosModuleNumber;
  UINT32                     PostIbbBiosModuleNumber;
  UINT32                     MicrocodeNumber;
  UINT32                     OptionalModuleNumber;
  UINT32                     PortModuleNumber;
  UINT32                     GlobalVersion;
  UINT32                     FitHeaderVersion;
  FIT_TABLE_CONTEXT_ENTRY    StartupAcm;
  UINT32                     StartupAcmVersion;
  FIT_TABLE_CONTEXT_ENTRY    BiosModule[MAX_BIOS_MODULE_ENTRY];
  UINT32                     BiosModuleVersion;
  FIT_TABLE_CONTEXT_ENTRY    NonIbbBiosModule[MAX_BIOS_MODULE_ENTRY];
  FIT_TABLE_CONTEXT_ENTRY    PostIbbBiosModule[MAX_BIOS_MODULE_ENTRY];
  FIT_TABLE_CONTEXT_ENTRY    Microcode[MAX_MICROCODE_ENTRY];
  UINT32                     MicrocodeVersion;
  FIT_TABLE_CONTEXT_ENTRY    OptionalModule[MAX_OPTIONAL_ENTRY];
  FIT_TABLE_CONTEXT_ENTRY    PortModule[MAX_PORT_ENTRY];
} FIT_TABLE_CONTEXT;

FIT_TABLE_CONTEXT   gFitTableContext;

unsigned int
xtoi (
  char  *str
  );

unsigned long long
xtol (
  char  *str
  );

VOID
PrintUtilityInfo (
  VOID
  )
/*++

Routine Description:

  Displays the standard utility information to SDTOUT

Arguments:

  None

Returns:

  None

--*/
{
  printf (
    "%s - Tiano IA32/X64 Bpm table generation Utility."" Version %i.%i\n\n",
    UTILITY_NAME,
    UTILITY_MAJOR_VERSION,
    UTILITY_MINOR_VERSION
    );
}

VOID
PrintUsage (
  VOID
  )
/*++

Routine Description:

  Displays the utility usage syntax to STDOUT

Arguments:

  None

Returns:

  None

--*/
{
  printf ("Usage: %s <BIOS> <MBIOS> [-F <FitTablePointerOffset>]\n"
          "           [-I <BiosInfoGuid>]\n"
          "           [-PV <PmBpmVersion>] [-BSVN <BootPolicyRevocation>] [-ASVN <AcmRecocation>] [-NEM <NEMDataStack>]\n"
          "           [-F <Flags>] [-BAR <MchBar>] [-VTDBAR <VtdBar>] [-PMRL <Base> <Limit>] [-PMRH <Base> <Limit>] [-PBET <PBETValue>] [-EP <Entrypoint>]\n"
          "           [-P <PlatformDataFile>] [-P ...]\n"
          "           -B <ExternalBatchFile> <DataFile> <SignatureFile>|-S <privkey.pem> <pubkey.pem>\n"
          "           [-KV <KeyManifestVersion>] [-KSVN <KeyManifestRevocation>] [-KID <KeyManifestID>] [-K <BPKeyPub.pem>|-KB <BPKeyPub.bin>]\n"
          "           -BK <ExternalBatchFile> <DataFile> <SignatureFile>|-SK <keyprivkey.pem> <keypubkey.pem>\n"
          "           [-T <TpmDeactivated>]\n"
          "           [-O <Manifest>] [-OY <KeyManifest>]\n"
          "", UTILITY_NAME);
  printf ("Usage: %s <BIOS> -INFO\n"
          "", UTILITY_NAME);
  printf ("  Where:\n");
  printf ("\tBIOS                  - Input BIOS with Fit table\n");
  printf ("\tMBIOS                 - Output BIOS with Boot Policy Manifest data included\n");
  printf ("\tFitTablePointerOffset - FIT table pointer offset. 0x%x as default. 0x18 for current soon to be obsoleted CPUs.\n", DEFAULT_FIT_TABLE_POINTER_OFFSET);
  printf ("\tPmBpmVersion          - Platform Manufacturer's version number.\n");
  printf ("\tBootPolicyRevocation  - Boost Policy Manifest Revocation Values.\n");
  printf ("\tAcmRecocation         - Anchor Cove ACM Revocation Values.\n");
  printf ("\tNEMDataStack          - This is the expected size of the LLC.\n");
  printf ("\tFlags                 - Various flags for this IBB.\n");
  printf ("\tMchBar                - Value exactly as to be written to the MCHBAR.\n");
  printf ("\tVtdBar                - Value exactly as to be written to the VTDBAR.\n");
  printf ("\tPMRL/H Base/Limit     - DMA-protected memory region information.\n");
  printf ("\tPBETValue             - Protect BIOS Environment Timer value.\n");
  printf ("\tEntrypoint            - This is the physical address of the first instruction of the IBB.\n");
  printf ("\tPlatformDataFile      - File name of Platform Specific Data.\n");
  printf ("\tExternalBatchFile     - The external batch file which will handle signing process.\n");
  printf ("\t                      - For example:\n");
  printf ("\t                      -   \"BpmGen.BAT BIOS_ORG.FD BIOS_M.FD -B Sign.BAT Data.bin Sign.bin -O manifest.bin -OY keymanifest.bin\"\n");
  printf ("\t                      -   Sign.BAT: \"SignBpm.exe Data.bin Sign.bin -K bpm.pvk bpm.pbk\"\n");
  printf ("\tDataFile              - The input data file name for external batch.\n");
  printf ("\tSignatureFile         - The outout signature file name from external batch.\n");
  printf ("\tprivkey.pem           - Input private key generated by OPENSSL.\n");
  printf ("\tpubkey.pem            - Input public key generated by OPENSSL.\n");
  printf ("\tKeyManifestVersion    - Key Manifest's version number.\n");
  printf ("\tKeyManifestRevocation - Key Manifest Revocation Values.\n");
  printf ("\tKeyManifestID         - Key Manifest Identifier.\n");
  printf ("\tManifest              - Output Boot Policy Manifest data written into MBIOS automatically\n");
  printf ("\tKeyManifest           - Output Key Boot Policy Manifest data written into MBIOS automatically\n");
  printf ("Note:\n");
  printf ("  The public and private keys can be created as follows:\n");
//printf ("\topenssl genrsa -17 -out privkey.pem 2048 (Exponent is 0x11)\n");
  printf ("\topenssl genrsa -F4 -out privkey.pem 2048 (Exponent is 0x10001)\n");
  printf ("\topenssl rsa -pubout -in privkey.pem -out pubkey.pem\n");
}

VOID *
SetMem (
  OUT     VOID                      *Buffer,
  IN      UINTN                     Length,
  IN      UINT8                     Value
  )
{
  //
  // Declare the local variables that actually move the data elements as
  // volatile to prevent the optimizer from replacing this function with
  // the intrinsic memset()
  //
  volatile UINT8                    *Pointer;

  Pointer = (UINT8*)Buffer;
  while (Length-- > 0) {
    *(Pointer++) = Value;
  }
  return Buffer;
}

STATUS
ReadInputFile (
  IN CHAR8    *FileName,
  OUT UINT8   **FileData,
  OUT UINT32  *FileSize,
  OUT UINT8   **FileBufferRaw OPTIONAL
  )
/*++

Routine Description:

  Read input file

Arguments:

  FileName      - The input file name
  FileData      - The input file data, the memory is alligned.
  FileSize      - The input file size
  FileBufferRaw - The memory to hold input file data. The caller should use this to free the memory.

Returns:

  STATUS_SUCCESS - The file found and data read
  STATUS_ERROR   - The file data is not read
  STATUS_WARNING - The file is not found

--*/
{
  FILE                        *FpIn;
  UINT32                      TempResult;

  //
  // Open the Input Fvrecovery.fv file
  //
  if ((FpIn = fopen (FileName, "rb")) == NULL) {
    //
    // Return WARNING, let caller make decision
    //
//    Error (NULL, 0, 0, "Unable to open file", FileName);
    return STATUS_WARNING;
  }
  //
  // Get the Input Fvrecovery.fv file size
  //
  fseek (FpIn, 0, SEEK_END);
  *FileSize = ftell (FpIn);
  //
  // Read the contents of input file to memory buffer
  //
  if (FileBufferRaw != NULL) {
    *FileBufferRaw = (UINT8 *) malloc (*FileSize + 0x10000);
    if (NULL == *FileBufferRaw) {
      Error (NULL, 0, 0, "No sufficient memory to allocate!", NULL);
      fclose (FpIn);
      return STATUS_ERROR;
    }
    TempResult = 0x10000 - (UINT32) ((UINTN) *FileBufferRaw & 0x0FFFF);
    *FileData = (UINT8 *)((UINTN)*FileBufferRaw + TempResult);
  } else {
    *FileData = (UINT8 *) malloc (*FileSize);
     if (NULL == *FileData) {
      Error (NULL, 0, 0, "No sufficient memory to allocate!", NULL);
      fclose (FpIn);
      return STATUS_ERROR;
    }
  }
  fseek (FpIn, 0, SEEK_SET);
  TempResult = fread (*FileData, 1, *FileSize, FpIn);
  if (TempResult != *FileSize) {
    Error (NULL, 0, 0, "Read input file error!", NULL);
    if (FileBufferRaw != NULL) {
      free ((VOID *)*FileBufferRaw);
    } else {
      free ((VOID *)*FileData);
    }
    fclose (FpIn);
    return STATUS_ERROR;
  }

  //
  // Close the input Fvrecovery.fv file
  //
  fclose (FpIn);

  return STATUS_SUCCESS;
}

CHAR8 *mFitTypeStr[] = {
  "           ",
  "MICROCODE  ",
  "STARTUP_ACM",
  "           ",
  "           ",
  "           ",
  "           ",
  "BIOS_MODULE",
  "TPM_POLICY ",
  "BIOS_POLICY",
  "TXT_POLICY ",
  "KEYMANIFEST",
  "BP_MANIFEST",
  "BIOS_DATA_A",
};

CHAR8  mFitSignature[] = "'        ' ";
CHAR8 *
FitTypeToStr (
  IN FIRMWARE_INTERFACE_TABLE_ENTRY  *FitEntry
  )
/*++

Routine Description:

  Convert FitEntry type to a string

Arguments:

  FitEntry - Fit entry

Returns:

  String

--*/
{
  if (FitEntry->Type == FIT_TABLE_TYPE_HEADER) {
    CopyMem (&mFitSignature[1], &FitEntry->Address, sizeof(FitEntry->Address));
    return mFitSignature;
  }
  if (FitEntry->Type < sizeof (mFitTypeStr)/sizeof(mFitTypeStr[0])) {
    return mFitTypeStr[FitEntry->Type];
  } else {
    return "           ";
  }
}

VOID
PrintFitTable (
  IN UINT8                       *FvBuffer,
  IN UINT32                      FvSize
  )
/*++

Routine Description:

  Print Fit table in flash image

Arguments:

  FvBuffer       - Fvrecovery binary buffer
  FvSize         - Fvrecovery size

Returns:

  None

--*/
{
  FIRMWARE_INTERFACE_TABLE_ENTRY  *FitEntry;
  UINT32                          EntryNum;
  UINT32                          Index;
  UINT32                          FitTableOffset;
  FIRMWARE_INTERFACE_TABLE_ENTRY_PORT   *FitEntryPort;

  printf ("##############\n");
  printf ("# FIT Table: #\n");
  printf ("##############\n");

  printf ("FIT Pointer Offset: 0x%x\n", gFitTableContext.FitTablePointerOffset);
  FitTableOffset = *(UINT32 *)(FvBuffer + FvSize - gFitTableContext.FitTablePointerOffset);
  printf ("FIT Table Address:  0x%x\n", FitTableOffset);
  FitEntry = (FIRMWARE_INTERFACE_TABLE_ENTRY *)FLASH_TO_MEMORY(FitTableOffset, FvBuffer, FvSize);

  EntryNum = *(UINT32 *)(&FitEntry[0].Size[0]) & 0xFFFFFF;
  printf ("====== ================ ====== ======== ============== ==== ======== (====== ==== ====== ==== ======)\n");
  printf ("Index:      Address      Size  Version       Type      C_V  Checksum (Index  Data Width  Bit  Offset)\n");
  printf ("====== ================ ====== ======== ============== ==== ======== (====== ==== ====== ==== ======)\n");
  for (Index = 0; Index < EntryNum; Index++) {
    printf (" %02d:   %016llx %06x   %04x   %02x-%s  %02x     %02x   ",
      Index,
      (unsigned long long) FitEntry[Index].Address,
      *(UINT32 *)(&FitEntry[Index].Size[0]) & 0xFFFFFF,
      FitEntry[Index].Version,
      FitEntry[Index].Type,
      FitTypeToStr(&FitEntry[Index]),
      FitEntry[Index].C_V,
      FitEntry[Index].Checksum
      );
    switch (FitEntry[Index].Type) {
    case FIT_TABLE_TYPE_TPM_POLICY:
    case FIT_TABLE_TYPE_TXT_POLICY:
      if (FitEntry[Index].Version == 0) {
        FitEntryPort = (FIRMWARE_INTERFACE_TABLE_ENTRY_PORT *)&FitEntry[Index];
        printf (" ( %04x  %04x   %02x    %02x   %04x )\n",
          FitEntryPort->IndexPort,
          FitEntryPort->DataPort,
          FitEntryPort->Width,
          FitEntryPort->Bit,
          FitEntryPort->Index
          );
        break;
      }
      // Not Port Configure, pass through
    default:
      printf ("\n");
      break;
    }
  }
  printf ("====== ================ ====== ======== ============== ==== ======== (====== ==== ====== ==== ======)\n");
  printf ("Index:      Address      Size  Version       Type      C_V  Checksum (Index  Data Width  Bit  Offset)\n");
  printf ("====== ================ ====== ======== ============== ==== ======== (====== ==== ====== ==== ======)\n");
}

UINT32
GetFitEntryInfo (
  IN UINT8     *FvBuffer,
  IN UINT32    FvSize
  )
/*++

Routine Description:

  Fill the FIT table information to Fvrecovery

Arguments:

  FvBuffer       - Fvrecovery binary buffer
  FvSize         - Fvrecovery size

Returns:

  0 - Fit Table not found

--*/
{
  FIRMWARE_INTERFACE_TABLE_ENTRY *FitEntry;
  UINT32                          FitIndex;
  UINT32                          FitTableOffset;

  //
  // 1. FitPointer
  //
  if (gFitTableContext.FitTablePointerOffset == 0) {
    gFitTableContext.FitTablePointerOffset = DEFAULT_FIT_TABLE_POINTER_OFFSET;
  }

  FitTableOffset = *(UINT32 *)(FvBuffer + FvSize - gFitTableContext.FitTablePointerOffset);

  if ((FitTableOffset == 0xEEEEEEEE) ||
      (FitTableOffset == 0xFFFFFFFF) ||
      (FitTableOffset == 0)) {
    Error (NULL, 0, 0, "Invalid FIT table pointer",  NULL);
    return 0;
  }

  FitEntry = (FIRMWARE_INTERFACE_TABLE_ENTRY *)FLASH_TO_MEMORY(FitTableOffset, FvBuffer, FvSize);
  FitIndex = 0;

  //
  // 2. FitHeader
  //
  if (FitEntry[FitIndex].Address != *(UINT64 *)"_FIT_   ") {
    return 0;
  }
  if (FitEntry[FitIndex].Type != FIT_TABLE_TYPE_HEADER) {
    return 0;
  }
  gFitTableContext.FitEntryNumber = *(UINT32 *)&FitEntry[FitIndex].Size[0];
  gFitTableContext.FitHeaderVersion = FitEntry[FitIndex].Version;

  //
  // 3. FitEntry
  //
  FitIndex++;
  for (; FitIndex < gFitTableContext.FitEntryNumber; FitIndex++) {
    switch (FitEntry[FitIndex].Type) {
    case FIT_TABLE_TYPE_MICROCODE:
      gFitTableContext.Microcode[gFitTableContext.MicrocodeNumber].Address = (UINT32)FitEntry[FitIndex].Address;
      gFitTableContext.MicrocodeVersion                                    = FitEntry[FitIndex].Version;
      gFitTableContext.MicrocodeNumber ++;
      break;
    case FIT_TABLE_TYPE_STARTUP_ACM:
      gFitTableContext.StartupAcm.Address = (UINT32)FitEntry[FitIndex].Address;
      gFitTableContext.StartupAcmVersion  = FitEntry[FitIndex].Version;
      break;
    case FIT_TABLE_TYPE_BIOS_MODULE:
      gFitTableContext.BiosModule[gFitTableContext.BiosModuleNumber].Address = (UINT32)FitEntry[FitIndex].Address;
      gFitTableContext.BiosModule[gFitTableContext.BiosModuleNumber].Size    = *(UINT32 *)&FitEntry[FitIndex].Size[0] * 16;
      gFitTableContext.BiosModuleVersion                                     = FitEntry[FitIndex].Version;
      gFitTableContext.BiosModuleNumber ++;
      break;
    case FIT_TABLE_TYPE_TPM_POLICY:
    case FIT_TABLE_TYPE_TXT_POLICY:
      if (FitEntry[FitIndex].Version == 0) {
        gFitTableContext.PortModule[gFitTableContext.PortModuleNumber].Address = (UINT32)FitEntry[FitIndex].Address;
        gFitTableContext.PortModule[gFitTableContext.PortModuleNumber].Size    = (UINT32)(FitEntry[FitIndex].Address >> 32);
        gFitTableContext.PortModule[gFitTableContext.PortModuleNumber].Version = FitEntry[FitIndex].Version;
        gFitTableContext.PortModule[gFitTableContext.PortModuleNumber].Type    = FitEntry[FitIndex].Type;
        gFitTableContext.PortModuleNumber ++;
        break;
      }
      // Not Port Configure, pass through
    default: // Others
      gFitTableContext.OptionalModule[gFitTableContext.OptionalModuleNumber].Address = (UINT32)FitEntry[FitIndex].Address;
      gFitTableContext.OptionalModule[gFitTableContext.OptionalModuleNumber].Size    = *(UINT32 *)&FitEntry[FitIndex].Size[0];
      gFitTableContext.OptionalModule[gFitTableContext.OptionalModuleNumber].Version = FitEntry[FitIndex].Version;
      gFitTableContext.OptionalModule[gFitTableContext.OptionalModuleNumber].Type    = FitEntry[FitIndex].Type;
      gFitTableContext.OptionalModuleNumber ++;
      break;
    }
  }

  return gFitTableContext.FitEntryNumber;
}

FIT_TABLE_CONTEXT_ENTRY *
GetFitEntryWithIndex (
  IN UINT32  Type,
  IN UINT32  EntryIndex
  )
/*++

Routine Description:

  Get FitEntry according to the type.
  The 1st entry match type will be returned.

Arguments:

  Type          - Fit entry type

Returns:

  FitEntry

--*/
{
  UINTN Index;
  UINTN FoundIndex;

  if (Type == FIT_TABLE_TYPE_STARTUP_ACM) {
    if (EntryIndex == 0) {
      return &gFitTableContext.StartupAcm;
    } else {
      return NULL;
    }
  }

  if (Type == FIT_TABLE_TYPE_BIOS_MODULE) {
    FoundIndex = 0;
    for (Index = 0; Index < gFitTableContext.BiosModuleNumber; Index++) {
      if (FoundIndex == EntryIndex) {
        return &gFitTableContext.BiosModule[Index];
      } else {
        FoundIndex ++;
      }
    }
    return NULL;
  }

  if (Type == FIT_TABLE_TYPE_MICROCODE) {
    FoundIndex = 0;
    for (Index = 0; Index < gFitTableContext.MicrocodeNumber; Index++) {
      if (FoundIndex == EntryIndex) {
        return &gFitTableContext.Microcode[Index];
      } else {
        FoundIndex ++;
      }
    }
    return NULL;
  }

  FoundIndex = 0;
  for (Index = 0; Index < gFitTableContext.OptionalModuleNumber; Index++) {
    if (gFitTableContext.OptionalModule[Index].Type == Type) {
      if (FoundIndex == EntryIndex) {
        return &gFitTableContext.OptionalModule[Index];
      } else {
        FoundIndex ++;
      }
    }
  }

  return NULL;
}

FIT_TABLE_CONTEXT_ENTRY *
GetFitEntry (
  IN UINT32  Type
  )
/*++

Routine Description:

  Get FitEntry according to the type.
  The 1st entry match type will be returned.

Arguments:

  Type          - Fit entry type

Returns:

  FitEntry

--*/
{
  return GetFitEntryWithIndex (Type, 0);
}

FIRMWARE_INTERFACE_TABLE_ENTRY *
GetFitEntryWithIndexFromFd (
  IN UINT32  Type,
  IN UINT32  EntryIndex,
  IN UINT8   *FdBuffer,
  IN UINT32  FdSize
  )
/*++

Routine Description:

  Get FitEntry according to the type.
  The 1st entry match type will be returned.

Arguments:

  Type          - Fit entry type

Returns:

  FitEntry

--*/
{
  UINTN Index;
  UINTN FoundIndex;
  FIRMWARE_INTERFACE_TABLE_ENTRY  *FitEntry;
  UINTN FitEntryCount;

  FitEntry = (VOID *)(UINTN)FLASH_TO_MEMORY (
                              *(UINT32 *)(FdBuffer + FdSize - gFitTableContext.FitTablePointerOffset),
                              FdBuffer,
                              FdSize
                              );
  FitEntryCount = (*(UINT32 *)FitEntry[0].Size & 0xFFFFFF);

  FoundIndex = 0;
  for (Index = 0; Index < FitEntryCount; Index++) {
    if (FitEntry[Index].Type == Type) {
      if (FoundIndex == EntryIndex) {
        return &FitEntry[Index];
      } else {
        FoundIndex ++;
      }
    }
  }

  return NULL;
}

FIRMWARE_INTERFACE_TABLE_ENTRY *
GetFitEntryFromFd (
  IN UINT32  Type,
  IN UINT8   *FdBuffer,
  IN UINT32  FdSize
  )
/*++

Routine Description:

  Get FitEntry according to the type.
  The 1st entry match type will be returned.

Arguments:

  Type          - Fit entry type

Returns:

  FitEntry

--*/
{
  return GetFitEntryWithIndexFromFd (Type, 0, FdBuffer, FdSize);
}

STATUS
WriteOutputFile (
  IN CHAR8   *FileName,
  IN UINT8   *FileData,
  IN UINT32  FileSize
  )
/*++

Routine Description:

  Read input file

Arguments:

  FileName      - The input file name
  FileData      - The input file data
  FileSize      - The input file size

Returns:

  STATUS_SUCCESS - Write file data successfully
  STATUS_ERROR   - The file data is not written

--*/
{
  FILE                        *FpOut;

  //
  // Open the output Fvrecovery.fv file
  //
  if ((FpOut = fopen (FileName, "w+b")) == NULL) {
    Error (NULL, 0, 0, "Unable to open file", "%s", FileName);
    return STATUS_ERROR;
  }
  //
  // Write the output Fvrecovery.fv file
  //
  if ((fwrite (FileData, 1, FileSize, FpOut)) != FileSize) {
    Error (NULL, 0, 0, "Write output file error!", "%s", FileName);
    fclose (FpOut);
    return STATUS_ERROR;
  }

  //
  // Close the output Fvrecovery.fv file
  //
  fclose (FpOut);

  return STATUS_SUCCESS;
}

VOID
SwapEndian (
  IN UINT8  *Area,
  IN UINT32 Size
  )
/*++

Routine Description:

  Swap area from big endian to little endian

Arguments:

  Area - Buffer address
  Size - Buffer size

Returns:

  None

--*/
{
  UINT8 Temp;
  UINTN Index;

  for (Index = 0; Index < (UINTN)Size / 2; Index++) {
    Temp = *(Area + Index);
    *(Area + Index) = *(Area + Size - 1 - Index);
    *(Area + Size - 1 - Index) = Temp;
  }
}

STATUS
CreateHash (
  IN  UINT8     *Data,
  IN  UINTN     Size,
  OUT UINT8     *Hash
  )
/*++

Routine Description:

  Create Hash for input data

Arguments:

  Data - Data address
  Size - Data size
  Hash - Hash generated

Returns:

  STATUS_SUCCESS

--*/
{
  EVP_MD_CTX   ctx;
  const EVP_MD *md;

  md = EVP_sha256();
  EVP_DigestInit(&ctx, md);
  EVP_DigestUpdate(&ctx, Data, Size);
  EVP_DigestFinal(&ctx, (UINT8 *)Hash, NULL);

  return STATUS_SUCCESS;
}

VOID
PrintHash (
  IN CHAR8     *Str,
  IN UINT8     *Hash
  )
/*++

Routine Description:

  Print hash

Arguments:

  Str  - Prefix string
  Hash - Hash to be printed

Returns:

  None

--*/
{
  UINTN Index;
  printf ("%s", Str);
  for (Index = 0; Index < SHA256_DIGEST_SIZE; Index++) {
    printf ("%02x", Hash[Index]);
  }
  printf ("\n");
}

VOID
DumpHex (
  IN UINT8 *Buffer,
  IN UINTN BufferSize
  )
/*++

Routine Description:

  Dump hex data

Arguments:

  Buffer     - Buffer address
  BufferSize - Buffer size

Returns:

  None

--*/
{
  UINTN  Index;
  UINTN  IndexJ;
#define COL_SIZE  16

  for (Index = 0; Index < BufferSize/COL_SIZE; Index++) {
    printf ("      %04x: ", (UINT16) Index * COL_SIZE);
    for (IndexJ = 0; IndexJ < COL_SIZE; IndexJ++) {
      printf ("%02x ", *(Buffer + Index * COL_SIZE + IndexJ));
    }
    printf ("\n");
  }
  if ((BufferSize % COL_SIZE) != 0) {
    printf ("      %04x: ", (UINT16) Index * COL_SIZE);
    for (IndexJ = 0; IndexJ < (BufferSize % COL_SIZE); IndexJ++) {
      printf ("%02x ", *(Buffer + Index * COL_SIZE + IndexJ));
    }
    printf ("\n");
  }
}

VOID
PrintHashStructure (
  IN HASH_STRUCTURE  *Hash
  )
{
  UINTN  Index;
  printf ("    HashStructure:\n");
  printf ("      HashAlg:    0x%04x\n", Hash->HashAlg);
  printf ("      Size:       0x%04x\n", Hash->Size);
  printf ("      HashBuffer: ");
  for (Index = 0; Index < sizeof(Hash->HashBuffer); Index++) {
    printf ("%02x", Hash->HashBuffer[Index]);
  }
  printf ("\n");
}

VOID
PrintRsaPublicKeyStructure (
  IN RSA_PUBLIC_KEY_STRUCT  *RsaPublicKeyStruct
  )
{
  printf ("    RsaPublicKeyStructure:\n");
  printf ("      Version:    0x%02x\n", RsaPublicKeyStruct->Version);
  printf ("      KeySize:    0x%04x\n", RsaPublicKeyStruct->KeySize);
  printf ("      Exponent:   0x%08x\n", RsaPublicKeyStruct->Exponent);
  printf ("      Modulus:\n");
  DumpHex (RsaPublicKeyStruct->Modulus, sizeof(RsaPublicKeyStruct->Modulus));
  printf ("\n");
}

VOID
PrintRsaSsaSigStructure (
  IN RSASSA_SIGNATURE_STRUCT  *RsaSsaSigStruct
  )
{
  printf ("    RsaSsaSigStructure:\n");
  printf ("      Version:    0x%02x\n", RsaSsaSigStruct->Version);
  printf ("      KeySize:    0x%04x\n", RsaSsaSigStruct->KeySize);
  printf ("      HashAlg:    0x%04x\n", RsaSsaSigStruct->HashAlg);
  printf ("      Signature:\n");
  DumpHex (RsaSsaSigStruct->Signature, sizeof(RsaSsaSigStruct->Signature));
  printf ("\n");
}

VOID
PrintKeySignatureStructure (
  IN KEY_SIGNATURE_STRUCT  *KeySignatureStruct
  )
{
  printf ("  KeySignatureStructure:\n");
  printf ("    Version:      0x%02x\n", KeySignatureStruct->Version);
  printf ("    KeyAlg:       0x%04x\n", KeySignatureStruct->KeyAlg);
  PrintRsaPublicKeyStructure (&KeySignatureStruct->Key);
  printf ("    SigScheme:    0x%04x\n", KeySignatureStruct->SigScheme);
  PrintRsaSsaSigStructure (&KeySignatureStruct->Signature);
}

VOID
PrintStructureID (
  IN UINT8 *StructureID
  )
{
  UINTN  Index;
  printf ("  StructureID:    ");
  for (Index = 0; Index < 8; Index++) {
    printf ("%c", StructureID[Index]);
  }
  printf ("\n");
}

VOID
PrintBootPolicyManifestHeaderElement (
  IN BOOT_POLICY_MANIFEST_HEADER  *BpmHeader
  )
{
  printf ("BootPolicyManifestHeaderElement:\n");
  PrintStructureID (BpmHeader->StructureID);
  printf ("  StructVersion:  0x%02x\n", BpmHeader->StructVersion);
  printf ("  HdrStructVer:   0x%02x\n", BpmHeader->HdrStructVersion);
  printf ("  PMBPMVersion:   0x%02x\n", BpmHeader->PMBPMVersion);
  printf ("  BPSVN:          0x%02x\n", BpmHeader->BPSVN);
  printf ("  ACMSVN:         0x%02x\n", BpmHeader->ACMSVN);
  printf ("  Reserved:       %02x\n", BpmHeader->Reserved);
  printf ("  NEMDataStack:   0x%04x\n", BpmHeader->NEMDataStack);
}

VOID
PrintIbbElement (
  IN IBB_ELEMENT  *IbbElement
  )
{
  UINT32 Index;

  printf ("IbbElement:\n");
  PrintStructureID (IbbElement->StructureID);
  printf ("  StructVersion:  0x%02x\n", IbbElement->StructVersion);
  printf ("  SetNumber:      0x%02x\n", IbbElement->SetNumber);
  printf ("  Reserved:       %02x\n", IbbElement->Reserved);
  printf ("  PBETValue:      0x%02x\n", IbbElement->PBETValue);
  printf ("  Flags:          0x%08x\n", IbbElement->Flags);
  printf ("    Enable VT-d:  0x%08x\n", IbbElement->Flags & IBB_FLAG_ENABLE_VTD);
  printf ("    InitMeasLoc3: 0x%08x\n", IbbElement->Flags & IBB_FLAG_INITIAL_MEASURE_LOC3);
  printf ("    AuthorityMeas:0x%08x\n", IbbElement->Flags & IBB_FLAG_AUTHORITY_MEASURE);
  printf ("  IBB_MCHBAR:     0x%016llx\n", (unsigned long long) IbbElement->IBB_MCHBAR);
  printf ("  VTD_BAR:        0x%016llx\n", (unsigned long long) IbbElement->VTD_BAR);
  printf ("  PMRL_Base:      0x%08x\n", IbbElement->PMRL_Base);
  printf ("  PMRL_Limit:     0x%08x\n", IbbElement->PMRL_Limit);
  printf ("  PMRH_Base:      0x%016llx\n", (unsigned long long) IbbElement->PMRH_Base);
  printf ("  PMRH_Limit:     0x%016llx\n", (unsigned long long) IbbElement->PMRH_Limit);
  printf ("  PostIbbHash:\n");
  PrintHashStructure (&IbbElement->PostIbbHash);
  printf ("  EntryPoint:     0x%08x\n", IbbElement->EntryPoint);
  printf ("  Digest:\n");
  PrintHashStructure (&IbbElement->Digest);
  printf ("  SegmentCount:   0x%02x\n", IbbElement->SegmentCount);
  for (Index = 0; Index < IbbElement->SegmentCount; Index++) {
    printf ("  Segment(%d)\n", Index);
    printf ("    Reserved:     %02x %02x\n",
      IbbElement->IBBSegment[Index].Reserved[0],
      IbbElement->IBBSegment[Index].Reserved[1]
      );
    printf ("    Flags:        0x%04x\n", IbbElement->IBBSegment[Index].Flags);
    if ((IbbElement->IBBSegment[Index].Flags & IBB_SEGMENT_FLAG_NON_IBB) != 0) {
      printf ("      Non-IBB Segment\n");
    } else {
      printf ("      IBB Segment\n");
    }
    printf ("    Base:         0x%08x\n", IbbElement->IBBSegment[Index].Base);
    printf ("    Size:         0x%08x\n", IbbElement->IBBSegment[Index].Size);
  }
}

VOID
PrintPlatformManufacturerElement (
  IN PLATFORM_MANUFACTURER_ELEMENT  *PmElement
  )
{
  printf ("PlatformManufacturerElement:\n");
  PrintStructureID (PmElement->StructureID);
  printf ("  StructVersion:  0x%02x\n", PmElement->StructVersion);
  printf ("  PMDataSize:     0x%08x\n", PmElement->PMDataSize);
  printf ("  PMData:\n");
  DumpHex ((UINT8 *)PmElement + 1, PmElement->PMDataSize);
  printf ("\n");
}

VOID
PrintBootPolicyManifestSignatureElement (
  IN BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT  *BpmSignatureElement
  )
{
  printf ("BootPolicyManifestSignatureElement:\n");
  PrintStructureID (BpmSignatureElement->StructureID);
  printf ("  StructVersion:  0x%02x\n", BpmSignatureElement->StructVersion);
  PrintKeySignatureStructure (&BpmSignatureElement->KeySignature);
}

VOID
PrintKeyHash (
  IN KEY_SIGNATURE_STRUCT *KeySignature
  )
{
  UINT8    HashBuffer[SHA256_DIGEST_SIZE];
  UINTN    Index;

  CreateHash (KeySignature->Key.Modulus, KeySignature->Key.KeySize/8, HashBuffer);

  printf ("# KEYHASH # : ");
  for (Index = 0; Index < sizeof(HashBuffer); Index++) {
    printf ("%02x", HashBuffer[Index]);
  }
  printf ("\n\n");
}

VOID
PrintBootPolicyManifest (
  IN UINT8  *BootPolicyManifest
  )
{
  BOOT_POLICY_MANIFEST_HEADER             *BpmHeader;
  IBB_ELEMENT                             *IbbElement;
  PLATFORM_MANUFACTURER_ELEMENT           *PmElement;
  BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT  *BpmSignatureElement;
  UINT8                                   *Buffer;

  printf ("######################\n");
  printf ("# BootPolicyManifest #\n");
  printf ("######################\n");

  Buffer = BootPolicyManifest;

  BpmHeader = (BOOT_POLICY_MANIFEST_HEADER *)Buffer;
  if (*(UINT64 *)BpmHeader->StructureID != BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_ID) {
    return ;
  }
  PrintBootPolicyManifestHeaderElement (BpmHeader);
  Buffer += sizeof(BOOT_POLICY_MANIFEST_HEADER);

  IbbElement = (IBB_ELEMENT *)Buffer;
  if (*(UINT64 *)IbbElement->StructureID != BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID) {
    return ;
  }
  PrintIbbElement (IbbElement);
  Buffer += sizeof(IBB_ELEMENT) + sizeof(IBB_SEGMENT_ELEMENT) * (IbbElement->SegmentCount - 1);

  PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)Buffer;
  while (*(UINT64 *)PmElement->StructureID == BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID) {
    PrintPlatformManufacturerElement (PmElement);
    Buffer += sizeof(PLATFORM_MANUFACTURER_ELEMENT) + PmElement->PMDataSize;
    PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)Buffer;
  }

  BpmSignatureElement = (BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT *)Buffer;
  if (*(UINT64 *)BpmSignatureElement->StructureID != BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_STRUCTURE_ID) {
    return ;
  }
  PrintBootPolicyManifestSignatureElement (BpmSignatureElement);

  PrintKeyHash (&BpmSignatureElement->KeySignature);
}

VOID
PrintKeyManifest (
  IN KEY_MANIFEST_STRAUCTURE  *KeyManifest
  )
{
  printf ("###############\n");
  printf ("# KeyManifest #\n");
  printf ("###############\n");

  if (*(UINT64 *)KeyManifest->StructureID != KEY_MANIFEST_STRUCTURE_ID) {
    return ;
  }

  printf ("KeyManifestElement:\n");

  PrintStructureID (KeyManifest->StructureID);
  printf ("  StructVersion:  0x%02x\n", KeyManifest->StructVersion);
  printf ("  KeyManifestVer: 0x%02x\n", KeyManifest->KeyManifestVersion);
  printf ("  KMSVN:          0x%02x\n", KeyManifest->KMSVN);
  printf ("  KeyManifestID:  0x%02x\n", KeyManifest->KeyManifestID);
  printf ("  BPKey:\n");
  PrintHashStructure (&KeyManifest->BPKey);
  PrintKeySignatureStructure (&KeyManifest->KeyManifestSignature);

  PrintKeyHash (&KeyManifest->KeyManifestSignature);
}

VOID
PrintBiosDataArea (
  IN BIOS_DATA_AREA_STRAUCTURE  *BiosDataArea
  )
{
  BDAS_DATA_ENTRY   *BdasDataEntry;
  UINT32            Index;

  printf ("################\n");
  printf ("# BiosDataArea #\n");
  printf ("################\n");

  if (*(UINT64 *)BiosDataArea->StructureID != BIOS_DATA_AREA_STRUCTURE_ID) {
    return ;
  }

  printf ("BiosDataArea:\n");

  PrintStructureID (BiosDataArea->StructureID);
  printf ("  StructVersion:  0x%08x\n", BiosDataArea->StructVersion);
  printf ("  DataEntryCount: 0x%08x\n", BiosDataArea->BDAS_DataEntryCount);
  BdasDataEntry = (BDAS_DATA_ENTRY *)(BiosDataArea->BDAS_DataEntry);
  for (Index = 0; Index < BiosDataArea->BDAS_DataEntryCount; Index++) {
    printf ("  DataEntry(%d)\n", Index);
    printf ("    Enumeration:  0x%04llx\n", (unsigned long long) BdasDataEntry[Index].Enumeration);
    printf ("    Data:         0x%012llx\n", (unsigned long long) BdasDataEntry[Index].Data);
    switch (BdasDataEntry[Index].Enumeration) {
    case BDAS_DATA_ENTRY_TYPE_TPM_ACTIVATION_STATUS:
      printf ("      TPM_Deac:   0x%012llx\n", (unsigned long long) BdasDataEntry[Index].Data & BDAS_DATA_ENTRY_DATA_TPM_DEACTIVATED);
      break;
    case BDAS_DATA_ENTRY_TYPE_RESERVED:
    default:
      break;
    }
  }
}

STATUS
PrepareSignature (
  IN CHAR8  *PubkeyName,
  OUT UINT8 *PubkeyArea,
  OUT UINT8 *PubkeyExpArea
  )
/*++

Routine Description:

  Get pubkey size and put pubkey into global context

Arguments:

  None

Returns:

  STATUS_SUCCESS

--*/
{
  FILE   *fp;
  RSA    *pubkey;
  UINT32 PubkeySize;
  UINT32 PubkeyExpSize;

  fp = fopen(PubkeyName, "r");
  if (fp == NULL) {
    return STATUS_ERROR;
  }

  pubkey = PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL);
  fclose (fp);
  if (pubkey == NULL) {
    return STATUS_ERROR;
  }

  PubkeySize = RSA_size(pubkey);
  if (BN_num_bytes(pubkey->n) != (int)PubkeySize) {
    RSA_free(pubkey);
    return STATUS_ERROR;
  }

  if (PubkeySize != RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT) {
    printf ("Pubkey size - %d\n", PubkeySize);
    Error (NULL, 0, 0, "PubKey size is NOT 256", NULL);
    RSA_free(pubkey);
    return STATUS_ERROR;
  }

  PubkeyExpSize = BN_num_bytes(pubkey->e);
  if (PubkeyExpSize > 4) {
    printf ("Pubkey exponent size - %d\n", PubkeyExpSize);
    Error (NULL, 0, 0, "PubKey exponent size is bigger than 4", NULL);
    RSA_free(pubkey);
    return STATUS_ERROR;
  }

  BN_bn2bin(pubkey->n, PubkeyArea);

  BN_bn2bin(pubkey->e, PubkeyExpArea);

  RSA_free(pubkey);

  //
  // Openssl key is big-endian and Policy needs little-endian
  //
  SwapEndian (PubkeyArea, PubkeySize);
//  SwapEndian (PubkeyExpArea, 4);

  return STATUS_SUCCESS;
}

STATUS
CreateSignature (
  IN CHAR8  *PrivKeyName,
  OUT UINT8 *SignArea,
  IN UINT8  *Data,
  IN UINTN  DataSize
  )
/*++

Routine Description:

  Create Signature into global context

Arguments:

  None

Returns:

  STATUS_SUCCESS

--*/
{
  FILE     *fp;
  RSA      *privkey;
  UINT32   sig_len;
  UINT8    digest[SHA256_DIGEST_SIZE];
  UINT32   PubkeySize;
  UINT32   PrikeySize;
  STATUS   Status;

  fp = fopen(PrivKeyName, "r");
  if (fp == NULL) {
    return STATUS_ERROR;
  }

  privkey = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL);
  fclose (fp);
  if (privkey == NULL) {
    return STATUS_ERROR;
  }

  PubkeySize = RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT;
  PrikeySize = RSA_size(privkey);
  if (PrikeySize != (int)PubkeySize) {
    printf ("Prikey size - %d\n", PrikeySize);
    Error (NULL, 0, 0, "PriKey size is NOT 256", NULL);
    RSA_free(privkey);
    return STATUS_ERROR;
  }

  //
  // first create digest of list (all except sig_block)
  //
  Status = CreateHash(Data, DataSize, digest);
  if (Status != STATUS_SUCCESS) {
    RSA_free(privkey);
    return STATUS_ERROR;
  }

  //
  // sign digest
  //
  if (!RSA_sign(NID_sha256, (UINT8 *)&digest, SHA256_DIGEST_SIZE, SignArea, &sig_len, privkey) ) {
    RSA_free(privkey);
    return STATUS_ERROR;
  }
  if (sig_len != PubkeySize) {
    RSA_free(privkey);
    return STATUS_ERROR;
  }

  RSA_free(privkey);

  //
  // SigBlock is big-endian
  //
//  SwapEndian (SignArea, PubkeySize);

  return STATUS_SUCCESS;
}

STATUS
CreateBootPolicyKeyHash (
  IN  CHAR8   *PubKeyName,
  OUT UINT8   *Hash,
  IN  BOOLEAN IsBin
  )
{
  EVP_MD_CTX   ctx;
  const EVP_MD *md;
  FILE   *fp;
  RSA    *pubkey;
  UINT8  PubkeyArea[RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT];
  UINT32 PubkeySize;
  UINT8  *TempData;
  STATUS Status;

  if (IsBin) {
    Status = ReadInputFile (PubKeyName, &TempData, &PubkeySize, NULL);
    if (Status != STATUS_SUCCESS) {
      return STATUS_ERROR;
    }
    CopyMem (PubkeyArea, TempData, sizeof(PubkeyArea));
    free (TempData);
  } else {
    fp = fopen(PubKeyName, "r");
    if (fp == NULL) {
      return STATUS_ERROR;
    }

    pubkey = PEM_read_RSA_PUBKEY(fp, NULL, NULL, NULL);
    fclose (fp);
    if (pubkey == NULL) {
      return STATUS_ERROR;
    }

    PubkeySize = RSA_size(pubkey);
    if (BN_num_bytes(pubkey->n) != (int)PubkeySize) {
      RSA_free(pubkey);
      return STATUS_ERROR;
    }

    if (PubkeySize != RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT) {
      printf ("Pubkey size - %d\n", PubkeySize);
      Error (NULL, 0, 0, "PubKey size is NOT 256", NULL);
      RSA_free(pubkey);
      return STATUS_ERROR;
    }

    BN_bn2bin(pubkey->n, PubkeyArea);

    RSA_free(pubkey);

    //
    // Openssl key is big-endian and Policy needs little-endian
    //
    SwapEndian (PubkeyArea, PubkeySize);
  }

  md = EVP_sha256();
  EVP_DigestInit(&ctx, md);

  EVP_DigestUpdate(
      &ctx,
      PubkeyArea,
      PubkeySize
      );

  EVP_DigestFinal(&ctx, (UINT8 *)Hash, NULL);

  return STATUS_SUCCESS;
}

STATUS
CreatePostIbbBiosHash (
  IN  UINT8     *Data,
  IN  UINTN     Size,
  OUT UINT8     *Hash
  )
{
  EVP_MD_CTX   ctx;
  const EVP_MD *md;
  UINTN        Index;

  md = EVP_sha256();
  EVP_DigestInit(&ctx, md);

  for (Index = 0; Index < gFitTableContext.PostIbbBiosModuleNumber; Index++) {
    EVP_DigestUpdate(
        &ctx,
        FLASH_TO_MEMORY (gFitTableContext.PostIbbBiosModule[Index].Address, Data, Size),
        gFitTableContext.PostIbbBiosModule[Index].Size
        );
  }

  EVP_DigestFinal(&ctx, (UINT8 *)Hash, NULL);

  return STATUS_SUCCESS;
}

STATUS
CreateBiosHash (
  IN  UINT8     *Data,
  IN  UINTN     Size,
  OUT UINT8     *Hash
  )
/*++

Routine Description:

  Create BIOS hash accroding to FIT table

Arguments:

  Data - BIOS buffer
  Hash - Hash for BIOS MODULE in FIT table
  Size - BIOS size

Returns:

  STATUS_SUCCESS

--*/
{
  EVP_MD_CTX   ctx;
  const EVP_MD *md;
  UINTN        Index;

  md = EVP_sha256();
  EVP_DigestInit(&ctx, md);

  for (Index = 0; Index < gFitTableContext.BiosModuleNumber; Index++) {
    EVP_DigestUpdate(
        &ctx,
        FLASH_TO_MEMORY (gFitTableContext.BiosModule[Index].Address, Data, Size),
        gFitTableContext.BiosModule[Index].Size
        );
  }

  EVP_DigestFinal(&ctx, (UINT8 *)Hash, NULL);

  return STATUS_SUCCESS;
}

STATUS
PrepareSignatureForExternalBatch (
  IN CHAR8    *FileName,
  IN VOID     *Data,
  IN UINT32   DataSize
  )
{
  return WriteOutputFile (FileName, Data, DataSize);
}

STATUS
CreateSignatureFromExternalBatch (
  IN CHAR8    *FileName,
  OUT VOID    *Data,
  IN UINT32   DataSize
  )
{
  UINT8   *FileData;
  UINT32  FileDataSize;
  STATUS  Status;

  Status = ReadInputFile (FileName, &FileData, &FileDataSize, NULL);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "ReadInputFile error", FileName);
    return STATUS_ERROR;
  }

  if (FileDataSize != DataSize) {
    printf ("DataSize - 0x%x, FileDataSize - 0x%x\n", DataSize, FileDataSize);
    Error (NULL, 0, 0, "SignatureFile size mismatch!", FileName);
    free (FileData);
    return STATUS_ERROR;
  }

  CopyMem (Data, FileData, DataSize);
  free (FileData);

  return STATUS_SUCCESS;
}

STATUS
InvokeExternalBatch (
  IN CHAR8    *FileName
  )
{
  system (FileName);
  return STATUS_SUCCESS;
}

STATUS
CreateBpm (
  IN UINT8     *FdBuffer,
  IN UINT32    FdSize
  )
/*++

Routine Description:

  Create Bpm into global context

Arguments:

  None

Returns:

  STATUS_SUCCESS

--*/
{
  STATUS                                  Status;
  UINTN                                   Index;
  UINTN                                   BiosModuleIndex;
  UINTN                                   NonIbbBiosModuleIndex;
  UINT8                                   *TempBuf;
  BOOT_POLICY_MANIFEST_HEADER             *BpmHeader;
  IBB_ELEMENT                             *IbbElement;
  PLATFORM_MANUFACTURER_ELEMENT           *PmElement;
  BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT  *BpmSignatureElement;
  KEY_MANIFEST_STRAUCTURE                 *KeyManifest;
  KEY_SIGNATURE_STRUCT                    *KeyManifestSignature;
  BIOS_DATA_AREA_STRAUCTURE               *BiosDataArea;

  // Create Bpm
  gMBiosContext.BootPolicyManifestSize = sizeof(BOOT_POLICY_MANIFEST_HEADER) +
                                         sizeof(IBB_ELEMENT) + sizeof(IBB_SEGMENT_ELEMENT) * (gMBiosContext.SegmentCount - 1) +
                                         gMBiosContext.PlatformDataTotalSize +
                                         sizeof(BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT);
  gMBiosContext.BootPolicyManifest = malloc (gMBiosContext.BootPolicyManifestSize);
  TempBuf = gMBiosContext.BootPolicyManifest;
  if (NULL == TempBuf) {
    Error (NULL, 0, 0, "No sufficient memory to allocate!", NULL);
    return STATUS_ERROR;
  }
  ZeroMem (TempBuf, gMBiosContext.BootPolicyManifestSize);

  // BOOT_POLICY_MANIFEST_HEADER
  BpmHeader = (BOOT_POLICY_MANIFEST_HEADER *)TempBuf;
  *(UINT64 *)BpmHeader->StructureID = BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_ID;
  BpmHeader->StructVersion = BOOT_POLICY_MANIFEST_STRUCTURE_VERSION;
  BpmHeader->HdrStructVersion = BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_VERSION;
  BpmHeader->PMBPMVersion = gMBiosContext.PMBPMVersion;
  BpmHeader->BPSVN = gMBiosContext.BootPolicyRevocation;
  BpmHeader->ACMSVN = gMBiosContext.AcmRecocation;
  BpmHeader->NEMDataStack = gMBiosContext.NEMDataStack;
  TempBuf += sizeof(BOOT_POLICY_MANIFEST_HEADER);

  // IBB_ELEMENT
  IbbElement = (IBB_ELEMENT *)TempBuf;
  *(UINT64 *)IbbElement->StructureID = BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID;
  IbbElement->StructVersion = BOOT_POLICY_MANIFEST_IBB_ELEMENT_VERSION;
  IbbElement->SetNumber = 0; // TBD
  IbbElement->PBETValue = gMBiosContext.PBETValue;
  IbbElement->Flags = gMBiosContext.Flags;
  IbbElement->IBB_MCHBAR = gMBiosContext.IBB_MCHBAR;
  IbbElement->VTD_BAR = gMBiosContext.VTD_BAR;
  IbbElement->PMRL_Base = gMBiosContext.PMRL_Base;
  IbbElement->PMRL_Limit = gMBiosContext.PMRL_Limit;
  IbbElement->PMRH_Base = gMBiosContext.PMRH_Base;
  IbbElement->PMRH_Limit = gMBiosContext.PMRH_Limit;
#if 0
  // PostIbbHash is NOT used, just zero it.
  IbbElement->PostIbbHash.HashAlg = TPM_ALG_SHA256;
  IbbElement->PostIbbHash.Size = SHA256_DIGEST_SIZE;
  CreatePostIbbBiosHash (FdBuffer, FdSize, IbbElement->PostIbbHash.HashBuffer);
#endif
  IbbElement->EntryPoint = gMBiosContext.EntryPoint;

  //
  // IBB segments order needs to be put from low addresss to high
  //
  {
    UINTN                   SubIndex;
    FIT_TABLE_CONTEXT_ENTRY TempEntry;

    if (gFitTableContext.BiosModuleNumber > 1) {
      for (Index = 0; Index < (UINTN)gFitTableContext.BiosModuleNumber - 1; Index++){
        for (SubIndex = 0; SubIndex < gFitTableContext.BiosModuleNumber - Index - 1; SubIndex++) {
          if (gFitTableContext.BiosModule[SubIndex].Address > gFitTableContext.BiosModule[SubIndex + 1].Address) {
            CopyMem (&TempEntry, &gFitTableContext.BiosModule[SubIndex], sizeof(FIT_TABLE_CONTEXT_ENTRY));
            CopyMem (&gFitTableContext.BiosModule[SubIndex], &gFitTableContext.BiosModule[SubIndex + 1], sizeof(FIT_TABLE_CONTEXT_ENTRY));
            CopyMem (&gFitTableContext.BiosModule[SubIndex + 1], &TempEntry, sizeof(FIT_TABLE_CONTEXT_ENTRY));
          }
        }
      }
    }
    if (gFitTableContext.NonIbbBiosModuleNumber > 1) {
      for (Index = 0; Index < (UINTN)gFitTableContext.NonIbbBiosModuleNumber - 1; Index++){
        for (SubIndex = 0; SubIndex < gFitTableContext.NonIbbBiosModuleNumber - Index - 1; SubIndex++) {
          if (gFitTableContext.NonIbbBiosModule[SubIndex].Address > gFitTableContext.NonIbbBiosModule[SubIndex + 1].Address) {
            CopyMem (&TempEntry, &gFitTableContext.NonIbbBiosModule[SubIndex], sizeof(FIT_TABLE_CONTEXT_ENTRY));
            CopyMem (&gFitTableContext.NonIbbBiosModule[SubIndex], &gFitTableContext.NonIbbBiosModule[SubIndex + 1], sizeof(FIT_TABLE_CONTEXT_ENTRY));
            CopyMem (&gFitTableContext.NonIbbBiosModule[SubIndex + 1], &TempEntry, sizeof(FIT_TABLE_CONTEXT_ENTRY));
          }
        }
      }
    }
  }
  IbbElement->Digest.HashAlg = TPM_ALG_SHA256;
  IbbElement->Digest.Size = SHA256_DIGEST_SIZE;
  CreateBiosHash (FdBuffer, FdSize, IbbElement->Digest.HashBuffer);
  IbbElement->SegmentCount = gMBiosContext.SegmentCount;
  BiosModuleIndex = 0;
  NonIbbBiosModuleIndex = 0;
  for (Index = 0; Index < IbbElement->SegmentCount; Index++) {
    if (BiosModuleIndex >= gFitTableContext.BiosModuleNumber) {
      IbbElement->IBBSegment[Index].Flags = IBB_SEGMENT_FLAG_NON_IBB;
      IbbElement->IBBSegment[Index].Base = gFitTableContext.NonIbbBiosModule[NonIbbBiosModuleIndex].Address;
      IbbElement->IBBSegment[Index].Size = gFitTableContext.NonIbbBiosModule[NonIbbBiosModuleIndex].Size;
      NonIbbBiosModuleIndex ++;
      continue;
    }
    if (NonIbbBiosModuleIndex >= gFitTableContext.NonIbbBiosModuleNumber) {
      IbbElement->IBBSegment[Index].Flags = IBB_SEGMENT_FLAG_IBB;
      IbbElement->IBBSegment[Index].Base = gFitTableContext.BiosModule[BiosModuleIndex].Address;
      IbbElement->IBBSegment[Index].Size = gFitTableContext.BiosModule[BiosModuleIndex].Size;
      BiosModuleIndex ++;
      continue;
    }

    if (gFitTableContext.BiosModule[BiosModuleIndex].Address < gFitTableContext.NonIbbBiosModule[NonIbbBiosModuleIndex].Address) {
      IbbElement->IBBSegment[Index].Flags = IBB_SEGMENT_FLAG_IBB;
      IbbElement->IBBSegment[Index].Base = gFitTableContext.BiosModule[BiosModuleIndex].Address;
      IbbElement->IBBSegment[Index].Size = gFitTableContext.BiosModule[BiosModuleIndex].Size;
      BiosModuleIndex ++;
    } else {
      IbbElement->IBBSegment[Index].Flags = IBB_SEGMENT_FLAG_NON_IBB;
      IbbElement->IBBSegment[Index].Base = gFitTableContext.NonIbbBiosModule[NonIbbBiosModuleIndex].Address;
      IbbElement->IBBSegment[Index].Size = gFitTableContext.NonIbbBiosModule[NonIbbBiosModuleIndex].Size;
      NonIbbBiosModuleIndex ++;
    }
  }
  TempBuf += sizeof(IBB_ELEMENT) + sizeof(IBB_SEGMENT_ELEMENT) * (gMBiosContext.SegmentCount - 1);

  // PLATFORM_MANUFACTURER_ELEMENT
  for (Index = 0; Index < gMBiosContext.PlatformDataCount; Index++) {
    PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)TempBuf;
    *(UINT64 *)PmElement->StructureID = BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID;
    PmElement->StructVersion = BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_VERSION;
    PmElement->PMDataSize = (UINT16)gMBiosContext.PlatformDataSize[Index];
    CopyMem (PmElement + 1, gMBiosContext.PlatformData[Index], gMBiosContext.PlatformDataSize[Index]);
    TempBuf += sizeof(PLATFORM_MANUFACTURER_ELEMENT) + gMBiosContext.PlatformDataSize[Index];
  }

  // BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT
  BpmSignatureElement = (BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT *)TempBuf;
  *(UINT64 *)BpmSignatureElement->StructureID = BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_STRUCTURE_ID;
  BpmSignatureElement->StructVersion = BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_VERSION;
  BpmSignatureElement->KeySignature.Version = KEY_SIGNATURE_STRUCT_VERSION;
  BpmSignatureElement->KeySignature.KeyAlg = ALG_RSA;
  BpmSignatureElement->KeySignature.Key.Version = RSA_PUBLIC_KEY_STRUCT_VERSION;
  BpmSignatureElement->KeySignature.Key.KeySize = RSA_PUBLIC_KEY_STRUCT_KEY_SIZE_DEFAULT;
//BpmSignatureElement->KeySignature.Key.Exponent; //later
//BpmSignatureElement->KeySignature.Key.Modulus; // later
  BpmSignatureElement->KeySignature.SigScheme = ALG_RSASSA;
  BpmSignatureElement->KeySignature.Signature.Version = RSASSA_SIGNATURE_STRUCT_VERSION;
  BpmSignatureElement->KeySignature.Signature.KeySize = RSASSA_SIGNATURE_STRUCT_KEY_SIZE_DEFAULT;
  BpmSignatureElement->KeySignature.Signature.HashAlg = TPM_ALG_SHA256;
//BpmSignatureElement->KeySignature.Signature.Signature; // later

  if (gMBiosContext.ExternalBatchName != NULL) {
    //
    // Sign binary with external batch file
    //
    Status = PrepareSignatureForExternalBatch (gMBiosContext.DataFileName, gMBiosContext.BootPolicyManifest, (UINTN)BpmSignatureElement - (UINTN)gMBiosContext.BootPolicyManifest);
    if (Status != STATUS_SUCCESS) {
      Error (NULL, 0, 0, "PrepareSignatureForExternalBatch error", NULL);
      return STATUS_ERROR;
    }
    Status = InvokeExternalBatch (gMBiosContext.ExternalBatchName);
    if (Status != STATUS_SUCCESS) {
      Error (NULL, 0, 0, "InvokeExternalBatch error", NULL);
      return STATUS_ERROR;
    }
    Status = CreateSignatureFromExternalBatch (gMBiosContext.SignatureFileName, gMBiosContext.BootPolicySign, RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT * 2 + RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE);
    if (Status != STATUS_SUCCESS) {
      Error (NULL, 0, 0, "CreateSignatureFromExternalBatch error", NULL);
      return STATUS_ERROR;
    }
  } else {
    Status = PrepareSignature (gMBiosContext.PubKeyName, gMBiosContext.BootPolicySign, gMBiosContext.BootPolicySign + RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT);
    if (Status != STATUS_SUCCESS) {
      Error (NULL, 0, 0, "PrepareSignature error", NULL);
      return STATUS_ERROR;
    }
    Status = CreateSignature (gMBiosContext.PrivKeyName, gMBiosContext.BootPolicySign + RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT + RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE, gMBiosContext.BootPolicyManifest, (UINTN)BpmSignatureElement - (UINTN)gMBiosContext.BootPolicyManifest);
    if (Status != STATUS_SUCCESS) {
      Error (NULL, 0, 0, "CreateSignature error", NULL);
      return STATUS_ERROR;
    }
  }

  CopyMem (BpmSignatureElement->KeySignature.Key.Modulus, gMBiosContext.BootPolicySign, RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT);
  CopyMem (&BpmSignatureElement->KeySignature.Key.Exponent, gMBiosContext.BootPolicySign + RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT, RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE);
  CopyMem (BpmSignatureElement->KeySignature.Signature.Signature, gMBiosContext.BootPolicySign + RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT + RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE, RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT);

  if (gMBiosContext.BPKeyCount > 0) {
    // Create KeyManifest
    gMBiosContext.KeyManifestSize = sizeof(KEY_MANIFEST_STRAUCTURE) +
                                    sizeof(HASH_STRUCTURE) * (gMBiosContext.BPKeyCount - 1);
    gMBiosContext.KeyManifest = malloc (gMBiosContext.KeyManifestSize);
    TempBuf = gMBiosContext.KeyManifest;
    if (NULL == TempBuf) {
      Error (NULL, 0, 0, "No sufficient memory to allocate!", NULL);
      return STATUS_ERROR;
    }
    ZeroMem (TempBuf, gMBiosContext.KeyManifestSize);

    // KEY_MANIFEST_STRAUCTURE
    KeyManifest = (KEY_MANIFEST_STRAUCTURE *)TempBuf;
    *(UINT64 *)KeyManifest->StructureID = KEY_MANIFEST_STRUCTURE_ID;
    KeyManifest->StructVersion = KEY_MANIFEST_VERSION;
    KeyManifest->KeyManifestVersion = gMBiosContext.KeyManifestVersion;
    KeyManifest->KMSVN = gMBiosContext.KeyManifestRevocation;
    KeyManifest->KeyManifestID = gMBiosContext.KeyManifestID;

    KeyManifest->BPKey.HashAlg = TPM_ALG_SHA256;
    KeyManifest->BPKey.Size = SHA256_DIGEST_SIZE;
    // Only support one BPKeyFile
    if (gMBiosContext.BPKeyFile[0] != NULL) {
      CreateBootPolicyKeyHash (gMBiosContext.BPKeyFile[0], KeyManifest->BPKey.HashBuffer, FALSE);
    } else {
      CreateBootPolicyKeyHash (gMBiosContext.BPKeyFileBin[0], KeyManifest->BPKey.HashBuffer, TRUE);
    }

    KeyManifestSignature = &KeyManifest->KeyManifestSignature;
    KeyManifestSignature->Version = KEY_SIGNATURE_STRUCT_VERSION;
    KeyManifestSignature->KeyAlg = ALG_RSA;
    KeyManifestSignature->Key.Version = RSA_PUBLIC_KEY_STRUCT_VERSION;
    KeyManifestSignature->Key.KeySize = RSA_PUBLIC_KEY_STRUCT_KEY_SIZE_DEFAULT;
  //KeyManifestSignature->Key.Exponent; // later
  //KeyManifestSignature->Key.Modulus; // later
    KeyManifestSignature->SigScheme = ALG_RSASSA;
    KeyManifestSignature->Signature.Version = RSASSA_SIGNATURE_STRUCT_VERSION;
    KeyManifestSignature->Signature.KeySize = RSASSA_SIGNATURE_STRUCT_KEY_SIZE_DEFAULT;
    KeyManifestSignature->Signature.HashAlg = TPM_ALG_SHA256;
  //KeyManifestSignature->Signature.Signature; // later

    if (gMBiosContext.KeyExternalBatchName != NULL) {
      //
      // Sign binary with external batch file
      //
      Status = PrepareSignatureForExternalBatch (gMBiosContext.KeyDataFileName, gMBiosContext.KeyManifest, (UINTN)KeyManifestSignature - (UINTN)gMBiosContext.KeyManifest);
      if (Status != STATUS_SUCCESS) {
        Error (NULL, 0, 0, "PrepareSignatureForExternalBatch error", NULL);
        return STATUS_ERROR;
      }
      Status = InvokeExternalBatch (gMBiosContext.KeyExternalBatchName);
      if (Status != STATUS_SUCCESS) {
        Error (NULL, 0, 0, "InvokeExternalBatch error", NULL);
        return STATUS_ERROR;
      }
      Status = CreateSignatureFromExternalBatch (gMBiosContext.KeySignatureFileName, gMBiosContext.KeySign, RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT * 2 + RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE);
      if (Status != STATUS_SUCCESS) {
        Error (NULL, 0, 0, "CreateSignatureFromExternalBatch error", NULL);
        return STATUS_ERROR;
      }
    } else {
      Status = PrepareSignature (gMBiosContext.KeyPubKeyName, gMBiosContext.KeySign, gMBiosContext.KeySign + RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT);
      if (Status != STATUS_SUCCESS) {
        Error (NULL, 0, 0, "PrepareSignature error", NULL);
        return STATUS_ERROR;
      }
      Status = CreateSignature (gMBiosContext.KeyPrivKeyName, gMBiosContext.KeySign + RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT + RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE, gMBiosContext.KeyManifest, (UINTN)KeyManifestSignature - (UINTN)gMBiosContext.KeyManifest);
      if (Status != STATUS_SUCCESS) {
        Error (NULL, 0, 0, "CreateSignature error", NULL);
        return STATUS_ERROR;
      }
    }

    CopyMem (KeyManifestSignature->Key.Modulus, gMBiosContext.KeySign, RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT);
    CopyMem (&KeyManifestSignature->Key.Exponent, gMBiosContext.KeySign + RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT, RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE);
    CopyMem (KeyManifestSignature->Signature.Signature, gMBiosContext.KeySign + RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT + RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_MAX_SIZE, RSASSA_SIGNATURE_STRUCT_KEY_LEN_DEFAULT);
  }

  if (gMBiosContext.BDASEntryCount > 0) {
    // Create BiosDataArea
    gMBiosContext.BiosDataAreaSize = sizeof(BIOS_DATA_AREA_STRAUCTURE) +
                                    sizeof(BDAS_DATA_ENTRY) * (gMBiosContext.BDASEntryCount);
    gMBiosContext.BiosDataArea = malloc (gMBiosContext.BiosDataAreaSize);
    if (NULL == gMBiosContext.BiosDataArea) {
      Error (NULL, 0, 0, "No sufficient memory to allocate!", NULL);
      return STATUS_ERROR;
    }
    ZeroMem (gMBiosContext.BiosDataArea, gMBiosContext.BiosDataAreaSize);

    // BIOS_DATA_AREA_STRAUCTURE
    BiosDataArea = (BIOS_DATA_AREA_STRAUCTURE *)gMBiosContext.BiosDataArea;
    *(UINT64 *)BiosDataArea->StructureID = BIOS_DATA_AREA_STRUCTURE_ID;
    BiosDataArea->StructVersion = BIOS_DATA_AREA_VERSION;
    BiosDataArea->BDAS_DataEntryCount = gMBiosContext.BDASEntryCount + 1;
    BiosDataArea->BDAS_DataEntry[0].Enumeration = BDAS_DATA_ENTRY_TYPE_RESERVED;
    BiosDataArea->BDAS_DataEntry[0].Data = 0;
    if (gMBiosContext.TpmDeactivated != 0xFF) {
      BiosDataArea->BDAS_DataEntry[1].Enumeration = BDAS_DATA_ENTRY_TYPE_TPM_ACTIVATION_STATUS;
      BiosDataArea->BDAS_DataEntry[1].Data = gMBiosContext.TpmDeactivated;
    }
  }

  return STATUS_SUCCESS;
}

UINT8 *
FindNextFvHeader (
  IN UINT8 *FileBuffer,
  IN UINTN  FileLength
  )
/*++

  Routine Description:
    Find next FvHeader in the FileBuffer

  Parameters:
    FileBuffer        -   The start FileBuffer which needs to be searched
    FileLength        -   The whole File Length.
  Return:
    FvHeader          -   The FvHeader is found successfully.
    NULL              -   The FvHeader is not found.

--*/
{
  UINT8                       *FileHeader;
  EFI_FIRMWARE_VOLUME_HEADER  *FvHeader;
  UINT16                      FileChecksum;

  FileHeader = FileBuffer;
  for (; (UINTN)FileBuffer < (UINTN)FileHeader + FileLength; FileBuffer += 8) {
    FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)FileBuffer;
    if (FvHeader->Signature == EFI_FVH_SIGNATURE) {
      //
      // potential candidate
      //

      //
      // Check checksum
      //
      if (FvHeader->FvLength > FileLength) {
        continue;
      }
      if (FvHeader->HeaderLength >= FileLength) {
        continue;
      }
      FileChecksum = CalculateChecksum16 ((UINT16 *)FileBuffer, FvHeader->HeaderLength / sizeof (UINT16));
      if (FileChecksum != 0) {
        continue;
      }

      //
      // Check revision and reserved field
      //
#if (PI_SPECIFICATION_VERSION < 0x00010000)
      if ((FvHeader->Revision == EFI_FVH_REVISION) &&
          (FvHeader->Reserved[0] == 0) &&
          (FvHeader->Reserved[1] == 0) &&
          (FvHeader->Reserved[2] == 0) ){
        return FileBuffer;
      }
#else
      if ((FvHeader->Revision == EFI_FVH_PI_REVISION) &&
          (FvHeader->Reserved[0] == 0) ){
        return FileBuffer;
      }
#endif
    }
  }

  return NULL;
}

UINT8  *
FindFileFromFvByGuid (
  IN UINT8     *FvBuffer,
  IN UINT32    FvSize,
  IN EFI_GUID  *Guid,
  OUT UINT32   *FileSize
  )
/*++

Routine Description:

  Find File with GUID in an FV

Arguments:

  FvBuffer       - FV binary buffer
  FvSize         - FV size
  Guid           - File GUID value to be searched
  FileSize       - Guid File size

Returns:

  FileLocation   - Guid File location.
  NULL           - Guid File is not found.

--*/
{
  EFI_FIRMWARE_VOLUME_HEADER  *FvHeader;
  EFI_FFS_FILE_HEADER         *FileHeader;
  UINT64                      FvLength;
  EFI_GUID                    *TempGuid;
  UINT8                       *FixPoint;
  UINT32                      Offset;
  UINT32                      FileLength;
  UINT32                      FileOccupiedSize;

  //
  // Find the FFS file
  //
  FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)FindNextFvHeader (FvBuffer, FvSize);
  if (NULL == FvHeader) {
    return NULL;
  }
  while (TRUE) {
    FvLength         = FvHeader->FvLength;

    //
    // Prepare to walk the FV image
    //
    InitializeFvLib (FvHeader, (UINT32)FvLength);

    FileHeader       = (EFI_FFS_FILE_HEADER *)((UINTN)FvHeader + FvHeader->HeaderLength);
    Offset           = (UINT32) (UINTN) FileHeader - (UINT32) (UINTN) FvHeader;

    while (Offset < FvLength) {
      TempGuid = (EFI_GUID *)&(FileHeader->Name);
      FileLength = (*(UINT32 *)(FileHeader->Size)) & 0x00FFFFFF;
      FileOccupiedSize = GETOCCUPIEDSIZE(FileLength, 8);
      if ((CompareGuid (TempGuid, Guid)) == 0) {
        //
        // Good! Find it.
        //
        FixPoint = ((UINT8 *)FileHeader + sizeof(EFI_FFS_FILE_HEADER));
        //
        // Find the position of file module, the offset
        // between the position and the end of Fvrecovery.fv file
        // should not exceed 128kB to prevent reset vector from
        // outside legacy E and F segment
        //
        if ((UINTN)FvHeader + FvLength - (UINTN)FixPoint > 0x20000) {
  //        printf ("WARNING: The position of file module is not in E and F segment!\n");
  //        return NULL;
        }
        *FileSize = FileLength - sizeof(EFI_FFS_FILE_HEADER);
  #if (PI_SPECIFICATION_VERSION < 0x00010000)
        if (FileHeader->Attributes & FFS_ATTRIB_TAIL_PRESENT) {
          *FileSize -= sizeof(EFI_FFS_FILE_TAIL);
        }
  #endif
        return FixPoint;
      }
      FileHeader = (EFI_FFS_FILE_HEADER *)((UINTN)FileHeader + FileOccupiedSize);
      Offset = (UINT32) (UINTN) FileHeader - (UINT32) (UINTN) FvHeader;
    }

    //
    // Not found, check next FV
    //
    if ((UINTN)FvBuffer + FvSize > (UINTN)FvHeader + FvLength) {
      FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)FindNextFvHeader ((UINT8 *)FvHeader + (UINTN)FvLength, (UINTN)FvBuffer + FvSize - ((UINTN)FvHeader + (UINTN)FvLength));
      if (FvHeader == NULL) {
        break;
      }
    } else {
      break;
    }
  }

  //
  // Not found
  //
  return NULL;
}

BOOLEAN
IsGuidData (
  IN CHAR8     *StringData,
  OUT EFI_GUID *Guid
  )
/*++

Routine Description:

  Check whether a string is a GUID

Arguments:

  StringData  - the String
  Guid        - Guid to hold the value

Returns:

  TRUE  - StringData is a GUID, and Guid field is filled.
  FALSE - StringData is not a GUID

--*/
{
  if (strlen (StringData) != strlen ("00000000-0000-0000-0000-000000000000")) {
    return FALSE;
  }
  if ((StringData[8] != '-') ||
      (StringData[13] != '-') ||
      (StringData[18] != '-') ||
      (StringData[23] != '-') ) {
    return FALSE;
  }

  StringToGuid (StringData, Guid);

  return TRUE;
}

STATUS
GenerateBpm (
  IN INTN      argc,
  IN CHAR8     **argv,
  IN UINT8     *FdBuffer,
  IN UINT32    FdSize
  )
/*++

Routine Description:

  Generate Bpm according to command line argument

Arguments:

  argc     - Number of command line parameters.
  argv     - Array of pointers to parameter strings.
  FdBuffer - BIOS buffer
  FdSize   - BIOS size

Returns:

  STATUS_SUCCESS

--*/
{
  INTN                    Index;
  STATUS                  Status;
  EFI_GUID                Guid;
  UINT8                   *FileBuffer;
  UINT32                  FileSize;
  BIOS_INFO_HEADER        *BiosInfo;
  BIOS_INFO_STRUCT        *BiosInfoStruct;
  UINTN                   BiosInfoIndex;

  Index = 3;
  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-F") == 0) ||
       (strcmp (argv[Index], "-f") == 0)) ) {
    Index += 2;
  }

  //
  // 0.5 BiosInfo
  //
  if ((Index + 1 >= argc) ||
      ((strcmp (argv[Index], "-I") != 0) &&
       (strcmp (argv[Index], "-i") != 0)) ) {
    //
    // Bypass
    //
  } else {
    //
    // Get offset from parameter
    //
    if (IsGuidData (argv[Index + 1], &Guid)) {
      FileBuffer = FindFileFromFvByGuid (FdBuffer, FdSize, &Guid, &FileSize);
      if (FileBuffer == NULL) {
        Error (NULL, 0, 0, "-I Parameter incorrect, GUID not found!", NULL);
        // not found
        return 0;
      }
      BiosInfo = (BIOS_INFO_HEADER *)FileBuffer;
      for (BiosInfoIndex = 0; BiosInfoIndex < FileSize; BiosInfoIndex++) {
        if (((BIOS_INFO_HEADER *)(FileBuffer + BiosInfoIndex))->Signature == BIOS_INFO_SIGNATURE) {
          BiosInfo = (BIOS_INFO_HEADER *)(FileBuffer + BiosInfoIndex);
        }
      }
      if (BiosInfo->Signature != BIOS_INFO_SIGNATURE) {
        Error (NULL, 0, 0, "-I Parameter incorrect, Signature Error!", NULL);
        // not found
        return 0;
      }
      BiosInfoStruct = (BIOS_INFO_STRUCT *)(BiosInfo + 1);
      for (BiosInfoIndex = 0; BiosInfoIndex < BiosInfo->EntryCount; BiosInfoIndex++) {
        switch (BiosInfoStruct[BiosInfoIndex].Type) {
        case FIT_TABLE_TYPE_BIOS_MODULE:
          if ((BiosInfoStruct[BiosInfoIndex].Attributes & BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_POST_IBB) != 0) {
            if (gFitTableContext.PostIbbBiosModuleNumber >= MAX_BIOS_MODULE_ENTRY) {
              Error (NULL, 0, 0, "-I Parameter incorrect, Too many Post IBB Bios Module!", NULL);
              return 0;
            }
            gFitTableContext.PostIbbBiosModule[gFitTableContext.PostIbbBiosModuleNumber].Type    = FIT_TABLE_TYPE_BIOS_MODULE;
            gFitTableContext.PostIbbBiosModule[gFitTableContext.PostIbbBiosModuleNumber].Address = (UINT32)BiosInfoStruct[BiosInfoIndex].Address;
            gFitTableContext.PostIbbBiosModule[gFitTableContext.PostIbbBiosModuleNumber].Size    = (UINT32)BiosInfoStruct[BiosInfoIndex].Size;
            gFitTableContext.PostIbbBiosModuleNumber ++;
          } else if ((BiosInfoStruct[BiosInfoIndex].Attributes & BIOS_INFO_STRUCT_ATTRIBUTE_BIOS_NON_IBB) != 0) {
            if (gFitTableContext.NonIbbBiosModuleNumber >= MAX_BIOS_MODULE_ENTRY) {
              Error (NULL, 0, 0, "-I Parameter incorrect, Too many Non IBB Bios Module!", NULL);
              return 0;
            }
            gFitTableContext.NonIbbBiosModule[gFitTableContext.NonIbbBiosModuleNumber].Type    = FIT_TABLE_TYPE_BIOS_MODULE;
            gFitTableContext.NonIbbBiosModule[gFitTableContext.NonIbbBiosModuleNumber].Address = (UINT32)BiosInfoStruct[BiosInfoIndex].Address;
            gFitTableContext.NonIbbBiosModule[gFitTableContext.NonIbbBiosModuleNumber].Size    = (UINT32)BiosInfoStruct[BiosInfoIndex].Size;
            gFitTableContext.NonIbbBiosModuleNumber ++;
          }
          break;
        default:
          break;
        }
      }
    } else {
      Error (NULL, 0, 0, "-I Parameter incorrect, expect GUID!", NULL);
      return 0;
    }
    Index += 2;
  }

  //
  // 1. Prepare manifest body
  //
  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-PV") == 0) ||
       (strcmp (argv[Index], "-pv") == 0)) ) {
    gMBiosContext.PMBPMVersion = (UINT8)xtoi (argv[Index + 1]);
    Index += 2;
  }

  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-BSVN") == 0) ||
       (strcmp (argv[Index], "-bsvn") == 0)) ) {
    gMBiosContext.BootPolicyRevocation = (UINT8)xtoi (argv[Index + 1]);
    Index += 2;
  }

  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-ASVN") == 0) ||
       (strcmp (argv[Index], "-asvn") == 0)) ) {
    gMBiosContext.AcmRecocation = (UINT8)xtoi (argv[Index + 1]);
    Index += 2;
  }

  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-NEM") == 0) ||
       (strcmp (argv[Index], "-nem") == 0)) ) {
    gMBiosContext.NEMDataStack = (UINT16)xtoi (argv[Index + 1]);
    Index += 2;
  }

  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-F") == 0) ||
       (strcmp (argv[Index], "-f") == 0)) ) {
    gMBiosContext.Flags = (UINT32)xtoi (argv[Index + 1]);
    Index += 2;
  }

  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-BAR") == 0) ||
       (strcmp (argv[Index], "-bar") == 0)) ) {
    gMBiosContext.IBB_MCHBAR = (UINT64)xtol (argv[Index + 1]);
    Index += 2;
  }

  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-VTDBAR") == 0) ||
       (strcmp (argv[Index], "-vtdbar") == 0)) ) {
    gMBiosContext.VTD_BAR = (UINT64)xtol (argv[Index + 1]);
    Index += 2;
  }

  if ((Index + 2 < argc) &&
      ((strcmp (argv[Index], "-PMRL") == 0) ||
       (strcmp (argv[Index], "-pmrl") == 0)) ) {
    gMBiosContext.PMRL_Base = (UINT32)xtoi (argv[Index + 1]);
    gMBiosContext.PMRL_Limit = (UINT32)xtoi (argv[Index + 2]);
    Index += 3;
  }

  if ((Index + 2 < argc) &&
      ((strcmp (argv[Index], "-PMRH") == 0) ||
       (strcmp (argv[Index], "-pmrh") == 0)) ) {
    gMBiosContext.PMRH_Base = (UINT64)xtol (argv[Index + 1]);
    gMBiosContext.PMRH_Limit = (UINT64)xtol (argv[Index + 2]);
    Index += 3;
  }

  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-PBET") == 0) ||
       (strcmp (argv[Index], "-pbet") == 0)) ) {
    gMBiosContext.PBETValue = (UINT8)xtoi (argv[Index + 1]);
    Index += 2;
  }

  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-EP") == 0) ||
       (strcmp (argv[Index], "-ep") == 0)) ) {
    gMBiosContext.EntryPoint = (UINT32)xtoi (argv[Index + 1]);
    if (gMBiosContext.EntryPoint < IBB_ENTRYPOINT_MIN) {
      Error (NULL, 0, 0, "-EP Parameter incorrect, must be within the top 64 bytes of the 4Gig!", "%s", argv[Index + 1]);
      return STATUS_ERROR;
    }
    Index += 2;
  }

  gMBiosContext.SegmentCount = (UINT8)(gFitTableContext.BiosModuleNumber + gFitTableContext.NonIbbBiosModuleNumber);

  //
  // Get PlatformDataFile
  //
  gMBiosContext.PlatformDataCount = 0;
  gMBiosContext.PlatformDataTotalSize = 0;
  while (TRUE) {
    if (Index + 1 >= argc) {
      break;
    }
    if ((strcmp (argv[Index], "-P") != 0) &&
        (strcmp (argv[Index], "-p") != 0) ) {
      break;
    }
    if (gMBiosContext.PlatformDataCount >= PLATFOMR_DATA_MAX_COUNT) {
      Error (NULL, 0, 0, "-P Parameter incorrect, Too many PlatformSpecificData!", NULL);
      return STATUS_ERROR;
    }
    Status = ReadInputFile (
               argv[Index + 1],
               (UINT8 **)&gMBiosContext.PlatformData[gMBiosContext.PlatformDataCount],
               &gMBiosContext.PlatformDataSize[gMBiosContext.PlatformDataCount],
               NULL
               );
    if (Status != STATUS_SUCCESS) {
      Error (NULL, 0, 0, "-P Parameter incorrect, Read File fail!", "%s", argv[Index + 1]);
      return STATUS_ERROR;
    }
    if ((gMBiosContext.PlatformDataSize[gMBiosContext.PlatformDataCount] & PLATFORM_DATA_ALIGNMENT) != 0) {
      Error (NULL, 0, 0, "-P Parameter incorrect, Must be in multiple of 4 bytes!", "%s", argv[Index + 1]);
      return STATUS_ERROR;
    }
    gMBiosContext.PlatformDataTotalSize += gMBiosContext.PlatformDataSize[gMBiosContext.PlatformDataCount];
    gMBiosContext.PlatformDataCount++;
    Index += 2;
  }

  //
  // 2. Prepare manifest sign
  //
  if ((Index + 2 < argc) &&
      ((strcmp (argv[Index], "-S") == 0) ||
       (strcmp (argv[Index], "-s") == 0)) ) {
    gMBiosContext.PrivKeyName = argv[Index + 1];
    gMBiosContext.PubKeyName  = argv[Index + 2];
    Index += 3;
  } else if ((Index + 3 < argc) &&
             ((strcmp (argv[Index], "-B") == 0) ||
             (strcmp (argv[Index], "-b") == 0)) ) {
    gMBiosContext.ExternalBatchName = argv[Index + 1];
    gMBiosContext.DataFileName = argv[Index + 2];
    gMBiosContext.SignatureFileName = argv[Index + 3];
    Index += 4;
  } else {
    Error (NULL, 0, 0, "Dot not know how to process Signing! Either -B or -S should be used.", NULL);
    return STATUS_ERROR;
  }

  //
  // 2.1 Get KeyManifest
  //
  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-KV") == 0) ||
       (strcmp (argv[Index], "-kv") == 0)) ) {
    gMBiosContext.KeyManifestVersion = (UINT8)xtoi (argv[Index + 1]);
    Index += 2;
  }

  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-KSVN") == 0) ||
       (strcmp (argv[Index], "-ksvn") == 0)) ) {
    gMBiosContext.KeyManifestRevocation = (UINT8)xtoi (argv[Index + 1]);
    Index += 2;
  }

  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-KID") == 0) ||
       (strcmp (argv[Index], "-kid") == 0)) ) {
    gMBiosContext.KeyManifestID = (UINT8)xtoi (argv[Index + 1]);
    Index += 2;
  }

  gMBiosContext.BPKeyCount = 0;
  while (TRUE) {
    UINT8  *TempData;
    UINT32 TempDataSize;
    if (Index + 1 >= argc) {
      break;
    }
    if ((strcmp (argv[Index], "-K") != 0) &&
        (strcmp (argv[Index], "-k") != 0) &&
        (strcmp (argv[Index], "-KB") != 0) &&
        (strcmp (argv[Index], "-kb") != 0) ) {
      break;
    }
    if (gMBiosContext.BPKeyCount >= BP_KEY_MAX_COUNT) {
      Error (NULL, 0, 0, "-K Parameter incorrect, Too many BPKeyData!", NULL);
      return STATUS_ERROR;
    }
    Status = ReadInputFile (
               argv[Index + 1],
               &TempData,
               &TempDataSize,
               NULL
               );
    if (Status != STATUS_SUCCESS) {
      Error (NULL, 0, 0, "-K Parameter incorrect, Read File fail!", "%s", argv[Index + 1]);
      return STATUS_ERROR;
    }
    free (TempData);
    if ((strcmp (argv[Index], "-K") == 0) ||
        (strcmp (argv[Index], "-k") == 0) ) {
      gMBiosContext.BPKeyFile[gMBiosContext.BPKeyCount] = argv[Index + 1];
    } else {
      gMBiosContext.BPKeyFileBin[gMBiosContext.BPKeyCount] = argv[Index + 1];
    }
    gMBiosContext.BPKeyCount++;
    Index += 2;
  }

  //
  // 2.1 Prepare KeyManifest sign
  //
  if ((Index + 2 < argc) &&
      ((strcmp (argv[Index], "-SK") == 0) ||
       (strcmp (argv[Index], "-sk") == 0)) ) {
    gMBiosContext.KeyPrivKeyName = argv[Index + 1];
    gMBiosContext.KeyPubKeyName  = argv[Index + 2];
    Index += 3;
  } else if ((Index + 3 < argc) &&
             ((strcmp (argv[Index], "-BK") == 0) ||
             (strcmp (argv[Index], "-bk") == 0)) ) {
    gMBiosContext.KeyExternalBatchName = argv[Index + 1];
    gMBiosContext.KeyDataFileName = argv[Index + 2];
    gMBiosContext.KeySignatureFileName = argv[Index + 3];
    Index += 4;
  } else {
    if (gMBiosContext.BPKeyCount > 0) {
      Error (NULL, 0, 0, "Dot not know how to process Signing! Either -BK or -SK should be used.", NULL);
      return STATUS_ERROR;
    }
  }

  //
  // 3. BiosDataArea
  //
  gMBiosContext.BDASEntryCount = 0;
  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-T") == 0) ||
       (strcmp (argv[Index], "-t") == 0)) ) {
    gMBiosContext.TpmDeactivated = (UINT8)xtoi (argv[Index + 1]);
    if (gMBiosContext.TpmDeactivated > 1) {
      Error (NULL, 0, 0, "TpmDeactivated invalid, only 0 or 1 should be used.", NULL);
      return STATUS_ERROR;
    }
    gMBiosContext.BDASEntryCount ++;
    Index += 2;
  } else {
    gMBiosContext.TpmDeactivated = 0xFF;
  }

  //
  // 4. Create policy
  //
  Status = CreateBpm (FdBuffer, FdSize);
  if (Status != STATUS_SUCCESS) {
    return STATUS_ERROR;
  }

  //
  // 5. Create output file
  //
  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-O") == 0) ||
       (strcmp (argv[Index], "-o") == 0)) ) {
    Status = WriteOutputFile (argv[Index + 1], gMBiosContext.BootPolicyManifest, gMBiosContext.BootPolicyManifestSize);
    Index += 2;
  }
  if ((Index + 1 < argc) &&
      ((strcmp (argv[Index], "-OY") == 0) ||
       (strcmp (argv[Index], "-oy") == 0)) ) {
    if (gMBiosContext.KeyManifest != NULL) {
      Status = WriteOutputFile (argv[Index + 1], gMBiosContext.KeyManifest, gMBiosContext.KeyManifestSize);
    }
    Index += 2;
  }
  return STATUS_SUCCESS;
}

STATUS
UpdateMBiosPolicy (
  IN UINT8     *FdBuffer,
  IN UINT32    FdSize
  )
/*++

Routine Description:

  Update generated PolicyData into BIOS according to FIT table

Arguments:

  FdBuffer - BIOS buffer
  FdSize   - BIOS size

Returns:

  STATUS_SUCCESS

--*/
{
  FIT_TABLE_CONTEXT_ENTRY          *BiosPolicyRecord;
  UINT8                            *PolicyData;
  FIRMWARE_INTERFACE_TABLE_ENTRY   *FitEntry;
  UINT32                           FitEntryNumber;
  UINT8                            Checksum;

  //
  // 1. Update Bpm
  //
  BiosPolicyRecord = GetFitEntry (FIT_TABLE_TYPE_BOOT_POLICY_MANIFEST);
  if (BiosPolicyRecord == NULL) {
    printf ("No Bpm Policy Found in FIT\n");
    return STATUS_SUCCESS;
  }

  if (BiosPolicyRecord->Size < gMBiosContext.BootPolicyManifestSize) {
    Error (NULL, 0, 0, "No enough space for Bpm", NULL);
    return STATUS_ERROR;
  }

  PolicyData = FLASH_TO_MEMORY (BiosPolicyRecord->Address, FdBuffer, FdSize);
  CopyMem (PolicyData, gMBiosContext.BootPolicyManifest, gMBiosContext.BootPolicyManifestSize);

  //
  // 1.1 Fix Size field, required by AnC spec
  //
  FitEntry = GetFitEntryFromFd (FIT_TABLE_TYPE_BOOT_POLICY_MANIFEST, FdBuffer, FdSize);
  if (FitEntry == NULL) {
    Error (NULL, 0, 0, "BPM not found in FIT", NULL);
    return STATUS_ERROR;
  }
  *(UINT32 *)&FitEntry->Size = gMBiosContext.BootPolicyManifestSize;

  //
  // 2. Update KeyManifest
  //
  if (gMBiosContext.KeyManifest != NULL) {
    BiosPolicyRecord = GetFitEntry (FIT_TABLE_TYPE_KEY_MANIFEST);
    if (BiosPolicyRecord == NULL) {
      printf ("No KeyManifest Found in FIT\n");
      return STATUS_SUCCESS;
    }

    if (BiosPolicyRecord->Size < gMBiosContext.KeyManifestSize) {
      Error (NULL, 0, 0, "No enough space for KeyManifest", NULL);
      return STATUS_ERROR;
    }

    PolicyData = FLASH_TO_MEMORY (BiosPolicyRecord->Address, FdBuffer, FdSize);
    CopyMem (PolicyData, gMBiosContext.KeyManifest, gMBiosContext.KeyManifestSize);

    //
    // 2.1 Fix Size field, required by AnC spec
    //
    FitEntry = GetFitEntryFromFd (FIT_TABLE_TYPE_KEY_MANIFEST, FdBuffer, FdSize);
    if (FitEntry == NULL) {
      Error (NULL, 0, 0, "KM not found in FIT", NULL);
      return STATUS_ERROR;
    }
    *(UINT32 *)&FitEntry->Size = gMBiosContext.KeyManifestSize;
  }

  //
  // 3. Update BiosDataArea
  //
  if (gMBiosContext.BiosDataArea != NULL) {
    BiosPolicyRecord = GetFitEntry (FIT_TABLE_TYPE_BIOS_DATA_AREA);
    if (BiosPolicyRecord == NULL) {
      printf ("No BiosDataArea Found in FIT\n");
      return STATUS_SUCCESS;
    }

    if (BiosPolicyRecord->Size < gMBiosContext.BiosDataAreaSize) {
      Error (NULL, 0, 0, "No enough space for BiosDataArea", NULL);
      return STATUS_ERROR;
    }

    PolicyData = FLASH_TO_MEMORY (BiosPolicyRecord->Address, FdBuffer, FdSize);
    CopyMem (PolicyData, gMBiosContext.BiosDataArea, gMBiosContext.BiosDataAreaSize);

    //
    // 3.1 Fix Size field, required by AnC spec
    //
    FitEntry = GetFitEntryFromFd (FIT_TABLE_TYPE_BIOS_DATA_AREA, FdBuffer, FdSize);
    if (FitEntry == NULL) {
      Error (NULL, 0, 0, "BDAS not found in FIT", NULL);
      return STATUS_ERROR;
    }
    *(UINT32 *)&FitEntry->Size = gMBiosContext.BiosDataAreaSize;
  }

  //
  // 4. Need fix checksum, because we may update Size field.
  //
  FitEntry = GetFitEntryFromFd (FIT_TABLE_TYPE_HEADER, FdBuffer, FdSize);
  if (FitEntry == NULL) {
    Error (NULL, 0, 0, "FIT Header not found in FIT", NULL);
    return STATUS_ERROR;
  }
  FitEntryNumber = *(UINT32 *)&FitEntry->Size & 0xFFFFFF;

  FitEntry->Checksum = 0;
  Checksum = CalculateChecksum8 ((UINT8 *)FitEntry, sizeof (FIRMWARE_INTERFACE_TABLE_ENTRY) * FitEntryNumber);
  FitEntry->Checksum = Checksum;

  return STATUS_SUCCESS;
}

VOID
FreeMBios (
  VOID
  )
/*++

Routine Description:

  Free global context

Arguments:

  None

Returns:

  None

--*/
{
  UINTN  Index;

  if (gMBiosContext.BootPolicyManifest != NULL) {
    free (gMBiosContext.BootPolicyManifest);
  }
  if (gMBiosContext.KeyManifest != NULL) {
    free (gMBiosContext.KeyManifest);
  }
  if (gMBiosContext.BiosDataArea != NULL) {
    free (gMBiosContext.BiosDataArea);
  }
  for (Index = 0; Index < gMBiosContext.PlatformDataCount; Index++) {
    if (gMBiosContext.PlatformData[Index] != NULL) {
      free (gMBiosContext.PlatformData[Index]);
    }
  }
}

/**

  This function compare memory content.

  @param DestinationBuffer  destination buffer
  @param SourceBuffer       source buffer
  @param Length             length

  @retval 0  the destination and source buffer are same
  @return the first differnce of destination and source buffer

**/
INTN
CompareMem (
  IN      CONST VOID                *DestinationBuffer,
  IN      CONST VOID                *SourceBuffer,
  IN      UINTN                     Length
  )
{
  while ((--Length != 0) &&
         (*(INT8*)DestinationBuffer == *(INT8*)SourceBuffer)) {
    DestinationBuffer = (INT8*)DestinationBuffer + 1;
    SourceBuffer = (INT8*)SourceBuffer + 1;
  }
  return (INTN)*(UINT8*)DestinationBuffer - (INTN)*(UINT8*)SourceBuffer;
}

STATUS
VerifyBpm (
  IN UINT8     *FdBuffer,
  IN UINT32    FdSize
  )
{
  STATUS                                  RetStatus;
  UINT8                                   *BpmBody;
  UINT8                                   *TempBuf;
  IBB_ELEMENT                             *IbbElement;
  PLATFORM_MANUFACTURER_ELEMENT           *PmElement;
  BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT  *BpmSignatureElement;
  FIRMWARE_INTERFACE_TABLE_ENTRY          *BiosPolicyRecord;
  UINT8                                   BiosHash[SHA256_DIGEST_SIZE];
  UINT8                                   ManifestPubKey[RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT];
  UINT8                                   ManifestSign[RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT];
  UINT32                                  ManifestPubKeyExponent;
  UINT8                                   OutBuffer[2048];
  RSA                                     *Rsa;
  INTN                                    Length;

  //
  // 0. Get BPM Policy
  //
  BiosPolicyRecord = GetFitEntryFromFd (FIT_TABLE_TYPE_BOOT_POLICY_MANIFEST, FdBuffer, FdSize);
  if (BiosPolicyRecord == NULL) {
    return STATUS_SUCCESS;
  }

  BpmBody = (UINT8 *)(UINTN)FLASH_TO_MEMORY (BiosPolicyRecord->Address, FdBuffer, FdSize);
  TempBuf = BpmBody;
  RetStatus = STATUS_SUCCESS;

  printf ("Start BpmVerification...\n");

  //
  // 1. Check BIOS Hash
  //
  TempBuf += sizeof(BOOT_POLICY_MANIFEST_HEADER);

  IbbElement = (IBB_ELEMENT *)TempBuf;
  {
    EVP_MD_CTX   ctx;
    const EVP_MD *md;
    UINTN        Index;

    md = EVP_sha256();
    EVP_DigestInit(&ctx, md);

    for (Index = 0; Index < IbbElement->SegmentCount; Index++) {
      if ((IbbElement->IBBSegment[Index].Flags & IBB_SEGMENT_FLAG_NON_IBB) == 0) {
        EVP_DigestUpdate(
            &ctx,
            FLASH_TO_MEMORY (IbbElement->IBBSegment[Index].Base, FdBuffer, FdSize),
            (UINTN)(UINT32)IbbElement->IBBSegment[Index].Size
            );
      }
    }

    EVP_DigestFinal(&ctx, (UINT8 *)BiosHash, NULL);
  }
  if (CompareMem (BiosHash, IbbElement->Digest.HashBuffer, sizeof(BiosHash)) != 0) {
    printf ("FAIL: BIOS Module Digest Verification\n");
    RetStatus = STATUS_ERROR;
  } else {
    printf ("PASS: BIOS Module Digest Verification\n");
  }
  TempBuf += sizeof(IBB_ELEMENT) + sizeof(IBB_SEGMENT_ELEMENT) * (IbbElement->SegmentCount - 1);

  PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)TempBuf;
  while (*(UINT64 *)PmElement->StructureID == BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID) {
    PrintPlatformManufacturerElement (PmElement);
    TempBuf += sizeof(PLATFORM_MANUFACTURER_ELEMENT) + PmElement->PMDataSize;
    PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)TempBuf;
  }

  //
  // 2. Check Signature
  //
  BpmSignatureElement = (BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT *)TempBuf;
  CopyMem (&ManifestPubKey, BpmSignatureElement->KeySignature.Key.Modulus, sizeof(ManifestPubKey));
  ManifestPubKeyExponent = BpmSignatureElement->KeySignature.Key.Exponent;
  CopyMem (&ManifestSign, BpmSignatureElement->KeySignature.Signature.Signature, sizeof(ManifestSign));
  SwapEndian (ManifestPubKey, sizeof(ManifestPubKey));
  SwapEndian ((UINT8 *)&ManifestPubKeyExponent, sizeof(ManifestPubKeyExponent));
//  SwapEndian (ManifestSign, sizeof(ManifestSign));

  //
  // Calculate hash
  //
  CreateHash (
    (UINT8 *)BpmBody,
    (UINTN)BpmSignatureElement - (UINTN)BpmBody,
    BiosHash
    );

  //
  // Verification
  //

  //
  // Generate & Initialize RSA Context.
  //

  //
  // Allocates & Initializes RSA Context by OpenSSL RSA_new()
  //
  Rsa = RSA_new ();
  if (Rsa == NULL) {
    printf ("Rsa == NULL\n");
    return STATUS_ERROR;
  }

  //
  // Set RSA Key Components.
  // NOTE: Only N and E are needed to be set as RSA public key for signature verification.
  //

  //
  // RSA Public Modulus (N)
  //
  if (Rsa->n != NULL) {
    BN_free (Rsa->n);
  }
  Rsa->n = BN_bin2bn (ManifestPubKey, sizeof(ManifestPubKey), Rsa->n);

  //
  // RSA Public Exponent (e)
  //
  if (Rsa->e != NULL) {
    BN_free (Rsa->e);
  }
  Rsa->e = BN_bin2bn ((UINT8 *)&ManifestPubKeyExponent, sizeof(ManifestPubKeyExponent), Rsa->e);

  //
  // Verify the signature.
  //

  //
  // RSA PKCS#1 Signature Decoding using OpenSSL RSA Decryption with Public Key
  //
  Length = RSA_public_decrypt (
             sizeof(ManifestSign),
             ManifestSign,
             OutBuffer,
             Rsa,
             RSA_PKCS1_PADDING
             );
  //
  // Invalid RSA Key or PKCS#1 Padding Checking Failed (if Length < 0)
  // NOTE: Length should be the addition of HashLength and some DER value.
  //       Ignore more strict length checking here.
  //
  if (Length < SHA256_DIGEST_SIZE) {
    RetStatus = STATUS_ERROR;
    printf ("FAIL: Manifest Signature length\n");
    goto Done;
  }

  //
  // Validate the MessageHash and Decoded Signature
  // NOTE: The decoded Signature should be the DER encoding of the DigestInfo value
  //       DigestInfo ::= SEQUENCE {
  //           digestAlgorithm AlgorithmIdentifier
  //           digest OCTET STRING
  //       }
  //       Then Memory Comparing should skip the DER value of the underlying SEQUENCE
  //       type and AlgorithmIdentifier.
  //
  if (CompareMem (BiosHash, OutBuffer + Length - SHA256_DIGEST_SIZE, SHA256_DIGEST_SIZE) == 0) {
    //
    // Valid RSA PKCS#1 Signature
    //
    printf ("PASS: Manifest Signature Verification\n");
    // Use last status
  } else {
    //
    // Failed to verification
    //
    printf ("FAIL: Manifest Signature Verification\n");
    RetStatus = STATUS_ERROR;
  }

Done:
  if (Rsa != NULL) {
    //
    // Free OpenSSL RSA Context
    //
    RSA_free (Rsa);
  }

  return RetStatus;
}

STATUS
VerifyKeyManifest (
  IN UINT8     *FdBuffer,
  IN UINT32    FdSize
  )
{
  STATUS                                  RetStatus;
  UINT8                                   *BpmBody;
  UINT8                                   *TempBuf;
  IBB_ELEMENT                             *IbbElement;
  PLATFORM_MANUFACTURER_ELEMENT           *PmElement;
  BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT  *BpmSignatureElement;
  FIRMWARE_INTERFACE_TABLE_ENTRY          *BiosPolicyRecord;
  FIRMWARE_INTERFACE_TABLE_ENTRY          *KeyManifestRecord;
  KEY_MANIFEST_STRAUCTURE                 *KeyManifest;
  KEY_SIGNATURE_STRUCT                    *KeyManifestSignature;
  UINT8                                   KeyHash[SHA256_DIGEST_SIZE];
  UINT8                                   ManifestPubKey[RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT];
  UINT8                                   ManifestSign[RSA_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT];
  UINT32                                  ManifestPubKeyExponent;
  UINT8                                   OutBuffer[2048];
  RSA                                     *Rsa;
  INTN                                    Length;

  //
  // 0. Get KeyManifest Policy
  //
  BiosPolicyRecord = GetFitEntryFromFd (FIT_TABLE_TYPE_BOOT_POLICY_MANIFEST, FdBuffer, FdSize);
  if (BiosPolicyRecord == NULL) {
    return STATUS_SUCCESS;
  }
  KeyManifestRecord = GetFitEntryFromFd (FIT_TABLE_TYPE_KEY_MANIFEST, FdBuffer, FdSize);
  if (KeyManifestRecord == NULL) {
    return STATUS_SUCCESS;
  }

  printf ("Start KeyManifestVerification...\n");

  //
  // 1. Check BPKey Hash
  //
  KeyManifest = (KEY_MANIFEST_STRAUCTURE *)(UINTN)FLASH_TO_MEMORY (KeyManifestRecord->Address, FdBuffer, FdSize);

  BpmBody = (UINT8 *)(UINTN)FLASH_TO_MEMORY (BiosPolicyRecord->Address, FdBuffer, FdSize);
  TempBuf = BpmBody;
  RetStatus = STATUS_SUCCESS;

  TempBuf += sizeof(BOOT_POLICY_MANIFEST_HEADER);

  IbbElement = (IBB_ELEMENT *)TempBuf;
  TempBuf += sizeof(IBB_ELEMENT) + sizeof(IBB_SEGMENT_ELEMENT) * (IbbElement->SegmentCount - 1);

  PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)TempBuf;
  while (*(UINT64 *)PmElement->StructureID == BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID) {
    PrintPlatformManufacturerElement (PmElement);
    TempBuf += sizeof(PLATFORM_MANUFACTURER_ELEMENT) + PmElement->PMDataSize;
    PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)TempBuf;
  }

  BpmSignatureElement = (BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT *)TempBuf;
  CopyMem (&ManifestPubKey, BpmSignatureElement->KeySignature.Key.Modulus, sizeof(ManifestPubKey));

  //
  // Calculate hash
  //
  CreateHash (
    (UINT8 *)BpmSignatureElement->KeySignature.Key.Modulus,
    sizeof(BpmSignatureElement->KeySignature.Key.Modulus),
    KeyHash
    );

  //
  // Verify BP KeyHash
  //
  if (CompareMem (KeyHash, KeyManifest->BPKey.HashBuffer, sizeof(KeyHash)) != 0) {
    printf ("FAIL: BPKey Digest Verification\n");
    RetStatus = STATUS_ERROR;
  } else {
    printf ("PASS: BPKey Digest Verification\n");
  }

  //
  // 2. Check Signature
  //
  KeyManifestSignature = &KeyManifest->KeyManifestSignature;
  CopyMem (&ManifestPubKey, KeyManifestSignature->Key.Modulus, sizeof(ManifestPubKey));
  ManifestPubKeyExponent = KeyManifestSignature->Key.Exponent;
  CopyMem (&ManifestSign, KeyManifestSignature->Signature.Signature, sizeof(ManifestSign));
  SwapEndian ((UINT8 *)&ManifestPubKeyExponent, sizeof(ManifestPubKeyExponent));
  SwapEndian (ManifestPubKey, sizeof(ManifestPubKey));
//  SwapEndian (ManifestSign, sizeof(ManifestSign));

  //
  // Calculate hash
  //
  CreateHash (
    (UINT8 *)KeyManifest,
    (UINTN)KeyManifestSignature - (UINTN)KeyManifest,
    KeyHash
    );

  //
  // Verification
  //

  //
  // Generate & Initialize RSA Context.
  //

  //
  // Allocates & Initializes RSA Context by OpenSSL RSA_new()
  //
  Rsa = RSA_new ();
  if (Rsa == NULL) {
    printf ("Rsa == NULL\n");
    return STATUS_ERROR;
  }

  //
  // Set RSA Key Components.
  // NOTE: Only N and E are needed to be set as RSA public key for signature verification.
  //

  //
  // RSA Public Modulus (N)
  //
  if (Rsa->n != NULL) {
    BN_free (Rsa->n);
  }
  Rsa->n = BN_bin2bn (ManifestPubKey, sizeof(ManifestPubKey), Rsa->n);

  //
  // RSA Public Exponent (e)
  //
  if (Rsa->e != NULL) {
    BN_free (Rsa->e);
  }
  Rsa->e = BN_bin2bn ((UINT8 *)&ManifestPubKeyExponent, sizeof(ManifestPubKeyExponent), Rsa->e);

  //
  // Verify the signature.
  //

  //
  // RSA PKCS#1 Signature Decoding using OpenSSL RSA Decryption with Public Key
  //
  Length = RSA_public_decrypt (
             sizeof(ManifestSign),
             ManifestSign,
             OutBuffer,
             Rsa,
             RSA_PKCS1_PADDING
             );
  //
  // Invalid RSA Key or PKCS#1 Padding Checking Failed (if Length < 0)
  // NOTE: Length should be the addition of HashLength and some DER value.
  //       Ignore more strict length checking here.
  //
  if (Length < SHA256_DIGEST_SIZE) {
    RetStatus = STATUS_ERROR;
    printf ("FAIL: Manifest Signature length\n");
    goto Done;
  }

  //
  // Validate the MessageHash and Decoded Signature
  // NOTE: The decoded Signature should be the DER encoding of the DigestInfo value
  //       DigestInfo ::= SEQUENCE {
  //           digestAlgorithm AlgorithmIdentifier
  //           digest OCTET STRING
  //       }
  //       Then Memory Comparing should skip the DER value of the underlying SEQUENCE
  //       type and AlgorithmIdentifier.
  //
  if (CompareMem (KeyHash, OutBuffer + Length - SHA256_DIGEST_SIZE, SHA256_DIGEST_SIZE) == 0) {
    //
    // Valid RSA PKCS#1 Signature
    //
    printf ("PASS: Manifest Signature Verification\n");
    // Use last status
  } else {
    //
    // Failed to verification
    //
    printf ("FAIL: Manifest Signature Verification\n");
    RetStatus = STATUS_ERROR;
  }

Done:
  if (Rsa != NULL) {
    //
    // Free OpenSSL RSA Context
    //
    RSA_free (Rsa);
  }

  return RetStatus;
}

STATUS
MBiosGen (
  IN INTN   argc,
  IN CHAR8  **argv
  )
/*++

Routine Description:

  Main function for MBiosGen.

Arguments:

  argc - Number of command line parameters.
  argv - Array of pointers to parameter strings.

Returns:
  STATUS_SUCCESS - Utility exits successfully.
  STATUS_ERROR   - Some error occurred during execution.

--*/
{
  UINT8                       *FileBufferRaw;
  UINTN                       FitEntryNumber;
  STATUS                      Status;
  UINT8                       *FdFileBuffer;
  UINT32                      FdFileSize;

  //
  // Step 1: Read BIOS data
  //
  Status = ReadInputFile (argv[1], &FdFileBuffer, &FdFileSize, &FileBufferRaw);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "Unable to open file", "%s", argv[1]);
    goto Done;
  }

  if ((strcmp (argv[3], "-F") == 0) ||
       (strcmp (argv[3], "-f") == 0)) {
    gFitTableContext.FitTablePointerOffset = xtoi (argv[4]);
  }

  //
  // Step 2: Get FIT entry information
  //
  FitEntryNumber = GetFitEntryInfo (FdFileBuffer, FdFileSize);
  if (FitEntryNumber == 0) {
    Error (NULL, 0, 0, "No FIT table found", NULL);
    Status = STATUS_ERROR;
    goto Done;
  }

  //
  // For debug
  //
  PrintFitTable (FdFileBuffer, FdFileSize);

  //
  // Step 3: Generate Bpm
  //
  Status = GenerateBpm (argc, argv, FdFileBuffer, FdFileSize);
  if (Status != STATUS_SUCCESS) {
    goto Done;
  }

  PrintBootPolicyManifest (gMBiosContext.BootPolicyManifest);
  if (gMBiosContext.KeyManifest != NULL) {
    PrintKeyManifest (gMBiosContext.KeyManifest);
  }
  printf ("BiosDataArea: %x\n", (UINT32) (UINTN) gMBiosContext.BiosDataArea);
  if (gMBiosContext.BiosDataArea != NULL) {
    PrintBiosDataArea (gMBiosContext.BiosDataArea);
  }

  //
  // Step 4: Update MBIOS data for BiosPolicy
  //
  Status = UpdateMBiosPolicy (FdFileBuffer, FdFileSize);
  if (Status != STATUS_SUCCESS) {
    goto Done;
  }

  //
  // Step 5: Write MBIOS data
  //
  Status = WriteOutputFile (argv[2], FdFileBuffer, FdFileSize);

  //
  // For debug
  //
  printf ("Final FIT table\n");
  PrintFitTable (FdFileBuffer, FdFileSize);

  //
  // Step 6: Verify
  //
  Status = VerifyBpm (FdFileBuffer, FdFileSize);
  if (Status == STATUS_SUCCESS) {
    printf ("VerifyBpm - PASS\n");
  } else {
    printf ("VerifyBpm - FAIL\n");
  }

  Status = VerifyKeyManifest (FdFileBuffer, FdFileSize);
  if (Status == STATUS_SUCCESS) {
    printf ("VerifyKeyManifest - PASS\n");
  } else {
    printf ("VerifyKeyManifest - FAIL\n");
  }

  printf ("###################################\n");
  printf ("# BPMBIOS generated successfully! #\n");
  printf ("###################################\n");

Done:
  FreeMBios ();
  if (FileBufferRaw != NULL) {
    free ((VOID *)FileBufferRaw);
  }

  return Status;
}

STATUS
DumpInfo (
  IN CHAR8 *FileName
  )
{
  UINT8                       *FileBufferRaw;
  UINTN                       FitEntryNumber;
  STATUS                      Status;
  UINT8                       *FdFileBuffer;
  UINT32                      FdFileSize;
  FIT_TABLE_CONTEXT_ENTRY     *BiosPolicyRecord;
  UINT8                       *PolicyData;

  //
  // Step 1: Read BIOS data
  //
  Status = ReadInputFile (FileName, &FdFileBuffer, &FdFileSize, &FileBufferRaw);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "Unable to open file", "%s", FileName);
    return Status;
  }

  //
  // Step 2: Get FIT entry information
  //
  FitEntryNumber = GetFitEntryInfo (FdFileBuffer, FdFileSize);
  if (FitEntryNumber == 0) {
    Error (NULL, 0, 0, "No FIT table found", NULL);
    return STATUS_ERROR;
  }

  //
  // 3. Print Fit table
  //
  PrintFitTable (FdFileBuffer, FdFileSize);

  //
  // 4. Print Bpm
  //
  BiosPolicyRecord = GetFitEntry (FIT_TABLE_TYPE_BOOT_POLICY_MANIFEST);
  if (BiosPolicyRecord == NULL) {
    printf ("No Bpm Policy Found in FIT\n");
  } else {
    PolicyData = FLASH_TO_MEMORY (BiosPolicyRecord->Address, FdFileBuffer, FdFileSize);
    PrintBootPolicyManifest (PolicyData);
  }

  //
  // 5. Print Km
  //
  BiosPolicyRecord = GetFitEntry (FIT_TABLE_TYPE_KEY_MANIFEST);
  if (BiosPolicyRecord == NULL) {
    printf ("No KeyManifest Found in FIT\n");
  } else {
    PolicyData = FLASH_TO_MEMORY (BiosPolicyRecord->Address, FdFileBuffer, FdFileSize);
    PrintKeyManifest ((KEY_MANIFEST_STRAUCTURE *)PolicyData);
  }

  //
  // 6. Print BiosDataArea
  //
  BiosPolicyRecord = GetFitEntry (FIT_TABLE_TYPE_BIOS_DATA_AREA);
  if (BiosPolicyRecord == NULL) {
    printf ("No BiosDataArea Found in FIT\n");
  } else {
    PolicyData = FLASH_TO_MEMORY (BiosPolicyRecord->Address, FdFileBuffer, FdFileSize);
    PrintBiosDataArea ((BIOS_DATA_AREA_STRAUCTURE *)PolicyData);
  }

  return STATUS_SUCCESS;
}

int
main (
  int   argc,
  char  **argv
  )
/*++

Routine Description:

  Main function.

Arguments:

  argc - Number of command line parameters.
  argv - Array of pointers to parameter strings.

Returns:
  STATUS_SUCCESS - Utility exits successfully.
  STATUS_ERROR   - Some error occurred during execution.

--*/
{
  SetUtilityName (UTILITY_NAME);

  //
  // Display utility information
  //
  PrintUtilityInfo ();

  //
  // Verify the correct number of arguments
  //
  if (argc >= MIN_ARGS) {
    return MBiosGen (argc, argv);
  } else if ((argc == 3) &&
             ((strcmp (argv[2], "-INFO") == 0) ||
              (strcmp (argv[2], "-info") == 0))) {
    DumpInfo (argv[1]);
    return STATUS_SUCCESS;
  } else {
    Error (NULL, 0, 0, "invalid number of input parameters specified", NULL);
    PrintUsage ();
    return STATUS_ERROR;
  }
}

unsigned int
xtoi (
  char  *str
  )
/*++

Routine Description:

  Convert hex string to uint

Arguments:

  str  -  The string

Returns:

--*/
{
  unsigned int u;
  char         c;
  unsigned int m;

  if (str == NULL) {
    return 0;
  }

  m = (unsigned int) -1 >> 4;
  //
  // skip preceeding white space
  //
  while (*str && *str == ' ') {
    str += 1;
  }
  //
  // skip preceeding zeros
  //
  while (*str && *str == '0') {
    str += 1;
  }
  //
  // skip preceeding x/X character
  //
  if (*str && (*str == 'x' || *str == 'X')) {
    str += 1;
  }
  //
  // convert hex digits
  //
  u = 0;
  c = *(str++);
  while (c) {
    if (c >= 'a' && c <= 'f') {
      c -= 'a' - 'A';
    }

    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')) {
      if (u > m) {
        return (unsigned int) -1;
      }

      u = (u << 4) | (c - (c >= 'A' ? 'A' - 10 : '0'));
    } else {
      //
      // Let application exit immediately
      //
      Error (NULL, 0, 0, "Hex value is expected!", NULL);
      exit (0);
      break;
    }

    c = *(str++);
  }

  return u;
}

unsigned long long
xtol (
  char  *str
  )
/*++

Routine Description:

  Convert hex string to uint

Arguments:

  str  -  The string

Returns:

--*/
{
  unsigned long long u;
  char         c;
  unsigned long long m;

  if (str == NULL) {
    return 0;
  }

  m = (unsigned long long) -1 >> 4;
  //
  // skip preceeding white space
  //
  while (*str && *str == ' ') {
    str += 1;
  }
  //
  // skip preceeding zeros
  //
  while (*str && *str == '0') {
    str += 1;
  }
  //
  // skip preceeding x/X character
  //
  if (*str && (*str == 'x' || *str == 'X')) {
    str += 1;
  }
  //
  // convert hex digits
  //
  u = 0;
  c = *(str++);
  while (c) {
    if (c >= 'a' && c <= 'f') {
      c -= 'a' - 'A';
    }

    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F')) {
      if (u > m) {
        return (unsigned long long) -1;
      }

      u = (u << 4) | (c - (c >= 'A' ? 'A' - 10 : '0'));
    } else {
      //
      // Let application exit immediately
      //
      Error (NULL, 0, 0, "Hex value is expected!", NULL);
      exit (0);
      break;
    }

    c = *(str++);
  }

  return u;
}

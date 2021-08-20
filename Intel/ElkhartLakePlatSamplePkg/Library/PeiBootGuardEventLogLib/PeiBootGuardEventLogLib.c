/** @file
  This file contains functions for creating TPM Event Log

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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

#include <IndustryStandard/UefiTcgPlatform.h>
#include <Guid/TcgEventHob.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PcdLib.h>
#include <Library/HobLib.h>
#include <Library/BaseCryptLib.h>
#include <Library/IoLib.h>
#include <Library/NemMapLib.h>
#include <Library/Tpm12CommandLib.h>
#include <Library/Tpm2CommandLib.h>
#include <Library/Tpm2DeviceLib.h>
#include <Ppi/FirmwareVolumeInfoMeasurementExcluded.h>
#include <Tcg2ConfigNvData.h>
#include <Protocol/Tcg2Protocol.h>
#include <Library/PciSegmentLib.h>
#include <Acm.h>
#include <Register/MeRegs.h>
#include <Register/PttPtpRegs.h>
#include <CpuRegs.h>
#include <Library/BootGuardLib.h>
#include <IndustryStandard/FirmwareInterfaceTable.h>
#include <Library/PeiBootGuardEventLogLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <IndustryStandard/Tpm20.h>

#define MMIO_ACM_POLICY_STATUS  (TXT_PUBLIC_BASE + R_CPU_ACM_POLICY_STATUS)  // 0xFED30378

//
// Chipset register, need double check if it is right.
//
#define ACM_KEY_HASH_MMIO_ADDR_0            0xFED30400
#define ACM_KEY_HASH_MMIO_ADDR_1            (ACM_KEY_HASH_MMIO_ADDR_0 + 8)
#define ACM_KEY_HASH_MMIO_ADDR_2            (ACM_KEY_HASH_MMIO_ADDR_0 + 16)
#define ACM_KEY_HASH_MMIO_ADDR_3            (ACM_KEY_HASH_MMIO_ADDR_0 + 24)

//
// Data structure definition
//
#pragma pack (1)

//
// BPM Policy:
//   FIT record type 12 points to Boot Policy Manifest.
//   FIT record type 11 points to Key Manifest.
//

#define RSA_KEY_SIZE_1K              1024
#define RSA_KEY_SIZE_2K              2048
#define RSA_KEY_SIZE_3K              3072
#define PKCS_1_5_RSA_SHA1_SIGNATURE_SIZE    (RSA_KEY_SIZE_1K / 8)
#define PKCS_1_5_RSA_SHA256_SIGNATURE_SIZE  (RSA_KEY_SIZE_2K / 8)
#define PKCS_1_5_RSA_SHA384_SIGNATURE_SIZE  (RSA_KEY_SIZE_3K / 8)
#define SHA1_DIGEST_SIZE             20
#define SHA256_DIGEST_SIZE           32
#define SHA384_DIGEST_SIZE           48
#define SM3_256_DIGEST_SIZE          32

typedef union {
    UINT8   digest8[SHA1_DIGEST_SIZE];
    UINT32  digest32[SHA1_DIGEST_SIZE / 4];
} BtgSha1Digest_u;

typedef union {
    UINT8   digest8[SHA256_DIGEST_SIZE];
    UINT32  digest32[SHA256_DIGEST_SIZE / 4];
    UINT64  digest64[SHA256_DIGEST_SIZE / 8];
} BtgSha256Digest_u;

typedef union {
    UINT8   digest8[SHA384_DIGEST_SIZE];
    UINT32  digest32[SHA384_DIGEST_SIZE / 4];
    UINT64  digest64[SHA384_DIGEST_SIZE / 8];
} BtgSha384Digest_u;

//
// Hash structure
//
typedef struct {
  UINT16               HashAlg;
  UINT16               Size;
  BtgSha1Digest_u      HashBuffer;
} SHA1_HASH_STRUCTURE;

typedef struct {
  UINT16               HashAlg;
  UINT16               Size;
  BtgSha256Digest_u    HashBuffer;
} SHA256_HASH_STRUCTURE;

typedef struct {
  UINT16               HashAlg;
  UINT16               Size;
  BtgSha384Digest_u    HashBuffer;
} SHA384_HASH_STRUCTURE;

typedef struct {
  UINT16               HashAlg;
  UINT16               Size;
  UINT8                HashBuffer[];
} SHAX_HASH_STRUCTURE;

typedef struct {
  UINT16               Size;           //Total number of bytes of HASH_LIST structure
  UINT16               Count;          //Number of Digest elements
//  SHAX_HASH_STRUCTURE  Digest[];       //Array of digests  {AlgID, Size, HashValue; ...}
} HASH_LIST;

typedef struct {
  UINT16                 Size;         //Total number of bytes of HASH_LIST structure
  UINT16                 Count;        //Number of Digest elements
  SHA1_HASH_STRUCTURE    Sha1Digest;   //Array of digests  {AlgID, Size, HashValue; ...}
  SHA256_HASH_STRUCTURE  Sha256Digest; //Array of digests  {AlgID, Size, HashValue; ...}
  SHA256_HASH_STRUCTURE  ShaSm3Digest; //Array of digests  {AlgID, Size, HashValue; ...}
  SHA384_HASH_STRUCTURE  Sha384Digest; //Array of digests  {AlgID, Size, HashValue; ...}
} MAX_HASH_LIST;

struct {
  UINT64               Usage;          // Bit mask of usages
  SHAX_HASH_STRUCTURE  Digest;         // Standard BtG hash structure primitive
} SHAX_KMHASH_STRUCT;


#define ALG_RSA             0x1
#define ALG_RSASSA          0x14

#define RSA_PUBLIC_KEY_STRUCT_VERSION_1_0  0x10
#define RSA_PUBLIC_KEY_STRUCT_KEY_EXPONENT_DEFAULT  0x11 // NOT 0x10001

typedef struct {
  UINT8    Version;                    // 0x10
  UINT16   KeySizeBits;                // 1024 or 2048 or 3072 bits
 // UINT32   Exponent;                   // The public exponent
//  UINT8    Modulus[];                  // The modulus in LSB format
} KEY_STRUCT_HEADER;

typedef struct {
  UINT8    Version;                    // 0x10
  UINT16   KeySizeBits;                // Number of bits in the modulus.
  UINT32   Exponent;                   // The public exponent (must be RSA_KEY_EXPONENT_VALUE)
  UINT8    Modulus[RSA_KEY_SIZE_2K/8]; // The modulus in LSB format (256 bytes)
} RSA2K_PUBLIC_KEY_STRUCT;

typedef struct {
  UINT8    Version;                    // 0x10
  UINT16   KeySizeBits;                // Number of bits in the modulus.
  UINT32   Exponent;                   // The public exponent (must be RSA_KEY_EXPONENT_VALUE)
  UINT8    Modulus[RSA_KEY_SIZE_3K/8]; // The modulus in LSB format (384 bytes)
} RSA3K_PUBLIC_KEY_STRUCT;

typedef struct {
  UINT8    Version;                    // 0x10
  UINT16   KeySizeBits;                // 1024 or 2048 or 3072 bits
  UINT32   Exponent;                   // The public exponent
  UINT8    Modulus[1];                  // The modulus in LSB format
} RSA_PUBLIC_KEY_STRUCT;

#define ECC_PUBLIC_KEY_STRUCT_VERSION_1_0  0x10
#define ECC_PUBLIC_KEY_STRUCT_KEY_SIZE_DEFAULT  256
#define ECC_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT   (ECC_PUBLIC_KEY_STRUCT_KEY_SIZE_DEFAULT/8)
typedef struct {
  UINT8  Version;                      // 0x10
  UINT16 KeySizeBits;                  // 256 - Number of bits in key. Fixed for SM2
  UINT8  Qx[ECC_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT];  // X component. Fixed size for SM2
  UINT8  Qy[ECC_PUBLIC_KEY_STRUCT_KEY_LEN_DEFAULT];  // Y component. Fixed size for SM2
} ECC_PUBLIC_KEY_STRUCT;

#define RSASSA_SIGNATURE_STRUCT_VERSION_1_0  0x10

typedef struct {
  UINT8    Version;
  UINT16   SigSizeBits;                // 2048 or 3072 bits
//  UINT16   HashAlg;
//  UINT8    Signature[];
} SIGNATURE_STRUCT_HEADER;

typedef struct {
  UINT8    Version;
  UINT16   KeySizeBits;                // 2048 or 3072 bits
  UINT16   HashAlg;
  UINT8    Signature[];
} RSASSA_SIGNATURE_STRUCT;

#define ECC_SIGNATURE_STRUCT_VERSION_1_0  0x10
typedef struct {
  UINT8    Version;
  UINT16   KeySizeBits;                // 256 or 384 bits
  UINT16   HashAlg;
//  UINT8    R[];                      // R component
//  UINT8    S[];                      // S component
} ECC_SIGNATURE_STRUCT;

#define KEY_SIGNATURE_STRUCT_VERSION_1_0  0x10
typedef struct {
  UINT8                      Version;
  UINT16                     KeyAlg;       // TPM_ALG_RSA=0x1 or TPM_ALG_ECC=0x23
/*
  union {                                  // Based on KeyAlg
    RSA_PUBLIC_KEY_STRUCT    RsaKey;
    ECC_PUBLIC_KEY_STRUCT    EccKey;
  } Key;
  UINT16                     SigScheme;    // TPM_ALG_RSASSA=0x14 or TPM_ALG_RSAPSS=0x15 or TPM_ALG_SM2=0x1B
  union {                                  // Based on KeyAlg
    RSASSA_SIGNATURE_STRUCT  SignatureRsa;
    ECC_SIGNATURE_STRUCT     SignatureEcc;
  } Sig;
  */
} KEY_AND_SIGNATURE_STRUCT_HEADER;
typedef struct {
  UINT8                      Version;
  UINT16                     KeyAlg;       // TPM_ALG_RSA=0x1 or TPM_ALG_ECC=0x23
  union {                                  // Based on KeyAlg
    RSA_PUBLIC_KEY_STRUCT    RsaKey;
    ECC_PUBLIC_KEY_STRUCT    EccKey;
  } Key;
  UINT16                     SigScheme;    // TPM_ALG_RSASSA=0x14 or TPM_ALG_RSAPSS=0x15 or TPM_ALG_SM2=0x1B
  union {                                  // Based on KeyAlg
    RSASSA_SIGNATURE_STRUCT  SignatureRsa;
    ECC_SIGNATURE_STRUCT     SignatureEcc;
  } Sig;
} KEY_AND_SIGNATURE_STRUCT;

#define BP_KEY_TYPE_BOOT_POLICY_MANIFEST  0
#define BP_KEY_TYPE_KEY_MANIFEST          1

#define BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_ID  (*(UINT64 *)"__ACBP__")
#define BOOT_POLICY_MANIFEST_HEADER_VERSION_2_1          0x21
//#define BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_VERSION_1_0   0x01
typedef struct {
  UINT8              StructureId[8];
  UINT8              StructVersion;        // 0x21
  UINT8              HdrStructVersion;     // 0x20
  UINT16             HdrSize;              // total number of bytes in Header (i.e., offset to first element)
  UINT16             KeySignatureOffset;   // Offset from start of Bpm to KeySignature field of Signature Element
  UINT8              BpmRevision;
  UINT8              BpmRevocation;
  UINT8              AcmRevocation;
  UINT8              Reserved;
  UINT16             NemPages;
} BOOT_POLICY_MANIFEST_HEADER;

#define IBB_SEGMENT_FLAG_IBB     0x0
#define IBB_SEGMENT_FLAG_NON_IBB 0x1
//#define IBB_ALIGNMENT            0x3F    // 64 bytes for BootGuard
typedef struct {
  UINT16             Reserved;         // Alignment
  UINT16             Flags;            // Control flags
  UINT32             Base;             // Segment base
  UINT32             Size;             // Segment size
} IBB_SEGMENT;

#define BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__IBBS__")
#define BOOT_POLICY_MANIFEST_IBB_ELEMENT_DIGEST_ID     (*(UINT64 *)"__DIGE__")

//#define BOOT_POLICY_MANIFEST_IBB_ELEMENT_DIGEST_ID     (*(UINT64 *)"__IBBS DIG__")

#define BOOT_POLICY_MANIFEST_IBB_ELEMENT_VERSION_2_0       0x20
//#define IBB_FLAG_ENABLE_VTD            0x1
#define IBB_FLAG_INITIAL_MEASURE_LOC3  0x2
#define IBB_FLAG_AUTHORITY_MEASURE     0x4
//#define IBB_ENTRYPOINT_MIN   0xFFFFFFC0
typedef struct {
  UINT8               StructureId[8];
  UINT8               StructVersion;   // 0x20
  UINT8               Reserved0;
  UINT16              ElementSize;     // Total number of bytes in the element
  UINT8               Reserved1;
  UINT8               SetType;
  UINT8               Reserved;
  UINT8               PbetValue;
  UINT32              Flags;
  UINT64              IbbMchBar;
  UINT64              VtdBar;
  UINT32              DmaProtBase0;
  UINT32              DmaProtLimit0;
  UINT64              DmaProtBase1;
  UINT64              DmaProtLimit1;
  SHAX_HASH_STRUCTURE PostIbbHash;
//  UINT32              IbbEntryPoint;
//  HASH_LIST           DigestList;
//  HASH_STRUCTURE      ObbHash;
//  UINT8               Reserved2[3];
//  UINT8               SegmentCount;
//  IBB_SEGMENT*        IbbSegment;  //IbbSegment[SegmentCount]
} IBB_ELEMENT;

#define BOOT_POLICY_MANIFEST_TXT_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__TXTS__")
#define BOOT_POLICY_MANIFEST_TXT_ELEMENT_VERSION_2_0       0x20
typedef struct {
  UINT8               StructureId[8];
  UINT8               StructVersion;   // 0x20
  UINT8               Reserved0;
  UINT16              ElementSize;     // Total number of bytes in the element
  UINT8               Reserved1;
  UINT8               SetType;
  UINT16              Reserved;
  UINT32              Flags;
  UINT16              PwrDownInterval;
  UINT8               PttCmosOffset0;
  UINT8               PttCmosOffset1;
  UINT16              AcpiBaseOffset;
  UINT16              Reserved2;
  UINT32              PrwmBaseOffset;
  HASH_LIST           DigestList;
  UINT8               Reserved3[3];
  UINT8               SegmentCount;
  IBB_SEGMENT*        TxtSegment;      // TxtSegment[SegmentCount]
} TXT_ELEMENT;

#define BOOT_POLICY_MANIFEST_PLATFORM_CONFIG_DATA_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__PCDS__")
#define BOOT_POLICY_MANIFEST_PLATFORM_CONFIG_DATA_ELEMENT_VERSION_2_0       0x20
typedef struct {
  UINT8               StructureId[8];
  UINT8               StructVersion;   // 0x20
  UINT8               Reserved0;
  UINT16              ElementSize;     // Total number of bytes in the element
  UINT16              Reserved1;
  UINT16              SizeOfData;
  UINT8*              Data;  //Data[SizeofData]  // Any data but starts from PDRS
} PLATFORM_CONFIG_DATA_ELEMENT;

#define BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__PMDA__")
#define BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_VERSION_2_0       0x20
//#define PLATFORM_DATA_ALIGNMENT  0x3  // 4 bytes
typedef struct {
  UINT8               StructureId[8];
  UINT8               StructVersion;   // 0x20
  UINT8               Reserved0;
  UINT16              ElementSize;     // Total number of bytes in the element
  UINT16              Reserved1;
  UINT16              PmDataSize;      // required to be 4 byte multiple
  UINT8*              PmData; //PmData[PmDataSize]
} PLATFORM_MANUFACTURER_ELEMENT;

#define BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_STRUCTURE_ID  (*(UINT64 *)"__PMSG__")
#define BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_VERSION_1_0       0x10
typedef struct {
  UINT8               StructureId[8];
  UINT8               StructVersion;       // 0x20
  UINT8               Reserved[3];         // KeySignature must be DWORD aligned
  KEY_AND_SIGNATURE_STRUCT  KeySignature;  // this is now a variable Size
} BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT;

#define KEY_MANIFEST_STRUCTURE_ID  (*(UINT64 *)"__KEYM__")
#define KEY_MANIFEST_STRUCTURE_VERSION_2_1     0x21
typedef struct {
  UINT8               StructureId[8];
  UINT8               StructVersion;       // 0x21
  UINT8               reserved[3];         // 3 bytes to make KeySignatureOffset same offset as for BPM
  UINT16              KeySignatureOffset;  // Offset from start of KM to KeyManifestSignature
  UINT8               Reserved2[3];        // Alignment
  UINT8               KeyManifestRevision;
  UINT8               KmSvn;
  UINT8               KeyManifestId;
  UINT16              KmPubKeyHashAlg;
  UINT16              KeyCount;
//  KMHASH_STRUCT*       KeyHash;  //KeyHash[KM_MAX_KEYS];
//  KEY_AND_SIGNATURE_STRUCT  KeyManifestSignature;
} KEY_MANIFEST_STRUCTURE;

//
// Detail PCR data
//
typedef struct {
  UINT64 AcmPolicySts;
  UINT16 AcmSvn;                   // ACM_SVN from ACM Header
  UINT8  AcmRsaSignature[];        // copy from ACM.HEADER.RSASIG
//  UINT8  KmRsaSignature[];         // copy from KM signature
//  UINT8  BpmRsaSignature[];        // copy from BPM signature
//  UINT8  IbbHash[];                // hash value of IBB
} DETAIL_PCR_DATA;

typedef struct {
  UINT64  AcmPolicySts;                        // lower 8 bits of the BP.RSTR
  UINT16  AcmSvn;                              // ACM_SVN from ACM Header
  //buffer size: Max AcmRSASignature + KmRSASignature + BpmRSASignature + IbbHash
  UINT8   buffer[RSA_KEY_SIZE_3K/8 + RSA_KEY_SIZE_3K/8 + RSA_KEY_SIZE_3K/8 + SHA384_DIGEST_SIZE ] ;
} MAX_DETAIL_PCR_DATA;

//
// Authority PCR data
//
typedef struct {
  UINT64 AcmPolicySts;
  UINT16 AcmSvn;                       // ACM_SVN from ACM Header
  UINT8  AcmKeyHash[];                 // The hash of the key used to verify the ACM (SHAxxx)
//  UINT8  BpKeyHash[];                  // The hash of the key used to verify the Key Manifest (SHAxxx)
//  UINT8  BpmKeyHashFromKm[];           // The hash of the key used to verify the Boot Policy Manifest (SHAxxx)
} AUTHORITY_PCR_DATA;

typedef struct {
  UINT64 AcmPolicySts;
  UINT16 AcmSvn;                               // ACM_SVN from ACM Header
  UINT8  AcmKeyHash[SHA384_DIGEST_SIZE];       // The hash of the key used to verify the ACM (SHAxxx)
  UINT8  BpKeyHash[SHA384_DIGEST_SIZE];        // The hash of the key used to verify the Key Manifest (SHAxxx)
  UINT8  BpmKeyHashFromKm[SHA384_DIGEST_SIZE]; // The hash of the key used to verify the Boot Policy Manifest (SHAxxx)
} MAX_AUTHORITY_PCR_DATA;

//
// Efi Startup Locality Event Data
//
typedef struct {
  UINT8   Signature[16];
  UINT8   StartupLocality;
} TCG_EFI_STARTUP_LOCALITY_EVENT;

typedef struct {
  EFI_GUID                  *EventGuid;
  EFI_TCG2_EVENT_LOG_FORMAT  LogFormat;
} EFI_TCG2_EVENT_INFO_STRUCT;

typedef union {
  struct {
    UINT32 KmId           : 4;      // 0-3   Key Manifest ID used for verified Key Manifest
    UINT32 MeasuredBoot   : 1;      // 4     perform measured boot
    UINT32 VerifiedBoot   : 1;      // 5     perform verified boot
    UINT32 HAP            : 1;      // 6     high assurance platform
    UINT32 TxtSupported   : 1;      // 7     txt supported
    UINT32 Reserved       : 1;      // 8     must be 0
    UINT32 DCD            : 1;      // 9     disable CPU debug
    UINT32 DBI            : 1;      // 10    disable BSP init
    UINT32 PBE            : 1;      // 11    protect BIOS environment
    UINT32 BBP            : 1;      // 12    bypass boot policy - fast S3 resume
    UINT32 TpmType        : 2;      // 13-14 TPM Type
    UINT32 TpmSuccess     : 1;      // 15    TPM Success
    UINT32 Reserved2      : 4;      // 16-19 BIOS Heartbeat
    UINT32 TxtProfile     : 5;      // 20-24 TXT profile selection
    UINT32 MemScrubPolicy : 2;      // 25-26 Memory scrubbing policy
    UINT32 KmArbEn        : 1;      // 27    KM ARB enable
    UINT32 BpmArbEn       : 1;      // 28    BPM ARB enable
    UINT32 Reserved3      : 3;      // 29-31
  } Bits;
  UINT32 Data;
} ACM_BIOS_POLICY;

#pragma pack ()

EFI_TCG2_EVENT_INFO_STRUCT mTcg2EventInfo[] = {
  {&gTcgEventEntryHobGuid,             EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2},
  {&gTcgEvent2EntryHobGuid,            EFI_TCG2_EVENT_LOG_FORMAT_TCG_2},
};

//
// This PPI means a FV does not need to be extended to PCR by TCG modules.
//
typedef struct {
  UINT32                                                Count;
  EFI_PEI_FIRMWARE_VOLUME_INFO_MEASUREMENT_EXCLUDED_FV  Fv[3];
} FIRMWARE_VOLUME_INFO_MEASUREMENT_EXCLUDED_PPI_2;

FIRMWARE_VOLUME_INFO_MEASUREMENT_EXCLUDED_PPI_2 mPeiFirmwareVolumeInfoMeasurementExcludedPpi = {
  3,
  {
    {
      FixedPcdGet32 (PcdFlashFvPreMemoryBase),
      FixedPcdGet32 (PcdFlashFvPreMemorySize)
    },
  }
};

EFI_PEI_PPI_DESCRIPTOR  mPeiFirmwareVolumeInfoMeasurementExcludedPpiList = {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gEfiPeiFirmwareVolumeInfoMeasurementExcludedPpiGuid,
  &mPeiFirmwareVolumeInfoMeasurementExcludedPpi
};

/**
  Dump raw data.

  @param[in]  Data  raw data
  @param[in]  Size  raw data size

**/
VOID
InternalDumpData (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN  Index;
  for (Index = 0; Index < Size; Index++) {
    DEBUG ((DEBUG_INFO, "%02x", (UINTN)Data[Index]));
  }
}

/**
  Dump raw data with colume format.

  @param[in]  Data  raw data
  @param[in]  Size  raw data size

**/
VOID
InternalDumpHex (
  IN UINT8  *Data,
  IN UINTN  Size
  )
{
  UINTN   Index;
  UINTN   Count;
  UINTN   Left;

#define COLUME_SIZE  (16 * 2)

  Count = Size / COLUME_SIZE;
  Left  = Size % COLUME_SIZE;
  for (Index = 0; Index < Count; Index++) {
    DEBUG ((DEBUG_INFO, "%04x: ", Index * COLUME_SIZE));
    InternalDumpData (Data + Index * COLUME_SIZE, COLUME_SIZE);
    DEBUG ((DEBUG_INFO, "\n"));
  }

  if (Left != 0) {
    DEBUG ((DEBUG_INFO, "%04x: ", Index * COLUME_SIZE));
    InternalDumpData (Data + Index * COLUME_SIZE, Left);
    DEBUG ((DEBUG_INFO, "\n"));
  }
}

/**
  Check if buffer is all zero.

  @param[in] Buffer      Buffer to be checked.
  @param[in] BufferSize  Size of buffer to be checked.

  @retval TRUE  Buffer is all zero.
  @retval FALSE Buffer is not all zero.
**/
BOOLEAN
IsZeroBufferLocal (
  IN VOID  *Buffer,
  IN UINTN BufferSize
  )
{
  UINT8 *BufferData;
  UINTN Index;

  BufferData = Buffer;
  for (Index = 0; Index < BufferSize; Index++) {
    if (BufferData[Index] != 0) {
      return FALSE;
    }
  }
  return TRUE;
}

/**
  Get digest from digest list.

  @param[in] HashAlg    digest algorithm
  @param[in] DigestList digest list
  @param[in] Digest     digest

  @retval EFI_SUCCESS   Sha1Digest is found and returned.
  @retval EFI_NOT_FOUND Sha1Digest is not found.
**/
EFI_STATUS
Tpm2GetDigestFromDigestList (
  IN TPMI_ALG_HASH      HashAlg,
  IN TPML_DIGEST_VALUES *DigestList,
  IN VOID               *Digest
  )
{
  UINTN  Index;
  UINT16 DigestSize;

  DigestSize = GetHashSizeFromAlgo (HashAlg);
  for (Index = 0; Index < DigestList->count; Index++) {
    if (DigestList->digests[Index].hashAlg == HashAlg) {
      CopyMem (
        Digest,
        &DigestList->digests[Index].digest,
        DigestSize
        );
      return EFI_SUCCESS;
    }
  }

  return EFI_NOT_FOUND;
}

/**
  Add a new entry to the Event Log.

  @param[in] DigestList    Pointer to a TPML_DIGEST_VALUES structure.
  @param[in] NewEventHdr   Pointer to a TCG_PCR_EVENT_HDR data structure.
  @param[in] NewEventData  Pointer to the new event data.

  @retval EFI_SUCCESS           The new event log entry was added.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
**/
EFI_STATUS
LogHashEvent (
  IN      TPML_DIGEST_VALUES        *DigestList,
  IN      TCG_PCR_EVENT_HDR         *NewEventHdr,
  IN      UINT8                     *NewEventData
  )
{
  VOID                              *HobData;
  EFI_STATUS                        Status;
  UINTN                             Index;
  EFI_STATUS                        RetStatus;
  TCG_PCR_EVENT2                    *TcgPcrEvent2;
  UINT8                             *DigestBuffer;
  UINT32                            SupportedEventLogs;

  SupportedEventLogs = EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2 | EFI_TCG2_EVENT_LOG_FORMAT_TCG_2;
  DEBUG ((DEBUG_INFO, "SupportedEventLogs - 0x%08x\n", SupportedEventLogs));

  RetStatus = EFI_SUCCESS;
  for (Index = 0; Index < sizeof(mTcg2EventInfo) / sizeof(mTcg2EventInfo[0]); Index++) {
    if ((SupportedEventLogs & mTcg2EventInfo[Index].LogFormat) != 0) {
      DEBUG((DEBUG_INFO, "  LogFormat - 0x%08x\n", mTcg2EventInfo[Index].LogFormat));
      switch (mTcg2EventInfo[Index].LogFormat) {
      case EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2:
        Status = Tpm2GetDigestFromDigestList (TPM_ALG_SHA1, DigestList, &NewEventHdr->Digest);
        if (!EFI_ERROR (Status)) {
          HobData = BuildGuidHob (
                     &gTcgEventEntryHobGuid,
                     sizeof (*NewEventHdr) + NewEventHdr->EventSize
                     );
          if (HobData == NULL) {
            RetStatus = EFI_OUT_OF_RESOURCES;
            break;
          }

          CopyMem (HobData, NewEventHdr, sizeof (*NewEventHdr));
          HobData = (VOID *) ((UINT8*)HobData + sizeof (*NewEventHdr));
          CopyMem (HobData, NewEventData, NewEventHdr->EventSize);
        }
        break;

      case EFI_TCG2_EVENT_LOG_FORMAT_TCG_2:
        HobData = BuildGuidHob (
                   &gTcgEvent2EntryHobGuid,
                   sizeof(TcgPcrEvent2->PCRIndex) + sizeof(TcgPcrEvent2->EventType) + GetDigestListSize (DigestList) + sizeof(TcgPcrEvent2->EventSize) + NewEventHdr->EventSize
                   );
        if (HobData == NULL) {
          RetStatus = EFI_OUT_OF_RESOURCES;
          break;
        }

        TcgPcrEvent2 = HobData;
        TcgPcrEvent2->PCRIndex = NewEventHdr->PCRIndex;
        TcgPcrEvent2->EventType = NewEventHdr->EventType;
        DigestBuffer = (UINT8 *)&TcgPcrEvent2->Digest;
        DigestBuffer = CopyDigestListToBuffer (DigestBuffer, DigestList, PcdGet32 (PcdTpm2HashMask));
        CopyMem (DigestBuffer, &NewEventHdr->EventSize, sizeof(TcgPcrEvent2->EventSize));
        DigestBuffer = DigestBuffer + sizeof(TcgPcrEvent2->EventSize);
        CopyMem (DigestBuffer, NewEventData, NewEventHdr->EventSize);
        break;
      }
    }
  }

  return RetStatus;
}

#if FixedPcdGetBool(PcdBfxEnable) == 1
/**
  Find FIT Entry address data by type

  @param[in] Type   FIT Entry type

  @return FIT entry address data
**/
VOID *
FindFitEntryData (
  IN UINT8   Type
  )
{
  EFI_STATUS                      Status;
  FIRMWARE_INTERFACE_TABLE_ENTRY  *FitEntry;
  UINTN                           FitBaseAddress;
  UINT32                          EntryNum;
  UINT32                          Index;

  Status = GetFitBase (&FitBaseAddress);
  if (EFI_ERROR (Status)) {
    ASSERT_EFI_ERROR (Status);
    return NULL;
  }
  FitEntry = (FIRMWARE_INTERFACE_TABLE_ENTRY  *) FitBaseAddress;
  EntryNum = *(UINT32 *)(&FitEntry[0].Size[0]) & 0xFFFFFF;
  for (Index = 0; Index < EntryNum; Index++) {
    if (FitEntry[Index].Type == Type) {
      DEBUG ((DEBUG_INFO, "Found the FIT entry.\n"));
      return (VOID *)(UINTN)FitEntry[Index].Address;
    }
  }

  return NULL;
}
#else
/**
  Find FIT Entry address data by type

  @param[in] Type   FIT Entry type

  @return FIT entry address data
**/
VOID *
FindFitEntryData (
  IN UINT8   Type
  )
{
  FIRMWARE_INTERFACE_TABLE_ENTRY  *FitEntry;
  UINT32                          EntryNum;
  UINT64                          FitTableOffset;
  UINT32                          Index;

  FitTableOffset = *(UINT64 *)(UINTN)(BASE_4GB - 0x40);
  FitEntry = (FIRMWARE_INTERFACE_TABLE_ENTRY *)(UINTN)FitTableOffset;
  if (FitEntry[0].Address != *(UINT64 *)"_FIT_   ") {
    return NULL;
  }
  if (FitEntry[0].Type != FIT_TYPE_00_HEADER) {
    return NULL;
  }
  EntryNum = *(UINT32 *)(&FitEntry[0].Size[0]) & 0xFFFFFF;
  for (Index = 0; Index < EntryNum; Index++) {
    if (FitEntry[Index].Type == Type) {
      return (VOID *)(UINTN)FitEntry[Index].Address;
    }
  }

  return NULL;
}
#endif

/**
  Find ACM address

  @return ACM address
**/
VOID *
FindAcm (
  VOID
  )
{
  return FindFitEntryData (FIT_TYPE_02_STARTUP_ACM);
}

/**
  Find BPM address

  @return BPM address
**/
VOID *
FindBpm (
  VOID
  )
{
  return FindFitEntryData (FIT_TYPE_0C_BOOT_POLICY_MANIFEST);
}

/**
  Find KM address

  @return KM address
**/
VOID *
FindKm (
  VOID
  )
{
  return FindFitEntryData (FIT_TYPE_0B_KEY_MANIFEST);
}

/**
  Find BPM element by structureID

  @param[in] Bpm           BPM address
  @param[in] StructureID   BPM element StructureID

  @return BPM element
**/
VOID *
FindBpmElement (
  IN BOOT_POLICY_MANIFEST_HEADER              *Bpm,
  IN UINT64                                   StructureId
  )
{
  BOOT_POLICY_MANIFEST_HEADER             *BpmHeader;
  IBB_ELEMENT                             *IbbElement;
  TXT_ELEMENT                             *TxtElement;
  PLATFORM_CONFIG_DATA_ELEMENT            *PcdsElement;
  PLATFORM_MANUFACTURER_ELEMENT           *PmElement;
  BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT  *BpmSignatureElement;
  UINT8                                   *Buffer;

  Buffer = (UINT8 *)Bpm;

  BpmHeader = (BOOT_POLICY_MANIFEST_HEADER *)Buffer;
  if (*(UINT64 *)BpmHeader->StructureId != BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_ID) {
    return NULL;
  }
  if (StructureId == BOOT_POLICY_MANIFEST_HEADER_STRUCTURE_ID) {
    return Buffer;
  }
  Buffer += sizeof(BOOT_POLICY_MANIFEST_HEADER);

  IbbElement = (IBB_ELEMENT *)Buffer;
  if (*(UINT64 *)IbbElement->StructureId != BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID) {
    return NULL;
  }
  if (StructureId == BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID) {
    return Buffer;
  }

  // Advance to end of IBB_ELEMENT structure
  Buffer = (UINT8*) &(IbbElement->PostIbbHash);
  Buffer += sizeof(UINT32) + IbbElement->PostIbbHash.Size;
  Buffer += sizeof(UINT32);  //entrypoint

  if (StructureId == BOOT_POLICY_MANIFEST_IBB_ELEMENT_DIGEST_ID) {
    return Buffer;
  }

  /* Need modification here, we can forward the pointer based on IBB digest list size field */

  Buffer += sizeof(UINT32) + ((SHAX_HASH_STRUCTURE*)Buffer)->Size;  //digest
  Buffer += sizeof(UINT8) + (sizeof(IBB_SEGMENT) * (*Buffer));  //size * segmentcount

  // Do we have TXT element in BPM?
  // If so, advance to end of TXT_ELEMENT structure
  TxtElement = (TXT_ELEMENT *)Buffer;
  if (*(UINT64 *)TxtElement->StructureId == BOOT_POLICY_MANIFEST_TXT_ELEMENT_STRUCTURE_ID)
  {
    Buffer = (UINT8*) &(TxtElement->DigestList);
    Buffer += sizeof(UINT32) + TxtElement->DigestList.Size;
    Buffer += sizeof(UINT8) + (sizeof(IBB_SEGMENT) * (*Buffer));  //size * segmentcount
  }

  // Do we have Platform Config Data element in BPM?
  // If so, advance to end of PLATFORM_CONFIG_DATA_ELEMENT structure
  PcdsElement = (PLATFORM_CONFIG_DATA_ELEMENT *)Buffer;
  if (*(UINT64 *)PcdsElement->StructureId == BOOT_POLICY_MANIFEST_PLATFORM_CONFIG_DATA_ELEMENT_STRUCTURE_ID)
  {
    Buffer += 11 + PcdsElement->SizeOfData;
  }

  // Do we have Platform Manufacturer element in BPM?
  // If so, advance to end of PLATFORM_MANUFACTURER_ELEMENT structure
  PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)Buffer;
  while (*(UINT64 *)PmElement->StructureId == BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID) {
    if (StructureId == BOOT_POLICY_MANIFEST_PLATFORM_MANUFACTURER_ELEMENT_STRUCTURE_ID) {
      return Buffer;
    }
    Buffer += sizeof(PLATFORM_MANUFACTURER_ELEMENT) + PmElement->PmDataSize;
    PmElement = (PLATFORM_MANUFACTURER_ELEMENT *)Buffer;
  }

  BpmSignatureElement = (BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT *)Buffer;
  if (*(UINT64 *)BpmSignatureElement->StructureId != BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_STRUCTURE_ID) {
    return NULL;
  }
  if (StructureId == BOOT_POLICY_MANIFEST_SIGNATURE_ELEMENT_STRUCTURE_ID) {
    return Buffer;
  }
  return NULL;
}

/**
  Find BPM IBB element

  @param[in] Bpm           BPM address

  @return BPM IBB element
**/
VOID *
FindBpmIbb (
  IN BOOT_POLICY_MANIFEST_HEADER              *Bpm
  )
{
  return FindBpmElement (Bpm, BOOT_POLICY_MANIFEST_IBB_ELEMENT_STRUCTURE_ID);
}

/**
  Check if this NPW ACM

  @retval TRUE  This is NPW ACM
  @retval FALSE This is NOT NPW ACM
**/
BOOLEAN
IsNpwAcm (
  VOID
  )
{
  ACM_HEADER  *Acm;

  Acm = FindAcm ();
  ASSERT (Acm != NULL);
  if (Acm == NULL) {
    return FALSE;
  }

  if (((Acm->Flags & ACM_HEADER_FLAG_DEBUG_SIGNED) == 0) && (Acm->AcmSvn < ACM_NPW_SVN)) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Check if this is VerifiedBoot

  @retval TRUE  This is VerifiedBoot
  @retval FALSE This is NOT VerifiedBoot
**/
BOOLEAN
IsVerifiedBoot (
  VOID
  )
{
  if ((AsmReadMsr64 (MSR_BOOT_GUARD_SACM_INFO) & B_BOOT_GUARD_SACM_INFO_VERIFIED_BOOT) != 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Check if this is MeasuredBoot

  @retval TRUE  This is MeasuredBoot
  @retval FALSE This is NOT MeasuredBoot
**/
BOOLEAN
IsMeasuredBoot (
  VOID
  )
{
  if ((AsmReadMsr64 (MSR_BOOT_GUARD_SACM_INFO) & B_BOOT_GUARD_SACM_INFO_MEASURED_BOOT) != 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Get ACM Policy Status

  @return ACM Policy Status
**/
UINT64
GetAcmPolicySts (
  VOID
  )
{
  UINT64 AcmPolicyStatus = MmioRead64 (MMIO_ACM_POLICY_STATUS);

  return AcmPolicyStatus;
}

/**
  Calculate SHA1 Hash

  @param[in]  Data   data
  @param[in]  Size   data size
  @param[out] Digest SHA1 digest
**/
VOID
CreateSha1Hash (
  IN  UINT8     *Data,
  IN  UINTN     Size,
  OUT UINT8     *Digest
  )
{
  UINTN       CtxSize;
  VOID        *HashCtx;

  CtxSize = Sha1GetContextSize ();
  HashCtx = AllocatePool (CtxSize);
  ASSERT (HashCtx != NULL);

  if (HashCtx != NULL){
    Sha1Init (HashCtx);
    Sha1Update (HashCtx, Data, Size);
    Sha1Final (HashCtx, Digest);
    FreePool (HashCtx);

    DEBUG((DEBUG_INFO, "Sha1 Hash  - \n"));
    InternalDumpHex((UINT8 *)(Digest), 20);
  }

  return ;
}

/**
  Calculate SHA256 Hash

  @param[in]  Data   data
  @param[in]  Size   data size
  @param[out] Digest SHA256 digest
**/
VOID
CreateSha256Hash (
  IN  UINT8     *Data,
  IN  UINTN     Size,
  OUT UINT8     *Digest
  )
{
  UINTN       CtxSize;
  VOID        *HashCtx;

  CtxSize = Sha256GetContextSize ();
  HashCtx = AllocatePool (CtxSize);
  ASSERT (HashCtx != NULL);

  if (HashCtx != NULL){
    Sha256Init (HashCtx);
    Sha256Update (HashCtx, Data, Size);
    Sha256Final (HashCtx, Digest);
    FreePool (HashCtx);
    DEBUG((DEBUG_INFO, "Sha256 Hash  - \n"));
    InternalDumpHex((UINT8 *)(Digest), 32);
  }
  return ;
}

/**
  Calculate SHA384 Hash

  @param[in]  Data   data
  @param[in]  Size   data size
  @param[out] Digest SHA384 digest
**/
VOID
CreateSha384Hash (
  IN  UINT8     *Data,
  IN  UINTN     Size,
  OUT UINT8     *Digest
  )
{
  UINTN       CtxSize;
  VOID        *HashCtx;
  CtxSize = Sha384GetContextSize ();
  HashCtx = AllocatePool (CtxSize);
  ASSERT (HashCtx != NULL);

  if (HashCtx != NULL){
    Sha384Init (HashCtx);
    Sha384Update (HashCtx, Data, Size);
    Sha384Final (HashCtx, Digest);
    FreePool (HashCtx);
    DEBUG((DEBUG_INFO, "Sha384 Hash  - \n"));
    InternalDumpHex((UINT8 *)(Digest), 48);
  }
  return ;
}

/**
  Calculate IBB Hash

  @param[in]  BpmIbb BPM IBB element
  @param[out] Digest IBB digest
**/
VOID
CreateIbbHash (
  IN  IBB_ELEMENT *BpmIbb,
  OUT UINT8       *Digest
  )
{
  UINTN       CtxSize;
  VOID        *HashCtx;
//TODO//  UINTN       Index;

  CtxSize = Sha256GetContextSize ();
  HashCtx = AllocatePool (CtxSize);
  ASSERT (HashCtx != NULL);
  Sha256Init (HashCtx);

//TODO//
/*
  for (Index = 0; Index < BpmIbb->SegmentCount; Index++) {
    if (BpmIbb->IbbSegment[Index].Flags == IBB_SEGMENT_FLAG_IBB) {
      Sha256Update (HashCtx, (VOID *)(UINTN)BpmIbb->IbbSegment[Index].Base, BpmIbb->IbbSegment[Index].Size);
    }
  }
*/

  Sha256Final (HashCtx, Digest);
  FreePool (HashCtx);

  return ;
}

/**
  Calculate DetailPCR extend value

  @param[out] SHA1   DetailPCR digest
  @param[out] SHA256 DetailPCR digest
**/
VOID
CalculateDetailPCRExtendValue (
  IN UINT32  ActivePcrBanks,
  OUT UINT8 *Sha1Digest,
  OUT UINT8 *Sha256Digest,
  OUT UINT8 *Sha384Digest
  )
{
  ACM_HEADER                       *Acm;
  KEY_MANIFEST_STRUCTURE           *Km;
  BOOT_POLICY_MANIFEST_HEADER      *Bpm;
  IBB_ELEMENT                      *BpmIbb;
  MAX_DETAIL_PCR_DATA              MaxDetailPcrData;
  UINT8                            *DetailPcrDataPtr;
  UINT32                           AcmSigSize=0;
  UINT32                           KmSigSize=0;
  UINT32                           BpmSigSize=0;
  UINT32                           DetailPcrDataSize;
  UINT32                           SavedDetailPcrDataSize;
  UINT8                            *CurrPos;
  UINT16                            KeyStructSize;
  UINT16                            KeyModulusSize;
  UINT16                            IbbDigestCount;
  UINT16                            IbbDigestSize;
  UINT8                             Idx;
  HASH_LIST                         *IbbHashPtr;

  Acm = FindAcm ();
  ASSERT (Acm != NULL);
  if (Acm == NULL) return;

  Km = FindKm ();
  ASSERT (Km != NULL);
  if (Km == NULL) return;

  //DEBUG ((DEBUG_INFO, "Key- manifest:\n"));
  //InternalDumpHex ((UINT8 *)Km,0x255 );

  Bpm = FindBpm ();
  ASSERT (Bpm != NULL);
  if (Bpm == NULL) return;

  //DEBUG ((DEBUG_INFO, "BPM:\n"));
  //InternalDumpHex ((UINT8 *)Bpm,0x3A1 );

  BpmIbb = FindBpmIbb (Bpm);
  ASSERT (BpmIbb != NULL);
  if (BpmIbb == NULL) return;

  //DEBUG ((DEBUG_INFO, "IBB:\n"));
  //InternalDumpHex ((UINT8 *)BpmIbb,0x114 );

  IbbHashPtr = (HASH_LIST*)FindBpmElement(Bpm, BOOT_POLICY_MANIFEST_IBB_ELEMENT_DIGEST_ID);
  ASSERT (IbbHashPtr != NULL);
  if (IbbHashPtr == NULL) return;


  //
  // Initialize the DETAIL_PCR_DATA structure
  //

  //
  // Copy ACM policy status & ACM SVN
  //
  DetailPcrDataPtr = (UINT8*)&MaxDetailPcrData;
  ((DETAIL_PCR_DATA*)DetailPcrDataPtr)->AcmPolicySts = GetAcmPolicySts ();
  ((DETAIL_PCR_DATA*)DetailPcrDataPtr)->AcmSvn = Acm->AcmSvn;
  // Print values
  DEBUG ((DEBUG_INFO, "DetailPcrData:\n"));
  DEBUG ((DEBUG_INFO, "AcmPolicySts  - 0x%04lx\n", ((DETAIL_PCR_DATA*)DetailPcrDataPtr)->AcmPolicySts));
  DEBUG ((DEBUG_INFO, "AcmSvn        - 0x%04x\n", ((DETAIL_PCR_DATA*)DetailPcrDataPtr)->AcmSvn));
  //
  // Advance
  //
  DetailPcrDataSize = sizeof(((DETAIL_PCR_DATA*)DetailPcrDataPtr)->AcmPolicySts) + sizeof(((DETAIL_PCR_DATA*)DetailPcrDataPtr)->AcmSvn);
  DetailPcrDataPtr += DetailPcrDataSize;

  //
  // Copy ACM RSA signature
  //
  if (((ACM_HEADER *) Acm)->HeaderVersion == 0) {
    AcmSigSize = RSA_KEY_SIZE_2K / 8;
    CopyMem (
      DetailPcrDataPtr,
      (UINT8 *) ((ACM_HEADER *) Acm)->Rsa2048Sig,
      AcmSigSize);
  }
  else {
    AcmSigSize = RSA_KEY_SIZE_3K / 8;
    CopyMem (
      DetailPcrDataPtr,
      (UINT8 *) ((ACM_HEADER_3 *) Acm)->Rsa3072Sig,
      AcmSigSize);
  }
  //
  // Print values
  //
  DEBUG ((DEBUG_INFO, "AcmRsaSignature:  AcmSigSize= 0x%04x\n", AcmSigSize));
  InternalDumpHex (DetailPcrDataPtr, AcmSigSize);
  //
  // Advance
  //
  DetailPcrDataSize += AcmSigSize;
  DetailPcrDataPtr += AcmSigSize;

  //
  // Copy KM signature
  //

  CurrPos = ((UINT8*)Km + Km->KeySignatureOffset);

  if (((KEY_AND_SIGNATURE_STRUCT*)CurrPos)->KeyAlg == TPM_ALG_RSA) {

    // advance the pointer to version (1 byte) and Key_alg (2 byte)
    CurrPos = (UINT8 *) (CurrPos + sizeof(UINT8) + sizeof(UINT16));
    KeyModulusSize = (((KEY_STRUCT_HEADER *)(UINT8*)CurrPos)->KeySizeBits)/8; //modulus size in bytes
    KeyStructSize = sizeof(UINT8) + sizeof(UINT16) + sizeof(UINT32) + KeyModulusSize;
    CurrPos = CurrPos + KeyStructSize;

    // Here we have reached up to SigScheme
    if(*(UINT16*)CurrPos == TPM_ALG_RSASSA) {
      CurrPos += sizeof(UINT16);
      KmSigSize = (((SIGNATURE_STRUCT_HEADER*)CurrPos)->SigSizeBits)/8;
      CurrPos += sizeof(UINT8) + sizeof(UINT16) + sizeof(UINT16); //Sirsion( 1 byte) + sigsize (2 bytes) + hash_alg (2 bytes)

      //we have reached here to the signature data
      DEBUG ((DEBUG_INFO, "KmSignature:\n"));
      InternalDumpHex (CurrPos, KmSigSize);

      CopyMem (
        DetailPcrDataPtr,
        CurrPos,
        KmSigSize);
    }

  } else {
    DEBUG ((DEBUG_INFO, "Unsupported KeyAlg\n"));
  }

  DetailPcrDataSize += KmSigSize;
  DetailPcrDataPtr += KmSigSize;

  //
  // Copy BPM signature
  //

  CurrPos = NULL;
  CurrPos = ((UINT8*)Bpm + Bpm->KeySignatureOffset);
  DEBUG ((DEBUG_INFO, "BpmSignatureoffset:0x%04x\n", Bpm->KeySignatureOffset));


  if(((KEY_AND_SIGNATURE_STRUCT*)CurrPos)->KeyAlg == TPM_ALG_RSA) {

    // advance the pointer to version (1 byte) and Key_alg (2 byte)
    CurrPos = (UINT8 *) (CurrPos + sizeof(UINT8) + sizeof(UINT16));
    KeyModulusSize = (((KEY_STRUCT_HEADER *)(UINT8*) CurrPos)-> KeySizeBits)/8; //modulus size in bytes
    KeyStructSize = sizeof(UINT8) + sizeof(UINT16) + sizeof(UINT32) + KeyModulusSize;
    CurrPos = CurrPos + KeyStructSize;

    // Here we have reached up to SigScheme
    if(*(UINT16*)CurrPos == TPM_ALG_RSASSA) {
      CurrPos += sizeof(UINT16);
      BpmSigSize = (((SIGNATURE_STRUCT_HEADER*)CurrPos)->SigSizeBits)/8;
      CurrPos += sizeof(UINT8) + sizeof(UINT16) + sizeof(UINT16) ;//Sirsion( 1 byte) + sigsize (2 bytes) + hash_alg (2 bytes)

      //we have reached here to the signature data
      DEBUG ((DEBUG_INFO, "BpmSignature:\n"));
      InternalDumpHex (CurrPos, BpmSigSize);

      CopyMem (
        DetailPcrDataPtr,
        CurrPos,
        BpmSigSize);
    }

  } else {
    DEBUG ((DEBUG_INFO, "Unsupported KeyAlg\n"));
  }

  DetailPcrDataSize += BpmSigSize;
  DetailPcrDataPtr += BpmSigSize;

   CurrPos = (UINT8 *)IbbHashPtr;

  SavedDetailPcrDataSize = DetailPcrDataSize;

  IbbDigestCount = ((HASH_LIST*)CurrPos)->Count;
  DEBUG ((DEBUG_INFO, "IbbDigestCount = 0x%04x\n", IbbDigestCount));
  //past size and count field
  CurrPos += sizeof(UINT16) + sizeof(UINT16);

  for(Idx = 0; Idx < IbbDigestCount ; Idx++) {
    DEBUG ((DEBUG_INFO, "Idx = 0x%04x\n", Idx));
    DEBUG ((DEBUG_INFO, "ActivePcrBanks = 0x%x\n", ActivePcrBanks));

    if(((SHAX_HASH_STRUCTURE *)CurrPos)->HashAlg ==TPM_ALG_SHA1) {
      IbbDigestSize =  SHA1_DIGEST_SIZE;
      CurrPos += sizeof(UINT16) + sizeof(UINT16);
      if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA1) != 0) {
      CopyMem (
        DetailPcrDataPtr,
        CurrPos,
        IbbDigestSize);

      InternalDumpHex (CurrPos, IbbDigestSize);
      DetailPcrDataSize = SavedDetailPcrDataSize + IbbDigestSize;
      CreateSha1Hash ((UINT8*)&MaxDetailPcrData, DetailPcrDataSize, (UINT8 *)Sha1Digest);
      }
      CurrPos += IbbDigestSize;

    } else if(((SHAX_HASH_STRUCTURE *)CurrPos)->HashAlg ==TPM_ALG_SHA256) {
      IbbDigestSize =  SHA256_DIGEST_SIZE;
      CurrPos += sizeof(UINT16) + sizeof(UINT16);
      if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA256) != 0) {
      CopyMem (
        DetailPcrDataPtr,
        CurrPos,
        IbbDigestSize);

      InternalDumpHex (CurrPos, IbbDigestSize);
      DetailPcrDataSize = SavedDetailPcrDataSize + IbbDigestSize;
      CreateSha256Hash ((UINT8*)&MaxDetailPcrData, DetailPcrDataSize, (UINT8 *)Sha256Digest);
      }
      CurrPos += IbbDigestSize;

    } else if(((SHAX_HASH_STRUCTURE *)CurrPos)->HashAlg ==TPM_ALG_SHA384) {
      IbbDigestSize =  SHA384_DIGEST_SIZE;
      CurrPos += sizeof(UINT16) + sizeof(UINT16);
      if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA384) != 0) {
        CopyMem (
          DetailPcrDataPtr,
          CurrPos,
          IbbDigestSize);
        InternalDumpHex (CurrPos, IbbDigestSize);
        DetailPcrDataSize = SavedDetailPcrDataSize + IbbDigestSize;
        CreateSha384Hash ((UINT8*)&MaxDetailPcrData, DetailPcrDataSize, (UINT8 *)Sha384Digest);
      }
      CurrPos += IbbDigestSize;

    } else if(((SHAX_HASH_STRUCTURE *)CurrPos)->HashAlg ==TPM_ALG_SM3_256) {
      IbbDigestSize =  SM3_256_DIGEST_SIZE;
      CurrPos += sizeof(UINT16) + sizeof(UINT16);
      CurrPos += IbbDigestSize;

    } else if(((SHAX_HASH_STRUCTURE *)CurrPos)->HashAlg ==TPM_ALG_SHA512) {
      IbbDigestSize =  SHA512_DIGEST_SIZE;
      CurrPos += sizeof(UINT16) + sizeof(UINT16);
      CurrPos += IbbDigestSize;
    }
  }
}

/**
  Calculate AuthorityPCR extend value

  @param[out] SHA1   Authority PCR digest
  @param[out] SHA256 Authority PCR digest
**/
VOID
CalculateAuthorityPCRExtendValue (
  OUT UINT8 *Sha1Digest,
  OUT UINT8 *Sha256Digest
  )
{
  ACM_HEADER                               *Acm;
  KEY_MANIFEST_STRUCTURE                   *Km;
  MAX_AUTHORITY_PCR_DATA                   MaxAuthorityPcrData;

  UINT8  *AuthorityPcrDataPtr = (UINT8*)&MaxAuthorityPcrData;
  UINT32 AuthorityPcrDataSize;

  Acm = FindAcm ();
  ASSERT (Acm != NULL);
  if (Acm == NULL) return;

  Km = FindKm ();
  ASSERT (Km != NULL);
  if (Km == NULL) return;

  //
  // Initialize the AUTHORITY_PCR_DATA structure
  //

  //
  // Copy ACM policy status & ACM SVN
  //
  ((AUTHORITY_PCR_DATA*)AuthorityPcrDataPtr)->AcmPolicySts = GetAcmPolicySts ();
  ((AUTHORITY_PCR_DATA*)AuthorityPcrDataPtr)->AcmSvn = Acm->AcmSvn;
  // Print values
  DEBUG ((DEBUG_INFO, "AuthorityPcrData:\n"));
  DEBUG ((DEBUG_INFO, "AcmPolicySts  - 0x%04lx\n", ((AUTHORITY_PCR_DATA*)AuthorityPcrDataPtr)->AcmPolicySts));
  DEBUG ((DEBUG_INFO, "AcmSvn        - 0x%04x\n", ((AUTHORITY_PCR_DATA*)AuthorityPcrDataPtr)->AcmSvn));  //
  // Advance
  //
  AuthorityPcrDataSize = sizeof(((AUTHORITY_PCR_DATA*)AuthorityPcrDataPtr)->AcmPolicySts) + sizeof(((AUTHORITY_PCR_DATA*)AuthorityPcrDataPtr)->AcmSvn);
  AuthorityPcrDataPtr += AuthorityPcrDataSize;

  //
  // Calculate ACM Key hash by ourselves, or access hardware register?
  //
//TODO//  if (1) {
    *(UINT64*)&(((AUTHORITY_PCR_DATA*)AuthorityPcrDataPtr)->AcmKeyHash[0])  = MmioRead64 (ACM_KEY_HASH_MMIO_ADDR_0);
    *(UINT64*)&(((AUTHORITY_PCR_DATA*)AuthorityPcrDataPtr)->AcmKeyHash[8])  = MmioRead64 (ACM_KEY_HASH_MMIO_ADDR_1);
    *(UINT64*)&(((AUTHORITY_PCR_DATA*)AuthorityPcrDataPtr)->AcmKeyHash[16]) = MmioRead64 (ACM_KEY_HASH_MMIO_ADDR_2);
    *(UINT64*)&(((AUTHORITY_PCR_DATA*)AuthorityPcrDataPtr)->AcmKeyHash[24]) = MmioRead64 (ACM_KEY_HASH_MMIO_ADDR_3);
//TODO//  } else {
//TODO//    CreateSha256Hash ((UINT8 *)&Acm->RsaPubKey, sizeof(Acm->RsaPubKey), (UINT8 *)&AuthorityPcrData.AcmKeyHash);
//TODO//  }
  //
  // Calculate BP Key hash by ourselves, because we can NOT access hardware register.
  //
//TODO//  CreateSha256Hash ((UINT8 *)&Km->KeyManifestSignature.Key.Modulus, sizeof(Km->KeyManifestSignature.Key.Modulus), (UINT8 *)&AuthorityPcrData.BpKeyHash);

//TODO//  CopyMem (&AuthorityPcrData.BpmKeyHashFromKm, &Km->BpKey.HashBuffer, sizeof(AuthorityPcrData.BpmKeyHashFromKm));

//TODO//  CreateSha1Hash ((UINT8 *)&AuthorityPcrData, sizeof(AuthorityPcrData), (UINT8 *)Sha1Digest);
//TODO//  CreateSha256Hash ((UINT8 *)&AuthorityPcrData, sizeof(AuthorityPcrData), (UINT8 *)Sha256Digest);
}

/**
  Check if we need AuthorityPCR measurement

  @retval TRUE  Need AuthorityPCR measurement
  @retval FALSE Do NOT need AuthorityPCR measurement
**/
BOOLEAN
NeedAuthorityMeasure (
  VOID
  )
{
  BOOT_POLICY_MANIFEST_HEADER              *Bpm;
  IBB_ELEMENT                              *BpmIbb;

  Bpm = FindBpm ();
  ASSERT (Bpm != NULL);
  if (Bpm == NULL) return FALSE;

  BpmIbb = FindBpmIbb (Bpm);
  ASSERT (BpmIbb != NULL);
  if (BpmIbb == NULL) return FALSE;

  if ((BpmIbb->Flags & IBB_FLAG_AUTHORITY_MEASURE) != 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Check if we need to add event for locality 3 startup

  @retval TRUE  Need Locality Event
  @retval FALSE Do NOT need Locality Event
**/
BOOLEAN
NeedLocalityEvent (
  VOID
  )
{
  BOOT_POLICY_MANIFEST_HEADER              *Bpm;
  IBB_ELEMENT                              *BpmIbb;

  Bpm = FindBpm ();
  ASSERT (Bpm != NULL);
  if (Bpm == NULL) return FALSE;

  BpmIbb = FindBpmIbb (Bpm);
  ASSERT (BpmIbb != NULL);
  if (BpmIbb == NULL) return FALSE;
  DEBUG ((DEBUG_INFO, "BpmIbb->Flags %x\n", BpmIbb->Flags));

  if ((BpmIbb->Flags & IBB_FLAG_INITIAL_MEASURE_LOC3) != 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Create DetailPCR event log

  @param[in] TpmType        TPM type
  @param[in] ActivePcrBanks Active PCR Banks
**/
VOID
CreateDetailPCREvent (
  IN UINT8              TpmType,
  IN UINT32             ActivePcrBanks
  )
{
  TCG_PCR_EVENT_HDR         NewEventHdr;
  UINT8                     Sha1[SHA1_DIGEST_SIZE];
  UINT8                     Sha256[SHA256_DIGEST_SIZE];
  UINT8                     Sha384[SHA384_DIGEST_SIZE];
  TPML_DIGEST_VALUES        DigestList;

  NewEventHdr.PCRIndex  = 0;
  NewEventHdr.EventType = EV_S_CRTM_CONTENTS;
  CalculateDetailPCRExtendValue (ActivePcrBanks,Sha1, Sha256, Sha384);
  DEBUG ((DEBUG_INFO, "CreateDetailPCREvent()\n"));

  ZeroMem (&DigestList, sizeof(DigestList));
  if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA1) != 0) {
    DigestList.digests[DigestList.count].hashAlg = TPM_ALG_SHA1;
    CopyMem (DigestList.digests[DigestList.count].digest.sha1, Sha1, SHA1_DIGEST_SIZE);
    DigestList.count ++;
  }
  if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA256) != 0) {
    DigestList.digests[DigestList.count].hashAlg = TPM_ALG_SHA256;
    CopyMem (DigestList.digests[DigestList.count].digest.sha256, Sha256, SHA256_DIGEST_SIZE);
    DigestList.count ++;
  }

  if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA384) != 0) {
    DigestList.digests[DigestList.count].hashAlg = TPM_ALG_SHA384;
    CopyMem (DigestList.digests[DigestList.count].digest.sha384, Sha384, SHA384_DIGEST_SIZE);
    DigestList.count ++;
  }
  if (((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA512) != 0) ||
      ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SM3_256) != 0)) {
    DEBUG ((DEBUG_INFO, "Unsupported PCR bank\n"));
  }

  if (IsNpwAcm()) {
    NewEventHdr.EventSize = sizeof ("Boot Guard Debug Measured S-CRTM");
    LogHashEvent (&DigestList, &NewEventHdr, (UINT8 *) "Boot Guard Debug Measured S-CRTM");
  } else {
    NewEventHdr.EventSize = sizeof ("Boot Guard Measured S-CRTM");
    LogHashEvent (&DigestList, &NewEventHdr, (UINT8 *) "Boot Guard Measured S-CRTM");
  }

  DEBUG ((DEBUG_INFO, "End of CreateDetailPCREvent()\n"));
}

/**
  Create AuthorityPCR event log

  @param[in] TpmType        TPM type
  @param[in] ActivePcrBanks Active PCR Banks
**/
VOID
CreateAuthorityPCREvent (
  IN UINT8              TpmType,
  IN UINT32             ActivePcrBanks
  )
{
  TCG_PCR_EVENT_HDR         NewEventHdr;
  UINT8                     Sha1[SHA1_DIGEST_SIZE];
  UINT8                     Sha256[SHA256_DIGEST_SIZE];
  TPML_DIGEST_VALUES        DigestList;

  if (NeedAuthorityMeasure() && IsVerifiedBoot()) {
    if (TpmType == TPM_DEVICE_1_2) {
      NewEventHdr.PCRIndex  = 6;
    } else {
      NewEventHdr.PCRIndex  = 7;
    }
    NewEventHdr.EventType = EV_EFI_VARIABLE_DRIVER_CONFIG;
    CalculateAuthorityPCRExtendValue (Sha1, Sha256);

    ZeroMem (&DigestList, sizeof(DigestList));
    if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA1) != 0) {
      DigestList.digests[DigestList.count].hashAlg = TPM_ALG_SHA1;
      CopyMem (DigestList.digests[DigestList.count].digest.sha1, Sha1, SHA1_DIGEST_SIZE);
      DigestList.count ++;
    }
    if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA256) != 0) {
      DigestList.digests[DigestList.count].hashAlg = TPM_ALG_SHA256;
      CopyMem (DigestList.digests[DigestList.count].digest.sha256, Sha256, SHA256_DIGEST_SIZE);
      DigestList.count ++;
    }

    if (IsNpwAcm()) {
      NewEventHdr.EventSize = sizeof (L"Boot Guard Debug Measured S-CRTM");
      LogHashEvent (&DigestList, &NewEventHdr, (UINT8 *)L"Boot Guard Debug Measured S-CRTM");
    } else {
      NewEventHdr.EventSize = sizeof (L"Boot Guard Measured S-CRTM");
      LogHashEvent (&DigestList, &NewEventHdr, (UINT8 *)L"Boot Guard Measured S-CRTM");
    }
  }
}

/**
  Create Locality Startup event entry

  @param[in] TpmType        TPM type
  @param[in] ActivePcrBanks Active PCR Banks
**/
VOID
CreateLocalityStartupEvent (
  IN UINT8              TpmType,
  IN UINT32             ActivePcrBanks
  )
{
  TCG_PCR_EVENT_HDR                NewEventHdr;
  UINT8                            Sha1[SHA1_DIGEST_SIZE];
  UINT8                            Sha256[SHA256_DIGEST_SIZE];
  UINT8                            Sha384[SHA384_DIGEST_SIZE];
  TPML_DIGEST_VALUES               DigestList;
  TCG_EFI_STARTUP_LOCALITY_EVENT   LocalityEventData;

  if (NeedLocalityEvent()) {
    ZeroMem (&Sha1, SHA1_DIGEST_SIZE);
    ZeroMem (&Sha256, SHA256_DIGEST_SIZE);
    ZeroMem (&Sha384, SHA384_DIGEST_SIZE);

    NewEventHdr.PCRIndex  = 0;
    NewEventHdr.EventType = EV_NO_ACTION;

    ZeroMem (&DigestList, sizeof(DigestList));

    if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA1) != 0) {
      DigestList.digests[DigestList.count].hashAlg = TPM_ALG_SHA1;
      CopyMem (DigestList.digests[DigestList.count].digest.sha1, Sha1, SHA1_DIGEST_SIZE);
      DigestList.count ++;
    }

    if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA256) != 0) {
      DigestList.digests[DigestList.count].hashAlg = TPM_ALG_SHA256;
      CopyMem (DigestList.digests[DigestList.count].digest.sha256, Sha256, SHA256_DIGEST_SIZE);
      DigestList.count ++;
    }

    if ((ActivePcrBanks & EFI_TCG2_BOOT_HASH_ALG_SHA384) != 0) {
      DigestList.digests[DigestList.count].hashAlg = TPM_ALG_SHA384;
      CopyMem (DigestList.digests[DigestList.count].digest.sha384, Sha384, SHA384_DIGEST_SIZE);
      DigestList.count ++;
    }

    NewEventHdr.EventSize = sizeof (TCG_EFI_STARTUP_LOCALITY_EVENT);

    CopyMem (LocalityEventData.Signature, (UINT8 *) "StartupLocality", sizeof ("StartupLocality"));
    LocalityEventData.StartupLocality = 0x03;

    LogHashEvent (&DigestList, &NewEventHdr,(UINT8 *) &LocalityEventData);
  }
}


/**
  Get Active PCR Banks.

  @retval UINT32  Number of PCR Banks.
**/

UINT32
GetActivePcrBanks (
  VOID
  )
{
  EFI_STATUS           Status;
  UINT32               ActivePcrBanks;
  TPML_PCR_SELECTION   Pcrs;
  UINTN                Index;

  DEBUG ((DEBUG_INFO, "GetActivePcrBank!\n"));

  Status = Tpm2GetCapabilityPcrs (&Pcrs);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Tpm2GetCapabilityPcrs fail!\n"));
    ActivePcrBanks = EFI_TCG2_BOOT_HASH_ALG_SHA1;
  } else {
    DEBUG ((DEBUG_INFO, "Tpm2GetCapabilityPcrs Count - %08x\n", Pcrs.count));
    ActivePcrBanks = 0;
    for (Index = 0; Index < Pcrs.count; Index++) {
      DEBUG ((DEBUG_INFO, "hash - %x\n", Pcrs.pcrSelections[Index].hash));
      switch (Pcrs.pcrSelections[Index].hash) {
      case TPM_ALG_SHA1:
        if (!IsZeroBufferLocal (Pcrs.pcrSelections[Index].pcrSelect, Pcrs.pcrSelections[Index].sizeofSelect)) {
          ActivePcrBanks |= EFI_TCG2_BOOT_HASH_ALG_SHA1;
        }
        break;
      case TPM_ALG_SHA256:
        if (!IsZeroBufferLocal (Pcrs.pcrSelections[Index].pcrSelect, Pcrs.pcrSelections[Index].sizeofSelect)) {
          ActivePcrBanks |= EFI_TCG2_BOOT_HASH_ALG_SHA256;
        }
        break;
      case TPM_ALG_SHA384:
        if (!IsZeroBufferLocal (Pcrs.pcrSelections[Index].pcrSelect, Pcrs.pcrSelections[Index].sizeofSelect)) {
          ActivePcrBanks |= EFI_TCG2_BOOT_HASH_ALG_SHA384;
        }
        break;
      case TPM_ALG_SHA512:
        if (!IsZeroBufferLocal (Pcrs.pcrSelections[Index].pcrSelect, Pcrs.pcrSelections[Index].sizeofSelect)) {
          ActivePcrBanks |= EFI_TCG2_BOOT_HASH_ALG_SHA512;
        }
        break;
      case TPM_ALG_SM3_256:
        if (!IsZeroBufferLocal (Pcrs.pcrSelections[Index].pcrSelect, Pcrs.pcrSelections[Index].sizeofSelect)) {
          ActivePcrBanks |= EFI_TCG2_BOOT_HASH_ALG_SM3_256;
        }
        break;
      }
    }
  }
  return ActivePcrBanks;
}

/**
  Create Boot Guard TPM event log

  @param[in] TpmType TPM type
**/
VOID
CreateTpmEventLog (
  IN UINT8              TpmType
  )
{
  UINT32               ActivePcrBanks;
  EFI_STATUS           Status;

  DEBUG ((DEBUG_INFO, "CreateTpmEventLog()\n"));

  //
  // Initialize TPM device
  //
  Status = Tpm2RequestUseTpm ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "TPM2 not detected!\n"));
  }

  ActivePcrBanks = GetActivePcrBanks ();

  if (IsMeasuredBoot()) {
    CreateLocalityStartupEvent (TpmType, ActivePcrBanks);
    CreateDetailPCREvent (TpmType, ActivePcrBanks);
    CreateAuthorityPCREvent (TpmType, ActivePcrBanks);
  }

  DEBUG ((DEBUG_INFO, "End of CreateTpmEventLog()\n"));
}

/**
  If Boot Guard already measured IBB, we do not need let TPM measure it again.
  So we need register this PPI to let TPM driver know this Fv should be
  excluded. This data should be consistent as the data in BiosInfo driver.
**/
VOID
ExcludeIbbFv (
  VOID
  )
{
  DEBUG ((DEBUG_INFO, "Excluding FV recovery as Boot Guard did Measurement of PEI FV\n"));
  PeiServicesInstallPpi (&mPeiFirmwareVolumeInfoMeasurementExcludedPpiList);
}

/**
  Create various events in the event log as required for Bootguard Enabled Boot

  @retval EFI_SUCCES             Events created successfully
  @retval Others                 Bootguard not supported
**/
EFI_STATUS
EFIAPI
CreateBootguardEventLogEntries (
  IN BOOT_GUARD_INFO *BootGuardInfo
  )
{
  UINT32 MeFwSts4;

  if (BootGuardInfo->BootGuardCapability == TRUE) {
    //
    // Skip TPM event log if TPM 1.2 device is deactivated.
    //
    MeFwSts4 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS_4));
    if ((MeFwSts4 & B_TPM1_2_DEACTIVATED) == 0) {
      //
      // Create TPM event log if not Sx Resume Type - S3/Deep-S3/FFS Resume
      // Note: S4->S0 is similar to S5->S0
      //
      if(BootGuardInfo->ByPassTpmEventLog != TRUE) {
        DEBUG ((DEBUG_INFO, "BIOS is Creating Event Log for ACM measurements\n"));
        CreateTpmEventLog ((UINT8) (BootGuardInfo->TpmType));
        //
        // If Boot Guard already measured IBB, we do not need let TPM measure it again.
        //
        if (IsMeasuredBoot()) {
          ExcludeIbbFv();
        }
      }
    }
  } else {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
Update Tpm Policy for Boot Guard

@param[in] BootGuardInfo - Pointer to BootGuardInfo.

@retval EFI_SUCCES             Convert variable to PCD successfully.
@retval EFI_UNSUPPORTED        Boot Guard or Boot Guard measure boot is not support.
**/
EFI_STATUS
UpdateBootGuardTpmPolicy (
  IN BOOT_GUARD_INFO *BootGuardInfo
  )
{
  UINTN           Size;

  Size = sizeof (EFI_GUID);

  DEBUG ((DEBUG_INFO, "Boot Guard Policy Initialization\n"));

  //
  // Check if platform supports Boot Guard
  //
  if (BootGuardInfo->BootGuardCapability == TRUE) {
    DEBUG ((DEBUG_INFO, "Boot Guard Support is enabled on Platform\n"));
    //
    // If Boot Guard is supported, check if ME FW indcates to Disconnect All TPM's
    //
    if (BootGuardInfo->DisconnectAllTpms == TRUE) {
      //
      // RPPO-KBL-0057: RoyalParkOverrideBegin
      //
      PcdSetPtrS (PcdTpmInstanceGuid, &Size, &gEfiTpmDeviceInstanceNoneGuid);
      DEBUG ((DEBUG_INFO, "Boot Guard - All TPM's are Disconnected\n"));
    } else {
    if (BootGuardInfo->MeasuredBoot == FALSE) {
      //
      // No TPM initiated by ACM. BIOS to continue measured boot
      // based on BIOS Policies.
      //
      DEBUG ((DEBUG_INFO, "Boot Guard - MeasuredBoot == FALSE\n"));
      return EFI_UNSUPPORTED;
    }

    if (BootGuardInfo->BypassTpmInit == TRUE) {
      //
      // 1. Identify TPM Type Selected by ACM
      // 2. Skip TPM Startup & SCRTM
      // 3. Bypass TPM Extends in BIOS for PEI FV
      //
      DEBUG ((DEBUG_INFO, "TPM is Successfully initialized by Boot Guard ACM\n"));
      switch (BootGuardInfo->TpmType) {
        case dTpm12:
          PcdSet8S (PcdTpmInitializationPolicy, 0);
          DEBUG ((DEBUG_INFO, "Boot Guard - dTPM 1.2\n"));
          break;

        case dTpm20:
          PcdSet8S (PcdTpm2InitializationPolicy, 0);
          DEBUG ((DEBUG_INFO, "Boot Guard - dTPM 2.0\n"));
          break;

        case Ptt:
          PcdSet8S (PcdTpm2InitializationPolicy, 0);
          PcdSet8S (PcdTpm2SelfTestPolicy, 0);
          DEBUG ((DEBUG_INFO, "Boot Guard - PTT\n"));
          break;

        default:
          //
          // Unknown Type
          //
          ASSERT (FALSE);
          break;
        }
      } else {
        //
        // If ACM fails to initialize TPM successfully BIOS should
        // Try to Enumerate TPM
        //
        PcdSetPtrS (PcdTpmInstanceGuid, &Size, &gEfiTpmDeviceInstanceNoneGuid);
        return EFI_UNSUPPORTED;
      } // End TPM Success
    } // End Disconnect All TPM's flow
  } else {
    return EFI_UNSUPPORTED;
  } // End BootGuardCapability

  return EFI_SUCCESS;
}

/**
UsbIo installation notification function.

This function finds out all the current USB IO PPIs in the system and add them
into private data.

@param  PeiServices      Indirect reference to the PEI Services Table.
@param  NotifyDesc       Address of the notification descriptor data structure.
@param  InvokePpi        Address of the PPI that was invoked.

@retval EFI_SUCCESS      The function completes successfully.

**/
EFI_STATUS
EFIAPI
ConfigurePttBootGuard (
  IN  EFI_PEI_SERVICES              **PeiServices,
  IN  EFI_PEI_NOTIFY_DESCRIPTOR     *NotifyDesc,
  IN  VOID                          *InvokePpi
  )
{
  UINT8                           RegRead;
  BOOT_GUARD_INFO                 BootGuardInfo;
  UINT32                          PttFtifReg;

  DEBUG ((DEBUG_INFO, "ConfigurePttBootGuard notify function\n"));

  ZeroMem (&BootGuardInfo, sizeof(BOOT_GUARD_INFO));
  GetBootGuardInfo (&BootGuardInfo);
  CreateBootguardEventLogEntries (&BootGuardInfo);
  UpdateBootGuardTpmPolicy (&BootGuardInfo);

  RegRead = MmioRead8 ((UINTN)PcdGet64 (PcdTpmBaseAddress) + 0x30);
  PttFtifReg = MmioRead32 (R_PTT_TXT_STS_FTIF);
  DEBUG ((EFI_D_INFO, "PttFtifReg: %x\n", PttFtifReg));

  if ((RegRead != 0xFF) && ((PttFtifReg & V_FTIF_FTPM_PRESENT) == V_FTIF_FTPM_PRESENT)) {
    DEBUG ((DEBUG_INFO, "PTT detected\n"));
  }

  return EFI_SUCCESS;
}

EFI_PEI_NOTIFY_DESCRIPTOR        mNotifyList = {
  EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gEfiTpmDeviceSelectedGuid,
  ConfigurePttBootGuard
};

/**
The constructor reads variable and sets HOB

@param  FileHandle   The handle of FFS header the loaded driver.
@param  PeiServices  The pointer to the PEI services.

@retval EFI_SUCCESS  The constructor always returns EFI_SUCCESS.

**/
EFI_STATUS
EFIAPI
ConfigurePttBootGuardConstructor (
  IN EFI_PEI_FILE_HANDLE        FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  DEBUG ((DEBUG_INFO, "ConfigurePttBootGuardConstructor Entry\n"));
  PeiServicesNotifyPpi (&mNotifyList);

  return EFI_SUCCESS;
}

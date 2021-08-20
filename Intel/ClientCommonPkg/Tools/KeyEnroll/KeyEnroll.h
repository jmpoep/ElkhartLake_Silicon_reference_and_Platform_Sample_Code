//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Definitions for the KeyEnroll utility.

Copyright (c) 2014 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation
(if any) is furnished under a license and may only be used or
copied in accordance with the terms of the license.  Except as
permitted by such license, no part of this software or
documentation may be reproduced, stored in a retrieval system, or
transmitted in any form or by any means without the express written
consent of Intel Corporation.

**/

#ifndef _KEY_ENROLL_H
#define _KEY_ENROLL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define PI_SPECIFICATION_VERSION  0x00010000
#define EFI_FVH_PI_REVISION       EFI_FVH_REVISION
#include <Common/UefiBaseTypes.h>
#include <Common/PiFirmwareFile.h>
#include <Common/PiFirmwareVolume.h>
#include <Common/UefiMultiPhase.h>
#include <Guid/PiFirmwareFileSystem.h>
#include <IndustryStandard/PeImage.h>
#include "EfiUtilityMsgs.h"
#include "CommonLib.h"
#include "ParseInf.h"

// require libeay32.lib user32.lib advapi32.lib gdi32.lib
#include <openssl/evp.h>
#include <openssl/x509.h>

//
// UEFI 2.4 - start
//
#define EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS   0x00000020
#define EFI_VARIABLE_APPEND_WRITE                            0x00000040

#define EFI_IMAGE_SECURITY_DATABASE       L"db"
#define EFI_IMAGE_SECURITY_DATABASE1      L"dbx"
#define EFI_IMAGE_SECURITY_DATABASE2      L"dbt"
#define EFI_PLATFORM_KEY_NAME             L"PK"
#define EFI_KEY_EXCHANGE_KEY_NAME         L"KEK"

#define EFI_IMAGE_SECURITY_DATABASE_GUID \
  { \
    0xd719b2cb, 0x3d3a, 0x4596, { 0xa3, 0xbc, 0xda, 0xd0, 0xe, 0x67, 0x65, 0x6f } \
  }
#define EFI_GLOBAL_VARIABLE \
  { \
    0x8BE4DF61, 0x93CA, 0x11d2, {0xAA, 0x0D, 0x00, 0xE0, 0x98, 0x03, 0x2B, 0x8C } \
  }

#define EFI_CERT_RSA2048_GUID \
  { \
    0x3c5766e8, 0x269c, 0x4e34, {0xaa, 0x14, 0xed, 0x77, 0x6e, 0x85, 0xb3, 0xb6} \
  }

#define EFI_CERT_X509_GUID \
  { \
    0xa5c059a1, 0x94e4, 0x4aa7, {0x87, 0xb5, 0xab, 0x15, 0x5c, 0x2b, 0xf0, 0x72} \
  }

#define EFI_CERT_SHA1_GUID \
  { \
    0x826ca512, 0xcf10, 0x4ac9, {0xb1, 0x87, 0xbe, 0x1, 0x49, 0x66, 0x31, 0xbd} \
  }

#define EFI_CERT_SHA256_GUID \
  { \
    0xc1c41626, 0x504c, 0x4092, {0xac, 0xa9, 0x41, 0xf9, 0x36, 0x93, 0x43, 0x28} \
  }

#define EFI_CERT_SHA384_GUID \
  { \
    0xff3e5307, 0x9fd0, 0x48c9, {0x85, 0xf1, 0x8a, 0xd5, 0x6c, 0x70, 0x1e, 0x1} \
  }

#define EFI_CERT_SHA512_GUID \
  { \
    0x93e0fae, 0xa6c4, 0x4f50, {0x9f, 0x1b, 0xd4, 0x1e, 0x2b, 0x89, 0xc1, 0x9a} \
  }

#define EFI_CERT_X509_SHA256_GUID \
  { \
    0x3bd2a492, 0x96c0, 0x4079, {0xb4, 0x20, 0xfc, 0xf9, 0x8e, 0xf1, 0x03, 0xed } \
  }

#define EFI_CERT_X509_SHA384_GUID \
  { \
    0x7076876e, 0x80c2, 0x4ee6, {0xaa, 0xd2, 0x28, 0xb3, 0x49, 0xa6, 0x86, 0x5b } \
  }

#define EFI_CERT_X509_SHA512_GUID \
  { \
    0x446dbf63, 0x2502, 0x4cda, {0xbc, 0xfa, 0x24, 0x65, 0xd2, 0xb0, 0xfe, 0x9d } \
  }

#define EFI_CERT_TYPE_PKCS7_GUID \
  { \
    0x4aafd29d, 0x68df, 0x49ee, {0x8a, 0xa9, 0x34, 0x7d, 0x37, 0x56, 0x65, 0xa7} \
  }

#define WIN_CERT_TYPE_PKCS_SIGNED_DATA 0x0002

#pragma pack(1)

typedef struct {
  ///
  /// An identifier which identifies the agent which added the signature to the list.
  ///
  EFI_GUID          SignatureOwner;
  ///
  /// The format of the signature is defined by the SignatureType.
  ///
  UINT8             SignatureData[1];
} EFI_SIGNATURE_DATA;

typedef struct {
  ///
  /// Type of the signature. GUID signature types are defined in below.
  ///
  EFI_GUID            SignatureType;
  ///
  /// Total size of the signature list, including this header.
  ///
  UINT32              SignatureListSize;
  ///
  /// Size of the signature header which precedes the array of signatures.
  ///
  UINT32              SignatureHeaderSize;
  ///
  /// Size of each signature.
  ///
  UINT32              SignatureSize;
  ///
  /// Header before the array of signatures. The format of this header is specified
  /// by the SignatureType.
  /// UINT8           SignatureHeader[SignatureHeaderSize];
  ///
  /// An array of signatures. Each signature is SignatureSize bytes in length.
  /// EFI_SIGNATURE_DATA Signatures[][SignatureSize];
  ///
} EFI_SIGNATURE_LIST;

typedef UINT8  EFI_SHA256_HASH[32];
typedef UINT8  EFI_SHA384_HASH[48];
typedef UINT8  EFI_SHA512_HASH[64];

typedef struct {
  ///
  /// The SHA256 hash of an X.509 certificate's To-Be-Signed contents.
  ///
  EFI_SHA256_HASH     ToBeSignedHash;
  ///
  /// The time that the certificate shall be considered to be revoked.
  ///
  EFI_TIME            TimeOfRevocation;
} EFI_CERT_X509_SHA256;

typedef struct {
  ///
  /// The SHA384 hash of an X.509 certificate's To-Be-Signed contents.
  ///
  EFI_SHA384_HASH     ToBeSignedHash;
  ///
  /// The time that the certificate shall be considered to be revoked.
  ///
  EFI_TIME            TimeOfRevocation;
} EFI_CERT_X509_SHA384;

typedef struct {
  ///
  /// The SHA512 hash of an X.509 certificate's To-Be-Signed contents.
  ///
  EFI_SHA512_HASH     ToBeSignedHash;
  ///
  /// The time that the certificate shall be considered to be revoked.
  ///
  EFI_TIME            TimeOfRevocation;
} EFI_CERT_X509_SHA512;

#pragma pack()

//
// UEFI 2.4 - end
//

#define WIN_CERT_UEFI_RSA2048_SIZE               256

//
// ASN.1
//
#define TWO_BYTE_ENCODE       0x82

//
// SHA-1 digest size in bytes.
//
#define SHA1_DIGEST_SIZE    20
//
// SHA-256 digest size in bytes
//
#define SHA256_DIGEST_SIZE  32
//
// SHA-384 digest size in bytes
//
#define SHA384_DIGEST_SIZE  48
//
// SHA-512 digest size in bytes
//
#define SHA512_DIGEST_SIZE  64
//
// Set max digest size as SHA512 Output (64 bytes) by far
//
#define MAX_DIGEST_SIZE    SHA512_DIGEST_SIZE

//
// Support hash types
//
#define HASHALG_SHA1                           0x00000000
#define HASHALG_SHA256                         0x00000001
#define HASHALG_SHA384                         0x00000002
#define HASHALG_SHA512                         0x00000003
#define HASHALG_MAX                            0x00000004

typedef struct {
  CHAR16                   *Name;           ///< Name for Hash Algorithm
  UINTN                    DigestLength;    ///< Digest Length
  UINT8                    *OidValue;       ///< Hash Algorithm OID ASN.1 Value
  UINTN                    OidLength;       ///< Length of Hash OID Value
} HASH_TABLE;

//
// We define another format of 5th directory entry: security directory
//
typedef struct {
  UINT32               Offset;      // Offset of certificate
  UINT32               SizeOfCert;  // size of certificate appended
} EFI_IMAGE_SECURITY_DATA_DIRECTORY;

//
//
// PKCS7 Certificate definition
//
#pragma pack (push, 1)
typedef struct {
  WIN_CERTIFICATE Hdr;
  UINT8           CertData[1];
} WIN_CERTIFICATE_EFI_PKCS;
#pragma pack (pop)

//
// Cryptograhpic Key Information
//
#pragma pack (push, 1)
typedef struct _CPL_KEY_INFO {
  UINT32                            KeyLengthInBits;    // Key Length In Bits
  UINT32                            BlockSize;          // Operation Block Size in Bytes
  UINT32                            CipherBlockSize;    // Output Cipher Block Size in Bytes
  UINT32                            KeyType;            // Key Type
  UINT32                            CipherMode;         // Cipher Mode for Symmetric Algorithm
  UINT32                            Flags;              // Additional Key Property Flags
} CPL_KEY_INFO;
#pragma pack (pop)



//
// Utility Name
//
#define UTILITY_NAME  "KeyEnroll"

//
// Utility version information
//
#define UTILITY_MAJOR_VERSION 0
#define UTILITY_MINOR_VERSION 10
#define UTILITY_DATE          __DATE__

//
// The maximum number of arguments accepted from the command line.
//
#define MIN_ARGS        4
#define BUF_SIZE        (8 * 1024)

#define EFI_SYSTEM_NV_DATA_FV_GUID \
  {0xfff12b8d, 0x7696, 0x4c8b, {0xa9, 0x85, 0x27, 0x47, 0x7, 0x5b, 0x4f, 0x50} }

///
/// LIST_ENTRY structure definition.
///
typedef struct _LIST_ENTRY {
  struct _LIST_ENTRY  *ForwardLink;
  struct _LIST_ENTRY  *BackLink;
} LIST_ENTRY;

#define CR(Record, TYPE, Field, TestSignature)  ((TYPE *) ((CHAR8 *) (Record) - (CHAR8 *) &(((TYPE *) 0)->Field)))

#define SIGNATURE_16(A, B)        ((A) | (B << 8))
#define SIGNATURE_32(A, B, C, D)  (SIGNATURE_16 (A, B) | (SIGNATURE_16 (C, D) << 16))

typedef struct {
  UINTN  EfiVariableAddr;
} G_EFI_FD_INFO;

#define VARIABLE_INFO_PRIVATE_SIGNATURE  SIGNATURE_32 ('V', 'K', 'E', 'S')

typedef struct {
  UINTN            Signature;
  LIST_ENTRY       Link;

  EFI_GUID         Guid;
  CHAR16           *Name;
  UINT32           Attributes;
  EFI_TIME         TimeStamp;
  UINTN            Size;
  UINT8            *Buffer;
} VARIABLE_INFO_PRIVATE;

#define VARIABLE_INFO_PRIVATE_FROM_LINK(a)  CR (a, VARIABLE_INFO_PRIVATE, Link, VARIABLE_INFO_PRIVATE_SIGNATURE)

///
/// When the attribute EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS is
/// set, then the Data buffer shall begin with an instance of a complete (and serialized)
/// EFI_VARIABLE_AUTHENTICATION_2 descriptor. The descriptor shall be followed by the new
/// variable value and DataSize shall reflect the combined size of the descriptor and the new
/// variable value. The authentication descriptor is not part of the variable data and is not
/// returned by subsequent calls to GetVariable().
///
typedef struct {
  ///
  /// For the TimeStamp value, components Pad1, Nanosecond, TimeZone, Daylight and
  /// Pad2 shall be set to 0. This means that the time shall always be expressed in GMT.
  ///
  EFI_TIME                    TimeStamp;
  ///
  /// Only a CertType of  EFI_CERT_TYPE_PKCS7_GUID is accepted.
  ///
  WIN_CERTIFICATE_UEFI_GUID   AuthInfo;
 } EFI_VARIABLE_AUTHENTICATION_2;


#define AUTHINFO2_SIZE(VarAuth2) ((OFFSET_OF (EFI_VARIABLE_AUTHENTICATION_2, AuthInfo)) + \
                                  (UINTN) ((EFI_VARIABLE_AUTHENTICATION_2 *) (VarAuth2))->AuthInfo.Hdr.dwLength)

extern G_EFI_FD_INFO               gEfiFdInfo;

#define FREE_NON_NULL_PTR(Pointer)      \
  do {                                  \
    if ((Pointer) != NULL) {            \
      free ((Pointer));                 \
      (Pointer) = NULL;                 \
    }                                   \
  } while(FALSE)

//
//  Command operation type.
//
typedef enum {
  VariableTypeAdd,                // Indicate to create variable.
  VariableTypeDel,                // Indicate to delete.
  VariableTypeAppend,             // Indicate to append.
  VariableTypeMax                 // Invalid type
} EFI_COMMAND_OPER_TYPE;

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
;

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
;

INTN
KeyEnrollStrCmp (
  IN      CONST CHAR16              *FirstString,
  IN      CONST CHAR16              *SecondString
  );

UINTN
KeyEnrollStrLen (
  IN      CONST CHAR16              *String
  );

UINTN
KeyEnrollStrSize (
  IN      CONST CHAR16              *String
  );

INTN
CompareMem (
  IN      CONST VOID                *DestinationBuffer,
  IN      CONST VOID                *SourceBuffer,
  IN      UINTN                     Length
  );

LIST_ENTRY *
EFIAPI
GetFirstNode (
  IN      CONST LIST_ENTRY          *List
  );

BOOLEAN
EFIAPI
IsNull (
  IN      CONST LIST_ENTRY          *List,
  IN      CONST LIST_ENTRY          *Node
  );

LIST_ENTRY *
EFIAPI
GetNextNode (
  IN      CONST LIST_ENTRY          *List,
  IN      CONST LIST_ENTRY          *Node
  );

LIST_ENTRY *
EFIAPI
InitializeListHead (
  IN OUT  LIST_ENTRY                *ListHead
  );

LIST_ENTRY *
EFIAPI
InsertTailList (
  IN OUT  LIST_ENTRY                *ListHead,
  IN OUT  LIST_ENTRY                *Entry
  );

LIST_ENTRY *
EFIAPI
RemoveEntryList (
  IN      CONST LIST_ENTRY          *Entry
  );

BOOLEAN
EFIAPI
IsListEmpty (
  IN      CONST LIST_ENTRY          *ListHead
  );

BOOLEAN
CompareTimeStamp (
  IN EFI_TIME               *FirstTime,
  IN EFI_TIME               *SecondTime
  );

VOID
Ascii2UnicodeString (
  IN  CHAR8    *String,
  OUT CHAR16   *UniString
  );

BOOLEAN
EFIAPI
X509GetTBSCert (
  IN  CONST UINT8  *Cert,
  IN  UINTN        CertSize,
  OUT UINT8        **TBSCert,
  OUT UINTN        *TBSCertSize
  );

#endif

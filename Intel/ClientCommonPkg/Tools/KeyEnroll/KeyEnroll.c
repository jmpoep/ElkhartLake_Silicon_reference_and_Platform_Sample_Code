//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/**
  Utility to enroll UEFI value, including PK, KEK, db/dbx/dbt at build time.

Copyright (c) 2014 - 2018, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "KeyEnroll.h"
#include "VariableCommon.h"
#include "EfiUtilityMsgs.c"
#include "AuthVariable.h"
#include <openssl/sha.h>

EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
EFI_GUID gEfiImageSecurityDatabaseGuid = EFI_IMAGE_SECURITY_DATABASE_GUID;
EFI_GUID gEfiSystemNvDataFvGuid = EFI_SYSTEM_NV_DATA_FV_GUID;
EFI_GUID gEfiCertRsa2048Guid        = EFI_CERT_RSA2048_GUID;
EFI_GUID gEfiCertX509Guid           = EFI_CERT_X509_GUID;
EFI_GUID gEfiCertSha1Guid           = EFI_CERT_SHA1_GUID;
EFI_GUID gEfiCertSha256Guid         = EFI_CERT_SHA256_GUID;
EFI_GUID gEfiCertSha384Guid         = EFI_CERT_SHA384_GUID;
EFI_GUID gEfiCertSha512Guid         = EFI_CERT_SHA512_GUID;
EFI_GUID gEfiCertTypeRsa2048Sha256Guid = EFI_CERT_TYPE_RSA2048_SHA256_GUID;
EFI_GUID gEfiCertTypePkcs7Guid         = EFI_CERT_TYPE_PKCS7_GUID;
EFI_GUID gEfiCertX509Sha256Guid = EFI_CERT_X509_SHA256_GUID;
EFI_GUID gEfiCertX509Sha384Guid = EFI_CERT_X509_SHA384_GUID;
EFI_GUID gEfiCertX509Sha512Guid = EFI_CERT_X509_SHA512_GUID;

//
// OID ASN.1 Value for Hash Algorithms
//
UINT8 mHashOidValueSha1[]   = {0x2B, 0x0E, 0x03, 0x02, 0x1A};
UINT8 mHashOidValueSha256[] = {0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01};
UINT8 mHashOidValueSha384[] = {0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x02};
UINT8 mHashOidValueSha512[] = {0x60, 0x86, 0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x03};

HASH_TABLE mHash[] = {
  { L"SHA1",   SHA1_DIGEST_SIZE,   mHashOidValueSha1,   sizeof(mHashOidValueSha1)},
  { L"SHA256", SHA256_DIGEST_SIZE, mHashOidValueSha256, sizeof(mHashOidValueSha256)},
  { L"SHA384", SHA384_DIGEST_SIZE, mHashOidValueSha384, sizeof(mHashOidValueSha384)},
  { L"SHA512", SHA512_DIGEST_SIZE, mHashOidValueSha512, sizeof(mHashOidValueSha512)},
};

G_EFI_FD_INFO               gEfiFdInfo;
LIST_ENTRY                  mVarListEntry;

unsigned int
xtoi (
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
    "%s - Tiano KeyEnroll Utility."" Version %i.%i\n\n",
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
  printf ("Usage: %s InputFile [OutputFile] [Command] [SubCommand] [Options [Parameter(s)]]\n"
          "\tCommand: PK|KEK|db|dbx|VAR|INFO\n"
          "\tPK     ADD|DEL [-F <CertFile> [-G <SignOwnerGuid>]]\n"
          "\tKEK    ADD|APPEND|DEL [-F <CertFile>|-K <KeyFile> -G <SignOwnerGuid>]\n"
          "\tdb|dbx ADD|APPEND|DEL [-F <CertFile>|-I <ImageFile> -G <SignOwnerGuid>]\n"
          "\tdbt    ADD|APPEND|DEL [-F <CertFile> -G <SignOwnerGuid>]\n"
          "\tdbx    ADD|APPEND -F <CertFile> -G <SignOwnerGuid> -H SHA256|SHA384|SHA512 [-DATE <MM/DD/YYYY>|NOW -TIME <HH:MM:SS>|NOW]]\n"
          "\tVAR    ADD|APPEND|DEL -N <Name> -G <Guid> [-A <Attributes> -D <DataFile> [-T]]\n"
          "\tINFO   [PK|KEK|db|dbx|dbt|ALL]\n"
          "", UTILITY_NAME);
  printf ("  Where:\n");
  printf ("\tInputFile   - Name of the input FD file.\n");
  printf ("\tOutputFile  - Name of the output FD file. No such parameter for INFO command.\n");
  printf ("\tCertFile    - DER-encoded certificate.\n");
  printf ("\tKeyFile     - Public key binary file.\n");
  printf ("\tImageFile   - UEFI PE/COFF image file.\n");
  printf ("\tDataFile    - The raw bytes passed in *Data to SetVariable()... \n");
  printf ("\t              If -T is also specified, it includes an EFI_VARIABLE_AUTHENTICATION_2\n");
  printf ("\t              concatenated with the new variable value for time based Auth Variable.\n");
}

/**
  Compare two EFI_TIME data.


  @param FirstTime           A pointer to the first EFI_TIME data.
  @param SecondTime          A pointer to the second EFI_TIME data.

  @retval  TRUE              The FirstTime is not later than the SecondTime.
  @retval  FALSE             The FirstTime is later than the SecondTime.

**/
BOOLEAN
CompareTimeStamp (
  IN EFI_TIME               *FirstTime,
  IN EFI_TIME               *SecondTime
  )
{
  if (FirstTime->Year != SecondTime->Year) {
    return (BOOLEAN) (FirstTime->Year < SecondTime->Year);
  } else if (FirstTime->Month != SecondTime->Month) {
    return (BOOLEAN) (FirstTime->Month < SecondTime->Month);
  } else if (FirstTime->Day != SecondTime->Day) {
    return (BOOLEAN) (FirstTime->Day < SecondTime->Day);
  } else if (FirstTime->Hour != SecondTime->Hour) {
    return (BOOLEAN) (FirstTime->Hour < SecondTime->Hour);
  } else if (FirstTime->Minute != SecondTime->Minute) {
    return (BOOLEAN) (FirstTime->Minute < SecondTime->Minute);
  }

  return (BOOLEAN) (FirstTime->Second <= SecondTime->Second);
}

VOID
GetCurrentTime (
  OUT EFI_TIME      *TimeStamp
  )
{
  time_t CurTime;
  struct tm *GmTime;

  memset (TimeStamp, 0, sizeof (*TimeStamp));

  time (&CurTime);
  GmTime = gmtime (&CurTime);
  if (GmTime == NULL) {
    return;
  }
  TimeStamp->Year = (UINT16)GmTime->tm_year + 1900; // Year is 1900-based
  TimeStamp->Month = (UINT8)GmTime->tm_mon + 1; // Month is zero based.
  TimeStamp->Day = (UINT8)GmTime->tm_mday;
  TimeStamp->Hour = (UINT8)GmTime->tm_hour;
  TimeStamp->Minute = (UINT8)GmTime->tm_min;
  TimeStamp->Second = (UINT8)GmTime->tm_sec;
}

BOOLEAN
IsGuidData (
  IN CHAR8     *StringData,
  IN EFI_GUID  *Guid
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

BOOLEAN
IsDateData (
  IN CHAR8     *StringData,
  IN EFI_TIME  *Time
  )
{
  UINTN     Index;
  UINT32    Month;
  UINT32    Day;
  UINT32    Year;
  EFI_TIME  TempTime;

  if ((strcmp (StringData, "NOW") == 0) ||
      (strcmp (StringData, "now") == 0)) {
    //
    // Fetch the current time based on UTC timezone
    //
    GetCurrentTime (&TempTime);

    Time->Month = TempTime.Month;
    Time->Day = TempTime.Day;
    Time->Year = TempTime.Year;
    return TRUE;
  }

  if (strlen (StringData) != strlen ("MM/DD/YYYY")) {
    return FALSE;
  }
  if ((StringData[2] != '/') ||
      (StringData[5] != '/') ) {
    return FALSE;
  }

  for (Index = 0; Index < 10; Index++) {
    if ((Index == 2) || (Index == 5)) {
      continue;
    }
    if ((StringData[Index] >= '0') && (StringData[Index] <= '9')) {
      continue;
    } else {
      return FALSE;
    }
  }

  Index = sscanf (
            StringData,
            "%02u/%02u/%04u",
            &Month,
            &Day,
            &Year
            );
  if (Index != 3) {
    return FALSE;
  }
  if ((Month < 1) || (Month > 12)) {
    return FALSE;
  }
  if ((Day < 1) || (Day > 31)) {
    return FALSE;
  }
  if ((Year < 1900) || (Year > 9999)) {
    return FALSE;
  }

  Time->Month = (UINT8)Month;
  Time->Day = (UINT8)Day;
  Time->Year = (UINT16)Year;

  return TRUE;
}

BOOLEAN
IsTimeData (
  IN CHAR8     *StringData,
  IN EFI_TIME  *Time
  )
{
  UINTN     Index;
  UINT32    Hour;
  UINT32    Minute;
  UINT32    Second;
  EFI_TIME  TempTime;

  if ((strcmp (StringData, "NOW") == 0) ||
      (strcmp (StringData, "now") == 0)) {
    //
    // Fetch the current time based on UTC timezone
    //
    GetCurrentTime (&TempTime);

    Time->Hour = TempTime.Hour;
    Time->Minute = TempTime.Minute;
    Time->Second = TempTime.Second;
    return TRUE;
  }

  if (strlen (StringData) != strlen ("HH:MM:SS")) {
    return FALSE;
  }
  if ((StringData[2] != ':') ||
      (StringData[5] != ':') ) {
    return FALSE;
  }

  for (Index = 0; Index < 8; Index++) {
    if ((Index == 2) || (Index == 5)) {
      continue;
    }
    if ((StringData[Index] >= '0') && (StringData[Index] <= '9')) {
      continue;
    } else {
      return FALSE;
    }
  }

  Index = sscanf (
            StringData,
            "%02u:%02u:%02u",
            &Hour,
            &Minute,
            &Second
            );
  if (Index != 3) {
    return FALSE;
  }
  if (Hour > 23) {
    return FALSE;
  }
  if (Minute > 59) {
    return FALSE;
  }
  if (Second > 59) {
    return FALSE;
  }

  Time->Hour = (UINT8)Hour;
  Time->Minute = (UINT8)Minute;
  Time->Second = (UINT8)Second;

  return TRUE;
}

/**
  Retrieve the TBSCertificate from one given X.509 certificate.

  @param[in]      Cert         Pointer to the given DER-encoded X509 certificate.
  @param[in]      CertSize     Size of the X509 certificate in bytes.
  @param[out]     TBSCert      DER-Encoded To-Be-Signed certificate.
  @param[out]     TBSCertSize  Size of the TBS certificate in bytes.

  If Cert is NULL, then return FALSE.
  If TBSCert is NULL, then return FALSE.
  If TBSCertSize is NULL, then return FALSE.

  @retval  TRUE   The TBSCertificate was retrieved successfully.
  @retval  FALSE  Invalid X.509 certificate.

**/
BOOLEAN
EFIAPI
X509GetTBSCert (
  IN  CONST UINT8  *Cert,
  IN  UINTN        CertSize,
  OUT UINT8        **TBSCert,
  OUT UINTN        *TBSCertSize
  )
{
  CONST UINT8  *Temp;
  INTN         Asn1Tag;
  INTN         ObjClass;
  UINTN        Length;

  //
  // Check input parameters.
  //
  if ((Cert == NULL) || (TBSCert == NULL) || (TBSCertSize == NULL)) {
    return FALSE;
  }

  //
  // An X.509 Certificate is: (defined in RFC3280)
  //   Certificate  ::=  SEQUENCE  {
  //     tbsCertificate       TBSCertificate,
  //     signatureAlgorithm   AlgorithmIdentifier,
  //     signature            BIT STRING }
  //
  // and
  //
  //  TBSCertificate  ::=  SEQUENCE  {
  //    version         [0]  Version DEFAULT v1,
  //    ...
  //    }
  //
  // So we can just ASN1-parse the x.509 DER-encoded data. If we strip
  // the first SEQUENCE, the second SEQUENCE is the TBSCertificate.
  //
  Temp = Cert;
  ASN1_get_object (&Temp, (long *)&Length, (int *)&Asn1Tag, (int *)&ObjClass, (long)CertSize);

  if (Asn1Tag != V_ASN1_SEQUENCE) {
    return FALSE;
  }

  *TBSCert = (UINT8 *)Temp;

  ASN1_get_object (&Temp, (long *)&Length, (int *)&Asn1Tag, (int *)&ObjClass, (long)Length);
  //
  // Verify the parsed TBSCertificate is one correct SEQUENCE data.
  //
  if (Asn1Tag != V_ASN1_SEQUENCE) {
    return FALSE;
  }

  *TBSCertSize = Length + (Temp - *TBSCert);

  return TRUE;
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
Unicode2AsciiString (
  IN  CHAR16   *UniString,
  OUT CHAR8    *String
  )
/*++

Routine Description:

  Write ascii string as unicode string format to FILE

Arguments:

  String      - Pointer to string that is written to FILE.
  UniString   - Pointer to unicode string

Returns:

  NULL

--*/
{
  while (*UniString != '\0') {
    *(String++) = (CHAR8)*(UniString++);
  }
  *String = '\0';
}

VOID
Ascii2UnicodeString (
  IN  CHAR8    *String,
  OUT CHAR16   *UniString
  )
/*++

Routine Description:

  Write ascii string as unicode string format to FILE

Arguments:

  String      - Pointer to string that is written to FILE.
  UniString   - Pointer to unicode string

Returns:

  NULL

--*/
{
  while (*String != '\0') {
    *(UniString++) = (CHAR16)*(String++);
  }
  *UniString = '\0';
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
    Error (NULL, 0, 0, "Unable to open file", FileName);
    return STATUS_ERROR;
  }
  //
  // Write the output Fvrecovery.fv file
  //
  if ((fwrite (FileData, 1, FileSize, FpOut)) != FileSize) {
    Error (NULL, 0, 0, "Write output file error!", NULL);
    fclose (FpOut);
    return STATUS_ERROR;
  }

  //
  // Close the output Fvrecovery.fv file
  //
  fclose (FpOut);

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
      if ((FvHeader->Revision == EFI_FVH_PI_REVISION) &&
          (FvHeader->Reserved[0] == 0) ){
        return FileHeader;
      }
    }
  }

  return NULL;
}

UINT32
GetVariableInfoFromFd (
  IN UINT8                       *FdBuffer,
  IN UINT32                      FdFileSize,
  OUT UINT8                      **VariableFv
  )
/*++

Routine Description:

  Get Variable information from Fd file.
  Assume Fv region is continuous in Fd file.

Arguments:

  FdBuffer     - Fd file buffer.
  FdFileSize   - Fd file size.
  Fvrecovery   - Fvrecovery pointer in Fd file buffer

Returns:
  Fvrecovery file size

--*/
{
  UINT8                       *FileBuffer;
  UINT32                      VariableFvFileSize;

  FileBuffer = FindNextFvHeader (FdBuffer, FdFileSize);
  if (FileBuffer == NULL) {
    *VariableFv = NULL;
    return 0;
  }
  VariableFvFileSize = 0;
  *VariableFv = NULL;

  while ((UINTN)FileBuffer < (UINTN)FdBuffer + FdFileSize) {
    //
    // Check variable
    //
    if (((EFI_FIRMWARE_VOLUME_HEADER *)FileBuffer)->Signature != EFI_FVH_SIGNATURE) {
      FileBuffer += 0x10;
      continue;
    }
    if (CompareGuid (&gEfiSystemNvDataFvGuid, &((EFI_FIRMWARE_VOLUME_HEADER *)FileBuffer)->FileSystemGuid) == 0) {
      VariableFvFileSize = (UINT32)((EFI_FIRMWARE_VOLUME_HEADER *)FileBuffer)->FvLength;
      *VariableFv = FileBuffer;
      break;
    }

    //
    // Next fv
    //
    FileBuffer = FindNextFvHeader (FileBuffer, (UINTN)FdBuffer + FdFileSize - (UINTN)FileBuffer);
    if (FileBuffer == NULL) {
      break;
    }
    FileBuffer = (UINT8 *)FileBuffer + ((EFI_FIRMWARE_VOLUME_HEADER *)FileBuffer)->FvLength;
  }

  return VariableFvFileSize;
}

/**
  Exchange the data between Efi variable and the data of VarList

  If VarToList is TRUE, copy the efi variable data to the VarList; Otherwise,
  update the data from varlist to efi variable.

  @param VarToList         The flag to control the direction of exchange.
  @param StorageListHead   Decide which variale list be updated

  @retval EFI_SUCCESS      Get the address successfully.
**/
EFI_STATUS
EfiVarAndListExchange (
  IN BOOLEAN      VarToList,
  IN  LIST_ENTRY  *StorageListHead
  )
{
   EFI_FIRMWARE_VOLUME_HEADER   *VarAddr;
   EFI_STATUS                   Status;
   VOID                         *VariableStoreHeader;
   VARIABLE_TYPE                VariableType;

   Status                      = EFI_ABORTED;
   VarAddr                     = (EFI_FIRMWARE_VOLUME_HEADER   *) gEfiFdInfo.EfiVariableAddr;
   VariableStoreHeader         = (VOID *)((CHAR8 *)VarAddr + VarAddr->HeaderLength);
   //
   // Judge the layout of NV by gEfiVariableGuid
   //
   VariableType  = CheckVarStore (VariableStoreHeader);

   Status = SynEfiVariable (VarToList, VariableType, StorageListHead);

   return Status;
}

/**
  Free resources of a storage.

  @param  Storage                Pointer of the storage

**/
VOID
DestroyStorage (
  IN VARIABLE_INFO_PRIVATE   *Storage
  )
{
  if (Storage == NULL) {
    return;
  }

  if (Storage->Name != NULL) {
    free (Storage->Name);
  }
  if (Storage->Buffer != NULL) {
    free (Storage->Buffer);
  }

  free (Storage);
  Storage = NULL;
}

/**
  Free resources allocated for all Storage in an LIST_ENTRY.

  @param  FormSet                Pointer of the FormSet

**/
VOID
DestroyAllStorage (
  IN LIST_ENTRY    *StorageListHead
  )
{
  LIST_ENTRY              *Link;
  VARIABLE_INFO_PRIVATE   *Storage;

  if (StorageListHead->ForwardLink != NULL) {
    while (!IsListEmpty (StorageListHead)) {
      Link = GetFirstNode (StorageListHead);
      Storage = VARIABLE_INFO_PRIVATE_FROM_LINK (Link);
      RemoveEntryList (&Storage->Link);

      DestroyStorage (Storage);
    }
  }
  StorageListHead = NULL;
}

LIST_ENTRY *
FindVariableList (
  IN  LIST_ENTRY     *StorageListHead,
  IN  CHAR16         *Name,
  IN  EFI_GUID       *Guid
  )
{
  LIST_ENTRY              *Link;
  VARIABLE_INFO_PRIVATE   *Storage;

  if (StorageListHead->ForwardLink != NULL) {
    Link = GetFirstNode (StorageListHead);
    while (!IsNull (StorageListHead, Link)) {
      Storage = VARIABLE_INFO_PRIVATE_FROM_LINK (Link);
      if ((CompareGuid (&Storage->Guid, Guid) == 0) &&
          (KeyEnrollStrCmp (Storage->Name, Name) == 0)) {
        return Link;
      }
      Link = GetNextNode (StorageListHead, Link);
    }
  }
  return NULL;
}

/*
  Find out the matching VARIABLE_INFO_PRIVATE by variable name and guid.

  @param[in]    VariableName            Name of variable to be find.
  @param[in]    VendorGuid              Variable vendor GUID.

  @retval       VARIABLE_INFO_PRIVATE   A pointer to VARIABLE_INFO_PRIVATE.
  @retval       NULL                    Not find.
*/
VARIABLE_INFO_PRIVATE*
FindVariableInfoPtr(
  IN    CHAR16        *VariableName,
  IN    EFI_GUID      *VendorGuid
  )
{
  LIST_ENTRY          *ListEntry;

  //
  //  Try to get auth variable by name and GUID.
  //
  ListEntry = FindVariableList (&mVarListEntry, VariableName, VendorGuid);
  if (ListEntry != NULL) {
    return VARIABLE_INFO_PRIVATE_FROM_LINK (ListEntry);
  }

  return NULL;
}

/**
  Filter out the duplicated EFI_SIGNATURE_DATA from the new data by comparing to the original data.
  And copy the combined data to final data.

  @param[in]        Data          Pointer to original EFI_SIGNATURE_LIST.
  @param[in]        DataSize      Size of Data buffer.
  @param[in]        NewData       Pointer to new EFI_SIGNATURE_LIST.
  @param[in]        NewDataSize   Size of NewData buffer.
  @param[out]       FinalData     Pointer to final combined EFI_SIGNATURE_LIST.
  @param[out]       FinalDataSize Size of FinalData buffer.

**/
VOID
FilterSignatureList (
  IN  VOID      *Data,
  IN  UINTN     DataSize,
  IN  VOID      *NewData,
  IN  UINTN     NewDataSize,
  OUT VOID      *FinalData,
  OUT UINTN     *FinalDataSize
  )
{
  EFI_SIGNATURE_LIST    *CertList;
  EFI_SIGNATURE_DATA    *Cert;
  UINTN                 CertCount;
  EFI_SIGNATURE_LIST    *NewCertList;
  EFI_SIGNATURE_DATA    *NewCert;
  UINTN                 NewCertCount;
  UINTN                 Index;
  UINTN                 Index2;
  UINTN                 NewSize;
  UINTN                 Size;
  UINT8                 *Tail;
  UINTN                 CopiedCount;
  UINTN                 SignatureListSize;
  BOOLEAN               IsNewCert;

  //
  // Copy the original data to final data first.
  //
  CopyMem (FinalData, Data, DataSize);
  *FinalDataSize = DataSize;

  if (NewDataSize == 0) {
    return;
  }

  Tail = (UINT8 *) FinalData + *FinalDataSize;

  NewSize = NewDataSize;
  NewCertList = (EFI_SIGNATURE_LIST *) NewData;
  while ((NewSize > 0) && (NewSize >= NewCertList->SignatureListSize)) {
    NewCert      = (EFI_SIGNATURE_DATA *) ((UINT8 *) NewCertList + sizeof (EFI_SIGNATURE_LIST) + NewCertList->SignatureHeaderSize);
    NewCertCount = (NewCertList->SignatureListSize - sizeof (EFI_SIGNATURE_LIST) - NewCertList->SignatureHeaderSize) / NewCertList->SignatureSize;

    CopiedCount = 0;
    for (Index = 0; Index < NewCertCount; Index++) {
      IsNewCert = TRUE;

      Size = DataSize;
      CertList = (EFI_SIGNATURE_LIST *) Data;
      while ((Size > 0) && (Size >= CertList->SignatureListSize)) {
        if ((CompareGuid (&CertList->SignatureType, &NewCertList->SignatureType) == 0) &&
           (CertList->SignatureSize == NewCertList->SignatureSize)) {
          Cert      = (EFI_SIGNATURE_DATA *) ((UINT8 *) CertList + sizeof (EFI_SIGNATURE_LIST) + CertList->SignatureHeaderSize);
          CertCount = (CertList->SignatureListSize - sizeof (EFI_SIGNATURE_LIST) - CertList->SignatureHeaderSize) / CertList->SignatureSize;
          for (Index2 = 0; Index2 < CertCount; Index2++) {
            //
            // Iterate each Signature Data in this Signature List.
            //
            if (CompareMem (NewCert, Cert, CertList->SignatureSize) == 0) {
              IsNewCert = FALSE;
              break;
            }
            Cert = (EFI_SIGNATURE_DATA *) ((UINT8 *) Cert + CertList->SignatureSize);
          }
        }

        if (!IsNewCert) {
          break;
        }
        Size -= CertList->SignatureListSize;
        CertList = (EFI_SIGNATURE_LIST *) ((UINT8 *) CertList + CertList->SignatureListSize);
      }

      if (IsNewCert) {
        printf ("found new cert!\n");
        //
        // New EFI_SIGNATURE_DATA, keep it.
        //
        if (CopiedCount == 0) {
          //
          // Copy EFI_SIGNATURE_LIST header for only once.
          //
          CopyMem (Tail, NewCertList, sizeof (EFI_SIGNATURE_LIST) + NewCertList->SignatureHeaderSize);
          Tail = Tail + sizeof (EFI_SIGNATURE_LIST) + NewCertList->SignatureHeaderSize;
        }

        CopyMem (Tail, NewCert, NewCertList->SignatureSize);
        Tail += NewCertList->SignatureSize;
        CopiedCount++;
      }

      NewCert = (EFI_SIGNATURE_DATA *) ((UINT8 *) NewCert + NewCertList->SignatureSize);
    }

    //
    // Update SignatureListSize in the kept EFI_SIGNATURE_LIST.
    //
    if (CopiedCount != 0) {
      SignatureListSize = sizeof (EFI_SIGNATURE_LIST) + NewCertList->SignatureHeaderSize + (CopiedCount * NewCertList->SignatureSize);
      CertList = (EFI_SIGNATURE_LIST *) (Tail - SignatureListSize);
      CertList->SignatureListSize = (UINT32) SignatureListSize;
    }

    NewSize -= NewCertList->SignatureListSize;
    NewCertList = (EFI_SIGNATURE_LIST *) ((UINT8 *) NewCertList + NewCertList->SignatureListSize);
  }

  *FinalDataSize = (Tail - (UINT8 *) FinalData);
}

EFI_STATUS
UpdateVariableList (
  IN  LIST_ENTRY     *Link,
  IN  CHAR16         *Name,
  IN  EFI_GUID       *Guid,
  IN  UINT32         Attributes,
  IN  EFI_TIME       *TimeStamp,
  IN  UINTN          Size,
  IN  UINT8          *Buffer,
  IN  BOOLEAN        Append
  )
{
  VARIABLE_INFO_PRIVATE   *Storage;
  UINTN                   NewSize;
  UINT8                   *NewBuffer;

  Storage = VARIABLE_INFO_PRIVATE_FROM_LINK (Link);

  Storage->Attributes = Attributes;
  if (Append) {
    if ((Attributes & EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS) != 0) {
      //
      // When the new TimeStamp value is later than the current timestamp associated
      // with the variable, we need associate the new timestamp with the updated value.
      //
      if (CompareTimeStamp (&Storage->TimeStamp, TimeStamp)) {
        CopyMem (&Storage->TimeStamp, TimeStamp, sizeof (*TimeStamp));
      }
    }
    NewSize = Storage->Size + Size;
    NewBuffer = malloc (NewSize);
    if (NewBuffer == NULL) {
      Error (NULL, 0, 0, "Unable to allocate memory", NULL);
      return EFI_OUT_OF_RESOURCES;
    }
    ASSERT (Storage->Buffer != NULL);
    if (((CompareGuid (Guid, &gEfiImageSecurityDatabaseGuid) == 0) &&
        ((KeyEnrollStrCmp (Name, EFI_IMAGE_SECURITY_DATABASE) == 0) || (KeyEnrollStrCmp (Name, EFI_IMAGE_SECURITY_DATABASE1) == 0) ||
        (KeyEnrollStrCmp (Name, EFI_IMAGE_SECURITY_DATABASE2) == 0))) ||
        ((CompareGuid (Guid, &gEfiGlobalVariableGuid) == 0) && (KeyEnrollStrCmp (Name, EFI_KEY_EXCHANGE_KEY_NAME) == 0))) {
      FilterSignatureList (
        Storage->Buffer,
        Storage->Size,
        Buffer,
        Size,
        NewBuffer,
        &NewSize
        );
    } else {
      CopyMem (NewBuffer, Storage->Buffer, Storage->Size);
      CopyMem (NewBuffer + Storage->Size, Buffer, Size);
    }

    Storage->Size = NewSize;
    free (Storage->Buffer);
    Storage->Buffer = NewBuffer;
  } else {
    if ((Attributes & EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS) != 0) {
      CopyMem (&Storage->TimeStamp, TimeStamp, sizeof (*TimeStamp));
    }
    Storage->Size = Size;
    ASSERT (Storage->Buffer != NULL);
    free (Storage->Buffer);
    Storage->Buffer = malloc (Size);
    if (Storage->Buffer == NULL) {
      Error (NULL, 0, 0, "Unable to allocate memory", NULL);
      return EFI_OUT_OF_RESOURCES;
    }
    CopyMem (Storage->Buffer, Buffer, Size);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
CreateVariableList (
  IN  LIST_ENTRY     *StorageListHead,
  IN  CHAR16         *Name,
  IN  EFI_GUID       *Guid,
  IN  UINT32         Attributes,
  IN  EFI_TIME       *TimeStamp,
  IN  UINTN          Size,
  IN  UINT8          *Buffer,
  IN  BOOLEAN        Append
  )
{
  VARIABLE_INFO_PRIVATE     *Storage;
  UINTN                     VarNameSize;
  LIST_ENTRY                *Link;
  EFI_TIME                  TempTimeStamp;

  if (((Attributes & EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS) != 0) &&
      (TimeStamp == NULL)) {
    //
    // Fetch the current time based on UTC timezone
    //
    GetCurrentTime (&TempTimeStamp);
    TimeStamp = &TempTimeStamp;
  }

  //
  // Check previous one
  //
  Link = FindVariableList (StorageListHead, Name, Guid);
  if (Link != NULL) {
    return UpdateVariableList (
             Link,
             Name,
             Guid,
             Attributes,
             TimeStamp,
             Size,
             Buffer,
             Append
             );
  }

  //
  // Create new one
  //
  Storage = malloc (sizeof (*Storage));
  if (Storage == NULL) {
    Error (NULL, 0, 0, "Unable to allocate memory", NULL);
    return EFI_OUT_OF_RESOURCES;
  }

  Storage->Signature = VARIABLE_INFO_PRIVATE_SIGNATURE;
  CopyMem (&Storage->Guid, Guid, sizeof(*Guid));
  VarNameSize = KeyEnrollStrSize (Name);
  Storage->Name = malloc (VarNameSize);
  if (Storage->Name == NULL) {
    Error (NULL, 0, 0, "Unable to allocate memory", NULL);
    free (Storage);
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem (Storage->Name, Name, VarNameSize);
  Storage->Attributes = Attributes;
  Storage->Size = Size;
  ASSERT (Storage->Size != 0);
  Storage->Buffer = malloc (Size);
  if (Storage->Buffer == NULL) {
    Error (NULL, 0, 0, "Unable to allocate memory", NULL);
    free (Storage->Name);
    free (Storage);
    return EFI_OUT_OF_RESOURCES;
  }
  CopyMem (Storage->Buffer, Buffer, Size);
  if ((Attributes & EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS) != 0) {
    CopyMem (&Storage->TimeStamp, TimeStamp, sizeof (*TimeStamp));
  }

  InsertTailList(StorageListHead, &Storage->Link);

  return EFI_SUCCESS;
}

EFI_STATUS
DeleteVariableList (
  IN  LIST_ENTRY     *StorageListHead,
  IN  CHAR16         *Name,
  IN  EFI_GUID       *Guid
  )
{
  VARIABLE_INFO_PRIVATE     *Storage;
  LIST_ENTRY                *Link;

  Link = FindVariableList (StorageListHead, Name, Guid);
  if (Link == NULL) {
    return EFI_NOT_FOUND;
  }

  Storage = VARIABLE_INFO_PRIVATE_FROM_LINK (Link);
  RemoveEntryList (&Storage->Link);
  DestroyStorage (Storage);

  return EFI_SUCCESS;
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

/**
  Load PE/COFF image information into internal buffer and check its validity.

  @retval   EFI_SUCCESS         Successful
  @retval   EFI_UNSUPPORTED     Invalid PE/COFF file
  @retval   EFI_ABORTED         Serious error occurs, like file I/O error etc.

**/
EFI_STATUS
LoadPeImage (
  IN UINT8                                 *ImageBase,
  IN UINTN                                 ImageSize,
  OUT EFI_IMAGE_SECURITY_DATA_DIRECTORY    **SecDataDir
  )
{
  EFI_IMAGE_DOS_HEADER                  *DosHdr;
  EFI_IMAGE_NT_HEADERS32                *NtHeader32;
  EFI_IMAGE_NT_HEADERS64                *NtHeader64;
  EFI_IMAGE_OPTIONAL_HEADER_PTR_UNION   NtHeader;
  UINT32                                PeCoffHeaderOffset;
  UINT16                                Magic;

  NtHeader32 = NULL;
  NtHeader64 = NULL;
  //
  // Read the Dos header
  //
  DosHdr = (EFI_IMAGE_DOS_HEADER *)(ImageBase);
  if (DosHdr->e_magic == EFI_IMAGE_DOS_SIGNATURE) {
    //
    // DOS image header is present,
    // So read the PE header after the DOS image header
    //
    PeCoffHeaderOffset = DosHdr->e_lfanew;
  } else {
    PeCoffHeaderOffset = 0;
  }

  //
  // Read PE header and check the signature validity and machine compatibility
  //
  NtHeader32 = (EFI_IMAGE_NT_HEADERS32 *) (ImageBase + PeCoffHeaderOffset);
  if (NtHeader32->Signature != EFI_IMAGE_NT_SIGNATURE) {
    return EFI_UNSUPPORTED;
  }

  NtHeader.Pe32 = NtHeader32;

  //
  // Measuring PE/COFF Image Header;
  // But CheckSum field and SECURITY data directory (certificate) are excluded
  //
  //
  // Get the magic value from the PE/COFF Optional Header
  //
  Magic = NtHeader.Pe32->OptionalHeader.Magic;

  //
  // Check the architecture field of PE header and get the Certificate Data Directory data
  // Note the size of FileHeader field is constant for both IA32 and X64 arch
  //
  if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    *SecDataDir = (EFI_IMAGE_SECURITY_DATA_DIRECTORY *) &(NtHeader32->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY]);
  } else if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
    NtHeader64 = (EFI_IMAGE_NT_HEADERS64 *) (ImageBase + PeCoffHeaderOffset);
    *SecDataDir = (EFI_IMAGE_SECURITY_DATA_DIRECTORY *) &(NtHeader64->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY]);
  } else {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
  Calculate hash of Pe/Coff image based on the authenticode image hashing in
  PE/COFF Specification 8.0 Appendix A

  @param[in]    HashAlg   Hash algorithm type.

  @retval TRUE            Successfully hash image.
  @retval FALSE           Fail in hash image.

**/
BOOLEAN
HashPeImage (
  IN  UINT32                    HashAlg,
  IN  UINT8                     *ImageBase,
  IN  UINTN                     ImageSize,
  OUT UINT8                     *ImageDigest,
  OUT UINTN                     *ImageDigestSize,
  OUT EFI_GUID                  *CertType
  )
{
  BOOLEAN                              Status;
  EFI_IMAGE_DOS_HEADER                 *DosHdr;
  UINT32                               PeCoffHeaderOffset;
  EFI_IMAGE_SECTION_HEADER             *Section;
  UINT8                                *HashBase;
  UINTN                                HashSize;
  UINTN                                SumOfBytesHashed;
  EFI_IMAGE_SECTION_HEADER             *SectionHeader;
  UINTN                                Index;
  UINTN                                Pos;
  UINT16                               Magic;
  EFI_IMAGE_OPTIONAL_HEADER_PTR_UNION  Hdr;
  UINT32                               NumberOfRvaAndSizes;
  UINT32                               CertSize;
  EVP_MD_CTX                           ctx;
  const EVP_MD                         *md;

  SectionHeader = NULL;
  Status        = FALSE;

  //
  // Initialize context of hash.
  //
  if (HashAlg == HASHALG_SHA1) {
    *ImageDigestSize  = SHA1_DIGEST_SIZE;
    CopyMem (CertType, &gEfiCertSha1Guid, sizeof(*CertType));
  } else if (HashAlg == HASHALG_SHA256) {
    *ImageDigestSize  = SHA256_DIGEST_SIZE;
    CopyMem (CertType, &gEfiCertSha256Guid, sizeof(*CertType));
  } else if (HashAlg == HASHALG_SHA384) {
    *ImageDigestSize  = SHA384_DIGEST_SIZE;
    CopyMem (CertType, &gEfiCertSha384Guid, sizeof(*CertType));
  } else if (HashAlg == HASHALG_SHA512) {
    *ImageDigestSize  = SHA512_DIGEST_SIZE;
    CopyMem (CertType, &gEfiCertSha512Guid, sizeof(*CertType));
  } else {
    printf ("HashPeImage - HashAlg : 0x%x\n", HashAlg);
    return FALSE;
  }
  ZeroMem (ImageDigest, *ImageDigestSize);

  switch (HashAlg) {
  case HASHALG_SHA1:
    md = EVP_sha1();
    break;
  case HASHALG_SHA256:
    md = EVP_sha256();
    break;
  case HASHALG_SHA384:
    md = EVP_sha384();
    break;
  case HASHALG_SHA512:
    md = EVP_sha512();
    break;
  default:
    md = NULL;
    break;
  }

  //
  // Check PE/COFF image
  //
  DosHdr = (EFI_IMAGE_DOS_HEADER *) (UINTN) ImageBase;
  PeCoffHeaderOffset = 0;
  if (DosHdr->e_magic == EFI_IMAGE_DOS_SIGNATURE) {
    PeCoffHeaderOffset = DosHdr->e_lfanew;
  }

  Hdr.Pe32 = (EFI_IMAGE_NT_HEADERS32 *)((UINT8 *) (UINTN) ImageBase + PeCoffHeaderOffset);
  if (Hdr.Pe32->Signature != EFI_IMAGE_NT_SIGNATURE) {
    printf ("Hdr.Pe32->Signature != EFI_IMAGE_NT_SIGNATURE\n");
    Status = FALSE;
    goto Done;
  }

  //
  // PE/COFF Image Measurement
  //
  //    NOTE: The following codes/steps are based upon the authenticode image hashing in
  //      PE/COFF Specification 8.0 Appendix A.
  //
  //

  // 1.  Load the image header into memory.

  // 2.  Initialize a SHA hash context.
  EVP_DigestInit(&ctx, md);

  //
  // Measuring PE/COFF Image Header;
  // But CheckSum field and SECURITY data directory (certificate) are excluded
  //

  //
  // Get the magic value from the PE/COFF Optional Header
  //
  Magic = Hdr.Pe32->OptionalHeader.Magic;

  //
  // 3.  Calculate the distance from the base of the image header to the image checksum address.
  // 4.  Hash the image header from its base to beginning of the image checksum.
  //
  HashBase = ImageBase;
  if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    //
    // Use PE32 offset.
    //
    NumberOfRvaAndSizes = Hdr.Pe32->OptionalHeader.NumberOfRvaAndSizes;
    HashSize = (UINTN) ((UINT8 *) (&Hdr.Pe32->OptionalHeader.CheckSum) - HashBase);
  } else {
    //
    // Use PE32+ offset.
    //
    NumberOfRvaAndSizes = Hdr.Pe32Plus->OptionalHeader.NumberOfRvaAndSizes;
    HashSize = (UINTN) ((UINT8 *) (&Hdr.Pe32Plus->OptionalHeader.CheckSum) - HashBase);
  }

  EVP_DigestUpdate(&ctx, HashBase, HashSize);

  //
  // 5.  Skip over the image checksum (it occupies a single ULONG).
  //
  if (NumberOfRvaAndSizes <= EFI_IMAGE_DIRECTORY_ENTRY_SECURITY) {
    //
    // 6.  Since there is no Cert Directory in optional header, hash everything
    //     from the end of the checksum to the end of image header.
    //
    if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
      //
      // Use PE32 offset.
      //
      HashBase = (UINT8 *) &Hdr.Pe32->OptionalHeader.CheckSum + sizeof (UINT32);
      HashSize = Hdr.Pe32->OptionalHeader.SizeOfHeaders - (UINTN) (HashBase - ImageBase);
    } else {
      //
      // Use PE32+ offset.
      //
      HashBase = (UINT8 *) &Hdr.Pe32Plus->OptionalHeader.CheckSum + sizeof (UINT32);
      HashSize = Hdr.Pe32Plus->OptionalHeader.SizeOfHeaders - (UINTN) (HashBase - ImageBase);
    }

    if (HashSize != 0) {
      EVP_DigestUpdate(&ctx, HashBase, HashSize);
    }
  } else {
    //
    // 7.  Hash everything from the end of the checksum to the start of the Cert Directory.
    //
    if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
      //
      // Use PE32 offset.
      //
      HashBase = (UINT8 *) &Hdr.Pe32->OptionalHeader.CheckSum + sizeof (UINT32);
      HashSize = (UINTN) ((UINT8 *) (&Hdr.Pe32->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY]) - HashBase);
    } else {
      //
      // Use PE32+ offset.
      //
      HashBase = (UINT8 *) &Hdr.Pe32Plus->OptionalHeader.CheckSum + sizeof (UINT32);
      HashSize = (UINTN) ((UINT8 *) (&Hdr.Pe32Plus->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY]) - HashBase);
    }

    if (HashSize != 0) {
      EVP_DigestUpdate(&ctx, HashBase, HashSize);
    }

    //
    // 8.  Skip over the Cert Directory. (It is sizeof(IMAGE_DATA_DIRECTORY) bytes.)
    // 9.  Hash everything from the end of the Cert Directory to the end of image header.
    //
    if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
      //
      // Use PE32 offset
      //
      HashBase = (UINT8 *) &Hdr.Pe32->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1];
      HashSize = Hdr.Pe32->OptionalHeader.SizeOfHeaders - (UINTN) ((UINT8 *) (&Hdr.Pe32->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1]) - ImageBase);
    } else {
      //
      // Use PE32+ offset.
      //
      HashBase = (UINT8 *) &Hdr.Pe32Plus->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1];
      HashSize = Hdr.Pe32Plus->OptionalHeader.SizeOfHeaders - (UINTN) ((UINT8 *) (&Hdr.Pe32Plus->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY + 1]) - ImageBase);
    }

    EVP_DigestUpdate(&ctx, HashBase, HashSize);
  }

  //
  // 10. Set the SUM_OF_BYTES_HASHED to the size of the header.
  //
  if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
    //
    // Use PE32 offset.
    //
    SumOfBytesHashed = Hdr.Pe32->OptionalHeader.SizeOfHeaders;
  } else {
    //
    // Use PE32+ offset
    //
    SumOfBytesHashed = Hdr.Pe32Plus->OptionalHeader.SizeOfHeaders;
  }

  //
  // 11. Build a temporary table of pointers to all the IMAGE_SECTION_HEADER
  //     structures in the image. The 'NumberOfSections' field of the image
  //     header indicates how big the table should be. Do not include any
  //     IMAGE_SECTION_HEADERs in the table whose 'SizeOfRawData' field is zero.
  //
  SectionHeader = (EFI_IMAGE_SECTION_HEADER *) malloc (sizeof (EFI_IMAGE_SECTION_HEADER) * Hdr.Pe32->FileHeader.NumberOfSections);
  if (SectionHeader == NULL) {
    printf ("SectionHeader == NULL\n");
    Status = FALSE;
    goto Done;
  }
  ZeroMem (SectionHeader, sizeof (EFI_IMAGE_SECTION_HEADER) * Hdr.Pe32->FileHeader.NumberOfSections);
  //
  // 12.  Using the 'PointerToRawData' in the referenced section headers as
  //      a key, arrange the elements in the table in ascending order. In other
  //      words, sort the section headers according to the disk-file offset of
  //      the section.
  //
  Section = (EFI_IMAGE_SECTION_HEADER *) (
               ImageBase +
               PeCoffHeaderOffset +
               sizeof (UINT32) +
               sizeof (EFI_IMAGE_FILE_HEADER) +
               Hdr.Pe32->FileHeader.SizeOfOptionalHeader
               );
  for (Index = 0; Index < Hdr.Pe32->FileHeader.NumberOfSections; Index++) {
    Pos = Index;
    while ((Pos > 0) && (Section->PointerToRawData < SectionHeader[Pos - 1].PointerToRawData)) {
      CopyMem (&SectionHeader[Pos], &SectionHeader[Pos - 1], sizeof (EFI_IMAGE_SECTION_HEADER));
      Pos--;
    }
    CopyMem (&SectionHeader[Pos], Section, sizeof (EFI_IMAGE_SECTION_HEADER));
    Section += 1;
  }

  //
  // 13.  Walk through the sorted table, bring the corresponding section
  //      into memory, and hash the entire section (using the 'SizeOfRawData'
  //      field in the section header to determine the amount of data to hash).
  // 14.  Add the section's 'SizeOfRawData' to SUM_OF_BYTES_HASHED .
  // 15.  Repeat steps 13 and 14 for all the sections in the sorted table.
  //
  for (Index = 0; Index < Hdr.Pe32->FileHeader.NumberOfSections; Index++) {
    Section = &SectionHeader[Index];
    if (Section->SizeOfRawData == 0) {
      continue;
    }
    HashBase  = ImageBase + Section->PointerToRawData;
    HashSize  = (UINTN) Section->SizeOfRawData;

    EVP_DigestUpdate(&ctx, HashBase, HashSize);

    SumOfBytesHashed += HashSize;
  }

  //
  // 16.  If the file size is greater than SUM_OF_BYTES_HASHED, there is extra
  //      data in the file that needs to be added to the hash. This data begins
  //      at file offset SUM_OF_BYTES_HASHED and its length is:
  //             FileSize  -  (CertDirectory->Size)
  //
  if (ImageSize > SumOfBytesHashed) {
    HashBase = ImageBase + SumOfBytesHashed;
    if (NumberOfRvaAndSizes <= EFI_IMAGE_DIRECTORY_ENTRY_SECURITY) {
      CertSize = 0;
    } else {
      if (Magic == EFI_IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
        //
        // Use PE32 offset.
        //
        CertSize = Hdr.Pe32->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY].Size;
      } else {
        //
        // Use PE32+ offset.
        //
        CertSize = Hdr.Pe32Plus->OptionalHeader.DataDirectory[EFI_IMAGE_DIRECTORY_ENTRY_SECURITY].Size;
      }
    }

    if (ImageSize > CertSize + SumOfBytesHashed) {
      HashSize = (UINTN) (ImageSize - CertSize - SumOfBytesHashed);

      EVP_DigestUpdate(&ctx, HashBase, HashSize);
    }
  }

  EVP_DigestFinal(&ctx, (UINT8 *)ImageDigest, NULL);
  Status = TRUE;

Done:
  if (SectionHeader != NULL) {
    free (SectionHeader);
  }
  return Status;
}

/**
  Recognize the Hash algorithm in PE/COFF Authenticode and calculate hash of
  Pe/Coff image based on the authenticated image hashing in PE/COFF Specification
  8.0 Appendix A

  @retval EFI_UNSUPPORTED             Hash algorithm is not supported.
  @retval EFI_SUCCESS                 Hash successfully.

**/
EFI_STATUS
HashPeImageByType (
  IN  UINT8                                *ImageBase,
  IN  UINTN                                ImageSize,
  IN  UINT8                                *AuthData,
  IN  UINTN                                AuthDataSize,
  OUT UINT8                                *ImageDigest,
  OUT UINTN                                *ImageDigestSize,
  OUT EFI_GUID                             *CertType
  )
{
  UINT8                     Index;

  for (Index = 0; Index < HASHALG_MAX; Index++) {
    //
    // Check the Hash algorithm in PE/COFF Authenticode.
    //    According to PKCS#7 Definition:
    //        SignedData ::= SEQUENCE {
    //            version Version,
    //            digestAlgorithms DigestAlgorithmIdentifiers,
    //            contentInfo ContentInfo,
    //            .... }
    //    The DigestAlgorithmIdentifiers can be used to determine the hash algorithm in PE/COFF hashing
    //    This field has the fixed offset (+32) in final Authenticode ASN.1 data.
    //    Fixed offset (+32) is calculated based on two bytes of length encoding.
    //
    if ((*(AuthData + 1) & TWO_BYTE_ENCODE) != TWO_BYTE_ENCODE) {
      //
      // Only support two bytes of Long Form of Length Encoding.
      //
      continue;
    }

    if (AuthDataSize < 32 + mHash[Index].OidLength) {
      return EFI_UNSUPPORTED;
    }

    if (CompareMem (AuthData + 32, mHash[Index].OidValue, mHash[Index].OidLength) == 0) {
      break;
    }
  }

  if (Index == HASHALG_MAX) {
    return EFI_UNSUPPORTED;
  }

  //
  // HASH PE Image based on Hash algorithm in PE/COFF Authenticode.
  //
  if (!HashPeImage(Index, ImageBase, ImageSize, ImageDigest, ImageDigestSize, CertType)) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

EFI_STATUS
CreateImageCertificateList (
  IN  CHAR8                       *ImageFile,
  IN  EFI_GUID                    *SignatureOwner,
  OUT EFI_SIGNATURE_LIST          **Cert
  )
{
  STATUS                                Status;
  EFI_STATUS                            EfiStatus;
  UINT8                                 *ImageBase = NULL;
  UINTN                                 ImageSize = 0;
  EFI_SIGNATURE_DATA                    *CertData=NULL;
  EFI_IMAGE_SECURITY_DATA_DIRECTORY     *SecDataDir;
  WIN_CERTIFICATE                       *Certificate;
  UINT8                                 ImageDigest[MAX_DIGEST_SIZE];
  UINTN                                 ImageDigestSize;
  EFI_GUID                              CertType;
  WIN_CERTIFICATE_UEFI_GUID             *GuidCertData;
  WIN_CERTIFICATE_EFI_PKCS              *PkcsCertData;

  Status = ReadInputFile (ImageFile, &ImageBase, (UINT32 *) &ImageSize, NULL);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "Unable to open file", ImageFile);
    return EFI_NOT_FOUND;
  }

  EfiStatus = LoadPeImage (ImageBase, ImageSize, &SecDataDir);
  if (EFI_ERROR (EfiStatus)) {
    Error (NULL, 0, 0, "Unable to load PE image", ImageFile);
    return EFI_UNSUPPORTED;
  }

  if (SecDataDir->SizeOfCert == 0) {
    if (!HashPeImage (HASHALG_SHA256, ImageBase, ImageSize, ImageDigest, &ImageDigestSize, &CertType)) {
      Error (NULL, 0, 0, "Unable to hash PE image", ImageFile);
      free (ImageBase);
      return EFI_UNSUPPORTED;
    }
  } else {
    //
    // Read the certificate data
    //
    Certificate = (WIN_CERTIFICATE *)(ImageBase + SecDataDir->Offset);

    if (Certificate->wCertificateType == WIN_CERT_TYPE_EFI_GUID) {
      GuidCertData = (WIN_CERTIFICATE_UEFI_GUID *) Certificate;
      if (CompareMem (&GuidCertData->CertType, &gEfiCertTypeRsa2048Sha256Guid, sizeof(EFI_GUID)) == 0) {
        if (!HashPeImage (HASHALG_SHA256, ImageBase, ImageSize, ImageDigest, &ImageDigestSize, &CertType)) {
          Error (NULL, 0, 0, "Image wCertificateType is EFI_GUID, but unable to hash PE image", ImageFile);
          free (ImageBase);
          return EFI_UNSUPPORTED;
        }
      } else if (CompareMem (&GuidCertData->CertType, &gEfiCertTypePkcs7Guid, sizeof(EFI_GUID)) == 0) {
        Status = HashPeImageByType (
                   ImageBase,
                   ImageSize,
                   (UINT8 *)GuidCertData + sizeof(GuidCertData->Hdr) + sizeof(GuidCertData->CertType),
                   GuidCertData->Hdr.dwLength - sizeof(GuidCertData->Hdr) - sizeof(GuidCertData->CertType),
                   ImageDigest,
                   &ImageDigestSize,
                   &CertType
                   );
        if (EFI_ERROR (Status)) {
          Error (NULL, 0, 0, "Image wCertificateType is EFI_GUID, Unable to hash PE image by type", ImageFile);
          free (ImageBase);
          return EFI_UNSUPPORTED;
        }
      } else {
        Error (NULL, 0, 0, "Image wCertificateType is EFI_GUID, but CertType is NOT gEfiCertTypeRsa2048Sha256Guid or gEfiCertTypePkcs7Guid", ImageFile);
        free (ImageBase);
        return EFI_UNSUPPORTED;
      }

    } else if (Certificate->wCertificateType == WIN_CERT_TYPE_PKCS_SIGNED_DATA) {
      PkcsCertData = (WIN_CERTIFICATE_EFI_PKCS *) Certificate;
      Status = HashPeImageByType (
                 ImageBase,
                 ImageSize,
                 PkcsCertData->CertData,
                 PkcsCertData->Hdr.dwLength - sizeof(PkcsCertData->Hdr),
                 ImageDigest,
                 &ImageDigestSize,
                 &CertType
                 );
      if (EFI_ERROR (Status)) {
        Error (NULL, 0, 0, "Image wCertificateType is PKCS_SIGNED_DATA, Unable to hash PE image by type", ImageFile);
        free (ImageBase);
        return EFI_UNSUPPORTED;
      }
    } else {
      Error (NULL, 0, 0, "Image wCertificateType is unknown", ImageFile);
      free (ImageBase);
      return EFI_UNSUPPORTED;
    }
  }


  // Allocate space for PK certificate list and initialize it.
  // Create PK database entry w/ SignatureHeaderSize equals 0.
  //
  *Cert = (EFI_SIGNATURE_LIST*) malloc (
              sizeof(EFI_SIGNATURE_LIST) + sizeof(EFI_SIGNATURE_DATA) - 1
              + ImageDigestSize
              );
  if (*Cert == NULL) {
    Error (NULL, 0, 0, "Unable to allocate memory", NULL);
    free (ImageBase);
    return EFI_OUT_OF_RESOURCES;
  }

  (*Cert)->SignatureListSize   = (UINT32) (sizeof(EFI_SIGNATURE_LIST)
                                    + sizeof(EFI_SIGNATURE_DATA) - 1
                                    + ImageDigestSize);
  (*Cert)->SignatureSize       = (UINT32) (sizeof(EFI_SIGNATURE_DATA) - 1 + ImageDigestSize);
  (*Cert)->SignatureHeaderSize = 0;
  CopyMem (&(*Cert)->SignatureType, &CertType, sizeof(EFI_GUID));
  CertData                     = (EFI_SIGNATURE_DATA*) ((UINTN)(*Cert)
                                                          + sizeof(EFI_SIGNATURE_LIST)
                                                          + (*Cert)->SignatureHeaderSize);
  CopyMem (&CertData->SignatureOwner, SignatureOwner, sizeof(EFI_GUID));
  CopyMem ((VOID*)&(CertData->SignatureData[0]), ImageDigest, ImageDigestSize);


  free (ImageBase);

  return EFI_SUCCESS;
}

EFI_STATUS
CreatePkCertificateList (
  IN  CHAR8                       *PkKeyFile,
  IN  EFI_GUID                    *SignatureOwner,
  OUT EFI_SIGNATURE_LIST          **Cert
  )
{
  STATUS                  Status;
  UINT8                   *PkKeyData = NULL;
  UINTN                   PkKeyDataSize = 0;
  EFI_SIGNATURE_DATA      *CertData=NULL;
  CPL_KEY_INFO            *KeyInfo;
  VOID                    *KeyBuffer = NULL;

  Status = ReadInputFile (PkKeyFile, &PkKeyData, (UINT32 *) &PkKeyDataSize, NULL);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "Unable to open file", PkKeyFile);
    return EFI_NOT_FOUND;
  }

  KeyInfo = (CPL_KEY_INFO *)PkKeyData;
  if (KeyInfo->KeyLengthInBits/8 != WIN_CERT_UEFI_RSA2048_SIZE) {
    Error (NULL, 0, 0, "PkKey data file format wrong", PkKeyFile);
    free (PkKeyData);
    return EFI_UNSUPPORTED;
  }
  KeyBuffer = (VOID *)(KeyInfo + 1);
  SwapEndian (KeyBuffer, WIN_CERT_UEFI_RSA2048_SIZE);

  // Allocate space for PK certificate list
  // and initialize the list.
  // Create PK database entry w/ SignatureHeaderSize equals 0.
  //
  *Cert = (EFI_SIGNATURE_LIST*) malloc (
            sizeof(EFI_SIGNATURE_LIST) + sizeof(EFI_SIGNATURE_DATA) - 1
            + WIN_CERT_UEFI_RSA2048_SIZE
            );
  if (*Cert == NULL) {
    Error (NULL, 0, 0, "Unable to allocate memory", NULL);
    free (PkKeyData);
    return EFI_OUT_OF_RESOURCES;
  }

  (*Cert)->SignatureListSize   = sizeof(EFI_SIGNATURE_LIST)
                                  + sizeof(EFI_SIGNATURE_DATA) - 1
                                  + WIN_CERT_UEFI_RSA2048_SIZE;
  (*Cert)->SignatureSize       = sizeof(EFI_SIGNATURE_DATA) - 1 + WIN_CERT_UEFI_RSA2048_SIZE;
  (*Cert)->SignatureHeaderSize = 0;
  CopyMem (&(*Cert)->SignatureType, &gEfiCertRsa2048Guid, sizeof(EFI_GUID));

  CertData                    = (EFI_SIGNATURE_DATA*)((UINTN)(*Cert)
                                                          + sizeof(EFI_SIGNATURE_LIST)
                                                          + (*Cert)->SignatureHeaderSize);

  CopyMem (&CertData->SignatureOwner, SignatureOwner, sizeof(EFI_GUID));

  //
  // Fill the PK database with PKpub data from PKKeyFile.
  //
  CopyMem ((VOID*)&(CertData->SignatureData[0]), KeyBuffer, WIN_CERT_UEFI_RSA2048_SIZE);

  free (PkKeyData);

  return EFI_SUCCESS;
}

BOOLEAN
IsX509FileDER (
  IN CONST UINT8             *X509Data,
  IN UINTN                   X509DataSize
  )
{
  X509     *X509Cert;

  //
  // Read DER-encoded X509 Certificate and Construct X509 object.
  //
  X509Cert = d2i_X509 (NULL, &X509Data, (long) X509DataSize);
  if (X509Cert == NULL) {
    return FALSE;
  }

  return TRUE;
}

BOOLEAN
IsX509FilePEM (
  IN CONST UINT8             *X509Data,
  IN UINTN                   X509DataSize
  )
{
  if (X509DataSize <= sizeof("-----BEGIN")) {
    return FALSE;
  }

  if (memcmp (X509Data, "-----BEGIN", sizeof("-----BEGIN") - 1) != 0) {
    return FALSE;
  }

  return TRUE;
}

EFI_STATUS
CreatePkX509CertificateList (
  IN  CHAR8                       *X509File,
  IN  EFI_GUID                    *SignatureOwner,
  OUT EFI_SIGNATURE_LIST          **Cert
  )
{
  STATUS                  Status;
  UINT8                   *X509Data = NULL;
  UINTN                   X509DataSize = 0;
  EFI_SIGNATURE_DATA      *CertData=NULL;

  Status = ReadInputFile (X509File, &X509Data, (UINT32 *) &X509DataSize, NULL);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "Unable to open file", X509File);
    return EFI_NOT_FOUND;
  }

  if (!IsX509FileDER (X509Data, X509DataSize)) {
    if (IsX509FilePEM (X509Data, X509DataSize)) {
      Error (NULL, 0, 0, "PEM format X509 file unsupported", X509File);
    } else {
      Error (NULL, 0, 0, "Non-DER format X509 file unsupported", X509File);
    }
    return EFI_UNSUPPORTED;
  }

  // Allocate space for PK certificate list and initialize it.
  // Create PK database entry w/ SignatureHeaderSize equals 0.
  //
  *Cert = (EFI_SIGNATURE_LIST*) malloc (
              sizeof(EFI_SIGNATURE_LIST) + sizeof(EFI_SIGNATURE_DATA) - 1
              + X509DataSize
              );
  if (*Cert == NULL) {
    Error (NULL, 0, 0, "Unable to allocate memory", NULL);
    return EFI_OUT_OF_RESOURCES;
  }

  (*Cert)->SignatureListSize   = (UINT32) (sizeof(EFI_SIGNATURE_LIST)
                                    + sizeof(EFI_SIGNATURE_DATA) - 1
                                    + X509DataSize);
  (*Cert)->SignatureSize       = (UINT32) (sizeof(EFI_SIGNATURE_DATA) - 1 + X509DataSize);
  (*Cert)->SignatureHeaderSize = 0;
  CopyMem (&(*Cert)->SignatureType, &gEfiCertX509Guid, sizeof(EFI_GUID));
  CertData                     = (EFI_SIGNATURE_DATA*) ((UINTN)(*Cert)
                                                          + sizeof(EFI_SIGNATURE_LIST)
                                                          + (*Cert)->SignatureHeaderSize);
  CopyMem (&CertData->SignatureOwner, SignatureOwner, sizeof(EFI_GUID));
  CopyMem ((VOID*)&(CertData->SignatureData[0]), X509Data, X509DataSize);

  free (X509Data);

  return EFI_SUCCESS;
}

EFI_STATUS
CreatePkX509CertificateListHash (
  IN  CHAR8                       *X509File,
  IN  EFI_GUID                    *SignatureOwner,
  IN  UINT32                      HashAlg,
  IN  EFI_TIME                    *Time,
  OUT EFI_SIGNATURE_LIST          **Cert
  )
{
  STATUS                  Status;
  UINT8                   *X509Data = NULL;
  UINTN                   X509DataSize = 0;
  EFI_SIGNATURE_DATA      *CertData=NULL;
  UINT8                   *TBSCert;
  UINTN                   TBSCertSize;
  EFI_CERT_X509_SHA256    X509Sha256;
  EFI_CERT_X509_SHA384    X509Sha384;
  EFI_CERT_X509_SHA512    X509Sha512;
  UINT8                   *X509Hash;
  UINTN                   X509HashSize;
  EVP_MD_CTX              ctx;
  const EVP_MD            *md;

  Status = ReadInputFile (X509File, &X509Data, (UINT32 *) &X509DataSize, NULL);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "Unable to open file", X509File);
    return EFI_NOT_FOUND;
  }

  if (!IsX509FileDER (X509Data, X509DataSize)) {
    if (IsX509FilePEM (X509Data, X509DataSize)) {
      Error (NULL, 0, 0, "PEM format X509 file unsupported", X509File);
    } else {
      Error (NULL, 0, 0, "Non-DER format X509 file unsupported", X509File);
    }
    return EFI_UNSUPPORTED;
  }

  //
  // Retrieve the TBSCertificate from the X.509 Certificate.
  //
  if (!X509GetTBSCert (X509Data, X509DataSize, &TBSCert, &TBSCertSize)) {
    return EFI_UNSUPPORTED;
  }

  switch (HashAlg) {
  case HASHALG_SHA256:
    md = EVP_sha256();
    EVP_DigestInit(&ctx, md);
    EVP_DigestUpdate(&ctx, TBSCert, TBSCertSize);
    EVP_DigestFinal(&ctx, (UINT8 *)&X509Sha256.ToBeSignedHash, NULL);
    CopyMem (&X509Sha256.TimeOfRevocation, Time, sizeof(EFI_TIME));
    X509Hash = (UINT8 *)&X509Sha256;
    X509HashSize = sizeof(X509Sha256);
    break;
  case HASHALG_SHA384:
    md = EVP_sha384();
    EVP_DigestInit(&ctx, md);
    EVP_DigestUpdate(&ctx, TBSCert, TBSCertSize);
    EVP_DigestFinal(&ctx, (UINT8 *)&X509Sha384.ToBeSignedHash, NULL);
    CopyMem (&X509Sha384.TimeOfRevocation, Time, sizeof(EFI_TIME));
    X509Hash = (UINT8 *)&X509Sha384;
    X509HashSize = sizeof(X509Sha384);
    break;
  case HASHALG_SHA512:
    md = EVP_sha512();
    EVP_DigestInit(&ctx, md);
    EVP_DigestUpdate(&ctx, TBSCert, TBSCertSize);
    EVP_DigestFinal(&ctx, (UINT8 *)&X509Sha512.ToBeSignedHash, NULL);
    CopyMem (&X509Sha512.TimeOfRevocation, Time, sizeof(EFI_TIME));
    X509Hash = (UINT8 *)&X509Sha512;
    X509HashSize = sizeof(X509Sha512);
    break;
  default:
    assert (FALSE);
    md = NULL;
    X509Hash = NULL;
    X509HashSize = 0;
    break;
  }

  // Allocate space for PK certificate list and initialize it.
  // Create PK database entry w/ SignatureHeaderSize equals 0.
  //
  *Cert = (EFI_SIGNATURE_LIST*) malloc (
              sizeof(EFI_SIGNATURE_LIST) + sizeof(EFI_SIGNATURE_DATA) - 1
              + X509HashSize
              );
  if (*Cert == NULL) {
    Error (NULL, 0, 0, "Unable to allocate memory", NULL);
    return EFI_OUT_OF_RESOURCES;
  }

  (*Cert)->SignatureListSize   = (UINT32) (sizeof(EFI_SIGNATURE_LIST)
                                    + sizeof(EFI_SIGNATURE_DATA) - 1
                                    + X509HashSize);
  (*Cert)->SignatureSize       = (UINT32) (sizeof(EFI_SIGNATURE_DATA) - 1 + X509HashSize);
  (*Cert)->SignatureHeaderSize = 0;
  switch (HashAlg) {
  case HASHALG_SHA256:
    CopyMem (&(*Cert)->SignatureType, &gEfiCertX509Sha256Guid, sizeof(EFI_GUID));
    break;
  case HASHALG_SHA384:
    CopyMem (&(*Cert)->SignatureType, &gEfiCertX509Sha384Guid, sizeof(EFI_GUID));
    break;
  case HASHALG_SHA512:
    CopyMem (&(*Cert)->SignatureType, &gEfiCertX509Sha512Guid, sizeof(EFI_GUID));
    break;
  }
  CertData                     = (EFI_SIGNATURE_DATA*) ((UINTN)(*Cert)
                                                          + sizeof(EFI_SIGNATURE_LIST)
                                                          + (*Cert)->SignatureHeaderSize);
  CopyMem (&CertData->SignatureOwner, SignatureOwner, sizeof(EFI_GUID));
  CopyMem ((VOID*)&(CertData->SignatureData[0]), X509Hash, X509HashSize);

  free (X509Data);

  return EFI_SUCCESS;
}

EFI_STATUS
EnrollPlatformKey (
  IN  CHAR8                       *PkFile,
  IN  EFI_GUID                    *SignatureOwner
  )
{
  EFI_STATUS                  EfiStatus;
  EFI_SIGNATURE_LIST          *PkCert;

  EfiStatus = CreatePkX509CertificateList (
                PkFile,
                SignatureOwner,
                &PkCert
                );
  if (EFI_ERROR (EfiStatus)) {
    printf ("EnrollPlatformKey - CreatePkX509CertificateList fail!\n");
    return EfiStatus;
  }

  EfiStatus = CreateVariableList (
                &mVarListEntry,
                EFI_PLATFORM_KEY_NAME,
                &gEfiGlobalVariableGuid,
                EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS,
                NULL,
                PkCert->SignatureListSize,
                (UINT8 *)PkCert,
                FALSE
                );
  if (!EFI_ERROR (EfiStatus)) {
    printf ("EnrollPlatformKey - success!\n");
  } else {
    printf ("EnrollPlatformKey - fail!\n");
    return EfiStatus;
  }

  return EfiStatus;
}

EFI_STATUS
DeletePlatformKey (
  VOID
  )
{
  EFI_STATUS  EfiStatus;

  EfiStatus = DeleteVariableList (
                &mVarListEntry,
                EFI_PLATFORM_KEY_NAME,
                &gEfiGlobalVariableGuid
                );
  if (EFI_ERROR (EfiStatus)) {
    printf ("DeletePlatformKey - not found!\n");
    return EfiStatus;
  }
  printf ("DeletePlatformKey - success!\n");
  return EfiStatus;
}

EFI_STATUS
EnrollKeyExchangeKey (
  IN  CHAR8                       *PkFile,
  IN  EFI_GUID                    *SignatureOwner,
  IN  BOOLEAN                     Append,
  IN  BOOLEAN                     IsCertFile
  )
{
  EFI_STATUS                  EfiStatus;
  EFI_SIGNATURE_LIST          *KekCert;

  if (IsCertFile) {
    EfiStatus = CreatePkX509CertificateList (
                  PkFile,
                  SignatureOwner,
                  &KekCert
                  );
    if (EFI_ERROR (EfiStatus)) {
      printf ("EnrollKeyExchangeKey - CreatePkX509CertificateList fail!\n");
      return EfiStatus;
    }
  } else {
    EfiStatus = CreatePkCertificateList (
                  PkFile,
                  SignatureOwner,
                  &KekCert
                  );
    if (EFI_ERROR (EfiStatus)) {
      printf ("EnrollKeyExchangeKey - CreatePkCertificateList fail!\n");
      return EfiStatus;
    }
  }

  EfiStatus = CreateVariableList (
                &mVarListEntry,
                EFI_KEY_EXCHANGE_KEY_NAME,
                &gEfiGlobalVariableGuid,
                EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS,
                NULL,
                KekCert->SignatureListSize,
                (UINT8 *)KekCert,
                Append
                );
  if (!EFI_ERROR (EfiStatus)) {
    printf ("EnrollKeyExchangeKey - success!\n");
  } else {
    printf ("EnrollKeyExchangeKey - fail!\n");
  }

  return EFI_SUCCESS;
}

EFI_STATUS
DeleteKeyExchangeKey (
  VOID
  )
{
  EFI_STATUS  EfiStatus;

  EfiStatus = DeleteVariableList (
                &mVarListEntry,
                EFI_KEY_EXCHANGE_KEY_NAME,
                &gEfiGlobalVariableGuid
                );
  if (EFI_ERROR (EfiStatus)) {
    printf ("DeleteKeyExchangeKey - not found!\n");
    return EfiStatus;
  }
  printf ("DeleteKeyExchangeKey - success!\n");
  return EfiStatus;
}

EFI_STATUS
EnrollSignatureDBHash (
  IN  CHAR8                       *PkFile,
  IN  EFI_GUID                    *SignatureOwner,
  IN  BOOLEAN                     Append,
  IN  UINT8                       DbIndex,
  IN  UINT32                      HashAlg,
  IN  EFI_TIME                    *Time
  )
{
  EFI_STATUS                  EfiStatus;
  EFI_SIGNATURE_LIST          *DbCert;
  CHAR16                      *Name;

  EfiStatus = CreatePkX509CertificateListHash (
                PkFile,
                SignatureOwner,
                HashAlg,
                Time,
                &DbCert
                );
  if (EFI_ERROR (EfiStatus)) {
    printf ("EnrollSignatureDBHash - CreatePkX509CertificateListHash fail!\n");
    return EfiStatus;
  }

  switch (DbIndex) {
  case 0:
    Name = EFI_IMAGE_SECURITY_DATABASE;
    break;
  case 1:
    Name = EFI_IMAGE_SECURITY_DATABASE1;
    break;
  case 2:
    Name = EFI_IMAGE_SECURITY_DATABASE2;
    break;
  default:
    Name = NULL;
    assert(FALSE);
    break;
  }

  ASSERT (Name != NULL);
  EfiStatus = CreateVariableList (
                &mVarListEntry,
                Name,
                &gEfiImageSecurityDatabaseGuid,
                EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS,
                NULL,
                DbCert->SignatureListSize,
                (UINT8 *)DbCert,
                Append
                );
  if (!EFI_ERROR (EfiStatus)) {
    printf ("EnrollSignatureDBHash - success!\n");
  } else {
    printf ("EnrollSignatureDBHash - fail!\n");
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EnrollSignatureDB (
  IN  CHAR8                       *PkFile,
  IN  EFI_GUID                    *SignatureOwner,
  IN  BOOLEAN                     Append,
  IN  UINT8                       DbIndex,
  IN  BOOLEAN                     IsCertFile
  )
{
  EFI_STATUS                  EfiStatus;
  EFI_SIGNATURE_LIST          *DbCert;
  CHAR16                      *Name;

  if (IsCertFile) {
    EfiStatus = CreatePkX509CertificateList (
                  PkFile,
                  SignatureOwner,
                  &DbCert
                  );
    if (EFI_ERROR (EfiStatus)) {
      printf ("EnrollSignatureDB - CreatePkX509CertificateList fail!\n");
      return EfiStatus;
    }
  } else {
    EfiStatus = CreateImageCertificateList (
                  PkFile,
                  SignatureOwner,
                  &DbCert
                  );
    if (EFI_ERROR (EfiStatus)) {
      printf ("EnrollSignatureDB - CreateImageCertificateList fail!\n");
      return EfiStatus;
    }
  }

  switch (DbIndex) {
  case 0:
    Name = EFI_IMAGE_SECURITY_DATABASE;
    break;
  case 1:
    Name = EFI_IMAGE_SECURITY_DATABASE1;
    break;
  case 2:
    Name = EFI_IMAGE_SECURITY_DATABASE2;
    break;
  default:
    Name = NULL;
    assert(FALSE);
    break;
  }

  ASSERT (Name != NULL);
  EfiStatus = CreateVariableList (
                &mVarListEntry,
                Name,
                &gEfiImageSecurityDatabaseGuid,
                EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS,
                NULL,
                DbCert->SignatureListSize,
                (UINT8 *)DbCert,
                Append
                );
  if (!EFI_ERROR (EfiStatus)) {
    printf ("EnrollSignatureDB - success!\n");
  } else {
    printf ("EnrollSignatureDB - fail!\n");
  }

  return EFI_SUCCESS;
}

EFI_STATUS
DeleteSignatureDB (
  IN  UINT8  DbIndex
  )
{
  CHAR16      *Name;
  EFI_STATUS  EfiStatus;

  switch (DbIndex) {
  case 0:
    Name = EFI_IMAGE_SECURITY_DATABASE;
    break;
  case 1:
    Name = EFI_IMAGE_SECURITY_DATABASE1;
    break;
  case 2:
    Name = EFI_IMAGE_SECURITY_DATABASE2;
    break;
  default:
    Name = NULL;
    assert(FALSE);
    break;
  }

  ASSERT (Name != NULL);
  EfiStatus = DeleteVariableList (
                &mVarListEntry,
                Name,
                &gEfiImageSecurityDatabaseGuid
                );
  if (EFI_ERROR (EfiStatus)) {
    printf ("DeleteSignatureDB - not found!\n");
    return EfiStatus;
  }
  printf ("DeleteSignatureDB - success!\n");
  return EfiStatus;
}

STATUS
ProcessPk (
  IN INTN   argc,
  IN CHAR8  **argv
  )
{
  EFI_GUID                    Guid;

  if ((strcmp (argv[4], "ADD") == 0) ||
      (strcmp (argv[4], "add") == 0)) {
    if ((argc != 7) && (argc != 9)) {
      Error (NULL, 0, 0, "PK ADD: invalid number of input parameters specified", NULL);
      return STATUS_ERROR;
    }
    if ((strcmp (argv[5], "-F") != 0) &&
        (strcmp (argv[5], "-f") != 0)) {
      Error (NULL, 0, 0, "PK ADD: -F is not specified", NULL);
      return STATUS_ERROR;
    }
    if (argc == 9) {
      if ((strcmp (argv[7], "-G") != 0) &&
          (strcmp (argv[7], "-g") != 0)) {
        Error (NULL, 0, 0, "PK ADD: -G is not specified", NULL);
        return STATUS_ERROR;
      }
      if (!IsGuidData (argv[8], &Guid)) {
        Error (NULL, 0, 0, "PK ADD: Unknown Guid - ", argv[8]);
        return STATUS_ERROR;
      }
    } else {
      CopyMem (&Guid, &gEfiGlobalVariableGuid, sizeof(Guid));
    }
    return EnrollPlatformKey (argv[6], &Guid);
  } else if ((strcmp (argv[4], "DEL") == 0) ||
             (strcmp (argv[4], "del") == 0)) {
    if (argc != 5) {
      Error (NULL, 0, 0, "PK DEL: invalid number of input parameters specified", NULL);
      return STATUS_ERROR;
    }
    return DeletePlatformKey ();
  }
  Error (NULL, 0, 0, "PK: Unknown SubCommand - ", argv[4]);
  return STATUS_ERROR;
}

STATUS
ProcessKek (
  IN INTN   argc,
  IN CHAR8  **argv
  )
{
  EFI_GUID                    Guid;
  BOOLEAN                     Append;
  BOOLEAN                     IsCertFile;

  if ((strcmp (argv[4], "ADD") == 0) ||
      (strcmp (argv[4], "add") == 0) ||
      (strcmp (argv[4], "APPEND") == 0) ||
      (strcmp (argv[4], "append") == 0)) {
    if (argc != 9) {
      Error (NULL, 0, 0, "KEK ADD|APPEND: invalid number of input parameters specified", NULL);
      return STATUS_ERROR;
    }
    if ((strcmp (argv[5], "-F") != 0) &&
        (strcmp (argv[5], "-f") != 0) &&
        (strcmp (argv[5], "-K") != 0) &&
        (strcmp (argv[5], "-k") != 0)) {
      Error (NULL, 0, 0, "KEK ADD|APPEND: -F|-K is not specified", NULL);
      return STATUS_ERROR;
    }
    if ((strcmp (argv[7], "-G") != 0) &&
        (strcmp (argv[7], "-g") != 0)) {
      Error (NULL, 0, 0, "KEK ADD|APPEND: -G is not specified", NULL);
      return STATUS_ERROR;
    }
    if (!IsGuidData (argv[8], &Guid)) {
      Error (NULL, 0, 0, "KEK ADD|APPEND: Unknown Guid - ", argv[8]);
      return STATUS_ERROR;
    }
    if ((strcmp (argv[4], "APPEND") == 0) ||
        (strcmp (argv[4], "append") == 0)) {
      Append = TRUE;
    } else {
      Append = FALSE;
    }
    if ((strcmp (argv[5], "-F") == 0) ||
        (strcmp (argv[5], "-f") == 0)) {
      IsCertFile = TRUE;
    } else {
      IsCertFile = FALSE;
    }
    return EnrollKeyExchangeKey (argv[6], &Guid, Append, IsCertFile);
  } else if ((strcmp (argv[4], "DEL") == 0) ||
             (strcmp (argv[4], "del") == 0)) {
    if (argc != 5) {
      Error (NULL, 0, 0, "KEK DEL: invalid number of input parameters specified", NULL);
      return STATUS_ERROR;
    }
    return DeleteKeyExchangeKey ();
  }
  Error (NULL, 0, 0, "KEK: Unknown SubCommand - ", argv[4]);
  return STATUS_ERROR;
}

STATUS
ProcessDb (
  IN INTN   argc,
  IN CHAR8  **argv,
  IN UINT8  DbIndex
  )
{
  EFI_GUID                    Guid;
  BOOLEAN                     Append;
  BOOLEAN                     IsCertFile;
  UINT32                      HashAlg;
  EFI_TIME                    Time;

  if ((strcmp (argv[4], "ADD") == 0) ||
      (strcmp (argv[4], "add") == 0) ||
      (strcmp (argv[4], "APPEND") == 0) ||
      (strcmp (argv[4], "append") == 0)) {
    if (argc < 9) {
      Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: invalid number of input parameters specified", NULL);
      return STATUS_ERROR;
    }
    if ((strcmp (argv[5], "-F") != 0) &&
        (strcmp (argv[5], "-f") != 0) &&
        (strcmp (argv[5], "-I") != 0) &&
        (strcmp (argv[5], "-i") != 0)) {
      Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: -F|-I is not specified", NULL);
      return STATUS_ERROR;
    }
    if ((strcmp (argv[7], "-G") != 0) &&
        (strcmp (argv[7], "-g") != 0)) {
      Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: -G is not specified", NULL);
      return STATUS_ERROR;
    }
    if (!IsGuidData (argv[8], &Guid)) {
      Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: Unknown Guid - ", argv[8]);
      return STATUS_ERROR;
    }
    if ((strcmp (argv[4], "APPEND") == 0) ||
        (strcmp (argv[4], "append") == 0)) {
      Append = TRUE;
    } else {
      Append = FALSE;
    }
    if ((strcmp (argv[5], "-F") == 0) ||
        (strcmp (argv[5], "-f") == 0)) {
      IsCertFile = TRUE;
    } else {
      IsCertFile = FALSE;
    }
    if (argc == 9) {
      return EnrollSignatureDB (argv[6], &Guid, Append, DbIndex, IsCertFile);
    }
    //
    // Hash
    //
    if (argc < 11) {
      Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: invalid number of paramter for cert hash", NULL);
    }
    if ((strcmp (argv[9], "-H") != 0) &&
        (strcmp (argv[9], "-h") != 0)) {
      Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: -H is not specified", NULL);
      return STATUS_ERROR;
    }
    HashAlg = HASHALG_MAX;
    if ((strcmp (argv[10], "SHA256") == 0) ||
        (strcmp (argv[10], "sha256") == 0) ) {
      HashAlg = HASHALG_SHA256;
    } else if ((strcmp (argv[10], "SHA384") == 0) ||
               (strcmp (argv[10], "sha384") == 0) ) {
      HashAlg = HASHALG_SHA384;
    } else if ((strcmp (argv[10], "SHA512") == 0) ||
               (strcmp (argv[10], "sha512") == 0) ) {
      HashAlg = HASHALG_SHA512;
    }
    if (HashAlg == HASHALG_MAX) {
      Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: Unknown Hash Algorithm", NULL);
      return STATUS_ERROR;
    }
    ZeroMem (&Time, sizeof(EFI_TIME));
    if (argc != 11) {
      if (argc != 15) {
        Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: invalid number of paramter for cert time", NULL);
        return STATUS_ERROR;
      }
      if ((strcmp (argv[11], "-DATE") != 0) &&
          (strcmp (argv[11], "-date") != 0)) {
        Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: -DATE is not specified", NULL);
        return STATUS_ERROR;
      }
      if (!IsDateData (argv[12], &Time)) {
        Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: Unknown Date - ", argv[12]);
        return STATUS_ERROR;
      }
      if ((strcmp (argv[13], "-TIME") != 0) &&
          (strcmp (argv[13], "-time") != 0)) {
        Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: -TIME is not specified", NULL);
        return STATUS_ERROR;
      }
      if (!IsTimeData (argv[14], &Time)) {
        Error (NULL, 0, 0, "db|dbx|dbt ADD|APPEND: Unknown Time - ", argv[14]);
        return STATUS_ERROR;
      }
    }
    return EnrollSignatureDBHash (argv[6], &Guid, Append, DbIndex, HashAlg, &Time);
  } else if ((strcmp (argv[4], "DEL") == 0) ||
             (strcmp (argv[4], "del") == 0)) {
    if (argc != 5) {
      Error (NULL, 0, 0, "db|dbx|dbt DEL: invalid number of input parameters specified", NULL);
      return STATUS_ERROR;
    }
    return DeleteSignatureDB (DbIndex);
  }
  Error (NULL, 0, 0, "db|dbx|dbt: Unknown SubCommand - ", argv[4]);
  return STATUS_ERROR;
}

EFI_STATUS
EnrollVar (
  IN CHAR8       *Name,
  IN EFI_GUID    *Guid,
  IN UINT32      Attributes,
  IN UINTN       DataSize,
  IN VOID        *Data,
  IN BOOLEAN     TimeBased,
  IN BOOLEAN     Append
  )
{
  EFI_STATUS  EfiStatus;
  CHAR16      *UnicodeBuf;
  UINT8       *Payload;
  UINTN       PayloadSize;
  EFI_TIME    *TimeStamp;

  UnicodeBuf = malloc ((strlen(Name) + 1) * sizeof(CHAR16));
  if (UnicodeBuf == NULL) {
    Error (NULL, 0, 0, "Unable to allocate memory for variable name", NULL);
    return EFI_OUT_OF_RESOURCES;
  }

  Ascii2UnicodeString (Name, UnicodeBuf);

  TimeStamp = NULL;
  Payload = (UINT8 *) Data;
  PayloadSize = DataSize;
  if (TimeBased) {
    TimeStamp = &((EFI_VARIABLE_AUTHENTICATION_2 *) Data)->TimeStamp;
    Payload = (UINT8 *) Data + AUTHINFO2_SIZE (Data);
    PayloadSize = DataSize - AUTHINFO2_SIZE (Data);
  }

  EfiStatus = CreateVariableList (
                &mVarListEntry,
                UnicodeBuf,
                Guid,
                Attributes,
                TimeStamp,
                PayloadSize,
                Payload,
                Append
                );
  if (!EFI_ERROR (EfiStatus)) {
    printf ("EnrollVar - success!\n");
  } else {
    printf ("EnrollVar - fail!\n");
  }
  free (UnicodeBuf);
  return EfiStatus;
}

EFI_STATUS
DeleteVar (
  IN CHAR8       *Name,
  IN EFI_GUID    *Guid
  )
{
  EFI_STATUS  EfiStatus;
  CHAR16      *UnicodeBuf;

  UnicodeBuf = malloc ((strlen(Name) + 1) * sizeof(CHAR16));
  if (UnicodeBuf == NULL) {
    Error (NULL, 0, 0, "Unable to allocate memory", NULL);
    return EFI_OUT_OF_RESOURCES;
  }

  Ascii2UnicodeString (Name, UnicodeBuf);

  EfiStatus = DeleteVariableList (
                &mVarListEntry,
                UnicodeBuf,
                Guid
                );
  if (EFI_ERROR (EfiStatus)) {
    printf ("DeleteVar - not found!\n");
  } else {
    printf ("DeleteVar - success!\n");
  }
  free (UnicodeBuf);
  return EfiStatus;
}

/*
  This function will check and parse the command line parameter.

  @param[in]    argc                    The number of input parameters.
  @param[in]    argv                    Point to input each parameters.
  @param[out]   SubCmd                  Point to the operation type.

  @retval       EFI_SUCCESS             All input parameters are valid.
  @retval       EFI_INVALID_PARAMETER   The number of input parameters or
                                        input parameters are invalid.
*/
EFI_STATUS
ParsingVariableParams (
  IN    INTN                      argc,
  IN    CHAR8                     **argv,
  OUT   EFI_COMMAND_OPER_TYPE     *SubCmd
  )
{
  CHAR8     *SubCmdPtr;
  UINTN     Index;

  if (argc != 9 && argc != 13 && argc != 14) {
    Error (NULL, 0, 0, "VAR: invalid number of input parameters specified", NULL);
    return EFI_INVALID_PARAMETER;
  }

  if (argv == NULL || SubCmd == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  SubCmdPtr = malloc (strlen (argv[4]) + 1);
  if (SubCmdPtr == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  memset (SubCmdPtr, 0, strlen (argv[4]) + 1);
  strncpy (SubCmdPtr, argv[4], strlen (argv[4]));

  for (Index = 0; Index < strlen (argv[4]) + 1; Index = Index + 1) {
    //
    //  Convert lower letter to upper one.
    //
    if ((SubCmdPtr[Index] >= 'a') && (SubCmdPtr[Index] <= 'z')) {
      SubCmdPtr[Index] -= 32;
    }
  }

  if (strcmp (SubCmdPtr, "ADD") == 0) {
    *SubCmd = VariableTypeAdd;
  } else if (strcmp (SubCmdPtr, "DEL") == 0) {
    *SubCmd = VariableTypeDel;
  } else if (strcmp (SubCmdPtr, "APPEND") == 0) {
    *SubCmd = VariableTypeAppend;
  } else {
    Error (NULL, 0, 0, "VAR: Unknown SubCommand - ", argv[4]);
    return EFI_INVALID_PARAMETER;
  }

  if ( (strcmp (argv[5], "-N") != 0) &&
       (strcmp (argv[5], "-n") != 0)
     ) {
    Error (NULL, 0, 0, "VAR: -N is not specified", NULL);
    return EFI_INVALID_PARAMETER;
  }

  if ( (strcmp (argv[7], "-G") != 0) &&
       (strcmp (argv[7], "-g") != 0)
     ) {
    Error (NULL, 0, 0, "VAR: -G is not specified", NULL);
    return EFI_INVALID_PARAMETER;
  }

  if (argc >= 13) {
    if ( (strcmp (argv[9], "-A") != 0) &&
         (strcmp (argv[9], "-a") != 0)
       ) {
      Error (NULL, 0, 0, "VAR: -A is not specified", NULL);
      return EFI_INVALID_PARAMETER;
    }
    if ( (strcmp (argv[11], "-D") != 0) &&
         (strcmp (argv[11], "-d") != 0)
       ) {
      Error (NULL, 0, 0, "VAR: -D is not specified", NULL);
      return EFI_INVALID_PARAMETER;
    }
  }

  if (argc == 14) {
    if ( (strcmp (argv[13], "-T") != 0) &&
         (strcmp (argv[13], "-t") != 0)
       ) {
      Error (NULL, 0, 0, "VAR: -T is not specified", NULL);
      return EFI_INVALID_PARAMETER;
    }
  }

  return EFI_SUCCESS;
}

STATUS
ProcessVar (
  IN INTN   argc,
  IN CHAR8  **argv
  )
{
  EFI_STATUS                  VerifyStatus;
  EFI_COMMAND_OPER_TYPE       CommandType;
  EFI_GUID                    Guid;
  UINT8                       *Data;
  UINTN                       DataSize;
  STATUS                      Status;
  UINT32                      Attributes;
  BOOLEAN                     TimeBased;

  Attributes                  = 0;
  Data                        = NULL;
  DataSize                    = 0;

  VerifyStatus = ParsingVariableParams (argc, argv, &CommandType);
  if (EFI_ERROR (VerifyStatus)) {
    return VerifyStatus;
  }

  //
  //  Make "certdb" variable as private variable.
  //
  if (strcmp(argv[6], "certdb") == 0) {
    Error (NULL, 0, 0, "Invalid variable name.", NULL);
    return STATUS_ERROR;
  }

  if (!IsGuidData (argv[8], &Guid)) {
    Error (NULL, 0, 0, "Unknown Guid - ", argv[8]);
    return STATUS_ERROR;
  }

  if (argc >= 13) {
    Attributes = xtoi (argv[10]);
    Status = ReadInputFile (argv[12], &Data, (UINT32 *) &DataSize, NULL);
    if (Status != STATUS_SUCCESS) {
      Error (NULL, 0, 0, "Can not get data - ", argv[12]);
      return STATUS_ERROR;
    }
  }

  TimeBased = (argc == 14) ? TRUE : FALSE;
  if ( ((Attributes & EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS) != 0) &&
        !TimeBased
     ) {
    Error (NULL, 0, 0, "EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS set is not matching -T flag.", NULL);
    return STATUS_ERROR;
  }

  if ( ((Attributes & EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS) == 0) &&
       TimeBased
     ) {
    Error (NULL, 0, 0, "EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS set is not matching -T flag.", NULL);
    return STATUS_ERROR;
  }

  //
  //  Non-timebased or "db","dbx","dbt","PK","KEY" variable will use previous logic to handling.
  //
  if ( strcmp(argv[6], "db") == 0 ||
       strcmp(argv[6], "dbx") == 0 ||
       strcmp(argv[6], "dbt") == 0 ||
       strcmp(argv[6], "PK") == 0 ||
       strcmp(argv[6], "KEY") == 0 ||
       !TimeBased
    ) {
    if (CommandType == VariableTypeDel) {
      Status = DeleteVar (argv[6], &Guid);
    } else {
      Status = EnrollVar (
                 argv[6],
                 &Guid,
                 Attributes,
                 DataSize,
                 Data,
                 TimeBased,
                 CommandType == VariableTypeAppend ? TRUE : FALSE
                 );
    }
  } else {
    Status = ProcessAuthVar (
               argv[6],
               &Guid,
               Data,
               DataSize,
               Attributes,
               CommandType
               );
  }

  FREE_NON_NULL_PTR (Data);
  return Status;
}

VOID
DumpTimestamp (
  IN EFI_TIME            *TimeOfRevocation
  )
{
  printf ("  %02d/%02d/%04d %02d:%02d:%02d\n",
    TimeOfRevocation->Month,
    TimeOfRevocation->Day,
    TimeOfRevocation->Year,
    TimeOfRevocation->Hour,
    TimeOfRevocation->Minute,
    TimeOfRevocation->Second
    );
}

VOID
DumpCert (
  IN  UINT8          *Buffer,
  IN  UINTN          Size
  )
{
  EFI_SIGNATURE_LIST               *CertList;
  EFI_SIGNATURE_DATA               *Cert;
  UINT32                           CertCount;
  UINT32                           CertListIndex;
  UINT32                           CertIndex;

  CertListIndex = 0;
  CertList = (EFI_SIGNATURE_LIST *)Buffer;
  while ((UINTN)CertList < (UINTN)Buffer + Size) {
    printf ("SIGNATURE_LIST[%d]\n", CertListIndex);
    printf ("  SignatureType       - %08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x\n",
      CertList->SignatureType.Data1,
      CertList->SignatureType.Data2,
      CertList->SignatureType.Data3,
      CertList->SignatureType.Data4[0],
      CertList->SignatureType.Data4[1],
      CertList->SignatureType.Data4[2],
      CertList->SignatureType.Data4[3],
      CertList->SignatureType.Data4[4],
      CertList->SignatureType.Data4[5],
      CertList->SignatureType.Data4[6],
      CertList->SignatureType.Data4[7]
      );
    printf ("  SignatureListSize   - %08x\n", CertList->SignatureListSize);
    printf ("  SignatureHeaderSize - %08x\n", CertList->SignatureHeaderSize);
    printf ("  SignatureSize       - %08x\n", CertList->SignatureSize);
    Cert = (EFI_SIGNATURE_DATA *)((UINT8 *)CertList + sizeof(EFI_SIGNATURE_LIST) + CertList->SignatureHeaderSize);
    CertCount = (CertList->SignatureListSize - sizeof(EFI_SIGNATURE_LIST) - CertList->SignatureHeaderSize) / CertList->SignatureSize;
    for (CertIndex = 0; CertIndex < CertCount; CertIndex++) {
      printf ("  SIGNATURE_DATA[%d]\n", CertIndex);
      printf ("    SignatureOwner    - %08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x\n",
        Cert->SignatureOwner.Data1,
        Cert->SignatureOwner.Data2,
        Cert->SignatureOwner.Data3,
        Cert->SignatureOwner.Data4[0],
        Cert->SignatureOwner.Data4[1],
        Cert->SignatureOwner.Data4[2],
        Cert->SignatureOwner.Data4[3],
        Cert->SignatureOwner.Data4[4],
        Cert->SignatureOwner.Data4[5],
        Cert->SignatureOwner.Data4[6],
        Cert->SignatureOwner.Data4[7]
        );
      printf ("    Signature         - \n");
      if (CompareGuid (&CertList->SignatureType, &gEfiCertX509Sha256Guid) == 0) {
        EFI_CERT_X509_SHA256  *CertX509Sha256;
        CertX509Sha256 = (EFI_CERT_X509_SHA256 *)Cert->SignatureData;
        printf ("      SHA256          - \n");
        DumpHex (CertX509Sha256->ToBeSignedHash, sizeof(CertX509Sha256->ToBeSignedHash));
        printf ("      Timestamp       - \n");
        DumpTimestamp (&CertX509Sha256->TimeOfRevocation);
      } else if (CompareGuid (&CertList->SignatureType, &gEfiCertX509Sha384Guid) == 0) {
        EFI_CERT_X509_SHA384  *CertX509Sha384;
        CertX509Sha384 = (EFI_CERT_X509_SHA384 *)Cert->SignatureData;
        printf ("      SHA384          - \n");
        DumpHex (CertX509Sha384->ToBeSignedHash, sizeof(CertX509Sha384->ToBeSignedHash));
        printf ("      Timestamp       - \n");
        DumpTimestamp (&CertX509Sha384->TimeOfRevocation);
      } else if (CompareGuid (&CertList->SignatureType, &gEfiCertX509Sha512Guid) == 0) {
        EFI_CERT_X509_SHA512  *CertX509Sha512;
        CertX509Sha512 = (EFI_CERT_X509_SHA512 *)Cert->SignatureData;
        printf ("      SHA512          - \n");
        DumpHex (CertX509Sha512->ToBeSignedHash, sizeof(CertX509Sha512->ToBeSignedHash));
        printf ("      Timestamp       - \n");
        DumpTimestamp (&CertX509Sha512->TimeOfRevocation);
      } else {
        DumpHex (Cert->SignatureData, CertList->SignatureSize - (sizeof(EFI_SIGNATURE_DATA) - 1));
      }
      Cert = (EFI_SIGNATURE_DATA *)((UINT8 *)Cert + CertList->SignatureSize);
    }
    CertList = (EFI_SIGNATURE_LIST *)((UINT8 *)CertList + CertList->SignatureListSize);
    CertListIndex ++;
  }

}

VOID
DumpVarStorage (
  IN VARIABLE_INFO_PRIVATE   *Storage,
  IN BOOLEAN                 IsDumpCert
  )
{
  printf ("Variable:\n");
  printf ("  Name       - %S\n", (wchar_t*)Storage->Name);
  printf ("  Guid       - %08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x\n",
    Storage->Guid.Data1,
    Storage->Guid.Data2,
    Storage->Guid.Data3,
    Storage->Guid.Data4[0],
    Storage->Guid.Data4[1],
    Storage->Guid.Data4[2],
    Storage->Guid.Data4[3],
    Storage->Guid.Data4[4],
    Storage->Guid.Data4[5],
    Storage->Guid.Data4[6],
    Storage->Guid.Data4[7]
    );
  printf ("  Attributes - %08x\n", Storage->Attributes);
  printf ("  Size       - %08x\n", (UINT32) Storage->Size);
  printf ("  Buffer     - \n");
  if (IsDumpCert) {
    DumpCert (Storage->Buffer, Storage->Size);
  } else {
    DumpHex (Storage->Buffer, Storage->Size);
  }
  printf ("\n");
}

VOID
DumpInfo (
  IN  CHAR16         *Name,
  IN  EFI_GUID       *Guid
  )
{
  LIST_ENTRY              *Link;
  VARIABLE_INFO_PRIVATE   *Storage;

  Link = FindVariableList (
           &mVarListEntry,
           Name,
           Guid
           );
  if (Link == NULL) {
    printf ("DumpInfo - not found!\n");
    return ;
  }
  Storage = VARIABLE_INFO_PRIVATE_FROM_LINK (Link);

  DumpVarStorage (Storage, TRUE);

  return ;
}

VOID
DumpVariableList (
  IN  LIST_ENTRY     *StorageListHead
  )
{
  LIST_ENTRY              *Link;
  VARIABLE_INFO_PRIVATE   *Storage;

  if (StorageListHead->ForwardLink != NULL) {
    Link = GetFirstNode (StorageListHead);
    while (!IsNull (StorageListHead, Link)) {
      Storage = VARIABLE_INFO_PRIVATE_FROM_LINK (Link);
      DumpVarStorage (Storage, FALSE);
      Link = GetNextNode (StorageListHead, Link);
    }
  }
}

STATUS
ProcessInfo (
  IN INTN   argc,
  IN CHAR8  **argv
  )
{
  if ((argc == 4) &&
      ((strcmp (argv[3], "PK") == 0) ||
       (strcmp (argv[3], "pk") == 0))) {
     DumpInfo (EFI_PLATFORM_KEY_NAME, &gEfiGlobalVariableGuid);
     return STATUS_SUCCESS;
  }
  else if ((argc == 4) &&
      ((strcmp (argv[3], "KEK") == 0) ||
       (strcmp (argv[3], "kek") == 0))) {
     DumpInfo (EFI_KEY_EXCHANGE_KEY_NAME, &gEfiGlobalVariableGuid);
     return STATUS_SUCCESS;
  }
  else if ((argc == 4) &&
      ((strcmp (argv[3], "DB") == 0) ||
       (strcmp (argv[3], "db") == 0))) {
     DumpInfo (EFI_IMAGE_SECURITY_DATABASE, &gEfiImageSecurityDatabaseGuid);
     return STATUS_SUCCESS;
  }
  else if ((argc == 4) &&
      ((strcmp (argv[3], "DBX") == 0) ||
       (strcmp (argv[3], "dbx") == 0))) {
     DumpInfo (EFI_IMAGE_SECURITY_DATABASE1, &gEfiImageSecurityDatabaseGuid);
     return STATUS_SUCCESS;
  }
  else if ((argc == 4) &&
      ((strcmp (argv[3], "DBT") == 0) ||
       (strcmp (argv[3], "dbt") == 0))) {
     DumpInfo (EFI_IMAGE_SECURITY_DATABASE2, &gEfiImageSecurityDatabaseGuid);
     return STATUS_SUCCESS;
  }
  else if ((argc == 4) &&
      ((strcmp (argv[3], "ALL") == 0) ||
       (strcmp (argv[3], "all") == 0))) {
     DumpVariableList (&mVarListEntry);
     return STATUS_SUCCESS;
  }
  Error (NULL, 0, 0, "INFO: Unknown SubCommand - ", argv[3]);
  return STATUS_ERROR;
}

STATUS
ProcessKey (
  IN INTN   argc,
  IN CHAR8  **argv
  )
{
  if ((strcmp (argv[2], "INFO") == 0) ||
      (strcmp (argv[2], "info") == 0)) {
    return ProcessInfo (argc, argv);
  }
  if ((strcmp (argv[3], "VAR") == 0) ||
      (strcmp (argv[3], "var") == 0)) {
    return ProcessVar (argc, argv);
  }
  else if ((strcmp (argv[3], "PK") == 0) ||
           (strcmp (argv[3], "pk") == 0)) {
     return ProcessPk (argc, argv);
  }
  else if ((strcmp (argv[3], "KEK") == 0) ||
           (strcmp (argv[3], "kek") == 0)) {
    return ProcessKek (argc, argv);
  }
  else if ((strcmp (argv[3], "DB") == 0) ||
           (strcmp (argv[3], "db") == 0)) {
    return ProcessDb (argc, argv, 0);
  }
  else if ((strcmp (argv[3], "DBX") == 0) ||
           (strcmp (argv[3], "dbx") == 0)) {
    return ProcessDb (argc, argv, 1);
  }
  else if ((strcmp (argv[3], "DBT") == 0) ||
           (strcmp (argv[3], "dbt") == 0)) {
    return ProcessDb (argc, argv, 2);
  }
  Error (NULL, 0, 0, "KeyEnroll: Unknown Command - ", argv[3]);
  return STATUS_ERROR;
}

STATUS
KeyEnroll (
  IN INTN   argc,
  IN CHAR8  **argv
  )
/*++

Routine Description:

  Main function for KeyEnroll.

Arguments:

  argc - Number of command line parameters.
  argv - Array of pointers to parameter strings.

Returns:
  STATUS_SUCCESS - Utility exits successfully.
  STATUS_ERROR   - Some error occurred during execution.

--*/
{
  UINT32                      VariableFvFileSize;
  UINT8                       *VariableFvFileBuffer;
  STATUS                      Status;
  UINT8                       *FdFileBuffer;
  UINT32                      FdFileSize;
  EFI_FIRMWARE_VOLUME_HEADER   *VarAddr;
  VOID                         *VariableStoreHeader;
  VARIABLE_TYPE               VariableType;

  //
  // Step 1: Read InputFvRecovery.fv data
  //
  Status = ReadInputFile (argv[1], &FdFileBuffer, &FdFileSize, NULL);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "Unable to open file", "%s", argv[1]);
    return Status;
  }

  //
  // Get Variable information
  //
  VariableFvFileSize = GetVariableInfoFromFd (FdFileBuffer, FdFileSize, &VariableFvFileBuffer);
  if ((VariableFvFileSize == 0) || (VariableFvFileBuffer == NULL)) {
    Error (NULL, 0, 0, "Variable FV not found in Fd file!", NULL);
    free ((VOID *)FdFileBuffer);
    return STATUS_ERROR;
  }
  gEfiFdInfo.EfiVariableAddr = (UINTN)VariableFvFileBuffer;

  VarAddr             = (EFI_FIRMWARE_VOLUME_HEADER *) gEfiFdInfo.EfiVariableAddr;
  VariableStoreHeader = (VOID *)((UINT8 *)VarAddr + VarAddr->HeaderLength);
  VariableType = CheckVarStore (VariableStoreHeader);
  switch (VariableType) {
  case VariableTypeTimeBasedAuth:
    printf ("VaraibleFv: Time-Based AuthVariable\n");
    break;
  case VariableTypeCountBasedAuth:
    printf ("VaraibleFv: Monotonic-Based AuthVariable - unsupported\n");
    return STATUS_ERROR;
    break;
  case VariableTypeNormal:
    printf ("VaraibleFv: Normal Variable - unsupported\n");
    return STATUS_ERROR;
    break;
  default:
    printf ("VaraibleFv: Unknown - unsupported\n");
    return STATUS_ERROR;
  }

  InitializeListHead (&mVarListEntry);

  Status = EfiVarAndListExchange (TRUE, &mVarListEntry);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "EfiVarAndListExchange (VarToList) Error!", NULL);
    return Status;
  }

  //
  // Construct Key
  //
  Status = ProcessKey (argc, argv);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "ProcessKey fail!", NULL);
    free ((VOID *)FdFileBuffer);
    return STATUS_ERROR;
  }

  if ((strcmp (argv[2], "INFO") == 0) ||
      (strcmp (argv[2], "info") == 0)) {
    return STATUS_SUCCESS;
  }

  Status = EfiVarAndListExchange (FALSE, &mVarListEntry);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "EfiVarAndListExchange (ListToVar) Error!", NULL);
    return Status;
  }
  DestroyAllStorage (&mVarListEntry);

  //
  // Step 5: Write OutputFvRecovery.fv data
  //
  Status = WriteOutputFile (argv[2], FdFileBuffer, FdFileSize);
  free ((VOID *)FdFileBuffer);
  if (Status != STATUS_SUCCESS) {
    Error (NULL, 0, 0, "Unable to write file", "%s", argv[2]);
    return Status;
  }

  printf ("Write Variable Successfully!\n");

  return Status;
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
    return KeyEnroll (argc, argv);
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

  Str  -  The string

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
  // skip preceeding white space
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
      // Let aplication exit immediately
      //
      Error (NULL, 0, 0, "Hex value is expected!", NULL);
      exit (0);
      break;
    }

    c = *(str++);
  }

  return u;
}

INTN
KeyEnrollStrCmp (
  IN      CONST CHAR16              *FirstString,
  IN      CONST CHAR16              *SecondString
  )
{
  while ((*FirstString != L'\0') && (*FirstString == *SecondString)) {
    FirstString++;
    SecondString++;
  }
  return *FirstString - *SecondString;
}

UINTN
KeyEnrollStrLen (
  IN      CONST CHAR16              *String
  )
{
  UINTN           Length;

  if (String == NULL) {
    return 0;
  }
  for (Length = 0; *String != L'\0'; String++, Length++) {
    ;
  }
  return Length;
}

UINTN
KeyEnrollStrSize (
  IN      CONST CHAR16              *String
  )
{
  return (KeyEnrollStrLen (String) + 1) * sizeof(CHAR16);
}

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

LIST_ENTRY *
EFIAPI
GetFirstNode (
  IN      CONST LIST_ENTRY          *List
  )
{
  return List->ForwardLink;
}

BOOLEAN
EFIAPI
IsNull (
  IN      CONST LIST_ENTRY          *List,
  IN      CONST LIST_ENTRY          *Node
  )
{
  return (BOOLEAN)(Node == List);
}

LIST_ENTRY *
EFIAPI
GetNextNode (
  IN      CONST LIST_ENTRY          *List,
  IN      CONST LIST_ENTRY          *Node
  )
{
  return Node->ForwardLink;
}

LIST_ENTRY *
EFIAPI
InitializeListHead (
  IN OUT  LIST_ENTRY                *ListHead
  )
{
  ListHead->ForwardLink = ListHead;
  ListHead->BackLink = ListHead;
  return ListHead;
}

LIST_ENTRY *
EFIAPI
InsertTailList (
  IN OUT  LIST_ENTRY                *ListHead,
  IN OUT  LIST_ENTRY                *Entry
  )
{
  Entry->ForwardLink = ListHead;
  Entry->BackLink = ListHead->BackLink;
  Entry->BackLink->ForwardLink = Entry;
  ListHead->BackLink = Entry;
  return ListHead;
}

LIST_ENTRY *
EFIAPI
RemoveEntryList (
  IN      CONST LIST_ENTRY          *Entry
  )
{
  Entry->ForwardLink->BackLink = Entry->BackLink;
  Entry->BackLink->ForwardLink = Entry->ForwardLink;
  return Entry->ForwardLink;
}

BOOLEAN
EFIAPI
IsListEmpty (
  IN      CONST LIST_ENTRY          *ListHead
  )
{
  return (BOOLEAN)(ListHead->ForwardLink == ListHead);
}

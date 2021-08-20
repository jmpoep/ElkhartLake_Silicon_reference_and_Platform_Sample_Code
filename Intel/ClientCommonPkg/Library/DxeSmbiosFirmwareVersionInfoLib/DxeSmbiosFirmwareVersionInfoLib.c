/** @file
  Library functions for SMBIOS Firmware Version Information.

 Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.<BR>

 This program and the accompanying materials are licensed and made available under
 the terms and conditions of the BSD License which accompanies this distribution.
 The full text of the license may be found at
 http://opensource.org/licenses/bsd-license.php

 THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
 WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#include <IndustryStandard/SmBios.h>
#include <FirmwareVersionInfoHob.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/Smbios.h>

#define TYPE14_FVI_STRING          "Firmware Version Info"

/**
  Installs the SMBIOS Firmware Version Info (FVI) OEM type SMBIOS table based on the FIRMWARE_VERSION_INFO_HOB

  @retval EFI_UNSUPPORTED      - Could not locate SMBIOS protocol
  @retval EFI_OUT_OF_RESOURCES - Failed to allocate memory for SMBIOS FVI OEM type.
  @retval EFI_SUCCESS          - Successfully installed SMBIOS FVI OEM type
**/
EFI_STATUS
EFIAPI
InstallSmbiosFviOemType (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS         Hob;
  SMBIOS_STRUCTURE             SmbiosHdr;
  EFI_SMBIOS_HANDLE            SmbiosHandle;
  EFI_SMBIOS_PROTOCOL          *Smbios;
  EFI_STATUS                   Status;
  UINT8                        Count;
  UINT16                       HobLength;
  UINT32                       StrSize;
  UINT32                       RequiredSize;
  UINT8                        *RecordPtr;
  UINTN                        *FviDataPtr;
  UINTN                        *DestPtr;
  UINTN                        *SourcePtr;
  CHAR8                        *CharInStrPtr;
  UINT16                       FviHobCount;

  DestPtr = NULL;
  SourcePtr = NULL;
  FviDataPtr = NULL;
  CharInStrPtr = NULL;
  RequiredSize = 0;
  FviHobCount = 0;
  Status = EFI_SUCCESS;

  DEBUG ((DEBUG_INFO, "InstallSmbiosFviOemType(): Install SMBIOS FVI OEM Type.\n"));

  Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **)&Smbios);
  if (Smbios == NULL) {
    return EFI_UNSUPPORTED;
  }

  ///
  /// Get FVI HOB
  ///
  for (Hob.Raw = GetHobList (); !END_OF_HOB_LIST(Hob); Hob.Raw = GET_NEXT_HOB (Hob)) {
    if ((GET_HOB_TYPE (Hob) == EFI_HOB_TYPE_GUID_EXTENSION) && (CompareGuid (&Hob.Guid->Name, &gSmbiosFirmwareVersionInfoHobGuid))) {
      HobLength = Hob.Guid->Header.HobLength;
      Count = ((FIRMWARE_VERSION_INFO_HOB *)Hob.Guid)->Count;
      ///
      /// Initialize the SMBIOS header
      ///
      SmbiosHdr.Length = sizeof(SMBIOS_STRUCTURE) + sizeof(UINT8) + (Count * sizeof (FIRMWARE_VERSION_INFO));
      SmbiosHdr.Type = PcdGet8(PcdSmbiosOemTypeFirmwareVersionInfo);
      SmbiosHdr.Handle = 0;
      if (SmbiosHdr.Type < 0x80) {
        continue;
      }

      FviDataPtr = (UINTN *)&(((FIRMWARE_VERSION_INFO_HOB *)Hob.Guid)->Count);
      CharInStrPtr = (CHAR8 *)((UINTN)FviDataPtr + sizeof(UINT8) + (Count * sizeof (FIRMWARE_VERSION_INFO)));
      ///
      /// Look for the two consecutive zeros
      ///
      StrSize = 0;
      while (*CharInStrPtr != 0 || *(CharInStrPtr + 1) != 0) {
        StrSize += 1;
        CharInStrPtr++;
      }
      ///
      /// Count ending two zeros.
      ///
      StrSize += 2;

      ///
      /// Make sure the length of FVIs with strings buffer is smaller than HOB length
      ///
      if ((sizeof(FIRMWARE_VERSION_INFO_HOB) + (Count * sizeof (FIRMWARE_VERSION_INFO)) + StrSize) > HobLength) {
        DEBUG ((DEBUG_ERROR, "The length of FVIs with strings buffer is bigger than HOB length.\n"));
        continue;
      }

      RequiredSize = sizeof(SMBIOS_STRUCTURE) + sizeof(UINT8) + (Count * sizeof (FIRMWARE_VERSION_INFO)) + StrSize;
      RecordPtr = (UINT8 *) AllocateZeroPool(RequiredSize);
      if (RecordPtr == NULL) {
        DEBUG ((DEBUG_ERROR, "Failed to allocate memory for SMBIOS FVI OEM type.\n"));
        return EFI_OUT_OF_RESOURCES;
      }
      DestPtr = (UINTN *)RecordPtr;
      SourcePtr = (UINTN *)&SmbiosHdr;
      CopyMem (DestPtr, SourcePtr, sizeof(SMBIOS_STRUCTURE));
      DestPtr = (UINTN *)((UINTN)RecordPtr + sizeof(SMBIOS_STRUCTURE));
      SourcePtr = (UINTN *)((UINTN)FviDataPtr);
      CopyMem (DestPtr, SourcePtr, sizeof(UINT8) + (Count * sizeof (FIRMWARE_VERSION_INFO)) + StrSize);

      ///
      /// Add FVI OEM type to SMBIOS table
      ///
      SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;
      Status = Smbios->Add (Smbios, NULL, &SmbiosHandle, (EFI_SMBIOS_TABLE_HEADER *) RecordPtr);
      if (!EFI_ERROR(Status)) {
        FviHobCount++;
      }
      FreePool (RecordPtr);
    }
  }

  DEBUG ((DEBUG_INFO, "InstallSmbiosFviOemType(): Found %d FVI HOBs and added to SMBIOS.\n", FviHobCount));

  return EFI_SUCCESS;
}

/**
  Installs SMBIOS Type 14 for grouping Firmware Version Info (FVI) OEM tables

  @retval others               - Failed to create an ReadyToBootEvent for install SMBIOS FVI Type 14
  @retval EFI_SUCCESS          - Successfully create an ReadyToBootEvent for install SMBIOS FVI Type 14
**/
EFI_STATUS
EFIAPI
InstallSmbiosFviType14 (
  VOID
  )
{
  EFI_SMBIOS_PROTOCOL               *SmbiosProtocol;
  EFI_STATUS                        Status;
  EFI_SMBIOS_HANDLE                 SmbiosHandle;
  EFI_SMBIOS_TABLE_HEADER           *Record;
  UINT32                            FviTypeCount;       // Number of FVI records located.
  UINT32                            FviT14Size;         // Size of the SMBIOS record to be installed.
  GROUP_STRUCT                      *FviTableOld;       // Pointers to discovered Fvi entries.
  GROUP_STRUCT                      *FviTableNew;
  SMBIOS_TABLE_TYPE14               *SmbiosTableType14;
  UINT8                             *GroupName;
  UINT8                             *EndPtr;
  static UINT8                      Type14FviString[sizeof (TYPE14_FVI_STRING)] = TYPE14_FVI_STRING;
  UINT8                             FviSmbiosType;

  SmbiosProtocol    = NULL;
  FviTableNew       = NULL;
  SmbiosTableType14 = NULL;

  DEBUG ((DEBUG_INFO, "AddSmbiosFviType14Callback(): Executing SMBIOS FVI Type 14 callback.\n"));

  ///
  /// Parse the SMBIOS records for
  ///
  Status = gBS->LocateProtocol (
                  &gEfiSmbiosProtocolGuid,
                  NULL,
                  (VOID *) &SmbiosProtocol
                  );
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "AddSmbiosFviType14Callback(): Locate SMBIOS protocol failure!!\n"));
    return Status;
  }

  FviTypeCount  = 0;
  SmbiosHandle  = SMBIOS_HANDLE_PI_RESERVED;
  ///
  /// Get FVI SMBIOS OEM Type
  ///
  FviSmbiosType = PcdGet8(PcdSmbiosOemTypeFirmwareVersionInfo);
  do {
    Status = SmbiosProtocol->GetNext (
                               SmbiosProtocol,
                               &SmbiosHandle,
                               NULL,
                               &Record,
                               NULL
                               );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "AddSmbiosFviType14Callback(): The SMBIOS record is the last available record.\n"));
      break;
    }
    ///
    /// Only One EFI_SMBIOS_TYPE_GROUP_ASSOCIATIONS with the label Type14FviString.
    /// is allowed in the system.
    ///
    if (Record->Type == EFI_SMBIOS_TYPE_GROUP_ASSOCIATIONS) {
      GroupName = ((UINT8 *)Record) + Record->Length;
      if(AsciiStrCmp ((CHAR8 *) GroupName, (CHAR8 *) Type14FviString) == 0) {
        DEBUG ((DEBUG_INFO, "AddSmbiosFviType14Callback(): The Type 14 table is already in SMBIOS records.\n"));
        FviTypeCount = 0;       //  mark the set as empty
        break;
      }
    }
    ///
    /// Locate the FviSmbiosType records.
    ///
    if (Record->Type == FviSmbiosType) {
      FviTypeCount++;
      FviTableOld = FviTableNew;
      FviTableNew = AllocateZeroPool (sizeof(GROUP_STRUCT)*FviTypeCount);
      if (FviTableNew == NULL) {
        DEBUG ((DEBUG_ERROR, "AddSmbiosFviType14Callback(): Allocate memory for FviTable failed!!\n"));
        goto AddSmbiosFviType14CallbackExit;
      }

      if (FviTypeCount > 1) {
        CopyMem (FviTableNew, FviTableOld, (sizeof (GROUP_STRUCT) * FviTypeCount));
      }

      if (FviTableOld != NULL) {
        FreePool (FviTableOld);
      }

      FviTableNew[FviTypeCount - 1].ItemType    = Record->Type;
      FviTableNew[FviTypeCount - 1].ItemHandle  = Record->Handle;
    }
  } while (Status == EFI_SUCCESS);      // End of retrieving Smbios FviSmbiosType records.

  DEBUG ((DEBUG_INFO, "AddSmbiosFviType14Callback(): Located %d FviSmbiosType (%d) records\n", FviTypeCount, FviSmbiosType));

  if (FviTypeCount != 0) {

    ///
    /// Add the Record to the SMBIOS table.
    ///
    FviT14Size = sizeof (SMBIOS_TABLE_TYPE14) + (UINT32) (AsciiStrLen (TYPE14_FVI_STRING)) + (sizeof (GROUP_STRUCT) * (FviTypeCount - 1)) + 2;

    SmbiosTableType14 = AllocateZeroPool (FviT14Size);
    if (SmbiosTableType14 == NULL) {
      DEBUG ((DEBUG_ERROR, "AddSmbiosFviType14Callback(): Allocate memory for FviTable failed!!\n"));
      goto AddSmbiosFviType14CallbackExit;
    }

    SmbiosTableType14->Hdr.Type = EFI_SMBIOS_TYPE_GROUP_ASSOCIATIONS;
    SmbiosTableType14->Hdr.Length = (UINT8) (sizeof (SMBIOS_TABLE_TYPE14) + (sizeof (GROUP_STRUCT) * (FviTypeCount - 1)));
    SmbiosTableType14->Hdr.Handle = SMBIOS_HANDLE_PI_RESERVED;  // Assign an unused handle.
    SmbiosTableType14->GroupName  = 1;
    CopyMem (SmbiosTableType14->Group, FviTableNew, sizeof (GROUP_STRUCT) * FviTypeCount);
    CopyMem ((&SmbiosTableType14->Group[FviTypeCount].ItemType), Type14FviString, sizeof (Type14FviString));
    EndPtr = (UINT8 *) (SmbiosTableType14);       // Extra zero marks the end of the record.
    EndPtr[FviT14Size - 1] = 0;

    Status = SmbiosProtocol->Add (
                               SmbiosProtocol,
                               NULL,
                               &SmbiosTableType14->Hdr.Handle,
                               (EFI_SMBIOS_TABLE_HEADER *) SmbiosTableType14
                               );
    if (!EFI_ERROR(Status)) {
      DEBUG ((DEBUG_INFO, "AddSmbiosFviType14Callback(): The Type 14 table is installed into SMBIOS records.\n"));
    }
  }

AddSmbiosFviType14CallbackExit:
  if (SmbiosTableType14 != NULL) {
    FreePool (SmbiosTableType14);
  }
  if (FviTableNew != NULL) {
    FreePool (FviTableNew);
  }

  return EFI_SUCCESS;
}

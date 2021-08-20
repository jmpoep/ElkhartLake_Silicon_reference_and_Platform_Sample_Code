/** @file
  CPU Firmware Version Info implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2017 Intel Corporation.

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

#include <Uefi.h>
#include <SiFvi.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PerformanceLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/MemoryAllocationLib.h>
#include <MeBiosPayloadHob.h>
#include <PchHsio.h>
#include <MemInfoHob.h>
#include <SaConfigHob.h>
#include <IndustryStandard/FirmwareVersionInfo.h>
#include <TxtInfoHob.h>
#include <IndustryStandard/Pci30.h>

///
/// Firmware Version Strings Structure
///
#pragma pack(push, 1)

typedef struct {
  CHAR8                          *ComponentName;
  CHAR8                          *VersionString;
} FIRMWARE_VERSION_STRINGS;

#pragma pack(pop)

GLOBAL_REMOVE_IF_UNREFERENCED INTEL_FIRMWARE_VERSION_INFO    mCpuFviData[] = {
                                                               DEFAULT_FVI_DATA (),
                                                               FVI_VERSION (DEFAULT_FVI_VERSION),
                                                               FVI_VERSION (DEFAULT_FVI_VERSION)
                                                             };
GLOBAL_REMOVE_IF_UNREFERENCED FIRMWARE_VERSION_STRINGS       mCpuFviStrings[] = {
                                                               DEFAULT_FVI_STRINGS (CPU),
                                                               { UCODE_FVI_STRING, NULL },
                                                               { TXT_FVI_STRING,   NULL }
                                                             };

GLOBAL_REMOVE_IF_UNREFERENCED INTEL_FIRMWARE_VERSION_INFO    mMeFviData[] = {
                                                               DEFAULT_FVI_DATA (),
                                                               DEFAULT_FVI_DATA (),
                                                               FVI_VERSION (DEFAULT_FVI_VERSION)
                                                             };
GLOBAL_REMOVE_IF_UNREFERENCED FIRMWARE_VERSION_STRINGS       mMeFviStrings[] = {
                                                               DEFAULT_FVI_STRINGS (ME),
                                                               DEFAULT_FVI_STRINGS (MEBX),
                                                               { ME_FW_FVI_STRING, ME_FW_CONSUMER_SKU_STRING }
                                                             };

GLOBAL_REMOVE_IF_UNREFERENCED INTEL_FIRMWARE_VERSION_INFO    mPchFviData[] = {
    DEFAULT_FVI_DATA(),
    FVI_VERSION(DEFAULT_FVI_VERSION),   // PCH CRID status
    FVI_VERSION(DEFAULT_FVI_VERSION),   // PCH CRID origin
    FVI_VERSION(DEFAULT_FVI_VERSION),   // PCH CRID new
    FVI_VERSION(DEFAULT_FVI_VERSION),   // RAID RC version
    FVI_VERSION(FVI_PCH_ICL_LP_AX_HSIO_VERSION)
};
GLOBAL_REMOVE_IF_UNREFERENCED FIRMWARE_VERSION_STRINGS       mPchFviStrings[] = {
    DEFAULT_FVI_STRINGS(PCH),
    { PCH_CRID_STATUS_STRING, PCH_CRID_DISABLED },
    { PCH_CRID_ORIGINAL_VALUE, NULL },
    { PCH_CRID_NEW_VALUE, NULL },
    { RAID_FVI_STRING, NULL },
    { ICL_PCH_LP_AX_HSIO_STRING, NULL }
};

GLOBAL_REMOVE_IF_UNREFERENCED INTEL_FIRMWARE_VERSION_INFO    mSaFviData[] = {
                                                               DEFAULT_FVI_DATA (),
                                                               FVI_VERSION (DEFAULT_FVI_VERSION),   // Memory RC version
                                                               FVI_VERSION (DEFAULT_FVI_VERSION),   // PCIE RC version
                                                               FVI_VERSION (DEFAULT_FVI_VERSION),   // SA CRID Status
                                                               FVI_VERSION (DEFAULT_FVI_VERSION),   // SA CRID origin
                                                               FVI_VERSION (DEFAULT_FVI_VERSION),   // SA CRID new
                                                               FVI_VERSION (DEFAULT_FVI_VERSION)    // VBIOS RC version
                                                             };
GLOBAL_REMOVE_IF_UNREFERENCED FIRMWARE_VERSION_STRINGS       mSaFviStrings[] = {
                                                               DEFAULT_FVI_STRINGS (SA),
                                                               { MEM_FVI_STRING,         NULL },
                                                               { PCIE_FVI_STRING,        NULL },
                                                               { SA_CRID_STATUS,         SA_CRID_DISABLED },
                                                               { SA_CRID_ORIGINAL_VALUE, NULL },
                                                               { SA_CRID_NEW_VALUE,      NULL },
                                                               { VBIOS_FVI_STRING,       NULL }
                                                             };


/**
  Build data Hob of the SMBIOS Firmware Version Info (FVI) OEM type based on the SMBIOS_TABLE_TYPE_OEM_INTEL_FVI

  @retval EFI_OUT_OF_RESOURCES - Failed to allocate memory for SMBIOS FVI OEM type.
  @retval EFI_SUCCESS          - Successfully built Hob
**/
EFI_STATUS
BuildFviHob (
  IN INTEL_FIRMWARE_VERSION_INFO    *Data,
  IN FIRMWARE_VERSION_STRINGS       *Strings,
  IN UINTN                          DataSize
  )
{
  EFI_STATUS                        Status;
  UINT8                             Index;
  UINTN                             SizeOfStrings;
  CHAR8                             *StringPtr;
  CHAR8                             **StringArray;
  UINT8                             StringCount;
  UINT8                             StringNumber;
  SMBIOS_TABLE_TYPE_OEM_INTEL_FVI   *Record;
  UINT8                             Count;
  UINT8                             *DataPtr;
  VOID                              *Hob;
  UINTN                             HobLength;

  SizeOfStrings = 0;
  HobLength = 0;
  StringCount = 0;                   ///< Number of non-null strings total.
  StringNumber = 0;                  ///< String number of the current string.
  Status = EFI_SUCCESS;

  DataPtr = (UINT8 *) Data;          ///< Points to the fixed data location for the current string.
  StringArray = (CHAR8 **) Strings;
  Count = (UINT8)(DataSize / sizeof (INTEL_FIRMWARE_VERSION_INFO));

  for (Index = 0; Index < (Count * FVI_NUMBER_OF_STRINGS); Index++) {
    if (StringArray[Index] != NULL) {
      SizeOfStrings += AsciiStrSize (StringArray[Index]);
      StringCount++;
      StringNumber = StringCount;
    } else {
      StringNumber = NO_STRING_AVAILABLE;
    }
    *DataPtr = StringNumber;
    DataPtr++;

    ///
    /// If this was the last string of this data block, adjust the DataPtr
    /// to the start of the string section of the next data block.
    ///
    if (((Index + 1) % FVI_NUMBER_OF_STRINGS) == 0) {
      DataPtr += (sizeof (INTEL_FIRMWARE_VERSION_INFO) - FVI_NUMBER_OF_STRINGS);
    }
  }

  ///
  /// Add the size of the terminating double null
  /// If there were any strings added, just add the second null
  ///
  if (SizeOfStrings == 0) {
    SizeOfStrings += 2;
  } else {
    SizeOfStrings += 1;
  }

  ///
  /// Initialize the full record
  /// The complete record layout is (SMBIOS_STRUCTURE + UINT8 + n * INTEL_FIRMWARE_VERSION_INFO + strings)
  ///
  HobLength = sizeof (SMBIOS_STRUCTURE) + sizeof (UINT8) + (Count * sizeof (INTEL_FIRMWARE_VERSION_INFO)) + SizeOfStrings;
  Record = (SMBIOS_TABLE_TYPE_OEM_INTEL_FVI *) AllocateZeroPool (HobLength);
  if (Record == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  Record->Header.Type = PcdGet8 (PcdFviSmbiosType);
  Record->Header.Length = sizeof (SMBIOS_STRUCTURE) + sizeof (UINT8) + (Count * sizeof (INTEL_FIRMWARE_VERSION_INFO));
  Record->Header.Handle = 0;
  Record->Count = Count;
  CopyMem (&(Record->Fvi[0]), Data, (Count * sizeof (INTEL_FIRMWARE_VERSION_INFO)));

  ///
  /// Copy the strings to the end of the record
  ///
  StringPtr = ((CHAR8 *) &(Record->Fvi[0])) + (Count * sizeof (INTEL_FIRMWARE_VERSION_INFO));
  for (Index = 0; Index < (Count * FVI_NUMBER_OF_STRINGS); Index++) {
    if (StringArray[Index] != NULL) {
      AsciiStrCpyS (StringPtr, SizeOfStrings, StringArray[Index]);
      StringPtr += AsciiStrSize (StringArray[Index]);
      SizeOfStrings -= AsciiStrSize (StringArray[Index]);
    }
  }

  Hob = BuildGuidDataHob (
          &gIntelSmbiosDataHobGuid,
          (VOID *) Record,
          HobLength
          );
  ASSERT (Hob != NULL);

  FreePool (Record);
  return Status;
}

/**
  This function builds the CPU FVI Hob

  @retval EFI_SUCCESS          - Successfully built the Hob
**/
EFI_STATUS
BuildCpuFviHob (
  VOID
  )
{
  UINT32        uCodeRevision;
  TXT_INFO_HOB  *TxtInfoHob;

  mCpuFviData[CPU_RC_VER].Version.MajorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMajor);
  mCpuFviData[CPU_RC_VER].Version.MinorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMinor);
  mCpuFviData[CPU_RC_VER].Version.Revision     = (UINT8)  PcdGet8 (PcdSiliconInitVersionRevision);
  mCpuFviData[CPU_RC_VER].Version.BuildNumber  = (UINT16) PcdGet8 (PcdSiliconInitVersionBuild);

  uCodeRevision = GetCpuUcodeRevision ();
  mCpuFviData[UCODE_VER].Version.MajorVersion  = (UINT8) ((uCodeRevision & 0xFF000000) >> 24);
  mCpuFviData[UCODE_VER].Version.MinorVersion  = (UINT8) ((uCodeRevision & 0x00FF0000) >> 16);
  mCpuFviData[UCODE_VER].Version.Revision      = (UINT8) ((uCodeRevision & 0x0000FF00) >> 8);
  mCpuFviData[UCODE_VER].Version.BuildNumber   = (UINT16) (uCodeRevision & 0x000000FF);

  //
  // Get TxtInfoHob
  //
  TxtInfoHob = (TXT_INFO_HOB *)GetFirstGuidHob (&gTxtInfoHobGuid);
  if (TxtInfoHob && !(0 == TxtInfoHob->Data.AcmMajorVersion && 0 == TxtInfoHob->Data.AcmMinorVersion)) {
    mCpuFviData[TXT_VER].Version.MajorVersion  = (UINT8) (TxtInfoHob->Data.AcmMajorVersion);
    mCpuFviData[TXT_VER].Version.MinorVersion  = (UINT8) (TxtInfoHob->Data.AcmMinorVersion);
    mCpuFviData[TXT_VER].Version.Revision      = (UINT8) (TxtInfoHob->Data.AcmRevision);
    mCpuFviData[TXT_VER].Version.BuildNumber   = 0;
  }

  return BuildFviHob (mCpuFviData, mCpuFviStrings, sizeof (mCpuFviData));
}

/**
  This function builds the ME FVI Hob

  @retval EFI_SUCCESS          - Successfully built the Hob
**/
EFI_STATUS
BuildMeFviHob (
  VOID
  )
{
  CONST UINT8                     StrCorporateSkuFw[sizeof (ME_FW_CORPORATE_SKU_STRING)] = ME_FW_CORPORATE_SKU_STRING;
  ME_BIOS_PAYLOAD_HOB             *MbpHob;

  MbpHob = NULL;
  //
  // Get the MBP Data.
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob != NULL) {
    mMeFviData[EnumMeFw].Version.MajorVersion = (UINT8)  MbpHob->MeBiosPayload.FwVersionName.MajorVersion;
    mMeFviData[EnumMeFw].Version.MinorVersion = (UINT8)  MbpHob->MeBiosPayload.FwVersionName.MinorVersion;
    mMeFviData[EnumMeFw].Version.Revision     = (UINT8)  MbpHob->MeBiosPayload.FwVersionName.HotfixVersion;
    mMeFviData[EnumMeFw].Version.BuildNumber  = (UINT16) MbpHob->MeBiosPayload.FwVersionName.BuildVersion;
    if (MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType == IntelMeCorporateFw) {
      mMeFviStrings[EnumMeFw].VersionString = (CHAR8 *) &StrCorporateSkuFw;
    }
  } else {
    DEBUG ((DEBUG_ERROR, "BuildMeFviHob: No MBP Data Protocol available\n"));
  }

  //
  // Default value of Silicon Init version
  //
  mMeFviData[EnumMeRc].Version.MajorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMajor);
  mMeFviData[EnumMeRc].Version.MinorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMinor);
  mMeFviData[EnumMeRc].Version.Revision     = (UINT8)  PcdGet8 (PcdSiliconInitVersionRevision);
  mMeFviData[EnumMeRc].Version.BuildNumber  = (UINT16) PcdGet8 (PcdSiliconInitVersionBuild);

  return BuildFviHob (mMeFviData, mMeFviStrings, sizeof (mMeFviData));
}

/**
  This function builds the PCH FVI Hob

  @retval EFI_SUCCESS          - Successfully built the Hob
**/
EFI_STATUS
BuildPchFviHob (
  VOID
  )
{
  //
  // Default value of Silicon Init version
  //
  mPchFviData[RC_VER].Version.MajorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMajor);
  mPchFviData[RC_VER].Version.MinorVersion = (UINT8)  PcdGet8 (PcdSiliconInitVersionMinor);
  mPchFviData[RC_VER].Version.Revision     = (UINT8)  PcdGet8 (PcdSiliconInitVersionRevision);
  mPchFviData[RC_VER].Version.BuildNumber  = (UINT16) PcdGet8 (PcdSiliconInitVersionBuild);

  return BuildFviHob (mPchFviData, mPchFviStrings, sizeof (mPchFviData));
}

/**
  This function builds the SA FVI Hob

  @retval EFI_SUCCESS          - Successfully built the Hob
**/
EFI_STATUS
BuildSaFviHob (
  VOID
  )
{
  CONST UINT8                     StrEnabled[sizeof (SA_CRID_ENABLED)] = SA_CRID_ENABLED;
  CONST UINT8                     StrDisabled[sizeof (SA_CRID_DISABLED)] = SA_CRID_DISABLED;
  STATIC CONST SiMrcVersion       MemRcVersionConst = {0, 0, 0, 0};
  CONST SiMrcVersion              *MemRcVersion;
  MEMORY_INFO_DATA_HOB            *MemInfo;
  UINT64                          McBaseAddress;
  UINT8                           Data8;
  SA_CONFIG_HOB                   *SaConfigHob;
  EFI_HOB_GUID_TYPE               *GuidHob;

  McBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  ///
  /// Save CRID_ORIGINAL value before SaSecurityInit() executes CRID function.
  ///
  mSaFviData[CRID_ORIGINAL].Version.MajorVersion = 0;
  mSaFviData[CRID_ORIGINAL].Version.MinorVersion = 0;
  mSaFviData[CRID_ORIGINAL].Version.Revision     = 0;
  mSaFviData[CRID_ORIGINAL].Version.BuildNumber  = (UINT16) PciSegmentRead8 (McBaseAddress + PCI_REVISION_ID_OFFSET);
  ///
  /// Get SaDataHob HOB
  ///
  SaConfigHob = NULL;
  SaConfigHob = (SA_CONFIG_HOB *) GetFirstGuidHob (&gSaConfigHobGuid);
  ///
  /// CRID configuration
  ///
  if (SaConfigHob->CridEnable == TRUE) {
    mSaFviStrings[CRID_STATUS].VersionString = (CHAR8 *) &StrEnabled;
    Data8 = CRID_DATA;
  } else {
    mSaFviStrings[CRID_STATUS].VersionString = (CHAR8 *) &StrDisabled;
    Data8 = CRID_LOCK;
  }
  PciSegmentWrite8 ((UINT64) (McBaseAddress + PCI_REVISION_ID_OFFSET), Data8);

  //
  // Search for the Memory Configuration GUID HOB. If it is not present, then
  // there's nothing we can do. It may not exist on the update path.
  //
  GuidHob = NULL;
  MemInfo = NULL;
  GuidHob = GetFirstGuidHob (&gSiMemoryInfoDataGuid);
  if (GuidHob != NULL) {
    MemInfo = (MEMORY_INFO_DATA_HOB *) GET_GUID_HOB_DATA (GuidHob);
  }
  if (MemInfo != NULL) {
    MemRcVersion = &MemInfo->Version;
  } else {
    MemRcVersion = &MemRcVersionConst;
  }

  mSaFviData[SA_RC_VER].Version.MajorVersion  = (UINT8)  PcdGet8 (PcdSiliconInitVersionMajor);
  mSaFviData[SA_RC_VER].Version.MinorVersion  = (UINT8)  PcdGet8 (PcdSiliconInitVersionMinor);
  mSaFviData[SA_RC_VER].Version.Revision      = (UINT8)  PcdGet8 (PcdSiliconInitVersionRevision);
  mSaFviData[SA_RC_VER].Version.BuildNumber   = (UINT16) PcdGet8 (PcdSiliconInitVersionBuild);
  mSaFviData[PCIE_VER].Version.MajorVersion   = (UINT8)  PcdGet8 (PcdSiliconInitVersionMajor);
  mSaFviData[PCIE_VER].Version.MinorVersion   = (UINT8)  PcdGet8 (PcdSiliconInitVersionMinor);
  mSaFviData[PCIE_VER].Version.Revision       = (UINT8)  PcdGet8 (PcdSiliconInitVersionRevision);
  mSaFviData[PCIE_VER].Version.BuildNumber    = (UINT16) PcdGet8 (PcdSiliconInitVersionBuild);
  mSaFviData[MEM_RC_VER].Version.MajorVersion = (UINT8)  MemRcVersion->Major;
  mSaFviData[MEM_RC_VER].Version.MinorVersion = (UINT8)  MemRcVersion->Minor;
  mSaFviData[MEM_RC_VER].Version.Revision     = (UINT8)  MemRcVersion->Rev;
  mSaFviData[MEM_RC_VER].Version.BuildNumber  = (UINT16) MemRcVersion->Build;
  mSaFviData[CRID_NEW].Version.MajorVersion   = 0;
  mSaFviData[CRID_NEW].Version.MinorVersion   = 0;
  mSaFviData[CRID_NEW].Version.Revision       = 0;
  mSaFviData[CRID_NEW].Version.BuildNumber    = (UINT16) PciSegmentRead8 (McBaseAddress + PCI_REVISION_ID_OFFSET);

  return BuildFviHob (mSaFviData, mSaFviStrings, sizeof (mSaFviData));
}

/**
  Initialize all Smbios FVI OEM Type Data Hob

**/
VOID
EFIAPI
BuildFviInfoHob (
  VOID
  )
{
  EFI_STATUS      Status;

  DEBUG ((DEBUG_INFO, "BuildFviInfoHob(): Build Smbios FVI Data Hob\n"));

  Status = BuildCpuFviHob();
  ASSERT_EFI_ERROR (Status);

  Status = BuildMeFviHob();
  ASSERT_EFI_ERROR (Status);

  Status = BuildPchFviHob();
  ASSERT_EFI_ERROR (Status);

  Status = BuildSaFviHob();
  ASSERT_EFI_ERROR (Status);
}

/** @file
  CPU Firmware Version Info implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

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
#include <ConfigBlock.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/S3BootScriptLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/PciIo.h>
#include <Protocol/Smbios.h>
#include <Protocol/MebxProtocol.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/DriverSupportedEfiVersion.h>
#include <IndustryStandard/Pci30.h>
#include <IndustryStandard/SmBios.h>

#include <SiFvi.h>
#include <SaCommonDefinitions.h>
#include <SiConfigHob.h>
#include <PchInfoHob.h>
#include <PchConfigHob.h>
#include <Library/PmcPrivateLib.h>
#include <IndustryStandard/FirmwareVersionInfo.h>

///
/// Firmware Version Strings Structure
///
#pragma pack(push, 1)

typedef struct {
  CHAR8                          *ComponentName;
  CHAR8                          *VersionString;
} FIRMWARE_VERSION_STRINGS;

#pragma pack(pop)

/**
  Create and update PCH related FVI Records.

  @param[in] PchFviData           A pointer to the INTEL_FIRMWARE_VERSION_INFO
**/
VOID
CreateAndUpdatePchFviRecords (
  IN INTEL_FIRMWARE_VERSION_INFO  *PchFviData
  )
{
  EFI_STATUS                      Status;
  UINTN                           Index;
  UINTN                           NumHandles;
  EFI_HANDLE                      *HandleBuffer;
  EFI_STRING                      DriverName;
  BOOLEAN                         FoundLegacyRaid;
  PCI_DATA_STRUCTURE              *PcirBlockPtr;
  EFI_PCI_IO_PROTOCOL             *PciIo;
  PCI_EXPANSION_ROM_HEADER        *RomImage;
  EFI_COMPONENT_NAME2_PROTOCOL    *ComponentName2;
  CHAR16                          RstDriverName1[] = RST_DRIVER_NAME1;
  CHAR16                          RstDriverName2[] = RST_DRIVER_NAME2;
  EFI_DRIVER_SUPPORTED_EFI_VERSION_PROTOCOL *DriverEfiVersion;

  FoundLegacyRaid = FALSE;
  //
  // Get all PCI IO protocols
  //
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiPciIoProtocolGuid,
                  NULL,
                  &NumHandles,
                  &HandleBuffer
                  );
  if (!EFI_ERROR (Status)) {
    //
    // Find the RAID BIOS by checking each PCI IO handle for RST OPROM
    //
    for (Index = 0; Index < NumHandles; Index++) {
      Status = gBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gEfiPciIoProtocolGuid,
                      (VOID **) &PciIo
                      );
      if (EFI_ERROR (Status) || (PciIo->RomImage == NULL)) {
        //
        // If this PCI device doesn't have a ROM image, skip to the next device.
        //
        continue;
      }

      RomImage = PciIo->RomImage;

      //
      // Get pointer to PCIR structure
      //
      PcirBlockPtr = (PCI_DATA_STRUCTURE *) ((UINTN) RomImage + RomImage->PcirOffset);

      //
      // Check if we have an RAID BIOS OPROM.
      //
      if ((RomImage->Signature == 0xAA55) &&
          (PcirBlockPtr->ClassCode[0] == 0x00) &&
          (PcirBlockPtr->ClassCode[1] == 0x04) &&
          (PcirBlockPtr->ClassCode[2] == 0x01)
          ) {
        PchFviData[RAID_VER].Version.MajorVersion = (UINT8) ((PcirBlockPtr->CodeRevision & 0xFF00) >> 8);
        PchFviData[RAID_VER].Version.MinorVersion = (UINT8)  (PcirBlockPtr->CodeRevision & 0x00FF);
        PchFviData[RAID_VER].Version.Revision     = 0;
        PchFviData[RAID_VER].Version.BuildNumber  = 0;
        FoundLegacyRaid = TRUE;
      }
    }
  }
  //
  // Search EFI RST OPROM
  //
  if (FoundLegacyRaid == FALSE) {
    Status = gBS->LocateHandleBuffer (
                    ByProtocol,
                    &gEfiDriverSupportedEfiVersionProtocolGuid,
                    NULL,
                    &NumHandles,
                    &HandleBuffer
                    );
    if (!EFI_ERROR (Status)) {
      for (Index = 0; Index < NumHandles; Index++) {
        Status = gBS->HandleProtocol (
                        HandleBuffer[Index],
                        &gEfiComponentName2ProtocolGuid,
                        (VOID **) &ComponentName2
                        );
        if (EFI_ERROR (Status)) {
          continue;
        }

        Status = ComponentName2->GetDriverName (ComponentName2, "en-US", &DriverName);
        if (EFI_ERROR (Status)) {
          continue;
        }

        if ((StrnCmp (DriverName, RstDriverName1, StrLen(RstDriverName1)) == 0) ||
            (StrnCmp (DriverName, RstDriverName2, StrLen(RstDriverName2)) == 0)) {
          Status = gBS->HandleProtocol (
                          HandleBuffer[Index],
                          &gEfiDriverSupportedEfiVersionProtocolGuid,
                          (VOID **) &DriverEfiVersion
                          );
          PchFviData[RAID_VER].Version.MajorVersion = (UINT8) ((DriverEfiVersion->FirmwareVersion & 0x00FF0000) >> 16);
          PchFviData[RAID_VER].Version.MinorVersion = (UINT8)  (DriverEfiVersion->FirmwareVersion & 0x000000FF);
          PchFviData[RAID_VER].Version.Revision     = 0;
          PchFviData[RAID_VER].Version.BuildNumber  = 0;
        }
      }
    }
  }
}


/**
  Update ME Smbios FVI data

  @param[in] MeFviData            A pointer to the INTEL_FIRMWARE_VERSION_INFO
**/
VOID
UpdateMeFvi (
  IN INTEL_FIRMWARE_VERSION_INFO  *MeFviData
  )
{
  EFI_STATUS                      Status;
  MEBX_PROTOCOL                   *MebxProtocol;

  Status = gBS->LocateProtocol (&gMebxProtocolGuid, NULL, (VOID **) &MebxProtocol);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Locate gMebxProtocolGuid failure, Status = %r\n", Status));
    return;
  }
  MeFviData[EnumMebx].Version.MajorVersion = (UINT8)  MebxProtocol->MebxVersion.Major;
  MeFviData[EnumMebx].Version.MinorVersion = (UINT8)  MebxProtocol->MebxVersion.Minor;
  MeFviData[EnumMebx].Version.Revision     = (UINT8)  MebxProtocol->MebxVersion.Hotfix;
  MeFviData[EnumMebx].Version.BuildNumber  = (UINT16) MebxProtocol->MebxVersion.Build;
}

/**
  Update PCH Smbios FVI data

  @param[in] PchFviData           A pointer to the INTEL_FIRMWARE_VERSION_INFO
  @param[in, out] PchFviStrings   A pointer to the FVI Strings information
**/
VOID
UpdatePchFvi (
  IN INTEL_FIRMWARE_VERSION_INFO *PchFviData,
  IN OUT CHAR8                   **PchFviStrings
  )
{
  STATIC CONST UINT8              StrEnabled[sizeof (PCH_CRID_ENABLED)] = PCH_CRID_ENABLED;
  STATIC CONST UINT8              StrDisabled[sizeof (PCH_CRID_DISABLED)] = PCH_CRID_DISABLED;
  UINT8                           Index;
  EFI_PEI_HOB_POINTERS            HobPtr;
  PCH_CONFIG_HOB                  *PchConfigHob;
  PCH_INFO_HOB                    *PchInfoHob;

  //
  // Do Crid programming as late as possible so others can get the ture PCH stepping.
  //
  HobPtr.Guid = GetFirstGuidHob (&gPchConfigHobGuid);
  ASSERT (HobPtr.Guid != NULL);
  PchConfigHob = (PCH_CONFIG_HOB *) GET_GUID_HOB_DATA (HobPtr.Guid);

  HobPtr.Guid = GetFirstGuidHob (&gPchInfoHobGuid);
  ASSERT (HobPtr.Guid != NULL);
  PchInfoHob = (PCH_INFO_HOB *) GET_GUID_HOB_DATA (HobPtr.Guid);

  PchFviData[PCH_CRID_ORIGINAL].Version.BuildNumber = (UINT16) PchInfoHob->CridOrgRid;
  if (PchInfoHob->CridSupport && PchConfigHob->General.Crid) {
    PmcSetCrid0WithS3BootScript ();
    PchFviData[PCH_CRID_NEW].Version.BuildNumber = (UINT16) PchInfoHob->CridNewRid;
  } else {
    PchFviData[PCH_CRID_NEW].Version.BuildNumber = (UINT16) PchInfoHob->CridOrgRid;
  }
  PmcLockCridWithS3BootScript ();

  //
  // Search the position of VersionString for PCH_CRID_STATUS
  //
  for (Index = 1; Index < PchFviData[PCH_CRID_STATUS].VersionString; Index++) {
    *PchFviStrings += AsciiStrSize ((CHAR8 *) *PchFviStrings);
  }
  if (PchFviData[PCH_CRID_ORIGINAL].Version.BuildNumber != PchFviData[PCH_CRID_NEW].Version.BuildNumber) {
    DEBUG ((DEBUG_INFO, "PCH_CRID_NEW.BuildNumber = %x\n", PchFviData[PCH_CRID_NEW].Version.BuildNumber));
    DEBUG ((DEBUG_INFO, "PCH_CRID_ORIGINAL.BuildNumber = %x\n", PchFviData[PCH_CRID_ORIGINAL].Version.BuildNumber));
    AsciiStrnCpyS (*PchFviStrings, SMBIOS_STRING_MAX_LENGTH, (CHAR8 *) &StrEnabled, sizeof (StrEnabled));
  } else {
    AsciiStrnCpyS (*PchFviStrings, SMBIOS_STRING_MAX_LENGTH, (CHAR8 *) &StrDisabled, sizeof (StrDisabled));
  }

  CreateAndUpdatePchFviRecords (PchFviData);
}

/**
  Update SA Smbios FVI data

  @param[in] SaFviData            A pointer to the INTEL_FIRMWARE_VERSION_INFO
**/
VOID
UpdateSaFvi (
  IN INTEL_FIRMWARE_VERSION_INFO *SaFviData
  )
{
  UINT8                         Data8;
  UINT64                        McBaseAddress;
  UINT16                        VbiosBuildNum;

  VbiosBuildNum = 0xFFFF;

  McBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);
  Data8 = PciSegmentRead8 (McBaseAddress + PCI_REVISION_ID_OFFSET);
  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint8,
    (UINTN) (PcdGet64 (PcdSiPciExpressBaseAddress) + McBaseAddress + PCI_REVISION_ID_OFFSET),
    1,
    &Data8
    );

  SaFviData[VBIOS_VER].Version.BuildNumber = VbiosBuildNum;
}

/**
  Update All Smbios FVI OEM Type Data

  @param  SmbiosOemType        - SMBIOS OEM Type

  @retval EFI_UNSUPPORTED      - Could not locate SMBIOS protocol
  @retval EFI_SUCCESS          - Successfully update FVI data
**/
EFI_STATUS
EFIAPI
UpdateFviInfo (
  IN UINT8                    SmbiosOemType
  )
{
  EFI_STATUS                  Status;
  EFI_SMBIOS_PROTOCOL         *Smbios;
  EFI_SMBIOS_HANDLE           SmbiosHandle;
  EFI_SMBIOS_TABLE_HEADER     *Record;
  INTEL_FIRMWARE_VERSION_INFO *FviData;
  FIRMWARE_VERSION_STRINGS    *FviString;

  DEBUG ((DEBUG_INFO, "UpdateFviInfo(): Update SMBIOS FVI OEM Type.\n"));

  Status = gBS->LocateProtocol (&gEfiSmbiosProtocolGuid, NULL, (VOID **) &Smbios);
  if (Smbios == NULL || EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "Error locating gEfiSmbiosProtocolGuid failure. Status = %r\n", Status));
    return EFI_UNSUPPORTED;
  }

  SmbiosHandle = SMBIOS_HANDLE_PI_RESERVED;

  do {
    Status = Smbios->GetNext (Smbios, &SmbiosHandle, NULL, &Record, NULL);
    if (EFI_ERROR (Status)) {
      break;
    }
    if (Record->Type == SmbiosOemType) {

      FviData   = (INTEL_FIRMWARE_VERSION_INFO *)((UINT8 *)Record + sizeof (EFI_SMBIOS_TABLE_HEADER) + sizeof (UINT8));
      FviString = (FIRMWARE_VERSION_STRINGS *)((UINT8 *)Record + Record->Length);

      if (AsciiStrnCmp ((CHAR8 *) &FviString->ComponentName, ME_FVI_STRING, AsciiStrLen (ME_FVI_STRING)) == 0) {
        UpdateMeFvi(FviData);
      }
      if (AsciiStrnCmp ((CHAR8 *) &FviString->ComponentName, PCH_FVI_STRING, AsciiStrLen (PCH_FVI_STRING)) == 0) {
        UpdatePchFvi(FviData, (CHAR8 **) &FviString);
      }
      if (AsciiStrnCmp ((CHAR8 *) &FviString->ComponentName, SA_FVI_STRING, AsciiStrLen (SA_FVI_STRING)) == 0) {
        UpdateSaFvi(FviData);
      }

    }
  } while (Status == EFI_SUCCESS);

  return EFI_SUCCESS;
}


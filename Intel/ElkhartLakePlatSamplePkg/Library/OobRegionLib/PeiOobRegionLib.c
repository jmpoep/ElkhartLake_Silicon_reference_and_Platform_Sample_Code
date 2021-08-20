/*++
  This file contains 'Framework Code' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may not be modified, except as allowed by
  additional terms of your license agreement.
--*/
/** @file
  Boot service PEI OOB Region library implementation.

  Copyright (c) 2019 - 2020, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/

#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/OobRegionLib.h>
#include <Library/BootMediaLib.h>
#include <PseOob.h>

/**
  This function returns OobRegion by searching HOB or FV.
  It also debug print the OOB data found.

  @param[out] OobRegion     The OOB data got from HOB or FV. It is optional,
                            no OOB data will be returned if it is NULL as input.

  @retval EFI_SUCCESS               OOB data has been got successfully.
  @retval EFI_NOT_FOUND             OOB data is not found, and no parameter will be modified.

**/
EFI_STATUS
EFIAPI
GetOobRegion (
  OUT OOB_DATA        *OobRegion OPTIONAL
  )
{
  EFI_STATUS                 Status;
  OOB_DATA                   TempOobRegion;
  VOID                       *Address;
  UINTN                      Size;
  UINTN                      Instance;
  EFI_PEI_FV_HANDLE          VolumeHandle;
  EFI_PEI_FILE_HANDLE        FileHandle;
  UINT32                     Count;
  EFI_FV_FILE_INFO           FileInfo;
  VOID                       *RootCABuffer;
  UINT32                     RootCABufferSize;
  EFI_COMMON_SECTION_HEADER  *Section;

  Address = NULL;
  RootCABuffer = NULL;
  RootCABufferSize = 0;
  Size = 0;
  Count = 0;

  DEBUG ((EFI_D_ERROR, "PEI get OOB data from SubRegion\n"));
  if (OobRegion == NULL) {
    //
    // It is NULL as input, so no OOB Data will be returned.
    // Use temp buffer to hold the OOB Data.
    //
    OobRegion = &TempOobRegion;
  }

  Address = GetFirstGuidHob (&gOobConfigSectionGuid);
  if (Address != NULL) {
    Size = sizeof (OOB_DATA);
    CopyMem ((VOID *) OobRegion, GET_GUID_HOB_DATA (Address), Size);

    return EFI_SUCCESS;
  }
  if (BootMediaIsSpi()) {
    PeiServicesInstallFvInfoPpi (
      NULL,
      (VOID *) PcdGet32 (PcdFlashFvOobConfigBase),
      PcdGet32 (PcdFlashFvOobConfigSize),
      NULL,
      NULL
      );
  } else {
    DEBUG ((EFI_D_INFO, "Skip OOB UFS support until flash map is defined for UFS OOB region\n"));
    return EFI_NOT_FOUND;
  }

  VolumeHandle = NULL;
  Instance = 0;
  while (TRUE) {
    //
    // Traverse all firmware volume instances.
    //
    Status = PeiServicesFfsFindNextVolume (Instance, &VolumeHandle);
    if (EFI_ERROR (Status)) {
      break;
    }

    FileHandle = NULL;
    Status = PeiServicesFfsFindFileByName (&gOobConfigSectionGuid, VolumeHandle, &FileHandle);
    if (!EFI_ERROR (Status)) {
      //
      // Search RAW section.
      //
      Status = PeiServicesFfsFindSectionData (EFI_SECTION_RAW, FileHandle, &Address);
      if (!EFI_ERROR (Status)) {
        //
        // OOB data is present in this FV.
        //
        Size = sizeof (OOB_DATA);
        CopyMem ((VOID *) OobRegion, Address, Size);

        //
        // Build GUID HOB for the BIOS ID image.
        //
        BuildGuidDataHob (&gOobConfigSectionGuid, Address, Size);

        //
        // Read ROOTCA file
        //
        Status = PeiServicesFfsFindFileByName (&gOobRootCASectionGuid, VolumeHandle, &FileHandle);
        if (!EFI_ERROR (Status)) {
          DEBUG ((DEBUG_INFO, "OOB Config RootCA  File Found\n"));
          Status = PeiServicesFfsGetFileInfo(FileHandle, &FileInfo);
          if (!EFI_ERROR (Status)) {
            DEBUG ((DEBUG_INFO, "Read File Information Successfully and its Size: %d\n", FileInfo.BufferSize));

            Section = (EFI_COMMON_SECTION_HEADER *)FileInfo.Buffer;
            if (IS_SECTION2(Section)) {
              ASSERT(SECTION2_SIZE(Section) > 0x00FFFFFF);
              RootCABufferSize = SECTION2_SIZE(Section) - sizeof (EFI_COMMON_SECTION_HEADER2);
              RootCABuffer     = (UINT8 *)FileInfo.Buffer + sizeof (EFI_COMMON_SECTION_HEADER2);
            } else {
              RootCABufferSize = SECTION_SIZE(Section) - sizeof (EFI_COMMON_SECTION_HEADER);
              RootCABuffer     = (UINT8 *)FileInfo.Buffer + sizeof (EFI_COMMON_SECTION_HEADER);
            }

            DEBUG ((DEBUG_INFO, "RootCA buffer Size : 0x%d \n", RootCABufferSize));
            DEBUG ((DEBUG_INFO, "RootCA: \n"));
            for (Count = 0; Count < RootCABufferSize; Count++) {
              DEBUG ((DEBUG_INFO, "%c", ((UINT8*)RootCABuffer)[Count]));
            }
            DEBUG((DEBUG_INFO, "\n"));
            //
            // Build GUID HOB for the OOB ROOT CA.
            //
            BuildGuidDataHob (&gOobRootCASectionGuid, (VOID*)&RootCABufferSize, sizeof(UINT32));
            BuildGuidDataHob (&gOobRootCASectionGuid, (VOID*)RootCABuffer, RootCABufferSize);
            return EFI_SUCCESS;
          } else {
            DEBUG ((DEBUG_INFO, "Failed to find RootCA File Info Status: 0x%d\n", Status));
          }
        } else {
          DEBUG ((DEBUG_INFO, "Failed to find RootCA FFS Status: 0x%d\n", Status));
        }
      }
    }

    //
    // Search the next volume.
    //
    Instance++;
  }

  DEBUG ((EFI_D_ERROR, "PEI get OOB data failed: %r\n", EFI_NOT_FOUND));
  return EFI_NOT_FOUND;
}


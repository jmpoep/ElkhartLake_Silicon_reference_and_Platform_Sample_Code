/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

@par Specification Reference:
**/

#include "FvCallback.h"
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/NemMapLib.h>
#include <Library/NvStorageCopyLib.h>
#include <Library/PcdLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BpdtLib.h>
#include <Library/HobLib.h>
#include <Library/BootMediaLib.h>
#if FixedPcdGetBool(PcdBfxEnable) == 1
#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
#include <Library/FspCommonLib.h>
#endif
#endif

EFI_GUID *mObbGuids[] = {
  &gFvSecurityGuid,
  &gFvPostMemoryGuid,
  &gFvFwBinariesGuid,
  &gFvAdvancedGuid,
  &gFvUefiBootGuid,
  &gFvOsBootGuid,
  &gFvTsnMacAddressGuid,
  &gFvPseTsnIpConfigGuid,
  &gFvTsnConfigGuid
};

/**
  Installs FV Info PPIs from the provided SubPartition for the provided FV names

  @param  [in]  FvData      Pointer in memory of a BPDT SUB_PARTITION_DATA struct
  @param  [in]  FvList      List of FVs to find
  @param  [in]  FvCount     Number of FVs in the list

  @retval EFI_SUCCESS       FVs found and installed successfully
**/
EFI_STATUS
EFIAPI
ParseFvData (
  IN  SUB_PARTITION_DATA    *FvData,
  IN  EFI_GUID              **FvList,
  IN  UINTN                 FvCount
  )
{
  EFI_STATUS                      Status;
  SUB_PARTITION_DIRECTORY_HEADER  *DirectoryHeader;
  SUB_PARTITION_DIRECTORY_ENTRY   *DirectoryEntry;
  EFI_FIRMWARE_VOLUME_HEADER      *FvHeader;
  EFI_FIRMWARE_VOLUME_EXT_HEADER  *FvExtHeader;
  EFI_FFS_FILE_HEADER             *FileHeader;
  EFI_GUID                        *FvName;
  UINTN                           EndOfSubPartition;
  UINTN                           FvIndex;
  UINTN                           InstallCount;
#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
#if FixedPcdGetBool(PcdBfxEnable) == 1
  FSP_GLOBAL_DATA                 *FspData;
#endif
#endif

  DEBUG ((DEBUG_INFO, "Parsing FVs from SubPartition 0x%08X\n", FvData->Address));

  InstallCount       = 0;
  EndOfSubPartition  = (UINTN) FvData->Address + FvData->Size;
  DirectoryHeader    = (SUB_PARTITION_DIRECTORY_HEADER *) FvData->Address;

  if (DirectoryHeader->HeaderMarker == DIRECTORY_HEADER_MARKER) {
    DEBUG ((EFI_D_INFO, "Directory Header found\n"));
    DirectoryEntry = (SUB_PARTITION_DIRECTORY_ENTRY *) (DirectoryHeader + 1);
    FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *) ((UINTN) DirectoryHeader + DirectoryEntry->Offset);
  } else {
    DEBUG ((EFI_D_INFO, "Directory Header not found\n"));
    FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *) FvData->Address;
  }

  while ((UINTN) FvHeader + FvHeader->FvLength <= EndOfSubPartition) {
    if (FvHeader->Signature != EFI_FVH_SIGNATURE) {
      DEBUG ((EFI_D_ERROR, "Found FV with invalid signature or installed last FV\n"));
      break;
    }
    if (FvHeader->ExtHeaderOffset) {
      FvExtHeader = (EFI_FIRMWARE_VOLUME_EXT_HEADER *) ((UINTN) FvHeader + FvHeader->ExtHeaderOffset);
      FvName = &FvExtHeader->FvName;
    } else {
      FileHeader = (EFI_FFS_FILE_HEADER *) ((UINTN) FvHeader + FvHeader->HeaderLength);
      FvName = &FileHeader->Name;
    }
    DEBUG ((EFI_D_INFO, "Found "));
    PrintFvName (FvName);
    DEBUG ((EFI_D_INFO, ", GUID: %g\n", FvName));

    if (BootMediaIsUfs ()) {
      if (CompareGuid (FvName, &gFvTsnMacAddressGuid)) {
        PcdSet32S (PcdUfsFlashTsnMacAddressFvBase, (UINT32)FvHeader);
        PcdSet32S (PcdUfsFlashTsnMacAddressFvSize, (UINT32)FvHeader->FvLength);
      }
      if (CompareGuid (FvName, &gFvPseTsnIpConfigGuid)) {
        PcdSet32S (PcdUfsFlashPseTsnIpConfigFvBase, (UINT32)FvHeader);
        PcdSet32S (PcdUfsFlashPseTsnIpConfigFvSize, (UINT32)FvHeader->FvLength);
      }
      if (CompareGuid (FvName, &gFvTsnConfigGuid)) {
        PcdSet32S (PcdUfsFlashTsnConfigFvBase, (UINT32)FvHeader);
        PcdSet32S (PcdUfsFlashTsnConfigFvSize, (UINT32)FvHeader->FvLength);
      }
      if (CompareGuid (FvName, &gFvTccConfigGuid)) {
        PcdSet32S (PcdUfsFlashTccConfigFvBase, (UINT32)FvHeader);
        PcdSet32S (PcdUfsFlashTccConfigFvSize, (UINT32)FvHeader->FvLength);
      }
      if (CompareGuid (FvName, &gFvSiipFwGuid)) {
        PcdSet32S (PcdUfsFvSiipFwBase, (UINT32)FvHeader);
        PcdSet32S (PcdUfsFvSiipFwSize, (UINT32)FvHeader->FvLength);
      }
    }

#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
#if FixedPcdGetBool(PcdBfxEnable) == 1
    if (CompareGuid (FvName, &gFvMicrocodeGuid)) {
      FspData = GetFspGlobalDataPointer ();
      DEBUG ((DEBUG_INFO | DEBUG_INIT, "Updating FspData->PlatformData.MicrocodeRegionBase\n"));
      FspData->PlatformData.MicrocodeRegionBase = (UINT32) (FvHeader);
      FspData->PlatformData.MicrocodeRegionBase += 0x60;
      DEBUG ((DEBUG_INFO | DEBUG_INIT, "MicrocodeRegionBase : 0x%08x\n", FspData->PlatformData.MicrocodeRegionBase));
      DEBUG ((DEBUG_INFO | DEBUG_INIT, "MicrocodeRegionSize : 0x%08x\n", FspData->PlatformData.MicrocodeRegionSize));
      DEBUG ((DEBUG_INFO | DEBUG_INIT, "CodeRegionBase      : 0x%08x\n", FspData->PlatformData.CodeRegionBase));
      DEBUG ((DEBUG_INFO | DEBUG_INIT, "CodeRegionSize      : 0x%08x\n", FspData->PlatformData.CodeRegionSize));
    }
#endif

    if (CompareGuid (FvName, &gFspSiliconRebasedFvGuid)) {
      PcdSet32S (PcdFspsBaseAddress, (UINT32) FvHeader);
    } else {
#endif
      if (CompareGuid (&FvHeader->FileSystemGuid, &gEfiSystemNvDataFvGuid)) {
        Status = CopyNvStorageDataToDefaultVariableHob (FvHeader);
        ASSERT_EFI_ERROR (Status);
      }
      for (FvIndex = 0; FvIndex < FvCount; FvIndex++) {
        if (CompareGuid (FvName, FvList[FvIndex])) {
          PeiServicesInstallFvInfoPpi (NULL, FvHeader, (UINT32) FvHeader->FvLength, NULL, NULL);
          InstallCount++;
        }
      }
#if FixedPcdGetBool(PcdFspWrapperEnable) == 1
    }
#endif
    FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *) ((UINTN) FvHeader + (UINTN) FvHeader->FvLength);
  } //while

  DEBUG ((DEBUG_INFO, "Finished parsing FV\n"));
  if (InstallCount != FvCount) {
    DEBUG ((DEBUG_WARN, "(Did not find all FVs in FvList)\n"));
  }

  return EFI_SUCCESS;
}

/**
  Locate and install Firmware Volume HOBs once there is main memory

  @param  PeiServices       General purpose services available to every PEIM
  @param  NotifyDescriptor  Notify that this module published
  @param  Ppi               PPI that was installed

  @retval  EFI_SUCCESS     The function completed successfully
**/
EFI_STATUS
EFIAPI
GetFvNotifyCallback (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDescriptor,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS                    Status;
  VOID                          *BiosRegion;
  BPDT_HEADER                   *Bpdt4;
  SUB_PARTITION_DATA            ObbData;
  UINTN                         FitBase;

  DEBUG ((EFI_D_INFO, "GetFvNotifyCallback: Processing BPDT Payloads\n"));

  Status = GetBiosRegion (&BiosRegion);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "GetBiosRegion() - %r\n", Status));
    return Status;
  }

  Bpdt4 = (BPDT_HEADER *) BiosRegion;
  if (Bpdt4 == NULL) {
    return EFI_NOT_FOUND;
  }
  DEBUG ((EFI_D_INFO, "Signature BPDT4 = 0x%X\n", Bpdt4->Signature));
  if (Bpdt4->Signature != BPDT_SIGN_GREEN) {
    // Should not continue execution at this point
    DEBUG ((EFI_D_ERROR, "GREEN signature = 0x%X\n", BPDT_SIGN_GREEN));
    DEBUG ((EFI_D_ERROR, "Signature failure, cannot continue!\n"));
    ASSERT ((Bpdt4->Signature == BPDT_SIGN_GREEN));
    return EFI_VOLUME_CORRUPTED;
  }

  Status = GetSubPartitionData (BpdtObb, Bpdt4, &ObbData);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = ParseFvData (&ObbData, mObbGuids, (sizeof (mObbGuids) / sizeof (EFI_GUID *)));
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Update the FIT HOB to point to post-memory locations
  //
  Status = GetFitBase (&FitBase);
  if (!EFI_ERROR (Status)) {
    Status = ProduceFitHob (FitBase);
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}

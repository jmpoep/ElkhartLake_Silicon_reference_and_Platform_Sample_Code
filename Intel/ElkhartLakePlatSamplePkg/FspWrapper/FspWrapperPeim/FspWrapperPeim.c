/** @file
  FSP WrapperPeim implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2020 Intel Corporation.

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

#include <Uefi.h>
#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PlatformInitLib.h>
#include <Library/SmmAccessLib.h>
#include <Library/PchSmmControlLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/HobLib.h>
#include <Library/MtrrLib.h>
#include <Library/SiMtrrLib.h>
#include <Ppi/MpServices.h>
#include <IndustryStandard/FirmwareVersionInfo.h>
#include <FspInfoHob.h>

#define  FSP_BIN_VERSION_STRING       "FSP Binary Version"

EFI_STATUS
FspWrapperMtrrEndOfPeiEvent (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDesc,
  IN VOID                       *Ppi
  );

static EFI_PEI_NOTIFY_DESCRIPTOR  mFspWrapperMtrrEndofPeiNotifyList = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEndOfPeiSignalPpiGuid,
  FspWrapperMtrrEndOfPeiEvent
};

#if FixedPcdGet8(PcdFspModeSelection) == 1
EFI_PEI_PPI_DESCRIPTOR mFspReadyToInstallMp = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gPeiReadyToInstallMpPpiGuid,
  NULL
};
#endif
/**
  A minimal wrapper function that allows MtrrSetAllMtrrs() to be passed to
  EFI_PEI_MP_SERVICES_PPI.StartupAllAPs() as Procedure.

  @param[in] Buffer  Pointer to an MTRR_SETTINGS object, to be passed to
                     MtrrSetAllMtrrs().
**/
VOID
EFIAPI
SetMtrrsFromBuffer (
  IN VOID *Buffer
  )
{
  MtrrSetAllMtrrs (Buffer);
}

/**
  FSP Mtrr End of PEI callback function.

  @param[in] PeiServices   - Pointer to PEI Services Table.
  @param[in] NotifyDesc    - Pointer to the descriptor for the Notification event that
                             caused this function to execute.
  @param[in] Ppi           - Pointer to the PPI data associated with this function.

  @retval EFI_STATUS       - Always return EFI_SUCCESS
**/
EFI_STATUS
FspWrapperMtrrEndOfPeiEvent (
  IN EFI_PEI_SERVICES           **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR  *NotifyDesc,
  IN VOID                       *Ppi
  )
{
  EFI_STATUS               Status;
  MTRR_SETTINGS            MtrrSetting;
  EFI_PEI_MP_SERVICES_PPI  *gMpServicesPpi;

  Status = MtrrTransfer2DefaultWB (&MtrrSetting);
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  //
  // Synchronize the update with all APs
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiMpServicesPpiGuid,
             0,
             NULL,
             (VOID **) &gMpServicesPpi
             );

  if (!EFI_ERROR (Status)) {
    MtrrGetAllMtrrs (&MtrrSetting);
    gMpServicesPpi->StartupAllAPs (
                      PeiServices,
                      gMpServicesPpi,
                      (EFI_AP_PROCEDURE) SetMtrrsFromBuffer,
                      FALSE,
                      0,
                      (VOID *) &MtrrSetting
                      );
  } else {
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}


/**
  Publish FSP binary version via FVI

  @param[in]     None

  @retval        EFI_SUCCESS
                 EFI_NOT_FOUND
**/
EFI_STATUS
PublishFspVersion (VOID)
{
  SMBIOS_TABLE_TYPE_OEM_INTEL_FVI *FspFviRecord;
  UINT8                           FspFviRecordSize;
  INTEL_FIRMWARE_VERSION_INFO     FspFviData;
  UINT8                           FspFviCount;
  UINTN                           *DestPtr;
  VOID                            *FspFviHobPtr;
  FSP_INFO_HOB                    *FspInfo;

  //
  // Locate FSP_INFO_HOB
  //
  FspInfo = (FSP_INFO_HOB *) GetFirstGuidHob (&gFspInfoGuid);
  if (FspInfo == NULL) {
    return EFI_NOT_FOUND;
  }

  FspFviCount      = 1;
  FspFviRecordSize = sizeof (SMBIOS_STRUCTURE) + sizeof (UINT8) + (FspFviCount * sizeof (INTEL_FIRMWARE_VERSION_INFO)) + sizeof (FSP_BIN_VERSION_STRING) + sizeof (UINT8);
  DestPtr          = NULL;
  FspFviHobPtr     = NULL;

  //
  // Initialize FSP binary FVI record.
  //
  FspFviRecord = (SMBIOS_TABLE_TYPE_OEM_INTEL_FVI *) AllocateZeroPool (FspFviRecordSize);
  if (FspFviRecord != NULL) {
    FspFviRecord->Header.Type   = PcdGet8 (PcdFviSmbiosType);
    FspFviRecord->Header.Length = sizeof (SMBIOS_STRUCTURE) + sizeof (UINT8) + (FspFviCount * sizeof (INTEL_FIRMWARE_VERSION_INFO));
    FspFviRecord->Header.Handle = 0;
    FspFviRecord->Count         = FspFviCount;

    //
    // Initialize FSP binary FVI data.
    //
    FspFviData.ComponentName        = 1;
    FspFviData.VersionString        = 0;
    FspFviData.Version.MajorVersion =  FspInfo->SiliconInitVersionMajor;
    FspFviData.Version.MinorVersion =  FspInfo->SiliconInitVersionMinor;
    FspFviData.Version.Revision =      FspInfo->FspVersionRevision;
    FspFviData.Version.BuildNumber =   (UINT16) FspInfo->FspVersionBuild;

    //
    // Concatenate FVI data to FVI record
    //
    DestPtr = (UINTN *)((UINTN)FspFviRecord + sizeof (SMBIOS_STRUCTURE) + sizeof (UINT8));
    CopyMem (DestPtr, &FspFviData, sizeof (INTEL_FIRMWARE_VERSION_INFO));

    //
    // Concatenate FVI strings to FVI record
    //
    DestPtr = (UINTN *)((UINTN)DestPtr + (FspFviCount * sizeof (INTEL_FIRMWARE_VERSION_INFO)));
    CopyMem (DestPtr, FSP_BIN_VERSION_STRING, sizeof (FSP_BIN_VERSION_STRING));

    FspFviHobPtr = BuildGuidDataHob (
                           &gIntelSmbiosDataHobGuid,
                           (VOID *) FspFviRecord,
                           FspFviRecordSize
                             );
    ASSERT (FspFviHobPtr != NULL);

    FreePool (FspFviRecord);
  } else {
    ASSERT_EFI_ERROR (EFI_OUT_OF_RESOURCES);
  }

  return EFI_SUCCESS;
}


/**
  The Entry point of the FSP wrapper PEIM

  @param[in]  FileHandle   Pointer to image file handle
  @param[in]  PeiServices  Pointer to PEI Services Table

  @return     EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
FspWrapperPeimEntry (
  IN       EFI_PEI_FILE_HANDLE  FileHandle,
  IN CONST EFI_PEI_SERVICES     **PeiServices
  )
{
  EFI_STATUS                       Status;
  EFI_BOOT_MODE                    BootMode;

  DEBUG ((DEBUG_INFO, "Entered FSP WrapperPeim entry\n"));

  PlatformLateInit ();
  PeiInstallSmmAccessPpi ();
  PchSmmControlInit ();
  PublishFspVersion ();

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  if (BootMode == BOOT_ON_S3_RESUME) {
#if FixedPcdGet8(PcdFspModeSelection) == 1
    //
    // Install mp service to sync BSP AP mtrrs when S3 resume.
    //
    Status = PeiServicesInstallPpi (&mFspReadyToInstallMp);
    ASSERT_EFI_ERROR (Status);
#endif
    //
    // Install Fsp Wrapper Mtrr Notify for S3 resume
    //
    Status = PeiServicesNotifyPpi (&mFspWrapperMtrrEndofPeiNotifyList);
    ASSERT_EFI_ERROR (Status);
  }

  DEBUG ((DEBUG_INFO, "Exit FSP WrapperPeim\n"));
  return EFI_SUCCESS;
}

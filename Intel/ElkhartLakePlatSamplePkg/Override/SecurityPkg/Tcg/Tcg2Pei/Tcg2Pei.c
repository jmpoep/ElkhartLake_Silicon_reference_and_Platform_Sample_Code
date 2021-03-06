/** @file
  Initialize TPM2 device and measure FVs before handing off control to DXE.

Copyright (c) 2015 - 2019, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <PiPei.h>

#include <IndustryStandard/UefiTcgPlatform.h>
#include <Ppi/FirmwareVolumeInfo.h>
#include <Ppi/FirmwareVolumeInfo2.h>
#include <Ppi/LockPhysicalPresence.h>
#include <Ppi/TpmInitialized.h>
#include <Ppi/FirmwareVolume.h>
//#include <Ppi/EndOfPeiPhase.h> // RPPO-LKF-0029:RoyalParkOverrideContent
#include <Ppi/TpmMeasure.h>      // RPPO-LKF-0029:RoyalParkOverrideContent
#include <Ppi/FirmwareVolumeInfoMeasurementExcluded.h>

#include <Guid/TcgEventHob.h>
#include <Guid/MeasuredFvHob.h>
#include <Guid/TpmInstance.h>

#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/PeimEntryPoint.h>
#include <Library/Tpm2CommandLib.h>
#include <Library/Tpm2DeviceLib.h>
#include <Library/HashLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Protocol/Tcg2Protocol.h>
#include <Library/PerformanceLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/ResetSystemLib.h>
#include <Library/Tcg2PhysicalPresenceLib.h>

#define PERF_ID_TCG2_PEI  0x3080

#if FixedPcdGetBool(PcdEdk2MasterEnable) == 1
#define PEI_CORE_MAX_FV_SUPPORTED  24
#endif

typedef struct {
  EFI_GUID                   *EventGuid;
  EFI_TCG2_EVENT_LOG_FORMAT  LogFormat;
} TCG2_EVENT_INFO_STRUCT;

TCG2_EVENT_INFO_STRUCT mTcg2EventInfo[] = {
  {&gTcgEventEntryHobGuid,   EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2},
  {&gTcgEvent2EntryHobGuid,  EFI_TCG2_EVENT_LOG_FORMAT_TCG_2},
};

BOOLEAN                 mImageInMemory  = FALSE;
EFI_PEI_FILE_HANDLE     mFileHandle;

EFI_PEI_PPI_DESCRIPTOR  mTpmInitializedPpiList = {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gPeiTpmInitializedPpiGuid,
  NULL
};

EFI_PEI_PPI_DESCRIPTOR  mTpmInitializationDonePpiList = {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gPeiTpmInitializationDonePpiGuid,
  NULL
};

//
// RPPO-LKF-0029:RoyalParkOverrideBegin
//
/*
EFI_PLATFORM_FIRMWARE_BLOB *mMeasuredBaseFvInfo;
UINT32 mMeasuredBaseFvIndex = 0;

EFI_PLATFORM_FIRMWARE_BLOB *mMeasuredChildFvInfo;
UINT32 mMeasuredChildFvIndex = 0;
*/
//
// RPPO-LKF-0029:RoyalParkOverrideEnd
//

/**
  Measure and record the Firmware Volum Information once FvInfoPPI install.

  @param[in] PeiServices       An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation.
  @param[in] NotifyDescriptor  Address of the notification descriptor data structure.
  @param[in] Ppi               Address of the PPI that was installed.

  @retval EFI_SUCCESS          The FV Info is measured and recorded to TPM.
  @return Others               Fail to measure FV.

**/
EFI_STATUS
EFIAPI
FirmwareVolmeInfoPpiNotifyCallback (
  IN EFI_PEI_SERVICES              **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR     *NotifyDescriptor,
  IN VOID                          *Ppi
  );

/**
  Record all measured Firmware Volum Information into a Guid Hob

  @param[in] PeiServices       An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation.
  @param[in] NotifyDescriptor  Address of the notification descriptor data structure.
  @param[in] Ppi               Address of the PPI that was installed.

  @retval EFI_SUCCESS          The FV Info is measured and recorded to TPM.
  @return Others               Fail to measure FV.

**/
//
// RPPO-LKF-0029:RoyalParkOverrideBegin
//
/*
EFI_STATUS
EFIAPI
EndofPeiSignalNotifyCallBack (
  IN EFI_PEI_SERVICES              **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR     *NotifyDescriptor,
  IN VOID                          *Ppi
  );
*/
//
// RPPO-LKF-0029:RoyalParkOverrideEnd
//

//
// RPPO-LKF-0029:RoyalParkOverrideBegin
//
/**
  Measure FV image.
  Add it into the measured FV list after the FV is measured successfully.

  @param[in]  FvBase            Base address of FV image.
  @param[in]  FvLength          Length of FV image.

  @retval EFI_SUCCESS           Fv image is measured successfully
                                or it has been already measured.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.

**/
EFI_STATUS
MeasureFvImage (
  IN EFI_PHYSICAL_ADDRESS           FvBase,
  IN UINT64                         FvLength
  );

/**
  Measure main BIOS.

  @retval EFI_SUCCESS           Operation completed successfully.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.

**/
EFI_STATUS
MeasureMainBios (
  VOID
  );

GLOBAL_REMOVE_IF_UNREFERENCED PEI_TPM_MEASURE_PPI mTpmMeasurePpi = {
  MeasureFvImage,
  MeasureMainBios
};

EFI_PEI_PPI_DESCRIPTOR  mTpmMeasurePpiList = {
  EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST,
  &gPeiTpmMeasurePpiGuid,
  &mTpmMeasurePpi
};

//
// RPPO-LKF-0029:RoyalParkOverrideEnd
//

EFI_PEI_NOTIFY_DESCRIPTOR           mNotifyList[] = {
  {
    EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK,
    &gEfiPeiFirmwareVolumeInfoPpiGuid,
    FirmwareVolmeInfoPpiNotifyCallback
  },
  {
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiPeiFirmwareVolumeInfo2PpiGuid,
    FirmwareVolmeInfoPpiNotifyCallback
  }
  //
  // RPPO-LKF-0029:RoyalParkOverrideBegin
  //
  /*
  ,{
    (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
    &gEfiEndOfPeiSignalPpiGuid,
    EndofPeiSignalNotifyCallBack
  }
  */
  //
  // RPPO-LKF-0029:RoyalParkOverrideEnd
  //
};

//EFI_PEI_FIRMWARE_VOLUME_INFO_MEASUREMENT_EXCLUDED_PPI *mMeasurementExcludedFvPpi; // RPPO-LKF-0029:RoyalParkOverrideContent

//
// RPPO-LKF-0029:RoyalParkOverrideBegin
//

/**
  Returns a pointer the Measured FV GUID HOB.

  @param[out] MeasuredHobData   A pointer to the Measured FV HOB data.

  @retval EFI_SUCCESS           The HOB data pointer was successfully updated.
  @retval EFI_OUT_OF_RESOURCES  Insufficient memory resources are available to allocate the HOB.

**/
EFI_STATUS
EFIAPI
GetMeasuredFvHob (
  OUT MEASURED_HOB_DATA **MeasuredHobData
  )
{
  EFI_HOB_GUID_TYPE   *GuidHob;
  MEASURED_HOB_DATA   *MeasuredHobDataPtr;
  UINTN               MeasuredHobDataSize;

  MeasuredHobDataPtr = NULL;

  GuidHob = GetFirstGuidHob (&gMeasuredFvHobGuid);
  if (GuidHob == NULL) {
    //
    // Build an initial empty HOB if it does not exist
    //
#if FixedPcdGetBool(PcdEdk2MasterEnable) == 1
    MeasuredHobDataSize = OFFSET_OF (MEASURED_HOB_DATA, MeasuredFvBuf) + \
                          (sizeof (EFI_PLATFORM_FIRMWARE_BLOB) * PEI_CORE_MAX_FV_SUPPORTED);
#else
    MeasuredHobDataSize = OFFSET_OF (MEASURED_HOB_DATA, MeasuredFvBuf) + \
                          (sizeof (EFI_PLATFORM_FIRMWARE_BLOB) * PcdGet32 (PcdPeiCoreMaxFvSupported));
#endif
    MeasuredHobDataPtr =  BuildGuidHob (
                            &gMeasuredFvHobGuid,
                            MeasuredHobDataSize
                            );
    if (MeasuredHobDataPtr != NULL) {
      ZeroMem ((VOID *) MeasuredHobDataPtr, MeasuredHobDataSize);
    } else {
      return EFI_OUT_OF_RESOURCES;
    }
    *MeasuredHobData = MeasuredHobDataPtr;
  } else {
    *MeasuredHobData = GET_GUID_HOB_DATA (GuidHob);
  }

  return EFI_SUCCESS;
}

  //
  // RPPO-LKF-0029:RoyalParkOverrideEnd
  //

/**
  Make sure that the current PCR allocations, the TPM supported PCRs,
  and the PcdTpm2HashMask are all in agreement.
**/
VOID
SyncPcrAllocationsAndPcrMask (
  VOID
  )
{
  EFI_STATUS                        Status;
  EFI_TCG2_EVENT_ALGORITHM_BITMAP   TpmHashAlgorithmBitmap;
  UINT32                            TpmActivePcrBanks;
  UINT32                            NewTpmActivePcrBanks;
  UINT32                            Tpm2PcrMask;
  UINT32                            NewTpm2PcrMask;

  DEBUG ((EFI_D_ERROR, "SyncPcrAllocationsAndPcrMask!\n"));

  //
  // Determine the current TPM support and the Platform PCR mask.
  //
  Status = Tpm2GetCapabilitySupportedAndActivePcrs (&TpmHashAlgorithmBitmap, &TpmActivePcrBanks);
  ASSERT_EFI_ERROR (Status);

  Tpm2PcrMask = PcdGet32 (PcdTpm2HashMask);

  //
  // Find the intersection of Pcd support and TPM support.
  // If banks are missing from the TPM support that are in the PCD, update the PCD.
  // If banks are missing from the PCD that are active in the TPM, reallocate the banks and reboot.
  //

  //
  // If there are active PCR banks that are not supported by the Platform mask,
  // update the TPM allocations and reboot the machine.
  //
  if ((TpmActivePcrBanks & Tpm2PcrMask) != TpmActivePcrBanks) {
    NewTpmActivePcrBanks = TpmActivePcrBanks & Tpm2PcrMask;

    DEBUG ((EFI_D_INFO, "%a - Reallocating PCR banks from 0x%X to 0x%X.\n", __FUNCTION__, TpmActivePcrBanks, NewTpmActivePcrBanks));
    if (NewTpmActivePcrBanks == 0) {
      DEBUG ((EFI_D_ERROR, "%a - No viable PCRs active! Please set a less restrictive value for PcdTpm2HashMask!\n", __FUNCTION__));
      ASSERT (FALSE);
    } else {
      Status = Tpm2PcrAllocateBanks (NULL, (UINT32)TpmHashAlgorithmBitmap, NewTpmActivePcrBanks);
      if (EFI_ERROR (Status)) {
        //
        // We can't do much here, but we hope that this doesn't happen.
        //
        DEBUG ((EFI_D_ERROR, "%a - Failed to reallocate PCRs!\n", __FUNCTION__));
        ASSERT_EFI_ERROR (Status);
      }
      //
      // Need reset system, since we just called Tpm2PcrAllocateBanks().
      //
      ResetCold();
    }
  }

  //
  // If there are any PCRs that claim support in the Platform mask that are
  // not supported by the TPM, update the mask.
  //
  if ((Tpm2PcrMask & TpmHashAlgorithmBitmap) != Tpm2PcrMask) {
    NewTpm2PcrMask = Tpm2PcrMask & TpmHashAlgorithmBitmap;

    DEBUG ((EFI_D_INFO, "%a - Updating PcdTpm2HashMask from 0x%X to 0x%X.\n", __FUNCTION__, Tpm2PcrMask, NewTpm2PcrMask));
    if (NewTpm2PcrMask == 0) {
      DEBUG ((EFI_D_ERROR, "%a - No viable PCRs supported! Please set a less restrictive value for PcdTpm2HashMask!\n", __FUNCTION__));
      ASSERT (FALSE);
    }

    Status = PcdSet32S (PcdTpm2HashMask, NewTpm2PcrMask);
    ASSERT_EFI_ERROR (Status);
  }
}

/**
  Add a new entry to the Event Log.

  @param[in]     DigestList    A list of digest.
  @param[in,out] NewEventHdr   Pointer to a TCG_PCR_EVENT_HDR data structure.
  @param[in]     NewEventData  Pointer to the new event data.

  @retval EFI_SUCCESS           The new event log entry was added.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
**/
EFI_STATUS
LogHashEvent (
  IN TPML_DIGEST_VALUES             *DigestList,
  IN OUT  TCG_PCR_EVENT_HDR         *NewEventHdr,
  IN      UINT8                     *NewEventData
  )
{
  VOID                              *HobData;
  EFI_STATUS                        Status;
  UINTN                             Index;
  EFI_STATUS                        RetStatus;
  UINT32                            SupportedEventLogs;
  TCG_PCR_EVENT2                    *TcgPcrEvent2;
  UINT8                             *DigestBuffer;

  SupportedEventLogs = EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2 | EFI_TCG2_EVENT_LOG_FORMAT_TCG_2;

  RetStatus = EFI_SUCCESS;
  for (Index = 0; Index < sizeof(mTcg2EventInfo)/sizeof(mTcg2EventInfo[0]); Index++) {
    if ((SupportedEventLogs & mTcg2EventInfo[Index].LogFormat) != 0) {
      DEBUG ((EFI_D_INFO, "  LogFormat - 0x%08x\n", mTcg2EventInfo[Index].LogFormat));
      switch (mTcg2EventInfo[Index].LogFormat) {
      case EFI_TCG2_EVENT_LOG_FORMAT_TCG_1_2:
        Status = GetDigestFromDigestList (TPM_ALG_SHA1, DigestList, &NewEventHdr->Digest);
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
        //
        // Use GetDigestListSize (DigestList) in the GUID HOB DataLength calculation
        // to reserve enough buffer to hold TPML_DIGEST_VALUES compact binary.
        //
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

/**
  Do a hash operation on a data buffer, extend a specific TPM PCR with the hash result,
  and build a GUIDed HOB recording the event which will be passed to the DXE phase and
  added into the Event Log.

  @param[in]      Flags         Bitmap providing additional information.
  @param[in]      HashData      Physical address of the start of the data buffer
                                to be hashed, extended, and logged.
  @param[in]      HashDataLen   The length, in bytes, of the buffer referenced by HashData.
  @param[in]      NewEventHdr   Pointer to a TCG_PCR_EVENT_HDR data structure.
  @param[in]      NewEventData  Pointer to the new event data.

  @retval EFI_SUCCESS           Operation completed successfully.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.

**/
EFI_STATUS
HashLogExtendEvent (
  IN      UINT64                    Flags,
  IN      UINT8                     *HashData,
  IN      UINTN                     HashDataLen,
  IN      TCG_PCR_EVENT_HDR         *NewEventHdr,
  IN      UINT8                     *NewEventData
  )
{
  EFI_STATUS                        Status;
  TPML_DIGEST_VALUES                DigestList;

  if (GetFirstGuidHob (&gTpmErrorHobGuid) != NULL) {
    return EFI_DEVICE_ERROR;
  }

  Status = HashAndExtend (
             NewEventHdr->PCRIndex,
             HashData,
             HashDataLen,
             &DigestList
             );
  if (!EFI_ERROR (Status)) {
    if ((Flags & EFI_TCG2_EXTEND_ONLY) == 0) {
      Status = LogHashEvent (&DigestList, NewEventHdr, NewEventData);
    }
  }

  if (Status == EFI_DEVICE_ERROR) {
    DEBUG ((EFI_D_ERROR, "HashLogExtendEvent - %r. Disable TPM.\n", Status));
    BuildGuidHob (&gTpmErrorHobGuid,0);
    REPORT_STATUS_CODE (
      EFI_ERROR_CODE | EFI_ERROR_MINOR,
      (PcdGet32 (PcdStatusCodeSubClassTpmDevice) | EFI_P_EC_INTERFACE_ERROR)
      );
  }

  return Status;
}

/**
  Measure CRTM version.

  @retval EFI_SUCCESS           Operation completed successfully.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.

**/
EFI_STATUS
MeasureCRTMVersion (
  VOID
  )
{
  TCG_PCR_EVENT_HDR                 TcgEventHdr;

  //
  // Use FirmwareVersion string to represent CRTM version.
  // OEMs should get real CRTM version string and measure it.
  //

  TcgEventHdr.PCRIndex  = 0;
  TcgEventHdr.EventType = EV_S_CRTM_VERSION;
  TcgEventHdr.EventSize = (UINT32) StrSize((CHAR16*)PcdGetPtr (PcdFirmwareVersionString));

  return HashLogExtendEvent (
           0,
           (UINT8*)PcdGetPtr (PcdFirmwareVersionString),
           TcgEventHdr.EventSize,
           &TcgEventHdr,
           (UINT8*)PcdGetPtr (PcdFirmwareVersionString)
           );
}

/**
  Measure FV image.
  Add it into the measured FV list after the FV is measured successfully.

  @param[in]  FvBase            Base address of FV image.
  @param[in]  FvLength          Length of FV image.

  @retval EFI_SUCCESS           Fv image is measured successfully
                                or it has been already measured.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.

**/
EFI_STATUS
MeasureFvImage (
  IN EFI_PHYSICAL_ADDRESS           FvBase,
  IN UINT64                         FvLength
  )
{
  UINT32                                                Index;
  EFI_STATUS                                            Status;
  EFI_PLATFORM_FIRMWARE_BLOB                            FvBlob;
  TCG_PCR_EVENT_HDR                                     TcgEventHdr;
  //
  // RPPO-LKF-0029:RoyalParkOverrideBegin
  //
  UINT32                                                Instance;
  EFI_PEI_FIRMWARE_VOLUME_INFO_MEASUREMENT_EXCLUDED_PPI *MeasurementExcludedFvPpi;
  MEASURED_HOB_DATA                                     *MeasuredHobData;  // RPPO-LKF-0029:RoyalParkOverrideContent

  //
  // Check Excluded FV list
  //
  Instance = 0;
  do {
    Status = PeiServicesLocatePpi(
                 &gEfiPeiFirmwareVolumeInfoMeasurementExcludedPpiGuid,
                 Instance,
                 NULL,
                 (VOID**)&MeasurementExcludedFvPpi
                 );
    if (!EFI_ERROR(Status)) {
      for (Index = 0; Index < MeasurementExcludedFvPpi->Count; Index ++) {
        if (MeasurementExcludedFvPpi->Fv[Index].FvBase == FvBase
         && MeasurementExcludedFvPpi->Fv[Index].FvLength == FvLength) {
          DEBUG ((DEBUG_INFO, "The FV which is excluded by Tcg2Pei starts at: 0x%x\n", FvBase));
          DEBUG ((DEBUG_INFO, "The FV which is excluded by Tcg2Pei has the size: 0x%x\n", FvLength));
          return EFI_SUCCESS;
        }
      }

      Instance++;
    }
  } while (!EFI_ERROR(Status));

  MeasuredHobData = NULL;
  Status = GetMeasuredFvHob (&MeasuredHobData);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Check whether FV is in the measured FV list.
  //
#if FixedPcdGetBool(PcdEdk2MasterEnable) == 1
  ASSERT (MeasuredHobData->Num < PEI_CORE_MAX_FV_SUPPORTED);
#else
  ASSERT (MeasuredHobData->Num < PcdGet32 (PcdPeiCoreMaxFvSupported));
#endif
  for (Index = 0; Index < MeasuredHobData->Num; Index ++) {
    if (MeasuredHobData->MeasuredFvBuf[Index].BlobBase == FvBase) {
      return EFI_SUCCESS;
    }
  }

  //
  // RPPO-LKF-0029:RoyalParkOverrideEnd
  //

  //
  // Measure and record the FV to the TPM
  //
  FvBlob.BlobBase   = FvBase;
  FvBlob.BlobLength = FvLength;

  DEBUG ((DEBUG_INFO, "The FV which is measured by Tcg2Pei starts at: 0x%x\n", FvBlob.BlobBase));
  DEBUG ((DEBUG_INFO, "The FV which is measured by Tcg2Pei has the size: 0x%x\n", FvBlob.BlobLength));

  TcgEventHdr.PCRIndex = 0;
  TcgEventHdr.EventType = EV_EFI_PLATFORM_FIRMWARE_BLOB;
  TcgEventHdr.EventSize = sizeof (FvBlob);

  Status = HashLogExtendEvent (
             0,
             (UINT8*) (UINTN) FvBlob.BlobBase,
             (UINTN) FvBlob.BlobLength,
             &TcgEventHdr,
             (UINT8*) &FvBlob
             );

  //
  // RPPO-LKF-0029:RoyalParkOverrideBegin
  //

  //
  // Add new FV into the measured FV list.
  //
#if FixedPcdGetBool(PcdEdk2MasterEnable) == 1
  if (MeasuredHobData->Num < PEI_CORE_MAX_FV_SUPPORTED) {
#else
  if (MeasuredHobData->Num < PcdGet32 (PcdPeiCoreMaxFvSupported)) {
#endif
    MeasuredHobData->MeasuredFvBuf[MeasuredHobData->Num].BlobBase   = FvBase;
    MeasuredHobData->MeasuredFvBuf[MeasuredHobData->Num].BlobLength = FvLength;
    MeasuredHobData->Num++;
  }

  //
  // RPPO-LKF-0029:RoyalParkOverrideEnd
  //

  return Status;
}

/**
  Measure main BIOS.

  @retval EFI_SUCCESS           Operation completed successfully.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.

**/
EFI_STATUS
MeasureMainBios (
  VOID
  )
{
  EFI_STATUS                        Status;
  UINT32                            FvInstances;
  EFI_PEI_FV_HANDLE                 VolumeHandle;
  EFI_FV_INFO                       VolumeInfo;
  EFI_PEI_FIRMWARE_VOLUME_PPI       *FvPpi;

  PERF_START_EX (mFileHandle, "EventRec", "Tcg2Pei", 0, PERF_ID_TCG2_PEI);
  FvInstances    = 0;
  while (TRUE) {
    //
    // Traverse all firmware volume instances of Static Core Root of Trust for Measurement
    // (S-CRTM), this firmware volume measure policy can be modified/enhanced by special
    // platform for special CRTM TPM measuring.
    //
    Status = PeiServicesFfsFindNextVolume (FvInstances, &VolumeHandle);
    if (EFI_ERROR (Status)) {
      break;
    }

    //
    // Measure and record the firmware volume that is dispatched by PeiCore
    //
    Status = PeiServicesFfsGetVolumeInfo (VolumeHandle, &VolumeInfo);
    ASSERT_EFI_ERROR (Status);
    //
    // Locate the corresponding FV_PPI according to founded FV's format guid
    //
    Status = PeiServicesLocatePpi (
               &VolumeInfo.FvFormat,
               0,
               NULL,
               (VOID**)&FvPpi
               );
    if (!EFI_ERROR (Status)) {
      MeasureFvImage ((EFI_PHYSICAL_ADDRESS) (UINTN) VolumeInfo.FvStart, VolumeInfo.FvSize);
    }

    FvInstances++;
  }
  PERF_END_EX (mFileHandle, "EventRec", "Tcg2Pei", 0, PERF_ID_TCG2_PEI + 1);

  return EFI_SUCCESS;
}

/**
  Measure and record the Firmware Volum Information once FvInfoPPI install.

  @param[in] PeiServices       An indirect pointer to the EFI_PEI_SERVICES table published by the PEI Foundation.
  @param[in] NotifyDescriptor  Address of the notification descriptor data structure.
  @param[in] Ppi               Address of the PPI that was installed.

  @retval EFI_SUCCESS          The FV Info is measured and recorded to TPM.
  @return Others               Fail to measure FV.

**/
EFI_STATUS
EFIAPI
FirmwareVolmeInfoPpiNotifyCallback (
  IN EFI_PEI_SERVICES               **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR      *NotifyDescriptor,
  IN VOID                           *Ppi
  )
{
  EFI_PEI_FIRMWARE_VOLUME_INFO_PPI  *Fv;
  EFI_STATUS                        Status;
  EFI_PEI_FIRMWARE_VOLUME_PPI       *FvPpi;
  UINTN                             Index;
  MEASURED_HOB_DATA                 *MeasuredHobData;  // RPPO-LKF-0029:RoyalParkOverrideContent

  Fv = (EFI_PEI_FIRMWARE_VOLUME_INFO_PPI *) Ppi;

  //
  // The PEI Core can not dispatch or load files from memory mapped FVs that do not support FvPpi.
  //
  Status = PeiServicesLocatePpi (
             &Fv->FvFormat,
             0,
             NULL,
             (VOID**)&FvPpi
             );
  if (EFI_ERROR (Status)) {
    return EFI_SUCCESS;
  }

  //
  // RPPO-LKF-0029:RoyalParkOverrideBegin
  //

  MeasuredHobData = NULL;
  Status = GetMeasuredFvHob (&MeasuredHobData);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // This is an FV from an FFS file, and the parent FV must have already been measured,
  // No need to measure twice, so just record the FV and return
  //
  if (Fv->ParentFvName != NULL || Fv->ParentFileName != NULL ) {
#if FixedPcdGetBool(PcdEdk2MasterEnable) == 1
    ASSERT (MeasuredHobData->Num <= PEI_CORE_MAX_FV_SUPPORTED);
    if (MeasuredHobData->Num < PEI_CORE_MAX_FV_SUPPORTED) {
#else
    ASSERT (MeasuredHobData->Num <= PcdGet32 (PcdPeiCoreMaxFvSupported));
    if (MeasuredHobData->Num < PcdGet32 (PcdPeiCoreMaxFvSupported)) {
#endif
      //
      // Check whether FV is in the measured child FV list.
      //
      for (Index = 0; Index < MeasuredHobData->Num; Index++) {
        if (MeasuredHobData->MeasuredFvBuf[Index].BlobBase == (EFI_PHYSICAL_ADDRESS) (UINTN) Fv->FvInfo) {
          return EFI_SUCCESS;
        }
      }
      MeasuredHobData->MeasuredFvBuf[MeasuredHobData->Num].BlobBase   = (EFI_PHYSICAL_ADDRESS) (UINTN) Fv->FvInfo;
      MeasuredHobData->MeasuredFvBuf[MeasuredHobData->Num].BlobLength = Fv->FvInfoSize;
      MeasuredHobData->Num++;
    }
    return EFI_SUCCESS;
  }

  //
  // RPPO-LKF-0029:RoyalParkOverrideEnd
  //

  return MeasureFvImage ((EFI_PHYSICAL_ADDRESS) (UINTN) Fv->FvInfo, Fv->FvInfoSize);
}

/**
  Do measurement after memory is ready.

  @param[in]      PeiServices   Describes the list of possible PEI Services.

  @retval EFI_SUCCESS           Operation completed successfully.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.
  @retval EFI_DEVICE_ERROR      The command was unsuccessful.

**/
EFI_STATUS
PeimEntryMP (
  IN      EFI_PEI_SERVICES          **PeiServices
  )
{
  EFI_STATUS                        Status;

  //
  // RPPO-LKF-0029:RoyalParkOverrideBegin
  //
  /*
  Status = PeiServicesLocatePpi (
               &gEfiPeiFirmwareVolumeInfoMeasurementExcludedPpiGuid,
               0,
               NULL,
               (VOID**)&mMeasurementExcludedFvPpi
               );
  // Do not check status, because it is optional

  mMeasuredBaseFvInfo  = (EFI_PLATFORM_FIRMWARE_BLOB *) AllocateZeroPool (sizeof (EFI_PLATFORM_FIRMWARE_BLOB) * PcdGet32 (PcdPeiCoreMaxFvSupported));
  ASSERT (mMeasuredBaseFvInfo != NULL);
  mMeasuredChildFvInfo = (EFI_PLATFORM_FIRMWARE_BLOB *) AllocateZeroPool (sizeof (EFI_PLATFORM_FIRMWARE_BLOB) * PcdGet32 (PcdPeiCoreMaxFvSupported));
  ASSERT (mMeasuredChildFvInfo != NULL);
  */
  //
  // RPPO-LKF-0029:RoyalParkOverrideEnd
  //

  if (PcdGet8 (PcdTpm2ScrtmPolicy) == 1) {
    Status = MeasureCRTMVersion ();
  }

  Status = MeasureMainBios ();

  //
  // Post callbacks:
  // for the FvInfoPpi services to measure and record
  // the additional Fvs to TPM
  //
  Status = PeiServicesNotifyPpi (&mNotifyList[0]);
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Measure and log Separator event with error, and extend the measurement result into a specific PCR.

  @param[in] PCRIndex         PCR index.

  @retval EFI_SUCCESS         Operation completed successfully.
  @retval EFI_DEVICE_ERROR    The operation was unsuccessful.

**/
EFI_STATUS
MeasureSeparatorEventWithError (
  IN      TPM_PCRINDEX              PCRIndex
  )
{
  TCG_PCR_EVENT_HDR                 TcgEvent;
  UINT32                            EventData;

  //
  // Use EventData 0x1 to indicate there is error.
  //
  EventData = 0x1;
  TcgEvent.PCRIndex  = PCRIndex;
  TcgEvent.EventType = EV_SEPARATOR;
  TcgEvent.EventSize = (UINT32)sizeof (EventData);
  return HashLogExtendEvent(0,(UINT8 *)&EventData, TcgEvent.EventSize, &TcgEvent,(UINT8 *)&EventData);
}

/**
  Entry point of this module.

  @param[in] FileHandle   Handle of the file being invoked.
  @param[in] PeiServices  Describes the list of possible PEI Services.

  @return Status.

**/
EFI_STATUS
EFIAPI
PeimEntryMA (
  IN       EFI_PEI_FILE_HANDLE      FileHandle,
  IN CONST EFI_PEI_SERVICES         **PeiServices
  )
{
  EFI_STATUS                        Status;
  EFI_STATUS                        Status2;
  EFI_BOOT_MODE                     BootMode;
  TPM_PCRINDEX                      PcrIndex;
  BOOLEAN                           S3ErrorReport;

  if (CompareGuid (PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceNoneGuid) ||
      CompareGuid (PcdGetPtr(PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceTpm12Guid)){
    DEBUG ((DEBUG_INFO, "No TPM2 instance required!\n"));
    return EFI_UNSUPPORTED;
  }

  if (GetFirstGuidHob (&gTpmErrorHobGuid) != NULL) {
    DEBUG ((EFI_D_ERROR, "TPM2 error!\n"));
    return EFI_DEVICE_ERROR;
  }

  Status = PeiServicesGetBootMode (&BootMode);
  ASSERT_EFI_ERROR (Status);

  //
  // In S3 path, skip shadow logic. no measurement is required
  //
  if (BootMode != BOOT_ON_S3_RESUME) {
    Status = (**PeiServices).RegisterForShadow(FileHandle);
    if (Status == EFI_ALREADY_STARTED) {
      mImageInMemory = TRUE;
      mFileHandle = FileHandle;
    } else if (Status == EFI_NOT_FOUND) {
      ASSERT_EFI_ERROR (Status);
    }
  }

  if (!mImageInMemory) {
    //
    // Initialize TPM device
    //
    Status = Tpm2RequestUseTpm ();
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "TPM2 not detected!\n"));
      goto Done;
    }

    S3ErrorReport = FALSE;
    if (PcdGet8 (PcdTpm2InitializationPolicy) == 1) {
      if (BootMode == BOOT_ON_S3_RESUME) {
        Status = Tpm2Startup (TPM_SU_STATE);
        if (EFI_ERROR (Status) ) {
          Status = Tpm2Startup (TPM_SU_CLEAR);
          if (!EFI_ERROR(Status)) {
            S3ErrorReport = TRUE;
          }
        }
      } else {
        Status = Tpm2Startup (TPM_SU_CLEAR);
      }
      if (EFI_ERROR (Status) ) {
        goto Done;
      }
    }

    //
    // Update Tpm2HashMask according to PCR bank.
    //
    SyncPcrAllocationsAndPcrMask ();

    if (S3ErrorReport) {
      //
      // The system firmware that resumes from S3 MUST deal with a
      // TPM2_Startup error appropriately.
      // For example, issue a TPM2_Startup(TPM_SU_CLEAR) command and
      // configuring the device securely by taking actions like extending a
      // separator with an error digest (0x01) into PCRs 0 through 7.
      //
      for (PcrIndex = 0; PcrIndex < 8; PcrIndex++) {
        Status = MeasureSeparatorEventWithError (PcrIndex);
        if (EFI_ERROR (Status)) {
          DEBUG ((EFI_D_ERROR, "Separator Event with Error not Measured. Error!\n"));
        }
      }
    }

    //
    // TpmSelfTest is optional on S3 path, skip it to save S3 time
    //
    if (BootMode != BOOT_ON_S3_RESUME) {
      if (PcdGet8 (PcdTpm2SelfTestPolicy) == 1) {
        Status = Tpm2SelfTest (NO);
        if (EFI_ERROR (Status)) {
          goto Done;
        }
      }
    }

    //
    // Only install TpmInitializedPpi on success
    //
    Status = PeiServicesInstallPpi (&mTpmInitializedPpiList);
    ASSERT_EFI_ERROR (Status);

    //
    // RPPO-LKF-0029:RoyalParkOverrideBegin
    //

    //
    // Only install TpmMeasuredPpi on success
    //
    Status2 = PeiServicesInstallPpi (&mTpmMeasurePpiList);
    ASSERT_EFI_ERROR (Status2);

    //
    // RPPO-LKF-0029:RoyalParkOverrideEnd
    //
  }

  if (mImageInMemory) {
    Status = PeimEntryMP ((EFI_PEI_SERVICES**)PeiServices);
    return Status;
  }

Done:
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "TPM2 error! Build Hob\n"));
    BuildGuidHob (&gTpmErrorHobGuid,0);
    REPORT_STATUS_CODE (
      EFI_ERROR_CODE | EFI_ERROR_MINOR,
      (PcdGet32 (PcdStatusCodeSubClassTpmDevice) | EFI_P_EC_INTERFACE_ERROR)
      );
  }
  //
  // Always install TpmInitializationDonePpi no matter success or fail.
  // Other driver can know TPM initialization state by TpmInitializedPpi.
  //
  Status2 = PeiServicesInstallPpi (&mTpmInitializationDonePpiList);
  ASSERT_EFI_ERROR (Status2);

  return Status;
}

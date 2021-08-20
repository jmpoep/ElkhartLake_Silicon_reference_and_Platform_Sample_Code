/** @file
  ME PayLoad Data implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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
#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/PerformanceLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Register/MeRegs.h>
#include <Ppi/SiPolicy.h>
#include <Library/MeTypeLib.h>
#include <Library/PeiMeLib.h>
#if FixedPcdGetBool(PcdBfxEnable) == 0
#include <Ppi/MbpSensitivePpi.h>
#endif
#include <MeBiosPayloadHob.h>
#include <BupMsgs.h>
#include "MbpData.h"
#include <Library/PostCodeLib.h>
#include <Library/HeciInitLib.h>
#include <Library/MeShowBufferLib.h>

/**
  Check if MBP items that might be missing on the first boot are available.
  If not, additional sync messages are executed in order to retrieve them.

  @param[in, out] MbpHob              Pointer to MBP Hob.
**/

VOID
SyncMissingMbpItems (
  IN OUT ME_BIOS_PAYLOAD_HOB *MbpHob
  )
{
  EFI_STATUS Status;

  if (MbpHob->MeBiosPayload.FwCapsSku.Available == FALSE) {
    Status = PeiHeciGetFwCapsSkuMsg (&MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities);
    if (!EFI_ERROR (Status)) {
      MbpHob->MeBiosPayload.FwCapsSku.Available = TRUE;
    }
  }
  if (MbpHob->MeBiosPayload.FwFeaturesState.Available == FALSE) {
    Status = PeiHeciGetFwFeatureStateMsg (&MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures);
    if (!EFI_ERROR (Status)) {
      MbpHob->MeBiosPayload.FwFeaturesState.Available = TRUE;
    }
  }
  if (MbpHob->MeBiosPayload.FwPlatType.Available == FALSE) {
    Status = PeiHeciGetPlatformTypeMsg (&MbpHob->MeBiosPayload.FwPlatType.RuleData);
    if (!EFI_ERROR (Status)) {
      MbpHob->MeBiosPayload.FwPlatType.Available = TRUE;
    }
  }
}

/**
  This routine returns ME-BIOS Payload information.

  @param[out] MbpPtr               ME-BIOS Payload information.
  @param[out] MbpSensitivePtr      ME-BIOS Payload sensitive information.

  @retval     EFI_SUCCESS          The function completed successfully.
  @retval     EFI_DEVICE_ERROR     Failed to consume MBP
  @retval     EFI_OUT_OF_RESOURCES Out of resource
**/
EFI_STATUS
PrepareMeBiosPayload (
  OUT  ME_BIOS_PAYLOAD                *MbpPtr,
  OUT  ME_BIOS_PAYLOAD_SENSITIVE      *MbpSensitivePtr
  )
{
  EFI_STATUS                            Status;
  UINT32                                MbpItemsCount;
  UINT32                                CurrentMbpItem;
  UINT32                                *MbpItems;
  MBP_ITEM_HEADER                       *MbpItemHeader;
  UINT32                                MbpItemId;
  UINT32                                MbpItemLength;
  VOID                                  *DestPtr;
  UINTN                                 DestSize;
  BOOLEAN                               SkipMbp;

  DEBUG ((DEBUG_INFO, "PrepareMeBiosPayload () - Start\n"));

  MbpItems = AllocateZeroPool (MAX_MBP_ITEMS_SIZE);
  if (MbpItems == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SkipMbp = MeMbpHobSkipped ();
  Status = PeiHeciGetMbpMsg (&MbpItemsCount, MbpItems, SkipMbp);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "HECI get MBP error: %r!\n", Status));
    FreePool (MbpItems);
    return Status;
  }
  if (SkipMbp) {
    DEBUG ((DEBUG_WARN, "Skipping MBP data due to SkipMbpHob set!\n"));
    //
    // Clear buffers from sensitive data
    //
    ZeroMem (MbpItems, MAX_MBP_ITEMS_SIZE);
    FreePool (MbpItems);
    return Status;
  }

  ZeroMem (MbpPtr, sizeof (ME_BIOS_PAYLOAD));
  ZeroMem (MbpSensitivePtr, sizeof (ME_BIOS_PAYLOAD_SENSITIVE));

  MbpItemHeader = (MBP_ITEM_HEADER*)MbpItems;

  for (CurrentMbpItem = 0; CurrentMbpItem < MbpItemsCount; CurrentMbpItem++) {

    MbpItemId = MBP_ITEM_ID(MbpItemHeader->Fields.AppId, MbpItemHeader->Fields.ItemId);
    //
    // Item length includes Item Header - need to substract it and convert length to bytes
    //
    MbpItemLength = (MbpItemHeader->Fields.Length - 1) * sizeof (UINT32);
    //
    // Copy data from HECI buffer per size of each MBP item
    //
    switch (MbpItemId) {
      //
      // Insensitive items
      //
      case MBP_ITEM_FW_VERSION_NAME:
        DestSize = sizeof (MbpPtr->FwVersionName);
        DestPtr = &MbpPtr->FwVersionName;
        break;

      case MBP_ITEM_FW_CAPABILITIES:
        DestSize = sizeof (MbpPtr->FwCapsSku.FwCapabilities);
        DestPtr = &MbpPtr->FwCapsSku.FwCapabilities;
        MbpPtr->FwCapsSku.Available = TRUE;
        break;

      case MBP_ITEM_CSE_PLATFORM_TYPE:
        DestSize = sizeof (MbpPtr->FwPlatType.RuleData);
        DestPtr = &MbpPtr->FwPlatType.RuleData;
        MbpPtr->FwPlatType.Available = TRUE;
        break;

      case MBP_ITEM_PERF_DATA:
        DestSize = sizeof (MbpPtr->PlatBootPerfData.MbpPerfData);
        DestPtr = &MbpPtr->PlatBootPerfData.MbpPerfData;
        MbpPtr->PlatBootPerfData.Available = TRUE;
        break;

      case MBP_ITEM_UNCONFIG_ON_RTC:
        DestSize = sizeof (MbpPtr->UnconfigOnRtcClearState.UnconfigOnRtcClearData);
        DestPtr = &MbpPtr->UnconfigOnRtcClearState.UnconfigOnRtcClearData;
        MbpPtr->UnconfigOnRtcClearState.Available = TRUE;
        break;

      case MBP_ITEM_SHIP_STATE:
        DestSize = sizeof (MbpPtr->FwFeaturesState.FwFeatures);
        DestPtr = &MbpPtr->FwFeaturesState.FwFeatures;
        MbpPtr->FwFeaturesState.Available = TRUE;
        break;

      case MBP_ITEM_ID_FW_ARB_SVN:
        DestSize = sizeof (MbpPtr->ArbSvnState.ArbSvnData);
        DestPtr = &MbpPtr->ArbSvnState.ArbSvnData;
        MbpPtr->ArbSvnState.Available = TRUE;
        break;


      case MBP_ITEM_HWA_MTU:
        DestSize = sizeof (MbpPtr->HwaRequest.Data);
        DestPtr = &MbpPtr->HwaRequest.Data;
        MbpPtr->HwaRequest.Available = TRUE;
        break;

      case MBP_ITEM_CHIPSET_INIT_VER:
        DestSize = sizeof (MbpPtr->MphyData);
        DestPtr = &MbpPtr->MphyData;
        break;

      case MBP_ITEM_ICC_PROFILE:
        DestSize = sizeof (MbpPtr->IccProfile);
        DestPtr = &MbpPtr->IccProfile;
        break;

      case MBP_ITEM_ID_MEASURED_BOOT:
        DestSize = sizeof (MbpPtr->MeasuredBootSupport.MeasuredBootData);
        DestPtr = &MbpPtr->MeasuredBootSupport.MeasuredBootData;
        MbpPtr->MeasuredBootSupport.Available = TRUE;
        break;

      case MBP_ITEM_DNX_IAFW_REQ:
        DestSize = sizeof(MbpPtr->IfwiDnxRequest);
        DestPtr = &MbpPtr->IfwiDnxRequest;
        MbpPtr->IfwiDnxRequest.Available = TRUE;
        break;
      //
      // Sensitive items
      //
      case MBP_ITEM_NVM_SMM_TRUSTED_CHANNEL:
        DestSize = sizeof (MbpSensitivePtr->TrustedChannel.Data);
        DestPtr = &MbpSensitivePtr->TrustedChannel.Data;
        MbpSensitivePtr->TrustedChannel.Available = TRUE;
        break;

      case MBP_ITEM_FW_BIOS_PLATFORM_KEY:
        DestSize = sizeof (MbpSensitivePtr->PlatformKey);
        DestPtr = &MbpSensitivePtr->PlatformKey;
        break;

      default:
        DEBUG ((DEBUG_WARN, "Unknown MBP Item %d header: %08x\n", CurrentMbpItem, MbpItemHeader->Data));
        MbpItemHeader += MbpItemHeader->Fields.Length;
        continue;
    }

    DEBUG ((DEBUG_INFO, "MBP Item %d header: %08x\n", CurrentMbpItem, MbpItemHeader->Data));
    if (MbpItemLength <= DestSize) {
      DEBUG_CODE (
        ShowBuffer (((UINT8*)(UINTN)(MbpItemHeader+1)), MbpItemLength);
      );
      CopyMem (DestPtr, (MbpItemHeader + 1), MbpItemLength);
    } else {
      DEBUG ((DEBUG_INFO, "Data size is larger than destination buffer. This item has not been copied.\n"));
    }
    MbpItemHeader += MbpItemHeader->Fields.Length;
  }

  //
  // Clear buffers from sensitive data
  //
  ZeroMem (MbpItems, MAX_MBP_ITEMS_SIZE);
  FreePool (MbpItems);
  DEBUG ((DEBUG_INFO, "HECI reset: clearing buffer from MBP Sensitive data.\n"));
  ResetHeciInterface (HECI1_DEVICE);

  return Status;
}

/**
  Install MbpData Hob.

  @retval     EFI_SUCCESS        The function completed successfully.
  @retval     EFI_UNSUPPORTED    MBP Hob creation skipped
  @retval     Others             Failed to create MBP Hob
**/
EFI_STATUS
InstallMbpHob (
  VOID
  )
{
  EFI_STATUS                          Status;
  ME_BIOS_PAYLOAD                     MbpData;
  ME_BIOS_PAYLOAD_SENSITIVE           MbpSensitiveData;
  ME_BIOS_PAYLOAD_HOB                 *MbpHob;
#if FixedPcdGetBool(PcdBfxEnable) == 1
  ME_BIOS_PAYLOAD_SENSITIVE_HOB       *MbpSensitiveDataHob;
#else
  EFI_PEI_PPI_DESCRIPTOR              *MbpSensitivePpiDesc;
  MBP_SENSITIVE_PPI                   *MbpSensitivePpi;
#endif

  if (MeTypeIsSps ()) {
    DEBUG ((DEBUG_INFO, "[SPS] Skip MBP initialization for SPS firmware\n"));
    return EFI_UNSUPPORTED;
  }

  DEBUG((DEBUG_INFO, "ME-BIOS: MBP Entry.\n"));
  PostCode (0xE02);

  PERF_START_EX (NULL, "EventRec", NULL, AsmReadTsc (), 0x8010);
  Status = PrepareMeBiosPayload (&MbpData, &MbpSensitiveData);
  PERF_END_EX (NULL, "EventRec", NULL, AsmReadTsc (), 0x8011);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ME-BIOS: MBP Exit - Get Mbp message has failed, Status: %r\n", Status));
    PostCode (0xE82);
    return EFI_DEVICE_ERROR;
  }

  if (!MeMbpHobSkipped ()) {
    ///
    /// Create MBP HOB
    ///
    Status = PeiServicesCreateHob (
               EFI_HOB_TYPE_GUID_EXTENSION,
               sizeof (ME_BIOS_PAYLOAD_HOB),
               (VOID**) &MbpHob
               );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "ME-BIOS: MBP Exit - MeBiosPayloadHob creation has failed, Status: %r\n", Status));
      PostCode (0xEA2);
      return Status;
    }

    //
    // Initialize MBP HOB
    //
    MbpHob->Header.Name   = gMeBiosPayloadHobGuid;
    MbpHob->Revision      = MBP_DATA_REVISION;
    CopyMem (&MbpHob->MeBiosPayload, &MbpData, sizeof (ME_BIOS_PAYLOAD));
    SyncMissingMbpItems (MbpHob);

#if FixedPcdGetBool(PcdBfxEnable) == 1
    ///
    /// Create the sensitive data MBP HOB
    ///
    Status = PeiServicesCreateHob (
               EFI_HOB_TYPE_GUID_EXTENSION,
               sizeof (ME_BIOS_PAYLOAD_SENSITIVE_HOB),
               (VOID **) &MbpSensitiveDataHob
               );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "MeBiosPayloadSensitiveDataHob could not be created.\n"));
      DEBUG ((
        DEBUG_ERROR,
        "ME-BIOS: MBP Exit - Error by MeBiosPayloadSensitiveDataHob create fail, Status: %r\n",
        Status
        ));
      PostCode (0xEA2);
      return Status;
    }
    //
    // Initialize MBP sensitive data HOB
    //
    MbpSensitiveDataHob->Header.Name = gMeBiosPayloadSensitiveDataHobGuid;
    MbpSensitiveDataHob->Revision    = MBP_DATA_REVISION;
    CopyMem (&MbpSensitiveDataHob->MeBiosPayloadSensitive, &MbpSensitiveData, sizeof (ME_BIOS_PAYLOAD_SENSITIVE));
    ZeroMem (&MbpSensitiveData, sizeof (ME_BIOS_PAYLOAD_SENSITIVE));


    DEBUG_CODE (
      PrintMbpData (MbpHob, MbpSensitiveDataHob);
    );
#else
    //
    // Initialize and install MBP sensitive data PPI
    //
    MbpSensitivePpi = (MBP_SENSITIVE_PPI *) AllocateZeroPool (sizeof (MBP_SENSITIVE_PPI));
    if (MbpSensitivePpi != NULL) {
      MbpSensitivePpi->Revision = MBP_SENSITIVE_PPI_REVISION;
      CopyMem (&MbpSensitivePpi->MbpSensitiveData, &MbpSensitiveData, sizeof (ME_BIOS_PAYLOAD_SENSITIVE));
      ZeroMem (&MbpSensitiveData, sizeof (ME_BIOS_PAYLOAD_SENSITIVE));

      MbpSensitivePpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
      if (MbpSensitivePpiDesc != NULL) {
        MbpSensitivePpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
        MbpSensitivePpiDesc->Guid  = &gMbpSensitivePpiGuid;
        MbpSensitivePpiDesc->Ppi   = (VOID *) MbpSensitivePpi;

        Status = PeiServicesInstallPpi (MbpSensitivePpiDesc);
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_ERROR, "ME-BIOS: MBP Exit - Error by MbpSensitivePpi install fail, Status: %r\n", Status));
          PostCode (0xEC2);
          return Status;
        }
      }
    }

    DEBUG_CODE (
      PrintMbpData (MbpHob, MbpSensitivePpi);
    );
#endif
  }

  DEBUG ((DEBUG_INFO, "ME-BIOS: MBP Exit - Success.\n"));
  PostCode (0xE22);
  return EFI_SUCCESS;
}


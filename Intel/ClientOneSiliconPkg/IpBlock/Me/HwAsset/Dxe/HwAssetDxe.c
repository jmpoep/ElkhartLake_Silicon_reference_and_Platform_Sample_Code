/** @file
  Hardware Asset Initialization driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include <Library/HobLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PerformanceLib.h>
#include <Library/PostCodeLib.h>
#include <Library/DxeMeLib.h>
#include <Library/DxeAmtHeciLib.h>
#include <Library/DxeAmtPolicyLib.h>
#include <Library/PmcPrivateLib.h>
#include <MeBiosPayloadHob.h>
#include <AsfMsgs.h>
#include "Inventory.h"

/**
  Constructs all asset tables and send them to FW

  @param[in]  IsMediaTablePushRequested Determines if CSME has requested Media Table in this boot

  @retval EFI_SUCCESS           Table sent
  @retval EFI_OUT_OF_RESOURCES  Unable to allocate necessary AssetTableData data structure.
  @retval Others                BIOS-ME communication error has occured
**/
EFI_STATUS
SendAssetTables2Firmware (
  IN BOOLEAN IsMediaTablePushRequested
  )
{
  HWA_TABLE   *AssetTablesData;
  EFI_STATUS  Status;
  UINT16      TableSize;

  AssetTablesData = AllocateZeroPool (sizeof (HWA_TABLE) + MAX_ASSET_TABLE_ALLOCATED_SIZE);
  if (AssetTablesData == NULL) {
    DEBUG ((DEBUG_WARN, "SendAssetTables2Firmware Error: Could not allocate Memory\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  TableSize = BuildHwaTable (AssetTablesData, IsMediaTablePushRequested);

  Status = HeciAssetUpdateFwMsg (AssetTablesData, TableSize);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_WARN, "SendAssetTables2Firmware Error: AssetUpdateFwMsg() returned Status %x\n", Status));
  }

  FreePool (AssetTablesData);

  return Status;
}


/**
  Signal an event for ready to boot.
**/
VOID
EFIAPI
HwAssetReadyToBootEvent (
  IN  EFI_EVENT                   Event,
  IN  VOID                        *Context
  )
{
  EFI_STATUS                                    Status;
  ME_BIOS_PAYLOAD_HOB                           *MbpHob;
  UINT8                                         PlatformBrand;
  BOOLEAN                                       WarmReset;
  BOOLEAN                                       SendTables;
  BOOLEAN                                       IsMediaTablePushRequested;

  DEBUG ((DEBUG_INFO, "HwAssetReadyToBootEvent enter\n"));
  MbpHob                    = NULL;
  IsMediaTablePushRequested = FALSE;

  //
  // Get the MBP Data.
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob == NULL) {
    DEBUG ((DEBUG_WARN, "MEBx: No MBP Data HOB available\n"));
    return;
  } else {
    PlatformBrand = (UINT8) MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.PlatformBrand;
    IsMediaTablePushRequested =  MbpHob->MeBiosPayload.HwaRequest.Available && (BOOLEAN) MbpHob->MeBiosPayload.HwaRequest.Data.Fields.MediaTablePush;
  }

  ///
  /// HW asset tables need to be sent when:
  /// - FW asked for it, or
  /// - FW is alive (brand!=0) and platform isn't booting from a warm reset unless it's first boot
  ///
  WarmReset = PmcIsMemoryPlacedInSelfRefreshState ();
  SendTables = IsMediaTablePushRequested || (PlatformBrand != NoBrand && !WarmReset);

  if (SendTables) {
    Status = SendAssetTables2Firmware (IsMediaTablePushRequested);
    DEBUG ((DEBUG_INFO, "Send Asset Tables to AMT FW - Status = %r\n", Status));
  }
}

/**
  The driver entry point - Hardware Asset Driver.

  @param[in] ImageHandle          Handle for this drivers loaded image protocol.
  @param[in] SystemTable          EFI system table.

  @retval EFI_SUCCESS             The driver installed without error.
  @retval EFI_UNSUPPORTED         The chipset is unsupported by this driver.
**/
EFI_STATUS
EFIAPI
HwAssetDriverEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS            Status;
  HECI_PROTOCOL         *Heci;
  UINT32                MeMode;
  EFI_EVENT             HwAssetEvent;

  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Heci->GetMeMode (&MeMode);
  if (MeMode != ME_MODE_NORMAL) {
    return EFI_UNSUPPORTED;
  }

  ///
  /// Create a Ready to Boot event.
  ///
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  HwAssetReadyToBootEvent,
                  (VOID *) &ImageHandle,
                  &gMePlatformReadyToBootGuid,
                  &HwAssetEvent
                  );

  ASSERT_EFI_ERROR (Status);
  return Status;
}

/** @file
  CPU feature control module

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

@par Specification
**/

#include <Library/CpuMailboxLib.h>
#include <Library/DebugLib.h>
#include <CpuPowerMgmt.h>

/**
  Get Address of Elixir Springs for a specific Elixir Springs Version

  @param[in] ElixirPatches     - Address of Elixir Springs Patches.
  @param[in] PatchSize         - Size of Elixir Springs Patches
  @param[in] ElixirVersion     - Version of Elixir Springs to patch.

  @retval VOID *               - Address of Elixir Springs Patch to be installed.
**/
VOID *
GetElixirPatch (
  IN VOID *ElixirPatches,
  IN UINT32 PatchesSize,
  IN UINT32 ElixirVersion
  )
{
/*
      Elixir Springs Patch Format:
        Bytes               Description
        [3:0]               Patch Revision Mask
        [7:4]               Patch Revision ID
        [11:8]              Patch size excluding header in DWORDS
        [12]                Data 0
        [13]                Address 0   - PCODE write Data 0 into Address 0.
        [14]                Data 1
        [15]                Address 1   - PCODE write Data 1 into Address 1.
        . . .
 */

  UINT8 *ElixirPatch = (UINT8*)ElixirPatches;
  UINT8 *EndOfPatches = ElixirPatch + PatchesSize;

  UINT32 PatchRevMask;
  UINT32 PatchRevId;
  INT32  PatchSize;

  while (ElixirPatch < EndOfPatches) {
    PatchRevMask = ((UINT32*)ElixirPatch)[0];
    PatchRevId   = ((UINT32*)ElixirPatch)[1];
    PatchSize    = ((UINT32*)ElixirPatch)[2] * sizeof (UINT32); // Convert size from dwords to bytes.

    if ((ElixirVersion & PatchRevMask) == PatchRevId) {
      return ElixirPatch;
    }

    ElixirPatch += PatchSize + 3 * sizeof (UINT32); //PatchSize doesn't include header, so add it too.
  }

  return NULL;
}

/**
  Get the Elixir Springs patch version needed from hardware.

  @param[in]  ElixirId    - Software ID of Elixir Springs Patch 0 or 1
  @param[out] VendorId    - Vendor ID
  @param[out] ProductId   - ProductId
  @param[out] ProductRev  - ProductRev
  @param[out] LotCode     - Lot code

  @retval UINT32          - = 0 if not patchable or hardware mailbox error.
  @retval UINT32          - > 0 Combination of Vendor ID, Product ID, Product Rev, and Lot Code.
**/
UINT32
GetRequiredElixirVersion (
  IN UINT32 ElixirId    OPTIONAL,
  OUT UINT8 *VendorId   OPTIONAL,
  OUT UINT8 *ProductId  OPTIONAL,
  OUT UINT8 *ProductRev OPTIONAL,
  OUT UINT8 *LotCode    OPTIONAL
  )
{
  EFI_STATUS Status;
  UINT32 MailboxCommand;
  UINT32 MailboxStatus;
  UINT32 MailboxData;
  UINT32 ElixirVersion = 0;
  UINT8  VrId;

  if (VendorId != NULL) {
    *VendorId = 0;
  }

  if (ProductId != NULL) {
    *ProductId = 0;
  }

  if (ProductRev != NULL) {
    *ProductRev = 0;
  }

  if (LotCode != NULL) {
    *LotCode = 0;
  }

  if (ElixirId > 1) {
    return 0; //Only 2 patches;
  }

  VrId = ElixirId ? SVID_REGISTER_VR_ID_VIRTUAL_1 : SVID_REGISTER_VR_ID_VIRTUAL_0;

  MailboxCommand = SVID_GET_REGISTER + (ELIXIR_VENDOR_ID_MAILBOX_ADDRESS << SVID_REGISTER_ADDR_OFFSET) + (VrId << SVID_REGISTER_VR_ID_OFFSET);
  Status = MailboxRead (MAILBOX_TYPE_PCODE, MailboxCommand, &MailboxData, &MailboxStatus);
  if (EFI_ERROR (Status) || EFI_ERROR (MailboxStatus)) {
    DEBUG ((DEBUG_ERROR, "Mailbox Command reading Elixir Springs Vendor ID failed. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    return 0;
  }

  if (VendorId != NULL) {
    *VendorId = (UINT8) MailboxData;
  }

  if (MailboxData != ELIXIR_VENDOR_ID_INTEL) {
    return 0;
  }

  ElixirVersion |= MailboxData << 24;

  MailboxCommand = SVID_GET_REGISTER + (ELIXIR_PRODUCT_ID_MAILBOX_ADDRESS << SVID_REGISTER_ADDR_OFFSET) + (VrId << SVID_REGISTER_VR_ID_OFFSET);
  Status = MailboxRead (MAILBOX_TYPE_PCODE, MailboxCommand, &MailboxData, &MailboxStatus);
  if (EFI_ERROR (Status) || EFI_ERROR (MailboxStatus)) {
    DEBUG ((DEBUG_ERROR, "Mailbox Command reading Elixir Springs Product ID failed. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    return 0;
  }

  ElixirVersion |= MailboxData << 16;
  if (ProductId != NULL) {
    *ProductId = (UINT8) MailboxData;
  }

  MailboxCommand = SVID_GET_REGISTER + (ELIXIR_PRODUCT_REV_MAILBOX_ADDRESS << SVID_REGISTER_ADDR_OFFSET) + (VrId << SVID_REGISTER_VR_ID_OFFSET);
  Status = MailboxRead (MAILBOX_TYPE_PCODE, MailboxCommand, &MailboxData, &MailboxStatus);
  if (EFI_ERROR (Status) || EFI_ERROR (MailboxStatus)) {
    DEBUG ((DEBUG_ERROR, "Mailbox Command reading Elixir Springs Product Revision failed. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    return 0;
  }

  ElixirVersion |= MailboxData << 8;
  if (ProductRev != NULL) {
    *ProductRev = (UINT8) MailboxData;
  }

  MailboxCommand = SVID_GET_REGISTER + (ELIXIR_LOT_CODE_MAILBOX_ADDRESS << SVID_REGISTER_ADDR_OFFSET) + (VrId << SVID_REGISTER_VR_ID_OFFSET);
  Status = MailboxRead (MAILBOX_TYPE_PCODE, MailboxCommand, &MailboxData, &MailboxStatus);
  if (EFI_ERROR (Status) || EFI_ERROR (MailboxStatus)) {
    DEBUG ((DEBUG_ERROR, "Mailbox Command reading Elixir Springs Lot Code failed. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    return 0;
  }
  ElixirVersion |= MailboxData;
  if (LotCode != NULL) {
    *LotCode = (UINT8) MailboxData;
  }

  return ElixirVersion;
}

/**
  Patch Elixir Springs with identified patch

  @param[in] ElixirPatch       - Address of Elixir Springs Patch.
  @param[in] ElixirId          - 0 or 1 for Elixir Springs Patch chip 0/1

  @retval EFI_SUCCESS          - Elixir Springs Patch installed.
  @retval EFI_DEVICE_ERROR     - Mailbox error
**/

EFI_STATUS
LoadElixirPatch (
  IN UINT8 *ElixirPatch,
  IN UINT32 ElixirId
  )
{
  EFI_STATUS Status;
  UINT32 MailboxCommand;
  UINT32 MailboxStatus;
  INT32  PatchSize;
  UINT8  VrId;

  if (ElixirId > 1) {
    return EFI_INVALID_PARAMETER; // Maximum of 2 elixir springs on a board
  }

  VrId = ElixirId ? SVID_REGISTER_VR_ID_VIRTUAL_1 : SVID_REGISTER_VR_ID_VIRTUAL_0;

  PatchSize = ((UINT32*)ElixirPatch)[2] * sizeof (UINT32); // Convert size from dwords to bytes.
  ElixirPatch += 3 * sizeof (UINT32); // Skip header

  while (PatchSize > 0) {
    UINT8 Data = *ElixirPatch++;
    UINT8 Address = *ElixirPatch++;

    MailboxCommand = SVID_SET_REGISTER + (Address << SVID_REGISTER_ADDR_OFFSET) + (VrId << SVID_REGISTER_VR_ID_OFFSET);
    Status = MailboxWrite (MAILBOX_TYPE_PCODE, MailboxCommand, Data, &MailboxStatus);
    if (EFI_ERROR (Status) || EFI_ERROR (MailboxStatus)) {
      DEBUG ((DEBUG_ERROR, "Mailbox Command to write patch failed. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
      return EFI_DEVICE_ERROR;
    }
    PatchSize -= 2;
  }

  return EFI_SUCCESS;
}

/**
  Patch Elixir Springs

  @param[in] ElixirPatches     - Address of Elixir Springs Patches.
  @param[in] PatchSize         - Size of Elixir Springs Patches

  @retval EFI_SUCCESS          - Elixir Springs Patch installed.
  @retval EFI_NOT_FOUND        - Elixir Springs Patch not found.
  @retval EFI_DEVICE_ERROR     - Mailbox error
**/

EFI_STATUS
ElixirSpringsPatchInit (
  IN VOID   *ElixirPatches,
  IN UINT32 PatchesSize
  )
{
  EFI_STATUS Status;
  UINT32 MailboxCommand;
  UINT32 MailboxStatus;

  VOID  *ElixirPatch;
  UINT32 ElixirVersion;
  UINT8  ProductId;

  BOOLEAN PatchLoaded = FALSE;

  if (ElixirPatches == NULL || PatchesSize == 0) {
    return EFI_NOT_FOUND;
  }

  ElixirVersion = GetRequiredElixirVersion (0, NULL, &ProductId, NULL, NULL);
  if (ElixirVersion == 0) {
    DEBUG ((DEBUG_INFO, "Elixir Patch not required.\n"));
    return EFI_SUCCESS;
  }

  ElixirPatch = GetElixirPatch (ElixirPatches, PatchesSize, ElixirVersion);
  if (ElixirPatch == NULL) {
    DEBUG ((DEBUG_INFO, "Elixir Patch version doesn't match binary.\n"));
    return EFI_NOT_FOUND;
  }

  MailboxCommand = SVID_SET_EXCLUSIVE;
  Status = MailboxWrite (MAILBOX_TYPE_PCODE, MailboxCommand, SVID_EXCLUSIVE_ENABLE, &MailboxStatus);
  if (EFI_ERROR (Status) || EFI_ERROR (MailboxStatus)) {
    DEBUG ((DEBUG_ERROR, "Mailbox Command to set Exclusive failed. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    return EFI_DEVICE_ERROR;
  }

  Status = LoadElixirPatch ((UINT8*)ElixirPatch, 0);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Elixir Patch didn't load.\n"));
  }
  PatchLoaded = !EFI_ERROR (Status);

  //
  // Some platforms will also have a second Elixir Spring's patch to load.
  //

  if (ProductId & 0x80) { // Load second patch
    ElixirVersion = GetRequiredElixirVersion (1, NULL, NULL, NULL, NULL);
    if (ElixirVersion == 0) {
      DEBUG ((DEBUG_INFO, "Elixir Second Patch not loaded.\n"));
      goto DisableExclusiveMode;
    }

    ElixirPatch = GetElixirPatch ((UINT8*)ElixirPatches, PatchesSize, ElixirVersion);
    if (ElixirPatch == NULL) {
      DEBUG ((DEBUG_INFO, "Elixir Second Patch version doesn't match binary.\n"));
      goto DisableExclusiveMode;
    }

    Status = LoadElixirPatch ((UINT8*)ElixirPatch, 1);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Elixir Second Patch didn't load.\n"));
    }
    if (PatchLoaded) PatchLoaded = !EFI_ERROR (Status); // First patch must also be loaded to set this flag.
  }

DisableExclusiveMode:
  Status = MailboxWrite (MAILBOX_TYPE_PCODE, MailboxCommand, SVID_EXCLUSIVE_DISABLE, &MailboxStatus);
  if (EFI_ERROR (Status) || EFI_ERROR (MailboxStatus)) {
    DEBUG ((DEBUG_ERROR, "Mailbox Command to disable exclusive failed. EFI_STATUS = %r, Mailbox Status = %X\n", Status, MailboxStatus));
    return Status;
  }

  return PatchLoaded ? EFI_SUCCESS : EFI_LOAD_ERROR;
}


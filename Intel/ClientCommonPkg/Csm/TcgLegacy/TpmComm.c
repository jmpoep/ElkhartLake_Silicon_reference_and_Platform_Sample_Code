/*++
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor.  This file may be modified by the user, subject to
  the additional terms of the license agreement
--*/
/** @file

  This module implements TCG INT1A feature.

Copyright (c) 2005 - 2016, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.


Module Name:

  TpmComm.c

Abstract:

  Utility functions used by TPM ReverseThunk driver

**/

#include <IndustryStandard/Tpm12.h>
#include <IndustryStandard/UefiTcgPlatform.h>
#include <Library/TpmCommLib.h>
#include <Library/BaseMemoryLib.h>

#include "TpmComm.h"

EFI_GUID                            gTcgEventEntryHob = {
  0x777dcf4b, 0x1d2a, 0x4680, {0xa6, 0x4c, 0x57, 0xb9, 0xa8, 0x82, 0x0, 0xa6}
};

/**
  Extend a TPM PCR.

  @param[in]  TpmHandle       TPM handle.
  @param[in]  DigestToExtend  The 160 bit value representing the event to be recorded.
  @param[in]  PcrIndex        The PCR to be updated.
  @param[out] NewPcrValue     New PCR value after extend.

  @retval EFI_SUCCESS         Operation completed successfully.
  @retval EFI_DEVICE_ERROR    The command was unsuccessful.

**/
EFI_STATUS
TpmCommExtend (
  IN      TIS_TPM_HANDLE            TpmHandle,
  IN      TPM_DIGEST                *DigestToExtend,
  IN      TPM_PCRINDEX              PcrIndex,
     OUT  TPM_DIGEST                *NewPcrValue
  )
{
  EFI_STATUS                        Status;
  TPM_DIGEST                        NewValue;
  TPM_RQU_COMMAND_HDR               CmdHdr;
  TPM_RSP_COMMAND_HDR               RspHdr;

  if (NewPcrValue == NULL) {
    NewPcrValue = &NewValue;
  }

  CmdHdr.tag = TPM_TAG_RQU_COMMAND;
  CmdHdr.paramSize =
    sizeof (CmdHdr) + sizeof (PcrIndex) + sizeof (*DigestToExtend);
  CmdHdr.ordinal = TPM_ORD_Extend;
  Status = TisPcExecute (
             TpmHandle,
             "%h%d%r%/%h%r",
             &CmdHdr,
             PcrIndex,
             DigestToExtend,
             (UINTN)sizeof (*DigestToExtend),
             &RspHdr,
             NewPcrValue,
             (UINTN)sizeof (*NewPcrValue)
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (RspHdr.returnCode != 0) {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}

/**
  Get TPM capability flags.

  @param[in]  TpmHandle    TPM handle.
  @param[in]  FlagSubcap   Flag subcap.
  @param[out] FlagBuffer   Pointer to the buffer for returned flag structure.
  @param[in]  FlagSize     Size of the buffer.

  @retval EFI_SUCCESS      Operation completed successfully.
  @retval EFI_DEVICE_ERROR The command was unsuccessful.

**/
EFI_STATUS
TpmCommGetFlags (
  IN      TIS_TPM_HANDLE            TpmHandle,
  IN      UINT32                    FlagSubcap,
     OUT  VOID                      *FlagBuffer,
  IN      UINTN                     FlagSize
  )
{
  EFI_STATUS                        Status;
  TPM_RQU_COMMAND_HDR               CmdHdr;
  TPM_RSP_COMMAND_HDR               RspHdr;
  UINT32                            Size;

  CmdHdr.tag = TPM_TAG_RQU_COMMAND;
  CmdHdr.paramSize = sizeof (CmdHdr) + sizeof (UINT32) * 3;
  CmdHdr.ordinal = TPM_ORD_GetCapability;

  Status = TisPcExecute (
             TpmHandle,
             "%h%d%d%d%/%h%d%r",
             &CmdHdr,
             TPM_CAP_FLAG,
             sizeof (FlagSubcap),
             FlagSubcap,
             &RspHdr,
             &Size,
             FlagBuffer,
             FlagSize
             );
  if (EFI_ERROR (Status)) {
    return Status;
  }
  if (RspHdr.returnCode != 0) {
    return EFI_DEVICE_ERROR;
  }
  return EFI_SUCCESS;
}

/**
  Add a new entry to the Event Log.

  @param[in, out] EventLogPtr   Pointer to the Event Log data.
  @param[in, out] LogSize       Size of the Event Log.
  @param[in]      MaxSize       Maximum size of the Event Log.
  @param[in]      NewEventHdr   Pointer to a TCG_PCR_EVENT_HDR data structure.
  @param[in]      NewEventData  Pointer to the new event data.

  @retval EFI_SUCCESS           The new event log entry was added.
  @retval EFI_OUT_OF_RESOURCES  No enough memory to log the new event.

**/
EFI_STATUS
TpmCommLogEvent (
  IN OUT  UINT8                     **EventLogPtr,
  IN OUT  UINTN                     *LogSize,
  IN      UINTN                     MaxSize,
  IN      TCG_PCR_EVENT_HDR         *NewEventHdr,
  IN      UINT8                     *NewEventData
  )
{
  UINT32                            NewLogSize;

  NewLogSize = sizeof (*NewEventHdr) + NewEventHdr->EventSize;
  if (NewLogSize + *LogSize > MaxSize) {
    return EFI_OUT_OF_RESOURCES;
  }

  *EventLogPtr += *LogSize;
  *LogSize += NewLogSize;
  CopyMem (*EventLogPtr, NewEventHdr, sizeof (*NewEventHdr));
  CopyMem (
    *EventLogPtr + sizeof (*NewEventHdr),
    NewEventData,
    NewEventHdr->EventSize
    );
  return EFI_SUCCESS;
}

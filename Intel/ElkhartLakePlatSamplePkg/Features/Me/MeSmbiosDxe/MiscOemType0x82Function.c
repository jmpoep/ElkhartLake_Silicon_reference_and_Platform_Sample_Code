/**@file
  Type 130: AMT-Specific SMBIOS Structure.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#include "MeSmbios.h"
#include <SetupVariable.h>
#include <MebxDataHob.h>
#include <Library/HobLib.h>

#define SECURE_ERASE_OEM_CAPABILIY BIT6

/**
  This function makes boot time changes to the contents of the MiscOemType0x82Data.

  @param[in] RecordType          Type of record to be processed from the Data Table.
                                 mMiscSubclassDataTable[].RecordType
  @param[in] RecordLen           pointer to the size of static RecordData from the Data Table.
                                 mMiscSubclassDataTable[].RecordLen
  @param[in] RecordData          Pointer to copy of RecordData from the Data Table.  Changes made
                                 to this copy will be written to the Data Hub but will not alter
                                 the contents of the static Data Table.
  @param[in] LogRecordData       Set *LogRecordData to TRUE to log RecordData to Data Hub.
                                 Set *LogRecordData to FALSE when there is no more data to log.

  @retval EFI_SUCCESS            All parameters were valid and *RecordData and *LogRecordData have been set.
  @retval EFI_UNSUPPORTED        Unexpected RecordType value.
  @retval EFI_INVALID_PARAMETER  One of the following parameter conditions was true:
                                    RecordLen was NULL.
                                    RecordData was NULL.
                                    LogRecordData was NULL.
**/
MISC_SUBCLASS_TABLE_FUNCTION (MiscOemType0x82)
{
  EFI_STATUS                                Status;
  ME_CAP                                    MeCapabilities;
  UINT32                                    MeMode;
  HECI_PROTOCOL                             *Heci;
  EFI_HOB_GUID_TYPE                         *GuidHob;
  MEBX_DATA_HOB                             MebxData;

  ZeroMem (&MebxData, sizeof (MEBX_DATA_HOB));
  GuidHob = GetFirstGuidHob (&gAmtMebxDataGuid);
  if (GuidHob != NULL) {
    CopyMem (&MebxData, GET_GUID_HOB_DATA (GuidHob), sizeof (MEBX_DATA_HOB));
  }

  //
  // First check for invalid parameters.
  //
  if ((RecordLen == NULL) || (RecordData == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // Then check for unsupported RecordType.
  //
  if (RecordType != MISC_OEM_TYPE_0x82_RECORD_NUMBER) {
    return EFI_UNSUPPORTED;
  }

  DEBUG ((DEBUG_INFO, "MiscOemType0x82 entry \n"));

  //
  // Yes, this is the first time.  Inspect/Change the contents of the
  // RecordData structure.
  //
  // Locate HECI protocol to use it for ME info, HECI messaging
  // If HECI not found register callback for it to update data
  //
  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID**) &Heci
                  );
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "HECI protocol not found! \n"));
    return Status;
  }

  ZeroMem (&MeCapabilities, sizeof (ME_CAP));
  Heci->GetMeMode (&MeMode);
  if (MeMode == ME_MODE_NORMAL) {
    Status = MbpGetMeFwInfo (&MeCapabilities);
  }

  if (MeCapabilities.IntelAmtFw == 1) {
    ((MISC_OEM_TYPE_0x82*)RecordData)->AmtSupported = 1;
    ((MISC_OEM_TYPE_0x82*)RecordData)->SrouEnabled = 1;     // If AMT supported, SRoU is always enabled
  } else {
    ((MISC_OEM_TYPE_0x82*)RecordData)->AmtSupported = 0;
    ((MISC_OEM_TYPE_0x82*)RecordData)->SrouEnabled = 0;
  }

  if (MeCapabilities.IntelAmtFw == 1) {
    ((MISC_OEM_TYPE_0x82*)RecordData)->AmtEnabled = MebxData.PlatformMngSel;
    ((MISC_OEM_TYPE_0x82*)RecordData)->SolEnabled = MebxData.AmtSol;
    ((MISC_OEM_TYPE_0x82*)RecordData)->NetworkEnabled = 1;  // If AMT enabled, LAN is always enabled
  }

  if (MeCapabilities.IntelKVM) {
    ((MISC_OEM_TYPE_0x82*)RecordData)->KvmEnabled = MebxData.KvmEnable;
  }


  DEBUG ((DEBUG_INFO, "MiscOemType0x82 exit \n"));

  return EFI_SUCCESS;
}

/* eof - MiscOemType0x82Function.c */

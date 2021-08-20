/** @file
  This file Extends CSME Configuration to PCR[1].

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include "MeExtMeasurement.h"
#include "MeExtConfig.h"

/**
  Ready To Boot Event call back function performs getting AMT Config data from CSME and extending to TPM-PCR[1]

  @param[in] Event         The event that triggered this notification function
  @param[in] Context       Pointer to the notification functions context
**/
VOID
EFIAPI
AmtConfigReadyToBootEvent (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS                  Status;
  AMT_CONFIG_DATA             AmtConfigData;
  PROV_DATA_STATE             AmtConfigProvState;
  UINT32                      AmtConfigSize;
  BIOS_REDIRECTION_SETTINGS   AmtConfigRedirSetting;
  ADMIN_SETUP_AUDIT_RECORD    AmtConfigProvAuditRecord;
  INTEL_ME_CONFIG_DATA        MeAmtEventConfigData;
  static CONST CHAR8          Signature[] = "IntelCSMEAmtConfig";

  gBS->CloseEvent (Event);

  ZeroMem (&(MeAmtEventConfigData.Signature), sizeof (MeAmtEventConfigData.Signature));
  CopyMem (&(MeAmtEventConfigData.Signature), Signature, AsciiStrLen (Signature));
  MeAmtEventConfigData.DataLength = AMT_CONFIG_RECORD_LENGTH;

  //
  // Get AMT Config from CSME
  //
  AmtConfigSize = sizeof (PROV_DATA_STATE);
  Status = HeciReadFileExMsg (MCA_AMT_PROV_STATE_FILE_ID, 0, &AmtConfigSize, 0, (UINT8 *) &AmtConfigProvState);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to read  AMT Provision state file, Status is %r \n", Status));
    ASSERT_EFI_ERROR (Status);
    return;
  }

  //
  // Get BIOS redirection settings from CSME
  //
  AmtConfigSize = sizeof (BIOS_REDIRECTION_SETTINGS);
  Status = HeciReadFileExMsg (MCA_AMT_BIOS_REDIR_FILE_ID, 0, &AmtConfigSize, 0, (UINT8 *) &AmtConfigRedirSetting);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to read  AMT Provision state file, Status is %r \n", Status));
    ASSERT_EFI_ERROR (Status);
    return;
  }

  //
  // Fill AMT Status in the structure 'AmtConfigData' as per file read data
  //
  AmtConfigData.AmtStatus.AmtGloballyEnabled  = (AmtConfigProvState.Bits.AmtGloballyEnabled == 1) ? 1 : 0;
  AmtConfigData.AmtStatus.MebxPwdSet          = (AmtConfigProvState.Bits.MebxPwdChanged == 1) ? 1 : 0;
  AmtConfigData.AmtStatus.AmtProvisioned      = (AmtConfigProvState.Bits.ProvisioningState == 1) ? 1 : 0;
  AmtConfigData.AmtStatus.AmtProvisioningMode = (AmtConfigProvState.Bits.ClientControlMode == 1) ? 1 : 0;
  AmtConfigData.AmtStatus.ZtcEnabled          = (AmtConfigProvState.Bits.ZTCEnabled == 1) ? 1 : 0;

  AmtConfigData.AmtStatus.KvmEnabled          = (AmtConfigRedirSetting.KvmHostIf == 1) ? 1 : 0;
  AmtConfigData.AmtStatus.SolEnabled          = (AmtConfigRedirSetting.SolHostIf == 1) ? 1 : 0;
  AmtConfigData.AmtStatus.UsbrEnabled         = (AmtConfigRedirSetting.IderHostIf == 1) ? 1 : 0;

  //
  // Get Secure PKI DNS Suffix from CSME only if AmtStatus bit0 is set
  //
  if (AmtConfigData.AmtStatus.AmtGloballyEnabled == 1) {
    AmtConfigSize = SECURE_PKI_DNS_SUFFIX_LENGTH;
    Status = HeciReadFileExMsg (MCA_AMT_SEC_PKI_FILE_ID, 0, &AmtConfigSize, 0, (UINT8 *) AmtConfigData.SecPkiDnsSfx);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to read Secure PKI DNS Suffix file, Status is %r \n", Status));
      ASSERT_EFI_ERROR (Status);
      return;
    }
  }

  //
  // Get AMT provisioning audit record from CSME only if AmtStatus bit2 & bit3 are set
  //
  if ((AmtConfigData.AmtStatus.AmtProvisioned == 1) && (AmtConfigData.AmtStatus.AmtProvisioningMode == 1)) {
    AmtConfigSize = sizeof (ADMIN_SETUP_AUDIT_RECORD);
    Status = HeciReadFileExMsg (MCA_AMT_PROV_ADT_REC_FILE_ID, 0, &AmtConfigSize, 0, (UINT8 *) &AmtConfigProvAuditRecord);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to read  AMT Provision state file, Status is %r \n", Status));
      ASSERT_EFI_ERROR (Status);
      return;
    }
    //
    // Fill PKI Provisioning leaf Certificate hash Algorithm & Finger print hash in the structure 'AmtConfigData' as per file read data
    //
    AmtConfigData.PkiProvLeafCertHashAlgm = (UINT32) AmtConfigProvAuditRecord.LeafHashAlgorithm;
    CopyMem (AmtConfigData.PkiProvLeafCertHashFingerPrint, AmtConfigProvAuditRecord.LeafCertFingerprint, PKI_PROV_LEAF_CERT_HASH_FINGERPRINT_LENGTH);
  }

  // Copy AMT Config Data to ME Event Config data structure
  CopyMem (MeAmtEventConfigData.ConfigData, &AmtConfigData, AMT_CONFIG_RECORD_LENGTH);

  //
  // Extend AMT Config data to TPM PCR[1] & Event log to TPM log
  //
  Status = TpmMeasureAndLogData (
             1,
             EV_NONHOST_CONFIG,
             &MeAmtEventConfigData,
             sizeof (INTEL_ME_CONFIG_DATA),
             &MeAmtEventConfigData,
             sizeof (INTEL_ME_CONFIG_DATA)
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed AMT Config data to TPM-PCR[1]\n"));
    ASSERT_EFI_ERROR (Status);
  }

  return;
}

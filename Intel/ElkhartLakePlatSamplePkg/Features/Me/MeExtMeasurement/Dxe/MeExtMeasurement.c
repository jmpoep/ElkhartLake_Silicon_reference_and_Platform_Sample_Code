/** @file
  CSME Extended Measurement driver.

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

/**
  Perform measurement for HER register.

  @param[in] HerValue             The value of HECI Extend Register.
  @param[in] Index                HerValue Size.

  @retval EFI_SUCCESS             Measurement performed
**/
EFI_STATUS
MeasureHer (
  IN  UINT32                      *HerValue,
  IN  UINT8                       Index
  )
{
  EFI_STATUS              Status;
  UINT32                  Hers;
  UINTN                   HashDataLen;
  UINT8                   *TempEvent;
  UINT32                  EventLogSize;
  UINT8                   LogEntryIndex;
  UINT8                   RemainingEntries;
  UINT32                  RemainingBufSize;
  UINT32                  ReceivedLogSize;
  CSME_MEASUREMENT_EVENT  CsmeEvent;
  static CONST CHAR8      Signature[] = "IntelCSxEEvent01";

  ///
  /// Get ER Log using BUP_COMMON_GET_ER_LOG and pass that log to Tpm Measurement
  ///
  ZeroMem (&CsmeEvent, sizeof (CsmeEvent));
  CopyMem (&(CsmeEvent.Signature), Signature, AsciiStrLen (Signature));

  ///
  /// Read HER Status register value
  ///
  Hers = PciRead32(PCI_LIB_ADDRESS(ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HERS));
  if ((Hers & B_ME_EXTEND_REG_ALGORITHM) == V_ME_SHA_256) {
    CsmeEvent.ERHashAlgorithm = V_ME_SHA_256;
  } else if ((Hers & B_ME_EXTEND_REG_ALGORITHM) == V_ME_SHA_384) {
    CsmeEvent.ERHashAlgorithm = V_ME_SHA_384;
  }

  EventLogSize = 0;
  RemainingBufSize = MAX_EVENTLOG_SIZE;
  ReceivedLogSize = 0;
  LogEntryIndex = 0;
  TempEvent = CsmeEvent.Events;

  do {
    RemainingEntries = 0;
    Status = HeciGetErLog (
               TempEvent,
               RemainingBufSize,
               &ReceivedLogSize,
               &LogEntryIndex,
               &RemainingEntries);
    if (EFI_ERROR (Status)) {
        DEBUG((DEBUG_INFO, "Failed to get ER Log data\n"));
        return Status;
    }

    EventLogSize += ReceivedLogSize;
    if (RemainingEntries) {
      if (EventLogSize >= MAX_EVENTLOG_SIZE) {
        DEBUG((DEBUG_INFO, "Event Log is exceeding the Maximum allocated buffer\n"));
        return EFI_BUFFER_TOO_SMALL;
      }

      TempEvent += (ReceivedLogSize + 1);
      LogEntryIndex++;
      RemainingBufSize = MAX_EVENTLOG_SIZE - EventLogSize;
    }
  } while (RemainingEntries != 0);

  EventLogSize += sizeof (CsmeEvent.Signature) + sizeof (CsmeEvent.ERHashAlgorithm);
  HashDataLen = (Index * sizeof (UINT32));
  //
  // Measure to PCR[0] with event EV_NONHOST_INFO
  //
  Status = TpmMeasureAndLogData (
             0,
             EV_NONHOST_INFO,
             &CsmeEvent,
             EventLogSize,   // Actual received event log size + signature length + Algorithm size
             HerValue,
             HashDataLen
             );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Get Extended Measurement data from CSME Extended registers.

  @param[in] Her               Pointer to receive HER Data buffer
  @param[in] HashAlgorithm     Hash Algorithm
  @param[in] HerMaxRegCount    DWord registers count which has Hash data

  @retval EFI_SUCCESS             Successfully read Measurement data
  @retval EFI_INVALID_PARAMETER   Input parameters are not valid
  @retval EFI_UNSUPPORTED         Unsupported Hash Algorithm
**/
EFI_STATUS
HeciGetHerData (
  IN UINT32    *Her,
  IN UINT8     HashAlgorithm,
  IN UINT8     HerMaxRegCount
  )
{
  EFI_STATUS    Status = EFI_SUCCESS;
  UINT32        HerOffset;
  UINT8         Index;

  if ((Her == NULL) || (HashAlgorithm == 0) || (HerMaxRegCount == 0)) {
    DEBUG ((DEBUG_ERROR, "HeciGetHerData: Invalid parameter\n"));
    return EFI_INVALID_PARAMETER;
  }

  HerOffset = (UINT32) R_ME_HER1;

  switch (HashAlgorithm) {
    case V_ME_SHA_256:
      ///
      /// Read HER data from PCI Config space 0xC0 - 0xDF (R_ME_HER1 - R_ME_HER8)
      ///
      for (Index = 0; Index < HerMaxRegCount; Index++) {
        *Her = PciRead32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, (HerOffset + (Index * sizeof (UINT32))) ));
        Her++;
      }
      break;

  case V_ME_SHA_384:
    ///
    /// Read HER data from MMIO space 0xCC0 - 0xCDF (HECI1_HER1 - HECI1_HER12)
    ///
    HerOffset += R_HER_BASE;
    Status = HeciGetHerDataSha384 (Her, HerOffset, HerMaxRegCount);
    break;

  default:
    DEBUG ((DEBUG_ERROR, "HeciGetHerData: Failed to get CSME Measurement data\n"));
    Status = EFI_UNSUPPORTED;
    break;
  }

  return Status;
}

/**
  End of DXE CallBack event to extend CSME Measurment to TPM-PCR[0] & AMT Config data to TPM-PCR[1]

  @param[in] Event      The event that triggered this notification function
  @param[in] Context    Pointer to the notification functions context

**/
VOID
EFIAPI
ExtendCsmeMeasurementToTpmPcr (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS    Status;
  UINT32        Her [HER_REG_COUNT_SHA384];
  UINT32        Hers;
  UINT8         HashAlgorithm;
  UINT8         HerMaxRegCount;

  gBS->CloseEvent (Event);

  ///
  /// Read HER Status register value
  ///
  Hers = PciRead32 (PCI_LIB_ADDRESS (ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HERS));
  if ((Hers & B_ME_EXTEND_REG_VALID) != B_ME_EXTEND_REG_VALID) {
    DEBUG ((DEBUG_INFO, "CSME-HER data is not available to Extend to TPM-PCR\n"));
    return;
  }

  if (Hers & B_ME_EXTEND_FEAT_PRESENT) {
    if ((Hers & B_ME_EXTEND_COMPLETE) != B_ME_EXTEND_COMPLETE) {
      DEBUG ((DEBUG_INFO, "CSME Extend Measurement is not Complete\n"));
      return;
    }
  }

  ZeroMem (&Her, sizeof (Her));
  HashAlgorithm = 0;
  HerMaxRegCount = 0;

  if ((Hers & B_ME_EXTEND_REG_ALGORITHM) == V_ME_SHA_256) {
    HashAlgorithm = V_ME_SHA_256;
    HerMaxRegCount = (UINT8) HER_REG_COUNT_SHA256;
  } else if ((Hers & B_ME_EXTEND_REG_ALGORITHM) == V_ME_SHA_384) {
    HashAlgorithm = V_ME_SHA_384;
    HerMaxRegCount = (UINT8) HER_REG_COUNT_SHA384;
  }

  Status = HeciGetHerData (Her, HashAlgorithm, HerMaxRegCount);
  if (!EFI_ERROR (Status)) {
    Status = MeasureHer (Her, HerMaxRegCount);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Extending ME Measurement to TPM-PCR0 failed, Status is %r \n", Status));
    }
  }

}

/**
  Entry point for Me Extended Measurement driver

  @param[in] ImageHandle          Standard entry point parameter.
  @param[in] SystemTable          Standard entry point parameter.

  @retval EFI_UNSUPPORTED         ME policy library initialization failure.
  @retval Others                  Status code returned by CreateEventEx.
**/
EFI_STATUS
EFIAPI
MeExtMeasurementEntryPoint (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  EFI_STATUS              Status;
  BOOLEAN                 HostSetupMbEnabled;
  BOOLEAN                 CsmeMbState;
  MEFWCAPS_SKU            MeFwCapsSku;
  BOOLEAN                 IsAmtSupport;
  UINT8                   SetMeasureBoot;
  UINT8                   GetMeasureBoot;
  EFI_EVENT               Event;
  ME_BIOS_PAYLOAD_HOB     *MbpHob;
  AMT_PEI_CONFIG          *AmtPeiConfig;
  EFI_PEI_HOB_POINTERS    HobPtr;

  //
  // Read MBP Table and check for CSME Measured Boot Support (MBP_ITEM_ID_MEASURED_BOOT  Bit 0) & AMT Support (MBP_KERNEL_FW_CAPS_ITEM Bit 2)
  //
  Status = EFI_SUCCESS;
  MbpHob = NULL;
  CsmeMbState = FALSE;
  IsAmtSupport = FALSE;
  HostSetupMbEnabled = FALSE;
  AmtPeiConfig = NULL;

  //
  // Get Mbp Data HOB
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob == NULL) {
    DEBUG ((DEBUG_ERROR, "MeExtMeasurementEntryPoint: Mbp Hob not found\n"));
    return EFI_NOT_FOUND;
  }

  if (MbpHob->MeBiosPayload.MeasuredBootSupport.Available == TRUE) {
    CsmeMbState = (MbpHob->MeBiosPayload.MeasuredBootSupport.MeasuredBootData.MeasuredBoot == 1) ? TRUE : FALSE;
  } else {
    DEBUG ((DEBUG_ERROR, "MeExtMeasurementEntryPoint: Csme not supported Measured Boot\n"));
    return EFI_UNSUPPORTED;
  }

  if (MbpHob->MeBiosPayload.FwCapsSku.Available == TRUE) {
    MeFwCapsSku.Data = MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Data;
    IsAmtSupport = (MeFwCapsSku.Fields.Amt == 1) ? TRUE : FALSE;
  }

  HobPtr.Guid = GetFirstGuidHob (&gAmtPolicyHobGuid);
  if (HobPtr.Guid != NULL) {
    AmtPeiConfig = (AMT_PEI_CONFIG *) GET_GUID_HOB_DATA (HobPtr.Guid);
    if (AmtPeiConfig->AmtEnabled == 0) {
      DEBUG ((DEBUG_INFO, "MeExtMeasurementEntryPoint: BIOS - AMT Policy is not Enabled\n"));
    }
    //
    // If AMT is supported, then get AMT Config data from CSME and push to TPM-PCR[1]
    //
    if ((AmtPeiConfig->AmtEnabled == 1) && (IsAmtSupport == TRUE)) {
      DEBUG ((DEBUG_INFO, "AMT is supported, push AMT Config to TPM-PCR[1]\n"));

      ///
      /// Create a Ready to Boot event.
      ///
      Status = EfiCreateEventReadyToBootEx (
                 TPL_CALLBACK,
                 AmtConfigReadyToBootEvent,
                 (VOID *) &ImageHandle,
                 &Event
                 );
      ASSERT_EFI_ERROR (Status);
    }
  }

  //
  // Get BIOS Setup value for Extended CSME Measurement
  //
  HostSetupMbEnabled = IsExtendedMeasuredBootEnabled ();

  //
  // 1. If Measured Boot is enabled on both CSME & Host side then register End of DXE event to extend CSME Measurement from ER Registers to TPM-PCR[0]
  // 2. Else if Host side Measured Boot is not in sync with CSME Side Measurement Boot, then Send MEI Command to CSME to enable/disable as per Host
  //    side Measured Boot State.
  //    Note: If CSME enables Measured Boot then issue Global reset to capture Measured data in next restart,
  //          else if CSME disables Measured Boot then No need to issue Global reset as Host is not going to update TPM PCR.
  // 3. If Measured Boot is disabled on both CSME & Host side then No action is required continue to Boot.
  //
  if ((CsmeMbState & HostSetupMbEnabled) == TRUE) {
    //
    // Extend CSME Measured data to TPM PCR[0]
    //
    DEBUG ((DEBUG_INFO, "Register End Of Dxe event to extended CSME Measured data to TPM-PCR[0]\n"));
    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    ExtendCsmeMeasurementToTpmPcr,
                    NULL,
                    &gEfiEndOfDxeEventGroupGuid,
                    &Event
                    );
    ASSERT_EFI_ERROR(Status);

  } else if (CsmeMbState != HostSetupMbEnabled) {
    if (HostSetupMbEnabled == TRUE) {
      //
      // Send Command to CSME to enable Extended Measured boot
      // Issue Global Reset
      //
      DEBUG ((DEBUG_INFO, "Send CSME command to Enable Measured Boot\n"));
      SetMeasureBoot = 1;
      Status = HeciSetMeasuredBootState (SetMeasureBoot);
      if (!EFI_ERROR (Status)) {
        GetMeasureBoot = 0;
        Status = HeciGetMeasuredBootState (&GetMeasureBoot);
        if (!EFI_ERROR (Status) && (GetMeasureBoot == 1)) {
          // CSME Successfully enabled Measured Boot. Issue Global Reset
          DEBUG ((DEBUG_INFO, "CSME Successfully Enable Measured Boot, Issuing Global Reset\n"));
          HeciSendCbmResetRequest (CBM_RR_REQ_ORIGIN_BIOS_POST, CBM_HRR_GLOBAL_RESET);
          CpuDeadLoop ();
        } else {
          DEBUG ((DEBUG_INFO, "CSME failed to HeciGetMeasuredBootState\n"));
        }
      } else {
        DEBUG ((DEBUG_INFO, "CSME failed for HeciSetMeasuredBootState to enable MB\n"));
      }
    } else {
      //
      // Send Command to CSME to disable Extended Measured boot
      // Not required to issue Global reset as no Measured data to be updated
      //
      DEBUG ((DEBUG_INFO, "Send CSME command to Disable Measured Boot\n"));
      SetMeasureBoot = 0;
      Status = HeciSetMeasuredBootState (SetMeasureBoot);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_INFO, "CSME failed for HeciSetMeasuredBootState to disable MB\n"));
      }
    }
  } else {
    //
    // MbCsmeSupport & MbHostSetupEnabled are FALSE that means Measured Boot is disabled on both CSME & Host side.
    // Continue to Boot
    //
    DEBUG ((DEBUG_INFO, "Extended CSME Measured Boot is disabled on both CSME & Host side, NO Action required, Continue to boot...\n"));
  }

  DEBUG ((DEBUG_INFO, "ME-Extended Measurement: Exit - Success.\n"));

  return Status;
}

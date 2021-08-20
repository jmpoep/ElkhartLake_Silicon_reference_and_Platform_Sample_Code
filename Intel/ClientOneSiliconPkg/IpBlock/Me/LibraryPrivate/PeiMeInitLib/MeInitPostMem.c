/** @file
  The PEI Library Implements ME Init.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include "MbpData.h"
#include "HeciInit.h"
#include <Library/DebugLib.h>
#include <Register/MeRegs.h>
#include <Library/PeiServicesLib.h>
#include <Library/HobLib.h>
#include <MeBiosPayloadHob.h>
#include <Library/PeiMeLib.h>
#include <MeFwHob.h>
#include <Library/PciSegmentLib.h>
#include <Library/HeciInitLib.h>
#include <Library/MeShowBufferLib.h>
#include <Library/BaseMemoryLib.h>
#include <AmtConfig.h>
#include <Library/MeFwStsLib.h>
#include <Library/PsfLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/PeiItssLib.h>
#include <Register/HeciRegs.h>
#include <Library/TimerLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/BootMediaLib.h>

/**
  Query if ME operation mode is Temp Disable mode.

  @retval TRUE            ME is in Temp Disable mode.
  @retval FALSE           ME is not in Temp Disable mode.
**/
BOOLEAN
IsMeInTempDisabledMode (
  VOID
  )
{
  HECI_FWS_REGISTER        MeFirmwareStatus;
  UINTN                    Timeout;
  UINT64                   HeciBaseAddress;

  HeciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, 0);
  if (PciSegmentRead16 (HeciBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    return FALSE;
  }

  Timeout = MSG_MAX_WAIT_TIMEOUT;

  do {
    ///
    /// Read ME status and check for operation mode
    ///
    MeFirmwareStatus.ul = PciSegmentRead32 (HeciBaseAddress + R_ME_HFS);
    if (MeFirmwareStatus.r.MeOperationMode == ME_OPERATION_MODE_SOFT_TEMP_DISABLE) {
      return TRUE;
    }

    MicroSecondDelay (ME_STATE_STALL_1_SECOND);
    Timeout--;
  } while (Timeout > 0);

  DEBUG ((DEBUG_ERROR, "Timeout: ME not in temp disabled mode after 5s. MeFirmwareStatus: %08x.\n", MeFirmwareStatus.ul));
  return FALSE;
}

/**
  Check if MCTP (Management Component Transport) Protocol is supported by CSME and BIOS.

  @param[in] MbpHob                   Pointer to MbpHob
  @param[in] MePeiConfig              Pointer to ME PEI Config

  @retval    TRUE                     MCTP is supported by CSME or BIOS
  @retval    FALSE                    MCTP is not supported by CSME or BIOS
**/
BOOLEAN
IsMctpConfigurationSupported (
  IN ME_BIOS_PAYLOAD_HOB *MbpHob,
  IN ME_PEI_CONFIG       *MePeiConfig
  )
{
  EFI_STATUS             Status;
  MEFWCAPS_SKU           FwCapsSku;

  if (MePeiConfig->MctpBroadcastCycle == 0) {
    return FALSE;
  }

  if (MbpHob != NULL) {
    if ((MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.Amt == 1) &&
        (MbpHob->MeBiosPayload.FwFeaturesState.FwFeatures.Fields.FullMng == 1))
      return TRUE;
  } else {
    ///
    /// When MBP is not available, we need to retrieve Feature Capabilities and State from CSME
    ///
    Status = PeiHeciGetFwCapsSkuMsg (&FwCapsSku);
    if (!EFI_ERROR (Status) && FwCapsSku.Fields.Amt == 1) {
      Status = PeiHeciGetFwFeatureStateMsg (&FwCapsSku);
      if (!EFI_ERROR (Status) && FwCapsSku.Fields.FullMng == 1) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
  Save FWSTS to ME FWSTS HOB, if the HOB is not existing, the HOB will be created and publish.
  If the HOB is existing, the data will be overrided.
**/
VOID
SaveFwStsToHob (
  VOID
  )
{
  ME_FW_HOB       *MeFwHob;
  UINT8           Index;
  UINT8           Count;
  EFI_STATUS      Status;

  MeFwHob = GetFirstGuidHob (&gMeFwHobGuid);
  if (MeFwHob == NULL) {
    ///
    /// Create HOB for ME Data
    ///
    Status = PeiServicesCreateHob (
               EFI_HOB_TYPE_GUID_EXTENSION,
               sizeof (ME_FW_HOB),
               (VOID **) &MeFwHob
               );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return;
    }

    DEBUG ((DEBUG_INFO, "ME FW HOB installed\n"));

    //
    // Initialize default HOB data
    //
    ZeroMem (&(MeFwHob->Revision), (sizeof (ME_FW_HOB) - sizeof (EFI_HOB_GUID_TYPE)));
    MeFwHob->EfiHobGuidType.Name = gMeFwHobGuid;
    MeFwHob->Revision = 1;
    MeFwHob->Count = GetMeFwStsDeviceCount ();
  }

  DEBUG ((DEBUG_INFO, "ME FW HOB data updated\n"));
  ///
  /// Save the FWSTS registers set for each MEI device.
  ///
  for (Count = 0; Count < GetMeFwStsDeviceCount (); Count++) {
    for (Index = 0; Index < GetMeFwStsOffsetCount (); Index++) {
      MeFwHob->Group[Count].Reg[Index] = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, (UINT32)gFwStsDeviceList[Count].HeciDev, gFwStsOffsetTable[Index]));
    }
    MeFwHob->Group[Count].FunNumber = (UINT32)gFwStsDeviceList[Count].HeciDev;
  }

  DEBUG_CODE_BEGIN ();
  DEBUG ((DEBUG_INFO, "Current ME FW HOB data printed - \n"));
  ShowBuffer ((UINT8 *) MeFwHob, sizeof (ME_FW_HOB));
  DEBUG_CODE_END ();
}

/**
  Save all policies in PEI phase to HOB.
**/
VOID
SavePolicyToHob (
  VOID
  )
{
  EFI_STATUS                Status;
  SI_POLICY_PPI             *SiPolicyPpi;
  SI_PREMEM_POLICY_PPI      *SiPreMemPolicyPpi;
  ME_PEI_PREMEM_CONFIG      *MePeiPreMemConfig;
  ME_PEI_CONFIG             *MePeiConfig;
#if FixedPcdGetBool(PcdAmtEnable) == 1
  AMT_PEI_CONFIG            *AmtPeiConfig;
#endif
  UINTN                     HobSize;
  VOID                      *HobPtr;

  SiPreMemPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  SiPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gMePeiConfigGuid, (VOID *) &MePeiConfig);
  ASSERT_EFI_ERROR (Status);

#if FixedPcdGetBool(PcdAmtEnable) == 1
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gAmtPeiConfigGuid, (VOID *) &AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);
#endif

  //
  // Create ME/AMT HOBs.
  //
  HobSize = MePeiPreMemConfig->Header.GuidHob.Header.HobLength;
  DEBUG ((DEBUG_INFO, "HobSize for MePeiPreMemConfig: %x\n", HobSize));
  HobPtr = BuildGuidDataHob (&gMePreMemPolicyHobGuid, MePeiPreMemConfig, HobSize);
  ASSERT (HobPtr != 0);

  HobSize = MePeiConfig->Header.GuidHob.Header.HobLength;
  DEBUG ((DEBUG_INFO, "HobSize for MePeiConfig: %x\n", HobSize));
  HobPtr = BuildGuidDataHob (&gMePolicyHobGuid, MePeiConfig, HobSize);
  ASSERT (HobPtr != 0);

#if FixedPcdGetBool(PcdAmtEnable) == 1
  HobSize = AmtPeiConfig->Header.GuidHob.Header.HobLength;
  DEBUG ((DEBUG_INFO, "HobSize for AmtPeiConfig: %x\n", HobSize));
  HobPtr = BuildGuidDataHob (&gAmtPolicyHobGuid, AmtPeiConfig, HobSize);
  ASSERT (HobPtr != 0);
#endif

}

/**
  Disable ME Devices when needed

  @param[in] HeciPpi                  The pointer with Heci Ppi
  @param[in] IntegratedTouchEnabled   The boolean value indicates IntegratedTouchEnabled should be enabled
                                      through MbpHob or via MePolicyPpi set by previous POST boot for S3 boot path
**/
VOID
MeDeviceConfigure (
  IN BOOLEAN                      IntegratedTouchEnabled
  )
{
  EFI_STATUS                      Status;
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  ME_PEI_PREMEM_CONFIG            *MePeiPreMemConfig;
  ME_BIOS_BOOT_PATH               MeBiosPath;
  ME_DEV_EXPOSURE                 MeDeviceExposure;
  UINT64                          DevicePciCfgBase;
#if FixedPcdGetBool(PcdAmtEnable) == 1
  SI_POLICY_PPI                   *SiPolicy;
  AMT_PEI_CONFIG                  *AmtPeiConfig;
#endif

  DEBUG ((DEBUG_INFO, "MeDeviceConfigure () - Start\n"));

  ///
  /// Step 1. Determine which devices should be hidden depending on specific Me-Boot Path
  ///
  MeDeviceExposure = GetBootPathMeDevHidePolicy ();

  ///
  /// Step 2. Perform device disabling based on FW capability and feature state
  ///         in all boot mode if it is not listed by ME Bios Boot path.
  ///         Policy can only control device disabling when the device is not
  ///         specified to be disabled by any non MeNormalBiosPath.
  ///

  ///
  /// 2-a. Disable HECI2 with CSME in all boot mode - already in MeBiosPath.
  ///
  //
  // Disable Heci2 if and only if policy dictates
  //
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gMePeiPreMemConfigGuid, (VOID *) &MePeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  if (!EFI_ERROR (Status)) {
    if (!MeHeci2Enabled ()) {
      MeDeviceExposure |= HIDE_MEI2;
    }
  }

  ///
  /// 2-b. Disable Heci3 when no Integrated Touch support
  ///
  if (!IntegratedTouchEnabled) {
    MeDeviceExposure |= HIDE_MEI3;
  }

#if FixedPcdGetBool(PcdAmtEnable) == 1
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicy
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Get SiPolicy fail\n"));
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPolicy, &gAmtPeiConfigGuid, (VOID *) &AmtPeiConfig);
  ASSERT_EFI_ERROR (Status);
  //
  // Since P2SB lock in EndOfPei phase, move all SOL disable check here.
  //
  if (AmtPeiConfig->AmtSolEnabled == 0) {
    MeDeviceExposure |= HIDE_SOL;
  }
#else
  MeDeviceExposure |= HIDE_SOL;
#endif

  ///
  /// Step 3. Perform checking for specific boot mode with ME Bios Boot Path,
  ///         like MeDisableSecoverMeiMsgBiosPath. HECI1 shall be disabled
  ///         after HMRFPO_DISABLE_MSG sent in previous POST boot path
  ///
  if (GetBootModeHob () == BOOT_ON_S3_RESUME) {
    MeBiosPath = CheckMeBootPath ();
    if ((MeBiosPath == SecoverMeiMsgPath) || (MeBiosPath == SwTempDisablePath) || (MeBiosPath == SecoverJmprPath)) {
      MeDeviceExposure |= HIDE_MEI1;
    }
  }

  ///
  /// Save MEI FWSTS registers set before disable it. The MEI device access right will be removed
  /// by late POST, hence save current FWSTS before disable them for reference without further enabling
  /// MEI steps required. The HOB data might be updated if gets failure when send EOP message in PEI
  /// phase, then FWSTS registers will be updated to reflect the last status before disable rest MEI devices
  ///
  SaveFwStsToHob ();

  if ((MeDeviceExposure & HIDE_MEI1)) {
    HeciDisable ();
  }
  if ((MeDeviceExposure & HIDE_MEI2)) {
    Heci2Disable ();
  }
  if ((MeDeviceExposure & HIDE_MEI3)) {
    Heci3Disable ();
  }

  ///
  /// Always disable IDE-r with CSME in all boot mode.
  ///


  if (MePeiPreMemConfig->HeciCommunication4 == FORCE_DISABLE) {

  ///
  /// HECI4 interface is not used and should be disabled by following below steps:
  ///  1. Temporary initialize HECI4 memory (program BAR, set MSE)
  ///  2. Set D0i3 bit in HECI4 memory space
  ///  3. Clear BAR and Command register
  ///  4. Disable device on PSF
  ///
  MeDeviceInit (HECI4, PcdGet32 (PcdSiliconInitTempMemBaseAddr), 0);

  SetD0I3Bit ((UINT32) HECI4);
  ///
  /// Clear BAR and CMD register
  ///
  DevicePciCfgBase = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI4, 0);
  PciSegmentAnd8 (DevicePciCfgBase + PCI_COMMAND_OFFSET, (UINT8)~(EFI_PCI_COMMAND_MEMORY_SPACE | EFI_PCI_COMMAND_BUS_MASTER));
  PciSegmentWrite32 (DevicePciCfgBase + PCI_BASE_ADDRESSREG_OFFSET, 0);

  PsfDisableHeciDevice (4);
  DEBUG ((DEBUG_INFO, "Disabling CSME device 0:22:%d\n", (UINT8) HECI4));
  }
}

/**
  Send Optional Heci Command.
**/
VOID
SendOptionalHeciCommand (
  VOID
  )
{
  EFI_STATUS                Status;
  SI_POLICY_PPI             *SiPolicyPpi;
  ME_PEI_CONFIG             *MePeiConfig;
  ME_BIOS_PAYLOAD_HOB       *MbpHob;
  UINT32                    UnconfigOnRtcClear = 0;

  DEBUG ((DEBUG_INFO, "SendOptionalHeciCommand\n"));

  SiPolicyPpi = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Locate gSiPolicyPpiGuid fail. Status = %r\n", Status));
    return;
  }
  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gMePeiConfigGuid, (VOID *) &MePeiConfig);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Get ME PeiConfigBlock fail, Status = %r\n", Status));
    return;
  }

  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
  if (MbpHob != NULL) {
    DEBUG ((DEBUG_INFO, "MbpHob NOT NULL\n"));

    if (MbpHob->MeBiosPayload.UnconfigOnRtcClearState.Available == 1) {
      UnconfigOnRtcClear = MbpHob->MeBiosPayload.UnconfigOnRtcClearState.UnconfigOnRtcClearData.DisUnconfigOnRtcClearState;
      if ((MePeiConfig->MeUnconfigOnRtcClear == 1) && (UnconfigOnRtcClear == DisableState)) {
        UnconfigOnRtcClear = EnableState;
        Status = PeiHeciSetUnconfigOnRtcClearDisableMsg (UnconfigOnRtcClear);
      } else if ((MePeiConfig->MeUnconfigOnRtcClear == 0) && (UnconfigOnRtcClear == EnableState)) {
        UnconfigOnRtcClear = DisableState;
        Status = PeiHeciSetUnconfigOnRtcClearDisableMsg (UnconfigOnRtcClear);
      }
    }
  }

  return;
}


/**
  Configure HECI devices on End Of Pei
**/
VOID
MeOnEndOfPei (
  VOID
  )
{
  UINT32               HeciBars[PCI_MAX_BAR];
  UINT8                MeDevFunction;

  DEBUG ((DEBUG_INFO, "MeOnEndOfPei\n"));

  if (GetBootModeHob () == BOOT_ON_S3_RESUME) {
    if (MeHeciD0I3Enabled () == FALSE) {
      return;
    }

    //
    // Set D0I3 bits if resuming from S3.
    // We have to make sure the HECI BARs are 32-bit here after restoring S3 boot script:
    //  1. Save MMIO BAR addresses for all HECI devices.
    //  2. Set to default (32-bit) BAR addresses for all HECI devices.
    //  3. Set D0i3 bit
    //  4. Restore MMIO BAR addresses for all HECI devices.
    //
    DEBUG ((DEBUG_INFO, "Setting D0I3 bits for HECI devices on S3 resume path\n"));
    for (MeDevFunction = HECI1; MeDevFunction <= HECI4; MeDevFunction++) {
      if (!IsHeciDeviceFunction (MeDevFunction)) {
        continue;
      }
      MeSaveBars (MeDevFunction, HeciBars);
      MeDeviceInit (MeDevFunction, MeGetHeciBarAddress (MeDevFunction), 0);
      SetD0I3Bit (MeDevFunction);
      MeRestoreBars (MeDevFunction, HeciBars);
    }
  } else {

    //
    // Send optional HECI command
    //
    if (!BootMediaIsUfs ()) {
      SendOptionalHeciCommand ();
    }

    //
    // Save ME/AMT policies in PEI phase to HOB for using in DXE.
    //
    SavePolicyToHob ();
  }

  DEBUG ((DEBUG_INFO, "MeOnEndOfPei done.\n"));
}

/**
 Configure ME device interrupts

 @param[in] SiPolicy      The Silicon Policy PPI instance
 @param[in] MeDev         The CSME device to be configured.
**/
VOID
MeDeviceConfigureInterrupts (
  IN CONST SI_POLICY_PPI  *SiPolicy,
  IN ME_DEVICE            MeDev
  )
{
  UINT64      PciBaseAddress;
  UINT8       FunctionNum;
  UINT8       InterruptPin;

  FunctionNum = HECI_FUNCTION_NUMBER + (UINT8)MeDev;

  PciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, FunctionNum, 0);

  if (PciSegmentRead16 (PciBaseAddress + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    return;
  }

  //
  // Configure ME device interrupts
  //
  InterruptPin = ItssGetDevIntPin (SiPolicy, ME_DEVICE_NUMBER, FunctionNum);

  switch (MeDev) {
    case HECI1:
    case HECI2:
    case HECI3:
    case HECI4:
    case IDER:
      PciSegmentWrite8 (PciBaseAddress + PCI_INT_PIN_OFFSET, InterruptPin);
      break;
  }
}

/**
  This function performs basic initialization for ME in PEI phase after memory is initialized.

  @param[in] SiPolicy     The Silicon Policy PPI instance

**/
VOID
EFIAPI
MePostMemInit (
  IN  SI_POLICY_PPI  *SiPolicy
  )
{
  EFI_STATUS                Status;
  ME_BIOS_PAYLOAD_HOB       *MbpHob;
  ME_PEI_CONFIG             *MePeiConfig;
  BOOLEAN                   IsIntegratedTouchEnabled;
  UINT8                     MeDevFunction;

  DEBUG ((DEBUG_INFO, "MePostMemInit() - Start\n"));

  Status = GetConfigBlock ((VOID *) SiPolicy, &gMePeiConfigGuid, (VOID *) &MePeiConfig);
  ASSERT_EFI_ERROR (Status);

  MbpHob = NULL;
  IsIntegratedTouchEnabled = FALSE;

  ///
  /// Install Mbp in POST Mem unless it's S3 resume boot. If MbpHob exists, reflect IntegratedTouch state
  /// from Mbp directly. Otherwise, refer to MePolicy, which contains previous POST boot status of IntegratedTouch.
  /// The IntegratedTouch status was retrieved via Mbp and saved in DXE phase by platform code, then passed to
  /// next S3/Error/Recovery boot path via SiPolicy. Platform should ensure the state is updated based on current
  /// IntegratedTouch status. Even if the current path is not S3/Error/Recovery bios boot path the following MeDeviceConfigure ()
  /// function may still disable IntegratedTouch device(MEI3) based on current ME Bios boot path requirement.
  ///
  if (GetBootModeHob () != BOOT_ON_S3_RESUME) {
    Status = InstallMbpHob ();
    if (!EFI_ERROR (Status)) {
      MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);
      if (MbpHob != NULL) {
        IsIntegratedTouchEnabled = !!MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Fields.IntegratedTouch;
      }
    }
  } else {
    if (MePeiConfig->Heci3Enabled == 1) {
      IsIntegratedTouchEnabled = TRUE;
    }
  }

  //
  // Configure CSME devices
  //
  MeDeviceConfigure (IsIntegratedTouchEnabled);
  if (IsMctpConfigurationSupported (MbpHob, MePeiConfig)) {
    PsfConfigureMctpCycle ();
  }

  //
  // Configure interrupts for CSME devices
  //
  for (MeDevFunction = HECI1; MeDevFunction <= HECI3; MeDevFunction++) {
    if ((MeDevFunction == IDER ) | (MeDevFunction == SOL )) {
      continue;
    }
    MeDeviceConfigureInterrupts (SiPolicy, MeDevFunction);
  }

  DEBUG ((DEBUG_INFO, "MePostMemInit() - End\n"));
  return;
}

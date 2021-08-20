/** @file
  This file contains the tests for the SecuePchConfiguration bit

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#include "HstiIhvDxe.h"
#include <Register/RtcRegs.h>

/**
  Check PCH P2SB SMM Unexpected Status.

  @param[in] Result - Secure Pch Configuration Tests Result

  @retval TRUE   Error Detected.
  @retval FALSE  Error Not Detected.
**/
BOOLEAN
SecurePchP2sbSmmConfiguration (
  VOID
  )
{
  EFI_STATUS                    Status;
  BOOLEAN                       Result;
  UINT32                        PchP2sbSmmResults;
  UINTN                         DataSize;

  PchP2sbSmmResults  = 0;
  Result = TRUE;

  // Get Pch Smm Unexpected Status Information
  DataSize = sizeof (PchP2sbSmmResults);
  Status = gRT->GetVariable (
                  L"SecurePchSmmVariableName",
                  &gHstiSmmVariableGuid,
                  NULL,
                  &DataSize,
                  &PchP2sbSmmResults
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "Unable to get PCH Smm Unexpected Status Variable\n"));
    return Result;
  }

  DEBUG ((DEBUG_INFO, "      P2sb Remove Access EPMASK5 Mask Configuration Test\n"));

  if (P2sbEpMask5RemAccMaskBits29To26UnexpSts & PchP2sbSmmResults) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: EPMASK5 Mask is not configured (P2SB SMM)\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_CODE_1,
      HSTI_PCH_SMM_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_STRING_1
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      P2sb Remove Access EPMASK7 Mask Configuration Test\n"));

  if (P2sbEpMask7RemAccMaskBits31To30UnexpSts & PchP2sbSmmResults) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: EPMASK7 Mask is not configured (P2SB SMM)\n"));
    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_CODE_2,
      HSTI_PCH_SMM_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_STRING_2
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      P2SB Mask Lock Bit Test\n"));

  if (P2sbLockMaskBitUnexpSts & PchP2sbSmmResults) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: P2SB Mask bit Unlocked (P2SB SMM)\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_CODE_3,
      HSTI_PCH_SMM_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_PCH_SMM_CONFIGURATION_UNEXP_STATUS_STRING_3
      );
    Result = FALSE;
  }

  return Result;
}

/**
  Check Secure PCH Acs Ech Configuration

  @param[in] Result - Secure Pch Configuration Tests Result

  @retval TRUE   Error Detected.
  @retval FALSE  Error Not Detected.
**/
BOOLEAN
SecurePchAcsEchPortsConfiguration (
  VOID
  )
{
  EFI_STATUS              Status;
  BOOLEAN                 Result;
  UINT64                  RpPcieBase          = 0;
  UINT32                  AcsEchPortRegValue  = 0;
  UINTN                   MaxPcieRootPorts    = 0;
  UINT32                  RpIndex             = 0;
  UINTN                   RpDev               = 0;
  UINTN                   RpFun               = 0;

  Result = TRUE;
  // For each port Verify ACS ECH Value is Correctly Configured
  DEBUG ((DEBUG_INFO, "      Root Port(s) ACS ECH Capability Enabled and Correct Configuration Test\n"));

  MaxPcieRootPorts = GetPchMaxPciePortNum ();

  for (RpIndex = 0; RpIndex < MaxPcieRootPorts; RpIndex++) {
    Status = GetPchPcieRpDevFun (RpIndex, &RpDev, &RpFun);
    if (EFI_ERROR (Status)){
      DEBUG ((DEBUG_INFO, "      RpIndex%d is invalid\n", RpIndex));
      ASSERT_EFI_ERROR (Status);
      continue;
    }

    // Check if End Port Device is used
    RpPcieBase = PchPcieBase (RpIndex);
    if (PciSegmentRead16 (RpPcieBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
      DEBUG ((DEBUG_INFO, "        INFO: Port Register Base Address (RpIndex = %d) = 0x%x not used\n", RpIndex, RpPcieBase));
      continue;
    } else {
      DEBUG ((DEBUG_INFO, "        Root Port Register Base Address  (RpIndex = %d) = 0x%x used\n", RpIndex, RpPcieBase));
    }

    // Verify ACS ECH Root Port (index) Capability is Enabled and Configured
    AcsEchPortRegValue = PciSegmentRead32 (RpPcieBase + R_PCH_PCIE_CFG_EX_ACSECH);
    if (!((AcsEchPortRegValue & (V_PCH_PCIE_CFG_EX_ACS_CV << N_PCIE_EXCAP_CV)) &&
         ((AcsEchPortRegValue & V_PCIE_EX_ACS_CID) == V_PCIE_EX_ACS_CID))) {
      DEBUG ((DEBUG_INFO, "          Unexpected Status: ACS feature is not Enabled or ACS ECH is incorrectly Configured = 0x%x\n", AcsEchPortRegValue));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_5,
        HSTI_PCH_SMM_SECURITY_CONFIGURATION,
        HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_5
        );
      Result = FALSE;
    }
  }

  return Result;
}

/**
  Run tests for SecurePCHConfiguration bit
**/
VOID
CheckSecurePchConfiguration (
  VOID
  )
{

  EFI_STATUS      Status;
  BOOLEAN         Result;
  BOOLEAN         ThermalTl;
  BOOLEAN         ThermalEctrl;
  BOOLEAN         ThermalPhl;
  BOOLEAN         ThermalPtl;

  if ((mFeatureImplemented[1] & HSTI_BYTE1_SECURE_PCH_CONFIGURATION) == 0) {
    return;
  }

  Result = TRUE;

  DEBUG ((DEBUG_INFO, "      Thermal Throttling Locks Test\n"));
  ThermalTl    = ThermalIsThrottleLock ();
  ThermalEctrl = ThermalIsEcThermalReportLock ();
  ThermalPhl   = ThermalIsPchHotLock ();
  ThermalPtl   = ThermalIsPmcThrottleLock ();

  if ((ThermalTl    == FALSE) &&
      (ThermalEctrl == FALSE) &&
      (ThermalPhl   == FALSE) &&
      (ThermalPtl   == FALSE)) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: One or more of the Thermal Locks bits are disabled\n"));
    DEBUG ((DEBUG_INFO, "          TLLOCK = %x\n", ThermalTl));
    DEBUG ((DEBUG_INFO, "          ECRPTENLOCK = %x\n", ThermalEctrl));
    DEBUG ((DEBUG_INFO, "          PHLCLOCK = %x\n", ThermalPhl));
    DEBUG ((DEBUG_INFO, "          TLENLOCK = %x\n", ThermalPtl));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_1,
      HSTI_PCH_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_1
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      Set Strap Lock Test\n"));
  if (PmcIsSetStrapMsgInterfaceLocked () == FALSE) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: Strap Lock set to 0\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_2,
      HSTI_PCH_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_2
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      PM CFG Debug Lock Test\n"));

  if (PmcIsDebugModeLocked () == FALSE) {
    DEBUG((DEBUG_INFO, "        Unexpected Status: Debug Mode set to 0\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_3,
      HSTI_PCH_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_3
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      SMI Enable Test\n"));

  if (PmcIsGblSmiEn () == FALSE) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: Global SMI is Disabled\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_D,
      HSTI_PCH_SECURITY_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_D
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      SMI Lock Test\n"));

  if (PmcIsSmiLockSet () == FALSE) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: Global SMI is Unlocked\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_D,
      HSTI_PCH_SECURITY_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_D
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      TCO SMI Lock Test\n"));

  if (TcoIsSmiLock () == FALSE) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: TCO SMI is not Locked\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_E,
      HSTI_PCH_SECURITY_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_E
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      RTC Bios Interface Lock Test\n"));

  if (RtcIsBiosInterfaceLock () == FALSE) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: RTC BILD is not Locked\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_CODE_4,
      HSTI_PCH_SECURITY_CONFIGURATION,
      HSTI_BYTE0_BOOT_FIRMWARE_MEDIA_PROTECTION_UNEXP_STATUS_STRING_4
      );
  }


  DEBUG ((DEBUG_INFO, "      SPD Configuration and Write Protection Test\n"));

  if (SmbusIsHostLocked () == FALSE) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: SPD is not Write Protected\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_4,
      HSTI_PROCESSOR_SPD_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_4
      );
    Result = FALSE;
  }

  // PCH P2SB SMM Test
  if (SecurePchP2sbSmmConfiguration () == FALSE) {
    Result = FALSE;
  }

  // PCH Acs Ech Ports Test
  if (SecurePchAcsEchPortsConfiguration () == FALSE) {
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      VR CONFIG Lock Test\n"));

  if (PmcIsFivrConfigLocked () == FALSE) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: VR CONFIG Bit is Unlocked\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_CODE_6,
      HSTI_PCH_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_PCH_CONFIGURATION_UNEXP_STATUS_STRING_6
      );
    Result = FALSE;
  }

  //
  // ALL PASS
  //
  if (Result) {
    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               1,
               HSTI_BYTE1_SECURE_PCH_CONFIGURATION
               );
    CheckStatusForHstiLibSet (Status);
  }

  return;
}

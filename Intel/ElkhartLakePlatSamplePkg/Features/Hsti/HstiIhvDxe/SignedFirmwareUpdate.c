/** @file
  This file contains the tests for the SignedFirmwareUpdate bit

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

/**
  Run tests for SignedFirmwareUpdate bit
**/
VOID
CheckSignedFirmwareUpdate (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOLEAN         Result;
  UINTN           CpuNumber;
  UINTN           CpuIndex;
  UINT64          PlatformInfo;
  UINT64          PlatFrmwProtCtrl;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE) == 0) {
    return;
  }

  Result = TRUE;

  DEBUG ((DEBUG_INFO, "    BIOS Guard Security per CPU Number Tests\n"));

  CpuNumber = GetCpuNumber ();
  for (CpuIndex = 0; CpuIndex < CpuNumber; CpuIndex++) {
    DEBUG ((DEBUG_INFO, "    [CPU - 0x%x]\n", CpuIndex));

    DEBUG ((DEBUG_INFO, "      BIOS Guard support Test\n"));

    PlatformInfo = ProcessorReadMsr64 (CpuIndex, MSR_PLATFORM_INFO);
    if ((PlatformInfo & B_MSR_PLATFORM_INFO_PFAT_ENABLE_MASK) == 0) {
      DEBUG ((DEBUG_INFO, "        Unexpected Status: BIOS Guard not supported\n"));

      BuildAndAppendHstiStatusString (
         HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_CODE_1,
         HSTI_BIOS_GUARD_SECURITY_CONFIGURATION,
         HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_STRING_1
         );
      Result = FALSE;
    } else {
      DEBUG ((DEBUG_INFO, "      BIOS Guard Lock Test\n"));

      PlatFrmwProtCtrl = ProcessorReadMsr64 (CpuIndex, MSR_PLAT_FRMW_PROT_CTRL);
      if ((PlatFrmwProtCtrl & B_MSR_PLAT_FRMW_PROT_CTRL_PFAT_LOCK_MASK) == 0) {
        DEBUG ((DEBUG_INFO, "        Unexpected Status: BIOS Guard lock not set\n"));


        BuildAndAppendHstiStatusString (
           HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_CODE_2,
           HSTI_BIOS_GUARD_SECURITY_CONFIGURATION,
           HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_STRING_2
           );
        Result = FALSE;
      }

      DEBUG ((DEBUG_INFO, "      BIOS Guard Enable Test\n"));

      if ((PlatFrmwProtCtrl & B_MSR_PLAT_FRMW_PROT_CTRL_PFAT_ENABLE_MASK) == 0) {
        DEBUG ((DEBUG_INFO, "        Unexpected Status: BIOS Guard not enabled\n"));


        BuildAndAppendHstiStatusString (
           HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_CODE_3,
           HSTI_BIOS_GUARD_SECURITY_CONFIGURATION,
           HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE_UNEXP_STATUS_STRING_3
           );
        Result = FALSE;
      }
    }
  }

  //
  // ALL PASS
  //
  if (Result) {
    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               0,
               HSTI_BYTE0_SIGNED_FIRMWARE_UPDATE
               );
    CheckStatusForHstiLibSet (Status);
  }

  return;
}

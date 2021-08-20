/** @file
  This file contains the tests for the SecureDebugInterfaceConfiguration Bit

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

typedef union {
  struct {
    UINT32  Low;
    UINT32  High;
  } Data32;
  UINT64 Data;
} UINT64_STRUCT;

/**
  Run tests for SecureDebugInterfaceConfiguration bit
**/
VOID
CheckSecureDebugInterfaceConfiguration (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOLEAN         Result;
  UINT32          RegEcx;
  UINT32          OpiCtrl;
  UINT64_STRUCT   DmiBar;
  CPU_FAMILY      CpuFamilyId;
  MSR_IA32_DEBUG_INTERFACE_REGISTER  DebugInterfaceReg;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_CONFIGURATION) == 0) {
    return;
  }

  Result = TRUE;

  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &RegEcx, NULL);

  if ((RegEcx & BIT11) != 0) {

    DebugInterfaceReg.Uint64 =  AsmReadMsr64 (MSR_IA32_DEBUG_INTERFACE);

    DEBUG ((DEBUG_INFO, "      Debug Interface Disabled\n"));

    if (DebugInterfaceReg.Bits.Enable) {
      DEBUG ((DEBUG_INFO, "        Unexpected Status: Debug Interface Enabled\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_CODE_1,
        HSTI_CPU_SECURITY_CONFIGURATION,
        HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_STRING_1
        );
      Result = FALSE;
    }

    DEBUG ((DEBUG_INFO, "      Debug Interface Locked Test\n"));

    if (!(DebugInterfaceReg.Bits.Lock)) {
      DEBUG ((DEBUG_INFO, "        Unexpected Status: Debug interface is not locked\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_CODE_2,
        HSTI_CPU_SECURITY_CONFIGURATION,
        HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_STRING_2
        );
      Result = FALSE;
    }
  }

  // Get CPU Family ID to determine Link (OPI vs DMI) and U/Y SKUs
  CpuFamilyId = GetCpuFamily ();
  DEBUG ((DEBUG_INFO, "      OPI Debug Interface Lockdown Test (only applicable for U/Y Production SKUs)\n"));
  if (!IsPchLinkDmi (CpuFamilyId)) {
    DmiBar.Data32.High = PciSegmentRead32 (
                           PCI_SEGMENT_LIB_ADDRESS(
                             SA_SEG_NUM,
                             SA_MC_BUS,
                             SA_MC_DEV,
                             SA_MC_FUN,
                             R_SA_DMIBAR + 4)
                           );
    DmiBar.Data32.Low  = PciSegmentRead32 (
                           PCI_SEGMENT_LIB_ADDRESS(
                             SA_SEG_NUM,
                             SA_MC_BUS,
                             SA_MC_DEV,
                             SA_MC_FUN,
                             R_SA_DMIBAR)
                           );
    DmiBar.Data       &= (UINT64) ~BIT0;
    OpiCtrl            = MmioRead32 ((UINTN)(DmiBar.Data + R_SA_DMIBAR_OPIO_PHY_CONTROL));

    // This test is valid only applicable for U/Y Revenue SKUs, checking Revenue vs. Pre-production part
    if (MmioRead32 (TXT_PUBLIC_BASE + 0x200) & BIT31) {

      if ((OpiCtrl & BIT26) == 0) {
        DEBUG ((DEBUG_INFO, "        Unexpected Status: OPI Debug interface is not locked\n"));

        BuildAndAppendHstiStatusString (
          HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_CODE_3,
          HSTI_DEBUG_INTERFACE_SECURITY_CONFIGURATION,
          HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_UNEXP_STATUS_STRING_3
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
               HSTI_BYTE0_DEBUG_INTERFACE_SECURITY_CONFIGURATION
               );
   CheckStatusForHstiLibSet (Status);
  }

  return;
}

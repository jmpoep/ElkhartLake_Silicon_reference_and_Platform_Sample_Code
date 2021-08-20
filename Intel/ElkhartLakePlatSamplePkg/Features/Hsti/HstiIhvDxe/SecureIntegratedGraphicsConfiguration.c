/** @file
  This file contains the tests for the SecureIntegratedGraphics bit

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
  Run tests for SecureIntegratedGraphicsConfiguration bit
**/
VOID
CheckSecureIntegratedGraphicsConfiguration (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOLEAN         Result;
  UINT16          Ggc;
  UINT32          Pavpc;
  UINT32          Bdsm;
  UINT32          Bgsm;
  UINT32          Tolud;
  UINT32          GsmSize;
  UINT32          DsmSize;
  UINT32          PcmBase;
  UINT32          IgdVendorId;

  //
  // Read Integrated Graphics Device
  //
  IgdVendorId = PciSegmentRead32 (
                  PCI_SEGMENT_LIB_ADDRESS (
                    SA_SEG_NUM,
                    SA_IGD_BUS,
                    SA_IGD_DEV,
                    SA_IGD_FUN_0,
                    R_SA_IGD_VID)
                  );

  if (((mFeatureImplemented[1] & HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION) == 0) ||
      (IgdVendorId == B_IGD_VENDOR_DID_MASK))  {
    return;
  }

  Result = TRUE;

  Ggc   = PciSegmentRead16 (
            PCI_SEGMENT_LIB_ADDRESS (
              SA_SEG_NUM,
              SA_MC_BUS,
              SA_MC_DEV,
              SA_MC_FUN,
              R_SA_GGC)
            );
  Pavpc = PciSegmentRead32 (
            PCI_SEGMENT_LIB_ADDRESS (
              SA_SEG_NUM,
              SA_MC_BUS,
              SA_MC_DEV,
              SA_MC_FUN,
              R_SA_PAVPC)
            );
  Bdsm  = PciSegmentRead32 (
            PCI_SEGMENT_LIB_ADDRESS (
              SA_SEG_NUM,
              SA_MC_BUS,
              SA_MC_DEV,
              SA_MC_FUN,
              R_SA_BDSM)
            );
  Bgsm  = PciSegmentRead32 (
            PCI_SEGMENT_LIB_ADDRESS (
              SA_SEG_NUM,
              SA_MC_BUS,
              SA_MC_DEV,
              SA_MC_FUN,
              R_SA_BGSM)
            );
  Tolud = PciSegmentRead32 (
            PCI_SEGMENT_LIB_ADDRESS (
              SA_SEG_NUM,
              SA_MC_BUS,
              SA_MC_DEV,
              SA_MC_FUN,
              R_SA_TOLUD)
            );

  DEBUG ((DEBUG_INFO, "      IGD Stolen Memory Consistency Test\n"));

  switch ((Ggc & B_SA_GGC_GGMS_MASK) >> N_SA_GGC_GGMS_OFFSET) {
    case V_SA_GGC_GGMS_2MB:
      GsmSize = SIZE_2MB;
      break;
    case V_SA_GGC_GGMS_4MB:
      GsmSize = SIZE_4MB;
      break;
    case V_SA_GGC_GGMS_8MB:
      GsmSize = SIZE_8MB;
      break;
    default:
      GsmSize = 0;
      break;
  }

 if (((Ggc & B_SA_GGC_GMS_MASK) >> N_SA_GGC_GMS_OFFSET) < 240 ) {
    DsmSize = (UINT32) ((Ggc & B_SA_GGC_GMS_MASK) >> N_SA_GGC_GMS_OFFSET) * SIZE_32MB;
  } else {
    DsmSize = SIZE_4MB * (((Ggc & B_SA_GGC_GMS_MASK) >> N_SA_GGC_GMS_OFFSET) - 239);
  }

  DEBUG ((DEBUG_INFO, "        INFO: DSM:   0x%08x  Size: 0x%08x\n", Bdsm & B_SA_BDSM_BDSM_MASK, DsmSize));
  DEBUG ((DEBUG_INFO, "        INFO: GSM:   0x%08x  Size: 0x%08x\n", Bgsm & B_SA_BGSM_BGSM_MASK, GsmSize));
  DEBUG ((DEBUG_INFO, "        INFO: TOLUD: 0x%08x\n", Tolud & B_SA_TOLUD_TOLUD_MASK));

  if ((Bgsm & B_SA_BGSM_BGSM_MASK) != (Bdsm & B_SA_BDSM_BDSM_MASK) - GsmSize) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: BGSM: 0x%x != BDSM: %x - GSMSize: %x \n",(Bgsm & B_SA_BGSM_BGSM_MASK),(Bdsm & B_SA_BDSM_BDSM_MASK),GsmSize));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_CODE_2,
      HSTI_PROCESSOR_GRAPHICS_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_STRING_2
      );
    Result = FALSE;
  }
  if ((Bdsm & B_SA_BDSM_BDSM_MASK) != (Tolud & B_SA_TOLUD_TOLUD_MASK) - DsmSize) {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: BDSM: 0x%x != TOLUD: %x - DSMSize: %x \n",(Bdsm & B_SA_BDSM_BDSM_MASK),(Tolud & B_SA_TOLUD_TOLUD_MASK),DsmSize));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_CODE_2,
      HSTI_PROCESSOR_GRAPHICS_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_STRING_2
      );
    Result = FALSE;
  }

  DEBUG ((DEBUG_INFO, "      Reserved Check Test\n"));
  if ((Pavpc & B_SA_PAVPC_PCME_MASK) != 0) {
    PcmBase = Pavpc & B_SA_PAVPC_PCMBASE_MASK;

    if ((PcmBase < (Bdsm & B_SA_BDSM_BDSM_MASK)) ||
        (PcmBase > (Tolud & B_SA_TOLUD_TOLUD_MASK)) ||
        ((PcmBase + SIZE_1MB) < (Bdsm & B_SA_BDSM_BDSM_MASK)) ||
        ((PcmBase + SIZE_1MB) > (Tolud & B_SA_TOLUD_TOLUD_MASK))) {
      DEBUG ((DEBUG_INFO, "        Unexpected Status: Graphics Security Reserved Check is Enabled but:\n"));
      DEBUG ((DEBUG_INFO, "        PCMBASE: 0x%08x or PCMBASE: 0x%08x + Size out of BDSM 0x%x or TOLUD 0x%08x boundaries\n", PcmBase, PcmBase + SIZE_1MB, Bdsm & B_SA_BDSM_BDSM_MASK, Tolud & B_SA_TOLUD_TOLUD_MASK));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_CODE_3,
        HSTI_PROCESSOR_GRAPHICS_SECURITY_CONFIGURATION,
        HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_STRING_3
        );
      Result = FALSE;
    }
  } else {
    DEBUG ((DEBUG_INFO, "        Unexpected Status: Graphics Security Reserved Check is Disabled\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_CODE_3,
      HSTI_PROCESSOR_GRAPHICS_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION_UNEXP_STATUS_STRING_3
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
               HSTI_BYTE1_SECURE_INTEGRATED_GRAPHICS_CONFIGURATION
               );
    CheckStatusForHstiLibSet (Status);
  }

  return;
}

/** @file
  This file contains the tests for the IntegratedDeviceDMAProtection bit

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

#define   B_VTD_BAR_MASK                    (0x7ffffff000)
#define   B_IPU_VENDOR_DEVICE_MASK          (0xFFFF)
#define   B_ITBT_VENDOR_DEVICE_MASK         (0xFFFF)
// Check if TBT Controller enabled
#define   B_ITBT_TECHNOLOGY_ENABLE_MASK     (B_SA_MCHBAR_TCSS_DEVEN_DMA0_MASK | \
                                             B_SA_MCHBAR_TCSS_DEVEN_DMA1_MASK)
typedef enum {
  Vtd1   = 1,
  Vtd9   = 2,
  VtdMax = 4
} VTD_INDEX_TYPE;

typedef enum {
  StatusMsg0   = 0,
  StatusMsg1   = 1,
  StatusMsgMax = 2
} STATUS_MSG_INDEX_TYPE;

/**
 Verify VTd (1, 2 and 9 HW Engines) Tests.

 Return   TRUE   All Tests Passed
          FALSE  At least one Test Failed for
                 VTd Checks
**/
BOOLEAN
CheckVtdConfiguration (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOLEAN         Result;
  UINT64          McD0BaseAddress;
  UINT64          McD2BaseAddress;
  UINT32          IgdVendorDeviceId;
  UINT32          SaMchBar;
  UINT32          Vtd;
  BOOLEAN         DevicePresentFlag = 0;
  UINT64          VtdIndex;
  UINTN           StringSize1;
  UINTN           StringSize2;
  CHAR16          *HstiStatusString [2] = {NULL, NULL};

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                      SA_SEG_NUM,
                      SA_MC_BUS,
                      SA_MC_DEV,
                      SA_MC_FUN,
                      0
                      );
  SaMchBar        = PciSegmentRead32 (
                      McD0BaseAddress + R_SA_MCHBAR
                      ) &~B_SA_MCHBAR_MCHBAREN_MASK;

  Result = TRUE;

  //
  // Check Vtd1 and Vtd9 - index 1 and 2 (Vtd1, Vtd9)
  //
  for (VtdIndex=1; VtdIndex < VtdMax; VtdIndex++) {
    DevicePresentFlag            = 0;
    HstiStatusString[StatusMsg0] = NULL;
    HstiStatusString[StatusMsg1] = NULL;
    StringSize1 = 0;
    StringSize2 = 0;

    switch (VtdIndex) {
    case Vtd1:
      //
      // Read Integrated Graphics Device
      //
      McD2BaseAddress    = PCI_SEGMENT_LIB_ADDRESS (
                             SA_SEG_NUM,
                             SA_IGD_BUS,
                             SA_IGD_DEV,
                             SA_IGD_FUN_0,
                             0
                             );
      IgdVendorDeviceId  = PciSegmentRead32 (McD2BaseAddress);
      DEBUG ((DEBUG_INFO, "        IGD (Vtd1) Vendor Device Register Value = %lx\n", IgdVendorDeviceId));
      //
      // Check GFXVTBAR (VTd1)
      // IgdVendor ID is defined and not equal to GT0 Device ID (@todo add check statement for EHL GT0 when available) and IGD is enabled.
      //
      if ((IgdVendorDeviceId != B_IGD_VENDOR_DID_MASK) &&
          (PciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN) & B_SA_DEVEN_D2EN_MASK)) {
        Vtd = MmioRead32 (SaMchBar + R_MCHBAR_VTD1_OFFSET);

        HstiStatusString[StatusMsg0] = BuildHstiStatusStringAndSize (
                                         HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_2,
                                         HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
                                         HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_2,
                                         StringSize1
                                         );
        HstiStatusString[StatusMsg1] = BuildHstiStatusStringAndSize (
                                         HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_3,
                                         HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
                                         HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_3,
                                         StringSize2
                                         );
        DevicePresentFlag = 1;
      }
      break;
    case Vtd9:
      //
      // Check BTDPVC0BAR (VTd9)
      //
     Vtd = MmioRead32 (SaMchBar + R_MCHBAR_VTD3_OFFSET);
      HstiStatusString[StatusMsg0] = BuildHstiStatusStringAndSize (
                                       HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_12,
                                       HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
                                       HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_12,
                                       StringSize1
                                       );
      HstiStatusString[StatusMsg1] = BuildHstiStatusStringAndSize (
                                       HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_13,
                                       HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
                                       HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_13,
                                       StringSize2
                                       );
      DevicePresentFlag = 1;
      VtdIndex = 9;
      break;

    default:
      DevicePresentFlag = 0;
      break;
    }

    if (DevicePresentFlag) {
      DEBUG ((DEBUG_INFO, "        Vtd%d Register Value = %lx\n", VtdIndex, Vtd));
      DEBUG ((DEBUG_INFO, "          Vtd%d Enabled Test\n", VtdIndex));
      if ((Vtd & BIT0) == 0) {
        DEBUG ((DEBUG_INFO, "            Unexpected Status: Vtd%d is not Enabled\n", VtdIndex));

        Status = HstiLibAppendErrorString (
                   PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                   NULL,
                   HstiStatusString[StatusMsg0]
                   );
        CheckStatusForHstiLibAppend (Status);
        Result = FALSE;
      } else {
        DEBUG ((DEBUG_INFO, "          Vtd%d Region Address Correctly Configured Test\n", VtdIndex));
        if ((Vtd & B_VTD_BAR_MASK) == 0) {
          DEBUG ((DEBUG_INFO, "            Unexpected Status: Vtd%d enabled but Vtd%d Region \
                    Address is not Configured\n", VtdIndex, VtdIndex));

          Status = HstiLibAppendErrorString (
                     PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
                     NULL,
                     HstiStatusString[StatusMsg1]
                     );
          CheckStatusForHstiLibAppend (Status);
          Result = FALSE;
        }
      }
    }

    if (HstiStatusString[StatusMsg0] != NULL) {
      ZeroMem (HstiStatusString[StatusMsg0], sizeof (StringSize1));
      FreePool (HstiStatusString[StatusMsg0]);
    }
    if (HstiStatusString[StatusMsg1] != NULL) {
      ZeroMem (HstiStatusString[StatusMsg1], sizeof (StringSize2));
      FreePool (HstiStatusString[StatusMsg1]);
    }
  }

  return Result;
}


/**
  Run tests for IntegratedDeviceDMAProtection bit
**/
VOID
CheckIntegratedDeviceDmaProtection (
  VOID
  )
{
  EFI_STATUS      Status;
  BOOLEAN         Result;
  UINT64          McD0BaseAddress;
  UINT32          SaMchBar;

  if ((mFeatureImplemented[0] & HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION) == 0) {
    return;
  }

  Result = TRUE;

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                      SA_SEG_NUM,
                      SA_MC_BUS,
                      SA_MC_DEV,
                      SA_MC_FUN,
                      0
                      );
  SaMchBar        = PciSegmentRead32 (
                      McD0BaseAddress + R_SA_MCHBAR
                      ) &~B_SA_MCHBAR_MCHBAREN_MASK;

  DEBUG ((DEBUG_INFO, "      DEBUG_INFO: McD0BaseAddress = 0x%x\n", McD0BaseAddress));

  DEBUG ((DEBUG_INFO, "      VTd Feature Enabled Test\n"));

  if ((PciSegmentRead32 (McD0BaseAddress + R_SA_MC_CAPID0_A_OFFSET) & BIT23) != 0) {
    DEBUG ((DEBUG_INFO, "       Unexpected Status: VTd Feature is Disabled\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_1,
      HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
      HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_1
      );
    Result = FALSE;
  } else {
    // If IOP VT-d IOMMU BAR (VTd9 HW engine) is not enabled then
    // VTd enable in SKU but disabled in platform
    // else verify VTd 1 - 6 and 9 HW engines
    if ((MmioRead32 (SaMchBar + R_MCHBAR_VTD3_OFFSET) & BIT0) == 0) {
      DEBUG ((DEBUG_INFO, "       Unexpected Status: VTd Feature is Enabled in the CPU SKU but disabled in the Platform\n"));

      BuildAndAppendHstiStatusString (
        HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_CODE_10,
        HSTI_INTEGRATED_DEVICE_DMA_PROTECTION,
        HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION_UNEXP_STATUS_STRING_10
        );
      Result = FALSE;
    } else {
      // Check VTd1, VTd2 and VTd9 HW engines
      if (CheckVtdConfiguration () == FALSE) {
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
               HSTI_BYTE0_INTEGRATED_DEVICE_DMA_PROTECTION
               );
    CheckStatusForHstiLibSet (Status);
  }

  return;
}

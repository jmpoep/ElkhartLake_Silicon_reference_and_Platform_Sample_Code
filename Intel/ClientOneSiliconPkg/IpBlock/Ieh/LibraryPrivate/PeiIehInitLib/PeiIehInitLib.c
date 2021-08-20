/** @file
  Initializes IEH Device in PEI

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

#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PchPcrLib.h>
#include <Ppi/SiPolicy.h>
#include <Register/IehRegs.h>
#include <Register/ItssRegs.h>
#include <Library/PciSegmentLib.h>
#include <Register/PchRegs.h>
#include <Register/PchPcrRegs.h>
#include <IndustryStandard/Pci30.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Library/CpuPlatformLib.h>

/**
  The function performs IEH specific programming.

  @param[in] SiPolicyPpi        The SI Policy PPI instance

**/
VOID
IehInit (
  IN  SI_POLICY_PPI           *SiPolicyPpi
  )
{
  IEH_CONFIG     *IehConfig;
  UINT32         Data32;
  UINT32         ItssUev;
  UINT64         IehPciBase;
  EFI_STATUS     Status;

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gIehConfigGuid, (VOID *) &IehConfig);
  ASSERT_EFI_ERROR (Status);

  IehPciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_IEH,
                 PCI_FUNCTION_NUMBER_PCH_IEH,
                 0
                 );

  if (PciSegmentRead32 (IehPciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFFFFFF) {
    DEBUG ((DEBUG_INFO, "IEH device not enabled. Skipping Init\n"));
    return;
  }

  ASSERT (PciSegmentRead32 (IehPciBase + PCI_VENDOR_ID_OFFSET) != 0xFFFFFFFF);

  ///
  /// LERRUNCSEV Register needs to be programmed as follows :
  ///  [5:0] = 111111b
  ///  [23, 20, 17, 14, 11, 8] = 111111b if ITSS.UEV[20] = 1b
  ///  [22, 19, 16, 13, 10, 7] = 111111b if ITSS.UEV[16] = 1b
  ///  [21, 18, 15, 12,  9, 6] = 111111b if ITSS.UEV[22] = 1b
  ///
  if (!IsFusaSupported ()) {
    ItssUev = PchPcrRead32(PID_ITSS, R_ITSS_PCR_UEV);
    Data32 = BIT5 | BIT4 | BIT3 | BIT2 | BIT1 | BIT0;
    if (ItssUev & BIT20) {
      Data32 |= BIT23 | BIT20 | BIT17 | BIT14 | BIT11 | BIT8;
    }
    if (ItssUev & BIT16) {
      Data32 |= BIT22 | BIT19 | BIT16 | BIT13 | BIT10 | BIT7;
    }
    if (ItssUev & BIT22) {
      Data32 |= BIT21 | BIT18 | BIT15 | BIT12 | BIT9 | BIT6;
    }
    PciSegmentWrite32 (IehPciBase + R_IEH_CFG_LERRUNCSEV, Data32);
  } else {
    PciSegmentWrite32 (IehPciBase + R_IEH_CFG_LERRUNCSEV, 0);
  }

  if (IehConfig->Mode == IEH_MODE_ENABLE) {
    PciSegmentAndThenOr32 (IehPciBase + R_IEH_CFG_MISCCTL1, (UINT32) ~(BIT30), BIT31);
    PciSegmentAnd32 (IehPciBase + R_IEH_CFG_BITMAP, 0xFFFFFFE0);

    if (!IsFusaSupported ()) {
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_GCOERRMSK, 0xFFE00000);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_GNFERRMSK, 0xFFE00000);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_GFAERRMSK, 0xFFE00000);
      PciSegmentAndThenOr32 (IehPciBase + R_IEH_CFG_GSYSEVTMAP, 0xFFFFFFC0, 0x3F);
      PciSegmentAndThenOr32 (IehPciBase + R_IEH_CFG_ERRPINCTRL, 0xFFFFFFC0, 0x2A);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_LERRUNCMSK, 0xFF000000);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_LERRCORMSK, 0xFF000000);
    } else {
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_LERRUNCMSK, 0);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_LERRCORMSK, 0);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_LCOERRCNTSEL, 0xFFFFFFFF);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_GCOERRMSK, 0);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_GNFERRMSK, 0);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_GFAERRMSK, 0);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_GSYSEVTMSK, 0);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_GSYSEVTMAP, 0x00000020);
      PciSegmentWrite32 (IehPciBase + R_IEH_CFG_ERRPINCTRL, 0x0000002A);
    }
  } else {
    // IEH Mode is set to Bypass
    PciSegmentAndThenOr32 (IehPciBase + R_IEH_CFG_MISCCTL1, (UINT32) ~(BIT31), BIT30);
  }
}



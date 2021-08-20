/** @file
  PEIM to initialize GNA.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <CpuRegs.h>
#include <Library/GnaInitLib.h>
#include <Library/GnaInfoLib.h>

/**
  GnaInit: Initialize the GNA device
  @param[in] GnaConfig  - GnaConfig to access the GNA Policy related information

**/
VOID
GnaInit (
  IN       GNA_CONFIG     *GnaConfig
  )
{
  UINT32            Data32;
  UINT64            McD0BaseAddress;

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, 0);

  ///
  /// Read PCI Device 0 offset 0xe8 CAPID0_B register BIT8 to check GNA capability
  ///
  Data32 = PciSegmentRead32 (McD0BaseAddress + R_SA_MC_CAPID0_B);

  if ((Data32 & BIT8) == BIT8) {
    ///
    /// GNA device not supported
    ///
    DEBUG ((DEBUG_INFO, "\nGNA Device not supported"));
    return;
  }

  if (GnaConfig->GnaEnable == FALSE) {
    ///
    /// Disable GNA device by DEVEN register
    ///

    PciSegmentAnd32 (McD0BaseAddress + R_SA_DEVEN, (UINT32) ~B_SA_DEVEN_D8EN_MASK);
    DEBUG ((DEBUG_INFO, "\nGNA Device has been disabled"));
    return;
  }

}

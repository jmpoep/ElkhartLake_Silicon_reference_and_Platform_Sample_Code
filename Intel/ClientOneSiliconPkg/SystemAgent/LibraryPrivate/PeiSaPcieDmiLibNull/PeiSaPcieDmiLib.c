/** @file
  SA PCIe/DMI PEI Initialization library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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
#include <SystemAgent/LibraryPrivate/PeiSaPcieInitLib/LowLevel/SaPegLowLevel.h>
#include <Library/SaPlatformLib.h>
#include <Library/PcieInitLib.h>
///
/// Functions
///
/**
  Programs the CNL PCIe/DMI recipe.

  @param[in]  DmiBar                      - DMIBAR
  @param[in]  MchBar                      - MCHBAR
  @param[in]  Gen3CtlePeaking             - Array of CTLE Peaking values to program per bundle
  @param[in]  Gen3CtlePeakingLength       - Length of the Gen3CtlePeaking array
  @param[in]  Gen3RxCtleOverride          - RxCTLE override configuration
  @param[in]  ProgramDmiRecipe            - Set to TRUE to program DMI, FALSE to program PCIe
**/
VOID
EFIAPI
CnlPegDmiRecipe (
  IN  UINT64                            DmiBar,
  IN  UINT64                            MchBar,
  IN  UINT8                             *Gen3CtlePeaking,
  IN  UINT8                             Gen3CtlePeakingLength,
  IN  UINT8                             Gen3RxCtleOverride,
  IN  BOOLEAN                           ProgramDmiRecipe
  )
{
  return;
}


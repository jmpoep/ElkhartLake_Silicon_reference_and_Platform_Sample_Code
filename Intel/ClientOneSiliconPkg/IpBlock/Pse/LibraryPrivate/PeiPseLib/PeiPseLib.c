/** @file
  PEI PCH PSE Library implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#include <Library/PeiServicesLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PchInfoLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/PmcPrivateLib.h>

/**
  Check if PSE is enabled

  @retval TRUE                    PSE is enabled
  @retval FALSE                   PSE device either fuse or policy disabled
**/
BOOLEAN
IsPseEnabled (
  VOID
  )
{
  EFI_STATUS                Status;
  SI_PREMEM_POLICY_PPI      *SiPreMemPolicyPpi;
  PSE_PREMEM_CONFIG         *PsePreMemConfig;

  //
  // Check if fuse disabled
  //
  if (!PmcIsPseSupported ()) {
    //
    // PSF Function Disable set in PchEarlyDisabledDeviceHandling()
    //
    DEBUG ((DEBUG_INFO, "PSE Fuse disabled - PSF Function Disable already set!\n"));
    return FALSE;
  }

  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPsePreMemConfigGuid, (VOID *) &PsePreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "PsePreMemConfig->Enable :%x\n",PsePreMemConfig->Enable));
  if (PsePreMemConfig->Enable) {
    return TRUE;
  } else {
    return FALSE;
  }
}

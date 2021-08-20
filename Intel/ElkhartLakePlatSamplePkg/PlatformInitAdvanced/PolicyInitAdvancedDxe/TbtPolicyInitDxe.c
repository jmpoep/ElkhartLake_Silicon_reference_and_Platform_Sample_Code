/** @file
  This file is SampleCode for TBT DXE Policy initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#include "TbtPolicyInitDxe.h"


//
// Function implementations
//

/**
  Initialize TBT DXE Policy

  @param[in] ImageHandle          Image handle of this driver.

  @retval EFI_SUCCESS             Initialization complete.
  @exception EFI_UNSUPPORTED      The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
TbtPolicyInitDxe (
  IN EFI_HANDLE                   ImageHandle
  )
{
  EFI_STATUS               Status;
  ITBT_POLICY_PROTOCOL     *ITbtPolicy;

  ITbtPolicy = NULL;
  Status     = EFI_SUCCESS;
  //
  // Call CreateITbtDxeConfigBlocks to create & initialize platform policy structure
  // and get all Intel default policy settings.
  //
  Status = CreateITbtDxeConfigBlocks (&ITbtPolicy);
  ASSERT_EFI_ERROR (Status);
  ASSERT (ITbtPolicy != NULL);
  DEBUG ((DEBUG_INFO, "ITbtPolicy->TableHeader.NumberOfBlocks = 0x%x\n ", ITbtPolicy->TableHeader.NumberOfBlocks));

  if (PcdGetBool (PcdDTbtEnable)) {
    //
    // Install DTBT Policy
    //
    Status = DTbtInstallPolicyProtocol (ImageHandle);
    if (!EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "Install DTbt Policy done\n"));
    }
  }

  if (mFirmwareConfiguration != FwConfigDefault) {

    UpdateDxeTbtPolicy (ITbtPolicy);
  }

  //
  // Install ITbtInstallPolicyProtocol.
  // While installed, RC assumes the Policy is ready and finalized. So please
  // update and override any setting before calling this function.
  //
  Status = ITbtInstallPolicyProtocol (ImageHandle, ITbtPolicy);

  return Status;
}

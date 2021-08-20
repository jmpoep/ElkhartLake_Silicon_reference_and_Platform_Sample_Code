/** @file
  PEI CSE Variable Storage Status Library implementation file.

@copyright
  @copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include <Library/BaseLib.h>
#include <Library/CseVariableStorageStatusLib.h>

#include <CseVariableStorageCommandQueue.h>

/**
  Determines whether the given HECI device is used for CSE variable storage.

  @param[in]  HECI_DEVICE     The HECI device to be evaluated for CSE variable storage usage.

  @retval     TRUE            The given HECI device is used for CSE variable storage.
  @retval     FALSE           The given HECI device is not used for CSE variable storage.

**/
BOOLEAN
EFIAPI
IsCseVariableStorageDevice (
  HECI_DEVICE   HeciDevice
  )
{
  return (
    IsCseVariableStorageEnabled () &&
    (
      HeciDevice == CSE_VARIABLE_STORAGE_CMD_QUEUE_UNTRUSTED_HECI_DEVICE ||
      HeciDevice == CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE
      )
    );
}

/**
  Determines whether the given HECI device is used after exit boot services or not.

  @param[in]  HECI_DEVICE     The HECI device to be evaluated whether it is used after exit boot services or not.

  @retval     TRUE            The given HECI device is used after exit boot services.
  @retval     FALSE           The given HECI device is not used after exit boot services.

**/
BOOLEAN
EFIAPI
IsUsedAfterExitBootServices (
  HECI_DEVICE   HeciDevice
  )
{
  return (
    IsCseVariableStorageEnabled () &&
    (
      HeciDevice == CSE_VARIABLE_STORAGE_CMD_QUEUE_TRUSTED_HECI_DEVICE
      )
    );
}
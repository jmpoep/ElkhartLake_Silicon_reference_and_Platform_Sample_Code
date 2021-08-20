/** @file
  Product specific definitions for SCS controllers.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include "PeiScsInitInternal.h"

/**
  Applies overrides to MMP lane as described in override table

  @param[in] PortId             Sideband port id of the MMP
  @param[in] MmpLaneIndex       Lane index of the MMP
**/
VOID
MmpApplyOverride (
  IN PCH_SBI_PID   PortId,
  IN UINT8         MmpLaneIndex
  )
{
}

/**
  Gets the default DLL values for SdCard controller.

  @return SCS_SD_DLL  Pointer to SdCard default DLL
**/
SCS_SD_DLL*
ScsGetSdCardDefaultDll (
  VOID
  )
{
  ASSERT (FALSE);
  return NULL;
}

/**
  Gets the default capabilities of SdCard controller.

  @return SCS_SD_CAPS  Pointer to SdCard capabilities
**/
SCS_SD_CAPS*
ScsGetSdCardDefaultCapabilities (
  VOID
  )
{
  ASSERT (FALSE);
  return NULL;
}

/**
  Gets the default capabilities of eMMC controller.

  @return SCS_SD_CAPS  Pointer to the eMMC capabilities
**/
SCS_SD_CAPS*
ScsGetEmmcDefaultCapabilities (
  VOID
  )
{
  ASSERT (FALSE);
  return NULL;
}

/**
Gets the default DLL values for eMMC controller.

@return SCS_SD_DLL  Pointer to eMMC default DLL
**/
SCS_SD_DLL*
ScsGetEmmcDefaultDll (
  VOID
  )
{
  ASSERT (FALSE);
  return NULL;
}

SCS_UFS_MMP  mUfs0Mmp = {
  PID_MMP_UFSX2A,
  (BIT1 | BIT0)
};

SCS_UFS_MMP mUfs1Mmp = {
  PID_MMP_UFSX2B,
  (BIT1 | BIT0)
};

/**
  Returns the MMP descriptor that given UFS controller is using.

  @param[in] UfsIndx  Index of the UFS controller

  @return SCS_UFS_MMP  Pointer to the MMP instance
**/
SCS_UFS_MMP*
ScsGetUfsMmp (
  IN UINT8  UfsIndex
  )
{
  switch (UfsIndex) {
    case 0:
      return &mUfs0Mmp;
    case 1:
      return &mUfs1Mmp;
    default:
      ASSERT (FALSE);
      return NULL;
  }
}

/**
  Checks if given UFS is used as a boot medium.

  @param[in] UfsIndex  Index of the UFS controller

  @retval  TRUE   UFS is used as a boot medium
  @retval  FALSE  UFS is not used as a boot medium
**/
BOOLEAN
ScsIsUfsBootMedium (
  IN UINT8  UfsIndex
  )
{
  return FALSE;
}


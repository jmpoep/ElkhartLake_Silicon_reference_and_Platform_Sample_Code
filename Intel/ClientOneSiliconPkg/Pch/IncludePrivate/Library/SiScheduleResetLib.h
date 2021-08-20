/** @file
  Reset scheduling library services

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

#ifndef _SI_SCHEDULE_RESET_LIB_H_
#define _SI_SCHEDULE_RESET_LIB_H_

#include <Uefi/UefiMultiPhase.h>
#include <PchResetPlatformSpecific.h>

/**
  This function updates the reset information in SiScheduleResetHob
  @param[in] ResetType        UEFI defined reset type.
  @param[in] ResetData        Optional element used to introduce a platform specific reset.
                               The exact type of the reset is defined by the EFI_GUID that follows
                               the Null-terminated Unicode string.
**/
VOID
SiScheduleResetSetType (
  IN EFI_RESET_TYPE     ResetType,
  IN PCH_RESET_DATA     *ResetData OPTIONAL
  );

/**
  This function returns TRUE or FALSE depending on whether a reset is required based on SiScheduleResetHob

  @retval     BOOLEAN       The function returns FALSE if no reset is required
**/
BOOLEAN
SiScheduleResetIsRequired (
  VOID
  );

/**
  This function performs reset based on SiScheduleResetHob

  @retval     BOOLEAN       The function returns FALSE if no reset is required
**/
BOOLEAN
SiScheduleResetPerformReset (
  VOID
  );

#endif //_SI_SCHEDULE_RESET_LIB_H_

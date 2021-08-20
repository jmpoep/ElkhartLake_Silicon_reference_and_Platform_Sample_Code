/** @file
  ITSS public library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/PchPcrLib.h>
#include <Register/PchPcrRegs.h>
#include <Register/ItssRegs.h>

/**
  This function gets the 8254CGE bit
  After BIOSDONE, the function only works inside SMM.

  @param[out]  ClockGateState    TRUE : 8254CGE is set, FALSE: 8254CGE is clear.

  @retval  EFI_SUCCESS           Get 8254CGE status successfully.
           EFI_UNSUPPORTED       Doesn't support 8254CGE get.
**/
EFI_STATUS
ItssGet8254ClockGateState (
  OUT BOOLEAN  *ClockGeteState
  )
{
  *ClockGeteState = (PchPcrRead32 (PID_ITSS, R_ITSS_PCR_ITSSPRC) & B_ITSS_PCR_ITSSPRC_8254CGE) != 0;
  return EFI_SUCCESS;
}

/**
  This function sets the 8254CGE bit
  After BIOSDONE, the function only works inside SMM.

  @param[in]  ClockGateEnable    Enable or disable clock gate

  @retval  EFI_SUCCESS           Set 8254CGE status successfully.
           EFI_UNSUPPORTED       Doesn't support 8254CGE set.
**/
EFI_STATUS
ItssSet8254ClockGateState (
  IN BOOLEAN   ClockGateEnable
  )
{
  PchPcrAndThenOr32 (
    PID_ITSS, R_ITSS_PCR_ITSSPRC,
    (UINT32)~B_ITSS_PCR_ITSSPRC_8254CGE,
    ClockGateEnable ? B_ITSS_PCR_ITSSPRC_8254CGE : 0
    );
  return EFI_SUCCESS;
}


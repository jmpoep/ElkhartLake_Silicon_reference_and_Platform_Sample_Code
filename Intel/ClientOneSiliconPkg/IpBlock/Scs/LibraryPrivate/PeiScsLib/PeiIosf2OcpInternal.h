/** @file
  Iosf2Ocp internal header.

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

#ifndef _PEI_IOSF2OCP_INTERNAL_H_
#define _PEI_IOSF2OCP_INTERNAL_H_

#include <Uefi/UefiBaseType.h>
#include <Library/PchPcrLib.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/PchInfoLib.h>
#include <Register/ScsIosf2OcpBridgeRegs.h>
#include "PeiIosf2Ocp.h"

/**
  This function configures power and clock gating policy in Iosf2Ocp bridge
  based on value passed by the caller.

  @param[in] BridgePortId              Port ID of target bridge
  @param[in] PowerAndClockGatingValue  Value to be written to power and clock gating register
**/
VOID
Iosf2OcpConfigurePowerAndClockGating (
  IN PCH_SBI_PID  BridgePortId,
  IN UINT32       PowerAndClockGatingValue
  );

/**
  Enables Iosf2Ocp bridge to send snooped transactions on
  IOSF fabric.

  @param[in]  BridgePortId  Iosf2Ocp bridge sideband port id
**/
VOID
Iosf2OcpEnableSnoopedTransactions (
  IN PCH_SBI_PID  BridgePortId
  );

#endif


/** @file
  This file contains functions that initializes Dekel

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
#include <Library/PeiCpuPcieDekelInitLib.h>
/**
  Read DEKEL FW download status

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID

  @retval     BOOLEAN          Fw Download Completed TRUE or FALSE
**/

BOOLEAN
EFIAPI
DekelFwStatus (
  IN  CPU_SB_DEVICE_PID  CpuSbDevicePid
  )
{
  return TRUE;
}

/**
  Initialize the Dekel in PEI

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID
**/

VOID
EFIAPI
DekelInit (
  IN  CPU_SB_DEVICE_PID  CpuSbDevicePid
  )
{
  return;
}

/**
  Read DEKEL Firmware Version

  @param[in]  CpuSbDevicePid   CPU SB Device Port ID

  @retval     UINT32         Dekel Firmware Version
**/

UINT32
EFIAPI
GetDekelFwVersion (
  IN  CPU_SB_DEVICE_PID  CpuSbDevicePid
)
{
  return 0;
}
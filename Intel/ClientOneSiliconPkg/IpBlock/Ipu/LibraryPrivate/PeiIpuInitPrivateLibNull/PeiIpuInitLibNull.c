/** @file
  PEIM to initialize IPU device

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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
#include <Library/IpuInitLib.h>

/**
  IpuInit: Initialize the IPU device

  @param[in] IPU_PREMEM_CONFIG   IpuPreMemPolicy
**/
VOID
IpuInit (
   VOID
  )
{
  return;
}

/**
  IsIpuEnabled: Check the IPU is enabled or not

  @retval FALSE = IPU Disabled by policy or fuse, TRUE = IPU Enabled.
**/
BOOLEAN
IsIpuEnabled (
  VOID
  )
{
  return FALSE;
}

/**
  GetIpuImrConfiguration: Get the IPU IMR Configuration

  @retval IPU IMR Configuration, 0 = IPU Camera, 1 = IPU Gen
**/
UINT8
GetIpuImrConfiguration (
  VOID
  )
{
  return 0;
}

/**
  IsIpuSupported: Check if IPU is supported or not

  @retval FALSE = IPU is fused off. TRUE = IPU is supported by Sillicon.
**/
BOOLEAN
IsIpuSupported (
  VOID
  )
{
  return FALSE;
}



/**
  Check IPU policies are valid for debugging unexpected problem if these
  values are not initialized or assigned incorrect resource.

  @param[in] IpuPreMemPolicy    The IPU PreMem Policy instance

**/
VOID
IpuValidatePolicy (
  IN    IPU_PREMEM_CONFIG    *IpuPreMemPolicy
  )
{
  return;
}

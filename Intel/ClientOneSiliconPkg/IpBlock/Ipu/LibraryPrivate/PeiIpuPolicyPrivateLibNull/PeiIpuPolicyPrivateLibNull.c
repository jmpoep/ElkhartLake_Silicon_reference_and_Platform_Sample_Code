/** @file
  This file provides services for IPU PEI policy default initialization

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

#include <Ppi/SiPolicy.h>


/**
  @param[in] SiPolicyPreMemPpi - Instance of SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
IpuPrintPolicyPpiPreMem (
  IN  SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  return;
}

/**
  @retval      Size of IPU config block table in case IPU is disabled.

**/
UINT16
EFIAPI
IpuGetConfigBlockTotalSizePreMem (
VOID
  )
{
  return 0;
}

/**

  IpuAddConfigBlocksPreMem adds IPU config blocks.
  No Config Block is added,  return success always.

**/
EFI_STATUS
EFIAPI
IpuAddConfigBlockPreMem (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return EFI_SUCCESS;
}

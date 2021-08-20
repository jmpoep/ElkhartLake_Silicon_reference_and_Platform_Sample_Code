/** @file
  Main System Agent Policy structure definition which will contain several config blocks during runtime.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#ifndef _SA_POLICY_COMMON_H_
#define _SA_POLICY_COMMON_H_

#include <Uefi.h>
#include <Library/SmbusLib.h>
#include <SaCommonDefinitions.h>
#include <ConfigBlock.h>
#include <Library/ConfigBlockLib.h>
#include <HybridGraphicsConfig.h>
#include <ConfigBlock/PramPreMemConfig.h>
#include <MemoryConfig.h>
#include <ConfigBlock/SaMiscPeiPreMemConfig.h>
#include <ConfigBlock/SaMiscPeiConfig.h>


//
// Extern the GUID for PPI users.
//
extern EFI_GUID gSiPolicyPpiGuid;
extern EFI_GUID gSaMiscPeiConfigGuid;
extern EFI_GUID gSiPreMemPolicyPpiGuid;
extern EFI_GUID gSaMiscPeiPreMemConfigGuid;
extern EFI_GUID gHybridGraphicsConfigGuid;
extern EFI_GUID gCpuTraceHubConfigGuid;
extern EFI_GUID gMemoryConfigGuid;
extern EFI_GUID gMemoryConfigNoCrcGuid;

#endif // _SA_POLICY_COMMON_H_

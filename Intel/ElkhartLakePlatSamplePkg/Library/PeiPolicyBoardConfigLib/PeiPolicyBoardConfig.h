/** @file
 Header file for PeiPolicyBoardConfig library instance.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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
#ifndef _PEI_POLICY_BOARD_CONFIG_H_
#define _PEI_POLICY_BOARD_CONFIG_H_

#include <PiPei.h>
#include <Library/PeiServicesLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiPolicyBoardConfigLib.h>
#include <Library/IoLib.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Library/EcLib.h>
#include <SetupVariable.h>
#include <SoftwareGuardSetupData.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MmPciLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/SiPolicyLib.h>
#if FixedPcdGet8(PcdFspModeSelection) == 1
#include <FspmUpd.h>
#include <FspsUpd.h>
#include <Library/FspCommonLib.h>
#endif

#define TPM20_SGX_NVINDEX  0x01C10104
#define TPM12_SGX_NVINDEX  0x50000004

#define SINIT_SVN_VARIABLE_NAME   (L"SinitSvn")

///
/// A NV-RAM variable for storing SINIT SVN value.
///
typedef struct _SINIT_SVN {
  ///
  /// Non-zero version indicates the variable is being initialized or valid
  ///
  UINT8  SvnNumber;
} SINIT_SVN;

#endif

/** @file
  PCH configuration based on PCH policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2018 Intel Corporation.

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
#ifndef _PCH_PREMEM_POLICY_COMMON_H_
#define _PCH_PREMEM_POLICY_COMMON_H_

#include <ConfigBlock.h>

#include "PchLimits.h"
#include "ConfigBlock/PchGeneralConfig.h"
#include <DciConfig.h>
#include <WatchDogConfig.h>
#include <SmbusConfig.h>
#include "ConfigBlock/LpcConfig.h"
#include "ConfigBlock/HsioPcieConfig.h"
#include "ConfigBlock/HsioSataConfig.h"
#include "ConfigBlock/HsioConfig.h"

#pragma pack (push,1)

#ifndef FORCE_ENABLE
#define FORCE_ENABLE  1
#endif
#ifndef FORCE_DISABLE
#define FORCE_DISABLE 2
#endif
#ifndef PLATFORM_POR
#define PLATFORM_POR  0
#endif

/**
  PCH Policy revision number
  Any backwards compatible changes to this structure will result in an update in the revision number
**/
#define PCH_PREMEM_POLICY_REVISION  1

/**
  PCH Policy PPI\n
  All PCH config block change history will be listed here\n\n

  - <b>Revision 1</b>:
    - Initial version.\n
**/
typedef struct _PCH_PREMEM_POLICY {
  CONFIG_BLOCK_TABLE_HEADER      TableHeader;
/*
  Individual Config Block Structures are added here in memory as part of AddConfigBlock()
*/
} PCH_PREMEM_POLICY;

#pragma pack (pop)

#endif // _PCH_PREMEM_POLICY_COMMON_H_

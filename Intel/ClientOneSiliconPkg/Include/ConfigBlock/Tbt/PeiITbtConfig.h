/** @file
  Header file for TBT PEI Policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#ifndef _PEI_ITBT_CONFIG_H_
#define _PEI_ITBT_CONFIG_H_

#include <ConfigBlock.h>
#include <Register/HostDmaRegs.h>
#include <Register/ItbtPcieRegs.h>
#include <PeiITbtGenericStructure.h>

#pragma pack(push, 1)
#define PEI_ITBT_CONFIG_REVISION 1

/**
 ITBT PEI configuration\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct _PEI_ITBT_CONFIG {
  CONFIG_BLOCK_HEADER           Header;                                            ///< Offset  0-27 Config Block Header
  ITBT_GENERIC_CONFIG           ITbtGenericConfig;                                 ///< ITbt Common Configuration
  ITBT_ROOTPORT_CONFIG          ITbtRootPortConfig [MAX_ITBT_PCIE_PORT];           ///< iTbt Root Port Configuration
  UINT16                        ITbtDmaLtr [SA_MAX_HOST_ITBT_DMA_NUMBER];          ///< iTbt Host controller DMA LTR value
} PEI_ITBT_CONFIG;
#pragma pack(pop)

#endif

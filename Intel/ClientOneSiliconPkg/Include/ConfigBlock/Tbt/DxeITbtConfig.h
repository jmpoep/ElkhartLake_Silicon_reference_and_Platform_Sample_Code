/** @file
  Headr file for iTBT DXE Policy

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

#ifndef _DXE_ITBT_CONFIG_H_
#define _DXE_ITBT_CONFIG_H_

#include <ConfigBlock.h>
#include <Register/ItbtPcieRegs.h>
#include <DxeTbtCommonDefinition.h>

#pragma pack(push, 1)

#define DXE_ITBT_CONFIG_REVISION 1

///
/// ITBT Generic Data Structure to be used cross to RP and controller in DXE phase
///
typedef struct _DXE_ITBT_GENERIC_CONFIG{
  UINT8    ITbtRtd3;
  UINT16   ITbtRtd3ExitDelay;
  UINT8    Reserved [1];         ///< Reserved for DWORD alignment
} DXE_ITBT_GENERIC_CONFIG;

/**
 ITBT DXE configuration\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct _DXE_ITBT_CONFIG {
  CONFIG_BLOCK_HEADER     Header;                                                       ///< Offset 0-27 Config Block Header
  TBT_COMMON_CONFIG       TbtCommonConfig;                                              ///< Tbt Common Information
  DXE_ITBT_GENERIC_CONFIG ITbtGenericConfig;                                            ///< ITbt Generic Information
  TBT_RESOURCE_CONFIG     ITbtResourceConfig[MAX_ITBT_PCIE_PORT];                       ///< iTbt Resource Configuration
  UINT8                   OsNativeResourceBalance;
  UINT8                   Reserved[3];
} DXE_ITBT_CONFIG;

#pragma pack(pop)

#endif

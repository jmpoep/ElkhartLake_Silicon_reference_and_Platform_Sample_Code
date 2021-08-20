/** @file

  Definitions required to create PcieStorageInfoHob

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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

#ifndef _PCH_PCIE_STORAGE_DETECT_HOB_
#define _PCH_PCIE_STORAGE_DETECT_HOB_

#include "PchLimits.h"

#define PCIE_STORAGE_INFO_HOB_REVISION              1

extern EFI_GUID gPchPcieStorageDetectHobGuid;

typedef enum {
  RstLinkWidthX1 = 1,
  RstLinkWidthX2 = 2,
  RstLinkWidthX4 = 4
} RST_LINK_WIDTH;

//
//  Stores information about connected PCIe storage devices used later by BIOS setup and RST remapping
//
#pragma pack(1)
typedef struct {
  UINT8  Revision;

  //
  // Stores the number of root ports occupied by a connected storage device, values from RST_LINK_WIDTH are supported
  //
  UINT8  PcieStorageLinkWidth[PCH_MAX_PCIE_ROOT_PORTS];

  //
  // Programming interface value for a given device, 0x02 - NVMe or RAID, 0x1 - AHCI storage, 0x0 - no device connected
  //
  UINT8  PcieStorageProgrammingInterface[PCH_MAX_PCIE_ROOT_PORTS];

  //
  // Stores information about cycle router number under a given PCIe controller
  //
  UINT8  RstCycleRouterMap[PCH_MAX_PCIE_CONTROLLERS];
} PCIE_STORAGE_INFO_HOB;
#pragma pack()
#endif

/** @file
  PCIe Config Block PreMem

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
#ifndef _PCIE_PREMEM_CONFIG_H_
#define _PCIE_PREMEM_CONFIG_H_

#define PCIE_PREMEM_CONFIG_REVISION  1

extern EFI_GUID gPciePreMemConfigGuid;

typedef enum {
  ImrRpLocationPch,
  ImrRpLocationSa,
  ImrRpLocationMax
} PCIE_IMR_ROOT_PORT_LOCATION;

#pragma pack (push,1)

typedef struct {
  UINT8     ImrEnabled;                        ///< PCIe IMR. <b>0: Disable</b>; 1: Enable.
  UINT8     ImrRpLocation;                     ///< 0: PCH_PCIe; 1: CPU_PCIe. If PCIeImrEnabled is TRUE then this will use to select the Root port location from PCH PCIe or CPU PCIe.Refer PCIE_IMR_ROOT_PORT_LOCATION above
  UINT16    ImrSize;                           ///< PCIe IMR size in megabytes
  UINT8     ImrRpSelection;                    ///< Index of root port that is selected for PCIe IMR (0 based)
  UINT8     Rsvd0[3];
} PCIE_IMR_CONFIG;

typedef struct {
  CONFIG_BLOCK_HEADER   Header;  ///< Offset 0 - 27 Config Block Header
  PCIE_IMR_CONFIG       PcieImr; ///< IMR Configuration
} PCIE_PREMEM_CONFIG;

#pragma pack (pop)
#endif // _PCIE_PREMEM_CONFIG_H_

/** @file
  Header file for SA PCI Express helpers library

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
#ifndef _SA_PCI_EXPRESS_HELPERS_LIB_H_
#define _SA_PCI_EXPRESS_HELPERS_LIB_H_

#include <SaPolicyCommon.h>

//
// Function prototypes
//

/**
  Get PCIe port number for enabled port.
  @param[in] RpBase    Root Port pci segment base address
  @return Root Port number (1 based)
**/
UINT32
PciePortNum (
  IN     UINT64  RpBase
  );

/**
  Get PCIe root port index
  @param[in] RpBase    Root Port pci segment base address
  @return Root Port index (0 based)
**/
UINT32
PciePortIndex (
  IN     UINT64  RpBase
  );

/**
  Translate PCIe Port/Lane pair to 0-based PCIe lane number.

  @param[in] RpIndex    Root Port index
  @param[in] RpLane     Root Port Lane (0-3)

  @retval PCIe lane number (0-based)
**/
UINT32
CpuPciePhysicalLane (
  UINT32 RpIndex,
  UINT32 RpLane
  );

/**
  Checks if lane reversal is enabled on a given root port

  @param[in] RpIndex  Root port index (0-based)

  @retval TRUE if lane reversal is enbabled, FALSE otherwise
**/
BOOLEAN
IsPcieLaneReversalEnabled (
  IN     UINT32  RpIndex
  );

/**
  Get current PCIe link speed.

  @param[in] RpBase    Root Port base address
  @return Link speed
**/
UINT32
GetLinkSpeed (
  UINT64  RpBase
  );

/**
  Get max PCIe link speed supported by the root port.

  @param[in] RpBase    Root Port pci segment base address
  @return Max link speed
**/
UINT32
CpuPcieGetMaxLinkSpeed (
  UINT64 RpBase
  );

#endif // _PEI_DXE_SMM_PCH_PCI_EXPRESS_HELPERS_LIB_H_

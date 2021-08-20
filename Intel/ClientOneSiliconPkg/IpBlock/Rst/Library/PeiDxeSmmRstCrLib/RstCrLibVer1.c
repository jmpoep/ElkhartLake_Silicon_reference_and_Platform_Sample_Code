/** @file
  Rst Cycle Router library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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
#include <Library/RstCrLib.h>
#include <Library/PchInfoLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mPchLpRstPcieStorageSupportedPort[] = {
  RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID,   // RP1..RP4
  RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID,   // RP5..RP8
  RST_PCIE_STORAGE_CR_2,       RST_PCIE_STORAGE_CR_2,       RST_PCIE_STORAGE_CR_2,       RST_PCIE_STORAGE_CR_2,         // RP9..RP12
  RST_PCIE_STORAGE_CR_3,       RST_PCIE_STORAGE_CR_3,       RST_PCIE_STORAGE_CR_3,       RST_PCIE_STORAGE_CR_3          // RP13..RP16
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT8 mPchHRstPcieStorageSupportedPort[] = {
  RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID,   // RP1..RP4
  RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID,   // RP5..RP8
  RST_PCIE_STORAGE_CR_1,       RST_PCIE_STORAGE_CR_1,       RST_PCIE_STORAGE_CR_1,       RST_PCIE_STORAGE_CR_1,         // RP9..RP12
  RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID, RST_PCIE_STORAGE_CR_INVALID,   // RP13..RP16
  RST_PCIE_STORAGE_CR_3,       RST_PCIE_STORAGE_CR_3,       RST_PCIE_STORAGE_CR_3,       RST_PCIE_STORAGE_CR_3,         // RP17..RP20
  RST_PCIE_STORAGE_CR_2,       RST_PCIE_STORAGE_CR_2,       RST_PCIE_STORAGE_CR_2,       RST_PCIE_STORAGE_CR_2          // RP21..RP24
};

/**
  Check the RST PCIe Storage Cycle Router number according to the root port number and PCH type

  @param[in] RootPortNum  Root Port Number

  @return  The RST PCIe Storage Cycle Router Number
**/
UINT8
RstGetCycleRouterNumber (
  IN  UINT32                   RootPortNum
  )
{
  if (IsPchLp ()) {
    if (RootPortNum < ARRAY_SIZE (mPchLpRstPcieStorageSupportedPort)) {
      return mPchLpRstPcieStorageSupportedPort[RootPortNum];
    }
  } else if (IsPchH ()) {
    if (RootPortNum < ARRAY_SIZE (mPchHRstPcieStorageSupportedPort)) {
      return mPchHRstPcieStorageSupportedPort[RootPortNum];
    }
  }
  return RST_PCIE_STORAGE_CR_INVALID;
}
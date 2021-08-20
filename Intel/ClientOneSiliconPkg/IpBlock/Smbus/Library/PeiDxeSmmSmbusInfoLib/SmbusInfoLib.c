/** @file
  Smbus Info Library

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
#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/IoLib.h>
#include <Register/SmbusRegs.h>
#include <Register/PchRegs.h>

/**
  Return Smbus Device Number

  @retval Smbus Device Number
**/
UINT8
SmbusDevNumber (
  VOID
  )
{
  return PCI_DEVICE_NUMBER_PCH_SMBUS;
}

/**
  Return Smbus Function Number

  @retval  Smbus Function Number
**/
UINT8
SmbusFuncNumber (
  VOID
  )
{
  return PCI_FUNCTION_NUMBER_PCH_SMBUS;
}

/**
  This function checks if SMBUS Host Lock is set

  @retval SMBUS host Hock state
**/
BOOLEAN
SmbusIsHostLocked (
  VOID
  )
{
  UINT32 Hostc;
  UINT64 SmbusPciBase;
  SmbusPciBase = PCI_SEGMENT_LIB_ADDRESS (
                   DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_SMBUS,
                   PCI_FUNCTION_NUMBER_PCH_SMBUS,
                   0
                   );
  Hostc = PciSegmentRead32 (SmbusPciBase + R_SMBUS_CFG_HOSTC);
  return !!(Hostc & B_SMBUS_CFG_HOSTC_SPDWD);
}

/**
  This function clears the Smbus Status Register
**/
VOID
SmbusClearStatusReg (
  VOID
  )
{
  UINT16 SmbusIoBase;
  UINT64 SmbusPciBase;
  SmbusPciBase = PCI_SEGMENT_LIB_ADDRESS (
                   DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_SMBUS,
                   PCI_FUNCTION_NUMBER_PCH_SMBUS,
                   0
                   );
  SmbusIoBase = PciSegmentRead16 (SmbusPciBase + R_SMBUS_CFG_BASE) & B_SMBUS_CFG_BASE_BAR;
  IoWrite8 (SmbusIoBase + R_SMBUS_IO_HSTS, B_SMBUS_IO_HSTS_ALL);
}


/** @file
  This file provides P2SB Public Library implementation

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2020 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <IndustryStandard/Pci30.h>
#include <Library/PciSegmentLib.h>
#include <Register/PchRegs.h>
#include <Register/P2sbRegs.h>

/**
  Get P2SB PCI device number

  @retval PCI dev number
**/
UINT8
P2sbDevNumber (
  VOID
  )
{
  return PCI_DEVICE_NUMBER_PCH_P2SB;
}

/**
  Get P2SB PCI function number

  @retval PCI fun number
**/
UINT8
P2sbFuncNumber (
  VOID
  )
{
  return PCI_FUNCTION_NUMBER_PCH_P2SB;
}

/**
  Hide or unhide the P2SB device

  @param[in]    P2sbBase  Base address of P2SB config space
  @param[in]    Hide  Whether to hide or unhide the device

  @retval       Success or failure
**/
STATIC INT32
P2sbHideDevice (
    IN UINT64 P2sbBase,
    IN BOOLEAN Hide
    )
{
  UINT8 E1RegValue;
  UINT16 VendorID;

  E1RegValue = (Hide == 1) ? BIT0 : 0x0;
  PciSegmentWrite8 (P2sbBase + R_P2SB_CFG_E0 + 1, E1RegValue);

  /* Paranoia: Check if the bit write has the desired effect */
  VendorID = PciSegmentRead16 (P2sbBase + PCI_VENDOR_ID_OFFSET);
  if ((Hide && VendorID != 0xFFFF) || (!Hide && VendorID == 0xFFFF)) {
    PciSegmentWrite8 (P2sbBase + R_P2SB_CFG_E0 + 1, BIT0);
    return -1;
  }

  return 0;
}

/**
  Get P2SB EPMASK setting
  Note: after end of pei this function can be used only in SMM

  @param[in]    EpMaskNum  EPMASK number

  @retval       EPMASKx setting
**/
UINT32
P2sbGetEpmask (
  IN UINT32  EpMaskNum
  )
{
  UINT32 EpMaskValue;
  UINT64 P2sbBase;

  P2sbBase = PCI_SEGMENT_LIB_ADDRESS (
               DEFAULT_PCI_SEGMENT_NUMBER_PCH,
               DEFAULT_PCI_BUS_NUMBER_PCH,
               P2sbDevNumber (),
               P2sbFuncNumber (),
               0
               );

  /*
   * P2SB is hidden by SiInit, so, unhide P2SB, read the register masks
   * and then hide the device again.
   */

  if (P2sbHideDevice (P2sbBase, FALSE)) {
    return 0;
  }

  switch (EpMaskNum) {
  case 5:
    EpMaskValue = PciSegmentRead32 (P2sbBase + R_P2SB_CFG_EPMASK5);
    break;
  case 7:
    EpMaskValue = PciSegmentRead32 (P2sbBase + R_P2SB_CFG_EPMASK7);
    break;
  default:
    EpMaskValue = 0;
    break;
  }

  if (P2sbHideDevice (P2sbBase, TRUE)) {
    EpMaskValue = 0;
  }
  return EpMaskValue;
}

/**
  Check P2SB EPMASK is locked
  Note: after end of pei this function can be used only in SMM

  @retval TRUE  P2SB EPMASK is locked
          FALSE P2SB EPMASK is not locked
**/
BOOLEAN
P2sbIsEpmaskLock (
  VOID
  )
{
  UINT64 P2sbBase;
  BOOLEAN Status;

  P2sbBase = PCI_SEGMENT_LIB_ADDRESS (
               DEFAULT_PCI_SEGMENT_NUMBER_PCH,
               DEFAULT_PCI_BUS_NUMBER_PCH,
               P2sbDevNumber (),
               P2sbFuncNumber (),
               0
               );

  if (P2sbHideDevice (P2sbBase, FALSE)) {
    return FALSE;
  }

  Status = !!(PciSegmentRead8 (P2sbBase + R_P2SB_CFG_E0 + 2) & BIT1);

  if (P2sbHideDevice (P2sbBase, TRUE)) {
    Status =  FALSE;
  }

  return Status;
}

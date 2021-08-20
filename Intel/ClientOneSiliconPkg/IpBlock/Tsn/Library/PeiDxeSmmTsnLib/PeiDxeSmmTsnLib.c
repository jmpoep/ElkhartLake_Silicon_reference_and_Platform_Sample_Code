/** @file
  TSN Library.
  All function in this library is available for PEI, DXE, and SMM
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include <Register/TsnRegs.h>
#include <Library/TsnLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchInfoLib.h>
#include <Register/PchRegs.h>
#include <IndustryStandard/Pci30.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>

/**
  Check whether TSN controller is enabled in the platform.

  @retval TRUE                    TSN is enabled
  @retval FALSE                   TSN is disabled
**/
BOOLEAN
IsTsnPresent (
  VOID
  )
{
  UINTN  PchTsnBase;
  UINT16 DeviceId;
  UINT16 VendorId;

  PchTsnBase = 0;
  DeviceId   = 0;
  VendorId   = 0;
  //
  // Check PCH Support
  //
  if (!PchIsTsnSupported ()) {
    return FALSE;
  }

  PchTsnBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PchTsnDevNumber (),
                 PchTsnFuncNumber (),
                 0
                 );
  DeviceId = PciSegmentRead16 (PchTsnBase + PCI_DEVICE_ID_OFFSET);
  VendorId = PciSegmentRead16 (PchTsnBase + PCI_VENDOR_ID_OFFSET);

  DEBUG ((DEBUG_INFO, "TSN Device: Device Id: 0x%4X, Vendor Id: 0x%4X\n", DeviceId, VendorId));
  if ((DeviceId == 0xFFFF) || (VendorId == 0xFFFF)) {
    return FALSE;
  }

  return TRUE;
}

/**
  Returns Pch TSN GBE PCI Device Number

  @retval  Pch Tsn device number
**/
UINT8
PchTsnDevNumber (
  VOID
  )
{
  return PCI_DEVICE_NUMBER_PCH_TSN;
}

/**
  Returns Pch TSN GBE PCI Function Number

  @retval Pch Tsn GbE function number
**/
UINT8
PchTsnFuncNumber (
  VOID
  )
{
  return PCI_FUNCTION_NUMBER_PCH_TSN;
}

/**
  Returns PSE TSN GBE PCI Device Number

  @retval  Pse Tsn GbE device number
**/
UINT8
PseTsnDevNumber (
  IN UINT8       PseTsnIndex
  )
{
  ASSERT (PseTsnIndex < GetPchMaxPseGbeControllersNum ());
  return PseTsnIndex == 0 ? PCI_DEVICE_NUMBER_PSE_TSN0 : PCI_DEVICE_NUMBER_PSE_TSN1;
}

/**
  Returns PSE TSN GBE PCI Function Number

  @retval Pse Tsn GbE function number
**/
UINT8
PseTsnFuncNumber (
  IN UINT8       PseTsnIndex
  )
{
  ASSERT (PseTsnIndex < GetPchMaxPseGbeControllersNum ());
  return PseTsnIndex == 0 ? PCI_FUNCTION_NUMBER_PSE_TSN0 : PCI_FUNCTION_NUMBER_PSE_TSN1;
}

/**
  Check whether PSE TSN controller is present in the platform.

  @retval TRUE                    TSN is enabled
  @retval FALSE                   TSN is disabled
**/
BOOLEAN
IsPseTsnPresent (
  IN UINT8       PseTsnIndex
  )
{
  UINTN  PseTsnBase;
  UINT16 DeviceId;
  UINT16 VendorId;

  PseTsnBase = 0;
  DeviceId   = 0;
  VendorId   = 0;

  PseTsnBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PseTsnDevNumber (PseTsnIndex),
                 PseTsnFuncNumber (PseTsnIndex),
                 0
                 );
  DeviceId = PciSegmentRead16 (PseTsnBase + PCI_DEVICE_ID_OFFSET);
  VendorId = PciSegmentRead16 (PseTsnBase + PCI_VENDOR_ID_OFFSET);

  DEBUG ((DEBUG_INFO, "PSE TSN Device: Device Id: 0x%4X, Vendor Id: 0x%4X\n", DeviceId, VendorId));
  if ((DeviceId == 0xFFFF) || (VendorId == 0xFFFF)) {
    return FALSE;
  }

  return TRUE;
}

/**
  Checks if TSN is Enabled or Disabled

  @retval  BOOLEAN    TRUE if device is enabled, FALSE otherwise.
**/
BOOLEAN
IsPchTsnEnabled (
  VOID
  )
{
  UINT64  TsnPciBase;

  TsnPciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PchTsnDevNumber (),
                 PchTsnFuncNumber (),
                 0
                 );

  if (PciSegmentRead32 (TsnPciBase) != 0xFFFFFFFF) {
    return TRUE;
  }

  return FALSE;
}

/** @file
  Pch SATA library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchInfoLib.h>
#include <Library/SataLib.h>
#include <Register/PchRegs.h>
#include <Register/SataRegs.h>

/**
  Get SATA controller address that can be passed to the PCI Segment Library functions.

  @param[in]  SataCtrlIndex       SATA controller index

  @retval SATA controller address in PCI Segment Library representation
**/
UINT64
SataRegBase (
  IN UINT32  SataCtrlIndex
  )
{
  ASSERT (SataCtrlIndex < MaxSataControllerNum ());

  return PCI_SEGMENT_LIB_ADDRESS (
           DEFAULT_PCI_SEGMENT_NUMBER_PCH,
           DEFAULT_PCI_BUS_NUMBER_PCH,
           SataDevNumber (SataCtrlIndex),
           SataFuncNumber (SataCtrlIndex),
           0
           );
}

/**
  Get SATA controller's Port Present Status

  @param[in]  SataCtrlIndex       SATA controller index

  @retval     Port Present Status
**/
UINT8
GetSataPortPresentStatus (
  IN UINT32  SataCtrlIndex
  )
{
  ASSERT (SataCtrlIndex < MaxSataControllerNum ());

  return PciSegmentRead8 (PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, SataDevNumber (SataCtrlIndex), SataFuncNumber (SataCtrlIndex), R_SATA_CFG_PCS + 2));
}

/**
  Get SATA controller Function Disable Status

  @param[in]  SataCtrlIndex       SATA controller index

  @retval 0 SATA Controller is not Function Disabled
  @retval 1 SATA Controller is Function Disabled
**/
BOOLEAN
SataControllerFunctionDisableStatus (
  IN UINT32  SataCtrlIndex
  )
{
  UINT32 SataGc;
  ASSERT (SataCtrlIndex < MaxSataControllerNum ());
  SataGc = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, SataDevNumber (SataCtrlIndex), SataFuncNumber (SataCtrlIndex), R_SATA_CFG_SATAGC));
  return !!(SataGc & BIT10);
}

/**
  Get SATA controller ABAR size

  @param[in]  SataCtrlIndex       SATA controller index

  @retval SATA controller ABAR size
**/
UINT32
GetSataAbarSize (
  IN UINT32  SataCtrlIndex
  )
{
  UINT32 SataGc;
  ASSERT (SataCtrlIndex < MaxSataControllerNum ());
  SataGc = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, SataDevNumber (SataCtrlIndex), SataFuncNumber (SataCtrlIndex), R_SATA_CFG_SATAGC));

  switch (SataGc & B_SATA_CFG_SATAGC_ASSEL) {
    case V_SATA_CFG_SATAGC_ASSEL_2K:
      return SIZE_2KB;
      break;

    case V_SATA_CFG_SATAGC_ASSEL_16K:
      return SIZE_16KB;
      break;

    case V_SATA_CFG_SATAGC_ASSEL_32K:
      return SIZE_32KB;
      break;

    case V_SATA_CFG_SATAGC_ASSEL_64K:
      return SIZE_64KB;
      break;

    case V_SATA_CFG_SATAGC_ASSEL_128K:
      return SIZE_128KB;
      break;

    case V_SATA_CFG_SATAGC_ASSEL_512K:
      return SIZE_256KB;
      break;

    default:
      return SIZE_2KB;
      break;
  }
}

/**
  Get SATA controller AHCI base address

  @param[in]  SataCtrlIndex       SATA controller index

  @retval SATA controller AHCI base address
**/
UINT32
GetSataAhciBase (
  IN UINT32  SataCtrlIndex
  )
{
  ASSERT (SataCtrlIndex < MaxSataControllerNum ());

  return PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (DEFAULT_PCI_SEGMENT_NUMBER_PCH, DEFAULT_PCI_BUS_NUMBER_PCH, SataDevNumber (SataCtrlIndex), SataFuncNumber (SataCtrlIndex), R_SATA_CFG_AHCI_BAR)) & 0xFFFFF800;
}


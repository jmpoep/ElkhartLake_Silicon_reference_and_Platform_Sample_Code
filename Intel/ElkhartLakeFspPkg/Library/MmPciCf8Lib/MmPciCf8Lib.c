/** @file
  This file contains routines that get PCI Express Address through I/O Ports CF8 and CFC

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2017 Intel Corporation.

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
#include <Library/BaseLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>

#define PCIEX_BAR_REG          0x80000060     // B0:D0:F0:R60
#define PCIEX_BAR_EN_MASK      0x1
#define PCIEX_BAR_LENGTH_MASK  0x6
#define PCIEX_BAR_ADDR_MASK    0x7FFC000000

/**
  This procedure will get PCIE address

  @param[in] Bus                  Pci Bus Number
  @param[in] Device               Pci Device Number
  @param[in] Function             Pci Function Number

  @retval PCIE address
**/
UINTN
MmPciBase (
  IN UINT32                       Bus,
  IN UINT32                       Device,
  IN UINT32                       Function
  )
{
  UINT64 PciExpressBaseValue = 0;
  BOOLEAN  InterruptState;

  ASSERT ((Bus <= 0xFF) && (Device <= 0x1F) && (Function <= 0x7));
  //
  //  Get PciExpressBaseAddress from PCIEX_BAR_REG (B0:D0:F0:R60)
  //
  InterruptState = SaveAndDisableInterrupts ();
  IoWrite32(0xCF8, PCIEX_BAR_REG);
  PciExpressBaseValue = IoRead32(0xCFC);
  SetInterruptState (InterruptState);
  ASSERT ((PciExpressBaseValue & PCIEX_BAR_EN_MASK) == 1);

  return ((UINTN) (PciExpressBaseValue & PCIEX_BAR_ADDR_MASK) + (UINTN) (Bus << 20) + (UINTN) (Device << 15) + (UINTN) (Function << 12));
}

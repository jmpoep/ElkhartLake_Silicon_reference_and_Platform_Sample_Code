/** @file
  Source file for FSP PCD Init PEI module

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

@par Specification
**/

#include <Library/PeiServicesLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>

#define PCIEX_BAR_REG 0x80000060     // B0:D0:F0:R60
#define PCIEX_BAR_EN_MASK  0x1
#define PCIEX_BAR_LENGTH_MASK  0xE
#define PCIEX_BAR_ADDR_MASK  0x7FFC000000

/**
  FSP PCD Init PEI module entry point

  @param[in]  FileHandle           Not used.
  @param[in]  PeiServices          General purpose services available to every PEIM.

  @retval     EFI_SUCCESS          The function completes successfully
  @retval     EFI_OUT_OF_RESOURCES Insufficient resources to create database
**/
EFI_STATUS
EFIAPI
FspPcdInitEntryPoint (
  IN       EFI_PEI_FILE_HANDLE    FileHandle,
  IN CONST EFI_PEI_SERVICES       **PeiServices
  )
{
  UINT64       PciExBarRegValue;
  UINT8        BarLength;
  BOOLEAN      InterruptState;

  InterruptState = SaveAndDisableInterrupts ();
  IoWrite32(0xCF8, PCIEX_BAR_REG);
  PciExBarRegValue = IoRead32(0xCFC);
  SetInterruptState (InterruptState);
  if ((PciExBarRegValue & PCIEX_BAR_EN_MASK) == 1) {
    PcdSetEx64 (&gSiPkgTokenSpaceGuid, PcdSiPciExpressBaseAddress, (PciExBarRegValue & PCIEX_BAR_ADDR_MASK));
    BarLength = (UINT8) (PciExBarRegValue & PCIEX_BAR_LENGTH_MASK);
    BarLength = BarLength >> 1;
    if (BarLength == 0) {
      PcdSetEx32 (&gSiPkgTokenSpaceGuid, PcdPciExpressRegionLength, SIZE_256MB);
    } else if (BarLength == 1) {
      PcdSetEx32 (&gSiPkgTokenSpaceGuid, PcdPciExpressRegionLength, SIZE_128MB);
    } else if (BarLength == 2) {
      PcdSetEx32 (&gSiPkgTokenSpaceGuid, PcdPciExpressRegionLength, SIZE_64MB);
    } else if (BarLength == 3) {
      PcdSetEx32 (&gSiPkgTokenSpaceGuid, PcdPciExpressRegionLength, SIZE_512MB);
    } else if (BarLength == 4) {
      PcdSetEx32 (&gSiPkgTokenSpaceGuid, PcdPciExpressRegionLength, SIZE_1GB);
    } else if (BarLength == 5) {
      PcdSetEx32 (&gSiPkgTokenSpaceGuid, PcdPciExpressRegionLength, SIZE_2GB);
    }
    DEBUG ((DEBUG_INFO, "FspPcdInitEntryPoint() - Updating PcdPciExpressRegionLength to 0x%x & PcdPciExpressBaseAddress to 0x%x\n",
            PcdGet32(PcdPciExpressRegionLength), PcdGet64(PcdSiPciExpressBaseAddress)));
  } else {
    DEBUG ((DEBUG_INFO, "FspPcdInitEntryPoint() - ERROR PciExpressBaseAddress not programmed\n" ));
    ASSERT ((PciExBarRegValue & PCIEX_BAR_EN_MASK) == 1);
  }
  return EFI_SUCCESS;
}

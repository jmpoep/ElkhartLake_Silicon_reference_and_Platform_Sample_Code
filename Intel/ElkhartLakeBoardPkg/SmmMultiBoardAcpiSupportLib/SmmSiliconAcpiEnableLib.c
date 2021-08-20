/** @file
  SMM Silicon ACPI Support Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <Uefi.h>
#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/IoLib.h>
#include <Library/BoardAcpiEnableLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/MmPciLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PmcLib.h>
#include <Register/PchRegs.h>
#include <Register/PchRegsLpc.h>
#include <Register/PmcRegs.h>
#include <Register/RtcRegs.h>

//
// Global variables
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_SMM_SYSTEM_TABLE2                     *mSmst;

GLOBAL_REMOVE_IF_UNREFERENCED UINT16                                    mAcpiBaseAddr;

/**

**/
EFI_STATUS
EFIAPI
SiliconEnableAcpi (
  IN BOOLEAN  EnableSci
  )
{
  UINT32                              OutputValue;
  UINT32                              SmiEn;
  UINT32                              SmiSts;
  UINT32                              ULKMC;
  UINT32                              Pm1Cnt;
  EFI_STATUS                          Status;
  UINT64                              LpcBaseAddress;

  LpcBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                     DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_LPC,
                     PCI_FUNCTION_NUMBER_PCH_LPC,
                     0
                     );

  //
  // Initialize global variables
  //
  mSmst = gSmst;

  //
  // Get the ACPI Base Address
  //
  mAcpiBaseAddr = PmcGetAcpiBase ();

  Status = EFI_SUCCESS;
  //
  // BIOS must also ensure that CF9GR is cleared and locked before handing control to the
  // OS in order to prevent the host from issuing global resets and resetting ME
  //
  // EDK2: To match PCCG current BIOS behavior, do not lock CF9 Global Reset
  // MmioWrite32 (
  //     PmcBaseAddress + R_PCH_PMC_ETR3),
  //     PmInit);

  //
  // Clear Port 80h
  //
  OutputValue = 0;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT16, 0x80, 1, &OutputValue);
  //
  // Disable SW SMI Timer and clean the status
  //
  mSmst->SmmIo.Io.Read (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_SMI_EN, 1, &SmiEn);
  SmiEn &= ~(B_ACPI_IO_SMI_EN_LEGACY_USB2 | B_ACPI_IO_SMI_EN_SWSMI_TMR | B_ACPI_IO_SMI_EN_LEGACY_USB);
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_SMI_EN, 1, &SmiEn);

  mSmst->SmmIo.Io.Read (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_SMI_STS, 1, &SmiSts);
  SmiSts |= B_ACPI_IO_SMI_EN_LEGACY_USB2 | B_ACPI_IO_SMI_EN_SWSMI_TMR | B_ACPI_IO_SMI_EN_LEGACY_USB;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_SMI_STS, 1, &SmiSts);

  //
  // Disable port 60/64 SMI trap if they are enabled
  //
  ULKMC = PciSegmentRead32 (LpcBaseAddress + R_LPC_CFG_ULKMC);
  ULKMC &= ~(B_LPC_CFG_ULKMC_60REN | B_LPC_CFG_ULKMC_60WEN | B_LPC_CFG_ULKMC_64REN | B_LPC_CFG_ULKMC_64WEN | B_LPC_CFG_ULKMC_A20PASSEN);
  PciSegmentWrite32 (LpcBaseAddress + R_LPC_CFG_ULKMC, ULKMC);

  //
  // Disable PM sources except power button
  //
  OutputValue = B_ACPI_IO_PM1_EN_PWRBTN;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT16, mAcpiBaseAddr + R_ACPI_IO_PM1_EN, 1, &OutputValue);
  //
  // Clear PM status except Power Button status for RapidStart Resume
  //
  // OutputValue = 0xFFFF;
  OutputValue = 0xFEFF;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT16, mAcpiBaseAddr + R_ACPI_IO_PM1_STS, 1, &OutputValue);

  //
  // Guarantee day-of-month alarm is invalid (ACPI 1.0 section 4.7.2.4)
  //
  OutputValue = R_RTC_IO_REGD;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT8, R_RTC_IO_INDEX_ALT, 1, &OutputValue);
  OutputValue = 0x0;
  mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT8, R_RTC_IO_TARGET_ALT, 1, &OutputValue);

  //
  // Enable SCI
  //
  if (EnableSci) {
    mSmst->SmmIo.Io.Read (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_PM1_CNT, 1, &Pm1Cnt);
    Pm1Cnt |= B_ACPI_IO_PM1_CNT_SCI_EN;
    mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_PM1_CNT, 1, &Pm1Cnt);
  }

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
SiliconDisableAcpi (
  IN BOOLEAN  DisableSci
  )
{
  UINT32      Pm1Cnt;

  //
  // Initialize global variables
  //
  mSmst = gSmst;

  //
  // Get the ACPI Base Address
  //
  mAcpiBaseAddr = PmcGetAcpiBase ();


  //
  // Disable SCI
  //
  if (DisableSci) {
    mSmst->SmmIo.Io.Read (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_PM1_CNT, 1, &Pm1Cnt);
    Pm1Cnt &= ~B_ACPI_IO_PM1_CNT_SCI_EN;
    mSmst->SmmIo.Io.Write (&mSmst->SmmIo, SMM_IO_UINT32, mAcpiBaseAddr + R_ACPI_IO_PM1_CNT, 1, &Pm1Cnt);
  }

  return EFI_SUCCESS;
}

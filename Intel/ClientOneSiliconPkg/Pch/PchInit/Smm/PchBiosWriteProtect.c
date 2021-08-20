/** @file
  PCH BIOS Write Protect Driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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
#include "PchInitSmm.h"
#include <Register/PchRegs.h>
#include <Register/PchRegsLpc.h>
#include <Register/SpiRegs.h>
#include <Library/SpiAccessPrivateLib.h>

//
// Global variables
//
GLOBAL_REMOVE_IF_UNREFERENCED PCH_TCO_SMI_DISPATCH_PROTOCOL     *mPchTcoSmiDispatchProtocol;
GLOBAL_REMOVE_IF_UNREFERENCED PCH_ESPI_SMI_DISPATCH_PROTOCOL    *mEspiSmmDispatchProtocol;
GLOBAL_REMOVE_IF_UNREFERENCED UINT64                            mLpcRegBase;

/**
  This hardware SMI handler will be run every time the BIOS Write Enable bit is set.

  @param[in] DispatchHandle       Not used
**/
VOID
EFIAPI
PchSpiBiosWpCallback (
  IN  EFI_HANDLE                              DispatchHandle
  )
{
  SpiClearBiosWriteProtectDisable ();
}

/**
  This hardware SMI handler will be run every time the BIOS Write Enable bit is set.

  @param[in] DispatchHandle       Not used

**/
VOID
EFIAPI
PchLpcBiosWpCallback (
  IN  EFI_HANDLE                              DispatchHandle
  )
{
  //
  // Disable BIOSWE bit to protect BIOS
  //
  PciSegmentAnd8 ((UINTN) (mLpcRegBase + R_LPC_CFG_BC), (UINT8) ~B_LPC_CFG_BC_WPD);
}

/**
  Entry point for Pch Bios Write Protect driver.

  @param[in] ImageHandle          Image handle of this driver.
  @param[in] SystemTable          Global system service table.

  @retval EFI_SUCCESS             Initialization complete.
**/
EFI_STATUS
EFIAPI
InstallPchBiosWriteProtect (
  IN EFI_HANDLE            ImageHandle,
  IN EFI_SYSTEM_TABLE      *SystemTable
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              Handle;

  DEBUG ((DEBUG_INFO, "InstallPchBiosWriteProtect()\n"));

  if (mPchConfigHob->LockDown.BiosLock != TRUE) {
    return EFI_SUCCESS;
  }

  mLpcRegBase = PCI_SEGMENT_LIB_ADDRESS (
                   DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_LPC,
                   PCI_FUNCTION_NUMBER_PCH_LPC,
                   0
                   );

  DEBUG ((DEBUG_INFO, "Installing BIOS Write Protect SMI handler\n"));
  //
  // Get the PCH TCO SMM dispatch protocol
  //
  mPchTcoSmiDispatchProtocol = NULL;
  Status = gSmst->SmmLocateProtocol (&gPchTcoSmiDispatchProtocolGuid, NULL, (VOID **) &mPchTcoSmiDispatchProtocol);
  ASSERT_EFI_ERROR (Status);
  //
  // Always register an SPI BiosWp callback function to handle TCO BIOSWR SMI
  // NOTE: No matter the BIOS resides behind SPI or not, it needs to handle the SPI BIOS WP SMI
  //       to avoid SMI deadloop on SPI WPD write.
  //
  Handle = NULL;
  Status = mPchTcoSmiDispatchProtocol->SpiBiosWpRegister (
                                         mPchTcoSmiDispatchProtocol,
                                         PchSpiBiosWpCallback,
                                         &Handle
                                         );
  ASSERT_EFI_ERROR (Status);

  //
  // Always register an LPC/eSPI BiosWp callback function to handle TCO BIOSWR SMI
  // NOTE: No matter the BIOS resides behind LPC/eSPI or not, it needs to handle the BIOS WP SMI
  //       to avoid SMI deadloop on LPC/eSPI WPD write.
  //
  if (IsEspiEnabled ()) {
    //
    // Get the PCH ESPI SMM dispatch protocol
    //
    mEspiSmmDispatchProtocol = NULL;
    Status = gSmst->SmmLocateProtocol (&gPchEspiSmiDispatchProtocolGuid, NULL, (VOID **) &mEspiSmmDispatchProtocol);
    ASSERT_EFI_ERROR (Status);

    //
    // Register an ESpiBiosWp callback function to handle BIOSWR SMI
    //
    Handle = NULL;
    Status = mEspiSmmDispatchProtocol->BiosWrProtectRegister (
                                         mEspiSmmDispatchProtocol,
                                         PchLpcBiosWpCallback,
                                         &Handle
                                         );
    ASSERT_EFI_ERROR (Status);
  } else {
    //
    // Register an LPC BiosWp callback function to handle TCO BIOSWR SMI
    //
    Handle = NULL;
    Status = mPchTcoSmiDispatchProtocol->LpcBiosWpRegister (
                                           mPchTcoSmiDispatchProtocol,
                                           PchLpcBiosWpCallback,
                                           &Handle
                                           );
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}


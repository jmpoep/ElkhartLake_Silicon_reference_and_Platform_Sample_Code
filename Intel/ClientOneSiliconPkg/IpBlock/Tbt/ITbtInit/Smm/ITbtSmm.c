/** @file
  ITBT Smm driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

//
// Module specific Includes
//
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/GpioLib.h>
#include <ITbtInfoHob.h>
#include <Protocol/ITbtNvsArea.h>
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchInfoLib.h>
#include <Library/IoLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Uefi/UefiSpec.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Guid/HobList.h>
#include "ITbtSmiHandler.h"
#include <SaRegs.h>
#include <Protocol/SaPolicy.h>
#include <Protocol/ITbtPolicy.h>
#include <Library/ItbtPcieRpLib.h>
#include <Library/ConfigBlockLib.h>

#define DISBL_IO_REG1C                0x01F1
#define DISBL_MEM32_REG20             0x0000FFF0
#define DISBL_PMEM_REG24              0x0001FFF1

#define PCI_CAPABILITY_ID_PCIEXP      0x10
#define PCI_CAPBILITY_POINTER_OFFSET  0x34

GLOBAL_REMOVE_IF_UNREFERENCED ITBT_NVS_AREA               *mITbtNvsAreaPtr;
GLOBAL_REMOVE_IF_UNREFERENCED UINT8                       gCurrentIntegratedTbtRootPort;
GLOBAL_REMOVE_IF_UNREFERENCED ITBT_INFO_HOB               *gITbtInfoHob = NULL;
STATIC UINTN                                              mPciExpressBaseAddress;

VOID
ITbtSwSmiCallback (
  VOID
  )
{
  UINT8 ThunderboltSmiFunction;

  DEBUG ((DEBUG_INFO, "ITbtSwSmiCallback Entry\n"));

  ThunderboltSmiFunction = mITbtNvsAreaPtr->ThunderboltSmiFunction;
  DEBUG ((DEBUG_INFO, "ITbtSwSmiCallback. ThunderboltSmiFunction=%d\n", ThunderboltSmiFunction));
  gCurrentIntegratedTbtRootPort = mITbtNvsAreaPtr->CurrentIntegratedTbtRootPort;

  switch (ThunderboltSmiFunction) {
  case 21:
    ITbtCallback ();
    break;

  case 22:
    ITbtDisablePCIDevicesAndBridges ();
    break;

  default:
    break;
  }
  DEBUG ((DEBUG_INFO, "ITbtSwSmiCallback Exit.\n"));
}

STATIC
EFI_STATUS
EFIAPI
IntegratedThunderboltSwSmiCallback (
  IN EFI_HANDLE                     DispatchHandle,
  IN  CONST VOID                    *DispatchContext,
  IN  OUT VOID                      *CommBuffer OPTIONAL,
  IN  UINTN                         *CommBufferSize OPTIONAL
  )
{
  ITbtSwSmiCallback();

  return EFI_SUCCESS;
}

EFI_STATUS
ITbtRegisterHandlers (
  VOID
  )
{
  EFI_STATUS                    Status;
  UINTN                         SmiInputValue;
  EFI_SMM_HANDLER_ENTRY_POINT2   SwHandler;
  EFI_SMM_SW_DISPATCH2_PROTOCOL *SwDispatch;
  EFI_SMM_SW_REGISTER_CONTEXT   SwContext;
  EFI_HANDLE                    SwDispatchHandle;

  Status = EFI_UNSUPPORTED;

  SwHandler = IntegratedThunderboltSwSmiCallback;
  SmiInputValue = PcdGet8 (PcdSwSmiITbtEnumerate);

  SwDispatchHandle        = NULL;
  //
  // Locate the SMM SW dispatch protocol
  //
  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmSwDispatch2ProtocolGuid,
                    NULL,
                    (VOID **) &SwDispatch
                    );

  ASSERT_EFI_ERROR (Status);
  //
  // Register SWSMI handler
  //
  SwContext.SwSmiInputValue = SmiInputValue;
  Status = SwDispatch->Register (
                        SwDispatch,
                        SwHandler,
                        &SwContext,
                        &SwDispatchHandle
                        );
  ASSERT_EFI_ERROR (Status);

  return Status;
}
EFI_STATUS
InSmmFunction (
  IN  EFI_HANDLE        ImageHandle,
  IN  EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                    Status;
  UINT8                         Index;

  Status = EFI_SUCCESS;

  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index ++) {
    if (gITbtInfoHob->ITbtRootPortConfig[Index].ITbtPcieRootPortEn == 1) {
      Status = ITbtRegisterHandlers();
      break;
    }
  }

  return Status;
}

EFI_STATUS
EFIAPI
ITbtSmmEntryPoint (
  IN EFI_HANDLE               ImageHandle,
  IN EFI_SYSTEM_TABLE         *SystemTable
  )
{
  ITBT_NVS_AREA_PROTOCOL        *ITbtNvsAreaProtocol;
  EFI_STATUS                    Status;

  DEBUG ((DEBUG_INFO, "ITbtSmmEntryPoint\n"));

  mPciExpressBaseAddress = PcdGet64 (PcdSiPciExpressBaseAddress);
  //
  // Locate ITbt shared data area
  //
  Status = gBS->LocateProtocol (&gITbtNvsAreaProtocolGuid, NULL, (VOID **) &ITbtNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);
  mITbtNvsAreaPtr = ITbtNvsAreaProtocol->Area;

  //
  // Get ITBT INFO HOB
  //
  gITbtInfoHob = (ITBT_INFO_HOB *) GetFirstGuidHob (&gITbtInfoHobGuid);
  if (gITbtInfoHob == NULL) {
    return EFI_NOT_FOUND;
  }

  return InSmmFunction (ImageHandle, SystemTable);
}

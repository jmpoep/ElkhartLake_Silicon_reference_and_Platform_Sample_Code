/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2008 - 2017 Intel Corporation.

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

#include "MeUlvCheck.h"

/**
  Entry point for the driver.
  Perform Check for ULV mismatch (ULV PCH not paired with ULV/LV CPU)
  In case of mismatch reported by FW, wait for ConsoleOut to initialize to warn user
  and stop booting process.

  @param[in]  ImageHandle  Image Handle.
  @param[in]  SystemTable  EFI System Table.

  @retval     EFI_SUCCESS  Function has completed successfully.
  @retval     Others       All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
EFIAPI
MeUlvCheckEntryPoint (
  IN EFI_HANDLE               ImageHandle,
  IN EFI_SYSTEM_TABLE         *SystemTable
  )
{
  EFI_EVENT                       ConOutInitEvent;
  EFI_STATUS                      Status;
  HECI_FWS_REGISTER               MeFirmwareStatus;
  BOOLEAN                         HeciDisabled = FALSE;
  ME_FW_HOB                       *MeFwHob;
  UINT32                          Index;

  DEBUG ((DEBUG_INFO, "MeUlvCheckEntryPoint start\n"));

  Status          = EFI_SUCCESS;
  ConOutInitEvent = NULL;
  MeFwHob         = NULL;
  Index           = 0;

  //
  // Find out whether HECI is disabled, if so enable to perform CurrentState check
  //
  if (PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, PCI_VENDOR_ID_OFFSET)) == 0xFFFFFFFF) {
    HeciDisabled = TRUE;
  }

  //
  // If Heci is disabled, check if ME is in debug mode.
  //
  if (HeciDisabled == TRUE) {
    MeFwHob = GetFirstGuidHob (&gMeFwHobGuid);
    if (MeFwHob != NULL) {
      Index = FindMeFwStsIndex (R_ME_HFS);
      if (Index != 0xFF) {
        MeFirmwareStatus.ul = MeFwHob->Group[HECI1_DEVICE].Reg[Index];
        DEBUG ((DEBUG_INFO, "MeFirmwareStatus 0x%x\n", MeFirmwareStatus.ul));
        if (MeFirmwareStatus.r.MeOperationMode == ME_OPERATION_MODE_DEBUG) {
          DEBUG ((DEBUG_INFO, "MeUlvCheckEntryPoint detects ME_OPERATION_MODE_DEBUG\n"));
          return EFI_SUCCESS;
        }
      }
    }
  }

  //
  // Enable HECI1 as FHS needs to be examine CurrentState
  //
  if (HeciDisabled) {
    HeciEnable ();
  }

  MeFirmwareStatus.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS));

  //
  // Make sure HECI FWS register bit [3:0] CURRENT WORKING STATE is NOT equal value 8 (INVALID_CPU_PLUGGED_IN)
  // If INVALID_CPU_PLUGGED_IN determined it means that invalid CPU SKU is populated as determined by PCH HW SKU
  // BIOS must halt the platform and display appropriate message as follows:
  //
  if (MeFirmwareStatus.r.CurrentState == ME_STATE_INVALID_CPU) {
    DEBUG ((DEBUG_ERROR, "(ULV) An unsupported CPU/PCH configuration has been identified!\n"));
    //
    // Register callback for informing user and stopping the platform when CONOUT is initialized
    //
    Status = gBS->CreateEvent (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    IllegalCpuForUlvPchHandler,
                    NULL,
                    &ConOutInitEvent
                    );
    ASSERT_EFI_ERROR (Status);
  }

  //
  // If HECI was initially disabled, preserve it
  //
  if (HeciDisabled) {
    HeciDisable();
  }
  return EFI_SUCCESS;
}

/**
  Perform End User messaging and halt booting because of ILLEGAL CPU-PCH configuration

  @param[in]  Event                 The event signaled.
  @param[in]  Context               The context passed in by the event notifier.
**/
VOID
EFIAPI
IllegalCpuForUlvPchHandler (
  IN  EFI_EVENT   Event,
  IN  VOID        *Context
  )
{
  ME_POLICY_PROTOCOL      *MePolicyInstance;
  EFI_STATUS              Status;
  ME_DXE_CONFIG           *MeDxeConfig;

  gBS->CloseEvent (Event);

  Status = gBS->LocateProtocol (&gDxeMePolicyGuid, NULL, (VOID **) &MePolicyInstance);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "(ULV) Failed to read ME Policy! Status = %r\n", Status));
    return;
  }

  Status = GetConfigBlock ((VOID *) MePolicyInstance, &gMeDxeConfigGuid, (VOID *) &MeDxeConfig);
  ASSERT_EFI_ERROR (Status);
  //
  // Indicate illegal configuration to End User and hang permanently
  //
  MeDxeConfig->MeReportError (MSG_ILLEGAL_CPU_PLUGGED_IN);
  CpuDeadLoop ();
}


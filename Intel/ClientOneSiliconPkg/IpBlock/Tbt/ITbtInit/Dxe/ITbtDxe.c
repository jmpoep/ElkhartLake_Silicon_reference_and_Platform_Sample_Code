/** @file
  ITBT init Dxe driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include <Uefi.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/TbtCommonLib.h>
#include <ITbtInfoHob.h>
#include <Protocol/ITbtPolicy.h>
#include <Protocol/ITbtNvsArea.h>
#include <Protocol/FirmwareVolume2.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Uefi/UefiSpec.h>
#include <Library/PcdLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/AslUpdateLib.h>
#include <Library/PcdLib.h>
#include <Library/DxeTbtDisBmeLib.h>
#include <Library/ItbtPcieRpLib.h>
#include <Protocol/TbtDisBmeProtocol.h>
#include <TcssDataHob.h>

GLOBAL_REMOVE_IF_UNREFERENCED ITBT_NVS_AREA_PROTOCOL                    mITbtNvsAreaProtocol;

/**
  DisableiTbtBmeCallBackFunction

  Disable BME on iTBT tree at ExitBootServices to hand off security of TBT hierarchies to the OS.

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
DisableITbtBmeCallBackFunction (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS                Status;
  UINT8                     Index;
  SBDF                      Sbdf = {0,0,0,0,0};
  UINTN                     RpDev;
  UINTN                     RpFunc;
  UINTN                     RpSegment;
  UINTN                     RpBus;

  DEBUG((DEBUG_INFO, "[TBT] DisableITbtBmeCallBackFunction START\n"));

  Status      = EFI_SUCCESS;
  Index       = 0;
  RpDev       = 0;
  RpFunc      = 0;
  RpSegment   = 0;
  RpBus       = 0;

  for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index++) {
      Status = GetItbtPcieRpInfo ((UINTN) Index, &RpSegment, &RpBus, &RpDev, &RpFunc);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Failed to get port[%d] info, Status: %r\n", Index, Status));
        continue;
      }

      Sbdf.Dev = (UINT32) RpDev;
      Sbdf.Func = (UINT32) RpFunc;
      Sbdf.Bus = (UINT32) RpBus;
      Sbdf.Seg = (UINT32) RpSegment;
      DEBUG ((DEBUG_INFO, "iTBT Root Port: %02x:%02x:%02x:%02x\n", Sbdf.Seg, Sbdf.Bus, Sbdf.Dev, Sbdf.Func));
      RecursiveTbtHierarchyConfiguration (Sbdf);
  }

  gBS->CloseEvent (Event);
  DEBUG((DEBUG_INFO, "[TBT] DisableITbtBmeCallBackFunction END\n"));
}

EFI_DISABLE_TBT_BME_PROTOCOL mDisableITbtBmeProtocol = {
    DisableITbtBmeCallBackFunction,
};

/**
  The function install DisableBme protocol for iTBT Shell validation
**/
VOID
InstallITbtDisableBmeProtocol (
  VOID
  )
{
  EFI_STATUS        Status;
  EFI_HANDLE        Handle;

  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gDisableITbtBmeProtocolGuid,
                  &mDisableITbtBmeProtocol,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "ITbtDisableBmeProtocol Failed. Status: %d\n", Status));
  } else {
    DEBUG ((DEBUG_INFO, "ITbtDisableBmeProtocol Installed\n"));
  }
}

/**
  ITBT NVS Area Initialize
**/
VOID
ITbtNvsAreaInit (
  IN  VOID              **mITbtNvsAreaPtr
  )
{
  UINTN                         Pages;
  EFI_PHYSICAL_ADDRESS          Address;
  EFI_STATUS                    Status;
  UINT8                         Index;
  ITBT_NVS_AREA_PROTOCOL        *ITbtNvsAreaProtocol;
  ITBT_POLICY_PROTOCOL          *ITbtPolicy;
  DXE_ITBT_CONFIG               *DxeITbtConfig;
  TCSS_DATA_HOB                 *TcssHob;
  ITBT_INFO_HOB                 *ITbtInfoHob;

  ITbtNvsAreaProtocol = NULL;
  ITbtPolicy = NULL;
  DxeITbtConfig = NULL;
  TcssHob = NULL;
  ITbtInfoHob = NULL;

  DEBUG ((DEBUG_INFO, "ITbtNvsAreaInit Start\n"));

  Status = gBS->LocateProtocol (&gITbtPolicyProtocolGuid, NULL, (VOID **) &ITbtPolicy);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *) ITbtPolicy, &gDxeITbtConfigGuid, (VOID *)&DxeITbtConfig);
  ASSERT_EFI_ERROR (Status);

  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
  ITbtInfoHob = (ITBT_INFO_HOB *) GetFirstGuidHob (&gITbtInfoHobGuid);

  Pages = EFI_SIZE_TO_PAGES (sizeof (ITBT_NVS_AREA));
  Address = 0xffffffff; // allocate address below 4G.

  Status  = gBS->AllocatePages (
                   AllocateMaxAddress,
                   EfiACPIMemoryNVS,
                   Pages,
                   &Address
                   );
  ASSERT_EFI_ERROR (Status);

  *mITbtNvsAreaPtr = (VOID *) (UINTN) Address;
  SetMem (*mITbtNvsAreaPtr, sizeof (ITBT_NVS_AREA), 0);

  //
  // ITBTNvsAreaProtocol default value init here
  //
  ITbtNvsAreaProtocol = (ITBT_NVS_AREA_PROTOCOL *) &Address;

  //
  // Initialize default values for ITBT NVS
  //
  ITbtNvsAreaProtocol->Area->WAKFinished           = 0;
  ITbtNvsAreaProtocol->Area->TbtAcpiRemovalSupport = 0;
  ITbtNvsAreaProtocol->Area->TbtAspm               = (UINT8) DxeITbtConfig->TbtCommonConfig.TbtAspm;
  ITbtNvsAreaProtocol->Area->TbtL1SubStates        = (UINT8) DxeITbtConfig->TbtCommonConfig.TbtL1SubStates;
  ITbtNvsAreaProtocol->Area->TbtSetClkReq          = (UINT8) DxeITbtConfig->TbtCommonConfig.TbtSetClkReq;
  ITbtNvsAreaProtocol->Area->TbtLtr                = (UINT8) DxeITbtConfig->TbtCommonConfig.TbtLtr;
  ITbtNvsAreaProtocol->Area->TbtPtm                = (UINT8) DxeITbtConfig->TbtCommonConfig.TbtPtm;
  ITbtNvsAreaProtocol->Area->OsNativeResourceBalance = DxeITbtConfig->OsNativeResourceBalance;
  ITbtNvsAreaProtocol->Area->ITbtRtd3              = (UINT8) DxeITbtConfig->ITbtGenericConfig.ITbtRtd3;
  ITbtNvsAreaProtocol->Area->ITbtRtd3ExitDelay     = (UINT16) DxeITbtConfig->ITbtGenericConfig.ITbtRtd3ExitDelay;
  if (ITbtInfoHob != NULL) {
    for (Index = 0; Index < MAX_ITBT_PCIE_PORT; Index ++) {
      if (ITbtInfoHob->ITbtRootPortConfig[Index].ITbtPcieRootPortEn == 1) {
        ITbtNvsAreaProtocol->Area->IntegratedTbtSupport = 1;
        break;
      }
    }
    ITbtNvsAreaProtocol->Area->IntegratedTbtDma0     = ((ITbtInfoHob->ITbtRootPortConfig[0].ITbtPcieRootPortEn == 1 || ITbtInfoHob->ITbtRootPortConfig[1].ITbtPcieRootPortEn == 1) ? TRUE : FALSE);
    ITbtNvsAreaProtocol->Area->IntegratedTbtDma1     = ((ITbtInfoHob->ITbtRootPortConfig[2].ITbtPcieRootPortEn == 1 || ITbtInfoHob->ITbtRootPortConfig[3].ITbtPcieRootPortEn == 1) ? TRUE : FALSE);
    ITbtNvsAreaProtocol->Area->ITbtPcieRootPortEn0   = ITbtInfoHob->ITbtRootPortConfig[0].ITbtPcieRootPortEn;
    ITbtNvsAreaProtocol->Area->ITbtPcieRootPortEn1   = ITbtInfoHob->ITbtRootPortConfig[1].ITbtPcieRootPortEn;
    ITbtNvsAreaProtocol->Area->ITbtPcieRootPortEn2   = ITbtInfoHob->ITbtRootPortConfig[2].ITbtPcieRootPortEn;
    ITbtNvsAreaProtocol->Area->ITbtPcieRootPortEn3   = ITbtInfoHob->ITbtRootPortConfig[3].ITbtPcieRootPortEn;
    ITbtNvsAreaProtocol->Area->ITbtForcePowerOnTimeoutInMs = ITbtInfoHob->ITbtForcePowerOnTimeoutInMs;
    ITbtNvsAreaProtocol->Area->ITbtConnectTopologyTimeoutInMs = ITbtInfoHob->ITbtConnectTopologyTimeoutInMs;
  }
  if (TcssHob != NULL) {
    ITbtNvsAreaProtocol->Area->ITbtImrValid        = (UINT8) ((TcssHob->TcssData.TbtImrStatus.Bits.Valid) & (TcssHob->TcssData.TbtImrStatus.Bits.Done));
  }

  DEBUG ((DEBUG_INFO, "ITbtNvsAreaInit End\n"));
}

/**
  This function gets registered as a callback to patch TBT ASL code

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
ITbtAcpiEndOfDxeCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS                            Status;
  UINT32                                Address;
  UINT16                                Length;
  UINT64                                SsdtOemTableId;

  SsdtOemTableId = SIGNATURE_64 ('T','c','s','s','S','s','d','t');

  Status = InitializeAslUpdateLib ();
  ASSERT_EFI_ERROR (Status);

  Address = (UINT32) (UINTN) mITbtNvsAreaProtocol.Area;
  Length  = (UINT16) sizeof (ITBT_NVS_AREA);
  DEBUG ((DEBUG_INFO, "Patch ITBT NvsAreaAddress: ITBT NVS Address %x Length %x\n", Address, Length));
  Status = UpdateSsdtNameAslCode ((UINT8*) &SsdtOemTableId, sizeof (SsdtOemTableId), SIGNATURE_32 ('I','T','N','B'), &Address, sizeof (Address));
  ASSERT_EFI_ERROR (Status);
  Status = UpdateSsdtNameAslCode ((UINT8*) &SsdtOemTableId, sizeof (SsdtOemTableId), SIGNATURE_32 ('I','T','N','L'), &Length, sizeof (Length));
  ASSERT_EFI_ERROR (Status);

  return;
}

/**
  Initialize Thunderbolt(TM) SSDT ACPI tables

  @retval EFI_SUCCESS    ACPI tables are initialized successfully
  @retval EFI_NOT_FOUND  ACPI tables not found
**/

EFI_STATUS
EFIAPI
ITbtDxeEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;
  EFI_HANDLE              Handle;
  EFI_EVENT               EndOfDxeEvent;
  EFI_EVENT               ExitBootServiceEvent;
  DXE_ITBT_CONFIG         *DxeITbtConfig;
  ITBT_POLICY_PROTOCOL    *ITbtPolicy;

  Status                  = EFI_SUCCESS;
  Handle                  = NULL;
  EndOfDxeEvent           = NULL;
  ExitBootServiceEvent    = NULL;
  DxeITbtConfig           = NULL;
  ITbtPolicy              = NULL;

  DEBUG ((DEBUG_INFO, "[TBT] ITbtDxeEntryPoint START\n"));

  //
  // Initialize ITbt Nvs Area
  //
  ITbtNvsAreaInit ((VOID **) &mITbtNvsAreaProtocol.Area);

  //
  // [ACPI] ITBT ACPI table
  //

  Handle = NULL;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gITbtNvsAreaProtocolGuid,
                  &mITbtNvsAreaProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Register an end of DXE event for ITBT ACPI to do some patch
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  ITbtAcpiEndOfDxeCallback,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->LocateProtocol (
              &gITbtPolicyProtocolGuid,
              NULL,
              (VOID **) &ITbtPolicy
              );
  if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to get ITbtPolicy, Status: %d\n", Status));
      goto Exit;
  }

  Status = GetConfigBlock ((VOID *) ITbtPolicy, &gDxeITbtConfigGuid, (VOID *)&DxeITbtConfig);
  if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to get DxeITbtConfig, Status: %d\n", Status));
      goto Exit;
  }

  if (DxeITbtConfig->TbtCommonConfig.TbtVtdBaseSecurity == TRUE) {

    //
    // Register a Exit Boot Service for disable iTBT BME
    //
    DEBUG ((DEBUG_INFO, "Register a Exit Boot Service for disable iTBT BME\n"));

    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    DisableITbtBmeCallBackFunction,
                    NULL,
                    &gEfiEventExitBootServicesGuid,
                    &ExitBootServiceEvent
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to Register a Exit Boot Service for disable TBT BME, Status: %d\n", Status));
      gBS->CloseEvent (ExitBootServiceEvent);
      goto Exit;
    }

    //
    // Install iTBT Disable Bme protocol for Shell testing purpose
    //
    InstallITbtDisableBmeProtocol ();
  }

Exit:
  DEBUG ((DEBUG_INFO, "[TBT] ITbtDxeEntryPoint END\n"));
  return Status;
}

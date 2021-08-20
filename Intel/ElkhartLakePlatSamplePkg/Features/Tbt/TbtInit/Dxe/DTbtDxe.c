/** @file
  DTBT init Dxe driver.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#include <Uefi.h>
#include <Uefi/UefiSpec.h>
#include <DTbtInfoHob.h>
#include <SetupVariable.h>
#include <Protocol/TbtDisBmeProtocol.h>
#include <Protocol/DxeDTbtPolicy.h>
#include <Protocol/DTbtNvsArea.h>
#include <Protocol/FirmwareVolume2.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/BaseLib.h>
#include <Library/TbtCommonLib.h>
#include <Library/PcdLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/AslUpdateLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DxeTbtDisBmeLib.h>
#include <Library/DTbtCommonLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED DTBT_NVS_AREA_PROTOCOL                    mDTbtNvsAreaProtocol;
GLOBAL_REMOVE_IF_UNREFERENCED DTBT_INFO_HOB                             *gDTbtInfoHob = NULL;


/**
  DisableDTbtBmeCallBackFunction

  Disable BME on DTbt tree at ExitBootServices to hand off security of TBT hierarchies to the OS.

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
DisableDTbtBmeCallBackFunction (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS                Status;
  UINT8                     Index;
  SBDF                      Sbdf = {0,0,0,0,0};
  UINTN                     RpDev;
  UINTN                     RpFunc;
  DTBT_INFO_HOB             *DTbtInfoHob = NULL;

  DEBUG((DEBUG_INFO, "[TBT] DisableDTbtBmeCallBackFunction START\n"));

  Status      = EFI_SUCCESS;
  Index       = 0;
  RpDev       = 0;
  RpFunc      = 0;

  //
  // Get DTbt INFO HOB
  //
  DTbtInfoHob = (DTBT_INFO_HOB *) GetFirstGuidHob (&gDTbtInfoHobGuid);
  if (DTbtInfoHob == NULL) {
    DEBUG ((DEBUG_ERROR, "Failed to get gDTbtInfoHob\n"));
    goto Exit;
  }

  for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
    DEBUG ((DEBUG_INFO, "DTbtInfoHob->DTbtControllerConfig[%d].PcieRpNumber: %d\n", Index, DTbtInfoHob->DTbtControllerConfig[Index].PcieRpNumber));

    if (DTbtInfoHob->DTbtControllerConfig[Index].DTbtControllerEn == 1) {
      Status = GetDTbtRpDevFun (DTbtInfoHob->DTbtControllerConfig[Index].Type, DTbtInfoHob->DTbtControllerConfig[Index].PcieRpNumber - 1, &RpDev, &RpFunc);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Failed to get GetDTbtRpDevFun, Status: %d\n", Status));
        continue;
      }
      Sbdf.Dev = (UINT32) RpDev;
      Sbdf.Func = (UINT32) RpFunc;
      RecursiveTbtHierarchyConfiguration (Sbdf);
    } else {
      DEBUG ((DEBUG_INFO, "DTbtInfoHob->DTbtControllerConfig[%d].DTbtControllerEn: %d\n", Index, DTbtInfoHob->DTbtControllerConfig[Index].DTbtControllerEn));
    }
  }

Exit:
  gBS->CloseEvent (Event);
  DEBUG((DEBUG_INFO, "[TBT] DisableDTbtBmeCallBackFunction END\n"));
}

EFI_DISABLE_TBT_BME_PROTOCOL mDisableDTbtBmeProtocol = {
    DisableDTbtBmeCallBackFunction,
};

/**
  Install DisableBme Protocol for DTBT UEFI-Shell Validation
**/
VOID
InstallDTbtDisableBmeProtocol (
  VOID
  )
{
  EFI_STATUS        Status;
  EFI_HANDLE        Handle;

  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gDxeDisableDTbtBmeProtocolGuid,
                  &mDisableDTbtBmeProtocol,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "DTbtDisableBmeProtocol Failed. Status: %d\n", Status));
  } else {
    DEBUG ((DEBUG_INFO, "DTbtDisableBmeProtocol Installed\n"));
  }
}

/**
  DTBT NVS Area Initialize
**/
VOID
DTbtNvsAreaInit (
  IN  VOID              **mDTbtNvsAreaPtr
  )
{
  UINTN                         Pages;
  EFI_PHYSICAL_ADDRESS          Address;
  EFI_STATUS                    Status;
  DTBT_NVS_AREA_PROTOCOL        *DTbtNvsAreaProtocol;
  DXE_DTBT_POLICY_PROTOCOL      *DxeDTbtConfig;

  DEBUG ((DEBUG_INFO, "DTbtNvsAreaInit Start\n"));

  Status = gBS->LocateProtocol (
                &gDxeDTbtPolicyProtocolGuid,
                NULL,
                (VOID **) &DxeDTbtConfig
                );
  ASSERT_EFI_ERROR (Status);

  Pages = EFI_SIZE_TO_PAGES (sizeof (DTBT_NVS_AREA));
  Address = 0xffffffff; // allocate address below 4G.

  Status  = gBS->AllocatePages (
                   AllocateMaxAddress,
                   EfiACPIMemoryNVS,
                   Pages,
                   &Address
                   );
  ASSERT_EFI_ERROR (Status);

  *mDTbtNvsAreaPtr = (VOID *) (UINTN) Address;
  SetMem (*mDTbtNvsAreaPtr, sizeof (DTBT_NVS_AREA), 0);

  //
  // DTBTNvsAreaProtocol default value init here
  //
  DTbtNvsAreaProtocol = (DTBT_NVS_AREA_PROTOCOL *) &Address;

  //
  // Initialize default values for DTBT NVS
  //
  DTbtNvsAreaProtocol->Area->WAKFinished             = 0;
  DTbtNvsAreaProtocol->Area->TbtAcpiRemovalSupport   = 0;
  DTbtNvsAreaProtocol->Area->DiscreteTbtSupport      = ((gDTbtInfoHob->DTbtControllerConfig[0].DTbtControllerEn == 1 || gDTbtInfoHob->DTbtControllerConfig[1].DTbtControllerEn == 1) ? TRUE : FALSE);
  DTbtNvsAreaProtocol->Area->TbtGpioFilter           = (UINT8) DxeDTbtConfig->DTbtGenericConfig.Gpio5Filter;
  DTbtNvsAreaProtocol->Area->TrOsup                  = (UINT8) DxeDTbtConfig->DTbtGenericConfig.TrA0OsupWa;
  DTbtNvsAreaProtocol->Area->TbtAspm                 = (UINT8) DxeDTbtConfig->TbtCommonConfig.TbtAspm;
  DTbtNvsAreaProtocol->Area->TbtL1SubStates          = (UINT8) DxeDTbtConfig->TbtCommonConfig.TbtL1SubStates;
  DTbtNvsAreaProtocol->Area->TbtSetClkReq            = (UINT8) DxeDTbtConfig->TbtCommonConfig.TbtSetClkReq;
  DTbtNvsAreaProtocol->Area->TbtLtr                  = (UINT8) DxeDTbtConfig->TbtCommonConfig.TbtLtr;
  DTbtNvsAreaProtocol->Area->TbtPtm                  = (UINT8) DxeDTbtConfig->TbtCommonConfig.TbtPtm;
  DTbtNvsAreaProtocol->Area->TbtWakeupSupport        = (UINT8)DxeDTbtConfig->DTbtGenericConfig.TbtWakeupSupport;
  DTbtNvsAreaProtocol->Area->TbtFrcPwrEn             = gDTbtInfoHob->DTbtGenericConfig.Gpio3ForcePwr;
  DTbtNvsAreaProtocol->Area->TbtAcDcSwitch           = (UINT8) DxeDTbtConfig->DTbtGenericConfig.TbtAcDcSwitch;

  //
  // DTBT Controller 1
  //
  DTbtNvsAreaProtocol->Area->DTbtControllerEn0       = gDTbtInfoHob->DTbtControllerConfig[0].DTbtControllerEn;
  DTbtNvsAreaProtocol->Area->RootportSelected0       = gDTbtInfoHob->DTbtControllerConfig[0].PcieRpNumber;
  DTbtNvsAreaProtocol->Area->RootportSelected0Type   = gDTbtInfoHob->DTbtControllerConfig[0].Type;
  DTbtNvsAreaProtocol->Area->RootportEnabled0        = gDTbtInfoHob->DTbtControllerConfig[0].DTbtControllerEn;
  DTbtNvsAreaProtocol->Area->TbtFrcPwrGpioNo0        = gDTbtInfoHob->DTbtControllerConfig[0].ForcePwrGpio.GpioPad;
  DTbtNvsAreaProtocol->Area->TbtFrcPwrGpioLevel0     = gDTbtInfoHob->DTbtControllerConfig[0].ForcePwrGpio.GpioLevel;
  DTbtNvsAreaProtocol->Area->TbtCioPlugEventGpioNo0  = gDTbtInfoHob->DTbtControllerConfig[0].CioPlugEventGpio.GpioPad;
  DTbtNvsAreaProtocol->Area->TbtPcieRstGpioNo0       = gDTbtInfoHob->DTbtControllerConfig[0].PcieRstGpio.GpioPad;
  DTbtNvsAreaProtocol->Area->TbtPcieRstGpioLevel0    = gDTbtInfoHob->DTbtControllerConfig[0].PcieRstGpio.GpioLevel;

  //
  // DTBT Controller 2
  //
  DTbtNvsAreaProtocol->Area->DTbtControllerEn1       = gDTbtInfoHob->DTbtControllerConfig[1].DTbtControllerEn;
  DTbtNvsAreaProtocol->Area->RootportSelected1       = gDTbtInfoHob->DTbtControllerConfig[1].PcieRpNumber;
  DTbtNvsAreaProtocol->Area->RootportSelected1Type   = gDTbtInfoHob->DTbtControllerConfig[1].Type;
  DTbtNvsAreaProtocol->Area->RootportEnabled1        = gDTbtInfoHob->DTbtControllerConfig[1].DTbtControllerEn;
  DTbtNvsAreaProtocol->Area->TbtFrcPwrGpioNo1        = gDTbtInfoHob->DTbtControllerConfig[1].ForcePwrGpio.GpioPad;
  DTbtNvsAreaProtocol->Area->TbtFrcPwrGpioLevel1     = gDTbtInfoHob->DTbtControllerConfig[1].ForcePwrGpio.GpioLevel;
  DTbtNvsAreaProtocol->Area->TbtCioPlugEventGpioNo1  = gDTbtInfoHob->DTbtControllerConfig[1].CioPlugEventGpio.GpioPad;
  DTbtNvsAreaProtocol->Area->TbtPcieRstGpioNo1       = gDTbtInfoHob->DTbtControllerConfig[1].PcieRstGpio.GpioPad;
  DTbtNvsAreaProtocol->Area->TbtPcieRstGpioLevel1    = gDTbtInfoHob->DTbtControllerConfig[1].PcieRstGpio.GpioLevel;
  DTbtNvsAreaProtocol->Area->TBtCommonGpioSupport    = gDTbtInfoHob->DTbtGenericConfig.DTbtSharedGpioConfiguration;

  DEBUG ((DEBUG_INFO, "DTbtNvsAreaInit End\n"));
}

/**
  This function gets registered as a callback to patch TBT ASL code

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
DTbtAcpiEndOfDxeCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS                            Status;
  UINT32                                Address;
  UINT16                                Length;
  UINT32                                Signature;

  Status = InitializeAslUpdateLib ();
  ASSERT_EFI_ERROR (Status);

  Address = (UINT32) (UINTN) mDTbtNvsAreaProtocol.Area;
  Length  = (UINT16) sizeof (DTBT_NVS_AREA);
  DEBUG ((DEBUG_INFO, "Patch DTBT NvsAreaAddress: TBT NVS Address %x Length %x\n", Address, Length));
  Status  = UpdateNameAslCode (SIGNATURE_32 ('D','T','N','B'), &Address, sizeof (Address));
  ASSERT_EFI_ERROR (Status);
  Status  = UpdateNameAslCode (SIGNATURE_32 ('D','T','N','L'), &Length, sizeof (Length));
  ASSERT_EFI_ERROR (Status);

  if (gDTbtInfoHob != NULL) {
    if (gDTbtInfoHob->DTbtControllerConfig[0].DTbtControllerEn == 1) {
      if (gDTbtInfoHob->DTbtControllerConfig[0].CioPlugEventGpio.AcpiGpeSignaturePorting == TRUE) {
        DEBUG ((DEBUG_INFO, "Patch ATBT Method Name\n"));
        Signature = gDTbtInfoHob->DTbtControllerConfig[0].CioPlugEventGpio.AcpiGpeSignature;
        Status  = UpdateMethodAslCode (SIGNATURE_32 ('A','T','B','T'), &Signature, sizeof (Signature));
        ASSERT_EFI_ERROR (Status);
      }
    }
    if (gDTbtInfoHob->DTbtControllerConfig[1].DTbtControllerEn == 1) {
      if((gDTbtInfoHob->DTbtGenericConfig.DTbtSharedGpioConfiguration == FALSE) && (gDTbtInfoHob->DTbtControllerConfig[1].CioPlugEventGpio.AcpiGpeSignaturePorting == TRUE)) {
        DEBUG ((DEBUG_INFO, "Patch BTBT Method Name\n"));
        Signature = gDTbtInfoHob->DTbtControllerConfig[1].CioPlugEventGpio.AcpiGpeSignature;
        Status  = UpdateMethodAslCode (SIGNATURE_32 ('B','T','B','T'), &Signature, sizeof (Signature));
        ASSERT_EFI_ERROR (Status);
      }
    }
  }

  return;
}

/**
  Initialize Thunderbolt(TM) SSDT ACPI tables

  @retval EFI_SUCCESS    ACPI tables are initialized successfully
  @retval EFI_NOT_FOUND  ACPI tables not found
**/

EFI_STATUS
EFIAPI
DTbtDxeEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                Status;
  EFI_HANDLE                Handle;
  EFI_EVENT                 EndOfDxeEvent;
  EFI_EVENT                 ExitBootServiceEvent;
  DXE_DTBT_POLICY_PROTOCOL  *DxeTbtConfig;

  Status                    = EFI_SUCCESS;
  Handle                    = NULL;
  EndOfDxeEvent             = NULL;
  ExitBootServiceEvent      = NULL;
  DxeTbtConfig              = NULL;

  DEBUG ((DEBUG_INFO, "[TBT] DTbtDxeEntryPoint START\n"));

  //
  // Get DTBT INFO HOB
  //
  gDTbtInfoHob = (DTBT_INFO_HOB *) GetFirstGuidHob (&gDTbtInfoHobGuid);
  if (gDTbtInfoHob == NULL) {
    return EFI_NOT_FOUND;
  }

  //
  // Initialize DTbt Nvs Area
  //
  DTbtNvsAreaInit ((VOID **) &mDTbtNvsAreaProtocol.Area);

  //
  // [ACPI] DTBT ACPI table
  //

  Handle = NULL;

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gDTbtNvsAreaProtocolGuid,
                  &mDTbtNvsAreaProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // Register an end of DXE event for DTBT ACPI to do some patch
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  DTbtAcpiEndOfDxeCallback,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  //
  // TBT Security requirment
  //
  Status = gBS->LocateProtocol (
              &gDxeDTbtPolicyProtocolGuid,
              NULL,
              (VOID **) &DxeTbtConfig
              );
  if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to DxeTbtConfig, Status: %d\n", Status));
      goto Exit;
  }

  if (DxeTbtConfig->TbtCommonConfig.TbtVtdBaseSecurity == TRUE) {

    //
    // Register a Exit Boot Service for disable DTbt BME
    //
    DEBUG ((DEBUG_INFO, "Register a Exit Boot Service for disable DTbt BME\n"));
    Status = gBS->CreateEventEx (
                    EVT_NOTIFY_SIGNAL,
                    TPL_CALLBACK,
                    DisableDTbtBmeCallBackFunction,
                    NULL,
                    &gEfiEventExitBootServicesGuid,
                    &ExitBootServiceEvent
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Failed to Register a Exit Boot Service for disable DTbt BME, Status: %d\n", Status));
      gBS->CloseEvent (ExitBootServiceEvent);
      goto Exit;
    }

    //
    // Install DTbt DisableBme for UEFI-Shell testing
    //
    InstallDTbtDisableBmeProtocol ();
  }

Exit:
  DEBUG ((DEBUG_INFO, "[TBT] DTbtDxeEntryPoint END\n"));
  return Status;
}

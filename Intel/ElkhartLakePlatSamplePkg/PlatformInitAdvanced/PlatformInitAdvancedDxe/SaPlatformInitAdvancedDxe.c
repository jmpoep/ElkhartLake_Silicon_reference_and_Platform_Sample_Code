/** @file
  Source code file for the SA Platform Init DXE module

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include "PlatformInitAdvancedDxe.h"
#include <Protocol/BlockIo.h>
#include <Protocol/GopPolicy.h>
#include <LegacyUsb/Protocol/UsbController.h>
#include <Protocol/SaPolicy.h>
#include <Library/DebugLib.h>
#include <Protocol/Cpu.h>
#include <Protocol/PciEnumerationComplete.h>
#include <PlatformNvRamHookLib.h>
#include <ITbtInfoHob.h>
#include <SaDataHob.h>
#include <Register/IgdRegs.h>

GLOBAL_REMOVE_IF_UNREFERENCED EFI_PHYSICAL_ADDRESS                  mAddress;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                                 mSize;
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN                               mIsGmadrSetToWc = FALSE;

#define EFI_MAX_ADDRESS       0xFFFFFFFF


EFI_STATUS
EFIAPI
RegisterDisplayDimmPopulationErrMsg (
  VOID
  );

VOID
EFIAPI
DisplayDimmPopulationErrMsg (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );

VOID
UpdateGmAdrRegionToWriteCombine (
  VOID
  );

VOID
EFIAPI
PciEnumCompleteCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  );

VOID
EFIAPI
ReadyToBootCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  );


/**
  Update RMRR Base and Limit Address for USB.

**/
VOID
UpdateRmrrUsbAddress (
  VOID
  )
{
  EFI_STATUS              Status;
  SA_POLICY_PROTOCOL      *SaPolicy;
  MISC_DXE_CONFIG         *MiscDxeConfig;
  UINTN                   VariableSize;
  SA_SETUP                SaSetup;

  VariableSize = sizeof(SA_SETUP);
  Status = gRT->GetVariable(
    L"SaSetup",
    &gSaSetupVariableGuid,
    NULL,
    &VariableSize,
    &SaSetup
    );
  ASSERT_EFI_ERROR(Status);

  Status = gBS->LocateProtocol (&gSaPolicyProtocolGuid, NULL, (VOID **) &SaPolicy);
  if (EFI_ERROR (Status)) {
    return;
  }

  Status = GetConfigBlock ((VOID *)SaPolicy, &gMiscDxeConfigGuid, (VOID *)&MiscDxeConfig);
  ASSERT_EFI_ERROR (Status);

  if (SaSetup.EnableVtd == 1) {
    mSize = EFI_SIZE_TO_PAGES(SA_VTD_RMRR_USB_LENGTH);
    mAddress = EFI_MAX_ADDRESS;

    Status = (gBS->AllocatePages) (
                     AllocateMaxAddress,
                     EfiReservedMemoryType,
                     mSize,
                     &mAddress
                    );
    ASSERT_EFI_ERROR (Status);

    MiscDxeConfig->RmrrUsbBaseAddress[0] = mAddress;
    MiscDxeConfig->RmrrUsbBaseAddress[1] = mAddress + SA_VTD_RMRR_USB_LENGTH - 1;
  }
}


/**
  Update Setup variable for keep DMA UUID
**/
VOID
UpdateItbtDmaUuidVariable (
  VOID
  )
{
  UINTN                         VarSize;
  UINT32                        VariableAttr;
  ITBT_INFO_HOB                 *ITbtInfoHobPtr;
  SETUP_DATA                    SystemConfiguration;
  EFI_STATUS                    Status;

  DEBUG ((DEBUG_INFO, "UpdateItbtDmaUuidVariable - Start\n"));
  //
  // Get Setup Data for update ITBT DMA UUID
  //
  VarSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  PLATFORM_SETUP_VARIABLE_NAME,
                  &gSetupVariableGuid,
                  &VariableAttr,
                  &VarSize,
                  &SystemConfiguration
                  );
  ASSERT_EFI_ERROR (Status);

  if (EFI_ERROR(Status)){
    DEBUG ((DEBUG_ERROR, "Platform Setup data was not found.\n"));
    return;
  }

  ///
  /// Get ITBT DMA UUID value from HOB of gTcssHobGuid
  ///
  ITbtInfoHobPtr = (ITBT_INFO_HOB *) GetFirstGuidHob (&gITbtInfoHobGuid);

  if (ITbtInfoHobPtr == NULL) {
    DEBUG ((DEBUG_ERROR, "TcssHobPtr is NULL.\n"));
    return;
  }

  ///
  /// Set ITBT DMA UUID to Setup Data variable with updated values
  ///
  Status = gRT->SetVariable (
                  PLATFORM_SETUP_VARIABLE_NAME,
                  &gSetupVariableGuid,
                  VariableAttr,
                  VarSize,
                  &SystemConfiguration
                  );
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_INFO, "UpdateItbtDmaUuidVariable - End\n"));
}


/**
  Updates DIMM slots status for Desktop,server and workstation boards

**/
VOID
UpdateDimmPopulation(
  VOID
  )
{
  if (PcdGetBool (PcdDimmPopulationError)) {
    RegisterDisplayDimmPopulationErrMsg ();
  }
}

/**
  Register DisplayDIMMPopulationErrMsg Notification function on SimpleIn protocol Installation.

  @param[in] SystemTable    Pointer to the System Table

  @retval  EFI_SUCCESS      return EFI_STATUS as success
**/
EFI_STATUS
EFIAPI
RegisterDisplayDimmPopulationErrMsg (
  VOID
  )
{
  EFI_EVENT DimmPopultionErrMsgEvent;
  VOID      *Registration;

  DimmPopultionErrMsgEvent  = NULL;

  //
  // Create event for SimpleInProtocol Callback notification
  //
  gBS->CreateEvent (
        EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        DisplayDimmPopulationErrMsg,
        NULL,
        &DimmPopultionErrMsgEvent
        );
  gBS->RegisterProtocolNotify (
        &gBdsAllDriversConnectedProtocolGuid,
        DimmPopultionErrMsgEvent,
        &Registration
        );

  return EFI_SUCCESS;
}

/**
  Display DIMM population error message, while Wrong DIMM Population is found.

  @param[in] Event    A pointer to the Event that triggered the callback
  @param[in] Context  A pointer to private data registered with the callback function.

  @retval  EFI_SUCCESS     If Successfully exectuted else returns the error status
**/
VOID
EFIAPI
DisplayDimmPopulationErrMsg (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS                Status;
  EFI_INPUT_KEY             Key;

  DEBUG ((DEBUG_ERROR, "\n DIMMPopulation Error msg\n"));

  if (gST->ConOut != NULL && gST->ConIn != NULL) {
    if (Event != NULL) {
      gBS->CloseEvent (Event);
    }
    //
    // Display the Error Message
    //
    gST->ConOut->OutputString (gST->ConOut, L"");

    gST->ConOut->OutputString (gST->ConOut, L"Error...! Invalid DIMM Population.");

    gST->ConOut->OutputString (gST->ConOut, L"Slot 0 can't be populated when Slot 1 is not populated on the same channel");

    gST->ConOut->OutputString (gST->ConOut, L"Press <Y> to Continue. <N> to Shutdown");

    //
    // Wait for User Input
    //
    do {
      Status = gBS->CheckEvent (gST->ConIn->WaitForKey);
      if (!EFI_ERROR (Status)) {
        Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
        if (Key.UnicodeChar == L'Y' || Key.UnicodeChar == L'y') {
          DEBUG ((DEBUG_INFO, " Boot Continue\n"));
          break;
        } else if (Key.UnicodeChar == L'N' || Key.UnicodeChar == L'n') {
          DEBUG ((DEBUG_ERROR, " System shutdown\n"));
          gRT->ResetSystem (EfiResetShutdown, EFI_SUCCESS, 0, NULL);
        }
      }
    } while (1);
  }
}


/**
  System Agent platform Initialization

**/
VOID
SaPlatformInitDxe (
  VOID
  )
{

  //
  // Update RMRR Base and Limit Address for USB
  //
  UpdateRmrrUsbAddress();

  //
  // Update GT Aperture region memory type as Write Combine.
  //
  UpdateGmAdrRegionToWriteCombine();
}

/**
  This function will update the GT Aperture Region to Write Combining.

**/
VOID
UpdateGmAdrRegionToWriteCombine (
  VOID
  )
{
  VOID                      *Registration;
  EFI_STATUS                Status;
  EFI_EVENT                 Event;

  DEBUG ((DEBUG_INFO, "Call backs to update GmAdr region as write combine\n"));

  ///
  /// Create PCI Enumeration Completed callback
  ///
  EfiCreateProtocolNotifyEvent (
    &gEfiPciEnumerationCompleteProtocolGuid,
    TPL_NOTIFY,
    PciEnumCompleteCallback,
    NULL,
    &Registration
    );

 Status = EfiCreateEventReadyToBootEx (
             TPL_CALLBACK,
             ReadyToBootCallback,
             NULL,
             &Event
             );

  ASSERT_EFI_ERROR (Status);
}

/**
  This function gets registered as a callback to perform SA  functions after PCI enumeration completes.

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
PciEnumCompleteCallback (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS              Status;
  VOID                    *ProtocolPointer;
  UINT32                  Msac;
  UINT64                  McD2BaseAddress;
  UINT64                  GtApertureSize;
  UINT64                  GtApertureAdr;
  EFI_CPU_ARCH_PROTOCOL   *CpuArch;
  UINTN                   VariableSize;
  SA_SETUP                SaSetup;

  DEBUG ((DEBUG_INFO, "SA Platform PciEnumCompleteCallback Start\n"));

  Msac = 0;
  GtApertureAdr = 0;
  GtApertureSize = 0;

  ///
  /// Check if this is first time called by EfiCreateProtocolNotifyEvent() or not,
  /// if it is, we will skip it until real event is triggered
  ///
  Status = gBS->LocateProtocol (&gEfiPciEnumerationCompleteProtocolGuid, NULL, (VOID **) &ProtocolPointer);
  if (EFI_SUCCESS != Status) {
    return;
  }

  gBS->CloseEvent (Event);

  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  ///
  /// If device 0:2:0 (Internal Graphics Device, or GT) is not present, skip it.
  ///
  if ((PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) != 0xFFFF)) {
    Msac = PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);
    GtApertureSize = ((((Msac & (BIT20 | BIT19 | BIT18 | BIT17 | BIT16))) >> 16) + 1) * SIZE_128MB;

    PciSegmentReadBuffer (McD2BaseAddress + R_SA_IGD_GMADR, sizeof (UINT64), &GtApertureAdr);
    GtApertureAdr &= 0xFFFFFFFFFFFFFFF0;

    Status = gBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **) &CpuArch);
    ASSERT_EFI_ERROR (Status);

  //
  // Check Enable Above 4GB MMIO or not
  //
  VariableSize = sizeof(SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SaSetup
                  );
  if (!EFI_ERROR(Status)) {
    if (SaSetup.EnableAbove4GBMmio == 1) {
      //
      // WORKAROUND for MTRR above 4G issue
      //
       GtApertureSize = SIZE_128GB;
    }
  }

    Status = CpuArch->SetMemoryAttributes (
                        CpuArch,
                        GtApertureAdr,
                        GtApertureSize,
                        EFI_MEMORY_WC
                        );
    if (EFI_SUCCESS == Status) {
      mIsGmadrSetToWc = TRUE;
    } else {
      DEBUG((DEBUG_INFO, "Setting GmAdr Memory as WriteCombine failed! Cache the Flash area as UC to release MTRR. \n"));
      Status = CpuArch->SetMemoryAttributes (
                        CpuArch,
                        0xff000000,
                        0x01000000,
                        EFI_MEMORY_UC
                        );
      DEBUG((DEBUG_INFO, "Setting Flash Memory as UnCacheable %r\n", Status));
      ASSERT_EFI_ERROR (Status);
      Status = CpuArch->SetMemoryAttributes (
                        CpuArch,
                        GtApertureAdr,
                        GtApertureSize,
                        EFI_MEMORY_WC
                        );
      DEBUG((DEBUG_INFO, "Setting GmAdr Memory as WriteCombine %r\n", Status));
      if (EFI_SUCCESS == Status) {
        mIsGmadrSetToWc = TRUE;
      }
      ASSERT_EFI_ERROR (Status);
    }
  }

  DEBUG ((DEBUG_INFO, "SA Platform PciEnumCompleteCallback End\n"));

  return;
}


/**
  This function handles SA task at the ready to boot

  @param[in]  Event     The Event this notify function registered to.
  @param[in]  Context   Pointer to the context data registered to the
                        Event.
**/
VOID
EFIAPI
ReadyToBootCallback (
  IN EFI_EVENT Event,
  IN VOID      *Context
  )
{
  EFI_STATUS              Status;
  UINT32                  Msac;
  UINT64                  McD2BaseAddress;
  UINT64                  GtApertureSize;
  UINT64                  GtApertureAdr;
  SA_POLICY_PROTOCOL      *SaPolicy;
//  MISC_DXE_CONFIG         *MiscDxeConfig;
  EFI_CPU_ARCH_PROTOCOL   *CpuArch;
//  SA_DATA_HOB             *SaDataHob;
  UINTN                   VariableSize;
  SA_SETUP                SaSetup;

  Msac = 0;
  GtApertureAdr = 0;
  GtApertureSize = 0;
  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);

  Status = gBS->LocateProtocol (&gSaPolicyProtocolGuid, NULL, (VOID **) &SaPolicy);
  ASSERT_EFI_ERROR (Status);

  Status = gBS->LocateProtocol (&gEfiCpuArchProtocolGuid, NULL, (VOID **) &CpuArch);
  ASSERT_EFI_ERROR (Status);

  gBS->CloseEvent (Event);

  if ((mIsGmadrSetToWc == TRUE) && (PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) != 0xFFFF)) {
    Msac = PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);
    GtApertureSize = ((((Msac & (BIT20 | BIT19 | BIT18 | BIT17 | BIT16))) >> 16) + 1) * SIZE_128MB;
    PciSegmentReadBuffer (McD2BaseAddress + R_SA_IGD_GMADR, sizeof (UINT64), &GtApertureAdr);
    GtApertureAdr &= 0xFFFFFFFFFFFFFFF0;

  //
  // Check Enable Above 4GB MMIO or not
  //
  VariableSize = sizeof(SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SaSetup
                  );

    if (!EFI_ERROR(Status)) {
      if ((SaSetup.EnableAbove4GBMmio == 1)) {

        //
        // WORKAROUND for MTRR above 4G issue
        //
        GtApertureSize = SIZE_128GB;
      }
      Status = CpuArch->SetMemoryAttributes (
                          CpuArch,
                          GtApertureAdr,
                          GtApertureSize,
                          EFI_MEMORY_UC
                          );
      ASSERT_EFI_ERROR (Status);
    }
  }

  return;
}
/** @file
  HECI driver services for Runtime DXE.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include "HeciRuntime.h"
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiRuntimeLib.h>

#include <Protocol/PciEnumerationComplete.h>

BOOLEAN                     mAtRuntime;
HECI_RUNTIME_DEVICE_CONTEXT mHeciDeviceContext[HeciMax];

STATIC EFI_EVENT            mExitBootServicesEvent;
STATIC EFI_EVENT            mVirtualAddressChangeEvent;

/**
  Notification function of EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE.

  This is a notification function registered on EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE event.
  It convers pointer to new virtual address.

  @param[in]  Event        Event whose notification function is being invoked.
  @param[in]  Context      Pointer to the notification function's context.

**/
VOID
EFIAPI
HeciRuntimeAddressChangeEvent (
  IN EFI_EVENT             Event,
  IN VOID                  *Context
  )
{
  UINT32    DeviceIndex;

  for (DeviceIndex = Heci1; DeviceIndex < HeciMax; DeviceIndex++) {
    if (mHeciDeviceContext[DeviceIndex].RuntimeAccessible) {
      EfiConvertPointer (0x0, (VOID **) &(mHeciDeviceContext[DeviceIndex].BaseAddress));
      EfiConvertPointer (0x0, (VOID **) &(mHeciDeviceContext[DeviceIndex].Bar0Address));
    }
  }
}

/**
  Sets an indicator that boot is entering runtime.

  @param  Event                   Pointer to this event
  @param  Context                 Event handler private data

**/
VOID
EFIAPI
HeciExitBootServicesCallback (
  EFI_EVENT  Event,
  VOID       *Context
  )
{
  mAtRuntime = TRUE;
}

/**
  Sets the runtime attribute in GCD for the specified HECI device's PCI CFG base address
  and BAR0.

  @param[in]    HeciDev           The HECI device that should be configured for runtime.

  @retval       EFI_SUCCESS       Setting memory attributes status.
  @retval       EFI_NOT_FOUND     Coult not find required HECI PCI device information.

**/
EFI_STATUS
EFIAPI
HeciSetRuntimeMemoryAttributes (
  IN  HECI_CONTEXT_DEVICE   HeciDev
  )
{
  EFI_STATUS                         Status;
  EFI_GCD_MEMORY_SPACE_DESCRIPTOR    GcdDescriptor;

  DEBUG ((DEBUG_INFO, "HeciSetRuntimeMemoryAttributes() Start\n"));
  DEBUG ((DEBUG_INFO, "HECI Device: HECI%d.\n", (HeciDev + 1)));

  if (mHeciDeviceContext[HeciDev].BaseAddress == 0 || mHeciDeviceContext[HeciDev].SegmentBaseAddress == 0) {
    return EFI_NOT_FOUND;
  }

  if (PciSegmentRead16 (mHeciDeviceContext[HeciDev].SegmentBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    if (mHeciDeviceContext[HeciDev].Bar0Address == 0) {
      return EFI_NOT_FOUND;
    }
  } else {
    CheckAndFixHeciForAccess (HeciDev);
  }

  DEBUG ((DEBUG_INFO, "HECI Base Address: 0x%x.\n", mHeciDeviceContext[HeciDev].BaseAddress));
  DEBUG ((DEBUG_INFO, "HECI BAR Address: 0x%x.\n", mHeciDeviceContext[HeciDev].Bar0Address));

  ///
  /// Set the EFI_MEMORY_RUNTIME attribute for the HECI BAR MMIO range
  ///
  Status = gDS->GetMemorySpaceDescriptor (mHeciDeviceContext[HeciDev].Bar0Address, &GcdDescriptor);
  if (Status == EFI_NOT_FOUND) {
    DEBUG ((DEBUG_INFO, "Adding HECI BAR descriptor in HeciRuntimeDxe.\n"));
    Status = gDS->AddMemorySpace (
                    EfiGcdMemoryTypeMemoryMappedIo,
                    mHeciDeviceContext[HeciDev].Bar0Address,
                    HECI_BAR_LENGTH,
                    0
                    );
    if (!EFI_ERROR (Status)) {
      Status = gDS->GetMemorySpaceDescriptor (mHeciDeviceContext[HeciDev].Bar0Address, &GcdDescriptor);
    }
  }
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = gDS->SetMemorySpaceAttributes (
                  mHeciDeviceContext[HeciDev].Bar0Address,
                  HECI_BAR_LENGTH,
                  GcdDescriptor.Attributes | EFI_MEMORY_RUNTIME
                  );

  ///
  /// Set the EFI_MEMORY_RUNTIME attribute for the HECI PCI CFG MMIO range
  ///
  Status = gDS->GetMemorySpaceDescriptor (mHeciDeviceContext[HeciDev].BaseAddress, &GcdDescriptor);
  if (Status == EFI_NOT_FOUND) {
    DEBUG ((DEBUG_INFO, "Adding HECI PCI CFG descriptor in HeciRuntimeDxe.\n"));
    Status = gDS->AddMemorySpace (
                    EfiGcdMemoryTypeMemoryMappedIo,
                    mHeciDeviceContext[HeciDev].BaseAddress,
                    HECI_BASE_LENGTH,
                    0
                    );
    if (!EFI_ERROR (Status)) {
      Status = gDS->GetMemorySpaceDescriptor (mHeciDeviceContext[HeciDev].BaseAddress, &GcdDescriptor);
    }
  }
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = gDS->SetMemorySpaceAttributes (
                  mHeciDeviceContext[HeciDev].BaseAddress,
                  HECI_BASE_LENGTH,
                  GcdDescriptor.Attributes | EFI_MEMORY_RUNTIME
                  );

  DEBUG ((DEBUG_INFO, "HeciSetRuntimeMemoryAttributes() End\n"));

  return Status;
}

/**
  PCI enumeration complete event handler to configure memory ranges in GCD needed at runtime.

  @param[in] Event    Event whose notification function is being invoked.
  @param[in] Context  Pointer to the notification function's context.
**/
VOID
EFIAPI
HeciOnPciEnumerationComplete (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  EFI_STATUS            Status;
  UINT32                DeviceIndex;
  VOID                  *Interface;

  Status = gBS->LocateProtocol (
                  &gEfiPciEnumerationCompleteProtocolGuid,
                  NULL,
                  &Interface
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  ///
  /// Update global HECI device context after PCI enumeration
  ///
  for (DeviceIndex = Heci1; DeviceIndex < HeciMax; DeviceIndex++) {
    CheckAndFixHeciForAccess (DeviceIndex);

    if (mHeciDeviceContext[DeviceIndex].RuntimeAccessible) {
      Status = HeciSetRuntimeMemoryAttributes (DeviceIndex);
      if (Status == EFI_NOT_FOUND) {
        DEBUG ((DEBUG_WARN, "The HECI device is unavailable.\n"));
      } else {
        ASSERT_EFI_ERROR (Status);
      }
    }
  }
}

/**
  Constructor for the Runtime DXE HECI Runtime library.

  @param  ImageHandle  ImageHandle of the loaded driver.
  @param  SystemTable  Pointer to the EFI System Table.

  @retval  EFI_SUCCESS            Register successfully.
  @retval  EFI_OUT_OF_RESOURCES   No enough memory to register this handler.
**/
EFI_STATUS
EFIAPI
HeciRuntimeLibConstructor (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS    Status;
  VOID          *Registration;

  InitializeHeciDeviceContext ();

  EfiCreateProtocolNotifyEvent (
    &gEfiPciEnumerationCompleteProtocolGuid,
    TPL_CALLBACK,
    HeciOnPciEnumerationComplete,
    NULL,
    &Registration
    );

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  HeciExitBootServicesCallback,
                  NULL,
                  &gEfiEventExitBootServicesGuid,
                  &mExitBootServicesEvent
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEventEx(
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  HeciRuntimeAddressChangeEvent,
                  NULL,
                  &gEfiEventVirtualAddressChangeGuid,
                  &mVirtualAddressChangeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

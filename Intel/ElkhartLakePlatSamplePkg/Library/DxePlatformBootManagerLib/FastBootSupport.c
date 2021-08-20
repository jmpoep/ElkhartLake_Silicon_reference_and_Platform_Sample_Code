/** @file

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include "BdsPlatform.h"
#include "FastBootSupport.h"
#include "OemSetup.h"

extern BOOLEAN                  mAnyKeypressed;

#if FixedPcdGetBool(PcdTpm2Enable) == 1
//
// Physical Presence requires UI confirm
//
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN      gPPRequireUIConfirm = FALSE;
#endif
GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN      mFastBootExceptionType2Happened = TRUE;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_GUID     mFastBootConsoleVariableGuid = {0xb14fd152, 0xf5e5, 0x478f, { 0xbc, 0x43, 0x1e, 0xed, 0x79, 0xb6, 0xf, 0xab} };

/**
  Check whether the 1st Boot Option is a USB device or not
  @param                        none
  @retval TRUE                  The 1st Boot Option is a USB device
  @retvar FALSE                 The 1st Boot Option is not a USB device
**/
BOOLEAN
FirstBootOptionIsUsb (
  VOID
  )
{
  EFI_STATUS                      Status;
  CHAR16                          OptionName[sizeof ("Boot####")];
  UINT16                          *BootOrder;
  UINTN                           Size;
  EFI_BOOT_MANAGER_LOAD_OPTION    BootOption;
  EFI_DEVICE_PATH_PROTOCOL        *Node;

  GetEfiGlobalVariable2 (L"BootOrder", (VOID **) &BootOrder, &Size);
  if (BootOrder == NULL) {
    return FALSE;
  }

  UnicodeSPrint (OptionName, sizeof (OptionName), L"Boot%04X", BootOrder[0]);
  FreePool (BootOrder);

  Status = EfiBootManagerVariableToLoadOption (OptionName, &BootOption);
  ASSERT_EFI_ERROR (Status);

  for (Node = BootOption.FilePath; !IsDevicePathEnd (Node); Node = NextDevicePathNode (Node)) {
    if ((DevicePathType (Node) == MESSAGING_DEVICE_PATH) &&
        ((DevicePathSubType (Node) == MSG_USB_CLASS_DP) ||
         (DevicePathSubType (Node) == MSG_USB_DP)))     {
      EfiBootManagerFreeLoadOption (&BootOption);
      return TRUE;
    }
  }
  EfiBootManagerFreeLoadOption (&BootOption);
  return FALSE;

}

VOID
RemoveUsbAndSerial (
  VOID    **Variable,
  UINTN   *VariableSize
  )
{
  EFI_DEVICE_PATH_PROTOCOL    *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL    *CopyOfDevicePath;
  EFI_DEVICE_PATH_PROTOCOL    *NewDevicePath;
  EFI_DEVICE_PATH_PROTOCOL    *TempDevicePath;
  EFI_DEVICE_PATH_PROTOCOL    *Instance;
  EFI_DEVICE_PATH_PROTOCOL    *Next;
  UINTN                       Size;
  BOOLEAN                     NeedToRemoveUsb;

  //
  // Check whether the 1st boot option is a USB device or not. If it is, the USB device path
  // must be kept; otherwise the USB device boot option will not be connected successfully.
  //
  NeedToRemoveUsb = FirstBootOptionIsUsb() ? FALSE : TRUE;
  DevicePath      = DuplicateDevicePath ((EFI_DEVICE_PATH_PROTOCOL*) *Variable);
  if (DevicePath == NULL) {
    return;
  }

  CopyOfDevicePath = DevicePath;
  NewDevicePath    = NULL;
  do {
    //
    // The outer loop handles multi instance device paths.
    //
    // After this call DevicePath points to the next Instance
    //
    Instance  = GetNextDevicePathInstance (&DevicePath, &Size);
    ASSERT (Instance != NULL);
    if (Instance == NULL) return;

    Next = Instance;
    while (!IsDevicePathEndType (Next)) {
      //
      // Early break when it's a USB device path
      //
      if (NeedToRemoveUsb && (Next->Type == MESSAGING_DEVICE_PATH) && ((Next->SubType == MSG_USB_DP) || (Next->SubType == MSG_USB_CLASS_DP))) {
        break;
      }

      //
      // Early break when it's a serial device path
      // Note: Check EISA_PNP_ID (0x501) instead of UART node because we only want to disable the local serial but not the SOL
      //       SOL device path doesn't contain the EISA_PNP_ID (0x501)
      //
      if ((Next->Type == ACPI_DEVICE_PATH) && (Next->SubType == ACPI_DP) &&
          (((ACPI_HID_DEVICE_PATH *) Next)->HID == EISA_PNP_ID (0x501))
          ) {
        break;
      }
      Next = NextDevicePathNode (Next);
    }
    if (IsDevicePathEndType (Next)) {
      SetDevicePathEndNode (Next);
      TempDevicePath = NewDevicePath;
      NewDevicePath  = AppendDevicePathInstance (TempDevicePath, Instance);
      if (TempDevicePath != NULL) {
        FreePool (TempDevicePath);
      }
    }
  } while (DevicePath != NULL);

  FreePool (CopyOfDevicePath);
  *Variable     = NewDevicePath;
  *VariableSize = GetDevicePathSize (NewDevicePath);
}

/**
  Check if PS2 keyboard is conntected, by sending ECHO command.
  @param                        none
  @retval TRUE                  connected
  @retvar FALSE                 unconnected
**/
BOOLEAN
DetectPs2Keyboard (
  VOID
  )
{
  UINT32                TimeOut;
  UINT32                RegEmptied;
  UINT8                 Data;
  UINT32                SumTimeOut;
  UINT32                GotIt;

  TimeOut     = 0;
  RegEmptied  = 0;

  //
  // Wait for input buffer empty
  //
  for (TimeOut = 0; TimeOut < PS2_KEYBOARD_TIMEOUT; TimeOut += 30) {
    if ((IoRead8 (KEYBOARD_8042_STATUS_REGISTER) & 0x02) == 0) {
      RegEmptied = 1;
      break;
    }
    MicroSecondDelay (30);
  }

  if (RegEmptied == 0) {
    return FALSE;
  }

  //
  // Write it
  //
  IoWrite8 (KEYBOARD_8042_DATA_REGISTER, KBC_INPBUF_VIA60_KBECHO);

  //
  // wait for 1s
  //
  GotIt       = 0;
  TimeOut     = 0;
  SumTimeOut  = 0;
  Data = 0;

  //
  // Read from 8042 (multiple times if needed)
  // until the expected value appears
  // use SumTimeOut to control the iteration
  //
  while (1) {

    //
    // Perform a read
    //
    for (TimeOut = 0; TimeOut < PS2_KEYBOARD_TIMEOUT; TimeOut += 30) {
      if (IoRead8 (KEYBOARD_8042_STATUS_REGISTER) & 0x01) {
        Data = IoRead8 (KEYBOARD_8042_DATA_REGISTER);
        break;
      }
      MicroSecondDelay (30);
    }

    SumTimeOut += TimeOut;

    if (PcdGetBool (PcdDetectPs2KbOnCmdAck)) {
      if(Data == PS2_KEYBOARD_CMDECHO_ACK) {
        GotIt = 1;
        break;
      }
    }

    if (Data == KBC_INPBUF_VIA60_KBECHO) {
      GotIt = 1;
      break;
    }

    if (SumTimeOut >= PS2_KEYBOARD_WAITFORVALUE_TIMEOUT) {
      break;
    }
  }

  //
  // Check results
  //
  if (GotIt == 1) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Check if PS2 keyboard is conntected. If the result of first time is
  error, it will retry again.
  @param                        none
  @retval TRUE                  connected
  @retvar FALSE                 unconnected
**/
BOOLEAN
IsPs2KeyboardConnected (
  VOID
  )
{
  BOOLEAN Result;

  Result = DetectPs2Keyboard ();

  if (Result == FALSE) {
    //
    // If there is no ps2 keyboard detected for the 1st time, retry again.
    //
    Result = DetectPs2Keyboard ();
  }

  return Result;
}

/**
  Update the ConIn variable to either Ps2 keyboard or USB keyboard.
  @param    IsPs2Keyboard       Is Ps2 keyboard connected
  @retval                       none
**/
VOID
UpdateConInVariable (
  BOOLEAN    IsPs2Keyboard
  )
{

  if (IsPs2Keyboard) {
    gRT->SetVariable (
           L"ConIn",
           &gEfiGlobalVariableGuid,
           EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
           sizeof (gKeyboardDevicePath),
           &gKeyboardDevicePath
           );
  } else {
    gRT->SetVariable (
           L"ConIn",
           &gEfiGlobalVariableGuid,
           EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
           sizeof (gUsbClassKeyboardDevicePath),
           &gUsbClassKeyboardDevicePath
           );
  }
}

/**
  Detect if user changed ConIn device.
  @param                        none
  @retval EFI_SUCCESS           User didn't change the ConIn device
  @retvar EFI_MEDIA_CHANGED     User changed the ConIn device
  @retvar EFI_DEVICE_ERROR      Cannot find ConIn variable
**/
EFI_STATUS
FastBootEnumConInDevice (
  VOID
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *VarConIn;
  EFI_DEVICE_PATH_PROTOCOL  *TempDevicePath;
  ACPI_HID_DEVICE_PATH      *DevicePathHid;
  EFI_STATUS                Status;
  BOOLEAN                   Ps2Keyboard;
  UINTN                     Size;

  Status = EFI_SUCCESS;

  if (mSystemConfiguration.ConInBehavior == PS2_CONSOLE) {
    GetEfiGlobalVariable2 (L"ConIn", (VOID **) &VarConIn, &Size);
    if ((VarConIn == NULL) || (Size < sizeof (EFI_DEVICE_PATH_PROTOCOL))) {
      return EFI_DEVICE_ERROR;
    }

    Ps2Keyboard = FALSE;
    if ((VarConIn->Type == MESSAGING_DEVICE_PATH) && (VarConIn->SubType == MSG_USB_CLASS_DP)) {
      //
      // The ConIn variable is USB keyboard, check if PS/2 keyboard is connected.
      //
      if (IsPs2KeyboardConnected ()) {
        Status = EFI_MEDIA_CHANGED;
        Ps2Keyboard = TRUE;
      }
    } else {
      TempDevicePath = NextDevicePathNode (NextDevicePathNode (VarConIn));
      DevicePathHid = (ACPI_HID_DEVICE_PATH *) TempDevicePath;
      if (DevicePathHid->HID == EISA_PNP_ID (0x0303)) {
        //
        // The ConIn variable is Ps2 keyboard, check if PS/2 keyboard is connected.
        //
        if (IsPs2KeyboardConnected ()) {
          Ps2Keyboard = TRUE;
        } else {
          Status = EFI_MEDIA_CHANGED;
        }
      }
    }

    if (Status == EFI_MEDIA_CHANGED) {
      UpdateConInVariable (Ps2Keyboard);
    }

    FreePool (VarConIn);
  }

  return Status;
}

/**
  When FastBoot is enabled, all input devices may not be connected by default.
  Hence, when entering into Setup menu, connecting all input consoles are required.

  @param[in]  Event                  The Event this notify function registered to.
  @param[in]  Context                Pointer to the context data registerd to the
                                     Event.

  @return None.
**/
VOID
EFIAPI
ConnectAllConsoles (
  EFI_EVENT Event,
  VOID      *Context
  )
{
  EFI_STATUS  Status;
  VOID        *Protocol;
  UINTN       Index;

  Status = gBS->LocateProtocol(
                  &gSetupEnterGuid,
                  NULL,
                  &Protocol
                  );
  if (EFI_ERROR (Status)) {
    return;
  }

  gBS->CloseEvent (Event);

  for (Index = 0; gPlatformConsole[Index].DevicePath != NULL; Index++) {
    //
    // Update the console Input variable
    //
    if ((gPlatformConsole[Index].ConnectType & CONSOLE_IN) == CONSOLE_IN) {
      EfiBootManagerUpdateConsoleVariable (ConIn, gPlatformConsole[Index].DevicePath, NULL);
    }
  }

  EfiBootManagerConnectAllDefaultConsoles();
  gDS->Dispatch ();
}

/**
  Update ConIn by corresponding console input behavior.
  @param                        none
  @retval                       none
**/
VOID
FastBootUpdateConInVarByConInBehavior (
  VOID
  )
{
  VOID        *SetupRegistration;
  UINTN       Index;

  switch (mSystemConfiguration.ConInBehavior) {
    case PS2_CONSOLE:
      UpdateEfiGlobalVariable (L"ConIn", &mFastBootConsoleVariableGuid, RemoveUsbAndSerial);
      break;

    case RECONNECT_LAST_GOOD_INPUT_CONSOLE:
      for (Index = 0; gPlatformConsole[Index].DevicePath != NULL; Index++) {
        //
        // Update variable ConIn with all input console device path
        //
        if ((gPlatformConsole[Index].ConnectType & CONSOLE_IN) == CONSOLE_IN) {
          EfiBootManagerUpdateConsoleVariable (ConIn, gPlatformConsole[Index].DevicePath, NULL);
        }
      }
      break;

    case WINDOWS_CONSOLE:
      //
      // Remove all device path from ConIn.
      // BIOS should not enumerate any input devices when Windows Console behavior is used
      //
      gRT->SetVariable (
             L"ConIn",
             &gEfiGlobalVariableGuid,
             EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
             0,
             NULL
             );
      break;

    default:
      break;
  }

  //
  // Register notification event for enter setup event
  //
  EfiCreateProtocolNotifyEvent(
       &gSetupEnterGuid,
       TPL_CALLBACK,
       ConnectAllConsoles,
       NULL,
       &SetupRegistration
       );

}

VOID
FastBootUpdateConsoleVariable (
  VOID
  )
{
  if (FastBootEnabled ()){
    FastBootUpdateConInVarByConInBehavior();
    UpdateEfiGlobalVariable (L"ConOut", &mFastBootConsoleVariableGuid, RemoveUsbAndSerial);
    UpdateEfiGlobalVariable (L"ErrOut", &mFastBootConsoleVariableGuid, RemoveUsbAndSerial);
  }
}

BOOLEAN
FastBootEnabled (
  VOID
  )
{
  return mSystemConfiguration.FastBoot;
}

BOOLEAN
IsExceptionType2Detected (
  VOID
  )
{
  return mFastBootExceptionType2Happened;
}

/*++

Routine Description:

  This funtion is used to get platform boot mode.
  If fitting any of the following conditions, the silent boot is enabled:
    1. FastBoot enabled and user doesn't press any key during POST
    2. mSystemConfiguration.BootMode is SILENT_BOOT and FastBoot is disabled.
  If mSystemConfiguration.BootMode is QUIET_BOOT, the quiet boot is enabled
  Otherwise, it is normal boot

Arguments:

Returns:

  NORMAL_BOOT  - Current boot mode is normal boot.
  QUIET_BOOT   - Current boot mode is quiet boot.
  SILENT_BOOT  - Current boot mode is silent boot.

--*/
UINT8
GetDisplayBootMode (
  VOID
  )
{
  UINT8       BootMode;

  if ((FastBootEnabled () && !mAnyKeypressed) || (mSystemConfiguration.DisplayBootMode == SILENT_BOOT && !FastBootEnabled ())) {
    BootMode = SILENT_BOOT;
  } else if (!FastBootEnabled () && mSystemConfiguration.DisplayBootMode == QUIET_BOOT) {
    BootMode = QUIET_BOOT;
  } else {
    BootMode = NORMAL_BOOT;
  }

  return BootMode;
}

VOID
FastBootGenericVariablesInit (
  VOID
  )
{
  EFI_STATUS                      Status;
  FAST_BOOT_EXCEPTION_PROTOCOL    *FastBootExceptionProtocol;
  EFI_HANDLE                      *HandleBuffer;
  UINTN                           HandleCount;
  UINTN                           Index;

  mFastBootExceptionType2Happened = TRUE;

  if (!FastBootEnabled ()) {
    return;
  }

  //
  // Locate all handles of Fast Boot Exception protocol
  //
  mFastBootExceptionType2Happened = FALSE;
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gFastBootExceptionProtocolGuid,
                  NULL,
                  &HandleCount,
                  &HandleBuffer
                  );
  if (EFI_ERROR (Status)) {
    if (Status != EFI_NOT_FOUND) {
      mFastBootExceptionType2Happened = TRUE;
    }
  } else {
    //
    // Exception Type statistic for subsequent BDS code
    //
    //
    // Get FAST_BOOT_EXCEPTION_TYPE with gFastBootExceptionProtocolGuid
    //
    for (Index = 0; Index < HandleCount; Index += 1) {
      Status = gBS->HandleProtocol (
                      HandleBuffer[Index],
                      &gFastBootExceptionProtocolGuid,
                      (VOID **) &FastBootExceptionProtocol
                      );
      if (EFI_ERROR (Status)) {
        continue;
      }
      if (FastBootExceptionProtocol->FbExceptionType > ExceptionType1) {
        mFastBootExceptionType2Happened = TRUE;
        break;
      }
    }
  }
}

EFI_STATUS
RaiseFastBootException (
  FAST_BOOT_EXCEPTION_TYPE      ExceptionType,
  FAST_BOOT_EXCEPTION_CATEGORY  ExceptionCategory
  )
{
  FAST_BOOT_EXCEPTION_PROTOCOL *FastBootException;
  EFI_HANDLE                   Handle;

  if (!FastBootEnabled()) {
    return EFI_SUCCESS;
  }

  if (ExceptionType > ExceptionType1) {
    mFastBootExceptionType2Happened = TRUE;
  }

  FastBootException = AllocatePool (sizeof (FAST_BOOT_EXCEPTION_PROTOCOL));
  if (FastBootException == NULL) {
    return EFI_SUCCESS;
  }

  FastBootException->FbExceptionType     = ExceptionType;
  FastBootException->FbExceptionCategory = ExceptionCategory;

  Handle = NULL;

  return gBS->InstallProtocolInterface (
                &Handle,
                &gFastBootExceptionProtocolGuid,
                EFI_NATIVE_INTERFACE,
                FastBootException
                );
}

VOID
FastBootUpdateBootMode (
  EFI_BOOT_MODE *BootMode
  )
{
  if (FastBootEnabled()) {
    if ( (*BootMode == BOOT_ON_S4_RESUME) && (!IsExceptionType2Detected()) ) {
      *BootMode = BOOT_WITH_MINIMAL_CONFIGURATION;
    } else if (*BootMode == BOOT_WITH_MINIMAL_CONFIGURATION) {
      if (IsExceptionType2Detected()) {
        *BootMode = BOOT_WITH_FULL_CONFIGURATION;
      }
    }
  }
}

/**
  Connect USB devices by the necessity when Fast Boot is enabled.
  @param                        none
  @retval                       none
**/
VOID
FastBootBootOptionPatch(
  EFI_BOOT_MODE                         BootMode
  )
{
  EFI_STATUS                            Status;
  CHAR16                                OptionName[sizeof ("Boot####")];
  UINT16                                *BootOrder;
  UINTN                                 Size;
  EFI_BOOT_MANAGER_LOAD_OPTION          BootOption;
  EFI_DEVICE_PATH_PROTOCOL              *BootNode;
  BOOLEAN                               IsUsbBootOption;

  EFI_DEVICE_PATH_PROTOCOL              *ConIn;
  EFI_DEVICE_PATH_PROTOCOL              *ConInNode;
  BOOLEAN                               NeedToConnectUsb;

  EFI_HANDLE                            *Handles;
  UINTN                                 HandleCount;
  UINTN                                 Index;
  EFI_PCI_IO_PROTOCOL                   *PciIo;
  UINT8                                 Class[3];

  if (!FastBootEnabled()) {
    return;
  }

  if ((BootMode != BOOT_WITH_MINIMAL_CONFIGURATION)
    && (BootMode != BOOT_WITH_FULL_CONFIGURATION)
    && (BootMode != BOOT_ON_S4_RESUME) ) {
    return;
  }

  //
  // When Fast Boot is enabled and no exception, only PS/2 keyboard will be connected
  // and no USB deivce won't be connected. In this case, if the first Boot Option refers to
  // an USB device, system can't boot to it. To solve this, connect the USB boot device
  // if the first Boot Option is USB device, which has not been connected yet.
  //

  //
  // Check if the fisrt Boot Option is a USB device
  //
  GetEfiGlobalVariable2 (L"BootOrder", (VOID **) &BootOrder, &Size);
  if (BootOrder == NULL) {
    return;
  }

  UnicodeSPrint (OptionName, sizeof (OptionName), L"Boot%04X", BootOrder[0]);
  FreePool (BootOrder);

  Status = EfiBootManagerVariableToLoadOption (OptionName, &BootOption);
  ASSERT_EFI_ERROR (Status);

  IsUsbBootOption = FALSE;
  for (BootNode = BootOption.FilePath; !IsDevicePathEnd (BootNode); BootNode = NextDevicePathNode (BootNode)) {
    if ((DevicePathType (BootNode) == MESSAGING_DEVICE_PATH) &&
        ((DevicePathSubType (BootNode) == MSG_USB_CLASS_DP) ||
        (DevicePathSubType (BootNode) == MSG_USB_DP))) {
      IsUsbBootOption = TRUE;
      break;
    }
  }

  //
  // Check if the ConIn device is USB keyboard.
  // If yes, it means the USB controller is connected while connecting ConIn devices.
  // And no need to re-connect USB again.
  //
  NeedToConnectUsb = TRUE;
  if (IsUsbBootOption) {
    GetEfiGlobalVariable2 (L"ConIn", (VOID **) &ConIn, &Size);
    if ((ConIn != NULL) && (Size >= sizeof (EFI_DEVICE_PATH_PROTOCOL))) {
      for (ConInNode = ConIn; !IsDevicePathEnd (ConInNode); ConInNode = NextDevicePathNode (ConInNode)) {
        if ((DevicePathType (ConInNode) == MESSAGING_DEVICE_PATH) &&
            ((DevicePathSubType (ConInNode) == MSG_USB_CLASS_DP) ||
            (DevicePathSubType (ConInNode) == MSG_USB_DP))) {
          NeedToConnectUsb = FALSE;
          break;
        }
      }
      FreePool (ConIn);
    }
  }

  //
  // Connect the USB Controllers if the first Boot Option is USB device and no USB device has been connected.
  //
  if (IsUsbBootOption && NeedToConnectUsb) {
    //
    // Find the USB HC first and then connect with the remaining device path
    //
    Status = gBS->LocateHandleBuffer (
                    ByProtocol,
                    &gEfiPciIoProtocolGuid,
                    NULL,
                    &HandleCount,
                    &Handles
                    );
    for (Index = 0; Index < HandleCount; Index++) {
      Status = gBS->HandleProtocol (
                      Handles[Index],
                      &gEfiPciIoProtocolGuid,
                      (VOID **) &PciIo
                      );
      if (!EFI_ERROR (Status)) {
        Status = PciIo->Pci.Read (PciIo, EfiPciIoWidthUint8, PCI_CLASSCODE_OFFSET, 3, &Class);
        if ((!EFI_ERROR (Status)) &&
            ((PCI_CLASS_SERIAL == Class[2]) && (PCI_CLASS_SERIAL_USB == Class[1]))
            ) {
          Status = gBS->ConnectController (
                          Handles[Index],
                          NULL,
                          BootNode,
                          FALSE
                          );
        }
      }
    }
  }

  EfiBootManagerFreeLoadOption (&BootOption);

  return;
}

/**
  Callback function to change the L"Timeout" variable.

  @param Variable        Return the variable buffer.
  @param VariableSize    Return the variable buffer length.
**/
VOID
SetNoWaiting (
  IN OUT VOID  **Variable,
  IN OUT UINTN *VariableSize
  )
{
  UINT16       *Timeout;

  ASSERT ((*VariableSize == sizeof (UINT16)) ||
          (*Variable == NULL && *VariableSize == 0)
         );
  Timeout  = AllocatePool (sizeof (UINT16));
  ASSERT (Timeout != NULL);
  if (Timeout == NULL) return;
  *Timeout = 0;

  *Variable     = Timeout;
  *VariableSize = sizeof (UINT16);
}

VOID
FastBootUpdateTimeoutVariable (
  VOID
  )
{
  if (!mAnyKeypressed && FastBootEnabled ()) {
    UpdateEfiGlobalVariable (L"Timeout", &mFastBootConsoleVariableGuid, SetNoWaiting);
  } else {
    UpdateEfiGlobalVariable (L"Timeout", &mFastBootConsoleVariableGuid, NULL);
  }
}

EFI_STATUS
EFIAPI
FastBootLibConstructor (
  IN      EFI_HANDLE                ImageHandle,
  IN      EFI_SYSTEM_TABLE          *SystemTable
  )
{
  EFI_STATUS            Status;
  UINTN                 VariableSize;

  //
  // Get current Boot Mode
  //
  gBootMode = GetBootModeHob ();

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &mSystemConfiguration
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to locate SystemConfiguation!\n"));
    ASSERT_EFI_ERROR (Status);
  }

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &mSaSetup
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to locate Setup SA veriable!\n"));
    ASSERT_EFI_ERROR (Status);
  }

#if FixedPcdGetBool(PcdTpm2Enable) == 1
  //
  // Get Physical Presence command state
  //
  gPPRequireUIConfirm = TcgPhysicalPresenceLibNeedUserConfirm();

  gPPRequireUIConfirm |= Tcg2PhysicalPresenceLibNeedUserConfirm();

  //
  // Initialize PcdConInConnectonDemand according to platform policy
  //   1. If not in NO config changed Mode, disable PcdConInConnectOnDemand
  //   2. Get physical presence command state, if true, disable PcdConInConnectOnDemand.
  //   3. Else follow SetupBrowser setting
  //
  if (gBootMode != BOOT_ASSUMING_NO_CONFIGURATION_CHANGES || gPPRequireUIConfirm) {
    PcdSetBoolS(PcdConInConnectOnDemand, FALSE);
  } else {
    PcdSetBoolS(PcdConInConnectOnDemand, (BOOLEAN)mSystemConfiguration.LazyConIn);
  }
  DEBUG((DEBUG_INFO, "PlatformBdsInit PcdConInConnectOnDemand value is %d.\n", PcdGetBool(PcdConInConnectOnDemand)));
#endif

  return EFI_SUCCESS;
}


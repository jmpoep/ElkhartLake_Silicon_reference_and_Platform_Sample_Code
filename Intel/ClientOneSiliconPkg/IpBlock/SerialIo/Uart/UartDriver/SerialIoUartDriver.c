/** @file
  Serial Io Uart Driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#include <Base.h>
#include <Protocol/PciIo.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DevicePathLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/TimerLib.h>
#include <Library/SerialIoUartLib.h>
#include <Library/SerialIoPrivateLib.h>
#include <IndustryStandard/Acpi10.h>
#include <IndustryStandard/Pci22.h>
#include "SerialIoUartDriver.h"

extern EFI_COMPONENT_NAME_PROTOCOL  mSerialIoUartDriverComponentName;

/**
  This function checks to see if the driver supports a device specified by
  "Controller handle" parameter. It is called by DXE Core StartImage() or
  ConnectController() routines. The driver uses 'device path' and/or
  'services' from the Bus I/O abstraction attached to the controller handle
  to determine if the driver support this controller handle.

  Note: In the BDS (Boot Device Selection) phase, the DXE core enumerate all
  devices (or, controller) and assigns GUIDs to them.

  @param[in] This                 a pointer points to the Binding Protocol instance
  @param[in] Controller           The handle of controller to be tested.
  @param[in] RemainingDevicePath  A pointer to the device path. Ignored by device
                                  driver but used by bus driver

  @retval EFI_SUCCESS             Controller is supported by this device
          EFI_ALREADY_STARTED     Driver is already installed
          EFI_UNSUPPORTED         Controller is not supported
**/
EFI_STATUS
EFIAPI
SerialIoUartDriverSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                Status;
  EFI_SERIAL_IO_PROTOCOL    SerialIoProtocol;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *EndPath;
  UINT16                    DeviceId;
  UINT8                     UartIndex;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiSerialIoProtocolGuid,
                  (VOID **) &SerialIoProtocol,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_TEST_PROTOCOL
                  );
  if (Status == EFI_SUCCESS) {
    return EFI_ALREADY_STARTED;
  }

  DevicePath = DevicePathFromHandle ( Controller );
  if (DevicePath == NULL) {
    return EFI_UNSUPPORTED;
  }
  EndPath = DevicePath;
  while (!IsDevicePathEnd (EndPath)) {
    DevicePath = EndPath;
    EndPath    = NextDevicePathNode (EndPath);
  }

  DeviceId  = 0xFFFF;
  UartIndex = 0xFF;
  if (DevicePath->Type == ACPI_DEVICE_PATH && DevicePath->SubType == ACPI_EXTENDED_DP) {
    DeviceId =  (UINT16)(((SERIAL_IO_UART_ACPI_EXTENDED_DEVICE_PATH*)DevicePath)->DeviceId);
    UartIndex = (UINT8) (((SERIAL_IO_UART_ACPI_EXTENDED_DEVICE_PATH*)DevicePath)->UartIndex);
  } else {
    return EFI_UNSUPPORTED;
  }

  if ((DeviceId == 0xFFFF) || (UartIndex == 0xFF) || (UartIndex > 2) || (DeviceId != GetSerialIoUartDeviceId (UartIndex))) {
    return EFI_UNSUPPORTED;
  }

  return EFI_SUCCESS;
}

/**
  Stop Uart Driver.

  @param[in] This                 Pointer to driver binding protocol
  @param[in] Controller           Controller handle to connect
  @param[in] NumberOfChildren     Number of children handle created by this driver
  @param[in] ChildHandleBuffer    Buffer containing child handle created

  @retval EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
SerialIoUartDriverStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                     Controller,
  IN  UINTN                          NumberOfChildren,
  IN  EFI_HANDLE                     *ChildHandleBuffer
  )
{
  EFI_STATUS                Status;
  EFI_SERIAL_IO_PROTOCOL    *SerialIoProtocol;
  SERIAL_IO_UART_DEV        *UartDevice;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;

  Status = gBS->HandleProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath
                  );

  if (!EFI_ERROR (Status)) {
    gBS->CloseProtocol (
           Controller,
           &gEfiDevicePathProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
  }

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiSerialIoProtocolGuid,
                  (VOID **) &SerialIoProtocol,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (!EFI_ERROR (Status)) {
    UartDevice = SERIAL_IO_UART_DEV_FROM_THIS (SerialIoProtocol);
    gBS->UninstallMultipleProtocolInterfaces (
           Controller,
           &gEfiDevicePathProtocolGuid,
           UartDevice->DevicePath,
           &gEfiSerialIoProtocolGuid,
           &UartDevice->SerialIoProtocol,
           NULL
           );
    if (UartDevice->ControllerNameTable != NULL) {
      FreeUnicodeStringTable (UartDevice->ControllerNameTable);
    }
    if (UartDevice->DevicePath != NULL) {
      FreePool (UartDevice->DevicePath);
    }
    FreePool (UartDevice);
  }

  return EFI_SUCCESS;
}

/**
  Reset serial device

  @param[in] This                 Pointer to EFI_SERIAL_IO_PROTOCOL

  @retval EFI_SUCCESS             Reset successfully
  @retval EFI_DEVICE_ERROR        Failed to reset
**/
EFI_STATUS
EFIAPI
SerialIoUartDriverReset (
  IN EFI_SERIAL_IO_PROTOCOL       *This
  )
{
  return EFI_SUCCESS;
}

/**
  Set new attributes to uart device

  @param[in] This                 Pointer to EFI_SERIAL_IO_PROTOCOL
  @param[in] BaudRate             The baudrate of the serial device
  @param[in] ReceiveFifoDepth     Fifo depth
  @param[in] Timeout              The request timeout for a single char
  @param[in] Parity               The type of parity used in serial device
  @param[in] DataBits             Number of databits used in serial device
  @param[in] StopBits             Number of stopbits used in serial device

  @retval EFI_DEVICE_ERROR        Failed o Append Device Path Node
          EFI_SUCCESS             New attributes were set
          EFI_ERROR               Failed o Reinstall Protocol Interface

**/
EFI_STATUS
EFIAPI
SerialIoUartDriverSetAttributes (
  IN EFI_SERIAL_IO_PROTOCOL       *This,
  IN UINT64                       BaudRate,
  IN UINT32                       ReceiveFifoDepth,
  IN UINT32                       Timeout,
  IN EFI_PARITY_TYPE              Parity,
  IN UINT8                        DataBits,
  IN EFI_STOP_BITS_TYPE           StopBits
  )
{
  EFI_STATUS                Status;
  SERIAL_IO_UART_DEV        *UartDevice;
  EFI_DEVICE_PATH_PROTOCOL  *NewDevicePath;

  UartDevice = SERIAL_IO_UART_DEV_FROM_THIS (This);

  //
  // See if the new attributes already match the current attributes
  //
  if (UartDevice->UartDevicePath.BaudRate == BaudRate &&
      UartDevice->UartDevicePath.DataBits == DataBits &&
      UartDevice->UartDevicePath.Parity == Parity &&
      UartDevice->UartDevicePath.StopBits == StopBits &&
      UartDevice->SerialIoMode.ReceiveFifoDepth == ReceiveFifoDepth &&
      UartDevice->SerialIoMode.Timeout == Timeout
      ) {
    return EFI_SUCCESS;
  }

  //
  // IgnoreBaudRateSet
  // - Disallows UART settings to be changed by the Serial Io Protocol.
  // - Required to support redirection on higher BaudRates,
  //   also avoids reconfiguration done initaily by DebugLibrary.
  //
  if (!PcdGetBool (PcdSerialIoUartDriverIgnoreBaudRateSet)) {
    SerialIoUartSetAttributes (
      UartDevice->UartIndex,
      BaudRate,
      Parity,
      DataBits,
      StopBits,
      UartDevice->AutoFlow
      );
  }

  //
  // Set the Serial I/O mode
  //
  This->Mode->BaudRate          = BaudRate;
  This->Mode->ReceiveFifoDepth  = ReceiveFifoDepth;
  This->Mode->Timeout           = Timeout;
  This->Mode->Parity            = Parity;
  This->Mode->DataBits          = DataBits;
  This->Mode->StopBits          = StopBits;

  //
  // See if Device Path Node has actually changed
  //
  if (UartDevice->UartDevicePath.BaudRate == BaudRate &&
      UartDevice->UartDevicePath.DataBits == DataBits &&
      UartDevice->UartDevicePath.Parity == Parity &&
      UartDevice->UartDevicePath.StopBits == StopBits
      ) {
    return EFI_SUCCESS;
  }
  //
  // Update the device path
  //
  UartDevice->UartDevicePath.BaudRate = BaudRate;
  UartDevice->UartDevicePath.DataBits = DataBits;
  UartDevice->UartDevicePath.Parity   = (UINT8) Parity;
  UartDevice->UartDevicePath.StopBits = (UINT8) StopBits;

  NewDevicePath = AppendDevicePathNode (
                    UartDevice->ParentDevicePath,
                    (EFI_DEVICE_PATH_PROTOCOL *) &UartDevice->UartDevicePath
                    );
  if (NewDevicePath == NULL) {
    return EFI_DEVICE_ERROR;
  }

  if (UartDevice->Handle != NULL) {
    Status = gBS->ReinstallProtocolInterface (
                    UartDevice->Handle,
                    &gEfiDevicePathProtocolGuid,
                    UartDevice->DevicePath,
                    NewDevicePath
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  if (UartDevice->DevicePath != NULL) {
    FreePool (UartDevice->DevicePath);
  }

  UartDevice->DevicePath = NewDevicePath;

  return EFI_SUCCESS;
}

/**
  Set ControlBits

  @param[in] This                 Pointer to EFI_SERIAL_IO_PROTOCOL
  @param[in] Control              Control bits that can be settable

  @retval EFI_UNSUPPORTED         TBD
**/
EFI_STATUS
EFIAPI
SerialIoUartDriverSetControl (
  IN EFI_SERIAL_IO_PROTOCOL       *This,
  IN UINT32                       Control
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Get ControlBits

  @param[in] This                 Pointer to EFI_SERIAL_IO_PROTOCOL
  @param[in] Control              Control signals of the serial device

  @retval EFI_UNSUPPORTED         TBD
**/
EFI_STATUS
EFIAPI
SerialIoUartDriverGetControl (
  IN EFI_SERIAL_IO_PROTOCOL       *This,
  OUT UINT32                      *Control
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Write the specified number of bytes to uart device

  @param[in] This                 Pointer to EFI_SERIAL_IO_PROTOCOL
  @param[in] BufferSize           On input the size of Buffer, on output the amount of data actually written
  @param[in] Buffer               The buffer of data to write

  @retval EFI_SUCCESS             The data were written successfully
  @retval EFI_DEVICE_ERROR        The device reported an error
**/
EFI_STATUS
EFIAPI
SerialIoUartDriverWrite (
  IN EFI_SERIAL_IO_PROTOCOL       *This,
  IN OUT UINTN                    *BufferSize,
  IN VOID                         *Buffer
  )
{
  EFI_TPL                   Tpl;
  SERIAL_IO_UART_DEV        *UartDevice;
  UartDevice = SERIAL_IO_UART_DEV_FROM_THIS (This);

  if (Buffer == NULL) {
    return EFI_DEVICE_ERROR;
  }

  Tpl = gBS->RaiseTPL (TPL_NOTIFY);
  SerialIoUartWrite (UartDevice->UartIndex, Buffer, *BufferSize);
  gBS->RestoreTPL (Tpl);

  return EFI_SUCCESS;
}

/**
  Read the specified number of bytes from uart device

  @param[in] This                 Pointer to EFI_SERIAL_IO_PROTOCOL
  @param[in] BufferSize           On input the size of Buffer, on output the amount of data returned in buffer
  @param[in] Buffer               The buffer to return the data into

  @retval EFI_SUCCESS             The data were read successfully
  @retval EFI_DEVICE_ERROR        The device reported an error
  @retval EFI_TIMEOUT             The device did not read any data
**/
EFI_STATUS
EFIAPI
SerialIoUartDriverRead (
  IN EFI_SERIAL_IO_PROTOCOL       *This,
  IN OUT UINTN                    *BufferSize,
  OUT VOID                        *Buffer
  )
{
  EFI_TPL                   Tpl;
  SERIAL_IO_UART_DEV        *UartDevice;
  UartDevice = SERIAL_IO_UART_DEV_FROM_THIS (This);

  if (*BufferSize == 0) {
    return EFI_SUCCESS;
  }

  if (Buffer == NULL) {
    return EFI_DEVICE_ERROR;
  }
  Tpl = gBS->RaiseTPL (TPL_NOTIFY);
  *BufferSize = SerialIoUartRead (UartDevice->UartIndex, Buffer, *BufferSize, FALSE);
  if (*BufferSize == 0) {
    gBS->RestoreTPL (Tpl);
    return EFI_TIMEOUT;
  }
  gBS->RestoreTPL (Tpl);

  return EFI_SUCCESS;
}

/**
  This routine is called right after the .Supported() called
  and return EFI_SUCCESS. Notes: The supported protocols are
  checked but the Protocols are closed.

  @param[in] This                 A pointer points to the Binding Protocol instance
  @param[in] Controller           The handle of controller to be tested. Parameter
                                  passed by the caller
  @param[in] RemainingDevicePath  A pointer to the device path. Should be ignored by
                                  device driver

  @retval EFI_SUCCESS             The driver ready and initial complete.
  @retval Other                   The device doesn't initial.
**/
EFI_STATUS
EFIAPI
SerialIoUartDriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                          Status;
  SERIAL_IO_UART_DEV                  *UartDevice;
  CHAR16                              SerialPortName[sizeof (SERIAL_IO_UART_NAME)];
  EFI_DEVICE_PATH_PROTOCOL            *ParentDevicePath;
  EFI_DEVICE_PATH_PROTOCOL            *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL            *EndPath;
  UINT8                               UartIndex;

  UartDevice = NULL;

  //
  // Get the Parent Device Path
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &ParentDevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status) && Status != EFI_ALREADY_STARTED) {
    return Status;
  }

  //
  // Initialize the serial device instance
  //
  UartDevice = AllocateZeroPool (sizeof (SERIAL_IO_UART_DEV));
  if (UartDevice == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto Error;
  }

  UartDevice->ParentDevicePath    = ParentDevicePath;
  UartDevice->ControllerNameTable = NULL;

  DevicePath = DevicePathFromHandle (Controller);
  if (DevicePath == NULL) {
    return EFI_UNSUPPORTED;
  }
  EndPath = DevicePath;
  while (!IsDevicePathEnd (EndPath)) {
    DevicePath = EndPath;
    EndPath    = NextDevicePathNode (EndPath);
  }

  UartIndex = (UINT8)(((SERIAL_IO_UART_ACPI_EXTENDED_DEVICE_PATH*)DevicePath)->UartIndex);

  StrCpyS (SerialPortName, sizeof (SerialPortName) / sizeof (CHAR16), L"Serial IO UART Driver Controller #");
  SerialPortName[sizeof (SERIAL_IO_UART_NAME) - 2] = (CHAR16) ((CHAR16) ('0' + UartIndex));
  AddUnicodeString (
    "eng",
    mSerialIoUartDriverComponentName.SupportedLanguages,
    &UartDevice->ControllerNameTable,
    (CHAR16 *) SerialPortName
    );

  UartDevice->Signature               = SERIAL_IO_UART_DEV_SIGNATURE;
  UartDevice->Handle                  = NULL;
  UartDevice->UartIndex               = UartIndex;
  UartDevice->AutoFlow                = FALSE;

  UartDevice->SerialIoProtocol.Revision       = EFI_SERIAL_IO_PROTOCOL_REVISION;
  UartDevice->SerialIoProtocol.Reset          = SerialIoUartDriverReset;
  UartDevice->SerialIoProtocol.SetAttributes  = SerialIoUartDriverSetAttributes;
  UartDevice->SerialIoProtocol.SetControl     = SerialIoUartDriverSetControl;
  UartDevice->SerialIoProtocol.GetControl     = SerialIoUartDriverGetControl;
  UartDevice->SerialIoProtocol.Write          = SerialIoUartDriverWrite;
  UartDevice->SerialIoProtocol.Read           = SerialIoUartDriverRead;
  UartDevice->SerialIoProtocol.Mode           = &(UartDevice->SerialIoMode);

  if (RemainingDevicePath != NULL) {
    //
    // Match the configuration of the RemainingDevicePath. IsHandleSupported()
    // already checked to make sure the RemainingDevicePath contains settings
    // that we can support.
    //
    CopyMem (&UartDevice->UartDevicePath, RemainingDevicePath, sizeof (UART_DEVICE_PATH));
  } else {
    //
    // Build the device path by appending the UART node to the ParentDevicePath
    //
    ZeroMem (&UartDevice->UartDevicePath, sizeof (UART_DEVICE_PATH));
    UartDevice->UartDevicePath.Header.Type    = MESSAGING_DEVICE_PATH;
    UartDevice->UartDevicePath.Header.SubType = MSG_UART_DP;
    SetDevicePathNodeLength ((EFI_DEVICE_PATH_PROTOCOL *) &UartDevice->UartDevicePath, sizeof (UART_DEVICE_PATH));
  }
  //
  // Build the device path by appending the UART node to the ParentDevicePath
  // from the WinNtIo handle. The Uart setings are zero here, since
  // SetAttribute() will update them to match the current setings.
  //
  UartDevice->DevicePath = AppendDevicePathNode (
                               ParentDevicePath,
                               (EFI_DEVICE_PATH_PROTOCOL *) &UartDevice->UartDevicePath
                               );

  if (UartDevice->DevicePath == NULL) {
    Status = EFI_DEVICE_ERROR;
    goto Error;
  }
  //
  // Fill in Serial I/O Mode structure based on either the RemainingDevicePath or defaults.
  //
  UartDevice->SerialIoMode.ControlMask      = FALSE; // No Flow Control
  UartDevice->SerialIoMode.Timeout          = 1000000;
  UartDevice->SerialIoMode.BaudRate         = UartDevice->UartDevicePath.BaudRate;
  UartDevice->SerialIoMode.ReceiveFifoDepth = PcdGet16 (PcdUartDefaultReceiveFifoDepth);
  UartDevice->SerialIoMode.DataBits         = UartDevice->UartDevicePath.DataBits;
  UartDevice->SerialIoMode.Parity           = UartDevice->UartDevicePath.Parity;
  UartDevice->SerialIoMode.StopBits         = UartDevice->UartDevicePath.StopBits;

  //
  // Install protocol interfaces for the serial device.
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &UartDevice->Handle,
                  &gEfiDevicePathProtocolGuid,
                  UartDevice->DevicePath,
                  &gEfiSerialIoProtocolGuid,
                  &UartDevice->SerialIoProtocol,
                  NULL
                  );

Error:
  if (EFI_ERROR (Status)) {
    gBS->CloseProtocol (
           Controller,
           &gEfiDevicePathProtocolGuid,
           This->DriverBindingHandle,
           Controller
           );
    if (UartDevice != NULL) {
      if (UartDevice->DevicePath != NULL) {
        FreePool (UartDevice->DevicePath);
      }

      FreeUnicodeStringTable (UartDevice->ControllerNameTable);
      FreePool (UartDevice);
    }
  }

  return Status;
}


GLOBAL_REMOVE_IF_UNREFERENCED EFI_DRIVER_BINDING_PROTOCOL mSerialIoUartDriverBinding = {
  SerialIoUartDriverSupported,
  SerialIoUartDriverStart,
  SerialIoUartDriverStop,
  0x10,
  NULL,
  NULL
};

/**
  Entry Point

  @param[in] ImageHandle          Handle for this drivers loaded image protocol.
  @param[in] SystemTable          EFI system table.

  @retval EFI_SUCCESS             Always return EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
SerialIoUartDriverEntryPoint (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_SYSTEM_TABLE             *SystemTable
  )
{
  return EfiLibInstallAllDriverProtocols (
           ImageHandle,
           SystemTable,
           &mSerialIoUartDriverBinding,
           ImageHandle,
           &mSerialIoUartDriverComponentName,
           NULL,
           NULL
           );
}


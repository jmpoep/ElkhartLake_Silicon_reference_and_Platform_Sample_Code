/** @file
  Thie file implements Gop Override Driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

#include "GopOverrideDriver.h"
#include <SetupVariable.h>
#include <Protocol/GopPolicy.h>

EFI_DRIVER_BINDING_PROTOCOL gGraphicsOverrideDriverBinding = {
  GopOverrideControllerDriverSupported,
  GopOverrideControllerDriverStart,
  GopOverrideControllerDriverStop,
  0xa,
  NULL,
  NULL
};

EFI_GRAPHICS_OUTPUT_PROTOCOL     *mGraphicsOutput;
EFI_GRAPHICS_OUTPUT_PROTOCOL     *mGraphicsOutputOrg;

EFI_GRAPHICS_OUTPUT_PROTOCOL     GraphicsOutputOverride = {
  GopQueryMode,
  GopSetMode,
  GopBlt,
  NULL
};

/**
  Return the current video mode information.

  @param  This       Protocol instance pointer.
  @param  ModeNumber The mode number to return information on.
  @param  SizeOfInfo A pointer to the size, in bytes, of the Info buffer.
  @param  Info       A pointer to callee allocated buffer that returns information about ModeNumber.

  @retval EFI_SUCCESS           Mode information returned.
  @retval EFI_BUFFER_TOO_SMALL  The Info buffer was too small.
  @retval EFI_DEVICE_ERROR      A hardware error occurred trying to retrieve the video mode.
  @retval EFI_NOT_STARTED       Video display is not initialized. Call SetMode ()
  @retval EFI_INVALID_PARAMETER One of the input args was NULL.

**/
EFI_STATUS
GopQueryMode (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL          *This,
  IN  UINT32                                ModeNumber,
  OUT UINTN                                 *SizeOfInfo,
  OUT EFI_GRAPHICS_OUTPUT_MODE_INFORMATION  **Info
  )
{
   return mGraphicsOutputOrg->QueryMode(mGraphicsOutputOrg, ModeNumber, SizeOfInfo, Info);
}

/**
  Set new video mode information.

  @param  This              Protocol instance pointer.
  @param  ModeNumber        The mode number to be set.

  @retval EFI_SUCCESS       Graphics mode was changed.
  @retval EFI_DEVICE_ERROR  The device had an error and could not complete the request.
  @retval EFI_UNSUPPORTED   ModeNumber is not supported by this device.

**/
EFI_STATUS
GopSetMode (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL *This,
  IN  UINT32                       ModeNumber
  )
{
    return mGraphicsOutputOrg->SetMode(mGraphicsOutputOrg, ModeNumber);
}

/**
  The following table defines actions for BltOperations:

  <B>EfiBltVideoFill</B> - Write data from the  BltBuffer pixel (SourceX, SourceY)
  directly to every pixel of the video display rectangle
  (DestinationX, DestinationY) (DestinationX + Width, DestinationY + Height).
  Only one pixel will be used from the BltBuffer. Delta is NOT used.

  <B>EfiBltVideoToBltBuffer</B> - Read data from the video display rectangle
  (SourceX, SourceY) (SourceX + Width, SourceY + Height) and place it in
  the BltBuffer rectangle (DestinationX, DestinationY )
  (DestinationX + Width, DestinationY + Height). If DestinationX or
  DestinationY is not zero then Delta must be set to the length in bytes
  of a row in the BltBuffer.

  <B>EfiBltBufferToVideo</B> - Write data from the  BltBuffer rectangle
  (SourceX, SourceY) (SourceX + Width, SourceY + Height) directly to the
  video display rectangle (DestinationX, DestinationY)
  (DestinationX + Width, DestinationY + Height). If SourceX or SourceY is
  not zero then Delta must be set to the length in bytes of a row in the
  BltBuffer.

  <B>EfiBltVideoToVideo</B> - Copy from the video display rectangle (SourceX, SourceY)
  (SourceX + Width, SourceY + Height) .to the video display rectangle
  (DestinationX, DestinationY) (DestinationX + Width, DestinationY + Height).
  The BltBuffer and Delta  are not used in this mode.

  @param  This         Protocol instance pointer.
  @param  BltBuffer    Buffer containing data to blit into video buffer. This
                       buffer has a size of Width*Height*sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
  @param  BltOperation Operation to perform on BlitBuffer and video memory
  @param  SourceX      X coordinate of source for the BltBuffer.
  @param  SourceY      Y coordinate of source for the BltBuffer.
  @param  DestinationX X coordinate of destination for the BltBuffer.
  @param  DestinationY Y coordinate of destination for the BltBuffer.
  @param  Width        Width of rectangle in BltBuffer in pixels.
  @param  Height       Hight of rectangle in BltBuffer in pixels.
  @param  Delta        OPTIONAL

  @retval EFI_SUCCESS           The Blt operation completed.
  @retval EFI_INVALID_PARAMETER BltOperation is not valid.
  @retval EFI_DEVICE_ERROR      A hardware error occured writting to the video buffer.

**/
EFI_STATUS
GopBlt (
  IN  EFI_GRAPHICS_OUTPUT_PROTOCOL            *This,
  IN  EFI_GRAPHICS_OUTPUT_BLT_PIXEL           *BltBuffer,   OPTIONAL
  IN  EFI_GRAPHICS_OUTPUT_BLT_OPERATION       BltOperation,
  IN  UINTN                                   SourceX,
  IN  UINTN                                   SourceY,
  IN  UINTN                                   DestinationX,
  IN  UINTN                                   DestinationY,
  IN  UINTN                                   Width,
  IN  UINTN                                   Height,
  IN  UINTN                                   Delta         OPTIONAL
  )
{
   return mGraphicsOutputOrg->Blt(mGraphicsOutputOrg, BltBuffer, BltOperation, SourceX, SourceY, DestinationX, DestinationY, Width, Height, Delta);
}

/**
  Test to see if Graphics Console could be supported on the Controller.
  Graphics Console could be supported if Graphics Output Protocol

  @param  This                Protocol instance pointer.
  @param  Controller          Handle of device to test.
  @param  RemainingDevicePath Optional parameter use to pick a specific child
                              device to start.

  @retval EFI_SUCCESS         This driver supports this device.
  @retval other               This driver does not support this device.

**/
EFI_STATUS
EFIAPI
GopOverrideControllerDriverSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                   Status;
  EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput;
  EFI_DEVICE_PATH_PROTOCOL     *DevicePath;

  GraphicsOutput = NULL;
  //
  // Open the IO Abstraction(s) needed to perform the supported test
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gGopOverrideProtocolGuid,
                  (VOID **) &GraphicsOutput,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  } else {
    //
    // Close the I/O Abstraction(s) used to perform the supported test
    //
      Status = gBS->CloseProtocol (
                      Controller,
                      &gGopOverrideProtocolGuid,
                      This->DriverBindingHandle,
                      Controller
                      );
      ASSERT_EFI_ERROR(Status);
  }

  //
  // We need to ensure that we do not layer on top of a virtual handle.
  // We need to ensure that the handles produced by the conspliter do not
  // get used.
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (!EFI_ERROR (Status)) {
    DEBUG((EFI_D_INFO, "GopOverrideControllerDriverSupported %x True \n", Controller));
    gBS->CloseProtocol (
          Controller,
          &gEfiDevicePathProtocolGuid,
          This->DriverBindingHandle,
          Controller
          );
  }

  return Status;
}

/**
  Start this driver on Controller by opening Graphics Output protocol
    and installing GraphicsOutputProtocol on Controller.

  @param  This                 Protocol instance pointer.
  @param  Controller           Handle of device to bind driver to
  @param  RemainingDevicePath  Optional parameter use to pick a specific child
                               device to start.

  @retval EFI_SUCCESS          This driver is added to Controller.
  @retval other                This driver does not support this device.

**/
EFI_STATUS
EFIAPI
GopOverrideControllerDriverStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                   Status;

  DEBUG ((EFI_D_INFO, "GopOverrideControllerDriverStart \n"));

  Status = gBS->OpenProtocol (
                  Controller,
                  &gGopOverrideProtocolGuid,
                  (VOID **) &mGraphicsOutputOrg,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  mGraphicsOutput = &GraphicsOutputOverride; // Wrapper
  mGraphicsOutput->Mode = mGraphicsOutputOrg->Mode; // Wrapper

  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Controller,
                  &gEfiGraphicsOutputProtocolGuid,
                  mGraphicsOutput,
                  NULL
                  );
  return Status;
}

/**
  Stop this driver on Controller by removing GraphicsOutputProtocol
  and closing the Graphics Output Protocol

  @param  This              Protocol instance pointer.
  @param  Controller        Handle of device to stop driver on
  @param  NumberOfChildren  Number of Handles in ChildHandleBuffer. If number of
                            children is zero stop the entire bus driver.
  @param  ChildHandleBuffer List of Child Handles to Stop.

  @retval EFI_SUCCESS       This driver is removed Controller.
  @retval EFI_NOT_STARTED   Simple Text Out protocol could not be found the
                            Controller.
  @retval other             This driver was not removed from this device.

**/
EFI_STATUS
EFIAPI
GopOverrideControllerDriverStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  )
{
  EFI_STATUS                   Status;

  DEBUG ((EFI_D_INFO, "GopOverrideControllerDriverStop \n"));

  if( mGraphicsOutput != NULL) {
    Status = gBS->UninstallProtocolInterface (
                  Controller,
                  &gEfiGraphicsOutputProtocolGuid,
                  &mGraphicsOutput
                  );
    DEBUG ((EFI_D_INFO, "UninstallProtocolInterface gEfiGraphicsOutputProtocolGuid : %x \n",Status));
    mGraphicsOutput = NULL;
  }

  Status = gBS->CloseProtocol (
                Controller,
                &gGopOverrideProtocolGuid,
                This->DriverBindingHandle,
                Controller
                );
  return Status;
}

/**
  This function update the GopOverrideGuid after locating the GopPolicy.

  @retval EFI_SUCCESS       GOP Override Protocol Guid is set.
  @retval EFI_NOT_READY     GOP Policy is not located.

**/
EFI_STATUS
UpdateGopOverrideGuid(VOID)
{
  EFI_STATUS              Status;
  GOP_POLICY_PROTOCOL     *GopPolicy;

  ///
  /// Locate the GOP Policy Protocol.
  ///
  GopPolicy = NULL;
  Status = gBS->LocateProtocol(&gGopPolicyProtocolGuid, NULL, (VOID **)&GopPolicy);
  if (EFI_ERROR(Status) || GopPolicy == NULL) {
    return EFI_NOT_READY;
  }

  ///
  /// Set GOP Override Protocol Guid
  ///
  CopyGuid(&(GopPolicy->GopOverrideGuid), &gGopOverrideProtocolGuid);
  DEBUG((DEBUG_INFO, "DxeGopOverride Enabled\n"));
  return EFI_SUCCESS;
}

/**
  This function Callback Update the GopPolicy and GopOverrideGuid.

  @param[in] Event           A pointer to the Event that triggered the callback.
  @param[in] Context         A pointer to private data registered with the callback function.

**/
VOID
EFIAPI
GopPolicyCallback(
IN EFI_EVENT          Event,
IN VOID               *Context
)
{
  UpdateGopOverrideGuid();
}

/**
  The user Entry Point for module GraphicsConsole. The user code starts with this function.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.
  @param[in] SystemTable    A pointer to the EFI System Table.

  @retval  EFI_SUCCESS       The entry point is executed successfully.
  @return  other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
InitializeGopOverrideDriver (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS       Status;
  EFI_EVENT        Event;
  VOID             *Registration;

  DEBUG ((EFI_D_INFO, "InitializeGopOverrideDriver \n"));

  ///
  /// Update GopOverrideGuid immediately  gGopPolicyProtocolGuid is installed
  ///
  Status = UpdateGopOverrideGuid();

  if (EFI_ERROR(Status)) {

    Status = gBS->CreateEvent(
      EVT_NOTIFY_SIGNAL,
      TPL_CALLBACK,
      GopPolicyCallback,
      NULL,
      &Event
      );

    if (!EFI_ERROR(Status)) {
      Status = gBS->RegisterProtocolNotify(
        &gGopPolicyProtocolGuid,
        Event,
        &Registration
        );
    }
  }
  //
  // Install driver model protocol(s).
  //
  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gGraphicsOverrideDriverBinding,
             ImageHandle,
             NULL,
             NULL
             );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

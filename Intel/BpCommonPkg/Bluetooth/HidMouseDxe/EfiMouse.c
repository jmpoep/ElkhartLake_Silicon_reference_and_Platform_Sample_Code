//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Help functions of HidMouse driver.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "HidMouseDxe.h"

#define USAGE_PAGE_BUTTON 0x09
#define USAGE_PAGE_GENERIC_DESKTOP_CONTROLS 0x01
#define USAGE_WHEEL 0x38

/**
  Initialize the BT mouse device.

  This function retrieves and parses HID report descriptor, and
  initializes state of BT_MOUSE_DEV. Then it sets indefinite idle
  rate for the device.

  @param  BtMouseDev           Device instance to be initialized.

  @retval EFI_SUCCESS           BT mouse device successfully initialized..
  @retval EFI_UNSUPPORTED       HID descriptor type is not report descriptor.
  @retval Other                 BT mouse device was not initialized successfully.

**/
EFI_STATUS
InitializeBtMouseDevice (
  IN OUT BT_MOUSE_DEV           *BtMouseDev
  )
{
  EDKII_HID_PROTOCOL      *HidProtocol;
  EFI_STATUS              Status;
  UINT8                   *ReportDesc;
  UINT8                   ReportId;
  UINT8                   Duration;

  HidProtocol = BtMouseDev->HidProtocol;

  //
  // @bug
  //
  ReportDesc = AllocateZeroPool (1);
  BtMouseDev->NumberOfButtons = 2;
  BtMouseDev->XLogicMax = 127;
  BtMouseDev->YLogicMax = 127;
  BtMouseDev->XLogicMin = -127;
  BtMouseDev->YLogicMin = -127;

  //
  // Check the presence of left and right buttons,
  // and initialize fields of EFI_SIMPLE_POINTER_MODE.
  //
  if (BtMouseDev->NumberOfButtons >= 1) {
    BtMouseDev->Mode.LeftButton = TRUE;
  }
  if (BtMouseDev->NumberOfButtons > 1) {
    BtMouseDev->Mode.RightButton = TRUE;
  }
  BtMouseDev->Mode.ResolutionX = 8;
  BtMouseDev->Mode.ResolutionY = 8;
  BtMouseDev->Mode.ResolutionZ = 0;

  //
  // ReportId is zero, which means the idle rate applies to all input reports.
  //
  ReportId = 0;
  //
  // Duration is zero, which means the duration is infinite.
  // so the endpoint will inhibit reporting forever,
  // and only reporting when a change is detected in the report data.
  //
  Duration = 0;
  HidSetIdleRequest (
    HidProtocol,
    ReportId,
    Duration
    );

  Status = HidStartNotification (HidProtocol);

  FreePool (ReportDesc);
  return Status;
}

/**
  Correct the endianness for the information.

  @param  Information           The data which need to change the endianness.
  @param  ReportSize            Report descriptor size

  @retval Information           Return the information after correcting the endianness.

**/
STATIC
INT32
CorrectEndianNess (
  IN INT32  Information,
  IN UINT32 ReportSize
  )
{
  UINT32 Mask;
  UINT32 Index;

  Mask = 1 << (ReportSize - 1);

  if ((Information & Mask) != 0) {
    for (Index = ReportSize; Index < 32; Index ++) {
      Mask = Mask << 1;
      Information = Information | Mask;
    }
  }

  return Information;
}

/**

  Fetch the info in the Data buffer.

  @param  Data          A pointer to a buffer that is filled with key data which is
                        retrieved via asynchronous interrupt transfer.
  @param  BytePosition  The position in byte level.
  @param  BitPosition   The position in bit level.
  @param  Size          Report descriptor size.

  @retval Information   Return the info got in Data buffer.

**/
STATIC
INT32
FetchInfo(
  IN UINT8 *Data,
  IN UINT32 *BytePosition,
  IN UINT32 *BitPosition,
  IN UINT32 Size
  )
{

  INT32  Information;
  UINT8  Index;
  UINT32  Mask;

  Information = 0;
  Mask = 1;

  for (Index = 1; Index <= Size; Index++) {

    if ((Data[*BytePosition] & (1 << *BitPosition)) != 0)
      Information = Information | Mask ;

    Mask = Mask << 1;

    if (*BitPosition == 7) {
      *BytePosition = *BytePosition + 1;
      *BitPosition  = 0;
    } else {
      *BitPosition = *BitPosition + 1;
    }

  }

  return Information;

}

/**
  Handler function for BT mouse's asynchronous interrupt transfer.

  This function is the handler function for BT mouse's asynchronous interrupt transfer
  to manage the mouse. It parses data returned from asynchronous interrupt transfer, and
  get button and movement state.

  @param  Data             A pointer to a buffer that is filled with key data which is
                           retrieved via asynchronous interrupt transfer.
  @param  DataLength       Indicates the size of the data buffer.
  @param  Context          Pointing to BT_MOUSE_DEV instance.

  @retval EFI_SUCCESS      Asynchronous interrupt transfer is handled successfully.
  @retval EFI_DEVICE_ERROR Hardware error occurs.

**/
EFI_STATUS
EFIAPI
OnMouseInterruptComplete (
  IN  VOID        *Data,
  IN  UINTN       DataLength,
  IN  VOID        *Context
  )
{
  BT_MOUSE_DEV       *BtMouseDevice;
  UINT8              ReportId;
  HID_REPORT_FMT     *ReportItem;
  UINT8              *DataPtr;
  LIST_ENTRY         *Link;
  LIST_ENTRY         *Cur;
  UINT32             Index;
  INT32              Information;
  UINT32             BytePosition;
  UINT32             BitPosition;

  DataPtr = (UINT8*)Data;
  BytePosition = 0;
  BitPosition  = 0;

  // Extract the ReportId
  ReportId = DataPtr[0];
  DataPtr++;
  DataLength --;

  BtMouseDevice  = (BT_MOUSE_DEV *) Context;
  BtMouseDevice->HidProtocol->GetReportFormatList(BtMouseDevice->HidProtocol, &Link);

  Cur  = GetFirstNode (Link);

  BtMouseDevice->StateChanged = TRUE;

  while (!IsNull (Link, Cur)) {

    ReportItem = ITEM_FROM_LINK(Cur);

    // Check if the item is of the input type
    if ( ReportItem->ReportId != ReportId || ReportItem->Type != BT_HID_ITEM_TYPE_INPUT ) {
      Cur = GetNextNode (Link, Cur);
      continue;
    }

    if (ReportItem->Usage != USAGE_WHEEL){
      switch (ReportItem->ArrVar) {
        case BT_HID_ITEM_TYPE_VARIABLE:
          for (Index = 0; Index < ReportItem->ReportCount; Index++) {

            Information = 0;
            Information = FetchInfo(DataPtr, &BytePosition, &BitPosition, ReportItem->ReportSize);

            if ( ReportItem->DatConst == 0 ){
              switch (ReportItem->UsagePage) {
                case USAGE_PAGE_BUTTON:
                  switch(Index){
                    case 0:
                      BtMouseDevice->State.LeftButton = (Information != 0) ? TRUE : FALSE;
                      break;
                    case 1:
                      BtMouseDevice->State.RightButton = (Information != 0) ? TRUE : FALSE;
                      break;
                  }
                  break;

                case USAGE_PAGE_GENERIC_DESKTOP_CONTROLS:
                  switch(Index){
                    case 0:
                      if (ReportItem->AbsRel)
                        BtMouseDevice->State.RelativeMovementX += CorrectEndianNess(Information, ReportItem->ReportSize);
                      break;
                    case 1:
                      if (ReportItem->AbsRel)
                        BtMouseDevice->State.RelativeMovementY += CorrectEndianNess(Information, ReportItem->ReportSize);
                      break;
                  }
                  break;
              }
            }
          }
          break;

        case BT_HID_ITEM_TYPE_ARRAY:
          // Handle Padding
          for (Index = 0; Index < ReportItem->ReportCount; Index++) {
            Information = 0;
            Information = FetchInfo(DataPtr, &BytePosition, &BitPosition, ReportItem->ReportSize);
          }
          // Do nothing :)
          break;
      }
    }
    Cur = GetNextNode (Link, Cur);
  }

  return EFI_SUCCESS;
}

/**
  Retrieves the current state of a pointer device.

  @param  This                  A pointer to the EFI_SIMPLE_POINTER_PROTOCOL instance.
  @param  MouseState            A pointer to the state information on the pointer device.

  @retval EFI_SUCCESS           The state of the pointer device was returned in State.
  @retval EFI_NOT_READY         The state of the pointer device has not changed since the last call to
                                GetState().
  @retval EFI_DEVICE_ERROR      A device error occurred while attempting to retrieve the pointer device's
                                current state.
  @retval EFI_INVALID_PARAMETER MouseState is NULL.

**/
EFI_STATUS
EFIAPI
BtGetMouseState (
  IN   EFI_SIMPLE_POINTER_PROTOCOL  *This,
  OUT  EFI_SIMPLE_POINTER_STATE     *MouseState
  )
{
  BT_MOUSE_DEV *MouseDev;

  if (MouseState == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MouseDev = BT_MOUSE_DEV_FROM_MOUSE_PROTOCOL (This);

  if (!MouseDev->StateChanged) {
    return EFI_NOT_READY;
  }

  //
  // Retrieve mouse state from BT_MOUSE_DEV, which was filled by OnMouseInterruptComplete()
  //
  CopyMem (
    MouseState,
    &MouseDev->State,
    sizeof (EFI_SIMPLE_POINTER_STATE)
    );

  //
  // Clear previous move state
  //
  MouseDev->State.RelativeMovementX = 0;
  MouseDev->State.RelativeMovementY = 0;
  MouseDev->State.RelativeMovementZ = 0;

  MouseDev->StateChanged            = FALSE;

  return EFI_SUCCESS;
}


/**
  Resets the pointer device hardware.

  @param  This                  A pointer to the EFI_SIMPLE_POINTER_PROTOCOL instance.
  @param  ExtendedVerification  Indicates that the driver may perform a more exhaustive
                                verification operation of the device during reset.

  @retval EFI_SUCCESS           The device was reset.
  @retval EFI_DEVICE_ERROR      The device is not functioning correctly and could not be reset.

**/
EFI_STATUS
EFIAPI
BtMouseReset (
  IN EFI_SIMPLE_POINTER_PROTOCOL    *This,
  IN BOOLEAN                        ExtendedVerification
  )
{
  BT_MOUSE_DEV       *BtMouseDevice;

  BtMouseDevice  = BT_MOUSE_DEV_FROM_MOUSE_PROTOCOL (This);

  //
  // Clear mouse state.
  //
  ZeroMem (
    &BtMouseDevice->State,
    sizeof (EFI_SIMPLE_POINTER_STATE)
    );
  BtMouseDevice->StateChanged = FALSE;

  return EFI_SUCCESS;
}

/**
  Event notification function for EFI_SIMPLE_POINTER_PROTOCOL.WaitForInput event.

  @param  Event        Event to be signaled when there's input from mouse.
  @param  Context      Points to BT_MOUSE_DEV instance.

**/
VOID
EFIAPI
BtMouseWaitForInput (
  IN  EFI_EVENT               Event,
  IN  VOID                    *Context
  )
{
  BT_MOUSE_DEV *BtMouseDev;

  BtMouseDev = (BT_MOUSE_DEV *) Context;

  //
  // If there's input from mouse, signal the event.
  //
  if (BtMouseDev->StateChanged) {
    gBS->SignalEvent (Event);
  }
}


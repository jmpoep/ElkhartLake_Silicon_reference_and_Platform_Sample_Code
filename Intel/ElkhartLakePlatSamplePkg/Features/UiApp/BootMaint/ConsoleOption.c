/** @file
  handles console redirection from boot manager

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2018 Intel Corporation.

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

#include "BootMaint.h"

GLOBAL_REMOVE_IF_UNREFERENCED UART_FLOW_CONTROL_DEVICE_PATH mFlowControlDevicePath =
{
  {
    MESSAGING_DEVICE_PATH,
    MSG_VENDOR_DP,
    {
      (UINT8)(sizeof(UART_FLOW_CONTROL_DEVICE_PATH)),
      (UINT8)((sizeof(UART_FLOW_CONTROL_DEVICE_PATH)) >> 8)
    }
  },
  DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL,
  UART_FLOW_CONTROL_HARDWARE
};

/**
  Check the device path node whether it's the Flow Control node or not.

  @param[in] FlowControl    The device path node to be checked.

  @retval TRUE              It's the Flow Control node.
  @retval FALSE             It's not.

**/
BOOLEAN
IsUartFlowControlNode (
  IN UART_FLOW_CONTROL_DEVICE_PATH *FlowControl
  )
{
  return (BOOLEAN) (
           (DevicePathType (FlowControl) == MESSAGING_DEVICE_PATH) &&
           (DevicePathSubType (FlowControl) == MSG_VENDOR_DP) &&
           (CompareGuid (&FlowControl->Guid, &gEfiUartDevicePathGuid))
           );
}

/**
  Function compares a device path data structure to that of all the nodes of a
  second device path instance.

  @param  Multi                 A pointer to a multi-instance device path data
                                structure.
  @param  Single                A pointer to a single-instance device path data
                                structure.

  @retval TRUE                  If the Single device path is contained within Multi device path.
  @retval FALSE                 The Single device path is not match within Multi device path.

**/
BOOLEAN
MatchDevicePaths (
  IN  EFI_DEVICE_PATH_PROTOCOL  *Multi,
  IN  EFI_DEVICE_PATH_PROTOCOL  *Single
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePathInst;
  UINTN                     Size;

  if (Multi == NULL || Single  == NULL) {
    return FALSE;
  }

  DevicePath     = Multi;
  DevicePathInst = GetNextDevicePathInstance (&DevicePath, &Size);

  //
  // Search for the match of 'Single' in 'Multi'
  //
  while (DevicePathInst != NULL) {
    //
    // If the single device path is found in multiple device paths,
    // return success
    //
    if (CompareMem (Single, DevicePathInst, Size) == 0) {
      FreePool (DevicePathInst);
      return TRUE;
    }

    FreePool (DevicePathInst);
    DevicePathInst = GetNextDevicePathInstance (&DevicePath, &Size);
  }

  return FALSE;
}

/**
  Check whether the device path node is ISA Serial Node.

  @param Acpi           Device path node to be checked

  @retval TRUE          It's ISA Serial Node.
  @retval FALSE         It's NOT ISA Serial Node.

**/
BOOLEAN
IsIsaSerialNode (
  IN ACPI_HID_DEVICE_PATH *Acpi
  )
{
  return (BOOLEAN) (
      (DevicePathType (Acpi) == ACPI_DEVICE_PATH) &&
      (DevicePathSubType (Acpi) == ACPI_DP) &&
      (ReadUnaligned32 (&Acpi->HID) == EISA_PNP_ID (0x0501))
      );
}

/**
  Update Com Ports attributes from DevicePath

  @param DevicePath      DevicePath that contains Com ports
  @param ComAttributes   Com attributes buffer.

  @retval EFI_SUCCESS   The update is successful.

**/
EFI_STATUS
UpdateComAttributeFromVariable (
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath,
  TOTAL_SERIAL_PORT_INFO    *ComAttributes
  );

/**
  Update the multi-instance device path of Terminal Device based on
  the global TerminalMenu. If ChangeTernimal is TRUE, the terminal
  device path in the Terminal Device in TerminalMenu is also updated.

  @param DevicePath      The multi-instance device path.
  @param ChangeTerminal  TRUE, then device path in the Terminal Device
                         in TerminalMenu is also updated; FALSE, no update.

  @return EFI_SUCCESS    The function completes successfully.

**/
EFI_STATUS
ChangeTerminalDevicePath (
  IN OUT    EFI_DEVICE_PATH_PROTOCOL  **DevicePath,
  IN        BOOLEAN                   ChangeTerminal
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *Node;
  EFI_DEVICE_PATH_PROTOCOL  *Node1;
  ACPI_HID_DEVICE_PATH      *Acpi;
  UART_DEVICE_PATH          *Uart;
  UART_DEVICE_PATH          *Uart1;
  UINTN                     Com;
  BM_TERMINAL_CONTEXT       *NewTerminalContext;
  BM_MENU_ENTRY             *NewMenuEntry;
  UART_FLOW_CONTROL_DEVICE_PATH *FlowControlNode;

  Node  = *DevicePath;
  Node  = NextDevicePathNode (Node);
  Com   = 0;
  while (!IsDevicePathEnd (Node)) {
    Acpi = (ACPI_HID_DEVICE_PATH *) Node;
    if (IsIsaSerialNode (Acpi)) {
      CopyMem (&Com, &Acpi->UID, sizeof (UINT32));
    }

    NewMenuEntry = BOpt_GetMenuEntry (&TerminalMenu, Com);

    NewTerminalContext = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;
    if ((DevicePathType (Node) == MESSAGING_DEVICE_PATH) && (DevicePathSubType (Node) == MSG_UART_DP)) {
      Uart = (UART_DEVICE_PATH *) Node;
      CopyMem (
        &Uart->BaudRate,
        &NewTerminalContext->BaudRate,
        sizeof (UINT64)
        );

      CopyMem (
        &Uart->DataBits,
        &NewTerminalContext->DataBits,
        sizeof (UINT8)
        );

      CopyMem (
        &Uart->Parity,
        &NewTerminalContext->Parity,
        sizeof (UINT8)
        );

      CopyMem (
        &Uart->StopBits,
        &NewTerminalContext->StopBits,
        sizeof (UINT8)
        );

      FlowControlNode = (UART_FLOW_CONTROL_DEVICE_PATH *) NextDevicePathNode (Node);
      if (IsUartFlowControlNode (FlowControlNode)) {
        FlowControlNode->FlowControlMap = NewTerminalContext->FlowControl;
      } else {
        //
        // Append the Flow control device node when user enable flow control.
        //
        if (NewTerminalContext->FlowControl != 0) {
          mFlowControlDevicePath.FlowControlMap = NewTerminalContext->FlowControl;
          *DevicePath = AppendDevicePathNode (
                                       *DevicePath,
                                       (EFI_DEVICE_PATH_PROTOCOL *) (&mFlowControlDevicePath)
                                       );
        }
      }

      //
      // Change the device path in the ComPort
      //
      if (ChangeTerminal) {
        Node1 = NewTerminalContext->DevicePath;
        Node1 = NextDevicePathNode (Node1);
        while (!IsDevicePathEnd (Node1)) {
          if ((DevicePathType (Node1) == MESSAGING_DEVICE_PATH) && (DevicePathSubType (Node1) == MSG_UART_DP)) {
            Uart1 = (UART_DEVICE_PATH *) Node1;
            CopyMem (
              &Uart1->BaudRate,
              &NewTerminalContext->BaudRate,
              sizeof (UINT64)
              );

            CopyMem (
              &Uart1->DataBits,
              &NewTerminalContext->DataBits,
              sizeof (UINT8)
              );

            CopyMem (
              &Uart1->Parity,
              &NewTerminalContext->Parity,
              sizeof (UINT8)
              );

            CopyMem (
              &Uart1->StopBits,
              &NewTerminalContext->StopBits,
              sizeof (UINT8)
              );
            break;
          }
          //
          // end if
          //
          Node1 = NextDevicePathNode (Node1);
        }
        //
        // end while
        //
        break;
      }
    }

    Node = NextDevicePathNode (Node);
  }

  return EFI_SUCCESS;

}

/**
  Update the device path that describing a terminal device
  based on the new BaudRate, Data Bits, parity and Stop Bits
  set.

  @param DevicePath terminal device's path

**/
VOID
ChangeVariableDevicePath (
  IN OUT EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *Node;
  ACPI_HID_DEVICE_PATH      *Acpi;
  UART_DEVICE_PATH          *Uart;
  UINTN                     Com;
  BM_TERMINAL_CONTEXT       *NewTerminalContext;
  BM_MENU_ENTRY             *NewMenuEntry;

  Node  = DevicePath;
  Node  = NextDevicePathNode (Node);
  Com   = 0;
  while (!IsDevicePathEnd (Node)) {
    Acpi = (ACPI_HID_DEVICE_PATH *) Node;
    if (IsIsaSerialNode (Acpi)) {
      CopyMem (&Com, &Acpi->UID, sizeof (UINT32));
    }

    if ((DevicePathType (Node) == MESSAGING_DEVICE_PATH) && (DevicePathSubType (Node) == MSG_UART_DP)) {
      NewMenuEntry = BOpt_GetMenuEntry (
                      &TerminalMenu,
                      Com
                      );
      ASSERT (NewMenuEntry != NULL);
      if (NewMenuEntry == NULL) {
        return;
      }
      NewTerminalContext  = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;
      Uart                = (UART_DEVICE_PATH *) Node;
      CopyMem (
        &Uart->BaudRate,
        &NewTerminalContext->BaudRate,
        sizeof (UINT64)
        );

      CopyMem (
        &Uart->DataBits,
        &NewTerminalContext->DataBits,
        sizeof (UINT8)
        );

      CopyMem (
        &Uart->Parity,
        &NewTerminalContext->Parity,
        sizeof (UINT8)
        );

      CopyMem (
        &Uart->StopBits,
        &NewTerminalContext->StopBits,
        sizeof (UINT8)
        );
    }

    Node = NextDevicePathNode (Node);
  }
}

/**
  Retrieve ACPI UID of UART from device path

  @param Handle          The handle for the UART device.
  @param AcpiUid         The ACPI UID on output.

  @retval  TRUE   Find valid UID from device path
  @retval  FALSE  Can't find

**/
BOOLEAN
RetrieveUartUid (
  IN EFI_HANDLE   Handle,
  IN OUT UINT32   *AcpiUid
  )
{
  EFI_STATUS                Status;
  ACPI_HID_DEVICE_PATH      *Acpi;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;

  Status = gBS->HandleProtocol (
                  Handle,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath
                  );
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  Acpi = NULL;
  for (; !IsDevicePathEnd (DevicePath); DevicePath = NextDevicePathNode (DevicePath)) {
    if ((DevicePathType (DevicePath) == MESSAGING_DEVICE_PATH) && (DevicePathSubType (DevicePath) == MSG_UART_DP)) {
      break;
    }
    //
    // Acpi points to the node before the Uart node
    //
    Acpi = (ACPI_HID_DEVICE_PATH *) DevicePath;
  }

  if ((Acpi != NULL) && IsIsaSerialNode (Acpi)) {
    if (AcpiUid != NULL) {
      CopyMem (AcpiUid, &Acpi->UID, sizeof (UINT32));
    }
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Sort Uart handles array with Acpi->UID from low to high.

  @param Handles         EFI_SERIAL_IO_PROTOCOL handle buffer
  @param NoHandles       EFI_SERIAL_IO_PROTOCOL handle count
**/
VOID
SortedUartHandle (
  IN  EFI_HANDLE *Handles,
  IN  UINTN      NoHandles
  )
{
  UINTN       Index1;
  UINTN       Index2;
  UINTN       Position;
  UINT32      AcpiUid1;
  UINT32      AcpiUid2;
  UINT32      TempAcpiUid;
  EFI_HANDLE  TempHandle;

  for (Index1 = 0; Index1 < NoHandles-1; Index1++) {
    if (!RetrieveUartUid (Handles[Index1], &AcpiUid1)) {
      continue;
    }
    TempHandle  = Handles[Index1];
    Position    = Index1;
    TempAcpiUid = AcpiUid1;

    for (Index2 = Index1+1; Index2 < NoHandles; Index2++) {
      if (!RetrieveUartUid (Handles[Index2], &AcpiUid2)) {
        continue;
      }
      if (AcpiUid2 < TempAcpiUid) {
        TempAcpiUid = AcpiUid2;
        TempHandle  = Handles[Index2];
        Position    = Index2;
      }
    }
    Handles[Position] = Handles[Index1];
    Handles[Index1]   = TempHandle;
  }
}

/**
  Test whether DevicePath is a valid Terminal


  @param DevicePath      DevicePath to be checked
  @param Termi           If DevicePath is valid Terminal, terminal type is returned.
  @param Com             If DevicePath is valid Terminal, Com Port type is returned.

  @retval  TRUE         If DevicePath point to a Terminal.
  @retval  FALSE        If DevicePath does not point to a Terminal.

**/
BOOLEAN
IsTerminalDevicePath (
  IN  EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  OUT TYPE_OF_TERMINAL         *Termi,
  OUT UINTN                    *Com
  );

/**
  Get Com port attributes according to the com port index or device path.


  @param ComAttributes      The com port array which save com port info.
  @param Com                The com port index or NULL.
  @param DevicePath         DevicePath info belong to the com port device or NULL

  @retval  The com port info.

**/
SERIAL_PORT_ATTRIBUTE *
GetComAttributes (
  IN      UINT8                     *ComAttributes,
  IN      UINTN                     *Com,
  IN      EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
  SERIAL_PORT_ATTRIBUTE   *CurNode;
  TOTAL_SERIAL_PORT_INFO  *TotalInfo;
  UINT64                  TotalSize;
  UINT64                  TotalInfoSize;

  TotalSize = 0;

  if (ComAttributes == NULL) {
    return NULL;
  }

  TotalInfo = (TOTAL_SERIAL_PORT_INFO  *)ComAttributes;
  TotalInfoSize = TotalInfo->TotalSize - sizeof (UINT64);

  while (TotalSize < TotalInfoSize) {
    CurNode = (SERIAL_PORT_ATTRIBUTE *) (((UINT8*) TotalInfo->PortAttributes) + TotalSize);

    if (Com != NULL && CurNode->ComTag.ComNum == *Com) {
      return CurNode;
    }

    if (DevicePath != NULL && CurNode->Length != 0 &&
      CompareMem (CurNode->ComTag.DevicePath, DevicePath, CurNode->Length) == 0) {
      return CurNode;
    }

    TotalSize += sizeof (SERIAL_PORT_ATTRIBUTE) + CurNode->Length;
  }

  return NULL;
}

/**
  Get Serial Attributes from device path or saved attributes info.

  @param Handle             Device handle which has the Serial io protocol.
  @param NewTerminalContext Menu context has the info.
  @param ComAttributes      Com attributes info saved in golcal parameter.
  @param Com                If DevicePath is valid Terminal, Com Port number is returned.
  @param DevicePath         If Device

**/
VOID
UpdateTerminalContext (
  IN      EFI_HANDLE                Handle,
  IN OUT  BM_TERMINAL_CONTEXT       *NewTerminalContext,
  IN OUT  UINT8                     **ComAttributes,
  OUT     BOOLEAN                   *NewInitialize,
  IN      UINTN                     *Com,
  IN      EFI_DEVICE_PATH_PROTOCOL  *DevicePath
  )
{
  EFI_SERIAL_IO_PROTOCOL    *SerialIo;
  UINT32                    FlowControl;
  UINTN                     NewNodeSize;
  UINTN                     OldNodeSize;
  SERIAL_PORT_ATTRIBUTE     *ComInfo;
  UINT8                     *TmpInfo;
  TOTAL_SERIAL_PORT_INFO    *TotalInfo;

  TotalInfo = (TOTAL_SERIAL_PORT_INFO *) (*ComAttributes);

  ComInfo = GetComAttributes (*ComAttributes, Com, DevicePath);

  if (ComInfo != NULL) {
    NewTerminalContext->BaudRate         = ComInfo->BaudRate;
    NewTerminalContext->DataBits         = ComInfo->DataBits;
    NewTerminalContext->Parity           = ComInfo->Parity;
    NewTerminalContext->StopBits         = ComInfo->StopBits;
    NewTerminalContext->FlowControl      = ComInfo->FlowControl;
    NewTerminalContext->TerminalType     = ComInfo->TerminalType;
    NewTerminalContext->IsEnabled        = ComInfo->IsEnabled;
    NewTerminalContext->LegacyResolution = ComInfo->LegacyResolution;
  } else {
    *NewInitialize = TRUE;

    gBS->HandleProtocol (
          Handle,
          &gEfiSerialIoProtocolGuid,
          (VOID **) &SerialIo
          );

    CopyMem (
      &NewTerminalContext->BaudRate,
      &SerialIo->Mode->BaudRate,
      sizeof (UINT64)
      );

    CopyMem (
      &NewTerminalContext->DataBits,
      &SerialIo->Mode->DataBits,
      sizeof (UINT8)
      );

    CopyMem (
      &NewTerminalContext->Parity,
      &SerialIo->Mode->Parity,
      sizeof (UINT8)
      );

    CopyMem (
      &NewTerminalContext->StopBits,
      &SerialIo->Mode->StopBits,
      sizeof (UINT8)
      );

    NewTerminalContext->FlowControl = 0;
    FlowControl                     = 0;
    SerialIo->GetControl(SerialIo, &FlowControl);
    if ((FlowControl & EFI_SERIAL_HARDWARE_FLOW_CONTROL_ENABLE) != 0) {
      NewTerminalContext->FlowControl = UART_FLOW_CONTROL_HARDWARE;
    }
    NewTerminalContext->LegacyResolution = 0x01;
    NewTerminalContext->TerminalType     = 0x00;
    NewTerminalContext->IsEnabled        = 0x00;

    //
    // Initialize the ComAttribute parameter.
    //
    if (Com != NULL) {
      NewNodeSize = sizeof (SERIAL_PORT_ATTRIBUTE);
    } else {
      NewNodeSize = sizeof (SERIAL_PORT_ATTRIBUTE) + GetDevicePathSize (DevicePath);
    }

    if (TotalInfo == NULL) {
      NewNodeSize += sizeof (UINT64);
      OldNodeSize  = 0;
    } else {
      OldNodeSize = TotalInfo->TotalSize;
    }
    TmpInfo = (UINT8 *) AllocateZeroPool (NewNodeSize + OldNodeSize);
    ASSERT (TmpInfo != NULL);
    if (TmpInfo == NULL) {
      return;
    }

    CopyMem(TmpInfo, (UINT8*)*ComAttributes, OldNodeSize);
    if (*ComAttributes != NULL) {
      FreePool (*ComAttributes);
    }
    *ComAttributes = TmpInfo;
    TotalInfo = (TOTAL_SERIAL_PORT_INFO *) (*ComAttributes);
    TotalInfo->TotalSize += NewNodeSize;
    if (OldNodeSize == 0) {
      ComInfo = TotalInfo->PortAttributes;
    } else {
      ComInfo = (SERIAL_PORT_ATTRIBUTE*) ((UINT8*) TotalInfo + OldNodeSize);
    }

    ComInfo->BaudRate         = NewTerminalContext->BaudRate;
    ComInfo->DataBits         = NewTerminalContext->DataBits;
    ComInfo->Parity           = NewTerminalContext->Parity;
    ComInfo->StopBits         = NewTerminalContext->StopBits;
    ComInfo->FlowControl      = NewTerminalContext->FlowControl;
    ComInfo->LegacyResolution = NewTerminalContext->LegacyResolution;
    ComInfo->TerminalType     = NewTerminalContext->TerminalType;
    ComInfo->IsEnabled        = 0x00;
    if (Com != NULL) {
      ComInfo->ComTag.ComNum = (UINT8) (*Com);
    } else {
      ComInfo->Length = (UINT8)GetDevicePathSize(DevicePath);
      CopyMem(&ComInfo->ComTag.DevicePath, (CHAR8*) DevicePath, ComInfo->Length);
    }
  }
}

/**
  Build a list containing all serial devices.


  @retval EFI_SUCCESS The function complete successfully.
  @retval EFI_UNSUPPORTED No serial ports present.

**/
EFI_STATUS
LocateSerialIo (
  VOID
  )
{
  UINTN                     Index;
  UINTN                     Index2;
  UINTN                     NoHandles;
  EFI_HANDLE                *Handles;
  EFI_STATUS                Status;
  ACPI_HID_DEVICE_PATH      *Acpi;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *Node;
  EFI_DEVICE_PATH_PROTOCOL  *OutDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *InpDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *ErrDevicePath;
  BM_MENU_ENTRY             *NewMenuEntry;
  BM_TERMINAL_CONTEXT       *NewTerminalContext;
  EFI_DEVICE_PATH_PROTOCOL  *NewDevicePath;
  VENDOR_DEVICE_PATH        Vendor;
  UINTN                     DevicePathLen;
  TOTAL_SERIAL_PORT_INFO    *ComAttributes;
  BOOLEAN                   NewInitialize;
  BOOLEAN                   GetUartNode;
  SERIAL_PORT_ATTRIBUTE     *TmpComInfo;

  ComAttributes = NULL;
  NewInitialize = FALSE;
  GetUartNode   = FALSE;
  Status        = EFI_SUCCESS;
  Handles       = NULL;
  Acpi          = NULL;
  DevicePath    = NULL;
  Node          = NULL;
  OutDevicePath = NULL;
  InpDevicePath = NULL;
  ErrDevicePath = NULL;
  NewMenuEntry  = NULL;
  NewTerminalContext = NULL;
  NewDevicePath = NULL;
  TmpComInfo    = NULL;
  //
  // Get all handles that have SerialIo protocol installed
  //
  InitializeListHead (&TerminalMenu.Head);
  TerminalMenu.MenuNumber = 0;
  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gEfiSerialIoProtocolGuid,
                  NULL,
                  &NoHandles,
                  &Handles
                  );
  if (EFI_ERROR (Status) || Handles == NULL) {
    //
    // No serial ports present
    //
    Status = EFI_UNSUPPORTED;
    goto EXIT;
  }

  //
  // Sort Uart handles array with Acpi->UID from low to high
  // then Terminal menu can be built from low Acpi->UID to high Acpi->UID
  //
  SortedUartHandle (Handles, NoHandles);

  //
  // Get legacy resolution setting from the variable.
  //
  if (NoHandles > 0) {
    GetVariable2 (L"ComAttributes", &gSetupVariableGuid, (VOID **) &ComAttributes, NULL);
    if (ComAttributes == NULL) {
      Status = EFI_NOT_FOUND;
      goto EXIT;
    }
  }

  for (Index = 0; Index < NoHandles; Index++) {
    //
    // Check to see whether the handle has DevicePath Protocol installed
    //
    gBS->HandleProtocol (
          Handles[Index],
          &gEfiDevicePathProtocolGuid,
          (VOID **) &DevicePath
          );

    Acpi = NULL;
    for (Node = DevicePath; !IsDevicePathEnd (Node); Node = NextDevicePathNode (Node)) {
      if ((DevicePathType (Node) == MESSAGING_DEVICE_PATH) && (DevicePathSubType (Node) == MSG_UART_DP)) {
        GetUartNode = TRUE;
        break;
      }
      //
      // Acpi points to the node before Uart node
      //
      Acpi = (ACPI_HID_DEVICE_PATH *) Node;
    }

    if (GetUartNode == FALSE) {
      continue;
    }

    GetUartNode = FALSE;
    NewMenuEntry = BOpt_CreateMenuEntry (BM_TERMINAL_CONTEXT_SELECT);
    if (NewMenuEntry == NULL) {
      Status = EFI_OUT_OF_RESOURCES;
      goto EXIT;
    }

    NewTerminalContext = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;
    NewTerminalContext->DevicePath = DuplicateDevicePath (DevicePath);

    if ((Acpi != NULL) && IsIsaSerialNode (Acpi)) {
      CopyMem (&NewMenuEntry->OptionNumber, &Acpi->UID, sizeof (UINT32));

      //
      // Save Display String "COM* "
      //
      NewMenuEntry->DisplayString = AllocateZeroPool (10);
      if (NewMenuEntry->DisplayString == NULL) {
        Status = EFI_OUT_OF_RESOURCES;
        goto EXIT;
      }
      StrCatS (NewMenuEntry->DisplayString, 10 / sizeof (CHAR16), L"COM");
      UnicodeValueToStringS(NewMenuEntry->DisplayString + StrLen(NewMenuEntry->DisplayString), sizeof (NewMenuEntry->DisplayString + StrLen(NewMenuEntry->DisplayString)), 0, NewMenuEntry->OptionNumber, 0);

      UpdateTerminalContext(Handles[Index], NewTerminalContext, (UINT8**) &ComAttributes, &NewInitialize, &NewMenuEntry->OptionNumber, NULL);
    } else {
      NewMenuEntry->OptionNumber = NO_COM_INDEX_NUM;
      NewMenuEntry->DisplayString = EfiLibStrFromDatahub (DevicePath);
      if (NULL == NewMenuEntry->DisplayString) {
        NewMenuEntry->DisplayString = UiDevicePathToStr (DevicePath);
      }

      UpdateTerminalContext(Handles[Index], NewTerminalContext, (UINT8**)&ComAttributes, &NewInitialize, NULL, DevicePath);
    }

    InsertTailList (&TerminalMenu.Head, &NewMenuEntry->Link);
    TerminalMenu.MenuNumber++;
  }

  if (NewInitialize) {
    //
    // Get L"ConOut", L"ConIn" and L"ErrOut" from the Var
    //
    GetEfiGlobalVariable2 (L"ConOut", (VOID **) &OutDevicePath, NULL);
    GetEfiGlobalVariable2 (L"ConIn", (VOID **) &InpDevicePath, NULL);
    GetEfiGlobalVariable2 (L"ErrOut", (VOID **) &ErrDevicePath, NULL);
    if (OutDevicePath != NULL) {
      UpdateComAttributeFromVariable (OutDevicePath, ComAttributes);
    }

    if (InpDevicePath != NULL) {
      UpdateComAttributeFromVariable (InpDevicePath, ComAttributes);
    }

    if (ErrDevicePath != NULL) {
      UpdateComAttributeFromVariable (ErrDevicePath, ComAttributes);
    }

    for (Index = 0; Index < TerminalMenu.MenuNumber; Index++) {
      NewMenuEntry = BOpt_GetMenuEntry (&TerminalMenu, Index);
      if (NULL == NewMenuEntry) {
        Status = EFI_NOT_FOUND;
        goto EXIT;
      }

      NewTerminalContext                = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;
      TmpComInfo = GetComAttributes((UINT8*) ComAttributes, &NewMenuEntry->OptionNumber, NewTerminalContext->DevicePath);
      if (TmpComInfo == NULL) {
        Status = EFI_NOT_FOUND;
        goto EXIT;
      }

      NewTerminalContext->TerminalType  = TmpComInfo->TerminalType;

      Vendor.Header.Type                = MESSAGING_DEVICE_PATH;
      Vendor.Header.SubType             = MSG_VENDOR_DP;

      for (Index2 = 0; Index2 < 4; Index2++) {
        CopyMem (&Vendor.Guid, &TerminalTypeGuid[Index2], sizeof (EFI_GUID));
        SetDevicePathNodeLength (&Vendor.Header, sizeof (VENDOR_DEVICE_PATH));
        NewDevicePath = AppendDevicePathNode (
                          NewTerminalContext->DevicePath,
                          (EFI_DEVICE_PATH_PROTOCOL *) &Vendor
                          );
        if (NewMenuEntry->HelpString != NULL) {
          FreePool (NewMenuEntry->HelpString);
        }
        //
        // NewMenuEntry->HelpString = UiDevicePathToStr (NewDevicePath);
        // NewMenuEntry->DisplayString = NewMenuEntry->HelpString;
        //
        NewMenuEntry->HelpString = NULL;

        if (MatchDevicePaths (OutDevicePath, NewDevicePath)) {
          NewTerminalContext->IsEnabled     = 0x01;
          NewTerminalContext->TerminalType  = (UINT8) Index2;
        }

        if (MatchDevicePaths (InpDevicePath, NewDevicePath)) {
          NewTerminalContext->IsEnabled     = 0x01;
          NewTerminalContext->TerminalType  = (UINT8) Index2;
        }

        if (MatchDevicePaths (ErrDevicePath, NewDevicePath)) {
          NewTerminalContext->IsEnabled     = 0x01;
          NewTerminalContext->TerminalType  = (UINT8) Index2;
        }
        TmpComInfo->IsEnabled    = NewTerminalContext->IsEnabled;
        TmpComInfo->TerminalType = NewTerminalContext->TerminalType;
      }
    }

    Status = gRT->SetVariable (
                    L"ComAttributes",
                    &gSetupVariableGuid,
                    VAR_ATTR_NV_BS,
                    ComAttributes->TotalSize,
                    ComAttributes
                    );
    if (EFI_ERROR (Status)) {
      ASSERT (FALSE);
    }

    //
    // Update EfiVarStore opcode.
    //
    UpdateComAttributesVarStore (ComAttributes);
  }

  //
  // Initial the Out Of Band variable.
  //
  GetVariable2 (L"OutOfBand", &gOutOfBandGuid, (VOID **) &DevicePath, NULL);

  for (Index = 0; Index < TerminalMenu.MenuNumber; Index++) {
    NewMenuEntry = BOpt_GetMenuEntry (&TerminalMenu, Index);
    NewTerminalContext = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;
    NewTerminalContext->IsOutOfBand = FALSE;
    if (DevicePath != NULL) {
      DevicePathLen = GetDevicePathSize(NewTerminalContext->DevicePath) - sizeof (EFI_DEVICE_PATH_PROTOCOL);
      if (CompareMem(NewTerminalContext->DevicePath, DevicePath, DevicePathLen) == 0) {
        NewTerminalContext->IsOutOfBand = TRUE;
      }
    }
  }

EXIT:

  if (ComAttributes != NULL) {
    FreePool (ComAttributes);
  }

  if (Handles != NULL) {
    FreePool (Handles);
  }

  if (NewMenuEntry != NULL) {
    if (NewMenuEntry->HelpString != NULL) {
      FreePool (NewMenuEntry->HelpString);
    }
  }

  return Status;
}

/**
  Update Com Ports attributes from DevicePath

  @param DevicePath      DevicePath that contains Com ports
  @param ComAttributes   Com attributes buffer.

  @retval EFI_SUCCESS   The update is successful.
  @retval EFI_NOT_FOUND Can not find specific menu entry
**/
EFI_STATUS
UpdateComAttributeFromVariable (
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath,
  TOTAL_SERIAL_PORT_INFO    *ComAttributes
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *Node;
  EFI_DEVICE_PATH_PROTOCOL  *SerialNode;
  ACPI_HID_DEVICE_PATH      *Acpi;
  UART_DEVICE_PATH          *Uart;
  UART_DEVICE_PATH          *Uart1;
  UINTN                     TerminalNumber;
  BM_MENU_ENTRY             *NewMenuEntry;
  BM_TERMINAL_CONTEXT       *NewTerminalContext;
  UART_FLOW_CONTROL_DEVICE_PATH *FlowControlNode;
  BOOLEAN                   HasFlowControlNode;
  SERIAL_PORT_ATTRIBUTE     *ComInfo;
  EFI_DEVICE_PATH_PROTOCOL  *TmpDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePathInst;
  UINTN                     Size;
  BOOLEAN                   HasSerialNode;

  HasFlowControlNode = FALSE;
  TmpDevicePath     = DevicePath;
  DevicePathInst    = GetNextDevicePathInstance (&TmpDevicePath, &Size);

  //
  // Search for the match of 'Single' in 'Multi'
  //
  while (DevicePathInst != NULL) {
    Node            = DevicePathInst;
    Node            = NextDevicePathNode (Node);
    TerminalNumber  = 0;
    HasSerialNode   = FALSE;

    while (!IsDevicePathEnd (Node)) {
      Acpi = (ACPI_HID_DEVICE_PATH *) Node;
      if (IsIsaSerialNode (Acpi)) {
        HasSerialNode  = TRUE;
        CopyMem (&TerminalNumber, &Acpi->UID, sizeof (UINT32));
      }

      if ((DevicePathType (Node) == MESSAGING_DEVICE_PATH) && (DevicePathSubType (Node) == MSG_UART_DP)) {
        Uart          = (UART_DEVICE_PATH *) Node;
        if (HasSerialNode) {
          NewMenuEntry  = BOpt_GetMenuEntry (&TerminalMenu, TerminalNumber);
        } else {
          NewMenuEntry  = BOpt_GetMenuEntryFromDevicePath(&TerminalMenu, DevicePathInst);
        }
        if (NULL == NewMenuEntry) {
          return EFI_NOT_FOUND;
        }

        NewTerminalContext = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;
        CopyMem (
          &NewTerminalContext->BaudRate,
          &Uart->BaudRate,
          sizeof (UINT64)
          );

        CopyMem (
          &NewTerminalContext->DataBits,
          &Uart->DataBits,
          sizeof (UINT8)
          );

        CopyMem (
          &NewTerminalContext->Parity,
          &Uart->Parity,
          sizeof (UINT8)
          );

        CopyMem (
          &NewTerminalContext->StopBits,
          &Uart->StopBits,
          sizeof (UINT8)
          );

        FlowControlNode = (UART_FLOW_CONTROL_DEVICE_PATH *) NextDevicePathNode (Node);
        if (IsUartFlowControlNode (FlowControlNode)) {
          HasFlowControlNode = TRUE;
          NewTerminalContext->FlowControl = (UINT8) ReadUnaligned32 (&FlowControlNode->FlowControlMap);
        } else if (NewTerminalContext->FlowControl != 0) {
          //
          // No Flow Control device path node, assumption no Flow control
          //
          NewTerminalContext->FlowControl = 0;
        }

        //
        // Update info saved in "ComAttributes".
        //
        if (HasSerialNode) {
          ComInfo = GetComAttributes((UINT8*)ComAttributes, &TerminalNumber, NULL);
        } else {
          ComInfo = GetComAttributes((UINT8*)ComAttributes, NULL, DevicePathInst);
        }

        if (ComInfo == NULL) {
          return EFI_NOT_FOUND;
        }

        ComInfo->BaudRate    = NewTerminalContext->BaudRate;
        ComInfo->DataBits    = NewTerminalContext->DataBits;
        ComInfo->Parity      = NewTerminalContext->Parity;
        ComInfo->StopBits    = NewTerminalContext->StopBits;
        ComInfo->FlowControl = NewTerminalContext->FlowControl;

        SerialNode  = NewTerminalContext->DevicePath;
        SerialNode  = NextDevicePathNode (SerialNode);
        while (!IsDevicePathEnd (SerialNode)) {
          if ((DevicePathType (SerialNode) == MESSAGING_DEVICE_PATH) && (DevicePathSubType (SerialNode) == MSG_UART_DP)) {
            //
            // Update following device paths according to
            // previous acquired uart attributes
            //
            Uart1 = (UART_DEVICE_PATH *) SerialNode;
            CopyMem (
              &Uart1->BaudRate,
              &NewTerminalContext->BaudRate,
              sizeof (UINT64)
              );

            CopyMem (
              &Uart1->DataBits,
              &NewTerminalContext->DataBits,
              sizeof (UINT8)
              );
            CopyMem (
              &Uart1->Parity,
              &NewTerminalContext->Parity,
              sizeof (UINT8)
              );
            CopyMem (
              &Uart1->StopBits,
              &NewTerminalContext->StopBits,
              sizeof (UINT8)
              );

            FlowControlNode = (UART_FLOW_CONTROL_DEVICE_PATH *) NextDevicePathNode (SerialNode);
            if (IsUartFlowControlNode (FlowControlNode)) {
              FlowControlNode->FlowControlMap = NewTerminalContext->FlowControl;
            } else {
              if (HasFlowControlNode) {
                mFlowControlDevicePath.FlowControlMap = NewTerminalContext->FlowControl;
                NewTerminalContext->DevicePath = AppendDevicePathNode (
                                             NewTerminalContext->DevicePath,
                                             (EFI_DEVICE_PATH_PROTOCOL *) (&mFlowControlDevicePath)
                                             );
              }
            }
            break;
          }

          SerialNode = NextDevicePathNode (SerialNode);
        }
        //
        // end while
        //
      }

      Node = NextDevicePathNode (Node);
    }

    FreePool (DevicePathInst);
    DevicePathInst = GetNextDevicePathInstance (&DevicePath, &Size);
  }

  return EFI_SUCCESS;
}

/**
  Build up Console Menu based on types passed in. The type can
  be BM_CONSOLE_IN_CONTEXT_SELECT, BM_CONSOLE_OUT_CONTEXT_SELECT
  and BM_CONSOLE_ERR_CONTEXT_SELECT.

  @param ConsoleMenuType Can be BM_CONSOLE_IN_CONTEXT_SELECT, BM_CONSOLE_OUT_CONTEXT_SELECT
                         and BM_CONSOLE_ERR_CONTEXT_SELECT.

  @retval EFI_UNSUPPORTED The type passed in is not in the 3 types defined.
  @retval EFI_NOT_FOUND   If the EFI Variable defined in UEFI spec with name "ConOutDev",
                          "ConInDev" or "ConErrDev" doesn't exists.
  @retval EFI_OUT_OF_RESOURCES Not enough resource to complete the operations.
  @retval EFI_SUCCESS          Function completes successfully.

**/
EFI_STATUS
GetConsoleMenu (
  IN UINTN              ConsoleMenuType
  )
{
  EFI_DEVICE_PATH_PROTOCOL  *DevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *AllDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *MultiDevicePath;
  EFI_DEVICE_PATH_PROTOCOL  *DevicePathInst;
  UINTN                     Size;
  UINTN                     DevicePathSize;
  UINTN                     AllDevicePathSize;
  UINTN                     AllCount;
  UINTN                     Index;
  UINTN                     Index2;
  BM_MENU_ENTRY             *NewMenuEntry;
  BM_CONSOLE_CONTEXT        *NewConsoleContext;
  TYPE_OF_TERMINAL          Terminal;
  UINTN                     Com;
  BM_MENU_OPTION            *ConsoleMenu;

  DevicePath    = NULL;
  AllDevicePath = NULL;
  AllCount      = 0;
  switch (ConsoleMenuType) {
  case BM_CONSOLE_IN_CONTEXT_SELECT:
    ConsoleMenu   = &ConsoleInpMenu;
    GetEfiGlobalVariable2 (L"ConIn", (VOID **) &DevicePath, &DevicePathSize);
    GetEfiGlobalVariable2 (L"ConInDev", (VOID **) &AllDevicePath, &AllDevicePathSize);
    break;

  case BM_CONSOLE_OUT_CONTEXT_SELECT:
    ConsoleMenu   = &ConsoleOutMenu;
    GetEfiGlobalVariable2 (L"ConOut", (VOID **) &DevicePath, &DevicePathSize);
    GetEfiGlobalVariable2 (L"ConOutDev", (VOID **) &AllDevicePath, &AllDevicePathSize);
    break;

  case BM_CONSOLE_ERR_CONTEXT_SELECT:
    ConsoleMenu   = &ConsoleErrMenu;
    GetEfiGlobalVariable2 (L"ErrOut", (VOID **) &DevicePath, &DevicePathSize);
    GetEfiGlobalVariable2 (L"ErrOutDev", (VOID **) &AllDevicePath, &AllDevicePathSize);
    break;

  default:
    return EFI_UNSUPPORTED;
  }

  if ((NULL == DevicePath) || (DevicePathSize < sizeof (EFI_DEVICE_PATH_PROTOCOL))) {
    return EFI_NOT_FOUND;
  }

  if ((NULL == AllDevicePath) || (AllDevicePathSize < sizeof (EFI_DEVICE_PATH_PROTOCOL))) {
    return EFI_NOT_FOUND;
  }

  InitializeListHead (&ConsoleMenu->Head);

  AllCount                = EfiDevicePathInstanceCount (AllDevicePath);
  ConsoleMenu->MenuNumber = 0;
  //
  // Following is menu building up for Console Devices selected.
  //
  MultiDevicePath = AllDevicePath;
  Index2          = 0;
  for (Index = 0; Index < AllCount; Index++) {
    DevicePathInst  = GetNextDevicePathInstance (&MultiDevicePath, &Size);

    NewMenuEntry    = BOpt_CreateMenuEntry (BM_CONSOLE_CONTEXT_SELECT);
    if (NULL == NewMenuEntry) {
      return EFI_OUT_OF_RESOURCES;
    }

    NewConsoleContext             = (BM_CONSOLE_CONTEXT *) NewMenuEntry->VariableContext;
    NewMenuEntry->OptionNumber    = Index2;

    NewConsoleContext->DevicePath = DuplicateDevicePath (DevicePathInst);
    ASSERT (NewConsoleContext->DevicePath != NULL);
    if (NewConsoleContext->DevicePath == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }
    NewMenuEntry->DisplayString   = EfiLibStrFromDatahub (NewConsoleContext->DevicePath);
    if (NULL == NewMenuEntry->DisplayString) {
      NewMenuEntry->DisplayString = UiDevicePathToStr (NewConsoleContext->DevicePath);
    }

    NewConsoleContext->IsTerminal = IsTerminalDevicePath (
                                      NewConsoleContext->DevicePath,
                                      &Terminal,
                                      &Com
                                      );

    NewConsoleContext->IsActive = MatchDevicePaths (
                                    DevicePath,
                                    NewConsoleContext->DevicePath
                                    );

    if (NewConsoleContext->IsTerminal) {
      BOpt_DestroyMenuEntry (NewMenuEntry);
    } else {
      Index2++;
      ConsoleMenu->MenuNumber++;
      InsertTailList (&ConsoleMenu->Head, &NewMenuEntry->Link);
    }
  }

  return EFI_SUCCESS;
}

/**
  Build up ConsoleOutMenu, ConsoleInpMenu and ConsoleErrMenu

  @retval EFI_SUCCESS    The function always complete successfully.

**/
EFI_STATUS
GetAllConsoles (
  VOID
  )
{
  GetConsoleMenu (BM_CONSOLE_IN_CONTEXT_SELECT);
  GetConsoleMenu (BM_CONSOLE_OUT_CONTEXT_SELECT);
  GetConsoleMenu (BM_CONSOLE_ERR_CONTEXT_SELECT);
  return EFI_SUCCESS;
}

/**
  Free ConsoleOutMenu, ConsoleInpMenu and ConsoleErrMenu

  @retval EFI_SUCCESS    The function always complete successfully.
**/
EFI_STATUS
FreeAllConsoles (
  VOID
  )
{
  BOpt_FreeMenu (&ConsoleOutMenu);
  BOpt_FreeMenu (&ConsoleInpMenu);
  BOpt_FreeMenu (&ConsoleErrMenu);
  BOpt_FreeMenu (&TerminalMenu);
  return EFI_SUCCESS;
}

/**
  Test whether DevicePath is a valid Terminal


  @param DevicePath      DevicePath to be checked
  @param Termi           If DevicePath is valid Terminal, terminal type is returned.
  @param Com             If DevicePath is valid Terminal, Com Port type is returned.

  @retval  TRUE         If DevicePath point to a Terminal.
  @retval  FALSE        If DevicePath does not point to a Terminal.

**/
BOOLEAN
IsTerminalDevicePath (
  IN  EFI_DEVICE_PATH_PROTOCOL *DevicePath,
  OUT TYPE_OF_TERMINAL         *Termi,
  OUT UINTN                    *Com
  )
{
  BOOLEAN                   IsTerminal;
  EFI_DEVICE_PATH_PROTOCOL  *Node;
  VENDOR_DEVICE_PATH        *Vendor;
  UART_DEVICE_PATH          *Uart;
  ACPI_HID_DEVICE_PATH      *Acpi;

  IsTerminal = FALSE;

  Uart   = NULL;
  Vendor = NULL;
  Acpi   = NULL;
  for (Node = DevicePath; !IsDevicePathEnd (Node); Node = NextDevicePathNode (Node)) {
    //
    // Vendor points to the node before the End node
    //
    Vendor = (VENDOR_DEVICE_PATH *) Node;

    if ((DevicePathType (Node) == MESSAGING_DEVICE_PATH) && (DevicePathSubType (Node) == MSG_UART_DP)) {
      Uart = (UART_DEVICE_PATH *) Node;
    }

    if (Uart == NULL) {
      //
      // Acpi points to the node before the UART node
      //
      Acpi = (ACPI_HID_DEVICE_PATH *) Node;
    }
  }

  if (Vendor == NULL ||
      DevicePathType (Vendor) != MESSAGING_DEVICE_PATH ||
      DevicePathSubType (Vendor) != MSG_VENDOR_DP ||
      Uart == NULL) {
    return FALSE;
  }

  //
  // There are four kinds of Terminal types
  // check to see whether this devicepath
  // is one of that type
  //
  if (CompareGuid (&Vendor->Guid, &TerminalTypeGuid[0])) {
    *Termi      = TerminalTypePcAnsi;
    IsTerminal  = TRUE;
  } else {
    if (CompareGuid (&Vendor->Guid, &TerminalTypeGuid[1])) {
      *Termi      = TerminalTypeVt100;
      IsTerminal  = TRUE;
    } else {
      if (CompareGuid (&Vendor->Guid, &TerminalTypeGuid[2])) {
        *Termi      = TerminalTypeVt100Plus;
        IsTerminal  = TRUE;
      } else {
        if (CompareGuid (&Vendor->Guid, &TerminalTypeGuid[3])) {
          *Termi      = TerminalTypeVtUtf8;
          IsTerminal  = TRUE;
        } else {
          IsTerminal = FALSE;
        }
      }
    }
  }

  if (!IsTerminal) {
    return FALSE;
  }

  if ((Acpi != NULL) && IsIsaSerialNode (Acpi)) {
    CopyMem (Com, &Acpi->UID, sizeof (UINT32));
  } else {
    return FALSE;
  }

  return TRUE;
}

/**
  Get mode number according to column and row

  @param CallbackData    The BMM context data.
**/
VOID
GetConsoleOutMode (
  IN  BMM_CALLBACK_DATA    *CallbackData
  )
{
  UINTN                         Col;
  UINTN                         Row;
  UINTN                         CurrentCol;
  UINTN                         CurrentRow;
  UINTN                         Mode;
  UINTN                         MaxMode;
  EFI_STATUS                    Status;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;

  ConOut   = gST->ConOut;
  MaxMode  = (UINTN) (ConOut->Mode->MaxMode);

  CurrentCol = PcdGet32 (PcdConOutColumn);
  CurrentRow = PcdGet32 (PcdConOutRow);
  for (Mode = 0; Mode < MaxMode; Mode++) {
    Status = ConOut->QueryMode (ConOut, Mode, &Col, &Row);
    if (!EFI_ERROR(Status)) {
      if (CurrentCol == Col && CurrentRow == Row) {
        CallbackData->BmmFakeNvData.ConsoleOutMode = (UINT16) Mode;
        break;
      }
    }
  }
}

/**

  Initialize console input device check box to ConsoleInCheck[MAX_MENU_NUMBER]
  in BMM_FAKE_NV_DATA structure.

  @param CallbackData    The BMM context data.

**/
VOID
GetConsoleInCheck (
  IN  BMM_CALLBACK_DATA    *CallbackData
  )
{
  UINT16              Index;
  BM_MENU_ENTRY       *NewMenuEntry;
  UINT8               *ConInCheck;
  BM_CONSOLE_CONTEXT  *NewConsoleContext;

  ASSERT (CallbackData != NULL);
  if (CallbackData == NULL) {
    return;
  }

  ConInCheck = &CallbackData->BmmFakeNvData.ConsoleInCheck[0];
  if (ConInCheck == NULL) {
    return;
  }

  for (Index = 0; ((Index < ConsoleInpMenu.MenuNumber) && \
       (Index < MAX_MENU_NUMBER)) ; Index++) {
    NewMenuEntry      = BOpt_GetMenuEntry (&ConsoleInpMenu, Index);
    NewConsoleContext = (BM_CONSOLE_CONTEXT *) NewMenuEntry->VariableContext;
    ConInCheck[Index] = NewConsoleContext->IsActive;
  }
}

/**

  Initialize console output device check box to ConsoleOutCheck[MAX_MENU_NUMBER]
  in BMM_FAKE_NV_DATA structure.

  @param CallbackData    The BMM context data.

**/
VOID
GetConsoleOutCheck (
  IN  BMM_CALLBACK_DATA    *CallbackData
  )
{
  UINT16              Index;
  BM_MENU_ENTRY       *NewMenuEntry;
  UINT8               *ConOutCheck;
  BM_CONSOLE_CONTEXT  *NewConsoleContext;

  ASSERT (CallbackData != NULL);
  if (CallbackData == NULL) return;

  ConOutCheck = &CallbackData->BmmFakeNvData.ConsoleOutCheck[0];

  if (ConOutCheck != NULL) {
    for (Index = 0; ((Index < ConsoleOutMenu.MenuNumber) && \
         (Index < MAX_MENU_NUMBER)) ; Index++) {
      NewMenuEntry      = BOpt_GetMenuEntry (&ConsoleOutMenu, Index);
      NewConsoleContext = (BM_CONSOLE_CONTEXT *) NewMenuEntry->VariableContext;
      ConOutCheck[Index] = NewConsoleContext->IsActive;
    }
  }
}

/**

  Initialize standard error output device check box to ConsoleErrCheck[MAX_MENU_NUMBER]
  in BMM_FAKE_NV_DATA structure.

  @param CallbackData    The BMM context data.

**/
VOID
GetConsoleErrCheck (
  IN  BMM_CALLBACK_DATA    *CallbackData
  )
{
  UINT16              Index;
  BM_MENU_ENTRY       *NewMenuEntry;
  UINT8               *ConErrCheck;
  BM_CONSOLE_CONTEXT  *NewConsoleContext;

  ASSERT (CallbackData != NULL);
  if (CallbackData == NULL) return;

  ConErrCheck = &CallbackData->BmmFakeNvData.ConsoleErrCheck[0];

  if (ConErrCheck != NULL) {
    for (Index = 0; ((Index < ConsoleErrMenu.MenuNumber) && \
         (Index < MAX_MENU_NUMBER)) ; Index++) {
      NewMenuEntry      = BOpt_GetMenuEntry (&ConsoleErrMenu, Index);
      NewConsoleContext = (BM_CONSOLE_CONTEXT *) NewMenuEntry->VariableContext;
      ConErrCheck[Index] = NewConsoleContext->IsActive;
    }
  }
}

/**

  Initialize terminal attributes (baudrate, data rate, stop bits, parity and terminal type)
  to BMM_FAKE_NV_DATA structure.

  @param CallbackData    The BMM context data.

**/
VOID
GetTerminalAttribute (
  IN  BMM_CALLBACK_DATA    *CallbackData
  )
{
  BMM_FAKE_NV_DATA     *CurrentFakeNVMap;
  BM_MENU_ENTRY        *NewMenuEntry;
  BM_TERMINAL_CONTEXT  *NewTerminalContext;
  UINT16               TerminalIndex;
  UINT8                AttributeIndex;

  ASSERT (CallbackData != NULL);
  if (CallbackData == NULL) {
    return;
  }

  CurrentFakeNVMap = &CallbackData->BmmFakeNvData;
  if (CurrentFakeNVMap == NULL) {
    return;
  }

  for (TerminalIndex = 0; ((TerminalIndex < TerminalMenu.MenuNumber) && \
       (TerminalIndex < MAX_MENU_NUMBER)); TerminalIndex++) {
    NewMenuEntry        = BOpt_GetMenuEntry (&TerminalMenu, TerminalIndex);
    NewTerminalContext  = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;
    for (AttributeIndex = 0; AttributeIndex < sizeof (BaudRateList) / sizeof (BaudRateList [0]); AttributeIndex++) {
      if (NewTerminalContext->BaudRate == (UINT64) (BaudRateList[AttributeIndex].Value)) {
        NewTerminalContext->BaudRateIndex = AttributeIndex;
        break;
      }
    }
    for (AttributeIndex = 0; AttributeIndex < sizeof (DataBitsList) / sizeof (DataBitsList[0]); AttributeIndex++) {
      if (NewTerminalContext->DataBits == (UINT64) (DataBitsList[AttributeIndex].Value)) {
        NewTerminalContext->DataBitsIndex = AttributeIndex;
        break;
      }
    }

    for (AttributeIndex = 0; AttributeIndex < sizeof (ParityList) / sizeof (ParityList[0]); AttributeIndex++) {
      if (NewTerminalContext->Parity == (UINT64) (ParityList[AttributeIndex].Value)) {
        NewTerminalContext->ParityIndex = AttributeIndex;
        break;
      }
    }

    for (AttributeIndex = 0; AttributeIndex < sizeof (StopBitsList) / sizeof (StopBitsList[0]); AttributeIndex++) {
      if (NewTerminalContext->StopBits == (UINT64) (StopBitsList[AttributeIndex].Value)) {
        NewTerminalContext->StopBitsIndex = AttributeIndex;
        break;
      }
    }
    CurrentFakeNVMap->COMBaudRate[TerminalIndex]     = NewTerminalContext->BaudRateIndex;
    CurrentFakeNVMap->COMDataRate[TerminalIndex]     = NewTerminalContext->DataBitsIndex;
    CurrentFakeNVMap->COMStopBits[TerminalIndex]     = NewTerminalContext->StopBitsIndex;
    CurrentFakeNVMap->COMParity[TerminalIndex]       = NewTerminalContext->ParityIndex;
    CurrentFakeNVMap->COMTerminalType[TerminalIndex] = NewTerminalContext->TerminalType;
    CurrentFakeNVMap->COMFlowControl[TerminalIndex]  = NewTerminalContext->FlowControl;
    CurrentFakeNVMap->COMLegacyResolution[TerminalIndex] = NewTerminalContext->LegacyResolution;
    CurrentFakeNVMap->COMIsEnabled[TerminalIndex]      = NewTerminalContext->IsEnabled;
  }
}


/**

  Initialize Com Output band port (COMOutOfBandPort) to BMM_FAKE_NV_DATA structure.

  @param CallbackData    The BMM context data.

**/
VOID
GetComOutOfBandPort (
  IN  BMM_CALLBACK_DATA    *CallbackData
  )
{
  UINT16                  Index;
  BM_MENU_ENTRY           *NewMenuEntry;
  BM_TERMINAL_CONTEXT     *NewTerminalContext;

  if (CallbackData == NULL) {
    return;
  }

  if (TerminalMenu.MenuNumber > 0) {
    for (Index = 0; Index < TerminalMenu.MenuNumber; Index++) {
      NewMenuEntry = BOpt_GetMenuEntry (&TerminalMenu, Index);
      NewTerminalContext = (BM_TERMINAL_CONTEXT *) NewMenuEntry->VariableContext;
      if (NewTerminalContext->IsOutOfBand) {
        CallbackData->BmmFakeNvData.COMOutOfBandPort = Index;
        break;
      }
    }
    if (Index == TerminalMenu.MenuNumber) {
      CallbackData->BmmFakeNvData.COMOutOfBandPort = Index;
    }
  }
}


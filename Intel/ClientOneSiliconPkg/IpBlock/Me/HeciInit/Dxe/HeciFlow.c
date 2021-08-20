/** @file
  Heci driver core for PEI & DXE phases, determines the HECI device and
  initializes it.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/DxeMeLib.h>
#include <MeiBusMsg.h>
#include <Protocol/HeciProtocol.h>
#include <Protocol/HeciFlowProtocol.h>

#define DEVICES_SUPPORTED 5
#define HECI_FLOW_TIMEOUT  1000000 //1s
#define HECI_FLOW_TIMESTEP 1000    //1ms

typedef struct {
  EFI_GUID Guid;
  UINT8    MeAddr;
  UINT8    HostAddr;
} HECI_FLOW_CLIENT;

typedef enum {
  NotInitialized,
  Started,
  Shutdown
} HECI_FLOW_STATE;

typedef struct {
  HECI_DEVICE        DevNumber;
  HECI_FLOW_STATE    State;
  UINT32             ClientsQuantity;
  HECI_FLOW_CLIENT   *Clients;
} DEVICE_CONTEXT;

typedef struct {
  UINT32             Quantity;
  DEVICE_CONTEXT     **Device;
} HECI_FLOW_CONTEXT;

GLOBAL_REMOVE_IF_UNREFERENCED  HECI_FLOW_CONTEXT     gFlowContext;
GLOBAL_REMOVE_IF_UNREFERENCED  HECI_FLOW_PROTOCOL    gHeciFlowProtocol;

/**
  Returns driver context for single HECI device
  If context doesn't exist yet, it is created
  Set of contexts is kept in global variable

  @param[in] Device    HECI device number

  @retval              Pointer to context for selected HECI device
**/
DEVICE_CONTEXT*
GetDeviceContext (
  IN HECI_DEVICE Device
  )
{
  UINT32         Index;
  DEVICE_CONTEXT **Array;
  DEVICE_CONTEXT *NewDev;

  //
  // If context for given device already exists, return it
  //
  for (Index = 0; Index < gFlowContext.Quantity; Index++) {
    if (gFlowContext.Device[Index]->DevNumber == Device) {
      return gFlowContext.Device[Index];
    }
  }
  //
  // Otherwise, alloc new device context...
  //
  NewDev = AllocateZeroPool (sizeof (DEVICE_CONTEXT));
  if (NewDev == NULL) {
    return NULL;
  }
  NewDev->DevNumber = Device;
  NewDev->State = NotInitialized;
  NewDev->ClientsQuantity = 0;
  //
  // ...and resize the array of pointers to device contexts
  //
  Array = AllocateZeroPool ((gFlowContext.Quantity + 1) * sizeof (DEVICE_CONTEXT*));
  if (Array == NULL) {
    return NULL;
  }
  CopyMem (Array, gFlowContext.Device, gFlowContext.Quantity * sizeof (DEVICE_CONTEXT*));
  Array[gFlowContext.Quantity] = NewDev;
  if (gFlowContext.Device != NULL) {
    FreePool (gFlowContext.Device);
  }
  gFlowContext.Device = Array;
  gFlowContext.Quantity++;
  return gFlowContext.Device[gFlowContext.Quantity - 1];
}

/**
  Counts how many bits are set in an array of bytes

  @param[in] Bytes   Array length
  @param[in] Byte    Array

  @retval UINT32     Number of bits set
**/
UINT32
CountBits (
  IN UINT32 Bytes,
  IN UINT8  *Byte
  )
{
  UINT32 ByteIndex;
  UINT8  BitIndex;
  UINT32 Result;

  Result = 0;
  for (ByteIndex = 0; ByteIndex < Bytes; ByteIndex++) {
    for (BitIndex = 0; BitIndex < 8; BitIndex++) {
      if (Byte[ByteIndex] & (1 << BitIndex)) {
        Result++;
      }
    }
  }
  return Result;
}

/**
  Creates a new connection between BIOS and CSME client.
  This includes reading the 1st flow control token that CSME will send immediately after connection is established.

  @param[in]    HeciDev          HECI device number
  @param[in]    HostAddr         Host Address of the new connection
  @param[in]    MeAddr           CSME Address of the new connection

  @retval EFI_SUCCESS            Connection was created, error otherwise
**/
EFI_STATUS
CreateConnection (
  IN  HECI_DEVICE HeciDev,
  IN  UINT8       HostAddr,
  IN  UINT8       MeAddr
  )
{
  EFI_STATUS Status;

  Status = HbmHostClientConnect (HeciDev, MeAddr, HostAddr);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "HbmHostClientConnect %r\n", Status));
    return Status;
  }
  Status = HbmGetFlowControlToken (HeciDev, HostAddr, MeAddr);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "HbmGetFlowControlToken %r\n", Status));
    return Status;
  }
  return Status;
}

/**
  Converts CSME client's GUID to HostAddress:MeAddress pair based on protocol context.
  Address pair identifies the connection and must be passed in HECI messages to CSME.
  If no connection for given GUID exist, a new one will be created and assigned new address pair.
  This function always sets the same HostAddr as MeAddr.

  @param[in]    Context          Driver context for single HECI device
  @param[in]    Guid             GUID of the client inside CSME
  @param[out]   HostAddr         Host Address to be used in HECI message's header
  @param[out]   MeAddr           CSME Address to be used in HECI message's header

  @retval EFI_SUCCESS            Address pair was found, error otherwise
**/
EFI_STATUS
GuidToAddressPair (
  IN       DEVICE_CONTEXT    *Context,
  IN CONST EFI_GUID          *Guid,
  OUT      UINT8             *HostAddr,
  OUT      UINT8             *MeAddr
  )
{
  UINT32     Index;
  EFI_STATUS Status;

  Status = EFI_SUCCESS;
  for (Index = 0; Index < Context->ClientsQuantity; Index++) {
    if (CompareGuid (&(Context->Clients[Index].Guid), Guid)) {
      *MeAddr = Context->Clients[Index].MeAddr;
      if (Context->Clients[Index].HostAddr == 0) {
        Status = CreateConnection (Context->DevNumber, *MeAddr, *MeAddr);
        Context->Clients[Index].HostAddr = *MeAddr;
      }
      *HostAddr = Context->Clients[Index].HostAddr;
      return Status;
    }
  }
  return EFI_NOT_FOUND;
}

/**
  Initializes HECI_FLOW_PROTOCOL context for given Heci device.
  First BIOS reads the list of CSME clients available under given Heci device then reads the GUID of each one.
  This information is stored in protocol's context.

  @param[in,out]  Context          Context for a single HECI device

  @retval         EFI_SUCCESS if context was initialized, error otherwise
**/
EFI_STATUS
InitializeDeviceContext (
  IN OUT DEVICE_CONTEXT *Context
  )
{
  EFI_STATUS        Status;
  UINT8             ValidAddressesList[32];
  UINT8             MeAddr;
  UINT32            Index;
  HECI_PROTOCOL     *Heci;

  if (Context->State != NotInitialized) {
    return EFI_ALREADY_STARTED;
  }
  //
  // In case of any error during context init, shutdown state will mark that protocol can't work on this Heci device,
  //
  Context->State = Shutdown;

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &(Heci));
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "HECI protocol missing\n"));
    return Status;
  }

  Status = HbmHostVersion (Context->DevNumber);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "HbmHostVersion %r\n", Status));
    return Status;
  }

  Status = HbmHostEnumRequest (Context->DevNumber, ValidAddressesList);
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "HbmHostEnumRequest %r\n", Status));
    return Status;
  }
  Context->ClientsQuantity = CountBits (32, ValidAddressesList);
  Context->Clients = AllocateZeroPool (Context->ClientsQuantity * sizeof (HECI_FLOW_CLIENT));
  if (Context->Clients == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Index = 0;
  for (MeAddr = 0; MeAddr < NUMBER_OF_VALID_ADDRESS_BITS - 1; MeAddr++) {
    if (ValidAddressesList[MeAddr / 8] & (0x1 << MeAddr % 8)) {
      Status = HbmGetClientProperties (Context->DevNumber, MeAddr, &(Context->Clients[Index].Guid));
      if (EFI_ERROR (Status)) {
        continue;
      }
      Context->Clients[Index].MeAddr = MeAddr;
      Context->Clients[Index].HostAddr = 0;
      Index++;
    }
  }
 Context->State = Started;

 return EFI_SUCCESS;
}

/**
  This function sends a HECI message to a CSME client identified by GUID over a connection with flow control, then
  waits for reponse. Message exchange flow is:
  [at start of exchange BIOS has flow control token and CSME does not]
  1. BIOS sends message; this consumes the token received in [4]
  2. BIOS sends flow control token to CSME
  3. CSME sends response; this consumes the token received in [2]
  4. CSME sends flow control token to BIOS
  [on exit, again BIOS has control token and CSME does not]
  ... but may be preceded by context/connection initialization when needed.

  If this is 1st use of this function for given HeciDev number, it initializes driver context for this device. Context
  initialization includes reading a list of all client GUIDs available inside CSME for that device.

  If this is 1st use of this function for given client GUID, it creates a connection with that client nad assigns
  Host Address equal to Me Address for that connection. When connection is created, BIOS receives initial flow control token.
  Connections are kept until end of BIOS execution (ExitBootServices event). Only a single connection will be created per
  CSME client, regardless of how many simultaneous connections it supports, but this single connection can be reused by
  multiple BIOS modules. This protocol does not distinguish its users.

  @param[in]    HeciDev          HECI device number
  @param[inout] Message          On entry, contains message to be sent; on exit, contains response
  @param[in]    Length           Length of message in buffer
  @param[inout] RespLength       On entry, max length of response; on exit, actual length of response
  @param[in]    Guid             GUID of the client inside CSME

  @retval EFI_SUCCESS            Message was sent and response was received
  @retval EFI_BUFFER_TOO_SMALL   Message was sent and a response arrived but it was too big for provided buffer
  @retval EFI_TIMEOUT            No response received
  @retval EFI_PROTOCOL_ERROR     Internal HECI error or missing flow control token
**/
EFI_STATUS
EFIAPI
SendAndReceive (
  IN       HECI_DEVICE    HeciDev,
  IN OUT   VOID           *Message,
  IN       UINT32         Length,
  IN OUT   UINT32         *RespLength,
  IN CONST EFI_GUID       *Guid
  )
{
  EFI_STATUS      Status;
  EFI_STATUS      Status2;
  UINT32          MsgLength;
  UINT8           HostAddr;
  UINT8           MeAddr;
  HECI_PROTOCOL   *Heci;
  DEVICE_CONTEXT  *Context;

  DEBUG ((DEBUG_INFO, "HECI FLOW send and receive\n"));

  Context = GetDeviceContext (HeciDev);
  if (Context == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  if (Context->State == NotInitialized) {
    Status = InitializeDeviceContext (Context);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else if (Context->State == Shutdown) {
    DEBUG ((DEBUG_ERROR, "after shutdown\n"));
    return EFI_UNSUPPORTED;
  }

  Status = GuidToAddressPair (Context, Guid, &HostAddr, &MeAddr);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &(Heci));
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "HECI protocol missing\n"));
    return Status;
  }
  Status =  Heci->SendMsg (HeciDev, (UINT32 *)Message, Length, HostAddr, MeAddr);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = HbmSendFlowControlToken (HeciDev, HostAddr, MeAddr);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  MsgLength = *RespLength;
  Status = Heci->ReadMsg (HeciDev, BLOCKING, (UINT32*)Message, &MsgLength);

  *RespLength = MsgLength;
  if (EFI_ERROR (Status) && Status != EFI_BUFFER_TOO_SMALL) {
    return Status;
  }
  Status2 = HbmGetFlowControlToken (HeciDev, HostAddr, MeAddr);
  if (EFI_ERROR (Status2)) {
    return EFI_PROTOCOL_ERROR;
  }
  return Status;
}


/**
  This function sends a HECI message to a CSME client identified by GUID over a connection with flow control.
  It does not expect response, except for flow control token.
  For more details see description of SendAndReceive function

  @param[in]  HeciDev          HECI device number
  @param[in]  Message          Buffer containing message to be sent
  @param[in]  Length           Length of message in buffer
  @param[in]  Guid             GUID of the client inside CSME

  @retval EFI_SUCCESS          Message could be sent, error otherwise
**/
EFI_STATUS
EFIAPI
Send (
  IN       HECI_DEVICE   HeciDev,
  IN       VOID          *Message,
  IN       UINT32        Length,
  IN CONST EFI_GUID      *Guid
  )
{
  EFI_STATUS     Status;
  UINT8          HostAddr;
  UINT8          MeAddr;
  HECI_PROTOCOL  *Heci;
  DEVICE_CONTEXT *Context;

  DEBUG ((DEBUG_ERROR, "HECI FLOW send\n"));
  Context = GetDeviceContext (HeciDev);
  if (Context == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }
  if (Context->State == NotInitialized) {
    Status = InitializeDeviceContext (Context);
    if (EFI_ERROR (Status)) {
      return Status;
    }
  } else if (Context->State == Shutdown) {
    DEBUG ((DEBUG_ERROR, "after shutdown\n"));
    return EFI_UNSUPPORTED;
  }

  Status = GuidToAddressPair (Context, Guid, &HostAddr, &MeAddr);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = gBS->LocateProtocol (&gHeciProtocolGuid, NULL, (VOID **) &(Heci));
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "HECI protocol missing\n"));
    return Status;
  }
  Status = Heci->SendMsg (HeciDev, (UINT32 *)Message, Length, HostAddr, MeAddr);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  Status = HbmGetFlowControlToken (HeciDev, HostAddr, MeAddr);
  if (EFI_ERROR (Status)) {
    return Status;
  }
  return Status;
}

/**
  Function to disconnect all HECI Flow connections for a single HECI device.

  @param[in]  HeciDev          HECI device number

**/
VOID
DisconnectHeciDevice (
  IN DEVICE_CONTEXT *Context
  )
{
  UINT32            Index;

  DEBUG ((DEBUG_INFO, "DisconnectHeciDevice %d(%d)\n", Context->DevNumber, Context->State));
  if (Context->State == Started) {
    for (Index = 0; Index < Context->ClientsQuantity; Index++) {
      if (Context->Clients[Index].HostAddr != 0) {
        HbmClientDisconnect (Context->DevNumber, Context->Clients[Index].HostAddr, Context->Clients[Index].MeAddr);
      }
    }
    Context->ClientsQuantity = 0;
    FreePool (Context->Clients);
  }
  Context->State = Shutdown;
}

/**
  Function to disconnect all HECI Flow connections for all HECI devices

  @param[in]  Event                   Pointer to this event
  @param[in]  Context                 Event handler private data

**/
VOID
EFIAPI
HeciFlowDisconnect (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  )
{
  UINT32         Index;
  DEVICE_CONTEXT *DevContext;
  for (Index = 0; Index < gFlowContext.Quantity; Index++) {
    DevContext = gFlowContext.Device[Index];
    DisconnectHeciDevice (DevContext);
    FreePool (DevContext);
  }
  if (gFlowContext.Device != NULL) {
    FreePool (gFlowContext.Device);
  }
}

/**
  Function to register ExitBootServices event and LegacyBoot callbacks for disconnecting all HECI Flow connections
**/
VOID
RegisterShutdownForHeciFlow (
  VOID
  )
{
  EFI_EVENT                   Event;
  EFI_STATUS                  Status;

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  HeciFlowDisconnect,
                  NULL,
                  &gEfiEventExitBootServicesGuid,
                  &Event
                  );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_NOTIFY,
                  HeciFlowDisconnect,
                  NULL,
                  &gEfiEventLegacyBootGuid,
                  &Event
                  );
  ASSERT_EFI_ERROR (Status);
}

/*
  Installs HECI_FLOW_PROTOCOL and registers a callback to uninstall it on exit boot services

  @retval EFI_SUCCESS       Protocol was installed, error otherwise
*/
EFI_STATUS
EFIAPI
InitializeHeciFlow (
  VOID
  )
{
  EFI_HANDLE    Handle;
  EFI_STATUS    Status;

  DEBUG ((DEBUG_INFO, "%a () Start\n", __FUNCTION__));

  Handle = NULL;
  gHeciFlowProtocol.SendAndReceive = (HECI_FLOW_SEND_AND_RECEIVE)&SendAndReceive;
  gHeciFlowProtocol.Send           = (HECI_FLOW_SEND)&Send;
  gFlowContext.Quantity            = 0;
  gFlowContext.Device              = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gHeciFlowProtocolGuid,
                  &gHeciFlowProtocol,
                  NULL
                  );
  RegisterShutdownForHeciFlow ();

  return Status;
}


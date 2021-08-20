/** @file
  Implementation file for communication functionalities by MEI (HECI)

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeMeLib.h>
#include <Library/HobLib.h>
#include <MeBiosPayloadHob.h>
#include <MeiBusMsg.h>
#include <Library/DxeJhiSupportLib.h>
#include <JhiInternal.h>
#include <Library/DxeBeihaiLib/Mei.h>

#ifdef _MSC_VER
#pragma warning ( disable: 4200 )         // zero-sized array in struct/union
#endif

#define JHI_MEI_HECI_DEVICE               HECI1_DEVICE  // always use HECI#1


#define EN_MEI_TXF_SPEEDUP                (1)

#if EN_MEI_TXF_SPEEDUP
#define MAX_TXRX_LENGTH                   (4064)
#else
#define MAX_HECIMSG_SIZE                  (0x1FC)
#define MAX_TXRX_LENGTH                   (MAX_HECIMSG_SIZE * 8)  // must be multiple of 0x1FC
#define MAKE_ALIEN_SIZE(len)              (((len) / MAX_HECIMSG_SIZE) * MAX_HECIMSG_SIZE)
#endif
#define MEIRCV_MINLEN                     (32)

#define min(x,y)                          (((x)>(y))?(y):(x))

#define HBM_PROTOCOL_ADDRESS              (0)       // HECI bus message protocol address
#define CLIENT_HOST_ADDRESS               (1)       // HECI Client host address

#define BEIHAI_MAX_RETRY                  (1)

#define HECI_HEADER_SIZE 4

enum  // same as JHI_PLATFROM_ID
{
  ME  = 0, // Intel(R) Management Engine (Intel(R) ME)
  SEC = 1,
  CSE = 2,
  INVALID_PLATFORM_ID = -1
};

typedef struct {
  EFI_GUID  ClientGuid;
  UINT8     ClientId;                     // ME address, 0 also indicates the client not found
  UINT8     HostAddress;
  UINT32    MaxMessageLength;
  BOOLEAN   HaveFlowControl;
  BOOLEAN   Connected;
  BOOLEAN   EnFirstFlowControl;
} ME_CLIENT_PROPERTIES;

//
// Instance
//
STATIC ME_CLIENT_PROPERTIES                      MeClients[] = {
  {{0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}}, 0, 0, 0, FALSE, FALSE, FALSE}, // IVM_CLIENT
  {{0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}}, 0, 0, 0, FALSE, FALSE, FALSE}, // SDM_CLIENT
  {{0, 0, 0, {0, 0, 0, 0, 0, 0, 0, 0}}, 0, 0, 0, FALSE, FALSE, FALSE}  // RTM_CLIENT
};

STATIC HECI_PROTOCOL                             *mHeciProtocol = NULL;    // MEI internal used

/**
  Read the flow control buffer as one
  is required before we can send a request message to the ME.
  Typically the ME will send one after we have sent a request message.
  This function allows us to request one if we have not received one.

  @param[in] MeClient             The pointer to the ME property.

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
ReadFlowControl (
  IN ME_CLIENT_PROPERTIES *MeClient
  )
{
  EFI_STATUS              Status;
  HBM_FLOW_CONTROL        FlowControlMessage;
  UINT32                  Length;
  UINT8                   i;
  UINTN                   MaxClientCount;
  BOOLEAN                 Cont;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "ReadFlowControl(ClientId: %x): HaveFlowControl: %x\n", MeClient->ClientId ,MeClient->HaveFlowControl));

  if (MeClient->HostAddress == 0) {
    //
    // We can send Flow control message only if MeiClientConnect has done.
    // (MeClient->HostAddress will be set after MeiClientConnect is finished.)
    //
    DEBUG_BEIHAI_LIB ((DEBUG_WARN, "ReadFlowControl skip since HostAddress has not connected.\n"));
    return EFI_SUCCESS;
  }

  if (MeClient->EnFirstFlowControl == FALSE) {
    DEBUG_BEIHAI_LIB ((DEBUG_WARN, "ReadFlowControl skip since it's first time.\n"));
    MeClient->EnFirstFlowControl = TRUE;
    return EFI_SUCCESS;
  }

  if (MeClient->HaveFlowControl) {
    return EFI_SUCCESS;
  }

  Cont = TRUE;
  do {

    //
    // Ask ME for flow control buffer
    //
    Length = sizeof (HBM_FLOW_CONTROL);
    Status = mHeciProtocol->ReadMsg (
                              JHI_MEI_HECI_DEVICE,
                              BLOCKING,
                              (UINT32 *) &FlowControlMessage,
                              &Length
                              );
    if (EFI_ERROR (Status)) {
      DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Unable to get Flow Control Message - %r\n", Status));
      return Status;
    }

    if (FlowControlMessage.Command.Fields.Command != FLOW_CONTROL) { //FLOW_CONTROL_CMD
      DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Not flow control command: %x\n", FlowControlMessage.Command.Fields.Command));
      return EFI_NOT_READY;
    }

    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Got ME Flow Control message via Request for %x\n", FlowControlMessage.MeAddress));

    MaxClientCount = sizeof (MeClients) /sizeof (MeClients[0]);
    ASSERT (MaxClientCount != 0);

    for (i = 0; i < MaxClientCount; i++) {
      if (FlowControlMessage.MeAddress == MeClients[i].ClientId) {
        MeClients[i].HaveFlowControl = TRUE;
        Cont = FALSE;
      }
    }
  } while (Cont);

  return Status;
}

/**
  Before we wait for a message from the ME, we need to notify the ME
  that we have a buffer ready. Since our code already has one, this is really
  a clear to send message to the ME

  @param[in] MeClient             The pointer to the ME property.

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
WriteFlowControl (
  IN ME_CLIENT_PROPERTIES *MeClient
  )
{
  EFI_STATUS              Status;
  HBM_FLOW_CONTROL        FlowControlMessage;
  UINT32                  Length;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "WriteFlowControl(ClientId: %x)\n", MeClient->ClientId));
  if (MeClient->HostAddress == 0) {
    //
    // We can send Flow control message only if MeiClientConnect has done.
    // (MeClient->HostAddress will be set after MeiClientConnect is finished.)
    //
    DEBUG_BEIHAI_LIB ((DEBUG_WARN, "WriteFlowControl skip since HostAddress has not connected.\n"));
    return EFI_SUCCESS;
  }

  ZeroMem (&FlowControlMessage, sizeof (HBM_FLOW_CONTROL));
  FlowControlMessage.Command.Fields.Command = FLOW_CONTROL;//FLOW_CONTROL_CMD;
  FlowControlMessage.Command.Fields.IsResponse = 0;
  FlowControlMessage.MeAddress = MeClient->ClientId;
  FlowControlMessage.HostAddress = MeClient->HostAddress;

  Length = sizeof (HBM_FLOW_CONTROL);

  //
  // Send Flow Control Ready to ME
  //
  Status = mHeciProtocol->SendMsg (
                            JHI_MEI_HECI_DEVICE,
                            (UINT32 *) &FlowControlMessage,
                            Length,
                            HBM_PROTOCOL_ADDRESS,
                            HBM_PROTOCOL_ADDRESS
                            );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Unable to send Client Read Flow Control Message to %d - %r\n", MeClient->ClientId, Status));
    return Status;
  }

  return Status;
}

/**
  Wait for a message from the ME FWU Client.
  Because the ME could be busy, we do a read and if receive a timeout,
  repeat the operation 2 additional times.
  Because we can receive a flow control message from the ME out of order,
  we check if the message received is a flow control.  If it is, we update
  the flow control variable and then re-issue the read request.

  @param[in] MeClient             The pointer to the ME property.

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
ReadMessageWithFlow (
  IN UINT8            *Buffer,
  IN OUT UINT32       *Length
  )
{
  EFI_STATUS          Status;
  HBM_FLOW_CONTROL    *FlowControlMessage;
  UINT32              Retry;
  UINT32              i;
  UINTN               MaxClientCount;
  BOOLEAN             Cont;
  UINT8               *Data;
  UINT8               *TempBuf;
  UINT32              TempBufSize;
  UINT32              MsgLength;
  UINT32              ExpectedLen;
  BOOLEAN             FlowControlMsg;


  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "ReadMessageWithFlow (Length: %x)\n", *Length));
  if (mHeciProtocol == NULL) {
    DEBUG_BEIHAI_LIB ((DEBUG_WARN, "ReadMessageWithFlow fail, not initialized\n"));
    return EFI_NOT_READY;
  }

  MaxClientCount = sizeof (MeClients) /sizeof (MeClients[0]);
  ASSERT (MaxClientCount != 0);

  Retry = BEIHAI_MAX_RETRY; // Retry x times with a 5 second timeout
  Cont = FALSE;
  Data = Buffer;
  MsgLength = *Length;
  TempBuf = NULL;
  TempBufSize = MEIRCV_MINLEN;
  ExpectedLen = *Length;

  do {
    Status = mHeciProtocol->ReadMsg (
                              JHI_MEI_HECI_DEVICE,
                              NON_BLOCKING,
                              (UINT32 *) Data,
                              &MsgLength
                              );
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "After ReadMsg, MsgLength: %x, Status: %r\n", MsgLength, Status));
    switch (Status) {
      case EFI_SUCCESS:
        Cont = FALSE;

        //
        // successful
        //
        FlowControlMsg = FALSE;
        FlowControlMessage = (HBM_FLOW_CONTROL *) Data;
        DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Check for flow control message: Command: %x\n", FlowControlMessage->Command.Fields.Command));
        if ((FlowControlMessage->Command.Fields.Command == FLOW_CONTROL) && //FLOW_CONTROL_CMD
            (FlowControlMessage->HostAddress == CLIENT_HOST_ADDRESS)) {
          DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, " Command: %x\n", FlowControlMessage->Command.Data));
          DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, " HostAddress: %x\n", FlowControlMessage->HostAddress));
          DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, " MeAddress: %x\n", FlowControlMessage->MeAddress));
          for (i = 0; i < MaxClientCount; i++) {
            if (FlowControlMessage->MeAddress == MeClients[i].ClientId) {
              DEBUG_BEIHAI_LIB ((DEBUG_INFO, "This is a flow control message\n"));
              DEBUG_BEIHAI_LIB ((DEBUG_INFO, "MeClients[%x] HaveFlowControl to TRUE\n", i));
              MeClients[i].HaveFlowControl = TRUE;
              FlowControlMsg = TRUE;
              break;
            }
          }
        }

        if (FlowControlMsg == TRUE) {
          *Length = 0;
        } else {
          if (MsgLength > ExpectedLen) {
            DEBUG_BEIHAI_LIB ((DEBUG_INFO, "ReadMessageWithFlow: received length(%x) > expected length(%x), truncate it !!!\n", MsgLength, ExpectedLen));
            *Length = ExpectedLen;
          } else {
            *Length = MsgLength;
          }
        }
        break;

      case EFI_BUFFER_TOO_SMALL:
        DEBUG_BEIHAI_LIB ((DEBUG_WARN, "Buff to small, reallocate temp buff (TempBufSize: %x, MsgLength: %x)\n", TempBufSize, MsgLength));
        if (TempBuf != NULL) {
          FreePool (TempBuf);
        }
        TempBuf = AllocateZeroPool (TempBufSize);

        //
        // We can't use MsgLength because it will be 0.
        //
        if (TempBuf == NULL) {
          DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "No resource for temp buff !!!\n"));
          ASSERT (FALSE);
          return EFI_OUT_OF_RESOURCES;
        }
        Data = TempBuf;
        MsgLength = TempBufSize;
        TempBufSize *= 2;
        Cont = TRUE;  // let's retry
        break;

      case EFI_TIMEOUT:
        //
        // Only apply retry timeout if we got EFI_TIMEOUT
        //
        Retry--;
        DEBUG_BEIHAI_LIB ((DEBUG_WARN, "ReadMsg timeout, Retry: %x\n", Retry));
        if (Retry != 0) {
          MsgLength = *Length;
          Cont = TRUE;
        } else {
          Cont = FALSE;
        }
        break;
      case EFI_NO_RESPONSE:
        DEBUG_BEIHAI_LIB((DEBUG_WARN, "."));
        MsgLength = *Length;
        Cont = TRUE;
        break;
      default:
        DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Unable to Read Message - %r\n", Status));
        Cont = FALSE;
        break;
    }
  } while (Cont);

  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "ReadMessageWithFlow fail: %r\n", Status));
    return Status;
  }

  if (TempBuf != NULL) {
    //
    // Received length (MsgLength) large than expected
    //
    CopyMem (Buffer, TempBuf, *Length);
    FreePool (TempBuf);
  }
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "ReadMessageWithFlow done, new Length: %x\n", *Length));

  return Status;
}

/**
  Send a message to the ME FWU Client.
  A Flow Control response is required from the ME before we can send a message.
  Thus if we have not received one, send a request for one.

  @param[in] MeClient             The pointer to the ME property.

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
SendMessageWithFlow (
  IN ME_CLIENT_PROPERTIES *MeClient,
  IN UINT8                *Buffer,
  IN UINT32               Length
  )
{
  EFI_STATUS              Status;
  UINT32                  Retry;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "SendMessageWithFlow (Length: %x)\n", Length));

  if (Length > MeClient->MaxMessageLength) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "SendMessageWithFlow fail since Length > MaxMessageLength\n"));
    return EFI_BUFFER_TOO_SMALL;
  }

  Status = ReadFlowControl (MeClient);
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_WARN, "SendMessageWithFlow fail, ReadFlowControl error: %r\n", Status));
  }

  Retry = BEIHAI_MAX_RETRY; // Retry x times with 5 second timeout on each message
  do {
    //
    // Send message to Local FW Update Client
    //
    Status = mHeciProtocol->SendMsg (
                              JHI_MEI_HECI_DEVICE,
                              (UINT32 *) Buffer,
                              Length,
                              MeClient->HostAddress,
                              MeClient->ClientId
                              );
    if (Status != EFI_TIMEOUT) {
      if (EFI_ERROR (Status)) {
        DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Unable send message to Client - %r\n", Status));
        return Status;
      }
    }

    if (!EFI_ERROR (Status)) {
      // Everything okay - message sent
      break;
    }

    Retry--;
  } while (Retry);

  if (Status == EFI_TIMEOUT) {
    DEBUG_BEIHAI_LIB ((DEBUG_WARN, "Unable to send Message - %r\n", Status));
  }


  MeClient->HaveFlowControl = FALSE;
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Reset HaveFlowControl to FALSE\n"));

  return Status;
}

/**
  Ask the ME for a list of dynamic clients.
  For each dynamic client returned in the array, ask the client for
  the properties and if the FW Update GUID is found, we have our
  client.  Each client will have its own MeAddress and HostAddress that is
  required for HECI messages to that client.

  @param[in] MeClient             The pointer to the ME property.

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
EnumClients (
  VOID
  )
{
  EFI_STATUS                          Status;
  HBM_HOST_ENUMERATION_REQUEST        EnumRequestMessage;
  HBM_HOST_ENUMERATION_RESPONSE       EnumResponse;
  UINT8                               i,j,k;
  UINT32                              Length;
  HBM_HOST_CLIENT_PROPERTIES_REQUEST  ClientPropertiesMessage;
  HBM_HOST_CLIENT_PROPERTIES_RESPONSE ClientPropertiesResponse;
  UINTN                               MaxClientCount;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "EnumClients\n"));
  EnumRequestMessage.Command.Fields.IsResponse = 0;
  EnumRequestMessage.Command.Fields.Command = HOST_ENUMERATE_REQUEST;// HOST_ENUM_REQ_CMD;
  EnumRequestMessage.Reserved[0] = 0;
  EnumRequestMessage.Reserved[1] = 0;
  EnumRequestMessage.Reserved[2] = 0;

  Length = sizeof (HBM_HOST_ENUMERATION_REQUEST);

  //
  // Send Host Enumeration to ME
  //
  Status = mHeciProtocol->SendMsg (
                            JHI_MEI_HECI_DEVICE,
                            (UINT32 *) &EnumRequestMessage,
                            Length,
                            HBM_PROTOCOL_ADDRESS,
                            HBM_PROTOCOL_ADDRESS
                            );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Unable to send Host Enumeration Request message - %r\n", Status));
    return Status;
  }

  //
  // Read response
  //
  Length = sizeof (HBM_HOST_ENUMERATION_RESPONSE);
  Status = mHeciProtocol->ReadMsg (
                            JHI_MEI_HECI_DEVICE,
                            BLOCKING,
                            (UINT32 *) &EnumResponse,
                            &Length
                            );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Unable to read Host Enumeration Response - %r\n", Status));
    return Status;
  }

  MaxClientCount = sizeof (MeClients) /sizeof (MeClients[0]);
  ASSERT (MaxClientCount != 0);
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "EnumClients, MaxClientCount: %x\n", MaxClientCount));
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "ValidAddresses\n"));
  DbgRawdataDump (EnumResponse.ValidAddresses, sizeof (EnumResponse.ValidAddresses));

  //
  // Find the Client
  //
  for (i = 0; i < sizeof (EnumResponse.ValidAddresses); i ++) {
    for (j = 0; j < 8; j ++) {
      if ((EnumResponse.ValidAddresses[i] & (1 << j)) != 0) {
        ClientPropertiesMessage.Command.Fields.IsResponse = 0;
        ClientPropertiesMessage.Command.Fields.Command = HOST_CLIENT_PROPERTIES_REQUEST;//HOST_CLIENT_PROPERTIES_REQ_CMD;
        ClientPropertiesMessage.Address = (i*8) +j;
        ClientPropertiesMessage.Reserved[0] = 0;
        ClientPropertiesMessage.Reserved[1] = 0;

        Length = sizeof (HBM_HOST_CLIENT_PROPERTIES_REQUEST);

        //
        // Send Client Properties Request to ME
        //
        Status = mHeciProtocol->SendMsg (
                                  JHI_MEI_HECI_DEVICE,
                                  (UINT32 *) &ClientPropertiesMessage,
                                  Length,
                                  HBM_PROTOCOL_ADDRESS,
                                  HBM_PROTOCOL_ADDRESS
                                  );
        if (EFI_ERROR (Status)) {
          DEBUG_BEIHAI_LIB ((DEBUG_WARN, "Unable to send Client Properties message to %d - %r\n", i, Status));
          break;
        }

        //
        // Read response
        //
        Length = sizeof (HBM_HOST_CLIENT_PROPERTIES_RESPONSE);
        Status = mHeciProtocol->ReadMsg (
                                  JHI_MEI_HECI_DEVICE,
                                  BLOCKING,
                                  (UINT32 *) &ClientPropertiesResponse,
                                  &Length
                                  );
        if (EFI_ERROR (Status)) {
          DEBUG_BEIHAI_LIB ((DEBUG_WARN, "Unable to read Host Enumeration Response - %r\n", Status));
          break;
        }

        if (!ClientPropertiesResponse.Status) {
          DEBUG_BEIHAI_LIB ((DEBUG_INFO, "ME client [i: %x][j: %x]\n",     i, j));
          DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  ProtocolName: %g\n",           ClientPropertiesResponse.ClientProperties.ProtocolName));
          DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  ProtocolVersion: %x\n",        ClientPropertiesResponse.ClientProperties.ProtocolVersion));
          DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  MaxNumberOfConnections: %x\n", ClientPropertiesResponse.ClientProperties.MaxNumberOfConnections));
          DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  FixedAddress: %x\n",           ClientPropertiesResponse.ClientProperties.FixedAddress));
          DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  SingleReceiveBuffer: %x\n",    ClientPropertiesResponse.ClientProperties.SingleReceiveBuffer));
          DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  MaxMessageLength: %x\n",       ClientPropertiesResponse.ClientProperties.MaxMessageLength));

          for (k = 0; k < MaxClientCount; k++) {
            if (
                 (MeClients[k].ClientId == 0) &&
                 (CompareMem(&ClientPropertiesResponse.ClientProperties.ProtocolName, &MeClients[k].ClientGuid, 16) == 0)  // Compre GUID
                 ) {

              MeClients[k].MaxMessageLength = ClientPropertiesResponse.ClientProperties.MaxMessageLength;
              //
              // Need to reduce the size of the data sent to include:
              //  1) HECI Message Header
              //  2) Flow Control Message and HECI Message Header
              //
              // Testing revealed that occassionally the Flow Control Message will be put into the same HECI buffer
              // from the host and thus iff the data is not restricted in size by the additional bytes, update data
              // will get corrupted.
              //
              MeClients[k].MaxMessageLength -= HECI_HEADER_SIZE;
              MeClients[k].ClientId = ClientPropertiesResponse.Address;

              DEBUG_BEIHAI_LIB ((DEBUG_INFO, "!!! Found Client[%x] !!!\n", k));
              DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  ClientId: %x\n", MeClients[k].ClientId));
              DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  MaxMessageLength: %x\n", MeClients[k].MaxMessageLength));
            }
          }
        }
      }
    }
  }

  for (k = 0; k < MaxClientCount; k++) {
    if (!MeClients[k].ClientId) {
      DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Can't find ME Client[%x] - exiting\n", k));
      return EFI_NOT_FOUND;
    }
  }

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "EnumClients done, Status: %r\n", Status));
  return Status;
}

/**
  Initialize ME interface

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
MeiInit (VOID)
{
  EFI_STATUS    Status;
  HECI_PROTOCOL *Heci;
  UINT32        MeMode;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "MeiInit\n"));
  Status = gBS->LocateProtocol (
                  &gHeciProtocolGuid,
                  NULL,
                  (VOID **) &Heci
                  );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiInit fail, can't find HECI protocol: %r.\n", Status));
    return Status;
  }

  Status = Heci->GetMeMode (&MeMode);
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiInit fail, GetMeMode error: %r.\n", Status));
    return Status;
  }

  if (MeMode != ME_MODE_NORMAL) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiInit fail, MeMode: %x is invalid.\n", MeMode));
    return EFI_DEVICE_ERROR;
  }

  Status = Heci->ResetHeci (JHI_MEI_HECI_DEVICE);
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiInit fail, ResetHeci error: %r.\n", Status));
    return Status;
  }

  //
  // Initialize module member
  //
  mHeciProtocol = Heci;
  ZeroMem (MeClients, sizeof (MeClients));
  CopyMem (&MeClients[IVM_CLIENT].ClientGuid, &gIvmProtocolGuid, sizeof (EFI_GUID));
  CopyMem (&MeClients[SDM_CLIENT].ClientGuid, &gSdmProtocolGuid, sizeof (EFI_GUID));
  CopyMem (&MeClients[RTM_CLIENT].ClientGuid, &gRtmProtocolGuid, sizeof (EFI_GUID));

  //
  // Enumeration ME client
  //
  Status = EnumClients ();
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiInit fail, EnumClients error: %r.\n", Status));
    return Status;
  }

  return EFI_SUCCESS;
}

/**
  De-initialize ME interface

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
MeiDeinit (VOID)
{
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "MeiDeinit\n"));

  if (mHeciProtocol == NULL) {
    DEBUG_BEIHAI_LIB ((DEBUG_WARN, "MeiDeinit fail, not initialized\n"));
    return EFI_NOT_READY;
  }

  return EFI_SUCCESS;
}

/**
  Connect to the enumerated client that supports FW Update
  A valid client ID is required for this routine

  @param[in] MeClient             The pointer to the ME property.

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
MeiClientConnect (
  IN ME_CLIENT_ID MeClientId
  )
{
  EFI_STATUS                          Status;
  HBM_CLIENT_CONNECT_REQUEST          ClientConnectRequest;
  HBM_CLIENT_CONNECT_RESPONSE         *ClientConnectResponse;
  UINT32                              Length;
  HBM_CLIENT_CONNECT_RESPONSE         Buffer;
  ME_CLIENT_PROPERTIES                *MeClient;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "MeiClientConnect, MeClientId: %x\n", MeClientId));
  if (MeClientId >= SVM_CLIENT) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiClientConnect error, MeClientId overflow.\n"));
    return EFI_INVALID_PARAMETER;
  }

  MeClient = &MeClients[MeClientId];

  ClientConnectRequest.MeAddress = MeClient->ClientId;
  ClientConnectRequest.HostAddress = CLIENT_HOST_ADDRESS;
  ClientConnectRequest.Command.Fields.Command = CLIENT_CONNECT_REQUEST;//CLIENT_CONNECT_REQ_CMD;
  ClientConnectRequest.Command.Fields.IsResponse = 0;
  ClientConnectRequest.Reserved = 0;

  Length = sizeof (HBM_CLIENT_CONNECT_REQUEST);

  //
  // Send Client Connect Request to ME
  //
  Status = mHeciProtocol->SendMsg (
                            JHI_MEI_HECI_DEVICE,
                            (UINT32 *) &ClientConnectRequest,
                            Length,
                            HBM_PROTOCOL_ADDRESS,
                            HBM_PROTOCOL_ADDRESS
                            );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Unable to send Client Connect Request message to %d - %r\n", MeClient->ClientId, Status));
    return Status;
  }

  Status = MeiRecv (MeClientId, (UINT32 *)&Buffer, &Length);
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Unable to read Client Connection Response - %r\n", Status));
    return Status;
  }

  ClientConnectResponse = (HBM_CLIENT_CONNECT_RESPONSE *)&Buffer;
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "HBM_CLIENT_CONNECT_RESPONSE\n"));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  Command: %x\n", ClientConnectResponse->Command.Data));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  MEAddress: %x\n", ClientConnectResponse->MeAddress));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  HostAddress: %x\n", ClientConnectResponse->HostAddress));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "  Status: %x\n", ClientConnectResponse->Status));
  if (ClientConnectResponse->Status) {
    DEBUG_BEIHAI_LIB ((DEBUG_WARN, "Unable to connect to client - %r\n", ClientConnectResponse->Status));
  }
  Status = ClientConnectResponse->Status;

  MeClient->Connected = TRUE;
  MeClient->HostAddress = ClientConnectResponse->HostAddress;
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "MeiClientConnect done, Status: %r (MeClientId: %x, HostAddress: %x, MeAddress: %x)\n",
                     Status, MeClientId, MeClient->HostAddress, MeClient->ClientId));

  return Status;

}

/**
  Disconnect from the connected client

  @param[in] MeClient             The pointer to the ME property.

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
MeiClientDisconnect (
  IN ME_CLIENT_ID MeClientId
  )
{
  EFI_STATUS                          Status;
  HBM_CLIENT_DISCONNECT_REQUEST       ClientDisconnectRequest;
  HBM_CLIENT_DISCONNECT_RESPONSE      ClientDisconnectResponse;
  UINT32                              Length;
  UINT32                              Buff[2];
  ME_CLIENT_PROPERTIES                *MeClient;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "MeiClientDisconnect, MeClientId: %x\n", MeClientId));
  if (MeClientId >= SVM_CLIENT) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiClientDisconnect error, MeClientId overflow.\n"));
    return EFI_INVALID_PARAMETER;
  }

  MeClient = &MeClients[MeClientId];

  if (MeClient->Connected == FALSE) {
    return EFI_SUCCESS;
  }

  ClientDisconnectRequest.MeAddress = MeClient->ClientId;
  ClientDisconnectRequest.HostAddress = CLIENT_HOST_ADDRESS;
  ClientDisconnectRequest.Command.Fields.Command = CLIENT_DISCONNECT_REQUEST;  //CLIENT_DISCONNECT_REQ_CMD;
  ClientDisconnectRequest.Command.Fields.IsResponse = 0;
  ClientDisconnectRequest.Reserved = 0;

  Length = sizeof (HBM_CLIENT_DISCONNECT_REQUEST);

  //
  // Send Client Disconnect Request to ME
  //
  Status = mHeciProtocol->SendMsg (
                            JHI_MEI_HECI_DEVICE,
                            (UINT32 *) &ClientDisconnectRequest,
                            Length,
                            HBM_PROTOCOL_ADDRESS,
                            HBM_PROTOCOL_ADDRESS
                            );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Unable to send Client Disconnect Request message to %d - %r\n", MeClient->ClientId, Status));
    return Status;
  }

  //
  // Read response - not sure why response is 8 bytes instead of 4, so we use
  // use cheat buffer
  //
  Length = sizeof (Buff);
  Status = mHeciProtocol->ReadMsg (
                            JHI_MEI_HECI_DEVICE,
                            BLOCKING,
                            (UINT32 *) Buff,
                            &Length
                            );
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "Unable to read Client Disconnect Response - %r\n", Status));
    return Status;
  }

  CopyMem (&ClientDisconnectResponse, Buff, sizeof (HBM_CLIENT_DISCONNECT_RESPONSE));

  if (ClientDisconnectResponse.Status) {
    DEBUG_BEIHAI_LIB ((DEBUG_WARN, "Unable to disconnect from Client - %x\n", ClientDisconnectResponse.Status));
  } else {
    MeClient->Connected = FALSE;
    DEBUG_BEIHAI_LIB ((DEBUG_INFO, "Disconnected from client\n"));
  }
  Status = ClientDisconnectResponse.Status;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "MeiClientDisconnect done, Status: %r (MeClientId: %x, HostAddress: %x, MeAddress: %x)\n",
                     Status, MeClientId, MeClient->HostAddress, MeClient->ClientId));
  return Status;
}

/**
  Send data by ME interface

  @param[in] MeClient             The ME client identifier.
  @param[in] Buffer               The pointer to the buffer for transition.
  @param[in] Length               The length of buffer.

  @retval EFI_SUCCESS             Receive data successfully.
  @retval others                  Receive data failed with error code.
**/
EFI_STATUS
MeiSend (
  IN ME_CLIENT_ID MeClientId,
  IN VOID         *Buffer,
  IN UINT32       Length
  )
{
  EFI_STATUS      Status;
  UINT32          SizeLeft;
  UINT32          SizeTransfer;
  UINT8           *Data;

  if (MeClientId >= SVM_CLIENT) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiSend error, MeClientId overflow.\n"));
    return EFI_INVALID_PARAMETER;
  }

#if EN_MEI_TXF_SPEEDUP == 0
  UINT32 AlignedPkgSize;

  AlignedPkgSize = MAKE_ALIEN_SIZE (MeClients[MeClientId].MaxMessageLength);
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> MeiSend (Length: %x, AlignedPkgSize: %x)\n", Length, AlignedPkgSize));
  if (AlignedPkgSize == 0) {
    AlignedPkgSize = MAX_HECIMSG_SIZE;
  }
#else
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> MeiSend (Length: %x)\n", Length));
#endif

  Status = EFI_INVALID_PARAMETER;
  if (Length > 0) {
    Data = (UINT8 *) Buffer;
    SizeLeft = Length;
    while (SizeLeft > 0) {
#if EN_MEI_TXF_SPEEDUP == 0
      SizeTransfer = min (AlignedPkgSize, SizeLeft);
#else
      SizeTransfer = min (MAX_TXRX_LENGTH, SizeLeft);
#endif

      Status = SendMessageWithFlow (&MeClients[MeClientId], Data, SizeTransfer);
      if (EFI_ERROR (Status)) {
        DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiSend fail, SendMessageWithFlow error: %r\n", Status));
        return Status;
      }

      Data += SizeTransfer;
      SizeLeft -= SizeTransfer;
    }
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "<<< MeiSend (Length: %x) done, Status: %r\n", Length, Status));
  return Status;
}

/**
  Receive data by ME interface

  @param[in] MeClient             The ME client identifier.
  @param[out] Buffer              The pointer to the buffer for transition.
  @param[in] Length               The length of buffer.

  @retval EFI_SUCCESS             Receive data successfully.
  @retval others                  Receive data failed with error code.
**/
EFI_STATUS
MeiRecv (
  IN ME_CLIENT_ID MeClientId,
  OUT VOID        *Buffer,
  IN UINT32       *Length
  )
{
  EFI_STATUS      Status;
  UINT32          SizeLeft;
  UINT32          SizeTransfer;
  UINT32          SizeTotalTansfer;
  UINT8           *Data;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, ">>> MeiRecv (Length: %x)\n", *Length));
  if (MeClientId >= SVM_CLIENT) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiRecv error, MeClientId overflow.\n"));
    return EFI_INVALID_PARAMETER;
  }

  Status = EFI_SUCCESS;
  SizeTotalTansfer = 0;


  Data = (UINT8 *) Buffer;
  SizeLeft = *Length;
  while (SizeLeft > 0) {
#if EN_MEI_TXF_SPEEDUP == 0
    SizeTransfer = min (MAX_TXRX_LENGTH, SizeLeft);
#else
    SizeTransfer = SizeLeft;
#endif

    ///
    /// Before receiving, we send a flow control to the ME indicating we have a buffer
    ///
    if (MeClientId != NO_CLIENT) {
      Status = WriteFlowControl (&MeClients[MeClientId]);
      if (EFI_ERROR (Status)) {
        DEBUG_BEIHAI_LIB ((DEBUG_WARN, "MeiRecv fail, WriteFlowControl error: %r\n", Status));
        goto done;
      }
    }

    Status = ReadMessageWithFlow (Data, &SizeTransfer);
    if (EFI_ERROR (Status)) {
      DEBUG_BEIHAI_LIB ((DEBUG_WARN, "MeiRecv fail, ReadMessageWithFlow error: %r\n", Status));
      goto done;
    }

    Data += SizeTransfer;
    SizeLeft -= SizeTransfer;
    SizeTotalTansfer += SizeTransfer;
  }

done:
  *Length = SizeTotalTansfer;
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "<<< MeiRecv (Length: %x) done, Status: %r\n", *Length, Status));

  return Status;
}

/**
  Get firmware info

  @param[in] MeInfo               The pointer to the information buffer.

  @retval EFI_SUCCESS             Get firmware info successfully.
  @retval EFI_UNSUPPORTED         Get firmware info failed with error code.
**/
STATIC
EFI_STATUS
MeiGetFwInfo (
  OUT ME_INFO *MeInfo
  )
{
  ME_BIOS_PAYLOAD_HOB       *MbpHob;

  MbpHob = NULL;
  //
  // Get Mbp Protocol
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);

  if (MbpHob == NULL) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiGetFwInfo fail, HeciGetFwVersionMsg error.\n"));
    return EFI_UNSUPPORTED;
  }

  MeInfo->Major  = (UINT16) MbpHob->MeBiosPayload.FwVersionName.MajorVersion;
  MeInfo->Minor  = (UINT16) MbpHob->MeBiosPayload.FwVersionName.MinorVersion;
  MeInfo->Hotfix = (UINT16) MbpHob->MeBiosPayload.FwVersionName.HotfixVersion;
  MeInfo->Build  = (UINT16) MbpHob->MeBiosPayload.FwVersionName.BuildVersion;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " MajorVersion:   %02x\n", MeInfo->Major));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " MinorVersion:   %02x\n", MeInfo->Minor));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " HotfixVersion:  %02x\n", MeInfo->Hotfix));
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, " BuildVersion:   %02x\n", MeInfo->Build));

  return EFI_SUCCESS;
}

/**
  Get platform type

  @param[in] MeInfo               The pointer to the information buffer.

  @retval EFI_SUCCESS             Get platform type successfully.
  @retval others                  Get platform type failed with error code.
**/
STATIC
EFI_STATUS
MeiGetPlatformInfo (
  OUT ME_INFO *MeInfo
  )
{
  ME_BIOS_PAYLOAD_HOB       *MbpHob;

  MbpHob = NULL;
  //
  // Get Mbp Protocol
  //
  MbpHob = GetFirstGuidHob (&gMeBiosPayloadHobGuid);

  if ((MbpHob == NULL) || (MbpHob->MeBiosPayload.FwPlatType.Available != 1)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiGetPlatformInfo fail, MeiCheckPlatformType error.\n"));
    return EFI_UNSUPPORTED;
  }

  //
  // Refer to ME_PLATFORM_TYPE for more details
  //
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, " SuperSku:                 %01x\n", MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.SuperSku));
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, " Reserved:                 %01x\n", MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.Reserved));
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, " IntelMeFwImageType:       %01x\n", MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.IntelMeFwImageType));
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, " PlatformBrand:            %01x\n", MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.PlatformBrand));
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, " Reserved1:                %04x\n", MbpHob->MeBiosPayload.FwPlatType.RuleData.Fields.Reserved1));
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "\n"));

  MeInfo->MeFwType = CSE;

  return EFI_SUCCESS;
}

/**
  Get information of ME interface

  @param[in] MeInfo               The pointer to the information buffer.

  @retval EFI_SUCCESS             Get information successfully.
  @retval others                  Get information failed with error code.
**/
EFI_STATUS
MeiGetInfo (
  OUT ME_INFO *MeInfo
  )
{
  EFI_STATUS                Status;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "MeiGetInfo\n"));

  Status = MeiGetFwInfo (MeInfo);
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiGetInfo fail, MeiGetFwInfo error: %r\n", Status));
    return Status;
  }

  Status = MeiGetPlatformInfo (MeInfo);
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "MeiGetInfo fail, MeiGetPlatformInfo error: %r\n", Status));
    return Status;
  }

  return Status;
}


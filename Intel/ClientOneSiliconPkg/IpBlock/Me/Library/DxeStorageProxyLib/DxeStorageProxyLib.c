/** @file
  DXE Storage Proxy Library.

  Note: This library may be refactored so that it is compatible with DXE and SMM with relatively minor changes.
        This is currently not done since an SMM implementation is not required.

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
#include <Base.h>
#include <CoreBiosMsg.h>
#include <Register/HeciRegs.h>
#include <Uefi/UefiBaseType.h>

#include <Library/BaseMemoryLib.h>
#include <Library/BlockIoWrapperLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/RpmbLib.h>
#include <Library/StorageProxyLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Protocol/HeciProtocol.h>
#include <Protocol/StorageProxyControl.h>
#include <HeciContextLib.h>

STATIC BOOLEAN                         mStorageProxyStopRequested;
STATIC HECI_PROTOCOL                   *mHeciProtocol;
STATIC STORAGE_PROXY_CONTROL_PROTOCOL  *mStorageProxyControlProtocol;

/**
  Locates the HECI protocol and sets the module HECI protocol pointer.

  @retval     EFI_SUCCESS            The HECI protocol was found.
  @retval     EFI_INVALID_PARAMETER  Invalid parameter.
  @retval     EFI_NOT_FOUND          The protocol interface was not found.

**/
EFI_STATUS
EFIAPI
LocateHeciProtocol (
  VOID
  )
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;
  if (mHeciProtocol == NULL) {
    Status = gBS->LocateProtocol (
                    &gHeciProtocolGuid,
                    NULL,
                    (VOID **) &mHeciProtocol
                    );
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Storage Proxy: Could not locate the HECI protocol.\n"));
      ASSERT_EFI_ERROR (Status);
    }
  }

  return Status;
}

/**
  Locates the Storage Proxy Control protocol and sets the module Storage Proxy Control protocol pointer.

  @retval     EFI_SUCCESS            The Storage Proxy Control protocol was found.
  @retval     EFI_INVALID_PARAMETER  Invalid parameter.
  @retval     EFI_NOT_FOUND          The protocol interface was not found.

**/
EFI_STATUS
EFIAPI
LocateStorageProxyControlProtocol (
  VOID
  )
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;
  if (mStorageProxyControlProtocol == NULL) {
    Status = gBS->LocateProtocol (
                    &gStorageProxyControlProtocolGuid,
                    NULL,
                    (VOID **) &mStorageProxyControlProtocol
                    );
  }

  return Status;
}

/**
  Locates the HECI protocol and sets the module HECI protocol pointer.

  @param[in]  StorageProxyHeader     A pointer to a structure of type STORAGE_PROXY_MESSAGE_HEADER.
  @param[in]  ExpectedCommand        The expected STORAGE_PROXY_COMMAND in the response message.

  @retval     TRUE                   The response header is valid.
  @retval     FALSE                  The response header is invalid.

**/
BOOLEAN
EFIAPI
IsStorageProxyResponseHeaderValid (
  IN CONST  STORAGE_PROXY_MESSAGE_HEADER  *StorageProxyHeader,
  IN        STORAGE_PROXY_COMMAND         ExpectedCommand
  )
{
  if (StorageProxyHeader == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy header checked for validity is invalid.\n"));
    ASSERT (StorageProxyHeader != NULL);
    return FALSE;
  } else if (StorageProxyHeader->Fields.Status != STORAGE_PROXY_STATUS_SUCCESS) {
    DEBUG ((
      DEBUG_ERROR,
      "Storage Proxy: The storage proxy response status is unsuccessful. Response = %d.\n",
      StorageProxyHeader->Fields.Status
      ));
    return FALSE;
  }

  return ((StorageProxyHeader->Fields.Command == (UINT32) ExpectedCommand) && (StorageProxyHeader->Fields.IsResponse == 1));
}

/**
  Determines if fundamental requirements are met to interact using storage proxy messages with CSME.

  @retval     TRUE            Basic requirements are met for a storage proxy transaction.
  @retval     FALSE           The HECI protocol could not be found or the HECI device is not in a normal state.
**/
BOOLEAN
EFIAPI
IsReadyForTransaction (
  VOID
  )
{
  EFI_STATUS    Status;
  UINT32        MeMode;

  Status = LocateHeciProtocol ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: Could not locate the HECI protocol.\n"));
    return FALSE;
  }

  Status = mHeciProtocol->GetMeMode (&MeMode);
  if (EFI_ERROR (Status) || (MeMode != ME_MODE_NORMAL)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: Error getting ME mode or mode is not normal. Status = %r.\n", Status));
    return FALSE;
  }

  return TRUE;
}

/**
  Checks if a critical Storage Proxy operation is in progress.

  @retval         TRUE        The storage proxy is busy.
  @retval         FALSE       The storage proxy is not busy.
**/
BOOLEAN
EFIAPI
StorageProxyCheckOperationInProgress (
  VOID
  )
{
  UINT32  GeneralStatus2;

  GeneralStatus2 =  PciSegmentRead32 (
                      PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_H_GS2)
                      );

  return (GeneralStatus2 & B_ME_H_GS2_STORAGE_OP_IN_PROGRESS) != 0;
}

/**
  Clears the critical Storage Proxy operation is in progress indicator.

**/
VOID
EFIAPI
StorageProxyClearOperationInProgress (
  VOID
  )
{
  PciSegmentAnd32 (
    PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_H_GS2),
    (UINT32) ~B_ME_H_GS2_STORAGE_OP_IN_PROGRESS
    );
}

/**
  Sets the critical Storage Proxy operation is in progress indicator.

**/
VOID
EFIAPI
StorageProxySetOperationInProgress (
  VOID
  )
{
  PciSegmentOr32 (
    PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_H_GS2),
    (UINT32) B_ME_H_GS2_STORAGE_OP_IN_PROGRESS
    );
}

/**
  Checks if the Storage Proxy is busy.

  @param [in]     TimeoutMs               The number of milliseconds until the timer expires.

  @retval         EFI_SUCCESS             The storage proxy is not busy.
  @retval         EFI_TIMEOUT             The storage proxy was busy for TriggerTime.
  @reval          Others                  An error occurred in the timer.
**/
EFI_STATUS
EFIAPI
StorageProxyCheckBusy (
  IN UINT32              TimeoutMs
  )
{
  EFI_STATUS                    Status;
  EFI_EVENT                     TimeoutEvent;
  UINT64                        TriggerTime;

  DEBUG ((DEBUG_INFO, "Storage Proxy: Wait for Storage Operation to complete.\n"));

  TimeoutEvent = NULL;
  TriggerTime = EFI_TIMER_PERIOD_MILLISECONDS (TimeoutMs);

  Status = gBS->CreateEvent (EVT_TIMER, TPL_CALLBACK, NULL, NULL, &TimeoutEvent);

  Status = gBS->SetTimer (TimeoutEvent, TimerRelative, TriggerTime);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  while ((gBS->CheckEvent (TimeoutEvent)) == EFI_NOT_READY) {
    if (!StorageProxyCheckOperationInProgress ()) {
      DEBUG ((DEBUG_INFO, "\n"));
      return EFI_SUCCESS;
    }
    DEBUG ((DEBUG_INFO, "."));
    MicroSecondDelay (1000); // 1 ms
  }
  //
  // Clear the StorageOperationInProgress bit if timeout occurred
  //
  if (gBS->CheckEvent (TimeoutEvent) == EFI_SUCCESS) {
    StorageProxyClearOperationInProgress ();
  }

  DEBUG ((DEBUG_INFO, "\n"));
  return EFI_TIMEOUT;
}

/**
  Checks if the Storage Proxy is idle.

  @param [in]     TimeoutMs               The number of milliseconds until the timer expires.

  @retval         EFI_NOT_READY           The storage proxy is busy.
  @retval         EFI_SUCCESS             The storage proxy was idle for TriggerTime.
  @reval          Others                  An error occurred in the timer.
**/
EFI_STATUS
EFIAPI
StorageProxyCheckIdle (
  IN UINT32              TimeoutMs
  )
{
  EFI_STATUS                    Status;
  EFI_EVENT                     TimeoutEvent;
  UINT64                        TriggerTime;

  TimeoutEvent = NULL;
  TriggerTime = EFI_TIMER_PERIOD_MILLISECONDS (TimeoutMs);

  Status = gBS->CreateEvent (EVT_TIMER, TPL_CALLBACK, NULL, NULL, &TimeoutEvent);

  Status = gBS->SetTimer (TimeoutEvent, TimerRelative, TriggerTime);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  while ((gBS->CheckEvent (TimeoutEvent)) == EFI_NOT_READY) {
    if (StorageProxyCheckOperationInProgress ()) {
      return EFI_NOT_READY;
    }
    MicroSecondDelay (100);
  }

  return EFI_SUCCESS;
}

/**
  Resets the values in the storage proxy info structure instance to defaults.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The structure was reset to default values successfully.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is invalid.
  @retval         Others                 The structure could not be reset.
**/
EFI_STATUS
EFIAPI
ResetStorageProxyInfoState (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  )
{
  if (StorageProxyInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (StorageProxyInfo->HostStorageProxyBuffer != NULL) {
    ZeroMem (StorageProxyInfo->HostStorageProxyBuffer, EFI_PAGES_TO_SIZE (STORAGE_PROXY_HECI_COMMUNICATE_BUFFER_PAGES));
  }

  StorageProxyInfo->CurrentAction = StorageProxyCheckForRequest;
  StorageProxyInfo->CurrentStatus = STORAGE_PROXY_STATUS_SUCCESS;

  return EFI_SUCCESS;
}

/**
  Sends a storage proxy response message indicating an error occurred.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxySendErrorMessage (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  )
{
  EFI_STATUS                            Status;
  UINT32                                HeciSendLength;
  STORAGE_PROXY_MESSAGE_HEADER          *StorageProxyMsgHeader;

  if (!IsReadyForTransaction ()) {
    return EFI_UNSUPPORTED;
  }

  StorageProxyMsgHeader = (STORAGE_PROXY_MESSAGE_HEADER *) StorageProxyInfo->HostStorageProxyBuffer;

  HeciSendLength = sizeof (STORAGE_PROXY_MESSAGE_HEADER);

  StorageProxyMsgHeader->Fields.IsResponse = TRUE;
  StorageProxyMsgHeader->Fields.Length     = HeciSendLength;
  StorageProxyMsgHeader->Fields.Status     = StorageProxyInfo->CurrentStatus;

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) StorageProxyMsgHeader,
                            HeciSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol when sending a proxy error message.\n"));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Sends the storage proxy Stop message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @retval         EFI_TIMEOUT            The Storage Proxy was busy for more than 5 seconds.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyStop (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  )
{
  EFI_STATUS                   Status;
  UINT32                       HeciSendLength;
  STORAGE_PROXY_STOP_REQUEST   StorageProxyStopMsg;

  mStorageProxyStopRequested = TRUE;

  if (!IsReadyForTransaction ()) {
    return EFI_UNSUPPORTED;
  }

  Status = StorageProxyCheckBusy (5000);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  HeciSendLength = sizeof (STORAGE_PROXY_STOP_REQUEST);

  ZeroMem (&StorageProxyStopMsg, sizeof (STORAGE_PROXY_STOP_REQUEST));
  StorageProxyStopMsg.StorageProxyHeader.Fields.Command    = STORAGE_PROXY_CMD_PROXY_STOP;
  StorageProxyStopMsg.StorageProxyHeader.Fields.IsResponse = FALSE;
  StorageProxyStopMsg.StorageProxyHeader.Fields.Length     = HeciSendLength;
  StorageProxyStopMsg.StorageProxyHeader.Fields.Status     = STORAGE_PROXY_STATUS_SUCCESS;
  StorageProxyStopMsg.ProxyState                           = 0;

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) &StorageProxyStopMsg,
                            HeciSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol sending the proxy stop message.\n"));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  // Note: There is no response defined for the storage proxy stop message.

  return EFI_SUCCESS;
}

/**
  Handles the storage proxy RPMB Write message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyRpmbWrite (
  IN OUT STORAGE_PROXY_INFO        *StorageProxyInfo
  )
{
  EFI_STATUS                       Status;
  STORAGE_PROXY_RPMB_WRITE_BUFFER  *StorageProxyRpmbWriteMsg;
  STORAGE_PROXY_STATUS             RpmbWriteStatus;
  UINT32                           MessageSendLength;

  RpmbWriteStatus = STORAGE_PROXY_STATUS_SUCCESS;

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyRpmbWrite() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  StorageProxyRpmbWriteMsg = (STORAGE_PROXY_RPMB_WRITE_BUFFER *) StorageProxyInfo->HostStorageProxyBuffer;

  if (StorageProxyRpmbWriteMsg->Request.StorageProxyHeader.Fields.Length != sizeof (STORAGE_PROXY_RPMB_WRITE_REQUEST)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An invalid size for RPMB write request was given.\n"));
    RpmbWriteStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
  } else {
    DEBUG ((DEBUG_INFO, "Storage Proxy: RPMB write request received.\n"));
    DEBUG ((DEBUG_INFO, "  Frame Buffer = 0x%08x.\n", (UINTN) &StorageProxyRpmbWriteMsg->Request.RpmbFrame));
    DEBUG ((DEBUG_INFO, "  Frame Size   = 0x%02x.\n", RPMB_FRAME_SIZE));

    Status = SecurityProtocolTransaction (
              RPMB_FRAME_SIZE,
              &StorageProxyRpmbWriteMsg->Request.RpmbFrame,
              FALSE
              );

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred writing to RPMB.\n"));
      RpmbWriteStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
    } else {
      //
      // Construct and send "Result Register Read Request"
      // Note: The RPMB response frame should be placed in the buffer provided for the RPMB request frame.
      //
      Status = RpmbRequestResult (&StorageProxyRpmbWriteMsg->Request.RpmbFrame);

      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred reading from RPMB.\n"));
        RpmbWriteStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
      }
    }
  }

  //
  // Send the RPMB Write Response Message
  //
  MessageSendLength = sizeof (STORAGE_PROXY_RPMB_WRITE_RESPONSE);

  StorageProxyRpmbWriteMsg->Response.StorageProxyHeader.Fields.IsResponse = TRUE;
  StorageProxyRpmbWriteMsg->Response.StorageProxyHeader.Fields.Length     = sizeof (STORAGE_PROXY_RPMB_WRITE_RESPONSE);
  StorageProxyRpmbWriteMsg->Response.StorageProxyHeader.Fields.Status     = RpmbWriteStatus;

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) StorageProxyRpmbWriteMsg,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol sending the RPMB Write response message.\n"));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Handles the storage proxy RPMB Read message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyRpmbRead (
  IN OUT STORAGE_PROXY_INFO       *StorageProxyInfo
  )
{
  EFI_STATUS                      Status;
  STORAGE_PROXY_RPMB_READ_BUFFER  *StorageProxyRpmbReadMsg;
  STORAGE_PROXY_STATUS            RpmbReadStatus;
  UINT32                          MessageSendLength;

  RpmbReadStatus = STORAGE_PROXY_STATUS_SUCCESS;

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyRpmbRead() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  StorageProxyRpmbReadMsg = (STORAGE_PROXY_RPMB_READ_BUFFER *) StorageProxyInfo->HostStorageProxyBuffer;

  if (StorageProxyRpmbReadMsg->Request.StorageProxyHeader.Fields.Length != sizeof (STORAGE_PROXY_RPMB_READ_REQUEST)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An invalid size for RPMB read request was given.\n"));
    RpmbReadStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
  } else {
    DEBUG ((DEBUG_INFO, "Storage Proxy: RPMB read request received.\n"));
    DEBUG ((DEBUG_INFO, "  Frame Buffer = 0x%08x.\n", (UINTN) &StorageProxyRpmbReadMsg->Request.RpmbFrame));
    DEBUG ((DEBUG_INFO, "  FrameSize    = 0x%02x.\n", RPMB_FRAME_SIZE));

    Status = SecurityProtocolTransaction (
              RPMB_FRAME_SIZE,
              &StorageProxyRpmbReadMsg->Request.RpmbFrame,
              TRUE
              );

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred reading from RPMB.\n"));
      RpmbReadStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
    }
  }

  //
  // Send the RPMB Read Response Message
  //
  MessageSendLength = sizeof (STORAGE_PROXY_RPMB_READ_RESPONSE);

  StorageProxyRpmbReadMsg->Response.StorageProxyHeader.Fields.IsResponse = TRUE;
  StorageProxyRpmbReadMsg->Response.StorageProxyHeader.Fields.Length     = MessageSendLength;
  StorageProxyRpmbReadMsg->Response.StorageProxyHeader.Fields.Status     = RpmbReadStatus;

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) StorageProxyRpmbReadMsg,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol sending the RPMB Read response message.\n"));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Handles the storage proxy RPMB Get Counter message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyRpmbGetCounter (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  )
{
  EFI_STATUS                                 Status;
  STORAGE_PROXY_RPMB_GET_COUNTER_BUFFER      *StorageProxyRpmbGetCounterMsg;
  STORAGE_PROXY_STATUS                       RpmbGetCounterStatus;
  UINT32                                     MessageSendLength;

  RpmbGetCounterStatus = STORAGE_PROXY_STATUS_SUCCESS;

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyRpmbGetCounter() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  StorageProxyRpmbGetCounterMsg = (STORAGE_PROXY_RPMB_GET_COUNTER_BUFFER *) StorageProxyInfo->HostStorageProxyBuffer;

  if (StorageProxyRpmbGetCounterMsg->Request.StorageProxyHeader.Fields.Length != sizeof (STORAGE_PROXY_RPMB_GET_COUNTER_REQUEST)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An invalid size for RPMB get counter request was given.\n"));
    RpmbGetCounterStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
  } else {
    DEBUG ((DEBUG_INFO, "Storage Proxy: RPMB Get Counter request received.\n"));
    DEBUG ((DEBUG_INFO, "  Frame Buffer = 0x%08x.\n", (UINTN) &StorageProxyRpmbGetCounterMsg->Request.RpmbFrame));
    DEBUG ((DEBUG_INFO, "  FrameSize    = 0x%02x.\n", RPMB_FRAME_SIZE));

    Status = SecurityProtocolTransaction (
              RPMB_FRAME_SIZE,
              &StorageProxyRpmbGetCounterMsg->Request.RpmbFrame,
              TRUE
              );

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred reading the RPMB counter.\n"));
      RpmbGetCounterStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
    }
  }

  //
  // Send the RPMB Get Counter Message
  //
  MessageSendLength = sizeof (STORAGE_PROXY_RPMB_GET_COUNTER_RESPONSE);

  StorageProxyRpmbGetCounterMsg->Response.StorageProxyHeader.Fields.IsResponse = TRUE;
  StorageProxyRpmbGetCounterMsg->Response.StorageProxyHeader.Fields.Length     = MessageSendLength;
  StorageProxyRpmbGetCounterMsg->Response.StorageProxyHeader.Fields.Status     = RpmbGetCounterStatus;

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) StorageProxyRpmbGetCounterMsg,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol sending the RPMB Get Counter response message.\n"));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Handles the storage proxy GPP Write message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyGppWrite (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  )
{
  EFI_STATUS                      Status;
  STORAGE_PROXY_GPP_WRITE_BUFFER  *StorageProxyGppWriteMsg;
  STORAGE_PROXY_STATUS            GppWriteStatus;
  UINT32                          MessageSendLength;
  UINT32                          DataWriteLength;

  GppWriteStatus = STORAGE_PROXY_STATUS_SUCCESS;

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyGppWrite() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  StorageProxyGppWriteMsg = (STORAGE_PROXY_GPP_WRITE_BUFFER *) StorageProxyInfo->HostStorageProxyBuffer;

  if (StorageProxyGppWriteMsg->Request.StorageProxyHeader.Fields.Length < sizeof (STORAGE_PROXY_GPP_WRITE_REQUEST)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An invalid size for GPP write request was given.\n"));
    GppWriteStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
  } else {
    DataWriteLength = StorageProxyGppWriteMsg->Request.StorageProxyHeader.Fields.Length - sizeof (STORAGE_PROXY_GPP_WRITE_REQUEST);

    DEBUG ((DEBUG_INFO, "Storage Proxy: GPP write request received.\n"));
    DEBUG ((DEBUG_INFO, "  Offset       = 0x%02x.\n", StorageProxyGppWriteMsg->Request.Offset));
    DEBUG ((DEBUG_INFO, "  Size         = 0x%02x.\n", DataWriteLength));
    DEBUG ((DEBUG_INFO, "  Partition ID = %d.\n", StorageProxyInfo->DeviceInfo.GppPartitionId));

    Status = BlockIoTransaction (
              StorageProxyInfo->DeviceInfo.GppPartitionId,
              StorageProxyGppWriteMsg->Request.Offset,
              DataWriteLength,
              (VOID *) (&(StorageProxyGppWriteMsg->Request) + 1),
              FALSE
              );

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred writing to GPP.\n"));
      GppWriteStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
    }
  }

  //
  // Send the GPP Write Response Message
  //
  MessageSendLength = sizeof (STORAGE_PROXY_GPP_WRITE_RESPONSE);

  StorageProxyGppWriteMsg->Response.StorageProxyHeader.Fields.IsResponse = TRUE;
  StorageProxyGppWriteMsg->Response.StorageProxyHeader.Fields.Length     = sizeof (STORAGE_PROXY_GPP_WRITE_RESPONSE);
  StorageProxyGppWriteMsg->Response.StorageProxyHeader.Fields.Status     = GppWriteStatus;

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) StorageProxyGppWriteMsg,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol sending the GPP Write response message.\n"));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Handles the storage proxy GPP Read message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyGppRead (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  )
{
  EFI_STATUS                      Status;
  STORAGE_PROXY_GPP_READ_BUFFER   *StorageProxyGppReadMsg;
  STORAGE_PROXY_STATUS            GppReadStatus;
  UINT32                          MessageSendLength;
  UINT32                          RequestReadSize;

  GppReadStatus = STORAGE_PROXY_STATUS_SUCCESS;

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyGppRead() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  StorageProxyGppReadMsg = (STORAGE_PROXY_GPP_READ_BUFFER *) StorageProxyInfo->HostStorageProxyBuffer;
  RequestReadSize = StorageProxyGppReadMsg->Request.Size;

  DEBUG ((DEBUG_INFO, "Storage Proxy: GPP read request received.\n"));
  DEBUG ((DEBUG_INFO, "  Offset       = 0x%02x.\n", StorageProxyGppReadMsg->Request.Offset));
  DEBUG ((DEBUG_INFO, "  Size         = 0x%02x.\n", RequestReadSize));
  DEBUG ((DEBUG_INFO, "  Partition ID = %d.\n", StorageProxyInfo->DeviceInfo.GppPartitionId));

  Status = BlockIoTransaction (
            StorageProxyInfo->DeviceInfo.GppPartitionId,
            StorageProxyGppReadMsg->Request.Offset,
            RequestReadSize,
            (VOID *) (&(StorageProxyGppReadMsg->Response) + 1),
            TRUE
            );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred reading from GPP.\n"));
    GppReadStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
  }

  //
  // Send the GPP Read Response Message
  //
  MessageSendLength = sizeof (STORAGE_PROXY_GPP_READ_RESPONSE) + RequestReadSize;

  StorageProxyGppReadMsg->Response.StorageProxyHeader.Fields.IsResponse = TRUE;
  StorageProxyGppReadMsg->Response.StorageProxyHeader.Fields.Length     = MessageSendLength;
  StorageProxyGppReadMsg->Response.StorageProxyHeader.Fields.Status     = GppReadStatus;

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) StorageProxyGppReadMsg,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol sending the GPP Read response message.\n"));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Sends the storage proxy Initialization message.

  This function will initialize STORAGE_PROXY_INFO structure. The caller should be aware the any previous information
  will be lost when this function returns.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @retval         EFI_OUT_OF_RESOURCES   Insufficient memory resources exist to allocate the storage proxy info structure.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyInit (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  )
{
  EFI_STATUS                            Status;
  UINT32                                HeciSendLength;
  UINT32                                HeciReceiveLength;
  STORAGE_PROXY_INIT_BUFFER             *StorageProxyInitMsg;

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyInit() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  if (!IsReadyForTransaction ()) {
    return EFI_UNSUPPORTED;
  }

  //
  // Clear OperationInProgress During Initialization
  //
  StorageProxyClearOperationInProgress ();

  //
  // Clear StorageProxyInfo and Allocate a Communication Buffer Used For Future Storage Proxy Transactions
  //
  if (StorageProxyInfo->HostStorageProxyBuffer == NULL) {
    ZeroMem ((VOID *) StorageProxyInfo, sizeof (STORAGE_PROXY_INFO));
    StorageProxyInfo->HostStorageProxyBuffer = AllocatePages (STORAGE_PROXY_HECI_COMMUNICATE_BUFFER_PAGES);
    if (StorageProxyInfo->HostStorageProxyBuffer == NULL) {
      DEBUG ((DEBUG_ERROR, "Storage Proxy: Failed to allocate the storage proxy communication buffer.\n"));
      return EFI_OUT_OF_RESOURCES;
    }
  }
  StorageProxyInitMsg = (STORAGE_PROXY_INIT_BUFFER *) StorageProxyInfo->HostStorageProxyBuffer;

  HeciSendLength    = sizeof (STORAGE_PROXY_INIT_REQUEST);
  //
  // On send this is the buffer size available, on receive it is the size of the response message + data from CSME.
  //
  HeciReceiveLength = EFI_PAGES_TO_SIZE (STORAGE_PROXY_HECI_COMMUNICATE_BUFFER_PAGES);

  StorageProxyInitMsg->Request.StorageProxyHeader.Data              = 0;
  StorageProxyInitMsg->Request.StorageProxyHeader.Fields.Command    = STORAGE_PROXY_CMD_PROXY_INIT;
  StorageProxyInitMsg->Request.StorageProxyHeader.Fields.IsResponse = FALSE;
  StorageProxyInitMsg->Request.StorageProxyHeader.Fields.Length     = HeciSendLength;
  StorageProxyInitMsg->Request.StorageProxyHeader.Fields.Status     = STORAGE_PROXY_STATUS_SUCCESS;

  DEBUG ((DEBUG_INFO, "Storage Proxy: Sending the HECI message for Proxy Init...\n"));
  Status = mHeciProtocol->SendwAck (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) StorageProxyInitMsg,
                            HeciSendLength,
                            &HeciReceiveLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol during the proxy init message.\n"));
    return Status;
  } else if (!IsStorageProxyResponseHeaderValid (&(StorageProxyInitMsg->Response.StorageProxyHeader), STORAGE_PROXY_CMD_PROXY_INIT)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The proxy init message response is invalid.\n"));
    return Status;
  }

  //
  // Populate Storage Proxy Device Information
  //
  DEBUG ((DEBUG_INFO, "Storage Proxy: Populating local proxy information based on CSE response...\n"));
  StorageProxyInfo->DeviceInfo.GppPartitionId   = StorageProxyInitMsg->Response.GppPartitionId;
  StorageProxyInfo->DeviceInfo.RpmbPartitionId  = StorageProxyInitMsg->Response.RpmbPartitionId;
  StorageProxyInfo->DeviceInfo.SerialNumberSize = StorageProxyInitMsg->Response.SerialNumberSize;
  ASSERT (StorageProxyInfo->DeviceInfo.SerialNumberSize > 0);
  StorageProxyInfo->DeviceInfo.StorageType      = StorageProxyInitMsg->Response.StorageType;
  ASSERT (StorageProxyInfo->DeviceInfo.StorageType > STORAGE_PROXY_TYPE_INVALID);
  DEBUG ((DEBUG_INFO, "    GPP Partition ID: %d\n", StorageProxyInfo->DeviceInfo.GppPartitionId));
  DEBUG ((DEBUG_INFO, "    RPMB Partition ID: %d\n", StorageProxyInfo->DeviceInfo.RpmbPartitionId));
  DEBUG ((DEBUG_INFO, "    Serial Number Size: %d bytes\n", StorageProxyInfo->DeviceInfo.SerialNumberSize));
  DEBUG ((DEBUG_INFO, "    Storage Proxy Type: %d\n", StorageProxyInfo->DeviceInfo.StorageType));

  if (StorageProxyInfo->DeviceInfo.SerialNumber != NULL) {
    FreePool (StorageProxyInfo->DeviceInfo.SerialNumber);
  }
  StorageProxyInfo->DeviceInfo.SerialNumber =  AllocateZeroPool (StorageProxyInfo->DeviceInfo.SerialNumberSize);
  if (StorageProxyInfo->DeviceInfo.SerialNumber == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: Failed to allocate the storage proxy device serial number buffer.\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  DEBUG ((DEBUG_INFO, "Storage Proxy: Copying serial number...\n"));
  CopyMem (
    (VOID *) StorageProxyInfo->DeviceInfo.SerialNumber,
    (VOID *) StorageProxyInitMsg->Response.SerialNumber,
    StorageProxyInfo->DeviceInfo.SerialNumberSize
    );

  //
  // Allocated buffer should be initialized to zero prior to this call (i.e. static storage)
  //

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "Storage Proxy: Proxy Init message complete.\n"));

  return EFI_SUCCESS;
}

/**
  Sends the storage proxy Status message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo parameter is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyStatus (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  )
{
  EFI_STATUS                   Status;
  UINT32                       HeciSendLength;
  UINT32                       BootPartitionState;
  UINT32                       GppPartitionState;
  UINT32                       RpmbPartitionState;
  STORAGE_PROXY_STATUS_REQUEST StorageProxyStatusMsg;

  if (!IsReadyForTransaction ()) {
    return EFI_UNSUPPORTED;
  }

  DEBUG ((DEBUG_INFO, "Storage Proxy: Preparing to send Proxy Status message...\n"));

  BootPartitionState = (GetBootModeHob () == BOOT_ON_FLASH_UPDATE) ?
                         STORAGE_PROXY_PARTITION_ACCESSIBLE :
                         STORAGE_PROXY_PARTITION_INACCESSIBLE;
  GppPartitionState = (GetBlockIoProtocol (StorageProxyInfo->DeviceInfo.GppPartitionId) == NULL) ?
                        STORAGE_PROXY_PARTITION_INACCESSIBLE :
                        STORAGE_PROXY_PARTITION_ACCESSIBLE;
  RpmbPartitionState = (SecurityLunSupported () == FALSE) ?
                         STORAGE_PROXY_PARTITION_INACCESSIBLE :
                         STORAGE_PROXY_PARTITION_ACCESSIBLE;

  HeciSendLength = sizeof (STORAGE_PROXY_STATUS_REQUEST);

  ZeroMem (&StorageProxyStatusMsg, sizeof (STORAGE_PROXY_STATUS_REQUEST));
  StorageProxyStatusMsg.StorageProxyHeader.Fields.Command    = STORAGE_PROXY_CMD_PROXY_STATUS;
  StorageProxyStatusMsg.StorageProxyHeader.Fields.IsResponse = FALSE;
  StorageProxyStatusMsg.StorageProxyHeader.Fields.Length     = HeciSendLength;
  StorageProxyStatusMsg.StorageProxyHeader.Fields.Status     = STORAGE_PROXY_STATUS_SUCCESS;
  StorageProxyStatusMsg.Capabilities.Fields.BufferDmaSupport = STORAGE_PROXY_BUFFER_DMA_SUPPORT;
  StorageProxyStatusMsg.CriticalSection                      = (StorageProxyCheckOperationInProgress ()) ? 1 : 0;
  StorageProxyStatusMsg.BootPartitionState                   = BootPartitionState;
  StorageProxyStatusMsg.GppPartitionState                    = GppPartitionState;
  StorageProxyStatusMsg.RpmbPartitionState                   = RpmbPartitionState;

  DEBUG ((DEBUG_INFO, "Storage Proxy: Status Values:\n"));
  DEBUG ((DEBUG_INFO, "  Command            = %d.\n", StorageProxyStatusMsg.StorageProxyHeader.Fields.Command));
  DEBUG ((
    DEBUG_INFO,
    "  BootPartitionState  = %a.\n",
    ((StorageProxyStatusMsg.BootPartitionState == STORAGE_PROXY_PARTITION_INACCESSIBLE) ? "Inaccessible" : "Accessible")
    ));
  DEBUG ((
    DEBUG_INFO,
    "  GppPartitionState  = %a.\n",
    ((StorageProxyStatusMsg.GppPartitionState == STORAGE_PROXY_PARTITION_INACCESSIBLE) ? "Inaccessible" : "Accessible")
    ));
  DEBUG ((
    DEBUG_INFO,
    "  RpmbPartitionState = %a.\n",
    ((StorageProxyStatusMsg.RpmbPartitionState == STORAGE_PROXY_PARTITION_INACCESSIBLE) ? "Inaccessible" : "Accessible")
    ));
  DEBUG ((DEBUG_INFO, "  CriticalSection    = %a.\n", ((StorageProxyStatusMsg.CriticalSection == 0) ? "Off" : "On")));
  DEBUG ((DEBUG_INFO, "  Capabilities       = 0x%8x.\n", StorageProxyStatusMsg.Capabilities));
  DEBUG ((
    DEBUG_INFO,
    "    Buffer DMA Support     = %a.\n",
    ((StorageProxyStatusMsg.Capabilities.Fields.BufferDmaSupport == STORAGE_PROXY_BUFFER_DMA_SUPPORT) ? "True" : "False")
    ));

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) &StorageProxyStatusMsg,
                            HeciSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol sending the proxy status message.\n"));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  // Note: There is no response defined for the storage proxy status message.
  DEBUG ((DEBUG_INFO, "Storage Proxy: Proxy Status message complete.\n"));

  return EFI_SUCCESS;
}

/**
  Handles the storage proxy Manage Critical Section message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyManageCriticalSection (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  )
{
  EFI_STATUS                                    Status;
  STORAGE_PROXY_MANAGE_CRITICAL_SECTION_REQUEST *ManageCriticalSectionMsg;

  Status = EFI_SUCCESS;
  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyManageCriticalSection() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  ManageCriticalSectionMsg = (STORAGE_PROXY_MANAGE_CRITICAL_SECTION_REQUEST *) StorageProxyInfo->HostStorageProxyBuffer;

  DEBUG ((DEBUG_INFO, "Storage Proxy: Manage Critical Section request received.\n"));

  if (
    ManageCriticalSectionMsg->StorageProxyHeader.Fields.IsResponse == TRUE ||
    ManageCriticalSectionMsg->StorageProxyHeader.Fields.Status != STORAGE_PROXY_STATUS_SUCCESS
    ) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The Manage Critical Section request is invalid.\n"));
    StorageProxyInfo->CurrentAction = StorageProxySendErrorMessage;
    StorageProxyInfo->CurrentStatus = STORAGE_PROXY_STATUS_NOT_SUPPORTED;
    return EFI_DEVICE_ERROR;
  }

  if (ManageCriticalSectionMsg->Command == STORAGE_PROXY_CRITICAL_SECTION_LOCK) {
    DEBUG ((DEBUG_INFO, "Storage Proxy: Manage Critical Section lock set requested.\n"));
    StorageProxySetOperationInProgress ();
    Status = StorageProxyStatus (StorageProxyInfo);
  } else if (ManageCriticalSectionMsg->Command == STORAGE_PROXY_CRITICAL_SECTION_UNLOCK) {
    DEBUG ((DEBUG_INFO, "Storage Proxy: Manage Critical Section lock clear requested.\n"));
    StorageProxyClearOperationInProgress ();
    Status = StorageProxyStatus (StorageProxyInfo);
    ASSERT_EFI_ERROR (Status);
    if (mStorageProxyStopRequested) {
      Status = StorageProxyStop (StorageProxyInfo);
    }
  } else {
    DEBUG ((DEBUG_INFO, "Storage Proxy: Manage Critical Section lock request is invalid.\n"));
    ASSERT (
      (ManageCriticalSectionMsg->Command == STORAGE_PROXY_CRITICAL_SECTION_LOCK) ||
      (ManageCriticalSectionMsg->Command == STORAGE_PROXY_CRITICAL_SECTION_UNLOCK)
      );
    Status = ResetStorageProxyInfoState (StorageProxyInfo);
  }
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Handles the storage proxy Allocate Memory Buffer message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyAllocateMemoryBuffer (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  )
{
  EFI_STATUS                                 Status;
  STORAGE_PROXY_ALLOC_MEMORY_BUFFER_BUFFER   *StorageProxyAllocMemoryBufferMsg;
  STORAGE_PROXY_STATUS                       AllocMemoryBufferStatus;
  UINT32                                     MessageSendLength;

  AllocMemoryBufferStatus = STORAGE_PROXY_STATUS_SUCCESS;

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyAllocateMemoryBuffer() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  StorageProxyAllocMemoryBufferMsg = (STORAGE_PROXY_ALLOC_MEMORY_BUFFER_BUFFER *) StorageProxyInfo->HostStorageProxyBuffer;

  DEBUG ((DEBUG_INFO, "Storage Proxy: Allocate Memory Buffer request received.\n"));
  DEBUG ((DEBUG_INFO, "  Length       = 0x%08x.\n", StorageProxyAllocMemoryBufferMsg->Request.Length));

  if (StorageProxyAllocMemoryBufferMsg->Request.Length == 0) {
    AllocMemoryBufferStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
  } else {
    StorageProxyInfo->AllocatedBuffer.Buffer = AllocatePages (
                                                 EFI_SIZE_TO_PAGES (StorageProxyAllocMemoryBufferMsg->Request.Length)
                                                 );

    if (StorageProxyInfo->AllocatedBuffer.Buffer == NULL) {
      DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred allocating the DRAM buffer.\n"));
      AllocMemoryBufferStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
    } else {
      DEBUG ((
        DEBUG_INFO,
        "Storage Proxy: Allocated %d pages at DRAM buffer 0x%08x.\n",
        EFI_SIZE_TO_PAGES (StorageProxyAllocMemoryBufferMsg->Request.Length),
        (UINTN) StorageProxyInfo->AllocatedBuffer.Buffer
        ));
      //
      // TODO: Update to return low and high for true 64-bit address.
      //
      StorageProxyInfo->AllocatedBuffer.Size                       = StorageProxyAllocMemoryBufferMsg->Request.Length;
      StorageProxyAllocMemoryBufferMsg->Response.BufferAddressLow  = (UINT32) (((UINTN) StorageProxyInfo->AllocatedBuffer.Buffer) & 0xFFFFFFFF);;
      StorageProxyAllocMemoryBufferMsg->Response.BufferAddressHigh = 0;
    }
  }

  //
  // Send the Allocate Memory Buffer Response Message
  //
  MessageSendLength = sizeof (STORAGE_PROXY_ALLOC_MEMORY_BUFFER_RESPONSE);

  StorageProxyAllocMemoryBufferMsg->Response.StorageProxyHeader.Fields.IsResponse = TRUE;
  StorageProxyAllocMemoryBufferMsg->Response.StorageProxyHeader.Fields.Length     = MessageSendLength;
  StorageProxyAllocMemoryBufferMsg->Response.StorageProxyHeader.Fields.Status     = AllocMemoryBufferStatus;

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) StorageProxyAllocMemoryBufferMsg,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol sending the Allocate Memory Buffer response message.\n"));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Handles the storage proxy Commit Memory Buffer message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyCommitMemoryBuffer (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  )
{
  EFI_STATUS                                 Status;
  STORAGE_PROXY_COMMIT_MEMORY_BUFFER_BUFFER  *StorageProxyCommitMemoryBufferMsg;
  VOID                                       *DataWriteBufferOffsetPtr;
  STORAGE_PROXY_STATUS                       CommitMemoryBufferStatus;
  UINT32                                     DataLength;
  UINT32                                     MessageSendLength;
  UINT32                                     TargetLun;
  BOOLEAN                                    DeallocateAfterCommit;

  CommitMemoryBufferStatus = STORAGE_PROXY_STATUS_SUCCESS;
  DataWriteBufferOffsetPtr = NULL;
  DeallocateAfterCommit    = FALSE;
  TargetLun                = 0;

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyCommitMemoryBuffer() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  StorageProxyCommitMemoryBufferMsg = (STORAGE_PROXY_COMMIT_MEMORY_BUFFER_BUFFER *) StorageProxyInfo->HostStorageProxyBuffer;

  DataLength = StorageProxyCommitMemoryBufferMsg->Request.Length;
  if (StorageProxyInfo->AllocatedBuffer.Buffer == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: Commit memory buffer was called with no buffer allocated.\n"));
    CommitMemoryBufferStatus = STORAGE_PROXY_STATUS_NOT_READY;
  } else if (StorageProxyCommitMemoryBufferMsg->Request.OffsetInBuffer > StorageProxyInfo->AllocatedBuffer.Size) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: Offset in buffer is greater than buffer size.\n"));
    CommitMemoryBufferStatus = STORAGE_PROXY_STATUS_INVALID_ADDRESS;
  } else {
    DEBUG ((DEBUG_INFO, "Storage Proxy: Commit Memory Buffer request received.\n"));
    DEBUG ((DEBUG_INFO, "  Storage Partition       = %d\n", StorageProxyCommitMemoryBufferMsg->Request.StoragePartition));

    if ((StorageProxyCommitMemoryBufferMsg->Request.DeallocateAfterCommit == 1) || (DataLength == 0)) {
      DeallocateAfterCommit = TRUE;
    }

    if (StorageProxyCommitMemoryBufferMsg->Request.StoragePartition == STORAGE_PROXY_PARTITION_GPP_INDICATOR) {
      DEBUG ((DEBUG_INFO, "    GPP partition specified.\n"));
      DEBUG ((DEBUG_INFO, "       GPP partition ID: %d\n", StorageProxyInfo->DeviceInfo.GppPartitionId));
      TargetLun = StorageProxyInfo->DeviceInfo.GppPartitionId;
    } else if (StorageProxyCommitMemoryBufferMsg->Request.StoragePartition == STORAGE_PROXY_PARTITION_BOOT_INDICATOR) {
      DEBUG ((DEBUG_INFO, "    Boot partition specified.\n"));
      DEBUG ((DEBUG_INFO, "       Boot partition ID: %d\n", FIRMWARE_BOOT_PARTITION));
      TargetLun = FIRMWARE_BOOT_PARTITION;
    } else {
      DEBUG ((DEBUG_ERROR, "    Invalid boot partition specified.\n"));
      DataLength = 0;
      CommitMemoryBufferStatus = STORAGE_PROXY_STATUS_NOT_SUPPORTED;
    }
    DEBUG ((DEBUG_INFO, "  Deallocate After Commit = %a\n", ((DeallocateAfterCommit) ? "True" : "False")));
    DEBUG ((DEBUG_INFO, "  Offset in Buffer        = 0x%x\n", StorageProxyCommitMemoryBufferMsg->Request.OffsetInBuffer));
    DEBUG ((DEBUG_INFO, "  NvmOffset               = 0x%x\n", StorageProxyCommitMemoryBufferMsg->Request.NvmOffset));
    DEBUG ((DEBUG_INFO, "  Length                  = 0x%x\n", DataLength));

    if (DataLength > 0 && CommitMemoryBufferStatus == STORAGE_PROXY_STATUS_SUCCESS) {
      DataWriteBufferOffsetPtr = (VOID *) (
                                   ((UINT8 *) StorageProxyInfo->AllocatedBuffer.Buffer) + \
                                   StorageProxyCommitMemoryBufferMsg->Request.OffsetInBuffer
                                   );

      Status = BlockIoTransaction (
                TargetLun,
                StorageProxyCommitMemoryBufferMsg->Request.NvmOffset,
                DataLength,
                DataWriteBufferOffsetPtr,
                FALSE
                );
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred committing the allocated buffer to NVM.\n"));
        CommitMemoryBufferStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
      }
    }

    if (DeallocateAfterCommit) {
      DEBUG ((DEBUG_INFO, "Storage Proxy: Deallocating the buffer.\n"));
      FreePages (StorageProxyInfo->AllocatedBuffer.Buffer, EFI_SIZE_TO_PAGES (StorageProxyInfo->AllocatedBuffer.Size));
      StorageProxyInfo->AllocatedBuffer.Buffer = NULL;
      StorageProxyInfo->AllocatedBuffer.Size   = 0;
    }
  }

  //
  // Send the Commit Memory Buffer Response Message
  //
  MessageSendLength = sizeof (STORAGE_PROXY_COMMIT_MEMORY_BUFFER_RESPONSE);

  StorageProxyCommitMemoryBufferMsg->Response.StorageProxyHeader.Fields.IsResponse = TRUE;
  StorageProxyCommitMemoryBufferMsg->Response.StorageProxyHeader.Fields.Length     = MessageSendLength;
  StorageProxyCommitMemoryBufferMsg->Response.StorageProxyHeader.Fields.Status     = CommitMemoryBufferStatus;
  StorageProxyCommitMemoryBufferMsg->Response.BytesWritten                         = DataLength;

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) StorageProxyCommitMemoryBufferMsg,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: An error was returned from the HECI protocol sending the Commit Memory Buffer response message.\n"));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Handles the storage proxy Fill Memory Buffer message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyFillMemoryBuffer (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  )
{
  EFI_STATUS                                 Status;
  STORAGE_PROXY_FILL_MEMORY_BUFFER_BUFFER    *StorageProxyFillMemoryBufferMsg;

  VOID                                       *DataReadBufferOffsetPtr;
  STORAGE_PROXY_STATUS                       FillMemoryBufferStatus;
  UINT32                                     DataLength;
  UINT32                                     MessageSendLength;
  UINT32                                     TargetLun;

  DataReadBufferOffsetPtr  = NULL;
  FillMemoryBufferStatus   = STORAGE_PROXY_STATUS_SUCCESS;
  TargetLun                = 0;

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyFillMemoryBuffer() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  StorageProxyFillMemoryBufferMsg = (STORAGE_PROXY_FILL_MEMORY_BUFFER_BUFFER *) StorageProxyInfo->HostStorageProxyBuffer;

  DataLength = StorageProxyFillMemoryBufferMsg->Request.Length;
  if (StorageProxyInfo->AllocatedBuffer.Buffer == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: Fill memory buffer was called with no buffer allocated.\n"));
    FillMemoryBufferStatus = STORAGE_PROXY_STATUS_NOT_READY;
  } else if (StorageProxyFillMemoryBufferMsg->Request.OffsetInBuffer > StorageProxyInfo->AllocatedBuffer.Size) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: Offset in buffer is greater than buffer size.\n"));
    FillMemoryBufferStatus = STORAGE_PROXY_STATUS_INVALID_ADDRESS;
  } else {
    DataReadBufferOffsetPtr = (VOID *) (
                                ((UINT8 *) StorageProxyInfo->AllocatedBuffer.Buffer) + \
                                StorageProxyFillMemoryBufferMsg->Request.OffsetInBuffer
                                );

    DEBUG ((DEBUG_INFO, "Storage Proxy: Fill Memory Buffer request received.\n"));
    DEBUG ((DEBUG_INFO, "  Storage Partition       = %d\n", StorageProxyFillMemoryBufferMsg->Request.StoragePartition));
    if (StorageProxyFillMemoryBufferMsg->Request.StoragePartition == STORAGE_PROXY_PARTITION_GPP_INDICATOR) {
      DEBUG ((DEBUG_INFO, "    GPP partition specified.\n"));
      DEBUG ((DEBUG_INFO, "       GPP partition ID: %d\n", StorageProxyInfo->DeviceInfo.GppPartitionId));
      TargetLun = StorageProxyInfo->DeviceInfo.GppPartitionId;
    } else if (StorageProxyFillMemoryBufferMsg->Request.StoragePartition == STORAGE_PROXY_PARTITION_BOOT_INDICATOR) {
      DEBUG ((DEBUG_INFO, "    Boot partition specified.\n"));
      DEBUG ((DEBUG_INFO, "       Boot partition ID: %d\n", FIRMWARE_BOOT_PARTITION));
      TargetLun = FIRMWARE_BOOT_PARTITION;
    } else {
      DEBUG ((DEBUG_ERROR, "    Invalid boot partition specified.\n"));
      DataLength = 0;
      FillMemoryBufferStatus = STORAGE_PROXY_STATUS_NOT_SUPPORTED;
    }
    DEBUG ((DEBUG_INFO, "  Offset in Buffer        = 0x%x\n", StorageProxyFillMemoryBufferMsg->Request.OffsetInBuffer));
    DEBUG ((DEBUG_INFO, "  NvmOffset               = 0x%x\n", StorageProxyFillMemoryBufferMsg->Request.NvmOffset));
    DEBUG ((DEBUG_INFO, "  Length                  = 0x%x\n", DataLength));

    Status = BlockIoTransaction (
              TargetLun,
              StorageProxyFillMemoryBufferMsg->Request.NvmOffset,
              DataLength,
              DataReadBufferOffsetPtr,
              TRUE
              );

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred reading data to the allocated buffer from NVM.\n"));
      FillMemoryBufferStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
    }
  }

  //
  // Send the Fill Memory Buffer Response Message
  //
  MessageSendLength = sizeof (STORAGE_PROXY_FILL_MEMORY_BUFFER_RESPONSE);

  StorageProxyFillMemoryBufferMsg->Response.StorageProxyHeader.Fields.IsResponse = TRUE;
  StorageProxyFillMemoryBufferMsg->Response.StorageProxyHeader.Fields.Length     = MessageSendLength;
  StorageProxyFillMemoryBufferMsg->Response.StorageProxyHeader.Fields.Status     = FillMemoryBufferStatus;
  StorageProxyFillMemoryBufferMsg->Response.BytesRead                            = DataLength;

  Status = mHeciProtocol->SendMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            (UINT32 *) StorageProxyFillMemoryBufferMsg,
                            MessageSendLength,
                            BIOS_FIXED_HOST_ADDR,
                            HECI_STORAGE_PROXY_MESSAGE_ADDR
                            );
  if (EFI_ERROR (Status)) {
    DEBUG ((
      DEBUG_ERROR,
      "Storage Proxy: An error was returned from the HECI protocol sending the Fill Memory Buffer response message.\n"
      ));
  }

  Status = ResetStorageProxyInfoState (StorageProxyInfo);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Processes a storage proxy request from CSME.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyProcessRequest (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  )
{
  EFI_STATUS                      Status;
  UINT32                          HeciReceiveLength;
  STORAGE_PROXY_MESSAGE_HEADER    *StorageProxyMsgHeader;

  DEBUG ((DEBUG_INFO, "Storage Proxy: Processing the proxy request message...\n"));

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyProcessRequest() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  if (!IsReadyForTransaction ()) {
    return EFI_UNSUPPORTED;
  }

  //
  // Provide a large fixed-size buffer (HostStorageProxyBuffer) to receive arbitrary messages from CSME
  //
  HeciReceiveLength = EFI_PAGES_TO_SIZE (STORAGE_PROXY_HECI_COMMUNICATE_BUFFER_PAGES);
  Status = mHeciProtocol->ReadMsg (
                            STORAGE_PROXY_HECI_DEVICE,
                            BLOCKING,
                            (UINT32 *) StorageProxyInfo->HostStorageProxyBuffer,
                            &HeciReceiveLength
                            );
  if (EFI_ERROR (Status)) {
    if (Status == EFI_NO_RESPONSE) {
      //
      // The ME HECI buffer was empty. The interrupt may have been generated for a reason other than
      // to send a message. Ignore the interrupt.
      //
      DEBUG ((DEBUG_INFO, "Storage Proxy: Ignoring interrupt with empty message.\n"));
      Status = ResetStorageProxyInfoState (StorageProxyInfo);
      ASSERT_EFI_ERROR (Status);
    } else {
      //
      // By sending a generic error message, the response length may not match what is expected in the message response.
      //
      StorageProxyInfo->CurrentAction = StorageProxySendErrorMessage;
      StorageProxyInfo->CurrentStatus = STORAGE_PROXY_STATUS_GENERAL_FAILURE;
      DEBUG ((DEBUG_ERROR, "Storage Proxy: An error occurred reading the CSME request message. Status = %r\n", Status));
    }
    goto Exit;
  }

  StorageProxyMsgHeader = StorageProxyInfo->HostStorageProxyBuffer;

  //
  // Validate the request message header
  //
  if (StorageProxyMsgHeader->Fields.IsResponse == TRUE) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: Unexpected response message received.\n"));
    StorageProxyInfo->CurrentAction = StorageProxySendErrorMessage;
    StorageProxyInfo->CurrentStatus = STORAGE_PROXY_STATUS_NOT_SUPPORTED;
    goto Exit;
  } else if (StorageProxyMsgHeader->Fields.Status != STORAGE_PROXY_STATUS_SUCCESS) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: Proxy status is unsuccessful in request received.\n"));
    StorageProxyInfo->CurrentAction = StorageProxySendErrorMessage;
    StorageProxyInfo->CurrentStatus = STORAGE_PROXY_STATUS_NOT_SUPPORTED;
    goto Exit;
  }

  DEBUG ((
    DEBUG_INFO,
    "Storage Proxy: Message request found from CSME. Command = %02d\n",
    StorageProxyMsgHeader->Fields.Command
    ));

  //
  // Determine the CSME command requested
  //
  switch (StorageProxyMsgHeader->Fields.Command) {
    case STORAGE_PROXY_CMD_RPMB_WRITE:
      StorageProxyInfo->CurrentAction = StorageProxyRpmbWrite;
      break;
    case STORAGE_PROXY_CMD_RPMB_READ:
      StorageProxyInfo->CurrentAction = StorageProxyRpmbRead;
      break;
    case STORAGE_PROXY_CMD_RPMB_GET_COUNTER:
      StorageProxyInfo->CurrentAction = StorageProxyRpmbGetCounter;
      break;
    case STORAGE_PROXY_CMD_GPP_WRITE:
      StorageProxyInfo->CurrentAction = StorageProxyGppWrite;
      break;
    case STORAGE_PROXY_CMD_GPP_READ:
      StorageProxyInfo->CurrentAction = StorageProxyGppRead;
      break;
    case STORAGE_PROXY_CMD_ALLOC_MEMORY_BUFFER:
      StorageProxyInfo->CurrentAction = StorageProxyAllocateMemoryBuffer;
      break;
    case STORAGE_PROXY_CMD_COMMIT_MEMORY_BUFFER:
      StorageProxyInfo->CurrentAction = StorageProxyCommitMemoryBuffer;
      break;
    case STORAGE_PROXY_CMD_FILL_MEMORY_BUFFER:
      StorageProxyInfo->CurrentAction = StorageProxyFillMemoryBuffer;
      break;
    case STORAGE_PROXY_CMD_MANAGE_CRITICAL_SECTION:
      StorageProxyInfo->CurrentAction = StorageProxyManageCriticalSection;
      break;
    default:
      DEBUG ((DEBUG_ERROR, "Storage Proxy: An unrecognized command was received.\n"));
      StorageProxyInfo->CurrentAction = StorageProxySendErrorMessage;
      StorageProxyInfo->CurrentStatus = STORAGE_PROXY_STATUS_INVALID_COMMAND;
      break;
  }

Exit:
  return Status;
}

/**
  Calculate if the circular buffer has overflowed.
  Corresponds to HECI HPS (part of) section 4.2.1

  @param[in] ReadPointer          Location of the read pointer.
  @param[in] WritePointer         Location of the write pointer.

  @retval                         Number of filled slots.
**/
UINT8
FilledSlots (
  IN UINT32 ReadPointer,
  IN UINT32 WritePointer
  )
{
  UINT8 FilledSlots;

  ///
  /// Calculation documented in HECI HPS 0.68 section 4.2.1
  ///
  FilledSlots = (((INT8) WritePointer) - ((INT8) ReadPointer));

  return FilledSlots;
}

/**
  This function provides a standard way to verify the Storage Proxy HECI device is configured
  properly. This is particularly important across operations such as PCI enumeration.

  @retval  HeciMemoryBar   HECI Memory BAR. A zero value indicates an invalid BAR.
**/
UINTN
EFIAPI
StorageProxyCheckAndFixHeciForAccess (
  VOID
  )
{
  UINT64  HeciBaseAddress;
  UINT32  Buffer[2];

  HeciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, STORAGE_PROXY_HECI_DEVICE, 0);
  if (PciSegmentRead16 (HeciBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    return 0;
  }

  Buffer[0] = PciSegmentRead32 (HeciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0;
  Buffer[1] = 0x0;
  if ((PciSegmentRead32 (HeciBaseAddress + PCI_BASE_ADDRESSREG_OFFSET) & 0x6) == 0x4) {
    Buffer[1] = PciSegmentRead32 (HeciBaseAddress + (PCI_BASE_ADDRESSREG_OFFSET + 4));
  }

  if (Buffer[0] == 0x0 && Buffer[1] == 0x0) {
    DEBUG ((DEBUG_WARN, "The MMIO BAR for the storage proxy HECI device is not programmed!\n"));
  } else if (Buffer[0] == 0xFFFFFFFF) {
    DEBUG ((DEBUG_WARN, "The storage proxy HECI device is not enabled in this phase!\n"));
  } else {
    PciSegmentOr8 (HeciBaseAddress + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_MEMORY_SPACE);
    return *((UINTN *) (&Buffer[0]));
  }

  return 0;
}

/**
  Checks if a storage proxy request was sent from CSME.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_DEVICE_ERROR       An error occurred getting the BAR from the storage proxy HECI device.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer passed to the function is NULL.
**/
EFI_STATUS
EFIAPI
StorageProxyCheckForRequest (
  IN OUT STORAGE_PROXY_INFO       *StorageProxyInfo
  )
{
  EFI_STATUS                      Status;
  UINTN                           StorageProxyHeciBar;
  HECI_CONTROL_STATUS_REGISTER    HeciCsrMeHra;

  if (StorageProxyInfo == NULL) {
    DEBUG ((DEBUG_ERROR, "Storage Proxy: The storage proxy info pointer passed to StorageProxyCheckForRequest() is NULL.\n"));
    return EFI_INVALID_PARAMETER;
  }

  StorageProxyHeciBar = StorageProxyCheckAndFixHeciForAccess ();
  if (StorageProxyHeciBar == 0x0) {
    DEBUG ((DEBUG_WARN, "Storage Proxy: The storage proxy HECI device BAR is not programmed (or PCI enumeration is active)!\n"));
  } else if (StorageProxyHeciBar == 0xFFFFFFFF) {
    return EFI_DEVICE_ERROR;
  } else {
    HeciCsrMeHra.Data = MmioRead32 (StorageProxyHeciBar + ME_CSR_HA);
    if (HeciCsrMeHra.Fields.Reset == 1 || HeciCsrMeHra.Fields.Ready == 0) {
      //
      // CSE reset on the storage proxy HECI device
      //
      DEBUG ((DEBUG_INFO, "Storage Proxy: Reconnecting due to CSE reset.\n"));

      Status = mHeciProtocol->ResetHeci (STORAGE_PROXY_HECI_DEVICE);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Storage Proxy: HECI Protocol Error - Resetting the storage proxy HECI device.\n"));
        return Status;
      }

      Status = mHeciProtocol->InitHeci (STORAGE_PROXY_HECI_DEVICE);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "Storage Proxy: HECI Protocol Error - Initializing the storage proxy HECI device.\n"));
        return Status;
      }

      //
      // Send the one-shot Proxy Initialization message (initializes the StorageProxyInfo structure)
      //
      Status = StorageProxyInit (StorageProxyInfo);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "BIOS storage proxy initialization failed after CSE reset. Status = %r.\n", Status));
        return Status;
      }

      //
      // Send the one-shot Proxy Status message
      //
      Status = StorageProxyStatus (StorageProxyInfo);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "BIOS storage proxy status failed after CSE reset. Status = %r.\n", Status));
        return Status;
      }
    } else if (FilledSlots (HeciCsrMeHra.Fields.CBReadPointer, HeciCsrMeHra.Fields.CBWritePointer) > 0) {
      DEBUG ((DEBUG_INFO, "Storage Proxy: Request detected on the storage proxy HECI device.\n"));
      StorageProxyInfo->CurrentAction = StorageProxyProcessRequest;
    }
  }
  // If a host interrupt is not asserted, keep the state at StorageProxyCheckForRequest.

  return EFI_SUCCESS;
}

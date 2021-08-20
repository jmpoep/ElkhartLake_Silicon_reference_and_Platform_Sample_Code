/** @file
  Implementation of USB device mode APIs.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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


#include <Base.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h>
#include "XdciUtility.h"
#include "UsbDeviceMode.h"
#include "UsbDeviceDxe.h"

#ifdef _MSC_VER
#pragma optimize ("", off)
#endif

//
// Global USBD driver object. This is the main private driver object
// that contains all data needed for this driver to operate.
//
USB_DEVICE_DRIVER_OBJ gDrvObj;

//
// Global data IO transaction request object
//
USB_DEVICE_IO_REQ gCtrlIoReq = {
  //
  // IO information containing the buffer and data size
  //
  {
    NULL,
    0,
  },
  //
  // Note: This object is used for Control Ep transfers only
  // therefore the endpoint info must always be NULL
  //
  {
    NULL,
    NULL,
  }
};

//
// global flag to signal device event processing loop to run/stop
//
BOOLEAN gRun = FALSE;


/**
  Initializes the XDCI core

  @param MmioBar       Address of MMIO BAR
  @param XdciHndl      Double pointer to for XDCI layer to set as an
                       opaque handle to the driver to be used in subsequent
                       interactions with the XDCI layer.

  @return EFI_SUCCESS if successfully initialized XDCI, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdInit (
  IN UINTN     MmioBar,
  IN VOID      **XdciHndl
  )
{
  EFI_STATUS               Status = EFI_DEVICE_ERROR;
  USB_DEV_CONFIG_PARAMS    ConfigParams;

  DEBUG ((DEBUG_INFO, "UsbdInit start\n"));
  ConfigParams.ControllerId = USB_ID_DWC_XDCI;
  ConfigParams.BaseAddress  = MmioBar;
  ConfigParams.Role = USB_ROLE_DEVICE;
  ConfigParams.Speed = USB_SPEED_SUPER;

  Status = usb_device_init (&ConfigParams, XdciHndl);

  DEBUG ((DEBUG_INFO, "UsbdInit status is %x\n", Status));
  DEBUG ((DEBUG_INFO, "ConfigParams.BaseAddress 0x%016lx\n", ConfigParams.BaseAddress));

  return Status;
}


/**
  Copies relevant endpoint data from standard USB endpoint descriptors
  to the usb_ep_info structure used by the XDCI

  @param EpDest   destination structure
  @param EpSrc    source structure

  @return VOID

**/
VOID
UsbdSetEpInfo (
  IN USB_EP_INFO                 *EpDest,
  IN USB_DEVICE_ENDPOINT_INFO    *EpSrc
  )
{
  EFI_USB_ENDPOINT_DESCRIPTOR              *EpDesc = NULL;
  EFI_USB_ENDPOINT_COMPANION_DESCRIPTOR    *EpCompDesc = NULL;

  /* start by clearing all data in the destination */
  SetMem (EpDest, sizeof(USB_EP_INFO), 0);
  EpDesc = EpSrc->EndpointDesc;
  EpCompDesc = EpSrc->EndpointCompDesc;

  if (EpDesc != NULL) {
    EpDest->ep_num = EpDesc->EndpointAddress & 0x0F; /* Bits 0-3 are ep num */
    EpDest->ep_dir = ((EpDesc->EndpointAddress & USB_ENDPOINT_DIR_IN) > 0) ? UsbEpDirIn : UsbEpDirOut;
    EpDest->ep_type = EpDesc->Attributes & USB_ENDPOINT_TYPE_MASK;
    EpDest->max_pkt_size = EpDesc->MaxPacketSize;
    EpDest->interval = EpDesc->Interval;
  }
  if (EpCompDesc != NULL) {
    EpDest->max_streams = EpCompDesc->Attributes & USB_EP_BULK_BM_ATTR_MASK;
    EpDest->burst_size = EpCompDesc->MaxBurst;
    EpDest->mult = EpCompDesc->BytesPerInterval;
  }

  return;
}


/**
  Initializes the given endpoint

  @param XdciHndl  Pointer (handle) to the XDCI driver object
  @param DevEpInfo Pointer to endpoint info structure
                   for the endpoint to initialize

  @return EFI_SUCCESS if operation succeeded, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdInitEp (
  IN VOID                      *XdciHndl,
  IN USB_DEVICE_ENDPOINT_INFO  *DevEpInfo
  )
{
  EFI_STATUS   Status = EFI_DEVICE_ERROR;
  USB_EP_INFO  EpInfo;

  UsbdSetEpInfo (&EpInfo, DevEpInfo);
  Status = usb_device_init_ep (XdciHndl, &EpInfo);

  return Status;
}


/**
  Callback handler used when transfer operations complete. Calls
  upper layer routine to handle the operation.

  @param XdciHndl  Pointer (handle) to the XDCI driver object
  @param XferReq   Pointer to the transfer request structure

  @return VOID

**/
VOID
EFIAPI
UsbdXferDoneHndlr (
  IN VOID                    *XdciHndl,
  IN USB_XFER_REQUEST        *XferReq
  )
{
  EFI_USB_DEVICE_XFER_INFO  XferInfo;

  XferInfo.EndpointNum = (UINT8)XferReq->ep_info.ep_num;
  XferInfo.EndpointDir = XferReq->ep_info.ep_dir;
  XferInfo.EndpointType = XferReq->ep_info.ep_type;
  XferInfo.Buffer = XferReq->xfer_buffer;
  XferInfo.Length = XferReq->actual_xfer_len;

  DEBUG ((DEBUG_INFO,  "UsbdXferDoneHndlr: XferReq->ep_info.ep_num = 0x%x\n", XferReq->ep_info.ep_num));
  DEBUG ((DEBUG_INFO,  "UsbdXferDoneHndlr: XferReq->ep_info.ep_dir = 0x%x\n", XferReq->ep_info.ep_dir));
  DEBUG ((DEBUG_INFO,  "UsbdXferDoneHndlr: XferReq->ep_info.ep_type = 0x%x\n", XferReq->ep_info.ep_type));
  DEBUG ((DEBUG_INFO,  "UsbdXferDoneHndlr: XferReq->xfer_buffer = 0x%x\n", XferReq->xfer_buffer));
  DEBUG ((DEBUG_INFO,  "UsbdXferDoneHndlr: XferReq->actual_xfer_len = 0x%x\n", XferReq->actual_xfer_len));

  UsbdXferDoneHdlr (&XferInfo);
  return;
}


/**
  Queue a request to transmit data

  @param XdciHndl  Pointer (handle) to the XDCI driver object
  @param IoReq     Pointer to IO structure containing details of the
                   transfer request

  @return EFI_SUCCESS if operation succeeded, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdEpTxData (
  IN VOID               *XdciHndl,
  IN USB_DEVICE_IO_REQ  *IoReq
  )
{
  EFI_STATUS        Status = EFI_DEVICE_ERROR;
  USB_XFER_REQUEST  TxReq;

  /* set endpoint data */
  UsbdSetEpInfo (&(TxReq.ep_info), &(IoReq->EndpointInfo)); /* set endpoint data */

  /* if this is a control endpoint, set the number and direction */
  if (IoReq->EndpointInfo.EndpointDesc == NULL) {
    TxReq.ep_info.ep_num = 0;
    TxReq.ep_info.ep_dir = UsbEpDirIn;
  }

  /* setup the trasfer request */
  TxReq.xfer_buffer = IoReq->IoInfo.Buffer;
  TxReq.xfer_len = IoReq->IoInfo.Length;
  TxReq.xfer_done = UsbdXferDoneHndlr;

  DEBUG ((DEBUG_INFO,  "TX REQUEST: epNum: 0x%x, epDir: 0x%x, epType: 0x%x, MaxPktSize: 0x%x\n",\
          TxReq.ep_info.ep_num, TxReq.ep_info.ep_dir, TxReq.ep_info.ep_type, TxReq.ep_info.max_pkt_size));

  Status = usb_device_ep_tx_data (XdciHndl, &TxReq);

  return Status;
}


/**
  Queue a request to receive data

  @param XdciHndl  Pointer (handle) to the XDCI driver object
  @param IoReq     Pointer to IO structure containing details of the
                   receive request

  @return EFI_SUCCESS if operation succeeded, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdEpRxData (
  IN VOID               *XdciHndl,
  IN USB_DEVICE_IO_REQ  *IoReq
  )
{
  EFI_STATUS        Status = EFI_DEVICE_ERROR;
  USB_XFER_REQUEST  RxReq;
  UINT32            ReqPacket;

  DEBUG ((DEBUG_INFO,  "RX REQUEST in: IoReq->IoInfo.Length: 0x%x\n", IoReq->IoInfo.Length));
  DEBUG ((DEBUG_INFO,  "RX REQUEST in: MaxPacketSize: 0x%x\n", IoReq->EndpointInfo.EndpointDesc->MaxPacketSize));

  if (IoReq->EndpointInfo.EndpointDesc->MaxPacketSize == 0) {
    return EFI_DEVICE_ERROR;
  }

  /* set endpoint data */
  UsbdSetEpInfo (&(RxReq.ep_info), &(IoReq->EndpointInfo));

  /* setup the trasfer request */
  RxReq.xfer_buffer = IoReq->IoInfo.Buffer;

  //
  // Transfer length should be multiple of USB packet size.
  //
  ReqPacket = IoReq->IoInfo.Length / IoReq->EndpointInfo.EndpointDesc->MaxPacketSize;
  ReqPacket = ((IoReq->IoInfo.Length % IoReq->EndpointInfo.EndpointDesc->MaxPacketSize) == 0)? ReqPacket : ReqPacket + 1;
  RxReq.xfer_len = ReqPacket * IoReq->EndpointInfo.EndpointDesc->MaxPacketSize;

  RxReq.xfer_done = UsbdXferDoneHndlr;

  DEBUG ((DEBUG_INFO,  "RX REQUEST: epNum: 0x%x, epDir: 0x%x, epType: 0x%x\n",\
          RxReq.ep_info.ep_num, RxReq.ep_info.ep_dir, RxReq.ep_info.ep_type));
  DEBUG ((DEBUG_INFO,  "RX REQUEST send: xfer_len: 0x%x\n", RxReq.xfer_len));
//  DEBUG ((DEBUG_INFO,  "RX REQUEST send: xfer_len: 0x%x, RequirePkg: 0x%x\n", RxReq.xfer_len, RequirePkg));

  Status = usb_device_ep_rx_data (XdciHndl, &RxReq);

  return Status;
}


/**
  Callback used to handle Reset events from the XDCI

  @param Param Pointer to a generic callback parameter structure

  @return XDCI usb status

**/
EFI_STATUS
EFIAPI
UsbdResetEvtHndlr (
  IN USB_DEVICE_CALLBACK_PARAM  *Param
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO,  "UsbdResetEvtHndlr \n"));
  Status = UsbdResetHdlr ();

  return Status;
}


/**
  Callback used to handle Connection done events from the XDCI

  @param Param Pointer to a generic callback parameter structure

  @return XDCI usb status

**/
EFI_STATUS
EFIAPI
UsbdConnDoneEvtHndlr (
  IN USB_DEVICE_CALLBACK_PARAM *Param
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO,  "UsbdConnDoneEvtHndlr \n"));
  Status = UsbdConnDoneHdlr();

  return Status;
}


/**
  Callback used to handle Control Endpoint Setup events from the XDCI

  @param Param Pointer to a generic callback parameter structure

  @return XDCI usb status

**/
EFI_STATUS
EFIAPI
UsbdSetupEvtHndlr (
  IN USB_DEVICE_CALLBACK_PARAM *Param
  )
{
  EFI_STATUS              Status = EFI_SUCCESS;
  EFI_USB_DEVICE_REQUEST  Req;

  DEBUG ((DEBUG_INFO,  "UsbdSetupEvtHndlr \n"));

  /* Fill out request object from the incomming buffer */
  CopyMem (&Req, Param->buffer, sizeof(EFI_USB_DEVICE_REQUEST));

  Status = UsbdSetupHdlr (&Req);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UsbdSetupEvtHndlr: EFI_DEVICE_ERROR\n"));
  }

  return Status;
}


#ifdef SUPPORT_SUPER_SPEED
/**
 * Callback used to handle XferNotReady events from the XDCI
 *
 * @param Param Pointer to a generic callback parameter structure
 *
 * @return XDCI usb status
 */
EFI_STATUS
EFIAPI
UsbdNrdyEvtHndlr (
  IN USB_DEVICE_CALLBACK_PARAM *Param
  )
{
  DEBUG ((DEBUG_INFO,  "UsbdNrdyEvtHndlr \n"));
  return EFI_SUCCESS;
}
#endif


/**
  Registers callbacks for event handlers with the XDCI layer.
  The functions will be called as the registered events are triggered.

  @param  XdciHndl to XDCI core driver
  @return EFI_SUCCESS if successful, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdRegisterCallbacks (
  IN VOID  *XdciHndl
  )
{
  if (usb_device_register_callback (XdciHndl, USB_DEVICE_RESET_EVENT, UsbdResetEvtHndlr) != EFI_SUCCESS) {
    goto UdciRegCallbackError;
  }

  if (usb_device_register_callback (XdciHndl, USB_DEVICE_CONNECTION_DONE, UsbdConnDoneEvtHndlr) != EFI_SUCCESS) {
    goto UdciRegCallbackError;
  }

  if (usb_device_register_callback (XdciHndl, USB_DEVICE_SETUP_PKT_RECEIVED, UsbdSetupEvtHndlr) != EFI_SUCCESS) {
    goto UdciRegCallbackError;
  }

#ifdef SUPPORT_SUPER_SPEED
  if (usb_device_register_callback (XdciHndl, USB_DEVICE_XFER_NRDY, UsbdNrdyEvtHndlr) != EFI_SUCCESS) {
    goto UdciRegCallbackError;
  }
#endif

  return EFI_SUCCESS;

UdciRegCallbackError:
  return EFI_DEVICE_ERROR;
}


/**
  Returns the configuration descriptor for this device. The data
  buffer returned will also contain all downstream interface and
  endpoint buffers.

  @param Buffer    Pointer to destination buffer to copy descriptor data to
  @param DescIndex the index of the descriptor to return
  @param ReqLen    the length in bytes of the request buffer
  @param DataLen   Pointer whos value is to be filled with the byte count of
                   data copied to the output buffer

  @return EFI_SUCCESS if descritor successfully copied, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdGetConfigDesc (
  IN VOID      *Buffer,
  IN UINT8     DescIndex,
  IN UINT32    ReqLen,
  IN UINT32    *DataLen
  )
{
  EFI_STATUS             Status = EFI_DEVICE_ERROR;
  UINT8                  NumConfigs = 0;
  UINT32                 ConfigLen = 0;
  USB_DEVICE_CONFIG_OBJ  *ConfigObj = 0;
  VOID                   *Descriptor = 0;
  UINT32                 Length = 0;

  DEBUG ((DEBUG_INFO, "UsbdGetConfigDesc()\n"));

  /*
   * For a CONFIGURATION request we send back all descriptors branching out
   * from this descriptor including the INTERFACE and ENDPOINT descriptors
   */

  /* Verify the requested configuration exists - check valid index */
  NumConfigs = gDrvObj.UsbdDevObj->DeviceDesc->NumConfigurations;

  if (DescIndex < NumConfigs) {
    /* get the configuration object using the index offset */
    ConfigObj = (gDrvObj.UsbdDevObj->ConfigObjs + DescIndex);
    /* get the complete configuration buffer block including Interface and Endpoint data */
    Descriptor = ConfigObj->ConfigAll;
    /* The config descriptor TotalLength has the full value for all desc buffers */
    ConfigLen = ConfigObj->ConfigDesc->TotalLength;
    /* copy the data to the output buffer */
    Length = MIN (ReqLen, ConfigLen);
    CopyMem (Buffer, Descriptor, Length);
    *DataLen = Length;
    Status = EFI_SUCCESS;

    PrintConfigDescriptor (ConfigObj->ConfigDesc);
  } else {
    DEBUG ((DEBUG_INFO, "UsbdGetConfigDesc() - Invalid Config index: %i\n", DescIndex));
  }

  return Status;
}


/**
  Sets the active configuration to the selected configuration index if it exists

  @param CfgValue  the configuration value to set

  @return EFI_SUCCESS if the configuration was set, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdSetConfig (
  UINT8  CfgValue
  )
{
  EFI_STATUS                 Status = EFI_DEVICE_ERROR;
  UINT8                      numConfigs = 0;
  USB_DEVICE_CONFIG_OBJ      *pConfigObj = NULL;
  USB_DEVICE_INTERFACE_OBJ   *pIfObj = NULL;
  USB_DEVICE_ENDPOINT_OBJ    *pEpObj = NULL;
  UINT8                      cfgItr = 0;
  UINT8                      ifItr = 0;
  UINT8                      epItr = 0;
  USB_DEVICE_ENDPOINT_INFO   epInfo;
  USB_EP_INFO                UsbEpInfo;

  DEBUG ((DEBUG_INFO, "UsbdSetConfig()\n"));

  /* Verify the requested configuration exists - check valid index */
  numConfigs = gDrvObj.UsbdDevObj->DeviceDesc->NumConfigurations;

  if (CfgValue != 0) {
    /* Search for a matching configuration */
    for (cfgItr = 0; cfgItr < numConfigs; cfgItr++) {
      pConfigObj = (gDrvObj.UsbdDevObj->ConfigObjs + cfgItr);
      if (pConfigObj->ConfigDesc->ConfigurationValue == CfgValue) {

        /* Set the active configuration object */
        gDrvObj.ActiveConfigObj = pConfigObj;

        /* Find all interface objects for this configuration */
        for (ifItr = 0; ifItr < pConfigObj->ConfigDesc->NumInterfaces; ifItr++) {
          pIfObj = (pConfigObj->InterfaceObjs + ifItr);

          /* Configure the Endpoints in the XDCI */
          for (epItr = 0; epItr < pIfObj->InterfaceDesc->NumEndpoints; epItr++) {
            pEpObj = (pIfObj->EndpointObjs + epItr);

            epInfo.EndpointDesc = pEpObj->EndpointDesc;
            epInfo.EndpointCompDesc = pEpObj->EndpointCompDesc;

            if (UsbdInitEp(gDrvObj.XdciDrvObj, &epInfo) == EFI_SUCCESS) {
              UsbdSetEpInfo(&UsbEpInfo, &epInfo);
              if (usb_device_ep_enable(gDrvObj.XdciDrvObj, &UsbEpInfo) == EFI_SUCCESS) {
                Status = EFI_SUCCESS;
              } else {
                DEBUG ((DEBUG_INFO, "UsbdSetConfig() - Failed to enable endpoint\n"));
              }
            } else {
              DEBUG ((DEBUG_INFO, "UsbdSetConfig() - Failed to initialize endpoint\n"));
            }
          }
        }

        /* Let the class driver know it is configured */
        if (Status == EFI_SUCCESS) {
          if (gDrvObj.UsbdDevObj->ConfigCallback != NULL) {
            gDrvObj.UsbdDevObj->ConfigCallback (CfgValue);
          }
        }

        gDrvObj.State = UsbDevStateConfigured; /* we are now configured */

        break; /* break from config search loop */
      }
    }
  }

  if (EFI_ERROR (Status)) {
   DEBUG ((DEBUG_INFO, "UsbdSetConfig() - Invalid requested configuration value: %i\n", CfgValue));
  }

  return Status;
}


/**
  Returns the currently active configuration value

  @param Buffer    Pointer to destination buffer to copy configuration value to
  @param ReqLen    the length in bytes of the request buffer
  @param DataLen   Pointer whos value is to be filled with the byte count of
                   data copied to the output buffer

  @return EFI_SUCCESS if config value is successfully copied, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdGetConfig (
  VOID      *Buffer,
  UINT32    ReqLen,
  UINT32    *DataLen
  )
{
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  DEBUG ((DEBUG_INFO, "UsbdGetConfig()\n"));

  if (ReqLen >= 1) { /* length of data expected must be 1 */
    if (gDrvObj.ActiveConfigObj != NULL) { /* assure we have a config active */
      *DataLen = 1; /* one byte for ConfigurationValue */
      *(UINT8*)Buffer = gDrvObj.ActiveConfigObj->ConfigDesc->ConfigurationValue;

      Status = EFI_SUCCESS;
    } else {
      DEBUG ((DEBUG_INFO, "UsbdGetConfig() - No active configuration available\n"));
    }
  } else {
    DEBUG ((DEBUG_INFO, "UsbdGetConfig() - Invalid data length\n"));
  }

  return Status;
}


/**
  Returns the requested string descriptor if it exists

  @param Buffer    Pointer to destination buffer to copy descriptor data to
  @param DescIndex the index of the descriptor to return
  @param LangId    the target language ID
  @param ReqLen    the length in bytes of the request buffer
  @param DataLen   Pointer whos value is to be filled with the byte count of
                   data copied to the output buffer

  @return EFI_SUCCESS if descritor successfully copied, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdGetStringDesc (
  VOID      *Buffer,
  UINT8     DescIndex,
  UINT16    LangId,
  UINT32    ReqLen,
  UINT32    *DataLen
  )
{
  EFI_STATUS             Status = EFI_DEVICE_ERROR;
  UINT32                 Length = 0;
  USB_STRING_DESCRIPTOR  *StringDesc;
  UINT8                  Index = 0;
  UINT8                  StrLangEntries = 0;
  BOOLEAN                StrLangFound = FALSE;

  DEBUG ((DEBUG_INFO, "UsbdGetStringDesc: Index: 0x%x, LangId: 0x%x, ReqLen: 0x%x\n", DescIndex, LangId, ReqLen));

  /* index zero of the string table contains the supported language codes */
  if (DescIndex == 0) {
    StringDesc = (gDrvObj.UsbdDevObj->StringTable);
    Length = MIN (ReqLen, StringDesc->Length);
    CopyMem (Buffer, StringDesc, Length);
    *DataLen = Length;
    Status = EFI_SUCCESS;
  } else {

    /*
     * Verify the requested language ID is supported. String descriptor Zero
     * (First entry in the string table) is expected to contain the language list.
     * The requested language ID is specified in the Index member of the request.
     */
    StringDesc = gDrvObj.UsbdDevObj->StringTable; /* get language string descriptor */
    StrLangEntries = ((StringDesc->Length - 2) >> 1);
    DEBUG ((DEBUG_INFO, "StrLangEntries=%x\n", StrLangEntries));

    DEBUG ((DEBUG_INFO, "Looking LangID: \n"));

    for (Index = 0; Index < StrLangEntries; Index++) {
      DEBUG ((DEBUG_INFO, "LangID [%x]= %x\n", Index, StringDesc->LangID [Index]));

      if (StringDesc->LangID [Index] == LangId) {
        DEBUG ((DEBUG_INFO, "Found it\n"));
        StrLangFound = TRUE;
      }
    }



    /* If we found a matching language, attempt to get the string index requested */
    if (StrLangFound == TRUE) {
      DEBUG ((DEBUG_INFO, "UsbdGetStringDesc: StrLangFound=Found, DescIndex=%x, StrTblEntries=%x\n", DescIndex, gDrvObj.UsbdDevObj->StrTblEntries));

      if (DescIndex < gDrvObj.UsbdDevObj->StrTblEntries) {
        /* get the string descriptor for the requested index */
        StringDesc = (gDrvObj.UsbdDevObj->StringTable + DescIndex);

        Length = MIN (ReqLen, StringDesc->Length);
        DEBUG ((DEBUG_INFO, "ReqLen=%x, StringLength=%x, Length=%x\n", ReqLen, StringDesc->Length, Length));

        CopyMem (Buffer, StringDesc, Length);
        *DataLen = Length;
        Status = EFI_SUCCESS;
      } else {
        DEBUG ((DEBUG_INFO, "UsbdGetStringDesc: Invalid String index in USB_REQ_GET_DESCRIPTOR request\n"));
      }
    } else {
      DEBUG ((DEBUG_INFO, "UsbdGetStringDesc: Unsupported String Language ID for USB_REQ_GET_DESCRIPTOR request\n"));
    }
  }

  if (Status == EFI_SUCCESS) {
    PrintStringDescriptor (StringDesc);
  }
  return Status;
}


#ifdef SUPPORT_SUPER_SPEED
/**
  Returns the configuration descriptor for this device. The data
  buffer returned will also contain all downstream interface and
  endpoint buffers.

  @param Buffer    Pointer to destination buffer to copy descriptor data to
  @param ReqLen    the length in bytes of the request buffer
  @param DataLen   Pointer whos value is to be filled with the byte count of
                   data copied to the output buffer

  @return EFI_SUCCESS if descritor successfully copied, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdGetBOSDesc (
  IN VOID      *Buffer,
  IN UINT32    ReqLen,
  IN UINT32    *DataLen
  )
{
  EFI_USB_BOS_DESCRIPTOR  *BosDesc = 0;
  UINT32                  Length = 0;

  DEBUG ((DEBUG_INFO, "UsbdGetBOSDesc()\n"));

  BosDesc = gDrvObj.UsbdDevObj->BosDesc;
  Length = MIN (ReqLen, gDrvObj.UsbdDevObj->BosDesc->TotalLength);

  CopyMem(Buffer, BosDesc, Length);
  *DataLen = Length;

  PrintBOSDescriptor (BosDesc);

  return EFI_SUCCESS;
}
#endif

/**
  Returns the current status for Device/Interface/Endpoint

  @param Buffer    Pointer to destination buffer to copy descriptor data to
  @param ReqType   The type of status to get
  @param ReqLen    the length in bytes of the request buffer
  @param DataLen   Pointer whos value is to be filled with the byte count of
                   data copied to the output buffer

  @return EFI_SUCCESS if status successfully copied, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdGetStatus (
  VOID      *Buffer,
  UINT8     ReqType,
  UINT32    ReqLen,
  UINT32    *DataLen
  )
{
  EFI_STATUS  Status = EFI_DEVICE_ERROR;

  DEBUG ((DEBUG_INFO, "UsbdGetStatus()\n"));

  if (ReqLen >= 2) { /* length of data must be at least 2 bytes */
    switch (ReqType & USB_TARGET_MASK) {
      case USB_TARGET_DEVICE:
        *DataLen = 2; /* two byte for status */
        *(UINT16*)Buffer = USB_STATUS_SELFPOWERED;
        Status = EFI_SUCCESS;
        break;

      case USB_TARGET_INTERFACE:
        /* No implementation needed at this time */
        break;

      case USB_TARGET_ENDPOINT:
        /* No implementation needed at this time */
        /* Should specify if endpoint is halted. Implement as necessary. */
        break;

      case USB_TARGET_OTHER:
        /* No implementation needed at this time */
        break;

      default:
        break;
    }
  } else {
    DEBUG ((DEBUG_INFO, "UsbdGetStatus() - Invalid data length\n"));
  }

  return Status;
}


/**
  Sets the address of the device

  @param address   the address value to set

  @return EFI_SUCCESS if address was set, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdSetAddress (
  UINT8    Address
  )
{
  EFI_STATUS  Status = EFI_DEVICE_ERROR;

  DEBUG ((DEBUG_INFO, "UsbdSetAddress: setting address: 0x%x\n", Address));

  if (Address <= 0x7F) { /* address must not be > 127 */
    gDrvObj.Address = Address;

    /* Configure Address in the XDCI */
    Status = usb_device_set_address (gDrvObj.XdciDrvObj, gDrvObj.Address);
    if (!EFI_ERROR (Status)) {
      gDrvObj.State = UsbDevStateAddress;
    } else {
      DEBUG ((DEBUG_INFO, "UsbdSetAddress: Failed to set address in XDCI\n"));
    }
  } else {
    DEBUG ((DEBUG_INFO, "UsbdSetAddress: Invalid address: 0x%x\n", Address));
  }

  return Status;
}


/**
  Handles Setup device requests. Standard requests are immediately
  handled here, and any Class/Vendor specific requests are forwarded
  to the class driver

  @param CtrlRequest  Pointer to a device request

  @return EFI_SUCCESS if request successfully handled, FALSE otherwise

**/
EFI_STATUS
UsbdSetupHdlr (
  IN EFI_USB_DEVICE_REQUEST    *CtrlRequest
  )
{
  EFI_STATUS              Status = EFI_DEVICE_ERROR;
  UINT8                   DescIndex = 0;
  USB_DEVICE_DESCRIPTOR   *DevDesc = 0;

  /* Initialize the IO object */
  gCtrlIoReq.IoInfo.Length = 0;

  DEBUG ((DEBUG_INFO, "UsbdSetupHdlr start\n"));
  PrintDeviceRequest (CtrlRequest);

  /* Handle Standard Device Requests */
  if ((CtrlRequest->RequestType & USB_REQ_TYPE_MASK) == USB_REQ_TYPE_STANDARD) {
    switch (CtrlRequest->Request) {
      case USB_REQ_GET_DESCRIPTOR:
        DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Host requests get descriptor\n"));
        if (CtrlRequest->RequestType == USB_RT_TX_DIR_D_TO_H) {
          DescIndex = (CtrlRequest->Value & 0xff); /* low byte is the index requested */
          switch (CtrlRequest->Value >> 8) { /* high byte contains request type */
            case USB_DESC_TYPE_DEVICE:
              DEBUG ((DEBUG_INFO, "Descriptor tyep: Device\n"));
              DevDesc = gDrvObj.UsbdDevObj->DeviceDesc;
              /* copy the data to the output buffer */
              gCtrlIoReq.IoInfo.Length = MIN (CtrlRequest->Length, DevDesc->Length);
              CopyMem(gCtrlIoReq.IoInfo.Buffer, DevDesc, gCtrlIoReq.IoInfo.Length);
              PrintDeviceDescriptor (DevDesc);
              break;

            case USB_DESC_TYPE_CONFIG:
              DEBUG ((DEBUG_INFO, "Descriptor tyep: Configuration\n"));
              Status = UsbdGetConfigDesc (
                         gCtrlIoReq.IoInfo.Buffer,
                         DescIndex,
                         CtrlRequest->Length,
                         &(gCtrlIoReq.IoInfo.Length)
                         );
              break;

            case USB_DESC_TYPE_STRING:
              DEBUG ((DEBUG_INFO, "Descriptor tyep: String\n"));
              Status = UsbdGetStringDesc (
                         gCtrlIoReq.IoInfo.Buffer,
                         DescIndex,
                         CtrlRequest->Index,
                         CtrlRequest->Length,
                         &(gCtrlIoReq.IoInfo.Length)
                         );
              break;

#ifdef SUPPORT_SUPER_SPEED
            case USB_DESC_TYPE_BOS:
              DEBUG ((DEBUG_INFO, "Descriptor tyep: BOS\n"));
              Status = UsbdGetBOSDesc (
                         gCtrlIoReq.IoInfo.Buffer,
                         CtrlRequest->Length,
                         &(gCtrlIoReq.IoInfo.Length)
                         );
              break;

            case USB_DESC_TYPE_SS_ENDPOINT_COMPANION:
              DEBUG ((DEBUG_INFO, "Descriptor tyep: Endpoint Companion\n"));
              break;
#endif

            default:
              DEBUG ((DEBUG_INFO, "Descriptor tyep: Unsupported, USB_REQ_GET_DESCRIPTOR request: 0x%x\n", (CtrlRequest->Value >> 8)));
              break;
          }
        } else {
          DEBUG ((DEBUG_INFO, "UsbdSetupHdlr() - Invalid direction for USB_REQ_GET_DESCRIPTOR request\n"));
        }
        break;

      case USB_REQ_GET_CONFIG:
        DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Host requests get configuration\n"));
        if (CtrlRequest->RequestType == USB_RT_TX_DIR_D_TO_H) {
          Status = UsbdGetConfig (gCtrlIoReq.IoInfo.Buffer, CtrlRequest->Length, &(gCtrlIoReq.IoInfo.Length));
        } else {
          DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Invalid direction for USB_REQ_GET_CONFIG request\n"));
        }
        break;

      case USB_REQ_SET_CONFIG:
        DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Host requests set configuration\n"));
        if (CtrlRequest->RequestType == USB_RT_TX_DIR_H_TO_D) {
          Status = UsbdSetConfig ((UINT8)CtrlRequest->Value);
        } else {
          DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Invalid direction for USB_REQ_SET_CONFIG request\n"));
        }
        break;

      case USB_REQ_SET_ADDRESS:
        if (CtrlRequest->RequestType == USB_RT_TX_DIR_H_TO_D) {
          Status = UsbdSetAddress ((UINT8)CtrlRequest->Value);
        } else {
          DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Invalid direction for USB_REQ_SET_ADDRESS request\n"));
        }
        break;

      case USB_REQ_GET_STATUS:
        if (CtrlRequest->RequestType & USB_RT_TX_DIR_D_TO_H) {
          Status = UsbdGetStatus (gCtrlIoReq.IoInfo.Buffer, CtrlRequest->RequestType, CtrlRequest->Length, &(gCtrlIoReq.IoInfo.Length));
        } else {
          DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Invalid direction for USB_REQ_GET_STATUS request\n"));
        }
        break;
#ifdef SUPPORT_SUPER_SPEED
      case USB_REQ_CLEAR_FEATURE:
      case USB_REQ_SET_FEATURE:
      case USB_REQ_SET_DESCRIPTOR:
      case USB_REQ_GET_INTERFACE:
      case USB_REQ_SET_INTERFACE:
      case USB_REQ_SYNCH_FRAME:
#endif
      default:
         DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Unsupported Standard Request: 0x%x\n", CtrlRequest->Request));
          break;
    }
  } else { /* This is not a Standard request, it specifies Class/Vendor handling */
    /* Forward request to class driver */
    DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Class/Vendor Request\n"));
    if (gDrvObj.UsbdDevObj->SetupCallback != NULL) {
      gDrvObj.UsbdDevObj->SetupCallback (CtrlRequest, &(gCtrlIoReq.IoInfo));
    }
  }

  DEBUG ((DEBUG_INFO, "dataLen=%x\n", gCtrlIoReq.IoInfo.Length));

  /* Transfer data according to request if necessary */
  if (gCtrlIoReq.IoInfo.Length> 0) {
    Status = UsbdEpTxData(gDrvObj.XdciDrvObj, &gCtrlIoReq);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Failed to TX data\n"));
    }
  } else {
    /* If we are not responding with data, send control status */
    Status = usb_device_ep0_tx_status (gDrvObj.XdciDrvObj);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_INFO, "UsbdSetupHdlr: Failed to Tx Ep0 Status\n"));
    }
  }

  return Status;
}


/**
  Handles device reset events. Sets the device address to zero.

  @return EFI_SUCCESS if able to set the address, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdResetHdlr (
  VOID
  )
{
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  DEBUG ((DEBUG_INFO, "UsbdResetHdlr()\n"));

  /* reset device address to 0 */
  Status = usb_device_set_address (gDrvObj.XdciDrvObj, 0x0);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UsbdResetHdlr() - Failed to set address in XDCI\n"));
  }

  return Status;
}


/**
  Handles Connection done events. Sets the device address to zero.

  @return EFI_SUCCESS if able to set the address, EFI_DEVICE_ERROR otherwise

**/
EFI_STATUS
UsbdConnDoneHdlr (
  VOID
  )
{
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  DEBUG ((DEBUG_INFO, "UsbdConnDoneHdlr()\n"));

  /* reset device address to 0 */
  Status = usb_device_set_address (gDrvObj.XdciDrvObj, 0x0);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "UsbdConnDoneHdlr() - Failed to set address in XDCI\n"));
  }

  /* set the device state to attached/connected */
  gDrvObj.State = UsbDevStateAttached;

  return Status;
}


/**
  Handles transmit/receive completion events. Directly handles
  control endpoint events and forwards class/vendor specific events
  to the class drivers.

  @param   XferInfo   Pointer to xfer structure

  @return

**/
VOID
UsbdXferDoneHdlr (
  IN EFI_USB_DEVICE_XFER_INFO    *XferInfo
  )
{
  //
  // If this is a non-control transfer complete, notify the class driver
  //
  if (XferInfo->EndpointNum > 0) {
    if (gDrvObj.UsbdDevObj->DataCallback != NULL) {
      gDrvObj.UsbdDevObj->DataCallback (XferInfo);
    }
  }

  return;
}


/**
  Binds a USB class driver with this USB device driver core.
  After calling this routine, the driver is ready to begin
  USB processing.

  @param  UsbdDevObj   Pointer to a usbd device object which contains
                       all relevant information for the class driver device

  @return TRUE if binding was successful, FALSE otherwise

**/
EFI_STATUS
EFIAPI
UsbDeviceBind (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This,
  IN USB_DEVICE_OBJ                             *UsbdDevObj
  )
{
  EFI_STATUS  Status = EFI_SUCCESS;

  /* allocate Tx buffer */
  gCtrlIoReq.IoInfo.Buffer = AllocateZeroPool (USB_EPO_MAX_PKT_SIZE_ALL);
  if (gCtrlIoReq.IoInfo.Buffer != NULL) {
    gDrvObj.UsbdDevObj = UsbdDevObj;
    gDrvObj.ActiveConfigObj = NULL;
    gDrvObj.Address = 0;
    gDrvObj.State = UsbDevStateInit;
  } else {
    DEBUG ((DEBUG_INFO, "UsbDeviceBind() - Failed to allocate IO Buffer\n"));
    Status = EFI_DEVICE_ERROR;
  }

  return Status;
}


/**
  Unbinds the USB class driver from this USB device driver core.

  @return TRUE if successful, FALSE otherwise

**/
EFI_STATUS
EFIAPI
UsbDeviceUnbind (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This
  )
{
  gDrvObj.UsbdDevObj = NULL;
  gDrvObj.ActiveConfigObj = NULL;
  gDrvObj.Address = 0;
  gDrvObj.State = UsbDevStateOff;
  gDrvObj.XdciInitialized = FALSE;

  /* release allocated buffer data */
  if (gCtrlIoReq.IoInfo.Buffer) {
    FreePool (gCtrlIoReq.IoInfo.Buffer);
  }

  return EFI_SUCCESS;
}


/**
  Performs continual USB device event processing until a cancel
  event occurs

  @param   TimeoutMs   Connection timeout in ms. If 0, waits forever.
  @return  TRUE if run executed normally, FALSE if error ocurred

**/
EFI_STATUS
EFIAPI
UsbDeviceRun (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This,
  IN UINT32                                     TimeoutMs
  )
{
  EFI_STATUS   Status = EFI_DEVICE_ERROR;

  /* can only run if XDCI is initialized */
  if (gDrvObj.XdciInitialized == TRUE) {

    gRun = TRUE; /* set the run flag to active */
    Status = EFI_SUCCESS;

    /* start the Event processing loop */
    DEBUG ((DEBUG_INFO, "UsbDeviceRun() - Starting event processing...\n"));
    while (1) {
      if (usb_device_isr_routine (gDrvObj.XdciDrvObj) != EFI_SUCCESS) {
        DEBUG ((DEBUG_INFO, "UsbDeviceRun() - Failed to execute event ISR\n"));
      }

      /* Check if a run cancel request exists, if so exit processing loop */
      if (gRun == FALSE) {
        Status = EFI_SUCCESS;
        DEBUG ((DEBUG_INFO, "UsbDeviceRun() - processing was cancelled\n"));
        break;
      }

      /* check for timeout */
      if (TimeoutMs == 0)
        return EFI_TIMEOUT;
      gBS->Stall (50);
      TimeoutMs--;
    }
  }

  return Status;
}


/**
  Sets a flag to stop the running device processing loop

  @return TRUE always

**/
EFI_STATUS
EFIAPI
UsbDeviceStop (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This
  )
{
  gRun = FALSE; /* set run flag to FALSE to stop processing */
  return EFI_SUCCESS;
}


EFI_STATUS
EFIAPI
UsbDeviceInitXdci (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This
  )
{
  EFI_STATUS            Status = EFI_DEVICE_ERROR;
  USB_XDCI_DEV_CONTEXT  *XdciDevContext;

  DEBUG ((EFI_D_ERROR, "UsbDeviceInitXdci\n"));
  XdciDevContext = USBUSBD_CONTEXT_FROM_PROTOCOL (This);

  UsbPlatformSpecificInit ();

  if (gDrvObj.XdciInitialized == FALSE) {
    if (XdciDevContext->XdciMmioBarAddr != 0) {

      /* Initialize device controller driver */
      DEBUG ((DEBUG_INFO, "UsbDeviceInitXdci() - Initializing Controller...\n"));

      /* Initialize the device controller interface */
      if (UsbdInit (XdciDevContext->XdciMmioBarAddr, &gDrvObj.XdciDrvObj) == EFI_SUCCESS) {

        /* Setup callbacks */
        if (UsbdRegisterCallbacks (gDrvObj.XdciDrvObj) == EFI_SUCCESS) {

          gDrvObj.XdciInitialized = TRUE;
          Status = EFI_SUCCESS;

          DEBUG ((DEBUG_INFO, "UsbDeviceInitXdci() - Controller initialization complete\n"));
        } else {
          DEBUG ((DEBUG_INFO, "UsbDeviceInitXdci() - Failed to register UDCI callbacks\n"));
        }
      } else {
        DEBUG ((DEBUG_INFO, "UsbDeviceInitXdci() - Failed to initialize UDCI\n"));
      }
    } else {
      DEBUG ((DEBUG_INFO, "UsbDeviceInitXdci() - XDCI MMIO BAR not set\n"));
    }
  } else {
    DEBUG ((DEBUG_INFO, "UsbDeviceInitXdci() - XDCI already initialized\n"));
    Status = EFI_ALREADY_STARTED;
  }

  return Status;
}


EFI_STATUS
EFIAPI
UsbDeviceConnect(
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This
  )
{
  EFI_STATUS  Status = EFI_DEVICE_ERROR;

  DEBUG ((DEBUG_INFO,  "UsbDeviceConnect \n"));
  if (usb_device_connect (gDrvObj.XdciDrvObj) == EFI_SUCCESS) {
    Status = EFI_SUCCESS;
  }
  return Status;
}


EFI_STATUS
EFIAPI
UsbDeviceDisConnect(
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This
  )
{
  EFI_STATUS  Status = EFI_DEVICE_ERROR;

  DEBUG ((DEBUG_INFO,  "UsbDeviceDisConnect \n"));
  if (usb_device_disconnect (gDrvObj.XdciDrvObj) == EFI_SUCCESS) {
    gDrvObj.State = UsbDevStateInit;
    Status = EFI_SUCCESS;
  }
  return Status;
}


EFI_STATUS
EFIAPI
UsbDeviceEpTxData(
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This,
  IN USB_DEVICE_IO_REQ                          *IoRequest
  )
{
  EFI_STATUS  Status;

  Status = UsbdEpTxData (gDrvObj.XdciDrvObj, IoRequest);
  return Status;
}


EFI_STATUS
EFIAPI
UsbDeviceEpRxData(
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This,
  IN USB_DEVICE_IO_REQ                          *IoRequest
  )
{
  EFI_STATUS  Status;

  Status = UsbdEpRxData (gDrvObj.XdciDrvObj, IoRequest);
  return Status;
}


//
// The Runtime UsbDeviceMode Protocol instance produced by this driver
//
EFI_USB_DEVICE_MODE_PROTOCOL  mUsbDeviceModeProtocol = {
  UsbDeviceInitXdci,
  UsbDeviceConnect,
  UsbDeviceDisConnect,
  UsbDeviceEpTxData,
  UsbDeviceEpRxData,
  UsbDeviceBind,
  UsbDeviceUnbind,
  UsbDeviceRun,
  UsbDeviceStop
};

#ifdef _MSC_VER
#pragma optimize ("", on)
#endif

/** @file
  Implementation for wrapper functions of XDCI APIs.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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


#include <Library/UsbDeviceLib.h>
#include "XdciCommon.h"
#include "XdciDevice.h"
#include "XdciInterface.h"
#include "UsbDeviceMode.h"

/**
  This function is used to initialize the device controller
  @config_params: Parameters from app to configure the core
  @dev_core_handle: Return parameter for upper layers to use
  for all HW-independent APIs

**/
EFI_STATUS
usb_device_init (
  IN USB_DEV_CONFIG_PARAMS    *ConfigParams,
  IN OUT VOID                 **DevCoreHandle
  )
{
  USB_DEV_CORE    *DevCorePtr;
  EFI_STATUS      Status = EFI_INVALID_PARAMETER;

  DEBUG ((DEBUG_INFO, "Call usb_device_init start\n"));

  /* Allocate device handle */
  DevCorePtr = AllocateZeroPool (sizeof (USB_DEV_CORE));
  DEBUG ((DEBUG_INFO, "device handle = 0x%x\n", DevCorePtr));

  if (DevCorePtr == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_init. ERROR: Failed to allocate memory\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  DEBUG ((DEBUG_INFO, "call usb_device_get_core_driver, ID=%x, \n", ConfigParams->ControllerId));

  /* Get the driver for this USB device core */
  DevCorePtr->core_driver = usb_device_get_core_driver(ConfigParams->ControllerId);
  if (DevCorePtr->core_driver != NULL) {
    DEBUG ((DEBUG_INFO, "call dev_core_init\n"));
    Status = DevCorePtr->core_driver->dev_core_init(
                                        ConfigParams,
                                        (VOID*)DevCorePtr,
                                        &DevCorePtr->controller_handle);
  } else {
    DEBUG ((DEBUG_INFO, "usb_device_init. ERROR: Driver not found\n"));
    return EFI_INVALID_PARAMETER;
  }

  *DevCoreHandle = (VOID *)DevCorePtr;
  return Status;
}

/**
  This function is used to de-initialize the device controller
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @flags: Flags indicating what type of de-initialization is required

**/
EFI_STATUS
usb_device_deinit (
  IN VOID      *DevCoreHandle,
  IN UINT32    Flags
  )
{
  USB_DEV_CORE    *Core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS      Status = EFI_DEVICE_ERROR;

  if (Core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_deinit: ERROR: INVALID HANDLE\n"));
  } else {
    if (Core->core_driver != NULL) {
      Status = Core->core_driver->dev_core_deinit(
                                    Core->controller_handle,
                                    Flags
                                    );
      FreePool(DevCoreHandle);
    } else {
      DEBUG ((DEBUG_INFO, "usb_device_deinit: Driver not found\n"));
      Status = EFI_INVALID_PARAMETER;
    }
  }

  return Status;
}

/**
  This function is used to register callback function for
  specified event
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @event: Event for which callback is to be registered
  @callback_fn: Callback function to be called by the
  controller driver for above event after critical processing

**/
EFI_STATUS
usb_device_register_callback (
  IN VOID                      *DevCoreHandle,
  IN USB_DEVICE_EVENT_ID       EventId,
  IN USB_DEVICE_CALLBACK_FUNC  CallbackFunc
  )
{
  EFI_STATUS    Status = EFI_DEVICE_ERROR;
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;

  DEBUG ((DEBUG_INFO, "usb_device_register_callback start\n"));

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_register_callback: ERROR: INVALID HANDLE\n"));
  } else {
    if (core->core_driver != NULL) {
      DEBUG ((DEBUG_INFO, "Call dev_core_register_callback\n"));
      Status = core->core_driver->dev_core_register_callback (
                                    core->controller_handle,
                                    EventId,
                                    CallbackFunc
                                    );
    }
  }

  return Status;
}

/**
  This function is used to register callback function for
  specified event
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @event_id: Event for which callback is to be unregistered

**/
EFI_STATUS
usb_device_unregister_callback (
  IN VOID                      *DevCoreHandle,
  IN USB_DEVICE_EVENT_ID       EventId
  )
{
  EFI_STATUS    Status = EFI_DEVICE_ERROR;
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_unregister_callback: ERROR: INVALID HANDLE\n"));
  } else {
    if (core->core_driver != NULL) {
      Status = core->core_driver->dev_core_unregister_callback(
                                    core->controller_handle,
                                    EventId
                                    );
    }
  }

  return Status;
}

/**
  This function is used to service interrupt events on device
  controller. Use this API in your OS/stack-specific ISR framework
  In polled mode scenario, invoke this API in a loop to service the
  events
  @dev_core_handle: Handle to HW-independent APIs for device
  controller

**/
EFI_STATUS
usb_device_isr_routine (
  IN VOID                      *DevCoreHandle
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_isr_routine: ERROR: INVALID HANDLE\n"));
  } else {
    if (core->core_driver != NULL) {
      Status = core->core_driver->dev_core_isr_routine (core->controller_handle);
    }
  }

  return Status;
}

/**
  This function is used to enable device controller to connect
  to USB host
  @dev_core_handle: Handle to HW-independent APIs for device
  controller

**/
EFI_STATUS
usb_device_connect (
  IN VOID                      *DevCoreHandle
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_connect: ERROR: INVALID HANDLE\n"));
  } else {
    DEBUG ((DEBUG_INFO, "usb_device_connect\n"));
    Status = core->core_driver->dev_core_connect (core->controller_handle);
  }

  return Status;
}

/**
  This function is used to disconnect device controller
  from USB host
  @dev_core_handle: Handle to HW-independent APIs for device
  controller

**/
EFI_STATUS
usb_device_disconnect (
  IN VOID                      *DevCoreHandle
  )
{
  USB_DEV_CORE  *core =(USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_disconnect: ERROR: INVALID HANDLE\n"));
  } else {
    DEBUG ((DEBUG_INFO, "usb_device_disconnect\n"));
    Status = core->core_driver->dev_core_disconnect(core->controller_handle);
  }

  return Status;
}

/**
  This function is used to obtain USB bus speed after bus reset complete
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @speed: negotiated speed

**/
EFI_STATUS
usb_device_get_speed (
  IN VOID                      *DevCoreHandle,
  IN USB_SPEED                 *Speed
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_get_speed: ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_get_speed(core->controller_handle, Speed);
  }

  return Status;
}

/**
  This function is used to set USB device address
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @address: USB device address to set

**/
EFI_STATUS
usb_device_set_address (
  IN VOID                      *DevCoreHandle,
  IN UINT32                    Address
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  DEBUG ((DEBUG_INFO, "usb_device_set_address: enter......\n"));
  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_set_address: ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_set_address(core->controller_handle, Address);
  }
  DEBUG ((DEBUG_INFO, "usb_device_set_address: exit......\n"));

  return Status;
}

/**
  This function is used to do device controller-specific processing
  of set configuration device framework request
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @config_num: configuration number selected by USB host

**/
EFI_STATUS
usb_device_set_configuration (
  IN VOID                      *DevCoreHandle,
  IN UINT32                    ConfigNum
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_set_configuration: ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_set_config (core->controller_handle, ConfigNum);
  }

  return Status;
}

/**
  This function is used to set desired link state in device controller
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @state: Desired link state

**/
EFI_STATUS
usb_device_set_link_state (
  IN VOID                      *DevCoreHandle,
  IN USB_DEVICE_SS_LINK_STATE  State
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_set_link_state: ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_set_link_state (core->controller_handle, State);
  }

  return Status;
}

/**
  This function is used to initialize non-EP0 endpoints
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @ep_info: Endpoint information for EP to be initialized

**/
EFI_STATUS
usb_device_init_ep (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_init_ep: ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_init_ep (core->controller_handle, EpInfo);
  }

  return Status;
}

/**
  This function is used to enable an endpoint
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @ep_info: Endpoint information for EP to be enabled

**/
EFI_STATUS
usb_device_ep_enable (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep_enable: ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep_enable (core->controller_handle, EpInfo);
  }

  return Status;
}

/**
  This function is used to disable an endpoint
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @ep_info: Endpoint information for EP to be disabled

**/
EFI_STATUS
usb_device_ep_disable (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep_disable ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep_disable (core->controller_handle, EpInfo);
  }

  return Status;
}

/**
  This function is used to STALL an endpoint
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @ep_info: Endpoint information for EP to be stalled

**/
EFI_STATUS
usb_device_ep_stall (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep_stall ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep_stall (core->controller_handle, EpInfo);
  }

  return Status;
}

/**
  This function is used to clear STALL on an endpoint
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @ep_info: Endpoint information for which STALL needs to be cleared

**/
EFI_STATUS
usb_device_ep_clear_stall (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep_clear_stall ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep_clear_stall (core->controller_handle, EpInfo);
  }

  return Status;
}

/**
  This function is used to set EP not ready state
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @ep_info: Endpoint information for EP that needs to be
  set in not ready state

**/
EFI_STATUS
usb_device_ep_set_nrdy (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep_set_nrdy ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep_set_nrdy (core->controller_handle, EpInfo);
  }

  return Status;
}

/**
  This function is used to queue request to receive SETUP packet
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @buffer: Buffer (bus-width aligned) where SETUP packet
  needs to be received

**/
EFI_STATUS
usb_device_ep0_rx_setup (
  IN VOID                      *DevCoreHandle,
  IN UINT8                     *Buffer
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep0_rx_setup ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep0_rx_setup_pkt (core->controller_handle, Buffer);
  }

  return Status;
}

/**
  This function is used to queue request to receive status phase
  for control transfer on EP0
  @dev_core_handle: Handle to HW-independent APIs for device
  controller

**/
EFI_STATUS
usb_device_ep0_rx_status (
  IN VOID                      *DevCoreHandle
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep0_rx_status ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep0_rx_status_pkt (core->controller_handle);
  }
  return Status;
}

/**
  This function is used to queue request to send status phase for
  control transfer on EP0
  @dev_core_handle: Handle to HW-independent APIs for device
  controller

**/
EFI_STATUS
usb_device_ep0_tx_status (
  IN VOID                      *DevCoreHandle
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep0_tx_status ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep0_tx_status_pkt (core->controller_handle);
  }

  return Status;
}

/**
  This function is used to queue a single request to transmit data on
  an endpoint. If more than one request need to be queued before
  previous requests complete then a request queue needs to be
  implemented in upper layers. This API should be not be invoked until
  current request completes.
  Callback for transfer completion is invoked when requested transfer length
  is reached or if a short packet is received
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @xfer_req: Address to transfer request describing this transfer

**/
EFI_STATUS
usb_device_ep_tx_data (
  IN VOID                      *DevCoreHandle,
  IN USB_XFER_REQUEST          *XferReq
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep_tx_data ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep_tx_data (core->controller_handle, XferReq);
  }

  return Status;
}

/**
  This function is used to queue a single request to receive data on
  an endpoint. If more than one request need to be queued before
  previous requests complete then a request queue needs to be implemented
  in upper layers. This API should be not be invoked until current request
  completes.
  Callback for transfer completion is invoked when requested transfer length
  is reached or if a short packet is received
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @xfer_req: Address to transfer request describing this transfer

**/
EFI_STATUS
usb_device_ep_rx_data (
  IN VOID                      *DevCoreHandle,
  IN USB_XFER_REQUEST          *XferReq
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep_rx_data ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep_rx_data (core->controller_handle, XferReq);
  }

  return Status;
}

/**
  This function is used to cancel a transfer request that was
  previously queued on an endpoint
  @dev_core_handle: Handle to HW-independent APIs for device
  controller
  @ep_info: Endpoint info where transfer needs to be cancelled

**/
EFI_STATUS
usb_device_ep_cancel_transfer (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *ep_info
  )
{
  USB_DEV_CORE  *core = (USB_DEV_CORE *)DevCoreHandle;
  EFI_STATUS    Status = EFI_DEVICE_ERROR;

  if (core == NULL) {
    DEBUG ((DEBUG_INFO, "usb_device_ep_cancel_transfer ERROR: INVALID HANDLE\n"));
  } else {
    Status = core->core_driver->dev_core_ep_cancel_transfer (core->controller_handle, ep_info);
  }

  return Status;
}

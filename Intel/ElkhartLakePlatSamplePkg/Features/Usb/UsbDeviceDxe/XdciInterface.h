/** @file
  Header file for table of XDCI core APIs.

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


#ifndef _USB_DCD_IF_H_
#define _USB_DCD_IF_H_

/* Core driver for device controller
 * @dev_core_init: Intializes device controller
 * @dev_core_deinit: De-initializes device controller
 * @dev_core_register_callback: Registers callback function for
 * an event to be called by the controller driver
 * @dev_core_unregister_callback: Unregisters callback function
 * for an event
 * @dev_core_isr_routine: core interrupt service routine for
 * device controller to be used by OS/stack-i/f layer
 * @dev_core_connect: Enable device controller to connect to USB host
 * @dev_core_disconnect: Soft disconnect device controller from
 * USB host
 * @dev_core_get_speed: Get USB bus speed on which device controller
 * is attached
 * @dev_core_set_address: Set USB device address in device controller
 * @dev_core_set_config: Set configuration number for device controller
 * @dev_core_set_link_state: Set link state for device controller
 * @dev_core_init_ep: Initialize non-EP0 endpoint
 * @dev_core_ep_enable: Enable endpoint
 * @dev_core_ep_disable: Disable endpoint
 * @dev_core_ep_stall: Stall/Halt endpoint
 * @dev_core_ep_clear_stall: Clear Stall/Halt on endpoint
 * @dev_core_ep_set_nrdy: Set endpoint to not ready state
 * @dev_core_ep0_rx_setup_pkt: Receive SETUP packet on EP0
 * @dev_core_ep0_rx_status_pkt: Receive status packet on EP0
 * @dev_core_ep0_tx_status_pkt: Transmit status packet from EP0
 * @dev_core_ep_tx_data: Transmit data from EP
 * @dev_core_ep_rx_data: Received data on EP
 * @dev_core_ep_cancel_transfer: Cancel transfer on EP
 */

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_INIT) (
  IN USB_DEV_CONFIG_PARAMS     *ConfigParams,
  IN VOID                      *parent_handle,
  IN VOID                      **core_handle
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_DEINIT) (
  IN VOID                      *core_handle,
  IN UINT32                    flags
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_REG_CALLBACK) (
  IN VOID                      *core_handle,
  IN USB_DEVICE_EVENT_ID       event,
  IN EFI_STATUS                (EFIAPI *callback_fn)(IN USB_DEVICE_CALLBACK_PARAM *cb_event_params)
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_UNREG_CALLBACK) (
  IN VOID                      *core_handle,
  IN USB_DEVICE_EVENT_ID       event
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_ISR_ROUTINE) (
  IN VOID                      *core_handle
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_CONNECT) (
  IN VOID                      *core_handle
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_DISCONNECT) (
  IN VOID                      *core_handle
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_GET_SPEED) (
  IN VOID                      *core_handle,
  IN USB_SPEED                 *speed
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_SET_ADDRESS) (
  IN VOID                      *core_handle,
  IN UINT32                    address
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_SET_CONFIG) (
  IN VOID                      *core_handle,
  IN UINT32                    config_num
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_SET_LINK_STATE) (
  IN VOID                      *core_handle,
  IN USB_DEVICE_SS_LINK_STATE  state
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_INIT_EP) (
  IN VOID                      *core_handle,
  IN USB_EP_INFO               *ep_info
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP_ENABLE) (
  IN VOID                      *core_handle,
  IN USB_EP_INFO               *ep_info
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP_DISABLE) (
  IN VOID                      *core_handle,
  IN USB_EP_INFO               *ep_info
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP_STALL) (
  IN VOID                      *core_handle,
  IN USB_EP_INFO               *ep_info
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP_CLEAR_STALL) (
  IN VOID                      *core_handle,
  IN USB_EP_INFO               *ep_info
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP_SET_NRDY) (
  IN VOID                      *core_handle,
  IN USB_EP_INFO               *ep_info
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP0_RX_SETUP_PKT) (
  IN VOID                      *core_handle,
  IN UINT8                     *buffer
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP0_RX_STATUS_PKT) (
  IN VOID                      *core_handle
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP0_TX_STATUS_PKT) (
  IN VOID                      *core_handle
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP_TX_DATA) (
  IN VOID                      *core_handle,
  IN USB_XFER_REQUEST          *xfer_handle
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP_RX_DATA) (
  IN VOID                      *core_handle,
  IN USB_XFER_REQUEST          *xfer_handle
  );

typedef
EFI_STATUS
(EFIAPI *DEV_CORE_EP_CANCEL_TRANSFER) (
  IN VOID                      *core_handle,
  IN USB_EP_INFO               *ep_info
  );

struct usb_device_core_driver {
  DEV_CORE_INIT                 dev_core_init;
  DEV_CORE_DEINIT               dev_core_deinit;
  DEV_CORE_REG_CALLBACK         dev_core_register_callback;
  DEV_CORE_UNREG_CALLBACK       dev_core_unregister_callback;
  DEV_CORE_ISR_ROUTINE          dev_core_isr_routine;
  DEV_CORE_CONNECT              dev_core_connect;
  DEV_CORE_DISCONNECT           dev_core_disconnect;
  DEV_CORE_GET_SPEED            dev_core_get_speed;
  DEV_CORE_SET_ADDRESS          dev_core_set_address;
  DEV_CORE_SET_CONFIG           dev_core_set_config;
  DEV_CORE_SET_LINK_STATE       dev_core_set_link_state;
  DEV_CORE_INIT_EP              dev_core_init_ep;
  DEV_CORE_EP_ENABLE            dev_core_ep_enable;
  DEV_CORE_EP_DISABLE           dev_core_ep_disable;
  DEV_CORE_EP_STALL             dev_core_ep_stall;
  DEV_CORE_EP_CLEAR_STALL       dev_core_ep_clear_stall;
  DEV_CORE_EP_SET_NRDY          dev_core_ep_set_nrdy;
  DEV_CORE_EP0_RX_SETUP_PKT     dev_core_ep0_rx_setup_pkt;
  DEV_CORE_EP0_RX_STATUS_PKT    dev_core_ep0_rx_status_pkt;
  DEV_CORE_EP0_TX_STATUS_PKT    dev_core_ep0_tx_status_pkt;
  DEV_CORE_EP_TX_DATA           dev_core_ep_tx_data;
  DEV_CORE_EP_RX_DATA           dev_core_ep_rx_data;
  DEV_CORE_EP_CANCEL_TRANSFER   dev_core_ep_cancel_transfer;
};

/* This API is used to obtain the driver handle for HW-independent API
 * @id: The ID of the core for which this driver is requested
 */
const struct usb_device_core_driver *usb_device_get_core_driver(
  USB_CONTROLLER_ID id);

#endif

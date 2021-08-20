/** @file
  Header file for wrapper functions of XDCI APIs.

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


#ifndef _USB_DEVICE_H_
#define _USB_DEVICE_H_

/* @USB_DEV_CONFIG_PARAMS: Struct to be filled in with configuration
 * parameters and passed to the init routine for device controller
 */
typedef struct {
  USB_CONTROLLER_ID  ControllerId; // Controller ID of the core
  UINT64             BaseAddress;  // Base address of the controller registers and on-chip memory
  UINT32             Flags;        // Initialization flags
  USB_SPEED          Speed;        // Desired USB bus speed
  USB_ROLE           Role;         // Default USB role
} USB_DEV_CONFIG_PARAMS;

/* @USB_DEV_CORE: Struct used as a handle for all
 * hardware-independent APIs
 */
typedef struct {
  const struct usb_device_core_driver *core_driver;
  VOID                                *controller_handle;
} USB_DEV_CORE;

typedef
EFI_STATUS
(EFIAPI *USB_DEVICE_CALLBACK_FUNC) (
  IN USB_DEVICE_CALLBACK_PARAM  *Param
  );

EFI_STATUS
usb_device_init (
  IN USB_DEV_CONFIG_PARAMS    *ConfigParams,
  IN OUT VOID                 **DevCoreHandle
  );

EFI_STATUS
usb_device_deinit (
  IN VOID                      *DevCoreHandle,
  IN UINT32                    Flags
  );

EFI_STATUS
usb_device_register_callback (
  IN VOID                      *DevCoreHandle,
  IN USB_DEVICE_EVENT_ID       EventId,
  IN USB_DEVICE_CALLBACK_FUNC  CallbackFunc
  );

EFI_STATUS
usb_device_unregister_callback (
  IN VOID                      *DevCoreHandle,
  IN USB_DEVICE_EVENT_ID       EventId
  );

EFI_STATUS
usb_device_isr_routine (
  IN VOID                      *DevCoreHandle
  );

EFI_STATUS
usb_device_connect (
  IN VOID                      *DevCoreHandle
  );

EFI_STATUS
usb_device_disconnect (
  IN VOID                      *DevCoreHandle
  );

EFI_STATUS
usb_device_get_speed (
  IN VOID                      *DevCoreHandle,
  IN USB_SPEED                 *Speed
  );

EFI_STATUS
usb_device_set_link_state (
  IN VOID                      *DevCoreHandle,
  IN USB_DEVICE_SS_LINK_STATE  State
  );

EFI_STATUS
usb_device_set_address (
  IN VOID                      *DevCoreHandle,
  IN UINT32                    Address
  );

EFI_STATUS
usb_device_set_configuration (
  IN VOID                      *DevCoreHandle,
  IN UINT32                    ConfigNum
  );

EFI_STATUS
usb_device_init_ep (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  );

EFI_STATUS
usb_device_ep_enable (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  );

EFI_STATUS
usb_device_ep_disable (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  );

EFI_STATUS
usb_device_ep_stall (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  );

EFI_STATUS
usb_device_ep_clear_stall (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  );

EFI_STATUS
usb_device_ep_set_nrdy (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *EpInfo
  );

EFI_STATUS
usb_device_ep0_rx_setup (
  IN VOID                      *DevCoreHandle,
  IN UINT8                     *Buffer
  );

EFI_STATUS
usb_device_ep0_rx_status (
  IN VOID                      *DevCoreHandle
  );

EFI_STATUS
usb_device_ep0_tx_status (
  IN VOID                      *DevCoreHandle
  );

EFI_STATUS
usb_device_ep_tx_data (
  IN VOID                      *DevCoreHandle,
  IN USB_XFER_REQUEST          *XferReq
  );

EFI_STATUS
usb_device_ep_rx_data (
  IN VOID                      *DevCoreHandle,
  IN USB_XFER_REQUEST          *XferReq
  );

EFI_STATUS
usb_device_ep_cancel_transfer (
  IN VOID                      *DevCoreHandle,
  IN USB_EP_INFO               *ep_info
  );

#endif

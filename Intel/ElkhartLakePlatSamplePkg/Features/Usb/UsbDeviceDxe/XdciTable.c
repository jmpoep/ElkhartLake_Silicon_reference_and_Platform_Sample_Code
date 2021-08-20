/** @file
  Implementation for table of XDCI core APIs.

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
#include "XdciDWC.h"
#include "UsbDeviceMode.h"

/* TODO: Document these later */


static const struct usb_device_core_driver core_driver_tbl[USB_CORE_ID_MAX] = { {
  dwc_xdci_core_init,
  dwc_xdci_core_deinit,
  dwc_xdci_core_register_callback,
  dwc_xdci_core_unregister_callback,
  dwc_xdci_core_isr_routine,
  dwc_xdci_core_connect,
  dwc_xdci_core_disconnect,
  dwc_xdci_core_get_speed,
  dwc_xdci_core_set_address,
  dwc_xdci_core_set_config,
  dwc_xdci_set_link_state,
  dwc_xdci_init_ep,
  dwc_xdci_ep_enable,
  dwc_xdci_ep_disable,
  dwc_xdci_ep_stall,
  dwc_xdci_ep_clear_stall,
  dwc_xdci_ep_set_nrdy,
  dwc_xdci_ep0_receive_setup_pkt,
  dwc_xdci_ep0_receive_status_pkt,
  dwc_xdci_ep0_send_status_pkt,
  dwc_xdci_ep_tx_data,
  dwc_xdci_ep_rx_data,
  dwc_xdci_ep_cancel_transfer
} };

const struct usb_device_core_driver *usb_device_get_core_driver(USB_CONTROLLER_ID id)
{
  if (id >= USB_CORE_ID_MAX)
    return NULL;

  return &core_driver_tbl[id];
}


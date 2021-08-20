/**@file
  Header file for definition of USBFN device mode protocol.

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

@par Specification
**/
#ifndef _USB_DEVICE_MODE_PROTOCOL_H_
#define _USB_DEVICE_MODE_PROTOCOL_H_

#include <Library/UsbDeviceLib.h>

///
/// UsbDeviceMode Protocol GUID.
///
#define EFI_USB_DEVICE_MODE_PROTOCOL_GUID \
  {0xC9923F7E, 0x1746, 0x4802, { 0x86, 0x2e, 0x1, 0x1c, 0x2c, 0x2d, 0x9d, 0x86 } }

typedef struct _EFI_USB_DEVICE_MODE_PROTOCOL EFI_USB_DEVICE_MODE_PROTOCOL;

typedef
EFI_STATUS
(EFIAPI *EFI_USB_DEVICE_MODE_INIT_XDCI) (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_USB_DEVICE_MODE_CONNECT) (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_USB_DEVICE_MODE_DISCONNECT) (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_USB_DEVICE_EP_TX_DATA) (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This,
  IN USB_DEVICE_IO_REQ                          *IoRequest
  );

typedef
EFI_STATUS
(EFIAPI *EFI_USB_DEVICE_EP_RX_DATA) (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This,
  IN USB_DEVICE_IO_REQ                          *IoRequest
  );

typedef
EFI_STATUS
(EFIAPI *EFI_USB_DEVICE_MODE_BIND) (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This,
  IN USB_DEVICE_OBJ                             *UsbdDevObj
  );

typedef
EFI_STATUS
(EFIAPI *EFI_USB_DEVICE_MODE_UNBIND) (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_USB_DEVICE_MODE_STOP) (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This
  );

typedef
EFI_STATUS
(EFIAPI *EFI_USB_DEVICE_MODE_RUN) (
  IN EFI_USB_DEVICE_MODE_PROTOCOL               *This,
  IN UINT32                                     TimeoutMs
  );

///
/// Usb Device Mode Protocol Structure.
///
struct _EFI_USB_DEVICE_MODE_PROTOCOL {
  EFI_USB_DEVICE_MODE_INIT_XDCI            InitXdci;
  EFI_USB_DEVICE_MODE_CONNECT              Connect;
  EFI_USB_DEVICE_MODE_DISCONNECT           DisConnect;
  EFI_USB_DEVICE_EP_TX_DATA                EpTxData;
  EFI_USB_DEVICE_EP_RX_DATA                EpRxData;
  EFI_USB_DEVICE_MODE_BIND                 Bind;
  EFI_USB_DEVICE_MODE_UNBIND               UnBind;
  EFI_USB_DEVICE_MODE_RUN                  Run;
  EFI_USB_DEVICE_MODE_STOP                 Stop;
};

#endif

/** @file
  Header file for USBFN protocol.

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


#ifndef __EFI_USB_FUNCTION_IO_INTERFACE_H__
#define __EFI_USB_FUNCTION_IO_INTERFACE_H__

#include <Uefi.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DevicePathLib.h>
#include <Library/PcdLib.h>
#include <Protocol/EfiUsbFnIo.h>
#include <Library/UsbDeviceLib.h>
#include <Library/PrintLib.h>
#include "UsbIoNode.h"
#include "XdciDWC.h"
#include "UsbDeviceMode.h"

//
// Debug message setting
//
#define USB_FUIO_DEBUG_INFO              EFI_D_ERROR
#define USB_FUIO_DEBUG_LOAD              EFI_D_ERROR
#define USB_FUIO_DEBUG_ERROR             EFI_D_ERROR
#define USB_FUIO_DEBUG_EVENT_I           0 //DEBUG_INIT
#define USB_FUIO_DEBUG_EVENT_D           EFI_D_ERROR
#define USB_FUIO_DEBUG_EVENT_NOTREADY_D  EFI_D_ERROR
#define USB_FUIO_DEBUG_EVENT_NOTREADY_I  0 //DEBUG_INIT

#define MAX_TRANSFER_PACKET     (8 * 1024 * 1024)

#define USBFU_VID     0x8086
#define USBFU_PID     0x0A65

#pragma pack(1)
typedef struct {
  UINT8                     ProgInterface;
  UINT8                     SubClassCode;
  UINT8                     BaseCode;
} USB_CLASSC;


/* Event Buffer Struct */
typedef struct  {
  UINT32 event;
  UINT32 dev_tst_lmp1;
  UINT32 dev_tst_lmp2;
  UINT32 reserved;
} USBD_EVENT_BUF;

typedef struct  {
  UINT32                        EpNum;
  EFI_USBFN_ENDPOINT_DIRECTION  Direction;
  UINTN                         XferAddress;
  UINT32                        XferLength;
  UINT8                         LogEpNum;
  BOOLEAN                       Complete;
  BOOLEAN                       ZlpFlag;
} USBD_EP_XFER_REC;

#pragma pack()

EFI_STATUS
UsbFnInitDevice (
  IN EFI_USBFN_IO_PROTOCOL        *This
  );

EFI_STATUS
UsbFnDeInitDevice (
  IN EFI_USBFN_IO_PROTOCOL        *This
  );

EFI_STATUS
EFIAPI
DetectPort (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  OUT EFI_USBFN_PORT_TYPE          *PortType
  );

EFI_STATUS
EFIAPI
AllocateTransferBuffer (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  IN UINTN                         Size,
  OUT VOID                         **Buffer
  );

EFI_STATUS
EFIAPI
FreeTransferBuffer (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  IN VOID                          *Buffer
  );

EFI_STATUS
EFIAPI
ConfigureEnableEndpoints (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  IN EFI_USB_DEVICE_INFO           *DeviceInfo
 );

EFI_STATUS
EFIAPI
GetEndpointMaxPacketSize (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  IN EFI_USB_ENDPOINT_TYPE         EndpointType,
  IN EFI_USB_BUS_SPEED             BusSpeed,
  OUT UINT16                       *MaxPacketSize
 );

EFI_STATUS
EFIAPI
GetMaxTransferSize (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  OUT UINTN                        *MaxTransferSize
  );

EFI_STATUS
EFIAPI
GetDeviceInfo (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  IN EFI_USBFN_DEVICE_INFO_ID      Id,
  IN OUT UINTN                     *BufferSize,
  OUT VOID                         *Buffer OPTIONAL
  );

EFI_STATUS
EFIAPI
GetVendorIdProductId (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  OUT UINT16                       *Vid,
  OUT UINT16                       *Pid
  );

EFI_STATUS
EFIAPI
AbortTransfer (
  IN EFI_USBFN_IO_PROTOCOL        *This,
  IN UINT8                        EndpointIndex,
  IN EFI_USBFN_ENDPOINT_DIRECTION Direction
  );

EFI_STATUS
EFIAPI
GetEndpointStallState (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  IN UINT8                         EndpointIndex,
  IN EFI_USBFN_ENDPOINT_DIRECTION  Direction,
  IN OUT BOOLEAN                   *State
  );

EFI_STATUS
EFIAPI
SetEndpointStallState (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  IN UINT8                         EndpointIndex,
  IN EFI_USBFN_ENDPOINT_DIRECTION  Direction,
  IN BOOLEAN                       State
  );

EFI_STATUS
EFIAPI
EventHandler (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  OUT EFI_USBFN_MESSAGE            *Message,
  IN OUT UINTN                     *PayloadSize,
  OUT EFI_USBFN_MESSAGE_PAYLOAD    *Payload
  );

EFI_STATUS
EFIAPI
Transfer (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  IN UINT8                         EndpointIndex,
  IN EFI_USBFN_ENDPOINT_DIRECTION  Direction,
  IN OUT UINTN                     *BufferSize,
  IN OUT VOID                      *Buffer
  );

EFI_STATUS
EFIAPI
StartController (
  IN EFI_USBFN_IO_PROTOCOL         *This
  );

EFI_STATUS
EFIAPI
StopController (
  IN EFI_USBFN_IO_PROTOCOL         *This
  );

EFI_STATUS
EFIAPI
SetEndpointPolicy (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  IN UINT8                         EndpointIndex,
  IN EFI_USBFN_ENDPOINT_DIRECTION  Direction,
  IN EFI_USBFN_POLICY_TYPE         PolicyType,
  IN UINTN                         BufferSize,
  IN VOID                          *Buffer
  );

EFI_STATUS
EFIAPI
GetEndpointPolicy (
  IN EFI_USBFN_IO_PROTOCOL         *This,
  IN UINT8                         EndpointIndex,
  IN EFI_USBFN_ENDPOINT_DIRECTION  Direction,
  IN EFI_USBFN_POLICY_TYPE         PolicyType,
  IN OUT UINTN                     *BufferSize,
  IN OUT VOID                      *Buffer
  );

VOID
UsbFnSetEpInfo (
  IN USB_EP_INFO                 *EpDest,
  IN USB_DEVICE_ENDPOINT_INFO    *EpSrc
  );

extern EFI_USBFN_IO_PROTOCOL         mUsbFunIoProtocol;
#endif

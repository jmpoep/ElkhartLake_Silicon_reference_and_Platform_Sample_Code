/** @file
  Header file for common definition of XDCI core.

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


#ifndef _XDCI_COMMON_H_
#define _XDCI_COMMON_H_

#define USB_SETUP_DATA_PHASE_DIRECTION_MASK  (0x80)

//
// EP direction
//
typedef enum {
  UsbEpDirOut = 0,
  UsbEpDirIn  = 1
} USB_EP_DIR;

//
// USB speeds
//
typedef enum {
  USB_SPEED_HIGH  = 0,
  USB_SPEED_FULL,
  USB_SPEED_LOW,
  USB_SPEED_SUPER = 4
} USB_SPEED;

typedef enum {
  USB_ID_DWC_XDCI = 0,
  USB_CORE_ID_MAX
} USB_CONTROLLER_ID;

typedef enum {
  USB_ROLE_HOST = 1,
  USB_ROLE_DEVICE,
  USB_ROLE_OTG
} USB_ROLE;

typedef enum {
  USB_XFER_QUEUED    = 0,
  USB_XFER_SUCCESSFUL,
  USB_XFER_STALL
} USB_XFER_STATUS;

typedef enum {
  USB_DEVICE_DISCONNECT_EVENT       = 0,
  USB_DEVICE_RESET_EVENT,
  USB_DEVICE_CONNECTION_DONE,
  USB_DEVICE_STATE_CHANGE_EVENT,
  USB_DEVICE_WAKEUP_EVENT,
  USB_DEVICE_HIBERNATION_REQ_EVENT,
  USB_DEVICE_SOF_EVENT              = 7,
  USB_DEVICE_ERRATIC_ERR_EVENT      = 9,
  USB_DEVICE_CMD_CMPLT_EVENT,
  USB_DEVICE_BUFF_OVERFLOW_EVENT,
  USB_DEVICE_TEST_LMP_RX_EVENT,
  USB_DEVICE_SETUP_PKT_RECEIVED,
  USB_DEVICE_XFER_NRDY,
  USB_DEVICE_XFER_DONE
} USB_DEVICE_EVENT_ID;

typedef enum {
  U0 = 0,
  U1,
  U2,
  U3,
  SS_DIS,
  RX_DET,
  SS_INACT,
  POLL,
  RECOV,
  HRESET,
  CMPLY,
  LPBK,
  RESUME_RESET = 15
} USB_DEVICE_SS_LINK_STATE;

typedef enum {
  CTRL_SETUP_PHASE,
  CTRL_DATA_PHASE,
  CTRL_STATUS_PHASE
} USB_CONTROL_XFER_PHASE;

typedef enum  {
  USB_EP_STATE_DISABLED = 0,
  USB_EP_STATE_ENABLED,
  USB_EP_STATE_STALLED,
  USB_EP_STATE_SETUP,
  USB_EP_STATE_IN_DATA,
  USB_EP_STATE_OUT_DATA,
  USB_EP_STATE_DATA,
  USB_EP_STATE_STATUS
} USB_EP_STATE;

typedef struct  {
  VOID                      *parent_handle;
  UINT32                    hird;
  UINT32                    ep_num;
  USB_SPEED                 speed;
  USB_EP_STATE              ep_state;
  USB_EP_DIR                ep_dir;
  UINT8                     ep_type;
  USB_DEVICE_SS_LINK_STATE  link_state;
  UINT8                     *buffer;
  BOOLEAN                   ss_event;
} USB_DEVICE_CALLBACK_PARAM;

//
// USB endpoint
//
typedef struct {
  UINT32       ep_num;
  USB_EP_DIR   ep_dir;
  UINT8        ep_type;
  UINT32       max_pkt_size;
  UINT32       max_streams;
  UINT32       burst_size;
  UINT32       interval;
  UINT32       mult;
} USB_EP_INFO;

//
// USB transfer request
//
typedef struct _USB_XFER_REQUEST USB_XFER_REQUEST;

typedef
VOID
(EFIAPI *USB_XFER_DONE_CALLBACK) (
  IN VOID                    *XdciHndl,
  IN USB_XFER_REQUEST        *XferReq
  );

struct _USB_XFER_REQUEST {
  VOID                      *xfer_buffer;     // Buffer address. bus-width aligned
  UINT32                    xfer_len;         // Requested transfer length
  UINT32                    actual_xfer_len;  // Actual transfer length at completion callback stage
  UINT32                    stream_id;        // Stream ID. Only relevant for bulk streaming
  UINT32                    frame_num;        // Only relevant for periodic transfer
  USB_XFER_STATUS           xfer_status;      // Transfer status
  USB_EP_INFO               ep_info;          // EP info
  USB_XFER_DONE_CALLBACK    xfer_done;        // Transfer completion callback
  BOOLEAN                   zlp;              // Do zero-length transfer
};

#endif

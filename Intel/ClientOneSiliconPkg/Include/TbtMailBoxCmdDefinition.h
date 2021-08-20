/**@file
  Header file of TBT MailBox Command Definition shared by C and ASL code.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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

#define PCIE2TBT_VLD_B                               BIT0
#define TBT2PCIE_DON_R                               BIT0
#define TBT_MAILBOX_DELAY                            100000 ///< 100ms

///
///Mailbox command value to controller is generic on all types of TBT controllers
///
/**
  Mailbox ommand to link controller (LC) and Connection Manager (CM) to enter Sx with wake support
**/
#define PCIE2TBT_GO2SX                              0x04 //(0x02 << 1)
/**
  Mailbox ommand to link controller (LC) and Connection Manager (CM) to enter Sx without wake support
**/
#define PCIE2TBT_GO2SX_NO_WAKE                      0x06 //(0x03 << 1)
/**
  Mailbox ommand to controller to exit Sx and the system went to sleep with attached devices previously
**/
#define PCIE2TBT_SX_EXIT_TBT_CONNECTED              0x08 //(0x04 << 1)
#define PCIE2TBT_SX_EXIT_NO_TBT_CONNECTED           0x0A //(0x05 << 1)
#define PCIE2TBT_OS_UP                              0x0C //(0x06 << 1)
#define PCIE2TBT_SET_SECURITY_LEVEL                 0x10 //(0x08 << 1)
#define PCIE2TBT_GET_SECURITY_LEVEL                 0x12 //(0x09 << 1)
#define PCIE2TBT_CM_AUTH_MODE_ENTER                 0x20 //(0x10 << 1)
#define PCIE2TBT_CM_AUTH_MODE_EXIT                  0x22 //(0x11 << 1)
#define PCIE2TBT_BOOT_ON                            0x30 //(0x18 << 1)
#define PCIE2TBT_BOOT_OFF                           0x32 //(0x19 << 1)
#define PCIE2TBT_USB_ON                             0x32 //(0x19 << 1)
#define PCIE2TBT_GET_ENUMERATION_METHOD             0x34 //(0x1A << 1)
#define PCIE2TBT_SET_ENUMERATION_METHOD             0x36 //(0x1B << 1)
#define PCIE2TBT_POWER_CYCLE                        0x38 //(0x1C << 1)
/**
  Mailbox ommand to CM to ensure all connected TBT devices are available on PCIe
**/
#define PCIE2TBT_CONNECT_TOPOLOGY_COMMAND           0x3E //(0x1F << 1)

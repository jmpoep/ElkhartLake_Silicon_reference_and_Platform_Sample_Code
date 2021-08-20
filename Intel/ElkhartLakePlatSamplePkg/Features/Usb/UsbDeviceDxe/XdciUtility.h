/** @file
 Header file for helper functions of XDCI device driver.

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


#ifndef _XDCI_UTILITY_H_
#define _XDCI_UTILITY_H_

#include <Library/UsbDeviceLib.h>

VOID
PrintDeviceDescriptor (
  IN USB_DEVICE_DESCRIPTOR    *DevDesc
  );

VOID
PrintConfigDescriptor (
  IN EFI_USB_CONFIG_DESCRIPTOR    *ConfigDesc
  );

VOID
PrintInterfaceDescriptor (
  IN EFI_USB_INTERFACE_DESCRIPTOR    *IfDesc
  );

VOID
PrintEpDescriptor (
  IN EFI_USB_ENDPOINT_DESCRIPTOR    *EpDesc
  );

VOID
PrintEpCompDescriptor (
  IN EFI_USB_ENDPOINT_COMPANION_DESCRIPTOR    *EpDesc
  );

VOID
PrintStringDescriptor (
  IN USB_STRING_DESCRIPTOR    *StrDesc
  );

VOID
PrintDeviceRequest (
  IN EFI_USB_DEVICE_REQUEST    *DevReq
  );

#ifdef SUPPORT_SUPER_SPEED
VOID
PrintBOSDescriptor (
  IN EFI_USB_BOS_DESCRIPTOR    *BosDesc
  );
#endif

#endif


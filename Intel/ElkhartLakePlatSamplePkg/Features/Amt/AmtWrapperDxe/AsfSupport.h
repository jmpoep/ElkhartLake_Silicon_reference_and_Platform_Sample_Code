/** @file
  ASF BDS Support include file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2019 Intel Corporation.

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

#ifndef _ASF_SUPPORT_H_
#define _ASF_SUPPORT_H_

#include <Uefi/UefiBaseType.h>
#include <Guid/GlobalVariable.h>
#include <IndustryStandard/Pci22.h>
#include <Protocol/LoadFile.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/BlockIo.h>
#include <Protocol/DiskInfo.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/SimpleNetwork.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PrintLib.h>
#include <Library/DevicePathLib.h>
#include <Register/MeRegs.h>
#include <Library/PchInfoLib.h>
#include <IndustryStandard/AlertStandardFormatTable.h>
#include <Protocol/AsfProtocol.h>
#include <Register/UsbRegs.h>

#define SECURE_BOOT_ENABLED               1
#define SECURE_BOOT_DISABLED              0

#define RESTORE_SECURE_BOOT_NONE          0
#define RESTORE_SECURE_BOOT_ENABLED       1

#define RESTORE_SECURE_BOOT_GUID \
  { \
    0x118b3c6f, 0x98d6, 0x4d05, { 0x96, 0xb2, 0x90, 0xe4, 0xcb, 0xb7, 0x40, 0x34 } \
  }

typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  PCI_DEVICE_PATH           Xhci;
  USB_DEVICE_PATH           Usbr;
  EFI_DEVICE_PATH_PROTOCOL  End;
} STORAGE_REDIRECTION_DEVICE_PATH;

extern
VOID
ConnectAllDriversToAllControllers (
  VOID
  );

#endif

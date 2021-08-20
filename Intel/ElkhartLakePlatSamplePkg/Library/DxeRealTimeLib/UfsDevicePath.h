/**@file

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef __UFS_DEVICE_PATH__H__
#define __UFS_DEVICE_PATH__H__

#include <Register/ScsVer3Regs.h>

typedef struct {
  ACPI_HID_DEVICE_PATH      PciRootBridge;
  PCI_DEVICE_PATH           PciDevice;
  EFI_DEVICE_PATH_PROTOCOL  End;
} PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH;

#define gPciRootBridge \
{ \
  { \
    ACPI_DEVICE_PATH, \
    ACPI_DP, \
    { \
      (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)), \
      (UINT8) ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8) \
    }, \
  }, \
  EISA_PNP_ID (0x0A03), \
  0 \
}

#define gEndEntire \
{ \
  END_DEVICE_PATH_TYPE, \
  END_ENTIRE_DEVICE_PATH_SUBTYPE, \
  { \
    END_DEVICE_PATH_LENGTH, \
    0 \
  } \
}

//
// UFS Controller Device Path
//
PLATFORM_ONBOARD_CONTROLLER_DEVICE_PATH  gPlatformOnboardUfsDevice = {
  gPciRootBridge,
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_PCI_DP,
      {
        (UINT8) (sizeof (PCI_DEVICE_PATH)),
        (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8)
      }
    },
    PCI_FUNCTION_NUMBER_PCH_EHL_SCS_UFS1,
    PCI_DEVICE_NUMBER_PCH_EHL_SCS_UFS1
  },
  gEndEntire
};

#endif

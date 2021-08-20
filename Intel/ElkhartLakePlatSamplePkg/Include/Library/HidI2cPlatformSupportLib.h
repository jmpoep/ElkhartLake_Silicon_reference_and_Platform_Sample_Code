/** @file
  Support for IO expander TCA6424.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

#include <Uefi.h>

//
// There's no decision yet if the 3 functions below should be a lib or protocol
//

EFI_STATUS EFIAPI HidI2cInitialize ( IN EFI_HANDLE Handle);
BOOLEAN EFIAPI HidI2cCheckInterrupt ( IN EFI_HANDLE Handle);
UINT16 EFIAPI HidI2cGetHidRegisterAddress ( IN EFI_HANDLE Handle);

typedef
UINT16
(EFIAPI *HID_I2C_GET_HID_REGISTER_ADDRESS)(
  IN EFI_HANDLE Device
);
typedef
BOOLEAN
(EFIAPI *HID_I2C_CHECK_INTERRUPT)(
  IN EFI_HANDLE Device
);
typedef
EFI_STATUS
(EFIAPI *HID_I2C_INITIALIZE)(
  IN EFI_HANDLE Device
);

typedef struct {
  HID_I2C_GET_HID_REGISTER_ADDRESS   GetHidRegisterAddress;
  HID_I2C_CHECK_INTERRUPT            CheckInterrupt;
  HID_I2C_INITIALIZE                 Initialize;
} HID_I2C_PLATFORM_SUPPORT;



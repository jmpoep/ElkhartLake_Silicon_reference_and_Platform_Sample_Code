/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/


#ifndef _BOOT_DEVICE_INFO_VARIABLE_H_
#define _BOOT_DEVICE_INFO_VARIABLE_H_

#define BOOT_DEVICE_INFO_GUID \
 { 0x5BD6B672, 0xB6EA, 0x4D6A, { 0xB5, 0x90, 0x18, 0xA9, 0x32, 0xB7, 0x87, 0x94 } }

#define BOOT_DEVICE_INFO_VARIABLE_NAME L"BootMediaInfo"
#define BOOT_DEVICE_INFO_REVISION      1
#define UFS_LUN_1                      0x01


typedef struct {
  /*
    Revision of this structure
  */
  UINT32  Version;
  /*
    BIT0 = SPI
    BIT1 = eMMC
    BIT2 = UFS
    BIT3 = NVMe
    BIT4 ~ BIT31 are reserved
  */
  UINT32 BootDeviceType;
  /*
    Partition for Boot image
  */
  UINT32 Partition;
} BOOT_DEVICE_SETUP;

#endif //_BOOT_DEVICE_INFO_VARIABLE_H_

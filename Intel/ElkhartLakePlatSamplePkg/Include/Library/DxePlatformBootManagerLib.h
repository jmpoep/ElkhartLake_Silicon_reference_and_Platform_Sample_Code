/** @file
  Header file for DxePlatformBootManagerLib

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

@par Specification Reference
**/

#ifndef _DXE_PLATFORM_BOOT_MANAGER_LIB_H_
#define _DXE_PLATFORM_BOOT_MANAGER_LIB_H_


/**
  Tries to expand the given partitions device path to start with physical HDD
  device path
  @param[in]       LoadOption          pointer to an Efi Boot Manager boot option
  @param[out]      BootDevicePath      indirect pointer to retrieved device path

  @retval          EFI_SUCCESS         Function found
**/
EFI_STATUS
ExpandPartitionsDevPath (
  IN EFI_BOOT_MANAGER_LOAD_OPTION     *LoadOption,
  OUT EFI_DEVICE_PATH_PROTOCOL       **BootDevicePath
  );

/**
  Checks whenever a given load option starts with a partition device path

  @param[in]       LoadOption          Pointer to load option to test

  @retval          TRUE
  @retval          FALSE
**/
BOOLEAN
IsItPartitionsDevicePath(
    IN EFI_BOOT_MANAGER_LOAD_OPTION     *LoadOption
  );

/**
  This function converts an input device structure to a Unicode string.

  @param DevPath                  A pointer to the device path structure.

  @return A new allocated Unicode string that represents the device path.
**/
CHAR16 *
DevicePathToStr (
  IN EFI_DEVICE_PATH_PROTOCOL     *DevPath
  );

#endif

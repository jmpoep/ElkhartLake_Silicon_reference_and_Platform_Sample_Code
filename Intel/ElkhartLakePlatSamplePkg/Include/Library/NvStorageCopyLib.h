/** @file
    This is the header file for the NvStorageCopy Library.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef __NV_STORAGE_COPY_LIB_H__
#define __NV_STORAGE_COPY_LIB_H__

/**
  Copies UEFI variable data from the given firmware volume to the default variable HOB.

  The default variable HOB must have been created with a size to accommodate the variable data
  copied by this function.

  @param[in]  NvStorageFvHeader   Pointer to the NV Storage firmware volume.

  @retval EFI_SUCCESS             If the function completed successfully.
  @retval EFI_INVALID_PARAMETER   The NvStorageFvHeader firmware volume is invalid or the variable store is invalid.
  @retval EFI_NOT_READY           The default variable HOB was not found or the data in the HOB is invalid.

**/
EFI_STATUS
EFIAPI
CopyNvStorageDataToDefaultVariableHob (
  IN CONST EFI_FIRMWARE_VOLUME_HEADER *NvStorageFvHeader
  );

#endif

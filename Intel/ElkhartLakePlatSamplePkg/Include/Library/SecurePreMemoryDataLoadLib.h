/** @file
  PEI Secure Pre-Memory Data Load Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#ifndef _SECURE_PRE_MEMORY_DATA_LOAD_LIB_H_
#define _SECURE_PRE_MEMORY_DATA_LOAD_LIB_H_

#include <SecurePreMemoryData.h>

/**
  Loads the Secure Pre-Memory Data (SPMD) from the CSE Shared SRAM on a block media boot. This data will contain
  a UEFI variable store that serves read requests in PEI on a block media boot.

  @param      None

  @retval     EFI_SUCCESS    The secure pre-memory data was loaded successfully.
  @retval     EFI_NOT_FOUND  The secure pre-memory data was not found.
*/
EFI_STATUS
EFIAPI
LoadSecurePreMemoryData (
  VOID
  );

#endif

/** @file
  CSE Variable Storage Initialization Library

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017-2018 Intel Corporation.

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

#ifndef _CSE_VARIABLE_STORAGE_INIT_LIB_H_
#define _CSE_VARIABLE_STORAGE_INIT_LIB_H_

#include <Base.h>
#include <CseVariableStorage.h>

/**
  Loads variable index data for all enabled variable stores that exist.

  If an enabled variable store does not exist, a new one will be created if possible.

  @param[in,out]    CseVariableStorageStores  A pointer to a structure that contains CSE variable storage stores info.

  @retval           EFI_SUCCESS               The variable store was established successfully.
  @retval           EFI_OUT_OF_RESOURCES      Not enough memory resources available for memory allocation needed.
  @retval           Others                    The variable store could not be established.
**/
EFI_STATUS
EFIAPI
EstablishAndLoadCseVariableStores (
  IN OUT CSE_VARIABLE_STORAGE_STORE   **CseVariableStorageStores
  );

/**
  Initializes all CSE variable storage stores.

  @param[out]     CseVariableStorageStores  A pointer to a structure that contains CSE variable storage stores.

  @retval         EFI_SUCCESS               The CSE variable storage stores were initialized successfully.
  @retval         EFI_OUT_OF_RESOURCES      Not enough memory resources needed for allocation were available.
  @retval         Others                    An error occurred initializing the CSE variable storage stores.
**/
EFI_STATUS
EFIAPI
InitializeCseVariableStorage (
  OUT CSE_VARIABLE_STORAGE_STORE  **CseVariableStorageStores
  );

#endif

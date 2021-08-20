/** @file
  Interface of MP Sync Data library.

  @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 Intel Corporation. <BR>

  The source code contained or described herein and all documents related to the
  source code ("Material") are owned by Intel Corporation or its suppliers or
  licensors. Title to the Material remains with Intel Corporation or its suppliers
  and licensors. The Material may contain trade secrets and proprietary    and
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
**/

#ifndef __RAS_GLOBAL_DATA_LIB_H__
#define __RAS_GLOBAL_DATA_LIB_H__



/**

  Get Ras global data pointer.

  This function implements single design pattern to return the system global data for RAS usage.
  It is required for the caller of this library API to cache the return value to module global
  variable to in the POST phase.

  @param Name            NULL-terminated Unicode string as the unique key for the global variable.
  @param Size            The size of global data.
  @param NewAllocation   Indicate whether the data is newly allocated or not.

  @return Pointer to the global data or NULL if there is out of resource.

**/
VOID*
EFIAPI
GetRasGlobalData (
  IN  CHAR16         *Name,
  IN  UINTN          Size,
  OUT BOOLEAN        *NewAllocation OPTIONAL
  );

#endif

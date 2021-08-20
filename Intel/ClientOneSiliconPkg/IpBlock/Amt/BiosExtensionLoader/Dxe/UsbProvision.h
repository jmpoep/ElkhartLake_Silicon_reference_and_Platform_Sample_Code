/** @file
  This files contains API definition to get and remove USB provision record.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2005 - 2018 Intel Corporation.

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

#ifndef _USB_PROVISION_H_
#define _USB_PROVISION_H_

#include <Protocol/SimpleFileSystem.h>

typedef struct {
  BOOLEAN          HandleValid;
  VOID             *ProvisionRecordBuffer;
  UINT32           ProvisionRecordSize;
  EFI_FILE_HANDLE  ProvisionFileHandle;
} PROVISION_RECORD_HANDLE;

/**
  This function searches file system for valid provision file
  and extract first valid provision record.

  @param[out] ProvisionRecordHandle  Pointer to provision record.

  @retval TRUE   Provision record found
  @retval FALSE  Provision record not found
**/
BOOLEAN
GetUsbProvisionRecord (
  OUT PROVISION_RECORD_HANDLE  *ProvisionRecordHandle
  );

/**
  Mark provision record as consumed if provision file
  allows consuming and MEBx consumed the record.
  This function should be called after MEBx invocation.

  This function is also responsible for cleanup of all of the
  resources allocated during initial data record discovery.
  After call to this function ProvisionRecord is no longer valid and
  shouldn't be used.

  @param[in] ProvisionRecordHandle  Provision record to consume
  @param[in] ReturnedDataRecord     Provision data record as returned from MEBx.
**/
VOID
RemoveUsbProvisionRecord (
  IN PROVISION_RECORD_HANDLE  *ProvisionRecordHandle,
  IN VOID                     *ReturnedDataRecord
  );

#endif

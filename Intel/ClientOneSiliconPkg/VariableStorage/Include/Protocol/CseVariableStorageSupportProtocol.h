/** @file
  This file declares the CSE Variable Storage Support Protocol

  This protocol allows the CSE UEFI variable implementation to provide
  common services to the CSE UEFI variable module.

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
#ifndef _CSE_VARIABLE_STORAGE_SUPPORT_PROTOCOL_H_
#define _CSE_VARIABLE_STORAGE_SUPPORT_PROTOCOL_H_

extern EFI_GUID gCseVariableStorageSupportProtocolGuid;

///
/// Revision
///
#define CSE_VARIABLE_STORAGE_SUPPORT_PROTOCOL_REVISION  1

typedef struct _CSE_VARIABLE_STORAGE_SUPPORT_PROTOCOL  CSE_VARIABLE_STORAGE_SUPPORT_PROTOCOL;

/**
  Notifies the CSE variable driver that the previously requested asynchronous Read I/O operation is complete.

  @param[in]  Status  The result of the variable I/O operation. Possible values are:
                        EFI_SUCCESS             The variable I/O completed successfully.
                        EFI_NOT_FOUND           The variable was not found.
                        EFI_DEVICE_ERROR        The variable I/O could not complete due to a hardware error.
                        EFI_SECURITY_VIOLATION  The variable I/O could not complete due to an authentication failure.
  @param[in]  Data                              A pointer to the data buffer with data from the read operation.
  @param[in]  DataSize                          The total size of variable data in bytes.

**/
typedef
VOID
(EFIAPI *CSE_VARIABLE_STORAGE_SUPPORT_NOTIFY_READ_IO_COMPLETE)(
  IN      EFI_STATUS        Status,
  IN      VOID              *Data,
  IN      UINTN             VariableSize
  );

/**
  Notifies the CSE variable driver that the runtime component of the driver is initialized.

**/
typedef
VOID
(EFIAPI *CSE_VARIABLE_STORAGE_SUPPORT_NOTIFY_RT_INITIALIZED)(
  VOID
  );

///
/// CSE Variable Storage Support Protocol
///
struct _CSE_VARIABLE_STORAGE_SUPPORT_PROTOCOL {
  CSE_VARIABLE_STORAGE_SUPPORT_NOTIFY_READ_IO_COMPLETE  NotifyReadIoComplete;     ///< Notify that read I/O is complete
  CSE_VARIABLE_STORAGE_SUPPORT_NOTIFY_RT_INITIALIZED    NofityRuntimeInitialized; ///< Notify that RT is initialized
};

#endif

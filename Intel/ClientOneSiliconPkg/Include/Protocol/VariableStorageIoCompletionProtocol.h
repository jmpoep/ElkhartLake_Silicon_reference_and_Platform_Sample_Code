/** @file
  This file declares the EDKII Variable Storage IO Completion Protocol

  This protocol is used to execute a collection of variable storage commands.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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

#ifndef _VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL_H_
#define _VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL_H_

extern EFI_GUID  gEdkiiVariableStorageIoCompletionProtocolGuid;

///
/// Revision
///
#define EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL_REVISION  1

typedef struct _EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL;

/**
  Retrieves a protocol instance-specific GUID.

  Returns a unique GUID per EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL instance.

  @param[in]     This                     A pointer to this protocol instance.
  @param[out]    InstanceGuid             A pointer to an EFI_GUID that is this protocol instance's GUID.

  @retval        EFI_SUCCESS              The protocol instance GUID was returned successfully.
  @retval        EFI_INVALID_PARAMETER    The InstanceGuid parameter provided was NULL.

**/
typedef
EFI_STATUS
(EFIAPI *EDKII_VARIABLE_STORAGE_IO_COMPLETION_GET_ID)(
  IN  EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL   *This,
  OUT EFI_GUID                                        *InstanceGuid
  );

/**
  Completes the variable storage transaction registered for asynchronous I/O.

  @param[in]     This                     A pointer to this protocol instance.
  @param[in]     SetVariableIoCompletion  TRUE if Complete() is being called to perform I/O for SetVariable
                                          FALSE if Complete() is being called to perform I/O for GetVariable

  @retval        EFI_SUCCESS              The commands executed successfully.
  @retval        Others                   An error occurred executing commands in the command queue.

**/
typedef
EFI_STATUS
(EFIAPI *EDKII_VARIABLE_STORAGE_IO_COMPLETION_COMPLETE)(
  IN  EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL   *This,
  IN  BOOLEAN                                         SetVariableIoCompletion
  );

///
/// Variable Storage IO Completion Protocol
///
struct _EDKII_VARIABLE_STORAGE_IO_COMPLETION_PROTOCOL {
  EDKII_VARIABLE_STORAGE_IO_COMPLETION_COMPLETE      Complete;  ///< Returns when IO request is complete.
  EDKII_VARIABLE_STORAGE_IO_COMPLETION_GET_ID        GetId;     ///< Retrieves a protocol instance-specific GUID
};

#endif

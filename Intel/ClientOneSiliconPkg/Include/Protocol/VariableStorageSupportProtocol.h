/** @file
  This file declares the EDKII Variable Storage Support Protocol

  This protocol allows the system UEFI variable implementation to provide
  common services which all the UEFI variable storage drivers will need

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _VARIABLE_STORAGE_SUPPORT_PROTOCOL_H_
#define _VARIABLE_STORAGE_SUPPORT_PROTOCOL_H_

extern EFI_GUID gEdkiiVariableStorageSupportProtocolGuid;

///
/// Revision
///
#define EDKII_VARIABLE_STORAGE_PROTOCOL_REVISION  1

typedef struct _EDKII_VARIABLE_STORAGE_SUPPORT_PROTOCOL  EDKII_VARIABLE_STORAGE_SUPPORT_PROTOCOL;

/**
  Notifies the core variable driver that the Variable Storage Driver's WriteServiceIsReady() function
  is now returning TRUE instead of FALSE.

  The Variable Storage Driver is required to call this function as quickly as possible.

**/
typedef
VOID
(EFIAPI *EDKII_VARIABLE_STORAGE_SUPPORT_NOTIFY_WRITE_SERVICE_READY)(
  VOID
  );

/**
  Notifies the core variable driver that the Variable Storage Driver has completed the previously requested
  SMM phase asyncronous I/O. If the operation was a read, the data is now present in the NV storage cache.

  This function will only be used by the SMM implementation of UEFI Variables

  @param[in]  VariableStorageInstanceGuid   The instance GUID of the variable storage protocol invoking this function
  @param[in]  Status                        The result of the variable I/O operation. Possible values are:
                            EFI_SUCCESS            The variable I/O completed successfully.
                            EFI_NOT_FOUND          The variable was not found.
                            EFI_OUT_OF_RESOURCES   Not enough storage is available to hold the variable and its data.
                            EFI_DEVICE_ERROR       The variable I/O could not complete due to a hardware error.
                            EFI_WRITE_PROTECTED    The variable in question is read-only.
                            EFI_WRITE_PROTECTED    The variable in question cannot be deleted.
                            EFI_SECURITY_VIOLATION The variable I/O could not complete due to an authentication failure.

**/
typedef
VOID
(EFIAPI *EDKII_VARIABLE_STORAGE_SUPPORT_NOTIFY_SMM_IO_COMPLETE)(
  IN      EFI_GUID                    *VariableStorageInstanceGuid,
  IN      EFI_STATUS                  Status
  );

/**
  Update the non-volatile variable cache with a new value for the given variable

  @param[in]  VariableName       Name of variable.
  @param[in]  VendorGuid         Guid of variable.
  @param[in]  Data               Variable data.
  @param[in]  DataSize           Size of data. 0 means delete.
  @param[in]  Attributes         Attributes of the variable.
  @param[in]  KeyIndex           Index of associated public key.
  @param[in]  MonotonicCount     Value of associated monotonic count.
  @param[in]  TimeStamp          Value of associated TimeStamp.

  @retval EFI_SUCCESS           The update operation is success.
  @retval EFI_OUT_OF_RESOURCES  Variable region is full, can not write other data into this region.

**/
typedef
EFI_STATUS
(EFIAPI *EDKII_VARIABLE_STORAGE_SUPPORT_UPDATE_NV_CACHE) (
  IN      CHAR16                      *VariableName,
  IN      EFI_GUID                    *VendorGuid,
  IN      VOID                        *Data,
  IN      UINTN                       DataSize,
  IN      UINT32                      Attributes      OPTIONAL,
  IN      UINT32                      KeyIndex        OPTIONAL,
  IN      UINT64                      MonotonicCount  OPTIONAL,
  IN      EFI_TIME                    *TimeStamp      OPTIONAL
  );

///
/// Variable Storage Support Protocol
/// Interface functions for variable storage driver to access core variable driver functions in DXE/SMM phase.
///
struct _EDKII_VARIABLE_STORAGE_SUPPORT_PROTOCOL {
  EDKII_VARIABLE_STORAGE_SUPPORT_NOTIFY_WRITE_SERVICE_READY     NotifyWriteServiceReady;  ///< Notify that SetVariable() is ready
  EDKII_VARIABLE_STORAGE_SUPPORT_NOTIFY_SMM_IO_COMPLETE         NotifySmmIoComplete;      ///< Notify that SMM I/O is complete
  EDKII_VARIABLE_STORAGE_SUPPORT_UPDATE_NV_CACHE                UpdateNvCache;            ///< Update the NV cache with a new value for the given variable
};

#endif

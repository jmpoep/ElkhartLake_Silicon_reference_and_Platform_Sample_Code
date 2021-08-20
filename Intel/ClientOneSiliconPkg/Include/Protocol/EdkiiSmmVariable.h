/** @file
  EDKII SMM Variable Protocol is related to the EDK II-specific implementation of
  variables and intended for use as a means to store data in the EFI SMM environment.

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

#ifndef __EDKII_SMM_VARIABLE_H__
#define __EDKII_SMM_VARIABLE_H__

//@todo: Add a notification to EFI_SMM_VARIABLE_PROTOCOL that is is the legacy protocol that is only included for
//       backwards compatibility and should not be used for new code.
typedef struct _EDKII_SMM_VARIABLE_PROTOCOL  EDKII_SMM_VARIABLE_PROTOCOL;

/**
  A callback function that is invoked once the data retrieved by a GetVariable request is ready.

  @param[in]       Context       A pointer given when SmmGetVariable was called. The callback may use this to
                                 help identify which variable operation the callback is being invoked for.
  @param[in]       Status        The result of the variable read operation. Possible values are:
                                 EFI_SUCCESS            The variable read completed successfully.
                                 EFI_NOT_FOUND          The variable was not found.
                                 EFI_BUFFER_TOO_SMALL   The DataSize is too small for the result.
                                 EFI_DEVICE_ERROR       The variable could not be retrieved due to a hardware error.
                                 EFI_SECURITY_VIOLATION The variable could not be retrieved due to an authentication failure.
  @param[in]       Attributes    The attributes bitmask for the variable.
  @param[in]       DataSize      The size of data returned in Data.
  @param[in]       Data          The contents of the variable.

**/
typedef
VOID
(EFIAPI *EDKII_SMM_GET_VARIABLE_CALLBACK)(
  IN      VOID                              *Context,            OPTIONAL
  IN      EFI_STATUS                        Status,
  IN      UINT32                            Attributes,
  IN      UINTN                             DataSize,
  IN      VOID                              *Data
  );

/**
  Begins the operation to return the value of a variable. At a later point in time, when the value of the variable
  is ready the provided callback function will be invoked.

  @param[in]       Context       A caller provided pointer that will be passed to the callback
                                 function when the callback is invoked. The caller may use this to
                                 help identify which variable operation the callback is being invoked for.
  @param[in]       VariableName  A Null-terminated string that is the name of the vendor's
                                 variable.
  @param[in]       VendorGuid    A unique identifier for the vendor.
  @param[in]       DataSize      The size in bytes of the return Data buffer.
  @param[out]      Data          The buffer to return the contents of the variable.
  @param[in]       Callback      The function to invoke once the variable data is ready.

  @retval EFI_SUCCESS            The function completed successfully.
  @retval EFI_INVALID_PARAMETER  VariableName is NULL.
  @retval EFI_INVALID_PARAMETER  VendorGuid is NULL.
  @retval EFI_INVALID_PARAMETER  DataSize is NULL.
  @retval EFI_INVALID_PARAMETER  The DataSize is not too small and Data is NULL.
  @retval EFI_NOT_READY          Another driver is presently using the Variable Services

**/
typedef
EFI_STATUS
(EFIAPI *EDKII_SMM_GET_VARIABLE)(
  IN      VOID                              *Context,       OPTIONAL
  IN      CHAR16                            *VariableName,
  IN      EFI_GUID                          *VendorGuid,
  IN      UINTN                             DataSize,
  IN      VOID                              *Data,
  IN      EDKII_SMM_GET_VARIABLE_CALLBACK   Callback
  );

/**
  A callback function that is invoked once the data provided to SetVariable has been written to non-volatile media.

  @param[in]       Context       A pointer given when SmmGetVariable was called. The callback may use this to
                                 help identify which variable operation the callback is being invoked for.
  @param[in]       Status        The result of the variable write operation. Possible values are:
                                 EFI_SUCCESS            The firmware has successfully stored the variable and its data as
                                                        defined by the Attributes.
                                 EFI_OUT_OF_RESOURCES   Not enough storage is available to hold the variable and its data.
                                 EFI_DEVICE_ERROR       The variable could not be written due to a hardware error.
                                 EFI_WRITE_PROTECTED    The variable in question is read-only.
                                 EFI_WRITE_PROTECTED    The variable in question cannot be deleted.
                                 EFI_SECURITY_VIOLATION The variable could not be written due to EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS
                                                        or EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACESS being set, but the AuthInfo
                                                        does NOT pass the validation check carried out by the firmware.
                                 EFI_NOT_FOUND          The variable trying to be updated or deleted was not found.

**/
typedef
VOID
(EFIAPI *EDKII_SMM_SET_VARIABLE_CALLBACK)(
  IN      VOID                              *Context,            OPTIONAL
  IN      EFI_STATUS                        Status
  );

/**
  Begins the operation to write the value of a variable. At a later point in time, when the variable write operation
  is complete the provided callback function will be invoked.

  @param[in]  Context            A caller provided pointer that will be passed to the callback
                                 function when the callback is invoked. The caller may use this to
                                 help identify which variable operation the callback is being invoked for.
  @param[in]  VariableName       A Null-terminated string that is the name of the vendor's variable.
                                 Each VariableName is unique for each VendorGuid. VariableName must
                                 contain 1 or more characters. If VariableName is an empty string,
                                 then EFI_INVALID_PARAMETER is returned.
  @param[in]  VendorGuid         A unique identifier for the vendor.
  @param[in]  Attributes         Attributes bitmask to set for the variable.
  @param[in]  DataSize           The size in bytes of the Data buffer. Unless the EFI_VARIABLE_APPEND_WRITE,
                                 EFI_VARIABLE_AUTHENTICATED_WRITE_ACCESS, or
                                 EFI_VARIABLE_TIME_BASED_AUTHENTICATED_WRITE_ACCESS attribute is set, a size of zero
                                 causes the variable to be deleted. When the EFI_VARIABLE_APPEND_WRITE attribute is
                                 set, then a SetVariable() call with a DataSize of zero will not cause any change to
                                 the variable value (the timestamp associated with the variable may be updated however
                                 even if no new data value is provided,see the description of the
                                 EFI_VARIABLE_AUTHENTICATION_2 descriptor below. In this case the DataSize will not
                                 be zero since the EFI_VARIABLE_AUTHENTICATION_2 descriptor will be populated).
  @param[in]  Data               The contents for the variable.
  @param[in]  Callback           The function to invoke once the variable is written.

  @retval EFI_SUCCESS            The write request has been successfully queued.
  @retval EFI_INVALID_PARAMETER  An invalid combination of attribute bits, name, and GUID was supplied, or the
                                 DataSize exceeds the maximum allowed.
  @retval EFI_INVALID_PARAMETER  VariableName is an empty string.
  @retval EFI_NOT_READY          Another driver is presently using the Variable Services

**/
typedef
EFI_STATUS
(EFIAPI *EDKII_SMM_SET_VARIABLE)(
  IN      VOID                              *Context,         OPTIONAL
  IN      CHAR16                            *VariableName,
  IN      EFI_GUID                          *VendorGuid,
  IN      UINT32                            Attributes,
  IN      UINTN                             DataSize,
  IN      VOID                              *Data,
  IN      EDKII_SMM_SET_VARIABLE_CALLBACK   Callback
  );

///
/// EDKII SMM Variable Protocol is intended for use as a means
/// to store data in the EFI SMM environment.
///
struct _EDKII_SMM_VARIABLE_PROTOCOL {
  EDKII_SMM_GET_VARIABLE      SmmGetVariable;
  EFI_GET_NEXT_VARIABLE_NAME  SmmGetNextVariableName;
  EDKII_SMM_SET_VARIABLE      SmmSetVariable;
  EFI_QUERY_VARIABLE_INFO     SmmQueryVariableInfo;
};

extern EFI_GUID gEdkiiSmmVariableProtocolGuid;

#endif

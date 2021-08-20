/** @file
  Defines common functions used in the CseVariableStorage module.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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

#ifndef _CSE_VARIABLE_STORAGE_INTERNAL_H_
#define _CSE_VARIABLE_STORAGE_INTERNAL_H_

#include <CseVariableStorage.h>
#include <Library/BaseLib.h>

#include <Guid/CseVariableStorageProtocolInstanceGuid.h>
#include <Protocol/CseVariableStorageSupportProtocol.h>
#include <Protocol/VariableStorageProtocol.h>
#include <Protocol/VariableStorageSupportProtocol.h>

extern CSE_VARIABLE_STORAGE_STORE         *mCseVariableStorageInfo[];
extern EDKII_VARIABLE_STORAGE_PROTOCOL    mCseVariableStorageProtocol;

/**
  CSE Variable Storage Update Cache.

  @param[in]      None.

  @retval         EFI_SUCCESS               The update operation was successful.
  @retval         EFI_OUT_OF_RESOURCES      Unable to allocate required memory space.
  @retval         EFI_ABORTED               The Cse read operation could not be completed successfully.
  @retval         Others                    An error occurred updating the data.
**/
EFI_STATUS
EFIAPI
CseVariableStorageUpdateCache (
  VOID
  );
/**
  Performs common initialization needed for a CSE variable storage module.

  @param  None

  @retval EFI_SUCCESS  The module was initialized successfully.
  @retval Others       The module could not be initialized.
**/
EFI_STATUS
EFIAPI
CseVariableStorageCommonInitialize (
  VOID
  );

/**
  Notifies the CSE variable driver that the runtime component of the driver is initialized.

**/
VOID
EFIAPI
CseVariableStorageRuntimeInitialized (
  VOID
  );

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
VOID
EFIAPI
CseVariableStorageReadIoComplete (
  IN      EFI_STATUS        Status,
  IN      VOID              *Data,
  IN      UINTN             VariableSize
  );

/**
  Retrieves a protocol instance-specific GUID.

  Returns a unique GUID per EDKII_VARIABLE_STORAGE_PROTOCOL instance.

  @param[in]       This                   A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[out]      VariableGuid           A pointer to an EFI_GUID that is this protocol instance's GUID.

  @retval          EFI_SUCCESS            The data was returned successfully.
  @retval          EFI_INVALID_PARAMETER  A required parameter is NULL.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGetId (
  IN CONST  EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  OUT       EFI_GUID                          *InstanceGuid
  );

/**
  This service retrieves a variable's value using its name and GUID.

  Read the specified variable from the CSE NVM variable store. If the Data
  buffer is too small to hold the contents of the variable,
  the error EFI_BUFFER_TOO_SMALL is returned and DataSize is set to the
  required buffer size to obtain the data.

  @param[in]       This                   A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[in]       AtRuntime              TRUE if the platform is in OS Runtime, FALSE if still in Pre-OS stage
  @param[in]       FromSmm                TRUE if GetVariable() is being called by SMM code, FALSE if called by DXE code
  @param[in]       VariableName           A pointer to a null-terminated string that is the variable's name.
  @param[in]       VariableGuid           A pointer to an EFI_GUID that is the variable's GUID. The combination of
                                          VariableGuid and VariableName must be unique.
  @param[out]      Attributes             If non-NULL, on return, points to the variable's attributes.
  @param[in, out]  DataSize               On entry, points to the size in bytes of the Data buffer.
                                          On return, points to the size of the data returned in Data.
  @param[out]      Data                   Points to the buffer which will hold the returned variable value.
  @param[out]      CommandInProgress      TRUE if the command requires asyncronous I/O and has not completed yet
                                          If this parameter is TRUE, then Attributes, DataSize, and Data will not
                                          be updated by this driver and do not contain valid data.  Asyncronous I/O
                                          should only be required during OS runtime phase, this return value must be
                                          FALSE if the AtRuntime parameter is FALSE.  This parameter should only be
                                          used by SMM Variable Storage implementations.  Runtime DXE implementations
                                          must always return FALSE.  If CommandInProgress is returned TRUE, then the
                                          function must return EFI_SUCCESS.

  @retval          EFI_SUCCESS            The variable was read successfully.
  @retval          EFI_NOT_FOUND          The variable could not be found.
  @retval          EFI_BUFFER_TOO_SMALL   The DataSize is too small for the resulting data.
                                          DataSize is updated with the size required for
                                          the specified variable.
  @retval          EFI_INVALID_PARAMETER  VariableName, VariableGuid, DataSize or Data is NULL.
  @retval          EFI_DEVICE_ERROR       The variable could not be retrieved because of a device error.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGetVariable (
  IN CONST  EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN        BOOLEAN                           AtRuntime,
  IN        BOOLEAN                           FromSmm,
  IN CONST  CHAR16                            *VariableName,
  IN CONST  EFI_GUID                          *VariableGuid,
  OUT       UINT32                            *Attributes OPTIONAL,
  IN OUT    UINTN                             *DataSize,
  OUT       VOID                              *Data,
  OUT       BOOLEAN                           *CommandInProgress
  );

/**
  This service retrieves an authenticated variable's value using its name and GUID.

  Read the specified authenticated variable from the UEFI variable store. If the Data
  buffer is too small to hold the contents of the variable,
  the error EFI_BUFFER_TOO_SMALL is returned and DataSize is set to the
  required buffer size to obtain the data.

  @param[in]       This                   A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[in]       AtRuntime              TRUE if the platform is in OS Runtime, FALSE if still in Pre-OS stage
  @param[in]       FromSmm                TRUE if GetVariable() is being called by SMM code, FALSE if called by DXE code
  @param[in]       VariableName           A pointer to a null-terminated string that is the variable's name.
  @param[in]       VariableGuid           A pointer to an EFI_GUID that is the variable's GUID. The combination of
                                          VariableGuid and VariableName must be unique.
  @param[out]      Attributes             If non-NULL, on return, points to the variable's attributes.
  @param[in, out]  DataSize               On entry, points to the size in bytes of the Data buffer.
                                          On return, points to the size of the data returned in Data.
  @param[out]      Data                   Points to the buffer which will hold the returned variable value.
  @param[out]      KeyIndex               Index of associated public key in database
  @param[out]      MonotonicCount         Associated monotonic count value to protect against replay attack
  @param[out]      TimeStamp              Associated TimeStamp value to protect against replay attack
  @param[out]      CommandInProgress      TRUE if the command requires asyncronous I/O and has not completed yet
                                          If this parameter is TRUE, then Attributes, DataSize, Data, KeyIndex,
                                          MonotonicCount, and TimeStamp will not be updated by this driver
                                          and do not contain valid data.  Asyncronous I/O should only be required
                                          during OS runtime phase, this return value must be FALSE if the AtRuntime
                                          parameter is FALSE.  This parameter should only be used by SMM Variable
                                          Storage implementations.  Runtime DXE implementations must always return
                                          FALSE.  If CommandInProgress is returned TRUE, then the function must return
                                          EFI_SUCCESS.

  @retval          EFI_SUCCESS            The variable was read successfully.
  @retval          EFI_NOT_FOUND          The variable could not be found.
  @retval          EFI_BUFFER_TOO_SMALL   The DataSize is too small for the resulting data.
                                          DataSize is updated with the size required for
                                          the specified variable.
  @retval          EFI_INVALID_PARAMETER  VariableName, VariableGuid, DataSize or Data is NULL.
  @retval          EFI_DEVICE_ERROR       The variable could not be retrieved because of a device error.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGetAuthenticatedVariable (
  IN CONST  EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN        BOOLEAN                           AtRuntime,
  IN        BOOLEAN                           FromSmm,
  IN CONST  CHAR16                            *VariableName,
  IN CONST  EFI_GUID                          *VariableGuid,
  OUT       UINT32                            *Attributes,
  IN OUT    UINTN                             *DataSize,
  OUT       VOID                              *Data,
  OUT       UINT32                            *KeyIndex,
  OUT       UINT64                            *MonotonicCount,
  OUT       EFI_TIME                          *TimeStamp,
  OUT       BOOLEAN                           *CommandInProgress
  );

/**
  Return the next variable name and GUID.

  This function is called multiple times to retrieve the VariableName
  and VariableGuid of all variables currently available in the system.
  On each call, the previous results are passed into the interface,
  and, on return, the interface returns the data for the next
  interface. When the entire variable list has been returned,
  EFI_NOT_FOUND is returned.

  @param[in]      This                   A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.

  @param[in, out] VariableNameSize       On entry, points to the size of the buffer pointed to by
                                         VariableName. On return, the size of the variable name buffer.
  @param[in, out] VariableName           On entry, a pointer to a null-terminated string that is the
                                         variable's name. On return, points to the next variable's
                                         null-terminated name string.
  @param[in, out] VariableGuid           On entry, a pointer to an EFI_GUID that is the variable's GUID.
                                         On return, a pointer to the next variable's GUID.
  @param[out]     VariableAttributes     A pointer to the variable attributes.

  @retval         EFI_SUCCESS            The variable was read successfully.
  @retval         EFI_NOT_FOUND          The variable could not be found.
  @retval         EFI_BUFFER_TOO_SMALL   The VariableNameSize is too small for the resulting
                                         data. VariableNameSize is updated with the size
                                         required for the specified variable.
  @retval         EFI_INVALID_PARAMETER  VariableName, VariableGuid or
                                         VariableNameSize is NULL.
  @retval         EFI_DEVICE_ERROR       The variable could not be retrieved because of a device error.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGetNextVariableName (
  IN CONST  EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN OUT    UINTN                             *VariableNameSize,
  IN OUT    CHAR16                            *VariableName,
  IN OUT    EFI_GUID                          *VariableGuid,
  OUT       UINT32                            *VariableAttributes
  );

/**
  Returns information on the amount of space available in the variable store

  @param[in]  This                           A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[in]  AtRuntime                      TRUE is the platform is in OS Runtime, FALSE if still in Pre-OS stage
  @param[out] VariableStoreSize              The total size of the NV storage. Indicates the maximum amount
                                             of data that can be stored in this NV storage area.
  @param[out] CommonVariablesTotalSize       The total combined size of all the common UEFI variables that are
                                             stored in this NV storage area. Excludes variables with the
                                             EFI_VARIABLE_HARDWARE_ERROR_RECORD attribute set.
  @param[out] HwErrVariablesTotalSize        The total combined size of all the UEFI variables that have the
                                             EFI_VARIABLE_HARDWARE_ERROR_RECORD attribute set and which are
                                             stored in this NV storage area. Excludes all other variables.

  @retval     EFI_INVALID_PARAMETER          Any of the given parameters are NULL
  @retval     EFI_SUCCESS                    Space information returned successfully.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGetStorageUsage (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN          BOOLEAN                           AtRuntime,
  OUT         UINT32                            *VariableStoreSize,
  OUT         UINT32                            *CommonVariablesTotalSize,
  OUT         UINT32                            *HwErrVariablesTotalSize
  );

/**
  Returns whether this NV storage area supports storing authenticated variables or not

  @param[in]  This                           A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[out] AuthSupported                  TRUE if this NV storage area can store authenticated variables,
                                             FALSE otherwise

  @retval     EFI_SUCCESS                    AuthSupported was returned successfully.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGetAuthenticatedSupport (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  OUT         BOOLEAN                           *AuthSupported
  );

/**
  This code sets a variable's value using its name and GUID.

  Caution: This function may receive untrusted input.
  This function may be invoked in SMM mode, and datasize and data are external input.
  This function will do basic validation, before parsing the data.
  This function will parse the authentication carefully to avoid security issues, like
  buffer overflow, integer overflow.
  This function will check attribute carefully to avoid authentication bypass.

  @param[in]  This                             A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[in]  AtRuntime                        TRUE if the platform is in OS Runtime, FALSE if still in Pre-OS stage
  @param[in]  FromSmm                          TRUE if GetVariable() is being called by SMM code, FALSE if called by DXE code
  @param[in]  VariableName                     Name of Variable to be found.
  @param[in]  VendorGuid                       Variable vendor GUID.
  @param[in]  Attributes                       Attribute value of the variable found
  @param[in]  DataSize                         Size of Data found. If size is less than the
                                               data, this value contains the required size.
  @param[in]  Data                             Data pointer.
  @param[in]  KeyIndex                         If writing an authenticated variable, the public key index
  @param[in]  MonotonicCount                   If writing a monotonic counter authenticated variable, the counter value
  @param[in]  TimeStamp                        If writing a timestamp authenticated variable, the timestamp value
  @param[out] CommandInProgress                TRUE if the command requires asyncronous I/O and has not completed yet.
                                               Asyncronous I/O should only be required during OS runtime phase, this
                                               return value must be FALSE if the AtRuntime parameter is FALSE.  This
                                               parameter should only be used by SMM Variable Storage implementations.
                                               Runtime DXE implementations must always return FALSE.  If
                                               CommandInProgress is returned TRUE, then the function must return
                                               EFI_SUCCESS.

  @retval     EFI_INVALID_PARAMETER            Invalid parameter.
  @retval     EFI_SUCCESS                      Set successfully.
  @retval     EFI_OUT_OF_RESOURCES             Resource not enough to set variable.
  @retval     EFI_NOT_FOUND                    Not found.
  @retval     EFI_WRITE_PROTECTED              Variable is read-only.

**/
EFI_STATUS
EFIAPI
CseVariableStorageSetVariable (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN          BOOLEAN                           AtRuntime,
  IN          BOOLEAN                           FromSmm,
  IN          CHAR16                            *VariableName,
  IN          EFI_GUID                          *VendorGuid,
  IN          UINT32                            Attributes,
  IN          UINTN                             DataSize,
  IN          VOID                              *Data,
  IN          UINT32                            KeyIndex       OPTIONAL,
  IN          UINT64                            MonotonicCount OPTIONAL,
  IN          EFI_TIME                          *TimeStamp     OPTIONAL,
  OUT         BOOLEAN                           *CommandInProgress
  );

/**
  Returns whether this NV storage area is ready to accept calls to SetVariable() or not

  @param[in]  This                           A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.

  @retval     TRUE                           The NV storage area is ready to accept calls to SetVariable()
  @retval     FALSE                          The NV storage area is not ready to accept calls to SetVariable()

**/
BOOLEAN
EFIAPI
CseVariableStorageWriteServiceIsReady (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This
  );

/**
  Performs variable store garbage collection/reclaim operation.

  @param[in]  This                             A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.

  @retval     EFI_INVALID_PARAMETER            Invalid parameter.
  @retval     EFI_SUCCESS                      Garbage Collection Successful.
  @retval     EFI_OUT_OF_RESOURCES             Insufficient resource to complete garbage collection.
  @retval     EFI_WRITE_PROTECTED              Write services are not yet ready.

**/
EFI_STATUS
EFIAPI
CseVariableStorageGarbageCollect (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This
  );

/**
  Queries the variable store to determine if asyncronous I/O is required during OS runtime to get/set variables.
  Different return values may be supplied depending on whether the origin of the call is SMM or not.

  @param[in]  This                           A pointer to this instance of the EDKII_VARIABLE_STORAGE_PROTOCOL.
  @param[in]  FromSmm                        TRUE if Get/SetVariable() is being called by SMM code, FALSE if called by DXE code

  @retval     TRUE                           Asyncronous I/O is required during OS runtime to call to Get/SetVariable()
  @retval     FALSE                          Asyncronous I/O is not required during OS runtime to call to Get/SetVariable()

**/
BOOLEAN
EFIAPI
CseVariableStorageAsyncIoRequired (
  IN CONST    EDKII_VARIABLE_STORAGE_PROTOCOL   *This,
  IN          BOOLEAN                           FromSmm
  );

/**
  Sets the CSE NVM variable with the supplied data. These arguments are similar to those in the EFI Variable services.

  @param[in]      VariableName         Name of variable.
  @param[in]      VendorGuid           Guid of variable.
  @param[in]      Data                 Variable data.
  @param[in]      DataSize             Size of data. 0 means delete.
  @param[in]      Attributes           Attributes of the variable. No runtime or bootservice attribute set means delete.
  @param[out]     CommandInProgress    Determines whether asynchronous I/O should be used or the variable should
                                       immediately be written.
  @param[in,out]  IndexVariable        The variable found in the header region corresponding to this variable.
  @param[in]      FromSmm              Indicates the variable caller invoked variable services from SMM.
  @param[in]      KeyIndex             Index of associated public key in database
  @param[in]      MonotonicCount       Associated monotonic count value to protect against replay attack
  @param[in]      TimeStamp            Associated TimeStamp value to protect against replay attack

  @retval         EFI_SUCCESS          The set operation was successful.
  @retval         Others               The set operation failed.
**/
EFI_STATUS
EFIAPI
SetVariable (
  IN       CHAR16                      *VariableName,
  IN       EFI_GUID                    *VendorGuid,
  IN       VOID                        *Data,
  IN       UINTN                       DataSize,
  IN       UINT32                      Attributes,
  OUT      BOOLEAN                     *CommandInProgress,
  IN OUT   VARIABLE_NVM_POINTER_TRACK  *IndexVariable,
  IN       BOOLEAN                     FromSmm,
  IN       UINT32                      KeyIndex        OPTIONAL,
  IN       UINT64                      MonotonicCount  OPTIONAL,
  IN       EFI_TIME                    *TimeStamp      OPTIONAL
  );

#endif

/** @file
  CSE Variable Storage Common Declarations

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#ifndef _CSE_VARIABLE_STORAGE_H_
#define _CSE_VARIABLE_STORAGE_H_

#include <Base.h>
#include <Uefi.h>
#include <VariableNvmStorageFormat.h>

#define CSE_VARIABLE_MAX_DMA_SIZE                           SIZE_256KB
#define CSE_VARIABLE_MONOLITHIC_INDEX_UPDATE_SIZE_THRESHOLD 1024
#define CSE_VARIABLE_NVM_ALIGNMENT                          16

typedef struct _CSE_VARIABLE_STORAGE_STORE CSE_VARIABLE_STORAGE_STORE;

typedef enum {
  CseVariableStorageTypeSecurePreMemoryArea,  ///< Variable storage in a special area readable by CSE
  CseVariableStorageTypeGeneralDataArea,      ///< Variable storage within a general area of the NVM
  CseVariableStorageTypeMax                   ///< End of CSE variable store file types
} CSE_VARIABLE_STORAGE_TYPE;

typedef enum {
  Heci1Device,             ///< HECI1 Device
  Heci2Device              ///< HECI2 Device
} CSE_VARIABLE_HECI_DEVICE;

#pragma pack(push, 1)

//
// Maintains common variable information
//
typedef struct {
  CHAR16      *VariableName;
  EFI_GUID    *VendorGuid;
  VOID        *Data;
  UINTN       DataSize;
  UINT32      Attributes;
} CSE_VARIABLE_INFORMATION_TRACK;

//
// Maintains authenticated variable information
//
typedef struct {
  UINT64      MonotonicCount;  ///< Associated monotonic count value to protect against replay attack
  UINT32      PubKeyIndex;     ///< Index of associated public key in database
  EFI_TIME    *TimeStamp;      ///< Associated TimeStamp value to protect against replay attack
} CSE_VARIABLE_AUTHENTICATED_FIELD_TRACK;

//
// Maintains information for a CSE variable storage store
//
typedef struct {
  EFI_GUID                         Guid;
  CSE_VARIABLE_STORAGE_TYPE        Type;
  BOOLEAN                          Enabled;
  BOOLEAN                          Established;
  BOOLEAN                          DataExpansionAllowed;
  UINT32                           MaximumSize;
  UINT32                           Offset;
  VOID                             *Header;
  VOID                             *Data;
  CHAR8                            *Name;
  VOID                             *OtherInfo;
} CSE_VARIABLE_STORAGE_INFO;

//
// Maintains information regarding the index area for a variable
//
typedef struct {
  BOOLEAN                             Valid;
  BOOLEAN                             AuthFlag;
  CONST CSE_VARIABLE_STORAGE_STORE    *CseVariableStore;
  VARIABLE_NVM_STORE_HEADER           VariableStoreHeader;
  VARIABLE_NVM_STORE_HEADER           *VariableStoreIndexPtr;
  AUTHENTICATED_VARIABLE_NVM_HEADER   VariableHeader;
  AUTHENTICATED_VARIABLE_NVM_HEADER   *VariableHeaderIndexPtr;
  CHAR16                              *VariableNamePtr;
} CSE_VARIABLE_STORAGE_INDEX_CONTEXT;

#pragma pack(pop)

/**
  Creates an empty UEFI variable store in the CSE Variable Storage area.

  @param[in,out]  This                        A pointer to a structure that contains CSE variable storage store info.
  @param[out]     VariableStore               A pointer to the caller allocated buffer for the variable store.
  @param[in,out]  VariableStoreBufferLength   The size in bytes of the buffer available on input.
                                              The size in bytes of the variable store created on output.

  @retval         EFI_SUCCESS                 The variable store was created successfully.
  @retval         EFI_INVALID_PARAMETER       A pointer parameter given was NULL.
  @retval         EFI_BUFFER_TOO_SMALL        VariableStoreBufferLength is too small to hold a variable store.
  @retval         Others                      A different error occurred attempting to create the variable store.
**/
typedef
EFI_STATUS
(EFIAPI *CSE_VARIABLE_STORAGE_CREATE_NEW_STORE)(
  IN OUT  CSE_VARIABLE_STORAGE_STORE *This,
  OUT     VOID                       *VariableStore,
  IN OUT  UINTN                      *VariableStoreBufferLength
  );

/**
  Reclaims a CSE Variable Storage store.

  @param[in]      This                      A pointer to a CSE_VARIABLE_STORAGE_STORE structure.

  @retval         EFI_SUCCESS               The reclaim operation was successful.
  @retval         EFI_UNSUPPORTED           A reclaim operation is not available for this CSE storage store.
  @retval         EFI_INVALID_PARAMETER     A pointer given to the function is NULL.
  @retval         EFI_NOT_READY             The CSE variable store used for the reclaim operation is not available.
  @retval         EFI_OUT_OF_RESOURCES      The memory resources available are insufficient for the reclaim operation.
  @retval         EFI_LOAD_ERROR            An error occurred loading data via CSE from non-volatile memory.
  @retval         Others                    The pre-memory file reclaim operation failed.
**/
typedef
EFI_STATUS
(EFIAPI *CSE_VARIABLE_STORAGE_RECLAIM_VARIABLE)(
  IN  CONST CSE_VARIABLE_STORAGE_STORE    *This
  );

/**
  Writes a new variable in CSE variable storage.

  @param[in]  This                             Pointer to a structure that contains CSE variable storage store info.
  @param[in]  VariableInformationTrack         Pointer to a structure that maintains common variable information.
  @param[in]  VariableStoreInfo                Pointer to a structure that maintains variable store information.
  @param[in]  AuthenticatedVariableFieldTrack  Pointer to a structure which maintains authenticated field values.
  @param[out] CommandInProgress                TRUE if the command requires asynchronous I/O and has not completed yet.
                                               If this command is TRUE, then the Data and DataSize are not updated and do
                                               not contain valid data.

  @retval     EFI_SUCCESS                      The variable write operation was successful.
  @retval     Others                           The variable write operation failed.
**/
typedef
EFI_STATUS
(EFIAPI *CSE_VARIABLE_STORAGE_WRITE_VARIABLE)(
  IN  CONST  CSE_VARIABLE_STORAGE_STORE              *This,
  IN  CONST  CSE_VARIABLE_INFORMATION_TRACK          *VariableInformationTrack,
  IN         VARIABLE_NVM_STORE_INFO                 *VariableStoreInfo,
  IN  CONST  CSE_VARIABLE_AUTHENTICATED_FIELD_TRACK  *VariableAuthenticatedFieldTrack OPTIONAL,
  OUT        BOOLEAN                                 *CommandInProgress OPTIONAL
  );

/**
  Updates a variable in CSE variable storage.

  @param[in]  This                             Pointer to a structure that contains CSE variable storage store info.
  @param[in]  VariableInformationTrack         Pointer to a structure that maintains common variable information.
  @param[in]  VariablePtrTrack                 Pointer to a structure that maintains variable header pointers.
  @param[in]  VariableStoreInfo                Pointer to a structure that maintains variable store information.
  @param[in]  VariableAuthenticatedFieldTrack  Pointer to a structure which maintains authenticated field values.
  @param[out] CommandInProgress                TRUE if the command requires asynchronous I/O and has not completed yet.
                                               If this command is TRUE, then the Data and DataSize are not updated and do
                                               not contain valid data.

  @retval     EFI_SUCCESS                      The variable update operation was successful.
  @retval     EFI_INVALID_PARAMETER            A pointer given was NULL or pointed to invalid data.
  @retval     EFI_UNSUPPORTED                  The update operation is not valid at this time.
  @retval     Others                           The variable update operation failed.
**/
typedef
EFI_STATUS
(EFIAPI *CSE_VARIABLE_STORAGE_UPDATE_VARIABLE)(
  IN  CONST  CSE_VARIABLE_STORAGE_STORE              *This,
  IN  CONST  CSE_VARIABLE_INFORMATION_TRACK          *VariableInformationTrack,
  IN  CONST  VARIABLE_NVM_POINTER_TRACK              *VariablePtrTrack,
  IN         VARIABLE_NVM_STORE_INFO                 *VariableStoreInfo,
  IN  CONST  CSE_VARIABLE_AUTHENTICATED_FIELD_TRACK  *VariableAuthenticatedFieldTrack OPTIONAL,
  OUT        BOOLEAN                                 *CommandInProgress OPTIONAL
  );

/**
  Deletes a variable in CSE variable storage.

  @param[in]  This                     A pointer to a structure that contains CSE variable storage store info.
  @param[in]  VariableStoreInfo        Pointer to a structure that maintains variable store information.
  @param[in]  VariableHeader           Pointer to the variable header that should be deleted.
  @param[out] CommandInProgress        TRUE if the command requires asynchronous I/O and has not completed yet.
                                       If this command is TRUE, then the Data and DataSize are not updated and do
                                       not contain valid data.

  @retval     EFI_SUCCESS              The variable was deleted successfully.
  @retval     EFI_INVALID_PARAMETER    The pointers given to the function are NULL or invalid.
  @retval     Others                   The variable deletion operation failed.
**/
typedef
EFI_STATUS
(EFIAPI *CSE_VARIABLE_STORAGE_DELETE_VARIABLE)(
  IN  CONST  CSE_VARIABLE_STORAGE_STORE *This,
  IN  CONST  VARIABLE_NVM_STORE_INFO    *VariableStoreInfo,
  IN         VARIABLE_NVM_HEADER        *VariableHeader,
  OUT        BOOLEAN                    *CommandInProgress OPTIONAL
  );


/**
  Reads data using a given type of CSE variable storage mechanism.

  The actual read is deferred if CommandInProgress is returned TRUE.

  @param[in]      This                    A pointer to a structure CSE Variable Storage Store structure.
  @param[out]     Data                    A pointer to a buffer that the data should be read into.
  @param[in,out]  DataSize                The length in bytes of data to read on input.
                                          The length in bytes of dapta read on output.
  @param[in]      Offset                  The offset in bytes from the base of the read area to begin reading.
  @param[out]     CommandInProgress       TRUE if the command requires asynchronous I/O and has not completed yet.
                                          If this command is TRUE, then the Data and DataSize are not updated and do
                                          not contain valid data.

  @retval     EFI_SUCCESS                 The data was read successfully.
  @retval     EFI_INVALID_PARAMETER       A parameter to the function was invalid such as a NULL pointer.
  @retval     EFI_ABORTED                 The read operation could not be completed successfully.
  @retval     Others                      An error occurred reading the data.

**/
typedef
EFI_STATUS
(EFIAPI *CSE_VARIABLE_STORAGE_READ_DATA)(
  IN  CONST  CSE_VARIABLE_STORAGE_STORE   *This,
  OUT        VOID                         *Data,
  IN  OUT    UINTN                        *DataSize,
  IN         UINT32                       Offset,
  OUT        BOOLEAN                      *CommandInProgress OPTIONAL
  );

/**
  Writes data using a given type of CSE variable storage mechanism.

  The actual write is deferred if CommandInProgress is returned TRUE.

  @param[in]  This                    A pointer to a structure CSE Variable Storage Store structure.
  @param[in]  Data                    A pointer to a buffer of data to write.
  @param[in]  DataSize                The length in bytes of data to write.
  @param[in]  Offset                  The offset in bytes from the base of the write area to write.
  @param[in]  Truncate                If true and a file system is used, the file will be truncated.
                                      If a file system is not used, this parameter is ignored.
  @param[in]  IndexContext            A structure with the index context for the variable being written.
  @param[out] CommandInProgress       TRUE if the command requires asynchronous I/O and has not completed yet.
                                      If this command is TRUE, then the Data and DataSize are not updated and do
                                      not contain valid data.

  @retval     EFI_SUCCESS             The data was written successfully.
  @retval     EFI_INVALID_PARAMETER   A parameter to the function was invalid such as a NULL pointer.
  @retval     EFI_UNSUPPORTED         The ability to write to CSE is not supported.
  @retval     EFI_ABORTED             The write operation could not be completed successfully.
  @retval     Others                  An error occurred writing the data.

**/
typedef
EFI_STATUS
(EFIAPI *CSE_VARIABLE_STORAGE_WRITE_DATA)(
  IN  CONST  CSE_VARIABLE_STORAGE_STORE         *This,
  IN  CONST  VOID                               *Data,
  IN         UINTN                              DataSize,
  IN         UINT32                             Offset,
  IN         BOOLEAN                            Truncate,
  IN  CONST  CSE_VARIABLE_STORAGE_INDEX_CONTEXT *IndexContext, OPTIONAL
  OUT        BOOLEAN                            *CommandInProgress OPTIONAL
  );

#pragma pack(push,1)

struct _CSE_VARIABLE_STORAGE_STORE {
  // General Store Information
  CSE_VARIABLE_STORAGE_INFO               Info;
  // Basic I/O Primitives
  CSE_VARIABLE_STORAGE_READ_DATA          Read;
  CSE_VARIABLE_STORAGE_WRITE_DATA         Write;
  // Variable Operations
  CSE_VARIABLE_STORAGE_CREATE_NEW_STORE   CreateNewStore;
  CSE_VARIABLE_STORAGE_RECLAIM_VARIABLE   Reclaim;
  CSE_VARIABLE_STORAGE_WRITE_VARIABLE     WriteNewVariable;
  CSE_VARIABLE_STORAGE_UPDATE_VARIABLE    UpdateVariable;
  CSE_VARIABLE_STORAGE_DELETE_VARIABLE    DeleteVariable;
};

#pragma pack(pop)

#endif

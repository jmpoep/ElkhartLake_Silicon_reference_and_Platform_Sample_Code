/** @file
  PEI CSE Variable Storage IO Null Library implementation file.

@copyright
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

#include <Uefi.h>
#include <CseVariableStorage.h>
#include <Library/BaseLib.h>

/**
  Returns whether asynchronous I/O is required with CSE.

  @retval       TRUE        Asynchronous I/O is required.
  @retval       FALSE       Asynchronous I/O is not required.

**/
BOOLEAN
EFIAPI
CseVariableStorageIsAsyncIoRequired (
  VOID
  )
{
  return FALSE;
}

/**
  Reads data from a General Data CSE Variable Storage area.

  The actual read is deferred if CommandInProgress is returned TRUE.

  @param[in]      CseVariableStorageStore A pointer to a structure CSE Variable Storage Store structure.
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
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataRead (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE   *CseVariableStorageStore,
  OUT        VOID                         *Data,
  IN  OUT    UINTN                        *DataSize,
  IN         UINT32                       Offset,
  OUT        BOOLEAN                      *CommandInProgress OPTIONAL
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Writes data to a General Data CSE Variable Storage area.

  The actual write is deferred if CommandInProgress is returned TRUE.

  @param[in]  CseVariableStorageStore A pointer to a structure CSE Variable Storage Store structure.
  @param[in]  Data                    A pointer to a buffer of data to write.
  @param[in]  DataSize                The length in bytes of data to write.
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
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataWrite (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE         *CseVariableStorageStore,
  IN  CONST  VOID                               *Data,
  IN         UINTN                              DataSize,
  IN         BOOLEAN                            Truncate,
  IN  CONST  CSE_VARIABLE_STORAGE_INDEX_CONTEXT *IndexContext, OPTIONAL
  OUT        BOOLEAN                            *CommandInProgress OPTIONAL
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Reclaims a CSE Variable Storage General Data store.

  @param[in]      CseVariableStorageStore   A pointer to a structure CSE Variable Storage Store structure.

  @retval         EFI_SUCCESS               The reclaim operation was successful.
  @retval         EFI_UNSUPPORTED           A reclaim operation is not available for this CSE storage store.
  @retval         EFI_INVALID_PARAMETER     A pointer given to the function is NULL.
  @retval         EFI_NOT_READY             The CSE variable store used for the reclaim operation is not available.
  @retval         EFI_OUT_OF_RESOURCES      The memory resources available are insufficient for the reclaim operation.
  @retval         EFI_LOAD_ERROR            An error occurred loading data via CSE from non-volatile memory.
  @retval         Others                    The pre-memory file reclaim operation failed.
**/
EFI_STATUS
EFIAPI
CseVariableStorageGeneralDataReclaim (
  IN CONST CSE_VARIABLE_STORAGE_STORE           *CseVariableStorageStore
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Initializes a CSE Variable Storage index context structure for a new variable write.

  @param[in]  CseVariableStorageStore          Pointer to a structure that contains CSE variable storage store info.
  @param[in]  VariableStoreInfo                Pointer to a structure that maintains variable store information.
  @param[out] IndexContext                     Pointer to the index context structure to initialize.
  @param[out] IndexVariableStoreHeader         Pointer to an index area variable store header buffer.

  @retval     EFI_SUCCESS                      The variable write operation was successful.
  @retval     EFI_UNSUPPORTED                  CSE variable index context initialization is not supported.
  @retval     EFI_INVALID_PARAMETER            A required pointer is set to NULL.
**/
EFI_STATUS
EFIAPI
CseVariableStorageInitializeNewVariableContext (
  IN  CONST  CSE_VARIABLE_STORAGE_STORE   *CseVariableStorageStore,
  IN  VARIABLE_NVM_STORE_INFO             *VariableStoreInfo,
  OUT CSE_VARIABLE_STORAGE_INDEX_CONTEXT  *IndexContext,
  OUT VARIABLE_NVM_STORE_HEADER           **IndexVariableStoreHeader
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Starts dispatching all queued CSE variable storage messages from SMM.

  @retval     EFI_SUCCESS                 The command queue was enabled successfully.
  @retval     EFI_UNSUPPORTED             The CSE variable storage SMM command queue is not supported at this time.
  @retval     EFI_NOT_READY               The required interfaces are not available for communication at this time.
  @retval     Others                      An error occurred enabling the command queue.

**/
EFI_STATUS
EFIAPI
CseVariableStorageStartSmmCommandQueue (
  VOID
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Returns whether the command queue is enabled for CSE variable read operations.

  @retval     TRUE                        Command queue is enabled for CSE variable read operations.
  @retval     FALSE                       Command queue is disabled for CSE variable read operations.

**/
BOOLEAN
EFIAPI
CseVariableStorageIsReadCommandQueueEnabled (
  VOID
  )
{
  return FALSE;
}

/**
  Returns whether the command queue is enabled for CSE variable write operations.

  @retval     TRUE                        Command queue is enabled for CSE variable write operations.
  @retval     FALSE                       Command queue is disabled for CSE variable write operations.

**/
BOOLEAN
EFIAPI
CseVariableStorageIsWriteCommandQueueEnabled (
  VOID
  )
{
  return FALSE;
}

/**
  Disables the command queue for CSE variable read operations.

**/
VOID
EFIAPI
CseVariableStorageDisableReadCommandQueue (
  VOID
  )
{
  return;
}

/**
  Enables the command queue for CSE variable read operations.

**/
VOID
EFIAPI
CseVariableStorageEnableReadCommandQueue (
  VOID
  )
{
  return;
}


/**
  Disables the command queue for CSE variable write operations.

**/
VOID
EFIAPI
CseVariableStorageDisableWriteCommandQueue (
  VOID
  )
{
  return;
}

/**
  Enables the command queue for CSE variable write operations.

**/
VOID
EFIAPI
CseVariableStorageEnableWriteCommandQueue (
  VOID
  )
{
  return;
}
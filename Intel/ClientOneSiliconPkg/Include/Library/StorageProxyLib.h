/** @file
  Header file for the Storage Proxy library.

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

@par Specification
**/

#ifndef _STORAGE_PROXY_LIB_H_
#define _STORAGE_PROXY_LIB_H_

#include <StorageProxyMsg.h>

typedef struct _STORAGE_PROXY_INFO STORAGE_PROXY_INFO;

/**
  A proxy state action.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  A response was specified when only request is allowed for this message.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.

**/
typedef
EFI_STATUS
(EFIAPI *STORAGE_PROXY_ACTION)(
  IN OUT STORAGE_PROXY_INFO       *StorageProxyInfo
  );

///
/// Storage Proxy NVM Device Information
///
typedef struct {
  UINT32                             GppPartitionId;
  UINT32                             RpmbPartitionId;
  UINT8                              Reserved[8];
  STORAGE_PROXY_TYPE                 StorageType;
  UINT32                             SerialNumberSize;
  UINT8                              *SerialNumber;
} STORAGE_PROXY_DEVICE_INFO;

///
/// Storage Proxy Allocate Memory Buffer Information
///
typedef struct {
  VOID                               *Buffer;
  UINTN                              Size;
} STORAGE_PROXY_ALLOCATED_BUFFER_INFO;

///
/// Storage Proxy Instance Information
///
struct _STORAGE_PROXY_INFO {
  STORAGE_PROXY_ACTION                CurrentAction;
  STORAGE_PROXY_STATUS                CurrentStatus;
  STORAGE_PROXY_ALLOCATED_BUFFER_INFO AllocatedBuffer;
  STORAGE_PROXY_DEVICE_INFO           DeviceInfo;
  VOID                                *HostStorageProxyBuffer;
};

/**
  Checks if a Storage Proxy operation is in progress.

  @retval         TRUE        The storage proxy is busy.
  @retval         FALSE       The storage proxy is not busy.
**/
BOOLEAN
EFIAPI
StorageProxyOperationInProgress (
  VOID
  );

/**
  Checks if the Storage Proxy is busy.

  @param [in]     TimeoutMs               The number of milliseconds until the timer expires.

  @retval         EFI_SUCCESS             The storage proxy is not busy.
  @retval         EFI_TIMEOUT             The storage proxy was busy for TriggerTime.
  @reval          Others                  An error occurred in the timer.
**/
EFI_STATUS
EFIAPI
StorageProxyCheckBusy (
  IN UINT32              TimeoutMs
  );

/**
  Checks if the Storage Proxy is idle.

  @param [in]     TimeoutMs               The number of milliseconds until the timer expires.

  @retval         EFI_NOT_READY           The storage proxy is busy.
  @retval         EFI_SUCCESS             The storage proxy was idle for TriggerTime.
  @reval          Others                  An error occurred in the timer.
**/
EFI_STATUS
EFIAPI
StorageProxyCheckIdle (
  IN UINT32              TimeoutMs
  );

/**
  Sends a storage proxy response message indicating an error occurred.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxySendErrorMessage (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  );

/**
  Sends the storage proxy Stop message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyStop (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  );

/**
  Handles the storage proxy RPMB Write message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyRpmbWrite (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  );

/**
  Handles the storage proxy RPMB Read message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyRpmbRead (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  );

/**
  Handles the storage proxy RPMB Get Counter message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyRpmbGetCounter (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  );

/**
  Handles the storage proxy GPP Write message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyGppWrite (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  );

/**
  Handles the storage proxy GPP Read message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyGppRead (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  );

/**
  Sends the storage proxy Initialization message.

  This function will initialize STORAGE_PROXY_INFO structure. The caller should be aware the any previous information
  will be lost when this function returns.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @retval         EFI_OUT_OF_RESOURCES   Insufficient memory resources exist to allocate the storage proxy info structure.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyInit (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  );

/**
  Sends the storage proxy Status message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo parameter is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyStatus (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  );

/**
  Handles the storage proxy Allocate Memory Buffer message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyAllocateMemoryBuffer (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  );

/**
  Handles the storage proxy Commit Memory Buffer message.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyCommitMemoryBuffer (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  );

/**
  Processes a storage proxy request from CSME.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer is NULL.
  @retval         EFI_NOT_FOUND          The HECI protocol could not be found.
  @retval         EFI_UNSUPPORTED        The HECI device is not in a normal state.
  @reval          Others                 An error occurred in the message transaction.
**/
EFI_STATUS
EFIAPI
StorageProxyProcessRequest (
  IN OUT STORAGE_PROXY_INFO             *StorageProxyInfo
  );

/**
  Checks if a storage proxy request was sent from CSME.

  @param[in,out]  StorageProxyInfo       A pointer to an instance of a STORAGE_PROXY_INFO structure.

  @retval         EFI_SUCCESS            The storage proxy message was successful.
  @retval         EFI_DEVICE_ERROR       An error occurred getting the BAR from the storage proxy HECI device.
  @retval         EFI_INVALID_PARAMETER  The StorageProxyInfo pointer passed to the function is NULL.
**/
EFI_STATUS
EFIAPI
StorageProxyCheckForRequest (
  IN OUT STORAGE_PROXY_INFO              *StorageProxyInfo
  );

#endif

/** @file
  Header file for the Block IO Wrapper library.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

#ifndef _BLOCK_IO_WRAPPER_LIB_H_
#define _BLOCK_IO_WRAPPER_LIB_H_

#include <Protocol/BlockIo.h>
#include <Protocol/StorageSecurityCommand.h>

typedef struct {
  VOID    *Protocol;
  UINT32  Lun;
} PROTOCOL_LIST_ENTRY;

/**
  Initializes a protocol list.

  @param[out] ProtocolList            A pointer to a list of PROTOCOL_LIST_ENTRY structs.

  @retval     EFI_SUCCESS             At least one ProtocolGuid protocol was found.
  @retval     EFI_INVALID_PARAMETER   Invalid parameter.
  @retval     EFI_OUT_OF_RESOURCES    Couldn't allocate a buffer for the protocol list.
  @retval     EFI_NOT_FOUND           The protocol interface was not found.

**/
EFI_STATUS
EFIAPI
InitProtocolList (
  IN  PROTOCOL_LIST_ENTRY   **ProtocolList,
  IN  EFI_GUID              *ProtocolGuid
  );

/**
  Find an instance of ProtocolGuid for the provided LUN in the provided ProtocolList.

  @param[in]  Lun         The LUN to find.

  @retval     != NULL     A protocol instance matching the provided LUN.
  @retval     NULL        The protocol instance was not found OR invalid argument.

**/
VOID *
EFIAPI
GetProtocolByLun (
  IN  UINT32                  Lun,
  IN  PROTOCOL_LIST_ENTRY     *ProtocolList,
  IN  EFI_GUID                *ProtocolGuid
  );

/**
  Find a BlockIoProtocol instance for the provided LUN.

  @param[in]  Lun         The LUN to find.

  @retval     != NULL     A BlockIoProtocol instance matching the provided LUN.
  @retval     NULL        The protocol instance was not found.

**/
EFI_BLOCK_IO_PROTOCOL *
EFIAPI
GetBlockIoProtocol (
  IN  UINT32                  Lun
  );

/**
  Find a StorageSecurityCommandProtocol instance for the provided LUN.

  @param[in]  Lun         The LUN to find.

  @retval     != NULL     A StorageSecurityCommandProtocol instance matching the provided LUN.
  @retval     NULL        The protocol instance was not found.

**/
EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *
EFIAPI
GetStorageSecurityCommandProtocol (
  IN  UINT32                  Lun
  );

/**
  Check if the Security LUN is supported.

  @retval     TRUE        The Security LUN is supported.
  @retval     FALSE       The Security LUN is not supported.

**/
BOOLEAN
EFIAPI
SecurityLunSupported (
  VOID
  );

/**
  Interacts with StorageSecurityCommandProtocol.

  @param[in]      PayloadBufferSize   The number of bytes to transfer.
  @param[in,out]  PayloadBuffer       A buffer with data to read into or write from.
  @param[in]      Receive             TRUE for Read, FALSE for Write.

  @retval         EFI_SUCCESS             The StorageSecurity transaction was successful.
  @retval         EFI_INVALID_PARAMETER   The PayloadBuffer pointer is NULL.
  @retval         EFI_NOT_FOUND           The RPMB BlockIo or StorageSecurityCommandProtocol is not found.
  @retval         EFI_BAD_BUFFER_SIZE     Transfer Size returned did not match provided Buffer Size.
  @retval         Other                   An error occurred in the BlocStorageSecuritykIo transaction.
**/
EFI_STATUS
EFIAPI
SecurityProtocolTransaction (
  IN      UINTN       PayloadBufferSize,
  IN OUT  VOID        *PayloadBuffer,
  IN      BOOLEAN     Receive
  );

/**
  Interacts with BlockIoProtocol.

  @param[in]      Lun       The LUN on which to run the transaction.
  @param[in]      Offset    The data offset within the BlockIo device.
  @param[in]      Length    The number of bytes to transfer.
  @param[in]      Data      A buffer with data to read into or write from.
  @param[in]      Read      TRUE for Read, FALSE for Write.

  @retval         EFI_SUCCESS             The BlockIo transaction was successful.
  @retval         EFI_INVALID_PARAMETER   The BlockIo or Data pointer is NULL.
  @retval         EFI_NOT_FOUND           The requested LUN BlockIoProtocol is not found.
  @retval         EFI_OUT_OF_RESOURCES    Couldn't allocate a buffer for the transaction.
  @retval         Other                   An error occurred in the BlockIo transaction.
**/
EFI_STATUS
EFIAPI
BlockIoTransaction (
  IN      UINT32      Lun,
  IN      UINT32      Offset,
  IN      UINT32      Length,
  IN OUT  VOID        *Data,
  IN      BOOLEAN     Read
  );

#endif

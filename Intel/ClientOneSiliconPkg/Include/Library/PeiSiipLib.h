/** @file
  Header file for PeiSiipLib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _PEI_MANIFEST_PARSER_LIB_H_
#define _PEI_MANIFEST_PARSER_LIB_H_

#include <SiipCommon.h>

/**
  Send IP specific dashboard Read/Write command

  @param[in]     OperationType    Read/Write command (0: Read operation, 1: Write operation)
  @param[in]     IpName           Which IP interface the command needs to be issued
  @param[in]     RegisterType     Loader/Verifier type (0: Loader, 1: Verifier)
  @param[in]     RegisterOffset   Dashboard register offset to be accessed
  @param[in]     NumberOfBytes    Number of byes to be read or written
  @param[in out] DataBuffer       For read operation it is of output type, for write operation it is of input type

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_INVALID_PARAMETER   Invalid command size
  @retval EFI_DEVICE_ERROR        Command failed with an error
  @retval EFI_TIMEOUT             Command did not complete in given timing requirements
**/
EFI_STATUS
DashboardSendCommand (
  IN     SIIP_OP_TYPE             OperationType,
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_REG_TYPE            RegisterType,
  IN     UINT16                   RegisterOffset,
  IN     SIIP_NUM_BYTES           NumberOfBytes,
  IN OUT VOID                     *DataBuffer
  );

/**
  Get the list of entities who has loader capabilities

  @param[in]     IpName             Which IP interface the command needs to be issued
  @param[out]    LoaderCapBuffer    Data which describes the loader capable entities

  @retval EFI_SUCCESS               Command was executed successfully
  @retval EFI_INVALID_PARAMETER     Invalid command size
  @retval EFI_DEVICE_ERROR          Command failed with an error
  @retval EFI_TIMEOUT               Command did not complete in given timing requirements
**/
EFI_STATUS
GetLoaderCapabilityInfo (
  IN     SIIP_IP_NAME             IpName,
  OUT    UINT32                   *LoaderCapBuffer
  );

/**
  Get the list of entities who has verifier capabilities

  @param[in]     IpName             Which IP interface the command needs to be issued
  @param[out]    VerifierCapBuffer  Data which describes the verifier capable entities

  @retval EFI_SUCCESS               Command was executed successfully
  @retval EFI_INVALID_PARAMETER     Invalid command size
  @retval EFI_DEVICE_ERROR          Command failed with an error
  @retval EFI_TIMEOUT               Command did not complete in given timing requirements
**/
EFI_STATUS
GetVerifierCapabilityInfo (
  IN     SIIP_IP_NAME             IpName,
  OUT    UINT32                   *VerifierCapBuffer
  );

/**
  Set the error code in dashboard for loading failed scenario

  @param[in]     IpName             Which IP interface the command needs to be issued
  @param[in]     ImageNumber        Failed image number
  @param[in]     ErrorCode          Failed reason

  @retval EFI_SUCCESS               Command was executed successfully
  @retval EFI_INVALID_PARAMETER     Invalid command size
  @retval EFI_DEVICE_ERROR          Command failed with an error
  @retval EFI_TIMEOUT               Command did not complete in given timing requirements
**/
EFI_STATUS
SetLoaderErrorInfo (
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_LOADER_INDEX        ImageNumber,
  IN     SIIP_ERROR_CODE          ErrorCode
  );

/**
  Set the error code in dashboard for verifier failed scenario

  @param[in]     IpName             Which IP interface the command needs to be issued
  @param[in]     ImageNumber        Failed image number
  @param[in]     ErrorCode          Failed reason

  @retval EFI_SUCCESS               Command was executed successfully
  @retval EFI_INVALID_PARAMETER     Invalid command size
  @retval EFI_DEVICE_ERROR          Command failed with an error
  @retval EFI_TIMEOUT               Command did not complete in given timing requirements
**/
EFI_STATUS
SetVerifierErrorInfo (
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_VERIFIER_INDEX      ImageNumber,
  IN     SIIP_ERROR_CODE          ErrorCode
  );

/**
  Set the base address/size/loading done for loader

  @param[in]     IpName              Which IP interface the command needs to be issued
  @param[in]     LoaderIndex         Data which describes the loader register index
  @param[in]     LoadedMemoryAddress Physical address of the image for the verifier to verify
  @param[in]     SizeOfImage         Size of the image

  @retval EFI_SUCCESS                Command was executed successfully
  @retval EFI_INVALID_PARAMETER      Invalid command size
  @retval EFI_DEVICE_ERROR           Command failed with an error
  @retval EFI_TIMEOUT                Command did not complete in given timing requirements
**/
EFI_STATUS
SetLoaderAddressSizeIndicatorInfo (
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_LOADER_INDEX        LoaderIndex,
  IN     UINT64                   LoadedMemoryAddress,
  IN     UINT32                   SizeOfImage
  );

/**
  Set the Imr Address and Size Info for PSE

  @param[in]     LoadViaImr          To know if this is loaded via IMR, if IMR, need to program last 3 bits.
  @param[in]     IpName              Which IP interface the command needs to be issued
  @param[in]     VerifierIndex       Data which describes the verifier register index
  @param[in]     LoadedMemoryAddress Physical address of the image after the verifier has integrity verified the image
  @param[in]     SizeOfRegion        Size of the region

  @retval EFI_SUCCESS                Command was executed successfully
  @retval EFI_INVALID_PARAMETER      Invalid command size
  @retval EFI_DEVICE_ERROR           Command failed with an error
  @retval EFI_TIMEOUT                Command did not complete in given timing requirements
**/
EFI_STATUS
SetImrAddressSizeIndicatorInfo (
  IN     BOOLEAN                  LoadViaImr,
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_IP_IMR_INDEX        ImrIndex,
  IN     UINT64                   LoadedMemoryAddress,
  IN     UINT64                   SizeOfRegion
  );

/**
  Set the base address/size/loading done for verifier

  @param[in]     LoadViaImr          To know if this is loaded via IMR, if IMR, need to program last 3 bits.
  @param[in]     IpName              Which IP interface the command needs to be issued
  @param[in]     VerifierIndex       Data which describes the verifier register index
  @param[in]     LoadedMemoryAddress Physical address of the image after the verifier has integrity verified the image
  @param[in]     SizeOfImage         Size of the image

  @retval EFI_SUCCESS                Command was executed successfully
  @retval EFI_INVALID_PARAMETER      Invalid command size
  @retval EFI_DEVICE_ERROR           Command failed with an error
  @retval EFI_TIMEOUT                Command did not complete in given timing requirements
**/
EFI_STATUS
SetVerifierAddressSizeIndicatorInfo (
  IN     BOOLEAN                  LoadViaImr,
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_VERIFIER_INDEX      VerifierIndex,
  IN     UINT64                   LoadedMemoryAddress,
  IN     UINT32                   SizeOfImage
  );

/**
  Get firmware consumed status (Firmware push or pull completed)

  @param[in]     IpName              Which IP interface the command needs to be issued
  @param[in]     VerifierIndex       Data which describes the verifier register index

  @retval EFI_SUCCESS                Success
  @retval EFI_DEVICE_ERROR           Failure
**/
EFI_STATUS
GetVerifierConsumeStatusInfo (
  IN     SIIP_IP_NAME             IpName,
  IN     SIIP_VERIFIER_INDEX      VerifierIndex
  );

/**
  SIIP Firmware Loading implementation

  @param[in]  SiPolicy        Pointer to SI_POLICY_PPI
  @param[in]  SIIP_IP_NAME    The SIIP IP name

  @retval EFI_SUCCESS                Success
  @retval EFI_DEVICE_ERROR           Failure
**/
EFI_STATUS
SiipFwLoading (
  IN  SI_POLICY_PPI     *SiPolicy,
  IN  SIIP_IP_NAME      IpName
  );

#endif

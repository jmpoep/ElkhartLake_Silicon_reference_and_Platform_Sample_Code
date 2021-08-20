/** @file
  PSE Siip library functions.

  This library provides basic PSE interface.

  There may be different libraries for different environments (PEI, BS, RT, SMM).
  Make sure you meet the requirements for the library (protocol dependencies, use
  restrictions, etc).

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#ifndef _PSE_LIB_H_
#define _PSE_LIB_H_

#include <SiipCommon.h>

/**
  Acquire PSE mmio address.

  @retval PchPseBar              return PSE MMIO address
**/
UINTN
AcquirePseBar (
  VOID
  );

/**
  Send IP specific dashboard Read/Write command

  @param[in]     OperationType    Read/Write command (0: Read operation, 1: Write operation)
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
PseSendCommand (
  IN     SIIP_OP_TYPE             OperationType,
  IN     SIIP_REG_TYPE            RegisterType,
  IN     UINT16                   RegisterOffset,
  IN     SIIP_NUM_BYTES           NumberOfBytes,
  IN OUT VOID                     *DataBuffer
  );

#endif

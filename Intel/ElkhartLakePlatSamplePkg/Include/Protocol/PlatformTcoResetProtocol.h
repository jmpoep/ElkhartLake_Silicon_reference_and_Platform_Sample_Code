/** @file
  This header file provides platform specific definitions used
  by other modules for platform specific initialization.
  This is not suitable for consumption by ASL or VRF files.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2019 Intel Corporation.

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

#ifndef _PLATFORM_TCO_RESET_PROTOCOL_H_
#define _PLATFORM_TCO_RESET_PROTOCOL_H_


#define EFI_TCO_RESET_PROTOCOL_GUID  \
  {0xa6a79162, 0xe325, 0x4c30, 0xbc, 0xc3, 0x59, 0x37, 0x30, 0x64, 0xef, 0xb3}

typedef struct _EFI_TCO_RESET_PROTOCOL EFI_TCO_RESET_PROTOCOL;

/*++

Routine Description:

  Enables the TCO timer to reset the system in case of a system hang.  This is
  used when writing the clock registers.

Arguments:

  RcrbGcsSaveValue  - This is the value of Timeout in Seconds.

Returns:

  EFI_STATUS

--*/
typedef
EFI_STATUS
(EFIAPI *EFI_TCO_RESET_PROTOCOL_ENABLE_TCO_RESET) (
  IN      UINT32            *RcrbGcsSaveValue
  );

/*++

Routine Description:

  Disables the TCO timer.  This is used after writing the clock registers.


Returns:

  EFI_STATUS

--*/
typedef
EFI_STATUS
(EFIAPI *EFI_TCO_RESET_PROTOCOL_DISABLE_TCO_RESET) (
  VOID
  );

typedef struct _EFI_TCO_RESET_PROTOCOL {
  EFI_TCO_RESET_PROTOCOL_ENABLE_TCO_RESET       EnableTcoReset;
  EFI_TCO_RESET_PROTOCOL_DISABLE_TCO_RESET      DisableTcoReset;
} EFI_TCO_RESET_PROTOCOL;

extern EFI_GUID gEfiTcoResetProtocolGuid;

#endif

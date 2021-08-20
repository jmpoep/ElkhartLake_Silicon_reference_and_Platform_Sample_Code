/** @file
  TXT One touch definitions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

#ifndef _TXT_ONE_TOUCH_DXE_H_
#define _TXT_ONE_TOUCH_DXE_H_

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Protocol/TcgService.h>
#include <Guid/TxtOneTouch.h>
#include <Protocol/TxtOneTouchOp.h>

#define H2NL(x)             (H2NS ((x) >> 16) | (H2NS ((x) & 0xffff) << 16))
#define H2NS(x)             ((((x) << 8) | ((x) >> 8)) & 0xffff)
#define TPM_PP_USER_ABORT   ((TPM_RESULT) (-0x10))
#define TPM_PP_BIOS_FAILURE ((TPM_RESULT) (-0x0f))

///
/// TPM PPI Commands
///
#define ENABLE              1
#define ACTIVATE            3
#define ENABLE_ACTIVATE     6
#define DISABLE_DEACTIVATE  7

///
/// Definitions
///
#define TXT_ONE_TOUCH_VAR L"TxtOneTouch"
#pragma pack(push, 1)
typedef struct {
  BOOLEAN NoTxtMaintenance;
  BOOLEAN TpmEnable;
  BOOLEAN TpmActive;
  BOOLEAN VtEnable;
  BOOLEAN VtdEnable;
  BOOLEAN TxtEnable;
  BOOLEAN StmEnable;
  BOOLEAN VmxEnable;
  BOOLEAN VmxInSmxEnable;
  BOOLEAN VmxOutsideSmxEnable;
  BOOLEAN SenterEnable;
} TXT_ONE_TOUCH_SETUP;
#pragma pack(pop)

/**
  Extend PPI operation for TxT.

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT

  @retval EFI_SUCCESS     - Execute the Command successful
  @retval EFI_UNSUPPORTED - Command is not supported
**/
EFI_STATUS
EFIAPI
TxtExecOperation (
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command
  );

/**
  Confirmation dialog for TxT PPI

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT
  @param[in] Confirm - User confirm

  @retval EFI_SUCCESS     - Execute the Command successful
  @retval EFI_UNSUPPORTED - Command is not supported
**/
EFI_STATUS
EFIAPI
TxtConfirmationDialog (
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command,
  IN OUT BOOLEAN               *Confirm
  );

/**
  Reset system.

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT

  @retval EFI_SUCCESS - Always return EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
TxtResetState (
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command
  );

/**
  Enable/Active TPM

  @param[in] Command  - The operation code for TxT One Touch function

  @retval EFI_SUCCESS        - TPM command lunch success
  @retval EFI_UNSUPPORTED    - The Command is not supported
  @retval EFI_DEVICE_ERROR   - Faile to lunch TPM command
**/
EFI_STATUS
TpmEnableActive (
  IN UINT8 Command
  );

/**
  Read/Write variable for enable/disable TxT one
  touch functions

  @param[in] VariableData - Point to Setup variable buffer
  @param[in] WriteData    - TRUE, write changes to Setup Variable. FALSE, not to write variable.

  @retval EFI_SUCCESS           - Operation complete successful
  @retval EFI_INVALID_PARAMETER - VariableData is NULL
**/
EFI_STATUS
ReadWriteVariable (
  IN OUT TXT_ONE_TOUCH_SETUP *VariableData,
  IN BOOLEAN                 WriteData
  );

/**
  Verify the status of Chipset capability and Setup settings

  @param[in] Data  - Point to TXT_ONE_TOUCH_SETUP

  @exception EFI_UNSUPPORTED - The system is not able to launch TxT
  @retval EFI_SUCCESS - The system is able to launch TxT
**/
EFI_STATUS
ValidateTxtStates (
  IN TXT_ONE_TOUCH_SETUP *Data
  );

#endif

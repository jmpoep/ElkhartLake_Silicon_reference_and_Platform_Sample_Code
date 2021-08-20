/** @file
  Txt specific PPI operation definition.

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

#ifndef _TXT_PPI_OPERATION_H_
#define _TXT_PPI_OPERATION_H_

typedef struct _TXT_ONE_TOUCH_OP_PROTOCOL TXT_ONE_TOUCH_OP_PROTOCOL;

//
// Member functions
//
/*
  Extend PPI operation for TxT.

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT

*/
typedef
EFI_STATUS
(EFIAPI *TXT_PPI_EXEC_OPERATION)(
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command
  );

/*
  Confirmation dialog for TxT PPI

  @param[in] This    - Point of TXT_ONE_TOUCH_OP_PROTOCOL
  @param[in] Command - Operation value for TxT
  @param[in] Confirm - User confirm
*/
typedef
EFI_STATUS
(EFIAPI *TXT_CONFIRMATION_DIALOG)(
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
typedef
EFI_STATUS
(EFIAPI *TXT_RESET_SYSTEM)(
  IN TXT_ONE_TOUCH_OP_PROTOCOL *This,
  IN UINT8                     Command
  );

struct _TXT_ONE_TOUCH_OP_PROTOCOL {
  TXT_PPI_EXEC_OPERATION  ExecuteOperation;
  TXT_CONFIRMATION_DIALOG ConfirmationDialog;
  TXT_RESET_SYSTEM        ResetSystem;
};

#endif

/** @file
  Header file for communication functionalities by MEI (HECI)

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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

#ifndef __MEI_H__
#define __MEI_H__


typedef struct _MEI_INFO {
  //
  // FW info
  //
  UINT16      Major;
  UINT16      Minor;
  UINT16      Hotfix;
  UINT16      Build;

  //
  // ME FW type
  //
  UINT16      MeFwType;
  //
} ME_INFO;

typedef enum _ME_CLIENT_ID {
  IVM_CLIENT,       // Intel Virtual Machine, same as JOMHI(ME10)
  SDM_CLIENT,       // Security Domain Manager
  RTM_CLIENT,       // Run Time Manager (Launcher)
  SVM_CLIENT,       // SVM
  NO_CLIENT,
} ME_CLIENT_ID;

/**
  Initialize ME interface

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
MeiInit (VOID);

/**
  De-initialize ME interface

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
MeiDeinit (VOID);

/**
  Connect to the enumerated client that supports FW Update
  A valid client ID is required for this routine

  @param[in] MeClient             The pointer to the ME property.

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
MeiClientConnect (
  IN ME_CLIENT_ID MeClientId
);

/**
  Disconnect from the connected client

  @param[in] MeClient             The pointer to the ME property.

  @retval JHI_SUCCESS             Get flow control message successfully.
  @retval others                  Get flow control message failed with error code.
**/
EFI_STATUS
MeiClientDisconnect (
  IN ME_CLIENT_ID MeClientId
);

/**
  Send data by ME interface

  @param[in] MeClient             The ME client identifier.
  @param[in] Buffer               The pointer to the buffer for transition.
  @param[in] Length               The length of buffer.

  @retval EFI_SUCCESS             Receive data successfully.
  @retval others                  Receive data failed with error code.
**/
EFI_STATUS
MeiSend (
  IN ME_CLIENT_ID MeClientId,
  IN VOID         *Buffer,
  IN UINT32       Length
);

/**
  Receive data by ME interface

  @param[in] MeClient             The ME client identifier.
  @param[out] Buffer              The pointer to the buffer for transition.
  @param[in] Length               The length of buffer.

  @retval EFI_SUCCESS             Receive data successfully.
  @retval others                  Receive data failed with error code.
**/
EFI_STATUS
MeiRecv (
  IN ME_CLIENT_ID MeClientId,
  OUT VOID        *Buffer,
  IN UINT32       *Length
);

/**
  Get information of ME interface

  @param[in] MeInfo               The pointer to the information buffer.

  @retval EFI_SUCCESS             Get information successfully.
  @retval others                  Get information failed with error code.
**/
EFI_STATUS
MeiGetInfo (
  OUT ME_INFO *MeInfo
);

#endif  // __MEI_H__


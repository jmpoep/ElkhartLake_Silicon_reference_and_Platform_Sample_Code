/** @file
  Header file for JHI plugin functionality.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

#ifndef __JHI_PLUGIN_H__
#define __JHI_PLUGIN_H__

#include <Protocol/JhiProtocol.h>
#include "JhiInternal.h"

/**
  Initialize Beihai library.

  @param[in] info                 The pointer to the buffer of BHP_INFO.

  @retval JHI_SUCCESS             Initialize Beihai library successfully.
  @retval others                  Initialize Beihai library failed with error code.
**/
UINT32
JHI_Plugin_Init (
  OUT BHP_INFO *info
);

/**
  De-initialize Beihai library.

  @retval JHI_SUCCESS             De-initialize Beihai library successfully.
  @retval others                  De-initialize Beihai library failed with error code.
**/
UINT32
JHI_Plugin_DeInit (VOID);

/**
  Download an applet to Beihai library.

  @param[in] pAppId               The AppId.
  @param[in] pAppBlob             The pointer to the buffer of applet.
  @param[in] AppSize              The size of applet.

  @retval JHI_SUCCESS             Download an applet successfully.
  @retval others                  Download an applet failed with error code.
**/
UINT32
JHI_Plugin_DownloadApplet (
  IN CONST CHAR8  *pAppId,
  IN UINT8        *pAppBlob,
  IN unsigned int AppSize
);

/**
  Unload an applet from Beihai library.

  @param[in] pAppId               The AppId.

  @retval JHI_SUCCESS             Unload an applet successfully.
  @retval others                  Unload an applet failed with error code.
**/
UINT32
JHI_Plugin_UnloadApplet (
  IN CONST CHAR8 *AppId
);

/**
  Create a session for an applet to Beihai library.

  @param[in] pAppId               The AppId.
  @param[out] pSession            The session handle.
  @param[in] pAppBlob             The pointer to the content of applet.
  @param[in] BlobSize             The size of the applet.
  @param[in] SessionID            The session ID for the sessin.
  @param[in] InitBuffer           The pointer to the buffer for session initialization.

  @retval JHI_SUCCESS             Create a session successfully.
  @retval others                  Create a session failed with error code.
**/
UINT32
JHI_Plugin_CreateSession (
  IN CONST CHAR8        *AppId,
  OUT VM_SESSION_HANDLE *pSession,
  IN CONST UINT8        *pAppBlob,
  IN unsigned int       BlobSize,
  IN JHI_SESSION_ID     SessionID,
  IN DATA_BUFFER        *InitBuffer
);

/**
  Close a session for an applet to Beihai library.

  @param[in] pSession             The session handle.

  @retval JHI_SUCCESS             Close a session successfully.
  @retval others                  Close a session failed with error code.
**/
UINT32
JHI_Plugin_CloseSession (
  IN VM_SESSION_HANDLE* pSession
);

/**
  Command, data transition to an applet by session.

  @param[in] Session              The session handle.
  @param[in] nCommandId           The command ID.
  @param[in] pIOBuffer            The pointer to the buffer for this command.
  @param[out] pResponseCode       The pointer to the buffer of response code.

  @retval JHI_SUCCESS             Transition successfully.
  @retval others                  Transition failed with error code.
**/
UINT32
JHI_Plugin_SendAndRecv (
  IN VM_SESSION_HANDLE  Session,
  IN INT32              nCommandId,
  IN JVM_COMM_BUFFER    *pIOBuffer,
  OUT INT32             *pResponseCode
);

/**
  Get property of an applet.

  @param[in] pAppId               The AppId.
  @param[in, out] pIOBuffer       The pointer to the buffer of property and return value.

  @retval JHI_SUCCESS             Get property successfully.
  @retval others                  Get property failed with error code.
**/
UINT32
JHI_Plugin_GetAppletProperty (
  IN CONST CHAR8          *AppId,
  IN OUT JVM_COMM_BUFFER  *pIOBuffer
);

#endif // __JHI_PLUGIN_H__


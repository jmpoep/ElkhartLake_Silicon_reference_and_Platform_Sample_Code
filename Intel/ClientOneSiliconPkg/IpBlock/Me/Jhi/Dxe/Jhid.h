/** @file
  Header for Frontend library of JHI DXE driver.

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

#ifndef __JHID_H__
#define __JHID_H__

#include <Protocol/JhiProtocol.h>
#include <JhiInternal.h>

/**
  Initialize JHI API core.

  @param[out] ppHandle            The pointer to JHI handle.
  @param[in]  Context             The pointer to extra information.
  @param[in]  Flags               The flags for initialization

  @retval JHI_SUCCESS             Initialize JHI API core successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidInitialize (
  OUT JHI_HANDLE  *ppHandle,
  IN VOID         *Context,
  IN UINT32       Flags
);

/**
  De-initialize JHI API core.

  @param[in]  Handle              The JHI handle.

  @retval JHI_SUCCESS             De-initialize JHI API core successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidDeinit (
  IN JHI_HANDLE   Handle
);

/**
  Install an applet to JHI API core.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The AppId to the applet.
  @param[in]  SrcFile             The file path of this applet.

  @retval JHI_SUCCESS             Install an applet to JHI API core successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidInstall2 (
  IN CONST JHI_HANDLE Handle,
  IN CONST APPID_STR  AppId,
  IN CONST CHAR16     *SrcFile
);

/**
  Install an applet to JHI API core.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The AppId to the applet.
  @param[in]  AppletBlob          The raw data of this applet.
  @param[in]  AppletLength        The data length of this applet.

  @retval JHI_SUCCESS             Install an applet to JHI API core successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidInstall3 (
  IN CONST JHI_HANDLE Handle,
  IN CONST APPID_STR  AppId,
  IN CONST VOID*      AppletBlob,
  IN CONST UINT32     AppletLength
);

/**
  Uninstall an applet from JHI API core.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The AppId to the applet.

  @retval JHI_SUCCESS             Uninstall an applet to JHI API core successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidUninstall (
  IN JHI_HANDLE       Handle,
  IN APPID_STR        AppId
);

/**
  Get applet property from JHI API core.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The AppId to the applet.
  @param[in]  pCommBuffer         The pointer to the buffer for information transition.

  @retval JHI_SUCCESS             Get applet property from JHI API core successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidGetAppletProperty (
  IN     JHI_HANDLE        Handle,
  IN     APPID_STR         AppId,
  IN OUT JVM_COMM_BUFFER   *pCommBuffer
);

/**
  Create a session for an applet.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The AppId to the applet.
  @param[in]  Flags               The flag to create session.
  @param[in]  InitBuffer          The pointer to the buffer for creating session.

  @retval JHI_SUCCESS             Create session successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidCreateSession (
  IN CONST JHI_HANDLE     Handle,
  IN CONST APPID_STR      AppId,
  IN UINT32               Flags,
  IN DATA_BUFFER          *InitBuffer,
  OUT JHI_SESSION_HANDLE  *pSessionHandle
);

/**
  Close a session for an applet.

  @param[in]  Handle              The JHI handle.
  @param[in]  pSessionHandle      The session handle to be closed.

  @retval JHI_SUCCESS             Close session successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidCloseSession (
  IN CONST JHI_HANDLE   Handle,
  IN JHI_SESSION_HANDLE *pSessionHandle
);

/**
  Get session count for an applet.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The AppId to the applet.
  @param[in]  pSessionsCount      The pointer to the buffer of session count.

  @retval JHI_SUCCESS             Get session count successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidGetSessionsCount (
  IN CONST JHI_HANDLE Handle,
  IN CONST APPID_STR  AppId,
  OUT UINT32          *pSessionsCount
);

/**
  Get session information for a session.

  @param[in]  Handle              The JHI handle.
  @param[in]  pSessionHandle      The session handle to be queried.
  @param[in]  pSessionsCount      The pointer to the buffer of session information.

  @retval JHI_SUCCESS             Get session information successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidGetSessionInfo (
  IN CONST JHI_HANDLE   Handle,
  IN JHI_SESSION_HANDLE SessionHandle,
  OUT JHI_SESSION_INFO  *SessionInfo
);

/**
  Get version information of JHI API core.

  @param[in]  Handle              The JHI handle.
  @param[in]  pVersionInfo        The pointer to the buffer of version information.

  @retval JHI_SUCCESS             Get version information successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidGetVersionInfo (
  IN CONST JHI_HANDLE   Handle,
  OUT JHI_VERSION_INFO  *pVersionInfo
);

/**
  Send/Receive data to/from JHI API core.

  @param[in]  Handle              The JHI handle.
  @param[in]  SessionHandle       The session handle.
  @param[in]  nCommandId          The command ID.
  @param[in]  pCommBuffer         The pointer to the buffer of communication.
  @param[in]  ResponseCode        The pointer to the buffer of response code.

  @retval JHI_SUCCESS             Data transfer successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidSendAndRecv (
  IN JHI_HANDLE           Handle,
  IN JHI_SESSION_HANDLE   SessionHandle,
  IN INT32                nCommandId,
  IN OUT JVM_COMM_BUFFER  *pCommBuffer,
  OUT INT32               *ResponseCode
);

#endif // __JHID_H__

/** @file
  Header for JHI service, this is the backend service of JHI DXE driver.

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

#ifndef __JHIS_H__
#define __JHIS_H__

#include <Protocol/JhiProtocol.h>
#include <JhiInternal.h>
#include <Protocol/SimpleFileSystem.h>  // EFI_FILE
#include <Guid/FileInfo.h>


typedef enum {
  INITALIZED,
  RUNNING,
  STOPING
} JHI_STATE;

///
/// JHI internal handle, this is the instance of JHI_HANDLE.
///
#define JHI_HANDLE_INSTANCE_SIGNATURE   SIGNATURE_32 ('j', 'i', 'h', '-')
typedef struct _JHI_I_HANDLE {
  UINT32                Signature;
  LIST_ENTRY            AppletHandleListHead; ///< The list header for all installed applets
  JHI_STATE             State;
  UINT32                ReferenceCount;
  JHI_VERSION_INFO      VersionInfo;
} JHI_I_HANDLE;

///
/// Applet information
///
#define JHI_APPLET_HANDLE_INSTANCE_SIGNATURE   SIGNATURE_32 ('j', 'i', 'a', 'h')
typedef struct _JHI_I_APPLET_HANDLE {
  UINT32                Signature;
  LIST_ENTRY            Link;
  LIST_ENTRY            SessionListHead;    ///< The list header for all opened sessions
  JHI_I_HANDLE          *JhiHandleInstance; ///< link back to JHI handle instance
  APPID_STR             UcAppId;            ///< Upper case AppId string
  CHAR16                *AppletFilepath;
  EFI_FILE              *FileHandle;
  UINT8                 *FileBlob;
  UINTN                 FileSize;
} JHI_I_APPLET_HANDLE;

///
/// Session information
///
#define JHI_SESSION_HANDLE_INSTANCE_SIGNATURE   SIGNATURE_32 ('j', 'i', 's', 'h')
typedef struct _JHI_I_SESSION_HANDLE {
  UINT32                Signature;
  LIST_ENTRY            Link;
  JHI_I_APPLET_HANDLE   *JhiAppletHandle;     ///< The applet handle that this session belongs to.
  UINTN                 GuidListIndex;
  JHI_SESSION_ID        SessionID;
  JHI_SESSION_INFO      SessionInfo;
  DATA_BUFFER           *InitBuffer;
  VM_SESSION_HANDLE     VMSessionHandle;
} JHI_I_SESSION_HANDLE;

/**
Relation of above structures:
  JHI_I_HANDLE owns JHI_I_APPLET_HANDLE
  JHI_I_APPLET_HANDLE owns JHI_I_SESSION_HANDLE
  JHI_I_HANDLE (- JHI_I_APPLET_HANDLE (- JHI_I_SESSION_HANDLE
**/


/**
  Initialize JHI service library

  @param[in]  JhiHandle           The JHI internal handle.

  @retval JHI_SUCCESS             Initialize JHI service successfully.
  @retval others                  Error code of JHI_Plugin_Init.
**/
JHI_RET
JhisInit (
  IN JHI_I_HANDLE *JhiHandle
);

/**
  De-initialize JHI service library.

  @param[in]  JhiHandle           The JHI internal handle.

  @retval JHI_SUCCESS             De-initialize JHI service successfully.
  @retval others                  Error code of JHI_Plugin_DeInit.
**/
JHI_RET
JhisDeInit (
  IN JHI_I_HANDLE *JhiHandle
);

/**
  Install an applet to JHI service library.

  @param[in]  JhiAppletHandle     The applet handle to be installed.

  @retval JHI_SUCCESS             Install applet successfully.
  @retval JHI_INVALID_INSTALL_FILE  Open applet file failed.
  @retval JHI_READ_FROM_FILE_FAILED Read applet file failed.
  @retval others                  Error code of JHI_Plugin_DownloadApplet.
**/
JHI_RET
JhisInstall (
  IN JHI_I_APPLET_HANDLE *JhiAppletHandle
);

/**
  Uninstall an applet from JHI service library.

  @param[in]  JhiAppletHandle     The applet handle to be uninstalled.

  @retval JHI_SUCCESS             Uninstall applet successfully.
  @retval others                  Error code of JHI_Plugin_UnloadApplet.
**/
JHI_RET
JhisUninstall (
  IN JHI_I_APPLET_HANDLE *JhiAppletHandle
);

/**
  Create a session to JHI service library.

  @param[in]  JhiSessionHandle    The session handle to be created.

  @retval JHI_SUCCESS             Create session successfully.
  @retval others                  Error code of JHI_Plugin_CreateSession.
**/
JHI_RET
JhisCreateSession (
  IN JHI_I_SESSION_HANDLE* JhiSessionHandle
);

/**
  Close a session to JHI service library.

  @param[in]  JhiSessionHandle    The session handle to be closed.

  @retval JHI_SUCCESS             Close session successfully.
  @retval others                  Error code of JHI_Plugin_CloseSession.
**/
JHI_RET
JhisCloseSession(
  IN JHI_I_SESSION_HANDLE* JhiSessionHandle
);

/**
  Send/receive data to/from JHI service library.

  @param[in]  JhiSessionHandle    The session handle to be transferred.
  @param[in]  nCommandId          The command identity to DAL VM.
  @param[in, out]  pCommBuffer    The pointer to the buffer of transition.
  @param[out] pResponseCode       The returned status code.

  @retval JHI_SUCCESS             Data transition successfully.
  @retval others                  Error code of JHI_Plugin_SendAndRecv.
**/
JHI_RET
JhisSendAndRecv (
  IN JHI_I_SESSION_HANDLE *JhiSessionHandle,
  IN INT32                nCommandId,
  IN OUT JVM_COMM_BUFFER  *pCommBuffer,
  OUT INT32               *pResponseCode
);

/**
  Get property from installed applet.

  @param[in]  JhiAppletHandle     The applet handle to be queried.
  @param[in, out]  pCommBuffer    The pointer to the buffer of property information.
  @param[in]  SessionCount        The session count of this applet.

  @retval JHI_SUCCESS             Get property successfully.
  @retval others                  Error code of JHI_Plugin_GetAppletProperty.
**/
JHI_RET
JhisGetAppletProperty (
  IN JHI_I_APPLET_HANDLE  *JhiAppletHandle,
  IN OUT JVM_COMM_BUFFER  *pCommBuffer,
  IN UINTN                SessionCount
);

#endif // __JHIS_H__


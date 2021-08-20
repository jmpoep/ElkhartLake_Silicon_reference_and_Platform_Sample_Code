/** @file
  Entry of JHI (Intel DAL Host Interface Service) DXE driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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

#include <Base.h>
#include <Uefi.h>

#include <PiDxe.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>

#include <Protocol/MePolicy.h>
#include <Protocol/JhiProtocol.h>
#include <Library/ConfigBlockLib.h>
#include "Jhid.h"


/**
  Initializes the DAL client programming library by allocating resources, establishing
  a session with the ME Firmware through the JHI Service installed in the PC client.
  Typically, this is the first function called by the clients of the JHI interface.
  Context must be NULL and flags set to 0.

  @param[out] Handle              The pointer to JHI handle.
                                  Handle returned by the interface for use by the application
                                  in future references to maintain application related info.
  @param[in]  Context             The pointer to application related context information that
                                  can be returned by interface if necessary.
  @param[in]  Flags               Input parameter used to indicate future conditions.
  @retval JHI_SUCCESS             Initialize JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
Initialize (
  OUT EFI_HANDLE                  *Handle,
  IN  VOID                        *Context,
  IN  UINT32                      Flags
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_Initialize >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_INITIALIZE,
    rc = JhidInitialize ((JHI_HANDLE *) Handle, Context, Flags);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_Initialize done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  Uninitializes the DAL client programming library by de-allocating resources and
  closes the connection with host JHI service. Typically, this is the last function
  called by the clients of the JHI interface and is used for cleanup at the end of
  a session.

  @param[in]  Handle              The JHI handle.

  @retval JHI_SUCCESS             Uninitialize JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
Uninit (
  IN  EFI_HANDLE                  Handle
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_Deinit >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_DEINIT,
    rc = JhidDeinit ((JHI_HANDLE) Handle);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_Deinit done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  Install an applet file to JHI core. This is a preboot version of JHI_Install2 API.
  This function gets the AppID and the path where the application package is stored
  which are then sent to JOM through JHI service. On successful installation, the
  application along with the manifest is then installed onto the ME through the JHI service.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')
  @param[in]  SrcFile             The file path of the applet.

  @retval JHI_SUCCESS             Install an applet to JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
InstallFile (
  IN  EFI_HANDLE                  Handle,
  IN  CHAR8                       *AppId,
  IN  CONST CHAR16                *SrcFile
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_Install2 (InstallFile) >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_INSTALL2,
    rc = JhidInstall2 ((JHI_HANDLE) Handle, AppId, SrcFile);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_Install2 done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  Install an applet from content to JHI core. This is a preboot version of JHI_Install3 API.
  This API is similar with JHI_PROTOCOL.InstallFile. This function gets the AppID
  and the contents (AppletBlob and AppletLength) of the application package then
  sent to JOM through JHI service.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')
  @param[in]  AppletBlob          The raw data of the applet.
  @param[in]  AppletLength        The data length of the applet.

  @retval JHI_SUCCESS             Install an applet to JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
InstallContent (
  IN  EFI_HANDLE                  Handle,
  IN  CHAR8                       *AppId,
  IN  CONST VOID                  *AppletBlob,
  IN  CONST UINT32                AppletLength
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_Install3 (InstallContent) >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_INSTALL3,
    rc = JhidInstall3 ((JHI_HANDLE) Handle, AppId, AppletBlob, AppletLength);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_Install3 done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  Uninstall an applet from JHI core. This is the interface used to uninstall an
  existing application from the JOM.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')

  @retval JHI_SUCCESS             Uninstall an applet to JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
Uninstall (
  IN  EFI_HANDLE                  Handle,
  IN  CHAR8                       *AppId
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_Uninstall >>>\n"));


  PREF_PROBE_BLOCK (JHI_PERFID_UNINSTALL,
    rc = JhidUninstall ((JHI_HANDLE) Handle, AppId);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_Uninstall done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  Get applet property from JHI core. This interface used to query one of the
  following properties of an installed applet:
  " applet.name
  " applet.vendor
  " applet.description
  " applet.version
  " security.version
  " applet.flash.quota
  " applet.debug.enable
  " applet.shared.session.support
  " applet.platform

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')
  @param[in]  CommBuffer          The pointer to the buffer for information transfer.

  @retval JHI_SUCCESS             Get applet property from JHI core successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
GetAppletProperty (
  IN     EFI_HANDLE               Handle,
  IN     CHAR8                    *AppId,
  IN OUT JVM_COMM_BUFFER          *CommBuffer
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_GetAppletProperty >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_GET_APPLET_PROPERTY,
    rc = JhidGetAppletProperty ((JHI_HANDLE) Handle, AppId, CommBuffer);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_GetAppletProperty done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  Create a session for an applet. This API function creates a session to a given
  applet (represented by appid) and return a session handle to which used to refer
  to the applet instance that would like to communicate with.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')
  @param[in]  Flags               The flag to create session.
  //
  // Here lists the flags that used when creating a session
  //
  #define JHI_NO_FLAGS            0 // no flags to be used
  #define JHI_SHARED_SESSION      1 // create a shared session, or receive a handle for an existing shared session
  // Note: for preboot JHI, we won't support multi-thread mechanism. So, there is no shared session, either.
  // In the other words, JHI_NO_FLAGS(0) is the only value that we support for Flags field.

  @param[in]  InitBuffer          The pointer to the buffer for creating session.
                                  Some initialization data that will be passed to
                                  the applet (the applet onInit() function). It can
                                  be set to NULL if no init data is needed by the applet.
  @param[in]  SessionHandle       The pointer to the session handle to be created
                                  and returned.

  @retval JHI_SUCCESS             Create session successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
CreateSession (
  IN  CONST EFI_HANDLE            Handle,
  IN  CONST CHAR8                 *AppId,
  IN  UINT32                      Flags,
  IN  DATA_BUFFER                 *InitBuffer,
  OUT EFI_HANDLE                  *SessionHandle
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_CreateSession >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_CREATE_SESSION,
    rc = JhidCreateSession ((JHI_HANDLE) Handle, AppId, Flags, InitBuffer, SessionHandle);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_CreateSession done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  Close a session for an applet. This API function close the session. After the
  function return, SessionHandle value will be not valid to use.

  @param[in]  Handle              The JHI handle.
  @param[in]  SessionHandle       The pointer to the session handle to be closed.

  @retval JHI_SUCCESS             Close session successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
CloseSession (
  IN  EFI_HANDLE                  Handle,
  IN  EFI_HANDLE                  *SessionHandle
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_CloseSession >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_CLOSE_SESSION,
    rc = JhidCloseSession ((JHI_HANDLE) Handle, SessionHandle);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_CloseSession done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  This function gets number of active sessions of an installed applet.

  @param[in]  Handle              The JHI handle.
  @param[in]  AppId               The applet UUID string without separator characters ('-')
  @param[in]  SessionsCount       The pointer to the buffer of session count.

  @retval JHI_SUCCESS             Get session count successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
GetSessionsCount (
  IN  EFI_HANDLE                  Handle,
  IN  CHAR8                       *AppId,
  OUT UINT32                      *SessionsCount
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_GetSessionsCount >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_GET_SESSION_COUNT,
    rc = JhidGetSessionsCount ((JHI_HANDLE) Handle, AppId, SessionsCount);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_GetSessionsCount done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  Get session information for a session. This API function returns information of
  a given session. Currently only the session state is available, but this API
  an be extended later to return more info.

  @param[in]  Handle              The JHI handle.
  @param[in]  SessionHandle       The session handle to be queried.
  @param[in]  SessionInfo         The pointer to the buffer of session information.

  @retval JHI_SUCCESS             Get session information successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
GetSessionInfo (
  IN  EFI_HANDLE                  Handle,
  IN  EFI_HANDLE                  SessionHandle,
  OUT JHI_SESSION_INFO            *SessionInfo
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_GetSessionInfo >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_GET_SESSION_INFO,
    rc = JhidGetSessionInfo ((JHI_HANDLE) Handle, SessionHandle, SessionInfo);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_GetSessionInfo done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  Get version information of JHI core. This function is used in order to get the
  versions of the FW, JHI and other general information such as Communication mode.

  @param[in]  Handle              The JHI handle.
  @param[in]  VersionInfo         The pointer to the buffer of version information.

  @retval JHI_SUCCESS             Get version information successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
GetVersionInfo (
  IN  CONST EFI_HANDLE            Handle,
  OUT JHI_VERSION_INFO            *VersionInfo
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_GetVersionInfo >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_GET_VERSION_INFO,
    rc = JhidGetVersionInfo ((JHI_HANDLE) Handle, VersionInfo);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_GetVersionInfo done, rc: %x>>>\n\n", rc));
  return rc;
}

/**
  Send/Receive data to/from JHI core. This is a preboot version of JHI_SendAndRecv2 API.
  The interface allows for sending and receiving raw data and in addition a UINT32
  response code. This is an atomic operation from the perspective of the calling application.

  @param[in]  Handle              The JHI handle.
  @param[in]  SessionHandle       The session handle.
  @param[in]  CommandId           The command id that is sent to the applet.
  @param[in]  CommBuffer          I/O communication buffer for sending/receiving raw data.
                                  In case the function returns JHI_INSUFFICIENT_BUFFER
                                  the RxBuf->length will hold the buffer size required
                                  by the applet for the response.

  @param[in]  ResponseCode        The pointer to the buffer of response code.
                                  The response code returned from the applet to
                                  the application by using the SetResponseCode()
                                  method. It can be NULL.

  @retval JHI_SUCCESS             Data transfer successfully.
  @retval others                  Error code that return from JHI core.
**/
JHI_RET
EFIAPI
SendAndRecv2 (
  IN     EFI_HANDLE               Handle,
  IN     EFI_HANDLE               SessionHandle,
  IN     INT32                    CommandId,
  IN OUT JVM_COMM_BUFFER          *CommBuffer,
  OUT    INT32                    *ResponseCode
  )
{
  JHI_RET rc;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_SendAndRecv2 >>>\n"));

  PREF_PROBE_BLOCK (JHI_PERFID_SENDRECV,
    rc = JhidSendAndRecv ((JHI_HANDLE) Handle, SessionHandle, CommandId, CommBuffer, ResponseCode);
    );

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "<<< JHI_SendAndRecv2 done, rc: %x>>>\n\n", rc));
  return rc;
}


///
/// Instance of JHI protocol
///
STATIC
ME_JHI_PROTOCOL
mJhiProtocolInstance = {
  JHI_PROTOCOL_REVISION,
  Initialize,
  Uninit,
  InstallFile,
  InstallContent,
  Uninstall,
  GetAppletProperty,
  CreateSession,
  GetSessionsCount,
  CloseSession,
  GetSessionInfo,
  GetVersionInfo,
  SendAndRecv2,
};

STATIC
BOOLEAN
GetJhiSupportStatus (VOID)
{
#if EN_JHI_CHECK_POLICY
  EFI_STATUS          Status;
  ME_POLICY_PROTOCOL  *DxeMePolicy;
  BOOLEAN             JhiSupport;
  ME_DXE_CONFIG       *MeDxeConfig;

  JhiSupport = FALSE;
  DxeMePolicy = NULL;

  ///
  /// Get JHI control status from ME policy
  ///
  Status = gBS->LocateProtocol (&gDxeMePolicyGuid, NULL, (VOID **) &DxeMePolicy);
  if (EFI_ERROR (Status) || DxeMePolicy == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "No ME Policy Protocol available"));
  } else {
    ASSERT (DxeMePolicy != NULL);

    Status = GetConfigBlock ((VOID *) DxeMePolicy, &gMeDxeConfigGuid, (VOID *) &MeDxeConfig);
    ASSERT_EFI_ERROR (Status);

    JhiSupport = (BOOLEAN) (MeDxeConfig->MeJhiSupport != 0);
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "GetJhiSupportStatus, JhiSupport: %x\n", JhiSupport));
  return JhiSupport;
#else
  DEBUG_JHI_DRIVER ((DEBUG_INFO, "GetJhiSupportStatus() always return TRUE.\n"));
  return TRUE;
#endif
}

//
// Entry point
//
EFI_STATUS
EFIAPI
JhiDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS  Status;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhiDxeEntryPoint\n"));

  Status = EFI_UNSUPPORTED;
  if (GetJhiSupportStatus () == TRUE) {
    ///
    /// JHI control status is enabled, install JHI protocol
    ///
    Status = gBS->InstallMultipleProtocolInterfaces (
                    &ImageHandle,
                    &gJhiProtocolGuid,
                    &mJhiProtocolInstance,
                    NULL
                    );
    ASSERT_EFI_ERROR (Status);
  } else {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhiDxeEntryPoint fail, JHI control status is not enabled\n"));
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhiDxeEntryPoint done, Status: %r\n", Status));
  return Status;
}


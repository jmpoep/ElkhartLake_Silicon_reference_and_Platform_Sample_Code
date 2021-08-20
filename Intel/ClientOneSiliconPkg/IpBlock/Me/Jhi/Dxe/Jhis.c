/** @file
  JHI service, this is the backend service of JHI DXE driver.
  This service link to JhiPlugin to use Beihai service.

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

#include <Base.h>
#include <Uefi.h>

#include <PiDxe.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Protocol/JhiProtocol.h>
#include <Library/DxeBeihaiLib/bhp_exp.h>
#include <Library/DxeBeihaiLib/JhiPlugin.h>
#include "Jhis.h"

/**
  Compare the applet property request against supported property values.

  @param[in]  AppProperty         The pointer to the string of property (NULL-terminated)
  @param[in]  AppPropertyLength   The length of this string (not include '\0', so the length = AsciiStrLen (AppProperty))

  @retval TRUE                    The property is valid.
  @retval FALSE                   The property is invalid.
**/
STATIC
BOOLEAN
IsPropertySupported (
  IN CHAR8* AppProperty,
  IN UINTN AppPropertyLength
  )
{
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "IsPropertySupported, AppProperty: %a, AppPropertyLength: %x\n",
                             AppProperty, AppPropertyLength));

  if (AppProperty == NULL || AppPropertyLength < 1) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "IsPropertySupported fail, input parameters invalid\n"));
    return FALSE;
  }

  if (AppProperty[AppPropertyLength] != 0) {
    return FALSE;
  }

  if (AsciiStrCmp (AppProperty, "applet.name") == 0) {
    return TRUE;
  }
  if (AsciiStrCmp (AppProperty, "applet.vendor") == 0) {
    return TRUE;
  }
  if (AsciiStrCmp (AppProperty, "applet.description") == 0) {
    return TRUE;
  }
  if (AsciiStrCmp (AppProperty, "applet.version") == 0) {
    return TRUE;
  }
  if (AsciiStrCmp (AppProperty, "security.version") == 0) {
    return TRUE;
  }
  if (AsciiStrCmp (AppProperty, "applet.flash.quota") == 0) {
    return TRUE;
  }
  if (AsciiStrCmp (AppProperty, "applet.debug.enable") == 0) {
    return TRUE;
  }
  if (AsciiStrCmp (AppProperty, "applet.shared.session.support") == 0) {
    return TRUE;
  }
  if (AsciiStrCmp (AppProperty, "applet.platform") == 0) {
    return TRUE;
  }

  return FALSE;
}


/**
  Initialize JHI service library

  @param[in]  JhiHandle           The JHI internal handle.

  @retval JHI_SUCCESS             Initialize JHI service successfully.
  @retval others                  Error code of JHI_Plugin_Init.
**/
JHI_RET
JhisInit (
  IN JHI_I_HANDLE *JhiHandle
  )
{
  JHI_RET  rc;
  BHP_INFO Info;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisInit\n"));
  ASSERT (JhiHandle != NULL);

  rc = JHI_Plugin_Init (&Info);
  if (rc != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhisInit fail, JHI_Plugin_Init error: %r.\n", rc));
    return rc;
  }


  ///
  /// Construct version information of JHI internal handle.
  ///
  AsciiSPrint (
    JhiHandle->VersionInfo.JhiVersion, VERSION_BUFFER_SIZE, "%d.%d.%d.%d",
    JHIDXE_VER_MAJOR,
    JHIDXE_VER_MINOR,
    JHIDXE_VER_HOTFIX,
    JHIDXE_VER_BUILD
    );
  JhiHandle->VersionInfo.JhiVerMajor = (UINT8) JHIDXE_VER_MAJOR;
  JhiHandle->VersionInfo.JhiVerMinor = (UINT8) JHIDXE_VER_MINOR;
  JhiHandle->VersionInfo.JhiVerHotfix = (UINT8) JHIDXE_VER_HOTFIX;
  JhiHandle->VersionInfo.JhiVerBuild = (UINT8) JHIDXE_VER_BUILD;

  AsciiSPrint (
    JhiHandle->VersionInfo.FwVersion, VERSION_BUFFER_SIZE, "%d.%d.%d.%d",
    Info.Major,
    Info.Minor,
    Info.Hotfix,
    Info.Build
    );
  JhiHandle->VersionInfo.FwMajor = (UINT8) Info.Major;
  JhiHandle->VersionInfo.FwMinor = (UINT8) Info.Minor;
  JhiHandle->VersionInfo.FwHotfix = (UINT8) Info.Hotfix;
  JhiHandle->VersionInfo.FwBuild = (UINT8) Info.Build;

  JhiHandle->VersionInfo.CommType = JHI_HECI;

  JhiHandle->VersionInfo.PlatformId = (JHI_PLATFROM_ID) Info.PluginType;
  JhiHandle->VersionInfo.VmType = (JHI_VM_TYPE) JHI_VM_TYPE_BEIHAI;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JHI_VERSION_INFO\n"));
  DEBUG_JHI_DRIVER ((DEBUG_INFO, " JhiVersion:   %a\n", JhiHandle->VersionInfo.JhiVersion));
  DEBUG_JHI_DRIVER ((DEBUG_INFO, " FwVersion:    %a\n", JhiHandle->VersionInfo.FwVersion));
  DEBUG_JHI_DRIVER ((DEBUG_INFO, " CommType:     %x\n", JhiHandle->VersionInfo.CommType));
  DEBUG_JHI_DRIVER ((DEBUG_INFO, " PlatformId:   %x\n", JhiHandle->VersionInfo.PlatformId));
  DEBUG_JHI_DRIVER ((DEBUG_INFO, " VmType:       %x\n", JhiHandle->VersionInfo.VmType));
  DEBUG_JHI_DRIVER ((DEBUG_INFO, "\n"));

  return rc;
}

/**
  De-initialize JHI service library.

  @param[in]  JhiHandle           The JHI internal handle.

  @retval JHI_SUCCESS             De-initialize JHI service successfully.
  @retval others                  Error code of JHI_Plugin_DeInit.
**/
JHI_RET
JhisDeInit (
  IN JHI_I_HANDLE *JhiHandle
  )
{
  JHI_RET     rc;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisDeInit\n"));
  ASSERT (JhiHandle != NULL);

  rc = JHI_Plugin_DeInit ();
  if (rc != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhisDeInit fail, JHI_Plugin_DeInit error: %x\n", rc));
  }
  return rc;
}

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
  )
{
  JHI_RET                  rc;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisInstall\n"));
  ASSERT (JhiAppletHandle != NULL);

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "JhisInstall: FileBlob: %x, FileSize: %x\n", JhiAppletHandle->FileBlob, JhiAppletHandle->FileSize));
  rc = JHI_Plugin_DownloadApplet ((CHAR8 *) JhiAppletHandle->UcAppId, JhiAppletHandle->FileBlob, (unsigned int) JhiAppletHandle->FileSize);
  if (rc == JHI_FILE_IDENTICAL) {
#if EN_JHI_REINSTALL
    //
    // The applet already exists in the VM, force to re-install it!!!
    //
    DEBUG_JHI_DRIVER ((DEBUG_INFO, "The applet already exists in the VM, force to re-install it!\n"));
    JHI_Plugin_UnloadApplet ((const char *) JhiAppletHandle->UcAppId);
    rc = JHI_Plugin_DownloadApplet ((CHAR8 *) JhiAppletHandle->UcAppId, JhiAppletHandle->FileBlob, (unsigned int) JhiAppletHandle->FileSize);
#else
    //
    // The applet already exists in the VM, ignore duplicate error.
    //
    DEBUG_JHI_DRIVER ((DEBUG_INFO, "The applet already exists in the VM, ignore duplicate error!\n"));
    rc = JHI_SUCCESS;
#endif
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisInstall done, rc: %x\n", rc));
  return rc;
}

/**
  Uninstall an applet from JHI service library.

  @param[in]  JhiAppletHandle     The applet handle to be uninstalled.

  @retval JHI_SUCCESS             Uninstall applet successfully.
  @retval others                  Error code of JHI_Plugin_UnloadApplet.
**/
JHI_RET
JhisUninstall (
  IN JHI_I_APPLET_HANDLE *JhiAppletHandle
  )
{
  JHI_RET                  rc;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisUninstall\n"));
  ASSERT (JhiAppletHandle != NULL);

  rc = JHI_Plugin_UnloadApplet ((const char *) JhiAppletHandle->UcAppId);
  if ( rc != JHI_SUCCESS ) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhisUninstall fail, JHI_Plugin_UnloadApplet error\n"));
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisUninstall done, rc: %x\n", rc));
  return rc;
}

/**
  Create a session to JHI service library.

  @param[in]  JhiSessionHandle    The session handle to be created.

  @retval JHI_SUCCESS             Create session successfully.
  @retval others                  Error code of JHI_Plugin_CreateSession.
**/
JHI_RET
JhisCreateSession (
  IN JHI_I_SESSION_HANDLE *JhiSessionHandle
  )
{
  JHI_RET                 rc;
  JHI_I_HANDLE            *JhiHandleInstance;
  JHI_I_APPLET_HANDLE     *JhiAppletHandle;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisCreateSession\n"));
  ASSERT (JhiSessionHandle != NULL);

  JhiHandleInstance = JhiSessionHandle->JhiAppletHandle->JhiHandleInstance;
  ASSERT (JhiHandleInstance != NULL);
  JhiAppletHandle = JhiSessionHandle->JhiAppletHandle;
  ASSERT (JhiAppletHandle != NULL);

  rc = JHI_INTERNAL_ERROR;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisCreateSession, PlatformId: %x\n", JhiHandleInstance->VersionInfo.PlatformId));
  switch (JhiHandleInstance->VersionInfo.PlatformId) {
    case ME:
      DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "PlatformId: ME\n"));
      rc = JHI_Plugin_CreateSession (
             JhiAppletHandle->UcAppId,
             &JhiSessionHandle->VMSessionHandle,
             NULL,
             0,
             JhiSessionHandle->SessionID,
             JhiSessionHandle->InitBuffer
             );
      break;

    case CSE:
      DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "PlatformId: CSE\n"));
      //
      // in CSE we need the blobs for the create session API
      //
      rc = JHI_Plugin_CreateSession (
             JhiAppletHandle->UcAppId,
             &JhiSessionHandle->VMSessionHandle,
             JhiAppletHandle->FileBlob,
             (unsigned int) JhiAppletHandle->FileSize,
             JhiSessionHandle->SessionID,
             JhiSessionHandle->InitBuffer
             );
      break;

    default:
      DEBUG_JHI_DRIVER ((DEBUG_INFO, "PlatformId not support !!!\n"));
      break;
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisCreateSession done, rc: %x\n", rc));
  return rc;
}

/**
  Close a session to JHI service library.

  @param[in]  JhiSessionHandle    The session handle to be closed.

  @retval JHI_SUCCESS             Close session successfully.
  @retval others                  Error code of JHI_Plugin_CloseSession.
**/
JHI_RET
JhisCloseSession (
  IN JHI_I_SESSION_HANDLE *JhiSessionHandle
  )
{
  JHI_RET                 rc;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisCloseSession\n"));
  ASSERT (JhiSessionHandle != NULL);

  rc = JHI_Plugin_CloseSession (&JhiSessionHandle->VMSessionHandle);
  if (rc == JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhisCloseSession fail, JHI_Plugin_CloseSession error\n"));
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisCloseSession done, rc: %x\n", rc));
  return rc;
}

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
  )
{
  JHI_RET                 rc;
  JHI_I_APPLET_HANDLE     *JhiAppletHandle;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisSendAndRecv\n"));
  ASSERT (JhiSessionHandle != NULL);
  if (JhiSessionHandle == NULL) {
    return JHI_INVALID_PARAMS;
  }

  JhiAppletHandle = JhiSessionHandle->JhiAppletHandle;
  ASSERT (JhiAppletHandle != NULL);
  if (JhiAppletHandle == NULL) {
    return JHI_INVALID_PARAMS;
  }

  ASSERT (JhiSessionHandle && pCommBuffer && pResponseCode);
  if (!(JhiSessionHandle && pCommBuffer && pResponseCode)) {
    return JHI_INTERNAL_ERROR;
  }

  rc = JHI_Plugin_SendAndRecv (
         JhiSessionHandle->VMSessionHandle,
         nCommandId,
         pCommBuffer,
         pResponseCode
         );

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisSendAndRecv done, rc: %x\n", rc));
  return rc;
}

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
  IN JHI_I_APPLET_HANDLE *JhiAppletHandle,
  IN OUT JVM_COMM_BUFFER* pCommBuffer,
  IN UINTN                SessionCount
  )
{
  JHI_RET                 rc;
#ifdef GET_APPLET_PROPERTY_OPEN_SESSION_W_A
  JHI_I_HANDLE            *JhiHandleInstance;
  DATA_BUFFER             TmpDataBuffer;
  JHI_SESSION_ID          SessionID;
  VM_SESSION_HANDLE       VMSessionHandle;
#endif //GET_APPLET_PROPERTY_OPEN_SESSION_W_A

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisGetAppletProperty\n"));

  rc = JHI_INTERNAL_ERROR;

  if (pCommBuffer == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhisGetAppletProperty fail, invalid parameters.\n"));
    rc = JHI_INVALID_PARAMS;
    goto done;
  }

  if (!IsPropertySupported ((CHAR8*) pCommBuffer->TxBuf->buffer, pCommBuffer->TxBuf->length)) {
    rc = JHI_APPLET_PROPERTY_NOT_SUPPORTED;
    goto done;
  }

#ifdef GET_APPLET_PROPERTY_OPEN_SESSION_W_A
  VMSessionHandle = NULL;
  JhiHandleInstance = JhiAppletHandle->JhiHandleInstance;
  ASSERT (JhiHandleInstance != NULL);
  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisGetAppletProperty, PlatformId: %x\n", JhiHandleInstance->VersionInfo.PlatformId));

  if (JhiHandleInstance->VersionInfo.PlatformId == CSE) { // W/A only for CSE
    ///
    /// Check if there's an open session, if not, open one
    ///
    if (SessionCount == 0) {
      TmpDataBuffer.buffer = NULL;
      TmpDataBuffer.length = 0;

      ZeroMem (SessionID, sizeof (JHI_SESSION_ID));

      rc = JHI_Plugin_CreateSession (
             JhiAppletHandle->UcAppId,
             &VMSessionHandle,
             JhiAppletHandle->FileBlob,
             (unsigned int) JhiAppletHandle->FileSize,
             SessionID,
             &TmpDataBuffer
             );
    }
  }
#endif //GET_APPLET_PROPERTY_OPEN_SESSION_W_A

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "Applet property request: %a\n", (CHAR8 *) pCommBuffer->TxBuf->buffer));
  rc = JHI_Plugin_GetAppletProperty (JhiAppletHandle->UcAppId, pCommBuffer);
  if (JHI_SUCCESS != rc) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhisGetAppletProperty fail, unable to get applet property\n"));

    if (rc == JHI_INSUFFICIENT_BUFFER) {
      DEBUG_JHI_DRIVER ((DEBUG_WARN, "RxBuf->length change to %x\n", pCommBuffer->RxBuf->length));
    }
  }

#ifdef GET_APPLET_PROPERTY_OPEN_SESSION_W_A
  if (VMSessionHandle != NULL) {
    JHI_Plugin_CloseSession (&VMSessionHandle);
  }
#endif //GET_APPLET_PROPERTY_OPEN_SESSION_W_A

done:
  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhisGetAppletProperty done, rc: %x\n", rc));

  return rc;
}


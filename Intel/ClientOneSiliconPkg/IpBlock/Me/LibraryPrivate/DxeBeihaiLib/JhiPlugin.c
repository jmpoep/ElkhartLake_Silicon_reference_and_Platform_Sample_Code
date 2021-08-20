/** @file
  JHI plugin library, this is the plugin service of JHI DXE driver.
  This plugin use Beihai APIs to provide service.

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


#include <Library/DxeBeihaiLib/bhp_exp.h>         // Beihai
#include <Library/DxeBeihaiLib/BeihaiStatusHAL.h>
#include <Library/DxeBeihaiLib/bh_acp_exp.h>      // ACP file support

#include <Library/DxeBeihaiLib/jhi_plugin_internal.h>
#include <Library/DxeBeihaiLib/JhiPlugin.h>

#define PROPERTY_VERSION  "applet.version"

STATIC
SD_SESSION_HANDLE IntelSdHandle;
STATIC
BOOLEAN IsIntelSdHandleOpen = FALSE;
#ifdef __GNUC__
#pragma GCC diagnostic warning "-Wunused-variable"
#endif

STATIC
UINT32
JhiErrorTranslate (
  IN UINT32 BhError,
  IN UINT32 DefaultError
  );


/**
  Open Intel SD session.

  @retval BH_SUCCESS              Open Intel SD session successfully.
  @retval others                  Error code of BHP_OpenSDSession
**/
STATIC
BH_RET
OpenIntelSD (VOID)
{
  BH_RET ret;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "OpenIntelSD start\n"));
  if (IsIntelSdHandleOpen) {
    DEBUG_BEIHAI_LIB ((DEBUG_INFO, "OpenIntelSD end, Result = 0x%X\n", BH_SUCCESS));
    return BH_SUCCESS;
  }

  ret = BHP_OpenSDSession (INTEL_SD_UUID, &IntelSdHandle);

  if (ret == BH_SUCCESS) {
    IsIntelSdHandleOpen = TRUE;
  }

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "OpenIntelSD end, Result = 0x%X\n", ret));
  return ret;
}

/**
  Close Intel SD session.

  @retval BH_SUCCESS              Close Intel SD session successfully.
  @retval others                  Error code of BHP_OpenSDSession
**/
STATIC
BH_RET
CloseIntelSD (VOID)
{
  BH_RET ret;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "CloseIntelSD start\n"));
  if (!IsIntelSdHandleOpen) {
    DEBUG_BEIHAI_LIB ((DEBUG_INFO, "CloseIntelSD end, Result = 0x%X\n", BH_SUCCESS));
    return BH_SUCCESS;
  }

  ret = BHP_CloseSDSession (IntelSdHandle);

  if (ret == BH_SUCCESS) {
    IntelSdHandle = NULL;
    IsIntelSdHandleOpen = FALSE;
  }

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "CloseIntelSD end, Result = 0x%X\n", ret));
  return ret;
}

/**
  Check TA session is installed or not.

  @param[in] pAppId               The AppId.

  @retval TRUE                    TA is installed.
  @retval FALSE                   TA is not installed.
**/
STATIC
BOOLEAN
IsTAInstalled (
  CONST CHAR8   *pAppId
  )
{
  BH_RET        ret;
  UINT32        AppletsCount;
  CHAR8         **AppIdStrList;
  BOOLEAN       Result;
  UINT32        i;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "IsTAInstalled start\n"));

  Result = FALSE;
  AppletsCount = 0;
  AppIdStrList = NULL;

#ifndef OPEN_INTEL_SD_SESSION_ONCE
  //first open the SD
  ret = OpenIntelSD ();
  if (ret != BH_SUCCESS) {
    goto done;
  }
#endif

  ret = BHP_ListInstalledTAs (IntelSdHandle, INTEL_SD_UUID, &AppletsCount, &AppIdStrList);

#ifndef OPEN_INTEL_SD_SESSION_ONCE
  CloseIntelSD ();
#endif

  if (ret == BH_SUCCESS) {
    if (AppIdStrList == NULL) {
      goto done;
    }

    for (i=0; i < AppletsCount; ++i) {
      if (AppIdStrList[i] == NULL) {
        continue;
      }
      if (AsciiStriCmp (AppIdStrList[i], pAppId) == 0) {
        DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "AppId found in TA AppIdList\n"));
        Result = TRUE;
      }
      FreePool (AppIdStrList[i]);
      AppIdStrList[i] = NULL;
    }

    FreePool (AppIdStrList);
  }

done:
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "IsTAInstalled end, Result = 0x%X\n", Result));
  return Result;
}

/**
  Get count of TA session.

  @param[in] pAppId               The AppId.

  @retval                         The count of TA session.
**/
STATIC
UINT32
GetTASessionCount (
  CONST CHAR8           *pAppId
  )
{
  BH_RET                ret;
  unsigned int          AppletSessionsCount;
  JAVATA_SESSION_HANDLE *AppletSessions;

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "GetTASessionCount start\n"));
  AppletSessionsCount = 0;
  AppletSessions = NULL;
  if ((pAppId == NULL) || (!IsTAInstalled (pAppId))) {
    DEBUG_BEIHAI_LIB ((DEBUG_INFO, "pAppId is NULL or not installed\n"));
    goto done;
  }

  ret = BHP_ListTASessions (pAppId, &AppletSessionsCount, &AppletSessions);
  if (ret != BH_SUCCESS) {
    BHP_Free (AppletSessions);
    AppletSessions = NULL;
    AppletSessionsCount = 0;
  }

done:
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "GetTASessionCount end, Result = 0x%X\n", AppletSessionsCount));
  return AppletSessionsCount;
}

#ifdef MAX_SESSIONS_W_A
/**
  Get total count of sessions.

  @retval                         The total count of sessions.
**/
STATIC
UINTN
GetTotalSessionsCount (VOID)
{
  BH_RET ret;
  UINT32 AppletsCount = 0;
  UINT32 AppletSessionsCount = 0;
  UINT32 totalSessionsCount = 0;
  CHAR8** AppIdStrList = NULL;
  JAVATA_SESSION_HANDLE* AppletSessions = NULL;
  UINT32 i;

#ifndef OPEN_INTEL_SD_SESSION_ONCE
  ///
  /// first open the SD
  ///
  ret = OpenIntelSD ();
  if (ret != BH_SUCCESS) {
    return;
  }
#endif

  ret = BHP_ListInstalledTAs (IntelSdHandle, INTEL_SD_UUID, &AppletsCount, &AppIdStrList);

#ifndef OPEN_INTEL_SD_SESSION_ONCE
  ///
  /// close the SD
  ///
  CloseIntelSD ();
#endif

  if (AppIdStrList == NULL) {
    return 0;
  }

  if (ret == BH_SUCCESS) {
    for (i=0; i < AppletsCount; ++i) {
      if (AppIdStrList[i] == NULL) {
        continue;
      }
      AppletSessionsCount = 0;
      ///
      /// Getting TA sessions count.
      ///
      ret = BHP_ListTASessions (AppIdStrList[i], &AppletSessionsCount, &AppletSessions);
      if (ret == BH_SUCCESS) {
        totalSessionsCount += AppletSessionsCount;
      }
      if (AppletSessions != NULL) {
        FreePool (AppletSessions);
        AppletSessions = NULL;
      }
      FreePool (AppIdStrList[i]);
      AppIdStrList[i] = NULL;
    }
  }

  if (AppIdStrList != NULL) {
    FreePool (AppIdStrList);
    AppIdStrList = NULL;
  }

  return totalSessionsCount;
}
#endif

/**
  Send the session ID to applet.

  @param[in] pSession             The session handle to Beihai library.
  @param[in] SessionID            The session ID to Beihai library.
  @param[in] AppletResponse       The pointer to the buffer of response code.

  @retval BH_SUCCESS              Send the session ID successfully.
  @retval others                  Error code of BHP_SendAndRecvInternal.
**/
STATIC
BH_RET
SendSessionIDtoApplet (
  IN VM_SESSION_HANDLE *pSession,
  IN JHI_SESSION_ID    SessionID,
  OUT int              *AppletResponse
  )
{
  // TODO: BH bug w/a - unable to send null output buffer.
  BH_RET        ret;
  CHAR8         pOutput[] = "output\0";
  unsigned int  outpuLength = 0;
  CHAR8         Uuid [sizeof (JHI_SESSION_ID) ];

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "SendSessionIDtoApplet start\n"));
  CopyMem (Uuid, &SessionID, sizeof (JHI_SESSION_ID));
  ///
  /// The value '1' in the 'what' field is internally reserved for passing the SessionID
  ///
  ret = BHP_SendAndRecvInternal (
          *pSession, 1, 0,
          Uuid, sizeof (JHI_SESSION_ID),
          (void**)&pOutput, (unsigned int *)&outpuLength,
          AppletResponse
          );
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "SendSessionIDtoApplet end, Result = 0x%X", ret));
  return ret;
}

/**
  Set uninstall package

  @param[in] pAppId               The AppId.
  @param[out] UninstallPkg        The pointer to the buffer of uninstall package

  @retval TRUE                    Set uninstall package successfully.
  @retval FALSE                   Set uninstall package failed.
**/
STATIC
BOOLEAN
SetUninstallPackage (
  IN CONST CHAR8  *pAppId,
  OUT CHAR8       **UninstallPkg
  )
{
  UINTN           i;
  CHAR8           *ptr;
  CHAR8           str[3];
#ifdef USE_LOCAL_ACP_FILE
  EFI_STATUS Status;
  EFI_FILE        *FileHandle;
  UINTN           FileSize;
#endif

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "SetUninstallPackage (pAppId: %a)\n", pAppId));

  if (pAppId == NULL || UninstallPkg == NULL) {
    return FALSE;
  }

  *UninstallPkg = NULL;

#ifdef USE_LOCAL_ACP_FILE
  ///
  /// use local acp file
  ///
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Use local acp file to set Uninstall package\n"));
  FileHandle = NULL;
  FileSize = 0;

  Status = FileOpen (UNINSTALL_PACK_FILE, &FileHandle);
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "SetUninstallPackage fail, open file error, Status: %r\n", Status));
    return FALSE;
  }

  Status = FileRead (FileHandle, UninstallPkg, &FileSize);
  if (EFI_ERROR (Status)) {
    DEBUG_BEIHAI_LIB ((DEBUG_ERROR, "SetUninstallPackage fail, read file error, Status: %r\n", Status));
    goto done;
  }

done:
  if (FileHandle != NULL) {
    FileClose (FileHandle);
  }

  if (*UninstallPkg == NULL) {
    return FALSE;
  }
#else
  ///
  /// copy from pre-defined uninstall pack
  ///
  *UninstallPkg = AllocateZeroPool (UNINSTALL_PACK_LEN);
  if (*UninstallPkg == NULL) {
    return FALSE;
  }
  CopyMem (*UninstallPkg, UNINSTALL_PACK, UNINSTALL_PACK_LEN);
#endif

  ///
  /// Replace the uuid in the package
  ///
  ptr = *UninstallPkg + APPID_STR_LENGTH + JHI_CSS_HEADER_SIZE;
  for (i = 0; i < APPID_STR_LENGTH; i+=2) {
    str[0] = pAppId[i];
    str[1] = pAppId[i+1];
    str[2] = 0;
    *ptr = (CHAR8) (UINTN) AsciiStrHexToUint64 (str);
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "str: %a -> %02x\n", str, (CHAR8)*ptr));
    ++ptr;
  }

  return TRUE;
}

#ifdef GET_APPLET_PROPERTY_NAMES_W_A
/**
  Set uninstall package

  @param[in] pAppId               The AppId.
  @param[out] UninstallPkg        The pointer to the buffer of uninstall package

  @retval TRUE                    Set uninstall package successfully.
  @retval FALSE                   Set uninstall package failed.
**/
BOOLEAN
ConvertAppProperty (
  IN CHAR8* Input,
  OUT CHAR8** Output,
  OUT int* OutputLen
  )
{
  CHAR8 NewString [32];

  if (Output == NULL || OutputLen == NULL) {
    return FALSE;
  }

  NewString [0] = 0;
  if (AsciiStrCmp (Input, "security.version") == 0) {
    AsciiStrCpyS (NewString, sizeof (NewString) / sizeof (CHAR8), "svn");
  } else if (AsciiStrCmp (Input, "applet.version") == 0) {
    AsciiStrCpyS (NewString, sizeof (NewString) / sizeof (CHAR8), "ta_version");
  } else if (AsciiStrCmp (Input, "applet.flash.quota") == 0) {
    AsciiStrCpyS (NewString, sizeof (NewString) / sizeof (CHAR8), "flash_quota");
  } else if (AsciiStrCmp (Input, "applet.version") == 0) {
    AsciiStrCpyS (NewString, sizeof (NewString) / sizeof (CHAR8), "ta_version");
  } else if (AsciiStrCmp (Input, "") == 0) {
    AsciiStrCpyS (NewString, sizeof (NewString) / sizeof (CHAR8), "");
  } else {
    AsciiStrCpyS (NewString, sizeof (NewString) / sizeof (CHAR8), Input);
  }

  *OutputLen = AsciiStrLen (NewString);
  *Output = (CHAR8*) AllocateZeroPool (*OutputLen + 1);
  AsciiStrCpyS (*Output, (*OutputLen + 1) / sizeof (CHAR8), NewString);

  return TRUE;
}
#endif

/**
  Convert version info for W/A

  @param[in, out] Output          The pointer to the buffer for string conversion.

  @retval TRUE                    Convert ersion info successfully.
  @retval FALSE                   Convert ersion info failed.
**/
BOOLEAN
ConvertAppPropertyVersion (
  IN OUT CHAR8** Output
  )
{
  return TRUE;
}

/**
  Initialize Beihai library.

  @param[in] info                 The pointer to the buffer of BHP_INFO.

  @retval JHI_SUCCESS             Initialize Beihai library successfully.
  @retval others                  Initialize Beihai library failed with error code.
**/
UINT32
JHI_Plugin_Init (
  OUT BHP_INFO *info
  )
{
  BH_RET ret;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_Init\n"));

  ret = BHP_Init (NULL, info);  // Send NULL to use default MEI handle in Beihai library

#ifdef OPEN_INTEL_SD_SESSION_ONCE
  if (ret == BH_SUCCESS) {
    OpenIntelSD ();
  }
#endif

  return JhiErrorTranslate (ret, JHI_NO_CONNECTION_TO_FIRMWARE);
}

/**
  De-initialize Beihai library.

  @retval JHI_SUCCESS             De-initialize Beihai library successfully.
  @retval others                  De-initialize Beihai library failed with error code.
**/
UINT32
JHI_Plugin_DeInit (VOID)
{
  BH_RET ret;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_DeInit\n"));

#ifdef OPEN_INTEL_SD_SESSION_ONCE
  CloseIntelSD ();
#endif

  ret = BHP_Deinit ();

  return JhiErrorTranslate (ret, JHI_INTERNAL_ERROR);
}

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
  )
{
  BH_RET ret = BPE_INTERNAL_ERROR;
  // first check if there are open sessions:
  UINT32 AppletSessionsCount = 0;
#ifdef MAX_APPLETS_W_A
  UINTN i;
  UINTN AppletsCount = 0;
  CHAR8** AppIdStrList = NULL;
#endif  // MAX_APPLETS_W_A


  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_DownloadApplet (pAppBlob: %x, AppSize: %x)\n", pAppBlob, AppSize));
  AppletSessionsCount = GetTASessionCount (pAppId);
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "AppletSessionsCount: %x\n", AppletSessionsCount));
  if (AppletSessionsCount > 0) {
    return JHI_INSTALL_FAILURE_SESSIONS_EXISTS;
  }

#ifdef MAX_APPLETS_W_A
  if (!IsTAInstalled (pAppId)) {
    ret = BHP_ListInstalledTAs (IntelSdHandle, INTEL_SD_UUID, (unsigned int *) &AppletsCount, &AppIdStrList); // just to get the AppletsCount
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "BHP_ListInstalledTAs: ret: %x, AppletsCount: %x\n", ret, AppletsCount));
    // cleanup
    if (AppIdStrList != NULL) {
      for (i = 0; i<AppletsCount; ++i) {
        if (AppIdStrList[i] != NULL) {
          FreePool (AppIdStrList[i]);
        }
      }
      FreePool (AppIdStrList);
    }
    DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "Applets installed count = %d.\n", AppletsCount));
    if (AppletsCount >= MAX_APPLETS_COUNT) {
      DEBUG_BEIHAI_LIB ((DEBUG_INFO, "MAX_APPLETS_W_A enforcement - returning JHI_MAX_INSTALLED_APPLETS_REACHED.\n"));
      return JHI_MAX_INSTALLED_APPLETS_REACHED;
    }
  }
#endif  // MAX_APPLETS_W_A

#ifndef OPEN_INTEL_SD_SESSION_ONCE
  //first open the SD
  ret = OpenIntelSD ();
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "OpenIntelSD first: %x\n", ret));
  if (ret != BH_SUCCESS) {
    return ret;
  }
#endif

  ret = BHP_SendAdminCmdPkg (IntelSdHandle, (CHAR8*) pAppBlob, AppSize);

#ifndef OPEN_INTEL_SD_SESSION_ONCE
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "CloseIntelSD\n"));
  //close the SD
  CloseIntelSD ();
#endif

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_DownloadApplet end, Result = 0x%X\n", ret));
  return JhiErrorTranslate (ret, JHI_INTERNAL_ERROR);
}

/**
  Unload an applet from Beihai library.

  @param[in] pAppId               The AppId.

  @retval JHI_SUCCESS             Unload an applet successfully.
  @retval others                  Unload an applet failed with error code.
**/
UINT32
JHI_Plugin_UnloadApplet (
  IN CONST CHAR8 *AppId
  )
{
  CHAR8* UninstallPkg = NULL;
  BH_RET ret;
#ifndef OPEN_INTEL_SD_SESSION_ONCE
  BH_RET ret2;
  BH_RET ret3;
#endif

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_UnloadApplet start\n"));
#ifndef OPEN_INTEL_SD_SESSION_ONCE
  //first open the SD
  ret3 = OpenIntelSD ();
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "OpenIntelSD first: %x\n", ret3));
  if (ret3 != BH_SUCCESS) {
    return ret3;
  }
#endif

  SetUninstallPackage (AppId, &UninstallPkg);
  if (UninstallPkg == NULL) {
    return JHI_INTERNAL_ERROR;
  }

  ret = BHP_SendAdminCmdPkg (IntelSdHandle, (CONST CHAR8*) UninstallPkg, UNINSTALL_PACK_LEN);
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "uninstalling applet (%a), ret: %x\n", AppId, ret));

#ifndef OPEN_INTEL_SD_SESSION_ONCE
  //close the SD
  ret2 = CloseIntelSD ();
  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "CloseIntelSD: %x\n", ret2));
#endif

  FreePool (UninstallPkg);

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_UnloadApplet end, Result = 0x%X\n", ret));
  return JhiErrorTranslate (ret, JHI_INTERNAL_ERROR);
}

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
  )
{
  ACInsJTAPackExt ta_pack;
  unsigned int ta_size = 0;
  BH_RET ret;
  int AppletResponse = -1;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_CreateSession (pAppBlob: %x BlobSize: %x)\n", pAppBlob, BlobSize));

#ifdef MAX_SESSIONS_W_A
  if (GetTotalSessionsCount () >= MAX_SESSIONS_COUNT) {
    return JHI_MAX_SESSIONS_REACHED;
  }
#endif //MAX_SESSIONS_W_A

  ZeroMem (&ta_pack, sizeof (ACInsJTAPackExt));
  ACP_pload_ins_jta (pAppBlob, BlobSize, &ta_pack);
  ta_size = BlobSize - (unsigned int) (UINTN) ((UINT8*) ta_pack.ta_pack - (UINT8*) pAppBlob);

  DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "ta_size: %x, offset: %x\n", ta_size, (unsigned int) (UINTN) ((UINT8*) ta_pack.ta_pack - (UINT8*) pAppBlob)));

  ret = BHP_OpenTASession (pSession, AppId, ta_pack.ta_pack, ta_size, (CHAR8*) InitBuffer->buffer, InitBuffer->length);
  if (ret == BH_SUCCESS) {
    //
    // Sending the SessionID to the applet.
    //
    ret = SendSessionIDtoApplet (pSession, SessionID, &AppletResponse);
    if (ret != BH_SUCCESS || AppletResponse != 0) {
      DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_CreateSession failed, SendSessionIDtoApplet error, Result = 0x%X\n", ret));
      ret = JHI_INTERNAL_ERROR;
    }
  }
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_CreateSession end, Result = 0x%X\n", ret));
  return JhiErrorTranslate (ret, JHI_INTERNAL_ERROR);
}

/**
  Close a session for an applet to Beihai library.

  @param[in] pSession             The session handle.

  @retval JHI_SUCCESS             Close a session successfully.
  @retval others                  Close a session failed with error code.
**/
UINT32
JHI_Plugin_CloseSession (
  IN VM_SESSION_HANDLE* pSession
  )
{
  BH_RET ret;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_CloseSession start\n"));
  ret = BHP_CloseTASession (*pSession);
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_CloseSession end, Result = 0x%X\n", ret));

  return JhiErrorTranslate (ret, JHI_INTERNAL_ERROR);
}

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
  )
{
  BH_RET ret;
  CHAR8* inputBuffer = (CHAR8*) pIOBuffer->TxBuf->buffer;
  int inputBufferLength = pIOBuffer->TxBuf->length;

  CHAR8* outputBuffer = (CHAR8*) pIOBuffer->RxBuf->buffer;
  int* outputBufferLength = (int*) &pIOBuffer->RxBuf->length;

  CHAR8* output = NULL;
  int outputLength = *outputBufferLength;

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_SendAndRecv start\n"));
  ret = BHP_SendAndRecv (Session, nCommandId, inputBuffer, inputBufferLength, (void **)&output, (unsigned int *)&outputLength, pResponseCode);

  if (ret == BH_SUCCESS && output != NULL) {
    ///
    /// Copy the output to the output buffer
    ///
    CopyMem (outputBuffer, output,outputLength);
  }
  *outputBufferLength = outputLength;

  ret = JhiErrorTranslate (ret, JHI_INTERNAL_ERROR);

  if (output) {
    BHP_Free (output);
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_SendAndRecv end, Result = 0x%X\n", ret));
  return ret;
}

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
  )
{
  UINT32          ret;
  char            *inputBuffer;
  int             inputBufferLength;
  char            PropertyVersion [] = PROPERTY_VERSION;
  char            *output;
  int             outputLength;
  char            *outputBuffer;
  int             *outputBufferLength; // number of characters without /0, not size of buffer
#ifdef GET_APPLET_PROPERTY_NAMES_W_A
  char            *newProperty;
  int             newPropertyLen;
#endif


  ret = JHI_INTERNAL_ERROR;
  inputBuffer = (CHAR8*) pIOBuffer->TxBuf->buffer;
  inputBufferLength = pIOBuffer->TxBuf->length;
  output = NULL;
  outputLength = 0;
  outputBuffer = (CHAR8*) pIOBuffer->RxBuf->buffer;
  outputBufferLength = (int *) &pIOBuffer->RxBuf->length;
  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_GetAppletProperty (AppId: %a, %a)\n", AppId, inputBuffer));

#ifdef GET_APPLET_PROPERTY_NAMES_W_A
  newProperty = NULL;
  newPropertyLen = 0;

  ConvertAppProperty (inputBuffer, &newProperty, &newPropertyLen);
  ret = BHP_QueryTAProperty (AppId, newProperty, newPropertyLen, &output);
  FreePool (newProperty);
#else
  ret = BHP_QueryTAProperty (AppId, inputBuffer, inputBufferLength, &output);
#endif

  if (ret == BH_SUCCESS && output != NULL) {
    if (AsciiStrCmp (inputBuffer, PropertyVersion) == 0) {
      ConvertAppPropertyVersion (&output);
    }

    outputLength = (UINT32) AsciiStrLen (output);

    if (*outputBufferLength < outputLength) {
      ///
      /// Buffer provided is too small for the response
      ///
      DEBUG_BEIHAI_LIB_VERBOSE ((DEBUG_INFO, "JHI_Plugin_GetAppletProperty: insufficient buffer sent to VM, expected: %d, received: %d\n", outputLength, *outputBufferLength));
      ret = JHI_INSUFFICIENT_BUFFER;
      *outputBufferLength = outputLength;
      goto cleanup;
    }

    ///
    /// Copy the output to the output buffer
    ///
    AsciiStrCpyS (outputBuffer, *outputBufferLength, output);
    *outputBufferLength = outputLength;
  } else {
    *outputBufferLength = 0;
  }

  ret = JhiErrorTranslate (ret, JHI_INTERNAL_ERROR);

cleanup:

  if (output != NULL) {
    BHP_Free (output);
  }

  DEBUG_BEIHAI_LIB ((DEBUG_INFO, "JHI_Plugin_GetAppletProperty end, Result = 0x%X\n", ret));
  return ret;
}

/**
  Translate Beihai error code into JHI status code.

  @param[in] BhError              The Beihai error code.
  @param[in] DefaultError         The default JHI status code.

  @retval                         JHI status code.
**/
STATIC
UINT32
JhiErrorTranslate (
  IN UINT32 BhError,
  IN UINT32 DefaultError
  )
{
  UINT32   JhiError;
  BOOLEAN  CheckHalError;

  JhiError      = JHI_INTERNAL_ERROR;
  CheckHalError = FALSE;

  switch (BhError) {
    case BH_SUCCESS:
      JhiError = JHI_SUCCESS;
      break;

      // SendAndRecv
    case BHE_INSUFFICIENT_BUFFER:
    case BHE_APPLET_SMALL_BUFFER:
      JhiError = JHI_INSUFFICIENT_BUFFER;
      break;

    case BPE_COMMS_ERROR:
    case BPE_NOT_INIT:
    case BPE_NO_CONNECTION_TO_FIRMWARE:
      JhiError = JHI_NO_CONNECTION_TO_FIRMWARE;
      break;

    case BHE_VM_INSTANCE_INIT_FAIL:
      JhiError = JHI_FIRMWARE_OUT_OF_RESOURCES;
      break;

    case BHE_UNCAUGHT_EXCEPTION:
    case BHE_APPLET_CRASHED:
    case BHE_WD_TIMEOUT:
    case BPE_INVALID_PARAMS:
    case BHE_APPLET_GENERIC: // not documented but sometimes recieved. (usually an exception thrown in onInit)
    case BHE_BAD_STATE: // not documented but sometimes recieved. (might be related to max heap)
      // TODO:
      //case BHE_APPLET_SMALL_BUFFER:
      JhiError = JHI_APPLET_FATAL;
      break;

    // DownloadApplet
    case BHE_SDM_SIGNAGURE_VERIFY_FAIL:
      JhiError = JHI_FILE_ERROR_AUTH;
      break;

    case BHE_INVALID_BPK_FILE:
      JhiError = JHI_INVALID_PACKAGE_FORMAT;
      break;

    case BHE_SDM_ALREADY_EXIST:
      JhiError = JHI_FILE_IDENTICAL;
      break;

    case BHE_SDM_TA_NUMBER_LIMIT:
      JhiError = JHI_MAX_INSTALLED_APPLETS_REACHED;
      break;

    case BHE_SDM_SVL_CHECK_FAIL:
      JhiError = JHI_SVL_CHECK_FAIL;
      break;

      // UnloadApplet
    case BHE_EXIST_LIVE_SESSION:
      JhiError = JHI_UNINSTALL_FAILURE_SESSIONS_EXISTS;
      break;

    case BHE_PACKAGE_NOT_FOUND:
    case BHE_SDM_NOT_FOUND:
      JhiError = JHI_APPLET_NOT_INSTALLED;
      break;

      // JHI_Plugin_GetAppletProperty
    case BHE_QUERY_PROP_NOT_SUPPORT:
      JhiError = JHI_APPLET_PROPERTY_NOT_SUPPORTED;
      break;

      // IAC errors
    case BHE_IAC_SERVICE_HOST_SESSION_NUM_EXCEED:
      JhiError = JHI_IAC_SERVER_SESSION_EXIST;
      break;

    case BHE_IAC_EXIST_INTERNAL_SESSION:
      JhiError = JHI_IAC_SERVER_INTERNAL_SESSIONS_EXIST;
      break;

      // Access control errors
    case BHE_GROUP_CHECK_FAIL:
      JhiError = JHI_MISSING_ACCESS_CONTROL;
      break;

    case BHE_SESSION_NUM_EXCEED:
      JhiError = JHI_MAX_SESSIONS_REACHED;
      break;

    default:
      CheckHalError = TRUE;
      break;
  }

  if (CheckHalError == TRUE) {
    switch ((BH_STATUS) BhError) {
      case HAL_BUFFER_TOO_SMALL:
        JhiError = JHI_INSUFFICIENT_BUFFER;
        break;

      case HAL_OUT_OF_MEMORY:
      case HAL_TIMED_OUT:
        JhiError = JHI_APPLET_FATAL;
        break;

      case HAL_ILLEGAL_SIGNATURE:
      case HAL_ILLEGAL_VERSION:
      case HAL_FW_VERSION_MISMATCH:
      case HAL_UNSUPPORTED_CPU_TYPE:
      case HAL_UNSUPPORTED_PCH_TYPE:
      case HAL_UNSUPPORTED_FEATURE_SET:
      case HAL_UNSUPPORTED_PLATFORM_TYPE:
        JhiError = JHI_FILE_ERROR_AUTH;
        break;

      case HAL_ALREADY_INSTALLED:
        JhiError = JHI_FILE_IDENTICAL;
        break;

      case HAL_OUT_OF_STORAGE:
      case HAL_OUT_OF_RESOURCES:
        JhiError = JHI_MAX_INSTALLED_APPLETS_REACHED;
        break;

      default:
        JhiError = DefaultError;
        break;
    }
  }

  return JhiError;
}


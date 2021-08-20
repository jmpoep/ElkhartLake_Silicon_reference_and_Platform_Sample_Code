/** @file
  JHI API core. This is the frontend library of JHI DXE driver.
  This library link to JHI service.

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

#include <Library/DxeJhiSupportLib.h>
#include <Library/PchInfoLib.h>
#include "Jhid.h"
#include "Jhis.h"


STATIC
struct
SESSION_GUID_LIST {
  BOOLEAN     Free;
  CONST GUID  Guid;
} SessionGuidList [] = {  // To support ME11 (Max Session Count = 10), we need at least 10 elements here.
  {TRUE, {0x970c1075, 0xdd41, 0x4b4f, {0xa7, 0xcd, 0x47, 0x96, 0x9e, 0x28, 0x57, 0xeb}}},
  {TRUE, {0x6101cf31, 0x3021, 0x4abe, {0x9a, 0x85, 0xd1, 0x6d, 0xb6, 0x21, 0x13, 0x27}}},
  {TRUE, {0x75940a3e, 0x0535, 0x45bc, {0x81, 0xb9, 0x86, 0xcc, 0xd3, 0x79, 0x24, 0x46}}},
  {TRUE, {0x58da1791, 0x71a3, 0x4e85, {0x98, 0x56, 0x27, 0x1b, 0x57, 0x96, 0x43, 0x9b}}},
  {TRUE, {0x7f91686c, 0x21ae, 0x432c, {0xba, 0x46, 0x50, 0xcc, 0x36, 0x36, 0xd0, 0x3e}}},
  {TRUE, {0x324d6aff, 0xe032, 0x4358, {0xba, 0x1b, 0x91, 0x4a, 0x28, 0xa7, 0x63, 0xae}}},
  {TRUE, {0x2f541ba2, 0x9755, 0x454d, {0x98, 0x10, 0xbc, 0x5b, 0xf6, 0xa4, 0x6c, 0x18}}},
  {TRUE, {0xd936cbc9, 0x979b, 0x4012, {0xba, 0xec, 0xf8, 0xfd, 0xe7, 0x5c, 0xc6, 0x3f}}},
  {TRUE, {0xc0223910, 0x52e3, 0x46ee, {0xa6, 0x9e, 0x74, 0xb1, 0x1d, 0x35, 0x49, 0xa8}}},
  {TRUE, {0x3c1189ae, 0xdc86, 0x4d50, {0x85, 0xdd, 0x25, 0xc0, 0x0b, 0x76, 0xda, 0xb2}}},
  // To support ME13 (Max Session Count = 16), we need at least 16 elements here.
  {TRUE, {0x3e862167, 0x4c29, 0x4bbb, {0x09d, 0xea, 0x8c, 0xa3, 0x90, 0xa2, 0x57, 0x1e}}},
  {TRUE, {0x1b3a528a, 0x4a3a, 0x422c, {0x0a5, 0xdd, 0x2e, 0xe8, 0x33, 0xf0, 0xcb, 0x3e}}},
  {TRUE, {0xbf6986bf, 0x9097, 0x4e30, {0x0a0, 0x8f, 0xa6, 0x54, 0x60, 0x22, 0xa3, 0xd2}}},
  {TRUE, {0x15ca5d7a, 0x4edc, 0x4189, {0x09d, 0xc9, 0x93, 0xc5, 0xca, 0x74, 0x90, 0x45}}},
  {TRUE, {0xa72f751a, 0xf2ab, 0x40d4, {0x09a, 0xb1, 0x28, 0x47, 0xd9, 0x24, 0x89, 0x02}}},
  {TRUE, {0x2f922b0b, 0x863c, 0x4125, {0x095, 0x47, 0x5c, 0xa1, 0x00, 0x98, 0x64, 0xe8}}},
};
STATIC
UINTN mSessionGuidIndex = 0;
STATIC
JHI_I_HANDLE *mAppHandle = NULL;  // a handle that is passed by the application when calling any jhi API function.


/**
  Create GUID for session ID (UEFI implementation of UuidCreate)

  @retval - Index of SessionGuidList
**/
STATIC
UINTN
SessionGuidCreate (VOID)
{
  UINTN i;
  UINTN Count;
  UINTN Index;

  Index = (UINTN) (-1);

  Count = sizeof (SessionGuidList) / sizeof (SessionGuidList[0]);
  for (i = 0; i < Count; i++) {
    mSessionGuidIndex = (mSessionGuidIndex + i) % Count;
    if (SessionGuidList [mSessionGuidIndex].Free == TRUE) {
      DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "SessionHandleCreate success, mSessionGuidIndex: %x (Count: %x)\n",
                                 mSessionGuidIndex, Count));
      Index = mSessionGuidIndex;
      mSessionGuidIndex = (mSessionGuidIndex + 1) % Count;
      break;
    }
  }

  return Index;
}

/**
  Release GUID for session ID

  @param[in]  Index               The index of SessionGuidList.
**/
STATIC
VOID
SessionGuidDestroy (
  UINTN Index
  )
{
  UINTN Count;

  Count = sizeof (SessionGuidList) / sizeof (SessionGuidList[0]);

  ASSERT (Index < Count);
  ASSERT (SessionGuidList [Index].Free == FALSE);
  if (Index < Count) {
    SessionGuidList [Index].Free = TRUE;
  }
}

/**
  Validate JHI handle

  @param[in]  Handle              The handle to be valid.

  @retval TRUE                    The handle is valid.
  @retval FALSE                   The handle is invalid.
**/
STATIC
JHI_RET
ValidateJHIhandle (
  IN JHI_HANDLE Handle
  )
{
  JHI_I_HANDLE       *JhiHandleInstance;

  if (Handle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "ValidateJHIhandle fail, Handle is NULL\n"));
    return JHI_INVALID_HANDLE;
  }

  if ((JHI_I_HANDLE*) Handle != mAppHandle) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "ValidateJHIhandle fail, Handle mismatch with mAppHandle\n"));
    return JHI_INVALID_HANDLE;
  }

  JhiHandleInstance = (JHI_I_HANDLE *) Handle;
  if (JhiHandleInstance->Signature != JHI_HANDLE_INSTANCE_SIGNATURE) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "ValidateJHIhandle fail, JHI_HANDLE signature mismatch(%08x != %08x)!\n",
                       JhiHandleInstance->Signature, JHI_HANDLE_INSTANCE_SIGNATURE));
    return JHI_INVALID_HANDLE;
  }

  return JHI_SUCCESS;
}

/**
  Validate AppID and convert it to upper case

  @param[in]  AppId               The AppId to be valid.
  @param[out] UcAppId             The AppId with upper case. (uc means Upper Case)

  @retval JHI_SUCCESS             AppID is valid.
  @retval JHI_INVALID_APPLET_GUID AppID is invalid.
**/
STATIC
JHI_RET
ValidateUUID (
  IN CONST APPID_STR AppId,
  OUT APPID_STR      UcAppId
  )
{
  JHI_RET rc;
  UINTN Len;
  UINTN i;

  rc = JHI_SUCCESS;

  ASSERT (AppId && UcAppId);
  if (!(AppId && UcAppId)) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "ValidateUUID fail, AppId(%x) or UcAppId(%x) is NULL.\n", AppId, UcAppId));
    return JHI_INVALID_APPLET_GUID;
  }

  if (AppId[APPID_STR_LENGTH] != '\0') {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "ValidateUUID fail, not NULL-terminated AppId string.\n"));
    return JHI_INVALID_APPLET_GUID;
  }

  Len = AsciiStrLen (AppId);
  ASSERT (APPID_STR_LENGTH == Len);
  if (APPID_STR_LENGTH != Len) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "ValidateUUID fail, the length of AppId is mismatched.\n"));
    return JHI_INVALID_APPLET_GUID;
  }

  //
  // Go thru each of the byte and convert to upper case if need be.
  //
  for ( i=0; i<Len; i++, AppId++) {
    UINT8 c = (*AppId & 0xff );
    if ( AsciiIsDigit (c)) {
      UcAppId[i] = c;
    } else if (('a' <= (c)) && ((c) <= 'z')) {
      UcAppId[i] = InternalAsciiToUpper (c);
    } else {
      return JHI_INVALID_APPLET_GUID;
    }
  }

  UcAppId[APPID_STR_LENGTH] = 0;
  return rc;
}

/**
  Create session handle

  @param[in]  JhiAppletHandle     The applet handle that the session belongs.
  @param[in]  Flags               The attributes for this session.
  @param[in]  InitBuffer          The buffer for initialization this session.

  @retval                         The pointer to session handle.
**/
STATIC
JHI_I_SESSION_HANDLE *
SessionHandleCreate (
  IN JHI_I_APPLET_HANDLE *JhiAppletHandle,
  IN UINT32 Flags,
  IN DATA_BUFFER* InitBuffer
  )
{
  JHI_I_SESSION_HANDLE *JhiSessionHandle;
  UINTN GuidListIndex;

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "SessionHandleCreate\n"));

  if (JhiAppletHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "SessionHandleCreate fail, invalid parameter.\n"));
    return NULL;
  }

  JhiSessionHandle = (JHI_I_SESSION_HANDLE *) AllocateZeroPool (sizeof (JHI_I_SESSION_HANDLE));
  if (JhiSessionHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "SessionHandleCreate fail, insufficient memory for JHI_I_SESSION_HANDLE.\n"));
    return NULL;
  }

  JhiSessionHandle->Signature = JHI_SESSION_HANDLE_INSTANCE_SIGNATURE;
  JhiSessionHandle->JhiAppletHandle = JhiAppletHandle;
  GuidListIndex = SessionGuidCreate ();
  if (GuidListIndex == (UINTN) (-1)) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "SessionHandleCreate fail, no free Session Guid available.\n"));
    return NULL;
  }
  JhiSessionHandle->GuidListIndex = GuidListIndex;
  SessionGuidList [GuidListIndex].Free = FALSE;
  CopyMem (JhiSessionHandle->SessionID, &SessionGuidList [GuidListIndex].Guid, sizeof (GUID));  //  UuidCreate (JhiSessionHandle->SessionID);
  JhiSessionHandle->SessionInfo.flags = Flags;
  JhiSessionHandle->SessionInfo.state = JHI_SESSION_STATE_ACTIVE;
  JhiSessionHandle->InitBuffer = InitBuffer;

  InsertTailList (&JhiAppletHandle->SessionListHead, &JhiSessionHandle->Link);

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "SessionHandleCreate done\n"));
  return JhiSessionHandle;
}

/**
  Destroy session handle and free all allocated resource

  @param[in]  JhiSessionHandle    The session handle to be checked.

  @retval TRUE                    Destroy session handle succeed.
  @retval FALSE                   Destroy session handle failed.
**/
STATIC
BOOLEAN
SessionHandleDestroy (
  IN JHI_I_SESSION_HANDLE *JhiSessionHandle
  )
{
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "SessionHandleDestroy\n"));

  if (JhiSessionHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "SessionHandleDestroy fail, invalid parameter.\n"));
    return FALSE;
  }

  SessionGuidDestroy (JhiSessionHandle->GuidListIndex);
  RemoveEntryList (&JhiSessionHandle->Link);
  FreePool (JhiSessionHandle);

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "SessionHandleDestroy done\n"));
  return TRUE;
}

/**
  Check session handle is valid or not

  @param[in]  JhiSessionHandle    The session handle to be checked.

  @retval TRUE                    The session handle is valid.
  @retval FALSE                   The session handle is invalid.
**/
STATIC
BOOLEAN
SessionHandleValid (
  IN JHI_I_SESSION_HANDLE* JhiSessionHandle
  )
{
  LIST_ENTRY            *Link;
  JHI_I_APPLET_HANDLE *JhiAppletHandle;
  JHI_I_SESSION_HANDLE *Session;
  BOOLEAN Valid = FALSE;

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "SessionHandleValid\n"));

  if (JhiSessionHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "SessionHandleValid fail, invalid parameter.\n"));
    return FALSE;
  }

  if (JhiSessionHandle->Signature != JHI_SESSION_HANDLE_INSTANCE_SIGNATURE) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "SessionHandleValid fail, Signature mismatch(%08x != %08x)!\n",
                       JhiSessionHandle->Signature, JHI_SESSION_HANDLE_INSTANCE_SIGNATURE));
    return FALSE;
  }

  JhiAppletHandle = JhiSessionHandle->JhiAppletHandle;
  if (JhiAppletHandle == NULL) {
    return FALSE;
  }

  for (
        Link = GetFirstNode (&JhiAppletHandle->SessionListHead);
        !IsNull (&JhiAppletHandle->SessionListHead, Link);
        Link = GetNextNode (&JhiAppletHandle->SessionListHead, Link)) {
    Session = CR (
                Link,
                JHI_I_SESSION_HANDLE,
                Link,
                JHI_SESSION_HANDLE_INSTANCE_SIGNATURE
                );
    if (Session == JhiSessionHandle) {
      Valid = TRUE;
      break;
    }
  }

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "SessionHandleValid done, Valid: %x\n", Valid));
  return Valid;
}

/**
  Create applet handle

  @param[in]  JhiHandleInstance   The JHI internal handle.
  @param[in]  UcAppId             The AppId (Uppder case).
  @param[in]  SrcFile             The file path of applet

  @retval                         The pointer to applet handle.
**/
STATIC
JHI_I_APPLET_HANDLE *
AppletHandleCreate (
  IN JHI_I_HANDLE  *JhiHandleInstance,
  IN APPID_STR     UcAppId,
  IN CONST CHAR16  *SrcFile
  )
{
  JHI_I_APPLET_HANDLE *JhiAppletHandle;
  UINTN               FilepathStrSize;

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "AppletHandleCreate(%a)\n", (CHAR8 *) UcAppId));

  if (mAppHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "AppletHandleCreate fail, invalid parameter.\n"));
    return NULL;
  }

  JhiAppletHandle = (JHI_I_APPLET_HANDLE *) AllocateZeroPool (sizeof (JHI_I_APPLET_HANDLE));
  if (JhiAppletHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "AppletHandleCreate fail, insufficient memory for JHI_I_APPLET_HANDLE (size: %x)\n", sizeof (JHI_I_APPLET_HANDLE)));
    return NULL;
  }

  JhiAppletHandle->Signature = JHI_APPLET_HANDLE_INSTANCE_SIGNATURE;
  InitializeListHead (&JhiAppletHandle->SessionListHead);
  JhiAppletHandle->JhiHandleInstance = JhiHandleInstance;
  CopyMem (JhiAppletHandle->UcAppId, UcAppId, sizeof (APPID_STR));

  if (SrcFile != NULL) {
    FilepathStrSize = sizeof (CHAR16) * (StrLen (SrcFile) + 1);
    JhiAppletHandle->AppletFilepath = AllocateZeroPool (FilepathStrSize);
    if (JhiAppletHandle->AppletFilepath == NULL) {
      DEBUG_JHI_DRIVER ((DEBUG_ERROR, "AppletHandleCreate fail, insufficient memory for SrcFile(FilepathStrSize: %x).\n", FilepathStrSize));
      FreePool (JhiAppletHandle);
      return NULL;
    }
    CopyMem (JhiAppletHandle->AppletFilepath, SrcFile, FilepathStrSize);
  }

  InsertTailList (&mAppHandle->AppletHandleListHead, &JhiAppletHandle->Link);

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "AppletHandleCreate done\n"));
  return JhiAppletHandle;
}

/**
  Destroy applet handle

  @param[in]  JhiAppletHandle     The applet handle.

  @retval TRUE                    Destroy applet handle successfully.
  @retval FALSE                   Destroy applet handle failed.
**/
STATIC
BOOLEAN
AppletHandleDestroy (
  IN JHI_I_APPLET_HANDLE *JhiAppletHandle
  )
{
  JHI_I_SESSION_HANDLE *Session;

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "AppletHandleDestroy\n"));

  if (JhiAppletHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "AppletHandleDestroy fail, invalid parameter.\n"));
    return FALSE;
  }

  while (!IsListEmpty (&JhiAppletHandle->SessionListHead)) {
    Session = CR (
                JhiAppletHandle->SessionListHead.ForwardLink,
                JHI_I_SESSION_HANDLE,
                Link,
                JHI_SESSION_HANDLE_INSTANCE_SIGNATURE
                );
    SessionHandleDestroy (Session);
  }

  RemoveEntryList (&JhiAppletHandle->Link);
  if (JhiAppletHandle->AppletFilepath) {
    FreePool (JhiAppletHandle->AppletFilepath);
  }
  FreePool (JhiAppletHandle);

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "AppletHandleDestroy done\n"));
  return TRUE;
}

/**
  Find applet handle by AppId

  @param[in]  UcAppId             The AppId to be searched. (Uppder case)

  @retval                         The pointer to applet handle.
**/
STATIC
JHI_I_APPLET_HANDLE *
AppletHandleFind (
  IN APPID_STR UcAppId
  )
{
  LIST_ENTRY            *Link;
  JHI_I_APPLET_HANDLE *JhiAppletHandle;

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "AppletHandleFind(%a)\n", (CHAR8 *) UcAppId));

  if (mAppHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "AppletHandleFind fail, not initialized.\n"));
    return NULL;
  }

  for (
        Link = GetFirstNode (&mAppHandle->AppletHandleListHead);
        !IsNull (&mAppHandle->AppletHandleListHead, Link);
        Link = GetNextNode (&mAppHandle->AppletHandleListHead, Link)) {
    JhiAppletHandle = CR (
                        Link,
                        JHI_I_APPLET_HANDLE,
                        Link,
                        JHI_APPLET_HANDLE_INSTANCE_SIGNATURE
                        );
    DbgRawdataDump (JhiAppletHandle->UcAppId, sizeof (APPID_STR));
    if (CompareMem (JhiAppletHandle->UcAppId, UcAppId, sizeof (APPID_STR)) == 0) {
      DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "AppletHandleFind success\n"));
      return JhiAppletHandle;
    }
  }

  DEBUG_JHI_DRIVER ((DEBUG_ERROR, "AppletHandleFind fail\n"));
  return NULL;
}

/**
  Get total count of opend session for an applet

  @param[in]  JhiAppletHandle     The applet handle to counted.

  @retval                         The total count of session for this applet
**/
STATIC
UINTN
GetSessionCount (
  JHI_I_APPLET_HANDLE *JhiAppletHandle
  )
{
  LIST_ENTRY            *Link;
  UINTN Count;

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "GetSessionCount\n"));

  if (JhiAppletHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "GetAppletCount fail, JhiAppletHandle is NULL.\n"));
    return 0;
  }

  Count = 0;
  for (
        Link = GetFirstNode (&JhiAppletHandle->SessionListHead);
        !IsNull (&JhiAppletHandle->SessionListHead, Link);
        Link = GetNextNode (&JhiAppletHandle->SessionListHead, Link)) {

    Count++;
  }

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "GetSessionCount done, Count: %x\n", Count));
  return Count;
}

/**
  Get total count of installed applet.

  @retval                         The total count of applets.
**/
STATIC
UINTN
GetAppletCount (VOID)
{
  LIST_ENTRY            *Link;
  UINTN Count;

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "GetAppletCount\n"));

  if (mAppHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "GetAppletCount fail, mAppHandle is NULL.\n"));
    return 0;
  }

  Count = 0;
  for (
        Link = GetFirstNode (&mAppHandle->AppletHandleListHead);
        !IsNull (&mAppHandle->AppletHandleListHead, Link);
        Link = GetNextNode (&mAppHandle->AppletHandleListHead, Link)) {

    Count++;
  }

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "GetAppletCount done, Count: %x\n", Count));
  return Count;
}

#if EN_JHI_TEARDOWN
/**
  Clean up all allocated resource.
**/
STATIC
VOID
JhidCleanUp ()
{
  JHI_I_APPLET_HANDLE *JhiAppletHandle;
  JHI_I_SESSION_HANDLE *Session;
  JHI_RET              rc;

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "JhidCleanUp\n"));

  if (mAppHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidCleanUp fail, not initialized.\n"));
    return;
  }

  while (!IsListEmpty (&mAppHandle->AppletHandleListHead)) {
    JhiAppletHandle = CR (
                        mAppHandle->AppletHandleListHead.ForwardLink,
                        JHI_I_APPLET_HANDLE,
                        Link,
                        JHI_APPLET_HANDLE_INSTANCE_SIGNATURE
                        );
    if (JhiAppletHandle == NULL) {
      DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidCleanUp get NULL JhiAppletHandle.\n"));
      ASSERT (FALSE);
      continue;
    }

    while (!IsListEmpty (&JhiAppletHandle->SessionListHead)) {
      Session = CR (
                  JhiAppletHandle->SessionListHead.ForwardLink,
                  JHI_I_SESSION_HANDLE,
                  Link,
                  JHI_SESSION_HANDLE_INSTANCE_SIGNATURE
                  );
      rc = JhisCloseSession (Session);
      if (rc != JHI_SUCCESS) {
        DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhidCleanUp: session close fail, rc: %08x\n", rc));
      }
      SessionHandleDestroy (Session);
    }

    rc  = JhisUninstall (JhiAppletHandle);
    if (rc != JHI_SUCCESS) {
      DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhidCleanUp: applet Uninstall fail, rc: %08x\n", rc));
    }

    RemoveEntryList (&JhiAppletHandle->Link);
    if (JhiAppletHandle->AppletFilepath) {
      FreePool (JhiAppletHandle->AppletFilepath);
    }

    FreePool (JhiAppletHandle);
  }
}
#endif

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
  )
{
  JHI_RET         rc;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidInitialize\n"));
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "PS: Context and Flags will be ignored\n"));
  ///
  /// Check for input parameters
  ///
  if (ppHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidInitialize fail, parameter invalid!\n"));
    return JHI_INVALID_PARAMS;
  }

  rc = JHI_INTERNAL_ERROR;

  ///
  /// Check ReferenceCount. Do not perform init if we already initialized it before.
  ///
  if (mAppHandle != NULL) {
    mAppHandle->ReferenceCount++;
    rc = JHI_SUCCESS;
    DEBUG_JHI_DRIVER ((DEBUG_INFO, "Handle already created, return successful status. ReferenceCount: %x\n",
                       mAppHandle->ReferenceCount));
    goto done;
  }

  mAppHandle = (JHI_I_HANDLE *) AllocateZeroPool (sizeof (JHI_I_HANDLE));
  if (mAppHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidInitialize fail, insufficient memory.\n"));
    return JHI_INTERNAL_ERROR;
  }

  mAppHandle->Signature = JHI_HANDLE_INSTANCE_SIGNATURE;
  mAppHandle->State = INITALIZED;
  mAppHandle->ReferenceCount = 1;
  InitializeListHead (&mAppHandle->AppletHandleListHead);

  rc = JhisInit (mAppHandle);
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "JhisInit rc: %x\n", rc));

done:
  *ppHandle = mAppHandle;

  if (rc != JHI_SUCCESS) {
    if (mAppHandle != NULL) {
      DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidInitialize failed, releasing allocated appHandle\n"));
      FreePool (mAppHandle);
      mAppHandle = NULL;
    }
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidInitialize done, ReferenceCount: %x, rc: %x\n", mAppHandle->ReferenceCount, rc));
  return rc;
}

/**
  De-initialize JHI API core.

  @param[in]  Handle              The JHI handle.

  @retval JHI_SUCCESS             De-initialize JHI API core successfully.
  @retval others                  Error status. (Please refer to Jhi.h)
**/
JHI_RET
JhidDeinit (
  IN JHI_HANDLE   Handle
  )
{
  JHI_RET         rc;

  rc = JHI_INTERNAL_ERROR;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidDeinit\n"));

  ///
  /// Validate the JHI Handle
  ///
  if (ValidateJHIhandle (Handle) != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JHI handle is invalid.\n"));
    return JHI_INVALID_HANDLE;
  }
  ASSERT (Handle == mAppHandle);

  mAppHandle->ReferenceCount--;
  DEBUG_JHI_DRIVER ((DEBUG_INFO, "ReferenceCount: %x\n", mAppHandle->ReferenceCount));

  ///
  /// Check ReferenceCount. Do not perform deinit if someone still refers to this JHI_HANDLE
  ///
  if (mAppHandle->ReferenceCount > 0) {
    rc = JHI_SUCCESS;
    DEBUG_JHI_DRIVER ((DEBUG_INFO, "Reference count is not zero, return successful status. ReferenceCount: %x\n",
                       mAppHandle->ReferenceCount));
    goto done;
  }

#if EN_JHI_TEARDOWN
  JhidCleanUp ();
#endif

  rc = JhisDeInit (mAppHandle);
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "JhisDeInit rc: %x\n", rc));

  FreePool (mAppHandle);
  mAppHandle = NULL;

  rc = JHI_SUCCESS;

done:

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidDeinit done, rc: %x\n", rc));
  return rc;
}

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
  )
{
  EFI_STATUS          Status;
  JHI_RET             rc;
  EFI_FILE            *FileHandle;
  UINT8               *FileBlob;
  UINTN               FileSize;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidInstall2 (JHI_INSTALL_FILE) (%a, %s)\n", AppId, SrcFile));

  rc = JHI_INTERNAL_ERROR;

  ASSERT (SrcFile);
  if (SrcFile == NULL || StrLen (SrcFile) > FILENAME_MAX) {
    return JHI_INVALID_INSTALL_FILE;
  }

  Status = FileOpen ((CHAR16 *) SrcFile, &FileHandle);
  if (EFI_ERROR (Status)) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhisInstall fail, open file error, Status: %r\n", Status));
    rc = JHI_INVALID_INSTALL_FILE;
    goto done;
  }

  Status = FileRead (FileHandle, (VOID **)&FileBlob, &FileSize);
  if (EFI_ERROR (Status)) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhisInstall fail, read file error, Status: %r\n", Status));
    rc = JHI_READ_FROM_FILE_FAILED;
    FileClose (FileHandle);
    goto done;
  }

  rc = JhidInstall3 (Handle, AppId, FileBlob, (UINT32) FileSize);
  if (JHI_SUCCESS != rc) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhidInstall3 fail\n"));
    FileClose (FileHandle);
  }

done:
  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidInstall2 (JHI_INSTALL_FILE) done, rc: %x\n", rc));
  return rc;
}


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
  )
{
  JHI_RET             rc;
  APPID_STR           UcAppId;
  JHI_I_APPLET_HANDLE *JhiAppletHandle;
  UINTN               AppletCount;
  UINTN               MaxAppletCount;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidInstall3 (JHI_INSTALL_CONTENT)(%a) AppletBlob: %x, AppletLength: %x\n", AppId, AppletBlob, AppletLength));

  rc = JHI_INTERNAL_ERROR;

  ///
  /// Validate the JHI Handle
  ///
  if (ValidateJHIhandle (Handle) != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JHI handle is invalid.\n"));
    return JHI_INVALID_HANDLE;
  }

  if (!(
         AppId && (AsciiStrLen (AppId) == APPID_STR_LENGTH) &&
         (ValidateUUID (AppId, UcAppId) == JHI_SUCCESS)
         )) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Either Appname is bad or illegal length.\n"));
    return JHI_INVALID_APPLET_GUID;
  }

  if (AppletBlob == NULL || AppletLength == 0) {
    return JHI_INVALID_INSTALL_FILE;
  }

  JhiAppletHandle = AppletHandleFind (UcAppId);
  if (JhiAppletHandle != NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "The UcAppId has been used, reject it\n"));
    return JHI_INVALID_APPLET_GUID;
  }

  ///
  /// Check for applet count
  ///
  AppletCount = GetAppletCount ();
  MaxAppletCount = GetPchMaxMeAppletCount();
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "Check for AppletCount: %x (MaxAppletCount: %x for PlatformId(%x))\n",
                             AppletCount, MaxAppletCount, mAppHandle->VersionInfo.PlatformId));
  if (AppletCount == MaxAppletCount) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "AppletCount reaches max allowe count\n"));
    return JHI_MAX_INSTALLED_APPLETS_REACHED;
  }

  JhiAppletHandle = AppletHandleCreate ((JHI_I_HANDLE *) Handle, UcAppId, NULL);
  if (JhiAppletHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Applet Handle create fail\n"));
    return JHI_INTERNAL_ERROR;
  }

  JhiAppletHandle->FileBlob = (UINT8 *) AppletBlob;
  JhiAppletHandle->FileSize = AppletLength;

  rc = JhisInstall (JhiAppletHandle);
  if (rc != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhisInstall fail\n"));
    AppletHandleDestroy (JhiAppletHandle);
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidInstall3 (JHI_INSTALL_CONTENT) done, rc: %x\n", rc));
  return rc;
}

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
  )
{
  JHI_RET             rc;
  APPID_STR           UcAppId;
  JHI_I_APPLET_HANDLE *JhiAppletHandle;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidUninstall\n"));

  ///
  /// Validate the JHI Handle
  ///
  if (ValidateJHIhandle (Handle) != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JHI handle is invalid.\n"));
    return JHI_INVALID_HANDLE;
  }

  if ( !(AppId && (AsciiStrLen (AppId) == APPID_STR_LENGTH) &&
         (ValidateUUID (AppId, UcAppId) == JHI_SUCCESS))) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Either Appname is bad or illegal length ..\n"));
    return JHI_INVALID_APPLET_GUID;
  }

  JhiAppletHandle = AppletHandleFind (UcAppId);
  if (JhiAppletHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Applet Handle doesn't exist\n"));
    return JHI_APPLET_NOT_INSTALLED;
  }

  rc  = JhisUninstall (JhiAppletHandle);

  if (JhiAppletHandle->AppletFilepath != NULL) {
    //
    // The applet file opened by JHI_Install2 (JHI_INSTALL_FILE) should close here.
    //
    if (JhiAppletHandle->FileBlob != NULL) {
      FreePool (JhiAppletHandle->FileBlob);
    }

    if (JhiAppletHandle->FileHandle != NULL) {
      FileClose (JhiAppletHandle->FileHandle);
    }
  }

  JhiAppletHandle->FileHandle = NULL;
  JhiAppletHandle->FileBlob = NULL;
  JhiAppletHandle->FileSize = 0;

  AppletHandleDestroy (JhiAppletHandle);

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidUninstall done, rc: %x\n", rc));
  return rc;
}

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
  )
{
  JHI_RET                  rc;
  APPID_STR                UcAppId;
  DATA_BUFFER              *pTxBuf;
  DATA_BUFFER              *pRxBuf;
  JHI_I_APPLET_HANDLE      *JhiAppletHandle;
  JVM_COMM_BUFFER          CommBuffer;
  UINTN                    SessionCount;
  UINTN                    BufferSize;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidGetAppletProperty(%a)\n", AppId));

  ZeroMem (&CommBuffer, sizeof (JVM_COMM_BUFFER));
  pTxBuf = CommBuffer.TxBuf;
  pRxBuf = CommBuffer.RxBuf;

  rc = JHI_INTERNAL_ERROR;

  ///
  /// Validate the JHI Handle
  ///
  if (ValidateJHIhandle (Handle) != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JHI handle is invalid.\n"));
    return JHI_INVALID_HANDLE;
  }

  if (!(AppId && (AsciiStrLen (AppId) == APPID_STR_LENGTH) &&
       (ValidateUUID (AppId, UcAppId) == JHI_SUCCESS))) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Either Appname is bad or illegal length ..\n"));
    return JHI_INVALID_APPLET_GUID;
  }

  if (pCommBuffer == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidGetAppletProperty fail, invalid parameters.\n"));
    return JHI_INVALID_COMM_BUFFER;
  }

  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, " TxBuf: (buffer: %x, length: %x)\n",
                             pCommBuffer->TxBuf->buffer, pCommBuffer->TxBuf->length));
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, " RxBuf: (buffer: %x, length: %x)\n",
                             pCommBuffer->RxBuf->buffer, pCommBuffer->RxBuf->length));

  if (((pCommBuffer->TxBuf->length > 0) && (pCommBuffer->TxBuf->buffer == NULL)) ||
      ((pCommBuffer->RxBuf->length > 0) && (pCommBuffer->RxBuf->buffer == NULL))) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidGetAppletProperty fail, invalid parameters in pCommBuffer.\n"));
    return JHI_INVALID_COMM_BUFFER;
  }

  if (pCommBuffer->TxBuf->length == 0) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidGetAppletProperty fail, invalid parameters in TxBuff length.\n"));
    return JHI_APPLET_PROPERTY_NOT_SUPPORTED;
  }

  if ((pCommBuffer->TxBuf->length > JHI_BUFFER_MAX / sizeof (CHAR16)) ||
      (pCommBuffer->RxBuf->length > JHI_BUFFER_MAX / sizeof (CHAR16))) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Buffer sent exceeds JHI_BUFFER_MAX limit\n"));
    return JHI_INVALID_BUFFER_SIZE;
  }

  ///
  /// Convert from Unicode to ANSI string
  ///
  pTxBuf->length = (pCommBuffer->TxBuf->length);
  BufferSize = pTxBuf->length + 1;
  pTxBuf->buffer = AllocateZeroPool (BufferSize);
  if (pTxBuf->buffer == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "Failed to allocate buffer\n"));
    rc = JHI_INSUFFICIENT_BUFFER;
    goto cleanup;
  }

  UnicodeStrToAsciiStrS ((UINT16 *) pCommBuffer->TxBuf->buffer, (CHAR8 *) pTxBuf->buffer, BufferSize);
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "TxBuf: Unicode2Ascii: Unicode: %s -> Ascii: %a\n",
                             (CHAR16 *) pCommBuffer->TxBuf->buffer, (CHAR8 *) pTxBuf->buffer));

  pRxBuf->length = pCommBuffer->RxBuf->length;
  if (pRxBuf->length != 0) {
    pRxBuf->buffer = AllocateZeroPool (pRxBuf->length + 1);
    if (NULL == pRxBuf->buffer) {
      DEBUG_JHI_DRIVER ((DEBUG_WARN, "Failed to allocate buffer\n"));
      rc = JHI_INSUFFICIENT_BUFFER;
      goto cleanup;
    }
  }

  JhiAppletHandle = AppletHandleFind (UcAppId);
  if (JhiAppletHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Applet Handle doesn't exist\n"));
    return JHI_APPLET_NOT_INSTALLED;
  }

  SessionCount = GetSessionCount (JhiAppletHandle);
  rc = JhisGetAppletProperty (JhiAppletHandle, &CommBuffer, SessionCount);

  pCommBuffer->RxBuf->length = pRxBuf->length;
  if (rc != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhidGetAppletProperty fail, JhisGetAppletProperty error, rc: %x\n", rc));
  } else {
    ///
    /// Convert from ANSI to Unicode string
    ///
    if (pRxBuf->buffer != NULL) {
      ((CHAR8 *) pRxBuf->buffer) [pRxBuf->length] = 0;
      AsciiStrToUnicodeStrS ((CHAR8 *) pRxBuf->buffer, (CHAR16 *) pCommBuffer->RxBuf->buffer, (pCommBuffer->RxBuf->length + 1));
      DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "RxBuf: Ascii2Unicode: Ascii: %a -> Unicode: %s\n",
                                 (CHAR8 *) pRxBuf->buffer, (CHAR16 *) pCommBuffer->RxBuf->buffer));
    }
  }

cleanup:
  if (NULL != pTxBuf->buffer) {
    FreePool (pTxBuf->buffer);
  }
  if (NULL != pRxBuf->buffer) {
    FreePool (pRxBuf->buffer);
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidGetAppletProperty done, rc: %x\n", rc));
  return rc;
}

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
  )
{
  JHI_RET                 rc;
  APPID_STR               UcAppId;
  DATA_BUFFER             TmpDataBuffer;
  JHI_I_APPLET_HANDLE     *JhiAppletHandle;
  JHI_I_SESSION_HANDLE    *JhiSessionHandle;
  UINTN                   SessionCount;
  UINTN                   MaxSessionCount;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidCreateSession\n"));

  rc = JHI_INTERNAL_ERROR;

  ///
  /// Validate the JHI Handle
  ///
  if (ValidateJHIhandle (Handle) != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JHI handle is invalid.\n"));
    return JHI_INVALID_HANDLE;
  }

  if (pSessionHandle == NULL) {
    return JHI_INVALID_SESSION_HANDLE;
  }

  // allow passing NULL buffer data
  if (InitBuffer == NULL) {
    TmpDataBuffer.buffer = NULL;
    TmpDataBuffer.length = 0;
    InitBuffer = &TmpDataBuffer;
  }

  if ( !(AppId && (AsciiStrLen (AppId) == APPID_STR_LENGTH) &&
         (ValidateUUID (AppId, UcAppId) == JHI_SUCCESS))) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Either Appname is bad or illegal length ..\n"));
    return JHI_INVALID_APPLET_GUID;
  }

  // Validate the incoming values
  if ((InitBuffer->length > 0) && (InitBuffer->buffer == NULL)) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Illegal argument supplied.. Check the input values..\n"));
    return JHI_INVALID_INIT_BUFFER;
  }

  if (InitBuffer->length > JHI_BUFFER_MAX) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "init buffer exceeds JHI_BUFFER_MAX limit\n"));
    return JHI_INVALID_BUFFER_SIZE;
  }

  JhiAppletHandle = AppletHandleFind (UcAppId);
  if (JhiAppletHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Applet Handle doesn't exist\n"));
    return JHI_APPLET_NOT_INSTALLED;
  }

  ///
  /// Check for session count
  ///
  SessionCount = GetSessionCount (JhiAppletHandle);
  MaxSessionCount = GetPchMaxMeSessionCount();
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "Check for SessionCount: %x (MaxSessionCount: %x for PlatformId(%x))\n",
                             SessionCount, MaxSessionCount, mAppHandle->VersionInfo.PlatformId));
  if (SessionCount == MaxSessionCount) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "SessionCount reaches max allowe count\n"));
    return JHI_MAX_SESSIONS_REACHED;
  }

  JhiSessionHandle = SessionHandleCreate (JhiAppletHandle, Flags, InitBuffer);
  if (JhiSessionHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Session Handle create fail\n"));
    return JHI_INTERNAL_ERROR;
  }

  rc = JhisCreateSession (JhiSessionHandle);
  if (JHI_SUCCESS != rc) {
    SessionHandleDestroy (JhiSessionHandle);
  } else {
    *pSessionHandle = JhiSessionHandle;
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidCreateSession done, rc: %x\n", rc));
  return rc;
}

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
  )
{
  JHI_RET               rc;
  JHI_I_SESSION_HANDLE  *JhiSessionHandle;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidCloseSession\n"));

  ///
  /// Validate the JHI Handle
  ///
  if (ValidateJHIhandle (Handle) != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JHI handle is invalid.\n"));
    return JHI_INVALID_HANDLE;
  }

  if (pSessionHandle == NULL) {
    return JHI_INVALID_SESSION_HANDLE;
  }

  JhiSessionHandle = (JHI_I_SESSION_HANDLE*) *pSessionHandle;
  if (!SessionHandleValid (JhiSessionHandle)) {
    rc = JHI_INVALID_SESSION_HANDLE;
    goto done;
  }

  // call for close session at the service
  rc  = JhisCloseSession (JhiSessionHandle);
  // JHI may return JHI_INVALID_SESSION_HANDLE which is expected.
  if (rc == JHI_INVALID_SESSION_HANDLE) {
    rc = JHI_SUCCESS;
  }

  // remove the session Handle form the list.
  if (SessionHandleDestroy (JhiSessionHandle)) {
    *pSessionHandle = NULL;
  }

done:
  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidCloseSession done, rc: %x\n", rc));
  return rc;
}

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
  )
{
  APPID_STR           UcAppId;
  JHI_I_APPLET_HANDLE *JhiAppletHandle;
  UINTN               Count;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidGetSessionsCount\n"));

  ///
  /// Validate the JHI Handle
  ///
  if (ValidateJHIhandle (Handle) != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JHI handle is invalid.\n"));
    return JHI_INVALID_HANDLE;
  }

  if (!pSessionsCount) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Invalid parameter for pSessionsCount\n"));
    return JHI_INVALID_PARAMS;
  }

  if ( !(AppId && (AsciiStrLen (AppId) == APPID_STR_LENGTH) &&
         (ValidateUUID (AppId, UcAppId) == JHI_SUCCESS))) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Either Appname is bad or illegal length ..\n"));
    return JHI_INVALID_APPLET_GUID;
  }

  JhiAppletHandle = AppletHandleFind (UcAppId);
  if (JhiAppletHandle == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Applet Handle doesn't exist\n"));
    return JHI_APPLET_NOT_INSTALLED;
  }

  Count = GetSessionCount (JhiAppletHandle);
  *pSessionsCount = (UINT32) Count;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidGetSessionsCount done, count: %x\n", *pSessionsCount));
  return JHI_SUCCESS;
}

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
  )
{
  JHI_I_SESSION_HANDLE  *JhiSessionHandle;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidGetSessionInfo\n"));

  ///
  /// Validate the JHI Handle
  ///
  if (ValidateJHIhandle (Handle) != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JHI handle is invalid.\n"));
    return JHI_INVALID_HANDLE;
  }

  if (SessionInfo == NULL) {
    return JHI_INVALID_SESSION_HANDLE;
  }

  JhiSessionHandle = (JHI_I_SESSION_HANDLE*) SessionHandle;

  if (!SessionHandleValid (JhiSessionHandle)) {
    return JHI_INVALID_SESSION_HANDLE;
  }

  if (!SessionInfo) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "Invalid parameter for SessionInfo\n"));
    return JHI_INVALID_PARAMS;
  }

  CopyMem (SessionInfo, &JhiSessionHandle->SessionInfo, sizeof (JHI_SESSION_INFO));

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidGetSessionInfo done\n"));
  return JHI_SUCCESS;
}

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
  )
{
  JHI_RET               rc;
  JHI_I_HANDLE          *JhiHandleInstance;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidGetVersionInfo\n"));

  ///
  /// Validate the JHI Handle
  ///
  if (ValidateJHIhandle (Handle) != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JHI handle is invalid.\n"));
    rc = JHI_INVALID_HANDLE;
    goto done;
  }

  if (pVersionInfo == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_WARN, "JhidGetVersionInfo fail, invalid parameters.\n"));
    rc = JHI_INVALID_PARAMS;
    goto done;
  }

  JhiHandleInstance = (JHI_I_HANDLE *) Handle;
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "JHI_VERSION_INFO (Size: %x)\n", sizeof (JHI_VERSION_INFO)));
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, " JhiVersion:  %a\n",   JhiHandleInstance->VersionInfo.JhiVersion));
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, " FwVersion:   %a\n",   JhiHandleInstance->VersionInfo.FwVersion));
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, " CommType :   %x\n",   JhiHandleInstance->VersionInfo.CommType));
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, " PlatformId:  %x\n",   JhiHandleInstance->VersionInfo.PlatformId));
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, " VmType:      %x\n",   JhiHandleInstance->VersionInfo.VmType));
  DEBUG_JHI_DRIVER_VERBOSE ((DEBUG_INFO, "\n"));

  CopyMem (pVersionInfo, &JhiHandleInstance->VersionInfo, sizeof (JHI_VERSION_INFO));
  rc = JHI_SUCCESS;

done:
  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidGetVersionInfo done, rc: %x\n", rc));
  return rc;
}

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
  )
{
  JHI_RET                 rc;
  JHI_I_SESSION_HANDLE    *JhiSessionHandle;
  INT32                   ResponseCodeTemp;
  INT32                   *pResponseCode;

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidSendAndRecv\n"));

  rc = JHI_SUCCESS;

  ///
  /// Validate the JHI Handle
  ///
  if (ValidateJHIhandle (Handle) != JHI_SUCCESS) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JHI handle is invalid.\n"));
    return JHI_INVALID_HANDLE;
  }

  if (pCommBuffer == NULL) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidSendAndRecv fail, illegal argument for JVM_COMM_BUFFER.\n"));
    return JHI_INVALID_COMM_BUFFER;
  }

  //
  // Validate the incoming values
  //
  if (((pCommBuffer->TxBuf->length > 0) && (pCommBuffer->TxBuf->buffer == NULL)) ||
      ((pCommBuffer->RxBuf->length > 0) && (pCommBuffer->RxBuf->buffer == NULL))) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidSendAndRecv fail, illegal arguments inside of JVM_COMM_BUFFER.\n"));
    return JHI_INVALID_COMM_BUFFER;
  }

  if ((pCommBuffer->TxBuf->length > JHI_BUFFER_MAX) || (pCommBuffer->RxBuf->length > JHI_BUFFER_MAX)) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidSendAndRecv fail, buffer sent exceeds JHI_BUFFER_MAX limit.\n"));
    return JHI_INVALID_BUFFER_SIZE;
  }

  JhiSessionHandle = (JHI_I_SESSION_HANDLE*) SessionHandle;

  if (!SessionHandleValid (JhiSessionHandle)) {
    DEBUG_JHI_DRIVER ((DEBUG_ERROR, "JhidSendAndRecv fail, session handle is invalid.\n"));
    return JHI_INVALID_SESSION_HANDLE;
  }

  if (ResponseCode == NULL) {
    pResponseCode = &ResponseCodeTemp;
  } else {
    pResponseCode = ResponseCode;
  }

  rc = JhisSendAndRecv (
         JhiSessionHandle,
         nCommandId,
         pCommBuffer,
         pResponseCode
         );
  ///
  /// If the session crashed we remove its allocated resources by calling JhidCloseSession
  ///
  if (rc == JHI_APPLET_FATAL || rc == JHI_INVALID_SESSION_HANDLE) {
    JhidCloseSession (Handle, &SessionHandle);
  }

  DEBUG_JHI_DRIVER ((DEBUG_INFO, "JhidSendAndRecv done, rc: %x\n", rc));
  return rc;
}



/** @file
  Definition for SysFwUpdateProgress Variable and Capsule backup filenames
  used for Seamless Recovery support

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

@par Specification
**/

#ifndef __SYSTEM_FIRMWARE_UPDATE_PROGRESS_H__
#define __SYSTEM_FIRMWARE_UPDATE_PROGRESS_H__

#define SYSFW_UPDATE_PROGRESS_GUID \
  { \
    0xf92b8157, 0xc647, 0x44d7, { 0x8d, 0x94, 0x81, 0x7d, 0x18, 0xa2, 0x76, 0xdc } \
  }

#define SYSFW_UPDATE_PROGRESS_VARIABLE_NAME              L"SysFwUpdateProgress"
#define SYSFW_UPDATE_CAPSULE_DIGEST_VARIABLE_NAME        L"CapDigest"
#define SYSFW_UPDATE_CURRENT_BIOS_DIGEST_VARIABLE_NAME   L"CurBiosDigest"
#define SYSFW_UPDATE_NEW_BIOS_DIGEST_VARIABLE_NAME       L"NewBiosDigest"

#define SYSFW_UPDATE_CURRENT_FVADV_BACKUP_FILE_NAME      L"FvAdv.fv"
#define SYSFW_UPDATE_NEW_FVADV_BACKUP_FILE_NAME          L"FvAdvN.fv"
#define SYSFW_UPDATE_CURRENT_FVUEFI_BACKUP_FILE_NAME     L"FvUEFI.fv"
#define SYSFW_UPDATE_NEW_FVUEFI_BACKUP_FILE_NAME         L"FvUEFIN.fv"
#define SYSFW_UPDATE_CURRENT_FVOS_BACKUP_FILE_NAME       L"FvOS.fv"
#define SYSFW_UPDATE_NEW_FVOS_BACKUP_FILE_NAME           L"FvOSN.fv"
#define SYSFW_UPDATE_CAPSULE_BACKUP_FILE_NAME            L"Capsule.cap"
#define SYSFW_UPDATE_WINDOWS_UX_CAPSULE_FILE_NAME        L"UxCap.cap"
#define SYSBIOS_UPDATE_CAPSULE_BACKUP_FILE_NAMEN         L"BiosBkN.cap"
#define SYSBIOS_UPDATE_CAPSULE_BACKUP_FILE_NAMEN1        L"BiosBkN1.cap"
#define SYSBIOS_UPDATE_CAPSULE_DIGEST_VARIABLE_NAMEN     L"BiosBkDigestN"
#define SYSBIOS_UPDATE_CAPSULE_DIGEST_VARIABLE_NAMEN1    L"BiosBkDigestN1"
#define SYSFW_UPDATE_CURRENT_BIOS_FILE_NAME              L"CurBios.fd"
#define SYSFW_UPDATE_NEW_BIOS_FILE_NAME                  L"NewBios.fd"

typedef enum {
  NotStarted              = 0,
  UpdatingMe              = 1,
  UpdatingIshPdt          = 2,
  UpdatingBios            = 3,
  UpdatingTypeMax
} SYSTEM_FIRMWARE_COMPONENT;

typedef enum {
  BiosIbbR    = 0,
  BiosIbb     = 1,
  BiosObb     = 2,
  BiosMax
} BIOS_UPDATE_PROGRESS;

typedef enum {
  BiosUfsIbbR  = 0,
  BiosUfsIbb   = 1,
  BiosUfsBpdt1 = 2,
  BiosUfsObb   = 3,
  BiosUfsBpdt2 = 4,
  BiosMaxUfs
} BIOS_UPDATE_PROGRESS_UFS;

#pragma pack(1)

typedef struct {
  SYSTEM_FIRMWARE_COMPONENT  Component;
  UINT32                     Progress;
} SYSTEM_FIRMWARE_UPDATE_PROGRESS;

#pragma pack()

extern EFI_GUID gSysFwUpdateProgressGuid;

#endif

/** @file
  This SMM driver will handle SA relevant late initialization

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DxeServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/SaPlatformLib.h>
#include <Protocol/SmmIoTrapDispatch2.h>
#include "SaLateInitSmm.h"
#include <SaRegs.h>
#include <CpuRegs.h>
#include <Library/PciSegmentLib.h>
#include <CpuDataStruct.h>
#include <CpuPcieHob.h>
#include <Library/CpuPcieLib.h>
#include <Protocol/SaIotrapSmi.h>
#include <PchPcieRpConfig.h>

typedef enum {
  EnumSaSmiCallbackForMaxPayLoad,
  EnumSaSmiCallbackForSaSaveRestore,
  EnumSaSmiCallbackForLateInit,
  EnumSaSmiCallbackForS3resume,
  EnumSaSmiCallbackMax
} SMI_OPERATION;

GLOBAL_REMOVE_IF_UNREFERENCED UINT8                           mSaSmiCallbackPhase      = EnumSaSmiCallbackForMaxPayLoad;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL        *mPchIoTrap;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_SMM_SX_DISPATCH2_PROTOCOL             *mSxDispatch;

/**
  A SMI callback to do SA relevant late initialization

  @param[in] DispatchHandle  - The handle of this callback, obtained when registering
  @param[in] DispatchContext - Pointer to the EFI_SMM_IO_TRAP_DISPATCH_CALLBACK_CONTEXT
**/
VOID
EFIAPI
SaIoTrapSmiCallback (
  IN  EFI_HANDLE                            DispatchHandle,
  IN CONST VOID                             *CallbackContext,
  IN OUT VOID                               *CommBuffer,
  IN OUT UINTN                              *CommBufferSize
  )
{

  if (mSaSmiCallbackPhase == EnumSaSmiCallbackMax) {
    return;
  }
  if (mSaSmiCallbackPhase == EnumSaSmiCallbackForMaxPayLoad) {
    //CpuPcieEnumCallback (); // @TODO :This is old code, remove this after making sure that Maxpayload, TC/VC mapping and Common clock programming are taken care
    ///
    /// Switch to next phase
    ///
    mSaSmiCallbackPhase = EnumSaSmiCallbackForSaSaveRestore;
  } else if (mSaSmiCallbackPhase == EnumSaSmiCallbackForSaSaveRestore) {
    ///
    /// Save platform registers including IGFX BAR & COMMAND registers and PAM
    ///
    SaSaveRestorePlatform (TRUE);
    ///
    /// Switch to next phase
    ///
    mSaSmiCallbackPhase = EnumSaSmiCallbackForLateInit;
  } else if (mSaSmiCallbackPhase == EnumSaSmiCallbackForLateInit) {
    ///
    /// Switch to next phase
    ///
    mSaSmiCallbackPhase = EnumSaSmiCallbackForS3resume;
  } else if (mSaSmiCallbackPhase == EnumSaSmiCallbackForS3resume) {
    ///
    /// Expected to execute in end of S3 resume flow
    ///
    SaS3ResumeCallback ();
  }
}

/**
  Force keep GT into RC6 state

  @retval EFI_SUCCESS    - GT RC6 MSR programmed successfully
**/
EFI_STATUS
EFIAPI
ForceGtRc6 (
  VOID
  )
{
  MSR_REGISTER  MsrGtSleepCmdSts;
  ///
  /// Set bit 0 in MSR_GT_SLEEP_CMDSTS (118h) to force keep GT RC6.
  ///
  MsrGtSleepCmdSts.Qword = AsmReadMsr64 (MSR_GT_SLEEP_CMDSTS);
  MsrGtSleepCmdSts.Dwords.Low |= B_MSR_MAILBOX_INTERNAL_PCODE_KEEP_GT_RC6;
  AsmWriteMsr64 (MSR_GT_SLEEP_CMDSTS, MsrGtSleepCmdSts.Qword);

  return EFI_SUCCESS;
}

/**
  Initializes the SA SMM handler

  @param[in] ImageHandle - The image handle of Wake On Lan driver
  @param[in] SystemTable - The standard EFI system table

  @retval EFI_SUCCESS    - SA SMM handler was installed or not necessary
  @retval EFI_NOT_FOUND  - Fail to register SMI callback or required protocol/hob missing.
**/
EFI_STATUS
EFIAPI
SaLateInitSmmEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  return EFI_SUCCESS;
}

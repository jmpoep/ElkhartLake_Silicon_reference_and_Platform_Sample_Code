/** @file
  PEI Multi-Board Initialization in Pre-Memory PEI Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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

@par Specification Reference:
**/

#include <PiPei.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/BoardInitLib.h>
#include <Library/MultiBoardInitSupportLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugLib.h>
#include <Library/BoardConfigLib.h>
#include <Library/EcMiscLib.h>
#include <PlatformBoardId.h>
#include <Library/SiliconInitLib.h>
#include <Register/CoreMsrcommon.h>

EFI_STATUS
EFIAPI
EhlBoardDetect (
  VOID
  );

EFI_STATUS
EFIAPI
EhlMultiBoardDetect (
  VOID
  );

EFI_BOOT_MODE
EFIAPI
EhlBoardBootModeDetect (
  VOID
  );

EFI_STATUS
EFIAPI
EhlBoardDebugInit (
  VOID
  );

EFI_STATUS
EFIAPI
EhlBoardInitBeforeMemoryInit (
  VOID
  );

EFI_STATUS
EFIAPI
EhlBoardInitAfterMemoryInit (
  VOID
  );

BOARD_DETECT_FUNC  mEhlBoardDetectFunc = {
  EhlMultiBoardDetect
};

BOARD_PRE_MEM_INIT_FUNC  mEhlBoardPreMemInitFunc = {
  EhlBoardDebugInit,
  EhlBoardBootModeDetect,
  EhlBoardInitBeforeMemoryInit,
  EhlBoardInitAfterMemoryInit,
  NULL, // BoardInitBeforeTempRamExit
  NULL, // BoardInitAfterTempRamExit
};

EFI_STATUS
EFIAPI
EhlMultiBoardDetect (
  VOID
  )
{
  EFI_STATUS    Status;
  UINT32 NumberOfActiveCores;

  Status = EFI_SUCCESS;

  DEBUG ((DEBUG_INFO, "EhlMultiBoardDetect\n"));

  EarlySiliconInit ();

  NumberOfActiveCores   = (((UINT32) AsmReadMsr64 (MSR_CORE_THREAD_COUNT)) >> 16) & 0xFFFF;

  // Update Memory Size for 2 core to avoid reset on first boot
  if (NumberOfActiveCores == 2) {
    PcdSet32S (PcdBoardAdjustEfiAcpiReclaimMemorySize, (UINT32) 0);
    PcdSet32S (PcdBoardAdjustEfiAcpiNvsMemorySize, (UINT32) -20);
    PcdSet32S (PcdBoardAdjustEfiReservedMemorySize, (UINT32) 0);
    PcdSet32S (PcdBoardAdjustEfiRtDataMemorySize, (UINT32) 0);
    PcdSet32S (PcdBoardAdjustEfiRtCodeMemorySize, (UINT32) 0);
  }

#if FixedPcdGetBool(PcdEcEnable) == 1
  Status = WakeUpEc ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Wake Up Ec Fail. Status = %r \n", Status));
  }
#endif
  EhlBoardDetect ();

  if ((LibPcdGetSku () == BoardIdEhlLp4xType4Erb) ||
      (LibPcdGetSku () == BoardIdEhlLp4xType4Rvp1) ||
      (LibPcdGetSku () == BoardIdEhlDdr4Type3Rvp2) ||
      (LibPcdGetSku () == BoardIdEhlLp4xType3Crb) ||
      (LibPcdGetSku () == BoardIdJslLp4xType4Rvp1) ||
      (LibPcdGetSku () == BoardIdJslLp4xErb)) {
    RegisterBoardPreMemInit (&mEhlBoardPreMemInitFunc);
  } else {
    DEBUG ((DEBUG_WARN,"Not a valid ElkhartLake Board\n"));
  }
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
PeiEhlMultiBoardInitPreMemLibConstructor (
  VOID
  )
{
  return RegisterBoardDetect (&mEhlBoardDetectFunc);
}

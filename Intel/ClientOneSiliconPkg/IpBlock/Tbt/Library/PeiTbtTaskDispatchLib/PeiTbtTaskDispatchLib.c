/**@file
  PEI TBT Task Dispatch library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

#include <Library/PeiTbtTaskDispatchLib.h>

/**
  Covert the current EFI_BOOT_MODE to TBT_BOOT_MODE

  @retval  TBT_BOOT_MODE                Mode to be used to execute corresponding TBT tasks.
**/
TBT_BOOT_MODE
TbtGetBootMode (
  VOID
  )
{
  EFI_STATUS                            Status;
  EFI_BOOT_MODE                         BootMode;

  Status = PeiServicesGetBootMode (&BootMode);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, "TbtGetBootMode: Fail. Return TBT_NULL."));
    return TBT_NULL;
  }

  if (BootMode == BOOT_ON_S3_RESUME) {
    return TBT_S3;
  }

  if (BootMode == BOOT_ON_S4_RESUME) {
    return TBT_S4;
  }

  return TBT_NORMAL;
}

/**
  TbtTaskDistpach: Dispatch the TBT tasks according to TBT_CALL_TABLE_ENTRY

  @param[in] TBT_CALL_TABLE_ENTRY       TbtCallTable
  @param[in] VOID                       PeiTbtConfig
**/
VOID
TbtTaskDistpach (
  IN TBT_CALL_TABLE_ENTRY               *TbtCallTable,
  IN VOID                               *PeiTbtConfig
)
{
  EFI_STATUS                            Status;
  UINT32                                Index;
  TBT_BOOT_MODE                         TbtBootMode;
  const TBT_CALL_TABLE_ENTRY            *Task;

  //
  // Perform the TBT Task
  //

  if (TbtCallTable == NULL)
  {
    DEBUG((DEBUG_ERROR, "[TBT] TbtTaskDistpach: Invalid Call Table. Return."));
    return;
  }

  TbtBootMode = TbtGetBootMode ();

  Index = 0;
  Task = &TbtCallTable[0];
  while (AsciiStrCmp (Task->String, "END_OF_TASK") != 0) {
    Task = &TbtCallTable[Index];

    //
    // Decide if we need to execute the selected TBT task.
    //
    if ((NULL == Task->TbtTask) || (Task->TbtBootModeFlag == TBT_NULL)) {
      Index++;
      continue;
    }
    if (((TbtBootMode == TBT_S3) && (Task->TbtBootModeFlag & TBT_S3))
      || ((TbtBootMode == TBT_S4) && (Task->TbtBootModeFlag & TBT_S4))
      || ((TbtBootMode == TBT_NORMAL) && (Task->TbtBootModeFlag & TBT_NORMAL))
      )
    {
      DEBUG ((DEBUG_INFO, "[TBT] TbtTask [%a] Start\n", Task->String));
      Status = Task->TbtTask (PeiTbtConfig);
      DEBUG ((DEBUG_INFO, "[TBT] TbtTask [%a] End, Status = %r\n", Task->String, Status));

      if (EFI_ERROR(Status)){
        DEBUG((DEBUG_ERROR, "[TBT] TbtTask [%a] is failed. Aborting TbtTask Table Call.\n", Task->String));
        break;          // It will go out of While Loop
      }
    }

    Index++;
  }
}
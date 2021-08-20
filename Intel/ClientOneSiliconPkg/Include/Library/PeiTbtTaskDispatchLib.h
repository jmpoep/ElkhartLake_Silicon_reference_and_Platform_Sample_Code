/**@file
  PEI TBT Task Dispatch library Header file

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
#ifndef __PEI_TBT_TASK_DISPATCH_LIB_H__
#define __PEI_TBT_TASK_DISPATCH_LIB_H__

#include <Library/PeiServicesLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/GpioLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/HobLib.h>
#include <Library/PcdLib.h>

typedef
EFI_STATUS
(EFIAPI *TBT_TASK) (
  VOID  *PeiTbtConfig
);

typedef enum {
  TBT_NULL,                             ///< All policy flags turned off.
  TBT_NORMAL   = (1 << 0),              ///< Execute TBT function on cold reset.
  TBT_S3       = (1 << 1),              ///< Execute TBT function on S3 exit.
  TBT_S4       = (1 << 2),              ///< Execute TBT function on S4 exit.
  TBT_ALL      = MAX_UINTN              ///< Execute TBT function always.
} TBT_BOOT_MODE;

typedef struct {
  TBT_TASK      TbtTask;                ///< Ptr to function to execute, with parameter list.
  TBT_BOOT_MODE TbtBootModeFlag;        ///< Call table base on TbtBootModeFlag
  CHAR8         *String;                ///< Output string describing this task.
} TBT_CALL_TABLE_ENTRY;

/**
  Covert the current EFI_BOOT_MODE to TBT_BOOT_MODE

  @retval  TBT_BOOT_MODE                Mode to be used to execute corresponding TBT tasks.
**/
TBT_BOOT_MODE
TbtGetBootMode (
  VOID
);

/**
  TbtTaskDistpach: Dispatch the TBT tasks according to TBT_CALL_TABLE_ENTRY

  @param[in] TBT_CALL_TABLE_ENTRY       TbtCallTable
  @param[in] VOID                       PeiTbtConfig
**/
VOID
TbtTaskDistpach (
  IN TBT_CALL_TABLE_ENTRY               *TbtCallTable,
  IN VOID                               *PeiTbtConfig
);
#endif

/** @file
  Header file of Fast Boot platform setup DXE driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#ifndef _FAST_BOOT_INFO_DRIVER_H_
#define _FAST_BOOT_INFO_DRIVER_H_

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <PlatformNvRamHookLib.h>
#include <Protocol/TcgService.h>
#include <Protocol/CpuIo2.h>
#include <Protocol/FastBootException.h>
#include <FastBootExceptionInfoHob.h>
#include <FastBootFunctionEnabledHob.h>
#include <Guid/HobList.h>
#include <Guid/EventGroup.h>
#include <Register/PmcRegs.h>
#include <Setup.h>
#include <SetupVariable.h>
#include <TcgSetup.h>

#define FAST_BOOT_WDT_RESET_SIGNATURE   0xFB
#define FAST_BOOT_WDT_30_SECONDS_COUNT  ((30 * 10 - 24) / 6)

#endif

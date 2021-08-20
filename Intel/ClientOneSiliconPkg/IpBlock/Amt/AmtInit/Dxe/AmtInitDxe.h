/** @file
  Include file for Amt Initialization Driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#ifndef _AMT_INIT_DXE_H_
#define _AMT_INIT_DXE_H_

#include <PiDxe.h>
#include <Pi/PiStatusCode.h>
#include <IndustryStandard/AlertStandardFormatTable.h>
#include <Guid/ConsoleOutDevice.h>
#include <Guid/HobList.h>
#include <Library/HobLib.h>
#include <Library/DxeAmtHeciLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/PostCodeLib.h>
#include <Library/DxeAsfLib.h>
#include <Library/DxeAmtHeciLib.h>
#include <Library/AslUpdateLib.h>
#include <Protocol/Runtime.h>
#include <Protocol/ReportStatusCodeHandler.h>
#include <Protocol/AsfProtocol.h>
#include <Protocol/HeciProtocol.h>
#include <Protocol/AmtPolicy.h>
#include <Library/AsfMsgLib.h>
#include <AmtForcePushPetHob.h>
#include <AmtPetQueueHob.h>
#include <AmtConfig.h>
#include <CoreBiosMsg.h>

#define AMT_FORCE_PUSH_PET_VARIABLE_NAME  L"AmtForcePushErrorPET"

//
// Prototypes
//
/**
  Register KVM Notification on ConsoltOut Device installed.

  @retval EFI_SUCCESS             The function executed without error.
  @retval EFI_INVALID_PARAMETER   One or more parameters are invalid.
  @retval EFI_OUT_OF_RESOURCES    The event could not be allocated.
**/
EFI_STATUS
KvmInit (
  VOID
  );

/**
  PET Message and Progress Code initialization.

  @retval EFI_SUCCESS             The driver installed without error.
  @retval EFI_INVALID_PARAMETER   One or more parameters are invalid.
  @retval EFI_OUT_OF_RESOURCES    The event could not be allocated.
**/
EFI_STATUS
PetMessageInit (
  VOID
  );
#endif

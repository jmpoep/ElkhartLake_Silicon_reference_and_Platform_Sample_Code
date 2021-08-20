/** @file
  Register Definitions for Me States

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2019 Intel Corporation.

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
#ifndef _ME_STATE_H_
#define _ME_STATE_H_
///
/// Ignore ME_FW_INIT_COMPLETE status Macro
///
#define ME_STATUS_ME_STATE_ONLY(a)  ((a) & (~(ME_FW_INIT_COMPLETE | ME_FW_BOOT_OPTIONS_PRESENT)))

///
/// Macro to check if ME FW INIT is completed
///
#define ME_STATUS_IS_ME_FW_INIT_COMPLETE(a) (((a) & ME_FW_INIT_COMPLETE) == ME_FW_INIT_COMPLETE)

///
/// Macro to combine the complete bit to status
///
#define ME_STATUS_WITH_ME_INIT_COMPLETE(a)  ((a) | ME_FW_INIT_COMPLETE)

///
/// Macro to check ME Boot Option Present
///
#define ME_STATUS_IS_ME_FW_BOOT_OPTIONS_PRESENT(a)  (((a) & ME_FW_BOOT_OPTIONS_PRESENT) == ME_FW_BOOT_OPTIONS_PRESENT)

//
// Abstract ME Mode Definitions
//
#define ME_MODE_NORMAL        0x00
#define ME_MODE_DEBUG         0x02
#define ME_MODE_TEMP_DISABLED 0x03
#define ME_MODE_SECOVER       0x04
#define ME_MODE_SPS           0x05  // Server SPS firmware is running in ME
#define ME_MODE_FAILED        0x06

//
// Abstract ME Status definitions
//
#define ME_READY                    0x00
#define ME_INITIALIZING             0x01
#define ME_IN_RECOVERY_MODE         0x02
#define ME_DISABLE_WAIT             0x06
#define ME_TRANSITION               0x07
#define ME_NOT_READY                0x0F
#define ME_FW_INIT_COMPLETE         0x80
#define ME_FW_BOOT_OPTIONS_PRESENT  0x100
#define ME_FW_UPDATES_IN_PROGRESS   0x200

//
// HECI Software Progress Error Code definitions.
// Error Code Structure: (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000x00) | ERROR_STATUS) = 0x03008x00
//
#define EFI_STATUS_TO_STATUS_CODE_VALUE(EfiStatus)  ((EFI_STATUS_CODE_VALUE) (EfiStatus & 0x1F))

#define SW_HECI_ACK_ERROR           (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000100))
#define SW_HECI_RECEIVE_ERROR       (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000200))
#define SW_HECI_SEND_ERROR          (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000300))
#define SW_HECI_INIT_ERROR          (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000400))
#define SW_HECI_GET_STATUS_ERROR    (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000500))
#define SW_HECI_GET_MODE_ERROR      (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000600))
#define SW_HECI_RESET_HECI_ERROR    (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000700))
#define SW_HECI_REINIT_ERROR        (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000800))
#define SW_HECI_RESETWAIT_ERROR     (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000900))
#define SW_HECI_EOP_ERROR           (EFI_SOFTWARE_UNSPECIFIED | (EFI_OEM_SPECIFIC | 0x00000A00))
#endif // _ME_STATE_H_

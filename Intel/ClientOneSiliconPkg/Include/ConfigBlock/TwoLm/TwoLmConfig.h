/** @file
  2LM PEI Pre-mem policy

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
#ifndef TWOLM_CONFIG_H_
#define TWOLM_CONFIG_H_


#include <ConfigBlock.h>

#define TWOLM_PREMEM_CONFIG_REVISION 1
extern EFI_GUID gTwoLmPreMemConfigGuid;

#define MFVC_VC_ARB_TABLE_INDEX 16         // Index for VC arbitration table registers

#define MEM_BOOT_MODE_1LM            0
#define MEM_BOOT_MODE_2LM            1
#define MEM_BOOT_MODE_PROVISIONING   2

#pragma pack (push,1)

///
/// The TWOLM_PREMEM_CONFIG block describes 2LM settings.
/// Revision 1 : Initial Version
///
typedef struct {
  CONFIG_BLOCK_HEADER   Header;             //< Offset 0-27 Config Block Header
  UINT32                FarMemorySize;      //< Offset 28-31 Far Memory Size in units of MB
  UINT32                PMemSize;           //< Offset 32-35 Persistent Memory Size in units of MB
  UINT8                 MemBootMode;        //< Offset 36 <b> 1: 1LM Mode </b>, 2: 2LM Mode, 3: Provisioning mode
  UINT8                 Peg3Aspm;           //< Offset 37 0:Disabled, 1:L0 ASPM, 2:L1 ASPM, <b> 3:L0L1 ASPM </b>, 4:Auto
  UINT8                 MfvcWrrArb;         //< Offset 38 MFVC WRR Arbitration setting 0:default, 1:128phase
  UINT8                 Rsvd1;              //< Offset 39 Reserved for Config block alignment
  UINT8                 VcId_7_0[MFVC_VC_ARB_TABLE_INDEX];    //< Offset 40-55 VC arbitration phase 31_00
  // Willard HW Parameters,                                     < Offset 56-59
  UINT32                SetHwParameters                : 1; // Enable/disable setting of HW parameters
  UINT32                Ltr_L1D2_ThVal                 :10; // LTR L1.2 Threshold Value
  UINT32                Ltr_L1D2_ThScale               : 3; // LTR L1.2 Threshold Scale
  UINT32                SysPwrState                    : 4; // system power state indicates the platform power state
  UINT32                MediaDeathNotification         : 1; // Media Death Notification Enable/Disable
  UINT32                HealthLogNotification          : 1; // Health Log Notification Enable/Disable
  UINT32                TempBelowThrottleNotification  : 1; // Temp crosses below TempThrottle Notification Enable/Disable
  UINT32                TempAboveThrottleNotification  : 1; // Temp crosses above TempThrottle Notification Enable/Disable
  UINT32                MissingCommitBitNotification   : 1; // Missing Commit Bit Notification Enable/Disable
  UINT32                NVMeHoldDisableBit             : 1; // When set to '1', FMSS will not send NVMe_hold VDM to initiate L1 low power state entry.
  UINT32                RsvdBits0                      : 8; // Reserved
} TWOLM_PREMEM_CONFIG;

#pragma pack (pop)

#endif /* TWOLM_CONFIG_H_ */

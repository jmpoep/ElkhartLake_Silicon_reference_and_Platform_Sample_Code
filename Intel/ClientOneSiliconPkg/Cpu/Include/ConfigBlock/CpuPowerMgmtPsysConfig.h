/** @file
  CPU Power Management Psys(Platform) Config Block.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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
#ifndef _CPU_POWER_MGMT_PSYS_CONFIG_H_
#define _CPU_POWER_MGMT_PSYS_CONFIG_H_

#define CPU_POWER_MGMT_PSYS_CONFIG_REVISION 1

extern EFI_GUID gCpuPowerMgmtPsysConfigGuid;

#pragma pack (push,1)

/**
  CPU Power Management Psys(Platform) Configuration Structure.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  UINT32 PsysPowerLimit1       : 1;               ///< MSR 0x65C[15]: PL1 Enable activates the PL1 value to limit average platform power
  UINT32 PsysPowerLimit1Time   : 8;               ///< MSR 0x65C[23:17]: PL1 timewindow in seconds.
  UINT32 PsysPowerLimit2       : 1;               ///< MSR 0x65C[47]: PL2 Enable activates the PL2 value to limit average platform power
  UINT32 RsvdBits              : 22;              ///< Reserved for future use.
  UINT16 PsysPowerLimit1Power;                    ///< MSR 0x65C[14:0]: Platform PL1 power. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.
  UINT16 PsysPowerLimit2Power;                    ///< MSR 0x65C[46:32]]: Platform PL2 power. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.
  UINT16 PsysPmax;                                ///< PCODE MMIO Mailbox: Platform Power Pmax. <b>0 - Auto</b> Specified in 1/8 Watt increments. 0-1024 Watts. Value of 800 = 100W.
  UINT8  Rsvd[2];                                 ///< Reserved for future use and config block alignment
} CPU_POWER_MGMT_PSYS_CONFIG;

#pragma pack (pop)

#endif // _CPU_POWER_MGMT_PSYS_CONFIG_H_

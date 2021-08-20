/** @file
  CPU PID Config Block.

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
#ifndef _CPU_PID_TEST_CONFIG_H_
#define _CPU_PID_TEST_CONFIG_H_

#define CPU_PID_TEST_CONFIG_REVISION 1

extern EFI_GUID gCpuPidTestConfigGuid;

#pragma pack (push,1)

/**
  PID Tuning Configuration Structure.
  Domain is mapped to Kp = 0, Ki = 1, Kd = 2.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  UINT16  Ratl[3];                                ///< RATL setting, in 1/256 units. Range is 0 - 65280
  UINT16  VrTdcVr0[3];                            ///< VR Thermal Design Current for VR0. In 1/256 units. Range is 0 - 65280
  UINT16  VrTdcVr1[3];                            ///< VR Thermal Design Current for VR1. In 1/256 units. Range is 0 - 65280
  UINT16  VrTdcVr2[3];                            ///< VR Thermal Design Current for VR2. In 1/256 units. Range is 0 - 65280
  UINT16  VrTdcVr3[3];                            ///< VR Thermal Design Current for VR3. In 1/256 units. Range is 0 - 65280
  UINT16  PbmPsysPl1Msr[3];                       ///< Power Budget Management Psys PL1 MSR. In 1/256 units. Range is 0 - 65280
  UINT16  PbmPsysPl1MmioPcs[3];                   ///< Power Budget Management Psys PL1 MMIO/PCS. In 1/256 units. Range is 0 - 65280
  UINT16  PbmPsysPl2Msr[3];                       ///< Power Budget Management Psys PL2 MSR. In 1/256 units. Range is 0 - 65280
  UINT16  PbmPsysPl2MmioPcs[3];                   ///< Power Budget Management Psys PL2 MMIO/PCS. In 1/256 units. Range is 0 - 65280
  UINT16  PbmPkgPl1Msr[3];                        ///< Power Budget Management Package PL1 MSR. In 1/256 units. Range is 0 - 65280
  UINT16  PbmPkgPl1MmioPcs[3];                    ///< Power Budget Management Package PL1 MMIO/PCS. In 1/256 units. Range is 0 - 65280
  UINT16  PbmPkgPl2Msr[3];                        ///< Power Budget Management Package PL2 MSR. In 1/256 units. Range is 0 - 65280
  UINT16  PbmPkgPl2MmioPcs[3];                    ///< Power Budget Management Package PL2 MMIO/PCS. In 1/256 units. Range is 0 - 65280
  UINT16  DdrPl1Msr[3];                           ///< DDR PL1 MSR. In 1/256 units. Range is 0 - 65280
  UINT16  DdrPl1MmioPcs[3];                       ///< DDR PL1 MMIO/PCS. In 1/256 units. Range is 0 - 65280
  UINT16  DdrPl2Msr[3];                           ///< DDR PL2 MSR. In 1/256 units. Range is 0 - 65280
  UINT16  DdrPl2MmioPcs[3];                       ///< DDR PL2 MMIO/PCS. In 1/256 units. Range is 0 - 65280
  /**
  Enable or Disable PID Tuning programming flow.
  If disabled, all other policies in this config block are ignored.
  **/
  UINT8   PidTuning;
  UINT8   Rsvd;                                   ///< Reserved for DWORD alignment.
} CPU_PID_TEST_CONFIG;

#pragma pack (pop)

#endif // _CPU_PID_TEST_CONFIG_H_

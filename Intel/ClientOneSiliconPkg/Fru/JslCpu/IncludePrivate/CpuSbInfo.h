/** @file
  Register names for CPU Side Band Information

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
#ifndef _CPU_SB_INFO_H_
#define _CPU_SB_INFO_H_

//
// CPU SB Device
//

#define CPU_SB_PID_PSF0       0x67
#define CPU_SB_PID_PSF1       0x64
#define CPU_SB_PID_TBT0       0xC3
#define CPU_SB_PID_TBT1       0xD1
#define CPU_SB_PID_PSF4       0xC9
#define CPU_SB_PID_PSF5       0xCB
#define CPU_SB_PID_OPIO       0x74
#define CPU_SB_PID_IOM        0xC1
#define CPU_SB_PID_FIA        0xD4
#define CPU_SB_PID_MG0        0xC4
#define CPU_SB_PID_MG1        0xC5
#define CPU_SB_PID_MG2        0xD2
#define CPU_SB_PID_MG3        0xD3
#define CPU_SB_PID_PCIE0      0xC6
#define CPU_SB_PID_PCIE1      0xC7
#define CPU_SB_PID_PCIE2      0xCE
#define CPU_SB_PID_PCIE3      0xCF
#define CPU_SB_PID_XHCI       0xC8
#define CPU_SB_PID_XDCI       0xCC
#define CPU_SB_PID_HTI        0xCD
#define CPU_SB_PID_PSFOPIO    0x70
#define CPU_SB_PID_FMHC       0x7F
#define CPU_SB_PID_PEG10      0x52
#define CPU_SB_PID_PEG11_12   0x56
#define CPU_SB_PID_PEG60      0x57
#define CPU_SB_PID_DEKEL_IO4  0x55
#define CPU_SB_PID_DEKEL_IO16 0x51

#endif  // _CPU_SB_INFO_H_

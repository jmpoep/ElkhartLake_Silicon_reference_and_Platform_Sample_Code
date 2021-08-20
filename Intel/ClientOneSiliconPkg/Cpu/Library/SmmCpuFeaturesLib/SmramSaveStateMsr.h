/** @file
  SMM State Save register.


@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

#ifndef __SMRAM_SAVE_STATE_MSR_H__
#define __SMRAM_SAVE_STATE_MSR_H__

///
/// MSR based SMM Save State Registers
///
#define MSR_CR0                      0xC00
#define MSR_CR3                      0xC01
#define MSR_EFLAGS                   0xC02

#define MSR_EFER                     0xC03
#define MSR_RIP                      0xC04
#define MSR_DR6                      0xC05
#define MSR_DR7                      0xC06
#define MSR_TR_LDTR                  0xC07
#define MSR_GS_FS                    0xC08
#define MSR_DS_SS                    0xC09
#define MSR_CS_ES                    0xC0A
#define MSR_IO_MISC_INFO             0xC0B
#define MSR_IO_MEM_ADDR              0xC0C
#define MSR_RDI                      0xC0D
#define MSR_RSI                      0xC0E
#define MSR_RBP                      0xC0F
#define MSR_RSP                      0xC10
#define MSR_RBX                      0xC11
#define MSR_RDX                      0xC12
#define MSR_RCX                      0xC13
#define MSR_RAX                      0xC14
#define MSR_R8                       0xC15
#define MSR_R9                       0xC16
#define MSR_R10                      0xC17
#define MSR_R11                      0xC18
#define MSR_R12                      0xC19
#define MSR_R13                      0xC1A
#define MSR_R14                      0xC1B
#define MSR_R15                      0xC1C
#define MSR_EVENT_CTL_HLT_IO         0xC1F

#define MSR_SMM_REVID                0xC21

#define MSR_LDTR_BASE                0xC2C
#define MSR_IDTR_BASE                0xC2D
#define MSR_GDTR_BASE                0xC2E

#define MSR_CR4                      0xC37

#endif

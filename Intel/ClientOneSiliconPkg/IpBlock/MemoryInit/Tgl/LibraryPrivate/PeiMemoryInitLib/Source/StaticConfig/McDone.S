/** @file

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

 @par Specification
**/

#define PRMRR_SIZE          0x8000000
#define PRMRR_SIZE_1        (PRMRR_SIZE - 1)
#define PRMRR_SIZE_2        (NOT PRMRR_SIZE_1)
#define UCODE_CR_MTRRCAP    0xfe
#define PRMRR_ENABLE        (1 SHL 12)
#define PRMRR_MASK_EN       0x800
#define PRMRR_MASK_LOCK     0x400
#define PRMRR_MASK_LOCK_EN  (PRMRR_MASK_EN | PRMRR_MASK_EN) 
#define UNCORE_PRMRR_MASK   0x1F5
#define UNCORE_PRMRR_BASE   0x2A0
#define NOT_F               (NOT 0xF)
".equ   PRMRR_SIZE, 0x8000000\n\t"
".equ   PRMRR_SIZE_1, 0x7FFFFFF\n\t"
".equ   PRMRR_SIZE_2, 0xF8000000\n\t"
".equ   UCODE_CR_MTRRCAP, 0xFE\n\t"
".equ   PRMRR_ENABLE, 0x1000\n\t"
".equ   PRMRR_MASK_EN, 0x800\n\t"
".equ   PRMRR_MASK_LOCK, 0x400\n\t"
".equ   PRMRR_MASK_LOCK_EN, (PRMRR_MASK_EN | PRMRR_MASK_EN) \n\t"
".equ   UNCORE_PRMRR_MASK, 0x1F5\n\t"
".equ   UNCORE_PRMRR_BASE, 0x2A0\n\t"
".equ   NOT_F, 0xFFFFFFF0\n\t"
"movl   $UCODE_CR_MTRRCAP, %%ecx\n\t"
"rdmsr\n\t"
"test   $PRMRR_ENABLE, %%eax\n\t"
"je     prmrr_skip\n\t"

// TSEGMB
"xorl    %%edx, %%edx\n\t"
"movl    0x0e00000B8, %%eax\n\t"
"outl    %%eax, $0x84\n\t"
"andl    $NOT_F, %%eax\n\t"

"subl   $PRMRR_SIZE, %%eax\n\t"
"andl   $PRMRR_SIZE_2, %%eax\n\t"

"movl   $UNCORE_PRMRR_BASE, %%ecx\n\t"
"wrmsr\n\t"

"movl   $0x7F, %%edx\n\t"
"movl   $0xffffffff, %%eax\n\t"
"subl   $PRMRR_SIZE_1, %%eax\n\t"                    /* 128 MB */
"orl    $PRMRR_MASK_LOCK_EN, %%eax\n\t"   /* Set lock bit [10] and 11 */
"movl   $UNCORE_PRMRR_MASK, %%eax\n\t"
"wrmsr\n\t"
"prmrr_skip:\n\t"

//
// writing to register MCDECS_CR_MC_INIT_STATE_G_0_0_0_MCHBAR_MCMAIN of MCHBAR
//
"movl    $0x00040018B, 0xfed15030\n\t"
"movl    $0x0000008F, 0xfed150FC\n\t"

//
// Poll MCDECS_CR_MC_INIT_STATE_G_0_0_0_MCHBAR_MCMAIN_MC_INIT_DONE_ACK  bit until is is set.
//
"PollDoneACK1600:\n\t"
  "testl  $0x20, 0xfed15030\n\t"
  "jz     PollDoneACK1600\n\t"

//
// Enable DDR thermal test feature
// DDR_PTM_CTL_0_0_0_MCHBAR_PCU offset 0x5880
// Set CLTM_ENABLE, bit 1:1
//
"movl   0xfed15880, %%eax\n\t"
"bts    $0x1, %%eax\n\t"
"movl   %%eax, 0xfed15880\n\t"

//
// Lock registers
//
"movl   %0, %%eax\n\t"
"outl   %%eax, $0x80\n\t"                      /* send a marker to port 80 */

"orl    $0x1, 0xa0(%%eax)\n\t"
"orl    $0x1, 0xbc(%%eax)\n\t"
"orl    $0x1, 0xb4(%%eax)\n\t"
"orl    $0x1, 0xb0(%%eax)\n\t"
"orl    $0x1, 0xa8(%%eax)\n\t"

"movl   0x98(%%eax), %%edx\n\t"
"orl    $0x1, %%edx\n\t"
"movl   %%edx, 0x98(%%eax)\n\t"

"movl   0x90(%%eax), %%edx\n\t"
"orl    $0x1, %%edx\n\t"
"movl   %%edx, 0x98(%%eax)\n\t"

"orl    $0x400, 0x78(%%eax)\n\t"

//
// Set EDRAM Base Address
//
"movl   $0xCF114000, %%eax\n\t"
"outl   %%eax, $0x80\n\t"

"xorl   %%edx, %%edx\n\t"
"shld   $6, %%eax, %%edx\n\t"
"orl    $0x1, %%eax\n\t"
"outl   %%eax, $0x80\n\t"
"xchgl  %%eax, %%edx\n\t"
"outl   %%eax, $0x80\n\t"
"xchgl  %%eax, %%edx\n\t"


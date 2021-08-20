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
//
// 8GB RAM, 6 GB remapped NO GFX
//

//
// Show the DDR size in GB on port80 
//
"movl   $0xC00A0008, %%eax\n\t"
"outl   %%eax, $0x80\n\t"
"movl   %0, %%ebx\n\t" /* move Pciexbar into ebx */

// NO GFX
"movl   $0x2, 0x50(%%ebx)\n\t"

// MESEG_BASE
"movl   $0xfe000000, 0x70(%%ebx)\n\t"
"movl   $1, 0x74(%%ebx)\n\t"

// MESEG_MASK
"movl   $0xfef00800, 0x78(%%ebx)\n\t"
"movl   $0x1, 0x7C(%%ebx)\n\t"

// REMAPBASE = 4GB
"movl   $0xfe000000, 0x90(%%ebx)\n\t"
"movl   $0x1, 0x94(%%ebx)\n\t"

// REMAPLIMIT
"movl   $0x7df00000, 0x98(%%ebx)\n\t"
"movl   $0x2, 0x9C(%%ebx)\n\t"

// TOM  = 8GB
"movl   $0x0, 0xA0(%%ebx)\n\t"
"movl   $0x2, 0xA4(%%ebx)\n\t"

// TOUUD to min(TOM-stolen mem for ME OR min PCI mem addr)\n\t"
"movl   $0x7f000000, 0xA8(%%ebx)\n\t"
"movl   $0x2, 0xAC(%%ebx)\n\t"

// BDSM
"movl   $0x80000000, 0xB0(%%ebx)\n\t"

// BGSM
"movl   $0x80000000, 0xB4(%%ebx)\n\t"

// TSEGMB
"movl   $0x7F000000, 0xB8(%%ebx)\n\t"

// TOLUD to TOM-stolen mem for ME
"movl   $0x80000000, 0xBC(%%ebx)\n\t"


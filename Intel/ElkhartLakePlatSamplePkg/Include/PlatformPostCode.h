/** @file

@copyright
  INTEL CONFIDENTIAL
 Copyright (c) 2016-2017 Intel Corporation. All rights reserved

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

@par Specification Reference:
**/
#ifndef _PLATFORMPOSTCODE_H_
#define _PLATFORMPOSTCODE_H_

//
// GENERAL USAGE GUIDELINES
//

/**
[definition]
PostCode = XYZZ
X - "D"=premem, "9"=postmem, "8"=SMM, "7"=DXE
Y - "6"=platform driver, "5"=board driver
ZZ - "00"=entry, "7F"=exit
 - 1 - board init premem: entry/exit (0xD500/0xD57F)
 - 2 - platform init premem: entry/exit (0xD600/0xD67F)
 - 3 - board init postmem: entry/exit (0x9500/0x957F)
 - 4 - platform init postmem: entry/exit (0x9600/0x967F)
 - 5 - board init DXE: entry/exit (0x7500/0x757F)
 - 6 - platform init DXE: entry/exit (0x7600/0x767F)
 - 7 - platform SMM init: entry/exit (0x8600/0x867F)
 - 8 - BIOS S3 entry (0xB503) means BioS PC 03, to differentiate with ACPI _PTS PC
 - 9 - BIOS S4 entry (0xB504) means BioS PC 04, to differentiate with ACPI _PTS PC
 - 10 - BIOS S5 entry (0B505) means BioS PC 05, to differentiate with ACPI _PTS PC
*/

#define BOARD_INIT_PREMEM_ENTRY     0xD500
#define BOARD_INIT_PREMEM_EXIT      0xD57F
#define PLATFORM_INIT_PREMEM_ENTRY  0xD600
#define PLATFORM_INIT_PREMEM_EXIT   0xD67F
#define BOARD_INIT_POSTMEM_ENTRY    0x9500
#define BOARD_INIT_POSTMEM_EXIT     0x957F
#define PLATFORM_INIT_POSTMEM_ENTRY 0x9600
#define PLATFORM_INIT_POSTMEM_EXIT  0x967F
#define BOARD_INIT_DXE_ENTRY        0x7500
#define BOARD_INIT_DXE_EXIT         0x757F
#define PLATFORM_INIT_DXE_ENTRY     0x7600
#define PLATFORM_INIT_DXE_EXIT      0x767F
#define PLATFORM_SMM_INIT_ENTRY     0x8600
#define PLATFORM_SMM_INIT_EXIT      0x867F
#define BIOS_S3_ENTRY               0xB503
#define BIOS_S4_ENTRY               0xB504
#define BIOS_S5_ENTRY               0xB505

#endif

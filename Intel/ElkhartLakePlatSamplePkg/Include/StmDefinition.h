/** @file
  This file contains definitions required to use the TXT STM

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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
#ifndef _TXT_STM_DEFINITION_H_
#define _TXT_STM_DEFINITION_H_

///
/// MSR definitions
///
#define MSR_PLATFORM_INFORMATION     0x000000CE
#define IA32_MTRR_PHYSBASE0 0x200
#define IA32_MTRR_PHYSMASK0 0x201
#define IA32_MTRR_PHYSBASE1 0x202
#define IA32_MTRR_PHYSMASK1 0x203
#define IA32_MTRR_PHYSBASE2 0x204
#define IA32_MTRR_PHYSMASK2 0x205
#define IA32_MTRR_PHYSBASE3 0x206
#define IA32_MTRR_PHYSMASK3 0x207
#define IA32_MTRR_PHYSBASE4 0x208
#define IA32_MTRR_PHYSMASK4 0x209
#define IA32_MTRR_PHYSBASE5 0x20A
#define IA32_MTRR_PHYSMASK5 0x20B
#define IA32_MTRR_PHYSBASE6 0x20C
#define IA32_MTRR_PHYSMASK6 0x20D
#define IA32_MTRR_PHYSBASE7 0x20E
#define IA32_MTRR_PHYSMASK7 0x20F
#define IA32_MTRR_PHYSBASE8 0x210
#define IA32_MTRR_PHYSMASK8 0x211
#define IA32_MTRR_PHYSBASE9 0x212
#define IA32_MTRR_PHYSMASK9 0x213

///
/// STM Definitions
///
///
/// Errors
///
#define SMM_SUCCESS                     0
#define ERROR_SMM_BAD_BUFFER            0x80020001
#define ERROR_SMM_MODULE_NOT_FOUND      0x80020002
#define ERROR_SMM_MODULE_FAIL_TO_UPDATE 0x80020003
#define ERROR_SMM_INVALID_RSC           0x80020004
#define ERROR_SMM_INVALID_BUFFER_SIZE   0x80020005
#define ERROR_SMM_BUFFER_TOO_SHORT      0x80020006
#define ERROR_SMM_INVALID_LIST          0x80020007
#define ERROR_SMM_OUT_OF_MEMORY         0x80020008
#define ERROR_SMM_AFTER_INIT            0x80020009

#define ERROR_INVALID_API               0x80030001
#define ERROR_INVALID_PARAMETER         0x80030002

///
/// API values
///
#ifndef SW_SMI_STM_GET_BIOS_AC_STATUS_CMD
#define SW_SMI_STM_GET_BIOS_AC_STATUS_CMD 0x10
#endif

#ifndef SW_SMI_STM_UPDATE_BIOS_AC_CMD
#define SW_SMI_STM_UPDATE_BIOS_AC_CMD 0x11
#endif

#ifndef SW_SMI_STM_GET_SINIT_AC_STATUS_CMD
#define SW_SMI_STM_GET_SINIT_AC_STATUS_CMD  0x12
#endif

#ifndef SW_SMI_STM_UPDATE_SINIT_AC_CMD
#define SW_SMI_STM_UPDATE_SINIT_AC_CMD  0x13
#endif

#ifndef SW_SMI_STM_GET_STM_STATUS_CMD
#define SW_SMI_STM_GET_STM_STATUS_CMD 0x14
#endif

#ifndef SW_SMI_STM_UPDATE_STM_CMD
#define SW_SMI_STM_UPDATE_STM_CMD 0x15
#endif

#ifndef SW_SMI_STM_HANDLE_BIOS_RESOURCES_CMD
#define SW_SMI_STM_HANDLE_BIOS_RESOURCES_CMD  0x16
#endif

#ifndef SW_SMI_STM_ACCESS_RESOURCES_CMD
#define SW_SMI_STM_ACCESS_RESOURCES_CMD 0x17
#endif

#ifndef SW_SMI_STM_LOAD_STM_CMD
#define SW_SMI_STM_LOAD_STM_CMD 0x18
#endif

#ifndef SW_SMI_STM_ADD_RESOURCES_CMD
#define SW_SMI_STM_ADD_RESOURCES_CMD  0x19
#endif

#define SW_SMI_STM_ADD_RUNTIME_RESOURCES_FUNC   0
#define SW_SMI_STM_READ_BIOS_RESOURCES_FUNC     1
#define SW_SMI_STM_REPLACE_BIOS_RESOURCES_FUNC  2
#define APPEND                                  0
#define START_OVER                              !0

#endif

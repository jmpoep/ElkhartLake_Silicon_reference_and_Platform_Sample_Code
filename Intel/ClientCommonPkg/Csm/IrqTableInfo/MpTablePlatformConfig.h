/** @file
Header file for MP table builder.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#ifndef __MPTABLE__PLATFORM_CONFIG_H__
#define __MPTABLE__PLATFORM_CONFIG_H__

#define ISA_IRQ_MASK      0xFFFF

#define MP_TABLE_MAX_BUS_ENTRIES        0xFF //from 0 to 0xFE, FF reserved means no parent bus
#define MP_TABLE_MAX_IO_APIC_ENTRIES    0x10

#define IO_APIC_BASE_ADDRESS_BOTTOM 0xFEC00000
#define IO_APIC_BASE_ADDRESS_TOP    0xFED00000
#define IO_APIC_SEARCH_STEP         0x1000

#define IO_APIC_INDEX_REG   0x0
#define IO_APIC_DATA_REG    0x4 //(0x10 in bytes = 0x4 in dwords

#define IO_APIC_MAP_ID_REG        0x0
#define IO_APIC_MAP_VERSION_REG   0x1

#define B_EFI_MSR_IA32_APIC_BASE_G_XAPIC      0x800//IA32_APIC_BASE bit11
#define B_EFI_MSR_IA32_APIC_BASE_M_XAPIC      0x400//IA32_APIC_BASE bit10

#define MP_TABLE_MAX_LEN                      4096
#define MP_EX_TABLE_MAX_LEN                   2048
#endif

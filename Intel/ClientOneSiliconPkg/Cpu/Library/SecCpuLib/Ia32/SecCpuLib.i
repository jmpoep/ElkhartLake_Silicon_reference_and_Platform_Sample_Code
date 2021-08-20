## @file
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2014 - 2017 Intel Corporation.
#
#  The source code contained or described herein and all documents related to the
#  source code ("Material") are owned by Intel Corporation or its suppliers or
#  licensors. Title to the Material remains with Intel Corporation or its suppliers
#  and licensors. The Material may contain trade secrets and proprietary and
#  confidential information of Intel Corporation and its suppliers and licensors,
#  and is protected by worldwide copyright and trade secret laws and treaty
#  provisions. No part of the Material may be used, copied, reproduced, modified,
#  published, uploaded, posted, transmitted, distributed, or disclosed in any way
#  without Intel's prior express written permission.
#
#  No license under any patent, copyright, trade secret or other intellectual
#  property right is granted to or conferred upon you by disclosure or delivery
#  of the Materials, either expressly, by implication, inducement, estoppel or
#  otherwise. Any license under such intellectual property rights must be
#  express and approved by Intel in writing.
#
#  Unless otherwise agreed by Intel in writing, you may not remove or alter
#  this notice or any other notice embedded in Materials by Intel or
#  Intel's suppliers or licensors in any way.
#
#  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
#  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
#  the terms of your license agreement with Intel or your vendor. This file may
#  be modified by the user, subject to additional terms of the license agreement.
#
# @par Specification
#

#
# Set to 1 to enable debug
#
.equ             NO_EVICTION_MODE_DEBUG,            0x01

.macro STATUS_CODE   status
.ifdef NO_EVICTION_MODE_DEBUG
   movb  \status, %al
   out   %al, $0x080
.endif
.endm

.macro    RET_ESI
  movd    %mm7, %esi                     # restore ESP from MM7
  jmp     *%esi
.endm

.macro    RET_EBP
  jmp     *%ebp                          # restore ESP from EBP
.endm

#
# MSR definitions
#
.equ             MSR_IA32_PLATFORM_ID,              0x0017
.equ             MSR_IA32_BIOS_UPDT_TRIG,           0x0079
.equ             MSR_IA32_BIOS_SIGN_ID,             0x008B
.equ             MSR_IA32_DEBUG_INTERFACE,          0x0C80
.equ             MSR_APIC_BASE,                     0x001B
.equ             MSR_BOOT_GUARD_SACM_INFO,          0x013A

#
# MTRR definitions
#
.equ             IA32_MTRR_CAP,                     0x00FE
.equ             MTRR_PHYS_BASE_0,                  0x0200
.equ             MTRR_PHYS_MASK_0,                  0x0201
.equ             MTRR_PHYS_BASE_1,                  0x0202
.equ             MTRR_PHYS_MASK_1,                  0x0203
.equ             MTRR_PHYS_BASE_2,                  0x0204
.equ             MTRR_PHYS_MASK_2,                  0x0205
.equ             MTRR_PHYS_BASE_3,                  0x0206
.equ             MTRR_PHYS_MASK_3,                  0x0207
.equ             MTRR_PHYS_BASE_4,                  0x0208
.equ             MTRR_PHYS_MASK_4,                  0x0209
.equ             MTRR_PHYS_BASE_5,                  0x020A
.equ             MTRR_PHYS_MASK_5,                  0x020B
.equ             MTRR_PHYS_BASE_6,                  0x020C
.equ             MTRR_PHYS_MASK_6,                  0x020D
.equ             MTRR_PHYS_BASE_7,                  0x020E
.equ             MTRR_PHYS_MASK_7,                  0x020F
.equ             MTRR_PHYS_BASE_8,                  0x0210
.equ             MTRR_PHYS_MASK_8,                  0x0211
.equ             MTRR_PHYS_BASE_9,                  0x0212
.equ             MTRR_PHYS_MASK_9,                  0x0213
.equ             MTRR_FIX_64K_00000,                0x0250
.equ             MTRR_FIX_16K_80000,                0x0258
.equ             MTRR_FIX_16K_A0000,                0x0259
.equ             MTRR_FIX_4K_C0000,                 0x0268
.equ             MTRR_FIX_4K_C8000,                 0x0269
.equ             MTRR_FIX_4K_D0000,                 0x026A
.equ             MTRR_FIX_4K_D8000,                 0x026B
.equ             MTRR_FIX_4K_E0000,                 0x026C
.equ             MTRR_FIX_4K_E8000,                 0x026D
.equ             MTRR_FIX_4K_F0000,                 0x026E
.equ             MTRR_FIX_4K_F8000,                 0x026F
.equ             MTRR_DEF_TYPE,                     0x02FF
.equ             MTRR_DEF_TYPE_E,                   0x0800
.equ             MTRR_DEF_TYPE_FE,                  0x0400

#
# Define the high 32 bits of MTRR masking
# This should be read from CPUID EAX = 080000008h, EAX bits [7:0]
# But for most platforms this will be a fixed supported size so it is
# fixed to save space.
#
.equ             MTRR_PHYS_MASK_VALID,              0x0800
.equ             MTRR_MEMORY_TYPE_UC,               0x00
.equ             MTRR_MEMORY_TYPE_WC,               0x01
.equ             MTRR_MEMORY_TYPE_WT,               0x04
.equ             MTRR_MEMORY_TYPE_WP,               0x05
.equ             MTRR_MEMORY_TYPE_WB,               0x06

.equ             NO_EVICT_MODE,                     0x02E0
.equ             CR0_CACHE_DISABLE,                 0x40000000
.equ             CR0_NO_WRITE,                      0x20000000

#
# Cache init and test values
# These are inverted to flip each bit at least once
#
.equ             CACHE_INIT_VALUE,                  0xA5A5A5A5
.equ             CACHE_TEST_VALUE,                  0x5AA55AA5

#
# Local APIC Register Equates
#
.equ             APIC_ICR_LO,                       0xFEE00300
.equ             ORSELFINIT,                        0x00004500    # OR mask to send INIT IPI to itself
.equ             ORALLBUTSELF,                      0x000C0000    # OR mask to set dest field = "All But Self"

.equ             FVHEADER_LEN_OFF,                  0x30
.equ             FFSHEADER_LEN,                     0x18

.equ             BLOCK_LENGTH_BYTES,                0x800         # BLOCK_LENGTH_BYTES = 2048

#
# Need to check value detail
#
UpdateHeaderStruc:
.equ             UpdateHeaderStrucdHeaderVersion,        0x00          # Header version#
.equ             UpdateHeaderStrucdUpdateRevision,       0x08          # Update revision#
.equ             UpdateHeaderStrucdDate,                 0x10          # Date in binary (08/13/07 as 0x08132007)
.equ             UpdateHeaderStrucdProcessorSignature,   0x18          # CPU type, family, model, stepping
.equ             UpdateHeaderStrucdChecksum,             0x20          # Checksum
.equ             UpdateHeaderStrucdLoaderRevision,       0x28          # Update loader version#
.equ             UpdateHeaderStrucdProcessorFlags,       0x30          # Processor Flags
.equ             UpdateHeaderStrucdDataSize,             0x38          # Size of encrypted data
.equ             UpdateHeaderStrucdTotalSize,            0x40          # Total size of update in bytes
.equ             UpdateHeaderStrucbReserved,             0x48          # 12 bytes reserved
UpdateHeaderStrucEnd:
.equ             UpdateHeaderStrucLength,                0x54          # UpdateHeaderStrucLength = UpdateHeaderStrucEnd - UpdateHeaderStruc #need to check it!!

SecCarInitParams:
# FSP_UPD_HEADER {
.equ             FspUpdHeader,                      0x0000
# }
# FSPT_CORE_UPD {
.equ             MicrocodeCodeAddr,                 0x0020
.equ             MicrocodeCodeSize,                 0x0024
.equ             CodeRegionBase,                    0x0028
.equ             CodeRegionSize,                    0x002C
# }
SecCarInitParamsEnd:

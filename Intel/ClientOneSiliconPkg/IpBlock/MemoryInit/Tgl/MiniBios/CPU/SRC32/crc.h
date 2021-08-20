/**@file
  This file contains generic definitions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2007 - 2017 Intel Corporation.

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

#ifndef  crc_h
#define  crc_h

//-------------------------------------
// Declarations and directives
//-------------------------------------

// CRC revision:
// [15:8] = Major revision number in BCD format
// [7:0]  = Minor revision number in BCD format
#define CRC_REVISION 0x0067

// CRC Release Candidate revision number
// Used to track pre-release versions
#define CRC_RC_REVISION 0x0000

#define inline __inline

// Base Types and Equates
#ifdef CPU_RC_32_MAK
typedef unsigned char       UINT8;
typedef unsigned short      UINT16;
typedef unsigned long       UINT32;
typedef char                INT8;
typedef short               INT16;
typedef long                INT32;
typedef char                CHAR8;
typedef unsigned char       BOOLEAN;
typedef UINT32              UINTN;
typedef INT32               INTN;
#endif // CPU_RC_32_MAK

// Global return codes
#define  SUCCESS  0
#define  FAILURE  1

#ifndef  NULL
#define  NULL ((void *) 0)
#endif

#define  BIT0  1
#define  BIT1  (1 << 1)
#define  BIT2  (1 << 2)
#define  BIT3  (1 << 3)
#define  BIT4  (1 << 4)
#define  BIT5  (1 << 5)
#define  BIT6  (1 << 6)
#define  BIT7  (1 << 7)
#define  BIT8  (1 << 8)
#define  BIT9  (1 << 9)
#define  BIT10 (1 << 10)
#define  BIT11 (1 << 11)
#define  BIT12 (1 << 12)
#define  BIT13 (1 << 13)
#define  BIT14 (1 << 14)
#define  BIT15 (1 << 15)
#define  BIT16 (1 << 16)
#define  BIT17 (1 << 17)
#define  BIT18 (1 << 18)
#define  BIT19 (1 << 19)
#define  BIT20 (1 << 20)
#define  BIT21 (1 << 21)
#define  BIT22 (1 << 22)
#define  BIT23 (1 << 23)
#define  BIT24 (1 << 24)
#define  BIT25 (1 << 25)
#define  BIT26 (1 << 26)
#define  BIT27 (1 << 27)
#define  BIT28 (1 << 28)
#define  BIT29 (1 << 29)
#define  BIT30 (1 << 30)
#define  BIT31 (1 << 31)
#define  BIT32 (0x100000000ULL)

// Reset types needed post execution
#define POST_RESET_CPU_ONLY   0x1
#define POST_RESET_POWERGOOD  0x2

#define ANY_SBSP              0

// Cache init and test values
// These are inverted to flip each bit at least once
#define CACHE_INIT_VALUE         0xA5A5A5A5
#define CACHE_TEST_VALUE         0x5A5A5A5A

// MSR definitions
#define MSR_IA32_PLATFORM_ID     0x0017
#define MSR_APIC_BASE            0x001B
#define MSR_EBC_FREQUENCY_ID     0x002C
#define MSR_SOCKET_ID            0x0039
#define MSR_IA32_FEATURE_CONTROL 0x003A
#define MSR_IA32_BIOS_UPDT_TRIG  0x0079
#define MSR_IA32_BIOS_SIGN_ID    0x008B
#define MSR_PLATFORM_INFO        0x00CE
#define MSR_CLOCK_FLEX_MAX       0x0194
#define MSR_IA32_MISC_ENABLES    0x01A0
#define MSR_NO_EVICT_MODE        0x02E0
#define MSR_CLOCK_CST_CONFIG_CONTROL 0x00E2
#define MSR_IA32_MC7_CTL         0x041C
#define MSR_IA32_MC8_MISC2       0x0288
#define MSR_PCIEXBAR             0x0300

#define MTRR_PHYS_BASE_0      0x0200
#define MTRR_PHYS_MASK_0      0x0201
#define MTRR_PHYS_BASE_1      0x0202
#define MTRR_PHYS_MASK_1      0x0203
#define MTRR_PHYS_BASE_2      0x0204
#define MTRR_PHYS_MASK_2      0x0205
#define MTRR_PHYS_BASE_3      0x0206
#define MTRR_PHYS_MASK_3      0x0207
#define MTRR_PHYS_BASE_4      0x0208
#define MTRR_PHYS_MASK_4      0x0209
#define MTRR_PHYS_BASE_5      0x020A
#define MTRR_PHYS_MASK_5      0x020B
#define MTRR_PHYS_BASE_6      0x020C
#define MTRR_PHYS_MASK_6      0x020D
#define MTRR_PHYS_BASE_7      0x020E
#define MTRR_PHYS_MASK_7      0x020F
#define MTRR_FIX_64K_00000    0x0250
#define MTRR_FIX_16K_80000    0x0258
#define MTRR_FIX_16K_A0000    0x0259
#define MTRR_FIX_4K_C0000     0x0268
#define MTRR_FIX_4K_C8000     0x0269
#define MTRR_FIX_4K_D0000     0x026A
#define MTRR_FIX_4K_D8000     0x026B
#define MTRR_FIX_4K_E0000     0x026C
#define MTRR_FIX_4K_E8000     0x026D
#define MTRR_FIX_4K_F0000     0x026E
#define MTRR_FIX_4K_F8000     0x026F
#define MTRR_DEF_TYPE         0x02FF

#define MTRR_MEMORY_TYPE_UC   0x00
#define MTRR_MEMORY_TYPE_WC   0x01
#define MTRR_MEMORY_TYPE_WT   0x04
#define MTRR_MEMORY_TYPE_WP   0x05
#define MTRR_MEMORY_TYPE_WB   0x06

#define MTRR_DEF_TYPE_E       0x0800
#define MTRR_DEF_TYPE_FE      0x0400
#define MTRR_PHYS_MASK_VALID  0x0800

#define PCIEBAR_ADDRESS       0xE0000000

// PCIEXBAR constant for enable in bit [0]
#define PCIEXBAR_ENABLE       1

// PCIEXBAR constants for size in bits [3:1]
#define PCIEXBAR_64MB         6
#define PCIEXBAR_128MB        7
#define PCIEXBAR_256MB        0

#define CR0_CACHE_DISABLE     0x040000000
#define CR0_NO_WRITE          0x020000000

// Memory-mapped APIC Offsets
#define APIC_ICR_LO             0x300
#define APIC_ICR_HI             0x310
#define APIC_TMR_INITIAL_CNT    0x380
#define APIC_TMR_CURRENT_CNT    0x390

// APIC Timer runs at 133MHz and by default decrements
// the current count register at once per two clocks.
// t = time in milliseconds
// c = APIC Timer Initial Value
// c = (t * 10^(-6) sec) * (133 * 10^6 count/sec) * (1/2 clocks)
// Notice seconds and exponents cancel out leaving count value
// c = (t * 133 / 2)
#define APIC_TMR_1US         (1 * 133 / 2)
#define APIC_TMR_10US        (10 * 133 / 2)
#define APIC_TMR_20US        (20 * 133 / 2)
#define APIC_TMR_100US       (100 * 133 / 2)
#define APIC_TMR_200US       (200 * 133 / 2)
#define APIC_TMR_10MS        (10 * 1000 * 133 / 2)

// SAD and Generic Uncore register mappings
#ifndef CPU_GENERIC_UNCORE_DEV
#define CPU_GENERIC_UNCORE_DEV   0
#endif
#ifndef CPU_GENERIC_UNCORE_FUNC
#define CPU_GENERIC_UNCORE_FUNC  0
#endif
#define DESIRED_CORES_REG        0x80     //(D0:F0:R80h)

#ifndef CPU_SAD_DEV
#define CPU_SAD_DEV              0
#endif
#ifndef CPU_SAD_FUNC
#define CPU_SAD_FUNC             1
#endif
#define SAD_PCIEXBAR_REG         0x50     //(D0:F1:R50h)
#define VENDOR_ID_REG            0

#ifndef CPU_LINK_0_DEV
#define CPU_LINK_0_DEV           2
#endif
#ifndef CPU_LINK_0_FUNC
#define CPU_LINK_0_FUNC          0
#endif
#define CPU_LINK_0_REUT_FUNC     1


#ifndef CPU_LINK_1_DEV
#define CPU_LINK_1_DEV           2
#endif
#ifndef CPU_LINK_1_FUNC
#define CPU_LINK_1_FUNC          4
#endif
#define CPU_LINK_1_REUT_FUNC     5

#define PCH_LP_DEVICE_ID_MASK       0xFFF0  ///< Mask for LP LPC controller Device ID
#define PCH_H_DEVICE_ID_MASK        0xFF00  ///< Mask for H  LPC controller Device ID
#define PCH_SPTLP_DEVICE_ID_MASK    0x9D40  ///< SPT-LP
#define PCH_SPTH_DEVICE_ID_MASK     0xA100  ///< SPT-H
#define PCH_CNLLP_DEVICE_ID_MASK    0x9D80  ///< CNP-LP
#define PCH_CNPH_SS_DEVICE_ID_MASK  0xA200  ///< CNP-H Super SKU
#define PCH_CNPH_DEVICE_ID_MASK     0xA300  ///< CNP-H

// DMI Port ID addresses
#define PID_DMI 0x88

// status codes
#define CRC_START          0x0C01
#define CRC_UCODE_DONE     0x0C02
#define CRC_NEM_DONE       0x0C03
#define CRC_NEM_FAILURE    0x0C04
#define CRC_CSI_RC         0x0C08
#define CRC_MRC            0x0C09
#define CRC_RESET_CHECK    0x0C10
#define CRC_EXIT           0x0C1F
#define CRC_FATAL          BIT15

typedef struct ucode {
    UINT32 version;
    UINT32 revision;
    UINT32 date;
    UINT32 processor;
    UINT32 checksum;
    UINT32 loader;
    UINT32 rsvd[6];
    UINT32 data[500];
} ucode_t;

typedef struct ucode_hdr {
    UINT32 version;
    UINT32 revision;
    UINT32 date;
    UINT32 processor;
    UINT32 checksum;
    UINT32 loader;
    UINT32 flags;
    UINT32 data_size;
    UINT32 total_size;
    UINT32 rsvd[3];
} ucode_hdr_t;

typedef struct ext_sig_hdr {
    UINT32 count;
    UINT32 checksum;
    UINT32 rsvd[3];
} ext_sig_hdr_t;

typedef struct ext_sig {
    UINT32 processor;
    UINT32 flags;
    UINT32 checksum;
} ext_sig_t;

typedef struct cpu_setup_options {
   UINT32   MchBarAddress;
   UINT32   PcieBarAddress;
   UINT32   SmBusBaseAddress;
   UINT32   HpetBaseAddress;
   UINTN    nem_code_addr;
   UINT32   nem_code_size;
   UINTN    nem_data_addr;
   UINT32   nem_data_size;
   UINT32   nem_heap_size;
   UINTN    ucode_region_addr;
   UINT32   ucode_region_size;
   UINTN    crc_exit_addr;
   UINTN    mem_data_addr;
} CPU_SETUP_OPTIONS;

#endif   // crc_h

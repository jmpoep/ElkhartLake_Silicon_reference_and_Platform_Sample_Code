/** @file
  Register names for Host Bridge block
  <b>Conventions</b>:
  - Prefixes:
    - Definitions beginning with "R_" are registers
    - Definitions beginning with "B_" are bits within registers
    - Definitions beginning with "V_" are meaningful values of bits within the registers
    - Definitions beginning with "S_" are register sizes
    - Definitions beginning with "N_" are the bit position
  - In general, SA registers are denoted by "_SA_" in register names
  - Registers / bits that are different between SA generations are denoted by
    "_SA_[generation_name]_" in register/bit names. e.g., "_SA_HSW_"
  - Registers / bits that are different between SKUs are denoted by "_[SKU_name]"
    at the end of the register/bit names
  - Registers / bits of new devices introduced in a SA generation will be just named
    as "_SA_" without [generation_name] inserted.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#ifndef _SA_REGS_HOST_BRIDGE_H_
#define _SA_REGS_HOST_BRIDGE_H_

//
// DEVICE 0 (Memory Controller Hub)
//
#define SA_MC_BUS          0x00
#define SA_MC_DEV          0x00
#define SA_MC_FUN          0x00
#define V_SA_MC_VID        0x8086
#define R_SA_MC_DEVICE_ID  0x02
#define R_SA_MC_CAPID0_B   0xE8

///
/// Maximum number of SDRAM channels supported by the memory controller
///
#define SA_MC_MAX_CHANNELS 2

///
/// Define the maximum number of data bytes on a system with no ECC memory support.
///
#define SA_MC_MAX_BYTES_NO_ECC (8)

///
/// Maximum number of DIMM sockets supported by each channel
///
#define SA_MC_MAX_SLOTS 2

///
/// Maximum number of sides supported per DIMM
///
#define SA_MC_MAX_SIDES 2

///
/// Maximum number of DIMM sockets supported by the memory controller
///
#define SA_MC_MAX_SOCKETS (SA_MC_MAX_CHANNELS * SA_MC_MAX_SLOTS)

///
/// Maximum number of rows supported by the memory controller
///
#define SA_MC_MAX_RANKS (SA_MC_MAX_SOCKETS * SA_MC_MAX_SIDES)

///
/// Maximum number of rows supported by the memory controller
///
#define SA_MC_MAX_ROWS (SA_MC_MAX_SIDES * SA_MC_MAX_SOCKETS)

///
/// Maximum memory supported by the memory controller
/// 4 GB in terms of KB
///
#define SA_MC_MAX_MEM_CAPACITY (4 * 1024 * 1024)

///
/// Define the SPD Address for DIMM 0
///
#define SA_MC_DIMM0_SPD_ADDRESS 0xA0

///
/// Define the maximum number of SPD data bytes on a DIMM.
///
#define SA_MC_MAX_SPD_SIZE (512)

#define V_SA_MC_CAPID0_B_2LM_EN   BIT14   // 2LM
#define V_SA_MC_CAPID0_B_VMD_DIS  BIT2

//
// SA DMI configuration
//

//
// Maximum DMI lanes and bundles supported (x8 and 4 lanes)
//
#define SA_DMI_MAX_LANE                      0x08
#define SA_DMI_MAX_BUNDLE                    0x04

// For CNL DT and H Series, which support x8 DMI
#define SA_DMI_CNL_DT_HALO_MAX_LANE          SA_DMI_MAX_LANE
#define SA_DMI_CNL_DT_HALO_MAX_BUNDLE        SA_DMI_MAX_BUNDLE

// For non CNL DT and H Series, which support x4 DMI
// ULT, ULX series and KBL- based refresh CPU series
//
#define SA_DMI_NON_CNL_DT_HALO_MAX_LANE      0x04
#define SA_DMI_NON_CNL_DT_HALO_MAX_BUNDLE    0x02

#define SA_DMI_KBL_MAX_LANE                  0x04
#define SA_DMI_KBL_MAX_BUNDLE                0x02


//
// IceLake Mobile SA Device IDs B0:D0:F0
//
#define V_SA_DEVICE_ID_ICL_MB_ULT_1 0x8A12   ///< Icelake Ult (ICL-U 4+2)
#define V_SA_DEVICE_ID_ICL_MB_ULT_2 0x8A14   ///< Icelake Ult (ICL-U 4+3e)
#define V_SA_DEVICE_ID_ICL_MB_ULT_3 0x8A02   ///< Icelake Ult (ICL-U 2+2)
#define V_SA_DEVICE_ID_ICL_MB_ULX_1 0x8A10   ///< Icelake Ulx (ICL-Y 4+2)
#define V_SA_DEVICE_ID_ICL_MB_ULX_2 0x8A00   ///< Icelake Ulx (ICL-Y 2+2)
//
// Icelake CPU Halo SA Device IDs B0:D0:F0
//
#define V_SA_DEVICE_ID_ICL_HALO_1   0x8A28   ///< Icelake Halo (6+1) SA DID
#define V_SA_DEVICE_ID_ICL_HALO_2   0x8A38   ///< Icelake Halo (8+2) SA DID
//
// Icelake CPU Desktop SA Device IDs B0:D0:F0
//
#define V_SA_DEVICE_ID_ICL_DT_1     0x8A2C   ///< Icelake Desktop (6+1) SA DID
#define V_SA_DEVICE_ID_ICL_DT_2     0x8A1C   ///< Icelake Desktop (4+1) SA DID
//
// ElkhartLake Mobile SA Device IDs B0:D0:F0
//
#define V_SA_DEVICE_ID_EHL_0        0x4500   ///< Super SKU1

#define V_SA_DEVICE_ID_EHL_1        0x4510   ///< Super SKU2
#define V_SA_DEVICE_ID_EHL_2        0x4512   ///< SKU 2 CORE
#define V_SA_DEVICE_ID_EHL_3        0x4514   ///< SKU 2 CORE
#define V_SA_DEVICE_ID_EHL_4        0x4516   ///< SKU 2 CORE
#define V_SA_DEVICE_ID_EHL_5        0x4518   ///< SKU 2 CORE
#define V_SA_DEVICE_ID_EHL_6        0x451A   ///< SKU 2 CORE
#define V_SA_DEVICE_ID_EHL_7        0x451C   ///< SKU 2 CORE
#define V_SA_DEVICE_ID_EHL_8        0x451E   ///< SKU 2 CORE

#define V_SA_DEVICE_ID_EHL_9        0x4520   ///< Super SKU3
#define V_SA_DEVICE_ID_EHL_10       0x4522   ///< SKU 4 CORE
#define V_SA_DEVICE_ID_EHL_11       0x4524   ///< SKU 4 CORE
#define V_SA_DEVICE_ID_EHL_12       0x4526   ///< SKU 4 CORE
#define V_SA_DEVICE_ID_EHL_13       0x4528   ///< SKU 4 CORE
#define V_SA_DEVICE_ID_EHL_14       0x452A   ///< SKU 4 CORE
#define V_SA_DEVICE_ID_EHL_15       0x452C   ///< SKU 4 CORE
#define V_SA_DEVICE_ID_EHL_16       0x452E   ///< SKU 4 CORE

#define V_SA_DEVICE_ID_EHL_17       0x4530   ///< Super SKU4
#define V_SA_DEVICE_ID_EHL_18       0x4532   ///< SKU 4 CORE (FUSA)
#define V_SA_DEVICE_ID_EHL_19       0x4534   ///< SKU 4 CORE
#define V_SA_DEVICE_ID_EHL_20       0x4536   ///< SKU 4 CORE
#define V_SA_DEVICE_ID_EHL_21       0x4538   ///< SKU 4 CORE
#define V_SA_DEVICE_ID_EHL_22       0x453A   ///< SKU 4 CORE
#define V_SA_DEVICE_ID_EHL_23       0x453C   ///< SKU 4 CORE

#define CPU_DEVICE_ID_EHL_1       0x4522   ///< SKU 1
#define CPU_DEVICE_ID_EHL_2       0x4524   ///< SKU 2
#define CPU_DEVICE_ID_EHL_3       0x4512   ///< SKU 3
#define CPU_DEVICE_ID_EHL_4       0x4526   ///< SKU 4
#define CPU_DEVICE_ID_EHL_5       0x4514   ///< SKU 5
#define CPU_DEVICE_ID_EHL_6       0x4528   ///< SKU 6
#define CPU_DEVICE_ID_EHL_7       0x452A   ///< SKU 7
#define CPU_DEVICE_ID_EHL_8       0x4516   ///< SKU 8
#define CPU_DEVICE_ID_EHL_9       0x452C   ///< SKU 9
#define CPU_DEVICE_ID_EHL_10      0x452E   ///< SKU 10
#define CPU_DEVICE_ID_EHL_11      0x4518   ///< SKU 11
#define CPU_DEVICE_ID_EHL_12      0x4532   ///< SKU 12

//
// TigerLake Mobile SA Device IDs B0:D0:F0
//
#define V_SA_DEVICE_ID_TGL_MB_ULT_1 0x9A14   ///< TigerLake Ult (TGL-U 4+2)
#define V_SA_DEVICE_ID_TGL_MB_ULT_2 0x9A04   ///< TigerLake Ult (TGL-U 2+2)

#define V_SA_DEVICE_ID_TGL_MB_ULX_1 0x9A12   ///< TigerLake Ulx (TGL-Y 4+2)
#define V_SA_DEVICE_ID_TGL_MB_ULX_2 0x9A02   ///< TigerLake Ulx (TGL-Y 2+2)
//
// TigerLake CPU Halo SA Device IDs B0:D0:F0
//
#define V_SA_DEVICE_ID_TGL_HALO_1   0x9A28   ///< TigerLake Halo (6+1) SA DID
#define V_SA_DEVICE_ID_TGL_HALO_2   0x9A38   ///< TigerLake Halo (8+2) SA DID
//
// TigerLake CPU Desktop SA Device IDs B0:D0:F0
//
#define V_SA_DEVICE_ID_TGL_DT_1     0x9A2C   ///< TigerLake Desktop (6+1) SA DID
#define V_SA_DEVICE_ID_TGL_DT_2     0x9A1C   ///< TigerLake Desktop (4+1) SA DID

///
///

/**
 <b>Description</b>:
  This is the base address for the PCI Express Egress Port MMIO Configuration space.  There is no physical memory within this 4KB window that can be addressed.  The 4KB reserved by this register does not alias to any PCI 2.3 compliant memory mapped space.  On reset, the EGRESS port MMIO configuration space is disabled and must be enabled by writing a 1 to PXPEPBAREN [Dev 0, offset 40h, bit 0].
  All the bits in this register are locked in LT mode.
**/
#define R_SA_PXPEPBAR  (0x40)
//
// Description of PXPEPBAREN (0:0)
// - 0:  PXPEPBAR is disabled and does not claim any memory
// - 1:  PXPEPBAR memory mapped accesses are claimed and decoded appropriately
// - This register is locked by LT.
//
#define N_SA_PXPEPBAR_PXPEPBAREN_OFFSET  (0x0)
#define S_SA_PXPEPBAR_PXPEPBAREN_WIDTH   (0x1)
#define B_SA_PXPEPBAR_PXPEPBAREN_MASK    (0x1)
#define V_SA_PXPEPBAR_PXPEPBAREN_DEFAULT (0x0)
//
// Description of PXPEPBAR (12:38)
// - This field corresponds to bits 38 to 12 of the base address PCI Express Egress Port MMIO configuration space.  BIOS will program this register resulting in a base address for a 4KB block of contiguous memory address space.  This register ensures that a naturally aligned 4KB space is allocated within the first 512GB of addressable memory space.  System Software uses this base address to program the PCI Express Egress Port MMIO register set.  All the bits in this register are locked in LT mode.
//
#define N_SA_PXPEPBAR_PXPEPBAR_OFFSET  (0xc)
#define S_SA_PXPEPBAR_PXPEPBAR_WIDTH   (0x1b)
#define B_SA_PXPEPBAR_PXPEPBAR_MASK    (0x7ffffff000)
#define V_SA_PXPEPBAR_PXPEPBAR_DEFAULT (0x0)

/**
 <b>Description</b>:
 - This is the base address for the Host Memory Mapped Configuration space.  There is no physical memory within this 32KB window that can be addressed.  The 32KB reserved by this register does not alias to any PCI 2.3 compliant memory mapped space.  On reset, the Host MMIO Memory Mapped Configuation space is disabled and must be enabled by writing a 1 to MCHBAREN [Dev 0, offset48h, bit 0].
 - All the bits in this register are locked in LT mode.
 - The register space contains memory control, initialization, timing, and buffer strength registers; clocking registers; and power and thermal management registers.
**/
#define R_SA_MCHBAR  (0x48)
/**
 Description of MCHBAREN (0:0)
 - 0: MCHBAR is disabled and does not claim any memory
 - 1: MCHBAR memory mapped accesses are claimed and decoded appropriately
 - This register is locked by LT.
**/
#define N_SA_MCHBAR_MCHBAREN_OFFSET  (0x0)
#define S_SA_MCHBAR_MCHBAREN_WIDTH   (0x1)
#define B_SA_MCHBAR_MCHBAREN_MASK    (0x1)
#define V_SA_MCHBAR_MCHBAREN_DEFAULT (0x0)
/**
Description of MCHBAR (19:38)
- This field corresponds to bits 38 to 19 of the base address Host Memory Mapped configuration space.  BIOS will program this register resulting in a base address for a 512KB block of contiguous memory address space.  This register ensures that a naturally aligned 512KB space is allocated within the first 512GB of addressable memory space. System Software uses this base address to program the Host Memory Mapped register set. All the bits in this register are locked in LT mode.
**/
#define N_SA_MCHBAR_MCHBAR_OFFSET  (0x13)
#define S_SA_MCHBAR_MCHBAR_WIDTH   (0x14)
#define B_SA_MCHBAR_MCHBAR_MASK    (0x7ffff80000ULL)
#define V_SA_MCHBAR_MCHBAR_DEFAULT (0x0)

/**
 <b>Description</b>:
 - All the bits in this register are LT lockable.
**/
#define R_SA_GTTMMADR_GGC_OFFSET (0x108040)
#define R_SA_GGC (0x50)
/**
 Description of GGCLCK (0:0)
 - When set to 1b, this bit will lock all bits in this register.
**/
#define N_SA_GGC_GGCLCK_OFFSET   (0x0)
#define S_SA_GGC_GGCLCK_WIDTH    (0x1)
#define B_SA_GGC_GGCLCK_MASK     (0x1)
#define V_SA_GGC_GGCLCK_DEFAULT  (0x0)
/**
 Description of IVD (1:1)
 - 0: Enable.  Device 2 (IGD) claims VGA memory and IO cycles, the Sub-Class Code within Device 2 Class Code register is 00.
 - 1: Disable.  Device 2 (IGD) does not claim VGA cycles (Mem and IO), and the Sub- Class Code field within Device 2 function 0 Class Code register is 80.
 - BIOS Requirement:  BIOS must not set this bit to 0 if the GMS field (bits 7:3 of this register) pre-allocates no memory.
 - This bit MUST be set to 1 if Device 2 is disabled either via a fuse or fuse override (CAPID0[46] = 1) or via a register (DEVEN[3] = 0).
 - This register is locked by LT lock.
**/
#define N_SA_GGC_IVD_OFFSET  (0x1)
#define S_SA_GGC_IVD_WIDTH   (0x1)
#define B_SA_GGC_IVD_MASK    (0x2)
#define V_SA_GGC_IVD_DEFAULT (0x0)
#define V_SA_GGC_GMS_DIS     0
#define V_SA_GGC_GMS_32MB    1
#define V_SA_GGC_GMS_64MB    2
/**
 Description of GMS (8:15)
 - This field is used to select the amount of Main Memory that is pre-allocated to support the Internal Graphics device in VGA (non-linear) and Native (linear) modes.  The BIOS ensures that memory is pre-allocated only when Internal graphics is enabled.
 - This register is also LT lockable.
 - Valid options are 0 (0x0) to 2048MB (0x40) in multiples of 32 MB
 - All other values are reserved
 - Hardware does not clear or set any of these bits automatically based on IGD being disabled/enabled.
 - BIOS Requirement: BIOS must not set this field to 0h if IVD (bit 1 of this register) is 0.
**/
#define N_SA_GGC_GMS_OFFSET  (0x8)
#define S_SA_GGC_GMS_WIDTH   (0x8)
#define B_SA_GGC_GMS_MASK    (0xff00)
#define V_SA_GGC_GMS_DEFAULT (0x01)

/**
 Description of GGMS (6:7)
 - This field is used to select the amount of Main Memory that is pre-allocated to support the Internal Graphics Translation Table.  The BIOS ensures that memory is pre-allocated only when Internal graphics is enabled.
 - GSM is assumed to be a contiguous physical DRAM space with DSM, and BIOS needs to allocate a contiguous memory chunk.  Hardware will derive the base of GSM from DSM only using the GSM size programmed in the register.
 - Valid options:
 - 0h: 0 MB of memory pre-allocated for GTT.
 - 1h: 2 MB of memory pre-allocated for GTT.
 - 2h: 4 MB of memory pre-allocated for GTT.
 - 3h: 8 MB of memory pre-allocated for GTT.
 - Others: Reserved
 - Hardware functionality in case of programming this value to Reserved is not guaranteed.
**/
#define N_SA_GGC_GGMS_OFFSET  (0x6)
#define S_SA_GGC_GGMS_WIDTH   (0x2)
#define B_SA_GGC_GGMS_MASK    (0xc0)
#define V_SA_GGC_GGMS_DEFAULT (2)
#define V_SA_GGC_GGMS_DIS     0
#define V_SA_GGC_GGMS_2MB     1
#define V_SA_GGC_GGMS_4MB     2
#define V_SA_GGC_GGMS_8MB     3

/**
 Description of VAMEN (2:2)
 - Enables the use of the iGFX enbines for Versatile Acceleration.
 - 1 - iGFX engines are in Versatile Acceleration Mode.  Device 2 Class Code is 048000h.
 - 0 - iGFX engines are in iGFX Mode.  Device 2 Class Code is 030000h.
**/
#define N_SA_GGC_VAMEN_OFFSET  (0x2)
#define S_SA_GGC_VAMEN_WIDTH   (0x1)
#define B_SA_GGC_VAMEN_MASK    (0x4)
#define V_SA_GGC_VAMEN_DEFAULT (0x0)

/**
 Description:
 - Allows for enabling/disabling of PCI devices and functions that are within the CPU package. The table below the bit definitions describes the behavior of all combinations of transactions to devices controlled by this register.
  All the bits in this register are LT Lockable.
**/
#define R_SA_DEVEN (0x54)

/**
 Description of D0EN (0:0)
 - Bus 0 Device 0 Function 0 may not be disabled and is therefore hardwired to 1.
**/
#define N_SA_DEVEN_D0EN_OFFSET   (0x0)
#define S_SA_DEVEN_D0EN_WIDTH    (0x1)
#define B_SA_DEVEN_D0EN_MASK     (0x1)
#define V_SA_DEVEN_D0EN_DEFAULT  (0x1)
/**
 Description of D2EN (4:4)
 - 0:  Bus 0 Device 2 is disabled and hidden
 - 1:  Bus 0 Device 2 is enabled and visible
 - This bit will remain 0 if Device 2 capability is disabled.
**/
#define N_SA_DEVEN_D2EN_OFFSET   (0x4)
#define S_SA_DEVEN_D2EN_WIDTH    (0x1)
#define B_SA_DEVEN_D2EN_MASK     (0x10)
#define V_SA_DEVEN_D2EN_DEFAULT  (0x10)

/**
 Description of D1F0EN (3:3)
 - 0: Bus 0 Device 1 Function 0 is disabled and not visible.
 - 1: Bus 0 Device 1 Function 0 is enabled and visible.
 - This bit will remain 0 if Device 1 Function 0 capability is disabled.
**/
#define N_SA_DEVEN_D1F0EN_OFFSET   (0x3)
#define S_SA_DEVEN_D1F0EN_WIDTH    (0x1)
#define B_SA_DEVEN_D1F0EN_MASK     (0x8)
#define V_SA_DEVEN_D1F0EN_DEFAULT  (0x8)
/**
 Description of D1F1EN (2:2)
 - 0: Bus 0 Device 1 Function 1 is disabled and not visible.
 - 1: Bus 0 Device 1 Function 1 is enabled and visible.
 - This bit will remain 0 if Device 1 Function 1 capability is disabled.
**/
#define N_SA_DEVEN_D1F1EN_OFFSET   (0x2)
#define S_SA_DEVEN_D1F1EN_WIDTH    (0x1)
#define B_SA_DEVEN_D1F1EN_MASK     (0x4)
#define V_SA_DEVEN_D1F1EN_DEFAULT  (0x4)
/**
 Description of D1F2EN (1:1)
 - 0: Bus 0 Device 1 Function 2 is disabled and not visible.
 - 1: Bus 0 Device 1 Function 2 is enabled and visible.
 - This bit will remain 0 if Device 1 Function 2 capability is disabled.
**/
#define N_SA_DEVEN_D1F2EN_OFFSET   (0x1)
#define S_SA_DEVEN_D1F2EN_WIDTH    (0x1)
#define B_SA_DEVEN_D1F2EN_MASK     (0x2)
#define V_SA_DEVEN_D1F2EN_DEFAULT  (0x2)

// 2LM
/**
Description of D3F0EN (5:5) NVME
- 0: Bus 0 Device 3 Function 0 is disabled and not visible.
- 1: Bus 0 Device 3 Function 0 is enabled and visible.
- This bit will remain 0 if Device 3 Function 0 capability is disabled.
**/
#define N_SA_DEVEN_D3F0EN_OFFSET   (0x5)
#define S_SA_DEVEN_D3F0EN_WIDTH    (0x1)
#define B_SA_DEVEN_D3F0EN_MASK     (0x20)
#define V_SA_DEVEN_D3F0EN_DEFAULT  (0x20)

// 2LM
/**
Description of D3F7EN (6:6) 2LM
- 0: Bus 0 Device 3 Function 7 is disabled and not visible.
- 1: Bus 0 Device 3 Function 7 is enabled and visible.
- This bit will remain 0 if Device 3 Function 7 capability is disabled.
**/
#define N_SA_DEVEN_D3F7EN_OFFSET   (0x6)
#define S_SA_DEVEN_D3F7EN_WIDTH    (0x1)
#define B_SA_DEVEN_D3F7EN_MASK     (0x40)
#define V_SA_DEVEN_D3F7EN_DEFAULT  (0x40)

/**
 Description of D5EN (10:10)
 - 0: Bus 0 Device 5 is disabled and not visible.
 - 1: Bus 0 Device 5 is enabled and visible.
 - This bit will remain 0 if Device 5 capability is disabled.
**/
#define N_SA_DEVEN_D5EN_OFFSET   (0xA)
#define S_SA_DEVEN_D5EN_WIDTH    (0x1)
#define B_SA_DEVEN_D5EN_MASK     (0x400)
#define V_SA_DEVEN_D5EN_DEFAULT  (0x400)
/**
 Description of D6EN (13:13)
 - 0: Bus 0 Device 6 is disabled and not visible.
 - 1: Bus 0 Device 6 is enabled and visible.
 - This bit will remain 0 if Device 6 capability is disabled.
**/
#define N_SA_DEVEN_D6EN_OFFSET   (0xD)
#define S_SA_DEVEN_D6EN_WIDTH    (0x1)
#define B_SA_DEVEN_D6EN_MASK     (0x2000)
#define V_SA_DEVEN_D6EN_DEFAULT  (0x2000)
/**
 Description of D8EN (15:15)
 - 0: Bus 0 Device 8 is disabled and not visible.
 - 1: Bus 0 Device 8 is enabled and visible.
 - This bit will remain 0 if Device 8 capability is disabled.
**/
#define N_SA_DEVEN_D8EN_OFFSET   (0xF)
#define S_SA_DEVEN_D8EN_WIDTH    (0x1)
#define B_SA_DEVEN_D8EN_MASK     (0x8000)
#define V_SA_DEVEN_D8EN_DEFAULT  (0x8000)
/**
 Description of D4EN (7:7)
 - 0: Bus 0 Device 4 is disabled and not visible.
 - 1: Bus 0 Device 4 is enabled and visible.
 - This bit will remain 0 if Device 4 capability is disabled.
 Update: DEVEN register change
**/
#define N_SA_DEVEN_D4EN_OFFSET   (0x7)
#define S_SA_DEVEN_D4EN_WIDTH    (0x1)
#define B_SA_DEVEN_D4EN_MASK     (0x80)
#define V_SA_DEVEN_D4EN_DEFAULT  (0x80)

/**
Description of D14F0EN (14:14)
- 0: Bus 0 Device 14 Function 0 is disabled and not visible.
- 1: Bus 0 Device 14 Function 0 is enabled and visible.
- Non-production BIOS code should provide a setup option to enable Bus 0 Device 14 Function 0.  When enabled, Bus 0 Device 14 Function 0 must be initialized in accordance to standard PCI device initialization procedures.
Update: DEVEN register change
**/
#define N_SA_DEVEN_D14F0EN_OFFSET   (0xe)
#define S_SA_DEVEN_D14F0EN_WIDTH    (0x1)
#define B_SA_DEVEN_D14F0EN_MASK     (0x4000)
#define V_SA_DEVEN_D14F0EN_DEFAULT  (0x0)


/**
 Description of ITH (12:12)
 - 0: Intel Trace Hub is disabled.
 - 1: Intel Trace Hub is enabled.
 Update: DEVEN register change
**/
#define N_SA_DEVEN_ITH_OFFSET    (0xC)
#define S_SA_DEVEN_ITH_WIDTH     (0x1)
#define B_SA_DEVEN_ITH_MASK      (0x1000)
#define V_SA_DEVEN_ITH_DEFAULT   (0x1)

/**
 Description of EPBAREN (27:27)
 - 0:  EPBAR is disabled and does not claim any memory.
 - 1:  EPBAR memory mapped accesses are claimed and decoded approprately. This bit is Intel Reserved
**/
#define N_SA_DEVEN_EPBAREN_OFFSET  (0x1b)
#define S_SA_DEVEN_EPBAREN_WIDTH   (0x1)
#define B_SA_DEVEN_EPBAREN_MASK    (0x8000000)
#define V_SA_DEVEN_EPBAREN_DEFAULT (0x0)
/**
 Description of MCHBAREN (28:28)
 - 0:  MCHBAR is disabled and does not claim any memory.
 - 1:  MCHBAR memory mapped accesses are claimed and decoded approprately. This bit is Intel Reserved
**/
#define N_SA_DEVEN_MCHBAREN_OFFSET   (0x1c)
#define S_SA_DEVEN_MCHBAREN_WIDTH    (0x1)
#define B_SA_DEVEN_MCHBAREN_MASK     (0x10000000)
#define V_SA_DEVEN_MCHBAREN_DEFAULT  (0x0)
/**
 Description of DMIBAREN (29:29)
 - 0:  DMIBAR is disabled and does not claim any memory.
 - 1:  DMIBAR memory mapped accesses are claimed and decoded approprately. This bit is Intel Reserved
**/
#define N_SA_DEVEN_DMIBAREN_OFFSET   (0x1d)
#define S_SA_DEVEN_DMIBAREN_WIDTH    (0x1)
#define B_SA_DEVEN_DMIBAREN_MASK     (0x20000000)
#define V_SA_DEVEN_DMIBAREN_DEFAULT  (0x0)
/**
 Description of PCIEXBAREN (31:31)
 - 0:  The PCIEXBAR register is disabled. Memory read and write transactions proceed as if there were no PCIEXBAR register. PCIEXBAR bits 31:28 are R/W with no functionality behind them.
 - 1:  The PCIEXBAR register is enabled. Memory read and write transactions whose address bits 31:28 match PCIEXBAR 31:28 will be translated to configuration reads and writes within the GMCH. These translated cycles are routed as shown in the table above.
**/
#define N_SA_DEVEN_PCIEXBAREN_OFFSET   (0x1f)
#define S_SA_DEVEN_PCIEXBAREN_WIDTH    (0x1)
#define B_SA_DEVEN_PCIEXBAREN_MASK     (0x80000000)
#define V_SA_DEVEN_PCIEXBAREN_DEFAULT  (0x0)
/**
 Description of RSVD (31:31)
**/
#define N_SA_DEVEN_RSVD_OFFSET   (0x1f)
#define S_SA_DEVEN_RSVD_WIDTH    (0x1)
#define B_SA_DEVEN_RSVD_MASK     (0x80000000)
#define V_SA_DEVEN_RSVD_DEFAULT  (0x0)

/**
 Description
 - Protected Audio Video Path Control
 - All the bits in this register are locked by LT.  When locked the R/W bits are RO.
**/

#define R_SA_DEV2_PAVPC                 (0xF0)
#define R_SA_GTTMMADR_PAVPC_OFFSET (0x1082C0)
#define R_SA_PAVPC (0x58)

/**
 Description of PCME (0:0)
 - This field enables Protected Content Memory within Graphics Stolen Memory.
 - This register is locked (becomes read-only) when PAVPLCK = 1b.
 - This register is read-only (stays at 0b) when PAVP fuse is set to "disabled"
 - 0: Protected Content Memory is disabled
 - 1: Protected Content Memory is enabled
**/
#define N_SA_PAVPC_PCME_OFFSET   (0x0)
#define S_SA_PAVPC_PCME_WIDTH    (0x1)
#define B_SA_PAVPC_PCME_MASK     (0x1)
#define V_SA_PAVPC_PCME_MASK     (0x0)
/**
 Description of PAVPE (1:1)
 - 0: PAVP path is disabled
 - 1: PAVP path is enabled
 - This register is locked (becomes read-only) when PAVPLCK = 1b
 - This register is read-only (stays at 0b) when PAVP capability is set to "disabled" as defined by CAPID0_B[PAVPE].
**/
#define N_SA_PAVPC_PAVPE_OFFSET  (0x1)
#define S_SA_PAVPC_PAVPE_WIDTH   (0x1)
#define B_SA_PAVPC_PAVPE_MASK    (0x2)
#define V_SA_PAVPC_PAVPE_DEFAULT (0x0)
/**
 Description of PAVPLCK (2:2)
 - This bit will lock all writeable contents in this register when set (including itself).
 - This bit will be locked if PAVP is fused off.
**/
#define N_SA_PAVPC_PAVPLCK_OFFSET  (0x2)
#define S_SA_PAVPC_PAVPLCK_WIDTH   (0x1)
#define B_SA_PAVPC_PAVPLCK_MASK    (0x4)
#define V_SA_PAVPC_PAVPLCK_DEFAULT (0x0)
/**
 Description of HVYMODSEL (3:3)
 - 0b   Lite Mode
**/
#define N_SA_PAVPC_HVYMODSEL_OFFSET  (0x3)
#define S_SA_PAVPC_HVYMODSEL_WIDTH   (0x1)
#define B_SA_PAVPC_HVYMODSEL_MASK    (0x8)
#define V_SA_PAVPC_HVYMODSEL_DEFAULT (0x0)

/**
 Description of WOPCMSZ (8:7)
 - 00b - 1MB (default)
**/
#define N_SA_PAVPC_WOPCMSZ_OFFSET  (0x7)
#define S_SA_PAVPC_WOPCMSZ_WIDTH   (0x2)
#define B_SA_PAVPC_WOPCMSZ_MASK    (0x180)
#define V_SA_PAVPC_WOPCMSZ_DEFAULT (0x0)

/**
 Description of PCMBASE (20:31)
 - This field is used to set the base of Protected Content Memory.
 - This corresponds to bits 31:20 of the system memory address range, giving a 1MB granularity. This value MUST be at least 1MB above the base and below the top of stolen memory.
 - This register is locked (becomes read-only) when PAVPE = 1b.
**/
#define N_SA_PAVPC_PCMBASE_OFFSET  (0x14)
#define S_SA_PAVPC_PCMBASE_WIDTH   (0xc)
#define B_SA_PAVPC_PCMBASE_MASK    (0xfff00000)
#define V_SA_PAVPC_PCMBASE_DEFAULT (0x0)

#define R_SA_DPR (0x5c) ///< DMA protected range register
/**
 Description of LOCK (0:0)
 - This bit will lock all writeable settings in this register, including itself.
**/
#define N_SA_DPR_LOCK_OFFSET   (0x0)
#define S_SA_DPR_LOCK_WIDTH    (0x1)
#define B_SA_DPR_LOCK_MASK     (0x1)
#define V_SA_DPR_LOCK_DEFAULT  (0x0)
/**
 Description of PRS (1:1)
 - This field indicates the status of DPR.
 - 0: DPR protection disabled
 - 1: DPR protection enabled
**/
#define N_SA_DPR_PRS_OFFSET   (0x1)
#define S_SA_DPR_PRS_WIDTH    (0x1)
#define B_SA_DPR_PRS_MASK     (0x2)
#define V_SA_DPR_PRS_DEFAULT  (0x0)
/**
 Description of EPM (2:2)
 - This field controls DMA accesses to the DMA Protected Range (DPR) region.
 - 0: DPR is disabled
 - 1: DPR is enabled.  All DMA requests accessing DPR region are blocked.
 - HW reports the status of DPR enable/disable through the PRS field in this register.
**/
#define N_SA_DPR_EPM_OFFSET  (0x2)
#define S_SA_DPR_EPM_WIDTH   (0x1)
#define B_SA_DPR_EPM_MASK    (0x4)
#define V_SA_DPR_EPM_DEFAULT (0x0)
/**
 Description of DPRSIZE (11:4)
 - This field is used to specify the size of memory protected from DMA access in MB
 - The maximum amount of memory that will be protected is 255MB
 - The Top of protected range is the base of TSEG-1
**/
#define N_DPR_DPRSIZE_OFFSET  (0x4)
#define V_DPR_DPRSIZE_WIDTH   (0x8)
#define V_DPR_DPRSIZE_MASK    (0xFF0)
#define V_DPR_DPRSIZE_DEFAULT (0x0)
/**
 Description of TOPOFDPR (31:20)
 - This is the Top address 1 of DPR - Base of TSEG
**/
#define N_SA_DPR_TOPOFDPR_OFFSET  (20)
#define S_SA_DPR_TOPOFDPR_WIDTH   (0xC)
#define B_SA_DPR_TOPOFDPR_MASK    (0xFFF00000)
#define V_SA_DPR_TOPOFDPR_DEFAULT (0x0)

/**
 Description:
  This is the base address for the PCI Express configuration space.  This window of addresses contains the 4KB of configuration space for each PCI Express device that can potentially be part of the PCI Express Hierarchy associated with the Uncore.  There is no actual physical memory within this window of up to 256MB that can be addressed.  The actual size of this range is determined by a field in this register.
  Each PCI Express Hierarchy requires a PCI Express BASE register.  The Uncore supports one PCI Express Hierarchy.  The region reserved by this register does not alias to any PCI2.3 compliant memory mapped space.  For example, the range reserved for MCHBAR is outside of PCIEXBAR space.
  On reset, this register is disabled and must be enabled by writing a 1 to the enable field in this register.  This base address shall be assigned on a boundary consistent with the number of buses (defined by the length field in this register), above TOLUD and still within 39-bit addressable memory space.
  The PCI Express Base Address cannot be less than the maximum address written to the Top of physical memory register (TOLUD).  Software must guarantee that these ranges do not overlap with known ranges located above TOLUD.
  Software must ensure that the sum of the length of the enhanced configuration region + TOLUD + any other known ranges reserved above TOLUD is not greater than the 39-bit addessable limit of 512GB.  In general, system implementation and the number of PCI/PCI Express/PCI-X buses supported in the hierarchy will dictate the length of the region.
  All the bits in this register are locked in LT mode.
**/
#define R_SA_PCIEXBAR  (0x60)
/**
 Description of PCIEXBAREN (0:0)
 - 0: The PCIEXBAR register is disabled.  Memory read and write transactions proceed s if there were no PCIEXBAR register.  PCIEXBAR bits 38:26 are R/W with no functionality behind them.
 - 1: The PCIEXBAR register is enabled.  Memory read and write transactions whose address bits 38:26 match PCIEXBAR will be translated to configuration reads and writes within the Uncore.  These Translated cycles are routed as shown in the above table.
 - This register is locked by LT.
**/
#define N_SA_PCIEXBAR_PCIEXBAREN_OFFSET  (0x0)
#define S_SA_PCIEXBAR_PCIEXBAREN_WIDTH   (0x1)
#define B_SA_PCIEXBAR_PCIEXBAREN_MASK    (0x1)
#define V_SA_PCIEXBAR_PCIEXBAREN_DEFAULT (0x0)
/**
 Description of LENGTH (1:3)
 - This field describes the length of this region.
 - 00: 256MB (buses 0-255).  Bits 38:28 are decoded in the PCI Express Base Address Field.
 - 01: 128MB (buses 0-127).  Bits 38:27 are decoded in the PCI Express Base Address Field.
 - 10: 64MB (buses 0-63).  Bits 38:26 are decoded in the PCI Express Base Address Field.
 - 11: 512MB (buses 0-255)(Segment0 + Segment1).  Bits 38:29 are decoded in the PCI Express Base Address Field.
 - This register is locked by LT.
**/
#define N_SA_PCIEXBAR_LENGTH_OFFSET  (0x1)
#define S_SA_PCIEXBAR_LENGTH_WIDTH   (0x3)
#define B_SA_PCIEXBAR_LENGTH_MASK    (0xE)
#define V_SA_PCIEXBAR_LENGTH_DEFAULT (0x0)

#define V_SA_PCIEXBAR_LENGTH_512MB   (0x3)
#define V_SA_PCIEXBAR_LENGTH_256MB   (0x0)
#define V_SA_PCIEXBAR_LENGTH_128MB   (0x1)
#define V_SA_PCIEXBAR_LENGTH_64MB    (0x2)
/**
 Description of ADMSK64 (26:26)
  This bit is either part of the PCI Express Base Address (R/W) or part of the Address Mask (RO, read 0b), depending on the value of bits [2:1] in this register.
**/
#define N_SA_PCIEXBAR_ADMSK64_OFFSET   (0x1a)
#define S_SA_PCIEXBAR_ADMSK64_WIDTH    (0x1)
#define B_SA_PCIEXBAR_ADMSK64_MASK     (0x4000000)
#define V_SA_PCIEXBAR_ADMSK64_DEFAULT  (0x0)
/**
 Description of ADMSK128 (27:27)
  This bit is either part of the PCI Express Base Address (R/W) or part of the Address Mask (RO, read 0b), depending on the value of bits [2:1] in this register.
**/
#define N_SA_PCIEXBAR_ADMSK128_OFFSET  (0x1b)
#define S_SA_PCIEXBAR_ADMSK128_WIDTH   (0x1)
#define B_SA_PCIEXBAR_ADMSK128_MASK    (0x8000000)
#define V_SA_PCIEXBAR_ADMSK128_DEFAULT (0x0)

/**
Description of ADMSK256 (28:28)
This bit is either part of the PCI Express Base Address (R/W) or part of the Address Mask (RO, read 0b), depending on the value of bits [2:1] in this register.
**/
#define N_SA_PCIEXBAR_ADMSK256_OFFSET  (0x1c)
#define S_SA_PCIEXBAR_ADMSK256_WIDTH   (0x1)
#define B_SA_PCIEXBAR_ADMSK256_MASK    (0x10000000)
#define V_SA_PCIEXBAR_ADMSK256_DEFAULT (0x0)
/**
Description of ADMSK512 (29:29)
This bit is either part of the PCI Express Base Address (R/W) or part of the Address Mask (RO, read 0b), depending on the value of bits [2:1] in this register.
**/
#define N_SA_PCIEXBAR_ADMSK512_OFFSET  (0x1d)
#define S_SA_PCIEXBAR_ADMSK512_WIDTH   (0x1)
#define B_SA_PCIEXBAR_ADMSK512_MASK    (0x20000000)
#define V_SA_PCIEXBAR_ADMSK512_DEFAULT (0x0)
/**
Description of ADMSK512 (30:30)
This bit is either part of the PCI Express Base Address (R/W) or part of the Address Mask (RO, read 0b), depending on the value of bits [2:1] in this register.
**/
#define N_SA_PCIEXBAR_ADMSK1024_OFFSET  (0x1e)
#define S_SA_PCIEXBAR_ADMSK1024_WIDTH   (0x1)
#define B_SA_PCIEXBAR_ADMSK1024_MASK    (0x40000000)
#define V_SA_PCIEXBAR_ADMSK1024_DEFAULT (0x0)

/**
 Description of PCIEXBAR (31:38)
 - This field corresponds to bits 38 to 31 of the base address for PCI Express enhanced configuration space.  BIOS will program this register resulting in a base address for a contiguous memory address space.  The size of the range is defined by bits [2:1] of this register.
 - This Base address shall be assigned on a boundary consistent with the number of buses (defined by the Length field in this register) above TOLUD and still within the 39-bit addressable memory space.  The address bits decoded depend on the length of the region defined by this register.
 - This register is locked by LT.
 - The address used to access the PCI Express configuration space for a specific device can be determined as follows:
 - PCI Express Base Address + Bus Number * 1MB + Device Number * 32KB + Function Number * 4KB
 - This address is the beginning of the 4KB space that contains both the PCI compatible configuration space and the PCI Express extended configuration space.
**/
#define N_SA_PCIEXBAR_PCIEXBAR_OFFSET  (0x1f)
#define S_SA_PCIEXBAR_PCIEXBAR_WIDTH   (0x8)
#define B_SA_PCIEXBAR_PCIEXBAR_MASK    (0x7f80000000)
#define V_SA_PCIEXBAR_PCIEXBAR_DEFAULT (0x0)

/**
 This is the base address for the Root Complex configuration space. This window of addresses contains the Root Complex Register set for the PCI Express Hierarchy associated with the Host Bridge. There is no physical memory within this 4KB window that can be addressed. The 4KB reserved by this register does not alias to any PCI 2.3 compliant memory mapped space. On reset, the Root Complex configuration space is disabled and must be enabled by writing a 1 to DMIBAREN [Dev 0, offset 68h, bit 0] All the bits in this register are locked in LT mode.
**/
#define R_SA_DMIBAR  (0x68)
/**
 Description of DMIBAREN (0:0)
 - 0: DMIBAR is disabled and does not claim any memory
 - 1: DMIBAR memory mapped accesses are claimed and decoded appropriately
 - This register is locked by LT.
**/
#define N_SA_DMIBAR_DMIBAREN_OFFSET  (0x0)
#define S_SA_DMIBAR_DMIBAREN_WIDTH   (0x1)
#define B_SA_DMIBAR_DMIBAREN_MASK    (0x1)
#define V_SA_DMIBAR_DMIBAREN_DEFAULT (0x0)
/**
 Description of DMIBAR (12:38)
 - This field corresponds to bits 38 to 12 of the base address DMI configuration space. BIOS will program this register resulting in a base address for a 4KB block of contiguous memory address space. This register ensures that a naturally aligned 4KB space is allocated within the first 512GB of addressable memory space. System Software uses this base address to program the DMI register set. All the Bits in this register are locked in LT mode.
**/
#define N_SA_DMIBAR_DMIBAR_OFFSET  (0xc)
#define S_SA_DMIBAR_DMIBAR_WIDTH   (0x1b)
#define B_SA_DMIBAR_DMIBAR_MASK    (0x7ffffff000)
#define V_SA_DMIBAR_DMIBAR_DEFAULT (0x0)

/**
 Associating each PCIe typeC root port with a segment number.
**/
#define R_SA_PCIESEGMAP  (0x78)
/**
 Description of R_SA_PCIESEGMAP (0:3)
 - PCIE0 SEGMENT - This field is programmed by BIOS and indicates the segment# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIESEGMAP_PCIE0SEG_OFFSET  (0x0)
#define S_SA_PCIESEGMAP_PCIE0SEG_WIDTH   (0x4)
#define B_SA_PCIESEGMAP_PCIE0SEG_MASK    (0xf)
#define V_SA_PCIESEGMAP_PCIE0SEG_DEFAULT (0x0)
/**
 Description of R_SA_PCIESEGMAP (4:7)
 - PCIE1 SEGMENT - This field is programmed by BIOS and indicates the segment# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIESEGMAP_PCIE1SEG_OFFSET  (0x4)
#define S_SA_PCIESEGMAP_PCIE1SEG_WIDTH   (0x4)
#define B_SA_PCIESEGMAP_PCIE1SEG_MASK    (0xf0)
#define V_SA_PCIESEGMAP_PCIE1SEG_DEFAULT (0x1)
/**
 Description of R_SA_PCIESEGMAP (8:11)
 - PCIE2 SEGMENT - This field is programmed by BIOS and indicates the segment# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIESEGMAP_PCIE2SEG_OFFSET  (0x8)
#define S_SA_PCIESEGMAP_PCIE2SEG_WIDTH   (0x4)
#define B_SA_PCIESEGMAP_PCIE2SEG_MASK    (0xf00)
#define V_SA_PCIESEGMAP_PCIE2SEG_DEFAULT (0x2)
/**
 Description of R_SA_PCIESEGMAP (12:15)
 - PCIE3 SEGMENT - This field is programmed by BIOS and indicates the segment# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIESEGMAP_PCIE3SEG_OFFSET  (0xC)
#define S_SA_PCIESEGMAP_PCIE3SEG_WIDTH   (0x4)
#define B_SA_PCIESEGMAP_PCIE3SEG_MASK    (0xf000)
#define V_SA_PCIESEGMAP_PCIE3SEG_DEFAULT (0x3)
/**
 Description of R_SA_PCIESEGMAP (16:19)
 - PCIE4 SEGMENT - This field is programmed by BIOS and indicates the segment# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIESEGMAP_PCIE4SEG_OFFSET  (0x10)
#define S_SA_PCIESEGMAP_PCIE4SEG_WIDTH   (0x4)
#define B_SA_PCIESEGMAP_PCIE4SEG_MASK    (0xf0000)
#define V_SA_PCIESEGMAP_PCIE4SEG_DEFAULT (0x4)
/**
 Description of R_SA_PCIESEGMAP (20:23)
 - PCIE5 SEGMENT - This field is programmed by BIOS and indicates the segment# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIESEGMAP_PCIE5SEG_OFFSET  (0x14)
#define S_SA_PCIESEGMAP_PCIE5SEG_WIDTH   (0x4)
#define B_SA_PCIESEGMAP_PCIE5SEG_MASK    (0xf00000)
#define V_SA_PCIESEGMAP_PCIE5SEG_DEFAULT (0x5)
/**
 Description of R_SA_PCIESEGMAP (24:27)
 - PCIE6 SEGMENT - This field is programmed by BIOS and indicates the segment# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIESEGMAP_PCIE6SEG_OFFSET  (0x18)
#define S_SA_PCIESEGMAP_PCIE6SEG_WIDTH   (0x4)
#define B_SA_PCIESEGMAP_PCIE6SEG_MASK    (0xf000000)
#define V_SA_PCIESEGMAP_PCIE6SEG_DEFAULT (0x6)
/**
 Description of PCIESEGMAP (28:31)
 - PCIE7 SEGMENT - This field is programmed by BIOS and indicates the segment# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIESEGMAP_PCIE7SEG_OFFSET  (0x1C)
#define S_SA_PCIESEGMAP_PCIE7SEG_WIDTH   (0x4)
#define B_SA_PCIESEGMAP_PCIE7SEG_MASK    (0xf0000000)
#define V_SA_PCIESEGMAP_PCIE7SEG_DEFAULT (0x7)

/**
 Associating each PCIe typeC root port with a function number.
**/
#define R_SA_PCIEFUNCMAP  (0x7C)
/**
 Description of R_SA_PCIEFUNCMAP (0:2)
 - PCIE0 FUNCTION - This field is programmed by BIOS and indicates the function# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIEFUNCMAP_PCIE0FUNC_OFFSET  (0x0)
#define S_SA_PCIEFUNCMAP_PCIE0FUNC_WIDTH   (0x3)
#define B_SA_PCIEFUNCMAP_PCIE0FUNC_MASK    (0x7)
#define V_SA_PCIEFUNCMAP_PCIE0FUNC_DEFAULT (0x0)
/**
 Description of R_SA_PCIEFUNCMAP (3:5)
 - PCIE1 FUNCTION - This field is programmed by BIOS and indicates the function# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIEFUNCMAP_PCIE1FUNC_OFFSET  (0x3)
#define S_SA_PCIEFUNCMAP_PCIE1FUNC_WIDTH   (0x3)
#define B_SA_PCIEFUNCMAP_PCIE1FUNC_MASK    (0x38)
#define V_SA_PCIEFUNCMAP_PCIE1FUNC_DEFAULT (0x0)
/**
 Description of R_SA_PCIEFUNCMAP (6:8)
 - PCIE2 FUNCTION - This field is programmed by BIOS and indicates the function# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIEFUNCMAP_PCIE2FUNC_OFFSET  (0x6)
#define S_SA_PCIEFUNCMAP_PCIE2FUNC_WIDTH   (0x3)
#define B_SA_PCIEFUNCMAP_PCIE2FUNC_MASK    (0x1C0)
#define V_SA_PCIEFUNCMAP_PCIE2FUNC_DEFAULT (0x0)
/**
 Description of R_SA_PCIEFUNCMAP (9:11)
 - PCIE3 FUNCTION - This field is programmed by BIOS and indicates the function# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIEFUNCMAP_PCIE3FUNC_OFFSET  (0x9)
#define S_SA_PCIEFUNCMAP_PCIE3FUNC_WIDTH   (0x3)
#define B_SA_PCIEFUNCMAP_PCIE3FUNC_MASK    (0xE00)
#define V_SA_PCIEFUNCMAP_PCIE3FUNC_DEFAULT (0x0)
/**
 Description of R_SA_PCIEFUNCMAP (12:14)
 - PCIE4 FUNCTION - This field is programmed by BIOS and indicates the function# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIEFUNCMAP_PCIE4FUNC_OFFSET  (0xC)
#define S_SA_PCIEFUNCMAP_PCIE4FUNC_WIDTH   (0x3)
#define B_SA_PCIEFUNCMAP_PCIE4FUNC_MASK    (0x7000)
#define V_SA_PCIEFUNCMAP_PCIE4FUNC_DEFAULT (0x0)
/**
 Description of R_SA_PCIEFUNCMAP (15:17)
 - PCIE5 FUNCTION - This field is programmed by BIOS and indicates the function# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIEFUNCMAP_PCIE5FUNC_OFFSET  (0xF)
#define S_SA_PCIEFUNCMAP_PCIE5FUNC_WIDTH   (0x3)
#define B_SA_PCIEFUNCMAP_PCIE5FUNC_MASK    (0x38000)
#define V_SA_PCIEFUNCMAP_PCIE5FUNC_DEFAULT (0x0)
/**
 Description of R_SA_PCIEFUNCMAP (18:20)
 - PCIE6 FUNCTION - This field is programmed by BIOS and indicates the function# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIEFUNCMAP_PCIE6FUNC_OFFSET  (0x12)
#define S_SA_PCIEFUNCMAP_PCIE6FUNC_WIDTH   (0x3)
#define B_SA_PCIEFUNCMAP_PCIE6FUNC_MASK    (0x1C0000)
#define V_SA_PCIEFUNCMAP_PCIE6FUNC_DEFAULT (0x0)
/**
 Description of R_SA_PCIEFUNCMAP (21:23)
 - PCIE7 FUNCTION - This field is programmed by BIOS and indicates the function# the PCIE TypeC port is associated with.
**/
#define N_SA_PCIEFUNCMAP_PCIE7FUNC_OFFSET  (0x15)
#define S_SA_PCIEFUNCMAP_PCIE7FUNC_WIDTH   (0x3)
#define B_SA_PCIEFUNCMAP_PCIE7FUNC_MASK    (0xE00000)
#define V_SA_PCIEFUNCMAP_PCIE7FUNC_DEFAULT (0x0)


/**
 Description:
 - This register controls the read, write and shadowing attributes of the BIOS range from F_0000h to F_FFFFh.  The Uncore allows programmable memory attributes on 13 legacy memory segments of various sizes in the 768KB to 1MB address range.  Seven Programmable Attribute Map (PAM) registers are used to support these features.  Cacheability of these areas is controlled via the MTRR register in the core.
 - Two bits are used to specify memory attributes for each memory segment.  These bits apply to host accesses to the PAM areas.  These attributes are:
 - RE - Read Enable.  When RE=1, the host read accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when RE=0, the host read accesses are directed to DMI.
 - WE - Write Enable.  When WE=1, the host write accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when WE=0, the host read accesses are directed to DMI.
 - The RE and WE attributes permit a memory segment to be Read Only, Write Only, Read/Write or Disabled.  For example, if a memory segment has RE=1 and WE=0, the segment is Read Only.
**/
#define R_SA_PAM0  (0x80)
///
/// Description of HIENABLE (4:5)
///  This field controls the steering of read and write cycles that address the BIOS area from 0F_0000h to 0F_FFFFh.
///  00: DRAM Disabled.  All accesses are directed to DMI.
///  01: Read Only.  All reads are sent to DRAM, all writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM, all reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM0_HIENABLE_OFFSET  (0x4)
#define S_SA_PAM0_HIENABLE_WIDTH   (0x2)
#define B_SA_PAM0_HIENABLE_MASK    (0x30)
#define V_SA_PAM0_HIENABLE_DEFAULT (0x0)

///
/// Description:
///  This register controls the read, write and shadowing attributes of the BIOS range from C_0000h to C_7FFFh.  The Uncore allows programmable memory attributes on 13 legacy memory segments of various sizes in the 768KB to 1MB address range.  Seven Programmable Attribute Map (PAM) registers are used to support these features.  Cacheability of these areas is controlled via the MTRR register in the core.
///  Two bits are used to specify memory attributes for each memory segment.  These bits apply to host accesses to the PAM areas.  These attributes are:
///  RE - Read Enable.  When RE=1, the host read accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when RE=0, the host read accesses are directed to DMI.
///  WE - Write Enable.  When WE=1, the host write accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when WE=0, the host read accesses are directed to DMI.
///  The RE and WE attributes permit a memory segment to be Read Only, Write Only, Read/Write or Disabled.  For example, if a memory segment has RE=1 and WE=0, the segment is Read Only.
///
#define R_SA_PAM1  (0x81)
///
/// Description of LOENABLE (0:1)
///  This field controls the steering of read and write cycles that address the BIOS area from 0C0000h to 0C3FFFh.
///  00: DRAM Disabled.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  01: Read Only.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM.  All reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM1_LOENABLE_OFFSET  (0x0)
#define S_SA_PAM1_LOENABLE_WIDTH   (0x2)
#define B_SA_PAM1_LOENABLE_MASK    (0x3)
#define V_SA_PAM1_LOENABLE_DEFAULT (0x0)
///
/// Description of HIENABLE (4:5)
///  This field controls the steering of read and write cycles that address the BIOS area from 0C_4000h to 0C_7FFFh.
///  00: DRAM Disabled.  All accesses are directed to DMI.
///  01: Read Only.  All reads are sent to DRAM, all writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM, all reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM1_HIENABLE_OFFSET  (0x4)
#define S_SA_PAM1_HIENABLE_WIDTH   (0x2)
#define B_SA_PAM1_HIENABLE_MASK    (0x30)
#define V_SA_PAM1_HIENABLE_DEFAULT (0x0)

///
/// Description:
///  This register controls the read, write and shadowing attributes of the BIOS range from C_8000h to C_FFFFh.  The Uncore allows programmable memory attributes on 13 legacy memory segments of various sizes in the 768KB to 1MB address range.  Seven Programmable Attribute Map (PAM) registers are used to support these features.  Cacheability of these areas is controlled via the MTRR register in the core.
///  Two bits are used to specify memory attributes for each memory segment.  These bits apply to host accesses to the PAM areas.  These attributes are:
///  RE - Read Enable.  When RE=1, the host read accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when RE=0, the host read accesses are directed to DMI.
///  WE - Write Enable.  When WE=1, the host write accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when WE=0, the host read accesses are directed to DMI.
///  The RE and WE attributes permit a memory segment to be Read Only, Write Only, Read/Write or Disabled.  For example, if a memory segment has RE=1 and WE=0, the segment is Read Only.
///
#define R_SA_PAM2  (0x82)
///
/// Description of LOENABLE (0:1)
///  This field controls the steering of read and write cycles that address the BIOS area from 0C8000h to 0CBFFFh.
///  00: DRAM Disabled.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  01: Read Only.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM.  All reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM2_LOENABLE_OFFSET  (0x0)
#define S_SA_PAM2_LOENABLE_WIDTH   (0x2)
#define B_SA_PAM2_LOENABLE_MASK    (0x3)
#define V_SA_PAM2_LOENABLE_DEFAULT (0x0)
///
/// Description of HIENABLE (4:5)
///  This field controls the steering of read and write cycles that address the BIOS area from 0CC000h to 0CFFFFh.
///  00: DRAM Disabled.  All accesses are directed to DMI.
///  01: Read Only.  All reads are sent to DRAM, all writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM, all reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM2_HIENABLE_OFFSET  (0x4)
#define S_SA_PAM2_HIENABLE_WIDTH   (0x2)
#define B_SA_PAM2_HIENABLE_MASK    (0x30)
#define V_SA_PAM2_HIENABLE_DEFAULT (0x0)

///
/// Description:
///  This register controls the read, write and shadowing attributes of the BIOS range from D0000h to D7FFFh.  The Uncore allows programmable memory attributes on 13 legacy memory segments of various sizes in the 768KB to 1MB address range.  Seven Programmable Attribute Map (PAM) registers are used to support these features.  Cacheability of these areas is controlled via the MTRR register in the core.
///  Two bits are used to specify memory attributes for each memory segment.  These bits apply to host accesses to the PAM areas.  These attributes are:
///  RE - Read Enable.  When RE=1, the host read accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when RE=0, the host read accesses are directed to DMI.
///  WE - Write Enable.  When WE=1, the host write accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when WE=0, the host read accesses are directed to DMI.
///  The RE and WE attributes permit a memory segment to be Read Only, Write Only, Read/Write or Disabled.  For example, if a memory segment has RE=1 and WE=0, the segment is Read Only.
///
#define R_SA_PAM3  (0x83)
///
/// Description of LOENABLE (0:1)
///  This field controls the steering of read and write cycles that address the BIOS area from 0D0000h to 0D3FFFh.
///  00: DRAM Disabled.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  01: Read Only.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM.  All reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM3_LOENABLE_OFFSET  (0x0)
#define S_SA_PAM3_LOENABLE_WIDTH   (0x2)
#define B_SA_PAM3_LOENABLE_MASK    (0x3)
#define V_SA_PAM3_LOENABLE_DEFAULT (0x0)
///
/// Description of HIENABLE (4:5)
///  This field controls the steering of read and write cycles that address the BIOS area from 0D4000h to 0D7FFFh.
///  00: DRAM Disabled.  All accesses are directed to DMI.
///  01: Read Only.  All reads are sent to DRAM, all writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM, all reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM3_HIENABLE_OFFSET  (0x4)
#define S_SA_PAM3_HIENABLE_WIDTH   (0x2)
#define B_SA_PAM3_HIENABLE_MASK    (0x30)
#define V_SA_PAM3_HIENABLE_DEFAULT (0x0)

///
/// Description:
///  This register controls the read, write and shadowing attributes of the BIOS range from D8000h to DFFFFh.  The Uncore allows programmable memory attributes on 13 legacy memory segments of various sizes in the 768KB to 1MB address range.  Seven Programmable Attribute Map (PAM) registers are used to support these features.  Cacheability of these areas is controlled via the MTRR register in the core.
///  Two bits are used to specify memory attributes for each memory segment.  These bits apply to host accesses to the PAM areas.  These attributes are:
///  RE - Read Enable.  When RE=1, the host read accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when RE=0, the host read accesses are directed to DMI.
///  WE - Write Enable.  When WE=1, the host write accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when WE=0, the host read accesses are directed to DMI.
///  The RE and WE attributes permit a memory segment to be Read Only, Write Only, Read/Write or Disabled.  For example, if a memory segment has RE=1 and WE=0, the segment is Read Only.
///
#define R_SA_PAM4  (0x84)
///
/// Description of LOENABLE (0:1)
///  This field controls the steering of read and write cycles that address the BIOS area from 0D8000h to 0DBFFFh.
///  00: DRAM Disabled.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  01: Read Only.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM.  All reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM4_LOENABLE_OFFSET  (0x0)
#define S_SA_PAM4_LOENABLE_WIDTH   (0x2)
#define B_SA_PAM4_LOENABLE_MASK    (0x3)
#define V_SA_PAM4_LOENABLE_DEFAULT (0x0)
///
/// Description of HIENABLE (4:5)
///  This field controls the steering of read and write cycles that address the BIOS area from 0DC000h to 0DFFFFh.
///  00: DRAM Disabled.  All accesses are directed to DMI.
///  01: Read Only.  All reads are sent to DRAM, all writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM, all reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM4_HIENABLE_OFFSET  (0x4)
#define S_SA_PAM4_HIENABLE_WIDTH   (0x2)
#define B_SA_PAM4_HIENABLE_MASK    (0x30)
#define V_SA_PAM4_HIENABLE_DEFAULT (0x0)

///
/// Description:
///  This register controls the read, write and shadowing attributes of the BIOS range from E_0000h to E_7FFFh.  The Uncore allows programmable memory attributes on 13 legacy memory segments of various sizes in the 768KB to 1MB address range.  Seven Programmable Attribute Map (PAM) registers are used to support these features.  Cacheability of these areas is controlled via the MTRR register in the core.
///  Two bits are used to specify memory attributes for each memory segment.  These bits apply to host accesses to the PAM areas.  These attributes are:
///  RE - Read Enable.  When RE=1, the host read accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when RE=0, the host read accesses are directed to DMI.
///  WE - Write Enable.  When WE=1, the host write accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when WE=0, the host read accesses are directed to DMI.
///  The RE and WE attributes permit a memory segment to be Read Only, Write Only, Read/Write or Disabled.  For example, if a memory segment has RE=1 and WE=0, the segment is Read Only.
///
#define R_SA_PAM5  (0x85)
///
/// Description of LOENABLE (0:1)
///  This field controls the steering of read and write cycles that address the BIOS area from 0E0000h to 0E3FFFh.
///  00: DRAM Disabled.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  01: Read Only.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM.  All reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM5_LOENABLE_OFFSET  (0x0)
#define S_SA_PAM5_LOENABLE_WIDTH   (0x2)
#define B_SA_PAM5_LOENABLE_MASK    (0x3)
#define V_SA_PAM5_LOENABLE_DEFAULT (0x0)
///
/// Description of HIENABLE (4:5)
///  This field controls the steering of read and write cycles that address the BIOS area from 0E4000h to 0E7FFFh.
///  00: DRAM Disabled.  All accesses are directed to DMI.
///  01: Read Only.  All reads are sent to DRAM, all writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM, all reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM5_HIENABLE_OFFSET  (0x4)
#define S_SA_PAM5_HIENABLE_WIDTH   (0x2)
#define B_SA_PAM5_HIENABLE_MASK    (0x30)
#define V_SA_PAM5_HIENABLE_DEFAULT (0x0)

///
/// Description:
///  This register controls the read, write and shadowing attributes of the BIOS range from E_8000h to E_FFFFh.  The Uncore allows programmable memory attributes on 13 legacy memory segments of various sizes in the 768KB to 1MB address range.  Seven Programmable Attribute Map (PAM) registers are used to support these features.  Cacheability of these areas is controlled via the MTRR register in the core.
///  Two bits are used to specify memory attributes for each memory segment.  These bits apply to host accesses to the PAM areas.  These attributes are:
///  RE - Read Enable.  When RE=1, the host read accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when RE=0, the host read accesses are directed to DMI.
///  WE - Write Enable.  When WE=1, the host write accesses to the corresponding memory segment are claimed by the Uncore and directed to main memory.  Conversely, when WE=0, the host read accesses are directed to DMI.
///  The RE and WE attributes permit a memory segment to be Read Only, Write Only, Read/Write or Disabled.  For example, if a memory segment has RE=1 and WE=0, the segment is Read Only.
///
#define R_SA_PAM6  (0x86)
///
/// Description of LOENABLE (0:1)
///  This field controls the steering of read and write cycles that address the BIOS area from 0E8000h to 0EBFFFh.
///  00: DRAM Disabled.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  01: Read Only.  All reads are sent to DRAM.  All writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM.  All reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM6_LOENABLE_OFFSET  (0x0)
#define S_SA_PAM6_LOENABLE_WIDTH   (0x2)
#define B_SA_PAM6_LOENABLE_MASK    (0x3)
#define V_SA_PAM6_LOENABLE_DEFAULT (0x0)
///
/// Description of HIENABLE (4:5)
///  This field controls the steering of read and write cycles that address the BIOS area from 0EC000h to 0EFFFFh.
///  00: DRAM Disabled.  All accesses are directed to DMI.
///  01: Read Only.  All reads are sent to DRAM, all writes are forwarded to DMI.
///  10: Write Only.  All writes are sent to DRAM, all reads are serviced by DMI.
///  11: Normal DRAM Operation.  All reads and writes are serviced by DRAM.
///  This register is locked by LT.
///
#define N_SA_PAM6_HIENABLE_OFFSET  (0x4)
#define S_SA_PAM6_HIENABLE_WIDTH   (0x2)
#define B_SA_PAM6_HIENABLE_MASK    (0x30)
#define V_SA_PAM6_HIENABLE_DEFAULT (0x0)

#define R_SA_MC_LAC_OFFSET         0x87  ///< Legacy Access Control Register
#define R_SA_B_HEN                 0x80  ///< RW

///
/// Description:
///  This Register contains the size of physical memory.  BIOS determines the memory size reported to the OS using this Register.
///
#define R_SA_TOM (0xa0)
///
/// Description of LOCK (0:0)
///  This bit will lock all writeable settings in this register, including itself.
///
#define N_SA_TOM_LOCK_OFFSET   (0x0)
#define S_SA_TOM_LOCK_WIDTH    (0x1)
#define B_SA_TOM_LOCK_MASK     (0x1)
#define V_SA_TOM_LOCK_DEFAULT  (0x0)

///
/// Description of TOM (20:38)
///  This register reflects the total amount of populated physical memory. This is NOT necessarily the highest main memory address (holes may exist in main memory address map due to addresses allocated for memory mapped IO). These bits correspond to address bits 38:20 (1MB granularity). Bits 19:0 are assumed to be 0. All the bits in this register are locked in LT mode.
///
#define N_SA_TOM_TOM_OFFSET  (0x14)
#define S_SA_TOM_TOM_WIDTH   (0x13)
#define B_SA_TOM_TOM_MASK    (0x7ffff00000)
#define V_SA_TOM_TOM_DEFAULT (0x7ffff00000)

///
/// Description:
///  This 64 bit register defines the Top of Upper Usable DRAM.
///  Configuration software must set this value to TOM minus all EP stolen memory if reclaim is disabled.  If reclaim is enabled, this value must be set to reclaim limit + 1byte, 1MB aligned, since reclaim limit is 1MB aligned. Address bits 19:0 are assumed to be 000_0000h for the purposes of address comparison. The Host interface positively decodes an address towards DRAM if the incoming address is less than the value programmed in this register and greater than or equal to 4GB.
///  BIOS Restriction: Minimum value for TOUUD is 4GB.
///  These bits are LT lockable.
///
#define R_SA_TOUUD (0xa8)
#define R_SA_GTTMMADR_TOUUD_OFFSET (0x108080)
///
/// Description of LOCK (0:0)
///  This bit will lock all writeable settings in this register, including itself.
///
#define N_SA_TOUUD_LOCK_OFFSET   (0x0)
#define S_SA_TOUUD_LOCK_WIDTH    (0x1)
#define B_SA_TOUUD_LOCK_MASK     (0x1)
#define V_SA_TOUUD_LOCK_DEFAULT  (0x0)
///
/// Description of TOUUD (20:38)
///  This register contains bits 38  to 20 of an address one byte above the maximum DRAM memory above 4G that is usable by the operating system. Configuration software must set this value to TOM minus all EP stolen memory if reclaim is disabled. If reclaim is enabled, this value must be set to reclaim limit 1MB aligned since reclaim limit + 1byte is 1MB aligned. Address bits 19:0 are assumed to be 000_0000h for the purposes of address comparison. The Host interface positively decodes an address towards DRAM if the incoming address is less than the value programmed in this register and greater than 4GB.
///  All the bits in this register are locked in LT mode.
///
#define N_SA_TOUUD_TOUUD_OFFSET  (0x14)
#define S_SA_TOUUD_TOUUD_WIDTH   (0x13)
#define B_SA_TOUUD_TOUUD_MASK    (0x7ffff00000ULL)
#define V_SA_TOUUD_TOUUD_DEFAULT (0x0)

///
/// Description:
///  This register contains the base address of graphics data stolen DRAM memory. BIOS determines the base of graphics data stolen memory by subtracting the graphics data stolen memory size (PCI Device 0 offset 52 bits 7:4) from TOLUD (PCI Device 0 offset BC bits 31:20).
///
#define R_SA_BDSM  (0xb0)
#define R_SA_GTTMMADR_BDSM_OFFSET (0x1080C0)
///
/// Description of LOCK (0:0)
///  This bit will lock all writeable settings in this register, including itself.
///
#define N_SA_BDSM_LOCK_OFFSET  (0x0)
#define S_SA_BDSM_LOCK_WIDTH   (0x1)
#define B_SA_BDSM_LOCK_MASK    (0x1)
#define V_SA_BDSM_LOCK_DEFAULT (0x0)
///
/// Description of BDSM (20:31)
///  This register contains bits 31 to 20 of the base address of stolen DRAM memory. BIOS determines the base of graphics stolen memory by subtracting the graphics stolen memory size (PCI Device 0 offset 52 bits 6:4) from TOLUD (PCI Device 0 offset BC bits 31:20).
///
#define N_SA_BDSM_BDSM_OFFSET  (0x14)
#define S_SA_BDSM_BDSM_WIDTH   (0xc)
#define B_SA_BDSM_BDSM_MASK    (0xfff00000)
#define V_SA_BDSM_BDSM_DEFAULT (0x0)

///
/// Description:
///  This register contains the base address of stolen DRAM memory for the GTT. BIOS determines the base of GTT stolen memory by subtracting the GTT graphics stolen memory size (PCI Device 0 offset 52 bits 9:8) from the Graphics Base of  Data Stolen Memory (PCI Device 0 offset B0 bits 31:20).
///
#define R_SA_BGSM  (0xb4)
#define R_SA_GTTMMADR_BGSM_OFFSET  (0x108100)
///
/// Description of LOCK (0:0)
///  This bit will lock all writeable settings in this register, including itself.
///
#define N_SA_BGSM_LOCK_OFFSET  (0x0)
#define S_SA_BGSM_LOCK_WIDTH   (0x1)
#define B_SA_BGSM_LOCK_MASK    (0x1)
#define V_SA_BGSM_LOCK_DEFAULT (0x0)
///
/// Description of BGSM (20:31)
///  This register contains the base address of stolen DRAM memory for the GTT. BIOS determines the base of GTT stolen memory by subtracting the GTT graphics stolen memory size (PCI Device 0 offset 52 bits 11:8) from the Graphics Base of  Data Stolen Memory (PCI Device 0 offset B0 bits 31:20).
///
#define N_SA_BGSM_BGSM_OFFSET  (0x14)
#define S_SA_BGSM_BGSM_WIDTH   (0xc)
#define B_SA_BGSM_BGSM_MASK    (0xfff00000)
#define V_SA_BGSM_BGSM_DEFAULT (0x0)

///
/// Description:
///  This register contains the base address of TSEG DRAM memory. BIOS determines the base of TSEG memory which must be at or below Graphics Base of GTT Stolen Memory (PCI Device 0 Offset B4 bits 31:20).
///
#define R_SA_TSEGMB  (0xb8)
#define R_SA_GTTMMADR_TSEGMB_OFFSET (0x108400)
///
/// Description of LOCK (0:0)
///  This bit will lock all writeable settings in this register, including itself.
///
#define N_SA_TSEGMB_LOCK_OFFSET  (0x0)
#define S_SA_TSEGMB_LOCK_WIDTH   (0x1)
#define B_SA_TSEGMB_LOCK_MASK    (0x1)
#define V_SA_TSEGMB_LOCK_DEFAULT (0x0)
///
/// Description of TSEGMB (20:31)
///  This register contains the base address of TSEG DRAM memory. BIOS determines the base of TSEG memory which must be at or below Graphics Base of GTT Stolen Memory (PCI Device 0 Offset B4 bits 31:20).
///
#define N_SA_TSEGMB_TSEGMB_OFFSET  (0x14)
#define S_SA_TSEGMB_TSEGMB_WIDTH   (0xc)
#define B_SA_TSEGMB_TSEGMB_MASK    (0xfff00000)
#define V_SA_TSEGMB_TSEGMB_DEFAULT (0x0)

///
/// Description:
///  This register contains the Top of low memory address.
///
#define R_SA_TOLUD (0xbc)
#define R_SA_GTTMMADR_TOLUD_OFFSET (0x108000)
///
/// Description of LOCK (0:0)
///  This bit will lock all writeable settings in this register, including itself.
///
#define N_SA_TOLUD_LOCK_OFFSET   (0x0)
#define S_SA_TOLUD_LOCK_WIDTH    (0x1)
#define B_SA_TOLUD_LOCK_MASK     (0x1)
#define V_SA_TOLUD_LOCK_DEFAULT  (0x0)
///
/// Description of TOLUD (20:31)
///  This register contains bits 31 to 20 of an address one byte above the maximum DRAM memory below 4G that is usable by the operating system. Address bits 31 down to 20 programmed to 01h implies a minimum memory size of 1MB. Configuration software must set this value to the smaller of the following 2 choices: maximum amount memory in the system minus ME stolen memory plus one byte or the minimum address allocated for PCI memory. Address bits 19:0 are assumed to be 0_0000h for the purposes of address comparison. The Host interface positively decodes an address towards DRAM if the incoming address is less than the value programmed in this register.
///  The Top of Low Usable DRAM is the lowest address above both Graphics Stolen memory and Tseg. BIOS determines the base of Graphics Stolen Memory by subtracting the Graphics Stolen Memory Size from TOLUD and further decrements by Tseg size to determine base of Tseg. All the Bits in this register are locked in LT mode.
///  This register must be 1MB aligned when reclaim is enabled.
///
#define N_SA_TOLUD_TOLUD_OFFSET    (0x14)
#define S_SA_TOLUD_TOLUD_WIDTH     (0xc)
#define B_SA_TOLUD_TOLUD_MASK      (0xfff00000)
#define V_SA_TOLUD_TOLUD_DEFAULT   (0x100000)

#define R_SA_MC_ERRSTS_OFFSET      0xC8    ///< Error Status Register
#define B_GMSWSMI                  0x1000  ///< Software SMI
#define R_SA_MC_ERRCMD_OFFSET      0xCA    ///< Error Command Register
#define R_SA_MC_SKPD_OFFSET        0xDC    ///< Scratch Pad Data
#define R_SA_MC_CAPID0_OFFSET      0xE0    ///< Capability Identification @bug reserved in EDS
#define R_SA_MC_CAPID0_A_OFFSET    0xE4
#define R_SA_MC_SIM_RECOGNITION_OFFSET          0xFC
#define V_SA_MC_SIM_RECOGNITION_PLATFORM_HW     0x00
#define V_SA_MC_SIM_RECOGNITION_PLATFORM_SIMICS 0x04
#define V_SA_MC_SIM_RECOGNITION_PLATFORM_HFPGA  0x05

//
// MCHBAR IO Register Offset Equates
//
#define R_SA_MCHBAR_PAVPC_OFFSET                   0x34    ///< PAPVC
#define R_SA_MCHBAR_MC_LOCK_OFFSET                 0x50FC
#define R_SA_MCHBAR_BIOS_RESET_CPL_OFFSET          0x5DA8
#define R_SA_MCHBAR_SAPMCTL_OFFSET                 0x5F00
#define R_SA_MCHBAR_MAD_INTER_CHANNEL_OFFSET       0x5000
#define R_SA_MCHBAR_MAD_INTRA_CH0_OFFSET           0x5004
#define R_SA_MCHBAR_MAD_INTRA_CH1_OFFSET           0x5008
#define R_SA_MCHBAR_MAD_DIMM_CH0_OFFSET            0x500C
#define R_SA_MCHBAR_MAD_DIMM_CH1_OFFSET            0x5010
#define R_SA_MCHBAR_CHANNEL_HASH_OFFSET            0x5024
#define R_SA_MCHBAR_CHANNEL_EHASH_OFFSET           0x5028
#define R_SA_MCHBAR_VLWCTL                         0x7020
#define B_SA_MCHBAR_VLWCTL_DROP_VLW_CTL            BIT0
#define R_SA_MCHBAR_TCSS_DEVEN_OFFSET              0x7090
/**
 TCSS_DEVEN register
 Description of PCIE0 (0:0)
 PCIE0 Enable - 0: PCIE0 is disabled and hidden. 1: PCIE0 is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_PCIE0_OFFSET   (0x0)
#define S_SA_MCHBAR_TCSS_DEVEN_PCIE0_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_PCIE0_MASK     (0x01)
#define V_SA_MCHBAR_TCSS_DEVEN_PCIE0_DEFAULT  (0x1)
/**
 TCSS_DEVEN register
 Description of PCIE1 (1:1)
 PCIE1 Enable - 0: PCIE1 is disabled and hidden. 1: PCIE1 is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_PCIE1_OFFSET   (0x1)
#define S_SA_MCHBAR_TCSS_DEVEN_PCIE1_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_PCIE1_MASK     (0x02)
#define V_SA_MCHBAR_TCSS_DEVEN_PCIE1_DEFAULT  (0x1)
/**
 TCSS_DEVEN register
 Description of PCIE2 (2:2)
 PCIE2 Enable - 0: PCIE2 is disabled and hidden. 1: PCIE2 is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_PCIE2_OFFSET   (0x2)
#define S_SA_MCHBAR_TCSS_DEVEN_PCIE2_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_PCIE2_MASK     (0x04)
#define V_SA_MCHBAR_TCSS_DEVEN_PCIE2_DEFAULT  (0x1)
/**
 TCSS_DEVEN register
 Description of PCIE3 (3:3)
 PCIE3 Enable - 0: PCIE3 is disabled and hidden. 1: PCIE3 is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_PCIE3_OFFSET   (0x3)
#define S_SA_MCHBAR_TCSS_DEVEN_PCIE3_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_PCIE3_MASK     (0x08)
#define V_SA_MCHBAR_TCSS_DEVEN_PCIE3_DEFAULT  (0x1)
/**
 TCSS_DEVEN register
 Description of PCIE4 (4:4)
 PCIE4 Enable - 0: PCIE4 is disabled and hidden. 1: PCIE4 is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_PCIE4_OFFSET   (0x4)
#define S_SA_MCHBAR_TCSS_DEVEN_PCIE4_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_PCIE4_MASK     (0x10)
#define V_SA_MCHBAR_TCSS_DEVEN_PCIE4_DEFAULT  (0x1)
/**
 TCSS_DEVEN register
 Description of PCIE5 (5:5)
 PCIE5 Enable - 0: PCIE5 is disabled and hidden. 1: PCIE5 is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_PCIE5_OFFSET   (0x5)
#define S_SA_MCHBAR_TCSS_DEVEN_PCIE5_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_PCIE5_MASK     (0x20)
#define V_SA_MCHBAR_TCSS_DEVEN_PCIE5_DEFAULT  (0x1)
/**
 TCSS_DEVEN register
 Description of XHCI (:8)
 XHCI Enable - 0: XHCI is disabled and hidden. 1: XHCI is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_XHCI_OFFSET   (0x8)
#define S_SA_MCHBAR_TCSS_DEVEN_XHCI_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_XHCI_MASK     (0x100)
#define V_SA_MCHBAR_TCSS_DEVEN_XHCI_DEFAULT  (0x1)
/**
 TCSS_DEVEN register
 Description of XDCI (9:9)
 xDCI Enable - 0: xDCI is disabled and hidden. 1: xDCI is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_XDCI_OFFSET   (0x9)
#define S_SA_MCHBAR_TCSS_DEVEN_XDCI_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_XDCI_MASK     (0x200)
#define V_SA_MCHBAR_TCSS_DEVEN_XDCI_DEFAULT  (0x1)
/**
 TCSS_DEVEN register
 Description of DMA0 (10:10)
 DMA0 Enable - 0: DMA0 is disabled and hidden. 1: DMA0 is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_DMA0_OFFSET   (0xA)
#define S_SA_MCHBAR_TCSS_DEVEN_DMA0_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_DMA0_MASK     (0x400)
#define V_SA_MCHBAR_TCSS_DEVEN_DMA0_DEFAULT  (0x1)
/**
 TCSS_DEVEN register
 Description of DMA1 (11:11)
 DMA1 Enable - 0: DMA1 is disabled and hidden. 1: DMA1 is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_DMA1_OFFSET   (0xB)
#define S_SA_MCHBAR_TCSS_DEVEN_DMA1_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_DMA1_MASK     (0x800)
#define V_SA_MCHBAR_TCSS_DEVEN_DMA1_DEFAULT  (0x1)
/**
 TCSS_DEVEN register
 Description of DMA2 (12:12)
 DMA2 Enable - 0: DMA2 is disabled and hidden. 1: DMA2 is enabled and visible.
**/
#define N_SA_MCHBAR_TCSS_DEVEN_DMA2_OFFSET   (0xC)
#define S_SA_MCHBAR_TCSS_DEVEN_DMA2_WIDTH    (0x1)
#define B_SA_MCHBAR_TCSS_DEVEN_DMA2_MASK     (0x1000)
#define V_SA_MCHBAR_TCSS_DEVEN_DMA2_DEFAULT  (0x1)
#define R_SA_MCHBAR_REGBAR_OFFSET                  0x5518
#define V_SA_MCHBAR_REGBAR_SIZE                    SIZE_16MB
#define R_SA_MCHBAR_EDRAMBAR_OFFSET                0x5408
#define R_SA_MCHBAR_ILTR_OVRD_OFFSET               0x5D30
#define R_SA_MCHBAR_EDRAM_RATIO_OFFSET             0x5E08
#define R_SA_MCHBAR_PAM_W_PG_CP                    0x6128
#define R_SA_MCHBAR_PAM_W_PG_WAC                   0x6130
#define B_SA_MCHBAR_PAM_W_PG_HOSTIA_POSTBOOT_SAI   BIT0


#define R_SA_MCHBAR_CRDTCTL_PMIN_A_OFFSET          0x7450
#define R_SA_MCHBAR_CRDTCTL_PMIN_B_OFFSET          0x7454
#define R_SA_MCHBAR_CRDTCTL_NPMIN_A_OFFSET         0x7458
#define R_SA_MCHBAR_CRDTCTL_NPMIN_B_OFFSET         0x745C
#define R_SA_MCHBAR_CRDTCTL_PINIT_A_OFFSET         0x7460
#define R_SA_MCHBAR_CRDTCTL_PINIT_B_OFFSET         0x7464
#define R_SA_MCHBAR_CRDTCTL_NPINIT_A_OFFSET        0x7468
#define R_SA_MCHBAR_CRDTCTL_NPINIT_B_OFFSET        0x746C
#define R_SA_MCHBAR_CRDTCTL_PMAX_A_OFFSET          0x7470
#define R_SA_MCHBAR_CRDTCTL_PMAX_B_OFFSET          0x7474
#define R_SA_MCHBAR_CRDTCTL_NPMAX_A_OFFSET         0x7478
#define R_SA_MCHBAR_CRDTCTL_NPMAX_B_OFFSET         0x747C
#define R_SA_MCHBAR_CRDTCTL_RRMIN_A_OFFSET         0x7480
#define R_SA_MCHBAR_CRDTCTL_RRMIN_B_OFFSET         0x7484
#define R_SA_MCHBAR_CRDTCTL_RRMAX_A_OFFSET         0x7488
#define R_SA_MCHBAR_CRDTCTL_RRMAX_B_OFFSET         0x748C

#define R_SA_MCHBAR_RESERVED_3_OFFSET              0x7BFC

#define V_SA_LTR_MAX_SNOOP_LATENCY_VALUE           0x0846  ///< Intel recommended maximum value for Snoop Latency (70us)
#define V_SA_LTR_MAX_NON_SNOOP_LATENCY_VALUE       0x0846  ///< Intel recommended maximum value for Non-Snoop Latency (70us)
#define B_SA_MCHBAR_EDRAM_RATIO_MASK               0x0000007F

#define R_SA_MCHBAR_HDAUDRID_IMPH                  0x7008
#define N_SA_MCHBAR_HDAUDRID_IMPH_DEVNUM_OFFSET    3
#define B_SA_MCHBAR_HDAUDRID_IMPH_DEVNUM_MASK      0x000000F8



//Description:
//  This is the MSR address that enables configuring the recipe for PEG and DMI private space registers.
#define R_SA_MSRIO_ADDRESS 0x791

///
/// DMIBAR registers
///
#define R_SA_DMIBAR_DMIPVCCAP1_OFFSET      0x4       ///< DMI VC Capabilities 1
#define R_SA_DMIBAR_DMIVC0RCTL_OFFSET      0x14      ///< DMI VC0 Resource Control
#define R_SA_DMIBAR_DMIVC0RSTS_OFFSET      0x1A      ///< DMI VC0 Status
#define R_SA_DMIBAR_DMIVC1RCTL_OFFSET      0x20      ///< DMI VC1 Resource Control
#define R_SA_DMIBAR_DMIVC1RSTS_OFFSET      0x26      ///< DMI VC1 Status
#define R_SA_DMIBAR_DMIVCPRCTL_OFFSET      0x2C      ///< DMI VCp Resource Control
#define R_SA_DMIBAR_DMIVCPRSTS_OFFSET      0x32      ///< DMI VCp Status
#define R_SA_DMIBAR_DMIVCMRCTL_OFFSET      0x38      ///< DMI VCm Resource Control
#define R_SA_DMIBAR_DMIVCMRSTS_OFFSET      0x3E      ///< DMI VCm Status
#define R_SA_DMIBAR_LCAP_OFFSET            0x84      ///< DMI Link Capabilities
#define R_SA_DMIBAR_LCTL_OFFSET            0x88      ///< DMI Link Control
#define R_SA_DMIBAR_LSTS_OFFSET            0x8A      ///< DMI Link Status
#define R_SA_DMIBAR_LCTL2_OFFSET           0x98      ///< DMI Link Control 2
#define R_SA_DMIBAR_LSTS2_OFFSET           0x9A      ///< Link Status 2
#define R_SA_DMIBAR_DCAP_OFFSET            0xA4      ///< DMI Device Capabilities
#define R_SA_DMIBAR_DCTL_OFFSET            0xA8      ///< DMI Device Control
#define R_SA_DMIBAR_DMICC_OFFSET           0x208     ///< DMI Config Control
#define R_SA_DMIBAR_DMISTS_OFFSET          0x214     ///< DMI Status
#define R_SA_DMIBAR_LTSSMC_OFFSET          0x224     ///< DMI LTSSMC Control
#define R_SA_DMIBAR_L0SLAT_OFFSET          0x22C     ///< DMI L0s Control
#define R_SA_DMIBAR_CFG4_OFFSET            0x258     ///< DMI Config 4
#define R_SA_DMIBAR_CFG5_OFFSET            0x25C     ///< DMI Config 5
#define R_SA_DMIBAR_CFG6_OFFSET            0x260     ///< DMI Config 6
#define R_SA_DMIBAR_PCIELOCK2_OFFSET       0x328     ///< DMI PCIELOCK2
#define R_SA_DMIBAR_AFELN0VMTX2_OFFSET     0x70C     ///< DMI AFE Lane VMTX2
#define R_SA_DMIBAR_AFELN0IOCFG0_OFFSET    0x808     ///< DMI AFE Lane IO Config 0
#define R_SA_DMIBAR_AFEBND0CFG1_OFFSET     0x904     ///< DMI AFE Bundle Config 1
#define R_SA_DMIBAR_AFEBND0CFG2_OFFSET     0x908     ///< DMI AFE Bundle Config 2
#define R_SA_DMIBAR_AFELN0CFG0_OFFSET      0xA00     ///< DMI AFE Lane Config 0
#define R_SA_DMIBAR_OPIO_T_SB_MIN          0xA84     ///< OPIO SB Min Assert Duration
#define R_SA_DMIBAR_OPIO_PHY_CONTROL       0xB34     ///< OPIO Phy Control
#define N_SA_DMIBAR_OPIO_SECURITY_LOCK_BIT BIT26     ///< Security Lock Bit
#define N_SA_DMIBAR_OPIO_CLOCK_GATE        BIT28     ///< IOSF SB Clock Gating
#define R_SA_DMIBAR_AFECMNCFG0_OFFSET      0xC00     ///< DMI AFE Common Config 0
#define R_SA_DMIBAR_AFECMNCFG1_OFFSET      0xC04     ///< DMI AFE Common Config 1
#define R_SA_DMIBAR_AFECMNCFG2_OFFSET      0xC08     ///< DMI AFE Common Config 2
#define R_SA_DMIBAR_AFECMNCFG3_OFFSET      0xC0C     ///< DMI AFE Common Config 3
#define R_SA_DMIBAR_AFE_PM_TMR_OFFSET      0xC28     ///< DMI AFE PM Timer
#define R_SA_DMIBAR_CMNSPARE_OFFSET        0xC38     ///< DMI Common Spare
#define R_SA_DMIBAR_DMITST_OFFSET          0xD0C     ///< DMI TEST
#define R_SA_DMIBAR_SCRATCHPAD0_OFFSET     0xD64     ///< DMI Scratchpad 0
#define R_SA_DMIBAR_SCRATCHPAD1_OFFSET     0xD68     ///< DMI Scratchpad 1
#define N_SA_DMIBAR_DMIVCCTL_EN            BIT31
#define V_SA_DMIBAR_DMIVCCTL_ID            (7 << 24) ///< Bit[26:24]
#define B_SA_DMIBAR_DMIVCCTL_TVM_MASK      0xFE
#define N_SA_DMIBAR_DMIVCCTL_ID            24
#define B_SA_DMIBAR_DMISTS_NP              BIT1
#define B_SA_DMIBAR_DCAP_OFFSET_LOCK       0x7         //(BIT2|BIT1|BIT0)
#define B_SA_DMIBAR_DCTL_OFFSET_MASK       0xFFFFFF1F  //~(BIT7|BIT6|BIT5)

#define R_SA_MSRIO_DMIBAR_AFE_PH3_CFG0_BND_0_OFFSET  0xA00 ///< DMI AFE PH3 Bundle Config 0
#define R_SA_MSRIO_DMIBAR_AFE_PH3_CFG1_BND_0_OFFSET  0xA10 ///< DMI AFE PH3 Bundle Config 1
#define R_SA_MSRIO_DMIBAR_AFE_PH3_CFG2_BND_0_OFFSET  0xA04 ///< DMI AFE PH3 Bundle Config 2

///
/// OPIO MSG PXPEPBAR Register
///
#define R_SA_PXPEPBAR_EPVECH               0x0
#define R_SA_PXPEPBAR_EPPVCCAP1            0x4
#define R_SA_PXPEPBAR_EPPVCCAP2            0x8
#define R_SA_PXPEPBAR_EPPVCCTL             0xC
#define R_SA_PXPEPBAR_EPVC0RCAP            0x10
#define R_SA_PXPEPBAR_EPVC0RCTL            0x14
#define R_SA_PXPEPBAR_EPVC0RSTS            0x1A
#define R_SA_PXPEPBAR_EPVC1RCAP            0x1C
#define R_SA_PXPEPBAR_EPVC1RCTL            0x20
#define B_SA_PXPEPBAR_EPVC1RCTL_VC1E       BIT31
#define B_SA_PXPEPBAR_EPVC1RCTL_VC1ID      BIT24| BIT25 | BIT26
#define N_SA_PXPEPBAR_EPVC1RCTL_VC1ID      24
#define B_SA_PXPEPBAR_EPVC1RCTL_TC1VC1M    0xFE
#define N_SA_PXPEPBAR_EPVC1RCTL_TC1VC1M    1
#define B_SA_PXPEPBAR_EPVC1RCTL_TC0VC1M    BIT0
#define R_SA_PXPEPBAR_EPVC1RSTS            0x26

///
/// REMAPBASE and REMAPLIMIT registers
///
#define R_SA_MCHBAR_REMAPBASE_OFFSET            (0x00005090)
///
/// Description of LOCK (0:0)
///  This bit will lock all writeable settings in this register, including itself.
///
#define N_SA_MCHBAR_REMAPBASE_LOCK_OFFSET       (0x0)
#define S_SA_MCHBAR_REMAPBASE_LOCK_WIDTH        (0x1)
#define B_SA_MCHBAR_REMAPBASE_LOCK_MASK         (0x1)
#define V_SA_MCHBAR_REMAPBASE_LOCK_DEFAULT      (0x0)
///
/// Description of REMAPBASE (20:35)
///  The value in this register defines the lower boundary of the Remap window. The Remap window is inclusive of this address. In the decoder A[19:0] of the Remap Base Address are assumed to be 0's. Thus the bottom of the defined memory range will be aligned to a 1MB boundary.
///  When the value in this register is greater than the value programmed into the Remap Limit register, the Remap window is disabled.
///  These bits are LT lockable.
///
#define N_SA_MCHBAR_REMAPBASE_REMAPBASE_OFFSET  (0x14)
#define S_SA_MCHBAR_REMAPBASE_REMAPBASE_WIDTH   (0x13)
#define B_SA_MCHBAR_REMAPBASE_REMAPBASE_MASK    (0x7ffff00000)
#define V_SA_MCHBAR_REMAPBASE_REMAPBASE_DEFAULT (0x0007FFFF)

#define R_SA_MCHBAR_REMAPLIMIT_OFFSET           (0x00005098)
///
/// Description of LOCK (0:0)
///  This bit will lock all writeable settings in this register, including itself.
///
#define N_SA_MCHBAR_REMAPLIMIT_LOCK_OFFSET      (0x0)
#define S_SA_MCHBAR_REMAPLIMIT_LOCK_WIDTH       (0x1)
#define B_SA_MCHBAR_REMAPLIMIT_LOCK_MASK        (0x1)
#define V_SA_MCHBAR_REMAPLIMIT_LOCK_DEFAULT     (0x0)
///
/// Description of REMAPLMT (20:35)
///  The value in this register defines the upper boundary of the Remap window. The Remap window is inclusive of this address. In the decoder A[19:0] of the remap limit address are assumed to be F's. Thus the top of the defined range will be one byte less than a 1MB boundary.
///  When the value in this register is less than the value programmed into the Remap Base register, the Remap window is disabled.
///  These Bits are LT lockable.
///
#define N_SA_MCHBAR_REMAPLIMIT_REMAPLMT_OFFSET  (0x14)
#define S_SA_MCHBAR_REMAPLIMIT_REMAPLMT_WIDTH   (0x13)
#define B_SA_MCHBAR_REMAPLIMIT_REMAPLMT_MASK    (0x7ffff00000)
#define V_SA_MCHBAR_REMAPLIMIT_REMAPLMT_DEFAULT (0x0)

//
// VCU Mailbox Definitions
//
#define R_SA_MCHBAR_VCU_MAILBOX_INTERFACE_OFFSET  0x6C00
#define R_SA_MCHBAR_VCU_MAILBOX_DATA_OFFSET       0x6C04
#define B_SA_MCHBAR_VCU_STATUS_RUN_BUSY           BIT31

#define V_SA_VCU_OPCODE_OPEN_SEQ                  0x2
#define V_SA_VCU_OPCODE_CLOSE_SEQ                 0x3
#define V_SA_VCU_OPCODE_READ_VCU_API_VER_ID       0x1
#define V_SA_VCU_OPCODE_READ_DATA                 0x7
#define V_SA_VCU_OPCODE_WRITE_DATA                0x8
#define V_SA_VCU_OPCODE_READ_CSR                  0x13
#define V_SA_VCU_OPCODE_WRITE_CSR                 0x14
#define V_SA_VCU_OPCODE_READ_MMIO                 0x15
#define V_SA_VCU_OPCODE_WRITE_MMIO                0x16


#define V_SA_VCU_SEQID_READ_CSR              0x1
#define V_SA_VCU_SEQID_WRITE_CSR             0x2
#define V_SA_VCU_SEQID_READ_MMIO             0x3
#define V_SA_VCU_SEQID_WRITE_MMIO            0x4

#define V_SA_VCU_RESPONSE_SUCCESS            0x40
#define V_SA_VCU_RESPONSE_BUSY               0x80
#define V_SA_VCU_RESPONSE_THREADUNAVAILABLE  0x82
#define V_SA_VCU_RESPONSE_ILLEGAL            0x90

///
/// VCU Miscellaneous Controls
///
#define V_SA_VCU_STATUS_BUSY_LIMIT     100
#define V_SA_VCU_RESPONSE_RETRY_LIMIT  10
#endif

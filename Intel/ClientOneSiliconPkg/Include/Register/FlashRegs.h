/** @file
  Register names for Flash registers

  Conventions:

  - Register definition format:
    Prefix_[GenerationName]_[ComponentName]_SubsystemName_RegisterSpace_RegisterName
  - Prefix:
    Definitions beginning with "R_" are registers
    Definitions beginning with "B_" are bits within registers
    Definitions beginning with "V_" are meaningful values within the bits
    Definitions beginning with "S_" are register size
    Definitions beginning with "N_" are the bit position
  - [GenerationName]:
    Three letter acronym of the generation is used (e.g. SKL,KBL,CNL etc.).
    Register name without GenerationName applies to all generations.
  - [ComponentName]:
    This field indicates the component name that the register belongs to (e.g. PCH, SA etc.)
    Register name without ComponentName applies to all components.
    Register that is specific to -H denoted by "_PCH_H_" in component name.
    Register that is specific to -LP denoted by "_PCH_LP_" in component name.
  - SubsystemName:
    This field indicates the subsystem name of the component that the register belongs to
    (e.g. PCIE, USB, SATA, GPIO, PMC etc.).
  - RegisterSpace:
    MEM - MMIO space register of subsystem.
    IO  - IO space register of subsystem.
    PCR - Private configuration register of subsystem.
    CFG - PCI configuration space register of subsystem.
  - RegisterName:
    Full register name.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#ifndef _FLASH_REGS_H_
#define _FLASH_REGS_H_

#define B_FLASH_FLCOMP_RIDS_FREQ          (BIT29 | BIT28 | BIT27)       ///< Read ID and Read Status Clock Frequency
#define N_FLASH_FLCOMP_RIDS_FREQ          27
#define B_FLASH_FLCOMP_WE_FREQ            (BIT26 | BIT25 | BIT24)       ///< Write and Erase Clock Frequency
#define N_FLASH_FLCOMP_WE_FREQ            24
#define B_FLASH_FLCOMP_FRCF_FREQ          (BIT23 | BIT22 | BIT21)       ///< Fast Read Clock Frequency
#define N_FLASH_FLCOMP_FRCF_FREQ          21
#define B_FLASH_FLCOMP_FR_SUP             BIT20                         ///< Fast Read Support.
#define B_FLASH_FLCOMP_RC_FREQ            (BIT19 | BIT18 | BIT17)       ///< Read Clock Frequency.
#define N_FLASH_FLCOMP_RC_FREQ            17
#define V_FLASH_FLCOMP_FREQ_48MHZ         0x02
#define V_FLASH_FLCOMP_FREQ_30MHZ         0x04
#define V_FLASH_FLCOMP_FREQ_17MHZ         0x06

#define N_FLASH_COMPONENTS                8                             ///< Bit position for number of Flash components
#define B_FLASH_COMPONENTS                0x3                           ///< Bit mask for number of Flash components

//
// Flash Descriptor Base Address Region (FDBAR) from Flash Region 0
//
#define R_FLASH_FDBAR_FLVALSIG            0x00                          ///< Flash Valid Signature
#define V_FLASH_FDBAR_FLVALSIG            0x0FF0A55A
#define R_FLASH_FDBAR_FLASH_MAP0          0x04
#define B_FLASH_FDBAR_FCBA                0x000000FF                    ///< Flash Component Base Address
#define B_FLASH_FDBAR_NC                  0x00000300                    ///< Number Of Components
#define N_FLASH_FDBAR_NC                  8                             ///< Number Of Components
#define V_FLASH_FDBAR_NC_1                0x00000000
#define V_FLASH_FDBAR_NC_2                0x00000100
#define B_FLASH_FDBAR_FRBA                0x00FF0000                    ///< Flash Region Base Address
#define B_FLASH_FDBAR_NR                  0x07000000                    ///< Number Of Regions
#define R_FLASH_FDBAR_FLASH_MAP1          0x08
#define B_FLASH_FDBAR_FMBA                0x000000FF                    ///< Flash Master Base Address
#define B_FLASH_FDBAR_NM                  0x00000700                    ///< Number Of Masters
#define B_FLASH_FDBAR_FPSBA               0x00FF0000                    ///< PCH Strap Base Address, [23:16] represents [11:4]
#define N_FLASH_FDBAR_FPSBA               16                            ///< PCH Strap base Address bit position
#define N_FLASH_FDBAR_FPSBA_REPR          4                             ///< PCH Strap base Address bit represents position
#define B_FLASH_FDBAR_PCHSL               0xFF000000                    ///< PCH Strap Length, [31:24] represents number of Dwords
#define N_FLASH_FDBAR_PCHSL               24                            ///< PCH Strap Length bit position
#define R_FLASH_FDBAR_FLASH_MAP2          0x0C
#define B_FLASH_FDBAR_FCPUSBA             0x00000FFC                    ///< CPU Strap Base Address [11:2]
#define N_FLASH_FDBAR_FCPUSBA             2                             ///< CPU Strap Base Address bit position
#define B_FLASH_FDBAR_CPUSL               0x00FF0000                    ///< CPU Strap Length, [23:16] represents number of Dwords
#define N_FLASH_FDBAR_CPUSL               16                            ///< CPU Strap Length bit position

//
// Flash Component Base Address (FCBA) from Flash Region 0
//
#define R_FLASH_FCBA_FLCOMP               0x00                          ///< Flash Components Register
#define B_FLASH_FLCOMP_COMP1_MASK         0xF0                          ///< Flash Component 1 Size MASK
#define N_FLASH_FLCOMP_COMP1              4                             ///< Flash Component 1 Size bit position
#define B_FLASH_FLCOMP_COMP0_MASK         0x0F                          ///< Flash Component 0 Size MASK
#define V_FLASH_FLCOMP_COMP_512KB         0x80000
//
// Descriptor Upper Map Section from Flash Region 0
//
#define R_FLASH_UMAP1                     0xEFC                         ///< Flash Upper Map 1
#define B_FLASH_UMAP1_VTBA                0x000000FF                    ///< VSCC Table Base Address
#define B_FLASH_UMAP1_VTL                 0x0000FF00                    ///< VSCC Table Length
#define B_FLASH_UMAP1_MDTBA               0xFF000000                    ///< MIP Descriptor Table Base Address
#define N_FLASH_UMAP1_MDTBA               24                            ///< MDTBA bits position
#define N_FLASH_UMAP1_MDTBA_REPR          4                             ///< MDTBA address representation position

//
// Straps location definitions
//

//
// MMP0
//
#define R_FLASH_STRAP_MMP0                 0xC4    ///< MMP0 Soft strap offset
#define B_FLASH_STRAP_MMP0                 0x10    ///< MMP0 Soft strap bit

#define R_FLASH_STRAP_SFDP                 0xF0    ///< PCH Soft Strap SFDP
#define B_FLASH_STRAP_SFDP_QIORE           BIT3    ///< Quad IO Read Enable
#define B_FLASH_STRAP_SFDP_QORE            BIT2    ///< Quad Output Read Enable
#define B_FLASH_STRAP_SFDP_DIORE           BIT1    ///< Dual IO Read Enable
#define B_FLASH_STRAP_SFDP_DORE            BIT0    ///< Dual Output Read Enable

//
// Descriptor Record 0
//
#define R_FLASH_STRAP_DSCR_0               0x00    ///< PCH Soft Strap 0
#define B_FLASH_STRAP_DSCR_0_PTT_SUPP      BIT22   ///< PTT Supported

#define R_PCH_SPI_STRP_GBETSN_DIS           0xC18    ///< GBETSN_DIS strap offset.
#define B_PCH_SPI_STRP_GBETSN_DIS           BIT3     ///< GBETSN_DIS Start Bit

#define R_PCH_SPI_STRP_THC_DIS              0xC20    ///< THC_DIS strap offset.
#define B_PCH_SPI_STRP_THC0_DIS             BIT25    ///< THC0_DIS Start Bit
#define B_PCH_SPI_STRP_THC1_DIS             BIT26    ///< THC1_DIS Start Bit

#endif

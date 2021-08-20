/** @file
  Register names for PCH P2SB device

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
  Copyright 2013 - 2019 Intel Corporation.

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
#ifndef _P2SB_REGS_H_
#define _P2SB_REGS_H_

//
// PCI to P2SB Bridge Registers (D31:F1)
//
#define PCI_DEVICE_NUMBER_PCH_P2SB                 31
#define PCI_FUNCTION_NUMBER_PCH_P2SB               1

#define V_P2SB_CFG_VENDOR_ID                       V_PCH_INTEL_VENDOR_ID

#define R_P2SB_CFG_SBREG_BAR                       0x10
#define B_P2SB_CFG_SBREG_RBA                       0xFF000000
#define R_P2SB_CFG_SBREG_BARH                      0x14
#define B_P2SB_CFG_SBREG_RBAH                      0xFFFFFFFF
#define R_P2SB_CFG_VBDF                            0x50
#define B_P2SB_CFG_VBDF_BUS                        0xFF00
#define B_P2SB_CFG_VBDF_DEV                        0x00F8
#define B_P2SB_CFG_VBDF_FUNC                       0x0007
#define R_P2SB_CFG_RCFG                            0x54
#define B_P2SB_CFG_RCFG_RPRID                      0x0000FF00
#define B_P2SB_CFG_RCFG_RSE                        BIT0
#define R_P2SB_CFG_HPTC                            0x60
#define B_P2SB_CFG_HPTC_AE                         BIT7
#define B_P2SB_CFG_HPTC_AS                         0x0003
#define N_HPET_ADDR_ASEL                           12
#define R_P2SB_CFG_IOAC                            0x64
#define B_P2SB_CFG_IOAC_AE                         BIT8
#define B_P2SB_CFG_IOAC_ASEL                       0x00FF
#define N_IO_APIC_ASEL                             12
#define R_IO_APIC_MEM_INDEX_OFFSET                 0x00
#define R_IO_APIC_MEM_DATA_OFFSET                  0x10
#define R_IO_APIC_MEM_EOI_OFFSET                   0x40
#define R_P2SB_CFG_IBDF                            0x6C
#define B_P2SB_CFG_IBDF_BUS                        0xFF00
#define B_P2SB_CFG_IBDF_DEV                        0x00F8
#define B_P2SB_CFG_IBDF_FUNC                       0x0007
#define V_P2SB_CFG_IBDF_BUS                        0
#define V_P2SB_CFG_IBDF_DEV                        30
#define V_P2SB_CFG_IBDF_FUNC                       7
#define R_P2SB_CFG_HBDF                            0x70
#define B_P2SB_CFG_HBDF_BUF                        0xFF00
#define B_P2SB_CFG_HBDF_DEV                        0x00F8
#define B_P2SB_CFG_HBDF_FUNC                       0x0007
#define V_P2SB_CFG_HBDF_BUS                        0
#define V_P2SB_CFG_HBDF_DEV                        30
#define V_P2SB_CFG_HBDF_FUNC                       6
#define R_P2SB_CFG_LFIORIEC                        0x74

//
// Definition for SBI
//
#define R_P2SB_CFG_SBIADDR                         0xD0
#define B_P2SB_CFG_SBIADDR_DESTID                  0xFF000000
#define B_P2SB_CFG_SBIADDR_RS                      0x000F0000
#define B_P2SB_CFG_SBIADDR_OFFSET                  0x0000FFFF
#define R_P2SB_CFG_SBIDATA                         0xD4
#define B_P2SB_CFG_SBIDATA_DATA                    0xFFFFFFFF
#define R_P2SB_CFG_SBISTAT                         0xD8
#define B_P2SB_CFG_SBISTAT_OPCODE                  0xFF00
#define B_P2SB_CFG_SBISTAT_POSTED                  BIT7
#define B_P2SB_CFG_SBISTAT_RESPONSE                0x0006
#define N_P2SB_CFG_SBISTAT_RESPONSE                1
#define B_P2SB_CFG_SBISTAT_INITRDY                 BIT0
#define R_P2SB_CFG_SBIRID                          0xDA
#define B_P2SB_CFG_SBIRID_FBE                      0xF000
#define B_P2SB_CFG_SBIRID_BAR                      0x0700
#define B_P2SB_CFG_SBIRID_FID                      0x00FF
#define R_P2SB_CFG_SBIEXTADDR                      0xDC
#define B_P2SB_CFG_SBIEXTADDR_ADDR                 0xFFFFFFFF

//
// Others
//
#define R_P2SB_CFG_E0                              0xE0
#define R_P2SB_CFG_E4                              0xE4
#define R_P2SB_CFG_E8                              0xE8
#define R_P2SB_CFG_EA                              0xEA
#define R_P2SB_CFG_F4                              0xF4

#define R_P2SB_CFG_200                             0x200
#define R_P2SB_CFG_204                             0x204
#define R_P2SB_CFG_208                             0x208
#define R_P2SB_CFG_20C                             0x20C
#define R_P2SB_CFG_210                             0x210
#define R_P2SB_CFG_214                             0x214
#define R_P2SB_CFG_218                             0x218
#define R_P2SB_CFG_21C                             0x21C

#define R_P2SB_CFG_EPMASK0                         0x220
#define R_P2SB_CFG_EPMASK1                         0x224
#define R_P2SB_CFG_EPMASK2                         0x228
#define R_P2SB_CFG_EPMASK3                         0x22C
#define R_P2SB_CFG_EPMASK4                         0x230
#define R_P2SB_CFG_EPMASK5                         0x234
#define R_P2SB_CFG_EPMASK6                         0x238
#define R_P2SB_CFG_EPMASK7                         0x23C

#define R_P2SB_CFG_SAIPOLCTRL                      0x240
#define R_P2SB_CFG_SAIPOLAC                        0x248

#endif

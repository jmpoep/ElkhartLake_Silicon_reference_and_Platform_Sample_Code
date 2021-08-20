/** @file
  Register names for PCH Storage and Communication Subsystem

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
#ifndef _SCS_REGS_H_
#define _SCS_REGS_H_

//
// SCS Devices proprietary PCI Config Space Registers
//
#define R_SCS_CFG_PCS                     0x84                          ///< PME Control Status
#define B_SCS_CFG_PCS_PMESTS              BIT15                         ///< PME Status
#define B_SCS_CFG_PCS_PMEEN               BIT8                          ///< PME Enable
#define B_SCS_CFG_PCS_NSS                 BIT3                          ///< No Soft Reset
#define B_SCS_CFG_PCS_PS                  (BIT1 | BIT0)                 ///< Power State
#define B_SCS_CFG_PCS_PS_D3HOT            (BIT1 | BIT0)                 ///< Power State: D3Hot State
#define R_SCS_CFG_PG_CONFIG               0xA2                          ///< PG Config
#define B_SCS_CFG_PG_CONFIG_HAE           BIT5                          ///< HA Enable
#define B_SCS_CFG_PG_CONFIG_SE            BIT3                          ///< Sleep Enable
#define B_SCS_CFG_PG_CONFIG_PGE           BIT2                          ///< PG Enable
#define B_SCS_CFG_PG_CONFIG_I3E           BIT1                          ///< I3 Enable
#define B_SCS_CFG_PG_CONFIG_PMCRE         BIT0                          ///< PMC Request Enable
#define V_SCS_CFG_BAR0_SIZE               0x1000                        ///< BAR0 size
//
// PCR registers
//
#define R_SCS_PCR_1C20                    0x1C20
#define R_SCS_PCR_4820                    0x4820
#define R_SCS_PCR_4020                    0x4020
#define R_SCS_PCR_5820                    0x5820
#define R_SCS_PCR_5C20                    0x5C20
#define R_SCS_PCR_1078                    0x1078
#endif

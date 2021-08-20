/** @file
  Register names for PCH Thermal Device for ICL

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
  Copyright 2017 - 2018 Intel Corporation.

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
#ifndef _THERMAL_REGS_H_
#define _THERMAL_REGS_H_

//
//  Thermal Device Registers
//
#define R_PMC_PWRM_THERMAL_MINTEMP                0x1500  ///< Min Temperature
#define R_PMC_PWRM_THERMAL_MAXTEMP                0x1504  ///< Max Temperature
#define R_PMC_PWRM_THERMAL_TRPTFRQ                0x1508  ///< Temperature Reporting Frequency
#define R_PMC_PWRM_THERMAL_CTEN                   0x150C  ///< Catastrophic Trip Point Enable
#define B_PMC_PWRM_THERMAL_CTEN_CTENLOCK          BIT31   ///< Policy Lock-Down Bit
#define B_PMC_PWRM_THERMAL_CTEN_CPDEN             BIT0    ///< Catastrophic Power-Down Enable
#define R_PMC_PWRM_THERMAL_ECRPTEN                0x1510  ///< EC Thermal Sensor Reporting Enable
#define B_PMC_PWRM_THERMAL_ECRPTEN_ECRPTENLOCK    BIT31   ///< Lock-Down Bit
#define B_PMC_PWRM_THERMAL_ECRPTEN_EN_RPT         BIT0    ///< Enable PMC to EC Temperature Reporting
#define R_PMC_PWRM_THERMAL_TL                     0x1520  ///< Throttle Levels
#define B_PMC_PWRM_THERMAL_TL_TLLOCK              BIT31   ///< TL LOCK
#define B_PMC_PWRM_THERMAL_TL_TT13EN              BIT30   ///< TT State 13 Enable
#define B_PMC_PWRM_THERMAL_TL_TTEN                BIT29   ///< TT Enable
#define R_PMC_PWRM_THERMAL_SWTHROT                0x1524  ///< SW Throttle (debug)
#define R_PMC_PWRM_THERMAL_TLEN                   0x1528  ///< Throttle Levels Enable
#define B_PMC_PWRM_THERMAL_TLEN_TLENLOCK          BIT31   ///< TLENLOCK
#define B_PMC_PWRM_THERMAL_TLEN_PMCTEN            BIT14   ///< PMC Throttling Enable
#define R_PMC_PWRM_THERMAL_TSAHV                  0x1530  ///< Thermal Sensor Alert High Value
#define R_PMC_PWRM_THERMAL_TSALV                  0x1534  ///< Thermal Sensor Alert Low Value
#define R_PMC_PWRM_THERMAL_TAS                    0x1538  ///< Thermal Alert Trip Status
#define R_PMC_PWRM_THERMAL_CTS                    0x153C  ///< Catastrophic Trip Status
#define R_PMC_PWRM_THERMAL_PHLC                   0x1540  ///< PCH Hot Level Control
#define B_PMC_PWRM_THERMAL_PHLC_PHLCLOCK          BIT31   ///< PHL Lock
#define B_PMC_PWRM_THERMAL_PHLC_PHLE              BIT15   ///< PHL Enable
#define R_PMC_PWRM_THERMAL_TSSX                   0x1560  ///< Temperature Sensor Control and Status
#define S_PMC_PWRM_THERMAL_TSSX                   4       ///< Size of Temperature Sensor Control and Status

#endif

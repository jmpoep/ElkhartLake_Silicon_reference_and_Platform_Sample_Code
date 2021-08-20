/** @file
  Register names for PCH PMC FIVR device

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
  Copyright 2017 - 2019 Intel Corporation.

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

@par Specification
**/
#ifndef _PCH_REGS_PMC_FIVR_H_
#define _PCH_REGS_PMC_FIVR_H_

//
// PWRM Registers
//
#define R_PMC_PWRM_EXT_RAIL_CONFIG                                    0x11B8                       ///< External Rail Config

#define B_PMC_PWRM_EXT_RAIL_CONFIG_VNN_SUPPORTED                      0xF0000000                   ///< Supported External VNN Rail configuration
#define N_PMC_PWRM_EXT_RAIL_CONFIG_VNN_SUPPORTED                      28                           ///< Supported External VNN Rail configuration
#define B_PMC_PWRM_EXT_RAIL_CONFIG_V1P05_SUPPORTED                    0x0F000000                   ///< Supported External V1P05 Rail configuration
#define N_PMC_PWRM_EXT_RAIL_CONFIG_V1P05_SUPPORTED                    24                           ///< Supported External V1P05 Rail configuration
#define B_PMC_PWRM_EXT_RAIL_CONFIG_V1P05_S0IX_SX                      0x1F00                       ///< Enable External V1P05 Rail in S0x/Sx
#define N_PMC_PWRM_EXT_RAIL_CONFIG_V1P05_S0IX_SX                      8                            ///< Enable External V1P05 Rail in S0x/Sx
#define B_PMC_PWRM_EXT_RAIL_CONFIG_VNN_S0IX_SX                        0x1F                         ///< Enable External VNN Rail in S0ix/Sx
#define N_PMC_PWRM_EXT_RAIL_CONFIG_VNN_S0IX_SX                        0                            ///< Enable External VNN Rail in S0ix/Sx

#define R_PMC_PWRM_EXT_V1P05_VR_CONFIG                                0x11C0                       ///< External v1p05 Rail Config
#define B_PMC_PWRM_EXT_V1P05_VR_CONFIG_VOLTAGE                        0x7FF0000                    ///< External v1p05 Voltage Value
#define N_PMC_PWRM_EXT_V1P05_VR_CONFIG_VOLTAGE                        16                           ///< External v1p05 Voltage Value
#define B_PMC_PWRM_EXT_V1P05_VR_CONFIG_ICC_MAX                        0xFFFF                       ///< External v1p05 Icc Max Value
#define N_PMC_PWRM_EXT_V1P05_VR_CONFIG_ICC_MAX                        0                            ///< External v1p05 Icc Max Value

#define R_PMC_PWRM_EXT_VNN_VR_CONFIG                                  0x11C4                       ///< External VNN Rail Config
#define B_PMC_PWRM_EXT_VNN_VR_CONFIG_VOLTAGE                          0x7FF0000                    ///< External VNN Voltage Value
#define N_PMC_PWRM_EXT_VNN_VR_CONFIG_VOLTAGE                          16                           ///< External VNN Voltage Value
#define B_PMC_PWRM_EXT_VNN_VR_CONFIG_ICC_MAX                          0xFFFF                       ///< External VNN Icc Max Value
#define N_PMC_PWRM_EXT_VNN_VR_CONFIG_ICC_MAX                          0                            ///< External VNN Icc Max Value

#define R_PMC_PWRM_EXT_VNN_V1P05_CTRL_HOLD_OFF                        0x11C8                       ///< Hold Off Control for V1p05
#define B_PMC_PWRM_EXT_VNN_V1P05_CTRL_HOLD_OFF_V1P05_CTRL_RAMP_TMR    0x0000FF00                   ///< V1p05 Control Ramp Timer
#define N_PMC_PWRM_EXT_VNN_V1P05_CTRL_HOLD_OFF_V1P05_CTRL_RAMP_TMR    8                            ///< V1p05 Control Ramp Timer
#define B_PMC_PWRM_EXT_VNN_V1P05_CTRL_HOLD_OFF_VNN_CTRL_RAMP_TMR      0x000000FF                   ///< VNN Control Ramp Timer
#define N_PMC_PWRM_EXT_VNN_V1P05_CTRL_HOLD_OFF_VNN_CTRL_RAMP_TMR      0                            ///< VNN Control Ramp Timer

#define R_PMC_PWRM_EXT_FET_RAMP_CFG                                   0x11CC
#define B_PMC_PWRM_EXT_FET_RAMP_CFG_V1P05_PHY_FRT_LOCK                BIT15
#define B_PMC_PWRM_EXT_FET_RAMP_CFG_V1P05_IS_FRT_LOCK                 BIT31

#define R_PMC_PWRM_VCCIN_AUX_CFG1                                     0x11D0                       ///< VCCIN AUX CONFIG Register1
#define B_PMC_PWRM_VCCIN_AUX_CFG1_LCM_HCM_VOLT_TRANS_TIME             0xFF0000                     ///< Low Current Mode Voltage to High Current Mode Voltage Transition Time
#define N_PMC_PWRM_VCCIN_AUX_CFG1_LCM_HCM_VOLT_TRANS_TIME             16                           ///< Low Current Mode Voltage to High Current Mode Voltage Transition Time
#define B_PMC_PWRM_VCCIN_AUX_CFG1_RMV_HCM_VOLT_TRANS_TIME             0xFF00                       ///< Retention Mode Voltage to High Current Mode Voltage Transition Time
#define N_PMC_PWRM_VCCIN_AUX_CFG1_RMV_HCM_VOLT_TRANS_TIME             8                            ///< Retention Mode Voltage to High Current Mode Voltage Transition Time
#define B_PMC_PWRM_VCCIN_AUX_CFG1_RMV_LCM_VOLT_TRANS_TIME             0xFF                         ///< Retention Mode Voltage to Low Current Mode Voltage Transition Time
#define N_PMC_PWRM_VCCIN_AUX_CFG1_RMV_LCM_VOLT_TRANS_TIME             0                            ///< Retention Mode Voltage to Low Current Mode Voltage Transition Time

#define R_PMC_PWRM_VCCIN_AUX_CFG2                                     0x11D4                       ///< VCCIN AUX CONFIG Register2
#define B_PMC_PWRM_VCCIN_AUX_CFG2_OFF_HCM_VOLT_TRANS_TIME             0x3FF                        ///< Voltage transition time when PCH changes the VCCIN_AUX regulator from 0V to the high current mode voltage
#define N_PMC_PWRM_VCCIN_AUX_CFG2_OFF_HCM_VOLT_TRANS_TIME             0                            ///< Voltage transition time when PCH changes the VCCIN_AUX regulator from 0V to the high current mode voltage

#define R_PMC_PWRM_CPPM_FIVR_POL1A                                    0x11F0                       ///< Register Configures If And How CPPM Interacts With FIVR
#define B_PMC_PWRM_CPPM_FIVR_POL1A_CPPM_FIVR_VOLT_QUAL                BIT30                        ///< CPPM Qualifier Enable for FIVR
#define B_PMC_PWRM_CPPM_FIVR_POL1A_LTR_FIVR_VOLT_SEL                  BIT29                        ///< ASLT/PLT SELECTION for FIVR
#define B_PMC_PWRM_CPPM_FIVR_POL1A_LTR_FIVR_VOLT_THRESH               0x1FF                        ///<  LTR Threshold for FIVR
#define V_PMC_PWRM_CPPM_FIVR_POL1A_LTR_FIVR_VOLT_THRESH               0x4
#define R_PMC_PWRM_CPPM_FIVR_POL1B                                    0x11F4                       ///< Register Configures If And How CPPM Interacts With FIVR
#define B_PMC_PWRM_CPPM_FIVR_POL1B_TNTE_FIVR_VOLT_PRE_WAKE            0x1FFFF                      ///< TNTE PreWake for FIVR Voltage

#define B_PMC_PWRM_CFG3_BIOS_FIVR_DYN_EN                              BIT28                        ///< Enable Dynamic FIVR Management

#endif // _PCH_REGS_PMC_FIVR_H_

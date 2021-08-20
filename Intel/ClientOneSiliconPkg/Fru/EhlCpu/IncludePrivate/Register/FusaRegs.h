/** @file
  Register definition for Functional Safety Registers

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
  Copyright 2019 Intel Corporation.

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
#ifndef _FUSA_REGS_H_
#define _FUSA_REGS_H_

///
/// Display and Graphics Fusa Configuration Registers
///
#define R_SA_GTMMADR_SF_CTL_0                             0x0B04   ///<SF_CONTROL_0
#define B_SA_GTMMADR_DE_FUSA_SF_CTL_LOCK_BIT              BIT0     ///<SF_CONTROL_0_LOCK
#define R_SA_PCI_DEVICECTL_OFFSET                         0x78     ///<DEVICECTL_0_2_0_PCI 0:2
#define R_SA_GTMMADR_GT_ERR_COR_OFFSET                    0x100130 ///<GT_ERR_COR 16:31
#define R_SA_GTMMADR_GT_ERR_NONFATAL_OFFSET               0x100134 ///<GT_ERR_NONFATAL
#define R_SA_GTMMADR_GT_ERR_FATAL_OFFSET                  0x100138 ///<GT_ERR_FATAL

#define R_SA_GTMMADR_DE_FUSA_PARITY_CTRL_OFFSET           0x100140 ///<DE_FUSA_IOSF_PARITY_CNTRL
#define B_SA_GTMMADR_DE_FUSA_IOSF_PARITY_CMD_BIT          BIT9     ///<DE_FUSA_IOSF_PARITY_CNTRL
#define B_SA_GTMMADR_DE_FUSA_IOSF_PARITY_DATA_BIT         BIT8     ///<DE_FUSA_IOSF_PARITY_CNTRL
#define B_SA_GTMMADR_DE_FUSA_DIP_PARITY_CMD_BIT           BIT25    ///<DE_FUSA_IOSF_PARITY_CNTRL
#define B_SA_GTMMADR_DE_FUSA_DIP_PARITY_DATA_BIT          BIT24    ///<DE_FUSA_IOSF_PARITY_CNTRL
#define B_SA_GTMMADR_DE_FUSA_IOSF_PARITY_CTL_LOCK_BIT     BIT0     ///<DE_FUSA_IOSF_PARITY_CNTRL_LOCK

#define R_SA_GTMMADR_DISPLAY_ERR_COR_OFFSET               0x44210  ///<DISPLAY_ERR_COR
#define R_SA_GTMMADR_DISPLAY_ERR_NONFATAL_OFFSET          0x44218  ///<DISPLAY_ERR_NONFATAL
#define R_SA_GTMMADR_DISPLAY_ERR_FATAL_OFFSET             0x44214  ///<DISPLAY_ERR_FATAL

///
/// Opio Fusa Configuration Registers
///
#define R_SA_DMIBAR_FUSA_E2EPARITY_CTL_OFFSET             0x500     ///< OPIO FUSA E2E PARITY ENABLE
#define B_SA_DMIBAR_PARITY_GEN_EN                         BIT30
#define B_SA_DMIBAR_DATA_PARITY_FATAL_CFG                 BIT26
#define B_SA_DMIBAR_DATA_PARITY_FATAL_OPI_CFG             BIT27

///
/// Psf Fusa Configuration Registers
///
#define R_PCH_PSF_PCR_GLOBAL_CONFIG                     0x4000      ///< PSF Segment Global Configuration Register
#define B_PCH_PSF_PCR_GLOBAL_CONFIG_ENCMPADET1          BIT11
#define B_PCH_PSF_PCR_GLOBAL_CONFIG_ENCMPADET2          BIT10
#endif

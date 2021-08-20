/** @file
  Register names for PSF block
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
#ifndef _CPU_PSF_REGS_H_
#define _CPU_PSF_REGS_H_

#define R_SA_PSF1_T0_SHDW_TRACE_HUB_D8F0_ACPI_REG_BASE  0x0100             ///< D8F0 PSF base address GNA
#define R_SA_PSF1_T0_SHDW_TRACE_HUB_D9F0_ACPI_REG_BASE  0x0180             ///< D9F0 PSF base address North Trace Hub (PCI)
#define R_SA_PSF1_T0_SHDW_TRACE_HUB_D9F1_ACPI_REG_BASE  0x0200             ///< D9F1 PSF base address North Trace Hub (ACPI)

//
// PSFx PCRs definitions
//
#define R_SA_PSF1_T0_SHDW_BAR0                     0                       ///< PCI BAR0
#define R_SA_PSF1_T0_SHDW_BAR1                     0x04                    ///< PCI BAR1
#define R_SA_PSF1_T0_SHDW_BAR2                     0x08                    ///< PCI BAR2
#define R_SA_PSF1_T0_SHDW_BAR3                     0x0C                    ///< PCI BAR3
#define R_SA_PSF1_T0_SHDW_BAR4                     0x10                    ///< PCI BAR4
#define R_SA_PSF1_T0_SHDW_PCIEN                    0x1C                    ///< PCI configuration space enable bits
#define B_SA_PSF1_T0_SHDW_PCIEN_BAR0DIS            BIT16                   ///< Disable BAR0
#define B_SA_PSF1_T0_SHDW_PCIEN_BAR1DIS            BIT17                   ///< Disable BAR1
#define B_SA_PSF1_T0_SHDW_PCIEN_BAR2DIS            BIT18                   ///< Disable BAR2
#define B_SA_PSF1_T0_SHDW_PCIEN_BAR3DIS            BIT19                   ///< Disable BAR3
#define B_SA_PSF1_T0_SHDW_PCIEN_BAR4DIS            BIT20                   ///< Disable BAR4
#define B_SA_PSF1_T0_SHDW_PCIEN_BAR5DIS            BIT21                   ///< Disable BAR5
#define B_SA_PSF1_T0_SHDW_PCIEN_FUNDIS             BIT8                    ///< Function disable
#define B_SA_PSF1_T0_SHDW_PCIEN_MEMEN              BIT1                    ///< Memory decoding enable
#define B_SA_PSF1_T0_SHDW_PCIEN_IOEN               BIT0                    ///< IO decoding enable
#define R_SA_PSF1_T0_SHDW_PMCSR                    0x20                    ///< PCI power management configuration
#define B_SA_PSF1_T0_SHDW_PMCSR_PWRST              (BIT1 | BIT0)           ///< Power status
#define R_SA_PSF1_T0_SHDW_CFG_DIS                  0x38                    ///< PCI configuration disable
#define B_SA_PSF1_T0_SHDW_CFG_DIS_CFGDIS           BIT0                    ///< config disable

#endif

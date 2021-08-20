/** @file
  Register names for PCH DMI SIP14

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
  Copyright 2018 Intel Corporation.

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
#ifndef _PCH_DMI14_REGS_H_
#define _PCH_DMI14_REGS_H_

//
// DMI Chipset Configuration Registers (PID:DMI)
//

//
// VC Configuration (Common)
//
#define R_PCH_DMI14_PCR_V0CTL                      0x2014                      ///< Virtual channel 0 resource control
#define R_PCH_DMI14_PCR_V0STS                      0x201A                      ///< Virtual channel 0 status
#define R_PCH_DMI14_PCR_V1CTL                      0x2020                      ///< Virtual channel 1 resource control
#define R_PCH_DMI14_PCR_V1STS                      0x2026                      ///< Virtual channel 1 status
#define R_PCH_DMI14_PCR_VMCTL                      0x2040                      ///< ME Virtual Channel (VCm) resource control
#define R_PCH_DMI14_PCR_VMSTS                      0x2046                      ///< ME Virtual Channel Resource Status
#define R_PCH_DMI14_PCR_UEM                        0x2088                      ///< Uncorrectable Error Mask
#define R_PCH_DMI14_PCR_REC                        0x20AC                      ///< Root Error Command

//
// Internal Link Configuration (DMI Only)
//
#define R_PCH_DMI14_PCR_LCTL                       0x21A8                      ///< Link Control
#define B_PCH_DMI14_PCR_LCTL_ES                    BIT7

//
// DMI Control
//
#define R_PCH_DMI14_PCR_DMIC                       0x2234                              ///< DMI Control
#define B_PCH_DMI14_PCR_DMIC_SRL                   BIT31                               ///< Secured register lock
#define B_PCH_DMI14_PCR_DMIC_DMICGEN               (BIT4 | BIT3 | BIT2 | BIT1 | BIT0)  ///< DMI Clock Gate Enable
#define R_PCH_DMI14_PCR_DMIHWAWC                   0x2238                              ///< DMI HW Autonomus Width Control
#define R_PCH_DMI14_PCR_IPCS                       0x223C                              ///< IOSF Primary Control And Status
#define B_PCH_DMI14_PCR_IPCS_PSS                   BIT15                               ///< IOSF Primary SAI Select
#define R_PCH_DMI14_PCR_IOSFSBCS                   0x223E                              ///< IOSF Sideband Control and Status

#define R_PCH_DMI14_PCR_2300                       0x2300
#define R_PCH_DMI14_PCR_2304                       0x2304
#define R_PCH_DMI14_PCR_2310                       0x2310
#define R_PCH_DMI14_PCR_2314                       0x2314
#define R_PCH_DMI14_PCR_2320                       0x2320
#define R_PCH_DMI14_PCR_232C                       0x232C
#define R_PCH_DMI14_PCR_2334                       0x2334
#define R_PCH_DMI14_PCR_2340                       0x2340
#define R_PCH_DMI14_PCR_2344                       0x2344
#define R_PCH_DMI14_PCR_2348                       0x2348
#define R_PCH_DMI14_PCR_234C                       0x234C

#define R_PCH_DMI14_PCR_2400                       0x2400
//
// Port Configuration Extension(DMI Only)
//
#define R_PCH_DMI14_PCR_G3L0SCTL                   0x2478                      ///< GEN3 L0s Control

//
// OP-DMI Specific Registers (OP-DMI Only)
//
#define R_PCH_OPDMI14_PCR_LCTL                      0x2600                      ///< Link Control
#define R_PCH_OPDMI14_PCR_STC                       0x260C                      ///< Sideband Timing Control
#define R_PCH_OPDMI14_PCR_LPMC                      0x2614                      ///< Link Power Management Control
#define R_PCH_OPDMI14_PCR_LCFG                      0x2618                      ///< Link Configuration

#endif

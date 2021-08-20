/** @file
  Register names for DMI and OP-DMI

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
  Copyright 2014 - 2017 Intel Corporation.

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
#ifndef _PCH_REGS_DMI_H_
#define _PCH_REGS_DMI_H_

//
// DMI Chipset Configuration Registers (PID:DMI)
//

//
// VC Configuration (Common)
//
#define R_PCH_DMI_PCR_V0CTL                  0x2014                      ///< Virtual channel 0 resource control
#define B_PCH_DMI_PCR_V0CTL_EN               BIT31
#define B_PCH_DMI_PCR_V0CTL_ID               (7 << 24)                   ///< Bit[26:24]
#define N_PCH_DMI_PCR_V0CTL_ID               24
#define V_PCH_DMI_PCR_V0CTL_ETVM_MASK        0xFC00
#define V_PCH_DMI_PCR_V0CTL_TVM_MASK         0x7E
#define R_PCH_DMI_PCR_V0STS                  0x201A                      ///< Virtual channel 0 status
#define B_PCH_DMI_PCR_V0STS_NP               BIT1
#define R_PCH_DMI_PCR_V1CTL                  0x2020                      ///< Virtual channel 1 resource control
#define B_PCH_DMI_PCR_V1CTL_EN               BIT31
#define B_PCH_DMI_PCR_V1CTL_ID               (0x0F << 24)                ///< Bit[27:24]
#define N_PCH_DMI_PCR_V1CTL_ID               24
#define V_PCH_DMI_PCR_V1CTL_ETVM_MASK        0xFC00
#define V_PCH_DMI_PCR_V1CTL_TVM_MASK         0xFE
#define R_PCH_DMI_PCR_V1STS                  0x2026                      ///< Virtual channel 1 status
#define B_PCH_DMI_PCR_V1STS_NP               BIT1
#define R_PCH_DMI_PCR_VMCTL                  0x2040                      ///< ME Virtual Channel (VCm) resource control
#define R_PCH_DMI_PCR_VMSTS                  0x2046                      ///< ME Virtual Channel Resource Status
#define R_PCH_DMI_PCR_UEM                    0x2088                      ///< Uncorrectable Error Mask
#define R_PCH_DMI_PCR_REC                    0x20AC                      ///< Root Error Command

//
// Internal Link Configuration (DMI Only)
//
#define R_PCH_DMI_PCR_LCAP                   0x204C                      ///< Link Capabilities
#define B_PCH_DMI_PCR_LCAP_EL1               (BIT17 | BIT16 | BIT15)     ///< L1 Exit Latency
#define N_PCH_DMI_PCR_LCAP_EL1               15                          ///< L1 Exit Latency
#define V_PCH_DMI_PCR_LCAP_EL1_8US_16US      0x4                         ///< L1 Exit Latency = 8us to less than 16us
#define B_PCH_DMI_PCR_LCAP_EL0               (BIT14 | BIT13 | BIT12)     ///< L0 Exit Latency
#define N_PCH_DMI_PCR_LCAP_EL0               12                          ///< L0 Exit Latency
#define V_PCH_DMI_PCR_LCAP_EL0_256NS_512NS   0x3                         ///< L0 Exit Latency = 256ns to less than 512ns
#define B_PCH_DMI_PCR_LCAP_APMS              (BIT11 | BIT10)             ///< L0 is supported on DMI
#define B_PCH_DMI_PCR_LCAP_MLW               0x000003F0
#define B_PCH_DMI_PCR_LCAP_MLS               0x0000000F
#define R_PCH_DMI_PCR_LCTL                   0x21A8                      ///< Link Control
#define B_PCH_DMI_PCR_LCTL_ES                BIT7
#define B_PCH_DMI_PCR_LCTL_ASPM              (BIT1 | BIT0)               ///< Link ASPM
#define R_PCH_DMI_PCR_LSTS                   0x21AA                      ///< Link Status
#define R_PCH_DMI_PCR_LCTL2                  0x2170                      ///< Link Control 2
#define R_PCH_DMI_PCR_LSTS2                  0x21B2                      ///< Link Status 2

//
// North Port Error Injection Configuration (DMI Only)
//
#define R_PCH_DMI_PCR_DMIEN                  0x2230                      ///< DMI Error Injection Enable

//
// DMI Control
//
#define R_PCH_DMI_PCR_DMIC                   0x2234                              ///< DMI Control
#define B_PCH_DMI_PCR_DMIC_SRL               BIT31                               ///< Secured register lock
#define B_PCH_DMI_PCR_DMIC_DMICGEN           (BIT4 | BIT3 | BIT2 | BIT1 | BIT0)  ///< DMI Clock Gate Enable
#define R_PCH_DMI_PCR_DMIHWAWC               0x2238                              ///< DMI HW Autonomus Width Control
#define R_PCH_DMI_PCR_IPCS                   0x223C                              ///< IOSF Primary Control And Status
#define B_PCH_DMI_PCR_IPCS_PSS               BIT15                               ///< IOSF Primary SAI Select
#define R_PCH_DMI_PCR_IOSFSBCS               0x223E                              ///< IOSF Sideband Control and Status
#define B_PCH_DMI_PCR_IOSFSBCS_DMICGEN       (BIT6 | BIT5 | BIT3 | BIT2)         ///< DMI Clock Gate Enable

#define R_PCH_DMI_PCR_2300                   0x2300
#define R_PCH_DMI_PCR_2304                   0x2304
#define R_PCH_DMI_PCR_2310                   0x2310
#define R_PCH_DMI_PCR_2314                   0x2314
#define R_PCH_DMI_PCR_2320                   0x2320
#define R_PCH_DMI_PCR_2324                   0x2324
#define R_PCH_DMI_PCR_232C                   0x232C
#define R_PCH_DMI_PCR_2334                   0x2334
#define R_PCH_DMI_PCR_2338                   0x2338
#define R_PCH_DMI_PCR_2340                   0x2340
#define R_PCH_DMI_PCR_2344                   0x2344
#define R_PCH_DMI_PCR_2348                   0x2348
#define R_PCH_DMI_PCR_234C                   0x234C

#define R_PCH_DMI_PCR_2400                   0x2400
//
// Port Configuration Extension(DMI Only)
//
#define R_PCH_DMI_PCR_G3L0SCTL               0x2478                      ///< GEN3 L0s Control

//
// OP-DMI Specific Registers (OP-DMI Only)
//
#define R_PCH_OPDMI_PCR_LCTL                  0x2600                      ///< Link Control
#define R_PCH_OPDMI_PCR_STC                   0x260C                      ///< Sideband Timing Control
#define R_PCH_OPDMI_PCR_LPMC                  0x2614                      ///< Link Power Management Control
#define R_PCH_OPDMI_PCR_LCFG                  0x2618                      ///< Link Configuration

//
// DMI Source Decode PCRs (Common)
//
#define R_PCH_DMI_PCR_PCIEPAR1E         0x2700                ///< PCIE Port IOxAPIC Range 1 Enable
#define R_PCH_DMI_PCR_PCIEPAR2E         0x2704                ///< PCIE Port IOxAPIC Range 2 Enable
#define R_PCH_DMI_PCR_PCIEPAR3E         0x2708                ///< PCIE Port IOxAPIC Range 3 Enable
#define R_PCH_DMI_PCR_PCIEPAR4E         0x270C                ///< PCIE Port IOxAPIC Range 4 Enable
#define R_PCH_DMI_PCR_PCIEPAR1DID       0x2710                ///< PCIE Port IOxAPIC Range 1 Destination ID
#define R_PCH_DMI_PCR_PCIEPAR2DID       0x2714                ///< PCIE Port IOxAPIC Range 2 Destination ID
#define R_PCH_DMI_PCR_PCIEPAR3DID       0x2718                ///< PCIE Port IOxAPIC Range 3 Destination ID
#define R_PCH_DMI_PCR_PCIEPAR4DID       0x271C                ///< PCIE Port IOxAPIC Range 4 Destination ID
#define R_PCH_DMI_PCR_P2SBIOR           0x2720                ///< P2SB IO Range
#define R_PCH_DMI_PCR_TTTBARB           0x2724                ///< Thermal Throttling BIOS Assigned Thermal Base Address
#define R_PCH_DMI_PCR_TTTBARBH          0x2728                ///< Thermal Throttling BIOS Assigned Thermal Base High Address
#define R_PCH_DMI_PCR_LPCLGIR1          0x2730                ///< LPC Generic I/O Range 1
#define R_PCH_DMI_PCR_LPCLGIR2          0x2734                ///< LPC Generic I/O Range 2
#define R_PCH_DMI_PCR_LPCLGIR3          0x2738                ///< LPC Generic I/O Range 3
#define R_PCH_DMI_PCR_LPCLGIR4          0x273C                ///< LPC Generic I/O Range 4
#define R_PCH_DMI_PCR_LPCGMR            0x2740                ///< LPC Generic Memory Range
#define R_PCH_DMI_PCR_SEGIR             0x27BC                ///< Second ESPI Generic I/O Range
#define R_PCH_DMI_PCR_SEGMR             0x27C0                ///< Second ESPI Generic Memory Range
#define R_PCH_DMI_PCR_LPCBDE            0x2744                ///< LPC BIOS Decode Enable
#define R_PCH_DMI_PCR_UCPR              0x2748                ///< uCode Patch Region
#define B_PCH_DMI_PCR_UCPR_UPRE         BIT0                  ///< uCode Patch Region Enable
#define R_PCH_DMI_PCR_GCS               0x274C                ///< Generic Control and Status
#define B_PCH_DMI_PCR_RPRDID            0xFFFF0000            ///< RPR Destination ID
#define B_PCH_DMI_PCR_BBS               BIT10                 ///< Boot BIOS Strap
#define B_PCH_DMI_PCR_RPR               BIT11                 ///< Reserved Page Route
#define B_PCH_DMI_PCR_BILD              BIT0                  ///< BIOS Interface Lock-Down
#define R_PCH_DMI_PCR_IOT1              0x2750                ///< I/O Trap Register 1
#define R_PCH_DMI_PCR_IOT2              0x2758                ///< I/O Trap Register 2
#define R_PCH_DMI_PCR_IOT3              0x2760                ///< I/O Trap Register 3
#define R_PCH_DMI_PCR_IOT4              0x2768                ///< I/O Trap Register 4
#define R_PCH_DMI_PCR_LPCIOD            0x2770                ///< LPC I/O Decode Ranges
#define R_PCH_DMI_PCR_LPCIOE            0x2774                ///< LPC I/O Enables
#define R_PCH_DMI_PCR_TCOBASE           0x2778                ///< TCO Base Address
#define B_PCH_DMI_PCR_TCOBASE_TCOBA     0xFFE0                ///< TCO Base Address Mask
#define R_PCH_DMI_PCR_GPMR1             0x277C                ///< General Purpose Memory Range 1
#define R_PCH_DMI_PCR_GPMR1DID          0x2780                ///< General Purpose Memory Range 1 Destination ID
#define R_PCH_DMI_PCR_GPMR2             0x2784                ///< General Purpose Memory Range 2
#define R_PCH_DMI_PCR_GPMR2DID          0x2788                ///< General Purpose Memory Range 2 Destination ID
#define R_PCH_DMI_PCR_GPMR3             0x278C                ///< General Purpose Memory Range 3
#define R_PCH_DMI_PCR_GPMR3DID          0x2790                ///< General Purpose Memory Range 3 Destination ID
#define R_PCH_DMI_PCR_GPIOR1            0x2794                ///< General Purpose I/O Range 1
#define R_PCH_DMI_PCR_GPIOR1DID         0x2798                ///< General Purpose I/O Range 1 Destination ID
#define R_PCH_DMI_PCR_GPIOR2            0x279C                ///< General Purpose I/O Range 2
#define R_PCH_DMI_PCR_GPIOR2DID         0x27A0                ///< General Purpose I/O Range 2 Destination ID
#define R_PCH_DMI_PCR_GPIOR3            0x27A4                ///< General Purpose I/O Range 3
#define R_PCH_DMI_PCR_GPIOR3DID         0x27A8                ///< General Purpose I/O Range 3 Destination ID

//
// Opi PHY registers
//
#define R_PCH_OPIPHY_PCR_0000           0x0000
#define R_PCH_OPIPHY_PCR_0110           0x0110
#define R_PCH_OPIPHY_PCR_0118           0x0118
#define R_PCH_OPIPHY_PCR_011C           0x011C
#define R_PCH_OPIPHY_PCR_0354           0x0354
#define R_PCH_OPIPHY_PCR_B104           0xB104
#define R_PCH_OPIPHY_PCR_B10C           0xB10C

#endif

/** @file
  Register names for PCH private chipset register

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
#ifndef _PCH_REGS_PCR_H_
#define _PCH_REGS_PCR_H_

/**
  Definition for SBI PID
  The PCH_SBI_PID defines the PID for PCR MMIO programming and PCH SBI programming as well.
**/
#define PID_CNVI       0x73
#define PID_ICLK       0xAD
#define PID_OPIPHY     0xAC
#define PID_MODPHY0    0xAB
#define PID_MODPHY1    0xAA
#define PID_MODPHY2    0xA9
#define PID_MODPHY3    0xA8
#define PID_USB2       0xCA
#define PID_DMI        0x88
#define PID_PSTH       0x89
#define PID_SATA       0xD9
#define PID_DSP        0xD7
#define PID_ESPISPI    0x72
#define PID_FIA        0xCF
#define PID_SPF        0x85
#define PID_SPE        0x84
#define PID_SPD        0x83
#define PID_SPC        0x82
#define PID_SPB        0x81
#define PID_SPA        0x80
#define PID_THC1       0xA3
#define PID_THC0       0xA2
#define PID_XHCI       0x70
#define PID_OTG        0x71
#define PID_SERIALIO   0xCB
#define PID_PSE        0xBE
#define PID_PSEBR      0xBF
#define PID_ISH        0xBE
#define PID_ISHBR      0xBF
#define PID_SCI        0xC8
#define PID_SDX        0x53
#define PID_EMMC       0x51
#define PID_UFSX2      0x50
#define PID_LPC        0xC7
#define PID_SMB        0xC6
#define PID_P2S        0xC5
#define PID_ITSS       0xC4
#define PID_RTC_HOST   0xC3
#define PID_IEH        0xC2
#define PID_DTS0       0xB2
#define PID_DTS1       0xB3
#define PID_DTS2       0xB4
#define PID_GBE        0xDB
#define PID_P2D        0xA0
#define PID_ICC        0xDC
#define PID_MMP_UFSX2A 0xB1
#define PID_MMP_UFSX2B 0xB0
#define PID_PMC        0xCC
#define PID_PMCBR      0xCD
#define PID_TAP2IOSFSB 0xDF
#define PID_ENDEBUG    0xDE
#define PID_DCI        0xB8
#define PID_DFXAGG     0xB7
#define PID_NPK        0xB6
#define PID_FUSE       0xD5
#define PID_DRNG       0xD2
#define PID_IOSFSB2TAP 0x66
#define PID_TAM        0x65
#define PID_FSPROX4    0x64
#define PID_FSPROX3    0x63
#define PID_FSPROX2    0x62
#define PID_FSPROX1    0x61
#define PID_FSPROX0    0x60
#define PID_PSF5       0x7F
#define PID_PSF7       0x7E
#define PID_PSF8       0x7D
#define PID_PSF9       0x7C
#define PID_PSF4       0xBD
#define PID_PSF3       0xBC
#define PID_PSF2       0xBB
#define PID_PSF1       0xBA
#define PID_GPIOCOM0   0x6E
#define PID_GPIOCOM1   0x6D
#define PID_GPIOCOM2   0x6C
#define PID_GPIOCOM3   0x6B
#define PID_GPIOCOM4   0x6A
#define PID_GPIOCOM5   0x69
#define PID_CSME15     0x9F
#define PID_CSME14     0x9E
#define PID_CSME13     0x9D
#define PID_CSME12     0x9C
#define PID_CSME11     0x9B
#define PID_CSME10     0x9A
#define PID_CSME9      0x99
#define PID_CSME8      0x98
#define PID_CSME7      0x97
#define PID_CSME6      0x96
#define PID_CSME5      0x95
#define PID_CSME4      0x94
#define PID_CSME3      0x93
#define PID_CSME2      0x92
#define PID_CSME1      0x91
#define PID_CSME0      0x90
#define PID_CSME_PSF   0x8F
#define PID_HOTHAM     0xB9
#define PID_CSMERTC    0x8E
#define PID_TSN        0xDA

#endif

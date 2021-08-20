/** @file
  Register names for SCI device

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

@par Specification
**/
#ifndef _SCI_REGS_H_
#define _SCI_REGS_H_

//
// SCI configuration registers (D26:F3)
//
#define PCI_DEVICE_NUMBER_SCI     26
#define PCI_FUNCTION_NUMBER_SCI   3

// SCI boot status success
#define V_SCI_MEM_BOOT_STATUS         0x42544F4B    // "BTOK"

//
// SCI MMIO space registers
//
#define R_SCI_MEM_SCRATCHPAD          0x0
#define R_SCI_MEM_DOORBELL_IN         0x14
#define B_SCI_MEM_DRBLIN_CHECK        BIT0
#define R_SCI_MEM_DOORBELL_OUT        0x2C
#define R_SCI_MEM_HOST_INTR_STATUS    0x34
#define R_SCI_MEM_HOST_INTR_MASK      0x3C
#define B_SCI_MEM_DRBLIN_INTR         BIT0
#define B_SCI_MEM_DRBLOUT_INTR        BIT1
#define R_SCI_MEM_TLP_CNT             0x40
#define R_SCI_MEM_RX_PKT_LENGTH       0x44
#define B_SCI_MEM_DRBLOUT_CHECK       BIT0
#define R_SCI_MEM_MB_RAM_RX           0x400   // to SCI
#define R_SCI_MEM_MB_RAM_TX           0x800   // from SCI

//
// SCI Iosf2Ocp bridge configuration registers
//
#define R_SCI_PCR_PMCTL               0x1D0
#define R_SCI_PCR_PCICFGCTR_BASE      0x200
#define B_SCI_PCR_PCICFGCTR_BAR1DIS   BIT7

#endif

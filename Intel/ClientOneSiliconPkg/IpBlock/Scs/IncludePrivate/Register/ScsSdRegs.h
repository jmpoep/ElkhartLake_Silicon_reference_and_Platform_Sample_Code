/** @file
  Register definitions for SD controllers on SCS.

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

#ifndef _SCS_SD_REGS_H_
#define _SCS_SD_REGS_H_

//
// SD Devices MMIO Space Register
//
#define R_SCS_MEM_DMAADR                                    0x00
#define R_SCS_MEM_BLKSZ                                     0x04
#define R_SCS_MEM_BLKCNT                                    0x06
#define R_SCS_MEM_CMDARG                                    0x08
#define R_SCS_MEM_XFRMODE                                   0x0C
#define B_SCS_MEM_XFRMODE_DMA_EN                            BIT0
#define B_SCS_MEM_XFRMODE_BLKCNT_EN                         BIT1
#define B_SCS_MEM_XFRMODE_AUTOCMD_EN_MASK                   (BIT2 | BIT3)
#define V_SCS_MEM_XFRMODE_AUTOCMD12_EN                      1
#define B_SCS_MEM_XFRMODE_DATA_TRANS_DIR                    BIT4               ///< 1: Read (Card to Host), 0: Write (Host to Card)
#define B_SCS_MEM_XFRMODE_MULTI_SINGLE_BLK                  BIT5               ///< 1: Multiple Block, 0: Single Block
#define R_SCS_MEM_SDCMD                                     0x0E
#define B_SCS_MEM_SDCMD_RESP_TYPE_SEL_MASK                  (BIT0 | BIT1)
#define V_SCS_MEM_SDCMD_RESP_TYPE_SEL_NO_RESP               0
#define V_SCS_MEM_SDCMD_RESP_TYPE_SEL_RESP136               1
#define V_SCS_MEM_SDCMD_RESP_TYPE_SEL_RESP48                2
#define V_SCS_MEM_SDCMD_RESP_TYPE_SEL_RESP48_CHK            3
#define B_SCS_MEM_SDCMD_CMD_CRC_CHECK_EN                    BIT3
#define B_SCS_MEM_SDCMD_CMD_INDEX_CHECK_EN                  BIT4
#define B_SCS_MEM_SDCMD_DATA_PRESENT_SEL                    BIT5
#define R_SCS_MEM_RESP                                      0x10
#define R_SCS_MEM_BUFDATAPORT                               0x20
#define R_SCS_MEM_PSTATE                                    0x24
#define B_SCS_MEM_PSTATE_DAT0                               BIT20
#define R_SCS_MEM_PWRCTL                                    0x29
#define R_SCS_MEM_CLKCTL                                    0x2C
#define R_SCS_MEM_TIMEOUT_CTL                               0x2E               ///< Timeout Control
#define B_SCS_MEM_TIMEOUT_CTL_DTCV                          0x0F               ///< Data Timeout Counter Value
#define R_SCS_MEM_SWRST                                     0x2F
#define B_SCS_MEM_SWRST_CMDLINE                             BIT1
#define B_SCS_MEM_SWRST_DATALINE                            BIT2
#define R_SCS_MEM_NINTSTS                                   0x30
#define B_SCS_MEM_NINTSTS_MASK                              0xFFFF
#define B_SCS_MEM_NINTSTS_CLEAR_MASK                        0x60FF
#define B_SCS_MEM_NINTSTS_CMD_COMPLETE                      BIT0
#define B_SCS_MEM_NINTSTS_TRANSFER_COMPLETE                 BIT1
#define B_SCS_MEM_NINTSTS_DMA_INTERRUPT                     BIT3
#define B_SCS_MEM_NINTSTS_BUF_READ_READY_INTR               BIT5
#define R_SCS_MEM_ERINTSTS                                  0x32
#define B_SCS_MEM_ERINTSTS_MASK                             0x13FF
#define B_SCS_MEM_ERINTSTS_CLEAR_MASK                       0x13FF
#define R_SCS_MEM_NINTEN                                    0x34
#define B_SCS_MEM_NINTEN_MASK                               0x7FFF
#define R_SCS_MEM_ERINTEN                                   0x36
#define B_SCS_MEM_ERINTEN_MASK                              0x13FF
#define R_SCS_MEM_NINTSIGNEN                                0x38
#define B_SCS_MEM_NINTSIGNEN_MASK                           0x7FFF
#define R_SCS_MEM_ERINTSIGNEN                               0x3A
#define B_SCS_MEM_ERINTSIGNEN_MASK                          0x13FF
#define R_SCS_MEM_HOST_CTL                                  0x28
#define R_SCS_MEM_HOST_CTL2                                 0x3E
#define B_SCS_MEM_HOST_CTL2_MODE_MASK                       (BIT0 | BIT1 | BIT2)
#define V_SCS_MEM_HOST_CTL2_MODE_HS400                      5
#define V_SCS_MEM_HOST_CTL2_MODE_DDR50                      4
#define V_SCS_MEM_HOST_CTL2_MODE_SDR104                     3
#define V_SCS_MEM_HOST_CTL2_MODE_SDR25                      1
#define R_SCS_MEM_CAP1                                      0x40
#define R_SCS_MEM_CAP2                                      0x44
#define B_SCS_MEM_CAP2_HS400_SUPPORT                        BIT31
#define B_SCS_MEM_CAP2_SDR104_SUPPORT                       BIT1
#define R_SCS_MEM_CESHC2                                    0x3C              ///< Auto CMD12 Error Status Register & Host Control 2
#define B_SCS_MEM_CESHC2_ASYNC_INT                          BIT30             ///< Asynchronous Interrupt Enable
#define R_SCS_MEM_CAP_BYPASS_CONTROL                        0x810
#define V_SCS_MEM_CAP_BYPASS_CONTROL_EN                     0x5A
#define R_SCS_MEM_CAP_BYPASS_REG1                           0x814
#define B_SCS_MEM_CAP_BYPASS_REG1_HS400                     BIT29
#define B_SCS_MEM_CAP_BYPASS_REG1_SLOT_TYPE                 (BIT12 | BIT11)
#define N_SCS_MEM_CAP_BYPASS_REG1_SLOT_TYPE                 11
#define V_SCS_MEM_CAP_BYPASS_REG1_SLOT_TYPE_EMBEDDED        0x1
#define R_SCS_MEM_CAP_BYPASS_REG2                           0x818
#define R_SCS_MEM_TX_CMD_DLL_CNTL                           0x820
#define R_SCS_MEM_TX_DATA_DLL_CNTL1                         0x824
#define R_SCS_MEM_TX_DATA_DLL_CNTL2                         0x828
#define R_SCS_MEM_RX_CMD_DATA_DLL_CNTL1                     0x82C
#define B_SCS_MEM_RX_CMD_DATA_DLL_CNTL1_SDR50               0x00007F00
#define N_SCS_MEM_RX_CMD_DATA_DLL_CNTL1_SDR50               8
#define B_SCS_MEM_RX_CMD_DATA_DLL_CNTL1_DDR50               0x007F0000
#define N_SCS_MEM_RX_CMD_DATA_DLL_CNTL1_DDR50               16
#define R_SCS_MEM_RX_STROBE_DLL_CNTL                        0x830
#define R_SCS_MEM_RX_CMD_DATA_DLL_CNTL2                     0x834
#define R_SCS_MEM_SD_CAP_BYPS                               0x880

#endif


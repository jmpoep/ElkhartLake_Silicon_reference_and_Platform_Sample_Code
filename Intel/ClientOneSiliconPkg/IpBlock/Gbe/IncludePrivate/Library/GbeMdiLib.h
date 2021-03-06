/** @file
  Header file for GbeMdiLib.

  Conventions:

  - Prefixes:
    Definitions beginning with "R_" are registers
    Definitions beginning with "B_" are bits within registers
    Definitions beginning with "V_" are meaningful values within the bits
    Definitions beginning with "S_" are register sizes
    Definitions beginning with "N_" are the bit position
  - In general, PCH registers are denoted by "_PCH_" in register names
  - Registers / bits that are different between PCH generations are denoted by
    "_PCH_[generation_name]_" in register/bit names.
  - Registers / bits that are specific to PCH-H denoted by "_H_" in register/bit names.
    Registers / bits that are specific to PCH-LP denoted by "_LP_" in register/bit names.
    e.g., "_PCH_H_", "_PCH_LP_"
    Registers / bits names without _H_ or _LP_ apply for both H and LP.
  - Registers / bits that are different between SKUs are denoted by "_[SKU_name]"
    at the end of the register/bit names
  - Registers / bits of new devices introduced in a PCH generation will be just named
    as "_PCH_" without [generation_name] inserted.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
#ifndef _GBE_MDI_LIB_H_
#define _GBE_MDI_LIB_H_

//
// Maximum loop time for GbE status check
// 4000 * 50 = 200 mSec in total
//
#define GBE_MAX_LOOP_TIME       4000
#define GBE_ACQUIRE_MDIO_DELAY  50
#define GBE_MDI_SET_PAGE_DELAY  4000 // 4 mSec delay after setting page

//
// LAN PHY MDI settings
//
// MDI Control Register Bits
// 31:30 Reserved
//       This field is reserved and returns 0.
// 29    Interrupt Enable.
//       When this bit is set to 1 by software, it causes the device to assert
//       an interrupt indicating the end of an MDI cycle.
// 28    Ready.
//       Set to 1 by the device at the end of MDI transaction (i.e., indicates a Read or
//       Write has been completed. It should be reset to 0 by software at the same time the
//       command is written.
// 27:26 Opcode
//       For an MDI write, the opcode equals 01b, and for MDI read, 10b. 00b and
//       11b are reserved and should not be used.
// 25:21 PHYAdd
//       PHY Address
// 20:16 RegAdd
//       PHY Register Address
// 15:0  Data

#define B_PHY_MDI_READY                BIT28
#define B_PHY_MDI_READ                 BIT27
#define B_PHY_MDI_WRITE                BIT26
//
//      PHY SPECIFIC registers
//
#define B_PHY_MDI_PHY_ADDRESS_02       BIT22
//
//      PHY GENERAL registers
//      Registers 0 to 15 are defined by the specification
//      Registers 16 to 31 are left available to the vendor
//
#define B_PHY_MDI_PHY_ADDRESS_01       BIT21
#define B_PHY_MDI_PHY_ADDRESS_MASK    (BIT25 | BIT24 | BIT23 | BIT22 | BIT21)
//
//  PHY Identifier Register 1
//  Bits [15:0] - PHY ID Number - The PHY identifier composed of bits 19 through 24 of the OUI.
//
#define R_PHY_MDI_GENEREAL_REGISTER_02_PHY_IDENTIFIER_1  0x00020000
//
//  PHY Identifier Register 2
//  Bits [15:10] - PHY ID Number   - The PHY identifier composed of bits 3 through 18
//                                   of the Organizationally Unique Identifier (OUI)
//  Bits [9:4]   - Device Model Number
//  Bits [3:0]   - Device Revision Number
//
#define R_PHY_MDI_GENEREAL_REGISTER_03_PHY_IDENTIFIER_2  0x00030000

#define MDI_REG_SHIFT(x)                              (x << 16)
#define B_PHY_MDI_PHY_REGISTER_MASK                   (BIT20 | BIT19 | BIT18 | BIT17 | BIT16)
#define R_PHY_MDI_PHY_REG_SET_ADDRESS                 0x00110000 // Used after new page setting
#define R_PHY_MDI_PHY_REG_DATA_READ_WRITE             0x00120000
#define R_PHY_MDI_PHY_REG_SET_PAGE                    0x001F0000

//
// LAN PHY MDI registers and bits
//

//
// Page 769 Port Control Registers
// 6020h (769 * 32)
//
#define PHY_MDI_PAGE_769_PORT_CONTROL_REGISTERS        769
//
// Custom Mode Control PHY Address 01, Page 769, Register 16
//
#define R_PHY_MDI_PAGE_769_REGISETER_16_CMC            0x0010
//
// Custom Mode Control
// Page 769, Register 16, BIT 10
// 0 - normal MDIO frequency access
// 1 - reduced MDIO frequency access (slow mdio)
//     required for read during cable disconnect
//
#define B_PHY_MDI_PAGE_769_REGISETER_16_CMC_MDIO_FREQ_ACCESS        BIT10
//
//  Port General Configuration PHY Address 01, Page 769, Register 17
//
#define R_PHY_MDI_PAGE_769_REGISETER_17_PGC            0x0011
//
// Page 769, Register 17, BIT 4
// Enables host wake up
//
#define B_PHY_MDI_PAGE_769_REGISETER_17_PGC_HOST_WAKE_UP            BIT4
//
// Page 769, Register 17, BIT 2
// Globally enable the MAC power down feature while the
// GbE supports WoL. When set to 1b,
// pages 800 and 801 are enabled for
// configuration and Host_WU_Active is not blocked for writes.
//
#define B_PHY_MDI_PAGE_769_REGISETER_17_PGC_MACPD_ENABLE            BIT2

//
// Page 800 Wake Up Registers
// 6400h (800 * 32)
//
#define PHY_MDI_PAGE_800_WAKE_UP_REGISTERS             800
//
// Wake Up Control - WUC PHY Address 01, Page 800, Register 1
// 1h (Register 1)
//
#define R_PHY_MDI_PAGE_800_REGISETER_1_WUC             0x0001
//
// Wake Up Control - (WUC)
// Page 800, Register 1, BIT 0
// Advance Power Management Enable (APME)
// If set to 1b, APM wake up is enabled.
//
#define B_PHY_MDI_PAGE_800_REGISETER_1_WUC_APME                     BIT0
//
// Receive Address Low - RAL PHY Address 01, Page 800, Register 16
// 10h (Register 16)
//
#define R_PHY_MDI_PAGE_800_REGISETER_16_RAL0           0x0010
//
// Receive Address Low - RAL PHY Address 01, Page 800, Register 17
// 11h (Register 17)
//
#define R_PHY_MDI_PAGE_800_REGISETER_17_RAL1           0x0011
//
// Receive Address High - RAH PHY Address 01, Page 800, Register 18
// 12h (Register 18)
//
#define R_PHY_MDI_PAGE_800_REGISETER_18_RAH0           0x0012
//
// Receive Address High - RAH PHY Address 01, Page 800, Register 19
// 13h (Register 19)
//
#define R_PHY_MDI_PAGE_800_REGISETER_19_RAH1           0x0013
//
// Setting AV (BIT15 RAH is divided on two registers)
// RAH Register 19, Page 800, BIT 31
//
// Address valid (AV)
// When this bit is set, the relevant RAL and RAH are valid
//
#define B_PHY_MDI_PAGE_800_REGISETER_19_RAH1_ADDRESS_VALID          BIT15
//
// Page 803 Host WoL Packet
// 6460h (803 * 32)
//
#define PHY_MDI_PAGE_803_HOST_WOL_PACKET               803
//
// Host WoL Packet Clear - HWPC PHY Address 01, Page 803, Register 66
//
#define R_PHY_MDI_PAGE_803_REGISETER_66_HWPC           0x0042


/**
  Change Extended Device Control Register BIT 11 to 1 which
  forces the interface between the MAC and the Phy to be on SMBus.
  Cleared on the assertion of PCI reset.

  @param [in]  GbeBar   GbE MMIO space

**/
VOID
GbeMdiForceMACtoSMB (
  IN      UINT32  GbeBar
  );

/**
  Test for MDIO operation complete.

  @param [in]  GbeBar   GbE MMIO space

  @retval EFI_SUCCESS
  @retval EFI_TIMEOUT
**/
EFI_STATUS
GbeMdiWaitReady (
  IN      UINT32  GbeBar
  );

/**
  Acquire MDIO software semaphore.

  1. Ensure that MBARA offset F00h [5] = 1b
  2. Poll MBARA offset F00h [5] up to 200ms

  @param [in] GbeBar   GbE MMIO space

  @retval EFI_SUCCESS
  @retval EFI_TIMEOUT
**/
EFI_STATUS
GbeMdiAcquireMdio (
  IN      UINT32  GbeBar
  );

/**
  Release MDIO software semaphore by clearing MBARA offset F00h [5]

  @param [in]  GbeBar   GbE MMIO space
**/
VOID
GbeMdiReleaseMdio (
  IN      UINT32  GbeBar
  );

/**
  Sets page on MDI
  Page setting is attempted twice.
  If first attempt failes MAC and the Phy are force to be on SMBus

  @param [in]  GbeBar  GbE MMIO space
  @param [in]  Data    Value to write in lower 16bits.

  @retval EFI_SUCCESS       Page setting was successfull
  @retval EFI_DEVICE_ERROR  Returned if both attermps of setting page failed
**/
EFI_STATUS
GbeMdiSetPage (
  IN      UINT32  GbeBar,
  IN      UINT32  Page
  );

/**
  Sets Register in current page.

  @param [in]  GbeBar      GbE MMIO space
  @param [in]  register    Register number

  @return EFI_STATUS
**/
EFI_STATUS
GbeMdiSetRegister (
  IN      UINT32  GbeBar,
  IN      UINT32  Register
  );


/**
  Perform MDI read.

  @param [in]  GbeBar       GbE MMIO space
  @param [in]  PhyAddress   Phy Address General - 02 or Specific - 01
  @param [in]  PhyRegister  Phy Register
  @param [out] ReadData     Return Value

  @retval EFI_SUCCESS            Based on response from GbeMdiWaitReady
  @retval EFI_TIMEOUT            Based on response from GbeMdiWaitReady
  @retval EFI_INVALID_PARAMETER  If Phy Address or Register validaton failed
**/
EFI_STATUS
GbeMdiRead (
  IN      UINT32  GbeBar,
  IN      UINT32  PhyAddress,
  IN      UINT32  PhyRegister,
  OUT     UINT16  *ReadData
  );

/**
  Perform MDI write.

  @param [in]  GbeBar       GbE MMIO space
  @param [in]  PhyAddress   Phy Address General - 02 or Specific - 01
  @param [in]  PhyRegister  Phy Register
  @param [in]  WriteData    Value to write in lower 16bits.

  @retval EFI_SUCCESS            Based on response from GbeMdiWaitReady
  @retval EFI_TIMEOUT            Based on response from GbeMdiWaitReady
  @retval EFI_INVALID_PARAMETER  If Phy Address or Register validaton failed
**/
EFI_STATUS
GbeMdiWrite (
  IN      UINT32  GbeBar,
  IN      UINT32  PhyAddress,
  IN      UINT32  PhyRegister,
  IN      UINT32  WriteData
  );

/**
  Gets Phy Revision and Model Number
  from PHY IDENTIFIER register 2 (offset 3)

  @param [in]  GbeBar           GbE MMIO space
  @param [out] LanPhyRevision   Return Value

  @return EFI_STATUS
  @return EFI_INVALID_PARAMETER When GbeBar is incorrect
**/
EFI_STATUS
GbeMdiGetLanPhyRevision (
  IN      UINT32  GbeBar,
  OUT     UINT16  *LanPhyRevision
  );

#endif // _GBE_MDI_LIB_H_

/** @file
  Register names for PCH TSN

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
  Copyright 2018 - 2019 Intel Corporation.

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
#ifndef _TSN_REGS_H_
#define _TSN_REGS_H_

//
// TSN Controller Registers
//
// EHL-PCH D30:F4
#define PCI_DEVICE_NUMBER_PCH_TSN                                    30
#define PCI_FUNCTION_NUMBER_PCH_TSN                                  4

#define V_PCH_TSN_RGMII_1G_CFG_DEVICE_ID                             0x43B0
#define V_PCH_TSN_SGMII_1G_CFG_DEVICE_ID                             0x43B1
#define V_PCH_TSN_SGMII_2_5G_CFG_DEVICE_ID                           0x43B2

// EHL-PSE TSN D29:F1
#define PCI_DEVICE_NUMBER_PSE_TSN0                                   29
#define PCI_FUNCTION_NUMBER_PSE_TSN0                                 1

#define V_PSE_TSN0_RGMII_1G_CFG_DEVICE_ID                            0x4BA0
#define V_PSE_TSN0_SGMII_1G_CFG_DEVICE_ID                            0x4BA1
#define V_PSE_TSN0_SGMII_2_5G_CFG_DEVICE_ID                          0x4BA2

// EHL-PSE TSN D29:F2
#define PCI_DEVICE_NUMBER_PSE_TSN1                                   29
#define PCI_FUNCTION_NUMBER_PSE_TSN1                                 2

#define V_PSE_TSN1_RGMII_1G_CFG_DEVICE_ID                            0x4BB0
#define V_PSE_TSN1_SGMII_1G_CFG_DEVICE_ID                            0x4BB1
#define V_PSE_TSN1_SGMII_2_5G_CFG_DEVICE_ID                          0x4BB2

// TSN PCI Configuration Space Registers
#define R_TSN_CFG_BAR0_LOW                                           0x10
#define B_TSN_CFG_BAR0_MASK                                          0x0FFF
#define V_TSN_CFG_BAR0_SIZE                                          0x2000
#define N_TSN_CFG_BAR0_ALIGNMENT                                     21

// TSN MMIO Space Registers Offset
#define R_TSN_MEM_MAC_MDIO_ADDRESS                 0x200        // MAC MDIO Address
#define R_TSN_MEM_MAC_MDIO_DATA                    0x204        // MAC MDIO Data
#define R_TSN_MEM_MAC_ADDRESS0_HIGH                0x300        // MAC Address 0 High
#define R_TSN_MEM_MAC_ADDRESS0_LOW                 0x304        // MAC Address 0 Low
#define B_TSN_MEM_ADDRESS_ENABLE                   0x80000000
#define R_TSN_MEM_MAC_ADDRESS_HIGH_MASK            0xFFFF

#define B_TSN_MEM_MAC_MDIO_ADDRESS_MASK            B_TSN_MEM_MAC_MDIO_PHYAD | B_TSN_MEM_MAC_MDIO_REGAD  | B_TSN_MEM_MAC_MDIO_CLK_TRAIL | B_TSN_MEM_MAC_MDIO_CLK_CSR | B_TSN_MEM_MAC_MDIO_GMII_GOC_1_0 | B_TSN_MEM_MAC_MDIO_CLAUSE45_PHY // MAC MDIO Mask related for Link Mode speed setup
#define B_TSN_MEM_MAC_MDIO_REGAD                   0x001F0000   // MAC MDIO 5-bit PHY Data Register Address (REGAD)[20:16] for IEEE 802.3 Standard Caluse 22
#define N_TSN_MEM_MAC_MDIO_REGAD                   0x10         // MAC MDIO 5-bit PHY Data Register Address (REGAD)[20:16] for IEEE 802.3 Standard Caluse 22
#define B_TSN_MEM_MAC_MDIO_PHYAD                   0x03E00000   // MAC MDIO 5-bit PHY Address (PHYAD)[25:21] for IEE 802.3 Standard Clause 22
#define N_TSN_MEM_MAC_MDIO_PHYAD                   0x15         // MAC MDIO 5-bit PHY Address (PHYAD)[25:21] for IEE 802.3 Standard Clause 22
#define V_TSN_MEM_MAC_MDIO_ADHOC_GCR_ADD           0x15         // MAC MDIO adhoc Global Configuration REgister (GCR) Address PHYAD 15h at bit [25:21] of  R_TSN_MEM_MAC_MDIO_ADDRESS

#define B_TSN_MEM_MAC_MDIO_CLK_TRAIL               0x7000       // MAC MDIO Number of Trailing CLocks [14:12]
#define N_TSN_MEM_MAC_MDIO_CLK_TRAIL               0xC          // MAC MDIO Number of Trailing CLocks [14:12]
#define V_TSN_MEM_MAC_MDIO_CLK_TRAIL               0x4          // MAC MDIO Number of Trailing CLocks [14:12] set to 4
#define B_TSN_MEM_MAC_MDIO_CLK_CSR                 0xF00        // MAC CSR Clock Range (CR) [11:8]
#define N_TSN_MEM_MAC_MDIO_CLK_CSR                 0x8          // MAC CSR Clock Range (CR) [11:8]
#define V_TSN_MEM_MAC_MDIO_CLK_CSR_DIV_10          0xB          // MAC CSR Clock Range (CR) CSR Clock / 10

#define V_TSN_MEM_MAC_MDIO_GMII_22_PHY_READ        0x0C         // MAC GMII_GOC_1 (Bit3) and GMII_GOC_1 (Bit2) are 1
#define V_TSN_MEM_MAC_MDIO_GMII_22_PHY_WRITE       0x04         // MAC GMII_GOC_1 (Bit3) is 0 and GMII_GOC_1 (Bit2) is 1
#define B_TSN_MEM_MAC_MDIO_GMII_GOC_1_0            BIT3 | BIT2

#define B_TSN_MEM_MAC_MDIO_CLAUSE45_PHY            BIT1         // IEEE 802.3 Clause 45 Phy Enable bit
#define B_TSN_MEM_MAC_MDIO_GMII_BUSY               BIT0         // MAC GMII Busy Bit

#define B_TSN_MEM_MAC_ADHOC_PHY_AUTONEG_DISABLE    BIT0         // MAC PHY Auto-Negotiation Disable bit. Set 1 to Disable auto negotioation. Set 0 Auto.
#define B_TSN_MEM_MAC_ADHOC_LINK_MODE              0x6
#define V_TSN_MEM_MAC_ADHOC_LINK_MODE_2_5G         0x6
#define V_TSN_MEM_MAC_ADHOC_LINK_MODE_1G           0x4

#define R_TSN_MEM_DMA_CTL_CH0                      0x10000      // DMA Control register channel 0
#define R_TSN_MEM_DMA_CTL_CH1                      0x10004      // DMA Control register channel 1
#define R_TSN_MEM_DMA_CTL_CH2                      0x10008      // DMA Control register channel 2
#define R_TSN_MEM_DMA_CTL_CH3                      0x1000C      // DMA Control register channel 3
#define R_TSN_MEM_DMA_CTL_CH4                      0x10010      // DMA Control register channel 4
#define R_TSN_MEM_DMA_CTL_CH5                      0x10014      // DMA Control register channel 5
#define R_TSN_MEM_DMA_CTL_CH6                      0x10018      // DMA Control register channel 6
#define R_TSN_MEM_DMA_CTL_CH7                      0x1001C      // DMA Control register channel 7
#define R_TSN_MEM_DMA_CTL_CH8                      0x10020      // DMA Control register channel 8
#define R_TSN_MEM_DMA_CTL_CH9                      0x10024      // DMA Control register channel 9
#define R_TSN_MEM_DMA_CTL_CH10                     0x10028      // DMA Control register channel 10
#define R_TSN_MEM_DMA_CTL_CH11                     0x1002C      // DMA Control register channel 11
#define R_TSN_MEM_DMA_CTL_CH12                     0x10030      // DMA Control register channel 12
#define R_TSN_MEM_DMA_CTL_CH13                     0x10034      // DMA Control register channel 13
#define R_TSN_MEM_DMA_CTL_CH14                     0x10038      // DMA Control register channel 14
#define R_TSN_MEM_DMA_CTL_CH15                     0x1003C      // DMA Control register channel 15
#define B_TSN_MEM_DMA_CTL_CH_VC_MAP                0x00000C00   // Bit[11]: Vc0/1 Wr, Bit[10]: Vc0/1 Rd
#define N_TSN_MEM_IOSF_WR_VC01                     11           // Bit[11] of DMA Control register
#define N_TSN_MEM_IOSF_RD_VC01                     10           // Bit[10] of DMA Control register

// TSN Side Band AXI/TC mapping registers
#define R_TSN_PCR_AXIID_TO_TC0_MAP_0                                 0x400
#define B_TSN_PCR_AXIID_TO_TC0_MAP_0                                 0x0000FFFF
#define R_TSN_PCR_AXIID_TO_TC1_MAP_0                                 0x410
#define B_TSN_PCR_AXIID_TO_TC1_MAP_0                                 0x0000FFFF

// TSN Side Band MSI/TC mapping registers
#define R_TSN_PCR_MSI_TO_TC0_MAP                                     0x500
#define B_TSN_PCR_MSI_TO_TC0_MAP                                     0xFC00FFFF
#define R_TSN_PCR_MSI_TO_TC1_MAP                                     0x504
#define B_TSN_PCR_MSI_TO_TC1_MAP                                     0xFC00FFFF

#define R_TSN_PCR_PMCTL                                              0x1D0
#define B_TSN_PCR_PMCTL_CLOCKGATE                                    0x3F

//
// TSN Iosf2Ocp bridge configuration registers
//
#define R_TSN_PCR_PCICFGCTRL                                         0x200                         ///< PCI Configuration Control
#define B_TSN_PCR_PCICFGCTR_PCI_IRQ                                  0x0FF00000                    ///< PCI IRQ number
#define N_TSN_PCR_PCICFGCTR_PCI_IRQ                                  20
#define B_TSN_PCR_PCICFGCTR_ACPI_IRQ                                 0x000FF000                    ///< ACPI IRQ number
#define N_TSN_PCR_PCICFGCTR_ACPI_IRQ                                 12
#define B_TSN_PCR_PCICFGCTR_IPIN1                                    (BIT11 | BIT10 | BIT9 | BIT8) ///< Interrupt Pin
#define N_TSN_PCR_PCICFGCTR_IPIN1                                    8

//
//  TSN Link Speed PLL Registers
//

#define R_MODPHY_PCR_CMN_DIG_DWORD2                                 0x8008
#define B_MODPHY_PCR_CMN_DIG_DWORD2                                 0x00000003
#define N_MODPHY_PCR_CMN_DIG_DWORD2_COMMON                          0x00000000

#define R_MODPHY_PCR_CMN_DIG_DWORD12                                0x8030
#define B_MODPHY_PCR_CMN_DIG_DWORD12                                0x00000001
#define N_MODPHY_PCR_CMN_DIG_DWORD12_COMMON                         0x00000001

#define R_MODPHY_PCR_CMN_DIG_DWORD15                                0x803C
#define B_MODPHY_PCR_CMN_DIG_DWORD15                                0x00000006
#define N_MODPHY_PCR_CMN_DIG_DWORD15_COMMON                         0x00000006

#define R_MODPHY_PCR_CMN_ANA_DWORD10                                0x80E8
#define B_MODPHY_PCR_CMN_ANA_DWORD10                                0x00FF0000
#define N_MODPHY_PCR_CMN_ANA_DWORD10_COMMON                         0x00010000

#define R_MODPHY_PCR_CMN_ANA_DWORD30                                0x8138
#define B_MODPHY_PCR_CMN_ANA_DWORD30                                0xFF007800
#define N_MODPHY_PCR_CMN_ANA_DWORD30_CLK24MHZ_2_5G                  0x82002800
#define N_MODPHY_PCR_CMN_ANA_DWORD30_CLK24MHZ_1G                    0x82005000
#define N_MODPHY_PCR_CMN_ANA_DWORD30_CLK38_4MHZ_2_5G                0x82002800
#define N_MODPHY_PCR_CMN_ANA_DWORD30_CLK38_4MHZ_1G                  0x00005000

#define R_MODPHY_PCR_LCPLL_DWORD0                                   0x8180
#define B_MODPHY_PCR_LCPLL_DWORD0                                   0x7FFFFFFF
#define B_MODPHY_PCR_LCPLL_DWORD0_CLK24MHZ_2_5G                     0x4D555582
#define B_MODPHY_PCR_LCPLL_DWORD0_CLK24MHZ_1G                       0x4AAAAA68
#define B_MODPHY_PCR_LCPLL_DWORD0_CLK38_4MHZ_2_5G                   0x58555551
#define B_MODPHY_PCR_LCPLL_DWORD0_CLK38_4MHZ_1G                     0x46AAAA41

#define R_MODPHY_PCR_LCPLL_DWORD2                                   0x8188
#define B_MODPHY_PCR_LCPLL_DWORD2                                   0x003F05FF
#define N_MODPHY_PCR_LCPLL_DWORD2_CLK24MHZ_2_5G                     0x0000012D
#define N_MODPHY_PCR_LCPLL_DWORD2_CLK24MHZ_1G                       0x00000139
#define N_MODPHY_PCR_LCPLL_DWORD2_CLK38_4MHZ_2_5G                   0x0000012D
#define N_MODPHY_PCR_LCPLL_DWORD2_CLK38_4MHZ_1G                     0x00000139

#define R_MODPHY_PCR_LCPLL_DWORD4                                   0x8190
#define B_MODPHY_PCR_LCPLL_DWORD4                                   0x07071F0F
#define N_MODPHY_PCR_LCPLL_DWORD4_COMMON                            0x02010804
//#define R_MODPHY_PCR_LCPLL_DWORD4_CLK24MHZ_2_5G                     0x02010804
//#define R_MODPHY_PCR_LCPLL_DWORD4_CLK24MHZ_1G                       0x02010804
//#define R_MODPHY_PCR_LCPLL_DWORD4_CLK38_4MHZ_2_5G                   0x02010804
//#define R_MODPHY_PCR_LCPLL_DWORD4_CLK38_4MHZ_1G                     0x02010804

#define R_MODPHY_PCR_LCPLL_DWORD6                                   0x8198
#define B_MODPHY_PCR_LCPLL_DWORD6                                   0x00020000
#define N_MODPHY_PCR_LCPLL_DWORD6_COMMON                            0x00020000
//#define R_MODPHY_PCR_LCPLL_DWORD6_CLK24MHZ_2_5G                     0x00020000
//#define R_MODPHY_PCR_LCPLL_DWORD6_CLK24MHZ_1G                       0x00020000
//#define R_MODPHY_PCR_LCPLL_DWORD6_CLK38_4MHZ_2_5G                   0x00020000
//#define R_MODPHY_PCR_LCPLL_DWORD6_CLK38_4MHZ_1G                     0x00020000

#define R_MODPHY_PCR_LCPLL_DWORD7                                   0x819C
#define B_MODPHY_PCR_LCPLL_DWORD7                                   0x003F0003
#define N_MODPHY_PCR_LCPLL_DWORD7_CLK24MHZ_2_5G                     0x001F0003
#define N_MODPHY_PCR_LCPLL_DWORD7_CLK24MHZ_1G                       0x002A0003
#define N_MODPHY_PCR_LCPLL_DWORD7_CLK38_4MHZ_2_5G                   0x001F0003
#define N_MODPHY_PCR_LCPLL_DWORD7_CLK38_4MHZ_1G                     0x002A0003

#define R_MODPHY_PCR_LCPLL_DWORD8                                   0x81A0
#define B_MODPHY_PCR_LCPLL_DWORD8                                   0x00FF0307
#define N_MODPHY_PCR_LCPLL_DWORD8_COMMON                            0x00000000
//#define R_MODPHY_PCR_LCPLL_DWORD8_CLK24MHZ_2_5G                     0x00000000
//#define R_MODPHY_PCR_LCPLL_DWORD8_CLK24MHZ_1G                       0x00000000
//#define R_MODPHY_PCR_LCPLL_DWORD8_CLK38_4MHZ_2_5G                   0x00000000
//#define R_MODPHY_PCR_LCPLL_DWORD8_CLK38_4MHZ_1G                     0x00000000

#define R_MODPHY_PCR_LPPLL_DWORD10                                  0x81A8
#define B_MODPHY_PCR_LPPLL_DWORD10                                  0x003800FF
#define N_MODPHY_PCR_LPPLL_DWORD10_CLK24MHZ_2_5G                    0x0008000E
#define N_MODPHY_PCR_LPPLL_DWORD10_CLK24MHZ_1G                      0x0008000E
#define N_MODPHY_PCR_LPPLL_DWORD10_CLK38_4MHZ_2_5G                  0x00100008
#define N_MODPHY_PCR_LPPLL_DWORD10_CLK38_4MHZ_1G                    0x00100008

#define R_MODPHY_PCR_LCPLL_DWORD11                                  0x81AC
#define B_MODPHY_PCR_LCPLL_DWORD11                                  0x00000201
#define N_MODPHY_PCR_LCPLL_DWORD11_COMMON                           0x00000200

#define R_MODPHY_PCR_LCPLL_DWORD12                                  0x81B0
#define B_MODPHY_PCR_LCPLL_DWORD12                                  0x08003C00
#define N_MODPHY_PCR_LCPLL_DWORD12_COMMON                           0x08003C00

#define R_MODPHY_PCR_LCPLL_DWORD18                                  0x81C8
#define B_MODPHY_PCR_LCPLL_DWORD18                                  0x000000FF
#define N_MODPHY_PCR_LCPLL_DWORD18_COMMON                           0x00000001

#define R_MODPHY_PCR_LCPLL_DWORD19                                  0x81CC
#define B_MODPHY_PCR_LCPLL_DWORD19                                  0x00FF00FF
#define N_MODPHY_PCR_LCPLL_DWORD19_COMMON                           0x00010001

#define R_MODPHY_PCR_CMN_DIG_DWORD1                                  0x7FD2
#define B_MODPHY_PCR_CMN_DIG_DWORD1                                  0x00000020
#define N_MODPHY_PCR_CMN_DIG_DWORD1_COMMON                           0x00000000

#define R_MODPHY_DLANE7_PCR_SET3                                    0xC04
#define R_MODPHY_DLANE8_PCR_SET3                                    0x4
#define R_MODPHY_DLANE9_PCR_SET3                                    0x404
#define R_MODPHY_DLANE10_PCR_SET3                                   0x804
#define R_MODPHY_DLANE11_PCR_SET3                                   0xC04
#define B_MODPHY_PCR_SET3                                           0x00200300
#define N_MODPHY_PCR_COMMON                                         0x00200300

#define R_MODPHY_DLANE7_PCR_2TAP_DEEMPH3P5_RATE1                    0xD54
#define R_MODPHY_DLANE8_PCR_2TAP_DEEMPH3P5_RATE1                    0x154
#define R_MODPHY_DLANE9_PCR_2TAP_DEEMPH3P5_RATE1                    0x554
#define R_MODPHY_DLANE10_PCR_2TAP_DEEMPH3P5_RATE1                   0x954
#define R_MODPHY_DLANE11_PCR_2TAP_DEEMPH3P5_RATE1                   0xD54
#define B_MODPHY_PCR_2TAP_DEEMPH3P5_RATE1                           0x003f0004
#define N_MODPHY_PCR_2TAP_DEEMPH3P5_RATE1_COMMON                    0x002d0000

#define R_MODPHY_DLANE7_PCR_2TAP_DEEMPH3P5_RATE0                    0xD58
#define R_MODPHY_DLANE8_PCR_2TAP_DEEMPH3P5_RATE0                    0x158
#define R_MODPHY_DLANE9_PCR_2TAP_DEEMPH3P5_RATE0                    0x558
#define R_MODPHY_DLANE10_PCR_2TAP_DEEMPH3P5_RATE0                   0x958
#define R_MODPHY_DLANE11_PCR_2TAP_DEEMPH3P5_RATE0                   0xD58
#define B_MODPHY_PCR_2TAP_DEEMPH3P5_RATE0                           0x00003F00
#define N_MODPHY_PCR_2TAP_DEEMPH3P5_RATE0_COMMON                    0x00002800

#define R_MODPHY_DLANE7_PCR_TX_DWORD18                              0xD88
#define R_MODPHY_DLANE8_PCR_TX_DWORD18                              0x188
#define R_MODPHY_DLANE9_PCR_TX_DWORD18                              0x588
#define R_MODPHY_DLANE10_PCR_TX_DWORD18                             0x988
#define R_MODPHY_DLANE11_PCR_TX_DWORD18                             0xD88
#define B_MODPHY_PCR_TX_DWORD18                                     0x00FC0F00
#define N_MODPHY_PCR_TX_DWORD18_COMMON                              0x00400800

#define R_MODPHY_DLANE7_PCR_TX_DWORD19                              0xD8C
#define R_MODPHY_DLANE8_PCR_TX_DWORD19                              0x18C
#define R_MODPHY_DLANE9_PCR_TX_DWORD19                              0x58C
#define R_MODPHY_DLANE10_PCR_TX_DWORD19                             0x98C
#define R_MODPHY_DLANE11_PCR_TX_DWORD19                             0xD8C
#define B_MODPHY_PCR_TX_DWORD19                                     0x00000020
#define N_MODPHY_PCR_TX_DWORD19_COMMON                              0x00000020

#define R_MODPHY_DLANE7_PCR_RXPICTRL1                               0xE00
#define R_MODPHY_DLANE8_PCR_RXPICTRL1                               0x200
#define R_MODPHY_DLANE9_PCR_RXPICTRL1                               0x600
#define R_MODPHY_DLANE10_PCR_RXPICTRL1                              0xA00
#define R_MODPHY_DLANE11_PCR_RXPICTRL1                              0xE00
#define B_MODPHY_PCR_RXPICTRL1                                      0x0000FC00
#define N_MODPHY_PCR_RXPICTRL1_COMMON                               0x00002800

#define R_MODPHY_DLANE7_PCR_RSVD4                                   0xE04
#define R_MODPHY_DLANE8_PCR_RSVD4                                   0x204
#define R_MODPHY_DLANE9_PCR_RSVD4                                   0x604
#define R_MODPHY_DLANE10_PCR_RSVD4                                  0xA04
#define R_MODPHY_DLANE11_PCR_RSVD4                                  0xE04
#define B_MODPHY_PCR_RSVD4                                          0x00003F80
#define N_MODPHY_PCR_RSVD4_COMMON                                   0x00000000

#define R_MODPHY_DLANE7_PCR_RSVD9                                   0xE08
#define R_MODPHY_DLANE8_PCR_RSVD9                                   0x208
#define R_MODPHY_DLANE9_PCR_RSVD9                                   0x608
#define R_MODPHY_DLANE10_PCR_RSVD9                                  0xA08
#define R_MODPHY_DLANE11_PCR_RSVD9                                  0xE08
#define B_MODPHY_PCR_RSVD9                                          0xFF000010
#define N_MODPHY_PCR_RSVD9_COMMON                                   0x21000010

#define R_MODPHY_DLANE7_PCR_RX_DWORD5                               0xE14
#define R_MODPHY_DLANE8_PCR_RX_DWORD5                               0x214
#define R_MODPHY_DLANE9_PCR_RX_DWORD5                               0x614
#define R_MODPHY_DLANE10_PCR_RX_DWORD5                              0xA14
#define R_MODPHY_DLANE11_PCR_RX_DWORD5                              0xE14
#define B_MODPHY_PCR_RX_DWORD5                                      0x00000700
#define N_MODPHY_PCR_RX_DWORD5_COMMON                               0x00000100

#define R_MODPHY_DLANE7_PCR_RSVD19                                  0xE18
#define R_MODPHY_DLANE8_PCR_RSVD19                                  0x218
#define R_MODPHY_DLANE9_PCR_RSVD19                                  0x618
#define R_MODPHY_DLANE10_PCR_RSVD19                                 0xA18
#define R_MODPHY_DLANE11_PCR_RSVD19                                 0xE18
#define B_MODPHY_PCR_RSVD19                                         0x00004000
#define N_MODPHY_PCR_RSVD19_COMMON                                  0x00000000

#define R_MODPHY_DLANE7_PCR_REG1C                                   0xE1C
#define R_MODPHY_DLANE8_PCR_REG1C                                   0x21C
#define R_MODPHY_DLANE9_PCR_REG1C                                   0x61C
#define R_MODPHY_DLANE10_PCR_REG1C                                  0xA1C
#define R_MODPHY_DLANE11_PCR_REG1C                                  0xE1C
#define B_MODPHY_PCR_REG1C                                          0x000000F0
#define N_MODPHY_PCR_REG1C_COMMON                                   0x00000050

#define R_MODPHY_DLANE7_PCR_REG21                                   0xE20
#define R_MODPHY_DLANE8_PCR_REG21                                   0x220
#define R_MODPHY_DLANE9_PCR_REG21                                   0x620
#define R_MODPHY_DLANE10_PCR_REG21                                  0xA20
#define R_MODPHY_DLANE11_PCR_REG21                                  0xE20
#define B_MODPHY_PCR_REG21                                          0x00000800
#define N_MODPHY_PCR_REG21_COMMON                                   0x00000800

#define R_MODPHY_DLANE7_PCR_RXUPIFCFGGHALFRATE_0                    0xE44
#define R_MODPHY_DLANE8_PCR_RXUPIFCFGGHALFRATE_0                    0x244
#define R_MODPHY_DLANE9_PCR_RXUPIFCFGGHALFRATE_0                    0x644
#define R_MODPHY_DLANE10_PCR_RXUPIFCFGGHALFRATE_0                   0xA44
#define R_MODPHY_DLANE11_PCR_RXUPIFCFGGHALFRATE_0                   0xE44
#define B_MODPHY_PCR_RXUPIFCFGGHALFRATE_0                           0x00FFFFFF
#define N_MODPHY_PCR_RXUPIFCFGGHALFRATE_0_COMMON                    0x00001548

#define R_MODPHY_DLANE7_PCR_RXUPPFCFGGQUARTERRATE_0                 0xE48
#define R_MODPHY_DLANE8_PCR_RXUPPFCFGGQUARTERRATE_0                 0x248
#define R_MODPHY_DLANE9_PCR_RXUPPFCFGGQUARTERRATE_0                 0x648
#define R_MODPHY_DLANE10_PCR_RXUPPFCFGGQUARTERRATE_0                0xA48
#define R_MODPHY_DLANE11_PCR_RXUPPFCFGGQUARTERRATE_0                0xE48
#define B_MODPHY_PCR_RXUPPFCFGGQUARTERRATE_0                        0x00FFFFFF
#define N_MODPHY_PCR_RXUPPFCFGGQUARTERRATE_0_COMMON                 0x0000194C

#define R_MODPHY_DLANE7_PCR_RX_DWORD20                              0xE50
#define R_MODPHY_DLANE8_PCR_RX_DWORD20                              0x250
#define R_MODPHY_DLANE9_PCR_RX_DWORD20                              0x650
#define R_MODPHY_DLANE10_PCR_RX_DWORD20                             0xA50
#define R_MODPHY_DLANE11_PCR_RX_DWORD20                             0xE50
#define B_MODPHY_PCR_RX_DWORD20                                     0x3F000000
#define N_MODPHY_PCR_RX_DWORD20_COMMON                              0x03000000

#define R_MODPHY_DLANE7_PCR_REG54                                   0xE54
#define R_MODPHY_DLANE8_PCR_REG54                                   0x254
#define R_MODPHY_DLANE9_PCR_REG54                                   0x654
#define R_MODPHY_DLANE10_PCR_REG54                                  0xA54
#define R_MODPHY_DLANE11_PCR_REG54                                  0xE54
#define B_MODPHY_PCR_REG54                                          0xC0003F3F
#define N_MODPHY_PCR_REG54_COMMON                                   0x00000102

#define R_MODPHY_DLANE7_PCR_RSVD5E                                  0xE5C
#define R_MODPHY_DLANE8_PCR_RSVD5E                                  0x25C
#define R_MODPHY_DLANE9_PCR_RSVD5E                                  0x65C
#define R_MODPHY_DLANE10_PCR_RSVD5E                                 0xA5C
#define R_MODPHY_DLANE11_PCR_RSVD5E                                 0xE5C
#define B_MODPHY_PCR_RSVD5E                                         0x00FF0000
#define N_MODPHY_PCR_RSVD5E_COMMON                                  0x00300000

#define R_MODPHY_DLANE7_PCR_RSVD75                                  0xE74
#define R_MODPHY_DLANE8_PCR_RSVD75                                  0x274
#define R_MODPHY_DLANE9_PCR_RSVD75                                  0x674
#define R_MODPHY_DLANE10_PCR_RSVD75                                 0xA74
#define R_MODPHY_DLANE11_PCR_RSVD75                                 0xE74
#define B_MODPHY_PCR_RSVD75                                         0x80007F00
#define N_MODPHY_PCR_RSVD75_COMMON                                  0x00007F00

#define R_MODPHY_DLANE7_PCR_REG7A                                   0xE78
#define R_MODPHY_DLANE8_PCR_REG7A                                   0x278
#define R_MODPHY_DLANE9_PCR_REG7A                                   0x678
#define R_MODPHY_DLANE10_PCR_REG7A                                  0xA78
#define R_MODPHY_DLANE11_PCR_REG7A                                  0xE78
#define B_MODPHY_PCR_REG7A                                          0x00030000
#define N_MODPHY_PCR_REG7A_COMMON                                   0x00030000

#define R_MODPHY_DLANE7_PCR_RSVD8B                                  0xE88
#define R_MODPHY_DLANE8_PCR_RSVD8B                                  0x288
#define R_MODPHY_DLANE9_PCR_RSVD8B                                  0x688
#define R_MODPHY_DLANE10_PCR_RSVD8B                                 0xA88
#define R_MODPHY_DLANE11_PCR_RSVD8B                                 0xE88
#define B_MODPHY_PCR_RSVD8B                                         0xC0000000
#define N_MODPHY_PCR_RSVD8B_COMMON                                  0x40000000

#define R_MODPHY_DLANE7_PCR_RSVD8D                                  0xE8C
#define R_MODPHY_DLANE8_PCR_RSVD8D                                  0x28C
#define R_MODPHY_DLANE9_PCR_RSVD8D                                  0x68C
#define R_MODPHY_DLANE10_PCR_RSVD8D                                 0xA8C
#define R_MODPHY_DLANE11_PCR_RSVD8D                                 0xE8C
#define B_MODPHY_PCR_RSVD8D                                         0x00F0FF00
#define N_MODPHY_PCR_RSVD8D_COMMON                                  0x00004000

#define R_MODPHY_DLANE7_PCR_RSVDEB                                  0xEE8
#define R_MODPHY_DLANE8_PCR_RSVDEB                                  0x2E8
#define R_MODPHY_DLANE9_PCR_RSVDEB                                  0x6E8
#define R_MODPHY_DLANE10_PCR_RSVDEB                                 0xAE8
#define R_MODPHY_DLANE11_PCR_RSVDEB                                 0xEE8
#define B_MODPHY_PCR_RSVDEB                                         0xFF000000
#define N_MODPHY_PCR_RSVDEB_COMMON                                  0x2C000000

#define R_MODPHY_DLANE7_PCR_RSVD80                                  0xC00
#define R_MODPHY_DLANE8_PCR_RSVD80                                  0x000
#define R_MODPHY_DLANE9_PCR_RSVD80                                  0x400
#define R_MODPHY_DLANE10_PCR_RSVD80                                 0x800
#define R_MODPHY_DLANE11_PCR_RSVD80                                 0xC00
#define B_MODPHY_PCR_RSVD80                                         0x403F0000
#define N_MODPHY_PCR_RSVD80_COMMON                                  0x400A0000

#define R_MODPHY_DLANE7_PCR_RSVDAB                                  0xEB4
#define R_MODPHY_DLANE8_PCR_RSVDAB                                  0x2B4
#define R_MODPHY_DLANE9_PCR_RSVDAB                                  0x6B4
#define R_MODPHY_DLANE10_PCR_RSVDAB                                 0xAB4
#define R_MODPHY_DLANE11_PCR_RSVDAB                                 0xEB4
#define B_MODPHY_PCR_RSVDAB                                         0x0F000000
#define N_MODPHY_PCR_RSVDAB_COMMON                                  0x0C000000

#define R_MODPHY_DLANE7_PCR_RX_DWORD51                              0xECC
#define R_MODPHY_DLANE8_PCR_RX_DWORD51                              0x2CC
#define R_MODPHY_DLANE9_PCR_RX_DWORD51                              0x6CC
#define R_MODPHY_DLANE10_PCR_RX_DWORD51                             0xACC
#define R_MODPHY_DLANE11_PCR_RX_DWORD51                             0xECC
#define B_MODPHY_PCR_RX_DWORD51                                     0x0000003F
#define N_MODPHY_PCR_RX_DWORD51_COMMON                              0x00000021

#define R_MODPHY_DLANE7_PCR_RX_DWORD61                              0xEF4
#define R_MODPHY_DLANE8_PCR_RX_DWORD61                              0x2F4
#define R_MODPHY_DLANE9_PCR_RX_DWORD61                              0x6F4
#define R_MODPHY_DLANE10_PCR_RX_DWORD61                             0xAF4
#define R_MODPHY_DLANE11_PCR_RX_DWORD61                             0xEF4
#define B_MODPHY_PCR_RX_DWORD61                                     0x0000FF00
#define N_MODPHY_PCR_RX_DWORD61_COMMON                              0x00001400

#define R_MODPHY_DLANE7_PCR_PCS_DWORD14                              0xC38
#define R_MODPHY_DLANE8_PCR_PCS_DWORD14                              0x38
#define R_MODPHY_DLANE9_PCR_PCS_DWORD14                              0x438
#define R_MODPHY_DLANE10_PCR_PCS_DWORD14                             0x838
#define R_MODPHY_DLANE11_PCR_PCS_DWORD14                             0xC38
#define B_MODPHY_PCR_PCS_DWORD14                                     0x0000007F
#define N_MODPHY_PCR_PCS_DWORD14_COMMON                              0x00000016

#define R_MODPHY_DLANE7_PCR_PCS_DWORD15                             0xC3C
#define R_MODPHY_DLANE8_PCR_PCS_DWORD15                             0x03C
#define R_MODPHY_DLANE9_PCR_PCS_DWORD15                             0x43C
#define R_MODPHY_DLANE10_PCR_PCS_DWORD15                            0x83C
#define R_MODPHY_DLANE11_PCR_PCS_DWORD15                            0xC3C
#define B_MODPHY_PCR_PCS_DWORD15                                    0x0000F000
#define N_MODPHY_PCR_PCS_DWORD15_COMMON                             0x00009000
#endif

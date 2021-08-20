/** @file
  Register names for USB Host and device controller

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
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _USB_REGS_H_
#define _USB_REGS_H_

//
// USB3 (XHCI) related definitions
// @todo: Add CPU PCI defs for xHCI
//
#define PCI_BUS_NUMBER_PCH_XHCI             0
#define PCI_DEVICE_NUMBER_PCH_XHCI          20
#define PCI_FUNCTION_NUMBER_PCH_XHCI        0

//
// XHCI PCI Config Space registers
//
#define R_XHCI_CFG_BAR0                     PCI_BASE_ADDRESSREG_OFFSET
#define B_XHCI_CFG_ALIGN_MASK               0xFFFF

#define R_XHCI_CFG_XHCC1                    0x40
#define B_XHCI_CFG_XHCC1_ACCTRL             BIT31
#define B_XHCI_CFG_XHCC1_URD                BIT23
#define R_XHCI_CFG_XHCC2                    0x44
#define B_XHCI_CFG_XHCC2_UNPPA              0x7F  ///< Upstream Non-Posted Pre-Allocation mask
#define N_XHCI_CFG_XHCC2_UNPPA              14    ///< Upstream Non-Posted Pre-Allocation bit position
#define B_XHCI_CFG_XHCC2_OCCFDONE           BIT31
#define R_XHCI_CFG_XHCLKGTEN                0x50
#define R_XHCI_CFG_PWR_CNTL_STS             0x74
#define B_XHCI_CFG_PWR_CNTL_STS_PWR_STS     (BIT1 | BIT0)
#define V_XHCI_CFG_PWR_CNTL_STS_PWR_STS_D3  (BIT1 | BIT0)
#define R_XHCI_CFG_MSI_NEXT                 0x81
#define R_XHCI_CFG_MSI_MCTL                 0x82
#define R_XHCI_CFG_PCE                      0xA2
#define B_XHCI_CFG_PCE_D3HE                 BIT2
#define R_XHCI_CFG_HSCFG2                   0xA4
#define R_XHCI_CFG_SSCFG1                   0xA8
#define R_XHCI_CFG_HSCFG1                   0xAC
#define R_XHCI_CFG_U2OCM                    0xB0
#define R_XHCI_CFG_U3OCM                    0xD0

#define R_XHCI_CFG_FUS                      0xE0
#define B_XHCI_CFG_FUS_USBR                 (BIT5)
#define V_XHCI_CFG_FUS_USBR_EN              0
#define V_XHCI_CFG_FUS_USBR_DIS             (BIT5)
#define R_XHCI_CFG_XHCC3                    0xFC  ///< XHCI System Bus Configuration 3

//
// xHCI MMIO registers
//

//
// 0x00 - 0x1F - Capability Registers
//
#define R_XHCI_MEM_CAPLENGTH                0x00
#define R_XHCI_MEM_HCIVERSION               0x02
#define B_XHCI_MEM_HCIVERSION               0xFFFF
#define V_XHCI_MEM_HCIVERSION               0x0110
#define N_XHCI_MEM_HCIVERSION               16
#define R_XHCI_MEM_HCSPARAMS1               0x04
#define R_XHCI_MEM_HCSPARAMS2               0x08
#define R_XHCI_MEM_HCSPARAMS3               0x0C
#define B_XHCI_MEM_HCSPARAMS3               0x0000FF00
#define B_XHCI_MEM_HCSPARAMS3_U2DEL         0xFFFF0000
#define N_XHCI_MEM_HCSPARAMS3_U2DEL         16
#define B_XHCI_MEM_HCSPARAMS3_U1DEL         0x000000FF
#define R_XHCI_MEM_HCCPARAMS1               0x10
#define R_XHCI_MEM_HCCPARAMS2               0x1C
#define B_XHCI_MEM_HCCPARAMS2_CTC           BIT3
#define R_XHCI_MEM_DBOFF                    0x14
#define R_XHCI_MEM_RTSOFF                   0x18

//
// 0x80 - 0xBF - Operational Registers
//
#define R_XHCI_MEM_USBCMD                   0x80   ///< USB Command
#define B_XHCI_MEM_USBCMD_RS                BIT0   ///< Run/Stop
#define B_XHCI_MEM_USBCMD_RST               BIT1   ///< Host Controller Reset
#define R_XHCI_MEM_USBSTS                   0x84   ///< USB Status
#define B_XHCI_MEM_USBSTS_HCH               BIT0   ///< Host Controller Halted
#define B_XHCI_MEM_USBSTS_CNR               BIT11

#define R_XHCI_MEM_PORTSC_START_OFFSET      0x480  ///< Port Status and Control Registers base offset
#define S_XHCI_MEM_PORTSC_PORT_SPACING      0x10   ///< Size of space between PortSC register for each port

#define B_XHCI_MEM_PORTSCXUSB2_WPR              BIT31  ///< Warm Port Reset
#define B_XHCI_MEM_PORTSCXUSB2_CEC              BIT23  ///< Port Config Error Change
#define B_XHCI_MEM_PORTSCXUSB2_PLC              BIT22  ///< Port Link State Change
#define B_XHCI_MEM_PORTSCXUSB2_PRC              BIT21  ///< Port Reset Change
#define B_XHCI_MEM_PORTSCXUSB2_OCC              BIT20  ///< Over-current Change
#define B_XHCI_MEM_PORTSCXUSB2_WRC              BIT19  ///< Warm Port Reset Change
#define B_XHCI_MEM_PORTSCXUSB2_PEC              BIT18  ///< Port Enabled Disabled Change
#define B_XHCI_MEM_PORTSCXUSB2_CSC              BIT17  ///< Connect Status Change
#define B_XHCI_MEM_PORTSCXUSB2_LWS              BIT16  ///< Port Link State Write Strobe
#define B_XHCI_MEM_PORTSCXUSB2_PP               BIT9
#define B_XHCI_MEM_PORTSCXUSB2_PLS              (BIT5 | BIT6 | BIT7 | BIT8)  ///< Port Link State
#define B_XHCI_MEM_PORTSCXUSB2_PR               BIT4   ///< Port Reset
#define B_XHCI_MEM_PORTSCXUSB2_PED              BIT1   ///< Port Enable/Disabled
#define B_XHCI_MEM_PORTSCXUSB2_CCS              BIT0   ///< Current Connect Status
#define B_XHCI_MEM_PORT_CHANGE_ENABLE           (B_XHCI_MEM_PORTSCXUSB2_CEC | B_XHCI_MEM_PORTSCXUSB2_PLC | B_XHCI_MEM_PORTSCXUSB2_PRC | B_XHCI_MEM_PORTSCXUSB2_OCC | B_XHCI_MEM_PORTSCXUSB2_WRC | B_XHCI_MEM_PORTSCXUSB2_PEC | B_XHCI_MEM_PORTSCXUSB2_CSC | B_XHCI_MEM_PORTSCXUSB2_PED)
#define B_XHCI_MEM_PORTPMSCXUSB2_PTC            (BIT28 | BIT29 | BIT30 | BIT31)  ///< Port Test Control

#define B_XHCI_MEM_PORTSCXUSB3_WPR              BIT31  ///< Warm Port Reset
#define B_XHCI_MEM_PORTSCXUSB3_CEC              BIT23  ///< Port Config Error Change
#define B_XHCI_MEM_PORTSCXUSB3_PLC              BIT22  ///< Port Link State Change
#define B_XHCI_MEM_PORTSCXUSB3_PRC              BIT21  ///< Port Reset Change
#define B_XHCI_MEM_PORTSCXUSB3_OCC              BIT20  ///< Over-current Change
#define B_XHCI_MEM_PORTSCXUSB3_WRC              BIT19  ///< Warm Port Reset Change
#define B_XHCI_MEM_PORTSCXUSB3_PEC              BIT18  ///< Port Enabled Disabled Change
#define B_XHCI_MEM_PORTSCXUSB3_CSC              BIT17  ///< Connect Status Change
#define B_XHCI_MEM_PORTSCXUSB3_LWS              BIT16  ///< Port Link State Write Strobe
#define B_XHCI_MEM_PORTSCXUSB3_PP               BIT9   ///< Port Power
#define B_XHCI_MEM_PORTSCXUSB3_PLS              (BIT8 | BIT7 | BIT6 | BIT5)    ///< Port Link State
#define V_XHCI_MEM_PORTSCXUSB3_PLS_POLLING      0x000000E0    ///< Link is in the Polling State
#define V_XHCI_MEM_PORTSCXUSB3_PLS_RXDETECT     0x000000A0    ///< Link is in the RxDetect State
#define V_XHCI_MEM_PORTSCXUSB3_PLS_DISABLED     0x00000080    ///< Link is in the Disabled State
#define V_XHCI_MEM_PORTSCXUSB3_PLS_COMPLIANCE   0x00000140    ///< Link is in the Compliance Mode State
#define B_XHCI_MEM_PORTSCXUSB3_PR               BIT4   ///< Port Reset
#define B_XHCI_MEM_PORTSCXUSB3_PED              BIT1   ///< Port Enable/Disabled
#define B_XHCI_MEM_PORTSCXUSB3_CHANGE_ENABLE    (B_XHCI_MEM_PORTSCXUSB3_CEC | B_XHCI_MEM_PORTSCXUSB3_PLC | B_XHCI_MEM_PORTSCXUSB3_PRC | B_XHCI_MEM_PORTSCXUSB3_OCC | B_XHCI_MEM_PORTSCXUSB3_WRC | B_XHCI_MEM_PORTSCXUSB3_PEC | B_XHCI_MEM_PORTSCXUSB3_CSC | B_XHCI_MEM_PORTSCXUSB3_PED)
//
// 0x2000 - 0x21FF - Runtime Registers
// 0x3000 - 0x307F - Doorbell Registers
//
#define R_XHCI_MEM_XECP_SUPP_USB2_2                     0x8008
#define R_XHCI_MEM_XECP_SUPP_USB3_2                     0x8028
#define B_XHCI_MEM_XECP_SUPP_USBX_2_CPC                 0xFF00  ///< Mask for Compatible Port Count in Capability
#define N_XHCI_MEM_XECP_SUPP_USBX_2_CPC                 8       ///< Shift for Compatible Port Count
#define R_XHCI_MEM_HOST_CTRL_SCH_REG                    0x8094
#define R_XHCI_MEM_HOST_CTRL_ODMA_REG                   0x8098  ///< Host Control ODMA Register
#define R_XHCI_MEM_HOST_CTRL_IDMA_REG                   0x809C
#define R_XHCI_MEM_PMCTRL                               0x80A4
#define B_XHCI_MEM_PMCTRL_SSU3LFPS_DET                  0xFF00  ///< SS U3 LFPS Detection Threshold Mask
#define N_XHCI_MEM_PMCTRL_SSU3LPFS_DET                  8       ///< SS U3 LFPS Detection Threshold position
#define R_XHCI_MEM_PGCBCTRL                             0x80A8  ///< PGCB Control
#define R_XHCI_MEM_HOST_CTRL_MISC_REG                   0x80B0  ///< Host Controller Misc Reg
#define R_XHCI_MEM_HOST_CTRL_MISC_REG_2                 0x80B4  ///< Host Controller Misc Reg 2
#define R_XHCI_MEM_SSPE                                 0x80B8  ///< Super Speed Port Enables
#define R_XHCI_MEM_AUX_CTRL_REG                         0x80C0  ///< AUX_CTRL_REG - AUX Reset Control
#define R_XHCI_MEM_HOST_BW_OV_HS_REG                    0x80C8  ///< HOST_BW_OV_HS_REG - High Speed TT Bandwidth Overhead
#define B_XHCI_MEM_HOST_BW_OV_HS_REG_OVHD_HSTTBW        0x0FFF  ///< Mask for Overhead per packet for HS-TT BW calculations value
#define B_XHCI_MEM_HOST_BW_OV_HS_REG_OVHD_HSBW          0xFFF000 ///< Mask for Overhead per packet for HS BW calculations value
#define N_XHCI_MEM_HOST_BW_OV_HS_REG_OVHD_HSBW          12
#define R_XHCI_MEM_DUAL_ROLE_CFG0                       0x80D8
#define R_XHCI_MEM_DUAL_ROLE_CFG1                       0x80DC
#define R_XHCI_MEM_AUX_CTRL_REG1                        0x80E0
#define R_XHCI_MEM_HOST_CTRL_PORT_LINK_REG              0x80EC  ///< SuperSpeed Port Link Control
#define R_XHCI_MEM_USB2_LINK_MGR_CTRL_REG1_DW1          0x80F0  ///< USB2_LINK_MGR_CTRL_REG1 - USB2 Port Link Control 1, 2, 3, 4
#define R_XHCI_MEM_USB2_LINK_MGR_CTRL_REG1_DW2          0x80F4  ///< USB2_LINK_MGR_CTRL_REG1 - USB2 Port Link Control 1, 2, 3, 4
#define R_XHCI_MEM_USB2_LINK_MGR_CTRL_REG1_DW3          0x80F8  ///< USB2_LINK_MGR_CTRL_REG1 - USB2 Port Link Control 1, 2, 3, 4
#define R_XHCI_MEM_USB2_LINK_MGR_CTRL_REG1_DW4          0x80FC  ///< USB2_LINK_MGR_CTRL_REG1 - USB2 Port Link Control 1, 2, 3, 4
#define R_XHCI_MEM_HOST_CTRL_BW_CTRL_REG                0x8100  ///< HOST_CTRL_BW_CTRL_REG - Host Controller Bandwidth Control Register
#define R_XHCI_MEM_HOST_IF_CTRL_REG                     0x8108  ///< HOST_IF_CTRL_REG - Host Controller Interface Control Register
#define R_XHCI_MEM_HOST_CTRL_TRM_REG2                   0x8110  ///< HOST_CTRL_TRM_REG2 - Host Controller Transfer Manager Control 2
#define R_XHCI_MEM_HOST_CTRL_BW_MAX_REG                 0x8128  ///< HOST_CTRL_BW_MAX_REG - Max BW Control Reg 4
#define B_XHCI_MEM_HOST_CTRL_BW_MAX_REG_MAX_HS_BW       0xFFF000///< HOST_CTRL_BW_MAX_REG - Max. Number of BW units for HS ports
#define N_XHCI_MEM_HOST_CTRL_BW_MAX_REG_MAX_HS_BW       12      ///< HOST_CTRL_BW_MAX_REG - Max. Number of BW units for HS ports position
#define R_XHCI_MEM_HOST_IF_PWR_CTRL_REG0                0x8140  ///< HOST_IF_PWR_CTRL_REG0 - Power Scheduler Control 0
#define R_XHCI_MEM_HOST_IF_PWR_CTRL_REG1                0x8144  ///< HOST_IF_PWR_CTRL_REG1 - Power Scheduler Control 1
#define R_XHCI_MEM_AUX_CTRL_REG2                        0x8154  ///< AUX_CTRL_REG2 - Aux PM Control Register 2
#define R_XHCI_MEM_HOST_CTRL_SCH_REG2                   0x8160  ///< HOST_CTRL_SCH_REG2 - Host Controller Scheduler 2
#define R_XHCI_MEM_USB2PHYPM                            0x8164  ///< USB2 PHY Power Management Control
#define R_XHCI_MEM_AUXCLKCTL                            0x816C  ///< xHCI Aux Clock Control Register
#define R_XHCI_MEM_USBLPM                               0x8170  ///< USB LPM Parameters
#define B_XHCI_MEM_USBLPM_MIN_U2_ELFPS_D                (BIT18 | BIT17 | BIT16) ///< Min U2 Exit LFPS Duration
#define R_XHCI_MEM_XHCLTVCTL                            0x8174  ///< xHC Latency Tolerance Parameters - LTV Control
#define B_XHCI_MEM_XHCLTVCTL_USB2_PL0_LTV               0xFFF   ///< USB2 Port L0 LTV
#define R_XHCI_MEM_XHCLTVCTL2                           0x8178  ///< xHC Latency Tolerance Control 2 - LTV Control 2
#define R_XHCI_MEM_LTVHIT                               0x817C  ///< xHC Latency Tolerance Parameters - High Idle Time Control
#define R_XHCI_MEM_LTVMIT                               0x8180  ///< xHC Latency Tolerance Parameters - Medium Idle Time Control
#define R_XHCI_MEM_LTVLIT                               0x8184  ///< xHC Latency Tolerance Parameters - Low Idle Time Control
#define R_XHCI_MEM_CFG_USB2_LTV_U2_NOREQ_REG            0x8188  ///< ADO USB2 LTR Register
#define R_XHCI_MEM_XECP_CMDM_CTRL_REG1                  0x818C  ///< Command Manager Control 1
#define R_XHCI_MEM_XECP_CMDM_CTRL_REG2                  0x8190  ///< Command Manager Control 2
#define R_XHCI_MEM_XECP_CMDM_CTRL_REG3                  0x8194  ///< Command Manager Control 3
#define R_XHCI_MEM_PDDIS                                0x8198  ///< xHC Pulldown Disable Control
#define R_XHCI_MEM_THROTT                               0x819C  ///< XHCI Throttle Control
#define R_XHCI_MEM_LFPSPM                               0x81A0  ///< LFPS PM Control
#define R_XHCI_MEM_THROTT2                              0x81B4  ///< XHCI Throttle
#define R_XHCI_MEM_LFPSONCOUNT                          0x81B8  ///< LFPS On Count
#define R_XHCI_MEM_D0I2CTRL                             0x81BC  ///< D0I2 Control Register
#define B_XHCI_MEM_D0I2CTRL                             0x3FDFFFF0  ///< D0I2 Control Register Mask
#define B_XHCI_MEM_D0I2CTRL_MSI_IDLE_THRESHOLD          0xFFF0  ///< Bitmask for MSI Idle Threshold
#define N_XHCI_MEM_D0I2CTRL_MSI_IDLE_THRESHOLD          4       ///< Bitshift for MSI Idle Threshold
#define N_XHCI_MEM_D0I2CTRL_MSID0I2PWT                  16      ///< Bitshift for MSI D0i2 Pre Wake Time
#define B_XHCI_MEM_D0I2CTRL_D0I2_MIN_RESIDENCY          0x1C00000 ///< D0i2 Minimum Residency bits
#define N_XHCI_MEM_D0I2CTRL_D0I2_MIN_RESIDENCY          22      ///< Bitshift for D0i2 Minimum Residency
#define N_XHCI_MEM_D0I2CTRL_D0I2_ENTRY_HYSTERESIS_TIMER 26      ///< Bitshift for D0i2 Entry Hysteresis Timer
#define R_XHCI_MEM_D0I2SCH_ALARM_CTRL                   0x81C0  ///< D0i2 Scheduler Alarm Control Register
#define B_XHCI_MEM_D0I2SCH_ALARM_CTRL                   0x1FFF1FFF  ///< Bitmask for D0i2 Scheduler Alarm Control Register
#define N_XHCI_MEM_D0I2SCH_ALARM_CTRL_D0I2IT            16      ///< Bitshift for D0i2 Idle Time
#define R_XHCI_MEM_USB2PMCTRL                           0x81C4  ///< USB2 Power Management Control
#define R_XHCI_MEM_AUX_CTRL_REG3                        0x81C8  ///< Aux PM Control 3 Register
#define R_XHCI_MEM_TRBPRFCTRLREG1                       0x81D0  ///< TRB Prefetch Control Register 1
#define R_XHCI_MEM_TRBPRFCACHEINVREG                    0x81D8  ///< TRB Prefetch Cache Invalidation Register 1
#define B_XHCI_MEM_TRBPRFCACHEINVREG_EN_TRB_FLUSH       0x7F    ///< TRB Flushing for various commands
#define N_XHCI_MEM_TRBPRFCACHEINVREG_EN_TRB_FLUSH       17      ///< Enable TRB flushing for various command

#define R_XHCI_MEM_DBGDEV_CTRL_REG1                     0x8754    ///< Debug Device Control Register 1

#define R_XHCI_MEM_PMCTRL2                                    0x8468    ///< PMCTRL2 - Power Management Control 2
#define R_XHCI_MEM_HOST_CTRL_SUS_LINK_PORT_REG                0x81F8
#define R_XHCI_MEM_HOST_CTRL_EARLY_DBG_REG                    0x81FC
#define R_XHCI_MEM_MULT_IN_SCH_POLICY                         0x82A0    ///< Multiple IN Scheduler Policy Register
#define R_XHCI_MEM_MULT_IN_FAIRNESS_POLICY_1                  0x82A4    ///< Fairness Policy Register 1
#define R_XHCI_MEM_XHCI_ECN_REG                               0x82FC
#define R_XHCI_MEM_GRP0_SAI_WAC_POLICY_LO                     0x8308    ///< Group0 SAI Write Access Control Policy Register Low
#define R_XHCI_MEM_GRP0_SAI_RAC_POLICY_LO                     0x8310    ///< Group0 SAI Read Access Control Policy Low
#define R_XHCI_MEM_PMREQ_CTRL_REG                             0x83D0    ///< PMREQ Control Register
#define R_XHCI_MEM_ENH_CLK_GATE_CTRL                          0x83D8    ///< Enhanced Clock Gate Control Policy Register
#define R_XHCI_MEM_HOST_CTRL_SSP_LINK_PORT_REG1               0x8E5C
#define R_XHCI_MEM_HOST_CTRL_SSP_LINK_REG2                    0x8E68
#define R_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG2                    0x8E74
#define R_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG3                    0x8E78
#define R_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4                    0x8E7C
#define B_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4_SCD_LFPS_TIMEOUT   0xFE0000
#define N_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4_SCD_LFPS_TIMEOUT   17
#define B_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4_SCD_TX_COUNT       0x1C000
#define N_XHCI_MEM_HOST_CTRL_SSP_LFPS_REG4_SCD_TX_COUNT       14
#define R_XHCI_MEM_HOST_CTRL_SSP_CONFIG_REG1                  0x8E80
#define R_XHCI_MEM_HOST_CTRL_SSP_CONFIG_REG2                  0x8E9C
#define R_XHCI_MEM_HOST_CTRL_USB3_RECAL                       0x8E84
#define R_XHCI_MEM_HOST_CTRL_SSP_TUNNELING_REG                0x8EA0    ///< HOST_CTRL_SSP_TUNNELING_REG

#define R_XHCI_MEM_HOST_CTRL_USB3_CP13_DEEMPH                 0x8E8C
#define R_XHCI_MEM_HOST_CTRL_USB3_CP14_DEEMPH                 0x8E90
#define R_XHCI_MEM_HOST_CTRL_USB3_CP15_DEEMPH                 0x8E94
#define R_XHCI_MEM_HOST_CTRL_USB3_CP16_DEEMPH                 0x8E98
#define N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_CP1_PRECURSOR   12
#define B_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_CP1_PRECURSOR   0x1F000
#define N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_C0_VALUE        6
#define B_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_C0_VALUE        0xFC0
#define N_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_CM1_PRECURSOR   0
#define B_XHCI_MEM_HOST_CTRL_USB3_CPXX_DEEPMH_CM1_PRECURSOR   0x3F

#define R_XHCI_MEM_USBLEGCTLSTS                 0x8470    ///< USB Legacy Support Control Status
#define B_XHCI_MEM_USBLEGCTLSTS_SMIBAR          BIT31     ///< SMI on BAR Status
#define B_XHCI_MEM_USBLEGCTLSTS_SMIPCIC         BIT30     ///< SMI on PCI Command Status
#define B_XHCI_MEM_USBLEGCTLSTS_SMIOSC          BIT29     ///< SMI on OS Ownership Change Status
#define B_XHCI_MEM_USBLEGCTLSTS_SMIBARE         BIT15     ///< SMI on BAR Enable
#define B_XHCI_MEM_USBLEGCTLSTS_SMIPCICE        BIT14     ///< SMI on PCI Command Enable
#define B_XHCI_MEM_USBLEGCTLSTS_SMIOSOE         BIT13     ///< SMI on OS Ownership Enable
#define B_XHCI_MEM_USBLEGCTLSTS_SMIHSEE         BIT4      ///< SMI on Host System Error Enable
#define B_XHCI_MEM_USBLEGCTLSTS_USBSMIE         BIT0      ///< USB SMI Enable

//
// Extended Capability Registers
//
#define R_PCH_XHCI_MEM_USB2PDO                  0x84F8    ///< USB2 Port Disable Override register
#define R_PCH_XHCI_MEM_USB3PDO                  0x84FC    ///< USB3 Port Disable Override register

//
// USB Audio Offload registers
//
#define R_XHCI_MEM_AUDIO_OFFLOAD_CTR            0x91F4    ///< Audio Offload Control

//
// USB2 Port Reset Messaging Enable
//
#define R_XHCI_MEM_U2PRM_U2PRDE                 0x92F4    ///< Control bits to enable USB2 Port Reset Messaging

//
// Debug Capability Descriptor Parameters
//
#define B_XHCI_MEM_CAPABILITY_ID                0xFF      ///< Capability ID
#define B_XHCI_MEM_CAPABILITY_NEXT_CAP_PTR      0xFF00    ///< Next Capability Pointer
#define N_XHCI_MEM_CAPABILITY_NEXT_CAP_PTR      8         ///< Byte shift for next capability pointer
#define V_XHCI_MEM_DBC_DCID                     0x0A      ///< Debug Capability ID
#define R_XHCI_MEM_DBC_DCCTRL                   0x20      ///< Debug Capability Control Register (DCCTRL)
#define B_XHCI_MEM_DBC_DCCTRL_DCR               BIT0      ///< Debug Capability - DbC Run (DCR)
#define R_XHCI_MEM_DBC_DCST                     0x24      ///< Debug Capability Status Register (DCST)
#define B_XHCI_MEM_DBC_DCST_DBG_PORT_NUMBER     0xFF      ///< Debug Port Number Mask
#define N_XHCI_MEM_DBC_DCST_DBG_PORT_NUMBER     24        ///< Debug Port Number Offset in DCST register
#define R_XHCI_MEM_DBC_DBCCTL                   0x8760    ///< DBCCTL - DbC Control
#define B_XHCI_MEM_DBC_DBCCTL_DISC_RXD_CNT      0x1F      ///< Soft Disconnect RX Detect Count mask
#define N_XHCI_MEM_DBC_DBCCTL_DISC_RXD_CNT      2         ///< Soft Disconnect RX Detect Count bitshift

//
// Over Current Mapping registers
//
#define R_XHCI_MEM_U2OCM                        0x90A4    ///< XHCI USB2 Overcurrent Pin N Mapping
#define R_XHCI_MEM_U3OCM                        0x9124    ///< XHCI USB3 Overcurrent Pin N Mapping

//
// xHCI Private registers
//
#define R_XHCI_PCR_DAP_USB2PORT_CTRL_0          0x500     ///< DAP USB2 Port0 Control 0 Register
#define B_XHCI_PCR_DAP_USB2PORT_CTRL_0_CE       0xE0      ///< Connector Event (CE) in DAP USB2 Port<N> Control 0 Register
#define N_XHCI_PCR_DAP_USB2PORT_CTRL_0_CE       5         ///< Starting Bit of (CE) in DAP USB2 Port<N> Control 0 Register
#define V_XHCI_PCR_DAP_USB2PORT_CTRL_0_CE_OTG   3         ///< Device Subscription (OTG)

#define R_XHCI_PCR_DAP_USB2PORT_STATUS_0        0x508     ///< DAP USB2 Port0 Status 0 Register
#define B_XHCI_PCR_DAP_USB2PORT_STATUS_0_OS     0xFF      ///< Operation State (OS) in DAP USB2 Port<N> Status 0 Register
#define V_XHCI_PCR_DAP_USB2PORT_STATUS_0_OS_DBC 0x40      ///< DBC Operation State

#define R_XHCI_PCR_DAP_USB3PORT_CTRL_0          0x600     ///< DAP USB3 Port0 Control 0 Register
#define B_XHCI_PCR_DAP_USB3PORT_CTRL_0_CE       0xE0      ///< Connector Event (CE) in DAP USB3 Port<N> Control 0 Register
#define N_XHCI_PCR_DAP_USB3PORT_CTRL_0_CE       5         ///< Starting Bit of (CE) in DAP USB3 Port<N> Control 0 Register
#define V_XHCI_PCR_DAP_USB3PORT_CTRL_0_CE_OTG   3         ///< Device Subscription (OTG)
//
// xDCI (OTG) USB Device Controller
//
#define PCI_DEVICE_NUMBER_PCH_XDCI              20
#define PCI_FUNCTION_NUMBER_PCH_XDCI            1

//
// xDCI (OTG) PCI Config Space Registers
//
#define R_XDCI_CFG_MEM_BASE                   0x10
#define V_XDCI_CFG_MEM_LENGTH                 0x200000
#define R_XDCI_CFG_PMCSR                      0x84      ///< Power Management Control and Status Register
#define R_XDCI_CFG_GENERAL_PURPOSER_REG1      0xA0      ///< General Purpose PCI RW Register1
#define R_XDCI_CFG_CPGE                       0xA2      ///< Chassis Power Gate Enable
#define R_XDCI_CFG_GENERAL_PURPOSER_REG4      0xAC      ///< General Purpose PCI RW Register4
#define R_XDCI_CFG_GENERAL_INPUT_REG          0xC0      ///< General Input Register

//
// xDCI (OTG) MMIO registers
//
#define R_XDCI_MEM_GCTL                       0xC110  ///< Xdci Global Ctrl
#define B_XDCI_MEM_GCTL_GHIBEREN              BIT1    ///< Hibernation enable
#define R_XDCI_MEM_GUSB2PHYCFG                0xC200  ///< Global USB2 PHY Configuration Register
#define B_XDCI_MEM_GUSB2PHYCFG_SUSPHY         BIT6    ///< Suspend USB2.0 HS/FS/LS PHY
#define R_XDCI_MEM_GUSB3PIPECTL0              0xC2C0  ///< Global USB3 PIPE Control Register 0
#define B_XDCI_MEM_GUSB3PIPECTL0_SUSPEN_EN    BIT17   ///< Suspend USB3.0 SS PHY (Suspend_en)
#define B_XDCI_MEM_GUSB3PIPECTL0_UX_IN_PX     BIT27   ///< Ux Exit in Px
#define R_XDCI_MEM_APBFC_U3PMU_CFG2           0x10F810
#define R_XDCI_MEM_APBFC_U3PMU_CFG4           0x10F818
#define R_XDCI_MEM_APBFC_U3PMU_CFG5           0x10F81C
#define R_XDCI_MEM_APBFC_U3PMU_CFG6           0x10F820

//
// xDCI (OTG) Private Configuration Registers
// (PID:OTG)
// @todo: Verify PCR vaLidity for CPU
//
#define R_OTG_PCR_IOSF_A2                 0xA2
#define R_OTG_PCR_IOSF_PMCTL              0x1D0
#define R_OTG_PCR_PCICFGCTRL1             0x200
#define B_OTG_PCR_PCICFGCTRL_PCI_IRQ      0x0FF00000
#define N_OTG_PCR_PCICFGCTRL_PCI_IRQ      20
#define B_OTG_PCR_PCICFGCTRL_ACPI_IRQ     0x000FF000
#define N_OTG_PCR_PCICFGCTRL_ACPI_IRQ     12
#define B_OTG_PCR_PCICFGCTRL_INT_PIN      0x00000F00
#define N_OTG_PCR_PCICFGCTRL_INT_PIN      8
#define B_OTG_PCR_PCICFGCTRL_BAR1_DIS     0x00000080
#define B_OTG_PCR_PCICFGCTRL_PME_SUP      0x0000007C
#define B_OTG_PCR_PCICFGCTRL_ACPI_INT_EN  0x00000002
#define B_OTG_PCR_PCICFGCTRL_PCI_CFG_DIS  0x00000001

//
// USB2 Private Configuration Registers
// USB2 HIP design featured
// (PID:USB2)
// Doesn't apply to CPU (only USB3 functionality present)
//
#define R_USB2_PCR_GLOBAL_PORT                0x4001                    ///< USB2 GLOBAL PORT
#define R_USB2_PCR_PP_LANE_BASE_ADDR          0x4000                    ///< PP LANE base address
#define R_USB2_PCR_PER_PORT                   0x00                      ///< USB2 PER PORT          Addr[7:2] = 0x00
#define B_USB2_PCR_PER_PORT_PERPORTRXISET     (BIT19 | BIT18 | BIT17)
#define N_USB2_PCR_PER_PORT_PERPORTRXISET     17
#define B_USB2_PCR_PER_PORT_PERPORTTXPEHALF   BIT14
#define N_USB2_PCR_PER_PORT_PERPORTTXPEHALF   14
#define B_USB2_PCR_PER_PORT_PERPORTPETXISET   (BIT13 | BIT12 | BIT11)
#define N_USB2_PCR_PER_PORT_PERPORTPETXISET   11
#define B_USB2_PCR_PER_PORT_PERPORTTXISET     (BIT10 | BIT9 | BIT8)
#define N_USB2_PCR_PER_PORT_PERPORTTXISET     8
#define R_USB2_PCR_UTMI_MISC_PER_PORT         0x08                      ///< UTMI MISC REG PER PORT Addr[7:2] = 0x08
#define R_USB2_PCR_PER_PORT_2                 0x26                      ///< USB2 PER PORT 2        Addr[7:2] = 0x26
#define B_USB2_PCR_PER_PORT_2_TXEMPHASISEN    (BIT24 | BIT23)           ///< HSNPREDRVSEL bits value USB2 PER PORT2 register
#define N_USB2_PCR_PER_PORT_2_TXEMPHASISEN    23
#define R_USB2_PCR_GLB_ADP_VBUS_REG           0x402B                    ///< GLB ADP VBUS REG
#define R_USB2_PCR_GLOBAL_PORT_2              0x402C                    ///< USB2 GLOBAL PORT 2
#define R_USB2_PCR_PLLDIVRATIOS_0             0x7000                    ///< PLLDIVRATIOS_0
#define B_USB2_PCR_PLLDIVRATIOS_0_FBDIVRATIO  0xFF000000
#define N_USB2_PCR_PLLDIVRATIOS_0_FBDIVRATIO  24
#define R_USB2_PCR_CONFIG_0                   0x7008                    ///< CONFIG_0
#define B_USB2_PCR_CONFIG_0_INT_COEFF         0x3E000
#define N_USB2_PCR_CONFIG_0_INT_COEFF         13
#define B_USB2_PCR_CONFIG_0_PROP_COEFF        0x1E00
#define N_USB2_PCR_CONFIG_0_PROP_COEFF        9
#define R_USB2_PCR_CONFIG_3                   0x7014                    ///< CONFIG_3
#define B_USB2_PCR_CONFIG_3_SFRCALIB_FMINCNT  0xFF00000
#define N_USB2_PCR_CONFIG_3_SFRCALIB_FMINCNT  24
#define B_USB2_PCR_CONFIG_3_SFRCALIB_FMAXCNT  0xFF0000
#define N_USB2_PCR_CONFIG_3_SFRCALIB_FMAXCNT  16
#define B_USB2_PCR_CONFIG_3_TDCCALIB_OSCCNT   0xFF00
#define N_USB2_PCR_CONFIG_3_TDCCALIB_OSCCNT   8
#define B_USB2_PCR_CONFIG_3_LOCKTIMERCNT_TH   0xFE
#define N_USB2_PCR_CONFIG_3_LOCKTIMERCNT_TH   1
#define R_USB2_PCR_DFT_1                      0x7024                    ///< DFT_1
#define B_USB2_PCR_DFT_1_KPSCALE              0x18000
#define N_USB2_PCR_DFT_1_KPSCALE              15
#define B_USB2_PCR_DFT_1_KISCALE              0x6000
#define N_USB2_PCR_DFT_1_KISCALE              13
#define R_USB2_PCR_SFRCONFIG_0                0x702C                    ///< SFRCONFIG_0
#define B_USB2_PCR_SFRCONFIG_0_SFRTIMER_COEF  0xF0
#define N_USB2_PCR_SFRCONFIG_0_SFRTIMER_COEF  4
#define R_USB2_PCR_PLL1                       0x7F02                    ///< USB2 PLL1
#define R_USB2_PCR_CFG_COMPBG                 0x7F04                    ///< USB2 COMPBG

//
// xHCI SSIC registers
//
#define R_XHCI_MEM_SSIC_CONF_REG2_PORT_1          0x880C    ///< SSIC Configuration Register 2 Port 1
#define R_XHCI_MEM_SSIC_CONF_REG2_PORT_2          0x883C    ///< SSIC Configuration Register 2 Port 2
#define B_XHCI_MEM_SSIC_CONF_REG2_PORT_UNUSED     BIT31
#define B_XHCI_MEM_SSIC_CONF_REG2_PROG_DONE       BIT30

//
// xHCI DCI MMIO Registers
//
#define R_XHCI_PCR_DCI_DBC_TRACE_IN_PAYLOAD_BP_LOW         0x50
#define R_XHCI_PCR_DCI_DBC_TRACE_IN_PAYLOAD_BP_HIGH        0x54
#define R_XHCI_PCR_DCI_DBC_TRACE_IN_PAYLOAD_QUALIFIERS     0x58
#define R_XHCI_PCR_DCI_DBC_TRACE_IN_STATUS_BP_LOW          0x60
#define R_XHCI_PCR_DCI_DBC_TRACE_IN_STATUS_BP_HIGH         0x64
#define R_XHCI_PCR_DCI_DBC_TRACE_IN_STATUS_QUALIFIERS      0x68
#define V_XHCI_PCR_DCI_DBC_TRACE_QUALIFIERS                0x22B800

#endif // _USB_REGS_H_


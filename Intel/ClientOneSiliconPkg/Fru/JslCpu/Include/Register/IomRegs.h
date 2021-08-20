/** @file
  Register names for IOM block
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
  Copyright 2017 - 2019 Intel Corporation.

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
#ifndef _SA_REGS_IOM_H_
#define _SA_REGS_IOM_H_

#define R_SA_REGBAR_IOM_TYPEC_STATUS_1_OFFSET     0xfff

#define R_SA_IOM_TYPEC_SW_CONFIGURATION_1         0x40
#define B_SA_IOM_D3_HOT_ENABLE                    BIT8
#define B_SA_IOM_D3_COLD_ENABLE                   BIT9
#define B_SA_IOM_USB_CONNECT_OVERRIDE             BIT10
///
/// B_SA_IOM_SW_RESTORE_USB_AON (BIOS_SUPPORT_S3_SAVE_RESTORE) - The USB AON registers will be restored by SW in S4/5
/// exit, and in S3 if SW_restore_USB_AON register bit is set.
///
#define B_SA_IOM_SW_RESTORE_USB_AON               BIT11
///
/// Unwakeble_SX (BIOS_DISABLE_TCSS_WAKEUP_IN_S4S5) - The ability to wake up from SX state by TCSS
///
#define B_SA_IOM_UNWAKEBLE_SX                     BIT12
///
/// BIOS_EC_REPLAY_CONNECTION_S3 - If a device is attached must have support from EC to replay connection map to shut
/// the rail down
///
#define BIOS_EC_REPLAY_CONNECTION_S3              BIT13
///
/// BIOS_EC_REPLAY_CONNECTION_S4S5 - If a device is attached must have support from EC to replay connection map to shut
/// the rail down
///
#define BIOS_EC_REPLAY_CONNECTION_S4S5            BIT14
///
/// SRID/CRID indication use Compatible Revision ID instead of Stepping Revision ID revision
//
#define B_SA_IOM_TYPEC_SW_CONFIGURATION_1_CRID_EN BIT18
#define B_SA_IOM_TYPEC_SW_CONFIGURATION_1_LOCK    BIT31

#define R_SA_IOM_TYPEC_SW_CONFIGURATION_2    0x44

///
/// AUX orientation override. Set by BIOS. One bit set for override the Aux orientation (meaning orientation is being
/// set on the board and IOM needs to ignore orientation value coming from the PMC) and 2nd for the orientation. The
/// register needs to be part of the save and restore in case we lose power in S0.
///
#define R_SA_IOM_TYPEC_SW_CONFIGURATION_3         0x48
#define B_SA_IOM_TYPEC_SW_CONFIGURATION_3_LOCK    BIT31

#define R_SA_IOM_TYPEC_SW_CONFIGURATION_4         0x98
#define B_SA_IOM_TYPEC_SW_CONFIGURATION_4_LOCK    BIT31

#define R_SA_IOM_TYPEC_CONTROL                  0x4C

///
/// This register maps the current status of each IP in the TypeC SS
///
#define R_SA_IOM_TYPEC_STATUS_1                   0x50
///
/// This indication mean the IOM FW got out of reset and strated the event loop handling.
///
#define B_SA_IOM_IOM_READY                        BIT30

///
/// This register maps the current status of each IP in the TypeC SS
///
#define R_SA_IOM_TYPEC_STATUS_2                   0x54

///
/// This register communicate IOM Engineer
///
#define R_SA_IOM_BIOS_MAIL_BOX_CMD        0x70

#define B_SA_IOM_BIOS_SET_TO_RUN          BIT31
#define V_SA_IOM_BIOS_UPDATE_DEVEN_CMD    0x1
#define V_SA_IOM_BIOS_GEM_SB_TRAN_CMD     0x2
#define V_SA_IOM_BIOS_CMD_TYPE_XDCI_INT   0x1
#define R_SA_IOM_BIOS_MAIL_BOX_DATA       0x74
#define B_SA_IOM_BIOS_MAIL_BOX_IOM_EN     BIT16

/**
 IOM status register holding the version (IOM_CSME_IMR_IOM_STATUS) in
 Bits 15:0 - FW Version
 Bits 29:22 - Error Code
 Bit 30 - Valid : Although the FW is in the IMR, it failed authentication and therefore should not be trusted.
          0 - Untrusted FW
          1 - Successful authentication
 Bit 31 - Done: FW download to IMR is done
**/
#define R_SA_IOM_CSME_IMR_IOM_STATUS              0x0C

/**
 TBT status register holding the version (IOM_CSME_IMR_MG_STATUS) in
 Bits 15:0 - FW Version
 Bits 29:22 - Error Code
 Bit 30 - Valid : Although the FW is in the IMR, it failed authentication and therefore should not be trusted.
          0 - Untrusted FW
          1 - Successful authentication
 Bit 31 - Done: FW download to IMR is done
**/
#define R_SA_IOM_CSME_IMR_MG_STATUS               0x10

/**
 TBT status register holding the version (IOM_CSME_IMR_TBT_STATUS) in
 Bits 15:0 - FW Version
 Bits 29:22 - Error Code
 Bit 30 - Valid : Although the FW is in the IMR, it failed authentication and therefore should not be trusted.
          0 - Untrusted FW
          1 - Successful authentication
 Bit 31 - Done: FW download to IMR is done
**/
#define R_SA_IOM_CSME_IMR_TBT_STATUS              0x14

///
/// This register BIOS communicate the PCH AUX layout with IOM
///
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PUP_MMOFFSET_1  0x1070
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PUP_MMOFFSET_2  0x1074
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PUP_MMOFFSET_3  0x1078
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PUP_MMOFFSET_4  0x107C
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PUP_MMOFFSET_5  0x1080
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PUP_MMOFFSET_6  0x1084
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PDN_MMOFFSET_1  0x1088
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PDN_MMOFFSET_2  0x108C
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PDN_MMOFFSET_3  0x1090
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PDN_MMOFFSET_4  0x1094
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PDN_MMOFFSET_5  0x1098
#define R_SA_IOM_AUX_ORI_BIAS_CTRL_PDN_MMOFFSET_6  0x109C

/**
 IOM FW information register (IOM_FW_INFO).
 This register is updated by IOM FW at boot time with the version info related to the loaded IOM FW image.
 Bit 3:0   - Used to distinguish between releases to different platforms. Silicon = 0x0, VP = 0x1, Others are reserved.
 Bit 7:4   - RSVD
 Bit 23:8  - Incremented for each official release
 Bit 31:24 - Increment each and every time there is new silicon. Example: TGL-A0 = 0x8, TGL-B0 = 0x9, TGL-C0 = 0xA, etc
**/
#define R_SA_IOM_FW_INFO                               0x15F8

/**
 IOM FW information register for engineering version (IOM_FW_INFO_ENGR).
 This register is updated by IOM FW at boot time with the version info related to the loaded IOM FW image.

 Bit 31:0 - Non-zero value used to identify engineering versions / hotfixes. Shall be zero for official releases.
**/
#define R_SA_IOM_FW_INFO_ENGR                          0x15FC


//
// Definition for SBI
//

#define R_SA_IOM_CFG_SBIADDR                         0xD0
#define B_SA_IOM_CFG_SBIADDR_DESTID                  0xFF000000
#define B_SA_IOM_CFG_SBIADDR_RS                      0x000F0000
#define B_SA_IOM_CFG_SBIADDR_OFFSET                  0x0000FFFF
#define R_SA_IOM_CFG_SBIDATA                         0xD4
#define B_SA_IOM_CFG_SBIDATA_DATA                    0xFFFFFFFF
#define R_SA_IOM_CFG_SBISTAT                         0xD8
#define B_SA_IOM_CFG_SBISTAT_OPCODE                  0xFF00
#define B_SA_IOM_CFG_SBISTAT_POSTED                  BIT7
#define B_SA_IOM_CFG_SBISTAT_RESPONSE                0x0006
#define N_SA_IOM_CFG_SBISTAT_RESPONSE                1
#define B_SA_IOM_CFG_SBISTAT_INITRDY                 BIT0
#define R_SA_IOM_CFG_SBIRID                          0xDA
#define B_SA_IOM_CFG_SBIRID_FBE                      0xF000
#define B_SA_IOM_CFG_SBIRID_BAR                      0x0700
#define B_SA_IOM_CFG_SBIRID_FID                      0x00FF
#define R_SA_IOM_CFG_SBIEXTADDR                      0xDC
#define B_SA_IOM_CFG_SBIEXTADDR_ADDR                 0xFFFFFFFF


typedef union {
  UINT32 RegValue;
  struct {
    UINT32 GpioPortId:8;
    UINT32 Bit:3;
    UINT32 Rev0:5;
    UINT32 VwIndex:8;
    UINT32 Rev1:8;
  } Bits;
} IOM_AUX_ORI_BIAS_STRUCTURE;


#define R_SA_IOM_AUX_ORI_OFFSET      0x00000048
#define B_SA_IOM_AUX_ORI_LOCK        0x80000000
#define B_SA_IOM_AUX_ORI_ENA_1       0x00000001
#define B_SA_IOM_AUX_ORI_1           0x00000002
#define B_SA_IOM_AUX_ORI_ENA_2       0x00000004
#define B_SA_IOM_AUX_ORI_2           0x00000008
#define B_SA_IOM_AUX_ORI_ENA_3       0x00000010
#define B_SA_IOM_AUX_ORI_3           0x00000020
#define B_SA_IOM_AUX_ORI_ENA_4       0x00000040
#define B_SA_IOM_AUX_ORI_4           0x00000080
#define B_SA_IOM_AUX_ORI_ENA_5       0x00000100
#define B_SA_IOM_AUX_ORI_5           0x00000200
#define B_SA_IOM_AUX_ORI_ENA_6       0x00000400
#define B_SA_IOM_AUX_ORI_6           0x00000800

#define R_SA_IOM_HSL_ORI_OFFSET      0x00000098
#define B_SA_IOM_HSL_ORI_LOCK        0x80000000
#define B_SA_IOM_HSL_ORI_ENA_1       0x00000001
#define B_SA_IOM_HSL_ORI_1           0x00000002
#define B_SA_IOM_HSL_ORI_ENA_2       0x00000004
#define B_SA_IOM_HSL_ORI_2           0x00000008
#define B_SA_IOM_HSL_ORI_ENA_3       0x00000010
#define B_SA_IOM_HSL_ORI_3           0x00000020
#define B_SA_IOM_HSL_ORI_ENA_4       0x00000040
#define B_SA_IOM_HSL_ORI_4           0x00000080
#define B_SA_IOM_HSL_ORI_ENA_5       0x00000100
#define B_SA_IOM_HSL_ORI_5           0x00000200
#define B_SA_IOM_HSL_ORI_ENA_6       0x00000400
#define B_SA_IOM_HSL_ORI_6           0x00000800


#endif


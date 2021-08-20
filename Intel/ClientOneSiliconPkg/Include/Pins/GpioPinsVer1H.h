/** @file
  GPIO pins for ICL-PCH-H,

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
#ifndef _GPIO_PINS_VER1_H_H_
#define _GPIO_PINS_VER1_H_H_
///
/// This header file should be used together with
/// PCH GPIO lib in C and ASL. All defines used
/// must match both ASL/C syntax
///

///
/// Unique ID used in GpioPad defines
///
#define GPIO_VER1_H_CHIPSET_ID      0x5

///
/// ICL H GPIO Groups
/// Use below for functions from PCH GPIO Lib which
/// require GpioGroup as argument
///

#define GPIO_VER1_H_GROUP_GPP_A    0x0500
#define GPIO_VER1_H_GROUP_GPP_B    0x0501
#define GPIO_VER1_H_GROUP_GPP_C    0x0502
#define GPIO_VER1_H_GROUP_GPP_D    0x0503
#define GPIO_VER1_H_GROUP_GPP_E    0x0504
#define GPIO_VER1_H_GROUP_GPP_F    0x0505
#define GPIO_VER1_H_GROUP_GPP_G    0x0506
#define GPIO_VER1_H_GROUP_GPP_H    0x0507
#define GPIO_VER1_H_GROUP_GPP_I    0x0508
#define GPIO_VER1_H_GROUP_GPP_J    0x0509
#define GPIO_VER1_H_GROUP_GPP_K    0x050A
#define GPIO_VER1_H_GROUP_GPP_R    0x050B
#define GPIO_VER1_H_GROUP_GPP_S    0x050C
#define GPIO_VER1_H_GROUP_GPD      0x050D
#define GPIO_VER1_H_GROUP_VGPIO    0x050E
#define GPIO_VER1_H_GROUP_VGPIO_0  0x050F
#define GPIO_VER1_H_GROUP_VGPIO_3  0x0510
#define GPIO_VER1_H_GROUP_SPI      0x0511
#define GPIO_VER1_H_GROUP_JTAG     0x0512
#define GPIO_VER1_H_GROUP_CPU      0x0513


///
/// ICL H GPIO pins
/// Use below for functions from PCH GPIO Lib which
/// require GpioPad as argument. Encoding used here
/// has all information required by library functions
///
#define GPIO_VER1_H_GPP_A0                   0x05000000
#define GPIO_VER1_H_GPP_A1                   0x05000001
#define GPIO_VER1_H_GPP_A2                   0x05000002
#define GPIO_VER1_H_GPP_A3                   0x05000003
#define GPIO_VER1_H_GPP_A4                   0x05000004
#define GPIO_VER1_H_GPP_A5                   0x05000005
#define GPIO_VER1_H_GPP_A6                   0x05000006
#define GPIO_VER1_H_GPP_A7                   0x05000007
#define GPIO_VER1_H_GPP_A8                   0x05000008
#define GPIO_VER1_H_GPP_A9                   0x05000009
#define GPIO_VER1_H_GPP_A10                  0x0500000A
#define GPIO_VER1_H_GPP_A11                  0x0500000B
#define GPIO_VER1_H_GPP_A12                  0x0500000C
#define GPIO_VER1_H_GPP_A13                  0x0500000D
#define GPIO_VER1_H_GPP_A14                  0x0500000E
#define GPIO_VER1_H_GPP_A15                  0x0500000F
#define GPIO_VER1_H_GPP_A16                  0x05000010
#define GPIO_VER1_H_GPP_A17                  0x05000011
#define GPIO_VER1_H_GPP_A18                  0x05000012
#define GPIO_VER1_H_GPP_A19                  0x05000013
#define GPIO_VER1_H_GPP_A20                  0x05000014
#define GPIO_VER1_H_GPP_A21                  0x05000015
#define GPIO_VER1_H_GPP_A22                  0x05000016
#define GPIO_VER1_H_GPP_A23                  0x05000017
#define GPIO_VER1_H_ESPI_CLK_LOOPBK          0x05000018

#define GPIO_VER1_H_GPP_B0                   0x05010000
#define GPIO_VER1_H_GPP_B1                   0x05010001
#define GPIO_VER1_H_GPP_B2                   0x05010002
#define GPIO_VER1_H_GPP_B3                   0x05010003
#define GPIO_VER1_H_GPP_B4                   0x05010004
#define GPIO_VER1_H_GPP_B5                   0x05010005
#define GPIO_VER1_H_GPP_B6                   0x05010006
#define GPIO_VER1_H_GPP_B7                   0x05010007
#define GPIO_VER1_H_GPP_B8                   0x05010008
#define GPIO_VER1_H_GPP_B9                   0x05010009
#define GPIO_VER1_H_GPP_B10                  0x0501000A
#define GPIO_VER1_H_GPP_B11                  0x0501000B
#define GPIO_VER1_H_GPP_B12                  0x0501000C
#define GPIO_VER1_H_GPP_B13                  0x0501000D
#define GPIO_VER1_H_GPP_B14                  0x0501000E
#define GPIO_VER1_H_GPP_B15                  0x0501000F
#define GPIO_VER1_H_GPP_B16                  0x05010010
#define GPIO_VER1_H_GPP_B17                  0x05010011
#define GPIO_VER1_H_GPP_B18                  0x05010012
#define GPIO_VER1_H_GPP_B19                  0x05010013
#define GPIO_VER1_H_GPP_B20                  0x05010014
#define GPIO_VER1_H_GPP_B21                  0x05010015
#define GPIO_VER1_H_GPP_B22                  0x05010016
#define GPIO_VER1_H_GPP_B23                  0x05010017
#define GPIO_VER1_H_GSPI0_CLK_LOOPBK         0x05010018
#define GPIO_VER1_H_GSPI1_CLK_LOOPBK         0x05010019

#define GPIO_VER1_H_GPP_C0                   0x05020000
#define GPIO_VER1_H_GPP_C1                   0x05020001
#define GPIO_VER1_H_GPP_C2                   0x05020002
#define GPIO_VER1_H_GPP_C3                   0x05020003
#define GPIO_VER1_H_GPP_C4                   0x05020004
#define GPIO_VER1_H_GPP_C5                   0x05020005
#define GPIO_VER1_H_GPP_C6                   0x05020006
#define GPIO_VER1_H_GPP_C7                   0x05020007
#define GPIO_VER1_H_GPP_C8                   0x05020008
#define GPIO_VER1_H_GPP_C9                   0x05020009
#define GPIO_VER1_H_GPP_C10                  0x0502000A
#define GPIO_VER1_H_GPP_C11                  0x0502000B
#define GPIO_VER1_H_GPP_C12                  0x0502000C
#define GPIO_VER1_H_GPP_C13                  0x0502000D
#define GPIO_VER1_H_GPP_C14                  0x0502000E
#define GPIO_VER1_H_GPP_C15                  0x0502000F
#define GPIO_VER1_H_GPP_C16                  0x05020010
#define GPIO_VER1_H_GPP_C17                  0x05020011
#define GPIO_VER1_H_GPP_C18                  0x05020012
#define GPIO_VER1_H_GPP_C19                  0x05020013
#define GPIO_VER1_H_GPP_C20                  0x05020014
#define GPIO_VER1_H_GPP_C21                  0x05020015
#define GPIO_VER1_H_GPP_C22                  0x05020016
#define GPIO_VER1_H_GPP_C23                  0x05020017

#define GPIO_VER1_H_GPP_D0                   0x05030000
#define GPIO_VER1_H_GPP_D1                   0x05030001
#define GPIO_VER1_H_GPP_D2                   0x05030002
#define GPIO_VER1_H_GPP_D3                   0x05030003
#define GPIO_VER1_H_GPP_D4                   0x05030004
#define GPIO_VER1_H_GPP_D5                   0x05030005
#define GPIO_VER1_H_GPP_D6                   0x05030006
#define GPIO_VER1_H_GPP_D7                   0x05030007
#define GPIO_VER1_H_GPP_D8                   0x05030008
#define GPIO_VER1_H_GPP_D9                   0x05030009
#define GPIO_VER1_H_GPP_D10                  0x0503000A
#define GPIO_VER1_H_GPP_D11                  0x0503000B
#define GPIO_VER1_H_GPP_D12                  0x0503000C
#define GPIO_VER1_H_GPP_D13                  0x0503000D
#define GPIO_VER1_H_GPP_D14                  0x0503000E
#define GPIO_VER1_H_GPP_D15                  0x0503000F
#define GPIO_VER1_H_GSPI2_CLK_LOOPBK         0x05030010
#define GPIO_VER1_H_SPI1_CLK_LOOPBK          0x05030011

#define GPIO_VER1_H_GPP_E0                   0x05040000
#define GPIO_VER1_H_GPP_E1                   0x05040001
#define GPIO_VER1_H_GPP_E2                   0x05040002
#define GPIO_VER1_H_GPP_E3                   0x05040003
#define GPIO_VER1_H_GPP_E4                   0x05040004
#define GPIO_VER1_H_GPP_E5                   0x05040005
#define GPIO_VER1_H_GPP_E6                   0x05040006
#define GPIO_VER1_H_GPP_E7                   0x05040007
#define GPIO_VER1_H_GPP_E8                   0x05040008
#define GPIO_VER1_H_GPP_E9                   0x05040009
#define GPIO_VER1_H_GPP_E10                  0x0504000A
#define GPIO_VER1_H_GPP_E11                  0x0504000B
#define GPIO_VER1_H_GPP_E12                  0x0504000C

#define GPIO_VER1_H_GPP_F0                   0x05050000
#define GPIO_VER1_H_GPP_F1                   0x05050001
#define GPIO_VER1_H_GPP_F2                   0x05050002
#define GPIO_VER1_H_GPP_F3                   0x05050003
#define GPIO_VER1_H_GPP_F4                   0x05050004
#define GPIO_VER1_H_GPP_F5                   0x05050005
#define GPIO_VER1_H_GPP_F6                   0x05050006
#define GPIO_VER1_H_GPP_F7                   0x05050007
#define GPIO_VER1_H_GPP_F8                   0x05050008
#define GPIO_VER1_H_GPP_F9                   0x05050009
#define GPIO_VER1_H_GPP_F10                  0x0505000A
#define GPIO_VER1_H_GPP_F11                  0x0505000B
#define GPIO_VER1_H_GPP_F12                  0x0505000C
#define GPIO_VER1_H_GPP_F13                  0x0505000D
#define GPIO_VER1_H_GPP_F14                  0x0505000E
#define GPIO_VER1_H_GPP_F15                  0x0505000F
#define GPIO_VER1_H_GPP_F16                  0x05050010
#define GPIO_VER1_H_GPP_F17                  0x05050011
#define GPIO_VER1_H_GPP_F18                  0x05050012
#define GPIO_VER1_H_GPP_F19                  0x05050013
#define GPIO_VER1_H_GPP_F20                  0x05050014
#define GPIO_VER1_H_GPP_F21                  0x05050015
#define GPIO_VER1_H_GPP_F22                  0x05050016
#define GPIO_VER1_H_GPP_F23                  0x05050017

#define GPIO_VER1_H_GPP_G0                   0x05060000
#define GPIO_VER1_H_GPP_G1                   0x05060001
#define GPIO_VER1_H_GPP_G2                   0x05060002
#define GPIO_VER1_H_GPP_G3                   0x05060003
#define GPIO_VER1_H_GPP_G4                   0x05060004
#define GPIO_VER1_H_GPP_G5                   0x05060005
#define GPIO_VER1_H_GPP_G6                   0x05060006
#define GPIO_VER1_H_GPP_G7                   0x05060007
#define GPIO_VER1_H_GPP_G8                   0x05060008
#define GPIO_VER1_H_GPP_G9                   0x05060009
#define GPIO_VER1_H_GPP_G10                  0x0506000A
#define GPIO_VER1_H_GPP_G11                  0x0506000B
#define GPIO_VER1_H_GPP_G12                  0x0506000C
#define GPIO_VER1_H_GPP_G13                  0x0506000D
#define GPIO_VER1_H_GPP_G14                  0x0506000E
#define GPIO_VER1_H_GPP_G15                  0x0506000F

#define GPIO_VER1_H_GPP_H0                   0x05070000
#define GPIO_VER1_H_GPP_H1                   0x05070001
#define GPIO_VER1_H_GPP_H2                   0x05070002
#define GPIO_VER1_H_GPP_H3                   0x05070003
#define GPIO_VER1_H_GPP_H4                   0x05070004
#define GPIO_VER1_H_GPP_H5                   0x05070005
#define GPIO_VER1_H_GPP_H6                   0x05070006
#define GPIO_VER1_H_GPP_H7                   0x05070007
#define GPIO_VER1_H_GPP_H8                   0x05070008
#define GPIO_VER1_H_GPP_H9                   0x05070009
#define GPIO_VER1_H_GPP_H10                  0x0507000A
#define GPIO_VER1_H_GPP_H11                  0x0507000B
#define GPIO_VER1_H_GPP_H12                  0x0507000C
#define GPIO_VER1_H_GPP_H13                  0x0507000D
#define GPIO_VER1_H_GPP_H14                  0x0507000E
#define GPIO_VER1_H_GPP_H15                  0x0507000F
#define GPIO_VER1_H_GPP_H16                  0x05070010
#define GPIO_VER1_H_GPP_H17                  0x05070011
#define GPIO_VER1_H_GPP_H18                  0x05070012
#define GPIO_VER1_H_GPP_H19                  0x05070013
#define GPIO_VER1_H_GPP_H20                  0x05070014
#define GPIO_VER1_H_GPP_H21                  0x05070015
#define GPIO_VER1_H_GPP_H22                  0x05070016
#define GPIO_VER1_H_GPP_H23                  0x05070017

#define GPIO_VER1_H_GPP_I0                   0x05080000
#define GPIO_VER1_H_GPP_I1                   0x05080001
#define GPIO_VER1_H_GPP_I2                   0x05080002
#define GPIO_VER1_H_GPP_I3                   0x05080003
#define GPIO_VER1_H_GPP_I4                   0x05080004
#define GPIO_VER1_H_GPP_I5                   0x05080005
#define GPIO_VER1_H_GPP_I6                   0x05080006
#define GPIO_VER1_H_GPP_I7                   0x05080007
#define GPIO_VER1_H_GPP_I8                   0x05080008
#define GPIO_VER1_H_GPP_I9                   0x05080009
#define GPIO_VER1_H_GPP_I10                  0x0508000A
#define GPIO_VER1_H_GPP_I11                  0x0508000B
#define GPIO_VER1_H_GPP_I12                  0x0508000C
#define GPIO_VER1_H_GPP_I13                  0x0508000D
#define GPIO_VER1_H_GPP_I14                  0x0508000E
#define GPIO_VER1_H_SYS_PWROK                0x0508000F
#define GPIO_VER1_H_SYS_RESETB               0x05080010
#define GPIO_VER1_H_MLK_RSTB                 0x05080011

#define GPIO_VER1_H_GPP_J0                   0x05090000
#define GPIO_VER1_H_GPP_J1                   0x05090001
#define GPIO_VER1_H_GPP_J2                   0x05090002
#define GPIO_VER1_H_GPP_J3                   0x05090003
#define GPIO_VER1_H_GPP_J4                   0x05090004
#define GPIO_VER1_H_GPP_J5                   0x05090005
#define GPIO_VER1_H_GPP_J6                   0x05090006
#define GPIO_VER1_H_GPP_J7                   0x05090007
#define GPIO_VER1_H_GPP_J8                   0x05090008
#define GPIO_VER1_H_GPP_J9                   0x05090009

#define GPIO_VER1_H_GPP_K0                   0x050A0000
#define GPIO_VER1_H_GPP_K1                   0x050A0001
#define GPIO_VER1_H_GPP_K2                   0x050A0002
#define GPIO_VER1_H_GPP_K3                   0x050A0003
#define GPIO_VER1_H_GPP_K4                   0x050A0004
#define GPIO_VER1_H_GPP_K5                   0x050A0005
#define GPIO_VER1_H_GPP_K6                   0x050A0006
#define GPIO_VER1_H_GPP_K7                   0x050A0007
#define GPIO_VER1_H_GPP_K8                   0x050A0008
#define GPIO_VER1_H_GPP_K9                   0x050A0009
#define GPIO_VER1_H_GPP_K10                  0x050A000A
#define GPIO_VER1_H_GPP_K11                  0x050A000B

#define GPIO_VER1_H_GPP_R0                   0x050B0000
#define GPIO_VER1_H_GPP_R1                   0x050B0001
#define GPIO_VER1_H_GPP_R2                   0x050B0002
#define GPIO_VER1_H_GPP_R3                   0x050B0003
#define GPIO_VER1_H_GPP_R4                   0x050B0004
#define GPIO_VER1_H_GPP_R5                   0x050B0005
#define GPIO_VER1_H_GPP_R6                   0x050B0006
#define GPIO_VER1_H_GPP_R7                   0x050B0007

#define GPIO_VER1_H_GPP_S0                   0x050C0000
#define GPIO_VER1_H_GPP_S1                   0x050C0001
#define GPIO_VER1_H_GPP_S2                   0x050C0002
#define GPIO_VER1_H_GPP_S3                   0x050C0003
#define GPIO_VER1_H_GPP_S4                   0x050C0004
#define GPIO_VER1_H_GPP_S5                   0x050C0005
#define GPIO_VER1_H_GPP_S6                   0x050C0006
#define GPIO_VER1_H_GPP_S7                   0x050C0007

#define GPIO_VER1_H_GPD0                     0x050D0000
#define GPIO_VER1_H_GPD1                     0x050D0001
#define GPIO_VER1_H_GPD2                     0x050D0002
#define GPIO_VER1_H_GPD3                     0x050D0003
#define GPIO_VER1_H_GPD4                     0x050D0004
#define GPIO_VER1_H_GPD5                     0x050D0005
#define GPIO_VER1_H_GPD6                     0x050D0006
#define GPIO_VER1_H_GPD7                     0x050D0007
#define GPIO_VER1_H_GPD8                     0x050D0008
#define GPIO_VER1_H_GPD9                     0x050D0009
#define GPIO_VER1_H_GPD10                    0x050D000A
#define GPIO_VER1_H_GPD11                    0x050D000B
#define GPIO_VER1_H_INPUT3VSEL               0x050D000C
#define GPIO_VER1_H_SLP_LANB                 0x050D000D
#define GPIO_VER1_H_SLP_SUSB                 0x050D000E
#define GPIO_VER1_H_WAKEB                    0x050D000F
#define GPIO_VER1_H_DRAM_RESETB              0x050D0010

#define GPIO_VER1_H_VGPIO0                   0x050E0000
#define GPIO_VER1_H_VGPIO3                   0x050E0001
#define GPIO_VER1_H_VGPIO4                   0x050E0002
#define GPIO_VER1_H_VGPIO5                   0x050E0003
#define GPIO_VER1_H_VGPIO6                   0x050E0004
#define GPIO_VER1_H_VGPIO7                   0x050E0005
#define GPIO_VER1_H_VGPIO8                   0x050E0006
#define GPIO_VER1_H_VGPIO9                   0x050E0007
#define GPIO_VER1_H_VGPIO10                  0x050E0008
#define GPIO_VER1_H_VGPIO11                  0x050E0009
#define GPIO_VER1_H_VGPIO12                  0x050E000A
#define GPIO_VER1_H_VGPIO13                  0x050E000B
#define GPIO_VER1_H_VGPIO18                  0x050E000C
#define GPIO_VER1_H_VGPIO19                  0x050E000D
#define GPIO_VER1_H_VGPIO20                  0x050E000E
#define GPIO_VER1_H_VGPIO21                  0x050E000F
#define GPIO_VER1_H_VGPIO22                  0x050E0010
#define GPIO_VER1_H_VGPIO23                  0x050E0011
#define GPIO_VER1_H_VGPIO24                  0x050E0012
#define GPIO_VER1_H_VGPIO25                  0x050E0013
#define GPIO_VER1_H_VGPIO30                  0x050E0014
#define GPIO_VER1_H_VGPIO31                  0x050E0015
#define GPIO_VER1_H_VGPIO32                  0x050E0016
#define GPIO_VER1_H_VGPIO33                  0x050E0017
#define GPIO_VER1_H_VGPIO34                  0x050E0018
#define GPIO_VER1_H_VGPIO35                  0x050E0019
#define GPIO_VER1_H_VGPIO36                  0x050E001A
#define GPIO_VER1_H_VGPIO37                  0x050E001B
#define GPIO_VER1_H_VGPIO39                  0x050E001C

#define GPIO_VER1_H_VGPIO_USB_0              0x050F0000
#define GPIO_VER1_H_VGPIO_USB_1              0x050F0001
#define GPIO_VER1_H_VGPIO_USB_2              0x050F0002
#define GPIO_VER1_H_VGPIO_USB_3              0x050F0003
#define GPIO_VER1_H_VGPIO_USB_8              0x050F0004
#define GPIO_VER1_H_VGPIO_USB_9              0x050F0005
#define GPIO_VER1_H_VGPIO_USB_10             0x050F0006
#define GPIO_VER1_H_VGPIO_USB_11             0x050F0007

#define GPIO_VER1_H_VGPIO_PCIE_0             0x05100000
#define GPIO_VER1_H_VGPIO_PCIE_1             0x05100001
#define GPIO_VER1_H_VGPIO_PCIE_2             0x05100002
#define GPIO_VER1_H_VGPIO_PCIE_3             0x05100003
#define GPIO_VER1_H_VGPIO_PCIE_4             0x05100004
#define GPIO_VER1_H_VGPIO_PCIE_5             0x05100005
#define GPIO_VER1_H_VGPIO_PCIE_6             0x05100006
#define GPIO_VER1_H_VGPIO_PCIE_7             0x05100007
#define GPIO_VER1_H_VGPIO_PCIE_8             0x05100008
#define GPIO_VER1_H_VGPIO_PCIE_9             0x05100009
#define GPIO_VER1_H_VGPIO_PCIE_10            0x0510000A
#define GPIO_VER1_H_VGPIO_PCIE_11            0x0510000B
#define GPIO_VER1_H_VGPIO_PCIE_12            0x0510000C
#define GPIO_VER1_H_VGPIO_PCIE_13            0x0510000D
#define GPIO_VER1_H_VGPIO_PCIE_14            0x0510000E
#define GPIO_VER1_H_VGPIO_PCIE_15            0x0510000F
#define GPIO_VER1_H_VGPIO_PCIE_16            0x05100010
#define GPIO_VER1_H_VGPIO_PCIE_17            0x05100011
#define GPIO_VER1_H_VGPIO_PCIE_18            0x05100012
#define GPIO_VER1_H_VGPIO_PCIE_19            0x05100013
#define GPIO_VER1_H_VGPIO_PCIE_20            0x05100014
#define GPIO_VER1_H_VGPIO_PCIE_21            0x05100015
#define GPIO_VER1_H_VGPIO_PCIE_22            0x05100016
#define GPIO_VER1_H_VGPIO_PCIE_23            0x05100017
#define GPIO_VER1_H_VGPIO_PCIE_24            0x05100018
#define GPIO_VER1_H_VGPIO_PCIE_25            0x05100019
#define GPIO_VER1_H_VGPIO_PCIE_26            0x0510001A
#define GPIO_VER1_H_VGPIO_PCIE_27            0x0510001B
#define GPIO_VER1_H_VGPIO_PCIE_28            0x0510001C
#define GPIO_VER1_H_VGPIO_PCIE_29            0x0510001D
#define GPIO_VER1_H_VGPIO_PCIE_30            0x0510001E
#define GPIO_VER1_H_VGPIO_PCIE_31            0x0510001F
#define GPIO_VER1_H_VGPIO_PCIE_32            0x05100020
#define GPIO_VER1_H_VGPIO_PCIE_33            0x05100021
#define GPIO_VER1_H_VGPIO_PCIE_34            0x05100022
#define GPIO_VER1_H_VGPIO_PCIE_35            0x05100023
#define GPIO_VER1_H_VGPIO_PCIE_36            0x05100024
#define GPIO_VER1_H_VGPIO_PCIE_37            0x05100025
#define GPIO_VER1_H_VGPIO_PCIE_38            0x05100026
#define GPIO_VER1_H_VGPIO_PCIE_39            0x05100027
#define GPIO_VER1_H_VGPIO_PCIE_40            0x05100028
#define GPIO_VER1_H_VGPIO_PCIE_41            0x05100029
#define GPIO_VER1_H_VGPIO_PCIE_42            0x0510002A
#define GPIO_VER1_H_VGPIO_PCIE_43            0x0510002B
#define GPIO_VER1_H_VGPIO_PCIE_44            0x0510002C
#define GPIO_VER1_H_VGPIO_PCIE_45            0x0510002D
#define GPIO_VER1_H_VGPIO_PCIE_46            0x0510002E
#define GPIO_VER1_H_VGPIO_PCIE_47            0x0510002F
#define GPIO_VER1_H_VGPIO_PCIE_48            0x05100030
#define GPIO_VER1_H_VGPIO_PCIE_49            0x05100031
#define GPIO_VER1_H_VGPIO_PCIE_50            0x05100032
#define GPIO_VER1_H_VGPIO_PCIE_51            0x05100033
#define GPIO_VER1_H_VGPIO_PCIE_52            0x05100034
#define GPIO_VER1_H_VGPIO_PCIE_53            0x05100035
#define GPIO_VER1_H_VGPIO_PCIE_54            0x05100036
#define GPIO_VER1_H_VGPIO_PCIE_55            0x05100037
#define GPIO_VER1_H_VGPIO_PCIE_56            0x05100038
#define GPIO_VER1_H_VGPIO_PCIE_57            0x05100039
#define GPIO_VER1_H_VGPIO_PCIE_58            0x0510003A
#define GPIO_VER1_H_VGPIO_PCIE_59            0x0510003B
#define GPIO_VER1_H_VGPIO_PCIE_60            0x0510003C
#define GPIO_VER1_H_VGPIO_PCIE_61            0x0510003D
#define GPIO_VER1_H_VGPIO_PCIE_62            0x0510003E
#define GPIO_VER1_H_VGPIO_PCIE_63            0x0510003F
#define GPIO_VER1_H_VGPIO_PCIE_64            0x05100040
#define GPIO_VER1_H_VGPIO_PCIE_65            0x05100041
#define GPIO_VER1_H_VGPIO_PCIE_66            0x05100042
#define GPIO_VER1_H_VGPIO_PCIE_67            0x05100043
#define GPIO_VER1_H_VGPIO_PCIE_68            0x05100044
#define GPIO_VER1_H_VGPIO_PCIE_69            0x05100045
#define GPIO_VER1_H_VGPIO_PCIE_70            0x05100046
#define GPIO_VER1_H_VGPIO_PCIE_71            0x05100047
#define GPIO_VER1_H_VGPIO_PCIE_72            0x05100048
#define GPIO_VER1_H_VGPIO_PCIE_73            0x05100049
#define GPIO_VER1_H_VGPIO_PCIE_74            0x0510004A
#define GPIO_VER1_H_VGPIO_PCIE_75            0x0510004B
#define GPIO_VER1_H_VGPIO_PCIE_76            0x0510004C
#define GPIO_VER1_H_VGPIO_PCIE_77            0x0510004D
#define GPIO_VER1_H_VGPIO_PCIE_78            0x0510004E
#define GPIO_VER1_H_VGPIO_PCIE_79            0x0510004F
#define GPIO_VER1_H_VGPIO_PCIE_80            0x05100050
#define GPIO_VER1_H_VGPIO_PCIE_81            0x05100051
#define GPIO_VER1_H_VGPIO_PCIE_82            0x05100052
#define GPIO_VER1_H_VGPIO_PCIE_83            0x05100053

#define GPIO_VER1_H_SPI0_IO_2                0x05110000
#define GPIO_VER1_H_SPI0_IO_3                0x05110001
#define GPIO_VER1_H_SPI0_MOSI_IO_0           0x05110002
#define GPIO_VER1_H_SPI0_MISO_IO_1           0x05110003
#define GPIO_VER1_H_SPI0_TPM_CSB             0x05110004
#define GPIO_VER1_H_SPI0_FLASH_0_CSB         0x05110005
#define GPIO_VER1_H_SPI0_FLASH_1_CSB         0x05110006
#define GPIO_VER1_H_SPI0_CLK                 0x05110007
#define GPIO_VER1_H_SPI0_CLK_LOOPBK          0x05110008

#define GPIO_VER1_H_JTAG_TDO                 0x05120000
#define GPIO_VER1_H_JTAGX                    0x05120001
#define GPIO_VER1_H_PRDYB                    0x05120002
#define GPIO_VER1_H_PREQB                    0x05120003
#define GPIO_VER1_H_CPU_TRSTB                0x05120004
#define GPIO_VER1_H_JTAG_TDI                 0x05120005
#define GPIO_VER1_H_JTAG_TMS                 0x05120006
#define GPIO_VER1_H_JTAG_TCK                 0x05120007
#define GPIO_VER1_H_ITP_PMODE                0x05120008
#define GPIO_VER1_H_MLK                      0x05120009

#define GPIO_VER1_H_HDACPU_SDI               0x05130000
#define GPIO_VER1_H_HDACPU_SDO               0x05130001
#define GPIO_VER1_H_HDACPU_SCLK              0x05130002
#define GPIO_VER1_H_PM_SYNC                  0x05130003
#define GPIO_VER1_H_PECI                     0x05130004
#define GPIO_VER1_H_CPUPWRGD                 0x05130005
#define GPIO_VER1_H_THRMTRIPB                0x05130006
#define GPIO_VER1_H_PLTRST_CPUB              0x05130007
#define GPIO_VER1_H_PM_DOWN                  0x05130008
#define GPIO_VER1_H_TRIGGER_IN               0x05130009
#define GPIO_VER1_H_TRIGGER_OUT              0x0513000A
#define GPIO_VER1_H_CLKOUT_CPURTC            0x0513000B
#define GPIO_VER1_H_VCCST_OVERRIDE           0x0513000C
#define GPIO_VER1_H_C10_WAKE                 0x0513000D

//
// GPIO Pin Muxing
// Determines a selection of physical pad for a given signal.
// Please refer to GPIO_NATIVE_PAD type
//

//
// Serial IO UART0 Pin Muxing options
//
#define GPIO_VER1_H_MUXING_SERIALIO_UART0_RXD_GPP_C8         0x15020208
#define GPIO_VER1_H_MUXING_SERIALIO_UART0_RXD_GPP_J3         0x25090203
#define GPIO_VER1_H_MUXING_SERIALIO_UART0_TXD_GPP_C9         0x15021209
#define GPIO_VER1_H_MUXING_SERIALIO_UART0_TXD_GPP_J4         0x25091204
#define GPIO_VER1_H_MUXING_SERIALIO_UART0_RTS_GPP_C10        0x1502220A
#define GPIO_VER1_H_MUXING_SERIALIO_UART0_RTS_GPP_J2         0x25092202
#define GPIO_VER1_H_MUXING_SERIALIO_UART0_CTS_GPP_C11        0x1502320B
#define GPIO_VER1_H_MUXING_SERIALIO_UART0_CTS_GPP_J5         0x25093205

#endif // _GPIO_PINS_VER1_H_H_

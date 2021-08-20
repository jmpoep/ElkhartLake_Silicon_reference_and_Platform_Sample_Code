/** @file
  GPIO pins for ICL-PCH-LP,

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#ifndef _GPIO_PINS_VER1_LP_H_
#define _GPIO_PINS_VER1_LP_H_
///
/// This header file should be used together with
/// PCH GPIO lib in C and ASL. All defines used
/// must match both ASL/C syntax
///

///
/// Unique ID used in GpioPad defines
///
#define GPIO_VER1_LP_CHIPSET_ID      0x6

///
/// ICL LP GPIO Groups
/// Use below for functions from PCH GPIO Lib which
/// require GpioGroup as argument
///
#define GPIO_VER1_LP_GROUP_GPP_A  0x0600
#define GPIO_VER1_LP_GROUP_GPP_B  0x0601
#define GPIO_VER1_LP_GROUP_GPP_C  0x0602
#define GPIO_VER1_LP_GROUP_GPP_D  0x0603
#define GPIO_VER1_LP_GROUP_GPP_E  0x0604
#define GPIO_VER1_LP_GROUP_GPP_F  0x0605
#define GPIO_VER1_LP_GROUP_GPP_G  0x0606
#define GPIO_VER1_LP_GROUP_GPP_H  0x0607
#define GPIO_VER1_LP_GROUP_GPP_R  0x0608
#define GPIO_VER1_LP_GROUP_GPP_S  0x0609
#define GPIO_VER1_LP_GROUP_GPD    0x060A
#define GPIO_VER1_LP_GROUP_VGPIO  0x060B
#define GPIO_VER1_LP_GROUP_SPI    0x060C
#define GPIO_VER1_LP_GROUP_CPU    0x060D
#define GPIO_VER1_LP_GROUP_JTAG   0x060E
#define GPIO_VER1_LP_GROUP_HVCMOS 0x060F

///
/// ICL LP GPIO pins
/// Use below for functions from PCH GPIO Lib which
/// require GpioPad as argument. Encoding used here
/// has all information required by library functions
///
#define GPIO_VER1_LP_GPP_A0               0x06000000
#define GPIO_VER1_LP_GPP_A1               0x06000001
#define GPIO_VER1_LP_GPP_A2               0x06000002
#define GPIO_VER1_LP_GPP_A3               0x06000003
#define GPIO_VER1_LP_GPP_A4               0x06000004
#define GPIO_VER1_LP_GPP_A5               0x06000005
#define GPIO_VER1_LP_GPP_A6               0x06000006
#define GPIO_VER1_LP_GPP_A7               0x06000007
#define GPIO_VER1_LP_GPP_A8               0x06000008
#define GPIO_VER1_LP_GPP_A9               0x06000009
#define GPIO_VER1_LP_GPP_A10              0x0600000A
#define GPIO_VER1_LP_GPP_A11              0x0600000B
#define GPIO_VER1_LP_GPP_A12              0x0600000C
#define GPIO_VER1_LP_GPP_A13              0x0600000D
#define GPIO_VER1_LP_GPP_A14              0x0600000E
#define GPIO_VER1_LP_GPP_A15              0x0600000F
#define GPIO_VER1_LP_GPP_A16              0x06000010
#define GPIO_VER1_LP_GPP_A17              0x06000011
#define GPIO_VER1_LP_GPP_A18              0x06000012
#define GPIO_VER1_LP_GPP_A19              0x06000013
#define GPIO_VER1_LP_GPP_A20              0x06000014
#define GPIO_VER1_LP_GPP_A21              0x06000015
#define GPIO_VER1_LP_GPP_A22              0x06000016
#define GPIO_VER1_LP_GPP_A23              0x06000017
#define GPIO_VER1_LP_ESPI_CLK_LOOPBK      0x06000018

#define GPIO_VER1_LP_GPP_B0               0x06010000
#define GPIO_VER1_LP_GPP_B1               0x06010001
#define GPIO_VER1_LP_GPP_B2               0x06010002
#define GPIO_VER1_LP_GPP_B3               0x06010003
#define GPIO_VER1_LP_GPP_B4               0x06010004
#define GPIO_VER1_LP_GPP_B5               0x06010005
#define GPIO_VER1_LP_GPP_B6               0x06010006
#define GPIO_VER1_LP_GPP_B7               0x06010007
#define GPIO_VER1_LP_GPP_B8               0x06010008
#define GPIO_VER1_LP_GPP_B9               0x06010009
#define GPIO_VER1_LP_GPP_B10              0x0601000A
#define GPIO_VER1_LP_GPP_B11              0x0601000B
#define GPIO_VER1_LP_GPP_B12              0x0601000C
#define GPIO_VER1_LP_GPP_B13              0x0601000D
#define GPIO_VER1_LP_GPP_B14              0x0601000E
#define GPIO_VER1_LP_GPP_B15              0x0601000F
#define GPIO_VER1_LP_GPP_B16              0x06010010
#define GPIO_VER1_LP_GPP_B17              0x06010011
#define GPIO_VER1_LP_GPP_B18              0x06010012
#define GPIO_VER1_LP_GPP_B19              0x06010013
#define GPIO_VER1_LP_GPP_B20              0x06010014
#define GPIO_VER1_LP_GPP_B21              0x06010015
#define GPIO_VER1_LP_GPP_B22              0x06010016
#define GPIO_VER1_LP_GPP_B23              0x06010017
#define GPIO_VER1_LP_GSPI0_CLK_LOOPBK     0x06010018
#define GPIO_VER1_LP_GSPI1_CLK_LOOPBK     0x06010019

#define GPIO_VER1_LP_GPP_C0               0x06020000
#define GPIO_VER1_LP_GPP_C1               0x06020001
#define GPIO_VER1_LP_GPP_C2               0x06020002
#define GPIO_VER1_LP_GPP_C3               0x06020003
#define GPIO_VER1_LP_GPP_C4               0x06020004
#define GPIO_VER1_LP_GPP_C5               0x06020005
#define GPIO_VER1_LP_GPP_C6               0x06020006
#define GPIO_VER1_LP_GPP_C7               0x06020007
#define GPIO_VER1_LP_GPP_C8               0x06020008
#define GPIO_VER1_LP_GPP_C9               0x06020009
#define GPIO_VER1_LP_GPP_C10              0x0602000A
#define GPIO_VER1_LP_GPP_C11              0x0602000B
#define GPIO_VER1_LP_GPP_C12              0x0602000C
#define GPIO_VER1_LP_GPP_C13              0x0602000D
#define GPIO_VER1_LP_GPP_C14              0x0602000E
#define GPIO_VER1_LP_GPP_C15              0x0602000F
#define GPIO_VER1_LP_GPP_C16              0x06020010
#define GPIO_VER1_LP_GPP_C17              0x06020011
#define GPIO_VER1_LP_GPP_C18              0x06020012
#define GPIO_VER1_LP_GPP_C19              0x06020013
#define GPIO_VER1_LP_GPP_C20              0x06020014
#define GPIO_VER1_LP_GPP_C21              0x06020015
#define GPIO_VER1_LP_GPP_C22              0x06020016
#define GPIO_VER1_LP_GPP_C23              0x06020017

#define GPIO_VER1_LP_GPP_D0               0x06030000
#define GPIO_VER1_LP_GPP_D1               0x06030001
#define GPIO_VER1_LP_GPP_D2               0x06030002
#define GPIO_VER1_LP_GPP_D3               0x06030003
#define GPIO_VER1_LP_GPP_D4               0x06030004
#define GPIO_VER1_LP_GPP_D5               0x06030005
#define GPIO_VER1_LP_GPP_D6               0x06030006
#define GPIO_VER1_LP_GPP_D7               0x06030007
#define GPIO_VER1_LP_GPP_D8               0x06030008
#define GPIO_VER1_LP_GPP_D9               0x06030009
#define GPIO_VER1_LP_GPP_D10              0x0603000A
#define GPIO_VER1_LP_GPP_D11              0x0603000B
#define GPIO_VER1_LP_GPP_D12              0x0603000C
#define GPIO_VER1_LP_GPP_D13              0x0603000D
#define GPIO_VER1_LP_GPP_D14              0x0603000E
#define GPIO_VER1_LP_GPP_D15              0x0603000F
#define GPIO_VER1_LP_GPP_D16              0x06030010
#define GPIO_VER1_LP_GPP_D17              0x06030011
#define GPIO_VER1_LP_GPP_D18              0x06030012
#define GPIO_VER1_LP_GPP_D19              0x06030013
#define GPIO_VER1_LP_GSPI2_CLK_LOOPBK     0x06030014

#define GPIO_VER1_LP_GPP_E0               0x06040000
#define GPIO_VER1_LP_GPP_E1               0x06040001
#define GPIO_VER1_LP_GPP_E2               0x06040002
#define GPIO_VER1_LP_GPP_E3               0x06040003
#define GPIO_VER1_LP_GPP_E4               0x06040004
#define GPIO_VER1_LP_GPP_E5               0x06040005
#define GPIO_VER1_LP_GPP_E6               0x06040006
#define GPIO_VER1_LP_GPP_E7               0x06040007
#define GPIO_VER1_LP_GPP_E8               0x06040008
#define GPIO_VER1_LP_GPP_E9               0x06040009
#define GPIO_VER1_LP_GPP_E10              0x0604000A
#define GPIO_VER1_LP_GPP_E11              0x0604000B
#define GPIO_VER1_LP_GPP_E12              0x0604000C
#define GPIO_VER1_LP_GPP_E13              0x0604000D
#define GPIO_VER1_LP_GPP_E14              0x0604000E
#define GPIO_VER1_LP_GPP_E15              0x0604000F
#define GPIO_VER1_LP_GPP_E16              0x06040010
#define GPIO_VER1_LP_GPP_E17              0x06040011
#define GPIO_VER1_LP_GPP_E18              0x06040012
#define GPIO_VER1_LP_GPP_E19              0x06040013
#define GPIO_VER1_LP_GPP_E20              0x06040014
#define GPIO_VER1_LP_GPP_E21              0x06040015
#define GPIO_VER1_LP_GPP_E22              0x06040016
#define GPIO_VER1_LP_GPP_E23              0x06040017

#define GPIO_VER1_LP_GPP_F0               0x06050000
#define GPIO_VER1_LP_GPP_F1               0x06050001
#define GPIO_VER1_LP_GPP_F2               0x06050002
#define GPIO_VER1_LP_GPP_F3               0x06050003
#define GPIO_VER1_LP_GPP_F4               0x06050004
#define GPIO_VER1_LP_GPP_F5               0x06050005
#define GPIO_VER1_LP_GPP_F6               0x06050006
#define GPIO_VER1_LP_GPP_F7               0x06050007
#define GPIO_VER1_LP_GPP_F8               0x06050008
#define GPIO_VER1_LP_GPP_F9               0x06050009
#define GPIO_VER1_LP_GPP_F10              0x0605000A
#define GPIO_VER1_LP_GPP_F11              0x0605000B
#define GPIO_VER1_LP_GPP_F12              0x0605000C
#define GPIO_VER1_LP_GPP_F13              0x0605000D
#define GPIO_VER1_LP_GPP_F14              0x0605000E
#define GPIO_VER1_LP_GPP_F15              0x0605000F
#define GPIO_VER1_LP_GPP_F16              0x06050010
#define GPIO_VER1_LP_GPP_F17              0x06050011
#define GPIO_VER1_LP_GPP_F18              0x06050012
#define GPIO_VER1_LP_GPP_F19              0x06050013

#define GPIO_VER1_LP_GPP_G0               0x06060000
#define GPIO_VER1_LP_GPP_G1               0x06060001
#define GPIO_VER1_LP_GPP_G2               0x06060002
#define GPIO_VER1_LP_GPP_G3               0x06060003
#define GPIO_VER1_LP_GPP_G4               0x06060004
#define GPIO_VER1_LP_GPP_G5               0x06060005
#define GPIO_VER1_LP_GPP_G6               0x06060006
#define GPIO_VER1_LP_GPP_G7               0x06060007

#define GPIO_VER1_LP_GPP_H0               0x06070000
#define GPIO_VER1_LP_GPP_H1               0x06070001
#define GPIO_VER1_LP_GPP_H2               0x06070002
#define GPIO_VER1_LP_GPP_H3               0x06070003
#define GPIO_VER1_LP_GPP_H4               0x06070004
#define GPIO_VER1_LP_GPP_H5               0x06070005
#define GPIO_VER1_LP_GPP_H6               0x06070006
#define GPIO_VER1_LP_GPP_H7               0x06070007
#define GPIO_VER1_LP_GPP_H8               0x06070008
#define GPIO_VER1_LP_GPP_H9               0x06070009
#define GPIO_VER1_LP_GPP_H10              0x0607000A
#define GPIO_VER1_LP_GPP_H11              0x0607000B
#define GPIO_VER1_LP_GPP_H12              0x0607000C
#define GPIO_VER1_LP_GPP_H13              0x0607000D
#define GPIO_VER1_LP_GPP_H14              0x0607000E
#define GPIO_VER1_LP_GPP_H15              0x0607000F
#define GPIO_VER1_LP_GPP_H16              0x06070010
#define GPIO_VER1_LP_GPP_H17              0x06070011
#define GPIO_VER1_LP_GPP_H18              0x06070012
#define GPIO_VER1_LP_GPP_H19              0x06070013
#define GPIO_VER1_LP_GPP_H20              0x06070014
#define GPIO_VER1_LP_GPP_H21              0x06070015
#define GPIO_VER1_LP_GPP_H22              0x06070016
#define GPIO_VER1_LP_GPP_H23              0x06070017

#define GPIO_VER1_LP_GPP_R0               0x06080000
#define GPIO_VER1_LP_GPP_R1               0x06080001
#define GPIO_VER1_LP_GPP_R2               0x06080002
#define GPIO_VER1_LP_GPP_R3               0x06080003
#define GPIO_VER1_LP_GPP_R4               0x06080004
#define GPIO_VER1_LP_GPP_R5               0x06080005
#define GPIO_VER1_LP_GPP_R6               0x06080006
#define GPIO_VER1_LP_GPP_R7               0x06080007

#define GPIO_VER1_LP_GPP_S0               0x06090000
#define GPIO_VER1_LP_GPP_S1               0x06090001
#define GPIO_VER1_LP_GPP_S2               0x06090002
#define GPIO_VER1_LP_GPP_S3               0x06090003
#define GPIO_VER1_LP_GPP_S4               0x06090004
#define GPIO_VER1_LP_GPP_S5               0x06090005
#define GPIO_VER1_LP_GPP_S6               0x06090006
#define GPIO_VER1_LP_GPP_S7               0x06090007

#define GPIO_VER1_LP_GPD0                 0x060A0000
#define GPIO_VER1_LP_GPD1                 0x060A0001
#define GPIO_VER1_LP_GPD2                 0x060A0002
#define GPIO_VER1_LP_GPD3                 0x060A0003
#define GPIO_VER1_LP_GPD4                 0x060A0004
#define GPIO_VER1_LP_GPD5                 0x060A0005
#define GPIO_VER1_LP_GPD6                 0x060A0006
#define GPIO_VER1_LP_GPD7                 0x060A0007
#define GPIO_VER1_LP_GPD8                 0x060A0008
#define GPIO_VER1_LP_GPD9                 0x060A0009
#define GPIO_VER1_LP_GPD10                0x060A000A
#define GPIO_VER1_LP_GPD11                0x060A000B
#define GPIO_VER1_LP_INPUT3VSEL           0x060A000C
#define GPIO_VER1_LP_SLP_LANB             0x060A000D
#define GPIO_VER1_LP_SLP_SUSB             0x060A000E
#define GPIO_VER1_LP_SLP_WAKEB            0x060A000F
#define GPIO_VER1_LP_SLP_DRAM_RESETB      0x060A0010

#define GPIO_VER1_LP_VGPIO0               0x060B0000
#define GPIO_VER1_LP_VGPIO3               0x060B0001
#define GPIO_VER1_LP_VGPIO4               0x060B0002
#define GPIO_VER1_LP_VGPIO5               0x060B0003
#define GPIO_VER1_LP_VGPIO6               0x060B0004
#define GPIO_VER1_LP_VGPIO7               0x060B0005
#define GPIO_VER1_LP_VGPIO8               0x060B0006
#define GPIO_VER1_LP_VGPIO9               0x060B0007
#define GPIO_VER1_LP_VGPIO10              0x060B0008
#define GPIO_VER1_LP_VGPIO11              0x060B0009
#define GPIO_VER1_LP_VGPIO12              0x060B000A
#define GPIO_VER1_LP_VGPIO13              0x060B000B
#define GPIO_VER1_LP_VGPIO18              0x060B000C
#define GPIO_VER1_LP_VGPIO19              0x060B000D
#define GPIO_VER1_LP_VGPIO20              0x060B000E
#define GPIO_VER1_LP_VGPIO21              0x060B000F
#define GPIO_VER1_LP_VGPIO22              0x060B0010
#define GPIO_VER1_LP_VGPIO23              0x060B0011
#define GPIO_VER1_LP_VGPIO24              0x060B0012
#define GPIO_VER1_LP_VGPIO25              0x060B0013
#define GPIO_VER1_LP_VGPIO30              0x060B0014
#define GPIO_VER1_LP_VGPIO31              0x060B0015
#define GPIO_VER1_LP_VGPIO32              0x060B0016
#define GPIO_VER1_LP_VGPIO33              0x060B0017
#define GPIO_VER1_LP_VGPIO34              0x060B0018
#define GPIO_VER1_LP_VGPIO35              0x060B0019
#define GPIO_VER1_LP_VGPIO36              0x060B001A
#define GPIO_VER1_LP_VGPIO37              0x060B001B
#define GPIO_VER1_LP_VGPIO39              0x060B001C

#define GPIO_VER1_LP_SPI0_IO_2            0x060C0000
#define GPIO_VER1_LP_SPI0_IO_3            0x060C0001
#define GPIO_VER1_LP_SPI0_MOSI_IO_0       0x060C0002
#define GPIO_VER1_LP_SPI0_MOSI_IO_1       0x060C0003
#define GPIO_VER1_LP_SPI0_TPM_CSB         0x060C0004
#define GPIO_VER1_LP_SPI0_FLASH_0_CSB     0x060C0005
#define GPIO_VER1_LP_SPI0_FLASH_1_CSB     0x060C0006
#define GPIO_VER1_LP_SPI0_CLK             0x060C0007
#define GPIO_VER1_LP_SPI0_CLK_LOOPBK      0x060C0008

#define GPIO_VER1_LP_HDACPU_SDI           0x060D0000
#define GPIO_VER1_LP_HDACPU_SDO           0x060D0001
#define GPIO_VER1_LP_HDACPU_SCLK          0x060D0002
#define GPIO_VER1_LP_PM_SYNC              0x060D0003
#define GPIO_VER1_LP_PECI                 0x060D0004
#define GPIO_VER1_LP_CPUPWRGD             0x060D0005
#define GPIO_VER1_LP_THRMTRIPB            0x060D0006
#define GPIO_VER1_LP_PLTRST_CPUB          0x060D0007
#define GPIO_VER1_LP_PM_DOWN              0x060D0008
#define GPIO_VER1_LP_TRIGGER_IN           0x060D0009
#define GPIO_VER1_LP_TRIGGER_OUT          0x060D000A
#define GPIO_VER1_LP_UFS_RESETB           0x060D000B
#define GPIO_VER1_LP_CLKOUT_CPURTC        0x060D000C
#define GPIO_VER1_LP_VCCST_PWRGD          0x060D000D
#define GPIO_VER1_LP_C10_WAKE             0x060D000E

#define GPIO_VER1_LP_JTAG_TDO             0x060E0000
#define GPIO_VER1_LP_JTAGX                0x060E0001
#define GPIO_VER1_LP_PRDYB                0x060E0002
#define GPIO_VER1_LP_PREQB                0x060E0003
#define GPIO_VER1_LP_CPU_TRSTB            0x060E0004
#define GPIO_VER1_LP_JTAG_TDI             0x060E0005
#define GPIO_VER1_LP_JTAG_TMS             0x060E0006
#define GPIO_VER1_LP_JTAG_TCK             0x060E0007
#define GPIO_VER1_LP_ITP_PMODE            0x060E0008

#define GPIO_VER1_LP_HVCMOS_L_BKLTEN      0x060F0000
#define GPIO_VER1_LP_HVCMOS_L_BKLTCTL     0x060F0001
#define GPIO_VER1_LP_HVCMOS_L_VDDEN       0x060F0002
#define GPIO_VER1_LP_HVCMOS_SYS_PWROK     0x060F0003
#define GPIO_VER1_LP_HVCMOS_SYS_RESETB    0x060F0004
#define GPIO_VER1_LP_HVCMOS_MLK_RSTB      0x060F0005

//
// GPIO Pin Muxing
// Determines a selection of physical pad for a given signal.
// Please refer to GPIO_NATIVE_PAD type
//

//
// Serial IO UART0 Pin Muxing options
//
#define GPIO_VER1_LP_MUXING_SERIALIO_UART0_RXD_GPP_C8        0x16020208
#define GPIO_VER1_LP_MUXING_SERIALIO_UART0_RXD_GPP_F1        0x26050201
#define GPIO_VER1_LP_MUXING_SERIALIO_UART0_TXD_GPP_C9        0x16021209
#define GPIO_VER1_LP_MUXING_SERIALIO_UART0_TXD_GPP_F2        0x26051202
#define GPIO_VER1_LP_MUXING_SERIALIO_UART0_RTS_GPP_C10       0x1602220A
#define GPIO_VER1_LP_MUXING_SERIALIO_UART0_RTS_GPP_F0        0x26052200
#define GPIO_VER1_LP_MUXING_SERIALIO_UART0_CTS_GPP_C11       0x1602320B
#define GPIO_VER1_LP_MUXING_SERIALIO_UART0_CTS_GPP_F3        0x26053203

//
// CNVi Pin Muxing options
//
#define GPIO_VER1_LP_MUXING_CNVI_RF_RESET_GPP_A8             0x2640E408
#define GPIO_VER1_LP_MUXING_CNVI_RF_RESET_GPP_F4             0x1645E404
#define GPIO_VER1_LP_MUXING_CNVI_MODEM_CLKREQ_GPP_A9         0x2640E609
#define GPIO_VER1_LP_MUXING_CNVI_MODEM_CLKREQ_GPP_F5         0x2645E605

#endif // _GPIO_PINS_VER1_LP_H_

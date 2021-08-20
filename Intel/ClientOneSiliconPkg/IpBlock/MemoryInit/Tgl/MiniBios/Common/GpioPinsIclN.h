/** @file
  GPIO pins for ICL-PCH-N,

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
#ifndef _GPIO_PINS_ICL_N_H_
#define _GPIO_PINS_ICL_N_H_
///
/// This header file should be used together with
/// PCH GPIO lib in C and ASL. All defines used
/// must match both ASL/C syntax
///

///
/// Unique ID used in GpioPad defines
///
#define GPIO_ICL_N_CHIPSET_ID     0x7

///
/// ICL N GPIO Groups
/// Use below for functions from PCH GPIO Lib which
/// require GpioGroup as argument
///
#define GPIO_ICL_N_GROUP_GPP_A    0x0700
#define GPIO_ICL_N_GROUP_GPP_B    0x0701
#define GPIO_ICL_N_GROUP_GPP_C    0x0702
#define GPIO_ICL_N_GROUP_GPP_D    0x0703
#define GPIO_ICL_N_GROUP_GPP_E    0x0704
#define GPIO_ICL_N_GROUP_GPP_G    0x0705
#define GPIO_ICL_N_GROUP_GPP_H    0x0706
#define GPIO_ICL_N_GROUP_GPP_R    0x0707
#define GPIO_ICL_N_GROUP_GPP_S    0x0708
#define GPIO_ICL_N_GROUP_GPD      0x0709
#define GPIO_ICL_N_GROUP_VGPIO    0x070A
#define GPIO_ICL_N_GROUP_VGPIO_3  0x070B
#define GPIO_ICL_N_GROUP_VGPIO_4  0x070C
#define GPIO_ICL_N_GROUP_SPI      0x070E
#define GPIO_ICL_N_GROUP_CPU      0x070E
#define GPIO_ICL_N_GROUP_JTAG     0x070F
#define GPIO_ICL_N_GROUP_HVCMOS   0x0710

///
/// ICL LP GPIO pins
/// Use below for functions from PCH GPIO Lib which
/// require GpioPad as argument. Encoding used here
/// has all information required by library functions
///
#define GPIO_ICL_N_GPP_A0               0x07000000
#define GPIO_ICL_N_GPP_A1               0x07000001
#define GPIO_ICL_N_GPP_A2               0x07000002
#define GPIO_ICL_N_GPP_A3               0x07000003
#define GPIO_ICL_N_GPP_A4               0x07000004
#define GPIO_ICL_N_GPP_A5               0x07000005
#define GPIO_ICL_N_GPP_A6               0x07000006
#define GPIO_ICL_N_GPP_A7               0x07000007
#define GPIO_ICL_N_GPP_A8               0x07000008
#define GPIO_ICL_N_GPP_A9               0x07000009
#define GPIO_ICL_N_GPP_A10              0x0700000A
#define GPIO_ICL_N_GPP_A11              0x0700000B
#define GPIO_ICL_N_GPP_A12              0x0700000C
#define GPIO_ICL_N_GPP_A13              0x0700000D
#define GPIO_ICL_N_GPP_A14              0x0700000E
#define GPIO_ICL_N_GPP_A15              0x0700000F
#define GPIO_ICL_N_GPP_A16              0x07000010
#define GPIO_ICL_N_GPP_A17              0x07000011
#define GPIO_ICL_N_GPP_A18              0x07000012
#define GPIO_ICL_N_GPP_A19              0x07000013
#define GPIO_ICL_N_ESPI_CLK_LOOPBK      0x07000014

#define GPIO_ICL_N_GPP_B0               0x07010000
#define GPIO_ICL_N_GPP_B1               0x07010001
#define GPIO_ICL_N_GPP_B2               0x07010002
#define GPIO_ICL_N_GPP_B3               0x07010003
#define GPIO_ICL_N_GPP_B4               0x07010004
#define GPIO_ICL_N_GPP_B5               0x07010005
#define GPIO_ICL_N_GPP_B6               0x07010006
#define GPIO_ICL_N_GPP_B7               0x07010007
#define GPIO_ICL_N_GPP_B8               0x07010008
#define GPIO_ICL_N_GPP_B9               0x07010009
#define GPIO_ICL_N_GPP_B10              0x0701000A
#define GPIO_ICL_N_GPP_B11              0x0701000B
#define GPIO_ICL_N_GPP_B12              0x0701000C
#define GPIO_ICL_N_GPP_B13              0x0701000D
#define GPIO_ICL_N_GPP_B14              0x0701000E
#define GPIO_ICL_N_GPP_B15              0x0701000F
#define GPIO_ICL_N_GPP_B16              0x07010010
#define GPIO_ICL_N_GPP_B17              0x07010011
#define GPIO_ICL_N_GPP_B18              0x07010012
#define GPIO_ICL_N_GPP_B19              0x07010013
#define GPIO_ICL_N_GPP_B20              0x07010014
#define GPIO_ICL_N_GPP_B21              0x07010015
#define GPIO_ICL_N_GPP_B22              0x07010016
#define GPIO_ICL_N_GPP_B23              0x07010017
#define GPIO_ICL_N_GSPI0_CLK_LOOPBK     0x07010018
#define GPIO_ICL_N_GSPI1_CLK_LOOPBK     0x07010019

#define GPIO_ICL_N_GPP_C0               0x07020000
#define GPIO_ICL_N_GPP_C1               0x07020001
#define GPIO_ICL_N_GPP_C2               0x07020002
#define GPIO_ICL_N_GPP_C3               0x07020003
#define GPIO_ICL_N_GPP_C4               0x07020004
#define GPIO_ICL_N_GPP_C5               0x07020005
#define GPIO_ICL_N_GPP_C6               0x07020006
#define GPIO_ICL_N_GPP_C7               0x07020007
#define GPIO_ICL_N_GPP_C8               0x07020008
#define GPIO_ICL_N_GPP_C9               0x07020009
#define GPIO_ICL_N_GPP_C10              0x0702000A
#define GPIO_ICL_N_GPP_C11              0x0702000B
#define GPIO_ICL_N_GPP_C12              0x0702000C
#define GPIO_ICL_N_GPP_C13              0x0702000D
#define GPIO_ICL_N_GPP_C14              0x0702000E
#define GPIO_ICL_N_GPP_C15              0x0702000F
#define GPIO_ICL_N_GPP_C16              0x07020010
#define GPIO_ICL_N_GPP_C17              0x07020011
#define GPIO_ICL_N_GPP_C18              0x07020012
#define GPIO_ICL_N_GPP_C19              0x07020013
#define GPIO_ICL_N_GPP_C20              0x07020014
#define GPIO_ICL_N_GPP_C21              0x07020015
#define GPIO_ICL_N_GPP_C22              0x07020016
#define GPIO_ICL_N_GPP_C23              0x07020017

#define GPIO_ICL_N_GPP_D0               0x07030000
#define GPIO_ICL_N_GPP_D1               0x07030001
#define GPIO_ICL_N_GPP_D2               0x07030002
#define GPIO_ICL_N_GPP_D3               0x07030003
#define GPIO_ICL_N_GPP_D4               0x07030004
#define GPIO_ICL_N_GPP_D5               0x07030005
#define GPIO_ICL_N_GPP_D6               0x07030006
#define GPIO_ICL_N_GPP_D7               0x07030007
#define GPIO_ICL_N_GPP_D8               0x07030008
#define GPIO_ICL_N_GPP_D9               0x07030009
#define GPIO_ICL_N_GPP_D10              0x0703000A
#define GPIO_ICL_N_GPP_D11              0x0703000B
#define GPIO_ICL_N_GPP_D12              0x0703000C
#define GPIO_ICL_N_GPP_D13              0x0703000D
#define GPIO_ICL_N_GPP_D14              0x0703000E
#define GPIO_ICL_N_GPP_D15              0x0703000F
#define GPIO_ICL_N_GPP_D16              0x07030010
#define GPIO_ICL_N_GPP_D17              0x07030011
#define GPIO_ICL_N_GPP_D18              0x07030012
#define GPIO_ICL_N_GPP_D19              0x07030013
#define GPIO_ICL_N_GPP_D20              0x07030014
#define GPIO_ICL_N_GPP_D21              0x07030015
#define GPIO_ICL_N_GPP_D22              0x07030016
#define GPIO_ICL_N_GPP_D23              0x07030017
#define GPIO_ICL_N_GSPI2_CLK_LOOPBK     0x07030018
#define GPIO_ICL_N_SPI1_CLK_LOOPBK      0x07030019

#define GPIO_ICL_N_GPP_E0               0x07040000
#define GPIO_ICL_N_GPP_E1               0x07040001
#define GPIO_ICL_N_GPP_E2               0x07040002
#define GPIO_ICL_N_GPP_E3               0x07040003
#define GPIO_ICL_N_GPP_E4               0x07040004
#define GPIO_ICL_N_GPP_E5               0x07040005
#define GPIO_ICL_N_GPP_E6               0x07040006
#define GPIO_ICL_N_GPP_E7               0x07040007
#define GPIO_ICL_N_GPP_E8               0x07040008
#define GPIO_ICL_N_GPP_E9               0x07040009
#define GPIO_ICL_N_GPP_E10              0x0704000A
#define GPIO_ICL_N_GPP_E11              0x0704000B
#define GPIO_ICL_N_GPP_E12              0x0704000C
#define GPIO_ICL_N_GPP_E13              0x0704000D
#define GPIO_ICL_N_GPP_E14              0x0704000E
#define GPIO_ICL_N_GPP_E15              0x0704000F
#define GPIO_ICL_N_GPP_E16              0x07040010
#define GPIO_ICL_N_GPP_E17              0x07040011
#define GPIO_ICL_N_GPP_E18              0x07040012
#define GPIO_ICL_N_GPP_E19              0x07040013
#define GPIO_ICL_N_GPP_E20              0x07040014
#define GPIO_ICL_N_GPP_E21              0x07040015
#define GPIO_ICL_N_GPP_E22              0x07040016
#define GPIO_ICL_N_GPP_E23              0x07040017

#define GPIO_ICL_N_GPP_G0               0x07050000
#define GPIO_ICL_N_GPP_G1               0x07050001
#define GPIO_ICL_N_GPP_G2               0x07050002
#define GPIO_ICL_N_GPP_G3               0x07050003
#define GPIO_ICL_N_GPP_G4               0x07050004
#define GPIO_ICL_N_GPP_G5               0x07050005
#define GPIO_ICL_N_GPP_G6               0x07050006
#define GPIO_ICL_N_GPP_G7               0x07050007

#define GPIO_ICL_N_GPP_H0               0x07060000
#define GPIO_ICL_N_GPP_H1               0x07060001
#define GPIO_ICL_N_GPP_H2               0x07060002
#define GPIO_ICL_N_GPP_H3               0x07060003
#define GPIO_ICL_N_GPP_H4               0x07060004
#define GPIO_ICL_N_GPP_H5               0x07060005
#define GPIO_ICL_N_GPP_H6               0x07060006
#define GPIO_ICL_N_GPP_H7               0x07060007
#define GPIO_ICL_N_GPP_H8               0x07060008
#define GPIO_ICL_N_GPP_H9               0x07060009
#define GPIO_ICL_N_GPP_H10              0x0706000A
#define GPIO_ICL_N_GPP_H11              0x0706000B
#define GPIO_ICL_N_GPP_H12              0x0706000C
#define GPIO_ICL_N_GPP_H13              0x0706000D
#define GPIO_ICL_N_GPP_H14              0x0706000E
#define GPIO_ICL_N_GPP_H15              0x0706000F
#define GPIO_ICL_N_GPP_H16              0x07060010
#define GPIO_ICL_N_GPP_H17              0x07060011
#define GPIO_ICL_N_GPP_H18              0x07060012
#define GPIO_ICL_N_GPP_H19              0x07060013
#define GPIO_ICL_N_GPP_H20              0x07060014
#define GPIO_ICL_N_GPP_H21              0x07060015
#define GPIO_ICL_N_GPP_H22              0x07060016
#define GPIO_ICL_N_GPP_H23              0x07060017

#define GPIO_ICL_N_GPP_R0               0x07070000
#define GPIO_ICL_N_GPP_R1               0x07070001
#define GPIO_ICL_N_GPP_R2               0x07070002
#define GPIO_ICL_N_GPP_R3               0x07070003
#define GPIO_ICL_N_GPP_R4               0x07070004
#define GPIO_ICL_N_GPP_R5               0x07070005
#define GPIO_ICL_N_GPP_R6               0x07070006
#define GPIO_ICL_N_GPP_R7               0x07070007

#define GPIO_ICL_N_GPP_S0               0x07080000
#define GPIO_ICL_N_GPP_S1               0x07080001
#define GPIO_ICL_N_GPP_S2               0x07080002
#define GPIO_ICL_N_GPP_S3               0x07080003
#define GPIO_ICL_N_GPP_S4               0x07080004
#define GPIO_ICL_N_GPP_S5               0x07080005
#define GPIO_ICL_N_GPP_S6               0x07080006
#define GPIO_ICL_N_GPP_S7               0x07080007

#define GPIO_ICL_N_GPD0                 0x07090000
#define GPIO_ICL_N_GPD1                 0x07090001
#define GPIO_ICL_N_GPD2                 0x07090002
#define GPIO_ICL_N_GPD3                 0x07090003
#define GPIO_ICL_N_GPD4                 0x07090004
#define GPIO_ICL_N_GPD5                 0x07090005
#define GPIO_ICL_N_GPD6                 0x07090006
#define GPIO_ICL_N_GPD7                 0x07090007
#define GPIO_ICL_N_GPD8                 0x07090008
#define GPIO_ICL_N_GPD9                 0x07090009
#define GPIO_ICL_N_GPD10                0x0709000A
#define GPIO_ICL_N_INPUT3VSEL           0x0709000B
#define GPIO_ICL_N_SLP_SUSB             0x0709000C
#define GPIO_ICL_N_SLP_WAKEB            0x0709000D
#define GPIO_ICL_N_SLP_DRAM_RESETB      0x0709000E

#define GPIO_ICL_N_VGPIO0               0x070A0000
#define GPIO_ICL_N_VGPIO3               0x070A0001
#define GPIO_ICL_N_VGPIO4               0x070A0002
#define GPIO_ICL_N_VGPIO5               0x070A0003
#define GPIO_ICL_N_VGPIO6               0x070A0004
#define GPIO_ICL_N_VGPIO7               0x070A0005
#define GPIO_ICL_N_VGPIO8               0x070A0006
#define GPIO_ICL_N_VGPIO9               0x070A0007
#define GPIO_ICL_N_VGPIO10              0x070A0008
#define GPIO_ICL_N_VGPIO11              0x070A0009
#define GPIO_ICL_N_VGPIO12              0x070A000A
#define GPIO_ICL_N_VGPIO13              0x070A000B
#define GPIO_ICL_N_VGPIO18              0x070A000C
#define GPIO_ICL_N_VGPIO19              0x070A000D
#define GPIO_ICL_N_VGPIO20              0x070A000E
#define GPIO_ICL_N_VGPIO21              0x070A000F
#define GPIO_ICL_N_VGPIO22              0x070A0010
#define GPIO_ICL_N_VGPIO23              0x070A0011
#define GPIO_ICL_N_VGPIO24              0x070A0012
#define GPIO_ICL_N_VGPIO25              0x070A0013
#define GPIO_ICL_N_VGPIO30              0x070A0014
#define GPIO_ICL_N_VGPIO31              0x070A0015
#define GPIO_ICL_N_VGPIO32              0x070A0016
#define GPIO_ICL_N_VGPIO33              0x070A0017
#define GPIO_ICL_N_VGPIO34              0x070A0018
#define GPIO_ICL_N_VGPIO35              0x070A0019
#define GPIO_ICL_N_VGPIO36              0x070A001A
#define GPIO_ICL_N_VGPIO37              0x070A001B
#define GPIO_ICL_N_VGPIO39              0x070A001C

#define GPIO_ICL_N_VGPIO_PCIE_0         0x070B0000
#define GPIO_ICL_N_VGPIO_PCIE_1         0x070B0001
#define GPIO_ICL_N_VGPIO_PCIE_2         0x070B0002
#define GPIO_ICL_N_VGPIO_PCIE_3         0x070B0003
#define GPIO_ICL_N_VGPIO_PCIE_4         0x070B0004
#define GPIO_ICL_N_VGPIO_PCIE_5         0x070B0005
#define GPIO_ICL_N_VGPIO_PCIE_6         0x070B0006
#define GPIO_ICL_N_VGPIO_PCIE_7         0x070B0007
#define GPIO_ICL_N_VGPIO_PCIE_8         0x070B0008
#define GPIO_ICL_N_VGPIO_PCIE_9         0x070B0009
#define GPIO_ICL_N_VGPIO_PCIE_10        0x070B000A
#define GPIO_ICL_N_VGPIO_PCIE_11        0x070B000B
#define GPIO_ICL_N_VGPIO_PCIE_12        0x070B000C
#define GPIO_ICL_N_VGPIO_PCIE_13        0x070B000D
#define GPIO_ICL_N_VGPIO_PCIE_14        0x070B000E
#define GPIO_ICL_N_VGPIO_PCIE_15        0x070B000F
#define GPIO_ICL_N_VGPIO_PCIE_16        0x070B0010
#define GPIO_ICL_N_VGPIO_PCIE_17        0x070B0011
#define GPIO_ICL_N_VGPIO_PCIE_18        0x070B0012
#define GPIO_ICL_N_VGPIO_PCIE_19        0x070B0013
#define GPIO_ICL_N_VGPIO_PCIE_20        0x070B0014
#define GPIO_ICL_N_VGPIO_PCIE_21        0x070B0015
#define GPIO_ICL_N_VGPIO_PCIE_22        0x070B0016
#define GPIO_ICL_N_VGPIO_PCIE_23        0x070B0017
#define GPIO_ICL_N_VGPIO_PCIE_24        0x070B0018
#define GPIO_ICL_N_VGPIO_PCIE_25        0x070B0019
#define GPIO_ICL_N_VGPIO_PCIE_26        0x070B001A
#define GPIO_ICL_N_VGPIO_PCIE_27        0x070B001B
#define GPIO_ICL_N_VGPIO_PCIE_28        0x070B001C
#define GPIO_ICL_N_VGPIO_PCIE_29        0x070B001D
#define GPIO_ICL_N_VGPIO_PCIE_30        0x070B001E
#define GPIO_ICL_N_VGPIO_PCIE_31        0x070B001F
#define GPIO_ICL_N_VGPIO_PCIE_32        0x070B0020
#define GPIO_ICL_N_VGPIO_PCIE_33        0x070B0021
#define GPIO_ICL_N_VGPIO_PCIE_34        0x070B0022
#define GPIO_ICL_N_VGPIO_PCIE_35        0x070B0023
#define GPIO_ICL_N_VGPIO_PCIE_36        0x070B0024
#define GPIO_ICL_N_VGPIO_PCIE_37        0x070B0025
#define GPIO_ICL_N_VGPIO_PCIE_38        0x070B0026
#define GPIO_ICL_N_VGPIO_PCIE_39        0x070B0027
#define GPIO_ICL_N_VGPIO_PCIE_40        0x070B0028
#define GPIO_ICL_N_VGPIO_PCIE_41        0x070B0029
#define GPIO_ICL_N_VGPIO_PCIE_42        0x070B002A
#define GPIO_ICL_N_VGPIO_PCIE_43        0x070B002B
#define GPIO_ICL_N_VGPIO_PCIE_44        0x070B002C
#define GPIO_ICL_N_VGPIO_PCIE_45        0x070B002D
#define GPIO_ICL_N_VGPIO_PCIE_46        0x070B002E
#define GPIO_ICL_N_VGPIO_PCIE_47        0x070B002F
#define GPIO_ICL_N_VGPIO_PCIE_48        0x070B0030
#define GPIO_ICL_N_VGPIO_PCIE_49        0x070B0031
#define GPIO_ICL_N_VGPIO_PCIE_50        0x070B0032
#define GPIO_ICL_N_VGPIO_PCIE_51        0x070B0033
#define GPIO_ICL_N_VGPIO_PCIE_52        0x070B0034
#define GPIO_ICL_N_VGPIO_PCIE_53        0x070B0035
#define GPIO_ICL_N_VGPIO_PCIE_54        0x070B0036
#define GPIO_ICL_N_VGPIO_PCIE_55        0x070B0037
#define GPIO_ICL_N_VGPIO_PCIE_56        0x070B0038
#define GPIO_ICL_N_VGPIO_PCIE_57        0x070B0039
#define GPIO_ICL_N_VGPIO_PCIE_58        0x070B003A
#define GPIO_ICL_N_VGPIO_PCIE_59        0x070B003B
#define GPIO_ICL_N_VGPIO_PCIE_60        0x070B003C
#define GPIO_ICL_N_VGPIO_PCIE_61        0x070B003D
#define GPIO_ICL_N_VGPIO_PCIE_62        0x070B003E
#define GPIO_ICL_N_VGPIO_PCIE_63        0x070B003F
#define GPIO_ICL_N_VGPIO_PCIE_64        0x070B0040
#define GPIO_ICL_N_VGPIO_PCIE_65        0x070B0041
#define GPIO_ICL_N_VGPIO_PCIE_66        0x070B0042
#define GPIO_ICL_N_VGPIO_PCIE_67        0x070B0043
#define GPIO_ICL_N_VGPIO_PCIE_68        0x070B0044
#define GPIO_ICL_N_VGPIO_PCIE_69        0x070B0045
#define GPIO_ICL_N_VGPIO_PCIE_70        0x070B0046
#define GPIO_ICL_N_VGPIO_PCIE_71        0x070B0047
#define GPIO_ICL_N_VGPIO_PCIE_72        0x070B0048
#define GPIO_ICL_N_VGPIO_PCIE_73        0x070B0049
#define GPIO_ICL_N_VGPIO_PCIE_74        0x070B004A
#define GPIO_ICL_N_VGPIO_PCIE_75        0x070B004B
#define GPIO_ICL_N_VGPIO_PCIE_76        0x070B004C
#define GPIO_ICL_N_VGPIO_PCIE_77        0x070B004D
#define GPIO_ICL_N_VGPIO_PCIE_78        0x070B004E
#define GPIO_ICL_N_VGPIO_PCIE_79        0x070B004F
#define GPIO_ICL_N_VGPIO_USB_0          0x070B0050
#define GPIO_ICL_N_VGPIO_USB_1          0x070B0051
#define GPIO_ICL_N_VGPIO_USB_2          0x070B0052
#define GPIO_ICL_N_VGPIO_USB_3          0x070B0053
#define GPIO_ICL_N_VGPIO_USB_4          0x070B0054
#define GPIO_ICL_N_VGPIO_USB_5          0x070B0055
#define GPIO_ICL_N_VGPIO_USB_6          0x070B0056
#define GPIO_ICL_N_VGPIO_USB_7          0x070B0057
#define GPIO_ICL_N_VGPIO_USB_8          0x070B0058
#define GPIO_ICL_N_VGPIO_USB_9          0x070B0059
#define GPIO_ICL_N_VGPIO_USB_10         0x070B005A
#define GPIO_ICL_N_VGPIO_USB_11         0x070B005B

#define GPIO_ICL_N_VGPIO_LNK_DN0        0x070C0000
#define GPIO_ICL_N_VGPIO_LNK_DN1        0x070C0001
#define GPIO_ICL_N_VGPIO_LNK_DN2        0x070C0002
#define GPIO_ICL_N_VGPIO_LNK_DN3        0x070C0003

#define GPIO_ICL_N_SPI0_IO_2            0x070E0000
#define GPIO_ICL_N_SPI0_IO_3            0x070E0001
#define GPIO_ICL_N_SPI0_MOSI_IO_0       0x070E0002
#define GPIO_ICL_N_SPI0_MOSI_IO_1       0x070E0003
#define GPIO_ICL_N_SPI0_TPM_CSB         0x070E0004
#define GPIO_ICL_N_SPI0_FLASH_0_CSB     0x070E0005
#define GPIO_ICL_N_SPI0_FLASH_1_CSB     0x070E0006
#define GPIO_ICL_N_SPI0_CLK             0x070E0007
#define GPIO_ICL_N_SPI0_CLK_LOOPBK      0x070E0008

#define GPIO_ICL_N_HDACPU_SDI           0x070E0000
#define GPIO_ICL_N_HDACPU_SDO           0x070E0001
#define GPIO_ICL_N_HDACPU_SCLK          0x070E0002
#define GPIO_ICL_N_PM_SYNC              0x070E0003
#define GPIO_ICL_N_PECI                 0x070E0004
#define GPIO_ICL_N_CPUPWRGD             0x070E0005
#define GPIO_ICL_N_THRMTRIPB            0x070E0006
#define GPIO_ICL_N_PLTRST_CPUB          0x070E0007
#define GPIO_ICL_N_PM_DOWN              0x070E0008
#define GPIO_ICL_N_TRIGGER_IN           0x070E0009
#define GPIO_ICL_N_TRIGGER_OUT          0x070E000A
#define GPIO_ICL_N_UFS_RESETB           0x070E000B
#define GPIO_ICL_N_CLKOUT_CPURTC        0x070E000C
#define GPIO_ICL_N_VCCST_PWRGD          0x070E000D
#define GPIO_ICL_N_C10_WAKE             0x070E000E

#define GPIO_ICL_N_JTAG_TDO             0x070F0000
#define GPIO_ICL_N_JTAGX                0x070F0001
#define GPIO_ICL_N_PRDYB                0x070F0002
#define GPIO_ICL_N_PREQB                0x070F0003
#define GPIO_ICL_N_CPU_TRSTB            0x070F0004
#define GPIO_ICL_N_JTAG_TDI             0x070F0005
#define GPIO_ICL_N_JTAG_TMS             0x070F0006
#define GPIO_ICL_N_JTAG_TCK             0x070F0007
#define GPIO_ICL_N_ITP_PMODE            0x070F0008

#define GPIO_ICL_N_HVCMOS_L_BKLTEN      0x07100000
#define GPIO_ICL_N_HVCMOS_L_BKLTCTL     0x07100001
#define GPIO_ICL_N_HVCMOS_L_VDDEN       0x07100002
#define GPIO_ICL_N_HVCMOS_SYS_PWROK     0x07100003
#define GPIO_ICL_N_HVCMOS_SYS_RESETB    0x07100004
#define GPIO_ICL_N_HVCMOS_MLK_RSTB      0x07100005

#endif

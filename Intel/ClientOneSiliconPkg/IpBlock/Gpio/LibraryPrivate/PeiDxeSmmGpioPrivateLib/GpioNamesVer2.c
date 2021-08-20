/** @file
  This file contains GPIO name library implementation specific to Ver2

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
#include <Base.h>
#include <Library/BaseLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/PchInfoLib.h>
#include <Library/GpioPrivateLib.h>
#include <Pins/GpioPinsVer2Lp.h>
#include <Pins/GpioPinsVer2H.h>

STATIC CONST CHAR8*  mGpioGppbNames[] = {
  "GSPI0_CLK_LOOPBK",
  "GSPI1_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppaNames[] = {
  "SPI0_CLK_LOOPBK",
  "ESPI_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioSpiNames[] = {
  "SPI0_IO_2",
  "SPI0_IO_3",
  "SPI0_MOSI_IO_0",
  "SPI0_MOSI_IO_1",
  "SPI0_TPM_CSB",
  "SPI0_FLASH_0_CSB",
  "SPI0_FLASH_1_CSB",
  "SPI0_CLK",
  "SPI0_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mPchLpGpioGpdNames[] = {
  "INPUT3VSEL",
  "SLP_LANB",
  "SLP_SUSB",
  "SLP_WAKEB",
  "SLP_DRAM_RESETB"
};

STATIC CONST CHAR8*  mPchHGpioGpdNames[] = {
  "SLP_LANB",
  "SLP_SUSB",
  "SLP_WAKEB",
  "SLP_DRAM_RESETB"
};

STATIC CONST CHAR8*  mGpioGppdNames[] = {
  "SPI1_THC0_CLK_LOOPBK",
  "GPI2_THC1_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppuNames[] = {
  "GSPI3_CLK_LOOPBK",
  "GSPI4_CLK_LOOPBK",
  "GSPI5_CLK_LOOPBK",
  "GSPI6_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioVgpioNames[] = {
  "VGPIO0",
  "VGPIO4",
  "VGPIO5",
  "VGPIO6",
  "VGPIO7",
  "VGPIO8",
  "VGPIO9",
  "VGPIO10",
  "VGPIO11",
  "VGPIO12",
  "VGPIO13",
  "VGPIO18",
  "VGPIO19",
  "VGPIO20",
  "VGPIO21",
  "VGPIO22",
  "VGPIO23",
  "VGPIO24",
  "VGPIO25",
  "VGPIO30",
  "VGPIO31",
  "VGPIO32",
  "VGPIO33",
  "VGPIO34",
  "VGPIO35",
  "VGPIO36",
  "VGPIO37"
};

STATIC CONST CHAR8*  mGpioGppfNames[] = {
  "GPPF_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioHvmosNames[] = {
  "L_BKLTEN",
  "L_BKLCTL",
  "L_VDDEN",
  "SYS_PWROK",
  "SYS_RESETB",
  "MLK_RSTB"
};

STATIC CONST CHAR8*  mGpioGppeNames[] = {
  "GPPE_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppiNames[] = {
  "SYS_PWROK",
  "SYS_RESETB",
  "MLK_RSTB"
};

STATIC CONST CHAR8*  mGpioJtagNames[] = {
  "JTAG_TDO",
  "JTAGX",
  "PRDYB",
  "PREQB",
  "CPU_TRSTB",
  "JTAG_TDI",
  "JTAG_TMS",
  "JTAG_TCK",
  "DBG_PMODE",
  "MLK"
};

STATIC CONST CHAR8*  mPchLpGpioCpuNames[] = {
  "HDACPU_SDI",
  "HDACPU_SDO",
  "HDACPU_SCLK",
  "PM_SYNC",
  "PECI",
  "CPUPWRGD",
  "THRMTRIPB",
  "PLTRST_CPUB",
  "PM_DOWN",
  "TRIGGER_IN",
  "TRIGGER_OUT",
  "UFS_RESETB",
  "CLKOUT_CPURTC",
  "VCCST_OVERRIDE",
  "C10_WAKE"
};

STATIC CONST CHAR8*  mPchHKGpioCpuNames[] = {
  "HDACPU_SDI",
  "HDACPU_SDO",
  "HDACPU_SCLK",
  "PM_SYNC",
  "PECI",
  "CPUPWRGD",
  "THRMTRIPB",
  "PLTRST_CPUB",
  "PM_DOWN",
  "TRIGGER_IN",
  "TRIGGER_OUT",
  "CLKOUT_CPURTC",
  "VCCST_OVERRIDE",
  "C10_WAKE"
};

STATIC CONST CHAR8*  mGpioVgpio0Names[] = {
  "VGPIO_USB_0",
  "VGPIO_USB_1",
  "VGPIO_USB_2",
  "VGPIO_USB_3",
  "VGPIO_USB_8",
  "VGPIO_USB_9",
  "VGPIO_USB_10",
  "VGPIO_USB_11"
};

STATIC CONST CHAR8*  mPchLpGpioVgpio3Names[] = {
  "VGPIO_PCIE_0",
  "VGPIO_PCIE_1",
  "VGPIO_PCIE_2",
  "VGPIO_PCIE_3",
  "VGPIO_PCIE_4",
  "VGPIO_PCIE_5",
  "VGPIO_PCIE_6",
  "VGPIO_PCIE_7",
  "VGPIO_PCIE_8",
  "VGPIO_PCIE_9",
  "VGPIO_PCIE_10",
  "VGPIO_PCIE_11",
  "VGPIO_PCIE_12",
  "VGPIO_PCIE_13",
  "VGPIO_PCIE_14",
  "VGPIO_PCIE_15",
  "VGPIO_PCIE_16",
  "VGPIO_PCIE_17",
  "VGPIO_PCIE_18",
  "VGPIO_PCIE_19",
  "VGPIO_PCIE_20",
  "VGPIO_PCIE_21",
  "VGPIO_PCIE_22",
  "VGPIO_PCIE_23",
  "VGPIO_PCIE_24",
  "VGPIO_PCIE_25",
  "VGPIO_PCIE_26",
  "VGPIO_PCIE_27",
  "VGPIO_PCIE_28",
  "VGPIO_PCIE_29",
  "VGPIO_PCIE_30",
  "VGPIO_PCIE_31",
  "VGPIO_PCIE_32",
  "VGPIO_PCIE_33",
  "VGPIO_PCIE_34",
  "VGPIO_PCIE_35",
  "VGPIO_PCIE_36",
  "VGPIO_PCIE_37",
  "VGPIO_PCIE_38",
  "VGPIO_PCIE_39",
  "VGPIO_PCIE_40",
  "VGPIO_PCIE_41",
  "VGPIO_PCIE_42",
  "VGPIO_PCIE_43",
  "VGPIO_PCIE_44",
  "VGPIO_PCIE_45",
  "VGPIO_PCIE_46",
  "VGPIO_PCIE_47",
  "VGPIO_PCIE_48",
  "VGPIO_PCIE_49",
  "VGPIO_PCIE_50",
  "VGPIO_PCIE_51",
  "VGPIO_PCIE_52",
  "VGPIO_PCIE_53",
  "VGPIO_PCIE_54",
  "VGPIO_PCIE_55",
  "VGPIO_PCIE_56",
  "VGPIO_PCIE_57",
  "VGPIO_PCIE_58",
  "VGPIO_PCIE_59",
  "VGPIO_PCIE_60",
  "VGPIO_PCIE_61",
  "VGPIO_PCIE_62",
  "VGPIO_PCIE_63",
  "VGPIO_PCIE_64",
  "VGPIO_PCIE_65",
  "VGPIO_PCIE_66",
  "VGPIO_PCIE_67",
  "VGPIO_PCIE_68",
  "VGPIO_PCIE_69",
  "VGPIO_PCIE_70",
  "VGPIO_PCIE_71",
  "VGPIO_PCIE_72",
  "VGPIO_PCIE_73",
  "VGPIO_PCIE_74",
  "VGPIO_PCIE_75",
  "VGPIO_PCIE_76",
  "VGPIO_PCIE_77",
  "VGPIO_PCIE_78",
  "VGPIO_PCIE_79",
  "VGPIO_USB_0",
  "VGPIO_USB_1",
  "VGPIO_USB_2",
  "VGPIO_USB_3",
  "VGPIO_USB_4",
  "VGPIO_USB_5",
  "VGPIO_USB_6",
  "VGPIO_USB_7",
  "VGPIO_PCIE_80",
  "VGPIO_PCIE_81",
  "VGPIO_PCIE_82",
  "VGPIO_PCIE_83"
};

STATIC CONST CHAR8*  mPchHGpioVgpio3Names[] = {
  "VGPIO_PCIE_0",
  "VGPIO_PCIE_1",
  "VGPIO_PCIE_2",
  "VGPIO_PCIE_3",
  "VGPIO_PCIE_4",
  "VGPIO_PCIE_5",
  "VGPIO_PCIE_6",
  "VGPIO_PCIE_7",
  "VGPIO_PCIE_8",
  "VGPIO_PCIE_9",
  "VGPIO_PCIE_10",
  "VGPIO_PCIE_11",
  "VGPIO_PCIE_12",
  "VGPIO_PCIE_13",
  "VGPIO_PCIE_14",
  "VGPIO_PCIE_15",
  "VGPIO_PCIE_16",
  "VGPIO_PCIE_17",
  "VGPIO_PCIE_18",
  "VGPIO_PCIE_19",
  "VGPIO_PCIE_20",
  "VGPIO_PCIE_21",
  "VGPIO_PCIE_22",
  "VGPIO_PCIE_23",
  "VGPIO_PCIE_24",
  "VGPIO_PCIE_25",
  "VGPIO_PCIE_26",
  "VGPIO_PCIE_27",
  "VGPIO_PCIE_28",
  "VGPIO_PCIE_29",
  "VGPIO_PCIE_30",
  "VGPIO_PCIE_31",
  "VGPIO_PCIE_32",
  "VGPIO_PCIE_33",
  "VGPIO_PCIE_34",
  "VGPIO_PCIE_35",
  "VGPIO_PCIE_36",
  "VGPIO_PCIE_37",
  "VGPIO_PCIE_38",
  "VGPIO_PCIE_39",
  "VGPIO_PCIE_40",
  "VGPIO_PCIE_41",
  "VGPIO_PCIE_42",
  "VGPIO_PCIE_43",
  "VGPIO_PCIE_44",
  "VGPIO_PCIE_45",
  "VGPIO_PCIE_46",
  "VGPIO_PCIE_47",
  "VGPIO_PCIE_48",
  "VGPIO_PCIE_49",
  "VGPIO_PCIE_50",
  "VGPIO_PCIE_51",
  "VGPIO_PCIE_52",
  "VGPIO_PCIE_53",
  "VGPIO_PCIE_54",
  "VGPIO_PCIE_55",
  "VGPIO_PCIE_56",
  "VGPIO_PCIE_57",
  "VGPIO_PCIE_58",
  "VGPIO_PCIE_59",
  "VGPIO_PCIE_60",
  "VGPIO_PCIE_61",
  "VGPIO_PCIE_62",
  "VGPIO_PCIE_63",
  "VGPIO_PCIE_64",
  "VGPIO_PCIE_65",
  "VGPIO_PCIE_66",
  "VGPIO_PCIE_67",
  "VGPIO_PCIE_68",
  "VGPIO_PCIE_69",
  "VGPIO_PCIE_70",
  "VGPIO_PCIE_71",
  "VGPIO_PCIE_72",
  "VGPIO_PCIE_73",
  "VGPIO_PCIE_74",
  "VGPIO_PCIE_75",
  "VGPIO_PCIE_76",
  "VGPIO_PCIE_77",
  "VGPIO_PCIE_78",
  "VGPIO_PCIE_79",
  "VGPIO_PCIE_80",
  "VGPIO_PCIE_81",
  "VGPIO_PCIE_82",
  "VGPIO_PCIE_83"
};

STATIC CONST GPIO_GROUP_NAME_INFO  mPchLpGroupDescriptors[] = {
  GPIO_GROUP_NAME("GPP_B", GPIO_VER2_LP_GSPI0_CLK_LOOPBK, mGpioGppbNames),
  GPIO_GROUP_NAME_BASIC("GPP_T"),
  GPIO_GROUP_NAME("GPP_A", GPIO_VER2_LP_ESPI_CLK_LOOPBK, mGpioGppaNames),
  GPIO_GROUP_NAME_BASIC("GPP_R"),
  GPIO_GROUP_NAME("SPI", GPIO_VER2_LP_SPI0_IO_2, mGpioSpiNames),
  GPIO_GROUP_NAME("GPD", GPIO_VER2_LP_INPUT3VSEL, mPchLpGpioGpdNames),
  GPIO_GROUP_NAME_BASIC("GPP_S"),
  GPIO_GROUP_NAME_BASIC("GPP_H"),
  GPIO_GROUP_NAME("GPP_D", GPIO_VER2_LP_GSPI2_CLK_LOOPBK, mGpioGppdNames),
  GPIO_GROUP_NAME("GPP_U", GPIO_VER2_LP_GSPI3_CLK_LOOPBK, mGpioGppuNames),
  GPIO_GROUP_NAME("VGPIO", GPIO_VER2_LP_VGPIO0, mGpioVgpioNames),
  GPIO_GROUP_NAME_BASIC("GPP_C"),
  GPIO_GROUP_NAME("GPP_F", GPIO_VER2_LP_GPPF_CLK_LOOPBK, mGpioGppfNames),
  GPIO_GROUP_NAME("HVCMOS", GPIO_VER2_LP_L_BKLTEN, mGpioHvmosNames),
  GPIO_GROUP_NAME("GPP_E", GPIO_VER2_LP_GPPE_CLK_LOOPBK, mGpioGppeNames),
  GPIO_GROUP_NAME("JTAG", GPIO_VER2_LP_JTAG_TDO, mGpioJtagNames),
  GPIO_GROUP_NAME("CPU", GPIO_VER2_LP_HDACPU_SDI, mPchLpGpioCpuNames),
  GPIO_GROUP_NAME("VGPIO3", GPIO_VER2_LP_VGPIO_PCIE_0, mPchLpGpioVgpio3Names)
};

STATIC CONST GPIO_GROUP_NAME_INFO  mPchHGroupDescriptors[] = {
  GPIO_GROUP_NAME("GPP_A", GPIO_VER2_H_SPI0_CLK_LOOPBK, mGpioGppaNames),
  GPIO_GROUP_NAME_BASIC("GPP_R"),
  GPIO_GROUP_NAME("GPP_B", GPIO_VER2_H_GSPI0_CLK_LOOPBK, mGpioGppbNames),
  GPIO_GROUP_NAME("VGPIO0", GPIO_VER2_H_VGPIO_USB_0, mGpioVgpio0Names),
  GPIO_GROUP_NAME("GPP_D", GPIO_VER2_H_SPI1_THC0_CLK_LOOPBK, mGpioGppdNames),
  GPIO_GROUP_NAME_BASIC("GPP_C"),
  GPIO_GROUP_NAME_BASIC("GPP_S"),
  GPIO_GROUP_NAME_BASIC("GPP_G"),
  GPIO_GROUP_NAME("VGPIO", GPIO_VER2_H_VGPIO0, mGpioVgpioNames),
  GPIO_GROUP_NAME("GPD", GPIO_VER2_H_SLP_LANB, mPchHGpioGpdNames),
  GPIO_GROUP_NAME_BASIC("GPP_E"),
  GPIO_GROUP_NAME_BASIC("GPP_F"),
  GPIO_GROUP_NAME("VGPIO3", GPIO_VER2_H_VGPIO_PCIE_0, mPchHGpioVgpio3Names),
  GPIO_GROUP_NAME_BASIC("GPP_H"),
  GPIO_GROUP_NAME_BASIC("GPP_J"),
  GPIO_GROUP_NAME_BASIC("GPP_K"),
  GPIO_GROUP_NAME("GPP_I", GPIO_VER2_H_SYS_PWROK, mGpioGppiNames),
  GPIO_GROUP_NAME("JTAG", GPIO_VER2_H_JTAG_TDO, mGpioJtagNames),
  GPIO_GROUP_NAME("CPU", GPIO_VER2_H_HDACPU_SDI, mPchHKGpioCpuNames)
};

/**
  Returns GPIO_GROUP_NAME_INFO corresponding to the given GpioPad

  @param[in] GroupIndex  Group index

  @retval GPIO_GROUP_NAME_INFO*  Pointer to the GPIO_GROUP_NAME_INFO
  @reval  NULL                   If no group descriptor was found
**/
CONST
GPIO_GROUP_NAME_INFO*
GpioGetGroupNameInfo (
  IN UINT32  GroupIndex
  )
{
  if (IsPchLp ()) {
    if (GroupIndex < ARRAY_SIZE (mPchLpGroupDescriptors)) {
      return &mPchLpGroupDescriptors[GroupIndex];
    }
  } else {
    if (GroupIndex < ARRAY_SIZE (mPchHGroupDescriptors)) {
      return &mPchHGroupDescriptors[GroupIndex];
    }
  }
  ASSERT (FALSE);
  return NULL;
}


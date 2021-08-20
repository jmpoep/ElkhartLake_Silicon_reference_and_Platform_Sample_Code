/** @file
  This file contains GPIO name library implementation specific to Ver3

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
#include <Base.h>
#include <Library/BaseLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/PchInfoLib.h>
#include <Library/GpioPrivateLib.h>
#include <Pins/GpioPinsVer3.h>

STATIC CONST CHAR8*  mGpioGppbNames[] = {
  "GSPI0_CLK_LOOPBK",
  "GSPI1_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppdNames[] = {
  "GSPI2_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppeNames[] = {
  "GPPE_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppfNames[] = {
  "GPPF_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppgNames[] = {
  "ESPI_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppuNames[] = {
  "GSPI3_CLK_LOOPBK",
  "GSPI4_CLK_LOOPBK",
  "GSPI5_CLK_LOOPBK",
  "GSPI6_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGpdNames[] = {
  "INPUT3VSEL",
  "SLP_LANB",
  "SLP_SUSB",
  "SLP_WAKEB",
  "SLP_DRAM_RESETB"
};

STATIC CONST CHAR8*  mGpioCpuNames[] = {
  "HDACPU_SDI",
  "HDACPU_SDO",
  "HDACPU_BCLK",
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
  "C10_WAKE",
  "PROCHOTB",
  "CATERRB"
};

STATIC CONST CHAR8*  mGpioHvcmosNames[] = {
  "L_BKLTEN",
  "L_BKLCTL",
  "L_VDDEN",
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
  "DBG_PMODE"
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
  "VGPIO37",
  "VGPIO39"
};

STATIC CONST CHAR8*  mGpioVgpio3Names[] = {
  "VGPIO_USB_0",
  "VGPIO_USB_1",
  "VGPIO_USB_2",
  "VGPIO_USB_3"
};

STATIC CONST GPIO_GROUP_NAME_INFO  mPchLpGroupDescriptors[] = {
  GPIO_GROUP_NAME("GPP_B", GPIO_VER3_GSPI0_CLK_LOOPBK, mGpioGppbNames),
  GPIO_GROUP_NAME_BASIC("GPP_T"),
  GPIO_GROUP_NAME("GPP_G", GPIO_VER3_ESPI_CLK_LOOPBK, mGpioGppgNames),
  GPIO_GROUP_NAME_BASIC("GPP_V"),
  GPIO_GROUP_NAME_BASIC("GPP_H"),
  GPIO_GROUP_NAME("GPP_D", GPIO_VER3_GSPI2_CLK_LOOPBK, mGpioGppdNames),
  GPIO_GROUP_NAME("GPP_U", GPIO_VER3_GSPI3_CLK_LOOPBK, mGpioGppuNames),
  GPIO_GROUP_NAME("VGPIO", GPIO_VER3_VGPIO0, mGpioVgpioNames),
  GPIO_GROUP_NAME("GPD", GPIO_VER3_INPUT3VSEL, mGpioGpdNames),
  GPIO_GROUP_NAME("CPU", GPIO_VER3_HDACPU_SDI, mGpioCpuNames),
  GPIO_GROUP_NAME_BASIC("GPP_S"),
  GPIO_GROUP_NAME_BASIC("GPP_A"),
  GPIO_GROUP_NAME("VGPIO3", GPIO_VER3_VGPIO_USB_0, mGpioVgpio3Names),
  GPIO_GROUP_NAME_BASIC("GPP_C"),
  GPIO_GROUP_NAME("GPP_F", GPIO_VER3_GPPF_CLK_LOOPBK, mGpioGppfNames),
  GPIO_GROUP_NAME("HVCMOS", GPIO_VER3_L_BKLTEN, mGpioHvcmosNames),
  GPIO_GROUP_NAME("GPP_E", GPIO_VER3_GPPE_CLK_LOOPBK, mGpioGppeNames),
  GPIO_GROUP_NAME("JTAG", GPIO_VER3_JTAG_TDO, mGpioJtagNames),
  GPIO_GROUP_NAME_BASIC("GPP_R"),
  GPIO_GROUP_NAME("SPI", GPIO_VER3_SPI0_IO_2, mGpioSpiNames)

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
  if (GroupIndex < ARRAY_SIZE (mPchLpGroupDescriptors)) {
    return &mPchLpGroupDescriptors[GroupIndex];
  }
  ASSERT (FALSE);
  return NULL;
}

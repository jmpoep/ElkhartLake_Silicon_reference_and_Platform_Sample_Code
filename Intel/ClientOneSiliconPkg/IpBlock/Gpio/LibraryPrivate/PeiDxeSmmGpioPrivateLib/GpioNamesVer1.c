/** @file
  This file contains GPIO name library implementation specific to Ver1

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
#include <Pins/GpioPinsVer1Lp.h>
#include <Pins/GpioPinsVer1N.h>
#include <Pins/GpioPinsVer1H.h>

STATIC CONST CHAR8*  mGpioGppaNames[] = {
  "ESPI_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppbNames[] = {
  "GSPI0_CLK_LOOPBK",
  "GSPI1_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppdNames[] = {
  "GSPI2_CLK_LOOPBK",
  "SPI1_CLK_LOOPBK"
};

STATIC CONST CHAR8*  mGpioGppiNames[] = {
  "SYS_PWROK",
  "SYS_RESETB",
  "MLK_RSTB"
};

STATIC CONST CHAR8*  mGpioGpdNames[] = {
  "INPUT3VSEL",
  "SLP_LANB",
  "SLP_SUSB",
  "SLP_WAKEB",
  "SLP_DRAM_RESETB"
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
  "VGPIO3",
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
  "VGPIO39",
};

STATIC CONST CHAR8*  mPchHGpioVgpio0Names[] = {
  "VGPIO_USB_0",
  "VGPIO_USB_1",
  "VGPIO_USB_2",
  "VGPIO_USB_3",
  "VGPIO_USB_8",
  "VGPIO_USB_9",
  "VGPIO_USB_10",
  "VGPIO_USB_11"
};

STATIC CONST CHAR8*  mPchNGpioVgpio3Names[] = {
  "VGPIO_USB_0",
  "VGPIO_USB_1",
  "VGPIO_USB_2",
  "VGPIO_USB_3",
  "VGPIO_USB_4",
  "VGPIO_USB_5",
  "VGPIO_USB_6",
  "VGPIO_USB_7",
  "VGPIO_USB_8",
  "VGPIO_USB_9",
  "VGPIO_USB_10",
  "VGPIO_USB_11"
};

STATIC CONST CHAR8*  mGpioVgpio4Names[] = {
  "VGPIO_LNK_DN0",
  "VGPIO_LNK_DN1",
  "VGPIO_LNK_DN2",
  "VGPIO_LNK_DN3"
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
  "ITP_PMODE",
  "MLK" // PCH-H only
};

STATIC CONST CHAR8*  mGpioHvmosNames[] = {
  "HVMOS_L_BKLTEN",
  "HVMOS_L_BKLCTL",
  "HVMOS_L_VDDEN",
  "HVMOS_SYS_PWROK",
  "HVMOS_SYS_RESETB",
  "HVMOS_MLK_RSTB"
};

STATIC CONST CHAR8*  mPchLpNGpioCpuNames[] = {
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
  "VCCST_PWRGD",
  "C10_WAKE"
};

STATIC CONST CHAR8*  mPchHGpioCpuNames[] = {
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

STATIC CONST GPIO_GROUP_NAME_INFO  mPchLpGroupDescriptors[] = {
  GPIO_GROUP_NAME("GPP_A", GPIO_VER1_LP_ESPI_CLK_LOOPBK, mGpioGppaNames),
  GPIO_GROUP_NAME("GPP_B", GPIO_VER1_LP_GSPI0_CLK_LOOPBK, mGpioGppbNames),
  GPIO_GROUP_NAME_BASIC("GPP_C"),
  GPIO_GROUP_NAME("GPP_D", GPIO_VER1_LP_GSPI2_CLK_LOOPBK, mGpioGppdNames),
  GPIO_GROUP_NAME_BASIC("GPP_E"),
  GPIO_GROUP_NAME_BASIC("GPP_F"),
  GPIO_GROUP_NAME_BASIC("GPP_G"),
  GPIO_GROUP_NAME_BASIC("GPP_H"),
  GPIO_GROUP_NAME_BASIC("GPP_R"),
  GPIO_GROUP_NAME_BASIC("GPP_S"),
  GPIO_GROUP_NAME("GPD", GPIO_VER1_LP_INPUT3VSEL, mGpioGpdNames),
  GPIO_GROUP_NAME("VGPIO", GPIO_VER1_LP_VGPIO3, mGpioVgpioNames),
  GPIO_GROUP_NAME("SPI", GPIO_VER1_LP_SPI0_IO_2, mGpioSpiNames),
  GPIO_GROUP_NAME("CPU", GPIO_VER1_LP_HDACPU_SDI, mPchLpNGpioCpuNames),
  GPIO_GROUP_NAME("JTAG", GPIO_VER1_LP_JTAG_TDO, mGpioJtagNames),
  GPIO_GROUP_NAME("HVCMOS", GPIO_VER1_LP_HVCMOS_L_BKLTEN, mGpioHvmosNames)
};

STATIC CONST GPIO_GROUP_NAME_INFO  mPchNGroupDescriptors[] = {
  GPIO_GROUP_NAME("GPP_A", GPIO_VER1_N_ESPI_CLK_LOOPBK, mGpioGppaNames),
  GPIO_GROUP_NAME("GPP_B", GPIO_VER1_N_GSPI0_CLK_LOOPBK, mGpioGppbNames),
  GPIO_GROUP_NAME_BASIC("GPP_C"),
  GPIO_GROUP_NAME("GPP_D", GPIO_VER1_N_GSPI2_CLK_LOOPBK, mGpioGppdNames),
  GPIO_GROUP_NAME_BASIC("GPP_E"),
  GPIO_GROUP_NAME_BASIC("GPP_G"),
  GPIO_GROUP_NAME_BASIC("GPP_H"),
  GPIO_GROUP_NAME_BASIC("GPP_R"),
  GPIO_GROUP_NAME_BASIC("GPP_S"),
  GPIO_GROUP_NAME("GPD", GPIO_VER1_N_INPUT3VSEL, mGpioGpdNames),
  GPIO_GROUP_NAME("VGPIO", GPIO_VER1_N_VGPIO3, mGpioVgpioNames),
  GPIO_GROUP_NAME("VGPIO_3", GPIO_VER1_N_VGPIO_USB_0, mPchNGpioVgpio3Names),
  GPIO_GROUP_NAME("VGPIO_4", GPIO_VER1_N_VGPIO_LNK_DN0, mGpioVgpio4Names),
  GPIO_GROUP_NAME("SPI", GPIO_VER1_N_SPI0_IO_2, mGpioSpiNames),
  GPIO_GROUP_NAME("CPU", GPIO_VER1_N_HDACPU_SDI, mPchLpNGpioCpuNames),
  GPIO_GROUP_NAME("JTAG", GPIO_VER1_N_JTAG_TDO, mGpioJtagNames),
  GPIO_GROUP_NAME("HVCMOS", GPIO_VER1_N_HVCMOS_L_BKLTEN, mGpioHvmosNames)
};

STATIC CONST GPIO_GROUP_NAME_INFO  mPchVer1p1NGroupDescriptors[] = {
  GPIO_GROUP_NAME("GPP_A", GPIO_VER1_N_ESPI_CLK_LOOPBK, mGpioGppaNames),
  GPIO_GROUP_NAME("GPP_B", GPIO_VER1_N_GSPI0_CLK_LOOPBK, mGpioGppbNames),
  GPIO_GROUP_NAME_BASIC("GPP_C"),
  GPIO_GROUP_NAME("GPP_D", GPIO_VER1_N_GSPI2_CLK_LOOPBK, mGpioGppdNames),
  GPIO_GROUP_NAME_BASIC("GPP_E"),
  GPIO_GROUP_NAME_BASIC("GPP_F"),
  GPIO_GROUP_NAME_BASIC("GPP_G"),
  GPIO_GROUP_NAME_BASIC("GPP_H"),
  GPIO_GROUP_NAME_BASIC("GPP_R"),
  GPIO_GROUP_NAME_BASIC("GPP_S"),
  GPIO_GROUP_NAME("GPD", GPIO_VER1_N_INPUT3VSEL, mGpioGpdNames),
  GPIO_GROUP_NAME("VGPIO", GPIO_VER1_N_VGPIO3, mGpioVgpioNames),
  GPIO_GROUP_NAME("VGPIO_3", GPIO_VER1_N_VGPIO_USB_0, mPchNGpioVgpio3Names),
  GPIO_GROUP_NAME("VGPIO_4", GPIO_VER1_N_VGPIO_LNK_DN0, mGpioVgpio4Names),
  GPIO_GROUP_NAME("SPI", GPIO_VER1_N_SPI0_IO_2, mGpioSpiNames),
  GPIO_GROUP_NAME("CPU", GPIO_VER1_N_HDACPU_SDI, mPchLpNGpioCpuNames),
  GPIO_GROUP_NAME("JTAG", GPIO_VER1_N_JTAG_TDO, mGpioJtagNames),
  GPIO_GROUP_NAME("HVCMOS", GPIO_VER1_N_HVCMOS_L_BKLTEN, mGpioHvmosNames)
};
STATIC CONST GPIO_GROUP_NAME_INFO  mPchHGroupDescriptors[] = {
  GPIO_GROUP_NAME("GPP_A", GPIO_VER1_H_ESPI_CLK_LOOPBK, mGpioGppaNames),
  GPIO_GROUP_NAME("GPP_B", GPIO_VER1_H_GSPI0_CLK_LOOPBK, mGpioGppbNames),
  GPIO_GROUP_NAME_BASIC("GPP_C"),
  GPIO_GROUP_NAME("GPP_D", GPIO_VER1_H_GSPI2_CLK_LOOPBK, mGpioGppdNames),
  GPIO_GROUP_NAME_BASIC("GPP_E"),
  GPIO_GROUP_NAME_BASIC("GPP_F"),
  GPIO_GROUP_NAME_BASIC("GPP_G"),
  GPIO_GROUP_NAME_BASIC("GPP_H"),
  GPIO_GROUP_NAME("GPP_I", GPIO_VER1_H_SYS_PWROK, mGpioGppiNames),
  GPIO_GROUP_NAME_BASIC("GPP_J"),
  GPIO_GROUP_NAME_BASIC("GPP_K"),
  GPIO_GROUP_NAME_BASIC("GPP_R"),
  GPIO_GROUP_NAME_BASIC("GPP_S"),
  GPIO_GROUP_NAME("GPD", GPIO_VER1_H_INPUT3VSEL, mGpioGpdNames),
  GPIO_GROUP_NAME("VGPIO", GPIO_VER1_H_VGPIO3, mGpioVgpioNames),
  GPIO_GROUP_NAME("VGPIO_0", GPIO_VER1_H_VGPIO_USB_0, mPchHGpioVgpio0Names),
  GPIO_GROUP_NAME_BASIC("VGPIO_PCIE_"),
  GPIO_GROUP_NAME("SPI", GPIO_VER1_H_SPI0_IO_2, mGpioSpiNames),
  GPIO_GROUP_NAME("JTAG", GPIO_VER1_H_JTAG_TDO, mGpioJtagNames),
  GPIO_GROUP_NAME("CPU", GPIO_VER1_H_HDACPU_SDI, mPchHGpioCpuNames)
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
  if (IsJslPch ()) {
    if (GroupIndex < ARRAY_SIZE (mPchVer1p1NGroupDescriptors)) {
      return &mPchVer1p1NGroupDescriptors[GroupIndex];
    }
  } else {
    if (IsPchLp ()) {
      if (GroupIndex < ARRAY_SIZE (mPchLpGroupDescriptors)) {
        return &mPchLpGroupDescriptors[GroupIndex];
      }
    } else if (IsPchN ()) {
      if (GroupIndex < ARRAY_SIZE (mPchNGroupDescriptors)) {
        return &mPchNGroupDescriptors[GroupIndex];
      }
    } else {
      if (GroupIndex < ARRAY_SIZE (mPchHGroupDescriptors)) {
        return &mPchHGroupDescriptors[GroupIndex];
      }
    }
  }
  ASSERT (FALSE);
  return NULL;
}


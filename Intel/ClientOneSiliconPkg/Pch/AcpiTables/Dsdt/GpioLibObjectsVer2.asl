/**@file
 VER2 GPIO data for use with GPIO ASL lib

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
#include "Register/GpioRegs.h"
#include "Register/GpioRegsVer2.h"
#include "GpioAcpiDefinesVer2.h"

//
// PCH GPIO Community address
//
#define PCH_GPIO_COM0 0x006e0000 // PID_GPIOCOM0 = 0x6E
#define PCH_GPIO_COM1 0x006d0000 // PID_GPIOCOM1 = 0x6D
#define PCH_GPIO_COM2 0x006c0000 // PID_GPIOCOM2 = 0x6C
#define PCH_GPIO_COM3 0x006b0000 // PID_GPIOCOM3 = 0x6B
#define PCH_GPIO_COM4 0x006a0000 // PID_GPIOCOM4 = 0x6A
#define PCH_GPIO_COM5 0x00690000 // PID_GPIOCOM5 = 0x69

//
// If in GPIO_GROUP_INFO structure certain register doesn't exist
// it will have value equal to NO_REGISTER_FOR_PROPERTY
//
#define NO_REGISTER_FOR_PROPERTY 0xFFFF

//
// If in GPIO_GROUP_INFO structure certain group should not be used
// by GPIO OS driver then "Gpio base number" field should be set to below value
//
#define GPIO_OS_DRV_NOT_SUPPORTED 0xFFFF

//
// GPIO Library objects
//
Scope(\_SB)
{
  //
  // GPIO information data structure
  //
  // PCH-LP: GPCL
  //
  // GPCx[GroupIndex][Field]
  //   Field0 - Community
  //   Field1 - Pad number
  //   Field2 - PADCFG register offset
  //   Field3 - HOSTSW_OWN register offset
  //   Field4 - PAD_OWN register offset
  //   Field5 - GPI_GPE_STS register offset
  //   Field6 - Gpio base number for GPIO OS Driver usage
  //            GpioIo and GpioInt number is created in following way:
  //              GpioAcpiPinNumber = GpioHwBankIndex * 32 + GpioPadNumber
  //            where GPIO OS Driver banks are (for PCH-LP):
  //              GpioHwBank[] ={"GPP_B","GPP_T","GPP_A","GPP_R","GPP_S","GPP_H","GPP_D","GPP_U","vGPIO","GPP_F","GPP_C","GPP_E"}
  //
  //
  // GPIO information data structure for PCH-LP
  //
  Name(GPCL, Package(){
    Package(){ // GPP_B
      PCH_GPIO_COM0,
      GPIO_VER2_PCH_LP_GPIO_GPP_B_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_B_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_B_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_B_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_B_GPI_GPE_STS,
      0
    },
    Package(){ // GPP_T
      PCH_GPIO_COM0,
      GPIO_VER2_PCH_LP_GPIO_GPP_T_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_T_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_T_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_T_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_T_GPI_GPE_STS,
      32
    },
    Package(){ // GPP_A
      PCH_GPIO_COM0,
      GPIO_VER2_PCH_LP_GPIO_GPP_A_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_A_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_A_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_A_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_A_GPI_GPE_STS,
      64
    },
    Package(){ // GPP_R
      PCH_GPIO_COM5,
      GPIO_VER2_PCH_LP_GPIO_GPP_R_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_R_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_R_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_R_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_R_GPI_GPE_STS,
      352
    },
    Package(){ // SPI
      PCH_GPIO_COM5,
      GPIO_VER2_PCH_LP_GPIO_SPI_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_SPI_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_SPI_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_SPI_PAD_OWN,
      NO_REGISTER_FOR_PROPERTY,
      GPIO_OS_DRV_NOT_SUPPORTED
    },
    Package(){ // GPD
      PCH_GPIO_COM2,
      GPIO_VER2_PCH_LP_GPIO_GPD_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPD_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPD_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPD_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPD_GPI_GPE_STS,
      GPIO_OS_DRV_NOT_SUPPORTED
    },
    Package(){ // GPP_S
      PCH_GPIO_COM1,
      GPIO_VER2_PCH_LP_GPIO_GPP_S_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_S_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_S_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_S_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_S_GPI_GPE_STS,
      96
    },
    Package(){ // GPP_H
      PCH_GPIO_COM1,
      GPIO_VER2_PCH_LP_GPIO_GPP_H_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_H_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_H_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_H_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_H_GPI_GPE_STS,
      128
    },
    Package(){ // GPP_D
      PCH_GPIO_COM1,
      GPIO_VER2_PCH_LP_GPIO_GPP_D_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_D_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_D_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_D_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_D_GPI_GPE_STS,
      160
    },
    Package(){ // GPP_U
      PCH_GPIO_COM1,
      GPIO_VER2_PCH_LP_GPIO_GPP_U_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_U_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_U_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_U_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_U_GPI_GPE_STS,
      192
    },
    Package(){ // VGPIO
      PCH_GPIO_COM1,
      GPIO_VER2_PCH_LP_GPIO_VGPIO_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_VGPIO_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_VGPIO_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_VGPIO_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_VGPIO_GPI_GPE_STS,
      224
    },
    Package(){ // GPP_C
      PCH_GPIO_COM4,
      GPIO_VER2_PCH_LP_GPIO_GPP_C_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_C_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_C_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_C_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_C_GPI_GPE_STS,
      256
    },
    Package(){ // GPP_F
      PCH_GPIO_COM4,
      GPIO_VER2_PCH_LP_GPIO_GPP_F_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_F_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_F_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_F_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_F_GPI_GPE_STS,
      288
    },
    Package(){ // HVCMOS
      PCH_GPIO_COM4,
      GPIO_VER2_PCH_LP_GPIO_HVCMOS_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_HVCMOS_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_HVCMOS_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_HVCMOS_PAD_OWN,
      NO_REGISTER_FOR_PROPERTY,
      GPIO_OS_DRV_NOT_SUPPORTED
    },
    Package(){ // GPP_E
      PCH_GPIO_COM4,
      GPIO_VER2_PCH_LP_GPIO_GPP_C_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_C_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_C_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_C_PAD_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_GPP_C_GPI_GPE_STS,
      320
    },
    Package(){ // JTAG
      PCH_GPIO_COM4,
      GPIO_VER2_PCH_LP_GPIO_JTAG_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_JTAG_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_JTAG_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_JTAG_PAD_OWN,
      NO_REGISTER_FOR_PROPERTY,
      GPIO_OS_DRV_NOT_SUPPORTED
    },
    Package(){ // CPU
      PCH_GPIO_COM3,
      GPIO_VER2_PCH_LP_GPIO_CPU_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_CPU_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_CPU_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_CPU_PAD_OWN,
      NO_REGISTER_FOR_PROPERTY,
      GPIO_OS_DRV_NOT_SUPPORTED
    },
    Package(){ // VGPIO_3
      PCH_GPIO_COM3,
      GPIO_VER2_PCH_LP_GPIO_VGPIO_3_PAD_MAX,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_VGPIO_3_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_VGPIO_3_HOSTSW_OWN,
      R_GPIO_VER2_PCH_LP_GPIO_PCR_VGPIO_3_PAD_OWN,
      NO_REGISTER_FOR_PROPERTY,
      GPIO_OS_DRV_NOT_SUPPORTED
    }
  })

  //
  // GPIO information data structure for PCH-H
  //
  Name(GPCH, Package(){
    Package(){ // GPP_A
      PCH_GPIO_COM0,
      GPIO_VER2_PCH_H_GPIO_GPP_A_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_A_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_A_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_A_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_A_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_A0
    },
    Package(){ // GPP_R
      PCH_GPIO_COM0,
      GPIO_VER2_PCH_H_GPIO_GPP_R_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_R_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_R_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_R_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_R_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_R0
    },
    Package(){ // GPP_B
      PCH_GPIO_COM0,
      GPIO_VER2_PCH_H_GPIO_GPP_B_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_B_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_B_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_B_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_B_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_B0
    },
    Package(){ // VGPIO_0
      PCH_GPIO_COM0,
      GPIO_VER2_PCH_H_GPIO_VGPIO_0_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_0_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_0_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_0_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_0_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_VGPIO_0_0
    },
    Package(){ // GPP_D
      PCH_GPIO_COM1,
      GPIO_VER2_PCH_H_GPIO_GPP_D_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_D_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_D_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_D_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_D_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_D0
    },
    Package(){ // GPP_C
      PCH_GPIO_COM1,
      GPIO_VER2_PCH_H_GPIO_GPP_C_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_C_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_C_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_C_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_C_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_C0
    },
    Package(){ // GPP_S
      PCH_GPIO_COM1,
      GPIO_VER2_PCH_H_GPIO_GPP_S_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_S_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_S_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_S_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_S_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_S0
    },
    Package(){ // GPP_G
      PCH_GPIO_COM1,
      GPIO_VER2_PCH_H_GPIO_GPP_G_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_G_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_G_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_G_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_G_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_G0
    },
    Package(){ // VGPIO
      PCH_GPIO_COM1,
      GPIO_VER2_PCH_H_GPIO_VGPIO_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_VGPIO0
    },
    Package(){ // GPD
      PCH_GPIO_COM2,
      GPIO_VER2_PCH_H_GPIO_GPD_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPD_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPD_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPD_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPD_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPD_0
    },
    Package(){ // GPP_E
      PCH_GPIO_COM3,
      GPIO_VER2_PCH_H_GPIO_GPP_C_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_C_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_C_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_C_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_C_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_E0
    },
    Package(){ // GPP_F
      PCH_GPIO_COM3,
      GPIO_VER2_PCH_H_GPIO_GPP_F_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_F_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_F_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_F_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_F_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_F0
    },
    Package(){ // VGPIO_3
      PCH_GPIO_COM3,
      GPIO_VER2_PCH_H_GPIO_VGPIO_3_PAD_MAX,
      NO_REGISTER_FOR_PROPERTY,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_3_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_3_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_VGPIO_3_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_VGPIO_3_0
    },
    Package(){ // GPP_H
      PCH_GPIO_COM4,
      GPIO_VER2_PCH_H_GPIO_GPP_H_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_H_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_H_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_H_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_H_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_H0
    },
    Package(){ // GPP_J
      PCH_GPIO_COM4,
      GPIO_VER2_PCH_H_GPIO_GPP_J_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_J_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_J_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_J_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_J_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_J0
    },
    Package(){ // GPP_K
      PCH_GPIO_COM4,
      GPIO_VER2_PCH_H_GPIO_GPP_K_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_K_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_K_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_K_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_K_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_K0
    },
    Package(){ // GPP_I
      PCH_GPIO_COM5,
      GPIO_VER2_PCH_H_GPIO_GPP_I_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_I_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_I_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_I_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_GPP_I_GPI_GPE_STS,
      GPIO_VER2_H_DRIVER_GPP_I0
    },
    Package(){ // JTAG
      PCH_GPIO_COM5,
      GPIO_VER2_PCH_H_GPIO_JTAG_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_JTAG_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_JTAG_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_JTAG_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_JTAG_GPI_GPE_EN,
      GPIO_VER2_H_DRIVER_JTAG_JTAG_TDO
    },
    Package(){ // CPU
      PCH_GPIO_COM5,
      GPIO_VER2_PCH_H_GPIO_CPU_PAD_MAX,
      R_GPIO_VER2_PCH_H_GPIO_PCR_CPU_PADCFG_OFFSET,
      R_GPIO_VER2_PCH_H_GPIO_PCR_CPU_HOSTSW_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_CPU_PAD_OWN,
      R_GPIO_VER2_PCH_H_GPIO_PCR_CPU_GPI_GPE_EN,
      GPIO_VER2_H_DRIVER_CPU_HDACPU_SDI
    },
  })

  //
  // Object for storing RX Level/Edge Configuration for all pads.
  // One fields contains data for one pad.
  //   00b = Level
  //   01b = Edge (RxInv=0 for rising edge; 1 for falling edge)
  //   10b = Disabled
  //   11b = Either rising edge or falling edge
  //
  // Each row has data for one group. Buffer size needs
  // to equal to number of pads
  Name(RXEV, Package(){
    Buffer(GPIO_VER2_PCH_LP_GPIO_GPP_B_PAD_MAX){},  // PCH-LP: GPP_B,  PCH-H: SPI
    Buffer(GPIO_VER2_PCH_H_GPIO_GPP_A_PAD_MAX){},   // PCH-LP: GPP_T,  PCH-H: GPP_A
    Buffer(GPIO_VER2_PCH_H_GPIO_GPP_B_PAD_MAX){},   // PCH-LP: GPP_A,  PCH-H: GPP_B
    Buffer(GPIO_VER2_PCH_LP_GPIO_GPP_R_PAD_MAX){},  // PCH-LP: GPP_R,  PCH-H: VGPIO0
    Buffer(GPIO_VER2_PCH_H_GPIO_GPP_C_PAD_MAX){},   // PCH-LP: SPI,    PCH-H: GPP_C
    Buffer(GPIO_VER2_PCH_H_GPIO_GPP_D_PAD_MAX){},   // PCH-LP: GPD,    PCH-H: GPP_D
    Buffer(GPIO_VER2_PCH_LP_GPIO_GPP_S_PAD_MAX){},  // PCH-LP: GPP_S,  PCH-H: GPP_R
    Buffer(GPIO_VER2_PCH_LP_GPIO_GPP_H_PAD_MAX){},  // PCH-LP: GPP_H,  PCH-H: GPP_S
    Buffer(GPIO_VER2_PCH_LP_GPIO_GPP_D_PAD_MAX){},  // PCH-LP: GPP_D,  PCH-H: GPP_G
    Buffer(GPIO_VER2_PCH_H_GPIO_VGPIO_PAD_MAX){},   // PCH-LP: GPP_U,  PCH-H: VGPIO
    Buffer(GPIO_VER2_PCH_LP_GPIO_VGPIO_PAD_MAX){},  // PCH-LP: VGPIO,  PCH-H: GPD
    Buffer(GPIO_VER2_PCH_LP_GPIO_GPP_C_PAD_MAX){},  // PCH-LP: GPP_C,  PCH-H: GPP_E
    Buffer(GPIO_VER2_PCH_LP_GPIO_GPP_F_PAD_MAX){},  // PCH-LP: GPP_F,  PCH-H: GPP_F
    Buffer(GPIO_VER2_PCH_H_GPIO_VGPIO_3_PAD_MAX){}, // PCH-LP: HVCMOS, PCH-H: VGPIO3
    Buffer(GPIO_VER2_PCH_LP_GPIO_GPP_E_PAD_MAX){},  // PCH-LP: GPP_E,  PCH-H: GPP_H
    Buffer(GPIO_VER2_PCH_H_GPIO_GPP_K_PAD_MAX){},   // PCH-LP: JTAG,   PCH-H: GPP_K
    Buffer(GPIO_VER2_PCH_LP_GPIO_CPU_PAD_MAX){},    // PCH-LP: CPU,    PCH-H: GPP_J
    Buffer(GPIO_VER2_PCH_LP_GPIO_VGPIO_3_PAD_MAX){},// PCH-LP: VGPIO3, PCH-H: GPP_I
    Buffer(GPIO_VER2_PCH_H_GPIO_JTAG_PAD_MAX){},    // PCH-LP: -----,  PCH-H: JTAG
    Buffer(GPIO_VER2_PCH_H_GPIO_CPU_PAD_MAX){}      // PCH-LP: -----,  PCH-H: CPU
  })
}
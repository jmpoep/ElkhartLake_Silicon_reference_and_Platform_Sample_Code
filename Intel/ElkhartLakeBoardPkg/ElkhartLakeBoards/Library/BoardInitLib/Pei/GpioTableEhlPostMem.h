/** @file
  GPIO definition table for ElkhartLake RVP & CRB Board

@copyright
  Copyright (c) 2019 Intel Corporation. All rights reserved
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.
  This file contains an 'Intel Peripheral Driver' and is
  licensed for Intel CPUs and chipsets under the terms of your
  license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the
  license agreement.
**/
#ifndef _ELKHARTLAKE_GPIO_TABLE_H_
#define _ELKHARTLAKE_GPIO_TABLE_H_

#include <Pins/GpioPinsVer3.h>
#include <Pins/GpioPinsVer1N.h>
#include <Library/GpioLib.h>
#include <Library/GpioConfig.h>

#ifndef ARG_UNUSED
#if defined(__GNUC__)
#  define ARG_UNUSED  __attribute__ ((unused))
#else
#  define ARG_UNUSED
#endif
#endif

static GPIO_INIT_CONFIG ARG_UNUSED mGpioTableEhlRvp[] =
{
  // M.2 Key-E - WLAN/BT
  {GPIO_VER3_GPP_E11, {GpioPadModeGpio, GpioHostOwnDefault, GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioHostDeepReset, GpioTermNone,  GpioOutputStateUnlock}},  //BT_RF_KILL_N
  {GPIO_VER3_GPP_E10, {GpioPadModeGpio, GpioHostOwnDefault, GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioHostDeepReset, GpioTermNone,  GpioOutputStateUnlock}},  //WIFI_RF_KILL_N
  {GPIO_VER3_GPD7,    {GpioPadModeGpio, GpioHostOwnAcpi,    GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioPlatformReset, GpioTermNone}},                          //M.2_WLAN_PERST_N
  {GPIO_VER3_GPP_F4,  {GpioPadModeGpio, GpioHostOwnAcpi,    GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntSci, GpioHostDeepReset, GpioTermWpu5K, GpioPadConfigUnlock  }},  //WIFI_WAKE_N
  {GPIO_VER3_GPP_F20, {GpioPadModeGpio, GpioHostOwnAcpi,    GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntSci, GpioHostDeepReset, GpioTermNone,  GpioPadConfigUnlock  }},  //UART_BT_WAKE_N

  // X4 Pcie Slot for Gen3 and Gen 4
  {GPIO_VER3_GPP_E13, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutLow,     GpioIntDis,              GpioPlatformReset, GpioTermNone}},  //ONBOARD_X4_PCIE_SLOT1_PWREN_N
  {GPIO_VER3_GPD11,   {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioPlatformReset, GpioTermNone}},  //ONBOARD_X4_PCIE_SLOT1_RESET_N
  {GPIO_VER3_GPP_E2,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntSci, GpioHostDeepReset, GpioTermNone,  GpioPadConfigUnlock}},  //ONBOARD_X4_PCIE_SLOT1_WAKE_N

  // X1 PCIe M.2 Key-B WWAN/SATA SSD
  {GPIO_VER3_GPP_F21, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PWR_EN
  {GPIO_VER3_GPP_V13, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_RST_N
  {GPIO_VER3_GPP_B14, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PE_RST_N
  {GPIO_VER3_GPP_B17, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PE_WAKE_N
  {GPIO_VER3_GPP_E0,  {GpioPadModeGpio,    GpioHostOwnGpio, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_FCP_OFF_N
  {GPIO_VER3_GPP_G12, {GpioPadModeNative3, GpioHostOwnGpio, GpioDirNone, GpioOutDefault, GpioIntDis, GpioHostDeepReset, GpioTermNone}},  //M.2_SSD_SATAXPCIE_1
  {GPIO_VER3_GPP_E8,  {GpioPadModeNative2, GpioHostOwnGpio, GpioDirNone, GpioOutDefault, GpioIntDis, GpioHostDeepReset, GpioTermNone}},  //M.2_SSD_SATA_DEVSLP_1

  // Battery Charger Vmin to PCH PROCHOT
  {GPIO_VER3_GPP_B2,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntEdge|GpioIntSci, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //BC_PROCHOT_N

  // FPS
  {GPIO_VER3_GPP_V14, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut, GpioOutHigh,    GpioIntDis,               GpioPlatformReset, GpioTermNone}},                       //FPS_RST_N
  {GPIO_VER3_GPP_V15, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirIn,  GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //FPS_INT

  // Audio
  {GPIO_VER3_GPP_B18, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,               GpioPlatformReset, GpioTermNone}},                       //SPKR_PD_N
  {GPIO_VER3_GPP_B15, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //CODEC_INT_N

  // Touch Panel 1
  {GPIO_VER3_GPP_B16, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},                       //TCH_PNL_PWR_EN
  {GPIO_VER3_GPP_E6,  {GpioPadModeNative2, GpioHostOwnGpio, GpioDirNone, GpioOutDefault, GpioIntDis, GpioHostDeepReset, GpioTermNone, GpioPadConfigUnlock}},  //THC0_SPI1_RST_N
  {GPIO_VER3_GPP_E17, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC0_SPI1_INT_N

  // Touch Panel 2, Not used by default in RVP
  //{GPIO_VER3_GPP_F17, {GpioPadModeNative3, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC1_SPI2_RSTB
  //{GPIO_VER3_GPP_F5,  {GpioPadModeNative3, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntEdge|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC1_SPI2_INT_N

  // SPI TPM
  {GPIO_VER3_GPP_G19, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirIn, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioHostDeepReset, GpioTermNone, GpioPadConfigUnlock}},  //SPI_TPM_INT_N

  // eMMC
  {GPIO_VER3_GPP_V0,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_CMD
  {GPIO_VER3_GPP_V1,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA0
  {GPIO_VER3_GPP_V2,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA1
  {GPIO_VER3_GPP_V3,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA2
  {GPIO_VER3_GPP_V4,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA3
  {GPIO_VER3_GPP_V5,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA4
  {GPIO_VER3_GPP_V6,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA5
  {GPIO_VER3_GPP_V7,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA6
  {GPIO_VER3_GPP_V8,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA7
  {GPIO_VER3_GPP_V9,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpd20K}},  //EMMC_RCLK
  {GPIO_VER3_GPP_V10, {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpd20K}},  //EMMC_CLK
  {GPIO_VER3_GPP_V11, {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_RESET

  // PSE GBE 0 - 1
  {GPIO_VER3_GPP_A0, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A1, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A2, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A3, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A4, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A5, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A6, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A7, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A8, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A9, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A10, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A11, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A12, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A13, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A14, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A15, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A16, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A17, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A18, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A19, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A20, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A21, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A22, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A23, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},

  // PSE UART 2 for debug log
  {GPIO_VER3_GPP_T12, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_T13, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_T14, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_T15, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},

  // MISC
  //{GPIO_VER3_GPP_R2,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut, GpioOutLow,     GpioIntDis,              GpioPlatformReset, GpioTermWpd20K}},                     //FLASH_DES_SEC_OVERRIDE
  {GPIO_VER3_GPD1,    {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //ACPRESENT
  // Generic Buttons
  {GPIO_VER3_GPP_E9,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntBothEdge | GpioIntSci, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  // HOME_BUTTON_N
  {GPIO_VER3_GPP_E12, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntBothEdge | GpioIntSci, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  // VOLUMEUP_N
  {GPIO_VER3_GPP_C8,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntBothEdge | GpioIntSci, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  // VOLUMEDOWN_N
  {0x0}
};


static GPIO_INIT_CONFIG ARG_UNUSED mGpioTableEhlSimics[] =
{
  // M.2 Key-E - WLAN/BT
  {GPIO_VER3_GPP_E11, {GpioPadModeGpio, GpioHostOwnDefault, GpioDirOut,   GpioOutHigh,   GpioIntDis,              GpioHostDeepReset,  GpioTermNone,  GpioOutputStateUnlock}},  //BT_RF_KILL_N
  {GPIO_VER3_GPP_E10, {GpioPadModeGpio, GpioHostOwnDefault, GpioDirOut,   GpioOutHigh,   GpioIntDis,              GpioHostDeepReset,  GpioTermNone,  GpioOutputStateUnlock}},  //WIFI_RF_KILL_N
  {GPIO_VER3_GPD7,    {GpioPadModeGpio, GpioHostOwnAcpi,    GpioDirOut,   GpioOutHigh,   GpioIntDis,              GpioPlatformReset,  GpioTermNone}},                          //M.2_WLAN_PERST_N
  {GPIO_VER3_GPP_F4,  {GpioPadModeGpio, GpioHostOwnAcpi,    GpioDirInInv, GpioOutDefault,GpioIntLevel|GpioIntSci, GpioHostDeepReset,  GpioTermWpu5K, GpioPadConfigUnlock  }},  //WIFI_WAKE_N
  {GPIO_VER3_GPP_F20, {GpioPadModeGpio, GpioHostOwnAcpi,    GpioDirInInv, GpioOutDefault,GpioIntLevel|GpioIntSci, GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock  }},  //UART_BT_WAKE_N

  // X4 Pcie Slot for Gen3 and Gen 4
  {GPIO_VER3_GPP_E13, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,  GpioOutLow,   GpioIntDis,GpioPlatformReset,  GpioTermNone}},  //ONBOARD_X4_PCIE_SLOT1_PWREN_N
  {GPIO_VER3_GPD11,   {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,  GpioIntDis,GpioPlatformReset,  GpioTermNone}},  //ONBOARD_X4_PCIE_SLOT1_RESET_N
  {GPIO_VER3_GPP_E2,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv,  GpioOutDefault,GpioIntLevel|GpioIntSci,GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock  }},  //ONBOARD_X4_PCIE_SLOT1_WAKE_N

  // X1 PCIe M.2 Key-B WWAN/SATA SSD
  {GPIO_VER3_GPP_F21, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PWR_EN
  {GPIO_VER3_GPP_V13, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_RST_N
  {GPIO_VER3_GPP_B14, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PE_RST_N
  {GPIO_VER3_GPP_B17, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PE_WAKE_N
  {GPIO_VER3_GPP_E0,  {GpioPadModeGpio,    GpioHostOwnGpio, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_FCP_OFF_N
  {GPIO_VER3_GPP_G12, {GpioPadModeNative3, GpioHostOwnGpio, GpioDirNone, GpioOutDefault, GpioIntDis, GpioHostDeepReset, GpioTermNone}},  //M.2_SSD_SATAXPCIE_1
  {GPIO_VER3_GPP_E8,  {GpioPadModeNative2, GpioHostOwnGpio, GpioDirNone, GpioOutDefault, GpioIntDis, GpioHostDeepReset, GpioTermNone}},  //M.2_SSD_SATA_DEVSLP_1

  // Battery Charger Vmin to PCH PROCHOT
//  {GPIO_VER3_GPP_B2,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntEdge|GpioIntSci, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //BC_PROCHOT_N

  // FPS
  {GPIO_VER3_GPP_V14, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut, GpioOutHigh,    GpioIntDis,               GpioPlatformReset,  GpioTermNone}},                        //FPS_RST_N
  {GPIO_VER3_GPP_V15, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirIn,  GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset,  GpioTermNone,  GpioPadConfigUnlock}},  //FPS_INT

  // Audio
  {GPIO_VER3_GPP_B18, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,     GpioIntDis,               GpioPlatformReset, GpioTermNone}},                       //SPKR_PD_N
  {GPIO_VER3_GPP_B15, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //CODEC_INT_N

  // Touch Panel 1
  {GPIO_VER3_GPP_B16, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},                       //TCH_PNL_PWR_EN
  {GPIO_VER3_GPP_E6,  {GpioPadModeNative2, GpioHostOwnGpio, GpioDirNone, GpioOutDefault, GpioIntDis, GpioHostDeepReset, GpioTermNone, GpioPadConfigUnlock}},  //THC0_SPI1_RST_N
  {GPIO_VER3_GPP_E17, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC0_SPI1_INT_N

  // Touch Panel 2, Not used by default in RVP
  //{GPIO_VER3_GPP_F17, {GpioPadModeNative3, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC1_SPI2_RSTB
  //{GPIO_VER3_GPP_F5,  {GpioPadModeNative3, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntEdge|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC1_SPI2_INT_N

  // SPI TPM
  {GPIO_VER3_GPP_G19, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirIn, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioHostDeepReset, GpioTermNone, GpioPadConfigUnlock}},  //SPI_TPM_INT_N

  // Generic Buttons
  {GPIO_VER3_GPP_E9,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntBothEdge | GpioIntSci, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  // HOME_BUTTON_N
  {GPIO_VER3_GPP_E12, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntBothEdge | GpioIntSci, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  // VOLUMEUP_N
  {GPIO_VER3_GPP_C8,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntBothEdge | GpioIntSci, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  // VOLUMEDOWN_N
  {0x0}
};

static GPIO_INIT_CONFIG ARG_UNUSED mGpioTableEhlCrb[] =
{
  // M.2 Key-E - WLAN/BT
  {GPIO_VER3_GPP_E11, {GpioPadModeGpio, GpioHostOwnDefault, GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioHostDeepReset, GpioTermNone,  GpioOutputStateUnlock}},  //BT_RF_KILL_N
  {GPIO_VER3_GPP_E10, {GpioPadModeGpio, GpioHostOwnDefault, GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioHostDeepReset, GpioTermNone,  GpioOutputStateUnlock}},  //WIFI_RF_KILL_N
  {GPIO_VER3_GPD7,    {GpioPadModeGpio, GpioHostOwnAcpi,    GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioPlatformReset, GpioTermNone}},                          //M.2_WLAN_PERST_N
  {GPIO_VER3_GPP_F4,  {GpioPadModeGpio, GpioHostOwnAcpi,    GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntSci, GpioHostDeepReset, GpioTermWpu5K, GpioPadConfigUnlock  }},  //WIFI_WAKE_N
  {GPIO_VER3_GPP_F20, {GpioPadModeGpio, GpioHostOwnAcpi,    GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntSci, GpioHostDeepReset, GpioTermNone,  GpioPadConfigUnlock  }},  //UART_BT_WAKE_N

  // X4 Pcie Slot for Gen3 and Gen 4
  {GPIO_VER3_GPD11,   {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioPlatformReset, GpioTermNone}},  //ONBOARD_X4_PCIE_SLOT1_RESET_N
  {GPIO_VER3_GPP_E2,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntSci, GpioHostDeepReset, GpioTermNone,  GpioPadConfigUnlock}},  //ONBOARD_X4_PCIE_SLOT1_WAKE_N

  // X1 PCIe M.2 Key-B WWAN/SATA SSD
  {GPIO_VER3_GPP_F21, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PWR_EN
  {GPIO_VER3_GPP_V13, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_RST_N
  {GPIO_VER3_GPP_B14, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PE_RST_N
  {GPIO_VER3_GPP_B17, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PE_WAKE_N
  {GPIO_VER3_GPP_E0,  {GpioPadModeGpio,    GpioHostOwnGpio, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_FCP_OFF_N
  {GPIO_VER3_GPP_E8,  {GpioPadModeNative2, GpioHostOwnGpio, GpioDirNone, GpioOutDefault, GpioIntDis, GpioHostDeepReset, GpioTermNone}},  //M.2_SSD_SATA_DEVSLP_1

  // Battery Charger Vmin to PCH PROCHOT
  {GPIO_VER3_GPP_B2,  {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntEdge|GpioIntSci, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //BC_PROCHOT_N

  // FPS
  {GPIO_VER3_GPP_V14, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut, GpioOutHigh,    GpioIntDis,               GpioPlatformReset, GpioTermNone}},                       //FPS_RST_N
  {GPIO_VER3_GPP_V15, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirIn,  GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //FPS_INT

  // Audio
  {GPIO_VER3_GPP_B15, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //CODEC_INT_N

  // Touch Panel 1
  {GPIO_VER3_GPP_B16, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},                       //TCH_PNL_PWR_EN
  {GPIO_VER3_GPP_E17, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC0_SPI1_INT_N

  // SPI TPM
  {GPIO_VER3_GPP_G19, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirIn, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioHostDeepReset, GpioTermNone, GpioPadConfigUnlock}},  //SPI_TPM_INT_N

  // eMMC
  {GPIO_VER3_GPP_V0,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_CMD
  {GPIO_VER3_GPP_V1,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA0
  {GPIO_VER3_GPP_V2,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA1
  {GPIO_VER3_GPP_V3,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA2
  {GPIO_VER3_GPP_V4,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA3
  {GPIO_VER3_GPP_V5,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA4
  {GPIO_VER3_GPP_V6,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA5
  {GPIO_VER3_GPP_V7,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA6
  {GPIO_VER3_GPP_V8,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_DATA7
  {GPIO_VER3_GPP_V9,  {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpd20K}},  //EMMC_RCLK
  {GPIO_VER3_GPP_V10, {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpd20K}},  //EMMC_CLK
  {GPIO_VER3_GPP_V11, {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioHostDeepReset,  GpioTermWpu20K}},  //EMMC_RESET


  // PSE GBE 0 - 1
  {GPIO_VER3_GPP_A0, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A1, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A2, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A3, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A4, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A5, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A6, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A7, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A8, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A9, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A10, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A11, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A12, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A13, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A14, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A15, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A16, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A17, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A18, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A19, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A20, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A21, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A22, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_A23, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},

  // PSE UART 2 for debug log
  {GPIO_VER3_GPP_T12, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_T13, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_T14, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},
  {GPIO_VER3_GPP_T15, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResumeReset, GpioTermDefault}},

  // MISC
  {GPIO_VER3_GPD1,    {GpioPadModeNative1, GpioHostOwnGpio, GpioDirNone,  GpioOutDefault, GpioIntDis, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //ACPRESENT
  {0x0}
};

static GPIO_INIT_CONFIG ARG_UNUSED mEhlTouchPanel1GpioTableRvp[] =
{
  // Touch Panel 1
  {GPIO_VER3_GPP_B16, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},                       //TCH_PNL_PWR_EN
  {GPIO_VER3_GPP_E6,  {GpioPadModeNative2, GpioHostOwnGpio, GpioDirNone, GpioOutDefault, GpioIntDis, GpioHostDeepReset, GpioTermNone, GpioPadConfigUnlock}},  //THC0_SPI1_RST_N
  {GPIO_VER3_GPP_E17, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC0_SPI1_INT_N
};

static GPIO_INIT_CONFIG ARG_UNUSED mEhlTouchPanel1GpioTableCrb[] =
{
  // Touch Panel 1
  {GPIO_VER3_GPP_B16, {GpioPadModeGpio,    GpioHostOwnAcpi, GpioDirOut,  GpioOutHigh,    GpioIntDis, GpioPlatformReset, GpioTermNone}},                       //TCH_PNL_PWR_EN
  {GPIO_VER3_GPP_E17, {GpioPadModeGpio, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntLevel|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC0_SPI1_INT_N
};

static GPIO_INIT_CONFIG ARG_UNUSED mEhlTouchPanel2GpioTable[] =
{
  // Touch Panel 2, Not used by default in RVP
  {GPIO_VER3_GPP_F17, {GpioPadModeNative3, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,              GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC1_SPI2_RSTB
  {GPIO_VER3_GPP_F5,  {GpioPadModeNative3, GpioHostOwnGpio, GpioDirInInv, GpioOutDefault, GpioIntEdge|GpioIntApic, GpioPlatformReset, GpioTermNone, GpioPadConfigUnlock}},  //THC1_SPI2_INT_N
};

static GPIO_INIT_CONFIG mEhlSciGpioTable[] =
{
  {GPIO_VER3_GPP_U12, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResetDefault, GpioTermDefault}},  //ISI_CHX_OKNOK_0
  {GPIO_VER3_GPP_U13, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResetDefault, GpioTermDefault}},  //ISI_CHX_OKNOK_1
  {GPIO_VER3_GPP_U14, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResetDefault, GpioTermDefault}},  //ISI_CHX_RLY_SWTCH
  {GPIO_VER3_GPP_U15, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResetDefault, GpioTermDefault}},  //ISI_CHX_PMIC_EN
  {GPIO_VER3_GPP_U16, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResetDefault, GpioTermDefault}},  //ISI_OKNOK_0
  {GPIO_VER3_GPP_U17, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResetDefault, GpioTermDefault}},  //ISI_OKNOK_1
  {GPIO_VER3_GPP_U18, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirDefault, GpioOutDefault, GpioIntDefault, GpioResetDefault, GpioTermDefault}}   //ISI_ALERT
};

static GPIO_INIT_CONFIG mEhlPseTsn0DeviceGpioTable[] =
{
  {GPIO_VER3_GPP_C3,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirOut,    GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII0_MDC
  {GPIO_VER3_GPP_C4,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirInOut,  GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII0_MDIO
  {GPIO_VER3_GPP_T4,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirIn,     GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII0_INT
  {GPIO_VER3_GPP_T5,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirOut,    GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII0_RESETB
  {GPIO_VER3_GPP_T6,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirInOut,  GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII0_AUXTS
  {GPIO_VER3_GPP_T7,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirInOut,  GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}}   //RGMII0_PPS
};

static GPIO_INIT_CONFIG mEhlPseTsn1DeviceGpioTable[] =
{
  {GPIO_VER3_GPP_C6,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirOut,    GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII1_MDC
  {GPIO_VER3_GPP_C7,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirInOut,  GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII1_MDIO
  {GPIO_VER3_GPP_H0,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirIn,     GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII1_INT
  {GPIO_VER3_GPP_H1,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirOut,    GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII1_RESETB
  {GPIO_VER3_GPP_H2,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirInOut,  GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII1_AUXTS
  {GPIO_VER3_GPP_H3,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirInOut,  GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}}   //RGMII1_PPS
};

static GPIO_INIT_CONFIG mEhlPchTsnDeviceGpioTable[] =
{
  {GPIO_VER3_GPP_C17, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirOut,    GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII2_MDC
  {GPIO_VER3_GPP_C16, {GpioPadModeNative1, GpioHostOwnDefault, GpioDirInOut,  GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII2_MDIO
  {GPIO_VER3_GPP_U0,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirIn,     GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII2_INT
  {GPIO_VER3_GPP_U2,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirInOut,  GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII2_PPS
  {GPIO_VER3_GPP_U1,  {GpioPadModeGpio,    GpioHostOwnDefault, GpioDirOut,    GpioOutHigh,      GpioIntDis, GpioResumeReset,  GpioTermNone}},  //RGMII2_RESETB
  {GPIO_VER3_GPP_U3,  {GpioPadModeNative1, GpioHostOwnDefault, GpioDirInOut,  GpioOutDefault,   GpioIntDis, GpioResumeReset,  GpioTermNone}}   //RGMII2_AUXTS
};

static GPIO_INIT_CONFIG mGpioTableJslLp4x[] =
{
  {GPIO_VER1_N_GPP_A9,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //WF_CAM_CLK_EN
  {GPIO_VER1_N_GPP_A11,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //CRD_CAM_PRIVACY_LED_1
  {GPIO_VER1_N_GPP_A12,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //x1_PCIE_SLOT2_PWR_EN
  {GPIO_VER1_N_GPP_A19,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //GPPC_A_19_PCHHOTB_USB3_A_PWR_EN

  {GPIO_VER1_N_GPP_B3,   {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntApic,  GpioPlatformReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //CODEC_INT_N
  {GPIO_VER1_N_GPP_B4,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirIn,     GpioOutDefault,  GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //CPU_GP_3_SNSR_HDR
  {GPIO_VER1_N_GPP_B14,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //WF_CAM_SW_RST_N
  {GPIO_VER1_N_GPP_B15,  {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntEdge|GpioIntApic,   GpioPlatformReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //THC0_SPI1_INT_N
  {GPIO_VER1_N_GPP_B18,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //CRD_CAM_STROBE_1
  {GPIO_VER1_N_GPP_B23,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirIn,     GpioOutDefault,  GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //BIOS_REC

  {GPIO_VER1_N_GPP_C1,   {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntSci,   GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //M.2_WIFI_WAKE_N
  {GPIO_VER1_N_GPP_C2,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirInOut,  GpioOutDefault,  GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //CAM_VSYNC1
  {GPIO_VER1_N_GPP_C3,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirIn,     GpioOutDefault,  GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //M2_WWAN_SSD_SKT2_CFG2
  {GPIO_VER1_N_GPP_C4,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //ONBOARD_X4_PCIE_SLOT1_RESET_N
  {GPIO_VER1_N_GPP_C5,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //THC0_SPI1_RST_N
  {GPIO_VER1_N_GPP_C7,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //SLP_LAN_N
  {GPIO_VER1_N_GPP_C8,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //SPKR_PD_N
  {GPIO_VER1_N_GPP_C9,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //TCH_PAD_LS_EN
  {GPIO_VER1_N_GPP_C10,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //M.2_WWAN_DISABLE_N
  {GPIO_VER1_N_GPP_C11,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //EC_SLP_S0_CS_N
  {GPIO_VER1_N_GPP_C12,  {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntEdge|GpioIntApic,   GpioPlatformReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //THC1_INT_N_TCH_PNL
  {GPIO_VER1_N_GPP_C13,  {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntSci,   GpioPlatformReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //SAR_NIRQ_PCH
  {GPIO_VER1_N_GPP_C14,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //PCIE_WAKE2_N
  {GPIO_VER1_N_GPP_C15,  {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntEdge|GpioIntApic,   GpioPlatformReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //TCH_PAD_INT_N

  {GPIO_VER1_N_GPP_D0,   {GpioPadModeGpio,  GpioHostOwnDefault, GpioDirOut,  GpioOutHigh,     GpioIntDis,                GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock  }}, // WIFI_RF_KILL_N
  {GPIO_VER1_N_GPP_D1,   {GpioPadModeGpio,  GpioHostOwnDefault, GpioDirOut,  GpioOutHigh,     GpioIntDis,                GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock  }}, // BT_RF_KILL_N
  {GPIO_VER1_N_GPP_D2,   {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntSmi,   GpioPlatformReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //EC_SMI_N
  {GPIO_VER1_N_GPP_D3,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //ONBOARD_X4_PCIE_SLOT1_PWREN_N
  {GPIO_VER1_N_GPP_D4,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //CAM2_PWREN
  {GPIO_VER1_N_GPP_D5,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //CRD_CAM_PWREN
  {GPIO_VER1_N_GPP_D6,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //LAN_RST_N
  {GPIO_VER1_N_GPP_D7,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //GPIO_ISOLATE_N
  {GPIO_VER1_N_GPP_D8,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //THC1_RST_N_TCH_PNL
  {GPIO_VER1_N_GPP_D9,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //M.2_WLAN_PERST_N
  {GPIO_VER1_N_GPP_D10,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //CAM2_RST_N
  {GPIO_VER1_N_GPP_D11,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //GPP_R_WWAN_PWREN

  {GPIO_VER1_N_GPP_D14,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //ONBOARD_X4_PCIE_SLOT1_DGPU_SEL
  {GPIO_VER1_N_GPP_D15,  {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntApic,  GpioPlatformReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //SPI_TPM_INT_N
  {GPIO_VER1_N_GPP_D16,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirIn,     GpioOutDefault,  GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //ISH_INT_DAT_ALS
  {GPIO_VER1_N_GPP_D17,  {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntSci,   GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //ONBOARD_X4_PCIE_SLOT1_WAKE_N

  {GPIO_VER1_N_GPP_E1,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //X1_PCIE_SLOT2_RTD3_RST_N
  {GPIO_VER1_N_GPP_E8,   {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntSci,   GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //UART_BT_WAKE_N

  // support from V2
  //{GPIO_VER1_N_GPP_F4,   {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntSci,   GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //X1_PCIE_SLOT2_WAKE_N

  {GPIO_VER1_N_GPP_H0,   {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntApic,  GpioPlatformReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //FPS_INT
  {GPIO_VER1_N_GPP_H11,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirIn,     GpioOutDefault,  GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //M.2_BT_I2S2_SCLK
  {GPIO_VER1_N_GPP_H14,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirIn,     GpioOutDefault,  GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //M.2_BT_I2S2_RXD
  {GPIO_VER1_N_GPP_H16,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //FPS_RST_N
  {GPIO_VER1_N_GPP_H18,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //TCH_PNL_PWR_EN
  {GPIO_VER1_N_GPP_H19,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //M2_CNVI_EN_N

  {GPIO_VER1_N_GPP_S1,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //SAR_DPR_PCH
  {0x0}
};

static GPIO_INIT_CONFIG mJslTouchPanelGpioTable[] =
{
  {GPIO_VER1_N_GPP_H18,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioPlatformReset,  GpioTermNone}},                         //TCH_PNL_PWR_EN
};

static GPIO_INIT_CONFIG mGpioTableJslEhlRvp[] =
{
  // M.2 Key-B WWAN
  {GPIO_VER1_N_GPP_B14,  {GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut, GpioOutHigh, GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PE_RST_N
  {GPIO_VER1_N_GPP_B17,  {GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut, GpioOutHigh, GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_WAKE_N
  {GPIO_VER1_N_GPP_E5,   {GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut, GpioOutHigh, GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_FCP_OFF_N
  {GPIO_VER1_N_GPP_H3,   {GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut, GpioOutHigh, GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_PWR_EN
  {GPIO_VER1_N_GPP_H17,  {GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut, GpioOutHigh, GpioIntDis, GpioPlatformReset, GpioTermNone}},  //M.2_WWAN_RST_N

  // Strap pins
  {GPIO_VER1_N_GPP_B10,  {GpioPadModeGpio, GpioHostOwnGpio, GpioDirIn, GpioOutDefault, GpioIntDis, GpioPlatformReset, GpioTermNone}},  //Boot Halt Strap
  {GPIO_VER1_N_GPP_A13,  {GpioPadModeGpio, GpioHostOwnGpio, GpioDirIn, GpioOutDefault, GpioIntDis, GpioPlatformReset, GpioTermNone}},  //Consent Strap
  {GPIO_VER1_N_GPP_E6,   {GpioPadModeGpio, GpioHostOwnGpio, GpioDirIn, GpioOutDefault, GpioIntDis, GpioPlatformReset, GpioTermNone}},  //JTAG ODT Enable
  {GPIO_VER1_N_GPP_B9,   {GpioPadModeGpio, GpioHostOwnGpio, GpioDirIn, GpioOutDefault, GpioIntDis, GpioPlatformReset, GpioTermNone}},  //eSPI Disable
  {0x0}
};

#endif // _ELKHARTLAKE_GPIO_TABLE_H_

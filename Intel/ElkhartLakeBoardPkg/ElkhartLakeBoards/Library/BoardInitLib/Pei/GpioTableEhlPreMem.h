/** @file
  Elkhartlake RVP/CRB GPIO definition table for Pre-Memory Initialization

@copyright
  Copyright (c) 2018 Intel Corporation. All rights reserved
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
#ifndef _ELKHARTLAKE_PREMEM_GPIO_TABLE_H_
#define _ELKHARTLAKE_PREMEM_GPIO_TABLE_H_

#include <Pins/GpioPinsVer1N.h>
#include <Pins/GpioPinsVer3.h>
#include <Library/GpioLib.h>
#include <Library/GpioConfig.h>

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTablePreMemEhl[] =
{
  {GPIO_VER3_GPP_E0,     {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,                   GpioPlatformReset,  GpioTermNone}},  // WWAN_FCP_OFF_N
  {GPIO_VER3_GPP_F21,    {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,                   GpioPlatformReset,  GpioTermNone}},  // WWAN_PWREN
  {GPIO_VER3_GPP_B14,    {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutLow,     GpioIntDis,                   GpioPlatformReset,  GpioTermNone}},  // WWAN_PERST_N
  {GPIO_VER3_GPP_B17,    {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntLevel | GpioIntSci,    GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock}},  // WWAN_WAKE_N
  {GPIO_VER3_GPP_V13,    {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutLow,     GpioIntDis,                   GpioPlatformReset,  GpioTermNone}},  // WWAN_RST_N
  {GPIO_VER3_GPD2,       {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntDis,                   GpioHostDeepReset,  GpioTermNone, GpioPadConfigUnlock}}, // LAN_WAKEB
  {GPIO_VER3_UFS_RESETB, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,                   GpioPlatformReset,  GpioTermNone}},  // UFS_RESETB
  {0x0}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTableMipiPreMemEhl[] =
{
  {GPIO_VER3_GPP_E14, { GpioPadModeGpio, GpioHostOwnDefault, GpioDirOut, GpioOutHigh, GpioIntDis, GpioResumeReset, GpioTermNone } },  //MIPI
  {0x0}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTablePreMemEhlSimics[] =
{
  {GPIO_VER3_GPP_E0,     {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,                   GpioPlatformReset,  GpioTermNone}},  // WWAN_FCP_OFF_N
  {GPIO_VER3_GPP_F21,    {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,                   GpioPlatformReset,  GpioTermNone}},  // WWAN_PWREN
  {GPIO_VER3_GPP_B14,    {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutLow,     GpioIntDis,                   GpioPlatformReset,  GpioTermNone}},  // WWAN_PERST_N
  {GPIO_VER3_GPP_B17,    {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntLevel | GpioIntSci,    GpioHostDeepReset,  GpioTermNone, GpioPadConfigUnlock}},  // WWAN_WAKE_N
  {GPIO_VER3_GPD2,       {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirInInv, GpioOutDefault, GpioIntDis,                   GpioHostDeepReset,  GpioTermNone, GpioPadConfigUnlock}}, // LAN_WAKEB
  {GPIO_VER3_UFS_RESETB, {GpioPadModeGpio, GpioHostOwnAcpi, GpioDirOut,   GpioOutHigh,    GpioIntDis,                   GpioPlatformReset,  GpioTermNone}},  // UFS_RESETB
  {0x0}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTableEhlWwanOnEarlyPreMem[] =
{
  {GPIO_VER3_GPP_F21,  { GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut,    GpioOutHigh,     GpioIntDis,               GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}},  //WWAN_PWREN
  {GPIO_VER3_GPP_E0,   { GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut,    GpioOutHigh,     GpioIntDis,               GpioResumeReset,    GpioTermNone}},                          //WWAN_FCP_OFF_N
  {GPIO_VER3_GPP_V13,  { GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut,    GpioOutHigh,     GpioIntDis,               GpioResumeReset,    GpioTermNone}},                          //WWAN_RST_N
  {GPIO_VER3_GPP_B14,  { GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut,    GpioOutHigh,     GpioIntDis,               GpioResumeReset,    GpioTermNone}},                          //WWAN_PERST_N
  {GPIO_VER3_GPP_B17,  { GpioPadModeGpio, GpioHostOwnGpio, GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntSci,  GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock}},    //WWAN_WAKE_N
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTableEhlWwanOffEarlyPreMem[] =
{
  {GPIO_VER3_GPP_V13,  { GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioResumeReset,    GpioTermNone}},                          //WWAN_RST_N
  {GPIO_VER3_GPP_B14,  { GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioResumeReset,    GpioTermNone}},                          //WWAN_PERST_N
  {GPIO_VER3_GPP_B17,  { GpioPadModeGpio, GpioHostOwnGpio, GpioDirInInv,  GpioOutDefault,  GpioIntLevel | GpioIntSci, GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock}},    //WWAN_WAKE_N
  {GPIO_VER3_GPP_E0,   { GpioPadModeGpio, GpioHostOwnGpio, GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioResumeReset,    GpioTermNone}},                          //WWAN_FCP_OFF_N
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTablePreMemJsl[] =
{
  {0x0}
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTableJslWwanOnEarlyPreMem[] =
{
  {GPIO_VER1_N_GPP_A10,  {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntSci,   GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //WWAN_WAKE_N
  {GPIO_VER1_N_GPP_E3,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_FCP_OFF_N
  {GPIO_VER1_N_GPP_S0,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_RST_N
  {GPIO_VER1_N_GPP_C0,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_PERST_N
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTableJslWwanOffEarlyPreMem[] =
{
  {GPIO_VER1_N_GPP_C0,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_PERST_N
  {GPIO_VER1_N_GPP_S0,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_RST_N
  {GPIO_VER1_N_GPP_E3,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_FCP_OFF_N
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTableJslEhlRvpWwanOnEarlyPreMem[] =
{
  {GPIO_VER1_N_GPP_B17,  {GpioPadModeGpio,  GpioHostOwnAcpi,  GpioDirInInv,  GpioOutDefault,  GpioIntLevel|GpioIntSci,   GpioHostDeepReset,  GpioTermNone,  GpioPadConfigUnlock  }}, //WWAN_WAKE_N
  {GPIO_VER1_N_GPP_E5,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_FCP_OFF_N
  {GPIO_VER1_N_GPP_H17,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_RST_N
  {GPIO_VER1_N_GPP_B14,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutHigh,     GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_PERST_N
};

GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTableJslEhlRvpWwanOffEarlyPreMem[] =
{
  {GPIO_VER1_N_GPP_B14,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_PERST_N
  {GPIO_VER1_N_GPP_H17,  {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_RST_N
  {GPIO_VER1_N_GPP_E5,   {GpioPadModeGpio,  GpioHostOwnGpio,  GpioDirOut,    GpioOutLow,      GpioIntDis,                GpioResumeReset,    GpioTermNone,  GpioOutputStateUnlock}}, //WWAN_FCP_OFF_N
};

#endif // _ELKHARTLAKE_PREMEM_GPIO_TABLE_H_

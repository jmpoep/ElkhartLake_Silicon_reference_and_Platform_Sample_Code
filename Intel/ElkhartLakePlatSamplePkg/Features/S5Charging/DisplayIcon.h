/** @file
  Header file for Display Icon.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _DISPLAY_ICON_H_
#define _DISPLAY_ICON_H_

#include <Protocol/GraphicsOutput.h>
#include <Protocol/HiiFont.h>

//
// Icon display default Values
//
#define DEFAULT_BLOCKWIDTH          100
#define DEFAULT_BLOCKHEIGHT         200
#define DEFAULT_BLOCKNUM            1
#define DEFAULT_POSX                100
#define DEFAULT_POSY                100

//
// This is the timer interval
//
#define CHARGING_TIMER_INTERVAL     (1000 * 10000) // 1s
#define ICON_DISPLAY_TIME_CONFIG    (5000 * 10000) // 5s
#define CONVERSION_COFICIENT 5
#define RSENSE_VALUE 10
//
// Maximum brightness display for S5 Charging
//
#define MAX_BRIGHTNESS_SETTING      10
#define MIN_BRIGHTNESS_SETTING      0


//
// DisplayIcon
//
EFI_STATUS
DisplayIcon (
  UINT32 SOC
  );

VOID
ClearDisplay (
  VOID
  );

EFI_STATUS
DisconnectDisplay (
  VOID
  );

EFI_STATUS
ConnectDisplay (
  VOID
  );

VOID
Ellipse (
  UINT8                         Orientation,
  INT32                         xc,
  INT32                         yc,
  INT32                         rx,
  INT32                         ry,
  UINT8                         FillFlag,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL fillColor[],
  UINT16                        PatternLength,
  UINT8                         Percentage
  );

VOID
DrawEllipse (
  UINT8                         Orientation,
  UINT32                        xc,
  UINT32                        yc,
  UINT32                        x,
  UINT32                        y,
  UINT8                         FillFlag,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL fillColor[],
  UINT16                        PatternLength,
  UINT8                         Percentage
  );

VOID
DrawBatteryIconPortrait (
  UINTN                         PosX,
  UINTN                         PosY,
  UINTN                         BatteryWidth,
  UINTN                         BatteryHeight,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern[],
  UINT8                         FillFlag,
  UINT16                        PatternLength
  );

VOID
FillBatteryIcon (
  UINT8  Orientation,
  UINTN  PosX,
  UINTN  PosY,
  UINTN  BatteryWidth,
  UINTN  BatteryHeight,
  UINT32 StageOfCharge
  );

VOID
TopSurfaceOfBattery (
  UINT8                         Orientation,
  UINTN                         PosX,
  UINTN                         PosY,
  UINTN                         BatteryWidth,
  UINTN                         BatteryHeight,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern[],
  UINT8                         FillFlag,
  UINT16                        PatternLength
  );

VOID
DisplayWirelessCharger (
  UINT8                         Orientation,
  UINTN                         PosX,
  UINTN                         PosY,
  UINTN                         BatteryWidth,
  UINTN                         BatteryHeight,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern[],
  UINT8                         FillFlag,
  UINT16                        PatternLength,
  EFI_HII_FONT_PROTOCOL         *FontProtocol
  );

VOID
DisplayPlug (
  UINT8  Orientation,
  UINTN  PosX,
  UINTN  PosY,
  UINTN  BatteryWidth,
  UINTN  BatteryHeight,
  UINT16 XRef,
  UINT16 YRef,
  UINT16 PlugWidth,
  UINT16 PlugHeight,
  UINT16 PlugType,
  UINT16 WireLength
  );

VOID
DisplayWiredCharger (
  UINT8                 Orientation,
  UINTN                 PosX,
  UINTN                 PosY,
  UINTN                 BatteryWidth,
  UINTN                 BatteryHeight,
  EFI_HII_FONT_PROTOCOL *FontProtocol
  );

EFI_STATUS
DisplayString (
  EFI_STRING                    DString,
  UINT16                        CenterX,
  UINT16                        CenterY,
  UINT8                         ZoomScale,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ForegroundColor,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL BackgroundColor,
  EFI_HII_FONT_PROTOCOL         *FontProtocol
  );

VOID
RefreshBlock (
  UINTN                         XTopLeft,
  UINTN                         YTopLeft,
  UINTN                         XSize,
  UINTN                         YSize,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL BackgroundColor
  );

VOID
DisplayUsbLogo (
  UINT16 XRef,
  UINT16 YRef,
  UINT16 Height
  );

#endif

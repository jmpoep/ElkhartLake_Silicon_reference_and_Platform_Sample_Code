/** @file
  Display Icon function

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/PrintLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/UgaDraw.h>

#include <Library/TimerLib.h>

#include<Protocol/HiiFont.h>
#include<Protocol/HiiImage.h>

#include "HardwareInterface.h"
#include "StateMachine.h"
#include "GopControl.h"
#include "DisplayIcon.h"
#include "S5Charging.h"


EFI_GRAPHICS_OUTPUT_BLT_PIXEL        mGraphicsColors[16] = {
  {0x00, 0x00, 0x00, 0x00},  // BLACK
  {0x98, 0x00, 0x00, 0x00},  // LIGHTBLUE
  {0x00, 0x98, 0x00, 0x00},  // LIGHGREEN
  {0x98, 0x98, 0x00, 0x00},  // LIGHCYAN
  {0x00, 0x00, 0x98, 0x00},  // LIGHRED
  {0x98, 0x00, 0x98, 0x00},  // MAGENTA
  {0x00, 0x98, 0x98, 0x00},  // BROWN
  {0x98, 0x98, 0x98, 0x00},  // LIGHTGRAY
  {0x30, 0x30, 0x30, 0x00},  // DARKGRAY - BRIGHT BLACK
  {0xff, 0x00, 0x00, 0x00},  // BLUE
  {0x00, 0xff, 0x00, 0x00},  // LIME
  {0xff, 0xff, 0x00, 0x00},  // CYAN
  {0x00, 0x00, 0xff, 0x00},  // RED
  {0xff, 0x00, 0xff, 0x00},  // FUCHSIA
  {0x00, 0xff, 0xff, 0x00},  // YELLOW
  {0xff, 0xff, 0xff, 0x00}   // WHITE
};
EFI_GRAPHICS_OUTPUT_BLT_PIXEL DisplayBackgroundColor;

GOP_DISPLAY_BRIGHTNESS_PROTOCOL  *mGopDisplayProtocol;

//locations changed
EFI_GRAPHICS_OUTPUT_PROTOCOL *GraphicsOutput;
UINTN BlockHeight;
UINTN BlockWidth;
//end of locations changed
UINT16 BottomIndex = 0, TopIndex = 0;   //(PatternLength-1);
UINT16 PrevBottomIndex = 0, PrevTopIndex = 0;
UINT8 DisplayOrientation = 0;   //0 for landscape 1 for Portrait
UINT8 DisplayTime = 10;   //display icon time in seconds
UINT8 FastChargingFlag = 0;


VOID
ClearDisplay (
  VOID
  )
/*++

Routine Description:
   Clear the display after a certain number of ticks.
Arguments:
   None.
Returns:
   None
--*/
{
  UINTN                           MaxRows = 0;
  UINTN                           MaxColumns = 0;

  DEBUG ((EFI_D_INFO, "[ClearDisplay] Start\n"));
  DEBUG ((EFI_D_INFO, "[ClearDisplay] CTics = %d  mMaxDisplayClockTics=%d\n", mDisplayInterface.ClockTicks, mMaxDisplayClockTicks));

  if (mDisplayInterface.ClockTicks > mMaxDisplayClockTicks) {
    mDisplayInterface.ClockTicks = 0;
    gST->ConOut->ClearScreen (gST->ConOut);
    gST->ConOut->QueryMode (gST->ConOut, gST->ConOut->Mode->Mode, &MaxColumns, &MaxRows);
    gST->ConOut->SetCursorPosition (gST->ConOut, (MaxColumns / 2 - 10), (MaxRows - 5));
  } else if (mDisplayInterface.ClockTicks > 0) {
    mDisplayInterface.ClockTicks++;
  } else {
    mDisplayInterface.ClockTicks = 0;
  }

  return;
}

EFI_STATUS
DisplayIcon (
  UINT32 StageOfCharge
  )
/*++

Routine Description:
   Display the icon on the screen wth the percentage bar proportional to StageOfCharge.
Arguments:
   StageOfCharge : the percentage of charge on the battery.
Returns:
   EFI_SUCCESS: Successfully displayed.
--*/
{
  EFI_STATUS                      Status;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *ConOut;
  EFI_HII_FONT_PROTOCOL           *FontProtocol;
  EFI_HII_IMAGE_PROTOCOL          *ImageProtocol;

  UINTN BlockNum;
  UINTN PosX;
  UINTN PosY;
  UINT32 SizeOfX = 0;
  UINT32 SizeOfY = 0;
  UINT16 i = 0;

  UINTN BatteryHeight = 360;   //390//420
  UINTN BatteryWidth = 200;   //220//240

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL FillColor, FgColor, BgColor;

  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern[180];
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL batteryColorPattern[200 + 10];   //batterywidth=200
  EFI_STRING StringStageOfCharge = L"100%";
  UINTN IncrementStep;

  Status = EFI_SUCCESS;
  DisplayBackgroundColor = mGraphicsColors[15]; //15 white 0 black

  DEBUG ((EFI_D_INFO, "[DisplayIcon] Start\n"));

  BlockWidth = DEFAULT_BLOCKWIDTH;
  BlockHeight = DEFAULT_BLOCKHEIGHT;
  BlockNum = DEFAULT_BLOCKNUM;
  PosX = DEFAULT_POSX;
  PosY = DEFAULT_POSY;

  BottomIndex = 0;
  TopIndex = 0; //(PatternLength-1);
  PrevBottomIndex = 0;
  PrevTopIndex = 0;

  StringStageOfCharge = AllocateZeroPool (4 * sizeof (EFI_STRING));
  if (StringStageOfCharge == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  if (mDisplayInterface.ClockTicks) {
    // do not go through display mechanism again
    return EFI_SUCCESS;
  } else {
    // start the clockticks.
    // once the clockticks start, they will be continuously
    // incremented until max number of clockticks is reached.
    // the screen will be cleared (through ClearDisplay() )
    // when this happens.
    mDisplayInterface.ClockTicks++;
  }

  gBS->LocateProtocol (
         &gEfiSimpleTextOutProtocolGuid,
         NULL,
         (VOID**) &ConOut
         );

  gBS->LocateProtocol (
         &gEfiGraphicsOutputProtocolGuid,
         NULL,
         (VOID**) &GraphicsOutput
         );

  Status = gBS->LocateProtocol (
                  &gEfiHiiFontProtocolGuid,
                  NULL,
                  (VOID **) &FontProtocol
                  );
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_INFO, "[EfiHiiFontProtocol] Error in Locating EFI_FONT protocol\n"));
    Print (L" Error in Locating EFI_FONT protocol  %r\n", Status);
  }
  Status = gBS->LocateProtocol (
                  &gEfiHiiImageProtocolGuid,
                  NULL,
                  (VOID **) &ImageProtocol
                  );
  if (EFI_ERROR(Status)) {
    DEBUG((EFI_D_INFO, "[efiHiiFontProtocol] Error in Locating Image protocol\n"));
    Print (L" Error in Locating Image protocol  %r\n", Status);
  }
  Status = gBS->HandleProtocol (gST->ConsoleOutHandle, &gEfiGraphicsOutputProtocolGuid, (VOID **) &GraphicsOutput);

  if (EFI_ERROR(Status)) {
    gBS->Stall (1000 * 1000);
    return EFI_DEVICE_ERROR;
  }

  gST->ConOut->EnableCursor (gST->ConOut, FALSE); //Disable cursor
  gST->ConOut->ClearScreen (gST->ConOut); //Clear screen

  SizeOfX = GraphicsOutput->Mode->Info->HorizontalResolution;
  SizeOfY = GraphicsOutput->Mode->Info->VerticalResolution;

  // Center Position
  PosX = SizeOfX / 2;
  PosY = SizeOfY / 2;
  //background color
  Status = GraphicsOutput->Blt (
                            GraphicsOutput,
                            &DisplayBackgroundColor,
                            EfiBltVideoFill,
                            0,
                            0,
                            0,
                            0,
                            PosX * 2,
                            PosY * 2,
                            (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                            );

  if (StageOfCharge < 10) {
    i = (UINT16) StageOfCharge + 48;
    StringStageOfCharge[0] = i;
    StringStageOfCharge[1] = '%';
    StringStageOfCharge[2] = '\0';
  } else if (StageOfCharge < 100) {
    i = (UINT16) StageOfCharge / 10 + 48;
    StringStageOfCharge[0] = i;
    i = (UINT16) StageOfCharge % 10 + 48;
    StringStageOfCharge[1] = i;
    StringStageOfCharge[2] = '%';
    StringStageOfCharge[3] = '\0';
  } else {
    StringStageOfCharge[0] = '1';
    StringStageOfCharge[1] = '0';
    StringStageOfCharge[2] = '0';
    StringStageOfCharge[3] = '%';
    StringStageOfCharge[4] = '\0';
  }

  //graypattern dark 60-220 light  220-60=  160

  IncrementStep = 160 / (BatteryWidth / 3);

  if (IncrementStep == 0) {
    IncrementStep = 1;
  }
  //Print(L"Increment Step %d\n\n",IncrementStep);
  FillColor.Red = 60;
  FillColor.Green = 60;
  FillColor.Blue = 60;
  FillColor.Reserved = 60;
  batteryColorPattern[0] = FillColor;

  for (i = 0; i < (UINT16) (BatteryWidth / 3); i++) {
    FillColor.Red = FillColor.Red + (UINT8) IncrementStep;
    FillColor.Green = FillColor.Green + (UINT8) IncrementStep;
    FillColor.Blue = FillColor.Blue + (UINT8) IncrementStep;
    FillColor.Reserved = 0;
    batteryColorPattern[i] = FillColor;
    //Print(L" %d",(FillColor.Red));
  }

  IncrementStep = (BatteryWidth * 2 / 3) / 160;
  if (IncrementStep == 0) {
    IncrementStep = 160 / (BatteryWidth * 2 / 3);
    if (IncrementStep == 0) {
      IncrementStep = 1;
    }
  }
  //Print(L"\n\nIncrement Step2 %d",IncrementStep);

  for (; i < (UINT16) (BatteryWidth + 10); i++) {
    batteryColorPattern[i].Red = batteryColorPattern[i - 1].Red - (UINT8) IncrementStep;
    batteryColorPattern[i].Green = batteryColorPattern[i - 1].Green - (UINT8) IncrementStep;
    batteryColorPattern[i].Blue = batteryColorPattern[i - 1].Blue - (UINT8) IncrementStep;
    batteryColorPattern[i].Reserved = 0;
    //  Print(L": %d",(batteryColorPattern[i-1].Red-(UINT8)IncrementStep));

    if ((batteryColorPattern[i].Red - IncrementStep) < 1) {
      batteryColorPattern[i].Red = 0;
      batteryColorPattern[i].Green = 0;
      batteryColorPattern[i].Blue = 0;
      batteryColorPattern[i].Reserved = 0;
    }
  }

  DisplayOrientation = 1;

  ColorPattern[0].Red = 240;
  ColorPattern[0].Green = 240;
  ColorPattern[0].Blue = 240;
  ColorPattern[0].Reserved = 0;
  Ellipse (
    DisplayOrientation,
    (UINT32) PosX + 10,
    (UINT32) PosY,
    (UINT32) (BatteryHeight / 2 + BatteryWidth / 3),
    (UINT32) (BatteryHeight / 2 + BatteryWidth / 3),
    (UINT8) 1,
    ColorPattern,
    1,
    100
    );

  ColorPattern[0].Red = 220;
  ColorPattern[0].Green = 220;
  ColorPattern[0].Blue = 220;
  ColorPattern[0].Reserved = 0;
  Ellipse (
    DisplayOrientation,
    (UINT32) PosX + 10,
    (UINT32) PosY,
    (UINT32) (BatteryHeight / 2 + BatteryWidth / 2),
    (UINT32) (BatteryHeight / 2 + BatteryWidth / 2),
    (UINT8) 7,
    ColorPattern,
    (UINT16) 10,
    100
    );

  //DrawBatteryIconLandscap(PosX,PosY,BatteryWidth,BatteryHeight,batteryColorPattern,1,1);
  DrawBatteryIconPortrait (PosX, PosY, BatteryWidth, BatteryHeight, batteryColorPattern, 1, 1);

  //Orientation 0 means landscape 1:portrait
  FillBatteryIcon (1, PosX, PosY, BatteryWidth, BatteryHeight, StageOfCharge);

  //FillBatteryIconLandscap(UINT8 Orientation, UINTN PosX,UINTN PosY,UINTN BatteryWidth,UINTN BatteryHeight,EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern[],UINT8 FillFlag,UINT16 PatternLength);
  //-------------------------------------------------------------------------------------------------------------------------

  ColorPattern[0] = mGraphicsColors[15];
  TopSurfaceOfBattery (
    1,
    PosX,
    PosY,
    BatteryWidth,
    BatteryHeight,
    batteryColorPattern,
    1,
    (UINT16) (BatteryWidth + 10)
    );

  BgColor.Red = 0;
  BgColor.Green = 0;
  BgColor.Blue = 0;
  BgColor.Reserved = 0;
  FgColor.Red = 0;
  FgColor.Green = 0;
  FgColor.Blue = 255;
  FgColor.Reserved = 0;

  DisplayString (StringStageOfCharge, (UINT16) PosX + 10, (UINT16) (PosY), 3, FgColor, BgColor, FontProtocol);

  //
  // TODO: Code different charger display here:
  //
  DisplayWiredCharger (1, PosX, PosY, BatteryWidth, BatteryHeight, FontProtocol);

  return EFI_SUCCESS;
}

VOID
DisplayUsbLogo (
  UINT16 XRef,
  UINT16 YRef,
  UINT16 Height
  )
{
  EFI_STATUS Status = EFI_SUCCESS;

  UINT16 Width = 2 * Height / 5;
  UINT16 VLWidth = Width / 9;
  UINT16 EdgeLength = 4 * VLWidth;  //3
  UINT16 DownCircleRadius = 2 * VLWidth;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL FillColor[1];

  UINT16 VLHeight = Height - EdgeLength * 2 / 3 - 2 * DownCircleRadius;

  UINT16 i, j;

  j = 0;
  FillColor[0].Red = 190;
  FillColor[0].Green = 190;
  FillColor[0].Blue = 190;
  FillColor[0].Reserved = 0;

  //for top triangle
  for (i = 0; i < (2 * EdgeLength) / 3; i++) {
    Status = GraphicsOutput->Blt (
                              GraphicsOutput,
                              &FillColor[0],
                              EfiBltVideoFill,
                              0,
                              0,
                              XRef - i,
                              YRef + i,
                              1,
                              2 * EdgeLength / 3 - i,
                              0
                              );
  }
  for (i = 0; i < (2 * EdgeLength) / 3; i++) {
    Status = GraphicsOutput->Blt (
                              GraphicsOutput,
                              &FillColor[0],
                              EfiBltVideoFill,
                              0,
                              0,
                              XRef + i,
                              YRef + i,
                              1,
                              2 * EdgeLength / 3 - i,
                              0
                              );
  }
  //top triangle ned
  //vericle line
  Status = GraphicsOutput->Blt (
                            GraphicsOutput,
                            &FillColor[0],
                            EfiBltVideoFill,
                            0,
                            0,
                            XRef - VLWidth / 2,
                            YRef + i,
                            VLWidth,
                            VLHeight,
                            0
                            );
  //down circle
  Ellipse (
    1,
    XRef,
    YRef + Height - DownCircleRadius * 2,
    DownCircleRadius,
    DownCircleRadius,
    (UINT8) 1,
    FillColor,
    1,
    100
    );

  //right angular line
  for (i = 0; i < (Width / 3 + 3); i++) {
    Status = GraphicsOutput->Blt (
                              GraphicsOutput,
                              &FillColor[0],
                              EfiBltVideoFill,
                              0,
                              0,
                              XRef + i,
                              YRef + (Height * 55) / 100 - i,
                              1,
                              VLWidth,
                              0
                              );
  }

  i = i - 3;
  Status = GraphicsOutput->Blt (
                            GraphicsOutput,
                            &FillColor[0],
                            EfiBltVideoFill,
                            0,
                            0,
                            XRef + i,
                            YRef + (Height * 55) / 100 - i - Width / 4,
                            VLWidth,
                            Width / 4 + VLWidth * 2 / 3 - 2,
                            0
                            );

  Status = GraphicsOutput->Blt (
                            GraphicsOutput,
                            &FillColor[0],
                            EfiBltVideoFill,
                            0,
                            0,
                            XRef + i - EdgeLength * 2 / 6 + VLWidth / 2,
                            YRef + (Height * 55) / 100 - i - Width / 3 - EdgeLength / 2,
                            EdgeLength * 2 / 3,
                            EdgeLength * 2 / 3,
                            0
                            );

  //left angular line
  for (i = 0; i < (Width / 3 + 3); i++) {
    Status = GraphicsOutput->Blt (
                              GraphicsOutput,
                              &FillColor[0],
                              EfiBltVideoFill,
                              0,
                              0,
                              XRef - i,
                              YRef + Height * 70 / 100 - i,
                              1,
                              VLWidth,
                              0
                              );
  }
  i = i - 3;
  Status = GraphicsOutput->Blt (
                            GraphicsOutput,
                            &FillColor[0],
                            EfiBltVideoFill,
                            0,
                            0,
                            XRef - i - VLWidth,
                            YRef + Height * 70 / 100 - i - Width / 4,
                            VLWidth,
                            Width / 4 + VLWidth * 2 / 3 - 2,
                            0
                            );

  Ellipse (
    1,
    XRef - i - VLWidth / 2,
    YRef + Height * 70 / 100 - i - Width / 4 - DownCircleRadius * 8 / 10,
    DownCircleRadius * 8 / 10,
    DownCircleRadius * 8 / 10,
    (UINT8) 1,
    FillColor,
    1,
    100
    );

}



EFI_STATUS
DisplayString (
  EFI_STRING                    DString,
  UINT16                        CenterX,
  UINT16                        CenterY,
  UINT8                         ZoomScale,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL FgColor,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL BgColor,
  EFI_HII_FONT_PROTOCOL         *FontProtocol
  )
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT16 i = 0, j = 0, k, l, m, n;
  EFI_HII_OUT_FLAGS Flags;
  EFI_IMAGE_OUTPUT *Blt1 = NULL;
  EFI_IMAGE_OUTPUT *BltZoomed = NULL;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL *TempPixel = NULL;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL *TempPixel2 = NULL;
  EFI_FONT_DISPLAY_INFO *FontInfo1 = NULL;
  EFI_HII_ROW_INFO *RowInfoArray = NULL;
  UINTN RowInfoArraySize;
  UINT16 ImageSize;
  UINT16 Counter = 0;
  UINT8 StrLength;
  UINT16 Width1;
  UINT16 Height1;
  EFI_STRING MyFont = L"Times New Roman";

  BltZoomed = (EFI_IMAGE_OUTPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (BltZoomed == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Blt1 = (EFI_IMAGE_OUTPUT *) AllocateZeroPool (sizeof(EFI_IMAGE_OUTPUT));
  if (Blt1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  Blt1->Image.Screen = GraphicsOutput;

  FontInfo1 = (EFI_FONT_DISPLAY_INFO *) AllocateZeroPool (sizeof(EFI_FONT_DISPLAY_INFO));
  if (FontInfo1 == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  for (StrLength = 0; DString[StrLength] != '\0'; StrLength++);  //calculation of length of string

  Width1 = 10 * ZoomScale * StrLength;
  Height1 = 20 * ZoomScale;

  Blt1->Width = Width1 / ZoomScale;
  Blt1->Height = Height1 / ZoomScale;
  // Height1=20*ZoomScale*3;
  FontInfo1->BackgroundColor = BgColor;
  FontInfo1->ForegroundColor = FgColor;
  FontInfo1->FontInfo.FontSize = 90;
  FontInfo1->FontInfo.FontStyle = 0;

  for (i = 0; MyFont[i] != '\0'; i++) {
    FontInfo1->FontInfo.FontName[i] = MyFont[i];
  }
  FontInfo1->FontInfo.FontName[i] = '\0';

  FontInfo1->FontInfo.FontStyle |= EFI_HII_FONT_STYLE_BOLD | EFI_HII_FONT_STYLE_SHADOW;
  //FontInfo1->FontInfoMask=  EFI_FONT_INFO_SYS_FONT|EFI_FONT_INFO_SYS_STYLE|EFI_FONT_INFO_RESIZE;
  FontInfo1->FontInfoMask = 0;
  //FontInfo1->FontInfoMask|=EFI_FONT_INFO_SYS_STYLE | EFI_FONT_INFO_RESIZE | EFI_FONT_INFO_SYS_BACK_COLOR|EFI_FONT_INFO_SYS_FONT;// EFI_FONT_INFO_ANY_SIZE;//EFI_FONT_INFO_RESIZE;// EFI_FONT_INFO_SYS_STYLE;
  FontInfo1->FontInfoMask |= EFI_FONT_INFO_SYS_BACK_COLOR | EFI_FONT_INFO_SYS_SIZE; // EFI_FONT_INFO_ANY_SIZE;//EFI_FONT_INFO_RESIZE;// EFI_FONT_INFO_SYS_STYLE;

  Flags = 0;
  Flags |= EFI_HII_OUT_FLAG_CLIP;
  Blt1->Image.Screen = NULL;
  Blt1->Image.Bitmap = AllocateZeroPool (Blt1->Width * Blt1->Height * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));
  Status = FontProtocol->StringToImage (
                           FontProtocol,
                           EFI_HII_IGNORE_IF_NO_GLYPH | EFI_HII_OUT_FLAG_CLIP | EFI_HII_OUT_FLAG_CLIP_CLEAN_X | EFI_HII_OUT_FLAG_CLIP_CLEAN_Y,
                           DString,
                           FontInfo1,
                           &Blt1,
                           0,
                           0,
                           &RowInfoArray,
                           &RowInfoArraySize,
                           NULL
                           );
  if (EFI_ERROR(Status)) {
    Print (L"Error in generating string : %r", Status);
  }

  BltZoomed->Image.Screen = NULL;
  BltZoomed->Image.Bitmap = AllocateZeroPool (Width1 * Height1 * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL));

  if (BltZoomed->Image.Bitmap == NULL) {
    Print (L"EFI_OUT_OF_RESOURCES");
  }

  TempPixel2 = NULL;

  j = 0;
  ImageSize = (UINT16) (Blt1->Width * Blt1->Height);

  TempPixel = NULL;

  m = (Blt1->Width) * (ZoomScale) * (ZoomScale);
  n = 0;
  i = 0;
  j = 0;
  while (i < (ImageSize)) {
    TempPixel = Blt1->Image.Bitmap + i; //*sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);

    n = (i / (Blt1->Width));
    for (k = 0; k < (ZoomScale); k++) {
      for (l = 0; l < (ZoomScale); l++) {
        //TempPixel2= BltZoomed->Image.Bitmap+(j+l)+k*Width1;//*sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
        //TempPixel2= BltZoomed->Image.Bitmap+n*m+l+(i%Width1)*ZoomScale+Width1*k;//    (j+l)+k*Width1;//*sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);
        TempPixel2 = BltZoomed->Image.Bitmap + n * m + l + (i % (Blt1->Width)) * ZoomScale + (Width1) * k; //    (j+l)+k*Width1;//*sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);

        TempPixel2->Red = TempPixel->Red;
        TempPixel2->Green = TempPixel->Green;
        TempPixel2->Blue = TempPixel->Blue;
        TempPixel2->Reserved = TempPixel->Reserved;
      }
    }
    i++;
  }
  Counter = 0;
  for (i = 0; i < Height1; i++) {
    for (j = 0; j < Width1; j++) {
      TempPixel = BltZoomed->Image.Bitmap + Counter;    //*sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL);

      //Print(L"%d %d %d     --    ",TempPixel->Red,TempPixel->Green,TempPixel->Blue);
      if (!(TempPixel->Red < 10 && TempPixel->Green < 10 && TempPixel->Blue < 10)) {
        Status = GraphicsOutput->Blt (
                                  GraphicsOutput,
                                  TempPixel,
                                  EfiBltVideoFill,
                                  0,
                                  0,
                                  CenterX - (RowInfoArray->LineWidth * ZoomScale) / 2 + j,
                                  CenterY - RowInfoArray->LineHeight + i,
                                  2,
                                  2,
                                  // ( Blt1->Width )* sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                  (Width1) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                  );
      }
      Counter++;
    }
  }

  //free up all the allocated buffer
  FreePool (Blt1->Image.Bitmap);
  FreePool (BltZoomed->Image.Bitmap);
  FreePool (Blt1);
  FreePool (BltZoomed);
  if (TempPixel == NULL) {
    FreePool (TempPixel);
  }
  if (TempPixel2 == NULL) {
    FreePool (TempPixel2);
  }

  return Status;
}



VOID
DisplayWiredCharger (
  UINT8                 Orientation,
  UINTN                 PosX,
  UINTN                 PosY,
  UINTN                 BatteryWidth,
  UINTN                 BatteryHeight,
  EFI_HII_FONT_PROTOCOL *FontProtocol
  )
{
  EFI_STRING                    StringFastCharging = L"Fast Charging";
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL BgColor;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL FgColor;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL FillColor2[1];

  UINT16 PlugWidth;
  UINT16 PlugHeight;
  UINT16 PlugWidth2;
  UINT16 PlugHeight2;
  UINT16 WireHeight;
  UINT16 Xref1, Xref2;
  UINT16 Yref1, Yref2, j, i;

  PlugWidth = (UINT16) (BatteryWidth / 2);
  PlugHeight = (UINT16) (BatteryWidth * 8 / 10);
  Xref1 = (UINT16) (PosX - PlugWidth / 2);
  Yref1 = (UINT16) (PosY + BatteryHeight / 2 + 60);

  PlugWidth2 = (UINT16) (BatteryWidth * 2 / 3);
  PlugHeight2 = (UINT16) (BatteryWidth * 3 / 4);  //(BatteryWidth*2/3);
  Xref2 = (UINT16) (PosX + BatteryHeight / 2);
  Yref2 = (UINT16) (PosY);
  WireHeight = (Yref2 + PlugHeight2 + PlugHeight2 / 2 - Yref1 + PlugHeight + PlugHeight);
  //calculate length of string

  FillColor2[0].Red = 30;
  FillColor2[0].Green = 30;
  FillColor2[0].Blue = 30;
  FillColor2[0].Reserved = 0;
  j = PlugHeight2 * 55 / 400;
  //quarter circular wire
  for (i = 2; i < (j + 2); i++) {
    Ellipse (
      1,
      Xref1 + (Xref2 - Xref1) / 2 + PlugWidth / 2 + j / 3,
      Yref1 + PlugHeight + PlugHeight / 2 - 24 + j / 2,
      (Xref2 - Xref1) / 2 + 10 - i + j / 2,
      (Xref2 - Xref1) / 2 - i + j / 2,
      (UINT8) 6,
      FillColor2,
      j,
      100
      );
    FillColor2[0].Red = FillColor2[0].Red + 3;
    FillColor2[0].Green = FillColor2[0].Green + 3;
    FillColor2[0].Blue = FillColor2[0].Blue + 3;
  }

  DisplayPlug (1, PosX, PosY, BatteryWidth, BatteryHeight, Xref1, Yref1, PlugWidth, PlugHeight, 1, 0);  //usb plug
  //DisplayPlug2(1, PosX, PosY, BatteryWidth, BatteryHeight,Xref2,Yref2,PlugWidth2,PlugHeight2,2,WireHeight);//normal plug

  //hr1=(UINT8)(Time/60);
  //min1=Time%60;
#if 0
  j=0;
  if (hr1>0)
  {
    FullFlag=0;
    if (hr1<10)
    StringTime[j++]=(UINT16)hr1+48;
    else
    {
      StringTime[j++]=(UINT16)hr1/10+48;
      StringTime[j++]=(UINT16)hr1%10+48;
    }
    StringTime[j++]=' ';
    StringTime[j++]='H';
    StringTime[j++]='r';
    StringTime[j++]=' ';
  }
  if (min1>0)
  {
    FullFlag=0;
    if (min1<10)
    StringTime[j++]=(UINT16)min1+48;
    else
    {
      StringTime[j++]=(UINT16)min1/10+48;
      StringTime[j++]=(UINT16)min1%10+48;
    }
    StringTime[j++]=' ';
    StringTime[j++]='M';
    StringTime[j++]='i';
    StringTime[j++]='n';
    StringTime[j++]=' ';
  }
  for (i=0;StringEstimated[i]!='\0';i++)
  StringTime[j++]=StringEstimated[i];
  StringTime[j++]='\0';
#endif

  BgColor.Red = 0;
  BgColor.Green = 0;
  BgColor.Blue = 0;
  BgColor.Reserved = 0;
  FgColor.Red = 0;
  FgColor.Green = 0;
  FgColor.Blue = 255;
  FgColor.Reserved = 0;

#if 0
  if (FullFlag==0)
  DisplayString(StringTime,(UINT16)PosX+10,(UINT16)(Yref1+PlugHeight2+PlugHeight2+PlugHeight2),2,FgColor,BgColor,FontProtocol);
  else
  DisplayString(FullyCharged,(UINT16)PosX+10,(UINT16)(Yref1+PlugHeight2+PlugHeight2+PlugHeight2),2,FgColor,BgColor,FontProtocol);
#endif

  if (FastChargingFlag == 1) {
    for (i = 0; i < DisplayTime * 3; i++) {
      gBS->Stall (1000000 / 3);  //in seconds its a one second
      if (FastChargingFlag == 0) {
        FgColor.Red = 255;
        FgColor.Green = 0;
        FgColor.Blue = 0;
        FastChargingFlag = 1;
      } else {
        FgColor.Red = 0;
        FgColor.Green = 0;
        FgColor.Blue = 255;
        FastChargingFlag = 0;
      }
      DisplayString (
        StringFastCharging,
        (UINT16) PosX + 10,
        (UINT16) (Yref1 + PlugHeight2 + PlugHeight2 / 2 + PlugHeight2),
        3,
        FgColor,
        BgColor,
        FontProtocol
        );

    }

  }
}


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
  UINT16 WireHeight
  )
{
  //1 for USB plug 2 for Charger Connector port
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern2[1];
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL PlugColor;
  EFI_STATUS                    Status;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern3[50];

  UINT16 PlugMidRegion = PlugWidth * 2 / 3;
  UINT16 PlugSideRegion = PlugWidth / 6;
  UINT16 PinHeight = PlugHeight * 55 / 100;
  UINT16 PinWidth = PinHeight / 4;
  UINT8 Increment = 0;
  UINT16 i, j;  //,k;

  Status = EFI_SUCCESS;
  PlugColor.Red = 30;
  PlugColor.Green = 30;
  PlugColor.Blue = 30;
  PlugColor.Reserved = 0;
  ColorPattern2[0] = PlugColor;
  j = PlugSideRegion;
  //plug left side region

  ColorPattern3[0].Red = 30;  //60
  ColorPattern3[0].Green = 30;
  ColorPattern3[0].Blue = 30;
  ColorPattern3[0].Reserved = 0;

  for (i = 1; i < 13; i++) {
    ColorPattern3[i].Red = ColorPattern3[i - 1].Red + 6;
    ColorPattern3[i].Green = ColorPattern3[i - 1].Green + 6;
    ColorPattern3[i].Blue = ColorPattern3[i - 1].Blue + 6;
  }
  for (i = 13; i < 50; i++) {
    ColorPattern3[i].Red = ColorPattern3[i - 1].Red - 3;
    ColorPattern3[i].Green = ColorPattern3[i - 1].Green - 3;
    ColorPattern3[i].Blue = ColorPattern3[i - 1].Blue - 3;
  }
  Ellipse (
    Orientation,
    XRef + PlugSideRegion + PlugMidRegion / 2,
    YRef + PlugHeight,
    PinWidth,
    PinWidth * 2 / 3,
    (UINT8) 2,
    ColorPattern3,
    50,
    100
    );
  for (i = 1; i < 4; i++)
    Ellipse (
      Orientation,
      XRef + PlugSideRegion + PlugMidRegion / 2,
      YRef + PlugHeight + (PinWidth * 2 / 3) * i * 4 / 3,
      PinWidth,
      PinWidth * 2 / 3,
      (UINT8) 2,
      ColorPattern3,
      50,
      100
      );
  //------------------------------

  for (i = 0; i < PlugSideRegion; i++) {

    Status = GraphicsOutput->Blt (
                              GraphicsOutput,
                              &PlugColor,
                              EfiBltVideoFill,
                              0,
                              0,
                              XRef + i,
                              YRef,
                              1,
                              PlugHeight - (j--),
                              (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                              );
    PlugColor.Red = PlugColor.Red + 3;
    PlugColor.Green = PlugColor.Green + 3;
    PlugColor.Blue = PlugColor.Blue + 3;
  }

  //plug mid region
  for (i = PlugSideRegion; i < PlugMidRegion + PlugSideRegion; i++) {

    Status = GraphicsOutput->Blt (
                              GraphicsOutput,
                              &PlugColor,
                              EfiBltVideoFill,
                              0,
                              0,
                              XRef + i,
                              YRef,
                              1,
                              PlugHeight,
                              (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                              );
  }
  //plug right side region
  j = 0;
  for (i = PlugMidRegion + PlugSideRegion; i < (PlugMidRegion + PlugSideRegion * 2); i++) {

    Status = GraphicsOutput->Blt (
                              GraphicsOutput,
                              &PlugColor,
                              EfiBltVideoFill,
                              0,
                              0,
                              XRef + i,
                              YRef,
                              1,
                              PlugHeight - (j++),
                              (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                              );
    PlugColor.Red = PlugColor.Red - 3;
    PlugColor.Green = PlugColor.Green - 3;
    PlugColor.Blue = PlugColor.Blue - 3;
  }
  //1  left side ellipse
  Ellipse (
    Orientation,
    XRef + PlugSideRegion,
    YRef,
    PlugSideRegion,
    PlugSideRegion * 2 / 3,
    (UINT8) 1,
    ColorPattern2,
    100,
    100
    );
  //1  left side ellipse
  Ellipse (
    Orientation,
    XRef + PlugSideRegion + PlugMidRegion,
    YRef,
    PlugSideRegion,
    PlugSideRegion * 2 / 3,
    (UINT8) 1,
    ColorPattern2,
    100,
    100
    );
  //rectagle betwwen two ellipse
  Status = GraphicsOutput->Blt (
                            GraphicsOutput,
                            &ColorPattern2[0],
                            EfiBltVideoFill,
                            0,
                            0,
                            XRef + PlugSideRegion,
                            YRef - PlugSideRegion * 2 / 3,
                            PlugMidRegion,
                            PlugSideRegion * 4 / 3,
                            (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                            );

  if (PlugType == 2) {
    //pin left side top ellipse
    Ellipse (
      Orientation,
      XRef + PlugSideRegion + 5 + PinWidth / 2,
      YRef - PinHeight,
      PinWidth / 2,
      PinWidth / 2,
      (UINT8) 1,
      ColorPattern2,
      100,
      100
      );

    PlugColor.Red = 149;
    PlugColor.Green = 141;
    PlugColor.Blue = 111;
    Increment = (UINT8) (PinWidth / (2 * 60));
    if (Increment == 0) {
      Increment = (UINT8) ((2 * 60) / PinWidth);
    }
    if (Increment == 0) {
      Increment = 1;
    }

    for (i = 0; i < PinWidth / 2; i++) {  //first pin
      Status = GraphicsOutput->Blt (
                                GraphicsOutput,
                                &PlugColor,
                                EfiBltVideoFill,
                                0,
                                0,
                                XRef + PlugSideRegion + 5 + i,
                                YRef - PinHeight,
                                1,
                                PinHeight,
                                (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                );
      PlugColor.Red = PlugColor.Red + Increment;
      PlugColor.Green = PlugColor.Green + Increment;
      PlugColor.Blue = PlugColor.Blue + Increment;
    }
    for (i = PinWidth / 2; i < PinWidth; i++) {  //first pin
      Status = GraphicsOutput->Blt (
                                GraphicsOutput,
                                &PlugColor,
                                EfiBltVideoFill,
                                0,
                                0,
                                XRef + PlugSideRegion + 5 + i,
                                YRef - PinHeight,
                                1,
                                PinHeight,
                                (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                );
      PlugColor.Red = PlugColor.Red - Increment;
      PlugColor.Green = PlugColor.Green - Increment;
      PlugColor.Blue = PlugColor.Blue - Increment;
    }

    //pin right side top ellipse
    Ellipse (
      Orientation,
      XRef + PlugSideRegion + PlugMidRegion - 5 - PinWidth / 2,
      YRef - PinHeight,
      PinWidth / 2,
      PinWidth / 2,
      (UINT8) 1,
      ColorPattern2,
      100,
      100
      );

    PlugColor.Red = 149;
    PlugColor.Green = 141;
    PlugColor.Blue = 111;

    for (i = 0; i < PinWidth / 2; i++) {  //first pin
      Status = GraphicsOutput->Blt (
                                GraphicsOutput,
                                &PlugColor,
                                EfiBltVideoFill,
                                0,
                                0,
                                XRef + PlugSideRegion + PlugMidRegion - 5 + i - PinWidth,
                                YRef - PinHeight,
                                1,
                                PinHeight,
                                (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                );
      PlugColor.Red = PlugColor.Red + Increment;
      PlugColor.Green = PlugColor.Green + Increment;
      PlugColor.Blue = PlugColor.Blue + Increment;
    }
    for (i = PinWidth / 2; i < PinWidth; i++) {  //first pin
      Status = GraphicsOutput->Blt (
                                GraphicsOutput,
                                &PlugColor,
                                EfiBltVideoFill,
                                0,
                                0,
                                XRef + PlugSideRegion + PlugMidRegion - 5 + i - PinWidth,
                                YRef - PinHeight,
                                1,
                                PinHeight,
                                (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                );
      PlugColor.Red = PlugColor.Red - Increment;
      PlugColor.Green = PlugColor.Green - Increment;
      PlugColor.Blue = PlugColor.Blue - Increment;
    }
    //straight wire
    PlugColor.Red = 30;
    PlugColor.Green = 30;
    PlugColor.Blue = 30;

    for (i = 0; i < PinWidth; i++) {
      Status = GraphicsOutput->Blt (
                                GraphicsOutput,
                                &PlugColor,
                                EfiBltVideoFill,
                                0,
                                0,
                                XRef + PlugSideRegion + PlugMidRegion / 2 + i - PinWidth / 2,
                                YRef + PlugHeight + PinWidth * 10 / 3,
                                1,
                                WireHeight,
                                (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                );
      PlugColor.Red = PlugColor.Red + Increment;
      PlugColor.Green = PlugColor.Green + Increment;
      PlugColor.Blue = PlugColor.Blue + Increment;
    }

  } else { //if (plugtype==2) end
    PlugColor.Red = 149;
    PlugColor.Green = 141;
    PlugColor.Blue = 111;

    Status = GraphicsOutput->Blt (
                              GraphicsOutput,
                              &PlugColor,
                              EfiBltVideoFill,
                              0,
                              0,
                              XRef + PlugSideRegion,
                              YRef - PlugSideRegion * 2 / 3,
                              PlugMidRegion,
                              PlugSideRegion / 2,
                              (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                              );
  }

  if (PlugType == 1) {
    DisplayUsbLogo (XRef + PlugWidth / 2, YRef + PlugSideRegion * 4 / 3, PlugHeight - PlugSideRegion * 8 / 3);
  }
}

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
  )
{
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern2[1];
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern3[500];
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL BgColor;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL FgColor;
  UINT16 i;
  UINT16 j;
  UINT16 Clearence = 170;

  ColorPattern2[0].Red = 0;
  ColorPattern2[0].Green = 0;
  ColorPattern2[0].Blue = 0;
  ColorPattern2[0].Reserved = 0;

  ColorPattern3[0].Red = 0;
  ColorPattern3[0].Green = 0;
  ColorPattern3[0].Blue = 0;
  ColorPattern3[0].Reserved = 0;
  if (Orientation == 0) {

  } else if (Orientation == 1) {

    //hr1=(UINT8)(Time/60);
    //min1=Time%60;
#if 0
    j=0;
    if (hr1>0)
    {
      FullFlag=0;
      if (hr1<10)
      StringTime[j++]=(UINT16)hr1+48;
      else
      {
        StringTime[j++]=(UINT16)hr1/10+48;
        StringTime[j++]=(UINT16)hr1%10+48;
      }
      StringTime[j++]=' ';
      StringTime[j++]='H';
      StringTime[j++]='r';
      StringTime[j++]=' ';
    }
    if (min1>0)
    {
      FullFlag=0;
      if (min1<10)
      StringTime[j++]=(UINT16)min1+48;
      else
      {
        StringTime[j++]=(UINT16)min1/10+48;
        StringTime[j++]=(UINT16)min1%10+48;
      }
      StringTime[j++]=' ';
      StringTime[j++]='M';
      StringTime[j++]='i';
      StringTime[j++]='n';
      StringTime[j++]=' ';
    }
    for (i=0;StringEstimated[i]!='\0';i++)
    StringTime[j++]=StringEstimated[i];
    StringTime[j++]='\0';
#endif

    //Print(L"StringTime  %s",StringTime);

    BgColor.Red = 0;
    BgColor.Green = 0;
    BgColor.Blue = 0;
    BgColor.Reserved = 0;
    FgColor.Red = 0;
    FgColor.Green = 0;
    FgColor.Blue = 255;
    FgColor.Reserved = 0;
#if 0
    if (FullFlag==0)
    DisplayString(StringTime,(UINT16)PosX+10,(UINT16)(PosY+BatteryHeight+Clearence+200),2,FgColor,BgColor,FontProtocol);
    else
    DisplayString(FullyCharged,(UINT16)PosX+10,(UINT16)(PosY+BatteryHeight+Clearence+200),2,FgColor,BgColor,FontProtocol);
#endif

    //display surface
    for (i = 60; i > 20; i--) {
      Ellipse (
        Orientation,
        (INT16) ((PosX) + 5),
        (INT16) (PosY + BatteryHeight + 30) + i + Clearence,
        (INT16) (BatteryWidth),
        (INT16) (40),
        (UINT8) 0,
        ColorPattern2,
        100,
        100
        );
    }

    for (i = 0; i < 250; i++) {
      ColorPattern3[i].Red = 0;
      ColorPattern3[i].Green = 0;
      ColorPattern3[i].Blue = 0;
      ColorPattern3[i].Reserved = 0;
    }
    for (i = 250; i < 500; i++) {
      ColorPattern3[i].Red = 104;
      ColorPattern3[i].Green = 104;
      ColorPattern3[i].Blue = 104;
      ColorPattern3[i].Reserved = 0;
    }

    Ellipse (
      Orientation,
      (INT16) ((PosX) + 5),
      (INT16) (PosY + BatteryHeight + 30) + 20 + Clearence,
      (INT16) (BatteryWidth),
      (INT16) (40),
      (UINT8) 2,
      ColorPattern3,
      500,
      100
      );

    ColorPattern3[0].Red = 180;
    ColorPattern3[0].Green = 180;
    ColorPattern3[0].Blue = 180;
    ColorPattern3[0].Reserved = 0;
    Ellipse (
      Orientation,
      (INT16) ((PosX) + 5),
      (INT16) (PosY + BatteryHeight + 30) + 20 + Clearence,
      (INT16) (20),
      (INT16) (10),
      (UINT8) 1,
      ColorPattern3,
      1,
      100
      );
    //left half
    Ellipse (
      Orientation,
      (INT16) ((PosX) + 5),
      (INT16) (PosY + BatteryHeight + 30) + 20 + Clearence,
      (INT16) (30),
      (INT16) (10),
      (UINT8) 3,
      ColorPattern3,
      1,
      80
      );
    Ellipse (
      Orientation,
      (INT16) ((PosX) + 5),
      (INT16) (PosY + BatteryHeight + 30) + 20 + Clearence,
      (INT16) (40),
      (INT16) (20),
      (UINT8) 3,
      ColorPattern3,
      1,
      80
      );
    Ellipse (
      Orientation,
      (INT16) ((PosX) + 5),
      (INT16) (PosY + BatteryHeight + 30) + 20 + Clearence,
      (INT16) (50),
      (INT16) (30),
      (UINT8) 3,
      ColorPattern3,
      1,
      80
      );
    //right half2
    Ellipse (
      Orientation,
      (INT16) ((PosX) + 5),
      (INT16) (PosY + BatteryHeight + 30) + 20 + Clearence,
      (INT16) (30),
      (INT16) (10),
      (UINT8) 4,
      ColorPattern3,
      1,
      80
      );
    Ellipse (
      Orientation,
      (INT16) ((PosX) + 5),
      (INT16) (PosY + BatteryHeight + 30) + 20 + Clearence,
      (INT16) (40),
      (INT16) (20),
      (UINT8) 4,
      ColorPattern3,
      1,
      80
      );
    Ellipse (
      Orientation,
      (INT16) ((PosX) + 5),
      (INT16) (PosY + BatteryHeight + 30) + 20 + Clearence,
      (INT16) (50),
      (INT16) (30),
      (UINT8) 4,
      ColorPattern3,
      1,
      80
      );

    for (j = 0; j < DisplayTime; j++) {
      gBS->Stall (100000);
      gBS->Stall (100000);
      //lower half ellipse
      for (i = 40; i < 60; i++) {
        Ellipse (
          Orientation,
          (INT16) ((PosX) + 5),
          (INT16) (PosY + BatteryHeight + 40) + i + (Clearence - 50),
          (INT16) (BatteryWidth / 5),
          (INT16) (BatteryWidth - BatteryWidth / 5),
          (UINT8) 0,
          ColorPattern,
          PatternLength,
          35
          );
      }
      gBS->Stall (100000);
      gBS->Stall (100000);
      //middle half ellipse
      for (i = 20; i < 40; i++) {
        Ellipse (
          Orientation,
          (INT16) ((PosX) + 5),
          (INT16) (PosY + BatteryHeight + 40) + i + (Clearence - 100) - 10,
          (INT16) (BatteryWidth / 4),
          (INT16) (BatteryWidth - BatteryWidth / 4),
          (UINT8) 0,
          ColorPattern,
          PatternLength,
          35
          );
      }
      gBS->Stall (100000);
      gBS->Stall (100000);

      //top half ellipse
      for (i = 0; i < 20; i++) {
        Ellipse (
          Orientation,
          (INT16) ((PosX) + 5),
          (INT16) (PosY + BatteryHeight + 40) + i,
          (INT16) (BatteryWidth / 3),
          (INT16) (BatteryWidth - BatteryWidth / 3),
          (UINT8) 0,
          ColorPattern,
          PatternLength,
          35
          );
      }
      gBS->Stall (100000);
      gBS->Stall (100000);

      RefreshBlock (
        PosX - BatteryWidth / 2,
        (PosY + BatteryHeight / 2 + 70),
        BatteryWidth + BatteryWidth,
        BatteryWidth + BatteryWidth / 2 - 60,
        DisplayBackgroundColor
        );
    }
  }
}



VOID
RefreshBlock (
  UINTN                          XTopLeft,
  UINTN                          YTopLeft,
  UINTN                          XSize,
  UINTN                          YSize,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  BackgroundColor
  )
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  Status = GraphicsOutput->Blt (
                             GraphicsOutput,
                             &BackgroundColor,
                             EfiBltVideoFill,
                             0,
                             0,
                             XTopLeft,
                             YTopLeft,
                             XSize,
                             YSize,
                             (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                             );

}


VOID
FillBatteryIcon (
  UINT8  Orientation,
  UINTN  PosX,
  UINTN  PosY,
  UINTN  BatteryWidth,
  UINTN  BatteryHeight,
  UINT32 StageOfCharge
  )
{
  EFI_STATUS Status;
  UINT16                        i;
  UINT16                        MidOfBatteryWidth;
  UINT16                        FillLength;
  UINTN                         xTopLeftCorner;
  UINTN                         yTopLeftCorner;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL FillColor;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern[180];
  UINTN                         PatternIndex;
  UINTN                         i2;
  UINTN                         IncrementStep;
  UINTN                         DecrementStep;
  UINT8                         ColorIncrement;
  UINT8                         ColorDecrement;
  UINT8                         ColorFlag;
  UINT16                        Init;
  UINT16                        Boundry;

  Status = EFI_SUCCESS;
  i = 0;
  MidOfBatteryWidth = 0;
  FillLength = 0;
  xTopLeftCorner = 0;
  yTopLeftCorner = 0;
  PatternIndex = 0;
  ColorIncrement = 1;
  ColorDecrement = 1;
  ColorFlag = 0;
  Init = 0;
  Boundry = 0;

  if (Orientation == 0) { //landscape  --
    xTopLeftCorner = PosX + (BatteryHeight - 40) / 2 - (StageOfCharge * (BatteryHeight - 40)) / 100;
    yTopLeftCorner = (PosY - BatteryWidth / 2 + 20);
    //Print(L"\nState of charge = %d  PosY: %d  PosX %d  BatteryHeight: %d   xTopLeftCorner: %d \n",StageOfCharge, PosY, PosX,BatteryHeight,xTopLeftCorner);
    FillLength = (UINT16) (PosX + BatteryHeight / 2 - xTopLeftCorner - 10);
    MidOfBatteryWidth = (UINT16) (yTopLeftCorner + BatteryWidth / 3);  //for 3d effect
  } else if (Orientation == 1) { //portrait |
    yTopLeftCorner = PosY + (BatteryHeight - 40) / 2 - (StageOfCharge * (BatteryHeight - 40)) / 100;
    xTopLeftCorner = (PosX - BatteryWidth / 2 + 20);
    //Print(L"\nState of charge = %d  PosY: %d  PosX %d  BatteryHeight: %d   xTopLeftCorner: %d \n",StageOfCharge, PosY, PosX,BatteryHeight,xTopLeftCorner);
    FillLength = (UINT16) (PosY + BatteryHeight / 2 - yTopLeftCorner - 10);
    MidOfBatteryWidth = (UINT16) (xTopLeftCorner + BatteryWidth / 3);  //for 3d effect
  }


  // x=(BW-20)/3 to find count of 1/3rd of pixels, pixel/noofcolors ratio x/110
  IncrementStep = (BatteryWidth - 20) / (3 * 110);
  DecrementStep = ((BatteryWidth - 20) * 2) / (3 * 110);

  if (IncrementStep < 1) {
    ColorIncrement = (UINT8) (1 + 110 / ((BatteryWidth - 20) / 3));
    IncrementStep = 1;

  }
  if (DecrementStep < 1) {
    DecrementStep = 1;
    ColorDecrement = (UINT8) (1 + 110 / (((BatteryWidth - 20) * 2) / 3));
  }

  //logic to fill battery

  if (StageOfCharge <= 10) { // for red
    //Red   : Red=255, GB-> Dark 30 - 140 bright
    FillColor.Red = 255;
    FillColor.Green = 30;
    FillColor.Blue = 30;
    FillColor.Reserved = 0;
    ColorFlag = 1;

  } else { //for green
    //Green: RB=0, G-> Dark 170-255 bright
    FillColor.Red = 0;
    FillColor.Green = 145;
    FillColor.Blue = 0;
    FillColor.Reserved = 0;
    ColorFlag = 3;
  }

  ColorPattern[0] = FillColor;

  if (Orientation == 0) {
    // Ellipse to fill base of battery fuel
    Init = (UINT16) yTopLeftCorner;
    Boundry = (UINT16) (yTopLeftCorner + BatteryWidth - 30);
  } else if (Orientation == 1) {
    // Ellipse to fill base of battery fuel
    Init = (UINT16) xTopLeftCorner;
    Boundry = (UINT16) (xTopLeftCorner + BatteryWidth - 30);
  }

  PatternIndex = 0;
  for (i = Init; i < Boundry; i = i + (UINT16) IncrementStep) {
    if (Orientation == 0) {
      Status = GraphicsOutput->Blt (
                                GraphicsOutput,
                                &FillColor,
                                EfiBltVideoFill,
                                0,
                                0,
                                xTopLeftCorner,
                                i,
                                FillLength,
                                IncrementStep,
                                (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                );
    } else {
      Status = GraphicsOutput->Blt (
                                GraphicsOutput,
                                &FillColor,
                                EfiBltVideoFill,
                                0,
                                0,
                                i,
                                yTopLeftCorner,
                                IncrementStep,
                                FillLength,
                                (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                );
    }

    for (i2 = PatternIndex; i2 < (IncrementStep + PatternIndex); i2++) {
      ColorPattern[i2] = FillColor;
    }
    PatternIndex = PatternIndex + IncrementStep;

    if (ColorFlag == 0) {
      if (i < MidOfBatteryWidth) {
        FillColor.Red = FillColor.Red + ColorIncrement;
        if (FillColor.Red < 10)
          FillColor.Red = 255;
      } else {
        FillColor.Red = FillColor.Red - ColorDecrement;
        IncrementStep = DecrementStep;
        if (FillColor.Red < 145) {
          FillColor.Red = 145;
        }
      }
    } else if (ColorFlag == 1) {
      if (i < MidOfBatteryWidth) {
        FillColor.Green = FillColor.Green + ColorIncrement;
        FillColor.Blue = FillColor.Blue + ColorIncrement;
        if (FillColor.Green > 140) {
          FillColor.Green = 140;
          FillColor.Blue = 140;
        }
      } else {
        IncrementStep = DecrementStep;

        FillColor.Green = FillColor.Green - ColorDecrement;
        FillColor.Blue = FillColor.Blue - ColorDecrement;
        if (FillColor.Green < 30) {
          FillColor.Green = 30;
          FillColor.Blue = 30;
        }
      }
    } else if (ColorFlag == 2) {
      if (i < MidOfBatteryWidth) {
        FillColor.Red = FillColor.Red + ColorIncrement;
        FillColor.Blue = FillColor.Blue + ColorIncrement;
      } else {
        FillColor.Red = FillColor.Red - ColorDecrement;
        FillColor.Blue = FillColor.Blue - ColorDecrement;
        IncrementStep = DecrementStep;
        if (FillColor.Blue < 5) {
          FillColor.Blue = 0;
          FillColor.Red = 0;
        }
      }
    } else if (ColorFlag == 3) {
      if (i < MidOfBatteryWidth) {
        FillColor.Green = FillColor.Green + ColorIncrement;
        if (FillColor.Green < 10)
          FillColor.Green = 255;
      } else {
        FillColor.Green = FillColor.Green - ColorDecrement;
        IncrementStep = DecrementStep;
        if (FillColor.Green < 145) {
          FillColor.Green = 145;
        }
      }
    }
  }
  i = i - (UINT16) IncrementStep;
  if (Orientation == 0) {
    Status = GraphicsOutput->Blt (
                              GraphicsOutput,
                              &FillColor,
                              EfiBltVideoFill,
                              0,
                              0,
                              xTopLeftCorner,
                              i,
                              PosX + BatteryHeight / 2 - xTopLeftCorner - 10,
                              (yTopLeftCorner + BatteryWidth - 30) - i,
                              (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                             );
  } else {
    Status = GraphicsOutput->Blt (
                              GraphicsOutput,
                              &FillColor,
                              EfiBltVideoFill,
                              0,
                              0,
                              i,
                              yTopLeftCorner,
                              IncrementStep,
                              FillLength,
                              (BlockWidth) * sizeof(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                              );
  }


  if (Orientation == 0) {
    for (i2 = PatternIndex; i2 < ((yTopLeftCorner + BatteryWidth - 30) - i + PatternIndex); i2++) {
      ColorPattern[i2] = FillColor;
    }
    PatternIndex = PatternIndex + (yTopLeftCorner + BatteryWidth - 30) - i;

    BottomIndex = (UINT16) (PatternIndex - 1);
  } else if (Orientation == 1) {
    for (i2 = PatternIndex; i2 < ((xTopLeftCorner + BatteryWidth - 30) - i + PatternIndex); i2++) {
      ColorPattern[i2] = FillColor;
    }
    PatternIndex = PatternIndex + (xTopLeftCorner + BatteryWidth - 30) - i;

    BottomIndex = (UINT16) (PatternIndex - 1);
  }

  //ellipse to fill base of battery fuel
  ColorPattern[0] = FillColor;


  if (Orientation == 0) {
    // Ellipse to fill base of battery fuel
    Ellipse (
      Orientation,
      (INT16) (PosX + BatteryHeight / 2) - 10,
      (INT16) (PosY + 5),
      (INT16) 20,
      (INT16) (BatteryWidth / 2 + 5) - 20,
      (UINT8) 2,
      ColorPattern,
      (UINT16) PatternIndex,
      100
      );
    // Level ellipse
    Ellipse (
      Orientation,
      (INT16) (xTopLeftCorner),
      (INT16) ((PosY) + 5),
      (INT16) 20,
      (INT16) (BatteryWidth / 2 + 5) - 20,
      (UINT8) 1,
      ColorPattern,
      1,
      100
      );
  } else if (Orientation == 1) {
    // Ellipse to fill base of battery fuel
    Ellipse (
      Orientation,
      (INT16) (PosX + 5),
      (INT16) (PosY + BatteryHeight / 2) - 10,
      (INT16) (BatteryWidth / 2 + 5) - 20,
      (INT16) 20,
      (UINT8) 2,
      ColorPattern,
      (UINT16) PatternIndex,
      100
      );
    // Level ellipse
    Ellipse (
      Orientation,
      (INT16) (PosX + 5),
      (INT16) (yTopLeftCorner),
      (INT16) (BatteryWidth / 2 + 5) - 20,
      (INT16) 20,
      (UINT8) 1,
      ColorPattern,
      1,
      100
      );
  }
} //end of fill function


VOID
DrawBatteryIconPortrait (
  UINTN                          PosX,
  UINTN                          PosY,
  UINTN                          BatteryWidth,
  UINTN                          BatteryHeight,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  ColorPattern[],
  UINT8                          FillFlag,
  UINT16                         PatternLength
  )
{
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern2[1];
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL BoundryColor;

  UINT16      i;
  UINT16      j;
  EFI_STATUS  Status;

  j                  = 0;
  Status             = EFI_SUCCESS;
  DisplayOrientation = 1;

  for (i = 20; i > 0; i--) {
    Ellipse (
      DisplayOrientation,
      (INT16) (PosX + 5),
      (INT16) (PosY + BatteryHeight / 2) + 10 + i,
      (INT16) (BatteryWidth / 2 + 5),
      (INT16) 20,
      (UINT8) 2,
      ColorPattern,
      (UINT16) BatteryWidth,
      100
      );
  }
  ColorPattern2[0].Red = 120;
  ColorPattern2[0].Green = 120;
  ColorPattern2[0].Blue = 120;
  ColorPattern2[0].Reserved = 0;
  Ellipse (
    DisplayOrientation,
    (INT16) (PosX + 5),
    (INT16) (PosY + BatteryHeight / 2) + 10 + i,
    (INT16) (BatteryWidth / 2 + 5),
    (INT16) 20,
    (UINT8) 1,
    ColorPattern2,
    BottomIndex,
    100
    );

  /*
     -2-
  1 |   |3
   |   |
   -4-*/
  //1

  BoundryColor.Red = 50; // Range: 50 = Dark, 150 = Bright
  BoundryColor.Green = 50;
  BoundryColor.Blue = 50;
  BoundryColor.Reserved = 0;
  for (i = 0; i < 15; i++) {
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &BoundryColor, // black
                               EfiBltVideoFill,
                               0,
                               0,
                               (PosX - BatteryWidth / 2) + i,
                               (PosY - BatteryHeight / 2),
                               1,
                               BatteryHeight + 10 + i,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );
    BoundryColor.Red=BoundryColor.Red+5;
    BoundryColor.Green=BoundryColor.Green+5;
    BoundryColor.Blue=BoundryColor.Blue+5;
  }


  //3


  BoundryColor.Red = 125; // Range: 50 = Dark, 150 = Bright
  BoundryColor.Green = 125;
  BoundryColor.Blue = 125;
  BoundryColor.Reserved = 0;
  j = 15;
  for (i = 0; i < 15; i++){
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &BoundryColor, // White
                               EfiBltVideoFill,
                               0,
                               0,
                               (PosX + BatteryWidth / 2) + i - 5,
                               (PosY - BatteryHeight /2),
                               1,
                               BatteryHeight + 10 + (j--),
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );

    BoundryColor.Red=BoundryColor.Red-5;
    BoundryColor.Green=BoundryColor.Green-5;
    BoundryColor.Blue=BoundryColor.Blue-5;
  }
} //end of DrawBatteryIconPortrait

VOID
TopSurfaceOfBattery (
  UINT8                          Orientation,
  UINTN                          PosX,
  UINTN                          PosY,
  UINTN                          BatteryWidth,
  UINTN                          BatteryHeight,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  ColorPattern[],
  UINT8                          FillFlag,
  UINT16                         PatternLength
  )
{
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL ColorPattern2[1];
  UINT16                        i;

  ColorPattern2[0].Red = 130;
  ColorPattern2[0].Green = 130;
  ColorPattern2[0].Blue = 130;
  ColorPattern2[0].Reserved = 0;

  if (Orientation == 0) {
    for (i = 0; i < 20; i++) {
      Ellipse (
        Orientation,
        (INT16) (PosX - BatteryHeight / 2) - i,
        (INT16) (PosY + 5),
        (INT16) 20,
        (INT16) (BatteryWidth / 2 + 5),
        (UINT8) 2,
        ColorPattern,
        PatternLength,
        100
        );
    }
    Ellipse (
      Orientation,
      (INT16) (PosX - BatteryHeight / 2) - i,
      (INT16) (PosY + 5),
      (INT16) 20,
      (INT16) (BatteryWidth / 2 + 5),
      (UINT8) 1,
      ColorPattern2,
      PatternLength,
      100
      );

    //top small ellipse
    for (; i < 45; i++) {
      Ellipse (
        Orientation,
        (INT16) (PosX - BatteryHeight / 2) - i,
        (INT16) (PosY + 5),
        (INT16) 20,
        (INT16) (BatteryWidth / 4 + 5),
        (UINT8) 2,
        ColorPattern,
        PatternLength,
        100
        );
    }
    Ellipse (
      Orientation,
      (INT16) (PosX - BatteryHeight / 2) - i,
      (INT16) (PosY + 5),
      (INT16) 20,
      (INT16) (BatteryWidth / 4 + 5),
      (UINT8) 1,
      ColorPattern2,
      1,
      100
      );
  } else if (Orientation == 1) {
    for (i = 0; i < 20; i++) {
      Ellipse (
        Orientation,
        (INT16) (PosX + 5),
        (INT16) (PosY - BatteryHeight / 2) - i,
        (INT16) (BatteryWidth / 2 + 5),
        (INT16) 20,
        (UINT8) 2,
        ColorPattern,
        PatternLength,
        100
        );
    }
    Ellipse (
      Orientation,
      (INT16) (PosX + 5),
      (INT16) (PosY - BatteryHeight / 2) - i,
      (INT16) (BatteryWidth / 2 + 5),
      (INT16) 20,
      (UINT8) 1,
      ColorPattern2,
      PatternLength,
      100
      );

    //top small ellipse
    for (; i < 45; i++) {
      Ellipse (
        Orientation,
        (INT16) (PosX + 5),
        (INT16) (PosY - BatteryHeight / 2) - i,
        (INT16) (BatteryWidth / 4 + 5),
        (INT16) 20,
        (UINT8) 2,
        ColorPattern,
        PatternLength,
        100
        );
    }
    Ellipse (
      Orientation,
      (INT16) (PosX + 5),
      (INT16) (PosY - BatteryHeight / 2) - i,
      (INT16) (BatteryWidth / 4 + 5),
      (INT16) 20,
      (UINT8) 1,
      ColorPattern2,
      PatternLength,
      100
      );
  }
}


VOID
Ellipse (
  UINT8                          Orientation,
  INT32                          xc,
  INT32                          yc,
  INT32                          rx,
  INT32                          ry,
  UINT8                          FillFlag,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  FillColor[],
  UINT16                         PatternLength,
  UINT8                          Percentage
  )
{
  INT16 counter;
  INT16 counter2;
  INT32 rxSq;
  INT32 prevY;
  INT32 prevX;
  INT32 rySq;
  INT32 x;
  INT32 y;
  INT32 p;
  INT32 px;
  INT32 py;

  counter  = 0;
  counter2 = 0;
  rxSq     = rx * rx;
  prevY    = ry;
  prevX    = rx;
  rySq     = ry * ry;
  x        = 0;
  y        = ry;
  px       = 0;
  py       = 2 * rxSq * y;

  BottomIndex = PatternLength - 1;
  TopIndex = 0;
  PrevBottomIndex = 0;
  PrevTopIndex = 0;

  if (Orientation == 1) {
    TopIndex = PatternLength / 2;
    BottomIndex = PatternLength / 2;
  }

  if ((FillFlag != 3) && (FillFlag != 4)) {
    DrawEllipse (Orientation, xc, yc, x, y, FillFlag, FillColor, 1, Percentage);
  }
  //Region 1
  p = (INT32) (rySq - (rxSq * ry) + (INT32) (rxSq / 4));
  while (px < py) {
    x++;
    px = px + 2 * rySq;
    if (p < 0) {
      p = p + rySq + px;
    } else {
      y--;
      py = py - 2 * rxSq;
      p = p + rySq + px - py;
    }
    if (prevY != y) {
      prevY = y;
      counter++;
    }
    if (prevX != x) {
      prevX = x;
      counter2++;
    }

    if (counter > (UINT16) ((ry * Percentage) / 100)) {
      if ((FillFlag != 3) && (FillFlag != 4)) {
        break;
      }
    }
    if ((FillFlag == 3) || (FillFlag == 4)) {
      if (counter2 > (UINT16) ((rx * Percentage) / 100)) {
        DrawEllipse (Orientation, xc, yc, x, y, FillFlag, FillColor, 1, Percentage);
      }
    } else {
      DrawEllipse (Orientation, xc, yc, x, y, FillFlag, FillColor, 1, Percentage);
    }
    //delay(30);
  }
  //Region 2
  p = (INT32)(rySq *(x * x + x) + rxSq * (y - 1) * (y - 1) - rxSq * rySq);
  while (y > 0) {
    y--;
    py = py - 2 * rxSq;
    if (p > 0) {
      p = p + rxSq - py;
    } else {
      x++;
      px = px + 2 * rySq;
      p = p + rxSq - py + px;
    }
    if (prevY != y) {
      prevY = y;
      counter++;
    }
    if (prevX != x) {
      prevX = x;
      counter2++;
    }
    if (counter > (UINT16) ((ry * Percentage) / 100)) {
      if ((FillFlag != 3) && (FillFlag != 4)) {
        break;
      }
    }
    if ((FillFlag == 3) || (FillFlag == 4)) {
      if (counter2 > (UINT16) ((rx * Percentage) / 100)) {
        DrawEllipse (Orientation, xc, yc, x, y, FillFlag, FillColor, 1, Percentage);
      }
    } else {
      DrawEllipse (Orientation, xc, yc, x, y, FillFlag, FillColor, 1, Percentage);
    }
  }
}




VOID
DrawEllipse (
  UINT8                          Orientation,
  UINT32                         xc,
  UINT32                         yc,
  UINT32                         x,
  UINT32                         y,
  UINT8                          FillFlag,
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL  FillColor[],
  UINT16                         PatternLength,
  UINT8                          Percentage
  )
{
  EFI_STATUS Status;

  Status = EFI_SUCCESS;

  //flag==2 for fill flag with pattern
  if (FillFlag == 2) {
    if (Orientation == 0) {
      Status = GraphicsOutput->Blt (
                                 GraphicsOutput,
                                 &FillColor[BottomIndex],
                                 EfiBltVideoFill,
                                 0,
                                 0,
                                 (xc - x),
                                 (yc + y),
                                 (2 * x),
                                 1,
                                 (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                 );
      if ((yc + y) != PrevTopIndex) {
        TopIndex++;
      }
      PrevTopIndex = (UINT16)(yc + y);

      Status = GraphicsOutput->Blt (
                                 GraphicsOutput,
                                 &FillColor[TopIndex],
                                 EfiBltVideoFill,
                                 0,
                                 0,
                                 (xc - x),
                                 (yc - y),
                                 (2 * x),
                                 1,
                                 (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                 );
      if ((yc - y) != PrevBottomIndex) {
        BottomIndex--;
      }

      PrevBottomIndex = (UINT16)(yc - y);
    }
    if (Orientation == 1) {//for portrait
      //gBS->Stall (100000);
      Status = GraphicsOutput->Blt (
                                 GraphicsOutput,
                                 &FillColor[TopIndex],
                                 EfiBltVideoFill,
                                 0,
                                 0,
                                 (xc + x),
                                 (yc - y),
                                 1,(2 * y),
                                 (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                 );
      if ((xc + x) != PrevTopIndex) {
        TopIndex++;
      }

      PrevTopIndex = (UINT16)(xc + x);

      Status = GraphicsOutput->Blt (
                                 GraphicsOutput,
                                 &FillColor[BottomIndex],
                                 EfiBltVideoFill,
                                 0,
                                 0,
                                 (xc - x),
                                 (yc - y),
                                 1,
                                 (2 * y),
                                 (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                 );
      if ((xc - x) != PrevBottomIndex) {
        BottomIndex--;
      }
      if (BottomIndex <= 1) {
        BottomIndex = 1;
      }
      PrevBottomIndex = (UINT16)(xc - x);
    }
  } else if (FillFlag == 1) {
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc - x),
                               (yc + y),
                               (2 * x),
                               1,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );

    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc - x),
                               (yc - y),
                               (2 * x),
                               1,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );
  } else if (FillFlag == 3) { // Circle half left
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc - x),
                               (yc + y),
                               2,
                               2,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );

    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc - x),
                               (yc - y),
                               2,
                               2,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );
  } else if (FillFlag == 4) { // Circle half right
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc + x),
                               (yc + y),
                               2,
                               2,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );

    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc + x),
                               (yc - y),
                               2,
                               2,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );
  } else if (FillFlag == 5) { // Circle half right
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc + x),
                               (yc + y),
                               1,
                               1,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );

    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc - x),
                               (yc + y),
                               1,
                               1,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );
  } else if (FillFlag == 6) { // Circle half right
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc - x),
                               (yc + y),
                               1,
                               1,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );
  } else { // Unfilled ellipse
    if (Percentage==100) {
      Status = GraphicsOutput->Blt (
                                 GraphicsOutput,
                                 &FillColor[0],
                                 EfiBltVideoFill,
                                 0,
                                 0,
                                 (xc + x),
                                 (yc + y),
                                 PatternLength,
                                 PatternLength,
                                 (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                 );

      Status = GraphicsOutput->Blt (
                                 GraphicsOutput,
                                 &FillColor[0],
                                 EfiBltVideoFill,
                                 0,
                                 0,
                                 (xc - x),
                                 (yc + y),
                                 PatternLength,
                                 PatternLength,
                                 (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                                 );
    }
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc + x),
                               (yc - y),
                               PatternLength,
                               PatternLength,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );
    Status = GraphicsOutput->Blt (
                               GraphicsOutput,
                               &FillColor[0],
                               EfiBltVideoFill,
                               0,
                               0,
                               (xc - x),
                               (yc - y),
                               PatternLength,
                               PatternLength,
                               (BlockWidth) * sizeof (EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
                               );
  }
}

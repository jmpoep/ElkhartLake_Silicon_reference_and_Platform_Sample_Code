/** @file
  Policy definition for Internal Graphics Config Block.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#ifndef _GRAPHICS_CONFIG_H_
#define _GRAPHICS_CONFIG_H_
#pragma pack(push, 1)

#define GRAPHICS_PEI_PREMEM_CONFIG_REVISION 1
#define GRAPHICS_PEI_CONFIG_REVISION        1
#define GRAPHICS_DXE_CONFIG_REVISION        1

#define DDI_DEVICE_NUMBER   4
#define MAX_BCLM_ENTRIES    20


//
// DDI defines
//
typedef enum {
  DdiDisable       = 0x00,
  DdiDdcEnable     = 0x01,
} DDI_DDC_TBT_VAL;

typedef enum {
  DdiHpdDisable  = 0x00,
  DdiHpdEnable   = 0x01,
} DDI_HPD_VAL;

typedef enum {
  DdiPortADisabled = 0x00,
  DdiPortAEdp      = 0x01,
  DdiPortAMipiDsi  = 0x02,
  DdiPortADp       = 0x03,
} DDI_PORTA_SETTINGS;

typedef enum {
  DdiPortBDisabled = 0x00,
  DdiPortBDp       = 0x01,
  DdiPortBMipiDsi  = 0x02,
  DdiPortBHdmi     = 0x03,
} DDI_PORTB_SETTINGS;

typedef enum {
  DdiPortCDisabled = 0x00,
  DdiPortCHdmi     = 0x01,
  DdiPortCDp       = 0x02,
} DDI_PORTC_SETTINGS;

/**
  This structure configures the Native GPIOs for DDI port per VBT settings.
**/
typedef struct {
  UINT8 DdiPortAConfig; /// The Configuration of DDI port A, this settings must match VBT's settings. DdiPortADisabled - DdiPortA is disabled, <b>DdiPortAEdp - Set DdiPortA to eDP</b>, DdiPortAMipiDsi - Set DdiPortA to MIPI DSI, DdiPortADp = DP
  UINT8 DdiPortBConfig; /// The Configuration of DDI port B, this settings must match VBT's settings. DdiPortBDisabled - DdiPortB is disabled, <b>DdiPortBDp - Set DdiPortB to DP</b>, DdiPortBMipiDsi - Set DdiPortB to MIPI DSI
  UINT8 DdiPortCConfig; /// The Configuration of DDI port C, this settings must match VBT's settings. DdiPortCDisabled - DdiPortC is disabled, <b>DdiPortCHdmi - Set DdiPortC to HDMI</b>, DdiPortCDp - Set DdiPortC DP
  UINT8 DdiPortAHpd;    /// The HPD setting of DDI Port A, this settings must match VBT's settings. DdiHpdDisable - Disable HPD, <b>DdiHpdEnable - Enable HPD</b>
  UINT8 DdiPortBHpd;    /// The HPD setting of DDI Port B, this settings must match VBT's settings. DdiHpdDisable - Disable HPD, <b>DdiHpdEnable - Enable HPD</b>
  UINT8 DdiPortCHpd;    /// The HPD setting of DDI Port C, this settings must match VBT's settings. <b>DdiHpdDisable - Disable HPD</b>, DdiHpdEnable - Enable HPD
  UINT8 DdiPort1Hpd;    /// The HPD setting of DDI Port 1, this settings must match VBT's settings. <b>DdiHpdDisable - Disable HPD</b>, DdiHpdEnable - Enable HPD
  UINT8 DdiPort2Hpd;    /// The HPD setting of DDI Port 2, this settings must match VBT's settings. <b>DdiHpdDisable - Disable HPD</b>, DdiHpdEnable - Enable HPD
  UINT8 DdiPort3Hpd;    /// The HPD setting of DDI Port 3, this settings must match VBT's settings. <b>DdiHpdDisable - Disable HPD</b>, DdiHpdEnable - Enable HPD
  UINT8 DdiPort4Hpd;    /// The HPD setting of DDI Port 4, this settings must match VBT's settings. <b>DdiHpdDisable - Disable HPD</b>, DdiHpdEnable - Enable HPD
  UINT8 DdiPortADdc;    /// The DDC setting of DDI Port A, this settings must match VBT's settings. DdiDisable - Disable DDC, <b>DdiDdcEnable - Enable DDC </b>
  UINT8 DdiPortBDdc;    /// The DDC setting of DDI Port B, this settings must match VBT's settings. DdiDisable - Disable DDC, <b>DdiDdcEnable - Enable DDC </b>
  UINT8 DdiPortCDdc;    /// The DDC setting of DDI Port C, this settings must match VBT's settings. <b>DdiDisable - Disable DDC</b>, DdiDdcEnable - Enable DDC
  UINT8 DdiPort1Ddc;    /// The DDC setting of DDI Port 1, this settings must match VBT's settings. <b>DdiDisable - Disable DDC</b>, DdiDdcEnable - Enable DDC
  UINT8 DdiPort2Ddc;    /// The DDC setting of DDI Port 2, this settings must match VBT's settings. <b>DdiDisable - Disable DDC</b>, DdiDdcEnable - Enable DDC
  UINT8 DdiPort3Ddc;    /// The DDC setting of DDI Port 3, this settings must match VBT's settings. <b>DdiDisable - Disable DDC</b>, DdiDdcEnable - Enable DDC
  UINT8 DdiPort4Ddc;    /// The DDC setting of DDI Port 4, this settings must match VBT's settings. <b>DdiDisable - Disable DDC</b>, DdiDdcEnable - Enable DDC
  UINT8 Rsvd[3];        ///< Reserved for 4 bytes alignment
} DDI_CONFIGURATION;

/**
  This Configuration block is to configure GT related PreMem data/variables.\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Offset 0-27 Config Block Header
  /**
    Offset 28:0
    Selection of the primary display device: 0=iGFX, 1=PEG, 2=PCIe Graphics on PCH, <b>3=AUTO</b>, 4=Switchable Graphics\n
    When AUTO mode selected, the priority of display devices is: PCIe Graphics on PCH > PEG > iGFX
  **/
  UINT32                PrimaryDisplay    : 3;
  /**
    Offset 28:3
    Intel Gfx Support. It controls enabling/disabling iGfx device.
    When AUTO mode selected, iGFX will be turned off when external graphics detected.
    If FALSE, all other polices can be ignored.
    <b>2 = AUTO</b>;
    0 = FALSE;
    1 = TRUE.
  **/
  UINT32                InternalGraphics  : 2;
  /**
    Offset 28:5
    Pre-allocated memory for iGFX\n
    0   = 0MB,1 or 247 = 32MB,\n
    2   = 64MB, 3 = 96MB,\n
    4   = 128MB,5 = 160MB,\n
    240 = 4MB,     241 = 8MB,\n
    242 = 12MB,    243 = 16MB,\n
    244 = 20MB,    245 = 24MB,\n
    246 = 28MB,    248 = 36MB,\n
    249 = 40MB,    250 = 44MB,\n
    251 = 48MB,    252 = 52MB,\n
    253 = 56MB,<b> 254 = 60MB</b>,\n
    <b>Note: enlarging pre-allocated memory for iGFX may need to reduce MmioSize because of 4GB boundary limitation</b>
  **/
  UINT32                IgdDvmt50PreAlloc : 8;
  UINT32                PanelPowerEnable  : 1;    ///< Offset 28:13 :<b>(Test)</b> Control for enabling/disabling VDD force bit (Required only for early enabling of eDP panel): 0=FALSE, <b>1=TRUE</b>
  UINT32                ApertureSize      : 7;    ///< Offset 28:14 :Graphics aperture size (256MB is the recommended size as per BWG) : 0=128MB, <b>1=256MB</b>, 3=512MB, 7=1024MB, 15=2048MB.
  UINT32                GtPsmiSupport     : 1;    ///< Offset 28:21 :PSMI support On/Off: <b>0=FALSE</b>, 1=TRUE
  UINT32                PsmiRegionSize    : 3;    ///< Offset 28:22 :Psmi region size: <b>0=32MB</b>, 1=288MB, 2=544MB, 3=800MB, 4=1056MB
  UINT32                DismSize          : 3;    ///< DiSM Size for 2LM Sku: <b>0=0GB</b>, 1=1GB, 2=2GB, 3=3GB, 4=4GB, 5=5GB, 6=6GB, 7=7GB
  UINT32                RsvdBits0         : 4;    ///< Offset 28:25 :Reserved for future use
  /**
  Offset 32
  Temp Address of System Agent GTTMMADR: Default is <b>0xAF000000</b>
  **/
  UINT32                GttMmAdr;
  UINT16                GttSize;                  ///< Offset 36 Selection of iGFX GTT Memory size: 1=2MB, 2=4MB, <b>3=8MB</b>
  UINT8                 Rsvd1[2];                 ///< Offset 38 Reserved for DWORD alignment
  /**
  Offset 40
  Temp Address of System Agent GMADR: Default is <b>0xB0000000</b>
  **/
  UINT32                GmAdr;
} GRAPHICS_PEI_PREMEM_CONFIG;

/**
  This configuration block is to configure IGD related variables used in PostMem PEI.
  If Intel Gfx Device is not supported, all policies can be ignored.
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Offset 0-27 Config Block Header
  UINT32                RenderStandby     : 1;    ///< Offset 28:0 :<b>(Test)</b> This field is used to enable or disable RC6 (Render Standby): 0=FALSE, <b>1=TRUE</b>
  UINT32                PmSupport         : 1;    ///< Offset 28:1 :<b>(Test)</b> IGD PM Support TRUE/FALSE: 0=FALSE, <b>1=TRUE</b>
  UINT32                PavpEnable        : 1;    ///< Offset 28:2 :IGD PAVP TRUE/FALSE: 0=FALSE, <b>1=TRUE</b>
  /**
    Offset 28:3
    CdClock Frequency select\n
    <b>0xFF = Auto. Max CdClock freq based on Reference Clk</b> \n
     0: 307.2, 1: 312 Mhz, 2: 552 Mhz, 3: 556.8 Mhz, 4: 648 Mhz, 5: 652.8 Mhz

  **/
  UINT32                CdClock            : 8;
  UINT32                PeiGraphicsPeimInit: 1;   ///< Offset 28:11 : This policy is used to enable/disable Intel Gfx PEIM.<b>0- Disable</b>, 1- Enable
  UINT32                CdynmaxClampEnable : 1;   ///< Offset 28:12 : This policy is used to enable/disable CDynmax Clamping Feature (CCF) <b>1- Enable</b>, 0- Disable
  UINT32                GtFreqMax          : 8;   ///< Offset 28:13 : <b>(Test)</b> Max GT frequency limited by user in multiples of 50MHz: Default value which indicates normal frequency is <b>0xFF</b>
  UINT32                DisableTurboGt     : 1;   ///< Offset 28:21 : This policy is used to enable/disable DisableTurboGt <b>0- Disable</b>, 1- Enable
  UINT32                SkipCdClockInit    : 1;   ///< Offset 28:22: SKip full CD clock initialization. <b>0- Disable</b>, 1- Enable
  UINT32                RsvdBits0          : 9;  ///< Offser 28:23 :Reserved for future use
  VOID*                 LogoPtr;                  ///< Offset 32 Address of Intel Gfx PEIM Logo to be displayed
  UINT32                LogoSize;                 ///< Offset 36 Intel Gfx PEIM Logo Size
  VOID*                 GraphicsConfigPtr;        ///< Offset 40 Address of the Graphics Configuration Table
  DDI_CONFIGURATION     DdiConfiguration;         ///< Offset 44 DDI configuration, need to match with VBT settings.
  VOID*                 BltBufferAddress;         ///< Offset 60 Address of Blt buffer for PEIM Logo use
  UINT32                BltBufferSize;            ///< Offset 64 The size for Blt Buffer, calculating by PixelWidth * PixelHeight * 4 bytes (the size of EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
} GRAPHICS_PEI_CONFIG;

/**
  This configuration block is to configure IGD related variables used in DXE.
  If Intel Gfx Device is not supported or disabled, all policies will be ignored.
  The data elements should be initialized by a Platform Module.\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Offset 0-27: Config Block Header
  UINT32                Size;                     ///< Offset 28 - 31: This field gives the size of the GOP VBT Data buffer
  EFI_PHYSICAL_ADDRESS  VbtAddress;               ///< Offset 32 - 39: This field points to the GOP VBT data buffer
  UINT8                 PlatformConfig;           ///< Offset 40: This field gives the Platform Configuration Information (0=Platform is S0ix Capable for ULT SKUs only, <b>1=Platform is not S0ix Capable</b>, 2=Force Platform is S0ix Capable for All SKUs)
  UINT8                 AlsEnable;                ///< Offset 41: Ambient Light Sensor Enable: <b>0=Disable</b>, 2=Enable
  UINT8                 BacklightControlSupport;  ///< Offset 42: Backlight Control Support: 0=PWM Inverted, <b>2=PWM Normal</b>
  UINT8                 IgdBootType;              ///< Offset 43: IGD Boot Type CMOS option: <b>0=Default</b>, 0x01=CRT, 0x04=EFP, 0x08=LFP, 0x20=EFP3, 0x40=EFP2, 0x80=LFP2
  UINT32                IuerStatusVal;            ///< Offset 44 - 47: Offset 16 This field holds the current status of all the supported Ultrabook events (Intel(R) Ultrabook Event Status bits)
  CHAR16                GopVersion[0x10];         ///< Offset 48 - 79:This field holds the GOP Driver Version. It is an Output Protocol and updated by the Silicon code
  /**
    Offset 80: IGD Panel Type CMOS option\n
    <b>0=Default</b>, 1=640X480LVDS, 2=800X600LVDS, 3=1024X768LVDS, 4=1280X1024LVDS, 5=1400X1050LVDS1\n
    6=1400X1050LVDS2, 7=1600X1200LVDS, 8=1280X768LVDS, 9=1680X1050LVDS, 10=1920X1200LVDS, 13=1600X900LVDS\n
    14=1280X800LVDS, 15=1280X600LVDS, 16=2048X1536LVDS, 17=1366X768LVDS
  **/
  UINT8                 IgdPanelType;
  UINT8                 IgdPanelScaling;          ///< Offset 81: IGD Panel Scaling: <b>0=AUTO</b>, 1=OFF, 6=Force scaling
  UINT8                 IgdBlcConfig;             ///< Offset 82: Backlight Control Support: 0=PWM Inverted, <b>2=PWM Normal</b>
  UINT8                 IgdDvmtMemSize;           ///< Offset 83: IGD DVMT Memory Size: 1=128MB, <b>2=256MB</b>, 3=MAX
  UINT8                 GfxTurboIMON;             ///< Offset 84: IMON Current Value: 14=Minimal, <b>31=Maximum</b>
  UINT8                 Reserved[3];              ///< Offset 85: Reserved for DWORD alignment.
  UINT16                BCLM[MAX_BCLM_ENTRIES];   ///< Offset 88: IGD Backlight Brightness Level Duty cycle Mapping Table.
} GRAPHICS_DXE_CONFIG;
#pragma pack(pop)

#endif // _GRAPHICS_CONFIG_H_

/** @file
  HDAudio verb tables for EHL boards.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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

#include <HdAudioConfig.h>

HDAUDIO_VERB_TABLE HdaVerbTableDisplayAudio = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: ICL Display Audio Codec
  //  Revision ID = 0xFF
  //  Codec Vendor: 0x8086280F
  //
  0x8086, 0x280F,
  0xFF, 0xFF,
  //
  // Display Audio Verb Table
  //
  // Enable the third converter and 4 pin widgets (for GEN10+, the Vendor Node ID is 02h)
  0x00278111,
  // Pin Widget 5 - PORT B - Configuration Default: 0x18560010
  0x00571C10,
  0x00571D00,
  0x00571E56,
  0x00571F18,
  // Pin Widget 6 - PORT C - Configuration Default: 0x18560020
  0x00671C20,
  0x00671D00,
  0x00671E56,
  0x00671F18,
  // Pin Widget 7 - PORT D - Configuration Default: 0x18560030
  0x00771C30,
  0x00771D00,
  0x00771E56,
  0x00771F18,
  // Pin Widget 8 - PORT E - Configuration Default: 0x18560040
  // For GEN10+ forth port was added and Node ID 8 has this Pin Widget for the forth port
  0x00871C40,
  0x00871D00,
  0x00871E56,
  0x00871F18,
  // Disable the third converter and 4 Pins (NID 02h)
  0x00278100
);

HDAUDIO_VERB_TABLE HdaVerbTableAlc286S = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: (Realtek ALC286S)
  //  Revision ID = 0xff
  //  Codec Verb Table for SKL PCH boards
  //  Codec Address: CAd value (0/1/2)
  //  Codec Vendor: 0x10EC0286
  //
  0x10EC, 0x0286,
  0xFF, 0xFF,
  //===================================================================================================
  //
  //                               Realtek Semiconductor Corp.
  //
  //===================================================================================================

  //Realtek High Definition Audio Configuration - Version : 5.0.2.1
  //Realtek HD Audio Codec : ALC286
  //PCI PnP ID : PCI\VEN_0000&DEV_0000&SUBSYS_00000000
  //HDA Codec PnP ID : HDAUDIO\FUNC_01&VEN_10EC&DEV_0286&SUBSYS_00000000
  //The number of verb command block : 15

  //    NID 0x12 : 0x90A60130
  //    NID 0x13 : 0x40000000
  //    NID 0x14 : 0x90170110
  //    NID 0x17 : 0x411111F0
  //    NID 0x18 : 0x03A19020
  //    NID 0x19 : 0x411111F0
  //    NID 0x1A : 0x0381302F
  //    NID 0x1D : 0x4066832D
  //    NID 0x1E : 0x411111F0
  //    NID 0x21 : 0x0321101F

  //===== HDA Codec Subsystem ID Verb-table =====
  //HDA Codec Subsystem ID  : 0x00000000
  0x00172000,
  0x00172100,
  0x00172200,
  0x00172300,

  //===== Pin Widget Verb-table =====
  //Widget node 0x01 :
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  //Pin widget 0x12 - DMIC
  0x01271C40,
  0x01271D01,
  0x01271EA6,
  0x01271F90,
  //Pin widget 0x13 - DMIC
  0x01371C00,
  0x01371D00,
  0x01371E00,
  0x01371F40,
  //Pin widget 0x14 - SPEAKER-OUT (Port-D)
  0x01471C10,
  0x01471D01,
  0x01471E17,
  0x01471F90,
  //Pin widget 0x17 - I2S-OUT
  0x01771CF0,
  0x01771D11,
  0x01771E11,
  0x01771F41,
  //Pin widget 0x18 - MIC1 (Port-B)
  0x01871C30,
  0x01871D90,
  0x01871EA1,
  0x01871F03,
  //Pin widget 0x19 - I2S-IN
  0x01971CF0,
  0x01971D11,
  0x01971E11,
  0x01971F41,
  //Pin widget 0x1A - LINE1 (Port-C)
  0x01A71C3F,
  0x01A71D30,
  0x01A71E81,
  0x01A71F03,
  //Pin widget 0x1D - PC-BEEP
  0x01D71C2D,
  0x01D71D23,
  0x01D71E66,
  0x01D71F40,
  //Pin widget 0x1E - S/PDIF-OUT
  0x01E71CF0,
  0x01E71D11,
  0x01E71E11,
  0x01E71F41,
  //Pin widget 0x21 - HP-OUT (Port-A)
  0x02171C20,
  0x02171D10,
  0x02171E21,
  0x02171F03,
  //Widget node 0x20 :
  0x02050071,
  0x02040014,
  0x02050010,
  0x02040C22,
  //Widget node 0x20 - 1 :
  0x0205004F,
  0x02045029,
  0x02050051,
  0x02045428,
  //Widget node 0x20 - 2 :
  0x0205002B,
  0x02040C50,
  0x0205002D,
  0x02041020,
  // New verbs from Realtek
  0x02050063,
  0x02042906
);

HDAUDIO_VERB_TABLE HdaVerbTableAlc298 = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: (Realtek ALC298)
  //  Revision ID = 0xff
  //  Codec Verb Table for SKL PCH boards
  //  Codec Address: CAd value (0/1/2)
  //  Codec Vendor: 0x10EC0298
  //
  0x10EC, 0x0298,
  0xFF, 0xFF,
  //===================================================================================================
  //
  //                               Realtek Semiconductor Corp.
  //
  //===================================================================================================

  //Realtek High Definition Audio Configuration - Version : 5.0.3.1
  //Realtek HD Audio Codec : ALC298
  //PCI PnP ID : PCI\VEN_8086&DEV_2668&SUBSYS_72708086
  //HDA Codec PnP ID :INTELAUDIO\FUNC_01&VEN_10EC&DEV_0298&SUBSYS_10EC11DC
  //The number of verb command block : 15

  //    NID 0x12 : 0x90A60130
  //    NID 0x13 : 0x40000000
  //    NID 0x14 : 0x90170110
  //    NID 0x17 : 0x411111F0
  //    NID 0x18 : 0x04A11040
  //    NID 0x19 : 0x411111F0
  //    NID 0x1A : 0x411111F0
  //    NID 0x1D : 0x40600001
  //    NID 0x1E : 0x411111F0
  //    NID 0x1F : 0x411111F0
  //    NID 0x21 : 0x04211020

  //===== HDA Codec Subsystem ID Verb-table =====
  //HDA Codec Subsystem ID  : 0x10EC11DC
  0x001720DC,
  0x00172111,
  0x001722EC,
  0x00172310,
  //===== Pin Widget Verb-table =====
  //Widget node 0x01 :
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  //Pin widget 0x12 - DMIC
  0x01271C30,
  0x01271D01,
  0x01271EA6,
  0x01271F90,
  //Pin widget 0x13 - DMIC
  0x01371C00,
  0x01371D00,
  0x01371E00,
  0x01371F40,
  //Pin widget 0x14 - SPEAKER-OUT (Port-D)
  0x01471C10,
  0x01471D01,
  0x01471E17,
  0x01471F90,
  //Pin widget 0x17 - I2S-OUT
  0x01771CF0,
  0x01771D11,
  0x01771E11,
  0x01771F41,
  //Pin widget 0x18 - MIC1 (Port-B)
  0x01871C40,
  0x01871D10,
  0x01871EA1,
  0x01871F04,
  //Pin widget 0x19 - I2S-IN
  0x01971CF0,
  0x01971D11,
  0x01971E11,
  0x01971F41,
  //Pin widget 0x1A - LINE1 (Port-C)
  0x01A71CF0,
  0x01A71D11,
  0x01A71E11,
  0x01A71F41,
  //Pin widget 0x1D - PC-BEEP
  0x01D71C01,
  0x01D71D00,
  0x01D71E60,
  0x01D71F40,
  //Pin widget 0x1E - S/PDIF-OUT
  0x01E71CF0,
  0x01E71D11,
  0x01E71E11,
  0x01E71F41,
  //Pin widget 0x1F - S/PDIF-IN
  0x01F71CF0,
  0x01F71D11,
  0x01F71E11,
  0x01F71F41,
  //Pin widget 0x21 - HP-OUT (Port-A)
  0x02171C20,
  0x02171D10,
  0x02171E21,
  0x02171F04,
  //Widget node 0x20 : global headset // internal speaker 1.9W/4ohm
  0x0205004F,
  0x02045009,
  0x0205006D,
  0x02048908,
  //Widget node 0x20-1 : 1 pin detect 2 port and if Pin8 floating its need internal pull high . This case had external pull high for Pin8
  0x02050062,
  0x0204AFE7,
  0x02050064,
  0x02047F01,
  //Widget node 0x20-2 : Set Pin55 to MCLK.
  0x0205002F,
  0x0204004C,
  0x02050019,
  0x02040217,
  //Widget node 0x20 - 3 :  I2S in SRC + Nonauto detect
  0x0205002B,
  0x02040D10,
  0x0205002D,
  0x02044020,
  //Widget node 0x20 - 4 :  LDO3 = 1.3V  I2S out config
  0x0205000E,
  0x02046F80,
  0x01771F00,
  0x01771F00,
  //Widget node 0x20 - 5 :HD-A parameter dynamic control  AI2SOUT need to set this command  Set Pin52 as cmos EAPD
  0x02050080,
  0x02045C52,
  0x02050033,
  0x02040204,
  //Widget node 0x20 - 6 :  To increase I2S Interface, EAPD and DMIC driving current
  0x02050036,
  0x02047BC0,
  0x02050079,
  0x02047BC0
);

//
// CNL codecs verb tables
//
HDAUDIO_VERB_TABLE HdaVerbTableAlc700 = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: (Realtek ALC700) CNL RVP
  //  Revision ID = 0xff
  //  Codec Verb Table for CNL PCH boards
  //  Codec Address: CAd value (0/1/2)
  //  Codec Vendor: 0x10EC0700
  //
  0x10EC, 0x0700,
  0xFF, 0xFF,
  //===================================================================================================
  //
  //                               Realtek Semiconductor Corp.
  //
  //===================================================================================================

  //Realtek High Definition Audio Configuration - Version : 5.0.3.0
  //Realtek HD Audio Codec : ALC700
  //PCI PnP ID : PCI\VEN_8086&DEV_2668&SUBSYS_72708086
  //HDA Codec PnP ID : HDAUDIO\FUNC_01&VEN_10EC&DEV_0700&SUBSYS_10EC10F2
  //The number of verb command block : 17

  //    NID 0x12 : 0x411111F0
  //    NID 0x13 : 0x40000000
  //    NID 0x14 : 0x411111F0
  //    NID 0x15 : 0x411111F0
  //    NID 0x16 : 0x411111F0
  //    NID 0x17 : 0x90170110
  //    NID 0x18 : 0x411111F0
  //    NID 0x19 : 0x04A11030
  //    NID 0x1A : 0x411111F0
  //    NID 0x1B : 0x411111F0
  //    NID 0x1D : 0x40622005
  //    NID 0x1E : 0x411111F0
  //    NID 0x1F : 0x411111F0
  //    NID 0x21 : 0x04211020
  //    NID 0x29 : 0x411111F0

  //===== HDA Codec Subsystem ID Verb-table =====
  //HDA Codec Subsystem ID  : 0x10EC10F2
  0x001720F2,
  0x00172110,
  0x001722EC,
  0x00172310,

  //===== Pin Widget Verb-table =====
  //Widget node 0x01 :
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  //Pin widget 0x12 - DMIC
  0x01271C00,
  0x01271D00,
  0x01271E00,
  0x01271F40,
  //Pin widget 0x13 - DMIC
  0x01371C00,
  0x01371D00,
  0x01371E00,
  0x01371F40,
  //Pin widget 0x14 - FRONT (Port-D)
  0x01471CF0,
  0x01471D11,
  0x01471E11,
  0x01471F41,
  //Pin widget 0x15 - I2S-OUT
  0x01571CF0,
  0x01571D11,
  0x01571E11,
  0x01571F41,
  //Pin widget 0x16 - LINE3 (Port-B)
  0x01671CF0,
  0x01671D11,
  0x01671E11,
  0x01671F41,
  //Pin widget 0x17 - I2S-OUT
  0x01771C10,
  0x01771D01,
  0x01771E17,
  0x01771F90,
  //Pin widget 0x18 - I2S-IN
  0x01871CF0,
  0x01871D11,
  0x01871E11,
  0x01871F41,
  //Pin widget 0x19 - MIC2 (Port-F)
  0x01971C30,
  0x01971D10,
  0x01971EA1,
  0x01971F04,
  //Pin widget 0x1A - LINE1 (Port-C)
  0x01A71CF0,
  0x01A71D11,
  0x01A71E11,
  0x01A71F41,
  //Pin widget 0x1B - LINE2 (Port-E)
  0x01B71CF0,
  0x01B71D11,
  0x01B71E11,
  0x01B71F41,
  //Pin widget 0x1D - PC-BEEP
  0x01D71C05,
  0x01D71D20,
  0x01D71E62,
  0x01D71F40,
  //Pin widget 0x1E - S/PDIF-OUT
  0x01E71CF0,
  0x01E71D11,
  0x01E71E11,
  0x01E71F41,
  //Pin widget 0x1F - S/PDIF-IN
  0x01F71CF0,
  0x01F71D11,
  0x01F71E11,
  0x01F71F41,
  //Pin widget 0x21 - HP-OUT (Port-I)
  0x02171C20,
  0x02171D10,
  0x02171E21,
  0x02171F04,
  //Pin widget 0x29 - I2S-IN
  0x02971CF0,
  0x02971D11,
  0x02971E11,
  0x02971F41,
  //Widget node 0x20 :
  0x02050045,
  0x02045289,
  0x0205004A,
  0x0204201B,
  //Widget node 0x20 - 1 :
  0x05850000,
  0x05843888,
  0x0205006F,
  0x02042C0B,


  //Widget node 0X20 for ALC1305   20160603 update
  0x02050024,
  0x02040010,
  0x02050026,
  0x02040000,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040004,
  0x02050028,
  0x02040600,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204003C,
  0x02050028,
  0x0204FFD0,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040080,
  0x02050028,
  0x02040080,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040080,
  0x02050028,
  0x02040880,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204003A,
  0x02050028,
  0x02040DFE,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204006A,
  0x02050028,
  0x0204005D,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204006C,
  0x02050028,
  0x02040442,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040005,
  0x02050028,
  0x02040880,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040006,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040008,
  0x02050028,
  0x0204B000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204002E,
  0x02050028,
  0x02040800,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204006A,
  0x02050028,
  0x020400C3,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204006C,
  0x02050028,
  0x0204D4A0,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204006A,
  0x02050028,
  0x020400CC,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204006C,
  0x02050028,
  0x0204400A,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204006A,
  0x02050028,
  0x020400C1,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204006C,
  0x02050028,
  0x02040320,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040039,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204003B,
  0x02050028,
  0x0204FFFF,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204003C,
  0x02050028,
  0x0204FC20,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204003A,
  0x02050028,
  0x02041DFE,
  0x02050029,
  0x0204B024,
  //
  0x02050024,
  0x02040010,
  0x02050026,
  0x020400C0,
  0x02050028,
  0x020401FA,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400C1,
  0x02050028,
  0x0204DE23,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400C2,
  0x02050028,
  0x02041C00,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400C3,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400C4,
  0x02050028,
  0x02040200,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400C5,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400C6,
  0x02050028,
  0x020403F5,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400C7,
  0x02050028,
  0x0204AF1B,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400C8,
  0x02050028,
  0x02041E0A,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400C9,
  0x02050028,
  0x0204368E,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400CA,
  0x02050028,
  0x020401FA,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400CB,
  0x02050028,
  0x0204DE23,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400CC,
  0x02050028,
  0x02041C00,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400CD,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400CE,
  0x02050028,
  0x02040200,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400CF,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400D0,
  0x02050028,
  0x020403F5,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400D1,
  0x02050028,
  0x0204AF1B,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400D2,
  0x02050028,
  0x02041E0A,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x020400D3,
  0x02050028,
  0x0204368E,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040040,
  0x02050028,
  0x0204800F,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040062,
  0x02050028,
  0x02048000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040063,
  0x02050028,
  0x02044848,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040064,
  0x02050028,
  0x02040800,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040065,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040066,
  0x02050028,
  0x02044004,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040067,
  0x02050028,
  0x02040802,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040068,
  0x02050028,
  0x0204890F,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040069,
  0x02050028,
  0x0204E021,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040070,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040071,
  0x02050000,
  0x02043330,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040072,
  0x02050000,
  0x02043333,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040073,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040074,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040075,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040076,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040050,
  0x02050028,
  0x020402EC,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040051,
  0x02050028,
  0x02044909,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040052,
  0x02050028,
  0x020440B0,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040046,
  0x02050028,
  0x0204C22E,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040047,
  0x02050028,
  0x02040C00,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040048,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040049,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204004A,
  0x02050028,
  0x02040000,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204004B,
  0x02050028,
  0x02041C00,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204006A,
  0x02050028,
  0x02040090,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204006C,
  0x02050028,
  0x0204721F,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x0204009E,
  0x02050028,
  0x02040001,
  0x02050029,
  0x0204B024,

  0x02050024,
  0x02040010,
  0x02050026,
  0x02040004,
  0x02050028,
  0x02040500,
  0x02050029,
  0x0204B024
); // HdaVerbTableAlc700

HDAUDIO_VERB_TABLE HdaVerbTableAlc701 = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: (Realtek ALC701) CNL external kit
  //  Revision ID = 0xff
  //  Codec Verb Table for CNL PCH boards
  //  Codec Address: CAd value (0/1/2)
  //  Codec Vendor: 0x10EC0701
  //
  0x10EC, 0x0701,
  0xFF, 0xFF,
  //===================================================================================================
  //
  //                               Realtek Semiconductor Corp.
  //
  //===================================================================================================

  //Realtek High Definition Audio Configuration - Version : 5.0.3.0
  //Realtek HD Audio Codec : ALC701
  //PCI PnP ID : PCI\VEN_8086&DEV_2668&SUBSYS_72708086
  //HDA Codec PnP ID : HDAUDIO\FUNC_01&VEN_10EC&DEV_0701&SUBSYS_10EC10F4
  //The number of verb command block : 17

  //    NID 0x12 : 0x40000000
  //    NID 0x13 : 0x411111F0
  //    NID 0x14 : 0x411111F0
  //    NID 0x15 : 0x411111F0
  //    NID 0x16 : 0x411111F0
  //    NID 0x17 : 0x411111F0
  //    NID 0x18 : 0x411111F0
  //    NID 0x19 : 0x04A11020
  //    NID 0x1A : 0x411111F0
  //    NID 0x1B : 0x411111F0
  //    NID 0x1D : 0x40451B05
  //    NID 0x1E : 0x411111F0
  //    NID 0x1F : 0x411111F0
  //    NID 0x21 : 0x04211010
  //    NID 0x29 : 0x411111F0


  //===== HDA Codec Subsystem ID Verb-table =====
  //HDA Codec Subsystem ID  : 0x10EC10F4
  0x001720F4,
  0x00172110,
  0x001722EC,
  0x00172310,

  //===== Pin Widget Verb-table =====
  //Widget node 0x01 :
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  //Pin widget 0x12 - DMIC
  0x01271C00,
  0x01271D00,
  0x01271E00,
  0x01271F40,
  //Pin widget 0x13 - DMIC
  0x01371CF0,
  0x01371D11,
  0x01371E11,
  0x01371F41,
  //Pin widget 0x14 - FRONT (Port-D)
  0x01471CF0,
  0x01471D11,
  0x01471E11,
  0x01471F41,
  //Pin widget 0x15 - I2S-OUT
  0x01571CF0,
  0x01571D11,
  0x01571E11,
  0x01571F41,
  //Pin widget 0x16 - LINE3 (Port-B)
  0x01671CF0,
  0x01671D11,
  0x01671E11,
  0x01671F41,
  //Pin widget 0x17 - I2S-OUT
  0x01771CF0,
  0x01771D11,
  0x01771E11,
  0x01771F41,
  //Pin widget 0x18 - I2S-IN
  0x01871CF0,
  0x01871D11,
  0x01871E11,
  0x01871F41,
  //Pin widget 0x19 - MIC2 (Port-F)
  0x01971C20,
  0x01971D10,
  0x01971EA1,
  0x01971F04,
  //Pin widget 0x1A - LINE1 (Port-C)
  0x01A71CF0,
  0x01A71D11,
  0x01A71E11,
  0x01A71F41,
  //Pin widget 0x1B - LINE2 (Port-E)
  0x01B71CF0,
  0x01B71D11,
  0x01B71E11,
  0x01B71F41,
  //Pin widget 0x1D - PC-BEEP
  0x01D71C05,
  0x01D71D1B,
  0x01D71E45,
  0x01D71F40,
  //Pin widget 0x1E - S/PDIF-OUT
  0x01E71CF0,
  0x01E71D11,
  0x01E71E11,
  0x01E71F41,
  //Pin widget 0x1F - S/PDIF-IN
  0x01F71CF0,
  0x01F71D11,
  0x01F71E11,
  0x01F71F41,
  //Pin widget 0x21 - HP-OUT (Port-I)
  0x02171C10,
  0x02171D10,
  0x02171E21,
  0x02171F04,
  //Pin widget 0x29 - I2S-IN
  0x02971CF0,
  0x02971D11,
  0x02971E11,
  0x02971F41,
  //Widget node 0x20 :
  0x02050045,
  0x02045289,
  0x0205006F,
  0x02042C0B,

  //Widget node 0x20 - 1 :
  0x05850000,
  0x05843888,
  0x0205004A,
  0x0204201B,
); // HdaVerbTableAlc701

HDAUDIO_VERB_TABLE HdaVerbTableAlc274 = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: (Realtek ALC274) CNL external kit
  //  Revision ID = 0xff
  //  Codec Verb Table for CNL PCH boards
  //  Codec Address: CAd value (0/1/2)
  //  Codec Vendor: 0x10EC0274
  //
  0x10EC, 0x0274,
  0xFF, 0xFF,
  //===================================================================================================
  //
  //                               Realtek Semiconductor Corp.
  //
  //===================================================================================================

  //Realtek High Definition Audio Configuration - Version : 5.0.3.0
  //Realtek HD Audio Codec : ALC274
  //PCI PnP ID : PCI\VEN_8086&DEV_2668&SUBSYS_72708086
  //HDA Codec PnP ID : HDAUDIO\FUNC_01&VEN_10EC&DEV_0274&SUBSYS_10EC10F6
  //The number of verb command block : 16

  //    NID 0x12 : 0x40000000
  //    NID 0x13 : 0x411111F0
  //    NID 0x14 : 0x411111F0
  //    NID 0x15 : 0x411111F0
  //    NID 0x16 : 0x411111F0
  //    NID 0x17 : 0x411111F0
  //    NID 0x18 : 0x411111F0
  //    NID 0x19 : 0x04A11020
  //    NID 0x1A : 0x411111F0
  //    NID 0x1B : 0x411111F0
  //    NID 0x1D : 0x40451B05
  //    NID 0x1E : 0x411111F0
  //    NID 0x1F : 0x411111F0
  //    NID 0x21 : 0x04211010


  //===== HDA Codec Subsystem ID Verb-table =====
  //,DA Codec Subsystem ID  : 0x10EC10F6
  0x001720F6,
  0x00172110,
  0x001722EC,
  0x00172310,

  //===== Pin Widget Verb-table =====
  //Widget node 0x01 :
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  //Pin widget 0x12 - DMIC
  0x01271C00,
  0x01271D00,
  0x01271E00,
  0x01271F40,
  //Pin widget 0x13 - DMIC
  0x01371CF0,
  0x01371D11,
  0x01371E11,
  0x01371F41,
  //Pin widget 0x14 - NPC
  0x01471CF0,
  0x01471D11,
  0x01471E11,
  0x01471F41,
  //Pin widget 0x15 - I2S_OUT2
  0x01571CF0,
  0x01571D11,
  0x01571E11,
  0x01571F41,
  //Pin widget 0x16 - LINE3 (Port-B)
  0x01671CF0,
  0x01671D11,
  0x01671E11,
  0x01671F41,
  //Pin widget 0x17 - I2S_OUT1
  0x01771CF0,
  0x01771D11,
  0x01771E11,
  0x01771F41,
  //Pin widget 0x18 - I2S_IN
  0x01871CF0,
  0x01871D11,
  0x01871E11,
  0x01871F41,
  //Pin widget 0x19 - MIC2 (Port-F)
  0x01971C20,
  0x01971D10,
  0x01971EA1,
  0x01971F04,
  //Pin widget 0x1A - LINE1 (Port-C)
  0x01A71CF0,
  0x01A71D11,
  0x01A71E11,
  0x01A71F41,
  //Pin widget 0x1B - LINE2 (Port-E)
  0x01B71CF0,
  0x01B71D11,
  0x01B71E11,
  0x01B71F41,
  //Pin widget 0x1D - PC-BEEP
  0x01D71C05,
  0x01D71D1B,
  0x01D71E45,
  0x01D71F40,
  //Pin widget 0x1E - S/PDIF-OUT
  0x01E71CF0,
  0x01E71D11,
  0x01E71E11,
  0x01E71F41,
  //Pin widget 0x1F - S/PDIF-IN
  0x01F71CF0,
  0x01F71D11,
  0x01F71E11,
  0x01F71F41,
  //Pin widget 0x21 - HP-OUT (Port-I)
  0x02171C10,
  0x02171D10,
  0x02171E21,
  0x02171F04,
  //Widget node 0x20 :
  0x02050045,
  0x02045289,
  0x0205006F,
  0x02042C0B,
  //Widget node 0x20 - 1 :
  0x02050035,
  0x02048968,
  0x05B50001,
  0x05B48540,
  //Widget node 0x20 - 2 :
  0x05850000,
  0x05843888,
  0x05850000,
  0x05843888,
  //Widget node 0x20 - 3 :
  0x0205004A,
  0x0204201B,
  0x0205004A,
  0x0204201B
); //HdaVerbTableAlc274

HDAUDIO_VERB_TABLE HdaVerbTableAlc711 = HDAUDIO_VERB_TABLE_INIT (
  //
  //  VerbTable: (Realtek ALC711)
  //  Revision ID = 0xff
  //  Codec Verb Table
  //  Codec Address: CAd value (0/1/2)
  //  Codec Vendor: 0x10EC0700
  //
  0x10EC, 0x0711,
  0xFF, 0xFF,
 //===================================================================================================
//
//                               Realtek Semiconductor Corp.
//
//===================================================================================================
//
//Realtek High Definition Audio Configuration - Version : 5.0.3.1
//Realtek HD Audio Codec : ALC711
//PCI PnP ID : PCI\VEN_8086&DEV_2668&SUBSYS_72708086
//HDA Codec PnP ID : INTELAUDIO\FUNC_01&VEN_10EC&DEV_0700&SUBSYS_10EC11C2
//The number of verb command block : 17

//    NID 0x12 : 0x40000000
//    NID 0x13 : 0x411111F0
//    NID 0x14 : 0x411111F0
//    NID 0x15 : 0x411111F0
//    NID 0x16 : 0x411111F0
//    NID 0x17 : 0x411111F0
//    NID 0x18 : 0x411111F0
//    NID 0x19 : 0x04A11010
//    NID 0x1A : 0x411111F0
//    NID 0x1B : 0x411111F0
//    NID 0x1D : 0x40400001
//    NID 0x1E : 0x411111F0
//    NID 0x1F : 0x411111F0
//    NID 0x21 : 0x04211020
//    NID 0x29 : 0x411111F0


//===== HDA Codec Subsystem ID Verb-table =====
//HDA Codec Subsystem ID  : 0x10EC11C2
  0x001720C2,
  0x00172111,
  0x001722EC,
  0x00172310,

  //===== Pin Widget Verb-table =====
  //Widget node 0x01 :
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  0x0017FF00,
  //Pin widget 0x12 - DMIC
  0x01271C00,
  0x01271D00,
  0x01271E00,
  0x01271F40,
  //Pin widget 0x13 - DMIC
  0x01371CF0,
  0x01371D11,
  0x01371E11,
  0x01371F41,
  //Pin widget 0x14 - FRONT (Port-D)
  0x01471CF0,
  0x01471D11,
  0x01471E11,
  0x01471F41,
  //Pin widget 0x15 - I2S-OUT
  0x01571CF0,
  0x01571D11,
  0x01571E11,
  0x01571F41,
  //Pin widget 0x16 - LINE3 (Port-B)
  0x01671CF0,
  0x01671D11,
  0x01671E11,
  0x01671F41,
  //Pin widget 0x17 - I2S-OUT
  0x01771CF0,
  0x01771D11,
  0x01771E11,
  0x01771F41,
  //Pin widget 0x18 - I2S-IN
  0x01871CF0,
  0x01871D11,
  0x01871E11,
  0x01871F41,
  //Pin widget 0x19 - MIC2 (Port-F)
  0x01971C10,
  0x01971D10,
  0x01971EA1,
  0x01971F04,
  //Pin widget 0x1A - LINE1 (Port-C)
  0x01A71CF0,
  0x01A71D11,
  0x01A71E11,
  0x01A71F41,
  //Pin widget 0x1B - LINE2 (Port-E)
  0x01B71CF0,
  0x01B71D11,
  0x01B71E11,
  0x01B71F41,
  //Pin widget 0x1D - PC-BEEP
  0x01D71C01,
  0x01D71D00,
  0x01D71E40,
  0x01D71F40,
  //Pin widget 0x1E - S/PDIF-OUT
  0x01E71CF0,
  0x01E71D11,
  0x01E71E11,
  0x01E71F41,
  //Pin widget 0x1F - S/PDIF-IN
  0x01F71CF0,
  0x01F71D11,
  0x01F71E11,
  0x01F71F41,
  //Pin widget 0x21 - HP-OUT (Port-I)
  0x02171C20,
  0x02171D10,
  0x02171E21,
  0x02171F04,
  //Pin widget 0x29 - I2S-IN
  0x02971CF0,
  0x02971D11,
  0x02971E11,
  0x02971F41,
  //Widget node 0x20 - 1 :
  0x05B50010,
  0x05B4581D,
  0x0205006F,
  0x0204058B,

  //Widget node 0x20 - 2 :
  0x02050045,
  0x02045289,
  0x0205004A,
  0x0204201B,
); // HdaVerbTableAlc711
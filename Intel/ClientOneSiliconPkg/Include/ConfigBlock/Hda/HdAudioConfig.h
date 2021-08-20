/** @file
  HDAUDIO policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#ifndef _HDAUDIO_CONFIG_H_
#define _HDAUDIO_CONFIG_H_

#include <ConfigBlock.h>
#include <PchLimits.h>

#define HDAUDIO_PREMEM_CONFIG_REVISION 1
#define HDAUDIO_CONFIG_REVISION 1
#define HDAUDIO_DXE_CONFIG_REVISION 1

extern EFI_GUID gHdAudioPreMemConfigGuid;
extern EFI_GUID gHdAudioConfigGuid;
extern EFI_GUID gHdAudioDxeConfigGuid;

#pragma pack (push,1)

///
/// The PCH_HDAUDIO_CONFIG block describes the expected configuration of the Intel HD Audio feature.
///

#define HDAUDIO_VERB_TABLE_VIDDID(Vid,Did)                      (UINT32)((UINT16)Vid | ((UINT16)Did << 16))
#define HDAUDIO_VERB_TABLE_RID_SDI_SIZE(Rid,Sdi,VerbTableSize)  (UINT32)((UINT8)Rid | ((UINT8)Sdi << 8) | ((UINT16)VerbTableSize << 16))
#define HDAUDIO_VERB_TABLE_CMD_SIZE(VerbTable)                  ((sizeof (VerbTable) - sizeof (HDA_VERB_TABLE_HEADER)) / (sizeof (UINT32)))

///
/// Use this macro to create HDAUDIO_VERB_TABLE and populate size automatically
///
#define HDAUDIO_VERB_TABLE_INIT(Vid,Did,Rid,Sdi,...) \
{ \
  { Vid, Did, Rid, Sdi, (sizeof((UINT32[]){__VA_ARGS__})/sizeof(UINT32)) }, \
  { __VA_ARGS__ } \
}


/**
  Azalia verb table header
  Every verb table should contain this defined header and followed by azalia verb commands.
**/
typedef struct {
  UINT16  VendorId;             ///< Codec Vendor ID
  UINT16  DeviceId;             ///< Codec Device ID
  UINT8   RevisionId;           ///< Revision ID of the codec. 0xFF matches any revision.
  UINT8   SdiNum;               ///< SDI number, 0xFF matches any SDI.
  UINT16  DataDwords;           ///< Number of data DWORDs following the header.
} HDA_VERB_TABLE_HEADER;

#ifdef _MSC_VER
//
// Disable "zero-sized array in struct/union" extension warning.
// Used for neater verb table definitions.
//
#pragma warning (push)
#pragma warning (disable: 4200)
#endif
typedef struct  {
  HDA_VERB_TABLE_HEADER  Header;
  UINT32 Data[];
} HDAUDIO_VERB_TABLE;
#ifdef _MSC_VER
#pragma warning (pop)
#endif

typedef struct {
  UINT32   ClkA;            ///<  Pin mux configuration. Refer to GPIO_*_MUXING_DMIC*_CLKA_*
  UINT32   ClkB;            ///<  Pin mux configuration. Refer to GPIO_*_MUXING_DMIC*_CLKB_*
  UINT32   Data;            ///<  Pin mux configuration. Refer to GPIO_*_MUXING_DMIC*_DATA_*
} HDA_DMIC_PIN_MUX;

typedef struct {
  UINT32  Enable    :  1;  ///< HDA interface enable. When enabled related pins will be switched to native mode: <b>0: Disable</b>; 1: Enable.
  UINT32  RsvdBits0 : 31;
  UINT8   SdiEnable[PCH_MAX_HDA_SDI];  ///< HDA SDI signal enable. When enabled related SDI pins will be switched to appropriate native mode: <b>0: Disable</b>; 1: Enable
  UINT8   Reserved[(4 - (PCH_MAX_HDA_SDI % 4)) % 4];  ///< Padding for SDI enable table.
} HDA_LINK_HDA;

typedef struct {
  UINT32             Enable    :  1;  ///< HDA DMIC interface enable. When enabled related pins will be switched to native mode: <b>0: Disable</b>; 1: Enable.
  UINT32             RsvdBits0 : 31;
  HDA_DMIC_PIN_MUX   PinMux;          ///< Pin mux configuration.
} HDA_LINK_DMIC;

typedef struct {
  UINT32             Enable    :  1;  ///< HDA SSP interface enable. When enabled related pins will be switched to native mode: <b>0: Disable</b>; 1: Enable.
  UINT32             RsvdBits0 : 31;
} HDA_LINK_SSP;

typedef struct {
  UINT32             Enable    :  1;  ///< HDA SNDW interface enable. When enabled related pins will be switched to native mode: <b>0: Disable</b>; 1: Enable.
  UINT32             RsvdBits0 : 31;
} HDA_LINK_SNDW;


/**
  This structure contains the policies which are related to HD Audio device (cAVS).

  <b>Revision 1:</b>
  - Inital version.

**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;          ///< Config Block Header
  UINT32  Pme                   :  1;    ///< Azalia wake-on-ring, <b>0: Disable</b>; 1: Enable
  UINT32  CodecSxWakeCapability :  1;    ///< Capability to detect wake initiated by a codec in Sx (eg by modem codec), <b>0: Disable</b>; 1: Enable
  UINT32  HdAudioLinkFrequency  :  4;    ///< HDA-Link frequency (PCH_HDAUDIO_LINK_FREQUENCY enum): <b>2: 24MHz</b>, 1: 12MHz, 0: 6MHz
  UINT32  RsvdBits0             : 26;    ///< Reserved bits 0
  /**
    Number of the verb table entry defined in VerbTablePtr.
    Each entry points to a verb table which contains HDAUDIO_VERB_TABLE structure and verb command blocks.
  **/
  UINT8   VerbTableEntryNum;
  UINT8   Rsvd0[3];                         ///< Reserved bytes, align to multiple 4
  /**
    Pointer to a verb table array.
    This pointer points to 32bits address, and is only eligible and consumed in post mem phase.
    Each entry points to a verb table which contains HDAUDIO_VERB_TABLE structure and verb command blocks.
    The prototype of this is:
    HDAUDIO_VERB_TABLE **VerbTablePtr;
  **/
  UINT32  VerbTablePtr;
} HDAUDIO_CONFIG;

/**
  This structure contains the premem policies which are related to HD Audio device (cAVS).

  <b>Revision 1:</b>
  - Inital version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;          ///< Config Block Header
  UINT32  Enable                :  1;    ///< Intel HD Audio (Azalia) enablement: 0: Disable, <b>1: Enable</b>
  UINT32  DspEnable             :  1;    ///< DSP enablement: 0: Disable; <b>1: Enable</b>
  UINT32  VcType                :  1;    ///< Virtual Channel Type Select: <b>0: VC0</b>, 1: VC1
  /**
    Universal Audio Architecture compliance for DSP enabled system:
    <b>0: Not-UAA Compliant (Intel SST driver supported only)</b>,
       1: UAA Compliant (HDA Inbox driver or SST driver supported)
  **/
  UINT32  DspUaaCompliance      :  1;
  UINT32  IDispLinkFrequency    :  4;    ///< iDisp-Link frequency (PCH_HDAUDIO_LINK_FREQUENCY enum): <b>4: 96MHz</b>, 3: 48MHz
  UINT32  IDispLinkTmode        :  3;    ///< iDisp-Link T-Mode (PCH_HDAUDIO_IDISP_TMODE enum): <b>0: 2T</b>, 1: 1T, 2: 4T, 3: 8T, 4: 16T
  UINT32  IDispCodecDisconnect  :  1;    ///< iDisplay Audio Codec disconnection, <b>0: Not disconnected, enumerable</b>; 1: Disconnected SDI, not enumerable
  UINT32  RsvdBits              : 20;    ///< Reserved bits 0

  /**
    Audio Link Mode configuration bitmask.
    Allows to configure enablement of the following interfaces: HDA-Link, DMIC, SSP, SoundWire.
  **/

  HDA_LINK_HDA          AudioLinkHda;    ///< HDA-Link enablement: 0: Disable; <b>1: Enable</b>.
  /**
    DMIC link enablement: 0: Disable; <b>1: Enable</b>.
    DMIC0  LKF: Muxed with SNDW2/SNDW4.
  **/
  HDA_LINK_DMIC         AudioLinkDmic [PCH_MAX_HDA_DMIC_LINK_NUM];
  /**
    I2S/SSP link enablement: <b>0: Disable</b>; 1: Enable.
    SSP0/1 LKF: Muxed with HDA.
    @note Since the I2S/SSP2 pin set contains pads which are also used for CNVi purpose, enabling AudioLinkSsp2
    is exclusive with CNVi is present.
  **/
  HDA_LINK_SSP          AudioLinkSsp  [PCH_MAX_HDA_SSP_LINK_NUM];
  /**
    SoundWire link enablement: <b>0: Disable</b>; 1: Enable.
    SNDW2  LKF: Muxed with DMIC0/DMIC1.
    SNDW3  LKF: Muxed with DMIC1.
    SNDW4  LKF: Muxed with DMIC0.
  **/
  HDA_LINK_SNDW         AudioLinkSndw [PCH_MAX_HDA_SNDW_LINK_NUM];


  UINT16  ResetWaitTimer;                   ///< <b>(Test)</b> The delay timer after Azalia reset, the value is number of microseconds. Default is <b>600</b>.
  UINT8   Rsvd0[2];                         ///< Reserved bytes, align to multiple 4

} HDAUDIO_PREMEM_CONFIG;

typedef struct {
  UINT32  AutonomousClockStop        :  1;    ///< SoundWire1 link autonomous clock stop capability: <b>0: Disable</b>; 1: Enable
  UINT32  DataOnActiveIntervalSelect :  2;    ///< SoundWire1 link data on active interval select 0: 3 clock periods; <b>1: 4 clock periods</b>; 2: 5 clock periods; 3: 6 clock periods
  UINT32  DataOnDelaySelect          :  1;    ///< SoundWire1 link data on delay select 0: 2 clock periods; <b>1: 3 clock periods</b>
  UINT32  RsvdBits1                  : 28;    ///< Reserved bits 1
} HDAUDIO_SNDW_CONFIG;

/**
  This structure contains the DXE policies which are related to HD Audio device (cAVS).
  <b>Revision 1:</b>
  - Inital version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER        Header;          ///< Config Block Header
  /**
    SNDW configuration for exposed via SNDW ACPI tables:
  **/
  HDAUDIO_SNDW_CONFIG        SndwConfig[PCH_MAX_HDA_SNDW_LINK_NUM];
  /**
    Bitmask of supported DSP features:
    [BIT0] - WoV; [BIT1] - BT Sideband; [BIT2] - Codec VAD; [BIT5] - BT Intel HFP; [BIT6] - BT Intel A2DP
    [BIT7] - DSP based speech pre-processing disabled; [BIT8] - 0: Intel WoV, 1: Windows Voice Activation
    Default is <b>zero</b>.
  **/
  UINT32  DspFeatureMask;
} HDAUDIO_DXE_CONFIG;

#pragma pack (pop)

#endif // _HDAUDIO_CONFIG_H_

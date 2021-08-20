/** @file
  This module configures the memory controller address decoder.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include "MrcAddressDecodeConfiguration.h"

/**
  This function configures the zone configuration registers MAD-CR and MAD-ZR-CR.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Controller  - Controller to configure.

  @retval Nothing.
**/
void
ZoneConfiguration (
  IN OUT MrcParameters *const MrcData,
  IN     UINT32               Controller
  )
{
  static const UINT8  ChWidDecode[MAX_MRC_DDR_TYPE] = {2, 1, 0, 0, 0xFF};
  MrcInput            *Inputs;
  MrcOutput           *Outputs;
  MrcDebug            *Debug;
  MrcControllerOut    *ControllerOut;
  MrcChannelOut       *ChannelOut;
  INT64               ChLMap;
  INT64               StkdMode;
  INT64               StkdModeCh1;
  INT64               EnhancedChMode;
  INT64               StkdModeChHashBits;
  INT64               ChSSize;
  INT64               DramType;
  INT64               HashMode;
  INT64               LsbMaskBit;
  INT64               HashMask;
  INT64               McChWidth;
  UINT32              ChannelSizeMin;
  UINT32              ChannelSize[MAX_CHANNEL];
  UINT32              CapacityDivisor;
  UINT32              Channel;
  UINT32              Dimm;
  UINT32              SystemChannel;
  UINT32              SmallChIdx;
  BOOLEAN             FullLpChPop;
  MC0_CHANNEL_EHASH_STRUCT  ChannelEHash;

  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ControllerOut       = &Outputs->Controller[Controller];
  CapacityDivisor     = 512;
  StkdModeChHashBits  = 0;
  StkdMode            = 0;
  EnhancedChMode      = Outputs->EnhancedChannelMode;
  StkdModeCh1         = 0;
  DramType            = Outputs->DdrType;
  HashMode            = 0;
  SystemChannel       = (EnhancedChMode) ? ctChannel2 : ctChannel1;

  // Add up the amount of memory in each channel.
  FullLpChPop = TRUE;   // Assume all LPDDR channels (4x16) are populated in the controller.
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    ChannelSize[Channel] = 0;
    if (ChannelOut->Status == CHANNEL_PRESENT) {
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (ChannelOut->Dimm[Dimm].Status == DIMM_PRESENT) {
          ChannelSize[Channel] += ChannelOut->Dimm[Dimm].DimmCapacity;
        }
      }
    } else {
      // If any channel is not present in the controller, set the flag to false for LPDDR.
      FullLpChPop = FALSE;
    }
  }

  if (ChannelSize[SystemChannel] <= ChannelSize[ctChannel0]) {
    ChLMap = 0;
    ChannelSizeMin = ChannelSize[SystemChannel];
    SmallChIdx = SystemChannel;
  } else {
    //  ChannelSize0 < ChannelSize1
    ChLMap = 1;
    ChannelSizeMin = ChannelSize[ctChannel0];
    SmallChIdx = ctChannel0;
  }
  // Need to add the capacity of the second LP Channel in Enhanced Channel Mode
  // Channels must be homogeneous
  if (Outputs->EnhancedChannelMode) {
    SmallChIdx++;
    if (MrcChannelExist (MrcData, Controller, SmallChIdx)) {
      ChannelSizeMin += ChannelSize[SmallChIdx];
    }
  }
  ChSSize = ChannelSizeMin / CapacityDivisor;
    // Interleaved mode
    // Check for any Channel hash support
    if (Inputs->ChHashEnable) {
      HashMask = Inputs->ChHashMask;
      MrcGetSetMc (MrcData, Controller, GsmMccHashMask, WriteNoCache | PrintValue, &HashMask);

      LsbMaskBit = Inputs->ChHashInterleaveBit;
      MrcGetSetMc (MrcData, Controller, GsmMccLsbMaskBit, WriteNoCache | PrintValue, &LsbMaskBit);

      HashMode = 1;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel HASH Enabled\n");
    }

  MrcGetSetMc (MrcData, Controller, GsmMccHashMode, WriteNoCache | PrintValue, &HashMode);

  ChannelEHash.Data = 0;
  if (EnhancedChMode && FullLpChPop) {
    // EHASH can only be enabled if all LPDDR channels are populated on the controller.
    // If RI is off, EHASH must be off.
    ChannelEHash.Bits.EHASH_MODE = Inputs->RankInterleave;
    ChannelEHash.Bits.EHASH_LSB_MASK_BIT = 2;
    ChannelEHash.Bits.EHASH_MASK = 0x830;
  }
  MrcWriteCR (MrcData, OFFSET_CALC_CH (MC0_CHANNEL_EHASH_REG, MC1_CHANNEL_EHASH_REG, Controller), ChannelEHash.Data);

  McChWidth   = ChWidDecode[Outputs->DdrType];

  MrcGetSetMc (MrcData, Controller, GsmMccAddrDecodeDdrType,  ForceWriteCached | PrintValue, &DramType);
  MrcGetSetMc (MrcData, Controller, GsmMccChWidth,            WriteToCache     | PrintValue, &McChWidth);
  if (Inputs->A0) {
    // The registers associated with these GetSets only exist on TGL A0
    MrcGetSetMc (MrcData, Controller, GsmMccStackedMode,        WriteToCache     | PrintValue, &StkdMode);
    MrcGetSetMc (MrcData, Controller, GsmMccStackChMap,         WriteToCache     | PrintValue, &StkdModeCh1);
    MrcGetSetMc (MrcData, Controller, GsmMccStackedChHash,      WriteToCache     | PrintValue, &StkdModeChHashBits);
  }
  MrcGetSetMc (MrcData, Controller, GsmMccSChannelSize,       WriteToCache     | PrintValue, &ChSSize);
  MrcGetSetMc (MrcData, Controller, GsmMccLChannelMap,        WriteToCache     | PrintValue, &ChLMap);
  MrcFlushRegisterCachedData (MrcData);
}

/**
  This function configures the zone configuration registers MAD_SLICE.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
ControllerZoneConfiguration (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput          *Inputs;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  INT64             MsLMap;
  INT64             StkdMode;
  INT64             StkdModeMs1;
  INT64             StkdModeMsHashBits;
  INT64             MsSSize;
  INT64             HashMode;
  INT64             LsbMaskBit;
  INT64             HashMask;
  UINT32            ControllerSizeMin;
  UINT32            ControllerSize[MAX_CONTROLLER];
  UINT32            CapacityDivisor;
  UINT8             Channel;
  UINT8             Controller;
  UINT8             Dimm;
  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  CapacityDivisor     = 512;
  StkdModeMsHashBits  = 0;
  StkdMode            = 0;
  StkdModeMs1         = 0;
  HashMode            = 0;
  ControllerSize[cCONTROLLER0] = 0;
  ControllerSize[cCONTROLLER1] = 0;

  // Add up the amount of memory in each controller.
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    ControllerSize[Controller] = 0;
    if (ControllerOut->Status == CONTROLLER_PRESENT) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut            = &ControllerOut->Channel[Channel];
        if (ChannelOut->Status == CHANNEL_PRESENT) {
          if (ChannelOut->ValidSubChBitMask != 3) {
          }
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            if (ChannelOut->Dimm[Dimm].Status == DIMM_PRESENT) {
              ControllerSize[Controller] += ChannelOut->Dimm[Dimm].DimmCapacity;
            }
          }
        }
      }
    }
  }

  if (ControllerSize[cCONTROLLER1] <= ControllerSize[cCONTROLLER0]) {
    MsLMap = 0;
    ControllerSizeMin = ControllerSize[cCONTROLLER1];
  } else {
    // MemorySliceSize0 < MemorySliceSize1
    MsLMap = 1;
    ControllerSizeMin = ControllerSize[cCONTROLLER0];
  }
  MsSSize = ControllerSizeMin / CapacityDivisor;

  if ((ControllerSize[cCONTROLLER1] != 0) && (ControllerSize[cCONTROLLER0] != 0)) {
    Outputs->MemoryMapData.ILMem = ControllerSizeMin * 2;
  } else {
    Outputs->MemoryMapData.ILMem = 0;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Interleaved Memory between controllers %d Megabytes\n", Outputs->MemoryMapData.ILMem);
    // Interleaved mode
    // Check for any Memory Slice hash support
    if (Inputs->MsHashEnable) {
      HashMask = Inputs->MsHashMask;
      MrcGetSetNoScope (MrcData, GsmCmiHashMask, WriteNoCache | PrintValue, &HashMask);

      LsbMaskBit = Inputs->MsHashInterleaveBit;
      MrcGetSetNoScope (MrcData, GsmCmiLsbMaskBit, WriteNoCache | PrintValue, &LsbMaskBit);

      HashMode = 1;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Controller HASH Enabled\n");
    }

  MrcGetSetNoScope (MrcData, GsmCmiHashMode, WriteNoCache | PrintValue, &HashMode);

  MrcGetSetNoScope (MrcData, GsmCmiStackedMode,       WriteToCache | PrintValue, &StkdMode);
  MrcGetSetNoScope (MrcData, GsmCmiStackMsMap,        WriteToCache | PrintValue, &StkdModeMs1);
  MrcGetSetNoScope (MrcData, GsmCmiStackedMsHash,     WriteToCache | PrintValue, &StkdModeMsHashBits);
  MrcGetSetNoScope (MrcData, GsmCmiSMadSliceSize,     WriteToCache | PrintValue, &MsSSize);
  MrcGetSetNoScope (MrcData, GsmCmiLMadSliceMap,      WriteToCache | PrintValue, &MsLMap);
  MrcFlushRegisterCachedData (MrcData);
}

/**
  This function configures the MAD_DIMM_CH0/1 register.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - Controller to configure.
  @param[in] Channel    - Channel to configure.

  @retval Nothing.
**/
void
ChannelAddressDecodeConfiguration (
  IN MrcParameters *const MrcData,
  IN const UINT32         Controller,
  IN const UINT32         Channel
  )
{
  const MrcInput      *Inputs;
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  MrcControllerOut    *ControllerOut;
  MrcDimmOut          *DimmL;
  MrcDimmOut          *DimmS;
  MrcDimmOut          *LpOrDdrDimm1;
  MrcDdrType          DdrType;
  INT64               GetSetVal;
  INT64               DimmLMap;
  INT64               DLNOR;
  INT64               DSNOR;
  INT64               RankInterleave;
  INT64               EnhancedInterleave;
  INT64               EccMode;
  INT64               DimmLSize;
  INT64               DimmSSize;
  UINT32              DimmLDramWidth;
  UINT32              DimmSDramWidth;
  UINT32              Dimm0Capacity;
  UINT32              Dimm1Capacity;
  UINT32              Offset;
  UINT32              CapacityDivisor;
  UINT32              IpChannel;
  UINT32              DimmSize;
  BOOLEAN             Lpddr;
  MC0_CH0_CR_DDR_MR_PARAMS_STRUCT    DdrMrParams;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  ControllerOut     = &Outputs->Controller[Controller];
  ChannelOut        = &ControllerOut->Channel[Channel];
  DdrType           = Outputs->DdrType;
  DdrMrParams.Data  = 0;
  CapacityDivisor   = 512;
  DimmLDramWidth    = 0;
  DimmSDramWidth    = 0;
  DimmLSize         = 0;
  DimmSSize         = 0;
  DLNOR             = 0;
  DSNOR             = 0;

  // If we are in EnhancedChannelMode treat LPDDR Ch 1/3 as the second DIMM in the MC Channel.
  // Otherwise use DIMM1 in the same struct.
  LpOrDdrDimm1  = (Outputs->EnhancedChannelMode) ? &ControllerOut->Channel[Channel + 1].Dimm[dDIMM0] : &ChannelOut->Dimm[dDIMM1];
  DdrType       = MrcData->Outputs.DdrType;
  Lpddr         = Outputs->Lpddr;
  IpChannel     = LP_IP_CH (Lpddr, Channel);

  if (ChannelOut->Dimm[dDIMM0].Status == DIMM_PRESENT) {
    Dimm0Capacity = ChannelOut->Dimm[dDIMM0].DimmCapacity;
  } else {
    Dimm0Capacity = 0;
  }

  if (LpOrDdrDimm1->Status == DIMM_PRESENT) {
    Dimm1Capacity = (MAX_DIMMS_IN_CHANNEL > 1) ? LpOrDdrDimm1->DimmCapacity : 0;
  } else {
    Dimm1Capacity = 0;
  }

  // larger dimm will be located to Dimm L and small dimm will be located to dimm S
  if (Dimm1Capacity <= Dimm0Capacity) {
    DimmL = &ChannelOut->Dimm[dDIMM0];
    DimmS = LpOrDdrDimm1;
    // larger DIMM in capacity 0 - DIMM 0 or 1 - DIMM 1
    DimmLMap = 0;
  } else {
    DimmL = LpOrDdrDimm1;
    DimmS = &ChannelOut->Dimm[dDIMM0];
    // larger DIMM in capacity 0 - DIMM 0 or 1 - DIMM 1
    DimmLMap = 1;
  }
  // Dimm L
  if ((0 < DimmL->RankInDimm) && (DimmL->Status == DIMM_PRESENT)) {
    DimmLSize = DimmL->DimmCapacity / CapacityDivisor;
    if ((Lpddr) && (Inputs->CpuModel == cmTGL_ULX_ULT)) {
      // For non-power of two device sizes we need to program DIMM_L/S_SIZE to the nearest power of two.
      DimmSize = (UINT32) DimmLSize;
      if (MrcCountBitsEqOne (DimmSize) == 2) { // 3, 6, 12, 24 etc.
        DimmLSize = (DimmSize * 4) / 3;        // Round up to the nearest power of two
      }
    }
    // RankInDimm must be 1 or 2, we test the case that the value is 0
    DLNOR = DimmL->RankInDimm - 1;
    // SDRAM width
    switch (DimmL->SdramWidth) {
      case 8:
        DimmLDramWidth = 0;
        break;

      case 16:
        DimmLDramWidth = 1;
        break;

      case 32:
      case 64:
        DimmLDramWidth = 2;
        break;
    }
  }
  // Dimm S
  if ((MAX_DIMMS_IN_CHANNEL > 1) && (0 < DimmS->RankInDimm) && (DimmS->Status == DIMM_PRESENT)) {
    DimmSSize = DimmS->DimmCapacity / CapacityDivisor;
    if ((Lpddr) && (Inputs->CpuModel == cmTGL_ULX_ULT)) {
      // For non-power of two device sizes we need to program DIMM_L/S_SIZE to the nearest power of two.
      DimmSize = (UINT32) DimmSSize;
      if (MrcCountBitsEqOne (DimmSize) == 2) { // 3, 6, 12, 24 etc.
        DimmSSize = (DimmSize * 4) / 3;        // Round up to the nearest power of two
      }
    }
    // RankInDimm must be 1 or 2, we test the case that this value is 0.
    DSNOR = DimmS->RankInDimm - 1;
    // SDRAM width
    switch (DimmS->SdramWidth) {
      case 8:
        DimmSDramWidth = 0;
        break;

      case 16:
        DimmSDramWidth = 1;
        break;

      case 32:
      case 64:
        DimmSDramWidth = 2;
        break;
    }
  }

  RankInterleave = (Inputs->RankInterleave) ? 1 : 0;
  EnhancedInterleave = (Inputs->EnhancedInterleave) ? 1 : 0;

  if (Outputs->EccSupport) {
    // Set to '01' - ECC is active in IO, ECC logic is not active.
    EccMode = emEccIoActive;
  } else {
    EccMode = 0;
  }

  // DIMM Config
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccLDimmSize,      WriteToCache | PrintValue, &DimmLSize);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccLDimmRankCnt,   WriteToCache | PrintValue, &DLNOR);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccSDimmSize,      WriteToCache | PrintValue, &DimmSSize);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccSDimmRankCnt,   WriteToCache | PrintValue, &DSNOR);
  GetSetVal = DimmLDramWidth;
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccLDimmDramWidth, WriteToCache | PrintValue, &GetSetVal);
  GetSetVal = DimmSDramWidth;
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccSDimmDramWidth, WriteToCache | PrintValue, &GetSetVal);

  //IntraChannel Config
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccLDimmMap,           WriteToCache | PrintValue, &DimmLMap);
  if (Inputs->A0) {
    // The registers associated with this GetSet only exist on TGL A0
    MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccRankInterleave,     WriteToCache | PrintValue, &RankInterleave);
  }
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccEnhancedInterleave, WriteToCache | PrintValue, &EnhancedInterleave);
  MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccEccMode,            WriteToCache | PrintValue, &EccMode);

  MrcFlushRegisterCachedData (MrcData);

  DdrMrParams.Bits.MR4_PERIOD = 0x200D;

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    DdrMrParams.Bits.DDR4_TS_readout_en = 1;
  }
  if (DimmLMap == 0) {
    DdrMrParams.Bits.Rank_0_width = DimmLDramWidth;
    DdrMrParams.Bits.Rank_1_width = DimmLDramWidth;
    DdrMrParams.Bits.Rank_2_width = DimmSDramWidth;
    DdrMrParams.Bits.Rank_3_width = DimmSDramWidth;
  } else {
    DdrMrParams.Bits.Rank_0_width = DimmSDramWidth;
    DdrMrParams.Bits.Rank_1_width = DimmSDramWidth;
    DdrMrParams.Bits.Rank_2_width = DimmLDramWidth;
    DdrMrParams.Bits.Rank_3_width = DimmLDramWidth;
  }

  Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_DDR_MR_PARAMS_REG, MC1_CH0_CR_DDR_MR_PARAMS_REG, Controller, MC0_CH1_CR_DDR_MR_PARAMS_REG, IpChannel);
  MrcWriteCR (MrcData, Offset, DdrMrParams.Data);

}

/**
  Initialize the MARS feature (Memory AwaRe Scrubber)

  @param[in] MrcData - Include all MRC global data.

  @retval none
**/
void
MrcMarsConfig (
  IN MrcParameters *const MrcData
  )
{
  /*
  UINT32  Index;
  UINT32  Data32;
  static const struct {
    UINT16 McReg;
    UINT16 IdpReg;
  } RegTable[] = {
    { MC0_MAD_INTER_CHANNEL_REG,  CCF_IDP_MAD_INTER_CHANNEL_REG },
    { MC0_MAD_INTRA_CH0_REG,      CCF_IDP_MAD_INTRA_CH0_REG     },
    { MC0_MAD_INTRA_CH1_REG,      CCF_IDP_MAD_INTRA_CH1_REG     },
    { MC0_MAD_DIMM_CH0_REG,       CCF_IDP_MAD_DIMM_CH0_REG      },
    { MC0_MAD_DIMM_CH1_REG,       CCF_IDP_MAD_DIMM_CH1_REG      },
    { MC0_CHANNEL_HASH_REG,       CCF_IDP_CHANNEL_HASH_REG      },
    { MC0_CHANNEL_EHASH_REG,      CCF_IDP_CHANNEL_EHASH_REG     }
  };
  CCF_IDP_MARS_ENABLE_STRUCT  MarsEnable;

  if (MrcData->Inputs.Mars == 0) {
    return;
  }
  // Copy from MC address decoding registers to CCF IDP register.
  // They have exactly the same format, so can copy as is.
  // @todo Some future SKU might have 2 IDP blocks, need to program both in this case.
  for (Index = 0; Index < ARRAY_COUNT (RegTable); Index++) {
    Data32 = MrcReadCR (MrcData, RegTable[Index].McReg);
    MrcWriteCR (MrcData, RegTable[Index].IdpReg, Data32);
  }

  MarsEnable.Data = 0;
  MarsEnable.Bits.MARS_Enable = 1;
  MrcWriteCR (MrcData, CCF_IDP_MARS_ENABLE_REG, MarsEnable.Data);
  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "MARS Enabled\n");
  */
  return;
}

/**
  This function is the main address decoding configuration function.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
MrcAdConfiguration (
  IN MrcParameters *const MrcData
  )
{
  UINT32      Controller;
  UINT32      Channel;
  BOOLEAN     Lpddr;

  Lpddr = MrcData->Outputs.Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (!MrcControllerExist (MrcData, Controller)) {
      continue;
    }
    ZoneConfiguration (MrcData, Controller);
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
        // For LPDDR4/5, only program register on even channels.
        continue;
      }
      ChannelAddressDecodeConfiguration (MrcData, Controller, Channel);
    } // for Channel
  } // for Controller

  // Initialize the MARS feature (Memory AwaRe Scrubber)
  // This has to be done once all the MC Address Decode register are programmed
  MrcMarsConfig (MrcData);

  return;
}

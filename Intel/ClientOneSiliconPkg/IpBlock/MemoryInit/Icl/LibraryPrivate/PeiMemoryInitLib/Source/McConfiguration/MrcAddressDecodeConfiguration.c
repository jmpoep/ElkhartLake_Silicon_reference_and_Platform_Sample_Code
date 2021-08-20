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

#if (MAX_CHANNEL > 2)
#error This module only supports a maximum of 2 channels.
#endif
#if (MAX_DIMMS_IN_CHANNEL > 2)
#error This module only supports a maximum of 2 DIMMs per channel.
#endif

/**
  This function configures the zone configuration registers MAD-CR and MAD-ZR-CR.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
ZoneConfiguration (
  IN OUT MrcParameters *const MrcData
)
{
  MrcInput                              *Inputs;
  MrcOutput                             *Outputs;
  MrcDebug                              *Debug;
  MrcControllerOut                      *ControllerOut;
  MrcChannelOut                         *ChannelOut;
  MrcChannelOut                         *ChannelOut0;
  MrcChannelOut                         *ChannelOut1;
  INT64                                 ChLMap;
  INT64                                 StkdMode;
  INT64                                 StkdModeCh1;
  INT64                                 EnhancedChMode;
  INT64                                 StkdModeChHashBits;
  INT64                                 ChSSize;
  INT64                                 DramType;
  INT64                                 HashMode;
  INT64                                 LsbMaskBit;
  INT64                                 HashMask;
  UINT32                                ChannelSizeMin;
  UINT32                                ChannelSize[MAX_CHANNEL];
  UINT32                                CapacityDivisor;
  UINT8                                 Channel;
  UINT8                                 Dimm;
  BOOLEAN                               TwoSubChPopulated;
  CHANNEL_EHASH_STRUCT                  ChannelEHash;

  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ControllerOut       = &Outputs->Controller[0];
  CapacityDivisor     = 512;
  StkdModeChHashBits  = 0;
  StkdMode            = 0;
  EnhancedChMode      = Outputs->EnhancedChannelMode;
  StkdModeCh1         = 0;
  DramType            = Outputs->DdrType;
  HashMode            = 0;

  //
  // Add up the amount of memory in each channel.
  //
  TwoSubChPopulated = TRUE;   // Assume both subch are populated on all channels
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut            = &ControllerOut->Channel[Channel];
    ChannelSize[Channel]  = 0;
    if (ChannelOut->Status == CHANNEL_PRESENT) {
      if (ChannelOut->ValidSubChBitMask != 3) {
        TwoSubChPopulated = FALSE;
      }
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (ChannelOut->Dimm[Dimm].Status == DIMM_PRESENT) {
          ChannelSize[Channel] += ChannelOut->Dimm[Dimm].DimmCapacity;
        }
      }
    }
  }

  ChannelOut0 = &ControllerOut->Channel[cCHANNEL0];
  ChannelOut1 = &ControllerOut->Channel[cCHANNEL1];
  if (ChannelSize[cCHANNEL1] <= ChannelSize[cCHANNEL0]) {
    ChLMap = 0;
    //
    // Set the virtual channel type according to the address decoding decision.
    //
    ChannelOut0->VirtualChannel = vcL;
    ChannelOut1->VirtualChannel = vcS;

    ChannelSizeMin              = ChannelSize[cCHANNEL1];
  } else {
    //
    //  ChannelSize0 < ChannelSize1
    //
    ChLMap = 1;

    //
    // Set the virtual channel type according to the address decoding decision.
    //
    ChannelOut0->VirtualChannel = vcS;
    ChannelOut1->VirtualChannel = vcL;

    ChannelSizeMin              = ChannelSize[cCHANNEL0];
  }

  ChSSize = ChannelSizeMin / CapacityDivisor;

    //
    // Interleaved mode
    // Check for any Channel hash support
    //
    if (Inputs->ChHashEnable) {
      HashMask = Inputs->ChHashMask;
      MrcGetSetDdrIoGroupController0 (MrcData, GsmMccHashMask, WriteNoCache | GSM_PRINT_VAL, &HashMask);

      LsbMaskBit = Inputs->ChHashInterleaveBit;
      MrcGetSetDdrIoGroupController0 (MrcData, GsmMccLsbMaskBit, WriteNoCache | GSM_PRINT_VAL, &LsbMaskBit);

      HashMode = 1;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel HASH Enabled\n");
    }

  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccHashMode, WriteNoCache | GSM_PRINT_VAL, &HashMode);

  ChannelEHash.Data = 0;
  if (Inputs->ChHashEnable && EnhancedChMode && TwoSubChPopulated) {
    // EHASH can only be enabled if both subch are populated on all enabled channels.
    // If RI is off, EHASH must be off.
    ChannelEHash.Bits.EHASH_MODE = Inputs->RankInterleave;
    ChannelEHash.Bits.EHASH_LSB_MASK_BIT = 2;
    ChannelEHash.Bits.EHASH_MASK = 0x830;
  }
  MrcWriteCR (MrcData, CHANNEL_EHASH_REG, ChannelEHash.Data);

  MrcEnableExtendedBankHashing (MrcData);

  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccAddrDecodeDdrType, ForceWriteCached | GSM_PRINT_VAL, &DramType);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccStackedMode,       WriteToCache | GSM_PRINT_VAL, &StkdMode);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccStackChMap,        WriteToCache | GSM_PRINT_VAL, &StkdModeCh1);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccStackedChHash,     WriteToCache | GSM_PRINT_VAL, &StkdModeChHashBits);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccSChannelSize,      WriteToCache | GSM_PRINT_VAL, &ChSSize);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccLChannelMap,       WriteToCache | GSM_PRINT_VAL, &ChLMap);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnhChannelMode,    WriteToCache | GSM_PRINT_VAL, &EnhancedChMode);
  MrcFlushRegisterCachedData (MrcData);
}

/**
  This function configures the MAD_DIMM_CH0/1 register.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] Channel  - Channel index

  @retval Nothing.
**/
void
ChannelAddressDecodeConfiguration (
  IN MrcParameters *const MrcData,
  IN const UINT32         Channel
)
{
  const MRC_FUNCTION  *MrcCall;
  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  MrcChannelOut   *ChannelOut;
  MrcDimmOut      *DimmL;
  MrcDimmOut      *DimmS;
  MrcDdrType      DdrType;
  INT64           GetSetVal;
  INT64           DimmLMap;
  INT64           DLNOR;
  INT64           DSNOR;
  INT64           DL8Gb;
  INT64           DS8Gb;
  INT64           RankInterleave;
  INT64           EnhancedInterleave;
  INT64           EccMode;
  INT64           DimmLSize;
  INT64           DimmSSize;
  UINT32          DimmLDramWidth;
  UINT32          DimmSDramWidth;
  UINT32          Dimm0Capacity;
  UINT32          Dimm1Capacity;
  UINT32          Offset;
  UINT32          CapacityDivisor;
  UINT32          DimmSize;
  BOOLEAN         Lpddr4;
  CH0_CR_DDR_MR_PARAMS_STRUCT    DdrMrParams;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  ChannelOut        = &Outputs->Controller[0].Channel[Channel];
  MrcCall           = Inputs->Call.Func;
  DdrType           = Outputs->DdrType;
  Lpddr4            = (DdrType == MRC_DDR_TYPE_LPDDR4);
  DdrMrParams.Data  = 0;
  CapacityDivisor   = 512;
  DimmLDramWidth    = 0;
  DimmSDramWidth    = 0;
  DL8Gb             = 0;
  DS8Gb             = 0;
  DimmLSize         = 0;
  DimmSSize         = 0;
  DLNOR             = 0;
  DSNOR             = 0;

  if (Outputs->EnhancedChannelMode && (ChannelOut->ValidSubChBitMask == 3)) {
    // Make sub-channels appear as DIMMs, capacity is divided evenly between DIMM0 and DIMM1
    ChannelOut->Dimm[dDIMM0].DimmCapacity /= 2;
    MrcCall->MrcCopyMem ((UINT8 *) &ChannelOut->Dimm[dDIMM1], (UINT8 *) &ChannelOut->Dimm[dDIMM0], sizeof (MrcDimmOut));
  }

  if (ChannelOut->Dimm[dDIMM0].Status == DIMM_PRESENT) {
    Dimm0Capacity = ChannelOut->Dimm[dDIMM0].DimmCapacity;
  } else {
    Dimm0Capacity = 0;
  }

  if (ChannelOut->Dimm[dDIMM1].Status == DIMM_PRESENT) {
    Dimm1Capacity = (MAX_DIMMS_IN_CHANNEL > 1) ? ChannelOut->Dimm[dDIMM1].DimmCapacity : 0;
  } else {
    Dimm1Capacity = 0;
  }

  //
  // larger dimm will be located to Dimm L and small dimm will be located to dimm S
  //
  if (Dimm1Capacity <= Dimm0Capacity) {
    DimmL = &ChannelOut->Dimm[dDIMM0];
    DimmS = &ChannelOut->Dimm[dDIMM1];
    //
    // larger DIMM in capacity 0 - DIMM 0 or 1 - DIMM 1
    //
    DimmLMap = 0;
  } else {
    DimmL = &ChannelOut->Dimm[dDIMM1];
    DimmS = &ChannelOut->Dimm[dDIMM0];
    //
    // larger DIMM in capacity 0 - DIMM 0 or 1 - DIMM 1
    //
    DimmLMap = 1;
  }
  //
  // Dimm L
  //
  if ((0 < DimmL->RankInDimm) && (DimmL->Status == DIMM_PRESENT)) {
    DimmLSize              = DimmL->DimmCapacity / CapacityDivisor;
    if (Lpddr4) {
      // For non-power of two device sizes we need to program DIMM_L/S_SIZE to the nearest power of two.
      DimmSize = (UINT32) DimmLSize;
      if (MrcCountBitsEqOne (DimmSize) == 2) { // 3, 6, 12, 24 etc.
        DimmLSize = (DimmSize * 4) / 3;        // Round up to the nearest power of two
      }
    }
    //
    // RankInDimm must be 1 or 2, we test the case that the value is 0
    //
    DLNOR             = DimmL->RankInDimm - 1;
    //
    // SDRAM width
    //
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
  //
  // Dimm S
  //
  if ((MAX_DIMMS_IN_CHANNEL > 1) && (0 < DimmS->RankInDimm) && (DimmS->Status == DIMM_PRESENT)) {
    DimmSSize              = DimmS->DimmCapacity / CapacityDivisor;
    if (Lpddr4) {
      // For non-power of two device sizes we need to program DIMM_L/S_SIZE to the nearest power of two.
      DimmSize = (UINT32) DimmSSize;
      if (MrcCountBitsEqOne (DimmSize) == 2) { // 3, 6, 12, 24 etc.
        DimmSSize = (DimmSize * 4) / 3;        // Round up to the nearest power of two
      }
    }
    //
    // RankInDimm must be 1 or 2, we test the case that this value is 0.
    //
    DSNOR             = DimmS->RankInDimm - 1;
    //
    // SDRAM width
    //
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
    //
    // Set to '01' - ECC is active in IO, ECC logic is not active.
    //
    EccMode = emEccIoActive;
  } else {
    EccMode = 0;
  }

  // DIMM Config
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccLDimmSize,      WriteToCache | GSM_PRINT_VAL, &DimmLSize);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccLDimmRankCnt,   WriteToCache | GSM_PRINT_VAL, &DLNOR);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccLDimm8Gb,       WriteToCache | GSM_PRINT_VAL, &DL8Gb);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccSDimmSize,      WriteToCache | GSM_PRINT_VAL, &DimmSSize);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccSDimmRankCnt,   WriteToCache | GSM_PRINT_VAL, &DSNOR);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccSDimm8Gb,       WriteToCache | GSM_PRINT_VAL, &DS8Gb);
  GetSetVal = DimmLDramWidth;
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccLDimmDramWidth, WriteToCache | GSM_PRINT_VAL, &GetSetVal);
  GetSetVal = DimmSDramWidth;
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccSDimmDramWidth, WriteToCache | GSM_PRINT_VAL, &GetSetVal);

  //IntraChannel Config
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccLDimmMap,           WriteToCache | GSM_PRINT_VAL, &DimmLMap);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccRankInterleave,     WriteToCache | GSM_PRINT_VAL, &RankInterleave);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccEnhancedInterleave, WriteToCache | GSM_PRINT_VAL, &EnhancedInterleave);
  MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccEccMode,            WriteToCache | GSM_PRINT_VAL, &EccMode);

  MrcFlushRegisterCachedData (MrcData);

  if (!Inputs->MrcSafeConfig) {
    DdrMrParams.Bits.MR4_PERIOD = 0x200D;

    if (DdrType == MRC_DDR_TYPE_DDR4) {
      DdrMrParams.Bits.DDR4_TS_readout_en = 1;
    }
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
  Offset = OFFSET_CALC_CH (CH0_CR_DDR_MR_PARAMS_REG, CH1_CR_DDR_MR_PARAMS_REG, Channel);
  MrcWriteCR (MrcData, Offset, DdrMrParams.Data);


  if (Outputs->EnhancedChannelMode && (ChannelOut->ValidSubChBitMask == 3)) {
    // Restore DIMM0 capacity and disable DIMM1
    ChannelOut->Dimm[dDIMM0].DimmCapacity *= 2;
    MrcCall->MrcSetMem ((UINT8 *) &ChannelOut->Dimm[dDIMM1], sizeof (MrcDimmOut), 0);
    ChannelOut->Dimm[dDIMM1].Status = DIMM_NOT_PRESENT;
  }
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
  MrcOutput         *Outputs;
  UINT8             Controller;
  UINT8             Channel;

  ZoneConfiguration (MrcData);

  Outputs = &MrcData->Outputs;
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }

      ChannelAddressDecodeConfiguration (MrcData, Channel);
    } // for Channel
  } // for Controller

  return;
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
  UINT32  Index;
  UINT32  Data32;
  UINT32  IdpOffset;
  BOOLEAN Idp1Exist;
  static const struct {
    UINT16 McReg;
    UINT16 IdpReg;
  } RegTable[] = {
    { MAD_INTER_CHANNEL_REG,  CCF_IDP_MAD_INTER_CHANNEL_REG },
    { MAD_INTRA_CH0_REG,      CCF_IDP_MAD_INTRA_CH0_REG     },
    { MAD_INTRA_CH1_REG,      CCF_IDP_MAD_INTRA_CH1_REG     },
    { MAD_DIMM_CH0_REG,       CCF_IDP_MAD_DIMM_CH0_REG      },
    { MAD_DIMM_CH1_REG,       CCF_IDP_MAD_DIMM_CH1_REG      },
    { CHANNEL_HASH_REG,       CCF_IDP_CHANNEL_HASH_REG      },
    { CHANNEL_EHASH_REG,      CCF_IDP_CHANNEL_EHASH_REG     }
  };
  CCF_IDP_MARS_ENABLE_STRUCT  MarsEnable;

  if (MrcData->Inputs.Mars == 0) {
    return;
  }

  IdpOffset = CCF_IDP1_CHANNEL_HASH_REG - CCF_IDP_CHANNEL_HASH_REG;
  Idp1Exist = FALSE;
  if (MrcData->Inputs.CpuModel == cmICL_DT_HALO_R) {
    Idp1Exist = ((MrcReadCR (MrcData, CCF_NCDECS_CR_PLAT_CONFIG_REG) & CCF_NCDECS_CR_PLAT_CONFIG_ENIDP1_MSK) != 0); // Check if bit 1 is set
  }

  // Copy from MC address decoding registers to CCF IDP register.
  // They have exactly the same format, so can copy as is.
  for (Index = 0; Index < ARRAY_COUNT (RegTable); Index++) {
    Data32 = MrcReadCR (MrcData, RegTable[Index].McReg);
    MrcWriteCR (MrcData, RegTable[Index].IdpReg, Data32);
    if (Idp1Exist) {
      MrcWriteCR (MrcData, RegTable[Index].IdpReg + IdpOffset, Data32);
    }
  }

  if (((MrcData->Inputs.CpuModel == cmICL_ULX_ULT) && (MrcData->Inputs.CpuStepping <= csIclB4)) ||
      ((MrcData->Inputs.CpuModel == cmICL_DT_HALO) && (MrcData->Inputs.CpuStepping == csIclP0))
     ) {
    return;
  }
  MarsEnable.Data = 0;
  MarsEnable.Bits.MARS_Enable = 1;
  MrcWriteCR (MrcData, CCF_IDP_MARS_ENABLE_REG, MarsEnable.Data);
  if (Idp1Exist) {
    MrcWriteCR (MrcData, CCF_IDP1_MARS_ENABLE_REG, MarsEnable.Data);
  }
  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "MARS Enabled\n");
}


/**
  This function configures the Extended Bank Hashing (EBH).

  @param[in] MrcData - Include all MRC global data.

  @retval none
**/
void
MrcEnableExtendedBankHashing (
  IN MrcParameters *const MrcData
  )
{
  UINT32                            Channel;
  MrcChannelOut                     *ChannelOut;
  MrcControllerOut                  *ControllerOut;
  MrcControllerIn                   *ControllerIn;
  MrcDimmOut                        *DimmOut;
  MrcDimmIn                         *DimmIn;
  MrcInput                          *Inputs;
  MrcOutput                         *Outputs;
  MrcDebug                          *Debug;
  MrcChannelIn                      *ChannelIn;
  UINT32                            Dimm;
  UINT32                            DimmCapacity;
  UINT8                             Ranks;
  UINT8                             SdramWidth;
  UINT32                            Offset;
  BOOLEAN                           FirstDimm;
  CH0_CR_MCMNTS_SPARE_STRUCT        McmntsSpare;

  Inputs                          = &MrcData->Inputs;
  Outputs                         = &MrcData->Outputs;
  Debug                           = &Outputs->Debug;
  ControllerOut                   = &Outputs->Controller[0];
  ControllerIn                    = &Inputs->Controller[0];
  FirstDimm                       = TRUE;
  DimmCapacity                    = 0;
  Ranks                           = 0;
  SdramWidth                      = 0;

  if (!Inputs->ExtendedBankHashing) {
    return;  //exit without enable EBH
  }

  if (Inputs->IclA0) {
    return;
  }

  //Can be only enabled when RIM and EIM
  if (!Inputs->RankInterleave || !Inputs->EnhancedInterleave){
    return;
  }

  //Check if 2 channels are occupied
  if (Outputs->ValidChBitMask != 3) {
    return;
  }

  // Check same rank occupancy in all channels
  if (ControllerOut->Channel[0].ValidRankBitMask != ControllerOut->Channel[1].ValidRankBitMask) {
    return;
  }

  // Check symmetrical DRAM configs, if same rank occupancy, rank size and device width
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    ChannelIn  = &ControllerIn->Channel[Channel];
    //Check LPDDR4 if 4 sub channels are occupied
    if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && (ChannelOut->ValidSubChBitMask != 3)) {
      return;
    }
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      DimmIn   = &ChannelIn->Dimm[Dimm];
      if (DimmIn->Status != DIMM_PRESENT) {
        continue;
      }
      DimmOut = &ChannelOut->Dimm[Dimm];
      if (FirstDimm) {
        DimmCapacity  = DimmOut->DimmCapacity;
        Ranks         = DimmOut->RankInDimm;
        SdramWidth    = DimmOut->SdramWidth;
        FirstDimm     = FALSE;
      } else {
        if ((DimmCapacity != DimmOut->DimmCapacity) ||
            (Ranks        != DimmOut->RankInDimm)   ||
            (SdramWidth   != DimmOut->SdramWidth)) {
          return;
        }
      }
    } // Dimm
  } // Channel

  // Enable EBH
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    Offset = OFFSET_CALC_CH (CH0_CR_MCMNTS_SPARE_REG, CH1_CR_MCMNTS_SPARE_REG, Channel);
    McmntsSpare.Data = MrcReadCR (MrcData, Offset);
    McmntsSpare.Bits.Decoder_EBH = 3;          // Enable EBH
    MrcWriteCR (MrcData, Offset, McmntsSpare.Data);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Extended Bank Hashing Enabled\n");

}



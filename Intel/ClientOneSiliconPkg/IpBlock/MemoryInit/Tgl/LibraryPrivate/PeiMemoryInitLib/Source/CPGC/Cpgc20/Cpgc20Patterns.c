/** @file
  This file implements functions for setting up the Pattern
  Generators for CPGC 2.0.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#include "MrcInterface.h"
#include "McAddress.h"
#include "MrcCpgcOffsets.h"
#include "MrcCommon.h"
#include "MrcDebugPrint.h"
#include "MrcCpgcApi.h"
#include "Cpgc20.h"
#include "Cpgc20Patterns.h"

/**
  This function configures the rotation rate for the PG (per Outputs->McChBitMask).
  If the RotateRate is 0, the hardware rotation is disabled.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  RotateRate    - Log2 count of how many transactions (SubSequence or Cacheline) before we rotate the PG.

  @retval - MrcStatus: mrcSuccess if McChBitMask are non-zero, mrcFail if McChBitMask = 0..
**/
MrcStatus
Cpgc20ConfigPgRotation (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                RotateRate
  )
{
  MrcOutput *Outputs;
  UINT32    Controller;
  UINT32    Channel;
  UINT32    Offset;
  UINT8     MaxChannel;
  UINT8     McChMask;
  MC0_CH0_CR_CPGC_DPAT_CFG_STRUCT CpgcDPatLaneRotate;

  Outputs    = &MrcData->Outputs;
  McChMask   = Outputs->McChBitMask;
  MaxChannel = Outputs->MaxChannels;

  if (RotateRate > MC0_CH0_CR_CPGC_DPAT_CFG_LANE_ROTATE_RATE_MAX) {
    MRC_CPGC_DEBUG_MSG (
      &Outputs->Debug,
      MSG_LEVEL_WARNING,
      "%sRotateRate %d exceeds max count %d\n",
      gWarnString,
      RotateRate,
      MC0_CH0_CR_CPGC_DPAT_CFG_LANE_ROTATE_RATE_MAX
      );
    RotateRate = MC0_CH0_CR_CPGC_DPAT_CFG_LANE_ROTATE_RATE_MAX;
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CPGC_DPAT_CFG_REG,
                MC1_CH0_CR_CPGC_DPAT_CFG_REG, Controller,
                MC0_CH1_CR_CPGC_DPAT_CFG_REG, Channel);
      CpgcDPatLaneRotate.Data = MrcReadCR (MrcData, Offset);
      if (CpgcDPatLaneRotate.Bits.LANE_ROTATE_RATE != RotateRate) {
        CpgcDPatLaneRotate.Bits.LANE_ROTATE_RATE = RotateRate;
        MrcWriteCR (MrcData, Offset, CpgcDPatLaneRotate.Data);
      }
    }
  }
  return (McChMask == 0) ? mrcFail : mrcSuccess;
}



/**
  This function sets up the CPGC data pattern configuration per Outputs->McChBitMask.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  LfsrPoly    - LFSR Polynominal applied to all UNISEQs
  @param[in]  PatCtlPtr   - Structure that stores start, Stop, IncRate and Dqpat for pattern.
  @param[in]  Index       - Which USQ to program pattern to

  @retval - MrcStatus: mrcSuccess if McChBitMask are non-zero, mrcFail if McChBitMask = 0.
**/
MrcStatus
Cpgc20DPatUsqCfg (
  IN  MrcParameters *const   MrcData,
  IN  MRC_PG_LFSR_TYPE       LfsrPoly,
  IN  MRC_PATTERN_CTL *const PatCtlPtr,
  IN  UINT8                  Index
  )
{
  MrcOutput                     *Outputs;
  UINT8                         McChMask;
  UINT8                         MaxChannel;
  UINT8                         Controller;
  UINT8                         Channel;
  UINT32                        Offset;
  MRC_PG_UNISEQ_TYPE            UniseqMode;
  MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_STRUCT  CpgcDpatUsqCfg;

  Outputs    = &MrcData->Outputs;
  McChMask   = Outputs->McChBitMask;
  MaxChannel = Outputs->MaxChannels;

  if (PatCtlPtr->DQPat == StaticPattern) {
    UniseqMode = MrcPgMuxPatBuffer;
  } else if (PatCtlPtr->DQPat == LMNVa) {
    UniseqMode = MrcPgMuxLmn;
  } else {
    UniseqMode = MrcPgMuxLfsr;
  }
  CpgcDpatUsqCfg.Data = 0;
  CpgcDpatUsqCfg.Bits.UNISEQ_MODE = UniseqMode;
  CpgcDpatUsqCfg.Bits.UNISEQ_LFSR_POLYNOMIAL_SIZE = LfsrPoly;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG,
                MC1_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG, Controller,
                MC0_CH1_CR_CPGC_DPAT_USQ_CFG_0_REG, Channel);
      Offset += (MC0_CH0_CR_CPGC_DPAT_USQ_CFG_1_REG - MC0_CH0_CR_CPGC_DPAT_USQ_CFG_0_REG) * Index;
      MrcWriteCR8 (MrcData, Offset, CpgcDpatUsqCfg.Data);
    }
  }
  return (McChMask == 0) ? mrcFail : mrcSuccess;
}

/**
  This function sets up the CPGC LFSR configuration per Outputs->McChBitMask.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  LfsrPoly    - LFSR Polynominal applied to all UNISEQs
  @param[in]  LaneRotate  - Lane Rotate Rate, should be log2(CPGC2_BASE_REPEATS.Base_Repeats+1) for BasicVA

  @retval - MrcStatus: mrcSuccess if McChBitMask are non-zero, mrcFail if McChBitMask = 0.
**/
MrcStatus
Cpgc20LfsrCfg (
  IN  MrcParameters *const   MrcData,
  IN  const UINT8            CmdPat,
  IN  UINT8                  LaneRotate
  )
{
  MrcOutput                               *Outputs;
  UINT8                                   Controller;
  UINT8                                   Channel;
  UINT8                                   MaxChannel;
  UINT8                                   McChMask;
  UINT32                                  Offset;
  MC0_CH0_CR_CPGC_DPAT_CFG_STRUCT  CpgcDpatCfg;

  Outputs          = &MrcData->Outputs;
  MaxChannel       = Outputs->MaxChannels;
  McChMask         = Outputs->McChBitMask;
  CpgcDpatCfg.Data = 0;
  CpgcDpatCfg.Bits.LANE_ROTATE_RATE = LaneRotate;
  if (!Outputs->EccSupport) {
    CpgcDpatCfg.Bits.ECC_DISABLE = 1;
  }
  if ((CmdPat == PatODTTA) || (CmdPat == PatWrRdTA)) {
    // Program LFSR Save/Restore.
    //@todo TGL, convert for CPGC2.0
    //    CpgcDpatCfg.Bits.RELOAD_LFSR_SEED_RATE = y; MIN (MrcLog2 (NumCL - 1) + 1, 7); // In Exponential mode MAX value is 7.  (Reload after 64 CLs)
    //    CpgcDpatCfg.Bits.SAVE_LFSR_SEED_RATE = x;
  }
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
        MC0_CH0_CR_CPGC_DPAT_CFG_REG,
        MC1_CH0_CR_CPGC_DPAT_CFG_REG, Controller,
        MC0_CH1_CR_CPGC_DPAT_CFG_REG, Channel);
      MrcWriteCR (MrcData, Offset, CpgcDpatCfg.Data);
    }
  }
  return (McChMask == 0) ? mrcFail : mrcSuccess;
}

/**
  This function sets up the CPGC LFSR configuration per Outputs->McChBitMask.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  Seed        - Seed to program
  @param[in]  Index       - Which UNISEQx to program seed to

  @retval - MrcStatus: mrcSuccess if McChBitMask are non-zero, mrcFail if McChBitMask = 0.
**/
MrcStatus
Cpgc20LfsrSeed (
  IN  MrcParameters *const   MrcData,
  IN  const UINT32           Seed,
  IN  const UINT8            Index
  )
{
  MrcOutput                             *Outputs;
  UINT32                                Offset;
  UINT8                                 McChMask;
  UINT8                                 MaxChannel;
  UINT8                                 Controller;
  UINT8                                 Channel;
  MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_STRUCT  CpgcLfsrSeed;

  CpgcLfsrSeed.Data = Seed;
  Outputs           = &MrcData->Outputs;
  McChMask          = Outputs->McChBitMask;
  MaxChannel        = Outputs->MaxChannels;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
        MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG,
        MC1_CH0_CR_CPGC_DPAT_UNISEQ_0_REG, Controller,
        MC0_CH1_CR_CPGC_DPAT_UNISEQ_0_REG, Channel);
      Offset += (MC0_CH0_CR_CPGC_DPAT_UNISEQ_1_REG - MC0_CH0_CR_CPGC_DPAT_UNISEQ_0_REG) * Index;
      MrcWriteCR (MrcData, Offset, CpgcLfsrSeed.Data);
    }
  }
  return (McChMask == 0) ? mrcFail : mrcSuccess;
}

/**
  This function sets the Data and ECC Lane Mask Enables (per Outputs->McChBitMask).
  If all bits in DataLaneMask and EccLaneMask are 0, then the DC/Invert feature is disabled.

  @param[in]  MrcData       - Pointer to global MRC data.
  @param[in]  DataLaneMask  - Bit-Mask of lanes to enable in this PG.
  @param[in]  EccLaneMask   - Bit-Mask of lanes to enable for ECC in this PG.

  @retval - MrcStatus: mrcSuccess if McChBitMask are non-zero, mrcFail if McChBitMask = 0.
**/
MrcStatus
Cpgc20SetPgInvDcEn (
  IN  MrcParameters *const  MrcData,
  IN  UINT64                DataLaneMask,
  IN  UINT8                 EccLaneMask
  )
{
  MrcOutput     *Outputs;
  UINT32        Controller;
  UINT32        Channel;
  UINT8         MaxChannel;
  UINT8         McChMask;
  UINT32        Offset;
  UINT64_STRUCT DataLaneMsk;
  MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_STRUCT       CpgcDPatInvDcCfg;
  MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_STRUCT  CpgcDpatInvMaskLowDWord;
  MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_STRUCT  CpgcDpatInvMaskHighDWord;

  Outputs          = &MrcData->Outputs;
  McChMask         = Outputs->McChBitMask;
  MaxChannel       = Outputs->MaxChannels;
  DataLaneMsk.Data = DataLaneMask;
  CpgcDpatInvMaskLowDWord.Data = DataLaneMsk.Data32.Low;
  CpgcDpatInvMaskHighDWord.Data = DataLaneMsk.Data32.High;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_REG,
                MC1_CH0_CR_CPGC_DPAT_INVDC_CFG_REG, Controller,
                MC0_CH1_CR_CPGC_DPAT_INVDC_CFG_REG, Channel);
      CpgcDPatInvDcCfg.Data = MrcReadCR (MrcData, Offset);
      if (CpgcDPatInvDcCfg.Bits.ECC_INV_DC_MASK != EccLaneMask) {
        CpgcDPatInvDcCfg.Bits.ECC_INV_DC_MASK = EccLaneMask;
        MrcWriteCR (MrcData, Offset, CpgcDPatInvDcCfg.Data);
      }

      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_REG,
                MC1_CH0_CR_CPGC_DPAT_INV_DC_MASK_LO_REG, Controller,
                MC0_CH1_CR_CPGC_DPAT_INV_DC_MASK_LO_REG, Channel);
      MrcWriteCR (MrcData, Offset, CpgcDpatInvMaskLowDWord.Data);

      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_REG,
                MC1_CH0_CR_CPGC_DPAT_INV_DC_MASK_HI_REG, Controller,
                MC0_CH1_CR_CPGC_DPAT_INV_DC_MASK_HI_REG, Channel);
      MrcWriteCR (MrcData, Offset, CpgcDpatInvMaskHighDWord.Data);
    }
  }
  return (McChMask == 0) ? mrcFail : mrcSuccess;
}

/**
  This function sets the Pattern Generators' Invert/DC configuration (per Outputs->McChBitMask).
  The invert mode inverts the selected lanes' values.  The DC mode sets the
  selected lanes to a DC value.

  When rotation is enabled, once the rotation rate is met, the LaneMask is rotated from
  LSb to MSb.  Bit 63 of data is rotated into bit 0 of ECC, and bit 7 of ECC is rotated
  to Bit 0 of data.

  @param[in]  MrcData             - Pointer to global MRC data.
  @param[in]  Mode                - Selects Invert (0) or DC mode (1).
  @param[in]  DcPolarity          - 0 = DC low. 1 = DC high.
  @param[in]  EnableRotate        - Enables the rotation feature for the Bit Enable Masks of ECC and Data.
  @param[in]  RotateRateExponent  - Programs the counter to rotate every 2^(RotateRateExponenet).
  @param[in]  BytegroupMapping    - Selects between 2 bytes of DPAT pattern generator to be applied to each DQ byte group.  MSB is the ECC byte group.

  @retval - MrcStatus: mrcSuccess if McChBitMask are non-zero, mrcFail if McChBitMask = 0.
**/
MrcStatus
Cpgc20SetPgInvDcCfg (
  IN  MrcParameters *const  MrcData,
  IN  CPGC20_INVERT_DC_MODE Mode,
  IN  UINT8                 DcPolarity,
  IN  BOOLEAN               EnableRotate,
  IN  UINT8                 RotateRateExponent,
  IN  UINT16                BytegroupMapping
  )
{
  MrcOutput *Outputs;
  UINT32    Controller;
  UINT32    Channel;
  UINT32    Offset;
  UINT8     MaxChannel;
  UINT8     McChMask;
  MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_STRUCT CpgcDPatInvDcCfg;
  MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_STRUCT CpgcDPatInvDcCfgOrig;

  Outputs               = &MrcData->Outputs;
  McChMask              = Outputs->McChBitMask;
  MaxChannel            = Outputs->MaxChannels;
  CpgcDPatInvDcCfg.Data = 0;
  CpgcDPatInvDcCfg.Bits.DC_OR_INV         = Mode;
  CpgcDPatInvDcCfg.Bits.DC_POL            = DcPolarity;
  CpgcDPatInvDcCfg.Bits.MASK_ROTATE_EN    = EnableRotate;
  CpgcDPatInvDcCfg.Bits.MASK_ROTATE_RATE  = RotateRateExponent;
  CpgcDPatInvDcCfg.Bits.BYTEGROUP_MAPPING = MIN (BytegroupMapping, MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_BYTEGROUP_MAPPING_MAX);
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CPGC_DPAT_INVDC_CFG_REG,
                MC1_CH0_CR_CPGC_DPAT_INVDC_CFG_REG, Controller,
                MC0_CH1_CR_CPGC_DPAT_INVDC_CFG_REG, Channel);
      CpgcDPatInvDcCfgOrig.Data = MrcReadCR (MrcData, Offset);
      CpgcDPatInvDcCfg.Bits.ECC_INV_DC_MASK = CpgcDPatInvDcCfgOrig.Bits.ECC_INV_DC_MASK;

      if (CpgcDPatInvDcCfg.Data != CpgcDPatInvDcCfgOrig.Data) {
        MrcWriteCR (MrcData, Offset, CpgcDPatInvDcCfg.Data);
      }
    }
  }
  return (McChMask == 0) ? mrcFail : mrcSuccess;
}
/**
  This function sets the Pattern Generators' Dpat Buffer Control. Useful for static pattern setup.

  @param[in]  MrcData             - Pointer to global MRC data.
  @param[in]  IncScale            - Exponential/Linear
  @param[in]  IncRate             - Pattern Generator's "lines" advancement rate
  @param[in]  Start               - Lane to start from
  @param[in]  Stop                - Lane to wrap ("stop") on

  @retval - MrcStatus: mrcSuccess if McChBitMask are non-zero, mrcFail if McChBitMask = 0.
**/
MrcStatus
Cpgc20SetDpatBufCtl (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                IncScale,
  IN  UINT16                IncRate,
  IN  UINT8                 Start,
  IN  UINT8                 Stop
  )
{
  MrcOutput *Outputs;
  UINT32    Controller;
  UINT32    Channel;
  UINT32    Offset;
  UINT8     McChBitMask;
  UINT8     MaxChannel;
  MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_STRUCT CpgcDpatAltBufCfg;

  Outputs     = &MrcData->Outputs;
  McChBitMask = Outputs->McChBitMask;
  MaxChannel  = Outputs->MaxChannels;
  CpgcDpatAltBufCfg.Data = 0;
  CpgcDpatAltBufCfg.Bits.BUF_PNTR_INC_SCALE = IncScale;
  CpgcDpatAltBufCfg.Bits.BUF_PNTR_INC_RATE  = IncRate;
  CpgcDpatAltBufCfg.Bits.BUF_STRT_PNTR      = Start;
  CpgcDpatAltBufCfg.Bits.BUF_END_PNTR       = Stop;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if ((MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel) == 0)) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_REG,
                MC1_CH0_CR_CPGC_DPAT_ALT_BUF_CFG_REG, Controller,
                MC0_CH1_CR_CPGC_DPAT_ALT_BUF_CFG_REG, Channel);
      MrcWriteCR (MrcData, Offset, CpgcDpatAltBufCfg.Data);
    }
  }
  return (McChBitMask == 0) ? mrcFail : mrcSuccess;
}


/**
  This function will program the Pattern Buffers in the CADB Pattern Generators for
    the specific Generator/Chunk for all enabled CADB engines.
  This function can be used to select what Pattern Buffers to target by passing setting
    NumChunks == ChunkStart.

  @param[in]  MrcData       - Pointer to global MRC Data.
  @param[in] McChBitMask    - Memory Controller Channel Bit mask for which test should be setup for.
  @param[in]  ChunkStart    - 0-based index of which chunk will receive the pattern.
  @param[in]  NumChunks     - 0-based index of how many chunks to write.  Pattern array must have this many entries.
  @param[in]  Pattern       - Pointer to an array of patterns to program to the selected generator[s].

  @retval - MrcStatus: mrcSuccess if McChBitMask are non-zero, mrcFail if McChBitMask = 0.
**/
MrcStatus
Cadb20ProgramPatGen (
  IN  MrcParameters     *const  MrcData,
  IN  UINT8                     McChBitMask,
  IN  UINT32                    ChunkStart,
  IN  UINT32                    NumChunks,
  IN  UINT64_STRUCT             Pattern[CADB_20_MAX_CHUNKS]
  )
{
  MrcOutput     *Outputs;
  MrcDebug      *Debug;
  UINT8         Controller;
  UINT8         Channel;
  UINT8         MaxChannel;
  UINT32        Index;
  UINT32        Offset;
  UINT32        BufOffset;

  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MaxChannel  = Outputs->MaxChannels;

  if ((ChunkStart + NumChunks) > CADB_20_MAX_CHUNKS) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s: Exceeded chunks avaliable\n", gErrString);
    return mrcFail;
  } else if (Pattern == NULL) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s: Pattern pointer is NULL\n", gErrString);
    return mrcFail;
  }

  BufOffset = MC0_CH0_CR_CADB_BUF_1_REG - MC0_CH0_CR_CADB_BUF_0_REG;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }

      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CADB_BUF_0_REG,
                MC1_CH0_CR_CADB_BUF_0_REG, Controller,
                MC0_CH1_CR_CADB_BUF_0_REG, Channel);
      Offset += (BufOffset * ChunkStart);

      for (Index = ChunkStart; Index < NumChunks; Index++) {
        MrcWriteCR64 (MrcData, Offset, Pattern[Index].Data);
        Offset += BufOffset;
      }
    }
  }
  return (McChBitMask == 0) ? mrcFail : mrcSuccess;
}

/**
  This function sets up the CADB DSEL Uniseq configuration.

  @param[in]  MrcData      - Pointer to global MRC data.
  @param[in]  UniseqMode   - Uniseq mode to program to all UniseqCfg.
  @param[in]  LfsrPolySize - LFSR Polynomial Size to program, note that this only has meaning when UniseqMode = MrcPgMuxLfsr.

  @retval - MrcStatus: mrcSuccess if McChBitMask are non-zero, mrcFail if McChBitMask = 0.
**/
MrcStatus
Cadb20UniseqCfg (
  IN  MrcParameters *const   MrcData,
  IN  MRC_PG_UNISEQ_TYPE     UniseqMode,
  IN  MRC_PG_LFSR_TYPE       LfsrPolySize
  )
{
  MrcOutput                                     *Outputs;
  UINT8                                         Controller;
  UINT8                                         Channel;
  UINT8                                         McChBitMask;
  UINT8                                         MaxChannel;
  UINT32                                        Index;
  UINT32                                        Offset;
  MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_STRUCT      CadbDselUniseqCfg;

  Outputs                = &MrcData->Outputs;
  McChBitMask            = Outputs->McChBitMask;
  MaxChannel             = Outputs->MaxChannels;
  CadbDselUniseqCfg.Data = 0;
  CadbDselUniseqCfg.Bits.UNISEQ_MODE = UniseqMode;
  CadbDselUniseqCfg.Bits.UNISEQ_LFSR_POLYNOMIAL_SIZE = LfsrPolySize;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG,
                MC1_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG, Controller,
                MC0_CH1_CR_CADB_DSEL_UNISEQ_CFG_0_REG, Channel);
      for (Index = 0; Index < CADB_20_NUM_DSEL_UNISEQ; Index++) {
        MrcWriteCR8 (MrcData, Offset, CadbDselUniseqCfg.Data);
        Offset += (MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_1_REG - MC0_CH0_CR_CADB_DSEL_UNISEQ_CFG_0_REG);
      }
    }
  }
  return (McChBitMask == 0) ? mrcFail : mrcSuccess;
}

/**
  This function sets up the CADB LFSR configuration.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  Seed        - Seed to program
  @param[in]  Index       - Which UNISEQx to program seed to

  @retval - MrcStatus: mrcSuccess if McChBitMask are non-zero, mrcFail if McChBitMask = 0.
**/
MrcStatus
Cadb20LfsrSeed (
  IN  MrcParameters *const   MrcData,
  IN  const UINT32           Seed,
  IN  const UINT8            Index
  )
{
  MrcOutput                                     *Outputs;
  UINT8                                         Controller;
  UINT8                                         Channel;
  UINT8                                         MaxChannel;
  UINT8                                         McChBitMask;
  MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_STRUCT     CadbLfsrSeed;
  UINT32                                        Offset;

  Outputs           = &MrcData->Outputs;
  McChBitMask       = Outputs->McChBitMask;
  MaxChannel        = Outputs->MaxChannels;
  CadbLfsrSeed.Data = Seed;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel) == 0) {
        continue;
      }
      Offset = OFFSET_CALC_MC_CH (
                MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG,
                MC1_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG, Controller,
                MC0_CH1_CR_CADB_DSEL_UNISEQ_PBUF_0_REG, Channel);
      Offset += (MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_1_REG - MC0_CH0_CR_CADB_DSEL_UNISEQ_PBUF_0_REG) * Index;
      MrcWriteCR (MrcData, Offset, CadbLfsrSeed.Data);
    }
  }

  return (McChBitMask == 0) ? mrcFail : mrcSuccess;
}

/**
  This function sets up CADB Start Delay
  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  Delay       - No. of (tCK * 2) ps delay because CADB StartTest is at 2x tCK clk.
**/
VOID
CadbStartDelay (
  IN  MrcParameters *const   MrcData,
  UINT8                      Delay
  )
{
  MrcOutput                   *Outputs;
  UINT32                      Controller;
  UINT32                      Channel;
  UINT32                      IpCh;
  UINT32                      Offset;
  BOOLEAN                     Lpddr;
  MC0_CH0_CR_CADB_DLY_STRUCT  CadbDly;
  Outputs   = &MrcData->Outputs;
  Lpddr = Outputs->Lpddr;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      if (!(IS_MC_SUB_CH (Lpddr, Channel))) {
        IpCh = LP_IP_CH (Lpddr, Channel);
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_CADB_DLY_REG, MC1_CH0_CR_CADB_DLY_REG, Controller, MC0_CH1_CR_CADB_DLY_REG, IpCh);
        CadbDly.Data = MrcReadCR (MrcData, Offset);
        CadbDly.Bits.START_DELAY = Delay;
        MrcWriteCR (MrcData, Offset, CadbDly.Data);
      }
    } // Ch
  } // Controller
}




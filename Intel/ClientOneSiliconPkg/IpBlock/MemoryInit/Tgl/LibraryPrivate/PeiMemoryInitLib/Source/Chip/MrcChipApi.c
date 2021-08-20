/** @file
  .

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include "MrcTypes.h"
#include "MrcInterface.h"
#include "MrcHalRegisterAccess.h"
#include "MrcCommon.h"
#include "MrcChipApi.h"
#include "MrcDdrIoApiInt.h"

#define GEN_MRS_FSM_PER_RANK_MAX    (12)
#define GEN_MRS_FSM_TIMING_SET_MAX  (4)
#define GEN_MRS_FSM_FLAT_TIME_MAX   (127)
#define GEN_MRS_FSM_TIME_SCALAR     (16)
#define GEN_MRS_FSM_TIME_SCALAR_BIT (0x80)
#define MC_NUM_REG_CH               (2)

/**
  This function configures the Generic MRS FSM shadow registers based on the MrData inputs.
  It will determine if it needs to use the per-rank feature if the MR value differs across ranks.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] MrData  - Pointer to an array of MR data to configure the MRS FSM with.

  @retval mrcSuccess if successful.
  @retval mrcFail if MrData pointer is null, the timing or per-rank registers are out of free entries.
**/
MrcStatus
MrcGenMrsFsmConfig (
  IN  MrcParameters *MrcData,
  IN  MRC_GEN_MRS_FSM_MR_TYPE MrData[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_MR_GEN_FSM]
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcDebug  *Debug;
  MrcOutput *Outputs;
  UINT32    Controller;
  UINT32    ControlRegNum;
  UINT32    Channel;
  UINT32    McCh;
  UINT32    MaxSubCh;
  UINT32    Offset;
  UINT32    PerRankSwitch;
  UINT32    Rank;
  UINT32    SubCh;
  UINT32    TimingSetIdx;
  UINT16    InitData;
  UINT16    MrDelay;
  UINT16    TimingSet[GEN_MRS_FSM_TIMING_SET_MAX];
  UINT8     ControlRegIdx;
  UINT8     PerRankIdx;
  UINT8     ShadowFieldIdx;
  UINT8     TimingEncode;
  UINT8     TimingSetNumValid;
  BOOLEAN   Done;
  BOOLEAN   Lpddr;
  BOOLEAN   MrPerRank;
  MRC_GEN_MRS_FSM_MR_TYPE *GenMrPtr;
  MC0_CH0_CR_MRS_FSM_CONTROL_STRUCT MrsFsmCtl;
  MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_STRUCT GenMrsFsmCtl;
  MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_STRUCT GenMrsFsmChVal;
  MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_STRUCT GenMrsFsmPerRankVal;
  MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_STRUCT GenMrsFsmTiming;

  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;
  MrcCall = MrcData->Inputs.Call.Func;
  Lpddr = Outputs->Lpddr;
  MaxSubCh = (Lpddr) ? 2 : 1;
  Rank = 0;
  Channel = 0;
  GenMrPtr = NULL;
  TimingSetNumValid = 0;
  GenMrsFsmTiming.Data = 0;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
     if (!MrcControllerExist (MrcData, Controller)) {
      // Skip unpopulated controllers.
      continue;
    }
    // Determine if the the MR value is the same across Sub-Channels and Ranks
    for (McCh = 0; McCh < MC_NUM_REG_CH; McCh++) {
      MrcCall->MrcSetMemWord (TimingSet, GEN_MRS_FSM_TIMING_SET_MAX, 0);
      TimingSetNumValid = 0;
      PerRankIdx = 0;
      for (ControlRegIdx = 0; ControlRegIdx < MAX_MR_GEN_FSM; ControlRegIdx++) {
        MrPerRank = FALSE;
        InitData  = MRC_UINT16_MAX;
        // Gate SubCh and Rank loops with MrPerRank == FALSE.
        // Once we find that they are different per rank; break out and start the register configuration
        for (SubCh = 0; ((SubCh < MaxSubCh) && (!MrPerRank)); SubCh++) {
          Channel = (McCh * MC_NUM_REG_CH) + SubCh;
          for (Rank = 0; ((Rank < MAX_RANK_IN_CHANNEL) && (!MrPerRank)); Rank++) {
            if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
              continue;
            }

            GenMrPtr = &MrData[Controller][Channel][Rank][ControlRegIdx];
            if (!GenMrPtr->Valid) {
              continue;
            }

            // Base Case
            if (InitData == MRC_UINT16_MAX) {
              InitData = GenMrPtr->MrData;
            } else if (InitData != GenMrPtr->MrData) { // Check that MR data is matching or needs to be per Rank
              MrPerRank = TRUE;
            }
          } // Rank
        } // SubCh

        // If InitData is not another value besides MRC_UINT16_MAX, then this ControlRegIdx
        // did not have a valid entry in the array for the subch's or ranks.  Skip this index.
        if (InitData == MRC_UINT16_MAX) {
          continue;
        }

        // Determine if there is a timing already.
        if (GenMrPtr == NULL) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "GenMrPtr is Null\n");
          return mrcFail;
        }
        // Need to scale from tCK to WCK
        MrDelay = GenMrPtr->Delay * 4;
        for (TimingSetIdx = 0; TimingSetIdx < TimingSetNumValid; TimingSetIdx++) {
          if (TimingSet[TimingSetIdx] == MrDelay) {
            break;
          }
        }
        // If not, add it if the register is not full.
        if (TimingSetIdx >= TimingSetNumValid) {
          if (MrDelay > GEN_MRS_FSM_FLAT_TIME_MAX) {
            // Round to the nearest multiple of the scalar based value and set the bit to enable the scalar
            TimingEncode = ((UINT8) DIVIDECEIL (MrDelay, GEN_MRS_FSM_TIME_SCALAR)) | GEN_MRS_FSM_TIME_SCALAR_BIT;
          } else {
            TimingEncode = (UINT8) MrDelay;
          }
          switch (TimingSetIdx) {
            case 0:
              GenMrsFsmTiming.Bits.TIMING_FIELD_0 = TimingEncode;
              break;

            case 1:
              GenMrsFsmTiming.Bits.TIMING_FIELD_1 = TimingEncode;
              break;

            case 2:
              GenMrsFsmTiming.Bits.TIMING_FIELD_2 = TimingEncode;
              break;

            case 3:
              GenMrsFsmTiming.Bits.TIMING_FIELD_3 = TimingEncode;
              break;

            default:
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_ERROR,
                "Generic FSM Timing is full - NumValid: %u, Index: %u, ControlRegIdx: %u, Mc: %u, IpCh: %u\n",
                TimingSetNumValid, TimingSetIdx, ControlRegIdx, Controller, McCh);
              return mrcFail;
          }
          Offset = OFFSET_CALC_MC_CH (
            MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG,
            MC1_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG,
            Controller,
            MC0_CH1_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG,
            McCh
            );
          MrcWriteCR (MrcData, Offset, GenMrsFsmTiming.Data);
          TimingSet[TimingSetIdx] = MrDelay;
          TimingSetNumValid++;
        }

        // Configure control register for this MR.
        GenMrsFsmCtl.Data = 0;
        GenMrsFsmCtl.Bits.ADDRESS = GenMrPtr->MrAddr;
        GenMrsFsmCtl.Bits.ACTIVE = GenMrPtr->Valid;
        GenMrsFsmCtl.Bits.TIMING_VALUE_POINTER = TimingSetIdx;
        if (MrPerRank) {
          GenMrsFsmCtl.Bits.PER_RANK = 1;
          GenMrsFsmCtl.Bits.PER_RANK_STORAGE_POINTER = PerRankIdx;
        }
        Offset = MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG +
          ((MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG - MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG) * Controller) +
          ((MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_0_REG - MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG) * McCh) +
          ((MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_1_REG - MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG) * ControlRegIdx);
        MrcWriteCR (MrcData, Offset, GenMrsFsmCtl.Data);

        // Configure MR Value in the Shadow or Per Rank registers.
        if (MrPerRank) {
          GenMrsFsmPerRankVal.Data = 0;
          for (SubCh = 0; SubCh < MaxSubCh; SubCh++) {
            Channel = (McCh * MC_NUM_REG_CH) + SubCh;
            for (Rank = 0; Rank < MAX_RANK_IN_DIMM; Rank++) {
              if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
                continue;
              }

              GenMrPtr = &MrData[Controller][Channel][Rank][ControlRegIdx];
              if (!GenMrPtr->Valid) {
                continue;
              }

              PerRankSwitch = (SubCh * MAX_RANK_IN_DIMM) + Rank;
              switch (PerRankSwitch) {
                case 0:
                  GenMrsFsmPerRankVal.Bits.SHADOW_0 = GenMrPtr->MrData;
                  break;

                case 1:
                  GenMrsFsmPerRankVal.Bits.SHADOW_1 = GenMrPtr->MrData;
                  break;

                case 2:
                  GenMrsFsmPerRankVal.Bits.SHADOW_2 = GenMrPtr->MrData;
                  break;

                case 3:
                  GenMrsFsmPerRankVal.Bits.SHADOW_3 = GenMrPtr->MrData;
                  break;

                default:
                  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Invalid case in Per Rank Switch: %d\n", PerRankSwitch);
                  return mrcFail;
              }
            }
          }
          MRC_DEBUG_ASSERT ((PerRankIdx < GEN_MRS_FSM_PER_RANK_MAX), Debug, "Number of per-rank instances has exceeded the max supported by the MC\n");
          Offset = MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG +
            ((MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG - MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG) * Controller) +
            ((MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG - MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG) * McCh) +
            ((MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_1_REG - MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG) * PerRankIdx);
          MrcWriteCR (MrcData, Offset, GenMrsFsmPerRankVal.Data);
          PerRankIdx++;
        } else {
          // Else, map it into the correct field of the Shadow Value (X % 4) where X is the control register instance.
          ControlRegNum = ControlRegIdx / 4;
          ShadowFieldIdx = ControlRegIdx % 4;

          // Find the first populated SubChannel or Rank and use that array entry to configure the shadow value.
          Done = FALSE;
          GenMrPtr = NULL;
          for (SubCh = 0; ((SubCh < MaxSubCh) && !Done); SubCh++) {
            for (Rank = 0; ((Rank < MAX_RANK_IN_CHANNEL) && !Done); Rank++) {
              Channel = (McCh * MC_NUM_REG_CH) + SubCh;
              if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
                GenMrPtr = &MrData[Controller][Channel][Rank][ControlRegIdx];
                Done = TRUE;
              }
            }
          }
          MRC_DEBUG_ASSERT ((GenMrPtr != NULL), Debug, "Did not find a populated SubCh/Rank\n");

          Offset = MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG +
            ((MC1_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG - MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG) * Controller) +
            ((MC0_CH1_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG - MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG) * McCh) +
            ((MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_1_REG - MC0_CH0_CR_GENERIC_MRS_FSM_SHADOW_VALUES_0_REG) * ControlRegNum);
          GenMrsFsmChVal.Data = MrcReadCR (MrcData, Offset);
          switch (ShadowFieldIdx) {
            case 0:
              GenMrsFsmChVal.Bits.SHADOW_0 = GenMrPtr->MrData;
              break;

            case 1:
              GenMrsFsmChVal.Bits.SHADOW_1 = GenMrPtr->MrData;
              break;

            case 2:
              GenMrsFsmChVal.Bits.SHADOW_2 = GenMrPtr->MrData;
              break;

            case 3:
              GenMrsFsmChVal.Bits.SHADOW_3 = GenMrPtr->MrData;
              break;
          }
          MrcWriteCR (MrcData, Offset, GenMrsFsmChVal.Data);
        }
      } // ControlRegIdx
    } // McCh
  } // Controller

  // Finally configure the MRS_FSM to use the Generic version if this is the first time sending the sequence
  if (!Outputs->JedecInitDone) {
    MrsFsmCtl.Data = 0;
    MrsFsmCtl.Bits.GENERIC_MRS_FSM_Enable = 1;
    MrsFsmCtl.Bits.do_ZQCL = 1;

    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        Offset = MC0_BC_CR_MRS_FSM_CONTROL_REG +
          ((MC1_BC_CR_MRS_FSM_CONTROL_REG - MC0_BC_CR_MRS_FSM_CONTROL_REG) * Controller);
        MrcWriteCR64 (MrcData, Offset, MrsFsmCtl.Data);
      }
    }
  }

  return mrcSuccess;
}

/**
  This function executes the MRS FSM and waits for the FSM to complete.
  If the FSM does not complete after 10 seconds, it will return an error message.

  @param[in] MrcData - Pointer to MRC global data.

  @retval mrcFail if the FSM is not idle.
  @retval mrcSuccess otherwise.
**/
MrcStatus
MrcGenMrsFsmRun (
  IN  MrcParameters *MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  MrcOutput *Outputs;
  UINT64    Timeout;
  UINT32    Controller;
  UINT32    Channel;
  UINT32    IpCh;
  UINT32    Offset;
  UINT8     MaxChannel;
  BOOLEAN   Lpddr;
  BOOLEAN   Flag;
  MC0_CH0_CR_MRS_FSM_RUN_STRUCT MrsFsmRun;

  Outputs = &MrcData->Outputs;
  MrcCall = MrcData->Inputs.Call.Func;
  Lpddr = Outputs->Lpddr;
  MaxChannel = Outputs->MaxChannels;

  // Start all FSM's in parallel
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        IpCh = LP_IP_CH (Lpddr, Channel);
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MRS_FSM_RUN_REG, MC1_CH0_CR_MRS_FSM_RUN_REG, Controller, MC0_CH1_CR_MRS_FSM_RUN_REG, IpCh);

        MrsFsmRun.Data = 0;
        MrsFsmRun.Bits.Run = 1;
        MrcWriteCR (MrcData, Offset, MrsFsmRun.Data);

        // If we're LPDDR and we are on Channel 0 or 2, increment channel additionally so we move to the next MC Channel.
        if (Lpddr && ((Channel % 2) == 0)) {
          Channel++;
        }
      }
    }
  }

  // Check that all FSM's are done
  Timeout = MrcCall->MrcGetCpuTime () + 10000; // 10 seconds timeout
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        IpCh = LP_IP_CH (Lpddr, Channel);
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MRS_FSM_RUN_REG, MC1_CH0_CR_MRS_FSM_RUN_REG, Controller, MC0_CH1_CR_MRS_FSM_RUN_REG, IpCh);

        do {
          MrsFsmRun.Data = MrcReadCR (MrcData, Offset);
          Flag = (MrsFsmRun.Bits.Run == 1);
        } while (Flag && (MrcCall->MrcGetCpuTime () < Timeout));
        if (Flag) {
          MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "Generic FSM is not idle\n");
          return mrcFail;
        }

        // If we're LPDDR and we are on Channel 0 or 2, increment channel additionally so we move to the next MC Channel.
        if (Lpddr && ((Channel % 2) == 0)) {
          Channel++;
        }
      }
    }
  }

  return mrcSuccess;
}

UINT32
MrcQclkToTck (
  IN  MrcParameters *const MrcData,
  IN  UINT32               Qclk
  )
{
  MrcOutput *Outputs;
  UINT32    RetVal;
  UINT32    Scalar;
  BOOLEAN   Gear2;

  Outputs = &MrcData->Outputs;
  Gear2 = Outputs->Gear2;

  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5) {
    Scalar = Gear2 ? 4 : 8;
  } else {
    Scalar = Gear2 ? 1 : 2;
  }

  RetVal = Qclk / Scalar;

  return RetVal;
}

/**
  Program MC/DDRIO registers to Gear1 or Gear2 mode.
  This only includes Gear2 mode enable/disable, not other registers that are impacted by gear mode.

  @param[in] MrcData - The MRC general data.
  @param[in] Gear2   - TRUE for Gear2, FALSE for Gear1

  @retval None
**/
VOID
MrcSetGear2 (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              Gear2
  )
{
  INT64     GetSetVal;

  GetSetVal = Gear2 ? 1 : 0;
  MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccGear2, WriteNoCache, &GetSetVal);

  DdrIoConfigGear2 (MrcData, Gear2);
}

UINT32
MrcTckToQclk (
  IN  MrcParameters *const MrcData,
  IN  UINT32               Tck
  )
{
  MrcOutput *Outputs;
  UINT32    RetVal;
  UINT32    Scalar;
  BOOLEAN   Gear2;

  Outputs = &MrcData->Outputs;
  Gear2 = Outputs->Gear2;

  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5) {
    Scalar = Gear2 ? 4 : 8;
  } else {
    Scalar = Gear2 ? 1 : 2;
  }

  RetVal = Tck * Scalar;

  return RetVal;
}

/**
  Programming of CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst

  @param[in] MrcData - The MRC global data.
  @param[in] BlockTrainReset - TRUE to BlockTrainReset for most training algos.  FALSE for specific training algos that need PiDivider sync.

**/
VOID
MrcBlockTrainResetToggle (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              BlockTrainReset
)
{
  UINT8   Value;
  UINT8   Index;
  UINT32  Offset;
  CH0CCC_CR_DDRCRCCCCLKCONTROLS_STRUCT  CccClkControls;

  Value = (BlockTrainReset) ? 1 : 0;

  for (Index = 0; Index < MAX_SYS_CHANNEL; Index++) {
    Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG, CH1CCC_CR_DDRCRCCCCLKCONTROLS_REG, Index);
    CccClkControls.Data = MrcReadCR (MrcData, Offset);
    if (CccClkControls.Bits.BlockTrainRst == Value) {
      continue;
    }
    CccClkControls.Bits.BlockTrainRst = Value;
    MrcWriteCR (MrcData, Offset, CccClkControls.Data);
  }
}

/**
  This function configures the DDRCRCMDBUSTRAIN register to values for normal mode.

  @param[in]  MrcData - Pointer to global MRC data.

  @retval none.
**/
VOID
MrcSetWritePreamble (
  IN  MrcParameters *const  MrcData
  )
{
  DATA_CR_DDRCRCMDBUSTRAIN_STRUCT   CmdBusTrain;

  // Configure Strobe
  CmdBusTrain.Data = 0;
  CmdBusTrain.Bits.DdrCRNumOfPulses = 3;
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRCRCMDBUSTRAIN_REG, CmdBusTrain.Data);
}

// TGL P0 has unsorted CCC channel instances. This table
// maps a System Channel index to a CCC Channel Instance
// modifier. This modifier indicates the position of the
// corresponding register offset relative to the P0 CCC
// CH0 instance.
//
// P0 CCC CH Instances sorted by register offset:
// CH Instance     | CH2 CH0 CH3 CH1 CH5 CH7 Ch4 CH6
// -------------------------------------------------
// Relative Offset |  -1   0   1   2   3   4   5   6
// to CH0 Instance |
INT8 CccChannelInstanceOffsetP0[MAX_SYS_CHANNEL] = {
  0, 2, -1, 1, 5, 3, 6, 4
};

// The offset between each CCC channel instance is constant across all CCC Registers. The offset
// only differs between TGL-U\Y and TGL-H.
#define TGL_ULXULT_CCC_CH_OFFSET (CH1CCC_CR_DDRCRCACOMP_REG - CH0CCC_CR_DDRCRCACOMP_REG)       // 0x100
#define TGL_H_CCC_CH_OFFSET      (CH0CCC_CR_DDRCRCACOMP_P0_REG - CH2CCC_CR_DDRCRCACOMP_P0_REG) //  0x80

/**
  Calculate the Unicast CCC Channel Register address for the input channel on the current SoC. The
  input register CH0 Offset must be the A0\B0 offset. This offset will be automatically adjusted for P0.

  @param[in] MrcData      - Pointer to MRC global data.
  @param[in] RegOffsetCh0 - The register offset for the CH0 instance of a CCC register. This must be
                            a TGL A0\B0 register offset.
  @param[in] Channel      - The system channel that must be accessed by the returned register offset.

  @retval UINT32 - The register offset to the requested channel for the current SoC.
**/
UINT32
MrcCrOffsetProjAdjCccCh (
  IN MrcParameters *const  MrcData,
  IN UINT32                RegOffsetCh0,
  IN UINT32                Channel
  )
{
  const MrcInput *Inputs;
  MrcOutput      *Outputs;
  MrcDebug       *Debug;
  UINT32         Offset;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;

  Offset = 0xFFFFFFFF;
  if (RegOffsetCh0 < CH0CCC_CR_DDRCRCACOMP_REG && RegOffsetCh0 > CH0CCC_CR_DCCLANESTATUS2_REG) {
    // Check that the inputs are winthin the known register offset range
    // for TGL A0\B0 CCC CH0 register instances.
    MRC_DEBUG_ASSERT (
      (RegOffsetCh0 >= CH0CCC_CR_DDRCRCACOMP_REG) || (RegOffsetCh0 <= CH0CCC_CR_DCCLANESTATUS2_REG), // 0x00003600 to 0x00003674
      Debug,
      "Error: Not a valid CCC Channel Register\n"
      );
  } else {
    if (Inputs->UlxUlt) {
      Offset = RegOffsetCh0 + (TGL_ULXULT_CCC_CH_OFFSET * Channel);
    } else {
      Offset = (RegOffsetCh0 | MRC_BIT7) + (TGL_H_CCC_CH_OFFSET * CccChannelInstanceOffsetP0[Channel]);
    }
  }

  return Offset;
}

/**
  Translate a TGL U\Y Register Offset to a TGL H Register Offset when the
  current processor is TGL H. The output is not guranteed to be correct if
  the input register offset is not a TGL U\Y register offset. There are known
  TGL-H register offsets which alias to TGL-U\Y register offsets.

  @param[in] MrcData      - Pointer to MRC global data.
  @param[in] RegOffset    - The register offset to tanslate. This must be a TGL A0\B0
                            register offset. Set BIT31 to avoid translation.

  @retval UINT32 - The register offset to the register for the current SoC.
**/
UINT32
MrcCrOffsetProjAdj (
  IN MrcParameters *const  MrcData,
  IN UINT32                RegOffset
  )
{
  const MrcInput *Inputs;
  UINT32         Offset;
  UINT32         Channel;
  UINT32         CccRegOffset;

  Inputs        = &MrcData->Inputs;

  if ((RegOffset & MRC_BIT31) != 0) {
    // BIT 31 set indicates that no offset calculation is needed. Clear the bit and return the offset.
    Offset = RegOffset & ~(MRC_BIT31);
  } else if (Inputs->UlxUlt) {
    // No Translation is needed for TGL-U\Y
    Offset = RegOffset;
  } else {
    if (RegOffset >= DDRVTT0_CR_DDRCRVTTGENCONTROL_REG && RegOffset <= DDRVTT3_CR_DDRCRVTTCOMPOFFSET2_REG) {
      // 0x00002900 to 0x00002A8C
      Offset = RegOffset + (DDRVTT0_CR_DDRCRVTTGENCONTROL_P0_REG - DDRVTT0_CR_DDRCRVTTGENCONTROL_REG); // 4352
    } else if (RegOffset == DDRVREF_CR_DDRCRVREFADJUST2_REG) {
      // 0x00002B0C
      Offset = DDRVREF_CR_DDRCRVREFADJUST2_P0_REG;
    } else if (RegOffset >= CH0CCC_CR_DDRCRCACOMP_REG && RegOffset <= CH7CCC_CR_DCCLANESTATUS2_REG) {
      // 0x00003600 to 0x00003D74
      // CCC Channel Registers
      // First figure out the base register offset and channel instance from the input offset
      // Bits [10:8] provide the channel
      Channel = ((RegOffset - 0x00003600) & (MRC_BIT10 | MRC_BIT9 | MRC_BIT8)) >> 8;
      // Bits [7:0] provide the base register instance
      CccRegOffset = (RegOffset & 0xFF) | 0x00003600;

      // Check that the calculated base register address is within bounds
      // of known TGL U\Y CCC CH0 registers
      if (CccRegOffset >= CH0CCC_CR_DDRCRCACOMP_REG && CccRegOffset <= CH0CCC_CR_DCCLANESTATUS2_REG) {
        Offset = MrcCrOffsetProjAdjCccCh (MrcData, CccRegOffset, Channel);
      } else {
        Offset = RegOffset;
      }
    } else if ((RegOffset >= MC0_CH0_CR_TC_PRE_REG && RegOffset <= MC0_CH0_CR_WCK_CONFIG_REG) ||
               (RegOffset >= MC1_CH0_CR_TC_PRE_REG && RegOffset <= MC1_CH0_CR_WCK_CONFIG_REG)) {
      // 0x00004000 to 0x000040F8
      // 0x00014000 to 0x000140F8
      Offset = RegOffset + (MC0_CH0_CR_TC_PRE_P0_REG - MC0_CH0_CR_TC_PRE_REG); // 40960
    } else if ((RegOffset >= MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG && RegOffset <= MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_27_REG) ||
               (RegOffset >= MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG && RegOffset <= MC1_CH0_CR_GENERIC_MRS_FSM_CONTROL_27_REG)) {
      // 0x00004120 to 0x0000418C
      // 0x00014120 to 0x0001418C
      Offset = RegOffset + (MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG - MC0_CH0_CR_GENERIC_MRS_FSM_CONTROL_0_REG); // 42224
    } else if (RegOffset == MC0_CH0_CR_MCMNTS_RDDATA_CTL_REG || RegOffset == MC1_CH0_CR_MCMNTS_RDDATA_CTL_REG) {
      // 0x000041E8
      // 0x000141E8
      Offset = RegOffset + (MC0_CH0_CR_MCMNTS_RDDATA_CTL_P0_REG - MC0_CH0_CR_MCMNTS_RDDATA_CTL_REG); // 42008
    } else if ((RegOffset >= MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG && RegOffset <= MC0_CH0_CR_MCMNTS_SPARE_REG) ||
               (RegOffset >= MC1_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG && RegOffset <= MC1_CH0_CR_MCMNTS_SPARE_REG)) {
      // 0x00004204 to 0x000043FC
      // 0x00014204 to 0x000143FC
      if (RegOffset == MC0_CH0_CR_TC_MR2_SHADDOW_REG || RegOffset == MC1_CH0_CR_TC_MR2_SHADDOW_REG) {
        // These Regs are unique to TGL U\Y
        // 0x0000424C
        // 0x0001424C
        Offset = 0xFFFFFFFF;
      } else if (RegOffset == MC0_CH0_CR_LPDDR_PASR_REG || RegOffset == MC1_CH0_CR_LPDDR_PASR_REG) {
        // 0x00004290
        // 0x00014290
        Offset = RegOffset + (MC0_CH0_CR_LPDDR_PASR_P0_REG - MC0_CH0_CR_LPDDR_PASR_REG); // 41532
      } else {
        Offset = RegOffset + (MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_P0_REG - MC0_CH0_CR_REUT_CH_MISC_REFRESH_CTRL_REG); // 41472
      }
    } else if ((RegOffset >= MC0_CH1_CR_TC_PRE_REG && RegOffset <= MC0_CH1_CR_WCK_CONFIG_REG) ||
               (RegOffset >= MC0_BC_CR_TC_PRE_REG && RegOffset <= MC0_BC_CR_WCK_CONFIG_REG) ||
               (RegOffset >= MC1_CH1_CR_TC_PRE_REG && RegOffset <= MC1_CH1_CR_WCK_CONFIG_REG) ||
               (RegOffset >= MC1_BC_CR_TC_PRE_REG && RegOffset <= MC1_BC_CR_WCK_CONFIG_REG)) {
      // 0x00004400 to 0x000044F8
      // 0x00004C00 to 0x00004CF8
      // 0x00014400 to 0x000144F8
      // 0x00014C00 to 0x00014CF8
      Offset = RegOffset + (MC0_CH1_CR_TC_PRE_P0_REG - MC0_CH1_CR_TC_PRE_REG); // 41984
    } else if ((RegOffset >= MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_0_REG && RegOffset <= MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_27_REG) ||
               (RegOffset >= MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_0_REG && RegOffset <= MC0_BC_CR_GENERIC_MRS_FSM_CONTROL_27_REG) ||
               (RegOffset >= MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_0_REG && RegOffset <= MC1_CH1_CR_GENERIC_MRS_FSM_CONTROL_27_REG) ||
               (RegOffset >= MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_0_REG && RegOffset <= MC1_BC_CR_GENERIC_MRS_FSM_CONTROL_27_REG)) {
      // 0x00004520 to 0x0000458C
      // 0x00004D20 to 0x00004D8C
      // 0x00014520 to 0x0001458C
      // 0x00014D20 to 0x00014D8C
      Offset = RegOffset + (MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_0_P0_REG - MC0_CH1_CR_GENERIC_MRS_FSM_CONTROL_0_REG); // 43248
    } else if (RegOffset == MC0_CH1_CR_MCMNTS_RDDATA_CTL_REG || RegOffset == MC0_BC_CR_MCMNTS_RDDATA_CTL_REG ||
               RegOffset == MC1_CH1_CR_MCMNTS_RDDATA_CTL_REG || RegOffset == MC1_BC_CR_MCMNTS_RDDATA_CTL_REG) {
      // 0x000045E8
      // 0x00004DE8
      // 0x000145E8
      // 0x00014DE8
      Offset = RegOffset + (MC0_CH1_CR_MCMNTS_RDDATA_CTL_P0_REG - MC0_CH1_CR_MCMNTS_RDDATA_CTL_REG); // 43032
    } else if ((RegOffset >= MC0_CH1_CR_REUT_CH_MISC_REFRESH_CTRL_REG && RegOffset <= MC0_CH1_CR_MCMNTS_SPARE_REG) ||
               (RegOffset >= MC0_BC_CR_REUT_CH_MISC_REFRESH_CTRL_REG && RegOffset <= MC0_BC_CR_MCMNTS_SPARE_REG) ||
               (RegOffset >= MC1_CH1_CR_REUT_CH_MISC_REFRESH_CTRL_REG && RegOffset <= MC1_CH1_CR_MCMNTS_SPARE_REG) ||
               (RegOffset >= MC1_BC_CR_REUT_CH_MISC_REFRESH_CTRL_REG && RegOffset <= MC1_BC_CR_MCMNTS_SPARE_REG)) {
      // 0x00004604 to 0x000047FC
      // 0x00004E04 to 0x00004FFC
      // 0x00014604 to 0x000147FC
      // 0x00014E04 to 0x00014FFC
      if (RegOffset == MC0_CH1_CR_TC_MR2_SHADDOW_REG || RegOffset == MC0_BC_CR_TC_MR2_SHADDOW_REG ||
          RegOffset == MC1_CH1_CR_TC_MR2_SHADDOW_REG || RegOffset == MC1_BC_CR_TC_MR2_SHADDOW_REG) {
        // These register are unique to TGL U\Y
        // 0x0000464C
        // 0x00004E4C
        // 0x0001464C
        // 0x00014E4C
        Offset = 0xFFFFFFFF;
      } else if (RegOffset == MC0_CH1_CR_LPDDR_PASR_REG || RegOffset == MC0_BC_CR_LPDDR_PASR_REG ||
                 RegOffset == MC1_CH1_CR_LPDDR_PASR_REG || RegOffset == MC1_BC_CR_LPDDR_PASR_REG) {
        // 0x00004690
        // 0x00004E90
        // 0x00014690
        // 0x00014E90
        Offset = RegOffset + (MC0_CH1_CR_LPDDR_PASR_P0_REG - MC0_CH1_CR_LPDDR_PASR_REG); // 42556
      } else {
        Offset = RegOffset + (MC0_CH1_CR_REUT_CH_MISC_REFRESH_CTRL_P0_REG - MC0_CH1_CR_REUT_CH_MISC_REFRESH_CTRL_REG); // 42496
      }
    } else if ((RegOffset >= MC0_MAD_INTER_CHANNEL_REG && RegOffset <= MC0_PARITY_CONTROL_REG) ||
               (RegOffset >= MC1_MAD_INTER_CHANNEL_REG && RegOffset <= MC1_PARITY_CONTROL_REG)) {
      // 0x00005000 to 0x000051B4
      // 0x00015000 to 0x000151B4
      if (RegOffset == MC0_PWM_GLB_DRV_OFF_COUNT_REG || RegOffset == MC1_PWM_GLB_DRV_OFF_COUNT_REG) {
        // 0x000050C0
        // 0x000150C0
        Offset = RegOffset + (MC0_PWM_GLB_DRV_OFF_COUNT_P0_REG - MC0_PWM_GLB_DRV_OFF_COUNT_REG); // 35000
      } else {
        Offset = RegOffset + (MC0_MAD_INTER_CHANNEL_P0_REG - MC0_MAD_INTER_CHANNEL_REG); // 34816
      }
    } else if ((RegOffset >= MC0_DDRPL_CFG_DTF_REG && RegOffset <= MC0_DDRPL_VISA_CFG_DTF_REG) ||
               (RegOffset >= MC1_DDRPL_CFG_DTF_REG && RegOffset <= MC1_DDRPL_VISA_CFG_DTF_REG)) {
      // 0x00005200 to 0x00005210
      // 0x00015200 to 0x00015210
      Offset = RegOffset + (MC0_DDRPL_CFG_DTF_P0_REG - MC0_DDRPL_CFG_DTF_REG); // 36096
    } else if (RegOffset >= CCC_CR_DDRCRCACOMP_REG && RegOffset <= CCC_CR_DCCLANESTATUS2_REG) {
      // 0x00008A00 to 0x00008A74
      Offset = RegOffset - (CCC_CR_DDRCRCACOMP_REG - CCC_CR_DDRCRCACOMP_P0_REG); // 512
    } else {
      // Check if the input register offset is unique to TGL B0
      if (RegOffset == DDRVREF_CR_DDRCRVREFADJUST1_REG) {
        // 0x00002B08
        Offset = 0xFFFFFFFF;
      } else if ((RegOffset >= MC0_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG && RegOffset <= MC0_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG) ||
                 (RegOffset >= MC0_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG && RegOffset <= MC0_CH1_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG) ||
                 (RegOffset >= MC0_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG && RegOffset <= MC0_BC_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG) ||
                 (RegOffset >= MC1_CH0_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG && RegOffset <= MC1_CH0_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG) ||
                 (RegOffset >= MC1_CH1_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG && RegOffset <= MC1_CH1_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG) ||
                 (RegOffset >= MC1_BC_CR_GENERIC_MRS_FSM_PER_RANK_VALUES_0_REG && RegOffset <= MC1_BC_CR_GENERIC_MRS_FSM_TIMING_STORAGE_REG)) {
        // 0x00004190 to 0x000041E0
        // 0x00004590 to 0x000045E0
        // 0x00004D90 to 0x00004DE0
        // 0x00014190 to 0x000141E0
        // 0x00014590 to 0x000145E0
        // 0x00014D90 to 0x00014DE0
        Offset = 0xFFFFFFFF;
      } else {
        // If none of the conditions are met, return the input register offset unchanged
        Offset = RegOffset;
      }
    }
  } // DtHalo

  return Offset;
}
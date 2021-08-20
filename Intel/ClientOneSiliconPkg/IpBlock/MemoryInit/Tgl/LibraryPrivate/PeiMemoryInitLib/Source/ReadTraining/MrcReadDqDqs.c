/** @file
  Once DQS is aligned against the clock in the receive enable training flow,
  the second stage of the read training is the DQ/DQS training, aligning each
  strobe with it's byte of data. The DQ/DQS training is once again using the
  DDR read synchronization mode, in this mode a predetermined pattern is read
  out of the DDR. The following algorithm is used to align the data sampling
  to the best sampling point.

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
//
// Include files
//
#include "MrcReadDqDqs.h"
#include "MrcCrosser.h"
#include "MrcCpgcApi.h"
#include "Cpgc20TestCtl.h"
#include "MrcCommon.h"

// For MPR pattern "00000000"
MRC_BG_BANK_PAIR Ddr4RdMprBankL2pBank3[2] = { {0, 3}, {1, 3} };

/**
  Perform Read MPR Training using normal reads.
  Centers read DQ-DQS with MPR pattern.

  @param[in, out] MrcData  - Pointer to MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcReadMprTrainingNormal (
  IN OUT MrcParameters *const MrcData,
  IN     BOOLEAN              Print
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcIntOutput        *IntOutputs;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  MrcStatus           MprStatus;
  UINT32              CpgcChickenPrevData[MAX_CONTROLLER];
  UINT32              Offset;
  UINT8               MaxChannel;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               Byte;
  UINT8               RankMask;  // RankBitMask for both channels
  UINT8               LoopCount;
  UINT8               McChBitMask;
  UINT64              ErrStatus;
  UINT64              ChunkStatus;
  UINT16              *Margin;
  UINT16              ChunkResult[MAX_CONTROLLER][MAX_CHANNEL];
  INT8                DqsDelay;
  INT16               CurrentPassingStart[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16               CurrentPassingEnd[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16               LargestPassingStart[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16               LargestPassingEnd[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16               FinalDqs[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16               cWidth;
  INT16               lWidth;
  INT16               Center;
  INT16               Left;
  INT16               Right;
  INT64               GetSetDis;
  INT64               GetSetEn;
  INT64               GetSetVal;
  BOOLEAN             Pass;
  BOOLEAN             Lpddr4;
  BOOLEAN             Lpddr5;
  BOOLEAN             Lpddr;
  BOOLEAN             Ddr4;
  UINT8               RDRDsgPrevData;
  UINT8               RDRDdgPrevData;
  UINT8               MrDqCalPatA;
  UINT8               MrDqCalPatB;
  UINT8               MrDqCalLow;
  UINT8               MrDqCalHigh;
  DDR4_MODE_REGISTER_3_STRUCT   Ddr4Mr3;
  MRC_BG_BANK_PAIR              BankMapping[MAX_CONTROLLER][MAX_CHANNEL][MAX_BANKS];
  MC0_CR_CPGC2_V_CHICKEN_STRUCT CpgcChickenStruct;
#ifdef MRC_DEBUG_PRINT
  UINT8               BitGroupErr[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
#endif // MRC_DEBUG_PRINT

  Inputs      = &MrcData->Inputs;
  MrcCall     = Inputs->Call.Func;
  Outputs     = &MrcData->Outputs;
  IntOutputs  = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Debug       = Print ? &Outputs->Debug : NULL;
  Status      = mrcSuccess;
  MprStatus   = mrcSuccess;
  Lpddr4      = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5      = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5);
  Ddr4        = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr       = Outputs->Lpddr;
  RankMask    = Outputs->ValidRankMask;
  GetSetDis   = 0;
  GetSetEn    = 1;
  MaxChannel  = Outputs->MaxChannels;
  RDRDsgPrevData = 0;
  RDRDdgPrevData = 0;

  LoopCount = 10;

  if (Lpddr) {
    // Set GsmMctRDRDsg and GsmMctRDRDdg to 8 (BL 16)
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        Offset = OFFSET_CALC_CH (MC0_CR_CPGC2_V_CHICKEN_REG, MC1_CR_CPGC2_V_CHICKEN_REG, Controller);
        CpgcChickenPrevData[Controller] = MrcReadCR (MrcData, Offset);
        CpgcChickenStruct.Data = CpgcChickenPrevData[Controller];
        CpgcChickenStruct.Bits.MPR_TEST_REQ_DBLR = 1;
        MrcWriteCR (MrcData, Offset, CpgcChickenStruct.Data);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Setting MPR_TEST_REQ_DBLR.\n");
        GetSetVal = 1;
        MrcGetSetMc (MrcData, Controller, GsmMccHalfCachelineMode, WriteToCache | PrintValue, &GetSetVal);
        Channel = Outputs->Controller[Controller].FirstPopCh;
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDsg, ReadFromCache | PrintValue, &GetSetVal);
        RDRDsgPrevData = (UINT8) GetSetVal;
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdg, ReadFromCache | PrintValue, &GetSetVal);
        RDRDdgPrevData = (UINT8) GetSetVal;
      }
    }
    GetSetVal = 8;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
          continue;
        }
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDsg, WriteToCache | PrintValue, &GetSetVal);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdg, WriteToCache | PrintValue, &GetSetVal);
        MrcFlushRegisterCachedData (MrcData);
        // Must update the XARB bubble injector when TAT values change
        SetTcBubbleInjector (MrcData, Controller, Channel);
      }
    }
  }

  if (Lpddr4) {
    MrDqCalPatA = 32;
    MrDqCalPatB = 40;
    MrDqCalLow  = 15;
    MrDqCalHigh = 20;
  } else if (Lpddr5) {
    MrDqCalPatA = 33;
    MrDqCalPatB = 34;
    MrDqCalLow  = 31;
    MrDqCalHigh = 32;
  } else {
    MrDqCalPatA = 0;
    MrDqCalPatB = 0;
    MrDqCalLow  = 0;
    MrDqCalHigh = 0;
  }

  // Setup REUT Engine
  SetupIOTestCpgcMPR (MrcData, Outputs->McChBitMask, LoopCount, NSOE);
  IntOutputs->SkipZq = TRUE;
  // Set DQS Delay to 32
  GetSetVal = 32;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        // Set DQS Delay to 32
        // Update RxDqsP & RxDqsN - leave other parameter the same; can we update in the next loop or do it per channel
        MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsNDelay, WriteToCache, &GetSetVal);
        MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsPDelay, WriteToCache, &GetSetVal);
        if (Ddr4) {
          // Save Bank Mapping
          MrcGetSetBankSequence (MrcData, Controller, Channel, &BankMapping[Controller][Channel][0], 2, MRC_GET);
          MrcGetSetBankSequence (MrcData, Controller, Channel, Ddr4RdMprBankL2p, 2, MRC_SET);
        }
      }
    } // Channel
  } // Controller
  MrcFlushRegisterCachedData (MrcData);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!((MRC_BIT0 << Rank) & RankMask)) {
      continue; // Skip if both channels empty
    }
    McChBitMask = 0;
    // Program MR3 and Mask RAS/WE to prevent scheduler for issuing non-Read commands
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        McChBitMask |= SelectReutRanks (MrcData, Controller, Channel, 1 << Rank, FALSE, 0); //Save particular mask to use with runIOTest later
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

        // Enter MPR mode on DRAM for DDR4
        if (Ddr4) {
          Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
          Ddr4Mr3.Bits.MprOperation = 1;
          Status = MrcWriteMRS (MrcData, Controller, Channel, (1 << Rank), mrMR3, Ddr4Mr3.Data);
        } else if (Lpddr) {
          MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalPatA, 0x55, TRUE); // DQ Calibration Pattern "A"
          MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalPatB, 0x55, TRUE); // DQ Calibration Pattern "B"
          MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalLow, 0x00, TRUE); // Lower Byte Invert for DQ Calibration
          MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalHigh, 0x00, TRUE); // Upper Byte Invert for DQ Calibration
        }
      } // for Channel
    } // for Controller
    MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccMprTrainDdrOn, WriteNoCache, &GetSetEn);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--- CPGC-based RDMPR ---\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank = %u\n", Rank);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\t0                1\nByte\t");
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE, (
      Outputs->SdramCount == (MAX_SDRAM_IN_DIMM)
      ) ? "0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8" : "0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7"
      );

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDqsDelay");
    for (DqsDelay = RMPR_DQS_START; DqsDelay < RMPR_DQS_STOP; DqsDelay += RMPR_DQS_STEP) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5d\t", DqsDelay);
      // Program DQS Delays and download the Reg File for the current rank.
      Status = ChangeMargin (MrcData, RdT, DqsDelay, 0, 1, 0, 0, 0, 0, 0, 0, 0);

      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              (Channel != 0) ? "" : ((Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "                  " : "                ")
              );
          }
        }
      }

      if (Ddr4) {
        // Clean the Rx FIFO using another MPR sequence - Bank 3 (all zeroes)
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MaxChannel; Channel++) {
            if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
              MrcGetSetBankSequence (MrcData, Controller, Channel, Ddr4RdMprBankL2pBank3, 2, MRC_SET);
            }
          } // for Channel
        } // for Controller
      }
      if (Lpddr) {
        // Clean the Rx FIFO using another MPR sequence - all zeroes
        MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccMprTrainDdrOn, WriteNoCache, &GetSetDis);
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MaxChannel; Channel++) {
            if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
              continue;
            }
            MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalPatA, 0, TRUE); // DQ Calibration Pattern "A"
            MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalPatB, 0, TRUE); // DQ Calibration Pattern "B"
          } // for Channel
        } // for Controller
        MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccMprTrainDdrOn, WriteNoCache, &GetSetEn);
      }
      SetupIOTestCpgcMPR (MrcData, McChBitMask, 4, NSOE);
      RunIOTest (MrcData, McChBitMask, Outputs->DQPat, 1, 0);

      // Go back to the original MPR pattern
      if (Ddr4) {
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MaxChannel; Channel++) {
            if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
              MrcGetSetBankSequence (MrcData, Controller, Channel, Ddr4RdMprBankL2p, 2, MRC_SET);
            }
          } // for Channel
        } // for Controller
      }
      if (Lpddr) {
        MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccMprTrainDdrOn, WriteNoCache, &GetSetDis);
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MaxChannel; Channel++) {
            if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
              continue;
            }
            MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalPatA, 0x55, TRUE); // DQ Calibration Pattern "A"
            MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalPatB, 0x55, TRUE); // DQ Calibration Pattern "B"
          } // for Channel
        } // for Controller
        MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccMprTrainDdrOn, WriteNoCache, &GetSetEn);
      }

      SetupIOTestCpgcMPR (MrcData, McChBitMask, LoopCount, NSOE);
      RunIOTest (MrcData, McChBitMask, Outputs->DQPat, 1, 0);

      // Update results for all ch/bytes
#ifdef MRC_DEBUG_PRINT
      MrcCall->MrcSetMem ((UINT8 *) BitGroupErr, sizeof (BitGroupErr), 0);
#endif // MRC_DEBUG_PRINT
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          ErrStatus = 0;
          ChunkStatus = 0;
          ChunkResult[Controller][Channel] = 0;
          // Read out per byte error results and check for any byte error
          MrcGetMiscErrStatus (MrcData, Controller, Channel, ByteGroupErrStatus, &ErrStatus);
          // Read per chunk error status
          MrcGetMiscErrStatus (MrcData, Controller, Channel, ChunkErrStatus, &ChunkStatus);
          ChunkResult[Controller][Channel] = (UINT16) ChunkStatus;
#ifdef MRC_DEBUG_PRINT
          MrcGetBitGroupErrStatus (MrcData, Controller, Channel, BitGroupErr[Controller][Channel]);
#endif // MRC_DEBUG_PRINT

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
              continue;
            }
            Pass = ((((UINT32) ErrStatus) & (1 << Byte)) == 0);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Pass ? ". " : "# ");

            if (DqsDelay == RMPR_DQS_START) {
              if (Pass) {
                CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = DqsDelay;
                LargestPassingStart[Controller][Channel][Byte] = LargestPassingEnd[Controller][Channel][Byte] = DqsDelay;
              } else {
                CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = -33;
                LargestPassingStart[Controller][Channel][Byte] = LargestPassingEnd[Controller][Channel][Byte] = -33;
              }
            } else {
              if (Pass) {
                if (CurrentPassingEnd[Controller][Channel][Byte] == (DqsDelay - RMPR_DQS_STEP)) {
                  CurrentPassingEnd[Controller][Channel][Byte] = DqsDelay;
                } else {
                  CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = DqsDelay;
                }
                // Update Largest variables

                cWidth  = CurrentPassingEnd[Controller][Channel][Byte] - CurrentPassingStart[Controller][Channel][Byte];
                lWidth  = LargestPassingEnd[Controller][Channel][Byte] - LargestPassingStart[Controller][Channel][Byte];
                if (cWidth > lWidth) {
                  LargestPassingStart[Controller][Channel][Byte]  = CurrentPassingStart[Controller][Channel][Byte];
                  LargestPassingEnd[Controller][Channel][Byte]    = CurrentPassingEnd[Controller][Channel][Byte];
                }
              }
            }
          } // for Byte
        } // for Channel
      } // for Controller

#ifdef MRC_DEBUG_PRINT
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          ErrStatus = 0;
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            ErrStatus |= MrcCall->MrcLeftShift64 (BitGroupErr[Controller][Channel][Byte], Byte * 8);
          }
          if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "0x%016llX 0x%04X ",
              ErrStatus,
              ChunkResult[Controller][Channel]
              );
          }
        }
      }
#endif  // MRC_DEBUG_PRINT

      Status = IoReset (MrcData);
    } // for DqsDelay

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    // Clean Up registers.
    // MPR_TRAIN_DDR_ON bit will force a special command so clear it before MRS command
    MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccMprTrainDdrOn, WriteNoCache, &GetSetDis);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];


          // Exit MPR mode on DRAM for DDR4
          if (Ddr4) {
            Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
            Status = MrcWriteMRS (MrcData, Controller, Channel, (MRC_BIT0 << Rank), mrMR3, Ddr4Mr3.Data);
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MC%u.C%u.R%u: \tLeft\tRight\tWidth\tCenter\tRxDqsPN\n", Controller, Channel, Rank);
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              continue;
            }
            Left  = LargestPassingStart[Controller][Channel][Byte];
            Right = LargestPassingEnd[Controller][Channel][Byte];
            lWidth = Right - Left;
            Center = Left + (lWidth / 2);

            // Error Handler if eye not found for all bytes
            if (lWidth == 0) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_ERROR,
                "\nERROR!! NO EYE found for Mc: %u Channel: %u Rank: %u Byte: %u \n",
                Controller,
                Channel,
                Rank,
                Byte
                );
              // Mark it as zero margin in MarginResult
              Left   = 0;
              Right  = 0;
              Center = 0;
              MprStatus = mrcReadMPRErr;
            } else if (lWidth <= RMPR_MIN_WIDTH) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_WARNING,
                "WARNING!! lWidth <= %u for Mc: %u Channel: %u Rank: %u Byte: %u\n",
                RMPR_MIN_WIDTH,
                Controller,
                Channel,
                Rank,
                Byte
                );
            }
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RxDqsPDelay, ReadFromCache, &GetSetVal);
            FinalDqs[Controller][Channel][Rank][Byte] = Center + (INT16) GetSetVal;
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  B%u: \t%d\t%d\t%d\t%d\t%d\n",
              Byte,
              Left,
              Right,
              lWidth,
              Center,
              FinalDqs[Controller][Channel][Rank][Byte]
              );
            // Update the MarginResult struct for future tests
            Margin    = &Outputs->MarginResult[LastRxT][Rank][Controller][Channel][Byte][0];
            Margin[0] = ABS (10 * (Left  - Center));
            Margin[1] = ABS (10 * (Right - Center));
          } // for Byte
        }
      } // for Channel
    } // for Controller
  } // for Rank

  // Now program the DQS center values on populated ranks.
  // Need to do it after all ranks are trained, because we need to keep the same DQS value on all ranks
  // during the training.
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              continue;
            }
            GetSetVal = (INT64) FinalDqs[Controller][Channel][Rank][Byte];
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RxDqsPDelay, WriteToCache, &GetSetVal);
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RxDqsNDelay, WriteToCache, &GetSetVal);
          }
        }
      }
    }
  }
  MrcFlushRegisterCachedData (MrcData);

  // Clean up after Test.
  if (Ddr4) {
    // Restore the bank mapping
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MrcChannelExist (MrcData, Controller, Channel)) {
          continue;
        }
        MrcGetSetBankSequence (MrcData, Controller, Channel, &BankMapping[Controller][Channel][0], 2, MRC_SET);
      } // for Channel
    } // for Controller
  } else if (Lpddr) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        Offset = OFFSET_CALC_CH (MC0_CR_CPGC2_V_CHICKEN_REG, MC1_CR_CPGC2_V_CHICKEN_REG, Controller);
        MrcWriteCR (MrcData, Offset, CpgcChickenPrevData[Controller]);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Revert MPR_TEST_REQ_DBLR.\n");
        GetSetVal = 0;
        MrcGetSetMc (MrcData, Controller, GsmMccHalfCachelineMode, WriteToCache | PrintValue, &GetSetVal);
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
            continue;
          }
          GetSetVal = RDRDsgPrevData;
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDsg, WriteToCache | PrintValue, &GetSetVal);
          GetSetVal = RDRDdgPrevData;
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdg, WriteToCache | PrintValue, &GetSetVal);
          MrcFlushRegisterCachedData (MrcData);
          // Must update the XARB bubble injector when TAT values change
          SetTcBubbleInjector (MrcData, Controller, Channel);
        }
      }
    }
  }
  IntOutputs->SkipZq = FALSE;
  Status  = ChangeMargin (MrcData, RdT, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
  Status  = IoReset (MrcData);

  if ((MprStatus != mrcSuccess) && (Inputs->ExitOnFailure == 1)) {
    Status = MprStatus;
  }
  return Status;
}

/**
  Perform Read MPR Training.
  Center read DQ-DQS with MPR pattern.

  @param[in, out] MrcData   - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcReadMprTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  return MrcReadMprTrainingNormal (MrcData, TRUE);  // CPGC-based
}

/**
  Perform Read MPR Training.
  Center read DQ-DQS with MPR pattern.
  This is the HW method of the Read MPR algorithm.

  @param[in, out] MrcData   - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
ReadMprTraining (
  IN OUT MrcParameters *const MrcData,
  IN     BOOLEAN              Print
  )
{
  const MrcInput   *Inputs;
  MrcDebug         *Debug;
  MrcOutput        *Outputs;
  MrcChannelOut    *ChannelOut;
  MrcStatus        Status;
  MrcStatus        MprStatus;
  MrcDdrType       DdrType;
  UINT8            MaxChannel;
  UINT8            Controller;
  UINT8            Channel;
  UINT8            IpChannel;
  UINT8            Rank;
  UINT8            Byte;
  UINT8            McChBitMask;
  UINT8            RankMask;  // RankBitMask for both channels
  UINT8            LoopCount;
  UINT8            TestDoneStatus;
  INT8             DqsDelay;
  INT16            CurrentPassingStart[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16            CurrentPassingEnd[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16            LargestPassingStart[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16            LargestPassingEnd[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16            FinalDqs[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16            cWidth;
  INT16            lWidth;
  INT16            Center;
  INT16            Left;
  INT16            Right;
  INT64            GroupOffset;
  INT64            GetSetDis;
  INT64            GetSetEn;
  INT64            GetSetVal;
  UINT8            RDRDsgPrevData;
  UINT8            RDRDdgPrevData;
  INT64            DataTrainFeedbackField;
  BOOLEAN          Pass;
  BOOLEAN          Lpddr;
  BOOLEAN          Lpddr4;
  BOOLEAN          Lpddr5;
  BOOLEAN          Ddr4;
  UINT16          *Margin;
  UINT32           Offset;
  UINT8            MrDqCalPatA;
  UINT8            MrDqCalPatB;
  UINT8            MrDqCalLow;
  UINT8            MrDqCalHigh;
  INT64                              GetSetValue;
  MRC_BG_BANK_PAIR                   BankMapping[MAX_CONTROLLER][MAX_CHANNEL][MAX_BANKS];
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT    CpgcSeqCtl;
  MC0_REQ0_CR_CPGC_SEQ_STATUS_STRUCT CpgcSeqStatus;
  DDR4_MODE_REGISTER_3_STRUCT        Ddr4Mr3;
  UINT32                             CpgcChickenPrevData[MAX_CONTROLLER];
  MC0_CR_CPGC2_V_CHICKEN_STRUCT      CpgcChickenStruct;

  Inputs         = &MrcData->Inputs;
  Outputs        = &MrcData->Outputs;
  Debug          = Print ? &Outputs->Debug : NULL;
  Status         = mrcSuccess;
  MprStatus      = mrcSuccess;
  DdrType        = Outputs->DdrType;
  Lpddr4         = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5         = (DdrType == MRC_DDR_TYPE_LPDDR5);
  Lpddr          = Outputs->Lpddr;
  Ddr4           = (DdrType == MRC_DDR_TYPE_DDR4);
  GetSetDis      = 0;
  GetSetEn       = 1;
  MaxChannel     = Outputs->MaxChannels;
  RDRDsgPrevData = 0;
  RDRDdgPrevData = 0;

  LoopCount = 10;

  if (Lpddr) {
    // Set GsmMctRDRDsg and GsmMctRDRDdg to 8 (BL 16)
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        Offset = OFFSET_CALC_CH (MC0_CR_CPGC2_V_CHICKEN_REG, MC1_CR_CPGC2_V_CHICKEN_REG, Controller);
        CpgcChickenPrevData[Controller] = MrcReadCR (MrcData, Offset);
        CpgcChickenStruct.Data = CpgcChickenPrevData[Controller];
        CpgcChickenStruct.Bits.MPR_TEST_REQ_DBLR = 1;
        MrcWriteCR (MrcData, Offset, CpgcChickenStruct.Data);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Setting MPR_TEST_REQ_DBLR.\n");
        GetSetVal = 1;
        MrcGetSetMc (MrcData, Controller, GsmMccHalfCachelineMode, WriteToCache | PrintValue, &GetSetVal);
        Channel = Outputs->Controller[Controller].FirstPopCh;
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDsg, ReadFromCache | PrintValue, &GetSetVal);
        RDRDsgPrevData = (UINT8) GetSetVal;
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdg, ReadFromCache | PrintValue, &GetSetVal);
        RDRDdgPrevData = (UINT8) GetSetVal;
      }
    }
    GetSetVal = 8;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
          continue;
        }
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDsg, WriteToCache | PrintValue, &GetSetVal);
        MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdg, WriteToCache | PrintValue, &GetSetVal);
        MrcFlushRegisterCachedData (MrcData);
        // Must update the XARB bubble injector when TAT values change
        SetTcBubbleInjector (MrcData, Controller, Channel);
      }
    }
  }

  if (Lpddr4) {
    MrDqCalPatA = 32;
    MrDqCalPatB = 40;
    MrDqCalLow = 15;
    MrDqCalHigh = 20;
  } else if (Lpddr5) {
    MrDqCalPatA = 33;
    MrDqCalPatB = 34;
    MrDqCalLow = 31;
    MrDqCalHigh = 32;
  } else {
    MrDqCalPatA = 0;
    MrDqCalPatB = 0;
    MrDqCalLow = 0;
    MrDqCalHigh = 0;
  }

  // Use basic addressing mode (open a page on a rank and keep writing/reading to it)
  // Rotate through all 8 logical ranks
  // LFSR and LMN disabled.
  McChBitMask = Outputs->McChBitMask;
  RankMask  = Outputs->ValidRankMask;

  GroupOffset = 32; // RxDqs PI Center
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        // Set DQS Delay to 32
        // Update RxDqsP & RxDqsN - leave other parameter the same; can we update in the next loop or do it per channel
        MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsNDelay, WriteToCache, &GroupOffset);
        MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsPDelay, WriteToCache, &GroupOffset);
        if (Ddr4) {
          // Save Bank Mapping
          MrcGetSetBankSequence (MrcData, Controller, Channel, &BankMapping[Controller][Channel][0], 2, MRC_GET);
          MrcGetSetBankSequence (MrcData, Controller, Channel, Ddr4RdMprBankL2p, 2, MRC_SET);
        }
      }
    } // Channel
  } // Controller
  MrcFlushRegisterCachedData (MrcData);

  //
  // Setup REUT Engine
  //
  SetupIOTestMPR (MrcData, McChBitMask, LoopCount, NSOE, 0, 0);

  // Enable Rank Mux Override
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteNoCache, &GetSetEn);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!((MRC_BIT0 << Rank) & RankMask)) {
      continue; // Skip for empty channels
    }

    // Update Rank Mux Override for the rank under test
    GetSetVal = Rank;
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideVal, WriteNoCache, &GetSetVal);
    //
    // Program MR3 and Mask RAS/WE to prevent scheduler for issuing non-Read commands
    //
    McChBitMask = 0;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        McChBitMask |= SelectReutRanks (MrcData, Controller, Channel, 1 << Rank, FALSE, 0);
        if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
          continue;
        }
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        //
        // Enter MPR mode on DRAM for DDR3/4
        //
        if (Ddr4) {
          Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
          Ddr4Mr3.Bits.MprOperation = 1;
          Status = MrcWriteMRS (MrcData, Controller, Channel, (1 << Rank), mrMR3, Ddr4Mr3.Data);
        } else if (Lpddr) {
          // Pattern 0xAA implemented due to LSB bit being sent first -- only supporting 1010 pattern.
          MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalPatA, 0xAA, TRUE); // DQ Calibration Pattern "A"
          MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalPatB, 0xAA, TRUE); // DQ Calibration Pattern "B"
          MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalLow, 0x00, TRUE); // Lower Byte Invert for DQ Calibration
          MrcIssueMrw (MrcData, Controller, Channel, Rank, MrDqCalHigh, 0x00, TRUE); // Upper Byte Invert for DQ Calibration
        }
      } // for Channel
    } // for Controller
    MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccMprTrainDdrOn, WriteNoCache, &GetSetEn);

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank = %u\n", Rank);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\t0                1\nByte\t");
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE, (
      Outputs->SdramCount == (MAX_SDRAM_IN_DIMM)
      ) ? "0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8" : "0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7"
      );

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDqsDelay");
    for (DqsDelay = RMPR_DQS_START; DqsDelay < RMPR_DQS_STOP; DqsDelay += RMPR_DQS_STEP) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5d\t", DqsDelay);

      //
      // Program DQS Delays and download the Reg File for the current rank.
      //
      Status = ChangeMargin (MrcData, RdT, DqsDelay, 0, 1, 0, 0, 0, 0, 0, 0, 0);

      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              (Channel != 0) ? "" : ((Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "                  " : "                ")
              );
          } else {
            // Force on SenseAmp
            // Enable RX Training mode. Turn on the ODT.
            MrcGetSetChStrb (MrcData, Controller, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn, WriteToCache, &GetSetEn);
            MrcGetSetChStrb (MrcData, Controller, Channel, MAX_SDRAM_IN_DIMM, GsmIocReadDqDqsMode, WriteNoCache, &GetSetEn);
            MrcGetSetChStrb (MrcData, Controller, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn, WriteToCache, &GetSetEn);
            MrcFlushRegisterCachedData (MrcData);
          }
        } // for Channel
      } // for Controller

      Status = IoReset (MrcData);

      // Start CPGC and run for 1uS
      CpgcSeqCtl.Data = 0;
      CpgcSeqCtl.Bits.START_TEST = 1;
      Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcSeqCtl);

      // Wait for test to start clearing errors.
      MrcWait (MrcData, START_TEST_DELAY);

      // Clear Results for Prior Test and wait to obtain results
      Status = IoReset (MrcData);
      MrcWait (MrcData, IO_RESET_DELAY);

      // Stop CPGC
      CpgcSeqCtl.Data = 0;
      CpgcSeqCtl.Bits.STOP_TEST = 1;
      Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcSeqCtl);

      // Wait till CPGC test is done on all participating channels
      do {
        TestDoneStatus = 0;
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MaxChannel; Channel++) {
            if ((MrcRankExist (MrcData, Controller, Channel, Rank)) && (!(IS_MC_SUB_CH (Lpddr, Channel)))) {
              IpChannel = LP_IP_CH (Lpddr, Channel);
              ChannelOut = &Outputs->Controller[Controller].Channel[IpChannel];
              Offset = OFFSET_CALC_MC_CH (MC0_REQ0_CR_CPGC_SEQ_STATUS_REG, MC1_REQ0_CR_CPGC_SEQ_STATUS_REG, Controller, MC0_REQ1_CR_CPGC_SEQ_STATUS_REG, IpChannel);
              CpgcSeqStatus.Data = MrcReadCR (MrcData, Offset);
              if (CpgcSeqStatus.Bits.TEST_DONE) {
                TestDoneStatus |= ChannelOut->CpgcChAssign << (Controller * MaxChannel);
              }
            }
          }
        }
      } while ((TestDoneStatus & McChBitMask) != McChBitMask);


      // Update results for all ch/bytes
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
              continue;
            }
            MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataTrainFeedback, ReadUncached, &DataTrainFeedbackField);
            Pass = (DataTrainFeedbackField == 1);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Pass ? ". " : "# ");

            if (DqsDelay == RMPR_DQS_START) {
              if (Pass) {
                CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = DqsDelay;
                LargestPassingStart[Controller][Channel][Byte] = LargestPassingEnd[Controller][Channel][Byte] = DqsDelay;
              } else {
                CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = -33;
                LargestPassingStart[Controller][Channel][Byte] = LargestPassingEnd[Controller][Channel][Byte] = -33;
              }
            } else {
              if (Pass) {
                if (CurrentPassingEnd[Controller][Channel][Byte] == (DqsDelay - RMPR_DQS_STEP)) {
                  CurrentPassingEnd[Controller][Channel][Byte] = DqsDelay;
                } else {
                  CurrentPassingStart[Controller][Channel][Byte] = CurrentPassingEnd[Controller][Channel][Byte] = DqsDelay;
                }
                //
                // Update Largest variables
                //
                cWidth  = CurrentPassingEnd[Controller][Channel][Byte] - CurrentPassingStart[Controller][Channel][Byte];
                lWidth  = LargestPassingEnd[Controller][Channel][Byte] - LargestPassingStart[Controller][Channel][Byte];
                if (cWidth > lWidth) {
                  LargestPassingStart[Controller][Channel][Byte]  = CurrentPassingStart[Controller][Channel][Byte];
                  LargestPassingEnd[Controller][Channel][Byte]    = CurrentPassingEnd[Controller][Channel][Byte];
                }
              }
            } // if (DqsDelay == RMPR_DQS_START)
          } // for Byte
        } // for Channel
      } // for Controller

      // Clear RxAmp and RxTrainingMode. Restore DataControl0
      MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn, WriteToCache, &GetSetDis);
      MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocReadDqDqsMode, WriteNoCache, &GetSetDis);
      MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocForceRxAmpOn, WriteToCache, &GetSetDis);
      MrcFlushRegisterCachedData (MrcData);
      Status = IoReset (MrcData);
    } // for DqsDelay

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    // Clean Up registers.
    // MPR_TRAIN_DDR_ON bit will force a special command so clear it before MRS command
    MrcGetSetMcCh (MrcData, MAX_CONTROLLER, MAX_CHANNEL, GsmMccMprTrainDdrOn, WriteNoCache, &GetSetDis);
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

          // Exit MPR mode on DRAM for DDR3/4
          if (Ddr4) {
            Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
            Status = MrcWriteMRS (MrcData, Controller, Channel, (MRC_BIT0 << Rank), mrMR3, Ddr4Mr3.Data);
          }

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "MC%u.C%u.R%u: \tLeft\tRight\tWidth\tCenter\tRxDqsPN\n", Controller, Channel, Rank);
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              continue;
            }
            Left  = LargestPassingStart[Controller][Channel][Byte];
            Right = LargestPassingEnd[Controller][Channel][Byte];
            lWidth = Right - Left;
            Center = Left + (lWidth / 2);
            //
            // Error Handler if eye not found for all bytes
            //
            if (lWidth == 0) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_ERROR,
                "ERROR!! NO EYE found for Mc: %u Channel: %u Rank: %u Byte: %u\n",
                Controller,
                Channel,
                Rank,
                Byte
                );
              //
              // Mark it as zero margin in MarginResult
              //
              Left   = 0;
              Right  = 0;
              Center = 0;
              MprStatus = mrcReadMPRErr;
            } else if (lWidth <= RMPR_MIN_WIDTH) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_WARNING,
                "WARNING!! lWidth <= %u for Mc: %u Channel: %u Rank: %u Byte: %u\n",
                RMPR_MIN_WIDTH,
                Controller,
                Channel,
                Rank,
                Byte
                );
            }
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RxDqsPDelay, ReadFromCache, &GetSetValue);
            FinalDqs[Controller][Channel][Rank][Byte] = Center + (INT16) GetSetValue;
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  B%u: \t%d\t%d\t%d\t%d\t%d\n",
              Byte,
              Left,
              Right,
              lWidth,
              Center,
              FinalDqs[Controller][Channel][Rank][Byte]
              );
            //
            // Update the MarginResult struct for future tests
            // Store the new margins relative to the center
            //
            Margin    = &Outputs->MarginResult[LastRxT][Rank][Controller][Channel][Byte][0];
            Margin[0] = ABS (10 * (Left  - Center));
            Margin[1] = ABS (10 * (Right - Center));
          } // for Byte
        } // for MrcRankExist
      } // for Channel
    } // for Controller
  } // for Rank

  //
  // Now program the DQS center values on populated ranks.
  // Need to do it after all ranks are trained, because we need to keep the same DQS value on all ranks
  // during the training.
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteExist (MrcData, Controller, Channel, Byte)) {
              continue;
            }
            GetSetValue = (INT64) FinalDqs[Controller][Channel][Rank][Byte];
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RxDqsPDelay, WriteToCache, &GetSetValue);
            MrcGetSetStrobe (MrcData, Controller, Channel, Rank, Byte, RxDqsNDelay, WriteToCache, &GetSetValue);
          }
        }
      }
    }
  }
  MrcFlushRegisterCachedData (MrcData);

  //
  // Restore DataControl0, and RxTrainingMode
  // Restore the bank mapping for DDR4
  //
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      if (Ddr4) {
        MrcGetSetBankSequence (MrcData, Controller, Channel, &BankMapping[Controller][Channel][0], 2, MRC_SET);
      }
    } // for Channel
  } // for Controller

  // Clean up after Test.
  if (Lpddr) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      if (MrcControllerExist (MrcData, Controller)) {
        Offset = OFFSET_CALC_CH (MC0_CR_CPGC2_V_CHICKEN_REG, MC1_CR_CPGC2_V_CHICKEN_REG, Controller);
        MrcWriteCR (MrcData, Offset, CpgcChickenPrevData[Controller]);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Revert MPR_TEST_REQ_DBLR.\n");
        GetSetVal = 0;
        MrcGetSetMc (MrcData, Controller, GsmMccHalfCachelineMode, WriteToCache | PrintValue, &GetSetVal);
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
            continue;
          }
          GetSetVal = RDRDsgPrevData;
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDsg, WriteToCache | PrintValue, &GetSetVal);
          GetSetVal = RDRDdgPrevData;
          MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctRDRDdg, WriteToCache | PrintValue, &GetSetVal);
          MrcFlushRegisterCachedData (MrcData);
          // Must update the XARB bubble injector when TAT values change
          SetTcBubbleInjector (MrcData, Controller, Channel);
        }
      }
    }
  }
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteNoCache, &GetSetDis);
  MrcFlushRegisterCachedData (MrcData);
  Status  = ChangeMargin (MrcData, RdT, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
  Status  = IoReset (MrcData);

  if ((MprStatus != mrcSuccess) && (Inputs->ExitOnFailure == 1)) {
    Status = MprStatus;
  }

  return Status;
}

/**
  Perform Read Timing Centering.
  Center Rx DQS-DQ using moderate pattern with 1D eye

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus       - if it succeded returns mrcSuccess
**/
MrcStatus
MrcReadTimingCentering (
  IN     MrcParameters *const MrcData
  )
{
  UINT8     ResetPerBit;
  UINT8     LoopCount;
  MrcStatus Status;

  ResetPerBit = 0;

  LoopCount   = 10;

  Status =  DQTimeCentering1D (MrcData, RdT, ResetPerBit, LoopCount, TRUE, FALSE);

  return Status;
}

/**
  This procedure is meant to find the calibrated step size for Per Bit DeSkew.

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus       - if it succeded returns mrcSuccess
**/
MrcStatus
MrcPerBitDeskewCalibration (
  IN     MrcParameters *const MrcData
  )
{
  //MrcInput  *Inputs;
  MrcOutput *Outputs;
  MrcStatus Status;
//  INT64     GetSetVal;
  UINT8     LoopCount;

  Outputs = &MrcData->Outputs;
  //Inputs  = &MrcData->Inputs;

  LoopCount   = 10;

  // If Read Per Bit Deskew is requested to be disabled, enable it temporarily to do calibration.
  //if (Inputs->RdTPbdDis) {
    //@todo: To disable Deskew set RxDqPerBitDeskew/RxDqPerBitDeskewOffset to 0
  //}

  Status = GetPerBitDeSkewStep (
            MrcData,
            Outputs->MarginResult,
            Outputs->ValidChBitMask,
            RdT,
            LoopCount
            );

  // Disable before continuing with training
  //if (Inputs->RdTPbdDis) {
    //@todo: To disable Deskew set RxDqPerBitDeskew/RxDqPerBitDeskewOffset to 0
  //}

  return Status;
}

/**
  This function executes the read Voltage centering.
  Center Rx DQ Vref using moderate pattern with 1D eye.

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus      - if it succeded returns mrcSuccess
**/
MrcStatus
MrcReadVoltageCentering (
  IN     MrcParameters *const MrcData
  )
{
  UINT8     LoopCount;

  LoopCount   = 10;

  return DQTimeCentering1D (MrcData, RdV, 0, LoopCount, TRUE, FALSE);
}

/**
  Perform Read Timing Centering in 2D.
  Final read timing centering using 2D algorithm and per bit optimization

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus       - if it succeded returns mrcSuccess
**/
MrcStatus
MrcReadTimingCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  MrcStatus       Status;
  UINT8           EnPerBit;
  UINT8           EnRxDutyCycle;
  UINT8           ResetPerBit;
  UINT8           LoopCount;
  UINT8           En2D;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcSuccess;
  LoopCount     = 15;

  if (!Inputs->RdTPbdDis) {
    EnPerBit      = 1;
    EnRxDutyCycle = 0;
    ResetPerBit   = 1;
    En2D          = 0;

    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Calling with EnRxDutyCycle = %d, EnPerBit = %d, ResetPerBit = %d En2D = %d\n",
      EnRxDutyCycle,
      EnPerBit,
      ResetPerBit,
      En2D
    );

    Status = DataTimeCentering2D (
      MrcData,
      Outputs->MarginResult,
      Outputs->McChBitMask,
      RdT,
      EnPerBit,
      EnRxDutyCycle,
      ResetPerBit,
      LoopCount,
      En2D
    );

    MrcPerBitDeskew (MrcData, Outputs->MarginResult, RdT);
  }

  if (mrcSuccess == Status) {
    EnPerBit      = 0;
    EnRxDutyCycle = 1;
    ResetPerBit   = 0;
    En2D          = 1;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "\nCalling with EnRxDutyCycle = %d, EnPerBit = %d, ResetPerBit = %d En2D = %d\n",
      EnRxDutyCycle,
      EnPerBit,
      ResetPerBit,
      En2D
    );

    Status = DataTimeCentering2D (
      MrcData,
      Outputs->MarginResult,
      Outputs->McChBitMask,
      RdT,
      EnPerBit,
      EnRxDutyCycle,
      ResetPerBit,
      LoopCount,
      En2D
    );
  }

  return Status;
}

/**
  Perform Read Voltage Centering in 2D.
  Note: This function currently only supports param = RdV

  @param[in,out] MrcData     - Include all MRC global data.
  @param[in,out] MarginByte  - Pointer to Marging Results data structure
  @param[in]     McChBitMask - MC Channel BIT mask for MC Channel(s) to work on
  @param[in]     Param       - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                8:WrTBit, 9:RdTBit, 10:RdVBit,
                                16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                ONLY RdV is allowed in this function
  @param[in]     EnPerBit    - Option to enable per bit margining
  @param[in]     ResetPerBit - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     LoopCount   - Loop count
  @param[in]     En2D        - Option to only run center at nominal Vref point

  @retval MrcStatus - If it succeded return mrcSuccess
**/
MrcStatus
ReadVoltageCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT16               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                McChBitMask,
  IN     UINT8                Param,
  IN     UINT8                EnPerBit,
  IN     UINT8                ResetPerBit,
  IN     UINT8                LoopCount,
  IN     UINT8                En2D
  )
{
  static const INT8   TimePoints[] = { 0, -8, 8 };
  static const UINT8  EHWeights[sizeof (TimePoints)] = { 1, 1, 1 };
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  UINT8               ResultType;
  UINT8               Controller;
  UINT8               Channel;
  UINT8               Byte;
  UINT8               Rank;
#ifdef MRC_DEBUG_PRINT
  UINT8               Edge;
#endif
  UINT8               RankResult;
  UINT8               RankMask;
  UINT8               bit;
  UINT8               lcloop;
  UINT8               tim;
  UINT8               paramB;
  UINT8               paramT;
  UINT8               BMap[MAX_SDRAM_IN_DIMM];
  INT8                SumEH;
  INT8                SumEHSign;
  UINT8               MaxTscale;
  UINT8               SaveLC;
  UINT16              mode;
  INT16               center[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32               value0[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32              BERStats[4];
  UINT32              TimScale[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT16               CenterSumByte[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32               CenterSumBit[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  UINT16              marginbit[MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  UINT16              EyeShape[3][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32              RxOffsetVdq;
  INT64               GetSetVal;
  UINT8               MaxVrefOffset;
  UINT8               MaxChannel;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  MaxChannel = Outputs->MaxChannels;
  Status    = mrcSuccess;
  SumEH     = 0;
  MaxTscale = 12;
  RankResult = 0;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  for (lcloop = 0; lcloop < (sizeof (BMap) / sizeof (BMap[0])); lcloop++) {
    BMap[lcloop] = lcloop;
  }
  //
  // Assume rank0 is always popuplated
  //
  if (Param == RdV) {
    paramB = RdVBit;
    paramT = RdT;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error Handler: Unknown Margin Parameter\n");
    Status = mrcReadVoltage2DError;
    return Status;
  }

  SetupIOTestBasicVA (MrcData, Outputs->McChBitMask, LoopCount, ABGSOE, 0, 0, 8, PatWrRd, 0, 0);
  //
  // Calculate SumEH for use in weighting equations
  //
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    SumEH += EHWeights[tim];

    //
    // Loop once at nominal Vref point
    //
    if (En2D == 0) {
      tim = sizeof (TimePoints);
    }
  }
  //
  // SumEH is used as divisor, make sure is never 0
  //
  if (SumEH == 0) {
    SumEH = 1;
  }

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (EnPerBit == 1) {
      // For Per bit run centering per Rank to get
      RankMask  = 1 << Rank;
    } else {
      RankMask = 0xF;
    }
    //
    // Reset PerBit Deskew to middle value before Byte training
    // Amplifier voltage offset for bit[x] of the DQ Byte.
    // Matched = {0: Most negative offset,... 16: 0 offset, ... 31: Most postive offset}.
    //
    if (ResetPerBit == 1) {
      // Matched = {0: Most negative offset,... 16: 0 offset, ... 31: Most postive offset}.
      // EnMultiCast=1, 0,0,0,0, UpdateHost=1, SkipWait=0
      Status = ChangeMargin (MrcData, paramB, 0xFFFFFFFF, 0, 1, 0, 0, Rank, 0, 0, 1, 0);
    }
    //
    // Select rank for REUT test
    //
    McChBitMask = 0;
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        McChBitMask |= SelectReutRanks(MrcData, Controller, Channel, RankMask, FALSE, 0);
      }
    } // Controller

    //
    // Continue with next rank if this rank is not present on any channel
    //
    if (!(McChBitMask)) {
      continue;
    }
    //
    // ####################################################
    // ################  Initialize EW/EH variables  ######
    // ####################################################
    //
    Status      = GetMarginByte (MrcData, Outputs->MarginResult, paramT, 0, 0xF);
    ResultType  = GetMarginResultType (paramT);

#ifdef MRC_DEBUG_PRINT
    if (En2D) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n### Measure Eye Height, per BYTE, at %s RankMask = 0x%X\n", "ALL (2D) Timing Points", RankMask);
    } else {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n### Measure Eye Height, per BYTE, at %s RankMask = 0x%X\n", "NOMINAL Timing", RankMask);
    }

    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
          continue;
        }

        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Mc%u.Ch%u ", Controller, Channel);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
        }
      }
    } // Controller


    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nByte    ");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
          continue;
        }

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", Byte);
        }
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t");
      }
    } // Controller

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nTScale\t");
#endif // MRC_DEBUG_PRINT
      //
      // Update TimScale to have the appropriate eye width (read from last saved parameters)
      //
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
          continue;
        }

        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (En2D > 0) {
            TimScale[Controller][Channel][Byte] =
               (
                MarginByte[ResultType][0][Controller][Channel][Byte][0] +
                MarginByte[ResultType][0][Controller][Channel][Byte][1]
                ) /
               20;
          } else {
            TimScale[Controller][Channel][Byte] = 1;
          }
          //
          // It is possible sumT is 0.
          //
          if (!(TimScale[Controller][Channel][Byte]) || (TimScale[Controller][Channel][Byte] > MaxTscale)) {
            TimScale[Controller][Channel][Byte] = MaxTscale;
          }

          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", TimScale[Controller][Channel][Byte]);
        } // Byte
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t");
      } // Channel
    } // Controller


    Status      = GetMarginByte (MrcData, Outputs->MarginResult, Param, RankResult, 0xF);
    ResultType  = GetMarginResultType (Param);

    //
    // ####################################################
    // ######   Measure Eye Height at all Timing Points  #####
    // ####################################################
    //
    //
    // Loop through all the Time Points to Test
    //
    for (tim = 0; tim < sizeof (TimePoints); tim++) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nRdTime\t");

      //
      // Setup Timing Offset for this point
      //
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
            continue;
          }

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            value0[Controller][Channel][Byte] = (INT32)(TimePoints[tim] * TimScale[Controller][Channel][Byte]) / MaxTscale;
            Status = ChangeMargin(MrcData, paramT, value0[Controller][Channel][Byte], 0, 0, Controller, Channel, Rank, Byte, 0, 1, 0);
            MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", value0[Controller][Channel][Byte]);
          }
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t");
        }
      } // Controller

      //
      // Run Margin Test
      //
      mode = 0;
      MaxVrefOffset = GetVrefOffsetLimits (MrcData, Param);
      Status = MrcGetBERMarginByte (
                MrcData,
                Outputs->MarginResult,
                McChBitMask,
                RankMask,
                RankMask,
                Param,
                mode,
                BMap,
                1,
                MaxVrefOffset,
                0,
                BERStats
                );
      RankResult = GetRankToStoreResults(MrcData, RankMask);
#ifdef MRC_DEBUG_PRINT
      for (Edge = 0; Edge < MAX_EDGES; Edge++) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, (Edge) ? "\nHigh\t\t":"\nLo\t\t");
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MaxChannel; Channel++) {
            if (!MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
              continue;
            }
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MRC_DEBUG_MSG(
                 Debug,
                 MSG_LEVEL_NOTE,
                 "%d\t",
                 MarginByte[ResultType][RankResult][Controller][Channel][Byte][Edge]
                 );
            } // Byte
            MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t");
          } // Channel
        } // Controller
      } // Edge

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nCenter\t");
#endif // MRC_DEBUG_PRINT
        //
        // Store Results
        //
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {

            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              center[Controller][Channel][RankResult][Byte] = (INT32)(MarginByte[ResultType][RankResult][Controller][Channel][Byte][1] -
                                                          MarginByte[ResultType][RankResult][Controller][Channel][Byte][0]);
              if (tim == 0) {
                CenterSumByte[Controller][Channel][Byte] = 0;
              }
              //
              // Calculate weight for this point
              //
              CenterSumByte[Controller][Channel][Byte] += EHWeights[tim] * center[Controller][Channel][RankResult][Byte];

              MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", center[Controller][Channel][RankResult][Byte] / 20);

              //
              // Record edges for use in per bit margining
              //
              EyeShape[tim][Controller][Channel][Byte][0] = MarginByte[ResultType][RankResult][Controller][Channel][Byte][0];
              EyeShape[tim][Controller][Channel][Byte][1] = MarginByte[ResultType][RankResult][Controller][Channel][Byte][1];
            } // Byte
            MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t");
          } // MC_CH_MASK_CHECK
        } // Channel
      } // Controller

      //
      // Loop once at nominal Vref point
      //
      if (En2D == 0) {
        tim = sizeof (TimePoints);
      }
    } // for tim

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n\nWtdCntr\t");
    //
    // ####################################################
    // ###########   Center Results per Byte   ############
    // ####################################################
    //
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
          continue;
        }

        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

        //
        // Calculate CenterPoint.  Round to Nearest Int
        //
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          SumEHSign = (CenterSumByte[Controller][Channel][Byte] < 0) ? (-1) : 1;

          CenterSumByte[Controller][Channel][Byte] = (CenterSumByte[Controller][Channel][Byte] + 10 * (SumEHSign * SumEH)) / (20 * SumEH);
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE,"%d\t", CenterSumByte[Controller][Channel][Byte]);

          //
          // Apply new center point
          //
          GetSetVal = CenterSumByte[Controller][Channel][Byte];
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, RxVref, WriteOffsetCached, &GetSetVal);

          //
          // Update the Eye Edges
          //
          for (tim = 0; tim < sizeof(TimePoints); tim++) {
            EyeShape[tim][Controller][Channel][Byte][0] = EyeShape[tim][Controller][Channel][Byte][0] + (10 * CenterSumByte[Controller][Channel][Byte]);
            EyeShape[tim][Controller][Channel][Byte][1] = EyeShape[tim][Controller][Channel][Byte][1] - (10 * CenterSumByte[Controller][Channel][Byte]);

            //
            // Loop once at nominal Vref point
            //
            if (En2D == 0) {
              tim = sizeof(TimePoints);
            }
          }
          //
          // Update MrcData for future tests (MarginResult points back to MrcData)
          // EyeShape for Vref 0 is assumed to have the best shape for future tests.
          //
          MarginByte[ResultType][RankResult][Controller][Channel][Byte][0] = (UINT16)EyeShape[0][Controller][Channel][Byte][0];
          MarginByte[ResultType][RankResult][Controller][Channel][Byte][1] = (UINT16)EyeShape[0][Controller][Channel][Byte][1];
        } // for Byte
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t");
      } // for Channel
    } // Controller


#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nRdVref\t");
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      for (Channel = 0; Channel < MaxChannel; Channel++) {
        if (!MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, RxVref, ReadFromCache, &GetSetVal);
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%d\t", (INT8)GetSetVal);
        }
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t");
      } // Channel
    } // Controller

#endif // MRC_DEBUG_PRINT
    //
    // ####################################################
    // ############    Measure Eye Height Per BIT   ########
    // ####################################################
    //
    if (EnPerBit) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE, (
        En2D
        ) ? "\n\n### Measure Eye Height, per BIT, at ALL (2D) Timing Points\n" :
        "\n\n### Measure Eye Height, per BIT, at NOMINAL Timing\n"
        );

      //
      // Stop on all lane fail
      //
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
#ifdef MRC_DEBUG_PRINT
            MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Mc%u.Ch%u\t\t\t\t\t",Controller, Channel);
            for (Byte = 0; Byte < Outputs->SdramCount - 1; Byte++) {
              MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t\t\t\t\t\t\t");
            }
#endif // MRC_DEBUG_PRINT
            // We enable error checking on all Cachelines and UI's of the Cacheline.
            //MrcSetChunkAndClErrMsk (MrcData, 0xFF, 0xFFFF);
            MrcSetupTestErrCtl (MrcData, ALSOE, 1);
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t");
          } // MC_CH_MASK_CHECK
        } // Channel
      } // Controller


#ifdef MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Byte % 12d\t\t\t", Byte);
            }
          }
        }
      } // Controller

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
#endif // MRC_DEBUG_PRINT
      //
      // Loop through all the Vref Points to Test
      //
      SaveLC = Outputs->DQPatLC;
      for (tim = 0; tim < sizeof (TimePoints); tim++) {
        //
        // Setup Timing Offset for this point
        //
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MaxChannel; Channel++) {
            if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {

              for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
                value0[Controller][Channel][Byte] = (INT32)(TimePoints[tim] * TimScale[Controller][Channel][Byte]) / MaxTscale;
                Status = ChangeMargin(MrcData, paramT, value0[Controller][Channel][Byte], 0, 0, Controller, Channel, Rank, Byte, 0, 1, 0);

                //
                // Amplifier voltage offset for bit[x] of the DQ Byte.
                // Matched = {0: Most negative offset,... 16: 0 offset, ... 31: Most postive offset}.
                //
                for (bit = 0; bit < MAX_BITS; bit++) {
                  marginbit[Controller][Channel][Byte][bit][0] = marginbit[Controller][Channel][Byte][bit][1] = 16;
                }
              }
            }
          }
        } // Controller


        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank %d \n", Rank);
        //
        // Run Margin Test
        // Loop through 2 times.  Once at low loop count and Once at high loopcount
        // Improves runtime
        // @TODO: Need 2 loops below if not using BASICVA
        //
        for (lcloop = 0; lcloop < 1; lcloop++) {
          Outputs->DQPatLC  = (lcloop == 0) ? 1 : SaveLC;
          mode              = 0;
          Status            = MrcGetMarginBit (MrcData, McChBitMask, Rank, marginbit, EyeShape[tim], paramB, mode, 15, MRC_PRINTS_ON);
        }
        //
        // Store Results
        //
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < MaxChannel; Channel++) {
            if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {

              for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
                for (bit = 0; bit < MAX_BITS; bit++) {
                  center[Controller][Channel][RankResult][Byte] = ((marginbit[Controller][Channel][Byte][bit][1] - 16) - (16 - marginbit[Controller][Channel][Byte][bit][0]));
                  if (tim == 0) {
                    CenterSumBit[Controller][Channel][RankResult][Byte][bit] = 0;
                  }
                  //
                  // Calculate weight for this point
                  //
                  CenterSumBit[Controller][Channel][RankResult][Byte][bit] += EHWeights[tim] * center[Controller][Channel][RankResult][Byte];
                } // Bit
              } // Byte
            } // MC_CH_MASK_CHECK
          } // Channel
        } // Controller

        //
        // Loop once at nominal Vref point
        //
        if (En2D == 0) {
          tim = sizeof (TimePoints);
        }
      } // for tim
      //
      // ####################################################
      // ############   Center Result Per BIT  ##############
      // ####################################################
      //
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nWgted Center\n\t\t\t");
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Byte%u", Byte);
        for (bit = 0; bit < MAX_BITS; bit++) {
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
        }
      }
      MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n");

      for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
        for (Channel = 0; Channel < MaxChannel; Channel++) {
          if (!MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
            continue;
          }
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "Mc%u.Ch%u\t\t",Controller, Channel);
          ChannelOut = &Outputs->Controller[Controller].Channel[Channel];

          //
          // Calculate and apply CenterPoint.  Round to Nearest Int
          //
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            for (bit = 0; bit < MAX_BITS; bit++) {
              SumEHSign = (CenterSumBit[Controller][Channel][Rank][Byte][bit] < 0) ? (-1) : 1;

              CenterSumBit[Controller][Channel][Rank][Byte][bit] = (CenterSumBit[Controller][Channel][Rank][Byte][bit] + (SumEHSign * SumEH)) / (2 * SumEH);

              //
              // Centerpoint needs to be added to starting DqPb value
              //
              CenterSumBit[Controller][Channel][Rank][Byte][bit] += (INT32)ChannelOut->RxDqVrefPb[Rank][Byte][bit].Center;

              //
              // Check for saturation
              //
              if (CenterSumBit[Controller][Channel][Rank][Byte][bit] > 15) {
                CenterSumBit[Controller][Channel][Rank][Byte][bit] = 15;
              } else if (CenterSumBit[Controller][Channel][Rank][Byte][bit] < 0) {
                CenterSumBit[Controller][Channel][Rank][Byte][bit] = 0;
              }

              MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "%x\t", CenterSumBit[Controller][Channel][Rank][Byte][bit]);

              //
              // Update MrcData
              //
              ChannelOut->RxDqVrefPb[Rank][Byte][bit].Center = (UINT8)CenterSumBit[Controller][Channel][Rank][Byte][bit];

              RxOffsetVdq = CenterSumBit[Controller][Channel][Rank][Byte][bit];
              //
              // Apply and propagate new centerpoint
              //
              Status = ChangeMargin (MrcData, RdVBit, RxOffsetVdq, 0, 0, Controller, Channel, Rank, Byte, 0, 1, 0);
            } // for bit
            MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\t");
          } // for Byte
          MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n");
        } // for Channel
      } // Controller

    } // if EnPerBit

    if (EnPerBit == 0) { // We use RankMask = 0x0F in this case
      break;
    }
  } // for Rank

/// @attention - This is used to determine if the PerBit routines are correct.  Left for sanity.
#ifdef MRC_DEBUG_PRINT
/*
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MC_CH_MASK_CHECK (McChBitMask, Controller, Channel, MaxChannel)) {
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        for (Rank = 0; Rank < MaxRank; Rank++) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            Offset = DDRDATA0CH0_CR_RXCONTROL2RANK0_REG +
               ((DDRDATA0CH1_CR_RXCONTROL2RANK0_REG - DDRDATA0CH0_CR_RXCONTROL2RANK0_REG) * Channel) +
               ((DDRDATA1CH0_CR_RXCONTROL2RANK0_REG - DDRDATA0CH0_CR_RXCONTROL2RANK0_REG) * Byte) +
               (DDRDATA0CH0_CR_RXCONTROL2RANK1_REG - DDRDATA0CH0_CR_RXCONTROL2RANK0_REG) * Rank;
            MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\nRdVref = % 3d   RdVBit = 0x%08X", (INT8)ChannelOut->RxVref[Byte],
                          MrcReadCR(MrcData, Offset));
          }
        }
      }
    }
  } // Controller
*/
#endif // MRC_DEBUG_PRINT

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  //
  // Clean up after test
  //
  Status = ChangeMargin (MrcData, paramT, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0);

  return Status;
}

/**
  Perform Read Voltage Centering in 2D.
  Note: This function currently only supports param = RdV

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it succeded return mrcSuccess
**/
MrcStatus
MrcReadVoltageCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  MrcOutput *Outputs;
  MrcStatus Status;
  UINT8     EnPerBit;
  UINT8     ResetPerBit;
  UINT8     LoopCount1;
  UINT8     LoopCount2;
  UINT8     En2D;
  UINT8     Controller;
  UINT8     Channel;
  BOOLEAN   Ddr4;
  BOOLEAN   Any2Dpc;
  UINT8     MaxChannel;

  Outputs    = &MrcData->Outputs;
  Ddr4       = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  MaxChannel = Outputs->MaxChannels;
  Any2Dpc    = FALSE;
  Status     = mrcSuccess;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannel; Channel++) {
      if (MrcChannelExist(MrcData, Controller, Channel)) {
        if (Outputs->Controller[Controller].Channel[Channel].DimmCount == 2) {
          Any2Dpc = TRUE;
          break;
        }
      }
    }
  } // Controller

  //EnPerBit    = 1;
  //ResetPerBit = 1;
  //En2D        = 0;

  LoopCount1  = 10;  // Lower loopcount for the first 2D pass on DDR4 2DPC
  LoopCount2  = 15;

  //Status = ReadVoltageCentering2D (
  //          MrcData,
  //          Outputs->MarginResult,
  //          Outputs->ValidChBitMask,
  //          RdV,
  //          EnPerBit,
  //          ResetPerBit,
  //          LoopCount2,
  //          En2D
  //          );

  if (mrcSuccess == Status) {
    EnPerBit    = 0;
    ResetPerBit = 0;
    En2D        = 1;

    if (Ddr4 && Any2Dpc) {
      Status = ReadVoltageCentering2D (
        MrcData,
        Outputs->MarginResult,
        Outputs->ValidChBitMask,
        RdV,
        EnPerBit,
        ResetPerBit,
        LoopCount1,
        En2D
        );
    }

    if (Status == mrcSuccess) {
      Status = ReadVoltageCentering2D (
        MrcData,
        Outputs->MarginResult,
        Outputs->ValidChBitMask,
        RdV,
        EnPerBit,
        ResetPerBit,
        LoopCount2,
        En2D
        );
    }
  }

  return Status;
}

/**
  Perform Early Read Timing 2D centering Training.
  Center read DQ-DQS timing while testing differents RxVref points.

  @param[in]  MrcData   - Include all MRC global data.
  @param[in]  TestType  - 0: Normal Traffic, 1: Read MPR.
  @param[in]  Prints    - Debug prints enable/disable

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
EarlyReadTimingCentering2D (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 TestType,
  IN  BOOLEAN               Prints
  )
{
  MrcInput    *Inputs;
  MrcOutput   *Outputs;
  MrcStatus   Status;
  MrcDdrType  DdrType;
  INT64       Min;
  INT64       Max;
  UINT32      LowVref;
  UINT32      HighVref;
  INT16       Points2DMin;
  INT16       Points2DMax;
  UINT8       LoopCount;
  UINT8       StepSize;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;

  if (DdrType == MRC_DDR_TYPE_LPDDR4) {
    LowVref = 140; // We're currently seeing the RxV eye shifted towards VOH.  No need to go to 0.
    HighVref = 440; // LP4 Pull-Up Calibrated Voltage for VOH
    StepSize = 2;
  } else {
    LowVref   = Outputs->VddVoltage[Inputs->MemoryProfile];
    HighVref  = LowVref;
    if (Outputs->OdtMode == MrcOdtModeVddq) {
      // Sweep from 2/3 VDDq to VDDq
      LowVref *= 2;
      LowVref   = UDIVIDEROUND (LowVref, 3);
    } else {
      // Sweep from 1/4 of VDDq to 2/3 of VDDq
      HighVref *= 2;
      LowVref   = UDIVIDEROUND (LowVref, 4);
      HighVref  = UDIVIDEROUND (HighVref, 3);
    }
    StepSize = 8;
  }
  StepSize = (Inputs->MemoryProfile != STD_PROFILE) ? 1 : StepSize;

  MrcEncodeRxVref (MrcData, LowVref, &Min);
  MrcEncodeRxVref (MrcData, HighVref, &Max);

  Points2DMin = (INT16) Min;
  Points2DMax = (INT16) Max;

  MrcGetSetLimits (
    MrcData,
    RxVref,
    &Min,
    &Max,
    NULL
    );

  Points2DMin = MAX (Points2DMin, (INT16) Min);

  LoopCount   = 10;
  Points2DMax = MIN (Points2DMax, (INT16) Max);
  Status = EarlyLinearCentering2D (
            MrcData,
            Outputs->McChBitMask,
            Outputs->ValidRankMask,
            RdT,
            RdV,
            Points2DMin,
            Points2DMax,
            StepSize,
            LoopCount,
            TestType,
            Prints
            );

  return Status;
}

/**
  Perform Read Timing Linear Centering in different Read Vref points using MPR mode.
  (Does not require Writes to be functional)

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it success return mrcSuccess
**/
MrcStatus
MrcEarlyReadMprTimingCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  return EarlyReadTimingCentering2D (MrcData, ERTC2D_MPR, TRUE);
}

/**
  Perform Early Read Timing 2D centering Training.
  Center read DQ-DQS timing while testing different RxVref points.

  @param[in, out] MrcData   - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcEarlyReadTimingCentering2D (
  IN     MrcParameters *const MrcData
  )
{
  return EarlyReadTimingCentering2D (MrcData, ERTC2D_NORMAL, TRUE);
}

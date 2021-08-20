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
#include "MrcMaintenance.h"
#include "MrcCrosser.h"
#include "MrcCpgcApi.h"
#include "Cpgc20TestCtl.h"
#include "MrcCommon.h"

// For MPR pattern "00000000"
MRC_BG_BANK_PAIR Ddr4RdMprBankL2pBank3[2] = { {0, 3}, {1, 3} };

/**
  Perform Read MPR Training using normal reads.
  Centers read DQ-DQS with MPR pattern.

  @param[in, out] MrcData    - Pointer to MRC global data.
  @param[in]      DqsStepInc - ReadMprDqs Step increment value.
  @param[in]      Print      - debug prints enable/disable.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcReadMprTrainingNormal (
  IN OUT MrcParameters *const MrcData,
  IN     INT8                 DqsStepInc,
  IN     BOOLEAN              Print
  )
{
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  const MRC_FUNCTION  *MrcCall;
  MrcOutput           *Outputs;
  MrcIntOutput        *MrcIntData;
  MrcChannelOut       *ChannelOut;
  MrcStatus           Status;
  MrcStatus           MprStatus;
  UINT8               Channel;
  UINT8               Rank;
  UINT8               Byte;
  UINT8               ChBitMask;
  UINT8               RankMask;  // RankBitMask for both channels
  UINT8               LoopCount;
  UINT64              ErrStatus;
  UINT64              ChunkStatus;
  UINT16              Result;
  UINT16              ChunkResult[MAX_CHANNEL];
  INT8                DqsDelay;
  INT32               CurrentPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32               CurrentPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32               LargestPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32               LargestPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32               FinalDqs[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32               cWidth;
  INT32               lWidth;
  INT32               Center;
  INT32               Left;
  INT32               Right;
  INT64               GetSetDis;
  INT64               GetSetEn;
  INT64               GetSetVal;
  UINT8               SubCh;
  BOOLEAN             Pass;
  BOOLEAN             Lpddr4;
  BOOLEAN             Ddr4;
  BOOLEAN             Gear2;
  BOOLEAN             SkipZqSave;
  UINT32              *Margin;
  UINT32              Pattern0;
  UINT32              Pattern1;
  UINT32              RdDataPtn;    //Read Data Pattern in 32 bit
  DDR4_MODE_REGISTER_3_STRUCT       Ddr4Mr3;
  INT8                RmprDqsStart;
  INT8                RmprDqsStop;
  MRC_BG_BANK_PAIR    BankMapping[MAX_CHANNEL][MAX_BANKS];
#ifdef MRC_DEBUG_PRINT
  UINT8               BitGroupErr[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
#endif // MRC_DEBUG_PRINT

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Debug     = Print ? &Outputs->Debug : NULL;
  Status    = mrcSuccess;
  MprStatus = mrcSuccess;
  Lpddr4    = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4      = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  ChBitMask = Outputs->ValidChBitMask;
  RankMask  = Outputs->ValidRankMask;
  GetSetDis = 0;
  GetSetEn  = 1;
  Pattern0  = 0xA5;      // Must Match the below RdDataPtn
  Pattern1  = 0xA5;      // Must Match the below RdDataPtn
  // Setup the Read Data Pattern.  This depends on technology.
  //          Lpddr4          Ddr4
  // Pattern  10100101        10101010
  RdDataPtn = (Lpddr4) ? 0xA5A5A5A5 : 0xAAAAAAAA;

  LoopCount = 10;

  // Setup REUT Engine
  SetupIOTestCpgcRead (MrcData, ChBitMask, LoopCount, NSOE, RdDataPtn);

  // We call SetupIOTest() many times during the training, no need to issue ZQCAL every time.
  // They will be converted to NOP anyway.
  SkipZqSave = MrcIntData->SkipZq;
  MrcIntData->SkipZq = TRUE;

  Gear2 = Outputs->Gear2;
  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && (Outputs->Frequency == f1067)) {
    Gear2 = FALSE;
  }

  if (Gear2) {
    RmprDqsStart = RMPR_DQS_START_G2; // [-63..63]
    RmprDqsStop  = RMPR_DQS_STOP_G2;
  } else {
    RmprDqsStart = RMPR_DQS_START;    // [-31..31]
    RmprDqsStop  = RMPR_DQS_STOP;
  }

  // Set DQS Delay to 32
  GetSetVal = Gear2 ? 64 : 32;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Set DQS Delay to 32
      // Update RxDqsP & RxDqsN - leave other parameter the same; can we update in the next loop or do it per channel
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsNDelay, WriteToCache, &GetSetVal);
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsPDelay, WriteToCache, &GetSetVal);
      if (Ddr4) {
        // Save Bank Mapping
        MrcGetSetBankSequence (MrcData, Channel, &BankMapping[Channel][0], 2, MRC_GET);
        MrcGetSetBankSequence (MrcData, Channel, Ddr4RdMprBankL2p, 2, MRC_SET);
      }
    }
  } // Channel
  MrcFlushRegisterCachedData (MrcData);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!((MRC_BIT0 << Rank) & RankMask)) {
      continue; // Skip if both channels empty
    }

    // Program MR3 and Mask RAS/WE to prevent scheduler for issuing non-Read commands
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      SelectReutRanks (MrcData, Channel, 1 << Rank, FALSE, 0);
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];

      // Enter MPR mode on DRAM for DDR4
      if (Ddr4) {
        Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
        Ddr4Mr3.Bits.MprOperation = 1;
        Status = MrcWriteMRS (MrcData, Channel, (1 << Rank), mrMR3, Ddr4Mr3.Data);
      } else { // Lpddr4
        for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
          if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
            MrcIssueMrw (MrcData, Channel, SubCh, Rank, 32, Pattern0, FALSE, FALSE, TRUE); // DQ Calibration Pattern "A"
            MrcIssueMrw (MrcData, Channel, SubCh, Rank, 40, Pattern1, FALSE, FALSE, TRUE); // DQ Calibration Pattern "B"
            MrcIssueMrw (MrcData, Channel, SubCh, Rank, 15, 0x00, FALSE, FALSE, TRUE); // Lower Byte Invert for DQ Calibration
            MrcIssueMrw (MrcData, Channel, SubCh, Rank, 20, 0x00, FALSE, FALSE, TRUE); // Upper Byte Invert for DQ Calibration
          }
        }
      }
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteNoCache, &GetSetEn);
    } // for Channel

//    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "--- CPGC-based RDMPR ---\n");
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank = %u\n", Rank);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\t0                1\nByte\t");
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE, (
      Outputs->SdramCount == (MAX_SDRAM_IN_DIMM)
      ) ? "0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8" : "0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7"
      );

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDqsDelay");
    for (DqsDelay = RmprDqsStart; DqsDelay < RmprDqsStop; DqsDelay += DqsStepInc) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5d\t", DqsDelay);
      // Program DQS Delays and download the Reg File for the current rank.
      Status = ChangeMargin (MrcData, RdT, DqsDelay, 0, 1, 0, 0, 0, 0, 0, 0);

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            (Channel != 0) ? "" : ((Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "                  " : "                ")
            );
        } else {
          ChannelOut = &Outputs->Controller[0].Channel[Channel];
        }
      }

//      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "-- pause -- \n");
//      MrcWriteCR(MrcData, BIOS_POST_CODE_PCU_REG, 0);
//      do {} while (MrcReadCR(MrcData, BIOS_POST_CODE_PCU_REG) == 0);

      if (Ddr4) {
        // Clean the Rx FIFO using another MPR sequence - Bank 3 (all zeroes)
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            MrcGetSetBankSequence (MrcData, Channel, Ddr4RdMprBankL2pBank3, 2, MRC_SET);
          }
        } // for Channel
      }
      if (Lpddr4) {
        // Clean the Rx FIFO using another MPR sequence - all zeroes
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
            continue;
          }
          ChannelOut = &Outputs->Controller[0].Channel[Channel];
          MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteNoCache, &GetSetDis);
          for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
            if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
              MrcIssueMrw (MrcData, Channel, SubCh, Rank, 32, 0, FALSE, FALSE, TRUE); // DQ Calibration Pattern "A"
              MrcIssueMrw (MrcData, Channel, SubCh, Rank, 40, 0, FALSE, FALSE, TRUE); // DQ Calibration Pattern "B"
            }
          }
          MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteNoCache, &GetSetEn);
        } // for Channel
      }
      SetupIOTestCpgcRead (MrcData, ChBitMask, 4, NSOE, RdDataPtn);
      RunIOTest (MrcData, ChBitMask, Outputs->DQPat, 1, 0);

      // Go back to the original MPR pattern
      if (Ddr4) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            MrcGetSetBankSequence (MrcData, Channel, Ddr4RdMprBankL2p, 2, MRC_SET);
          }
        } // for Channel
      }
      if (Lpddr4) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
            continue;
          }
          ChannelOut = &Outputs->Controller[0].Channel[Channel];
          MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteNoCache, &GetSetDis);
          for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
            if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
              MrcIssueMrw (MrcData, Channel, SubCh, Rank, 32, Pattern0, FALSE, FALSE, TRUE); // DQ Calibration Pattern "A"
              MrcIssueMrw (MrcData, Channel, SubCh, Rank, 40, Pattern1, FALSE, FALSE, TRUE); // DQ Calibration Pattern "B"
            }
          }
          MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteNoCache, &GetSetEn);
        } // for Channel
      }

      SetupIOTestCpgcRead (MrcData, ChBitMask, LoopCount, NSOE, RdDataPtn);
      RunIOTest (MrcData, ChBitMask, Outputs->DQPat, 1, 0);

      // Update results for all ch/bytes
#ifdef MRC_DEBUG_PRINT
        MrcCall->MrcSetMem ((UINT8 *) BitGroupErr, sizeof (BitGroupErr), 0);
#endif // MRC_DEBUG_PRINT
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        ErrStatus = 0;
        ChunkStatus = 0;
        Result = 0;
        ChunkResult[Channel] = 0;
        for (SubCh = 0; SubCh < MrcIntData->SubChEngCount; SubCh++){
          if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
            // Read out per byte error results and check for any byte error
            MrcGetMiscErrStatus (MrcData, Channel, SubCh, ByteGroupErrStatus, &ErrStatus);
            // Read per chunk error status
            MrcGetMiscErrStatus (MrcData, Channel, SubCh, ChunkErrStatus, &ChunkStatus);
            Result |= MrcCall->MrcLeftShift64 (ErrStatus, (SubCh == 0) ? 0 : 4);
            ChunkResult[Channel] |= MrcCall->MrcLeftShift64 (ChunkStatus, (SubCh == 0) ? 0 : 4);
#ifdef MRC_DEBUG_PRINT
            MrcGetBitGroupErrStatus (MrcData, Channel, SubCh, BitGroupErr[Channel]);
#endif // MRC_DEBUG_PRINT
          }
        }

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
            continue;
          }
          Pass = ((Result & (1 << Byte)) == 0);
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Pass ? ". " : "# ");

          if (DqsDelay == RmprDqsStart) {
            if (Pass) {
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = DqsDelay;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte] = DqsDelay;
            } else {
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = RmprDqsStart - 2;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte] = RmprDqsStart - 2;
            }
          } else {
            if (Pass) {
              if (CurrentPassingEnd[Channel][Byte] == (DqsDelay - DqsStepInc)) {
                CurrentPassingEnd[Channel][Byte] = DqsDelay;
              } else {
                CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = DqsDelay;
              }
              // Update Largest variables
              cWidth  = CurrentPassingEnd[Channel][Byte] - CurrentPassingStart[Channel][Byte];
              lWidth  = LargestPassingEnd[Channel][Byte] - LargestPassingStart[Channel][Byte];
              if (cWidth > lWidth) {
                LargestPassingStart[Channel][Byte]  = CurrentPassingStart[Channel][Byte];
                LargestPassingEnd[Channel][Byte]    = CurrentPassingEnd[Channel][Byte];
              }
            }
          }
        } // for Byte
      } // for Channel

#ifdef MRC_DEBUG_PRINT
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          ErrStatus = 0;
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            ErrStatus |= MrcCall->MrcLeftShift64 (BitGroupErr[Channel][Byte], Byte * 8);
          }
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "0x%016llX 0x%04X ",
              ErrStatus,
              ChunkResult[Channel]
              );
          }
        }
#endif  // MRC_DEBUG_PRINT

      Status = IoReset (MrcData);
    } // for DqsDelay

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    // Clean Up registers.
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        ChannelOut = &Outputs->Controller[0].Channel[Channel];

        // MPR_TRAIN_DDR_ON bit will force a special command so clear it before MRS command
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteNoCache, &GetSetDis);

        // Exit MPR mode on DRAM for DDR4
        if (Ddr4) {
          Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
          Status = MrcWriteMRS (MrcData, Channel, (MRC_BIT0 << Rank), mrMR3, Ddr4Mr3.Data);
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u.R%u: \tLeft\tRight\tWidth\tCenter\tRxDqsPN\n", Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          Left  = LargestPassingStart[Channel][Byte];
          Right = LargestPassingEnd[Channel][Byte];
          lWidth = Right - Left;
          Center = Left + (lWidth / 2);

          // Error Handler if eye not found for all bytes
          if (lWidth == 0) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_ERROR,
              "\nERROR!! NO EYE found for Channel: %u Rank: %u Byte: %u \n",
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
              "WARNING!! lWidth <= %u for Channel: %u Rank: %u Byte: %u\n",
              RMPR_MIN_WIDTH,
              Channel,
              Rank,
              Byte
              );
          }
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsPDelay, ReadFromCache, &GetSetVal);
          FinalDqs[Channel][Rank][Byte] = Center + (INT32) GetSetVal;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "  B%u: \t%d\t%d\t%d\t%d\t%d\n",
            Byte,
            Left,
            Right,
            lWidth,
            Center,
            FinalDqs[Channel][Rank][Byte]
            );
          // Update the MarginResult struct for future tests
          Margin    = &Outputs->MarginResult[LastRxT][Rank][Channel][Byte][0];
          Margin[0] = ABS (10 * (Left  - Center));
          Margin[1] = ABS (10 * (Right - Center));
        } // for Byte
      }
    } // for Channel
  } // for Rank

  // Now program the DQS center values on populated ranks.
  // Need to do it after all ranks are trained, because we need to keep the same DQS value on all ranks
  // during the training.
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          GetSetVal = (INT64) FinalDqs[Channel][Rank][Byte];
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsPDelay, WriteToCache, &GetSetVal);
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsNDelay, WriteToCache, &GetSetVal);
        }
      }
    }
  }
  MrcFlushRegisterCachedData (MrcData);

  if (Ddr4) {
    // Restore the bank mapping
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      MrcGetSetBankSequence (MrcData, Channel, &BankMapping[Channel][0], 2, MRC_SET);
    } // for Channel
  }
  // Clean up after Test.
  Status  = ChangeMargin (MrcData, RdT, 0, 0, 1, 0, 0, 0, 0, 0, 0);
  Status  = IoReset (MrcData);

  MrcIntData->SkipZq = SkipZqSave;

  if (MprStatus != mrcSuccess) {
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
  MrcStatus   Status;
  UINT32      RankMask;

  RankMask = MrcData->Outputs.ValidRankMask;

  if (MrcData->Outputs.LpddrEctDone) {
    Status = MrcReadMprTrainingNormal (MrcData, RMPR_DQS_STEP, MRC_PRINTS_ON); // CPGC-based
  } else {
    Status = ReadMprTraining (MrcData, RankMask, RMPR_DQS_STEP, MRC_PRINTS_ON); // HW-based
  }
  return Status;
}

/**
  Perform Read MPR Training.
  Center read DQ-DQS with MPR pattern.
  This is the HW method of the Read MPR algorithm.

  @param[in, out] MrcData    - Include all MRC global data.
  @param[in]      RankMask   - Bitmask of ranks to train.
  @param[in]      DqsStepInc - ReadMprDqs Step increment value.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
ReadMprTraining (
  IN OUT MrcParameters *const MrcData,
  IN     UINT32               RankMask,
  IN     INT8                 DqsStepInc,
  IN     BOOLEAN              Print
  )
{
  const MrcInput  *Inputs;
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  MrcChannelOut   *ChannelOut;
  MrcStatus       Status;
  MrcStatus       MprStatus;
  MrcDdrType      DdrType;
  UINT8           Channel;
  UINT8           SubCh;
  UINT8           Rank;
  UINT8           Byte;
  UINT8           ChBitMask;
  UINT8           LoopCount;
  UINT8           TestDoneStatus;
  INT8            DqsDelay;
  INT32           CurrentPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32           CurrentPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32           LargestPassingStart[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32           LargestPassingEnd[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32           FinalDqs[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32           cWidth;
  INT32           lWidth;
  INT32           Center;
  INT32           Left;
  INT32           Right;
  INT64           GroupOffset;
  INT64           GetSetDis;
  INT64           GetSetEn;
  INT64           GetSetVal;
  INT64           LeakerCompSave[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  BOOLEAN         Pass;
  BOOLEAN         Ddr4;
  BOOLEAN         Gear2;
  UINT32          *Margin;
  UINT32          Offset;
  INT8            RmprDqsStart;
  INT8            RmprDqsStop;
  INT64           GetSetValue;
  MRC_BG_BANK_PAIR                            BankMapping[MAX_CHANNEL][MAX_BANKS];
  CH0_SC0_CR_CPGC_SEQ_CTL_STRUCT              CpgcSeqCtl;
  CH0_SC0_CR_CPGC_SEQ_STATUS_STRUCT           CpgcSeqStatus;
  DDR4_MODE_REGISTER_3_STRUCT                 Ddr4Mr3;

  Inputs     = &MrcData->Inputs;
  Outputs    = &MrcData->Outputs;
  Debug      = Print ? &Outputs->Debug : NULL;
  Status     = mrcSuccess;
  MprStatus  = mrcSuccess;
  DdrType    = Outputs->DdrType;
  Ddr4       = (DdrType == MRC_DDR_TYPE_DDR4);
  GetSetDis  = 0;
  GetSetEn   = 1;
  ChBitMask  = Outputs->ValidChBitMask;

  LoopCount = 10;

  //
  // Use basic addressing mode (open a page on a rank and keep writing/reading to it)
  // Rotate through all 8 logical ranks
  // LFSR and LMN disabled.
  //

  Gear2 = Outputs->Gear2;
  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && (Outputs->Frequency == f1067)) {
    Gear2 = FALSE;
  }
  if (Ddr4 && Gear2) {
    RmprDqsStart = RMPR_DQS_START_G2; // [-63..63]
    RmprDqsStop  = RMPR_DQS_STOP_G2;
  } else {
    RmprDqsStart = RMPR_DQS_START;    // [-31..31]
    RmprDqsStop  = RMPR_DQS_STOP;
  }
  GroupOffset = Gear2 ? 64 : 32; // RxDqs PI Center
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Set DQS Delay to 32
      // Update RxDqsP & RxDqsN - leave other parameter the same; can we update in the next loop or do it per channel
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsNDelay, WriteToCache, &GroupOffset);
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsPDelay, WriteToCache, &GroupOffset);
      if (Ddr4) {
        // Save Bank Mapping
        MrcGetSetBankSequence (MrcData, Channel, &BankMapping[Channel][0], 2, MRC_GET);
        MrcGetSetBankSequence (MrcData, Channel, Ddr4RdMprBankL2p, 2, MRC_SET);
      }
    }
  }
  MrcFlushRegisterCachedData (MrcData);

  //
  // Setup REUT Engine
  //
  SetupIOTestMPR (MrcData, ChBitMask, LoopCount, NSOE, 0, 0);

  // Enable Rank Mux Override
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteToCache, &GetSetEn);

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (!((MRC_BIT0 << Rank) & RankMask)) {
      continue; // Skip if both channels empty
    }

    // Update Rank Mux Override for the rank under test
    GetSetVal = Rank;
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideVal, WriteToCache, &GetSetVal);
    //
    // Program MR3 and Mask RAS/WE to prevent scheduler for issuing non-Read commands
    //
    ChBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChBitMask |= SelectReutRanks (MrcData, Channel, 1 << Rank, FALSE, 0);
      if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      //
      // Enter MPR mode on DRAM for DDR4
      //
      if (Ddr4) {
        Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
        Ddr4Mr3.Bits.MprOperation = 1;
        Status = MrcWriteMRS (MrcData, Channel, (1 << Rank), mrMR3, Ddr4Mr3.Data);
      } else { // Lpddr4
        for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
          if (MrcSubChannelExist (MrcData, Channel, SubCh)) {
            MrcIssueMrw (MrcData, Channel, SubCh, Rank, 32, 0x55, FALSE, FALSE, TRUE); // DQ Calibration Pattern "A"
            MrcIssueMrw (MrcData, Channel, SubCh, Rank, 40, 0x55, FALSE, FALSE, TRUE); // DQ Calibration Pattern "B"
            MrcIssueMrw (MrcData, Channel, SubCh, Rank, 15, 0x00, FALSE, FALSE, TRUE); // Lower Byte Invert for DQ Calibration
            MrcIssueMrw (MrcData, Channel, SubCh, Rank, 20, 0x00, FALSE, FALSE, TRUE); // Upper Byte Invert for DQ Calibration
          }
        }
      }
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteNoCache, &GetSetEn);
    } // for Channel

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Rank = %u\n", Rank);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel\t0                1\nByte\t");
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE, (
      Outputs->SdramCount == (MAX_SDRAM_IN_DIMM)
      ) ? "0 1 2 3 4 5 6 7 8 0 1 2 3 4 5 6 7 8" : "0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7"
      );

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nDqsDelay");
    for (DqsDelay = RmprDqsStart; DqsDelay < RmprDqsStop; DqsDelay += DqsStepInc) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n% 5d\t", DqsDelay);

      //
      // Program DQS Delays and download the Reg File for the current rank.
      //
      Status = ChangeMargin (MrcData, RdT, DqsDelay, 0, 1, 0, 0, 0, 0, 0, 0);

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            (Channel != 0) ? "" : ((Outputs->SdramCount == MAX_SDRAM_IN_DIMM) ? "                  " : "                ")
            );
        } else {
          // Enable RX Training mode. Turn on the ODT.
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocReadDqDqsMode, WriteToCache, &GetSetEn);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn,    WriteToCache, &GetSetEn);
          MrcFlushRegisterCachedData (MrcData);

          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
              continue;
            }
            // Force on SenseAmp
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceBiasOn, WriteToCache, &GetSetEn);
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceRxAmpOn, WriteToCache, &GetSetEn);
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLeakerComp, ReadFromCache, &LeakerCompSave[Channel][Byte]);
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLeakerComp, WriteToCache, &GetSetDis);
          }
          MrcFlushRegisterCachedData (MrcData);
        }
      } // for Channel

      Status = IoReset (MrcData);

      // Start CPGC and run for 1uS
      CpgcSeqCtl.Data = 0;
      CpgcSeqCtl.Bits.START_TEST = 1;
      Cpgc20ControlRegWrite (MrcData, CpgcSeqCtl);

      // Wait for test to start clearing errors.
      MrcWait (MrcData, START_TEST_DELAY);

      // Clear Results for Prior Test and wait to obtain results
      Status = IoReset (MrcData);
      MrcWait (MrcData, IO_RESET_DELAY);

      // Stop CPGC
      CpgcSeqCtl.Data = 0;
      CpgcSeqCtl.Bits.STOP_TEST = 1;
      Cpgc20ControlRegWrite (MrcData, CpgcSeqCtl);

      // Wait till CPGC test is done on all participating channels
      do {
        TestDoneStatus = 0;
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
            Offset = OFFSET_CALC_CH (CH0_SC0_CR_CPGC_SEQ_STATUS_REG, CH1_SC0_CR_CPGC_SEQ_STATUS_REG, Channel);
            CpgcSeqStatus.Data = MrcReadCR (MrcData, Offset);
            TestDoneStatus |= (CpgcSeqStatus.Bits.TEST_DONE) << Channel;
          }
        }
      } while ((TestDoneStatus & ChBitMask) != ChBitMask);


      // Update results for all ch/bytes
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }

        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ");
            continue;
          }
          Offset = MrcGetOffsetDataTrainFeedback (MrcData, Channel, Byte);
          Pass = (MrcReadCR (MrcData, Offset) == 1);

          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, Pass ? ". " : "# ");

          if (DqsDelay == RmprDqsStart) {
            if (Pass) {
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = DqsDelay;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte] = DqsDelay;
            } else {
              CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = RmprDqsStart - 2;
              LargestPassingStart[Channel][Byte] = LargestPassingEnd[Channel][Byte] = RmprDqsStart - 2;
            }
          } else {
            if (Pass) {
              if (CurrentPassingEnd[Channel][Byte] == (DqsDelay - DqsStepInc)) {
                CurrentPassingEnd[Channel][Byte] = DqsDelay;
              } else {
                CurrentPassingStart[Channel][Byte] = CurrentPassingEnd[Channel][Byte] = DqsDelay;
              }
              // Update Largest variables
              cWidth  = CurrentPassingEnd[Channel][Byte] - CurrentPassingStart[Channel][Byte];
              lWidth  = LargestPassingEnd[Channel][Byte] - LargestPassingStart[Channel][Byte];
              if (cWidth > lWidth) {
                LargestPassingStart[Channel][Byte]  = CurrentPassingStart[Channel][Byte];
                LargestPassingEnd[Channel][Byte]    = CurrentPassingEnd[Channel][Byte];
              }
            }
          } // if (DqsDelay == RmprDqsStart)
        } // for Byte
      } // for Channel

      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }

        // Clear RxAmp and Bias overrides.
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceBiasOn,  WriteToCache, &GetSetDis);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceRxAmpOn, WriteToCache, &GetSetDis);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLeakerComp,   WriteToCache, &LeakerCompSave[Channel][Byte]);
        }
        MrcFlushRegisterCachedData (MrcData);

        // Restore DataControl0 (clear RxTrainingMode and ForceOdtOn)
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocForceOdtOn,    WriteToCache, &GetSetDis);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, MAX_SDRAM_IN_DIMM, GsmIocReadDqDqsMode, WriteToCache, &GetSetDis);
        MrcFlushRegisterCachedData (MrcData);
      } // for Channel

      Status = IoReset (MrcData);
    } // for DqsDelay

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

    //
    // Clean Up registers.
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        ChannelOut = &Outputs->Controller[0].Channel[Channel];

        //
        // MPR_TRAIN_DDR_ON bit will force a special command so clear it before MRS command
        //
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocMprTrainDdrOn, WriteNoCache, &GetSetDis);

        //
        // Exit MPR mode on DRAM for DDR4
        //
        if (Ddr4) {
          Ddr4Mr3.Data = ChannelOut->Dimm[Rank / 2].Rank[Rank % 2].MR[mrMR3];
          Status = MrcWriteMRS (MrcData, Channel, (MRC_BIT0 << Rank), mrMR3, Ddr4Mr3.Data);
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u.R%u: \tLeft\tRight\tWidth\tCenter\tRxDqsPN\n", Channel, Rank);
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          Left  = LargestPassingStart[Channel][Byte];
          Right = LargestPassingEnd[Channel][Byte];
          lWidth = Right - Left;
          Center = Left + (lWidth / 2);
          //
          // Error Handler if eye not found for all bytes
          //
          if (lWidth == 0) {
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_ERROR,
              "ERROR!! NO EYE found for Channel: %u Rank: %u Byte: %u\n",
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
              "WARNING!! lWidth <= %u for Channel: %u Rank: %u Byte: %u\n",
              RMPR_MIN_WIDTH,
              Channel,
              Rank,
              Byte
              );
          }
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsPDelay, ReadFromCache, &GetSetValue);
          FinalDqs[Channel][Rank][Byte] = Center + (INT32) GetSetValue;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "  B%u: \t%d\t%d\t%d\t%d\t%d\n",
            Byte,
            Left,
            Right,
            lWidth,
            Center,
            FinalDqs[Channel][Rank][Byte]
            );
          //
          // Update the MarginResult struct for future tests
          // Store the new margins relative to the center
          //
          Margin    = &Outputs->MarginResult[LastRxT][Rank][Channel][Byte][0];
          Margin[0] = ABS (10 * (Left  - Center));
          Margin[1] = ABS (10 * (Right - Center));
        } // for Byte
      }
    } // for Channel
  } // for Rank

  //
  // Now program the DQS center values on populated ranks.
  // Need to do it after all ranks are trained, because we need to keep the same DQS value on all ranks
  // during the training.
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (((1 << Rank) & RankMask) == 0) {
      continue;
    }
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
            continue;
          }
          GetSetValue = (INT64) FinalDqs[Channel][Rank][Byte];
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsPDelay, WriteToCache, &GetSetValue);
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsNDelay, WriteToCache, &GetSetValue);
        }
      }
    }
  }
  MrcFlushRegisterCachedData (MrcData);

  if (Ddr4) {
    //
    // Restore the bank mapping
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      MrcGetSetBankSequence (MrcData, Channel, &BankMapping[Channel][0], 2, MRC_SET);
    } // for Channel
  }
  // Clean up after Test.
  MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRankOverrideEn, WriteToCache, &GetSetDis);
  MrcFlushRegisterCachedData (MrcData);
  Status  = ChangeMargin (MrcData, RdT, 0, 0, 1, 0, 0, 0, 0, 0, 0);
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
  MrcOutput *Outputs;
  MrcDebug  *Debug;
  UINT8     ResetPerBit;
  UINT8     LoopCount;
  MrcStatus Status;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  ResetPerBit = 1;

  LoopCount   = 10;

  // Center Read Dq/Dqs in two passes - first using RxDqsN and then RxDqsP.
  // This gives better centering than using RdT param which sweeps both strobes at the same time.

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Center using %s\n", "RxDqsN");
  Status = DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTN, ResetPerBit, LoopCount, MRC_PRINTS_ON, FALSE);
  if (Status == mrcSuccess) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Center using %s\n", "RxDqsP");
    Status = DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdTP, ResetPerBit, LoopCount, MRC_PRINTS_ON, FALSE);
  }

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
  MrcInput  *Inputs;
  MrcOutput *Outputs;
  MrcStatus Status;
  INT64     GetSetVal;
  UINT8     LoopCount;

  Outputs = &MrcData->Outputs;
  Inputs  = &MrcData->Inputs;

  LoopCount   = 10;

  // If Read Per Bit Deskew is requested to be disabled, enable it temporarily to do calibration.
  if (Inputs->RdTPbdDis) {
    GetSetVal = 0;
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxDeskewDis, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);
  }

  Status = GetPerBitDeSkewStep (
            MrcData,
            Outputs->MarginResult,
            Outputs->ValidChBitMask,
            RdT,
            LoopCount
            );

  // Disable before continuing with training
  if (Inputs->RdTPbdDis) {
    GetSetVal = 1;
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxDeskewDis, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);
  }

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
  MrcOutput *Outputs;
  UINT8     LoopCount;

  Outputs = &MrcData->Outputs;

  LoopCount   = 10;

  return DQTimeCentering1D (MrcData, Outputs->ValidChBitMask, RdV, 0, LoopCount, TRUE, FALSE);
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
              Outputs->ValidChBitMask,
              RdT,
              EnPerBit,
              EnRxDutyCycle,
              ResetPerBit,
              LoopCount,
              En2D,
              MRC_PRINTS_ON
              );
    if (!Outputs->Gear2) {
      MrcPerBitDeskew (MrcData, Outputs->MarginResult, RdT);
    }
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
              Outputs->ValidChBitMask,
              RdT,
              EnPerBit,
              EnRxDutyCycle,
              ResetPerBit,
              LoopCount,
              En2D,
              MRC_PRINTS_ON
              );
  }

  return Status;
}

/**
  Perform Read Voltage Centering in 2D.
  Note: This function currently only supports param = RdV

  @param[in,out] MrcData     - Include all MRC global data.
  @param[in,out] MarginByte  - Pointer to Marging Results data structure
  @param[in]     ChBitMask   - Channel bit mask.
  @param[in]     Param       - {0:RcvEn, 1:RdT, 2:WrT, 3: WrDqsT, 4:RdV, 5:WrV, 6:WrLevel,
                                8:WrTBit, 9:RdTBit, 10:RdVBit,
                                16:RdFan2, 17:WrFan2, 32:RdFan3, 32:WrFan3}
                                ONLY RdV is allowed in this function
  @param[in]     EnPerBit    - Option to enable per bit margining
  @param[in]     ResetPerBit - Option to Reset PerBit Deskew to middle value before byte training
  @param[in]     LoopCount   - Loop count
  @param[in]     En2D        - Option to only run center at nominal Vref point
  @param[in]     Prints      - Enable/Disable debug prints

  @retval MrcStatus - If it succeded return mrcSuccess
**/
MrcStatus
ReadVoltageCentering2D (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                ChBitMask,
  IN     UINT8                Param,
  IN     UINT8                EnPerBit,
  IN     UINT8                ResetPerBit,
  IN     UINT8                LoopCount,
  IN     UINT8                En2D,
  IN     BOOLEAN              Prints
  )
{
  static const INT8                       TimePoints[] = { 0, -8, 8 };
  static const UINT8                      EHWeights[sizeof (TimePoints)] = { 1, 1, 1 };
  const MrcInput                          *Inputs;
  MrcDebug                                *Debug;
  const MRC_FUNCTION                      *MrcCall;
  MrcOutput                               *Outputs;
  MrcChannelOut                           *ChannelOut;
  MrcStatus                               Status;
  UINT8                                   ResultType;
  UINT8                                   Channel;
  UINT8                                   Byte;
  UINT8                                   Rank;
  UINT8                                   RankResult;
  UINT8                                   RankMask;
  UINT8                                   bit;
  UINT8                                   lcloop;
  UINT8                                   tim;
  UINT8                                   paramB;
  UINT8                                   paramT;
  UINT8                                   BMap[MAX_SDRAM_IN_DIMM];
  INT8                                    SumEH;
  INT8                                    SumEHSign;
  UINT8                                   MaxTscale;
  UINT8                                   SaveLC;
  UINT16                                  mode;
  INT32                                   center[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   value0[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  UINT32                                  BERStats[4];
  UINT32                                  TimScale[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   CenterSumByte[MAX_CHANNEL][MAX_SDRAM_IN_DIMM];
  INT32                                   CenterSumBit[MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  UINT32                                  marginbit[MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  UINT32                                  EyeShape[3][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  INT64                                   GetSetVal;
  UINT8                                   MaxVrefOffset;
  INT64                                   RxVocMax;
  INT64                                   RxVocMiddle;
  MrcDebugMsgLevel                        DebugLevel;

  Inputs    = &MrcData->Inputs;
  MrcCall   = Inputs->Call.Func;
  Outputs   = &MrcData->Outputs;
  Debug     = &Outputs->Debug;
  DebugLevel    = Prints ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  Status    = mrcSuccess;
  SumEH     = 0;
  MaxTscale = 12;
  RankResult = 0;
  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  for (lcloop = 0; lcloop < (sizeof (BMap) / sizeof (BMap[0])); lcloop++) {
    BMap[lcloop] = lcloop;
  }
  if (Param == RdV) {
    paramB = RdVBit;
    paramT = RdT;
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Error Handler: Unknown Margin Parameter\n");
    Status = mrcReadVoltage2DError;
    return Status;
  }

  SetupIOTestBasicVA (MrcData, ChBitMask, LoopCount, ABGSOE, 0, 0, 8);

  // Calculate SumEH for use in weighting equations
  for (tim = 0; tim < sizeof (TimePoints); tim++) {
    SumEH += EHWeights[tim];
    // Loop once at nominal Vref point
    if (En2D == 0) {
      tim = sizeof (TimePoints);
    }
  }
  // SumEH is used as divisor, make sure is never 0
  if (SumEH == 0) {
    SumEH = 1;
  }

  // DDR4 uses N-path, so the range is [0..15]
  // LP4 (P-Path) range is [0..31]
  MrcGetSetLimits (MrcData, RxVoc, NULL, &RxVocMax, NULL);
  RxVocMiddle = ((INT32) RxVocMax + 1) / 2;

  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (EnPerBit == 1) {
      // For Per bit run centering per Rank to get
      RankMask  = 1 << Rank;
    } else {
      RankMask = 0xF;
    }
    // Reset PerBit Deskew to middle value before Byte training
    // Amplifier voltage offset for bit[x] of the DQ Byte.
    if (ResetPerBit == 1) {
      MrcGetSetDdrIoGroupSocket0 (MrcData, MAX_CHANNEL, Rank, MAX_SDRAM_IN_DIMM, MAX_BITS, RxVoc, WriteToCache, &RxVocMiddle);
      MrcFlushRegisterCachedData (MrcData);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &Outputs->Controller[0].Channel[Channel];
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          for (bit = 0; bit < MAX_BITS; bit++) {
            ChannelOut->RxDqVrefPb[Rank][Byte][bit].Center = (UINT8) RxVocMiddle;
          }
        }
      }
    }
    // Select rank for REUT test
    ChBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChBitMask |= SelectReutRanks (MrcData, Channel, RankMask, FALSE, 0);
    }
    // Continue with next rank if this rank is not present on any channel
    if (ChBitMask == 0) {
      continue;
    }
    // ####################################################
    // ################  Initialize EW/EH variables  ######
    // ####################################################
    Status      = GetMarginByte (MrcData, Outputs->MarginResult, paramT, 0, 0xF);
    ResultType  = GetMarginResultType (paramT);

#ifdef MRC_DEBUG_PRINT
    if (En2D) {
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n### Measure Eye Height, per BYTE, at %s RankMask = 0x%X\n", "ALL (2D) Timing Points", RankMask);
    } else {
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n### Measure Eye Height, per BYTE, at %s RankMask = 0x%X\n", "NOMINAL Timing", RankMask);
    }

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }

      MRC_DEBUG_MSG (Debug, DebugLevel, "Channel %d", Channel);
      if (Channel == 0) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG (Debug, DebugLevel, "        ");
        }
      }
    }

    MRC_DEBUG_MSG (Debug, DebugLevel, "\nByte    ");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }

      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MRC_DEBUG_MSG (Debug, DebugLevel, "%d       ", Byte);
      }
    }
    MRC_DEBUG_MSG (Debug, DebugLevel, "\nTScale\t");
#endif // MRC_DEBUG_PRINT

    // Update TimScale to have the appropriate eye width (read from last saved parameters)
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }

      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        if (En2D > 0) {
          TimScale[Channel][Byte] = (MarginByte[ResultType][0][Channel][Byte][0] + MarginByte[ResultType][0][Channel][Byte][1]) / 20;
        } else {
          TimScale[Channel][Byte] = 1;
        }
        // It is possible sumT is 0.
        if ((TimScale[Channel][Byte] == 0) || (TimScale[Channel][Byte] > MaxTscale)) {
          TimScale[Channel][Byte] = MaxTscale;
        }

        MRC_DEBUG_MSG (Debug, DebugLevel, "%d\t", TimScale[Channel][Byte]);
      }
    }

    // Param is RdV
    Status      = GetMarginByte (MrcData, Outputs->MarginResult, Param, RankResult, 0xF);
    ResultType  = GetMarginResultType (Param);

    // ####################################################
    // ######   Measure Eye Height at all Timing Points  ##
    // ####################################################

    // Loop through all the Time Points to Test
    for (tim = 0; tim < sizeof (TimePoints); tim++) {
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n\nRdTime\t");

      // Setup Timing Offset for this point
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(ChBitMask & (MRC_BIT0 << Channel))) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          value0[Channel][Byte] = (INT32) (TimePoints[tim] * TimScale[Channel][Byte]) / MaxTscale;
          Status = ChangeMargin (MrcData, paramT, value0[Channel][Byte], 0, 0, Channel, Rank, Byte, 0, 1, 0);
          MRC_DEBUG_MSG (Debug, DebugLevel, "%d\t", value0[Channel][Byte]);
        }
      }
      // Run Margin Test
      mode = 0;
      MaxVrefOffset = GetMaxPossibleVrefOffset (MrcData, Param);
      Status = MrcGetBERMarginByte (
                MrcData,
                Outputs->MarginResult,
                ChBitMask,
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
      MRC_DEBUG_MSG (Debug, DebugLevel, "\nLo-Hi\t");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(ChBitMask & (MRC_BIT0 << Channel))) {
          continue;
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MRC_DEBUG_MSG (
            Debug,
            DebugLevel,
            "%d %d\t",
            MarginByte[ResultType][RankResult][Channel][Byte][0],
            MarginByte[ResultType][RankResult][Channel][Byte][1]
            );
        }
      }

      MRC_DEBUG_MSG (Debug, DebugLevel, "\nCenter\t");
#endif // MRC_DEBUG_PRINT

      // Store Results
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            center[Channel][RankResult][Byte] = (INT32)(MarginByte[ResultType][RankResult][Channel][Byte][1] -
                                                        MarginByte[ResultType][RankResult][Channel][Byte][0]);
            if (tim == 0) {
              CenterSumByte[Channel][Byte] = 0;
            }
            // Calculate weight for this point
            CenterSumByte[Channel][Byte] += EHWeights[tim] * center[Channel][RankResult][Byte];
            MRC_DEBUG_MSG (Debug, DebugLevel, "%d\t", center[Channel][RankResult][Byte] / 20);

            // Record edges for use in per bit margining
            EyeShape[tim][Channel][Byte][0] = MarginByte[ResultType][RankResult][Channel][Byte][0];
            EyeShape[tim][Channel][Byte][1] = MarginByte[ResultType][RankResult][Channel][Byte][1];
          }
        }
      }
      // Loop once at nominal Vref point
      if (En2D == 0) {
        tim = sizeof (TimePoints);
      }
    } // for tim

    MRC_DEBUG_MSG (Debug, DebugLevel, "\n\nWtdCntr\t");
    // ####################################################
    // ###########   Center Results per Byte   ############
    // ####################################################
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];

      // Calculate CenterPoint.  Round to Nearest Int
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        SumEHSign                     = (CenterSumByte[Channel][Byte] < 0) ? (-1) : 1;

        CenterSumByte[Channel][Byte]  = (CenterSumByte[Channel][Byte] + 10 * (SumEHSign * SumEH)) / (20 * SumEH);
        MRC_DEBUG_MSG(Debug, DebugLevel,"%d\t", CenterSumByte[Channel][Byte] / 2);

        // Apply new centerpoint
        // step size for RxVref is VDD/192 AND for RxVrefOffset is VDD/384
        GetSetVal = CenterSumByte[Channel][Byte] / 2;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxVref, WriteOffsetCached, &GetSetVal);

        // Update the Eye Edges
        for (tim = 0; tim < sizeof (TimePoints); tim++) {
          EyeShape[tim][Channel][Byte][0] = (INT32) EyeShape[tim][Channel][Byte][0] + (10 * CenterSumByte[Channel][Byte]);
          EyeShape[tim][Channel][Byte][1] = (INT32) EyeShape[tim][Channel][Byte][1] - (10 * CenterSumByte[Channel][Byte]);

          // Loop once at nominal Vref point
          if (En2D == 0) {
            tim = sizeof (TimePoints);
          }
        }
        //
        // Update MrcData for future tests (MarginResult points back to MrcData)
        // EyeShape for Vref 0 is assumed to have the best shape for future tests.
        //
        MarginByte[ResultType][RankResult][Channel][Byte][0] = EyeShape[0][Channel][Byte][0];
        MarginByte[ResultType][RankResult][Channel][Byte][1] = EyeShape[0][Channel][Byte][1];
      } // for Byte
    } // for Channel

#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (Debug, DebugLevel, "\nRdVref\t");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (MRC_BIT0 << Channel))) {
        continue;
      }
      ChannelOut = &Outputs->Controller[0].Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxVref, ReadFromCache, &GetSetVal);
        MRC_DEBUG_MSG (Debug, DebugLevel, "%d\t", (INT8) GetSetVal);
      }
    }
#endif // MRC_DEBUG_PRINT

    // ####################################################
    // ############    Measure Eye Height Per BIT   ########
    // ####################################################
    if (EnPerBit) {
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n### Measure Eye Height, per BIT, at %s\n", En2D ? "ALL (2D) Timing Points" : "NOMINAL Timing\n");

      // Stop on all lane fail
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
  #ifdef MRC_DEBUG_PRINT
          MRC_DEBUG_MSG (Debug, DebugLevel, "Channel      %d", Channel);
          if (Channel == 0) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              MRC_DEBUG_MSG (Debug, DebugLevel, "\t\t\t\t\t\t");
            }
          }
  #endif // MRC_DEBUG_PRINT
          // We enable error checking on all Cachelines and UI's of the Cacheline.
          //MrcSetChunkAndClErrMsk (MrcData, Channel, 0xFF, 0xFFFF);
          MrcSetupTestErrCtl (MrcData, Channel, ALSOE, 1);
        }
      }

  #ifdef MRC_DEBUG_PRINT
      MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (ChBitMask & (MRC_BIT0 << Channel)) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            MRC_DEBUG_MSG (Debug, DebugLevel, "             Byte % 24d ", Byte);
          }
        }
      }

      MRC_DEBUG_MSG (Debug, DebugLevel, "\n");
  #endif // MRC_DEBUG_PRINT

      // Loop through all the Vref Points to Test
      SaveLC = Outputs->DQPatLC;
      for (tim = 0; tim < sizeof (TimePoints); tim++) {
        // Setup Timing Offset for this point
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              value0[Channel][Byte] = (INT32) (TimePoints[tim] * TimScale[Channel][Byte]) / MaxTscale;
              Status = ChangeMargin (MrcData, paramT, value0[Channel][Byte], 0, 0, Channel, Rank, Byte, 0, 1, 0);

              // Amplifier voltage offset for bit[x] of the DQ Byte.
              for (bit = 0; bit < MAX_BITS; bit++) {
                marginbit[Channel][Byte][bit][0] = marginbit[Channel][Byte][bit][1] = (UINT32) RxVocMiddle;
              }
            }
          }
        }

        MRC_DEBUG_MSG (Debug, DebugLevel, "Rank %d \n", Rank);
        //
        // Run Margin Test
        // Loop through 2 times.  Once at low loop count and Once at high loopcount
        // Improves runtime
        // @TODO: Need 2 loops below if not using BASICVA
        //
        for (lcloop = 0; lcloop < 1; lcloop++) {
          Outputs->DQPatLC  = (lcloop == 0) ? 1 : SaveLC;
          mode              = 0;
          Status            = MrcGetMarginBit (MrcData, ChBitMask, Rank, marginbit, EyeShape[tim], paramB, mode, (UINT8) RxVocMax, MRC_PRINTS_ON);
        }
        // Store Results
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          if (ChBitMask & (MRC_BIT0 << Channel)) {
            for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
              for (bit = 0; bit < MAX_BITS; bit++) {
                center[Channel][RankResult][Byte] = ((marginbit[Channel][Byte][bit][1] - (UINT32) RxVocMiddle) - ((UINT32) RxVocMiddle - marginbit[Channel][Byte][bit][0]));
                if (tim == 0) {
                  CenterSumBit[Channel][RankResult][Byte][bit] = 0;
                }
                // Calculate weight for this point
                CenterSumBit[Channel][RankResult][Byte][bit] += EHWeights[tim] * center[Channel][RankResult][Byte];
              }
            }
          }
        }

        // Loop once at nominal Vref point
        if (En2D == 0) {
          tim = sizeof (TimePoints);
        }
      } // for tim
      // ####################################################
      // ############   Center Result Per BIT  ##############
      // ####################################################
      MRC_DEBUG_MSG (Debug, DebugLevel, "\nWgted Center ");
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!(ChBitMask & (MRC_BIT0 << Channel))) {
          continue;
        }
        ChannelOut = &Outputs->Controller[0].Channel[Channel];

        // Calculate and apply CenterPoint.  Round to Nearest Int
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          for (bit = 0; bit < MAX_BITS; bit++) {
            SumEHSign = (CenterSumBit[Channel][Rank][Byte][bit] < 0) ? (-1) : 1;
            CenterSumBit[Channel][Rank][Byte][bit]  = (CenterSumBit[Channel][Rank][Byte][bit] + (SumEHSign * SumEH)) / (2 * SumEH);

            // Centerpoint needs to be added to starting DqPb value
            CenterSumBit[Channel][Rank][Byte][bit] += (INT32) ChannelOut->RxDqVrefPb[Rank][Byte][bit].Center;

            // Check for saturation
            if (CenterSumBit[Channel][Rank][Byte][bit] > RxVocMax) {
              CenterSumBit[Channel][Rank][Byte][bit] = (INT32) RxVocMax;
            } else if (CenterSumBit[Channel][Rank][Byte][bit] < 0) {
              CenterSumBit[Channel][Rank][Byte][bit] = 0;
            }

            GetSetVal = CenterSumBit[Channel][Rank][Byte][bit];
            MRC_DEBUG_MSG (Debug, DebugLevel, "%x   ", (UINT32) GetSetVal);

            // Apply and propagate new centerpoint
            MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, Byte, bit, RxVoc, WriteToCache, &GetSetVal);
            ChannelOut->RxDqVrefPb[Rank][Byte][bit].Center = (UINT8) GetSetVal;
          } // for bit
          MRC_DEBUG_MSG (Debug, DebugLevel, "           ");
        } // for Byte
      } // for Channel
      MrcFlushRegisterCachedData (MrcData);
    } // if EnPerBit

    if (EnPerBit == 0) { // We use RankMask = 0x0F in this case
      break;
    }
  } // for Rank

/// @attention - This is used to determine if the PerBit routines are correct.  Left for sanity.
/*
#ifdef MRC_DEBUG_PRINT
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (ChBitMask & (MRC_BIT0 << Channel)) {
        ChannelOut = &Outputs->Controller[0].Channel[Channel];
        for (Rank = 0; Rank < MaxRank; Rank++) {
          for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
            Offset = DDRDATA0CH0_CR_RXCONTROL2RANK0_REG +
              ((DDRDATA0CH1_CR_RXCONTROL2RANK0_REG - DDRDATA0CH0_CR_RXCONTROL2RANK0_REG) * Channel) +
              ((DDRDATA1CH0_CR_RXCONTROL2RANK0_REG - DDRDATA0CH0_CR_RXCONTROL2RANK0_REG) * Byte) +
              (DDRDATA0CH0_CR_RXCONTROL2RANK1_REG - DDRDATA0CH0_CR_RXCONTROL2RANK0_REG) * Rank;
            MRC_DEBUG_MSG (Debug, DebugLevel, "\nRdVref = % 3d   RdVBit = 0x%08X", (INT8) ChannelOut->RxVref[Byte],
              MrcReadCR (MrcData, Offset));
          }
        }
      }
    }
#endif // MRC_DEBUG_PRINT
*/
  MRC_DEBUG_MSG (Debug, DebugLevel, "\n");

  // Clean up after test
  Status = ChangeMargin (MrcData, paramT, 0, 0, 1, 0, 0, 0, 0, 1, 0);

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
  UINT8     Channel;
  BOOLEAN   Ddr4;
  BOOLEAN   Any2Dpc;

  Outputs = &MrcData->Outputs;
  Ddr4    = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Any2Dpc = FALSE;
  Status  = mrcSuccess;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      if (Outputs->Controller[0].Channel[Channel].DimmCount == 2) {
        Any2Dpc = TRUE;
        break;
      }
    }
  }

  EnPerBit    = 0;
  ResetPerBit = 0;
  En2D        = 0;

  LoopCount1  = 10;  // Lower loopcount for the first 2D pass on DDR4 2DPC
  LoopCount2  = 15;

  if (EnPerBit) {
    Status = ReadVoltageCentering2D (
              MrcData,
              Outputs->MarginResult,
              Outputs->ValidChBitMask,
              RdV,
              EnPerBit,
              ResetPerBit,
              LoopCount2,
              En2D,
              MRC_PRINTS_ON
              );
  }
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
        En2D,
        MRC_PRINTS_ON
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
        En2D,
        MRC_PRINTS_ON
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
    LowVref = 20; // We're currently seeing the RxV eye shifted towards VOH.  No need to go to 0.
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
  Points2DMax = MIN (Points2DMax, (INT16) Max);

    LoopCount   = 10;
    Status = EarlyLinearCentering2D (
              MrcData,
              Outputs->ValidChBitMask,
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

/**
  Perform DQ DFE Training.  To enable DFE and set the equalization strength by performing 3 phases of training

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if succeeded
**/
MrcStatus
MrcDqDfeTraining (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput      *Outputs;
  INT64           GetSetValue;
  MrcDebug       *Debug;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;

  if (MrcData->Inputs.IclA0) {
    // DFE is only supported in ICL B0 and on
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "DFE is disabled on A-step\n");
    return mrcSuccess;
  }

  // Enable DFE
  // DdrCrDataDfeControl0Rank*.DqDfeEn enables the feature per rank
  GetSetValue = 1;
  MrcGetSetDdrIoGroupStrobe (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, DqDfeEnable, WriteNoCache , &GetSetValue);

  //Set all the DqDfeCoeffRank* fields to 0x3 to set strongest equalization strength
  GetSetValue = 0x3;
  MrcGetSetDdrIoGroupStrobe (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, DqDfeCoeff, WriteNoCache , &GetSetValue);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Start DQ DFE Phase 1\n");
  MrcDqDfeTraining1 (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Start DQ DFE Phase 2\n");
  MrcDqDfeTraining2 (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Start DQ DFE Phase 3\n");
  MrcDqDfeTraining3 (MrcData);

  return mrcSuccess;
}

/**
  Perform Phase 1 of DQ DFE Training
  Find the best margin per byte for DFE Delay Mode & top3 bits of DlyBit
             DfeDlyModeRank* values (0..3),
             DqDfeDlyBit* field for all bits, ranks and bytes

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if succeeded
**/
MrcStatus
MrcDqDfeTraining1 (
  IN OUT MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[] = { RdV };
  static const UINT8  Scale[]    = { 1, 0, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptDqDfeMode };
  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;

  Start = OptParamLimitValue (MrcData, OptDqDfeMode, 0);
  Stop  = OptParamLimitValue (MrcData, OptDqDfeMode, 1);

  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xf,
    OptParam,
    ARRAY_COUNT(OptParam),
    FullGrid,
    TestList,
    ARRAY_COUNT(TestList),
    Scale,
    NULL,
    &Start,  // Start
    &Stop,  // Stop
    14,     // LoopCount
    1,      // Repeats
    0,      // NoPrint
    0,      // SkipOdtUpdate
    0,      // RdRd2Test
    0,      // GuardBand
    BasicVA // PatternType
    );
  return mrcSuccess;
}

/**
  Perform Phase 2 of DQ DFE Training
  Find the best margin per bit by toggling 6 bits DqDfeDlyBit (both coarse + fine)
             DqDfeDlyBit* field for all bits, ranks and bytes

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if succeeded
**/
MrcStatus
MrcDqDfeTraining2 (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput              *Inputs;
  const MRC_FUNCTION          *MrcCall;
  MrcOutput                   *Outputs;
  MrcChannelOut               *ChannelOut;
  MrcControllerOut            *ControllerOut;
  MrcStatus                   Status;
  MrcStatus                   CurStatus;
  UINT8                       Channel;
  UINT8                       Byte;
  UINT8                       paramV;
  INT8                        Start;
  INT8                        Stop;
  UINT8                       Step;
  INT8                        DqDfeVal;
  UINT8                       DqDfeIdx;
  UINT8                       LoopCount;
  UINT8                       ResultType;
  UINT8                       RankMask;
  UINT8                       mode;
  UINT8                       Rank;
  UINT8                       Bit;
  UINT8                       MaxMargin;
  UINT32                      MarginBitSummary[8][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS];
  UINT32                      marginbit[MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_BITS][MAX_EDGES];
  UINT32                      MarginByteArray[8][MAX_RANK_IN_CHANNEL][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES];
  UINT32                      BestMargin;
  INT32                       DqDfeBestValue;
  INT64                       GetSetVal;
  UINT8                       BMap[9];   // Need by GetBERMarginByte
  UINT32                      BERStats[4];
  UINT8                       ChBitMask;

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  ChBitMask     = Outputs->ValidChBitMask;
  RankMask      = Outputs->ValidRankMask;
  Status        = mrcSuccess;

  LoopCount = 10;

  paramV = RdV;
  MaxMargin = GetMaxPossibleVrefOffset (MrcData, paramV);

  MrcCall->MrcSetMem ((UINT8 *) BERStats, sizeof (BERStats), 0);
  MrcCall->MrcSetMemDword ((UINT32 *) marginbit, sizeof (marginbit) / sizeof (UINT32), MaxMargin);  // Initialize per-bit margins
  MrcCall->MrcSetMemDword ((UINT32 *) MarginBitSummary, sizeof (MarginBitSummary) / sizeof (UINT32), 0);
  MrcCall->MrcSetMemDword ((UINT32 *) MarginByteArray, sizeof (MarginByteArray) / sizeof (UINT32), MAX_POSSIBLE_TIME);

  for (Byte = 0; Byte < ARRAY_COUNT(BMap); Byte++) {
    BMap[Byte] = Byte;
  }

  // For all other training params use regular VA pattern
  SetupIOTestBasicVA (MrcData, ChBitMask, LoopCount, NSOE, 0, 0, 8); // Set test to all channels.

  Start = OptParamLimitValue (MrcData, OptDqDfeDly, 0);
  Stop  = OptParamLimitValue (MrcData, OptDqDfeDly, 1);
  Step  = 8; // Search in steps of 8


  // #############################################
  // ######    Measure RdV margin per Bit   ######
  // #############################################
  // @todo: Stop on all lane fail
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (ChBitMask & (1 << Channel)) {
      // We enable error checking on all Cachelines and UI's of the Cacheline.
      MrcSetupTestErrCtl (MrcData, Channel, NSOE, 1);
    } else {
      continue;
    }

    ChannelOut = &ControllerOut->Channel[Channel];
    SelectReutRanks (MrcData, Channel, ChannelOut->ValidRankBitMask, FALSE, 0);
  }

  // Get margin per Bit
  Status = GetMarginByte (MrcData, Outputs->MarginResult, paramV, 0, 0xF);
  ResultType = GetMarginResultType (paramV);

  // Search DqDfeDelayMode values
  for (DqDfeVal = Start, DqDfeIdx = 0; DqDfeVal <= Stop; DqDfeVal += Step, DqDfeIdx++) {
    GetSetVal = DqDfeVal;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (1 << Channel))) {
        continue;
      }

      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (((1 << Rank) & RankMask) == 0) {
          continue;  // No such rank
        }
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          // Init results per Byte
          MarginByteArray[DqDfeIdx][Rank][Channel][Byte][0] = Outputs->MarginResult[ResultType][Rank][Channel][Byte][0];
          MarginByteArray[DqDfeIdx][Rank][Channel][Byte][1] = Outputs->MarginResult[ResultType][Rank][Channel][Byte][1];
        }
      } // end of Rank
    } // end of Channel
    MrcGetSetDdrIoGroupSocket0 (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, DqDfeDelay, WriteToCache, &GetSetVal);
    MrcFlushRegisterCachedData (MrcData);

    // Run the test
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!(ChBitMask & (1 << Channel))) {
        continue;
      }
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (((1 << Rank) & RankMask) == 0) {
          continue;  // No such rank
        }

        mode = 0; // get margin for all ranks
        Status = MrcGetMarginBit (MrcData, ChBitMask, Rank, marginbit[Rank], MarginByteArray[DqDfeIdx][Rank], paramV, mode, MaxMargin, MRC_PRINTS_OFF);
        if (Status != mrcSuccess) {
          return Status;
        }
        // Store results
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          for (Bit = 0; Bit < MAX_BITS; Bit++) {
            MarginBitSummary[DqDfeIdx][Rank][Channel][Byte][Bit] = marginbit[Rank][Channel][Byte][Bit][0] + marginbit[Rank][Channel][Byte][Bit][1];
          } // end of Bit
        } // end of Byte
      } // end of Rank
    } // end of Channel
  } // end of DqDfeVal

  // #########################################################
  // ######     Get DqDfeDelay optimal value per Bit    ######
  // #########################################################
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!(ChBitMask & (1 << Channel))) {
      continue;
    }
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (((1 << Rank) & RankMask) == 0) {
        continue;  // No such rank
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        for (Bit = 0; Bit < MAX_BITS; Bit++) {
          DqDfeBestValue = 0;  // default value
          BestMargin = 0;
          for (DqDfeIdx = 0; DqDfeIdx <= (Stop + ABS (Start)) / Step; DqDfeIdx++) {
            if (BestMargin <= MarginBitSummary[DqDfeIdx][Rank][Channel][Byte][Bit]) {
              BestMargin = MarginBitSummary[DqDfeIdx][Rank][Channel][Byte][Bit];
              if (BestMargin > MarginBitSummary[0][Rank][Channel][Byte][Bit]) {  // Compare to default value
                DqDfeBestValue = Start + DqDfeIdx * Step;
              }
            }
          } // DqDfeDelayMode Loop
          GetSetVal = DqDfeBestValue;
          // @todo Print a nice table instead of using GetSet PrintValue
          CurStatus = MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, Byte, Bit, DqDfeDelay, WriteToCache | PrintValue, &GetSetVal);
          if (Status == mrcSuccess) {
            Status = CurStatus;
          }
        } // Bit loop
      } // Byte loop
    } // Rank loop
  } // Channel loop

  MrcFlushRegisterCachedData(MrcData);
  return Status;
}


/**
  Perform Phase 3 of DQ DFE Training
  Find the best margin per byte by toggling 2bits DqDfeCoeffRank* registers.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if succeeded
**/
MrcStatus
MrcDqDfeTraining3 (
  IN OUT MrcParameters *const MrcData
  )
{
  static const UINT8  TestList[] = { RdV };
  static const UINT8  Scale[]    = { 1, 0, 0, 0, 0 };
  static const UINT8  OptParam[] = { OptDqDfeCoeff };
  OptOffsetChByte     BestOff;
  INT8                Start;
  INT8                Stop;

  Start = OptParamLimitValue (MrcData, OptDqDfeCoeff, 0);
  Stop  = OptParamLimitValue (MrcData, OptDqDfeCoeff, 1);


  TrainDDROptParam (
    MrcData,
    &BestOff,
    0x3,
    0xf,
    OptParam,
    ARRAY_COUNT (OptParam),
    FullGrid,
    TestList,
    ARRAY_COUNT (TestList),
    Scale,
    NULL,
    &Start,  // Start
    &Stop,  // Stop
    14,     // LoopCount
    1,      // Repeats
    0,      // NoPrint
    0,      // SkipOdtUpdate
    0,      // RdRd2Test
    0,      // GuardBand
    BasicVA // PatternType
    );
  return mrcSuccess;
}

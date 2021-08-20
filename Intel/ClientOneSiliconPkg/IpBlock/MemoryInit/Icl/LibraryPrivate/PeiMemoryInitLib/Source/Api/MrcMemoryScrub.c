/** @file
  This file contains the memory scrubbing and alias checking functions.

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

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcMemoryScrub.h"
#include "MrcCpgcApi.h"
#include "Cpgc20TestCtl.h"
#include "MrcSpdProcessing.h"
#include "MrcMcConfiguration.h"


/**
  Zero out all of the memory.
  This function is used in the following cases:
   - ECC is enabled (to initialize ECC logic)
   - TXT library is asking to scrub the memory (instead of SCLEAN ACM)
   - Platform code is asking to scrub the memory due to MOR bit being set (Memory Override Request)

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if the clean succeeded, otherwise an error status.
**/
MrcStatus
MrcEccClean (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  MrcDebug              *Debug;
  const MRC_FUNCTION    *MrcCall;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcStatus             Status;
  INT64                 GetSetVal;
  INT64                 Ddr4OneDpc;
  UINT32                Offset;
  UINT32                tRFC;
  UINT8                 Rank;
  UINT8                 Channel;
  UINT8                 ChBitMask;
  UINT8                 RankFeatureEnable;
  UINT8                 ChError;
  BOOLEAN               EccEnabled;
  BOOLEAN               Ibecc;
  BOOLEAN               TxtClean;
  BOOLEAN               CleanMemory;
  BOOLEAN               WarmReset;
  BOOLEAN               Lpddr4;
  CH0_CR_SC_PCIT_STRUCT ScPcit;
  CH0_CR_SC_PCIT_STRUCT ScPcitSave[MAX_CHANNEL];
  CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT Lp4DqsOsclParams;
  CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT Lp4DqsOsclParamsOrg[MAX_CHANNEL];
  MCMISCS_DELTADQSCOMMON0_STRUCT          DeltaDqsCommon;
  MCMISCS_DELTADQSCOMMON0_STRUCT          DeltaDqsCommonOrg;

#ifdef MRC_DEBUG_PRINT
  static const char *SourceStr[4] = { "ECC", "CleanMemory", "TXT", "IBECC" };
#endif

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;
  EccEnabled    = (Outputs->EccSupport == TRUE);
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  tRFC          = 0;
  TxtClean      = Inputs->TxtClean;
  CleanMemory   = Inputs->CleanMemory;
  WarmReset     = (Inputs->BootMode == bmWarm);
  ChError       = 0;

  Ibecc = (Inputs->Ibecc == TRUE) && ((Inputs->IbeccOperationMode == 0) || (Inputs->IbeccOperationMode == 2));

  if (!(((Ibecc || EccEnabled || CleanMemory) && (!WarmReset)) || TxtClean)) {
    // Memory clean is not needed if none of the (Ibecc || EccEnabled || CleanMemory || TxtClean) bit is set
    // In WarmRest, only TxtClean needs to preform this EccClean function, not required for EccEnabled or CleanMemory
    return mrcSuccess;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Scrubbing Memory due to %s\n", EccEnabled ? SourceStr[0] : (Ibecc ? SourceStr[3] : (TxtClean ? SourceStr[2] : SourceStr[1])));

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    tRFC = ControllerOut->Channel[Channel].Timing[Inputs->MemoryProfile].tRFC;
    if (Lpddr4) {
      // Disable the DQS Osillator for LP4.
      Offset = OFFSET_CALC_CH (CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, Channel);
      Lp4DqsOsclParams.Data                 = MrcReadCR (MrcData, Offset);
      Lp4DqsOsclParamsOrg[Channel].Data     = Lp4DqsOsclParams.Data;
      Lp4DqsOsclParams.Bits.DQSOSCL_PERIOD  = 0;
      Lp4DqsOsclParams.Bits.DIS_SRX_DQSOSCL = 1;
      MrcWriteCR (MrcData, Offset, Lp4DqsOsclParams.Data);
    }

    // Change PCIT to 0xFF
    Offset = OFFSET_CALC_CH (CH0_CR_SC_PCIT_REG, CH1_CR_SC_PCIT_REG, Channel);
    ScPcit.Data = MrcReadCR (MrcData, Offset);
    ScPcitSave[Channel] = ScPcit;
    ScPcit.Bits.PCIT = 0xFF;
    MrcWriteCR (MrcData, Offset, ScPcit.Data);
  }

  DeltaDqsCommonOrg.Data = 0;
  if (Lpddr4) {
   // Disable DqDqs Retraining feature
    DeltaDqsCommon.Data = MrcReadCR (MrcData, MCMISCS_DELTADQSCOMMON0_REG);
    DeltaDqsCommonOrg.Data = DeltaDqsCommon.Data;
    if (DeltaDqsCommonOrg.Bits.Lp4DeltaDQSTrainMode == 1) {
      DeltaDqsCommon.Bits.Lp4DeltaDQSTrainMode = 0;
      MrcWriteCR (MrcData, MCMISCS_DELTADQSCOMMON0_REG, DeltaDqsCommon.Data);
    }
  }

  // Enable refreshes on MC before we start ECC scrubbing.
  // Refresh must be kept enabled from this point on, otherwise we might loose the ECC initialization.
  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableRefresh, WriteNoCache | PrintValue, &GetSetVal);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    //Enable CKE for all ranks for CPGC tests in memory scrubbing
    GetSetVal = ChannelOut->ValidCkeBitMask;
    if (!Lpddr4) {
      // Adjust CKE mask if ddr4_1dpc is enabled on this channel
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccDdr4OneDpc, ReadFromCache, &Ddr4OneDpc);
      if (Ddr4OneDpc != 0) {
        GetSetVal = 9;        // '1001' - MC is using ranks 0 and 3 when ddr4_1dpc is enabled
      }
    }
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocCkeOn, WriteNoCache | PrintValue, &GetSetVal);
  }

  // Go to CPCG mode
  MrcSetNormalMode (MrcData, FALSE);

  // Scrub per rank, on both channels in parallel
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
    if (((1 << Rank) & Outputs->ValidRankMask) == 0) {
      continue;
    }
    // Determine the Active Channels
    ChBitMask = 0;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      RankFeatureEnable = 0x02;  // Enable Refresh during CPGC test
      ChBitMask |= SelectReutRanks (MrcData, Channel, 1 << Rank, FALSE, RankFeatureEnable);
    }

    SetupIOTestScrub (MrcData, ChBitMask);

    // Update the Bank/Row/Col sizes per current rank population
    Cpgc20AddressSetupScrub (MrcData, Rank);

    // Run the test on both channels, don't check for errors - this is WR only test
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Scrubbing Rank%d: ChBitMask = 0x%X\n", Rank, ChBitMask);
    RunIOTest (MrcData, ChBitMask, Outputs->DQPat, 1, 0);

    // Wait for MC to drain - CPGC test done indication comes earlier that all the WR's come out
    MrcWait (MrcData, ((Outputs->tCKps * 64 * Outputs->BurstLength) / 1000) * MRC_TIMER_1NS);
    MrcWait (MrcData, ((Outputs->tCKps * tRFC) / 1000) * MRC_TIMER_1NS);
  } // for Rank

  if (TxtClean) {
    // Perform Memory Read Test to Check Zeros per rank, on both channels in parallel
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (((1 << Rank) & Outputs->ValidRankMask) == 0) {
        continue;
      }
      // Determine the Active Channels
      ChBitMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        RankFeatureEnable = 0x02;  // Enable Refresh during CPGC test
        ChBitMask |= SelectReutRanks (MrcData, Channel, 1 << Rank, FALSE, RankFeatureEnable);
      }

      SetupIOTestCpgcRead (MrcData, ChBitMask, 4, NSOE, 0x0);  //RdDataPtn = 0x00000000

      // Update the Bank/Row/Col sizes per current rank population
      Cpgc20AddressSetupScrub (MrcData, Rank);

      // Run the test on both channels, to check if it is all zeros
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Checking Zeros on Rank%d: ChBitMask = 0x%X\n", Rank, ChBitMask);
      ChError |= RunIOTest (MrcData, ChBitMask, Outputs->DQPat, 1, 0);

    } // for Rank
  } // for TxtClean

  if (Lpddr4 && (DeltaDqsCommonOrg.Bits.Lp4DeltaDQSTrainMode == 1)) {
    // Restore DqDqs Retraining value
    MrcWriteCR (MrcData, MCMISCS_DELTADQSCOMMON0_REG, DeltaDqsCommonOrg.Data);
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Restore PCIT value
      Offset = OFFSET_CALC_CH (CH0_CR_SC_PCIT_REG, CH1_CR_SC_PCIT_REG, Channel);
      MrcWriteCR (MrcData, Offset, ScPcitSave[Channel].Data);

      if (Lpddr4) {
        // Restore the DQS Oscillator value for LP4.
        Offset = OFFSET_CALC_CH (CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, Channel);
        MrcWriteCR (MrcData, Offset, Lp4DqsOsclParamsOrg[Channel].Data);
      }
    }
  }

  // Go to Normal mode
  MrcSetNormalMode (MrcData, TRUE);

// Check the scrubbing result
  if (ChError != 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%s: Memory is not Clean after Scrubbing, ChError = 0x%X\n", gWarnString, ChError);
  }

  if (TxtClean) {
    if (ChError == 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Memory is Clean, ChError = 0x%X, Calling TxtLib ClearSecretsBit()\n", ChError);
      MrcCall->MrcClearSecretsBit();     // Call TxtLib ClearSecretsBit();
    } else { //Failed on scrub
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Calling TxtLib SetPowerDownRequest()\n");
      MrcCall->MrcSetPowerDownRequest();    // Call TxtLib SetPowerDownRequest();
    }
  }

  return Status;
}

/**
  This function performs a memory alias check.

  @param[in] MrcData - The global host structure

  @retval mrcSuccess or error value.
**/
MrcStatus
MrcAliasCheck (
  IN OUT MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION            *MrcCall;
  MrcDebug                      *Debug;
  MrcInput                      *Inputs;
  MrcOutput                     *Outputs;
  MrcControllerOut              *ControllerOut;
  MrcDimmOut                    *DimmOut;
  MrcStatus                     Status;
  INT64                         RefreshSave;
  INT64                         GetSetVal;
  UINT32                        SdramAddressingCapacity;
  UINT32                        CrOffset;
  UINT32                        SdramCapacity;
  UINT8                         Rank;
  UINT8                         RankToDimm;
  UINT8                         Channel;
  UINT8                         ActiveChBitMask;
  BOOLEAN                       InvalidSpdAddressingCapacity;
  MRC_REUTAddress               ReutAddress;
  MAD_INTRA_CH0_STRUCT          MadIntraOrig[MAX_CHANNEL];
  MAD_INTRA_CH0_STRUCT          MadIntra;
  BOOLEAN                       Lpddr4;
  CH0_CR_SC_PCIT_STRUCT         ScPcit;
  INT64                         IocEccEn;
  CH0_CR_SC_PCIT_STRUCT     ScPcitOrg[MAX_CHANNEL];
  CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT Lp4DqsOsclParamsOrg[MAX_CHANNEL];
  CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_STRUCT Lp4DqsOsclParams;
  MCMISCS_DELTADQSCOMMON0_STRUCT          DeltaDqsCommon;
  MCMISCS_DELTADQSCOMMON0_STRUCT          DeltaDqsCommonOrg;

  Outputs       = &MrcData->Outputs;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Status        = mrcSuccess;
  Lpddr4        = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  InvalidSpdAddressingCapacity  = FALSE;

  // Check to see if the SDRAM Addressing * Primary Bus Width == SDRAM capacity.
  // If not, report an alias and exit.
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += MAX_RANK_IN_DIMM) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        RankToDimm              = RANK_TO_DIMM_NUMBER (Rank);
        DimmOut                 = &ControllerOut->Channel[Channel].Dimm[RankToDimm];
        SdramAddressingCapacity = (DimmOut->ColumnSize * DimmOut->RowSize);
        // Since the minimum number of row and column bits are 12 and 9 respectively,
        // we can shift by 20 to get the result in Mb before multiplying by the bus width.
        SdramAddressingCapacity  = SdramAddressingCapacity >> 20;
        SdramAddressingCapacity *= DimmOut->Banks;
        SdramAddressingCapacity *= DimmOut->BankGroups;
        SdramAddressingCapacity *= DimmOut->SdramWidth;
        if (Lpddr4) {
          // SPD Density is per die, but SdramWidth is per LP4 channel, so need to multiple by number of channels per die
          SdramAddressingCapacity *= DimmOut->ChannelsPerDie;
        }
        SdramCapacity            = SdramCapacityTable[DimmOut->DensityIndex] * 8;
        if (SdramCapacity != SdramAddressingCapacity) {
          InvalidSpdAddressingCapacity = TRUE;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            "ERROR: Channel %d Dimm %d SPD SDRAM Adressing Capacity(0x%xMb) does not match SDRAM Capacity(0x%xMb)\nPlease verify:\n",
            Channel,
            RankToDimm,
            SdramAddressingCapacity,
            SdramCapacity
            );
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_ERROR,
            " Capacity: 0x%x\n RowSize: 0x%x\n ColumnSize: 0x%x\n Banks: 0x%x\n Bank Groups: 0x%x\n Device Width: 0x%x\n",
            SdramCapacity,
            DimmOut->RowSize,
            DimmOut->ColumnSize,
            DimmOut->Banks,
            DimmOut->BankGroups,
            DimmOut->SdramWidth
            );
          break;
        }
      }
    }
  }
  //
  // Since we will not hang the system, signal that an Alias could exist and return mrcSuccess.
  //
  if (TRUE == InvalidSpdAddressingCapacity) {
    Outputs->SpdSecurityStatus = MrcSpdStatusAliased;
    MRC_DEBUG_ASSERT (
      (InvalidSpdAddressingCapacity == FALSE),
      Debug,
      "...Memory Alias detected - Invalid Spd Addressing Capacity...\n"
    );
    return Status;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Performing Alias Test\n");
  MrcCall->MrcSetMem ((UINT8 *) &ReutAddress, sizeof (ReutAddress), 0);


  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Determine if we are ECC enabled.  If so, disable ECC since the ECC scrub has yet to occur.
      if (Outputs->EccSupport == TRUE) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "ECC enabled.  Disabling ECC for the test.  Must scrub after this!!!\n");
        CrOffset = MAD_INTRA_CH0_REG + ((MAD_INTRA_CH1_REG - MAD_INTRA_CH0_REG) * Channel);
        MadIntraOrig[Channel].Data = MrcReadCR (MrcData, CrOffset);
        MadIntra.Data              = MadIntraOrig[Channel].Data;
        MadIntra.Bits.ECC          = emNoEcc;
        MrcWriteCR (MrcData, CrOffset, MadIntra.Data);
      }
      if (Lpddr4) {
        // Disable the DQS Osillator for LP4.
        CrOffset = OFFSET_CALC_CH (CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, Channel);
        Lp4DqsOsclParams.Data                 = MrcReadCR (MrcData, CrOffset);
        Lp4DqsOsclParamsOrg[Channel].Data     = Lp4DqsOsclParams.Data;
        Lp4DqsOsclParams.Bits.DQSOSCL_PERIOD  = 0;
        Lp4DqsOsclParams.Bits.DIS_SRX_DQSOSCL = 1;
        MrcWriteCR (MrcData, CrOffset, Lp4DqsOsclParams.Data);
      }
      // Change PCIT to 0xFF
      CrOffset            = OFFSET_CALC_CH (CH0_CR_SC_PCIT_REG, CH1_CR_SC_PCIT_REG, Channel);
      ScPcit.Data         = MrcReadCR (MrcData, CrOffset);
      ScPcitOrg[Channel]  = ScPcit;
      ScPcit.Bits.PCIT    = 0xFF;
      MrcWriteCR (MrcData, CrOffset, ScPcit.Data);
    }
  }
  if (Outputs->EccSupport) {
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocEccEn, ReadFromCache, &IocEccEn);
    GetSetVal = 0;
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocEccEn, ForceWriteCached, &GetSetVal);
  }
  DeltaDqsCommonOrg.Data = 0;
  if (Lpddr4) {
   // Disable DqDqs Retraining feature
    CrOffset = MCMISCS_DELTADQSCOMMON0_REG;
    DeltaDqsCommon.Data = MrcReadCR (MrcData, CrOffset);
    DeltaDqsCommonOrg.Data = DeltaDqsCommon.Data;
    if (DeltaDqsCommonOrg.Bits.Lp4DeltaDQSTrainMode == 1) {
      DeltaDqsCommon.Bits.Lp4DeltaDQSTrainMode = 0;
      MrcWriteCR (MrcData, CrOffset, DeltaDqsCommon.Data);
    }
  }

  // Enable Refreshes. Save previous state.
  MrcGetSetDdrIoGroupController0(MrcData, GsmMccEnableRefresh, ReadNoCache, &RefreshSave);
  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0(MrcData, GsmMccEnableRefresh, WriteNoCache, &GetSetVal);

  // Go to CPCG mode
  MrcSetNormalMode (MrcData, FALSE);

  // Run test Per Dimm
  //
  for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += MAX_RANK_IN_DIMM){
    if ((MRC_BIT0 << Rank) & Outputs->ValidRankMask) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Testing Dimm %d\n", Rank / 2);
//@todo <ICL>      MrcMemoryCheckSetup (MrcData, &ReutAddress, Rank, 0, &ReutUninitialized);
      //
      // Determine Active Channels
      //
      ActiveChBitMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ActiveChBitMask |= SelectReutRanks (MrcData, Channel, MRC_BIT0 << Rank, FALSE, 0);
      }

      //
      // Run the test
      //
//@todo <ICL>      Status = MrcRunMemoryScrub (MrcData, ActiveChBitMask, TRUE);
      if (Status != mrcSuccess) {
        break;
      }
    }
  }

  if (Lpddr4 && (DeltaDqsCommonOrg.Bits.Lp4DeltaDQSTrainMode == 1)) {
    // Restore DqDqs Retraining value
    CrOffset = MCMISCS_DELTADQSCOMMON0_REG;
    MrcWriteCR (MrcData, CrOffset, DeltaDqsCommonOrg.Data);
  }
  if (Outputs->EccSupport) {
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocEccEn, ForceWriteCached, &IocEccEn);
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "ReEnabling ECC Logic.  Must scrub after this!\n");
  }
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Restore PCIT value
      CrOffset  = OFFSET_CALC_CH (CH0_CR_SC_PCIT_REG, CH1_CR_SC_PCIT_REG, Channel);
      MrcWriteCR (MrcData, CrOffset, ScPcitOrg[Channel].Data);
      if (Lpddr4) {
        // Restore the DQS Oscillator value for LP4.
        CrOffset = OFFSET_CALC_CH (CH0_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, CH1_CR_LP4_DQS_OSCILLATOR_PARAMS_REG, Channel);
        MrcWriteCR (MrcData, CrOffset, Lp4DqsOsclParamsOrg[Channel].Data);
      }
      // ReEnable ECC logic.
      if (Outputs->EccSupport == TRUE) {
        CrOffset = MAD_INTRA_CH0_REG + ((MAD_INTRA_CH1_REG - MAD_INTRA_CH0_REG) * Channel);
        MrcWriteCR (MrcData, CrOffset, MadIntraOrig[Channel].Data);
      }
    }
  }

  // Wait 4 usec after enabling the ECC IO, needed by HW
  MrcWait (MrcData, 4 * MRC_TIMER_1US);

  // Go to Normal mode
  MrcSetNormalMode (MrcData, TRUE);

  if (mrcSuccess != Status) {
    Outputs->SpdSecurityStatus = MrcSpdStatusAliased;
    MRC_DEBUG_ASSERT (
      (Status == mrcSuccess),
      Debug,
      "%s Alias Detected! See REUT Error above. ***\n Error Status : %x \n", gErrString, Status);
    Status = mrcSuccess;
  }

  // Restore Refreshes.
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableRefresh, WriteNoCache, &RefreshSave);

  return Status;
}

/**
  This function provides MRC core hook to call TXT Alias Check before DRAM Init Done.

  @param[in]  MrcData - Pointer to global MRC structure.

  @retval mrcSuccess.
**/
MrcStatus
MrcTxtAliasCheck (
  IN MrcParameters *const MrcData
  )
{
  MrcData->Inputs.Call.Func->MrcTxtAcheck();
  return mrcSuccess;
}

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

/**
  This function sets all the memory to a known value when ECC is enabled and
  either we are not in warm boot or we are in warm boot and TXT is set (which is forced to fast cold).

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
  //static const UINT8    WrapCarryEn[MrcReutFieldMax]   = {0, 0, 0, 0};
  //static const UINT8    WrapTriggerEn[MrcReutFieldMax] = {0, 0, 0, 0};
  //static const UINT8    AddrInvertEn[MrcReutFieldMax]  = {0, 0, 0, 0};
  MrcOutput             *Outputs;
  MrcTiming             *Timing;
  MrcStatus             Status;
  MRC_REUTAddress       ReutAddress;
  INT64                 GetSetVal;
  UINT32                Offset;
  UINT32                DdrMrParamsSave[MAX_CHANNEL];
  UINT32                tREFI;
  UINT8                 Rank;
  UINT8                 Channel;
  UINT8                 ActiveChBitMask;
  BOOLEAN               EccEnabled;
  MC0_CH0_CR_DDR_MR_PARAMS_STRUCT             DdrMrParams;
//  REUT_CH0_SUBSEQ_CTL_0_STRUCT            ReutSubSeqCtl;
  //CH0_SC0_CR_CPGC_SEQ_STATUS_STRUCT          ReutChSeqCfg;
  //CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_STRUCT   ReutChPatWdbCl; //@todo <ICL> Update with CPGC 2.0 implementation
  MC0_CH0_CR_SC_PCIT_STRUCT                   ScPcit;
  MC0_CH0_CR_SC_PCIT_STRUCT                   ScPcitSave[MAX_CHANNEL];
#ifdef MRC_DEBUG_PRINT
  static const char *SourceStr[2] = {"Ecc", "CleanMemory"};
#endif

  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  Status        = mrcSuccess;
  EccEnabled    = (Outputs->EccSupport == TRUE);
  MrcCall->MrcSetMem ((UINT8 *) &ReutAddress, sizeof (ReutAddress), 0);

  if (EccEnabled || (Inputs->CleanMemory == TRUE)) {
    //
    // Enable refreshes on MC before we start ECC scrubbing.
    //
    GetSetVal = 1;
    MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableRefresh, WriteNoCache, &GetSetVal);

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Scrubbing Memory due to %s\n", (EccEnabled) ? SourceStr[0] : SourceStr[1]);
    //
    // Setup the first cache line to zeros.
    //
    // @todo <CNL> use DC level feature instead of WDBFixedPattern ?
    //WriteFixedPattern (MrcData, &Pattern, &PMask, 1, 0);

    // Setup CPGC for both channels. Test will write 0x0 to all memory
    // Go to CPCG mode
    MrcSetNormalMode (MrcData, FALSE);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (MrcData, 0, Channel)) {
        continue;
      }
/**
      // Set Reut sequence cfg register
      ReutChSeqCfg.Data                                    = 0;
      ReutChSeqCfg.Bits.Global_Control                     = 1;
      ReutChSeqCfg.Bits.Start_Test_Delay                   = 2;
      ReutChSeqCfg.Bits.Address_Update_Rate_Mode           = 0;
      ReutChSeqCfg.Bits.Stop_Base_Sequence_On_Wrap_Trigger = 0;
      MrcWriteCR64 (
        MrcData,
        OFFSET_CALC_CH (REUT_CH_SEQ_CFG_0_REG, REUT_CH_SEQ_CFG_1_REG, Channel),
        ReutChSeqCfg.Data
        );
**/
      //
      // Program Write Data Buffer Control.  Since we are using 1 cache line, we only need
      // to set the increment scale to linear.
      //
/** @todo <ICL>: Update with CPGC 2.0 implementation
      ReutChPatWdbCl.Data = 0;
      ReutChPatWdbCl.Bits.WDB_Increment_Scale = 1;
      MrcWriteCR (
        MrcData,
        OFFSET_CALC_CH (CH0_CR_REUT_CH_PAT_WDB_CL_CTRL_REG, CH1_CR_REUT_CH_PAT_WDB_CL_CTRL_REG, Channel),
        ReutChPatWdbCl.Data
        );
**/
      //
      // Change PCIT to 0xFF
      //
      Offset = OFFSET_CALC_CH (MC0_CH0_CR_SC_PCIT_REG, MC0_CH1_CR_SC_PCIT_REG, Channel);
      ScPcit.Data = MrcReadCR (MrcData, Offset);
      ScPcitSave[Channel] = ScPcit;
      ScPcit.Bits.PCIT = 0xFF;
      MrcWriteCR (MrcData, Offset, ScPcit.Data);
    }

    //
    // Continue to setup Reut and Run Per Rank
    //
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (((1 << Rank) & Outputs->ValidRankMask) == 0) {
        continue;
      }
      //
      // Determine the Active Channels
      //
      ActiveChBitMask = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ActiveChBitMask |= SelectReutRanks (MrcData, /**Controller**/ 0, Channel, MRC_BIT0 << Rank, FALSE, 0);
      }

      //
      // Program the sequence addresses and loopcount per channel
      //
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if ((ActiveChBitMask & (1 << Channel)) == 0) {
          continue;
        }

        // Go over all addresses
/** @todo <ICL>: Update with CPGC 2.0 implementation
        ReutAddress.Stop[MrcReutFieldCol]  = DimmOut->ColumnSize - WDB_CACHE_LINE_SIZE;
        ReutAddress.Stop[MrcReutFieldRow]  = (UINT16) DimmOut->RowSize - 1;
        ReutAddress.Stop[MrcReutFieldBank] = BankCount - 1;

        ReutAddress.IncVal[MrcReutFieldCol]  = 1;  // Each write is 1 cache line which is 8 column addresses worth of data.
        ReutAddress.IncVal[MrcReutFieldRow]  = 1;  // Walk through rows 1 at a time.
        ReutAddress.IncVal[MrcReutFieldBank] = 1;  // Walk through bank 1 at a time.

        ReutAddress.IncRate[MrcReutFieldRow]  = DimmOut->ColumnSize / WDB_CACHE_LINE_SIZE;
        ReutAddress.IncRate[MrcReutFieldBank] = DimmOut->RowSize * (DimmOut->ColumnSize / WDB_CACHE_LINE_SIZE);

        MrcProgramSequenceAddress (
          MrcData,
          Channel,
          ReutAddress.Start,
          ReutAddress.Stop,
          ReutAddress.Order,
          ReutAddress.IncRate,
          ReutAddress.IncVal,
          WrapTriggerEn,
          WrapCarryEn,
          AddrInvertEn,
          0,                    // AddrInvertRate
          FALSE
        );

        // Set up the Subsequence control.
        ReutSubSeqCtl.Data = 0;
        ReutSubSeqCtl.Bits.Subsequence_Type = BWr;
        ReutSubSeqCtl.Bits.Number_of_Cachelines = MrcLog2 ((DimmOut->ColumnSize / WDB_CACHE_LINE_SIZE)) - 1; // MrcLog2 is giving log value plus 1
        ReutSubSeqCtl.Bits.Number_of_Cachelines_Scale = 0;
        MrcWriteCR (
          MrcData,
          OFFSET_CALC_CH (REUT_CH0_SUBSEQ_CTL_0_REG, REUT_CH1_SUBSEQ_CTL_0_REG, Channel),
          ReutSubSeqCtl.Data
        );

        // Program loopcount registers
        MrcSetLoopcount (MrcData, BankCount * DimmOut->RowSize);
**/
      } // for Channel

      //
      // Run the test on both Channels
      //
      Status = MrcRunMemoryScrub (MrcData, ActiveChBitMask, TRUE);
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Rank %d error!\n", Rank);
        break;
      }
    } // for Rank

    // To avoid an invalid timing of Temp read, we need to do the following:
    //   Save previous value
    //   Set MR4_PERIOD to 0
    //   Wait tREFI
    //   Go to Normal mode
    //   Restore MR4_PERIOD
    if (EccEnabled) {
      tREFI = 0;
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist (MrcData, 0, Channel)) {
          Offset = MC0_CH0_CR_DDR_MR_PARAMS_REG +
            (MC0_CH1_CR_DDR_MR_PARAMS_REG - MC0_CH0_CR_DDR_MR_PARAMS_REG) * Channel;
          DdrMrParamsSave[Channel] = MrcReadCR (MrcData, Offset);
          DdrMrParams.Data = DdrMrParamsSave[Channel];
          DdrMrParams.Bits.MR4_PERIOD = 0;
          MrcWriteCR (MrcData, Offset, DdrMrParams.Data);
          Timing = &Outputs->Controller[0].Channel[Channel].Timing[Inputs->MemoryProfile];
          tREFI = MAX (tREFI, Timing->tREFI);
        }
      }
      // Memory Clock is in fs.  Scale to ps then multiply by tREFI.  Then Ciel to nearest ns.
      tREFI = tREFI * (Outputs->MemoryClock / 1000);
      tREFI = DIVIDECEIL (tREFI, 1000);
      MrcWait (MrcData, tREFI * MRC_TIMER_1NS);
    }

    // Go to Normal mode
    MrcSetNormalMode (MrcData, TRUE);

    // Restore MR4
    if (EccEnabled) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist (MrcData, 0, Channel)) {
          Offset = MC0_CH0_CR_DDR_MR_PARAMS_REG +
            (MC0_CH1_CR_DDR_MR_PARAMS_REG - MC0_CH0_CR_DDR_MR_PARAMS_REG) * Channel;
          MrcWriteCR (MrcData, Offset, DdrMrParamsSave[Channel]);
        }
      }
    }

    if (Status != mrcSuccess) {
      MrcCall->MrcDebugHook (MrcData, MRC_ECC_CLEAN_ERROR);
    }
    //
    // Restore PCIT value
    //
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (MrcData, 0, Channel)) {
        Offset = OFFSET_CALC_CH (MC0_CH0_CR_SC_PCIT_REG, MC0_CH1_CR_SC_PCIT_REG, Channel);
        MrcWriteCR (MrcData, Offset, ScPcitSave[Channel].Data);
      }
    }
  } // if scrubbing required

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
  const MRC_FUNCTION  *MrcCall;
  MrcDebug            *Debug;
  const MrcInput      *Inputs;
  static const UINT16 SdramCapacityTable[] = {256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 12288, 24576, 3072, 6144, 18432}; // Mb
  MrcOutput           *Outputs;
  MrcControllerOut    *ControllerOut;
  MrcDimmOut          *DimmOut;
  MrcStatus           Status;
  INT64               RefreshSave;
  INT64               GetSetVal;
  UINT32              SdramAddressingCapacity;
  UINT8               SdramCapacityFactor;
  UINT32              CrOffset;
  UINT16              SdramCapacity;
  UINT8               Rank;
  UINT8               RankToDimm;
  UINT8               Channel;
  UINT8               ActiveChBitMask;
  BOOLEAN             InvalidSpdAddressingCapacity;
  MRC_REUTAddress     ReutAddress;
  MC0_MAD_INTRA_CH0_STRUCT       MadIntraOrig[MAX_CHANNEL];
  MC0_MAD_INTRA_CH0_STRUCT       MadIntra;

  Outputs       = &MrcData->Outputs;
  Inputs        = &MrcData->Inputs;
  MrcCall       = Inputs->Call.Func;
  Debug         = &Outputs->Debug;
  ControllerOut = &Outputs->Controller[0];
  Status        = mrcSuccess;
  InvalidSpdAddressingCapacity  = FALSE;

  // SPD shows capacity for x16 channel, but our channel width is x32. Need Multiply by two.
  SdramCapacityFactor  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ? 2 : 1;

  // Enable Refreshes.  Save previous state.
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableRefresh, ReadNoCache, &RefreshSave);
  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableRefresh, WriteNoCache, &GetSetVal);

  // Go to CPCG mode
  MrcSetNormalMode (MrcData, FALSE);

  //
  // Check to see if the SDRAM Addressing * Primary Bus Width == SDRAM capacity.
  // If not, report an alias and exit.
  //
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += MAX_RANK_IN_DIMM) {
      if (MrcRankExist (MrcData, CONTROLLER_0, Channel, Rank)) {
        RankToDimm              = RANK_TO_DIMM_NUMBER (Rank);
        DimmOut                 = &ControllerOut->Channel[Channel].Dimm[RankToDimm];
        SdramAddressingCapacity = (DimmOut->ColumnSize * DimmOut->RowSize);
        // Since the minimum number of row and column bits are 12 and 9 respectively,
        // we can shift by 20 to get the result in Mb before multiplying by the bus width.
        SdramAddressingCapacity  = (SdramAddressingCapacity >> 20) * SdramCapacityFactor;
        SdramAddressingCapacity *= DimmOut->Banks;
        SdramAddressingCapacity *= DimmOut->BankGroups;
        SdramAddressingCapacity *= DimmOut->SdramWidth;
        SdramCapacity            = SdramCapacityTable[DimmOut->DensityIndex];
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
    return Status;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Performing Alias Test\n");
  MrcCall->MrcSetMem ((UINT8 *) &ReutAddress, sizeof (ReutAddress), 0);

  //
  // Determine if we are ECC enabled.  If so, disable ECC since the ECC scrub has yet to occur.
  //
  if (Outputs->EccSupport == TRUE) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "ECC enabled.  Disabling ECC for the test.  Must scrub after this!!!\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (MrcData, 0, Channel)) {
        CrOffset = MC0_MAD_INTRA_CH0_REG +
          ((MC0_MAD_INTRA_CH1_REG - MC0_MAD_INTRA_CH0_REG) * Channel);

        MadIntraOrig[Channel].Data = MrcReadCR (MrcData, CrOffset);
        MadIntra.Data              = MadIntraOrig[Channel].Data;
        MadIntra.Bits.ECC          = emNoEcc;
        MrcWriteCR (MrcData, CrOffset, MadIntra.Data);
      }
    }
  }

  //
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
        ActiveChBitMask |= SelectReutRanks (MrcData, /**Controller**/ 0, Channel, MRC_BIT0 << Rank, FALSE, 0);
      }

      //
      // Run the test
      //
      Status = MrcRunMemoryScrub (MrcData, ActiveChBitMask, TRUE);
      if (Status != mrcSuccess) {
        break;
      }
    }
  }

  if (Outputs->EccSupport == TRUE) {
    MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "ReEnabling ECC Logic.  Must scrub after this!\n");
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (MrcData, 0, Channel)) {
        CrOffset = MC0_MAD_INTRA_CH0_REG +
          ((MC0_MAD_INTRA_CH1_REG - MC0_MAD_INTRA_CH0_REG) * Channel);

        MrcWriteCR (MrcData, CrOffset, MadIntraOrig[Channel].Data);
      }
    }
  }

  // Wait 4 usec after enabling the ECC IO, needed by HW
  MrcWait (MrcData, 4 * MRC_TIMER_1US);

  // Go to Normal mode
  MrcSetNormalMode (MrcData, TRUE);

  if (mrcSuccess != Status) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "*** Alias Detected!  See REUT Error above. ***\n");
    Outputs->SpdSecurityStatus = MrcSpdStatusAliased;
    Status = mrcSuccess;
  }

  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableRefresh, WriteNoCache, &RefreshSave);

  return Status;
}

/**
  This function runs the srcubbing test reporting any timeouts/errors.

  @param[in] MrcData - The global host structure
  @param[in] ChBitMask - Bitmask of channels the test is run on.
  @param[in] MsgPrint  - Print debug messages

  @retval mrcSuccess or error value.
**/
MrcStatus
MrcRunMemoryScrub (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                ChBitMask,
  IN     BOOLEAN              MsgPrint
  )
{
//@todo <ICL> Update with CPGC 2.0 implementation.
//  const MRC_FUNCTION *MrcCall;
//  MrcDebug           *Debug;
//  MrcDebugMsgLevel   DebugLevel;
  MrcStatus          Status;
  Status  = mrcSuccess;
/**
  UINT8              ErrorStatus;
  UINT8              TestDoneStatus;
  REUT_GLOBAL_CTL_STRUCT       ReutGlobalCtl;
  REUT_GLOBAL_ERR_STRUCT       ReutGlobalErr;
#ifndef SLE_FLAG
  UINT64  Timer;
#endif

  Status  = mrcSuccess;
  Debug   = &MrcData->Outputs.Debug;
  MrcCall = MrcData->Inputs.Call.Func;
  DebugLevel = MsgPrint ? MSG_LEVEL_ERROR : MSG_LEVEL_NEVER;
  TestDoneStatus = 1;
  IoReset (MrcData);
  //
  // Setup Timer and run the test
  //
#ifndef SLE_FLAG
  Timer = MrcCall->MrcGetCpuTime () + 20000; // 20 Second timeout
#endif
  ReutGlobalCtl.Data                                = 0;
  ReutGlobalCtl.Bits.Global_Start_Test              = 1;
  ReutGlobalCtl.Bits.Global_Clear_Errors            = 1;
  ReutGlobalCtl.Bits.Global_Stop_Test_On_Any_Error  = NSOE;
  MrcWriteCR (MrcData, REUT_GLOBAL_CTL_REG, ReutGlobalCtl.Data);
  //
  // Wait until Channel test done status matches ChbitMask or TimeoutCounter value reaches 0;
  //
  do {
    ReutGlobalErr.Data = MrcReadCR (MrcData, REUT_GLOBAL_ERR_REG);
    TestDoneStatus     = (UINT8) ((ReutGlobalErr.Bits.Channel_Test_Done_Status_1 << 1) |
                                ReutGlobalErr.Bits.Channel_Test_Done_Status_0);
#ifdef SLE_FLAG
  } while (((TestDoneStatus & ChBitMask) != ChBitMask));
#else
  } while (((TestDoneStatus & ChBitMask) != ChBitMask) && (MrcCall->MrcGetCpuTime () < Timer));
#endif

  if ((TestDoneStatus & ChBitMask) != ChBitMask) {
    Status = mrcDeviceBusy;
    MRC_DEBUG_MSG (
      Debug,
      DebugLevel,
      "Timeout occured while running the test: ReutGlobalErr: 0x%X.\n",
      ReutGlobalErr.Data
      );
  }

  // For x64 Channels, we can break out as soon as either SubChannel has an error for the channels populated.
  // Same as Error Status mask.
  // Current assumption is SubChannels are run sequentially.  Traffic is only sent on tested sub channel.  If a failure occurs, report it as an error for that Channel.
  // If a Sch is not populated, its Error status is Don't Care.
  // Not Valid (NV)
  // Sc1,Sc0   | 0,0 | 0,1 | 1,1 | 1,0 |
  // Sc1E,Sc0E |-----------------------|
  //    0,0    | NV  |  0  |  0  |  0  |
  //    0,1    | NV  |  1  |  1  |  0  |
  //    1,1    | NV  |  1  |  1  |  1  |
  //    1,0    | NV  |  0  |  1  |  1  |
  //           |-----------------------|
  // SA:RestricteContent - @todo: <ICL> Modify when enabling 2 SCH parallel execution
  ErrorStatus = (UINT8) ((ReutGlobalErr.Bits.Channel_Error_Status_3 | ReutGlobalErr.Bits.Channel_Error_Status_2) << 1 |
                          (ReutGlobalErr.Bits.Channel_Error_Status_1 | ReutGlobalErr.Bits.Channel_Error_Status_0));
  if (ErrorStatus & ChBitMask) {
    Status = mrcReutSequenceError;
    MRC_DEBUG_MSG (
      Debug,
      DebugLevel,
      "REUT Error: Channel(s):%s%s\n",
      (ReutGlobalErr.Bits.Channel_Error_Status_0 == 1) ? " 0" : "",
      (ReutGlobalErr.Bits.Channel_Error_Status_1 == 1) ? " 1" : ""
      );
  }

**/
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

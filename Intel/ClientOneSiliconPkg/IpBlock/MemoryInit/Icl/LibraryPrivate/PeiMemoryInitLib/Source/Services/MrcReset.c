/** @file
  The functions in this file implement the DDR4 reset sequence.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
// Include files

#include "MrcReset.h"
#include "MrcMcConfiguration.h"
#include "MrcDdrCommon.h"
#include "MrcLpddr4.h"
#include "MrcDdr4.h"
#include "MrcGears.h"

/**
  Perform full JEDEC reset and init sequence.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcResetSequence (
  IN MrcParameters *const MrcData
  )
{
  MrcStatus     Status;
  MrcInput      *Inputs;
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  MrcDdrType    DdrType;
  MrcFrequency  DdrFreq;
  UINT8         Channel;
  UINT8         Value;
  UINT8         tCCD_L;
  BOOLEAN       Restore;
  BOOLEAN       Lpddr4;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;
  Lpddr4  = (DdrType == MRC_DDR_TYPE_LPDDR4);

  // Start with an IO reset
  Status = IoReset (MrcData);

  if (mrcSuccess == Status) {
    // Check if rcomp is done and the ddr ready to use
    Status = CheckFirstRcompDone (MrcData);
    if (mrcSuccess == Status) {
      // Perform jedec reset.
      // If RTT_NOM is to be enabled in MR1, the ODT input signal must be statically held LOW
      // in our system RTT_NOM is always enable.
      // Force ODT low
      MrcWriteCR (MrcData, BC_CR_REUT_CH_MISC_ODT_CTRL_REG, CH0_CR_REUT_CH_MISC_ODT_CTRL_ODT_Override_MAX);

      if (Lpddr4) {
        // Set Low frequency (1067), unless we're already there
        // This will also update Gear2 mode in MC/DDRIO, in LP4 we switch to Gear1 when going down to 1067.
        if ((Outputs->Frequency != f1067) && (Inputs->LpFreqSwitch == TRUE)) {
          Status = MrcFrequencySwitch (MrcData, f1067, !Outputs->RestoreMRs);
          if (Status != mrcSuccess) {
            return Status;
          }
        }

        Status = MrcJedecResetLpddr4 (MrcData);
        if (Status == mrcSuccess) {
          Status = MrcJedecInitLpddr4 (MrcData);
        }

        if (Outputs->LpddrEctDone && (Status == mrcSuccess)) {
          // Set FSP-OP = 1, set High frequency
          Status = MrcLpddr4SwitchToHigh (MrcData, !Outputs->RestoreMRs);
        }
        if (!Outputs->JedecInitDone) {
          Outputs->JedecInitDone  = TRUE;
          Outputs->RestoreMRs     = TRUE;
        }
        MrcWriteCR (MrcData, BC_CR_REUT_CH_MISC_ODT_CTRL_REG, 0);
        return Status;
      }

      MrcJedecReset (MrcData);

      // Initialize the DIMM MRS registers.
      if (DdrType == MRC_DDR_TYPE_DDR4) {
        DdrFreq = Outputs->Frequency;
        // MR3 A10:A9 Write Command Latency when CRC and DM are both enabled
        if (DdrFreq <= f1600) {
          Value = 0;
        } else if (DdrFreq <= f2400) {
          Value = 1;
        } else {
          Value = 2;
        }
        // Step 6 - Set the MR3 for each rank
        // MR3 A[3] = 0 = 1/2 Rate (Geardown Mode)
        // MR3 A[4] = 0 = Disable  (Per DRAM Addressability)
        Status = MrcSetMR3_DDR4 (MrcData, 0, 0, 0, 0, 0, 0, 0, Value);
        if (Status == mrcSuccess) {

          Restore = Outputs->JedecInitDone;

          // Get tCCD_L from any populated channel (all channels have the same timings)
          tCCD_L = 0;
          for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
            if (MrcChannelExist (Outputs, Channel)) {
              ChannelOut = &Outputs->Controller[0].Channel[Channel];
              tCCD_L = (UINT8) ChannelOut->Timing[Inputs->MemoryProfile].tCCD_L;
              break;
            }
          }
          // tCCD_L encoding in MR6[12:10]: 0 = 4nCK, 1 = 5nCK...
          tCCD_L -= 4;

          // Step 7 - Set the MR6 for each rank
          Status = MrcSetMR6_DDR4 (MrcData, 0, 0, 0, tCCD_L, Restore);
          if (Status == mrcSuccess) {
            // Step 8 - Set the MR5 for each rank
            // MR5 A[2:0] = 000 = Disable (C/A Parity Latency Mode)
            Status = MrcSetMR5_DDR4 (MrcData, 0, 0, 0, 1, 0, 0, 0, 0);
            if (Status == mrcSuccess) {
              // Step 9 - Set the MR4 for each rank
              // MR4 A[1] = 0 = Disable     (Maximum Power Down Mode)
              // MR4 A[8:6] = 000 = Disable (CS to CMD/ADDR Latency)
              Status = MrcSetMR4_DDR4 (MrcData, 0, 0, 0, 0, 0, 0, 0, 0, 0);
              if (Status == mrcSuccess) {
                // Step 10 - Set the MR2 for each rank
                Status = MrcSetMR2_DDR4 (MrcData, 0);
                if (Status == mrcSuccess) {
                  // Step 11 - Set the MR1 for each rank
                  Status = MrcSetMR1_DDR4 (MrcData, 1, INIT_DIMM_RON_34, 0, 0, 0);
                  if (Status == mrcSuccess) {
                    // Step 12 - Set the MR0 for each rank
                    Status = MrcSetMR0_DDR4 (MrcData, 0, 0, 0, 1);
                    if (Status == mrcSuccess) {
                      // Step 13 - Issue ZQCL command to start ZQ calibration
                      Status = MrcIssueZQ (MrcData, 0x3, MRC_ZQ_INIT);
                      if (Status == mrcSuccess) {
                        // Program DIMM Vref in MR6
                        if (!Outputs->RestoreMRs) { // program middle range - 68.45% Vdd = 820mV
                          MrcSetDefaultTxVrefDdr4 (MrcData);
                        } else { // restore
                          // First program average DQ Vref using non-PDA access.
                          // Then program the per-device DQ Vref using PDA
                          ChangeMargin (MrcData, WrV, 0, 0, 1, 0, 0, 0, 0, 0, 0);
                          ChangeMargin (MrcData, WrV, 0, 0, 1, 0, 0, 0x1FF, 0, 0, 0);
                        }
                      } //Step 13 - ZQCL
                    } //Step 12 - MR0
                  } //Step 11 - MR1
                } //Step 10 - MR2
              } //Step 9 - MR4
            } //Step 8 - MR5
          } //Step 7 - MR6
        } //Step 6 - MR3
      }
      MrcWriteCR (MrcData, BC_CR_REUT_CH_MISC_ODT_CTRL_REG, 0);
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (!MrcChannelExist (Outputs, Channel)) {
          continue;
        }

        if (!Outputs->JedecInitDone) {
          // We can disable DIMM ODT at the end of the first JEDEC Init, if ODT is not used.
          // ODT pin must be stable 0 or 1 during JEDEC reset/init
          // If Odt is not used, disable all Ranks.
          if (!Outputs->DramDqOdtEn) {
            MrcSetOdtSignals (MrcData, Channel, 0);
          }
        }
      } // for Channel
      Outputs->JedecInitDone = TRUE;
    }
  }
  // Set flag to restore from host structure instead from look-up table
  Outputs->RestoreMRs = TRUE;

  return Status;
}

/**
  Perform JEDEC DIMM reset sequence.

  @param[in] MrcData - Include all MRC global data.

  @retval - none
**/
void
MrcJedecReset (
  IN MrcParameters *const MrcData
  )
{
  MrcInput                                *Inputs;
  MRC_FUNCTION                            *MrcCall;
  MrcOutput                               *Outputs;
  MrcControllerOut                        *ControllerOut;
  MrcVddSelect                            VddVoltage;
  UINT32                                  VddSettleWaitTime;
  UINT32                                  PciEBar;
  UINT8                                   Channel;
  INT64                                   GetSetVal;
  INT64                                   Ddr4OneDpc;

  Inputs            = &MrcData->Inputs;
  MrcCall           = Inputs->Call.Func;
  Outputs           = &MrcData->Outputs;
  ControllerOut     = &Outputs->Controller[0];
  VddSettleWaitTime = 200; // 200us is the minimum w/o the delay needed to allow for DDR3L Change
  PciEBar           = Inputs->PciEBaseAddress;

  // De-assert DRAM RESET# signal
  MrcCall->MrcDramReset (PciEBar, 1);

  // Force CKE low
  MrcWriteCR (MrcData, BC_CR_REUT_CH_MISC_CKE_CTRL_REG, CH0_CR_REUT_CH_MISC_CKE_CTRL_CKE_Override_MAX);

  // Assert DIMM reset signal - step 1
  MrcCall->MrcDramReset (PciEBar, 0);

  // Check and Switch voltage
  VddVoltage = Outputs->VddVoltage[Inputs->MemoryProfile];
  if ((VddVoltage != VDD_INVALID) && (Outputs->VddVoltageDone == FALSE)) {
    MrcVDDVoltageCheckAndSwitch (MrcData, VddVoltage, &VddSettleWaitTime);
  }
  // delay 200 micro sec as jedec ask
  if (Outputs->JedecInitDone) {
    VddSettleWaitTime = 1;  // tPW_RESET = 1us
  }
  MrcWait (MrcData, VddSettleWaitTime * MRC_TIMER_1US);

  // De-assert DIMM reset signal - step 2
  MrcCall->MrcDramReset (PciEBar, 1);

  // delay 500 micro sec as jedec ask
  MrcWait (MrcData, 500 * MRC_TIMER_1US);

  // Enable the DCLK - step 3
  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccEnableDclk, WriteNoCache, &GetSetVal);

  // wait the 20 nano sec tCKSRX.
  MrcWait (MrcData, 20 * MRC_TIMER_1NS);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {

      // Set the Valid CKE - step 4
      GetSetVal = ControllerOut->Channel[Channel].ValidRankBitMask;

      // Adjust CKE mask if ddr4_1dpc is enabled on this channel
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccDdr4OneDpc, ReadFromCache, &Ddr4OneDpc);
      if (Ddr4OneDpc != 0) {
        GetSetVal = 9;        // '1001' - MC is using ranks 0 and 3 when ddr4_1dpc is enabled
      }
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocCkeOn, WriteNoCache, &GetSetVal);
    }
  }
  // Wait minimum of Reset CKE Exit time, tXPR - Step 5
  // tXPR = max (5 tCK, tRFC(min) + 10ns)
  // tRFC is 550ns for 16Gb DDR4 devices
  MrcWait (MrcData, 1 * MRC_TIMER_1US);
  return;
}

/**
  Wait in a loop until the first RCOMP has been completed.
  MRC should wait until this bit is set before executing any DDR command.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcDeviceBusy - On Rcomp completion timeout.
  @retval mrcSuccess    - On Rcomp completion.
**/
MrcStatus
CheckFirstRcompDone (
  IN MrcParameters *const MrcData
  )
{
  const MRC_FUNCTION  *MrcCall;
  RCOMP_TIMER_STRUCT  CrRcompTimer;
  BOOLEAN             Busy;
  UINT64              Timeout;

  MrcCall = MrcData->Inputs.Call.Func;
  Timeout = MrcCall->MrcGetCpuTime (MrcData) + 10000; // 10 seconds timeout

  do {
    CrRcompTimer.Data = MrcReadCR (MrcData, RCOMP_TIMER_REG);
    Busy              = (0 == CrRcompTimer.Bits.First_Rcomp_done) ? TRUE : FALSE;
  } while (Busy && (MrcCall->MrcGetCpuTime (MrcData) < Timeout));

  return ((Busy) ? mrcDeviceBusy : mrcSuccess);
}

/**
  Perform the required steps to exit self refresh in S3/Warm reset:
   1. Set MC_INIT_STATE_G.pure_srx to 1.
   2. Set MCHBAR_CHx_CR_MC_INIT_STATE.SRX_reset to 1.
    - MRC does not need to pull DIMMs out of self-refresh by
      asserting CKE high, and issue ZQ Long.
    - MC will do these steps automatically when MRC will switch
      it to Normal mode.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcSelfRefreshExit (
  IN MrcParameters *const MrcData
  )
{
  const MrcOutput *Outputs;
  MrcDdrType      DdrType;
  INT64           GetSetVal;
  UINT32          Offset;
  UINT8           Channel;
  UINT8           Rank;
  BOOLEAN         Lpddr4;
  CH0_CR_MC_INIT_STATE_STRUCT               McInitState;
  CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_STRUCT  LpddrTemperature;
  CH0_CR_DDR4_MPR_RANK_TEMPERATURE_STRUCT   Ddr4Temprature;

  Outputs = &MrcData->Outputs;
  DdrType = Outputs->DdrType;
  Lpddr4  = (DdrType == MRC_DDR_TYPE_LPDDR4);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    LpddrTemperature.Data = 0;
    Ddr4Temprature.Data = 0;

    // Indicate to MC that we are going to exit Self Refresh when we go to Normal Mode
    Offset = OFFSET_CALC_CH (CH0_CR_MC_INIT_STATE_REG, CH1_CR_MC_INIT_STATE_REG, Channel);
    McInitState.Data = MrcReadCR (MrcData, Offset);
    McInitState.Bits.SRX_reset = 1;
    MrcWriteCR (MrcData, Offset, McInitState.Data);

    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
        if (Lpddr4) {
          LpddrTemperature.Data |= (RANK_TEMPERATURE_HOT_LPDDR4 << (CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_Rank_1_OFF * Rank));
        } else { // MRC_DDR_TYPE_DDR4
          Ddr4Temprature.Data |= (RANK_TEMPERATURE_HOT_DDR4 << (CH0_CR_DDR4_MPR_RANK_TEMPERATURE_Rank_1_OFF * Rank));
        }
      }
    }

    // SA:RestritedContent Permanent MRC W/A for SKL bug [5122603][Mc unaware of DRAM initial temperature may violate derating/refresh rate requirements]
    // SA:RestritedContent Keep the same W/A for CNL.
    // Initialize MC to "hot" temperature until the first LPDDR4/DDR4 temperature read occurs.
    if (Lpddr4) {
      Offset = OFFSET_CALC_CH (CH0_CR_LPDDR_MR4_RANK_TEMPERATURE_REG, CH1_CR_LPDDR_MR4_RANK_TEMPERATURE_REG, Channel);
      MrcWriteCR (MrcData, Offset, LpddrTemperature.Data);
    } else { // MRC_DDR_TYPE_DDR4
      Offset = OFFSET_CALC_CH (CH0_CR_DDR4_MPR_RANK_TEMPERATURE_REG, CH1_CR_DDR4_MPR_RANK_TEMPERATURE_REG, Channel);
      MrcWriteCR (MrcData, Offset, Ddr4Temprature.Data);
    }
  } // for Channel

  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmMccPureSrx, WriteNoCache, &GetSetVal);

  return mrcSuccess;
}


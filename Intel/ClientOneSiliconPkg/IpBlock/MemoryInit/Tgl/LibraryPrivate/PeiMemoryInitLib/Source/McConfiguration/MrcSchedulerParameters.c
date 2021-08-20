/** @file
  This module configures the memory controller scheduler.

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

// Include files
#include "MrcSchedulerParameters.h"

/// Defines
#define MRC_SC_PH_THROT_CR_COUNT  (4)

/// Enumerations
typedef enum {
  MrcSptLoadSameRank,
  MrcSptUnloadedSameRank,
  MrcSptLoadedDiffRank,
  MrcSptUnloadedDiffRank,
  MrcSptMax
} MRC_SC_PH_THROT_TYPE;

/// Static data
const static UINT8 ScPhThrottlingPor[MRC_SC_PH_THROT_CR_COUNT][MrcSptMax] = {
  {8, 1, 12, 1}, // SC_PH_THROTTLING_0
  {4, 0,  8, 0}, // SC_PH_THROTTLING_1
  {2, 0,  6, 0}, // SC_PH_THROTTLING_2
  {0, 0,  0, 0}  // SC_PH_THROTTLING_3
};

/**
  This function configures the memory controller MC0_CH0_CR_SPID_LOW_POWER_CTL register using
  the register definition compatible with TGL A0 and TGL P0.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - The target controller to configure
  @param[in] IpChannel  - The target IP Channel to configure.

  @retval Nothing.
**/
void
ConfigSpidLowPowerCtl (
  IN MrcParameters *const MrcData,
  IN UINT32         Controller,
  IN UINT32         IpChannel
  )
{
  const MrcInput                       *Inputs;
  BOOLEAN                              SafeMode;
  UINT32                               Offset;
  MC0_CH0_CR_SPID_LOW_POWER_CTL_STRUCT SpidLowPowerCtl;

  Inputs        = &MrcData->Inputs;
  SafeMode      = (Inputs->SafeMode == TRUE);

  Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SPID_LOW_POWER_CTL_REG, MC1_CH0_CR_SPID_LOW_POWER_CTL_REG, Controller, MC0_CH1_CR_SPID_LOW_POWER_CTL_REG, IpChannel);
  SpidLowPowerCtl.Data = MrcReadCR (MrcData, Offset);
  SpidLowPowerCtl.A0Bits.ckevalid_enable = SafeMode ? 0 : 1;
  SpidLowPowerCtl.A0Bits.selfrefresh_latency = SafeMode ? 5 : 2;
  // Safe mode values are CR default
  if (!SafeMode) {
    SpidLowPowerCtl.A0Bits.raise_cke_after_exit_latency = 0;
    SpidLowPowerCtl.A0Bits.idle_length = 1;
    SpidLowPowerCtl.A0Bits.powerdown_length = 8;
    SpidLowPowerCtl.A0Bits.selfrefresh_length = 8;
  } else {
    SpidLowPowerCtl.A0Bits.powerdown_enable = 0;
    SpidLowPowerCtl.A0Bits.selfrefresh_enable = 0;
  }
  if (Inputs->A0) {
    SpidLowPowerCtl.A0Bits.powerdown_latency  = 5;
    SpidLowPowerCtl.A0Bits.idle_latency       = 2;
    SpidLowPowerCtl.A0Bits.powerdown_enable   = 0;
    SpidLowPowerCtl.A0Bits.selfrefresh_enable = 0;
  } else {
    if (!SafeMode) {
      SpidLowPowerCtl.A0Bits.idle_latency = 0;
    }
    SpidLowPowerCtl.A0Bits.powerdown_latency = SafeMode ? 5 : 2;
  }
  MrcWriteCR (MrcData, Offset, SpidLowPowerCtl.Data);
}

/**
  This function configures the memory controller MC0_CH0_CR_SPID_LOW_POWER_CTL register using
  the register definition compatible with TGL A0 and TGL P0.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - The target controller to configure
  @param[in] IpChannel  - The target IP Channel to configure.

  @retval Nothing.
**/
void
ConfigB0SpidLowPowerCtl (
  IN MrcParameters *const MrcData,
  IN UINT32        Controller,
  IN UINT32        IpChannel
  )
{
  const MrcInput                       *Inputs;
  BOOLEAN                              SafeMode;
  UINT32                               Offset;
  MC0_CH0_CR_SPID_LOW_POWER_CTL_STRUCT SpidLowPowerCtl;

  Inputs        = &MrcData->Inputs;
  SafeMode      = (Inputs->SafeMode == TRUE);

  Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SPID_LOW_POWER_CTL_REG, MC1_CH0_CR_SPID_LOW_POWER_CTL_REG, Controller, MC0_CH1_CR_SPID_LOW_POWER_CTL_REG, IpChannel);
  SpidLowPowerCtl.Data = MrcReadCR (MrcData, Offset);
  SpidLowPowerCtl.Bits.ckevalid_enable = SafeMode ? 0 : 1;
  SpidLowPowerCtl.Bits.selfrefresh_latency = SafeMode ? 5 : 2;
  // Safe mode values are CR default
  if (!SafeMode) {
    SpidLowPowerCtl.Bits.raise_cke_after_exit_latency = 0;
    SpidLowPowerCtl.Bits.idle_length = 1;
    SpidLowPowerCtl.Bits.powerdown_length = 8;
    SpidLowPowerCtl.Bits.selfrefresh_length = 8;
  } else {
    SpidLowPowerCtl.Bits.powerdown_enable = 0;
    SpidLowPowerCtl.Bits.selfrefresh_enable = 0;
  }

  // SpidLowPowerCtl.Bits.idle_latency does not exist on TGL B0
  SpidLowPowerCtl.Bits.powerdown_latency = SafeMode ? 5 : 2;

  MrcWriteCR (MrcData, Offset, SpidLowPowerCtl.Data);
}

/**
  This function configures the memory controller scheduler.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
MrcSchedulerParametersConfig (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  MrcDebug        *Debug;
  MrcIntOutput    *MrcIntData;
  MrcChannelOut   *ChannelOut;
  MrcDimmOut      *DimmOut;
  MrcTiming       *Timing;
  MrcDdrType      DdrType;
  INT64           GetSetVal;
  INT64           Nto1Ratio;
  INT64           FreqPoint;
  INT64           CmdStretch;
  INT64           DramTechnology;
  INT64           tCKCKEH;
  INT64           tCSCKEH;
  INT64           CmdTristateDis;
  INT64           tCPDED;
  UINT32          Offset;
  UINT32          Channel;
  UINT32          IpChannel;
  UINT32          Controller;
  UINT32          tCL;
  UINT32          tCWL;
  UINT32          BurstLength;
  UINT8           AddressMirror;
  UINT8           X8Device;
  UINT8           Dimm;
  UINT8           Gear2;
  UINT8           Index;
  BOOLEAN         Lpddr4;
  BOOLEAN         Lpddr5;
  BOOLEAN         Lpddr;
  BOOLEAN         Ddr4;
  BOOLEAN         EnableMcOdtCtrl;
  BOOLEAN         SafeMode;
  MC0_MCDECS_CBIT_STRUCT                  McdecsCbit;
  MC0_CH0_CR_SCHED_CBIT_STRUCT            SchedCbit;
  MC0_CH0_CR_SCHED_SECOND_CBIT_STRUCT     SchedSecondCbit;
  MC0_CH0_CR_SCHED_THIRD_CBIT_STRUCT      SchedThirdCbit;
  MC0_CH0_CR_SC_WDBWM_STRUCT              ScWdbWm;
  MC0_SC_QOS_STRUCT                       ScQos;
  MC0_CH0_CR_SC_PCIT_STRUCT               ScPcit;
  MC0_CH0_CR_WCK_CONFIG_STRUCT            WckConfig;
  MC0_MCDECS_SECOND_CBIT_STRUCT           McdecsSecondCbit;
  MC0_CH0_CR_SC_BLOCKING_RULES_CFG_STRUCT ScBlockingRulesCfg;
  MC0_CH0_CR_SC_PH_THROTTLING_0_STRUCT    ScPhThrottling;
  MC0_CH0_CR_SC_PR_CNT_CONFIG_STRUCT      ScPrCntCfg;
  MC0_CH0_CR_SC_WPQ_THRESHOLD_STRUCT      ScWpqThreshold;
  MC0_QUEUE_CREDIT_C_STRUCT               QueueCredit;
  MC0_CH0_CR_WMM_READ_CONFIG_STRUCT       WmmReadConfig;
  MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_STRUCT   XarbBubbleInjCfg;

  MrcIntData    = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  DdrType       = Outputs->DdrType;
  AddressMirror = 0;
  X8Device      = 0;
  Lpddr4        = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5        = (DdrType == MRC_DDR_TYPE_LPDDR5);
  Ddr4          = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr         = Outputs->Lpddr;
  SafeMode      = (Inputs->SafeMode == TRUE);
  Gear2         = (Outputs->Gear2) ? 1 : 0; // Don't assume TRUE == 1 FALSE == 0.

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (!(MrcControllerExist (MrcData, Controller))) {
      continue;
    }
    Offset = OFFSET_CALC_CH (MC0_MCDECS_CBIT_REG, MC1_MCDECS_CBIT_REG, Controller);
    McdecsCbit.Data = MrcReadCR (MrcData, Offset);
    McdecsCbit.Bits.dis_single_ch_sr        = 0;
    McdecsCbit.Bits.dis_other_ch_stolen_ref = 0;
    MrcWriteCR (MrcData, Offset, McdecsCbit.Data);

    Offset = OFFSET_CALC_CH (MC0_BC_CR_SCHED_CBIT_REG, MC1_BC_CR_SCHED_CBIT_REG, Controller);
    SchedCbit.Data = 0;
    SchedCbit.Bits.dis_pt_it = Inputs->DisPgCloseIdleTimeout;

    // ZQ Command Serialize Options:
    //   DDR4 do not serialize ZQ commands.
    //   LPDDR4 is always serialized regardless of layout.
    SchedCbit.Bits.serialize_zq = (Lpddr5) ? 0 : Inputs->SharedZqPin;

    // Determine if we are enabling MC control over DRAM ODT pin.  LPDDR4 has no ODT pin,
    // so we do not enable MC control of the ODT pin for this technology.
    if (!Lpddr && Outputs->DramDqOdtEn) {
      EnableMcOdtCtrl = 1;
    } else {
      EnableMcOdtCtrl = 0;
    }
    // Field is a disable.  So use negative logic on the Enable variable.
    SchedCbit.Bits.dis_odt = !EnableMcOdtCtrl;
    SchedCbit.Bits.dis_clk_gate = (SafeMode ? 1 : 0);
    MrcWriteCrMulticast (MrcData, Offset, SchedCbit.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SCHED_CBIT = %08Xh\n", SchedCbit.Data);

    Offset = OFFSET_CALC_CH (MC0_BC_CR_SC_WDBWM_REG, MC1_BC_CR_SC_WDBWM_REG, Controller);
    ScWdbWm.Data = 0;
    ScWdbWm.Bits.WMM_entry_wm = 0x38;
    ScWdbWm.Bits.WMM_exit_wm = 0x28;
    ScWdbWm.Bits.WIM_wm = SafeMode ? 0x3c : 0x3b;
    ScWdbWm.Bits.Write_Isoc_CAS_count = SafeMode ? 0x40 : 0x20;
    ScWdbWm.Bits.Read_CAS_count   = SafeMode ? 0x10 : 0x14;
    ScWdbWm.Bits.Write_CAS_count  = SafeMode ? 0x10 : 0x14;
    ScWdbWm.Bits.Write_CAS_count_for_VC1  = SafeMode ? 0x40 : 0x20;
    ScWdbWm.Bits.Write_threshold_for_lp_read_bklr = SafeMode ? 0x16 : 0x14;
    MrcWriteCR64 (MrcData, Offset, ScWdbWm.Data);

    Offset = OFFSET_CALC_CH (MC0_SC_QOS_REG, MC1_SC_QOS_REG, Controller);
    ScQos.Data = 0;
    ScQos.Bits.Isoch_time_window = 0x1C2;
    ScQos.Bits.Write_starvation_window = 0x5A;
    ScQos.Bits.Read_starvation_window = 0x5A;
    ScQos.Bits.VC0_read_count = 0x16;
    ScQos.Bits.VC1_Read_starvation_en = 1;
    ScQos.Bits.Write_starvation_in_Isoc_en = 1;
    ScQos.Bits.Read_starvation_in_Isoch_en = 1;
    ScQos.Bits.VC0_counter_disable = 1;
    ScQos.Bits.Force_MCVC1Demote = 0;
    ScQos.Bits.MC_Ignore_VC1Demote = 0;
    MrcWriteCR64 (MrcData, Offset, ScQos.Data);

    Offset = OFFSET_CALC_CH (MC0_BC_CR_SCHED_SECOND_CBIT_REG, MC1_BC_CR_SCHED_SECOND_CBIT_REG, Controller);
    SchedSecondCbit.Data = 0;
    if (Inputs->A0) {
      SchedSecondCbit.Bits.disable_wr_on_SAGV_exit_for_DCC = 1;
    }
    if (SafeMode) {
      SchedSecondCbit.Bits.DisWrActThrottleOnAnyRead = 1;
    }
    SchedSecondCbit.Bits.enable_fdata_nak = 1;
    MrcWriteCrMulticast (MrcData, Offset, SchedSecondCbit.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SCHED_SECOND_CBIT = %08Xh\n", SchedSecondCbit.Data);

    Offset = OFFSET_CALC_CH (MC0_BC_CR_SC_PCIT_REG, MC1_BC_CR_SC_PCIT_REG, Controller);
    ScPcit.Data = 0;
    ScPcit.Bits.PCIT = 0x40;
    ScPcit.Bits.PCIT_GT = (SafeMode) ? 0 : 0x40;
    MrcWriteCrMulticast (MrcData, Offset, ScPcit.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SC_PCIT = %08Xh\n", ScPcit.Data);
    Offset = OFFSET_CALC_CH (MC0_QUEUE_CREDIT_C_REG, MC1_QUEUE_CREDIT_C_REG, Controller);
    QueueCredit.Data = MrcReadCR (MrcData, Offset);
    QueueCredit.Bits.RPQ_count = 33;
    MrcWriteCR (MrcData, Offset, QueueCredit.Data);

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if ((!MrcChannelExist (MrcData, Controller, Channel)) || IS_MC_SUB_CH (Lpddr, Channel)) {
        // For LPDDR4/5, only program register on even channels.
        continue;
      }
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      IpChannel = LP_IP_CH (Lpddr, Channel);
      // Set the Command N mode and Command Rate Limit
      // Command stretch:
      //   00 - 1N
      //   01 - 2N
      //   10 - 3N
      //   11 - N:1
      // DDR4 Gear2: When command stretch is set to 1N or 2N, MC will generate a command "like" 2N and 4N respectively
      Nto1Ratio = SafeMode ? 1 : 3;    // This was called Command Rate Limit before
      if (Lpddr) {
        CmdStretch = 0;
      } else {
        CmdStretch = (Outputs->Gear2) ? 1 : 2;     // DDR4: 3N Mode for Gear1, 2N Mode for Gear2
      }

      DramTechnology = DdrType;  // Matches MRC_DDR_TYPE_xxx encoding
      AddressMirror = 0;
      X8Device      = 0;
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (MrcRankExist (MrcData, Controller, Channel, Dimm * MAX_RANK_IN_DIMM)) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DimmOut->AddressMirrored) {
            AddressMirror |= (1 << Dimm);
          }
          if ((DimmOut->SdramWidth == 8) && (Ddr4)) {
            X8Device |= (1 << Dimm);
          }
        }
      }

      // @todo: Move this to MrcMemoryApi: MrcGetCpded()
      switch (DdrType) {
        case MRC_DDR_TYPE_LPDDR4:
        case MRC_DDR_TYPE_LPDDR5:
          // tCPDED is unused in CNL, MC is using tCKE for this parameter. Use default value (1)
          tCPDED = 1;
          break;

        case MRC_DDR_TYPE_DDR4:
          tCPDED = 4;
          break;

        default:
          MRC_DEBUG_ASSERT ((1 == 0), Debug, "Unsupported DDR Type: %u\n", DdrType);
          tCPDED = 0;
          break;
      }

      // Disable command tri state before training.
      CmdTristateDis = 1;

      // Use max values to be safe, because we don't know yet the final delta between CS/CK and CKE in DDRIO.
      tCKCKEH = 7;
      tCSCKEH = 7;

      FreqPoint = MrcIntData->SaGvPoint;

      GetSetVal = AddressMirror;
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccAddrMirror,     WriteNoCache | PrintValue, &GetSetVal);
      GetSetVal = X8Device;
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccX8Device,       WriteNoCache | PrintValue, &GetSetVal);
      GetSetVal = Gear2;
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccGear2,          WriteNoCache | PrintValue, &GetSetVal);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdGapRatio,    WriteNoCache | PrintValue, &Nto1Ratio);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccDramType,       WriteNoCache | PrintValue, &DramTechnology);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdStretch,     WriteNoCache | PrintValue, &CmdStretch);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccCmdTriStateDis, WriteNoCache | PrintValue, &CmdTristateDis);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccFreqPoint,      WriteNoCache | PrintValue, &FreqPoint);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctCPDED,          WriteNoCache | PrintValue, &tCPDED);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctCKCKEH,         WriteNoCache | PrintValue, &tCKCKEH);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMctCSCKEH,         WriteNoCache | PrintValue, &tCSCKEH);

      // Configure WCK parameters
      if (Lpddr5) {
        Timing = &ChannelOut->Timing[Inputs->MemoryProfile];
        tCL = Timing->tCL;
        tCWL = Timing->tCWL;
        BurstLength = Outputs->BurstLength;
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_WCK_CONFIG_REG, MC1_CH0_CR_WCK_CONFIG_REG, Controller, MC0_CH1_CR_WCK_CONFIG_REG, IpChannel);
        WckConfig.Data = MrcReadCR64 (MrcData, Offset);
        // Ranks must be present incrementally.  Thus we can check the bit mask > 1 to determine that we have more than 1 rank present.
        WckConfig.Bits.LP5_WCK_MODE = (SafeMode) ? 0 : (ChannelOut->ValidRankBitMask > 1) ? 1 : 2;
        WckConfig.Bits.tWCKOFF = 15;//4; // @todo Spec is unclear. 4:1
        WckConfig.Bits.WCK_OFF_IDLE_TIMER = 0x100; // @todo what is the value
        if (Inputs->A0) {
          WckConfig.Bits.WCK_MRR_SHORTER_BL_DIS = 1;
        }
        WckConfig.Bits.tWCKPST = 3; // To be modified based on the Mr10.Bits.WckPstLen
        // Table 130 - WCK2CK SYNC Off Timing
        // New WCK = RL + BL + RD (tWCKPST / tCK)
        // tWCKPST is 2.5 tWCK
        WckConfig.Bits.RD_WCK_ASYNC_GAP = (tCL + BurstLength) * 4;
        // New WCK = WL + BL + RD (tWCKPST / tCK)
        WckConfig.Bits.WR_WCK_ASYNC_GAP = (tCWL + BurstLength) * 4;
        MrcWriteCR64 (MrcData, Offset, WckConfig.Data);
      }

      // Set Opportunistic Read for Write Major Mode
      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_WMM_READ_CONFIG_REG, MC1_CH0_CR_WMM_READ_CONFIG_REG, Controller, MC0_CH1_CR_WMM_READ_CONFIG_REG, IpChannel);
      WmmReadConfig.Data = MrcReadCR (MrcData, Offset);
      if (!SafeMode) {
        WmmReadConfig.Bits.MAX_RPQ_CAS = 0x4;
      }
      MrcWriteCR (MrcData, Offset, WmmReadConfig.Data);

      for (Index = 0; Index < MRC_SC_PH_THROT_CR_COUNT; Index++) {
        ScPhThrottling.Data = 0;
        ScPhThrottling.Bits.loaded_same_rank        = ScPhThrottlingPor[Index][MrcSptLoadSameRank];
        ScPhThrottling.Bits.unloaded_same_rank      = ScPhThrottlingPor[Index][MrcSptUnloadedSameRank];
        ScPhThrottling.Bits.loaded_different_rank   = ScPhThrottlingPor[Index][MrcSptLoadedDiffRank];
        ScPhThrottling.Bits.unloaded_different_rank = ScPhThrottlingPor[Index][MrcSptUnloadedDiffRank];
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_PH_THROTTLING_0_REG, MC1_CH0_CR_SC_PH_THROTTLING_0_REG, Controller, MC0_CH1_CR_SC_PH_THROTTLING_0_REG, IpChannel);
        Offset += (MC0_CH0_CR_SC_PH_THROTTLING_1_REG - MC0_CH0_CR_SC_PH_THROTTLING_0_REG) * Index;
        MrcWriteCR (MrcData, Offset, ScPhThrottling.Data);
      }

      if (!SafeMode) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_PR_CNT_CONFIG_REG, MC1_CH0_CR_SC_PR_CNT_CONFIG_REG, Controller, MC0_CH1_CR_SC_PR_CNT_CONFIG_REG, IpChannel);
        ScPrCntCfg.Data = MrcReadCR64 (MrcData, Offset);
        ScPrCntCfg.Bits.Ring = 0x20;
        ScPrCntCfg.Bits.SA = 0x20;
        MrcWriteCR64 (MrcData, Offset, ScPrCntCfg.Data);

        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_WPQ_THRESHOLD_REG, MC1_CH0_CR_SC_WPQ_THRESHOLD_REG, Controller, MC0_CH1_CR_SC_WPQ_THRESHOLD_REG, IpChannel);
        ScWpqThreshold.Data = MrcReadCR (MrcData, Offset);
        ScWpqThreshold.Bits.Low_WM = 0x10;
        MrcWriteCR (MrcData, Offset, ScWpqThreshold.Data);

        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_XARB_CFG_BUBBLE_INJ_REG, MC1_CH0_CR_XARB_CFG_BUBBLE_INJ_REG, Controller, MC0_CH1_CR_XARB_CFG_BUBBLE_INJ_REG, IpChannel);
        XarbBubbleInjCfg.Data = MrcReadCR (MrcData, Offset);
        XarbBubbleInjCfg.Bits.bubble_inj_read_switch_num_cas = 0;
        XarbBubbleInjCfg.Bits.bubble_inj_write_switch_num_cas = 0;
        XarbBubbleInjCfg.Bits.bubble_inj_any_cas_switch_num_cas = 0;
        MrcWriteCR (MrcData, Offset, XarbBubbleInjCfg.Data);
      }

      if (Inputs->B0) {
        ConfigB0SpidLowPowerCtl (MrcData, Controller, IpChannel);
      } else { // csTglA0 or csTglP0
        ConfigSpidLowPowerCtl (MrcData, Controller, IpChannel);
      }

      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SCHED_THIRD_CBIT_REG, MC1_CH0_CR_SCHED_THIRD_CBIT_REG, Controller, MC0_CH1_CR_SCHED_THIRD_CBIT_REG, IpChannel);
      SchedThirdCbit.Data = MrcReadCR (MrcData, Offset);
      SchedThirdCbit.Bits.preempt_vc1_during_demote = 1;
      SchedThirdCbit.Bits.ipq_ignore_write_ph = 1;
      if (SafeMode) {
        SchedThirdCbit.Bits.dis_wdb_clk_gate = 1;
        SchedThirdCbit.Bits.dis_mnt_clk_gate = 1;
        SchedThirdCbit.Bits.dis_scheds_clk_gate = 1;
      }
      if (Lpddr4) {
        SchedThirdCbit.Bits.dis_cke_off_in_refresh = 1;
      }
      MrcWriteCR (MrcData, Offset, SchedThirdCbit.Data);

      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_BLOCKING_RULES_CFG_REG, MC1_CH0_CR_SC_BLOCKING_RULES_CFG_REG, Controller, MC0_CH1_CR_SC_BLOCKING_RULES_CFG_REG, IpChannel);
      ScBlockingRulesCfg.Data = MrcReadCR (MrcData, Offset);
      if (!SafeMode) {
        ScBlockingRulesCfg.Bits.med_wm_allowed_preempt_priorities = 7;
        ScBlockingRulesCfg.Bits.high_wm_allowed_preempt_priorities = 6;
      }
      MrcWriteCR (MrcData, Offset, ScBlockingRulesCfg.Data);

    } // Channel

    Offset = OFFSET_CALC_CH (MC0_MCDECS_SECOND_CBIT_REG, MC1_MCDECS_SECOND_CBIT_REG, Controller);
    McdecsSecondCbit.Data = MrcReadCR (MrcData, Offset);
    if (Inputs->A0) {
      McdecsSecondCbit.Bits.dis_spid_cmd_clk_gate = 0;
    }
    MrcWriteCR (MrcData, Offset, McdecsSecondCbit.Data);

  } // Controller
  if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
    MrcSetOdtMatrix (MrcData, 1);
  }

  return;
}

/**
  Set ODT Logic behavior for DDR4.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Profile - Behavior type. Currently Profile 1 is supported (DDR3-like)

  @retval none
**/
void
MrcSetOdtMatrix (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                    Profile
  )
{
  MrcDebug      *Debug;
  MrcOutput     *Outputs;
  MrcChannelOut *ChannelOut;
  INT64         EnableOdtMatrix;
  UINT32        Controller;
  UINT32        Offset;
  UINT8         Channel;
  UINT8         Dimm;
  MC0_CH0_CR_SC_ODT_MATRIX_STRUCT  OdtMatrix;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      OdtMatrix.Data = 0;
      switch (Profile) {
        case 1:
          // DDR3 like behavior: put OdtNom on rank 0 of the other DIMM
          // DDR4 difference is that ODT pin is not asserted on the target rank
          if (ChannelOut->DimmCount == 2) {
            OdtMatrix.Bits.Write_Rank_0 = 0x4;
            OdtMatrix.Bits.Write_Rank_1 = 0x4;
            OdtMatrix.Bits.Write_Rank_2 = 0x1;
            OdtMatrix.Bits.Write_Rank_3 = 0x1;
            OdtMatrix.Bits.Read_Rank_0  = 0x4;
            OdtMatrix.Bits.Read_Rank_1  = 0x4;
            OdtMatrix.Bits.Read_Rank_2  = 0x1;
            OdtMatrix.Bits.Read_Rank_3  = 0x1;
          } else {
            for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
              if (ChannelOut->Dimm[Dimm].RankInDimm > 1) {
                if (Dimm == 0) {
                  OdtMatrix.Bits.Write_Rank_0 = 0x1;
                  OdtMatrix.Bits.Write_Rank_1 = 0x2;
                } else {
                  OdtMatrix.Bits.Write_Rank_2 = 0x4;
                  OdtMatrix.Bits.Write_Rank_3 = 0x8;
                }
              }
            }
          }
          break;

        case 0:
          // set odt pins to zero.
          break;

        default:
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "MrcSetOdtMatrix : Unknown Odt Matrix Profile\n");
          break;
      } // switch Profile

      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_ODT_MATRIX_REG, MC0_CH0_CR_SC_ODT_MATRIX_REG, Controller, MC0_CH1_CR_SC_ODT_MATRIX_REG, Channel);
      MrcWriteCR (MrcData, Offset, OdtMatrix.Data);

      EnableOdtMatrix = 1;
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmMccEnableOdtMatrix, WriteCached, &EnableOdtMatrix);
    } // Channel
  } // Controller
}

/**
  Configure DDR4_1DPC performance feature.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
MrcConfigureDdr4OneDpc (
  IN MrcParameters *const MrcData
  )
{
// @todo
#if 0
  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  MrcDebug        *Debug;
  MrcChannelOut   *ChannelOut;
  MrcDimmOut      *DimmOut;
  UINT32          Channel;
  UINT32          Dimm;
  UINT32          DimmMask;
  UINT32          Offset;
  INT64           GetSetVal;
  INT64           GetSetEn;
  CH0_CR_SC_ODT_MATRIX_STRUCT  OdtMatrix;

  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  GetSetEn = 1;
  if (Outputs->DdrType != MRC_DDR_TYPE_DDR4) { // This is DDR4-only feature
    return;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (MrcData, 0, Channel)) {
      continue;
    }
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    if (ChannelOut->DimmCount != 1) {  // Must be 1DPC
      continue;
    }
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      DimmOut = &ChannelOut->Dimm[Dimm];
      if ((DimmOut->Status != DIMM_PRESENT) || (DimmOut->RankInDimm != 2)) { // Must be 2R DIMM
        continue;
      }
      DimmMask = 1 << Dimm;
      if ((Inputs->Ddr4OneDpc & DimmMask) == 0) { // If feature is disabled for this DIMM
        continue;
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%d DIMM%d: Enabling ddr4_1dpc\n", Channel, Dimm);
      // We have a single 2R DIMM on this channel and going to enable ddr4_1dpc feature on this channel
      GetSetVal = DimmMask;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccDdr4OneDpc, WriteNoCache | PrintValue, &GetSetVal);

      // 1. Rank Interleave must be on
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccRankInterleave,  WriteToCache | PrintValue, &GetSetEn);

      // 2. If Address Mirror enabled on this DIMM, must enable it on the other DIMM as well
      if (DimmOut->AddressMirrored) {
        GetSetVal = 3;
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccAddrMirror, WriteNoCache | PrintValue, &GetSetVal);
      }

      // 3. In TC_RDRD, TC_RDWR, TC_WRRD and TC_WRWR configure to the *_dd field the same value as to the _dr field.
      // @todo 2xMCs & IS_MC_SUB_CH (Lpddr, Channel)
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, ReadFromCache | PrintValue, &GetSetVal);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdd, WriteToCache  | PrintValue, &GetSetVal);

      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdr, ReadFromCache | PrintValue, &GetSetVal);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdd, WriteToCache  | PrintValue, &GetSetVal);

      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdr, ReadFromCache | PrintValue, &GetSetVal);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdd, WriteToCache  | PrintValue, &GetSetVal);

      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdr, ReadFromCache | PrintValue, &GetSetVal);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdd, WriteToCache  | PrintValue, &GetSetVal);

      // 4. In ODT_MATRIX configure the fields according to the rank occupancy (i.e. if ranks 0,1 exist set the matrix fields for ranks 0,3 instead)
      // Note that inside each field you still indicate which ODT pins are required to be set, so set bits 0,1 and not 0,3
      Offset = OFFSET_CALC_CH (CH0_CR_SC_ODT_MATRIX_REG, CH1_CR_SC_ODT_MATRIX_REG, Channel);
      OdtMatrix.Data = MrcReadCR (MrcData, Offset);
      if (Dimm == 0) {
        OdtMatrix.Bits.Write_Rank_3 = OdtMatrix.Bits.Write_Rank_1;
      } else { // DIMM1
        OdtMatrix.Bits.Write_Rank_0 = OdtMatrix.Bits.Write_Rank_2;
      }
      MrcWriteCR (MrcData, Offset, OdtMatrix.Data);

      // 5. MC_INIT_STATE.Rank_occupancy must be '1001'
      GetSetVal = 9;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccRankOccupancy, WriteToCache | PrintValue, &GetSetVal);

      // 6. If DIMM0: Roundtrip latency of Rank 3 should be set to the roundtrip latency of Rank 1
      //    If DIMM1: Roundtrip latency of Rank 0 should be set to the roundtrip latency of Rank 2
      if (Dimm == 0) {
        MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, 0, 1, RoundTripDelay, ReadFromCache | PrintValue, &GetSetVal);
        MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, 0, 3, RoundTripDelay, WriteToCache  | PrintValue, &GetSetVal);
      } else { // DIMM1
        MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, 0, 2, RoundTripDelay, ReadFromCache | PrintValue, &GetSetVal);
        MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, 0, 0, RoundTripDelay, WriteToCache  | PrintValue, &GetSetVal);
      }

      // 7. When MRH is used (DDR_MR_COMMNAD_0_0_0_MCHBAR), it should be programmed to access either rank 0 or rank 3 (and not 1 or 2).
      // See MrcRunMrh() and MrcDdr4PdaCmd()

      // 8. sc_gs_cfg_training.reset_on_command = 0
      // We don't use this feature, so it's stays zero

      // 9. sc_gs_cfg.x8_device should be the same for both DIMMs
      GetSetVal = (DimmOut->SdramWidth == 8) ? 3 : 0;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccX8Device, WriteNoCache | PrintValue, &GetSetVal);
    } // for Dimm
  } // for Channel
  MrcFlushRegisterCachedData (MrcData);
#endif
}

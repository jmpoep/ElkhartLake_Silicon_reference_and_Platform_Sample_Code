/** @file
  This module configures the memory controller scheduler.

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

//
// Include files
//
#include "MrcSchedulerParameters.h"
#include "MrcTimingConfiguration.h"
#include "MrcDdrCommon.h"
#include "MrcLpddr4.h"

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
  UINT8           AddressMirror;
  UINT8           X8Device;
  UINT8           Channel;
  UINT8           Dimm;
  BOOLEAN         Lpddr4;
  BOOLEAN         Ddr4;
  BOOLEAN         EnableMcOdtCtrl;
  MCDECS_CBIT_STRUCT                McdecsCbit;
  CH0_CR_SCHED_CBIT_STRUCT          SchedCbit;
  CH0_CR_SCHED_SECOND_CBIT_STRUCT   SchedSecondCbit;
  CH0_CR_SCHED_THIRD_CBIT_STRUCT    SchedThirdCbit;
  CH0_CR_SC_WDBWM_STRUCT            ScWdbWm;
  SC_QOS_STRUCT                     ScQos;
  CH0_CR_SC_PCIT_STRUCT             ScPcit;
  CH0_CR_SPID_LOW_POWER_CTL_STRUCT  SpidLowPowerCtl;
  MrcIntData    = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  DdrType       = Outputs->DdrType;
  AddressMirror = 0;
  X8Device      = 0;
  Lpddr4        = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4          = (DdrType == MRC_DDR_TYPE_DDR4);

  McdecsCbit.Data = MrcReadCR (MrcData, MCDECS_CBIT_REG);
  McdecsCbit.Bits.dis_single_ch_sr        = 0;
  McdecsCbit.Bits.dis_other_ch_stolen_ref = 0;
  if (Inputs->IclA0) {
    McdecsCbit.Bits.dis_iosf_sb_clk_gate = 1;
  }
  MrcWriteCR (MrcData, MCDECS_CBIT_REG, McdecsCbit.Data);

  SchedCbit.Data = 0;

  // ZQ Command Serialize Options:
  // DDR4 do not serialize ZQ commands.
  // LPDDR4 is always serialized regardless of layout.
  SchedCbit.Bits.serialize_zq = Inputs->SharedZqPin;

  // Determine if we are enabling MC control over DRAM ODT pin.  LPDDR4 has no ODT pin,
  // so we do not enable MC control of the ODT pin for this technology.
  if (!Lpddr4 && Outputs->DramDqOdtEn) {
    EnableMcOdtCtrl = 1;
  } else {
    EnableMcOdtCtrl = 0;
  }
  // Field is a disable.  So use negative logic on the Enable variable.
  SchedCbit.Bits.dis_odt = !EnableMcOdtCtrl;
  MrcWriteCrMulticast (MrcData, BC_CR_SCHED_CBIT_REG, SchedCbit.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SCHED_CBIT = %08Xh\n", SchedCbit.Data);

  ScWdbWm.Data = 0;
  ScWdbWm.Bits.WMM_entry_wm     = 0x38;
  ScWdbWm.Bits.WMM_exit_wm      = 0x28;
  ScWdbWm.Bits.WIM_wm           = 59;
//@todo for HALO  ScWdbWm.Bits.EDRAM_scrub_wm   = 0x38;
  ScWdbWm.Bits.Read_CAS_count   = 0x10;
  ScWdbWm.Bits.Write_CAS_count  = 0x10;
  ScWdbWm.Bits.Write_CAS_count_for_VC1  = 0x40;
  ScWdbWm.Bits.Write_threshold_for_lp_read_bklr = 0x16;
  MrcWriteCR64 (MrcData, BC_CR_SC_WDBWM_REG, ScWdbWm.Data);

  ScQos.Data = 0;
  ScQos.Bits.Isoch_time_window            = 0x1C2;
  ScQos.Bits.Write_starvation_window      = 0x5A;
  ScQos.Bits.Read_starvation_windowLow    = 0x0A;
  ScQos.Bits.Read_starvation_windowHigh   = 0x05;
  ScQos.Bits.VC0_read_count               = 0x16;
  ScQos.Bits.VC1_Read_starvation_en       = 1;
  ScQos.Bits.Write_starvation_in_Isoc_en  = 1;
  ScQos.Bits.Read_starvation_in_Isoch_en  = 1;
  ScQos.Bits.VC0_counter_disable          = 1;
  ScQos.Bits.Force_MCVC1Demote            = 0;
  ScQos.Bits.MC_Ignore_VC1Demote          = 0;
  MrcWriteCR64 (MrcData, SC_QOS_REG, ScQos.Data);

  ScPcit.Data = 0;
  ScPcit.Bits.PCIT = 0x40;
  ScPcit.Bits.PCIT_GT = 0x60;
  MrcWriteCrMulticast (MrcData, BC_CR_SC_PCIT_REG, ScPcit.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SC_PCIT = %08Xh\n", ScPcit.Data);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut = &Outputs->Controller[0].Channel[Channel];
    //
    // Set the Command N mode and Command Rate Limit
    // Command stretch:
    //   00 - 1N
    //   01 - 2N
    //   10 - 3N
    //   11 - N:1
    // DDR4 Gear2: When command stretch is set to 1N or 2N, MC will generate a command "like" 2N and 4N respectively
    Nto1Ratio = 3;    // This was called Command Rate Limit before
    if (Lpddr4) {
      CmdStretch = 0;     // 1N Mode for LPDDR4
    } else {
      CmdStretch = (Outputs->Gear2) ? 1 : 2;     // DDR4: 3N Mode for Gear1, 2N Mode for Gear2
    }

    DramTechnology = DdrType;  // Matches MRC_DDR_TYPE_xxx encoding
    AddressMirror = 0;
    X8Device      = 0;
    for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
      if (MrcRankInChannelExist (MrcData, Dimm * MAX_RANK_IN_DIMM, Channel)) {
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
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccAddrMirror,     WriteToCache | GSM_PRINT_VAL, &GetSetVal);
    GetSetVal = X8Device;
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccX8Device,       WriteToCache | GSM_PRINT_VAL, &GetSetVal);
    GetSetVal = Outputs->Gear2;
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccGear2,          WriteToCache | GSM_PRINT_VAL, &GetSetVal);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdGapRatio,    WriteToCache | GSM_PRINT_VAL, &Nto1Ratio);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccDramType,       WriteToCache | GSM_PRINT_VAL, &DramTechnology);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdStretch,     WriteToCache | GSM_PRINT_VAL, &CmdStretch);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccCmdTriStateDis, WriteToCache | GSM_PRINT_VAL, &CmdTristateDis);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccFreqPoint,      WriteToCache | GSM_PRINT_VAL, &FreqPoint);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctCPDED,          WriteToCache | GSM_PRINT_VAL, &tCPDED);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctCKCKEH,         WriteToCache | GSM_PRINT_VAL, &tCKCKEH);
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctCSCKEH,         WriteToCache | GSM_PRINT_VAL, &tCSCKEH);
    MrcFlushRegisterCachedData (MrcData);
    Offset = OFFSET_CALC_CH (CH0_CR_SPID_LOW_POWER_CTL_REG, CH1_CR_SPID_LOW_POWER_CTL_REG, Channel);
    SpidLowPowerCtl.Data = MrcReadCR (MrcData, Offset);

    SpidLowPowerCtl.Bits.idle_enable          = 1;
    SpidLowPowerCtl.Bits.powerdown_enable     = 1;
    SpidLowPowerCtl.Bits.selfrefresh_enable   = 1;
    SpidLowPowerCtl.Bits.idle_length          = 4;
    SpidLowPowerCtl.Bits.powerdown_length     = 1;
    SpidLowPowerCtl.Bits.selfrefresh_length   = 1;
    SpidLowPowerCtl.Bits.idle_latency         = 1;
    SpidLowPowerCtl.Bits.powerdown_latency    = 4;
    SpidLowPowerCtl.Bits.selfrefresh_latency  = 4;
    SpidLowPowerCtl.Bits.ckevalid_length      = 8;
    SpidLowPowerCtl.Bits.raise_cke_after_exit_latency = 0;
    MrcWriteCR(MrcData, Offset, SpidLowPowerCtl.Data);

    Offset = OFFSET_CALC_CH (CH0_CR_SCHED_SECOND_CBIT_REG, CH1_CR_SCHED_SECOND_CBIT_REG, Channel);
    SchedSecondCbit.Data = MrcReadCR (MrcData, Offset);
    SchedSecondCbit.Bits.dis_burst_ref_limit = 1;
    MrcWriteCR (MrcData, Offset, SchedSecondCbit.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u: SCHED_SECOND_CBIT = %08Xh\n", Channel, SchedSecondCbit.Data);

    Offset = OFFSET_CALC_CH (CH0_CR_SCHED_THIRD_CBIT_REG, CH1_CR_SCHED_THIRD_CBIT_REG, Channel);
    SchedThirdCbit.Data = MrcReadCR(MrcData, Offset);
    SchedThirdCbit.Bits.Read_threshold_for_lp_read_bklr = 0x8;
    SchedThirdCbit.Bits.pe_read_for_pe_blkr = 0x1;
    SchedThirdCbit.Bits.lp_read_blkr = 0x1;
    if (Lpddr4) {
      SchedThirdCbit.Bits.dis_cke_off_in_refresh = 1;
    }

    MrcWriteCR(MrcData, Offset, SchedThirdCbit.Data);

  } // for Channel


  return;
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
  CH0_CR_SC_ODT_MATRIX_STRUCT       OdtMatrix;
  CH0_CR_XARB_CFG_BUBBLE_INJ_STRUCT XarbCfgBubbleInj;

  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  GetSetEn = 1;
  if (Outputs->DdrType != MRC_DDR_TYPE_DDR4) { // This is DDR4-only feature
    return;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
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

      // Force CKE on all ranks, to avoid CKE going down during enabling of this feature
      GetSetVal = 0x0F;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmIocCkeOn, WriteNoCache | PrintValue, &GetSetVal);

      // Enable remapped rank in MC_INIT_STATE.Rank_occupancy, to avoid CKE going down during this flow
      GetSetVal = (Dimm == 0) ? 0x0B : 0x0D; // '1011' or '1101'
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccRankOccupancy, WriteNoCache | PrintValue, &GetSetVal);


      GetSetVal = DimmMask;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccDdr4OneDpc, WriteCached | PrintValue, &GetSetVal);

      // 1. MC_INIT_STATE.Rank_occupancy must be '1001'
      GetSetVal = 9;
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccRankOccupancy, WriteNoCache | PrintValue, &GetSetVal);

      // 2. Rank Interleave must be on
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccRankInterleave,  WriteToCache | PrintValue, &GetSetEn);

      // 3. If Address Mirror enabled on this DIMM, must enable it on the other DIMM as well
      if (DimmOut->AddressMirrored) {
        GetSetVal = 3;
        MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccAddrMirror, WriteToCache | PrintValue, &GetSetVal);
      }

      // 4. In TC_RDRD, TC_RDWR, TC_WRRD and TC_WRWR configure to the *_dd field the same value as to the _dr field.
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, ReadFromCache | PrintValue, &GetSetVal);
      if (Outputs->Gear2) {
        if (((Inputs->CpuModel == cmICL_ULX_ULT) && (Inputs->CpuStepping <= csIclB4)) ||
            ((Inputs->CpuModel == cmICL_DT_HALO) && (Inputs->CpuStepping == csIclP0))) {
          GetSetVal = MAX (GetSetVal, 8);
          MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdr, WriteCached | PrintValue, &GetSetVal);
        }
      }
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDRDdd, WriteCached   | PrintValue, &GetSetVal);

      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdr, ReadFromCache | PrintValue, &GetSetVal);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctRDWRdd, WriteCached   | PrintValue, &GetSetVal);

      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdr, ReadFromCache | PrintValue, &GetSetVal);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRRDdd, WriteCached   | PrintValue, &GetSetVal);

      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdr, ReadFromCache | PrintValue, &GetSetVal);
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMctWRWRdd, WriteCached   | PrintValue, &GetSetVal);

      // Must update the XARB bubble injector when TAT values change
      // This will read TAT values from the CRs, hence using WriteCached in the block above, to avoid extra register cache flush
      SetTcBubbleInjector (MrcData, Channel);

      // 5. In ODT_MATRIX configure the fields according to the rank occupancy (i.e. if ranks 0,1 exist set the matrix fields for ranks 0,3 instead)
      // Note that inside each field you still indicate which ODT pins are required to be set, so set bits 0,1 and not 0,3
      Offset = OFFSET_CALC_CH (CH0_CR_SC_ODT_MATRIX_REG, CH1_CR_SC_ODT_MATRIX_REG, Channel);
      OdtMatrix.Data = MrcReadCR (MrcData, Offset);
      if (Dimm == 0) {
        OdtMatrix.Bits.Write_Rank_3 = OdtMatrix.Bits.Write_Rank_1;
      } else { // DIMM1
        OdtMatrix.Bits.Write_Rank_0 = OdtMatrix.Bits.Write_Rank_2;
      }
      MrcWriteCR (MrcData, Offset, OdtMatrix.Data);

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
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccX8Device, WriteToCache | PrintValue, &GetSetVal);

      if (Inputs->IclA0) {
        Offset = OFFSET_CALC_CH (CH0_CR_XARB_CFG_BUBBLE_INJ_REG, CH1_CR_XARB_CFG_BUBBLE_INJ_REG, Channel);
        XarbCfgBubbleInj.Data = MrcReadCR (MrcData, Offset);
        XarbCfgBubbleInj.Bits.bubble_inj_enable_read_switch     = 0;
        XarbCfgBubbleInj.Bits.bubble_inj_enable_write_switch    = 0;
        XarbCfgBubbleInj.Bits.bubble_inj_enable_any_cas_switch  = 0;
        MrcWriteCR (MrcData, Offset, XarbCfgBubbleInj.Data);
      }
    } // for Dimm
  } // for Channel
  MrcFlushRegisterCachedData (MrcData);
}

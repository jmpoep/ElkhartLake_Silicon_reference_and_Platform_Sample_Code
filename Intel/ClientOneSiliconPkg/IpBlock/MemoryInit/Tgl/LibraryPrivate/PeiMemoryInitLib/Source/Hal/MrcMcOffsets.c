/** @file
  This file contains functions to get Memory Controller (MC) Offsets
  for timings, refresh, scheduler, and anything else MC specific.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include "McAddress.h"
#include "MrcCommon.h"

///
/// Public Functions
///
/**
  Function used to get the CR Offset for Memory Controller Timings.

  @param[in]  Group      - MC Timing Group being accessed.
  @param[in]  Socket     - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Controller - Memory controller in the processor socket (0-based).
  @param[in]  Channel    - DDR Channel Number within the memory controller (0-based).
  @param[in]  FreqIndex  - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
MrcGetMcTimingRegOffset (
  IN  MrcParameters *MrcData,
  IN  GSM_GT        Group,
  IN  UINT32        Socket,
  IN  UINT32        Controller,
  IN  UINT32        Channel,
  IN  UINT32        FreqIndex
  )
{
  UINT32    Offset;
  UINT8     MaxChannel;

  Offset     = MRC_UINT32_MAX;
  MaxChannel = 2; // MAX_MC_CHANNEL


  switch (Group) {
    case GsmMctRCD:
    case GsmMctRP:
    case GsmMctRPabExt:
    case GsmMctRAS:
    case GsmMctRDPRE:
    case GsmMctPPD:
    case GsmMctWRPRE:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_PRE_REG, MC1_CH0_CR_TC_PRE_REG, Controller, MC0_CH1_CR_TC_PRE_REG, Channel);
      }
      break;

    case GsmMctRFCpb:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_PBR_REG, MC1_CH0_CR_SC_PBR_REG, Controller, MC0_CH1_CR_SC_PBR_REG, Channel);
      }
      break;

    case GsmMctFAW:
    case GsmMctRRDsg:
    case GsmMctRRDdg:
    case GsmMctLpDeratingExt:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_ACT_REG, MC1_CH0_CR_TC_ACT_REG, Controller, MC0_CH1_CR_TC_ACT_REG, Channel);
      }
      break;

    case GsmMctOdtRdDuration:
    case GsmMctOdtRdDelay:
    case GsmMctWrEarlyOdt:
    case GsmMctOdtWrDuration:
    case GsmMctOdtWrDelay:
    case GsmMctCL:
    case GsmMctCWL:
    case GsmMctAONPD:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_ODT_REG, MC1_CH0_CR_TC_ODT_REG, Controller, MC0_CH1_CR_TC_ODT_REG, Channel);
      }
      break;

    case GsmMctRDRDsg:
    case GsmMctRDRDdg:
    case GsmMctRDRDdr:
    case GsmMctRDRDdd:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_RDRD_REG, MC1_CH0_CR_TC_RDRD_REG, Controller, MC0_CH1_CR_TC_RDRD_REG, Channel);
      }
      break;

    case GsmMctRDWRsg:
    case GsmMctRDWRdg:
    case GsmMctRDWRdr:
    case GsmMctRDWRdd:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_RDWR_REG, MC1_CH0_CR_TC_RDWR_REG, Controller, MC0_CH1_CR_TC_RDWR_REG, Channel);
      }
      break;

    case GsmMctWRRDsg:
    case GsmMctWRRDdg:
    case GsmMctWRRDdr:
    case GsmMctWRRDdd:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_WRRD_REG, MC1_CH0_CR_TC_WRRD_REG, Controller, MC0_CH1_CR_TC_WRRD_REG, Channel);
      }
      break;

    case GsmMctWRWRsg:
    case GsmMctWRWRdg:
    case GsmMctWRWRdr:
    case GsmMctWRWRdd:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_WRWR_REG, MC1_CH0_CR_TC_WRWR_REG, Controller, MC0_CH1_CR_TC_WRWR_REG, Channel);
      }
      break;

    case GsmMctCKE:
    case GsmMctXP:
    case GsmMctXPDLL:
    case GsmMctPRPDEN:
    case GsmMctRDPDEN:
    case GsmMctWRPDEN:
    case GsmMctCA2CS:
    case GsmMctCSL:
    case GsmMctCSH:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_PWRDN_REG, MC1_CH0_CR_TC_PWRDN_REG, Controller, MC0_CH1_CR_TC_PWRDN_REG, Channel);
      }
      break;

    case GsmMctXSDLL:
    case GsmMctZQOPER:
    case GsmMctMOD:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_SRFTP_REG, MC1_CH0_CR_TC_SRFTP_REG, Controller, MC0_CH1_CR_TC_SRFTP_REG, Channel);
      }
      break;

    case GsmMctXSR:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_SREXITTP_REG, MC1_CH0_CR_TC_SREXITTP_REG, Controller, MC0_CH1_CR_TC_SREXITTP_REG, Channel);
      }
      break;

    case GsmMctZQCAL:
    case GsmMctZQCS:
    case GsmMctZQCSPeriod:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_ZQCAL_REG, MC1_CH0_CR_TC_ZQCAL_REG, Controller, MC0_CH1_CR_TC_ZQCAL_REG, Channel);
      }
      break;

    case GsmMctCPDED:
    case GsmMctCAL:
    case GsmMctCKCKEH:
    case GsmMctCSCKEH:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_GS_CFG_REG, MC1_CH0_CR_SC_GS_CFG_REG, Controller, MC0_CH1_CR_SC_GS_CFG_REG, Channel);
      }
      break;

    case GsmMctSrIdle:
      Offset = OFFSET_CALC_CH (MC0_PM_SREF_CONFIG_REG, MC1_PM_SREF_CONFIG_REG, Controller);
      break;

    case GsmMctREFI:
    case GsmMctRFC:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_RFTP_REG, MC1_CH0_CR_TC_RFTP_REG, Controller, MC0_CH1_CR_TC_RFTP_REG, Channel);
      }
      break;

    case GsmMctOrefRi:
    case GsmMctRefreshHpWm:
    case GsmMctRefreshPanicWm:
    case GsmMctREFIx9:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_RFP_REG, MC1_CH0_CR_TC_RFP_REG, Controller, MC0_CH1_CR_TC_RFP_REG, Channel);
      }
      break;

    case GsmMctCWLAdd:
    case GsmMctCWLDec:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_WR_DELAY_REG, MC1_CH0_CR_SC_WR_DELAY_REG, Controller, MC0_CH1_CR_SC_WR_DELAY_REG, Channel);
      }
      break;

    default:
      break;
  }

  return Offset;
}

/**
  Function used to get the CR Offset for Memory Controller Configuration Settings.

  @param[in]  Group      - MC Timing Group being accessed.
  @param[in]  Socket     - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Controller - Memory controller in the processor socket (0-based).
  @param[in]  Channel    - DDR Channel Number within the memory controller (0-based).
  @param[in]  FreqIndex  - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
MrcGetMcConfigRegOffset (
  IN  MrcParameters *MrcData,
  IN  GSM_GT        Group,
  IN  UINT32        Socket,
  IN  UINT32        Controller,
  IN  UINT32        Channel,
  IN  UINT32        FreqIndex
  )
{
  UINT32    Offset;
  UINT8     MaxChannel;
  MrcInput  *Inputs;

  Offset     = MRC_UINT32_MAX;
  MaxChannel = 2; // MAX_MC_CHANNEL

  Inputs = &MrcData->Inputs;

  switch (Group) {
    case GsmMccLp4FifoRdWr:
    case GsmMccCpgcInOrder:
    case GsmMccCadbEnable:
    case GsmMccDeselectEnable:
    case GsmMccBusRetainOnBubble:
    case GsmMccMaskCs:
    case GsmMccIgnoreCke:
    case GsmMccResetDelay:
    case GsmMccResetOnCmd:
    case GsmMccBlockXarb:
    case GsmMccCmdTriStateDisTrain:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_GS_CFG_TRAINING_REG, MC1_CH0_CR_SC_GS_CFG_TRAINING_REG , Controller, MC0_CH1_CR_SC_GS_CFG_TRAINING_REG, Channel);
      }
      break;

    case GsmMccDramType:
    case GsmMccCmdStretch:
    case GsmMccCmdGapRatio:
    case GsmMccAddrMirror:
    case GsmMccCmdTriStateDis:
    case GsmMccFreqPoint:
    case GsmMccEnableOdtMatrix:
    case GsmMccX8Device:
    case GsmMccGear2:
    case GsmMccDdr4OneDpc:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_GS_CFG_REG, MC1_CH0_CR_SC_GS_CFG_REG, Controller, MC0_CH1_CR_SC_GS_CFG_REG, Channel);
      }
      break;

    case GsmMccAddrDecodeDdrType:
    case GsmMccStackedMode:
    case GsmMccStackChMap:
    case GsmMccLChannelMap:
    case GsmMccSChannelSize:
    case GsmMccStackedChHash:
    case GsmMccChWidth:
    case GsmMccHalfCachelineMode:
      Offset = OFFSET_CALC_CH (MC0_MAD_INTER_CHANNEL_REG, MC1_MAD_INTER_CHANNEL_REG, Controller);
      break;

    case GsmMccLDimmMap:
    case GsmMccRankInterleave:
    case GsmMccEnhancedInterleave:
    case GsmMccEccMode:
      // No Broadcast supported for this.
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_MAD_INTRA_CH0_REG, MC1_MAD_INTRA_CH0_REG, Controller, MC0_MAD_INTRA_CH1_REG, Channel);
      }
      break;

    case GsmMccLDimmSize:
    case GsmMccLDimmDramWidth:
    case GsmMccLDimmRankCnt:
    case GsmMccSDimmSize:
    case GsmMccSDimmDramWidth:
    case GsmMccSDimmRankCnt:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_MAD_DIMM_CH0_REG, MC1_MAD_DIMM_CH0_REG, Controller, MC0_MAD_DIMM_CH1_REG, Channel);
      }
      break;

    case GsmMccSaveFreqPoint:
    case GsmMccEnableRefresh:
    case GsmMccMcInitDoneAck:
    case GsmMccMrcDone:
    case GsmMccEnableDclk:
    case GsmMccPureSrx:
    case GsmMccDdrReset:
    case GsmMccSafeSr:
      if (Inputs->CpuModel == cmTGL_DT_HALO) {
        Offset = OFFSET_CALC_CH (MC0_MC_INIT_STATE_G_P0_REG, MC1_MC_INIT_STATE_G_P0_REG, Controller);
      } else {
        Offset = OFFSET_CALC_CH (MC0_MC_INIT_STATE_G_REG, MC1_MC_INIT_STATE_G_REG, Controller);
      }
      break;

    case GsmMccEnableSr:
      Offset = OFFSET_CALC_CH (MC0_PM_SREF_CONFIG_REG, MC1_PM_SREF_CONFIG_REG, Controller);
      break;

    case GsmMccRankOccupancy:
    case GsmMccMcSrx:
      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MC_INIT_STATE_REG, MC1_CH0_CR_MC_INIT_STATE_REG, Controller, MC0_CH1_CR_MC_INIT_STATE_REG, Channel);
      break;

    case GsmMccRefInterval:
    case GsmMccRefStaggerEn:
    case GsmMccRefStaggerMode:
    case GsmMccDisableStolenRefresh:
    case GsmMccEnRefTypeDisplay:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MC_REFRESH_STAGGER_REG, MC1_CH0_CR_MC_REFRESH_STAGGER_REG, Controller, MC0_CH1_CR_MC_REFRESH_STAGGER_REG, Channel);
      }
      break;

    case GsmMccHashMask:
    case GsmMccLsbMaskBit:
    case GsmMccHashMode:
      Offset = OFFSET_CALC_CH (MC0_CHANNEL_HASH_REG, MC1_CHANNEL_HASH_REG, Controller);
      break;

    case GsmMccMr2Shadow:
    case GsmMccSrtAvail:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_TC_MR2_SHADDOW_REG, MC1_CH0_CR_TC_MR2_SHADDOW_REG, Controller, MC0_CH1_CR_TC_MR2_SHADDOW_REG, Channel);
      }
      break;

    case GsmMccDisableCkTristate:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SCHED_SECOND_CBIT_REG, MC1_CH0_CR_SCHED_SECOND_CBIT_REG, Controller, MC0_CH1_CR_SCHED_SECOND_CBIT_REG, Channel);
      }
      break;

    case GsmMccPbrDis:
    case GsmMccPbrDisOnHot:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_PBR_REG, MC1_CH0_CR_SC_PBR_REG, Controller, MC0_CH1_CR_SC_PBR_REG, Channel);
      }
      break;

    case GsmMccOdtOverride:
    case GsmMccOdtOn:
    case GsmMccMprTrainDdrOn:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG, MC1_CH0_CR_REUT_CH_MISC_ODT_CTRL_REG, Controller, MC0_CH1_CR_REUT_CH_MISC_ODT_CTRL_REG, Channel);
      }
      break;

    case GsmMccCkeOverride:
    case GsmMccCkeOn:
      if (Channel < MaxChannel) {
        Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG, MC1_CH0_CR_REUT_CH_MISC_CKE_CTRL_REG, Controller, MC0_CH1_CR_REUT_CH_MISC_CKE_CTRL_REG, Channel);
      }
      break;

    default:
      break;
  }

  return Offset;
}


/**
  Function used to get the CR Offset for Common Memory Interface Settings.

  @param[in]  Group     - CMI Group being accessed.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the system (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
MrcGetCmiRegOffset (
  IN  MrcParameters *MrcData,
  IN  GSM_GT        Group,
  IN  UINT32        Socket,
  IN  UINT32        Channel,
  IN  UINT32        FreqIndex
  )
{
  UINT32 Offset;

  Offset = MRC_UINT32_MAX;

  switch (Group) {
    case GsmCmiHashMask:
    case GsmCmiLsbMaskBit:
    case GsmCmiHashMode:
      Offset = CMI_MEMORY_SLICE_HASH_REG;
      break;

    case GsmCmiStackedMode:
    case GsmCmiStackMsMap:
    case GsmCmiStackedMsHash:
    case GsmCmiSMadSliceSize:
    case GsmCmiLMadSliceMap:
      Offset = CMI_MAD_SLICE_REG;
      break;

    default:
      break;
  }

  return Offset;
}

/**
  This function returns the offset for the MRS FSM Control register.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  Controller  - Controller index.
  @param[in]  Channel     - Channel index.

  @retval Register Offset.
**/
UINT32
MrcGetMrsFsmCtlOffset (
  IN  MrcParameters *MrcData,
  IN  UINT32        Controller,
  IN  UINT32        Channel
  )
{
  UINT32 Offset;

  Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MRS_FSM_CONTROL_REG, MC1_CH0_CR_MRS_FSM_CONTROL_REG, Controller, MC0_CH1_CR_MRS_FSM_CONTROL_REG, Channel);

  return Offset;
}

/**
  This function returns the offset for MRS run FSM Control register.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  Controller  - Controller index.
  @param[in]  Channel     - Channel index.

  @retval Register Offset.
**/
UINT32
MrcGetMrsRunFsmOffset (
  IN  MrcParameters *MrcData,
  IN  UINT32        Controller,
  IN  UINT32        Channel
  )
{
  UINT32 Offset;

  Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_MRS_FSM_RUN_REG, MC1_CH0_CR_MRS_FSM_RUN_REG, Controller, MC0_CH1_CR_MRS_FSM_RUN_REG, Channel);

  return Offset;
}

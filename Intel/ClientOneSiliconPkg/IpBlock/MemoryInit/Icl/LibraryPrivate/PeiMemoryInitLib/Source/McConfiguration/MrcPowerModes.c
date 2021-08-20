/** @file
  This module configures the memory controller power modes.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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

///
/// Include files
///
#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcPowerModes.h"
#include "MrcDebugPrint.h"
#include "MrcSpdProcessing.h"

GLOBAL_REMOVE_IF_UNREFERENCED const DdrPowerWeightEntry Ddr4PowerWeightTable2[] = {
  {{{0      , 0    , 0          , 0       , 0      , 0    , 0        , 0        , 0}}, 5, 0xC8, 0x96, 0x8F, 0x7, 0x0B, 0x00}
};

/**
  This function configures the power down control register.

  @param[in]  - MrcData - The MRC global data.

  @retval - Nothing
**/
void
MrcPowerDownConfig (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput  *Inputs;
  MrcOutput       *Outputs;
  MrcCpuModel     CpuModel;
  BOOLEAN         UlxUlt;
  BOOLEAN         Lpddr;
  CH0_CR_PM_PDWN_CONFIG_STRUCT PmPdwnConfig;

  Inputs    = &MrcData->Inputs;
  Outputs   = &MrcData->Outputs;
  CpuModel  = Inputs->CpuModel;

  UlxUlt = (CpuModel == cmICL_ULX_ULT);
  Lpddr  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);

  PmPdwnConfig.Data                   = 0;
  PmPdwnConfig.Bits.PDWN_idle_counter = (UlxUlt) ? PDWN_IDLE_COUNTER_ULX_ULT : PDWN_IDLE_COUNTER_DT_HALO;

  if (Inputs->PwdwnIdleCounter != 0) {  // 0 means AUTO
    PmPdwnConfig.Bits.PDWN_idle_counter = Inputs->PwdwnIdleCounter;
  }

  if (Lpddr) {
    PmPdwnConfig.Bits.dis_cke_tt      = Inputs->ThrtCkeMinDefeatLpddr;
    PmPdwnConfig.Bits.TT_idle_counter = Inputs->ThrtCkeMinTmrLpddr;
  } else {
    PmPdwnConfig.Bits.dis_cke_tt      = Inputs->ThrtCkeMinDefeat;
    PmPdwnConfig.Bits.TT_idle_counter = Inputs->ThrtCkeMinTmr;
  }

  switch (Inputs->PowerDownMode) {
    case pdmNoPowerDown:
      break;

    case pdmAPD:
      PmPdwnConfig.Bits.APD = 1;
      break;

    case pdmPPDDLLOFF:
      PmPdwnConfig.Bits.PPD = 1;
      PmPdwnConfig.Bits.Slow_Exit = 1;
      break;

    case pdmAuto:
      PmPdwnConfig.Bits.PPD = 1;
      if (!Lpddr && UlxUlt) {
        // Slow Exit (DLL Off) on ULX/ULT
        // Fast Exit on DT/Halo
        PmPdwnConfig.Bits.Slow_Exit = 1;
      }
      break;
  }

  MrcWriteCR (MrcData, BC_CR_PM_PDWN_CONFIG_REG, PmPdwnConfig.Data);
  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "PM_PDWN_CONFIG: 0x%Xh\n", PmPdwnConfig.Data);

  return;
}

/**
  This functions sets power weight, scale factor and Channel
  Power Floor values from lookup table based on DIMMs present in
  the system.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
MrcStatus
MrcPowerWeight (
  IN     MrcParameters *const MrcData
  )
{
  const MrcInput               *Inputs;
  MrcDebug                     *Debug;
  const MRC_FUNCTION           *MrcCall;
  MrcOutput                    *Outputs;
  MrcControllerOut             *ControllerOut;
  MrcChannelOut                *ChannelOut;
  MrcDimmOut                   *DimmOut;
  UINT8                        Channel;
  UINT8                        Dimm;
  const DdrPowerWeightEntry    *DdrPwt[3];
  UINT8                        PwtSetPtr;
  UINT16                       PwtSize[3];
  PowerWeightInputs            DimmPwt;
  UINT8                        i;
  UINT16                       j;
  BOOLEAN                      DimmEntryFound;
  BOOLEAN                      Ddr4;
  UINT8                        SfDiff;
  UINT8                        MinScaleFactor;
  UINT8                        ScaleFactor[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT8                        ChPwrFloor[MAX_CHANNEL][MAX_DIMMS_IN_CHANNEL];
  UINT32                       Offset;
  CH0_CR_PM_DIMM_RD_ENERGY_STRUCT            PmDimmRdEnergy[MAX_CHANNEL];
  CH0_CR_PM_DIMM_WR_ENERGY_STRUCT            PmDimmWrEnergy[MAX_CHANNEL];
  CH0_CR_PM_DIMM_ACT_ENERGY_STRUCT           PmDimmActEnergy[MAX_CHANNEL];
  CH0_CR_PM_DIMM_PD_ENERGY_STRUCT            PmDimmPdEnergy[MAX_CHANNEL];
  CH0_CR_PM_DIMM_IDLE_ENERGY_STRUCT          PmDimmIdleEnergy[MAX_CHANNEL];
  DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_STRUCT    DdrRaplChannelPowerFloor;

  Inputs                        = &MrcData->Inputs;
  MrcCall                       = Inputs->Call.Func;
  Outputs                       = &MrcData->Outputs;
  Debug                         = &Outputs->Debug;
  ControllerOut                 = &Outputs->Controller[0];
  MinScaleFactor                = (UINT8) ~0;
  DdrRaplChannelPowerFloor.Data = 0;

  Ddr4   = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);

  MrcCall->MrcSetMem ((UINT8 *) PmDimmRdEnergy, sizeof (PmDimmRdEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmWrEnergy, sizeof (PmDimmWrEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmActEnergy, sizeof (PmDimmActEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmPdEnergy, sizeof (PmDimmPdEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) PmDimmIdleEnergy, sizeof (PmDimmIdleEnergy), 0);
  MrcCall->MrcSetMem ((UINT8 *) ScaleFactor, sizeof (ScaleFactor), 0xFF);
  MrcCall->MrcSetMem ((UINT8 *) ChPwrFloor, sizeof (ChPwrFloor), 0);

  DdrPwt[0]    = NULL;
  PwtSize[0]   = 0;
  DdrPwt[1]    = NULL;
  PwtSize[1]   = 0;
  DdrPwt[2]    = Ddr4PowerWeightTable2;
  PwtSize[2]   = ARRAY_COUNT (Ddr4PowerWeightTable2);
  PwtSetPtr    = 2;

  if (Inputs->MemoryProfile != USER_PROFILE) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      //
      // Collect Channel level data for lookup
      //
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmOut = &ChannelOut->Dimm[Dimm];
        if (DimmOut->Status != DIMM_PRESENT) {
          continue;
        }

        DimmPwt.Data = 0;
        //
        // Collect DIMM level data for lookup
        //

        if (Inputs->MemoryProfile >= MAX_PROFILE) {
          return mrcWrongInputParameter;        // VddVoltage[] is out of range, error on input->MemoryProfile
        }
        switch (Outputs->VddVoltage[Inputs->MemoryProfile]) {
          case VDD_1_20:
            DimmPwt.Bits.Vddq = VDD_120;
            break;

          case VDD_1_35:
            DimmPwt.Bits.Vddq = VDD_135;
            break;

          case VDD_1_50:
            DimmPwt.Bits.Vddq = VDD_150;
            break;

          default:
            DimmPwt.Bits.Vddq = VDD_OTHER;
            PwtSetPtr = MAX (2, PwtSetPtr);
            break;
        }

        DimmPwt.Bits.Ecc         = DimmOut->EccSupport;
        DimmPwt.Bits.DimmType    = DimmOut->ModuleType;
        if (DimmOut->ModuleType == SoUDimmEccMemoryPackageDdr4) {
          DimmPwt.Bits.DimmType = SoDimmMemoryPackage;  // The table checks for UDIMM vs. SO-DIMM, so treat ECC SO-DIMM as SO-DIMM
        }
        DimmPwt.Bits.DeviceWidth = DimmOut->SdramWidthIndex;
        DimmPwt.Bits.NumOfRanks  = DimmOut->RankInDimm;
        DimmPwt.Bits.Dpc         = ChannelOut->DimmCount;

        switch (Outputs->Frequency) {
          case f1067:
            DimmPwt.Bits.Frequency = FREQ_1067;
            break;

          case f1333:
            DimmPwt.Bits.Frequency = FREQ_1333;
            break;

          case f1600:
            DimmPwt.Bits.Frequency = FREQ_1600;
            break;

          case f1867:
            DimmPwt.Bits.Frequency = FREQ_1867;
            break;

          case f2133:
            DimmPwt.Bits.Frequency = FREQ_2133;
            break;

          default:
            PwtSetPtr = MAX (2, PwtSetPtr);
            break;
        }

        DimmPwt.Bits.DramDensity = DimmOut->DensityIndex;

        //
        // Search lookup table for DIMM entry
        //
        DimmEntryFound = FALSE;

        for (i = PwtSetPtr; i < 3; i++) {
          if (DimmEntryFound) {
            break;
          }
          if (i == 1) {
            DimmPwt.Bits.Dpc  = 0;
          } else if (i == 2) {
            DimmPwt.Data = 0;
          }
          for (j = 0; j < PwtSize[i]; j++) {
            if (Ddr4) {
              if (DimmPwt.Data == DdrPwt[i][j].PwInput.Data) {
                PmDimmRdEnergy[Channel].Data8[Dimm]   = DdrPwt[i][j].RdCr;
                PmDimmWrEnergy[Channel].Data8[Dimm]   = DdrPwt[i][j].WrCr;
                PmDimmActEnergy[Channel].Data8[Dimm]  = DdrPwt[i][j].ActCr;
                PmDimmPdEnergy[Channel].Data8[Dimm]   = DdrPwt[i][j].CkeL;
                PmDimmIdleEnergy[Channel].Data8[Dimm] = DdrPwt[i][j].CkeH;
                ScaleFactor[Channel][Dimm]            = DdrPwt[i][j].ScaleFactor;
                ChPwrFloor[Channel][Dimm]             = DdrPwt[i][j].ChPwrFloor;
                MinScaleFactor                        = MIN (MinScaleFactor, ScaleFactor[Channel][Dimm]);
                DimmEntryFound                        = TRUE;
                break;
              }
            }
          }
        }
      }
    }

    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmOut = &ChannelOut->Dimm[Dimm];
        if (DimmOut->Status != DIMM_PRESENT) {
          continue;
        }
        //
        // Set Scale Factor of all DIMMs to lowest Scale Factor and adjust weights accordingly.
        //
        if ((SfDiff = ScaleFactor[Channel][Dimm] - MinScaleFactor) > 0) {
          PmDimmRdEnergy[Channel].Data8[Dimm]   = (PmDimmRdEnergy[Channel].Data8[Dimm] + 1) >> SfDiff;
          PmDimmWrEnergy[Channel].Data8[Dimm]   = (PmDimmWrEnergy[Channel].Data8[Dimm] + 1) >> SfDiff;
          PmDimmActEnergy[Channel].Data8[Dimm]  = (PmDimmActEnergy[Channel].Data8[Dimm] + 1) >> SfDiff;
          PmDimmPdEnergy[Channel].Data8[Dimm]   = (PmDimmPdEnergy[Channel].Data8[Dimm] + 1) >> SfDiff;
          PmDimmIdleEnergy[Channel].Data8[Dimm] = (PmDimmIdleEnergy[Channel].Data8[Dimm] + 1) >> SfDiff;
        }
      }
      //
      // Set RAPL Channel Power Floor to average of DIMMs rounded up to nearest integer multiple of 0.125W (which is
      // going to be a multiple of 8 for Channel Power Floor Register).
      //
      if (ChannelOut->DimmCount > 1) {
        if (ChPwrFloor[Channel][0] != ChPwrFloor[Channel][1]) {
          ChPwrFloor[Channel][0] = (ChPwrFloor[Channel][0] + ChPwrFloor[Channel][1] + 1) / 2;
          if (ChPwrFloor[Channel][0] < 0xF8) {
            if ((ChPwrFloor[Channel][0] % 8) != 0) {
              ChPwrFloor[Channel][0] = ChPwrFloor[Channel][0] + (8 - (ChPwrFloor[Channel][0] % 8));
            }
          } else { // No more 8-bit mulitples of 8 after 0xF8, must round down.
            ChPwrFloor[Channel][0] = 0xF8;
          }
        }
      } else {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          ChPwrFloor[Channel][0] = MAX (ChPwrFloor[Channel][0], ChPwrFloor[Channel][Dimm]);
        }
      }

      //
      // Apply power weights
      //
      Offset = OFFSET_CALC_CH (CH0_CR_PM_DIMM_RD_ENERGY_REG, CH1_CR_PM_DIMM_RD_ENERGY_REG, Channel);
      MrcWriteCR (MrcData, Offset, PmDimmRdEnergy[Channel].Data);
      Offset = OFFSET_CALC_CH (CH0_CR_PM_DIMM_WR_ENERGY_REG, CH1_CR_PM_DIMM_WR_ENERGY_REG, Channel);
      MrcWriteCR (MrcData, Offset, PmDimmWrEnergy[Channel].Data);
      Offset = OFFSET_CALC_CH (CH0_CR_PM_DIMM_ACT_ENERGY_REG, CH1_CR_PM_DIMM_ACT_ENERGY_REG, Channel);
      MrcWriteCR (MrcData, Offset, PmDimmActEnergy[Channel].Data);
      Offset = OFFSET_CALC_CH (CH0_CR_PM_DIMM_PD_ENERGY_REG, CH1_CR_PM_DIMM_PD_ENERGY_REG, Channel);
      MrcWriteCR (MrcData, Offset, PmDimmPdEnergy[Channel].Data);
      Offset = OFFSET_CALC_CH (CH0_CR_PM_DIMM_IDLE_ENERGY_REG, CH1_CR_PM_DIMM_IDLE_ENERGY_REG, Channel);
      MrcWriteCR (MrcData, Offset, PmDimmIdleEnergy[Channel].Data);
    }
    DdrRaplChannelPowerFloor.Bits.CH0 = ChPwrFloor[0][0];
    DdrRaplChannelPowerFloor.Bits.CH1 = ChPwrFloor[1][0];
    MrcWriteCR (MrcData, DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_REG, DdrRaplChannelPowerFloor.Data);
    MrcWriteCR (MrcData, DDR_ENERGY_SCALEFACTOR_PCU_REG, (UINT32) MinScaleFactor);

#ifdef MRC_DEBUG_PRINT
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Applied Power Weights:\n\tSclFctr\tRdCr\tWrCr\tActCr\tCkeL\tCkeH\tChPwrFloor\n"
      );
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (!MrcChannelExist (Outputs, Channel)) {
        continue;
      }
      ChannelOut = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmOut = &ChannelOut->Dimm[Dimm];
        if (DimmOut->Status == DIMM_PRESENT) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%dD%d:\t", Channel, Dimm);
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "%d\t%2Xh\t%2Xh\t%2Xh\t%Xh\t%2Xh\t%2Xh\n",
            MinScaleFactor,
            PmDimmRdEnergy[Channel].Data8[Dimm],
            PmDimmWrEnergy[Channel].Data8[Dimm],
            PmDimmActEnergy[Channel].Data8[Dimm],
            PmDimmPdEnergy[Channel].Data8[Dimm],
            PmDimmIdleEnergy[Channel].Data8[Dimm],
            ChPwrFloor[Channel][0]
            );
        }
      }
    }
#endif
  }

  return mrcSuccess;
}

/**
  Configures Memory Thermal settings

  @param[in] MrcData  - The MRC "global data" area.
  @retval: mrcSuccess if the write is successful, otherwise mrcFail.
**/
MrcStatus
MrcThermalConfig (
  IN MrcParameters *const MrcData
  )
{
  MrcInput                                      *Inputs;
  MrcOutput                                     *Outputs;
  MrcDebug                                      *Debug;
  ThermalMngmtEn                                *ThermalEnables;
  MrcDdrType                                    DdrType;
  UINT8                                         Channel;
  UINT32                                        Offset;
  DDR_PTM_CTL_PCU_STRUCT                        DdrPtmCtl;
  DDR_ENERGY_SCALEFACTOR_PCU_STRUCT             DdrEnergyScaleFactor;
  DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_STRUCT       DdrRaplChannelPowerFloor;
  DDR_RAPL_LIMIT_PCU_STRUCT                     DdrRaplLimit;
  DDR_WARM_THRESHOLD_CH0_PCU_STRUCT             DdrWarmThresholdCh0;
  DDR_WARM_THRESHOLD_CH1_PCU_STRUCT             DdrWarmThresholdCh1;
  DDR_HOT_THRESHOLD_CH0_PCU_STRUCT              DdrHotThresholdCh0;
  DDR_HOT_THRESHOLD_CH1_PCU_STRUCT              DdrHotThresholdCh1;
  DDR_WARM_BUDGET_CH0_PCU_STRUCT                DdrWarmBudgetCh0;
  DDR_WARM_BUDGET_CH1_PCU_STRUCT                DdrWarmBudgetCh1;
  DDR_HOT_BUDGET_CH0_PCU_STRUCT                 DdrHotBudgetCh0;
  DDR_HOT_BUDGET_CH1_PCU_STRUCT                 DdrHotBudgetCh1;
  CH0_CR_PM_DIMM_IDLE_ENERGY_STRUCT             PmDimmIdleEnergy;
  CH0_CR_PM_DIMM_PD_ENERGY_STRUCT               PmDimmPdEnergy;
  CH0_CR_PM_DIMM_ACT_ENERGY_STRUCT              PmDimmActEnergy;
  CH0_CR_PM_DIMM_RD_ENERGY_STRUCT               PmDimmRdEnergy;
  CH0_CR_PM_DIMM_WR_ENERGY_STRUCT               PmDimmWrEnergy;
  PM_SREF_CONFIG_STRUCT                         PmSrefConfig;

  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  ThermalEnables      = &Inputs->ThermalEnables;
  DdrType             = Outputs->DdrType;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Configuring Thermal Controls\n");

  if (Inputs->UserPowerWeightsEn) {
    //
    // ENERGY SCALE FACTOR
    //
    DdrEnergyScaleFactor.Data             = 0;
    DdrEnergyScaleFactor.Bits.SCALEFACTOR = Inputs->EnergyScaleFact;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_ENERGY_SCALEFACTOR %Xh: %Xh \n",
      DDR_ENERGY_SCALEFACTOR_PCU_REG,
      DdrEnergyScaleFactor.Data
      );
    MrcWriteCR (MrcData, DDR_ENERGY_SCALEFACTOR_PCU_REG, DdrEnergyScaleFactor.Data);

    //
    // RAPL POWER FLOOR
    //
    DdrRaplChannelPowerFloor.Data     = 0;
    DdrRaplChannelPowerFloor.Bits.CH0 = Inputs->RaplPwrFlCh0;
    DdrRaplChannelPowerFloor.Bits.CH1 = Inputs->RaplPwrFlCh1;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_RAPL_CHANNEL_POWER_FLOOR %Xh: %Xh \n",
      DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_REG,
      DdrRaplChannelPowerFloor.Data
      );
    MrcWriteCR (MrcData, DDR_RAPL_CHANNEL_POWER_FLOOR_PCU_REG, DdrRaplChannelPowerFloor.Data);
  }

  //
  // RAPL LIMIT
  //
  DdrRaplLimit.Data                       = 0;
  DdrRaplLimit.Bits.LIMIT1_TIME_WINDOW_X  = ThermalEnables->RaplLim1WindX;
  DdrRaplLimit.Bits.LIMIT1_TIME_WINDOW_Y  = ThermalEnables->RaplLim1WindY;
  DdrRaplLimit.Bits.LIMIT1_ENABLE         = Inputs->RaplLim1Ena;
  DdrRaplLimit.Bits.LIMIT1_POWER          = ThermalEnables->RaplLim1Pwr;
  DdrRaplLimit.Bits.LOCKED                = Inputs->RaplLim2Lock;
  DdrRaplLimit.Bits.LIMIT2_TIME_WINDOW_X  = ThermalEnables->RaplLim2WindX;
  DdrRaplLimit.Bits.LIMIT2_TIME_WINDOW_Y  = ThermalEnables->RaplLim2WindY;
  DdrRaplLimit.Bits.LIMIT2_ENABLE         = Inputs->RaplLim2Ena;
  DdrRaplLimit.Bits.LIMIT2_POWER          = ThermalEnables->RaplLim2Pwr;
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_RAPL_LIMIT1 %Xh: %Xh \n",
    DDR_RAPL_LIMIT_PCU_REG,
    DdrRaplLimit.Data32[0]
    );
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DDR_RAPL_LIMIT2 %Xh: %Xh \n",
    DDR_RAPL_LIMIT_PCU_REG + 4,
    DdrRaplLimit.Data32[1]
    );
  MrcWriteCR (MrcData, DDR_RAPL_LIMIT_PCU_REG, DdrRaplLimit.Data32[0]);
  MrcWriteCR (MrcData, DDR_RAPL_LIMIT_PCU_REG + 4, DdrRaplLimit.Data32[1]);

#ifdef UP_SERVER_FLAG
  if ( (Inputs->UserThresholdEnable)  || (Inputs->BoardType != btUpServer) ) {
#endif
    //
    // DDR WARM AND HOT THRESHOLD
    //
    DdrWarmThresholdCh0.Data        = 0;
    DdrWarmThresholdCh0.Bits.DIMM1  = ThermalEnables->WarmThreshold[0][1];
    DdrWarmThresholdCh0.Bits.DIMM0  = ThermalEnables->WarmThreshold[0][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_WARM_THRESHOLD_CH0 %Xh: %Xh \n",
      DDR_WARM_THRESHOLD_CH0_PCU_REG,
      DdrWarmThresholdCh0.Data
      );
    MrcWriteCR (MrcData, DDR_WARM_THRESHOLD_CH0_PCU_REG, DdrWarmThresholdCh0.Data);

    DdrWarmThresholdCh1.Data        = 0;
    DdrWarmThresholdCh1.Bits.DIMM1  = ThermalEnables->WarmThreshold[1][1];
    DdrWarmThresholdCh1.Bits.DIMM0  = ThermalEnables->WarmThreshold[1][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_WARM_THRESHOLD_CH1 %Xh: %Xh \n",
      DDR_WARM_THRESHOLD_CH1_PCU_REG,
      DdrWarmThresholdCh1.Data
      );
    MrcWriteCR (MrcData, DDR_WARM_THRESHOLD_CH1_PCU_REG, DdrWarmThresholdCh1.Data);

    DdrHotThresholdCh0.Data       = 0;
    DdrHotThresholdCh0.Bits.DIMM1 = ThermalEnables->HotThreshold[0][1];
    DdrHotThresholdCh0.Bits.DIMM0 = ThermalEnables->HotThreshold[0][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_HOT_THRESHOLD_CH0 %Xh: %Xh \n",
      DDR_HOT_THRESHOLD_CH0_PCU_REG,
      DdrHotThresholdCh0.Data
      );
    MrcWriteCR (MrcData, DDR_HOT_THRESHOLD_CH0_PCU_REG, DdrHotThresholdCh0.Data);

    DdrHotThresholdCh1.Data       = 0;
    DdrHotThresholdCh1.Bits.DIMM1 = ThermalEnables->HotThreshold[1][1];
    DdrHotThresholdCh1.Bits.DIMM0 = ThermalEnables->HotThreshold[1][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_HOT_THRESHOLD_CH1 %Xh: %Xh \n",
      DDR_HOT_THRESHOLD_CH1_PCU_REG,
      DdrHotThresholdCh1.Data
      );
    MrcWriteCR (MrcData, DDR_HOT_THRESHOLD_CH1_PCU_REG, DdrHotThresholdCh1.Data);
#ifdef UP_SERVER_FLAG
  }

  if( (Inputs->UserBudgetEnable) || (Inputs->BoardType != btUpServer) ) {
#endif
    //
    // DDR WARM AND HOT BUDGET
    //
    DdrWarmBudgetCh0.Data       = 0;
    DdrWarmBudgetCh0.Bits.DIMM1 = ThermalEnables->WarmBudget[0][1];
    DdrWarmBudgetCh0.Bits.DIMM0 = ThermalEnables->WarmBudget[0][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_WARM_BUDGET_CH0 %Xh: %Xh \n",
      DDR_WARM_BUDGET_CH0_PCU_REG,
      DdrWarmBudgetCh0.Data
      );
    MrcWriteCR (MrcData, DDR_WARM_BUDGET_CH0_PCU_REG, DdrWarmBudgetCh0.Data);

    DdrWarmBudgetCh1.Data       = 0;
    DdrWarmBudgetCh1.Bits.DIMM1 = ThermalEnables->WarmBudget[1][1];
    DdrWarmBudgetCh1.Bits.DIMM0 = ThermalEnables->WarmBudget[1][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_WARM_BUDGET_CH1 %Xh: %Xh \n",
      DDR_WARM_BUDGET_CH1_PCU_REG,
      DdrWarmBudgetCh1.Data
      );
    MrcWriteCR (MrcData, DDR_WARM_BUDGET_CH1_PCU_REG, DdrWarmBudgetCh1.Data);

    DdrHotBudgetCh0.Data        = 0;
    DdrHotBudgetCh0.Bits.DIMM1  = ThermalEnables->HotBudget[0][1];
    DdrHotBudgetCh0.Bits.DIMM0  = ThermalEnables->HotBudget[0][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_HOT_BUDGET_CH0 %Xh: %Xh \n",
      DDR_HOT_BUDGET_CH0_PCU_REG,
      DdrHotBudgetCh0.Data
      );
    MrcWriteCR (MrcData, DDR_HOT_BUDGET_CH0_PCU_REG, DdrHotBudgetCh0.Data);

    DdrHotBudgetCh1.Data        = 0;
    DdrHotBudgetCh1.Bits.DIMM1  = ThermalEnables->HotBudget[1][1];
    DdrHotBudgetCh1.Bits.DIMM0  = ThermalEnables->HotBudget[1][0];
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "DDR_HOT_BUDGET_CH1 %Xh: %Xh \n",
      DDR_HOT_BUDGET_CH1_PCU_REG,
      DdrHotBudgetCh1.Data
      );
    MrcWriteCR (MrcData, DDR_HOT_BUDGET_CH1_PCU_REG, DdrHotBudgetCh1.Data);
#ifdef UP_SERVER_FLAG
  }
#endif

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      if (Inputs->UserPowerWeightsEn) {
        PmDimmIdleEnergy.Data                   = 0;
        PmDimmIdleEnergy.Bits.DIMM1_IDLE_ENERGY = ThermalEnables->IdleEnergy[Channel][1];
        PmDimmIdleEnergy.Bits.DIMM0_IDLE_ENERGY = ThermalEnables->IdleEnergy[Channel][0];
        Offset = OFFSET_CALC_CH (CH0_CR_PM_DIMM_IDLE_ENERGY_REG, CH1_CR_PM_DIMM_IDLE_ENERGY_REG, Channel);
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "C%u PM_DIMM_IDLE_ENERGY %Xh: %Xh \n",
          Channel,
          Offset,
          PmDimmIdleEnergy.Data
          );
        MrcWriteCR (MrcData, Offset, PmDimmIdleEnergy.Data);

        PmDimmPdEnergy.Data                 = 0;
        PmDimmPdEnergy.Bits.DIMM1_PD_ENERGY = ThermalEnables->PdEnergy[Channel][1];
        PmDimmPdEnergy.Bits.DIMM0_PD_ENERGY = ThermalEnables->PdEnergy[Channel][0];
        Offset = OFFSET_CALC_CH (CH0_CR_PM_DIMM_PD_ENERGY_REG, CH1_CR_PM_DIMM_PD_ENERGY_REG, Channel);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_DIMM_PD_ENERGY %Xh: %Xh \n", Channel, Offset, PmDimmPdEnergy.Data);
        MrcWriteCR (MrcData, Offset, PmDimmPdEnergy.Data);

        PmDimmActEnergy.Data                  = 0;
        PmDimmActEnergy.Bits.DIMM1_ACT_ENERGY = ThermalEnables->ActEnergy[Channel][1];
        PmDimmActEnergy.Bits.DIMM0_ACT_ENERGY = ThermalEnables->ActEnergy[Channel][0];
        Offset = OFFSET_CALC_CH (CH0_CR_PM_DIMM_ACT_ENERGY_REG, CH1_CR_PM_DIMM_ACT_ENERGY_REG, Channel);
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_NOTE,
          "C%u PM_DIMM_ACT_ENERGY %Xh: %Xh \n",
          Channel,
          Offset,
          PmDimmActEnergy.Data
          );
        MrcWriteCR (MrcData, Offset, PmDimmActEnergy.Data);

        PmDimmRdEnergy.Data                 = 0;
        PmDimmRdEnergy.Bits.DIMM1_RD_ENERGY = ThermalEnables->RdEnergy[Channel][1];
        PmDimmRdEnergy.Bits.DIMM0_RD_ENERGY = ThermalEnables->RdEnergy[Channel][0];
        Offset = OFFSET_CALC_CH (CH0_CR_PM_DIMM_RD_ENERGY_REG, CH1_CR_PM_DIMM_RD_ENERGY_REG, Channel);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_DIMM_RD_ENERGY %Xh: %Xh \n", Channel, Offset, PmDimmRdEnergy.Data);
        MrcWriteCR (MrcData, Offset, PmDimmRdEnergy.Data);

        PmDimmWrEnergy.Data                 = 0;
        PmDimmWrEnergy.Bits.DIMM1_WR_ENERGY = ThermalEnables->WrEnergy[Channel][1];
        PmDimmWrEnergy.Bits.DIMM0_WR_ENERGY = ThermalEnables->WrEnergy[Channel][0];
        Offset = OFFSET_CALC_CH (CH0_CR_PM_DIMM_WR_ENERGY_REG, CH1_CR_PM_DIMM_WR_ENERGY_REG, Channel);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "C%u PM_DIMM_WR_ENERGY %Xh: %Xh \n", Channel, Offset, PmDimmWrEnergy.Data);
        MrcWriteCR (MrcData, Offset, PmDimmWrEnergy.Data);
      }
    }
  }
  PmSrefConfig.Data             = 0;
  PmSrefConfig.Bits.SR_Enable   = Inputs->SrefCfgEna;
  PmSrefConfig.Bits.Idle_timer  = Inputs->SrefCfgIdleTmr;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PM_SREF_CONFIG %Xh: %Xh\n", PM_SREF_CONFIG_REG, PmSrefConfig.Data);
  MrcWriteCR (MrcData, PM_SREF_CONFIG_REG, PmSrefConfig.Data);

  //
  // POWER THERMAL MANAGEMENT CONTROL
  //
  DdrPtmCtl.Data                    = MrcReadCR (MrcData, DDR_PTM_CTL_PCU_REG);
  DdrPtmCtl.Bits.OLTM_ENABLE        = Inputs->EnableOltm;
  DdrPtmCtl.Bits.CLTM_ENABLE        = Inputs->EnableCltm;
  DdrPtmCtl.Bits.EXTTS_ENABLE       = Inputs->EnableExtts;
  DdrPtmCtl.Bits.REFRESH_2X_MODE    = Inputs->Refresh2X;

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    if ((Outputs->TCRSensitiveHynixDDR4) || (Outputs->TCRSensitiveMicronDDR4)) {
      DdrPtmCtl.Bits.DDR4_SKIP_REFRESH_EN = 0;
    } else {
      DdrPtmCtl.Bits.DDR4_SKIP_REFRESH_EN = 1;
    }
    DdrPtmCtl.Bits.DISABLE_DRAM_TS = (Inputs->DdrThermalSensor == 0) ? 1 : 0;
  }

  if (DdrType == MRC_DDR_TYPE_LPDDR4) {
    DdrPtmCtl.Bits.PDWN_CONFIG_CTL = Inputs->EnablePwrDnLpddr;
    DdrPtmCtl.Bits.DISABLE_DRAM_TS = (Inputs->DdrThermalSensor == 0) ? 1 : 0;
  } else {
    DdrPtmCtl.Bits.PDWN_CONFIG_CTL = Inputs->EnablePwrDn;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_PTM_CTL %Xh: %Xh\n", DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);
  MrcWriteCR (MrcData, DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);

#ifdef UP_SERVER_FLAG
  if (Inputs->BoardType == btUpServer) {
    MrcCltmTsodInitChecking (MrcData);
    if (Inputs->TsodManualEnable != 0) {
      CltmTsodConfiguration (MrcData);
    }
  }
#endif

  return mrcSuccess;
}


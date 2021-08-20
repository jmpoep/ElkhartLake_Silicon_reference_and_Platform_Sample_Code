/** @file
  This module configures the memory controller power modes.

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

///
/// Include files
///
#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcPowerModes.h"
#include "MrcDebugPrint.h"
#include "MrcSpdProcessing.h"

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
  UINT32          Controller;
  UINT32          Offset;
  BOOLEAN         UlxUlt;
  BOOLEAN         Lpddr;
  BOOLEAN         Lpddr5;
  MC0_CH0_CR_PM_PDWN_CONFIG_STRUCT PmPdwnConfig;
  MC0_CH0_CR_WCK_CONFIG_STRUCT     WckConfig;

  Inputs    = &MrcData->Inputs;
  Outputs   = &MrcData->Outputs;

  UlxUlt = Inputs->UlxUlt;
  Lpddr  = Outputs->Lpddr;
  Lpddr5 = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR5);

  WckConfig.Data = 0;
  PmPdwnConfig.Data = 0;
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
      break;

    case pdmAuto:
      PmPdwnConfig.Bits.PPD = 1;
      break;
  }

  if (Lpddr5) {
    Controller = (MrcControllerExist (MrcData, cCONTROLLER0)) ? 0 : 1;
    Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_WCK_CONFIG_REG, MC1_CH0_CR_WCK_CONFIG_REG, Controller, MC0_CH1_CR_WCK_CONFIG_REG, LP_IP_CH (Lpddr5, Outputs->Controller[Controller].FirstPopCh));
    WckConfig.Data = MrcReadCR64 (MrcData, Offset);
    WckConfig.Bits.WCK_OFF_IDLE_TIMER = PmPdwnConfig.Bits.PDWN_idle_counter / 2;
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (MrcControllerExist (MrcData, Controller)) {
      Offset = OFFSET_CALC_CH (MC0_BC_CR_PM_PDWN_CONFIG_REG, MC1_BC_CR_PM_PDWN_CONFIG_REG, Controller);
      MrcWriteCR (MrcData, Offset, PmPdwnConfig.Data);
      MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "MC%u_PM_PDWN_CONFIG: 0x%Xh\n", Controller, PmPdwnConfig.Data);
      if (Lpddr5) {
        Offset = OFFSET_CALC_CH (MC0_BC_CR_WCK_CONFIG_REG, MC1_BC_CR_WCK_CONFIG_REG, Controller);
        MrcWriteCR64 (MrcData, Offset, WckConfig.Data);
      }
    }
  }

  return;
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
  MrcInput                  *Inputs;
  MrcOutput                 *Outputs;
  MrcDebug                  *Debug;
  MrcDdrType                DdrType;
  UINT32                    Controller;
  UINT32                    Offset;
  BOOLEAN                   Lpddr;
  DDR_PTM_CTL_PCU_STRUCT    DdrPtmCtl;
  MC0_PM_SREF_CONFIG_STRUCT PmSrefConfig;

  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  DdrType             = Outputs->DdrType;
  Lpddr               = Outputs->Lpddr;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Configuring Thermal Controls\n");

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (!MrcControllerExist (MrcData, Controller)) {
      continue;
    }
    Offset = OFFSET_CALC_CH (MC0_PM_SREF_CONFIG_REG, MC1_PM_SREF_CONFIG_REG, Controller);
    PmSrefConfig.Data             = MrcReadCR (MrcData, Offset);
    PmSrefConfig.Bits.SR_Enable   = Inputs->SrefCfgEna;
    PmSrefConfig.Bits.Idle_timer  = Inputs->SrefCfgIdleTmr;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PM_SREF_CONFIG %Xh: %Xh\n", Offset, PmSrefConfig.Data);
    MrcWriteCR (MrcData, Offset, PmSrefConfig.Data);
  } // Controller

  // POWER THERMAL MANAGEMENT CONTROL
  DdrPtmCtl.Data                    = MrcReadCR (MrcData, DDR_PTM_CTL_PCU_REG);
  DdrPtmCtl.Bits.REFRESH_2X_MODE    = Inputs->Refresh2X;

  if (DdrType == MRC_DDR_TYPE_DDR4) {
    if ((Outputs->TCRSensitiveHynixDDR4) || (Outputs->TCRSensitiveMicronDDR4)) {
      DdrPtmCtl.Bits.DDR4_SKIP_REFRESH_EN = 0;
    } else {
      DdrPtmCtl.Bits.DDR4_SKIP_REFRESH_EN = 1;
    }
  }
  DdrPtmCtl.Bits.PDWN_CONFIG_CTL = (Lpddr ? Inputs->EnablePwrDnLpddr :Inputs->EnablePwrDn);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDR_PTM_CTL %Xh: %Xh\n", DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);
  MrcWriteCR (MrcData, DDR_PTM_CTL_PCU_REG, DdrPtmCtl.Data);

  return mrcSuccess;
}


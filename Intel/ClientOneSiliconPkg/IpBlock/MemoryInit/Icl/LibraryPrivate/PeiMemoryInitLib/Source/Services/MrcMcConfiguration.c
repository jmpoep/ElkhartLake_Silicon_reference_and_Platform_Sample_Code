/** @file
  The functions in this file implement the memory controller registers that
  are not training specific. After these functions are executed, the
  memory controller will be ready to execute the timing training sequences.

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
#include "MrcMcConfiguration.h"
#include "MrcMaintenance.h"
#include "MrcDdrIoOffsets.h"
#include "MrcInterface.h"
#include "MrcLpddr4.h"
#include "MrcDdr4.h"
#include "MrcCommon.h"
#include "MrcDdrCommon.h"
#include "Cpgc20.h"
#include "MrcCpgcOffsets.h"
#include "MrcCpgcApi.h"
#include "MrcGears.h"

///
/// Structs and Types
///

/// CNL CKE/CTL/CKECTL Enable Mappings.
typedef union {
  union {
    union {
      struct {
        UINT8 Clk     : 2;
        UINT8 Cs0ScA  : 1;
        UINT8 Cs1ScB  : 1;
        UINT8 Cs1ScA  : 1;
        UINT8 Cs0ScB  : 1;
        UINT8 Cs2ScA  : 1;
        UINT8 Cs2ScB  : 1;
      } CnlB0;
    } Lpddr4;
    struct {
      UINT8 Clk01 : 2;
      UINT8 Cs01  : 2;
      UINT8       : 2;
      UINT8 Odt01 : 2;
    } Ddr4;
  } Ctl;
  union {
    struct {
      UINT8 Cke01ScA  : 2;
      UINT8 Cke01ScB  : 2;
      UINT8 Cke2ScA   : 1;
      UINT8 Cke2ScB   : 1;
      UINT8           : 2;
    } Lpddr;
    struct {
      UINT8 Cke0      : 1;
      UINT8 Cke1A     : 1;  ///< Shared CKE Delay. Used when MrcInput.SeparateCkeDelayDdr4 is 0
      UINT8           : 1;
      UINT8 Cke1B     : 1;  ///< Separate CKE Delay. Used when MrcInput.SeparateCkeDelayDdr4 is 1
      UINT8           : 4;
    } Ddr4;
  } Cke;
  union {
    struct {
      UINT8 Clk     : 2;
      UINT8         : 2;  // Not used
      UINT8 Cs3ScA  : 1;
      UINT8 Cs3ScB  : 1;
      UINT8         : 2;  // ODT - not used for LP4
    } Lpddr4;
    struct {
      UINT8 Clk23   : 2;
      UINT8         : 2;  // Not used
      UINT8 Cs23    : 2;
      UINT8 Odt23   : 2;
    } Ddr4;
  } CtlClkCke;
  union {
    struct {
      UINT8 Cke3ScA : 1;
      UINT8 Cke3ScB : 1;
    } Lpddr4;
    struct {
      UINT8 Cke23   : 2;
    } Ddr4;
  } Ccc4Cke;
  UINT8 Data8;
} CLK_CKE_CTL_EN_TYPE;

///
/// Defines
///

///
/// Global Constants
///
const UINT8 CompParamList[] = { RdOdt, WrDS, WrDSCmd, WrDSCtl, WrDSClk };
const UINT8 ByteStagger[] = {1, 4, 1, 5, 2, 6, 3, 7, 8};  // Increased Byte Stagger for byte0
const UINT8 MinCycleStageDelay[] = {46, 70, 70, 46};      // Avoid corner case

/**
  This function calculates the two numbers that get you closest to the slope.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Slope   - Targeted slope (multiplied by 1000 for integer math)

  @retval Returns the Slope Index to be programmed for VtSlope in terms of the CR.
**/
UINT8
MrcCalcVtSlopeCode (
  IN  MrcParameters * const MrcData,
  IN  const UINT16 Slope
  )
{
  static const INT16 Coding[] = {0, -250, -125, -62, 500, 250, 125, 62}; // 0: 0, 1: -1/4, 2: -1/8, 3: -1/16, 4: +1/2, 5: +1/4, 6: +1/8, 7: +1/16
  INT16       Error;
  INT16       BestError;
  UINT8       BestI;
  UINT8       BestJ;
  UINT8       i;
  UINT8       j;

  BestError = 1000;
  BestI     = 0;
  BestJ     = 0;
  for (i = 0; i < (sizeof (Coding) / sizeof (Coding[0])); i++) {
    for (j = 0; j < (sizeof (Coding) / sizeof (Coding[0])); j++) {
      Error = Slope - (Coding[i] + Coding[j]);
      if (Error < 0) {
        Error = -Error;
      }

      if (BestError > Error) {
        BestError = Error;
        BestI     = i;
        BestJ     = j;
      }
    }
  }

  return (BestI << 3) + BestJ;
}

/**
  This function locks the DDR frequency requested from SPD or User.
  It will update the frequency related members in the output structure.

  @param[in, out] MrcData - MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcFrequencyLock (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput          *Inputs;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcStatus         Status;
  MrcProfile        Profile;
  UINT32            Channel;
  MrcIntOutput      *MrcIntData;

  MrcIntData        = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[CONTROLLER_0];
  Profile           = Inputs->MemoryProfile;
  // Make sure tCL-tCWL <= 4
  // This is needed to support ODT properly for 2DPC case
  // @todo: <CNL> Move to DDRIO INIT.
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, (UINT8) Channel)) {
      ChannelOut = &ControllerOut->Channel[Channel];
      if (ChannelOut->DimmCount == 2) {
        if ((ChannelOut->Timing[Profile].tCL - ChannelOut->Timing[Profile].tCWL) > 4) {
          ChannelOut->Timing[Profile].tCWL = ChannelOut->Timing[Profile].tCL - 4;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "(tCL-tCWL) > 4, CH %u - tCWL has been updated to %u\n",
            Channel,
            ChannelOut->Timing[Profile].tCWL
            );
        }
      }
    }
  }

  // For LPDDR4, we need to do the first lock at the low frequency for ECT flow.
  // If we are disabling ECT or frequency switching, we need to lock at the intended frequency.
  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) &&
      (Inputs->LpFreqSwitch == TRUE) &&
      (Inputs->TrainingEnables.ECT == 1) &&
      (Inputs->BootMode == bmCold)) {
    Outputs->Frequency = f1067;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Locking at low(%d) first.  Will switch to high(%d) after ECT\n",
      Outputs->Frequency,
      Outputs->HighFrequency
      );
  }

  // We don't always use MrcFrequencySwitch because of LPDDR4 Self-Refresh is command based.
  // On first execution of the frequency, Command has not been training and Self-Refresh may fail.
  if ((MrcData->Inputs.SaGv != MrcSaGvEnabled) || (MrcIntData->SaGvPoint == MrcSaGvPointLow)) {
    Status = McFrequencySet (MrcData, MRC_PRINTS_ON);
  } else {
    Status = MrcFrequencySwitch (MrcData, Outputs->Frequency, MRC_PRINTS_ON);
  }
  if (Status != mrcSuccess) {
    return Status;
  }
  MrcInternalCheckPoint (MrcData, OemFrequencySetDone, NULL);

  // Save MRC Version into CR
  MrcSetMrcVersion (MrcData);

  return Status;
}

/**
  This function initializes the Memory Controller: Scheduler, Timings, Address Decode,
  Odt Control, and refresh settings.

  @param[in, out] MrcData - MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status.
**/
MrcStatus
MrcMcConfiguration (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput *Outputs;
  MrcDebug  *Debug;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Timing Config\n");
  MrcTimingConfiguration (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Refresh Config\n");
  MrcRefreshConfiguration (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Scheduler parameters\n");
  MrcSchedulerParametersConfig (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Address Decoding Config\n");
  MrcAdConfiguration (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Maintenance Configuration\n");
  MrcMaintenanceConfig (MrcData);

  if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
    MrcSetOdtMatrix (MrcData, 1);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Probeless Config\n");
  MrcProbelessConfig (MrcData);

  // Initialize the MARS feature (Memory AwaRe Scrubber)
  // This has to be done once all the MC Address Decode register are programmed
  MrcMarsConfig (MrcData);

  return mrcSuccess;
}

/**
  This function initializes memory subsystem registers that are not specific to MC or DDRIO.

  @param[in, out] MrcData - Pointer to the global MRC data.

  @retval MrcStatus - mrcSuccess if successful or an error status.
**/
MrcStatus
MrcMemorySsInit (
  IN OUT  MrcParameters *const MrcData
  )
{
  return mrcSuccess;
}

/**
  This function configures probeless config register.

  @param[in, out] MrcData - All the MRC global data.
**/
void
MrcProbelessConfig (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput            *Inputs;
  MrcOutput                 *Outputs;
  MrcDebug                  *Debug;
  BOOLEAN                   Populated;
  UINT8                     Channel;
  UINT32                    Offset;
  MCDECS_MISC_STRUCT              McdecsMisc;
  DDRPL_CFG_DTF_STRUCT            ProbelessCfg;
  CH0_CR_PL_AGENT_CFG_DTF_STRUCT  PlAgentCfg;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  if (Inputs->IclA0) {
    McdecsMisc.Data = MrcReadCR (MrcData, MCDECS_MISC_REG);
    McdecsMisc.Bits.Spare_RW |= MRC_BIT1;
    MrcWriteCR (MrcData, MCDECS_MISC_REG, McdecsMisc.Data);
  }

  ProbelessCfg.Data = MrcReadCR (MrcData, DDRPL_CFG_DTF_REG);

  if (Inputs->IclA0) {  // These two fields are gone in B0
    //Set up DRAM_technology based on DdrType
    ProbelessCfg.Bits.DRAM_technology = Outputs->DdrType;

    //If ECHM is enabled, set ECHM to 1.
    ProbelessCfg.Bits.ECHM = Outputs->EnhancedChannelMode;
  }

  //If channel 0 is populated, program MCHTrace to 0. Else program to 1.
  Channel = MrcChannelExist (Outputs, 0) ? 0 : 1;
  ProbelessCfg.Bits.MCHTrace = Channel;

  //If DDR4 or LP memory subchannel 0 is populated for channel 0, program SCHTrace to 0.
  //Else if not DDR4 and subchannel 0 is not populated for channel 0, program SCHTrace to 1.
  Populated = MrcSubChannelExist (MrcData, Channel, 0);
  ProbelessCfg.Bits.SCHTrace = !Populated;

  //If ECC is enabled, set ECC_EN to 1.
  ProbelessCfg.Bits.ECC_EN = Outputs->EccSupport;

  //Set DDRPL_Activate based on setup option ProbelessTrace Enable or Disable. Default is Disabled.
  ProbelessCfg.Bits.DDRPL_Activate = Inputs->ProbelessTrace;

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "DRAM_Technology = 0x%x\nMCHTrace = 0x%x\nSCHTrace = 0x%x\nECHM = 0x%x\nECC_EN = 0x%x\nDDRPL_Activate = 0x%x\n",
    ProbelessCfg.Bits.DRAM_technology,
    ProbelessCfg.Bits.MCHTrace,
    ProbelessCfg.Bits.SCHTrace,
    ProbelessCfg.Bits.ECHM,
    ProbelessCfg.Bits.ECC_EN,
    ProbelessCfg.Bits.DDRPL_Activate
    );

  MrcWriteCR (MrcData, DDRPL_CFG_DTF_REG, ProbelessCfg.Data);

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      Offset = OFFSET_CALC_CH (CH0_CR_PL_AGENT_CFG_DTF_REG, CH1_CR_PL_AGENT_CFG_DTF_REG, Channel);
      PlAgentCfg.Data = MrcReadCR (MrcData, Offset);
      PlAgentCfg.Bits.data_trace_mode = 3;
      MrcWriteCR (MrcData, Offset, PlAgentCfg.Data);
    }
  }
}

/**
  This function calculates the Dynamic and Static leg sizes by calibrating Comp to a predetermined value.
  Dynamic leg is calculated by disabling static legs and reading the comp code resulting from a predefined Comp target.
  Static legs are calculated by enabling all static legs and setting ROn to some predetermined value.
  Dynamic legs previously calculated allow determining the static legs size.
  The Dynamic and Static leg size calculation has two main usages:
  1. RxBias calculation for P-Bias (when using P-Path).
  2. ODT/RON Impedance calculation.
  This function initializes the Rx Bias circuits for P-Path in DDRIO.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
CalcStaticDynamicLegSize (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput            *Inputs;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MrcIntOutput        *IntOutputs;
  MrcStatus           Status;
  MRC_ODT_MODE_TYPE   OdtModeSave;
  INT64               GetSetVal;
  UINT16              RonCompCode;
  UINT16              OdtCompCode;
  INT64               StoredOdtStatic;
  INT64               StoredStaticLegs;
  UINT32              Numerator;
  UINT32              Denominator;
  UINT32              CurrCompVref;
  static const UINT16 RonRCompTarget = 50;
  static const UINT16 OdtRCompTarget = 60;
  static const UINT16 NumStaticLegs  = 5; // ICL - 5 legs

  IntOutputs  = (MrcIntOutput *)(MrcData->IntOutputs.Internal);
  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  Status      = mrcSuccess;
  OdtModeSave = Outputs->OdtMode;
  // Read initial state of values
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompOdtStaticDis, ReadUncached, &StoredOdtStatic);
  MrcGetSetDdrIoGroupController0 (MrcData, DqRcompStatLegs, ReadUncached, &StoredStaticLegs);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Starting P-Path current optimization training\n");
  //
  // Calculate Dynamic leg size using Tx ODT RCOMP
  // Algorithm - Disable static legs
  // Set ODT to predfined Target (OdtTarget) and read resulting CompCode (OdtCompCode)
  // DynamicLegR = OdtCompCode * OdtTarget
  //
  // 1. Disable all static legs
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Calculating Dynamic legs strength:\n");
  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompOdtStaticDis, ForceWriteCached, &GetSetVal);
  // 2. Set termination mode to Vdd
  MrcSetIoOdtMode (MrcData, MrcOdtModeVddq);
  // 3. Set ODT Target to 60 Ohms
  Numerator = (MRC_COMP_VREF_STEP_SIZE - 1) * Inputs->RcompResistor[RdOdt];
  Denominator = OdtRCompTarget + Inputs->RcompResistor[RdOdt];

  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && (Inputs->LowSupplyEnData)) {
    Numerator *= Inputs->VccIomV;
    Denominator *= VDD_1_10;
  }
  CurrCompVref = UDIVIDEROUND (Numerator, Denominator);

  OdtCompCode = (UINT8) UpdateCompGlobalOffset (MrcData, RdOdt, (INT32)CurrCompVref, FALSE, TRUE);
  if (OdtCompCode == 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%s OdtCompCode is 0!\n", gWarnString);
    OdtCompCode = 1;
  }
  IntOutputs->ResistanceDynamicLeg = OdtCompCode * OdtRCompTarget;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "OdtRCompTarget %u, Numerator %u, CurrCompVref %u, Denominator %u, CompCode %u, Disable Static Legs %u, Dynamic legs strength %u\n",
                  OdtRCompTarget, Numerator, CurrCompVref, Denominator, OdtCompCode, (UINT32)GetSetVal, IntOutputs->ResistanceDynamicLeg);
  //
  // Calculate Static leg size using Tx Dq RCOMP
  // RonTarget  = (StaticLegR / NumStaticLegs) || (DynamicLegR / RonCompCode)
  // StaticLegR = NumStaticLegs * ( OdtTarget * RonTarget * OdtCompCode ) / (OdtTarget * OdtCompCode - RonTarget * RonCompCode)
  //
  // 1. Enable all 8 Static legs
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Calculating Static legs strength:\n");
  GetSetVal = 3;
  MrcGetSetDdrIoGroupController0 (MrcData, DqRcompStatLegs, ForceWriteUncached, &GetSetVal);
  // 2. Set target Ron to 50 Ohms
  Numerator   = (MRC_COMP_VREF_STEP_SIZE - 1)* Inputs->RcompResistor[WrDS];
  Denominator = RonRCompTarget + Inputs->RcompResistor[WrDS];
  if ((Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) && (Inputs->LowSupplyEnData)) {
    Numerator   *= Inputs->VccIomV;
    Denominator *= (UINT16) ((Outputs->Lp4x) ? VDD_1_10 : Outputs->VddVoltage[Inputs->MemoryProfile]);
  }
  CurrCompVref  = UDIVIDEROUND (Numerator, Denominator);
  RonCompCode   = (UINT8) UpdateCompGlobalOffset (MrcData, WrDS, (INT32) CurrCompVref, FALSE, TRUE);
  if (RonCompCode == 0) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%s RonCompCode is 0!\n", gWarnString);
    RonCompCode = 1;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Numerator %u, Denominator %u, CurrCompVref %u\n", Numerator, Denominator, CurrCompVref);
  Numerator = NumStaticLegs * (OdtRCompTarget * RonRCompTarget * OdtCompCode);
  Denominator = OdtRCompTarget * OdtCompCode - RonRCompTarget * RonCompCode;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Numerator %d, Denominator: %d, OdtCompCode: %d, RonCompCode: %d\n", Numerator, Denominator, OdtCompCode, RonCompCode);
  IntOutputs->ResistanceStaticLeg = (UINT16) UDIVIDEROUND (Numerator, Denominator);
  MRC_DEBUG_ASSERT (IntOutputs->ResistanceStaticLeg != 0, Debug, "ResistanceStaticLeg is 0 !\n");
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "RonRCompTarget %u, CompCode %u\n", RonRCompTarget, RonCompCode);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Num Static Legs %u, Static legs strength %u\n", NumStaticLegs, IntOutputs->ResistanceStaticLeg);
  //
  // Restore original IO settings
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Restoring ODT settings \n");
  // 1. Restore StaticLegs
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompOdtStaticDis, ForceWriteCached, &StoredOdtStatic);
  // 2. Restore termination mode
  MrcSetIoOdtMode (MrcData, OdtModeSave);
  // 3. Restore Target ODT
  UpdateCompTargetValue (MrcData, RdOdt, Inputs->RcompTarget[RdOdt], TRUE);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Restoring WrDS settings \n");
  // 1. Restore StaticLegs
  MrcGetSetDdrIoGroupController0 (MrcData, DqRcompStatLegs, ForceWriteCached, &StoredStaticLegs);
  // 2. Restore Target WrDS
  UpdateCompTargetValue (MrcData, WrDS, Inputs->RcompTarget[WrDS], TRUE);
  // 3. Restore TxEq
  // GetSetVal = StoredTxEqualization;
  // MrcGetSetDdrIoGroupStrobe (MrcData, MAX_CHANNEL, MAX_RANK_IN_CHANNEL, MAX_DRAM_DEVICE, TxEq, ForceWriteCached, &GetSetVal);
  return Status;

}

/**
  Calculate StrongWkLeaker value using RdOdt comp codes.

  @param[in] MrcData - Include all MRC global data.

  @retval Leaker value
**/
UINT32
CalcStrongLeaker (
  IN MrcParameters *const MrcData
  )
{
  MrcInput  *Inputs;
  MrcOutput *Outputs;
  MrcDebug  *Debug;
  UINT32    Leaker;
  UINT32    OdtCompCodeUp;
  UINT32    OdtCompCodeDn;
  UINT32    CompVref;
  UINT32    Numerator;
  UINT32    Denominator;
  UINT32    OdtRCompTarget;
  UINT32    ReferenceR;
  UINT32    NumOfSegments;
  INT64     GetSetVal;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  // 1. Disable Static ODT legs
  GetSetVal = 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompOdtStaticDis, WriteNoCache, &GetSetVal);

  // 2. Set RdOdt target to 50 Ohm and read Up/Dn comp codes
  OdtRCompTarget = 50;
  NumOfSegments = (Outputs->OdtMode == MrcOdtModeVtt) ? 1 : 2;
  ReferenceR  = DIVIDEROUND (Inputs->RcompResistor[RdOdt], NumOfSegments);

  Numerator = MRC_COMP_VREF_STEP_SIZE * ReferenceR;
  Denominator = OdtRCompTarget + ReferenceR;
  if (Outputs->OdtMode == MrcOdtModeVtt) {
    Denominator *= 2;
  }
  if (Inputs->LowSupplyEnData) {
    Numerator *= Inputs->VccIomV;
    Denominator *= VDD_1_10;
  }
  CompVref = UDIVIDEROUND (Numerator, Denominator);

  OdtCompCodeUp = UpdateCompGlobalOffset (MrcData, RdOdt, (INT32) CompVref, FALSE, TRUE);
  MrcGetSetDdrIoGroupController0 (MrcData, CompRcompOdtDn, ReadUncached, &GetSetVal);
  OdtCompCodeDn = (UINT32) GetSetVal;

  Leaker = (OdtCompCodeUp + OdtCompCodeDn) / 2;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "OdtCompCodeUp/Dn = %d/%d, StrongWkLeaker = %d\n", OdtCompCodeUp, OdtCompCodeDn, Leaker);

  // This is called before we program initial RCOMP targets, so no need to save/restore anything

  return Leaker;
}

/**
  This function initializes the Memory Controller Phy.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrIoPreInit (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput          *Inputs;
  MrcIntOutput      *MrcIntData;
  MrcStatus         Status;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  INT64             GetSetVal;
  INT64             GetSetEn;
  UINT32            Offset;
  UINT8             Controller;
  UINT8             Channel;
  BOOLEAN           Lpddr4;
  BOOLEAN           Ddr4;
  BOOLEAN           DqPinsInterleaved;
  DDRSCRAM_CR_DDRMISCCONTROL3_STRUCT             CkeMapping;

  Inputs = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  ControllerOut = &Outputs->Controller[0];
  Status = mrcSuccess;
  Lpddr4 = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4 = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  GetSetEn = 1;
  DqPinsInterleaved = (Inputs->DqPinsInterleaved != 0);
  MrcIntData->ClkDccInit = FALSE;
  MrcIntData->DqsDccInit = FALSE;

  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    ControllerOut->DeviceId = (UINT16) (MrcPciRead32 (MrcData, HOST_BRIDGE_BUS, HOST_BRIDGE_DEVICE, HOST_BRIDGE_FUNCTION, HOST_BRIDGE_DEVID) >> 16);
    ControllerOut->RevisionId = (UINT8) (MrcPciRead32 (MrcData, HOST_BRIDGE_BUS, HOST_BRIDGE_DEVICE, HOST_BRIDGE_FUNCTION, HOST_BRIDGE_REVID));
  }

  // Select the interleaving mode of DQ/DQS pins
  // This must be the first DDR IO register to be programmed on ULT
  GetSetVal = (DqPinsInterleaved) ? 0 : 1;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocNoDqInterleave, WriteToCache, &GetSetVal);
  MrcWeaklockEnDis (MrcData, MRC_DISABLE);

  if (Lpddr4) {
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocScramLpMode, WriteToCache, &GetSetEn);
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocScramLp4Mode, WriteToCache, &GetSetEn);
  }

  // Rank CKE Mapping
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    CkeMapping.Data = 0;
    CkeMapping.Bits.glbdrv_clkgate_enable = 1;
    if (Lpddr4) {
      // LPDDR4
      // CKEbuf0_Mapping is Rank 0.
      CkeMapping.Bits.CKEbuf1_Mapping = 1;
      CkeMapping.Bits.CKEbuf2_Mapping = 2;
      CkeMapping.Bits.CKEbuf3_Mapping = 3;
      // CKEbuf4_Mapping is 0
      CkeMapping.Bits.CKEbuf5_Mapping = 2;
      CkeMapping.Bits.CKEbuf6_Mapping = 1;
      CkeMapping.Bits.CKEbuf7_Mapping = 3;
    } else {
      // DDR4
      // CKEbuf0_Mapping is Rank 0.
      CkeMapping.Bits.CKEbuf3_Mapping = 1;
      CkeMapping.Bits.CKEbuf6_Mapping = 2;
      CkeMapping.Bits.CKEbuf7_Mapping = 3;
    }
    Offset = DDRSCRAM_CR_DDRMISCCONTROL3_REG +
      (DDRSCRAM_CR_DDRMISCCONTROL4_REG - DDRSCRAM_CR_DDRMISCCONTROL3_REG) * Channel;
    MrcWriteCR (MrcData, Offset, CkeMapping.Data);
  } // Channel

  if (Outputs->EnhancedChannelMode) {
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIoc4ChMode, WriteToCache, &GetSetEn);
  }
  if (Ddr4) {
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocScramDdr4Mode, WriteToCache, &GetSetEn);
  }
  if (Outputs->EccSupport) {
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocEccEn, WriteToCache, &GetSetEn);
  }
  if (Inputs->CpuModel == cmICL_DT_HALO_R) {
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDdrCentric, WriteToCache, &GetSetEn);
  }

  MrcSetGear2 (MrcData, Outputs->Gear2);

  MrcFlushRegisterCachedData (MrcData);

  return Status;
}

/**
  This function initializes the Memory Controller Phy.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrIoInit (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  MrcIntOutput      *IntOutputs;
  const MRC_FUNCTION *MrcCall;
  MrcIntControllerOut *IntControllerOut;
  MrcIntCmdTimingOut *IntCmdTiming;
  MrcStatus         Status;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcControllerOut  *ControllerOut;
  MrcProfile        Profile;
  MrcVddSelect      Vdd;
  MrcFrequency      QclkFrequency;
  INT64             GetSetVal;
  INT64             GetSetVal2;
  INT64             GetSetVal3;
  INT64             GetSetVal4;
  INT64             GetSetVal5;
  INT64             GetSetMax;
  INT64             Roundtrip;
  INT64             GetSetEn;
  INT64             GetSetDis;
  INT64             RcvEnPi[MAX_CHANNEL];
  INT64             tCL4RcvEn;
  INT64             tCL4RxDqFifoRdEn;
  INT64             tCWL4TxDqFifoWrEn;
  INT64             tCWL4TxDqFifoRdEn;
  INT64             RxDqFifoRdEnRankDel;
  INT64             RxDqsPPi;
  INT64             RxDqsNPi;
  INT64             RxEqInit;
  INT64             RxDqBitPi;
  INT64             TxEqInit;
  INT64             TxDqPi;
  INT64             TxDqsPi;
  INT64             TxDqBitPi;
  INT64             CbenVal;
  INT64             CBEnAmp1Val;
  INT64             RxDataValidDclk;
  INT64             RxDataValidQclk;
  INT64             RxVocMax;
  INT64             RxVocMiddle;
  INT32             TdqsckMin;
  INT32             MaxRxStaggerCtl;
  INT32             tCL;
  INT32             tCWL;
  UINT32            DllBwCtrl;
  UINT32            SubCh;
  UINT32            Offset;
  UINT32            Data32;
  UINT32            Itarget;
  UINT32            IcompUp;
  UINT32            IcompDn;
  UINT32            EffPullUp;
  UINT32            DdrIoGear1;
  UINT32            Gear2;
  UINT32            ClkDelay;
  UINT32            Voh;
  UINT32            PuDeltaV;
  UINT32            StrongWkLeaker;
  UINT16            VssHiSwingTarget;
  UINT16            SAFE;
  UINT16            NS;
  UINT16            VssHi;  // Target VssHi Voltage
  UINT16            VssHiMax;
  UINT16            Target;
  UINT16            Slope;
  UINT16            SlopeSagv;
  UINT8             delta;
  UINT8             Channel;
  UINT8             SubChannel;
  UINT8             Rank;
  UINT8             Byte;
  UINT8             Bit;
  UINT8             VddHi;
  UINT8             Latency[MAX_CHANNEL];
  UINT8             ChannelLatency;
  UINT8             i;
  UINT8             ClkEn;
  UINT8             LowSupEnData;
  UINT8             LowSupEnCcc;
  UINT8             RankPresent;
  BOOLEAN           EnVttOdt;
  BOOLEAN           Lpddr4;
  BOOLEAN           Ddr4;
  BOOLEAN           UlxUlt;
  BOOLEAN           DtHalo;
  BOOLEAN           IclB;
  DDRVREF_CR_DDRCRVREFADJUST1_STRUCT             VrefAdj1;
  DDRVREF_CR_DDRCRVREFADJUST1_STRUCT_A0          VrefAdj1A0;
  DDRVREF_CR_DDRCRVREFADJUST2_STRUCT             VrefAdj2;
  DDRVREF_CR_DDRCRVREFADJUST2_STRUCT_A0          VrefAdj2A0;
  DDRVREF_CR_DDRCRVREFADJUST3_STRUCT             VrefAdj3;
  DDRVSSHIBOTA_CR_DDRCRVTTFORVSSHICORNRTROL_STRUCT VssHiCtrl1;
  DDRCMDCH0_CR_DDRCRCMDCONTROLS_STRUCT           DdrCrCmdControls;
  DDRCMD_CR_DDRCRCMDCONTROLS1_STRUCT             DdrCrCmdControls1;
  DDRCKECH0_CR_DDRCRCTLCONTROLS_STRUCT           DdrCrCkeControls;
  DDRCTLCH0_CR_DDRCRCTLCONTROLS_STRUCT           DdrCrCtlControls;
  DDRCTLCH0_CR_DDRCRCTLCONTROLS1_STRUCT          CtlControls1;
  DDRCTLCH0_CR_DDRCRCTLRANKSUSED_STRUCT          CtlRanksUsed;
  DDRCKECH0_CR_DDRCRCKERANKSUSED_STRUCT          CkeRanksUsed;
  DDRCTLCLKCKE0_CR_DDRCRCTLRANKSUSED_STRUCT      CtlClkCkeRanksUsed;
  DDRCTLCLKCKE0_CR_DDRCRCCC4CKERANKSUSED_STRUCT  Ccc4CkeRanksUsed;
  DDRPHY_COMP_CR_DDRCRCOMPVSSHI_STRUCT           DdrCrCompVssHi;
  DDRSCRAM_CR_DDRMISCCONTROL1_STRUCT             MiscControl1;
  DDRSCRAM_CR_DDRMISCCONTROL2_STRUCT             MiscControl2;
  DDRSCRAM_CR_DDRMISCCONTROL5_STRUCT             MiscControl5;
  DDRPHY_COMP_CR_DDRCRCOMPCTL2_STRUCT            CompCtl2;
  M_COMP_PCU_STRUCT                              CrMCompPcu;
  CH0_CR_SC_WR_DELAY_STRUCT                      ScWrDelay;
  DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_STRUCT        VttGenCtl;
  DDRVTTTOP0_CR_DDRCRVTTGENCONTROL2_STRUCT       VttGenCtl2;
  DDRDATA0_CR_DLLPITESTANDADC_STRUCT             DataDllPiTestAndAdc;
  CLK_CKE_CTL_EN_TYPE                            ClkCkeCtlEn;
  DDRPHY_COMP_CR_DDRCRCTLCOMP_STRUCT             DdrCrCtlComp;
  DDRPHY_COMP_CR_DDRCRCOMPOVR_STRUCT             CompDdrCrCompOvr;
  DDRVREF_CR_DDRCRVREFCONTROL_STRUCT             DdrCrVrefCtl;
  BOOLEAN                                        CkeWaRequired;
  static const UINT32 ScramblerRegOffsets[] = {  // The offsets are not consecutive, hence use a table
    DDRSCRAM_CR_DDRSCRAMBLECH0_REG,
    DDRSCRAM_CR_DDRSCRAMBLECH1_REG,
    DDRSCRAM_CR_DDRSCRAMBLECH2_REG,
    DDRSCRAM_CR_DDRSCRAMBLECH3_REG
  };

  Inputs            = &MrcData->Inputs;
  MrcCall           = Inputs->Call.Func;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  ControllerOut     = &Outputs->Controller[0];
  IntOutputs        = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  IntControllerOut  = &IntOutputs->Controller[0];
  Profile           = Inputs->MemoryProfile;
  Status            = mrcSuccess;
  Vdd               = (Outputs->Lp4x) ? VDD_1_10 : Outputs->VddVoltage[Profile];
  Lpddr4            = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4              = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  GetSetEn          = 1;
  GetSetDis         = 0;
  SAFE              = 0;
  VssHiSwingTarget  = 950;  // VssHi target voltage in mV
  delta             = 20;   // VssHi change voltage during panic, in mV
  LowSupEnCcc       = (Inputs->LowSupplyEnCcc && Lpddr4) ? 1 : 0;
  LowSupEnData      = (Inputs->LowSupplyEnData && Lpddr4) ? 1 : 0;
  MrcCall->MrcSetMem (Latency, sizeof (Latency), 0);
  EnVttOdt          = (Outputs->OdtMode == MrcOdtModeVtt);
  CbenVal           = 3;
  UlxUlt            = (Inputs->CpuModel == cmICL_ULX_ULT);
  DtHalo            = (Inputs->CpuModel == cmICL_DT_HALO_R);
  IclB             = UlxUlt && (Inputs->CpuStepping == csIclB0 || Inputs->CpuStepping == csIclB4);
  Gear2             = Outputs->Gear2 ? 1 : 0; // Used to add extra clock(s) in Gear2 mode
  DdrIoGear1        = Gear2 ? 0 : 1; // DDRIO Register encoding: 1 = Gear1, 0 = Gear2
  QclkFrequency     = (Lpddr4 && Inputs->LpFreqSwitch) ? Outputs->HighFrequency : Outputs->Frequency;

  if (Gear2) {
    QclkFrequency = QclkFrequency / 2;
  }

  CompDdrCrCompOvr.Data       = 0;
  DdrCrCtlComp.Data           = 0;
  CtlRanksUsed.Data           = 0;
  if (Inputs->SafeMode) {
    SAFE = 0xFFFF;
  }

  NS    = ~SAFE;
  VddHi = (Vdd > VDD_1_35) ? 1 : 0; // Set HiVdd bit if Vdd is over 1.35v

  // Get CL per channel
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      ChannelOut       = &ControllerOut->Channel[Channel];
      Latency[Channel] = (UINT8) ChannelOut->Timing[Profile].tCL;
    }
  }

  // Clear out Channel Disabled bits on each iteration of MRC.
  // Otherwise multiple MRC runs with disabling certain channels will cause all channels to be disabled.
  GetSetVal = 0;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocChNotPop, WriteCached, &GetSetVal);
  // Initialize ValidChBitMask and ValidRankMask used during all training steps
  // Program various Rank Occupancy / RanksUsed bits.
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];

    if (Inputs->Ddr4OneDpc) {
      // Make sure ddr4_1dpc feature is turned off before programming rank occupancy - it might be on from the previous SAGV point
      MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccDdr4OneDpc, WriteCached | PrintValue, &GetSetDis);
    }

    // Set the Rank_occupancy per channel.
    //  For Enhanced Channel Mode, CNL map is the following:
    //    Bit    Sub Ch.   Rank
    //    0   -   0         0
    //    1   -   0         1
    //    2   -   1         0
    //    3   -   1         1
    //    4   -   0         2
    //    5   -   0         3
    //    6   -   1         2
    //    7   -   1         3
    GetSetVal = 0;
    if (Outputs->EnhancedChannelMode) {
      for (SubChannel = 0; SubChannel < Outputs->SubChCount; SubChannel++) {
        if ((1 << SubChannel) & ChannelOut->ValidSubChBitMask) {
          GetSetVal |= (INT64) ((UINT32) (ChannelOut->ValidRankBitMask) << (2 * SubChannel));
        }
      }
    } else {
      GetSetVal = ChannelOut->ValidRankBitMask;
    }
    MrcGetSetDdrIoGroupChannel (MrcData, Channel, GsmMccRankOccupancy, WriteNoCache, &GetSetVal);

    if (!MrcChannelExist (Outputs, Channel)) {
      // Set RanksUsed to 0 in CLK, CTL and CKE fubs
      CtlRanksUsed.Data = 0;
      CtlRanksUsed.Bits.CsOdtForCS_ODT_0 = 1;  // Need to select ODT functionality, so that ODT buffers will tri-state.
      CtlRanksUsed.Bits.CsOdtForCS_ODT_1 = 1;
      CtlRanksUsed.Bits.Gear1 = DdrIoGear1;
      CtlRanksUsed.Bits.CsPiClkGateEn = Lpddr4 ? 3 : 0;
      CtlRanksUsed.Bits.PiClkEn = DDRCTLCH0_CR_DDRCRCTLRANKSUSED_PiClkEn_MAX; // Enable all PI clocks, so that ODT buffers will tri-state.
      Offset = OFFSET_CALC_CH (DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG, DDRCTLCH1_CR_DDRCRCTLRANKSUSED_REG, Channel);
      MrcWriteCR (MrcData, Offset, CtlRanksUsed.Data);
      CtlRanksUsed.Bits.PiClkEn = 0;
      Offset = OFFSET_CALC_CH (DDRCKECH0_CR_DDRCRCKERANKSUSED_REG, DDRCKECH1_CR_DDRCRCKERANKSUSED_REG, Channel);
      MrcWriteCR (MrcData, Offset, CtlRanksUsed.Data);

      if (DtHalo) {
        CtlClkCkeRanksUsed.Data  = 0;
        CtlClkCkeRanksUsed.Bits.PiClkEn = DDRCTLCLKCKE0_CR_DDRCRCTLRANKSUSED_PiClkEn_MAX; // Enable all PI clocks, so that ODT buffers will tri-state.
        Offset = OFFSET_CALC_CH (DDRCTLCLKCKE0_CR_DDRCRCTLRANKSUSED_REG, DDRCTLCLKCKE1_CR_DDRCRCTLRANKSUSED_REG, Channel);
        MrcWriteCR (MrcData, Offset, CtlClkCkeRanksUsed.Data);

        Ccc4CkeRanksUsed.Data  = 0;
        Offset = OFFSET_CALC_CH (DDRCTLCLKCKE0_CR_DDRCRCCC4CKERANKSUSED_REG, DDRCTLCLKCKE1_CR_DDRCRCCC4CKERANKSUSED_REG, Channel);
        MrcWriteCR (MrcData, Offset, Ccc4CkeRanksUsed.Data);
      }

      MrcGetSetDdrIoGroupController0 (MrcData, GsmIocChNotPop, ReadFromCache, &GetSetVal);
      GetSetVal |= (INT64) (0x3 << (2 * Channel));
      MrcGetSetDdrIoGroupController0 (MrcData, GsmIocChNotPop, WriteCached, &GetSetVal);

      continue;
    }

    if (Outputs->EnhancedChannelMode) {
      MrcGetSetDdrIoGroupController0 (MrcData, GsmIocChNotPop, ReadFromCache, &GetSetVal);
      for (SubChannel = 0; SubChannel < Outputs->SubChCount; SubChannel++) {
        if (((1 << SubChannel) & ChannelOut->ValidSubChBitMask) == 0) {
          GetSetVal |= (INT64) (1 << (2 * Channel + SubChannel));
        }
      }
      MrcGetSetDdrIoGroupController0 (MrcData, GsmIocChNotPop, WriteCached, &GetSetVal);
    }

    Outputs->ValidChBitMask |= (1 << Channel);
    Outputs->ValidRankMask  |= ChannelOut->ValidRankBitMask;
    Outputs->ValidSubChMask |= ChannelOut->ValidSubChBitMask;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "C%u: ValidRankBitMask=0x%x, ValidRankMask=0x%x, ValidSubChBitMask=0x%x, ValidByteMask=0x%x\n",
      Channel,
      ChannelOut->ValidRankBitMask,
      Outputs->ValidRankMask,
      ChannelOut->ValidSubChBitMask,
      ChannelOut->ValidByteMask
      );

    // Initialize CLK fub
    ClkEn = ChannelOut->ValidRankBitMask;
    if (Inputs->Ddr4DdpSharedClock) { // CLK0 is shared between Rank0 and Rank1
      ClkEn &= 0xD;                   // CLK1 is not used, save power
    }

    // Initialize CTL fub - CS and ODT
    // DDRCTLCHx has enables for Clock[0:1] and 6 CS/ODT's that are configurable.
    // For now, we assume a homogeneious configuration for LPDDR3/4.
    // 0 Enables CTL's to be CS.  This way we only need to set the ODT's that are enabled.
    CtlRanksUsed.Data = 0;
    CtlRanksUsed.Bits.PiClkEn = DDRCTLCH0_CR_DDRCRCTLRANKSUSED_PiClkEn_MAX; // Enable all PI clocks
    CtlRanksUsed.Bits.Gear1 = DdrIoGear1;
    ClkCkeCtlEn.Data8 = (ClkEn & 0x3); // CLK is always bits 0:1 in Ctl fub.
    if (Lpddr4) {
      // Optimization.  A and B step are the same for CLK/Cs0ScA
      ClkCkeCtlEn.Ctl.Lpddr4.CnlB0.Clk    = 1;
      ClkCkeCtlEn.Ctl.Lpddr4.CnlB0.Cs0ScA = (ChannelOut->ValidRankBitMask & 0x1);
      ClkCkeCtlEn.Ctl.Lpddr4.CnlB0.Cs1ScA = ((ChannelOut->ValidRankBitMask >> 1) & 0x1);
      ClkCkeCtlEn.Ctl.Lpddr4.CnlB0.Cs2ScA = ((ChannelOut->ValidRankBitMask >> 2) & 0x1);
      if (ChannelOut->ValidSubChBitMask == 3) { // Second subch is populated
        // Optimization.  X and B step are the same for CLK/Cs1ScB
        ClkCkeCtlEn.Ctl.Lpddr4.CnlB0.Clk    = 3;
        ClkCkeCtlEn.Ctl.Lpddr4.CnlB0.Cs1ScB = ((ChannelOut->ValidRankBitMask >> 1) & 0x1);
        ClkCkeCtlEn.Ctl.Lpddr4.CnlB0.Cs0ScB = ClkCkeCtlEn.Ctl.Lpddr4.CnlB0.Cs0ScA;
        ClkCkeCtlEn.Ctl.Lpddr4.CnlB0.Cs2ScB = ClkCkeCtlEn.Ctl.Lpddr4.CnlB0.Cs2ScA;
      }
      CtlRanksUsed.Bits.CsPiClkGateEn = 3;  // No ODT pins in LP4, so can save power
    } else {
      // Legacy DDR3/4 support
      ClkCkeCtlEn.Ctl.Ddr4.Cs01   = (ChannelOut->ValidRankBitMask & 0x3);
      ClkCkeCtlEn.Ctl.Ddr4.Odt01  = ClkCkeCtlEn.Ctl.Ddr4.Cs01;
      // Force both pins to ODTs regardless of Ranks populated.
      CtlRanksUsed.Bits.CsOdtForCS_ODT_0 = 1;
      CtlRanksUsed.Bits.CsOdtForCS_ODT_1 = 1;
    }
    CtlRanksUsed.Bits.CtlCkTxEn = ClkCkeCtlEn.Data8;
    Offset = OFFSET_CALC_CH (DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG, DDRCTLCH1_CR_DDRCRCTLRANKSUSED_REG, Channel);
    MrcWriteCR (MrcData, Offset, CtlRanksUsed.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCTLCH%d_CR_DDRCRCTLRANKSUSED = 0x%X\n", Channel, CtlRanksUsed.Data);

    Offset = (Channel == 0) ? DDRSCRAM_CR_DDRMISCCONTROL1_REG : DDRSCRAM_CR_DDRMISCCONTROL2_REG;
    MiscControl1.Data = MrcReadCR (MrcData, Offset);
    // Initialize CS/ODT mapping in MISCCONTROL1/2
    if (Outputs->EnhancedChannelMode) {
      MiscControl1.Bits.CsOdtMapping_cs0  = 0; // SchA CS0
      MiscControl1.Bits.CsOdtMapping_cs1  = 3; // SchB CS1
      MiscControl1.Bits.CsOdtMapping_cs2  = 1; // SchA CS1
      MiscControl1.Bits.CsOdtMapping_cs3  = 2; // SchB CS0
      MiscControl1.Bits.CsOdtMapping_odt0 = 8;
      MiscControl1.Bits.CsOdtMapping_odt1 = 10;
    } else {
      // This configures LPDDR3 x64 and DDR4 1DPC.
      MiscControl1.Bits.CsOdtMapping_cs0 = 0;  // CS0
      MiscControl1.Bits.CsOdtMapping_cs1 = 1;  // CS1
      MiscControl1.Bits.CsOdtMapping_odt0 = 4; // ODT0
      MiscControl1.Bits.CsOdtMapping_odt1 = 5; // ODT1
    }

    // Need to ensure rx_analogen_grace_cnt is set to Max for training.
    // Update the final value in MrcMcActivate.
    if (Channel == 0) {
      MiscControl2.Data = MrcReadCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL2_REG);
      MiscControl2.Bits.rx_analogen_grace_cnt = DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_MAX;
      MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL2_REG, MiscControl2.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u: DDRMISCCONTROL%u = 0x%X\n", 1, 2, MiscControl2.Data);
      Data32 = MiscControl1.Data;
    } else {
      MiscControl2.Data = MiscControl1.Data;
      MiscControl2.Bits.rx_analogen_grace_cnt = DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_MAX;
      Data32 = MiscControl2.Data;
    }

    MrcWriteCR (MrcData, Offset, Data32);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u: DDRMISCCONTROL%u = 0x%X\n", Channel, Channel + 1, Data32);

    // Configure 2DPC items.
    if (DtHalo) {
      Offset = (Channel == 0) ? DDRSCRAM_CR_DDRMISCCONTROL5_REG : DDRSCRAM_CR_DDRMISCCONTROL6_REG;
      MiscControl5.Data = 0;
      if (Lpddr4) {
        MiscControl5.Bits.CsOdtMapping_odt2 = 6;  // Unused for LP4. Program default
        MiscControl5.Bits.CsOdtMapping_odt3 = 7;  // Unused for LP4. Program default
        MiscControl5.Bits.CsOdtMapping_cs4  = 9;  // SchA CS 3
        MiscControl5.Bits.CsOdtMapping_cs5  = 11; // SchB CS 3
      } else if (Ddr4) {
        MiscControl5.Bits.CsOdtMapping_odt2 = 6;  // ODT Rank 2
        MiscControl5.Bits.CsOdtMapping_odt3 = 7;  // ODT Rank 3
        MiscControl5.Bits.CsOdtMapping_cs4  = 2;  // CS Rank 2
        MiscControl5.Bits.CsOdtMapping_cs5  = 3;  // CS Rank 3
      }
      MrcWriteCR (MrcData, Offset, MiscControl5.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%u: DDRMISCCONTROL%u = 0x%X\n", Channel, Channel + 5, MiscControl5.Data);
    }

    // Initialize RanksUsed in CKE fub
    ClkEn = 0;
    ClkCkeCtlEn.Data8 = 0;
    CkeRanksUsed.Data  = 0;
    if (Ddr4) {
      ClkCkeCtlEn.Cke.Ddr4.Cke0 = ChannelOut->ValidRankBitMask & 0x1;
      if (Inputs->SeparateCkeDelayDdr4) {
        ClkCkeCtlEn.Cke.Ddr4.Cke1B = (ChannelOut->ValidRankBitMask >> 1) & 0x1;
      } else {
        ClkCkeCtlEn.Cke.Ddr4.Cke1A = (ChannelOut->ValidRankBitMask >> 1) & 0x1;
      }
    } else {
      // LP3 and LP4 share similar layout.
      ClkCkeCtlEn.Cke.Lpddr.Cke01ScA  = ChannelOut->ValidRankBitMask & 0x3;
      if (ChannelOut->ValidSubChBitMask == 3) { // Second subch is populated
        ClkCkeCtlEn.Cke.Lpddr.Cke01ScB = ChannelOut->ValidRankBitMask & 0x3;
      }
    }
    CkeRanksUsed.Bits.PiClkEn = DDRCKECH0_CR_DDRCRCKERANKSUSED_PiClkEn_MAX; // Enable all PI clocks
    CkeRanksUsed.Bits.CtlCkTxEn  = ClkCkeCtlEn.Data8;
    CkeRanksUsed.Bits.Gear1 = DdrIoGear1;
    ClkEn   = ChannelOut->ValidRankBitMask;

    Offset = OFFSET_CALC_CH (DDRCKECH0_CR_DDRCRCKERANKSUSED_REG, DDRCKECH1_CR_DDRCRCKERANKSUSED_REG, Channel);
    MrcWriteCR (MrcData, Offset, CkeRanksUsed.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCKECH%d_CR_DDRCRCKERANKSUSED = 0x%X\n", Channel, CkeRanksUsed.Data);
    // Save for future use in JEDEC Reset, etc.
    ChannelOut->ValidCkeBitMask = ClkEn;
    if (Outputs->EnhancedChannelMode && (ChannelOut->ValidSubChBitMask == 3)) { // Second subch is populated
      ChannelOut->ValidCkeBitMask |= (ClkEn << 2);  // Enable the same CKE pins on the second subch as well
    }

    if (DtHalo) {
      // Initialize RanksUsed in CtlClkCke fub
      ClkCkeCtlEn.Data8 = 0;
      CtlClkCkeRanksUsed.Data  = 0;
      if (Ddr4) {
        RankPresent = (ChannelOut->ValidRankBitMask >> 2) & 0x3;
        ClkCkeCtlEn.CtlClkCke.Ddr4.Clk23  = RankPresent;
        ClkCkeCtlEn.CtlClkCke.Ddr4.Cs23   = RankPresent;
        ClkCkeCtlEn.CtlClkCke.Ddr4.Odt23  = RankPresent;
      } else if (Lpddr4) {
        RankPresent = (ChannelOut->ValidRankBitMask >> 3) & 0x1;
        ClkCkeCtlEn.CtlClkCke.Lpddr4.Clk     = 1;
        ClkCkeCtlEn.CtlClkCke.Lpddr4.Cs3ScA  = RankPresent;
        if (ChannelOut->ValidSubChBitMask == 3) {
          ClkCkeCtlEn.CtlClkCke.Lpddr4.Clk     = 3;
          ClkCkeCtlEn.CtlClkCke.Lpddr4.Cs3ScB  = RankPresent;
        }
        CtlClkCkeRanksUsed.Bits.CsPiClkGateEn = 3;
      }
      CtlClkCkeRanksUsed.Bits.PiClkEn = DDRCTLCLKCKE0_CR_DDRCRCTLRANKSUSED_PiClkEn_MAX; // Enable all PI clocks
      CtlClkCkeRanksUsed.Bits.CtlCkTxEn  = ClkCkeCtlEn.Data8;
      CtlClkCkeRanksUsed.Bits.Gear1 = DdrIoGear1;
      CtlClkCkeRanksUsed.Bits.cs_all_clk_gate_dis  = 1; // @todo check with DE
      CtlClkCkeRanksUsed.Bits.CsClkGateDis_in_idle = 1; // @todo check with DE

      Offset = OFFSET_CALC_CH (DDRCTLCLKCKE0_CR_DDRCRCTLRANKSUSED_REG, DDRCTLCLKCKE1_CR_DDRCRCTLRANKSUSED_REG, Channel);
      MrcWriteCR (MrcData, Offset, CtlClkCkeRanksUsed.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCTLCLKCKE%d_CR_DDRCRCTLRANKSUSED = 0x%X\n", Channel, CtlClkCkeRanksUsed.Data);

      ClkCkeCtlEn.Data8 = 0;
      Ccc4CkeRanksUsed.Data = 0;
      if (Ddr4) {
        ClkCkeCtlEn.Ccc4Cke.Ddr4.Cke23 = (ChannelOut->ValidRankBitMask >> 2) & 0x3;
      } else { // LP4
        RankPresent = (ChannelOut->ValidRankBitMask >> 3) & 1;
        ClkCkeCtlEn.Ccc4Cke.Lpddr4.Cke3ScA = RankPresent;
        if (ChannelOut->ValidSubChBitMask == 3) {
          ClkCkeCtlEn.Ccc4Cke.Lpddr4.Cke3ScB = RankPresent;
        }
      }
      Ccc4CkeRanksUsed.Bits.ctlcktxen = ClkCkeCtlEn.Data8;

      Offset = OFFSET_CALC_CH (DDRCTLCLKCKE0_CR_DDRCRCCC4CKERANKSUSED_REG, DDRCTLCLKCKE1_CR_DDRCRCCC4CKERANKSUSED_REG, Channel);
      MrcWriteCR (MrcData, Offset, Ccc4CkeRanksUsed.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCTLCLKCKE%d_CR_DDRCRCCC4CKERANKSUSED = 0x%X\n", Channel, Ccc4CkeRanksUsed.Data);
    }
  }  //  for Channel
  MrcFlushRegisterCachedData (MrcData);

  // Select the DDRIO ODT Mode. This also programs default RxVref.
  MrcSetIoOdtMode (MrcData, Outputs->OdtMode);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init Data CRs\n");
  // Initialize the Receive Enable Delay Fields, RX FIFO Delays, and Roundtrip Latency.
  // Even though Roundtrip Latency is in the MC domain, it depends on RX IO delays, so we will init it here.
  // Cached fields sits in cache until later flush call.
  if (Lpddr4) {
    TdqsckMin = (Inputs->LoopBackTest) ? 0 : tDQSCK_MIN_LP4;
  } else {
    TdqsckMin = 0;
  }
  TdqsckMin = DIVIDECEIL (TdqsckMin, Outputs->UIps);
  ClkDelay = 1;      // Our initial CLK/CTL PI is 64
//  GetSetVal2  = 0; // RxFlyByDel(Dclk)
//  StepMath    = (2 * (INT32) tCL) + TdqsckMin - ((7 + 1) - (3 + 4)) - (8 - 2) + 1; // RxFifoRdEnTclDelay(Qclk)
//  GetSetVal4  = (StepMath % 2) + DIVIDECEIL (64 + 0, 64);
//  GetSetVal4  = DIVIDECEIL (StepMath, 2); // RxFifoRdEnFlybyDelay(Dclk)
//  GetSetVal3  = StepMath / 2; // RxFifoRdEnTclDelay(Dclk)
//  Roundtrip  = GetSetVal1 + GetSetVal2 + (RcvEnPi / 64)+ 8;
  GetSetVal2 = 0; // RxFlybyDelay(Dclk)
  RxDataValidDclk = Gear2 ? 14 : 7;  // RTL constant
  RxDataValidQclk = 0;  // RTL constant
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    RcvEnPi[Channel] = ClkDelay * 64 + (Ddr4 ? 32 : 0) + 4;  // Start from CTL PI value; add 4 ticks for fixed offset in per-bit deskew
    if (Inputs->LoopBackTest) {
      RcvEnPi[Channel] = 128 + ClkDelay * 64;  // Increase initial RecvEn value so that we can center/margin it later
    }
    tCL = Latency[Channel];
    Data32 = Gear2 ? (2 * (tCL - 10) + TdqsckMin) : (2 * tCL + TdqsckMin - 13); // RxIoTclDelay (Qclk)
    RcvEnPi[Channel] += ((Data32 % 2) * 64);   // If odd number of QCLKs, add one 1 QCLK to RcvEnPi
    tCL4RcvEn = Data32 / 2;                    // RxIoTclDelay (Dclk)

    if (Gear2) {
      Data32 = 2 * tCL + TdqsckMin + (TdqsckMin % 2) - 9;     // RxFifoRdEnTclDelay (Qclk)
      if (!Inputs->IclA0) {
        Data32 += 1;
      }
    } else {
      Data32 = 2 * tCL + TdqsckMin - 6 + 1;                       // RxFifoRdEnTclDelay (Qclk)
    }
    RxDqFifoRdEnRankDel = (Data32 % 2) + ClkDelay;            // In QCLK, "+1" comes from CTL/CMD PI delay of 64 ticks
    tCL4RxDqFifoRdEn = Data32 / 2;                // RxFifoRdEnTclDelay (Dclk)
    if (Inputs->LoopBackTest) {
      tCL4RxDqFifoRdEn += 1;
    }

    // "+1" comes from CTL/CMD PI delay of 64 ticks
    if (Lpddr4) {
      // div_round_ip(tDQSCK + (Gear2 ? (tDQSCK % 2) : 0) + (Lp4 ? 6 : 0) + 2 * tCL + 3),      Gear2 + 1)
      Data32 = TdqsckMin + Gear2 * (TdqsckMin % 2) + ((Lpddr4) ? 6 : 0) + (2 * tCL) + 3 + ClkDelay;
      Data32 = DIVIDECEIL (Data32, Gear2 + 1);
      Data32 += 12;
    } else {
      // Gear1: 3N mode
      // Gear2: 2N mode
      Data32 = (2 * tCL) + 2 * (2 - Gear2) + 3 + ClkDelay;
      Data32 = DIVIDECEIL (Data32, Gear2 + 1);
      Data32 += (12 + Gear2);
    }
    if (Gear2 && !Lpddr4) {
      Data32 += 1;
    }
    if (!Inputs->IclA0) {
      Data32 += 1;
    }
    if (Inputs->LoopBackTest) {
      Data32 += (Gear2 ? 1 : 2);
    }
    Roundtrip = Data32;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "tCL = %d, Roundtrip = %d\n", (UINT32) tCL, (UINT32) Roundtrip);
    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, MRC_IGNORE_ARG, RxIoTclDelay,           WriteToCache | PrintValue, &tCL4RcvEn);
      MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, MRC_IGNORE_ARG, RxFifoRdEnTclDelay,     WriteToCache | PrintValue, &tCL4RxDqFifoRdEn);
      MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, MRC_IGNORE_ARG, RxDqDataValidDclkDelay, WriteToCache | PrintValue, &RxDataValidDclk);
      MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, MRC_IGNORE_ARG, RxDqDataValidQclkDelay, WriteToCache | PrintValue, &RxDataValidQclk);
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RxFlybyDelay,         WriteToCache | PrintValue, &GetSetVal2);
          MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RxFifoRdEnFlybyDelay, WriteToCache | PrintValue, &RxDqFifoRdEnRankDel);
          MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, RoundTripDelay,       WriteToCache | PrintValue, &Roundtrip);
        }
      }
    }
  }

  // Initialize TX FIFO
  // Cached fields sits in cache until later flush call.
  GetSetVal3  = 0; // TxDqFifoRdEnFlybyDelay(Dclk), RptChRepClkOn, TxDqFifoRdEnPerRankDelDis
  GetSetVal4  = 7; // CmdAnlgEnGraceCnt
  GetSetVal5  = MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MAX; // TxAnlgEnGraceCnt
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];
    tCWL = ChannelOut->Timing[Profile].tCWL;

    ScWrDelay.Data = 0;           // @todo: <CNL> GetSet
    ScWrDelay.Bits.Add_tCWL = 0;
    ScWrDelay.Bits.Dec_tCWL = MIN (3, (UINT8) tCWL + ScWrDelay.Bits.Add_tCWL - 2);
    Offset = OFFSET_CALC_CH (CH0_CR_SC_WR_DELAY_REG, CH1_CR_SC_WR_DELAY_REG, Channel);
    MrcWriteCR (MrcData, Offset, ScWrDelay.Data);

    if (Gear2) {
      tCWL4TxDqFifoWrEn  = tCWL - (2 * ScWrDelay.Bits.Dec_tCWL) - (Lpddr4 ? 1 : 3) + (tCWL % 2) - 2 * Lpddr4 * (tCWL % 2);
    } else {
      tCWL4TxDqFifoWrEn  = tCWL - ScWrDelay.Bits.Dec_tCWL + ScWrDelay.Bits.Add_tCWL - 2; // TxDqFifoWrEnTcwlDelay(DClk)
    }
    tCWL4TxDqFifoRdEn  = tCWL4TxDqFifoWrEn - 1; // TxDqFifoRdEnTcwlDelay(DCLK)
    tCWL4TxDqFifoRdEn -= 1; // txdqs_section_rep is 7
    if (Lpddr4) {
      tCWL4TxDqFifoRdEn -= (Gear2 ? 2 : 1);  // On LP4 subtract 1 due to 2tCK WRPRE
    }

    for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
      MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, TxDqFifoWrEnTcwlDelay, WriteToCache | PrintValue, &tCWL4TxDqFifoWrEn);
      MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, TxDqFifoRdEnTcwlDelay, WriteToCache | PrintValue, &tCWL4TxDqFifoRdEn);
      MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, GsmIocRptChRepClkOn,   WriteToCache | PrintValue, &GetSetVal3);
      MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, GsmIocTxDqFifoRdEnPerRankDelDis, WriteToCache | PrintValue, &GetSetVal3);
      MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, GsmIocCmdAnlgEnGraceCnt, WriteToCache | PrintValue, &GetSetVal4);
      MrcGetSetDdrIoGroupChSch (MrcData, Channel, SubCh, GsmIocTxAnlgEnGraceCnt,  WriteToCache | PrintValue, &GetSetVal5);
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
          MrcGetSetDdrIoGroupChSchRnk (MrcData, Channel, SubCh, Rank, TxDqFifoRdEnFlybyDelay, WriteToCache | PrintValue, &GetSetVal3);
        }
      }
    }
  } // for Channel

  // Initialize Rx and Tx Data CRs
  // RxDqsN/P_Pi = 32, RcvEn = 64
  RxDqsPPi    = 32;
  RxDqsNPi    = 32;
  RxEqInit    = 0;  // Start with Rx Equalization Disabled
  RxDqBitPi   = 32; // Program to center (0 offset), ICL Rx perbit deskew range is [0..63]

  // Set TxEq to full strength, TxDqs = 0 and TxDq = 32,
  TxEqInit    = 0x3F; // Full Drive
  TxDqsPi     = 64;
  TxDqPi      = TxDqsPi + (Gear2 ? 96 : 32);
  TxDqBitPi   = 32;  // Program to center (0 offset), ICL Tx perbit deskew range is [0..63]

  // Rx Amplifier voltage offset
    // DDR4 uses N-path, so the range is [0..15]
  // LP4 (P-Path) range is [0..31]
  MrcGetSetLimits (MrcData, RxVoc, NULL, &RxVocMax, NULL);
  RxVocMiddle = ((INT32) RxVocMax + 1) / 2;

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    ChannelOut = &ControllerOut->Channel[Channel];
    for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
      if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
        continue;
      }
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        // RxGroup
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxEq,        WriteToCache, &RxEqInit);
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsNDelay, WriteToCache, &RxDqsNPi);
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RxDqsPDelay, WriteToCache, &RxDqsPPi);
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, RecEnDelay,  WriteToCache, &RcvEnPi[Channel]);

        // Rx/Tx per bit offset - Middle value. Train later.
        for (Bit = 0; Bit < MAX_BITS; Bit++) {
          MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, Byte, Bit, RxDqBitDelay,  WriteToCache | GSM_UPDATE_HOST, &RxDqBitPi);
          MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, Byte, Bit, TxDqBitDelay,  WriteToCache | GSM_UPDATE_HOST, &TxDqBitPi);
          MrcGetSetDdrIoGroupSocket0 (MrcData, Channel, Rank, Byte, Bit, RxVoc,         WriteToCache, &RxVocMiddle);
        } // Bit

        // Set Rx/Tx per-bit deskew step size to Single Step (x1)
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxDeskewCal, WriteToCache, &GetSetDis);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocTxDeskewCal, WriteToCache, &GetSetDis);

        // TxGroup
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxEq,        WriteToCache, &TxEqInit);
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqDelay,   WriteToCache, &TxDqPi);
        MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, Byte, TxDqsDelay,  WriteToCache, &TxDqsPi);
      } // Byte
    } // for Rank
    if (((ChannelOut->ValidRankBitMask & 0x1) == 0) && (ChannelOut->ValidRankBitMask > 0x3)) {
      MrcGetSetLimits (MrcData, RecEnDelay, NULL, &GetSetMax, NULL);
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, rRank0, MAX_SDRAM_IN_DIMM, RecEnDelay, WriteToCache, &GetSetMax);
      MrcGetSetLimits (MrcData, TxDqsDelay, NULL, &GetSetMax, NULL);
      MrcGetSetDdrIoGroupStrobe (MrcData, Channel, rRank0, MAX_SDRAM_IN_DIMM, TxDqsDelay, WriteToCache, &GetSetMax);
    }
  } // Channel
  MrcFlushRegisterCachedData (MrcData);

  // Initial value to corresponding 0.
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DDRCRDATAOFFSETTRAIN_REG, 0x0);
  MrcWriteCrMulticast (MrcData, DDRDATA_CR_DDRCRDATAOFFSETCOMP_REG, 0x0);

  StrongWkLeaker = 0;
  if (Lpddr4) {
    if (UlxUlt && (Inputs->CpuStepping >= csIclD1)) {
      StrongWkLeaker = 0x38;
    } else {
      StrongWkLeaker = CalcStrongLeaker (MrcData);
    }
  }

  // Initialize DataControl0:7
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompOdtStaticDis, WriteToCache | PrintValue, &GetSetDis);
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      if (!MrcByteInChannelExist (MrcData, Channel, Byte)) {
        continue;
      }
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDataOdtStaticDis, WriteToCache | PrintValue, &GetSetDis);
      if (DtHalo) {
        MrcGetSetDdrIoGroupChannelStrobe(MrcData, Channel, Byte, GsmIocForceRxAmpOn, WriteToCache, &GetSetEn);
      }
      if (Lpddr4) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDataCtlLpMode,   WriteToCache | PrintValue, &GetSetEn);
        // Mutually exclusive with DdrCrDataControl0.EnReadPreamble
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLpEarlyRLeak,    WriteToCache | PrintValue, &GetSetEn);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocOdtSampExtEn,    WriteToCache | PrintValue, &GetSetEn);

        // Program leaker and DqsP/N Park Mode
        if (Inputs->IclA0 || IclB) {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLp4ForceDqsNOn,  WriteToCache | PrintValue, &GetSetEn);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLp4ForceDqsPOn,  WriteToCache | PrintValue, &GetSetEn);
        } else { // C0+
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLp4ForceDqsNOnWithLeaker,  WriteToCache | PrintValue, &GetSetEn);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLp4ForceDqsPOnWithLeaker,  WriteToCache | PrintValue, &GetSetEn);
        }
        if (!Inputs->IclA0) {
          GetSetVal = 7;
          if (!IclB) {
            GetSetVal = (StrongWkLeaker >> 4) & 3; // Bits [5:4]
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocStrongWeakLeakerMsb, WriteToCache | PrintValue, &GetSetVal);
            GetSetVal = (StrongWkLeaker & 0x0F);
          }
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocStrongWeakLeaker,      WriteToCache | PrintValue, &GetSetVal);
          GetSetVal = 2;//(IclB) ? 3 : 7;
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLeakerComp,            WriteToCache | PrintValue, &GetSetVal);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLeakerWithTxAnalogEn,  WriteToCache | PrintValue, &GetSetEn);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocStrong2WeakOnDqsOdt,   WriteToCache | PrintValue, &GetSetEn);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocForceDqsOnQuickOdtOff, WriteToCache | PrintValue, &GetSetEn);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDqsOdtSampExtEn,       WriteToCache | PrintValue, &GetSetDis);
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocEnRcvenPreZeroFill,    WriteToCache | PrintValue, &GetSetEn);
          if (!Gear2) {
            MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRcvenFourCycleFill, WriteToCache | PrintValue, &GetSetDis);
          }
        }
      } // Lpddr4

      GetSetVal = 1;  // 2 qclk DLL mask
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDllMask,  WriteToCache | PrintValue, &GetSetVal);

      if (Lpddr4) {
        GetSetVal = 9;   // Rx Bias IComp value for Lp4/x
      } else {
        GetSetVal = 13;  // Rx Bias IComp value for DDR4
      }
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxBiasIComp,    WriteToCache | PrintValue, &GetSetVal);

      GetSetVal = DDRDATA0CH0_CR_DDRCRDATACONTROL6_RxDqsAmpOffset_DEF;
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxDqsAmpOffset, WriteToCache | PrintValue, &GetSetVal);

      GetSetVal = DDRDATA0CH0_CR_DDRCRDATACONTROL2_RxClkStgNum_MAX;
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxClkStg, WriteToCache | PrintValue, &GetSetVal);
      GetSetVal = 1;
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxClkStgNumMsb, WriteToCache | PrintValue, &GetSetVal);

      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxCben, WriteToCache | PrintValue, &CbenVal);
      CBEnAmp1Val = 3;
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, CBEnAmp1, WriteToCache | PrintValue, &CBEnAmp1Val);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocVrefPwrDnEn, WriteToCache | PrintValue, &GetSetEn);
      if (Ddr4) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDataCtlDdr4Mode, WriteToCache | PrintValue, &GetSetEn);
      }

      // Disable per-bit deskew if SAFE mode
      GetSetVal = (Inputs->RdTPbdDis) ? 1 : 0;
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxDeskewDis, WriteToCache | PrintValue, &GetSetVal);
      GetSetVal = (Inputs->WrTPbdDis) ? 1 : 0;
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocTxDeskewDis, WriteToCache | PrintValue, &GetSetVal);

      //Enabling clk gate  for each byte
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocGlobalClkEn, WriteToCache | PrintValue, &GetSetEn);

      if (Lpddr4) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDataCtlLp4Mode,     WriteToCache | PrintValue, &GetSetEn);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLongWrPreambleLp4,  WriteToCache | PrintValue, &GetSetEn);
        GetSetVal = LowSupEnData;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocLowSupEnDqDqs,      WriteToCache | PrintValue, &GetSetVal);
        GetSetVal = (Inputs->Lp4Npath) ? 1 : 0;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxTypeSelect,       WriteToCache | PrintValue, &GetSetVal);
        GetSetVal = (Inputs->Lp4Npath) ? 1 : 0;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxBiasSel,      WriteToCache | PrintValue, &GetSetVal);
        GetSetVal = (Inputs->Lp4Npath) ? 1 : 14;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxBiasRComp,    WriteToCache | PrintValue, &GetSetVal);
      } else if (Ddr4) {
        GetSetVal = 1;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxBiasSel, WriteToCache | PrintValue, &GetSetVal);
      }

      if (Inputs->IclA0 || Gear2) {
        // Initial PiCb values for SDLL / D0
        // For Gear2 need to set to 0, in Steps A also in Gear1
        GetSetVal = 0;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, SdllPiCb, WriteToCache | PrintValue, &GetSetVal);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, D0PiCb, WriteToCache | PrintValue, &GetSetVal);
      }
      // Initial BW ctl for SDLL / D0
      DllBwCtrl = (Gear2) ? 0x00EB9854 : 0xFDB86521; // according to Dll cfg table
      if (QclkFrequency < f1200) {
        DllBwCtrl = DllBwCtrl >> 0;
      } else if (QclkFrequency < 1466) {
        DllBwCtrl = DllBwCtrl >> 4;
      } else if (QclkFrequency < f1733) {
        DllBwCtrl = DllBwCtrl >> 8;
      } else if (QclkFrequency < f2267) {
        DllBwCtrl = DllBwCtrl >> 12;
      } else if (QclkFrequency < f2533) {
        DllBwCtrl = DllBwCtrl >> 16;
      } else if (QclkFrequency < f2800) {
        DllBwCtrl = DllBwCtrl >> 20;
      } else if (QclkFrequency < f3067) {
        DllBwCtrl = DllBwCtrl >> 24;
      } else {
        DllBwCtrl = DllBwCtrl >> 28;
      }

      GetSetVal = DllBwCtrl & 0xF;
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, SdllBwCtrl, WriteToCache | PrintValue, &GetSetVal);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, D0BwCtrl,   WriteToCache | PrintValue, &GetSetVal);

      // Data Xover settings should be updated accordingly to Qclk frequency.
      // values that this field can be set are : FQclk > 2133[0x0], FQclk < 1200[0x3], else[0x1]
      if (QclkFrequency < f1200) {
        GetSetVal = 3;
      } else if (QclkFrequency <= f2133) {
        GetSetVal = 1;
      } else {
        GetSetVal = 0;
      }
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocXoverMinDelayCtl, WriteToCache | PrintValue, &GetSetVal);
    } // Byte

    // Rx Vref Config for LPDDR4
    if (Lpddr4) {
      // @todo: This is tied to the Pull Up Calibration selected in LPDDR4 MR.
      Voh = (Outputs->Lp4x) ? 360 : 440;  // mV
      PuDeltaV = ((Outputs->Lp4x) ? VDD_0_60 : VDD_1_10) - Voh;
      EffPullUp = PuDeltaV * Inputs->RcompTarget[RdOdt];
      EffPullUp = DIVIDEROUND (EffPullUp, Voh);
      MrcSetIdealRxVref (MrcData, Channel, EffPullUp, 80, Inputs->RcompTarget[RdOdt], TRUE);
    }

    ChannelOut      = &ControllerOut->Channel[Channel];
    ChannelLatency  = 2 * Latency[Channel] - 6;
    MaxRxStaggerCtl =  (Lpddr4 ? 6 : 0) + 2 * Latency[Channel] + TdqsckMin + ClkDelay;
    if (Gear2) {
      MaxRxStaggerCtl = (MaxRxStaggerCtl - 10) / 2;
    } else {
      MaxRxStaggerCtl = MaxRxStaggerCtl - 5;
    }

    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      // These CRs do a lot of RMW.
      ChannelOut->DataCompOffset[Byte]  = 0;

      // Stagger byte turn on to reduce dI/dT.
      GetSetVal = ((ChannelLatency * ByteStagger[Byte]) / (UINT8) Outputs->SdramCount) & 0x1F;
      GetSetVal = MIN (GetSetVal, MaxRxStaggerCtl);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxStaggerCtl, WriteToCache | PrintValue, &GetSetVal);
    }
  } // Channel

  // Program delay/duration for ODT/SenseAmp, according to current RecvEn
  UpdateSampOdtTiming (MrcData, 1);

  MrcFlushRegisterCachedData (MrcData);

  if (Inputs->IclA0) {
    MrcWriteCrMulticast (MrcData, DDR_CR_CBTUNE1_REG, 0x10000000); // Picb = 0 for MDLL
  }

  if (Ddr4) {
    MrcSetDefaultRxVrefDdr4 (MrcData, TRUE, TRUE);
  }

  // Initialize VssHi CRs
  // VssHi:
  //   For Y/U: Max {Vccddq-0.95V, 0.3V}
  //   For H/S: Max {Vccddq-0.95V, 0.25V}
  VssHi = ((UINT16) Vdd - VssHiSwingTarget);
  VssHiMax = UlxUlt ? 300 : 250;
  VssHi = MAX (VssHi, VssHiMax);

  Target = (VssHi * 192) / (UINT16) Vdd - 20;  // Sets target for VssHi.

  VssHiCtrl1.Data = 0;
  // Panic for VssHi Step size is VDD/192
  // Panic target should be 70mV (70000uV)
  Data32 = (Vdd * 1000) / 192;
  VssHiCtrl1.Bits.Panic = DIVIDEROUND (70000, Data32);
  VssHiCtrl1.Bits.VccddqLo = (Vdd < VDD_1_35);
  VssHiCtrl1.Bits.VccddqHi = (Vdd > VDD_1_35);
  VssHiCtrl1.Bits.EnVttOdt = EnVttOdt;
  VssHiCtrl1.Bits.VssHiGndSel = (Vdd > VDD_1_10) ? 1 : 0;
  MrcWriteCrMulticast (MrcData, DDRVSSHIGH_CR_DDRCRVTTFORVSSHICORNRTROL_REG, VssHiCtrl1.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DdrCrVttForVsshiControl: 0x%X\n", VssHiCtrl1.Data);

  Data32 = (SAFE) ?
    (2 << 14) + (2 << 8) + (2 << 6) :             // Set BwError and *BWDivider to safe values
    (1 << 22) + (2 << 14) + (1 << 8) + (1 << 6);  // Normal values for *BWDivider, GainBoost
  Data32 += (1 << 16);                                        // Enable Panic Driver
  Data32 += Target + (0 << 10);                               // Set loop sample frequency at max
  if (!SAFE) {
    // CNL changed this from a Disable to Enable.  So we want to always set it unless we're in SAFE mode.
    Data32 |= (1 << 17);                                     // DisPanicDuringCkePwrDn, only disable Panic during CkePwrDn
  }
  MrcWriteCrMulticast (MrcData, DDRVSSHIGH_CR_DDRCRVSSHICONTROL_REG, Data32); // Multicast to both channels
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DdrCrVsshiControl: 0x%X\n", Data32);
  if (!Lpddr4) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init Dimm Vref CRs\n");
    // Initialize Dimm Vref CRs
    // Ideal Slope EQN = (((Target*VccIo)/Vdd)-1)
    //                   ULX/ULT  DT/HALO
    // Slope      Target  1.19     1.19
    // @todo: Select correct target based on CPU SKU.

    Slope = (UINT16)((1190 * Inputs->VccIomV) / (UINT16)Vdd) - 1000;
    Slope = MrcCalcVtSlopeCode (MrcData, Slope);             // Translate ideal slope in CR value

    // Apply offset to VtCode: mV * VccIO / Vddq
    // ULX/ULT = 50.67 mV
    // DT/HALO = 48.33 mV
    // Field is in steps of 4mV.
    Offset = UDIVIDEROUND (((DtHalo) ? 4833 : 5067) * Inputs->VccIomV, Vdd * 100);
    Offset = Offset / 4;

    DdrCrVrefCtl.Data = 0;
    // Apply both VtSlopeA and VtSlopeB, Set SlowBWError = 1, VtOffset
    DdrCrVrefCtl.Bits.VtOffset = Offset;
    DdrCrVrefCtl.Bits.VtSlopeB = (Slope & 0x7);
    DdrCrVrefCtl.Bits.VtSlopeA = ((Slope >> 3) & 0x7);
    DdrCrVrefCtl.Bits.SlowBWError = 1;

    // Enable HiBW mode and SampleDivider
    DdrCrVrefCtl.Bits.HiBWEnable    = 1;
    DdrCrVrefCtl.Bits.SampleDivider = 1;
    DdrCrVrefCtl.Bits.LoBWDivider   = 3;
    DdrCrVrefCtl.Bits.HiBWDivider   = 0;


    MrcWriteCR (MrcData, DDRVREF_CR_DDRCRVREFCONTROL_REG, DdrCrVrefCtl.Data);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DdrCrVrefControl: 0x%X\n", DdrCrVrefCtl.Data);
  }
  // Enable all DimmVref and VddHi based on VddVoltage
  if (Inputs->IclA0) {
    VrefAdj1A0.Data = 0;
    // LPDDR4 VREFs are not controlled by CPU.  Turn off to save power.
    if (!Lpddr4) {
      VrefAdj1A0.Bits.EnDimmVrefCA   = 1;
      if (Outputs->ValidChBitMask & 1) {
        VrefAdj1A0.Bits.EnDimmVrefCh0  = (Inputs->CaVrefConfig == 1) ? 1 : 0;
      }
      if (Outputs->ValidChBitMask & 2) {
        VrefAdj1A0.Bits.EnDimmVrefCh1  = (Inputs->CaVrefConfig == 2) ? 1 : 0;
      }
    }
    VrefAdj2A0.Data = 0;
    VrefAdj2A0.Bits.HiZTimerCtrl  = DDRVREF_CR_DDRCRVREFADJUST2_HiZTimerCtrl_MAX;
    MrcWriteCR (MrcData, DDRVREF_CR_DDRCRVREFADJUST1_REG, VrefAdj1A0.Data);
    MrcWriteCR (MrcData, DDRVREF_CR_DDRCRVREFADJUST2_REG, VrefAdj2A0.Data);
  } else {
    VrefAdj1.Data = 0;
    VrefAdj2.Data = 0;
    VrefAdj3.Data = 0;
    // LPDDR4 VREFs are not controlled by CPU.  Turn off to save power.
    if (!Lpddr4) {
      if (IsDimmPresent (MrcData, 0, 0, 0, 0) == mrcSuccess) {
        VrefAdj1.Bits.Ch0Dimm0CaVrefEn = 1;
        VrefAdj1.Bits.Ch0Dimm0CaVrefIntCtl = MID_INT_VREF;
      }
      if (IsDimmPresent (MrcData, 0, 0, 0, 1) == mrcSuccess) {
        VrefAdj1.Bits.Ch0Dimm1CaVrefEn = 1;
        VrefAdj1.Bits.Ch0Dimm1CaVrefIntCtl = MID_INT_VREF;
      }
      if (IsDimmPresent (MrcData, 0, 0, 1, 0) == mrcSuccess) {
        VrefAdj1.Bits.Ch1Dimm0CaVrefEn = 1;
        VrefAdj1.Bits.Ch1Dimm0CaVrefIntCtl = MID_INT_VREF;
      }
      if (IsDimmPresent (MrcData, 0, 0, 1, 1) == mrcSuccess) {
        VrefAdj3.Bits.Ch1Dimm1CaVrefEn = 1;
        VrefAdj3.Bits.Ch1Dimm1CaVrefIntCtl = MID_INT_VREF;
      }
      VrefAdj1.Bits.VrefDimmSagvAnalogEn = 1;

      // Ideal SlopeSagv EQN = (((Target*VccIo)/Vdd)-1)
      //                   ULX/ULT  DT/HALO
      // SlopeSagv  Target  1.13     1.15
      // @todo: Select correct target based on CPU SKU.
      SlopeSagv = (UINT16)((((DtHalo) ? 1150 : 1130) * Inputs->VccIomV) / (UINT16)Vdd) - 1000;
      SlopeSagv = MrcCalcVtSlopeCode (MrcData, SlopeSagv);             // Translate ideal slope in CR value

     // Apply offsetSagv to VtCode: mV * VccIO / Vddq
     // ULX/ULT = 42.6 mV
     // DT/HALO = 42.2 mV
     // Field is in steps of 4mV.
      Offset = UDIVIDEROUND (((DtHalo) ? 422 : 426) * Inputs->VccIomV, Vdd * 10);
      Offset = Offset / 4;

      VrefAdj2.Bits.VtSlopeAOnSAGV = ((SlopeSagv >>3) & 0x7);
      VrefAdj2.Bits.VtSlopeBOnSAGV = (SlopeSagv & 0x7);
      VrefAdj2.Bits.VtOffsetOnSAGV = Offset;
    }
    VrefAdj2.Bits.HiZTimerCtrl  = DDRVREF_CR_DDRCRVREFADJUST2_HiZTimerCtrl_MAX;
    MrcWriteCR (MrcData, DDRVREF_CR_DDRCRVREFADJUST1_REG, VrefAdj1.Data);
    MrcWriteCR (MrcData, DDRVREF_CR_DDRCRVREFADJUST2_REG, VrefAdj2.Data);
    MrcWriteCR (MrcData, DDRVREF_CR_DDRCRVREFADJUST3_REG, VrefAdj3.Data);
  }

  // Set all DIMM Vref fields to 1/2 VDD
  // CNL sweeps from 0 - VDD.  So we program 1/2 the range: 192.
  if (!Lpddr4) {
    // Set CaVref offset value
    ChangeMargin (MrcData, CmdV, MID_INT_VREF, 0, 1, 0, 0, 0, 0, 1, 0);
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {

      ChannelOut = &ControllerOut->Channel[Channel];
      IntCmdTiming = &IntControllerOut->CmdTiming[Channel];

      Offset = OFFSET_CALC_CH (DDRCMDACH0_CR_DDRCRCMDCONTROLS1_REG, DDRCMDACH1_CR_DDRCRCMDCONTROLS1_REG, Channel);
      DdrCrCmdControls1.Data = MrcReadCR (MrcData, Offset);
      DdrCrCmdControls1.Bits.Gear1 = DdrIoGear1;
      DdrCrCmdControls1.Bits.CMDLowsupEn = LowSupEnCcc;
      if (!Inputs->IclA0) {
        DdrCrCmdControls1.Bits.cmd_eq_strengh = 0;
      }
      MrcWriteCR (MrcData, Offset, DdrCrCmdControls1.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD%c Ch%d DdrCrCmdControls1: 0x%08X\n", 'A', Channel, DdrCrCmdControls1.Data);

      Offset = OFFSET_CALC_CH (DDRCMDBCH0_CR_DDRCRCMDCONTROLS1_REG, DDRCMDBCH1_CR_DDRCRCMDCONTROLS1_REG, Channel);
      DdrCrCmdControls1.Data = MrcReadCR (MrcData, Offset);
      DdrCrCmdControls1.Bits.Gear1 = DdrIoGear1;
      DdrCrCmdControls1.Bits.CMDLowsupEn = LowSupEnCcc;
      if (!Inputs->IclA0) {
        DdrCrCmdControls1.Bits.cmd_eq_strengh = 0;
      }
      MrcWriteCR (MrcData, Offset, DdrCrCmdControls1.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CMD%c Ch%d DdrCrCmdControls1: 0x%08X\n", 'B', Channel, DdrCrCmdControls1.Data);

      // No Clock CTL/PI CR's.  Included in CTL fubs.
      DdrCrCmdControls.Data = 0;
      DdrCrCmdControls.Bits.DllMask   = 1;
      DdrCrCmdControls.Bits.VccddqHi  = VddHi;

      // The above bits are aligned in CMD/CTL/CKE for CNL.
      DdrCrCtlControls.Data = DdrCrCmdControls.Data;
      DdrCrCmdControls.Bits.ClkGateDisable = SAFE;
      DdrCrCtlControls.Bits.ClkGateDisable = SAFE;
      if (Lpddr4) {
        DdrCrCtlControls.Bits.ma3_ma4_par_dis = 1;
      }

      // Initialize CMD CRs
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init CMD CRs\n");
      DdrCrCmdControls.Bits.EarlyWeakDrive  = 3;
      DdrCrCmdControls.Bits.CmdTxEq         = NS & 0; // Enable Early Warning and Cmd DeEmphasis

      DdrCrCmdControls.Bits.CMD_Rate = Gear2;

      Offset = OFFSET_CALC_CH (DDRCMDCH0_CR_DDRCRCMDCONTROLS_REG, DDRCMDCH1_CR_DDRCRCMDCONTROLS_REG, Channel);
      MrcWriteCrMulticast (MrcData, Offset, DdrCrCmdControls.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Ch%d DdrCrCmdControls: 0x%08X\n", Channel, DdrCrCmdControls.Data);

      // Initialize CKE CRs
      DdrCrCkeControls.Data           = DdrCrCmdControls.Data;
      DdrCrCkeControls.Bits.CtlSRDrv  = NS & 1;
      DdrCrCkeControls.Bits.CtlTxEq   = NS & 1; // Enable Weak CKE in SR and Cke DeEmphasis
      DdrCrCkeControls.Bits.CMD_Rate  = Gear2;
      if (Lpddr4) {
        DdrCrCkeControls.Bits.ma3_ma4_par_dis = 1;
      }
      Offset = OFFSET_CALC_CH (DDRCKECH0_CR_DDRCRCTLCONTROLS_REG, DDRCKECH1_CR_DDRCRCTLCONTROLS_REG, Channel);
      MrcWriteCR (MrcData, Offset, DdrCrCkeControls.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCKECH%d_DdrCrCtlControls: 0x%08X\n", Channel, DdrCrCkeControls.Data);

      // Initialize CTL CRs
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init CTL CRs\n");
      DdrCrCtlControls.Bits.CtlTxEq  = (NS & 1);  // Enable Weak CKE in SR and Cke DeEmphasis
      DdrCrCtlControls.Bits.CtlSRDrv = (NS & 0);  // Enable Weak CKE in SR and Cke DeEmphasis
      DdrCrCtlControls.Bits.CMD_Rate = Gear2;
      Offset = OFFSET_CALC_CH (DDRCTLCH0_CR_DDRCRCTLCONTROLS_REG, DDRCTLCH1_CR_DDRCRCTLCONTROLS_REG, Channel);
      MrcWriteCR (MrcData, Offset, DdrCrCtlControls.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCTLCH%d_DdrCrCtlControls: 0x%08X\n", Channel, DdrCrCtlControls.Data);

      CtlControls1.Data = 0;
      // Set CKE to constant 1's (0x6).  3-bit subfields: Cs0,Cs1,Cs2,Cs3,Odt0,Odt1
      CtlControls1.Bits.MapCkeForScOdt = 6 | (6 << 3) | (6 << 6) | (6 << 9) | (6 << 12) | (6 << 15);
      CtlControls1.Bits.CKELowsupEn = 0;
      CtlControls1.Bits.CLKLowsupEn = LowSupEnCcc;
      CtlControls1.Bits.CTLLowsupEn = 0;
      CtlControls1.Bits.CMDLowsupEn = LowSupEnCcc;
      Offset = OFFSET_CALC_CH (DDRCTLCH0_CR_DDRCRCTLCONTROLS1_REG, DDRCTLCH1_CR_DDRCRCTLCONTROLS1_REG, Channel);
      MrcWriteCR (MrcData, Offset, CtlControls1.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCTLCH%d_DdrCrCtlControls1: 0x%08X\n", Channel, CtlControls1.Data);

      Offset = OFFSET_CALC_CH (DDRCKECH0_CR_DDRCRCTLCONTROLS1_REG, DDRCKECH1_CR_DDRCRCTLCONTROLS1_REG, Channel);
      // DDRCRCTLCONTROLS1 has the same layout in CTL and CKE fubs
      MrcWriteCR (MrcData, Offset, CtlControls1.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRCKECH%d_DdrCrCtlControls1: 0x%08X\n", Channel, CtlControls1.Data);

      // Initialize CRs shared between CKE/CTL/CMD/CLK
      // PI setting must match value written for TxDQs above.
      // There are no shared registers for CLK, only CKE/CTL but only CTLPICODING and CTLCOMPOFFSET
      // Set CTL/CLK PI to 64.
      // Set CMD to 64 for DDR4/LPDDR4, for ideal initial command centering.
      GetSetVal = MRC_INITIAL_CMD_PI;
      Offset = MRC_CMD_GRP_MAX;
      for (i = 0; i < Offset; i++) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, i, CmdGrpPi, WriteToCache | PrintValue, &GetSetVal);
        IntCmdTiming->CmdPiCode[i] = (UINT8) GetSetVal;
      }
      GetSetVal = MRC_INITIAL_CTL_PI;
      // ULX/ULT only have two ranks.  DT has 4.  Same number of CCC groups as ranks.
      Offset = (UlxUlt) ? MRC_U_Y_CCC_GRP_MAX : MRC_H_S_CCC_GRP_MAX;
      for (i = 0; i < Offset; i++) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, i, CtlGrpPi, WriteToCache | PrintValue, &GetSetVal);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, i, ClkGrpPi, WriteToCache | PrintValue, &GetSetVal);
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, i, CkeGrpPi, WriteToCache | PrintValue, &GetSetVal);
        IntCmdTiming->CtlPiCode[i] = (UINT8) GetSetVal;
        IntCmdTiming->ClkPiCode[i] = (UINT8) GetSetVal;
        IntCmdTiming->CkePiCode[i] = (UINT8) GetSetVal;
      }
      GetSetVal = 0;
      for (SubCh = 0; SubCh < Outputs->SubChCount; SubCh++) {
        // Set Cmd Comp offsets to Zero for now. May offset comp in future
        MrcGetSetDdrIoCmdGroup (MrcData, Channel, SubCh, CmdRCompDrvDownOffset, WriteToCache, &GetSetVal);
        MrcGetSetDdrIoCmdGroup (MrcData, Channel, SubCh, CmdRCompDrvUpOffset, WriteToCache, &GetSetVal);
        MrcGetSetDdrIoCmdGroup (MrcData, Channel, SubCh, CmdSCompOffset, WriteToCache, &GetSetVal);
      }

      // Set Ctl Comp offsets to Zero for now. May offset comp in future
      MrcGetSetDdrIoCmdGroup (MrcData, Channel, 0, CtlRCompDrvDownOffset, WriteToCache, &GetSetVal);
      MrcGetSetDdrIoCmdGroup (MrcData, Channel, 0, CtlRCompDrvUpOffset, WriteToCache, &GetSetVal);
      MrcGetSetDdrIoCmdGroup (MrcData, Channel, 0, CtlSCompOffset, WriteToCache, &GetSetVal);

      // Set Cke Comp offsets to Zero for now. May offset comp in future
      MrcGetSetDdrIoCmdGroup(MrcData, Channel, 0, CkeRCompDrvDownOffset, WriteToCache, &GetSetVal);
      MrcGetSetDdrIoCmdGroup(MrcData, Channel, 0, CkeRCompDrvUpOffset, WriteToCache, &GetSetVal);
      MrcGetSetDdrIoCmdGroup(MrcData, Channel, 0, CkeSCompOffset, WriteToCache, &GetSetVal);

      // Set Clk Comp offsets to Zero for now. May offset comp in future
      MrcGetSetDdrIoCmdGroup (MrcData, Channel, 0, ClkSCompOffset, WriteToCache, &GetSetVal);

      if (DtHalo) {
        GetSetVal = 7;
      }
      MrcGetSetDdrIoCmdGroup (MrcData, Channel, 0, ClkRCompDrvDownOffset, WriteToCache, &GetSetVal);
      MrcGetSetDdrIoCmdGroup (MrcData, Channel, 0, ClkRCompDrvUpOffset, WriteToCache, &GetSetVal);

      // Enable Changing Clk params on the fly
      GetSetVal = 1;
      MrcGetSetDdrIoCmdGroup (MrcData, Channel, 0, ClkCompOnTheFlyUpdtEn, WriteToCache, &GetSetVal);
    }
  } // End of for Channel...

  // Set Cmd/Ctl/Clk TCO Comp to middle of the range
  GetSetVal = 32;
  MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, TcoCompCodeClk, WriteToCache | PrintValue, &GetSetVal);
  MrcGetSetDdrIoGroupChannel (MrcData, MAX_CHANNEL, TcoCompCodeCtl, WriteToCache | PrintValue, &GetSetVal);
  for (i = 0; i < MRC_CMD_GRP_MAX; i++) {
    MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, i, TcoCompCodeCmd, WriteToCache | PrintValue, &GetSetVal);
  }

  MrcFlushRegisterCachedData (MrcData);

  // Disable Periodic RComp
  // Set periodic comp = (10uS * 2^COMP_INT)
  CrMCompPcu.Data               = 0;
  CrMCompPcu.Bits.COMP_DISABLE  = 1;
  CrMCompPcu.Bits.COMP_INTERVAL = COMP_INT;  // Set COMP_INT to happen every 10mS
  MrcWriteCR (MrcData, M_COMP_PCU_REG, CrMCompPcu.Data);

  // Initialize COMP CRs for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  GetSetVal = SAFE;             // Override PwrDn in Safe Mode
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompClkOn, WriteToCache, &GetSetVal);

  // Should be the same as TxTrainRank.TxEqualization[5:4]
  GetSetVal = (DtHalo) ? 0 : 3;
  MrcGetSetDdrIoGroupController0 (MrcData, DqRcompStatLegs, WriteToCache, &GetSetVal);

  GetSetVal = (Vdd < VDD_1_35) ? 1 : 0;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompVccddqLo, WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  // Initialize COMP CRs for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  CompCtl2.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL2_REG);
  CompCtl2.Bits.PanicDrvUpVref = 76;
  CompCtl2.Bits.DQDQSLowsupEn = LowSupEnData;
  CompCtl2.Bits.CLKLowsupEn   = LowSupEnCcc;
  CompCtl2.Bits.CMDLowsupEn   = LowSupEnCcc;
  CompCtl2.Bits.CTLLowsupEn   = 0;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL2_REG, CompCtl2.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DdrCrCompCtl2: 0x%x\n", CompCtl2.Data);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init COMP CRs\n");
  for (i = 0; i < sizeof (CompParamList) / sizeof (CompParamList[0]); i++) {
    UpdateCompTargetValue (MrcData, CompParamList[i], Inputs->RcompTarget[i], TRUE);
  }
  CalcStaticDynamicLegSize (MrcData);

  // Calculate Target Values for VssHi Panic Driver
  // Rtarget = Tperiod / Cdie / ln( VssHi / (VssHi - Delta) )
  DdrCrCompVssHi.Data = 0;

  // Target Current.  pF * mV / pS -> mA
  Itarget = CDIEVSSHI * delta / Outputs->UIps;
  // Compensated to this current
  IcompDn = (Inputs->VccIomV - VssHi) / Inputs->RcompResistor[2];
  IcompUp = VssHi / Inputs->RcompResistor[2];

  DdrCrCompVssHi.Bits.VtOffset = 0x1F;
  // VSSHI Slope Targets: ULX/ULT - 1.3966, DT/HALO - 1.4305.  Min Error is 2^(-3) + 2^(-3)
  DdrCrCompVssHi.Bits.VtSlopeA = 0x5;
  DdrCrCompVssHi.Bits.VtSlopeB = 0x5;
  // Calculate multiplier to get target current
  DdrCrCompVssHi.Bits.PanicCompUpMult = MIN ((Itarget / IcompUp), DDRPHY_COMP_CR_DDRCRCOMPVSSHI_PanicCompUpMult_MAX);
  DdrCrCompVssHi.Bits.PanicCompDnMult = MIN ((Itarget / IcompDn), DDRPHY_COMP_CR_DDRCRCOMPVSSHI_PanicCompDnMult_MAX);
  Offset = DDRPHY_COMP_CR_DDRCRCOMPVSSHI_REG;
  MrcWriteCR (MrcData, Offset, DdrCrCompVssHi.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DdrCrCompVssHi = 0x%08X\n", DdrCrCompVssHi.Data);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init MISC CRs\n");
  // Initialize MISC CRs
  GetSetVal = 12;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocWlLatency, WriteToCache, &GetSetVal);
  if (Lpddr4) {
    GetSetVal = 3;
    MrcGetSetDdrIoGroupController0 (MrcData, GsmIocLpRcvenCtrl, WriteToCache, &GetSetVal);
  }
  GetSetVal = 3; // 8 QCLKs
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocWlWakeCyc, WriteToCache, &GetSetVal);
  GetSetVal = 5; // 128 QCLKs
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocWlSleepCyc, WriteToCache, &GetSetVal);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocDisDataIdlClkGate, WriteToCache, &GetSetEn);
  MrcFlushRegisterCachedData (MrcData);

  // Keep scrambling disabled for training
  for (i = 0; i < ARRAY_COUNT (ScramblerRegOffsets); i++) {
    MrcWriteCR (MrcData, ScramblerRegOffsets[i], 0);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Update LS COMP CRs\n");

  CkeWaRequired = FALSE;
  if (UlxUlt) {
     if (Inputs->CpuStepping == csIclB0) {
      // SKPD (PCI 0:0:0:DC ) Register bit 0 : 1 for B1 substep
      Offset = Inputs->PciEBaseAddress + MrcCall->MrcGetPcieDeviceAddress (0, 0, 0, SKPD_0_0_0_PCI_REG);
      CkeWaRequired = (((MrcCall->MrcMmioRead32 (Offset)) & MRC_BIT0) == 0);
     } else if (Inputs->CpuStepping == csIclA0) {
       CkeWaRequired = TRUE;
     }
  }

  // code for CKE glitch issue for A0 and B0 only in UltUlx
  if (CkeWaRequired) {
      // COMP Override
    CompDdrCrCompOvr.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR_REG);
    CompDdrCrCompOvr.Bits.CtlDrvD = 1;
    CompDdrCrCompOvr.Bits.CtlDrvU = 1;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR_REG, CompDdrCrCompOvr.Data);
    DdrCrCtlComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCTLCOMP_REG);
    DdrCrCtlComp.Bits.RcompDrvDown = 63;
    DdrCrCtlComp.Bits.RcompDrvUp   = 63;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCTLCOMP_REG, DdrCrCtlComp.Data);
  }

  // Use SAFE for DLLPITESTANDADC settings
  DataDllPiTestAndAdc.Data = 0;
  DataDllPiTestAndAdc.Bits.PhaseDrvPwrSavOn = NS;
  // Multicast all DLLPITESTANDADC.  Each Fub has same CR layout.
  MrcWriteCrMulticast (MrcData, DDR_CR_DLLPITESTANDADC_REG, DataDllPiTestAndAdc.Data);

  if (Outputs->OdtMode == MrcOdtModeVtt) {
    MrcSetupVtt (MrcData, TRUE);
  }

  // VTT programming
  VssHiCtrl1.Data = 0;
  VttGenCtl.Data = 0;
  VttGenCtl2.Data = 0;
  if (Ddr4 && Inputs->DqPinsInterleaved) {
    VttGenCtl.Bits.DdrCRForceODTOn = 1;
  }
  VttGenCtl.Bits.Target = 600 * 192 / Vdd - 20;
  //  VccddqHi       VccddqLo       Vdd
  //  (Vdd == 1.5v)  (Vdd == 1.2v)
  //  0                 1           1.2v
  //  0                 0           1.35v
  //  1                 0           1.5v
  //  1                 1           reserved for future use
  VssHiCtrl1.Bits.VccddqHi  = (Vdd > VDD_1_35);
  VssHiCtrl1.Bits.VccddqLo  = (Vdd < VDD_1_35);
  VttGenCtl.Bits.EnVttOdt  = EnVttOdt;
  VttGenCtl.Bits.Enable2VtNmos = 1;
  VttGenCtl.Bits.Enable2VtPmos = 1;
  VttGenCtl2.Bits.VttUsePmosCompCRThreshold = 52;
  // Panic step size at uV resolution
  Data32 = (Vdd * 1000) / 384;
  // Panic at 25mV (25000uV)
  VttGenCtl.Bits.Panic = DIVIDEROUND (VPANIC1, Data32);
  MrcWriteCR (MrcData, DDRVTTTOP0_CR_DDRCRVTTGENCONTROL_REG, VttGenCtl.Data);
  MrcWriteCR (MrcData, DDRVTTTOP1_CR_DDRCRVTTGENCONTROL_REG, VttGenCtl.Data);
  MrcWriteCR (MrcData, DDRVTTMIDLOW0_CR_DDRCRVTTGENCONTROL_REG, VttGenCtl.Data);
  MrcWriteCR (MrcData, DDRVTTMIDLOW1_CR_DDRCRVTTGENCONTROL_REG, VttGenCtl.Data);

  // Panic at 40mV
  VttGenCtl.Bits.Panic = DIVIDEROUND (VPANIC2, Data32);
  MrcWriteCR (MrcData, DDRVTTMIDHIGH0_CR_DDRCRVTTGENCONTROL_REG, VttGenCtl.Data);
  MrcWriteCR (MrcData, DDRVTTMIDHIGH1_CR_DDRCRVTTGENCONTROL_REG, VttGenCtl.Data);
  MrcWriteCR (MrcData, DDRVTTBOT0_CR_DDRCRVTTGENCONTROL_REG, VttGenCtl.Data);
  MrcWriteCR (MrcData, DDRVTTBOT1_CR_DDRCRVTTGENCONTROL_REG, VttGenCtl.Data);

  // VttGenCtl2
  MrcWriteCrMulticast (MrcData, DDRVTT_CR_DDRCRVTTGENCONTROL2_REG, VttGenCtl2.Data);

  // Set the DDR voltage in PCU
  MrcSetPcuDdrVoltage (MrcData, Vdd);

  return Status;
}

/**
  This function initializes the Slew Rate of DQ, CMD, CTL and CLK buffers in DDRIO.
  Initialization consists of the following steps:
  1. Find Min and Max chain length in Cycle lock.
     Max is defined as 2 cell more than the number of cells where the Comp code trend reverses (Harmonic Lock)
  2. Calculate the desired buffer segment delay:
     DesiredDelay [pSec] = Vswing [mV] * Derating / (DesiredSlewRate [pSec/mv] * NumSegmentsPerBuffer)
  3. Calculate required number of Cells (assuming Cycle Lock)
     DelayCells = round(QClkCycle [pSec] / DesiredDelay [pSec])
  4. If Delay Cells < Max delay
     4a. ForceRComp
     4b. Done
  5. Else If Delay Cells >= Max delay
     5a. Set Phase Lock.
     5b. DelayCells = round(QClkCycle [pSec] / (2* DesiredDelay [pSec]))
     5c. If Delay Cells <= Max delay
         5c1. ForceRComp
         5c2. If CompCode == 0 - Set ByPass
     5d. Else:
         4d1. Set Bypass

  For LPDDR4 we first  perform a transition to the high frequency point in order to calculate Max number of cells at the top
  frequency which is the limiter.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrScompInit (
  IN OUT MrcParameters *const MrcData
  )
{
  static const GSM_GT SCompCells[4] = {TxSlewRate, CmdSlewRate, CtlSlewRate, ClkSlewRate};
  static const GSM_GT SCompPC[4] = {DqScompPC, CmdScompPC, CtlScompPC, ClkScompPC};
  static const GSM_GT SCompCode[4] = {SCompCodeDq, SCompCodeCmd, SCompCodeCtl, SCompCodeClk};
  static const UINT8  DesiredSlewRateUDdr4[4] = {45, 32, 30, 45};  // units of [mV/ps] and multiplied by 10 for integer math precision in DesiredBufferSegmentDelay calculation below.
  static const UINT8  DesiredSlewRateHDdr4[4] = {45, 30, 30, 50};  // units of [mV/ps] and multiplied by 10 for integer math precision in DesiredBufferSegmentDelay calculation below.
  static const UINT8  DesiredSlewRateLpdr4[4] = {55, 35, 35, 45};  // units of [mV/ps] and multiplied by 10 for integer math precision in DesiredBufferSegmentDelay calculation below.
  static const UINT8  RcompParam[4] = {WrDS, WrDSCmd, WrDSCtl, WrDSClk};
  static const UINT8  ScompParam[4] = {SCompDq, SCompCmd, SCompCtl, SCompClk};
  static const BOOLEAN  BypassOverride = TRUE;    // Simple knob to enable SCOMP bypass
  static const BOOLEAN  ScompForceByPassParam[4] = { TRUE, FALSE, FALSE, TRUE };
  const  char           *ByPassString;
  static const UINT8    SCompCellsGb = 4;    // Guardband on the number of cells determined by the possible drift of harmonic lock over VT drift

  MrcInput          *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcIntOutput      *IntOutputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT8 const       *DesiredSlewRate;
  MrcVddSelect      Vdd;
  INT64             GetSetVal;
  UINT32            OdtWr;
  UINT32            OdtNom;
  UINT32            DelayCells;
  UINT32            DesiredBufferSegmentDelay[4];
  UINT32            MinChainLength;
  UINT32            MaxChainLength;
  UINT32            VSwing;
  UINT32            VHigh;
  UINT32            VLow;
  UINT32            Voh;
  UINT32            Vtt;
  UINT32            VccIo;
  UINT32            Rtt;
  UINT32            Divisor;
  UINT32            Dividend;
  UINT32            OdtValue;
  UINT32            OdtPark;
  UINT32            Data32;
  UINT32            Offset;
  UINT16            CpuRon;
  UINT8             ScompIndex;
  UINT8             ScompInitMax;
  UINT8             CellIndex;
  UINT8             Max;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Dimm;
  UINT8             SCompResult[4][SCOMP_CELLS_MAX + 1];
  UINT8             SCompCodeResult;
  UINT8             SCompCount[4];
  UINT8             NCells[4][MAX_EDGES];
  UINT8             ChannelsPopulated;
  UINT8             DimmSerialResistor;
  UINT8             SegmentsPerBuffer;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr4;
  BOOLEAN           Is2DPC;
  BOOLEAN           Is2RDimm;
  BOOLEAN           Lp4FreqSwitch;
  DDRPHY_COMP_CR_DDRCRCOMPOVR_STRUCT            DdrCrCompOvr;
  DDRCMDCH0_CR_DDRCRCMDCONTROLS_STRUCT          DdrCrCmdControls;
  DDRCTLCH0_CR_DDRCRCTLRANKSUSED_STRUCT         CtlRanksUsed;
  DDRCKECH0_CR_DDRCRCKERANKSUSED_STRUCT         CkeRanksUsed;
  DDRCTLCLKCKE0_CR_DDRCRCTLRANKSUSED_STRUCT     CccCtlRanksUsed;
  DDRCTLCLKCKE0_CR_DDRCRCCC4CKERANKSUSED_STRUCT Ccc4CkeRanksUsed;

  Inputs            = &MrcData->Inputs;
  MrcCall           = Inputs->Call.Func;
  Outputs           = &MrcData->Outputs;
  IntOutputs        = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  ControllerOut     = &Outputs->Controller[0];
  Debug             = &Outputs->Debug;
  Ddr4              = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4            = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Vdd               = (Outputs->Lp4x) ? VDD_1_10 : Outputs->VddVoltage[Inputs->MemoryProfile];
  VccIo             = Inputs->VccIomV;
  ScompInitMax      = ARRAY_COUNT (ScompParam);
  Dividend          = 0;
  Lp4FreqSwitch     = (Lpddr4 &&
                       (Inputs->LpFreqSwitch == TRUE) &&
                       (Inputs->TrainingEnables.ECT == 1) &&
                       (Inputs->BootMode == bmCold));

  if (Lp4FreqSwitch) {
    MrcFrequencySwitch (MrcData, Outputs->HighFrequency, TRUE);
  }

  // Determine slew rate targets according to CPU Sku and DDR type
  if (Inputs->CpuidModel == cmICL_ULX_ULT) {
    if (Lpddr4) {
      DesiredSlewRate = DesiredSlewRateLpdr4;
    } else {
      DesiredSlewRate = DesiredSlewRateUDdr4;
    }
  } else {
    // DT/Halo
    DesiredSlewRate = DesiredSlewRateHDdr4;
  }

  for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
    // Setup of DQ, CMD, CTL, CLK SCompPC
    GetSetVal = 1; // Cycle lock
    MrcGetSetDdrIoGroupController0 (MrcData, SCompPC[ScompIndex], WriteCached, &GetSetVal);
  }

  MrcCall->MrcSetMem (SCompResult[0], sizeof (SCompResult), 0);
  MrcCall->MrcSetMem (SCompCount, sizeof (SCompCount), 0);
  MrcCall->MrcSetMem ((UINT8 *) NCells, sizeof (NCells), 0);
  // Gather results for 3-15 ScompCells
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\tScompCode\n\t\tDq\tCmd\tCtl\tClk\nScompCells\n");
  for (CellIndex = SCOMP_CELLS_MIN; CellIndex <= SCOMP_CELLS_MAX; CellIndex++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d\t", CellIndex);
    for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
      // Setup of DQ, CMD, CTL, CLK ScompCells
      GetSetVal = CellIndex;
      MrcGetSetDdrIoGroupController0 (MrcData, SCompCells[ScompIndex], WriteCached, &GetSetVal);
    }

    // Force Comp Cycle
    ForceRcomp (MrcData);

    // Read the SCOMP results
    for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
      MrcGetSetDdrIoGroupController0 (MrcData, SCompCode[ScompIndex], ReadUncached, &GetSetVal);
      SCompResult[ScompIndex][CellIndex] = (UINT8) GetSetVal;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", SCompResult[ScompIndex][CellIndex]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  }

  DdrCrCompOvr.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR_REG);

  // Compare results
  for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
    if (ScompParam[ScompIndex] != SCompDq) {
      Max = 62;
    } else {
      Max = 29;
    }
    // DQ, CMD, CTL, CLK ScompCells
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s ", GlobalCompOffsetStr[ScompParam[ScompIndex]]);
    if (SCompResult[ScompIndex][SCOMP_CELLS_MIN] <= 1) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Setting Slew Rate Compensation Override\n");
      DdrCrCompOvr.Data |= (1 << (ScompIndex + 10));
    } else {
      for (CellIndex = SCOMP_CELLS_MIN; CellIndex <= SCOMP_CELLS_MAX; CellIndex++) {
        // Find Minimum usable chain length with unsaturated COMP code value, and at least 2 ticks of margin.
        if ((NCells[ScompIndex][0] == 0) && (SCompResult[ScompIndex][CellIndex] >= 2) && (SCompResult[ScompIndex][CellIndex] < Max)) {
          NCells[ScompIndex][0] = CellIndex;
        }
        if (SCompResult[ScompIndex][CellIndex] > Max) {
          //Exceeds upper limit.
          continue;
        }
        NCells[ScompIndex][1] = CellIndex;
        if (CellIndex == SCOMP_CELLS_MIN) {
          // Skip first index for determining Harmonic lock.
          continue;
        }
        if ((SCompResult[ScompIndex][CellIndex] > SCompResult[ScompIndex][CellIndex - 1]) || (SCompResult[ScompIndex][CellIndex] == 0)) {
          // Harmonic lock occurred.
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Harmonic Lock Occured - ");
          NCells[ScompIndex][1] = (CellIndex < SCompCellsGb) ? 0 : (CellIndex - SCompCellsGb);
          break;
        }
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SCompCellsMin = %d, SCompCellsMax = %d\n", NCells[ScompIndex][0], NCells[ScompIndex][1]);
    }
  }
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR_REG, DdrCrCompOvr.Data);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nScompType\tVSwing\tBufferSegDelay\tSCompPC \tSCompCells\n");
  for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %s\t", GlobalCompOffsetStr[ScompParam[ScompIndex]]);
    // Determine Vtt and Voh based on partition being calculated, Dram Type, and source mux
    if (ScompParam[ScompIndex] == SCompDq) {
      Voh = (Lpddr4 && Inputs->LowSupplyEnData) ? VccIo : Vdd;
      Vtt = (Lpddr4) ? 0 : Vdd;
      SegmentsPerBuffer = 2;
    } else {
      Voh = (Lpddr4 && Inputs->LowSupplyEnCcc && (ScompParam[ScompIndex] != SCompCtl)) ? VccIo : Vdd;
      Vtt = (Lpddr4) ? 0 : Vdd / 2;
      SegmentsPerBuffer = (ScompParam[ScompIndex] == SCompClk) ? 2 : 3;
    }
    if ((NCells[ScompIndex][0] == 0) && (NCells[ScompIndex][1] == 0)) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Slew Rate Compensation Override Set\n");
      GetSetVal = 0;
    } else {
      VSwing = 0;
      MinChainLength = MAX (SCOMP_CELLS_MIN, NCells[ScompIndex][0]);
      MaxChainLength = MIN (SCOMP_CELLS_MAX, NCells[ScompIndex][1]);
      ChannelsPopulated = 0;
      CpuRon = Inputs->RcompTarget[RcompParam[ScompIndex]];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        if (MrcChannelExist (Outputs, Channel)) {
          ChannelOut = &ControllerOut->Channel[Channel];
          ChannelsPopulated++;
          Is2DPC =  (ChannelOut->DimmCount == 2);
          DimmSerialResistor = 15;
          OdtValue = 0;
          if (ScompParam[ScompIndex] == SCompDq) {
            if (!Outputs->DramDqOdtEn) {
              VSwing += Voh;
              continue;
            }
          }
          for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += MAX_RANK_IN_DIMM) {
            if (MrcRankInChannelExist (MrcData, Rank, Channel)) {
              Dimm = RANK_TO_DIMM_NUMBER (Rank);
              Is2RDimm = (ChannelOut->Dimm[Dimm].RankInDimm == 1);
              if ((DimmSerialResistor != 0) && (ChannelOut->Dimm[Dimm].ModuleType == NonDimmMemoryPackage)) {
                DimmSerialResistor = 0;
              }
              switch (ScompParam[ScompIndex]) {
                case SCompDq:
                  OdtWr = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtWr, FALSE, 0, TRUE);
                  if (Ddr4) {
                    OdtNom = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtNom, FALSE, 0, TRUE);
                    OdtPark = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtPark, FALSE, 0, TRUE);
                    OdtPark = (Is2RDimm) ? OdtPark : 0xFFFF;
                    if (Is2DPC) {
                      // OdtValue = OdtWr || (1st Dimm is 2 rank) ? OdtPark : 0xFFFF) || OdtNom || (2nd Dimm is 2 rank) ? OdtPark : 0xFFFF
                      if (Dimm == 0) {
                        Dividend = OdtWr * OdtPark;
                        Divisor = OdtWr + OdtPark;
                        OdtValue = DIVIDEROUND (Dividend, Divisor);
                      } else {
                        Dividend = OdtNom * OdtPark;
                        Divisor = OdtNom + OdtPark;
                        Data32 = DIVIDEROUND (Dividend, Divisor);
                        Dividend = Data32 * OdtValue;
                        Divisor = Data32 + OdtValue;
                        OdtValue = DIVIDEROUND (Dividend, Divisor);
                      }
                    } else {
                      // OdtValue = OdtWr || (Dimm is 2 rank) ? OdtPark : 0xFFFF
                      Dividend = OdtWr * OdtPark;
                      Divisor = OdtWr + OdtPark;
                      OdtValue = DIVIDEROUND (Dividend, Divisor);
                    }
                  } else { // Lpddr4
                    OdtValue = OdtWr;
                  }
                  break;

                case SCompCmd:
                  if (Ddr4) {
                    if (Is2DPC) {
                      Dividend = 55 * 55;
                      Divisor = 55 + 55;
                      OdtValue = DIVIDEROUND (Dividend, Divisor);
                    } else {
                      OdtValue = 55;
                    }
                  } else { // Lpddr4
                    OdtValue = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtCA, FALSE, 0, TRUE);
                  }
                  break;

                case SCompCtl:
                  if (Ddr4) {
                    if (Is2DPC) {
                      Dividend = 55 * 55;
                      Divisor = 55 + 55;
                      OdtValue = DIVIDEROUND (Dividend, Divisor);
                    } else {
                      OdtValue = 55;
                    }
                  } else { // Lpddr4
                    OdtValue = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtCA, FALSE, 0, TRUE);
                  }
                  break;

                case SCompClk:
                  if (Ddr4) {
                    if (Is2DPC) {
                      Dividend = 39 * 39;
                      Divisor = 39 + 39;
                      OdtValue = DIVIDEROUND (Dividend, Divisor);
                    } else {
                      OdtValue = 39;
                    }
                  } else { // Lpddr4
                    OdtValue = CalcDimmImpedance (MrcData, Channel, Rank, OptDimmOdtCA, FALSE, 0, TRUE);
                  }
                  break;

                default:
                  break;
              } // Switch ScompType
            } // RankExist
          } // For Rank
          Rtt = ((ScompParam[ScompIndex] == SCompClk) ? 0 : DimmSerialResistor) + OdtValue;
          Divisor = Rtt + CpuRon;
          if (Divisor == 0) {
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s - ODT, CPU Impedance and Dimm Resistor values are zero\n", gErrString, GlobalCompOffsetStr[ScompParam[ScompIndex]]);
            return mrcFail;
          }
          //VHigh = Vtt + ((Voh - Vtt) * Rtt / (CpuRon + Rtt));
          //VLow = Vtt * (CpuRon / (CpuRon + Rtt));
          VHigh = Vtt + (((Voh - Vtt) * Rtt) / (Divisor));
          VLow = (Vtt * CpuRon) / Divisor;
          VSwing += (VHigh - VLow);
        } // ChannelExist
      } // For Channel
      VSwing /= (ChannelsPopulated == 0) ? 1 : ChannelsPopulated;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", VSwing);

      // Derating value is 0.8, but because DesiredSlewRate is multiplied by 10 for precision, value of 8 is used here.
      DesiredBufferSegmentDelay[ScompIndex] = (VSwing * 8) / (DesiredSlewRate[ScompIndex] * SegmentsPerBuffer);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t", DesiredBufferSegmentDelay[ScompIndex]);
      if (DesiredBufferSegmentDelay[ScompIndex] == 0) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s BufferSegDelay value is zero\n", gErrString);
        return mrcFail;
      }
      DelayCells = DIVIDEROUND (Outputs->Qclkps, DesiredBufferSegmentDelay[ScompIndex]);
      if (DelayCells > (MaxChainLength + 1)) {
        // Calculated value is larger than maximum chain length.
        DelayCells = DIVIDEROUND (Outputs->Qclkps, 2 * DesiredBufferSegmentDelay[ScompIndex]);
        GetSetVal = 0; // Phase Lock
      } else {
        GetSetVal = 1; // Cycle Lock
      }

      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t\t", (GetSetVal == 0) ? "Phase" : "Cycle");
      MrcGetSetDdrIoGroupController0 (MrcData, SCompPC[ScompIndex], WriteCached, &GetSetVal);
      DelayCells = RANGE (DelayCells - 1, MinChainLength, MaxChainLength);
      GetSetVal = DelayCells;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\n", DelayCells);
      // Save Min Max lengh chain and BufferSegmentDelay for Cmd
      if (SCompCells[ScompIndex] == CmdSlewRate){
        IntOutputs->CmdSRData.BufferSegmentDelayCmd = (UINT8) DesiredBufferSegmentDelay[ScompIndex];
        IntOutputs->CmdSRData.MaxChainLengthCmd = (UINT8) MaxChainLength;
        IntOutputs->CmdSRData.MinChainLengthCmd = (UINT8) MinChainLength;
      }
    }
    MrcGetSetDdrIoGroupController0 (MrcData, SCompCells[ScompIndex], WriteCached, &GetSetVal);
  }
  ForceRcomp (MrcData);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Resulting Comp Code");
  for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
    MrcGetSetDdrIoGroupController0 (MrcData, SCompCode[ScompIndex], ReadUncached, &GetSetVal);
    SCompCodeResult = (UINT8) GetSetVal;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%s %d\t", GlobalCompOffsetStr[ScompParam[ScompIndex]], (INT8) GetSetVal);

    if ((SCompCodeResult == 0) || ((ScompForceByPassParam[ScompIndex]) && (BypassOverride))) {
      if ((ScompForceByPassParam[ScompIndex]) && BypassOverride) {
        ByPassString = "Force SlewRate bypass applied";
      } else {  //if (SCompCodeResult == 0)
        ByPassString = "SR Saturated";
      }
      MrcGetSetDdrIoGroupController0 (MrcData, SCompPC[ScompIndex], ReadFromCache, &GetSetVal);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s, SCompCodeResult %u, SCompPC %u\n", ByPassString, SCompCodeResult, (UINT8) GetSetVal);
      if (ScompParam[ScompIndex] == SCompDq) {
        GetSetVal = 1;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDqSlewDlyByPass, WriteCached, &GetSetVal);
      } else if (ScompParam[ScompIndex] == SCompCmd) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          Offset = OFFSET_CALC_CH (DDRCMDACH0_CR_DDRCRCMDCONTROLS_REG, DDRCMDACH1_CR_DDRCRCMDCONTROLS_REG, Channel);
          DdrCrCmdControls.Data = MrcReadCR (MrcData, Offset);
          DdrCrCmdControls.Bits.DdrCmdSlwDlyByp = 1;
          MrcWriteCR (MrcData, Offset, DdrCrCmdControls.Data);

          Offset = OFFSET_CALC_CH (DDRCMDBCH0_CR_DDRCRCMDCONTROLS_REG, DDRCMDBCH1_CR_DDRCRCMDCONTROLS_REG, Channel);
          DdrCrCmdControls.Data = MrcReadCR (MrcData, Offset);
          DdrCrCmdControls.Bits.DdrCmdSlwDlyByp = 1;
          MrcWriteCR (MrcData, Offset, DdrCrCmdControls.Data);
        }
      } else if (ScompParam[ScompIndex] == SCompCtl) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          Offset = OFFSET_CALC_CH (DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG, DDRCTLCH1_CR_DDRCRCTLRANKSUSED_REG, Channel);
          CtlRanksUsed.Data = MrcReadCR (MrcData, Offset);
          CtlRanksUsed.Bits.DdrCtlCkeSlwDlyByp = 1;
          MrcWriteCR (MrcData, Offset, CtlRanksUsed.Data);

          Offset = OFFSET_CALC_CH (DDRCKECH0_CR_DDRCRCKERANKSUSED_REG, DDRCKECH1_CR_DDRCRCKERANKSUSED_REG, Channel);
          CkeRanksUsed.Data = MrcReadCR (MrcData, Offset);
          CkeRanksUsed.Bits.DdrCkeCmdSlwDlyByp = 1;
          CkeRanksUsed.Bits.DdrCtlCkeSlwDlyByp = 1;
          MrcWriteCR (MrcData, Offset, CkeRanksUsed.Data);

          if (Inputs->CpuModel == cmICL_DT_HALO_R) {
            Offset = OFFSET_CALC_CH (DDRCTLCLKCKE0_CR_DDRCRCTLRANKSUSED_REG, DDRCTLCLKCKE1_CR_DDRCRCTLRANKSUSED_REG, Channel);
            CccCtlRanksUsed.Data = MrcReadCR (MrcData, Offset);
            CccCtlRanksUsed.Bits.DdrCtlCkeSlwDlyByp = 1;
            MrcWriteCR (MrcData, Offset, CccCtlRanksUsed.Data);

            Offset = OFFSET_CALC_CH (DDRCTLCLKCKE0_CR_DDRCRCCC4CKERANKSUSED_REG, DDRCTLCLKCKE1_CR_DDRCRCCC4CKERANKSUSED_REG, Channel);
            Ccc4CkeRanksUsed.Data = MrcReadCR (MrcData, Offset);
            Ccc4CkeRanksUsed.Bits.DdrCkeCmdSlwDlyByp = 1;
            MrcWriteCR (MrcData, Offset, Ccc4CkeRanksUsed.Data);
          }
        }
      } else if (ScompParam[ScompIndex] == SCompClk) {
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          Offset = OFFSET_CALC_CH (DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG, DDRCTLCH1_CR_DDRCRCTLRANKSUSED_REG, Channel);
          CtlRanksUsed.Data = MrcReadCR (MrcData, Offset);
          CtlRanksUsed.Bits.ClkSlewDlyByPass = 1;
          MrcWriteCR (MrcData, Offset, CtlRanksUsed.Data);

          if (Inputs->CpuModel == cmICL_DT_HALO_R) {
            Offset = OFFSET_CALC_CH (DDRCTLCLKCKE0_CR_DDRCRCTLRANKSUSED_REG, DDRCTLCLKCKE1_CR_DDRCRCTLRANKSUSED_REG, Channel);
            CccCtlRanksUsed.Data = MrcReadCR (MrcData, Offset);
            CccCtlRanksUsed.Bits.ClkSlewDlyByPass = 1;
            MrcWriteCR (MrcData, Offset, CccCtlRanksUsed.Data);
          }
        }
      }
      GetSetVal = 1;
      MrcGetSetDdrIoGroupController0 (MrcData, SCompPC[ScompIndex], WriteCached, &GetSetVal);
      ForceRcomp (MrcData);
      MrcGetSetDdrIoGroupController0 (MrcData, SCompCode[ScompIndex], ReadUncached, &GetSetVal);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "New comp code: %u", (UINT8) GetSetVal);
    }
  } // for ScompIndex
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  if (Lp4FreqSwitch) {
    MrcFrequencySwitch (MrcData, f1067, TRUE);
  }
  return mrcSuccess;
}

/**
  This function initializes all the necessary registers for basic training by
  Activating and initializing CPGC Engine
  Cleaning out MRs for programming

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcPreTraining (
  IN MrcParameters *const MrcData
  )
{
  const MrcInput    *Inputs;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcCpuModel       CpuModel;
  MrcDdrType        DdrType;
  INT64             TxEqualization;
  INT64             GetSetVal;
  UINT32            Offset;
  UINT8             Channel;
  UINT8             SubCh;
  UINT8             Rank;
  BOOLEAN           UltUlx;
  BOOLEAN           Ddr4;
  CH0_SC0_CR_CPGC_SEQ_CFG_A_STRUCT    CpgcSeqCfgA;
  CH0_SC0_CR_CPGC2_CREDIT_CFG_STRUCT  Cpgc20Credits;
  DDR4_MODE_REGISTER_2_STRUCT         Ddr4Mr2;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];
  DdrType       = Outputs->DdrType;
  CpuModel      = MrcData->Inputs.CpuModel;
  UltUlx        = (CpuModel == cmICL_ULX_ULT);
  Ddr4          = (DdrType == MRC_DDR_TYPE_DDR4);

  MrcSetNormalMode (MrcData, FALSE); // Go to CPGC mode

  // Assign subchannel to its serial number
  // Activate CPGC Engines on populated channels and subchannels.
  CpgcSeqCfgA.Data = 0;
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelOut = &ControllerOut->Channel[Channel];

    if (Ddr4) {
      // Setup Bank Logical to Physical mapping
      // This will allow B2B traffic if we use banks 0 and 1 in CPGC tests, which is good for most data tests.
      // Other tests, like CMD or TAT, can set up a different bank mapping.
      MrcGetSetBankSequence (
        MrcData,
        Channel,
        Ddr4x16BankMapB2B,
        MAX_DDR4_x16_BANKS,
        MRC_SET
        );
    }

    Offset = OFFSET_CALC_CH (CH0_SC0_CR_CPGC2_CREDIT_CFG_REG, CH1_SC0_CR_CPGC2_CREDIT_CFG_REG, Channel);
    Cpgc20Credits.Data = MrcReadCR (MrcData, Offset);
    Cpgc20Credits.Bits.CREDITS_CONFIG_DONE = 1;
    MrcWriteCR (MrcData, Offset, Cpgc20Credits.Data);

    for (SubCh = 0; SubCh < MAX_SUB_CHANNEL; SubCh++) {
      if (!MrcSubChannelExist (MrcData, Channel, SubCh)) {
        continue;
      }
      CpgcSeqCfgA.Bits.CHANNEL_ASSIGN      = (1 << SubCh);
      CpgcSeqCfgA.Bits.REQUEST_DATA_SIZE   = 1;
      CpgcSeqCfgA.Bits.INITIALIZATION_MODE = CPGC20_ACTIVE_MODE;
      if (DdrType == MRC_DDR_TYPE_LPDDR4) {
        // Use Global Bind to bind both subchannels together, so that they start/stop together.
        // We don't want to do this in DDR4, because then both 64-bit channels will always start/stop together,
        // and DDR4 can have asymmetrical population.
        CpgcSeqCfgA.Bits.GLOBAL_START_BIND     = 1;
        CpgcSeqCfgA.Bits.GLOBAL_STOP_BIND      = 1;
        CpgcSeqCfgA.Bits.GLOBAL_CLEAR_ERR_BIND = 1;
      }
      Offset = MrcGetCpgcSeqCfgOffset (MrcData, Channel, SubCh);
      MrcWriteCR (MrcData, Offset, CpgcSeqCfgA.Data);
      if (Ddr4) {
        // Only program the SubCh0 for DDR4
        break;
      }
    }

    if (Ddr4 && (Inputs->BootMode != bmWarm)) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
        if (!(MrcRankInChannelExist (MrcData, Rank, Channel))) {
          continue;
        }
        // Check RttWr if not 0 (not off)
        Ddr4Mr2.Data = ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[Rank % 2].MR[mrMR2];
        if (Ddr4Mr2.Bits.DynamicOdt != 0) {
          TxEqualization  = 0x3F;
          GetSetVal       = UltUlx ? 0 : 1;
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, MAX_SDRAM_IN_DIMM, TxEq, WriteCached, &TxEqualization);
          MrcGetSetDdrIoGroupStrobe (MrcData, Channel, Rank, MAX_SDRAM_IN_DIMM, GsmIocConstZTxEqEn, WriteCached, &GetSetVal);
        }
      } // for Rank
    } // if DDR4
  } // for Channel

  return mrcSuccess;
}

/**
  This function initializes all the necessary registers after main training steps but before LCT.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess

**/
MrcStatus
MrcPostTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  UINT8             Channel;

  Outputs       = &MrcData->Outputs;
  ControllerOut = &Outputs->Controller[0];

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      // Update CmdN timing, Round Trip Latency and tXP
      // OldN = 3N (Gear1) or 2N (Gear2), NewN = 1N or 2N
      UpdateCmdNTiming (
        MrcData,
        Channel,
        Outputs->Gear2 ? (2 * 1) : (2 * 2),
        (ControllerOut->Channel[Channel].Timing[MrcData->Inputs.MemoryProfile].NMode == 2) ? 2 : 0
      );
    }
  }

  return mrcSuccess;
}

/**
  Program PCU_CR_DDR_VOLTAGE register.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] VddVoltage - Current DDR voltage.

**/
void
MrcSetPcuDdrVoltage (
  IN OUT MrcParameters *MrcData,
  IN     MrcVddSelect  VddVoltage
  )
{
  MrcOutput                     *Outputs;
  MrcDebug                      *Debug;
  UINT8                         Data8;
  DDR_VOLTAGE_PCU_STRUCT        DdrVoltage;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  switch (VddVoltage) {
    case VDD_1_35:
      Data8 = 1;
      break;

    case VDD_1_20:
      Data8 = 3;
      if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
        Data8 = 7;
      }
      break;

    case VDD_1_10:
      Data8 = 6;
      break;

    default:
      Data8 = 0;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PCU_CR_DDR_VOLTAGE = 0x%02X\n", Data8);
  DdrVoltage.Data = 0;
  DdrVoltage.Bits.DDR_VOLTAGE = Data8;
  MrcWriteCR (MrcData, DDR_VOLTAGE_PCU_REG, DdrVoltage.Data);
}

/**
  This function sets up the Vtt termination.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] DebugMsg - Whether to display debug messages

**/
void
MrcSetupVtt (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              DebugMsg
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MrcVddSelect      Vdd;
  INT64             GetSetVal;
  UINT32            Itarget;
  UINT32            Idelta;
  UINT32            Vpanic2;
  UINT32            Vpanic1;
  UINT32            Iload;
  UINT32            IcompUp;
  UINT32            IcompDn;
  UINT32            RonDimm;
  UINT32            TotalRon;
  UINT32            NumberOfSegments;
  UINT32            CmdTarget;
  UINT32            Vtt;
  UINT32            NumOfLoader;
  UINT32            GsmMode;
  UINT32            CmdPanicDrvUpTarget;
  UINT16            RodtCpu;
  UINT8             Rank;
  UINT8             TotalDimms;
  UINT8             Channel;
  UINT8             Gear2;
  MrcDebugMsgLevel  DebugLevel;
  DDRPHY_COMP_CR_DDRCRCOMPCTL3_STRUCT CompCtl3;
#ifdef MRC_DEBUG_PRINT
  DDRDATA0CH0_CR_RCOMPDATA2_STRUCT    DdrCrDataComp2;
#endif //MRC_DEBUG_PRINT

  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  CmdPanicDrvUpTarget = 180; // Ohms
  TotalRon            = 0;
  TotalDimms          = 0;
  Vdd                 = Outputs->VddVoltage[Inputs->MemoryProfile];
  Gear2               = Outputs->Gear2 ? 1 : 0;

  DebugLevel = (DebugMsg) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
  GsmMode    = (DebugMsg) ? GSM_PRINT_VAL : 0;

  // Target Vtt Voltage
  Vtt = Vdd / 2;
  // Calculate RodtCPU
  // @todo: in power training this might vary between different bytes so need to avg
  RodtCpu = CalcCpuImpedance (MrcData, 0, 0, 0, OptRdOdt, FALSE, 0, FALSE,  0, 0);
  // Calculate RonDimm Per Dimm (assuming)
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (MrcChannelExist (Outputs, Channel)) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += 2) {
        if (!MrcRankInChannelExist (MrcData, Rank, Channel)) {
          continue;
        }
        TotalDimms++;
        TotalRon += CalcDimmImpedance(MrcData, Channel, Rank, OptDimmRon, TRUE, INIT_DIMM_RON_34, FALSE);
      } // Rank exist
    } // Channel exist
  } // Channel

  if (TotalDimms == 0) {
    TotalDimms++;
  }
  RonDimm = TotalRon / TotalDimms;

  // Delta Current.  pF * mV / pS -> mA
  // iload = vdd/(2*(rodt+ron))*64
  Vpanic1 = VPANIC1 / 1000; // Scale to mV
  Vpanic2 = VPANIC2 / 1000; // Scale to mV
  if ((RodtCpu == 0) && (RonDimm == 0)) {
    RonDimm++;
  }
  // For ULX/ULT VTT is divided per every 4 bytes.
  // DT/HALO stays at ever 8 bytes.
  NumOfLoader = (Inputs->CpuModel == cmICL_ULX_ULT) ? 32 : 64;
  Iload = Vdd * NumOfLoader * 1000 / (2 * (RodtCpu + RonDimm));  // uA
  Idelta = ((CDIEVTT * (Vpanic2 - Vpanic1)) / (Outputs->UIps / 2)) * 1000; // uA
  Idelta /= (Gear2 + 1); // clk is half
  Itarget = (Iload + Idelta) / (NumOfLoader); //uA

  MRC_DEBUG_MSG (Debug, DebugLevel, "MrcSetupVtt: RodtCpu=%u ohm, RonDimm=%u ohm\n", RodtCpu, RonDimm);
  MRC_DEBUG_MSG (Debug, DebugLevel, "Itarget=%u uA, Iload=%u uA, Idelta=%u uA\n", Itarget, Iload, Idelta);

  // Configure VTT Panic Comp Command Ron Vref
  // The number of segments for CmdDrv is 3 in CNL
  NumberOfSegments = 3;
  CmdTarget = NumberOfSegments * Inputs->RcompTarget[WrDSCmd];

  // Compensated to this current
  IcompDn = 1000 * (Inputs->VccIomV - Vtt) / CmdTarget; // uA
  IcompUp = 1000 * Vtt / CmdPanicDrvUpTarget; // uA
  if (IcompDn == 0) {
    IcompDn++;
  }
  if (IcompUp == 0) {
    IcompUp++;
  }
  // CmdPanicDrvUpTarget and CmdTarget are no longer used after this.  So we will use this variable to pre-calculate before doing the Divide Round Macro
  CmdTarget += CmdPanicDrvUpTarget;
  CmdPanicDrvUpTarget *= 191;
  CompCtl3.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL3_REG);
  CompCtl3.Bits.CmdDrvVrefForVttPanicComp = DIVIDEROUND (CmdPanicDrvUpTarget, CmdTarget);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL3_REG, CompCtl3.Data);

  MRC_DEBUG_MSG (Debug, DebugLevel, "IcompDn=%u uA, IcompUp=%u uA\n", IcompDn, IcompUp);
  // Calculate multiplier to get target current
  GetSetVal = 2 * (Itarget / IcompUp);
  GetSetVal = MIN (GetSetVal, DDRPHY_COMP_CR_DDRCRCOMPCTL2_VttPanicCompUpMult_MAX); // Avoid clamp warning from GetSet
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocVttPanicCompUpMult, WriteCached | GsmMode, &GetSetVal);

  GetSetVal = 2 * (Itarget / IcompDn);
  GetSetVal = MIN (GetSetVal, DDRPHY_COMP_CR_DDRCRCOMPCTL2_VttPanicCompDnMult_MAX); // Avoid clamp warning from GetSet
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocVttPanicCompDnMult, WriteCached | GsmMode, &GetSetVal);

  ForceRcomp (MrcData);

#ifdef MRC_DEBUG_PRINT
  DdrCrDataComp2.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP2_REG);
  MRC_DEBUG_MSG (Debug, DebugLevel, "final panicvttup = 0x%X\n", DdrCrDataComp2.Bits.PanicVttUp);
  MRC_DEBUG_MSG (Debug, DebugLevel, "final panicvttdn = 0x%X\n", DdrCrDataComp2.Bits.PanicVttDn);
#endif //MRC_DEBUG_PRINT
}

/**
  This function Enables ODT signals for the specific DDR Type based on CPU layout.

  @param[in]  MrcData - MRC global data.
  @param[in]  Channel - Channel to configure.
  @param[in]  RanksToEnable  - Rank Mask for which ODT signals to enable.
**/
void
MrcSetOdtSignals (
  IN  MrcParameters *MrcData,
  IN  UINT32        Channel,
  IN  UINT8         RanksToEnable
  )
{
  MrcDebug    *Debug;
  MrcOutput   *Outputs;
  MrcDdrType  DdrType;
  UINT32      Offset;
  CLK_CKE_CTL_EN_TYPE ClkCkeCtlEn;
  DDRCTLCH0_CR_DDRCRCTLRANKSUSED_STRUCT CtlRanksUsed;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  DdrType       = Outputs->DdrType;

  Offset = DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG +
    ((DDRCTLCH1_CR_DDRCRCTLRANKSUSED_REG - DDRCTLCH0_CR_DDRCRCTLRANKSUSED_REG) * Channel);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Channel %u ODT Ranks Enabled = 0x%X\n", Channel, RanksToEnable);
  CtlRanksUsed.Data = MrcReadCR (MrcData, Offset);
  ClkCkeCtlEn.Data8 = (UINT8) CtlRanksUsed.Bits.CtlCkTxEn;
  if (DdrType == MRC_DDR_TYPE_DDR4) {
    ClkCkeCtlEn.Ctl.Ddr4.Odt01 = RanksToEnable & 0x3;
    CtlRanksUsed.Bits.CtlCkTxEn = ClkCkeCtlEn.Data8;
  } else if (DdrType != MRC_DDR_TYPE_LPDDR4) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Non-Supported DDR Type: %s\n", gDdrTypeStr[DdrType]);
  }

  // No case for LPDDR4 as it has no ODT pins.
  MrcWriteCR (MrcData, Offset, CtlRanksUsed.Data);
}

/**
  This function configures the DDR IO ODT type to Data and Comp blocks.
  VSS and VTT blocks are one time configured in MrcDdrIoInit.
  This updates OdtMode in MrcOutput.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  NewMode - ODT mode to enable.

  @retval MrcStatus - mrcSuccess if a valid ODT mode is requested, otherwise mrcWrongInputParameter.
**/
MrcStatus
MrcSetIoOdtMode (
  IN  MrcParameters *const  MrcData,
  IN  MRC_ODT_MODE_TYPE     NewMode
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  MRC_ODT_MODE_TYPE CurrentMode;
  INT64             VttMode;
  INT64             VddqMode;
  INT64             VssMode;
  INT32             RxVrefValue;
  INT64             GetSetValue;
  INT32             RxVrefMinValue;
  INT32             RxVrefMaxValue;
  INT64             GetRxVrefMin;
  INT64             GetRxVrefMax;
  INT64             PanicDrvUp;
  INT32             OdtTarget;
  UINT32            Channel;
  UINT32            Byte;
  UINT32            EffPullUp;
  UINT32            Voh;
  UINT32            PuDeltaV;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr4;
  BOOLEAN           Lpddr4Vss;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  CurrentMode = Outputs->OdtMode;
  OdtTarget   = -1;
  Ddr4        = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4      = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr4Vss   = (Lpddr4 && (NewMode == MrcOdtModeVss));
  GetSetValue = 0;

  if ((NewMode >= MrcOdtModeMax) || (NewMode == MrcOdtModeDefault)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Invalid ODT Mode requested: %d\n", NewMode);
    return mrcWrongInputParameter;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "New ODT Mode: %s\t Original ODT Mode: %s\n", gIoOdtModeStr[NewMode], gIoOdtModeStr[CurrentMode]);
  MrcGetSetLimits (MrcData, RxVref, &GetRxVrefMin, &GetRxVrefMax, NULL);
  RxVrefMinValue = (INT32) GetRxVrefMin;
  RxVrefMaxValue = (INT32) GetRxVrefMax;
  // Same register is modified in IoInit outside of HAL, need to ensure it hasn't changed
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompVttOdtEn, ReadCached, &VttMode);

  // CTT mode is the default if no other mode is enabled.  Thus we clear all other modes.
  VttMode   = (NewMode == MrcOdtModeVtt)  ? 1 : 0;
  VddqMode  = (NewMode == MrcOdtModeVddq) ? 1 : 0;
  if (NewMode == MrcOdtModeVss) {
    VssMode = 1;
    RxVrefValue = (RxVrefMaxValue + (3 * RxVrefMinValue)) / 4;  // VSS termination: RxVref = 0.25 * Vddq
  } else {
    VssMode = 0;
    RxVrefValue = (RxVrefMinValue + RxVrefMaxValue) / 2;  // Middle of the range for CTT/VTT termination
    if (Inputs->LowSupplyEnData && Lpddr4) {
      RxVrefValue *= Inputs->VccIomV;
      RxVrefValue /= VDD_1_10;
    }
  }

  // Disable VTT first, before enabling VDDQ.
  // VssOdt and VddqOdt reside in separate registers so need to enforce the order.
  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      GetSetValue = 0;
      if (NewMode == MrcOdtModeVddq) {
        if (CurrentMode == MrcOdtModeVtt) {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDataVttOdtEn, WriteCached, &GetSetValue);
        }
        if (CurrentMode == MrcOdtModeVss) {
          MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocVssOdtEn,     WriteCached, &GetSetValue);
        }
      }
      if ((CurrentMode == MrcOdtModeVddq) && (NewMode == MrcOdtModeVss)) {
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDataVddqOdtEn, WriteCached, &GetSetValue);
      }
    } // Byte
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDataVddqOdtEn,  WriteToCache, &VddqMode);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocDataVttOdtEn,   WriteToCache, &VttMode);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocRxVrefMFC,      WriteToCache, &VttMode);
      MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, GsmIocVssOdtEn,       WriteToCache, &VssMode);

      // Update RxVref to match the new termination type
      // DDR4 will be updated below using MrcSetDefaultRxVrefDdr4
      // LPDDR4 VSS termination will be updated below.
      if (!(Ddr4 || Lpddr4Vss)) {
        GetSetValue = RxVrefValue;
        MrcGetSetDdrIoGroupChannelStrobe (MrcData, Channel, Byte, RxVref, WriteToCache | PrintValue, &GetSetValue);
      }
    } // Byte
  } // Channel
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompVddqOdtEn, WriteToCache, &VddqMode);
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocCompVttOdtEn,  WriteToCache, &VttMode);
  PanicDrvUp = 76;
  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocPanicDrvUpVref, WriteToCache, &PanicDrvUp);

  MrcFlushRegisterCachedData (MrcData);

  // The input RcompTarget[RdOdt] is for the initial ODT mode.  When we change from
  // VTT Mode to CTT mode, we must adjust the Rcomp.  When we return from CTT Mode
  // to VTT mode, we will restore the input Rcomp.
  if ((CurrentMode == MrcOdtModeVtt) && (NewMode == MrcOdtModeCtt)) {
    // VTT used 1 segment so we need to double the RdOdt Rcomp
    OdtTarget = Inputs->RcompTarget[RdOdt] * 2;
  } else if ((CurrentMode == MrcOdtModeCtt) && (NewMode == MrcOdtModeVtt)) {
    OdtTarget = Inputs->RcompTarget[RdOdt];
  }

  Outputs->OdtMode = NewMode;

  // OdtTarget has to be a positive value.  We use -1 to determine if we need to
  // update the ODT to avoid embedding two function calls in the previous if-statement.
  if (OdtTarget > -1) {
    // We use an INT32 here so  that -1 doesn't alias to a possible valid value from the
    // the input parameter which is a UINT16.  So its safe to force the typecast here.
    UpdateCompTargetValue (MrcData, RdOdt, (UINT16) OdtTarget, TRUE);
  }

  if (Ddr4) {
    MrcSetDefaultRxVrefDdr4 (MrcData, TRUE, TRUE); // Update DDR4 RxVref, uses Outputs->OdtMode
  } else if (Lpddr4Vss) {
    Voh = (Outputs->Lp4x) ? 360 : 440;  // mV
    PuDeltaV = ((Outputs->Lp4x) ? VDD_0_60 : VDD_1_10) - Voh;
    EffPullUp = PuDeltaV * Inputs->RcompTarget[RdOdt];
    EffPullUp = DIVIDEROUND (EffPullUp, Voh);
    MrcSetIdealRxVref (MrcData, MAX_CHANNEL, EffPullUp, 80, Inputs->RcompTarget[RdOdt], TRUE);
  }

  return mrcSuccess;
}

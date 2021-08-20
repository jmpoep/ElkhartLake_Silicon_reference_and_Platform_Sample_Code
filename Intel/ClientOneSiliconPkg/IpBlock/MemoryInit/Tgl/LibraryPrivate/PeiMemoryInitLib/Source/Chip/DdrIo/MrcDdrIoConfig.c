/** @file
  This file contains code related to initializing and configuring the DDRIO.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include "MrcInterface.h"
#include "MrcHalRegisterAccess.h"
#include "MrcCommon.h" // Needed for OFFSET_CALC_CH
#include "MrcDdrIoApi.h"
#include "MrcDdrIoApiInt.h"
#include "MrcReset.h"
#include "MrcDdrIoOffsets.h"
#include "Cpgc20TestCtl.h"

/// Defines
#define VoltageSelect_VccDDQ   (0)
#define VoltageSelect_Vccdd2   (1)
#define MaxVoltageSelect       (2)
#define DDRIO_MAX_VTT_GEN      (4)
#define VCC_DLL_BYTES          (2)
#define VCCDLL1                (1)
#define VCCDLL2                (2)
#define VSXHI                  (3)
#define MAX_VSXHI_CODES        (5)
#define MAX_OFFSET_VOLTAGE    (2)
#define MAX_FF_RCVEN_PI       (5)
#define MAX_FF_RCVEN_PRE      (5)
#define MAX_VCCDLL_CODES      (7)
#define MAX_FF_WRITESTAGGER   (2)
#define MRC_NUMBURSTS_FFTIMING (32)
#define MAX_VCCDLL_DATA_PAR   (8)
#define MAX_VCCDLL_PAR        (12)
#define MAX_KICKBACK_CODES     (5)
#define NDEFAULT               (33)
#define MAX_VCCDLL_DATA_PAR    (8)
#define COMPVTARGET_SWINGV     (260)
#define COMPVTARGET_STEPV      (26)
///

/// Constants
const INT8 RxFifoChDelay[MRC_DDR_TYPE_UNKNOWN][MAX_GEARS][MAX_SYS_CHANNEL] = {
// Gear1                              Gear2
// Channel
//   0,  1,  2,  3,  4,  5,  6,  7     0,  1,  2,  3,  4,  5,  6,  7
  {{ 5,  3,  0,  0,  0,  0,  0,  0}, { 9,  7,  0,  0,  0,  0,  0,  0}}, // DDR4
  {{ 5,  5,  3,  3,  0,  0,  0,  0}, { 9,  9,  7,  7,  0,  0,  0,  0}}, // DDR5
  {{ 7,  7,  7,  7,  5,  5,  5,  5}, {11, 11, 11, 11,  9,  9,  9,  9}}, // LPDDR5
  {{ 5,  5,  5,  5,  3,  3,  3,  3}, { 9,  9,  9,  9,  7,  7,  7,  7}}  // LPDDR4
};

/// Enums
typedef enum {
  DllDdrData0,
  DllDdrData1,
  DllDdrData2,
  DllDdrData3,
  DllDdrData4,
  DllDdrData5,
  DllDdrData6,
  DllDdrData7,
  DllDdrCcc0,
  DllDdrCcc1,
  DllDdrCcc2,
  DllDdrCcc3,
  DllDdrMax
} DLL_PARTITIONS;

typedef enum {
  CaVssHi,
  CtlVssHi,
  ClkVssHi,
  MaxCccVssHi
} CCC_VSSHI;

/// Structs
typedef struct {
  UINT8 Channel;
  UINT8 Byte;
} PHY_PARTITION_BLOCK;

const PHY_PARTITION_BLOCK LpddrDdr4ILDllPartitions[DllDdrMax][VCC_DLL_BYTES] = {

  //   Physical Channel, Phy Byte
    {{ 0, 0}, { 1, 0}}, //DllDdrData0
    {{ 0, 1}, { 1, 1}}, //DllDdrData1
    {{ 0, 2}, { 1, 2}}, //DllDdrData2
    {{ 0, 3}, { 1, 3}}, //DllDdrData3
    {{ 0, 4}, { 1, 4}}, //DllDdrData4
    {{ 0, 5}, { 1, 5}}, //DllDdrData5
    {{ 0, 6}, { 1, 6}}, //DllDdrData6
    {{ 0, 7}, { 1, 7}}, //DllDdrData7
    {{ 0, 0}, { 1, 0}}, //DllDdrCcc0
    {{ 2, 0}, { 3, 0}}, //DllDdrCcc1
    {{ 4, 0}, { 5, 0}}, //DllDdrCcc2
    {{ 6, 0}, { 7, 0}}, //DllDdrCcc3
};

const PHY_PARTITION_BLOCK Ddr4NILDllPartitions[DllDdrMax][VCC_DLL_BYTES] = {
  //   Physical Channel, Phy Byte
    {{ 0, 0}, { 0, 2}}, //DllDdrData0
    {{ 0, 1}, { 0, 3}}, //DllDdrData1
    {{ 0, 4}, { 0, 6}}, //DllDdrData2
    {{ 0, 5}, { 0, 7}}, //DllDdrData3
    {{ 1, 0}, { 1, 2}}, //DllDdrData4
    {{ 1, 1}, { 1, 3}}, //DllDdrData5
    {{ 1, 4}, { 1, 6}}, //DllDdrData6
    {{ 1, 5}, { 1, 7}}, //DllDdrData7
    {{ 0, 0}, { 1, 0}}, //DllDdrCcc0
    {{ 2, 0}, { 3, 0}}, //DllDdrCcc1
    {{ 4, 0}, { 5, 0}}, //DllDdrCcc2
    {{ 6, 0}, { 7, 0}}, //DllDdrCcc3
};



/**
  This function updates the Gear specific fields in the DDRIO

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Gear2   - TRUE for Gear2, FALSE for Gear1
**/
VOID
DdrIoConfigGear2 (
  IN  MrcParameters *MrcData,
  IN  BOOLEAN       Gear2
  )
{
  const MrcInput *Inputs;
  INT64          GetSetVal;
  UINT32         Index;
  UINT32         Offset;
  UINT32         Data;
  UINT32         DdrIoGear1;
  UINT8          Pi0DivEn;
  UINT8          Pi0Inc;
  UINT8          Pi123DivEn;
  UINT8          Pi123Inc;
  UINT8          Pi4DivEn;
  UINT8          Pi4Inc;
  UINT8          PiSyncDiv;
  CH0CCC_CR_DDRCRPINSUSED_STRUCT      CccPinsUsed;
  CH0CCC_CR_DDRCRPINSUSED_P0_STRUCT   CccPinsUsedP0;
  CH0CCC_CR_DDRCRCCCPIDIVIDER_STRUCT  CccPiDivider;

  Inputs = &MrcData->Inputs;
  DdrIoGear1 = Gear2 ? 0 : 1; // DDRIO Register encoding: 1 = Gear1, 0 = Gear2

  GetSetVal = DdrIoGear1;
  MrcGetSetNoScope (MrcData, GsmIocScramGear1, WriteCached, &GetSetVal);

  MrcGetSetStrobe (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MRC_IGNORE_ARG, MAX_SDRAM_IN_DIMM, GsmIocDataCtlGear1, WriteCached, &GetSetVal);

  // Update CMD/CLK/CTL PI Dividers
  if (MrcData->Outputs.DdrType == MRC_DDR_TYPE_LPDDR5) {
    Pi123DivEn = 1;
    // for WCK pi4, set en to 0 and Div to 3
    Pi0DivEn = 1;
    if (Gear2) {
      PiSyncDiv = 2;
      Pi0Inc = 2;
      Pi123Inc = 1;
      Pi4Inc = 3;
      Pi4DivEn = 0;
    } else {
      PiSyncDiv = 3;
      Pi0Inc = 1;
      Pi123Inc = 0;
      Pi4Inc = 2;
      Pi4DivEn = 1;
    }
  } else {
    if (Gear2) {
      PiSyncDiv = 0;
      Pi0DivEn = 0;
      Pi0Inc = 0;
      Pi123DivEn = 0;
      Pi123Inc = 0;
      Pi4Inc = 0;
      Pi4DivEn = 0;
    } else {
      PiSyncDiv = 0;
      Pi0DivEn = 1;
      Pi0Inc = 2;
      Pi123DivEn = 1;
      Pi123Inc = 2;
      Pi4Inc = 2;
      Pi4DivEn = 1;
    }
  }

  CccPiDivider.Data = 0;
  CccPiDivider.Bits.PiClkDuration = CH0CCC_CR_DDRCRCCCPIDIVIDER_PiClkDuration_MAX; // @todo - Set final value in MrcMcActivate.
  CccPiDivider.Bits.PiSyncDivider = PiSyncDiv;
  CccPiDivider.Bits.WckHalfPreamble = 1; // 4:1 mode
  CccPiDivider.Bits.Pi4IncPreamble = (Gear2) ? 2 : 1;
  CccPiDivider.Bits.Pi4DivEnPreamble = 1;
  // Cmd
  CccPiDivider.Bits.Pi0DivEn  = Pi0DivEn;
  CccPiDivider.Bits.Pi0Inc    = Pi0Inc;
  // Ctl
  CccPiDivider.Bits.Pi1DivEn  = Pi123DivEn;
  CccPiDivider.Bits.Pi1Inc    = Pi123Inc;
  // Ctl (Lp, Ddr4 Ccc1) / Cke (Ddr4 Ccc2)
  CccPiDivider.Bits.Pi2DivEn  = Pi123DivEn;
  CccPiDivider.Bits.Pi2Inc    = Pi123Inc;
  // Clk
  CccPiDivider.Bits.Pi3DivEn  = Pi123DivEn;
  CccPiDivider.Bits.Pi3Inc    = Pi123Inc;
  // Cke (Lp4) / Wck (Lp5)
  CccPiDivider.Bits.Pi4DivEn  = Pi4DivEn;
  CccPiDivider.Bits.Pi4Inc    = Pi4Inc;
  MrcWriteCR (MrcData, CCC_CR_DDRCRCCCPIDIVIDER_REG, CccPiDivider.Data);

  for (Index = 0; Index < MRC_NUM_CCC_INSTANCES; Index++) {
    Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRPINSUSED_REG, CH1CCC_CR_DDRCRPINSUSED_REG, Index);
    Data = MrcReadCR (MrcData, Offset);
    if (Inputs->UlxUlt) {
      CccPinsUsed.Data = Data;
      CccPinsUsed.Bits.Gear1 = DdrIoGear1;
      Data = CccPinsUsed.Data;
    } else {
      CccPinsUsedP0.Data = Data;
      CccPinsUsedP0.P0Bits.Gear1 = DdrIoGear1;
      Data = CccPinsUsedP0.Data;
    }
    MrcWriteCR (MrcData, Offset, Data);
  }
}

/**
  This function records the result of VssHi Comp Calibration as well as setup for the next iteration

  @param[in, out] MrcData  - Include all MRC global data.
  @param[out] CCCVssHi2    - Array for storing CCC Vdd2
  @param[out] CCCVssHiQ    - Array for storing CCC Vddq
  @param[out] DQVssHiQ     - Array for storing DQ
  @param[in] CCCBlock      - Array for which CCCBlock is for VDDQ and which is for Vdd2
  @param[in] FirstCCCBlock - First populated Channel to read from for CCC Block
  @param[in] Index         - Index of array
  @param[in] RCompCodes    - Array of CompCodes to write for next iteration

**/
VOID
MrcVssHiCompCalSetup (
  IN OUT MrcParameters *const MrcData,
  OUT UINT8      CCCVssHi2[MRC_NUM_OF_VSSHI_COMPS],
  OUT UINT8      CCCVssHiQ[MRC_NUM_OF_VSSHI_COMPS],
  OUT UINT8      DQVssHiQ[MRC_NUM_OF_VSSHI_COMPS],
  IN  CCC_VSSHI  CCCBlock[MaxVoltageSelect],
  IN  UINT32     FirstCCCBlock,
  IN  UINT32     Index,
  IN  UINT8      RCompCodes[MRC_NUM_OF_VSSHI_COMPS]
  )
{
  UINT8   LoopIndex;
  UINT32  CccOffset;
  UINT32  CccBroadcastOffset;
  UINT32  Offset;
  DDRPHY_COMP_CR_DDRCRCACOMP_STRUCT  CccPhyComp;
  CCC_CR_DDRCRCACOMP_STRUCT  CccComp;
  DDRPHY_COMP_CR_DDRCRDATACOMP0_STRUCT  DataComp0;

  for (LoopIndex = 0; LoopIndex < MaxVoltageSelect; LoopIndex++) {
    switch (CCCBlock[LoopIndex]) {
      case CaVssHi:
        Offset = DDRPHY_COMP_CR_DDRCRCACOMP_REG;
        CccOffset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCACOMP_REG, CH1CCC_CR_DDRCRCACOMP_REG, FirstCCCBlock);
        CccBroadcastOffset = CCC_CR_DDRCRCACOMP_REG;
        break;

      case CtlVssHi:
        Offset = DDRPHY_COMP_CR_DDRCRCTLCOMP_REG;
        CccOffset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCTLCOMP_REG, CH1CCC_CR_DDRCRCTLCOMP_REG, FirstCCCBlock);
        CccBroadcastOffset = CCC_CR_DDRCRCTLCOMP_REG;
        break;

      case ClkVssHi:
        Offset = DDRPHY_COMP_CR_DDRCRCLKCOMP_REG;
        CccOffset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCLKCOMP_REG, CH1CCC_CR_DDRCRCLKCOMP_REG, FirstCCCBlock);
        CccBroadcastOffset = CCC_CR_DDRCRCLKCOMP_REG;
        break;

      default:
        Offset = CccOffset = CccBroadcastOffset = MRC_IGNORE_ARG;
        break;
    }
    if (Offset == MRC_IGNORE_ARG) {
      continue;
    }
    CccPhyComp.Data = MrcReadCR (MrcData, Offset);
    if (LoopIndex == VoltageSelect_VccDDQ) {
      CCCVssHiQ[Index] = (UINT8) CccPhyComp.Bits.VssHiFF;
    } else {
      CCCVssHi2[Index] = (UINT8) CccPhyComp.Bits.VssHiFF;
    }
    if (Index < (MRC_NUM_OF_VSSHI_COMPS - 1)) {
      //Setup for the next iteration except last one
      CccPhyComp.Bits.RcompDrvUp = RCompCodes[Index + 1];
      MrcWriteCR (MrcData, Offset, CccPhyComp.Data);
      CccComp.Data = MrcReadCR (MrcData, CccOffset);
      CccComp.Bits.RcompDrvUp = RCompCodes[Index + 1];
      MrcWriteCrMulticast (MrcData, CccBroadcastOffset, CccComp.Data);
    }
  }

  Offset = DDRPHY_COMP_CR_DDRCRDATACOMP0_REG;
  DataComp0.Data = MrcReadCR (MrcData, Offset);
  DQVssHiQ[Index] = (UINT8) DataComp0.Bits.VssHiFF;
  if (Index < (MRC_NUM_OF_VSSHI_COMPS - 1)) {
    //Setup for the next iteration except last one
    DataComp0.Bits.RcompDrvUp = RCompCodes[Index + 1];
    MrcWriteCR (MrcData, Offset, DataComp0.Data);
  }
}

/**
  This function calculates the VssHi Coefficients

  @param[in, out] MrcData - Include all MRC global data.
  @param[in, out] VssHi   - Array for of VssHiFF results
  @param[out] FFRefBit5   - Result for FFRefBit5
  @param[out] FFRefBit4   - Result for FFRefBit4
  @param[out] FFRefBit3   - Result for FFRefBit3
  @param[out] FFRefBit2   - Result for FFRefBit2
  @param[out] FFRefLSB    - Result for FFRefLSB
  @param[out] FFRefStatic - Result for FFRefStatic

**/
VOID
MrcVssHiCoeffCalc (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT8                VssHi[MRC_NUM_OF_VSSHI_COMPS],
  OUT UINT8                   *FFRefBit5,
  OUT UINT8                   *FFRefBit4,
  OUT UINT8                   *FFRefBit3,
  OUT UINT8                   *FFRefBit2,
  OUT UINT8                   *FFRefLSB,
  OUT UINT8                   *FFRefStatic
  )
{
  INT32  Data32;
  INT32  SubtractionValue;
  INT32  Bit5Value;
  INT32  Bit4Value;
  INT32  Bit3Value;
  INT32  Bit2Value;
  INT32  LSBValue;
  INT32  StaticValue;

  Data32 = VssHi[0] + VssHi[1] + VssHi[2];
  Data32 /= 3;
  VssHi[2] = (UINT8) Data32;
  StaticValue = VssHi[2];
  if (FFRefStatic != NULL) {
    *FFRefStatic = (UINT8) (RANGE (StaticValue, 0, 15));
  }

  Data32 = VssHi[13] + VssHi[12];
  SubtractionValue = VssHi[11] + VssHi[2];
  Bit5Value = Data32 - SubtractionValue;
  Bit5Value /= 2;
  if (FFRefBit5 != NULL) {
    *FFRefBit5 = (UINT8) (RANGE (Bit5Value, 0, 15));
  }

  Data32 = VssHi[11] + VssHi[10];
  SubtractionValue = VssHi[9] + VssHi[2];
  Bit4Value = Data32 - SubtractionValue;
  Bit4Value /= 2;
  if (FFRefBit4 != NULL) {
    *FFRefBit4 = (UINT8) (RANGE (Bit4Value, 0, 7));
  }

  Data32 = VssHi[9] + VssHi[8];
  SubtractionValue = VssHi[7] + VssHi[2];
  Bit3Value = Data32 - SubtractionValue;
  Bit3Value /= 2;
  if (FFRefBit3 != NULL) {
    *FFRefBit3 = (UINT8) (RANGE (Bit3Value, 0, 7));
  }

  Data32 = VssHi[7] + VssHi[6];
  SubtractionValue = VssHi[5] + VssHi[2];
  Bit2Value = Data32 - SubtractionValue;
  Bit2Value /= 2;
  if (FFRefBit2 != NULL) {
    *FFRefBit2 = (UINT8) (RANGE (Bit2Value, 0, 7));
  }

  Data32 = (2 * VssHi[5]) + (2 * VssHi[4]) + VssHi[3];
  SubtractionValue =  VssHi[4] + (2 * VssHi[3]) + (2 * VssHi[2]);
  LSBValue = Data32 - SubtractionValue;
  LSBValue /= 5;
  if (FFRefLSB != NULL) {
    *FFRefLSB = (UINT8) (RANGE (LSBValue, 0, 7));
  }

  return;
}

/**
  This function programs the Drift Limits (Global and Local) based on TargetNUI

  @param[in, out] MrcData            - Include all MRC global data.
  @param[in, out] OrigVccDllDqsDelay - Register value of DDRPHY_COMP_CR_VCCDLLDQSDELAY_REG
  @param[in] FirstController         - First populated Controller to read from
  @param[in] FirstByte               - First populated Byte to read from

**/
VOID
MrcDriftProg (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32  *OrigVccDllDqsDelay,
  IN UINT32       FirstController,
  IN UINT32       FirstByte
  )
{
  MrcOutput          *Outputs;
  UINT32             Offset;
  UINT32             TargetNUI;
  UINT32             VTDrift;
  UINT32             SysDrift;
  UINT32             FwdClkMinMax;
  UINT32             UIfs;
  UINT32             DriftLimitGlobal;
  UINT32             DriftLimitLocal;
  UINT32             IamA0;
  DATA0CH0_CR_RCOMPDATA0_STRUCT  RcompData0;
  DDRPHY_COMP_CR_VCCDLLDQSDELAY_STRUCT  VccDllDqsDelay;

  VccDllDqsDelay.Data = *OrigVccDllDqsDelay;
  Outputs    = &MrcData->Outputs;
  IamA0      = (MrcData->Inputs.A0) ? 1 : 0;
  UIfs       = (Outputs->Qclkps * 1000) >> ((Outputs->Gear2) ? 1 : 0);
  UIfs       = MAX (UIfs, 1); //Divide by zero protection
  VTDrift    = 15000; //femtosec
  SysDrift   = 15000; //femtosec

  Offset     = OFFSET_CALC_MC_CH (DATA0CH0_CR_RCOMPDATA0_REG, DATA0CH1_CR_RCOMPDATA0_REG, FirstController, DATA1CH0_CR_RCOMPDATA0_REG, FirstByte);
  RcompData0.Data = MrcReadCR (MrcData, Offset);
  TargetNUI = (RcompData0.Bits.DqsNTargetNUI) + 1; //Convert 0-based to 1-based

  FwdClkMinMax = ((TargetNUI * UIfs) - (UIfs / 4) - (UIfs * 9) / 100) / (1 + (VTDrift / UIfs) + (SysDrift / UIfs)); //femtosec
  DriftLimitGlobal = MAX ((UIfs * IamA0 / 2), (UIfs / 4) + ((UIfs * 9) / 100) + VTDrift + (SysDrift * FwdClkMinMax / UIfs)); //femtosec
  DriftLimitLocal = MAX (VTDrift, DriftLimitGlobal - (UIfs / 2));

  // Cast in PI ticks
  DriftLimitGlobal = DriftLimitGlobal * 64 / UIfs;
  DriftLimitLocal = DriftLimitLocal * 64 / UIfs;

  // make sure don't overflow
  DriftLimitLocal = MIN (DriftLimitLocal, 15);
  DriftLimitGlobal = MIN (DriftLimitGlobal, 255);

  VccDllDqsDelay.Bits.DriftLimitGlobal = DriftLimitGlobal;
  VccDllDqsDelay.Bits.DriftLimitLocal = DriftLimitLocal;
  if (*OrigVccDllDqsDelay != VccDllDqsDelay.Data) {
    *OrigVccDllDqsDelay = VccDllDqsDelay.Data;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLDQSDELAY_REG, VccDllDqsDelay.Data);
  }
}

/**
  This function runs DVFS Comp Calibration

  @param[in, out] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcDdrCompCalDvfs (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput          *Outputs;
  MrcInput           *Inputs;
  const MRC_FUNCTION *MrcCall;
  BOOLEAN            Lpddr;
  UINT8              FFRefBit5;
  UINT8              FFRefBit4;
  UINT8              FFRefBit3;
  UINT8              FFRefBit2;
  UINT8              FFRefLSB;
  UINT8              FFRefStatic;
  static UINT8       RCompCodes[MRC_NUM_OF_VSSHI_COMPS] = {0, 0, 0, 1, 2, 3, 4, 7, 8, 15, 16, 31, 32, 63};
  CCC_VSSHI          CCCBlock[MaxVoltageSelect];
  UINT8              CCCVssHi2[MRC_NUM_OF_VSSHI_COMPS];
  UINT8              CCCVssHiQ[MRC_NUM_OF_VSSHI_COMPS];
  UINT8              DQVssHiQ[MRC_NUM_OF_VSSHI_COMPS];
  UINT32             Index;
  UINT32             MaxIndex;
  UINT32             FirstController;
  UINT32             FirstChannel;
  UINT32             FirstCCCBlock;
  UINT32             Offset;
  UINT32             OrigCaPhyComp;
  UINT32             OrigCtlPhyComp;
  UINT32             OrigClkPhyComp;
  UINT32             OrigCaComp;
  UINT32             OrigCtlComp;
  UINT32             OrigClkComp;
  UINT32             OrigDataRcompDrvUp;
  DATA0CH0_CR_RCOMPDATA0_STRUCT  RcompData0;
  DDRPHY_COMP_CR_DDRCRCOMPOVR0_STRUCT  CompOvr0;
  DDRPHY_COMP_CR_DDRCRCOMPCTL0_STRUCT  CompCtl0;
  DDRPHY_COMP_CR_DDRCRCACOMP_STRUCT  CaPhyComp;
  DDRPHY_COMP_CR_DDRCRCTLCOMP_STRUCT  CtlPhyComp;
  DDRPHY_COMP_CR_DDRCRCLKCOMP_STRUCT  ClkPhyComp;
  CCC_CR_DDRCRCACOMP_STRUCT  CaComp;
  CCC_CR_DDRCRCTLCOMP_STRUCT  CtlComp;
  CCC_CR_DDRCRCLKCOMP_STRUCT  ClkComp;
  DDRPHY_COMP_CR_DDRCRDATACOMP0_STRUCT  DataComp0;
  DDRPHY_COMP_CR_VSXHIFFCOMPREF0_STRUCT  VsxHiFFCompRef0;
  DDRPHY_COMP_CR_VSXHIFFCOMPREF1_STRUCT  VsxHiFFCompRef1;

  Inputs       = &MrcData->Inputs;
  MrcCall      = Inputs->Call.Func;
  Outputs      = &MrcData->Outputs;
  Lpddr        = Outputs->Lpddr;
  MaxIndex     = MRC_NUM_OF_VSSHI_COMPS;

  MrcCall->MrcSetMem (CCCVssHi2, sizeof (CCCVssHi2), 0);
  MrcCall->MrcSetMem (CCCVssHiQ, sizeof (CCCVssHiQ), 0);
  MrcCall->MrcSetMem (DQVssHiQ, sizeof (DQVssHiQ), 0);

  FirstController = (MrcControllerExist (MrcData, cCONTROLLER0)) ? 0 : 1;
  if (Lpddr) {
    FirstChannel = Outputs->Controller[FirstController].FirstPopCh;
  } else {
    FirstChannel = 0;
  }
  FirstCCCBlock = (FirstController * MAX_CHANNEL) + FirstChannel;

  //VsxHi FF Equations (Reading and initializing)
  CompCtl0.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL0_REG);
  if (CompCtl0.Bits.ClkVoltageSelect == VoltageSelect_VccDDQ) {
    CCCBlock[VoltageSelect_VccDDQ] = ClkVssHi;
  } else if (CompCtl0.Bits.CaVoltageSelect == VoltageSelect_VccDDQ) {
    CCCBlock[VoltageSelect_VccDDQ] = CaVssHi;
  } else if (CompCtl0.Bits.CtlVoltageSelect == VoltageSelect_VccDDQ) {
    CCCBlock[VoltageSelect_VccDDQ] = CtlVssHi;
  } else {
    CCCBlock[VoltageSelect_VccDDQ] = MaxCccVssHi;
  }
  if (CompCtl0.Bits.ClkVoltageSelect == VoltageSelect_Vccdd2) {
    CCCBlock[VoltageSelect_Vccdd2] = ClkVssHi;
  } else if (CompCtl0.Bits.CaVoltageSelect == VoltageSelect_Vccdd2) {
    CCCBlock[VoltageSelect_Vccdd2] = CaVssHi;
  } else if (CompCtl0.Bits.CtlVoltageSelect == VoltageSelect_Vccdd2) {
    CCCBlock[VoltageSelect_Vccdd2] = CtlVssHi;
  } else {
    CCCBlock[VoltageSelect_Vccdd2] = MaxCccVssHi;
  }

  CompOvr0.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR0_REG);
  CompOvr0.Bits.ClkDrvU = 1;
  CompOvr0.Bits.CtlDrvU = 1;
  CompOvr0.Bits.CmdDrvU = 1;
  CompOvr0.Bits.DqDrvU = 1;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR0_REG, CompOvr0.Data);
  CaPhyComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCACOMP_REG);
  OrigCaPhyComp = CaPhyComp.Data;
  CtlPhyComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCTLCOMP_REG);
  OrigCtlPhyComp = CtlPhyComp.Data;
  ClkPhyComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCLKCOMP_REG);
  OrigClkPhyComp = ClkPhyComp.Data;
  Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCACOMP_REG, CH1CCC_CR_DDRCRCACOMP_REG, FirstCCCBlock);
  CaComp.Data = MrcReadCR (MrcData, Offset);
  OrigCaComp = CaComp.Data;
  Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCTLCOMP_REG, CH1CCC_CR_DDRCRCTLCOMP_REG, FirstCCCBlock);
  CtlComp.Data = MrcReadCR (MrcData, Offset);
  OrigCtlComp = CtlComp.Data;
  Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCLKCOMP_REG, CH1CCC_CR_DDRCRCLKCOMP_REG, FirstCCCBlock);
  ClkComp.Data = MrcReadCR (MrcData, Offset);
  OrigClkComp = ClkComp.Data;
  RcompData0.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP0_REG);
  DataComp0.Data = RcompData0.Data;
  OrigDataRcompDrvUp = DataComp0.Bits.RcompDrvUp;
  //VsxHi FF Equations (Updating Rcomp fields)
  CaPhyComp.Bits.RcompDrvUp = RCompCodes[0];
  CtlPhyComp.Bits.RcompDrvUp = RCompCodes[0];
  ClkPhyComp.Bits.RcompDrvUp = RCompCodes[0];
  CaComp.Bits.RcompDrvUp = RCompCodes[0];
  CtlComp.Bits.RcompDrvUp = RCompCodes[0];
  ClkComp.Bits.RcompDrvUp = RCompCodes[0];
  DataComp0.Bits.RcompDrvUp = RCompCodes[0];
  //VsxHi FF Equations (Write registers)
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCACOMP_REG, CaPhyComp.Data);
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCACOMP_REG, CaComp.Data);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCTLCOMP_REG, CtlPhyComp.Data);
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCTLCOMP_REG, CtlComp.Data);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCLKCOMP_REG, ClkPhyComp.Data);
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCLKCOMP_REG, ClkComp.Data);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP0_REG, DataComp0.Data);
  //Force 1st Comp
  ForceRcomp (MrcData);

  //VssHi (Store Index = 0, Write Out Index = 1)
  Index = 0;
  MrcVssHiCompCalSetup (MrcData, CCCVssHi2, CCCVssHiQ, DQVssHiQ, CCCBlock, FirstCCCBlock, Index, RCompCodes);

  for (Index = 1; Index < MaxIndex; Index++) {
    //Force Comp
    ForceRcomp (MrcData);

    //VsxHi FF Equations (Store Index, Write Out Index+1)
    MrcVssHiCompCalSetup (MrcData, CCCVssHi2, CCCVssHiQ, DQVssHiQ, CCCBlock, FirstCCCBlock, Index, RCompCodes);
  }

  VsxHiFFCompRef0.Data = 0;
  VsxHiFFCompRef1.Data = 0;

  if (CCCBlock[VoltageSelect_VccDDQ] != MaxCccVssHi) {
    //Calculate VssHi Coefficients for CCC VddQ
    MrcVssHiCoeffCalc (MrcData, CCCVssHiQ, &FFRefBit5, &FFRefBit4, &FFRefBit3, &FFRefBit2, &FFRefLSB, &FFRefStatic);
    VsxHiFFCompRef0.Bits.CCCQFFRefBit5 = FFRefBit5;
    VsxHiFFCompRef0.Bits.CCCQFFRefBit4 = FFRefBit4;
    VsxHiFFCompRef0.Bits.CCCQFFRefBit3 = FFRefBit3;
    VsxHiFFCompRef0.Bits.CCCQFFRefBit2 = FFRefBit2;
    VsxHiFFCompRef0.Bits.CCCQFFRefLSB = FFRefLSB;
    VsxHiFFCompRef0.Bits.CCCQFFRefStatic = FFRefStatic;
  }

  if (CCCBlock[VoltageSelect_Vccdd2] != MaxCccVssHi) {
    //Calculate VssHi Coefficients for CCC Vdd2
    MrcVssHiCoeffCalc (MrcData, CCCVssHi2, &FFRefBit5, &FFRefBit4, &FFRefBit3, &FFRefBit2, &FFRefLSB, &FFRefStatic);
    VsxHiFFCompRef0.Bits.CCC2FFRefBit5 = FFRefBit5;
    VsxHiFFCompRef0.Bits.CCC2FFRefBit4 = FFRefBit4;
    VsxHiFFCompRef0.Bits.CCC2FFRefBit3 = FFRefBit3;
    VsxHiFFCompRef1.Bits.CCC2FFRefBit2 = FFRefBit2;
    VsxHiFFCompRef1.Bits.CCC2FFRefLSB = FFRefLSB;
    VsxHiFFCompRef1.Bits.CCC2FFRefStatic = FFRefStatic;
  }

  //Calculate VssHi Coefficients for DQ VddQ
  MrcVssHiCoeffCalc (MrcData, DQVssHiQ, &FFRefBit5, &FFRefBit4, &FFRefBit3, &FFRefBit2, &FFRefLSB, &FFRefStatic);
  VsxHiFFCompRef1.Bits.DQFFRefBit5 = FFRefBit5;
  VsxHiFFCompRef1.Bits.DQFFRefBit4 = FFRefBit4;
  VsxHiFFCompRef1.Bits.DQFFRefBit3 = FFRefBit3;
  VsxHiFFCompRef1.Bits.DQFFRefBit2 = FFRefBit2;
  VsxHiFFCompRef1.Bits.DQFFRefLsb = FFRefLSB;
  VsxHiFFCompRef1.Bits.DQFFRefStatic = FFRefStatic;

  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSXHIFFCOMPREF0_REG, VsxHiFFCompRef0.Data);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSXHIFFCOMPREF1_REG, VsxHiFFCompRef1.Data);

  CompOvr0.Bits.ClkDrvU = 0;
  CompOvr0.Bits.CtlDrvU = 0;
  CompOvr0.Bits.CmdDrvU = 0;
  CompOvr0.Bits.DqDrvU = 0;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR0_REG, CompOvr0.Data);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCACOMP_REG, OrigCaPhyComp);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCTLCOMP_REG, OrigCtlPhyComp);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCLKCOMP_REG, OrigClkPhyComp);
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCACOMP_REG, OrigCaComp);
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCTLCOMP_REG, OrigCtlComp);
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCLKCOMP_REG, OrigClkComp);
  RcompData0.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP0_REG);
  RcompData0.Bits.RcompDrvUp = OrigDataRcompDrvUp;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP0_REG, RcompData0.Data);

  //Force Comp
  ForceRcomp (MrcData);

  return mrcSuccess;
}

/**
  This function records the results of RcompDrvUp for VsxHi LVR

  @param[in, out] MrcData        - Include all MRC global data.
  @param[in, out] ClkRcompDrvUp  - CLK RcompDrvUp (Current Total)
  @param[in, out] CaRcompDrvUp   - CA RcompDrvUp (Current Total)
  @param[in, out] CtlRcompDrvUp  - CTL RcompDrvUp (Current Total)
  @param[in, out] NumOfComps     - # of comps stored (used for division to get average)
**/
VOID
MrcVsxHiLVRDataGathering (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT32  *ClkRcompDrvUp,
  IN OUT UINT32  *CaRcompDrvUp,
  IN OUT UINT32  *CtlRcompDrvUp,
  IN OUT UINT32  *NumOfComps
  )
{
  DDRPHY_COMP_CR_DDRCRCACOMP_STRUCT  CaPhyComp;
  DDRPHY_COMP_CR_DDRCRCLKCOMP_STRUCT  ClkPhyComp;
  DDRPHY_COMP_CR_DDRCRCTLCOMP_STRUCT  CtlPhyComp;

  if (CaRcompDrvUp != NULL) {
    CaPhyComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCACOMP_REG);
    *CaRcompDrvUp += CaPhyComp.Bits.RcompDrvUp;
  }

  if (ClkRcompDrvUp != NULL) {
    ClkPhyComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCLKCOMP_REG);
    *ClkRcompDrvUp += ClkPhyComp.Bits.RcompDrvUp;
  }

  if (CtlRcompDrvUp != NULL) {
    CtlPhyComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCTLCOMP_REG);
    *CtlRcompDrvUp += CtlPhyComp.Bits.RcompDrvUp;
  }

  if (NumOfComps != NULL) {
    *NumOfComps += 1;
  }
}

/**
  This function does the one time compensation for LVR for Rload value.

  @param[in, out] MrcData    - Include all MRC global data.
**/
VOID
MrcVsxHiLVROneTime (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput          *Inputs;
  DDRPHY_COMP_CR_VCCDLLREPLICACTRL1_STRUCT        VccDllReplicaCtrl1;
  DDRPHY_COMP_CR_VCCDLLCOMPDLL_STRUCT             VccDllCompDll;
  DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_STRUCT        CompDvfsRload;

  Inputs     = &MrcData->Inputs;

  VccDllReplicaCtrl1.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLREPLICACTRL1_REG);
  //Dividend is the target Resistance load
  VccDllReplicaCtrl1.Bits.RloadInstances = DIVIDECEIL (800, Inputs->RcompResistor);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLREPLICACTRL1_REG, VccDllReplicaCtrl1.Data);
  ForceRcomp (MrcData);

  VccDllCompDll.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLCOMPDLL_REG);
  CompDvfsRload.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_REG);

  if (VccDllCompDll.Bits.RloadDqs != CompDvfsRload.Bits.VsxHiLVRBias) {
    CompDvfsRload.Bits.VsxHiLVRBias = VccDllCompDll.Bits.RloadDqs;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_REG, CompDvfsRload.Data);
  }

}

/**
  This function runs early DVFS compensation for VsxHi LVR and calculates Error against the
  average RcompDrvUp data for finding optimal value to apply to VsxHiLVRTargetDvfs

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in] CaRcompDrvUpAvg  - Average RcompDrvUp data for Ca.
  @param[in] ClkRcompDrvUpAvg - Average RcompDrvUp data for Clk.
  @param[in] CtlRcompDrvUpAvg - Average RcompDrvUp data for Ctl.

**/
VOID
MrcVsxHiLVREarlyDvfs (
  IN OUT MrcParameters *const MrcData,
  IN UINT32  CaRcompDrvUpAvg,
  IN UINT32  ClkRcompDrvUpAvg,
  IN UINT32  CtlRcompDrvUpAvg
  )
{
  MrcOutput         *Outputs;
  MrcInput          *Inputs;
  UINT8             Counter;
  UINT32            Vdd2Mv;
  UINT32            VccDdqMv;
  UINT32            VccIoMv;
  UINT32            TargetVsxHi;
  UINT32            TargetLow;
  UINT32            TargetHigh;
  INT32             TargetV0;
  INT32             Error;
  INT64             GetSetVal;
  BOOLEAN           ErrorMinimized;
  BOOLEAN           AddClkVoltageSelect;
  BOOLEAN           AddCtlVoltageSelect;
  BOOLEAN           AddCaVoltageSelect;
  DDRPHY_COMP_CR_DDRCRCOMPCTL0_STRUCT  CompCtl0;
  DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_STRUCT  CompDvfsRLoad;
  DDRPHY_COMP_CR_DDRCRCACOMP_STRUCT  PhyComp;

  Outputs     = &MrcData->Outputs;
  Inputs      = &MrcData->Inputs;
  Vdd2Mv      = Outputs->Vdd2Mv;
  Vdd2Mv      = MAX (Vdd2Mv, 1);
  VccDdqMv    = Outputs->VccddqVoltage;
  VccIoMv     = Inputs->VccIomV;
  TargetHigh  = DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_VsxHiLVRTargetDvfs_MAX;
  TargetLow   = DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_VsxHiLVRTargetDvfs_MIN;
  ErrorMinimized = FALSE;

  if (!Outputs->Lpddr) {
    return;
  }

  GetSetVal = 1;
  MrcGetSetNoScope (MrcData, GsmIocScramOvrdPeriodicToDvfsComp, WriteCached, &GetSetVal);

  CompCtl0.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL0_REG);
  CompDvfsRLoad.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_REG);
  TargetVsxHi = Vdd2Mv - (VccDdqMv - (CompCtl0.Bits.CCCVssHiBypassVddqMode ? 0 : Vdd2Mv - VccIoMv));
  TargetVsxHi = RANGE (TargetVsxHi, 100, 450); //Unit is mV

  TargetV0 = (Vdd2Mv + 4 * TargetVsxHi) * 192;  //unit in # of millivolt
  TargetV0 /= (Vdd2Mv * 5); //unitless and *1 granularity
  TargetV0 -= 32;
  TargetV0 = RANGE (TargetV0, 0, 127);

  CompDvfsRLoad.Bits.VsxHiLVRTargetDvfs = (UINT32) TargetV0;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_REG, CompDvfsRLoad.Data);
  AddClkVoltageSelect = (CompCtl0.Bits.ClkVoltageSelect == VoltageSelect_VccDDQ);
  AddCtlVoltageSelect = (CompCtl0.Bits.CtlVoltageSelect == VoltageSelect_VccDDQ);
  AddCaVoltageSelect = (CompCtl0.Bits.CaVoltageSelect == VoltageSelect_VccDDQ);

  Counter = 0;
  do {
    //Force DVFS Comp
    ForceRcomp (MrcData);

    Counter++;
    Error = 0;
    if (AddClkVoltageSelect) {
      PhyComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCLKCOMP_REG);
      Error += (INT32) (PhyComp.Bits.RcompDrvUp - ClkRcompDrvUpAvg);
    }
    if (AddCtlVoltageSelect) {
      PhyComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCTLCOMP_REG);
      Error += (INT32) (PhyComp.Bits.RcompDrvUp - CtlRcompDrvUpAvg);
    }
    if (AddCaVoltageSelect) {
      PhyComp.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCACOMP_REG);
      Error += (INT32) (PhyComp.Bits.RcompDrvUp - CaRcompDrvUpAvg);
    }

    if (Error > 0) {
      //Decrease TargetV0
      TargetHigh = TargetV0;
      TargetV0 += TargetLow;
      TargetV0 /= 2;
    } else if (Error < 0) {
      //Increase TargetV0
      TargetLow = TargetV0;
      TargetV0 += TargetHigh;
      TargetV0 /= 2;
    } else {
      //No change to TargetV0, Done
      TargetLow = TargetHigh = TargetV0;
    }

    if (TargetLow == TargetHigh) {
      //Here when either Error == 0 or when no more range left to sweep
      ErrorMinimized = TRUE;
    } else {
      CompDvfsRLoad.Bits.VsxHiLVRTargetDvfs = (UINT32) TargetV0;
      MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_REG, CompDvfsRLoad.Data);
    }
  } while ((ErrorMinimized == FALSE) && (Counter < 10));
  MRC_DEBUG_ASSERT (Counter < 10, &Outputs->Debug, "MrcVsxHiLVREarlyDvfs failed to Minimize Error!\n");

  //Restore POR CR values
  GetSetVal = 0;
  MrcGetSetNoScope (MrcData, GsmIocScramOvrdPeriodicToDvfsComp, WriteCached, &GetSetVal);

  //Clear DvfsModeEn
  ForceRcomp (MrcData);

}

/**
  This function runs First Comp Calibration - PreTraining
  (VsxHi/Vtt Panic, PDB Cal, Unmatched, View Pins, SideClkPulse)

  @param[in, out] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcDdrCompCalPre (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput           *Inputs;
  MrcOutput          *Outputs;
  BOOLEAN            HVM;
  BOOLEAN            UnMatched;
  BOOLEAN            Lpddr;
  UINT8              Gear2;
  INT8               DqsPTarget;
  INT8               DqsPOffset;
  INT8               DqsNTarget;
  INT8               DqsNOffset;
  INT8               DqsPResult;
  INT8               DqsNResult;
  UINT16             RTargetUp;
  UINT16             RTargetDown;
  UINT16             QclkPs;
  UINT32             Index;
  UINT32             MaxIndex;
  UINT32             FirstController;
  UINT32             FirstChannel;
  UINT32             FirstByte;
  UINT32             FirstCCCBlock;
  UINT32             Offset;
  UINT32             TempValU32;
  UINT32             Temp1ValU32;
  UINT32             DivisorU32;
  UINT32             OrigCompCtl3DqDrvVrefDn;
  UINT32             OrigCompCtl4DqDrvVrefUp;
  UINT32             CaRcompDrvUp;
  UINT32             ClkRcompDrvUp;
  UINT32             CtlRcompDrvUp;
  UINT32             NumOfComps;
  UINT32             OrigRcompData0;
  UINT32             OrigRcompData1;
  INT64              GetSetVal;
  BOOLEAN            UyA0;
  DDRPHY_COMP_CR_VSSHIPANIC_STRUCT  VssHiPanic;
  DDRPHY_COMP_CR_DDRCRVSXHICOMPDATA_STRUCT  VsxHiCompData;
  DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_STRUCT  VttPanic;
  DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_STRUCT  VttPanic2;
  DATA0CH0_CR_DATACOMPVTT_STRUCT  VttCompData;
  DDRPHY_COMP_CR_DDRCRVIEWCTL_STRUCT  ViewCtl;
  DDRPHY_COMP_CR_DDRCRCOMPCTL3_STRUCT  CompCtl3;
  DDRPHY_COMP_CR_DDRCRCOMPCTL4_STRUCT  CompCtl4;
  DDRPHY_COMP_CR_VCCDLLDQSDELAY_STRUCT  VccDllDqsDelay;
  DATA0CH0_CR_RCOMPDATA0_STRUCT  RcompData0;
  DATA0CH0_CR_RCOMPDATA1_STRUCT  RcompData1;
  DLLDDR_CR_DDRCRVCCDLLFFNBIAS_STRUCT  VccDllFfNbias;

  Inputs       = &MrcData->Inputs;
  Outputs      = &MrcData->Outputs;
  HVM          = FALSE; //@todo Add option to Inputs parameter
  RTargetUp    = 50; //Ohms
  RTargetDown  = 50; //Ohms
  QclkPs       = Outputs->Qclkps;
  UnMatched    = ((Outputs->RxMode == MrcRxModeUnmatchedRxWRload) || (Outputs->RxMode == MrcRxModeUnmatchedRxWPpath));
  Gear2        = (Outputs->Gear2) ? 1 : 0;
  Lpddr        = Outputs->Lpddr;
  MaxIndex     = 4;
  UyA0         = Inputs->A0;

  FirstController = (MrcControllerExist (MrcData, cCONTROLLER0)) ? 0 : 1;
  if (Lpddr) {
    FirstChannel = Outputs->Controller[FirstController].FirstPopCh;
  } else {
    FirstChannel = 0;
  }
  FirstByte = (MAX_BYTE_IN_LP_CHANNEL * FirstChannel); //@todo : For DDR5 MAX_BYTE_IN_CHANNEL != 2 so add that
  FirstCCCBlock = (FirstController * MAX_CHANNEL) + FirstChannel;

  // Clean out DqsXOffsetNUI
  Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_RCOMPDATA0_REG, DATA0CH1_CR_RCOMPDATA0_REG, FirstController, DATA1CH0_CR_RCOMPDATA0_REG, FirstByte);
  RcompData0.Data = MrcReadCR (MrcData, Offset);
  RcompData0.Bits.DqsNOffsetNUI = 0;
  MrcWriteCrMulticast (MrcData, DATA_CR_RCOMPDATA0_REG, RcompData0.Data);

  Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_RCOMPDATA1_REG, DATA0CH1_CR_RCOMPDATA1_REG, FirstController, DATA1CH0_CR_RCOMPDATA1_REG, FirstByte);
  RcompData1.Data = MrcReadCR (MrcData, Offset);
  RcompData1.Bits.DqsPOffsetNUI = 0;
  MrcWriteCrMulticast (MrcData, DATA_CR_RCOMPDATA1_REG, RcompData1.Data);

  //1st Comp (Adjust Panic Drivers, View Pin Comp, PBD Deskew, Unmatched RX, VsxHi FF Equations)
  //Adjust Panic Drivers
  VssHiPanic.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VSSHIPANIC_REG);
  VttPanic2.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_REG);
  VssHiPanic.Bits.PanicPDn2xStep = (HVM) ? 1 : 0;
  VttPanic2.Bits.PanicPDn2xStep = (HVM) ? 1 : 0;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSSHIPANIC_REG, VssHiPanic.Data);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_REG, VttPanic2.Data);

  //View Pin Comp
  ViewCtl.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRVIEWCTL_REG);
  ViewCtl.Bits.WrEnViewDrv = 1;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRVIEWCTL_REG, ViewCtl.Data);
  CompCtl3.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL3_REG);
  CompCtl4.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL4_REG);
  OrigCompCtl3DqDrvVrefDn = CompCtl3.Bits.DqDrvVrefDn;
  OrigCompCtl4DqDrvVrefUp = CompCtl4.Bits.DqDrvVrefUp;
  TempValU32 = (191 * RTargetDown) / (RTargetDown + RTargetUp);
  TempValU32 = MIN (191, TempValU32);
  CompCtl3.Bits.DqDrvVrefDn = TempValU32;
  TempValU32 = (191 * 100) / (100 + RTargetUp);
  TempValU32 = MIN (191, TempValU32);
  CompCtl4.Bits.DqDrvVrefUp = TempValU32;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL3_REG, CompCtl3.Data);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL4_REG, CompCtl4.Data);

  //PBD Deskew
  GetSetVal = UDIVIDEROUND (QclkPs, 90);
  MrcGetSetNoScope (MrcData, CmdSlewRate, WriteToCache, &GetSetVal);
  GetSetVal = 1;
  MrcGetSetNoScope (MrcData, CmdScompPC, WriteToCache, &GetSetVal);

  //Unmatched RX
  if (UnMatched) {
    VccDllDqsDelay.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLDQSDELAY_REG);
    VccDllDqsDelay.Bits.RxDqsOffsetComp = 0;
    VccDllDqsDelay.Bits.TrainTargetOffsetUI = 1;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLDQSDELAY_REG, VccDllDqsDelay.Data);

    Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_RCOMPDATA0_REG, DATA0CH1_CR_RCOMPDATA0_REG, FirstController, DATA1CH0_CR_RCOMPDATA0_REG, FirstByte);
    RcompData0.Data = MrcReadCR (MrcData, Offset);

    Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_RCOMPDATA1_REG, DATA0CH1_CR_RCOMPDATA1_REG, FirstController, DATA1CH0_CR_RCOMPDATA1_REG, FirstByte);
    RcompData1.Data = MrcReadCR (MrcData, Offset);

    RcompData0.Bits.DqsNTargetNUI = Gear2;
    RcompData1.Bits.DqsPTargetNUI = Gear2;
    MrcWriteCrMulticast (MrcData, DATA_CR_RCOMPDATA0_REG, RcompData0.Data);
    MrcWriteCrMulticast (MrcData, DATA_CR_RCOMPDATA1_REG, RcompData1.Data);
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP0_REG, RcompData0.Data);
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP1_REG, RcompData1.Data);
    MrcDriftProg (MrcData, &VccDllDqsDelay.Data, FirstController, FirstByte);
  }

  MrcVsxHiLVROneTime (MrcData);

  //Force 1st Comp
  ForceRcomp (MrcData);

  //Adjust Panic Drivers
  if (HVM == FALSE) {
    VsxHiCompData.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRVSXHICOMPDATA_REG);
    DivisorU32 = MAX (VssHiPanic.Bits.VsxHiPanicCompDnMult, 1);
    TempValU32 = VsxHiCompData.Bits.PanicDrvDn / DivisorU32;
    if (TempValU32 > 40) {
      VssHiPanic.Bits.PanicPDn2xStep = 1;
      MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSSHIPANIC_REG, VssHiPanic.Data);
    }
    VttPanic.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_REG);
    VttPanic2.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_REG);

    Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_DATACOMPVTT_REG, DATA0CH1_CR_DATACOMPVTT_REG, FirstController, DATA1CH0_CR_DATACOMPVTT_REG, FirstByte);
    VttCompData.Data = MrcReadCR (MrcData, Offset);
    DivisorU32 = MAX (VttPanic.Bits.VttPanicCompDn0Mult, 1);
    TempValU32 = VttCompData.Bits.PanicVttDn0 / DivisorU32;
    DivisorU32 = MAX (VttPanic.Bits.VttPanicCompDn1Mult, 1);
    Temp1ValU32 = VttCompData.Bits.PanicVttDn1 / DivisorU32;
    TempValU32 = MAX (TempValU32, Temp1ValU32);
    if (TempValU32 > 40) {
      VttPanic2.Bits.PanicPDn2xStep = 1;
      MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_REG, VttPanic2.Data);
    }
  }

  //View Pin Comp
  ViewCtl.Bits.WrEnViewDrv = 0;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRVIEWCTL_REG, ViewCtl.Data);
  CompCtl3.Bits.DqDrvVrefDn = OrigCompCtl3DqDrvVrefDn;
  CompCtl4.Bits.DqDrvVrefUp = OrigCompCtl4DqDrvVrefUp;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL3_REG, CompCtl3.Data);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL4_REG, CompCtl4.Data);

  //PBD Deskew
  MrcGetSetNoScope (MrcData, SCompCodeCmd, ReadUncached, &GetSetVal);
  TempValU32 = (UINT32) (GetSetVal);
  GetSetVal = (TempValU32 >= 26) ? 1 : 0;
  MrcGetSetNoScope (MrcData, GsmIocVccDllRxDeskewCal, WriteToCache, &GetSetVal);
  MrcGetSetNoScope (MrcData, GsmIocVccDllTxDeskewCal, WriteToCache, &GetSetVal);
  MrcGetSetNoScope (MrcData, GsmIocVccDllCccDeskewCal, WriteToCache, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, RxPerBitDeskewCal, WriteToCache, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, TxPerBitDeskewCal, WriteToCache, &GetSetVal);
  MrcGetSetCcc (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MRC_IGNORE_ARG, 0, CccPerBitDeskewCal, WriteToCache, &GetSetVal);
  // although not related to PBD, Scomp result is also used to program the VccDLL clock doubler
  Offset = OFFSET_CALC_CH (DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_REG, DLLDDRDATA1_CR_DDRCRVCCDLLFFNBIAS_REG, FirstCCCBlock);
  Temp1ValU32 = ((TempValU32 * 10) / 45) + 5;
  VccDllFfNbias.Data = MrcReadCR (MrcData, Offset);
  VccDllFfNbias.Bits.SideClkPulse = MIN (Temp1ValU32, 15);
  MrcWriteCR (MrcData, DLLDDR_CR_DDRCRVCCDLLFFNBIAS_REG, VccDllFfNbias.Data);

  CaRcompDrvUp = ClkRcompDrvUp = CtlRcompDrvUp = NumOfComps = 0;
  if (!UyA0 && Lpddr) {
    MrcVsxHiLVRDataGathering (MrcData, &ClkRcompDrvUp, &CaRcompDrvUp, &CtlRcompDrvUp, &NumOfComps);
  }

  for (Index = 1; Index <= MaxIndex; Index++) {
    if (UnMatched) {
      MrcDriftProg (MrcData, &VccDllDqsDelay.Data, FirstController, FirstByte);
    }

    //Force Comp
    ForceRcomp (MrcData);

    if (!UyA0 && Lpddr) {
      MrcVsxHiLVRDataGathering (MrcData, &ClkRcompDrvUp, &CaRcompDrvUp, &CtlRcompDrvUp, &NumOfComps);
    }

    if ((Index == 4) && UnMatched) {
      //Unmatched RX finished
      Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_RCOMPDATA0_REG, DATA0CH1_CR_RCOMPDATA0_REG, FirstController, DATA1CH0_CR_RCOMPDATA0_REG, FirstByte);
      RcompData0.Data = MrcReadCR (MrcData, Offset);
      OrigRcompData0 = RcompData0.Data;

      Offset = OFFSET_CALC_MC_CH (DATA0CH0_CR_RCOMPDATA1_REG, DATA0CH1_CR_RCOMPDATA1_REG, FirstController, DATA1CH0_CR_RCOMPDATA1_REG, FirstByte);
      RcompData1.Data = MrcReadCR (MrcData, Offset);
      OrigRcompData1 = RcompData1.Data;

      DqsNOffset = (INT8) RcompData0.Bits.DqsNOffsetNUI;
      DqsNTarget = (INT8) RcompData0.Bits.DqsNTargetNUI;
      DqsPOffset = (INT8) RcompData1.Bits.DqsPOffsetNUI;
      DqsPTarget = (INT8) RcompData1.Bits.DqsPTargetNUI;

      DqsNResult = DqsNTarget - DqsNOffset;
      DqsPResult = DqsPTarget - DqsPOffset;

      if (DqsPResult > DqsNResult) {
        DqsPTarget = DqsNTarget;
        DqsPOffset = DqsNOffset;
      } else if (DqsPResult < DqsNResult) {
        DqsNTarget = DqsPTarget;
        DqsNOffset = DqsPOffset;
      }

      RcompData0.Bits.DqsNOffsetNUI = DqsNOffset;
      RcompData0.Bits.DqsNTargetNUI = DqsNTarget;
      RcompData1.Bits.DqsPOffsetNUI = DqsPOffset;
      RcompData1.Bits.DqsPTargetNUI = DqsPTarget;

      if (OrigRcompData0 != RcompData0.Data) {
        MrcWriteCrMulticast (MrcData, DATA_CR_RCOMPDATA0_REG, RcompData0.Data);
        MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP0_REG, RcompData0.Data);
      }
      if (OrigRcompData1 != RcompData1.Data) {
        MrcWriteCrMulticast (MrcData, DATA_CR_RCOMPDATA1_REG, RcompData1.Data);
        MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP1_REG, RcompData1.Data);
      }

      VccDllDqsDelay.Bits.RxDqsOffsetComp = 1;
      VccDllDqsDelay.Bits.TrainTargetOffsetUI = 0;
      MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLDQSDELAY_REG, VccDllDqsDelay.Data);
    }
  }

  //Force Comp
  ForceRcomp (MrcData);

  if (!UyA0 && Lpddr) {
    NumOfComps = MAX (NumOfComps, 1);
    CaRcompDrvUp /= NumOfComps;
    ClkRcompDrvUp /= NumOfComps;
    CtlRcompDrvUp /= NumOfComps;
    MrcVsxHiLVREarlyDvfs (MrcData, CaRcompDrvUp, ClkRcompDrvUp, CtlRcompDrvUp);
  }

  return mrcSuccess;
}

/**
  This function train the current supply for the DCO such that the FLL is able to hit 4 GHz.

  @param[in]  MrcData - Pointer to global data.

  @retval MrcStatus - mrcFail if Inputs->ExitOnFailure is set and we cannot reach 4 GHz; otherwise mrcSuccess.
**/
MrcStatus
MrcFllInit (
  IN  MrcParameters *const  MrcData
  )
{
  static const UINT8 FllRefClkDivRatio[4] = {3, 4, 6, 8};
  MrcStatus Status;
  MrcOutput *Outputs;
  UINT32    FllVcoFreq;
  UINT32    RefClkPs;
  UINT8     TuneVal;
  UINT8     FastCalWinVal;
  BOOLEAN   SkipIrefTuning;
  FLL_STATIC_CFG_0_REG_STRUCT FllStaticCfg0;
  FLL_STATIC_CFG_1_REG_STRUCT FllStaticCfg1;
  FLL_CMD_CFG_REG_STRUCT      FllCmdCfg;
  FLL_CMD_CFG_REG_STRUCT      FllCmdCfgSave;
  FLL_DIAG_STAT_REG_STRUCT    FllDiagStat;
  DDRPHY_COMP_CR_DDRCRFLLWIRED_STRUCT             FllWired;
#ifdef MRC_DEBUG_PRINT
  MrcDebug  *Debug;
  Debug = &MrcData->Outputs.Debug;
#endif

  Outputs = &MrcData->Outputs;
  Status  = mrcSuccess;

  // Get current register configuration and save FllCmdCfg
  FllCmdCfgSave.Data = MrcReadCR (MrcData, FLL_CMD_CFG_REG_REG);
  FllCmdCfg.Data = FllCmdCfgSave.Data;

  // Set FLL in closed loop and init for training
  FllStaticCfg0.Data = MrcReadCR (MrcData, FLL_STATIC_CFG_0_REG_REG);
  FllStaticCfg0.Bits.RUNTIME_CAL = 1;
  MrcWriteCR (MrcData, FLL_STATIC_CFG_0_REG_REG, FllStaticCfg0.Data);
  FastCalWinVal = 1 << FllStaticCfg0.Bits.FAST_CAL_WINDOW_VAL;

  FllCmdCfg.Bits.FLL_RATIO = 66;
  MrcWriteCR (MrcData, FLL_CMD_CFG_REG_REG, FllCmdCfg.Data);
  SkipIrefTuning = (FllCmdCfg.Data != FllCmdCfgSave.Data) ? TRUE : FALSE;

  // Calculate FLL RefClk in pS
  FllStaticCfg1.Data = MrcReadCR (MrcData, FLL_STATIC_CFG_1_REG_REG);
  RefClkPs = (1000000 * FllRefClkDivRatio[FllStaticCfg1.Bits.REFCLK_DIVIDE_RATIO_SEL]) / FLL_REF_CLK;

  // Set Wired to use FLL CRI for ratio
  FllWired.Data = MrcReadCR(MrcData, DDRPHY_COMP_CR_DDRCRFLLWIRED_REG);
  FllWired.Bits.FLLCalEnSrc = 1;
  FllWired.Bits.FLLCalRatioSrc = 1;
  MrcWriteCR(MrcData, DDRPHY_COMP_CR_DDRCRFLLWIRED_REG, FllWired.Data);

  if (SkipIrefTuning) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "DcoIrefTune:\tFrequency (MHz)\n");
    for (TuneVal = FLL_CMD_CFG_REG_DCO_IREFTUNE_MIN; TuneVal <= FLL_CMD_CFG_REG_DCO_IREFTUNE_MAX; TuneVal++) {
      // Update the new IrefTune value and enable cold relock.

      // Disable FLL
      FllCmdCfg.Bits.FLL_LDO_ENABLE = 1;
      FllCmdCfg.Bits.FLL_OUT_CLK_REQ_OVRD_EN = 1;
      FllCmdCfg.Bits.FLL_OUT_CLK_REQ = 0;
      FllCmdCfg.Bits.FLL_ENABLE = 0;
      FllCmdCfg.Bits.FLL_LDO_ENABLE = 0;
      MrcWriteCR (MrcData, FLL_CMD_CFG_REG_REG, FllCmdCfg.Data);

      FllCmdCfg.Bits.DCO_IREFTUNE = TuneVal;
      MrcWriteCR (MrcData, FLL_CMD_CFG_REG_REG, FllCmdCfg.Data);

      // Relock FLL
      FllCmdCfg.Bits.FLL_LDO_ENABLE_OVRD_EN = 1;
      FllCmdCfg.Bits.FLL_OUT_CLK_REQ_OVRD_EN = 1;
      FllCmdCfg.Bits.FLL_OUT_CLK_REQ = 1;
      MrcWriteCR (MrcData, FLL_CMD_CFG_REG_REG, FllCmdCfg.Data);

      FllStaticCfg0.Bits.CAL_THRESH_HI = 0x0;
      FllStaticCfg0.Bits.CAL_THRESH_LO = 0x0;
      MrcWriteCR (MrcData, FLL_STATIC_CFG_0_REG_REG, FllStaticCfg0.Data);

      // Enable FLL
      //FllCmdCfg.Bits.DCO_IREFTUNE = TuneVal;
      FllCmdCfg.Bits.FLL_ENABLE = 1;
      FllCmdCfg.Bits.FLL_LDO_ENABLE = 1;
      FllCmdCfg.Bits.FLL_OUT_CLK_REQ = 1;
      MrcWriteCR (MrcData, FLL_CMD_CFG_REG_REG, FllCmdCfg.Data);

      // Wait 2k Cycles, read the count and calculate FLL VCO Freq
      MrcWait (MrcData, ((2 * Outputs->Qclkps)));
      FllDiagStat.Data = MrcReadCR (MrcData, FLL_DIAG_STAT_REG_REG);

      // FLL VCO CLK (MHz) = fll_counter_sum / (fast_cal_window_val * refclk_us * 10)
      // Optimizing the * 10 out of TuneVal calculation so drop a 0 here to be in Kilo instead of Mega units.
      FllVcoFreq = (FllDiagStat.Bits.FLL_COUNTER_SUM * 100000) / (FastCalWinVal * RefClkPs);

      // Check if FLL VCO Freq > 4 GHz and break if we reach 4 GHz
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "%u:\t\t%u\n", TuneVal, FllVcoFreq);
      if (FllVcoFreq > f4000) {
        break;
      }
    }
  } else {
    TuneVal = (UINT8) FllCmdCfgSave.Bits.DCO_IREFTUNE;
  }

  // Disable FLL Training mode
  FllStaticCfg0.Bits.RUNTIME_CAL = 0;
  MrcWriteCR (MrcData, FLL_STATIC_CFG_0_REG_REG, FllStaticCfg0.Data);

  // Program optimal IrefTune
  FllCmdCfg.Bits.DCO_IREFTUNE = TuneVal;
  FllCmdCfg.Bits.FLL_RATIO = FllCmdCfgSave.Bits.FLL_RATIO;
  FllCmdCfg.Bits.FLL_LDO_ENABLE_OVRD_EN = 0;   // Clear to give control to wired interface
  FllCmdCfg.Bits.FLL_LDO_ENABLE = 0;           // Clear to give control to wired interface
  FllCmdCfg.Bits.FLL_OUT_CLK_REQ_OVRD_EN = 0;  // Clear to give control to wired interface
  MrcWriteCR (MrcData, FLL_CMD_CFG_REG_REG, FllCmdCfg.Data);

  FllWired.Bits.FLLCalEnSrc = 0;
  FllWired.Bits.FLLCalRatioSrc = 0;
  MrcWriteCR(MrcData, DDRPHY_COMP_CR_DDRCRFLLWIRED_REG, FllWired.Data);

  if (TuneVal > FLL_CMD_CFG_REG_DCO_IREFTUNE_MAX) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s FLL Training could not reach 4GHz in the DcoIrefTune range\n", gErrString);
    if (MrcData->Inputs.ExitOnFailure) {
      Status = mrcFail;
    }
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n%sDcoIrefTune\nFLL:\t%u\n%sDcoIrefTune\n", gStartTagStr, TuneVal, gStopTagStr);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_ALGO, "End FLL_CMD_CFG_REG_REG = 0x%x\n", MrcReadCR (MrcData, FLL_CMD_CFG_REG_REG));

  return Status;
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
  static const UINT8  OdtModeLut[MrcOdtModeMax] = {2,2,1,0}; //MrcOdtModeDefault - unused, MrcOdtModeVtt, MrcOdtModeVddq, MrcOdtModeVss,
  const MrcInput      *Inputs;
  MrcDebug            *Debug;
  MrcOutput           *Outputs;
  MRC_ODT_MODE_TYPE   CurrentMode;
  INT64               VttMode;
  INT64               VddqMode;
  INT64               DataOdtMode;
  INT64               RxVrefValue;
  INT32               RxVrefMinValue;
  INT32               RxVrefMaxValue;
  INT64               GetRxVrefMin;
  INT64               GetRxVrefMax;
  UINT32              EffPullUp;
  UINT32              Idx;
  UINT32              PuDeltaV;
  UINT32              Offset;
  UINT32              Voh;
  BOOLEAN             Ddr4;
  BOOLEAN             Lpddr4;
  BOOLEAN             Lpddr4Vss;
  DDRVTT0_CR_DDRCRVTTGENCONTROL_STRUCT  VttGenCtl;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  CurrentMode = Outputs->OdtMode;
  Ddr4        = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4      = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr4Vss   = (Lpddr4 && (NewMode == MrcOdtModeVss));

  if ((NewMode >= MrcOdtModeMax) || (NewMode == MrcOdtModeDefault)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "Invalid ODT Mode requested: %d\n", NewMode);
    return mrcWrongInputParameter;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "New ODT Mode: %s\t Original ODT Mode: %s\n", gIoOdtModeStr[NewMode], gIoOdtModeStr[CurrentMode]);
  MrcGetSetLimits (MrcData, RxVref, &GetRxVrefMin, &GetRxVrefMax, NULL);
  RxVrefMinValue = (INT32) GetRxVrefMin;
  RxVrefMaxValue = (INT32) GetRxVrefMax;

  // default mode if no other mode is enabled.  Thus we clear all other modes.
  VttMode   = (NewMode == MrcOdtModeVtt)  ? 1 : 0;
  VddqMode  = (NewMode == MrcOdtModeVddq) ? 1 : 0;
  if (NewMode == MrcOdtModeVss) {
    RxVrefValue = (RxVrefMaxValue + (3 * RxVrefMinValue)) / 4;  // VSS termination: RxVref = 0.25 * Vddq
  } else {
    RxVrefValue = (RxVrefMinValue + RxVrefMaxValue) / 2;  // Middle of the range for VTT termination
  }
  DataOdtMode = OdtModeLut[NewMode];

  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataOdtMode,  WriteToCache, &DataOdtMode);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxVrefMFC,    WriteToCache, &VttMode);

  // Update RxVref to match the new termination type
  // DDR4 will be updated below using MrcSetDefaultRxVrefDdr4
  // LPDDR4 VSS termination will be updated below.
  if (!(Ddr4 || Lpddr4Vss)) {
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, RxVref, WriteToCache | PrintValue, &RxVrefValue);
  }

  MrcGetSetNoScope (MrcData, GsmIocCompVddqOdtEn, WriteToCache, &VddqMode);
  MrcGetSetNoScope (MrcData, GsmIocCompVttOdtEn,  WriteToCache, &VttMode);

  MrcFlushRegisterCachedData (MrcData);

  for (Idx = 0; Idx < DDRIO_MAX_VTT_GEN; Idx++) {
    Offset = DDRVTT0_CR_DDRCRVTTGENCONTROL_REG +
      ((DDRVTT1_CR_DDRCRVTTGENCONTROL_REG - DDRVTT0_CR_DDRCRVTTGENCONTROL_REG) * Idx);
    VttGenCtl.Data = MrcReadCR (MrcData, Offset);
    VttGenCtl.Bits.EnVttOdt = (UINT32) VttMode;
    MrcWriteCR (MrcData, Offset, VttGenCtl.Data);
  }

  Outputs->OdtMode = NewMode;

  if (Ddr4) {
    MrcSetDefaultRxVrefDdr4 (MrcData, TRUE, TRUE); // Update DDR4 RxVref, uses Outputs->OdtMode
  } else if (Lpddr4Vss) {
    Voh = (Outputs->Lp4x) ? 360 : 440;  // mV
    PuDeltaV = ((Outputs->Lp4x) ? VDD_0_60 : VDD_1_10) - Voh;
    EffPullUp = PuDeltaV * Inputs->RcompTarget[RdOdt];
    EffPullUp = DIVIDEROUND (EffPullUp, Voh);
    MrcSetIdealRxVref (MrcData, MAX_CONTROLLER, MAX_CHANNEL, EffPullUp, 80, Inputs->RcompTarget[RdOdt], TRUE);
  }

  return mrcSuccess;
}

/**
  This function decodes which Channel and Byte is connected to a specific DLL Data/CCC partition.
  Use of the Channel/Byte array in GetSet, NOT MrcGetSet.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in] Partition    - DLL Data/CCC partition.
  @param[out] Channel     - Array of corresponding Channel.
  @param[out] Byte        - Array of corresponding Byte.
  @param[out] TargetRail  - Whether it is VccDLL0 (1) or VccDLL1 (2).

  @retval Status - mrcSuccess if partition is expected, otherwise mrcFail
**/
MrcStatus
MrcDllPartitionDecode (
  IN MrcParameters *const MrcData,
  IN DLL_PARTITIONS       Partition,
  OUT UINT32              Channel[VCC_DLL_BYTES],
  OUT UINT32              Byte[VCC_DLL_BYTES],
  OUT UINT32              *TargetRail
  )
{
  MrcOutput            *Outputs;
  MrcInput             *Inputs;
  MrcDebug             *Debug;
  const PHY_PARTITION_BLOCK  *PhyDllPartition;
  MrcStatus            Status;
  MrcDdrType           DdrType;
  UINT32               Index;

  Outputs = &MrcData->Outputs;
  Inputs = &MrcData->Inputs;
  Debug = &Outputs->Debug;
  DdrType = Outputs->DdrType;
  Status = mrcSuccess;

  if (Partition >= DllDdrMax) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s - DLL Data/CCC Partition is not valid! - %x\n", gErrString, Partition);
    Status = mrcFail;
  }
  if ((Channel == NULL) || (Byte == NULL) || (TargetRail == NULL)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s - Missing pointers for return data!\n", gErrString);
    Status = mrcFail;
  }

  if (Status != mrcFail) {
    if ((DdrType == MRC_DDR_TYPE_DDR4) && (Inputs->DqPinsInterleaved == 0)) {
      PhyDllPartition = Ddr4NILDllPartitions[Partition];
    } else {
      PhyDllPartition = LpddrDdr4ILDllPartitions[Partition];
    }
    for (Index = 0; Index < VCC_DLL_BYTES; Index++) {
      Channel[Index] = PhyDllPartition[Index].Channel;
      Byte[Index] = PhyDllPartition[Index].Byte;
    }
    *TargetRail = ((Partition < DllDdrData4) || (Partition == DllDdrCcc0) || (Partition == DllDdrCcc1)) ? VCCDLL1 : VCCDLL2;
  }

  return Status;
}

/**
  This function freezes VccDll or VsxHi voltage rails

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  TargetRail - VccDll Rail North or South.
  @param[in]  Freeze - Freeze or Unfreeze target rail.

**/
VOID
FreezeVccDllVsxHi (
  IN MrcParameters    *const MrcData,
  IN UINT32                  TargetRail,
  IN BOOLEAN                 Freeze
  )
{
  UINT32 Index;
  UINT32 SelCode;
  UINT32 OpenLoop;
  INT64  GetSetEn;
  INT64  GetSetOpenLoop;

  if (TargetRail != VSXHI) {
    Index = TargetRail - VCCDLL1; //Base 0
    SelCode = GsmIocVccDllControlSelCode_V;
    OpenLoop = GsmIocVccDllControlOpenLoop_V;
  } else {
    Index = 1;
    SelCode = GsmIocVsxHiControlSelCode_V;
    OpenLoop = GsmIocVsxHiControlOpenLoop_V;
  }
  GetSetEn = 1;
  GetSetOpenLoop = 0;

  if (Freeze) {
    MrcGetSetVccDll (MrcData, Index, SelCode, ReadCrWriteCached, &GetSetEn);
    GetSetOpenLoop = 1;
  }
  //2 Writes happening to remove chance of race condition between writing OpenLoop = 1 and OutputCode data is reflected back on read.
  MrcGetSetVccDll (MrcData, Index, OpenLoop, ReadCrWriteCached, &GetSetOpenLoop);
  MrcGetSetVccDll (MrcData, Index, OpenLoop, ReadCrForceWriteCached, &GetSetOpenLoop);
}

/**
  This function runs DDRIO Offset Correction - PreTraining
  (VsxHi FB/FF Offset Correction & VccDLL Per Partition Nbias Vref Offset Correction)

  @param[in, out] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcOffsetCorrectionPre (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput          *Outputs;
  MrcDebug           *Debug;
  MrcStatus          Status;
  BOOLEAN            SweepNotFinished;
  DLL_PARTITIONS     Partition;
  GSM_GT             DebugPrint;
  UINT8              McChBitMask;
  UINT8              Counter;
  UINT8              Channel;
  INT16              StartValue;
  INT16              SweepValue;
  INT16              SweepStep;
  INT16              CurrentStep;
  UINT32             Wait4000Qclks;
  UINT32             Index;
  UINT32             TargetRail;
  UINT32             Low;
  UINT32             High;
  UINT32             Middle;
  UINT32             OrigVccDllTarget;
  UINT32             Controller;
  UINT32             Offset;
  UINT32             VccDllControl_SelCode;
  UINT32             ChannelIndex[VCC_DLL_BYTES];
  UINT32             ByteIndex[VCC_DLL_BYTES];
  INT32              LowSigned;
  INT32              HighSigned;
  INT64              GetSetVal;
  INT64              GetSetEn;
  INT64              GetSetMin;
  INT64              GetSetMax;
  DDRPHY_COMP_CR_VCCDLLTARGET_STRUCT  VccDllTarget;
  DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_STRUCT  VccDllFFNBias;
  DDRPHY_COMP_CR_VSSHITARGET_STRUCT  VssHiTarget;
  DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_STRUCT  VssHiControl;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT  CpgcStartTest;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT  CpgcStopTest;
  MC0_CH0_CR_CADB_CFG_STRUCT  CadbConfig;
  MC0_CH0_CR_CADB_CTL_STRUCT  CadbStartTest;
  MC0_CH0_CR_CADB_CTL_STRUCT  CadbStopTest;

  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  Wait4000Qclks = (Outputs->Qclkps * 4) * MRC_TIMER_1NS;
  Status        = mrcSuccess;
  DebugPrint    = GSM_PRINT_VAL;
  GetSetEn      = 1;

  CpgcStartTest.Data = CpgcStopTest.Data = CadbStartTest.Data = CadbStopTest.Data = 0;
  CpgcStartTest.Bits.START_TEST = 1;
  CpgcStopTest.Bits.STOP_TEST = 1;
  CadbStartTest.Bits.START_TEST = 1;
  CadbStopTest.Bits.STOP_TEST = 1;

  //VccDLL Offset Correction
  //Step 1: Feedback Offset Correction
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VccDll_Step1\n");
  GetSetVal = 0;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteCached | DebugPrint, &GetSetVal);
  MrcGetSetNoScope (MrcData, GsmIocEnableSpineGate, WriteCached | DebugPrint, &GetSetVal);
  MrcWeaklockEnDis (MrcData, MRC_ENABLE);

  //Configure VccDLL for feedback loop
  MrcGetSetVccDll (MrcData, 0, GsmIocVccDllControlSelCode_V, ReadCached | DebugPrint, &GetSetVal);
  VccDllControl_SelCode = (UINT32) GetSetVal;

  GetSetVal = 0;
  for (Index = 0; Index < VCC_DLL_BYTES; Index++) {
    MrcGetSetVccDll (MrcData, Index, GsmIocVccDllControlSelCode_V, ReadCrWriteToCache | DebugPrint, &GetSetVal);
  }
  MrcFlushRegisterCachedData (MrcData);

  //Loop TargetRail
  VccDllTarget.Data = OrigVccDllTarget = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG);
  VccDllTarget.Bits.ForceCompAmpOn = 1;
  for (TargetRail = VCCDLL1; TargetRail <= VCCDLL2; TargetRail++) {
    VccDllTarget.Bits.SelectVccDllRail = TargetRail;
    VccDllTarget.Bits.RstCount = 0;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);
    Index = TargetRail - VCCDLL1; //Base 0
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tSweeping TargetRail 0x%x\n", TargetRail);

    //Initialize variables for this Target Rail
    SweepNotFinished = TRUE;
    MrcGetSetLimits (MrcData, GsmIocVccDllControlTarget_V, &GetSetMin, &GetSetMax, NULL);
    LowSigned = (INT32) GetSetMin;
    HighSigned = (INT32) GetSetMax;

    //Binary Sweep Target Rail
    while (SweepNotFinished) {
      GetSetVal = (LowSigned + HighSigned) / 2;
      MrcGetSetVccDll (MrcData, Index, GsmIocVccDllControlTarget_V, ReadCrWriteCached | DebugPrint, &GetSetVal);
      ForceRcomp (MrcData);

      VccDllTarget.Bits.RstCount = 1;
      MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);
      MrcWait (MrcData, Wait4000Qclks);

      VccDllTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\tVccDllTarget.Bits.CountMSB = 0x%x\n", VccDllTarget.Bits.CountMSB);
      if (VccDllTarget.Bits.CountMSB >= 0x8) {
        HighSigned = (INT32) GetSetVal - 1;
      } else {
        LowSigned = (INT32) GetSetVal + 1;
      }
      if (HighSigned < LowSigned) {
        SweepNotFinished = FALSE;
      }
    }
  }
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\n%sPreTrain_Offset_Correction_VccDll_Step1\n", gStartTagStr);
  for (TargetRail = VCCDLL1; TargetRail <= VCCDLL2; TargetRail++) {
    Index = TargetRail - VCCDLL1; //Base 0
    MrcGetSetVccDll (MrcData, Index, GsmIocVccDllControlTarget_V, ReadFromCache, &GetSetVal);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\tTargetRail 0x%x = 0x%x\n", TargetRail, (UINT32) GetSetVal);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%sPreTrain_Offset_Correction_VccDll_Step1\n", gStopTagStr);
#endif

  //Step 2: Comp Nbias Offset Correction
  //Configure VccDLL for feedback loop, done as part of Step 1
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VccDll_Step2\n");
  VccDllTarget.Data = OrigVccDllTarget;
  VccDllTarget.Bits.ForceCompAmpOn = 1;
  VccDllTarget.Bits.SelectVccDllRail = 3; //VccDLL_Replica
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);
  MrcWait (MrcData, Wait4000Qclks); //Wait for Nbias to turn on

  //Initialize variables for this Target Rail
  SweepNotFinished = TRUE;
  Low = DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_NbTarget_MIN;
  High = DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_NbTarget_MAX;
  VccDllFFNBias.Data = MrcReadCR (MrcData, DLLDDRCOMP_CR_DDRCRVCCDLLFFNBIAS_REG);
  Middle = VccDllFFNBias.Bits.NbTarget;

  //Sweep Target Rail
  while (SweepNotFinished) {
    VccDllFFNBias.Bits.NbTarget = Middle;
    MrcWriteCR (MrcData, DLLDDRCOMP_CR_DDRCRVCCDLLFFNBIAS_REG, VccDllFFNBias.Data);

    VccDllTarget.Bits.RstCount = 1;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);
    MrcWait (MrcData, Wait4000Qclks);

    VccDllTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG);
    if (VccDllTarget.Bits.CountMSB >= 0x8) {
      High = Middle - 1;
    } else {
      Low = Middle + 1;
    }
    if (High < Low) {
      SweepNotFinished = FALSE;
    }
    Middle = (High + Low) / 2;
  }
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\n%sPreTrain_Offset_Correction_VccDll_Step2\n", gStartTagStr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\t0x%x\n", VccDllFFNBias.Bits.NbTarget);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%sPreTrain_Offset_Correction_VccDll_Step2\n", gStopTagStr);
#endif

  //Step 4: Per partition Nbias Vref Offset Correction
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VccDll_Step4\n");
  MrcWeaklockEnDis (MrcData, MRC_DISABLE);

  for (TargetRail = VCCDLL1; TargetRail <= VCCDLL2; TargetRail++) {
    FreezeVccDllVsxHi (MrcData, TargetRail, TRUE);
  }

  VccDllTarget.Data = OrigVccDllTarget;
  VccDllTarget.Bits.ForceCompAmpOn = 1;

  StartValue = (INT16) VccDllFFNBias.Bits.NbTarget;

  for (Index = 0; Index < MAX_SYS_CHANNEL; Index++) {
    //CCC (only 8 Phy Channel)
    GetSetVal = 0;
    GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocCccPiEn, WriteToCache | DebugPrint, &GetSetVal);
    GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocCccPiEnOverride, WriteToCache | DebugPrint, &GetSetVal);

    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      //Data (Using Index for Byte/Strobe)
      GetSetVal = 0;
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Controller, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocTxPiPwrDnDis, WriteToCache | DebugPrint, &GetSetVal);
      GetSetVal = 1;
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Controller, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocRxDisable, WriteToCache | DebugPrint, &GetSetVal);
    }
  }
  MrcFlushRegisterCachedData (MrcData);

  McChBitMask = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
      //@todo H/S needs function adjustment for different populated rank across channels
      McChBitMask |= SelectReutRanks (MrcData, (UINT8) Controller, Channel, 1, FALSE, 0);
    }
  }
  SetupIOTestEndless (MrcData, McChBitMask, 10, NSOE, 0, 0, PatWrRdEndless);

  for (Partition = DllDdrData0; Partition < DllDdrMax; Partition++) {
    Status |= MrcDllPartitionDecode (MrcData, Partition, ChannelIndex, ByteIndex, &TargetRail);
    VccDllTarget.Bits.SelectVccDllRail = TargetRail;
    VccDllTarget.Bits.RstCount = 0;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);

    //Setup for this partition
    for (Index = 0; Index < VCC_DLL_BYTES; Index++) {
      if (Partition < DllDdrCcc0) {
        //Data Partitions
        GetSetVal = 1;
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, ByteIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocTxPiPwrDnDis, WriteToCache | DebugPrint, &GetSetVal);
        GetSetVal = 0;
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, ByteIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocRxDisable, WriteToCache | DebugPrint, &GetSetVal);
      } else {
        //CCC Partitions
        GetSetVal = 0x1F;
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocCccPiEn, WriteToCache | DebugPrint, &GetSetVal);
        GetSetVal = 1;
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocCccPiEnOverride, WriteToCache | DebugPrint, &GetSetVal);
      }
    }
    MrcFlushRegisterCachedData (MrcData);

    //Setup for sweep within this Partition
    Counter = 0;
    SweepStep = 0;
    SweepValue = StartValue;
    SweepNotFinished = TRUE;
    Offset = OFFSET_CALC_CH (DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_REG, DLLDDRDATA1_CR_DDRCRVCCDLLFFNBIAS_REG, Partition); //Offsets works across Data and CCC partitions
    if (Partition == DllDdrData0) {
      //Data - CPGC Continous Read/Write
      Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStartTest);
    } else if (Partition == DllDdrCcc0) {
      //Stop CPGC
      Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStopTest);
    }

    //Sweep the setting
    do {
      if (Counter) {
        SweepValue += SweepStep;
        VccDllFFNBias.Bits.NbTarget = (UINT32) SweepValue;
        MrcWriteCR (MrcData, Offset, VccDllFFNBias.Data);
      }
      VccDllTarget.Bits.RstCount = 1;
      MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);
      MrcWait (MrcData, Wait4000Qclks);

      VccDllTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG);
      CurrentStep = (VccDllTarget.Bits.CountMSB >= 0x8) ? -1 : 1;
      if (Counter == 0) {
        SweepStep = CurrentStep;
      }

      if ((SweepValue <= 0) || (SweepValue >= 126) || (CurrentStep != SweepStep)) {
        //SweepValue reached edge of valid range or MSB of CountMSB toggled
        SweepNotFinished = FALSE;
      } else {
        Counter++;
      }
    } while (SweepNotFinished);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Sweep of Partition 0x%x took 0x%x iterations\n", Partition, Counter);

    //Cleanup for this partition
    for (Index = 0; Index < VCC_DLL_BYTES; Index++) {
      if (Partition < DllDdrCcc0) {
        //Data
        GetSetVal = 0;
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, ByteIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocTxPiPwrDnDis, WriteToCache | DebugPrint, &GetSetVal);
        GetSetVal = 1;
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, ByteIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocRxDisable, WriteToCache | DebugPrint, &GetSetVal);
      } else {
        //CCC
        GetSetVal = 0;
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocCccPiEn, WriteToCache | DebugPrint, &GetSetVal);
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocCccPiEnOverride, WriteToCache | DebugPrint, &GetSetVal);
      }
    }
    MrcFlushRegisterCachedData (MrcData);
  }

  //Cleanup of Step 4
  //Clean up by clearing VccDLLControl.OpenLoop, VccDLLComp.ForceCompAmpOn and any other clocking overrides used in the individual partitions.Issue TrainReset
  GetSetVal = VccDllControl_SelCode;
  for (Index = 0; Index < VCC_DLL_BYTES; Index++) {
    MrcGetSetVccDll (MrcData, Index, GsmIocVccDllControlSelCode_V, ReadCrWriteToCache | DebugPrint, &GetSetVal);
  }
  MrcFlushRegisterCachedData (MrcData);
  for (TargetRail = VCCDLL1; TargetRail <= VCCDLL2; TargetRail++) {
    FreezeVccDllVsxHi (MrcData, TargetRail, FALSE);
  }
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, OrigVccDllTarget);

  for (Index = 0; Index < MAX_SYS_CHANNEL; Index++) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      //Data (Using Index for Byte/Strobe)
      GetSetVal = 0;
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Controller, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocTxPiPwrDnDis, WriteToCache | DebugPrint, &GetSetVal);
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Controller, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocRxDisable, WriteToCache | DebugPrint, &GetSetVal);
    }
  }
  MrcFlushRegisterCachedData (MrcData);
  IoReset (MrcData);
  //VccDll is good to rely on from here on
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\n%sPreTrain_Offset_Correction_VccDll_Step4\n", gStartTagStr);
  for (Partition = DllDdrData0; Partition < DllDdrMax; Partition++) {
    Offset = OFFSET_CALC_CH (DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_REG, DLLDDRDATA1_CR_DDRCRVCCDLLFFNBIAS_REG, Partition); //Offsets works across Data and CCC partitions
    VccDllFFNBias.Data = MrcReadCR (MrcData, Offset);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\tPartition 0x%x = 0x%x\n", Partition, VccDllFFNBias.Bits.NbTarget);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%sPreTrain_Offset_Correction_VccDll_Step4\n", gStopTagStr);
#endif

  //VsxHi FB Offset (@todo LPMode = 3)
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VssHi FB Offset\n");
  GetSetVal = 0;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteCached | DebugPrint, &GetSetVal);
  VssHiTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG);
  VssHiTarget.Bits.ForceCompAmpOn = 1;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG, VssHiTarget.Data);

  //Initialize variables for this sweep
  SweepNotFinished = TRUE;
  Low = DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_Target_MIN;
  High = DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_Target_MAX;
  VssHiControl.Data = MrcReadCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG);
  Middle = VssHiControl.Bits.Target;

  //Sweep Target Binary
  while (SweepNotFinished) {
    VssHiControl.Bits.Target = Middle;
    MrcWriteCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG, VssHiControl.Data);
    ForceRcomp (MrcData);

    VssHiTarget.Bits.RstCount = 1;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG, VssHiTarget.Data);
    MrcWait (MrcData, Wait4000Qclks);

    VssHiTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG);
    if (VssHiTarget.Bits.CountMSB >= 0x8) {
      High = Middle - 1;
    } else {
      Low = Middle + 1;
    }
    if (High < Low) {
      SweepNotFinished = FALSE;
    }
    Middle = (High + Low) / 2;
  }
  VssHiTarget.Bits.RstCount = 0;
  VssHiTarget.Bits.ForceCompAmpOn = 0;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG, VssHiTarget.Data);
#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\n%sPreTrain_Offset_Correction_VssHi_FB\n", gStartTagStr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\t0x%x\n", VssHiControl.Bits.Target);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%sPreTrain_Offset_Correction_VssHi_FB\n", gStopTagStr);
#endif

  //VsxHi FF Offset (@todo LPMode = 3)
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "VssHi FF Offset\n");
  GetSetVal = 1;
  MrcGetSetNoScope (MrcData, GsmIocForceCmpUpdt, WriteCached, &GetSetVal);
  MrcWait (MrcData, 100 * MRC_TIMER_1NS);

  //Freeze FB loop
  VssHiControl.Bits.SelCode = 1;
  MrcWriteCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG, VssHiControl.Data);
  VssHiControl.Data = MrcReadCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG);
  VssHiControl.Bits.OpenLoop = 1;
  MrcWriteCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG, VssHiControl.Data);
  VssHiControl.Data = MrcReadCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG);
  //This Write is to remove chance of race condition between writing OpenLoop = 1 and OutputCode data is reflected back on read.
  MrcWriteCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG, VssHiControl.Data);

  //LPMode = 0 (@todo)
  GetSetVal = 1;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteCached | DebugPrint, &GetSetVal);
  IoReset (MrcData);

  //CCC partitions
  SetupIOTestCADB (MrcData, McChBitMask, 10, NSOE, 1, 0);
  //Enable CADB Always On mode (Override the one in SetupIOTest)
  CadbConfig.Data = 0;
  CadbConfig.Bits.CADB_MODE = Cadb20ModeAlwaysOn;
  CadbConfig.Bits.LANE_DESELECT_EN = 5;        // Drive deselects on CS and CA pins; @todo - not sure this is needed in AlwaysOn mode ?
  CadbConfig.Bits.INITIAL_DSEL_EN = 1;
  CadbConfig.Bits.INITIAL_DSEL_SSEQ_EN = 1;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);
  // Enable CADB on MC
  McCadbEnable (MrcData, TRUE);

  //SelectReutRanks skipped as earlier step is still valid

  for (Partition = DllDdrCcc0; Partition <= DllDdrCcc3; Partition++) {
    MrcDllPartitionDecode (MrcData, Partition, ChannelIndex, ByteIndex, &TargetRail);
    //Initialize variables for this Partition
    SweepNotFinished = TRUE;
    MrcGetSetLimits (MrcData, VsxHiClkFFOffset, &GetSetMin, &GetSetMax, NULL);
    LowSigned = (INT32) GetSetMin;
    HighSigned = (INT32) GetSetMax;

    //Binary Sweep
    while (SweepNotFinished) {
      GetSetVal = (LowSigned + HighSigned) / 2;

      //Stop CADB Test
      Cadb20ControlRegWrite (MrcData, McChBitMask, CadbStopTest);

      //Setup for this setting for this partition// AR: Mahmoud to see if the 3 FFOffset needs to be separated
      for (Index = 0; Index < VCC_DLL_BYTES; Index++) {
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, VsxHiClkFFOffset, WriteToCache | DebugPrint, &GetSetVal);
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, VsxHiCaFFOffset, WriteToCache | DebugPrint, &GetSetVal);
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, VsxHiCtlFFOffset, WriteToCache | DebugPrint, &GetSetVal);
      }
      MrcFlushRegisterCachedData (MrcData);
      //ForceCompUpdate to make sure FFOffset takes
      MrcGetSetNoScope (MrcData, GsmIocForceCmpUpdt, WriteCached, &GetSetEn);

      //Start CADB Test
      Cadb20ControlRegWrite (MrcData, McChBitMask, CadbStartTest);

      VssHiTarget.Bits.RstCount = 1;
      MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG, VssHiTarget.Data);
      MrcWait (MrcData, Wait4000Qclks);

      VssHiTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG);
      if (VssHiTarget.Bits.CountMSB >= 0x8) {
        HighSigned = (INT32) GetSetVal - 1;
      } else {
        LowSigned = (INT32) GetSetVal + 1;
      }

      if (HighSigned < LowSigned) {
        SweepNotFinished = FALSE;
      }
    }
  }
  // Stop CADB Test
  Cadb20ControlRegWrite (MrcData, McChBitMask, CadbStopTest);
  // Stop CADB
  CadbConfig.Data = 0;
  Cadb20ConfigRegWrite (MrcData, CadbConfig);
  // Disable CADB on MC
  McCadbEnable (MrcData, FALSE);

  //Data partitions
  GetSetVal = 1;
  for (Index = 0; Index < MAX_SYS_CHANNEL; Index++) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Controller, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocTxDisable, WriteToCache | DebugPrint, &GetSetVal);
    }
  }
  MrcFlushRegisterCachedData (MrcData);

  //Enable CPGC for EndlessWrite
  SetupIOTestBasicVA (MrcData, McChBitMask, 1, NSOE, 0, 0, 10, PatWrEndless, 0, 0);
  Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStartTest);

  for (Partition = DllDdrData0; Partition <= DllDdrData7; Partition++) {
    MrcDllPartitionDecode (MrcData, Partition, ChannelIndex, ByteIndex, &TargetRail);
    //Initialize variables for this Partition
    SweepNotFinished = TRUE;
    MrcGetSetLimits (MrcData, CompOffsetVssHiFF, &GetSetMin, &GetSetMax, NULL);
    LowSigned = (INT32) GetSetMin;
    HighSigned = (INT32) GetSetMax;

    //Setup for this partition
    GetSetVal = 0;
    for (Index = 0; Index < VCC_DLL_BYTES; Index++) {
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, ByteIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocTxDisable, WriteToCache | DebugPrint, &GetSetVal);
    }
    MrcFlushRegisterCachedData (MrcData);

    //Binary Sweep
    while (SweepNotFinished) {
      GetSetVal = (LowSigned + HighSigned) / 2;
      for (Index = 0; Index < VCC_DLL_BYTES; Index++) {
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, ByteIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, CompOffsetVssHiFF, WriteToCache | DebugPrint, &GetSetVal);
      }
      MrcFlushRegisterCachedData (MrcData);
      //ForceCompUpdate to make sure FFOffset takes
      MrcGetSetNoScope (MrcData, GsmIocForceCmpUpdt, WriteCached, &GetSetEn);

      VssHiTarget.Bits.RstCount = 1;
      MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG, VssHiTarget.Data);
      MrcWait (MrcData, Wait4000Qclks);

      VssHiTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG);
      if (VssHiTarget.Bits.CountMSB >= 0x8) {
        HighSigned = (INT32) GetSetVal - 1;
      } else {
        LowSigned = (INT32) GetSetVal + 1;
      }

      if (HighSigned < LowSigned) {
        SweepNotFinished = FALSE;
      }
    }

    //Cleanup for this partition
    GetSetVal = 1;
    for (Index = 0; Index < VCC_DLL_BYTES; Index++) {
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, ByteIndex[Index], MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocTxDisable, WriteToCache | DebugPrint, &GetSetVal);
    }
    MrcFlushRegisterCachedData (MrcData);
  }

  //Clean up
  Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStopTest);

  GetSetVal = 0;
  for (Index = 0; Index < MAX_SYS_CHANNEL; Index++) {
    for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Controller, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, MRC_IGNORE_ARG, MRC_IGNORE_ARG, DdrLevel, GsmIocTxDisable, WriteToCache | DebugPrint, &GetSetVal);
    }
  }
  MrcGetSetNoScope (MrcData, GsmIocForceCmpUpdt, WriteToCache, &GetSetVal);
  MrcFlushRegisterCachedData (MrcData);

  VssHiControl.Bits.OpenLoop = 0;
  MrcWriteCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG, VssHiControl.Data);

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\n%sPreTrain_Offset_Correction_VssHi_FF\n", gStartTagStr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%sPreTrain_Offset_Correction_VssHi_FF\n", gStopTagStr);
#endif

  return mrcSuccess;
}

/**
  This function runs VssHi Regulator Offset Correction - PreTraining
  MRC:RestrictedContent TGL MAS 1.14 - section 3.8.6.7.5

  @param[in, out] MrcData - Include all MRC global data.
  @param[in] DebugPrint   - To print debug messages or not.
**/
void
MrcVssHiRegulatorOffsetCorrection (
  IN OUT MrcParameters *const MrcData,
  IN     BOOLEAN              DebugPrint
  )
{
  MrcInput           *Inputs;
  MrcOutput          *Outputs;
  MrcDebug           *Debug;
  MrcDebugMsgLevel   DebugLevel;
  UINT32             Vdd2Mv;
  INT32              TargetV;
  INT32              PanicV;
  INT32              VccIoMvMinus375mV;
  INT32              ErrorTarget1;
  INT32              ErrorHi1;
  INT32              ErrorLo1;
  INT32              ErrorTarget2;
  INT32              ErrorHi2;
  INT32              ErrorLo2;
  BOOLEAN            Fail;
  DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER_STRUCT  VssHiSampler;
  DDRVSSHIAFEA_CR_DDRCRVSSHICOMPOFFSET_STRUCT  VssHiCompOffset;

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  Vdd2Mv            = Outputs->Vdd2Mv;
  VccIoMvMinus375mV = MAX ((INT32) (Inputs->VccIomV) - 375, 0);
  DebugLevel = DebugPrint ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;

  VssHiSampler.Data = MrcReadCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER_REG);
  TargetV = (VssHiSampler.Bits.Target + 32) * Vdd2Mv / 384;
  PanicV = (VssHiSampler.Bits.Panic) * Vdd2Mv / 384;

  VssHiSampler.Bits.VssHiTargetUsePmos = (TargetV < VccIoMvMinus375mV) ? 1 : 0;
  VssHiSampler.Bits.PanicHiUsePmos = ((TargetV + PanicV) < VccIoMvMinus375mV) ? 1 : 0;
  VssHiSampler.Bits.PanicLoUsePmos = ((TargetV - PanicV) < VccIoMvMinus375mV) ? 1 : 0;

  MrcWriteCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER_REG, VssHiSampler.Data);
  MRC_DEBUG_MSG (Debug, DebugLevel, "Vdd2Mv = %dmV, VccIo - 375 = %dmV, TargetV = %dmV, PanicV = %dmV, DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER = 0x%x\n", Vdd2Mv, VccIoMvMinus375mV, TargetV, PanicV, VssHiSampler.Data);
  ForceRcomp (MrcData);

  Fail = FALSE;
  VssHiCompOffset.Data = MrcReadCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICOMPOFFSET_REG);
  ErrorTarget1 = (VssHiCompOffset.Bits.VsshiTargetCompOfst * Vdd2Mv / 384) + TargetV - VccIoMvMinus375mV;
  ErrorHi1 = (VssHiCompOffset.Bits.PanicHiCompOfst * Vdd2Mv / 384) + TargetV + PanicV - VccIoMvMinus375mV;
  ErrorLo1 = (VssHiCompOffset.Bits.PanicLoCompOfst * Vdd2Mv / 384) + TargetV - PanicV - VccIoMvMinus375mV;
  MRC_DEBUG_MSG (Debug, DebugLevel, "VsshiTargetCompOfst = 0x%x, PanicHiCompOfst = 0x%x, PanicLoCompOfst = 0x%x\n", VssHiCompOffset.Bits.VsshiTargetCompOfst, VssHiCompOffset.Bits.PanicHiCompOfst, VssHiCompOffset.Bits.PanicLoCompOfst);
  if (ErrorTarget1 > 0) {
    Fail = TRUE;
    VssHiSampler.Bits.VssHiTargetUsePmos = ~VssHiSampler.Bits.VssHiTargetUsePmos;
    MRC_DEBUG_MSG (Debug, DebugLevel, "1st Try Error on VssHiTargetUsePmos\n");
  }
  if (ErrorHi1 > 0) {
    Fail = TRUE;
    VssHiSampler.Bits.PanicHiUsePmos = ~VssHiSampler.Bits.PanicHiUsePmos;
    MRC_DEBUG_MSG (Debug, DebugLevel, "1st Try Error on PanicHiUsePmos\n");
  }
  if (ErrorLo1 > 0) {
    Fail = TRUE;
    VssHiSampler.Bits.PanicLoUsePmos = ~VssHiSampler.Bits.PanicLoUsePmos;
    MRC_DEBUG_MSG (Debug, DebugLevel, "1st Try Error on PanicLoUsePmos\n");
  }

  if (Fail) {
    MrcWriteCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER_REG, VssHiSampler.Data);
    MRC_DEBUG_MSG (Debug, DebugLevel, "DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER = 0x%x\n", VssHiSampler.Data);
    ForceRcomp (MrcData);

    Fail = FALSE;
    VssHiCompOffset.Data = MrcReadCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICOMPOFFSET_REG);
    ErrorTarget2 = 375 - ((VssHiCompOffset.Bits.VsshiTargetCompOfst * Vdd2Mv / 384) + TargetV);
    ErrorHi2 = 375 - ((VssHiCompOffset.Bits.PanicHiCompOfst * Vdd2Mv / 384) + TargetV + PanicV);
    ErrorLo2 = 375 - ((VssHiCompOffset.Bits.PanicLoCompOfst * Vdd2Mv / 384) + TargetV - PanicV);
    MRC_DEBUG_MSG (Debug, DebugLevel, "VsshiTargetCompOfst = 0x%x, PanicHiCompOfst = 0x%x, PanicLoCompOfst = 0x%x\n", VssHiCompOffset.Bits.VsshiTargetCompOfst, VssHiCompOffset.Bits.PanicHiCompOfst, VssHiCompOffset.Bits.PanicLoCompOfst);

    if ((ErrorTarget1 > 0) && (ErrorTarget1 < ErrorTarget2)) {
      Fail = TRUE;
      VssHiSampler.Bits.VssHiTargetUsePmos = ~VssHiSampler.Bits.VssHiTargetUsePmos;
      MRC_DEBUG_MSG (Debug, DebugLevel, "2nd Try Error on VssHiTargetUsePmos\n");
    }
    if ((ErrorHi1 > 0) && (ErrorHi1 < ErrorHi2)) {
      Fail = TRUE;
      VssHiSampler.Bits.PanicHiUsePmos = ~VssHiSampler.Bits.PanicHiUsePmos;
      MRC_DEBUG_MSG (Debug, DebugLevel, "2nd Try Error on PanicHiUsePmos\n");
    }
    if ((ErrorLo1 > 0) && (ErrorLo1 < ErrorLo2)) {
      Fail = TRUE;
      VssHiSampler.Bits.PanicLoUsePmos = ~VssHiSampler.Bits.PanicLoUsePmos;
      MRC_DEBUG_MSG (Debug, DebugLevel, "2nd Try Error on PanicLoUsePmos\n");
    }
    if (Fail) {
      MrcWriteCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER_REG, VssHiSampler.Data);
      MRC_DEBUG_MSG (Debug, DebugLevel, "DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER = 0x%x\n", VssHiSampler.Data);
      ForceRcomp (MrcData);
    }
  }

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\n%sVssHi_Regulator_Offset_Correction\n", gStartTagStr);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER = 0x%x\n", VssHiSampler.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "VssHiTargetUsePmos = 0x%x\n", VssHiSampler.Bits.VssHiTargetUsePmos);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "PanicHiUsePmos = 0x%x\n", VssHiSampler.Bits.PanicHiUsePmos);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "PanicLoUsePmos = 0x%x\n", VssHiSampler.Bits.PanicLoUsePmos);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "%sVssHi_Regulator_Offset_Correction\n", gStopTagStr);
#endif

  return;
}

/**
  This function runs the Inner Test Content for  VccDll Read/Write/Idle FF Timing
  Idle isnt implemented for A0

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  VccDllTargetOrig - Register value to avoid reading it again.

  @retval Goodness - Subtract VccDllTarget.CountMSB for 7mV from VccDllTarget.CountMSB -7mV
**/
INT8
RunInnerTest (
  IN MrcParameters    *const MrcData,
  IN UINT32           *const VccdllTarget
)
{
  MrcOutput           *Outputs;
  MrcVddSelect        Vccddq;
  UINT8               McChBitMask;
  UINT8               OffsetV;
  UINT8               CountMSB [MAX_OFFSET_VOLTAGE];
  INT8                Goodness;
  INT16               OffsetVoltage [MAX_OFFSET_VOLTAGE];
  DDRPHY_COMP_CR_VCCDLLTARGET_STRUCT              VccDllTarget;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT  CpgcStartTest;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT  CpgcStopTest;

  Outputs           = &MrcData->Outputs;
  Vccddq            = Outputs->VccddqVoltage;
  McChBitMask       = Outputs->McChBitMask;
  OffsetVoltage[0]  = 7 * 384;
  OffsetVoltage[1]  = -7 * 384;

  CpgcStartTest.Data = CpgcStopTest.Data = 0;
  CpgcStartTest.Bits.START_TEST = 1;
  CpgcStopTest.Bits.STOP_TEST = 1;

  Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStartTest);
  for (OffsetV = 0; OffsetV < MAX_OFFSET_VOLTAGE; OffsetV++) {
    VccDllTarget.Data = *VccdllTarget;
    VccDllTarget.Bits.CompVTarget +=  DIVIDEROUND (OffsetVoltage[OffsetV], Vccddq);
    VccDllTarget.Bits.RstCount = 1;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);
    MrcWait (MrcData, 1000); // Wait 1us, Allow DAC to settle before starting test. The new wait function takes delay in ns
    VccDllTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG);
    CountMSB[OffsetV] = (UINT8) VccDllTarget.Bits.CountMSB;
  }
  Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStopTest);
  Goodness = MrcSE (CountMSB[1], DDRPHY_COMP_CR_VCCDLLTARGET_CountMSB_WID, 8) - MrcSE (CountMSB[0], DDRPHY_COMP_CR_VCCDLLTARGET_CountMSB_WID, 8); // (CountMSB for -7mv) - (CountMSB for 7mv)
  MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_NOTE, "\n Goodness = %i", Goodness);
  return Goodness;
}

/**
  This function finds the best setting for the following :
  FFWriteStagger during FF Write training
  FFRcvEnPi and FFRcvEnPre during FF Read training. FFRcvEnPi + FFRcvEnPre = 5. So we increment FFRcvEnPi while decrementing FFRcvEnPre and determine which
  combination gives us the maximum Goodness.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  CmdType - Pass the enum RdEndless, WrEndless or Idle (enum doesnt exist currently).
  @param[in]  VccdllTarget - Init value for VccDllTarget register
**/
VOID
VccDllCompWriteReadIdleTuning (
  IN MrcParameters    *const MrcData,
  IN UINT8            CmdType,
  IN UINT32           *const VccdllTarget
)
{
  //MrcInput    *Inputs;
  MrcOutput   *Outputs;
  INT8              GoodnessWr[MAX_FF_WRITESTAGGER];
  INT8              GoodnessRd;
  INT8              Goodness;
//  UINT32            OffsetDataControl6;
  UINT32            Offset;
//  UINT32            RcvEnExtFF;
//  UINT32            FirstController;
  UINT8             FFWriteStagger;
  UINT8             FFRcvEnPi;
  UINT8             FFRcvEnPre;
  UINT8             GoodnessRcvEnPi;
  UINT8             GoodnessRcvEnPre;
  UINT8             Byte;
  DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_STRUCT      VccDllFFControl;
//  DATA0CH0_CR_DDRCRDATACONTROL6_STRUCT            DataControl6;

  //Inputs = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  GoodnessRcvEnPi = 0;
  GoodnessRcvEnPre = 0;
  //DataControl6.Data = 0;
  // Read the first populated channel
  // FirstController = (MrcControllerExist (MrcData, cCONTROLLER0)) ? 0 : 1; // This is only needed for DataControl6 Offset read and the Channel is equivalent to controller

  for (Byte = 0; Byte < (MAX_SDRAM_IN_DIMM - 1); Byte++) {
    Offset = DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG + (DLLDDRDATA1_CR_DDRCRVCCDLLFFCONTROL_REG - DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG) * Byte;
    VccDllFFControl.Data = MrcReadCR (MrcData, Offset);
    if (CmdType == PatWrEndless) {
      for (FFWriteStagger = 0; FFWriteStagger < MAX_FF_WRITESTAGGER; FFWriteStagger++) {
        VccDllFFControl.Bits.FFWriteStagger = FFWriteStagger;
        MrcWriteCR (MrcData, Offset, VccDllFFControl.Data);
        GoodnessWr[FFWriteStagger] = RunInnerTest (MrcData, VccdllTarget);
      }
      if (GoodnessWr[0] > GoodnessWr[1]) {
        FFWriteStagger = 0;
      } else {
        FFWriteStagger = 1;
      }
      // Preserve the max goodness value for each byte
      VccDllFFControl.Bits.FFWriteStagger = FFWriteStagger;

    } else if (CmdType == PatRdEndless) {
      GoodnessRd = MRC_INT8_MIN;
      //if (!(Inputs->A0)) {
        //OffsetDataControl6 = DataControl6Offset (FirstController, Byte); // Assume all channels are programmed as first channel
        //DataControl6.Data = MrcReadCR (MrcData, OffsetDataControl6);
      //}
      for (FFRcvEnPi = 0; FFRcvEnPi < MAX_FF_RCVEN_PI; FFRcvEnPi++) {
        for (FFRcvEnPre = 0; FFRcvEnPre < (MAX_FF_RCVEN_PRE - FFRcvEnPi); FFRcvEnPre++) {
          //if (!(Inputs->A0)) {
            //RcvEnExtFF = RANGE (((5 / FFRcvEnPi) * (DataControl6.Bits.RXTogglePreAmble << ((!Outputs->Gear2) ? 1 : 0))), 0, 3);
          //}
          VccDllFFControl.Bits.FFRcvEnPi = FFRcvEnPi;
          VccDllFFControl.Bits.FFRcvEnPre = FFRcvEnPre;
          MrcWriteCR (MrcData, Offset, VccDllFFControl.Data);
          Goodness = RunInnerTest (MrcData, VccdllTarget);
          if (GoodnessRd < Goodness) {
            GoodnessRd = Goodness;
            if (GoodnessRd == DDRPHY_COMP_CR_VCCDLLTARGET_CountMSB_MAX) {
              MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_WARNING, "\n Reached Max Goodness = %d", GoodnessRd);
            }
            GoodnessRcvEnPi = FFRcvEnPi;
            GoodnessRcvEnPre = FFRcvEnPre;
          }
        } // FFRcvEnPre
      } // FFRcvEnPi
      VccDllFFControl.Bits.FFRcvEnPi = GoodnessRcvEnPi;
      VccDllFFControl.Bits.FFRcvEnPre = GoodnessRcvEnPre;
    } // Read
    MrcWriteCR (MrcData, Offset, VccDllFFControl.Data);
  } // Byte
}


/**
  This function trains VccDll for Write, Read and Idle FeedForward timing.
  MRC:RestrictedContent Idle isnt coded for A0 due to RTL bug on LPMode.

  @param[in]  MrcData - Pointer to global MRC data.

  @retval MrcStatus - mrcSuccess
**/
MrcStatus
MrcVccDllFFTiming (
  IN  MrcParameters *const  MrcData
  )
{
  MrcOutput           *Outputs;
  MrcStatus           Status;
  UINT8               NumCL;
  UINT8               VccDllRail;
  UINT8               Wait;
  UINT8               Train;
  UINT32              VccDllTargetOrig;
  DDRPHY_COMP_CR_VCCDLLTARGET_STRUCT           VccDllTarget;


  Status      = mrcSuccess;
  Outputs     = &MrcData->Outputs;
  // BurstLength is in terms of tCK and not in terms of no. of bursts of DQS
  NumCL       = MRC_NUMBURSTS_FFTIMING / (Outputs->BurstLength * 2);

  VccDllTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG);
  VccDllTargetOrig = VccDllTarget.Data;
  VccDllTarget.Bits.ForceCompAmpOn = 1;

  // Run each training i.e Write, Read and Idle
  for (Train = PatWrEndless; Train <= PatRdEndless; Train++) {
    // @todo change the condition to !Idle when Idle is coded
    Wait = ((Train == PatWrEndless) || (Train == PatRdEndless))  ? 32 : 128;  // Number of Qclks to wait between CPGC Algos
    SetupIOTestBasicVA (MrcData, Outputs->McChBitMask, 1, NSOE, 0, 0, 9, Train, Wait, NumCL); // This will setup for Traffic - Idle.

    for (VccDllRail = VCCDLL1; VccDllRail <= VCCDLL2; VccDllRail++) {
      VccDllTarget.Bits.SelectVccDllRail = VccDllRail;
      MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);
      VccDllCompWriteReadIdleTuning (MrcData, Train, &VccDllTarget.Data);
    }
  }

  // Restore the values of VccDllTarget
  VccDllTarget.Data = VccDllTargetOrig;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);
  return Status;
}

/**
  This function runs the test to update the VccDllTarget.countMsb

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  TargetRail - VccDll North or South Rail.
  @param[in]  WaitTime - Wait for function call MrcWait.
  @param[in]  VccDllTargetOrig - Save the original value of VccDllTarget before modifying it.

  @retval Count - Returns CountMsb
**/
INT8
GetVccDllVsxHiCompVrefCountMsb (
  IN MrcParameters    *const MrcData,
  IN UINT8                   TargetRail,
  IN UINT32                  WaitTime,
  IN UINT32           *const TargetOrig
  )
{
  DDRPHY_COMP_CR_VCCDLLTARGET_STRUCT   VccDllTarget;
  DDRPHY_COMP_CR_VSSHITARGET_STRUCT    VssHiTarget;
  UINT8                                CountMsb;
  INT8                                 Count;

  Count = 0;
  if (TargetRail != VSXHI) {
    VccDllTarget.Data = *TargetOrig;
    VccDllTarget.Bits.ForceCompAmpOn = 1;
    VccDllTarget.Bits.SelectVccDllRail = TargetRail;
    VccDllTarget.Bits.RstCount = 1;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);
    MrcWait (MrcData, WaitTime);
    VccDllTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG);
    CountMsb = (UINT8) VccDllTarget.Bits.CountMSB;
    Count = MrcSE (CountMsb, DDRPHY_COMP_CR_VCCDLLTARGET_CountMSB_WID, 8);
  } else {
    VssHiTarget.Data = *TargetOrig;
    VssHiTarget.Bits.ForceCompAmpOn = 1;
    VssHiTarget.Bits.SelectVssHiRail= (TargetRail == VSXHI) ? 1 : 0;
    VssHiTarget.Bits.RstCount = 1;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG, VssHiTarget.Data);
    MrcWait (MrcData, WaitTime);
    VssHiTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG);
    CountMsb = (UINT8) VssHiTarget.Bits.CountMSB;
    Count = MrcSE (CountMsb, DDRPHY_COMP_CR_VSSHITARGET_CountMSB_WID, 8);
  }
  MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "\n Count 0x%x\n", Count);
  return Count;
}

/**
  This function to finds the transition of CountMsb from -ve to +ve or vice-versa

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Code - Feed Forward Offset Code.
  @param[in]  Partition - VccDll Partition.
  @param[in]  TargetRail - VccDll North or South voltage rail.
  @param[in] VccDllTargetOrig - VccDllTarget setting as per Phyinit.
**/
VOID
LinearSearch (
  IN MrcParameters    *const MrcData,
  IN UINT32                  Code,
  IN UINT8                   Partition,
  IN UINT8                   TargetRail,
  IN UINT32           *const VccDllTargetOrig
  )
{
  INT64  TargetVal;
  INT64  Min;
  INT8   Step;
  UINT32 WaitTime;
  UINT32 Channel;
  UINT32 Byte;
  INT64  Max;
  INT16  Result;
  UINT8  MSBValue;
  UINT8  PrevMSBValue;
  UINT8  Par;
  UINT8  ParLimit;
  BOOLEAN Done;
  BOOLEAN IdleOrWeak;

  TargetVal = 0;
  PrevMSBValue = 0;
  Done = FALSE;
  Step = 0;
  //WaitTime = (MrcData->Outputs.Qclkps * 4) * MRC_TIMER_1NS; // The new wait function takes delay in ns
  WaitTime = (MrcData->Outputs.Qclkps * 4); // remove this and uncomment above after TGL_MRC_PO_Branch is merged
  IdleOrWeak = ((Code == GsmIocFFCodeIdleOffset) || (Code == GsmIocFFCodeWeakOffset)) ? TRUE : FALSE;
  ParLimit = IdleOrWeak ? 11 : Partition;

  MrcGetSetLimits (MrcData, Code, &Min, &Max, NULL);
  do {
    // This loop will run only once for all other codes other than IdleOrWeak
    for (Par = Partition; Par <= ParLimit; Par++) {
      // decode Channel and Byte from Partition to program correct VccDllComp reg
      Channel = (Par > (MAX_VCCDLL_DATA_PAR - 1)) ? (Par - MAX_VCCDLL_DATA_PAR) : MRC_IGNORE_ARG;
      Byte = (Par > (MAX_VCCDLL_DATA_PAR - 1)) ? MRC_IGNORE_ARG : Par;
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Byte, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Code, WriteCached, &TargetVal);
    }
    // ClampCheck code
    if ((TargetVal < Min) || (TargetVal > Max)) {
      Done = TRUE;
    }
    Result = GetVccDllVsxHiCompVrefCountMsb (MrcData, TargetRail, WaitTime, VccDllTargetOrig);
    if (IdleOrWeak) {
      Result += GetVccDllVsxHiCompVrefCountMsb (MrcData, VCCDLL2, WaitTime, VccDllTargetOrig); // Result is 16 bits wide because of Binary add for 2 UINT8
    }

    MSBValue = Result ? 1 : 0;
    if (TargetVal == 0) {
      PrevMSBValue = MSBValue;
      Step = (MSBValue) ? -1 : 1;
    } else if (MSBValue != PrevMSBValue) {
      Done = TRUE;
    }
    TargetVal += Step;
  }  while (!Done);

  FreezeVccDllVsxHi (MrcData, TargetRail, TRUE);
  if (IdleOrWeak) {
    FreezeVccDllVsxHi (MrcData, VCCDLL2, TRUE);
  }
}

/**
  This function trains VccDll Per Module FF Offset Correction

  @param[in]  MrcData - Pointer to global MRC data.

  @retval MrcStatus - mrcSuccess if successful, else an error status

**/
MrcStatus
MrcVccDllFFOffsetCorrection (
  IN MrcParameters    *const MrcData
  )
{
  const MrcInput    *Inputs;
  MrcOutput         *Outputs;
  MrcStatus         Status;
  INT64             GetSetVal;
  UINT32            Offset;
  UINT32            Data;
  UINT32            ChannelPerRail[VCC_DLL_BYTES];
  UINT32            BytePerRail[VCC_DLL_BYTES];
  UINT8             NumCL;
  UINT8             Channel;
  UINT8             Byte;
  UINT32            TargetRail;
  UINT32            Code;
  UINT32            FirstController;
  UINT32            FirstChannel;
  UINT32            FirstByte;
  UINT32            VccDllTargetOrig;
  UINT8             VccDllRail;
  UINT8             Index;
  UINT8             ParStart;
  UINT8             ParEnd;
  UINT8             Partition;
  INT64             InternalClocks;
  INT64             TxPiOn;
  INT64             RxPiOn;
  INT64             RxDisable;
  INT64             WlWakeCyc;
  INT64             WlSleepCyc;
  INT32             AvgCodePiOffset;
  UINT32                                  CccPinsUsedSaved[MRC_NUM_CCC_INSTANCES];
  CH0CCC_CR_DDRCRPINSUSED_STRUCT          *CccPinsUsed;
  CH0CCC_CR_DDRCRPINSUSED_P0_STRUCT       *CccPinsUsedP0;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT         CpgcStartTest;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT         CpgcStopTest;

  static UINT32 const TargetCode [] = {GsmIocFFCodeIdleOffset, GsmIocFFCodeWeakOffset, GsmIocFFCodePiOffset, GsmIocFFCodeCCCDistOffset, GsmIocFFCodePBDOffset,
    GsmIocFFCodeWriteOffset, GsmIocFFCodeReadOffset};

  static UINT8 const ParStartEnd[2][MAX_VCCDLL_CODES] =
  { // Code   Idle   Weak   Pi   CCCDist   Pbd   Write   Read
              {0,     0,    0,     8,       0,     0,     0},
              {0,     0,    7,     11,      11,    7,     7}};

  Status  = mrcSuccess;
  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;

  // Assuming Numburst = 32
  NumCL     = MRC_NUMBURSTS_FFTIMING / (Outputs->BurstLength * 2); // BurstLength is in tCK and not in no. of DQS bursts
  Channel = 0; //Initialize to avoid compile errors
  Byte = 0;
  AvgCodePiOffset = 0;

  CpgcStartTest.Data = CpgcStopTest.Data = 0;
  CpgcStartTest.Bits.START_TEST = 1;
  CpgcStopTest.Bits.STOP_TEST = 1;

  // Read VccDllTarget and VccDllControl before modifying them
  VccDllTargetOrig = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG);
  // Read the first populated channel
  FirstController = (MrcControllerExist (MrcData, cCONTROLLER0)) ? 0 : 1;
  FirstChannel = Outputs->Controller[FirstController].FirstPopCh;

  // Save the following fields
  // Assume that the following fields will be same across all channels
  // Following fields are from datacontrol regs, channel is equivalent to controller for offset calc.
  // But these enums go through MrcTranslateSystemToIp translates channel and strobe to corresponding memtech
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocInternalClocksOn, ReadFromCache, &InternalClocks);
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocRxPiPwrDnDis, ReadFromCache, &RxPiOn);
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocTxPiPwrDnDis, ReadFromCache, &TxPiOn);
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocRxDisable, ReadFromCache, &RxDisable);

  // The following enums do not go through Translate function
  if (Outputs->Lpddr) {
    if (FirstController == 1) {
      FirstChannel = FirstChannel + MAX_CHANNEL; // FirstPopCh only returns ch0,1,2,3 so if only Controller 1 is populated, FirstPopCh should be +4
    }
  }
  FirstByte = (MAX_BYTE_IN_LP_CHANNEL * FirstChannel);
  MrcGetSetChStrb (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, FirstByte, GsmIocWlWakeCyc, ReadFromCache, &WlWakeCyc); // Offset calc only needs Byte
  MrcGetSetChStrb (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, FirstByte, GsmIocWlSleepCyclesLp, ReadFromCache, &WlSleepCyc);

  for (Code = 0; Code < ARRAY_COUNT (TargetCode); Code++) {
    ParStart = ParStartEnd[0][Code];
    ParEnd = ParStartEnd[1][Code];
    if (TargetCode[Code] == GsmIocFFCodeReadOffset) {
      Status = MrcResetSequence (MrcData);
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "\n Dram Reset fails at FFCodeReadOffset training \n");
        break;
      }
    }
    for (Partition = ParStart; Partition <= ParEnd; Partition++) {
      MrcDllPartitionDecode (MrcData, Partition, ChannelPerRail, BytePerRail, &TargetRail);
      switch (TargetCode[Code]) {  // Setup DDRIO before starting compensation
        case GsmIocFFCodeIdleOffset:
          GetSetVal = 0;
          MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteCached, &GetSetVal);
          // MrcGetSetNoScope (MrcData, GsmIocScramLpMode, WriteToCache | PrintValue, &GetSetDis);
          MrcWeaklockEnDis (MrcData, MRC_DISABLE);
          FreezeVccDllVsxHi (MrcData, VCCDLL1, TRUE);
          FreezeVccDllVsxHi (MrcData, VCCDLL2, TRUE);
          GetSetVal = 1;
          MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteCached, &GetSetVal);
          TargetRail = VCCDLL1;
          break;

        case GsmIocFFCodeWeakOffset:
          // Internal clocks are already off after Idle
          // TargetRail is already VCCDLL1
          FreezeVccDllVsxHi (MrcData, VCCDLL1, TRUE);
          FreezeVccDllVsxHi (MrcData, VCCDLL2, TRUE);
          // MrcGetSetNoScope (MrcData, GsmIocScramLpMode, WriteToCache | PrintValue, &GetSetDis);
          GetSetVal = 3;
          MrcGetSetChStrb (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MAX_SDRAM_IN_DIMM, GsmIocWlWakeCyc, WriteCached, &GetSetVal);
          GetSetVal = 5;
          MrcGetSetChStrb (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MAX_SDRAM_IN_DIMM, GsmIocWlSleepCyclesLp, WriteCached, &GetSetVal);
          MrcWeaklockEnDis (MrcData, MRC_ENABLE);
          GetSetVal = 1;
          MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteCached, &GetSetVal);
          break;

        case GsmIocFFCodePiOffset:
          MrcWeaklockEnDis (MrcData, MRC_DISABLE);

          GetSetVal = 1;
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetVal);
          }
          FreezeVccDllVsxHi (MrcData, TargetRail, TRUE);

          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSetVal = 1;
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxPiPwrDnDis, WriteCached, &GetSetVal);
          }
          break;

        case GsmIocFFCodeCCCDistOffset:
          MrcWeaklockEnDis (MrcData, MRC_DISABLE);
          GetSetVal = 1;
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetVal);
          }
          FreezeVccDllVsxHi (MrcData, TargetRail, TRUE);
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRPINSUSED_REG, CH1CCC_CR_DDRCRPINSUSED_REG, ChannelPerRail[VccDllRail]);
            CccPinsUsedSaved[ChannelPerRail[VccDllRail]] = MrcReadCR (MrcData, Offset);
            Data = CccPinsUsedSaved[ChannelPerRail[VccDllRail]];
            if (Inputs->UlxUlt) {
              CccPinsUsed = (CH0CCC_CR_DDRCRPINSUSED_STRUCT *) &Data;
              CccPinsUsed->Bits.PiEn = 0x1F;
              CccPinsUsed->Bits.TxEn = 0;
            } else {
              CccPinsUsedP0 = (CH0CCC_CR_DDRCRPINSUSED_P0_STRUCT *) &Data;
              CccPinsUsedP0->P0Bits.PiEn = 0x1F;
              CccPinsUsedP0->P0Bits.TxEn = 0;
            }
            MrcWriteCR (MrcData, Offset, Data);
          }
          break;

        case GsmIocFFCodePBDOffset:
          // PiEn and TxEn are set as per CCCDistOffset, they will be set to init values after this step
          GetSetVal = 1;
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetVal);
          }
          FreezeVccDllVsxHi (MrcData, TargetRail, TRUE);
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRPINSUSED_REG, CH1CCC_CR_DDRCRPINSUSED_REG, ChannelPerRail[VccDllRail]);
            // Set PiEn and TxEn back to Init
            MrcWriteCR (MrcData, Offset, CccPinsUsedSaved[ChannelPerRail[VccDllRail]]);
          }
          break;

        case GsmIocFFCodeWriteOffset:
          GetSetVal = 1;
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetVal);
          }
          FreezeVccDllVsxHi (MrcData, TargetRail, TRUE);
          // Because order needs to be followed for config therefore TxPiOn cant be set above
          GetSetVal = 1;
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocTxPiPwrDnDis, WriteCached, &GetSetVal);
          }
          break;

        case GsmIocFFCodeReadOffset:
          GetSetVal = 1;
          MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxDisable, WriteCached, &GetSetVal);
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSetVal = 1;
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetVal);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxPiPwrDnDis, WriteCached, &GetSetVal);
            GetSetVal = 0;
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxDisable, WriteCached, &GetSetVal);
          }
          FreezeVccDllVsxHi (MrcData, TargetRail, TRUE);
          SetupIOTestBasicVA (MrcData, Outputs->McChBitMask, 1, NSOE, 0, 0, 9, PatRdEndless, 0, NumCL);
          Cpgc20ControlRegWrite (MrcData, Outputs->McChBitMask, CpgcStartTest);
          break;
      } // End of Switch

      LinearSearch (MrcData, TargetCode[Code], Partition, (UINT8) TargetRail, &VccDllTargetOrig);

      // Turn Off Internal clock for that partition for CodePi : CodeRead
      GetSetVal = 0;
      if (!(TargetCode[Code] == GsmIocFFCodeIdleOffset) && !(TargetCode[Code] == GsmIocFFCodeWeakOffset)) {
        for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
          GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetVal);
        }
      } else { // After Idle and Weak set all InternalClocks Off
        MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteCached, &GetSetVal);
      }
      // Restore per partition
      switch (TargetCode[Code]) {
        case GsmIocFFCodePiOffset:
          GetSetVal = 0;
          GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Byte, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxPiPwrDnDis, WriteCached, &GetSetVal);
          break;
        case GsmIocFFCodePBDOffset:
          GetSetVal = 0;
          for (Index = 0; Index < MRC_NUM_CCC_INSTANCES; Index++) {
            Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRPINSUSED_REG, CH1CCC_CR_DDRCRPINSUSED_REG, Index);
            Data = CccPinsUsedSaved[Index];
            if (Inputs->UlxUlt) {
              CccPinsUsed = (CH0CCC_CR_DDRCRPINSUSED_STRUCT *) &Data;
              CccPinsUsed->Bits.PiEn = 0;
            } else {
              CccPinsUsedP0 = (CH0CCC_CR_DDRCRPINSUSED_P0_STRUCT *) &Data;
              CccPinsUsedP0->P0Bits.PiEn = 0;
            }
            MrcWriteCR (MrcData, Offset, Data);
          }
          break;
        case GsmIocFFCodeWriteOffset:
          GetSetVal = 0;
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocTxOn, WriteCached, &GetSetVal);
          }
          break;
        case GsmIocFFCodeReadOffset:
          // stop CPGC
          Cpgc20ControlRegWrite (MrcData, Outputs->McChBitMask, CpgcStopTest);
          GetSetVal = 0;
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxPiPwrDnDis, WriteCached, &GetSetVal);
          }
          break;
      }
    } // Partition

    // Average all FFCodePiOffset from Data partitions and program the CCC partition with that value
    if (TargetCode[Code] == GsmIocFFCodePiOffset) {
      for (Partition = 0; Partition < MAX_VCCDLL_DATA_PAR; Partition++) {
        // Strobe is passed in as Partition, check VccDllDataCCCCompOffset () to see offset calculation
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, (UINT32) Partition, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, TargetCode[Code], ReadFromCache, &GetSetVal);
        AvgCodePiOffset += (INT32) GetSetVal;
      }
      AvgCodePiOffset = (AvgCodePiOffset / MAX_VCCDLL_DATA_PAR);
      GetSetVal = (INT64) AvgCodePiOffset;
      for (Partition = MAX_VCCDLL_DATA_PAR; Partition < MAX_VCCDLL_PAR; Partition++) {
        // Channel is passed in as Partition, check VccDllDataCCCCompOffset () to see offset calculation. CCC VccDllPartitions are programmed
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, (UINT32) Partition, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, TargetCode[Code], WriteCached, &GetSetVal);
      }
    }

    // Restore at the end
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteToCache, &InternalClocks);
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis, WriteToCache, &TxPiOn);
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxDisable, WriteToCache, &RxDisable);
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxPiPwrDnDis, WriteToCache, &RxPiOn);
    for (Byte = 0; Byte < (MAX_SDRAM_IN_DIMM - 1); Byte++) {
      MrcGetSetChStrb (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Byte, GsmIocWlWakeCyc, WriteToCache, &WlWakeCyc);
      MrcGetSetChStrb (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Byte, GsmIocWlSleepCyclesLp, WriteToCache, &WlSleepCyc);
    }
    MrcFlushRegisterCachedData (MrcData);

    for (Index = 0; Index < MRC_NUM_CCC_INSTANCES; Index++) {
      Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRPINSUSED_REG, CH1CCC_CR_DDRCRPINSUSED_REG, Index);
      MrcWriteCR (MrcData, Offset, CccPinsUsedSaved[Index]);
    }
    //CleanUp
    // Unfreeze VccDll, assume OpenLoop = 0 in original as its not set unless we are training VccDll
    FreezeVccDllVsxHi (MrcData, 0, FALSE);
    // Restore VccDllTarget
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTargetOrig);

  } // Code

  return Status;
}

/**
  This function runs the innerloop for kickbacknoise linear search which detects X for every N.
  N - Number of capacitive noise cancelling legs that is the denominator for the equation for each of the codes run in this training
  X - CompVTargetmax - CompVTargetmin

  @param[in] MrcData - Include all MRC global data.
  @param[in] VccDllTargetOrig - VccDllTarget setting as per Phyinit.
  @param[in] TargetRail - VccDll North or South voltage rail.
  @param[in, out] X = CompVTargetmax - CompVTargetmin

  @retval MrcStatus - mrcSuccess if successful, else an error status
**/
MrcStatus
RunInnerTestKickBackNoise (
  IN MrcParameters *const MrcData,
  IN UINT32        *const VccDllTargetOrig,
  IN UINT32               TargetRail,
  IN OUT UINT32           *X
  )
{
  MrcOutput          *Outputs;
  MrcStatus          Status;
  MrcDebug           *Debug;
  UINT32 WaitTime;
  UINT32 CompVTarget;
  INT32  Step;
  INT32  Limit;
  UINT32 CompVTargetMax;
  UINT32 CompVTargetMin;
  BOOLEAN Done;
  BOOLEAN DoneMax;
  BOOLEAN DoneMin;
  DDRPHY_COMP_CR_VCCDLLTARGET_STRUCT  VccDllTarget;

  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;
  Step = 1;
  CompVTargetMax = 0;
  CompVTargetMin = 0;
  Limit = COMPVTARGET_SWINGV / COMPVTARGET_STEPV;
  Done = FALSE;
  DoneMax = FALSE;
  DoneMin = FALSE;
  WaitTime = (MrcData->Outputs.Qclkps * 4) * MRC_TIMER_1NS;
  VccDllTarget.Data = *VccDllTargetOrig;
  CompVTarget = VccDllTarget.Bits.CompVTarget; // Center point
  Status = mrcSuccess;
  do {
    VccDllTarget.Bits.ForceCompAmpOn = 1;
    VccDllTarget.Bits.SelectVccDllRail   = TargetRail;
    VccDllTarget.Bits.CompVTarget = CompVTarget + Step; // Center + 1 or Center -1 depending on the direction of the search
    VccDllTarget.Bits.RstCount = 1;
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTarget.Data);
    MrcWait (MrcData, WaitTime); // Wait 4000Qclks, Allow DAC to settle before starting test.
    VccDllTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG);
    if (VccDllTarget.Bits.CountMSB  == 0) {
      CompVTargetMax = VccDllTarget.Bits.CompVTarget;
      DoneMax = TRUE;
      Step = -1;
    } else if (VccDllTarget.Bits.CountMSB  == 0xF) {
      CompVTargetMin = VccDllTarget.Bits.CompVTarget;
      DoneMin = TRUE;
    } else {
      if (!DoneMax && (Step < Limit)) {
        Step += 1;
      } else if (!DoneMin && (ABS (Step) < Limit)) {
        Step -= 1;
      } else {
        if (!DoneMax && (Step == Limit)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n Couldn't find CompVTargetMax, try increasing COMPVTARGET_SWINGV from 25mV to 30mV \n");
          Status = mrcFail;
          break;
        } else if (!DoneMin && (ABS (Step) == Limit)) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n Couldn't find CompVTargetMin, try increasing COMPVTARGET_SWINGV from 25mV to 30mV \n");
          Status = mrcFail;
          break;
        }
      }
    }
    Done = ((DoneMax == TRUE) && (DoneMin == TRUE));

  } while (!Done);
  if (Status == mrcSuccess) {
    CompVTargetMax -= CompVTargetMin;
    *X = CompVTargetMax; // X must not be -ve
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "CompVTargetMax = %d CompVTargetMin = %d, X = %d\n", CompVTargetMax, CompVTargetMin, X);

  return Status;
}

/**
  This function is used to perform linear search for VccDll Kickback noise correction
  MRC:RestrictedBegin
  The purpose of KickBackNoise correction is to find ideal number of capcanel legs for each Code.
  Number of legs is determined N which is the denominator for each of the equation for each code.
  Default N = 33. Finding N is a linear process. Optimal N will with the range of 29 - 38.
  Within each N loop we need to find bestX. X = VccDllTarget.CompVTargetMax - VccDllTarget.CompVTargetMin
  MAS proposes a faster search for X but each step in CompVTarget causes a 2.6mV change. Expected X will be within
  -25mV to +25 mV which is about 10 steps. Therefore Binary search wont work and hence linear search is deployed.
  MRC:RestrictedEnd

  @param[in]     MrcData          - Include all MRC global data.
  @param[in]     Code             - Coupling cap register fields.
  @param[in]     Partition        - VccDll Partition.
  @param[in]     TargetRail       - VccDll North or South voltage rail.
  @param[in]     VccDllTargetOrig - VccDllTarget setting as per Phyinit.
  @param[in,out] NIdle            - Remember BestN for CodeIdle.
  @param[in,out] NWrite           - Remember BestN for CodeWrite.
  @param[in,out] NRead            - Remember BestN for CodeRead.

  @retval Status - mrcSuccess if successful, else an error status
**/
MrcStatus
LinearSearchKickBackNoise (
  IN MrcParameters *const MrcData,
  IN UINT32               Code,
  IN UINT8                Partition,
  IN UINT32               TargetRail,
  IN UINT32        *const VccDllTargetOrig,
  IN OUT UINT8            *NIdle,
  IN OUT UINT8            *NWrite,
  IN OUT UINT8            *NRead
) {
  MrcStatus  Status;
  INT64    GetSetVal;
  UINT32   NewCode;
  UINT32   OrigCode;
  UINT32   Channel;
  UINT32   Byte;
  UINT32    X;
  UINT32    Xcompare;
  UINT8    BestN;
  UINT8    N;
  BOOLEAN  PiOrPBD;

  Xcompare = 126;
  X = 0; // initialize
  Status = mrcSuccess;
  BestN = 1; // dont set to 0 , to avoid any divide by 0 errors
  PiOrPBD = ((Code == GsmIocCapCancelCodePi) || (Code == GsmIocCapCancelCodePBD));
  // decode Channel and Byte from Partition. Channel is only used to program CCC partitions, Byte is used for data par
  Channel = (Partition > (MAX_VCCDLL_DATA_PAR - 1)) ? (Partition - MAX_VCCDLL_DATA_PAR) : MRC_IGNORE_ARG;
  Byte = (Partition > (MAX_VCCDLL_DATA_PAR - 1)) ? MRC_IGNORE_ARG : Partition;

  // Program the register field
  GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Byte, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Code, ReadFromCache, &GetSetVal);
  OrigCode = (UINT32) GetSetVal;

  if (!PiOrPBD) {
    for (N = (NDEFAULT - 4); N < (NDEFAULT + 5); N++) {
      NewCode = OrigCode * NDEFAULT;
      NewCode /= N;
      GetSetVal = NewCode;
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Byte, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Code, WriteCached, &GetSetVal);
      Status = RunInnerTestKickBackNoise (MrcData, VccDllTargetOrig, TargetRail, &X);
      if (Status != mrcSuccess) {
        return Status;
      }
      if (X < Xcompare) {
        if (Status == mrcSuccess) {
          Xcompare = X;
          BestN = N;
        } else {
          break;
        }
      }
    }
  }

    switch (Code) {
      case GsmIocCapCancelCodeIdle:
        *NIdle = BestN;
        break;

      case GsmIocCapCancelCodeWrite:
        *NWrite = BestN;
        break;

      case GsmIocCapCancelCodeRead:
        *NRead = BestN;
        break;

      case GsmIocCapCancelCodePi:
      case GsmIocCapCancelCodePBD:
        BestN = *NIdle;
        BestN += *NWrite;
        BestN += *NRead;
        BestN /= 3;
        NewCode = OrigCode * NDEFAULT;
        NewCode /= BestN;
        GetSetVal = NewCode;
        GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Byte, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Code, WriteCached, &GetSetVal);
        break;

      default:
        break;
    }

  return Status;
}

/**
  VccDll KickBackNoise Correction
  MRC:RestrictedContent - Described in MAS 3.1.7.4.8. MRC needs to tune the circuit to reduce noise induced by NBias feed foreward legs.
  This is the main function for this training and its organized as follows :
    Setup
    Call linear search and update the reg field
    Restore per partition
    Restore at the end

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcFail if Inputs->ExitOnFailure is set and we cannot reach 4 GHz; otherwise mrcSuccess.
**/
MrcStatus
MrcKickBackNoiseCorrection (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcStatus         Status;
  INT64             GetSetEn;
  INT64             GetSetDis;
  INT64             InternalClocks;
  INT64             TxPiOn;
  INT64             RxPiOn;
  INT64             RxDisable;
  UINT32            Code;
  UINT32            ChannelPerRail[VCC_DLL_BYTES];
  UINT32            BytePerRail[VCC_DLL_BYTES];
  UINT32            TargetRail;
  UINT32            VccDllTargetOrig;
  UINT32            FirstController;
  UINT32            FirstChannel;
  UINT8             NIdle;
  UINT8             NWrite;
  UINT8             NRead;
  UINT8             Partition;
  UINT8             ParStart;
  UINT8             ParEnd;
  UINT8             VccDllRail;
  UINT8             McChBitMask;
  UINT8             Wait;
  UINT8             NumCL;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT  CpgcStartTest;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT  CpgcStopTest;

  static UINT32 const TargetCode [] = {GsmIocCapCancelCodeIdle, GsmIocCapCancelCodeWrite, GsmIocCapCancelCodeRead, GsmIocCapCancelCodePi, GsmIocCapCancelCodePBD};

  Outputs     = &MrcData->Outputs;
  McChBitMask = Outputs->McChBitMask;
  CpgcStartTest.Data = CpgcStopTest.Data = 0;
  CpgcStartTest.Bits.START_TEST = 1;
  CpgcStopTest.Bits.STOP_TEST = 1;
  Wait = 64 / 2;
  NumCL       = 64 / (Outputs->BurstLength * 2);
  GetSetEn  = 1;
  GetSetDis = 0;
  NIdle  = 0;
  NWrite = 0;
  NRead  = 0;
  Status = mrcSuccess;

  // Read VccDllTarget and VccDllControl before modifying them
  VccDllTargetOrig = MrcReadCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG);
  // Read the first populated channel
  FirstController = (MrcControllerExist (MrcData, cCONTROLLER0)) ? 0 : 1;
  FirstChannel = Outputs->Controller[FirstController].FirstPopCh;

  // Save the following fields
  // Assume that the following fields will be same across all channels
  // Following fields are from datacontrol regs, channel is equivalent to controller for offset calc.
  // But these enums go through MrcTranslateSystemToIp translates channel and strobe to corresponding memtech
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocInternalClocksOn, ReadFromCache, &InternalClocks);
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocRxPiPwrDnDis, ReadFromCache, &RxPiOn);
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocTxPiPwrDnDis, ReadFromCache, &TxPiOn);
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocRxDisable, ReadFromCache, &RxDisable);

  static UINT8 const ParStartEnd[2][MAX_KICKBACK_CODES] = {
  //Code  Idle  Write   Read  Pi  Pbd
    {      0,     0,     0,   0,    8},
    {      11,    7,     7,   11,   11}};

  for (Code = 0; Code < ARRAY_COUNT (TargetCode); Code++) {
    ParStart = ParStartEnd[0][Code];
    ParEnd = ParStartEnd[1][Code];
    if (TargetCode[Code] == GsmIocCapCancelCodeRead) {
      Status = MrcResetSequence (MrcData);
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "\n Dram Reset fails at FFCodeReadOffset training \n");
        break;
      }
    }
    for (Partition = ParStart; Partition <= ParEnd; Partition++) {
      MrcDllPartitionDecode (MrcData, Partition, ChannelPerRail, BytePerRail, &TargetRail);
      switch (TargetCode[Code]) {  // Setup DDRIO before starting compensation
        case GsmIocCapCancelCodeIdle:
          MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteCached, &GetSetDis);
          MrcWeaklockEnDis (MrcData, MRC_ENABLE);
          FreezeVccDllVsxHi (MrcData, TargetRail, TRUE);
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetEn);
          }
          // Turn off Internal Clocks of TargetRail at the partition restore of this Code
          break;

        case GsmIocCapCancelCodeWrite:
          FreezeVccDllVsxHi (MrcData, TargetRail, TRUE);
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetEn);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocTxPiPwrDnDis, WriteCached, &GetSetEn);
          }
          SetupIOTestBasicVA (MrcData, McChBitMask, 1, NSOE, 0, 0, 9, PatWrEndless, Wait, NumCL);
          Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStartTest);
          break;

        case GsmIocCapCancelCodeRead:
          FreezeVccDllVsxHi (MrcData, TargetRail, TRUE);
          MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxDisable, WriteCached, &GetSetEn);
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetEn);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxPiPwrDnDis, WriteCached, &GetSetEn);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxDisable, WriteCached, &GetSetDis);
          }
          SetupIOTestBasicVA (MrcData, McChBitMask, 1, NSOE, 0, 0, 9, PatRdEndless, Wait, NumCL);
          Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStartTest);
          break;

        case GsmIocCapCancelCodePi:
          break;
        case GsmIocCapCancelCodePBD:
          break;

      } // End of Switch
      Status = LinearSearchKickBackNoise (MrcData, Code, Partition, TargetRail, &VccDllTargetOrig, &NIdle, &NWrite, &NRead);
      if ((Status != mrcSuccess) && MrcData->Inputs.ExitOnFailure) {
        MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "\n Linear Search for BestN and smallest X values failed for Code  %d Partition %d \n", Code, Partition);
        return Status;
      }
      // Restore per partition
      switch (TargetCode[Code]) {
        case GsmIocCapCancelCodeIdle:
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetDis);
          }
          MrcWeaklockEnDis (MrcData, MRC_DISABLE);
          break;

        case GsmIocCapCancelCodeWrite:
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetDis);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocTxPiPwrDnDis, WriteCached, &GetSetDis);
          }
          Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStopTest);
          break;

        case GsmIocCapCancelCodeRead:
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached, &GetSetDis);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxPiPwrDnDis, WriteCached, &GetSetDis);
          }
          Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStopTest);
          break;

        case GsmIocCapCancelCodePi:
        case GsmIocCapCancelCodePBD:
          break;
      } // end of switch
    } // End of Partition

    // Restore at the end of the code
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteToCache, &InternalClocks);
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis, WriteToCache, &TxPiOn);
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxDisable, WriteToCache, &RxDisable);
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxPiPwrDnDis, WriteToCache, &RxPiOn);
    MrcFlushRegisterCachedData (MrcData);

    // CleanUp
    // Unfreeze VccDll, assume OpenLoop = 0 in original as its not set unless we are training VccDll
    FreezeVccDllVsxHi (MrcData, 0, FALSE);
    // Restore VccDllTarget
    MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDllTargetOrig);

  } // Code
  return Status;
}

/**
  This function to finds the transition of CountMsb from -ve to +ve or vice-versa

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Code - Feed Forward Offset Code.
  @param[in]  Partition - VccDll Partition
  @param[in]  TargetOrig - VsxHiFFTarget setting as per Phyinit.
  @param[in,out] MIdle - Best M value for CodeIdle.
  @param[in,out] MWrite - Best M value for CodeWrite.
  @param[in,out] MRead - Best M value for CodeRead.
**/
VOID
LinearSearchVsxHi (
  IN MrcParameters    *const MrcData,
  IN UINT32                  Code,
  IN UINT8                   Partition,
  IN UINT32           *const TargetOrig,
  IN OUT UINT32              *MIdle,
  IN OUT UINT32              *MWrite,
  IN OUT UINT32              *MRead
  )
{
  INT64  TargetDefault;
  INT64  TargetVal;
  INT64  Min;
  INT8   Step;
  UINT32 DefaultM;
  UINT32 M;
  UINT32 MTrain;
  UINT32 MScale;
  UINT32 Numerator;
  UINT32 WaitTime;
  UINT32 Channel;
  UINT32 Byte;
  INT64  Max;
  INT16  Result;
  UINT8  MSBValue;
  UINT8  PrevMSBValue;
  BOOLEAN Done;

  PrevMSBValue = 0;
  Done = FALSE;
  Step = 0;
  DefaultM = 0;
  WaitTime = (MrcData->Outputs.Qclkps * 4);

  // decode channel and byte from partition. This is only pertinent if we have multiple partitions
  Channel = (Partition > (MAX_VCCDLL_DATA_PAR - 1)) ? (Partition - MAX_VCCDLL_DATA_PAR) : MRC_IGNORE_ARG;
  Byte = (Partition > (MAX_VCCDLL_DATA_PAR - 1)) ? MRC_IGNORE_ARG : Partition;
  GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Byte, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Code, ReadCached | PrintValue, &TargetDefault);
  TargetVal = TargetDefault;

  // Lookup Default M
  switch (Code) {
    case GsmIocVssHiFFCodeIdle :
      DefaultM = 18;
      break;
    case GsmIocVssHiFFCodeRead :
    case GsmIocVssHiFFCodeWrite :
      DefaultM = 20;
      break;
    case GsmIocVssHiFFCodePBD :
      DefaultM = 13;
      break;
    case GsmIocVssHiFFCodePi :
      DefaultM = 7;
      break;
  }
  M = DefaultM;
  Numerator = (UINT32) TargetDefault * DefaultM;
  MrcGetSetLimits (MrcData, Code, &Min, &Max, NULL);
  if ((Code != GsmIocVssHiFFCodePBD) || (Code != GsmIocVssHiFFCodePi)) {
    do {
      GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Byte, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Code, WriteCached | PrintValue, &TargetVal);
      // ClampCheck code
      if ((TargetVal < Min) || (TargetVal > Max)) {
        Done = TRUE;
      }
      Result = GetVccDllVsxHiCompVrefCountMsb (MrcData, VSXHI, WaitTime, TargetOrig);

      MSBValue = Result ? 1 : 0;
      if (TargetVal == TargetDefault) {
        PrevMSBValue = MSBValue;
        Step = (MSBValue) ? -1 : 1;
      } else if (MSBValue != PrevMSBValue) {
        Done = TRUE;  // Dont stop here, do the full sweep and report. Parameterize the sweep
        switch (Code) {
          case GsmIocVssHiFFCodeIdle :
            *MIdle = M;
            break;
          case GsmIocVssHiFFCodeWrite :
            *MWrite = M;
            break;
          case GsmIocVssHiFFCodeRead :
            *MRead = M;
            break;
          default:
            *MIdle = 0;
            *MWrite = 0;
            *MRead = 0;
            break;
        }
      }
      M += Step;
      if (M == 0) {
        M = DefaultM;
        MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_WARNING, "\n M has hit the value of 0 and therefore being restored to its default value");
      }
      TargetVal = Numerator / M;
    }  while (!Done);
  } else {
    MScale = (*MIdle + *MWrite + *MRead) / 3;
    MTrain = MScale * DefaultM;
    if (MTrain == 0) {
      MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_WARNING, "\n MIdle + MWrite + MRead = 0, restoring MTrain to be 1 to avoid divide by 0 fault");
      MTrain = 1;
    }
    TargetVal = Numerator / MTrain ;
    MRC_DEBUG_MSG (&MrcData->Outputs.Debug, MSG_LEVEL_NOTE, "\n MTrain %d, Mscale %d, Numerator %d\n", MTrain, MScale, Numerator);
    GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Channel, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Byte, MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Code, WriteCached | PrintValue, &TargetVal);
  }
}

/**
  VsxHiFFTuning
  MRC:RestrictedContent - Described in MAS 3.1.7.5 VccDll injects alot of noise on VsxHi rail
  so MRC needs to tune the VsxHi FF legs to compensate

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcFail if Inputs->ExitOnFailure is set and we cannot reach 4 GHz; otherwise mrcSuccess.
**/
MrcStatus
MrcVsxHiPostTrainingComp (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcStatus         Status;
  INT64             GetSetEn;
  INT64             GetSetDis;
  INT64             InternalClocks;
  INT64             TxPiOn;
  INT64             RxPiOn;
  INT64             RxDisable;
  UINT32            Code;
  UINT32            ChannelPerRail[VCC_DLL_BYTES];
  UINT32            BytePerRail[VCC_DLL_BYTES];
  UINT32            TargetRail;
  UINT32            VsxHiTargetOrig;
  UINT32            FirstController;
  UINT32            FirstChannel;
  UINT32            MIdle;
  UINT32            MWrite;
  UINT32            MRead;
  UINT8             Partition;
  UINT8             ParStart;
  UINT8             ParEnd;
  UINT8             VccDllRail;
  UINT8             McChBitMask;
  UINT8             Wait;
  UINT8             NumCL;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT  CpgcStartTest;
  MC0_REQ0_CR_CPGC_SEQ_CTL_STRUCT  CpgcStopTest;
  static UINT32 const TargetCode [] = {GsmIocVssHiFFCodeIdle, GsmIocVssHiFFCodeWrite, GsmIocVssHiFFCodeRead, GsmIocVssHiFFCodePBD, GsmIocVssHiFFCodePi};

  Outputs = &MrcData->Outputs;
  McChBitMask = Outputs->McChBitMask;
  CpgcStartTest.Data = CpgcStopTest.Data = 0;
  CpgcStartTest.Bits.START_TEST = 1;
  CpgcStopTest.Bits.STOP_TEST = 1;
  Wait = 64 / 2;
  NumCL = 64 / (Outputs->BurstLength * 2);
  GetSetEn = 1;
  GetSetDis = 0;
  MIdle = 0;
  MWrite = 0;
  MRead = 0;
  Status = mrcSuccess;

  VsxHiTargetOrig = MrcReadCR (MrcData,  DDRPHY_COMP_CR_VSSHITARGET_REG);
  // Read the first populated channel
  FirstController = (MrcControllerExist (MrcData, cCONTROLLER0)) ? 0 : 1;
  FirstChannel = Outputs->Controller[FirstController].FirstPopCh;

  // Save the following fields
  // Assume that the following fields will be same across all channels
  // Following fields are from datacontrol regs, channel is equivalent to controller for offset calc.
  // But these enums go through MrcTranslateSystemToIp translates channel and strobe to corresponding memtech
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocInternalClocksOn, ReadFromCache, &InternalClocks);
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocRxPiPwrDnDis, ReadFromCache, &RxPiOn);
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocTxPiPwrDnDis, ReadFromCache, &TxPiOn);
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, 0, GsmIocRxDisable, ReadFromCache, &RxDisable);

  static UINT8 const ParStartEnd[2][MAX_VSXHI_CODES] = {
  //Code Idle  Write Read   Pi  Pbd
         {0,    0,    0,    0,  8},
         {11,   7,    7,    11, 11}};
  for (Code = 0; Code < ARRAY_COUNT (TargetCode); Code++) {
    if (TargetCode[Code] == GsmIocVssHiFFCodeRead) {
      Status = MrcResetSequence (MrcData);
      if (Status != mrcSuccess) {
        MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_ERROR, "\n Dram Reset fails at VssHiFFCodeRead training \n");
        break;
      }
    }
    ParStart = ParStartEnd[0][Code];
    ParEnd = ParStartEnd[1][Code];
    for (Partition = ParStart; Partition <= ParEnd; Partition++) {
      MrcDllPartitionDecode (MrcData, Partition, ChannelPerRail, BytePerRail, &TargetRail);
      switch (TargetCode[Code]) {  // Setup DDRIO before starting compensation
        case GsmIocVssHiFFCodeIdle:
          MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteCached, &GetSetDis);
          MrcWeaklockEnDis (MrcData, MRC_ENABLE);
          FreezeVccDllVsxHi (MrcData, VSXHI, TRUE);
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached | PrintValue, &GetSetEn);
          }
          break;

        case GsmIocVssHiFFCodeWrite:
          FreezeVccDllVsxHi (MrcData, VSXHI, TRUE);
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached | PrintValue, &GetSetEn);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocTxPiPwrDnDis, WriteCached | PrintValue, &GetSetEn);
          }
          SetupIOTestBasicVA (MrcData, McChBitMask, 1, NSOE, 0, 0, 9, PatWrEndless, Wait, NumCL);
          Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStartTest);
          break;

        case GsmIocVssHiFFCodeRead:
          FreezeVccDllVsxHi (MrcData, VSXHI, TRUE);
          MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxDisable, WriteCached, &GetSetEn);
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached | PrintValue, &GetSetEn);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxPiPwrDnDis, WriteCached | PrintValue, &GetSetEn);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxDisable, WriteCached | PrintValue, &GetSetDis);
          }
          SetupIOTestBasicVA (MrcData, McChBitMask, 1, NSOE, 0, 0, 9, PatRdEndless, Wait, NumCL);
          Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStartTest);
          break;
        case GsmIocVssHiFFCodePBD:
        case GsmIocVssHiFFCodePi:
          // No setup as alternative way is implemented
          break;
      } // switch
      LinearSearchVsxHi (MrcData, Code, Partition, &VsxHiTargetOrig, &MIdle, &MWrite, &MRead);

      // Restore per partition, wouldnt be necessary if the training isnt per partition
      switch (Code) {
        case GsmIocVssHiFFCodeIdle:
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached | PrintValue, &GetSetDis);
          }
          MrcWeaklockEnDis (MrcData, MRC_DISABLE);
          break;

        case GsmIocVssHiFFCodeWrite:
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached | PrintValue, &GetSetDis);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocTxPiPwrDnDis, WriteCached | PrintValue, &GetSetDis);
          }
          Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStopTest);
          break;

        case GsmIocVssHiFFCodeRead:
          for (VccDllRail = 0; VccDllRail < VCC_DLL_BYTES; VccDllRail++) {
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocInternalClocksOn, WriteCached | PrintValue, &GetSetDis);
            GetSet (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, ChannelPerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, BytePerRail[VccDllRail], MRC_IGNORE_ARG, MRC_IGNORE_ARG, MRC_IGNORE_ARG, GsmIocRxPiPwrDnDis, WriteCached | PrintValue, &GetSetDis);
          }
          Cpgc20ControlRegWrite (MrcData, McChBitMask, CpgcStopTest);
          break;
      } // switch
    } // Partition
    // Restore at the end of the code
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocInternalClocksOn, WriteToCache | PrintValue, &InternalClocks);
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocTxPiPwrDnDis, WriteToCache | PrintValue, &TxPiOn);
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxDisable, WriteToCache | PrintValue, &RxDisable);
    MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxPiPwrDnDis, WriteToCache | PrintValue, &RxPiOn);
    MrcFlushRegisterCachedData (MrcData);

    // CleanUp
    // Unfreeze VsxHi, assume OpenLoop = 0 in original as its not set unless we are training VsxHi
    FreezeVccDllVsxHi (MrcData, VSXHI, FALSE);
    // Restore VsxHiTarget
    MrcWriteCR (MrcData,  DDRPHY_COMP_CR_VSSHITARGET_REG, VsxHiTargetOrig);

  } // Code
  return Status;
}

/**
  VsxHiFFTuning
  MRC:RestrictedContent - Described in MAS 3.1.7.5 VccDll injects alot of noise on VsxHi rail
  so MRC needs to tune the VsxHi FF legs to compensate

  @param[in] MrcData - Include all MRC global data.
  @retval MrcStatus - mrcFail if Inputs->ExitOnFailure is set and we cannot reach 4 GHz; otherwise mrcSuccess.
**/
MrcStatus
MrcVsxHiFFTuning (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput         *Outputs;
  MrcStatus         Status;
  UINT32            FirstController;
  UINT32            FirstChannel;
  UINT32            Offset;
  UINT32            VccDllBlock;
  DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_STRUCT  VccDllFFControl;

  Outputs = &MrcData->Outputs;
  Status  = mrcSuccess;
  FirstController = (MrcControllerExist (MrcData, cCONTROLLER0)) ? 0 : 1;
  FirstChannel = Outputs->Controller[FirstController].FirstPopCh;
  VccDllBlock = ((MAX_CCC_PER_CHANNEL * FirstController) + FirstChannel);
  Offset = OFFSET_CALC_CH (DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_REG, DLLDDRDATA1_CR_DDRCRVCCDLLFFCONTROL_REG, VccDllBlock) ;
  VccDllFFControl.Data = MrcReadCR (MrcData, Offset);
  if (VccDllFFControl.Bits.LocalVsxHiBypass) {
    MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_NOTE, "\n VsxHiFFTuning Skipped because LocalVsxHiBypass is set\n");
  } else if (VccDllFFControl.Bits.Bypass) {
    MrcWriteCR (MrcData, DLLDDR_CR_DDRCRVCCDLLVSXHIFF_REG, 0);
    MRC_DEBUG_MSG (&Outputs->Debug, MSG_LEVEL_NOTE, "\n VsxHiFFTuning Skipped because VccDllBypass is set. VccDllVsxHiFF\n");
  } else {
    Status = MrcVsxHiPostTrainingComp (MrcData);
  }
  return Status;
}




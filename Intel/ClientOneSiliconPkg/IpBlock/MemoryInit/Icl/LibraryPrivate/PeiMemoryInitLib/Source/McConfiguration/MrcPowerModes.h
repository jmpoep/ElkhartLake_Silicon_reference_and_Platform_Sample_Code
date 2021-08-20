/** @file
  This module includes the power modes definitions.

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
#ifndef _MrcPowerModes_h_
#define _MrcPowerModes_h_
#pragma pack(push, 1)

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcGlobal.h"

//
// Lookup table definitions
//
#define VDD_120     1
#define VDD_135     2
#define VDD_150     3
#define VDD_OTHER   4
#define ECC_F       0
#define ECC_T       1
#define TYPE_SODIMM 3
#define TYPE_UDIMM  2
#define WIDTH_4     0
#define WIDTH_8     1
#define WIDTH_16    2
#define WIDTH_32    3
#define RANKS_1     1
#define RANKS_2     2
#define DPC_1       1
#define DPC_2       2
#define FREQ_1067   3
#define FREQ_1200   4
#define FREQ_1333   5
#define FREQ_1400   6
#define FREQ_1600   7
#define FREQ_1800   8
#define FREQ_1867   9
#define FREQ_2000   10
#define FREQ_2133   11
#define FREQ_2200   12
#define FREQ_2400   13
#define FREQ_2600   14
#define FREQ_2667   15
#define DENSITY_2   3
#define DENSITY_4   4
#define DENSITY_8   5
#define DIMM_POSITION_1  0
#define DIMM_POSITION_2  1

typedef enum {
  tsmNoThermalSensing = 0,  ///< No thermal sensing in MC
  tsmThermalSensor,         ///< Thermal Sensor (on DIMM) - when set thermal sense is active
  tsmBwEstimation,          ///< BW estimation - when set, PM_SUM_PC_CxRy of this DIMM accumulates command power estimation
  tsmBoth                   ///< Both (1) and (2)
} ThermalSensorModes;

///
/// Power Down mode
///
typedef enum {
  pdmNoPowerDown      = 0,
  pdmAPD              = 1,
  pdmPPD              = 2,
  pdmPPDDLLOFF        = 6,
  pdmAuto             = 0xFF,
} MrcPowerDownMode;

typedef union {
  struct {
    UINT32 Vddq        :  4;
    UINT32 Ecc         :  1;
    UINT32 DimmType    :  4;
    UINT32 DeviceWidth :  3;
    UINT32 NumOfRanks  :  3;
    UINT32 Dpc         :  2;
    UINT32 Frequency   :  4;
    UINT32 DramDensity :  3;
    UINT32 Spare       :  8;
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8 Data8[4];
} PowerWeightInputs;

typedef struct {
  PowerWeightInputs PwInput;
  UINT8             ScaleFactor;
  UINT8             RdCr;
  UINT8             WrCr;
  UINT8             ActCr;
  UINT8             CkeL;
  UINT8             CkeH;
  UINT8             ChPwrFloor;
} DdrPowerWeightEntry;

#define PDWN_IDLE_COUNTER_ULX_ULT   (0x40)
#define PDWN_IDLE_COUNTER_DT_HALO   (0x80)

#define MCDECS_CBIT_DEFAULT (0x00000000)

/**
  This function configure the MC power register post training after normal mode before PCU start working.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing.
**/
extern
void
MrcPowerModesPostTraining (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function configures the power down control register.

  @param[in]  - MrcData - The MRC global data.

  @retval - Nothing
**/
extern
void
MrcPowerDownConfig (
  IN MrcParameters *const MrcData
  );

/**
  This functions applies power weight values from lookup table to every DIMM in the system.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
extern
MrcStatus
MrcPowerWeight (
  MrcParameters * const MrcData
);

#ifdef UP_SERVER_FLAG
typedef union {
  struct {
    UINT32 Vddq        :  4;
    UINT32 Ecc         :  1;
    UINT32 DimmType    :  4;
    UINT32 DeviceWidth :  3;
    UINT32 NumOfRanks  :  3;
    UINT32 DimmPos     :  2;
    UINT32 Dpc         :  2;
    UINT32 Frequency   :  4;
    UINT32 DramDensity :  3;
    UINT32 Spare       :  6;
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} PowerUpWeightInputs;

typedef struct {
  PowerUpWeightInputs PwInput;
  UINT8                  ScaleFactor;
  UINT8                  RdCr;
  UINT8                  WrCr;
  UINT8                  ActCr;
  UINT8                  CkeL;
  UINT8                  CkeH;
  UINT8                  ChPwrFloor;
  UINT8                  WarmB;
  UINT8                  HotB;
  UINT8                  ThermOffset;
} DdrUpPwEntry;

/**
  This functions applies power weight values  and TSOD values according to DIMM configuration

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
extern
MrcStatus
MrcUpPowerWeightAndTsod (
  MrcParameters * const MrcData
);

/**
CLTM Initialization Checking

  @param[in] MrcData - Include all MRC global data.

**/
extern
void
MrcCltmTsodInitChecking (
  MrcParameters * const MrcData
);


/**
CLTM TSOD Configuration

  @param[in] MrcData - Include all MRC global data.

**/
extern
void
CltmTsodConfiguration (
  MrcParameters * const MrcData
);

/**

This function will disable CLTM

  @param[in] MrcData - Include all MRC global data.

**/
extern
void
MrcCltmDisable (
  MrcParameters * const MrcData
);
#endif

/**
  Configures Memory Thermal settings

  @param[in] MrcData  - The MRC "global data" area.
  @retval: mrcSuccess if the write is successful, otherwise mrcFail.
**/
extern
MrcStatus
MrcThermalConfig (
  IN MrcParameters *const MrcData
  );

#pragma pack(pop)
#endif // _MrcPowerModes_h_

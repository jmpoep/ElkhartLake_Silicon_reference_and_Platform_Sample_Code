/** @file
  Definition of LPDDR4 Specific functions, constants, defines,
  and data structures.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#ifndef _MRC_LPDDR_4_H_
#define _MRC_LPDDR_4_H_
#include "MrcLpddr4Registers.h"

///
/// Multi-Purpose Commands (MPC)
///
#define MRC_LP4_MPC_NOP           (0x0)
#define MRC_LP4_MPC_RD_FIFO       (0x41)
#define MRC_LP4_MPC_RD_DQ_CAL     (0x43)
#define MRC_LP4_MPC_RFU1          (0x45)
#define MRC_LP4_MPC_WR_FIFO       (0x47)
#define MRC_LP4_MPC_RFU2          (0x49)
#define MRC_LP4_MPC_START_DQS_OSC (0x4B)
#define MRC_LP4_MPC_STOP_DQS_OSC  (0x4D)
#define MRC_LP4_MPC_ZQCAL_START   (0x4F)
#define MRC_LP4_MPC_ZQCAL_LATCH   (0x51)

/// tOSCO = max(40ns, 8nCK). 40ns is the max for all supported frequencies
#define MRC_LP4_tOSCO_FS 40000000

/// tCKE values for LPDDR4: max(7.5ns, 4nCK). 7.5ns is the max for 1067 and above
#define tCKE_LPDDR4_FS 7500000

/// tCKELCS = Max(5ns, 5nCK)
#define MRC_LP4_tCKELCS_PS          (5 * 1000)

/// tCAENT = 250ns
#define MRC_LP4_tCAENT_NS           (250)

/// tFC_Long = 250ns
#define MRC_LP4_tFC_LONG_NS         (250)

/// tVRCG_DISABLE = 100ns
#define MRC_LP4_tVRCG_DISABLE_NS    (100)

/// tVRCG_ENABLE = 200ns
#define MRC_LP4_tVRCG_ENABLE_NS     (200)

/// tVrefCA_Long = 250ns
#define MRC_LP4_tVREFCA_LONG_NS     (250)

/// tVrefCA_Short = 80ns
#define MRC_LP4_tVREFCA_SHORT_NS    (80)

///
/// ZQ fixed delay values
///   Unrealistic that we will be using low enough frequencies that nCK is the longer delay.
///
/// tZQCAL = 1us
#define MRC_LP4_ZQ_CAL_DELAY_US     (1)
#define MRC_LP4_ZQ_CAL_DELAY_NS     (1000)
/// tZQLAT = MAX (30ns, 8nCK)
#define MRC_LP4_ZQ_LATCH_DELAY_NS   (30)
/// tZQRESET = MAX (50ns, 3nCK)
#define MRC_LP4_ZQ_RESET_DELAY_NS   (50)

///
/// ZQ Reset Op Code and MR
///
#define MRC_LP4_ZQ_RESET_MR         (10)
#define MRC_LP4_ZQ_RESET_OP_CODE    (0x1B)

///
/// Precharge to Precharge Delay for all Frequencies in DCLK
///
#define MRC_LP4_tPPD_ALL_FREQ (4)

///
/// CAS-to-CAS delay for all frequencies in DCLK
///
#define MRC_LP4_tCCD_ALL_FREQ (8)

///
/// tODTon / tODToff values in [ps]
///
#define MRC_LP4_tODT_ON_MIN   1500
#define MRC_LP4_tODT_ON_MAX   3500
#define MRC_LP4_tODT_Off_MIN  1500
#define MRC_LP4_tODT_Off_MAX  3500

///
/// tDQSCK values in [ps]
///
#define tDQSCK_MIN_LP4  1500
#define tDQSCK_TYP_LP4  2400
#define tDQSCK_MAX_LP4  3500

///
/// Initialization Timing Parameters
///
#define MRC_LP4_tINIT0_US   20000   ///< Max voltage-ramp time
#define MRC_LP4_tINIT1_US   200     ///< Min RESET_n low time after Voltage Ramp
#define MRC_LP4_tINIT2_NS   10      ///< Min CKE low time before RESET_n high
#define MRC_LP4_tINIT3_US   2000    ///< Min CKE low time after RESET_n high
#define MRC_LP4_tINIT4_TCK  5       ///< Min stable clock before first CKE high
#define MRC_LP4_tINIT5_US   2       ///< Min idle time before first MR[W,R]

///
/// Vref related defines
///
#define MRC_LP4_VREF_CODE_MAX     50      ///< Maximum possible MR Code for LPDDR4 Write/Command Vref
#define MRC_LP4_VREF_OFFSET_MIN   (-40)   ///< Minimum possible Vref offset for LPDDR4 Write/Command Vref
#define MRC_LP4_VREF_OFFSET_MAX   40      ///< Maximum possible Vref offset for LPDDR4 Write/Command Vref
#define MRC_LP4_VREF_MIDDLE_RANGE 286     ///< mV
#define MRC_LP4_VREF_STEP_SIZE      4400  ///< uV
#define MRC_LP4_VREF_MIN          110000  ///< uV
#define MRC_LP4_VREF_MAX          462000  ///< uV
#define MRC_LP4X_VREF_MIN          90000  ///< uV
#define MRC_LP4X_VREF_MAX         377400  ///< uV
#define MRC_LP4X_VREF_STEP_SIZE     3600  ///< uV

///
/// tDQS2DQ in femtoseconds.
///
#define MRC_LP4_tDQS2DQ_MIN_FS 200000
#define MRC_LP4_tDQS2DQ_MAX_FS 800000

///
/// tDQSCK in femtoseconds.
///
#define MRC_LP4_tDQSCK_MAX_FS 3600000

#define LP4_RZQ_NUM_VALUES (7)

/// ODTLon Timing Array Index.
typedef enum {
  Lp4OdtlOn,
  Lp4OdtlOff,
  Lp4OdtlMax
} LPDDR4_ODTL_PARAM;

///
/// Structure Definitions
///
typedef struct {
  UINT16  RttWr;
  UINT16  RttCa;
} TOdtValueLpddr4;

typedef struct {
  UINT32  Frequency;
  UINT8   OdtlOn[Lp4WlSetMax];
  UINT8   OdtlOff[Lp4WlSetMax];
} LP4_ODTL_TIMING_TYPE;

// This table is the list of possible terminations the DRAM can achieve using ZQ Resistor.
extern const UINT16 Lp4RzqValues[LP4_RZQ_NUM_VALUES];

///
/// Function Declaration
///
/**
  This function is used to get the timing parameter tDQS2DQ Min or Max.

  @param[in]  IsMin - TRUE returns the minimum value, FALSE returns the maximum value.

  @retval UINT32 - The requested parameter in Femptoseconds.
**/
UINT32
Lpddr4GetTdqs2dq (
  IN  BOOLEAN IsMin
  );

/**
  This function configures the terminating ranks to the programmed FSP (FSP-OP = 1) to enable
  their CA ODT termination for the non-terminating ranks.  This is done across all LPDDR4 channels.

  @param[in]  MrcData - Pointer to the MRC global data.
  @param[in]  Enable  - Boolean parameter to enable(TRUE) or disable(FALSE) CA termination.

  @retval MrcStatus - mrcSuccess otherwise an error status.
**/
MrcStatus
MrcLpddr4SetCbtCaOdtEn (
  IN  MrcParameters *const  MrcData,
  IN  BOOLEAN               Enable
  );

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only WriteRecovery does error checking against spec valid values.

  @param[in]      MrcData         - Pointer to MRC global data.
  @param[in]      SdramWidth      - LPDDR4 device width (8 or 16)
  @param[in]      BurstLength     - Number of DRAM bursts (UI) per command.
  @param[in]      WrPreambleLen   - Write Preamble length in tCK.
  @param[in]      RdPreambleType  - Switch to select between a static or toggling read Preamble.
  @param[in]      WriteRecovery   - Write Recovery time for auto pre-charge commands.
  @param[in]      RdPostambleLen  - Length of the read postamble.
  @param[in,out]  MrData          - Pointer to MR data to update.

  @retval MrcStatus - mrcWrongInputParameter or mrcSuccess.
**/
MrcStatus
MrcLpddr4SetMr1 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 SdramWidth,
  IN      UINT8                 BurstLength,
  IN      UINT8                 WrPreambleLen,
  IN      UINT8                 RdPreambleType,
  IN      UINT8                 WriteRecovery,
  IN      UINT8                 RdPostambleLen,
  IN OUT  UINT16                *MrData
  );

/*
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only RdLatency and WrLatency does error checking against spec valid values.

  @param[in]      MrcData         - Pointer to MRC global data.
  @param[in]      SdramWidth      - LPDDR4 device width (8 or 16)
  @param[in]      RdLatency       - Read Latency Value.  Function will convert to encoding.
  @param[in]      Wrlatency       - Write Latency Value.  Function will convert to encoding.
  @param[in]      WrLatencySet    - Switch to select between Set A and Set B of Write Latency delays.
  @param[in]      WrLevelingMode  - Switch to enable JEDEC Write Leveling mode.
  @param[in,out]  MrData          - Pointer to MR data to update.

  @retval MrcStatus - mrcWrongInputParameter or mrcSuccess.
**/
MrcStatus
MrcLpddr4SetMr2 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 SdramWidth,
  IN      UINT16                RdLatency,
  IN      UINT16                WrLatency,
  IN      UINT8                 WrLatencySet,
  IN      UINT8                 WrLevelingMode,
  IN OUT  UINT16                *MrData
  );

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARGx is passed in, that parameter is ignored.
  PdDrvStr does error checking against spec valid values.

  @param[in]      MrcData     - Pointer to global MRC data.
  @param[in]      PuCalPoint  - Pull Up Calibration Point.
  @param[in]      PdDrvStr    - Pull Down Drive Strength value to set (in Ohms).  Does not support infinity (0xFFFF) as RFU.
  @param[in,out]  MrData      - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr3 (
  IN  MrcParameters *const  MrcData,
  IN      UINT8             PuCalPoint,
  IN      UINT16            PdDrvStr,
  IN OUT  UINT16    *const  MrData
  );

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  DqOdt and CaOdt does error checking against spec valid values.

  @param[in]      MrcData - Pointer to global MRC data.
  @param[in]      DqOdt   - Data ODT value to set (in Ohms).
  @param[in]      CaOdt   - Command/Address ODT value to set (in Ohms).
  @param[in,out]  MrData  - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr11 (
  IN      MrcParameters *const  MrcData,
  IN      UINT16                DqOdt,
  IN      UINT16                CaOdt,
  IN OUT  UINT16        *const  MrData
  );

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only CaVref does error checking against spec valid values.

  @param[in]      MrcData     - Pointer to global MRC data.
  @param[in]      CaVref      - Command/Address Vref to set (JEDEC Encoding).
  @param[in]      CaVrefRange - Command/Address Vref range selector.
  @param[in]      CaCbtMode   - Command/Address CBT training mode.
  @param[in,out]  MrData      - Pointer to MR data to update.

  @retval MrcStatus - mrcWrongInputParameter if CaVref is invalid, else mrcSuccess.
**/
MrcStatus
MrcLpddr4SetMr12 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 CaVref,
  IN      UINT8                 CaVrefRange,
  IN      UINT8                 CaCbtMode,
  IN OUT  UINT16        *const  MrData
  );

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.

  @param[in]      MrcData         - Pointer to global MRC data.
  @param[in]      CbtMode         - Command Bus Training mode switch.
  @param[in]      RptMode         - Read Preamble Training mode switch.
  @param[in]      VrcgMode        - VREF Current Generator mode switch.
  @param[in]      DataMaskDisable - Data Mask Operation switch.
  @param[in]      FspWrite        - Frequency Set Point write enable switch.
  @param[in]      FspOpMode       - Frequency Set Point Operation Mode switch.
  @param[in,out]  MrData          - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr13 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 CbtMode,
  IN      UINT8                 RptMode,
  IN      UINT8                 VrcgMode,
  IN      UINT8                 DataMaskDisable,
  IN      UINT8                 FspWrite,
  IN      UINT8                 FspOpMode,
  IN OUT  UINT16        *const  MrData
  );

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only DqVref does error checking against spec valid values.

  @param[in]      MrcData     - Pointer to global MRC data.
  @param[in]      DqVref      - Data Vref to set (JEDEC Encoding).
  @param[in]      DqVrefRange - Data Vref range selector.
  @param[in,out]  MrData      - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr14 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 DqVref,
  IN      UINT8                 DqVrefRange,
  IN OUT  UINT16        *const  MrData
  );

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  Only SocOdt does error checking against spec valid values.

  @param[in]      MrcData - Pointer to global MRC data.
  @param[in]      SocOdt  - SOC ODT value to set (in Ohms).
  @param[in]      CkOdtEn - Clock ODT enabled for non-terminating rank.
  @param[in]      CsOdtEn - Chip Select ODT enable for non-terminating rank.
  @param[in]      CaOdtEn - Command/Address ODT termination disable.
  @param[in,out]  MrData  - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr22 (
  IN      MrcParameters *const  MrcData,
  IN      UINT16                SocOdt,
  IN      UINT8                 CkOdtEn,
  IN      UINT8                 CsOdtEn,
  IN      UINT8                 CaOdtEn,
  IN OUT  UINT16        *const  MrData
  );

/**
  This function will set up the pointer passed in based on LPDDR4 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.

  @param[in]      MrcData       - Pointer to global MRC data.
  @param[in]      DqioDuration  - DQS interval timer run time.
  @param[in,out]  MrData        - Pointer to MR data to update.

  @retval MrcStatus - mrcSuccess if the value is supported, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr4SetMr23 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 DqioDuration,
  IN OUT  UINT16        *const  MrData
  );

  /**
  Program LPDDR4 FSP-OP and FSP-WR values.

  @param[in]  MrcData     - Pointer to MRC global data.
  @param[in]  ChMask      - Bit mask of Channel's to configure.
  @param[in]  SubChMask   - Bit mask of Sub Channel's to configure.
  @param[in]  RankMask    - Bit mask of Rank's to configure.
  @param[in]  VrcgMode    - VREF Current Generator mode switch.
  @param[in]  FspWePoint  - FSP-WR value in MR13[6]
  @param[in]  FspOpPoint  - FSP-OP value in MR13[7]

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
Lpddr4SetFsp (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 ChMask,
  IN  UINT8                 SubChMask,
  IN  UINT8                 RankMask,
  IN  UINT8                 VrcgMode,
  IN  UINT8                 FspWePoint,
  IN  UINT8                 FspOpPoint
  );

/**
  This function searches the list of valid ODT encodings for LPDDR4 to find the closest matching
  ODT.  The SOC ODT and the SOC_ODT programming to the LPDDR4 MR must match or unexpected behavior
  may occur.  It will return this value to the caller.

  @param[in]  MrcData - Pointer to the global MRC data
  @param[in]  SocOdt  - The ODT requested by the system

  @retval - Closest matching ODT value.
**/
UINT16
MrcCheckSocOdtLpddr4 (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                SocOdt
  );

/**
  This function will return the requested ODTL timing value (On/OFF).

  @param[in]  Frequency - Integer based number representing the frequency.
  @param[in]  WlSet     - The current Write Latency set used.
  @param[in]  OdtlParam - Specifies which value of ODTL to return: On or Off (LPDDR4_ODTL_PARAM).

  @retval UINT8 The timing value in DCLK's.  0 If it is unsupported/undefined.
**/
UINT8
MrcGetOdtlTimingLpddr4 (
  IN  UINT32                Frequency,
  IN  LPDDR4_WR_LATENCY_SET WlSet,
  IN  LPDDR4_ODTL_PARAM     OdtlParam
  );

/**
  Issue LPDDR4 MPC command using MRH (Mode Register Handler).

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - The channel to work on
  @param[in] SubChannel - The sub-channel to work on
  @param[in] Rank       - The rank to work on
  @param[in] Address    - MPC address
  @param[in] Data       - MPC Data
  @param[in] DebugPrint - When TRUE, will print debugging information

  @retval mrcSuccess    - MPC was sent successfully
  @retval mrcDeviceBusy - Timed out waiting for MRH
**/
MrcStatus
MrcIssueMpc (
  IN MrcParameters *const MrcData,
  IN UINT32               Channel,
  IN UINT32               SubChannel,
  IN UINT32               Rank,
  IN UINT32               Address,
  IN UINT32               Data,
  IN BOOLEAN              DebugPrint
  );

/**
  This function will issue the JEDEC init MR sequence for LPDDR4.
  If RestoreMRs is set, the sequence will issued the MR values saved in
  the MRC global data.  Otherwise, an initial value is used.
  MR order:
    MR1, MR2, MR3, MR11, MR12, MR13, MR14, MR22, MR23, ZQ Start, ZQ Latch.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcJedecInitLpddr4 (
  IN  MrcParameters *const  MrcData
  );

/**
  Switch LPDDR4 to high operating frequency:
   - Set FSP_OP = 1
   - Lock MC PLL at high frequency

  @param[in] MrcData    - Pointer to MRC global data.
  @param[in] DebugPrint - Enable/disable debug printing

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcLpddr4SwitchToHigh (
  IN  MrcParameters *const  MrcData,
  IN BOOLEAN                DebugPrint
  );

/**
  This function performs the reset sequence required by JEDEC spec for LPDDR4.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcJedecResetLpddr4 (
  IN  MrcParameters *const  MrcData
  );

/**
  This function converts from MRC training index to DRAM Vref encoding:
    Offset [-40:-11]  - Range 0 Vref 0 - 29 (10% - 21.6%).
    Offset [-10:40]   - Range 1 Vref 0 - 50 (22% - 42%).

  @param[in]  MrcData - Include all MRC global data.
  @param[in]  Offset  - Training index to convert.
  @param[out] Vref    - Pointer to return the Vref MR encoding.
  @param[out] Range   - Pointer to return the Vref range.

  @retval mrcSuccess              Input parameters are valid (LPDDR4 Spec).
  @retval mrcWrongInputParameter  Input parameters are invalid (LPDDR4 Spec).
**/
MrcStatus
MrcOffsetToVrefLpddr4 (
  IN  MrcParameters *const  MrcData,
  IN  INT32                 Offset,
  OUT UINT8                 *Range,
  OUT UINT8                 *Vref
  );

/**
  This function converts the Vref number in millivolts to the MRC training offset.
  This function will return the closest training offset.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  VrefMv  - Request Vref in millivolts.
  @param[out] Offset  - Pointer to return training index.

  @retval mrcSuccess              Input parameters are valid.
  @retval mrcWrongInputParameter  Input parameters are invalid.
**/
MrcStatus
MrcVrefToOffsetLpddr4 (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                VrefMv,
  OUT INT32                 *Offset
  );

/**
  This function converts from DRAM Vref encoding to MRC training offset:
    Range 0 Vref [0:29] (10% - 21.6%) - Offset [-40:-11].
    Range 1 Vref [0:50] (22% - 42%)   - [-10:40].

  @param[in]  MrcData - Include all MRC global data.
  @param[in]  Vref    - Vref MR encoding.
  @param[in]  Range   - Vref range.  Only 0 and 1 are valid.
  @param[out] Offset  - Pointer to return training index.

  @retval mrcSuccess              Input parameters are valid (LPDDR4 Spec).
  @retval mrcWrongInputParameter  Input parameters are invalid (LPDDR4 Spec).
**/
MrcStatus
MrcVrefEncToOffsetLpddr4 (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 Vref,
  IN  UINT8                 Range,
  OUT INT32                 *Offset
  );

/**
  Set Tx and CA DIMM Vref absolute Value for LDDR4.
  Use custom MRC range [-40:+40] (110mV:462mV) where zero offset is 286mV
  and step is 4.4mV (JEDEC spec).

  51 indexes (-10:40) on Range 1 (22% - 42%).  30 indexes (-40:-11) on Range 0 (10% - 21.6%).

  @param[in]      MrcData       - Include all MRC global data.
  @param[in]      VrefType      - The type of Vref to set
  @param[in]      Channel       - Channel to program.
  @param[in]      Rank          - Selecting which Rank to talk to.
  @param[in]      Offset        - Vref Offset to program.
  @param[in]      UpdateMrcData - Update MRC host struct.

  @retval mrcSuccess -  Within programmable range.
  @retval mrcWrongInputParameter  - Not in programmable range.
  @retval mrcDeviceBusy - MRH could not complete MR write.
**/
MrcStatus
MrcSetVrefLpddr4 (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 VrefType,
  IN  UINT8                 Channel,
  IN  UINT8                 Rank,
  IN  INT32                 Offset,
  IN  BOOLEAN               UpdateMrcData
  );

/**
  This function selects the ODT table according to the board type.

  @param[in] MrcData         - Include all the MRC general data.
  @param[in] Dimm            - selected DIMM.
  @param[in] OdtIndex        - selected ODT index.

  @retval TOdtValueLpddr4 * - Pointer to the relevant table or NULL if the table was not found.
**/
TOdtValueLpddr4 *
SelectTable_LPDDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          Dimm,
  IN const TOdtIndex      OdtIndex
  );

/**
  Lpddr4 Set DimmParamValue is responsible for performing the concrete set DIMM paramter to value,
  using Lpddr4 specific MR set functions.
  Parameters supported: OptDimmRon, OptDimmOdtWr

  @param[in,out]  MrcData         - Include all MRC global data.
  @param[in,out]  MrData          - Pointer to the MR data to update.
  @param[in]      OptParam        - The Dimm Opt Param (e.g., OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom)
  @param[in]      ParamValue      - The actual values (Typically in Ohms)

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam
                    - MrcStatus of the MR set functions otherwise

**/
MrcStatus
Lpddr4SetDimmParamValue (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT16        *const MrData,
  IN     UINT8                OptParam,
  IN     UINT16               ParamValue
  );

/**
  Lppdr4 Get the MR value and its corresponding index for a given DIMM Opt Param.
  Value is set by reference to the corresponding pointers.

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      OptParam    - The Dimm Opt Param (e.g., OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom)
  @param[out]     *MrIndex    - Updated Pointer to the MR index.
  @param[out]     *MrNum      - Updated Pointer to the MR number.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam,
                      mrcSuccess             otherwise
**/
MrcStatus
Lpddr4GetOptDimmParamMrIndex (
  IN MrcParameters *const MrcData,
  IN UINT8                OptDimmParam,
  OUT UINT8               *MrIndex,
  OUT UINT8               *MrNum
  );

/**
  This function configures MR22 on FSP 0 and FSP 1 to the same value.

  @param[in] MrcData - Pointer to global MRC data.

  @retval Nothing.
**/
MrcStatus
Lpddr4FspSetStaticMrs (
  IN MrcParameters *const MrcData
  );

/**
  LPDDR4 get available values and the number of possible values of a given DimmOptParam.

  @param[in]      MrcData               - Include all MRC global data.
  @param[in]      DimmOptParam          - e.g., OptDimmOdtWr, OptDimmOdtNom, OptDimmOdtPark, OptDimmRon
  @param[out]     **DimmOptParamVals    - Reference to the pointer of values.
  @param[out]     *NumDimmOptParamVals  - Reference to the number of values.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam
                      mrcSuccess             otherwise
**/
MrcStatus
Lpddr4GetDimmOptParamValues (
  IN MrcParameters *const MrcData,
  IN UINT8                DimmOptParam,
  OUT UINT16              **DimmOptParamVals,
  OUT UINT8               *NumDimmOptParamVals
  );

/**
  Used to update TxVref and CaVref for LPDDR4.
  Uses input offset value to increment/decrement current setting.

  @param[in,out] MrcData       - Include all MRC global data.
  @param[in]     Channel       - Selecting which Channel to talk to.
  @param[in]     RankMask      - Selecting which Ranks to talk to.
  @param[in]     VrefType      - Determines the Vref type to change, only CmdV and TxVref are valid.
  @param[in]     Offset        - Vref offset value.
  @param[in]     UpdateMrcData - Used to decide if Mrc host must be updated.
  @param[in]     IsCachedOffsetParam - Determines if the paramter is an offset (relative to cache) or absolute value.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam,  mrcSuccess otherwise
**/
MrcStatus
Lpddr4SetDramVref (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                RankMask,
  IN     UINT8                VrefType,
  IN     INT32                Offset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              IsCachedOffsetParam
  );
#endif // _MRC_LPDDR_4_H_


/** @file
  Implementation of LPDDR5 Specific functions, and constants.

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
  JEDEC
**/

#ifndef _MRC_LPDDR5_H_
#define _MRC_LPDDR5_H_

///
/// Multi-Purpose Commands (MPC)
///
#define MRC_LP5_MPC_START_WCK2DQI_OSC (0x81)

///
/// Timings
///
///  Precharge to Precharge Delay for all Frequencies in tCK
#define MRC_LP5_tPPD_ALL_FREQ (2)

/*
  tWCK2CK
  MR18 Op[5]  Min   Max
  0 (4:1)     -.5   .5
  1 (2:1)     -.25  .25
*/

/// WCKDQO (pS)
#define MRC_LP5_tWCKDQO_MIN (650)
#define MRC_LP5_tWCKDQO_MAX (1600)

/// WCKDQI (pS)
#define MRC_LP5_tWCKDQI_MIN (300)
#define MRC_LP5_tWCKDQI_MAX (800)

/// tODT On Off (pS)
#define MRC_LP5_tODT_ON_OFF_MIN (1500)
#define MRC_LP5_tODT_ON_OFF_MAX (3500)

/// tFC_Long = 250ns
#define MRC_LP5_tFC_LONG_NS (250)

/// Minimum interval between PDE and PDX or between PDX and PDE (tCSPD) fS
#define MRC_LP5_tCSPD_MIN           (7500000)
#define MRC_LP5_tCSPD_MIN_NCK       (3)

/// Delay from valid command to PDE (tCMDPD) pS
#define MRC_LP5_tCMDPD_MIN          (1750)
#define MRC_LP5_tCMDPD_MIN_NCK      (2)

/// Valid Clock Requirement after PDE (tCSLCK) pS
#define MRC_LP5_tCSCLK_MIN          (5000)
#define MRC_LP5_tCSCLK_MIN_NCK      (3)

/// Valid Clock Requirement for PDX (tCKCSH) pS
#define MRC_LP5_tCKCSH_MIN          (1750)
#define MRC_LP5_tCKCSH_MIN_NCK      (2)

/// Exit from Power-Down to next valid command delay (tXP) fS
#define MRC_LP5_tXP_MIN             (7500000)
#define MRC_LP5_tXP_MIN_NCK         (3)

/// Minimum CS High Pulse width at PDX (tCSH) pS
#define MRC_LP5_tCSH_MIN            (3000)

/// Minimum CS Low Duration time at PDX (tCSL) pS
#define MRC_LP5_tCSL_MIN            (4000)

/// Delay from MRW command to PDE (tMRWPD) pS
#define MRC_LP5_tMRWPD_MIN          (14000)
#define MRC_LP5_tMRWPD_MIN_NCK      (6)

/// Delay from ZQ Calibration Start Command to PDE (tZQPD) pS
#define MRC_LP5_tZQPD_MIN           (1750)
#define MRC_LP5_tZQPD_MIN_NCK       (2)

/// Valid CA LOW requirement before CS change Low to High (tCA2CS_PRE) pS
#define MRC_LP5_tCA2CS_PRE_MIN      (1750)
#define MRC_LP5_tCA2CS_PRE_MIN_NCK  (2)

/// ECT Timing parameters in pS
#define MRC_LP5_tWCK2DQ7H_PS        (5000)
#define MRC_LP5_tDQ7HWCK_PS         (5000)
#define MRC_LP5_tDQ7HCK_PS          (5000)
#define MRC_LP5_tADR_PS             (20000)
#define MRC_LP5_tDQ7LWCK_PS         (5000)
#define MRC_LP5_tVREFCA_LONG_PS     (250000)

/// tVRCG_DISABLE = 100ns
#define MRC_LP5_tVRCG_DISABLE_NS    (100)

/// tVRCG_ENABLE = 150ns
#define MRC_LP5_tVRCG_ENABLE_NS     (150)

///
/// Vref related defines
///
#define LP5_VREF_OFFSET_MIN     (-58)     ///< Minimum possible Vref offset for Write/Command Vref
#define LP5_VREF_OFFSET_MAX     (58)      ///< Maximum possible Vref offset for Write/Command Vref
#define LP5_VREF_MIN_MV         (75)      ///< mV
#define LP5_CA_VREF_MAX         (350)     ///< mV
#define LP5_DQ_VREF_LOW_F_MAX   (350)     ///< mV
#define LP5_DQ_VREF_HIGH_F_MAX  (225)     ///< mV
#define LP5_VREF_MIN_UV         (75000)   ///< uV
#define LP5_VREF_MAX            (375000)  ///< uV
#define LP5_VREF_STEP_SIZE      (2500)    ///< uV

/**
  This function selects the ODT table according to the board type.

  @param[in] MrcData  - Include all the MRC general data.
  @param[in] Dimm     - selected DIMM.
  @param[in] OdtIndex - selected ODT index.

  @retval TOdtValueLpddr * - Pointer to the relevant table or NULL if the table was not found.
**/
TOdtValueLpddr *
SelectTable_LPDDR5 (
  IN MrcParameters *const MrcData,
  IN const UINT32         Dimm,
  IN const TOdtIndex      OdtIndex
  );

///
/// External functions
///
/**
  This function returns the impact to Write Latency for the requested LPDDR_ODTL_PARAM.
  Only supports BL32 8-Bank mode.

  @param[in]  Frequency - Data Rate.
  @param[in]  OdtlParam - Select between On or Off timing.

  @retval INT8 - Timing impact.
**/
INT8
MrcGetWrOdtlLpddr5 (
  IN  MrcFrequency      Frequency,
  IN  LPDDR_ODTL_PARAM  OdtlParam
  );

/**
  This function returns the impact to Read Latency for Non-target ODT of the requested LPDDR_ODTL_PARAM.
  Only supports BL32 8-Bank mode.

  @param[in]  Frequency - Data Rate.
  @param[in]  OdtlParam - Select between On or Off timing.

  @retval INT8 - Timing impact.
**/
INT8
MrcGetNtRdOdtlLpddr5 (
  IN  MrcFrequency      Frequency,
  IN  LPDDR_ODTL_PARAM  OdtlParam
  );

/**
  This function returns tWCKPRE_Static for both Writes and Reads in 4:1 mode.
  The implementation is based off of Table 26/27 WCK2CK Sync AC Parameters for Write/Read Operation

  @param[in]  Frequency - Data Rate.

  @retval INT8 - Timing in tCK
**/
INT8
MrcGetWckPreStaticLpddr5 (
  IN  MrcFrequency  Frequency
  );

/**
  This function returns tWCKENL_FS in 4:1 mode.
  The implementation si based off of Table 28 WCK2CK Sync AC Paramters for CAS(WS_FAST)

  @param[in]  Frequency - Data Rate.

  @retval UINT8 - Timing in tCK
**/
UINT8
MrcGetWckEnlFsLpddr5 (
  IN  MrcFrequency  Frequency
  );

/**
  This function returns tWCKPRE_total_WR.
  The implementation is based off of Table 26 WCK2CK Sync AC Parameters for Write Operation

  @param[in]  Frequency - Data rate.

  @retval UINT8 - Timing in tCK.
**/
UINT8
MrcGetWckPreWrTotalLpddr5 (
  IN  MrcFrequency  Frequency
  );

/**
  This function returns tWCKPRE_total_RD for SetA or SetB.
  This function assumes DVFSC is disabled and DBI is off.
  The implementation is based off of Table 27 WCK2CK Sync AC Parameters for Read Operation.

  @param[in]  Frequency - Data rate.

  @retval UINT8 - Timing in tCK.
**/
INT8
MrcGetWckPreRdTotalLpddr5 (
  IN  MrcFrequency  Frequency
  );

/**
  This function will issue the JEDEC init MR sequence for LPDDR5.
  If RestoreMRs is set, the sequence will use the MR values saved in
  the MRC global data.  Otherwise, an initial value is used.
  Flow:
   1. Set Low frequency (1100)
   2. Send FSP-OP[0] MR2 to program RL of the high frequency
     - This is needed for DQ mapping step of ECT
   3. Set FSP-WR = 1, FSP-OP = 0
   4. Send all MRs
   5. If ECT_Done
     a. Set High frequency
     b. Set FSP-OP = 1

  @param[in]  MrcData - Pointer to MRC global data.

  @retval MrcStatus - mrcSuccess if successful, else an error status.
**/
MrcStatus
MrcJedecInitLpddr5 (
  IN  MrcParameters *const  MrcData
  );


/**
  This function will set up the pointer passed in based on LPDDR5 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.
  @param[in]      MrcData         - Pointer to global MRC data.
  @param[in]      CbtMode         - Command Bus Training mode switch.
  @param[in,out]  MrData          - Pointer to MR data to update.
  @retval MrcStatus - mrcSuccess if a supported ODT value, else mrcWrongInputParameter.
**/
MrcStatus
MrcLpddr5SetMr13 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 CbtMode,
  IN OUT  UINT16        *const  MrData
  );

/**
  This function will set up the pointer passed in based on LPDDR5 Mode Register definition.
  If MRC_IGNORE_ARG8 is passed in, that parameter is ignored.

  @param[in]      MrcData   - Pointer to global MRC data.
  @param[in]      FspWrite  - Frequency Set Point write enable switch.
  @param[in]      FspOpMode - Frequency Set Point Operation Mode switch.
  @param[in]      CbtMode   - Command Bus Training mode switch.
  @param[in]      VrcgMode  - VREF Current Generator mode switch.
  @param[in]      CbtPhase  - Controls which phase of the clock the CA pattern is latched.
  @param[in,out]  MrData    - Pointer to MR data to update.
**/
MrcStatus
MrcLpddr5SetMr16 (
  IN      MrcParameters *const  MrcData,
  IN      UINT8                 FspWrite,
  IN      UINT8                 FspOpMode,
  IN      UINT8                 CbtMode,
  IN      UINT8                 VrcgMode,
  IN      UINT8                 CbtPhase,
  IN OUT  UINT16        *const  MrData
  );

/**
  This function will drive DQ7 for LP5 ECT so that DRAM can switch from FSP0 to FSP1.

  @param[in]      MrcData   - Pointer to global MRC data.
  @param[in]      DQ7Value    Value of DQ7 pin
  @param[in]      WckControlSave Save the previous value for WckControl register
  @param[in]      MiscControl7Save Save the previous value for MiscControl7 register
  **/
VOID
MrcDriveDq7 (
  IN MrcParameters *const  MrcData,
  IN     UINT8             Dq7Value,
  IN OUT UINT32    *const  WckControlSave,
  IN OUT UINT32    *const  MiscControl7Save
  );

/**
  This function will set Rcomp for DQ to look like they are in RX mode.

  @param[in]      MrcData   - Pointer to global MRC data.
  @param[in]      Set         To set Rcomp values for RX mode
  @param[in]      DataRcompDataSave Save the phyinit value for RcompData register
  **/
VOID
MrcSetRcompData (
  IN      MrcParameters *const MrcData,
  IN      BOOLEAN              Set,
  IN OUT  UINT32               DataRcompDataSave [MAX_CONTROLLER][MAX_SDRAM_IN_DIMM]
  );

/**
  This function converts from DRAM Vref encoding to MRC training offset:
  Vref [0:127] - Offset [10:117] :: LP5 (15% - 73.5%) * 500mV.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Vref    - Vref MR encoding.
  @param[out] Offset  - Pointer to return training index.

  @retval mrcSuccess              Input parameters are valid (LPDDR5 Spec).
  @retval mrcWrongInputParameter  Input parameters are invalid (LPDDR5 Spec).
**/
MrcStatus
MrcVrefEncToOffsetLpddr5 (
  IN  MrcParameters *const  MrcData,
  IN  UINT8                 Vref,
  OUT INT32                 *Offset
);

/**
  Used to update TxVref and CaVref for LPDDR5.
  Uses input offset value to increment/decrement current setting.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in,out] Controller     - Selecting which Controller to talk to.
  @param[in]     Channel        - Selecting which Channel to talk to.
  @param[in]     RankMask       - Selecting which Ranks to talk to.
  @param[in]     VrefType       - Determines the Vref type to change, only CmdV and TxVref are valid.
  @param[in]     Offset         - Vref offset value.
  @param[in]     UpdateMrcData  - Used to decide if Mrc host must be updated.
  @param[in]     IsCachedOffsetParam - Determines if the paramter is an offset (relative to cache) or absolute value.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam,  mrcSuccess otherwise
**/
MrcStatus
Lpddr5SetDramVref (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Controller,
  IN     UINT8                Channel,
  IN     UINT8                RankMask,
  IN     UINT8                VrefType,
  IN     INT32                Offset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              IsCachedOffsetParam
  );

#endif // _MRC_LPDDR5_H_

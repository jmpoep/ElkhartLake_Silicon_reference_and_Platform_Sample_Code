/** @file
  Definition of DDR4 Specific functions, constants, defines,
  and data structures.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#ifndef _MRC_DDR_4_H_
#define _MRC_DDR_4_H_

#include "MrcApi.h"
#include "MrcDdr4Registers.h"
#include "MrcCommon.h"

///
/// Timings
///
#define TRPRE_ALL_FREQ      (1) ///< tRPRE is = 1 tCK for all frequencies up to 1600.

typedef struct {
  UINT16  RttWr;   ///< Wa - Write ODT on active rank
  UINT16  RttNom;  ///< Wp - ODT on one of the ranks on passive DIMM during Write operation
  UINT16  RttPark;
} TOdtValueDdr4;

typedef enum {
  DDR4_ODIC_34,     // 0 - RZQ/7 = 34 Ohm
  DDR4_ODIC_48,     // 1 - RZQ/5 = 48 Ohm
  DDR4_ODIC_RSVD_0, // 2 - Reserved
  DDR4_ODIC_RSVD_1  // 3 - Reserved
} OutputDriverImpedanceControlDdr4;

/**
  Used to update TxVref for DDR4.
  Uses input offset value to increment/decrement current setting.

  @param[in,out] MrcData        - Include all MRC global data.
  @param[in]     Controller     - Selecting which Memory Controller to talk to.
  @param[in]     Channel        - Selecting which Channel to talk to.
  @param[in]     RankMask       - Selecting which Ranks to talk to.
  @param[in]     DeviceMask     - Selecting which Devices to talk to (only valid for DDR4 and adjusting VrefDQ).
  @param[in]     VrefType       - Determines the Vref type to change, only TxVref is valid.
  @param[in]     Offset         - Vref offset value.
  @param[in]     UpdateMrcData  - Used to decide if Mrc host must be updated.
  @param[in]     PdaMode        - Selecting to use MRH or old method for MRS (only valid for DDR4 and adjusting VrefDQ).
  @param[in]     IsCachedOffset - Determines if the paramter is an offset (relative to cache) or absolute value.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam,  mrcSuccess otherwise.
**/
MrcStatus
Ddr4SetDramVref (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Controller,
  IN     UINT8                Channel,
  IN     UINT8                RankMask,
  IN     UINT16               DeviceMask,
  IN     UINT8                VrefType,
  IN     INT32                Offset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              PdaMode,
  IN     BOOLEAN              IsCachedOffset
  );

/**
  Set Tx Dimm Vref absolute Value for DDR4.
  Use custom MRC range [-36:+37] where zero offset is 820mV and step is 7.8mV (JEDEC spec).

  @param[in, out] MrcData       - Include all MRC global data.
  @param[in]      Controller    - Memory Controller Number within the processor (0-based).
  @param[in]      Channel       - Selecting which Channel to talk to
  @param[in]      Rank          - Selecting which Rank to talk to
  @param[in]      Device        - Selecting which Device to talk to (only valid when PDAmode is TRUE)
  @param[in]      TxVrefOffset  - TxVref Offset to set
  @param[in]      UpdateMrcData - update MRC host struct
  @param[in]      PdaMode       - Selecting to use MRH or old method for MRS

  @retval Nothing
**/
extern
void
MrcSetTxVrefDdr4 (
  IN OUT MrcParameters *const MrcData,
  IN     UINT32               Controller,
  IN     UINT8                Channel,
  IN     UINT8                Rank,
  IN     UINT8                Device,
  IN     INT32                TxVrefOffset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              PdaMode
  );


/**
  This function Update the Non PDA DDR4 Vref to match the PDA average
  across all bytes (per rank/ch).
  This will allow the use of Non PDA sweep using GetBerMarginByte

  @param[in]     MrcData         - Include all MRC global data.
  @param[in]     Controller      - Selecting which Controller to talk to.
  @param[in]     Channel         - Selecting which Channel to talk to.
  @param[in]     RankMask        - ranks to work on

  @retval mrcWrongInputParameter if a bad Param is passed in, otherwise mrcSuccess.
**/

MrcStatus
UpdatePdaCenter (
  IN     MrcParameters *const MrcData,
  IN     const UINT8          Controller,
  IN     const UINT8          Channel,
  IN     const UINT8          Ranks
  );


/**
  Ddr4 get available values and the number of possible values of a given DimmOptParam.

  @param[in]      MrcData               - Include all MRC global data.
  @param[in]      DimmOptParam          - e.g., OptDimmOdtWr, OptDimmOdtNom, OptDimmOdtPark, OptDimmRon
  @param[out]     **DimmOptParamVals    - Pointer to the pointer of values.
  @param[out]     *NumDimmOptParamVals  - Pointer to the number of values.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam
                      mrcSuccess             otherwise
**/
MrcStatus
Ddr4GetDimmOptParamValues (
  IN MrcParameters *const MrcData,
  IN UINT8                DimmOptParam,
  OUT UINT16              **DimmOptParamVals,
  OUT UINT8               *NumDimmOptParamVals
  );

/**
  Ddr4 Get the MR value and its corresponding index for a given DIMM Opt Param.
  Value is set by reference to the corresponding pointers.

  @param[in]      MrcData     - Include all MRC global data.
  @param[in]      OptParam    - The Dimm Opt Param (e.g., OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom)
  @param[out]     *MrIndex    - Updated Pointer to the MR index.
  @param[out]     *MrNum      - Updated Pointer to the MR number.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam
                      mrcSuccess             otherwise
**/
MrcStatus
Ddr4GetOptDimmParamMrIndex (
  IN MrcParameters *const MrcData,
  IN UINT8                OptDimmParam,
  OUT UINT8               *MrIndex,
  OUT UINT8               *MrNum
);

/**
  Ddr4 Set DimmParamValue is responsible for performing the concrete DDR4 specific  set DIMM parameter
  to value, using LPDDR3 MR set functions.

  @param[in,out]  MrcData         - Include all MRC global data.
  @param[in,out]  MrData          - Pointer to the MR data to update.
  @param[in]      OptParam        - The Dimm Opt Param (e.g., OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom)
  @param[in]      ParamValue      - The actual values (Typically in Ohms)

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam
                                             otherwise the MrcStatus of the MR set functions
**/
MrcStatus
Ddr4SetDimmParamValue (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT16        *const MrData,
  IN     UINT8                OptParam,
  IN     UINT16               ParamValue
  );

/**
  Perform JEDEC Init sequence for DDR4.

  @param[in] MrcData - Pointer to MRC global data.

  @retval MrcStatus
**/
MrcStatus
MrcJedecInitDdr4 (
  IN MrcParameters *const MrcData
  );

/**
  Perform JEDEC reset sequence for DDR4.

  @param[in] MrcData - Include all MRC global data.

  @retval - none
**/
extern
void
MrcJedecResetDdr4 (
  IN MrcParameters *const MrcData
  );

/**
  Offset to DDR4 VrefDQ Range/Value (MR6)

  @param[in] MrcData         - Include all MRC global data.
  @param[in] Offset          - Offset value

  @retval DDR4 VrefDQ Range/Value
**/
UINT8
MrcOffsetToVrefDqDdr4 (
  IN MrcParameters *const MrcData,
  IN INT32                Offset
  );

/**
  DDR4 VrefDQ Range/Value (MR6) to Offset

  @param[in] VrefDQ          - MR6 Bits A6:A0(Bit6 Range, Bit5:0 Value)

  @retval Offset
**/
INT32
MrcVrefDqToOffsetDdr4 (
  IN UINT8                VrefDQ
  );


/**
  Maps the bytes to their corresponding device

  @param[in] MrcData         - Include all the MRC general data.

  @retval mrcSuccess if successful or some type of failure due to checks
**/
MrcStatus
MrcDdr4DeviceMap (
  IN MrcParameters *const MrcData
  );

/**
  This function writes the MR0 register for all the ranks

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      BurstLength     - Burst length bit A0-A1
  @param[in]      ReadBurstType   - Read burst type bit A3
  @param[in]      TestMode        - Test mode type bit A7
  @param[in]      DllReset        - DLL reset bit A8

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR0_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          BurstLength,
  IN     const UINT8          ReadBurstType,
  IN     const UINT8          TestMode,
  IN     const UINT8          DllReset
  );

/**
  This function writes the MR1 register for all the ranks and channels

  @param[in, out] MrcData         - include all the MRC data
  @param[in]      DLLEnable       - DLL enable bit A0
  @param[in]      Odic            - Output driver impedance in Ohms
  @param[in]      AdditiveLatency - Additive latency bit A3-A4
  @param[in]      WlEnable        - Write leveling enable bit A7
  @param[in]      Qoff            - Qoff bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR1_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          DLLEnable,
  IN     const UINT8          Odic,
  IN     const UINT8          AdditiveLatency,
  IN     const UINT8          WlEnable,
  IN     const UINT8          Qoff
  );

/**
  This function writes the MR2 register for all the ranks and channels

  @param[in, out] MrcData    - general data
  @param[in]      WriteCRC   - Write CRC Enable bit (A12)

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR2_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT8          WriteCRC
  );

/**
  This function writes the MR3 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] MprPage         - MPR Page Selection bit A0-A1
  @param[in] MprOper         - MPR Operation bit A2
  @param[in] MprReadFormat   - MPR Read Format bit A11-A12
  @param[in] Geardown        - Geardown Mode bit A3
  @param[in] PDA             - Per DRAM Addressability bit A4
  @param[in] TempSensor      - Temperature Sensor Readout bit A5
  @param[in] RefreshRate     - Fine Granularity Refresh Mode bit A6-A8
  @param[in] WriteCMDLatency - Write CMD Latency when DM are enabled bit A9-A10

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR3_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          MprPage,
  IN const UINT8          MprOper,
  IN const UINT8          MprReadFormat,
  IN const UINT8          Geardown,
  IN const UINT8          PDA,
  IN const UINT8          TempSensor,
  IN const UINT8          RefreshRate,
  IN const UINT8          WriteCMDLatency
  );

/**
  This function writes the MR4 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] MaxPDMode       - Maximum Power Down Mode bit A1
  @param[in] TempRange       - Temperature Controlled Refresh Range bit A2
  @param[in] TempMode        - Temperature Controlled Refresh Mode bit A3
  @param[in] IntVref         - Internal Vref Monitor bit A4
  @param[in] CS2CALatency    - CS to CMD/ADDR Latency Mode (cycles) bit A6-A8
  @param[in] SelfRefAbort    - Self Refresh Abort bit A9
  @param[in] RdPreaMode      - Read Preamble Training Mode bit A10
  @param[in] RdPrea          - Read Preamble bit A11
  @param[in] WrPrea          - Write Preamble bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR4_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          MaxPDMode,
  IN const UINT8          TempRange,
  IN const UINT8          TempMode,
  IN const UINT8          IntVref,
  IN const UINT8          CS2CALatency,
  IN const UINT8          SelfRefAbort,
  IN const UINT8          RdPreaMode,
  IN const UINT8          RdPrea,
  IN const UINT8          WrPrea
  );

/**
  This function writes the MR5 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] CaParityLat     - C/A Parity Latency Mode bit A0-A2
  @param[in] CRCErrClr       - CRC Error Clear bit A3
  @param[in] CaParityErrSts  - C/A Parity Error Status bit A4
  @param[in] OdtBufferPD     - ODT Input Buffer for Power Down bit A5
  @param[in] CaParityPErr    - CA parity Persistent Error bit A9
  @param[in] DataMask        - Data Mask bit A10
  @param[in] WriteDbi        - Write DBI bit A11
  @param[in] ReadDbi         - Read DBI bit A12

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR5_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          CaParityLat,
  IN const UINT8          CRCErrClr,
  IN const UINT8          CaParityErrSts,
  IN const UINT8          OdtBufferPD,
  IN const UINT8          CaParityPErr,
  IN const UINT8          DataMask,
  IN const UINT8          WriteDbi,
  IN const UINT8          ReadDbi
  );

/**
  This function writes the MR6 register for all the ranks and channels

  @param[in] MrcData         - include all the MRC data
  @param[in] VrefDQValue     - VrefDQ Training Value bit A0-A5
  @param[in] VrefDQRange     - VrefDQ Training Range bit A6
  @param[in] VrefDQEnable    - VrefDQ Training Enable bit A7
  @param[in] TccdL           - tCCD_L bit A10-A12
  @param[in] Restore         - 1 = Restore/ 0 = No Restore

  @retval MrcStatus - mrcSuccess if passes, otherwise an error status

**/
MrcStatus
MrcSetMR6_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT8          VrefDQValue,
  IN const UINT8          VrefDQRange,
  IN const UINT8          VrefDQEnable,
  IN const UINT8          TccdL,
  IN const BOOLEAN        Restore
  );

/**
  This function updates the Rtt value in the MR2 value passed in.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt value in ohms.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister - Updated MR2 register

**/
DDR4_MODE_REGISTER_2_STRUCT
UpdateRttWrValue_DDR4 (
  MrcParameters *const        MrcData,
  const UINT16                 OdtValue,
  DDR4_MODE_REGISTER_2_STRUCT Ddr4ModeRegister
  );

/**
  This function updates the Rtt value in the MR5 value passed in.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt value in ohms.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister - Updated MR5 register

**/
DDR4_MODE_REGISTER_5_STRUCT
UpdateRttParkValue_DDR4 (
  MrcParameters *const        MrcData,
  const UINT16                OdtValue,
  DDR4_MODE_REGISTER_5_STRUCT Ddr4ModeRegister
  );

/**
  This function takes the MR1 register value and updates the odt value
  inside the register.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdtValue         - Selected odt value in ohms.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister  - Updated register

**/
DDR4_MODE_REGISTER_1_STRUCT
UpdateRttNomValue_DDR4 (
  IN MrcParameters *const        MrcData,
  IN const UINT16                OdtValue,
  IN DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister
  );

/**
  This function takes the MR1 register value and updates the ODIC (Output Driver Impedance Control)
  value inside the register.

  @param[in] MrcData          - Include all the MRC general data.
  @param[in] OdicValue        - Selected ODIC value in ohms.
  @param[in] Ddr4ModeRegister - Register to update.

  @retval Ddr4ModeRegister  - Updated register

**/
DDR4_MODE_REGISTER_1_STRUCT
UpdateOdicValue_DDR4 (
  IN MrcParameters *const        MrcData,
  IN const UINT16                OdicValue,
  IN DDR4_MODE_REGISTER_1_STRUCT Ddr4ModeRegister
  );

/**
  This function selects the ODT table according to the board type.

  @param[in] MrcData         - Include all the MRC general data.
  @param[in] Dimm            - selected DIMM.
  @param[in] OdtIndex        - selected ODT index.

  @retval TOdtValueDdr4 * - Pointer to the relevant table or NULL if the table was not found.
**/
TOdtValueDdr4 *
SelectTable_DDR4 (
  IN MrcParameters *const MrcData,
  IN const UINT32         Dimm,
  IN const TOdtIndex      OdtIndex
  );

#endif // _MRC_DDR_4_H_

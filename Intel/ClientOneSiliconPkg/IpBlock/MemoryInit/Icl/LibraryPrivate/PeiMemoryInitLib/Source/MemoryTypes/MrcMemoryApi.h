/** @file
This API provides an interface to abstract out memory protocol differences.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2017 Intel Corporation.

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
#ifndef _MRC_MEMORY_API_H_
#define _MRC_MEMORY_API_H_
///
/// Functions
///
/**
  This function will return the JEDEC parameter tDQS2DQ Min or Max based on the
  populated memory type.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  IsMin   - TRUE returns the minimum value, FALSE returns the maximum value.
  @param[out] Tdqs2dq - Returned parameter value in Femptoseconds.  If the memory technology does not suppor the parameter, 0 is returned.

  @retval MrcStatus - mrcSuccess if the API supports the memory type; mrcDimmNoSupported if the API does not support the memory type.
**/
MrcStatus
MrcGetTdqs2dq (
  IN  MrcParameters *const  MrcData,
  IN  const BOOLEAN         IsMin,
  OUT UINT32                *Tdqs2dq
  );

/**
  This function will return the center of the range of the JEDEC timing parameter tDQS2DQ based on the
  populated memory type.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[out] Tdqs2dqCenter - Returned parameter value in Femptoseconds.  If the memory technology does not suppor the parameter, 0 is returned.

  @retval MrcStatus - mrcSuccess if the API supports the memory type; mrcDimmNoSupported if the API does not support the memory type.
**/
MrcStatus
MrcGetTdqs2dqCenter (
  IN  MrcParameters *const  MrcData,
  OUT UINT32                *Tdqs2dqCenter
  );

/**
  This function will return the JEDEC parameter tDQSCK MIN based on the
  populated memory type.

  @param[in]   MrcData   - Pointer to MRC global data.
  @param[out]  TdqsCkPs  - If TdqsCk is not present on the current memory technology, 0 is returned.

  @retval MrcStatus - mrcSuccess if the memory type is supported; mrcDimmNotSupport if the memory type is not supported.
**/
MrcStatus
MrcGetTdqsckMin (
IN  MrcParameters *const  MrcData,
OUT UINT32                *TdqsCkPs
  );

/**
  This function determines if the SOC ODT requested is valid for the memory technology.
  If, the requested ODT is not supported, it will return the the closest matching ODT.
  If there is no limitation by the memory technology or the ODT value is supported,
  it will return the requested ODT.

  @param[in]  MrcData - Pointer to the global MRC data
  @param[in]  SocOdt  - The ODT requested by the system

  @retval - Valid ODT value.
**/
UINT16
MrcCheckForSocOdtEnc (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                SocOdt
  );

/**
  This function configures the DRAM final state before transitioning to Normal Mode.

  @param[in] MrcData - Pointer to global MRC data.

  @retval Nothing.
**/
VOID
MrcDramStateFinalize (
  IN  MrcParameters *const MrcData
  );

/**
  This function returns the Command/Address bus width per technology type.

  @param[in]  MrcData   - Pointer to global MRC data.
  @param[out] BusWidth  - Return variable for the bus width.  0 is return if the technolog is not supported.

  @retval MrcStatus - mrcSuccess if the memory type is supported; mrcDimmNotSupport if the memory type is not supported.
**/
MrcStatus
MrcGetCmdBusWidth (
  IN  MrcParameters *const  MrcData,
  OUT UINT8                 *BusWidth
  );

/**
  Used to update VrefDQ for DDR4/LPDDR4 or VrefCA for LPDDR4.
  Uses input offset value to increment/decrement current setting.

  @param[in,out] MrcData       - Include all MRC global data.
  @param[in]     Channel       - Selecting which Channel to talk to.
  @param[in]     RankMask      - Selecting which Ranks to talk to.
  @param[in]     DeviceMask    - Selecting which Devices to talk to (only valid for DDR4 and adjusting VrefDQ).
  @param[in]     VrefType      - Determines the Vref type to change, only CmdV and TxVref are valid.
  @param[in]     Offset        - Vref offset value.
  @param[in]     UpdateMrcData - Used to decide if Mrc host must be updated.
  @param[in]     PdaMode       - Selecting to use MRH or old method for MRS (only valid for DDR4 and adjusting VrefDQ).
  @param[in]     IsCachedOffsetParam - Determines if the paramter is an offset (relative to cache) or absolute value.

  @retval Nothing.
**/
void
MrcSetDramVref (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                RankMask,
  IN     UINT16               DeviceMask,
  IN     UINT8                VrefType,
  IN     INT32                Offset,
  IN     BOOLEAN              UpdateMrcData,
  IN     BOOLEAN              PdaMode,
  IN     BOOLEAN              IsCachedOffsetParam
  );

/**
  SetDimmParamValue is responsible for performing the concrete set DIMM parameter to value, using
  Per-Technology SetDimmParamValue functions.
  Parameters supported: OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom.
  Function performs the following stages:
  1. Reads cached value.
  2. Programs new value to cache.
  3. Programs MRs via MRH.

  Note Shadow register are defined per Channel. If there is any variation between ranks it will be lost.

  @param[in,out] MrcData    - Include all MRC global data.
  @param[in]     Channel    - Channel index to work on.
  @param[in]     Ranks      - Rank mask to be applied to.
  @param[in]     SubChMask  - Sub Channel index to work on.
  @param[in]     OptParam   - Defines the OptParam Offsets.
  @param[in]     ParamValue - The actual values (Typically in Ohms)
  @param[in]     UpdateHost - Decides if MrcData has to be updated

  @retval MrcStatus - mrcWrongInputParameter if unsupported Technology
                    - MrcStatus of the Technology specific SetDimmParamValue functions
**/
MrcStatus
SetDimmParamValue (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                Ranks,
  IN     UINT8                SubChMask,
  IN     UINT8                OptParam,
  IN     UINT16               ParamValue,
  IN     UINT8                UpdateHost
  );

/**
  GetOptDimmParamMrIndex using Technology specific GetOptDimmParamMrIndex functions

  @param[in]  MrcData     - Include all MRC global data.
  @param[in]  OptParam    - The Dimm Opt Param (e.g., OptDimmRon, OptDimmOdtWr, OptDimmOdtPark, OptDimmOdtNom)
  @param[out] *MrIndex    - Updated Pointer to the MR index.
  @param[out] *MrNum      - Updated Pointer to the MR number.

  @retval MrcStatus - mrcWrongInputParameter if unsupported Technology
                      Status of the Technology specific functions otherwise
**/
MrcStatus
GetOptDimmParamMrIndex (
  IN MrcParameters *const MrcData,
  IN UINT8                OptDimmParam,
  OUT UINT8               *MrIndex,
  OUT UINT8               *MrNum
  );

/**
  Get available values and the number of possible values of a given DimmOptParam.

  @param[in]  MrcData               - Include all MRC global data.
  @param[in]  DimmOptParam          - e.g., OptDimmOdtWr, OptDimmOdtNom, OptDimmOdtPark, OptDimmRon
  @param[out] **DimmOptParamVals    - Pointer to the pointer of values.
  @param[out] *NumDimmOptParamVals  - Pointer to the number of values.

  @retval MrcStatus - mrcWrongInputParameter if unsupported OptParam
                      mrcSuccess             otherwise
**/
MrcStatus
GetDimmOptParamValues (
  IN MrcParameters *const MrcData,
  IN UINT8                DimmOptParam,
  OUT UINT16              **DimmOptParamVals,
  OUT UINT8               *NumDimmOptParamVals
  );

/**
  Return the ODT table index for the given Channel / DIMM.

  @param[in] MrcData         - Include all the mrc global data.
  @param[in] Channel         - Channel to work on.
  @param[in] Dimm            - DIMM to work on.

  @retval Pointer to the relevant ODT structure - (TOdtValue *) or (TOdtValueDdr4 *) or (TOdtValueLpddr4 *)
**/
extern
void *
GetOdtTableIndex (
  IN MrcParameters *const MrcData,
  IN const UINT8          Channel,
  IN const UINT8          Dimm
  );
#endif // _MRC_MEMORY_API_H_

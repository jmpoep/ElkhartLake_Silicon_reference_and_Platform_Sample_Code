/** @file
  The third stage of the write training is determining the PI setting for each
  byte strobe to make sure that data is sent at the optimal location.
  In order to do that a pattern of alternating zeros and ones is written to a block of the memory, and then read out.
  By identifying the location where it is farthest away from where errors are shown the DQS will be aligned to the
  center of the eye.

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
#ifndef _MrcWriteDqDqs_h_
#define _MrcWriteDqDqs_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommandTraining.h"
#include "MrcCommon.h"
#include "MrcGlobal.h"
#include "MrcReset.h"

/**
  this function executes the write timing centering in 2D.
    Final write timing centering using 2D algorithm and per bit optimization.

    @param[in] MrcData - Include all MRC global data.

    @retval MrcStatus -  if it succeded returns mrcSuccess

  **/
extern
MrcStatus
MrcWriteTimingCentering (
  IN     MrcParameters *const MrcData
  );

/**
  this function executes the write Voltage centering (DDR4 only).
  Center Tx DQ Vref using moderate pattern with 1D eye using PDA mode.

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus      - if it succeded returns mrcSuccess
**/
extern
MrcStatus
MrcWriteVoltageCentering (
  IN     MrcParameters *const MrcData
  );

/**
  this function executes the write timing centering in 2D.
    Final write timing centering using 2D algorithm and per bit optimization.

    @param[in] MrcData - Include all MRC global data.

    @retval MrcStatus -  if it succeded returns mrcSuccess

  **/
extern
MrcStatus
MrcWriteTimingCentering2D (
  IN     MrcParameters *const MrcData
  );

/**
  Measure margins across various parameters

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  mrcSuccess if succeded
**/
extern
MrcStatus
MrcRankMarginTool (
  IN OUT MrcParameters *const MrcData
  );

/**
  Measure margins across various parameters

  @param[in, out] MrcData - Include all MRC global data.

  @retval                   -  mrcSuccess if succeeded
**/
extern
MrcStatus
MrcRankMarginToolBit (
  IN OUT MrcParameters *const MrcData
  );

/**
  this function execute the write timing centering in 2D.
  Final write timing centering using 2D algorithm and per bit optimization

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeded returns mrcSuccess
**/
/**
  Perform Read Voltage Centering in 2D.
  Note: This function currently only supports param = WrV

  @param[in, out] MrcData       - Include all MRC global data.

  @retval MrcStatus -    if it succeded return mrcSuccess
  @todo - Need option for loopcount
**/
extern
MrcStatus
MrcWriteVoltageCentering2D (
  IN OUT MrcParameters *const MrcData
  );

/**
  Perform Write Voltage Centering in 2D for DDR4.
  Note: This function currently only supports param = WrV

  @param[in, out] MrcData       - Include all MRC global data.

  @retval MrcStatus -    if it succeded return mrcSuccess
  @todo - Need option for loopcount
**/
extern
MrcStatus
MrcWriteVoltageCentering2D_DDR4 (
  IN OUT MrcParameters *const MrcData
  );

/**
  Perform Write Voltage Centering in 2D for DDR4.
  Note: This function currently only supports param = WrV

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in, out] MarginByte  - Margin results array for each byte
  @param[in]      McChBitMask - Channel bit mask.
  @param[in]      Rank        - The particular rank being centered
  @param[in]      LoopCount   - Loop counter.
  @param[in]      En2D        - Enable 2D.

  @retval MrcStatus -    if it succeded return mrcSuccess
**/
extern
MrcStatus
  WriteVoltageCentering2D_DDR4 (
  IN OUT MrcParameters *const MrcData,
  IN OUT UINT16               MarginByte[MAX_RESULT_TYPE][MAX_RANK_IN_CHANNEL][MAX_CONTROLLER][MAX_CHANNEL][MAX_SDRAM_IN_DIMM][MAX_EDGES],
  IN     UINT8                McChBitMask,
  IN     UINT8                Rank,
  IN     UINT8                LoopCount,
  IN     UINT8                En2D
  );

/**
  Perform Write Timing Linear Centering in different Vref points.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] Prints        - Debug prints enable/disable

  @retval MrcStatus       - if it success return mrcSuccess
**/
extern
MrcStatus
EarlyWriteTimingCentering2D (
  IN     MrcParameters *const MrcData,
  IN     BOOLEAN              Prints
  );

/**
  Perform Write Timing Linear Centering in different Vref points.

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus       - if it success return mrcSuccess
**/
extern
MrcStatus
MrcEarlyWriteTimingCentering2D (
  IN     MrcParameters *const MrcData
  );

/**
  Perform LP4 Re-Training.

  @param[in] MrcData       - Include all MRC global data.

  @retval MrcStatus        - if it success return mrcSuccess
**/
extern
MrcStatus
MrcWriteDqDqsReTraining (
  IN     MrcParameters *const MrcData
  );

#endif // _MrcWriteDqDqs_h_

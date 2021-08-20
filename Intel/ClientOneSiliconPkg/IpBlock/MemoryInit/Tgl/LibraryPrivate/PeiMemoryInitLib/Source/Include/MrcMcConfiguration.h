/** @file
  Non training specific memory controller configuration definitions.

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
#ifndef __MrcMcConfiguration_h__
#define __MrcMcConfiguration_h__

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcAddressDecodeConfiguration.h"
#include "MrcCommandTraining.h"
#include "MrcCommon.h"
#include "MrcGeneral.h"
#include "MrcGlobal.h"
#include "MrcRefreshConfiguration.h"
#include "MrcSchedulerParameters.h"
#include "MrcStartMemoryConfiguration.h"
#include "MrcTimingConfiguration.h"

#define CDIEVSSHI           (2300)  ///< Constant CdieVssHi (value in pF), CNL value
#define CDIEVTT             (2500)  ///< Constant CdieVtt (value in pF), CNL value
#define VPANIC1             (25000)
#define VPANIC2             (40000)
#define SCOMP_CELLS_MIN     (3)
#define SCOMP_CELLS_MAX     (DDRPHY_COMP_CR_DDRCRCOMPCTL1_DqScompCells_MAX)

#define MRC_SAFE_LP4_CMD_PI  (128)
#define MRC_SAFE_LP4_CTL_PI  (128)

#define MRC_SAFE_LP5_CMD_PI  (0)
#define MRC_SAFE_LP5_CTL_PI  (0)

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
  );

/**
  This function locks the DDR frequency requested from SPD or User.
  It will update the frequency related members in the output structure.

  @param[in, out] MrcData - MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcFrequencyLock (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function initializes the Memory Controller: Scheduler, Timings, Address Decode,
  Odt Control, and refresh settings.

  @param[in, out] MrcData - MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status.
**/
MrcStatus
MrcMcConfiguration (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function initializes memory subsystem registers that are not specific to MC or DDRIO.

  @param[in, out] MrcData - Pointer to the global MRC data.

  @retval MrcStatus - mrcSuccess if successful or an error status.
**/
MrcStatus
MrcMemorySsInit (
  IN OUT  MrcParameters *const MrcData
  );

/**
  This function configures probeless config register.

  @param[in, out] MrcData - All the MRC global data.
**/
extern
void
MrcProbelessConfig(
  IN OUT MrcParameters *const MrcData
  );

/**
  This function initializes the Memory Controller Phy.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrIoPreInit (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function initializes the Memory Controller Phy.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrIoInit (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function checks for Scomp Training or Bypass mode.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrScomp (
  IN OUT MrcParameters *const MrcData
  );

/**
This function bypass the Slew Rate Delay Cells of the give Scomp Type.

  @param[in, out] MrcData    - Include all MRC global data.
  @param[in]      ScompIndex - Scomp Type
**/
VOID
MrcDdrScompBypass (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8         ScompBypassBitMask
  );

/**
  This function initializes the Memory Controller Scomp.

  @param[in, out] MrcData    - Include all MRC global data.
  @param[in]      ScompIndex - Scomp Type

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrScompInit (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8         ScompBypassBitMask
  );

/**
  This function init all the necessary registers for the training.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
extern
MrcStatus
MrcPreTraining (
  MrcParameters *const MrcData
  );

/**
  This function initializes all the necessary registers after main training steps but before LCT.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
extern
MrcStatus
MrcPostTraining (
  MrcParameters *const MrcData
  );

/**
  Program PCU_CR_DDR_VOLTAGE register.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] VddVoltage - Current DDR voltage.

**/
extern
void
MrcSetPcuDdrVoltage (
  IN OUT MrcParameters *MrcData,
  IN     MrcVddSelect  VddVoltage
  );

/**
  This function Setup the Vtt Termination.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] DebugMsg - Whether to display debug messages

**/
void
MrcSetupVtt (
  IN MrcParameters *const MrcData,
  IN BOOLEAN       DebugMsg
  );

#endif // __MrcMcConfiguration_h__


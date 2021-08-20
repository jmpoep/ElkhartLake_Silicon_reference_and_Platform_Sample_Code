/** @file
  .

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#ifndef _MrcChipApi_h_
#define _MrcChipApi_h_

#include "MrcDdrIoApi.h"

///
/// Defines and Macros
///
#define MAX_MR_GEN_FSM  (28)  ///< Maximum number of MR Addresses that can be sent.

///
/// Struct and Types
///
typedef struct {
  UINT16  Delay;  ///< Specified in tCK
  UINT8   MrAddr;
  UINT8   MrData;
  BOOLEAN Valid;
} MRC_GEN_MRS_FSM_MR_TYPE;

/**
  This function configures the Generic MRS FSM shadow registers based on the MrData inputs.
  It will determine if it needs to use the per-rank feature if the MR value differs across ranks.

  @param[in] MrcData - Pointer to MRC global data.
  @param[in] MrData  - Pointer to an array of MR data to configure the MRS FSM with.

  @retval mrcSuccess if successful.
  @retval mrcFail if MrData pointer is null, the timing or per-rank registers are out of free entries.
**/
MrcStatus
MrcGenMrsFsmConfig (
  IN  MrcParameters *MrcData,
  IN  MRC_GEN_MRS_FSM_MR_TYPE MrData[MAX_CONTROLLER][MAX_CHANNEL][MAX_RANK_IN_CHANNEL][MAX_MR_GEN_FSM]
  );

/**
  This function executes the MRS FSM and waits for the FSM to complete.
  If the FSM does not complete after 10 seconds, it will return an error message.

  @param[in] MrcData - Pointer to MRC global data.

  @retval mrcFail if the FSM is not idle.
  @retval mrcSuccess otherwise.
**/
MrcStatus
MrcGenMrsFsmRun (
  IN  MrcParameters *MrcData
  );

UINT32
MrcQclkToTck (
  IN  MrcParameters *const MrcData,
  IN  UINT32               Qclk
  );

UINT32
MrcTckToQclk (
  IN  MrcParameters *const MrcData,
  IN  UINT32               Tck
  );

/**
  Program MC/DDRIO registers to Gear1 or Gear2 mode.
  This only includes Gear2 mode enable/disable, not other registers that are impacted by gear mode.

  @param[in] MrcData - The MRC general data.
  @param[in] Gear2   - TRUE for Gear2, FALSE for Gear1

  @retval None
**/
void
MrcSetGear2 (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              Gear2
  );

/**
  Programming of CCC_CR_DDRCRCCCCLKCONTROLS_BlockTrainRst

  @param[in] MrcData - The MRC global data.
  @param[in] BlockTrainReset - TRUE to BlockTrainReset for most training algos.  FALSE for specific training algos that need PiDivider sync.

**/
VOID
MrcBlockTrainResetToggle (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              BlockTrainReset
  );

/**
  This function configures the DDRCRCMDBUSTRAIN register to values for normal mode.

  @param[in]  MrcData - Pointer to global MRC data.

  @retval none.
**/
VOID
MrcSetWritePreamble (
  IN  MrcParameters *const  MrcData
  );

/**
  Translate a TGL U\Y Register Offset to a TGL H Register Offset when the
  current processor is TGL H. The output is not guranteed to be correct if
  the input register offset is not a TGL U\Y register offset. There are known
  TGL-H register offsets which alias to TGL-U\Y register offsets.

  @param[in] MrcData      - Pointer to MRC global data.
  @param[in] RegOffset    - The register offset to tanslate. This must be a TGL A0\B0
                            register offset. Set BIT31 to avoid translation.

  @retval UINT32 - The register offset to the register for the current SoC.
**/
UINT32
MrcCrOffsetProjAdj (
  IN MrcParameters *const  MrcData,
  IN UINT32                RegOffset
  );

#endif // _MrcChipApi_h_

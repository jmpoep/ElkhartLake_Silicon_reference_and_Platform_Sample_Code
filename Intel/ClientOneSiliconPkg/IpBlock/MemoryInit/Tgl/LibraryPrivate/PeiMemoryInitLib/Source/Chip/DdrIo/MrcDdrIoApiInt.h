/** @file
  Contains functions that are used outside of the DdrIo Library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#ifndef _MrcDdrIoApiInt_h_
#define _MrcDdrIoApiInt_h_

/// Constants
extern const INT8 RxFifoChDelay[MRC_DDR_TYPE_UNKNOWN][MAX_GEARS][MAX_SYS_CHANNEL];

/// Defines
#define MRC_NUM_CCC_INSTANCES  (8)
#define MRC_NUM_OF_VSSHI_COMPS (14)
#define FLL_REF_CLK            (400) // MHz

/// Functions
/**
  This function updates the Gear specific fields in the DDRIO

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Gear2   - TRUE for Gear2, FALSE for Gear1
**/
VOID
DdrIoConfigGear2 (
  IN  MrcParameters *MrcData,
  IN  BOOLEAN       Gear2
  );

/**
  This function configures the DDR IO ODT type to Data and Comp blocks.
  VSS and VTT blocks are one time configured in MrcDdrIoInit.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  NewMode - ODT mode to enable.

  @retval MrcStatus - mrcSuccess if a valid ODT mode is requested, otherwise mrcWrongInputParameter.
**/
MrcStatus
MrcSetIoOdtMode (
  IN  MrcParameters *const  MrcData,
  IN  MRC_ODT_MODE_TYPE     NewMode
  );

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
  );

#endif //_MrcDdrIoApiInt_h_

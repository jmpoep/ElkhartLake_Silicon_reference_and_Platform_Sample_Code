/** @file
  This file contains functions to get Memory Controller Offsets
  used memory training.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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

#ifndef _MRC_MC_OFFSETS_H_
#define _MRC_MC_OFFSETS_H_
#include "MrcInterface.h"

/**
  Function used to get the CR Offset for Memory Controller Timings.

  @param[in]  Group     - MC Timing Group being accessed.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
MrcGetMcTimingRegOffset (
  IN  MrcParameters *MrcData,
  IN  GSM_GT  Group,
  IN  UINT32  Socket,
  IN  UINT32  Channel,
  IN  UINT32  FreqIndex
  );

/**
  Function used to get the CR Offset for Memory Controller Configuration Settings.

  @param[in]  Group     - MC Timing Group being accessed.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
MrcGetMcConfigRegOffset (
  IN  MrcParameters *MrcData,
  IN  GSM_GT  Group,
  IN  UINT32  Socket,
  IN  UINT32  Channel,
  IN  UINT32  FreqIndex
  );

/**
  This function returns the offset for the MRS FSM Control register.

  @param[in]  MrcData - Pointer to global MRC data.

  @retval Register Offset.
**/
UINT32
MrcGetMrsFsmCtlOffset (
  IN  MrcParameters *MrcData,
  IN  UINT32        Channel
  );

/**
  This function returns the offset for MRS run FSM Control register.

  @param[in]  MrcData - Pointer to global MRC data.

  @retval Register Offset.
**/
UINT32
MrcGetMrsRunFsmOffset (
  IN  MrcParameters *MrcData,
  IN  UINT32        Channel
  );

#endif //_MRC_MC_OFFSETS_H_

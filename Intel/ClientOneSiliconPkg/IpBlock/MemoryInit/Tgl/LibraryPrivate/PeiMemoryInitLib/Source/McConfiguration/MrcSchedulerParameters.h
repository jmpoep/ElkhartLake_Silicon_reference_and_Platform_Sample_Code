/** @file
  This module includes the memory controller scheduler parameters.

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
#ifndef _MrcSchedulerParameters_h_
#define _MrcSchedulerParameters_h_

#include "MrcTypes.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcGlobal.h"

#define SCHED_CBIT_DEFAULT    (0x00100030)
#define SCHED_CBIT_DEFAULT_B0 (0x00100000)

#define SC_WDBWM_DEFAULT      (0x553C3038)

/**
  This function configures the memory controller scheduler.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
MrcSchedulerParametersConfig (
  IN MrcParameters *const MrcData
  );

/**
  Set ODT Logic behavior for DDR4.

  @param[in, out] MrcData - Include all MRC global data.
  @param[in]      Profile - behavior Type. Currently Profile 1 is supported (DDR3-like)

  @retval none
**/
void
MrcSetOdtMatrix (
  IN OUT MrcParameters *const MrcData,
  IN UINT8                    Profile
  );

/**
  Configure DDR4_1DPC performance feature.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
void
MrcConfigureDdr4OneDpc (
  IN MrcParameters *const MrcData
  );

#endif // _MrcSchedulerParameters_h_

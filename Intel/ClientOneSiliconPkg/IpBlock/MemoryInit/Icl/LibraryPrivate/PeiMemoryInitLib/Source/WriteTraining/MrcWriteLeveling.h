/** @file
  The write leveling training algorithm definitions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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
#ifndef _MrcWriteLeveling_h_
#define _MrcWriteLeveling_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcReset.h"
#include "MrcIoControl.h"
#include "MrcReadReceiveEnable.h"

/**
  this function execute the Jedec write leveling Cleanup.
  Center TxDQS-CLK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeded return mrcSuccess
**/
extern
MrcStatus
MrcWriteLevelingFlyByTraining (
  IN OUT MrcParameters *const MrcData
  );

/**
  this function execute the functional write leveling training.
  Center TxDQS-CLK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succeded return mrcSuccess
**/
extern
MrcStatus
MrcWriteLevelingTraining (
  IN OUT MrcParameters *const MrcData
  );

/**
  this function execute the Jedec write leveling training.
  Center TxDQS-CLK timing

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if it succedes return mrcSuccess
**/
extern
MrcStatus
MrcJedecWriteLevelingTraining (
  IN OUT MrcParameters *const MrcData
  );

#endif // _MrcWriteLeveling_h_

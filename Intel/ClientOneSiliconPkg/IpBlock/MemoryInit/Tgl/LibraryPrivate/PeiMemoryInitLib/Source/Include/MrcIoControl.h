/** @file
  Memory controller IO configuration definition header.

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
#ifndef _MrcIoControl_h_
#define _MrcIoControl_h_

#include "MrcGlobal.h"
#include "MrcCommon.h"


/**
  Reset the MC IO module. The MC hardware will handle creating the 20 dclk pulse
  after the bit is set and will also clear the bit.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess    - IO Reset was done successfully
  @retval mrcDeviceBusy - Timed out waiting for the IO to clear the bit
**/
MrcStatus
IoReset (
  IN MrcParameters *const MrcData
  );
#endif // _MrcIoControl_h_

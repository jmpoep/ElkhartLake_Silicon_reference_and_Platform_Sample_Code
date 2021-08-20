/** @file
  This module configures the memory controller address decoder.

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
#ifndef _MrcAddressConfiguration_h_
#define _MrcAddressConfiguration_h_


#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcGlobal.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcDebugPrint.h"

/**
  This function is the main address decoding configuration function.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.

**/
extern
void
MrcAdConfiguration (
  IN MrcParameters *const MrcData
  );

/**
  This function configures the zone configuration registers MAD-CR and MAD-ZR-CR.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Controller  - Controller to configure.

  @retval Nothing.
**/
void
ZoneConfiguration (
  IN OUT MrcParameters *const MrcData,
  IN     UINT32               Controller
  );

/**
  This function configures the zone configuration registers MAD_SLICE.

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing.
**/
extern
void
ControllerZoneConfiguration (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function configures the MAD_DIMM_CH0/1 register.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Controller - Controller to configure.
  @param[in] Channel    - Channel to configure.

  @retval Nothing.
**/
void
ChannelAddressDecodeConfiguration (
  IN MrcParameters *const MrcData,
  IN const UINT32         Controller,
  IN const UINT32         Channel
  );

/**
  Initialize the MARS feature (Memory AwaRe Scrubber)

  @param[in] MrcData - Include all MRC global data.

  @retval none
**/
extern
void
MrcMarsConfig (
  IN MrcParameters *const MrcData
  );

#endif

/** @file
  Read receive enable training definitions.

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
#ifndef _MrcReadReceiveEnable_h_
#define _MrcReadReceiveEnable_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcCommon.h"
#include "MrcCrosser.h"
#include "MrcGlobal.h"
#include "MrcTimingConfiguration.h"
#include "MrcHalRegisterAccess.h"

//  For DDR4/LP3, 8x8=64UIs/32 DCLKs
//    At lowest speed (1067): ~60nsec, CL=8
//    At fastest speed (3200): ~20nsec, CL=22
//  For LP4, 8x16=128 UIs/64 DCLKs
//    1067MT/s: ~120nsec, CL=10
//    3200MT/s: ~40nsec, CL=28
//  We want to turn on our buffers 34 DCLK's to land in the middle of the burst.
//  This gives us 6 DLCK's of margin on the fast end for routing (34-28 = 6).
//  IO consumes 7 DCLK before starting RcvEn count.  So we subtract that from IO programming.
#define MRC_RCVEN_TOTAL_INIT    (34)  // DCLK
// -7 for tCL RcvEn
#define MRC_TCL_RCVEN_INIT      (22)  // DCLK
#define MRC_RX_FLYBY_INIT       (3)   // DCLK
#define MRC_RCVEN_PI_INIT       (256)  // PI
#define MRC_RCVEN_PI_DCLK_INIT  (2)    // DCLK
#define MRC_FIFO_GUARDBAND      (1)    // DCLK

///
/// ReadReceiveEnable (RRE) parameters
/// Command training will reduce this by 64, so plan for that now in the ideal value.
/// If the Rank delta is larger than PI width minus 64, then do not reserve this extra range.
///
#define RRE_PI_TO_RESERVE         (64)
#define RRE_PI_IDEAL              (256)
#define RRE_PI_IDEAL_RSV          (RRE_PI_LARGE_DELTA_IDEAL + RRE_PI_TO_RESERVE)
#define RRE_ALL_RANKS_MASK        (0x0F)
#define RRE_DCLK_PI_VAL           (128)
#define RRE_QCLK_PI_VAL           (64)

// CLK PI shift during Roundtrip Latency optimization in order to guardband for delay drift/jitter
#define MRC_RTL_CLK_SHIFT         (25)

/**
  Perform receive enable training.
  Optimize RcvEn timing with MPR pattern

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus -  if succeeded, return mrcSuccess
**/
extern
MrcStatus
MrcReadLevelingTraining (
  IN OUT MrcParameters *const MrcData
  );

/**
  Once the DQS high phase has been found (for each DRAM) the next stage is to find out the round trip latency,
  by locating the preamble cycle. This is achieved by trying smaller and smaller roundtrip
  values until the strobe sampling is done on the preamble cycle.
  The following algorithm is used to find the preamble cycle:

  @param[in] MrcData         - all the global data

  @retval Nothing.
**/
extern
MrcStatus
MrcRoundTripLatency (
  IN     MrcParameters *const MrcData
  );

/**
  Perform Receive Enable Timing Centering.
  Center Receive Enable using moderate pattern with 1D eye

  @param[in] MrcData         - Include all MRC global data.

  @retval MrcStatus       - if it succeded returns mrcSuccess
**/
MrcStatus
MrcReceiveEnTimingCentering (
  IN MrcParameters *const MrcData
  );

#endif // _MrcReadReceiveEnable_h_

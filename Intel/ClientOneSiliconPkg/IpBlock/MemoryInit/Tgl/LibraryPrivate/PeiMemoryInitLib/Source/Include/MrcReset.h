/** @file
  The DDR3 reset sequence definitions.

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

#ifndef _MrcReset_h_
#define _MrcReset_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcDdr3.h"

//
// Defines for "all ranks Hot" for LPDDR_MR4_RANK_TEMPERATURE and DDR4_MPR_RANK_TEMPERATURE
// Each nibble is one rank; values are from JEDEC spec.
//
#define RANK_TEMPERATURE_HOT_LPDDR4     0x06060606
#define RANK_TEMPERATURE_HOT_LPDDR5     0x0f0f0f0f
#define RANK_TEMPERATURE_HOT_DDR4       0x02020202
#define RANK_TEMPERATURE_1XREF_LPDDR4   0x03030303
#define RANK_TEMPERATURE_1XREF_LPDDR5   0x09090909
#define RANK_TEMPERATURE_1XREF_DDR4     0x01010101

/**
  Perform full JEDEC reset and init sequence.

  @param[in] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess or reason for failure.
**/
extern
MrcStatus
MrcResetSequence (
  IN MrcParameters *const MrcData
  );

/**
  Perform the required steps to exit self refresh in S3/Warm reset:
    Download the Read Reg File for all populated ranks.
    Assert CKE for all the ranks present to pull Dimms out of Self-Refresh.
    Issue long ZQ Calibration for all the ranks present in the channel.
    Set REUT to normal mode for all channels.
    Set the Power Down Config Register.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcSelfRefreshExit (
  IN MrcParameters *const MrcData
  );

/**
  Perform the MRs Commands to initialize DDR4 memory

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess, mrcFail when not successful
**/
MrcStatus
MrcDdr4Mrs (
  IN MrcParameters *const MrcData
  );

#endif // _MrcReset_h_

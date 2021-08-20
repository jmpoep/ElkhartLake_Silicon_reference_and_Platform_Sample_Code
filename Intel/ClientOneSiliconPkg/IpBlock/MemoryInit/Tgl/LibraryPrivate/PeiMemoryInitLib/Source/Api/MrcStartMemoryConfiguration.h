/** @file
  Starting point for the core memory reference code.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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

#ifndef __MRC_StartMemoryConfiguration_h__
#define __MRC_StartMemoryConfiguration_h__

//
// Include files
//

#include "MrcTypes.h"
#include "MrcApi.h"

#define POST_CODE_NO_OVR  ((1 << ((sizeof (MrcPostCode) * 8) - 1)) + ((1 << ((sizeof (MrcPostCode) * 8) - 1)) - 1))

typedef enum {
  MF_NULL,                ///< All policy flags turned off.
  MF_COLD     = (1 << 0), ///< Execute MRC function on cold reset.
  MF_FAST     = (1 << 1), ///< Execute MRC function on cold reset when S3 data is present.
  MF_WARM     = (1 << 2), ///< Execute MRC function on warm reset.
  MF_S3       = (1 << 3), ///< Execute MRC function on S3 exit.
  MF_RMT      = (1 << 4), ///< Execute RMT after this function.
  MF_GV_1     = (1 << 5), ///< Execute MRC function when in the First SA GV point.
  MF_GV_2     = (1 << 6), ///< Execute MRC function when in the Second SA GV point.
  MF_GV_3     = (1 << 7), ///< Execute MRC function when in the Third SA GV point.
  MF_GV_4     = (1 << 8), ///< Execute MRC function when in the Fourth SA GV point.
  MF_TST      = (1 << 9), ///< Execute Trained State Tracing after this function.
  MF_DELIM    = MRC_UINT32_MAX
} MrcPolicyFlag;

#pragma pack(push, 1)
typedef struct {
  MrcStatus (*mrc_task) (MrcParameters * const MrcData);  ///< Ptr to function to execute, with parameter list.
  MrcPostCode   post_code_ovr;                            ///< BIOS post code output to the debug port if value <> 0.
  UINT32        oem_cmd;                                  ///< OEM function to execute prior to MRC function.
  BOOLEAN       DebugPrint;                               ///< Print debug log or not for this task
  MrcPolicyFlag policy_flag;                              ///< Call table flags
  MrcIteration  iteration;                                ///< Maximum number of CPU only resets.
#ifdef MRC_DEBUG_PRINT
  char          *String;                                  ///< Output string describing this task (potentially output to debug serial port).
#endif // MRC_DEBUG_PRINT
} CallTableEntry;
#pragma pack(pop)

extern const CallTableEntry MrcCallTable[];

/**
  this function use by the OEM to do dedicated task during the MRC.

  @param[in] MrcData           - include all the MRC data
  @param[in] OemStatusCommand  - A command that indicates the task to perform.
  @param[in] ptr               - general ptr for general use.

  @retval The status of the task.
**/
extern
MrcStatus
MrcInternalCheckPoint (
  IN MrcParameters        *MrcData,
  IN MrcOemStatusCommand  OemStatusCommand,
  IN void                 *ptr
  );

/**
@brief

  Get the number of call table entries.

  @param[in, out] MrcData - Include all MRC global data.

  @retval The number of call table entries.

**/
extern
UINT16
MrcGetCallTableCount (
  IN OUT MrcParameters *const MrcData
  );

#endif

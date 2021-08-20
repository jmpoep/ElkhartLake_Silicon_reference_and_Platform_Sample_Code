/** @file
  This file contains memory scrubbing and alias checking related information.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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
#ifndef _MrcMemoryScrub_h_
#define _MrcMemoryScrub_h_
#pragma pack (push, 1)


#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcCommon.h"
#include "MrcDebugHook.h"
#include "MrcGlobal.h"

/**
  Zero out all of the memory.
  This function is used in the following cases:
   - ECC is enabled (to initialize ECC logic)
   - TXT library is asking to scrub the memory (instead of SCLEAN ACM)
   - Platform code is asking to scrub the memory due to MOR bit being set (Memory Override Request)

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess if the clean succeeded, otherwise an error status.
**/
extern
MrcStatus
MrcEccClean (
  IN     MrcParameters *const MrcData
  );

/**
  This function performs a memory alias check.

  @param[in] MrcData - The global host structure

  @retval mrcSuccess or error value.
**/
extern
MrcStatus
MrcAliasCheck (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function provides MRC core hook to call TXT Alias Check before DRAM Init Done.

  @param[in]  MrcData - Pointer to global MRC structure.

  @retval mrcSuccess.
**/
MrcStatus
MrcTxtAliasCheck (
  IN MrcParameters *const MrcData
  );

#pragma pack (pop)
#endif

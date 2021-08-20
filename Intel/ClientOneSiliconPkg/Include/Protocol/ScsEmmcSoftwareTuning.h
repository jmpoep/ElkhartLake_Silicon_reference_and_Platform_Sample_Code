/** @file
  Protocol definition for saving eMMC software tuning results. Implemented by
  platform code.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#ifndef _SCS_EMMC_SOFTWARE_TUNING_H_
#define _SCS_EMMC_SOFTWARE_TUNING_H_
#include <ScsConfig.h>

#define SCS_EMMC_SOFTWARE_TUNING_PROTOCOL_REVISION 1

extern EFI_GUID  gScsEmmcSoftwareTuningProtocolGuid;

typedef struct _SCS_EMMC_SOFTWARE_TUNING_PROTOCOL SCS_EMMC_SOFTWARE_TUNING_PROTOCOL;

/**
  This protocol can be used to get eMMC HS400 DLL values that have been tuned
  by eMMC HS400 software tuning algorithm.

  If eMMC HS400 software tuning is enabled in policy, reference code
  will publish this protocol after software tuning has finished successfully. Tuned DLL
  values can be saved by platform code and used in subsequent boots to speed up
  the boot time.
**/
struct _SCS_EMMC_SOFTWARE_TUNING_PROTOCOL {
  UINT32                            Revision;
  SCS_EMMC_SOFTWARE_TUNING_RESULTS  TuningResults;
};

#endif


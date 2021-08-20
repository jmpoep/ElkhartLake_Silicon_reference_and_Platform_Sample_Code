/** @file
  Configurations for Telemetry

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#ifndef _TELEMETRY_CONFIG_H_
#define _TELEMETRY_CONFIG_H_

#include <ConfigBlock.h>

#pragma pack (push,1)

#define TELEMETRY_PEI_CONFIG_REVISION 1
#define TELEMETRY_PEI_PREMEM_CONFIG_REVISION 1

extern EFI_GUID gTelemetryPeiConfigGuid;
extern EFI_GUID gTelemetryPeiPreMemConfigGuid;

/**
  This configuration block describes Telemetry settings in PreMem.\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER        Header;              /// Config Block Header
  UINT32                     CpuCrashLogDevice;   /// Enable or Disable CrashLog/Telemetry Device  0- Disable, <b>1- Enable</b>
} TELEMETRY_PEI_PREMEM_CONFIG;

/**
  This configuration block describes Telemetry settings in PostMem.\n
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER        Header;              /// Config Block Header
  UINT32                     CpuCrashLogEnable;   /// Enable or Disable CrashLog feature  0- Disable, <b>1- Enable</b>
} TELEMETRY_PEI_CONFIG;

#pragma pack (pop)

#endif

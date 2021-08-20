/** @file
  Header file for North TraceHub Lib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#ifndef _PEI_CPU_TRACEHUB_LIB_H_
#define _PEI_CPU_TRACEHUB_LIB_H_

#include <SaPolicyCommon.h>
#include <TraceHubConfig.h>
#include <Library/PeiServicesLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/BootGuardLib.h>
#include <Library/MtrrLib.h>
#include <Library/CpuRegbarAccessLib.h>

/**
  Hide CPU Trace Hub device via PSF
**/
VOID
HideCpuTraceHub (
  VOID
);

/**
  Configure CPU Trace Hub

  @param[in] EnableMode              Trace Hub Enable Mode from policy

  @retval EFI_SUCCESS.
  @retval EFI_OUT_OF_RESOURCES.
**/
EFI_STATUS
ConfigureCpuTraceHub (
  IN UINT8       EnableMode
  );
#endif

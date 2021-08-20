/** @file
  Header file for the PeiCpuPolicyLib library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

@par Specification
**/
#ifndef _PEI_CPU_POLICY_LIBRARY_H_
#define _PEI_CPU_POLICY_LIBRARY_H_

#include <PiPei.h>
#include <CpuAccess.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Ppi/MasterBootMode.h>
#include <Ppi/SiPolicy.h>
#include <Library/CpuPolicyLib.h>
#include <BiosGuard.h>
#include <IndustryStandard/SmBios.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/TxtLib.h>
#include <Register/Cpuid.h>
#include <Library/PcdLib.h>
#include <SaCommonDefinitions.h>

//
// TXT configuration defines
//
#define TXT_SINIT_MEMORY_SIZE         0x50000
#define TXT_HEAP_MEMORY_SIZE          0xF0000
#define TXT_LCP_PD_BASE               0x0         ///< Platform default LCP
#define TXT_LCP_PD_SIZE               0x0         ///< Platform default LCP
#define TXT_TGA_MEMORY_SIZE           0x0         ///< Maximum 512K of TGA memory (aperture)

#endif // _PEI_CPU_POLICY_LIBRARY_H_

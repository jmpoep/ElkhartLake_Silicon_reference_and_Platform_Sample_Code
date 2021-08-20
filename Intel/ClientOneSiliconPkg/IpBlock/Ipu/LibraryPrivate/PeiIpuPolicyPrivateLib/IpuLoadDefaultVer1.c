/** @file
  This file provides services for IPU PEI policy default load function Ver1.

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
#include <Library/DebugLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PeiServicesLib.h>
#include <Ppi/SiPolicy.h>
#include <SiPolicyStruct.h>


/**
  Function call to Load defaults for IPU Ver1

  @param[in] ConfigBlockPointer  - Pointer to ConfigBlock
**/
VOID
IpuLoadPreMemDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  IPU_PREMEM_CONFIG      *IpuPreMemPolicy;
  UINT8                  Index;

  IpuPreMemPolicy = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "IpuPreMemPolicy->Header.GuidHob.Name = %g\n", &IpuPreMemPolicy->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "IpuPreMemPolicy->Header.GuidHob.Header.HobLength = 0x%x\n", IpuPreMemPolicy->Header.GuidHob.Header.HobLength));
  //
  // IPU Policy Ver 1 default load
  //
  if (PcdGetBool (PcdIpuEnable)) {
    IpuPreMemPolicy->IpuEnable = TRUE;
    IpuPreMemPolicy->IpuImrConfiguration = 0;
    for (Index = 0; Index < GPIO_IMGUCLK_NUMBER_OF_PINS; Index ++) {
      IpuPreMemPolicy->ImguClkOutEn[Index] = TRUE;
    }
  }

}

/** @file
  This file provides services for IPU PEI policy default print function Version 2

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
#include <Library/PeiIpuPolicyPrivateLib.h>




/**
  This function prints the PEI phase PreMem policy for IPU.

  @param[in] SiPolicyPreMemPpi - Instance of SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
IpuPrintPolicyPpiPreMem (
  IN  SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                            Status;
  IPU_PREMEM_CONFIG                     *IpuPreMemPolicy;
  UINT8                                 Index;

  //
  // Get IPU Config Blocks which needs to be used here
  //
  IpuPreMemPolicy = NULL;
  Status = GetConfigBlock ((VOID *) SiPolicyPreMemPpi, &gIpuPreMemConfigGuid, (VOID *) &IpuPreMemPolicy);
  ASSERT_EFI_ERROR (Status);
  if (IpuPreMemPolicy != NULL) {
    DEBUG ((DEBUG_INFO, "------------------------ IPU_PREMEM_CONFIG Begin -----------------\n"));
    if (IpuPreMemPolicy->Header.Revision == IPU_PREMEM_CONFIG_REVISION) {
      DEBUG ((DEBUG_INFO, " Revision : %d\n", IpuPreMemPolicy->Header.Revision));
      DEBUG ((DEBUG_INFO, " IpuEnable : 0x%x\n", IpuPreMemPolicy->IpuEnable));
      DEBUG ((DEBUG_INFO, " IpuImrConfiguration : 0x%x\n", IpuPreMemPolicy->IpuImrConfiguration));
      for (Index = 0; Index < GPIO_IMGUCLK_NUMBER_OF_PINS; Index ++) {
        DEBUG ((DEBUG_INFO, " ImguClkOutEn[%x] : %x\n", Index, IpuPreMemPolicy->ImguClkOutEn[Index]));
      }
      DEBUG ((DEBUG_INFO, " IpuFusaConfigEnable : 0x%x\n", IpuPreMemPolicy->IpuFusaConfigEnable));
    } else {
      DEBUG ((DEBUG_INFO, " IPU Config Block Revision = %d \n", IpuPreMemPolicy->Header.Revision));
      DEBUG ((DEBUG_INFO, " IPU_PREMEM_CONFIG_REVISION = %d \n", IPU_PREMEM_CONFIG_REVISION));
      DEBUG ((DEBUG_INFO, " IPU Config Block Version doesn't match.\n"));
      ASSERT (IpuPreMemPolicy->Header.Revision == IPU_PREMEM_CONFIG_REVISION);
    }
    DEBUG ((DEBUG_INFO, "\n----------------------- IPU_PREMEM_CONFIG End ------------------\n"));
  }

  DEBUG_CODE_END ();
  return;
}

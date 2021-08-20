/** @file
  Provide SecTemporaryRamDone function.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2020 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification
**/

#include <PiPei.h>
#include <Ppi/TempRamExitPpi.h>
#include <Library/CacheAsRamLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/DebugAgentLib.h>
#include <Library/FspWrapperPlatformLib.h>
#include <Library/FspWrapperApiLib.h>
#include <Library/PeiServicesTablePointerLib.h>
#include <Library/BootMediaLib.h>

/**
  This interface disables temporary memory in SEC Phase.
  @todo move to inside FSP
**/
VOID
EFIAPI
SecPlatformDisableTemporaryMemory (
  VOID
  )
{
  //
  //  Call FSP TemRamExit Api for SPI boot
  //
  if (BootMediaIsSpi ()) {
    DEBUG((DEBUG_INFO, "SecPlatformDisableTemporaryMemory enter\n"));

#if FixedPcdGet8(PcdFspModeSelection) == 1
    EFI_STATUS                Status;
    VOID                      *TempRamExitParam;

    TempRamExitParam = UpdateTempRamExitParam ();
    Status = CallTempRamExit (TempRamExitParam);
    DEBUG((DEBUG_INFO, "TempRamExit status: 0x%x\n", Status));
    ASSERT_EFI_ERROR(Status);
#else

    EFI_STATUS               Status;
    CONST EFI_PEI_SERVICES   **PeiServices;
    FSP_TEMP_RAM_EXIT_PPI    *TempRamExitPpi;

    PeiServices = GetPeiServicesTablePointer ();
    Status = (*PeiServices)->LocatePpi (
                             PeiServices,
                             &gFspTempRamExitPpiGuid,
                             0,
                             NULL,
                             (VOID **) &TempRamExitPpi
                             );
    ASSERT_EFI_ERROR (Status);
    if (EFI_ERROR (Status)) {
      return;
    }
    TempRamExitPpi->TempRamExit (NULL);
#endif
  }

  return ;
}

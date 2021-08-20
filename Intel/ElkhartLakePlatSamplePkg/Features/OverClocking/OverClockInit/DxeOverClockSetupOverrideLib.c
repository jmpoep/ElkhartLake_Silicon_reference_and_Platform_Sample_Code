/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2017 Intel Corporation.

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

@par Specification Reference:
**/

#include <Uefi/UefiBaseType.h>
#include <Uefi/UefiSpec.h>
#include <Library/DebugLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <SetupVariable.h>
#include "DxeOverClockSetupOverrideLib.h"

/**
  This Function loads the H/W Defults for the OverClock Variables
  during LoadDefaults (F3) in Setup.

  @param[in] SetupDataBuf          Pointer to a SETUP_DATA buffer.
  @param[in] SaSetupDataBuf        Pointer to a SA_SETUP buffer.
  @param[in] CpuSetupDataBuf       Pointer to a CPU_SETUP buffer.

**/
VOID
LoadOverClockHwDefault (
  UINT8     *SetupDataBuf,
  UINT8     *SaSetupDataBuf,
  UINT8     *CpuSetupDataBuf
  )
{
  UINTN           VariableSize;
  EFI_STATUS      Status;
  SA_SETUP        SaSetupData;
  SA_SETUP        *SaSetup;
  CPU_SETUP       CpuSetupData;
  CPU_SETUP       *CpuSetup;
  SETUP_DATA      SetupData;
  SETUP_DATA      *Setup;

  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupData
                  );
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR(Status)) {
    Setup = (SETUP_DATA *) SetupDataBuf;
  }

  VariableSize = sizeof (SA_SETUP);
  Status = gRT->GetVariable (
                  L"SaSetup",
                  &gSaSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SaSetupData
                  );
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR(Status)) {
    SaSetup = (SA_SETUP *) SaSetupDataBuf;
    SaSetup->tCL        = SaSetupData.tCLDefault;
    SaSetup->tRCDtRP    = SaSetupData.tRCDtRPDefault;
    SaSetup->tRAS       = SaSetupData.tRASDefault;
  }

  VariableSize = sizeof (CPU_SETUP);
  Status = gRT->GetVariable (
                  L"CpuSetup",
                  &gCpuSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &CpuSetupData
                  );
  ASSERT_EFI_ERROR (Status);
  if (!EFI_ERROR(Status)) {
    CpuSetup = (CPU_SETUP *) CpuSetupDataBuf;
    CpuSetup->CpuRatio = CpuSetupData.FlexRatioOverrideDefault;
    if (CpuSetupData.Ck505Present) {
      CpuSetup->ProcessorBusSpeedOverride = CpuSetupData.ProcessorBusSpeedOverrideDefault;
    }
    CpuSetup->RatioLimit1 = CpuSetupData.RatioLimit1Default;
    CpuSetup->RatioLimit2 = CpuSetupData.RatioLimit2Default;
    CpuSetup->RatioLimit3 = CpuSetupData.RatioLimit3Default;
    CpuSetup->RatioLimit4 = CpuSetupData.RatioLimit4Default;
    CpuSetup->RatioLimit5 = CpuSetupData.RatioLimit5Default;
    CpuSetup->RatioLimit6 = CpuSetupData.RatioLimit6Default;
    CpuSetup->RatioLimit7 = CpuSetupData.RatioLimit7Default;
    CpuSetup->RatioLimit8 = CpuSetupData.RatioLimit8Default;
  }
}

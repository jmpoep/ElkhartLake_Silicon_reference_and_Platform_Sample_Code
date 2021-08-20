/** @file
  This file is PeiDTbtPolicyLib library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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
#include <Library/PeiServicesLib.h>
#include <PiPei.h>
#include <PeiDTbtPolicyLibrary.h>
#include <Ppi/ReadOnlyVariable2.h>
#include <Ppi/PeiDTbtPolicy.h>

/**
  Print PEI DTBT Policy
**/
VOID
EFIAPI
DTbtPrintPeiPolicyConfig (
  VOID
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                       Status;
  UINT8                            Index;
  PEI_DTBT_POLICY                  *PeiDTbtConfig;

  PeiDTbtConfig = NULL;
  Status = EFI_NOT_FOUND;
  DEBUG ((DEBUG_INFO, "DTbtPrintPolicyConfig Start\n"));

  Status = PeiServicesLocatePpi (
             &gPeiDTbtPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &PeiDTbtConfig
             );
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, " gPeiDTbtPolicyPpiGuid Not installed!!!\n"));
    return;
  }

  //
  // Print DTBT Policy
  //
  DEBUG ((DEBUG_INFO, "\n------------------------ DTBT Policy (PEI) Print BEGIN -----------------\n"));
  DEBUG ((DEBUG_INFO, "Revision : 0x%x\n", PEI_DTBT_POLICY_REVISION));
  for (Index = 0; Index < MAX_DTBT_CONTROLLER_NUMBER; Index++) {
    DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtControllerConfig[%x].DTbtControllerEn = %x\n", Index, PeiDTbtConfig->DTbtControllerConfig[Index].DTbtControllerEn));
    DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtControllerConfig[%x].Type = %x\n", Index, PeiDTbtConfig->DTbtControllerConfig[Index].Type));
    DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtControllerConfig[%x].PcieRpNumber = %x\n", Index, PeiDTbtConfig->DTbtControllerConfig[Index].PcieRpNumber));
    DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtControllerConfig[%x].ForcePwrGpio.GpioPad = %x\n", Index, PeiDTbtConfig->DTbtControllerConfig[Index].ForcePwrGpio.GpioPad));
    DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtControllerConfig[%x].ForcePwrGpio.GpioLevel = %x\n", Index, PeiDTbtConfig->DTbtControllerConfig[Index].ForcePwrGpio.GpioLevel));
    DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtControllerConfig[%x].PcieRstGpio.GpioPad = %x\n", Index, PeiDTbtConfig->DTbtControllerConfig[Index].PcieRstGpio.GpioPad));
    DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtControllerConfig[%x].PcieRstGpio.GpioLevel = %x\n", Index, PeiDTbtConfig->DTbtControllerConfig[Index].PcieRstGpio.GpioLevel));
    DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtControllerConfig[%x].CioPlugEventGpio.GpioPad = %x\n", Index, PeiDTbtConfig->DTbtControllerConfig[Index].CioPlugEventGpio.GpioPad));
    DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtControllerConfig[%x].CioPlugEventGpio.AcpiGpeSignature = %x\n", Index, PeiDTbtConfig->DTbtControllerConfig[Index].CioPlugEventGpio.AcpiGpeSignature));
    DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtControllerConfig[%x].CioPlugEventGpio.AcpiGpeSignaturePorting = %x\n", Index, PeiDTbtConfig->DTbtControllerConfig[Index].CioPlugEventGpio.AcpiGpeSignaturePorting));
  }

  //
  // Print DTBT Common Policy
  //
  DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtGenericConfig.TbtBootOn = %x\n", PeiDTbtConfig->DTbtGenericConfig.TbtBootOn));
  DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtGenericConfig.TbtUsbOn = %x\n", PeiDTbtConfig->DTbtGenericConfig.TbtUsbOn));
  DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwr = %x\n", PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwr));
  DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwrDly = %x\n", PeiDTbtConfig->DTbtGenericConfig.Gpio3ForcePwrDly));
  DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtGenericConfig.DTbtSharedGpioConfiguration = %x\n", PeiDTbtConfig->DTbtGenericConfig.DTbtSharedGpioConfiguration));
  DEBUG ((DEBUG_INFO, "PeiDTbtConfig->DTbtGenericConfig.PcieRstSupport = %x\n", PeiDTbtConfig->DTbtGenericConfig.PcieRstSupport));
  DEBUG ((DEBUG_INFO, "\n------------------------ DTBT Policy (PEI) Print END -----------------\n"));
  DEBUG_CODE_END ();

  return;
}

/**
  Install DTbt Policy

  @retval EFI_SUCCESS                   The policy is installed.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer

**/
EFI_STATUS
EFIAPI
InstallPeiDTbtPolicy (
  VOID
  )
{
  EFI_STATUS                    Status;
  EFI_PEI_PPI_DESCRIPTOR        *PeiDTbtPolicyPpiDesc;
  PEI_DTBT_POLICY               *PeiDTbtConfig;

  DEBUG ((DEBUG_INFO, "Install PEI DTBT Policy\n"));

  PeiDTbtConfig = NULL;

  //
  // Allocate memory for PeiDTbtPolicyPpiDesc
  //
  PeiDTbtPolicyPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
  ASSERT (PeiDTbtPolicyPpiDesc != NULL);
  if (PeiDTbtPolicyPpiDesc == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Allocate memory and initialize all default to zero for PeiDTbtPolicy
  //
  PeiDTbtConfig = (PEI_DTBT_POLICY *) AllocateZeroPool (sizeof (PEI_DTBT_POLICY));
  ASSERT (PeiDTbtConfig != NULL);
  if (PeiDTbtConfig == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Initialize PPI
  //
  PeiDTbtPolicyPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
  PeiDTbtPolicyPpiDesc->Guid = &gPeiDTbtPolicyPpiGuid;
  PeiDTbtPolicyPpiDesc->Ppi = PeiDTbtConfig;

  Status = PeiServicesInstallPpi (PeiDTbtPolicyPpiDesc);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Install PEI DTBT Policy failed\n"));
  }
  return Status;
}


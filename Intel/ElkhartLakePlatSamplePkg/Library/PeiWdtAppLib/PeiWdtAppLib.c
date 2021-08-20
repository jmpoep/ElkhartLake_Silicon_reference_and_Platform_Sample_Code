/** @file
  Platform-specific Wdt code. Offers more convenient and foolproof API
  for manipulating WDT than low-level WDT driver which is part of Reference
  Code. WdtApp is too platform-specific to be included in reference code.
  However, it is expected that each client will need to write something
  similar on his own.
  This implementation simply kicks Wdt once before MRC execution starts,
  with such timeout value that allows BIOS to arrive in DXE phase where
  the Dxe part of this driver takes control of Wdt. There are other
  possibilities. For example, a more robust way would be to kick WDT more
  often, after each PEI module is loaded, and use shorter timeout values.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2016 Intel Corporation.

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

#include <Library/PeiWdtAppLib.h>

/**
  Turns on WDT during PEI phase according to requests made by
  OS overclocking application (through WDT status) and BIOS modules (through flash variable)

  @param[in]  WdtPei

  @retval     EFI_SUCCESS
**/
EFI_STATUS
PeiWdtApp (
  IN WDT_PPI    *WdtPei
  )
{
  EFI_STATUS                      Status;
  EFI_GUID                        EfiPeiReadOnlyVariable2PpiGuid = EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID;
  WDT_PERSISTENT_DATA             WdtStateData;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *ReadOnlyVariable;
  UINTN                           VariableSize;

  DEBUG ((DEBUG_INFO, "(WdtApp) PeiWdtApp\n"));

  Status = PeiServicesLocatePpi (
             &EfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &ReadOnlyVariable
             );
  ASSERT_EFI_ERROR (Status);

  VariableSize = sizeof (WdtStateData);

  Status = ReadOnlyVariable->GetVariable (
                               ReadOnlyVariable,
                               WDT_PERSISTENT_DATA_C_NAME,
                               &gWdtPersistentDataGuid,
                               NULL,
                               &VariableSize,
                               &WdtStateData
                               );

  if (EFI_ERROR (Status)) {
    WdtStateData.Enable = 0;
  }

  if ((WdtPei->IsWdtRequired() == TRUE) || (WdtPei->IsWdtEnabled() == TRUE) || (WdtStateData.Enable == 1)) {
    WdtPei->ReloadAndStart (PcdGet8 (PcdWdtTimeoutBetweenPeiDxe));
  } else {
    WdtPei->Disable ();
  }

  return EFI_SUCCESS;
}

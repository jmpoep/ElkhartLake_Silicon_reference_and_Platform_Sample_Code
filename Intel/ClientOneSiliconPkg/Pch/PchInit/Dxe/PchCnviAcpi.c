/** @file
  Initializes PCH CNVi device ACPI data.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#include <Library/HobLib.h>
#include <CnviConfigHob.h>
#include "PchInit.h"

/**
  Update ASL definitions for CNVi device.

  @retval EFI_SUCCESS         The function completed successfully
**/
EFI_STATUS
UpdateCnviAcpiData (
  VOID
  )
{
  EFI_PEI_HOB_POINTERS HobPtr;
  CNVI_CONFIG_HOB      *CnviConfigHob;

  DEBUG ((DEBUG_INFO, "UpdateCnviAcpiData() Start\n"));

  // Get CNVi Config HOB.
  HobPtr.Guid = GetFirstGuidHob (&gCnviConfigHobGuid);
  if (HobPtr.Guid != NULL) {
    CnviConfigHob = (CNVI_CONFIG_HOB *) GET_GUID_HOB_DATA (HobPtr.Guid);
    mPchNvsAreaProtocol.Area->CnviMode           = (UINT8)CnviConfigHob->Mode;
    mPchNvsAreaProtocol.Area->CnviBtCore         = (UINT8)CnviConfigHob->BtCore;
    mPchNvsAreaProtocol.Area->CnviBtAudioOffload = (UINT8)CnviConfigHob->BtAudioOffload;
  }
  DEBUG ((DEBUG_INFO, "UpdateCnviAcpiData() End\n"));

  return EFI_SUCCESS;
}

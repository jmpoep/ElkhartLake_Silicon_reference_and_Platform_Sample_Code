/** @file
  The DXE IPU Init Library Implements

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

#include <Base.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <SaPolicyCommon.h>
#include <Library/HobLib.h>
#include <Protocol/SaNvsArea.h>
#include <IpuConfigHob.h>

/**
  Update IPU NVS AREA tables

**/
VOID
UpdateIpuNvs (
  VOID
  )
{
  SYSTEM_AGENT_NVS_AREA_PROTOCOL   *SaNvsAreaProtocol;
  IPU_CONFIG_HOB                   *IpuConfigHob;
  EFI_STATUS                       Status;
  ///
  /// Update IPU Device Enable status in Nvs from HOB values
  ///
  Status = gBS->LocateProtocol (&gSaNvsAreaProtocolGuid, NULL, (VOID **) &SaNvsAreaProtocol);
  if (Status != EFI_SUCCESS) {
    return;
  }

  IpuConfigHob = NULL;
  IpuConfigHob = (IPU_CONFIG_HOB *) GetFirstGuidHob (&gIpuConfigHobGuid);
  if (IpuConfigHob != NULL) {
    DEBUG ((DEBUG_INFO, "[IPU] Update IPU GNVS Area.\n"));
    SaNvsAreaProtocol->Area->IpuAcpiMode = (UINT8) IpuConfigHob->IpuAcpiMode;
  }
}


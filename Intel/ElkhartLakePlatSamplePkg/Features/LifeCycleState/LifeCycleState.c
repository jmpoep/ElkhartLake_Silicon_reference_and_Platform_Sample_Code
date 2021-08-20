/**@file

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


#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PciLib.h>
#include <Register/HeciRegs.h>
#include <Register/MeRegs.h>
#include <Protocol/LifeCycleState.h>
#include <Library/PreSiliconEnvDetectLib.h>

LIFE_CYCLE_STATE mLifeCycleState;

LIFE_CYCLE_STATE_PROTOCOL mLifeCycleStateProtocol = {
  LIFE_CYCLE_STATE_PROTOCOL_REVISION1,
  GetLifeCycleState
};

/**
  Retrieves life cycle state

  @param[in]   This              Protocol instance pointer.
  @param[out]  LifeCycleState    The life cycle state read from ME FW status.

  @retval      EFI_SUCCESS       The state was successfully retrived.

**/
EFI_STATUS
GetLifeCycleState (
  IN LIFE_CYCLE_STATE_PROTOCOL *This,
  OUT LIFE_CYCLE_STATE *LifeCycleState
  )
{
  *LifeCycleState = mLifeCycleState;
  return EFI_SUCCESS;
}

/**
  The life cycle state driver entry point.

  @param[in]  ImageHandle       Image handle of this driver
  @param[in]  SystemTable       A pointer to the EFI System Table.

  @return     EFI_SUCCESS       The protocol is installed successfully.
  @return     Others            Failed to initialize the driver.

**/
EFI_STATUS
LifeCycleStateDriverEntry (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS            Status;
  EFI_HANDLE            LifeCycleStatHandle;
  HECI_FW_STS6_REGISTER MeFirmwareStatus;

  LifeCycleStatHandle = NULL;

  MeFirmwareStatus.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, R_ME_HFS_6));

  if (IsSimicsEnvironment ()) {
    if (PciSegmentRead16 ((PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, 0) + PCI_DEVICE_ID_OFFSET)) == 0xFFFF) {
      DEBUG ((DEBUG_INFO, "HeciBaseAddress Not found! \n"));
      DEBUG ((DEBUG_INFO, "Temp set MeMode in Simics as normal mode! \n"));
      MeFirmwareStatus.r.FpfSocConfigLock = 0;
    }
  }

  mLifeCycleState = (MeFirmwareStatus.r.FpfSocConfigLock == 1) ? StateEndUser : StateManufacturing;


  //
  // Install on a new handle
  //
  Status = gBS->InstallProtocolInterface (
                  &LifeCycleStatHandle,
                  &gLifeCycleStateProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mLifeCycleStateProtocol
                  );

  DEBUG ((DEBUG_INFO, "LifeCycleState Protocol Installation Status = %r\n", Status));

  return Status;
}

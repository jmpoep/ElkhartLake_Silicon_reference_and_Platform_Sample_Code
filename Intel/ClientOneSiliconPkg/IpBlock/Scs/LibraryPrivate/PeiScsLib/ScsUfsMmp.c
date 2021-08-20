/** @file
  Support routines for programming UFS MMP.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Register/ScsUfsRegs.h>
#include "PeiScsInitInternal.h"

/**
  Returns the maximum number of lanes supported by MMP
**/
STATIC
UINT8
MmpGetMaxLanes (
  VOID
  )
{
  return 7;
}

/**
  Configures power gating on MMP lane

  @param[in] SiPolicyPpi     Pointer to SI_POLICY_PPI
  @param[in] PortId        Sideband port id of the MMP
  @param[in] MmpLaneIndex  Lane index of the MMP
**/
STATIC
VOID
MmpLanePowerGatingEnable (
  IN SI_POLICY_PPI  *SiPolicy,
  IN PCH_SBI_PID    PortId,
  IN UINT8          MmpLaneIndex
  )
{
  EFI_STATUS          Status;
  PCH_GENERAL_CONFIG  *PchGeneralConfig;

  Status = GetConfigBlock ((VOID *) SiPolicy, &gPchGeneralConfigGuid, (VOID *) &PchGeneralConfig);
  ASSERT_EFI_ERROR (Status);

  if (PchGeneralConfig->PchMasterPowerGating != 0) {
    MmpPrivateWrite8 (PortId, MmpLaneIndex, R_SCS_PCR_MMPUFS_DLANEX_IMP8_PWRGT, 0x1);
  } else {
    MmpPrivateWrite8 (PortId, MmpLaneIndex, R_SCS_PCR_MMPUFS_DLANEX_IMP8_PWRGT, 0x0);
  }
}

/**
  Initializes MMP lane

  @param[in] PortId        Sideband port id of the MMP
  @param[in] MmpLaneIndex  Lane index of the MMP
**/
STATIC
VOID
MmpLaneInitialize (
  IN PCH_SBI_PID  PortId,
  IN UINT8        MmpLaneIndex
  )
{
  MmpPrivateWrite8 (PortId, MmpLaneIndex, R_SCS_PCR_MMPUFS_DLANEX_TX3_SYNC_LEN, 0x4A);
  MmpPrivateWrite8 (PortId, MmpLaneIndex, R_SCS_PCR_MMPUFS_DLANEX_IMP23_INTFILTER, 0x1);
}

/**
  Writes a 1 byte value to specified MMP Private register

  @param[in] PortId          MMP port id
  @param[in] MmpLaneIndex    MMP lane index
  @param[in] RegisterOffset  Offset of a private register
  @param[in] Value           Value to be written
**/
VOID
MmpPrivateWrite8 (
  IN PCH_SBI_PID  PortId,
  IN UINT8        MmpLaneIndex,
  IN UINT16       RegisterOffset,
  IN UINT8        Value
  )
{
  UINT16  LaneBaseAddress;

  LaneBaseAddress = R_SCS_PCR_MMPUFS_DLANE1 * MmpLaneIndex;

  PchPcrWrite8 (PortId, LaneBaseAddress + RegisterOffset, Value);
  //
  // After writing to private register we have to trigger transaction
  // by writing to configuration update field in IMP22 private register.
  //
  PchPcrAndThenOr32 (
    PortId,
    LaneBaseAddress + R_SCS_PCR_MMPUFS_DLANEX_IMP22,
    (UINT32) ~B_SCS_PCR_MMPUFS_DLANEX_IMP22_CNFGUPD,
    V_SCS_PCR_MMPUFS_DLANEX_IMP22_CNFGUPD << N_SCS_PCR_MMPUFS_DLANEX_IMP22_CNFGUPD
    );
}

/**
  Initializes MMP instance

  @param[in] SiPolicyPpi        Pointer to SI_POLICY_PPI
  @param[in] MmpInstance        MMP instance
**/
VOID
MmpInit (
  IN SI_POLICY_PPI  *SiPolicy,
  IN SCS_UFS_MMP    *MmpInstance
  )
{
  UINT8         MmpLaneIndex;

  if (MmpInstance == NULL) {
    return;
  }
  for (MmpLaneIndex = 0; MmpLaneIndex < MmpGetMaxLanes (); MmpLaneIndex++) {
    if (((MmpInstance->LaneMask >> MmpLaneIndex) & BIT0) != 0) {
      MmpLanePowerGatingEnable (SiPolicy, MmpInstance->PortId, MmpLaneIndex);
      MmpLaneInitialize (MmpInstance->PortId, MmpLaneIndex);
      MmpApplyOverride (MmpInstance->PortId, MmpLaneIndex);
    }
  }
}

/**
  Disables MMP lanes

  @param[in] MmpInstance  MMP instance
**/
VOID
MmpDisable (
  IN SI_POLICY_PPI  *SiPolicy,
  IN SCS_UFS_MMP    *MmpInstance
  )
{
  UINT8  MmpLaneIndex;

  if (MmpInstance == NULL) {
    return;
  }
  for (MmpLaneIndex = 0; MmpLaneIndex < MmpGetMaxLanes (); MmpLaneIndex++) {
    if (((MmpInstance->LaneMask >> MmpLaneIndex) & BIT0) != 0) {
      MmpLanePowerGatingEnable (SiPolicy, MmpInstance->PortId, MmpLaneIndex);
    }
  }
}


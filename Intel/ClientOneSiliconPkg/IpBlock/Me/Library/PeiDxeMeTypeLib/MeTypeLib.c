/** @file
  ME Type library implementeation

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <PiDxe.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/MeTypeLib.h>

#include <Register/MeRegs.h>
#include <Register/HeciRegs.h>


/**
  Get type of firmware running in ME

  @return One of ME_TYPE values is returned.

**/
ME_TYPE
MeTypeGet (
  VOID
  )
{
  HECI_FWS_REGISTER MeHfs;

  MeHfs.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, HECI_BUS, HECI_DEV, HECI_FUN, R_ME_HFS));
  if (MeHfs.ul == 0xFFFFFFFF) {
    return MeTypeUndef;
  }
  if (MeHfs.r.MeOperationMode == ME_OPERATION_MODE_SPS) {
    //
    // Server Platform Services firmware is running in ME
    //
    return MeTypeSps;
  }
  return MeTypeClient;
}


/**
  Verify type of firmware running in ME

  @return TRUE if it is SPS recovery firmware running in ME, otherwise FALSE.

**/
BOOLEAN
MeTypeIsSpsRecovery (
  VOID
  )
{
  HECI_FWS_REGISTER MeHfs;

  MeHfs.ul = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, HECI_BUS, HECI_DEV, HECI_FUN, R_ME_HFS));
  if (MeHfs.ul != 0xFFFFFFFF) {
    return (MeHfs.r.MeOperationMode == ME_OPERATION_MODE_SPS &&
            MeHfs.r.CurrentState == ME_STATE_RECOVERY);
  }
  return FALSE;
}


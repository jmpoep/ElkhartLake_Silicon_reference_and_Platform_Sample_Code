/** @file
  TCC Library.
  All function in this library is available for PEI, DXE, and SMM
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 - 2020 Intel Corporation.

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
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/PchRegsLpcEhl.h>
#include <Library/IoLib.h>
#include <TccConfigSubRegion.h>
#include <TccTuningHob.h>
#include <Library/PchPcrLib.h>
#include <Library/CpuMailboxLib.h>
#include <Library/TimerLib.h>

/**
  Check whether SKU supports Real-Time features

  @retval TRUE                    Real-Time SKU
  @retval FALSE                   Non-Real-Time SKU
**/
BOOLEAN
IsRtSku (
  VOID
  )
{
  UINTN  PchBase;
  UINT16 DeviceId;

  PchBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 0, 0, 0
                 );

  DeviceId = PciSegmentRead16 (PchBase + PCI_DEVICE_ID_OFFSET);
  switch (DeviceId) {
    case V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_8:
    case V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_9:
    case V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_10:
    case V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_11:
    case V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_12:
    case V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_INDU_13:
      return TRUE;
    default:
      return FALSE;
  }
}

/**
  Get the Base Address of Psuedo-Lockable region for LLC QoS.

  @param[in]   Index          The index of the region
**/
UINTN
GetLlcQosRegionAddress (
  UINT8 Index
  )
{
  return BASE_1GB;
}

/**
  Get the Size of Psuedo-Lockable region for LLC QoS.

  @param[in]   Index          The index of the region
**/
UINTN
GetLlcQosRegionSize (
  UINT8 Index
  )
{
  return SIZE_4MB;
}

/**
  Get the optimal region for psuedo-locking LLC to improve QoS.
  Base address and size identified by modeling data of each platform.
  More than one region may be psuedo-lockable.

  @param[in]   Index          The index of the psuedo-lockable region
  @param[out]  LlcQosAddress  Base address of locking region
  @param[out]  LlcQosSize     Size of locking region
**/
VOID
GetLlcQosRegion (
  IN  UINT8 Index,
  OUT UINTN *LlcQosAddress,
  OUT UINTN *LlcQosSize
  )
{
  *LlcQosAddress = GetLlcQosRegionAddress (Index);
  *LlcQosSize    = GetLlcQosRegionSize (Index);

  return;
}

/**
  The number of LLC QoS records to be installed.

  @return The number of LLC QoS records to be installed.
**/
UINT8
GetNumLlcQosRecords (
  VOID
  )
{
  return 1;
}

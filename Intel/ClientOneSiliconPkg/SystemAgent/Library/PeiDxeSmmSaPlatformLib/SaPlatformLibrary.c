/** @file
  SA Platform Lib implementation.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#include "SaPlatformLibrary.h"
#include <Library/PciSegmentLib.h>
#include <SaRegs.h>
#include <Library/CpuPlatformLib.h>
#include <IndustryStandard/Pci22.h>
#include <CpuPcieInfo.h>

/**
  Determine if PCH Link is DMI/OPI

  @param[in] CpuModel             CPU model

  @retval TRUE                    DMI
  @retval FALSE                   OPI
**/
BOOLEAN
IsPchLinkDmi (
  IN CPU_FAMILY  CpuModel
  )
{
  if ((CpuModel == EnumCpuTglDtHalo) || (CpuModel == EnumCpuIclDtHalo)) {
    return TRUE; // DMI
  }
  return FALSE;  // OPI
}


/**
  Returns the number of DMI lanes for current CPU

  @retval UINT8
**/
UINT8
GetMaxDmiLanes (
  )
{
  return SA_DMI_NON_CNL_DT_HALO_MAX_LANE;
}


/**
  Returns the number of DMI bundles for current CPU

  @retval UINT8
**/
UINT8
GetMaxDmiBundles (
  )
{
  return SA_DMI_NON_CNL_DT_HALO_MAX_BUNDLE;
}


/**
  Returns the function numbers for current CPU

  @retval UINT8
**/
UINT8
GetMaxPegFuncs (
  )
{
  return SA_PEG_NON_CNL_H_MAX_FUN;
}


/**
  Returns the number of PEG lanes for current CPU

  @retval UINT8
**/
UINT8
GetMaxPegLanes (
  )
{
  return SA_PEG_NON_CNL_H_MAX_LANE;
}


/**
  Returns the number of PEG bundles for current CPU

  @retval UINT8
**/
UINT8
GetMaxPegBundles (
  )
{
  return  SA_PEG_NON_CNL_H_MAX_BUNDLE;
}

/**
  Checks if PEG port is present

  @retval TRUE     PEG is presented
  @retval FALSE    PEG is not presented
**/
BOOLEAN
IsPegPresent (
  VOID
  )
{
  UINT64  PegBaseAddress;

  PegBaseAddress  = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_PEG_BUS_NUM, SA_PEG_DEV_NUM, 0, 0);
  if (PciSegmentRead16 (PegBaseAddress) != 0xFFFF) {
    return TRUE;
  }
  return FALSE;
}

/**
  Checks if SKU is DisplayOnly

  @retval FALSE  SKU is not DisplayOnly
  @retval TRUE   SKU is DisplayOnly
**/
BOOLEAN
EFIAPI
IsDisplayOnlySku (
  VOID
  )
{
  UINT16           GtDid;

  GtDid           = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_IGD_DEV, SA_IGD_FUN_0, PCI_DEVICE_ID_OFFSET));
  if (GtDid == V_SA_PCI_DEV_2_GT0_JSL_EHL_ID) {
    return TRUE;
  }
  return FALSE;
}


/**
  Checks if SKU is Mobile

  @retval FALSE  SKU is not Mobile
  @retval TRUE   SKU is Mobile
**/
BOOLEAN
EFIAPI
IsMobileSku (
  VOID
  )
{
  UINT16           DeviceId;

  DeviceId = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_DEVICE_ID));
  if (
      (DeviceId == V_SA_DEVICE_ID_EHL_0) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_1) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_2) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_3) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_4) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_5) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_6) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_7) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_8) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_9) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_10) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_11) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_12) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_13) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_14) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_15) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_16) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_17) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_18) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_19) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_20) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_21) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_22) || \
      (DeviceId == V_SA_DEVICE_ID_EHL_23) \
    ) {
    return TRUE;
  }
  return FALSE;
}

/**
  Checks if SKU is Desktop

  @retval FALSE  SKU is not Desktop
  @retval TRUE   SKU is Desktop
**/
BOOLEAN
EFIAPI
IsDesktopSku (
  VOID
  )
{
  UINT16           DeviceId;

  DeviceId = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_DEVICE_ID));
  if (
      (DeviceId == V_SA_DEVICE_ID_ICL_DT_1) || \
      (DeviceId == V_SA_DEVICE_ID_ICL_DT_2) \
    ) {
    return TRUE;
  }
  return FALSE;
}

/**
  Checks if SKU is Halo

  @retval FALSE  SKU is not Halo
  @retval TRUE   SKU is Halo
**/
BOOLEAN
EFIAPI
IsHaloSku (
  VOID
  )
{
  UINT16           DeviceId;

  DeviceId = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_DEVICE_ID));
  if (
      (DeviceId == V_SA_DEVICE_ID_ICL_HALO_1) || \
      (DeviceId == V_SA_DEVICE_ID_ICL_HALO_2) \
    ) {
      return TRUE;
  }
  return FALSE;
}

/**
  Checks if SKU is Server

  @retval FALSE  SKU is not Server
  @retval TRUE   SKU is Server
**/
BOOLEAN
EFIAPI
IsServerSku (
  VOID
  )
{
    return FALSE;
}


/**
  Checks if SAM is enabled or not.

  @retval FALSE  SAM is disabled
  @retval TRUE   SAM is enabled
**/
BOOLEAN
EFIAPI
IsSamEnabled (
  VOID
  )
{
///
///
  return FALSE;
}


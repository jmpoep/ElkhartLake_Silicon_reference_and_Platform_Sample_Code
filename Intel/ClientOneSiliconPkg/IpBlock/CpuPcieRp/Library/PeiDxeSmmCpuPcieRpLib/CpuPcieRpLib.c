/** @file
  CPU PCIe root port library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/CpuPcieInfoLib.h>
#include <PcieRegs.h>
#include <Register/PchRegsClk.h>
#include <Library/CpuPlatformLib.h>
#include <Register/CpuPcieRegs.h>
#include "CpuPcieInfo.h"
#include <Library/CpuPcieRpLib.h>
/**
  Get CPU Pcie Root Port Device and Function Number by Root Port physical Number

  @param[in]  RpNumber              Root port physical number. (0-based)
  @param[out] RpDev                 Return corresponding root port device number.
  @param[out] RpFun                 Return corresponding root port function number.

  @retval     EFI_SUCCESS           Root port device and function is retrieved
  @retval     EFI_INVALID_PARAMETER RpNumber is invalid
**/
EFI_STATUS
EFIAPI
GetCpuPcieRpDevFun (
  IN  UINTN   RpNumber,
  OUT UINTN   *RpDev,
  OUT UINTN   *RpFun
  )
{
  if (RpNumber > GetMaxCpuPciePortNum ()) {
    DEBUG ((DEBUG_ERROR, "GetCpuPcieRpDevFun invalid RpNumber %x", RpNumber));
    ASSERT (FALSE);
    return EFI_INVALID_PARAMETER;
  }
  if (GetCpuFamily() == CPUID_FULL_FAMILY_MODEL_TIGERLAKE_ULT_ULX) { // For TGL - U/Y only one CPU PCIE Root port is present
    *RpDev = 6;
    *RpFun = 0;
    return EFI_SUCCESS;
  }

  switch(RpNumber){
    case 0:
      *RpDev = 6;
      *RpFun = 0;
      break;
    case 1:
      *RpDev = 1;
      *RpFun = 0;
      break;
    case 2:
      *RpDev = 1;
      *RpFun = 1;
      break;
    case 3:
      *RpDev = 1;
      *RpFun = 2;
      break;
    default:
      *RpDev = 6;
      *RpFun = 0;
      break;
  }
  return EFI_SUCCESS;
}

/**
  Get Root Port physical Number by CPU Pcie Root Port Device and Function Number

  @param[in]  RpDev                 Root port device number.
  @param[in]  RpFun                 Root port function number.
  @param[out] RpNumber              Return corresponding physical Root Port index (0-based)

  @retval     EFI_SUCCESS           Physical root port is retrieved
**/
EFI_STATUS
EFIAPI
GetCpuPcieRpNumber (
  IN  UINTN   RpDev,
  IN  UINTN   RpFun,
  OUT UINTN   *RpNumber
  )
{
  UINT64 RpBase;

  //@TODO : This API needs to be tested to make sure it works well for CPU PCIE ports

  RpBase = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, RpDev, RpFun, 0);
  *RpNumber = (PciSegmentRead32 (RpBase + R_PCIE_LCAP) >> B_PCIE_LCAP_PN_OFFSET) -1;
  return EFI_SUCCESS;
}

/**
  Gets pci segment base address of PCIe root port.

  @param RpIndex    Root Port Index (0 based)
  @return PCIe port base address.
**/
UINT64
CpuPcieBase (
  IN  UINT32   RpIndex
  )
{
  UINTN   RpDevice;
  UINTN   RpFunction;
  GetCpuPcieRpDevFun (RpIndex, &RpDevice, &RpFunction);
  return PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, (UINT32) RpDevice, (UINT32) RpFunction, 0);
}

/**
  Determines whether L0s is supported on current stepping.

  @return TRUE if L0s is supported, FALSE otherwise
**/
//@TODO : Check if this API is required for SA - if not remove this API
BOOLEAN
IsCpuPcieL0sSupported (
  VOID
  )
{
  return TRUE;
}

/**
  Some early PCH steppings require Native ASPM to be disabled due to hardware issues:
   - RxL0s exit causes recovery
   - Disabling PCIe L0s capability disables L1
  Use this function to determine affected steppings.

  @return TRUE if Native ASPM is supported, FALSE otherwise
**/
//@TODO : Check if this API is required for CPU PCIe - if not remove this API
BOOLEAN
IsCpuPcieNativeAspmSupported (
  VOID
  )
{
  return IsCpuPcieL0sSupported ();
}

/**
  Determines whether PCIe link is active

  @param[in] RpBase    Root Port base address
  @retval Link Active state
**/
BOOLEAN
CpuPcieIsLinkActive (
  UINT64  RpBase
  )
{
  return !! (PciSegmentRead16 (RpBase + R_PCIE_LSTS) & B_PCIE_LSTS_LA);
}
/** @file
  This code provides a initialization of intel VT-d (Virtualization Technology for Directed I/O).

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _PEI_VTD_INIT_LIB_H_
#define _PEI_VTD_INIT_LIB_H_

///
/// Include files
///
#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PostCodeLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Ppi/SiPolicy.h>
#include <Library/CpuPlatformLib.h>
#include <IndustryStandard/Pci22.h>
#include <IpuPreMemConfig.h>

/**
  Configure VT-d Base and capabilities.

  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI

  @retval EFI_SUCCESS         - Vtd initialization complete
  @exception EFI_UNSUPPORTED  - Vtd is not enabled by policy
**/
EFI_STATUS
VtdInit (
  IN  VTD_CONFIG           *Vtd
  );

/**
  Clear IPU VTD BAR.

  @param[in]   MchBar           MchBar Value
**/
VOID
ClearIpuVtdBar (
  IN  UINTN                MchBar
  );

/**
  Clear DMA Protection set by Boot Guard.

  @param[in]   MchBar           MchBar Value
**/
VOID
ClearDmaProtectionSetByBootGuard (
  IN  UINTN                MchBar
  );


/**
  Configure IGD VTD BAR.
  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI
  @param[in]   MchBar           MchBar Value

  @retval EFI_SUCCESS           Function executed successfully
**/
EFI_STATUS
ConfigureIgdVtdBar (
  IN  VTD_CONFIG           *Vtd,
  IN  UINTN                MchBar
  );

/**
  Configure IPU VTD BAR.

  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI
  @param[in]   MchBar           MchBar Value

  @retval EFI_SUCCESS           Function executed successfully
  @retval EFI_NOT_FOUND         The required PPI could not be located.
**/
EFI_STATUS
ConfigureIpuVtdBar (
  IN  VTD_CONFIG           *Vtd,
  IN  UINTN                MchBar
  );

/**
  Configure IOP VTD BAR.

  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI
  @param[in]   MchBar           MchBar Value

  @retval EFI_SUCCESS           Function executed successfully
**/
EFI_STATUS
ConfigureIopVtdBar (
  IN  VTD_CONFIG           *Vtd,
  IN  UINTN                MchBar
  );

  /**
  Configure VT-d Base and capabilities for IPs available in PostMem.

  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI

  @retval EFI_SUCCESS         - Vtd initialization complete
  @exception EFI_UNSUPPORTED  - Vtd is not enabled by policy
**/
EFI_STATUS
VtdLateInit (
  IN  VTD_CONFIG           *Vtd
  );
/**
  Installs VTD Data Hob

  @retval EFI_SUCCESS           The HOB was successfully created.
  @retval EFI_OUT_OF_RESOURCES  There is no additional space for HOB creation.
**/
EFI_STATUS
InstallVtdDataHob (
  VOID
  );
/**
  Clear ITBT VTD BAR.

  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI
  @param[in]   MchBar           MchBar Value
**/
VOID
ClearITbtVtdBar (
  IN  VTD_CONFIG  *Vtd,
  IN  UINTN          MchBar
  );
/**
  Configure ITbt VTD BAR.

  @param[in]   VTD_CONFIG       VTD config block from SA Policy PPI
  @param[in]   MchBar           MchBar Value

  @retval EFI_SUCCESS           Function executed successfully
**/
EFI_STATUS
ConfigureITbtVtdBar (
  IN  VTD_CONFIG  *Vtd,
  IN  UINTN       MchBar
  );
#endif

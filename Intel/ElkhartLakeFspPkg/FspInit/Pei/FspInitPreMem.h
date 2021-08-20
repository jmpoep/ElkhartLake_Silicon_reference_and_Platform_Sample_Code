/** @file
  Header file for FSP Init Pre-Memory PEI module

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2018 Intel Corporation.

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

@par Specification
**/

#ifndef _FSP_INIT_PRE_MEMORY_H_
#define _FSP_INIT_PRE_MEMORY_H_

#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/CacheAsRamLib.h>
#include <Library/MtrrLib.h>
#include <Library/FspSwitchStackLib.h>
#include <Library/FspCommonLib.h>
#include <Library/FspPlatformLib.h>
#include <Ppi/MemoryDiscovered.h>
#include <Ppi/Reset.h>
#include <Ppi/Reset2.h>
#include <FspEas.h>
#include <FspmUpd.h>
#include <Ppi/MasterBootMode.h>
#include <Library/SiPolicyLib.h>
#include <Library/CpuPolicyLib.h>
#include <Library/PeiSaPolicyLib.h>
#include <Library/PchPolicyLib.h>
#include <Library/PeiMePolicyLib.h>
#include <Library/PeiAmtPolicyLib.h>
#include <Library/MeChipsetLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/StallPpiLib.h>
#include <Register/MeRegs.h>


/**
  This function will be called when MRC is done.

  @param  PeiServices General purpose services available to every PEIM.

  @param  NotifyDescriptor Information about the notify event..

  @param  Ppi The notify context.

  @retval EFI_SUCCESS If the function completed successfully.
**/
EFI_STATUS
EFIAPI
MemoryDiscoveredPpiNotifyCallback (
  IN EFI_PEI_SERVICES          **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN VOID                      *Ppi
  );

/**
  This function handles reset request inside FSP to redirect the flow to BootLoader with Reset
  required status.

  @param  PeiServices General purpose services available to every PEIM.

  @retval EFI_SUCCESS if it completed successfully.
**/
EFI_STATUS
EFIAPI
FspResetSystem (
  IN CONST EFI_PEI_SERVICES **PeiServices
  );

/**
  This function handles reset request inside FSP to redirect the flow to BootLoader with Reset
  required status.

  @param[in] ResetType            UEFI defined reset type.
  @param[in] ResetStatus          The status code for the reset.
  @param[in] DataSize             The size of ResetData in bytes.
  @param[in] ResetData            Optional element used to introduce a platform specific reset.
                                  The exact type of the reset is defined by the EFI_GUID that follows
                                  the Null-terminated Unicode string.

**/
VOID
FspResetSystem2 (
  IN EFI_RESET_TYPE     ResetType,
  IN EFI_STATUS         ResetStatus,
  IN UINTN              DataSize,
  IN VOID               *ResetData OPTIONAL
  );
/**
  This function performs PCH PEI Policy update in pre-memory.

  @param[in, out] SiPreMemPolicy  The SI PreMem Policy PPI instance
  @param[in] FspmUpd              The pointer of FspmUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiPchPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI     *SiPreMemPolicy,
  IN FSPM_UPD                     *FspmUpd
  );

/**
  This function performs CPU PEI Policy initialization in PreMem.

  @param[in, out] SiPreMemPolicyPpi  The Si PreMem Policy PPI instance
  @param[in]      FspmUpd            The pointer of FspmUpd

  @retval EFI_SUCCESS             The PPI is installed and initialized.
  @retval EFI ERRORS              The PPI is not successfully installed.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
FspUpdatePeiCpuPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI       *SiPreMemPolicyPpi,
  IN FSPM_UPD                       *FspmUpd
  );

/**
This function performs Security PEI Policy initialization in PreMem.

@param[in, out] SiPreMemPolicyPpi     The SI Pre-Mem Policy PPI instance
@param[in]      FspmUpd               The pointer of FspmUpd

@retval EFI_SUCCESS             The PPI is installed and initialized.
@retval EFI ERRORS              The PPI is not successfully installed.
@retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
EFIAPI
FspUpdatePeiSecurityPolicyPreMem(
IN OUT  SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi,
IN FSPM_UPD                  *FspmUpd
);

/**
  This function performs Me PEI Policy update in pre-memory.

  @param[in out] SiPreMemPolicy    SI_PREMEM_POLICY_PPI
  @param[in]     FspmUpd           The pointer of FspmUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiMePolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI   *SiPreMemPolicy,
  IN     FSPM_UPD               *FspmUpd
  );

/**
  UpdatePeiSaPolicy performs SA PEI Policy initialization in pre-memory

  @param[in out] SiPreMemPolicy    SI_PREMEM_POLICY_PPI
  @param[in]     FspmUpd           The pointer of FspmUpd

  @retval EFI_SUCCESS              The policy is installed and initialized.
**/
EFI_STATUS
FspUpdatePeiSaPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI   *SiPreMemPolicy,
  IN     FSPM_UPD               *FspmUpd
  );

/**
  This function performs Silicon PEI Policy initialization in pre-memory.

  @param[in, out] SiPreMemPolicy The Silicon Policy PPI instance
  @param[in]      FspmUpd        The pointer of FspmUpd

  @retval EFI_SUCCESS  The function completed successfully
**/
EFI_STATUS
EFIAPI
FspUpdatePeiSiPolicyPreMem (
  IN OUT SI_PREMEM_POLICY_PPI *SiPreMemPolicy,
  IN     FSPM_UPD             *FspmUpd
  );
#endif

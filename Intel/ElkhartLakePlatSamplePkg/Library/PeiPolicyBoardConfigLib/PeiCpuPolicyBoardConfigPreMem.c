/** @file
 Intel PEI CPU Pre-Memory Policy update by board configuration

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2020 Intel Corporation.

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

@par Specification Reference:
**/
#include "PeiPolicyBoardConfig.h"
#include <PlatformNvRamHookLib.h>
#include <Register/Cpuid.h>
#include <Library/TxtLib.h>

#define TXT_SINIT_MEMORY_SIZE         0x50000
#define TXT_HEAP_MEMORY_SIZE          0xF0000

#define GET_OCCUPIED_SIZE(ActualSize, Alignment) \
  ((ActualSize) + (((Alignment) - ((ActualSize) & ((Alignment) - 1))) & ((Alignment) - 1)))

/**
  Searches PEI firmware volume (FV_BB) for file containing BIOS ACM.

  @param[out] BiosAcBase       - A pointer to pointer to variable to hold found address

  @retval EFI_SUCCESS          - If address has been found
  @exception EFI_NOT_FOUND     - If address has not been found
**/
EFI_STATUS
FindBiosAcmInVolume (
  OUT UINT32             **BiosAcmBase
  )
{
  EFI_STATUS                    Status;
  EFI_FIRMWARE_VOLUME_HEADER    *FvHeader;
  EFI_FFS_FILE_HEADER           *FfsHeader;
  UINT32                        ModuleAddr;

  ///
  /// Locate Firmware Volume header
  ///
  FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)(UINTN)FixedPcdGet32 (PcdFlashFvFirmwareBinariesBase);
  Status = PeiServicesFfsFindFileByName (&gStartupAcmPeiFileGuid, FvHeader, (VOID **)&FfsHeader);
  ModuleAddr = (UINT32)((UINT8 *) FfsHeader + sizeof (EFI_FFS_FILE_HEADER));
  *BiosAcmBase = (UINT32 *) ModuleAddr;
  ///
  /// If BIOS ACM is not found - don't hang system. Assume that TXT
  /// must be disabled.
  ///
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to locate BIOS ACM\n"));
    return EFI_NOT_FOUND;
  }
  DEBUG(( DEBUG_ERROR, "ACM Module Location: %x\n", *BiosAcmBase));

  // found Startup ACM; check for 128KB alignment
  ASSERT(((((UINT32)(*BiosAcmBase)) & 0x1FFFF) == 0) ? TRUE : FALSE);

  return EFI_SUCCESS;
}

/**
  Searches FV for Elixir Springs patch.

  @param[out] Patch        - Pointer to patch.
  @param[out] PatchSize        - Patch Size.

  @retval EFI_SUCCESS          - If Patch is found in FV.
  @exception EFI_NOT_FOUND     - If Patch not found.
**/
EFI_STATUS
FindElixirSpringsPatch (
  OUT UINT32 **Patch,
  OUT UINT32 *PatchSize
  )
{
  EFI_STATUS                    Status;
  EFI_FIRMWARE_VOLUME_HEADER    *FvHeader;
  EFI_FFS_FILE_HEADER           *FfsHeader;
  UINT32                        ModuleAddr;
  UINT32                        FileLength;

  ///
  /// Locate Firmware Volume header
  ///
  FvHeader = (EFI_FIRMWARE_VOLUME_HEADER *)(UINTN)FixedPcdGet32 (PcdFlashFvFirmwareBinariesBase);
  Status = PeiServicesFfsFindFileByName (&gElixirSpringsPatchGuid, FvHeader, (VOID **)&FfsHeader);
  ModuleAddr = (UINT32)((UINT8 *) FfsHeader + sizeof (EFI_FFS_FILE_HEADER));
  *Patch = (UINT32 *) ModuleAddr;
  if (IS_FFS_FILE2 (FfsHeader)) {
    FileLength = FFS_FILE2_SIZE (FfsHeader);
    ASSERT (FileLength > 0x00FFFFFF);
  } else {
    FileLength = FFS_FILE_SIZE (FfsHeader);
  }
  *PatchSize = FileLength - sizeof(EFI_FFS_FILE_HEADER);

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to locate Elixir Springs Patch file in FV.\n"));
    return EFI_NOT_FOUND;
  } else {
    DEBUG(( DEBUG_ERROR, "Elixir spring patch Location: 0x%x Size: 0x%x\n", *Patch, *PatchSize));
  }

  return EFI_SUCCESS;
}

/**
  This function performs PEI CPU Pre-Memory Policy update by board configuration.

  @retval EFI_SUCCESS             The SI Policy is successfully updated.
  @retval Others                  The SI Policy is not successfully updated.
**/
EFI_STATUS
EFIAPI
UpdatePeiCpuPolicyBoardConfigPreMem (
  VOID
  )
{
#if FixedPcdGet8(PcdFspModeSelection) == 1
#else
  EFI_STATUS                      Status;
#endif
  UINT8                           TxtAcheckRequest;
  CPUID_VERSION_INFO_ECX          Ecx;
  UINT32                          TxtCapableChipset;
#if FixedPcdGetBool(PcdElixirSpringsPatchBinEnable) == 1
  UINT32                          *ElixirSpringsPatch;
  UINT32                          ElixirSpringsPatchSize;
#endif
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                            *FspmUpd;
#else
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
#if FixedPcdGetBool(PcdElixirSpringsPatchBinEnable) == 1
  CPU_CONFIG_LIB_PREMEM_CONFIG    *CpuConfigLibPreMemConfig;
#endif
  CPU_SECURITY_PREMEM_CONFIG      *CpuSecurityPreMemConfig;
#endif

  DEBUG ((DEBUG_INFO, "Updating CPU Policy by board config in Pre-Mem\n"));

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = NULL;
#else
  SiPreMemPolicyPpi       = NULL;
  CpuSecurityPreMemConfig = NULL;
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = (FSPM_UPD *) PcdGet32 (PcdFspmUpdDataAddress);
  ASSERT (FspmUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR (Status);

#if FixedPcdGetBool(PcdElixirSpringsPatchBinEnable) == 1
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuConfigLibPreMemConfigGuid, (VOID *) &CpuConfigLibPreMemConfig);
  ASSERT_EFI_ERROR (Status);
#endif
  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR(Status);
#endif

  AsmCpuid (CPUID_VERSION_INFO, NULL, NULL, &Ecx.Uint32, NULL);
  TxtCapableChipset = CheckSmxCapabilities ();
  TxtAcheckRequest = GetTxtAliasCheckAndReset () & 1;
#if FixedPcdGetBool(PcdElixirSpringsPatchBinEnable) == 1
  Status = FindElixirSpringsPatch (&ElixirSpringsPatch, &ElixirSpringsPatchSize);
  if (!EFI_ERROR (Status)) {
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ElixirSpringsPatchAddr, CpuConfigLibPreMemConfig->ElixirSpringsPatchAddr, (UINT32)ElixirSpringsPatch);
    UPDATE_POLICY (((FSPM_UPD *) FspmUpd)->FspmConfig.ElixirSpringsPatchSize, CpuConfigLibPreMemConfig->ElixirSpringsPatchSize, ElixirSpringsPatchSize);
  }
#endif

  return EFI_SUCCESS;
}

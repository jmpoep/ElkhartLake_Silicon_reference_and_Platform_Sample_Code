/** @file
 Intel PEI CPU Policy update by board configuration

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2020 Intel Corporation.

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
#include <Library/Tpm2CommandLib.h>
#include <Library/Tpm12CommandLib.h>

/**
  This function is for platform code to provide EC Commands since different BIOS might have different EC.
  Platform code need to provide a function for CPU code to call to communicate with EC.

  @param[in] EcCmdType      - EC Command Type.
  @param[in] EcCmd          - EC Command Byte to send.
  @param[in] SendData       - EC Data Byte to send.
  @param[in] ReceiveData    - EC Data Byte received.

  @retval EFI_SUCCESS          Command Read/ Write Success
  @retval EFI_DEVICE_ERROR     Command Read/ Write Error
  @retval EFI_OUT_OF_RESOURCES No enough resources (such as out of memory).
**/
EFI_STATUS
PlatformSendEcCommand (
  IN EC_COMMAND_TYPE             EcCmdType,
  IN UINT8                       EcCmd,
  IN UINT8                       SendData,
  IN OUT UINT8                   *ReceiveData
  )
{
  EFI_STATUS Status;

  switch (EcCmdType) {
  case SendEcCmds:
    ///
    /// Sends command to Embedded controller.
    ///
    Status = SendEcCommand(EcCmd);
    break;
  case SendEcValue:
    ///
    /// Sends data to Embedded controller.
    ///
    Status = SendEcData(SendData);
    break;
  case ReceiveEcValue:
    ///
    /// Receives data from Embedded controller.
    ///
    Status = ReceiveEcData(ReceiveData);
    break;
  default:
    return EFI_DEVICE_ERROR;
  }

  return Status;
}


/**
  This function performs PEI CPU Policy update by board configuration.

  @retval EFI_SUCCESS             The SI Policy is successfully updated.
  @retval Others                  The SI Policy is not successfully updated.
**/
EFI_STATUS
EFIAPI
UpdatePeiCpuPolicyBoardConfig (
  VOID
  )
{
  EFI_STATUS                      Status;
  SINIT_SVN                       SinitSvn;
  UINTN                           SinitSvnVariableDataSize;
#if FixedPcdGetBool(PcdTxtEnable) == 1
  UINT8                           Tpm12Data[8], *Tpm12DataPtr;
  UINT32                          Tpm12DataSize;
  TPM2B_MAX_BUFFER                Tpm20Data, *Tpm20DataPtr;
#endif
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariableServices;
#if FixedPcdGet8(PcdFspModeSelection) == 1
  VOID                            *FspmUpd;
  VOID                            *FspsUpd;
#else
  SI_PREMEM_POLICY_PPI            *SiPreMemPolicyPpi;
  SI_POLICY_PPI                   *SiPolicyPpi;
  SA_MISC_PEI_PREMEM_CONFIG       *MiscPeiPreMemConfig;
  CPU_SECURITY_PREMEM_CONFIG      *CpuSecurityPreMemConfig;
  CPU_SGX_CONFIG                  *CpuSgxConfig;
#endif

  DEBUG ((DEBUG_INFO, "Updating CPU Policy by board config in Post-Mem\n"));

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = NULL;
  FspsUpd = NULL;
#else
  SiPolicyPpi             = NULL;
  CpuSgxConfig            = NULL;
  SiPreMemPolicyPpi       = NULL;
  MiscPeiPreMemConfig     = NULL;
  CpuSecurityPreMemConfig = NULL;
#endif

#if FixedPcdGet8(PcdFspModeSelection) == 1
  FspmUpd = (FSPM_UPD *) PcdGet32 (PcdFspmUpdDataAddress);
  ASSERT (FspmUpd != NULL);

  FspsUpd = (FSPS_UPD *) PcdGet32 (PcdFspsUpdDataAddress);
  ASSERT (FspsUpd != NULL);
#else
  Status = PeiServicesLocatePpi (&gSiPreMemPolicyPpiGuid, 0, NULL, (VOID **) &SiPreMemPolicyPpi);
  ASSERT_EFI_ERROR(Status);

  Status = PeiServicesLocatePpi (&gSiPolicyPpiGuid, 0, NULL, (VOID **) &SiPolicyPpi);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock ((VOID *)SiPreMemPolicyPpi, &gCpuSecurityPreMemConfigGuid, (VOID *) &CpuSecurityPreMemConfig);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock ((VOID *)SiPreMemPolicyPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
  ASSERT_EFI_ERROR(Status);

  Status = GetConfigBlock ((VOID *)SiPolicyPpi, &gCpuSgxConfigGuid, (VOID *) &CpuSgxConfig);
  ASSERT_EFI_ERROR(Status);
#endif

  //
  // Make sure ReadOnlyVariablePpi is available
  //
  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &VariableServices
             );
  ASSERT_EFI_ERROR(Status);

  //
  // SGX programs SINIT SVN only when TXT is enabled, so this data from TPM is required only when TXT is enabled.
  //
#if FixedPcdGetBool(PcdTxtEnable) == 1
#if FixedPcdGet8(PcdFspModeSelection) == 1
  if (((FSPM_UPD *) FspmUpd)->FspmConfig.TxtImplemented == 1) {
#else
  if (MiscPeiPreMemConfig->TxtImplemented == 1) {
#endif
    if (CompareGuid (PcdGetPtr (PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceTpm20DtpmGuid)) {
      Tpm20DataPtr = &Tpm20Data;
      Status = Tpm2NvRead(TPM20_SGX_NVINDEX, TPM20_SGX_NVINDEX, NULL, 8, 0, Tpm20DataPtr);
      if (!EFI_ERROR(Status)) {
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SgxSinitDataFromTpm, CpuSgxConfig->SgxSinitDataFromTpm, Tpm20Data.buffer[0]);
      }
    }

    if (CompareGuid (PcdGetPtr (PcdTpmInstanceGuid), &gEfiTpmDeviceInstanceTpm12Guid)) {
      Tpm12DataPtr = &Tpm12Data[0];
      Tpm12DataSize = 8;
      Status = Tpm12NvReadValue (TPM12_SGX_NVINDEX, 0, &Tpm12DataSize, Tpm12DataPtr);
      if (!EFI_ERROR (Status)) {
        UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SgxSinitDataFromTpm, CpuSgxConfig->SgxSinitDataFromTpm, Tpm12Data[0]);
      }
    }
  }
#endif

  /// Initialize UEFI Variable
  SinitSvnVariableDataSize = sizeof (SINIT_SVN);
  Status = VariableServices->GetVariable (
             VariableServices,
             SINIT_SVN_VARIABLE_NAME,
             &gSinitSvnGuid,
             NULL,
             &SinitSvnVariableDataSize,
             &SinitSvn
             );

  if (Status == EFI_NOT_FOUND) {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SgxSinitNvsData, CpuSgxConfig->SgxSinitNvsData, 0);
#if FixedPcdGet8(PcdFspModeSelection) == 1
    DEBUG ((DEBUG_INFO, "SINIT SV SVN:: NV Variable Not Found. Programming SINIT SE SVN value = %x\n", ((FSPS_UPD *) FspsUpd)->FspsConfig.SgxSinitNvsData));
#else
    DEBUG ((DEBUG_INFO, "SINIT SV SVN:: NV Variable Not Found. Programming SINIT SE SVN value = %x\n", CpuSgxConfig->SgxSinitNvsData));
#endif
  } else {
    UPDATE_POLICY (((FSPS_UPD *) FspsUpd)->FspsConfig.SgxSinitNvsData, CpuSgxConfig->SgxSinitNvsData, SinitSvn.SvnNumber);
#if FixedPcdGet8(PcdFspModeSelection) == 1
    DEBUG ((DEBUG_INFO, "SINIT SV SVN:: NV Variable Found. Programming SINIT SE SVN value = %x\n", ((FSPS_UPD *) FspsUpd)->FspsConfig.SgxSinitNvsData));
#else
    DEBUG ((DEBUG_INFO, "SINIT SV SVN:: NV Variable Found. Programming SINIT SE SVN value = %x\n", CpuSgxConfig->SgxSinitNvsData));
#endif
  }

  return Status;
}

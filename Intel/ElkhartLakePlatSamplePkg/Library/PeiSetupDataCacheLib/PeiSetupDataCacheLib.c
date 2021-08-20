/** @file
  Main implementation source file for the support of caching the "Setup" variable.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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

#include "PeiSetupDataCacheLib.h"


EFI_PEI_READ_ONLY_VARIABLE2_PPI mNewVariablePpi = {
  NewGetVariable,
  NewNextVariableName
};

EFI_PEI_PPI_DESCRIPTOR     mNewVariablePpiList = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPeiReadOnlyVariable2PpiGuid,
  &mNewVariablePpi
};

/**
  This service retrieves a variable's value using its name and GUID.

  Read the specified variable from the UEFI variable store. If the Data
  buffer is too small to hold the contents of the variable, the error
  EFI_BUFFER_TOO_SMALL is returned and DataSize is set to the required buffer
  size to obtain the data.

  @param[in]      This                  A pointer to this instance of the EFI_PEI_READ_ONLY_VARIABLE2_PPI.
  @param[in]      VariableName          A pointer to a null-terminated string that is the variable's name.
  @param[in]      VariableGuid          A pointer to an EFI_GUID that is the variable's GUID. The combination of
                                        VariableGuid and VariableName must be unique.
  @param[out]     Attributes            If non-NULL, on return, points to the variable's attributes.
  @param[in, out] DataSize              On entry, points to the size in bytes of the Data buffer.
                                        On return, points to the size of the data returned in Data.
  @param[out]     Data                  Points to the buffer which will hold the returned variable value.

  @retval         EFI_SUCCESS           The variable was read successfully.
  @retval         EFI_NOT_FOUND         The variable could not be found.
  @retval         EFI_BUFFER_TOO_SMALL  The DataSize is too small for the resulting data.
                                        DataSize is updated with the size required for
                                        the specified variable.
  @retval         EFI_INVALID_PARAMETER VariableName, VariableGuid, DataSize or Data is NULL.
  @retval         EFI_DEVICE_ERROR      The variable could not be retrieved because of a device error.
**/
EFI_STATUS
EFIAPI
NewGetVariable (
  IN CONST  EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
  IN CONST  CHAR16                          *VariableName,
  IN CONST  EFI_GUID                        *VariableGuid,
  OUT       UINT32                          *Attributes,
  IN OUT    UINTN                           *DataSize,
  OUT       VOID                            *Data
  )
{
  SETUP_DATA_HOB              *SetupDataHob;
  EFI_STATUS                  Status;
  PEI_READ_WRITE_VARIABLE_PPI *ReadWriteVariable;

  Status = PeiServicesLocatePpi (
                  &gPeiReadWriteVariablePpiGuid,
                  0,
                  NULL,
                  (VOID** ) &ReadWriteVariable
                  );

  if (Status == EFI_SUCCESS) {
    return ReadWriteVariable->GetVariable (
                                (CHAR16 *)VariableName,
                                (EFI_GUID *)VariableGuid,
                                Attributes,
                                DataSize,
                                Data
                                );
  }

  if (VariableName == NULL || VariableGuid == NULL || DataSize == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  SetupDataHob = (SETUP_DATA_HOB *)(VOID *)GetFirstGuidHob (&gSetupDataHobGuid);
  ASSERT (SetupDataHob != NULL);
  if (SetupDataHob == NULL) {
    return EFI_NOT_FOUND;
  }

  SetupDataHob->TotalCnt++;

  if ((StrCmp (VariableName, L"Setup") == 0) &&
       CompareGuid (VariableGuid, &gSetupVariableGuid)) {
    SetupDataHob->CacheCnt++;

    if (*DataSize < sizeof (SETUP_DATA)) {
      *DataSize = sizeof (SETUP_DATA);
      return EFI_BUFFER_TOO_SMALL;
    }

    if (Attributes != NULL) {
      *Attributes = SetupDataHob->SetupAttributes;
    }
    *DataSize = sizeof (SETUP_DATA);
    CopyMem (Data, &SetupDataHob->SetupData, sizeof(SETUP_DATA));
    return EFI_SUCCESS;
  }

  if ((StrCmp (VariableName, L"SaSetup") == 0) &&
       CompareGuid (VariableGuid, &gSaSetupVariableGuid)) {
    SetupDataHob->CacheCnt++;

    if (*DataSize < sizeof (SA_SETUP)) {
      *DataSize = sizeof (SA_SETUP);
      return EFI_BUFFER_TOO_SMALL;
    }

    if (Attributes != NULL) {
      *Attributes = SetupDataHob->SaAttributes;
    }
    *DataSize = sizeof (SA_SETUP);
    CopyMem (Data, &SetupDataHob->SaSetup, sizeof(SA_SETUP));
    return EFI_SUCCESS;
  }

  if ((StrCmp (VariableName, L"MeSetup") == 0) &&
       CompareGuid (VariableGuid, &gMeSetupVariableGuid)) {
    SetupDataHob->CacheCnt++;

    if (*DataSize < sizeof (ME_SETUP)) {
      *DataSize = sizeof (ME_SETUP);
      return EFI_BUFFER_TOO_SMALL;
    }

    if (Attributes != NULL) {
      *Attributes = SetupDataHob->MeAttributes;
    }
    *DataSize = sizeof (ME_SETUP);
    CopyMem (Data, &SetupDataHob->MeSetup, sizeof(ME_SETUP));
    return EFI_SUCCESS;
  }

  if ((StrCmp (VariableName, L"CpuSetup") == 0) &&
       CompareGuid (VariableGuid, &gCpuSetupVariableGuid)) {
    SetupDataHob->CacheCnt++;

    if (*DataSize < sizeof (CPU_SETUP)) {
      *DataSize = sizeof (CPU_SETUP);
      return EFI_BUFFER_TOO_SMALL;
    }

    if (Attributes != NULL) {
      *Attributes = SetupDataHob->CpuAttributes;
    }
    *DataSize = sizeof (CPU_SETUP);
    CopyMem (Data, &SetupDataHob->CpuSetup, sizeof(CPU_SETUP));
    return EFI_SUCCESS;
  }

  if ((StrCmp (VariableName, L"PchSetup") == 0) &&
       CompareGuid (VariableGuid, &gPchSetupVariableGuid)) {
    SetupDataHob->CacheCnt++;

    if (*DataSize < sizeof (PCH_SETUP)) {
      *DataSize = sizeof (PCH_SETUP);
      return EFI_BUFFER_TOO_SMALL;
    }

    if (Attributes != NULL) {
      *Attributes = SetupDataHob->PchAttributes;
    }
    *DataSize = sizeof (PCH_SETUP);
    CopyMem (Data, &SetupDataHob->PchSetup, sizeof(PCH_SETUP));
    return EFI_SUCCESS;
  }

  return SetupDataHob->VariablePpi->GetVariable (
                         This,
                         VariableName,
                         VariableGuid,
                         Attributes,
                         DataSize,
                         Data
                         );
}


/**
  Return the next variable name and GUID.

  This function is called multiple times to retrieve the VariableName
  and VariableGuid of all variables currently available in the system.
  On each call, the previous results are passed into the interface,
  and, on return, the interface returns the data for the next
  interface. When the entire variable list has been returned,
  EFI_NOT_FOUND is returned.

  @param[in]      This                  A pointer to this instance of the EFI_PEI_READ_ONLY_VARIABLE2_PPI.
  @param[in, out] VariableNameSize      On entry, points to the size of the buffer pointed to by VariableName.
                                        On return, the size of the variable name buffer.
  @param[in, out] VariableName          On entry, a pointer to a null-terminated string that is the variable's name.
                                        On return, points to the next variable's null-terminated name string.
  @param[in, out] VariableGuid          On entry, a pointer to an EFI_GUID that is the variable's GUID.
                                        On return, a pointer to the next variable's GUID.

  @retval         EFI_SUCCESS           The variable was read successfully.
  @retval         EFI_NOT_FOUND         The variable could not be found.
  @retval         EFI_BUFFER_TOO_SMALL  The VariableNameSize is too small for the resulting
                                        data. VariableNameSize is updated with the size
                                        required for the specified variable.
  @retval         EFI_INVALID_PARAMETER VariableName, VariableGuid or
                                        VariableNameSize is NULL.
  @retval         EFI_DEVICE_ERROR      The variable could not be retrieved because of a device error.
**/
EFI_STATUS
EFIAPI
NewNextVariableName (
  IN CONST  EFI_PEI_READ_ONLY_VARIABLE2_PPI *This,
  IN OUT UINTN                              *VariableNameSize,
  IN OUT CHAR16                             *VariableName,
  IN OUT EFI_GUID                           *VariableGuid
  )
{
  SETUP_DATA_HOB              *SetupDataHob;
  EFI_STATUS                  Status;
  PEI_READ_WRITE_VARIABLE_PPI *ReadWriteVariable;

  Status = PeiServicesLocatePpi (
                  &gPeiReadWriteVariablePpiGuid,
                  0,
                  NULL,
                  (VOID** ) &ReadWriteVariable
                  );

  if (Status == EFI_SUCCESS) {
    return ReadWriteVariable->GetNextVariableName (
                                VariableNameSize,
                                VariableName,
                                VariableGuid
                                );
  }

  SetupDataHob = (SETUP_DATA_HOB *)(VOID *)GetFirstGuidHob (&gSetupDataHobGuid);
  ASSERT (SetupDataHob != NULL);
  if (SetupDataHob == NULL) {
    return EFI_NOT_FOUND;
  }

  return SetupDataHob->VariablePpi->NextVariableName (
                                      This,
                                      VariableNameSize,
                                      VariableName,
                                      VariableGuid
                                      );
}

/**
  Notification function of Read Only Variable2 PPI.

  @retval     EFI_SUCCESS      SetupDataHob already exists, or was successfully (re)installed
  @retval     Others           Error status return
**/
EFI_STATUS
EFIAPI
SetupDataCacheInit (
  VOID
  )
{
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *VariablePpi;
  EFI_PEI_PPI_DESCRIPTOR          *OldVariablePpiList;
  UINTN                           VarSize;
  UINTN                           SaVarSize;
  UINTN                           MeVarSize;
  UINTN                           CpuVarSize;
  UINTN                           PchVarSize;
  SETUP_DATA_HOB                  *SetupDataHob;
  EFI_STATUS                      Status;

  SetupDataHob = (SETUP_DATA_HOB *)(VOID *)GetFirstGuidHob (&gSetupDataHobGuid);
  if (SetupDataHob != NULL) {
    //
    // SetupDataHob already created
    //
    return EFI_SUCCESS;
  }

  Status = PeiServicesLocatePpi (
                         &gEfiPeiReadOnlyVariable2PpiGuid,
                         0,
                         &OldVariablePpiList,
                         (VOID **) &VariablePpi
                         );
  if (EFI_ERROR(Status)) {
    ASSERT_EFI_ERROR(Status);
    return Status;
  }

  Status = PeiServicesCreateHob (
                         EFI_HOB_TYPE_GUID_EXTENSION,
                         sizeof (SETUP_DATA_HOB),
                         (VOID **) &SetupDataHob
                         );
  if (EFI_ERROR(Status)) {
    ASSERT_EFI_ERROR(Status);
    return Status;
  }

  CopyMem(&SetupDataHob->Header.Name, &gSetupDataHobGuid, sizeof(EFI_GUID));
  SetMem ((VOID *)&SetupDataHob->SetupData, sizeof(SETUP_DATA), 0);
  SetMem ((VOID *)&SetupDataHob->SaSetup, sizeof(SA_SETUP), 0);
  SetMem ((VOID *)&SetupDataHob->MeSetup, sizeof(ME_SETUP), 0);
  SetMem ((VOID *)&SetupDataHob->CpuSetup, sizeof(CPU_SETUP), 0);
  SetMem ((VOID *)&SetupDataHob->PchSetup, sizeof(PCH_SETUP), 0);
  SetupDataHob->VariablePpi = VariablePpi;
  SetupDataHob->TotalCnt = 0;
  SetupDataHob->CacheCnt = 0;

  VarSize = sizeof (SETUP_DATA);
  Status = VariablePpi->GetVariable (
                          VariablePpi,
                          L"Setup",
                          &gSetupVariableGuid,
                          &SetupDataHob->SetupAttributes,
                          &VarSize,
                          &SetupDataHob->SetupData
                          );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  SaVarSize = sizeof (SA_SETUP);
  Status = VariablePpi->GetVariable (
                          VariablePpi,
                          L"SaSetup",
                          &gSaSetupVariableGuid,
                          &SetupDataHob->SaAttributes,
                          &SaVarSize,
                          &SetupDataHob->SaSetup
                          );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  MeVarSize = sizeof (ME_SETUP);
  Status = VariablePpi->GetVariable (
                          VariablePpi,
                          L"MeSetup",
                          &gMeSetupVariableGuid,
                          &SetupDataHob->MeAttributes,
                          &MeVarSize,
                          &SetupDataHob->MeSetup
                          );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  CpuVarSize = sizeof (CPU_SETUP);
  Status = VariablePpi->GetVariable (
                          VariablePpi,
                          L"CpuSetup",
                          &gCpuSetupVariableGuid,
                          &SetupDataHob->CpuAttributes,
                          &CpuVarSize,
                          &SetupDataHob->CpuSetup
                          );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  PchVarSize = sizeof (PCH_SETUP);
  Status = VariablePpi->GetVariable (
                          VariablePpi,
                          L"PchSetup",
                          &gPchSetupVariableGuid,
                          &SetupDataHob->PchAttributes,
                          &PchVarSize,
                          &SetupDataHob->PchSetup
                          );
  if (EFI_ERROR(Status)) {
    return Status;
  }

  ASSERT ((VarSize == sizeof(SETUP_DATA)) &&
          (SaVarSize == sizeof(SA_SETUP)) &&
          (MeVarSize == sizeof(ME_SETUP)) &&
          (CpuVarSize == sizeof(CPU_SETUP)) &&
          (PchVarSize == sizeof(PCH_SETUP))
         );
  if ((VarSize == sizeof(SETUP_DATA)) &&
      (SaVarSize == sizeof(SA_SETUP)) &&
      (MeVarSize == sizeof(ME_SETUP)) &&
      (CpuVarSize == sizeof(CPU_SETUP)) &&
      (PchVarSize == sizeof(PCH_SETUP))) {
    Status = PeiServicesReInstallPpi (
                                (CONST EFI_PEI_PPI_DESCRIPTOR *)OldVariablePpiList,
                                (CONST EFI_PEI_PPI_DESCRIPTOR *)&mNewVariablePpiList
                                );
    ASSERT_EFI_ERROR(Status);
  }

  return Status;
}


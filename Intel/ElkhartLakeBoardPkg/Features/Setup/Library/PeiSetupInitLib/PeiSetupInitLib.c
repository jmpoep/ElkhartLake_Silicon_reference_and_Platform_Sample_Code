/** @file
  Implementation of Setup variable initialization in PEI.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include <PiPei.h>
#include <SetupVariable.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/PeiServicesLib.h>
#include <Library/SetupInitLib.h>
#include <Library/UefiVariableDefaultHobLib.h>
#include <Library/UefiVariableHelperLib.h>
#include <Ppi/ReadOnlyVariable2.h>

VARIABLE_ENTRY_CONSISTENCY mSetupVariableList[] = {
  // GUID                   Name         Data Size
  { &gSetupVariableGuid,    L"Setup",    sizeof(SETUP_DATA) },
  { &gSaSetupVariableGuid,  L"SaSetup",  sizeof(SA_SETUP)   },
  { &gCpuSetupVariableGuid, L"CpuSetup", sizeof(CPU_SETUP)  },
  { &gPchSetupVariableGuid, L"PchSetup", sizeof(PCH_SETUP)  },
  { &gMeSetupVariableGuid,  L"MeSetup",  sizeof(ME_SETUP)   }
};

typedef union {
  SETUP_DATA SetupData;
  CPU_SETUP  CpuSetup;
  ME_SETUP   MeSetup;
  SA_SETUP   SaSetup;
  PCH_SETUP  PchSetup;
} SETUP_VAR_DATA;

/**
  Update variable revision field value.

  @param[in]      Offset         The field offset of the variable data structure.
  @param[in]      Revision       An unsigned integer represent the revision value.
  @param[in]      *VarName       A pointer to a unicode string represent the varaibel name.
  @param[in]      *VarGuid       A pointer to a GUID represnet the variable GUID.
  @param[in]      VarSize        A usnsigned integer that represent the variable size in byte.

  @retval         EFI_SUCCESS    the value is updated successfully.
**/
EFI_STATUS
EFIAPI
UpdateSetupVariableRevision (
  IN UINTN      Offset,
  IN UINT8      Revision,
  IN CHAR16     *VarName,
  IN EFI_GUID   *VarGuid,
  IN UINTN      VarSize
  )
{
  EFI_STATUS      Status;
  UINTN           VarDataSize;
  SETUP_VAR_DATA  VarData;
  UINT8           *RevisionPtr;

  VarDataSize = VarSize;

  Status = GetVariableFromHob (
                  VarName,
                  VarGuid,
                  NULL,
                  &VarDataSize,
                  &VarData
                  );

  if (Status == EFI_BUFFER_TOO_SMALL) {
    DEBUG ((DEBUG_ERROR, "VarDataSize =  : %x\n", VarDataSize));
    Status = GetVariableFromHob (
                  VarName,
                  VarGuid,
                  NULL,
                  &VarDataSize,
                  &VarData
                  );
  }
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Get variable from hob failed : %r\n", Status));
    DEBUG ((DEBUG_ERROR, "Variable Name : %s, GUID : %g\n", VarName, VarGuid));
    return Status;
  }

  RevisionPtr = (UINT8 *) (VOID *) &VarData + Offset;
  *RevisionPtr = Revision;

  Status = SetVariableToHob (
                  VarName,
                  VarGuid,
                  NULL,
                  VarDataSize,
                  &VarData
                  );

  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Set variable to hob failed : %r\n", Status));
    DEBUG ((DEBUG_ERROR, "Variable Name : %s, GUID : %g\n", VarName, VarGuid));
  }

  return Status;
}

/**
  Updates the Setup variable revision for the Setup structures.

  @retval         EFI_SUCCESS    The revision for the Setup structures was updated successfully.
**/
EFI_STATUS
EFIAPI
UpdateAllSetupVariableRevisions (
  VOID
  )
{
  EFI_STATUS Status;

  Status = UpdateSetupVariableRevision (
             OFFSET_OF (SETUP_DATA, Revision),
             SETUP_DATA_REVISION,
             PLATFORM_SETUP_VARIABLE_NAME,
             &gSetupVariableGuid,
             sizeof (SETUP_DATA)
             );
  ASSERT_EFI_ERROR (Status);

  //
  // Set SETUP variable revision.
  //
  Status = UpdateSetupVariableRevision (
             OFFSET_OF (ME_SETUP, Revision),
             ME_SETUP_REVISION,
             L"MeSetup",
             &gMeSetupVariableGuid,
             sizeof (ME_SETUP)
             );
  ASSERT_EFI_ERROR (Status);

  Status = UpdateSetupVariableRevision (
             OFFSET_OF (CPU_SETUP, Revision),
             CPU_SETUP_REVISION,
             L"CpuSetup",
             &gCpuSetupVariableGuid,
             sizeof (CPU_SETUP)
             );
  ASSERT_EFI_ERROR (Status);

  Status = UpdateSetupVariableRevision (
             OFFSET_OF (SA_SETUP, Revision),
             SA_SETUP_REVISION,
             L"SaSetup",
             &gSaSetupVariableGuid,
             sizeof (SA_SETUP)
             );
  ASSERT_EFI_ERROR (Status);

  Status = UpdateSetupVariableRevision (
             OFFSET_OF (PCH_SETUP, Revision),
             PCH_SETUP_REVISION,
             L"PchSetup",
             &gPchSetupVariableGuid,
             sizeof (PCH_SETUP)
             );
  ASSERT_EFI_ERROR (Status);

  Status = UpdateSetupVariableRevision (
             OFFSET_OF (SI_SETUP, Revision),
             SI_SETUP_REVISION,
             L"SiSetup",
             &gSiSetupVariableGuid,
             sizeof (SI_SETUP)
             );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Patch default setup variable hob for PEI pre-memory phase.

  @param[in]      ConfigPatchStruct      setup variable data default patch table
  @param[in]      ConfigPatchStructSize  size of setup variable data default patch table
**/
VOID
EFIAPI
PatchSetupConfigurationDataPreMem (
  IN CONFIG_PATCH_STRUCTURE  *ConfigPatchStruct,
  IN UINTN                   ConfigPatchStructSize
  )
{
  CONFIG_PATCH_TABLE  *ConfigPatchTable;
  SETUP_VAR_DATA      Data;
  UINTN               DataSize;
  UINTN               StructIndex;
  UINTN               TableIndex;
  EFI_STATUS          Status;
  UINT32              Attributes;
  DEBUG ((DEBUG_INFO, "PatchConfigurationData\n"));
  for (StructIndex = 0; StructIndex < ConfigPatchStructSize; StructIndex++) {

    ConfigPatchTable = ConfigPatchStruct[StructIndex].ConfigPatchTable;
    if (ConfigPatchTable == NULL) {
      continue;
    }

    DataSize = ConfigPatchStruct[StructIndex].VarSize;
    Status = GetVariableFromHob (ConfigPatchStruct[StructIndex].VarName,  ConfigPatchStruct[StructIndex].VarGuid, &Attributes, &DataSize, &Data);
    DEBUG ((DEBUG_INFO, "Patch Begin - %s\n", ConfigPatchStruct[StructIndex].VarName));
    DEBUG ((DEBUG_INFO, "ConfigPatchTableSize : 0x%x\n",ConfigPatchStruct[StructIndex].ConfigPatchTableSize));
    for (TableIndex = 0; TableIndex < ConfigPatchStruct[StructIndex].ConfigPatchTableSize; TableIndex++) {
      DEBUG ((DEBUG_INFO, "  Offset - 0x%x, Size - 0x%x, Data - ", ConfigPatchTable[TableIndex].Offset, ConfigPatchTable[TableIndex].Size));
      {
        UINTN Index;
        UINT8 *DumpData;
        DumpData = (UINT8 *)&ConfigPatchTable[TableIndex].Data;
        for (Index = 0; Index < ConfigPatchTable[TableIndex].Size; Index++) {
          DEBUG ((DEBUG_INFO, "%02x ", DumpData[Index]));
        }
      }
      DEBUG ((DEBUG_INFO, "\n"));
      CopyMem ((UINT8 *)(VOID*)&Data + ConfigPatchTable[TableIndex].Offset, &ConfigPatchTable[TableIndex].Data, ConfigPatchTable[TableIndex].Size);
    }

    Status = SetVariableToHob (ConfigPatchStruct[StructIndex].VarName, ConfigPatchStruct[StructIndex].VarGuid, &Attributes, DataSize, &Data);
    ASSERT_EFI_ERROR (Status);
    DEBUG ((DEBUG_INFO, "Patch End - %s\n", ConfigPatchStruct[StructIndex].VarName));
  }

  return;
}

/**
  Checks if Setup UEFI variables are found in the UEFI variable store.

  @retval BOOLEAN   Indicates whether the UEFI variable was found.

**/
BOOLEAN
EFIAPI
IsSetupStructuresFound (
  VOID
  )
{
  EFI_STATUS                      Status;
  UINTN                           Size;
  UINTN                           VariableIndex;
  SETUP_VAR_DATA                  Setup;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *PeiReadOnlyVariablePpi;

  Status = PeiServicesLocatePpi (
             &gEfiPeiReadOnlyVariable2PpiGuid,
             0,
             NULL,
             (VOID **) &PeiReadOnlyVariablePpi
             );
  if (EFI_ERROR (Status)) {
    return FALSE;
  }

  for (
    VariableIndex = 0;
    VariableIndex < (sizeof (mSetupVariableList) / sizeof (mSetupVariableList[0]));
    VariableIndex++
    ) {
    Size = sizeof (SETUP_VAR_DATA);
    Status = PeiReadOnlyVariablePpi->GetVariable (
                                       PeiReadOnlyVariablePpi,
                                       mSetupVariableList[VariableIndex].Name,
                                       mSetupVariableList[VariableIndex].Guid,
                                       NULL,
                                       &Size,
                                       &Setup
                                       );
    if (EFI_ERROR (Status)) {
      return FALSE;
    }
    DEBUG ((
      DEBUG_INFO,
      "Found setup variable %s - %g.\n",
      mSetupVariableList[VariableIndex].Name,
      mSetupVariableList[VariableIndex].Guid
      ));
  }

  return TRUE;
}

/**
  Prints all Setup UEFI variables located in the UEFI variable store.

  @retval EFI_SUCCESS   An error did not occur located the UEFI variables and printing the contents.
  @retval Others        An error occurred locating the UEFI variables.

**/
EFI_STATUS
EFIAPI
PrintSetupStructures (
  VOID
  )
{
  DEBUG_CODE_BEGIN();
    EFI_STATUS                      Status;
    UINTN                           Size;
    UINTN                           VariableIndex;
    SETUP_VAR_DATA                  Setup;
    EFI_PEI_READ_ONLY_VARIABLE2_PPI *PeiReadOnlyVariablePpi;

    Status = PeiServicesLocatePpi (
               &gEfiPeiReadOnlyVariable2PpiGuid,
               0,
               NULL,
               (VOID **) &PeiReadOnlyVariablePpi
               );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    for (
      VariableIndex = 0;
      VariableIndex < sizeof (mSetupVariableList) / sizeof (mSetupVariableList[0]);
      VariableIndex++
      ) {
      Size = sizeof (SETUP_VAR_DATA);
      Status = PeiReadOnlyVariablePpi->GetVariable (
                                         PeiReadOnlyVariablePpi,
                                         mSetupVariableList[VariableIndex].Name,
                                         mSetupVariableList[VariableIndex].Guid,
                                         NULL,
                                         &Size,
                                         &Setup
                                         );
      if (EFI_ERROR (Status)) {
        return Status;
      }
      DEBUG ((DEBUG_INFO, "\nDumping %s:", mSetupVariableList[VariableIndex].Name));
      PrintVariableData ((UINT8 *) &Setup, Size);
    }
  DEBUG_CODE_END();

  return EFI_SUCCESS;
}

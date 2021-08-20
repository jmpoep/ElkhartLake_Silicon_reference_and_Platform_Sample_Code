/** @file
  Implementation of DxeBoardConfigLib.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/


#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PcdLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/BoardConfigLib.h>
#include <Library/PchPcieRpLib.h>
#include <Register/PchPcieRpRegs.h>
#include <Register/PchRegs.h>
#include <PcieRegs.h>
#include <Library/PciSegmentLib.h>

/**
  Update board configure patch table.

  @param[in, out]  TargetPatchTable      Target patch table you want to be updated.
  @param[in, out]  TargetPatchTableSize  Target patch table size that you want to be updated.
  @param[in]       SourcePatchTable      Source patch table.
  @param[in]       SourcePatchTableSize  Source patch table size.

**/
VOID
UpdatePatchTable (
  IN OUT CONFIG_PATCH_STRUCTURE **TargetPatchTable,
  IN OUT UINTN                  *TargetPatchTableSize,
  IN     CONFIG_PATCH_STRUCTURE *SourcePatchTable,
  IN     UINTN                  SourcePatchTableSize
  )
{
  UINTN                  TargetIndex;
  UINTN                  SourceIndex;
  CONFIG_PATCH_STRUCTURE *TargetPatchItem;
  CONFIG_PATCH_STRUCTURE *SourcePatchItem;

  if ((TargetPatchTable == NULL) || (TargetPatchTableSize == NULL) || (SourcePatchTable == NULL)) {
    ASSERT_EFI_ERROR (EFI_INVALID_PARAMETER);
    return;
  }

  //
  // If TargetPatchTable isn't initialized before, must clone TargetPatchTable from SourcePatchTable
  //
  if ((*TargetPatchTable == NULL) || (*TargetPatchTableSize == 0)) {
    *TargetPatchTable = AllocateCopyPool (
                          SourcePatchTableSize * sizeof (CONFIG_PATCH_STRUCTURE),
                          SourcePatchTable
                          );
    ASSERT (*TargetPatchTable != NULL);
    *TargetPatchTableSize = SourcePatchTableSize;
    for (
      TargetIndex = 0, TargetPatchItem = *TargetPatchTable, SourcePatchItem = SourcePatchTable;
      TargetIndex < *TargetPatchTableSize;
      TargetIndex++, TargetPatchItem++, SourcePatchItem++)
    {
      TargetPatchItem->VarName = AllocateCopyPool (StrSize (SourcePatchItem->VarName), SourcePatchItem->VarName);
      ASSERT (TargetPatchItem->VarName != NULL);
      TargetPatchItem->VarGuid = AllocateCopyPool (sizeof (EFI_GUID), SourcePatchItem->VarGuid);
      ASSERT (TargetPatchItem->VarGuid != NULL);
      if (TargetPatchItem->ConfigPatchTable != NULL) {
        TargetPatchItem->ConfigPatchTable = AllocateCopyPool (
                                              SourcePatchItem->ConfigPatchTableSize * sizeof (CONFIG_PATCH_TABLE),
                                              SourcePatchItem->ConfigPatchTable
                                              );
        ASSERT (TargetPatchItem->ConfigPatchTable != NULL);
      }
    }
    return;
  }

  //
  // If TargetPatchTable has been initialized before, must Update TargetPatchTable from SourcePatchTable
  // 1. Update TargetPatchItem from SourcePatchItem that VarName and VarGuid are existed in TargetPatchTable
  //
  for (TargetIndex = 0, TargetPatchItem = *TargetPatchTable; TargetIndex < *TargetPatchTableSize; TargetIndex++, TargetPatchItem++) {
    for (SourceIndex = 0, SourcePatchItem = SourcePatchTable; SourceIndex < SourcePatchTableSize; SourceIndex++, SourcePatchItem++) {
      //
      // Find VarGuid and VarName in SourcePatchItem are matched them in TargetPatchItem.
      //
      if (StrnCmp (TargetPatchItem->VarName, SourcePatchItem->VarName, StrLen (TargetPatchItem->VarName)) != 0) {
        continue;
      }
      if (!CompareGuid (TargetPatchItem->VarGuid, SourcePatchItem->VarGuid)) {
        continue;
      }

      //
      // Clone new TargetPatchItem->ConfigPatchTable from SourcePatchItem->ConfigPatchTable
      //
      if ((TargetPatchItem->ConfigPatchTable == NULL) && (SourcePatchItem->ConfigPatchTable != NULL)) {
        TargetPatchItem->ConfigPatchTable = AllocateCopyPool (
                                              SourcePatchItem->ConfigPatchTableSize * sizeof (CONFIG_PATCH_TABLE),
                                              SourcePatchItem->ConfigPatchTable
                                              );
        ASSERT (TargetPatchItem->ConfigPatchTable != NULL);
        TargetPatchItem->ConfigPatchTableSize = SourcePatchItem->ConfigPatchTableSize;
        continue;

      //
      // Update current TargetPatchItem->ConfigPatchTable from SourcePatchItem->ConfigPatchTable
      //
      } else if ((TargetPatchItem->ConfigPatchTable != NULL) && (SourcePatchItem->ConfigPatchTable != NULL)) {
        TargetPatchItem->ConfigPatchTable = ReallocatePool (
                                              TargetPatchItem->ConfigPatchTableSize * sizeof (CONFIG_PATCH_TABLE),
                                              (TargetPatchItem->ConfigPatchTableSize + SourcePatchItem->ConfigPatchTableSize) * sizeof (CONFIG_PATCH_TABLE),
                                              TargetPatchItem->ConfigPatchTable
                                              );
        ASSERT (TargetPatchItem->ConfigPatchTable != NULL);
        CopyMem (
          TargetPatchItem->ConfigPatchTable + TargetPatchItem->ConfigPatchTableSize,
          SourcePatchItem->ConfigPatchTable,
          SourcePatchItem->ConfigPatchTableSize * sizeof (CONFIG_PATCH_TABLE)
          );
        TargetPatchItem->ConfigPatchTableSize += SourcePatchItem->ConfigPatchTableSize;
        continue;
      }
    }
  }

  //
  // If TargetPatchTable has been initialized before, must Update TargetPatchTable from SourcePatchTable
  // 2. Insert new SourcePatchItem that VarGuid and VarName aren't existed in TargetPatchTable.
  //
  for (SourceIndex = 0, SourcePatchItem = SourcePatchTable; SourceIndex < SourcePatchTableSize; SourceIndex++, SourcePatchItem++) {
    //
    // Confirm VarGuid and VarName in SourcePatchItem aren't existed in TargetPatchTable.
    //
    if ((SourcePatchItem->ConfigPatchTable == NULL) || (SourcePatchItem->ConfigPatchTableSize == 0)) {
      continue;
    }
    for (TargetIndex = 0, TargetPatchItem = *TargetPatchTable; TargetIndex < *TargetPatchTableSize; TargetIndex++, TargetPatchItem++) {
      if ((StrnCmp (TargetPatchItem->VarName, SourcePatchItem->VarName, StrLen (TargetPatchItem->VarName)) == 0) &&
           CompareGuid (TargetPatchItem->VarGuid, SourcePatchItem->VarGuid)) {
        break;
      }
    }
    if (TargetIndex != *TargetPatchTableSize) {
      continue;
    }

    //
    // Insert TargetPatchItem from SourcePatchItem
    //
    *TargetPatchTable = ReallocatePool (
                          (*TargetPatchTableSize) * sizeof (CONFIG_PATCH_STRUCTURE),
                          ((*TargetPatchTableSize) + 1) * sizeof (CONFIG_PATCH_STRUCTURE),
                          *TargetPatchTable
                          );
    ASSERT (*TargetPatchTable != NULL);

    TargetPatchItem                   = *TargetPatchTable + *TargetPatchTableSize;
    CopyMem (TargetPatchItem, SourcePatchItem, sizeof (CONFIG_PATCH_STRUCTURE));

    //
    // Update TargetPatchItem->VarName from SourcePatchItem->VarName
    //
    TargetPatchItem->VarName = AllocateCopyPool (
                                 StrSize (SourcePatchItem->VarName),
                                 SourcePatchItem->VarName
                                 );
    ASSERT (TargetPatchItem->VarName != NULL);

    //
    // Update TargetPatchItem->VarGuid from SourcePatchItem->VarGuid
    //
    TargetPatchItem->VarGuid = AllocateCopyPool (
                                 sizeof (EFI_GUID),
                                 SourcePatchItem->VarGuid
                                 );
    ASSERT (TargetPatchItem->VarGuid != NULL);

    //
    // Update TargetPatchItem->ConfigPatchTable from SourcePatchItem->ConfigPatchTable
    //
    TargetPatchItem->ConfigPatchTable = AllocateCopyPool (
                                          SourcePatchItem->ConfigPatchTableSize * sizeof (CONFIG_PATCH_TABLE),
                                          SourcePatchItem->ConfigPatchTable
                                          );
    ASSERT (TargetPatchItem->ConfigPatchTable != NULL);

    *TargetPatchTableSize += 1;
  }
}

/**
  Free unused patch table.

  @param[in, out]  PatchTable             Patch table you want to free memory.
  @param[in, out]  PatchTableSize         Patch table size that you want to free memory.

**/
VOID
FreePatchTable (
  IN OUT CONFIG_PATCH_STRUCTURE **PatchTable,
  IN OUT UINTN                  *PatchTableSize
  )
{
  UINTN Index;

  for (Index = 0; Index < *PatchTableSize; Index++) {
    if ((*PatchTable)[Index].VarName != NULL) {
      FreePool ((*PatchTable)[Index].VarName);
    }
    if ((*PatchTable)[Index].VarGuid != NULL) {
      FreePool ((*PatchTable)[Index].VarGuid);
    }
    if ((*PatchTable)[Index].ConfigPatchTable != NULL) {
      FreePool ((*PatchTable)[Index].ConfigPatchTable);
    }
  }
  if (*PatchTable != NULL) {
    FreePool (*PatchTable);
    *PatchTable     = NULL;
    *PatchTableSize = 0;
  }
}

/**
  Check if given rootport has device connected and enable wake capability

  @param[in]  RpNum           An unsigned integer represent the root port number.

  @retval                     TRUE if endpoint was connected
  @retval                     FALSE if no endpoint was detected
**/
BOOLEAN
IsPcieEndPointPresent (
  IN UINT8 RpNum
  )
{
  EFI_STATUS    Status;
  UINTN         RpDev;
  UINTN         RpFun;
  UINT64        RpBaseAddress;

  Status = GetPchPcieRpDevFun (RpNum, &RpDev, &RpFun);
  if (!EFI_ERROR (Status)) {
    //
    // check if device is present
    //
    RpBaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                      DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      RpDev,
                      RpFun,
                      0
                      );

    if ((PciSegmentRead16 (RpBaseAddress) != 0xFFFF) &&
        (PciSegmentRead16 (RpBaseAddress + R_PCH_PCIE_CFG_SLSTS) & B_PCIE_SLSTS_PDS)) {
      return TRUE;
    }
  }

  return FALSE;
}

/**
  prepare setup variable default patch table for DXE phase

  @param[in]      ConfigPatchStruct      setup variable data default patch table
  @param[in]      ConfigPatchStructSize  size of setup variable data default patch table

  @retval         EFI_SUCCESS            The function completed successfully.
**/
EFI_STATUS
PatchConfigurationDataInit (
  IN CONFIG_PATCH_STRUCTURE  *ConfigPatchStruct,
  IN UINTN                   ConfigPatchStructSize
  )
{
  EFI_STATUS                 Status;
  CONFIG_PATCH_TABLE         *SetupConfigPatchTableTemp;
  CONFIG_PATCH_TABLE         *SaSetupConfigPatchTableTemp;
  CONFIG_PATCH_TABLE         *CpuSetupConfigPatchTableTemp;
  CONFIG_PATCH_TABLE         *PchSetupConfigPatchTableTemp;
  CONFIG_PATCH_TABLE         *MeSetupConfigPatchTableTemp;
  CONFIG_PATCH_TABLE         *ConfigPatchTable;
  UINTN                      StructIndex;
  UINTN                      DataSize;

  DEBUG ((EFI_D_INFO, "PatchConfigurationDataInit\n"));

  Status = EFI_SUCCESS;

  for (StructIndex = 0; StructIndex < ConfigPatchStructSize; StructIndex++) {

    ConfigPatchTable = ConfigPatchStruct[StructIndex].ConfigPatchTable;
    if (ConfigPatchTable == NULL) {
      continue;
    }

    DataSize = ConfigPatchStruct[StructIndex].ConfigPatchTableSize * sizeof (CONFIG_PATCH_TABLE);

    if (StrnCmp (L"Setup", ConfigPatchStruct[StructIndex].VarName, StrLen (ConfigPatchStruct[StructIndex].VarName)) == 0) {
      Status = gBS->AllocatePool (EfiBootServicesData, DataSize, (VOID **) &SetupConfigPatchTableTemp);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      CopyMem (SetupConfigPatchTableTemp, ConfigPatchTable, DataSize);
      PcdSet64S (PcdSetupConfigPatchTable, (UINT64) SetupConfigPatchTableTemp);
      PcdSet64S (PcdSetupConfigPatchTableSize, (UINT64) ConfigPatchStruct[StructIndex].ConfigPatchTableSize);
    }

    if (StrnCmp (L"SaSetup", ConfigPatchStruct[StructIndex].VarName, StrLen (ConfigPatchStruct[StructIndex].VarName)) == 0) {
      Status = gBS->AllocatePool (EfiBootServicesData, DataSize, (VOID **) &SaSetupConfigPatchTableTemp);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      CopyMem (SaSetupConfigPatchTableTemp, ConfigPatchTable, DataSize);
      PcdSet64S (PcdSaSetupConfigPatchTable, (UINT64) SaSetupConfigPatchTableTemp);
      PcdSet64S (PcdSaSetupConfigPatchTableSize, (UINT64) ConfigPatchStruct[StructIndex].ConfigPatchTableSize);
    }

    if (StrnCmp (L"CpuSetup", ConfigPatchStruct[StructIndex].VarName, StrLen (ConfigPatchStruct[StructIndex].VarName)) == 0) {
      Status = gBS->AllocatePool (EfiBootServicesData, DataSize, (VOID **) &CpuSetupConfigPatchTableTemp);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      CopyMem (CpuSetupConfigPatchTableTemp, ConfigPatchTable, DataSize);
      PcdSet64S (PcdCpuSetupConfigPatchTable, (UINT64) CpuSetupConfigPatchTableTemp);
      PcdSet64S (PcdCpuSetupConfigPatchTableSize, (UINT64) ConfigPatchStruct[StructIndex].ConfigPatchTableSize);
    }

    if (StrnCmp (L"PchSetup", ConfigPatchStruct[StructIndex].VarName, StrLen (ConfigPatchStruct[StructIndex].VarName)) == 0) {
      Status = gBS->AllocatePool (EfiBootServicesData, DataSize, (VOID **) &PchSetupConfigPatchTableTemp);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      CopyMem (PchSetupConfigPatchTableTemp, ConfigPatchTable, DataSize);
      PcdSet64S (PcdPchSetupConfigPatchTable, (UINT64) PchSetupConfigPatchTableTemp);
      PcdSet64S (PcdPchSetupConfigPatchTableSize, (UINT64) ConfigPatchStruct[StructIndex].ConfigPatchTableSize);
    }

    if (StrnCmp (L"MeSetup", ConfigPatchStruct[StructIndex].VarName, StrLen (ConfigPatchStruct[StructIndex].VarName)) == 0) {
      Status = gBS->AllocatePool (EfiBootServicesData, DataSize, (VOID **) &MeSetupConfigPatchTableTemp);
      if (EFI_ERROR (Status)) {
        return Status;
      }
      CopyMem (MeSetupConfigPatchTableTemp, ConfigPatchTable, DataSize);
      PcdSet64S (PcdMeSetupConfigPatchTable, (UINT64) MeSetupConfigPatchTableTemp);
      PcdSet64S (PcdMeSetupConfigPatchTableSize, (UINT64) ConfigPatchStruct[StructIndex].ConfigPatchTableSize);
    }

  }

  return Status;
}
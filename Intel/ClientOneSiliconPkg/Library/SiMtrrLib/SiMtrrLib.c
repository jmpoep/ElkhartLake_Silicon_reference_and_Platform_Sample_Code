/** @file
  Provides Silicon code function for MTRRs programming.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/
#include "SiMtrr.h"

/**
  Function attempts to update MTRRs setting buffer
  and remove needless MTRRs to save variable MTRRs numbers.

  @param[in, out]  MtrrSetting - A buffer holding all MTRRs content.
**/
VOID
EFIAPI
MtrrUpdateVariableMtrrs (
  IN OUT MTRR_SETTINGS  *MtrrSetting
  )
{
  EFI_STATUS             Status;
  UINTN                  Index;
  UINTN                  PatchIndex;
  UINTN                  VariableMtrrCount;
  UINTN                  UpdatedMtrrNumber;
  UINT64                 MtrrBase;
  UINT64                 MtrrSize;
  UINT64                 McD2BaseAddress;
  UINT64                 GtApertureAdr;
  UINT64                 MtrrValidAddressMask;
  UINT64                 MtrrValidBitsMask;

  MTRR_MEMORY_CACHE_TYPE MemoryType;
  UPDATED_VARIABLE_MTRR MtrrPatchTable[] = {
  // BaseAddress, Length (0 means calculated by MtrrMask), OrgMtrrType,         ChgMtrrType,      IsValid
    {0xff000000,  0x01000000,                              CacheWriteProtected, CacheUncacheable, TRUE}, //Flash
    {0x00,        0x00000000,                              CacheWriteCombining, CacheUncacheable, FALSE} //InternalGraphics
  };

  DEBUG ((DEBUG_INFO, "Silicon MTRR Update MTRRs Setting Start\n"));

  MtrrLibInitializeMtrrMask (&MtrrValidBitsMask, &MtrrValidAddressMask);
  UpdatedMtrrNumber = sizeof (MtrrPatchTable) / sizeof (UPDATED_VARIABLE_MTRR);
  GtApertureAdr = 0;
  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  //
  // If device 0:2:0 (Internal Graphics Device, or GT) is not present, skip it.
  //
  if ((PciSegmentRead16 (McD2BaseAddress + R_SA_IGD_VID) != 0xFFFF)) {
    PciSegmentReadBuffer (McD2BaseAddress + R_SA_IGD_GMADR, sizeof (UINT64), &GtApertureAdr);
    MtrrPatchTable[InternalGraphics].BaseAddress = GtApertureAdr & MtrrValidAddressMask;
    MtrrPatchTable[InternalGraphics].Valid       = TRUE;
  }

  VariableMtrrCount = GetVariableMtrrCount ();
  for (Index = 0; Index < VariableMtrrCount; Index++) {
    MtrrBase  = (MtrrSetting->Variables.Mtrr[Index].Base & (~(SIZE_4KB - 1)));
    MemoryType = MtrrGetMemoryAttribute (MtrrSetting->Variables.Mtrr[Index].Base);

    for (PatchIndex = 0; PatchIndex < UpdatedMtrrNumber; PatchIndex++) {
      if ((MtrrPatchTable[PatchIndex].Valid == TRUE) &&
          (MtrrBase == MtrrPatchTable[PatchIndex].BaseAddress) &&
          (MemoryType == MtrrPatchTable[PatchIndex].OrgMtrrType)) {
        if (MtrrPatchTable[PatchIndex].Length == 0) {
          MtrrSize = (MtrrSetting->Variables.Mtrr[Index].Mask) & ~((UINT64)(0xFFF));
          MtrrPatchTable[PatchIndex].Length = (~MtrrSize + 1) & MtrrValidAddressMask;
        }
        Status = MtrrSetMemoryAttributeInMtrrSettings (
                   MtrrSetting,
                   MtrrPatchTable[PatchIndex].BaseAddress,
                   MtrrPatchTable[PatchIndex].Length,
                   MtrrPatchTable[PatchIndex].ChgMtrrType
                 );
        ASSERT_EFI_ERROR (Status);
        MtrrPatchTable[PatchIndex].Valid = FALSE;
        break;
      }
    }
  }

  DEBUG ((DEBUG_INFO, "Silicon MTRR Update MTRRs Setting End\n"));
}

/**
  This function attempts to set the attributes into MTRR setting buffer.

  @param[in, out] MtrrSetting   - A buffer holding all MTRRs content.
  @param[in]      Touud         - Top of Upper Usable DRAM
  @param[in]      Ranges        - Array holding memory type settings.
  @param[in]      RangeCount    - Memory range count in the array.

  @retval EFI_SUCCESS           - The function completed successfully.
  @retval EFI_OUT_OF_RESOURCES  - Array is full.
**/
EFI_STATUS
EFIAPI
SiSetMemoryAttributesInMtrrSettings (
  IN OUT MTRR_SETTINGS      *MtrrSetting,
  IN     UINT64             Touud,
  IN     MTRR_MEMORY_RANGE  *Ranges,
  IN     UINTN              RangeCount
  )
{
  EFI_STATUS        Status;
  UINTN             Index;
  UINTN             TailIndex;
  UINT64            Base;
  UINT64            TopHighMemory;

  TailIndex = 0;
  for (Index = 0; Index < RangeCount; Index++) {
    Status = MtrrSetMemoryAttributeInMtrrSettings (
               MtrrSetting,
               Ranges[Index].BaseAddress,
               Ranges[Index].Length,
               Ranges[Index].Type
               );
    if (EFI_ERROR (Status)) {
      return Status;
    }
    // Looking for latest CacheWriteBack
    if (Ranges[Index].Type == CacheWriteBack) {
      TailIndex = Index;
    }
  }

  //
  // Set above 4GB Mmio space to Uncacheable
  //
  if (PcdGet64 (PcdAbove4GBMmioSize) > 0) {
    Status = MtrrSetMemoryAttributeInMtrrSettings (
               MtrrSetting,
               PcdGet64 (PcdAbove4GBMmioBase),
               PcdGet64 (PcdAbove4GBMmioSize),
               CacheUncacheable
               );
    if (EFI_ERROR (Status)) {
      return Status;
    }
  }

  //
  // Sometime we don't have enough Mtrrs to cover all memory in PEI.
  // Try to cover it here.
  //
  if (Touud > (Ranges[TailIndex].BaseAddress + Ranges[TailIndex].Length)) {
    TopHighMemory = GetPowerOfTwo64 (Touud);
    if (TopHighMemory != (Touud)) {
      TopHighMemory = LShiftU64 (TopHighMemory, 1);
    }
    if (Ranges[TailIndex].BaseAddress < SIZE_4GB) {
      Base = SIZE_4GB;
    } else {
      Base = Ranges[TailIndex].BaseAddress;
    }
    while ((TopHighMemory > (Ranges[TailIndex].BaseAddress + Ranges[TailIndex].Length)) && (TopHighMemory > Base)) {
      Status = MtrrSetMemoryAttributeInMtrrSettings (
                 MtrrSetting,
                 Base,
                 TopHighMemory - Base,
                 CacheWriteBack
                 );
      if (Status == EFI_SUCCESS) {
        break;
      } else {
        DEBUG ((DEBUG_ERROR, "Set to TOUUD Memory Attribute: %r %016X-%016X\n", Status, Base, TopHighMemory));
        DEBUG ((DEBUG_ERROR, " [TOUUD:%016X]Reduce size and try again.\n", Touud));
      }
      TopHighMemory = RShiftU64 (TopHighMemory, 1);
    }
  }

  return EFI_SUCCESS;
}

/**
  Function attempts to and update MTRRs Setting.

  @param[out]  MtrrSetting      - A buffer holding all MTRRs content.

  @retval EFI_SUCCESS           - The function completed successfully.
  @retval EFI_UNSUPPORTED       - Mtrr is not supported.
  @retval EFI_INVALID_PARAMETER - MtrrSetting is NULL.
**/
EFI_STATUS
EFIAPI
MtrrTransfer2DefaultWB (
  OUT MTRR_SETTINGS  *MtrrSetting
  )
{
  EFI_STATUS        Status;
  MTRR_SETTINGS     NewMtrrs;
  UINTN             RangeCount;
  UINT32            VariableMtrrCount;
  UINT64_STRUCT     Touud;
  UINT64            McD0BaseAddress;
  UINT64            MtrrValidBitsMask;
  UINT64            MtrrValidAddressMask;
  MTRR_MEMORY_RANGE RawVariableRanges[MTRR_NUMBER_OF_VARIABLE_MTRR];
  MTRR_MEMORY_RANGE Ranges[MTRR_NUMBER_OF_VARIABLE_MTRR];

  DEBUG ((DEBUG_INFO, "Silicon MTRR Transfer to Default WriteBack Start\n"));

  if (!IsMtrrSupported ()) {
    return EFI_UNSUPPORTED;
  }

  if (MtrrSetting == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  ZeroMem (MtrrSetting, sizeof (MTRR_SETTINGS));
  MtrrGetAllMtrrs (MtrrSetting);

  VariableMtrrCount = GetVariableMtrrCount ();
  DEBUG ((DEBUG_INFO, "\n"));
  MtrrDebugPrintAllMtrrs ();

  MtrrUpdateVariableMtrrs (MtrrSetting);

  MtrrLibInitializeMtrrMask (&MtrrValidBitsMask, &MtrrValidAddressMask);
  Ranges[0].BaseAddress = 0;
  Ranges[0].Length      = MtrrValidBitsMask + 1;
  Ranges[0].Type        = (MTRR_MEMORY_CACHE_TYPE)(MtrrSetting->MtrrDefType & 0x07); //[Bits 2:0] Default Memory Type.
  RangeCount = 1;

  MtrrLibGetRawVariableRanges (
    &MtrrSetting->Variables, VariableMtrrCount,
    MtrrValidBitsMask, MtrrValidAddressMask, RawVariableRanges
    );

  MtrrLibApplyVariableMtrrs (
    RawVariableRanges, VariableMtrrCount,
    Ranges, ARRAY_SIZE (Ranges), &RangeCount
    );

  McD0BaseAddress   = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, 0);
  Touud.Data32.Low  = PciSegmentRead32 (McD0BaseAddress + R_SA_TOUUD);
  Touud.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_TOUUD + 4);
  Touud.Data        = Touud.Data & B_SA_TOUUD_TOUUD_MASK;

  //
  // Reset all MTRR setting.
  //
  ZeroMem (&NewMtrrs, sizeof (MTRR_SETTINGS));

  //
  // Default Cachable attribute will be set to WB to support large memory size/hot plug memory
  //
  NewMtrrs.MtrrDefType &= ~((UINT64)(0xFF));
  NewMtrrs.MtrrDefType |= (UINT64) CacheWriteBack;
  DEBUG_CODE (
    //
    // Copy origin fixed mtrrs to make sure debug log is correct.
    //
    CopyMem (&NewMtrrs.Fixed, &MtrrSetting->Fixed, sizeof (MTRR_VARIABLE_SETTINGS));
  );
  Status = SiSetMemoryAttributesInMtrrSettings (&NewMtrrs, Touud.Data, Ranges, RangeCount);
  if (Status == EFI_OUT_OF_RESOURCES) {
    //
    // If there is no enough MTRR to configure with default WB setting, it will be switched to default UC setting.
    //
    ZeroMem (&NewMtrrs, sizeof (MTRR_SETTINGS));
    NewMtrrs.MtrrDefType = MtrrSetting->MtrrDefType;
    Status = SiSetMemoryAttributesInMtrrSettings (&NewMtrrs, Touud.Data, Ranges, RangeCount);
  }
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (Status == EFI_SUCCESS) {
    // Update Mtrrs variables and default type
    CopyMem (&MtrrSetting->Variables, &NewMtrrs.Variables, sizeof (MTRR_VARIABLE_SETTINGS));
    MtrrSetting->MtrrDefType = NewMtrrs.MtrrDefType;
  }
  MtrrSetAllMtrrs (MtrrSetting);

  MtrrDebugPrintAllMtrrs ();

  DEBUG ((DEBUG_INFO, "Silicon MTRR Transfer to Default WriteBack End\n"));
  return EFI_SUCCESS;
}


/** @file
  This file provides services for PEI policy default initialization

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
#include <Library/GpioLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/CpuPcieLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PreSiliconEnvDetectLib.h>
#include <Library/PeiMemPolicyLib.h>
#ifdef FSP_FLAG
#include <Library/FspCommonLib.h>
#endif
#include <TwoLmConfig.h>
#include <CpuPcieRpConfig.h>


#define DEFAULT_OPTION_ROM_TEMP_BAR            0x80000000
#define DEFAULT_OPTION_ROM_TEMP_MEM_LIMIT      0xC0000000

//
// Function call to Load defaults for Individial IP Blocks
//
/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadSaMiscPeiPreMemDefault (
  IN   VOID          *ConfigBlockPointer
  )
{
  SA_MISC_PEI_PREMEM_CONFIG            *MiscPeiPreMemConfig;

  MiscPeiPreMemConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "MiscPeiPreMemConfig->Header.GuidHob.Name = %g\n", &MiscPeiPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "MiscPeiPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", MiscPeiPreMemConfig->Header.GuidHob.Header.HobLength));
  //
  // Policy initialization commented out here is because it's the same with default 0 and no need to re-do again.
  //
  MiscPeiPreMemConfig->LockPTMregs                      = 1;

  //
  // Initialize the Platform Configuration
  //
  MiscPeiPreMemConfig->MchBar              = (UINT32) PcdGet64 (PcdMchBaseAddress);

  MiscPeiPreMemConfig->DmiBar              = 0xFEDA0000;
  MiscPeiPreMemConfig->EpBar               = 0xFEDA1000;
  MiscPeiPreMemConfig->EdramBar            = 0xFED80000;
  MiscPeiPreMemConfig->SmbusBar            = 0xEFA0;
  MiscPeiPreMemConfig->TsegSize            = PcdGet32 (PcdTsegSize);
  MiscPeiPreMemConfig->RegBar              = PcdGet32 (PcdRegBarBaseAddress);


  ///
  /// Initialize the DataPtr for S3 resume
  ///
  MiscPeiPreMemConfig->S3DataPtr = NULL;
#if FixedPcdGetBool(PcdTxtEnable) == 1
#ifndef FSP_FLAG
  MiscPeiPreMemConfig->TxtImplemented = 1;
#else
  if (GetFspGlobalDataPointer()->FspMode == FSP_IN_DISPATCH_MODE) {
    MiscPeiPreMemConfig->TxtImplemented = 0;
  }
#endif
#endif
  MiscPeiPreMemConfig->OpRomScanTempMmioBar      = DEFAULT_OPTION_ROM_TEMP_BAR;
  MiscPeiPreMemConfig->OpRomScanTempMmioLimit    = DEFAULT_OPTION_ROM_TEMP_MEM_LIMIT;
  MiscPeiPreMemConfig->EnableAbove4GBMmio = 1;
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadSaMiscPeiDefault (
  IN   VOID          *ConfigBlockPointer
  )
{
  SA_MISC_PEI_CONFIG        *MiscPeiConfig;
  CPU_FAMILY                CpuFamilyId;
  CPU_STEPPING              CpuStepping;

  CpuFamilyId = GetCpuFamily ();
  CpuStepping = GetCpuStepping ();

  MiscPeiConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "MiscPeiConfig->Header.GuidHob.Name = %g\n", &MiscPeiConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "MiscPeiConfig->Header.GuidHob.Header.HobLength = 0x%x\n", MiscPeiConfig->Header.GuidHob.Header.HobLength));

  if ((CpuFamilyId == EnumCpuIclUltUlx) && (CpuStepping == EnumIclA0)) {
    MiscPeiConfig->Device4Enable = 1;
  }
}



/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
LoadPramPrememDefault (
  IN VOID    *ConfigBlockPointer
  )
{
  PRAM_PREMEM_CONFIG        *PramPreMemConfig;
  PramPreMemConfig = ConfigBlockPointer;
  DEBUG ((DEBUG_INFO, "PramPreMemConfig->Header.GuidHob.Name = %g\n", &PramPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PramPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PramPreMemConfig->Header.GuidHob.Header.HobLength));
}



static COMPONENT_BLOCK_ENTRY  mSaIpBlocksPreMem [] = {
  {&gSaMiscPeiPreMemConfigGuid,       sizeof (SA_MISC_PEI_PREMEM_CONFIG),  SA_MISC_PEI_PREMEM_CONFIG_REVISION,  LoadSaMiscPeiPreMemDefault},
  {&gPramPreMemConfigGuid,            sizeof (PRAM_PREMEM_CONFIG),         PRAM_PREMEM_CONFIG_REVISION,         LoadPramPrememDefault},
  {&gMemoryConfigGuid,                sizeof (MEMORY_CONFIGURATION),       MEMORY_CONFIG_REVISION,              LoadMemConfigDefault},
  {&gMemoryConfigNoCrcGuid,           sizeof (MEMORY_CONFIG_NO_CRC),       MEMORY_CONFIG_REVISION,              LoadMemConfigNoCrcDefault}
};

static COMPONENT_BLOCK_ENTRY  mSaIpBlocks [] = {
  {&gSaMiscPeiConfigGuid,       sizeof (SA_MISC_PEI_CONFIG),   SA_MISC_PEI_CONFIG_REVISION,      LoadSaMiscPeiDefault}
};

/**
  Get SA config block table total size.

  @retval     Size of SA config block table
**/
UINT16
EFIAPI
SaGetConfigBlockTotalSize (
  VOID
  )
{
  return GetComponentConfigBlockTotalSize (&mSaIpBlocks[0], sizeof (mSaIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  Get SA config block table total size.

  @retval      Size of SA config block table
**/
UINT16
EFIAPI
SaGetConfigBlockTotalSizePreMem (
  VOID
  )
{
  return GetComponentConfigBlockTotalSize (&mSaIpBlocksPreMem[0], sizeof (mSaIpBlocksPreMem) / sizeof (COMPONENT_BLOCK_ENTRY));
}

/**
  SaAddConfigBlocksPreMem add all SA config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SaAddConfigBlocksPreMem (
  IN VOID           *ConfigBlockTableAddress
  )
{
  EFI_STATUS  Status;

  DEBUG ((DEBUG_INFO, "SA AddConfigBlocks. TotalBlockCount = 0x%x\n",  sizeof (mSaIpBlocksPreMem) / sizeof (COMPONENT_BLOCK_ENTRY)));
  Status = AddComponentConfigBlocks (ConfigBlockTableAddress, &mSaIpBlocksPreMem[0], sizeof (mSaIpBlocksPreMem) / sizeof (COMPONENT_BLOCK_ENTRY));
  if (Status == EFI_SUCCESS) {
    SaLoadSamplePolicyPreMem (ConfigBlockTableAddress);
  }
  return Status;
}

/**
  SaAddConfigBlocks add all SA config blocks.

  @param[in] ConfigBlockTableAddress    The pointer to add SA config blocks

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
EFIAPI
SaAddConfigBlocks (
  IN VOID           *ConfigBlockTableAddress
  )
{
  DEBUG ((DEBUG_INFO, "SA AddConfigBlocks. TotalBlockCount = 0x%x\n",  sizeof (mSaIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY)));

  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mSaIpBlocks[0], sizeof (mSaIpBlocks) / sizeof (COMPONENT_BLOCK_ENTRY));
}

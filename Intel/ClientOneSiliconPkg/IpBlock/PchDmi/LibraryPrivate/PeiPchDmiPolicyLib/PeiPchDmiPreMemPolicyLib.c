/** @file
  This file provides services for PchDmi PreMem policy function

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
#include <Library/DebugLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Ppi/SiPolicy.h>
#include <PchDmiConfig.h>

/**
  Print PCH_DMI_PREMEM_CONFIG and serial out.

  @param[in] SiPreMemPolicyPpi            Pointer to a SI_PREMEM_POLICY_PPI
**/
VOID
PchDmiPreMemPrintConfig (
  IN SI_PREMEM_POLICY_PPI     *SiPreMemPolicyPpi
  )
{
  EFI_STATUS            Status;
  PCH_DMI_PREMEM_CONFIG *PchDmiPreMemConfig;
  UINT32                Index;

  Status = GetConfigBlock ((VOID *) SiPreMemPolicyPpi, &gPchDmiPreMemConfigGuid, (VOID *) &PchDmiPreMemConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ DMI PreMem Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " TestDmiRtlepceb= %x\n", PchDmiPreMemConfig->TestDmiRtlepceb));
  DEBUG ((DEBUG_INFO, " TestDmiUpPortTranPresetEn= %x\n", PchDmiPreMemConfig->TestDmiUpPortTranPresetEn));
  DEBUG ((DEBUG_INFO, " TestDmiMeUmaRootSpaceCheck= %x\n", PchDmiPreMemConfig->TestDmiMeUmaRootSpaceCheck));
  for (Index = 0; Index < PCH_MAX_DMI_LANES; Index++) {
    DEBUG ((DEBUG_INFO, " Lane[%d] DmiTranCoOverEn= %x\n", Index, PchDmiPreMemConfig->Lane[Index].TestDmiTranCoOverEn));
    DEBUG ((DEBUG_INFO, " Lane[%d] DmiTranCoOverPostCur= %x\n", Index, PchDmiPreMemConfig->Lane[Index].TestDmiTranCoOverPostCur));
    DEBUG ((DEBUG_INFO, " Lane[%d] DmiTranCoOverPreCur= %x\n", Index, PchDmiPreMemConfig->Lane[Index].TestDmiTranCoOverPreCur));
    DEBUG ((DEBUG_INFO, " Lane[%d] DmiUpPortTranPreset= %x\n", Index, PchDmiPreMemConfig->Lane[Index].TestDmiUpPortTranPreset));
  }
}

/**
  Load Config block default

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
PchDmiPreMemLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  UINTN                  Index;
  PCH_DMI_PREMEM_CONFIG  *PchDmiPreMemConfig;
  PchDmiPreMemConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "PchDmiPreMemConfig->Header.GuidHob.Name = %g\n", &PchDmiPreMemConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "PchDmiPreMemConfig->Header.GuidHob.Header.HobLength = 0x%x\n", PchDmiPreMemConfig->Header.GuidHob.Header.HobLength));

  for (Index = 0; Index < PCH_MAX_DMI_LANES; Index++) {
    PchDmiPreMemConfig->Lane[Index].TestDmiTranCoOverEn      = PLATFORM_POR;
    PchDmiPreMemConfig->Lane[Index].TestDmiUpPortTranPreset  = 0x7;
  }
}

STATIC COMPONENT_BLOCK_ENTRY  mPchDmiPreMemBlocks = {
  &gPchDmiPreMemConfigGuid,
  sizeof (PCH_DMI_PREMEM_CONFIG),
  DMI_PREMEM_CONFIG_REVISION,
  PchDmiPreMemLoadConfigDefault
};

/**
  Get PchDmi config block table size.

  @retval      Size of config block
**/
UINT16
PchDmiPreMemGetConfigBlockTotalSize (
  VOID
  )
{
  return mPchDmiPreMemBlocks.Size;
}

/**
  Add PchDmi ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
PchDmiPreMemAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mPchDmiPreMemBlocks, 1);
}

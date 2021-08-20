/** @file
  This file provides service for PEI phase policy printing

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
#include <Library/DebugLib.h>
#include <Library/GpioNativeLib.h>
#include <Ppi/SiPolicy.h>
#include <TwoLmConfig.h>

/**
  This function prints the PEI phase PreMem policy.

  @param[in] SiPolicyPreMemPpi - Instance of SI_PREMEM_POLICY_PPI
**/
VOID
EFIAPI
SaPrintPolicyPpiPreMem (
  IN  SI_PREMEM_POLICY_PPI *SiPolicyPreMemPpi
  )
{
  DEBUG_CODE_BEGIN ();
  INTN                                  Index;
  EFI_STATUS                            Status;
  SA_MISC_PEI_PREMEM_CONFIG             *MiscPeiPreMemConfig;
  PRAM_PREMEM_CONFIG                    *PramPreMemConfig;

  //
  // Get requisite IP Config Blocks which needs to be used here
  //
  Status = GetConfigBlock ((VOID *)SiPolicyPreMemPpi, &gSaMiscPeiPreMemConfigGuid, (VOID *) &MiscPeiPreMemConfig);
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock ((VOID *)SiPolicyPreMemPpi, &gPramPreMemConfigGuid, (VOID *) &PramPreMemConfig);
  ASSERT_EFI_ERROR (Status);




  DEBUG ((DEBUG_INFO, "\n------------------------ SA Policy (PEI PreMem) Print BEGIN -----------------\n"));
  DEBUG ((DEBUG_INFO, "Revision : 0x%x\n", SiPolicyPreMemPpi->TableHeader.Header.Revision));
  ASSERT (SiPolicyPreMemPpi->TableHeader.Header.Revision == SI_PREMEM_POLICY_REVISION);

  DEBUG ((DEBUG_INFO, "------------------------ SA_MISC_PEI_PREMEM_CONFIG  -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", MiscPeiPreMemConfig->Header.Revision));
  ASSERT (MiscPeiPreMemConfig->Header.Revision == SA_MISC_PEI_PREMEM_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " SpdAddressTable[%d] :", MEM_CFG_MAX_SOCKETS));
  for (Index = 0; Index < MEM_CFG_MAX_SOCKETS; Index++) {
    DEBUG ((DEBUG_INFO, " 0x%x", MiscPeiPreMemConfig->SpdAddressTable[Index]));
  }

  DEBUG ((DEBUG_INFO, "\n MchBar : 0x%x\n", MiscPeiPreMemConfig->MchBar));
  DEBUG ((DEBUG_INFO, " DmiBar : 0x%x\n", MiscPeiPreMemConfig->DmiBar));
  DEBUG ((DEBUG_INFO, " EpBar : 0x%x\n", MiscPeiPreMemConfig->EpBar));
  DEBUG ((DEBUG_INFO, " SmbusBar : 0x%x\n", MiscPeiPreMemConfig->SmbusBar));
  DEBUG ((DEBUG_INFO, " RegBar : 0x%x\n", MiscPeiPreMemConfig->RegBar));
  DEBUG ((DEBUG_INFO, " TsegSize: 0x%x\n MmioSize: %d MB\n", MiscPeiPreMemConfig->TsegSize, MiscPeiPreMemConfig->MmioSize));
  DEBUG ((DEBUG_INFO, " EdramBar : 0x%x\n", MiscPeiPreMemConfig->EdramBar));
  DEBUG ((DEBUG_INFO, " MmioSizeAdjustment: %d MB\n UserBd: 0x%x\n", MiscPeiPreMemConfig->MmioSizeAdjustment, MiscPeiPreMemConfig->UserBd));
  DEBUG ((DEBUG_INFO, " SkipExtGfxScan: %d\n S3DataPtr: 0x%x\n", MiscPeiPreMemConfig->SkipExtGfxScan, MiscPeiPreMemConfig->S3DataPtr));
  DEBUG ((DEBUG_INFO, " IedSize: %d\n", MiscPeiPreMemConfig->IedSize));
  DEBUG ((DEBUG_INFO, " TxtImplemented: %d\n BdatEnable: %d\n", MiscPeiPreMemConfig->TxtImplemented, MiscPeiPreMemConfig->BdatEnable));
  DEBUG ((DEBUG_INFO, " BdatTestType: %d\n ScanExtGfxForLegacyOpRom: %d\n", MiscPeiPreMemConfig->BdatTestType, MiscPeiPreMemConfig->ScanExtGfxForLegacyOpRom));
  DEBUG ((DEBUG_INFO, " CridEnable: %d\n", MiscPeiPreMemConfig->CridEnable));
  DEBUG ((DEBUG_INFO, " AcpiReservedMemoryBase: 0x%x\n", MiscPeiPreMemConfig->AcpiReservedMemoryBase));
  DEBUG ((DEBUG_INFO, " AcpiReservedMemorySize: 0x%x\n", MiscPeiPreMemConfig->AcpiReservedMemorySize));
  DEBUG ((DEBUG_INFO, " SystemMemoryLength: 0x%x\n", MiscPeiPreMemConfig->SystemMemoryLength));
  DEBUG ((DEBUG_INFO, " OpRomScanTempMmioBar: 0x%x\n", MiscPeiPreMemConfig->OpRomScanTempMmioBar));
  DEBUG ((DEBUG_INFO, " OpRomScanTempMmioLimit: 0x%x\n", MiscPeiPreMemConfig->OpRomScanTempMmioLimit));
  DEBUG ((DEBUG_INFO, " EnableAbove4GBMmio : 0x%x\n", MiscPeiPreMemConfig->EnableAbove4GBMmio));

  DEBUG ((DEBUG_INFO, "------------------------ PRAM_PREMEM_CONFIG -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", PramPreMemConfig->Header.Revision));
  ASSERT (PramPreMemConfig->Header.Revision == PRAM_PREMEM_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " PramPreMemConfig->PramSize : 0x%x\n", PramPreMemConfig->PramSize));

  DEBUG ((DEBUG_INFO, "\n------------------------ SA Policy (PEI PreMem) Print END -----------------\n"));
  DEBUG_CODE_END ();
  return;
}

/**
  This function prints the PEI phase policy.

  @param[in] SiPolicyPpi - Instance of SI_POLICY_PPI
**/
VOID
EFIAPI
SaPrintPolicyPpi (
  IN  SI_POLICY_PPI     *SiPolicyPpi
  )
{
  DEBUG_CODE_BEGIN ();
  EFI_STATUS                            Status;
  SA_MISC_PEI_CONFIG                    *MiscPeiConfig;
  //
  // Get requisite IP Config Blocks which needs to be used here
  //

  Status = GetConfigBlock ((VOID *) SiPolicyPpi, &gSaMiscPeiConfigGuid, (VOID *) &MiscPeiConfig);
  ASSERT_EFI_ERROR (Status);



  DEBUG ((DEBUG_INFO, "\n------------------------ SA Policy (PEI) Print BEGIN -----------------\n"));
  DEBUG ((DEBUG_INFO, "Revision : 0x%x\n", SiPolicyPpi->TableHeader.Header.Revision));
  ASSERT (SiPolicyPpi->TableHeader.Header.Revision == SI_POLICY_REVISION);

  DEBUG ((DEBUG_INFO, "------------------------ SA_MISC_PEI_CONFIG  -----------------\n"));
  DEBUG ((DEBUG_INFO, " Revision : %d\n", MiscPeiConfig->Header.Revision));
  ASSERT (MiscPeiConfig->Header.Revision == SA_MISC_PEI_CONFIG_REVISION);
  DEBUG ((DEBUG_INFO, " Device4Enable : 0x%x\n", MiscPeiConfig->Device4Enable));
  DEBUG ((DEBUG_INFO, " SkipPamLock : 0x%x\n", MiscPeiConfig->SkipPamLock));
  DEBUG ((DEBUG_INFO, " EdramTestMode : 0x%x\n", MiscPeiConfig->EdramTestMode));
  DEBUG_CODE_END ();
  return;
}

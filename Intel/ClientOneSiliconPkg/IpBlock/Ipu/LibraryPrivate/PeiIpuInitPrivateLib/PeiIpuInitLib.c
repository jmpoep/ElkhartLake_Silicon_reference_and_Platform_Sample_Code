/** @file
  PEIM Private Library to initialize for IPU device

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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
#include <Ppi/SiPolicy.h>
#include <Library/PeiServicesLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PciSegmentLib.h>
#include <Register/IpuRegs.h>
#include <Register/IgdRegs.h>
#include <Library/IpuInitLib.h>
#include <Library/IpuInitFruLib.h>
#include <IpuDataHob.h>
#include <IpuConfigHob.h>

#include <Library/GpioPrivateLib.h>
#include <IndustryStandard/Pci30.h>

/**
  IpuInit: Initialize the IPU device
**/
VOID
IpuInit (
  VOID
  )
{
  BOOLEAN              IpuDisabled;
  UINT64               IpuBaseAddress;
  IPU_DATA_HOB         *IpuDataHob;
  IPU_CONFIG_HOB       *IpuConfigHob;
  IPU_PREMEM_CONFIG    *IpuPreMemPolicy;
  BOOLEAN              IpuSupport;
  SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi;
  EFI_STATUS           Status;
  UINT8                Index;

  DEBUG ((DEBUG_INFO, "IpuInit Begins\n"));
  IpuBaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, IPU_BUS_NUM, IPU_DEV_NUM, IPU_FUN_NUM, 0);
  IpuDisabled = FALSE;
  IpuDataHob = NULL;
  IpuConfigHob = NULL;
  IpuPreMemPolicy = NULL;

  // @todo :  Call GetConfigBlock here. IsIpuSupport() ouput IpuPreMemPolicy in the future.
  SiPreMemPolicyPpi  = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gIpuPreMemConfigGuid, (VOID *) &IpuPreMemPolicy);
  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "BIOS doens't have IPU ConfigBlock\n"));
  }

  if (!IsIpuSupported () || IpuPreMemPolicy == NULL) {
    DEBUG ((DEBUG_INFO, "IPU is not supported\n"));
    IpuDisabled = TRUE;
    IpuSupport = FALSE;
  } else {
    IpuSupport = TRUE;
    DEBUG ((DEBUG_INFO, "Silicon supports IPU and BIOS has IPU config block\n"));
    //
    // Install IPU HOB
    //
    DEBUG ((DEBUG_INFO, "Install IPU HOB\n"));
    InstallIpuHob(&IpuDataHob, &IpuConfigHob);
    //
    // IPU is not fused off, and IPU ConfigBlock present
    //
    if ((PciSegmentRead16 (IpuBaseAddress + PCI_VENDOR_ID_OFFSET)) == 0xFFFF) {
      DEBUG ((DEBUG_WARN, "IPU config space not accessible!\n"));
      IpuDisabled = TRUE;
    }
    if (IpuPreMemPolicy->IpuEnable == 0) {
      DEBUG ((DEBUG_INFO, "Policy decides to disable IPU\n"));
      IpuDisabled = TRUE;
    }
  }

  //
  //  Program IPU bit at DEVEN register
  //
  if (!IpuDisabled) {
    //
    //  Set D5EN bit at DEVEN register
    //
    DEBUG ((DEBUG_INFO, "Set IPU bit at DEVEN regiser\n"));
    PciSegmentOr32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), (UINT32) B_SA_DEVEN_D5EN_MASK);
  } else {
    //
    //  Clear D5EN bit at DEVEN register
    //
    DEBUG ((DEBUG_INFO, "Clear IPU bit at DEVEN regiser\n"));
    PciSegmentAnd32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_DEVEN), (UINT32) ~B_SA_DEVEN_D5EN_MASK);
  }

  if (!IpuDisabled) {
    //
    // Configure IMGUCLK
    //
    for (Index = 0; Index < GPIO_IMGUCLK_NUMBER_OF_PINS; Index ++) {
      if (IpuPreMemPolicy->ImguClkOutEn[Index] == TRUE) {
        GpioEnableImguClkOut (Index);
      }
    }
    //
    // Miscellaneous configuration
    //
    IpuConfigMisc (IpuPreMemPolicy);
  }

  //
  // Initialize Hob for DXE phase use.
  //
  if (IpuDataHob != NULL && IpuConfigHob != NULL) {
    IpuDataHob->IpuSupport = IpuSupport;
    DEBUG ((DEBUG_INFO, "IpuDataHob->IpuSupport = %X \n", IpuDataHob->IpuSupport));
    //
    // Update IPU ACPI mode depending on IGFX present or not
    //
    if ((!IpuDisabled) && (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0)) != 0xFFFF)) {
      IpuConfigHob->IpuAcpiMode = 1;         // Set IPU ACPI mode as IGFX Child device
    } else {
      IpuConfigHob->IpuAcpiMode = 0;         // Set IPU ACPI mode as Disabled
    }
    DEBUG ((DEBUG_INFO, "IpuConfigHob->IpuAcpiMode = %X \n", IpuConfigHob->IpuAcpiMode));
  }
}



/**
  GetIpuImrConfiguration: Get the IPU IMR Configuration

  @retval IPU IMR Configuration, 0 = IPU Camera, 1 = IPU Gen, 2:7 = Undefined
**/
UINT8
GetIpuImrConfiguration (
  VOID
  )
{
  SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi;
  IPU_PREMEM_CONFIG    *IpuPreMemPolicy;
  EFI_STATUS           Status;

  SiPreMemPolicyPpi  = NULL;
  IpuPreMemPolicy = NULL;

  ///
  /// Get policy settings through the SiPreMemPolicyPpi
  ///
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gIpuPreMemConfigGuid, (VOID *) &IpuPreMemPolicy);
  ASSERT_EFI_ERROR (Status);

  return (UINT8) IpuPreMemPolicy->IpuImrConfiguration;
}

/**
  IsIpuSupported: Check if IPU is supported or not by Silicon.

  @retval FALSE = IPU is fused off. TRUE = IPU is supported by Sillicon.
**/
BOOLEAN
IsIpuSupported (
  VOID
  )
{
  UINT32               Data32;
  ///
  /// Check if Silicon is IPU capable
  ///
  Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MC_CAPID0_B));
  if (Data32 & BIT31) {
    DEBUG ((DEBUG_INFO, "IPU Fused off\n"));
    return FALSE;
  }

  DEBUG ((DEBUG_INFO, "IPU is supported by Silicon\n"));
  return TRUE;
}

/**
  IsIpuEnabled: Check if IPU is Enabled or not

  @retval FALSE = IPU is not supported, and/or IPU policy is disabled. TRUE = IPU is supported and IPU policy is enabled.
**/
BOOLEAN
IsIpuEnabled (
  VOID
  )
{
  IPU_PREMEM_CONFIG    *IpuPreMemPolicy;
  SI_PREMEM_POLICY_PPI *SiPreMemPolicyPpi;
  EFI_STATUS           Status;

  // @todo :  Call GetConfigBlock here. IsIpuSupport() ouput IpuPreMemPolicy in the future.
  ///
  /// Check if BIOS supports IPU by ConfigBlock presence
  ///
  SiPreMemPolicyPpi  = NULL;
  IpuPreMemPolicy = NULL;
  Status = PeiServicesLocatePpi (
             &gSiPreMemPolicyPpiGuid,
             0,
             NULL,
             (VOID **) &SiPreMemPolicyPpi
             );
  ASSERT_EFI_ERROR (Status);
  Status = GetConfigBlock((VOID *) SiPreMemPolicyPpi, &gIpuPreMemConfigGuid, (VOID *) &IpuPreMemPolicy);
  if (Status != EFI_SUCCESS) {
    DEBUG ((DEBUG_INFO, "BIOS doens't have IPU ConfigBlock\n"));
    return FALSE;
  }

  if (!IsIpuSupported ()) {
    return FALSE;
  }

  if (IpuPreMemPolicy->IpuEnable) {
    return TRUE;
  } else {
    return FALSE;
  }
}

/**
  Init and Install IPU Hob
  @param[out] IPU_DATA_HOB        - IPU_DATA_HOB instance installed by this function
  @param[out] IPU_CONFIG_HOB      - IPU_CONFIG_HOB instance installed by this function

  @retval EFI_SUCCESS
**/
EFI_STATUS
InstallIpuHob (
  OUT      IPU_DATA_HOB                 **IpuDataHobOut,
  OUT      IPU_CONFIG_HOB               **IpuConfigHobOut
  )
{
  EFI_STATUS                    Status;
  IPU_DATA_HOB                  *IpuDataHob;
  IPU_CONFIG_HOB                *IpuConfigHob;

  ///
  /// Create HOB for IPU Data
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (IPU_DATA_HOB),
             (VOID **) &IpuDataHob
             );
  ASSERT_EFI_ERROR (Status);
  ///
  /// Create HOB for IPU Config
  ///
  Status = PeiServicesCreateHob (
             EFI_HOB_TYPE_GUID_EXTENSION,
             sizeof (IPU_CONFIG_HOB),
             (VOID **) &IpuConfigHob
             );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Initialize default HOB data
  ///
  ///
  /// IPU_DATA_HOB
  ///
  IpuDataHob->EfiHobGuidType.Name = gIpuDataHobGuid;
  DEBUG ((DEBUG_INFO, "IpuDataHob->EfiHobGuidType.Name: %g\n", &IpuDataHob->EfiHobGuidType.Name));
  ZeroMem (&(IpuDataHob->IpuSupport), sizeof (IPU_DATA_HOB) - sizeof (EFI_HOB_GUID_TYPE));
  DEBUG ((DEBUG_INFO, "IpuDataHob @ %X\n", IpuDataHob));
  DEBUG ((DEBUG_INFO, "IpuDataHobSize - HobHeader: %X\n", sizeof (IPU_DATA_HOB) - sizeof (EFI_HOB_GUID_TYPE)));
  DEBUG ((DEBUG_INFO, "IpuDataHobSize: %X\n", sizeof (IPU_DATA_HOB)));
  ///
  /// IPU_DATA_HOB
  ///
  IpuConfigHob->EfiHobGuidType.Name = gIpuConfigHobGuid;
  DEBUG ((DEBUG_INFO, "IpuConfigHob->EfiHobGuidType.Name: %g\n", &IpuConfigHob->EfiHobGuidType.Name));
  ZeroMem (&(IpuConfigHob->IpuAcpiMode), sizeof (IPU_CONFIG_HOB) - sizeof (EFI_HOB_GUID_TYPE));
  DEBUG ((DEBUG_INFO, "IpuConfigHob @ %X\n", IpuDataHob));
  DEBUG ((DEBUG_INFO, "IpuConfigHobSize - HobHeader: %X\n", sizeof (IPU_CONFIG_HOB) - sizeof (EFI_HOB_GUID_TYPE)));
  DEBUG ((DEBUG_INFO, "IpuConfigHobSize: %X\n", sizeof (IPU_CONFIG_HOB)));


  (*IpuDataHobOut)   = IpuDataHob;
  (*IpuConfigHobOut) = IpuConfigHob;

  DEBUG ((DEBUG_INFO, "IPU HOB installed\n"));

  return EFI_SUCCESS;
}



/**
  Check IPU policies are valid for debugging unexpected problem if these
  values are not initialized or assigned incorrect resource.

  @param[in] IpuPreMemPolicy    The IPU PreMem Policy instance

**/
VOID
IpuValidatePolicy (
  IN    IPU_PREMEM_CONFIG    *IpuPreMemPolicy
  )
{
  ASSERT (IpuPreMemPolicy->Header.Revision == IPU_PREMEM_CONFIG_REVISION);
}

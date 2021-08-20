/** @file
  DXE Library for Initializing SystemAgent Graphics ACPI table initialization.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#include <Library/DxeGraphicsInitLib.h>


typedef union {
  struct {
    UINT32  Low;
    UINT32  High;
  } Data32;
  UINT64 Data;
} UINT64_STRUCT;

GLOBAL_REMOVE_IF_UNREFERENCED UINT64_STRUCT                 mMchBarBase;
GLOBAL_REMOVE_IF_UNREFERENCED GOP_COMPONENT_NAME2_PROTOCOL  *GopComponentName2Protocol = NULL;

/**
    Do Post GT PM Init Steps after VBIOS Initialization.

  @retval EFI_SUCCESS          Succeed.
**/
EFI_STATUS
PostPmInitEndOfDxe (
  VOID
  )
{
  CHAR16                    *DriverVersion;
  UINTN                     Index;
  EFI_STATUS                Status;
  GRAPHICS_DXE_CONFIG       *GraphicsDxeConfig;
  SA_POLICY_PROTOCOL        *SaPolicy;

  ///
  /// Get the platform setup policy.
  ///
  DriverVersion = NULL;
  Status = gBS->LocateProtocol (&gSaPolicyProtocolGuid, NULL, (VOID **) &SaPolicy);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID *) SaPolicy, &gGraphicsDxeConfigGuid, (VOID *)&GraphicsDxeConfig);
  ASSERT_EFI_ERROR (Status);


  Status = gBS->LocateProtocol (&gGopComponentName2ProtocolGuid, NULL, (VOID **)&GopComponentName2Protocol);
  if (!EFI_ERROR (Status)) {
    Status = GopComponentName2Protocol->GetDriverVersion (
                                          GopComponentName2Protocol,
                                          "en-US",
                                          &DriverVersion
                                          );
    if (!EFI_ERROR (Status)) {
      for (Index = 0; (DriverVersion[Index] != '\0'); Index++) {
      }
      Index = (Index+1)*2;
      CopyMem (GraphicsDxeConfig->GopVersion, DriverVersion, Index);
    }
  }

  ///
  /// Return final status
  ///
  return EFI_SUCCESS;
}


/**
Initialize GT ACPI tables

  @param[in] ImageHandle -     Handle for the image of this driver
  @param[in] SaPolicy -        SA DXE Policy protocol

  @retval EFI_SUCCESS          - GT ACPI initialization complete
  @retval EFI_NOT_FOUND        - Dxe System Table not found.
  @retval EFI_OUT_OF_RESOURCES - Mmio not allocated successfully.
**/
EFI_STATUS
GraphicsInit (
  IN EFI_HANDLE              ImageHandle,
  IN SA_POLICY_PROTOCOL      *SaPolicy
  )
{
  EFI_STATUS                      Status;
  GRAPHICS_DXE_CONFIG             *GraphicsDxeConfig;
  SYSTEM_AGENT_NVS_AREA_PROTOCOL  *SaNvsAreaProtocol;

  Status                  = EFI_SUCCESS;
  mMchBarBase.Data32.High = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR + 4));
  mMchBarBase.Data32.Low  = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_MCHBAR));
  mMchBarBase.Data       &= (UINT64) ~BIT0;

  Status = GetConfigBlock ((VOID *) SaPolicy, &gGraphicsDxeConfigGuid, (VOID *)&GraphicsDxeConfig);
  ASSERT_EFI_ERROR (Status);

  ///
  ///  Locate the SA Global NVS Protocol.
  ///
  Status = gBS->LocateProtocol (&gSaNvsAreaProtocolGuid, NULL, (VOID **) &SaNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Update IGD SA Global NVS
  ///
  DEBUG ((DEBUG_INFO, " Update Igd SA Global NVS Area.\n"));

  SaNvsAreaProtocol->Area->AlsEnable                    = GraphicsDxeConfig->AlsEnable;
  ///
  /// Initialize IGD state by checking if IGD Device 2 Function 0 is enabled in the chipset
  ///
  if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, 0, 0, R_SA_DEVEN)) & B_SA_DEVEN_D2EN_MASK) {
    SaNvsAreaProtocol->Area->IgdState = 1;
  } else {
    SaNvsAreaProtocol->Area->IgdState = 0;
  }

  SaNvsAreaProtocol->Area->BrightnessPercentage         = 100;
  SaNvsAreaProtocol->Area->IgdBootType                  = GraphicsDxeConfig->IgdBootType;
  SaNvsAreaProtocol->Area->IgdPanelType                 = GraphicsDxeConfig->IgdPanelType;
  SaNvsAreaProtocol->Area->IgdPanelScaling              = GraphicsDxeConfig->IgdPanelScaling;
  ///
  /// Get SFF power mode platform data for the IGD driver.  Flip the bit (bitwise xor)
  /// since Setup value is opposite of NVS and IGD OpRegion value.
  ///
  SaNvsAreaProtocol->Area->IgdDvmtMemSize               = GraphicsDxeConfig->IgdDvmtMemSize;
  SaNvsAreaProtocol->Area->IgdFunc1Enable               = 0;
  SaNvsAreaProtocol->Area->IgdHpllVco                   = MmioRead8 (mMchBarBase.Data + 0xC0F) & 0x07;
  SaNvsAreaProtocol->Area->IgdSciSmiMode                = 0;
  SaNvsAreaProtocol->Area->GfxTurboIMON                 = GraphicsDxeConfig->GfxTurboIMON;
  SaNvsAreaProtocol->Area->EdpValid                     = 0;

  return EFI_SUCCESS;
}
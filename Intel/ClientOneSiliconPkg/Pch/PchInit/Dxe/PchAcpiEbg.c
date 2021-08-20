/** @file
  This is the driver that initializes the Intel CedarFork PCH.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/HobLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include "PchInit.h"
#include <Protocol/PchPolicy.h>
#include <GpioDevConfig.h>
#include <ScsConfig.h>
#include <Library/AslUpdateLib.h>
#include <Library/PchInfoLib.h>
#include <Library/GpioLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PmcLib.h>
#include <Library/GbeLib.h>
#include <PchRstHob.h>
#include <Library/PchPcieRpLib.h>
#include <TraceHubConfig.h>
#include <PchReservedResources.h>
#include <Register/TraceHubRegs.h>
#include <Library/PciSegmentLib.h>
#include <Register/PchRegs.h>
#include <Library/BaseLib.h>

//
// Module variables
//
GLOBAL_REMOVE_IF_UNREFERENCED PCH_NVS_AREA_PROTOCOL    mPchNvsAreaProtocol;

/**
  Update NVS Area after RST PCIe Storage Remapping and before Boot
**/
VOID
PchUpdateNvsAreaAfterRemapping (
  VOID
  )
{
  UINTN                 Index;
  VOID                  *Hob;
  PCH_RST_HOB           *RstHob;

  Hob = GetFirstGuidHob (&gPchRstHobGuid);
  if (Hob == NULL) {
    DEBUG (( DEBUG_INFO , "PchUpdateNvsAreaAfterRemapping: cannot fetch RstHob" ));
    return;
  }

  RstHob = (PCH_RST_HOB *) GET_GUID_HOB_DATA (Hob);

  for (Index = 0; Index < PCH_MAX_RST_PCIE_STORAGE_CR; Index++) {
    mPchNvsAreaProtocol.Area->RstPcieStorageInterfaceType[Index]        = RstHob->RstCrConfiguration[Index].DeviceInterface;
    mPchNvsAreaProtocol.Area->RstPcieStoragePmCapPtr[Index]             = RstHob->SavedRemapedDeviceConfigSpace[Index].PmCapPtr;
    mPchNvsAreaProtocol.Area->RstPcieStoragePcieCapPtr[Index]           = RstHob->SavedRemapedDeviceConfigSpace[Index].PcieCapPtr;
    mPchNvsAreaProtocol.Area->RstPcieStorageL1ssCapPtr[Index]           = RstHob->SavedRemapedDeviceConfigSpace[Index].L1ssCapPtr;
    mPchNvsAreaProtocol.Area->RstPcieStorageEpL1ssControl2[Index]       = RstHob->SavedRemapedDeviceConfigSpace[Index].EndpointL1ssControl2;
    mPchNvsAreaProtocol.Area->RstPcieStorageEpL1ssControl1[Index]       = RstHob->SavedRemapedDeviceConfigSpace[Index].EndpointL1ssControl1;
    mPchNvsAreaProtocol.Area->RstPcieStorageLtrCapPtr[Index]            = RstHob->SavedRemapedDeviceConfigSpace[Index].LtrCapPtr;
    mPchNvsAreaProtocol.Area->RstPcieStorageEpLtrData[Index]            = RstHob->SavedRemapedDeviceConfigSpace[Index].EndpointLtrData;
    mPchNvsAreaProtocol.Area->RstPcieStorageEpLctlData16[Index]         = RstHob->SavedRemapedDeviceConfigSpace[Index].EndpointLctlData16;
    mPchNvsAreaProtocol.Area->RstPcieStorageEpDctlData16[Index]         = RstHob->SavedRemapedDeviceConfigSpace[Index].EndpointDctlData16;
    mPchNvsAreaProtocol.Area->RstPcieStorageEpDctl2Data16[Index]        = RstHob->SavedRemapedDeviceConfigSpace[Index].EndpointDctl2Data16;
    mPchNvsAreaProtocol.Area->RstPcieStorageRpDctl2Data16[Index]        = RstHob->SavedRemapedDeviceConfigSpace[Index].RootPortDctl2Data16;
    mPchNvsAreaProtocol.Area->RstPcieStorageUniqueTableBar[Index]       = RstHob->RstCrConfiguration[Index].EndPointUniqueMsixTableBar;
    mPchNvsAreaProtocol.Area->RstPcieStorageUniqueTableBarValue[Index]  = RstHob->RstCrConfiguration[Index].EndPointUniqueMsixTableBarValue;
    mPchNvsAreaProtocol.Area->RstPcieStorageUniquePbaBar[Index]         = RstHob->RstCrConfiguration[Index].EndPointUniqueMsixPbaBar;
    mPchNvsAreaProtocol.Area->RstPcieStorageUniquePbaBarValue[Index]    = RstHob->RstCrConfiguration[Index].EndPointUniqueMsixPbaBarValue;
    mPchNvsAreaProtocol.Area->RstPcieStorageRootPortNum[Index]          = RstHob->RstCrConfiguration[Index].RootPortNum;
  }
}

/**
  PCH ACPI initialization before Boot Sript Table is closed
  It update ACPI table and ACPI NVS area.

  @param[in] Event                A pointer to the Event that triggered the callback.
  @param[in] Context              A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
PchAcpiOnEndOfDxe (
  IN EFI_EVENT    Event,
  IN VOID         *Context
  )
{
  EFI_STATUS  Status;
  DEBUG ((DEBUG_INFO, "PchAcpiOnEndOfDxe() Start\n"));

  ///
  /// Closed the event to avoid call twice when launch shell
  ///
  gBS->CloseEvent (Event);
  //
  // Update Pch Nvs Area
  //
  Status = PchUpdateNvsArea ();
  if (EFI_ERROR (Status)) {
    return;
  }

  //
  // Patch PchNvsArea Address
  //
  PatchPchNvsAreaAddress ();

  DEBUG ((DEBUG_INFO, "PchAcpiOnEndOfDxe() End\n"));

  return;
}

/**
  Initialize Pch acpi
  @param[in] ImageHandle          Handle for the image of this driver

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver
**/
EFI_STATUS
PchAcpiInit (
  IN EFI_HANDLE         ImageHandle
  )
{
  EFI_STATUS  Status;
  EFI_EVENT   EndOfDxeEvent;

  DEBUG ((DEBUG_INFO, "Install PCH NVS protocol\n"));

  Status = (gBS->AllocatePool) (EfiACPIMemoryNVS, sizeof (PCH_NVS_AREA), (VOID **) &mPchNvsAreaProtocol.Area);
  ASSERT_EFI_ERROR (Status);

  ZeroMem ((VOID *) mPchNvsAreaProtocol.Area, sizeof (PCH_NVS_AREA));
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &ImageHandle,
                  &gPchNvsAreaProtocolGuid,
                  &mPchNvsAreaProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  ///
  /// Update the NVS Area after RST PCIe Storage Remapping
  ///
  PchUpdateNvsAreaAfterRemapping ();
  //
  // Register an end of DXE event for PCH ACPI to do tasks before invoking any UEFI drivers,
  // applications, or connecting consoles,...
  //
  Status = gBS->CreateEventEx (
                  EVT_NOTIFY_SIGNAL,
                  TPL_CALLBACK,
                  PchAcpiOnEndOfDxe,
                  NULL,
                  &gEfiEndOfDxeEventGroupGuid,
                  &EndOfDxeEvent
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/**
  Updates eMMC related fields in NVS area.

  @param[in] PchPolicy  Pointer to the PCH_POLICY_PROTOCOL
**/
STATIC
VOID
EmmcUpdateNvsArea (
  IN PCH_POLICY_PROTOCOL  *PchPolicy
  )
{
  SCS_EMMC_DXE_CONFIG  *EmmcDxeConfig;
  EFI_STATUS           Status;

  Status = GetConfigBlock ((VOID*)PchPolicy, &gEmmcDxeConfigGuid, (VOID*)&EmmcDxeConfig);
  ASSERT_EFI_ERROR (Status);

  //
  // Update eMMC HS400 mode enablement
  //
  mPchNvsAreaProtocol.Area->EMH4 = (UINT8) mPchConfigHob->Emmc.Hs400Enabled;
  mPchNvsAreaProtocol.Area->EmmcEnabled = (UINT8) mPchConfigHob->Emmc.Enabled;

  //
  // Update eMMC Driver Strength
  // Per eMMC 5.01 JEDEC Specification (JESD84-B50.1, Table 186)
  // Nominal Impedance - Driver Type Values:
  // 50 Ohm              0x0
  // 33 Ohm              0x1
  // 40 Ohm              0x4
  //
  switch (EmmcDxeConfig->DriverStrength) {
    case DriverStrength33Ohm:
      mPchNvsAreaProtocol.Area->EMDS = 0x1;
      break;
    case DriverStrength40Ohm:
      mPchNvsAreaProtocol.Area->EMDS = 0x4;
      break;
    case DriverStrength50Ohm:
    default:
      mPchNvsAreaProtocol.Area->EMDS = 0x0;
  }
}

/**
  Update ASL object before Boot

  @retval EFI_STATUS
  @retval EFI_NOT_READY         The Acpi protocols are not ready.
**/
EFI_STATUS
PchUpdateNvsArea (
  VOID
  )
{
  EFI_STATUS            Status;
  UINTN                 Index;
  UINT32                HpetBaseAdress;
  GPIO_GROUP            GroupToGpeDwX[3];
  UINT32                GroupDw[3];
  PCH_POLICY_PROTOCOL   *PchPolicy;
  GPIO_DXE_CONFIG   *GpioDxeConfig;

  ///
  /// Get PCH Policy Protocol
  ///
  Status = gBS->LocateProtocol (&gPchPolicyProtocolGuid, NULL, (VOID **)&PchPolicy);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Get GPIO DXE Config Block
  ///
  Status = GetConfigBlock ((VOID *)PchPolicy, &gGpioDxeConfigGuid, (VOID *)&GpioDxeConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "PchUpdateNvsArea\n"));

  //
  // PCIe LTR Configuration - Latency Tolerance Reporting
  //
  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
    mPchNvsAreaProtocol.Area->LtrEnable[Index]     = mPchConfigHob->PcieRp.RootPort[Index].LtrEnable;
  }

  //
  // Update ASL PcieMmCfgBaseAddress value
  //
#if 0
  // @todo: EBG ACPI Enable when doing requirement
  mPchNvsAreaProtocol.Area->MmCfgAddress = (UINT32)PcdGet64 (PcdPciExpressBaseAddress);
#endif

  //
  // Update PCHS.
  //
  mPchNvsAreaProtocol.Area->PchSeries     = PchSeries ();
  //
  // Update PCHG.
  //
  mPchNvsAreaProtocol.Area->PchGeneration = (UINT16) PchGeneration ();
  //
  // Update PSTP.
  //
  mPchNvsAreaProtocol.Area->PchStepping = (UINT16) PchStepping ();
  //
  // Update HPET base address.
  //
  PchHpetBaseGet (&HpetBaseAdress);
  mPchNvsAreaProtocol.Area->HPTE          = TRUE;  // @todo remove the NVS, since it's always enabled.
  mPchNvsAreaProtocol.Area->HPTB          = HpetBaseAdress;
  //
  // Update SBREG_BAR.
  //
  mPchNvsAreaProtocol.Area->SBRG          = PCH_PCR_BASE_ADDRESS;

  //
  // Update PMC ACPIBASE and PWRMBASE
  //
  mPchNvsAreaProtocol.Area->PMBS = PmcGetAcpiBase ();

  mPchNvsAreaProtocol.Area->PWRM = PmcGetPwrmBase ();

  //
  // Update GPIO device ACPI variables
  //
  mPchNvsAreaProtocol.Area->SGIR = mPchConfigHob->Interrupt.GpioIrqRoute;
  mPchNvsAreaProtocol.Area->GPHD = (UINT8)GpioDxeConfig->HideGpioAcpiDevice;

  //
  // Update GPP_X to GPE_DWX mapping.
  //
  GpioGetGroupDwToGpeDwX (
    &GroupToGpeDwX[0], &GroupDw[0],
    &GroupToGpeDwX[1], &GroupDw[1],
    &GroupToGpeDwX[2], &GroupDw[2]
    );

  //
  // GEI0/1/2 and GED0/1/2 are objects for informing how GPIO groups are mapped to GPE0.
  // If Group is mapped to 1-Tier GPE information is also stored on what Group DW
  // is mapped to GPE_DWx. Because GPE_DWx register is 32 bits large if groups have more than
  // 32 pads only part of it can be mapped.
  //
  //  GEIx - GroupIndex mapped to GPE0_DWx
  //  GEDx - DoubleWorld part of Group: 0 - pins 31-0, 1 - pins 63-32, ...
  //
  mPchNvsAreaProtocol.Area->GEI0 = (UINT8) GpioGetGroupIndexFromGroup (GroupToGpeDwX[0]);
  mPchNvsAreaProtocol.Area->GEI1 = (UINT8) GpioGetGroupIndexFromGroup (GroupToGpeDwX[1]);
  mPchNvsAreaProtocol.Area->GEI2 = (UINT8) GpioGetGroupIndexFromGroup (GroupToGpeDwX[2]);
  mPchNvsAreaProtocol.Area->GED0 = (UINT8) GroupDw[0];
  mPchNvsAreaProtocol.Area->GED1 = (UINT8) GroupDw[1];
  mPchNvsAreaProtocol.Area->GED2 = (UINT8) GroupDw[2];

  //
  // SCS Configuration
  //
  EmmcUpdateNvsArea (PchPolicy);

  //
  // CPU SKU
  //
#if 0
  // @todo: EBG ACPI Enable when doing requirement
  mPchNvsAreaProtocol.Area->DynamicS0i3Support = (UINT8)mPchConfigHob->Pm.S0i3Support;
#endif

  mPchNvsAreaProtocol.Area->PsOnEnable            = (UINT8)mPchConfigHob->Pm.PsOnEnable;

  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
    mPchNvsAreaProtocol.Area->LtrEnable[Index]  = (UINT8)mPchConfigHob->PcieRp.RootPort[Index].LtrEnable;
  }

  mPchNvsAreaProtocol.Area->GBES = IsGbePresent ();

  //
  // Update PCH Trace Hub Mode
  //
  mPchNvsAreaProtocol.Area->PchTraceHubMode     = (UINT8) mPchConfigHob->PchTraceHub.PchTraceHubMode;
  //
  // if SCRPD0[24] is set, force TH to be host debugger mode.
  //
  if (MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS) != 0xFFFFFFFF) {
    if (MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_TRACE_HUB_MEM_CSR_MTB_SCRPD0) & BIT24) {
      mPchNvsAreaProtocol.Area->PchTraceHubMode = TraceHubModeHostDebugger;
    }
  }
  return Status;
}

/**
  Initialize PCH Nvs Area opeartion region.

**/
EFI_STATUS
PatchPchNvsAreaAddress (
  VOID
  )
{
  EFI_STATUS                            Status;
  UINT32                                Address;
  UINT16                                Length;

  Status = InitializeAslUpdateLib ();
  ASSERT_EFI_ERROR (Status);

  Address = (UINT32) (UINTN) mPchNvsAreaProtocol.Area;
  Length  = (UINT16) sizeof (PCH_NVS_AREA);
  DEBUG ((DEBUG_INFO, "PatchPchNvsAreaAddress: PCH NVS Address %x Length %x\n", Address, Length));
  Status  = UpdateNameAslCode (SIGNATURE_32 ('P','N','V','B'), &Address, sizeof (Address));
  ASSERT_EFI_ERROR (Status);
  Status  = UpdateNameAslCode (SIGNATURE_32 ('P','N','V','L'), &Length, sizeof (Length));
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

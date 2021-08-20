/** @file
  PCH Init Smm module for PCH specific SMI handlers.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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

@par Specification
**/
#include "PchInitSmm.h"
#include <Register/PchRegs.h>
#include <Register/UsbRegs.h>
#include <Register/SmbusRegs.h>
#include <Register/PmcRegsFivr.h>

GLOBAL_REMOVE_IF_UNREFERENCED EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL        *mPchIoTrap;
GLOBAL_REMOVE_IF_UNREFERENCED EFI_SMM_SX_DISPATCH2_PROTOCOL             *mSxDispatch;

GLOBAL_REMOVE_IF_UNREFERENCED PCH_NVS_AREA                              *mPchNvsArea;
GLOBAL_REMOVE_IF_UNREFERENCED UINT16                                    mAcpiBaseAddr;

GLOBAL_REMOVE_IF_UNREFERENCED FIVR_EXT_RAIL_CONFIG                      mFivrExtVnnRailSxConfig;

//
// NOTE: The module variables of policy here are only valid in post time, but not runtime time.
//
GLOBAL_REMOVE_IF_UNREFERENCED PCH_CONFIG_HOB                            *mPchConfigHob;

//
// The reserved MMIO range to be used in Sx handler
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_PHYSICAL_ADDRESS                      mResvMmioBaseAddr;
GLOBAL_REMOVE_IF_UNREFERENCED UINTN                                     mResvMmioSize;

/**
  SMBUS Sx entry SMI handler.
**/
VOID
SmbusSxCallback (
  VOID
  )
{
  UINT64                      SmbusRegBase;
  UINT16                      SmbusIoBase;

  SmbusRegBase = PCI_SEGMENT_LIB_ADDRESS (
                   DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                   DEFAULT_PCI_BUS_NUMBER_PCH,
                   PCI_DEVICE_NUMBER_PCH_SMBUS,
                   PCI_FUNCTION_NUMBER_PCH_SMBUS,
                   0
                   );

  if (PciSegmentRead32 (SmbusRegBase) == 0xFFFFFFFF) {
    return;
  }

  SmbusIoBase = PciSegmentRead16 (SmbusRegBase + R_SMBUS_CFG_BASE) & B_SMBUS_CFG_BASE_BAR;
  if (SmbusIoBase == 0) {
    return;
  }

  PciSegmentOr8 (SmbusRegBase + PCI_COMMAND_OFFSET, EFI_PCI_COMMAND_IO_SPACE);
  //
  // Clear SMBUS status and SMB_WAK_STS of GPE0
  //
  IoWrite8 (SmbusIoBase + R_SMBUS_IO_HSTS, B_SMBUS_IO_SMBALERT_STS);
  IoWrite32 (mAcpiBaseAddr + R_ACPI_IO_GPE0_STS_127_96, B_ACPI_IO_GPE0_STS_127_96_SMB_WAK);
}

/*
  PCH xHCI Sx entry SMI handler
*/
VOID
PchXhciSxCallback (
  VOID
  )
{
  UINTN      XhciPciBase;

  XhciPciBase = PCI_SEGMENT_LIB_ADDRESS (
                    DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    PCI_DEVICE_NUMBER_PCH_XHCI,
                    PCI_FUNCTION_NUMBER_PCH_XHCI,
                    0
                    );

  //
  // Safety check for xHCI existense
  //
  if (PciSegmentRead32 (XhciPciBase) == 0xFFFFFFFF) {
    return;
  }

  //
  // If xHCI is in D0 that means OS didn't put it to D3 during Sx entry i.e. USB kernel debug is enabled.
  // Unless it is put manually to D3, USB wake functionality will not work.
  //
  if ((PciSegmentRead8 (XhciPciBase + R_XHCI_CFG_PWR_CNTL_STS) & V_XHCI_CFG_PWR_CNTL_STS_PWR_STS_D3) == 0) {
    //
    // Put device to D3 to enable wake functionality for USB devices
    //
    PciSegmentOr8 (XhciPciBase + R_XHCI_CFG_PWR_CNTL_STS, (UINT8)(B_XHCI_CFG_PWR_CNTL_STS_PWR_STS));
  }
}

/**
  Cache PCH FIVR policy.
**/
VOID
UpdatePchFivrSettings (
  VOID
  )
{
  CopyMem (
    &mFivrExtVnnRailSxConfig,
    &mPchConfigHob->Fivr.ExtVnnRailSx,
    sizeof (mFivrExtVnnRailSxConfig)
    );
}

/**
  PCH FIVR Sx entry SMI handler.
**/
VOID
PchFivrSxCallback (
  VOID
  )
{
  UINT32              PchPwrmBase;
  UINT32              Data32And;
  UINT32              Data32Or;
  UINT16              IccMax;

  if (mFivrExtVnnRailSxConfig.EnabledStates == 0) {
    return;
  }

  PchPwrmBase = PmcGetPwrmBase ();

  //
  // Temporary disable external bypass for the time of reconfiguration of Voltage and IccMax
  //
  MmioAnd32 (
    PchPwrmBase + R_PMC_PWRM_EXT_RAIL_CONFIG,
    (UINT32)~(B_PMC_PWRM_EXT_RAIL_CONFIG_VNN_S0IX_SX)
    );

  //
  // Configure Voltage level and ICC_max for external Vnn VR rail
  //
  IccMax = (UINT16) (((mFivrExtVnnRailSxConfig.IccMax) * (2 << 13))/1000);

  Data32Or = (mFivrExtVnnRailSxConfig.Voltage << N_PMC_PWRM_EXT_VNN_VR_CONFIG_VOLTAGE) |
    (IccMax << N_PMC_PWRM_EXT_VNN_VR_CONFIG_ICC_MAX);
  Data32And = (UINT32)~(B_PMC_PWRM_EXT_VNN_VR_CONFIG_VOLTAGE | B_PMC_PWRM_EXT_VNN_VR_CONFIG_ICC_MAX);

  MmioAndThenOr32 (
    PchPwrmBase + R_PMC_PWRM_EXT_VNN_VR_CONFIG,
    Data32And,
    Data32Or
    );

  //
  // Enable external bypass for Vnn rail
  //
  MmioOr32 (
    PchPwrmBase + R_PMC_PWRM_EXT_RAIL_CONFIG,
    mFivrExtVnnRailSxConfig.EnabledStates << N_PMC_PWRM_EXT_RAIL_CONFIG_VNN_S0IX_SX
    );
}

/**
  PCH Sx entry SMI handler.

  @param[in]     Handle          Handle of the callback
  @param[in]     Context         The dispatch context
  @param[in,out] CommBuffer      A pointer to a collection of data in memory that will
                                 be conveyed from a non-SMM environment into an SMM environment.
  @param[in,out] CommBufferSize  The size of the CommBuffer.

  @retval EFI_SUCCESS
**/
EFI_STATUS
EFIAPI
PchSxHandler (
  IN  EFI_HANDLE                   Handle,
  IN CONST VOID                    *Context OPTIONAL,
  IN OUT VOID                      *CommBuffer OPTIONAL,
  IN OUT UINTN                     *CommBufferSize OPTIONAL
  )
{
  PchLanSxCallback ();
  PchHdaSxCallback ();
  PchXhciSxCallback ();

  SmbusSxCallback ();
  PchFivrSxCallback ();

  return EFI_SUCCESS;
}

/**
  Initialize PCH Sx entry SMI handler.

  @param[in] ImageHandle - Handle for the image of this driver
**/
VOID
InitializeSxHandler (
  IN EFI_HANDLE        ImageHandle
  )
{
  EFI_SMM_SX_REGISTER_CONTEXT               SxDispatchContext;
  EFI_HANDLE                                SxDispatchHandle;
  EFI_SLEEP_TYPE                            SxType;
  EFI_STATUS                                Status;

  DEBUG ((DEBUG_INFO, "InitializeSxHandler() Start\n"));

  //
  // Register the callback for S3/S4/S5 entry
  //
  SxDispatchContext.Phase = SxEntry;
  for (SxType = SxS3; SxType <= SxS5; SxType++) {
    SxDispatchContext.Type  = SxType;
    Status = mSxDispatch->Register (
                            mSxDispatch,
                            PchSxHandler,
                            &SxDispatchContext,
                            &SxDispatchHandle
                            );
    ASSERT_EFI_ERROR (Status);
  }

  DEBUG ((DEBUG_INFO, "InitializeSxHandler() End\n"));
}

/**
  Allocates reserved MMIO for Sx SMI handler use.
**/
VOID
AllocateReservedMmio (
  VOID
  )
{
  mResvMmioBaseAddr = PcdGet32 (PcdSiliconInitTempMemBaseAddr);
  mResvMmioSize     = PcdGet32 (PcdSiliconInitTempMemSize);
  DEBUG ((DEBUG_INFO, "mResvMmioBaseAddr %x, mResvMmioSize %x\n", mResvMmioBaseAddr, mResvMmioSize));
}

/**
  Initializes the PCH SMM handler for for PCIE hot plug support
  <b>PchInit SMM Module Entry Point</b>\n
  - <b>Introduction</b>\n
      The PchInitSmm module is a SMM driver that initializes the Intel Platform Controller Hub
      SMM requirements and services. It consumes the PCH_POLICY_HOB and SI_POLICY_HOB for expected
      configurations per policy.

  - <b>Details</b>\n
    This module provides SMI handlers to services PCIE HotPlug SMI, LinkActive SMI, and LinkEq SMI.
    And also provides port 0x61 emulation support, registers BIOS WP handler to process BIOSWP status,
    and registers SPI Async SMI handler to handler SPI Async SMI.
    This module also registers Sx SMI callback function to detail with GPIO Sx Isolation and LAN requirement.

  - @pre
    - PCH PCR base address configured
    - EFI_PCI_HOST_BRIDGE_RESOURCE_ALLOCATION_PROTOCOL
      - This is to ensure that PCI MMIO and IO resource has been prepared and available for this driver to allocate.
    - EFI_SMM_BASE2_PROTOCOL
    - EFI_SMM_IO_TRAP_DISPATCH2_PROTOCOL
    - EFI_SMM_SX_DISPATCH2_PROTOCOL
    - EFI_SMM_CPU_PROTOCOL
    - @link _PCH_SMM_IO_TRAP_CONTROL_PROTOCOL PCH_SMM_IO_TRAP_CONTROL_PROTOCOL @endlink
    - @link _PCH_SMI_DISPATCH_PROTOCOL PCH_SMI_DISPATCH_PROTOCOL @endlink
    - @link _PCH_PCIE_SMI_DISPATCH_PROTOCOL PCH_PCIE_SMI_DISPATCH_PROTOCOL @endlink
    - @link _PCH_TCO_SMI_DISPATCH_PROTOCOL PCH_TCO_SMI_DISPATCH_PROTOCOL @endlink
    - @link _PCH_ESPI_SMI_DISPATCH_PROTOCOL PCH_ESPI_SMI_DISPATCH_PROTOCOL @endlink

  - <b>References</b>\n
    - @link _PCH_POLICY PCH_POLICY_HOB @endlink.
    - @link _SI_POLICY_STRUCT SI_POLICY_HOB @endlink.

  - <b>Integration Checklists</b>\n
    - Verify prerequisites are met. Porting Recommendations.
    - No modification of this module should be necessary
    - Any modification of this module should follow the PCH BIOS Specification and EDS

  @param[in] ImageHandle - Handle for the image of this driver
  @param[in] SystemTable - Pointer to the EFI System Table

  @retval EFI_SUCCESS    - PCH SMM handler was installed
**/
EFI_STATUS
EFIAPI
PchInitSmmEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                                Status;
  PCH_NVS_AREA_PROTOCOL                     *PchNvsAreaProtocol;
  EFI_PEI_HOB_POINTERS                      HobPtr;

  DEBUG ((DEBUG_INFO, "PchInitSmmEntryPoint()\n"));

  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmIoTrapDispatch2ProtocolGuid,
                    NULL,
                    (VOID **) &mPchIoTrap
                    );
  ASSERT_EFI_ERROR (Status);

  Status = gSmst->SmmLocateProtocol (
                    &gEfiSmmSxDispatch2ProtocolGuid,
                    NULL,
                    (VOID**) &mSxDispatch
                    );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->LocateProtocol (&gPchNvsAreaProtocolGuid, NULL, (VOID **) &PchNvsAreaProtocol);
  ASSERT_EFI_ERROR (Status);
  mPchNvsArea = PchNvsAreaProtocol->Area;

  //
  // Get PCH Data HOB.
  //
  HobPtr.Guid   = GetFirstGuidHob (&gPchConfigHobGuid);
  ASSERT (HobPtr.Guid != NULL);
  mPchConfigHob = (PCH_CONFIG_HOB *) GET_GUID_HOB_DATA (HobPtr.Guid);

  mAcpiBaseAddr = PmcGetAcpiBase ();

  AllocateReservedMmio ();

  InitializeSxHandler (ImageHandle);

  Status = InitializePchPcieSmm (ImageHandle, SystemTable);
  ASSERT_EFI_ERROR (Status);

  Status = InstallPchBiosWriteProtect (ImageHandle, SystemTable);
  ASSERT_EFI_ERROR (Status);

  Status = InstallPchSpiAsyncSmiHandler ();
  ASSERT_EFI_ERROR (Status);

  UpdateHdaCodecSxWakeCapabilitySetting ();

  UpdatePchFivrSettings ();


  return EFI_SUCCESS;
}

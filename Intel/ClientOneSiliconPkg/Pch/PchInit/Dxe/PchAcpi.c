/** @file
  This is the driver that initializes the Intel PCH.

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
#include <Library/SerialIoAccessLib.h>
#include <Library/SerialIoPrivateLib.h>
#include <Library/GbeLib.h>
#include <PchRstHob.h>
#include <Library/PchPcieRpLib.h>
#include <Library/CpuPlatformLib.h>
#include <TraceHubConfig.h>
#include <PchReservedResources.h>
#include <Register/TraceHubRegs.h>
#include <Library/PciSegmentLib.h>
#include <Register/PchRegs.h>
#include <Library/BaseLib.h>
#include <Register/UsbRegs.h>
#include <Library/PcdLib.h>
#include <IndustryStandard/Pci22.h>
#include <PcieRegs.h>
#include <Library/PchPcrLib.h>
#include <Register/PseRegs.h>
#include <Library/PchPseIoLib.h>
#include <Register/ScsVer3Regs.h>

//
// Module variables
//
GLOBAL_REMOVE_IF_UNREFERENCED PCH_NVS_AREA_PROTOCOL    mPchNvsAreaProtocol;

/**
  Retrieve interrupt information about a PCH device from policy

  @param[in] UartNumber                 Uart number

  @retval PCH_DEVICE_INTERRUPT_CONFIG   structure with device's interrupt information
**/
PCH_DEVICE_INTERRUPT_CONFIG
GetUartInterrupt (
  IN UINT8  UartNumber
  )
{
  PCH_DEVICE_INTERRUPT_CONFIG EmptyRecord;
  UINT8                       DevNum;
  UINT8                       FuncNum;
  UINT8                       Index;

  ZeroMem (&EmptyRecord, sizeof (PCH_DEVICE_INTERRUPT_CONFIG));
  DevNum  = GetSerialIoUartDeviceNumber (UartNumber);
  FuncNum = GetSerialIoUartFunctionNumber (UartNumber);

  for (Index = 0; Index < mPchConfigHob->Interrupt.NumOfDevIntConfig; Index++) {
    if ((mPchConfigHob->Interrupt.DevIntConfig[Index].Device == DevNum) &&
        (mPchConfigHob->Interrupt.DevIntConfig[Index].Function == FuncNum)) {
      return mPchConfigHob->Interrupt.DevIntConfig[Index];
    }
  }
  return EmptyRecord;
}

/**
  Update ASL definitions for SerialIo devices.

**/
VOID
UpdateSerialIoAcpiData (
  VOID
  )
{
  UINT8        Index;

  for (Index = 0; Index < GetPchMaxSerialIoSpiControllersNum (); Index++) {
    mPchNvsAreaProtocol.Area->SM0[Index] = mPchConfigHob->SerialIo.SpiDeviceConfig[Index].Mode;
    mPchNvsAreaProtocol.Area->SC0[Index] = GetSerialIoSpiPciCfg (Index);
  }
  for (Index = 0; Index < GetPchMaxSerialIoI2cControllersNum (); Index++) {
    mPchNvsAreaProtocol.Area->IM0[Index] = mPchConfigHob->SerialIo.I2cDeviceConfig[Index].Mode;
    mPchNvsAreaProtocol.Area->IC0[Index] = GetSerialIoI2cPciCfg (Index);
  }
  for (Index = 0; Index < GetPchMaxSerialIoUartControllersNum (); Index++) {
    mPchNvsAreaProtocol.Area->UM0[Index] = mPchConfigHob->SerialIo.UartDeviceConfig[Index].Mode;
    mPchNvsAreaProtocol.Area->UC0[Index] = GetSerialIoUartPciCfg (Index);
    mPchNvsAreaProtocol.Area->UD0[Index] = mPchConfigHob->SerialIo.UartDeviceConfig[Index].DmaEnable;
    mPchNvsAreaProtocol.Area->UP0[Index] = mPchConfigHob->SerialIo.UartDeviceConfig[Index].PowerGating;
    mPchNvsAreaProtocol.Area->UI0[Index] = (GetUartInterrupt (Index)).Irq;
  }
}

/**
  Update NVS Area for Timed GPIO devices.
**/
VOID
UpdateTimedGpioSetup (
  VOID
  )
{
  mPchNvsAreaProtocol.Area->EnableTimedGpio0 = (UINT8)mPchConfigHob->Pm.EnableTimedGpio0;
  mPchNvsAreaProtocol.Area->EnableTimedGpio1 = (UINT8)mPchConfigHob->Pm.EnableTimedGpio1;
}

/**
  Update NVS Area after RST PCIe Storage Remapping and before Boot

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_NOT_FOUND           Couldn't fetch RstHob
**/
EFI_STATUS
PchUpdateNvsAreaAfterRemapping (
  VOID
  )
{
  UINTN                 Index;
  VOID                  *Hob;
  PCH_RST_HOB           *RstHob;

  Hob = GetFirstGuidHob (&gPchRstHobGuid);
  if (Hob == NULL) {
    return EFI_NOT_FOUND;
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
  return EFI_SUCCESS;
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
  DEBUG ((DEBUG_INFO, "PchAcpiOnEndOfDxe() Start\n"));

  ///
  /// Closed the event to avoid call twice when launch shell
  ///
  gBS->CloseEvent (Event);

  //
  // Init HDA Audio ACPI tables
  //
  PchHdAudioAcpiInit ();
  //
  // Update ASL definitions for SerialIo devices.
  //
  UpdateSerialIoAcpiData ();
  UpdateCnviAcpiData ();
  UpdateTimedGpioSetup ();

  //
  // Update Pch Nvs Area
  //
  PchUpdateNvsArea ();

  //
  // Patch PchNvsArea Address
  //
  PatchPchNvsAreaAddress ();

  UpdateCsrtAcpiData ();
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
EFIAPI
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
  Updates SD card related fields in NVS area.

  @param[in] PchPolicy  Pointer to the PCH_POLICY_PROTOCOL
**/
STATIC
VOID
SdCardUpdateNvsArea (
  VOID
  )
{
  mPchNvsAreaProtocol.Area->SdCardEnabled = (UINT8) mPchConfigHob->SdCard.Enabled;
}

/**
  Updates UFS related fields in NVS area.

  @param[in] PchPolicy  Pointer to the PCH_POLICY_PROTOCOL
**/
STATIC
VOID
UfsUpdateNvsArea (
  VOID
  )
{
  UINT64 UfsPciBase;

  UfsPciBase = PCI_SEGMENT_LIB_ADDRESS (
                DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                DEFAULT_PCI_BUS_NUMBER_PCH,
                PCI_DEVICE_NUMBER_PCH_EHL_SCS_UFS0,
                PCI_FUNCTION_NUMBER_PCH_EHL_SCS_UFS0,
                0
                );
  if (PciSegmentRead32 (UfsPciBase) != 0xFFFFFFFF) {
    mPchNvsAreaProtocol.Area->Ufs0Enabled = (UINT8) TRUE;
  } else {
    mPchNvsAreaProtocol.Area->Ufs0Enabled = (UINT8) FALSE;
  }

  UfsPciBase = PCI_SEGMENT_LIB_ADDRESS (
                DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                DEFAULT_PCI_BUS_NUMBER_PCH,
                PCI_DEVICE_NUMBER_PCH_EHL_SCS_UFS1,
                PCI_FUNCTION_NUMBER_PCH_EHL_SCS_UFS1,
                0
                );
  if (PciSegmentRead32 (UfsPciBase) != 0xFFFFFFFF) {
    mPchNvsAreaProtocol.Area->Ufs1Enabled = (UINT8) TRUE;
  } else {
    mPchNvsAreaProtocol.Area->Ufs1Enabled = (UINT8) FALSE;
  }
}

/**
  Update NVS area for PCIe root ports.
**/
STATIC
VOID
PcieRpUpdateNvsArea (
  VOID
  )
{
  UINT32  Index;

  for (Index = 0; Index < PCH_MAX_PCIE_CLOCKS; Index++) {
    mPchNvsAreaProtocol.Area->ClockToRootPortMap[Index] = mPchConfigHob->PcieRp.PcieClock[Index].Usage;
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
  UINTN                 RpDev;
  UINTN                 RpFun;
  UINT32                Data32;
  PCH_POLICY_PROTOCOL   *PchPolicy;
  GPIO_DXE_CONFIG       *GpioDxeConfig;
  UINT64                XdciPciBase;
  UINT64                XdciBar;
  UINT16                PciMemConfig;
  UINT16                TcoBase;
  UINT8                 ClearXdciBar = FALSE;
  UINTN                 PseDmaPciMmBase;
  UINTN                 PseCanPciMmBase;

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

  //
  // Update ASL PCIE port address according to root port device and function
  //
  for (Index = 0; Index < GetPchMaxPciePortNum (); Index++) {
    Status = GetPchPcieRpDevFun (Index, &RpDev, &RpFun);
    ASSERT_EFI_ERROR (Status);

    Data32 = ((UINT8) RpDev << 16) | (UINT8) RpFun;
    mPchNvsAreaProtocol.Area->RpAddress[Index] = Data32;

    //
    // Update Maximum Snoop Latency and Maximum No-Snoop Latency values for PCIE
    //
    mPchNvsAreaProtocol.Area->PcieLtrMaxSnoopLatency[Index]   = mPchConfigHob->PcieRp.RootPort[Index].PcieRpLtrConfig.LtrMaxSnoopLatency;
    mPchNvsAreaProtocol.Area->PcieLtrMaxNoSnoopLatency[Index] = mPchConfigHob->PcieRp.RootPort[Index].PcieRpLtrConfig.LtrMaxNoSnoopLatency;
  }

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
  // Update base address
  //
  mPchNvsAreaProtocol.Area->PMBS = PmcGetAcpiBase ();
  mPchNvsAreaProtocol.Area->PWRM = PmcGetPwrmBase ();
  PchTcoBaseGet (&TcoBase);
  mPchNvsAreaProtocol.Area->TcoBase = TcoBase;

  //
  // Update PCH PID info
  //
  mPchNvsAreaProtocol.Area->IclkPid = PchPcrGetPid (PchIpIclk);

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
  SdCardUpdateNvsArea ();
  UfsUpdateNvsArea ();

  PcieRpUpdateNvsArea ();

  //
  // CPU SKU
  //
  mPchNvsAreaProtocol.Area->CpuSku = GetCpuSku ();
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
    if (MmioRead32 (PCH_TRACE_HUB_MTB_BASE_ADDRESS + R_TRACE_HUB_MEM_CSR_MTB_SCRPD0) & B_TRACE_HUB_MEM_CSR_MTB_SCRPD0_DEBUGGER_IN_USE) {
      mPchNvsAreaProtocol.Area->PchTraceHubMode = TraceHubModeHostDebugger;
    }
  }

  //
  // Saving GCTL value into PCH NVS area
  //

  XdciPciBase = PCI_SEGMENT_LIB_ADDRESS (
                  DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                  DEFAULT_PCI_BUS_NUMBER_PCH,
                  PCI_DEVICE_NUMBER_PCH_XDCI,
                  PCI_FUNCTION_NUMBER_PCH_XDCI,
                  0
                  );

  //
  // Determine Base address for Base address register (Offset 0x10)
  //
  if (PciSegmentRead32 (XdciPciBase) != 0xFFFFFFFF) {

    XdciBar = PciSegmentRead32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0;

    if ((PciSegmentRead32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET) & B_PCI_BAR_MEMORY_TYPE_MASK) == B_PCI_BAR_MEMORY_TYPE_64) {
      XdciBar += (UINT64)PciSegmentRead32 (XdciPciBase + (PCI_BASE_ADDRESSREG_OFFSET + 4)) << 32;
    }

    if (XdciBar == 0x0) {
      ClearXdciBar = TRUE;
      PciSegmentWrite32 ((XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET), PcdGet32 (PcdSiliconInitTempMemBaseAddr));
      XdciBar = PciSegmentRead32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET) & 0xFFFFFFF0;

      if ((PciSegmentRead32 (XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET) & B_PCI_BAR_MEMORY_TYPE_MASK) == B_PCI_BAR_MEMORY_TYPE_64) {
        XdciBar += (UINT64)PciSegmentRead32 (XdciPciBase + (PCI_BASE_ADDRESSREG_OFFSET + 4)) << 32;
      }
    }

    //
    // Enable Pci Memconfig to read the correct value for GCTL register
    //
    PciMemConfig = PciSegmentRead16 (XdciPciBase + PCI_COMMAND_OFFSET);
    PciSegmentWrite16 (XdciPciBase + PCI_COMMAND_OFFSET, PciMemConfig | (EFI_PCI_COMMAND_BUS_MASTER | EFI_PCI_COMMAND_MEMORY_SPACE));

    mPchNvsAreaProtocol.Area->PchxDCIPwrDnScale = MmioRead32(XdciBar + R_XDCI_MEM_GCTL);
    DEBUG ((DEBUG_INFO, "PchxDCIPwrDnScale  0x%x\n", (UINT64)mPchNvsAreaProtocol.Area->PchxDCIPwrDnScale));
    //
    // Disable Pci Memconfig & clear Base address
    //
    PciSegmentWrite16(XdciPciBase + PCI_COMMAND_OFFSET, PciMemConfig);

    if (ClearXdciBar == TRUE) {
      PciSegmentWrite32 ((XdciPciBase + PCI_BASE_ADDRESSREG_OFFSET), 0x0);
      PciSegmentWrite32 ((XdciPciBase + (PCI_BASE_ADDRESSREG_OFFSET + 4)), 0x0);
    }
  }

  PseDmaPciMmBase = PCI_SEGMENT_LIB_ADDRESS (
                      DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_PSE_DMA1,
                      PCI_FUNCTION_NUMBER_PCH_PSE_DMA1,
                      0
                      );

  if (PciSegmentRead16 (PseDmaPciMmBase) != 0xFFFF) {
    //
    // Saving PSE DMA1 address to DSDT
    //
    mPchNvsAreaProtocol.Area->PseDma1Address = PCH_PSE_DMA1_BASE_ADDRESS;
    DEBUG ((DEBUG_INFO, "Patching DSDT with PSE DMA1:   0x%x\n", mPchNvsAreaProtocol.Area->PseDma1Address));
    mPchNvsAreaProtocol.Area->PseDma1Length = V_PCH_PSE_DMAC_BAR_SIZE;
    mPchNvsAreaProtocol.Area->PseDma1En = 1;
  } else {
    mPchNvsAreaProtocol.Area->PseDma1Address = 0;
    mPchNvsAreaProtocol.Area->PseDma1Length = 0;
    mPchNvsAreaProtocol.Area->PseDma1En = 0;
  }

  PseDmaPciMmBase = PCI_SEGMENT_LIB_ADDRESS (
                      DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PCI_DEVICE_NUMBER_PCH_PSE_DMA2,
                      PCI_FUNCTION_NUMBER_PCH_PSE_DMA2,
                      0
                      );
  if (PciSegmentRead16 (PseDmaPciMmBase) != 0xFFFF) {
    //
    // Saving PSE DMA2 address to DSDT
    //
    mPchNvsAreaProtocol.Area->PseDma2Address = PCH_PSE_DMA2_BASE_ADDRESS;
    DEBUG ((DEBUG_INFO, "Patching DSDT with PSE DMA2:   0x%x\n", mPchNvsAreaProtocol.Area->PseDma2Address));
    mPchNvsAreaProtocol.Area->PseDma2Length = V_PCH_PSE_DMAC_BAR_SIZE;
    mPchNvsAreaProtocol.Area->PseDma2En = 1;
  } else {
    mPchNvsAreaProtocol.Area->PseDma2Address = 0;
    mPchNvsAreaProtocol.Area->PseDma2Length = 0;
    mPchNvsAreaProtocol.Area->PseDma2En = 0;
  }

  PseCanPciMmBase = PCI_SEGMENT_LIB_ADDRESS (0, 0, PCI_DEVICE_NUMBER_PCH_PSE_CAN0, PCI_FUNCTION_NUMBER_PCH_PSE_CAN0, 0);
  if (PciSegmentRead16 (PseCanPciMmBase) != 0xFFFF) {
    mPchNvsAreaProtocol.Area->PseCan0Enabled = 1;
  } else {
    mPchNvsAreaProtocol.Area->PseCan0Enabled = 0;
  }

  PseCanPciMmBase = PCI_SEGMENT_LIB_ADDRESS (0, 0, PCI_DEVICE_NUMBER_PCH_PSE_CAN1, PCI_FUNCTION_NUMBER_PCH_PSE_CAN1, 0);
  if (PciSegmentRead16 (PseCanPciMmBase) != 0xFFFF) {
    mPchNvsAreaProtocol.Area->PseCan1Enabled = 1;
  } else {
    mPchNvsAreaProtocol.Area->PseCan1Enabled = 0;
  }


  return Status;
}

/**
  Initialize PCH Nvs Area opeartion region.

  @retval EFI_SUCCESS    initialized successfully
  @retval EFI_NOT_FOUND  Nvs Area operation region is not found
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


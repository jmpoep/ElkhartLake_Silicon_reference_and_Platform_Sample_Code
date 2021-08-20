/** @file
  Header file for the HybridGraphics Dxe driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2019 Intel Corporation.

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
#ifndef _HYBRID_GRAPHICS_INIT_LIB_H_
#define _HYBRID_GRAPHICS_INIT_LIB_H_

#include <SaPolicyCommon.h>
#include "HybridGraphicsInfo.h"
#include <Uefi.h>
#include <IndustryStandard/Pci.h>
#include <IndustryStandard/Acpi.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/MmPciLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TimerLib.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/PciIo.h>
#include <Guid/HobList.h>
#include <Guid/EventGroup.h>
#include <Protocol/FirmwareVolume2.h>
#include <Library/PciCf8Lib.h>
#include <Library/SaPlatformLib.h>
#include <Library/PciSegmentLib.h>
#include <HgInfoHob.h>
#include <Protocol/SaPolicy.h>
#include <Protocol/SaNvsArea.h>
#include <CpuRegs.h>
#include <PcieRegs.h>
#include <Library/CpuPlatformLib.h>
#include <Library/GpioNativeLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchPcieRpLib.h>
#include <Library/PcieHelperLib.h>
#include <Register/IgdRegs.h>

/**
  Initialize the HybridGraphics support (DXE).

  @retval EFI_SUCCESS          - HybridGraphics initialization complete
  @retval EFI_OUT_OF_RESOURCES - Unable to allocated memory
  @retval EFI_NOT_FOUND        - HG InfoHob not found
  @retval EFI_DEVICE_ERROR     - Error Accessing HG GPIO
**/
EFI_STATUS
DxeHybridGraphicsInit (
  VOID
  );

/**
  Load and execute the dGPU VBIOS.

  @param[in] VbiosConfig - Pointer to VbiosData policy for Load/Execute and VBIOS Source.
      LoadVbios    : 0 = Do Not Load   ; 1 = Load VBIOS
      ExecuteVbios : 0 = Do Not Execute; 1 = Execute VBIOS
      VbiosSource  : 0 = PCIE Device   ; 1 = FirmwareVolume => TBD

  @retval EFI_SUCCESS     - Load and execute successful.
  @exception EFI_UNSUPPORTED - Secondary VBIOS not loaded.
**/
EFI_STATUS
LoadAndExecuteDgpuVbios (
  IN   SA_POLICY_PROTOCOL       *SaPolicy
  );

/**
  Initialize the runtime SwitchableGraphics support data for ACPI tables in GlobalNvs.

  @retval EFI_SUCCESS - The data updated successfully.
**/
EFI_STATUS
UpdateGlobalNvsData (
  VOID
  );

/**
  Do an AllocatePages () of type AllocateMaxAddress for EfiBootServicesCode
  memory.

  @param[in] AllocateType     - Allocated Legacy Memory Type
  @param[in] StartPageAddress - Start address of range
  @param[in] Pages            - Number of pages to allocate
  @param[in, out] Result      - Result of allocation

  @retval EFI_SUCCESS - Legacy16 code loaded
  @retval Other       - No protocol installed, unload driver.
**/
EFI_STATUS
AllocateLegacyMemory (
  IN  EFI_ALLOCATE_TYPE         AllocateType,
  IN  EFI_PHYSICAL_ADDRESS      StartPageAddress,
  IN  UINTN                     Pages,
  IN OUT  EFI_PHYSICAL_ADDRESS  *Result
  );

/**
Load Intel HG SSDT Tables

@retval EFI_SUCCESS - HG SSDT Table load successful.
**/
EFI_STATUS
LoadAcpiTables (
  VOID
  );

/**
  This function gets registered as a EndOfDxe callback to perform HG initialization

  @param[in] Event     - A pointer to the Event that triggered the callback.
  @param[in] Context   - A pointer to private data registered with the callback function.
**/
VOID
EFIAPI
HgEndOfDxeCallback (
  IN EFI_EVENT  Event,
  IN VOID       *Context
  );

/**
  Find the Pcie Capability ID for PCIe ports.

  @param[in] PciePortDev       - PCIe Port Device Number
  @param[in] PciePortFun       - PCIe Port Function Number

  @retval EFI_SUCCESS - Found  out the Cap Id.
**/
EFI_STATUS
FindPcieEpCapId (
  IN UINT8 PciePortDev,
  IN UINT8 PciePortFun
  );

#endif

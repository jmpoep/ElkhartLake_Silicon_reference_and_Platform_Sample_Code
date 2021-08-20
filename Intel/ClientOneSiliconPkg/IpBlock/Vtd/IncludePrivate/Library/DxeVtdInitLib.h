/** @file
  Header file for DXE VTD Init Lib.

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
#ifndef _DXE_VTD_INIT_LIB_H_
#define _DXE_VTD_INIT_LIB_H_

#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/VtdInfoLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/SaPlatformLib.h>
#if FixedPcdGetBool(PcdITbtEnable) == 1
#include <Library/ItbtPcieRpLib.h>
#endif
#include <IndustryStandard/Acpi.h>
#include <IndustryStandard/Pci.h>
#include <VtdDataHob.h>
#include <PchConfigHob.h>
#include <PchInfoHob.h>
#include <CpuRegs.h>
#include <Register/P2sbRegs.h>
#include <Register/IpuRegs.h>
#include <Register/IgdRegs.h>
#include <Register/VtdRegs.h>
#include <DmaRemappingTable.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/SaPolicy.h>
#include <Protocol/SaNvsArea.h>
#include <Protocol/FirmwareVolume2.h>

/**
  Locate the VT-d ACPI tables data file and read ACPI SSDT tables.
  Publish the appropriate SSDT based on current configuration and capabilities.

  @param[in] SaPolicy            SA DXE Policy protocol

  @retval EFI_SUCCESS - Vtd initialization complete
  @retval Other       - No Vtd function initiated
**/
EFI_STATUS
VtdInit (
  IN  SA_POLICY_PROTOCOL    *SaPolicy
  );

/**
  EndOfPcieEnum routine for update DMAR
**/
VOID
UpdateDmarEndOfPcieEnum (
  VOID
  );
#endif

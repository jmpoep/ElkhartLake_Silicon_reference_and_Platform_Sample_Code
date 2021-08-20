/** @file
  This code defines ACPI DMA Remapping table related definitions.
  See the System Agent BIOS specification for definition of the table.

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
#ifndef _DMA_REMAPPING_TABLE_H_
#define _DMA_REMAPPING_TABLE_H_

#include <Uefi.h>
#include <Base.h>
#include <IndustryStandard/DmaRemappingReportingTable.h>
#include <IndustryStandard/Acpi.h>
#include <Register/ItbtPcieRegs.h>

#pragma pack(1)
///
/// DMAR table signature
///
#define EFI_ACPI_VTD_DMAR_TABLE_SIGNATURE   0x52414D44  ///< "DMAR"
#define EFI_ACPI_DMAR_TABLE_REVISION        1
#define EFI_ACPI_DRHD_ENGINE_HEADER_LENGTH  0x10
#define EFI_ACPI_RMRR_HEADER_LENGTH         0x18
#define MAX_PCI_DEPTH                       5

typedef struct {
  EFI_ACPI_DMAR_DEVICE_SCOPE_STRUCTURE_HEADER DeviceScopeStructureHeader;
  EFI_ACPI_DMAR_PCI_PATH                      PciPath;     // device, function
} EFI_ACPI_DEV_SCOPE_STRUCTURE;

typedef struct {
  EFI_ACPI_DMAR_DRHD_HEADER     DrhdHeader;
  EFI_ACPI_DEV_SCOPE_STRUCTURE  DeviceScope[1];
} EFI_ACPI_DRHD_ENGINE1_STRUCT;

typedef struct {
  EFI_ACPI_DMAR_DRHD_HEADER     DrhdHeader;
  //
  // @todo use PCD
  //
  EFI_ACPI_DEV_SCOPE_STRUCTURE  DeviceScope[2];
} EFI_ACPI_DRHD_ENGINE3_STRUCT;

typedef struct {
  EFI_ACPI_DMAR_RMRR_HEADER     RmrrHeader;
  EFI_ACPI_DEV_SCOPE_STRUCTURE  DeviceScope[2];
} EFI_ACPI_RMRR_USB_STRUC;

typedef struct {
  EFI_ACPI_DMAR_RMRR_HEADER     RmrrHeader;
  EFI_ACPI_DEV_SCOPE_STRUCTURE  DeviceScope[1];    // IGD
} EFI_ACPI_RMRR_IGD_STRUC;

typedef struct {
  EFI_ACPI_DMAR_RMRR_HEADER     RmrrHeader;
  EFI_ACPI_DEV_SCOPE_STRUCTURE  DeviceScope[1];    // IGD - DiSM
} EFI_ACPI_RMRR_IGD_DISM_STRUC;

typedef struct {
  EFI_ACPI_DMAR_ANDD_HEADER     AnddHeader;
  UINT8                         AcpiObjectName[20];
} EFI_ACPI_ANDD_STRUC;

typedef struct {
  EFI_ACPI_DMAR_HEADER          DmarHeader;
  EFI_ACPI_DRHD_ENGINE1_STRUCT  DrhdEngine1;
  EFI_ACPI_DRHD_ENGINE3_STRUCT  DrhdEngine3;
  EFI_ACPI_RMRR_USB_STRUC       RmrrUsb;
  EFI_ACPI_RMRR_IGD_STRUC       RmrrIgd;
} EFI_ACPI_DMAR_TABLE;

#pragma pack()

#endif

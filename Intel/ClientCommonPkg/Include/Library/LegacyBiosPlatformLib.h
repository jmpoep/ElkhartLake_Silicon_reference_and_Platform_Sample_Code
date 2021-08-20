/** @file
    Header file for Legacy Bios Platform functionality.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2017 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#ifndef _LEGACY_BIOS_PLATFORM_LIB_H_
#define _LEGACY_BIOS_PLATFORM_LIB_H_

#include <Protocol/LegacyBios.h>
#include <Protocol/LegacyBiosPlatform.h>

typedef struct {
  EFI_HANDLE  Handle;
  UINT16      Vid;
  UINT16      Did;
  UINT16      SvId;
  UINT16      SysId;
} DEVICE_STRUCTURE;

EFI_COMPATIBILITY16_TABLE *
EFIAPI
GetCompatibility16Table (
  VOID
  );

VOID *
EFIAPI
Compatibility16GetTableAddressFunc (
  IN UINT16  AllocationRegion,
  IN UINT16  Length,
  IN UINT16  Allignment,
  OUT UINT16 *Segment,
  OUT UINT16 *Offset
  );

EFI_STATUS
EFIAPI
FindAllDeviceTypes (
  IN  UINT8                 BaseCodeValue,
  IN  UINT8                 SubClassCodeValue,
  IN OUT DEVICE_STRUCTURE   *DeviceTable,
  IN OUT UINT16             *DeviceIndex,
  IN BOOLEAN                DeviceFlags
  );

VOID
EFIAPI
PrepareAcpiInLegacyRegion (
  VOID
  );

VOID
EFIAPI
PrepareToScanRomHookSetTextMode (
  VOID
  );

VOID
EFIAPI
PrepareToScanRomHookVideo (
  IN EFI_HANDLE  DeviceHandle,
  IN EFI_HANDLE  VgaHandle
  );

VOID
EFIAPI
AfterRomInitHookVideo (
  IN EFI_HANDLE  DeviceHandle,
  IN EFI_HANDLE  VgaHandle
  );

VOID
EFIAPI
PlatformHookInitAhciOprom (
  IN EFI_HANDLE  DeviceHandle
  );

VOID
EFIAPI
PrepareToScanRomHookAhciOprom (
  IN EFI_HANDLE  DeviceHandle
  );

VOID
EFIAPI
AfterRomInitHookAhciOprom (
  IN EFI_HANDLE  DeviceHandle
  );

VOID
EFIAPI
LegacyBootAhciOpromRestore (
  VOID
  );

VOID
EFIAPI
PrepareToScanRomHookEbdaBcv (
  IN EFI_HANDLE  DeviceHandle
  );

VOID
EFIAPI
AfterRomInitHookEbdaBcv (
  IN EFI_HANDLE  DeviceHandle,
  IN OUT UINTN   *Shadowaddress
  );

VOID
EFIAPI
PrepareToBootEbdaBcv (
  VOID
  );

EFI_STATUS
EFIAPI
PlatformTranslatePirq (
  IN VOID                                         *PirqTable,
  IN EFI_LEGACY_IRQ_PRIORITY_TABLE_ENTRY          *IrqPriorityTable,
  IN UINTN                                        IrqPriorityEntryCount,
  IN UINTN                                        PciBus,
  IN UINTN                                        PciDevice,
  IN UINTN                                        PciFunction,
  IN OUT UINT8                                    *Pirq,
  OUT UINT8                                       *PciIrq
  );

#endif

/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2016 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _PCI_HOT_PLUG_H_
#define _PCI_HOT_PLUG_H_

//
// External include files do NOT need to be explicitly specified in real EDKII
// environment
//
#include <Base.h>
#include <Library/PcdLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <IndustryStandard/Acpi10.h>
#include <Protocol/PciHotPlugInit.h>
#include <Protocol/PciRootBridgeIo.h>
#include <SetupVariable.h>
#include <Library/DevicePathLib.h>
#include <Library/UefiLib.h>
#include <Guid/HobList.h>
#include <Library/HobLib.h>
#include <Protocol/SaPolicy.h>
#include <SetupVariable.h>
#include <IndustryStandard/Pci.h>
#include <ITbtInfoHob.h>
#include <DTbtInfoHob.h>

#define PCI_HOT_PLUG_DRIVER_PRIVATE_SIGNATURE SIGNATURE_32 ('G', 'U', 'L', 'P')
#define MAX_P2PB_OF_TBT_DAISY_CHAIN ((MAX_DTBT_CONTROLLER_NUMBER + MAX_ITBT_PCIE_PORT) * 64)
#define PCI_ROOT_0_STRING           L"PciRoot(0x0)"
#define PCI_ROOT_1_STRING           L"PciRoot(0x1)"

#define ACPI \
  { \
    { ACPI_DEVICE_PATH, ACPI_DP, { (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)), (UINT8) \
      ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8) } }, EISA_PNP_ID (0x0A03), 0 \
  }

#define PCI(device, function) \
  { \
    { HARDWARE_DEVICE_PATH, HW_PCI_DP, { (UINT8) (sizeof (PCI_DEVICE_PATH)), (UINT8) ((sizeof (PCI_DEVICE_PATH)) >> 8) } }, \
      (UINTN) function, (UINTN) device \
  }

#define END \
  { \
    END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, { END_DEVICE_PATH_LENGTH, 0 } \
  }

#define LPC(eisaid, function) \
  { \
    { ACPI_DEVICE_PATH, ACPI_DP, { (UINT8) (sizeof (ACPI_HID_DEVICE_PATH)), (UINT8) \
      ((sizeof (ACPI_HID_DEVICE_PATH)) >> 8) } }, EISA_PNP_ID (eisaid), function \
  }

typedef struct PCIE_HOT_PLUG_DEVICE_PATH {
  ACPI_HID_DEVICE_PATH      PciRootBridgeNode;
  PCI_DEVICE_PATH           PciRootPortNode;
  EFI_DEVICE_PATH_PROTOCOL  EndDeviceNode;
} PCIE_HOT_PLUG_DEVICE_PATH;

typedef struct {
  UINTN                           Signature;
  EFI_HANDLE                      Handle; // Handle for protocol this driver installs on
  EFI_PCI_HOT_PLUG_INIT_PROTOCOL  HotPlugInitProtocol;
} PCI_HOT_PLUG_INSTANCE;

typedef struct {
  EFI_DEVICE_PATH_PROTOCOL *HpcDevicePath;
  UINT64                   HpcPciAddress; // Bit[15:8]:Function, Bit[23:16]:Device, Bit[31:24]:Bus, Bit[32]:Segment
  UINT8                    RsvdExtraBusNum;
  UINT16                   RsvdPcieMegaMem;
  UINT8                    PcieMemAddrRngMax;
  UINT16                   RsvdPciePMegaMem;
  UINT8                    PciePMemAddrRngMax;
  UINT8                    RsvdPcieKiloIo;
} P2PB_RESOURCE_RECORD;

typedef struct {
  UINT8                    P2pbSegNum;
  UINT8                    P2pbBusNum;
  UINT8                    NumOfP2pbHotPlug;
  UINT8                    NumOfP2pbNonHotPlug;
} NUMBER_OF_HOTPLUG_BRIDGE;
/**
  This procedure returns a list of Root Hot Plug controllers that require
  initialization during boot process

  @param[in]  This      The pointer to the instance of the EFI_PCI_HOT_PLUG_INIT protocol.
  @param[out] HpcCount  The number of Root HPCs returned.
  @param[out] HpcList   The list of Root HPCs. HpcCount defines the number of elements in this list.

  @retval EFI_SUCCESS.
**/
EFI_STATUS
EFIAPI
GetRootHpcList (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL    *This,
  OUT UINTN                             *PhpcCount,
  OUT EFI_HPC_LOCATION                  **PhpcList
  );

/**
  This procedure Initializes one Root Hot Plug Controller
  This process may casue initialization of its subordinate buses

  @param[in]  This            The pointer to the instance of the EFI_PCI_HOT_PLUG_INIT protocol.
  @param[in]  HpcDevicePath   The Device Path to the HPC that is being initialized.
  @param[in]  HpcPciAddress   The address of the Hot Plug Controller function on the PCI bus.
  @param[in]  Event           The event that should be signaled when the Hot Plug Controller initialization is complete. Set to NULL if the caller wants to wait until the entire initialization process is complete. The event must be of the type EFI_EVT_SIGNAL.
  @param[out] HpcState        The state of the Hot Plug Controller hardware. The type EFI_Hpc_STATE is defined in section 3.1.

  @retval   EFI_SUCCESS.
**/
EFI_STATUS
EFIAPI
InitializeRootHpc (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL  *This,
  IN  EFI_DEVICE_PATH_PROTOCOL        *PhpcDevicePath,
  IN  UINT64                          PhpcPciAddress,
  IN  EFI_EVENT                       Event, OPTIONAL
  OUT EFI_HPC_STATE                   *PhpcState
  );

/**
  Returns the resource padding required by the PCI bus that is controlled by the specified Hot Plug Controller.

  @param[in]  This           The pointer to the instance of the EFI_PCI_HOT_PLUG_INIT protocol. initialized.
  @param[in]  HpcDevicePath  The Device Path to the Hot Plug Controller.
  @param[in]  HpcPciAddress  The address of the Hot Plug Controller function on the PCI bus.
  @param[out] HpcState       The state of the Hot Plug Controller hardware. The type EFI_HPC_STATE is defined in section 3.1.
  @param[out] Padding        This is the amount of resource padding required by the PCI bus under the control of the specified Hpc. Since the caller does not know the size of this buffer, this buffer is allocated by the callee and freed by the caller.
  @param[out] Attribute      Describes how padding is accounted for.

  @retval     EFI_SUCCESS.
**/
EFI_STATUS
EFIAPI
GetResourcePadding (
  IN  EFI_PCI_HOT_PLUG_INIT_PROTOCOL  *This,
  IN  EFI_DEVICE_PATH_PROTOCOL        *PhpcDevicePath,
  IN  UINT64                          PhpcPciAddress,
  OUT EFI_HPC_STATE                   *PhpcState,
  OUT VOID                            **Padding,
  OUT EFI_HPC_PADDING_ATTRIBUTES      *Attributes
  );

#endif

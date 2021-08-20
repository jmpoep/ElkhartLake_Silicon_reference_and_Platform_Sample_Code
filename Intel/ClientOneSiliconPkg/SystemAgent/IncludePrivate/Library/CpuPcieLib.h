/** @file
  Defines and prototypes for the System Agent PCIe library module
  This library is expected to share between DXE and SMM drivers.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2019 Intel Corporation.

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
#ifndef _CPU_PCIE_LIB_H_
#define _CPU_PCIE_LIB_H_

#include <Library/S3BootScriptLib.h>
#include <Protocol/SaPolicy.h>

#define MAX_SUPPORTED_ROOT_BRIDGE_NUMBER  4
#define MAX_SUPPORTED_DEVICE_NUMBER       192
#define L0_SET                            BIT0
#define L1_SET                            BIT1
#define MAX_PAM_REG_COUNT                 7
#define PAM_REG_BASE                      0x80
#define MAX_PCIE_ASPM_OVERRIDE            500
#define MAX_PCIE_LTR_OVERRIDE             500

///
/// The value before AutoConfig match the setting of PCI Express Base Specification 1.1, please be careful for adding new feature
///
typedef enum {
  PcieAspmDisabled,
  PcieAspmL0s,
  PcieAspmL1,
  PcieAspmL0sL1,
  PcieAspmAutoConfig,
  PcieAspmMax
} CPU_PCIE_ASPM_CONFIG;

typedef struct {
  UINT64                    Address;
  S3_BOOT_SCRIPT_LIB_WIDTH  Width;
  UINT32                    Value;
} BOOT_SCRIPT_PCI_REGISTER_SAVE;

/**
  Enumerate all end point devices connected to root bridge ports and record their MMIO base address

  @exception EFI_UNSUPPORTED      PCIe capability structure not found
  @retval    EFI_SUCCESS          All done successfully
**/
EFI_STATUS
EnumerateAllPcieDevices (
  VOID
  );

/**
  Sets Common Clock, TCx-VC0 mapping, and Max Payload for PCIe
**/
VOID
CpuPcieConfigBeforeOpRom (
  VOID
  );

/**
  This function does all SA ASPM initialization
**/
VOID
SaAspm (
  VOID
  );

/**
  This function checks PEG end point device for extended tag capability and enables them if they are.
**/
VOID
EnableExtendedTag (
  VOID
  );

/**
  This function saves/restores Chipset registers

  @param[in] IsSaving                  - TRUE for saving and FALSE for restoring
  @param[in] PciRegistersSaveTable[]   - The register table that has to be saved/restored
  @param[in] PciRegistersSaveTableSize - Size of above table
  @param[in,out] PciRegistersSaveBuffer - A saving/restoring buffer for those register settings.
**/
VOID
SaSaveRestoreChipset (
  IN     BOOLEAN                       IsSaving,
  IN     BOOT_SCRIPT_PCI_REGISTER_SAVE PciRegistersSaveTable[],
  IN     UINTN                         PciRegistersSaveTableSize,
  IN OUT UINTN                         *PciRegistersSaveBuffer
  );

/**
  This function saves/restores platform relative registers

  @param[in] IsSaving                  - TRUE for saving and FALSE for restoring
**/
VOID
SaSaveRestorePlatform (
  IN BOOLEAN        IsSaving
  );

/**
  This function handles SA S3 resume
**/
VOID
SaS3Resume (
  VOID
  );

/**
  Wrapper function for all SA S3 resume tasks which can be a callback function.
**/
VOID
SaS3ResumeCallback (
  VOID
  );

/**
  Wrapper function for all CPU PCIe ASPM tasks and extended tag which can be a callback function.
**/
VOID
CpuPcieConfigAfterOpRom (
  VOID
  );

/**
  Wrapper function for all CPU PCIe enumeration tasks which can be a callback function.
**/
VOID
CpuPcieEnumCallback (
  VOID
  );

/**
  This function will initialize all required policy into global veriables so no need to locate policy protocol during runtime.

  @param[in] SaPolicy  - DXE SA policy
**/
VOID
CpuPcieInitPolicy (
  IN SA_POLICY_PROTOCOL *SaPolicy
  );

#endif

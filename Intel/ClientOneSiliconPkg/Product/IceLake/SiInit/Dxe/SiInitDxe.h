/** @file
  Header file for Silicon Init DXE.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
#ifndef _SI_INIT_DXE_MODULE_H_
#define _SI_INIT_DXE_MODULE_H_
#include <Library/DebugLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Guid/EventGroup.h>
#include <Protocol/Smbios.h>
#include <Protocol/SiPolicyProtocol.h>
#include <Library/SmbiosMemoryLib.h>
#include <SiFvi.h>

/**
  Entry point of the incompatible pci device support code. Setup an incompatible device list template
  and install EFI Incompatible PCI Device Support protocol.

  @param ImageHandle             A handle for the image that is initializing this driver.
  @param SystemTable             A pointer to the EFI system table.

  @retval EFI_SUCCESS            Installed EFI Incompatible PCI Device Support Protocol successfully.
  @retval others                 Failed to install protocol.

**/
EFI_STATUS
EFIAPI
IncompatiblePciDeviceSupport (
  VOID
  );

#endif // _SI_INIT_DXE_MODULE_H_

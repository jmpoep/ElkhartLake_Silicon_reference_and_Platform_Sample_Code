/** @file
  Header file for PCH Initialization Driver.

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
#ifndef _PCH_INIT_DXE_H_
#define _PCH_INIT_DXE_H_

#include <SiConfigHob.h>
#include <PchConfigHob.h>
#include <Protocol/PchNvsArea.h>

//
// Data definitions
//
extern EFI_HANDLE               mImageHandle;

//
// Pch NVS area definition
//
extern PCH_NVS_AREA_PROTOCOL    mPchNvsAreaProtocol;

extern PCH_CONFIG_HOB           *mPchConfigHob;
extern SI_CONFIG_HOB_DATA       *mSiConfigHobData;

//
// Function Prototype
//

//
// Local function prototypes
//
/**
  Common PchInit Module Entry Point
**/
VOID
PchInitEntryPointCommon (
  VOID
  );

/**
  Common PCH initialization on PCI enumeration complete.
**/
VOID
PchOnPciEnumCompleteCommon (
  VOID
  );

/**
  Calls Boot Os Hand off routine for each Serial IO Controller
**/
VOID
ConfigureSerialIoAtBoot (
  VOID
  );

/**
  Puts all SerialIo controllers (except UARTs in debug mode) in D3.
  Clears MemoryEnable for all PCI-mode controllers on S3 resume
**/
VOID
ConfigureSerialIoAtS3Resume (
  VOID
  );

/**
  Add Serial Io UART Hidden Handles
**/
VOID
CreateSerialIoUartHiddenHandle (
  VOID
  );

/**
  Initialize Intel High Definition Audio ACPI Tables

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_LOAD_ERROR          ACPI table cannot be installed
  @retval EFI_UNSUPPORTED         ACPI table not set because DSP is disabled
**/
EFI_STATUS
PchHdAudioAcpiInit (
  VOID
  );

/**
  Perform the remaining configuration on SATA to perform device detection,
  then set the SATA SPD and PxE corresponding, and set the Register Lock on PCH SATA
**/
VOID
ConfigureSataOnEndOfDxe (
  VOID
  );

/**
  Perform USB3 Compliance Mode Configuration at ExitBootService
**/
VOID
ConfigureUsb3ComplianceDxe (
  VOID
  );

/**
  Update ASL data for CNVI Device.

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
UpdateCnviAcpiData (
   VOID
   );

/**
  Update ASL data for PSE DMA Device.

  @retval EFI_SUCCESS             The function completed successfully
**/
EFI_STATUS
UpdateCsrtAcpiData (
   VOID
   );

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
  );

/**
  Update ASL object before Boot

  @retval EFI_STATUS
  @retval EFI_NOT_READY         The Acpi protocols are not ready.
**/
EFI_STATUS
PchUpdateNvsArea (
  VOID
  );

/**
  Initialize PCH Nvs Area opeartion region.

  @retval EFI_SUCCESS    initialized successfully
  @retval EFI_NOT_FOUND  Nvs Area operation region is not found
**/
EFI_STATUS
PatchPchNvsAreaAddress (
  VOID
  );

#endif // _PCH_INIT_DXE_H_

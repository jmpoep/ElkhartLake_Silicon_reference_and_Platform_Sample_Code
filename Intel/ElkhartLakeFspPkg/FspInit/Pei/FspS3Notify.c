/** @file
  Source file for FSP S3 Notify  PEI module

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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

#include "FspS3Notify.h"
#include <Library/PcdLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>

STATIC EFI_PEI_NOTIFY_DESCRIPTOR mNotifyDesc = {
  (EFI_PEI_PPI_DESCRIPTOR_NOTIFY_CALLBACK | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEndOfPeiSignalPpiGuid,
  FspS3NotifyOnEndOfPei
};

EFI_PEI_PPI_DESCRIPTOR      mReadyToInstallPeiPostPciEnumerationPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiReadyToInstallPciEnumerationCompleteProtocolGuid,
  NULL
};

EFI_PEI_PPI_DESCRIPTOR      mPeiPostPciEnumerationPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiPciEnumerationCompleteProtocolGuid,
  NULL
};

EFI_PEI_PPI_DESCRIPTOR      mReadyToInstallPeiReadyToBootPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiReadyToInstallEventReadyToBootGuid,
  NULL
};

EFI_PEI_PPI_DESCRIPTOR      mPeiReadyToBootPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEfiEventReadyToBootGuid,
  NULL
};

EFI_PEI_PPI_DESCRIPTOR      mReadyToInstallPeiEndOfFirmwarePpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gFspReadyToInstallEventEndOfFirmwareGuid,
  NULL
};

EFI_PEI_PPI_DESCRIPTOR      mPeiEndOfFirmwarePpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gFspEventEndOfFirmwareGuid,
  NULL
};

EFI_PEI_PPI_DESCRIPTOR      mEndOfFspS3NotifyPpi = {
  (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST),
  &gEndOfFspS3NotifyGuid,
  NULL
};

/**
  FSP S3 Notify PEI module entry point

  @param[in]  FileHandle           Not used.
  @param[in]  PeiServices          General purpose services available to every PEIM.

  @retval     EFI_SUCCESS          The function completes successfully
  @retval     EFI_OUT_OF_RESOURCES Insufficient resources to create database
**/
EFI_STATUS
FspS3NotifyEntryPoint (
  IN       EFI_PEI_FILE_HANDLE    FileHandle,
  IN CONST EFI_PEI_SERVICES       **PeiServices
  )
{
  EFI_STATUS             Status = EFI_SUCCESS;

  if (GetFspGlobalDataPointer()->FspMode == FSP_IN_DISPATCH_MODE) {
    EFI_BOOT_MODE          BootMode;

    DEBUG((DEBUG_INFO, "FSP S3 Notify Entry\n"));

    Status = PeiServicesGetBootMode (&BootMode);
    if (BootMode == BOOT_ON_S3_RESUME) {
      //
      // End of SiInit notification event
      //
      DEBUG((DEBUG_INFO, "BOOT_ON_S3_RESUME\n"));
      Status = PeiServicesNotifyPpi (&mNotifyDesc);
      ASSERT_EFI_ERROR (Status);
    }
  }

  return Status;
}

/**
  Fix up pointers since they are located in real memory now.

  @param[in] PeiServices          General purpose services available to every PEIM.
  @param[in] NotifyDescriptor     The notification structure this PEIM registered on install.
  @param[in] Ppi                  The memory discovered PPI.  Not used.

  @retval EFI_SUCCESS             The function completed successfully.
**/
EFI_STATUS
EFIAPI
FspS3NotifyOnEndOfPei (
  IN EFI_PEI_SERVICES    **PeiServices,
  IN EFI_PEI_NOTIFY_DESCRIPTOR *NotifyDescriptor,
  IN VOID                      *Ppi
  )
{
  EFI_STATUS             Status;

  Status = EFI_SUCCESS;

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FspS3NotifyOnEndOfPei Entry\n"));

  DEBUG ((DEBUG_INFO | DEBUG_INIT, "FSP Post PCI Enumeration ...\n"));
  PeiServicesInstallPpi (&mReadyToInstallPeiPostPciEnumerationPpi);

  PeiServicesInstallPpi (&mPeiPostPciEnumerationPpi);

  DEBUG ((DEBUG_INFO| DEBUG_INIT, "FSP Ready To Boot ...\n"));
  PeiServicesInstallPpi (&mReadyToInstallPeiReadyToBootPpi);

  PeiServicesInstallPpi (&mPeiReadyToBootPpi);

  DEBUG ((DEBUG_INFO| DEBUG_INIT, "FSP End of Firmware ...\n"));
  PeiServicesInstallPpi (&mReadyToInstallPeiEndOfFirmwarePpi);

  PeiServicesInstallPpi (&mPeiEndOfFirmwarePpi);

  DEBUG ((DEBUG_INFO| DEBUG_INIT, "FSP S3 Notify End ...\n"));
  PeiServicesInstallPpi (&mEndOfFspS3NotifyPpi);

  return Status;
}

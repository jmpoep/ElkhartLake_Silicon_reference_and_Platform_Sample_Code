/** @file
  SMM Smbus Driver Entry

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2018 Intel Corporation.

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
#include "SmbusSmm.h"

SMBUS_INSTANCE  *mSmbusContext;
/**
  Execute an SMBUS operation

  @param[in] This                 The protocol instance
  @param[in] SlaveAddress         The address of the SMBUS slave device
  @param[in] Command              The SMBUS command
  @param[in] Operation            Which SMBus protocol will be issued
  @param[in] PecCheck             If Packet Error Code Checking is to be used
  @param[in, out] Length          Length of data
  @param[in, out] Buffer          Data buffer

  @retval EFI_SUCCESS             The SMBUS operation is successful
  @retval Other Values            Something error occurred
**/
EFI_STATUS
EFIAPI
SmbusExecute (
  IN      CONST EFI_SMBUS_HC_PROTOCOL   *This,
  IN      EFI_SMBUS_DEVICE_ADDRESS      SlaveAddress,
  IN      EFI_SMBUS_DEVICE_COMMAND      Command,
  IN      EFI_SMBUS_OPERATION           Operation,
  IN      BOOLEAN                       PecCheck,
  IN OUT  UINTN                         *Length,
  IN OUT  VOID                          *Buffer
  )
{
  InitializeSmbusRegisters ();

  return SmbusExec (
           SlaveAddress,
           Command,
           Operation,
           PecCheck,
           Length,
           Buffer
           );
}

/**
  <b>SMBus SMM Module Entry Point</b>\n
  - <b>Introduction</b>\n
    The SMBus module is a SMM driver that provides a standard way to execute an SMBus command.

  - @pre
    - EFI_SMM_BASE2_PROTOCOL
      - Documented in the System Management Mode Core Interface Specification

  - @result
    The SMBus driver produces EFI_SMBUS_HC_PROTOCOL documented in the SMBus Host Controller Protocol Specification.

  - <b>Integration Checklist</b>\n
    - Verify prerequisites are met
    - Add Smbus\Smm\SmbusSmm.inf to the platform DSC file.

  @param[in] ImageHandle          ImageHandle of this module
  @param[in] SystemTable          EFI System Table

  @retval EFI_SUCCESS             Driver initializes successfully
  @retval Other values            Some error occurred
**/
EFI_STATUS
EFIAPI
InitializeSmbusSmm (
  IN      EFI_HANDLE            ImageHandle,
  IN      EFI_SYSTEM_TABLE      *SystemTable
  )
{
  EFI_STATUS  Status;

  ///
  /// Locate SMM Base Protocol
  ///

  Status = gSmst->SmmAllocatePool (EfiRuntimeServicesData, sizeof (SMBUS_INSTANCE), (VOID **) &mSmbusContext);

  if (EFI_ERROR (Status)) {
    return Status;
  } else {
    ZeroMem (mSmbusContext, sizeof (SMBUS_INSTANCE));

    mSmbusContext->Signature                  = PCH_SMBUS_PRIVATE_DATA_SIGNATURE;
    mSmbusContext->SmbusController.Execute    = SmbusExecute;
    mSmbusContext->SmbusController.ArpDevice  = SmbusArpDevice;
    mSmbusContext->SmbusController.GetArpMap  = SmbusGetArpMap;
    mSmbusContext->SmbusController.Notify     = SmbusNotify;

    ///
    /// Install the SMBUS interface
    ///
    Status = gSmst->SmmInstallProtocolInterface (
                      &mSmbusContext->Handle,
                      &gEfiSmmSmbusProtocolGuid,
                      EFI_NATIVE_INTERFACE,
                      &mSmbusContext->SmbusController
                      );
    ASSERT_EFI_ERROR (Status);
  }

  return EFI_SUCCESS;
}

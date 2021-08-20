/** @file
  Source code file providing TCO Reset protocol functions

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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

#include <Uefi/UefiBaseType.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Protocol/PlatformTcoResetProtocol.h>
#include <Register/PmcRegs.h>

EFI_STATUS
EnableTcoReset (
  IN      UINT32            *RcrbGcsSaveValue
  );

EFI_STATUS
DisableTcoReset (
  VOID
  );

EFI_TCO_RESET_PROTOCOL  mTcoResetProtocol = {
  EnableTcoReset,
  DisableTcoReset
};

EFI_STATUS
EnableTcoReset (
  IN      UINT32            *RcrbGcsSaveValue
  )
/*++

Routine Description:

  Enables the TCO timer to reset the system in case of a system hang.  This is
  used when writing the clock registers.

Arguments:

  RcrbGcsSaveValue  - This is the value of Timeout in Seconds.

Returns:

  EFI_STATUS

--*/
{
  UINT16          AcpiBase;
  UINT16          TcoBase;
  UINT32          TcoTimerValue;

  TcoTimerValue = 4; // Default value, in seconds

  if (*RcrbGcsSaveValue != 0) {
    TcoTimerValue = (UINT32) ((*RcrbGcsSaveValue * 10) / 6);
  }
  //
  // Max value should be 0x3FF,
  // Since TCOTMR bits are writable
  // from BIT9 down to BIT0.
  //
  if (TcoTimerValue > 0x3FF) {
    TcoTimerValue = 0x3FF;
  }
  //
  // Obtain ACPI Base Address
  //
  AcpiBase = PcdGet16 (PcdAcpiBaseAddress);
  if ((AcpiBase == 0) || (AcpiBase == 0xFFFF)) {
    return EFI_DEVICE_ERROR;
  }
  //
  // Obtain TCO Base Address
  //
  TcoBase = PcdGet16 (PcdTcoBaseAddress);
  if ((TcoBase == 0) || (TcoBase == 0xFFFF)) {
    return EFI_DEVICE_ERROR;
  }
  //
  // Stop TCO if not already stopped
  //
  IoOr16 (TcoBase + R_TCO_IO_TCO1_CNT, (UINT16) (B_TCO_IO_TCO1_CNT_TMR_HLT));
  //
  // Clear second TCO status
  //
  IoWrite8 (TcoBase + R_TCO_IO_TCO2_STS, B_TCO_IO_TCO2_STS_SECOND_TO);
  //
  // Clear NO_REBOOT bit
  //
  IoAnd16 (TcoBase + R_TCO_IO_TCO1_CNT, (UINT16)~B_TCO_IO_TCO1_CNT_NR_MSUS);
  //
  // Set TCO timer value (interval * 0.6s)
  //
  IoWrite16 (TcoBase + R_TCO_IO_TMR, (UINT16)(TcoTimerValue & 0x3FF));
  //
  // Trigger TCO to reload timer value by
  // writing ANY value to TCORLD register.
  //
  IoWrite16 (TcoBase + R_TCO_IO_RLD, (UINT16) 0x01);
  //
  // Clear second TCO status
  //
  IoWrite8 (TcoBase + R_TCO_IO_TCO2_STS, B_TCO_IO_TCO2_STS_SECOND_TO);
  //
  // Clear the timer halt bit so that
  // the TCO timer can start running.
  //
  IoAnd16 (TcoBase + R_TCO_IO_TCO1_CNT, (UINT16)~(B_TCO_IO_TCO1_CNT_TMR_HLT));
  //
  // Clear TCO Enable
  // This is to avoid TCO logic to generate SMI,
  // preventing possible clearing of TCO TIMEOUT bit
  // in SMI handler.
  // This is done so that second timeout can happen
  // for the system to reset.
  //
  IoAnd32 (AcpiBase + R_ACPI_IO_SMI_EN, (UINT32)~(B_ACPI_IO_SMI_EN_TCO));

  return EFI_SUCCESS;
}


EFI_STATUS
DisableTcoReset (
  VOID
  )
/*++

Routine Description:

  Disables the TCO timer.  This is used after writing the clock registers.


Returns:

  EFI_STATUS

--*/
{
  UINT16          TcoBase;

  //
  // Obtain TCO Base Address
  //
  TcoBase = PcdGet16 (PcdTcoBaseAddress);
  if ((TcoBase == 0) || (TcoBase == 0xFFFF)) {
    return EFI_DEVICE_ERROR;
  }
  //
  // Halt the TCO timer
  //
  IoOr16 (TcoBase + R_TCO_IO_TCO1_CNT, (UINT16) (B_TCO_IO_TCO1_CNT_TMR_HLT));

  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
PlatformTcoResetInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
)
/*++

Routine Description:
  Initialize the TCO Reset Protocol

Arguments:

  ImageHandle             Image handle of the loaded driver
  SystemTable             Pointer to the System Table

Returns:

  EFI_SUCCESS             Thread can be successfully created
  EFI_OUT_OF_RESOURCES    Cannot allocate protocol data structure
  EFI_DEVICE_ERROR        Cannot startup the driver.

--*/
{
  EFI_HANDLE    Handle;
  EFI_STATUS    Status;

  Handle = NULL;
  Status = gBS->InstallProtocolInterface (
                  &Handle,
                  &gEfiTcoResetProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  &mTcoResetProtocol
                  );
  ASSERT_EFI_ERROR (Status);

  return Status;
}

/** @file
  Simple Boot Flag.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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

#include "SimpleBootFlagInternal.h"

EFI_ACPI_BOOT_TABLE mBoot = {
  {
    EFI_ACPI_3_0_SIMPLE_BOOT_FLAG_TABLE_SIGNATURE,
    sizeof (EFI_ACPI_BOOT_TABLE),
    1,     // Revision
    0x00,  // Checksum will be updated at runtime

    //
    // It is expected that these values will be updated at runtime
    //
    { EFI_ACPI_OEM_ID },        // OEMID is a 6 bytes long field
    EFI_ACPI_OEM_TABLE_ID,      // OEM table identification(8 bytes long)
    EFI_ACPI_OEM_REVISION,      // OEM revision number
    EFI_ACPI_CREATOR_ID,        // ASL compiler vendor ID
    EFI_ACPI_CREATOR_REVISION   // ASL compiler revision number
  },

  //
  // CmosIndex, indicates at which offset in CMOS memory the BOOT register is located.
  // This hardcode value has a chance to be dynamic updated DsdtTableUpdate callback.
  //
  0,

  //
  // 3 bytes reserved value
  //
  {
    0x00,
    0x00,
    0x00
  }
};

BOOLEAN
CheckOddParity (
  IN  UINT8 Value
  )
/*++

Routine Description:
 Check if the value is of ODD parity.

Arguments:
 Value - the 8 bits value
    
Returns:

  TRUE  -  the value is of ODD parity
  FALSE -  the value is not of ODD parity

--*/
{
  UINT8                           OddNum;
  UINT8                           Index;
  
  OddNum = 0;
  
  for (Index = 0; Index < 8; Index++) {
    if (Value & (1 << Index)) {
      OddNum++;
    }
  }
  
  return (BOOLEAN) (OddNum % 2 != 0);
}
/**
  The Entry Point for module SimpleBootFlag. The user code starts with this function.

  @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
  @param[in] SystemTable    A pointer to the EFI System Table.
  
  @retval EFI_SUCCESS       The entry point is executed successfully.
  @retval other             Some error occurs when executing this entry point.

**/
EFI_STATUS
EFIAPI
SimpleBootFlagEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS                      Status;
  UINTN                           BufferSize;

  EFI_SIMPLE_BOOT_FLAG            SimpleBootFlag;
  UINT8                           LegacyValue;
  UINT8                           EfiValue;

  BOOLEAN                         LegacyValueExists;
  BOOLEAN                         EfiValueExists;

  EFI_ACPI_TABLE_PROTOCOL         *AcpiTable;
  UINTN                           TableKey;

  LegacyValue       = 0;
  EfiValue          = 0;

  //
  // Read EFI variable
  //
  EfiValueExists = FALSE;
  BufferSize     = sizeof (EfiValue);
  Status = gRT->GetVariable (
                  SIMPLE_BOOT_FLAG_VARIABLE_NAME,
                  &gEfiGlobalVariableGuid,
                  NULL,
                  &BufferSize,
                  &EfiValue
                  );
                  
  if (!EFI_ERROR (Status)) {
    EfiValueExists = TRUE;
    if (!CheckOddParity (EfiValue)) {
      EfiValue = 0;
    }
  }
  
  //
  // Read CMOS
  //
  
  if (PcdGet8 (PcdBootRegisterCmosIndex) == 0xFF) {
    LegacyValueExists = FALSE;
  } else {
    LegacyValueExists = TRUE;
    IoWrite8 (0x70, PcdGet8 (PcdBootRegisterCmosIndex));
    LegacyValue = IoRead8 (0x71);
    if (!CheckOddParity (LegacyValue)) {
      LegacyValue = 0;
    }
  }
  
  //
  // Chapter 3.2:
  // The firmware must not alter this register or variable while the operating 
  // system owns it, with the exception of updating the CMOS BOOT register if necessary 
  // when an EFI-aware OS or executable writes to the SimpleBootFlag
  // environment variable. It is not required to update the SimpleBootFlag environment variable 
  // if the CMOS BOOT register is updated.
  //
  // So the CMOS Boot register should always be synced with SimpleBootFlag variable, and 
  // CMOS Boot register has more priorty if it is different with SimpleBootFlag variable.
  //
  SimpleBootFlag.Uint8 = (EfiValue != 0) ? EfiValue : LegacyValue;
  
  //
  // Set DIAG bit?
  //  When the BOOTING bit wasn't cleared by OS
  //
  if (SimpleBootFlag.Bits.Booting != 0) {
    SimpleBootFlag.Bits.Diag = 1;
  }

  //
  // Set BOOTING bit!
  //  Expect OS to clear it
  //
  SimpleBootFlag.Bits.Booting = 1;
  
  //
  // Set SUPRESSBOOTDISPLAY bit?
  //  When the platform turns on this feature
  // It's possible that OS set it in S4 shutdown, so we shouldn't clear it
  //
  if (PcdGetBool (PcdBootSuppressDisplay)) {
    SimpleBootFlag.Bits.SuppressBootDisplay = 1;
  }
  
  //
  // Set the PARITY bit
  //
  SimpleBootFlag.Bits.Parity = 0;
  if (!CheckOddParity (SimpleBootFlag.Uint8)) {
    SimpleBootFlag.Bits.Parity = 1;
  }
  
  //
  // Write CMOS
  //
  if (LegacyValueExists) {
    IoWrite8 (0x70, PcdGet8 (PcdBootRegisterCmosIndex));
    IoWrite8 (0x71, SimpleBootFlag.Uint8);

    //
    // Publish the BOOT table
    //
    Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &AcpiTable);
    ASSERT_EFI_ERROR (Status);

    mBoot.CmosIndex = PcdGet8 (PcdBootRegisterCmosIndex);
    Status = AcpiTable->InstallAcpiTable (AcpiTable, &mBoot, sizeof (mBoot), &TableKey);
    ASSERT_EFI_ERROR (Status);
  }

  if (EfiValueExists) {
    //
    // Write SimpleBootFlag variable
    //
    Status = gRT->SetVariable (
                    SIMPLE_BOOT_FLAG_VARIABLE_NAME,
                    &gEfiGlobalVariableGuid,
                    EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                    sizeof (EFI_SIMPLE_BOOT_FLAG),
                    &SimpleBootFlag
                    );
    ASSERT_EFI_ERROR (Status);
  }
  
  return EFI_SUCCESS;  
}

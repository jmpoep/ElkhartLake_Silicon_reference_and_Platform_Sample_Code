/** @file
  PCH Smm Library Services that implements both S/W SMI generation and detection.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2007 - 2016 Intel Corporation.

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


#include "CommonHeader.h"



/**
  Triggers a run time or boot time SMI.

  This function triggers a software SMM interrupt and set the APMC status with an 8-bit Data.

  @param  Data                 The value to set the APMC status.

**/
VOID
InternalTriggerSmi (
  IN UINT8                     Data
  )
{
  ASSERT(FALSE);
}


/**
  Triggers an SMI at boot time.

  This function triggers a software SMM interrupt at boot time.

**/
VOID
EFIAPI
TriggerBootServiceSoftwareSmi (
  VOID
  )
{
  ASSERT(FALSE);
}


/**
  Triggers an SMI at run time.

  This function triggers a software SMM interrupt at run time.

**/
VOID
EFIAPI
TriggerRuntimeSoftwareSmi (
  VOID
  )
{
  ASSERT(FALSE);
}


/**
  Gets the software SMI data.

  This function tests if a software SMM interrupt happens. If a software SMI happens,
  it retrieves the SMM data and returns it as a non-negative value; otherwise a negative
  value is returned.

  @return Data                 The data retrieved from SMM data port in case of a software SMI;
                               otherwise a negative value.

**/
INTN
InternalGetSwSmiData (
  VOID
  )
{
  ASSERT(FALSE);
  return -1;
}


/**
  Test if a boot time software SMI happened.

  This function tests if a software SMM interrupt happened. If a software SMM interrupt happened and
  it was triggered at boot time, it returns TRUE. Otherwise, it returns FALSE.

  @retval TRUE   A software SMI triggered at boot time happened.
  @retval FLASE  No software SMI happened or the software SMI was triggered at run time.

**/
BOOLEAN
EFIAPI
IsBootServiceSoftwareSmi (
  VOID
  )
{
  ASSERT(FALSE);
  return FALSE;
}


/**
  Test if a run time software SMI happened.

  This function tests if a software SMM interrupt happened. If a software SMM interrupt happened and
  it was triggered at run time, it returns TRUE. Otherwise, it returns FALSE.

  @retval TRUE   A software SMI triggered at run time happened.
  @retval FLASE  No software SMI happened or the software SMI was triggered at boot time.

**/
BOOLEAN
EFIAPI
IsRuntimeSoftwareSmi (
  VOID
  )
{
  ASSERT(FALSE);
  return FALSE;
}



/**

  Clear APM SMI Status Bit; Set the EOS bit.

**/
VOID
EFIAPI
ClearSmi (
  VOID
  )
{

  UINT16                       ABase;

  //
  // Get ABase
  //
  ABase = PcdGet16 (PcdPchAcpiIoPortBaseAddress);

  //
  // Clear the APM SMI Status Bit
  //
  IoWrite16 (ABase + R_PCH_ACPI_SMI_STS, B_PCH_ACPI_APM_STS);

  //
  // Set the EOS Bit
  //
  IoOr32 (ABase + R_PCH_ACPI_SMI_EN, B_PCH_ACPI_EOS);
}


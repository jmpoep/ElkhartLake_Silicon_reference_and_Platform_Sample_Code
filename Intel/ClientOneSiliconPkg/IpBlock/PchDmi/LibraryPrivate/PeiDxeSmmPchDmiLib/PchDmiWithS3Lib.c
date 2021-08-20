/** @file
  PCH DMI library with S3 boot script support.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/S3BootScriptLib.h>
#include <Register/PchPcrRegs.h>
#include <Register/PchDmiRegs.h>

#include "PchDmi14.h"
#include "PchDmi15.h"

/**
  Configure DMI Lock
**/
VOID
PchDmiSetLockWithS3BootScript (
  VOID
  )
{
  UINT32  Data32Or;
  UINT32  Data32And;
  UINT16  Address;

  Data32And = 0xFFFFFFFF;
  if (IsPchWithPdmi ()) {
    PchDmi15SrlRegData (&Address, &Data32Or);
  } else {
    PchDmi14SrlRegData (&Address, &Data32Or);
  }

  PchPcrAndThenOr32 (
    PID_DMI, Address,
    Data32And,
    Data32Or
    );
  PCH_PCR_BOOT_SCRIPT_READ_WRITE (
    S3BootScriptWidthUint32,
    PID_DMI, Address,
    &Data32Or,
    &Data32And
    );
}

/**
  Set BIOS interface Lock-Down
**/
VOID
PchDmiSetBiosLockDownWithS3BootScript (
  VOID
  )
{
  UINT32  Data32Or;
  UINT32  Data32And;

  //
  // Set BIOS Lock-Down (BILD)
  // When set, prevents GCS.BBS from being changed
  //
  Data32And = 0xFFFFFFFF;
  Data32Or = B_PCH_DMI_PCR_BILD;
  PchPcrAndThenOr32 (PID_DMI, R_PCH_DMI_PCR_GCS, Data32And, Data32Or);
  PCH_PCR_BOOT_SCRIPT_READ_WRITE (
    S3BootScriptWidthUint32,
    PID_DMI, R_PCH_DMI_PCR_GCS,
    &Data32Or,
    &Data32And
    );
}

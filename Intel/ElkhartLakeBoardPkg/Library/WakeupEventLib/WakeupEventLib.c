/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#include <PiPei.h>
#include <Library/DebugLib.h>
#include <Library/PmcLib.h>
#include <Library/IoLib.h>
#include <Register/PmcRegs.h>
#include <IndustryStandard/SmBios.h>

/**
  Parse the status registers for figuring out the wake-up event.

  @param[out]  WakeUpType       Updates the wakeuptype based on the status registers
**/
VOID
GetWakeupEvent (
  OUT  UINT8   *WakeUpType
  )
{
  UINT16             Pm1Sts;
  UINTN              Gpe0Sts;
  UINTN              Gpe0PmeSts;
  UINTN              Gpe0RiSts;
  UINT16             AcpiBase;

  DEBUG ((DEBUG_INFO, "GetWakeupEvent ()\n"));

  Gpe0Sts    = 0;
  Gpe0RiSts  = 0;
  Gpe0PmeSts = 0;
  AcpiBase = PmcGetAcpiBase ();

  ///
  /// Read the ACPI registers
  ///
  Pm1Sts     = IoRead16 (AcpiBase + R_ACPI_IO_PM1_STS);
  Gpe0Sts    = IoRead32 (AcpiBase + R_ACPI_IO_GPE0_STS_127_96);
  Gpe0RiSts  = Gpe0Sts & B_ACPI_IO_GPE0_STS_127_96_RI;
  Gpe0PmeSts = Gpe0Sts & B_ACPI_IO_GPE0_STS_127_96_PME;

  DEBUG ((DEBUG_INFO, "Gpe0Sts is: %02x\n", Gpe0Sts));
  DEBUG ((DEBUG_INFO, "ACPI Wake Status Register: %04x\n", Pm1Sts));

  ///
  /// Figure out the wake-up event
  ///
  if ((Pm1Sts & B_ACPI_IO_PM1_EN_PWRBTN) != 0 ) {
    *WakeUpType = SystemWakeupTypePowerSwitch;
  } else if ((Pm1Sts & B_ACPI_IO_PM1_STS_WAK) != 0) {
    if (Gpe0PmeSts != 0) {
      *WakeUpType = SystemWakeupTypePciPme;
    } else if (Gpe0RiSts != 0) {
      *WakeUpType = SystemWakeupTypeModemRing;
    } else if (Gpe0Sts != 0) {
      *WakeUpType = SystemWakeupTypeOther;
    } else {
      *WakeUpType = SystemWakeupTypeOther;
    }
  } else if ((Pm1Sts & B_ACPI_IO_PM1_STS_RTC) != 0) {
    *WakeUpType = SystemWakeupTypeApmTimer;
  } else {
    *WakeUpType = SystemWakeupTypeOther;
  }

  DEBUG ((DEBUG_INFO, "GetWakeupEvent : WakeUpType %x\n", *WakeUpType));
}

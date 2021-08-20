/** @file
  Source code file providing PUPDR ACPI table patch and publish

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
#include "PupdrDxe.h"

/*++

Routine Description:

  Get the information about OEM1.

Arguments:

  The Address of OEM1 table.

Returns:

  EFI_SUCCESS             Function executed successfully

--*/
VOID
GetPlatformOem1Data (
  OUT EFI_ACPI_EM_OEM_1_TABLE * Oem1
  )
{
  EFI_STATUS  Status;
  UINTN       VariableSize;
  SETUP_DATA  SetupData;


  VariableSize = sizeof (SETUP_DATA);
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &SetupData
                  );
  if (Status == EFI_SUCCESS) {
    Oem1->IaAppsRun   = SetupData.IaAppsRun;
    Oem1->IaAppsCap   = SetupData.IaAppsCap;
    Oem1->IaAppsToUse = SetupData.IaAppsToUse;
  }
  Oem1->BatChpType  = 1;

  Oem1->Header.OemTableId = EFI_ACPI_OEM1_TABLE_ID;

  DEBUG ((EFI_D_INFO, "Oem1->Header.OemTableId = %llx\n", Oem1->Header.OemTableId));
  DEBUG ((EFI_D_INFO, "Oem1->Header.Revision = %x\n\n", Oem1->Header.Revision));
  DEBUG ((EFI_D_INFO, "Oem1->FixedOption0 = %x\n", Oem1->FixedOption0));
  DEBUG ((EFI_D_INFO, "Oem1->FixedOption1 = %x\n", Oem1->FixedOption1));
  DEBUG ((EFI_D_INFO, "Oem1->DBIInGpioNumber = %d\n", Oem1->DBIInGpioNumber));
  DEBUG ((EFI_D_INFO, "Oem1->DBIOutGpioNumber = %d\n", Oem1->DBIOutGpioNumber));
  DEBUG ((EFI_D_INFO, "Oem1->BatChpType = %d\n", Oem1->BatChpType));
  DEBUG ((EFI_D_INFO, "Oem1->IaAppsRun = %d\n", Oem1->IaAppsRun));
  DEBUG ((EFI_D_INFO, "Oem1->BatIdDBIBase = %d\n", Oem1->BatIdDBIBase));
  DEBUG ((EFI_D_INFO, "Oem1->BatIdAnlgBase = %d\n", Oem1->BatIdAnlgBase));
  DEBUG ((EFI_D_INFO, "Oem1->IaAppsCap = %d\n", Oem1->IaAppsCap));
  DEBUG ((EFI_D_INFO, "Oem1->VBattFreqLmt = %d\n", Oem1->VBattFreqLmt));
  DEBUG ((EFI_D_INFO, "Oem1->CapFreqIdx = %d\n", Oem1->CapFreqIdx));
  DEBUG ((EFI_D_INFO, "Oem1->BatIdx = %d\n", Oem1->BatIdx));
  DEBUG ((EFI_D_INFO, "Oem1->IaAppsToUse = %d\n", Oem1->IaAppsToUse));
  DEBUG ((EFI_D_INFO, "Oem1->TurboChrg = %d\n", Oem1->TurboChrg));

  return;
}

/*++

  Routine Description:

    Update the RSCI table.
    TODO: Since this is the first draft, all the logic and definition should be reviewed when newer PUPDR(>0.3) and PMIC(>0.7) are out

  Arguments:

    *TableHeader   - The table to be set

  Returns:

    EFI_SUCCESS - Returns EFI_SUCCESS

--*/
VOID
PatchRsciTable (
  IN OUT   EFI_ACPI_DESCRIPTION_HEADER  *TableHeader
  )
{
  EFI_ACPI_RESET_SHUTDOWN_COMMUNICATION_INTERFACE * RsciTable;

  RsciTable = (EFI_ACPI_RESET_SHUTDOWN_COMMUNICATION_INTERFACE *)(UINTN)TableHeader;
  RsciTable->Header.OemTableId = EFI_ACPI_RSCI_OEM_TABLE_ID;
  //
  // Wake Sources
  //
  RsciTable->WakeSrc       = (UINT8)WAKE_NOT_APPLICABLE;
  RsciTable->Resets        = (UINT8)RESET_NOT_APPLICABLE;
  RsciTable->ShuntdownSrc  = (UINT8)SHTDWN_NOT_APPLICABLE;
  RsciTable->ResetType     = (UINT8)WARM_RESET;


  PupdrGetWakeSource (&RsciTable->WakeSrc);
  PupdrGetResetSource (&RsciTable->Resets, &RsciTable->ResetType);
  PupdrGetShutdownSource (&RsciTable->ShuntdownSrc);

  DEBUG((EFI_D_ERROR, "RsciTable->WakeSrc = 0x%X\n", RsciTable->WakeSrc));
  DEBUG((EFI_D_ERROR, "RsciTable->ResetType = 0x%X\n", RsciTable->ResetType));
  DEBUG((EFI_D_ERROR, "RsciTable->Resets = 0x%X\n", RsciTable->Resets));
  DEBUG((EFI_D_ERROR, "RsciTable->ShuntdownSrc = 0x%X\n", RsciTable->ShuntdownSrc));

  return;
}

/*++

Routine Description:

  This function will update any runtime platform specific information.
  This currently includes:
    Setting OEM table values, ID, table ID, creator ID and creator revision.
    Enabling the proper processor entries in the APIC tables.

Arguments:

  Table  -  The table to update

Returns:

  EFI_SUCCESS  -  The function completed successfully.

--*/
VOID
PupdrUpdateTables (
  IN OUT EFI_ACPI_COMMON_HEADER  *Table
  )
{
  switch (Table->Signature) {

    case EFI_ACPI_RESET_SHUTDOWN_COMMUNICATION_INTERFACE_SIGNATURE:
      PatchRsciTable ((EFI_ACPI_DESCRIPTION_HEADER *) Table);
      break;

    case EFI_ACPI_OEM1_SIGNATURE:
      GetPlatformOem1Data ((EFI_ACPI_EM_OEM_1_TABLE *) Table);
      break;

    default:
      break;
  }

  return;
}

VOID
PupdrGetWakeSource (
  OUT UINT8 *WakeSource
  )
{
  UINT16      PmcPm1En;
  UINT16      PmcPm1Sts;
  UINT16      AcpiBase;

  AcpiBase = PmcGetAcpiBase ();

  PmcPm1En = IoRead16 (AcpiBase + R_ACPI_IO_PM1_EN);
  PmcPm1Sts = IoRead16 (AcpiBase + R_ACPI_IO_PM1_STS);

  if ((PmcPm1En & B_ACPI_IO_PM1_EN_PWRBTN) && (PmcPm1Sts & B_ACPI_IO_PM1_STS_PWRBTN)) {
    *WakeSource = WAKE_POWER_BUTTON_PRESSED;
    DEBUG ((EFI_D_INFO, "[PUPDR] Wake source: WAKE_POWER_BUTTON_PRESSED\n"));
  } else if (PmcPm1Sts & B_ACPI_IO_PM1_STS_RTC) {
    *WakeSource = WAKE_RTC_TIMER;
    DEBUG ((EFI_D_INFO, "[PUPDR] Wake source: WAKE_RTC_TIMER\n"));
  } else {
    *WakeSource = WAKE_NOT_APPLICABLE;
  }
  return;
}

VOID
PupdrGetResetSource (
  OUT UINT8 *ResetSource,
  OUT UINT8 *ResetType
  )
{
  UINT32      PmcGenPmconA;
  UINT16      Tco2Sts;
  UINT32      PchPwrmBase;
  UINT16      TcoBase;

  PchTcoBaseGet (&TcoBase);
  PchPwrmBase = PmcGetPwrmBase ();

  Tco2Sts = IoRead16 (TcoBase + R_TCO_IO_TCO2_STS);
  PmcGenPmconA   = MmioRead32 (PchPwrmBase + R_PMC_PWRM_GEN_PMCON_A);

  DEBUG ((EFI_D_INFO, "[PUPDR] Reset source: PmcGenPmconA = 0x%X\n", PmcGenPmconA));
  DEBUG ((EFI_D_INFO, "[PUPDR] Reset source: Tco2Sts = 0x%X\n", Tco2Sts));

  if (Tco2Sts & B_TCO_IO_TCO2_STS_SECOND_TO) {
    *ResetSource = RESET_KERNEL_WATCHDOG;
    DEBUG ((EFI_D_INFO, "[PUPDR] Reset source: RESET_KERNEL_WATCHDOG\n"));
  } else {
    //
    // Reset from AOS is always cold reset
    //
    *ResetType   = COLD_RESET;
    *ResetSource = RESET_OS_INITIATED;
    DEBUG ((EFI_D_INFO, "[PUPDR] Reset source: RESET_OS_INITIATED via ACPI\n"));
  }

  if ((PmcGenPmconA & B_PMC_PWRM_GEN_PMCON_A_GBL_RST_STS) == B_PMC_PWRM_GEN_PMCON_A_GBL_RST_STS) {
    *ResetType = GLOBAL_RESET;
  }

  return;
}

VOID
PupdrGetShutdownSource (
  OUT UINT8 *ShutdownSource
  )
{
  UINT16      AcpiBase;
  UINT16      PmcPm1Sts;

  AcpiBase = PmcGetAcpiBase ();

  PmcPm1Sts = IoRead16 (AcpiBase + R_ACPI_IO_PM1_STS);

  if ((PmcPm1Sts & B_ACPI_IO_PM1_STS_PRBTNOR) == B_ACPI_IO_PM1_STS_PRBTNOR) {
    *ShutdownSource = SHTDWN_POWER_BUTTON_OVERRIDE;
    DEBUG((EFI_D_INFO, "[PUPDR] Shutdown source: SHTDWN_POWER_BUTTON_OVERRIDE\n"));
  }
  return;
}

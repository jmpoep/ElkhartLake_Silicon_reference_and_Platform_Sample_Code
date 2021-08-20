
/** @file
  Initializes the PCH HD Audio ACPI Tables.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Protocol/AcpiTable.h>
#include <DxeHdaNhlt.h>
#include <Library/DxeHdaNhltLib.h>
#include "PchInit.h"
#include <HdAudioConfig.h>
#include <PchConfigHob.h>
#include <Library/PcdLib.h>
#include <Protocol/PchPolicy.h>
#include <HdAudioConfig.h>
#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/HdaRegs.h>

#define XTAL_FREQ_24MHZ      0
#define XTAL_FREQ_38P4MHZ    1

/**
  Retrieves address of NHLT table from XSDT/RSDT.

  @retval NHLT_ACPI_TABLE*  Pointer to NHLT table if found
  @retval NULL              NHLT could not be found
**/
NHLT_ACPI_TABLE *
LocateNhltAcpiTable (
  VOID
  )
{
  EFI_ACPI_3_0_ROOT_SYSTEM_DESCRIPTION_POINTER  *Rsdp;
  EFI_ACPI_DESCRIPTION_HEADER                   *Xsdt;
  NHLT_ACPI_TABLE                               *Nhlt;
  UINTN                                         Index;
  UINT64                                        Data64;
  EFI_STATUS                                    Status;
  Rsdp  = NULL;
  Xsdt  = NULL;
  Nhlt  = NULL;

  ///
  /// Find the AcpiSupport protocol returns RSDP (or RSD PTR) address.
  ///
  DEBUG ((DEBUG_INFO, "LocateNhltAcpiTable() Start\n"));

  Status = EfiGetSystemConfigurationTable (&gEfiAcpiTableGuid, (VOID *) &Rsdp);
  if (EFI_ERROR (Status) || (Rsdp == NULL)) {
    DEBUG ((DEBUG_ERROR, "EFI_ERROR or Rsdp == NULL\n"));
    return NULL;
  }

  Xsdt = (EFI_ACPI_DESCRIPTION_HEADER *) (UINTN) Rsdp->XsdtAddress;
  if (Xsdt == NULL || Xsdt->Signature != EFI_ACPI_5_0_EXTENDED_SYSTEM_DESCRIPTION_TABLE_SIGNATURE) {
    // If XSDT has not been found, check RSDT
    Xsdt = (EFI_ACPI_DESCRIPTION_HEADER *) (UINTN) Rsdp->RsdtAddress;
    if (Xsdt == NULL || Xsdt->Signature != EFI_ACPI_5_0_ROOT_SYSTEM_DESCRIPTION_TABLE_SIGNATURE) {
      DEBUG ((DEBUG_ERROR, "XSDT/RSDT == NULL or wrong signature\n"));
      return NULL;
    }
  }

  for (Index = sizeof (EFI_ACPI_DESCRIPTION_HEADER); Index < Xsdt->Length; Index = Index + sizeof (UINT64)) {
    Data64  = *(UINT64 *) ((UINT8 *) Xsdt + Index);
    Nhlt    = (NHLT_ACPI_TABLE *) (UINTN) Data64;
    if (Nhlt != NULL && Nhlt->Header.Signature == NHLT_ACPI_TABLE_SIGNATURE) {
      break;
    }
    Nhlt = NULL;
  }

  if (Nhlt == NULL || Nhlt->Header.Signature != NHLT_ACPI_TABLE_SIGNATURE) {
    DEBUG ((DEBUG_ERROR, "Nhlt == NULL or wrong signature\n"));
    return NULL;
  }

  DEBUG ((DEBUG_INFO, "Found NhltTable, Address = 0x%016x\n", Nhlt));

  return Nhlt;
}

/**
  Sets NVS ACPI variables for HDAS._DSM and SNDW._DSD accordingly to policy.

  @param[in]                NhltAcpiTableAddress
  @param[in]                NhltAcpiTableLength
  @param[in]                *HdAudioConfigHob
  @param[in]                *HdAudioDxeConfig
**/
VOID
UpdateHdaAcpiData (
  IN       UINT64                 NhltAcpiTableAddress,
  IN       UINT32                 NhltAcpiTableLength,
  IN CONST HDAUDIO_HOB            *HdAudioConfigHob,
  IN CONST HDAUDIO_DXE_CONFIG     *HdAudioDxeConfig
  )
{
  DEBUG ((DEBUG_INFO, "UpdateHdaAcpiData():\n NHLT Address = 0x%016x, Length = 0x%08x\n", NhltAcpiTableAddress, NhltAcpiTableLength));
  DEBUG ((DEBUG_INFO, " FeatureMask = 0x%08x\n", HdAudioDxeConfig->DspFeatureMask));
  mPchNvsAreaProtocol.Area->XTAL = XTAL_FREQ_38P4MHZ;
  mPchNvsAreaProtocol.Area->NHLA = NhltAcpiTableAddress;
  mPchNvsAreaProtocol.Area->NHLL = NhltAcpiTableLength;
  mPchNvsAreaProtocol.Area->ADFM = HdAudioDxeConfig->DspFeatureMask;

  if (HdAudioConfigHob->DspEnable || HdAudioConfigHob->DspUaaCompliance == FALSE) {
    mPchNvsAreaProtocol.Area->SWQ0 = HdAudioConfigHob->AudioLinkSndw1 ? 0 : BIT1;
    mPchNvsAreaProtocol.Area->SWQ1 = HdAudioConfigHob->AudioLinkSndw2 ? 0 : BIT1;
    mPchNvsAreaProtocol.Area->SWQ2 = HdAudioConfigHob->AudioLinkSndw3 ? 0 : BIT1;
    mPchNvsAreaProtocol.Area->SWQ3 = HdAudioConfigHob->AudioLinkSndw4 ? 0 : BIT1;
  } else {
    mPchNvsAreaProtocol.Area->SWQ0 = BIT1;
    mPchNvsAreaProtocol.Area->SWQ1 = BIT1;
    mPchNvsAreaProtocol.Area->SWQ2 = BIT1;
    mPchNvsAreaProtocol.Area->SWQ3 = BIT1;
  }

  mPchNvsAreaProtocol.Area->ACS0 = (UINT8)HdAudioDxeConfig->SndwConfig[0].AutonomousClockStop;
  mPchNvsAreaProtocol.Area->ACS1 = (UINT8)HdAudioDxeConfig->SndwConfig[1].AutonomousClockStop;
  mPchNvsAreaProtocol.Area->ACS2 = (UINT8)HdAudioDxeConfig->SndwConfig[2].AutonomousClockStop;
  mPchNvsAreaProtocol.Area->ACS3 = (UINT8)HdAudioDxeConfig->SndwConfig[3].AutonomousClockStop;

  mPchNvsAreaProtocol.Area->DAI0 = (UINT8)HdAudioDxeConfig->SndwConfig[0].DataOnActiveIntervalSelect;
  mPchNvsAreaProtocol.Area->DAI1 = (UINT8)HdAudioDxeConfig->SndwConfig[1].DataOnActiveIntervalSelect;
  mPchNvsAreaProtocol.Area->DAI2 = (UINT8)HdAudioDxeConfig->SndwConfig[2].DataOnActiveIntervalSelect;
  mPchNvsAreaProtocol.Area->DAI3 = (UINT8)HdAudioDxeConfig->SndwConfig[3].DataOnActiveIntervalSelect;

  mPchNvsAreaProtocol.Area->DOD0 = (UINT8)HdAudioDxeConfig->SndwConfig[0].DataOnDelaySelect;
  mPchNvsAreaProtocol.Area->DOD1 = (UINT8)HdAudioDxeConfig->SndwConfig[1].DataOnDelaySelect;
  mPchNvsAreaProtocol.Area->DOD2 = (UINT8)HdAudioDxeConfig->SndwConfig[2].DataOnDelaySelect;
  mPchNvsAreaProtocol.Area->DOD3 = (UINT8)HdAudioDxeConfig->SndwConfig[3].DataOnDelaySelect;
}

/**
  Initialize Intel High Definition Audio ACPI Tables

  @retval EFI_SUCCESS             The function completed successfully
  @retval EFI_LOAD_ERROR          ACPI table cannot be installed
  @retval EFI_UNSUPPORTED         ACPI table not set because DSP is disabled
**/
EFI_STATUS
PchHdAudioAcpiInit (
  VOID
  )
{
  EFI_STATUS                    Status;
  UINT64                        HdaPciBase;
  CONST HDAUDIO_HOB             *HdAudioConfigHob;
  PCH_POLICY_PROTOCOL           *PchPolicy;
  HDAUDIO_DXE_CONFIG            *HdAudioDxeConfig;
  NHLT_ACPI_TABLE               *NhltTable;


  DEBUG ((DEBUG_INFO, "PchHdAudioAcpiInit() Start\n"));

  HdAudioConfigHob = &mPchConfigHob->HdAudio;

  ///
  /// Get PCH Policy Protocol
  ///
  Status = gBS->LocateProtocol (&gPchPolicyProtocolGuid, NULL, (VOID **)&PchPolicy);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Get HD Audio DXE Config Block
  ///
  Status = GetConfigBlock ((VOID *)PchPolicy, &gHdAudioDxeConfigGuid, (VOID *)&HdAudioDxeConfig);
  ASSERT_EFI_ERROR (Status);

  HdaPciBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PCI_DEVICE_NUMBER_PCH_HDA,
                 PCI_FUNCTION_NUMBER_PCH_HDA,
                 0
                 );

  if ((PciSegmentRead16 (HdaPciBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) || (HdAudioConfigHob->DspEnable == FALSE)) {
    // Do not set ACPI tables if HDAudio is Function disabled or DSP is disabled
    DEBUG ((DEBUG_INFO, "AudioDSP: Non-HDAudio ACPI Table (NHLT) not set!\n"));
    return EFI_UNSUPPORTED;
  }

  NhltTable = LocateNhltAcpiTable ();
  if (NhltTable == NULL) {
    return EFI_LOAD_ERROR;
  }

  UpdateHdaAcpiData ((UINT64) (UINTN) NhltTable, (UINT32) (NhltTable->Header.Length), HdAudioConfigHob, HdAudioDxeConfig);
  DEBUG_CODE ( NhltAcpiTableDump (NhltTable); );

  DEBUG ((DEBUG_INFO, "PchHdAudioAcpiInit() End - Status = %r\n", Status));
  return Status;
}


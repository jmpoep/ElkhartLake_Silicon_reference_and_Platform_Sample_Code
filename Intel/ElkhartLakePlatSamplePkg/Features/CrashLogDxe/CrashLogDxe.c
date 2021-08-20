/** @file
This DXE driver supports the CrashLog Feature.

@copyright
INTEL CONFIDENTIAL
Copyright 2016 - 2019 Intel Corporation.

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

#include "CrashLogDxe.h"

///
/// Boot Error Record Table (BERT) instance
///
STATIC  EFI_ACPI_6_1_BOOT_ERROR_RECORD_TABLE_HEADER  *mBert;

STATIC EFI_ACPI_TABLE_PROTOCOL       *mAcpiTbl = NULL;
STATIC BOOLEAN                       mPmcCrashLogSupport = FALSE;
STATIC BOOLEAN                       mCpuCrashLogSupport = FALSE;
STATIC UINT32                        mPmcCrashLogDataBuffer = 0;
STATIC UINT32                        mCpuCrashLogDataBuffer = 0;
STATIC UINT32                        mPmcCrashLogSize = 0;
STATIC UINT32                        mCpuCrashLogSize = 0;
STATIC UINT8                         *mCrashLogDest = NULL;
/**

  Update Platform & OEM ID's in Whea ACPI tables

  @param[in]  TableHeader  BERT Table Header Pointer

**/
VOID
UpdateAcpiTableIds (
  EFI_ACPI_DESCRIPTION_HEADER     *TableHeader
  )
{
  //
  // Update the OEMID, OEM revision, OEM TABLE ID, Creator ID and Creator revision
  //
  *(UINT32 *)(TableHeader->OemId) = 'I' + ('N' << 8) + ('T' << 16) + ('E' << 24);
  *(UINT16 *)(TableHeader->OemId + 4) = 'L' + (' ' << 8);

  TableHeader->OemTableId = EFI_ACPI_OEM_TABLE_ID;
  TableHeader->OemRevision = EFI_WHEA_OEM_REVISION;
  TableHeader->CreatorId = EFI_ACPI_CREATOR_ID;
  TableHeader->CreatorRevision = EFI_ACPI_CREATOR_REVISION;
}

/**
  Get PMC Crash log

  @retval EFI_SUCCESS             The function completes successfully

**/
EFI_STATUS
GetPmcCrashLog (
  )
{
  UINT8              *CrashLogAddr = NULL;
  UINT32             CrashLogSize = 0;
  CRASHLOG_FIELD     *CrashLogField = NULL;

  DEBUG ((DEBUG_INFO, "BERT Pmc CrashLog Destination = 0x%x \n ", mCrashLogDest));

  CrashLogAddr = (UINT8 *) (UINTN) mPmcCrashLogDataBuffer;
  DEBUG ((DEBUG_INFO, "Value at CrashLogAddress 0x%x = 0x%x \n ", (UINTN)CrashLogAddr, *CrashLogAddr));
  CrashLogField = (CRASHLOG_FIELD *) CrashLogAddr;
  if (CrashLogField->CrashLogVersion != 0) {
    DEBUG ((DEBUG_INFO, "Pmc CrashLog is present, CrashLogVersion = 0x%x\n", CrashLogField->CrashLogVersion));
  } else {
    return EFI_NOT_FOUND;
  }
  DEBUG ((DEBUG_INFO, "Pmc Crash Data Collection\n"));
  while (CrashLogSize < (mPmcCrashLogSize)) {
    *mCrashLogDest = *CrashLogAddr;
    if (CrashLogSize < CRASHLOG_SIZE_DEBUG_PURPOSE) { // Dumping only few bytes to help debug
      DEBUG ((DEBUG_INFO, "CrashData = 0x%x\n", *mCrashLogDest));
    }
    mCrashLogDest++;
    CrashLogAddr++;
    CrashLogSize++;
  }

  DEBUG ((DEBUG_INFO, "Copied Pmc CrasLog Size = 0x%x\n", CrashLogSize));

  return EFI_SUCCESS;
}

/**
  Get Cpu Crash log

  @retval EFI_SUCCESS             The function completes successfully

**/
EFI_STATUS
GetCpuCrashLog (
  )
{
  UINT8             *CrashLogAddr = NULL;
  UINT32             CrashLogSize = 0;

  DEBUG ((DEBUG_INFO, "BERT Cpu CrashLog Destination = 0x%x \n ", mCrashLogDest));

  CrashLogAddr = (UINT8 *) (UINTN) mCpuCrashLogDataBuffer;
  DEBUG ((DEBUG_INFO, "Value at CrashLogAddress 0x%x = 0x%x \n ", (UINTN)CrashLogAddr, (UINT32) *CrashLogAddr));
  if (mCpuCrashLogSize > 0) {
    DEBUG ((DEBUG_INFO, "Cpu CrashLog is present.\n"));
  } else {
    return EFI_NOT_FOUND;
  }
  DEBUG ((DEBUG_INFO, "Cpu Crash Data Collection\n"));
  while (CrashLogSize < (mCpuCrashLogSize)) {
    *mCrashLogDest = *CrashLogAddr;
    if (CrashLogSize < CRASHLOG_SIZE_DEBUG_PURPOSE) { // Dumping only few bytes to help debug
      DEBUG ((DEBUG_INFO, "CrashData = 0x%x\n", *mCrashLogDest));
    }
    mCrashLogDest++;
    CrashLogAddr++;
    CrashLogSize++;
  }
  DEBUG ((DEBUG_INFO, "Copied Cpu CrasLog Size = 0x%x\n", CrashLogSize));

  return EFI_SUCCESS;
}

/**

  Add a new Firmware CrashLog Entry to existing Error Status Block.

  @param[in] ErrStsBlk                          BERT GENERIC_ERROR_STATUS instance.
  @param[in out] FirmwareGenericErrorAddr       Pointer to this FirmwareGenericError entry address, updated on return.
  @param[in out] FirmwareCrashLogPayloadAddr    Pointer to Firmware CrashLog Entry payload address, updated on return.
  @param[in] EntrySize                          Firmware CrashLog Entry payload size.
  @param[in] EntrySource                        Firmware CrashLog Entry source.
  @param[in] EntryVersion                       Firmware CrashLog Entry version.

**/

VOID
AddFirmwareCrashLogEntry (
  IN     EFI_ACPI_6_1_GENERIC_ERROR_STATUS_STRUCTURE    *ErrStsBlk,
  IN OUT FIRMWARE_GENERIC_ERROR                         **FirmwareGenericErrorAddr,
  IN OUT UINT8                                          **FirmwareCrashLogPayloadAddr,
  IN     UINT32                                         EntrySize,
  IN     UINT32                                         EntrySource,
  IN     UINT32                                         EntryVersion
  )
{
  FIRMWARE_GENERIC_ERROR  *FirmwareGenericError = NULL;

  FirmwareGenericError = (FIRMWARE_GENERIC_ERROR*)((UINT8*)(void*)ErrStsBlk + ErrStsBlk->DataLength + sizeof (EFI_ACPI_6_1_GENERIC_ERROR_STATUS_STRUCTURE));
  ZeroMem (FirmwareGenericError, sizeof (FIRMWARE_GENERIC_ERROR));

  CopyMem (&FirmwareGenericError->GenericErrorDataEntry.SectionType, &gEfiFirmwareErrorSectionGuid, sizeof (EFI_GUID));
  FirmwareGenericError->GenericErrorDataEntry.ErrorSeverity = EFI_ACPI_6_1_ERROR_SEVERITY_FATAL;
  FirmwareGenericError->GenericErrorDataEntry.Revision = EFI_ACPI_6_1_GENERIC_ERROR_DATA_ENTRY_REVISION;
  FirmwareGenericError->GenericErrorDataEntry.ValidationBits = 0;
  FirmwareGenericError->GenericErrorDataEntry.ErrorDataLength = EntrySize + sizeof (EFI_FIRMWARE_ERROR_DATA);
  FirmwareGenericError->EfiFirmwareErrorData.ErrorType = 1; //FW CrashLog Error Record
  FirmwareGenericError->EfiFirmwareErrorData.Revision = EFI_2_7_FIRMWARE_ERROR_RECORD_REVISION;
  FirmwareGenericError->EfiFirmwareErrorData.RecordId = (UINT64) (((UINT64) EntryVersion << 32) | EntrySource);

  ErrStsBlk->DataLength += FirmwareGenericError->GenericErrorDataEntry.ErrorDataLength + sizeof (EFI_ACPI_6_1_GENERIC_ERROR_DATA_ENTRY_STRUCTURE);
  ErrStsBlk->BlockStatus.ErrorDataEntryCount++;

  *FirmwareGenericErrorAddr = FirmwareGenericError;
  *FirmwareCrashLogPayloadAddr = (UINT8*)(void*) FirmwareGenericError + sizeof (FIRMWARE_GENERIC_ERROR);
}

/**
  Get PMC, PUNIT, CPU Crash Log, and initialize the APEI BERT GENERIC_ERROR_STATUS structure

  @param[in] ErrStsBlk            BERT GENERIC_ERROR_STATUS instance.

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
GenFwBootErrorlog (
  IN EFI_ACPI_6_1_GENERIC_ERROR_STATUS_STRUCTURE    *ErrStsBlk
  )
{
  EFI_STATUS                    Status = EFI_SUCCESS;
  UINT32                        PmcCrashLogVersion = 0;
  FIRMWARE_GENERIC_ERROR        *PmcFirmwareGenericError = NULL;
  UINT32                        CrashLogSize;

  CrashLogSize = mPmcCrashLogSize + mCpuCrashLogSize;
  if (ErrStsBlk == NULL) {
    return EFI_NOT_FOUND;
  }
  //
  // Get the version of each component
  //
  PmcCrashLogVersion   = *(UINT32*)(UINTN) mPmcCrashLogDataBuffer;
  DEBUG ((DEBUG_INFO, "PmcCrashLogVersion = 0x%x\n", PmcCrashLogVersion));

  ErrStsBlk->RawDataOffset = 0;
  ErrStsBlk->RawDataLength = 0;
  ErrStsBlk->ErrorSeverity = EFI_ACPI_6_1_ERROR_SEVERITY_FATAL;
  ErrStsBlk->BlockStatus.ErrorDataEntryCount = 0;
  ErrStsBlk->DataLength = 0;

  AddFirmwareCrashLogEntry (ErrStsBlk, &PmcFirmwareGenericError, &mCrashLogDest, CrashLogSize, 0, PmcCrashLogVersion);
  Status = GetPmcCrashLog ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "PMC CrashLog not present\n"));
    mPmcCrashLogSupport = FALSE;
  }
  Status = GetCpuCrashLog ();
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "CPU CrashLog not present\n"));
    mCpuCrashLogSupport = FALSE;
  }
  if (mPmcCrashLogSupport == FALSE && mCpuCrashLogSupport == FALSE) {
    return EFI_NOT_FOUND;
  }

  ErrStsBlk->BlockStatus.MultipleUncorrectableErrors = 1;
  ErrStsBlk->BlockStatus.UncorrectableErrorValid = 1;

  mBert->BootErrorRegionLength = ErrStsBlk->DataLength + sizeof (EFI_ACPI_6_1_GENERIC_ERROR_STATUS_STRUCTURE);

  DEBUG ((DEBUG_INFO, " ErrStsBlk->DataLength = 0x%x\n", ErrStsBlk->DataLength));
  DEBUG ((DEBUG_INFO, " ErrorStatusBlock Size = 0x%x\n", mBert->BootErrorRegionLength));
  DEBUG ((DEBUG_INFO, " PmcFirmwareGenericError->GenericErrorDataEntry.ErrorDataLength = 0x%x\n", PmcFirmwareGenericError->GenericErrorDataEntry.ErrorDataLength));
  DEBUG ((DEBUG_INFO, " PmcCrashLogSize = 0x%x\n", mPmcCrashLogSize));
  DEBUG ((DEBUG_INFO, " CpuCrashLogSize = 0x%x\n", mCpuCrashLogSize));

  return EFI_SUCCESS;
}

/**
  Log firmware boot error log  in APEI BERT.

  @param[in] BootErrorTable       APEI BERT address.

  @retval EFI_SUCCESS             The function completes successfully
**/
EFI_STATUS
LogFwBootErrorlog (
  IN EFI_ACPI_6_1_BOOT_ERROR_RECORD_TABLE_HEADER    *BootErrorTable
  )
{
  EFI_ACPI_6_1_GENERIC_ERROR_STATUS_STRUCTURE       *ErrStsBlk;

  if (BootErrorTable == NULL) {
    return EFI_NOT_FOUND;
  }

  ErrStsBlk = (EFI_ACPI_6_1_GENERIC_ERROR_STATUS_STRUCTURE *) (UINTN) BootErrorTable->BootErrorRegion;
  if (ErrStsBlk->DataLength >= BootErrorTable->BootErrorRegionLength) {
    return EFI_OUT_OF_RESOURCES;
  }
  return GenFwBootErrorlog (ErrStsBlk);
}

/**
  Install ACPI table for APEI BERT

  @param[in] Bert             APEI BERT Instance.

  @retval EFI_SUCCESS             The function completes successfully
**/
STATIC
EFI_STATUS
InstallApeiBertTables (
  EFI_ACPI_6_1_BOOT_ERROR_RECORD_TABLE_HEADER   *Bert
  )
{
  EFI_STATUS            Status;
  UINTN                 TableKey;

  Status = EFI_SUCCESS;

  if (Bert == NULL) {
    return EFI_INVALID_PARAMETER;
  }


  if (mAcpiTbl) {
    DEBUG ((DEBUG_INFO, "APEI Support. Install BERT Table \n"));
    TableKey = 0;
    Status = mAcpiTbl->InstallAcpiTable (
                         mAcpiTbl,
                         Bert,
                         Bert->Header.Length,
                         &TableKey
                         );
  }

  return Status;
}

/**
  Discover CrashLog
**/
BOOLEAN
DiscoverCrashLog (
  VOID
  )
{
  EFI_STATUS                      Status;
  PMC_IPC_DISCOVERY_BUF           DiscoveryBuffer;
  TEL_CRASHLOG_DEVSC_CAP          CrashLogDevscCap;
  BOOLEAN                         CrashLogSupport;

  Status = EFI_SUCCESS;
  CrashLogSupport = FALSE;
  ZeroMem (&DiscoveryBuffer, sizeof (PMC_IPC_DISCOVERY_BUF));

  //
  // PCH CrashLog Discovery
  //
  Status = PmcCrashLogDiscovery (&DiscoveryBuffer);

  DEBUG ((DEBUG_INFO, "PCH CrashLog Discovery Value = 0x%x , Status = %r, Avail = %d, Dis = %d\n", DiscoveryBuffer.Uint32, Status, DiscoveryBuffer.Bits.Avail, DiscoveryBuffer.Bits.Dis));

  if (EFI_ERROR (Status) || (DiscoveryBuffer.Bits.Avail != 1) || (DiscoveryBuffer.Bits.Dis == 1)) {
    DEBUG ((DEBUG_INFO, "PCH CrashLog feature not supported\n"));
  } else {
    mPmcCrashLogSupport = TRUE;
    CrashLogSupport = TRUE;
    //
    // Update Crash Log Size on PMC SSRAM
    //
    mPmcCrashLogSize = (DiscoveryBuffer.Bits.Size != 0) ? (DiscoveryBuffer.Bits.Size * sizeof (UINT32)) : 0xC00;
    DEBUG ((DEBUG_INFO, "PMC CrashLog Size = 0x%x\n", mPmcCrashLogSize));
  }

  //
  // CPU CrashLog Discovery
  //
  Status = GetCpuCrashLogCapability (&CrashLogDevscCap);

  if (EFI_ERROR (Status) ) {
    DEBUG ((DEBUG_INFO, "CPU CrashLog feature not supported\n"));
  } else {
    mCpuCrashLogSupport = TRUE;
    CrashLogSupport = TRUE;
  }

  return CrashLogSupport;
}

/**
  Entry point of the CrashLog support driver.

  @param[in]  ImageHandle   EFI_HANDLE: A handle for the image that is initializing this driver
  @param[in]  SystemTable   EFI_SYSTEM_TABLE: A pointer to the EFI system table

  @retval  EFI_SUCCESS:              Driver initialized successfully
           EFI_LOAD_ERROR:           Failed to Initialize or to Load the driver
           EFI_OUT_OF_RESOURCES:     Could not allocate needed resources
**/
EFI_STATUS
EFIAPI
InstallCrashLogSupport (
  IN EFI_HANDLE                ImageHandle,
  IN EFI_SYSTEM_TABLE          *SystemTable
  )
{
  EFI_STATUS                   Status;
  SETUP_DATA                   SetupData;
  UINTN                        VariableSize;
  UINT32                       VariableAttributes;
  BOOLEAN                      CreateBertTableOrNot;
  EFI_HOB_GUID_TYPE            *CrashLogDataBufferHob;
  UINT32                       BootErrorRegionSize;
  CPU_CRASHLOG_HOB             *CpuCrashLogHob;

  CreateBertTableOrNot = FALSE;
  VariableSize = sizeof (SETUP_DATA);

  DEBUG ((DEBUG_INFO, "CrashLog Entry Point\n"));
  Status = gRT->GetVariable (
                  L"Setup",
                  &gSetupVariableGuid,
                  &VariableAttributes,
                  &VariableSize,
                  &SetupData
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (!SetupData.EnableCrashLog) {
    //
    // The PCH CrashLog Disable.
    //
    DEBUG ((DEBUG_INFO, "Disable PCH CrashLog Feature\n"));
    Status = PmcCrashLogDisable ();
    //
    // Check for the CrashLog feature, if it is available or not.
    //
    CreateBertTableOrNot = DiscoverCrashLog ();
    if (!CreateBertTableOrNot) {
      DEBUG ((DEBUG_INFO, "CrashLog Feature is disabled\n"));
    }
    return Status;
  }

  //
  // Check for the CrashLog feature, if it is available or not.
  //
  CreateBertTableOrNot = DiscoverCrashLog ();
  if (!CreateBertTableOrNot) {
    DEBUG ((DEBUG_ERROR, "DiscoverCrashLog: CrashLog is not supported \n"));
    return EFI_UNSUPPORTED;
  }

  if (mPmcCrashLogSupport) {
    if (SetupData.CrashLogOnAllReset) {
      DEBUG ((DEBUG_INFO, "Crash Log on All Reset \n"));
      //
      // Collect crash data on every boot
      //
      Status = PmcCrashLogOnAllReset ();
      DEBUG ((DEBUG_INFO, "PMC IPC to collect Crash Log on every reset successful\n"));
    }
  }

  DEBUG ((DEBUG_INFO, "BERT Init\n"));

  CrashLogDataBufferHob = GetFirstGuidHob (&gPmcCrashLogDataBufferHobGuid);
  if (CrashLogDataBufferHob != NULL) {
    mPmcCrashLogDataBuffer = (UINT32) (*(UINTN *) GET_GUID_HOB_DATA (CrashLogDataBufferHob));
  }

  DEBUG ((DEBUG_INFO, "PmcCrashLogDataBuffer = 0x%x \n ", mPmcCrashLogDataBuffer));

  if (mPmcCrashLogDataBuffer == 0) {
    DEBUG ((DEBUG_ERROR, "PMC CrashLog data is not present \n"));
    mPmcCrashLogSupport = FALSE;
  }

  CrashLogDataBufferHob = GetFirstGuidHob (&gCpuCrashLogDataBufferHobGuid);
  if (CrashLogDataBufferHob != NULL) {
    CpuCrashLogHob = (CPU_CRASHLOG_HOB *) GET_GUID_HOB_DATA (CrashLogDataBufferHob);
    mCpuCrashLogDataBuffer = (UINT32) (CpuCrashLogHob->AllocateAddress);
    mCpuCrashLogSize = CpuCrashLogHob->Size;
    DEBUG ((DEBUG_INFO, "CpuCrashLogDataBuffer = 0x%x\n", mCpuCrashLogDataBuffer));
    DEBUG ((DEBUG_INFO, "CpuCrashLogSize = 0x%x\n", mCpuCrashLogSize));
  }

  if (mCpuCrashLogDataBuffer == 0) {
    DEBUG ((DEBUG_ERROR, "Cpu CrashLog data is not present\n"));
    mCpuCrashLogSupport = FALSE;
  }

  if ((mPmcCrashLogSupport == FALSE) && (mCpuCrashLogSupport == FALSE)) {
    DEBUG ((DEBUG_ERROR, "CrashLog is not supported \n"));
    return EFI_NOT_READY;
  }

  //
  // Allocate memory for BERT table
  //
  mBert = (EFI_ACPI_6_1_BOOT_ERROR_RECORD_TABLE_HEADER *) AllocateZeroPool (sizeof (EFI_ACPI_6_1_BOOT_ERROR_RECORD_TABLE_HEADER));

  if (mBert == NULL) {
    DEBUG ((DEBUG_ERROR, "Unable to Allocate Memory for BERT Record Creation\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Fill EFI_ACPI_DESCRIPTION_HEADER structure
  //
  mBert->Header.Signature = EFI_ACPI_6_1_BOOT_ERROR_RECORD_TABLE_SIGNATURE;
  mBert->Header.Length = sizeof (EFI_ACPI_6_1_BOOT_ERROR_RECORD_TABLE_HEADER);
  mBert->Header.Revision = EFI_ACPI_6_1_BOOT_ERROR_RECORD_TABLE_REVISION;
  mBert->Header.Checksum = 0;
  UpdateAcpiTableIds (&mBert->Header);
  //
  // Allocate memory space Error status blocks
  // Allocate memort space for Errorlog Address range, Fill EFI_ACPI_6_1_BOOT_ERROR_RECORD_TABLE_HEADER(mBert) structure
  //
  BootErrorRegionSize = sizeof (EFI_ACPI_6_1_GENERIC_ERROR_STATUS_STRUCTURE) + sizeof (FIRMWARE_GENERIC_ERROR) + mPmcCrashLogSize + mCpuCrashLogSize;
  mBert->BootErrorRegion = (UINT64) AllocateReservedZeroPool ((UINTN) BootErrorRegionSize);

  DEBUG ((DEBUG_INFO, "mBert->BootErrorRegion     = %x\n", (UINTN)mBert->BootErrorRegion));
  DEBUG ((DEBUG_INFO, "mBert->BootErrorRegionSize = %x\n", BootErrorRegionSize));

  if (mBert->BootErrorRegion == 0) {
    DEBUG ((DEBUG_ERROR, "Unable to Allocate Memory for Boot Error Record Data\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  mBert->BootErrorRegionLength = BootErrorRegionSize;

  Status = LogFwBootErrorlog (mBert);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "No Pmc or Punit or Cpu error log found\n"));
    return EFI_NOT_FOUND;
  }
  mAcpiTbl = NULL;
  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, (VOID **) &mAcpiTbl);
  ASSERT_EFI_ERROR (Status);

  Status = InstallApeiBertTables (mBert);
  if (EFI_ERROR (Status) && (Status != EFI_ALREADY_STARTED)) {
    DEBUG ((DEBUG_ERROR, "Not able to install ACPI table for APEI BERT \n"));
  }

  if (mBert != NULL) {
    FreePool (mBert);
  }

  DEBUG ((DEBUG_INFO, "CrashLog Exit \n"));
  return Status;
}

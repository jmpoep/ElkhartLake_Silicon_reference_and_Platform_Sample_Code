/**@file
  Hardware Root of Trust ACPI Table

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2019-2020 Intel Corporation.

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

@par Specification
**/

#include "AcpiPsds.h"
#include <MeBiosPayloadHob.h>
#include <Library/BaseMemoryLib.h>
#include <Library/CpuPlatformLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Uefi.h>
#include <Base.h>
#include <IndustryStandard/Acpi.h>
#include <Library/DxeServicesTableLib.h>
#include <Protocol/AcpiTable.h>
#include <MkhiMsgs.h>
#include <Register/HeciRegs.h>
#include <Register/MeRegs.h>
#include <Library/PciSegmentLib.h>
#include <Guid/GlobalVariable.h>
#include <Library/ReportStatusCodeLib.h>
#include <MeState.h>
#include <Library/DxeMeLib.h>
#include <Register/ArchitecturalMsr.h>



#define PSD_VERSION_MAJOR                               0x0000
#define PSD_VERSION_MINOR                               0x0003
#define CPUID_SGX_ENABLED                               0x12
#define PSD_HROT_NONE                                   0
#define PSD_HROT_ROM                                    1
#define PSD_HROT_TXE                                    2
#define PSD_HROT_CSE                                    3
#define PSD_HROT_ACM                                    4
#define PSD_HROT_TXT                                    5

/**
  Wrapper function to Get EOM status from CSE Status Register.

  @param[in,out] EomState         Pointer to The EOM state value.

  @retval EFI_SUCCESS         The EOM Get Status successfully.
  @retval Others              The EOM Get from CSE doesn't get status.

 **/
EFI_STATUS
GetEomState (
  IN OUT UINT8 *EomState
  )
{

  HECI_FW_STS6_REGISTER             MeFirmwareStatus;
  UINT64                            HeciBaseAddress;

  if(EomState == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *EomState = 0;
  HeciBaseAddress = PCI_SEGMENT_LIB_ADDRESS (ME_SEGMENT, ME_BUS, ME_DEVICE_NUMBER, HECI_FUNCTION_NUMBER, 0);
  if (PciSegmentRead16 (HeciBaseAddress + PCI_DEVICE_ID_OFFSET) == 0xFFFF) {
    REPORT_STATUS_CODE (EFI_ERROR_CODE, SW_HECI_GET_MODE_ERROR | EFI_STATUS_TO_STATUS_CODE_VALUE (EFI_NOT_FOUND));
    return EFI_NOT_FOUND;
  }

  //with Flexible Manufacturing mode following bit is EOM
  MeFirmwareStatus.ul = PciSegmentRead32 (HeciBaseAddress + R_ME_HFS_6);
  //need to invert it to make interpretation compatible with PSD spec-3.0
  *EomState = (UINT8)(!(MeFirmwareStatus.r.FpfSocConfigLock));
  DEBUG((DEBUG_INFO, "EomState Status=0x%x R_ME_HFS_6[30] = 0x%x \n", *EomState, (UINT8)(MeFirmwareStatus.r.FpfSocConfigLock) ));
  return EFI_SUCCESS;
}

/**
Get Sec FW Version.
@param[in]: SecVersion Pointer to  Sec FW Version structure.
@return EFI_SUCCESS.
@return EFI_ERROR.

**/
EFI_STATUS
GetSecFwVersion(
    SEC_VERSION_INFO *SecVersion
  )
{
  EFI_STATUS   Status;
  GET_FW_VER_ACK_DATA MsgGenGetFwVersionAckData;

  //MBP gets Firmware update info from ME client
  ME_BIOS_PAYLOAD_HOB *MbpHob;

  if (SecVersion == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MbpHob = NULL;

  //
  // Get Mbp Data HOB
  //
  MbpHob = GetFirstGuidHob(&gMeBiosPayloadHobGuid);
  if (MbpHob == NULL) {
    DEBUG((DEBUG_INFO, "HeciGetMeFwInfo: No MBP Data Protocol available calling Heci API\n"));
    Status = HeciGetFwVersionMsg(&MsgGenGetFwVersionAckData);
    if (Status == EFI_SUCCESS) {
      SecVersion->CodeMajor = MsgGenGetFwVersionAckData.CodeMajor;
      SecVersion->CodeMinor = MsgGenGetFwVersionAckData.CodeMinor;
      SecVersion->CodeHotFix = MsgGenGetFwVersionAckData.CodeHotFix;
      SecVersion->CodeBuildNo = MsgGenGetFwVersionAckData.CodeBuildNo;
    }
   } else {

    SecVersion->CodeMajor   =  MbpHob->MeBiosPayload.FwVersionName.MajorVersion;
    SecVersion->CodeMinor   =  MbpHob->MeBiosPayload.FwVersionName.MinorVersion;
    SecVersion->CodeBuildNo =  MbpHob->MeBiosPayload.FwVersionName.BuildVersion;
    SecVersion->CodeHotFix  =  MbpHob->MeBiosPayload.FwVersionName.HotfixVersion;

  }
  return EFI_SUCCESS;
}

/**
Get Sec Capabilities of CSE.
@param[in] SecCapability Pointer to Sec Caps.
@retval EFI_SUCCESS Success get all FW hash value
@retval EFI_ERROR Unable to get hash value

**/
EFI_STATUS
GetSecCapability(
    UINT32    *SecCapability
  )
{
  EFI_STATUS   Status;
  MEFWCAPS_SKU MsgGenGetFwCapsSku;
  ME_BIOS_PAYLOAD_HOB *MbpHob;

  if (SecCapability == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  MbpHob = NULL;
  //
  // Get Mbp Data HOB
  //
  MbpHob = GetFirstGuidHob(&gMeBiosPayloadHobGuid);
  if ((MbpHob != NULL) && (MbpHob->MeBiosPayload.FwCapsSku.Available)) {

    *SecCapability = MbpHob->MeBiosPayload.FwCapsSku.FwCapabilities.Data;
  }else {
    DEBUG((DEBUG_INFO, "HeciGetMeFwInfo: No MBP Data Protocol available calling Heci API\n"));
    Status = HeciGetFwCapsSkuMsg(&MsgGenGetFwCapsSku);
    if (EFI_ERROR(Status)) {
      return Status;
    }
    *SecCapability = MsgGenGetFwCapsSku.Data;
  }
  return EFI_SUCCESS;
}



/**

  Install Platform Service Discovery Table.
  @param[in] NONE.
 *@retval EFI_SUCCESS at successfult Installion of PSD ACPI
 *        table.
  @retval EFI_ERROR otherwise.

**/
EFI_STATUS
EFIAPI
InstallAcpiPsdTable(
  VOID
  )
{

  ACPI_PSD_TABLE                  *mPsdt;
  UINT32                          MsrValue;
  EFI_STATUS                      Status;
  UINT8                           SecureBoot;
  UINTN                           VarSize;
  EFI_ACPI_TABLE_PROTOCOL         *AcpiTable;
  UINTN                           AcpiTableKey;

  Status = gBS->LocateProtocol (&gEfiAcpiTableProtocolGuid, NULL, &AcpiTable);
  if (EFI_ERROR(Status)) {
    return Status;
  }

  mPsdt = AllocateZeroPool(sizeof(ACPI_PSD_TABLE));
  if (mPsdt == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  // Populate Platfrom security capabilities in table structure
  mPsdt->Header.Signature = EFI_ACPI_PSD_SIGNATURE;
  mPsdt->Header.Length    = sizeof(ACPI_PSD_TABLE);
  mPsdt->Header.Revision  = EFI_ACPI_PSD_TABLE_REVISION;
  mPsdt->Header.Checksum  = 0;

  CopyMem(&mPsdt->Header.OemId, PSDS_EFI_ACPI_OEM_ID, 6);
  mPsdt->Header.OemTableId              = PSDS_EFI_ACPI_OEM_TABLE_ID;
  mPsdt->Header.OemRevision             = PSDS_EFI_ACPI_OEM_REVISION;
  mPsdt->Header.CreatorId               = PSDS_EFI_ACPI_CREATOR_ID;
  mPsdt->Header.CreatorRevision         = PSDS_EFI_ACPI_CREATOR_REVISION;

  mPsdt->PsdVersion.PsdVerMajor = PSD_VERSION_MAJOR;
  mPsdt->PsdVersion.PsdVerMinor = PSD_VERSION_MINOR;
  DEBUG((EFI_D_INFO, "PsdVerMajor=%x\n", mPsdt->PsdVersion.PsdVerMajor));
  DEBUG((EFI_D_INFO, "PsdVerMinor=%x\n", mPsdt->PsdVersion.PsdVerMinor));

  //Eom State,
  Status = GetEomState(&mPsdt->EomState);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, " GetEomState failed =%x\n",Status));
  }

  //Sec Capabilities,
  Status = GetSecCapability(&(mPsdt->CsmeSecCapabilities));
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, " GetSecCapability failed =%x\n",Status));
  }
  DEBUG((EFI_D_INFO, "CsmeSecCapabilities=%x\n", mPsdt->CsmeSecCapabilities));
//FW version,
  Status = GetSecFwVersion(&(mPsdt->FwVer));
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, " GetSecCFwVersion failed =%x\n",Status));
  }

  DEBUG((EFI_D_INFO,"CodeMajor=%x\n CodeMinor=%x\n CodeHotFix=%x\n\
        CodeBuildNo=%x \n", mPsdt->FwVer.CodeMajor, mPsdt->FwVer.CodeMinor,\
        mPsdt->FwVer.CodeHotFix, mPsdt->FwVer.CodeBuildNo));

  CopyMem(&mPsdt->FwVendor, EFI_ACPI_PSD_FW_VENDOR, EFI_ACPI_PSD_FW_VENDOR_SIZE);

  // Get Secure Boot Info
  VarSize = sizeof(UINT8);
  Status = gRT->GetVariable(
      EFI_SECURE_BOOT_MODE_NAME,
      &gEfiGlobalVariableGuid,
      NULL,
      &VarSize,
      &SecureBoot
      );

  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_INFO, "  Get Secure Boot Info failed =%x\n",Status));
  }

  ///
  /// Read Boot Guard S-ACM Info MSR
  ///
  ///
  ///00 - Secure boot is Disabled; 01 - Verified boot is enabled.
  ///11 - Secure boot (verified + PcdVerifiedBootEnabled) enabled.
  MsrValue = (UINT32)AsmReadMsr64(MSR_BOOT_GUARD_SACM_INFO);
  mPsdt->MeasuredBoot = (UINT8)(MsrValue & B_BOOT_GUARD_SACM_INFO_MEASURED_BOOT) >> 5;
  mPsdt->SecureBoot = (UINT8)(((MsrValue & B_BOOT_GUARD_SACM_INFO_VERIFIED_BOOT) >> 5)  | SecureBoot);

  ///0 - No HWRoT; 1 - ROM based RoT; 2 - TXE; 3 - CSE; 4 - ACM; 5 - TXT
  mPsdt->HwrotType  = PSD_HROT_ACM;

  DEBUG((EFI_D_INFO, "SecureBootEnabled=%x\n", mPsdt->SecureBoot));
  DEBUG((EFI_D_INFO, "MeasuredBootEnabled=%x\n", mPsdt->MeasuredBoot));
  DEBUG((EFI_D_INFO, "HwrotType=%x\n", mPsdt->HwrotType));

  AcpiTableKey = 0;

  Status = AcpiTable->InstallAcpiTable(AcpiTable, mPsdt, mPsdt->Header.Length, &AcpiTableKey);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_ERROR, " InstallAcpiTable failed =%x, %x\n",Status, AcpiTableKey));
     FreePool(mPsdt);
     return Status;
  }

  FreePool(mPsdt);
  return  EFI_SUCCESS;
}

/*++
  Entry point to install Hardware Root of Trust (PSDS) ACPI Table

  @param[in] ImageHandle     Handle for this drivers loaded image protocol.
  @param[in] SystemTable     EFI system table.

  @return EFI_SUCCESS           Installed PSDS ACPI table successfully.

--*/

EFI_STATUS
AcpiPsdsDxeEntryPoint (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS                      Status;

  Status = InstallAcpiPsdTable();
  return Status;

}


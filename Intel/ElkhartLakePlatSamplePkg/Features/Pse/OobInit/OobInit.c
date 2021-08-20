/** @file
  Pse Out of Band Initialization

@copyright
  INTEL CONFIDENTIAL
  Copyright (c) 2019 - 2020 Intel Corporation.

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
#include <Uefi/UefiBaseType.h>
#include <Register/PseRegs.h>

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/HobLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/DxeServicesLib.h>
#include <Register/MeRegs.h>
#include <Protocol/HeciFlowProtocol.h>
#include <Protocol/FirmwareVolume2.h>
#include <PseOob.h>

#include <Library/PseInfoLib.h>
#include <Library/IoLib.h>
#include <Register/PchRegs.h>
#include <Library/PciSegmentLib.h>
#include <SetupVariable.h>


/**
  Dump OOB Package info from subregion.

  This function dumps OOB package info to send from BIOS for debug purpose.

  @param  Buffer            The OOB buffer to dump.

**/
VOID
DumpSubregionOob (
  IN OOB_DATA      *OobData
  )
{
  if (OobData == NULL) {
    DEBUG ((DEBUG_INFO, "Get null from OOB Subregion\n"));
    return;
  }
  DEBUG ((DEBUG_INFO, "\n\nProvState: %x\n", OobData->ProvState));
  DEBUG ((DEBUG_INFO, "\n\nDeviceIdSize: %x\n", OobData->DeviceIdSize));
  DEBUG ((DEBUG_INFO, "DeviceId: \n"));
  for (UINT32 Count = 0; Count < 25; Count++) {
    DEBUG ((DEBUG_INFO, "%c", OobData->DeviceId[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n\nTokenIdSize: %x\n", OobData->TokenIdSize));
  DEBUG ((DEBUG_INFO, "TokenId: \n"));
  for (UINT32 Count = 0; Count < 25; Count++) {
    DEBUG ((DEBUG_INFO, "%c", OobData->TokenId[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n\nCloudTypeSize: %x\n", OobData->CloudTypeSize));
  DEBUG ((DEBUG_INFO, "CloudType: \n"));
  for (UINT32 Count = 0; Count < 16; Count++) {
    DEBUG ((DEBUG_INFO, "%c", OobData->CloudType[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n\nCloudHostUrlSize: %x\n", OobData->CloudHostUrlSize));
  DEBUG ((DEBUG_INFO, "CloudHostUrl: \n"));
  for (UINT32 Count = 0; Count < 25; Count++) {
    DEBUG ((DEBUG_INFO, "%c", OobData->CloudHostUrl[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n\nCloudHostPort: %x\n", OobData->CloudHostPort));
  DEBUG ((DEBUG_INFO, "ProxyHostUrlSize: %x\n", OobData->ProxyHostUrlSize));
  DEBUG ((DEBUG_INFO, "ProxyHostUrl: \n"));
  for (UINT32 Count = 0; Count < 25; Count++) {
    DEBUG ((DEBUG_INFO, "%c", OobData->ProxyHostUrl[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n\nProxyHostPort: %x\n", OobData->ProxyHostPort));
  DEBUG ((DEBUG_INFO, "BiosPasswordSize: %x\n", OobData->BiosPasswordSize));
  DEBUG ((DEBUG_INFO, "BiosPassword: \n"));
  for (UINT32 Count = 0; Count < 25; Count++) {
    DEBUG ((DEBUG_INFO, "%c", OobData->BiosPassword[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));
}


/**
  Dump OOB Package info.

  This function dumps OOB package info to send from BIOS for debug purpose.

  @param  Buffer            The OOB buffer to dump.

**/
VOID
DumpOobPackageInfo (
  IN HECI_BIOS_PSE_MSG_PACKAGE      *OobPkg
  )
{
  if (OobPkg == NULL) {
    return;
  }
  DEBUG ((DEBUG_INFO, "OobPkg.OobHeader.Command: %x\n", OobPkg->OobHeader.Command));
  DEBUG ((DEBUG_INFO, "OobPkg.OobHeader.MessageComplete: %x\n", OobPkg->OobHeader.MessageComplete));
  DEBUG ((DEBUG_INFO, "OobPkg.OobHeader.Status: %x\n", OobPkg->OobHeader.Status));
  DEBUG ((DEBUG_INFO, "OobPkg.OobHeader.ProtocolVersioning: %x\n", OobPkg->OobHeader.ProtocolVersioning));
  DEBUG ((DEBUG_INFO, "OobPkg.OobHeader.Source: %x\n", OobPkg->OobHeader.Source));
  DEBUG ((DEBUG_INFO, "OobPkg.OobHeader.Length: %x\n", OobPkg->OobHeader.Length));
  DEBUG ((DEBUG_INFO, "OOB data length: %x\n", OobPkg->OobMsg.Length));
  DEBUG ((DEBUG_INFO, "OOB length: %x\n", sizeof(OobPkg)));

  if (OobPkg->OobMsg.Length > OOB_HEADER_SIZE) {
    for (UINT32 Count = 0; Count < OobPkg->OobMsg.Length - 4; Count++) {
      DEBUG ((DEBUG_INFO, "0x%x ", OobPkg->Data[Count]));
    }
  }
}

/**
  Get PSE Version through SMHI client.
**/
EFI_STATUS
PseGetVersion (
  VOID
  )
{
  HECI_FLOW_PROTOCOL      *HeciFlow;
  SMHI_GET_VERSION_RES    SmhiMessage;
  UINT32                  Length;
  PSE_VERSION             PseVersion;
  EFI_STATUS              Status = EFI_SUCCESS;

  DEBUG((DEBUG_INFO, "Getting PSE Version\n"));

  SmhiMessage.Header.Command          = PSE_GET_VERSION;
  SmhiMessage.Header.IsResponse       = 0;
  SmhiMessage.Header.HasNext          = 0;
  SmhiMessage.Header.Reserved         = 0;
  SmhiMessage.Header.Status           = 0;
  Length                              = sizeof(SMHI_GET_VERSION_RES);

  Status = gBS->LocateProtocol (&gHeciFlowProtocolGuid, NULL, (VOID **) &HeciFlow);
  if (!EFI_ERROR (Status)) {
    Status = HeciFlow->SendAndReceive (PSE_HECI, &SmhiMessage, sizeof(UINT32), &Length , &gPseSmhiClientInterfaceGuid);
    if (!EFI_ERROR (Status)) {
      CopyMem (&PseVersion, &SmhiMessage.Version, sizeof(PSE_VERSION));
      DEBUG ((DEBUG_INFO, "FW Version: %d.%d.%d.%d.\n", PseVersion.Major, PseVersion.Minor, PseVersion.Hotfix, PseVersion.Build));
    } else {
      DEBUG((DEBUG_INFO, "Error on fetching PSE FW version. Status : %x\n", Status));
    }
  }
  return Status;
}

/**
  @param[out] OobRegion

  @retval     EFI_SUCCESS
  @retval     EFI_NOT_FOUND
**/
EFI_STATUS
EFIAPI
GetRootCAData (
  OUT OOB_ROOTCA     *OobRootCA
  )
{
  VOID                  *Address;
  UINTN                 Size;

  Address   = NULL;
  Size      = 0;

  if (OobRootCA != NULL) {
    Address = GetFirstGuidHob (&gOobRootCASectionGuid);
    if (Address != NULL) {
      OobRootCA->Size   = *((UINT32*)GET_GUID_HOB_DATA (Address));
      if (OobRootCA->Size) {
        Address = GetNextGuidHob (&gOobRootCASectionGuid, (UINT8*)Address+GET_HOB_LENGTH (Address));
        OobRootCA->Buffer = GET_GUID_HOB_DATA (Address);
        DEBUG ((EFI_D_INFO, "DXE get OOB RootCA from HOB successfully\n"));
        return EFI_SUCCESS;
      }
    }
  }

  return EFI_NOT_FOUND;
}

/*
  First time OOB Provisioning flow

  Step 1: Sending data as below
  (currently all hardcoded)

  From PSE Manifest
  1) ROOTCA
  2) Owner Public Key
  3) HKDR_32B_TPM_SALT

  From BIOS setup menu
  4) TOKEN_ID
  5) USERNAME
  6A) Config Data - CLOUD URL
  6B) Config Data - CLOUD PORT
  6C) Config Data - PROXY URL
  6D) Config Data - PROXY PORT

  Step 2: Send PROV_INIT_ACK
*/

EFI_STATUS
FirstBootProvisioning (
  IN OOB_DATA      *OobData
  )
{
  HECI_FLOW_PROTOCOL          *HeciFlow;
  HECI_BIOS_PSE_MSG_PACKAGE   OobPkg;
  UINT32                      Length;
  UINT32                      ReceivedFragmentLength = 0;
  UINT32                      TotalReceivedLength = 0;
  UINT32                      Count2 = 0;
  PCH_SETUP                   PchSetup;
  UINTN                       VariableSize;
  EFI_STATUS                  Status = EFI_SUCCESS;
  OOB_VARIABLE                OobVariable;
  UINTN                       OobVariableSize = sizeof (OOB_VARIABLE);
  OOB_ROOTCA                  OobRootCA;

  DEBUG((DEBUG_INFO, "Running First Boot Provisioning Flow\n"));

  Status = gBS->LocateProtocol (&gHeciFlowProtocolGuid, NULL, (VOID **) &HeciFlow);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get Root CA data and its length from FFS
  //
  GetRootCAData(&OobRootCA);
  DEBUG ((DEBUG_INFO, "RootCA buffer Size : %d Buffer: 0x%x\n", OobRootCA.Size, OobRootCA.Buffer));
  DEBUG ((DEBUG_INFO, "RootCA: \n"));
  for (UINTN Count = 0; Count < OobRootCA.Size; Count++) {
    DEBUG ((DEBUG_INFO, "%c", ((UINT8*)OobRootCA.Buffer)[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  //
  // ROOTCA
  //
  if (OobRootCA.Size) {
    DEBUG((DEBUG_INFO, "\nSending RootCA\n"));
    OobPkg.OobHeader.Command = BIOS_OOB_PROV_INIT_OOB;
    OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
    OobPkg.OobHeader.Status = 0;
    OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
    OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

    OobPkg.OobMsg.Type = BIOS_OOB_TYPE_ROOTCA;
    OobPkg.OobMsg.Length = 4 + OobRootCA.Size;
    if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
      CopyMem(OobPkg.Data, OobRootCA.Buffer, OobPkg.OobMsg.Length);
    } else {
      DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
      ASSERT(FALSE);
    }

    OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
    Length    = OobPkg.OobHeader.Length;
    DumpOobPackageInfo(&OobPkg);
    Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
    if (EFI_ERROR(Status)) {
      DEBUG((DEBUG_INFO, "Error on sending ROOTCA. Status : %x\n", Status));
      return Status;
    }
  }

  //
  // BIOS_OOB_TYPE_256_OWNER_PUBLIC_KEY
  //
  DEBUG((DEBUG_INFO, "\n\nSending BIOS_OOB_TYPE_256_OWNER_PUBLIC_KEY\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_PROV_INIT_OOB;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_256_OWNER_PUBLIC_KEY;
  OobPkg.OobMsg.Length = OOB_HEADER_SIZE + sizeof(PUBLIC_KEY)/sizeof(CHAR8);
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, (UINT8 *)PUBLIC_KEY, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_INFO, "Error on sending BIOS_OOB_TYPE_256_OWNER_PUBLIC_KEY. Status : %x\n", Status));
    return Status;
  }

  //
  // BIOS_OOB_TYPE_HKDF_32B_TPM_SALT
  //
  DEBUG((DEBUG_INFO, "\n\nSending BIOS_OOB_TYPE_HKDF_32B_TPM_SALT\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_PROV_INIT_OOB;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_HKDF_32B_TPM_SALT;
  OobPkg.OobMsg.Length = 4 + sizeof(TPM_SALT)/sizeof(CHAR8);
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, (UINT8 *)TPM_SALT, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_INFO, "Error on sending BIOS_OOB_TYPE_HKDF_32B_TPM_SALT. Status : %x\n", Status));
    return Status;
  }

  //
  // BIOS_OOB_TYPE_UNENCRYPTED_TOKEN_ID
  //
  DEBUG((DEBUG_INFO, "\n\nSending BIOS_OOB_TYPE_UNENCRYPTED_TOKEN_ID\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_PROV_INIT_OOB;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_UNENCRYPTED_TOKEN_ID;
  OobPkg.OobMsg.Length = 4 + OobData->TokenIdSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, (UINT8 *)OobData->TokenId, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_INFO, "Error on sending BIOS_OOB_TYPE_UNENCRYPTED_TOKEN_ID. Status : %x\n", Status));
    return Status;
  }

  //
  // BIOS_OOB_TYPE_UNENCRYPTED_DEVICE_ID
  //
  DEBUG((DEBUG_INFO, "\n\nSending BIOS_OOB_TYPE_UNENCRYPTED_DEVICE_ID\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_PROV_INIT_OOB;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_UNENCRYPTED_DEVICE_ID;
  OobPkg.OobMsg.Length = 4 + OobData->DeviceIdSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, (UINT8 *)OobData->DeviceId, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_INFO, "Error on sending BIOS_OOB_TYPE_UNENCRYPTED_DEVICE_ID. Status : %x\n", Status));
    return Status;
  }

  //
  // Sending BIOS_OOB_TYPE_CLD_ADAPTER
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_CLD_ADAPTER\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_CLD_ADAPTER;
  OobPkg.OobMsg.Length = 4 + OobData->CloudTypeSize;

  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, OobData->CloudType, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // BIOS_OOB_TYPE_CLOUD_URL
  //
  DEBUG((DEBUG_INFO, "\n\nSending BIOS_OOB_TYPE_CLOUD_URL\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_PROV_INIT_OOB;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_CLOUD_URL;
  OobPkg.OobMsg.Length = 4 + OobData->CloudHostUrlSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, (UINT8 *)OobData->CloudHostUrl, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_INFO, "Error on sending BIOS_OOB_TYPE_CLOUD_URL. Status : %x\n", Status));
    return Status;
  }

  //
  // Sending BIOS_OOB_TYPE_CLOUD_PORT
  //
  DEBUG((DEBUG_INFO, "\n\nSending BIOS_OOB_TYPE_CLOUD_PORT\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_PROV_INIT_OOB;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_CLOUD_PORT;
  OobPkg.OobMsg.Length = 4 + sizeof(OobData->CloudHostPort)/sizeof(UINT8);
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, &OobData->CloudHostPort, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_INFO, "Error on sending BIOS_OOB_TYPE_CLOUD_PORT. Status : %x\n", Status));
    return Status;
  }

  //
  // BIOS_OOB_TYPE_PROXY_URL
  //
  DEBUG((DEBUG_INFO, "\n\nSending BIOS_OOB_TYPE_PROXY_URL\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_PROV_INIT_OOB;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_PROXY_URL;
  OobPkg.OobMsg.Length = 4 + OobData->ProxyHostUrlSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, (UINT8 *)OobData->ProxyHostUrl, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_INFO, "Error on sending BIOS_OOB_TYPE_PROXY_URL. Status : %x\n", Status));
    return Status;
  }

  //
  // BIOS_OOB_TYPE_PROXY_PORT
  //
  DEBUG((DEBUG_INFO, "\n\nSending BIOS_OOB_TYPE_PROXY_PORT\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_PROV_INIT_OOB;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_COM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_PROXY_PORT;
  OobPkg.OobMsg.Length = 4 + sizeof(OobData->ProxyHostPort)/sizeof(UINT8);
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, &OobData->ProxyHostPort, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = MAX_HECI_PACKAGE;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->SendAndReceive (PSE_HECI, &OobPkg, OobPkg.OobHeader.Length, &Length , &gPseOobHeciClientInterfaceGuid);

  DEBUG((DEBUG_INFO, "\n\nReceiving data from PSE\n"));
  // Process received input after setting BIOS_OOB_MSG_COM
  if (!EFI_ERROR (Status)) {
    DEBUG_CODE_BEGIN ();
      DEBUG ((DEBUG_INFO, "[TT] Response from OOB:\nOobPkg.OobMsg.Type: %x\nFull length: %x\n", OobPkg.OobMsg.Type, Length));
      DEBUG ((DEBUG_INFO, "OOB first header data length: %x\nFull data:\n", OobPkg.OobMsg.Length));
      for (UINT32 Count = 0; Count < Length - (OOB_HEADER_SIZE + HECI_HEADER_SIZE); Count++){
        DEBUG ((DEBUG_INFO, "0x%02x ", OobPkg.Data[Count]));
        if (Count % 0x10 == 0) {
          DEBUG ((DEBUG_INFO, "\n"));
        }
      }
    DEBUG_CODE_END ();
      DEBUG ((DEBUG_INFO, "\nParsed Data: \n"));
      // First chunk excludes header length, thus short of 4 bytes.
      // This is parsed separately and to be checked whether it is only single package or multiple package.
      ReceivedFragmentLength = OobPkg.OobMsg.Length - OOB_HEADER_SIZE;
      for (Count2 = 0; Count2 < ReceivedFragmentLength; Count2++){
        DEBUG ((DEBUG_INFO, "0x%02x ", OobPkg.Data[Count2 + TotalReceivedLength]));
      }
      TotalReceivedLength = ReceivedFragmentLength;
      DEBUG ((DEBUG_INFO, "\nReceived Fragment Length : 0x%x, Total Received Length : 0x%x\n", ReceivedFragmentLength, TotalReceivedLength));

      // If this is multiple package, the data need to be dynamically parsed.
      while (TotalReceivedLength < Length - (OOB_HEADER_SIZE + HECI_HEADER_SIZE)) {
        DEBUG ((DEBUG_INFO, "\nmultiple package case. Next package: \n"));
        DEBUG ((DEBUG_INFO, "Header 0 : %x (supposedly type) 0x%x\n", TotalReceivedLength + 0, OobPkg.Data[TotalReceivedLength]));
        DEBUG ((DEBUG_INFO, "Header 1 : %x (supposedly size) 0x%x\n", TotalReceivedLength + 1, OobPkg.Data[TotalReceivedLength + 1]));

        ReceivedFragmentLength = OobPkg.Data[TotalReceivedLength + 1];
        if (ReceivedFragmentLength <= OOB_HEADER_SIZE) {
          break;
        }

        Status = gRT->GetVariable (
                        OOB_VARIABLE_NAME,
                        &gOobVariablesGuid,
                        NULL,
                        &OobVariableSize,
                        &OobVariable
                        );
        // Determine the type of OOB variable to receive
        switch (OobPkg.Data[TotalReceivedLength]){
          case BIOS_OOB_TYPE_HKDF_32B_PSE_SALT:
            DEBUG ((DEBUG_INFO, "BIOS_OOB_TYPE_HKDF_32B_PSE_SALT\n"));
            CopyMem (OobVariable.PseSalt, &OobPkg.Data[4 + TotalReceivedLength], ReceivedFragmentLength-4);
            OobVariable.PseSaltSize = ReceivedFragmentLength-4;
            break;
          case BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID:
            DEBUG ((DEBUG_INFO, "BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID\n"));
            CopyMem (OobVariable.EncryptedTokenId, &OobPkg.Data[4 + TotalReceivedLength], ReceivedFragmentLength-4);
            OobVariable.EncryptedTokenIdSize = ReceivedFragmentLength-4;
            break;
          case BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_TAG:
            DEBUG ((DEBUG_INFO, "BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_TAG\n"));
            CopyMem (OobVariable.EncryptedTokenIdTag, &OobPkg.Data[4 + TotalReceivedLength], ReceivedFragmentLength-4);
            OobVariable.EncryptedTokenIdTagSize = ReceivedFragmentLength-4;
            break;
          case BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_IV:
            DEBUG ((DEBUG_INFO, "BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_IV\n"));
            CopyMem (OobVariable.EncryptedTokenIdIv, &OobPkg.Data[4 + TotalReceivedLength], ReceivedFragmentLength-4);
            OobVariable.EncryptedTokenIdIvSize = ReceivedFragmentLength-4;
            break;
          case BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID:
            DEBUG ((DEBUG_INFO, "BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID\n"));
            CopyMem (OobVariable.EncryptedDeviceId, &OobPkg.Data[4 + TotalReceivedLength], ReceivedFragmentLength-4);
            OobVariable.EncryptedDeviceIdSize = ReceivedFragmentLength-4;
            break;
          case BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_TAG:
            DEBUG ((DEBUG_INFO, "BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_TAG\n"));
            CopyMem (OobVariable.EncryptedDeviceIdTag, &OobPkg.Data[4 + TotalReceivedLength], ReceivedFragmentLength-4);
            OobVariable.EncryptedDeviceIdTagSize = ReceivedFragmentLength-4;
            break;
          case BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_IV:
            DEBUG ((DEBUG_INFO, "BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_IV\n"));
            CopyMem (OobVariable.EncryptedDeviceIdIv, &OobPkg.Data[4 + TotalReceivedLength], ReceivedFragmentLength-4);
            OobVariable.EncryptedDeviceIdIvSize = ReceivedFragmentLength-4;
            break;
          default:
            DEBUG ((DEBUG_INFO, "Unknown data\n"));
            break;
        }
    DEBUG_CODE_BEGIN ();
        DEBUG ((DEBUG_INFO, "Raw Data: \n"));
        for (Count2 = 4; Count2 < ReceivedFragmentLength; Count2++){
          DEBUG ((DEBUG_INFO, "0x%02x ", OobPkg.Data[Count2 + TotalReceivedLength]));
        }
    DEBUG_CODE_END ();

        Status = gRT->SetVariable (
                        OOB_VARIABLE_NAME,
                        &gOobVariablesGuid,
                        EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS,
                        OobVariableSize,
                        &OobVariable
                        );
        if (EFI_ERROR (Status)) {
          DEBUG ((DEBUG_INFO, "OOB variable set failed (%r)\n", Status));
        }

        DEBUG ((DEBUG_INFO, "Next Fragment Length : 0x%x, Total Received Length : 0x%x\n", ReceivedFragmentLength, TotalReceivedLength));
        TotalReceivedLength += ReceivedFragmentLength;
        if (TotalReceivedLength > Length) {
          DEBUG ((DEBUG_INFO, "breaking..\n"));
          break;
        }
      }
  } else {
    DEBUG((DEBUG_INFO, "Error on fetching OOB response. Status : %x\n", Status));
    return Status;
  }

  //
  // Step 2: Send PROV_INIT_ACK without any data
  //
  OobPkg.OobHeader.Command = BIOS_OOB_PROV_INIT_ACK;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_COM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_PROV_INIT_ACK;
  OobPkg.OobMsg.Length = OOB_HEADER_SIZE;
  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = MAX_HECI_PACKAGE;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->SendAndReceive (PSE_HECI, &OobPkg, OobPkg.OobHeader.Length, &Length , &gPseOobHeciClientInterfaceGuid);

  if (!EFI_ERROR (Status)) {
    DEBUG_CODE_BEGIN ();
      DEBUG ((DEBUG_INFO, "Response from OOB:\nOobPkg.OobMsg.Type: %x\nOOB data length: %x\nData:\n", OobPkg.OobMsg.Type, OobPkg.OobMsg.Length));
      for (UINT32 Count = 0; Count < OobPkg.OobMsg.Length - OOB_HEADER_SIZE; Count++){
        DEBUG ((DEBUG_INFO, "0x%x ", OobPkg.Data[Count]));
      }
    DEBUG_CODE_END ();
  } else {
    DEBUG((DEBUG_INFO, "Error on fetching OOB response. Status : %x\n", Status));
    return Status;
  }

  // After done everything in this flow, overwrite the NV variable that sets the first
  // time boot so that this flow will not run again, issue reset.
  if (EFI_ERROR (Status)) {
    return Status;
  } else {
    // Overwrite NV variable for first time boot
    VariableSize = sizeof (PCH_SETUP);
    Status = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &PchSetup
                  );
    PchSetup.PchPseOobIsFirstBootProvDone = TRUE;
    Status = gRT->SetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS,
                  sizeof (PCH_SETUP),
                  &PchSetup
                  );
    // Readback to ensure Variables are set correctly.
    Status = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &PchSetup
                  );
    if (Status == EFI_SUCCESS) {
      DEBUG((DEBUG_INFO, "New PchPseOobIsFirstBootProvDone: %x\n", PchSetup.PchPseOobIsFirstBootProvDone));
      if (PchSetup.PchPseOobIsFirstBootProvDone == FALSE){
        DEBUG((DEBUG_INFO, "Error, it should be FALSE, please investigate.\n"));
        ASSERT(FALSE);
      }
      // Issue reset
      gRT->ResetSystem (EfiResetCold, EFI_SUCCESS, 0, NULL);
    } else {
      DEBUG((DEBUG_INFO, "Getting and setting Setup Variables failed with status: %x\n", Status));
      return Status;
    }
  }
  return Status;
}

/*
  Normal Boot flow

  Sending data as below

  Step 1:
  From Manifest
  1) ROOTCA
  2) Owner Public Key
  3) HKDR_32B_TPM_SALT

  Step 2:
  From TPM NV Indices (From response in first time provisioning flow)
  1) BIOS_OOB_TYPE_HKDF_32B_PSE_SALT
  2) BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID
  3) BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_TAG
  4) BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_IV
  5) BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID
  6) BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_TAG
  7) BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_IV
  8) BIOS_OOB_TYPE_CLOUD_URL
  9) BIOS_OOB_TYPE_CLOUD_PORT
  10) BIOS_OOB_TYPE_PROXY_URL
  11) BIOS_OOB_TYPE_PROXY_PORT
  12) BIOS_OOB_TYPE_PROVISIONING_STATE
*/
EFI_STATUS
NormalBoot (
  IN OOB_DATA      *OobData
  )
{
  HECI_FLOW_PROTOCOL          *HeciFlow;
  HECI_BIOS_PSE_MSG_PACKAGE   OobPkg;
  UINT32                      Length;
  EFI_STATUS                  Status = EFI_SUCCESS;
  OOB_VARIABLE                OobVariable;
  UINTN                       OobVariableSize = 0;
  OOB_ROOTCA                  OobRootCA;

  DEBUG((DEBUG_INFO, "Running Normal Boot Flow\n"));

  Status = gBS->LocateProtocol (&gHeciFlowProtocolGuid, NULL, (VOID **) &HeciFlow);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get Root CA data and its length from FFS
  //
  GetRootCAData(&OobRootCA);
  DEBUG ((DEBUG_INFO, "RootCA buffer Size : %d Buffer: 0x%x\n", OobRootCA.Size, OobRootCA.Buffer));
  DEBUG ((DEBUG_INFO, "RootCA: \n"));
  for (UINTN Count = 0; Count < OobRootCA.Size; Count++) {
    DEBUG ((DEBUG_INFO, "%c", ((UINT8*)OobRootCA.Buffer)[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  //
  // Sending ROOTCA
  //
  if (OobRootCA.Size) {
    DEBUG((DEBUG_INFO, "\nSending RootCA\n"));
    OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB;
    OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
    OobPkg.OobHeader.Status = 0;
    OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
    OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

    OobPkg.OobMsg.Type = BIOS_OOB_TYPE_ROOTCA;
    OobPkg.OobMsg.Length = 4 + OobRootCA.Size;
    if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
      CopyMem(OobPkg.Data, OobRootCA.Buffer, OobPkg.OobMsg.Length);
    } else {
      DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
      ASSERT(FALSE);
    }

    OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
    Length    = OobPkg.OobHeader.Length;
    DumpOobPackageInfo(&OobPkg);
    Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
    if (EFI_ERROR(Status)) {
      DEBUG((DEBUG_INFO, "Error on sending ROOTCA. Status : %x\n", Status));
      return Status;
    }
  }

  //
  // Sending BIOS_OOB_TYPE_HKDF_32B_TPM_SALT
  //
  DEBUG((DEBUG_INFO, "\n\nSending BIOS_OOB_TYPE_HKDF_32B_TPM_SALT\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_HKDF_32B_TPM_SALT;
  OobPkg.OobMsg.Length = 4 + sizeof(TPM_SALT)/sizeof(CHAR8);
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, TPM_SALT, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_INFO, "Error on sending BIOS_OOB_TYPE_HKDF_32B_TPM_SALT. Status : %x\n", Status));
    return Status;
  }

  //
  // Sending BIOS_OOB_TYPE_256_OWNER_PUBLIC_KEY
  // Receive TPM NV Password
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_256_OWNER_PUBLIC_KEY\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_COM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_256_OWNER_PUBLIC_KEY;
  OobPkg.OobMsg.Length = OOB_HEADER_SIZE + sizeof(PUBLIC_KEY)/sizeof(CHAR8);
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, PUBLIC_KEY, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = MAX_HECI_PACKAGE;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->SendAndReceive (PSE_HECI, &OobPkg, OobPkg.OobHeader.Length, &Length , &gPseOobHeciClientInterfaceGuid);

  if (!EFI_ERROR (Status)) {
    DEBUG_CODE_BEGIN ();
      DEBUG ((DEBUG_INFO, "Response should represents TPM_NV_PASSWORD.\nOOB data length: %x\n", OobPkg.OobMsg.Length));
      for (UINT32 Count = 0; Count < OobPkg.OobMsg.Length - OOB_HEADER_SIZE; Count++){
        DEBUG ((DEBUG_INFO, "0x%x ", OobPkg.Data[Count]));
      }
    DEBUG_CODE_END ();
  } else {
    DEBUG((DEBUG_INFO, "Error on fetching OOB response. Status : %x\n", Status));
    return Status;
  }

  OobVariableSize = sizeof(OOB_VARIABLE);
  //
  // Get Variable to load OOB data
  //
  Status = gRT->GetVariable (
                  OOB_VARIABLE_NAME,
                  &gOobVariablesGuid,
                  NULL,
                  &OobVariableSize,
                  &OobVariable
                  );
  if (Status == EFI_NOT_FOUND) {
    DEBUG((DEBUG_INFO, "Error! Could not find OOB data during provisioning flow\n"));
  }

  DEBUG_CODE_BEGIN ();
  if (!EFI_ERROR(Status)) {
    //dump out everything to make sure contents are good to go.
    DEBUG((DEBUG_INFO, "\n\nOOB Content Summary:\nPseSalt\n"));
    for (UINT32 Count = 0; Count < OobVariable.PseSaltSize; Count++) {
      DEBUG((DEBUG_INFO, "0x%02x ", OobVariable.PseSalt[Count]));
    }
    DEBUG((DEBUG_INFO, "\nSize: 0x%02x \n", OobVariable.PseSaltSize));
    for (UINT32 Count = 0; Count < OobVariable.EncryptedTokenIdSize; Count++) {
      DEBUG((DEBUG_INFO, "0x%02x ", OobVariable.EncryptedTokenId[Count]));
    }
    DEBUG((DEBUG_INFO, "\nSize: 0x%02x ", OobVariable.EncryptedTokenIdSize));
    DEBUG((DEBUG_INFO, "EncryptedTokenIdTag\n"));
    for (UINT32 Count = 0; Count < OobVariable.EncryptedTokenIdTagSize; Count++) {
      DEBUG((DEBUG_INFO, "0x%02x ", OobVariable.EncryptedTokenIdTag[Count]));
    }
    DEBUG((DEBUG_INFO, "\nSize: 0x%02x ", OobVariable.EncryptedTokenIdTagSize));
    DEBUG((DEBUG_INFO, "EncryptedTokenIdIv\n"));
    for (UINT32 Count = 0; Count < OobVariable.EncryptedTokenIdIvSize; Count++) {
      DEBUG((DEBUG_INFO, "0x%02x ", OobVariable.EncryptedTokenIdIv[Count]));
    }
    DEBUG((DEBUG_INFO, "\nSize: 0x%02x ", OobVariable.EncryptedTokenIdIvSize));
    DEBUG((DEBUG_INFO, "EncryptedDeviceId\n"));
    for (UINT32 Count = 0; Count < OobVariable.EncryptedDeviceIdSize; Count++) {
      DEBUG((DEBUG_INFO, "0x%02x ", OobVariable.EncryptedDeviceId[Count]));
    }
    DEBUG((DEBUG_INFO, "\nSize: 0x%02x ", OobVariable.EncryptedDeviceIdSize));
    DEBUG((DEBUG_INFO, "EncryptedDeviceIdTag\n"));
    for (UINT32 Count = 0; Count < OobVariable.EncryptedDeviceIdTagSize; Count++) {
      DEBUG((DEBUG_INFO, "0x%02x ", OobVariable.EncryptedDeviceIdTag[Count]));
    }
    DEBUG((DEBUG_INFO, "\nSize: 0x%02x ", OobVariable.EncryptedDeviceIdTagSize));
    DEBUG((DEBUG_INFO, "EncryptedDeviceIdIv\n"));
    for (UINT32 Count = 0; Count < OobVariable.EncryptedDeviceIdIvSize; Count++) {
      DEBUG((DEBUG_INFO, "0x%02x ", OobVariable.EncryptedDeviceIdIv[Count]));
    }
    DEBUG((DEBUG_INFO, "Size: 0x%02x ", OobVariable.EncryptedDeviceIdIvSize));
  } else {
    DEBUG((DEBUG_INFO, "Error code: %r\n", Status));
  }
  DEBUG_CODE_END ();

  //
  // Sending BIOS_OOB_TYPE_HKDF_32B_PSE_SALT
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_HKDF_32B_PSE_SALT\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_HKDF_32B_PSE_SALT;
  OobPkg.OobMsg.Length = 4 + OobVariable.PseSaltSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, OobVariable.PseSalt, OobVariable.PseSaltSize);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);
  if (EFI_ERROR(Status)) {
    DEBUG((DEBUG_INFO, "Error on sending BIOS_OOB_TYPE_HKDF_32B_TPM_SALT. Status : %x\n", Status));
    return Status;
  }

  //
  // Sending BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID;
  OobPkg.OobMsg.Length = 4 + OobVariable.EncryptedTokenIdSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, OobVariable.EncryptedTokenId, OobVariable.EncryptedTokenIdSize);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than obPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_TAG
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_TAG\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_TAG;
  OobPkg.OobMsg.Length = 4 + OobVariable.EncryptedTokenIdTagSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, OobVariable.EncryptedTokenIdTag, OobVariable.EncryptedTokenIdTagSize);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_IV
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_IV\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_ENCRYPTED_TOKEN_ID_IV;
  OobPkg.OobMsg.Length = 4 + OobVariable.EncryptedTokenIdIvSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, OobVariable.EncryptedTokenIdIv, OobVariable.EncryptedTokenIdIvSize);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID;
  OobPkg.OobMsg.Length = 4 + OobVariable.EncryptedDeviceIdSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, OobVariable.EncryptedDeviceId, OobVariable.EncryptedDeviceIdSize);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_TAG
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_TAG\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_TAG;
  OobPkg.OobMsg.Length = 4 + OobVariable.EncryptedDeviceIdTagSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, OobVariable.EncryptedDeviceIdTag, OobVariable.EncryptedDeviceIdTagSize);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_IV
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_IV\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_ENCRYPTED_DEVICE_ID_IV;
  OobPkg.OobMsg.Length = 4 + OobVariable.EncryptedDeviceIdIvSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, OobVariable.EncryptedDeviceIdIv, OobVariable.EncryptedDeviceIdIvSize);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_CLD_ADAPTER
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_CLD_ADAPTER\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_CLD_ADAPTER;
  OobPkg.OobMsg.Length = 4 + OobData->CloudTypeSize;

  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, OobData->CloudType, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_CLOUD_URL
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_CLOUD_URL\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_CLOUD_URL;
  OobPkg.OobMsg.Length = 4 + OobData->CloudHostUrlSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, OobData->CloudHostUrl, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_CLOUD_PORT
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_CLOUD_PORT\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_CLOUD_PORT;
  OobPkg.OobMsg.Length = 4 + sizeof(OobData->CloudHostPort)/sizeof(UINT8);
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, &OobData->CloudHostPort, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_PROXY_URL
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_PROXY_URL\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_PROXY_URL;
  OobPkg.OobMsg.Length = 4 + OobData->ProxyHostUrlSize;
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, (UINT8 *)OobData->ProxyHostUrl, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_PROXY_PORT
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_PROXY_PORT\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_INCOM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_PROXY_PORT;
  OobPkg.OobMsg.Length = 4 + sizeof(OobData->ProxyHostPort)/sizeof(UINT8);
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, &OobData->ProxyHostPort, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = OobPkg.OobHeader.Length;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->Send (PSE_HECI, &OobPkg, Length, &gPseOobHeciClientInterfaceGuid);

  //
  // Sending BIOS_OOB_TYPE_PROVISIONING_STATE
  //
  DEBUG((DEBUG_INFO, "\n\n Sending BIOS_OOB_TYPE_PROVISIONING_STATE\n"));
  OobPkg.OobHeader.Command = BIOS_OOB_INIT_OOB2;
  OobPkg.OobHeader.MessageComplete = BIOS_OOB_MSG_COM;
  OobPkg.OobHeader.Status = 0;
  OobPkg.OobHeader.ProtocolVersioning = OOB_PROTOCOL_VERSION;
  OobPkg.OobHeader.Source = BIOS_OOB_BIOS;

  OobPkg.OobMsg.Type = BIOS_OOB_TYPE_PROVISIONING_STATE;
  OobPkg.OobMsg.Length = OOB_HEADER_SIZE + sizeof(OobData->ProvState)/sizeof(UINT8);
  if (sizeof(OobPkg.Data) >= OobPkg.OobMsg.Length) {
    CopyMem(OobPkg.Data, &OobData->ProvState, OobPkg.OobMsg.Length);
  } else {
    DEBUG((DEBUG_INFO, "Data overflow, sizeof OobPkg.Data : %d is smaller than OobPkg.OobMsg.Length : %d\n", sizeof(OobPkg.Data), OobPkg.OobMsg.Length));
    ASSERT(FALSE);
  }

  OobPkg.OobHeader.Length = OobPkg.OobMsg.Length + OOB_HEADER_SIZE;
  Length    = MAX_HECI_PACKAGE;
  DumpOobPackageInfo(&OobPkg);
  Status = HeciFlow->SendAndReceive (PSE_HECI, &OobPkg, OobPkg.OobHeader.Length, &Length , &gPseOobHeciClientInterfaceGuid);

  if (!EFI_ERROR (Status)) {
    DEBUG_CODE_BEGIN ();
      DEBUG ((DEBUG_INFO, "OOB data length: %x\n", OobPkg.OobMsg.Length));
      for (UINT32 Count = 0; Count < OobPkg.OobMsg.Length - OOB_HEADER_SIZE; Count++){
        DEBUG ((DEBUG_INFO, "0x%x ", OobPkg.Data[Count]));
      }
    DEBUG_CODE_END ();
    return EFI_SUCCESS;
  } else {
    DEBUG((DEBUG_INFO, "Error on fetching OOB response. Status : %x\n", Status));
    return EFI_NOT_FOUND;
  }
}

/*
  Reprovisioning flow

  Step 1: Sending data as below

  from Manifest
  1) ROOTCA
  2) Owner Public Key
  3) HKDR_32B_TPM_SALT
*/
EFI_STATUS
Reprovisioning (
  VOID
  )
{
  DEBUG((DEBUG_INFO, "Running Reprovisioning Flow\n"));
  return EFI_SUCCESS;
}

/**
  @param[out] OobRegion

  @retval     EFI_SUCCESS
  @retval     EFI_NOT_FOUND
**/
EFI_STATUS
EFIAPI
GetOobData (
  OUT OOB_DATA     *OobRegion OPTIONAL
  )
{
  EFI_STATUS            Status;
  OOB_DATA              TempOobRegion;
  VOID                  *Address;
  UINTN                 Size;

  Address   = NULL;
  Size      = 0;

  if (OobRegion == NULL) {
    //
    // It is NULL as input, so no BIOS ID will be returned.
    // Use temp buffer to hold the BIOS ID.
    //
    OobRegion = &TempOobRegion;
  }

  Address = GetFirstGuidHob (&gOobConfigSectionGuid);
  if (Address != NULL) {
    Size = sizeof (OOB_DATA);
    CopyMem ((VOID *) OobRegion, GET_GUID_HOB_DATA (Address), Size);

    DEBUG ((EFI_D_INFO, "DXE get OOB Data from HOB successfully\n"));
    return EFI_SUCCESS;
  }

  Status = GetSectionFromAnyFv (
             &gOobConfigSectionGuid,
             EFI_SECTION_RAW,
             0,
             &Address,
             &Size
             );
  if ((Status == EFI_SUCCESS) && (Address != NULL)) {
    //
    // OOB Data image is present in FV.
    //
    Size = sizeof (OOB_DATA);
    CopyMem ((VOID *) OobRegion, Address, Size);
    //
    // GetSectionFromAnyFv () allocated buffer for Address, now free it.
    //
    FreePool (Address);

    DEBUG ((EFI_D_INFO, "DXE get OOB Region from FV successfully\n"));
    return EFI_SUCCESS;
  }

  DEBUG ((EFI_D_ERROR, "DXE get OOB Region failed: %r\n", EFI_NOT_FOUND));
  return Status;
}

EFI_STATUS
OobInitEntryPoint (
  IN EFI_HANDLE ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  )
{
  EFI_STATUS            Status = EFI_SUCCESS;
  PCH_SETUP             PchSetup;
  UINTN                 VariableSize;
  UINTN                 PchPseBar;
  UINT32                PchPseBarLow;
  UINT32                PchPseBarHigh;
  UINT32                PimrData;
  UINT64                PchPseBase;
  UINT8                 PseDeviceNumber;
  UINT8                 PseFunctionNumber;
  OOB_DATA              OobPtr;

  Status = GetOobData(&OobPtr);
  if (Status != EFI_SUCCESS) {
    DEBUG((DEBUG_INFO, "Unable to find OOB region data!\n"));
    return Status;
  } else {
    DumpSubregionOob(&OobPtr);
  }

  if(OobPtr.ProvState == OOB_DISABLED) {
    DEBUG((DEBUG_INFO, "Exiting, Provision state not set in OOB_DATA.\n"));
    return EFI_ACCESS_DENIED;
  } else {
    VariableSize = sizeof (PCH_SETUP);
    Status = gRT->GetVariable (
                  L"PchSetup",
                  &gPchSetupVariableGuid,
                  NULL,
                  &VariableSize,
                  &PchSetup
                  );
    if (Status != EFI_SUCCESS) {
      DEBUG((DEBUG_INFO, "Get PSE Setup Variable failed with status: %x\n", Status));
      return Status;
    } else {
      PseDeviceNumber = PseGetDeviceNumber ();
      PseFunctionNumber = PseGetFunctionNumber ();

      PchPseBase = PCI_SEGMENT_LIB_ADDRESS (
                      DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                      DEFAULT_PCI_BUS_NUMBER_PCH,
                      PseDeviceNumber,
                      PseFunctionNumber,
                      0
                      );
      if (PciSegmentRead16 (PchPseBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
        DEBUG((DEBUG_INFO, "Skipping OOB as PSE device is disabled/not found.\n"));
        return EFI_NOT_FOUND;
      } else {
        DEBUG((DEBUG_INFO, "Starting OOB flow, clearing PIMR busy bit\n"));
        PchPseBarLow = PciSegmentRead32 (PchPseBase + R_PSE_CFG_BAR0_LOW) & ~(B_PSE_CFG_BAR0_MASK);
        PchPseBarHigh = PciSegmentRead32 (PchPseBase + R_PSE_CFG_BAR0_HIGH);
        PchPseBar = ((UINT64)PchPseBarHigh << 32) | PchPseBarLow;
        DEBUG((DEBUG_INFO, "PchPseBar : %x\n", PchPseBar));

        PimrData = MmioRead32 (PchPseBar + R_PSE_MMIO_PIMR_OFFSET);
        DEBUG((DEBUG_INFO, "PIMR Data (before): %x, ", PimrData));

        PimrData = PimrData & ~B_PSE_MMIO_PIMR_BUSY_CLEAR;
        DEBUG((DEBUG_INFO, "Masked Data: %x, ", PimrData));
        MmioWrite32 (PchPseBar + R_PSE_MMIO_PIMR_OFFSET, PimrData);

        PimrData = MmioRead32 (PchPseBar + R_PSE_MMIO_PIMR_OFFSET);
        DEBUG((DEBUG_INFO, "PIMR Data (after): %x\n", PimrData));

        Status = PseGetVersion ();
        if (!EFI_ERROR (Status)) {
          DEBUG((DEBUG_INFO, "OOB first boot: %x\n", PchSetup.PchPseOobIsFirstBootProvDone));
          if (PchSetup.PchPseOobIsFirstBootProvDone == FALSE) {
            Status = FirstBootProvisioning (&OobPtr);
          } else {
            Status = NormalBoot (&OobPtr);
          }
          /*
            TODO: Reprovisioning flow
            Status = Reprovisioning ();
          */
        } else {
          DEBUG((DEBUG_INFO, "Failed to get PSE Version with status: %x\n", Status));
        }
      }
    }
  }

  return Status;
}

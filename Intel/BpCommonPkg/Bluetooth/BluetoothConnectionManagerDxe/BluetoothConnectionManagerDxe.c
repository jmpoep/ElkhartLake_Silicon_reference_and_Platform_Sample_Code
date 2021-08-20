//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
 Bluetooth LE Connection Manager.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#include "BluetoothConnectionManagerDxe.h"
#include <Library/PerformanceLib.h>

BT_CONFIG_DEV                    *mBtConfigDevice;


EFI_GUID                         gHiiBluetoothConfigFormSetGuid = HII_BLUETOOTH_CONFIG_FORM_SET_GUID;
EFI_GUID                         gIfrRefreshRemoteDevGuid = HII_IFR_REFRESH_REMOT_DEV_GUID;

CHAR16 mLocalDeviceDataVariableName[] = L"LocalDeviceData";
HII_VENDOR_DEVICE_PATH  mBtConfigDevicePath = {
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8) (sizeof (VENDOR_DEVICE_PATH)),
        (UINT8) ((sizeof (VENDOR_DEVICE_PATH)) >> 8)
      }
    },
    HII_BLUETOOTH_CONFIG_FORM_SET_GUID
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    {
      (UINT8) (END_DEVICE_PATH_LENGTH),
      (UINT8) ((END_DEVICE_PATH_LENGTH) >> 8)
    }
  }
};

EFI_DRIVER_BINDING_PROTOCOL gBluetoothConfigDriverBinding = {
  BluetoothConfigDriverBindingSupported,
  BluetoothConfigDriverBindingStart,
  BluetoothConfigDriverBindingStop,
  0xa,
  NULL,
  NULL
};

typedef struct {
  BLUETOOTH_UUID   Uuid;
  CHAR16           *Name;
} UUID_NAME;

CHAR16    mUnknownUuidName[] = L"UnknownUUID (0x0000)";
UUID_NAME mServiceUuid16Name[] = {
    {BluetoothUuidServiceDiscoveryServerServiceClassID, L"ServiceDiscoveryServerServiceClassID"},
    {BluetoothUuidBrowseGroupDescriptorServiceClassID, L"BrowseGroupDescriptorServiceClassID"},
    {BluetoothUuidSerialPort, L"SerialPort"},
    {BluetoothUuidLANAccessUsingPPP, L"LANAccessUsingPPP"},
    {BluetoothUuidDialupNetworking, L"DialupNetworking"},
    {BluetoothUuidIrMCSync, L"IrMCSync"},
    {BluetoothUuidOBEXObjectPush, L"OBEXObjectPush"},
    {BluetoothUuidOBEXFileTransfer, L"OBEXFileTransfer"},
    {BluetoothUuidIrMCSyncCommand, L"IrMCSyncCommand"},
    {BluetoothUuidHeadset, L"Headset"},
    {BluetoothUuidCordlessTelephony, L"CordlessTelephony"},
    {BluetoothUuidAudioSource, L"AudioSource"},
    {BluetoothUuidAudioSink, L"AudioSink"},
    {BluetoothUuidAVRemoteControlTarget, L"AVRemoteControlTarget"},
    {BluetoothUuidAdvancedAudioDistribution, L"AdvancedAudioDistribution"},
    {BluetoothUuidAVRemoteControl, L"AVRemoteControl"},
    {BluetoothUuidAVRemoteControlController, L"AVRemoteControlController"},
    {BluetoothUuidIntercom, L"Intercom"},
    {BluetoothUuidFax, L"Fax"},
    {BluetoothUuidHeadsetAudioGateway, L"HeadsetAudioGateway"},
    {BluetoothUuidWAP, L"WAP"},
    {BluetoothUuidWAPClient, L"WAPClient"},
    {BluetoothUuidPANU, L"PANU"},
    {BluetoothUuidNAP, L"NAP"},
    {BluetoothUuidGN, L"GN"},
    {BluetoothUuidDirectPrinting, L"DirectPrinting"},
    {BluetoothUuidReferencePrinting, L"ReferencePrinting"},
    {BluetoothUuidBasicImagingProfile, L"BasicImagingProfile"},
    {BluetoothUuidImagingResponder, L"ImagingResponder"},
    {BluetoothUuidImagingAutomaticArchive, L"ImagingAutomaticArchive"},
    {BluetoothUuidImagingReferencedObjects, L"ImagingReferencedObjects"},
    {BluetoothUuidHandsfree, L"Handsfree"},
    {BluetoothUuidHandsfreeAudioGateway, L"HandsfreeAudioGateway"},
    {BluetoothUuidDirectPrintingReferenceObjectsService, L"DirectPrintingReferenceObjectsService"},
    {BluetoothUuidReflectedUI, L"ReflectedUI"},
    {BluetoothUuidBasicPrinting, L"BasicPrinting"},
    {BluetoothUuidPrintingStatus, L"PrintingStatus"},
    {BluetoothUuidHumanInterfaceDeviceService, L"HumanInterfaceDeviceService"},
    {BluetoothUuidHardcopyCableReplacement, L"HardcopyCableReplacement"},
    {BluetoothUuidHCRPrint, L"HCRPrint"},
    {BluetoothUuidHCRScan, L"HCRScan"},
    {BluetoothUuidCommonISDNAccess, L"CommonISDNAccess"},
    {BluetoothUuidSIMAccess, L"SIMAccess"},
    {BluetoothUuidPhonebookAccessPCE, L"PhonebookAccessPCE"},
    {BluetoothUuidPhonebookAccessPSE, L"PhonebookAccessPSE"},
    {BluetoothUuidPhonebookAccess, L"PhonebookAccess"},
    {BluetoothUuidHeadsetHS, L"HeadsetHS"},
    {BluetoothUuidMessageAccessServer, L"MessageAccessServer"},
    {BluetoothUuidMessageNotificationServer, L"MessageNotificationServer"},
    {BluetoothUuidMessageAccessProfile, L"MessageAccessProfile"},
    {BluetoothUuidGNSS, L"GNSS"},
    {BluetoothUuidGNSSServer, L"GNSSServer"},
    {BluetoothUuid3DDisplay, L"3DDisplay"},
    {BluetoothUuid3DGlasses, L"3DGlasses"},
    {BluetoothUuid3DSynchronization, L"3DSynchronization"},
    {BluetoothUuidMPSProfile, L"MPSProfile"},
    {BluetoothUuidMPSSC, L"MPSSC"},
    {BluetoothUuidPnPInformation, L"PnPInformation"},
    {BluetoothUuidGenericNetworking, L"GenericNetworking"},
    {BluetoothUuidGenericFileTransfer, L"GenericFileTransfer"},
    {BluetoothUuidGenericAudio, L"GenericAudio"},
    {BluetoothUuidGenericTelephony, L"GenericTelephony"},
    {BluetoothUuidUPNPService, L"UPNPService"},
    {BluetoothUuidUPNPIPService, L"UPNPIPService"},
    {BluetoothUuidESDPUPNPIPPAN, L"ESDPUPNPIPPAN"},
    {BluetoothUuidESDPUPNPIPLAP, L"ESDPUPNPIPLAP"},
    {BluetoothUuidESDPUPNPL2CAP, L"ESDPUPNPL2CAP"},
    {BluetoothUuidVideoSource, L"VideoSource"},
    {BluetoothUuidVideoSink, L"VideoSink"},
    {BluetoothUuidVideoDistribution, L"VideoDistribution"},
    {BluetoothUuidHDP, L"HDP"},
    {BluetoothUuidHDPSource, L"HDPSource"},
    {BluetoothUuidHDPSink, L"HDPSink"},
    {BluetoothUuidPublicBrowseRoot, L"PublicBrowseRoot"},
    {BluetoothUuidAlertNotificationService, L"AlertNotificationService"},
    {BluetoothUuidAutomationIO, L"AutomationIO"},
    {BluetoothUuidBatteryService, L"BatteryService"},
    {BluetoothUuidBloodPressure, L"BloodPressure"},
    {BluetoothUuidBodyComposition, L"BodyComposition"},
    {BluetoothUuidBondManagement, L"BondManagement"},
    {BluetoothUuidContinuousGlucoseMonitoring, L"ContinuousGlucoseMonitoring"},
    {BluetoothUuidCurrentTimeService, L"CurrentTimeService"},
    {BluetoothUuidCyclingPower, L"CyclingPower"},
    {BluetoothUuidCyclingSpeedandCadence, L"CyclingSpeedandCadence"},
    {BluetoothUuidDeviceInformation, L"DeviceInformation"},
    {BluetoothUuidEnvironmentalSensing, L"EnvironmentalSensing"},
    {BluetoothUuidGenericAccess, L"GenericAccess"},
    {BluetoothUuidGenericAttribute, L"GenericAttribute"},
    {BluetoothUuidGlucose, L"Glucose"},
    {BluetoothUuidHealthThermometer, L"HealthThermometer"},
    {BluetoothUuidHeartRate, L"HeartRate"},
    {BluetoothUuidHTTPProxy, L"HTTPProxy"},
    {BluetoothUuidHumanInterfaceDevice, L"HumanInterfaceDevice"},
    {BluetoothUuidImmediateAlert, L"ImmediateAlert"},
    {BluetoothUuidIndoorPositioning, L"IndoorPositioning"},
    {BluetoothUuidInternetProtocolSupport, L"InternetProtocolSupport"},
    {BluetoothUuidLinkLoss, L"LinkLoss"},
    {BluetoothUuidLocationandNavigation, L"LocationandNavigation"},
    {BluetoothUuidNextDSTChangeService, L"NextDSTChangeService"},
    {BluetoothUuidObjectTransfer, L"ObjectTransfer"},
    {BluetoothUuidPhoneAlertStatusService, L"PhoneAlertStatusService"},
    {BluetoothUuidPulseOximeter, L"PulseOximeter"},
    {BluetoothUuidReferenceTimeUpdateService, L"ReferenceTimeUpdateService"},
    {BluetoothUuidRunningSpeedandCadence, L"RunningSpeedandCadence"},
    {BluetoothUuidScanParameters, L"ScanParameters"},
    {BluetoothUuidTransportDiscovery, L"TransportDiscovery"},
    {BluetoothUuidTxPower, L"TxPower"},
    {BluetoothUuidUserData, L"UserData"},
    {BluetoothUuidWeightScale, L"WeightScale"},
  };

/**
  Connects all controllers with EFI Bluetooth ATTRIBUTE service binding
  protocol recursively.

  @param[in]  Event    Event whose notification function is being invoked.
  @param[in]  Context  The pointer to the notification function's context,
                       which is implementation-dependent.

**/
VOID
EFIAPI
StartDeviceDrivers (
  IN EFI_EVENT              Event,
  IN VOID                   *Context
  )
{
  EFI_HANDLE    *HandleBuffer;
  UINTN         NumberOfHandles;
  UINTN         Index;

  gBS->LocateHandleBuffer (
         ByProtocol,
         &gEfiBluetoothAttributeServiceBindingProtocolGuid,
         NULL,
         &NumberOfHandles,
         &HandleBuffer
         );

  for (Index = 0; Index < NumberOfHandles; Index++) {
    gBS->ConnectController (
           HandleBuffer[Index],
           NULL,
           NULL,
           TRUE
           );
  }

  if (HandleBuffer != NULL) {
    FreePool (HandleBuffer);
  }

}

/**
  Checks whether a given Bluetooth device address is valid or not.

  @param[in]  Address  A pointer to a Bluetooth device address to check.

  @retval  TRUE   The given Bluetooth device address is valid.
  @retval  FALSE  The given Bluetooth device address is not valid.

**/
BOOLEAN
IsValidBleAddress (
  IN BLUETOOTH_LE_ADDRESS    *Address
  )
{
  BLUETOOTH_LE_ADDRESS NullAddress;

  ASSERT (Address != NULL);

  ZeroMem (&NullAddress, sizeof(BLUETOOTH_LE_ADDRESS));
  return (BOOLEAN) (CompareMem (Address, &NullAddress, sizeof (BLUETOOTH_LE_ADDRESS)) != 0);
}

/**
  Finds a specific type of Generic Access Profile data from the Bluetooth LE
  advertisement data.

  @param[in]  AdvertisementData      A pointer to the BluetoothLE advertisement
                                     data.
  @param[in]  AdvertisementDataSize  The size of AdvertisementData in bytes.
  @param[in]  Type                   The given type of Generic Access Profile
                                     data to find in AdvertisementData.

  @retval  NULL    If the given type is not found in AdvertisementData.
  @retval  Others  Points to start of the given type in AdvertisementData.

**/
UINT8 *
FindTypeFromAdvertisementData (
  IN UINT8    *AdvertisementData,
  IN UINTN    AdvertisementDataSize,
  IN UINT8    Type
  )
{
  UINT8  *Data;

  Data = AdvertisementData;
  while (Data < AdvertisementData + AdvertisementDataSize) {
    if (*Data == 0) {
      break;
    }
    if (*(Data + 1) == Type) {
      return Data;
    }
    Data += (*Data + 1);
  }

  return NULL;
}

/**
  Get detail info for host controller.

  The caller need to free the buffer after using it.

  @param  BluetoothLeConfig     BluetoothLE config protocol for this device.
  @param  DataType              Type for the infor which need to get.
  @param  DataSize              Return the size of the return buffer.
  @param  Data                  Return the data for this info.

  @retval EFI_SUCCESS           The image has been unloaded.
**/
EFI_STATUS
GetInfoFromHandle (
  IN     EFI_BLUETOOTH_LE_CONFIG_PROTOCOL   *BluetoothLeConfig,
  IN     EFI_BLUETOOTH_CONFIG_DATA_TYPE     DataType,
  IN OUT UINTN                              *DataSize,
  IN OUT VOID                               **Data OPTIONAL
  )
{
  EFI_STATUS                       Status;
  UINTN                            BufferSize;
  UINT8                            *Buffer;

  if ((BluetoothLeConfig == NULL) || (DataSize == NULL) || ((*DataSize != 0) && (Data == NULL))) {
    return EFI_INVALID_PARAMETER;
  }

  if (DataType >= EfiBluetoothConfigDataTypeMax) {
    return EFI_NOT_FOUND;
  }

  *DataSize  = 0;
  BufferSize = 0;
  Buffer     = NULL;
  Status = BluetoothLeConfig->GetData (BluetoothLeConfig, DataType, &BufferSize, Buffer);
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return Status;
  }

  Buffer = AllocatePool (BufferSize);
  ASSERT (Buffer != NULL);

  Status = BluetoothLeConfig->GetData (BluetoothLeConfig, DataType, &BufferSize, Buffer);
  if (EFI_ERROR (Status)) {
    FreePool (Buffer);
    return Status;
  }

  *DataSize = BufferSize;
  *Data     = Buffer;

  return EFI_SUCCESS;
}

/**
  Locate the device from device list based on the MAC address.

  @param[in]   Addr          Input device address.
  @param[in]   AddressType   Address type.

  @return The device
**/
BT_REMOTE_DEVICE_ATTRIBUTE *
LocateDevInList (
  IN UINT8                       *Addr,
  IN EFI_BLUETOOTH_ADDRESS_TYPE  AddressType
  )
{
  LIST_ENTRY                       *Link;
  BT_REMOTE_DEVICE_ATTRIBUTE       *Dev;

  ASSERT (AddressType < EfiInvalidAddressType);

  for ( Link  = GetFirstNode (&mBtConfigDevice->RemoteDeviceList)
      ; !IsNull (&mBtConfigDevice->RemoteDeviceList, Link)
      ; Link = GetNextNode (&mBtConfigDevice->RemoteDeviceList, Link)) {
    Dev = BT_REMOTE_DEVICE_FROM_LINK (Link);

    switch (AddressType) {
    case EfiIdentifyAddressType:
      if (CompareMem (Addr, Dev->IDAddr.Address, sizeof (Dev->IDAddr.Address)) == 0) {
        return Dev;
      }
      break;

    case EfiAdvertisementAddressType:
      if (CompareMem (Addr, Dev->AdvAddr.Address, sizeof (Dev->AdvAddr.Address)) == 0) {
        return Dev;
      }
      break;

    default:
      ASSERT(AddressType == EfiAnyAddressType);
      if (((CompareMem (Addr, Dev->AdvAddr.Address, sizeof (Dev->AdvAddr.Address)) == 0)) ||
          ((CompareMem (Addr, Dev->IDAddr.Address, sizeof (Dev->IDAddr.Address)) == 0))) {
        return Dev;
      }
      break;
    }
  }

  return NULL;
}

/**
  Locate the device from Paired device storage based on the MAC address.

  @param[in]       IDAddr  Input device address. It's Identify address.
  @param[in, out]  Index   The index in the device array.

  @return The device storage.
**/
BT_LE_REMOTE_DEV_STORAGE  *
LocateDevInGlobalData (
  IN     BLUETOOTH_LE_ADDRESS  *IDAddr,
  IN OUT UINTN                 *Index
  )
{
  UINTN                     Count;

  for (Count = 0; Count < EFI_BLUETOOTH_LE_MAX_BONDED_DEV; Count++) {
    if (CompareMem (IDAddr->Address, &mBtConfigDevice->ControllerData.RemoteIDAddr[Count].Address, sizeof (IDAddr->Address)) == 0) {
      if (Index != NULL) {
        *Index = Count;
      }

      return &mBtConfigDevice->PairedDevData[Count];
    }
  }

  return NULL;
}

/**
  Refresh the device information.

  @param[in]  Dev       Pointer to the new device.
  @param[in]  ScanInfo  Data related to scan result.

**/
VOID
RefreshDeviceInformation (
  IN BT_REMOTE_DEVICE_ATTRIBUTE                      *Dev,
  IN EFI_BLUETOOTH_LE_SCAN_CALLBACK_INFORMATION      *ScanInfo
  )
{
  UINT8                 Len;
  UINT8                 *Data;

  Dev->RSSI = ScanInfo->RSSI;

  //
  // ID matches but BD might not match. So update it.
  //
  CopyMem (&Dev->AdvAddr, &ScanInfo->BDAddr.Address, sizeof(BLUETOOTH_LE_ADDRESS));

  Data = BluetoothFindTypeFromAdvData (ScanInfo->AdvertisementData, ScanInfo->AdvertisementDataSize, BluetoothGapTypeCompleteLocalName, &Len);
  if (Data != NULL) {
    ZeroMem(Dev->LocalName, sizeof(Dev->LocalName));
    CopyMem (Dev->LocalName, Data, MIN (Len, sizeof (Dev->LocalName) - 1));
  }

  Data = BluetoothFindTypeFromAdvData (ScanInfo->AdvertisementData, ScanInfo->AdvertisementDataSize, BluetoothGapTypeAppearance, &Len);
  if (Data != NULL) {
    Dev->Appearance = *((UINT16*)Data);
  }
}

/**
  Dump the data.

  @param[in]  ScanInfo      Data related to scan result.

**/
VOID
DumpScanInfo (
  IN EFI_BLUETOOTH_LE_SCAN_CALLBACK_INFORMATION *ScanInfo
  )
{
  UINTN  Index;

  DEBUG ((DEBUG_INFO, "BtCfgDxe :: ScanInfo from %02x:%02x:%02x:%02x:%02x:%02x(%x)",
                        ScanInfo->BDAddr.Address[0], ScanInfo->BDAddr.Address[1],
                        ScanInfo->BDAddr.Address[2], ScanInfo->BDAddr.Address[3],
                        ScanInfo->BDAddr.Address[4], ScanInfo->BDAddr.Address[5],
                        ScanInfo->BDAddr.Type
                        ));
  DEBUG ((DEBUG_INFO, "/%02x:%02x:%02x:%02x:%02x:%02x(%x), ",
                        ScanInfo->DirectAddress.Address[0], ScanInfo->DirectAddress.Address[1],
                        ScanInfo->DirectAddress.Address[2], ScanInfo->DirectAddress.Address[3],
                        ScanInfo->DirectAddress.Address[4], ScanInfo->DirectAddress.Address[5],
                        ScanInfo->DirectAddress.Type
                        ));

  DEBUG ((DEBUG_INFO, "State/dBm/DataSize = %x/%d/%x\n",
                        ScanInfo->RemoteDeviceState,
                        ScanInfo->RSSI,
                        ScanInfo->AdvertisementDataSize
                        ));

  for (Index = 0; Index < ScanInfo->AdvertisementDataSize; ) {
    DEBUG ((DEBUG_INFO, " %02x", ((UINT8*)ScanInfo->AdvertisementData)[Index]));
    Index++;
    if ((Index % 0x10) == 0) {
      DEBUG ((DEBUG_INFO, "\n"));
    }
  }

  if ((Index % 0x10) != 0) {
    DEBUG ((DEBUG_INFO, "\n"));
  }
}

/**
  Dump remote device list information.

**/
VOID
DumpRemoteDeviceList (
  VOID
  )
{
  LIST_ENTRY                       *Link;
  BT_REMOTE_DEVICE_ATTRIBUTE       *RemoteDev;
  UINTN                            Index;

  Index = 0;
  DEBUG ((EFI_D_INFO, "BtCfgDxe :: Dump Remote Device List Begin:\n"));

  EfiAcquireLock (&mBtConfigDevice->DeviceListLock);

  for ( Link  = GetFirstNode (&mBtConfigDevice->RemoteDeviceList)
      ; !IsNull (&mBtConfigDevice->RemoteDeviceList, Link)
      ; Link = GetNextNode (&mBtConfigDevice->RemoteDeviceList, Link)
      ) {
    RemoteDev = BT_REMOTE_DEVICE_FROM_LINK(Link);

    DEBUG ((DEBUG_INFO, " %02d - %02x:%02x:%02x:%02x:%02x:%02x(%x)",
                          Index,
                          RemoteDev->AdvAddr.Address[0], RemoteDev->AdvAddr.Address[1],
                          RemoteDev->AdvAddr.Address[2], RemoteDev->AdvAddr.Address[3],
                          RemoteDev->AdvAddr.Address[4], RemoteDev->AdvAddr.Address[5],
                          RemoteDev->AdvAddr.Type
                          ));

    DEBUG ((DEBUG_INFO, "/%02x:%02x:%02x:%02x:%02x:%02x(%x), ",
                          RemoteDev->IDAddr.Address[0], RemoteDev->IDAddr.Address[1],
                          RemoteDev->IDAddr.Address[2], RemoteDev->IDAddr.Address[3],
                          RemoteDev->IDAddr.Address[4], RemoteDev->IDAddr.Address[5],
                          RemoteDev->IDAddr.Type
                          ));

    DEBUG ((DEBUG_INFO, "State/dBm/Appearance/Name = %x/%d/%x/%a\n",
                          RemoteDev->RemoteDeviceState,
                          RemoteDev->RSSI,
                          RemoteDev->Appearance,
                          RemoteDev->LocalName
                          ));

    Index ++;
  }

  EfiReleaseLock (&mBtConfigDevice->DeviceListLock);
}

/**
  Callback function used by bus driver to inform new device founded.

  @param[in]  This      Blue tooth config protocol for this device.
  @param[in]  Context   Context used by caller.
  @param[in]  ScanInfo  Data related to scan result. NULL ScanInfo means scan
                        complete.

  @retval EFI_SUCCESS  The image has been unloaded.

**/
EFI_STATUS
EFIAPI
ScanCallback (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL                              *This,
  IN VOID                                                          *Context,
  IN EFI_BLUETOOTH_LE_SCAN_CALLBACK_INFORMATION                    *ScanInfo
  )
{
  BT_REMOTE_DEVICE_ATTRIBUTE    *RemoteDevAttr;

  if (!mBtConfigDevice->InScanning) {
    DEBUG ((DEBUG_ERROR, "BtCfgDxe :: Scan callback trigged not during scanning!!!\n"));
  }

  mBtConfigDevice->FoundNewDevice = TRUE;
  gBS->SignalEvent (mBtConfigDevice->RefreshRemoteDevEvent);

  if (ScanInfo == NULL) {
    //
    // NULL ScanInfo indicates scan is finished.
    //
    mBtConfigDevice->UpdateScanMenu = TRUE;
    mBtConfigDevice->InScanning = FALSE;
    DEBUG ((DEBUG_INFO, "BtCfgDxe :: !!! Scan finished !!!\n"));
    DumpRemoteDeviceList();
    return EFI_SUCCESS;
  }

  DumpScanInfo (ScanInfo);

  EfiAcquireLock (&mBtConfigDevice->DeviceListLock);

  RemoteDevAttr = LocateDevInList (ScanInfo->BDAddr.Address, EfiAdvertisementAddressType);
  if (RemoteDevAttr != NULL) {
    //
    // Refresh information for existing device.
    //
    RefreshDeviceInformation(RemoteDevAttr, ScanInfo);
    DEBUG ((DEBUG_INFO, "BtCfgDxe :: Refresh device in list in scanning: %02x:%02x:%02x:%02x:%02x:%02x(%x), Name : %a\n",
      RemoteDevAttr->AdvAddr.Address[0], RemoteDevAttr->AdvAddr.Address[1],
      RemoteDevAttr->AdvAddr.Address[2], RemoteDevAttr->AdvAddr.Address[3],
      RemoteDevAttr->AdvAddr.Address[4], RemoteDevAttr->AdvAddr.Address[5],
      RemoteDevAttr->AdvAddr.Type,
      RemoteDevAttr->LocalName
      ));
    EfiReleaseLock (&mBtConfigDevice->DeviceListLock);

    return EFI_SUCCESS;
  }
  EfiReleaseLock (&mBtConfigDevice->DeviceListLock);

  //
  // A new device is found in scanning.
  //
  RemoteDevAttr = AllocateZeroPool (sizeof (BT_REMOTE_DEVICE_ATTRIBUTE));
  ASSERT (RemoteDevAttr != NULL);
  RemoteDevAttr->Signature = BT_REMOTE_DEVICE_SIGNATURE;
  RefreshDeviceInformation(RemoteDevAttr, ScanInfo);

  EfiAcquireLock (&mBtConfigDevice->DeviceListLock);
  InsertTailList (&mBtConfigDevice->RemoteDeviceList, &RemoteDevAttr->Link);
  EfiReleaseLock (&mBtConfigDevice->DeviceListLock);

  DEBUG ((DEBUG_INFO, "BtCfgDxe :: Add device to List in scanning: %02x:%02x:%02x:%02x:%02x:%02x(%x), Name : %a\n",
    RemoteDevAttr->AdvAddr.Address[0], RemoteDevAttr->AdvAddr.Address[1],
    RemoteDevAttr->AdvAddr.Address[2], RemoteDevAttr->AdvAddr.Address[3],
    RemoteDevAttr->AdvAddr.Address[4], RemoteDevAttr->AdvAddr.Address[5],
    RemoteDevAttr->AdvAddr.Type,
    RemoteDevAttr->LocalName
    ));

  return EFI_SUCCESS;
}

/**

  Dump remote device data structure.

  @param[in]      RemoteDevData            Remote device data structure.

**/
VOID
DumpRemoteDeviceData (
  IN BT_LE_REMOTE_DEV_STORAGE  *RemoteDevData
  )
{
  UINTN                       Count;

  DEBUG ((DEBUG_INFO, "BtCfgDxe :: Dump RemoteDevData begin:\n"));
  DEBUG ((DEBUG_INFO, " PeerName: %a\n",          RemoteDevData->PeerName));
  DEBUG ((DEBUG_INFO, " KeysDistributed: 0x%x\n", RemoteDevData->KeysDistributed));
  DEBUG ((DEBUG_INFO, " KeySize: 0x%x\n",         RemoteDevData->KeySize));
  DEBUG ((DEBUG_INFO, " AuthReq: 0x%x\n",         RemoteDevData->AuthReq));
  DEBUG ((DEBUG_INFO, " PeerEdiv: 0x%x\n",        RemoteDevData->PeerEdiv));
  DEBUG ((DEBUG_INFO, " PeerSignCounter: 0x%x\n", RemoteDevData->PeerSignCounter));
  DEBUG ((DEBUG_INFO, " LocalSignCounter: 0x%x\n",RemoteDevData->LocalSignCounter));

  DEBUG ((DEBUG_INFO, " PeerLtk:"));
  for (Count = 0; Count < sizeof (RemoteDevData->PeerLtk); Count++) {
    DEBUG ((DEBUG_INFO, " %02x", RemoteDevData->PeerLtk[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG ((DEBUG_INFO, " PeerIrk:"));
  for (Count = 0; Count < sizeof (RemoteDevData->PeerIrk); Count++) {
    DEBUG ((DEBUG_INFO, " %02x", RemoteDevData->PeerIrk[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG ((DEBUG_INFO, " PeerCsrk:"));
  for (Count = 0; Count < sizeof (RemoteDevData->PeerCsrk); Count++) {
    DEBUG ((DEBUG_INFO, " %02x", RemoteDevData->PeerCsrk[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG ((DEBUG_INFO, " PeerRand:"));
  for (Count = 0; Count < sizeof (RemoteDevData->PeerRand); Count++) {
    DEBUG ((DEBUG_INFO, " %02x", RemoteDevData->PeerRand[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG ((DEBUG_INFO, " LocalLtk:"));
  for (Count = 0; Count < sizeof (RemoteDevData->LocalLtk); Count++) {
    DEBUG ((DEBUG_INFO, " %02x", RemoteDevData->LocalLtk[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG ((DEBUG_INFO, " LocalIrk:"));
  for (Count = 0; Count < sizeof (RemoteDevData->LocalIrk); Count++) {
    DEBUG ((DEBUG_INFO, " %02x", RemoteDevData->LocalIrk[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  DEBUG ((DEBUG_INFO, " LocalCsrk:"));
  for (Count = 0; Count < sizeof (RemoteDevData->LocalCsrk); Count++) {
    DEBUG ((DEBUG_INFO, " %02x", RemoteDevData->LocalCsrk[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));
}

/**

  Dump local device data structure.

  @param[in]      LocalData            Local device data structure.

**/
VOID
DumpLocalDeviceData (
  IN BT_LE_LOCAL_DEV_STORAGE  *LocalData
  )
{
  UINTN                       Count;

  DEBUG ((DEBUG_INFO, "BtCfgDxe :: Dump LocalDeviceData (%a) begin:\n Irk:", LocalData->LocalName));
  for (Count = 0; Count < sizeof (LocalData->KeyIrk); Count++) {
    DEBUG ((DEBUG_INFO, " %02x", LocalData->KeyIrk[Count]));
  }
  DEBUG ((DEBUG_INFO, "\n"));

  for (Count = 0; Count < EFI_BLUETOOTH_LE_MAX_BONDED_DEV; Count++) {
    if (IsValidBleAddress (&LocalData->RemoteIDAddr[Count])) {
      DEBUG ((DEBUG_INFO, " %02x - %02x:%02x:%02x:%02x:%02x:%02x(%x)\n",
                            Count,
                            LocalData->RemoteIDAddr[Count].Address[0],
                            LocalData->RemoteIDAddr[Count].Address[1],
                            LocalData->RemoteIDAddr[Count].Address[2],
                            LocalData->RemoteIDAddr[Count].Address[3],
                            LocalData->RemoteIDAddr[Count].Address[4],
                            LocalData->RemoteIDAddr[Count].Address[5],
                            LocalData->RemoteIDAddr[Count].Type));
    }
  }
}

/**
  Dump advertisement data.

  @param[in]  AdvertisementData      A pointer to the BluetoothLE advertisement data.
  @param[in]  AdvertisementDataSize  The size of AdvertisementData in bytes.

**/
VOID
DumpAdvertisementData (
  IN UINT8                *AdvertisementData,
  IN UINT32               AdvertisementDataSize
  )
{
  UINTN Count;

  DEBUG ((DEBUG_INFO, "BtCfgDxe :: Dump Advertisement Data: Length = 0x%x\n", AdvertisementDataSize));
  for (Count = 0; Count < AdvertisementDataSize; ) {
    DEBUG ((DEBUG_INFO, " %02x", AdvertisementData[Count]));
    Count++;

    if (Count % 16 == 0) {
      DEBUG ((DEBUG_INFO, "\n"));
    }
  }

  DEBUG ((DEBUG_INFO, "\n"));
}

/**

  Delete the specified device from global data and storage.

  @param[in]      RemoteIDAddr            Remote device address. Input the Identify Address.
  @param[in]      DeleteStorage           Delete related storage or not.

**/
EFI_STATUS
DeletePairedDevice (
  IN BLUETOOTH_LE_ADDRESS           *RemoteIDAddr,
  IN BOOLEAN                        DeleteStorage
  )
{
  EFI_STATUS               Status;
  UINTN                    LocalDataSize;
  UINTN                    Index;
  CHAR16                   RemoteBdAddrStr[LE_BD_ADDR_STR_LEN];
  BT_LE_REMOTE_DEV_STORAGE *RemoteData;

  DumpLocalDeviceData (&mBtConfigDevice->ControllerData);

  RemoteData = LocateDevInGlobalData (RemoteIDAddr, &Index);
  if (RemoteData == NULL) {
    DEBUG ((EFI_D_ERROR , "BtCfgDxe :: Device is not in LocalDeviceData (%02x:%02x:%02x:%02x:%02x:%02x(%x))\n",
                  RemoteIDAddr->Address[0], RemoteIDAddr->Address[1],
                  RemoteIDAddr->Address[2], RemoteIDAddr->Address[3],
                  RemoteIDAddr->Address[4], RemoteIDAddr->Address[5],
                  RemoteIDAddr->Type));
    return EFI_NOT_FOUND;
  }

  ZeroMem (RemoteData, sizeof (BT_LE_REMOTE_DEV_STORAGE));
  ZeroMem (&mBtConfigDevice->ControllerData.RemoteIDAddr[Index], sizeof (BLUETOOTH_LE_ADDRESS));
  if (!DeleteStorage) {
    return EFI_SUCCESS;
  }

  LocalDataSize = sizeof(BT_LE_LOCAL_DEV_STORAGE);
  Status = gRT->SetVariable(mLocalDeviceDataVariableName,
      &gEfiBluetoothLeConfigProtocolGuid,
      EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
      LocalDataSize,
      &mBtConfigDevice->ControllerData);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR , "BtCfgDxe :: Failed to delete device in LocalDeviceData (%02x:%02x:%02x:%02x:%02x:%02x(%x))\n",
                  RemoteIDAddr->Address[0], RemoteIDAddr->Address[1],
                  RemoteIDAddr->Address[2], RemoteIDAddr->Address[3],
                  RemoteIDAddr->Address[4], RemoteIDAddr->Address[5],
                  RemoteIDAddr->Type));
    return EFI_ACCESS_DENIED;
  }

  ZeroMem(RemoteBdAddrStr, sizeof(RemoteBdAddrStr));
  LE_BDADDR_TO_STRING(RemoteBdAddrStr, RemoteIDAddr->Address, RemoteIDAddr->Type);

  Status = gRT->SetVariable(RemoteBdAddrStr,
      &gEfiBluetoothLeConfigProtocolGuid,
      EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
      0,
      NULL);
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR , "BtCfgDxe :: Can't delete device local stoage (%02x:%02x:%02x:%02x:%02x:%02x(%x))\n",
                  RemoteIDAddr->Address[0], RemoteIDAddr->Address[1],
                  RemoteIDAddr->Address[2], RemoteIDAddr->Address[3],
                  RemoteIDAddr->Address[4], RemoteIDAddr->Address[5],
                  RemoteIDAddr->Type));
    return EFI_ACCESS_DENIED;
  }

  mBtConfigDevice->PairedDevDataSaved[Index] = FALSE;
  mBtConfigDevice->PairedDevCount--;

  DEBUG ((DEBUG_INFO, "BtCfgDxe :: SUCCESS delete device in local data and stoage (%02x:%02x:%02x:%02x:%02x:%02x(%x))\n",
                RemoteIDAddr->Address[0], RemoteIDAddr->Address[1],
                RemoteIDAddr->Address[2], RemoteIDAddr->Address[3],
                RemoteIDAddr->Address[4], RemoteIDAddr->Address[5],
                RemoteIDAddr->Type));

  return EFI_SUCCESS;
}

/**

  Save the specified device to storage.

  @param[in]      RemoteIDAddr            Remote device address. Input the identify address.

**/
EFI_STATUS
SavePairedDevice (
  IN BLUETOOTH_LE_ADDRESS              *RemoteIDAddr
  )
{
  CHAR16                   RemoteBdAddrStr[LE_BD_ADDR_STR_LEN];
  UINTN                    RemoteDataSize;
  UINTN                    LocalDataSize;
  UINTN                    Index;
  BT_LE_REMOTE_DEV_STORAGE *RemoteData;
  EFI_STATUS               Status;

  DEBUG ((DEBUG_INFO, "BtCfgDxe :: Begin to save Device %02x:%02x:%02x:%02x:%02x:%02x(%x)\n",
                        RemoteIDAddr->Address[0], RemoteIDAddr->Address[1],
                        RemoteIDAddr->Address[2], RemoteIDAddr->Address[3],
                        RemoteIDAddr->Address[4], RemoteIDAddr->Address[5],
                        RemoteIDAddr->Type));

  DumpLocalDeviceData (&mBtConfigDevice->ControllerData);

  RemoteData = LocateDevInGlobalData (RemoteIDAddr, &Index);
  if (RemoteData == NULL) {
    DEBUG ((DEBUG_ERROR, "BtCfgDxe :: Device not found in the maintained storage!"));
    return EFI_NOT_FOUND;
  }

  DumpRemoteDeviceData (RemoteData);

  ZeroMem(RemoteBdAddrStr, sizeof(RemoteBdAddrStr));
  LE_BDADDR_TO_STRING(RemoteBdAddrStr, RemoteIDAddr->Address, RemoteIDAddr->Type);
  RemoteDataSize = sizeof(BT_LE_REMOTE_DEV_STORAGE);
  Status = gRT->SetVariable(RemoteBdAddrStr,
      &gEfiBluetoothLeConfigProtocolGuid,
      EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
      RemoteDataSize,
      RemoteData);
  if (!EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "BtCfgDxe :: Add new storage for Device = %02x:%02x:%02x:%02x:%02x:%02x(%x)\n",
                          RemoteIDAddr->Address[0], RemoteIDAddr->Address[1],
                          RemoteIDAddr->Address[2], RemoteIDAddr->Address[3],
                          RemoteIDAddr->Address[4], RemoteIDAddr->Address[5],
                          RemoteIDAddr->Type));
  }

  //
  // Saved this device before means this devcie already saved in
  // LocalDeviceData, so skip to save in LocalDeviceData.
  //
  if (mBtConfigDevice->PairedDevDataSaved[Index]) {
    return EFI_SUCCESS;
  }

  mBtConfigDevice->PairedDevDataSaved[Index] = TRUE;
  mBtConfigDevice->PairedDevCount++;

  LocalDataSize = sizeof(BT_LE_LOCAL_DEV_STORAGE);
  Status = gRT->SetVariable(mLocalDeviceDataVariableName,
      &gEfiBluetoothLeConfigProtocolGuid,
      EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
      LocalDataSize,
      &mBtConfigDevice->ControllerData);
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Connect device.

  @param[in]  RemoteDev     Disconnect the device specified.
**/
VOID
ConnectDevice (
  IN BT_REMOTE_DEVICE_ATTRIBUTE       *RemoteDev
  )
{
  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *LeConfigProtocol;
  BLUETOOTH_LE_ADDRESS             *BleAddress;

  LeConfigProtocol = mBtConfigDevice->BluetoothLeConfig;

  mBtConfigDevice->CurrentBondingDev = RemoteDev;
  if (IsValidBleAddress(&RemoteDev->IDAddr)) {
    mBtConfigDevice->CurrentBondingIDAddress = TRUE;
    BleAddress = &RemoteDev->IDAddr;
  } else {
    mBtConfigDevice->CurrentBondingIDAddress = FALSE;
    BleAddress = &RemoteDev->AdvAddr;
  }

  ASSERT (mBtConfigDevice->ConnectState == StateIdle);
  //
  // Change BluetoothPhaseType to StateConnecting to let later while code to wait for the connect return.
  //
  mBtConfigDevice->ConnectState = StateConnecting;

  DEBUG ((EFI_D_INFO, "BtCfgDxe :: Connect Device: %a, IDAddr: %02x:%02x:%02x:%02x:%02x:%02x(%x)\n",
    RemoteDev->LocalName,
    BleAddress->Address[0], BleAddress->Address[1],
    BleAddress->Address[2], BleAddress->Address[3],
    BleAddress->Address[4], BleAddress->Address[5],
    BleAddress->Type
    ));

  LeConfigProtocol->Connect (LeConfigProtocol, TRUE, TRUE, 0, BleAddress);

  do {} while (mBtConfigDevice->ConnectState == StateConnecting);
  ASSERT (mBtConfigDevice->ConnectState == StateIdle);

  mBtConfigDevice->CurrentBondingDev = NULL;
}

/**
  Disconnect device.

  @param[in]  RemoteDev     Disconnect the device specified.
  @param[in]  Reason        Bluetooth disconnect reason.
**/
VOID
DisconnectDevice (
  IN BT_REMOTE_DEVICE_ATTRIBUTE       *RemoteDev,
  IN UINT8                             Reason
  )
{
  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *LeConfigProtocol;
  BLUETOOTH_LE_ADDRESS             *BleAddress;

  ASSERT (mBtConfigDevice->ConnectState == StateIdle);
  ASSERT ((RemoteDev->RemoteDeviceState & EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED) != 0);

  LeConfigProtocol = mBtConfigDevice->BluetoothLeConfig;

  mBtConfigDevice->CurrentBondingDev = RemoteDev;

  if (IsValidBleAddress(&RemoteDev->IDAddr)) {
    mBtConfigDevice->CurrentBondingIDAddress = TRUE;
    BleAddress = &RemoteDev->IDAddr;
  } else {
    mBtConfigDevice->CurrentBondingIDAddress = FALSE;
    BleAddress = &RemoteDev->AdvAddr;
  }

  DEBUG ((EFI_D_INFO, "BtCfgDxe :: Disconnect Device[%x]: %a, IDAddr: %02x:%02x:%02x:%02x:%02x:%02x(%x)\n",
    RemoteDev->RemoteDeviceState,
    RemoteDev->LocalName,
    BleAddress->Address[0], BleAddress->Address[1],
    BleAddress->Address[2], BleAddress->Address[3],
    BleAddress->Address[4], BleAddress->Address[5],
    BleAddress->Type
    ));

  //
  // Change BluetoothPhaseType to StateDisconnecting to let later while code to wait for the disconnect return.
  //
  if ((RemoteDev->RemoteDeviceState & EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED) != 0) {
    mBtConfigDevice->ConnectState = StateDisconnecting;
  }

  //
  // Even if device is disconnected, still call it to let iLE stack remove this device from auto reconnect list.
  //
  LeConfigProtocol->Disconnect (LeConfigProtocol, BleAddress, Reason);

  if ((RemoteDev->RemoteDeviceState & EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED) != 0) {
    //
    // Wait until LinkConnCompCallback transfer from StateDisconnecting to StateIdle.
    //
    do {} while (mBtConfigDevice->ConnectState == StateDisconnecting);
  }
  ASSERT (mBtConfigDevice->ConnectState == StateIdle);

  mBtConfigDevice->CurrentBondingDev = NULL;
}


/**
  Delete the specified device from device list.

  @param[in]  IDAddr     A pointer to a Bluetooth device address to delete.
                         Address is Identify address.

**/
VOID
DeleteRemoteDeviceByAddress (
  IN  BLUETOOTH_LE_ADDRESS         *IDAddr
  )
{
  LIST_ENTRY                       *Link;
  BT_REMOTE_DEVICE_ATTRIBUTE       *RemoteDev;
  ASSERT (IDAddr != NULL);

  EfiAcquireLock (&mBtConfigDevice->DeviceListLock);

  Link = GetFirstNode (&mBtConfigDevice->RemoteDeviceList);
  while (!IsNull (&mBtConfigDevice->RemoteDeviceList, Link)) {
    RemoteDev = BT_REMOTE_DEVICE_FROM_LINK (Link);
    Link = GetNextNode (&mBtConfigDevice->RemoteDeviceList, Link);

    if (CompareMem (RemoteDev->IDAddr.Address, IDAddr->Address, sizeof (IDAddr->Address)) == 0) {
      RemoveEntryList (&RemoteDev->Link);
      EfiReleaseLock (&mBtConfigDevice->DeviceListLock);

      DEBUG ((EFI_D_INFO, "BtCfgDxe :: User request Delete device: %02x:%02x:%02x:%02x:%02x:%02x(%x) (%a)\n",
        RemoteDev->IDAddr.Address[0], RemoteDev->IDAddr.Address[1],
        RemoteDev->IDAddr.Address[2], RemoteDev->IDAddr.Address[3],
        RemoteDev->IDAddr.Address[4], RemoteDev->IDAddr.Address[5],
        RemoteDev->IDAddr.Type,
        RemoteDev->LocalName
      ));

      DeletePairedDevice (&RemoteDev->IDAddr, TRUE);

      FreePool (RemoteDev);
      return;
    }
  }

  EfiReleaseLock (&mBtConfigDevice->DeviceListLock);

  DEBUG ((EFI_D_ERROR, "BtCfgDxe :: Not found device in List %02x:%02x:%02x:%02x:%02x:%02x(%x))\n",
    IDAddr->Address[0], IDAddr->Address[1],
    IDAddr->Address[2], IDAddr->Address[3],
    IDAddr->Address[4], IDAddr->Address[5],
    IDAddr->Type));
  DumpRemoteDeviceList ();
}

/**
  Delete the specified device from Device state


  @param[in]  DeviceState     Specify the device state. Idle/connect/paired.

**/
VOID
DeleteRemoteDeviceByState (
  IN  UINT32                       DeviceState
  )
{
  LIST_ENTRY                       *Link;
  BT_REMOTE_DEVICE_ATTRIBUTE       *RemoteDev;

  EfiAcquireLock (&mBtConfigDevice->DeviceListLock);

  Link = GetFirstNode (&mBtConfigDevice->RemoteDeviceList);
  while (!IsNull (&mBtConfigDevice->RemoteDeviceList, Link)) {
    RemoteDev = BT_REMOTE_DEVICE_FROM_LINK (Link);
    Link = GetNextNode (&mBtConfigDevice->RemoteDeviceList, Link);

    if (RemoteDev->RemoteDeviceState == DeviceState) {
      DEBUG ((EFI_D_INFO, "BtCfgDxe :: User request to Delete device: %02x:%02x:%02x:%02x:%02x:%02x(%x) (%a)\n",
        RemoteDev->AdvAddr.Address[0], RemoteDev->AdvAddr.Address[1],
        RemoteDev->AdvAddr.Address[2], RemoteDev->AdvAddr.Address[3],
        RemoteDev->AdvAddr.Address[4], RemoteDev->AdvAddr.Address[5],
        RemoteDev->AdvAddr.Type,
        RemoteDev->LocalName
      ));

      RemoveEntryList (&RemoteDev->Link);
      FreePool (RemoteDev);
    }
  }
  EfiReleaseLock (&mBtConfigDevice->DeviceListLock);
}

/**
  Gets an string that contains the address information of the host controller.

  @param[in]   ConfigProtocol  A pointer to EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                               structure.
  @param[out]  DevAddress      A pointer to an string which contains the
                               address information of the host controller.

  @retval  Other        A value from other functions.
  @retval  EFI_SUCCESS  The host controller address string is returned.

**/
EFI_STATUS
GetDeviceAddress (
  IN  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL    *ConfigProtocol,
  OUT CHAR16                              **DevAddress
  )
{
  EFI_STATUS                       Status;
  UINTN                            DataSize;
  UINT8                            *Buffer;
  BLUETOOTH_LE_ADDRESS             *LeAddr;

  DataSize = 0;
  Buffer   = NULL;

  Status = GetInfoFromHandle(ConfigProtocol, EfiBluetoothConfigDataTypeBDADDR, &DataSize, (void**)&Buffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  LeAddr = (BLUETOOTH_LE_ADDRESS *) Buffer;

  *DevAddress = AllocateZeroPool (DataSize * sizeof (CHAR16) * 3);
  ASSERT (*DevAddress != NULL);
  UnicodeSPrint (
    *DevAddress,
    DataSize * sizeof (CHAR16) * 3,
    L"%02x-%02x-%02x-%02x-%02x-%02x",
    (UINTN)LeAddr->Address[0],
    (UINTN)LeAddr->Address[1],
    (UINTN)LeAddr->Address[2],
    (UINTN)LeAddr->Address[3],
    (UINTN)LeAddr->Address[4],
    (UINTN)LeAddr->Address[5]
    );

  FreePool (Buffer);

  return EFI_SUCCESS;
}

/**
  Gets an string that contains the device name of the host controller.

  @param[in]   ConfigProtocol  A pointer to EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                               structure.
  @param[out]  LocalName       A pointer to an string which contains the
                               device name of the host controller.

  @retval  EFI_SUCCESS  The host controller device name is returned.
  @retval  Other        A value from other functions.

**/
EFI_STATUS
GetLocalName (
  IN  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL    *ConfigProtocol,
  OUT CHAR16                              **LocalName
  )
{
  EFI_STATUS                       Status;
  UINTN                            DataSize;
  UINT8                            *Buffer;
  CHAR16                           *UniDeviceName;

  DataSize = 0;
  Buffer   = NULL;
  Status   = EFI_SUCCESS;

  Status = GetInfoFromHandle(ConfigProtocol, EfiBluetoothConfigDataTypeDeviceName, &DataSize, (void**)&Buffer);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (DataSize == 0) {
    //
    // Device Name is NULL, get the Address.
    //
    Status = GetDeviceAddress (ConfigProtocol, &UniDeviceName);
    ASSERT_EFI_ERROR (Status);
  } else {
    DEBUG ((DEBUG_INFO, "BtCfgDxe :: Get local name from %a\n", Buffer));
    UniDeviceName = AllocateZeroPool (DataSize * sizeof (CHAR16));
    ASSERT (UniDeviceName != NULL);
    AsciiStrToUnicodeStrS ((const CHAR8*)Buffer, UniDeviceName, DataSize);
  }

  *LocalName = UniDeviceName;

  FreePool (Buffer);

  return EFI_SUCCESS;
}

/**
  Sets the device name of the host controller with a given string.

  @param[in]  ConfigProtocol  A pointer to EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                              structure.
  @param[in]  LocalName       A pointer to an string that will be set as the
                              device name of the host controller.

  @retval  Other  A value from other functions.

**/
EFI_STATUS
SetLocalName (
  IN  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL    *ConfigProtocol,
  IN  CHAR16                              *LocalName
  )
{
  CHAR8        *AsciiName;
  EFI_STATUS   Status;
  UINTN        LocalDataSize;
  UINTN        MaxStrLen;

  MaxStrLen = StrLen (LocalName) + 1;
  AsciiName = AllocateZeroPool (MaxStrLen);
  ASSERT (AsciiName != NULL);
  UnicodeStrToAsciiStrS(LocalName, AsciiName, MaxStrLen);

  AsciiStrCpyS((CHAR8 *)mBtConfigDevice->ControllerData.LocalName, sizeof (mBtConfigDevice->ControllerData.LocalName), AsciiName);
  LocalDataSize = sizeof(BT_LE_LOCAL_DEV_STORAGE);
  Status = gRT->SetVariable(mLocalDeviceDataVariableName,
             &gEfiBluetoothLeConfigProtocolGuid,
             EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
             LocalDataSize,
             &mBtConfigDevice->ControllerData);
  ASSERT_EFI_ERROR (Status);

  return ConfigProtocol->SetData (ConfigProtocol, EfiBluetoothConfigDataTypeDeviceName, AsciiStrnLenS (AsciiName, MaxStrLen), AsciiName);
}

/**
  Update the question value input in Callback function.

  @param  Type                  The input value type.
  @param  Value                 The input value buffer.
  @param  RetValue              The value need to return.

**/
VOID
GetInputValue (
  IN  UINT8                                  Type,
  IN  EFI_IFR_TYPE_VALUE                     *Value,
  OUT UINT64                                 *RetValue
  )
{
  switch (Type) {
  case EFI_IFR_TYPE_NUM_SIZE_8:
    *RetValue = Value->u8;
    break;

  case EFI_IFR_TYPE_NUM_SIZE_16:
    *RetValue = Value->u16;
    break;

  case EFI_IFR_TYPE_NUM_SIZE_32:
    *RetValue = Value->u32;
    break;

  case EFI_IFR_TYPE_NUM_SIZE_64:
    *RetValue = Value->u64;
    break;

  case EFI_IFR_TYPE_BOOLEAN:
    *RetValue = Value->b;
    break;

  case EFI_IFR_TYPE_STRING:
    *RetValue = Value->string;
    break;

  default:
    break;
  }
}

CHAR16 *mRssiStr[] = {
  L"*****",
  L"****-",
  L"***--",
  L"**---",
  L"*----",
  L"-----"
};

/**
  Genereate signal level base on RSSI value.

  The valid RSSI value from -128 ~ 0, higher is better.

  @param  RSSI          RSSI value.

  @retval String        Return the string about signal level.

**/
CHAR16 *
RssiToString (
  IN INT8               RSSI
  )
{
  ASSERT (RSSI >= -128 && RSSI <= 0);
  RSSI = -RSSI;
  RSSI /= 25;
  return mRssiStr[RSSI];
}

/**
  Genereate device name base on the local name or deivce address.

  @param[in]  LocalName       Device Name.
  @param[in]  BDAddr          Device Address.

  @retval     DeviceName   A Unicode string which contains the device name.

**/
CHAR16 *
GenerateDeviceName (
  IN CHAR8                      *LocalName,
  IN BLUETOOTH_LE_ADDRESS       *BDAddr
  )
{
  CHAR16    *DeviceName;
  UINTN     StringLen;

  if (LocalName[0] == '\0') {
    StringLen = (sizeof (BLUETOOTH_ADDRESS) * 3) * sizeof (CHAR16);
    DeviceName = AllocateZeroPool (StringLen);
    ASSERT (DeviceName != NULL);
    UnicodeSPrint (
      DeviceName,
      StringLen,
      L"%02x:%02x:%02x:%02x:%02x:%02x",
      (UINTN)BDAddr->Address[0],
      (UINTN)BDAddr->Address[1],
      (UINTN)BDAddr->Address[2],
      (UINTN)BDAddr->Address[3],
      (UINTN)BDAddr->Address[4],
      (UINTN)BDAddr->Address[5]
      );
  } else {
    StringLen = (sizeof (BLUETOOTH_ADDRESS) * 3 + AsciiStrnLenS (LocalName, MAX_DEVICE_NAME_LEN) + 4 ) * sizeof (CHAR16);
    DeviceName = AllocateZeroPool (StringLen);
    ASSERT (DeviceName != NULL);
    UnicodeSPrint (
      DeviceName,
      StringLen,
      L"%02x:%02x:%02x:%02x:%02x:%02x(%a)",
      (UINTN)BDAddr->Address[0],
      (UINTN)BDAddr->Address[1],
      (UINTN)BDAddr->Address[2],
      (UINTN)BDAddr->Address[3],
      (UINTN)BDAddr->Address[4],
      (UINTN)BDAddr->Address[5],
      LocalName
      );
  }

  return DeviceName;
}

/**
  Genereate device name base on the local name or deivce address.

  @param[in]  LocalName       Device Name.
  @param[in]  Address         Device Address.
  @param[in]  RSSI            Bluetooth RSSI.
  @param[in]  IsPaired        Whether this device is connected.

  @retval     DeviceName   A Unicode string which contains the device name.

**/
CHAR16 *
GenerateDeviceStatus (
  IN CHAR8                      *LocalName,
  IN BLUETOOTH_LE_ADDRESS       *Address,
  IN INT8                       RSSI,
  IN BOOLEAN                    IsPaired
  )
{
  CHAR16    *DeviceStatus;
  UINTN     StringLen;
  CHAR16    *DeviceName;
  //
  // Show name like "##:##:##:##:##:##(Name) [***--] "
  // if "##:##:##:##:##:##(Name)" length > MAX_DEVICE_NAME_LENGTH, cut it.
  //
  DeviceName = GenerateDeviceName (LocalName, Address);
  if (StrLen (DeviceName) > MAX_UI_DEVICE_NAME_FIELD) {
    DeviceName[MAX_UI_DEVICE_NAME_FIELD] = '\0';
  }

  //
  // Assume the device name is small than 45.
  // else we will cut the name to 45.
  //
  if (IsPaired) {
    StringLen = (MAX_UI_DEVICE_NAME_FIELD) * sizeof (CHAR16);
  } else {
    StringLen = (MAX_UI_DEVICE_NAME_FIELD + StrSize (L" [*****]")) * sizeof (CHAR16);
  }
  DeviceStatus = AllocateZeroPool (StringLen);
  ASSERT (DeviceStatus != NULL);

  if (IsPaired) {
    UnicodeSPrint (DeviceStatus, StringLen, L"%-*s", MAX_UI_DEVICE_NAME_FIELD, DeviceName);
  } else {
    UnicodeSPrint (DeviceStatus, StringLen, L"%-*s [%s]", MAX_UI_DEVICE_NAME_FIELD, DeviceName, RssiToString (RSSI));
  }

  FreePool (DeviceName);

  return DeviceStatus;
}

/**
  Updates the status of scanning remote Bluetooth devices on the scan page.

**/
VOID
UpdateScanMenu (
  VOID
  )
{
  VOID                             *ScanStartOpCodeHandle;
  VOID                             *ScanEndOpCodeHandle;
  EFI_IFR_GUID_LABEL               *ScanStartLabel;
  EFI_IFR_GUID_LABEL               *ScanEndLabel;

  //
  // Allocate space for creation of UpdateData Buffer
  //
  ScanStartOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (ScanStartOpCodeHandle != NULL);

  ScanEndOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (ScanEndOpCodeHandle != NULL);

  //
  // Create Hii Extend Label OpCode as the start opcode
  //
  ScanStartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (ScanStartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  ScanStartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  ScanStartLabel->Number       = LABEL_BLUETOOTH_SCAN;

  //
  // Create Hii Extend Label OpCode as the end opcode
  //
  ScanEndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (ScanEndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  ScanEndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  ScanEndLabel->Number       = LABEL_BLUETOOTH_SCAN_END;

  if (mBtConfigDevice->InScanning) {
    HiiCreateTextOpCode (
      ScanStartOpCodeHandle,
      STRING_TOKEN(STR_SCANNING_STRING),
      STRING_TOKEN(STR_SCANNING_STRING_HELP),
      0
      );
  } else {
    HiiCreateActionOpCode (
      ScanStartOpCodeHandle,
      KEY_SCAN_DEVICE_ID,
      STRING_TOKEN(STR_SCAN_STRING),
      STRING_TOKEN(STR_SCAN_STRING_HELP),
      EFI_IFR_FLAG_CALLBACK,
      0
      );
  }

  HiiUpdateForm (
    mBtConfigDevice->HiiHandle,
    &gHiiBluetoothConfigFormSetGuid,
    BLUETOOTH_DEVICE_MANAGEMENT_FORM,
    ScanStartOpCodeHandle,
    ScanEndOpCodeHandle
    );

  HiiFreeOpCodeHandle (ScanStartOpCodeHandle);
  HiiFreeOpCodeHandle (ScanEndOpCodeHandle);
}

/**
  Update Remote BT device info.

**/
EFI_STATUS
UpdateDevicePage (
  VOID
  )
{
  LIST_ENTRY                       *Link;
  BT_REMOTE_DEVICE_ATTRIBUTE       *RemoteDev;
  CHAR16                           *DeviceName;
  VOID                             *PairedStartOpCodeHandle;
  VOID                             *PairedEndOpCodeHandle;
  VOID                             *StartOpCodeHandle;
  EFI_IFR_GUID_LABEL               *PairedStartLabel;
  EFI_IFR_GUID_LABEL               *PairedEndLabel;
  VOID                             *AvailableStartOpCodeHandle;
  VOID                             *AvailableEndOpCodeHandle;
  EFI_IFR_GUID_LABEL               *AvailableStartLabel;
  EFI_IFR_GUID_LABEL               *AvailableEndLabel;
  EFI_STRING_ID                    Token;
  UINTN                            Index;
  BOOLEAN                          IsPaired;

  Index       = 0;
  //
  // Allocate space for creation of UpdateData Buffer
  //
  AvailableStartOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (AvailableStartOpCodeHandle != NULL);

  AvailableEndOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (AvailableEndOpCodeHandle != NULL);

  //
  // Create Hii Extend Label OpCode as the start opcode
  //
  AvailableStartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (AvailableStartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  AvailableStartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  AvailableStartLabel->Number       = LABEL_BLUETOOTH_AVAILABLE_DEVICE_LIST;

  //
  // Create Hii Extend Label OpCode as the end opcode
  //
  AvailableEndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (AvailableEndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  AvailableEndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  AvailableEndLabel->Number       = LABEL_BLUETOOTH_AVAILABLE_END;

  //
  // Allocate space for creation of UpdateData Buffer
  //
  PairedStartOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (PairedStartOpCodeHandle != NULL);

  PairedEndOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (PairedEndOpCodeHandle != NULL);

  //
  // Create Hii Extend Label OpCode as the start opcode
  //
  PairedStartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (PairedStartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  PairedStartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  PairedStartLabel->Number       = LABEL_BLUETOOTH_PAIRED_DEVICE_LIST;

  //
  // Create Hii Extend Label OpCode as the end opcode
  //
  PairedEndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (PairedEndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  PairedEndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  PairedEndLabel->Number       = LABEL_BLUETOOTH_PAIRED_END;

  //
  // Lock device list during updating scan result page.
  // Device status maybe update by LinkConnCompCallback.
  //
  EfiAcquireLock (&mBtConfigDevice->DeviceListLock);

  Link  = GetFirstNode (&mBtConfigDevice->RemoteDeviceList);
  while (!IsNull (&mBtConfigDevice->RemoteDeviceList, Link)) {
    RemoteDev = BT_REMOTE_DEVICE_FROM_LINK (Link);
    Link = GetNextNode (&mBtConfigDevice->RemoteDeviceList, Link);

    IsPaired = ((RemoteDev->RemoteDeviceState & EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED) != 0)? TRUE: FALSE;

    if (IsValidBleAddress(&RemoteDev->IDAddr)) {
      DeviceName = GenerateDeviceStatus((CHAR8 *)(RemoteDev->LocalName), &RemoteDev->IDAddr, RemoteDev->RSSI, IsPaired);
    } else {
      DeviceName = GenerateDeviceStatus((CHAR8 *)(RemoteDev->LocalName), &RemoteDev->AdvAddr, RemoteDev->RSSI, IsPaired);
    }

    Token = HiiSetString (mBtConfigDevice->HiiHandle, 0, DeviceName, NULL);

    if (IsPaired) {
      StartOpCodeHandle = PairedStartOpCodeHandle;
      HiiCreateTextOpCode (
          StartOpCodeHandle,
          Token,
          0,
          0
          );
    } else {
      StartOpCodeHandle = AvailableStartOpCodeHandle;
      HiiCreateGotoOpCode (
        StartOpCodeHandle,
        BLUETOOTH_REMOTE_DEVICE_FORM,
        Token,
        STRING_TOKEN (STR_GOTO_REMOTE_DEVICE_HELP),
        EFI_IFR_FLAG_CALLBACK,
        (EFI_QUESTION_ID)(REMOTE_DEVICE_OFFSET + Index)
        );
    }

    if ((RemoteDev->RemoteDeviceState & EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED) != 0) {
      HiiCreateActionOpCode (
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(DISCONNECT_DEVICE_OFFSET + Index),
        STRING_TOKEN (STR_DEVICE_ACTION_NOT_CONNECT),
        STRING_TOKEN (STR_DEVICE_ACTION_NOT_CONNECT_HELP),
        EFI_IFR_FLAG_CALLBACK,
        0
        );
    } else {
      HiiCreateActionOpCode (
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(CONNECT_DEVICE_OFFSET + Index),
        STRING_TOKEN (STR_DEVICE_ACTION_CONNECT),
        STRING_TOKEN (STR_DEVICE_ACTION_CONNECT_HELP),
        EFI_IFR_FLAG_CALLBACK,
        0
        );
    }

    if (IsPaired) {
      HiiCreateActionOpCode (
        StartOpCodeHandle,
        (EFI_QUESTION_ID)(DELETE_DEVICE_OFFSET + Index),
        STRING_TOKEN (STR_DEVICE_ACTION_DELETE),
        STRING_TOKEN (STR_DEVICE_ACTION_DELETE_HELP),
        EFI_IFR_FLAG_CALLBACK,
        0
        );
    }

    HiiCreateSubTitleOpCode (
      StartOpCodeHandle,
      STRING_TOKEN (STR_NULL_STRING),
      0,
      0,
      0);

    Index++;
  }
  EfiReleaseLock (&mBtConfigDevice->DeviceListLock);

  HiiUpdateForm (
    mBtConfigDevice->HiiHandle,
    &gHiiBluetoothConfigFormSetGuid,
    BLUETOOTH_DEVICE_MANAGEMENT_FORM,
    PairedStartOpCodeHandle,
    PairedEndOpCodeHandle
    );

  HiiUpdateForm (
    mBtConfigDevice->HiiHandle,
    &gHiiBluetoothConfigFormSetGuid,
    BLUETOOTH_DEVICE_MANAGEMENT_FORM,
    AvailableStartOpCodeHandle,
    AvailableEndOpCodeHandle
    );

  HiiFreeOpCodeHandle (PairedStartOpCodeHandle);
  HiiFreeOpCodeHandle (PairedEndOpCodeHandle);
  HiiFreeOpCodeHandle (AvailableStartOpCodeHandle);
  HiiFreeOpCodeHandle (AvailableEndOpCodeHandle);

  return EFI_SUCCESS;
}

/**
  Displays a popup window to indicate the result of a connect/disconnect
  operation.


  @param[in]  RemoteDev            A pointer to the BT_REMOTE_DEVICE_ATTRIBUTE
                                   structure that specifies the target device.
  @param[in]  ErrorType            Input the error type.

**/
VOID
ConnectResultPopup (
  IN BT_REMOTE_DEVICE_ATTRIBUTE  *RemoteDev,
  IN EFI_BLUETOOTH_ERROR_TYPE    ErrorType
  )
{
  EFI_INPUT_KEY                 Key;
  CHAR16                        *StringBuffer1;
  CHAR16                        *StringBuffer2;
  CHAR16                        *DeviceName;

  StringBuffer1 = AllocateZeroPool (MAX_STRING_LEN * sizeof (CHAR16));
  ASSERT (StringBuffer1 != NULL);
  StringBuffer2 = AllocateZeroPool (MAX_STRING_LEN * sizeof (CHAR16));
  ASSERT (StringBuffer2 != NULL);

  if (IsValidBleAddress (&RemoteDev->IDAddr)) {
    DeviceName = GenerateDeviceName ((CHAR8 *)RemoteDev->LocalName, &RemoteDev->IDAddr);
  } else {
    DeviceName = GenerateDeviceName ((CHAR8 *)RemoteDev->LocalName, &RemoteDev->AdvAddr);
  }

  switch (ErrorType) {
  case ResultExceedMaxPairedDevices:
    UnicodeSPrint (
      StringBuffer1,
      MAX_STRING_LEN,
      L" Number of paired devices cannot be larger than %d! ",
      EFI_BLUETOOTH_LE_MAX_BONDED_DEV
      );
    break;

  case ResultConnectFail:
    UnicodeSPrint (
      StringBuffer1,
      MAX_STRING_LEN,
      L" Connect to %s fail! ",
      DeviceName
      );
    break;

  case ResultDisconnectFail:
    UnicodeSPrint (
      StringBuffer1,
      MAX_STRING_LEN,
      L" Disconnect to %s fail! ",
      DeviceName
      );
    break;

  default:
    break;
  }

  StrCpyS (StringBuffer2, MAX_STRING_LEN, L" Press Enter to continue ");

  //
  // Popup a info to notice user
  //
  do {
    CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, StringBuffer1, StringBuffer2, NULL);
  } while (Key.UnicodeChar != CHAR_CARRIAGE_RETURN);

  FreePool (StringBuffer1);
  FreePool (StringBuffer2);
  FreePool (DeviceName);
}

/**
  Displays a popup window to get the user's choice on a authorization request.

  @param[in]  IndicatorString  Additional string that will be displayed on the
                               popup window.

  @retval  0  User rejects the authorization request.
  @retval  1  User approves the authorization request.

**/
UINT8
HandleAuthorizationRequestEvent (
  IN CHAR16          *IndicatorString
  )
{
  EFI_INPUT_KEY                 Key;
  CHAR16                        *StringBuffer2;
  CHAR16                        *StringBuffer3;
  CHAR16                        *StringBuffer4;
  CHAR16                        ApproveResponse;
  CHAR16                        RejectResponse;

  ApproveResponse = L'Y';
  RejectResponse  = L'N';

  StringBuffer2 = AllocateZeroPool (MAX_STRING_LEN * sizeof (CHAR16));
  ASSERT (StringBuffer2 != NULL);
  StringBuffer3 = AllocateZeroPool (MAX_STRING_LEN * sizeof (CHAR16));
  ASSERT (StringBuffer3 != NULL);

  UnicodeSPrint (
    StringBuffer2,
    StrSize (L"Approve it, please input <Y>"),
    L"Approve it, please input <Y>"
    );

  UnicodeSPrint (
    StringBuffer3,
    StrSize (L"Reject it, please input <N>"),
    L"Reject it, please input <N>"
    );

  StringBuffer4 = L"";


  //
  // Popup a menu to notice user
  //
  do {
    CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, IndicatorString, StringBuffer4, StringBuffer2, StringBuffer3, StringBuffer4, NULL);
  }while (
      ((Key.UnicodeChar | UPPER_LOWER_CASE_OFFSET) != (ApproveResponse | UPPER_LOWER_CASE_OFFSET)) &&
      ((Key.UnicodeChar | UPPER_LOWER_CASE_OFFSET) != (RejectResponse | UPPER_LOWER_CASE_OFFSET))
    );

  FreePool (StringBuffer2);
  FreePool (StringBuffer3);

  if ((Key.UnicodeChar | UPPER_LOWER_CASE_OFFSET) == (ApproveResponse | UPPER_LOWER_CASE_OFFSET)) {
    return 1;
  } else {
    return 0;
  }
}


/**
  Count the storage space of a Unicode string.

  This function handles the Unicode string with NARROW_CHAR
  and WIDE_CHAR control characters. NARROW_HCAR and WIDE_CHAR
  does not count in the resultant output. If a WIDE_CHAR is
  hit, then 2 Unicode character will consume an output storage
  space with size of CHAR16 till a NARROW_CHAR is hit.

  @param String          The input string to be counted.
  @param LimitLen        Whether need to limit the string length.
  @param MaxWidth        The max length this function supported.
  @param Offset          The max index of the string can be show out.

  @return Storage space for the input string.

**/
UINTN
GetStringWidth (
  IN  CHAR16               *String,
  IN  BOOLEAN              LimitLen,
  IN  UINTN                MaxWidth,
  OUT UINTN                *Offset
  )
{
  UINTN Index;
  UINTN Count;
  UINTN IncrementValue;

  if (String == NULL) {
    return 0;
  }

  Index           = 0;
  Count           = 0;
  IncrementValue  = 1;

  do {
    //
    // Advance to the null-terminator or to the first width directive
    //
    for (;(String[Index] != NARROW_CHAR) && (String[Index] != WIDE_CHAR) && (String[Index] != 0); Index++) {
      Count = Count + IncrementValue;

      if (LimitLen && Count > MaxWidth) {
        break;
      }
    }

    //
    // We hit the null-terminator, we now have a count
    //
    if (String[Index] == 0) {
      break;
    }

    if (LimitLen && Count > MaxWidth) {
      *Offset = Index;
      break;
    }

    //
    // We encountered a narrow directive - strip it from the size calculation since it doesn't get printed
    // and also set the flag that determines what we increment by.(if narrow, increment by 1, if wide increment by 2)
    //
    if (String[Index] == NARROW_CHAR) {
      //
      // Skip to the next character
      //
      Index++;
      IncrementValue = 1;
    } else {
      //
      // Skip to the next character
      //
      Index++;
      IncrementValue = 2;
    }
  } while (String[Index] != 0);

  return Count * sizeof (CHAR16);
}

/**
  Draws a dialog box to the console output device specified by
  ConOut defined in the EFI_SYSTEM_TABLE and waits for a keystroke
  from the console input device specified by ConIn defined in the
  EFI_SYSTEM_TABLE.

  If there are no strings in the variable argument list, then ASSERT().
  If all the strings in the variable argument list are empty, then ASSERT().

  @param[in]  Attribute   Specifies the foreground and background color of the popup.
  @param[in]  ...         The variable argument list that contains pointers to Null-
                          terminated Unicode strings to display in the dialog box.
                          The variable argument list is terminated by a NULL.

**/
VOID
EFIAPI
PopUpPasskey (
  IN  UINTN          Attribute,
  ...
  )
{
  VA_LIST                          Args;
  EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL  *ConOut;
  EFI_SIMPLE_TEXT_OUTPUT_MODE      SavedConsoleMode;
  UINTN                            Columns;
  UINTN                            Rows;
  UINTN                            Column;
  UINTN                            Row;
  UINTN                            NumberOfLines;
  UINTN                            MaxLength;
  CHAR16                           *String;
  UINTN                            Length;
  CHAR16                           *Line;
  UINTN                            EventIndex;
  CHAR16                           *TmpString;

  //
  // Determine the length of the longest line in the popup and the the total
  // number of lines in the popup
  //
  VA_START (Args, Attribute);
  MaxLength = 0;
  NumberOfLines = 0;
  while ((String = VA_ARG (Args, CHAR16 *)) != NULL) {
    MaxLength = MAX (MaxLength, GetStringWidth (String, FALSE, 0, NULL) / 2);
    NumberOfLines++;
  }
  VA_END (Args);

  //
  // If the total number of lines in the popup is zero, then ASSERT()
  //
  ASSERT (NumberOfLines != 0);

  //
  // If the maximum length of all the strings is zero, then ASSERT()
  //
  ASSERT (MaxLength != 0);

  //
  // Cache a pointer to the Simple Text Output Protocol in the EFI System Table
  //
  ConOut = gST->ConOut;

  //
  // Save the current console cursor position and attributes
  //
  CopyMem (&SavedConsoleMode, ConOut->Mode, sizeof (SavedConsoleMode));

  //
  // Retrieve the number of columns and rows in the current console mode
  //
  ConOut->QueryMode (ConOut, SavedConsoleMode.Mode, &Columns, &Rows);

  //
  // Disable cursor and set the foreground and background colors specified by Attribute
  //
  ConOut->EnableCursor (ConOut, FALSE);
  ConOut->SetAttribute (ConOut, Attribute);

  //
  // Limit NumberOfLines to height of the screen minus 3 rows for the box itself
  //
  NumberOfLines = MIN (NumberOfLines, Rows - 3);

  //
  // Limit MaxLength to width of the screen minus 2 columns for the box itself
  //
  MaxLength = MIN (MaxLength, Columns - 2);

  //
  // Compute the starting row and starting column for the popup
  //
  Row    = (Rows - (NumberOfLines + 3)) / 2;
  Column = (Columns - (MaxLength + 2)) / 2;

  //
  // Allocate a buffer for a single line of the popup with borders and a Null-terminator
  //
  Line = AllocateZeroPool ((MaxLength + 3) * sizeof (CHAR16));
  ASSERT (Line != NULL);

  //
  // Draw top of popup box
  //
  SetMem16 (Line, (MaxLength + 2) * 2, BOXDRAW_HORIZONTAL);
  Line[0]             = BOXDRAW_DOWN_RIGHT;
  Line[MaxLength + 1] = BOXDRAW_DOWN_LEFT;
  Line[MaxLength + 2] = L'\0';
  ConOut->SetCursorPosition (ConOut, Column, Row++);
  ConOut->OutputString (ConOut, Line);

  //
  // Draw middle of the popup with strings
  //
  VA_START (Args, Attribute);
  while ((String = VA_ARG (Args, CHAR16 *)) != NULL && NumberOfLines > 0) {
    SetMem16 (Line, (MaxLength + 2) * 2, L' ');
    Line[0]             = BOXDRAW_VERTICAL;
    Line[MaxLength + 1] = BOXDRAW_VERTICAL;
    Line[MaxLength + 2] = L'\0';
    ConOut->SetCursorPosition (ConOut, Column, Row);
    ConOut->OutputString (ConOut, Line);
    Length = GetStringWidth (String, FALSE, 0, NULL) / 2;
    if (Length <= MaxLength) {
      //
      // Length <= MaxLength
      //
      ConOut->SetCursorPosition (ConOut, Column + 1 + (MaxLength - Length) / 2, Row++);
      ConOut->OutputString (ConOut, String);
    } else {
      //
      // Length > MaxLength
      //
      GetStringWidth (String, TRUE, MaxLength, &Length);
      TmpString = AllocateZeroPool ((Length + 1) * sizeof (CHAR16));
      ASSERT (TmpString != NULL);
      StrnCpyS (TmpString, Length + 1, String, Length - 3);
      StrCatS (TmpString, Length + 1, L"...");

      ConOut->SetCursorPosition (ConOut, Column + 1, Row++);
      ConOut->OutputString (ConOut, TmpString);
      FreePool (TmpString);
    }
    NumberOfLines--;
  }
  VA_END (Args);

  //
  // Draw bottom of popup box
  //
  SetMem16 (Line, (MaxLength + 2) * 2, BOXDRAW_HORIZONTAL);
  Line[0]             = BOXDRAW_UP_RIGHT;
  Line[MaxLength + 1] = BOXDRAW_UP_LEFT;
  Line[MaxLength + 2] = L'\0';
  ConOut->SetCursorPosition (ConOut, Column, Row++);
  ConOut->OutputString (ConOut, Line);

  //
  // Free the allocated line buffer
  //
  FreePool (Line);

  //
  // Restore the cursor visibility, position, and attributes
  //
  ConOut->EnableCursor      (ConOut, SavedConsoleMode.CursorVisible);
  ConOut->SetCursorPosition (ConOut, SavedConsoleMode.CursorColumn, SavedConsoleMode.CursorRow);
  ConOut->SetAttribute      (ConOut, SavedConsoleMode.Attribute);

  //
  // Wait for a event.
  //
  gBS->WaitForEvent (1, &mBtConfigDevice->PasskeyInputEvent, &EventIndex);
}

/**
  Displays a window to inform user of the passkey information.

  @param[in]  IndicatorString  Additional string that will be displayed on the
                               window.
  @param[in]  DataSize         The size of Data in bytes.
  @param[in]  Data             The passkey data.

**/
VOID
HandlePasskeyReadyEvent (
  IN CHAR16                                 *IndicatorString,
  IN UINTN                                  DataSize,
  IN VOID                                   *Data
  )
{
  CHAR16                        *StringBuffer2;
  UINT32                        Passkey;
  UINTN                         StringLength;

  CopyMem(&Passkey, Data, DataSize);

  StringLength = StrLen (L"Please enter passkey ") + 6 + StrLen (L" in the other device") + 1;

  StringBuffer2 = AllocateZeroPool (StringLength * sizeof (CHAR16));
  ASSERT (StringBuffer2 != NULL);

  UnicodeSPrint (
    StringBuffer2,
    StringLength * sizeof (CHAR16),
    L"Please enter passkey %06d in the other device",
    Passkey
    );

  //
  // Popup the passkey info to let user know.
  //
  PopUpPasskey (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, IndicatorString, StringBuffer2, NULL);

  FreePool (StringBuffer2);
}

/**
  Get password input from the popup windows, and unlock the device.

  @param[in]  IndicatorString  Not used.
  @param[in]  DataSize         Not used.
  @param[in]  Data             Not used.

  @retval  0       No passkey is input.
  @retval  UINT32  The passkey entered by the user.

**/
UINT32
HandlePasskeyRequestEvent (
  IN CHAR16                                 *IndicatorString,
  IN UINTN                                  DataSize,
  IN VOID                                   *Data
  )
{
  EFI_INPUT_KEY                InputKey;
  UINTN                        InputLength;
  CHAR16                       Unicode[MAX_PASSKEY_SIZE + 1];
  CHAR16                       *StringBuffer1;
  CHAR16                       *StringBuffer2;
  CHAR16                       *StringBuffer3;
  CHAR16                       *StringBuffer4;
  UINT32                       Passkey;

  Print(L"Please enter passkey displayed on the other device");

  StringBuffer2 = L"Please enter passkey displayed on the other device";
  StringBuffer4 = L"";
  StringBuffer3 = L"Press <O> for OK";
  StringBuffer1 = L"Press <C> for Cancel";

  ZeroMem(Unicode, sizeof(Unicode));
  InputLength = 0;
  Unicode[InputLength] = '_';

  while (TRUE) {
    CreatePopUp(
        EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE,
        &InputKey,
        StringBuffer2,
        StringBuffer4,
        Unicode,
        StringBuffer4,
        StringBuffer3,
        StringBuffer1,
        NULL
    );

    //
    // Check key.
    //
    if (InputKey.ScanCode == SCAN_NULL) {
      if (InputKey.UnicodeChar == CHAR_BACKSPACE) {
        if (InputLength > 0) {
          Unicode[InputLength] = 0;
          InputLength--;
        }
      } else if ((InputKey.UnicodeChar == 'O') || (InputKey.UnicodeChar == 'o')) {
        //
        // pass key finished
        //

        //
        // Add the null terminator.
        //
        Unicode[InputLength] = 0;
        InputLength++;
        break;
      } else if ((InputKey.UnicodeChar == 'C') || (InputKey.UnicodeChar == 'c')) {
        break;
      } else {
        if (InputLength < MAX_PASSKEY_SIZE) {
          //
          // add Next key entry
          //
          Unicode[InputLength] = InputKey.UnicodeChar;
          InputLength++;
          if (InputLength == MAX_PASSKEY_SIZE) {
            //
            // Add the null terminator.
            //
            Unicode[InputLength] = 0;
          } else {
            Unicode[InputLength] = '_';
          }
        }
      }
    }
  }

  if ((InputLength == 0) || (InputKey.UnicodeChar == 'C') || (InputKey.UnicodeChar == 'c')) {
    return 0;
  }

  Passkey = (UINT32) StrDecimalToUintn (Unicode);
  ZeroMem(Unicode, sizeof(Unicode)); // Clear the stack

  return Passkey;
}

/**
  Displays a popup window for user to confirm whether the passkey is displayed
  on the remote device.

  @param[in]  IndicatorString  Additional string that will be displayed on the
                               popup window.
  @param[in]  DataSize         The size of Data in bytes.
  @param[in]  Data             The passkey data.

  @retval  0  The shown passkey is different from the one displayed on the
              remote device.
  @retval  1  The shown passkey is the same as the one displayed on the remote
              device.

**/
UINT8
HandleNumericComparisonEvent (
  IN CHAR16                                 *IndicatorString,
  IN UINTN                                  DataSize,
  IN VOID                                   *Data
  )
{
  EFI_INPUT_KEY                 Key;
  CHAR16                        *StringBuffer1;
  CHAR16                        *StringBuffer2;
  CHAR16                        *StringBuffer3;
  CHAR16                        *StringBuffer4;
  UINT32                        Passkey;
  UINTN                         StringLength;
  CHAR16                        ConfirmResponse;
  CHAR16                        RejectResponse;

  CopyMem(&Passkey, Data, DataSize);

  StringLength = StrLen (L"Is ") + 6 + StrLen (L" being displayed on the other device (0/1)?  ");

  StringBuffer2 = AllocateZeroPool (MAX_STRING_LEN * sizeof (CHAR16));
  ASSERT (StringBuffer2 != NULL);

  UnicodeSPrint (
    StringBuffer2,
    StringLength * sizeof (CHAR16),
    L"Is %06d being displayed on the other device (0/1)?  ",
    Passkey
    );

  StringBuffer4 = L"";

  ConfirmResponse = L'Y';
  RejectResponse  = L'N';

  StringBuffer1 = AllocateZeroPool (MAX_STRING_LEN * sizeof (CHAR16));
  ASSERT (StringBuffer2 != NULL);
  StringBuffer3 = AllocateZeroPool (MAX_STRING_LEN * sizeof (CHAR16));
  ASSERT (StringBuffer3 != NULL);

  UnicodeSPrint (
    StringBuffer1,
    StrSize (L"If Yes, please input <Y>"),
    L"If Yes, please input <Y>"
    );

  UnicodeSPrint (
    StringBuffer3,
    StrSize (L"If No, please input <N>"),
    L"f No, please input <N>"
    );

  //
  // Popup a menu to notice user
  //
  do {
    CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, IndicatorString, StringBuffer2, StringBuffer4, StringBuffer1, StringBuffer3, StringBuffer4, NULL);
  }while (
      ((Key.UnicodeChar | UPPER_LOWER_CASE_OFFSET) != (ConfirmResponse | UPPER_LOWER_CASE_OFFSET)) &&
      ((Key.UnicodeChar | UPPER_LOWER_CASE_OFFSET) != (RejectResponse | UPPER_LOWER_CASE_OFFSET))
    );

  FreePool (StringBuffer2);
  FreePool (StringBuffer3);

  if ((Key.UnicodeChar | UPPER_LOWER_CASE_OFFSET) == (ConfirmResponse | UPPER_LOWER_CASE_OFFSET)) {
    return 1;
  } else {
    return 0;
  }
}

/**
  The callback function for SMP.

  @param[in]  This           Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                             instance.
  @param[in]  Context        Data passed into callback function. This is
                             optional parameter and may be NULL.
  @param[in]  BDAddr         Remote BluetoothLE device address.
  @param[in]  EventDataType  Event data type in
                             EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE.
  @param[in]  DataSize       Indicates the size, in bytes, of the data buffer
                             specified by Data.
  @param[in]  Data           A pointer to the buffer of data.

  @retval  EFI_SUCCESS  The callback function complete successfully.
  @retval  Other        A value from other functions.

**/
EFI_STATUS
EFIAPI
SmpCallback (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL       *This,
  IN VOID                                   *Context,
  IN BLUETOOTH_LE_ADDRESS                   *BDAddr,
  IN EFI_BLUETOOTH_LE_SMP_EVENT_DATA_TYPE   EventDataType,
  IN UINTN                                  DataSize,
  IN VOID                                   *Data
  )
{
  UINT8                      Auth;
  UINT32                     Passkey;
  CHAR16                     *StringBuffer;
  UINTN                      StringLength;
  BT_REMOTE_DEVICE_ATTRIBUTE *RemoteDev;
  CHAR16                     *DevName;
  EFI_STATUS                 Status = EFI_SUCCESS;

  if (mBtConfigDevice->ConnectState != StateConnecting) {
    DEBUG ((DEBUG_ERROR, "BtCfgDxe :: SmpCallback trigged not during connecting!!!"));
  }

  EfiAcquireLock (&mBtConfigDevice->DeviceListLock);

  RemoteDev = LocateDevInList (BDAddr->Address, EfiAnyAddressType);
  if (RemoteDev == NULL) {
    DEBUG ((EFI_D_ERROR, "BtCfgDxe :: SmpCallback : Could not found the input device in the list!\n"));
    EfiReleaseLock (&mBtConfigDevice->DeviceListLock);

    DumpRemoteDeviceList ();

    return EFI_SUCCESS;
  }
  EfiReleaseLock (&mBtConfigDevice->DeviceListLock);

  if (IsValidBleAddress(&RemoteDev->IDAddr)) {
    DevName = GenerateDeviceName((CHAR8 *)RemoteDev->LocalName, &RemoteDev->IDAddr);
  } else {
    DevName = GenerateDeviceName((CHAR8 *)RemoteDev->LocalName, &RemoteDev->AdvAddr);
  }

  DEBUG ((EFI_D_INFO, "BtCfgDxe :: Paired reqeust from  %s, Event = %u \n", DevName, EventDataType));

  StringBuffer = AllocateZeroPool (MAX_STRING_LEN * sizeof (CHAR16));
  ASSERT (StringBuffer != NULL);

  StringLength = StrSize (L"Pairing Request from ") + StrSize (DevName);

  UnicodeSPrint (StringBuffer, StringLength, L"Pairing Request from %s\n", DevName);

  FreePool (DevName);

  switch(EventDataType)
  {
  case EfiBluetoothSmpAuthorizationRequestEvent:
    Auth = HandleAuthorizationRequestEvent (StringBuffer);
    Data = &Auth;
    DataSize = sizeof(Auth);
    break;
  case EfiBluetoothSmpPasskeyReadyEvent:
    HandlePasskeyReadyEvent (StringBuffer, DataSize, Data);
    DataSize = 0;
    Data = 0;
    break;
  case EfiBluetoothSmpPasskeyRequestEvent:
    Passkey = HandlePasskeyRequestEvent (StringBuffer, DataSize, Data);
    Data = &Passkey;
    DataSize = sizeof(Passkey);
    break;
  case EfiBluetoothSmpNumericComparisonEvent:
    Auth = HandleNumericComparisonEvent (StringBuffer, DataSize, Data);
    Data = &Auth;
    DataSize = sizeof(Auth);
    break;
  case EfiBluetoothSmpOOBDataRequestEvent:
    CopyMem(&Passkey, Data, DataSize);
    DEBUG ((EFI_D_INFO, "EfiBlutoothSmpOOBDataRequestEvent is not supported yet!\n"));
    DataSize = 0;
    Data = 0;
    break;
  }

  if (DataSize != 0) {
    Status = mBtConfigDevice->BluetoothLeConfig->SendSmpAuthData(This, BDAddr, EventDataType, DataSize, Data);
  }

  Passkey = 0; // Clear the stack entry
  return Status;
}

/**
  Check whether the input device address is the current bonding one.


  @param[in]  Address        Remote BluetoothLE device address.

**/
BOOLEAN
IsCurrentBondingDevice (
  IN BLUETOOTH_LE_ADDRESS        *Address
  )
{
  if (mBtConfigDevice->CurrentBondingDev == NULL) {
    return FALSE;
  }

  if (mBtConfigDevice->CurrentBondingIDAddress &&
      CompareMem (Address->Address, mBtConfigDevice->CurrentBondingDev->IDAddr.Address, sizeof (Address->Address)) == 0) {
    return TRUE;
  }

  if (!mBtConfigDevice->CurrentBondingIDAddress &&
      CompareMem (Address->Address, mBtConfigDevice->CurrentBondingDev->AdvAddr.Address, sizeof (Address->Address)) == 0) {
    return TRUE;
  }

  return FALSE;
}

/**
  The callback function to hook connect complete event.

  @param[in]  This            Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                              instance.
  @param[in]  Context         Data passed into callback function. This is
                              optional parameter and may be NULL.
  @param[in]  CallbackType    The value defined in
                              EFI_BLUETOOTH_CONNECT_COMPLETE_CALLBACK_TYPE.
  @param[in]  Address         Remote BluetoothLE device address.
                              Call in with same address when user call connect
                              or disconnect.
  @param[in]  InputBuffer     A pointer to the buffer of data that is input from callback caller.
  @param[in]  InputBufferSize Indicates the size, in bytes, of the data buffer specified by InputBuffer.

  @retval  EFI_SUCCESS  The callback function complete successfully.

**/
EFI_STATUS
EFIAPI
LinkConnCompCallback (
  IN  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL                 *This,
  IN  VOID                                             *Context,
  IN  EFI_BLUETOOTH_CONNECT_COMPLETE_CALLBACK_TYPE     CallbackType,
  IN  BLUETOOTH_LE_ADDRESS                             *Address,
  IN  VOID                                             *InputBuffer,
  IN  UINTN                                            InputBufferSize
 )
{
  BT_REMOTE_DEVICE_ATTRIBUTE  *RemoteDev;
  BT_LE_REMOTE_DEV_STORAGE    *PairedDevData;
  UINTN                       Index;

  DEBUG ((EFI_D_INFO, "LeConnCompCallback - %d\n", CallbackType));
  DEBUG ((EFI_D_INFO, "LeConnCompCallback - BDAddr %02x:%02x:%02x:%02x:%02x:%02x Type %02x\n",
                              Address->Address[0], Address->Address[1],
                              Address->Address[2], Address->Address[3],
                              Address->Address[4], Address->Address[5],
                              Address->Type
                              ));
  EfiAcquireLock (&mBtConfigDevice->DeviceListLock);

  RemoteDev = LocateDevInList (Address->Address, EfiAnyAddressType);
  if (RemoteDev == NULL) {
    DEBUG ((EFI_D_ERROR, "BtCfgDxe :: ConnCompCallback not found the input device in the list!\n"));
    EfiReleaseLock (&mBtConfigDevice->DeviceListLock);

    DumpRemoteDeviceList ();

    return EFI_SUCCESS;
  }

  switch (CallbackType) {
  case EfiBluetoothConnCallbackTypeDisconnected:
    RemoteDev->RemoteDeviceState &= ~EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED;
    //
    // If not trigged by the device which is connecting, just skip.
    //
    if (mBtConfigDevice->ConnectState == StateConnecting) {
      if (IsCurrentBondingDevice (Address)) {
        PERF_END (NULL, "Connect", "Bluetooth", 0);
        //
        // IsValidBleAddress(&RemoteDev->IDAddr) == TRUE means this device has called LeSmpSetDataCallback
        // to update mBtConfigDevice->PairedDevData[Index]. Check whether need to clean it.
        //
        if (IsValidBleAddress(&RemoteDev->IDAddr)) {
          PairedDevData = LocateDevInGlobalData(&RemoteDev->IDAddr, &Index);
          ASSERT (PairedDevData != NULL);
          //
          // mBtConfigDevice->PairedDevDataSaved[Index] == TRUE means this device is connected before, now
          // is reconnecting, should not clear mBtConfigDevice->PairedDevData[Index] if connect failed now.
          // Else means this device is first time connecting and return failed, need to clean the maintained
          // mBtConfigDevice->PairedDevData[Index].
          //
          if (!mBtConfigDevice->PairedDevDataSaved[Index]) {
            DeletePairedDevice (&RemoteDev->IDAddr, FALSE);
          }
        } else {
          DEBUG ((DEBUG_INFO, "BtCfgDxe :: Identify address is invalid, not delete Paired device data!\n"));
        }
      }
    }
    break;

  case EfiBluetoothConnCallbackTypeConnected:
    RemoteDev->RemoteDeviceState |= EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED;
    RemoteDev->AdvAddr.Type = Address->Type;
    break;

  case EfiBluetoothConnCallbackTypeEncrypted:
    RemoteDev->RemoteDeviceState |= EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED;
    RemoteDev->RemoteDeviceState |= EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED;
    //
    // If not trigged by the device which is connecting, just return.
    //
    if (mBtConfigDevice->ConnectState == StateConnecting) {
      if (IsCurrentBondingDevice (Address)) {
        ASSERT (IsValidBleAddress(&RemoteDev->IDAddr));
        //
        // Update Remote device name from local database
        //
        PairedDevData = LocateDevInGlobalData(&RemoteDev->IDAddr, &Index);
        ASSERT (PairedDevData != NULL);
        ZeroMem(PairedDevData->PeerName, sizeof(PairedDevData->PeerName));
        CopyMem(PairedDevData->PeerName, RemoteDev->LocalName, MIN(sizeof(PairedDevData->PeerName) - 1, sizeof(RemoteDev->LocalName)));

        SavePairedDevice (&RemoteDev->IDAddr);

        gBS->SignalEvent (mBtConfigDevice->PasskeyInputEvent);
      }
    }
    gBS->SignalEvent (mBtConfigDevice->ConnectDriverEvent);
    break;

  default:
    break;
  }

  EfiReleaseLock (&mBtConfigDevice->DeviceListLock);

  //
  // Call LinkConnCompCallback has two cases:
  // 1. User requests connect action trigged   2. iLE stack auto reconnection trigged.
  // Before user request connect trigges this function, iLE stack auto reconnection may trigges this function,
  // in this case, we should not update mBtConfigDevice->BluetoothPhaseType. Base on
  // mBtConfigDevice->CurBondingDevAddr to decide whether need to update it.
  //
  if (IsCurrentBondingDevice (Address)) {
    mBtConfigDevice->ConnectState = StateIdle;
  }

  //
  // Fake found new device event to let the form refresh the connect status.
  //
  mBtConfigDevice->FoundNewDevice = TRUE;
  gBS->SignalEvent (mBtConfigDevice->RefreshRemoteDevEvent);

  return EFI_SUCCESS;
}

/**
  Find the remote device base on the index.

  @param  Offset    The device index in the list.

  @retval The remote device info.

**/
BT_REMOTE_DEVICE_ATTRIBUTE *
GetRemoteDevice (
  IN UINTN      Offset
  )
{
  LIST_ENTRY                       *Link;
  UINTN                            Index;

  Index = 0;
  Link  = GetFirstNode (&mBtConfigDevice->RemoteDeviceList);
  while (!IsNull (&mBtConfigDevice->RemoteDeviceList, Link)) {
    if (Index == Offset) {
      break;
    }

    Link = GetNextNode (&mBtConfigDevice->RemoteDeviceList, Link);
    Index ++;
  }

  if (IsNull (&mBtConfigDevice->RemoteDeviceList, Link)) {
    return NULL;
  }

  return BT_REMOTE_DEVICE_FROM_LINK (Link);
}

/**
  To find the service name based on the ServiceUuid.
  The returned service name is allocated through AllocateZeroPoolreturn function,
  caller needs to free it.

  @param  AdvertisementData     Point to the AdvertisementData.

  @retval  A Unicode string which contains the service name.

**/
CHAR16*
UuidToName (
  IN UINT8                *AdvertisementData
  )
{
  UINT16                  Uuid16;
  UINTN                   Index;
  UINTN                   StringLen;
  CHAR16                  *UuidName;
  CHAR16                  *DisplayName;

  //
  // Skip the length (1 byte) and type (1 byte)
  // then point to the value of UUID.
  //
  AdvertisementData += 2;
  Uuid16 = ReadUnaligned16 ((UINT16*)AdvertisementData);

  UuidName = mUnknownUuidName;
  for (Index = 0; Index < sizeof (mServiceUuid16Name) / sizeof (mServiceUuid16Name[0]); Index++) {
    if (Uuid16 == mServiceUuid16Name[Index].Uuid) {
      UuidName = mServiceUuid16Name[Index].Name;
      break;
    }
  }
  StringLen = StrSize (UuidName) + sizeof (L"  ");
  DisplayName = AllocatePool (StringLen);
  ASSERT (DisplayName != NULL);
  UnicodeSPrint (DisplayName, StringLen, L"  %s", UuidName);
  return DisplayName;
}

/**
  Updates the service information of a remote Bluetooth device.

  @param[in]  AdvertisementData      A pointer to the BluetoothLE advertisement
                                     data.
  @param[in]  AdvertisementDataSize  The size of AdvertisementData in bytes.

**/
VOID
UpdateServiceInfoForRemoteDev (
  IN UINT8                *AdvertisementData,
  IN UINT32               AdvertisementDataSize
  )
{
  UINT8                   *AdInCompUuid16;
  UINT8                   *AdCompUuid16;
  UINT8                   *TempAdvertisementData;
  VOID                    *StartOpCodeHandle;
  VOID                    *EndOpCodeHandle;
  EFI_IFR_GUID_LABEL      *StartLabel;
  EFI_IFR_GUID_LABEL      *EndLabel;
  EFI_STRING_ID           StringId;
  CHAR16                  *UnicodeData;
  UINT32                  TempAdvertisementDataSize;

  //
  // Allocate space for creation of UpdateData Buffer
  //
  StartOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (StartOpCodeHandle != NULL);

  EndOpCodeHandle = HiiAllocateOpCodeHandle ();
  ASSERT (EndOpCodeHandle != NULL);

  //
  // Create Hii Extend Label OpCode as the start opcode
  //
  StartLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (StartOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  StartLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  StartLabel->Number       = LABEL_BLUETOOTH_AVAILABLE_SERVICE_LIST;

  //
  // Create Hii Extend Label OpCode as the end opcode
  //
  EndLabel = (EFI_IFR_GUID_LABEL *) HiiCreateGuidOpCode (EndOpCodeHandle, &gEfiIfrTianoGuid, NULL, sizeof (EFI_IFR_GUID_LABEL));
  EndLabel->ExtendOpCode = EFI_IFR_EXTEND_OP_LABEL;
  EndLabel->Number       = LABEL_BLUETOOTH_AVAILABLE_SERVICE_END;

  TempAdvertisementData = AdvertisementData;
  TempAdvertisementDataSize = AdvertisementDataSize;

  if (TempAdvertisementData != NULL) {
    AdInCompUuid16 = FindTypeFromAdvertisementData (TempAdvertisementData, TempAdvertisementDataSize,BluetoothGapTypeIncomplete16BitServiceClassUUIDs);
    while ((AdInCompUuid16 != NULL) && ((AdInCompUuid16 + 4) <= (TempAdvertisementData + TempAdvertisementDataSize))) {
      UnicodeData = UuidToName (AdInCompUuid16);
      StringId = HiiSetString (mBtConfigDevice->HiiHandle, 0, UnicodeData, NULL);
      FreePool(UnicodeData);
      HiiCreateTextOpCode (
        StartOpCodeHandle,
        StringId,
        0,
        0
        );

      if (TempAdvertisementDataSize < (UINT32)(*AdInCompUuid16 + 1)) {
        break;
      }

      TempAdvertisementData += (*AdInCompUuid16 + 1);
      TempAdvertisementDataSize -= (*AdInCompUuid16 + 1);

      AdInCompUuid16 = FindTypeFromAdvertisementData (TempAdvertisementData, TempAdvertisementDataSize,BluetoothGapTypeIncomplete16BitServiceClassUUIDs);
    }

    AdCompUuid16 = FindTypeFromAdvertisementData (AdvertisementData, AdvertisementDataSize, BluetoothGapTypeComplete16BitServiceClassUUIDs);
    if ((AdInCompUuid16 != NULL) && ((AdInCompUuid16 + 4) <= (AdvertisementData + AdvertisementDataSize))) {
      UnicodeData = UuidToName (AdCompUuid16);
      StringId = HiiSetString (mBtConfigDevice->HiiHandle, 0, UnicodeData, NULL);
      FreePool(UnicodeData);
      HiiCreateTextOpCode (
        StartOpCodeHandle,
        StringId,
        0,
        0
        );
    }
  }

  HiiUpdateForm (
    mBtConfigDevice->HiiHandle,
    &gHiiBluetoothConfigFormSetGuid,
    BLUETOOTH_REMOTE_DEVICE_FORM,
    StartOpCodeHandle,
    EndOpCodeHandle
    );

  HiiFreeOpCodeHandle (StartOpCodeHandle);
  HiiFreeOpCodeHandle (EndOpCodeHandle);
}

/**
  Updates the information of a remote Bluetooth device for display.

  @param[in]  RemoteDev  A pointer to the BT_REMOTE_DEVICE_ATTRIBUTE structure.

  @retval  EFI_SUCCESS           The information of the specified remote
                                 Bluetooth device has been updated
                                 successfully.
  @retval  EFI_OUT_OF_RESOURCES  The operation fails due to memory allocation
                                 failure.
  @retval  Other                 A value from other functions.

**/
EFI_STATUS
UpdateRemoteDevPageInfo (
  IN BT_REMOTE_DEVICE_ATTRIBUTE       *RemoteDev
  )
{
  EFI_STRING_ID          StringId;
  CHAR16                 *UniValue;
  EFI_STATUS             Status;
  VOID                   *Buffer;
  UINTN                  BufferSize;

  Status = EFI_SUCCESS;

  //
  // Update remote dev name.
  //
  if (AsciiStrnLenS ((const CHAR8*)(RemoteDev->LocalName), MAX_DEVICE_NAME_LEN) != 0) {
    UniValue = AllocateZeroPool (AsciiStrSize ((const CHAR8*)(RemoteDev->LocalName)) * sizeof (CHAR16));
    ASSERT (UniValue != NULL);
    AsciiStrToUnicodeStrS ((const CHAR8*)(RemoteDev->LocalName), UniValue, AsciiStrSize ((const CHAR8*)(RemoteDev->LocalName)));
  } else {
    UniValue = AllocateCopyPool (StrSize (L" "), L" ");
  }
  StringId = HiiSetString (
             mBtConfigDevice->HiiHandle,
             STRING_TOKEN (STR_NAME_STRING_VALUE),
             UniValue,
             NULL
             );
  if (StringId == 0) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Update remote dev address.
  //
  UniValue = AllocateZeroPool ((3 * 6) * sizeof (CHAR16));
  ASSERT (UniValue != NULL);
  UnicodeSPrint (
    UniValue,
    (3 * 6) * sizeof (CHAR16),
    L"%02x-%02x-%02x-%02x-%02x-%02x",
    (UINTN)RemoteDev->AdvAddr.Address[0],
    (UINTN)RemoteDev->AdvAddr.Address[1],
    (UINTN)RemoteDev->AdvAddr.Address[2],
    (UINTN)RemoteDev->AdvAddr.Address[3],
    (UINTN)RemoteDev->AdvAddr.Address[4],
    (UINTN)RemoteDev->AdvAddr.Address[5]
    );
  StringId = HiiSetString (
               mBtConfigDevice->HiiHandle,
               STRING_TOKEN (STR_REMOTE_ADDRESS_STRING_VALUE),
               UniValue,
               NULL
               );
  if (StringId == 0) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Update remote dev state info.
  //
  if ((RemoteDev->RemoteDeviceState & EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED) != 0) {
    UniValue = AllocateCopyPool (StrSize (L"Connected"), L"Connected");
  } else {
    UniValue = AllocateCopyPool (StrSize (L"Disconnected"), L"Disconnected");
  }
  StringId = HiiSetString (
             mBtConfigDevice->HiiHandle,
             STRING_TOKEN (STR_STATE_STRING_VALUE),
             UniValue,
             NULL
             );
  if (StringId == 0) {
    return EFI_OUT_OF_RESOURCES;
  }

  //
  // Get Sdp Info for this device.
  //
  BufferSize = 0;
  Buffer = NULL;
  Status = mBtConfigDevice->BluetoothLeConfig->GetRemoteData (mBtConfigDevice->BluetoothLeConfig, EfiBluetoothConfigDataTypeAdvertisementData, &RemoteDev->AdvAddr, &BufferSize, Buffer);
  if (Status == EFI_BUFFER_TOO_SMALL) {
    Buffer = AllocateZeroPool (BufferSize);
    Status = mBtConfigDevice->BluetoothLeConfig->GetRemoteData(mBtConfigDevice->BluetoothLeConfig, EfiBluetoothConfigDataTypeAdvertisementData, &RemoteDev->AdvAddr, &BufferSize, Buffer);
    if (Status == EFI_SUCCESS) {
      ASSERT (Buffer != NULL);
      DumpAdvertisementData (Buffer, (UINT32)BufferSize);
      UpdateServiceInfoForRemoteDev (Buffer, (UINT32)BufferSize);
      FreePool (Buffer);
    } else {
      DEBUG ((EFI_D_INFO, "BtCfgDxe :: Get AdvertisementData from remote device failed!\n"));
    }
  } else {
    DEBUG ((EFI_D_INFO, "BtCfgDxe :: Get AdvertisementData from remote device failed!\n"));
    //
    // If get SDP info return error, skip it.
    //
    Status = EFI_SUCCESS;
  }

  return Status;
}

/**
  This function allows a caller to extract the current configuration for one
  or more named elements from the target driver.


  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Request         A null-terminated Unicode string in <ConfigRequest> format.
  @param Progress        On return, points to a character in the Request string.
                         Points to the string's null terminator if request was successful.
                         Points to the most recent '&' before the first failing name/value
                         pair (or the beginning of the string if the failure is in the
                         first name/value pair) if the request was not successful.
  @param Results         A null-terminated Unicode string in <ConfigAltResp> format which
                         has all values filled in for the names in the Request string.
                         String to be allocated by the called function.

  @retval  EFI_SUCCESS            The Results is filled with the requested values.
  @retval  EFI_OUT_OF_RESOURCES   Not enough memory to store the results.
  @retval  EFI_INVALID_PARAMETER  Request is illegal syntax, or unknown name.
  @retval  EFI_NOT_FOUND          Routing data doesn't match any storage in this driver.

**/
EFI_STATUS
EFIAPI
HiiConfigAccessExtractConfig (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  CONST EFI_STRING                       Request,
  OUT EFI_STRING                             *Progress,
  OUT EFI_STRING                             *Results
  )
{
  if (Progress == NULL || Results == NULL) {
    return EFI_INVALID_PARAMETER;
  }
  *Progress = Request;
  return EFI_NOT_FOUND;
}

/**
  This function processes the results of changes in configuration.


  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Configuration   A null-terminated Unicode string in <ConfigResp> format.
  @param Progress        A pointer to a string filled in with the offset of the most
                         recent '&' before the first failing name/value pair (or the
                         beginning of the string if the failure is in the first
                         name/value pair) or the terminating NULL if all was successful.

  @retval  EFI_SUCCESS            The Results is processed successfully.
  @retval  EFI_INVALID_PARAMETER  Configuration is NULL.
  @retval  EFI_NOT_FOUND          Routing data doesn't match any storage in this driver.

**/
EFI_STATUS
EFIAPI
HiiConfigAccessRouteConfig (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  CONST EFI_STRING                       Configuration,
  OUT EFI_STRING                             *Progress
  )
{
  if (Configuration == NULL || Progress == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  *Progress = Configuration + StrLen (Configuration);
  return EFI_SUCCESS;
}

/**
  The callback function to get SMP data.

  @param[in]       This      Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                             instance.
  @param[in]       Context   Data passed into callback function. This is
                             optional parameter and may be NULL.
  @param[in]       IDAddr    Remote BluetoothLE device address. For Local
                             device setting, it should be NULL.
                             Call in with Identify address.
  @param[in]       DataType  Data type in EFI_BLUETOOTH_LE_SMP_DATA_TYPE.
  @param[in, out]  DataSize  On input, indicates the size, in bytes, of the
                             data buffer specified by Data. On output,
                             indicates the amount of data actually returned.
  @param[out]      Data      A pointer to the buffer of data that will be
                             returned.

  @retval  EFI_SUCCESS            The SMP get data callback function is
                                  registered successfully.
  @retval  EFI_BUFFER_TOO_SMALL   Data is too small to hold the return data.
  @retval  EFI_INVALID_PARAMETER  The value of DataType is not in
                                  EFI_BLUETOOTH_LE_SMP_DATA_TYPE.
  @retval  EFI_UNSUPPORTED        The given DataType is currently not
                                  supported.
  @retval  Other                  A value from other functions.

**/
EFI_STATUS
EFIAPI
LeSmpGetDataCallback (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL  *This,
  IN VOID                              *Context,
  IN BLUETOOTH_LE_ADDRESS              *IDAddr,
  IN EFI_BLUETOOTH_LE_SMP_DATA_TYPE    DataType,
  IN OUT UINTN                         *DataSize,
  OUT VOID                             *Data
  )
{
  EFI_STATUS                 Status;
  BT_LE_REMOTE_DEV_STORAGE   *RemoteData;
  UINT8                      Count;
  UINT8                      *DataPtr;

  Status = EFI_SUCCESS;

  if (IDAddr == NULL) {
    DEBUG ((EFI_D_INFO, "BtCfgDxe :: LeSmpGetDataCallback DataType = 0x%x, IDAddr = NULL\n", DataType));
  } else {
    DEBUG ((EFI_D_INFO, "BtCfgDxe :: LeSmpGetDataCallback DataType = 0x%x, IDAddr = %02x:%02x:%02x:%02x:%02x:%02x(%x)\n",
                            DataType,
                            IDAddr->Address[0], IDAddr->Address[1],
                            IDAddr->Address[2], IDAddr->Address[3],
                            IDAddr->Address[4], IDAddr->Address[5],
                            IDAddr->Type));
  }

  if (*DataSize == 0) {
    *DataSize = MAX((EFI_BLUETOOTH_LE_MAX_BONDED_DEV * sizeof(BLUETOOTH_LE_ADDRESS)), MAX_DEVICE_NAME_LEN);
    return EFI_BUFFER_TOO_SMALL;
  }

  if (Data == NULL) {
    *DataSize = 0;
    return EFI_BUFFER_TOO_SMALL;
  }

  if (IDAddr == NULL) {
    switch(DataType) {
    case EfiBluetoothSmpLocalIRK:
      *DataSize = sizeof(mBtConfigDevice->ControllerData.KeyIrk);
      CopyMem(Data, mBtConfigDevice->ControllerData.KeyIrk, sizeof(mBtConfigDevice->ControllerData.KeyIrk));
      break;
    case ((EFI_BLUETOOTH_LE_SMP_DATA_TYPE) EfiBluetoothSmpPeerAddress):
      DataPtr = (UINT8*)Data;
      *DataSize = 0;
      for (Count = 0; Count < EFI_BLUETOOTH_LE_MAX_BONDED_DEV; Count++) {
        if (IsValidBleAddress(&mBtConfigDevice->ControllerData.RemoteIDAddr[Count])) {
          //
          // Found remote device entry in local device storage
          //
          CopyMem(DataPtr, &mBtConfigDevice->ControllerData.RemoteIDAddr[Count], sizeof(BLUETOOTH_LE_ADDRESS));
          DataPtr += sizeof(BLUETOOTH_LE_ADDRESS);
          *DataSize += sizeof(BLUETOOTH_LE_ADDRESS);
        }
      }
      break;
    default:
      *DataSize = 0;
      Status  = EFI_INVALID_PARAMETER;
      break;
    }
  } else {
    RemoteData = LocateDevInGlobalData (IDAddr, NULL);
    if (RemoteData == NULL) {
      /* Remote Entry is not Available */
      *DataSize = 0;
      return EFI_NOT_FOUND;
    }

    switch(DataType) {
    case EfiBluetoothSmpLocalIR:
      *DataSize = 0;
      Status  = EFI_UNSUPPORTED;
      break;
    case EfiBluetoothSmpLocalER:
      *DataSize = 0;
      Status  = EFI_UNSUPPORTED;
      break;
    case EfiBluetoothSmpLocalDHK:
      *DataSize = 0;
      Status  = EFI_UNSUPPORTED;
      break;
    case EfiBluetoothSmpKeysDistributed:
      *DataSize = sizeof(RemoteData->KeysDistributed);
      CopyMem(Data, &RemoteData->KeysDistributed, sizeof(RemoteData->KeysDistributed));
      break;
    case EfiBluetoothSmpKeySize:
      *DataSize = sizeof(RemoteData->KeySize);
      CopyMem(Data, &RemoteData->KeySize, sizeof(RemoteData->KeySize));
      break;
    case EfiBluetoothSmpKeyType:
      *DataSize = sizeof(RemoteData->AuthReq);
      CopyMem(Data, &RemoteData->AuthReq, sizeof(RemoteData->AuthReq));
      break;
    case EfiBluetoothSmpPeerLTK:
      *DataSize = sizeof(RemoteData->PeerLtk);
      CopyMem(Data, RemoteData->PeerLtk, sizeof(RemoteData->PeerLtk));
      break;
    case EfiBluetoothSmpPeerIRK:
      *DataSize = sizeof(RemoteData->PeerIrk);
      CopyMem(Data, RemoteData->PeerIrk, sizeof(RemoteData->PeerIrk));
      break;
    case EfiBluetoothSmpPeerCSRK:
      *DataSize = sizeof(RemoteData->PeerCsrk);
      CopyMem(Data, RemoteData->PeerCsrk, sizeof(RemoteData->PeerCsrk));
      break;
    case EfiBluetoothSmpPeerRand:
      *DataSize = sizeof(RemoteData->PeerRand);
      CopyMem(Data, RemoteData->PeerRand, sizeof(RemoteData->PeerRand));
      break;
    case EfiBluetoothSmpPeerEDIV:
      *DataSize = sizeof(RemoteData->PeerEdiv);
      CopyMem(Data, &RemoteData->PeerEdiv, sizeof(RemoteData->PeerEdiv));
      break;
    case EfiBluetoothSmpPeerSignCounter:
      *DataSize = sizeof(RemoteData->PeerSignCounter);
      CopyMem(Data, &RemoteData->PeerSignCounter, sizeof(RemoteData->PeerSignCounter));
      break;
    case EfiBluetoothSmpLocalLTK:
      *DataSize = sizeof(RemoteData->LocalLtk);
      CopyMem(Data, RemoteData->LocalLtk, sizeof(RemoteData->LocalLtk));
      break;
    case EfiBluetoothSmpLocalIRK:
      *DataSize = sizeof(RemoteData->LocalIrk);
      CopyMem(Data, RemoteData->LocalIrk, sizeof(RemoteData->LocalIrk));
      break;
    case EfiBluetoothSmpLocalCSRK:
      *DataSize = sizeof(RemoteData->LocalCsrk);
      CopyMem(Data, RemoteData->LocalCsrk, sizeof(RemoteData->LocalCsrk));
      break;
    case EfiBluetoothSmpLocalSignCounter:
      *DataSize = sizeof(RemoteData->LocalSignCounter);
      CopyMem(Data, &RemoteData->LocalSignCounter, sizeof(RemoteData->LocalSignCounter));
      break;
    case EfiBluetoothSmpLocalDIV:
      *DataSize = 0;
      Status  = EFI_UNSUPPORTED;
      break;
    default:
      *DataSize = 0;
      Status  = EFI_INVALID_PARAMETER;
      break;
    }
  }

  return Status;
}

/**
  The callback function to set SMP data.

  @param[in]  This      Pointer to the EFI_BLUETOOTH_LE_CONFIG_PROTOCOL
                        instance.
  @param[in]  Context   Data passed into callback function. This is optional
                        parameter and may be NULL.
  @param[in]  IDAddr    Remote BluetoothLE device address.
                        Call in with Identify address.
  @param[in]  DataType  Data type in EFI_BLUETOOTH_LE_SMP_DATA_TYPE.
  @param[in]  DataSize  Indicates the size, in bytes, of the data buffer
                        specified by Data.
  @param[in]  Data      A pointer to the buffer of data.

  @retval  EFI_SUCCESS            The SMP set data callback function is
                                  registered successfully.
  @retval  EFI_INVALID_PARAMETER  The value of DataType is not in
                                  EFI_BLUETOOTH_LE_SMP_DATA_TYPE.
  @retval  EFI_UNSUPPORTED        The given DataType is currently not
                                  supported.
  @retval  Other                  A value from other functions.

**/
EFI_STATUS
EFIAPI
LeSmpSetDataCallback (
  IN EFI_BLUETOOTH_LE_CONFIG_PROTOCOL  *This,
  IN VOID                              *Context,
  IN BLUETOOTH_LE_ADDRESS              *IDAddr,
  IN EFI_BLUETOOTH_LE_SMP_DATA_TYPE    DataType,
  IN UINTN                             DataSize,
  IN VOID                              *Data
  )
{
  EFI_STATUS               Status;
  BT_LE_REMOTE_DEV_STORAGE *RemoteData;
  UINTN                    LocalDataSize;
  UINTN                    Index;

  Status = EFI_SUCCESS;

  if (mBtConfigDevice->ConnectState != StateConnecting) {
    DEBUG ((DEBUG_INFO, "BtCfgDxe :: LeSmpSetDataCallback call in not in CONNECTING phase!\n"));
  }

  if (IDAddr == NULL) {
    DEBUG ((EFI_D_INFO, "BtCfgDxe :: LeSmpSetDataCallback DataType = 0x%x, IDAddr = NULL\n", DataType));
  } else {
    DEBUG ((EFI_D_INFO, "BtCfgDxe :: LeSmpSetDataCallback DataType = 0x%x, IDAddr = %02x:%02x:%02x:%02x:%02x:%02x(%x)\n",
                            DataType,
                            IDAddr->Address[0], IDAddr->Address[1],
                            IDAddr->Address[2], IDAddr->Address[3],
                            IDAddr->Address[4], IDAddr->Address[5],
                            IDAddr->Type));
    if (DataType != EfiBluetoothSmpKeysDistributed) {
      //
      // EfiBluetoothSmpKeysDistributed is first type which called in to update the
      // mBtConfigDevice->CurrentBondingDev->IDAddr.
      // If current call in type is not EfiBluetoothSmpKeysDistributed and mBtConfigDevice->CurrentBondingDev->IDAddr
      // still invalid, this is not a correct situation. So add ASSERT code here.
      //
      if (!IsValidBleAddress(&mBtConfigDevice->CurrentBondingDev->IDAddr)) {
        DEBUG ((DEBUG_ERROR, "BtCfgDxe :: !!!WARNING!!! IDAddr still invalid after EfiBluetoothSmpKeysDistributed type!\n"));
        ASSERT (FALSE);
      }
    }
  }

  if (IDAddr == NULL) {
    switch(DataType) {
    case EfiBluetoothSmpLocalIRK:
    {
      if (DataSize == sizeof(mBtConfigDevice->ControllerData.KeyIrk) && (Data != NULL)) {
        CopyMem(mBtConfigDevice->ControllerData.KeyIrk, Data, sizeof(mBtConfigDevice->ControllerData.KeyIrk));

        LocalDataSize = sizeof(BT_LE_LOCAL_DEV_STORAGE);
        Status = gRT->SetVariable(mLocalDeviceDataVariableName,
                   &gEfiBluetoothLeConfigProtocolGuid,
                   EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
                   LocalDataSize,
                   &mBtConfigDevice->ControllerData);
        ASSERT_EFI_ERROR (Status);
      }
    }
      break;
    default:
      Status  = EFI_INVALID_PARAMETER;
      break;
    }
  } else {
    RemoteData = LocateDevInGlobalData (IDAddr, &Index);
    if (RemoteData == NULL) {
      DEBUG ((EFI_D_INFO, "BtCfgDxe :: LeSmpSetDataCallback allocate new Global Data!\n"));
      //
      // Add new device to local device storage.
      //
      for (Index = 0; Index < EFI_BLUETOOTH_LE_MAX_BONDED_DEV; Index++) {
        if (!IsValidBleAddress (&mBtConfigDevice->ControllerData.RemoteIDAddr[Index])) {
          CopyMem(&mBtConfigDevice->ControllerData.RemoteIDAddr[Index], IDAddr, sizeof(BLUETOOTH_LE_ADDRESS));
          ZeroMem (&mBtConfigDevice->PairedDevData[Index], sizeof (&mBtConfigDevice->PairedDevData[Index]));
          RemoteData = &mBtConfigDevice->PairedDevData[Index];
          break;
        }
      }

      if (RemoteData == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }
    }

    switch(DataType) {
    case EfiBluetoothSmpLocalIR:
      Status  = EFI_UNSUPPORTED;
      break;
    case EfiBluetoothSmpLocalER:
      Status  = EFI_UNSUPPORTED;
      break;
    case EfiBluetoothSmpLocalDHK:
      Status  = EFI_UNSUPPORTED;
      break;
    case EfiBluetoothSmpKeysDistributed:
      //
      // This is new pairing entry, so deleting all other information if already exist
      //
      SetMem(RemoteData, sizeof(BT_LE_REMOTE_DEV_STORAGE), 0);
      CopyMem(&mBtConfigDevice->CurrentBondingDev->IDAddr, IDAddr, sizeof(BLUETOOTH_LE_ADDRESS));
      DEBUG ((EFI_D_INFO, "BtCfgDxe :: LeSmpSetDataCallback call in, update IDAdrr success!\n"));
      CopyMem(&RemoteData->KeysDistributed, Data, sizeof(RemoteData->KeysDistributed));
      break;
    case EfiBluetoothSmpKeySize:
      CopyMem(&RemoteData->KeySize, Data, sizeof(RemoteData->KeySize));
      break;
    case EfiBluetoothSmpKeyType:
      CopyMem(&RemoteData->AuthReq, Data, sizeof(RemoteData->AuthReq));
      break;
    case EfiBluetoothSmpPeerLTK:
      CopyMem(RemoteData->PeerLtk, Data, sizeof(RemoteData->PeerLtk));
      break;
    case EfiBluetoothSmpPeerIRK:
      CopyMem(RemoteData->PeerIrk, Data, sizeof(RemoteData->PeerIrk));
      break;
    case EfiBluetoothSmpPeerCSRK:
      CopyMem(RemoteData->PeerCsrk, Data, sizeof(RemoteData->PeerCsrk));
      break;
    case EfiBluetoothSmpPeerRand:
      CopyMem(RemoteData->PeerRand, Data, sizeof(RemoteData->PeerRand));
      break;
    case EfiBluetoothSmpPeerEDIV:
      CopyMem(&RemoteData->PeerEdiv, Data, sizeof(RemoteData->PeerEdiv));
      break;
    case EfiBluetoothSmpPeerSignCounter:
      CopyMem(&RemoteData->PeerSignCounter, Data, sizeof(RemoteData->PeerSignCounter));
      break;
    case EfiBluetoothSmpLocalLTK:
      CopyMem(RemoteData->LocalLtk, Data, sizeof(RemoteData->LocalLtk));
      break;
    case EfiBluetoothSmpLocalIRK:
      CopyMem(RemoteData->LocalIrk, Data, sizeof(RemoteData->LocalIrk));
      break;
    case EfiBluetoothSmpLocalCSRK:
      CopyMem(RemoteData->LocalCsrk, Data, sizeof(RemoteData->LocalCsrk));
      break;
    case EfiBluetoothSmpLocalSignCounter:
      CopyMem(&RemoteData->LocalSignCounter, Data, sizeof(RemoteData->LocalSignCounter));
      break;
    case EfiBluetoothSmpLocalDIV:
      Status  = EFI_UNSUPPORTED;
      break;
    default:
      Status  = EFI_INVALID_PARAMETER;
      break;

    }

    //
    // Only save the data if the remote device storage has saved before.
    // It means this callback type is trigged after connect complete.
    //
    if (mBtConfigDevice->PairedDevDataSaved[Index]) {
      SavePairedDevice(IDAddr);
    }
  }
  return Status;
}

/**
  Update device status.
**/
VOID
UpdateDeviceStatus (
  VOID
  )
{
  EFI_HANDLE                 *Handles;
  UINTN                      NumberOfHandles;
  UINTN                      Index;
  EFI_DEVICE_PATH_PROTOCOL   *DevicePath;
  BT_REMOTE_DEVICE_ATTRIBUTE *RemoteDev;
  BLUETOOTH_LE_DEVICE_PATH   *LeDevicePath;

  gBS->LocateHandleBuffer (
                          ByProtocol,
                          &gEfiBluetoothAttributeServiceBindingProtocolGuid,
                          NULL,
                          &NumberOfHandles,
                          &Handles
                          );

  for (Index = 0; Index < NumberOfHandles; Index++) {
    DevicePath = DevicePathFromHandle (Handles[Index]);
    if (DevicePath == NULL) {
      continue;
    }

    while (!IsDevicePathEnd (DevicePath)) {
      if (DevicePathType (DevicePath) == MESSAGING_DEVICE_PATH && DevicePathSubType (DevicePath) == MSG_BLUETOOTH_LE_DP) {
        LeDevicePath = (BLUETOOTH_LE_DEVICE_PATH *) DevicePath;

        DEBUG ((DEBUG_VERBOSE , "BtCfgDxe :: Find BLE Device Node (%02x:%02x:%02x:%02x:%02x:%02x(%x))\n",
                      LeDevicePath->Address.Address[0], LeDevicePath->Address.Address[1],
                      LeDevicePath->Address.Address[2], LeDevicePath->Address.Address[3],
                      LeDevicePath->Address.Address[4], LeDevicePath->Address.Address[5],
                      LeDevicePath->Address.Type));

        RemoteDev = LocateDevInList(LeDevicePath->Address.Address, EfiAnyAddressType);
        if (RemoteDev != NULL) {
          RemoteDev->RemoteDeviceState |= EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED;
          DEBUG ((DEBUG_INFO , "BtCfgDxe :: Add Connected status for device (%02x:%02x:%02x:%02x:%02x:%02x(%x))\n",
                      LeDevicePath->Address.Address[0], LeDevicePath->Address.Address[1],
                      LeDevicePath->Address.Address[2], LeDevicePath->Address.Address[3],
                      LeDevicePath->Address.Address[4], LeDevicePath->Address.Address[5],
                      LeDevicePath->Address.Type));
        }
        break;
      }
      DevicePath = NextDevicePathNode (DevicePath);
    }
  }

  if (Handles != NULL) {
    FreePool (Handles);
  }
}

/**
  Initialize the Paired device list.
**/
VOID
InitializePairedDevice (
  VOID
  )
{
  EFI_STATUS                  Status;
  UINTN                       Index;
  CHAR16                      RemoteBdAddrStr[LE_BD_ADDR_STR_LEN];
  UINTN                       RemoteDataSize;
  BT_REMOTE_DEVICE_ATTRIBUTE  *RemoteDevAttr;

  InitializeListHead (&mBtConfigDevice->RemoteDeviceList);

  for (Index = 0; Index < EFI_BLUETOOTH_LE_MAX_BONDED_DEV; Index++) {
    if (!IsValidBleAddress(&mBtConfigDevice->ControllerData.RemoteIDAddr[Index])) {
      continue;
    }

    //
    // Found remote device entry in local device storage
    //
    ZeroMem(RemoteBdAddrStr, sizeof(RemoteBdAddrStr));
    LE_BDADDR_TO_STRING(RemoteBdAddrStr, mBtConfigDevice->ControllerData.RemoteIDAddr[Index].Address, mBtConfigDevice->ControllerData.RemoteIDAddr[Index].Type);

    RemoteDataSize = sizeof(BT_LE_REMOTE_DEV_STORAGE);

    Status = gRT->GetVariable(RemoteBdAddrStr,
        &gEfiBluetoothLeConfigProtocolGuid,
        NULL,
        &RemoteDataSize,
        &mBtConfigDevice->PairedDevData[Index]);
    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "BtCfgDxe :: Warning! Device in LocalDeviceData don't have local storage! %02x:%02x:%02x:%02x:%02x:%02x(%x)!\n",
        mBtConfigDevice->ControllerData.RemoteIDAddr[Index].Address[0], mBtConfigDevice->ControllerData.RemoteIDAddr[Index].Address[1],
        mBtConfigDevice->ControllerData.RemoteIDAddr[Index].Address[2], mBtConfigDevice->ControllerData.RemoteIDAddr[Index].Address[3],
        mBtConfigDevice->ControllerData.RemoteIDAddr[Index].Address[4], mBtConfigDevice->ControllerData.RemoteIDAddr[Index].Address[5],
        mBtConfigDevice->ControllerData.RemoteIDAddr[Index].Type
        ));

      ZeroMem (&mBtConfigDevice->ControllerData.RemoteIDAddr[Index], sizeof(BLUETOOTH_LE_ADDRESS));
      ZeroMem (&mBtConfigDevice->PairedDevData[Index], sizeof(BT_LE_REMOTE_DEV_STORAGE));
      continue;
    }

    DumpRemoteDeviceData(&mBtConfigDevice->PairedDevData[Index]);

    mBtConfigDevice->PairedDevDataSaved[Index] = TRUE;
    mBtConfigDevice->PairedDevCount++;

    RemoteDevAttr = AllocateZeroPool (sizeof (BT_REMOTE_DEVICE_ATTRIBUTE));
    ASSERT (RemoteDevAttr != NULL);

    RemoteDevAttr->Signature = BT_REMOTE_DEVICE_SIGNATURE;
    CopyMem (&RemoteDevAttr->IDAddr, &mBtConfigDevice->ControllerData.RemoteIDAddr[Index], sizeof (RemoteDevAttr->IDAddr));
    CopyMem (RemoteDevAttr->LocalName, mBtConfigDevice->PairedDevData[Index].PeerName, sizeof(RemoteDevAttr->LocalName));
    RemoteDevAttr->RemoteDeviceState = EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED;
    InsertTailList (&mBtConfigDevice->RemoteDeviceList, &RemoteDevAttr->Link);
  }

  UpdateDeviceStatus ();

  DumpRemoteDeviceList ();
}

/**
  Initialize the host controller related data.

**/
VOID
InitializeControllerData (
  VOID
  )
{
  EFI_STATUS                       Status;
  UINTN                            LocalDataSize;

  Status = EFI_SUCCESS;
  LocalDataSize = sizeof(BT_LE_LOCAL_DEV_STORAGE);

  Status = gRT->GetVariable(mLocalDeviceDataVariableName,
      &gEfiBluetoothLeConfigProtocolGuid,
      NULL,
      &LocalDataSize,
      &mBtConfigDevice->ControllerData);

  if ((LocalDataSize != sizeof(BT_LE_LOCAL_DEV_STORAGE)) || (mBtConfigDevice->ControllerData.LocalName[MAX_DEVICE_NAME_LEN - 1] != 0)) {
    Status = RETURN_COMPROMISED_DATA; // Data is corrupted
  }

  if (EFI_ERROR (Status)) {
    SetMem(&mBtConfigDevice->ControllerData, sizeof(BT_LE_LOCAL_DEV_STORAGE), 0);

    AsciiStrCpyS((CHAR8 *)mBtConfigDevice->ControllerData.LocalName, sizeof(mBtConfigDevice->ControllerData.LocalName), BT_DEFAULT_NAME);

    LocalDataSize = sizeof(BT_LE_LOCAL_DEV_STORAGE);
    Status = gRT->SetVariable(mLocalDeviceDataVariableName,
               &gEfiBluetoothLeConfigProtocolGuid,
               EFI_VARIABLE_BOOTSERVICE_ACCESS | EFI_VARIABLE_RUNTIME_ACCESS | EFI_VARIABLE_NON_VOLATILE,
               LocalDataSize,
               &mBtConfigDevice->ControllerData);
    ASSERT_EFI_ERROR (Status);
  }

  DumpLocalDeviceData (&mBtConfigDevice->ControllerData);
}

/**
  Initialize the ble stack.

  @retval return the status.
**/
EFI_STATUS
InitializeBleStack (
  VOID
  )
{
  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *LeConfigProtocol;
  EFI_STATUS                       Status;

  Status      = EFI_SUCCESS;
  LeConfigProtocol = mBtConfigDevice->BluetoothLeConfig;

  LeConfigProtocol->RegisterSmpGetDataCallback(LeConfigProtocol, LeSmpGetDataCallback, NULL);
  LeConfigProtocol->RegisterSmpSetDataCallback(LeConfigProtocol, LeSmpSetDataCallback, NULL);
  LeConfigProtocol->RegisterSmpAuthCallback(LeConfigProtocol, SmpCallback, NULL);
  LeConfigProtocol->RegisterLinkConnectCompleteCallback(LeConfigProtocol, LinkConnCompCallback, NULL);

  Status = LeConfigProtocol->Init (LeConfigProtocol);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = LeConfigProtocol->SetData (
                                LeConfigProtocol,
                                EfiBluetoothConfigDataTypeDeviceName,
                                AsciiStrnLenS ((CHAR8 *)mBtConfigDevice->ControllerData.LocalName, MAX_DEVICE_NAME_LEN),
                                mBtConfigDevice->ControllerData.LocalName
                                );
  ASSERT_EFI_ERROR (Status);
  DEBUG ((DEBUG_INFO, "BtCfgDxe :: Update host controller name to %a!\n", mBtConfigDevice->ControllerData.LocalName));

  return EFI_SUCCESS;
}

/**
  This function processes the results of changes in configuration.


  @param This            Points to the EFI_HII_CONFIG_ACCESS_PROTOCOL.
  @param Action          Specifies the type of action taken by the browser.
  @param QuestionId      A unique value which is sent to the original exporting driver
                         so that it can identify the type of data to expect.
  @param Type            The type of value for the question.
  @param Value           A pointer to the data being sent to the original exporting driver.
  @param ActionRequest   On return, points to the action requested by the callback function.

  @retval  EFI_SUCCESS           The callback successfully handled the action.
  @retval  EFI_OUT_OF_RESOURCES  Not enough storage is available to hold the variable and its data.
  @retval  EFI_DEVICE_ERROR      The variable could not be saved.
  @retval  EFI_UNSUPPORTED       The specified Action is not supported by the callback.

**/
EFI_STATUS
EFIAPI
HiiConfigAccessCallback (
  IN  CONST EFI_HII_CONFIG_ACCESS_PROTOCOL   *This,
  IN  EFI_BROWSER_ACTION                     Action,
  IN  EFI_QUESTION_ID                        QuestionId,
  IN  UINT8                                  Type,
  IN  EFI_IFR_TYPE_VALUE                     *Value,
  OUT EFI_BROWSER_ACTION_REQUEST             *ActionRequest
  )
{
  EFI_STATUS                  Status;
  UINT64                      InputValue;
  CHAR16                      *UnicodeData;
  EFI_STRING_ID               StringId;
  BT_REMOTE_DEVICE_ATTRIBUTE  *RemoteDev;
  EFI_INPUT_KEY               Key;
  UINT8                       Index;
  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *LeConfigProtocol;

  Status      = EFI_SUCCESS;
  UnicodeData = NULL;
  LeConfigProtocol = mBtConfigDevice->BluetoothLeConfig;

  if ((LeConfigProtocol == NULL) && (Action != EFI_BROWSER_ACTION_FORM_OPEN)) {
    return EFI_UNSUPPORTED;
  }

  switch (Action) {
  case EFI_BROWSER_ACTION_FORM_OPEN:
    {
      switch (QuestionId) {
      case KEY_HOST_CONTROLLER_LOCAL_NAME:
        if (!mBtConfigDevice->FinishHostInit) {
          Status = GetDeviceAddress (LeConfigProtocol, &UnicodeData);
          if (!EFI_ERROR (Status)) {
            StringId = HiiSetString (
                         mBtConfigDevice->HiiHandle,
                         STRING_TOKEN (STR_ADDRESS_STRING_VALUE),
                         UnicodeData,
                         NULL
                         );

            FreePool (UnicodeData);
          }

          mBtConfigDevice->FinishHostInit = TRUE;
        }
        break;

      case KEY_GOTO_DEVICE_MANAGER:
        UpdateScanMenu ();
        UpdateDevicePage ();
        break;

      default:
        break;
      }
    }
    break;

  case EFI_BROWSER_ACTION_RETRIEVE:
    {
      switch (QuestionId) {
      case KEY_HOST_CONTROLLER_LOCAL_NAME:
        Status = GetLocalName (LeConfigProtocol, &UnicodeData);
        if (EFI_ERROR (Status)) {
          Status = EFI_DEVICE_ERROR;
        } else {
          StringId = HiiSetString (
                       mBtConfigDevice->HiiHandle,
                       Value->string,
                       UnicodeData,
                       NULL
                       );
          if (StringId == 0) {
            Status = EFI_OUT_OF_RESOURCES;
          }
        }
        break;

      case KEY_REFRESH_DEVICE_ID:
        if (mBtConfigDevice->FoundNewDevice) {
          mBtConfigDevice->FoundNewDevice = FALSE;

          UpdateDevicePage ();
          if (mBtConfigDevice->UpdateScanMenu) {
            UpdateScanMenu ();
            mBtConfigDevice->UpdateScanMenu = FALSE;
          }
        }
        break;

      default:
        break;
      }

    }
    break;

  case EFI_BROWSER_ACTION_CHANGING:
    {
      if (QuestionId >= CONNECT_DEVICE_OFFSET && QuestionId < CONNECT_DEVICE_OFFSET + DEVICE_LIST_MAX) {

        //
        // Press connect for one device.
        //
        RemoteDev = GetRemoteDevice (QuestionId - CONNECT_DEVICE_OFFSET);
        ASSERT (RemoteDev != NULL);

        if (((RemoteDev->RemoteDeviceState & EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED) == 0) &&
            (mBtConfigDevice->PairedDevCount == EFI_BLUETOOTH_LE_MAX_BONDED_DEV)) {
          //
          // Forbid to connect to a new device when paired device count is equal to EFI_BLUETOOTH_LE_MAX_BONDED_DEV.
          //
          ConnectResultPopup (RemoteDev, ResultExceedMaxPairedDevices);
          Status = EFI_UNSUPPORTED;
          break;
        }

        PERF_START (NULL, "Connect", "Bluetooth", 0);
        ConnectDevice (RemoteDev);

        if ((RemoteDev->RemoteDeviceState & EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED) == 0) {
          ConnectResultPopup(RemoteDev, ResultConnectFail);
        }
      } else if (QuestionId >= DISCONNECT_DEVICE_OFFSET && QuestionId < DISCONNECT_DEVICE_OFFSET + DEVICE_LIST_MAX) {
        //
        // Press disconnect for one device.
        //
        RemoteDev = GetRemoteDevice (QuestionId - DISCONNECT_DEVICE_OFFSET);
        ASSERT (RemoteDev != NULL);

        DisconnectDevice(RemoteDev, BluetoothDisconnectReasonTypeRemoteUserTerminatedConnection);

        if ((RemoteDev->RemoteDeviceState & EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED) != 0) {
          ConnectResultPopup(RemoteDev, ResultDisconnectFail);
        }
      } else if (QuestionId >= REMOTE_DEVICE_OFFSET && QuestionId < REMOTE_DEVICE_OFFSET + DEVICE_LIST_MAX) {
        //
        // Press DeviceInfo for one device.
        //
        RemoteDev = GetRemoteDevice (QuestionId - REMOTE_DEVICE_OFFSET);
        ASSERT (RemoteDev != NULL);

        DEBUG ((EFI_D_INFO, "BtCfgDxe :: Enter remote Device page: %a, Addr: %02x:%02x:%02x:%02x:%02x:%02x(%x)\n",
          RemoteDev->LocalName,
          RemoteDev->AdvAddr.Address[0],RemoteDev->AdvAddr.Address[1],
          RemoteDev->AdvAddr.Address[2],RemoteDev->AdvAddr.Address[3],
          RemoteDev->AdvAddr.Address[4],RemoteDev->AdvAddr.Address[5],
          RemoteDev->AdvAddr.Type
          ));

        Status = UpdateRemoteDevPageInfo (RemoteDev);
      } else if (QuestionId >= DELETE_DEVICE_OFFSET && QuestionId < DELETE_DEVICE_OFFSET + DEVICE_LIST_MAX) {
        //
        // Press Delete for one device.
        //
        RemoteDev = GetRemoteDevice (QuestionId - DELETE_DEVICE_OFFSET);
        ASSERT (RemoteDev != NULL);

        DisconnectDevice (RemoteDev, BluetoothDisconnectReasonTypeRemoteDeviceTerminatedConnectionDueToLowResources);

        DeleteRemoteDeviceByAddress (&RemoteDev->IDAddr);
      } else if (QuestionId == KEY_HOST_CONTROLLER_LOCAL_NAME) {
        GetInputValue (Type, Value, &InputValue);
        UnicodeData = HiiGetString (mBtConfigDevice->HiiHandle, (EFI_STRING_ID) InputValue, NULL);
        for (Index = 0; Index < StrLen (UnicodeData); Index ++) {
          if (UnicodeData[Index] != L' ') {
            break;
          }
        }
        if (Index == StrLen (UnicodeData)) {
          do {
            CreatePopUp (EFI_LIGHTGRAY | EFI_BACKGROUND_BLUE, &Key, L"Update fail! LocalName cannot contain only spaces", L"Press ENTER to continue", NULL);
          } while (Key.UnicodeChar != CHAR_CARRIAGE_RETURN);
          Status = EFI_DEVICE_ERROR;
        }
        FreePool (UnicodeData);
      }
    }
    break;

  case EFI_BROWSER_ACTION_CHANGED:
    {
      if ((QuestionId >= DELETE_DEVICE_OFFSET && QuestionId < DELETE_DEVICE_OFFSET + DEVICE_LIST_MAX) ||
          (QuestionId >= CONNECT_DEVICE_OFFSET && QuestionId < CONNECT_DEVICE_OFFSET + DEVICE_LIST_MAX) ||
          (QuestionId >= DISCONNECT_DEVICE_OFFSET && QuestionId < DISCONNECT_DEVICE_OFFSET + DEVICE_LIST_MAX)){
        //
        // Update the remote device list form.
        //
        UpdateDevicePage ();
      } else {
        switch (QuestionId) {
        case KEY_HOST_CONTROLLER_LOCAL_NAME:
          GetInputValue (Type, Value, &InputValue);
          UnicodeData = HiiGetString (mBtConfigDevice->HiiHandle, (EFI_STRING_ID) InputValue, NULL);
          Status = SetLocalName (LeConfigProtocol, UnicodeData);
          FreePool (UnicodeData);
          break;

        case KEY_SCAN_DEVICE_ID:
          //
          // Clean the saved device list before do the new scan.
          // Clean the available device in scan page before do the new scan.
          //
          DeleteRemoteDeviceByState (0);
          UpdateDevicePage ();

          mBtConfigDevice->InScanning = TRUE;
          Status = LeConfigProtocol->Scan (LeConfigProtocol, TRUE, 10, NULL, ScanCallback, NULL);
          if (!EFI_ERROR (Status)) {
            UpdateScanMenu ();
          }

          break;

        default:
          break;
        }
      }
    }
    break;

  default:
    break;
  }

  return Status;
}

/**
  Initialization function for HII.

  @param[in]  ImageHandle     The image handle of this driver.
  @param[in]  Controller      The controller handle.
  @param[in]  DevicePath      Device path of the HII form set.

  @retval  EFI_SUCESS  The HII initialization completes successfully.
  @retval  Other       A value from other functions.

**/
EFI_STATUS
EFIAPI
BluetoothConfigHiiInit (
  IN EFI_HANDLE                   ImageHandle,
  IN EFI_HANDLE                   *Controller,
  IN EFI_DEVICE_PATH_PROTOCOL     *DevicePath
  )
{
  EFI_STATUS                      Status;
  EFI_HII_PACKAGE_LIST_HEADER     *PackageList;

  //
  // Retrieve HII package list from ImageHandle
  //
  Status = gBS->OpenProtocol (
                  ImageHandle,
                  &gEfiHiiPackageListProtocolGuid,
                  (VOID **) &PackageList,
                  ImageHandle,
                  NULL,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  mBtConfigDevice->ConfigAccess.ExtractConfig = HiiConfigAccessExtractConfig;
  mBtConfigDevice->ConfigAccess.RouteConfig = HiiConfigAccessRouteConfig;
  mBtConfigDevice->ConfigAccess.Callback = HiiConfigAccessCallback;

  //
  // Publish sample Fromset
  //
  Status = gBS->InstallMultipleProtocolInterfaces (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  DevicePath,
                  &gEfiHiiConfigAccessProtocolGuid,
                  &mBtConfigDevice->ConfigAccess,
                  NULL
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Publish HII package list to HII Database.
  //
  Status = gHiiDatabase->NewPackageList (
                          gHiiDatabase,
                          PackageList,
                          *Controller,
                          &mBtConfigDevice->HiiHandle
                          );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEventEx (
        EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        EfiEventEmptyFunction,
        NULL,
        &gIfrRefreshRemoteDevGuid,
        &mBtConfigDevice->RefreshRemoteDevEvent
        );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEvent (
        EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        EfiEventEmptyFunction,
        NULL,
        &mBtConfigDevice->PasskeyInputEvent
        );
  ASSERT_EFI_ERROR (Status);

  Status = gBS->CreateEvent (
        EVT_NOTIFY_SIGNAL,
        TPL_CALLBACK,
        StartDeviceDrivers,
        NULL,
        &mBtConfigDevice->ConnectDriverEvent
        );
  ASSERT_EFI_ERROR (Status);

  //
  // Create a lock for performing device list update.
  //
  EfiInitializeLock (&mBtConfigDevice->DeviceListLock, TPL_NOTIFY);

  return EFI_SUCCESS;
}

/**
  Unloads the application and its installed protocol.

  @param[in]  ImageHandle       Handle that identifies the image to be unloaded.

  @retval EFI_SUCCESS           The image has been unloaded.
**/
EFI_STATUS
BluetoothConfigUninit (
  VOID
  )
{
  gBS->CloseEvent (mBtConfigDevice->RefreshRemoteDevEvent);
  gBS->CloseEvent (mBtConfigDevice->PasskeyInputEvent);
  gBS->CloseEvent (mBtConfigDevice->ConnectDriverEvent);

  if (mBtConfigDevice->ControllerHandle != NULL) {
    gBS->UninstallMultipleProtocolInterfaces (
              mBtConfigDevice->ControllerHandle,
              &gEfiDevicePathProtocolGuid,
              mBtConfigDevice->DevicePath,
              &gEfiHiiConfigAccessProtocolGuid,
              &mBtConfigDevice->ConfigAccess,
              NULL
           );
  }

  if (mBtConfigDevice->HiiHandle != NULL) {
    HiiRemovePackages (mBtConfigDevice->HiiHandle);
  }

  return EFI_SUCCESS;
}

/**
  Clean up global data mBtConfigDevice.

  @param  This                  The HID KB driver binding instance.
  @param  Controller            Handle of device to bind driver to.

**/
VOID
CleanUpBtConfigDevice (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller
  )
{
  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *LeConfigProtocol;

  LeConfigProtocol = mBtConfigDevice->BluetoothLeConfig;

  LeConfigProtocol->RegisterSmpAuthCallback(LeConfigProtocol, NULL, NULL);
  LeConfigProtocol->RegisterLinkConnectCompleteCallback(LeConfigProtocol, NULL, NULL);
  LeConfigProtocol->RegisterSmpGetDataCallback(LeConfigProtocol, NULL, NULL);
  LeConfigProtocol->RegisterSmpSetDataCallback(LeConfigProtocol, NULL, NULL);

  gBS->CloseProtocol (
         Controller,
         &gEfiBluetoothLeConfigProtocolGuid,
         This->DriverBindingHandle,
         Controller
         );

  BluetoothConfigUninit ();

  DeleteRemoteDeviceByState (0);
  DeleteRemoteDeviceByState (EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED);
  DeleteRemoteDeviceByState (EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_PAIRED | EFI_BLUETOOTH_CONFIG_REMOTE_DEVICE_STATE_CONNECTED);
  ASSERT (IsListEmpty (&mBtConfigDevice->RemoteDeviceList));

  if (mBtConfigDevice->DevicePath != NULL) {
    FreePool (mBtConfigDevice->DevicePath);
  }
  if (mBtConfigDevice->ControllerNameTable != NULL) {
    FreePool (mBtConfigDevice->ControllerNameTable);
  }
  FreePool (mBtConfigDevice);
}

/**
  Entrypoint of HID KB Driver.

  This function is the entrypoint of HID KB Driver. It installs Driver Binding
  Protocols together with Component Name Protocols.

  @param  ImageHandle       The firmware allocated handle for the EFI image.
  @param  SystemTable       A pointer to the EFI System Table.

  @retval EFI_SUCCESS       The entry point is executed successfully.

**/
EFI_STATUS
EFIAPI
BluetoothConfigDriverBindingEntryPoint (
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;

  Status = EfiLibInstallDriverBindingComponentName2 (
             ImageHandle,
             SystemTable,
             &gBluetoothConfigDriverBinding,
             ImageHandle,
             &gBluetoothConfigComponentName,
             &gBluetoothConfigComponentName2
             );
  ASSERT_EFI_ERROR (Status);

  return EFI_SUCCESS;
}

/**
  Check whether HID KB driver supports this device.

  @param  This                   The HID KB driver binding protocol.
  @param  Controller             The controller handle to check.
  @param  RemainingDevicePath    The remaining device path.

  @retval EFI_SUCCESS            The driver supports this controller.
  @retval other                  This device isn't supported.

**/
EFI_STATUS
EFIAPI
BluetoothConfigDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                       Status;
  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *ConfigProtocol;

  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiBluetoothLeConfigProtocolGuid,
                  (VOID **) &ConfigProtocol,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  gBS->CloseProtocol (
        Controller,
        &gEfiBluetoothLeConfigProtocolGuid,
        This->DriverBindingHandle,
        Controller
        );

  DEBUG ((EFI_D_ERROR, "BluetoothConfigDriverBindingSupported: %r\n", Status));

  return Status;
}


/**
  Starts the HID KB device with this driver.

  This function consumes Hid I/O Portocol, intializes HID KB device,
  installs SimpleTextIn Protocol.

  @param  This                  The HID KB driver binding instance.
  @param  Controller            Handle of device to bind driver to.
  @param  RemainingDevicePath   Optional parameter use to pick a specific child
                                device to start.

  @retval EFI_SUCCESS           This driver supports this device.
  @retval EFI_UNSUPPORTED       This driver does not support this device.
  @retval EFI_DEVICE_ERROR      This driver cannot be started due to device Error.
  @retval EFI_OUT_OF_RESOURCES  Can't allocate memory resources.
  @retval EFI_ALREADY_STARTED   This driver has been started.

**/
EFI_STATUS
EFIAPI
BluetoothConfigDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN EFI_HANDLE                     Controller,
  IN EFI_DEVICE_PATH_PROTOCOL       *RemainingDevicePath
  )
{
  EFI_STATUS                       Status;
  EFI_BLUETOOTH_LE_CONFIG_PROTOCOL *LeConfigProtocol;
  EFI_DEVICE_PATH                  *DevicePath;
  BT_CONFIG_DEV                    *BtConfigDevice;

  DEBUG ((EFI_D_ERROR, "BluetoothConfigDriverBindingStart: Enter Controller = %p\n", Controller));

  BtConfigDevice = NULL;
  //
  // Open Hid I/O Protocol
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiBluetoothLeConfigProtocolGuid,
                  (VOID **) &LeConfigProtocol,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_BY_DRIVER
                  );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Get the Device Path Protocol on Controller's handle
  //
  Status = gBS->OpenProtocol (
                  Controller,
                  &gEfiDevicePathProtocolGuid,
                  (VOID **) &DevicePath,
                  This->DriverBindingHandle,
                  Controller,
                  EFI_OPEN_PROTOCOL_GET_PROTOCOL
                  );

  if (EFI_ERROR (Status)) {
    gBS->CloseProtocol (
       Controller,
       &gEfiBluetoothLeConfigProtocolGuid,
       This->DriverBindingHandle,
       Controller
       );
    return Status;
  }

  BtConfigDevice = AllocateZeroPool (sizeof (BT_CONFIG_DEV));
  ASSERT (BtConfigDevice != NULL);

  BtConfigDevice->Signature              = BTCONFIG_DEV_SIGNATURE;
  BtConfigDevice->BluetoothLeConfig      = LeConfigProtocol;
  BtConfigDevice->DevicePath             = AppendDevicePath (DevicePath, (EFI_DEVICE_PATH *)&mBtConfigDevicePath);

  mBtConfigDevice = BtConfigDevice;

  Status = BluetoothConfigHiiInit (This->DriverBindingHandle, &BtConfigDevice->ControllerHandle, BtConfigDevice->DevicePath);
  ASSERT_EFI_ERROR (Status);

  BtConfigDevice->ControllerNameTable = NULL;
  AddUnicodeString2 (
    "eng",
    gBluetoothConfigComponentName.SupportedLanguages,
    &BtConfigDevice->ControllerNameTable,
    L"Bluetooth Config Driver",
    TRUE
    );
  AddUnicodeString2 (
    "en",
    gBluetoothConfigComponentName2.SupportedLanguages,
    &BtConfigDevice->ControllerNameTable,
    L"Bluetooth Config Driver",
    FALSE
    );

  InitializeControllerData ();
  InitializePairedDevice ();
  Status = InitializeBleStack ();
  if (EFI_ERROR (Status)) {
    goto ErrorExit;
  }

  DEBUG ((EFI_D_ERROR, "BluetoothConfigDriverBindingStart: Exit Success\n"));

  PERF_END (NULL, "Init", "Bluetooth", 0);
  return EFI_SUCCESS;

//
// Error handler
//
ErrorExit:
  if (EFI_ERROR (Status)) {
    CleanUpBtConfigDevice (This, Controller);
  }

  DEBUG ((EFI_D_ERROR, "BluetoothConfigDriverBindingStart: Exit - %r\n", Status));

  return Status;
}

/**
  Stop the HID KB device handled by this driver.

  @param  This                   The HID KB driver binding protocol.
  @param  Controller             The controller to release.
  @param  NumberOfChildren       The number of handles in ChildHandleBuffer.
  @param  ChildHandleBuffer      The array of child handle.

  @retval EFI_SUCCESS            The device was stopped.
  @retval EFI_UNSUPPORTED        SimpleTextIn Protocol is not installed on Controller.
  @retval Others                 Fail to uninstall protocols attached on the device.

**/
EFI_STATUS
EFIAPI
BluetoothConfigDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Controller,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  )
{
  DEBUG ((EFI_D_ERROR, "BluetoothConfigDriverBindingStop: ctrl = %x, no = %x\n", Controller, NumberOfChildren));

  CleanUpBtConfigDevice (This, Controller);

  DEBUG ((EFI_D_ERROR, "BluetoothConfigDriverBindingStop: Exit status = EFI_SUCCESS\n"));

  return EFI_SUCCESS;
}


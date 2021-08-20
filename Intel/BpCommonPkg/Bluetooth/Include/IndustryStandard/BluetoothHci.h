//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Definitions for Bluetooth HCI layer.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef __BLUETOOTH_HCI_H__
#define __BLUETOOTH_HCI_H__

#pragma pack(1)

//
// Host Controller Interface
//

typedef enum {
  BluetoothOGFLinkControlCommands = 0x01,
  BluetoothOGFLinkPolicyCommands = 0x02,
  BluetoothOGFControllerBasebandCommands = 0x03,
  BluetoothOGFInformationalParameters = 0x04,
  BluetoothOGFStatusParameters = 0x05,
  BluetoothOGFTestingCommands = 0x06,
  BluetoothOGFLEControllerCommands = 0x08,
} BLUETOOTH_OGF;

typedef enum {
  //
  // BluetoothOGFLinkControlCommands
  //
  BluetoothOCFInquiry = 0x0001,
  BluetoothOCFInquiryCancel = 0x0002,
  BluetoothOCFPeriodicInquiryMode = 0x0003,
  BluetoothOCFExitPeriodicInquiryMode = 0x0004,
  BluetoothOCFCreateConnection = 0x0005,
  BluetoothOCFDisconnect = 0x0006,
  BluetoothOCFCreateConnectionCancel = 0x0008,
  BluetoothOCFAcceptConnectionRequest = 0x0009,
  BluetoothOCFRejectConnectionRequest = 0x000A,
  BluetoothOCFLinkKeyRequestReply = 0x000B,
  BluetoothOCFLinkKeyRequestNegativeReply = 0x000C,
  BluetoothOCFPINCodeRequestReply = 0x000D,
  BluetoothOCFPINCodeRequestNegativeReply = 0x000E,
  BluetoothOCFChangeConnectionPacketType = 0x000F,
  BluetoothOCFAuthenticationRequested = 0x0011,
  BluetoothOCFSetConnectionEncryption = 0x0013,
  BluetoothOCFChangeConnectionLinkKey = 0x0015,
  BluetoothOCFMasterLinkKey = 0x0017,
  BluetoothOCFRemoteNameRequest = 0x0019,
  BluetoothOCFRemoteNameRequestCancel = 0x001A,
  BluetoothOCFReadRemoteSupportedFeatures = 0x001B,
  BluetoothOCFReadRemoteExtendedFeatures = 0x001C,
  BluetoothOCFReadRemoteVersionInformation = 0x001D,
  BluetoothOCFReadClockOffset = 0x001F,
  BluetoothOCFReadLMPHandle = 0x0020,
  BluetoothOCFSetupSynchronousConnection = 0x0028,
  BluetoothOCFAcceptSynchronousConnectionRequest = 0x0029,
  BluetoothOCFRejectSynchronousConnectionRequest = 0x002A,
  BluetoothOCFIOCapabilityRequestReply = 0x002B,
  BluetoothOCFUserConfirmationRequestReply = 0x002C,
  BluetoothOCFUserConfirmationRequestNegativeReply = 0x002D,
  BluetoothOCFUserPasskeyRequestReply = 0x002E,
  BluetoothOCFUserPasskeyRequestNegativeReply = 0x002F,
  BluetoothOCFRemoteOOBDataRequestReply = 0x0030,
  BluetoothOCFRemoteOOBDataRequestNegativeReply = 0x0033,
  BluetoothOCFIOCapabilityRequestNegativeReply = 0x0034,
  BluetoothOCFCreatePhysicalLink = 0x0035,
  BluetoothOCFAcceptPhysicalLink = 0x0036,
  BluetoothOCFDisconnectPhysicalLink = 0x0037,
  BluetoothOCFCreateLogicalLink = 0x0038,
  BluetoothOCFAcceptLogicalLink = 0x0039,
  BluetoothOCFDisconnectLogicalLink = 0x003A,
  BluetoothOCFLogicalLinkCancel = 0x003B,
  BluetoothOCFFlowSpecModify = 0x003C,
  BluetoothOCFEnhancedSetupSynchronousConnection = 0x003D,
  BluetoothOCFEnhancedAcceptSynchronousConnectionRequest = 0x003E,
  BluetoothOCFTruncatedPage = 0x003F,
  BluetoothOCFTruncatedPageCancel = 0x0040,
  BluetoothOCFSetConnectionlessSlaveBroadcast = 0x0041,
  BluetoothOCFSetConnectionlessSlaveBroadcastReceive = 0x0042,
  BluetoothOCFStartSynchronizationTrain = 0x0043,
  BluetoothOCFReceiveSynchronizationTrain = 0x0044,
  BluetoothOCFRemoteOOBExtendedDataRequestReply = 0x0045,

  //
  // BluetoothOGFLinkPolicyCommands
  //
  BluetoothOCFHoldMode = 0x0001,
  BluetoothOCFSniffMode = 0x0003,
  BluetoothOCFExitSniffMode = 0x0004,
  BluetoothOCFParkState = 0x0005,
  BluetoothOCFExitParkState = 0x0006,
  BluetoothOCFQoSSetup = 0x0007,
  BluetoothOCFRoleDiscovery = 0x0009,
  BluetoothOCFSwitchRole = 0x000B,
  BluetoothOCFReadLinkPolicySettings = 0x000C,
  BluetoothOCFWriteLinkPolicySettings = 0x000D,
  BluetoothOCFReadDefaultLinkPolicySettings = 0x000E,
  BluetoothOCFWriteDefaultLinkPolicySettings = 0x000F,
  BluetoothOCFFlowSpecification = 0x0010,
  BluetoothOCFSniffSubrating = 0x0011,

  //
  // BluetoothOGFControllerBasebandCommands
  //
  BluetoothOCFSetEventMask = 0x0001,
  BluetoothOCFReset = 0x0003,
  BluetoothOCFSetEventFilter = 0x0005,
  BluetoothOCFFlush = 0x0008,
  BluetoothOCFReadPINType = 0x0009,
  BluetoothOCFWritePINType = 0x000A,
  BluetoothOCFCreateNewUnitKey = 0x000B,
  BluetoothOCFReadStoredLinkKey = 0x000D,
  BluetoothOCFWriteStoredLinkKey = 0x0011,
  BluetoothOCFDeleteStoredLinkKey = 0x0012,
  BluetoothOCFWriteLocalName = 0x0013,
  BluetoothOCFReadLocalName = 0x0014,
  BluetoothOCFReadConnectionAcceptTimeout = 0x0015,
  BluetoothOCFWriteConnectionAcceptTimeout = 0x0016,
  BluetoothOCFReadPageTimeout = 0x0017,
  BluetoothOCFWritePageTimeout = 0x0018,
  BluetoothOCFReadScanEnable = 0x0019,
  BluetoothOCFWriteScanEnable = 0x001A,
  BluetoothOCFReadPageScanActivity = 0x001B,
  BluetoothOCFWritePageScanActivity = 0x001C,
  BluetoothOCFReadInquiryScanActivity = 0x001D,
  BluetoothOCFWriteInquiryScanActivity = 0x001E,
  BluetoothOCFReadAuthenticationEnable = 0x001F,
  BluetoothOCFWriteAuthenticationEnable = 0x0020,
  BluetoothOCFReadClassOfDevice = 0x0023,
  BluetoothOCFWriteClassOfDevice = 0x0024,
  BluetoothOCFReadVoiceSetting = 0x0025,
  BluetoothOCFWriteVoiceSetting = 0x0026,
  BluetoothOCFReadAutomaticFlushTimeout = 0x0027,
  BluetoothOCFWriteAutomaticFlushTimeout = 0x0028,
  BluetoothOCFReadNumBroadcastRetransmissions = 0x0029,
  BluetoothOCFWriteNumBroadcastRetransmissions = 0x002A,
  BluetoothOCFReadHoldModeActivity = 0x002B,
  BluetoothOCFWriteHoldModeActivity = 0x002C,
  BluetoothOCFReadTransmitPowerLevel = 0x002D,
  BluetoothOCFReadSynchronousFlowControlEnable = 0x002E,
  BluetoothOCFWriteSynchronousFlowControlEnable = 0x002F,
  BluetoothOCFSetControllerToHostFlowControl = 0x0031,
  BluetoothOCFHostBufferSize = 0x0033,
  BluetoothOCFHostNumberOfCompletedPackets = 0x0035,
  BluetoothOCFReadLinkSupervisionTimeout = 0x0036,
  BluetoothOCFWriteLinkSupervisionTimeout = 0x0037,
  BluetoothOCFReadNumberOfSupportedIAC = 0x0038,
  BluetoothOCFReadCurrentIACLAP = 0x0039,
  BluetoothOCFWriteCurrentIACLAP = 0x003A,
  BluetoothOCFSetAFHHostChannelClassification = 0x003F,
  BluetoothOCFReadInquiryScanType = 0x0042,
  BluetoothOCFWriteInquiryScanType = 0x0043,
  BluetoothOCFReadInquiryMode = 0x0044,
  BluetoothOCFWriteInquiryMode = 0x0045,
  BluetoothOCFReadPageScanType = 0x0046,
  BluetoothOCFWritePageScanType = 0x0047,
  BluetoothOCFReadAFHChannelAssessmentMode = 0x0048,
  BluetoothOCFWriteAFHChannelAssessmentMode = 0x0049,
  BluetoothOCFReadExtendedInquiryResponse = 0x0051,
  BluetoothOCFWriteExtendedInquiryResponse = 0x0052,
  BluetoothOCFRefreshEncryptionKey = 0x0053,
  BluetoothOCFReadSimplePairingMode = 0x0055,
  BluetoothOCFWriteSimplePairingMode = 0x0056,
  BluetoothOCFReadLocalOOBData = 0x0057,
  BluetoothOCFReadInquiryResponseTransmitPowerLevel = 0x0058,
  BluetoothOCFWriteInquiryTransmitPowerLevel = 0x0059,
  BluetoothOCFSendKeypressNotification = 0x0060,
  BluetoothOCFReadDefaultErroneousDataReporting = 0x005A,
  BluetoothOCFWriteDefaultErroneousDataReporting = 0x005B,
  BluetoothOCFEnhancedFlush = 0x005F,
  BluetoothOCFReadLogicalLinkAcceptTimeout = 0x0061,
  BluetoothOCFWriteLogicalLinkAcceptTimeout = 0x0062,
  BluetoothOCFSetEventMaskPage2 = 0x0063,
  BluetoothOCFReadLocationData = 0x0064,
  BluetoothOCFWriteLocationData = 0x0065,
  BluetoothOCFReadFlowControlMode = 0x0066,
  BluetoothOCFWriteFlowControlMode = 0x0067,
  BluetoothOCFReadEnhancedTransmitPowerLevel = 0x0068,
  BluetoothOCFReadBestEffortFlushTimeout = 0x0069,
  BluetoothOCFWriteBestEffortFlushTimeout = 0x006A,
  BluetoothOCFShortRangeMode = 0x006B,
  BluetoothOCFReadLEHostSupported = 0x006C,
  BluetoothOCFWriteLEHostSupported = 0x006D,
  BluetoothOCFSetMWSChannelParameters = 0x006E,
  BluetoothOCFSetExternalFrameConfiguration = 0x006F,
  BluetoothOCFSetMWSSignalingCommand = 0x0070,
  BluetoothOCFSetMWSTransportLayer = 0x0071,
  BluetoothOCFSetMWSScanFrequencyTable = 0x0072,
  BluetoothOCFSetMWS_PATTERNConfiguration = 0x0073,
  BluetoothOCFSetReservedLT_ADDR = 0x0074,
  BluetoothOCFDeleteReservedLT_ADDR = 0x0075,
  BluetoothOCFSetConnectionlessSlaveBroadcastData = 0x0076,
  BluetoothOCFReadSynchronizationTrainParameters = 0x0077,
  BluetoothOCFWriteSynchronizationTrainParameters = 0x0078,
  BluetoothOCFReadSecureConnectionsHostSupport = 0x0079,
  BluetoothOCFWriteSecureConnectionsHostSupport = 0x007A,
  BluetoothOCFReadAuthenticatedPayloadTimeout = 0x007B,
  BluetoothOCFWriteAuthenticatedPayloadTimeout = 0x007C,
  BluetoothOCFReadLocalOOBExtendedData = 0x007D,
  BluetoothOCFReadExtendedPageTimeout = 0x007E,
  BluetoothOCFWriteExtendedPageTimeout = 0x007F,
  BluetoothOCFReadExtendedInquiryLength = 0x0080,
  BluetoothOCFWriteExtendedInquiryLength = 0x0081,

  //
  // BluetoothOGFInformationalParameters
  //
  BluetoothOCFReadLocalVersionInformation = 0x0001,
  BluetoothOCFReadLocalSupportedCommands = 0x0002,
  BluetoothOCFReadLocalSupportedFeatures = 0x0003,
  BluetoothOCFReadLocalExtendedFeatures = 0x0004,
  BluetoothOCFReadBufferSize = 0x0005,
  BluetoothOCFReadBD_ADDR = 0x0009,
  BluetoothOCFReadDataBlockSize = 0x000A,
  BluetoothOCFReadLocalSupportedCodecs = 0x000B,

  //
  // BluetoothOGFStatusParameters
  //
  BluetoothOCFReadFailedContactCounter = 0x0001,
  BluetoothOCFResetFailedContactCounter = 0x0002,
  BluetoothOCFReadLinkQuality = 0x0003,
  BluetoothOCFReadRSSI = 0x0005,
  BluetoothOCFReadAFHChannelMap = 0x0006,
  BluetoothOCFReadClock = 0x0007,
  BluetoothOCFReadEncryptionKeySize = 0x0008,
  BluetoothOCFReadLocalAMPInfo = 0x0009,
  BluetoothOCFReadLocalAMPASSOC = 0x000A,
  BluetoothOCFWriteRemoteAMPASSOC = 0x000B,
  BluetoothOCFGetMWSTransportLayerConfiguration = 0x000C,
  BluetoothOCFSetTriggeredClockCapture = 0x000D,

  //
  // BluetoothOGFTestingCommands
  //
  BluetoothOCFReadLoopbackMode = 0x0001,
  BluetoothOCFWriteLoopbackMode = 0x0002,
  BluetoothOCFEnableDeviceUnderTestMode = 0x0003,
  BluetoothOCFWriteSimplePairingDebugMode = 0x0004,
  BluetoothOCFEnableAMPReceiverReports = 0x0007,
  BluetoothOCFAMPTestEnd = 0x0008,
  BluetoothOCFAMPTest = 0x0009,
  BluetoothOCFWriteSecureConnectionsTestMode = 0x000A,

  //
  // BluetoothOGFLEControllerCommands
  //
  BluetoothOCFLESetEventMask = 0x0001,
  BluetoothOCFLEReadBufferSize = 0x0002,
  BluetoothOCFLEReadLocalSupportedFeatures = 0x0003,
  BluetoothOCFLESetRandomAddress = 0x0005,
  BluetoothOCFLESetAdvertisingParameters = 0x0006,
  BluetoothOCFLEReadAdvertisingChannelTxPower = 0x0007,
  BluetoothOCFLESetAdvertisingData = 0x0008,
  BluetoothOCFLESetScanResponseData = 0x0009,
  BluetoothOCFLESetAdvertiseEnable = 0x000A,
  BluetoothOCFLESetScanParameters = 0x000B,
  BluetoothOCFLESetScanEnable = 0x000C,
  BluetoothOCFLECreateConnection = 0x000D,
  BluetoothOCFLECreateConnectionCancel = 0x000E,
  BluetoothOCFLEReadWhiteListSize = 0x000F,
  BluetoothOCFLEClearWhiteList = 0x0010,
  BluetoothOCFLEAddDeviceToWhiteList = 0x0011,
  BluetoothOCFLERemoveDeviceFromWhiteList = 0x0012,
  BluetoothOCFLEConnectionUpdate = 0x0013,
  BluetoothOCFLESetHostChannelClassification = 0x0014,
  BluetoothOCFLEReadChannelMap = 0x0015,
  BluetoothOCFLEReadRemoteUsedFeatures = 0x0016,
  BluetoothOCFLEEncrypt = 0x0017,
  BluetoothOCFLERand = 0x0018,
  BluetoothOCFLEStartEncryption = 0x0019,
  BluetoothOCFLELongTermKeyRequestReply = 0x001A,
  BluetoothOCFLELongTermKeyRequestNegativeReply = 0x001B,
  BluetoothOCFLEReadSupportedStates = 0x001C,
  BluetoothOCFLEReceiverTest = 0x001D,
  BluetoothOCFLETransmitterTest = 0x001E,
  BluetoothOCFLETestEnd = 0x001F,
  BluetoothOCFLERemoteConnectionParameterRequestReply = 0x0020,
  BluetoothOCFLERemoteConnectionParameterRequestNegativeReply = 0x0021,

} BLUETOOTH_OCF;

typedef enum {
  BluetoothEventInquiryComplete = 0x01,
  BluetoothEventInquiryResult = 0x02,
  BluetoothEventConnectionComplete = 0x03,
  BluetoothEventConnectionRequest = 0x04,
  BluetoothEventDisconnectionComplete = 0x05,
  BluetoothEventAuthenticationComplete = 0x06,
  BluetoothEventRemoteNameRequestComplete = 0x07,
  BluetoothEventEncryptionChange = 0x08,
  BluetoothEventChangeConnectionLinkKeyComplete = 0x09,
  BluetoothEventMasterLinkKeyComplete = 0x0A,
  BluetoothEventReadRemoteSupportedFeaturesComplete = 0x0B,
  BluetoothEventReadRemoteVersionInformationComplete = 0x0C,
  BluetoothEventQoSSetupComplete = 0x0D,
  BluetoothEventCommandComplete = 0x0E,
  BluetoothEventCommandStatus = 0x0F,
  BluetoothEventHardwareError = 0x10,
  BluetoothEventFlushOccurred = 0x11,
  BluetoothEventRoleChange = 0x12,
  BluetoothEventNumberOfCompletedPackets = 0x13,
  BluetoothEventModeChange = 0x14,
  BluetoothEventReturnLinkKeys = 0x15,
  BluetoothEventPINCodeRequest= 0x16,
  BluetoothEventLinkKeyRequest = 0x17,
  BluetoothEventLinkKeyNotification = 0x18,
  BluetoothEventLoopbackCommand = 0x19,
  BluetoothEventDataBufferOverflow = 0x1A,
  BluetoothEventMaxSlotsChange = 0x1B,
  BluetoothEventReadClockOffsetComplete = 0x1C,
  BluetoothEventConnectionPacketTypeChanged = 0x1D,
  BluetoothEventQoSViolation = 0x1E,
  BluetoothEventPageScanRepetitionModeChange = 0x20,
  BluetoothEventFlowSpecificationComplete = 0x21,
  BluetoothEventInquiryResultWithRSSI = 0x22,
  BluetoothEventReadRemoteExtendedFeaturesComplete = 0x23,
  BluetoothEventSynchronousConnectionComplete = 0x24,
  BluetoothEventSynchronousConnectionChanged = 0x2D,
  BluetoothEventSniffSubrating = 0x2E,
  BluetoothEventExtendedInquiryResult = 0x2F,
  BluetoothEventEncryptionKeyRefreshComplete = 0x30,
  BluetoothEventIOCapabilityRequest = 0x31,
  BluetoothEventIOCapabilityResponse = 0x32,
  BluetoothEventUserConfirmationRequest = 0x33,
  BluetoothEventUserPasskeyRequest = 0x34,
  BluetoothEventRemoteOOBDataRequest = 0x35,
  BluetoothEventSimplePairingComplete = 0x36,
  BluetoothEventLinkSupervisionTimeoutChanged = 0x38,
  BluetoothEventEnhancedFlushComplete = 0x39,
  BluetoothEventUserPasskeyNotification = 0x3B,
  BluetoothEventKeypressNotification = 0x3C,
  BluetoothEventRemoteHostSupportedFeaturesNotification = 0x3D,
  BluetoothEventPhysicalLinkComplete = 0x40,
  BluetoothEventChannelSelected = 0x41,
  BluetoothEventDisconnectionPhysicalLinkComplete = 0x42,
  BluetoothEventPhysicalLinkLossEarlyWarning = 0x43,
  BluetoothEventPhysicalLinkRecovery = 0x44,
  BluetoothEventLogicalLinkComplete = 0x45,
  BluetoothEventDisconnectionLogicalLinkComplete = 0x46,
  BluetoothEventFlowSpecModifyComplete = 0x47,
  BluetoothEventNumberOfCompletedDataBlocks = 0x48,
  BluetoothEventShortRangeModeChangeComplete = 0x4C,
  BluetoothEventAMPStatusChange = 0x4D,
  BluetoothEventAMPStartTest = 0x49,
  BluetoothEventAMPTestEnd = 0x4A,
  BluetoothEventAMPReceiverReport = 0x4B,
  BluetoothEventTriggeredClockCapture = 0x4E,
  BluetoothEventSynchronizationTrainComplete = 0x4F,
  BluetoothEventSynchronizationTrainReceived = 0x50,
  BluetoothEventConnectionlessSlaveBroadcastReceive = 0x51,
  BluetoothEventConnectionlessSlaveBroadcastTimeout = 0x52,
  BluetoothEventTruncatedPageComplete = 0x53,
  BluetoothEventSlavePageResponseTimeout = 0x54,
  BluetoothEventConnectionlessSlaveBroadcastChannelMapChange = 0x55,
  BluetoothEventInquiryResponseNotification = 0x56,
  BluetoothEventAuthenticatedPayloadTimeoutExpired = 0x57,

  BluetoothEventLEMeta = 0x3E,
} BLUETOOTH_EVENT;

typedef enum {
  BluetoothEventLEConnectionComplete = 0x01,
  BluetoothEventLEAdvertisingReport = 0x02,
  BluetoothEventLEConnectionUpdateComplete = 0x03,
  BluetoothEventLEReadRemoteUsedFeaturesComplete = 0x04,
  BluetoothEventLELongTermKeyRequest = 0x05,
  BluetoothEventLERemoteConnectionParameterRequest = 0x06,
} BLUETOOTH_LE_EVENT;

typedef struct {
  UINT16  OCF:10;
  UINT16  OGF:6;
  UINT8   ParameterTotalLength;
} BLUETOOTH_HCI_COMMAND_HEADER;

typedef struct {
  UINT16  OCF:10;
  UINT16  OGF:6;
} BLUETOOTH_HCI_OPCODE;

typedef struct {
  UINT16  Handle:12;
  UINT16  PacketBoundaryFlag:2;
  UINT16  BroadcastFlag:2;
  UINT16  DataTotalLength;
} BLUETOOTH_HCI_ACL_DATA_HEADER;

typedef struct {
  UINT16  ConnectionHandle:12;
  UINT16  PacketStatusFlag:2;
  UINT16  Reserved:2;
  UINT8   DataTotalLength;
} BLUETOOTH_HCI_SYNCHRONOUS_DATA_HEADER;

typedef struct {
  UINT8   EventCode;
  UINT8   ParameterTotalLength;
} BLUETOOTH_HCI_EVENT_HEADER;

#define BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE 248

//
// HCI Event
//
typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       Status;
} BLUETOOTH_HCI_EVENT_INQUIRY_COMPLETE;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       Status;
  UINT16                      ConnectionHandle;
  BLUETOOTH_ADDRESS           BDAddr;
  UINT8                       LinkType;
  UINT8                       EncryptionEnabled;
} BLUETOOTH_HCI_EVENT_CONNECTION_COMPLETE;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  BLUETOOTH_ADDRESS           BDAddr;
  BLUETOOTH_CLASS_OF_DEVICE   ClassOfDevice;
  UINT8                       LinkType;
} BLUETOOTH_HCI_EVENT_CONNECTION_REQUEST;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       Status;
  UINT16                      ConnectionHandle;
  UINT8                       Reason;
} BLUETOOTH_HCI_EVENT_DISCONNECTION_COMPLETE;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       Status;
  UINT16                      ConnectionHandle;
}BLUETOOTH_HCI_EVENT_AUTHENTICATION_COMPLETE;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       Status;
  BLUETOOTH_ADDRESS           BDAddr;
  UINT8                       RemoteName[BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE];
} BLUETOOTH_HCI_EVENT_REMOTE_NAME_REQUEST_COMPLETE;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       Status;
  UINT16                      ConnectionHandle;
  UINT8                       EncryptEnable;
} BLUETOOTH_HCI_EVENT_ENCRYPTION_CHANGE;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       Status;
  UINT16                      ConnectionHandle;
  UINT64                      LMPFeatures;
} BLUETOOTH_HCI_EVENT_READ_REMOVE_SUPPORTED_FEATURE_COMPLETE;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       Status;
  UINT16                      ConnectionHandle;
  UINT8                       Flags;
  UINT8                       ServiceType;
  UINT32                      TokenRate;
  UINT32                      PeakBandwidth;
  UINT32                      Latency;
  UINT32                      DelayVariation;
} BLUETOOTH_HCI_EVENT_QOS_SETUP_COMPLETE;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       NumHCICommandPackets;
  UINT16                      OCF:10;
  UINT16                      OGF:6;
} BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       Status;
  UINT8                       NumHCICommandPackets;
  UINT16                      OCF:10;
  UINT16                      OGF:6;
} BLUETOOTH_HCI_EVENT_COMMAND_STATUS;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       HardwareCode;
} BLUETOOTH_HCI_EVENT_HARDWARE_ERROR;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       NumberOfHandles;
  UINT16                      ConnectionHandle[1];
  UINT16                      HCNumOfCompletedPackets[1];
} BLUETOOTH_HCI_EVENT_NUMBER_OF_COMPLETED_PACKETS;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       Status;
  UINT16                      ConnectionHandle;
  UINT8                       CurrentMode;
  UINT16                      Interval;
} BLUETOOTH_HCI_EVENT_MODE_CHANGE;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  BLUETOOTH_ADDRESS           BDAddr;
} BLUETOOTH_HCI_EVENT_PIN_CODE_REQUEST;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  BLUETOOTH_ADDRESS           BDAddr;
} BLUETOOTH_HCI_EVENT_LINK_KEY_REQUEST;

#define BLUETOOTH_HCI_LINK_KEY_SIZE 16

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  BLUETOOTH_ADDRESS           BDAddr;
  UINT8                       LinkKey[BLUETOOTH_HCI_LINK_KEY_SIZE];
  UINT8                       KeyType;
} BLUETOOTH_HCI_EVENT_LINK_KEY_NOTIFICATION;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       NumResponses;
  BLUETOOTH_ADDRESS           BDAddr[1];
  UINT8                       PageScanRepetitionMode[1];
  UINT8                       Reserved[1];
  BLUETOOTH_CLASS_OF_DEVICE   ClassOfDevice[1];
  UINT16                      ClockOffset[1];
  UINT8                       RSSI[1];
} BLUETOOTH_HCI_EVENT_INQUIRY_RESULT_WITH_RSSI;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  UINT8                       NumResponses;
  BLUETOOTH_ADDRESS           BDAddr;
  UINT8                       PageScanRepetitionMode;
  UINT8                       Reserved;
  BLUETOOTH_CLASS_OF_DEVICE   ClassOfDevice;
  UINT16                      ClockOffset;
  UINT8                       RSSI;
  UINT8                       ExtendedInquiryResponse[240];
} BLUETOOTH_HCI_EVENT_EXTENDED_INQUIRY_RESULT;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  BLUETOOTH_ADDRESS           BDAddr;
} BLUETOOTH_HCI_EVENT_IO_CAPABILITY_REQUEST;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  BLUETOOTH_ADDRESS           BDAddr;
  UINT32                      NumericValue;
} BLUETOOTH_HCI_EVENT_USER_CONFIRMATION_REQUEST;

typedef struct {
  BLUETOOTH_HCI_EVENT_HEADER  Header;
  BLUETOOTH_ADDRESS           BDAddr;
  UINT32                      Passkey;
} BLUETOOTH_HCI_EVENT_USER_PASSKEY_NOTIFICATION;

//
// HCI Command
//
typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT8                         LAP[3];
  UINT8                         InquiryLength;
  UINT8                         NumResponses;
} BLUETOOTH_HCI_COMMAND_INQUIRY;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
} BLUETOOTH_HCI_RESPONSE_INQUIRY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_INQUIRY_CANCEL;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_INQUIRY_CANCEL;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
  UINT16                        PacketType;
  UINT8                         PageScanRepetitionMode;
  UINT8                         Reserved;
  UINT16                        ClockOffset;
  UINT8                         AllowRoleSwitch;
} BLUETOOTH_HCI_COMMAND_CREATE_CONNECTION;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
} BLUETOOTH_HCI_RESPONSE_CREATE_CONNECTION;

typedef enum {
  BluetoothDisconnectReasonTypeAuthenticationFailure  = 0x05,
  BluetoothDisconnectReasonTypeRemoteUserTerminatedConnection = 0x13,
  BluetoothDisconnectReasonTypeRemoteDeviceTerminatedConnectionDueToLowResources = 0x14,
  BluetoothDisconnectReasonTypeRemoteDeviceTerminatedConnectionDueToPowerOff = 0x15,
  BluetoothDisconnectReasonTypeUnsupportedRemoteFeature = 0x1A,
  BluetoothDisconnectReasonTypePairingWithUnitKeyNotSupported = 0x29
} BLUETOOTH_HCI_DISCONNECT_REASON_TYPE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT16                        ConnectionHandle;
  UINT8                         Reason;
} BLUETOOTH_HCI_COMMAND_DISCONNECT;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
  UINT8                         Role;
} BLUETOOTH_HCI_COMMAND_ACCEPT_CONNECTION_REQUEST;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
  UINT8                         LinkKey[BLUETOOTH_HCI_LINK_KEY_SIZE];
} BLUETOOTH_HCI_COMMAND_LINK_KEY_REQUEST_REPLY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
} BLUETOOTH_HCI_COMMAND_LINK_KEY_REQUEST_NEGATIVE_REPLY;

#define BLUETOOTH_HCI_PIN_CODE_MAX_SIZE 16

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
  UINT8                         PinCodeLength;
  UINT8                         PinCode[BLUETOOTH_HCI_PIN_CODE_MAX_SIZE];
} BLUETOOTH_HCI_COMMAND_PIN_CODE_REQUEST_REPLY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
} BLUETOOTH_HCI_COMMAND_PIN_CODE_REQUEST_NEGATIVE_REPLY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT16                        ConnectionHandle;
} BLUETOOTH_HCI_COMMAND_AUTHENTICATION_REQUESTED;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT16                        ConnectionHandle;
  UINT8                         EncryptionEnable;
} BLUETOOTH_HCI_COMMAND_SET_CONNECTION_ENCRYPTION;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
  UINT8                         PageScanRepetitionMode;
  UINT8                         Reserved;
  UINT16                        ClockOffset;
} BLUETOOTH_HCI_COMMAND_REMOTE_NAME_REQUEST;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
} BLUETOOTH_HCI_RESPONSE_REMOTE_NAME_REQUEST;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT16                        ConnectionHandle;
} BLUETOOTH_HCI_COMMAND_READ_REMOTE_SUPPORTED_FEATURES;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
} BLUETOOTH_HCI_RESPONSE_READ_REMOTE_SUPPORTED_FEATURES;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
  UINT8                         IOCapabiltiy;
  UINT8                         OOBDataPresent;
  UINT8                         AuthReq;
} BLUETOOTH_HCI_COMMAND_IO_CAPABILITY_REQUEST_REPLY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
} BLUETOOTH_HCI_COMMAND_USER_CONFIRMATION_REQUEST_REPLY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
} BLUETOOTH_HCI_COMMAND_USER_CONFIRMATION_REQUEST_NEGATIVE_REPLY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT16                        ConnectionHandle;
} BLUETOOTH_HCI_COMMAND_EXIT_SNIFF_MODE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
} BLUETOOTH_HCI_RESPONSE_EXIT_SNIFF_MODE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT16                        DefaultLinkPolicySettings;
} BLUETOOTH_HCI_COMMAND_WRITE_DEFAULT_LINK_POLICY_SETTINGS;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                  Status;
} BLUETOOTH_HCI_RESPONSE_WRITE_DEFAULT_LINK_POLICY_SETTINGS;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT64                        EventMask;
} BLUETOOTH_HCI_COMMAND_SET_EVENT_MASK;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                  Status;
} BLUETOOTH_HCI_RESPONSE_SET_EVENT_MASK;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_RESET;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_RESET;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT8                         FilterType;
  UINT8                         InquiryResultFilterConditionType;
  UINT8                         ConnectionSetupFilterConditionType;
} BLUETOOTH_HCI_COMMAND_SET_EVENT_FILTER;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_SET_EVENT_FILTER;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
  UINT8                         ReadAllFlag;
} BLUETOOTH_HCI_COMMAND_READ_STORED_LINK_KEY;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT16                                MaxNumKeys;
  UINT16                                NumKeysRead;
} BLUETOOTH_HCI_RESPONSE_READ_STORED_LINK_KEY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT8                         NumKeysToWrite;
  BLUETOOTH_ADDRESS             BDAddr;
  UINT8                         LinkKey[BLUETOOTH_HCI_LINK_KEY_SIZE];
} BLUETOOTH_HCI_COMMAND_WRITE_STORED_LINK_KEY;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 NumKeysWritten;
} BLUETOOTH_HCI_RESPONSE_WRITE_STORED_LINK_KEY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_ADDRESS             BDAddr;
  UINT8                         DeleteAllFlag;
} BLUETOOTH_HCI_COMMAND_DELETE_STORED_LINK_KEY;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT16                                NumKeysDeleted;
} BLUETOOTH_HCI_RESPONSE_DELETE_STORED_LINK_KEY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT8                         LocalName[BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE];
} BLUETOOTH_HCI_COMMAND_WRITE_LOCAL_NAME;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_WRITE_LOCAL_NAME;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_LOCAL_NAME;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 LocalName[BLUETOOTH_HCI_COMMAND_LOCAL_READABLE_NAME_MAX_SIZE];
} BLUETOOTH_HCI_RESPONSE_READ_LOCAL_NAME;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT16                        ConnAcceptTimeout;
} BLUETOOTH_HCI_COMMAND_WRITE_CONNECTION_ACCEPT_TIMEOUT;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_WRITE_CONNECTION_ACCEPT_TIMEOUT;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT16                        PageTimeout;
} BLUETOOTH_HCI_COMMAND_WRITE_PAGE_TIMEOUT;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_WRITE_PAGE_TIMEOUT;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_SCAN_ENABLE;

typedef enum {
  BluetoothScanEnableTypeNoScansEnabled = 0x00,
  BluetoothScanEnableTypeOnlyInquiryScanEnabled = 0x01,
  BluetoothScanEnableTypeOnlyPageScanEnabled = 0x02,
  BluetoothScanEnableTypeBothPageInquiryScanEnabled = 0x03,
} BLUETOOTH_SCAN_ENABLE_TYPE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 ScanEnable;
} BLUETOOTH_HCI_RESPONSE_READ_SCAN_ENABLE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT8                         ScanEnable;
} BLUETOOTH_HCI_COMMAND_WRITE_SCAN_ENABLE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_WRITE_SCAN_ENABLE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_PAGE_SCAN_ACTIVITY;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT16                                PageScanInterval;
  UINT16                                PageScanWindow;
} BLUETOOTH_HCI_RESPONSE_READ_PAGE_SCAN_ACTIVITY;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_CLASS_OF_DEVICE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  BLUETOOTH_CLASS_OF_DEVICE             ClassOfDevice;
} BLUETOOTH_HCI_RESPONSE_READ_CLASS_OF_DEVICE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  BLUETOOTH_CLASS_OF_DEVICE     ClassOfDevice;
} BLUETOOTH_HCI_COMMAND_WRITE_CLASS_OF_DEVICE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_WRITE_CLASS_OF_DEVICE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_VOICE_SETTING;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT16                                VoiceSetting;
} BLUETOOTH_HCI_RESPONSE_READ_VOICE_SETTING;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT8                         InquiryMode;
} BLUETOOTH_HCI_COMMAND_WRITE_INQUIRY_MODE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_WRITE_INQUIRY_MODE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_PAGE_SCAN_TYPE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 PageScanType;
} BLUETOOTH_HCI_RESPONSE_READ_PAGE_SCAN_TYPE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT8                         FECRequired;
  UINT8                         ExtendedInquiryResponse[240];
} BLUETOOTH_HCI_COMMAND_WRITE_EXTENDED_INQUIRY_RESPONSE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_WRITE_EXTENDED_INQUIRY_RESPONSE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_SIMPLE_PAIRING_MODE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 SimplePairingMode;
} BLUETOOTH_HCI_RESPONSE_READ_SIMPLE_PAIRING_MODE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT8                         SimplePairingMode;
} BLUETOOTH_HCI_COMMAND_WRITE_SIMPLE_PAIRING_MODE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_WRITE_SIMPLE_PAIRING_MODE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_INQUIRY_RESPONSE_TRANSMIT_POWER_LEVEL;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 TXPower;
} BLUETOOTH_HCI_RESPONSE_READ_INQUIRY_RESPONSE_TRANSMIT_POWER_LEVEL;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_LOCAL_VERSION_INFORMATION;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 HCIVersion;
  UINT16                                HCIRevision;
  UINT8                                 LMPPALVersion;
  UINT16                                ManufacturerName;
  UINT16                                LMPPALSubversion;
} BLUETOOTH_HCI_RESPONSE_READ_LOCAL_VERSION_INFORMATION;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_LOCAL_SUPPORTED_COMMANDS;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 SupportedCommands[64];
} BLUETOOTH_HCI_RESPONSE_READ_LOCAL_SUPPORTED_COMMANDS;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_LOCAL_SUPPORTED_FEATURES;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT64                                LMPFeatures;
} BLUETOOTH_HCI_RESPONSE_READ_LOCAL_SUPPORTED_FEATURES;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT8                         PageNumber;
} BLUETOOTH_HCI_COMMAND_READ_LOCAL_EXTENDED_FEATURES;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 PageNumber;
  UINT8                                 MaximumPageNumber;
  UINT64                                ExtendedLMPFeatures;
} BLUETOOTH_HCI_RESPONSE_READ_LOCAL_EXTENDED_FEATURES;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_BUFFER_SIZE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT16                                HCACLDataPacketLength;
  UINT8                                 HCSynchronousDataPacketLength;
  UINT16                                HCTotalNumACLDataPackets;
  UINT16                                HCTotalNumSynchronousDataPackets;
} BLUETOOTH_HCI_RESPONSE_READ_BUFFER_SIZE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_BD_ADDR;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  BLUETOOTH_ADDRESS                     BDAddr;
} BLUETOOTH_HCI_RESPONSE_READ_BD_ADDR;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_READ_DATA_BLOCK_SIZE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT16                                MaxACLDataPacketLength;
  UINT16                                DataBlockLength;
  UINT16                                TotalNumDataBlocks;
} BLUETOOTH_HCI_RESPONSE_READ_DATA_BLOCK_SIZE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_LE_READ_BUFFER_SIZE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT16                                HcLeDataPacketLength;
  UINT8                                 HcTotalNumLeDataPackets;
} BLUETOOTH_HCI_RESPONSE_LE_READ_BUFFER_SIZE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_LE_READ_LOCAL_SUPPORTED_FEATURES;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT64                                LeFeatures;
} BLUETOOTH_HCI_RESPONSE_LE_READ_LOCAL_SUPPORTED_FEATURES;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_LE_READ_ADVERTISING_CHANNEL_TX_POWER;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 TransmitPowerLevel;
} BLUETOOTH_HCI_RESPONSE_LE_READ_ADVERTISING_CHANNEL_TX_POWER;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_LE_READ_WHITE_LIST_SIZE;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT8                                 WhiteListSize;
} BLUETOOTH_HCI_RESPONSE_LE_READ_WHITE_LIST_SIZE;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
} BLUETOOTH_HCI_COMMAND_LE_READ_SUPPORTED_STATES;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
  UINT64                                LeStates;
} BLUETOOTH_HCI_RESPONSE_LE_READ_SUPPORTED_STATES;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT64                        LeEventMask;
} BLUETOOTH_HCI_COMMAND_LE_SET_EVENT_MASK;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_LE_SET_EVENT_MASK;

typedef struct {
  BLUETOOTH_HCI_COMMAND_HEADER  Header;
  UINT8                         AdvertisingDataLength;
  UINT8                         AdvertisingData[31];
} BLUETOOTH_HCI_COMMAND_LE_SET_ADVERTISING_DATA;

typedef struct {
  BLUETOOTH_HCI_EVENT_COMMAND_COMPLETE  Header;
  UINT8                                 Status;
} BLUETOOTH_HCI_RESPONSE_LE_SET_ADVERTISING_DATA;

#pragma pack()

#endif


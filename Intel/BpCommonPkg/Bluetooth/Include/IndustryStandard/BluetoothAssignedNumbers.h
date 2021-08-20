//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Definitions for Bluetooth standard.

Copyright (c) 2013 - 2017, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef __BLUETOOTH_ASSIGNED_NUMBERS_H__
#define __BLUETOOTH_ASSIGNED_NUMBERS_H__

#pragma pack(1)

//
// 1. Baseband
//
#define BLUETOOTH_LAP_INQUIRY_GENERIC 0x9E8B33
#define BLUETOOTH_LAP_INQUIRY_LIMITED 0x9E8B00

#define BLUETOOTH_COD_MAJOR_SERVICE_LIMITED_DISCOVERABLE_MODE 0x1
#define BLUETOOTH_COD_MAJOR_SERVICE_POSITIONING               0x8
#define BLUETOOTH_COD_MAJOR_SERVICE_NETWORKING                0x10
#define BLUETOOTH_COD_MAJOR_SERVICE_RENDERING                 0x20
#define BLUETOOTH_COD_MAJOR_SERVICE_CAPTURING                 0x40
#define BLUETOOTH_COD_MAJOR_SERVICE_OBJECT_TRANSFER           0x80
#define BLUETOOTH_COD_MAJOR_SERVICE_AUDIO                     0x100
#define BLUETOOTH_COD_MAJOR_SERVICE_TELEPHONY                 0x200
#define BLUETOOTH_COD_MAJOR_SERVICE_INFORMATION               0x400

typedef enum {
  BluetoothMajorClassMiscellaneous = 0x0,
  BluetoothMajorClassComputer = 0x1,
  BluetoothMajorClassPhone = 0x2,
  BluetoothMajorClassLan = 0x3,
  BluetoothMajorClassAudioVideo = 0x4,
  BluetoothMajorClassPeripheral = 0x5,
  BluetoothMajorClassImaging = 0x6,
  BluetoothMajorClassWearable = 0x7,
  BluetoothMajorClassToy = 0x8,
  BluetoothMajorClassHealth = 0x9,
  BluetoothMajorClassUncategorized = 0x1F,
} BLUETOOTH_COD_MAJOR_CLASS;

typedef enum {
  BluetoothMinorClassUncategorized = 0x0,

  //
  // BluetoothMajorClassComputer
  //
  BluetoothMinorClassDesktopWorkstation = 0x1,
  BluetoothMinorClassServerClassComputer = 0x2,
  BluetoothMinorClassLaptop = 0x3,
  BluetoothMinorClassHandheldPCPDA = 0x4,
  BluetoothMinorClassPalmSizePCPDA = 0x5,
  BluetoothMinorClassWearableComputer = 0x6,
  BluetoothMinorClassTablet = 0x7,

  //
  // BluetoothMajorClassPhone
  //
  BluetoothMinorClassCellular = 0x1,
  BluetoothMinorClassCordless = 0x2,
  BluetoothMinorClassSmartphone = 0x3,
  BluetoothMinorClassWiredModemOrVoiceGateway = 0x4,
  BluetoothMinorClassCommonISDNAccess = 0x5,

  //
  // BluetoothMajorClassAudioVideo
  //
  BluetoothMinorClassWearableHeadsetDevice = 0x1,
  BluetoothMinorClassHandsFreeDevice = 0x2,
  BluetoothMinorClassMicrophone = 0x4,
  BluetoothMinorClassLoudspeaker = 0x5,
  BluetoothMinorClassHeadphones = 0x6,
  BluetoothMinorClassPortableAudio = 0x7,
  BluetoothMinorClassCarAudio = 0x8,
  BluetoothMinorClassSetTopBox = 0x9,
  BluetoothMinorClassHiFiAudioDevice = 0xA,
  BluetoothMinorClassVCR = 0xB,
  BluetoothMinorClassVideoCamera = 0xC,
  BluetoothMinorClassCamcorder = 0xD,
  BluetoothMinorClassVideoMonitor = 0xE,
  BluetoothMinorClassVideoDisplayAndLoudspeaker = 0xF,
  BluetoothMinorClassVideoConferencing = 0x10,
  BluetoothMinorClassGamingToy = 0x12,

  //
  // BluetoothMajorClassPeripheral
  //

  //  (bit2 ~ 5)
  BluetoothMinorClassJoystick = 0x1,
  BluetoothMinorClassGamepad = 0x2,
  BluetoothMinorClassRemoteControl = 0x3,
  BluetoothMinorClassSensingDevice = 0x4,
  BluetoothMinorClassDigitizerTablet = 0x5,
  BluetoothMinorClassCardReader = 0x6,
  BluetoothMinorClassDigitalPen = 0x7,
  BluetoothMinorClassHandheldScannerForBarcodesRFID = 0x8,
  BluetoothMinorClassHandheldGesturalInputDevice = 0x9,

  //  (bit6 ~ 7)
  BluetoothMinorClassBitKeyboard = 0x10,
  BluetoothMinorClassBitPointingDevice = 0x20,

  //
  // BluetoothMajorClassImaging
  //

  //  (bit4 ~ 7)
  BluetoothMinorClassBitDisplay = 0x4,
  BluetoothMinorClassBitCamera = 0x8,
  BluetoothMinorClassBitScanner = 0x10,
  BluetoothMinorClassBitPrinter = 0x20,

  //
  // BluetoothMajorClassWearable
  //
  BluetoothMinorClassWristwatch = 0x1,
  BluetoothMinorClassPager = 0x2,
  BluetoothMinorClassJacket = 0x3,
  BluetoothMinorClassHelmet = 0x4,
  BluetoothMinorClassGlasses = 0x5,

  //
  // BluetoothMajorClassToy
  //
  BluetoothMinorClassRobot = 0x1,
  BluetoothMinorClassVehicle = 0x2,
  BluetoothMinorClassDollActionFigure = 0x3,
  BluetoothMinorClassController = 0x4,
  BluetoothMinorClassGame = 0x5,

  //
  // BluetoothMajorClassHealth
  //
  BluetoothMinorClassBloodPressureMonitor = 0x1,
  BluetoothMinorClassThermometer = 0x2,
  BluetoothMinorClassWeighingScale = 0x3,
  BluetoothMinorClassGlucoseMeter = 0x4,
  BluetoothMinorClassPulseOximeter = 0x5,
  BluetoothMinorClassHeartPulseRateMonitor = 0x6,
  BluetoothMinorClassHealthDataDisplay = 0x7,
  BluetoothMinorClassStepCounter = 0x8,
  BluetoothMinorClassBodyCompositionAnalyzer = 0x9,
  BluetoothMinorClassPeakFlowMonitor = 0xA,
  BluetoothMinorClassMedicationMonitor = 0xB,
  BluetoothMinorClassKneeProsthesis = 0xC,
  BluetoothMinorClassAnkleProsthesis = 0xD,
  BluetoothMinorClassGenericHealthManager = 0xE,
  BluetoothMinorClassPersonalMobilityDevice = 0xF,

} BLUETOOTH_COD_MINOR_CLASS;

//
// 2. Link Manager
//
typedef enum {
  BluetoothVers10b = 0,
  BluetoothVers11 = 1,
  BluetoothVers12 = 2,
  BluetoothVers20 = 3,
  BluetoothVers21 = 4,
  BluetoothVers30 = 5,
  BluetoothVers40 = 6,
  BluetoothVers41 = 7,
} BLUETOOTH_VERSION;

//
// 3. Service Discovery
//
typedef enum {
  //
  // 1. Protocol Identifiers
  //
  BluetoothUuidSDP = 0x0001,
  BluetoothUuidUDP = 0x0002,
  BluetoothUuidRFCOMM = 0x0003,
  BluetoothUuidTCP = 0x0004,
  BluetoothUuidTCSBIN = 0x0005,
  BluetoothUuidTCSAT = 0x0006,
  BluetoothUuidATT = 0x0007,
  BluetoothUuidOBEX = 0x0008,
  BluetoothUuidIP = 0x0009,
  BluetoothUuidFTP = 0x000A,
  BluetoothUuidHTTP = 0x000C,
  BluetoothUuidWSP = 0x000E,
  BluetoothUuidBNEP = 0x000F,
  BluetoothUuidUPNP = 0x0010,
  BluetoothUuidHIDP = 0x0011,
  BluetoothUuidHardcopyControlChannel = 0x0012,
  BluetoothUuidHardcopyDataChannel = 0x0014,
  BluetoothUuidHardcopyNotification = 0x0016,
  BluetoothUuidAVCTP = 0x0017,
  BluetoothUuidAVDTP = 0x0019,
  BluetoothUuidCMTP = 0x001B,
  BluetoothUuidMCAPControlChannel = 0x001E,
  BluetoothUuidMCAPDataChannel = 0x001F,
  BluetoothUuidL2CAP = 0x0100,
  //
  // Service Class Name
  //
  BluetoothUuidServiceDiscoveryServerServiceClassID = 0x1000,
  BluetoothUuidBrowseGroupDescriptorServiceClassID = 0x1001,
  BluetoothUuidSerialPort = 0x1101,
  BluetoothUuidLANAccessUsingPPP = 0x1102,
  BluetoothUuidDialupNetworking = 0x1103,
  BluetoothUuidIrMCSync = 0x1104,
  BluetoothUuidOBEXObjectPush = 0x1105,
  BluetoothUuidOBEXFileTransfer = 0x1106,
  BluetoothUuidIrMCSyncCommand = 0x1107,
  BluetoothUuidHeadset = 0x1108,
  BluetoothUuidCordlessTelephony = 0x1109,
  BluetoothUuidAudioSource = 0x110A,
  BluetoothUuidAudioSink = 0x110B,
  BluetoothUuidAVRemoteControlTarget = 0x110C,
  BluetoothUuidAdvancedAudioDistribution = 0x110D,
  BluetoothUuidAVRemoteControl = 0x110E,
  BluetoothUuidAVRemoteControlController = 0x110F,
  BluetoothUuidIntercom = 0x1110,
  BluetoothUuidFax = 0x1111,
  BluetoothUuidHeadsetAudioGateway  = 0x1112,
  BluetoothUuidWAP = 0x1113,
  BluetoothUuidWAPClient = 0x1114,
  BluetoothUuidPANU = 0x1115,
  BluetoothUuidNAP = 0x1116,
  BluetoothUuidGN = 0x1117,
  BluetoothUuidDirectPrinting = 0x1118,
  BluetoothUuidReferencePrinting = 0x1119,
  BluetoothUuidBasicImagingProfile = 0x111A,
  BluetoothUuidImagingResponder = 0x111B,
  BluetoothUuidImagingAutomaticArchive = 0x111C,
  BluetoothUuidImagingReferencedObjects = 0x111D,
  BluetoothUuidHandsfree = 0x111E,
  BluetoothUuidHandsfreeAudioGateway = 0x111F,
  BluetoothUuidDirectPrintingReferenceObjectsService = 0x1120,
  BluetoothUuidReflectedUI = 0x1121,
  BluetoothUuidBasicPrinting = 0x1122,
  BluetoothUuidPrintingStatus = 0x1123,
  BluetoothUuidHumanInterfaceDeviceService = 0x1124,
  BluetoothUuidHardcopyCableReplacement = 0x1125,
  BluetoothUuidHCRPrint = 0x1126,
  BluetoothUuidHCRScan = 0x1127,
  BluetoothUuidCommonISDNAccess = 0x1128,
  BluetoothUuidSIMAccess = 0x112D,
  BluetoothUuidPhonebookAccessPCE = 0x112E,
  BluetoothUuidPhonebookAccessPSE = 0x112F,
  BluetoothUuidPhonebookAccess = 0x1130,
  BluetoothUuidHeadsetHS = 0x1131,
  BluetoothUuidMessageAccessServer = 0x1132,
  BluetoothUuidMessageNotificationServer = 0x1133,
  BluetoothUuidMessageAccessProfile = 0x1134,
  BluetoothUuidGNSS = 0x1135,
  BluetoothUuidGNSSServer = 0x1136,
  BluetoothUuid3DDisplay = 0x1137,
  BluetoothUuid3DGlasses = 0x1138,
  BluetoothUuid3DSynchronization = 0x1139,
  BluetoothUuidMPSProfile = 0x113A,
  BluetoothUuidMPSSC = 0x113B,
  BluetoothUuidPnPInformation = 0x1200,
  BluetoothUuidGenericNetworking = 0x1201,
  BluetoothUuidGenericFileTransfer = 0x1202,
  BluetoothUuidGenericAudio = 0x1203,
  BluetoothUuidGenericTelephony = 0x1204,
  BluetoothUuidUPNPService = 0x1205,
  BluetoothUuidUPNPIPService = 0x1206,
  BluetoothUuidESDPUPNPIPPAN = 0x1300,
  BluetoothUuidESDPUPNPIPLAP = 0x1301,
  BluetoothUuidESDPUPNPL2CAP = 0x1302,
  BluetoothUuidVideoSource = 0x1303,
  BluetoothUuidVideoSink = 0x1304,
  BluetoothUuidVideoDistribution = 0x1305,
  BluetoothUuidHDP = 0x1400,
  BluetoothUuidHDPSource = 0x1401,
  BluetoothUuidHDPSink = 0x1402,

  //
  // 2. Browse Group Identifiers
  //
  BluetoothUuidPublicBrowseRoot = 0x1002,

  //
  // 3.GATT Service
  //
  BluetoothUuidGenericAccess                = 0x1800,
  BluetoothUuidGenericAttribute             = 0x1801,
  BluetoothUuidImmediateAlert               = 0x1802,
  BluetoothUuidLinkLoss                     = 0x1803,
  BluetoothUuidTxPower                      = 0x1804,
  BluetoothUuidCurrentTimeService           = 0x1805,
  BluetoothUuidReferenceTimeUpdateService   = 0x1806,
  BluetoothUuidNextDSTChangeService         = 0x1807,
  BluetoothUuidGlucose                      = 0x1808,
  BluetoothUuidHealthThermometer            = 0x1809,
  BluetoothUuidDeviceInformation            = 0x180A,
  BluetoothUuidHeartRate                    = 0x180D,
  BluetoothUuidPhoneAlertStatusService      = 0x180E,
  BluetoothUuidBatteryService               = 0x180F,
  BluetoothUuidBloodPressure                = 0x1810,
  BluetoothUuidAlertNotificationService     = 0x1811,
  BluetoothUuidHumanInterfaceDevice         = 0x1812,
  BluetoothUuidScanParameters               = 0x1813,
  BluetoothUuidRunningSpeedandCadence       = 0x1814,
  BluetoothUuidAutomationIO                 = 0x1815,
  BluetoothUuidCyclingSpeedandCadence       = 0x1816,
  BluetoothUuidCyclingPower                 = 0x1818,
  BluetoothUuidLocationandNavigation        = 0x1819,
  BluetoothUuidEnvironmentalSensing         = 0x181A,
  BluetoothUuidBodyComposition              = 0x181B,
  BluetoothUuidUserData                     = 0x181C,
  BluetoothUuidWeightScale                  = 0x181D,
  BluetoothUuidBondManagement               = 0x181E,
  BluetoothUuidContinuousGlucoseMonitoring  = 0x181F,
  BluetoothUuidInternetProtocolSupport      = 0x1820,
  BluetoothUuidIndoorPositioning            = 0x1821,
  BluetoothUuidPulseOximeter                = 0x1822,
  BluetoothUuidHTTPProxy                    = 0x1823,
  BluetoothUuidTransportDiscovery           = 0x1824,
  BluetoothUuidObjectTransfer               = 0x1825,
} BLUETOOTH_UUID;

typedef enum {
  //
  // 3. Attribute Identifiers
  //

  // Core Specification: Universal Attributes
  BluetoothAttributeIdCoreServiceRecordHandle = 0x0000,
  BluetoothAttributeIdCoreServiceClassIDList = 0x0001,
  BluetoothAttributeIdCoreServiceRecordState = 0x0002,
  BluetoothAttributeIdCoreServiceID = 0x0003,
  BluetoothAttributeIdCoreProtocolDescriptorList = 0x0004,
  BluetoothAttributeIdCoreBrowseGroupList = 0x0005,
  BluetoothAttributeIdCoreLanguageBaseAttributeIDList = 0x0006,
  BluetoothAttributeIdCoreServiceInfoTimeToLive = 0x0007,
  BluetoothAttributeIdCoreServiceAvailability = 0x0008,
  BluetoothAttributeIdCoreProfileDescriptorList = 0x0009,
  BluetoothAttributeIdCoreDocumentationURL = 0x000A,
  BluetoothAttributeIdCoreClientExecutableURL = 0x000B,
  BluetoothAttributeIdCoreIconURL = 0x000C,
  BluetoothAttributeIdCoreAdditionalProtocolDescriptorLists = 0x000D,

  BluetoothAttributeIdCorePrimaryLanguageBase = 0x0100,
  BluetoothAttributeIdOffsetCoreServiceName = 0x0000,
  BluetoothAttributeIdOffsetCoreServiceDescription = 0x0001,
  BluetoothAttributeIdOffsetCoreProviderName = 0x0002,

  // Core Specification: Service Discovery Service
  //  ServiceDiscoveryServerServiceClassID: 0x1000
  BluetoothAttributeIdCoreSDSVersionNumberList = 0x0200,
  BluetoothAttributeIdCoreSDSServiceDatabaseState = 0x0201,

  // Core Specification: Browse Group Descriptor Service
  //  BrowseGroupDescriptorServiceClassID: 0x1001
  BluetoothAttributeIdCoreBGDSGroupID = 0x0200,

  // Advanced Audio Distribution Profile: 0x110D
  //  AudioSource: 0x110A
  //  AudioSink: 0x110B
  BluetoothAttributeIdA2DPSupportedFeatures = 0x0311,

  // Audio/Video Remote Control Profile
  //  A/V_RemoteControlTarget: 0x110C
  //  A/V_RemoteControl: 0x110E
  //  A/V_RemoteControlController: 0x110F
  BluetoothAttributeIdAVRCPSupportedFeatures = 0x0311,

  // Basic Imaging Profile
  //  ImagingResponder: 0x111B
  //  ImagingAutomaticArchive: 0x111C
  //  ImagingReferencedObjects: 0x111D
  BluetoothAttributeIdBIPGoepL2capPsm = 0x0200,
  BluetoothAttributeIdBIPSupportedCapabilities = 0x0310,
  BluetoothAttributeIdBIPSupportedFeatures = 0x0311,
  BluetoothAttributeIdBIPSupportedFunctions = 0x0312,
  BluetoothAttributeIdBIPTotalImagingDataCapacity = 0x0313,

  // Basic Printing Profile
  //  Direct Printing: 0x1118
  //  ReferencePrinting: 0x1119
  //  DirectPrintingReferenceObjectsService: 0x1120
  //  ReflectedUI: 0x1121
  //  PrintingStatus: 0x1123
  BluetoothAttributeIdBPPDocumentFormatsSupported = 0x0350,
  BluetoothAttributeIdBPPCharacterRepertoiresSupported = 0x0352,
  BluetoothAttributeIdBPPXHTMLPrintImageFormatsSupported = 0x0354,
  BluetoothAttributeIdBPPColorSupported = 0x0356,
  BluetoothAttributeIdBPP1284ID = 0x0358,
  BluetoothAttributeIdBPPPrinterName = 0x035A,
  BluetoothAttributeIdBPPPrinterLocation = 0x035C,
  BluetoothAttributeIdBPPDuplexSupported = 0x035E,
  BluetoothAttributeIdBPPMediaTypesSupported = 0x0360,
  BluetoothAttributeIdBPPMaxMediaWidth = 0x0362,
  BluetoothAttributeIdBPPMaxMediaLength = 0x0364,
  BluetoothAttributeIdBPPEnhancedLayoutSupported = 0x0366,
  BluetoothAttributeIdBPPRUIFormatsSupported = 0x0368,
  BluetoothAttributeIdBPPReferencePrintingRUISupported = 0x0370,
  BluetoothAttributeIdBPPDirectPrintingRUISupported = 0x0372,
  BluetoothAttributeIdBPPReferencePrintingTopURL = 0x0364,
  BluetoothAttributeIdBPPDirectPrintingTopURL = 0x0376,
  BluetoothAttributeIdBPPPrinterAdminRUITopURL = 0x0378,
  BluetoothAttributeIdBPPDeviceName = 0x037A,

  // Cordless Telephony Profile
  //  CordlessTelephony: 0x1109
  BluetoothAttributeIdCTPExternalNetwork = 0x0301,

  // Device Identification Profile
  //  PnPInformation: 0x1200
  BluetoothAttributeIdDIPSpecificationID = 0x0200,
  BluetoothAttributeIdDIPVendorID = 0x0201,
  BluetoothAttributeIdDIPProductID = 0x0202,
  BluetoothAttributeIdDIPVersion = 0x0203,
  BluetoothAttributeIdDIPPrimaryRecord = 0x0204,
  BluetoothAttributeIdDIPVendorIDSource = 0x0205,

  // Fax Profile
  //  Fax: 0x1111
  BluetoothAttributeIdFaxClass1Support = 0x0302,
  BluetoothAttributeIdFaxClass20Support = 0x0303,
  BluetoothAttributeIdFaxClass2SupportVendorSpecificClass = 0x0304,
  BluetoothAttributeIdFaxAudioFeedbackSupport = 0x0305,

  // File Transfer Profile
  //  OBEXFileTransfer: 0x1109
  BluetoothAttributeIdFTPGoepL2capPsm = 0x0200,

  // Global Navigation Satellite System Profile
  //  GNSS Service: 0x1136
  BluetoothAttributeIdGNSSSupportedFeatures = 0x0200,

  // Hands-Free Profile
  //  Handsfree: 0x111E
  //  HandsfreeAudioGateway: 0x111F
  BluetoothAttributeIdHFPNetwork = 0x0301,
  BluetoothAttributeIdHFPSupportedFeatures = 0x0311,

  // Hardcopy Replacement Profile
  //  HCR_Print: 0x1126
  //  HCR_Scan: 0x1127
  BluetoothAttributeIdHCRP1284ID = 0x0300,
  BluetoothAttributeIdHCRPDeviceName = 0x0302,
  BluetoothAttributeIdHCRPFriendlyName = 0x0304,
  BluetoothAttributeIdHCRPDeviceLocation = 0x0306,

  // Headset Profile
  //  Headset: 0x1108
  //  Headset - Audio Gateway (AG): 0x1112
  //  Headset: 0x1131
  BluetoothAttributeIdHSPRemoteAudioVolumeControl = 0x0302,

  // Health Device Profile
  //  HDP Source: 0x1401
  //  HDP Sink: 0x1402
  BluetoothAttributeIdHDPSupportFeaturesList = 0x0200,
  BluetoothAttributeIdHDPDataExchangeSpecification = 0x0301,
  BluetoothAttributeIdHDPMCAPSupportedProcedures = 0x0302,

  // Human Interface Device Profile: 0x0011
  //  HumanInterfaceDeviceService: 0x1124
  BluetoothAttributeIdHIDDeviceReleaseNumber = 0x0200,
  BluetoothAttributeIdHIDParserVersion = 0x0201,
  BluetoothAttributeIdHIDDeviceSubclass = 0x0202,
  BluetoothAttributeIdHIDCountryCode = 0x0203,
  BluetoothAttributeIdHIDVirtualCable = 0x0204,
  BluetoothAttributeIdHIDReconnectInitiate = 0x0205,
  BluetoothAttributeIdHIDDescriptorList = 0x0206,
  BluetoothAttributeIdHIDLANGIDBaseList = 0x0207,
  BluetoothAttributeIdHIDSDPDisable  = 0x0208,
  BluetoothAttributeIdHIDBatteryPower = 0x0209,
  BluetoothAttributeIdHIDRemoteWake = 0x020A,
  BluetoothAttributeIdHIDProfileVersion = 0x020B,
  BluetoothAttributeIdHIDSupervisionTimeout = 0x020C,
  BluetoothAttributeIdHIDNormallyConnectable = 0x020D,
  BluetoothAttributeIdHIDBootDevice = 0x020E,
  BluetoothAttributeIdHIDSSRHostMaxLatency = 0x020F,
  BluetoothAttributeIdHIDSSRHostMinTimeout = 0x0210,

  // Interoperability as WAP Bearer
  //  WAP: 0x1113
  //  WAP_CLIENT: 0x1114
  BluetoothAttributeIdWAPNetworkAddress = 0x0306,
  BluetoothAttributeIdWAPGateway = 0x0307,
  BluetoothAttributeIdWAPHomePageURL = 0x0308,
  BluetoothAttributeIdWAPStackType = 0x0309,

  // Message Access Profile
  //  Message Access Server: 0x1132
  //  Message Notification Server: 0x1133
  BluetoothAttributeIdMAPGoepLcapPsm = 0x0200,
  BluetoothAttributeIdMAPMASInstanceID = 0x0315,
  BluetoothAttributeIdMAPSupportedMessageTypes = 0x0316,
  BluetoothAttributeIdMAPSupportedFeatures = 0x0317,

  // Object Push Profile
  //  OBEXObjectPush: 0x1105
  BluetoothAttributeIdOPPGoepLcapPsm = 0x0200,
  BluetoothAttributeIdOPPServiceVersion = 0x0300,
  BluetoothAttributeIdOPPSupportedFormatsList = 0x0303,

  // Personal Area Networking Profile
  //  PANU: 0x1115
  //  NAP: 0x1116
  //  GN: 0x1117
  BluetoothAttributeIdPANIpSubnet = 0x0200,
  BluetoothAttributeIdPANSecurityDescription = 0x030A,
  BluetoothAttributeIdPANNetAccessType = 0x030B,
  BluetoothAttributeIdPANMaxNetAccessrate = 0x030C,
  BluetoothAttributeIdPANIPv4Subnet = 0x030D,
  BluetoothAttributeIdPANIPv6Subnet = 0x030E,

  // Phone Book Access Profile: 0x1130
  //  Phonebook Access - PCE: 0x112E
  //  Phonebook Access - PSE: 0x112F
  BluetoothAttributeIdPBAPGoepL2capPsm = 0x0200,
  BluetoothAttributeIdPBAPSupportedRepositories = 0x0314,
  BluetoothAttributeIdPBAPSupportedFeatures = 0x0317,

  // Synchronization Profile
  //  IrMCSync: 0x1104
  BluetoothAttributeIdSYNCSupportedDataStoresList = 0x0301,

  // Multi-Profile
  //  MPS SC UUID: 0x113B
  BluetoothAttributeIdMPSDScenarios = 0x0200,
  BluetoothAttributeIdMPMDScenarios = 0x0201,
  BluetoothAttributeIdMPSupportedProfilesProtocols = 0x0202,
} BLUETOOTH_ATTRIBUTE_ID;

//
// 5. Logical Link Control
//
typedef enum {
  BluetoothPsmSDP = 0x0001,
  BluetoothPsmRFCOMM = 0x0003,
  BluetoothPsmTCSBIN = 0x0005,
  BluetoothPsmTCSBINCordless = 0x0007,
  BluetoothPsmBNEP = 0x000F,
  BluetoothPsmHIDControl = 0x0011,
  BluetoothPsmHIDInterrupt = 0x0013,
  BluetoothPsmUPnP = 0x0015,
  BluetoothPsmAVCTP = 0x0017,
  BluetoothPsmAVDTP = 0x0019,
  BluetoothPsmAVCTPBrowsing = 0x001B,
  BluetoothPsmUDICPlane = 0x001D,
  BluetoothPsmATT = 0x001F,
  BluetoothPsm3DSP = 0x0021,
} BLUETOOTH_PSM;

//
// 6. Host Controller Interface
//
typedef enum {
  BluetoothHciVers10b = 0,
  BluetoothHciVers11 = 1,
  BluetoothHciVers12 = 2,
  BluetoothHciVers20 = 3,
  BluetoothHciVers21 = 4,
  BluetoothHciVers30 = 5,
  BluetoothHciVers40 = 6,
  BluetoothHciVers41 = 7,
} BLUETOOTH_HCI_VERSION;

//
// 7. Generic Access Profile
//
typedef enum {
  BluetoothGapTypeFlags = 0x01,
  BluetoothGapTypeIncomplete16BitServiceClassUUIDs = 0x02,
  BluetoothGapTypeComplete16BitServiceClassUUIDs = 0x03,
  BluetoothGapTypeIncomplete32BitServiceClassUUIDs = 0x04,
  BluetoothGapTypeComplete32BitServiceClassUUIDs = 0x05,
  BluetoothGapTypeIncomplete128BitServiceClassUUIDs = 0x06,
  BluetoothGapTypeComplete128BitServiceClassUUIDs = 0x07,
  BluetoothGapTypeShortenedLocalName = 0x08,
  BluetoothGapTypeCompleteLocalName = 0x09,
  BluetoothGapTypeTxPowerLevel = 0x0A,
  BluetoothGapTypeClassOfDevice = 0x0D,
  BluetoothGapTypeSimplePairingHashC = 0x0E,
  BluetoothGapTypeSimplePairingRandomizerR = 0x0F,
  BluetoothGapTypeDeviceID = 0x10,
  BluetoothGapTypeSecurityManagerTKValue = 0x11,
  BluetoothGapTypeSecurityManagerOutOfBandFlags = 0x12,
  BluetoothGapTypeSlaveConnectionIntervalRange = 0x13,
  BluetoothGapTypeListOf16BitServiceSolicitationUUIDs = 0x14,
  BluetoothGapTypeListOf128BitServiceSolicitationUUIDs = 0x15,
  BluetoothGapTypeServiceData = 0x16,
  BluetoothGapTypePublicTargetAddress = 0x17,
  BluetoothGapTypeRandomTargetAddress = 0x18,
  BluetoothGapTypeAppearance = 0x19,
  BluetoothGapTypeAdvertisingInterval = 0x1A,
  BluetoothGapType3DInformationData = 0x3D,
  BluetoothGapTypeManufacturerSpecificData = 0xFF,
} BLUETOOTH_GAP_DATA_TYPE;

//
// 8. AMP Manager Protocol
//
typedef enum {
  BluetoothControllerTypeBREDR = 0,
  BluetoothControllerTypeAMP = 1,
} BLUETOOTH_CONTROLLER_TYPE;

//
// 11. Generic Attribute Profile
//
typedef enum {
  //
  // GATT Services
  //
  BluetoothGattTypeGenericAccessProfile = 0x1800,
  BluetoothGattTypeGenericAttributeProfile = 0x1801,
  //
  // GATT Attribute Types
  //
  BluetoothGattTypePrimaryService = 0x2800,
  BluetoothGattTypeSecondaryService = 0x2801,
  BluetoothGattTypeInclude = 0x2802,
  BluetoothGattTypeCharacteristic = 0x2803,
  //
  // GATT Characteristic Descriptors
  //
  BluetoothGattTypeCharacteristicExtendedProperties = 0x2900,
  BluetoothGattTypeCharacteristicUserDescription = 0x2901,
  BluetoothGattTypeClientCharacteristicConfiguration = 0x2902,
  BluetoothGattTypeServerCharacteristicConfiguration = 0x2903,
  BluetoothGattTypeCharacteristicFormat = 0x2904,
  BluetoothGattTypeCharacteristicAggregateFormat = 0x2905,
  BluetoothGattTypeReportReference = 0x2908,
  //
  // GATT Characteristic Types
  //
  BluetoothGattTypeDeviceName = 0x2A00,
  BluetoothGattTypeAppearance = 0x2A01,
  BluetoothGattTypePeripheralPrivacyFlag = 0x2A02,
  BluetoothGattTypeReconnectionAddress = 0x2A03,
  BluetoothGattTypePeripheralPreferredConnectionParameters = 0x2A04,
  BluetoothGattTypeServiceChanged = 0x2A05,
  BluetoothGattTypeBatteryLevel = 0x2A19,
  BluetoothGattTypeBootKeyboardInputReport = 0x2A22,
  BluetoothGattTypeBootKeyboardOutputReport = 0x2A32,
  BluetoothGattTypeBootMouseInputReport = 0x2A33,
  BluetoothGattTypeHidReportMap = 0x2A4B,
  BluetoothGattTypeHidReport = 0x2A4D,
  BluetoothGattTypeHidProtocolMode = 0x2A4E,
  BluetoothGattTypeDescReportRefer = 0x2908,
  BluetoothGattTypeDescExternalReportRefer = 0x2907,
  BluetoothGattTypePnPID = 0x2A50,
} BLUETOOTH_GATT_DATA_TYPE;

// TBD

#pragma pack()

#endif


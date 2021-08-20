/** @file

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2004 - 2020 Intel Corporation.

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

#ifndef _SETUP_VARIABLE_H_
#define _SETUP_VARIABLE_H_

#include <PchLimits.h>
#include <Register/CpuPcieRegs.h>
#include <CpuPcieInfo.h>
#include <Register/ItbtPcieRegs.h>

#ifndef MAX_CUSTOM_P_STATES
#define MAX_CUSTOM_P_STATES 40
#endif // MAX_CUSTOM_P_STATES
#ifndef MAX_16_CUSTOM_P_STATES
#define MAX_16_CUSTOM_P_STATES 16
#endif // MAX_16_CUSTOM_P_STATES

#define MAX_IIO_PCI_EXPRESS_ROOT_PORTS    4
#define MAX_PCI_ROOT_BRIDGES              1
#define SATA_MODE_AHCI                    0
#define SATA_MODE_RAID                    1
#define SATA_TEST_MODE_ENABLE             1
#define NON_CS_DEVICES                    9
#define I2C0_SENSOR_DEVICES               7
#define I2C1_SENSOR_DEVICES               13
#define SERIAL_IO_I2C0                    0x0
#define SERIAL_IO_I2C1                    0x1
#define SERIAL_IO_I2C2                    0x2
#define SERIAL_IO_I2C3                    0x3
#define SERIAL_IO_I2C4                    0x4
#define SERIAL_IO_I2C5                    0x5
#define SERIAL_IO_I2C6                    0x6
#define SERIAL_IO_I2C7                    0x7

#define SERIAL_IO_SPI0                    0x0
#define SERIAL_IO_SPI1                    0x1
#define SERIAL_IO_SPI2                    0x2
#define SERIAL_IO_SPI3                    0x3
#define SERIAL_IO_SPI4                    0x4
#define SERIAL_IO_SPI5                    0x5
#define SERIAL_IO_SPI6                    0x6

#define SERIAL_IO_UART0                   0x0
#define SERIAL_IO_UART1                   0x1
#define SERIAL_IO_UART2                   0x2
#define SERIAL_IO_UART3                   0x3
#define SERIAL_IO_UART4                   0x4
#define SERIAL_IO_UART5                   0x5
#define SERIAL_IO_UART6                   0x6

//
// This is 8 Bits Map of I2C Devices for combined use in BoardConfigPatchTable.h and in PchSetup.hfr
//
#define SERIAL_IO_I2C_TOUCHPAD            0x1
#define SERIAL_IO_I2C_TOUCHPANEL          0x2
//#define 3TH_SERIAL_IO_I2C_DEVICE        0x4
//#define 4TH_SERIAL_IO_I2C_DEVICE       0x08
//#define 5TH_SERIAL_IO_I2C_DEVICE       0x10
//#define 6TH_SERIAL_IO_I2C_DEVICE       0x20
//#define 7TH_SERIAL_IO_I2C_DEVICE       0x40
//#define 8TH_SERIAL_IO_I2C_DEVICE       0x80

//
// This is 8 Bits Map of SPI Devices for combined use in BoardConfigPatchTable.h and in PchSetup.hfr
//
#define SERIAL_IO_SPI_FINGERPRINT         0x1
//#define 2nd_SERIAL_IO_SPI_DEVICE       0x02
//#define 3rd_SERIAL_IO_SPI_DEVICE       0x04
//#define 4TH_SERIAL_IO_SPI_DEVICE       0x08
//#define 5TH_SERIAL_IO_SPI_DEVICE       0x10
//#define 6TH_SERIAL_IO_SPI_DEVICE       0x20
//#define 7TH_SERIAL_IO_SPI_DEVICE       0x40
//#define 8TH_SERIAL_IO_SPI_DEVICE       0x80

#define HDAUDIO_FEATURES                    9
#define HDAUDIO_PP_MODULES                  32
#define HDAUDIO_LINK_MODE_HDA               0
#define HDAUDIO_LINK_MODE_I2S_SSP           1
#define HDAUDIO_LINK_MODE_SNDW              2
#define HDAUDIO_LINK_MODE_ADVANCED          3

#define GUID_CHARS_NUMBER                   37 // 36 GUID chars + null termination
#define FIVR_RAIL_S0IX_SX_STATES_MAX       5  // Number of availabe S0ix/Sx policy bits in FIVR Rail configuration
#define FIVR_RAIL_EXT_VOLTAGE_STATES_MAX   4  // Number of supported voltage settings for FIVR Rail configuration

#define SETUP_MAX_USB2_PORTS              16
#define SETUP_MAX_USB3_PORTS              10

#define EFI_CSM_CONTROL_ALWAYS_ON         0x0
#define EFI_CSM_CONTROL_ALWAYS_OFF        0x1
#define EFI_CSM_CONTROL_DETECT_LEGACY_VGA 0x2

#define VBT_SELECT_EDP                    0x0
#define VBT_SELECT_MIPI                   0x1

#define OPROM_EFI                         1
#define OPROM_LEGACY                      0

#define MIPICAM_I2C_DEVICES_COUNT         12
#define MIPICAM_GPIO_COUNT                4
#define MIPICAM_MODULE_NAME_LENGTH        16
#define MIPICAM_HID_LENGTH                9
#define DTBT_CONTROLLER_SUPPORTED         2
#define ITBT_ROOT_PORTS_SUPPORTED         6
#define ITBT_HOST_DMA_SUPPORTED           3
#ifndef SGX_SOFTWARE_CONTROL
#define SGX_SOFTWARE_CONTROL 2
#endif

#pragma pack(1)
/**
 Making any setup structure change after code frozen
 will need to maintain backward compatibility, bump up
 structure revision and update below history table\n
  <b>Revision 1</b>:  - Initial version.
  <b>Revision 2</b>:  - Removing RTC Wake up Time Date, Hour, Minute and Sec Option. These must be set by the Tool in OS.
**/

#define SETUP_DATA_REVISION 2

typedef struct {
  UINT8   Revision;
  UINT8   FastBoot;
  UINT8   FastBootWdt;
  UINT8   SkipHIIUpdate;
  UINT8   ConInBehavior;
  UINT8   DisplayBootMode;
  UINT8   Numlock;
  UINT8   InteractiveText;
  UINT8   LazyConIn;
  UINT8   VirtualKeyboard;
  UINT8   FirmwareConfiguration;
  UINT8   OpRomPost; // [Legacy] \ EFI Compatible
  // General PCI Settings: [] - default
  UINT8   PciLatency; //[32]\ 64 \ 96 \ 128 \ 160 \ 192 \ 224 \ 248
#ifdef PCI_X_SUPPORT
  UINT8   PciXLatency; // 32 \[64]\ 96 \ 128 \ 160 \ 192 \ 224 \ 248
#endif // PCI_X_SUPPORT
#ifdef PCI_EXPRESS_SUPPORT
#ifdef PCI_EXPRESS_INIT_SUPPORT
  // PCI Express Device Settings: [] - default
  UINT8   RelaxedOrdering; //[Disable]\ Enable
  UINT8   ExtTagField; //[Disable]\ Enable
  UINT8   NoSnoop; // Disable \[Enable]
  UINT8   MaxPayload; // [Auto]\ 128 \ 256 \ 512 \ 1024 \ 2048 \ 4096 (in bytes)
  UINT8   MaxReadRequest; // [Auto]\ 128 \ 256 \ 512 \ 1024 \ 2048 \ 4096 (in bytes)
  // PCI Express Link settings: [] - default
  UINT8   AspmMode; // [Disable]\ Auto \ Force L0
  UINT8   ExtendedSynch; // [Disable]\ Enable
#endif // PCI_EXPRESS_INIT_SUPPORT
#endif // PCI_EXPRESS_SUPPORT
  UINT8   AcpiAuto;
  UINT8   AcpiSleepState;
  UINT8   AcpiHibernate;
  UINT8   AcpiTableRevision;
  UINT8   PciExpNative;
  UINT8   NativeAspmEnable;
  UINT8   PtidSupport;
  // AcpiDebug Setup Options
  UINT8   AcpiDebug;
  UINT32  AcpiDebugAddress;
  UINT8   PciDelayOptimizationEcr;
  // S5 RTC wakeup setup options
  UINT8   WakeOnRTCS5;
  UINT8   RTCWakeupDate;        // @deprecated since revision 2
  UINT8   RTCWakeupTimeHour;    // @deprecated since revision 2
  UINT8   RTCWakeupTimeMinute;  // @deprecated since revision 2
  UINT8   RTCWakeupTimeSecond;  // @deprecated since revision 2
  UINT8   PeciAccessMethod;
  UINT8   LowPowerS0Idle;
  UINT8   PepCpu;
  UINT8   PepGfx;
  UINT8   PepSataContraints;
  UINT8   PepUart0;
  UINT8   PepUart1;
  UINT8   PepUart2;
  UINT8   PepI2c0;
  UINT8   PepI2c1;
  UINT8   PepI2c2;
  UINT8   PepI2c3;
  UINT8   PepI2c4;
  UINT8   PepI2c5;
  UINT8   PepI2c6;
  UINT8   PepI2c7;
  UINT8   PepSpi0;
  UINT8   PepSpi1;
  UINT8   PepSpi2;
  UINT8   PepXhci;
  UINT8   PepAudio;
  UINT8   PepEmmc;
  UINT8   PepSdxc;
  UINT8   PepIpu;
  UINT8   PepCsme;
  UINT8   PepGbe;
  UINT8   PepThc0;
  UINT8   PepThc1;
  UINT8   PepIsi;
  UINT8   PepGbeTsn;
  UINT8   PepPse;
  UINT8   PepPseTsn;
  UINT8   PepPseDma;
  UINT8   PepPsePwm;
  UINT8   PepPseAdc;
  UINT8   PepPseSpi;
  UINT8   PepPseI2c;
  UINT8   PepPseUart;
  UINT8   PepPseI2s;
  UINT8   PepPseGpio;
  UINT8   PepPseCan;
  UINT8   PepPseQep;
  UINT8   PepTcss;
  UINT8   CSNotifyEC;
  UINT8   CSDebugLightEC;
  UINT8   EcLowPowerMode;
  UINT8   EcDebugLed;
  UINT8   ECBaseCsPwrPolicy;
  UINT8   SensorStandby;
  UINT8   PL1LimitCS;
  UINT16  PL1LimitCSValue;
  UINT8   TenSecondPowerButtonSupport;
  UINT8   TenSecondPowerButtonEnable;
  UINT8   LpitResidencyCounter;
  UINT8   IrmtConfiguration;
  // Reading SSDT table from file
  UINT8   LoadSSDTFromFile;
  //
  // On Screen Branding
  //
  UINT16  OperatingSystem;
  UINT16  OemBadgingBrand;
  UINT8   BootFirstToShell;

  UINT8   SensorHubType;
  UINT8   DebugUsbUartSupport;
  UINT8   DebugUsbUart;
  UINT8   PxeRom;
  UINT8   EfiNetworkSupport;
  UINT8   Reserved; // Get rid of "EnableClockSpreadSpec"
  UINT8   UsbSensorHub;

  UINT8   HddAcousticPowerManagement;
  UINT8   HddAcousticMode;

  //
  // Recovery Configuration
  //
  UINT8   IsRecoveryJumper;

  //
  // MipiCam sensor configuration menu
  //
  UINT8   MipiCam_ControlLogic0;             // None/discrete/PMIC
  UINT8   MipiCam_ControlLogic1;             // None/discrete/PMIC
  UINT8   MipiCam_ControlLogic2;             // None/discrete/PMIC
  UINT8   MipiCam_ControlLogic3;             // None/discrete/PMIC
  UINT8   MipiCam_ControlLogic4;             // None/discrete/PMIC
  UINT8   MipiCam_ControlLogic5;             // None/discrete/PMIC

  UINT8   MipiCam_Link0;                     // Enabled / Disabled
  UINT8   MipiCam_Link1;                     // Enabled / Disabled
  UINT8   MipiCam_Link2;                     // Enabled / Disabled
  UINT8   MipiCam_Link3;                     // Enabled / Disabled
  UINT8   MipiCam_Link4;                     // Enabled / Disabled
  UINT8   MipiCam_Link5;                     // Enabled / Disabled

  UINT8   MipiCam4Enable;                    // Enable 5th camera
  UINT8   MipiCam5Enable;                    // Enable 6th camera

  UINT8   MipiCam_LanesClkDiv;

  UINT8   MipiCam_ControlLogic0_Type;
  UINT8   MipiCam_ControlLogic0_CrdVersion;
  UINT32  MipiCam_ControlLogic0_InputClock;
  UINT8   MipiCam_ControlLogic0_PchClockSource;
  UINT8   MipiCam_ControlLogic0_GpioPinsEnabled;
  UINT8   MipiCam_ControlLogic0_I2cChannel;
  UINT16  MipiCam_ControlLogic0_I2cAddress;
  UINT8   MipiCam_ControlLogic0_Pld;
  UINT8   MipiCam_ControlLogic0_Wled1FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic0_Wled1TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic0_Wled2FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic0_Wled2TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic0_SubPlatformId;
  UINT8   MipiCam_ControlLogic0_Wled1Type;
  UINT8   MipiCam_ControlLogic0_Wled2Type;
  UINT8   MipiCam_ControlLogic0_GpioGroupPadNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic0_GpioGroupNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic0_GpioFunction[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic0_GpioActiveValue[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic0_GpioInitialValue[MIPICAM_GPIO_COUNT];

  UINT8   MipiCam_ControlLogic1_Type;
  UINT8   MipiCam_ControlLogic1_CrdVersion;
  UINT32  MipiCam_ControlLogic1_InputClock;
  UINT8   MipiCam_ControlLogic1_PchClockSource;
  UINT8   MipiCam_ControlLogic1_GpioPinsEnabled;
  UINT8   MipiCam_ControlLogic1_I2cChannel;
  UINT16  MipiCam_ControlLogic1_I2cAddress;
  UINT8   MipiCam_ControlLogic1_Pld;
  UINT8   MipiCam_ControlLogic1_Wled1FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic1_Wled1TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic1_Wled2FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic1_Wled2TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic1_SubPlatformId;
  UINT8   MipiCam_ControlLogic1_Wled1Type;
  UINT8   MipiCam_ControlLogic1_Wled2Type;
  UINT8   MipiCam_ControlLogic1_GpioGroupPadNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic1_GpioGroupNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic1_GpioFunction[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic1_GpioActiveValue[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic1_GpioInitialValue[MIPICAM_GPIO_COUNT];

  UINT8   MipiCam_ControlLogic2_Type;
  UINT8   MipiCam_ControlLogic2_CrdVersion;
  UINT32  MipiCam_ControlLogic2_InputClock;
  UINT8   MipiCam_ControlLogic2_PchClockSource;
  UINT8   MipiCam_ControlLogic2_GpioPinsEnabled;
  UINT8   MipiCam_ControlLogic2_I2cChannel;
  UINT16  MipiCam_ControlLogic2_I2cAddress;
  UINT8   MipiCam_ControlLogic2_Pld;
  UINT8   MipiCam_ControlLogic2_Wled1FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic2_Wled1TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic2_Wled2FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic2_Wled2TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic2_SubPlatformId;
  UINT8   MipiCam_ControlLogic2_Wled1Type;
  UINT8   MipiCam_ControlLogic2_Wled2Type;
  UINT8   MipiCam_ControlLogic2_GpioGroupPadNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic2_GpioGroupNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic2_GpioFunction[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic2_GpioActiveValue[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic2_GpioInitialValue[MIPICAM_GPIO_COUNT];

  UINT8   MipiCam_ControlLogic3_Type;
  UINT8   MipiCam_ControlLogic3_CrdVersion;
  UINT32  MipiCam_ControlLogic3_InputClock;
  UINT8   MipiCam_ControlLogic3_PchClockSource;
  UINT8   MipiCam_ControlLogic3_GpioPinsEnabled;
  UINT8   MipiCam_ControlLogic3_I2cChannel;
  UINT16  MipiCam_ControlLogic3_I2cAddress;
  UINT8   MipiCam_ControlLogic3_Pld;
  UINT8   MipiCam_ControlLogic3_Wled1FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic3_Wled1TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic3_Wled2FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic3_Wled2TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic3_SubPlatformId;
  UINT8   MipiCam_ControlLogic3_Wled1Type;
  UINT8   MipiCam_ControlLogic3_Wled2Type;
  UINT8   MipiCam_ControlLogic3_GpioGroupPadNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic3_GpioGroupNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic3_GpioFunction[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic3_GpioActiveValue[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic3_GpioInitialValue[MIPICAM_GPIO_COUNT];

  UINT8   MipiCam_ControlLogic4_Type;
  UINT8   MipiCam_ControlLogic4_CrdVersion;
  UINT32  MipiCam_ControlLogic4_InputClock;
  UINT8   MipiCam_ControlLogic4_PchClockSource;
  UINT8   MipiCam_ControlLogic4_GpioPinsEnabled;
  UINT8   MipiCam_ControlLogic4_I2cChannel;
  UINT16  MipiCam_ControlLogic4_I2cAddress;
  UINT8   MipiCam_ControlLogic4_Pld;
  UINT8   MipiCam_ControlLogic4_Wled1FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic4_Wled1TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic4_Wled2FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic4_Wled2TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic4_SubPlatformId;
  UINT8   MipiCam_ControlLogic4_Wled1Type;
  UINT8   MipiCam_ControlLogic4_Wled2Type;
  UINT8   MipiCam_ControlLogic4_GpioGroupPadNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic4_GpioGroupNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic4_GpioFunction[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic4_GpioActiveValue[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic4_GpioInitialValue[MIPICAM_GPIO_COUNT];

  UINT8   MipiCam_ControlLogic5_Type;
  UINT8   MipiCam_ControlLogic5_CrdVersion;
  UINT32  MipiCam_ControlLogic5_InputClock;
  UINT8   MipiCam_ControlLogic5_PchClockSource;
  UINT8   MipiCam_ControlLogic5_GpioPinsEnabled;
  UINT8   MipiCam_ControlLogic5_I2cChannel;
  UINT16  MipiCam_ControlLogic5_I2cAddress;
  UINT8   MipiCam_ControlLogic5_Pld;
  UINT8   MipiCam_ControlLogic5_Wled1FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic5_Wled1TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic5_Wled2FlashMaxCurrent;
  UINT8   MipiCam_ControlLogic5_Wled2TorchMaxCurrent;
  UINT8   MipiCam_ControlLogic5_SubPlatformId;
  UINT8   MipiCam_ControlLogic5_Wled1Type;
  UINT8   MipiCam_ControlLogic5_Wled2Type;
  UINT8   MipiCam_ControlLogic5_GpioGroupPadNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic5_GpioGroupNumber[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic5_GpioFunction[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic5_GpioActiveValue[MIPICAM_GPIO_COUNT];
  UINT8   MipiCam_ControlLogic5_GpioInitialValue[MIPICAM_GPIO_COUNT];

  UINT8   MipiCam_Link0_SensorModel;         // IMX135 / OV5693 / IMX179 / OV8858 / OV2740-IVCAM / IMX208 / OV9728 / IMX188 / User0
  UINT16  MipiCam_Link0_UserHid[MIPICAM_HID_LENGTH];
  UINT8   MipiCam_Link0_CameraPhysicalLocation;
  UINT16  MipiCam_Link0_ModuleName[MIPICAM_MODULE_NAME_LENGTH];
  UINT8   MipiCam_Link0_I2cDevicesEnabled;   // number of I2C devices defined for this link
  UINT8   MipiCam_Link0_I2cChannel;
  UINT16  MipiCam_Link0_I2cAddress[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link0_I2cDeviceType[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link0_DriverData_Version;
  UINT8   MipiCam_Link0_DriverData_CrdVersion;
  UINT8   MipiCam_Link0_DriverData_LaneUsed;
  UINT8   MipiCam_Link0_DriverData_EepromType;
  UINT8   MipiCam_Link0_DriverData_VcmType;
  UINT8   MipiCam_Link0_DriverData_CustomData[4];
  UINT32  MipiCam_Link0_DriverData_Mclk;
  UINT8   MipiCam_Link0_DriverData_ControlLogic;
  UINT8   MipiCam_Link0_DriverData_FlashSupport;
  UINT8   MipiCam_Link0_DriverData_PrivacyLed;
  UINT8   MipiCam_Link0_DriverData_Degree;
  UINT8   MipiCam_Link0_DriverData_PmicPosition;
  UINT8   MipiCam_Link0_DriverData_VoltageRail;
  UINT8   MipiCam_Link0_DriverData_PprValue;
  UINT8   MipiCam_Link0_DriverData_PprUnit;

  UINT8   MipiCam_Link1_SensorModel;         // IMX135 / OV5693 / IMX179 / OV8858 / OV2740-IVCAM / IMX208 / OV9728 / IMX188 / User1
  UINT16  MipiCam_Link1_UserHid[MIPICAM_HID_LENGTH];
  UINT8   MipiCam_Link1_CameraPhysicalLocation;
  UINT16  MipiCam_Link1_ModuleName[MIPICAM_MODULE_NAME_LENGTH];
  UINT8   MipiCam_Link1_I2cDevicesEnabled;   // number of I2C devices defined for this link
  UINT8   MipiCam_Link1_I2cChannel;
  UINT16  MipiCam_Link1_I2cAddress[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link1_I2cDeviceType[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link1_DriverData_Version;
  UINT8   MipiCam_Link1_DriverData_CrdVersion;
  UINT8   MipiCam_Link1_DriverData_LaneUsed;
  UINT8   MipiCam_Link1_DriverData_EepromType;
  UINT8   MipiCam_Link1_DriverData_VcmType;
  UINT8   MipiCam_Link1_DriverData_CustomData[4];
  UINT32  MipiCam_Link1_DriverData_Mclk;
  UINT8   MipiCam_Link1_DriverData_ControlLogic;
  UINT8   MipiCam_Link1_DriverData_FlashSupport;
  UINT8   MipiCam_Link1_DriverData_PrivacyLed;
  UINT8   MipiCam_Link1_DriverData_Degree;
  UINT8   MipiCam_Link1_DriverData_PmicPosition;
  UINT8   MipiCam_Link1_DriverData_VoltageRail;
  UINT8   MipiCam_Link1_DriverData_PprValue;
  UINT8   MipiCam_Link1_DriverData_PprUnit;

  UINT8   MipiCam_Link2_SensorModel;         // IMX135 / OV5693 / IMX179 / OV8858 / OV2740-IVCAM / IMX208 / OV9728 / IMX188 / User2
  UINT16  MipiCam_Link2_UserHid[MIPICAM_HID_LENGTH];
  UINT8   MipiCam_Link2_CameraPhysicalLocation;
  UINT16  MipiCam_Link2_ModuleName[MIPICAM_MODULE_NAME_LENGTH];
  UINT8   MipiCam_Link2_I2cDevicesEnabled;   // number of I2C devices defined for this link
  UINT8   MipiCam_Link2_I2cChannel;
  UINT16  MipiCam_Link2_I2cAddress[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link2_I2cDeviceType[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link2_DriverData_Version;
  UINT8   MipiCam_Link2_DriverData_CrdVersion;
  UINT8   MipiCam_Link2_DriverData_LaneUsed;
  UINT8   MipiCam_Link2_DriverData_EepromType;
  UINT8   MipiCam_Link2_DriverData_VcmType;
  UINT8   MipiCam_Link2_DriverData_CustomData[4];
  UINT32  MipiCam_Link2_DriverData_Mclk;
  UINT8   MipiCam_Link2_DriverData_ControlLogic;
  UINT8   MipiCam_Link2_DriverData_FlashSupport;
  UINT8   MipiCam_Link2_DriverData_PrivacyLed;
  UINT8   MipiCam_Link2_DriverData_Degree;
  UINT8   MipiCam_Link2_DriverData_PmicPosition;
  UINT8   MipiCam_Link2_DriverData_VoltageRail;
  UINT8   MipiCam_Link2_DriverData_PprValue;
  UINT8   MipiCam_Link2_DriverData_PprUnit;

  UINT8   MipiCam_Link3_SensorModel;         // IMX135 / OV5693 / IMX179 / OV8858 / OV2740-IVCAM / IMX208 / OV9728 / IMX188 / User3
  UINT16  MipiCam_Link3_UserHid[MIPICAM_HID_LENGTH];
  UINT8   MipiCam_Link3_CameraPhysicalLocation;
  UINT16  MipiCam_Link3_ModuleName[MIPICAM_MODULE_NAME_LENGTH];
  UINT8   MipiCam_Link3_I2cDevicesEnabled;   // number of I2C devices defined for this link
  UINT8   MipiCam_Link3_I2cChannel;
  UINT16  MipiCam_Link3_I2cAddress[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link3_I2cDeviceType[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link3_DriverData_Version;
  UINT8   MipiCam_Link3_DriverData_CrdVersion;
  UINT8   MipiCam_Link3_DriverData_LaneUsed;
  UINT8   MipiCam_Link3_DriverData_EepromType;
  UINT8   MipiCam_Link3_DriverData_VcmType;
  UINT8   MipiCam_Link3_DriverData_CustomData[4];
  UINT32  MipiCam_Link3_DriverData_Mclk;
  UINT8   MipiCam_Link3_DriverData_ControlLogic;
  UINT8   MipiCam_Link3_DriverData_FlashSupport;
  UINT8   MipiCam_Link3_DriverData_PrivacyLed;
  UINT8   MipiCam_Link3_DriverData_Degree;
  UINT8   MipiCam_Link3_DriverData_PmicPosition;
  UINT8   MipiCam_Link3_DriverData_VoltageRail;
  UINT8   MipiCam_Link3_DriverData_PprValue;
  UINT8   MipiCam_Link3_DriverData_PprUnit;

  UINT8   MipiCam_Link4_SensorModel;         // IMX135 / OV5693 / IMX179 / OV8858 / OV2740-IVCAM / IMX208 / OV9728 / IMX188 / User3
  UINT16  MipiCam_Link4_UserHid[MIPICAM_HID_LENGTH];
  UINT8   MipiCam_Link4_CameraPhysicalLocation;
  UINT16  MipiCam_Link4_ModuleName[MIPICAM_MODULE_NAME_LENGTH];
  UINT8   MipiCam_Link4_I2cDevicesEnabled;   // number of I2C devices defined for this link
  UINT8   MipiCam_Link4_I2cChannel;
  UINT16  MipiCam_Link4_I2cAddress[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link4_I2cDeviceType[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link4_DriverData_Version;
  UINT8   MipiCam_Link4_DriverData_CrdVersion;
  UINT8   MipiCam_Link4_DriverData_LaneUsed;
  UINT8   MipiCam_Link4_DriverData_EepromType;
  UINT8   MipiCam_Link4_DriverData_VcmType;
  UINT8   MipiCam_Link4_DriverData_CustomData[4];
  UINT32  MipiCam_Link4_DriverData_Mclk;
  UINT8   MipiCam_Link4_DriverData_ControlLogic;
  UINT8   MipiCam_Link4_DriverData_FlashSupport;
  UINT8   MipiCam_Link4_DriverData_PrivacyLed;
  UINT8   MipiCam_Link4_DriverData_Degree;
  UINT8   MipiCam_Link4_DriverData_PmicPosition;
  UINT8   MipiCam_Link4_DriverData_VoltageRail;
  UINT8   MipiCam_Link4_DriverData_PprValue;
  UINT8   MipiCam_Link4_DriverData_PprUnit;

  UINT8   MipiCam_Link5_SensorModel;         // IMX135 / OV5693 / IMX179 / OV8858 / OV2740-IVCAM / IMX208 / OV9728 / IMX188 / User3
  UINT16  MipiCam_Link5_UserHid[MIPICAM_HID_LENGTH];
  UINT8   MipiCam_Link5_CameraPhysicalLocation;
  UINT16  MipiCam_Link5_ModuleName[MIPICAM_MODULE_NAME_LENGTH];
  UINT8   MipiCam_Link5_I2cDevicesEnabled;   // number of I2C devices defined for this link
  UINT8   MipiCam_Link5_I2cChannel;
  UINT16  MipiCam_Link5_I2cAddress[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link5_I2cDeviceType[MIPICAM_I2C_DEVICES_COUNT];
  UINT8   MipiCam_Link5_DriverData_Version;
  UINT8   MipiCam_Link5_DriverData_CrdVersion;
  UINT8   MipiCam_Link5_DriverData_LaneUsed;
  UINT8   MipiCam_Link5_DriverData_EepromType;
  UINT8   MipiCam_Link5_DriverData_VcmType;
  UINT8   MipiCam_Link5_DriverData_CustomData[4];
  UINT32  MipiCam_Link5_DriverData_Mclk;
  UINT8   MipiCam_Link5_DriverData_ControlLogic;
  UINT8   MipiCam_Link5_DriverData_FlashSupport;
  UINT8   MipiCam_Link5_DriverData_PrivacyLed;
  UINT8   MipiCam_Link5_DriverData_Degree;
  UINT8   MipiCam_Link5_DriverData_PmicPosition;
  UINT8   MipiCam_Link5_DriverData_VoltageRail;
  UINT8   MipiCam_Link5_DriverData_PprValue;
  UINT8   MipiCam_Link5_DriverData_PprUnit;

  UINT8   PchI2cSensorDevicePort[PCH_MAX_SERIALIO_I2C_CONTROLLERS];

  UINT8   PchI2cTouchPadType;
  UINT8   PchI2cTouchPadIrqMode;
  UINT8   PchI2cTouchPadBusAddress;
  UINT16  PchI2cTouchPadHidAddress;
  UINT8   PchI2cTouchPadSpeed;

  UINT8   PchI2cTouchPanelType;
  UINT8   PchI2cTouchPanelIrqMode;
  UINT8   PchI2cTouchPanelBusAddress;
  UINT16  PchI2cTouchPanelHidAddress;
  UINT8   PchI2cTouchPanelSpeed;

  UINT8   PchSpiSensorDevicePort[PCH_MAX_SERIALIO_SPI_CONTROLLERS];
  UINT8   PchSpiFingerPrintType;
  UINT8   PchSpiSensorIrqMode;

  UINT8   PchUart1SensorDevice;
  UINT8   PchUart2SensorDevice;
  UINT8   PchI2cWittDevice;
  UINT8   PchI2cWittVersion;
  UINT8   PchUartUtkDevice;
  UINT8   DiscreteBtModule;
  UINT8   DiscreteBtModuleIrqMode;

  UINT8   PchI2cSpeed[PCH_MAX_SERIALIO_I2C_CONTROLLERS];

  UINT8   PchSerialIoUseTimingParameters;

  UINT16  PchSerialIoTimingSSH0;  // [SSH0] SSCN-HIGH for I2C0
  UINT16  PchSerialIoTimingSSL0;  // [SSL0] SSCN-LOW  for I2C0
  UINT16  PchSerialIoTimingSSD0;  // [SSD0] SSCN-HOLD for I2C0
  UINT16  PchSerialIoTimingFMH0;  // [FMH0] FMCN-HIGH for I2C0
  UINT16  PchSerialIoTimingFML0;  // [FML0] FMCN-LOW  for I2C0
  UINT16  PchSerialIoTimingFMD0;  // [FMD0] FMCN-HOLD for I2C0
  UINT16  PchSerialIoTimingFPH0;  // [FPH0] FPCN-HIGH for I2C0
  UINT16  PchSerialIoTimingFPL0;  // [FPL0] FPCN-LOW  for I2C0
  UINT16  PchSerialIoTimingFPD0;  // [FPD0] FPCN-HOLD for I2C0
  UINT16  PchSerialIoTimingHSH0;  // [HSH0] HSCN-HIGH for I2C0
  UINT16  PchSerialIoTimingHSL0;  // [HSL0] HSCN-LOW  for I2C0
  UINT16  PchSerialIoTimingHSD0;  // [HSD0] HSCN-HOLD for I2C0

  UINT16  PchSerialIoTimingSSH1;  // [SSH1] SSCN-HIGH for I2C1
  UINT16  PchSerialIoTimingSSL1;  // [SSL1] SSCN-LOW  for I2C1
  UINT16  PchSerialIoTimingSSD1;  // [SSD1] SSCN-HOLD for I2C1
  UINT16  PchSerialIoTimingFMH1;  // [FMH1] FMCN-HIGH for I2C1
  UINT16  PchSerialIoTimingFML1;  // [FML1] FMCN-LOW  for I2C1
  UINT16  PchSerialIoTimingFMD1;  // [FMD1] FMCN-HOLD for I2C1
  UINT16  PchSerialIoTimingFPH1;  // [FPH1] FPCN-HIGH for I2C1
  UINT16  PchSerialIoTimingFPL1;  // [FPL1] FPCN-LOW  for I2C1
  UINT16  PchSerialIoTimingFPD1;  // [FPD1] FPCN-HOLD for I2C1
  UINT16  PchSerialIoTimingHSH1;  // [HSH1] HSCN-HIGH for I2C1
  UINT16  PchSerialIoTimingHSL1;  // [HSL1] HSCN-LOW  for I2C1
  UINT16  PchSerialIoTimingHSD1;  // [HSD1] HSCN-HOLD for I2C1

  UINT16  PchSerialIoTimingSSH2;  // [SSH2] SSCN-HIGH for I2C2
  UINT16  PchSerialIoTimingSSL2;  // [SSL2] SSCN-LOW  for I2C2
  UINT16  PchSerialIoTimingSSD2;  // [SSD2] SSCN-HOLD for I2C2
  UINT16  PchSerialIoTimingFMH2;  // [FMH2] FMCN-HIGH for I2C2
  UINT16  PchSerialIoTimingFML2;  // [FML2] FMCN-LOW  for I2C2
  UINT16  PchSerialIoTimingFMD2;  // [FMD2] FMCN-HOLD for I2C2
  UINT16  PchSerialIoTimingFPH2;  // [FPH2] FPCN-HIGH for I2C2
  UINT16  PchSerialIoTimingFPL2;  // [FPL2] FPCN-LOW  for I2C2
  UINT16  PchSerialIoTimingFPD2;  // [FPD2] FPCN-HOLD for I2C2
  UINT16  PchSerialIoTimingHSH2;  // [HSH2] HSCN-HIGH for I2C2
  UINT16  PchSerialIoTimingHSL2;  // [HSL2] HSCN-LOW  for I2C2
  UINT16  PchSerialIoTimingHSD2;  // [HSD2] HSCN-HOLD for I2C2

  UINT16  PchSerialIoTimingSSH3;  // [SSH3] SSCN-HIGH for I2C3
  UINT16  PchSerialIoTimingSSL3;  // [SSL3] SSCN-LOW  for I2C3
  UINT16  PchSerialIoTimingSSD3;  // [SSD3] SSCN-HOLD for I2C3
  UINT16  PchSerialIoTimingFMH3;  // [FMH3] FMCN-HIGH for I2C3
  UINT16  PchSerialIoTimingFML3;  // [FML3] FMCN-LOW  for I2C3
  UINT16  PchSerialIoTimingFMD3;  // [FMD3] FMCN-HOLD for I2C3
  UINT16  PchSerialIoTimingFPH3;  // [FPH3] FPCN-HIGH for I2C3
  UINT16  PchSerialIoTimingFPL3;  // [FPL3] FPCN-LOW  for I2C3
  UINT16  PchSerialIoTimingFPD3;  // [FPD3] FPCN-HOLD for I2C3
  UINT16  PchSerialIoTimingHSH3;  // [HSH3] HSCN-HIGH for I2C3
  UINT16  PchSerialIoTimingHSL3;  // [HSL3] HSCN-LOW  for I2C3
  UINT16  PchSerialIoTimingHSD3;  // [HSD3] HSCN-HOLD for I2C3

  UINT16  PchSerialIoTimingSSH4;  // [SSH4] SSCN-HIGH for I2C4
  UINT16  PchSerialIoTimingSSL4;  // [SSL4] SSCN-LOW  for I2C4
  UINT16  PchSerialIoTimingSSD4;  // [SSD4] SSCN-HOLD for I2C4
  UINT16  PchSerialIoTimingFMH4;  // [FMH4] FMCN-HIGH for I2C4
  UINT16  PchSerialIoTimingFML4;  // [FML4] FMCN-LOW  for I2C4
  UINT16  PchSerialIoTimingFMD4;  // [FMD4] FMCN-HOLD for I2C4
  UINT16  PchSerialIoTimingFPH4;  // [FPH4] FPCN-HIGH for I2C4
  UINT16  PchSerialIoTimingFPL4;  // [FPL4] FPCN-LOW  for I2C4
  UINT16  PchSerialIoTimingFPD4;  // [FPD4] FPCN-HOLD for I2C4
  UINT16  PchSerialIoTimingHSH4;  // [HSH4] HSCN-HIGH for I2C4
  UINT16  PchSerialIoTimingHSL4;  // [HSL4] HSCN-LOW  for I2C4
  UINT16  PchSerialIoTimingHSD4;  // [HSD4] HSCN-HOLD for I2C4

  UINT16  PchSerialIoTimingSSH5;  // [SSH5] SSCN-HIGH for I2C5
  UINT16  PchSerialIoTimingSSL5;  // [SSL5] SSCN-LOW  for I2C5
  UINT16  PchSerialIoTimingSSD5;  // [SSD5] SSCN-HOLD for I2C5
  UINT16  PchSerialIoTimingFMH5;  // [FMH5] FMCN-HIGH for I2C5
  UINT16  PchSerialIoTimingFML5;  // [FML5] FMCN-LOW  for I2C5
  UINT16  PchSerialIoTimingFMD5;  // [FMD5] FMCN-HOLD for I2C5
  UINT16  PchSerialIoTimingFPH5;  // [FPH5] FPCN-HIGH for I2C5
  UINT16  PchSerialIoTimingFPL5;  // [FPL5] FPCN-LOW  for I2C5
  UINT16  PchSerialIoTimingFPD5;  // [FPD5] FPCN-HOLD for I2C5
  UINT16  PchSerialIoTimingHSH5;  // [HSH5] HSCN-HIGH for I2C5
  UINT16  PchSerialIoTimingHSL5;  // [HSL5] HSCN-LOW  for I2C5
  UINT16  PchSerialIoTimingHSD5;  // [HSD5] HSCN-HOLD for I2C5

  UINT16  PchSerialIoTimingSSH6;  // [SSH6] SSCN-HIGH for I2C6
  UINT16  PchSerialIoTimingSSL6;  // [SSL6] SSCN-LOW  for I2C6
  UINT16  PchSerialIoTimingSSD6;  // [SSD6] SSCN-HOLD for I2C6
  UINT16  PchSerialIoTimingFMH6;  // [FMH6] FMCN-HIGH for I2C6
  UINT16  PchSerialIoTimingFML6;  // [FML6] FMCN-LOW  for I2C6
  UINT16  PchSerialIoTimingFMD6;  // [FMD6] FMCN-HOLD for I2C6
  UINT16  PchSerialIoTimingFPH6;  // [FPH6] FPCN-HIGH for I2C6
  UINT16  PchSerialIoTimingFPL6;  // [FPL6] FPCN-LOW  for I2C6
  UINT16  PchSerialIoTimingFPD6;  // [FPD6] FPCN-HOLD for I2C6
  UINT16  PchSerialIoTimingHSH6;  // [HSH6] HSCN-HIGH for I2C6
  UINT16  PchSerialIoTimingHSL6;  // [HSL6] HSCN-LOW  for I2C6
  UINT16  PchSerialIoTimingHSD6;  // [HSD6] HSCN-HOLD for I2C6

  UINT16  PchSerialIoTimingSSH7;  // [SSH7] SSCN-HIGH for I2C7
  UINT16  PchSerialIoTimingSSL7;  // [SSL7] SSCN-LOW  for I2C7
  UINT16  PchSerialIoTimingSSD7;  // [SSD7] SSCN-HOLD for I2C7
  UINT16  PchSerialIoTimingFMH7;  // [FMH7] FMCN-HIGH for I2C7
  UINT16  PchSerialIoTimingFML7;  // [FML7] FMCN-LOW  for I2C7
  UINT16  PchSerialIoTimingFMD7;  // [FMD7] FMCN-HOLD for I2C7
  UINT16  PchSerialIoTimingFPH7;  // [FPH7] FPCN-HIGH for I2C7
  UINT16  PchSerialIoTimingFPL7;  // [FPL7] FPCN-LOW  for I2C7
  UINT16  PchSerialIoTimingFPD7;  // [FPD7] FPCN-HOLD for I2C7
  UINT16  PchSerialIoTimingHSH7;  // [HSH7] HSCN-HIGH for I2C7
  UINT16  PchSerialIoTimingHSL7;  // [HSL7] HSCN-LOW  for I2C7
  UINT16  PchSerialIoTimingHSD7;  // [HSD7] HSCN-HOLD for I2C7

  UINT16  PchSerialIoTimingM0C0;  // [M0C0] M0D3 for I2C0
  UINT16  PchSerialIoTimingM1C0;  // [M1C0] M1D3 for I2C0
  UINT16  PchSerialIoTimingM0C1;  // [M0C1] M0D3 for I2C1
  UINT16  PchSerialIoTimingM1C1;  // [M1C1] M1D3 for I2C1
  UINT16  PchSerialIoTimingM0C2;  // [M0C2] M0D3 for I2C2
  UINT16  PchSerialIoTimingM1C2;  // [M1C2] M1D3 for I2C2
  UINT16  PchSerialIoTimingM0C3;  // [M0C3] M0D3 for I2C3
  UINT16  PchSerialIoTimingM1C3;  // [M1C3] M1D3 for I2C3
  UINT16  PchSerialIoTimingM0C4;  // [M0C4] M0D3 for I2C4
  UINT16  PchSerialIoTimingM1C4;  // [M1C4] M1D3 for I2C4
  UINT16  PchSerialIoTimingM0C5;  // [M0C5] M0D3 for I2C5
  UINT16  PchSerialIoTimingM1C5;  // [M1C5] M1D3 for I2C5
  UINT16  PchSerialIoTimingM0C6;  // [M0C6] M0D3 for SPI0
  UINT16  PchSerialIoTimingM1C6;  // [M1C6] M1D3 for SPI0
  UINT16  PchSerialIoTimingM0C7;  // [M0C7] M0D3 for SPI1
  UINT16  PchSerialIoTimingM1C7;  // [M1C7] M1D3 for SPI1
  UINT16  PchSerialIoTimingM0C8;  // [M0C8] M0D3 for SPI2
  UINT16  PchSerialIoTimingM1C8;  // [M1C8] M1D3 for SPI2
  UINT16  PchSerialIoTimingM0C9;  // [M0C9] M0D3 for UART0
  UINT16  PchSerialIoTimingM1C9;  // [M1C9] M1D3 for UART0
  UINT16  PchSerialIoTimingM0CA;  // [M0CA] M0D3 for UART1
  UINT16  PchSerialIoTimingM1CA;  // [M1CA] M1D3 for UART1
  UINT16  PchSerialIoTimingM0CB;  // [M0CB] M0D3 for UART2
  UINT16  PchSerialIoTimingM1CB;  // [M1CB] M1D3 for UART2
  UINT16  PchSerialIoTimingM0CC;  // [M0CC] M0D3 for I2C6
  UINT16  PchSerialIoTimingM1CC;  // [M1CC] M1D3 for I2C6
  UINT16  PchSerialIoTimingM0CD;  // [M0CD] M0D3 for I2C7
  UINT16  PchSerialIoTimingM1CD;  // [M1CD] M1D3 for I2C7

  UINT8   Ps2KbMsEnable;
  UINT8   TouchPanelMuxSelector;

  UINT8   Ac1TripPoint;
  UINT8   Ac0TripPoint;
  UINT8   Ac1FanSpeed;
  UINT8   Ac0FanSpeed;
  UINT8   PassiveThermalTripPoint;
  UINT8   CriticalThermalTripPoint;
  UINT8   PassiveTc1Value;
  UINT8   PassiveTc2Value;
  UINT8   PassiveTspValue;
  UINT8   DisableActiveTripPoints;
  UINT8   DisablePassiveTripPoints;
  UINT8   DisableCriticalTripPoints;
  UINT8   PmicVccLevel;
  UINT8   PmicVddqLevel;
  UINT8   TwoComponents;

  UINT8   CPUTempReadEnable;
  UINT8   CPUEnergyReadEnable;
  UINT8   PCHTempReadEnable;
  UINT8   AlertEnableLock;
  UINT8   PchAlert;
  UINT8   DimmAlert;
  UINT8   CpuTemp;
  UINT8   CpuFanSpeed;

  //
  // DPTF SETUP items begin
  //
  UINT8   EnableDptf;
  UINT8   EnableDCFG;

  UINT8   EnableSaDevice;
  UINT8   ActiveThermalTripPointSA;
  UINT8   PassiveThermalTripPointSA;
  UINT8   CriticalThermalTripPointSA;
  UINT8   CriticalThermalTripPointSaS3;
  UINT8   ThermalSamplingPeriodSA;
  UINT8   HotThermalTripPointSA;
  UINT32  PpccStepSize;
  UINT8   LPOEnable;
  UINT8   LPOStartPState;
  UINT8   LPOStepSize;
  UINT8   LPOPowerControlSetting;
  UINT8   LPOPerformanceControlSetting;
  UINT16  MinPowerLimit0;
  UINT16  MinPowerLimit1;
  UINT16  MinPowerLimit2;
  UINT8   EnableCtdpPolicy;

  UINT8   EnableFan1Device;

  UINT8   EnableDisplayParticipant;
  UINT8   DisplayDepthUpperLimit;
  UINT8   DisplayDepthLowerLimit;

  UINT8   EnableWrlsParticipant;
  UINT8   ActiveThermalTripPointWrls;
  UINT8   PassiveThermalTripPointWrls;
  UINT8   CriticalThermalTripPointWrls;
  UINT8   CriticalThermalTripPointWrlsS3;
  UINT8   HotThermalTripPointWrls;
  UINT8   ThermalSamplingPeriodWrls;

  UINT8   EnableWWANParticipant;
  UINT8   ActiveThermalTripPointWWAN;
  UINT8   PassiveThermalTripPointWWAN;
  UINT8   CriticalThermalTripPointWWAN;
  UINT8   CriticalThermalTripPointWwanS3;
  UINT8   HotThermalTripPointWWAN;

  UINT8   EnableChargerParticipant;
  UINT8   EnablePowerParticipant;
  UINT16  PowerParticipantPollingRate;
  UINT8   EnablePowerBossPolicy;

  UINT8   Enable2DCameraParticipant;

  UINT8   EnableBatteryParticipant;

  UINT8   EnableStorageParticipantST1;
  UINT8   ActiveThermalTripPointST1;
  UINT8   PassiveThermalTripPointST1;
  UINT8   CriticalThermalTripPointST1;
  UINT8   CriticalThermalTripPointS3ST1;
  UINT8   HotThermalTripPointST1;

  UINT8   EnableStorageParticipantST2;
  UINT8   ActiveThermalTripPointST2;
  UINT8   PassiveThermalTripPointST2;
  UINT8   CriticalThermalTripPointST2;
  UINT8   CriticalThermalTripPointS3ST2;
  UINT8   HotThermalTripPointST2;

  UINT8   EnableVS1Participant;
  UINT8   ActiveThermalTripPointVS1;
  UINT8   PassiveThermalTripPointVS1;
  UINT8   CriticalThermalTripPointVS1;
  UINT8   CriticalThermalTripPointVS1S3;
  UINT8   HotThermalTripPointVS1;

  UINT8   EnableVS2Participant;
  UINT8   ActiveThermalTripPointVS2;
  UINT8   PassiveThermalTripPointVS2;
  UINT8   CriticalThermalTripPointVS2;
  UINT8   CriticalThermalTripPointVS2S3;
  UINT8   HotThermalTripPointVS2;

  UINT8   EnableSen1ParticipantSupport;
  UINT8   EnableSen1Participant;
  UINT8   ActiveThermalTripPointSen1;
  UINT8   PassiveThermalTripPointSen1;
  UINT8   CriticalThermalTripPointSen1;
  UINT8   CriticalThermalTripPointSen1S3;
  UINT8   HotThermalTripPointSen1;
  UINT8   SensorSamplingPeriodSen1;

  UINT8   EnableSen2Participant;
  UINT8   ActiveThermalTripPointSen2;
  UINT8   PassiveThermalTripPointSen2;
  UINT8   CriticalThermalTripPointSen2;
  UINT8   CriticalThermalTripPointSen2S3;
  UINT8   HotThermalTripPointSen2;
  UINT8   SensorSamplingPeriodSen2;

  UINT8   EnableSen3Participant;
  UINT8   ActiveThermalTripPointSen3;
  UINT8   PassiveThermalTripPointSen3;
  UINT8   CriticalThermalTripPointSen3;
  UINT8   CriticalThermalTripPointSen3S3;
  UINT8   HotThermalTripPointSen3;
  UINT8   SensorSamplingPeriodSen3;

  UINT8   EnableSen4Participant;
  UINT8   ActiveThermalTripPointSen4;
  UINT8   PassiveThermalTripPointSen4;
  UINT8   CriticalThermalTripPointSen4;
  UINT8   CriticalThermalTripPointSen4S3;
  UINT8   HotThermalTripPointSen4;
  UINT8   SensorSamplingPeriodSen4;

  UINT8   EnableSen5Participant;
  UINT8   ActiveThermalTripPointSen5;
  UINT8   PassiveThermalTripPointSen5;
  UINT8   CriticalThermalTripPointSen5;
  UINT8   CriticalThermalTripPointSen5S3;
  UINT8   HotThermalTripPointSen5;
  UINT8   SensorSamplingPeriodSen5;

  UINT8   EnablePchFivrParticipant;

  UINT8   EnableActivePolicy;
  UINT8   EnablePassivePolicy;
  UINT8   TrtRevision;
  UINT8   EnableCriticalPolicy;
  UINT8   EnableRFIMPolicy;
  UINT8   EnableAPPolicy;
  UINT8   EnableVSPolicy;
  UINT8   EnablePIDPolicy;

  UINT8   PpccObject;
  UINT8   PdrtObject;
  UINT8   ArtgObject;
  UINT8   PmaxObject;
  UINT8   Tmp1Object;
  UINT8   Tmp2Object;
  UINT8   Tmp3Object;
  UINT8   Tmp4Object;
  UINT8   Tmp5Object;
  UINT8   Tmp6Object;
  UINT8   Tmp7Object;
  UINT8   Tmp8Object;
  UINT8   OptionalObjects;

  UINT8   OemDesignVariable0;
  UINT8   OemDesignVariable1;
  UINT8   OemDesignVariable2;
  UINT8   OemDesignVariable3;
  UINT8   OemDesignVariable4;
  UINT8   OemDesignVariable5;

  //
  // DPTF SETUP items end
  //
  UINT8   Rtd3Support;
  UINT8   Rtd3P0dl;
  UINT8   Rtd3UsbPt1;
  UINT8   Rtd3UsbPt2;
  UINT16  Rtd3AudioDelay;
  UINT16  Rtd3TouchPadDelay;
  UINT16  Rtd3TouchPanelDelay;
  UINT16  Rtd3SensorHub;
  UINT16  VRRampUpDelay;
  UINT8   PstateCapping;
  UINT8   Rtd3ZpoddSupport;
  UINT8   Rtd3Zpodd;
  UINT8   Rtd3WWAN;
  UINT8   Rtd3SataPort0;
  UINT8   Rtd3SataPort1;
  UINT8   Rtd3SataPort2;
  UINT8   Rtd3SataPort3;
  UINT8   Rtd3SataPort4;
  UINT8   Rtd3SataPort5;
  UINT8   Rtd3WaGpio;
  UINT8   Rtd3RemapCR1;
  UINT8   Rtd3RemapCR2;
  UINT8   Rtd3RemapCR3;
  UINT8   Rtd3I2CTouchPanel;

  UINT8   PowerSharingManagerEnable;
  UINT8   PsmSplcDomainType1;
  UINT32  PsmSplcPowerLimit1;
  UINT32  PsmSplcTimeWindow1;

  UINT8   PsmDplcDomainType1;
  UINT8   PsmDplcDomainPreference1;
  UINT16  PsmDplcPowerLimitIndex1;
  UINT16  PsmDplcDefaultPowerLimit1;
  UINT32  PsmDplcDefaultTimeWindow1;
  UINT16  PsmDplcMinimumPowerLimit1;
  UINT16  PsmDplcMaximumPowerLimit1;
  UINT16  PsmDplcMaximumTimeWindow1;

  UINT8   WifiEnable;
  UINT8   WifiDomainType1;
  UINT16  WifiPowerLimit1;
  UINT32  WifiTimeWindow1;
  UINT8   TRxDelay0;
  UINT8   TRxCableLength0;
  UINT8   TRxDelay1;
  UINT8   TRxCableLength1;
  UINT8   WrddDomainType1;
  UINT16  WrddCountryIndentifier1;
  UINT8   WrddDomainType2;
  UINT16  WrddCountryIndentifier2;
  UINT8   WrdsWiFiSarEnable;
  UINT8   WrdsWiFiSarTxPowerSet1Limit1;
  UINT8   WrdsWiFiSarTxPowerSet1Limit2;
  UINT8   WrdsWiFiSarTxPowerSet1Limit3;
  UINT8   WrdsWiFiSarTxPowerSet1Limit4;
  UINT8   WrdsWiFiSarTxPowerSet1Limit5;
  UINT8   WrdsWiFiSarTxPowerSet1Limit6;
  UINT8   WrdsWiFiSarTxPowerSet1Limit7;
  UINT8   WrdsWiFiSarTxPowerSet1Limit8;
  UINT8   WrdsWiFiSarTxPowerSet1Limit9;
  UINT8   WrdsWiFiSarTxPowerSet1Limit10;

  UINT8   EwrdWiFiDynamicSarEnable;
  UINT8   EwrdWiFiDynamicSarRangeSets;
  UINT8   EwrdWiFiSarTxPowerSet2Limit1;
  UINT8   EwrdWiFiSarTxPowerSet2Limit2;
  UINT8   EwrdWiFiSarTxPowerSet2Limit3;
  UINT8   EwrdWiFiSarTxPowerSet2Limit4;
  UINT8   EwrdWiFiSarTxPowerSet2Limit5;
  UINT8   EwrdWiFiSarTxPowerSet2Limit6;
  UINT8   EwrdWiFiSarTxPowerSet2Limit7;
  UINT8   EwrdWiFiSarTxPowerSet2Limit8;
  UINT8   EwrdWiFiSarTxPowerSet2Limit9;
  UINT8   EwrdWiFiSarTxPowerSet2Limit10;
  UINT8   EwrdWiFiSarTxPowerSet3Limit1;
  UINT8   EwrdWiFiSarTxPowerSet3Limit2;
  UINT8   EwrdWiFiSarTxPowerSet3Limit3;
  UINT8   EwrdWiFiSarTxPowerSet3Limit4;
  UINT8   EwrdWiFiSarTxPowerSet3Limit5;
  UINT8   EwrdWiFiSarTxPowerSet3Limit6;
  UINT8   EwrdWiFiSarTxPowerSet3Limit7;
  UINT8   EwrdWiFiSarTxPowerSet3Limit8;
  UINT8   EwrdWiFiSarTxPowerSet3Limit9;
  UINT8   EwrdWiFiSarTxPowerSet3Limit10;
  UINT8   EwrdWiFiSarTxPowerSet4Limit1;
  UINT8   EwrdWiFiSarTxPowerSet4Limit2;
  UINT8   EwrdWiFiSarTxPowerSet4Limit3;
  UINT8   EwrdWiFiSarTxPowerSet4Limit4;
  UINT8   EwrdWiFiSarTxPowerSet4Limit5;
  UINT8   EwrdWiFiSarTxPowerSet4Limit6;
  UINT8   EwrdWiFiSarTxPowerSet4Limit7;
  UINT8   EwrdWiFiSarTxPowerSet4Limit8;
  UINT8   EwrdWiFiSarTxPowerSet4Limit9;
  UINT8   EwrdWiFiSarTxPowerSet4Limit10;
  UINT8   WgdsWiFiSarDeltaGroup1PowerMax1;
  UINT8   WgdsWiFiSarDeltaGroup1PowerChainA1;
  UINT8   WgdsWiFiSarDeltaGroup1PowerChainB1;
  UINT8   WgdsWiFiSarDeltaGroup1PowerMax2;
  UINT8   WgdsWiFiSarDeltaGroup1PowerChainA2;
  UINT8   WgdsWiFiSarDeltaGroup1PowerChainB2;
  UINT8   WgdsWiFiSarDeltaGroup2PowerMax1;
  UINT8   WgdsWiFiSarDeltaGroup2PowerChainA1;
  UINT8   WgdsWiFiSarDeltaGroup2PowerChainB1;
  UINT8   WgdsWiFiSarDeltaGroup2PowerMax2;
  UINT8   WgdsWiFiSarDeltaGroup2PowerChainA2;
  UINT8   WgdsWiFiSarDeltaGroup2PowerChainB2;
  UINT8   WgdsWiFiSarDeltaGroup3PowerMax1;
  UINT8   WgdsWiFiSarDeltaGroup3PowerChainA1;
  UINT8   WgdsWiFiSarDeltaGroup3PowerChainB1;
  UINT8   WgdsWiFiSarDeltaGroup3PowerMax2;
  UINT8   WgdsWiFiSarDeltaGroup3PowerChainA2;
  UINT8   WgdsWiFiSarDeltaGroup3PowerChainB2;
  UINT8   WiFiDynamicSarAntennaACurrentSet;
  UINT8   WiFiDynamicSarAntennaBCurrentSet;

  UINT8   BluetoothSar;
  UINT8   BluetoothSarBr;
  UINT8   BluetoothSarEdr2;
  UINT8   BluetoothSarEdr3;
  UINT8   BluetoothSarLe;
  UINT8   BluetoothSarLe2Mhz;
  UINT8   BluetoothSarLeLr;

  UINT8   AntennaDiversity;
  UINT8   CoExistenceManager;
  UINT8   PrebootBleEnable;
  UINT16  BleReconnectionDelay;
  UINT8   UsbFnEnable;

  UINT8   CsmControl; // This member deprecated for EHL and should be deleted in next generation

  UINT8   FanControl;
  UINT8   CpuFanControl;
  UINT8   LowestFanSpeed;

  //
  // Thunderbolt(TM)
  //
  UINT8   TbtSetupFormSupport;
  UINT8   TbtSetupDTbtPegTypeSupport;
  UINT8   DiscreteTbtSupport;
  UINT8   IntegratedTbtSupport;
  UINT8   TbtPcieSupport;
  UINT8   TbtUsbOn;
  UINT8   TbtBootOn;
  UINT8   TbtWakeupSupport;
  UINT8   Gpio3ForcePwr;
  UINT16  Gpio3ForcePwrDly;
  UINT8   SecurityMode;
  UINT8   CallSmiBeforeBoot;
  UINT8   TBTHotSMI;
  UINT8   Gpio5Filter;
  UINT8   TBTHotNotify;
  UINT8   EnableMsiInFadt;
  UINT8   DTbtController[DTBT_CONTROLLER_SUPPORTED];
  UINT8   DTbtControllerType[DTBT_CONTROLLER_SUPPORTED];
  UINT8   TBTSetClkReq;
  UINT8   TbtAspm;
  UINT8   TbtLtr;
  UINT8   DTbthostRouterPortNumber[DTBT_CONTROLLER_SUPPORTED];
  UINT8   DTbtPcieExtraBusRsvd[DTBT_CONTROLLER_SUPPORTED];
  UINT16  DTbtPcieMemRsvd[DTBT_CONTROLLER_SUPPORTED];
  UINT8   DTbtPcieIoRsvd[DTBT_CONTROLLER_SUPPORTED];
  UINT8   DTbtPcieMemAddrRngMax[DTBT_CONTROLLER_SUPPORTED];
  UINT16  DTbtPciePMemRsvd[DTBT_CONTROLLER_SUPPORTED];
  UINT8   DTbtPciePMemAddrRngMax[DTBT_CONTROLLER_SUPPORTED];
  UINT8   Win10Support;
  UINT8   TrOsup;
  UINT8   TbtL1SubStates;
  UINT8   TbtPtm;
  UINT8   OsNativeResourceBalance;
  UINT8   TbtAcDcSwitch;
  UINT8   TbtLegacyModeSupport;
  // ITBT Specific Setup Options
  UINT8   ITbtPcieRootPortSupported[ITBT_ROOT_PORTS_SUPPORTED];
  UINT8   ITbtRootPort[ITBT_ROOT_PORTS_SUPPORTED];
  UINT8   ITbtPcieExtraBusRsvd[ITBT_ROOT_PORTS_SUPPORTED];
  UINT16  ITbtPcieMemRsvd[ITBT_ROOT_PORTS_SUPPORTED];
  UINT8   ITbtPcieMemAddrRngMax[ITBT_ROOT_PORTS_SUPPORTED];
  UINT16  ITbtPciePMemRsvd[ITBT_ROOT_PORTS_SUPPORTED];
  UINT8   ITbtPciePMemAddrRngMax[ITBT_ROOT_PORTS_SUPPORTED];
  UINT16  ITbtForcePowerOnTimeoutInMs;
  UINT16  ITbtConnectTopologyTimeoutInMs;
  UINT16  ReserveMemoryPerSlot;
  UINT16  ReservePMemoryPerSlot;
  UINT8   ReserveIoPerSlot;
  UINT8   TbtSkipPciOprom;
  UINT8   TbtAcpiRemovalSupport;

  UINT8   OcWdtEnabled;
  UINT8   IccLockRegisters;
  UINT8   IccProfile;
  UINT8   ShowProfile;
  UINT8   NumProfiles;
  UINT8   IccPllShutdownEnabled;

  UINT8   CsModeFirst;
  UINT8   CsMode;
  UINT8   CsModeChanged;

  UINT8   PlatformUnstable;
  UINT8   IsOcDefaultsInitalized;

  UINT8   SecureEraseModeRealMode;
  UINT8   ForceSecureErase;

  UINT8   HidEventFilterDriverEnable;


  UINT8   PmicSlpS0VmSupport;
  UINT8   HebcValueSupport;
  UINT32  HebcValue;

  UINT8   I2cSarResetDelay;

  UINT8   WwanEnable;

  UINT8   UsbcBiosTcssHandshake;
  // EC - BIOS handshake timeouts
  UINT32  UsbConnStatusTimeout;
  UINT32  UsbcSxEntryTimeout;
  UINT32  UsbcSxExitTimeout;


  UINT8   VtioSupport;
  UINT8   SdevCio2Entry;
  UINT8   SdevIspEntry;
  UINT8   SdevHeciEntry;
  UINT8   SdevSpi1Entry;
  UINT8   SdevSpi2Entry;
  UINT8   SdevXhciEntry;
  UINT16  SdevNumberOfSensors[5];
  UINT16  SdevSensorEntry1[5];
  UINT16  SdevSensorEntry2[5];

  UINT8   EcChargingMethod;
  UINT8   AlternateModeSynchDelay;
  UINT8   WakeOnWiGigSupport;

  UINT8   SystemTimeAndAlarmSource; // Select source for system time and alarm

  UINT8   TrustedDeviceSetupBoot;
  UINT8   TestUsbUnlockForNoa;

  UINT8   EnableCrashLog;
  UINT8   CrashLogOnAllReset;

  UINT8   SysFwUpdateLoadDefault;
  UINT8   SysFwUpdateSkipPowerCheck;

  UINT8   BoardReworkComplainceEnable;
  UINT8   ItpxdpMuxSupport;
  UINT8   ItpxdpMux;


  UINT8   OsDnx;

  UINT8   PepPeg0;
  // Option to slect UCMC/UCSI device
  UINT8   TcssUcmDevice;
  UINT8   PepPcieStorage;
  UINT8   TbtVtdBaseSecurity;
  UINT8   KernelDebugPatch;
  UINT8   IfwiDnx;
  UINT8   ITbtRtd3;
  UINT16  ITbtRtd3ExitDelay;
  UINT8   AuxOriOverrideSupport;
  UINT8   AuxOriOverride;
  UINT8   SerialIoSpiCsDeviceEnable[3];

  UINT8   BclkSource;
  UINT8   PowermeterDeviceEnable; // powermeter enabling
  UINT8   WwanResetWorkaround;

  UINT8   SdevXhciNumberOfDevices;
  UINT8   SdevXhciDeviceAttributes[2];
  UINT8   SdevXhciRootPortNumber[2];
  UINT16  SdevXhciVendorId[2];
  UINT16  SdevXhciProductId[2];
  UINT16  SdevXhciRevision[2];
  UINT8   SdevXhciInterfaceNumber[2];
  UINT8   SdevXhciClass[2];
  UINT8   SdevXhciSubClass[2];
  UINT8   SdevXhciProtocol[2];
  UINT16  SdevXhciAcpiPathStringOffset[2];
  UINT16  SdevXhciAcpiPathStringLength[2];
  UINT64  SdevXhciFirmwareHashDevice1[4];
  UINT64  SdevXhciFirmwareHashDevice2[4];
  UINT16  SdevXhciAcpiPathNameDevice1[49]; // 48 characters + NULL termination
  UINT16  SdevXhciAcpiPathNameDevice2[49]; // 48 characters + NULL termination
  UINT8   ControlIommu;

  UINT8   SdevFlags[5];
  UINT8   SdevXhciFlags;
  //
  // S5 Charging
  //
  UINT8   ChargingEnable;
  UINT8   ChargingLpmEnable;
  UINT8   CriticalBatteryLimit;
  UINT8   CriticalBatteryLimitFeature;
  UINT16  IaAppsRun;
  UINT8   IaAppsCap;
  UINT8   IaAppsToUse;
  UINT8   TccMode;
  UINT8   RVP1BoardWifiEnable;

} SETUP_DATA;

/**
 Making any setup structure change after code frozen
 will need to maintain backward compatibility, bump up
 structure revision and update below history table\n
  <b>Revision 1</b>:  - Initial version.
**/

#define CPU_SETUP_REVISION  1

typedef struct {
  UINT8   Revision;
  UINT8   CpuRatio;
  UINT8   CpuDefaultRatio;
  UINT8   CpuRatioOverride;
  UINT8   Peci;
  UINT8   HyperThreading;
  UINT8   ActiveCoreCount;
  UINT8   BistOnReset;
  UINT8   JtagC10PowerGateDisable;
  UINT8   EnableGv;
  UINT8   RaceToHalt;
  UINT8   EnableHwp;
  UINT8   EnableItbm;
  UINT8   EnableItbmDriver;

  UINT8   EnablePerCorePState;
  UINT8   EnableHwpAutoPerCorePstate;
  UINT8   EnableHwpAutoEppGrouping;
  UINT8   EnableEpbPeciOverride;
  UINT8   EnableFastMsrHwpReq;

  UINT8   BootFrequency;
  UINT8   EnableCx;
  UINT8   EnableC1e;
  UINT8   TurboMode;
  UINT32  PowerLimit1;
  UINT8   LongDurationPwrLimitOverride;
  UINT8   PowerLimit1Time;
  UINT8   PowerLimit2;
  UINT32  PowerLimit2Power;
  UINT8   PowerLimit3Override;
  UINT32  PowerLimit3;
  UINT8   PowerLimit3Time;
  UINT8   PowerLimit3DutyCycle;
  UINT8   PowerLimit3Lock;
  UINT8   PowerLimit4Override;
  UINT32  PowerLimit4;
  UINT8   PowerLimit4Lock;
  UINT8   TurboPowerLimitLock;
  UINT8   PlatformPowerLimit1Enable;
  UINT32  PlatformPowerLimit1Power;
  UINT8   PlatformPowerLimit1Time;
  UINT8   PlatformPowerLimit2Enable;
  UINT32  PlatformPowerLimit2Power;
  UINT8   EnergyEfficientPState;
  UINT8   CStatePreWake;
  UINT8   CStateAutoDemotion;
  UINT8   CStateUnDemotion;
  UINT8   PkgCStateDemotion;
  UINT8   PkgCStateUnDemotion;
  UINT8   EnableThermalMonitor;
  UINT8   PmgCstCfgCtrlLock;
  UINT8   ConfigTdpLevel;
  UINT8   ConfigTdpLock;
  UINT8   ConfigTdpBios;
  UINT8   TimedMwait;
  UINT8   PmgCstCfgCtrIoMwaitRedirection;
  UINT8   InterruptRedirectMode;

  UINT8   HdcControl;
  UINT8   PkgCStateLimit;
  UINT8   CstateLatencyControl1TimeUnit;
  UINT8   CstateLatencyControl2TimeUnit;
  UINT8   CstateLatencyControl3TimeUnit;
  UINT8   CstateLatencyControl4TimeUnit;
  UINT8   CstateLatencyControl5TimeUnit;
  UINT16  CstateLatencyControl1Irtl;
  UINT16  CstateLatencyControl2Irtl;
  UINT16  CstateLatencyControl3Irtl;
  UINT16  CstateLatencyControl4Irtl;
  UINT16  CstateLatencyControl5Irtl;

  UINT32  Custom1PowerLimit1Power;
  UINT32  Custom1PowerLimit2Power;
  UINT8   Custom1PowerLimit1Time;
  UINT8   Custom1TurboActivationRatio;
  UINT32  Custom2PowerLimit1Power;
  UINT32  Custom2PowerLimit2Power;
  UINT8   Custom2PowerLimit1Time;
  UINT8   Custom2TurboActivationRatio;
  UINT32  Custom3PowerLimit1Power;
  UINT32  Custom3PowerLimit2Power;
  UINT8   Custom3PowerLimit1Time;
  UINT8   Custom3TurboActivationRatio;
  UINT8   TStatesEnable;
  UINT8   EnableProcHot;
  UINT8   DisableProcHotOut;
  UINT8   DisableVrThermalAlert;
  UINT8   ProcHotLock;
  UINT8   ProcHotResponse;
  UINT8   TCCActivationOffset;
  UINT8   NumOfCustomPStates;
  UINT8   StateRatio[MAX_CUSTOM_P_STATES];
  UINT8   StateRatioMax16[MAX_16_CUSTOM_P_STATES];
  UINT8   VT;
  UINT8   AES;
  UINT8   MachineCheck;
  UINT8   MonitorMwait;
  UINT16  DprSize;
  UINT8   HwPrefetcher;
  UINT8   AclPrefetch;
  UINT8   Txt;
  UINT8   LtDprProgramming;
  UINT8   ResetAux;
  UINT8   AcheckRequest;
  UINT8   MsegOpt;
  UINT8   MsegSize;

  UINT8   EcTurboControlMode;
  UINT8   AcBrickCapacity;
  UINT8   EcPollingPeriod;
  UINT8   EcGuardBandValue;
  UINT8   EcAlgorithmSel;

  UINT8   IsTurboRatioDefaultsInitalized;
  UINT8   FlexRatioOverrideDefault;
  UINT8   RatioLimit1Default;
  UINT8   RatioLimit2Default;
  UINT8   RatioLimit3Default;
  UINT8   RatioLimit4Default;
  UINT8   RatioLimit5Default;
  UINT8   RatioLimit6Default;
  UINT8   RatioLimit7Default;
  UINT8   RatioLimit8Default;
  UINT8   RatioLimit1;
  UINT8   RatioLimit2;
  UINT8   RatioLimit3;
  UINT8   RatioLimit4;
  UINT8   RatioLimit5;
  UINT8   RatioLimit6;
  UINT8   RatioLimit7;
  UINT8   RatioLimit8;
  UINT8   OverclockingLockDefault;
  UINT8   OverclockingLock;

  UINT8   BiosGuard;
  UINT8   BiosGuardToolsInterface;

  UINT8   DebugInterfaceEnable;
  UINT8   DebugInterfaceLockEnable;
  UINT8   DebugCpuDisabled;
  UINT8   EnableSgx;
  UINT8   EpochUpdate;
  UINT8   ShowEpoch;
  UINT32  MaxPrmrrSize;
  UINT32  PrmrrSize;
  UINT8   ApIdleManner;

  UINT8   ProcessorTraceOutputScheme;
  UINT8   ProcessorTraceMemSize;
  UINT8   ProcessorTraceEnable;

  UINT8   SkipStopPbet;
  UINT8   ThreeStrikeCounterDisable;
  UINT8   EpocFclkFreq;

  //
  // SA = 0, IA = 1, Ring = 2, GT = 3, FIVR = 4
  //
  UINT8   PsysSlope;
  UINT8   PsysOffset;
  UINT16  PsysPmax;
  UINT8   VrConfigEnable[5];
  UINT16  AcLoadline[5];
  UINT16  DcLoadline[5];
  UINT16  Psi1Threshold[5];
  UINT16  Psi2Threshold[5];
  UINT16  Psi3Threshold[5];
  UINT8   Psi3Enable[5];
  UINT8   Psi4Enable[5];
  UINT16  ImonSlope[5];
  UINT16  ImonOffset[5];
  UINT8   ImonOffsetPrefix[5];
  UINT16  IccMax[5];
  UINT16  VrVoltageLimit[5];
  UINT16  TdcCurrentLimit[5];
  UINT8   TdcEnable[5];
  UINT8   TdcTimeWindow[5];
  UINT8   TdcLock[5];

  UINT32  TccOffsetTimeWindow;
  UINT8   TccOffsetClamp;
  UINT8   TccOffsetLock;

  //
  // CPU related
  //
  UINT8   FlexOverrideEnable;
  UINT8   MaxEfficiencyRatio;
  UINT8   MaxNonTurboRatio;
  UINT8   FlexRatioOverride;
  UINT8   EnableGvDefault;
  UINT8   TurboModeDefault;
  UINT8   PowerLimit1TimeDefault;
  UINT32  PowerLimit1Default;
  UINT32  PowerLimit2Default;

  UINT8   BusSpeedEnable;
  UINT8   ProcessorBusSpeedOverride;
  UINT8   ProcessorBusSpeedOverrideDefault;

  UINT8   PciePll;
  UINT8   EnergyEfficientTurbo;

  UINT8   WDTSupportforNextOSBoot;
  UINT16  TimeforNextOSBoot;

  UINT8   EnableDigitalThermalSensor;

  //
  // OverClocking setup options
  //
  UINT8   OverclockingSupport;
  UINT8   XtuInterfaceEnable;

  UINT8   CoreMaxOcRatio;
  UINT8   CoreVoltageMode;
  UINT16  CoreVoltageOverride;
  UINT16  CoreVoltageOffset;
  UINT8   CoreVoltageOffsetPrefix;
  UINT16  CoreExtraTurboVoltage;
  UINT8   Avx2RatioOffset;
  UINT8   Avx3RatioOffset;
  UINT8   RingMaxOcRatio;
  UINT8   RingDownBin;
  UINT8   RingVoltageMode;
  UINT16  RingVoltageOverride;
  UINT16  RingVoltageOffset;
  UINT8   RingVoltageOffsetPrefix;
  UINT16  RingExtraTurboVoltage;

  //
  // OverClocking Default setup options
  //
  UINT8   CoreMaxOcRatioDefault;
  UINT8   CoreVoltageModeDefault;
  UINT16  CoreVoltageOverrideDefault;
  UINT16  CoreVoltageOffsetDefault;
  UINT8   CoreVoltageOffsetPrefixDefault;
  UINT16  CoreExtraTurboVoltageDefault;
  UINT8   Avx2RatioOffsetDefault;
  UINT8   Avx3RatioOffsetDefault;
  UINT8   RingMaxOcRatioDefault;
  UINT8   VoltageOptimization;

  UINT8   RingVoltageModeDefault;
  UINT16  RingVoltageOverrideDefault;
  UINT16  RingVoltageOffsetDefault;
  UINT8   RingVoltageOffsetPrefixDefault;
  UINT16  RingExtraTurboVoltageDefault;
  UINT8   EnableAllThermalFunctions;
  UINT8   CorePllVoltageOffset;
  UINT8   GtPllVoltageOffset;
  UINT8   RingPllVoltageOffset;
  UINT8   SaPllVoltageOffset;
  UINT8   McPllVoltageOffset;
  UINT8   TjMaxOffset;

  //
  // RFI Setup Options
  //
  UINT16 FivrRfiFrequency;
  UINT8  FivrSpreadSpectrum;

  //
  // Acoustic Noise Mitigation
  //
  UINT8   AcousticNoiseMitigation;
  UINT8   FastPkgCRampDisableIa;
  UINT8   FastPkgCRampDisableGt;
  UINT8   FastPkgCRampDisableSa;
  UINT8   FastPkgCRampDisableFivr;
  UINT8   SlowSlewRateForIa;
  UINT8   SlowSlewRateForGt;
  UINT8   SlowSlewRateForSa;
  UINT8   SlowSlewRateForFivr;
  UINT8   EnableMinVoltageOverride;
  UINT16  MinVoltageRuntime;
  UINT16  MinVoltageC8;

  UINT8   HwpInterruptControl;
  UINT16  IccMaxDefault[5];
  UINT8   BclkAdaptiveVoltageEnable;

  UINT8   FivrFaults;
  UINT8   FivrEfficiency;

  UINT8   PpinSupport;
  UINT8   PpinEnableMode;

  UINT8   MinRingRatioLimit;
  UINT8   MinRingRatioLimitDefault;
  UINT8   MaxRingRatioLimit;
  UINT8   MaxRingRatioLimitDefault;

  UINT8   SafModeDisableBiosGuard;
  // Bclk RFI Frequency for each SAGV point in 10KHz units.
  UINT32  BclkRfi10KhzFreq[4];
  UINT8   CpuBclkSpread;

  UINT8   AcSplitLock;

} CPU_SETUP;

typedef struct {
  UINT16  CpuFamilyModel;
  UINT16  CpuExtendedFamilyModel;
  UINT8   CpuStepping;
  UINT8   EdramSupported;

  //
  // Vr Topology
  //
  UINT8  CoreVrLocked;
  UINT8  SaVrLocked;
  UINT8  GtVrLocked;
  UINT8  FivrVrLocked;
} CPU_SETUP_VOLATILE_DATA;

typedef struct {
  UINT64  SgxEpoch0;
  UINT64  SgxEpoch1;
} CPU_SETUP_SGX_EPOCH_DATA;

typedef struct {
  UINT8                DTbtContollersNumber;
  UINT8                ITbtRootPortsNumber;
} TBT_SETUP_VOLATILE_DATA;

/**
 Making any setup structure change after code frozen
 will need to maintain backward compatibility, bump up
 structure revision and update below history table\n
  <b>Revision 1</b>:  - Initial version.
**/

#define ME_SETUP_REVISION   1

typedef struct {
  UINT8   Revision;
  //
  // Intel ME
  //
  UINT8   MeFirmwareInfo;
  UINT8   MeImageType;
  UINT8   MeFwDowngrade;
  UINT8   CommsHubEnable;

  UINT8   HeciTimeouts;
  UINT8   DidInitStat;
  UINT8   DisableCpuReplacedPolling;
  UINT8   SendDidMsg;
  UINT8   DisableMessageCheck;
  UINT8   SkipMbpHob;
  UINT8   HeciCommunication2;
  UINT8   KtDeviceEnable;
  UINT8   DisableD0I3SettingForHeci;
  UINT8   MctpBroadcastCycle;

  UINT8   ChangeEps;
  UINT8   UnconfigOnRtcAvailable;
  UINT8   MeUnconfigOnRtcClear;
  UINT8   CoreBiosDoneEnabled;
  UINT8   Heci3Enabled;
  UINT8   MeJhiSupport;

  //
  // Intel AMT
  //
  UINT8   Amt;
  UINT8   AmtbxHotKeyPressed;
  UINT8   AmtbxSelectionScreen;
  UINT8   HideUnConfigureMeConfirm;
  UINT8   MebxDebugMsg;
  UINT8   UnConfigureMe;
  UINT8   AmtCiraRequest;
  UINT8   AmtCiraTimeout;
  UINT8   UsbProvision;
  UINT8   FwProgress;

  //
  // ASF
  //
  UINT8   AsfSensorsTable;

  //
  // WatchDog
  //
  UINT8   WatchDogEnabled;
  UINT16  WatchDogTimerOs;
  UINT16  WatchDogTimerBios;

  //
  // MEBx resolution settings
  //
  UINT8   MebxNonUiTextMode;
  UINT8   MebxUiTextMode;
  UINT8   MebxGraphicsMode;

  //
  //
  // Extend ME/CSME Measurements to TPM-PCR
  //
  UINT8   ExtendMeMeasuredBoot;

  //
  // Anti-Rollback SVN
  //
  UINT8   AutoArbSvnCommit;

} ME_SETUP;

/**
 Making any setup structure change after code frozen
 will need to maintain backward compatibility, bump up
 structure revision and update below history table\n
  <b>Revision 1</b>:  - Initial version.
**/

#define SA_SETUP_REVISION   1

typedef struct {
  UINT8   Revision;
  UINT8   BdatEnable;

  //
  // Memory related
  //
  UINT8   XmpProfileEnable;
  UINT16  MemoryVoltage;
  UINT16  MemoryVoltageDefault;
  UINT8   DllBwEn0;
  UINT8   DllBwEn1;
  UINT8   DllBwEn2;
  UINT8   DllBwEn3;
  //
  // Memory timing override (these options are used for Custom/User Profile)
  //
  UINT8   DdrRefClkDefault;
  UINT8   DdrRefClk;
  UINT8   DdrRatioDefault;
  UINT8   DdrRatio;
  UINT8   DdrOddRatioMode;
  UINT8   tCL;
  UINT8   tCWL;
  UINT16  tFAW;
  UINT16  tRAS;
  UINT8   tRCDtRP;
  UINT16  tREFI;
  UINT16  tRFC;
  UINT8   tRRD;
  UINT8   tRTP;
  UINT8   tWR;
  UINT8   tWTR;
  UINT8   NModeSupport;
  //
  // Default values to restore memory timings to in case of Platform instability
  //
  UINT8   tCLDefault;
  UINT8   tCWLDefault;
  UINT16  tFAWDefault;
  UINT16  tRASDefault;
  UINT8   tRCDtRPDefault;
  UINT16  tREFIDefault;
  UINT16  tRFCDefault;
  UINT8   tRRDDefault;
  UINT8   tRTPDefault;
  UINT8   tWRDefault;
  UINT8   tWTRDefault;
  UINT8   NModeDefault;

  UINT16  GtDid;                    // not a SETUP item, used by BIOS to pass GT SKU DID to SETUP items
  UINT8   IgdBootType;
  UINT8   DisplayPipeB;
  UINT8   LcdPanelType;

  UINT8   LcdPanelScaling;

  UINT8   EnableRenderStandby;
  UINT8   IgdLcdBlc;
  UINT8   AlsEnable;
  UINT8   ActiveLFP;
  UINT8   LfpColorDepth;
  UINT8   GTTSize;
  UINT8   ApertureSize;
  UINT8   GtPsmiSupport;
  UINT8   GtPsmiRegionSize;
  UINT8   DismSize;
  UINT8   PanelPowerEnable;
  UINT8   PmSupport;
  UINT8   PeiGraphicsPeimInit;
  UINT8   PavpEnable;
  UINT8   VbtSelect;
  UINT8   VbiosBrightness;
  UINT8   CdynmaxClampEnable;
  UINT8   CdClock;
  UINT8   GtFreqMax;
  UINT8   DisableTurboGt;
  UINT8   SkipCdClockInit;

  UINT8   DfdRestoreEnable;
  UINT8   RC1pFreqEnable;
  //
  // ICC Related
  //
  UINT8   BclkOverride;
  UINT32  BclkFrequency;
  UINT8   EpgEnable;
  UINT16  Idd3n;
  UINT16  Idd3p;

  //
  // DVMT5.0 Graphic memory setting
  //
  UINT8   IgdDvmt50PreAlloc;
  UINT8   IgdDvmt50TotalAlloc;
  //
  // SA Device Control
  //
  UINT8   EnableVtd;
  UINT8   EnableAbove4GBMmio;
  UINT8   GnaEnable;
  UINT8   SaIpuEnable;
  UINT8   SaIpuImrConfiguration;
  UINT8   SaIpuFusaConfigEnable;
  UINT8   EdramTestMode;
  UINT8   IedMemEnable;
  UINT8   CpuTraceHubMode;
  UINT8   CpuTraceHubMemReg0Size;
  UINT8   CpuTraceHubMemReg1Size;
  //
  // VT-d
  //
  UINT8   X2ApicOptOut;
  UINT8   DmaControlGuarantee;
  UINT8   VtdIgdEnable;
  UINT8   VtdIpuEnable;
  UINT8   VtdIopEnable;
  UINT8   VtdItbtEnable;

  //
  // DMI
  //
  UINT8   DmiMaxLinkSpeed;

  UINT8   DmiDeEmphasis;
  UINT8   DmiGen3EqPh2Enable;
  UINT8   DmiGen3EqPh3Method;
  UINT8   DmiGen3ProgramStaticEq;
  UINT8   DmiGen3RootPortPreset[8];
  UINT8   DmiGen3EndPointPreset[8];
  UINT8   DmiGen3EndPointHint[8];
  UINT8   DmiGen3RxCtlePeaking[4];
  // Stop Grant
  UINT8   AutoNsg;
  UINT8   NumStopGrant;
  // Primary Display Select
  UINT8   PrimaryDisplay;
  UINT8   PcieCardSelect;
  UINT16  DelayAfterPwrEn;
  UINT16  DelayAfterHoldReset;
  UINT8   InternalGraphics;
  // Graphics Turbo IMON Current
  UINT8   GfxTurboIMON;

  //Enable PTM in TCSS
  UINT8   PtmEnabled[MAX_ITBT_PCIE_PORT];
  //
  // PCIe LTR Configuration
  //
  UINT8   SaPcieItbtLtrEnable[MAX_ITBT_PCIE_PORT];
  UINT8   SaPcieItbtSnoopLatencyOverrideMode[MAX_ITBT_PCIE_PORT];
  UINT8   SaPcieItbtSnoopLatencyOverrideMultiplier[MAX_ITBT_PCIE_PORT];
  UINT16  SaPcieItbtSnoopLatencyOverrideValue[MAX_ITBT_PCIE_PORT];
  UINT8   SaPcieItbtNonSnoopLatencyOverrideMode[MAX_ITBT_PCIE_PORT];
  UINT8   SaPcieItbtNonSnoopLatencyOverrideMultiplier[MAX_ITBT_PCIE_PORT];
  UINT16  SaPcieItbtNonSnoopLatencyOverrideValue[MAX_ITBT_PCIE_PORT];
  UINT8   SaPcieItbtForceLtrOverride[MAX_ITBT_PCIE_PORT];
  UINT8   SaPcieItbtLtrConfigLock[MAX_ITBT_PCIE_PORT];
  //
  // Cpu Telemetry Aggregator (CrashLog)
  //
  UINT8   CpuCrashLogDevice;

  //
  // VMD:Settings
  //
  UINT8   VmdSupported;
  UINT8   VmdEnable;
  UINT8   VmdPortA;
  UINT8   VmdPortB;
  UINT8   VmdPortC;
  UINT8   VmdPortD;
  UINT8   VmdCfgBarSz;
  UINT8   VmdCfgBarAttr;
  UINT8   VmdMemBarSz1;
  UINT8   VmdMemBar1Attr;
  UINT8   VmdMemBarSz2;
  UINT8   VmdMemBar2Attr;
  UINT8   VmdPortAPresent;
  UINT8   VmdPortBPresent;
  UINT8   VmdPortCPresent;
  UINT8   VmdPortDPresent;
  UINT8   RaidR0;
  UINT8   RaidR1;
  UINT8   RaidR10;
  UINT8   RaidR5;
  UINT8   Rrt;
  UINT8   RrtOnlyEsata;
  UINT8   OptaneMemory;

  //
  // 2LM
  //
  UINT8   TwoLmSupported;
  UINT8   MemBootMode;
  UINT8   MfvcWrrArb;
  UINT8   VcId_7_0[16];
  UINT8   SetHwParameters;
  UINT16  Ltr_L1D2_ThVal;
  UINT8   Ltr_L1D2_ThScale;
  UINT8   SysPwrState;
  UINT8   MediaDeathNotification;
  UINT8   HealthLogNotification;
  UINT8   TempBelowThrottleNotification;
  UINT8   TempAboveThrottleNotification;
  UINT8   MissingCommitBitNotification;
  UINT8   NVMeHoldDisableBit;

  //
  // MRC settings
  //
  UINT8   HobBufferSize;
  UINT8   EccSupport;
  UINT8   MaxTolud;
  UINT16  DdrFreqLimit;
  UINT8   SpdProfileSelected;
  UINT8   MrcTimeMeasure;
  UINT8   MrcFastBoot;
  UINT8   RmtPerTask;
  UINT8   TrainTrace;
  UINT8   ChHashEnable;
  UINT16  ChHashMask;
  UINT8   ChHashInterleaveBit;
  UINT8   ExtendedBankHashing;
  UINT8   PerBankRefresh;
  UINT8   ForceSingleRank;
  UINT8   ForceSingleSubchannel;
  UINT8   LpddrMemWriteLatencySet;
  UINT8   RetrainOnFastFail;
  UINT8   Ddr4OneDpc;
  UINT8   SafeMode;
  UINT8   BdatTestType;
  UINT8   RMTLoopCount;
  UINT8   MemTestOnWarmBoot;
  UINT8   MrcTrainOnWarm;
  UINT8   LowSupplyEnData;
  UINT8   LowSupplyEnCcc;
  UINT8   DisPgCloseIdleTimeout;

  UINT8   PowerDownMode;
  UINT8   SaGv;
  UINT16  FreqSaGvLow;
  UINT16  FreqSaGvMid;
  UINT8   DdrSpeedControl;
  UINT8   SaGvLowGear2;
  UINT8   SaGvMidGear2;
  UINT8   SaGvHighGear2;
  UINT8   MarginLimitCheck;
  UINT16  MarginLimitL2;

  //
  // MRC Training Algorithms
  //
  UINT8   ECT;
  UINT8   SOT;
  UINT8   ERDMPRTC2D;
  UINT8   RDMPRT;
  UINT8   RCVET;
  UINT8   JWRL;
  UINT8   EWRTC2D;
  UINT8   ERDTC2D;
  UINT8   WRTC1D;
  UINT8   WRVC1D;
  UINT8   RDTC1D;
  UINT8   DIMMODTT;
  UINT8   DIMMRONT;
  UINT8   WRDSEQT;
  UINT8   WRSRT;
  UINT8   RDODTT;
  UINT8   RDEQT;
  UINT8   RDAPT;
  UINT8   WRTC2D;
  UINT8   RDTC2D;
  UINT8   WRVC2D;
  UINT8   RDVC2D;
  UINT8   CMDVC;
  UINT8   LCT;
  UINT8   RTL;
  UINT8   TAT;
  UINT8   RMT;
  UINT8   MEMTST;
  UINT8   ALIASCHK;
  UINT8   RCVENC1D;
  UINT8   RMC;
  UINT8   WRDSUDT;
  UINT8   CMDSR;
  UINT8   CMDDSEQ;
  UINT8   CMDNORM;
  UINT8   EWRDSEQ;
  UINT8   RDVC1D;
  UINT8   TXTCO;
  UINT8   CLKTCO;
  UINT8   DIMMODTCA;
  UINT8   TXTCODQS;
  UINT8   DCC;
  UINT8   DQDFE;
  UINT8   SOTC;
  UINT8   Lp4DqsOscEn;

  //
  // Power and Thermal Throttling Options
  //
  UINT8   EnableExtts;
  UINT8   EnableCltm;
  UINT8   EnableOltm;
  UINT8   EnablePwrDn;
  UINT8   EnablePwrDnLpddr;
  UINT8   Refresh2X;
  UINT8   DdrThermalSensor;
  UINT8   LockPTMregs;
  UINT8   UserPowerWeightsEn;

  UINT8   EnergyScaleFact;
  UINT8   RaplPwrFlCh1;
  UINT8   RaplPwrFlCh0;

  UINT8   RaplLim2Lock;
  UINT8   RaplLim2WindX;
  UINT8   RaplLim2WindY;
  UINT8   RaplLim2Ena;
  UINT16  RaplLim2Pwr;
  UINT8   RaplLim1WindX;
  UINT8   RaplLim1WindY;
  UINT8   RaplLim1Ena;
  UINT16  RaplLim1Pwr;

  UINT8   WarmThresholdCh0Dimm0;
  UINT8   WarmThresholdCh0Dimm1;
  UINT8   WarmThresholdCh1Dimm0;
  UINT8   WarmThresholdCh1Dimm1;
  UINT8   HotThresholdCh0Dimm0;
  UINT8   HotThresholdCh0Dimm1;
  UINT8   HotThresholdCh1Dimm0;
  UINT8   HotThresholdCh1Dimm1;
  UINT8   WarmBudgetCh0Dimm0;
  UINT8   WarmBudgetCh0Dimm1;
  UINT8   WarmBudgetCh1Dimm0;
  UINT8   WarmBudgetCh1Dimm1;
  UINT8   HotBudgetCh0Dimm0;
  UINT8   HotBudgetCh0Dimm1;
  UINT8   HotBudgetCh1Dimm0;
  UINT8   HotBudgetCh1Dimm1;

  UINT8   IdleEnergyCh0Dimm1;
  UINT8   IdleEnergyCh0Dimm0;
  UINT8   PdEnergyCh0Dimm1;
  UINT8   PdEnergyCh0Dimm0;
  UINT8   ActEnergyCh0Dimm1;
  UINT8   ActEnergyCh0Dimm0;
  UINT8   RdEnergyCh0Dimm1;
  UINT8   RdEnergyCh0Dimm0;
  UINT8   WrEnergyCh0Dimm1;
  UINT8   WrEnergyCh0Dimm0;

  UINT8   IdleEnergyCh1Dimm1;
  UINT8   IdleEnergyCh1Dimm0;
  UINT8   PdEnergyCh1Dimm1;
  UINT8   PdEnergyCh1Dimm0;
  UINT8   ActEnergyCh1Dimm1;
  UINT8   ActEnergyCh1Dimm0;
  UINT8   RdEnergyCh1Dimm1;
  UINT8   RdEnergyCh1Dimm0;
  UINT8   WrEnergyCh1Dimm1;
  UINT8   WrEnergyCh1Dimm0;

  UINT8   SrefCfgEna;
  UINT16  SrefCfgIdleTmr;
  UINT8   ThrtCkeMinDefeat;
  UINT8   ThrtCkeMinTmr;
  UINT8   ThrtCkeMinDefeatLpddr;
  UINT8   ThrtCkeMinTmrLpddr;

  UINT8   MemoryThermalManagement;
  UINT8   PeciInjectedTemp;
  UINT8   ExttsViaTsOnBoard;
  UINT8   ExttsViaTsOnDimm;
  UINT8   VirtualTempSensor;
  UINT8   ScramblerSupport;
  UINT8   ForceColdReset;
  UINT8   DisableDimmMc0Ch0;
  UINT8   DisableDimmMc0Ch1;
  UINT8   RemapEnable;
  UINT8   MrcSafeConfig;
  UINT8   RhPrevention;
  UINT8   RhSolution;
  UINT8   RhActProbability;
  UINT8   MaxRttWr;
  UINT8   ExitOnFailure;

#ifdef UP_SERVER_FLAG
  UINT8   UserThresholdEnable;
  UINT8   UserBudgetEnable;
  UINT8   TsodTcritMax;
  UINT8   TsodEventMode;
  UINT8   TsodEventPolarity;
  UINT8   TsodCriticalEventOnly;
  UINT8   TsodEventOutputControl;
  UINT8   TsodAlarmwindowLockBit;
  UINT8   TsodCriticaltripLockBit;
  UINT8   TsodShutdownMode;
  UINT8   TsodThigMax;
  UINT8   TsodManualEnable;
#endif
  UINT8   SkipExtGfxScan;
  //
  // CRID
  //
  UINT8   CridEnable;

  UINT8   SlateIndicatorRT;
  UINT8   SlateIndicatorSx;
  UINT8   DockIndicatorRT;
  UINT8   DockIndicatorSx;
  UINT8   IuerButtonEnable;
  UINT8   IuerConvertibleEnable;
  UINT8   IuerDockEnable;

  //
  // Uncore Related
  //
  UINT16  UncoreVoltageOffset;
  UINT8   UncoreVoltageOffsetPrefix;

  UINT16  UncoreVoltageOffsetDefault;
  UINT8   UncoreVoltageOffsetPrefixDefault;

  //
  // GT related
  //
  UINT8   GtMaxOcRatio;                 ///< Maximum GT turbo ratio override
  UINT8   GtVoltageMode;                ///< Specifies whether GT voltage is operating in Adaptive or Override mode - 0: Adaptive, 1: Override
  UINT16  GtVoltageOffset;              ///< The voltage offset applied to GT. Valid range from -1000mv to 1000mv
  UINT8   GtVoltageOffsetPrefix;
  UINT16  GtVoltageOverride;            ///< The GT voltage override which is applied to the entire range of GT frequencies
  UINT16  GtExtraTurboVoltage;          ///< The adaptive voltage applied during turbo frequencies. Valid range from 0 to 2000mV
  UINT8   GtusMaxOcRatio;                ///< Maximum GT turbo ratio override
  UINT8   GtusVoltageMode;               ///< Specifies whether GT unslice voltage is operating in Adaptive or Override mode - 0: Adaptive, 1: Override
  UINT16  GtusVoltageOffset;             ///< The voltage offset applied to GT unslice. Valid range from -1000mv to 1000mv
  UINT8   GtusVoltageOffsetPrefix;
  UINT16  GtusVoltageOverride;           ///< The GT unslice voltage override which is applied to the entire range of GT frequencies
  UINT16  GtusExtraTurboVoltage;         ///< The adaptive voltage applied during turbo frequencies. Valid range from 0 to 2000mV

  UINT8   GtMaxOcRatioDefault;          ///< Maximum GT turbo ratio override
  UINT8   GtVoltageModeDefault;         ///< Specifies whether GT voltage is operating in Adaptive or Override mode - 0: Adaptive, 1: Override
  UINT16  GtVoltageOffsetDefault;       ///< The voltage offset applied to GT. Valid range from -1000mv to 1000mv
  UINT8   GtVoltageOffsetPrefixDefault;
  UINT16  GtVoltageOverrideDefault;     ///< The GT voltage override which is applied to the entire range of GT frequencies
  UINT16  GtExtraTurboVoltageDefault;   ///< The adaptive voltage applied during turbo frequencies. Valid range from 0 to 2000mV
  UINT8   GtusMaxOcRatioDefault;         ///< Maximum GT turbo ratio override
  UINT8   GtusVoltageModeDefault;        ///< Specifies whether GT unslice voltage is operating in Adaptive or Override mode - 0: Adaptive, 1: Override
  UINT16  GtusVoltageOffsetDefault;      ///< The voltage offset applied to GT unslice. Valid range from -1000mv to 1000mv
  UINT8   GtusVoltageOffsetPrefixDefault;
  UINT16  GtusVoltageOverrideDefault;    ///< The GT unslice voltage override which is applied to the entire range of GT frequencies
  UINT16  GtusExtraTurboVoltageDefault;  ///< The adaptive voltage applied during turbo frequencies. Valid range from 0 to 2000mV

  UINT8   RealtimeMemoryTiming;         ///< Realtime memory timing will allow system to perform realtime memory timing changes.
  UINT8   BclkChangeWarmReset;
  UINT8   BclkChangeContinues;

  UINT8   Ibecc;
  UINT8   IbeccParity;
  UINT8   IbeccOperationMode;
  UINT8   IbeccProtectedRegionEnable[8];
  UINT16  IbeccProtectedRegionBase[8];
  UINT16  IbeccProtectedRegionMask[8];
  UINT8   PramSize;
  UINT8   RMTBIT;
  //
  // FUSA
  //
  UINT8   DisplayFusaConfigEnable;
  UINT8   GraphicFusaConfigEnable;
  UINT8   OpioFusaConfigEnable;
} SA_SETUP;

/**
 Making any setup structure change after code frozen
 will need to maintain backward compatibility, bump up
 structure revision and update below history table\n
  <b>Revision 1</b>:  - Initial version.
  <b>Revision 2</b>:  - add DciModphyPg
**/

#define PCH_SETUP_REVISION  2

typedef struct {
  UINT8   Revision;
  UINT8   ExternalDma;
  UINT16  RootPortDid;              // not a SETUP item, used by BIOS to pass Root Port DID to SETUP items

  UINT8   DeepSxMode;
  UINT8   LanWakeFromDeepSx;
  UINT8   DisableDsxAcPresentPulldown;
  UINT8   PmcReadDisable;
  UINT8   OsDebugPort;
  UINT8   PchLan;
  UINT8   DciUsb3TypecUfpDbg;
  UINT8   PchEnableDbcObs;
  UINT8   PchWakeOnLan;
  UINT8   SlpLanLowDc;
  UINT8   PchWakeOnWlan;
  UINT8   PchWakeOnWlanDeepSx;
  UINT8   PchEnergyReport;
  UINT8   EnableTcoTimer;
  UINT8   PchCrid;
  UINT8   PmcLpmS0i2p0En;
  UINT8   PmcLpmS0i2p1En;
  UINT8   PmcLpmS0i2p2En;
  UINT8   PmcLpmS0i3p0En;
  UINT8   PmcLpmS0i3p1En;
  UINT8   PmcLpmS0i3p2En;
  UINT8   PmcLpmS0i3p3En;
  UINT8   PmcLpmS0i3p4En;

  UINT8   PchRtcMemoryLock;
  UINT8   PchBiosLock;
  UINT8   UnlockGpioPads;
  UINT8   PsOnEnable;

  UINT8   Hpet;
  UINT8   StateAfterG3;
  UINT8   IchPort80Route;
  UINT8   EnhancePort8xhDecoding;
  UINT8   PciePllSsc;
  UINT8   WdtEnable;
  UINT8   PchS0ixAutoDemotion;
  UINT8   PmcGrTscEnable;
  UINT8   PchLatchEventsC10Exit;
  //
  // Usb Config
  //
  UINT8   PchUsbPortDisable;
  UINT8   PchUsbHsPort[SETUP_MAX_USB2_PORTS];
  UINT8   PchUsbSsPort[SETUP_MAX_USB3_PORTS];
  UINT8   PchUsbOtgDisable;
  UINT8   PchUsbHsPortOtg[SETUP_MAX_USB2_PORTS];
  UINT8   PchUsbSsPortOtg[SETUP_MAX_USB3_PORTS];
  UINT8   PchUsbPdoProgramming;
  UINT8   EnableComplianceMode;
  UINT8   PchUsbOverCurrentEnable;
  UINT8   PchXhciOcLock;
  UINT8   PchXhciAcLock;
  UINT8   PchUsb2SusWellPgEnable;

  //
  // xDCI Config
  //
  UINT8   PchXdciSupport;

  //
  // Sata CONFIG
  //
  UINT8   PchSata;
  UINT8   SataInterfaceMode;
  UINT8   SataRstInterrupt;
  UINT8   SataPort[PCH_MAX_SATA_PORTS];
  UINT8   SataHotPlug[PCH_MAX_SATA_PORTS];
  UINT8   SataMechanicalSw[PCH_MAX_SATA_PORTS];
  UINT8   SataSpinUp[PCH_MAX_SATA_PORTS];
  UINT8   SataExternal[PCH_MAX_SATA_PORTS];
  UINT8   SataType[PCH_MAX_SATA_PORTS];
  UINT8   SataTopology[PCH_MAX_SATA_PORTS];
  UINT8   SataRaidR0;
  UINT8   SataRaidR1;
  UINT8   SataRaidR10;
  UINT8   SataRaidR5;
  UINT8   SataRaidIrrt;
  UINT8   SataRaidOub;
  UINT8   SataHddlk;
  UINT8   SataLedl;
  UINT8   SataRaidIooe;
  UINT8   SataRaidSrt;
  UINT8   SataRaidOromDelay;
  UINT8   SataRstForceForm;
  UINT8   SataLegacyOrom;
  UINT8   SataRstOptaneMemory;
  UINT8   SataRstCpuAttachedStorage;
  UINT8   RaidDeviceId;
  UINT8   SataSalp;
  UINT8   SataTestMode;
  UINT8   SataPortMultiplier;
  UINT8   PxDevSlp[PCH_MAX_SATA_PORTS];
  UINT8   SataRxPolarity[PCH_MAX_SATA_PORTS];
  UINT8   EnableDitoConfig[PCH_MAX_SATA_PORTS];
  UINT16  DitoVal[PCH_MAX_SATA_PORTS];
  UINT8   DmVal[PCH_MAX_SATA_PORTS];
  UINT8   RstPcieRemapEnabled[PCH_MAX_PCIE_ROOT_PORTS];

  //
  // PCI_EXPRESS_CONFIG, MAX 16 root ports
  //
  UINT8   PcieRootPort8xhDecode;
  UINT8   Pcie8xhDecodePortIndex;
  UINT8   PcieRootPortPeerMemoryWriteEnable;
  UINT8   PcieComplianceTestMode;
  UINT8   PchPcieClockUsageOverride[PCH_MAX_PCIE_CLOCKS];
  UINT8   PchPcieClkReqSupport[PCH_MAX_PCIE_CLOCKS];
  UINT8   PcieRootPortEn[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortAspm[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortURE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortFEE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortNFE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortCEE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortCTD[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortPIE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortSFE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortSNE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortSCE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortPMCE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortHPE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortAER[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortSpeed[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortTHS[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortL1SubStates[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortACS[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortPTM[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortDPC[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortEDPC[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortSI[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortMVCE[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieRootPortMVCESupported[PCH_MAX_PCIE_ROOT_PORTS];
  UINT16  PcieDetectTimeoutMs[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   RpFunctionSwap;

  //
  // PCIe EQ
  //
  UINT8   PcieEqOverrideDefault;
  UINT8   PcieEqMethod;
  UINT8   PcieEqMode;
  UINT8   PcieEqPh2LocalTransmitterOverrideEnable;
  UINT8   PcieEqPh1DownstreamPortTransmitterPreset;
  UINT8   PcieEqPh1UpstreamPortTransmitterPreset;
  UINT8   PcieEqPh3NumberOfPresetsOrCoefficients;
  UINT8   PcieEqPh3PreCursorList[10];
  UINT8   PcieEqPh3PostCursorList[10];
  UINT8   PcieEqPh3PresetList[11];
  UINT8   PcieEqPh2LocalTransmitterOverridePreset;

  //
  // PCIe LTR Configuration
  //
  UINT8   PchPcieLtrEnable[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PchPcieLtrConfigLock[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PchPcieSnoopLatencyOverrideMode[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PchPcieSnoopLatencyOverrideMultiplier[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PchPcieNonSnoopLatencyOverrideMode[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PchPcieNonSnoopLatencyOverrideMultiplier[PCH_MAX_PCIE_ROOT_PORTS];
  UINT16  PchPcieSnoopLatencyOverrideValue[PCH_MAX_PCIE_ROOT_PORTS];
  UINT16  PchPcieNonSnoopLatencyOverrideValue[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PchPcieForceLtrOverride[PCH_MAX_PCIE_ROOT_PORTS];

  //
  // DMI Configuration
  //
  UINT8   PchDmiAspm;

  //
  // THC Configuration
  //
  UINT8   ThcPort0Assignment;
  UINT8   ThcPort0Clock;
  UINT8   ThcPort1Assignment;
  UINT8   ThcPort1Clock;

  //
  // IEH Configuration
  //
  UINT8  IehMode;

  //
  // PCI Bridge Resources
  //
  UINT8   PcieExtraBusRsvd[PCH_MAX_PCIE_ROOT_PORTS];
  UINT16  PcieMemRsvd[PCH_MAX_PCIE_ROOT_PORTS];
  UINT8   PcieIoRsvd[PCH_MAX_PCIE_ROOT_PORTS];

  //
  // HD-Audio Configuration
  //
  UINT8   PchHdAudio;
  UINT8   PchHdAudioDsp;
  UINT8   PchHdAudioDspUaaCompliance;
  UINT8   PchHdaIDisplayCodecDisconnect;
  UINT8   PchHdAudioPme;
  UINT8   PchHdAudioLinkMode;
  UINT8   PchHdAudioHdaLinkEnable;
  UINT8   PchHdAudioHdaSdiEnable[PCH_MAX_HDA_SDI];
  UINT8   PchHdAudioDmicLinkEnable[PCH_MAX_HDA_DMIC_LINK_NUM];
  UINT8   PchHdAudioSndwLinkEnable[PCH_MAX_HDA_SNDW_LINK_NUM];
  UINT8   PchHdAudioSspLinkEnable[PCH_MAX_HDA_SSP_LINK_NUM];
  UINT8   PchHdaHdAudioLinkFreq;
  UINT8   PchHdaIDisplayLinkFreq;
  UINT8   PchHdaIDisplayLinkTmode;
  UINT8   PchHdAudioCodecSxWakeCapability;
  UINT8   PchHdaAutonomousClockStopSndw[PCH_MAX_HDA_SNDW_LINK_NUM];
  UINT8   PchHdaDataOnActiveIntervalSelectSndw[PCH_MAX_HDA_SNDW_LINK_NUM];
  UINT8   PchHdaDataOnDelaySelectSndw[PCH_MAX_HDA_SNDW_LINK_NUM];
  UINT8   PchHdAudioCodecSelect;
  UINT8   PchHdAudioI2sCodecSelect;
  UINT8   PchHdAudioNhltEndpointDmic;
  UINT8   PchHdAudioNhltEndpointBluetooth;
  UINT8   PchHdAudioNhltEndpointI2s;
  UINT8   PchHdAudioNhltExternalTable;
  UINT8   PchHdAudioFeature[HDAUDIO_FEATURES];
  UINT8   PchHdAudioPostProcessingMod[HDAUDIO_PP_MODULES];
  CHAR16  PchHdAudioPostProcessingModCustomGuid1[GUID_CHARS_NUMBER];
  CHAR16  PchHdAudioPostProcessingModCustomGuid2[GUID_CHARS_NUMBER];
  CHAR16  PchHdAudioPostProcessingModCustomGuid3[GUID_CHARS_NUMBER];

  //
  // Interrupt Configuration
  //
  UINT8   PchIoApic24119Entries;
  UINT8   Enable8254ClockGating;

  //
  // PCH Thermal Throttling
  //
  UINT8   PchCrossThrottling;
  //
  // SCS Configuration
  //
  UINT8   PchScsEmmcEnabled;
  UINT8   PchScsEmmcHs400Enabled;
  UINT8   PchScsEmmcHs400SoftwareTuning;
  UINT8   PchScsEmmcHs400DriverStrength;
  UINT8   PchScsSdCardEnabled;
  UINT8   PchScsUfsEnable[PCH_MAX_UFS_DEV_NUM];

  BOOLEAN PchPseOobIsFirstBootProvDone;

  UINT32  PchPseLogOutputChannel;
  UINT16  PchPseLogOutputOffset;
  UINT16  PchPseLogOutputSize;
  UINT8   PchPseJtagEnabled;
  UINT8   PchPseJtagPinMux;

  //
  // Programmable Service Engine (PSE) configuration
  //
  UINT8   PchPseEnable;
  UINT8   PchPseI2sEnable[PCH_MAX_PSE_I2S_CONTROLLERS];
  UINT8   PchPsePwmEnable;
  UINT8   PchPseUartEnable[PCH_MAX_PSE_UART_CONTROLLERS];
  UINT8   PchPseHsuartEnable[PCH_MAX_PSE_HSUART_PINS];
  UINT8   PchPseQepEnable[PCH_MAX_PSE_QEP_CONTROLLERS];
  UINT8   PchPseI2cEnable[PCH_MAX_PSE_I2C_CONTROLLERS];
  UINT8   PchPseSpiEnable[PCH_MAX_PSE_SPI_CONTROLLERS];
  UINT8   PchPseDmaEnable[PCH_MAX_PSE_DMA_CONTROLLERS];
  UINT8   PchPseGbeEnable[PCH_MAX_PSE_GBE_CONTROLLERS];
  UINT8   PchPseSpiCs0Enable[PCH_MAX_PSE_SPI_CONTROLLERS];
  UINT8   PchPseSpiCs1Enable[PCH_MAX_PSE_SPI_CONTROLLERS];
  UINT8   PchPseAdcEnable;
  UINT8   PchPseCanEnable[PCH_MAX_PSE_CAN_CONTROLLERS];
  UINT8   PchPseTgpioEnable[PCH_MAX_PSE_TGPIO_CONTROLLERS];
  UINT8   PchPseTgpioAllocatePins[PCH_MAX_PSE_TGPIO_CONTROLLERS];
  UINT8   PchPseTgpioPinEnable[PCH_MAX_PSE_TGPIO_CONTROLLER_PINS];
  UINT8   PchPsePwmPinEnable[PCH_MAX_PSE_PWM_CONTROLLER_PINS];

  UINT8   PchPseI2sSbInterruptEnable[PCH_MAX_PSE_I2S_CONTROLLERS];
  UINT8   PchPsePwmSbInterruptEnable;
  UINT8   PchPseUartSbInterruptEnable[PCH_MAX_PSE_UART_CONTROLLERS];
  UINT8   PchPseHsuartSbInterruptEnable[PCH_MAX_PSE_HSUART_PINS];
  UINT8   PchPseQepSbInterruptEnable[PCH_MAX_PSE_QEP_CONTROLLERS];
  UINT8   PchPseI2cSbInterruptEnable[PCH_MAX_PSE_I2C_CONTROLLERS];
  UINT8   PchPseSpiSbInterruptEnable[PCH_MAX_PSE_SPI_CONTROLLERS];
  UINT8   PchPseDmaSbInterruptEnable[PCH_MAX_PSE_DMA_CONTROLLERS];
  UINT8   PchPseAdcSbInterruptEnable;
  UINT8   PchPseLh2PseSbInterruptEnable;
  UINT8   PchPseCanSbInterruptEnable[PCH_MAX_PSE_CAN_CONTROLLERS];
  UINT8   PchPseDmaTestEnable;
  UINT8   PchPseI2s0PinAssignment;

  //
  // Pch Serial Io configuration
  //
  UINT8   PchSpiCsPolarity[6]; // [PCH_MAX_SERIALIO_SPI_CONTROLLERS * PCH_MAX_SERIALIO_SPI_CHIP_SELECTS]
  UINT8   PchSerialIoSpi[PCH_MAX_SERIALIO_SPI_CONTROLLERS];
  UINT8   PchSpiCsPolaritySelect[PCH_MAX_SERIALIO_SPI_CHIP_SELECTS];
  UINT8   PchSerialIoUart[PCH_MAX_SERIALIO_UART_CONTROLLERS];
  UINT8   PchUartDmaEnable[PCH_MAX_SERIALIO_UART_CONTROLLERS];
  UINT8   PchUartHwFlowCtrl[PCH_MAX_SERIALIO_UART_CONTROLLERS];
  UINT8   PchUartPowerGating[PCH_MAX_SERIALIO_UART_CONTROLLERS];
  UINT8   PchSerialIoI2c[PCH_MAX_SERIALIO_I2C_CONTROLLERS];
  UINT8   PchSerialIoDeviceI2C4Support;
  UINT8   PchGpio;
  UINT8   PchGpioIrqRoute;
  UINT16  PchGpioDebounce;
  UINT8   PchGpioTestDevices;
  UINT8   PchAdditionalSerialIoDevices;

  //
  // TraceHub Setup Options
  //
  UINT8   PchTraceHubMode;
  UINT8   PchTraceHubMemReg0Size;
  UINT8   PchTraceHubMemReg1Size;
  //
  // Thermal Throttling Level options
  //
  UINT8   PchTtLevelSuggestSet;
  UINT16  PchThrmT0Level;
  UINT16  PchThrmT1Level;
  UINT16  PchThrmT2Level;
  UINT8   PchThrmTtEnable;
  UINT8   PchThrmTtState13Enable;
  UINT8   PchThrmTtLock;

  //
  // DMI Thermal Throttling
  //
  UINT8   PchDmiTsSuggestSet;
  UINT8   PchTs0Width;
  UINT8   PchTs1Width;
  UINT8   PchTs2Width;
  UINT8   PchTs3Width;
  UINT8   PchDmiTsawEn;
  //
  // SATA Thermal Throttling
  //
  UINT8   PchSataTsSuggestSet;
  UINT8   PchP0T1M;
  UINT8   PchP0T2M;
  UINT8   PchP0T3M;
  UINT8   PchP0TDisp;
  UINT8   PchP0Tinact;
  UINT8   PchP0TDispFinit;
  UINT8   PchP1T1M;
  UINT8   PchP1T2M;
  UINT8   PchP1T3M;
  UINT8   PchP1TDisp;
  UINT8   PchP1Tinact;
  UINT8   PchP1TDispFinit;
  //
  // CNVi
  //
  UINT8   CnviMode;
  UINT8   CnviBtCore;
  UINT8   CnviBtAudioOffload;
  //
  // eSPI Setup Options
  //
  UINT8   PchEspiLgmrEnable;
  UINT8   PchEspiHostC10ReportEnable;

  //
  // SMBUS
  //
  UINT8   SmbusSpdWriteDisable;
  //
  // P2SB
  //
  UINT8   PchSidebandLock;
  //
  // Flash Protection configuration
  //
  UINT8   FprrEnable;

  //
  // Debug Panel
  //
  UINT8   DciEn;
  UINT8   DciDbcMode;
  UINT8   DciModphyPg;
  UINT8   PmcDbgMsgEn;

  //Hammock Harbor
  UINT8   EnableTimedGpio0;
  UINT8   EnableTimedGpio1;

  //
  // FIVR Configuration;
  //
  UINT8   ExternalV1p05StateEnable[FIVR_RAIL_S0IX_SX_STATES_MAX];
  UINT8   ExternalVnnStateEnable[FIVR_RAIL_S0IX_SX_STATES_MAX];
  UINT8   ExternalVnnSxStateEnable[FIVR_RAIL_S0IX_SX_STATES_MAX];
  UINT8   ExternalV1p05SupportedVoltageStates[FIVR_RAIL_EXT_VOLTAGE_STATES_MAX];
  UINT8   ExternalVnnSupportedVoltageStates[FIVR_RAIL_EXT_VOLTAGE_STATES_MAX];

  UINT8   ExternalV1p05IccMax;
  UINT16  ExternalV1p05Voltage;
  UINT8   ExternalVnnIccMax;
  UINT16  ExternalVnnVoltage;
  UINT8   ExternalVnnSxIccMax;
  UINT16  ExternalVnnSxVoltage;

  UINT8   PchRetToLowCurModeVolTranTime;
  UINT8   PchRetToHighCurModeVolTranTime;
  UINT8   PchLowToHighCurModeVolTranTime;
  UINT16  PchOffToHighCurModeVolTranTime;
  UINT8   PchFivrDynPm;

  //
  // OS IDLE MODE
  //
  UINT8   PchPmcOsIdleModeEnable;

  UINT8   V1p05PhyExtFetControlEnable;
  UINT8   V1p05IsExtFetControlEnable;

  UINT8   PchLegacyIoLowLatency;

  //
  // PSF
  //
  UINT8   PsfTccEnable;

  //
  // TSN
  //
  UINT8   PchTsnEnable;
  UINT8   PchTsnGbeMultiVcEnable;
  UINT8   PchTsnGbeLinkSpeed;
  UINT8   PchTsnGbeSgmiiEnable;
  UINT8   PseTsnGbeMultiVcEnable[PCH_MAX_PSE_GBE_CONTROLLERS];
  UINT8   PseTsnGbeLinkSpeed[PCH_MAX_PSE_GBE_CONTROLLERS];
  UINT8   PseTsnGbeSgmiiEnable[PCH_MAX_PSE_GBE_CONTROLLERS];

  // FUSA
  //
  UINT8   PsfFusaConfigEnable;

  //
  // FIA
  //
  UINT8   FiaLaneReversalEnable[PCH_MAX_FIA_ORM_CONNECTOR];

  //
  // Master Clock Gating & Power Gating
  //
  UINT8   PchMasterClockGating;
  UINT8   PchMasterPowerGating;
  UINT8   TestPcieClockGating;

  UINT8   PchUsb3LinkSpeed;


  //
  // Sci Gpio Pin Mux
  //
  UINT8   SciPinMuxEnable;
} PCH_SETUP;


/**
  Making any setup structure change after code frozen
  will need to maintain backward compatibility, bump up
  structure revision and update below history table.\n
  <b>Revision 1</b>:  - Initial version.
**/

#define SI_SETUP_REVISION  1

typedef struct {
  UINT8   Revision;
  UINT8   PlatformDebugConsent;
  //
  // PCIe IMR
  //
  UINT8   PcieImrEnable;
  UINT16  PcieImrSize;
  UINT8   PcieImrRpLocation;
  UINT8   PcieImrRpSelection;
} SI_SETUP;

#pragma pack()

#ifndef PLATFORM_SETUP_VARIABLE_NAME
#define PLATFORM_SETUP_VARIABLE_NAME             L"Setup"
#endif

#define SETUP_GUID \
 { 0xEC87D643, 0xEBA4, 0x4BB5, { 0xA1, 0xE5, 0x3F, 0x3E, 0x36, 0xB2, 0x0D, 0xA9 } }

#define SA_SETUP_GUID \
 { 0x72c5e28c, 0x7783, 0x43a1, { 0x87, 0x67, 0xfa, 0xd7, 0x3f, 0xcc, 0xaf, 0xa4 } }

#define ME_SETUP_GUID \
 { 0x5432122d, 0xd034, 0x49d2, { 0xa6, 0xde, 0x65, 0xa8, 0x29, 0xeb, 0x4c, 0x74 } }

#define CPU_SETUP_GUID \
 { 0xb08f97ff, 0xe6e8, 0x4193, { 0xa9, 0x97, 0x5e, 0x9e, 0x9b, 0xa,  0xdb, 0x32 } }

#define PCH_SETUP_GUID \
 { 0x4570b7f1, 0xade8, 0x4943, { 0x8d, 0xc3, 0x40, 0x64, 0x72, 0x84, 0x23, 0x84 } }

#define SI_SETUP_GUID \
 { 0xAAF8E719, 0x48F8, 0x4099, { 0xA6, 0xF7, 0x64, 0x5F, 0xBD, 0x69, 0x4C, 0x3D } }

#define DEBUG_CONFIG_GUID \
 { 0xDE0A5E74, 0x4E3E, 0x3D96, { 0xA4, 0x40, 0x2C, 0x96, 0xEC, 0xBD, 0x3C, 0x97 } }

#endif

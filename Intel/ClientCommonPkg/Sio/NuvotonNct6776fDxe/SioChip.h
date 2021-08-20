/** @file
  SIO chip specific implementation.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#ifndef _SIO_H_
#define _SIO_H_


#include "Register.h"

#define COM1_ADDRESS                    0x03F8
#define COM1_IRQ_BIT                    BIT4
#define HWMON_BASE_ADDRESS              0x0290  // HWMON uses +5 and +6.
#define HWMON_INDEX_ADDRESS             (HWMON_BASE_ADDRESS + 5)
#define HWMON_DATA_ADDRESS              (HWMON_BASE_ADDRESS + 6)

//#define NCT6776F_HWMON_PROTOCOL_GUID \
//  { 0x1c20e600, 0x2814, 0x4e22, { 0x9e, 0x96, 0x14, 0xe0, 0x46, 0x72, 0xf4, 0xd4 }};

typedef struct {
  UINT8 Register;
  UINT8 Value;
} HWMON_REGISTER_PAIR;

EFI_STATUS
EFIAPI
Nct6776fHwMonStart (
  VOID
  );

EFI_STATUS
EFIAPI
Nct6776fHwMonSetBankValues (
  IN  HWMON_REGISTER_PAIR  *RegisterPair,
  IN  UINT8                 Bank,
  IN  UINT8                 RegisterCount
  );

EFI_STATUS
EFIAPI
Nct6776fHwMonReadRegister (
  IN  UINT8     Register,
  OUT UINT8    *Value
  );

typedef
EFI_STATUS
(EFIAPI  *NCT6776F_HWMON_START) (
  VOID
  );

typedef
EFI_STATUS
(EFIAPI  *NCT6776F_HWMON_SET_BANK_VALUES) (
  IN  HWMON_REGISTER_PAIR  *RegisterPair,
  IN  UINT8                 Bank,
  IN  UINT8                 RegisterCount
  );

typedef
EFI_STATUS
(EFIAPI  *NCT6776F_HWMON_READ_REGISTER) (
  IN  UINT8     Register,
  OUT UINT8    *Value
  );

typedef struct _NCT6776F_HWMON_PROTOCOL {
  NCT6776F_HWMON_START           StartMonitor;
  NCT6776F_HWMON_SET_BANK_VALUES SetMonitorBankValues;
  NCT6776F_HWMON_READ_REGISTER   ReadMonitorRegister;
} NCT6776F_HWMON_PROTOCOL;

typedef
UINT8
(EFIAPI *LOCAL_IO_WRITE8) (
  IN      UINTN                     Port,
  IN      UINT8                     Value
  );

#define RESOURCE_IO    BIT0
#define RESOURCE_IRQ   BIT1
#define RESOURCE_DMA   BIT2
#define RESOURCE_MEM   BIT3

#pragma pack(1)

typedef struct {
  EFI_ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR  Io;
  EFI_ACPI_IRQ_NOFLAG_DESCRIPTOR              Irq;
  EFI_ACPI_END_TAG_DESCRIPTOR                 End;
} ACPI_SIO_RESOURCES_IO_IRQ;

typedef struct {
  EFI_ACPI_FIXED_LOCATION_IO_PORT_DESCRIPTOR  Io;
  EFI_ACPI_END_TAG_DESCRIPTOR                 End;
} ACPI_SIO_RESOURCES_IO;

#pragma pack()

typedef struct {
  UINT32                      HID;
  UINT32                      UID;
} EFI_SIO_ACPI_DEVICE_ID;

typedef struct {
  EFI_SIO_ACPI_DEVICE_ID      Device;
  UINT8                       DeviceId;
  UINT8                       ResourceMask;
  ACPI_RESOURCE_HEADER_PTR    Resources;
  ACPI_RESOURCE_HEADER_PTR    PossibleResources;
} DEVICE_INFO;


/**
  Initialize the SIO chip and save for S3.
**/
VOID
SioInitAndSaveS3 (
  VOID
  );


/**
  Return the supported devices.

  @param[out] Devices         Pointer to pointer of EFI_SIO_ACPI_DEVICE_ID.
                              Caller is responsible to free the buffer.
  @param[out] Count           Pointer to UINTN holding the device count.
**/
VOID
DeviceGetList (
  OUT EFI_SIO_ACPI_DEVICE_ID **Devices,
  OUT UINTN                  *Count
  );


/**
  Program the SIO chip to enable the specified device using the default resource.

  @param[in] Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
**/
VOID
DeviceEnable (
  IN EFI_SIO_ACPI_DEVICE_ID   *Device
  );


/**
  Get the possible ACPI resources for specified device.

  @param[in]  Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[out] Resources       Pointer to ACPI_RESOURCE_HEADER_PTR.

  @retval     EFI_SUCCESS     The resources are returned successfully.
**/
EFI_STATUS
DevicePossibleResources (
  IN  EFI_SIO_ACPI_DEVICE_ID   *Device,
  OUT ACPI_RESOURCE_HEADER_PTR *Resources
  );


/**
  Set the ACPI resources for specified device.

  The SIO chip is programmed to use the new resources and the
  resources setting are saved. The function assumes the resources
  are valid.

  @param[in] Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[in] Resources       ACPI_RESOURCE_HEADER_PTR.

  @retval    EFI_SUCCESS     The resources are set successfully.
**/
EFI_STATUS
DeviceSetResources (
  IN EFI_SIO_ACPI_DEVICE_ID   *Device,
  IN ACPI_RESOURCE_HEADER_PTR Resources
  );


/**
  Get the ACPI resources for specified device.

  @param[in]  Device          Pointer to EFI_SIO_ACPI_DEVICE_ID.
  @param[out] Resources       Pointer to ACPI_RESOURCE_HEADER_PTR.

  @retval     EFI_SUCCESS     The resources are returned successfully.
**/
EFI_STATUS
DeviceGetResources (
  IN  EFI_SIO_ACPI_DEVICE_ID   *Device,
  OUT ACPI_RESOURCE_HEADER_PTR *Resources
  );


/**
  Program the SIO chip to enter the configure mode.
**/
VOID
EnterConfigMode (
  VOID
  );


/**
  Program the SIO chip to exit the configure mode.
**/
VOID
ExitConfigMode (
  VOID
  );


/**
  Perform a 8-bit I/O write to SIO register.

  @param[in]  Index  The register index.
  @param[in]  Data   The value to write to register.
**/
VOID
WriteRegister (
  IN  UINT8            Index,
  IN  UINT8            Data
  );


/**
  Perform a 8-bit I/O read from SIO register.

  @param[in]  Index  The register index.

  @retval     Value  The value written to the register.
**/
UINT8
ReadRegister (
  IN  UINT8            Index
  );

#endif // _SIO_H_

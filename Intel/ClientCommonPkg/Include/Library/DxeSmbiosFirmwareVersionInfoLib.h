/** @file
  Header file for DxeSmbiosFirmwareVersionInfoLib implementation

Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.<BR>
This program and the accompanying materials are licensed and made available under 
the terms and conditions of the BSD License that accompanies this distribution.  
The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php.                                          

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#ifndef _DXE_SMBIOS_FIRMWARE_VERSION_INFO_LIB_H_
#define _DXE_SMBIOS_FIRMWARE_VERSION_INFO_LIB_H_

/**
  Installs the SMBIOS Firmware Version Info (FVI) OEM type SMBIOS table based on the FIRMWARE_VERSION_INFO_HOB

  @retval EFI_UNSUPPORTED      - Could not locate SMBIOS protocol
  @retval EFI_OUT_OF_RESOURCES - Failed to allocate memory for SMBIOS FVI OEM type.
  @retval EFI_SUCCESS          - Successfully installed SMBIOS FVI OEM type
**/
EFI_STATUS
EFIAPI
InstallSmbiosFviOemType (
  VOID
  );

/**
  Installs SMBIOS Type 14 for grouping Firmware Version Info (FVI) OEM tables

  @retval others               - Failed to create an ReadyToBootEvent for install SMBIOS FVI Type 14
  @retval EFI_SUCCESS          - Successfully create an ReadyToBootEvent for install SMBIOS FVI Type 14
**/
EFI_STATUS
EFIAPI
InstallSmbiosFviType14 (
  VOID
  );

#endif // _DXE_SMBIOS_FIRMWARE_VERSION_INFO_LIB_H_

/**@file

 This file describes the contents of the ACPI PSDS Table.
 @copyright
  INTEL CONFIDENTIAL
  Copyright 2019 - 2020 Intel Corporation.

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


#ifndef _ACPI_PSDS_UPDATE_H_
#define _ACPI_PSDS_UPDATE_H_

#define EFI_ACPI_PSD_SIGNATURE            SIGNATURE_32('P', 'S', 'D', 'S')  // 'PSDS'
#define PSDS_EFI_ACPI_OEM_ID              "INTEL "  // OEMID 6 bytes long
#define PSDS_EFI_ACPI_OEM_TABLE_ID        SIGNATURE_64('E','D','K','2',' ',' ',' ',' ') // OEM table id 8 bytes long
#define PSDS_EFI_ACPI_OEM_REVISION        0x00000005
#define PSDS_EFI_ACPI_CREATOR_ID          SIGNATURE_32('I','N','T','L')
#define PSDS_EFI_ACPI_CREATOR_REVISION    0x0100000D
#define EFI_ACPI_PSD_TABLE_REVISION       0x1
#define EFI_ACPI_PSD_FW_VENDOR_SIZE       16
#define EFI_ACPI_PSD_FW_VENDOR            "INTEL           "   // 16 bytes long


#pragma pack(1)


//
//FW Version information
//
typedef struct {
  UINT32 CodeMinor; //Major number
  UINT32 CodeMajor; //Minor number
  UINT32 CodeBuildNo; //Build number
  UINT32 CodeHotFix; //Hot fix
} SEC_VERSION_INFO;

//
//PSD Version information
//
typedef struct {
  UINT16 PsdVerMinor; //Version minor number.
  UINT16 PsdVerMajor; //Version major number.
} PSD_VERSION_INFO;

//
// PSDT Table which will be populated to OS,
//
typedef struct {
  EFI_ACPI_DESCRIPTION_HEADER      Header; //ACPI header
  PSD_VERSION_INFO                 PsdVersion; //PSD Version
  UINT32                           CsmeSecCapabilities; //in APL it is called TXE.
  UINT16                           SgxCapabilities; //Sgx Capabilities
  SEC_VERSION_INFO                 FwVer; //security Firmware version information
  UINT8                            FwVendor[EFI_ACPI_PSD_FW_VENDOR_SIZE]; //vendor info
  UINT8                            EomState; //End of manufacturing.
  UINT8                            SecureBoot; //secure boot status.
  UINT8                            MeasuredBoot; //measured boot status.
  UINT8                            HwrotType; //HW root of trust.
} ACPI_PSD_TABLE;

#pragma pack()

#endif //_ACPI_PSDS_UPDATE_H_


/** @file
  APIs for Intel Trusted Device Setup Main Protocol.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#ifndef _TRUSTED_DEVICE_SETUP_MAIN_PROTOCOL_H_
#define _TRUSTED_DEVICE_SETUP_MAIN_PROTOCOL_H_

//
// Extern the GUID for protocol users.
//
extern EFI_GUID                         gTrustedDeviceSetupMainProtocolGuid;

//
// Forward reference for ANSI C compatibility
//
typedef struct _TRUSTED_DEVICE_SETUP_MAIN_PROTOCOL          TRUSTED_DEVICE_SETUP_MAIN_PROTOCOL;

/**
  The Intel Trusted Device Setup Main protocol function.

  The function does the necessary work for the Trusted Device Setup feature.
  This function shall be called from the PlatformBootManagerBeforeConsole () right before ExitPmAuth ().
  Ensure no ConIn variables are set after this runs.

  @param      ExtensionFvBase   Starting Address of the Firmware Volume accommodate the Extension.
  @param      ExtensionFvSize   Size of the Firmware Volume
  @param      TDS Enabled Info, BIT14 - Enabled, BIT15 - Boot_Lock, BIT0 - Chassis Intrusion Status.
  @retval     EFI_SUCCESS       It is a Trusted Device Setup boot and all tasks have been successfully completed.
  @retval     EFI_UNSUPPORTED   It is not a Trusted Device Setup boot
  @retval     EFI_ABORTED       Trusted Device Setup failed
**/
typedef
EFI_STATUS
(EFIAPI *TRUSTED_DEVICE_SETUP_ENTRY) (
  IN UINT32 ExtensionFvBase,
  IN UINT32 ExtensionFvSize,
  IN UINT16 TrustedDeviceSetupParam
);

/**
  Update SMBIOS table 131 with Intel Trusted Device Setup BIOS capabilities

  Function sets whether BIOS supports the enhanced measured boot feature,
  the Trusted Device Setup boot and setup lock feature, and chassis intrusion detection.

  @param SMBIOS_STRUCTURE Structure of SMBIOS record to be udpated wtih Trusted Device Setup capablities.
**/
typedef
VOID
(EFIAPI *SMBIOS_TRUSTED_DEVICE_SETUP_CAPABILITIES) (
  IN OUT VOID           *RecordData
);

typedef struct _TRUSTED_DEVICE_SETUP_PROTOCOL {
  /**
    This member specifies the revision of this structure. This field is used to
    indicate backwards compatible changes to the protocol.
  **/
  UINT8                                             Revision;
  TRUSTED_DEVICE_SETUP_ENTRY                        TrustedDeviceSetupEntry;
  SMBIOS_TRUSTED_DEVICE_SETUP_CAPABILITIES          SmbiosTrustedDeviceSetupCapabilities;
} TRUSTED_DEVICE_SETUP_PROTOCOL;

/**
  Intel Trusted Device Setup Protocol revision number

  Revision 1:   Initial version
**/
#define  TRUSTED_DEVICE_SETUP_PROTOCOL_REVISION                 1

#endif

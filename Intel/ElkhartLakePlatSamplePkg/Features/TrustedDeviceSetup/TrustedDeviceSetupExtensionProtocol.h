/** @file
  APIs for Intel Trusted Device Setup Extension Protocol.

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
#ifndef _TRUSTED_DEVICE_SETUP_EXTENSION_PROTOCOL_H_
#define _TRUSTED_DEVICE_SETUP_EXTENSION_PROTOCOL_H_

//
// Extern the GUID for protocol users.
//
extern EFI_GUID                         gTrustedDeviceSetupExtensionProtocolGuid;

//
// Forward reference for ANSI C compatibility
//
typedef struct _TRUSTED_DEVICE_SETUP_EXTENSION_PROTOCOL          TRUSTED_DEVICE_SETUP_EXTENSION_PROTOCOL;

  /**
  Chassis Intrusion Enabled Function
  1 - Chassis Intrusion Enabled and Supported
  0 - Chassis Intrusion Not Enabled or Not Supported
  **/
typedef
BOOLEAN
(EFIAPI *CHASSIS_INTRUSION_ENABLED) (
  VOID
);

/**
  Chassis Intrusion Detected Function
    1 - Chassis Intrusion Detected
    0 - Chassis Intrusion Not Detected
**/
typedef
BOOLEAN
(EFIAPI *CHASSIS_INTRUSION_DETECTED) (
  VOID
);

/**
  Add Keyboard Function

  @retval EFI_SUCCESS Keyboard functionality has successfully been added.
**/
typedef
EFI_STATUS
(EFIAPI *ADD_KEYBOARD) (
  VOID
);

/**
  Remove Keyboard Function

  @retval EFI_SUCCESS Keyboard functionality has successfully been removed.
**/
typedef
EFI_STATUS
(EFIAPI *REMOVE_KEYBOARD) (
  VOID
);

typedef struct _TRUSTED_DEVICE_SETUP_EXTENSION_PROTOCOL {
  /**
    This member specifies the revision of this structure. This field is used to
    indicate backwards compatible changes to the protocol.
  **/
  UINT8                                 Revision;
  CHASSIS_INTRUSION_ENABLED             ChassisIntrusionEnabled;
  CHASSIS_INTRUSION_DETECTED            ChassisIntrusionDetected;
  ADD_KEYBOARD                          AddKeyboard;
  REMOVE_KEYBOARD                       RemoveKeyboard;
} TRUSTED_DEVICE_SETUP_EXTENSION_PROTOCOL;

/**
  Intel Trusted Device Setup Protocol revision number

  Revision 1:   Initial version
**/
#define  TRUSTED_DEVICE_SETUP_EXTENSION_PROTOCOL_REVISION                 2

#endif

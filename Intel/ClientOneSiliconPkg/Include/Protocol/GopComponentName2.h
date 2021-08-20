/** @file
  Protocol to retrieve the GOP driver version

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2016 Intel Corporation.

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
#ifndef _GOP_COMPONENT_NAME2_H_
#define _GOP_COMPONENT_NAME2_H_


typedef struct _GOP_COMPONENT_NAME2_PROTOCOL  GOP_COMPONENT_NAME2_PROTOCOL;

///
/// GOP Component protocol for retrieving driver name
///
typedef
EFI_STATUS
(EFIAPI *GOP_COMPONENT_NAME2_GET_DRIVER_NAME) (
  IN  GOP_COMPONENT_NAME2_PROTOCOL * This,
  IN  CHAR8                           *Language,
  OUT CHAR16                          **DriverName
  );

///
/// GOP Component protocol for retrieving controller name
///
typedef
EFI_STATUS
(EFIAPI *GOP_COMPONENT_NAME2_GET_CONTROLLER_NAME) (
  IN  GOP_COMPONENT_NAME2_PROTOCOL          * This,
  IN  EFI_HANDLE                               ControllerHandle,
  IN  EFI_HANDLE                               ChildHandle OPTIONAL,
  IN  CHAR8                                    *Language,
  OUT CHAR16                                   **ControllerName
  );

///
/// GOP Component protocol for retrieving driver version
///
typedef
EFI_STATUS
(EFIAPI *GOP_COMPONENT_NAME2_GET_DRIVER_VERSION) (
  IN  GOP_COMPONENT_NAME2_PROTOCOL          * This,
  IN  CHAR8                                    *Language,
  OUT CHAR16                                   **DriverVersion
  );

/**
  GOP Component protocol\n
  This protocol will be installed by GOP driver and can be used to retrieve GOP information.
**/
struct _GOP_COMPONENT_NAME2_PROTOCOL {
  GOP_COMPONENT_NAME2_GET_DRIVER_NAME      GetDriverName;          ///< Protocol function to get driver name
  GOP_COMPONENT_NAME2_GET_DRIVER_VERSION   GetDriverVersion;       ///< Protocol function to get driver version
  GOP_COMPONENT_NAME2_GET_CONTROLLER_NAME  GetControllerName;      ///< Protocol function to get controller name
  CHAR8                                    *SupportedLanguages;    ///< Number of Supported languages.
};

extern EFI_GUID gGopComponentName2ProtocolGuid;

#endif

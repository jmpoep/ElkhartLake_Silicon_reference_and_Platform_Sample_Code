/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2009 - 2016 Intel Corporation.

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
#ifndef __EFI_EC_ACCESS_H___
#define __EFI_EC_ACCESS_H___

//typedef struct gEfiEcAccessProtocolGuid _gEfiEcAccessProtocolGuid;
//
// EC Access specification constant and types
//


//
// EC Access specification Data Structures
//


typedef
EFI_STATUS
(EFIAPI *EC_QUERY_COMMAND) (
  UINT8   *Qdata
);

typedef
EFI_STATUS
(EFIAPI *EC_WRITE_CMD) (
  UINT8    cmd
);

typedef
EFI_STATUS
(EFIAPI *EC_WRITE_DATA) (
  UINT8    data
);

typedef
EFI_STATUS
(EFIAPI *EC_READ_DATA) (
  UINT8   *data
);

typedef
EFI_STATUS
(EFIAPI *EC_READ_MEM) (
  UINT8  Index,
  UINT8  *Data
);

typedef
EFI_STATUS
(EFIAPI *EC_WRITE_MEM) (
  UINT8  Index,
  UINT8  Data
);

typedef
EFI_STATUS
(EFIAPI *EC_ACPI_ENABLE) (
  VOID
  );


typedef
EFI_STATUS
(EFIAPI *EC_ACPI_DISABLE) (
  VOID
  );

typedef
EFI_STATUS
(EFIAPI *EC_SMI_NOTIFY_ENABLE) (
  VOID
  );

typedef
EFI_STATUS
(EFIAPI *EC_SMI_NOTIFY_DISABLE) (
  VOID
  );


typedef
EFI_STATUS  (EFIAPI *EC_SHUTDOWN_SYSTEM)(
  VOID
  );

typedef
EFI_STATUS  (EFIAPI *EC_GET_MOTHER_BOARD_ID)(
UINT8    *FabID
);

typedef
EFI_STATUS  (EFIAPI *EC_GET_EC_VERSION)(
UINT8    *Revision
);

typedef
EFI_STATUS  (EFIAPI *EC_ENABLE_LAN)(
  VOID
  );

typedef
EFI_STATUS  (EFIAPI *EC_DISABLE_LAN)(
  VOID
  );

typedef
EFI_STATUS  (EFIAPI *EC_DEEPSX_CONFIG)(
UINT8    ECData
);

typedef
EFI_STATUS  (EFIAPI *EC_TURBOCTRL_TESTMODE)(
UINT8    Enable,
UINT8    ACBrickCap,
UINT8    ECPollPeriod,
UINT8    ECGuardBandValue,
UINT8    ECAlgorithmSel
);

typedef
EFI_STATUS (EFIAPI *EC_GET_SWITCH_STATUS)(
  UINT8    *Data
);

typedef
EFI_STATUS  (EFIAPI *EC_FAIL_SAFE_FAN_CTRL)(
UINT8    CpuTemp,
UINT8    CpuFanSpeed
);
typedef struct _EFI_EC_ACCESS_PROTOCOL {
  EFI_HANDLE                Handle;
  EC_QUERY_COMMAND          QuerryCmd;
  EC_WRITE_CMD              WriteCmd;
  EC_WRITE_DATA             WriteData;
  EC_READ_DATA          ReadData;
  EC_READ_MEM          ReadMem;
  EC_WRITE_MEM          WriteMem;
  EC_ACPI_ENABLE        AcpiEnable;
  EC_ACPI_DISABLE        AcpiDisable;
  EC_SMI_NOTIFY_ENABLE      SMINotifyEnable;
  EC_SMI_NOTIFY_DISABLE     SMINotifyDisable;
  EC_SHUTDOWN_SYSTEM         ShutDownSystem;
  EC_GET_MOTHER_BOARD_ID    GetMotherBoardID;
  EC_GET_EC_VERSION        GetECVersion;
  EC_ENABLE_LAN          EnableLan;
  EC_DISABLE_LAN        DisableLan;
  EC_DEEPSX_CONFIG        DeepSxConfig;
  EC_TURBOCTRL_TESTMODE      TurboCtrlMode;
  EC_GET_SWITCH_STATUS      GetSwitchStatus;
  EC_FAIL_SAFE_FAN_CTRL     FailSafeFanCtrl;
} EFI_EC_ACCESS_PROTOCOL;

#endif






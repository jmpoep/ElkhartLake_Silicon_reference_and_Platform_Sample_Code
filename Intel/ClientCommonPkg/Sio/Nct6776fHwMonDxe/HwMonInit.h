/**
  This file header file contains a private Hardware Monitor structure
  definition and the prototype to the Hardware Monitor initialization
  procedure.

@copyright
  Copyright (c) 2013-2015, Intel Corporation. All rights reserved.
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.
  This file contains a 'Sample Driver' and is licensed as such
  under the terms of your license agreement with Intel or your
  vendor. This file may be modified by the user, subject to
  the additional terms of the license agreement.
**/

#ifndef _NCT6776F_HWMONINIT_H_
#define _NCT6776F_HWMONINIT_H_

//typedef unsigned char UINT8;

// HwMon default values.
#define HWMON_FAN_CONTROL_THERMAL_CR    0x10
#define HWMON_FAN_CONTROL_SMART_FAN     0x40

typedef struct {
  UINT8                       Port;
  UINT8                       Value;
} SIO_REGISTER_SETTING;

typedef struct {
  UINT8                       Bank;
  UINT8                       Register;
  UINT8                       Mask;
  UINT8                       Value;
} HWMON_REGISTER_INFO;

typedef struct {
  UINT8 Register;
  UINT8 Value;
} HWMON_REGISTER_PAIR;

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

VOID
HwMonInit (
  IN  NCT6776F_HWMON_PROTOCOL *HwMonProtocol
  );

#endif  // _NCT6776F_HWMONINIT_H_

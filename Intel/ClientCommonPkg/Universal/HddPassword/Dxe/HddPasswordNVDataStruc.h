//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
HddPassword NVData structure used by the driver.

Copyright (c) 2010 - 2013, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _HDD_PASSWORD_NVDATASTRUC_H_
#define _HDD_PASSWORD_NVDATASTRUC_H_

#include <Guid/HiiPlatformSetupFormset.h>

#define HDD_PASSWORD_CONFIG_GUID \
  { \
    0xd5fd1546, 0x22c5, 0x4c2e, { 0x96, 0x9f, 0x27, 0x3c, 0x0, 0x77, 0x10, 0x80 } \
  }

#define FORMID_HDD_MAIN_FORM          1
#define FORMID_HDD_DEVICE_FORM        2

#define HDD_DEVICE_ENTRY_LABEL        0x1234
#define HDD_DEVICE_LABEL_END          0xffff

#define KEY_HDD_DEVICE_ENTRY_BASE     0x1000

#define KEY_HDD_USER_PASSWORD         0x101
#define KEY_HDD_MASTER_PASSWORD       0x102

#pragma pack(1)

typedef struct _HDD_PASSWORD_CONFIG {
  UINT16      Supported;
  UINT16      Enabled;
  UINT16      Locked;
  UINT16      Frozen;
  UINT16      UserPasswordStatus;
  UINT16      MasterPasswordStatus;
  UINT16      IdeUserPassword[32];
  UINT16      IdeMasterPassword[32];
} HDD_PASSWORD_CONFIG;

#pragma pack()

#endif

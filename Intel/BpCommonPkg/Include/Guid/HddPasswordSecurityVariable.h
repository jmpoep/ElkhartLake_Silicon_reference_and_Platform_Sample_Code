//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  Defines Name GUIDs to represent a hardisk device variable guid for ATA Security Feature.

Copyright (c) 2010, Intel Corporation. All rights reserved.<BR>
This software and associated documentation (if any) is furnished
under a license and may only be used or copied in accordance
with the terms of the license. Except as permitted by such
license, no part of this software or documentation may be
reproduced, stored in a retrieval system, or transmitted in any
form or by any means without the express written consent of
Intel Corporation.

**/

#ifndef _HDD_PASSWORD_SECURITY_VARIABLE_H_
#define _HDD_PASSWORD_SECURITY_VARIABLE_H_

///
/// The Global ID used to identify a harddisk device variable guid for ATA Security Feature.
///
#define EFI_HDD_PASSWORD_SECURITY_VARIABLE_GUID \
  { \
    0x5e22f4e2, 0x35ea, 0x421b, { 0x8f, 0xd1, 0xd4, 0xae, 0x85, 0x67, 0xa4, 0x51 } \
  };

#define PASSWORD_SALT_SIZE 32
typedef struct _EFI_HDD_DEVICE_LIST {
  UINT32       Bus;
  UINT32       Device;
  UINT32       Function;
  UINT16       Port;
  UINT16       PortMultiplierPort;
  UINT8        Password[32];
  UINT8        PasswordSalt[PASSWORD_SALT_SIZE];
} EFI_HDD_DEVICE_LIST;

extern EFI_GUID gEfiHddPasswordSecurityVariableGuid;

#endif

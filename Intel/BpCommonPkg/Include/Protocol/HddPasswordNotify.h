//
// This file contains a 'Sample Driver' and is licensed as such
// under the terms of your license agreement with Intel or your
// vendor.  This file may be modified by the user, subject to
// the additional terms of the license agreement
//
/** @file
  This file contains Protocol definitions for CsmLoader.

  Copyright (c) 2012 - 2013, Intel Corporation. All rights reserved.<BR>
  This software and associated documentation (if any) is furnished
  under a license and may only be used or copied in accordance
  with the terms of the license. Except as permitted by such
  license, no part of this software or documentation may be
  reproduced, stored in a retrieval system, or transmitted in any
  form or by any means without the express written consent of
  Intel Corporation.

**/


#ifndef _HDD_PASSWORD_NOTIFIY_H_
#define _HDD_PASSWORD_NOTIFIY_H_

typedef struct {
  UINTN       Function;
  EFI_STATUS  ReturnStatus;
  UINT8       Data[1];
} SMM_COMMUNICATE_HEADER;

#define SMM_FUNCTION_SET_HDD_PASSWORD        1
#define SMM_FUNCTION_UNLOCK_HDD_PASSWORD     2

extern EFI_GUID gEfiHddPasswordNotifyProtocolGuid;

#endif

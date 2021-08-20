/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#include "SimulatedSecureErase.h"

CHAR16 mNoOsMsg[]             = L"Operating system not found...";
CHAR16 mEraseMsg[]            = L"Erasing SSD";
CHAR16 mAfterEraseMsgFormat[] = L"Disk erase completed. System shutdown in %d seconds";

EFI_STATUS
SimulateSecureErase (
  VOID
  )
{
  UINTN    Index = 0;

  DEBUG ((DEBUG_INFO, "SecureErase ::SimulateSecureErase\n"));
  for (Index = 0; Index < 5; Index++) {
    ProgressBarDialog (mEraseMsg);
  }

  return EFI_SUCCESS;
}


VOID
SimulateSecureEraseDone (
  VOID
  )
{
  UINTN    Index = 0;
  CHAR16   AfterEraseMsg[(sizeof(mAfterEraseMsgFormat)/sizeof(CHAR16))+5];

  DEBUG ((DEBUG_INFO, "SecureErase ::SimulateSecureEraseDone\n"));
  for (Index = 10; Index !=0 ; Index--) {
    UnicodeSPrint (AfterEraseMsg, sizeof(AfterEraseMsg), mAfterEraseMsgFormat, Index);
    ClearScreen ();
    OutputString (AfterEraseMsg, 10, 10, EFI_BACKGROUND_BLACK | EFI_WHITE);
    gBS->Stall (1000000L);
  }

  FillScreen (EFI_BACKGROUND_BLACK | EFI_WHITE);
  gBS->Stall (5000000L);
  OutputString (mNoOsMsg, 1, 1, EFI_BACKGROUND_BLACK | EFI_WHITE);

  return;
}

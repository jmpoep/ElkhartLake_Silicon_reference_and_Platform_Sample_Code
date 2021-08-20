/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2016 Intel Corporation.

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


#include <SetupPrivate.h>
#include <SioSetup.h>

VOID
SetSioStrings_WPCN381U (
  SPIO_DEV       *Dev,
  EFI_HII_HANDLE HiiHandle
  )
{

  if ((!Dev->NvData.DevEnable) || (!Dev->VlData.DevImplemented)) {
    return ;

  }

  switch (Dev->DeviceInfo->Type) {
    case dsFDC:
      InitString (HiiHandle,STRING_TOKEN (STR_WPCN381U_FLOPPY_CONFIG_VALUE),
                  L"IO=%Xh; IRQ=%d; DMA=%d;",Dev->VlData.DevBase1,Dev->VlData.DevIrq1,Dev->VlData.DevDma1);
    break;
  case dsUART:
    if (Dev->DeviceInfo->UID == 3) {
      InitString (
        HiiHandle,
        STRING_TOKEN (STR_WPCN381U_SERIAL0_CONFIG_VALUE),
        L"IO=%Xh; IRQ=%d;",
        Dev->VlData.DevBase1,
        Dev->VlData.DevIrq1
        );
    }else if(Dev->DeviceInfo->UID == 4){
       InitString (HiiHandle, STRING_TOKEN (STR_WPCN381U_SERIAL1_CONFIG_VALUE),
       L"IO=%Xh; IRQ=%d;",Dev->VlData.DevBase1,Dev->VlData.DevIrq1);
    }
    break;

  case dsLPT:
    if (Dev->VlData.DevDma1) {
      if (Dev->VlData.DevIrq1) {
        InitString (
          HiiHandle,
          STRING_TOKEN (STR_WPCN381U_PARALLEL_CONFIG_VALUE),
          L"IO=%Xh; IRQ=%d; DMA=%d;",
          Dev->VlData.DevBase1,
          Dev->VlData.DevIrq1,
          Dev->VlData.DevDma1
          );
      } else {
        InitString (
          HiiHandle,
          STRING_TOKEN (STR_PARALLEL_CONFIG_VALUE),
          L"IO=%Xh; DMA=%d;",
          Dev->VlData.DevBase1,
          Dev->VlData.DevDma1
          );

      }

    } else {
      if (Dev->VlData.DevIrq1) {
        InitString (
          HiiHandle,
          STRING_TOKEN (STR_WPCN381U_PARALLEL_CONFIG_VALUE),
          L"IO=%Xh; IRQ=%d;",
          Dev->VlData.DevBase1,
          Dev->VlData.DevIrq1
          );
      } else {
        InitString (
          HiiHandle,
          STRING_TOKEN (STR_PARALLEL_CONFIG_VALUE),
          L"IO=%Xh;",
          Dev->VlData.DevBase1
          );
      }
    }
    break;

  default:
    break;
  }
}

VOID
InitSioStrings_WPCN381U (
  EFI_HII_HANDLE HiiHandle,
  UINT16         Class
  )


{
  static EFI_GUID siopg = EFI_BOARD_SIO_PROTOCOL_GUID;
  SPIO_DEV        *dev;
  UINTN           i;
  UINTN           hcnt;
  EFI_HANDLE      *hbuff;
  EFI_STATUS      Status;

  Status = 0;
  if (Class == ADVANCED_FORM_SET_CLASS) {
    DEBUG ((DEBUG_INFO, "<InitSioStrings_WPCN381U>"));
    Status = gBS->LocateHandleBuffer (ByProtocol, &siopg, NULL, &hcnt, &hbuff);
    if (EFI_ERROR (Status)) {
      hcnt = 0;
    }

    for (i = 0; i < hcnt; i++) {
      Status = gBS->HandleProtocol (hbuff[i], &siopg, (VOID *) &dev);
      ASSERT_EFI_ERROR (Status);
      if (dev->DeviceInfo->HasSetup) {
        SetSioStrings_WPCN381U (dev, HiiHandle);
      }
    }
  }
}

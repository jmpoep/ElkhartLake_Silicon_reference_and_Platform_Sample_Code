/** @file
  This files contains Pch XHCI library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2017 Intel Corporation.

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

#ifndef _PCH_XHCI_LIB_H_
#define _PCH_XHCI_LIB_H_

/**
  Enumeration of each PCH XHCI LEGACY SMI type.
  PchXhciLegacySmiEn is the major switch for XHCI legacy SMI.
  And each can be ORed with others as parameter. ex..
  PchXhciLegacySmiEnSet (PchXhciLegacySmiEn | PchXhciLegacySmiOsOwnershipEn);
**/
enum PCH_XHCI_LEGACY_SMI {
  PchXhciLegacySmiEn                 = B_XHCI_MEM_USBLEGCTLSTS_USBSMIE,
  PchXhciLegacySmiHostSysErrorEn     = B_XHCI_MEM_USBLEGCTLSTS_SMIHSEE,
  PchXhciLegacySmiOsOwnershipEn      = B_XHCI_MEM_USBLEGCTLSTS_SMIOSOE,
  PchXhciLegacySmiPciCmdEn           = B_XHCI_MEM_USBLEGCTLSTS_SMIPCICE,
  PchXhciLegacySmiBarEn              = B_XHCI_MEM_USBLEGCTLSTS_SMIBARE
};

/**
  Get XHCI USB legacy SMI control setting.

  @retval     return XHCI USB legacy SMI setting.
**/
UINT32
EFIAPI
PchXhciLegacySmiEnGet (
  VOID
  );

/**
  Set XHCI USB legacy SMI control setting.

  @param[in]  UsbLegacySmiEn            Set XHCI USB legacy SMI

**/
VOID
EFIAPI
PchXhciLegacySmiEnSet (
  UINT32                                UsbLegacySmiEn
  );

#endif // _PCH_XHCI_LIB_H_

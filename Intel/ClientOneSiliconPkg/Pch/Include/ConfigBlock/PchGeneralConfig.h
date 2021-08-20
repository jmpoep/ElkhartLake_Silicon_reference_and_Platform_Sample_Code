/** @file
  PCH General policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2020 Intel Corporation.

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
#ifndef _PCH_GENERAL_CONFIG_H_
#define _PCH_GENERAL_CONFIG_H_

#define PCH_GENERAL_CONFIG_REVISION 1
#define PCH_GENERAL_PREMEM_CONFIG_REVISION 1

extern EFI_GUID gPchGeneralConfigGuid;
extern EFI_GUID gPchGeneralPreMemConfigGuid;

#pragma pack (push,1)

enum PCH_RESERVED_PAGE_ROUTE {
  PchReservedPageToLpc,                   ///< Port 80h cycles are sent to LPC.
  PchReservedPageToPcie                   ///< Port 80h cycles are sent to PCIe.
};

typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  /**
    This member describes whether or not the Compatibility Revision ID (CRID) feature
    of PCH should be enabled. <b>0: Disable</b>; 1: Enable
  **/
  UINT32    Crid            :  1;
  /**
    Set to enable low latency of legacy IO.
    Some systems require lower IO latency irrespective of power.
    This is a tradeoff between power and IO latency.
    @note: Once this is enabled, DmiAspm, Pcie DmiAspm in SystemAgent
    and ITSS Clock Gating are forced to disabled.
    <b>0: Disable</b>, 1: Enable
  **/
  UINT32    LegacyIoLowLatency  :  1;
  /**
    Master switch to program the default clock gating setting,
    or force disable clock gating for all PCH devices. <b>0: Disable</b>; 1: Default
  **/
  UINT32    PchMasterClockGating : 1;
  /**
    Master switch to program the default power gating setting,
    or force disable power gating for all PCH devices. <b>0: Disable</b>; 1: Default
  **/
  UINT32    PchMasterPowerGating : 1;
  /**
    Enable or disable Sci Gpio Pin Mux. <b>0: Disable</b>; 1: Enable
  **/
  UINT32    SciPinMuxEnable      : 1;
  UINT32    RsvdBits0            : 27;       ///< Reserved bits

} PCH_GENERAL_CONFIG;

typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  /**
    Control where the Port 80h cycles are sent, <b>0: LPC</b>; 1: PCI.
  **/
  UINT32    Port80Route     :  1;
  UINT32    IotgPllSscEn    :  1;       ///< Need to disable CPU Side SSC for A0 PO
  /**
    Master switch to program the default clock gating setting,
    or force disable clock gating for all PCH devices. <b>0: Disable</b>; 1: Default
  **/
  UINT32    PchMasterClockGating : 1;
  /**
    Master switch to program the default power gating setting,
    or force disable power gating for all PCH devices. <b>0: Disable</b>; 1: Default
  **/
  UINT32    PchMasterPowerGating : 1;
  UINT32    RsvdBits0       : 28;       ///< Reserved bits
} PCH_GENERAL_PREMEM_CONFIG;

#pragma pack (pop)

#endif // _PCH_GENERAL_CONFIG_H_

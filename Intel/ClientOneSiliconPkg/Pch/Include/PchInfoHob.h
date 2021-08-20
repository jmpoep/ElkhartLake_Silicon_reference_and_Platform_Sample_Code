/** @file
  This file contains definitions of PCH Info HOB.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#ifndef _PCH_INFO_HOB_H_
#define _PCH_INFO_HOB_H_

extern EFI_GUID gPchInfoHobGuid;

#include <PchLimits.h>

#define PCH_INFO_HOB_REVISION  3

#pragma pack (push,1)
/**
  This structure is used to provide the information of PCH controller.

  <b>Revision 1</b>:
  - Initial version.
  <b>Revision 2</b>:
  - Add CridSupport, CridOrgRid, and CridNewRid.
  <b>Revision 3</b>:
  - Add Thc0Strap.
**/
typedef struct {
  /**
    This member specifies the revision of the PCH Info HOB. This field is used
    to indicate backwards compatible changes to the protocol. Platform code that
    consumes this protocol must read the correct revision value to correctly interpret
    the content of the protocol fields.
  **/
  UINT8        Revision;
  UINT8        PcieControllerCfg[6];
  /**
    GbE over PCIe port number when GbE is enabled
    >0 - Root port number (1-based)
    0  - GbE over PCIe disabled
    This information needs to be passed through HOB as FIA registers
    are not accessible with POSTBOOT_SAI
  **/
  UINT8        GbePciePortNumber;
  /**
    THC strap disable/enable status
  **/
  UINT8       Thc0Strap;
  /**
    TSN over PCIe FIA lane enabled and lane number
   **/
  UINT8        TsnPortLaneEnabled[3];
  UINT8        TsnPortLaneNum[3];
  UINT8        Rsvd;
  UINT32       PciePortFuses;
  /**
    Bit map for PCIe Root Port Lane setting. If bit is set it means that
    corresponding Root Port has its lane enabled.
    BIT0 - RP0, BIT1 - RP1, ...
    This information needs to be passed through HOB as FIA registers
    are not accessible with POSTBOOT_SAI
  **/
  UINT32       PciePortLaneEnabled;
  /**
    Publish Hpet BDF and IoApic BDF information for VTD.
  **/
  UINT32       HpetBusNum    :  8;
  UINT32       HpetDevNum    :  5;
  UINT32       HpetFuncNum   :  3;
  UINT32       IoApicBusNum  :  8;
  UINT32       IoApicDevNum  :  5;
  UINT32       IoApicFuncNum :  3;
  /**
    Publish the CRID information.
  **/
  UINT32       CridOrgRid    :  8;
  UINT32       CridNewRid    :  8;
  UINT32       CridSupport   :  1;
  UINT32       Rsvdbits      : 15;
} PCH_INFO_HOB;

#pragma pack (pop)

#endif // _PCH_INFO_HOB_H_


/** @file
  Header file for PEI SI SSID LIB.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#ifndef _PEI_SI_SSID_LIB_H_
#define _PEI_SI_SSID_LIB_H_

#include <Ppi/SiPolicy.h>

/**
  Silicon to override default SVID and SSID

  @param[in]      PciDevNum       Pci device number
  @param[in]      PciFuncNum      Pci function number
  @param[in,out]  Svid            Svid value
  @param[in,out]  Ssid            Ssid value

  @retval         TRUE            Silicon overrides the SSID
  @retval         FALSE           Silicon doesn't override the SSID
**/
typedef
BOOLEAN
(*SI_SSID_OVERRIDE_FUNC) (
  UINT32                 PciDevNum,
  UINT32                 PciFuncNum,
  UINT16                 *Svid,
  UINT16                 *Ssid
  );

/**
  Program devices Subsystem Vendor Identifier (SVID) and Subsystem Identifier (SID).

  @param[in] SiPolicy             The SI Policy PPI instance
  @param[in] SiSsidOverrideFunc   Silicon SSID override function
**/
VOID
SiProgramSsid (
  IN  SI_POLICY_PPI             *SiPolicy,
  IN  SI_SSID_OVERRIDE_FUNC     SiSsidOverrideFunc
  );

#endif

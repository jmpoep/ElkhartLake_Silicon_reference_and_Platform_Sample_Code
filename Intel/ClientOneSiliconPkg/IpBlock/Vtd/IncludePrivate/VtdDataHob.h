/** @file
  The GUID definition for Vtd Data Hob

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
#ifndef _VTD_DATA_HOB_H_
#define _VTD_DATA_HOB_H_

#include <Register/VtdRegs.h>
#include <Base.h>

extern EFI_GUID gVtdDataHobGuid;

#pragma pack (push,1)

///
/// The data elements should be initialized by a Platform Module.
/// The data structure is for VT-d driver initialization
///
typedef struct {
  EFI_HOB_GUID_TYPE     EfiHobGuidType;                    ///< GUID Hob type structure for gVtdDataHobGuid
  BOOLEAN               VtdDisable;                        ///< 1 = Avoids programming Vtd bars, Vtd overrides and DMAR table
  UINT32                BaseAddress[VTD_ENGINE_NUMBER];    ///< This field is used to describe the base addresses for VT-d function
  BOOLEAN               X2ApicOptOut;                      ///< This field is used to enable the X2APIC_OPT_OUT bit in the DMAR table. <b>1=Enable/Set</b> and 0=Disable/Clear
  BOOLEAN               DmaControlGuarantee;               ///< This field is used to enable the DMA_CONTROL_GUARANTEE bit in the DMAR table. <b>1=Enable/Set</b> and 0=Disable/Clear
  BOOLEAN               InterruptRemappingSupport;         ///< This field is used to indicate Interrupt Remapping supported or not
} VTD_DATA_HOB;

#pragma pack (pop)
#endif

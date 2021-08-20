/** @file
  MBP Sensitive PPI

@copyright
  INTEL CONFIDENTIAL
  Copyright 2006 - 2016 Intel Corporation.

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
#ifndef _MBP_SENSITIVE_PPI_H_
#define _MBP_SENSITIVE_PPI_H_

#include <MeBiosPayloadData.h>

///
/// MBP Sensitive PPI GUID
/// This PPI provides an interface to store MBP sensitive data in PEI phase
///
extern EFI_GUID gMbpSensitivePpiGuid;

///
/// Revision
///
#define MBP_SENSITIVE_PPI_REVISION  1

///
/// MBP SENSITIVE PPI
/// Contains MBP sensitive data which should not be passed on to DXE as an HOB
///
typedef struct {
  UINT8                       Revision;       ///< Policy structure revision number
  ME_BIOS_PAYLOAD_SENSITIVE   MbpSensitiveData;
} MBP_SENSITIVE_PPI;

#endif // MBP_SENSITIVE_PPI

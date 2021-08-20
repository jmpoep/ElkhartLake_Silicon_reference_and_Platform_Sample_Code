/** @file
  ME PayLoad Data Header File.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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

#ifndef _MBP_DATA_H_
#define _MBP_DATA_H_

#include <MeBiosPayloadHob.h>
#if FixedPcdGetBool(PcdBfxEnable) == 1
#include <MeBiosPayloadData.h>
#include <Ppi/HeciPpi.h>
#else
#include <Ppi/MbpSensitivePpi.h>
#endif

/**
  Install MbpData Hob.

  @retval     EFI_SUCCESS        The function completed successfully.
  @retval     EFI_UNSUPPORTED    MBP Hob creation skipped
  @retval     Others             Failed to create MBP Hob
**/
EFI_STATUS
InstallMbpHob (
  VOID
  );

/**
  Print MbpHob data

  @param[in] MbpHob             Pointer to Mbp Hob
  @param[in] MbpSensitivePpi    Pointer to Mbp Sensitive Ppi

**/
VOID
PrintMbpData (
  IN ME_BIOS_PAYLOAD_HOB *MbpHob,
#if FixedPcdGetBool(PcdBfxEnable) == 1
  IN ME_BIOS_PAYLOAD_SENSITIVE_HOB *MbpSensitiveHob
#else
  IN MBP_SENSITIVE_PPI   *MbpSensitivePpi
#endif
  );

#endif

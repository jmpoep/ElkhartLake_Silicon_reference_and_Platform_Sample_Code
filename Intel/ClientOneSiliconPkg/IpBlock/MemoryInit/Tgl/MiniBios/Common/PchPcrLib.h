/** @file
  Header file for PchPcrLib.

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
#ifndef _PCH_PCR_LIB_H_
#define _PCH_PCR_LIB_H_

#include "PchRegsPcr.h"

/**
  Read PCR register.
  It returns PCR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  Pid      Port ID
  @param[in]  Offset   Register offset of this Port ID

  @retval UINT32       PCR register value.
**/
UINT32
PchPcrRead32 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT32                            Offset
  );

/**
  Read PCR register.
  It returns PCR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  Pid      Port ID
  @param[in]  Offset   Register offset of this Port ID

  @retval UINT16       PCR register value.
**/
UINT16
PchPcrRead16 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT32                            Offset
  );

/**
  Read PCR register.
  It returns PCR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  Pid      Port ID
  @param[in]  Offset   Register offset of this Port ID

  @retval UINT8        PCR regsiter value
**/
UINT8
PchPcrRead8 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT32                            Offset
  );

/**
  Write PCR register.
  It programs PCR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  Pid      Port ID
  @param[in]  Offset   Register offset of Port ID.
  @param[in]  Data     Input Data. Must be the same size as Size parameter.

  @retval UINT32       Value written to register
**/
UINT32
PchPcrWrite32 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT32                            Offset,
  IN  UINT32                            InData
  );

/**
  Write PCR register.
  It programs PCR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  Pid      Port ID
  @param[in]  Offset   Register offset of Port ID.
  @param[in]  Data     Input Data. Must be the same size as Size parameter.

  @retval  UINT16      Value written to register
**/
UINT16
PchPcrWrite16 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT32                            Offset,
  IN  UINT16                            InData
  );

/**
  Write PCR register.
  It programs PCR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  Pid      Port ID
  @param[in]  Offset   Register offset of Port ID.
  @param[in]  Data     Input Data. Must be the same size as Size parameter.

  @retval  UINT8       Value written to register
**/
UINT8
PchPcrWrite8 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT32                            Offset,
  IN  UINT8                             InData
  );

/**
  Write PCR register.
  It programs PCR register and size in 4bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  Pid      Port ID
  @param[in]  Offset   Register offset of Port ID.
  @param[in]  AndData  AND Data. Must be the same size as Size parameter.
  @param[in]  OrData   OR Data. Must be the same size as Size parameter.

  @retval  UINT32      Value written to register

**/
UINT32
PchPcrAndThenOr32 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT32                            Offset,
  IN  UINT32                            AndData,
  IN  UINT32                            OrData
  );

/**
  Write PCR register.
  It programs PCR register and size in 2bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  Pid      Port ID
  @param[in]  Offset   Register offset of Port ID.
  @param[in]  AndData  AND Data. Must be the same size as Size parameter.
  @param[in]  OrData   OR Data. Must be the same size as Size parameter.

  @retval UINT16       Value written to register

**/
UINT16
PchPcrAndThenOr16 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT32                            Offset,
  IN  UINT16                            AndData,
  IN  UINT16                            OrData
  );

/**
  Write PCR register.
  It programs PCR register and size in 1bytes.
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  Pid      Port ID
  @param[in]  Offset   Register offset of Port ID.
  @param[in]  AndData  AND Data. Must be the same size as Size parameter.
  @param[in]  OrData   OR Data. Must be the same size as Size parameter.

  @retval  UINT8       Value written to register

**/
UINT8
PchPcrAndThenOr8 (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT32                            Offset,
  IN  UINT8                             AndData,
  IN  UINT8                             OrData
  );

#endif // _PCH_PCR_LIB_H_

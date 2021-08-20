/** @file
  The header file for Machine check register initialization driver

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

@par Specification
**/
#ifndef _MACHINE_CHECK_INIT_H
#define _MACHINE_CHECK_INIT_H

#include <Ppi/MpServices.h>

#pragma pack(1)

typedef struct {
  UINT32 FPU : 1;
  UINT32 VME : 1;
  UINT32 DE  : 1;
  UINT32 PSE : 1;
  UINT32 TSC : 1;
  UINT32 MSR : 1;
  UINT32 PAE : 1;
  UINT32 MCE : 1;

  UINT32 CX8       : 1;
  UINT32 APIC      : 1;
  UINT32 Reserved0 : 1;
  UINT32 SEP       : 1;
  UINT32 MTRR      : 1;
  UINT32 PGE       : 1;
  UINT32 MCA       : 1;
  UINT32 CMOV      : 1;

  UINT32 PAT       : 1;
  UINT32 PSE_36    : 1;
  UINT32 PSN       : 1;
  UINT32 CLFSH     : 1;
  UINT32 Reserved1 : 1;
  UINT32 DS        : 1;
  UINT32 ACPI      : 1;
  UINT32 MMX       : 1;

  UINT32 FXSR      : 1;
  UINT32 SSE       : 1;
  UINT32 SSE2      : 1;
  UINT32 SS        : 1;
  UINT32 HTT       : 1;
  UINT32 TM        : 1;
  UINT32 Reserved2 : 1;
  UINT32 PBE       : 1;
} CPU_FEATURE;

typedef struct {
  UINT32 Count        : 8;
  UINT32 MCG_CTL_P    : 1;
  UINT32 MCG_EXT_P    : 1;
  UINT32 EXT_CORR_ERR : 1;
  UINT32 MCG_TES_P    : 1;
  UINT32 Reserved0    : 4;
  UINT32 MCG_EXT_CNT  : 8;
  UINT32 Reserved1    : 8;
} CPU_IA32_MCG_CAP_LOW_REGISTER;

#pragma pack()

/**
  Initialize all the Machine-Check registers.

  @param[in] Buffer      - Pointer to private data. Not Used.
  @param[in] MchkEnable  - Enable Mchk or not.
**/
VOID
InitializeMachineCheckRegisters (
  IN VOID    *Buffer,
  IN BOOLEAN MchkEnable
  , IN BOOLEAN IsFusaSupported
  );

#endif

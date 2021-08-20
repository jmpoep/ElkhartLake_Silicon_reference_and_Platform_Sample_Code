/** @file
  Private data structures and function prototypes.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#ifndef _CPU_INIT_DXE_H
#define _CPU_INIT_DXE_H

#include <Protocol/Metronome.h>
#include <Protocol/Cpu.h>
#include <Library/MemoryAllocationLib.h>
#include <Guid/EventGroup.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuAccess.h>
#include <Protocol/CpuInfo.h>
#include <Library/CpuPlatformLib.h>
#include <Library/HobLib.h>
#include <Library/ConfigBlockLib.h>
#include <CpuInitDataHob.h>
#include <SiConfigHob.h>

extern CPU_INIT_DATA_HOB  *mCpuInitDataHob;
extern CPU_CONFIG_DATA    *mCpuConfigData;

#define EFI_IDIV_ROUND(r, s)         ((r) / (s) + (((2 * ((r) % (s))) < (s)) ? 0 : 1))
#define MWAIT_C6                     0x20
#define MWAIT_C6_1                   0x21
#define MWAIT_C7                     0x30
#define MWAIT_C7_1                   0x31
#define MWAIT_C7_2                   0x32
#define MWAIT_C7_3                   0x33
#define MWAIT_CD                     0x40
#define MWAIT_CD_1                   0x50
#define MWAIT_CD_2                   0x60
#define DTS_IO_TRAP_ADDRESS          0x810
#define DTS_IO_TRAP_LENGTH           4
#define DTS_ACPI_DISABLE             0
#define LATENCY_C6                   78
#define LATENCY_C7                   97
#define LATENCY_C8                   260
#define LATENCY_C9                   487
#define LATENCY_C10                  1034

/**
  Initialize the state information for the CPU Architectural Protocol

  @param[in] ImageHandle - Image handle of the loaded driver
  @param[in] SystemTable - Pointer to the System Table

  @retval EFI_SUCCESS           - thread can be successfully created
  @retval EFI_OUT_OF_RESOURCES  - cannot allocate protocol data structure
  @retval EFI_DEVICE_ERROR      - cannot create the thread
**/
EFI_STATUS
EFIAPI
InitializeCpu (
  IN EFI_HANDLE       ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable
  );


/**
  Copy Global MTRR data to S3
**/
VOID
SaveBspMtrrForS3 (
  VOID
  );

/**
 * Code to update SGX Global NVS variable in EPC.ASL
 *
 */
VOID
UpdateSgxNvs (
  VOID
  );

/**
  Initialize CPU info.

  @retval EFI_SUCCESS          - Successfully prepared.
  @retval EFI_OUT_OF_RESOURCES - Not enough memory to complete the function.
**/
EFI_STATUS
InitCpuInfo (
  VOID
  );


/**
  Initialize Cpu Nvs Area Protocol

  @param[in] ImageHandle - Image handle of the loaded driver

  @retval EFI_SUCCESS           - thread can be successfully created
**/
EFI_STATUS
EFIAPI
CpuAcpiInit (
  IN EFI_HANDLE       ImageHandle
  );

/**
  Initialize BIOS Guard NVS Area Protocol

  @param[in] ImageHandle - Image handle of the loaded driver

  @retval EFI_SUCCESS           - thread can be successfully created
**/
EFI_STATUS
EFIAPI
BiosGuardAcpiInit (
  IN EFI_HANDLE       ImageHandle
  );

#endif

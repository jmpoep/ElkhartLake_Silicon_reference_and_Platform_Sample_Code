/** @file
  Header file for PpmS3 Smm Driver.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

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
#ifndef _POWER_MGMT_SMM_H_
#define _POWER_MGMT_SMM_H_

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmPeriodicTimerDispatch2.h>
#include <Protocol/PchSmmPeriodicTimerControl.h>
#include <Library/HobLib.h>

#include <Library/PmcPrivateLib.h>
#include <Library/CpuPlatformLib.h>
#include <CpuInitDataHob.h>
#include <Library/CpuCommonLib.h>
#include <Register/Cpuid.h>
#include <Register/Msr.h>
#include <CpuAccess.h>
#include <PowerMgmtNvsStruct.h>
#include <Protocol/CpuNvsArea.h>
#include <Protocol/CpuPolicyProtocol.h>

#define PPM_WAIT_PERIOD 15

typedef struct {
  UINT8     Reserved1[248];
  UINT32    SMBASE;
  UINT32    SMMRevId;
  UINT16    IORestart;
  UINT16    AutoHALTRestart;
  UINT8     Reserved2[164];
  UINT32    ES;
  UINT32    CS;
  UINT32    SS;
  UINT32    DS;
  UINT32    FS;
  UINT32    GS;
  UINT32    LDTBase;
  UINT32    TR;
  UINT32    DR7;
  UINT32    DR6;
  UINT32    EAX;
  UINT32    ECX;
  UINT32    EDX;
  UINT32    EBX;
  UINT32    ESP;
  UINT32    EBP;
  UINT32    ESI;
  UINT32    EDI;
  UINT32    EIP;
  UINT32    EFLAGS;
  UINT32    CR3;
  UINT32    CR0;
} EFI_SMI_CPU_SAVE_STATE;

/**
  Runs the specified procedure on all logical processors, passing in the
  parameter buffer to the procedure.

  @param[in]     Procedure  The function to be run.
  @param[in out] Buffer     Pointer to a parameter buffer.

  @retval EFI_SUCCESS
**/
EFI_STATUS
RunOnAllLogicalProcessors (
  IN EFI_AP_PROCEDURE Procedure,
  IN OUT VOID         *Buffer
  );

/**
  Digital Thermal Sensor (DTS) SMM driver function.
  @retval EFI_SUCCESS            Driver initialization completed successfully
  @retval EFI_OUT_OF_RESOURCES   Error when allocating required memory buffer.
**/
EFI_STATUS
EFIAPI
InstallDigitalThermalSensor (
  VOID
  );

/**
  Initialize the HWP SMI Handler.
  @retval EFI_SUCCESS   The driver installes/initialized correctly.
**/
EFI_STATUS
EFIAPI
InitPowerMgmtHwpLvt (
  VOID
  );

/**
  Initialize the Periodic SMM to check for changes in IA32_HWP_Capabilities.
  Initalize the SMI handler to resume this periodic SMM if the OS supports it.

  @retval EFI_SUCCESS   The driver installes/initialized correctly.
  @retval EFI_NOT_FOUND CPU Data HOB not available.
**/
EFI_STATUS
EFIAPI
InitPowerMgmtItbmSmm (
  VOID
  );

#endif

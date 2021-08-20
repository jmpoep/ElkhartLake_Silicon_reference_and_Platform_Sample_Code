/** @file
  This file provides services for Gpio policy function

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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
#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/SiConfigBlockLib.h>
#include <Library/ConfigBlockLib.h>
#include <Protocol/PchPolicy.h>
#include <ConfigBlock/Gpio/GpioDevConfig.h>

/**
  Print GPIO_DXE_CONFIG and serial out.

  @param[in] PchPolicy            Pointer to a PCH_POLICY_PROTOCOL
**/
VOID
GpioDxePrintConfig (
  IN PCH_POLICY_PROTOCOL    *PchPolicy
  )
{
  EFI_STATUS        Status;
  GPIO_DXE_CONFIG   *GpioDxeConfig;

  Status = GetConfigBlock ((VOID *) PchPolicy, &gGpioDxeConfigGuid, (VOID *) &GpioDxeConfig);
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "------------------ GPIO DXE Config ------------------\n"));
  DEBUG ((DEBUG_INFO, " HideGpioAcpiDevice : %d\n", GpioDxeConfig->HideGpioAcpiDevice));
}

/**
  Load DXE Config block default for GPIO

  @param[in] ConfigBlockPointer         Pointer to config block
**/
VOID
GpioDxeLoadConfigDefault (
  IN VOID          *ConfigBlockPointer
  )
{
  GPIO_DXE_CONFIG  *GpioDxeConfig;
  GpioDxeConfig = ConfigBlockPointer;

  DEBUG ((DEBUG_INFO, "GpioDxeConfig->Header.GuidHob.Name = %g\n", &GpioDxeConfig->Header.GuidHob.Name));
  DEBUG ((DEBUG_INFO, "GpioDxeConfig->Header.GuidHob.Header.HobLength = 0x%x\n", GpioDxeConfig->Header.GuidHob.Header.HobLength));

  GpioDxeConfig->HideGpioAcpiDevice = 0;
}

STATIC COMPONENT_BLOCK_ENTRY  mGpioBlocks = {
  &gGpioDxeConfigGuid,
  sizeof (GPIO_DXE_CONFIG),
  GPIO_DXE_CONFIG_REVISION,
  GpioDxeLoadConfigDefault
};

/**
  Get Gpio config block table size.

  @retval      Size of config block
**/
UINT16
GpioDxeGetConfigBlockTotalSize (
  VOID
  )
{
  return mGpioBlocks.Size;
}

/**
  Add Gpio ConfigBlock.

  @param[in] ConfigBlockTableAddress    The pointer to config block table

  @retval EFI_SUCCESS                   The policy default is initialized.
  @retval EFI_OUT_OF_RESOURCES          Insufficient resources to create buffer
**/
EFI_STATUS
GpioDxeAddConfigBlock (
  IN VOID           *ConfigBlockTableAddress
  )
{
  return AddComponentConfigBlocks (ConfigBlockTableAddress, &mGpioBlocks, 1);
}

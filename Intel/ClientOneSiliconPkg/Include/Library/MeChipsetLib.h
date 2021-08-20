/** @file
  Header file for Me Chipset Lib

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2017 Intel Corporation.

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
#ifndef _ME_CHIPSET_LIB_H_
#define _ME_CHIPSET_LIB_H_

#include <Uefi.h>
#include <IndustryStandard/Pci22.h>

///
/// CSME PCI devices should be numbered according to their PCI function number
/// HECI1 = 0, HECI2 = 1, IDER = 2, SOL = 3, HECI3 = 4, HECI4 = 5
///
typedef enum {
  HECI1 = 0,
  HECI2,
  IDER,
  SOL,
  HECI3,
  HECI4,
} ME_DEVICE;

typedef enum {
  Disabled = 0,
  Enabled,
} ME_DEVICE_FUNC_CTRL;

/**
  Checks if the given PCIe ME Device Function is HECI Device Function

  @param[in]     Function  ME Device Function

  @retval TRUE   This is a HECI Device Function
  @retval FALSE  This is not a HECI Device Function
**/
BOOLEAN
IsHeciDeviceFunction (
  IN ME_DEVICE Function
  );

/**
  Put ME device out of D0I3

  @param[in] Function  ME function where D0I3 is to be changed

**/
VOID
ClearD0I3Bit (
  IN  UINT32   Function
  );

/**
  Put ME device into D0I3

  @param[in] Function          Select of Me device

**/
VOID
SetD0I3Bit (
  IN  UINT32   Function
  );

/**
  Enable/Disable Me devices

  @param[in] WhichDevice          Select of Me device
  @param[in] DeviceFuncCtrl       Function control

**/
VOID
MeDeviceControl (
  IN  ME_DEVICE                   WhichDevice,
  IN  ME_DEVICE_FUNC_CTRL         DeviceFuncCtrl
  );

/**
  Initialize Me devices

  @param[in] WhichDevice          Select of Me device
  @param[in] MmioAddrL32          MMIO address for 32-bit low dword
  @param[in] MmioAddrH32          MMIO address for 32-bit high dword

**/
VOID
MeDeviceInit (
  IN  ME_DEVICE                   WhichDevice,
  IN  UINT32                      MmioAddrL32,
  IN  UINT32                      MmioAddrH32
  );

/**
  Save HECI BARs

  @param[in] WhichDevice          Select of Me device
  @param[in] BarList              Buffer to store BAR addresses

**/
VOID
MeSaveBars (
  IN     ME_DEVICE                WhichDevice,
  IN OUT UINT32                   BarList[PCI_MAX_BAR]
  );

/**
  Restore HECI BARs

  @param[in] WhichDevice          Select of Me device
  @param[in] BarList              Buffer for BAR addresses to be restored

**/
VOID
MeRestoreBars (
  IN  ME_DEVICE                   WhichDevice,
  IN  UINT32                      BarList[PCI_MAX_BAR]
  );

/**
  This function gets sha384 CSME Measured data from HECI1 MMIO space (HECI1_HER1 - HECI1_HER12)

  @param[in]      Her            - Pointer to receive HER Data buffer of 12 DWORDS
  @param[in]      HerOffset      - Offset of first HER register in MMIO Space
  @param[in]      HerMaxRegCount - Max Register count to read HER registers

  @retval EFI_SUCCESS             Event data read successfully
  @retval EFI_INVALID_PARAMETER   Input parameters are not valid
  @retval EFI_DEVICE_ERROR        HECI Device error, command aborts abnormally
  @retval EFI_NOT_READY           Device is not ready
**/
EFI_STATUS
HeciGetHerDataSha384 (
  IN UINT32    *Her,
  IN UINT32    HerOffset,
  IN UINT8     HerMaxRegCount
  );

#endif


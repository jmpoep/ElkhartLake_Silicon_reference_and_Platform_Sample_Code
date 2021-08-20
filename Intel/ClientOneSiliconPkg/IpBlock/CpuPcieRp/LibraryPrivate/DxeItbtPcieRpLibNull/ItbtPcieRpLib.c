/** @file
  ITBT PCIE root port library.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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
#include <Base.h>
#include <Uefi/UefiBaseType.h>
/**
  Get ITBT Pcie Root Port Segment Bus Device and Function Number by Port Index

  @param[in]  PortIndex             Root port index. (0-based)
  @param[out] Segment               Return corresponding root port segment number.
  @param[out] Bus                   Return corresponding root port bus number.
  @param[out] Device                Return corresponding root port device number.
  @param[out] Function              Return corresponding root port function number.

  @retval     EFI_SUCCESS           Root port Info is retrieved
  @retval     EFI_UNSUPPORTED       PortIndex is invalid/disabled
**/
EFI_STATUS
EFIAPI
GetItbtPcieRpInfo (
  IN   UINTN    PortIndex,
  OUT  UINTN    *Segment,
  OUT  UINTN    *Bus,
  OUT  UINTN    *Device,
  OUT  UINTN    *Function
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Get ITBT PCIE Root Port Index by ITBT PCIE Root Port Segment Bus Device and Function Number

  @param[in]  Segment             Root port segment number.
  @param[in]  Bus                 Root port Bus.
  @param[in]  Device              Root port Device.
  @param[in]  Function            Root port Function.
  @param[out] PortIndex           Return corresponding Root Port index (0-based)

  @retval     EFI_SUCCESS           PortIndex is retrieved
  @retval     EFI_UNSUPPORTED       PortIndex is invalid/disabled
**/
EFI_STATUS
EFIAPI
GetItbtPciePortIndex (
  IN   UINTN    Segment,
  IN   UINTN    Bus,
  IN   UINTN    Device,
  IN   UINTN    Function,
  OUT  UINTN    *PortIndex
  )
{
  return EFI_UNSUPPORTED;
}

/**
  This function performs initialization for TBT Device Info Internal Structure
**/
VOID
InitializeItbtDevInfo (
  VOID
  )
{
}

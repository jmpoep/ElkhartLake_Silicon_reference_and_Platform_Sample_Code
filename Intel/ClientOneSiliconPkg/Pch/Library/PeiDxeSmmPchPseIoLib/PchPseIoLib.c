/** @file
  PCH Pse IO Lib implementation.
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <Library/IoLib.h>
#include <Library/BaseLib.h>
#include <IndustryStandard/Pci30.h>
#include <Library/PchPcrLib.h>
#include <Library/PchInfoLib.h>
#include <Library/MmPciLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PcdLib.h>
#include <Library/GpioPrivateLib.h>
#include <Library/PchPseIoLib.h>
#include <Include/PcieRegs.h>
#include <Library/PsfLib.h>
#include <PchLimits.h>
#include <Register/PchRegs.h>
#include <Register/PchPcrRegs.h>
#include <Register/PseRegs.h>
#include <Library/DebugLib.h>

// TODO: evaluate and port later as similar to Serial IO

GLOBAL_REMOVE_IF_UNREFERENCED UINT16 mPchPseIoPciCfgCtrAddr [PCH_MAX_PSE_CONTROLLERS] =
{
  R_PSE_IO_PCR_PCICFGCTRL1,
  R_PSE_IO_PCR_PCICFGCTRL2,
  R_PSE_IO_PCR_PCICFGCTRL3,
  R_PSE_IO_PCR_PCICFGCTRL4,
  R_PSE_IO_PCR_PCICFGCTRL5,
  R_PSE_IO_PCR_PCICFGCTRL6,
  R_PSE_IO_PCR_PCICFGCTRL7,
  R_PSE_IO_PCR_PCICFGCTRL8,
  R_PSE_IO_PCR_PCICFGCTRL9,
  R_PSE_IO_PCR_PCICFGCTRL10,
  R_PSE_IO_PCR_PCICFGCTRL11,
  R_PSE_IO_PCR_PCICFGCTRL12,
  R_PSE_IO_PCR_PCICFGCTRL13,
  R_PSE_IO_PCR_PCICFGCTRL14,
  R_PSE_IO_PCR_PCICFGCTRL15,
  R_PSE_IO_PCR_PCICFGCTRL16,
  R_PSE_IO_PCR_PCICFGCTRL17,
  R_PSE_IO_PCR_PCICFGCTRL18,
  R_PSE_IO_PCR_PCICFGCTRL19,
  R_PSE_IO_PCR_PCICFGCTRL20,
  R_PSE_IO_PCR_PCICFGCTRL21,
  R_PSE_IO_PCR_PCICFGCTRL22,
  R_PSE_IO_PCR_PCICFGCTRL23,
  R_PSE_IO_PCR_PCICFGCTRL24,
  R_PSE_IO_PCR_PCICFGCTRL25,
  R_PSE_IO_PCR_PCICFGCTRL26,
  R_PSE_IO_PCR_PCICFGCTRL27,
  R_PSE_IO_PCR_PCICFGCTRL28,
  R_PSE_IO_PCR_PCICFGCTRL29,
  R_PSE_IO_PCR_PCICFGCTRL30,
  R_PSE_IO_PCR_PCICFGCTRL31,
  R_PSE_IO_PCR_PCICFGCTRL32,
  R_PSE_IO_PCR_PCICFGCTRL33,
  R_PSE_IO_PCR_PCICFGCTRL34,
  R_PSE_IO_PCR_PCICFGCTRL35,
  R_PSE_IO_PCR_PCICFGCTRL36
};

/**
  Gets Pci Config control offset

  @param[in] DeviceNumber               device number
  @param[in] FunctionNumber             function number

  @retval    CfgCtrAddr                 Offset of Pci config control
                                        0 if Device and Function do not correspond to Serial IO
**/
UINT16
GetPseIoConfigControlOffset (
  IN UINT8  DeviceNumber,
  IN UINT8  FunctionNumber
  )
{
  PCH_PSE_IO_CONTROLLER  Controller;
  PCH_PSE_IO_CONTROLLER  ControllerMax;

  ControllerMax = GetPchMaxPseIoControllersNum ();

  for (Controller = 0; Controller < ControllerMax; Controller++) {
    if ((DeviceNumber == GetPseIoDeviceNumber (Controller)) &&
        (FunctionNumber == GetPseIoFunctionNumber (Controller))) {
      return mPchPseIoPciCfgCtrAddr[Controller];
    }
  }
  return 0;
}

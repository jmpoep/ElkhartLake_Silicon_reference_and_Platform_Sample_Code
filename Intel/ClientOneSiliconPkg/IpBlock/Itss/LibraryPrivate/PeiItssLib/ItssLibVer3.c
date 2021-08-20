/** @file
  VER3 PEI PCH ITSS library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2019 Intel Corporation.

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
#include <Library/DebugLib.h>
#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/PchInfoLib.h>

#include "ItssLibInternal.h"

extern CONST PCH_DEV_INT_INFO mPchDeviceInterruptInfo[];
extern UINT32                 mPchDeviceInterruptInfoSize;

/**
  Get Interrupt Info data

  @param[out] Size       Current size of the interrupt info

  @retval Pointer to Interrupt Info data on current PCH
**/
CONST PCH_DEV_INT_INFO*
GetInterruptInfoData (
  OUT UINT32  *Size
  )
{
  *Size = mPchDeviceInterruptInfoSize;
  return mPchDeviceInterruptInfo;
}

//
// @todo: Review once EHL documentation is available
//
GLOBAL_REMOVE_IF_UNREFERENCED CONST PCH_PIRX_REGISTER mPirxRegister[] = {
//Dev, PirIndex
  {31, 0},  // D31 LPC/eSPI, cAVS, SMBUS, SPI, GbE, TraceHub
  {29, 1},  // D29 PCIe
  {28, 2},  // D28 PCIe
  {23, 3},  // D23 SATA
  {22, 4},  // D22 HECI,IDER,KT
  {20, 5},  // D20 xHCI
  {16, 6}   // D16 THC
};

/**
  Get PIRx register data table

  @param[out] Size       Current size of the PIRx register table (number of PIRx registers)

  @retval Pointer to PIRx register data table
**/
CONST PCH_PIRX_REGISTER*
GetPirxRegData (
  OUT UINT32  *Size
  )
{
  *Size = ARRAY_SIZE (mPirxRegister);
  return mPirxRegister;
}

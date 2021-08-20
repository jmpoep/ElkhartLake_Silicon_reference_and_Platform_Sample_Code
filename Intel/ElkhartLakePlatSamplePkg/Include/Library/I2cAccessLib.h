/** @file
  Support for IO expander TCA6424.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2018 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/TimerLib.h>
#include <Library/IoLib.h>
#include <Library/UefiLib.h>
#include <Library/SerialIoAccessLib.h>

#define WAIT_1_SECOND            1600000000 //1.6 * 10^9
#define MAX_DATA_COUNT           6
#define BLOCK_COMMAND_WAIT       0
#define BLOCK_COMMAND_I2C_READ   1
#define BLOCK_COMMAND_I2C_WRITE  2

EFI_STATUS
I2cWriteRead (
  IN UINTN  MmioBase,
  IN UINT8  SlaveAddress,
  IN UINT8  WriteLength,
  IN UINT8  *WriteBuffer,
  IN UINT8  ReadLength,
  IN UINT8  *ReadBuffer,
  IN UINT64  TimeBudget
  );

EFI_STATUS
I2cBlockWriteRead(
  IN UINT8  I2cNumber,
  IN UINT8  SlaveAddress,
  IN UINT8 *I2cCommandBlock,
  IN UINT32 BlockSize
  );

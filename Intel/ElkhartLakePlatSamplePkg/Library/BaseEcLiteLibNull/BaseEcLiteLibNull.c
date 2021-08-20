/** @file
  Base EcLite Null library implementation for HECI layer.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:
**/

#include <Base.h>
#include <Uefi.h>
#include <EcLite.h>
#include <Library/EcLiteLib.h>
#include <Library/DebugLib.h>


/**
  Read/Write data from EcLite Firmware.

  @param[in] Flag            Data Read/Write, 0x01: Read 0x02: Write
  @param[in] Offset          Data Read/Write Offset
  @param[in] Length          Data payload Size in Bytes
  @param[in] CompletionCode  BIOS Notfication to ISH (if any action to be taken based on the Offset Write)
  @param[in] Data            Data buffer to be sent/updated based on the data length

  @retval    EFI_SUCCESS   Success
  @retval    EFI_TIMEOUT   Timeout
  @retval    Other         Failed
**/
EFI_STATUS
SendReceiveEcLiteData (
  IN     UINT8    Flag,
  IN     UINT16   Offset,
  IN     UINT16   Length,
  IN     UINT8    CompletionCode,
  IN OUT VOID    *Data
  )
{
  return EFI_SUCCESS;
}

/** @file
  Base EcLite library implementation for HECI layer.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017  -2019 Intel Corporation.

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

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/EcLiteLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Register/MeRegs.h>
#include <Protocol/HeciFlowProtocol.h>
#include <EcLite.h>

extern EFI_GUID gPseEcLiteHeciClientInterfaceGuid;
/**
  Read/Write data from EcLite Firmware.

  @param[in] Flag            Data Read/Write, 0x01: Read 0x02: Write
  @param[in] Offset          Data Read/Write Offset
  @param[in] Length          Data payload Size in Bytes
  @param[in] CompletionCode  BIOS Notfication to PSE (if any action to be taken based on the Offset Write)
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
  IN OUT VOID     *Data
  )
{
#if 1
  DEBUG((DEBUG_INFO, "EcLite: SendReceiveEcLiteData - Not supported now\n"));
  return EFI_SUCCESS;
#else
  HECI_ECLITE_HEADER   EcLitePayload;
  UINT8                *Buffer;
  UINT32               ReceiveLength;
  EFI_STATUS           Status;
  HECI_FLOW_PROTOCOL   *HeciFlow;

  DEBUG((DEBUG_INFO, "EcLite: SendReceiveEcLiteData\n"));
  //
  // Validate Input Parameters
  //
  if (((Flag != ECLITE_READ_COMMAND) && (Flag != ECLITE_WRITE_COMMAND)) ||
      (Offset > ECLITE_MAX_BYTES_SUPPORTED) ||
      (Length > ECLITE_MAX_BYTES_SUPPORTED) ||
      (Data == NULL)) {
    DEBUG ((DEBUG_INFO, "EcLite: Invalid input parameters\n"));
    return EFI_INVALID_PARAMETER;
  }
  EcLitePayload.Fields.HeaderVersion       = ECLITE_HEADER_REVISION;
  EcLitePayload.Fields.DataType            = 1;
  EcLitePayload.Fields.DataReadWrite       = Flag;
  EcLitePayload.Fields.DataReadWriteOffset = Offset;
  EcLitePayload.Fields.DataLength          = Length;
  EcLitePayload.Fields.CompletionCode      = CompletionCode;
  //
  // Initiate HECI flow to get the data from EcLite App Firmware
  //
  Status = gBS->LocateProtocol (&gHeciFlowProtocolGuid, NULL, (VOID **)&HeciFlow);
  if (!EFI_ERROR (Status)) {
    ReceiveLength = sizeof (HECI_ECLITE_HEADER) + Length;
    Buffer = AllocateZeroPool (ReceiveLength);
    if (Buffer != NULL) {
      CopyMem (Buffer, &EcLitePayload, sizeof (HECI_ECLITE_HEADER));
      CopyMem ((Buffer + sizeof (HECI_ECLITE_HEADER)), (UINT8 *)Data, Length);
      Status = HeciFlow->SendAndReceive (PSE_HECI, (UINT32 *)Buffer, ReceiveLength, &ReceiveLength, &gPseEcLiteHeciClientInterfaceGuid);
      if (!EFI_ERROR (Status)) {
        CopyMem ((UINT8 *) Data, (Buffer + sizeof (HECI_ECLITE_HEADER)), Length);
        DEBUG ((DEBUG_INFO, "EcLite: Data %x\n", (*(UINT32 *)Data)));
      }

      FreePool (Buffer);
      return Status;
    }

    DEBUG ((DEBUG_INFO, "EcLite: Buffer allocation failure\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  DEBUG ((DEBUG_INFO, "EcLite: LocateProtocol failure %r\n", Status));
  return Status;
#endif
}

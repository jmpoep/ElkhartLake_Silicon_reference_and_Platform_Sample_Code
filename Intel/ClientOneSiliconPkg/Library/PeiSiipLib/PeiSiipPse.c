/**@file
  PSE Siip library implementation

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification
**/

#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TimerLib.h>
#include <Library/PciSegmentLib.h>
#include <SiipCommon.h>

#include <IndustryStandard/Pci30.h>
#include <Register/PchRegs.h>
#include <Register/PseRegs.h>
#include <Library/IoLib.h>
#include <Library/PeiSiipPse.h>
#include <Library/PseInfoLib.h>

/**
  Acquire PSE mmio address.

  @retval PchPseBar              return PSE MMIO address
**/
UINTN
AcquirePseBar (
  VOID
  )
{
  UINT64       PchPseBase;
  UINT8        PseDeviceNumber;
  UINT8        PseFunctionNumber;

  PseDeviceNumber = PseGetDeviceNumber ();
  PseFunctionNumber = PseGetFunctionNumber ();

  PchPseBase = PCI_SEGMENT_LIB_ADDRESS (
                 DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                 DEFAULT_PCI_BUS_NUMBER_PCH,
                 PseDeviceNumber,
                 PseFunctionNumber,
                 0
                 );
  return (((UINT64) PciSegmentRead32 (PchPseBase + R_PSE_CFG_BAR0_HIGH) << 32)
          | (PciSegmentRead32 (PchPseBase + R_PSE_CFG_BAR0_LOW) & ~(B_PSE_CFG_BAR0_MASK)));
}

/**
  Send IP specific dashboard Read/Write command

  @param[in]     OperationType    Read/Write command (0: Read operation, 1: Write operation)
  @param[in]     RegisterType     Loader/Verifier type (0: Loader, 1: Verifier)
  @param[in]     RegisterOffset   Dashboard register offset to be accessed
  @param[in]     NumberOfBytes    Number of byes to be read or written
  @param[in out] DataBuffer       For read operation it is of output type, for write operation it is of input type

  @retval EFI_SUCCESS             Command was executed successfully
  @retval EFI_INVALID_PARAMETER   Invalid command size
  @retval EFI_DEVICE_ERROR        Command failed with an error
  @retval EFI_TIMEOUT             Command did not complete in given timing requirements
**/
EFI_STATUS
PseSendCommand (
  IN     SIIP_OP_TYPE             OperationType,
  IN     SIIP_REG_TYPE            RegisterType,
  IN     UINT16                   RegisterOffset,
  IN     SIIP_NUM_BYTES           NumberOfBytes,
  IN OUT VOID                     *DataBuffer
  )
{
  EFI_STATUS             Status;
  UINTN                  PchPseBar;

  Status = EFI_SUCCESS;
  PchPseBar = AcquirePseBar();
  DEBUG ((DEBUG_INFO, "PchPseBar %x\n", PchPseBar));

  if (OperationType == READ) {
    if (RegisterType == LOADER) {
      switch (NumberOfBytes) {
        case TWO_BYTES:
          *(UINT16 *)DataBuffer = MmioRead16 (PchPseBar + R_PSE_MMIO_LOADER_OFFSET + RegisterOffset);
          break;
        case FOUR_BYTES:
          *(UINT32 *)DataBuffer = MmioRead32 (PchPseBar + R_PSE_MMIO_LOADER_OFFSET + RegisterOffset);
          break;
        case EIGHT_BYTES:
          *(UINT64 *)DataBuffer = MmioRead64 (PchPseBar + R_PSE_MMIO_LOADER_OFFSET + RegisterOffset);
          break;
        default:
          Status = EFI_INVALID_PARAMETER;
          break;
      }
    } else if (RegisterType == VERIFIER) {
      switch (NumberOfBytes) {
        case TWO_BYTES:
          *(UINT16 *)DataBuffer = MmioRead16 (PchPseBar + R_PSE_MMIO_VERIFER_OFFSET + RegisterOffset);
          break;
        case FOUR_BYTES:
          *(UINT32 *)DataBuffer = MmioRead32 (PchPseBar + R_PSE_MMIO_VERIFER_OFFSET + RegisterOffset);
          break;
        case EIGHT_BYTES:
          *(UINT64 *)DataBuffer = MmioRead64 (PchPseBar + R_PSE_MMIO_VERIFER_OFFSET + RegisterOffset);
          break;
        default:
          Status = EFI_INVALID_PARAMETER;
          break;
      }
    }
  } else if (OperationType == WRITE) {
    if (RegisterType == LOADER) {
      switch (NumberOfBytes) {
        case TWO_BYTES:
          Status = EFI_INVALID_PARAMETER; // 2 bytes MmioWrite is truncated therefore invalid
          break;
        case FOUR_BYTES:
          MmioWrite32 (PchPseBar + R_PSE_MMIO_LOADER_OFFSET + RegisterOffset, *(UINT32 *)DataBuffer);
          break;
        case EIGHT_BYTES:
          MmioWrite64 (PchPseBar + R_PSE_MMIO_LOADER_OFFSET + RegisterOffset, *(UINT64 *)DataBuffer);
          break;
        default:
          Status = EFI_INVALID_PARAMETER;
          break;
      }
    } else if (RegisterType == VERIFIER) {
      switch (NumberOfBytes) {
        case TWO_BYTES:
          Status = EFI_INVALID_PARAMETER; // 2 bytes MmioWrite is truncated therefore invalid
          break;
        case FOUR_BYTES:
          MmioWrite32 (PchPseBar + R_PSE_MMIO_VERIFER_OFFSET + RegisterOffset, *(UINT32 *)DataBuffer);
          break;
        case EIGHT_BYTES:
          MmioWrite64 (PchPseBar + R_PSE_MMIO_VERIFER_OFFSET + RegisterOffset, *(UINT64 *)DataBuffer);
          break;
        default:
          Status = EFI_INVALID_PARAMETER;
          break;
      }
    }
  }
  DEBUG ((DEBUG_INFO, "PseSendCommand: Op %x, RegType %x, Offset 0x%x , NumOfBytes %d, Data %x\n",
          OperationType, RegisterType, RegisterOffset, NumberOfBytes,  *(UINT64 *)DataBuffer));

  return Status;
}

/** @file
  PCH SBI access library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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
#include <IndustryStandard/Pci30.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Register/PchRegs.h>
#include <Register/P2sbRegs.h>

/**
  Execute PCH SBI message
  Take care of that there is no lock protection when using SBI programming in both POST time and SMI.
  It will clash with POST time SBI programming when SMI happen.
  Programmer MUST do the save and restore opration while using the PchSbiExecution inside SMI
  to prevent from racing condition.
  This function will reveal P2SB and hide P2SB if it's originally hidden. If more than one SBI access
  needed, it's better to unhide the P2SB before calling and hide it back after done.

  When the return value is "EFI_SUCCESS", the "Response" do not need to be checked as it would have been
  SBI_SUCCESS. If the return value is "EFI_DEVICE_ERROR", then this would provide additional information
  when needed.

  @param[in] Pid                        Port ID of the SBI message
  @param[in] Offset                     Offset of the SBI message
  @param[in] Opcode                     Opcode
  @param[in] Posted                     Posted message
  @param[in, out] Data32                Read/Write data
  @param[out] Response                  Response

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_DEVICE_ERROR              Transaction fail
  @retval EFI_INVALID_PARAMETER         Invalid parameter
  @retval EFI_TIMEOUT                   Timeout while waiting for response
**/
EFI_STATUS
PchSbiExecution (
  IN     PCH_SBI_PID                    Pid,
  IN     UINT64                         Offset,
  IN     PCH_SBI_OPCODE                 Opcode,
  IN     BOOLEAN                        Posted,
  IN OUT UINT32                         *Data32,
  OUT    UINT8                          *Response
  )
{
  return PchSbiExecutionEx ( Pid,
           Offset,
           Opcode,
           Posted,
           0x000F,
           0x0000,
           0x0000,
           Data32,
           Response
           );
}

/**
  Full function for executing PCH SBI message
  Take care of that there is no lock protection when using SBI programming in both POST time and SMI.
  It will clash with POST time SBI programming when SMI happen.
  Programmer MUST do the save and restore opration while using the PchSbiExecution inside SMI
  to prevent from racing condition.
  This function will reveal P2SB and hide P2SB if it's originally hidden. If more than one SBI access
  needed, it's better to unhide the P2SB before calling and hide it back after done.

  When the return value is "EFI_SUCCESS", the "Response" do not need to be checked as it would have been
  SBI_SUCCESS. If the return value is "EFI_DEVICE_ERROR", then this would provide additional information
  when needed.

  @param[in] Pid                        Port ID of the SBI message
  @param[in] Offset                     Offset of the SBI message
  @param[in] Opcode                     Opcode
  @param[in] Posted                     Posted message
  @param[in] Fbe                        First byte enable
  @param[in] Bar                        Bar
  @param[in] Fid                        Function ID
  @param[in, out] Data32                Read/Write data
  @param[out] Response                  Response

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_DEVICE_ERROR              Transaction fail
  @retval EFI_INVALID_PARAMETER         Invalid parameter
  @retval EFI_TIMEOUT                   Timeout while waiting for response
**/
EFI_STATUS
PchSbiExecutionEx (
  IN     PCH_SBI_PID                    Pid,
  IN     UINT64                         Offset,
  IN     PCH_SBI_OPCODE                 Opcode,
  IN     BOOLEAN                        Posted,
  IN     UINT16                         Fbe,
  IN     UINT16                         Bar,
  IN     UINT16                         Fid,
  IN OUT UINT32                         *Data32,
  OUT    UINT8                          *Response
  )
{
  UINT64                                P2sbBase;
  UINTN                                 Timeout;
  UINT16                                SbiStat;

  //
  // Check opcode valid
  //
  switch (Opcode) {
    case MemoryRead:
    case MemoryWrite:
    case PciConfigRead:
    case PciConfigWrite:
    case PrivateControlRead:
    case PrivateControlWrite:
    case GpioLockUnlock:
      break;
    default:
      return EFI_INVALID_PARAMETER;
      break;
  }

  P2sbBase = PCI_SEGMENT_LIB_ADDRESS (
               DEFAULT_PCI_SEGMENT_NUMBER_PCH,
               DEFAULT_PCI_BUS_NUMBER_PCH,
               PCI_DEVICE_NUMBER_PCH_P2SB,
               PCI_FUNCTION_NUMBER_PCH_P2SB,
               0
               );
  if (PciSegmentRead16 (P2sbBase + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    ASSERT (FALSE);
    return EFI_DEVICE_ERROR;
  }
  ///
  /// BWG Section 2.2.1
  /// 1. Poll P2SB PCI offset D8h[0] = 0b
  /// Make sure the previous opeartion is completed.
  ///
  Timeout = 0xFFFFFFF;
  while (Timeout > 0) {
    SbiStat = PciSegmentRead16 (P2sbBase + R_P2SB_CFG_SBISTAT);
    if ((SbiStat & B_P2SB_CFG_SBISTAT_INITRDY) == 0) {
      break;
    }
    Timeout--;
  }
  if (Timeout == 0) {
    return EFI_TIMEOUT;
  }
  //
  // Initial Response status
  //
  *Response = SBI_INVALID_RESPONSE;
  SbiStat   = 0;
  ///
  /// 2. Write P2SB PCI offset D0h[31:0] with Address and Destination Port ID
  ///
  PciSegmentWrite32 (P2sbBase + R_P2SB_CFG_SBIADDR, (UINT32) ((Pid << 24) | (UINT16) Offset));
  ///
  /// 3. Write P2SB PCI offset DCh[31:0] with extended address, which is expected to be 0 in CNL PCH.
  ///
  PciSegmentWrite32 (P2sbBase + R_P2SB_CFG_SBIEXTADDR, (UINT32) RShiftU64 (Offset, 16));
  ///
  /// 5. Set P2SB PCI offset D8h[15:8] = 00000110b for read
  ///    Set P2SB PCI offset D8h[15:8] = 00000111b for write
  //
  // Set SBISTAT[15:8] to the opcode passed in
  // Set SBISTAT[7] to the posted passed in
  //
  PciSegmentAndThenOr16 (
    (P2sbBase + R_P2SB_CFG_SBISTAT),
    (UINT16) ~(B_P2SB_CFG_SBISTAT_OPCODE | B_P2SB_CFG_SBISTAT_POSTED),
    (UINT16) ((Opcode << 8) | (Posted << 7))
    );
  ///
  /// 6. Write P2SB PCI offset DAh[15:0] = F000h
  ///
  //
  // Set RID[15:0] = Fbe << 12 | Bar << 8 | Fid
  //
  PciSegmentWrite16 (
    (P2sbBase + R_P2SB_CFG_SBIRID),
    (((Fbe & 0x000F) << 12) | ((Bar & 0x0007) << 8) | (Fid & 0x00FF))
    );

  switch (Opcode) {
    case MemoryWrite:
    case PciConfigWrite:
    case PrivateControlWrite:
    case GpioLockUnlock:
      ///
      /// 4. Write P2SB PCI offset D4h[31:0] with the intended data accordingly
      ///
      PciSegmentWrite32 ((P2sbBase + R_P2SB_CFG_SBIDATA), *Data32);
      break;
    default:
      ///
      /// 4. Write P2SB PCI offset D4h[31:0] with dummy data such as 0,
      /// because all D0-DFh register range must be touched in CNL PCH
      /// for a successful SBI transaction.
      ///
      PciSegmentWrite32 ((P2sbBase + R_P2SB_CFG_SBIDATA), 0);
      break;
  }
  ///
  /// 7. Set P2SB PCI offset D8h[0] = 1b, Poll P2SB PCI offset D8h[0] = 0b
  ///
  //
  // Set SBISTAT[0] = 1b, trigger the SBI operation
  //
  PciSegmentOr16 (P2sbBase + R_P2SB_CFG_SBISTAT, (UINT16) B_P2SB_CFG_SBISTAT_INITRDY);
  //
  // Poll SBISTAT[0] = 0b, Polling for Busy bit
  //
  Timeout = 0xFFFFFFF;
  while (Timeout > 0) {
    SbiStat = PciSegmentRead16 (P2sbBase + R_P2SB_CFG_SBISTAT);
    if ((SbiStat & B_P2SB_CFG_SBISTAT_INITRDY) == 0) {
      break;
    }
    Timeout--;
  }
  if (Timeout == 0) {
    //
    // If timeout, it's fatal error.
    //
    return EFI_TIMEOUT;
  } else {
    ///
    /// 8. Check if P2SB PCI offset D8h[2:1] = 00b for successful transaction
    ///
    *Response = (UINT8) ((SbiStat & B_P2SB_CFG_SBISTAT_RESPONSE) >> N_P2SB_CFG_SBISTAT_RESPONSE);
    if (*Response == SBI_SUCCESSFUL) {
      switch (Opcode) {
        case MemoryRead:
        case PciConfigRead:
        case PrivateControlRead:
          ///
          /// 9. Read P2SB PCI offset D4h[31:0] for SBI data
          ///
          *Data32 = PciSegmentRead32 (P2sbBase + R_P2SB_CFG_SBIDATA);
          break;
        default:
          break;
      }
      return EFI_SUCCESS;
    } else {
      return EFI_DEVICE_ERROR;
    }
  }
}


/** @file
  TCSS PMC Library.
  PMC-PD BIOS-PMC handshake messages
  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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

#include <Library/IoLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/BaseLib.h>
#include <Library/PmcLib.h>
#include <Library/PmcPrivateLib.h>
#include <Library/TcssPmcLib.h>

/**
  Handshake with PMC if PMC handshaking support is enabled BIOS sends TCSS_BIOS_INIT Done (aka.USBC connection replay)
  message along with USBC connctions replay setting to PMC. All TCSS initialization is expected to be done before PMC
  do any port negotiation. The indicator sent from BIOS to PMC should be treated as TCSS BIOS initialization done
  semaphore.

  @param[in]       IomReadyStatus       Status of IomReady bit read from TCSS Hob
  @param[in]       PmcReplay            Replay status based on VccSt and BootMode

  @retval          EFI_SUCCESS          Command success
  @retval          EFI_DEVICE_ERROR     Command error
**/
EFI_STATUS
PmcTcssBiosInitDone (
  IN  EFI_STATUS                        IomReadyStatus,
  IN  UINT8                             PmcReplay
)
{
  EFI_STATUS                            Status;
  UINT32                                PmcIomReadyBitMask;
  UINT32                                PmcReplayBitMask;
  PMC_IPC_COMMAND_BUFFER                Wbuf;

  DEBUG ((DEBUG_INFO, "[TCSS]PmcTcssBiosInitDone: Sending TCSS BIOS Init Done message to PMC\n"));

  ZeroMem (&Wbuf, sizeof (PMC_IPC_COMMAND_BUFFER));

  //
  // Set IomReady bit if IOM is ready
  //
  PmcIomReadyBitMask = 0;
  if (IomReadyStatus == EFI_SUCCESS) {
    PmcIomReadyBitMask = BIT0;
  }

  //
  // Replay bit
  //
  if (PmcReplay == 1) {
    PmcReplayBitMask = BIT1;
  } else {
    PmcReplayBitMask = 0;
  }

  Wbuf.Buf0 = PmcIomReadyBitMask | PmcReplayBitMask;

  Status = PmcSendCommand (
    PMC_IPC_COMMAND_ID_TCSS_INFO,
    PMC_IPC_SUB_COMMAND_ID_TCSS_BIOS_INIT_DONE,
    4,
    &Wbuf,
    NULL);

  return Status;
}
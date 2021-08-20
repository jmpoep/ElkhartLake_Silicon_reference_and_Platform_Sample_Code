/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2017 Intel Corporation.

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

#include <IndustryStandard/Tpm12.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/Tpm2DeviceLib.h>
#include <Library/PciSegmentLib.h>

#include <Library/PttPtpLib.h>
#include <Guid/PttPTPInstanceGuid.h>

#define R_PTT_HCI_BASE_ADDRESS             0xFED40000

/**
  This service enables the sending of commands to the TPM2.

  @param[in]  InputParameterBlockSize  Size of the TPM2 input parameter block.
  @param[in]  InputParameterBlock      Pointer to the TPM2 input parameter block.
  @param[in]  OutputParameterBlockSize Size of the TPM2 output parameter block.
  @param[in]  OutputParameterBlock     Pointer to the TPM2 output parameter block.

  @retval EFI_SUCCESS            The command byte stream was successfully sent to the device and a response was successfully received.
  @retval EFI_DEVICE_ERROR       The command was not successfully sent to the device or a response was not successfully received from the device.
  @retval EFI_BUFFER_TOO_SMALL   The output parameter block is too small.
**/
EFI_STATUS
EFIAPI
PttSubmitCommand (
  IN UINT32            InputParameterBlockSize,
  IN UINT8             *InputParameterBlock,
  IN OUT UINT32        *OutputParameterBlockSize,
  IN UINT8             *OutputParameterBlock
  )
{
  return PttHciSubmitCommand(InputParameterBlock, InputParameterBlockSize, OutputParameterBlock, OutputParameterBlockSize);
}

EFI_STATUS
EFIAPI
PttRequestUseTpm (
  VOID
  )
{

  BOOLEAN IsPttEnabled;
  UINT32 Data32;

  IsPttEnabled = FALSE;

  //
  // Check if it's SV ME FW first
  // Read FirmwareStatus register D22:F0:40h BIT[3:0]
  //
  Data32 = (PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 22, 0, 0x40))) & 0x0F;

  //
  // Return error if SV ME FW detected
  // ME_STATE_SV_FW = 0x0F
  //
  if (Data32 == 0x0F) {
    return EFI_DEVICE_ERROR;
  }

  if ((*(UINT8 *) (UINTN) (R_PTT_HCI_BASE_ADDRESS + R_TPM_INTERFACE_ID) != 0xFF)) {
    IsPttEnabled = TRUE;
  }

  if(!IsPttEnabled)
  {
    return EFI_DEVICE_ERROR;
  }

  return EFI_SUCCESS;
}

TPM2_DEVICE_INTERFACE  mPttInternalTpm2Device = {
  TPM_DEVICE_INTERFACE_TPM20_PTT_PTP,
  PttSubmitCommand,
  PttRequestUseTpm,
};

EFI_STATUS
EFIAPI
Tpm2InstanceLibPttConstructor (
  VOID
  )
{
  EFI_STATUS  Status;

  Status = Tpm2RegisterTpm2DeviceLib (&mPttInternalTpm2Device);
  if ((Status == EFI_SUCCESS) || (Status == EFI_UNSUPPORTED)) {
    //
    // Unsupported means platform policy does not need this instance enabled.
    //
    return EFI_SUCCESS;
  }
  return Status;
}

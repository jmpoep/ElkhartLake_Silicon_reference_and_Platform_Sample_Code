/** @file
  Wrap EFI_SPI_PROTOCOL to provide some library level interfaces
  for module use.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2018 Intel Corporation.

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

#include <Library/SpiFlashCommon.h>
#include <Library/IoLib.h>
#include <Protocol/BiosGuard.h>

PCH_SPI_PROTOCOL       *mSpiProtocol;
BIOSGUARD_PROTOCOL     *mBiosGuardProtocol;

//
// Variables for boottime and runtime usage.
//
UINTN mBiosAreaBaseAddress = 0;
UINTN mBiosSize            = 0;
UINTN mBiosOffset          = 0;

/**
  Enable block protection on the Serial Flash device.

  @retval     EFI_SUCCESS       Opertion is successful.
  @retval     EFI_DEVICE_ERROR  If there is any device errors.

**/
EFI_STATUS
EFIAPI
SpiFlashLock (
  VOID
  )
{
  EFI_STATUS  Status;

  Status = EFI_SUCCESS;

  if (mBiosGuardProtocol != NULL) {
    Status = mBiosGuardProtocol->Execute (
                              mBiosGuardProtocol,
                              FALSE
                              );
  }

  return Status;
}

/**
  Read NumBytes bytes of data from the address specified by
  PAddress into Buffer.

  @param[in]      Address       The starting physical address of the read.
  @param[in,out]  NumBytes      On input, the number of bytes to read. On output, the number
                                of bytes actually read.
  @param[out]     Buffer        The destination data buffer for the read.

  @retval         EFI_SUCCESS       Opertion is successful.
  @retval         EFI_DEVICE_ERROR  If there is any device errors.

**/
EFI_STATUS
EFIAPI
SpiFlashRead (
  IN     UINTN                        Address,
  IN OUT UINT32                       *NumBytes,
     OUT UINT8                        *Buffer
  )
{
  ASSERT ((NumBytes != NULL) && (Buffer != NULL));
  if ((NumBytes == NULL) || (Buffer == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  //
  // This function is implemented specifically for those platforms
  // at which the SPI device is memory mapped for read. So this
  // function just do a memory copy for Spi Flash Read.
  //
  CopyMem (Buffer, (VOID *) Address, *NumBytes);

  return EFI_SUCCESS;
}

/**
  Write NumBytes bytes of data from Buffer to the address specified by
  PAddresss.

  @param[in]      Address         The starting physical address of the write.
  @param[in,out]  NumBytes        On input, the number of bytes to write. On output,
                                  the actual number of bytes written.
  @param[in]      Buffer          The source data buffer for the write.

  @retval         EFI_SUCCESS       Opertion is successful.
  @retval         EFI_DEVICE_ERROR  If there is any device errors.

**/
EFI_STATUS
EFIAPI
SpiFlashWrite (
  IN     UINTN                      Address,
  IN OUT UINT32                     *NumBytes,
  IN     UINT8                      *Buffer
  )
{
  EFI_STATUS                Status;
  UINTN                     Offset;
  UINT32                    Length;
  UINT32                    RemainingBytes;

  ASSERT ((NumBytes != NULL) && (Buffer != NULL));
  if ((NumBytes == NULL) || (Buffer == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  ASSERT (Address >= mBiosAreaBaseAddress);

  Offset = Address - mBiosAreaBaseAddress;

  ASSERT ((*NumBytes + Offset) <= mBiosSize);

  Status = EFI_SUCCESS;
  RemainingBytes = *NumBytes;

  if (mBiosGuardProtocol != NULL) {
    ///
    /// BIOS Guard Write protocol takes the offset from the base of flash component.
    ///
    Offset = mBiosOffset + Offset;

    mBiosGuardProtocol->Write (
                     mBiosGuardProtocol,
                     (UINT32) Offset,
                     RemainingBytes,
                     Buffer
                     );
    return EFI_SUCCESS;
  }

  while (RemainingBytes > 0) {
    if (RemainingBytes > SECTOR_SIZE_4KB) {
      Length = SECTOR_SIZE_4KB;
    } else {
      Length = RemainingBytes;
    }
    Status = mSpiProtocol->FlashWrite (
                             mSpiProtocol,
                             FlashRegionBios,
                             (UINT32) Offset,
                             Length,
                             Buffer
                             );
    if (EFI_ERROR (Status)) {
      break;
    }
    RemainingBytes -= Length;
    Offset += Length;
    Buffer += Length;
  }

  //
  // Actual number of bytes written
  //
  *NumBytes -= RemainingBytes;

  return Status;
}

/**
  Erase the block starting at Address.

  @param[in]  Address         The starting physical address of the block to be erased.
                              This library assume that caller garantee that the PAddress
                              is at the starting address of this block.
  @param[in]  NumBytes        On input, the number of bytes of the logical block to be erased.
                              On output, the actual number of bytes erased.

  @retval     EFI_SUCCESS.      Opertion is successful.
  @retval     EFI_DEVICE_ERROR  If there is any device errors.

**/
EFI_STATUS
EFIAPI
SpiFlashBlockErase (
  IN    UINTN                     Address,
  IN    UINTN                     *NumBytes
  )
{
  EFI_STATUS          Status;
  UINTN               Offset;
  UINTN               RemainingBytes;

  ASSERT (NumBytes != NULL);
  if (NumBytes == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ASSERT (Address >= mBiosAreaBaseAddress);

  Offset = Address - mBiosAreaBaseAddress;

  ASSERT ((*NumBytes % SECTOR_SIZE_4KB) == 0);
  ASSERT ((*NumBytes + Offset) <= mBiosSize);

  Status = EFI_SUCCESS;
  RemainingBytes = *NumBytes;

  if (mBiosGuardProtocol != NULL) {
    ///
    /// BIOS Guard Erase protocol takes the offset from the base of flash component.
    ///
    Offset = mBiosOffset + Offset;

    while (RemainingBytes > 0) {
      mBiosGuardProtocol->Erase (
                       mBiosGuardProtocol,
                       (UINT32) Offset
                       );
      RemainingBytes -= SECTOR_SIZE_4KB;
      Offset         += SECTOR_SIZE_4KB;
    }
    return EFI_SUCCESS;
  }

  Status = mSpiProtocol->FlashErase (
                           mSpiProtocol,
                           FlashRegionBios,
                           (UINT32) Offset,
                           (UINT32) RemainingBytes
                           );
  return Status;
}


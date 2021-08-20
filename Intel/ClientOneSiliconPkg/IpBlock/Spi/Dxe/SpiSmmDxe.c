/** @file
  SPI DXE Driver implements the SPI Host Controller Compatibility Interface.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/SmmCommunication.h>
#include <Protocol/Spi.h>
#include "SpiSmmCommunication.h"

#define SPI_COMM_BUFFER_PAGE       2
EFI_SMM_COMMUNICATION_PROTOCOL     *mSmmCommunication        = NULL;
VOID                               *mCommunicateBuffer       = NULL;
CONST UINT32                       mMaxDataSize              = EFI_PAGES_TO_SIZE (SPI_COMM_BUFFER_PAGE - 1);

/**
  Initialize the communicate buffer using DataSize and Function number.

  @param[out]      CommunicateBuffer The communicate buffer. Caller should free it after use.
  @param[out]      DataPtr           Points to the data in the communicate buffer. Caller should not free it.
  @param[in]       DataSize          The payload size.
  @param[in]       Function          The function number used to initialize the communicate header.

  @retval EFI_SUCCESS                Command succeed.
  @retval EFI_ACCESS_DENIED          SmmCommunicateHeaderSize is more than SPI_COMM_BUFFER_PAGE.
**/
STATIC
EFI_STATUS
InitCommunicateBuffer (
  OUT     VOID                              **CommunicateBuffer,
  OUT     VOID                              **DataPtr,
  IN      UINTN                             DataSize,
  IN      UINTN                             Function
  )
{
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_COMMUNICATE_FUNCTION_HEADER       *SmmSpiFunctionHeader;
  UINTN                                     SmmCommunicateHeaderSize;

  //
  // The whole buffer size: SMM_COMMUNICATE_HEADER_SIZE + SMM_SPI_COMMUNICATE_HEADER_SIZE + DataSize.
  //
  SmmCommunicateHeader     = mCommunicateBuffer;
  SmmCommunicateHeaderSize = SMM_COMMUNICATE_HEADER_SIZE + SMM_SPI_COMMUNICATE_HEADER_SIZE + DataSize;
  if (SmmCommunicateHeaderSize > EFI_PAGES_TO_SIZE (SPI_COMM_BUFFER_PAGE)) {
    return EFI_ACCESS_DENIED;
  }
  ZeroMem (SmmCommunicateHeader, SmmCommunicateHeaderSize);

  //
  // Prepare data buffer.
  //
  CopyGuid (&SmmCommunicateHeader->HeaderGuid, &gPchSmmSpiProtocolGuid);
  SmmCommunicateHeader->MessageLength = SMM_SPI_COMMUNICATE_HEADER_SIZE + DataSize;

  SmmSpiFunctionHeader = (SMM_SPI_COMMUNICATE_FUNCTION_HEADER *) SmmCommunicateHeader->Data;
  SmmSpiFunctionHeader->Function = Function;
  SmmSpiFunctionHeader->ReturnStatus = EFI_NOT_READY;

  *CommunicateBuffer = SmmCommunicateHeader;
  if (DataPtr != NULL) {
    *DataPtr = SmmSpiFunctionHeader->Data;
  }
  return EFI_SUCCESS;
}

/**
  Send the data in communicate buffer to SMI handler and get response.

  @param[in, out]  SmmCommunicateHeader    The communicate buffer.
  @param[in]       DataSize                The payload size.

  @return          The status from SMM communication
**/
EFI_STATUS
SendCommunicateBuffer (
  IN OUT  EFI_SMM_COMMUNICATE_HEADER        *SmmCommunicateHeader,
  IN      UINTN                             DataSize
  )
{
  EFI_STATUS                                Status;
  UINTN                                     CommSize;
  SMM_SPI_COMMUNICATE_FUNCTION_HEADER       *SmmSpiFunctionHeader;

  CommSize = SMM_COMMUNICATE_HEADER_SIZE + SMM_SPI_COMMUNICATE_HEADER_SIZE + DataSize;
  Status = mSmmCommunication->Communicate (mSmmCommunication, SmmCommunicateHeader, &CommSize);
  ASSERT_EFI_ERROR (Status);

  SmmSpiFunctionHeader = (SMM_SPI_COMMUNICATE_FUNCTION_HEADER *) SmmCommunicateHeader->Data;
  return  SmmSpiFunctionHeader->ReturnStatus;
}


/**
  Read data from the flash part.

  @param[in] This                 Pointer to the PCH_SPI_PROTOCOL instance.
  @param[in] FlashRegionType      The Flash Region type for flash cycle which is listed in the Descriptor.
  @param[in] Address              The Flash Linear Address must fall within a region for which BIOS has access permissions.
  @param[in] ByteCount            Number of bytes in the data portion of the SPI cycle.
  @param[out] Buffer              The Pointer to caller-allocated buffer containing the dada received.
                                  It is the caller's responsibility to make sure Buffer is large enough for the total number of bytes read.

  @retval EFI_SUCCESS             Command succeed.
  @retval EFI_INVALID_PARAMETER   The parameters specified are not valid.
  @retval EFI_DEVICE_ERROR        Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
SpiFlashRead (
  IN     PCH_SPI_PROTOCOL   *This,
  IN     FLASH_REGION_TYPE  FlashRegionType,
  IN     UINT32             Address,
  IN     UINT32             ByteCount,
  OUT    UINT8              *Buffer
  )
{
  EFI_STATUS                                Status;
  UINTN                                     PayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_FLASH_READ                        *SmmSpiFlashRead;
  UINT32                                    TempByteCount;
  UINT32                                    Index;

  Status = EFI_INVALID_PARAMETER;
  TempByteCount = ByteCount;
  Index         = 0;
  while (TempByteCount > 0) {
    //
    // Initialize PayloadSize.
    //
    if (TempByteCount > mMaxDataSize) {
      PayloadSize = sizeof (SMM_SPI_FLASH_READ) + mMaxDataSize;
    } else {
      PayloadSize = sizeof (SMM_SPI_FLASH_READ) + TempByteCount;
    }

    //
    // Initialize the communicate buffer.
    //
    Status = InitCommunicateBuffer ((VOID **)&SmmCommunicateHeader, (VOID **)&SmmSpiFlashRead, PayloadSize, SPI_FUNCTION_FLASH_READ);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "SpiFlashRead - InitCommunicateBuffer fails\n"));
      return Status;
    }

    //
    // Fill input data
    //
    SmmSpiFlashRead->FlashRegionType = FlashRegionType;
    SmmSpiFlashRead->Address         = Address + Index;
    SmmSpiFlashRead->ByteCount       = (UINT32)(PayloadSize - sizeof (SMM_SPI_FLASH_READ));
    SmmSpiFlashRead->Buffer          = (UINT8 *)(SmmSpiFlashRead + 1);

    //
    // Send data to SMM.
    //
    Status = SendCommunicateBuffer (SmmCommunicateHeader, PayloadSize);

    //
    // Check output data
    //
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "SpiFlashRead - Communication : %r\n", Status));
      return Status;
    }
    CopyMem (Buffer + Index, SmmSpiFlashRead->Buffer, SmmSpiFlashRead->ByteCount);

    if (TempByteCount > mMaxDataSize) {
      Index         += mMaxDataSize;
      TempByteCount -= mMaxDataSize;
    } else {
      break;
    }
  }

  return Status;
}

/**
  Write data to the flash part. Remark: Erase may be needed before write to the flash part.

  @param[in] This                 Pointer to the PCH_SPI_PROTOCOL instance.
  @param[in] FlashRegionType      The Flash Region type for flash cycle which is listed in the Descriptor.
  @param[in] Address              The Flash Linear Address must fall within a region for which BIOS has access permissions.
  @param[in] ByteCount            Number of bytes in the data portion of the SPI cycle.
  @param[in] Buffer               Pointer to caller-allocated buffer containing the data sent during the SPI cycle.

  @retval EFI_SUCCESS             Command succeed.
  @retval EFI_INVALID_PARAMETER   The parameters specified are not valid.
  @retval EFI_DEVICE_ERROR        Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
SpiFlashWrite (
  IN     PCH_SPI_PROTOCOL   *This,
  IN     FLASH_REGION_TYPE  FlashRegionType,
  IN     UINT32             Address,
  IN     UINT32             ByteCount,
  IN     UINT8              *Buffer
  )
{
  EFI_STATUS                                Status;
  UINTN                                     PayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_FLASH_WRITE                       *SmmSpiFlashWrite;
  UINT32                                    TempByteCount;
  UINT32                                    Index;

  Status = EFI_INVALID_PARAMETER;
  TempByteCount = ByteCount;
  Index         = 0;
  while (TempByteCount > 0) {
    //
    // Initialize PayloadSize.
    //
    if (TempByteCount > mMaxDataSize) {
      PayloadSize = sizeof (SMM_SPI_FLASH_WRITE) + mMaxDataSize;
    } else {
      PayloadSize = sizeof (SMM_SPI_FLASH_WRITE) + TempByteCount;
    }

    //
    // Initialize the communicate buffer.
    //
    Status = InitCommunicateBuffer ((VOID **)&SmmCommunicateHeader, (VOID **)&SmmSpiFlashWrite, PayloadSize, SPI_FUNCTION_FLASH_WRITE);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "SpiFlashWrite - InitCommunicateBuffer fails\n"));
      return Status;
    }

    //
    // Fill input data
    //
    SmmSpiFlashWrite->FlashRegionType = FlashRegionType;
    SmmSpiFlashWrite->Address         = Address + Index;
    SmmSpiFlashWrite->ByteCount       = (UINT32)(PayloadSize - sizeof (SMM_SPI_FLASH_WRITE));
    SmmSpiFlashWrite->Buffer          = (UINT8 *)(SmmSpiFlashWrite + 1);

    //
    // Send data to SMM.
    //
    CopyMem (SmmSpiFlashWrite->Buffer, Buffer + Index, SmmSpiFlashWrite->ByteCount);
    Status = SendCommunicateBuffer (SmmCommunicateHeader, PayloadSize);

    //
    // Check output data
    //
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "SpiFlashWrite - Communication : %r\n", Status));
      return Status;
    }

    if (TempByteCount > mMaxDataSize) {
      Index         += mMaxDataSize;
      TempByteCount -= mMaxDataSize;
    } else {
      break;
    }
  }

  return Status;
}

/**
  Erase some area on the flash part.

  @param[in] This                 Pointer to the PCH_SPI_PROTOCOL instance.
  @param[in] FlashRegionType      The Flash Region type for flash cycle which is listed in the Descriptor.
  @param[in] Address              The Flash Linear Address must fall within a region for which BIOS has access permissions.
  @param[in] ByteCount            Number of bytes in the data portion of the SPI cycle.

  @retval EFI_SUCCESS             Command succeed.
  @retval EFI_INVALID_PARAMETER   The parameters specified are not valid.
  @retval EFI_DEVICE_ERROR        Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
SpiFlashErase (
  IN     PCH_SPI_PROTOCOL   *This,
  IN     FLASH_REGION_TYPE  FlashRegionType,
  IN     UINT32             Address,
  IN     UINT32             ByteCount
  )
{
  EFI_STATUS                                Status;
  UINTN                                     PayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_FLASH_ERASE                       *SmmSpiFlashErase;

  PayloadSize = sizeof (SMM_SPI_FLASH_ERASE);

  //
  // Initialize the communicate buffer.
  //
  Status = InitCommunicateBuffer ((VOID **)&SmmCommunicateHeader, (VOID **)&SmmSpiFlashErase, PayloadSize, SPI_FUNCTION_FLASH_ERASE);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashErase - Communication : %r\n", Status));
    return Status;
  }

  //
  // Fill input data
  //
  SmmSpiFlashErase->FlashRegionType = FlashRegionType;
  SmmSpiFlashErase->Address = Address;
  SmmSpiFlashErase->ByteCount = ByteCount;

  //
  // Send data to SMM.
  //
  Status = SendCommunicateBuffer (SmmCommunicateHeader, PayloadSize);

  //
  // Check output data
  //
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashErase - Communication : %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Read SFDP data from the flash part.

  @param[in] This                 Pointer to the PCH_SPI_PROTOCOL instance.
  @param[in] ComponentNumber      The Componen Number for chip select
  @param[in] Address              The starting byte address for SFDP data read.
  @param[in] ByteCount            Number of bytes in SFDP data portion of the SPI cycle
  @param[out] SfdpData            The Pointer to caller-allocated buffer containing the SFDP data received
                                  It is the caller's responsibility to make sure Buffer is large enough for the total number of bytes read

  @retval EFI_SUCCESS             Command succeed.
  @retval EFI_INVALID_PARAMETER   The parameters specified are not valid.
  @retval EFI_DEVICE_ERROR        Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
SpiFlashReadSfdp (
  IN     PCH_SPI_PROTOCOL   *This,
  IN     UINT8              ComponentNumber,
  IN     UINT32             Address,
  IN     UINT32             ByteCount,
  OUT    UINT8              *SfdpData
  )
{
  EFI_STATUS                                Status;
  UINTN                                     PayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_FLASH_READ_SFDP                   *SmmSpiFlashReadSfdp;

  PayloadSize = sizeof (SMM_SPI_FLASH_READ_SFDP) + ByteCount;

  //
  // Initialize the communicate buffer.
  //
  Status = InitCommunicateBuffer ((VOID **)&SmmCommunicateHeader, (VOID **)&SmmSpiFlashReadSfdp, PayloadSize, SPI_FUNCTION_FLASH_READ_SFDP);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashReadSfdp - InitCommunicateBuffer fails\n"));
    return Status;
  }

  //
  // Fill input data
  //
  SmmSpiFlashReadSfdp->ComponentNumber = ComponentNumber;
  SmmSpiFlashReadSfdp->Address = Address;
  SmmSpiFlashReadSfdp->ByteCount = ByteCount;
  SmmSpiFlashReadSfdp->SfdpData = (UINT8 *)(SmmSpiFlashReadSfdp + 1);

  //
  // Send data to SMM.
  //
  Status = SendCommunicateBuffer (SmmCommunicateHeader, PayloadSize);
  CopyMem (SfdpData, SmmSpiFlashReadSfdp->SfdpData, ByteCount);

  //
  // Check output data
  //
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashReadSfdp - Communication : %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Read Jedec Id from the flash part.

  @param[in] This                 Pointer to the PCH_SPI_PROTOCOL instance.
  @param[in] ComponentNumber      The Componen Number for chip select
  @param[in] ByteCount            Number of bytes in JedecId data portion of the SPI cycle, the data size is 3 typically
  @param[out] JedecId             The Pointer to caller-allocated buffer containing JEDEC ID received
                                  It is the caller's responsibility to make sure Buffer is large enough for the total number of bytes read.

  @retval EFI_SUCCESS             Command succeed.
  @retval EFI_INVALID_PARAMETER   The parameters specified are not valid.
  @retval EFI_DEVICE_ERROR        Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
SpiFlashReadJedecId (
  IN     PCH_SPI_PROTOCOL   *This,
  IN     UINT8              ComponentNumber,
  IN     UINT32             ByteCount,
  OUT    UINT8              *JedecId
  )
{
  EFI_STATUS                                Status;
  UINTN                                     PayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_FLASH_READ_JEDEC_ID               *SmmSpiFlashReadJedecId;

  PayloadSize = sizeof (SMM_SPI_FLASH_READ_JEDEC_ID) + ByteCount;

  //
  // Initialize the communicate buffer.
  //
  Status = InitCommunicateBuffer ((VOID **)&SmmCommunicateHeader, (VOID **)&SmmSpiFlashReadJedecId, PayloadSize, SPI_FUNCTION_FLASH_READ_JEDEC_ID);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashReadJedecId - InitCommunicateBuffer fails\n"));
    return Status;
  }

  //
  // Fill input data
  //
  SmmSpiFlashReadJedecId->ComponentNumber = ComponentNumber;
  SmmSpiFlashReadJedecId->ByteCount = ByteCount;
  SmmSpiFlashReadJedecId->JedecId = (UINT8 *)(SmmSpiFlashReadJedecId + 1);

  //
  // Send data to SMM.
  //
  Status = SendCommunicateBuffer (SmmCommunicateHeader, PayloadSize);
  CopyMem (JedecId, SmmSpiFlashReadJedecId->JedecId, ByteCount);

  //
  // Check output data
  //
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashReadJedecId - Communication : %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Write the status register in the flash part.

  @param[in] This                 Pointer to the PCH_SPI_PROTOCOL instance.
  @param[in] ByteCount            Number of bytes in Status data portion of the SPI cycle, the data size is 1 typically
  @param[in] StatusValue          The Pointer to caller-allocated buffer containing the value of Status register writing

  @retval EFI_SUCCESS             Command succeed.
  @retval EFI_INVALID_PARAMETER   The parameters specified are not valid.
  @retval EFI_DEVICE_ERROR        Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
SpiFlashWriteStatus (
  IN     PCH_SPI_PROTOCOL   *This,
  IN     UINT32             ByteCount,
  IN     UINT8              *StatusValue
  )
{
  EFI_STATUS                                Status;
  UINTN                                     PayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_FLASH_WRITE_STATUS                *SmmSpiFlashWriteStatus;

  PayloadSize = sizeof (SMM_SPI_FLASH_WRITE_STATUS) + ByteCount;

  //
  // Initialize the communicate buffer.
  //
  Status = InitCommunicateBuffer ((VOID **)&SmmCommunicateHeader, (VOID **)&SmmSpiFlashWriteStatus, PayloadSize, SPI_FUNCTION_FLASH_WRITE_STATUS);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashWriteStatus - InitCommunicateBuffer fails\n"));
    return Status;
  }

  //
  // Fill input data
  //
  SmmSpiFlashWriteStatus->ByteCount = ByteCount;
  SmmSpiFlashWriteStatus->StatusValue = (UINT8 *)(SmmSpiFlashWriteStatus + 1);

  //
  // Send data to SMM.
  //
  CopyMem (SmmSpiFlashWriteStatus->StatusValue, StatusValue, ByteCount);
  Status = SendCommunicateBuffer (SmmCommunicateHeader, PayloadSize);

  //
  // Check output data
  //
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashWriteStatus - Communication : %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Read status register in the flash part.

  @param[in] This                 Pointer to the PCH_SPI_PROTOCOL instance.
  @param[in] ByteCount            Number of bytes in Status data portion of the SPI cycle, the data size is 1 typically
  @param[out] StatusValue         The Pointer to caller-allocated buffer containing the value of Status register received.

  @retval EFI_SUCCESS             Command succeed.
  @retval EFI_INVALID_PARAMETER   The parameters specified are not valid.
  @retval EFI_DEVICE_ERROR        Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
SpiFlashReadStatus (
  IN     PCH_SPI_PROTOCOL   *This,
  IN     UINT32             ByteCount,
  OUT    UINT8              *StatusValue
  )
{
  EFI_STATUS                                Status;
  UINTN                                     PayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_FLASH_READ_STATUS                 *SmmSpiFlashReadStatus;

  PayloadSize = sizeof (SMM_SPI_FLASH_READ_STATUS) + ByteCount;

  //
  // Initialize the communicate buffer.
  //
  Status = InitCommunicateBuffer ((VOID **)&SmmCommunicateHeader, (VOID **)&SmmSpiFlashReadStatus, PayloadSize, SPI_FUNCTION_FLASH_READ_STATUS);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashReadStatus - InitCommunicateBuffer fails\n"));
    return Status;
  }

  //
  // Fill input data
  //
  SmmSpiFlashReadStatus->ByteCount = ByteCount;
  SmmSpiFlashReadStatus->StatusValue = (UINT8 *)(SmmSpiFlashReadStatus + 1);

  //
  // Send data to SMM.
  //
  Status = SendCommunicateBuffer (SmmCommunicateHeader, PayloadSize);
  CopyMem (StatusValue, SmmSpiFlashReadStatus->StatusValue, ByteCount);

  //
  // Check output data
  //
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiFlashReadStatus - Communication : %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Get the SPI region base and size, based on the enum type

  @param[in] This                 Pointer to the PCH_SPI_PROTOCOL instance.
  @param[in] FlashRegionType      The Flash Region type for for the base address which is listed in the Descriptor.
  @param[out] BaseAddress         The Flash Linear Address for the Region 'n' Base
  @param[out] RegionSize          The size for the Region 'n'

  @retval EFI_SUCCESS             Read success
  @retval EFI_INVALID_PARAMETER   Invalid region type given
  @retval EFI_DEVICE_ERROR        The region is not used
**/
EFI_STATUS
EFIAPI
SpiGetRegionAddress (
  IN     PCH_SPI_PROTOCOL   *This,
  IN     FLASH_REGION_TYPE  FlashRegionType,
  OUT    UINT32             *BaseAddress,
  OUT    UINT32             *RegionSize
  )
{
  EFI_STATUS                                Status;
  UINTN                                     PayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_GET_REGION_ADDRESS                *SmmSpiGetRegionAddress;

  PayloadSize = sizeof (SMM_SPI_GET_REGION_ADDRESS) + sizeof (UINT32) + sizeof (UINT32);

  //
  // Initialize the communicate buffer.
  //
  Status = InitCommunicateBuffer ((VOID **)&SmmCommunicateHeader, (VOID **)&SmmSpiGetRegionAddress, PayloadSize, SPI_FUNCTION_GET_REGION_ADDRESS);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiGetRegionAddress - InitCommunicateBuffer fails\n"));
    return Status;
  }

  //
  // Fill input data
  //
  SmmSpiGetRegionAddress->FlashRegionType = FlashRegionType;
  SmmSpiGetRegionAddress->BaseAddress = (UINT32 *)(SmmSpiGetRegionAddress + 1);
  SmmSpiGetRegionAddress->RegionSize = (UINT32 *)(SmmSpiGetRegionAddress + 1) + 1;

  //
  // Send data to SMM.
  //
  Status = SendCommunicateBuffer (SmmCommunicateHeader, PayloadSize);
  CopyMem (BaseAddress, SmmSpiGetRegionAddress->BaseAddress, sizeof (UINT32));
  CopyMem (RegionSize, SmmSpiGetRegionAddress->RegionSize, sizeof (UINT32));

  //
  // Check output data
  //
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiGetRegionAddress - Communication : %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Read PCH Soft Strap Values

  @param[in] This                 Pointer to the PCH_SPI_PROTOCOL instance.
  @param[in] SoftStrapAddr        PCH Soft Strap address offset from FPSBA.
  @param[in] ByteCount            Number of bytes in SoftStrap data portion of the SPI cycle
  @param[out] SoftStrapValue      The Pointer to caller-allocated buffer containing PCH Soft Strap Value.
                                  If the value of ByteCount is 0, the data type of SoftStrapValue should be UINT16 and SoftStrapValue will be PCH Soft Strap Length
                                  It is the caller's responsibility to make sure Buffer is large enough for the total number of bytes read.

  @retval EFI_SUCCESS             Command succeed.
  @retval EFI_INVALID_PARAMETER   The parameters specified are not valid.
  @retval EFI_DEVICE_ERROR        Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
SpiReadPchSoftStrap (
  IN     PCH_SPI_PROTOCOL   *This,
  IN     UINT32             SoftStrapAddr,
  IN     UINT32             ByteCount,
  OUT    VOID               *SoftStrapValue
  )
{
  EFI_STATUS                                Status;
  UINTN                                     PayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_READ_PCH_SOFTSTRAP                *SmmSpiReadPchSoftStrap;

  PayloadSize = sizeof (SMM_SPI_READ_PCH_SOFTSTRAP) + ByteCount;

  //
  // Initialize the communicate buffer.
  //
  Status = InitCommunicateBuffer ((VOID **)&SmmCommunicateHeader, (VOID **)&SmmSpiReadPchSoftStrap, PayloadSize, SPI_FUNCTION_READ_PCH_SOFTSTRAP);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiReadPchSoftStrap - InitCommunicateBuffer fails\n"));
    return Status;
  }

  //
  // Fill input data
  //
  SmmSpiReadPchSoftStrap->SoftStrapAddr = SoftStrapAddr;
  SmmSpiReadPchSoftStrap->ByteCount = ByteCount;
  SmmSpiReadPchSoftStrap->SoftStrapValue = (UINT8 *)(SmmSpiReadPchSoftStrap + 1);

  //
  // Send data to SMM.
  //
  Status = SendCommunicateBuffer (SmmCommunicateHeader, PayloadSize);
  CopyMem (SoftStrapValue, SmmSpiReadPchSoftStrap->SoftStrapValue, ByteCount);

  //
  // Check output data
  //
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiReadPchSoftStrap - Communication : %r\n", Status));
    return Status;
  }

  return Status;
}

/**
  Read CPU Soft Strap Values

  @param[in] This                 Pointer to the PCH_SPI_PROTOCOL instance.
  @param[in] SoftStrapAddr        CPU Soft Strap address offset from FCPUSBA.
  @param[in] ByteCount            Number of bytes in SoftStrap data portion of the SPI cycle.
  @param[out] SoftStrapValue      The Pointer to caller-allocated buffer containing CPU Soft Strap Value.
                                  If the value of ByteCount is 0, the data type of SoftStrapValue should be UINT16 and SoftStrapValue will be PCH Soft Strap Length
                                  It is the caller's responsibility to make sure Buffer is large enough for the total number of bytes read.

  @retval EFI_SUCCESS             Command succeed.
  @retval EFI_INVALID_PARAMETER   The parameters specified are not valid.
  @retval EFI_DEVICE_ERROR        Device error, command aborts abnormally.
**/
EFI_STATUS
EFIAPI
SpiReadCpuSoftStrap (
  IN     PCH_SPI_PROTOCOL   *This,
  IN     UINT32             SoftStrapAddr,
  IN     UINT32             ByteCount,
  OUT    VOID               *SoftStrapValue
  )
{
  EFI_STATUS                                Status;
  UINTN                                     PayloadSize;
  EFI_SMM_COMMUNICATE_HEADER                *SmmCommunicateHeader;
  SMM_SPI_READ_CPU_SOFTSTRAP                *SmmSpiReadCpuSoftStrap;

  PayloadSize = sizeof (SMM_SPI_READ_CPU_SOFTSTRAP) + ByteCount;

  //
  // Initialize the communicate buffer.
  //
  Status = InitCommunicateBuffer ((VOID **)&SmmCommunicateHeader, (VOID **)&SmmSpiReadCpuSoftStrap, PayloadSize, SPI_FUNCTION_READ_CPU_SOFTSTRAP);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiReadCpuSoftStrap - InitCommunicateBuffer fails\n"));
    return Status;
  }

  //
  // Fill input data
  //
  SmmSpiReadCpuSoftStrap->SoftStrapAddr = SoftStrapAddr;
  SmmSpiReadCpuSoftStrap->ByteCount = ByteCount;
  SmmSpiReadCpuSoftStrap->SoftStrapValue = (UINT8 *)(SmmSpiReadCpuSoftStrap + 1);

  //
  // Send data to SMM.
  //
  Status = SendCommunicateBuffer (SmmCommunicateHeader, PayloadSize);
  CopyMem (SoftStrapValue, SmmSpiReadCpuSoftStrap->SoftStrapValue, ByteCount);

  //
  // Check output data
  //
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "SpiReadCpuSoftStrap - Communication : %r\n", Status));
    return Status;
  }

  return Status;
}

PCH_SPI_PROTOCOL  mSpiProtocol = {
  PCH_SPI_SERVICES_REVISION,
  SpiFlashRead,
  SpiFlashWrite,
  SpiFlashErase,
  SpiFlashReadSfdp,
  SpiFlashReadJedecId,
  SpiFlashWriteStatus,
  SpiFlashReadStatus,
  SpiGetRegionAddress,
  SpiReadPchSoftStrap,
  SpiReadCpuSoftStrap,
};

/**
  SPI DXE Module Entry Point.

  @param[in] ImageHandle          Image handle of this driver.
  @param[in] SystemTable          Global system service table.

  @retval EFI_SUCCESS             Initialization complete.
  @exception EFI_UNSUPPORTED      The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
InstallSpiSmmDxe (
  IN EFI_HANDLE            ImageHandle,
  IN EFI_SYSTEM_TABLE      *SystemTable
  )
{
  EFI_STATUS                      Status;
  EFI_HANDLE                      Handle;

  DEBUG ((DEBUG_INFO, "InstallSpiSmmDxe() Start\n"));

  Status = gBS->LocateProtocol (&gEfiSmmCommunicationProtocolGuid, NULL, (VOID **) &mSmmCommunication);
  ASSERT_EFI_ERROR (Status);
  mCommunicateBuffer = AllocateRuntimePages (SPI_COMM_BUFFER_PAGE);
  ASSERT (mCommunicateBuffer != NULL);

  Handle = NULL;
  Status = gBS->InstallMultipleProtocolInterfaces (
                  &Handle,
                  &gPchSpiProtocolGuid,
                  &mSpiProtocol,
                  NULL
                  );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "InstallSpiSmmDxe() End\n"));

  return Status;
}

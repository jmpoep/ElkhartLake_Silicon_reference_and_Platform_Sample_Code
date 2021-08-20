/** @file
  SPI STUB SMM Driver implements the SPI Host Controller Compatibility Interface.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/SmmServicesTableLib.h>
#include <Library/SmmMemLib.h>
#include <Protocol/Spi.h>
#include <Guid/EventGroup.h>
#include "SpiSmmCommunication.h"

PCH_SPI_PROTOCOL  *mSmmSpiProtocol;
EFI_HANDLE        mSmmSpiHandle;
BOOLEAN           mEndOfDxe;

/**
  Communication service SMI Handler entry.

  This SMI handler provides services for the fault tolerant write wrapper driver.

  NOTE: This handle will be unregistered at EndOfDxe.
  No check is needed.

  @param[in]     DispatchHandle  The unique handle assigned to this handler by SmiHandlerRegister().
  @param[in]     RegisterContext Points to an optional handler context which was specified when the
                                 handler was registered.
  @param[in, out] CommBuffer     A pointer to a collection of data in memory that will be conveyed
                                 from a non-SMM environment into an SMM environment.
  @param[in, out] CommBufferSize The size of the CommBuffer.

  @retval EFI_SUCCESS                         The interrupt was handled and quiesced. No other handlers
                                              should still be called.
  @retval EFI_WARN_INTERRUPT_SOURCE_QUIESCED  The interrupt has been quiesced but other handlers should
                                              still be called.
  @retval EFI_WARN_INTERRUPT_SOURCE_PENDING   The interrupt is still pending and other handlers should still
                                              be called.
  @retval EFI_INTERRUPT_PENDING               The interrupt could not be quiesced.

**/
EFI_STATUS
EFIAPI
SmmSpiHandler (
  IN     EFI_HANDLE                                DispatchHandle,
  IN     CONST VOID                                *RegisterContext,
  IN OUT VOID                                      *CommBuffer,
  IN OUT UINTN                                     *CommBufferSize
  )
{
  EFI_STATUS                                       Status;
  SMM_SPI_COMMUNICATE_FUNCTION_HEADER              *SmmSpiFunctionHeader;
  SMM_SPI_FLASH_READ                               *SmmSpiFlashRead;
  SMM_SPI_FLASH_WRITE                              *SmmSpiFlashWrite;
  SMM_SPI_FLASH_ERASE                              *SmmSpiFlashErase;
  SMM_SPI_FLASH_READ_SFDP                          *SmmSpiFlashReadSfdp;
  SMM_SPI_FLASH_READ_JEDEC_ID                      *SmmSpiFlashReadJedecId;
  SMM_SPI_FLASH_WRITE_STATUS                       *SmmSpiFlashWriteStatus;
  SMM_SPI_FLASH_READ_STATUS                        *SmmSpiFlashReadStatus;
  SMM_SPI_GET_REGION_ADDRESS                       *SmmSpiGetRegionAddress;
  SMM_SPI_READ_PCH_SOFTSTRAP                       *SmmSpiReadPchSoftStrap;
  SMM_SPI_READ_CPU_SOFTSTRAP                       *SmmSpiReadCpuSoftStrap;
  UINTN                                            CommBufferPayloadSize;
  UINTN                                            TempCommBufferSize;

  //
  // If input is invalid, stop processing this SMI
  //
  if ((CommBuffer == NULL) || (CommBufferSize == NULL)) {
    return EFI_SUCCESS;
  }

  TempCommBufferSize = *CommBufferSize;

  if (TempCommBufferSize < SMM_SPI_COMMUNICATE_HEADER_SIZE) {
    DEBUG ((DEBUG_ERROR, "SmmSpiHandler: SMM communication buffer size invalid!\n"));
    return EFI_SUCCESS;
  }
  CommBufferPayloadSize = TempCommBufferSize - SMM_SPI_COMMUNICATE_HEADER_SIZE;

  if (!SmmIsBufferOutsideSmmValid ((UINTN)CommBuffer, TempCommBufferSize)) {
    DEBUG ((DEBUG_ERROR, "SmmSpiHandler: SMM communication buffer in SMRAM or overflow!\n"));
    return EFI_SUCCESS;
  }

  SmmSpiFunctionHeader = (SMM_SPI_COMMUNICATE_FUNCTION_HEADER *)CommBuffer;

  if (mEndOfDxe) {
    if ((SmmSpiFunctionHeader->Function == SPI_FUNCTION_FLASH_WRITE) ||
        (SmmSpiFunctionHeader->Function == SPI_FUNCTION_FLASH_ERASE))
    {
      //
      // It will be not safe to expose the operations after End Of Dxe.
      //
      DEBUG ((DEBUG_ERROR, "SmmSpiHandler: Not safe to do the operation: %x after End Of Dxe, so access denied!\n", SmmSpiFunctionHeader->Function));
      SmmSpiFunctionHeader->ReturnStatus = EFI_ACCESS_DENIED;
      return EFI_SUCCESS;
    }
  }

  SmmSpiFunctionHeader->ReturnStatus = EFI_INVALID_PARAMETER;

  switch (SmmSpiFunctionHeader->Function) {
    case SPI_FUNCTION_FLASH_READ:
      if (CommBufferPayloadSize < sizeof (SMM_SPI_FLASH_READ)) {
        DEBUG ((DEBUG_ERROR, "FlashRead: SMM communication buffer size invalid!\n"));
        return EFI_SUCCESS;
      }
      SmmSpiFlashRead = (SMM_SPI_FLASH_READ *) SmmSpiFunctionHeader->Data;
      //
      // Check buffer range is valid
      //
      if (((SmmSpiFlashRead->Buffer) != (UINT8 *)(SmmSpiFlashRead + 1)) ||
          ((SmmSpiFlashRead->Buffer + SmmSpiFlashRead->ByteCount) > (SmmSpiFunctionHeader->Data + CommBufferPayloadSize)))
      {
        DEBUG ((DEBUG_ERROR, "FlashRead: SMM communication buffer range invalid!\n"));
        return EFI_SUCCESS;
      }

      Status = mSmmSpiProtocol->FlashRead (
                                  mSmmSpiProtocol,
                                  SmmSpiFlashRead->FlashRegionType,
                                  SmmSpiFlashRead->Address,
                                  SmmSpiFlashRead->ByteCount,
                                  SmmSpiFlashRead->Buffer
                                  );
      break;

    case SPI_FUNCTION_FLASH_WRITE:
      if (CommBufferPayloadSize < sizeof (SMM_SPI_FLASH_WRITE)) {
        DEBUG ((DEBUG_ERROR, "FlashWrite: SMM communication buffer size invalid!\n"));
        return EFI_SUCCESS;
      }
      SmmSpiFlashWrite = (SMM_SPI_FLASH_WRITE *) SmmSpiFunctionHeader->Data;
      //
      // Check buffer range is valid
      //
      if (((SmmSpiFlashWrite->Buffer) != (UINT8 *)(SmmSpiFlashWrite + 1)) ||
          ((SmmSpiFlashWrite->Buffer + SmmSpiFlashWrite->ByteCount) > (SmmSpiFunctionHeader->Data + CommBufferPayloadSize)))
      {
        DEBUG ((DEBUG_ERROR, "FlashWrite: SMM communication buffer range invalid!\n"));
        return EFI_SUCCESS;
      }

      Status = mSmmSpiProtocol->FlashWrite (
                                  mSmmSpiProtocol,
                                  SmmSpiFlashWrite->FlashRegionType,
                                  SmmSpiFlashWrite->Address,
                                  SmmSpiFlashWrite->ByteCount,
                                  SmmSpiFlashWrite->Buffer
                                  );
      break;

    case SPI_FUNCTION_FLASH_ERASE:
      if (CommBufferPayloadSize < sizeof (SMM_SPI_FLASH_ERASE)) {
        DEBUG ((DEBUG_ERROR, "FlashErase: SMM communication buffer size invalid!\n"));
        return EFI_SUCCESS;
      }
      SmmSpiFlashErase = (SMM_SPI_FLASH_ERASE *) SmmSpiFunctionHeader->Data;

      Status = mSmmSpiProtocol->FlashErase (
                                  mSmmSpiProtocol,
                                  SmmSpiFlashErase->FlashRegionType,
                                  SmmSpiFlashErase->Address,
                                  SmmSpiFlashErase->ByteCount
                                  );
      break;

    case SPI_FUNCTION_FLASH_READ_SFDP:
      if (CommBufferPayloadSize < sizeof (SMM_SPI_FLASH_READ_SFDP)) {
        DEBUG ((DEBUG_ERROR, "FlashReadSfdp: SMM communication buffer size invalid!\n"));
        return EFI_SUCCESS;
      }
      SmmSpiFlashReadSfdp = (SMM_SPI_FLASH_READ_SFDP *) SmmSpiFunctionHeader->Data;
      //
      // Check buffer range is valid
      //
      if (((SmmSpiFlashReadSfdp->SfdpData) != (UINT8 *)(SmmSpiFlashReadSfdp + 1)) ||
          ((SmmSpiFlashReadSfdp->SfdpData + SmmSpiFlashReadSfdp->ByteCount) > (SmmSpiFunctionHeader->Data + CommBufferPayloadSize)))
      {
        DEBUG ((DEBUG_ERROR, "FlashReadSfdp: SMM communication buffer range invalid!\n"));
        return EFI_SUCCESS;
      }

      Status = mSmmSpiProtocol->FlashReadSfdp (
                                  mSmmSpiProtocol,
                                  SmmSpiFlashReadSfdp->ComponentNumber,
                                  SmmSpiFlashReadSfdp->Address,
                                  SmmSpiFlashReadSfdp->ByteCount,
                                  SmmSpiFlashReadSfdp->SfdpData
                                  );
      break;

    case SPI_FUNCTION_FLASH_READ_JEDEC_ID:
      if (CommBufferPayloadSize < sizeof (SMM_SPI_FLASH_READ_JEDEC_ID)) {
        DEBUG ((DEBUG_ERROR, "FlashReadJedecId: SMM communication buffer size invalid!\n"));
        return EFI_SUCCESS;
      }
      SmmSpiFlashReadJedecId = (SMM_SPI_FLASH_READ_JEDEC_ID *) SmmSpiFunctionHeader->Data;
      //
      // Check buffer range is valid
      //
      if (((SmmSpiFlashReadJedecId->JedecId) != (UINT8 *)(SmmSpiFlashReadJedecId + 1)) ||
          ((SmmSpiFlashReadJedecId->JedecId + SmmSpiFlashReadJedecId->ByteCount) > (SmmSpiFunctionHeader->Data + CommBufferPayloadSize)))
      {
        DEBUG ((DEBUG_ERROR, "FlashReadJedecId: SMM communication buffer range invalid!\n"));
        return EFI_SUCCESS;
      }

      Status = mSmmSpiProtocol->FlashReadJedecId (
                                  mSmmSpiProtocol,
                                  SmmSpiFlashReadJedecId->ComponentNumber,
                                  SmmSpiFlashReadJedecId->ByteCount,
                                  SmmSpiFlashReadJedecId->JedecId
                                  );
      break;

    case SPI_FUNCTION_FLASH_WRITE_STATUS:
      if (CommBufferPayloadSize < sizeof (SMM_SPI_FLASH_WRITE_STATUS)) {
        DEBUG ((DEBUG_ERROR, "FlashWriteStatus: SMM communication buffer size invalid!\n"));
        return EFI_SUCCESS;
      }
      SmmSpiFlashWriteStatus = (SMM_SPI_FLASH_WRITE_STATUS *) SmmSpiFunctionHeader->Data;
      //
      // Check buffer range is valid
      //
      if (((SmmSpiFlashWriteStatus->StatusValue) != (UINT8 *)(SmmSpiFlashWriteStatus + 1)) ||
          ((SmmSpiFlashWriteStatus->StatusValue + SmmSpiFlashWriteStatus->ByteCount) > (SmmSpiFunctionHeader->Data + CommBufferPayloadSize)))
      {
        DEBUG ((DEBUG_ERROR, "FlashWriteStatus: SMM communication buffer range invalid!\n"));
        return EFI_SUCCESS;
      }

      Status = mSmmSpiProtocol->FlashWriteStatus (
                                  mSmmSpiProtocol,
                                  SmmSpiFlashWriteStatus->ByteCount,
                                  SmmSpiFlashWriteStatus->StatusValue
                                  );
      break;

    case SPI_FUNCTION_FLASH_READ_STATUS:
      if (CommBufferPayloadSize < sizeof (SMM_SPI_FLASH_READ_STATUS)) {
        DEBUG ((DEBUG_ERROR, "FlashReadStatus: SMM communication buffer size invalid!\n"));
        return EFI_SUCCESS;
      }
      SmmSpiFlashReadStatus = (SMM_SPI_FLASH_READ_STATUS *) SmmSpiFunctionHeader->Data;
      //
      // Check buffer range is valid
      //
      if (((SmmSpiFlashReadStatus->StatusValue) != (UINT8 *)(SmmSpiFlashReadStatus + 1)) ||
          ((SmmSpiFlashReadStatus->StatusValue + SmmSpiFlashReadStatus->ByteCount) > (SmmSpiFunctionHeader->Data + CommBufferPayloadSize)))
      {
        DEBUG ((DEBUG_ERROR, "FlashReadStatus: SMM communication buffer range invalid!\n"));
        return EFI_SUCCESS;
      }

      Status = mSmmSpiProtocol->FlashReadStatus (
                                  mSmmSpiProtocol,
                                  SmmSpiFlashReadStatus->ByteCount,
                                  SmmSpiFlashReadStatus->StatusValue
                                  );
      break;

    case SPI_FUNCTION_GET_REGION_ADDRESS:
      if (CommBufferPayloadSize < sizeof (SMM_SPI_GET_REGION_ADDRESS)) {
        DEBUG ((DEBUG_ERROR, "GetRegionAddress: SMM communication buffer size invalid!\n"));
        return EFI_SUCCESS;
      }
      SmmSpiGetRegionAddress = (SMM_SPI_GET_REGION_ADDRESS *) SmmSpiFunctionHeader->Data;
      //
      // Check buffer range is valid
      //
      if (((SmmSpiGetRegionAddress->BaseAddress) != (UINT32 *)(SmmSpiGetRegionAddress + 1)) ||
          ((SmmSpiGetRegionAddress->RegionSize) != ((UINT32 *)(SmmSpiGetRegionAddress + 1) + 1)))
      {
        DEBUG ((DEBUG_ERROR, "GetRegionAddress: SMM communication buffer range invalid!\n"));
        return EFI_SUCCESS;
      }

      Status = mSmmSpiProtocol->GetRegionAddress (
                                  mSmmSpiProtocol,
                                  SmmSpiGetRegionAddress->FlashRegionType,
                                  SmmSpiGetRegionAddress->BaseAddress,
                                  SmmSpiGetRegionAddress->RegionSize
                                  );
      break;

    case SPI_FUNCTION_READ_PCH_SOFTSTRAP:
      if (CommBufferPayloadSize < sizeof (SMM_SPI_READ_PCH_SOFTSTRAP)) {
        DEBUG ((DEBUG_ERROR, "ReadPchSoftStrap: SMM communication buffer size invalid!\n"));
        return EFI_SUCCESS;
      }
      SmmSpiReadPchSoftStrap = (SMM_SPI_READ_PCH_SOFTSTRAP *) SmmSpiFunctionHeader->Data;
      //
      // Check buffer range is valid
      //
      if ((((UINT8 *)SmmSpiReadPchSoftStrap->SoftStrapValue) != (UINT8 *)(SmmSpiReadPchSoftStrap + 1)) ||
          (((UINT8 *)SmmSpiReadPchSoftStrap->SoftStrapValue + SmmSpiReadPchSoftStrap->ByteCount) > (SmmSpiFunctionHeader->Data + CommBufferPayloadSize)))
      {
        DEBUG ((DEBUG_ERROR, "ReadPchSoftStrap: SMM communication buffer range invalid!\n"));
        return EFI_SUCCESS;
      }

      Status = mSmmSpiProtocol->ReadPchSoftStrap (
                                  mSmmSpiProtocol,
                                  SmmSpiReadPchSoftStrap->SoftStrapAddr,
                                  SmmSpiReadPchSoftStrap->ByteCount,
                                  SmmSpiReadPchSoftStrap->SoftStrapValue
                                  );
      break;

    case SPI_FUNCTION_READ_CPU_SOFTSTRAP:
      if (CommBufferPayloadSize < sizeof (SMM_SPI_READ_CPU_SOFTSTRAP)) {
        DEBUG ((DEBUG_ERROR, "ReadCpuSoftStrap: SMM communication buffer size invalid!\n"));
        return EFI_SUCCESS;
      }
      SmmSpiReadCpuSoftStrap = (SMM_SPI_READ_CPU_SOFTSTRAP *) SmmSpiFunctionHeader->Data;
      //
      // Check buffer range is valid
      //
      if ((((UINT8 *)SmmSpiReadCpuSoftStrap->SoftStrapValue) != (UINT8 *)(SmmSpiReadCpuSoftStrap + 1)) ||
          (((UINT8 *)SmmSpiReadCpuSoftStrap->SoftStrapValue + SmmSpiReadCpuSoftStrap->ByteCount) > (SmmSpiFunctionHeader->Data + CommBufferPayloadSize)))
      {
        DEBUG ((DEBUG_ERROR, "ReadCpuSoftStrap: SMM communication buffer range invalid!\n"));
        return EFI_SUCCESS;
      }

      Status = mSmmSpiProtocol->ReadCpuSoftStrap (
                                  mSmmSpiProtocol,
                                  SmmSpiReadCpuSoftStrap->SoftStrapAddr,
                                  SmmSpiReadCpuSoftStrap->ByteCount,
                                  SmmSpiReadCpuSoftStrap->SoftStrapValue
                                  );
      break;

    default:
      Status = EFI_UNSUPPORTED;
  }

  SmmSpiFunctionHeader->ReturnStatus = Status;

  return EFI_SUCCESS;
}

/**
  SMM END_OF_DXE protocol notification event handler.

  @param  Protocol   Points to the protocol's unique identifier
  @param  Interface  Points to the interface instance
  @param  Handle     The handle on which the interface was installed

  @retval EFI_SUCCESS   SmmEndOfDxeCallback runs successfully

**/
EFI_STATUS
EFIAPI
SmmEndOfDxeCallback (
  IN CONST EFI_GUID                       *Protocol,
  IN VOID                                 *Interface,
  IN EFI_HANDLE                           Handle
  )
{
  mEndOfDxe = TRUE;

  return EFI_SUCCESS;
}

/**
  SPI SMM Module Entry Point.

  @param[in] ImageHandle          Image handle of this driver.
  @param[in] SystemTable          Global system service table.

  @retval EFI_SUCCESS             Initialization complete.
  @exception EFI_UNSUPPORTED      The chipset is unsupported by this driver.
  @retval EFI_OUT_OF_RESOURCES    Do not have enough resources to initialize the driver.
  @retval EFI_DEVICE_ERROR        Device error, driver exits abnormally.
**/
EFI_STATUS
EFIAPI
InstallSpiSmmStub (
  IN EFI_HANDLE            ImageHandle,
  IN EFI_SYSTEM_TABLE      *SystemTable
  )
{
  EFI_STATUS                      Status;
  VOID                            *SmmEndOfDxeRegistration;

  DEBUG ((DEBUG_INFO, "InstallSpiSmmStub() Start\n"));

  Status = gSmst->SmmLocateProtocol (&gPchSmmSpiProtocolGuid, NULL, (VOID **) &mSmmSpiProtocol);
  ASSERT_EFI_ERROR (Status);

  ///
  /// Register SMM SPI SMI handler
  ///
  Status = gSmst->SmiHandlerRegister (SmmSpiHandler, &gPchSmmSpiProtocolGuid, &mSmmSpiHandle);
  ASSERT_EFI_ERROR (Status);

  //
  // Register EFI_SMM_END_OF_DXE_PROTOCOL_GUID notify function.
  //
  Status = gSmst->SmmRegisterProtocolNotify (
                    &gEfiSmmEndOfDxeProtocolGuid,
                    SmmEndOfDxeCallback,
                    &SmmEndOfDxeRegistration
                    );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((DEBUG_INFO, "InstallSpiSmmStub() End\n"));

  return EFI_SUCCESS;
}

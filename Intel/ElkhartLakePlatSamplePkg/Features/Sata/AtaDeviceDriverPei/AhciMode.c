/** @file
  The file for AHCI mode of ATA host controller.

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

#include "AtaPassThruPei.h"

EFI_ATA_COLLECTIVE_MODE  mSupportedModes = {
  {
    TRUE,                   ///< PioMode.Valid
    0                       ///< PioMode.Mode
  },
  {
    TRUE,                   ///< SingleWordDmaMode.Valid
    0
  },
  {
    FALSE,                  ///< MultiWordDmaMode.Valid
    0
  },
  {
    TRUE,                   ///< UdmaMode.Valid
    0                       ///< UdmaMode.Mode
  }
};

/**
  Read AHCI Operation register.

  @param  Offset       The operation register offset.

  @return The register content read.

**/
UINT32
EFIAPI
AhciReadReg (
  IN  UINT32              Offset
  )
{
  UINT32                  Data;

  Data = 0;
  Data = MmioRead32 (mAhciBar + Offset);
  return Data;
}

/**
  Write AHCI Operation register.

  @param  Offset       The operation register offset.
  @param  Data         The data used to write down.

**/
VOID
EFIAPI
AhciWriteReg (
  IN UINT32               Offset,
  IN UINT32               Data
  )
{
  MmioWrite32 (mAhciBar + Offset, Data);
  return ;
}

/**
  Do AND operation with the value of AHCI Operation register.

  @param  Offset       The operation register offset.
  @param  AndData      The data used to do AND operation.

**/
VOID
EFIAPI
AhciAndReg (
  IN UINT32               Offset,
  IN UINT32               AndData
  )
{
  UINT32 Data;

  Data  = AhciReadReg (Offset);
  Data &= AndData;

  AhciWriteReg (Offset, Data);
}

/**
  Do OR operation with the value of AHCI Operation register.

  @param  Offset       The operation register offset.
  @param  OrData       The data used to do OR operation.

**/
VOID
EFIAPI
AhciOrReg (
  IN UINT32               Offset,
  IN UINT32               OrData
  )
{
  UINT32 Data;

  Data  = AhciReadReg (Offset);
  Data |= OrData;

  AhciWriteReg (Offset, Data);
}

/**
  Wait for the value of the specified MMIO register set to the test value.

  @param  Offset            The MMIO address to test.
  @param  MaskValue         The mask value of memory.
  @param  TestValue         The test value of memory.
  @param  Timeout           The time out value for wait memory set, uses 100ns as a unit.

  @retval EFI_TIMEOUT       The MMIO setting is time out.
  @retval EFI_SUCCESS       The MMIO is correct set.

**/
EFI_STATUS
EFIAPI
AhciWaitMmioSet (
  IN  UINTN                     Offset,
  IN  UINT32                    MaskValue,
  IN  UINT32                    TestValue,
  IN  UINT64                    Timeout
  )
{
  UINT32     Value;
  UINT64     Delay;
  BOOLEAN    InfiniteWait;

  if (Timeout == 0) {
    InfiniteWait = TRUE;
  } else {
    InfiniteWait = FALSE;
  }

  Delay = DivU64x32 (Timeout, 1000) + 1;

  do {
    //
    // Access PCI MMIO space to see if the value is the tested one.
    //
    Value = AhciReadReg ((UINT32) Offset) & MaskValue;

    if (Value == TestValue) {
      return EFI_SUCCESS;
    }

    //
    // Stall for 100 microseconds.
    //
    MicroSecondDelay (100);

    Delay--;

  } while (InfiniteWait || (Delay > 0));

  return EFI_TIMEOUT;
}

/**
  Wait for the value of the specified system memory set to the test value.

  @param  Address           The system memory address to test.
  @param  MaskValue         The mask value of memory.
  @param  TestValue         The test value of memory.
  @param  Timeout           The time out value for wait memory set, uses 100ns as a unit.

  @retval EFI_TIMEOUT       The system memory setting is time out.
  @retval EFI_SUCCESS       The system memory is correct set.

**/
EFI_STATUS
EFIAPI
AhciWaitMemSet (
  IN  EFI_PHYSICAL_ADDRESS      Address,
  IN  UINT32                    MaskValue,
  IN  UINT32                    TestValue,
  IN  UINT64                    Timeout
  )
{
  UINT32     Value;
  UINT64     Delay;
  BOOLEAN    InfiniteWait;

  if (Timeout == 0) {
    InfiniteWait = TRUE;
  } else {
    InfiniteWait = FALSE;
  }

  Delay =  DivU64x32 (Timeout, 1000) + 1;

  do {
    //
    // Access sytem memory to see if the value is the tested one.
    //
    // The system memory pointed by Address will be updated by the
    // SATA Host Controller, "volatile" is introduced to prevent
    // compiler from optimizing the access to the memory address
    // to only read once.
    //
    Value  = *(volatile UINT32 *) (UINTN) Address;
    Value &= MaskValue;

    if (Value == TestValue) {
      return EFI_SUCCESS;
    }

    //
    // Stall for 100 microseconds.
    //
    MicroSecondDelay (100);

    Delay--;

  } while (InfiniteWait || (Delay > 0));

  return EFI_TIMEOUT;
}

/**
  Check the memory status to the test value.

  @param[in]       Address           The memory address to test.
  @param[in]       MaskValue         The mask value of memory.
  @param[in]       TestValue         The test value of memory.
  @param[in, out]  Task              Optional. Pointer to the ATA_NONBLOCK_TASK used by
                                     non-blocking mode. If NULL, then just try once.

  @retval EFI_NOTREADY      The memory is not set.
  @retval EFI_TIMEOUT       The memory setting retry times out.
  @retval EFI_SUCCESS       The memory is correct set.

**/
EFI_STATUS
EFIAPI
AhciCheckMemSet (
  IN     UINTN                     Address,
  IN     UINT32                    MaskValue,
  IN     UINT32                    TestValue,
  IN OUT ATA_NONBLOCK_TASK         *Task
  )
{
  UINT32     Value;

  if (Task != NULL) {
    Task->RetryTimes--;
  }

  Value  = *(volatile UINT32 *) Address;
  Value &= MaskValue;

  if (Value == TestValue) {
    return EFI_SUCCESS;
  }

  if ((Task != NULL) && !Task->InfiniteWait && (Task->RetryTimes == 0)) {
    return EFI_TIMEOUT;
  } else {
    return EFI_NOT_READY;
  }
}

/**
  Check if the device is still on port. It also checks if the AHCI controller
  supports the address and data count will be transferred.

  @param  Port             The number of port.

  @retval EFI_SUCCESS      The device is attached to port and the transfer data is
                           supported by AHCI controller.
  @retval EFI_UNSUPPORTED  The transfer address and count is not supported by AHCI
                           controller.
  @retval EFI_NOT_READY    The physical communication between AHCI controller and device
                           is not ready.

**/
EFI_STATUS
EFIAPI
AhciCheckDeviceStatus (
  IN  UINT8                  Port
  )
{
  UINT32      Data;
  UINT32      Offset;

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SSTS;

  Data   = AhciReadReg (Offset) & EFI_AHCI_PORT_SSTS_DET_MASK;

  if (Data == EFI_AHCI_PORT_SSTS_DET_PCE) {
    return EFI_SUCCESS;
  }

  return EFI_NOT_READY;
}

/**

  Clear the port interrupt and error status. It will also clear
  HBA interrupt status.

  @param      Port           The number of port.

**/
VOID
EFIAPI
AhciClearPortStatus (
  IN  UINT8                  Port
  )
{
  UINT32 Offset;

  //
  // Clear any error status
  //
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SERR;
  AhciWriteReg (Offset, AhciReadReg (Offset));

  //
  // Clear any port interrupt status
  //
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_IS;
  AhciWriteReg (Offset, AhciReadReg (Offset));

  //
  // Clear any HBA interrupt status
  //
  AhciWriteReg (EFI_AHCI_IS_OFFSET, AhciReadReg (EFI_AHCI_IS_OFFSET));
}

/**
  This function is used to dump the Status Registers and if there is ERR bit set
  in the Status Register, the Error Register's value is also be dumped.

  @param  AhciRegisters    The pointer to the EFI_AHCI_REGISTERS.
  @param  Port             The number of port.
  @param  AtaStatusBlock   A pointer to EFI_ATA_STATUS_BLOCK data structure.

**/
VOID
EFIAPI
AhciDumpPortStatus (
  IN     EFI_AHCI_REGISTERS         *AhciRegisters,
  IN     UINT8                      Port,
  IN OUT EFI_ATA_STATUS_BLOCK       *AtaStatusBlock
  )
{
  UINTN                Offset;
  UINT32               Data;
  UINTN                FisBaseAddr;
  EFI_STATUS           Status;

  if (AtaStatusBlock != NULL) {
    ZeroMem (AtaStatusBlock, sizeof (EFI_ATA_STATUS_BLOCK));

    FisBaseAddr = (UINTN)AhciRegisters->AhciRFis + Port * sizeof (EFI_AHCI_RECEIVED_FIS);
    Offset      = FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET;

    Status = AhciCheckMemSet (Offset, EFI_AHCI_FIS_TYPE_MASK, EFI_AHCI_FIS_REGISTER_D2H, NULL);
    if (!EFI_ERROR (Status)) {
      //
      // If D2H FIS is received, update StatusBlock with its content.
      //
      CopyMem (AtaStatusBlock, (UINT8 *)Offset, sizeof (EFI_ATA_STATUS_BLOCK));
    } else {
      //
      // If D2H FIS is not received, only update Status & Error field through PxTFD
      // as there is no other way to get the content of the Shadow Register Block.
      //
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
      Data   = AhciReadReg ((UINT32)Offset);

      AtaStatusBlock->AtaStatus  = (UINT8)Data;
      if ((AtaStatusBlock->AtaStatus & BIT0) != 0) {
        AtaStatusBlock->AtaError = (UINT8)(Data >> 8);
      }
    }
  }
}

/**
  Enable the FIS running for giving port.

  @param      Port           The number of port.
  @param      Timeout        The timeout value of enabling FIS, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   The FIS enable setting fails.
  @retval EFI_TIMEOUT        The FIS enable setting is time out.
  @retval EFI_SUCCESS        The FIS enable successfully.

**/
EFI_STATUS
EFIAPI
AhciEnableFisReceive (
  IN  UINT8                     Port,
  IN  UINT64                    Timeout
  )
{
  UINT32 Offset;

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  AhciOrReg (Offset, EFI_AHCI_PORT_CMD_FRE);

  //return EFI_SUCCESS;
  return AhciWaitMmioSet (
           Offset,
           EFI_AHCI_PORT_CMD_FR,
           EFI_AHCI_PORT_CMD_FR,
           Timeout
           );
}

/**
  Disable the FIS running for giving port.

  @param      Port           The number of port.
  @param      Timeout        The timeout value of disabling FIS, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   The FIS disable setting fails.
  @retval EFI_TIMEOUT        The FIS disable setting is time out.
  @retval EFI_UNSUPPORTED    The port is in running state.
  @retval EFI_SUCCESS        The FIS disable successfully.

**/
EFI_STATUS
EFIAPI
AhciDisableFisReceive (
  IN  UINT8                     Port,
  IN  UINT64                    Timeout
  )
{
  UINT32 Offset;
  UINT32 Data;

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  Data   = AhciReadReg (Offset);

  //
  // Before disabling Fis receive, the DMA engine of the port should NOT be in running status.
  //
  if ((Data & (EFI_AHCI_PORT_CMD_ST | EFI_AHCI_PORT_CMD_CR)) != 0) {
    return EFI_UNSUPPORTED;
  }

  //
  // Check if the Fis receive DMA engine for the port is running.
  //
  if ((Data & EFI_AHCI_PORT_CMD_FR) != EFI_AHCI_PORT_CMD_FR) {
    return EFI_SUCCESS;
  }

  AhciAndReg (Offset, (UINT32)~(EFI_AHCI_PORT_CMD_FRE));

  return AhciWaitMmioSet (
           Offset,
           EFI_AHCI_PORT_CMD_FR,
           0,
           Timeout
           );
}

/**
  Build the command list, command table and prepare the fis receiver.

  @param    AhciRegisters         The pointer to the EFI_AHCI_REGISTERS.
  @param    Port                  The number of port.
  @param    PortMultiplier        The timeout value of stop.
  @param    CommandFis            The control fis will be used for the transfer.
  @param    CommandList           The command list will be used for the transfer.
  @param    AtapiCommand          The atapi command will be used for the transfer.
  @param    AtapiCommandLength    The length of the atapi command.
  @param    CommandSlotNumber     The command slot will be used for the transfer.
  @param    DataPhysicalAddr      The pointer to the data buffer pci bus master address.
  @param    DataLength            The data count to be transferred.

**/
VOID
EFIAPI
AhciBuildCommand (
  IN     EFI_AHCI_REGISTERS         *AhciRegisters,
  IN     UINT8                      Port,
  IN     UINT8                      PortMultiplier,
  IN     EFI_AHCI_COMMAND_FIS       *CommandFis,
  IN     EFI_AHCI_COMMAND_LIST      *CommandList,
  IN     EFI_AHCI_ATAPI_COMMAND     *AtapiCommand OPTIONAL,
  IN     UINT8                      AtapiCommandLength,
  IN     UINT8                      CommandSlotNumber,
  IN OUT VOID                       *DataPhysicalAddr,
  IN     UINT32                     DataLength
  )
{
  UINT64     BaseAddr;
  UINT32     PrdtNumber;
  UINT32     PrdtIndex;
  UINTN      RemainedData;
  UINTN      MemAddr;
  DATA_64    Data64;
  UINT32     Offset;

  //
  // Filling the PRDT
  //
  PrdtNumber = (UINT32)DivU64x32 (((UINT64)DataLength + EFI_AHCI_MAX_DATA_PER_PRDT - 1), EFI_AHCI_MAX_DATA_PER_PRDT);

  //
  // According to AHCI 1.3 spec, a PRDT entry can point to a maximum 4MB data block.
  // It also limits that the maximum amount of the PRDT entry in the command table
  // is 65535.
  //
  ASSERT (PrdtNumber <= 65535);

  Data64.Uint64 = (UINTN) (AhciRegisters->AhciRFis) + sizeof (EFI_AHCI_RECEIVED_FIS) * Port;

  BaseAddr = Data64.Uint64;

  ZeroMem ((VOID *)((UINTN) BaseAddr), sizeof (EFI_AHCI_RECEIVED_FIS));

  ZeroMem (AhciRegisters->AhciCommandTable, sizeof (EFI_AHCI_COMMAND_TABLE));

  CommandFis->AhciCFisPmNum = PortMultiplier;

  CopyMem (&AhciRegisters->AhciCommandTable->CommandFis, CommandFis, sizeof (EFI_AHCI_COMMAND_FIS));

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  if (AtapiCommand != NULL) {
    CopyMem (
      &AhciRegisters->AhciCommandTable->AtapiCmd,
      AtapiCommand,
      AtapiCommandLength
      );

    CommandList->AhciCmdA = 1;
    CommandList->AhciCmdP = 1;

    AhciOrReg (Offset, (EFI_AHCI_PORT_CMD_DLAE | EFI_AHCI_PORT_CMD_ATAPI));
  } else {
    AhciAndReg (Offset, (UINT32)~(EFI_AHCI_PORT_CMD_DLAE | EFI_AHCI_PORT_CMD_ATAPI));
  }

  RemainedData = (UINTN) DataLength;
  MemAddr      = (UINTN) DataPhysicalAddr;
  CommandList->AhciCmdPrdtl = PrdtNumber;

  for (PrdtIndex = 0; PrdtIndex < PrdtNumber; PrdtIndex++) {
    if (RemainedData < EFI_AHCI_MAX_DATA_PER_PRDT) {
      AhciRegisters->AhciCommandTable->PrdtTable[PrdtIndex].AhciPrdtDbc = (UINT32)RemainedData - 1;
    } else {
      AhciRegisters->AhciCommandTable->PrdtTable[PrdtIndex].AhciPrdtDbc = EFI_AHCI_MAX_DATA_PER_PRDT - 1;
    }

    Data64.Uint64 = (UINT64)MemAddr;
    AhciRegisters->AhciCommandTable->PrdtTable[PrdtIndex].AhciPrdtDba  = Data64.Uint32.Lower32;
    AhciRegisters->AhciCommandTable->PrdtTable[PrdtIndex].AhciPrdtDbau = Data64.Uint32.Upper32;
    RemainedData -= EFI_AHCI_MAX_DATA_PER_PRDT;
    MemAddr      += EFI_AHCI_MAX_DATA_PER_PRDT;
  }

  //
  // Set the last PRDT to Interrupt On Complete
  //
  if (PrdtNumber > 0) {
    AhciRegisters->AhciCommandTable->PrdtTable[PrdtNumber - 1].AhciPrdtIoc = 1;
  }

  CopyMem (
    (VOID *) ((UINTN) AhciRegisters->AhciCmdList + (UINTN) CommandSlotNumber * sizeof (EFI_AHCI_COMMAND_LIST)),
    CommandList,
    sizeof (EFI_AHCI_COMMAND_LIST)
    );

  Data64.Uint64 = (UINT64)(UINTN) AhciRegisters->AhciCommandTable;
  AhciRegisters->AhciCmdList[CommandSlotNumber].AhciCmdCtba  = Data64.Uint32.Lower32;
  AhciRegisters->AhciCmdList[CommandSlotNumber].AhciCmdCtbau = Data64.Uint32.Upper32;
  AhciRegisters->AhciCmdList[CommandSlotNumber].AhciCmdPmp   = PortMultiplier;

}

/**
  Buid a command FIS.

  @param  CmdFis            A pointer to the EFI_AHCI_COMMAND_FIS data structure.
  @param  AtaCommandBlock   A pointer to the AhciBuildCommandFis data structure.

**/
VOID
EFIAPI
AhciBuildCommandFis (
  IN OUT EFI_AHCI_COMMAND_FIS    *CmdFis,
  IN     EFI_ATA_COMMAND_BLOCK   *AtaCommandBlock
  )
{
  ZeroMem (CmdFis, sizeof (EFI_AHCI_COMMAND_FIS));

  CmdFis->AhciCFisType = EFI_AHCI_FIS_REGISTER_H2D;
  //
  // Indicator it's a command
  //
  CmdFis->AhciCFisCmdInd      = 0x1;
  CmdFis->AhciCFisCmd         = AtaCommandBlock->AtaCommand;

  CmdFis->AhciCFisFeature     = AtaCommandBlock->AtaFeatures;
  CmdFis->AhciCFisFeatureExp  = AtaCommandBlock->AtaFeaturesExp;

  CmdFis->AhciCFisSecNum      = AtaCommandBlock->AtaSectorNumber;
  CmdFis->AhciCFisSecNumExp   = AtaCommandBlock->AtaSectorNumberExp;

  CmdFis->AhciCFisClyLow      = AtaCommandBlock->AtaCylinderLow;
  CmdFis->AhciCFisClyLowExp   = AtaCommandBlock->AtaCylinderLowExp;

  CmdFis->AhciCFisClyHigh     = AtaCommandBlock->AtaCylinderHigh;
  CmdFis->AhciCFisClyHighExp  = AtaCommandBlock->AtaCylinderHighExp;

  CmdFis->AhciCFisSecCount    = AtaCommandBlock->AtaSectorCount;
  CmdFis->AhciCFisSecCountExp = AtaCommandBlock->AtaSectorCountExp;

  CmdFis->AhciCFisDevHead     = (UINT8) (AtaCommandBlock->AtaDeviceHead | 0xE0);
}

/**
  Start a PIO data transfer on specific port.

  @param[in]       AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param[in]       Port                The number of port.
  @param[in]       PortMultiplier      The timeout value of stop.
  @param[in]       AtapiCommand        The atapi command will be used for the
                                       transfer.
  @param[in]       AtapiCommandLength  The length of the atapi command.
  @param[in]       Read                The transfer direction.
  @param[in]       AtaCommandBlock     The EFI_ATA_COMMAND_BLOCK data.
  @param[in, out]  AtaStatusBlock      The EFI_ATA_STATUS_BLOCK data.
  @param[in, out]  MemoryAddr          The pointer to the data buffer.
  @param[in]       DataCount           The data count to be transferred.
  @param[in]       Timeout             The timeout value of non data transfer, uses 100ns as a unit.
  @param[in]       Task                Optional. Pointer to the ATA_NONBLOCK_TASK
                                       used by non-blocking mode.

  @retval EFI_DEVICE_ERROR    The PIO data transfer abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for transfer.
  @retval EFI_SUCCESS         The PIO data transfer executes successfully.

**/
EFI_STATUS
EFIAPI
AhciPioTransfer (
  IN     EFI_AHCI_REGISTERS         *AhciRegisters,
  IN     UINT8                      Port,
  IN     UINT8                      PortMultiplier,
  IN     EFI_AHCI_ATAPI_COMMAND     *AtapiCommand OPTIONAL,
  IN     UINT8                      AtapiCommandLength,
  IN     BOOLEAN                    Read,
  IN     EFI_ATA_COMMAND_BLOCK      *AtaCommandBlock,
  IN OUT EFI_ATA_STATUS_BLOCK       *AtaStatusBlock,
  IN OUT VOID                       *MemoryAddr,
  IN     UINT32                     DataCount,
  IN     UINT64                     Timeout
  )
{
  EFI_STATUS                    Status;
  UINTN                         FisBaseAddr;
  UINTN                         Offset;
  UINT64                        Delay;
  DATA_64                       Data64;
  EFI_AHCI_COMMAND_FIS          CFis;
  EFI_AHCI_COMMAND_LIST         CmdList;
  UINT32                        PortTfd;
  UINT32                        PrdCount;
  UINT32                        OldRfisLo;
  UINT32                        OldRfisHi;
  UINT32                        OldCmdListLo;
  UINT32                        OldCmdListHi;
  BOOLEAN                       InfiniteWait;
  BOOLEAN                       PioFisReceived;
  BOOLEAN                       D2hFisReceived;

  if (Timeout == 0) {
    InfiniteWait = TRUE;
  } else {
    InfiniteWait = FALSE;
  }

  //InfiniteWait = TRUE;

  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FB;
  OldRfisLo = AhciReadReg (Offset);
  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FBU;
  OldRfisHi = AhciReadReg (Offset);

  Data64.Uint64 = (UINTN) (AhciRegisters->AhciRFis) + sizeof (EFI_AHCI_RECEIVED_FIS) * Port;
  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FB;
  AhciWriteReg (Offset, Data64.Uint32.Lower32);
  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FBU;
  AhciWriteReg (Offset, Data64.Uint32.Upper32);

  //
  // Single task envrionment, we only use one command table for all port
  //
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLB;
  OldCmdListLo = AhciReadReg (Offset);
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLBU;
  OldCmdListHi = AhciReadReg (Offset);

  Data64.Uint64 = (UINTN) (AhciRegisters->AhciCmdList);
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLB;
  AhciWriteReg (Offset, Data64.Uint32.Lower32);
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLBU;
  AhciWriteReg (Offset, Data64.Uint32.Upper32);

  //
  // Package read needed
  //
  AhciBuildCommandFis (&CFis, AtaCommandBlock);

  ZeroMem (&CmdList, sizeof (EFI_AHCI_COMMAND_LIST));

  CmdList.AhciCmdCfl = EFI_AHCI_FIS_REGISTER_H2D_LENGTH / 4;
  CmdList.AhciCmdW   = Read ? 0 : 1;

  AhciBuildCommand (
    AhciRegisters,
    Port,
    PortMultiplier,
    &CFis,
    &CmdList,
    AtapiCommand,
    AtapiCommandLength,
    0,
    (VOID *)(UINTN)MemoryAddr,
    DataCount
    );

  Status = AhciStartCommand (
             Port,
             0,
             Timeout
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "  AhciPioTransfer: AhciStartCommand failed (%r)\n", Status));
    goto Exit;
  }

  //
  // Check the status and wait the driver sending data
  //
  FisBaseAddr = (UINTN)AhciRegisters->AhciRFis + Port * sizeof (EFI_AHCI_RECEIVED_FIS);

  if (Read && (AtapiCommand == 0)) {
    //
    // Wait device sends the PIO setup fis before data transfer
    //
    Status = EFI_TIMEOUT;
    Delay  = DivU64x32 (Timeout, 1000) + 1;
    do {
      PioFisReceived = FALSE;
      D2hFisReceived = FALSE;
      Offset = FisBaseAddr + EFI_AHCI_PIO_FIS_OFFSET;
      Status = AhciCheckMemSet (Offset, EFI_AHCI_FIS_TYPE_MASK, EFI_AHCI_FIS_PIO_SETUP, NULL);
      if (!EFI_ERROR (Status)) {
        DEBUG ((EFI_D_INFO, "    AhciPioTransfer: PioFisReceived\n"));
        PioFisReceived = TRUE;
      }
      //
      // According to SATA 2.6 spec section 11.7, D2h FIS means an error encountered.
      // But Qemu and Marvel 9230 sata controller may just receive a D2h FIS from device
      // after the transaction is finished successfully.
      // To get better device compatibilities, we further check if the PxTFD's ERR bit is set.
      // By this way, we can know if there is a real error happened.
      //
      Offset = FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET;
      Status = AhciCheckMemSet (Offset, EFI_AHCI_FIS_TYPE_MASK, EFI_AHCI_FIS_REGISTER_D2H, NULL);
      if (!EFI_ERROR (Status)) {
        DEBUG ((EFI_D_INFO, "    AhciPioTransfer: D2hFisReceived\n"));
        D2hFisReceived = TRUE;
      }

      if (PioFisReceived || D2hFisReceived) {
        Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
        PortTfd = AhciReadReg ((UINT32) Offset);
        //
        // PxTFD will be updated if there is a D2H or SetupFIS received.
        //
        if ((PortTfd & EFI_AHCI_PORT_TFD_ERR) != 0) {
          Status = EFI_DEVICE_ERROR;
          break;
        }

        PrdCount = *(volatile UINT32 *) (&(AhciRegisters->AhciCmdList[0].AhciCmdPrdbc));
        if (PrdCount == DataCount) {
          Status = EFI_SUCCESS;
          break;
        }
      }

      //
      // Stall for 100 microseconds.
      //
      MicroSecondDelay(100);

      Delay--;
      if (Delay == 0) {
        Status = EFI_TIMEOUT;
      }
    } while (InfiniteWait || (Delay > 0));
  } else {
    //
    // Wait for D2H Fis is received
    //
    Offset = FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET;
    Status = AhciWaitMemSet (
               Offset,
               EFI_AHCI_FIS_TYPE_MASK,
               EFI_AHCI_FIS_REGISTER_D2H,
               Timeout
               );

    if (EFI_ERROR (Status)) {
      DEBUG ((EFI_D_ERROR, "  AhciPioTransfer: AhciWaitMemSet (%r)\n", Status));
      goto Exit;
    }

    Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
    PortTfd = AhciReadReg ((UINT32) Offset);
    if ((PortTfd & EFI_AHCI_PORT_TFD_ERR) != 0) {
      Status = EFI_DEVICE_ERROR;
    }
  }

Exit:
  AhciStopCommand (
    Port,
    Timeout
    );

  AhciDisableFisReceive (
    Port,
    Timeout
    );

  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FB;
  AhciWriteReg (Offset, OldRfisLo);
  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FBU;
  AhciWriteReg (Offset, OldRfisHi);

  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLB;
  AhciWriteReg (Offset, OldCmdListLo);
  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLBU;
  AhciWriteReg (Offset, OldCmdListHi);

  AhciDumpPortStatus (AhciRegisters, Port, AtaStatusBlock);

  return Status;
}

/**
  Start a DMA data transfer on specific port

  @param[in]       Instance            The ATA_ATAPI_PASS_THRU_INSTANCE protocol instance.
  @param[in]       AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param[in]       Port                The number of port.
  @param[in]       PortMultiplier      The timeout value of stop.
  @param[in]       AtapiCommand        The atapi command will be used for the
                                       transfer.
  @param[in]       AtapiCommandLength  The length of the atapi command.
  @param[in]       Read                The transfer direction.
  @param[in]       AtaCommandBlock     The EFI_ATA_COMMAND_BLOCK data.
  @param[in, out]  AtaStatusBlock      The EFI_ATA_STATUS_BLOCK data.
  @param[in, out]  MemoryAddr          The pointer to the data buffer.
  @param[in]       DataCount           The data count to be transferred.
  @param[in]       Timeout             The timeout value of non data transfer, uses 100ns as a unit.
  @param[in]       Task                Optional. Pointer to the ATA_NONBLOCK_TASK
                                       used by non-blocking mode.

  @retval EFI_DEVICE_ERROR    The DMA data transfer abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for transfer.
  @retval EFI_SUCCESS         The DMA data transfer executes successfully.

**/
EFI_STATUS
EFIAPI
AhciDmaTransfer (
  IN     PEI_ATA_PASS_THRU_INSTANCE *Instance,
  IN     EFI_AHCI_REGISTERS         *AhciRegisters,
  IN     UINT8                      Port,
  IN     UINT8                      PortMultiplier,
  IN     EFI_AHCI_ATAPI_COMMAND     *AtapiCommand OPTIONAL,
  IN     UINT8                      AtapiCommandLength,
  IN     BOOLEAN                    Read,
  IN     EFI_ATA_COMMAND_BLOCK      *AtaCommandBlock,
  IN OUT EFI_ATA_STATUS_BLOCK       *AtaStatusBlock,
  IN OUT VOID                       *MemoryAddr,
  IN     UINT32                     DataCount,
  IN     UINT64                     Timeout,
  IN     ATA_NONBLOCK_TASK          *Task
  )
{
  EFI_STATUS                    Status;
  UINTN                         Offset;
  EFI_AHCI_COMMAND_FIS          CFis;
  EFI_AHCI_COMMAND_LIST         CmdList;
  UINTN                         FisBaseAddr;
  DATA_64                       Data64;
  UINT32                        PortTfd;
  UINT32                        OldRfisLo;
  UINT32                        OldRfisHi;
  UINT32                        OldCmdListLo;
  UINT32                        OldCmdListHi;



  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FB;
  OldRfisLo = AhciReadReg (Offset);
  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FBU;
  OldRfisHi = AhciReadReg (Offset);

  Data64.Uint64 = (UINTN) (AhciRegisters->AhciRFis) + sizeof (EFI_AHCI_RECEIVED_FIS) * Port;
  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FB;
  AhciWriteReg (Offset, Data64.Uint32.Lower32);
  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FBU;
  AhciWriteReg (Offset, Data64.Uint32.Upper32);

  //
  // Single task envrionment, we only use one command table for all port
  //
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLB;
  OldCmdListLo = AhciReadReg (Offset);
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLBU;
  OldCmdListHi = AhciReadReg (Offset);

  Data64.Uint64 = (UINTN) (AhciRegisters->AhciCmdList);
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLB;
  AhciWriteReg (Offset, Data64.Uint32.Lower32);
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLBU;
  AhciWriteReg (Offset, Data64.Uint32.Upper32);

    //
    // Package read needed
    //
    AhciBuildCommandFis (&CFis, AtaCommandBlock);

    ZeroMem (&CmdList, sizeof (EFI_AHCI_COMMAND_LIST));

    CmdList.AhciCmdCfl = EFI_AHCI_FIS_REGISTER_H2D_LENGTH / 4;
    CmdList.AhciCmdW   = Read ? 0 : 1;

    AhciBuildCommand (
      AhciRegisters,
      Port,
      PortMultiplier,
      &CFis,
      &CmdList,
      AtapiCommand,
      AtapiCommandLength,
      0,
      (VOID *)(UINTN)MemoryAddr,
      DataCount
      );

    Status = AhciStartCommand (
               Port,
               0,
               Timeout
               );
    if (EFI_ERROR (Status)) {
      goto Exit;
    }

  //
  // Wait for command compelte
  //
  FisBaseAddr = (UINTN)AhciRegisters->AhciRFis + Port * sizeof (EFI_AHCI_RECEIVED_FIS);
  Offset      = FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET;
  Status = AhciWaitMemSet (
             Offset,
             EFI_AHCI_FIS_TYPE_MASK,
             EFI_AHCI_FIS_REGISTER_D2H,
             Timeout
             );

  if (EFI_ERROR (Status)) {
    goto Exit;
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
  PortTfd = AhciReadReg ((UINT32) Offset);
  if ((PortTfd & EFI_AHCI_PORT_TFD_ERR) != 0) {
    Status = EFI_DEVICE_ERROR;
  }

Exit:
  //
  // For Blocking mode, the command should be stopped, the Fis should be disabled
  // and the PciIo should be unmapped.
  // For non-blocking mode, only when a error is happened (if the return status is
  // EFI_NOT_READY that means the command doesn't finished, try again.), first do the
  // context cleanup, then set the packet's Asb status.
  //
  AhciStopCommand (
    Port,
    Timeout
    );

  AhciDisableFisReceive (
    Port,
    Timeout
    );

  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FB;
  AhciWriteReg (Offset, OldRfisLo);
  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FBU;
  AhciWriteReg (Offset, OldRfisHi);

  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLB;
  AhciWriteReg (Offset, OldCmdListLo);
  Offset    = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLBU;
  AhciWriteReg (Offset, OldCmdListHi);

  AhciDumpPortStatus (AhciRegisters, Port, AtaStatusBlock);
  return Status;
}

/**
  Start a non data transfer on specific port.

  @param[in]       AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param[in]       Port                The number of port.
  @param[in]       PortMultiplier      The timeout value of stop.
  @param[in]       AtapiCommand        The atapi command will be used for the
                                       transfer.
  @param[in]       AtapiCommandLength  The length of the atapi command.
  @param[in]       AtaCommandBlock     The EFI_ATA_COMMAND_BLOCK data.
  @param[in, out]  AtaStatusBlock      The EFI_ATA_STATUS_BLOCK data.
  @param[in]       Timeout             The timeout value of non data transfer, uses 100ns as a unit.
  @param[in]       Task                Optional. Pointer to the ATA_NONBLOCK_TASK
                                       used by non-blocking mode.

  @retval EFI_DEVICE_ERROR    The non data transfer abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for transfer.
  @retval EFI_SUCCESS         The non data transfer executes successfully.

**/
EFI_STATUS
EFIAPI
AhciNonDataTransfer (
  IN     EFI_AHCI_REGISTERS            *AhciRegisters,
  IN     UINT8                         Port,
  IN     UINT8                         PortMultiplier,
  IN     EFI_AHCI_ATAPI_COMMAND        *AtapiCommand OPTIONAL,
  IN     UINT8                         AtapiCommandLength,
  IN     EFI_ATA_COMMAND_BLOCK         *AtaCommandBlock,
  IN OUT EFI_ATA_STATUS_BLOCK          *AtaStatusBlock,
  IN     UINT64                        Timeout,
  IN     ATA_NONBLOCK_TASK             *Task
  )
{
  EFI_STATUS                   Status;
  UINTN                        FisBaseAddr;
  UINTN                        Offset;
  UINT32                       PortTfd;
  EFI_AHCI_COMMAND_FIS         CFis;
  EFI_AHCI_COMMAND_LIST        CmdList;

  //
  // Package read needed
  //
  AhciBuildCommandFis (&CFis, AtaCommandBlock);

  ZeroMem (&CmdList, sizeof (EFI_AHCI_COMMAND_LIST));

  CmdList.AhciCmdCfl = EFI_AHCI_FIS_REGISTER_H2D_LENGTH / 4;

  AhciBuildCommand (
    AhciRegisters,
    Port,
    PortMultiplier,
    &CFis,
    &CmdList,
    AtapiCommand,
    AtapiCommandLength,
    0,
    NULL,
    0
    );

  Status = AhciStartCommand (
             Port,
             0,
             Timeout
             );
  if (EFI_ERROR (Status)) {
    goto Exit;
  }

  //
  // Wait device sends the Response Fis
  //
  FisBaseAddr = (UINTN)AhciRegisters->AhciRFis + Port * sizeof (EFI_AHCI_RECEIVED_FIS);
  Offset      = FisBaseAddr + EFI_AHCI_D2H_FIS_OFFSET;
  Status      = AhciWaitMemSet (
                  Offset,
                  EFI_AHCI_FIS_TYPE_MASK,
                  EFI_AHCI_FIS_REGISTER_D2H,
                  Timeout
                  );

  if (EFI_ERROR (Status)) {
    goto Exit;
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
  PortTfd = AhciReadReg ((UINT32) Offset);
  if ((PortTfd & EFI_AHCI_PORT_TFD_ERR) != 0) {
    Status = EFI_DEVICE_ERROR;
  }

Exit:
  AhciStopCommand (
    Port,
    Timeout
    );

  AhciDisableFisReceive (
    Port,
    Timeout
    );

  AhciDumpPortStatus (AhciRegisters, Port, AtaStatusBlock);

  return Status;
}

/**
  Stop command running for giving port

  @param  Port               The number of port.
  @param  Timeout            The timeout value of stop, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   The command stop unsuccessfully.
  @retval EFI_TIMEOUT        The operation is time out.
  @retval EFI_SUCCESS        The command stop successfully.

**/
EFI_STATUS
EFIAPI
AhciStopCommand (
  IN  UINT8                     Port,
  IN  UINT64                    Timeout
  )
{
  UINT32 Offset;
  UINT32 Data;

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  Data   = AhciReadReg (Offset);

  if ((Data & (EFI_AHCI_PORT_CMD_ST |  EFI_AHCI_PORT_CMD_CR)) == 0) {
    return EFI_SUCCESS;
  }

  if ((Data & EFI_AHCI_PORT_CMD_ST) != 0) {
    AhciAndReg (Offset, (UINT32)~(EFI_AHCI_PORT_CMD_ST));
  }

  return AhciWaitMmioSet (
           Offset,
           EFI_AHCI_PORT_CMD_CR,
           0,
           Timeout
           );
}

/**
  Start command for give slot on specific port.

  @param  Port               The number of port.
  @param  CommandSlot        The number of Command Slot.
  @param  Timeout            The timeout value of start, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   The command start unsuccessfully.
  @retval EFI_TIMEOUT        The operation is time out.
  @retval EFI_SUCCESS        The command start successfully.

**/
EFI_STATUS
EFIAPI
AhciStartCommand (
  IN  UINT8                     Port,
  IN  UINT8                     CommandSlot,
  IN  UINT64                    Timeout
  )
{
  UINT32     CmdSlotBit;
  EFI_STATUS Status;
  UINT32     PortStatus;
  UINT32     StartCmd;
  UINT32     PortTfd;
  UINT32     Offset;
  UINT32     Capability;

  //
  // Collect AHCI controller information
  //
  Capability = AhciReadReg(EFI_AHCI_CAPABILITY_OFFSET);

  CmdSlotBit = (UINT32) (1 << CommandSlot);

  AhciClearPortStatus (
    Port
    );

  Status = AhciEnableFisReceive (
             Port,
             Timeout
             );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  PortStatus = AhciReadReg (Offset);

  StartCmd = 0;
  if ((PortStatus & EFI_AHCI_PORT_CMD_ALPE) != 0) {
    StartCmd = AhciReadReg (Offset);
    StartCmd &= ~EFI_AHCI_PORT_CMD_ICC_MASK;
    StartCmd |= EFI_AHCI_PORT_CMD_ACTIVE;
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;
  PortTfd = AhciReadReg (Offset);

  if ((PortTfd & (EFI_AHCI_PORT_TFD_BSY | EFI_AHCI_PORT_TFD_DRQ)) != 0) {
    if ((Capability & BIT24) != 0) {
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
      AhciOrReg (Offset, EFI_AHCI_PORT_CMD_CLO);

      AhciWaitMmioSet (
        Offset,
        EFI_AHCI_PORT_CMD_CLO,
        0,
        Timeout
        );
    }
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
  AhciOrReg (Offset, EFI_AHCI_PORT_CMD_ST | StartCmd);

  //
  // Setting the command
  //
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CI;
  AhciAndReg (Offset, 0);
  AhciOrReg (Offset, CmdSlotBit);

  return EFI_SUCCESS;
}

/**
  Do AHCI port reset.

  @param  Port               The number of port.
  @param  Timeout            The timeout value of reset, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   The port reset unsuccessfully
  @retval EFI_TIMEOUT        The reset operation is time out.
  @retval EFI_SUCCESS        The port reset successfully.

**/
EFI_STATUS
EFIAPI
AhciPortReset (
  IN  UINT8                     Port,
  IN  UINT64                    Timeout
  )
{
  EFI_STATUS      Status;
  UINT32          Offset;

  AhciClearPortStatus (Port);

  AhciStopCommand (Port, Timeout);

  AhciDisableFisReceive (Port, Timeout);

  AhciEnableFisReceive (Port, Timeout);

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SCTL;

  AhciOrReg (Offset, EFI_AHCI_PORT_SCTL_DET_INIT);

  //
  // wait 5 millisecond before de-assert DET
  //
  MicroSecondDelay (5000);

  AhciAndReg (Offset, (UINT32)EFI_AHCI_PORT_SCTL_MASK);

  //
  // wait 5 millisecond before de-assert DET
  //
  MicroSecondDelay (5000);

  //
  // Wait for communication to be re-established
  //
  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SSTS;
  Status = AhciWaitMmioSet (
             Offset,
             EFI_AHCI_PORT_SSTS_DET_MASK,
             EFI_AHCI_PORT_SSTS_DET_PCE,
             Timeout
             );

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Port %d COMRESET failed: %r\n", Port, Status));
    return Status;
  }

  Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SERR;
  AhciOrReg (Offset, EFI_AHCI_PORT_ERR_CLEAR);

  return EFI_SUCCESS;
}

/**
  Do AHCI HBA reset.

  @param  Timeout            The timeout value of reset, uses 100ns as a unit.

  @retval EFI_DEVICE_ERROR   AHCI controller is failed to complete hardware reset.
  @retval EFI_TIMEOUT        The reset operation is time out.
  @retval EFI_SUCCESS        AHCI controller is reset successfully.

**/
EFI_STATUS
EFIAPI
AhciReset (
  IN  UINT64                    Timeout
  )
{
  UINT64                 Delay;
  UINT32                 Value;

  //
  // Make sure that GHC.AE bit is set before accessing any AHCI registers.
  //
  Value = AhciReadReg(EFI_AHCI_GHC_OFFSET);

  if ((Value & EFI_AHCI_GHC_ENABLE) == 0) {
    AhciOrReg (EFI_AHCI_GHC_OFFSET, EFI_AHCI_GHC_ENABLE);
  }

  AhciOrReg (EFI_AHCI_GHC_OFFSET, EFI_AHCI_GHC_RESET);

  Delay = DivU64x32(Timeout, 1000) + 1;

  do {
    Value = AhciReadReg(EFI_AHCI_GHC_OFFSET);

    if ((Value & EFI_AHCI_GHC_RESET) == 0) {
      break;
    }

    //
    // Stall for 100 microseconds.
    //
    MicroSecondDelay(100);

    Delay--;
  } while (Delay > 0);

  if (Delay == 0) {
    return EFI_TIMEOUT;
  }

  return EFI_SUCCESS;
}

/**
  Send Buffer cmd to specific device.

  @param  AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param  Port                The number of port.
  @param  PortMultiplier      The port multiplier port number.
  @param  Buffer              The data buffer to store IDENTIFY PACKET data.

  @retval EFI_DEVICE_ERROR    The cmd abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for executing.
  @retval EFI_SUCCESS         The cmd executes successfully.

**/
EFI_STATUS
EFIAPI
AhciIdentify (
  IN EFI_AHCI_REGISTERS       *AhciRegisters,
  IN UINT8                    Port,
  IN UINT8                    PortMultiplier,
  IN OUT EFI_IDENTIFY_DATA    *Buffer
  )
{
  EFI_STATUS                   Status;
  EFI_ATA_COMMAND_BLOCK        AtaCommandBlock;

  if (AhciRegisters == NULL || Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (&AtaCommandBlock, sizeof (EFI_ATA_COMMAND_BLOCK));

  AtaCommandBlock.AtaCommand     = ATA_CMD_IDENTIFY_DRIVE;
  AtaCommandBlock.AtaSectorCount = 1;

  Status = AhciPioTransfer (
             AhciRegisters,
             Port,
             PortMultiplier,
             NULL,
             0,
             TRUE,
             &AtaCommandBlock,
             NULL,
             Buffer,
             sizeof (EFI_IDENTIFY_DATA),
             ATA_ATAPI_TIMEOUT
             );

  return Status;
}

/**
  Send SET FEATURE cmd on specific device.

  @param  AhciRegisters       The pointer to the EFI_AHCI_REGISTERS.
  @param  Port                The number of port.
  @param  PortMultiplier      The port multiplier port number.
  @param  Feature             The data to send Feature register.
  @param  FeatureSpecificData The specific data for SET FEATURE cmd.

  @retval EFI_DEVICE_ERROR    The cmd abort with error occurs.
  @retval EFI_TIMEOUT         The operation is time out.
  @retval EFI_UNSUPPORTED     The device is not ready for executing.
  @retval EFI_SUCCESS         The cmd executes successfully.

**/
EFI_STATUS
EFIAPI
AhciDeviceSetFeature (
  IN EFI_AHCI_REGISTERS     *AhciRegisters,
  IN UINT8                  Port,
  IN UINT8                  PortMultiplier,
  IN UINT16                 Feature,
  IN UINT32                 FeatureSpecificData
  )
{
  EFI_STATUS               Status;
  EFI_ATA_COMMAND_BLOCK    AtaCommandBlock;
  EFI_ATA_STATUS_BLOCK     AtaStatusBlock;

  ZeroMem (&AtaCommandBlock, sizeof (EFI_ATA_COMMAND_BLOCK));
  ZeroMem (&AtaStatusBlock, sizeof (EFI_ATA_STATUS_BLOCK));

  AtaCommandBlock.AtaCommand      = ATA_CMD_SET_FEATURES;
  AtaCommandBlock.AtaFeatures     = (UINT8) Feature;
  AtaCommandBlock.AtaFeaturesExp  = (UINT8) (Feature >> 8);
  AtaCommandBlock.AtaSectorCount  = (UINT8) FeatureSpecificData;
  AtaCommandBlock.AtaSectorNumber = (UINT8) (FeatureSpecificData >> 8);
  AtaCommandBlock.AtaCylinderLow  = (UINT8) (FeatureSpecificData >> 16);
  AtaCommandBlock.AtaCylinderHigh = (UINT8) (FeatureSpecificData >> 24);

  Status = AhciNonDataTransfer (
             AhciRegisters,
             (UINT8)Port,
             (UINT8)PortMultiplier,
             NULL,
             0,
             &AtaCommandBlock,
             &AtaStatusBlock,
             ATA_ATAPI_TIMEOUT,
             NULL
             );

  return Status;
}

/**
  Allocate transfer-related data struct which is used at AHCI mode.

  @param  AhciRegisters         The pointer to the EFI_AHCI_REGISTERS.

**/
EFI_STATUS
EFIAPI
AhciCreateTransferDescriptor (
  IN OUT EFI_AHCI_REGISTERS     *AhciRegisters
  )
{
  EFI_STATUS            Status;
  EFI_PHYSICAL_ADDRESS  Buffer;

  UINT32                Capability;
  UINT32                PortImplementBitMap;
  UINT8                 MaxPortNumber;
  UINT8                 MaxCommandSlotNumber;
  UINT64                MaxReceiveFisSize;
  UINT64                MaxCommandListSize;
  UINT64                MaxCommandTableSize;

  //
  // Collect AHCI controller information
  //
  Capability           = AhciReadReg(EFI_AHCI_CAPABILITY_OFFSET);
  //
  // Get the number of command slots per port supported by this HBA.
  //
  MaxCommandSlotNumber = (UINT8) (((Capability & 0x1F00) >> 8) + 1);
  DEBUG ((EFI_D_INFO, " MaxCommandSlotNumber = 0x%x..\n", MaxCommandSlotNumber));

  PortImplementBitMap  = AhciReadReg(EFI_AHCI_PI_OFFSET);
  //
  // Get the highest bit of implemented ports which decides how many bytes are allocated for recived FIS.
  //
  MaxPortNumber        = (UINT8)(UINTN)(HighBitSet32(PortImplementBitMap) + 1);
  DEBUG ((EFI_D_INFO, " MaxPortNumber = 0x%x..\n", MaxPortNumber));
  if (MaxPortNumber == 0) {
    return EFI_DEVICE_ERROR;
  }

  //
  // Allocate memory for received FIS
  //
  MaxReceiveFisSize    = MaxPortNumber * sizeof (EFI_AHCI_RECEIVED_FIS);
  Status = PeiServicesAllocatePages (
             EfiBootServicesData,
             EFI_SIZE_TO_PAGES ((UINTN) MaxReceiveFisSize),
             &Buffer
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    return EFI_OUT_OF_RESOURCES;
  }

  ZeroMem ((VOID *) (UINTN) Buffer, (UINTN)MaxReceiveFisSize);
  AhciRegisters->AhciRFis          = (VOID *) (UINTN)Buffer;
  AhciRegisters->MaxReceiveFisSize = MaxReceiveFisSize;

  //
  // Allocate memory for command list
  // Note that the implemenation is a single task model which only use a command list for all ports.
  //
  MaxCommandListSize = MaxCommandSlotNumber * sizeof (EFI_AHCI_COMMAND_LIST);
  Status = PeiServicesAllocatePages (
             EfiBootServicesData,
             EFI_SIZE_TO_PAGES ((UINTN) MaxCommandListSize),
             &Buffer
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    Status = EFI_OUT_OF_RESOURCES;
  }

  ZeroMem ((VOID *) (UINTN) Buffer, (UINTN)MaxCommandListSize);
  AhciRegisters->AhciCmdList        = (VOID *) (UINTN)Buffer;
  AhciRegisters->MaxCommandListSize = MaxCommandListSize;

  //
  // Allocate memory for command table
  // According to AHCI 1.3 spec, a PRD table can contain maximum 65535 entries.
  //
  MaxCommandTableSize = sizeof (EFI_AHCI_COMMAND_TABLE);
  Status = PeiServicesAllocatePages (
             EfiBootServicesData,
             EFI_SIZE_TO_PAGES ((UINTN) MaxCommandTableSize),
             &Buffer
             );
  ASSERT_EFI_ERROR (Status);
  if (EFI_ERROR (Status)) {
    Status = EFI_OUT_OF_RESOURCES;
  }

  ZeroMem ((VOID *) (UINTN) Buffer, (UINTN)MaxCommandTableSize);
  AhciRegisters->AhciCommandTable    = (VOID *) (UINTN)Buffer;
  AhciRegisters->MaxCommandTableSize = MaxCommandTableSize;

  return EFI_SUCCESS;
}

/**
  Initialize ATA host controller at AHCI mode.

  The function is designed to initialize ATA host controller.

  @param[in]  Instance          A pointer to the ATA_ATAPI_PASS_THRU_INSTANCE instance.

**/
EFI_STATUS
EFIAPI
AhciModeInitialization (
  IN  PEI_ATA_PASS_THRU_INSTANCE   *Instance
  )
{
  EFI_STATUS                       Status;
  UINT32                           Capability;
  UINT8                            MaxPortNumber;
  UINT32                           PortImplementBitMap;

  EFI_AHCI_REGISTERS               *AhciRegisters;

  UINT8                            Port;
  DATA_64                          Data64;
  UINT32                           Offset;
  UINT32                           Data;
  EFI_IDENTIFY_DATA                Buffer;
  EFI_ATA_DEVICE_TYPE              DeviceType;
  EFI_ATA_TRANSFER_MODE            TransferMode;
  UINT32                           PhyDetectDelay;
  UINT32                           Value;

  if (Instance == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  DEBUG ((EFI_D_INFO, "AhciModeInitialization: begin\n"));

  Status = AhciReset (EFI_AHCI_BUS_RESET_TIMEOUT);

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "  AHCI bus reset timeout\n"));
    return EFI_DEVICE_ERROR;
  }

  //
  // Collect AHCI controller information
  //
  Capability = AhciReadReg (EFI_AHCI_CAPABILITY_OFFSET);
  DEBUG ((EFI_D_INFO, " Capability = %x..\n", Capability));

  //
  // Make sure that GHC.AE bit is set before accessing any AHCI registers.
  //
  Value = AhciReadReg(EFI_AHCI_GHC_OFFSET);

  if ((Value & EFI_AHCI_GHC_ENABLE) == 0) {
    AhciOrReg (EFI_AHCI_GHC_OFFSET, EFI_AHCI_GHC_ENABLE);
  }

  //
  // Get the number of command slots per port supported by this HBA.
  //
  MaxPortNumber        = (UINT8) ((Capability & 0x1F) + 1);
  DEBUG ((EFI_D_INFO, " MaxPortNumber = 0x%x..\n", MaxPortNumber));

  //
  // Get the bit map of those ports exposed by this HBA.
  // It indicates which ports that the HBA supports are available for software to use.
  //
  PortImplementBitMap  = AhciReadReg(EFI_AHCI_PI_OFFSET);
  DEBUG ((EFI_D_INFO, " PortImplementBitMap = 0x%x..\n", PortImplementBitMap));

  AhciRegisters = &Instance->AhciRegisters;
  Status = AhciCreateTransferDescriptor (AhciRegisters);

  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "  AhciCreateTransferDescriptor failed\n"));
    return EFI_OUT_OF_RESOURCES;
  }

  DEBUG ((EFI_D_INFO, "  start enumerate port..\n"));

  //
  // Enumerate ATA port
  //
  for (Port = 0; Port < EFI_AHCI_MAX_PORTS; Port ++) {
    if ((PortImplementBitMap & (BIT0 << Port)) != 0) {
      DEBUG ((EFI_D_INFO, "  find port implemented(0x%x).\n", Port));
      //
      // According to AHCI spec, MaxPortNumber should be equal or greater than the number of implemented ports.
      //
      if ((MaxPortNumber--) == 0) {
        //
        // Should never be here.
        //
        ASSERT (FALSE);
        return EFI_SUCCESS;
      }

      //
      // Initialize FIS Base Address Register and Command List Base Address Register for use.
      //
      Data64.Uint64 = (UINTN) (AhciRegisters->AhciRFis) + sizeof (EFI_AHCI_RECEIVED_FIS) * Port;
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FB;
      AhciWriteReg (Offset, Data64.Uint32.Lower32);
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_FBU;
      AhciWriteReg (Offset, Data64.Uint32.Upper32);

      Data64.Uint64 = (UINTN) (AhciRegisters->AhciCmdList);
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLB;
      AhciWriteReg (Offset, Data64.Uint32.Lower32);
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CLBU;
      AhciWriteReg (Offset, Data64.Uint32.Upper32);

      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
      Data = AhciReadReg (Offset);
      if ((Data & EFI_AHCI_PORT_CMD_CPD) != 0) {
        AhciOrReg (Offset, EFI_AHCI_PORT_CMD_POD);
      }

      if ((Capability & EFI_AHCI_CAP_SSS) != 0) {
        AhciOrReg (Offset, EFI_AHCI_PORT_CMD_SUD);
      }

      //
      // Disable aggressive power management.
      //
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SCTL;
      AhciOrReg (Offset, EFI_AHCI_PORT_SCTL_IPM_INIT);
      //
      // Disable the reporting of the corresponding interrupt to system software.
      //
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_IE;
      AhciAndReg (Offset, 0);

      //
      // Enable FIS Receive DMA engine for the first D2H FIS.
      //
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
      AhciOrReg (Offset, EFI_AHCI_PORT_CMD_FRE);

      //
      // Wait no longer than 10 ms to wait the Phy to detect the presence of a device.
      // It's the requirment from SATA1.0a spec section 5.2.
      //
      PhyDetectDelay = EFI_AHCI_BUS_PHY_DETECT_TIMEOUT;
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SSTS;
      do {
        Data = AhciReadReg (Offset) & EFI_AHCI_PORT_SSTS_DET_MASK;
        if ((Data == EFI_AHCI_PORT_SSTS_DET_PCE) || (Data == EFI_AHCI_PORT_SSTS_DET)) {
          break;
        }

        MicroSecondDelay (1000);
        PhyDetectDelay--;
      } while (PhyDetectDelay > 0);

      if (PhyDetectDelay == 0) {
        //
        // No device detected at this port.
        // Clear PxCMD.SUD for those ports at which there are no device present.
        //
        Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_CMD;
        AhciAndReg (Offset, (UINT32) ~(EFI_AHCI_PORT_CMD_SUD));
        DEBUG ((EFI_D_ERROR, " Port %d No device detected at this port\n", Port));
        continue;
      }

      //
      // According to SATA1.0a spec section 5.2, we need to wait for PxTFD.BSY and PxTFD.DRQ
      // and PxTFD.ERR to be zero. The maximum wait time is 16s which is defined at ATA spec.
      //
      PhyDetectDelay = 16 * 1000;
      do {
        Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SERR;
        if (AhciReadReg(Offset) != 0) {
          AhciWriteReg (Offset, AhciReadReg(Offset));
        }
        Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_TFD;

        Data = AhciReadReg (Offset) & EFI_AHCI_PORT_TFD_MASK;
        if (Data == 0) {
          break;
        }

        MicroSecondDelay (1000);
        PhyDetectDelay--;
      } while (PhyDetectDelay > 0);

      if (PhyDetectDelay == 0) {
        DEBUG ((EFI_D_ERROR, " Port %d Device presence detected but phy not ready (TFD=0x%X)\n", Port, Data));
        continue;
      }

      //
      // When the first D2H register FIS is received, the content of PxSIG register is updated.
      //
      Offset = EFI_AHCI_PORT_START + Port * EFI_AHCI_PORT_REG_WIDTH + EFI_AHCI_PORT_SIG;
      Status = AhciWaitMmioSet (
                 Offset,
                 0x0000FFFF,
                 0x00000101,
                 EFI_TIMER_PERIOD_SECONDS(16)
                 );
      if (EFI_ERROR (Status)) {
        DEBUG ((EFI_D_ERROR, " AhciWaitMmioSet : %r\n", Status));
        continue;
      }

      Data = AhciReadReg (Offset);
      if ((Data & EFI_AHCI_ATAPI_SIG_MASK) == EFI_AHCI_ATA_DEVICE_SIG) {
        Status = AhciIdentify (AhciRegisters, Port, 0, &Buffer);

        if (EFI_ERROR (Status)) {
          DEBUG ((EFI_D_ERROR, "  AhciIdentify : %r\n", Status));
          continue;
        }

        DeviceType = EfiIdeHarddisk;
      } else {
        DEBUG ((EFI_D_ERROR, " No match type \n"));
        continue;
      }
      DEBUG ((EFI_D_INFO, "port [%d] port mulitplier [%d] has a [%a]\n",
              Port, 0, DeviceType == EfiIdeCdrom ? "cdrom" : "harddisk"));

      //
      // Set best supported PIO mode on this IDE device
      //
      if (mSupportedModes.PioMode.Mode <= EfiAtaPioMode2) {
        TransferMode.ModeCategory = EFI_ATA_MODE_DEFAULT_PIO;
      } else {
        TransferMode.ModeCategory = EFI_ATA_MODE_FLOW_PIO;
      }

      TransferMode.ModeNumber = (UINT8) (mSupportedModes.PioMode.Mode);

      //
      // Set supported DMA mode on this IDE device. Note that UDMA & MDMA cann't
      // be set together. Only one DMA mode can be set to a device. If setting
      // DMA mode operation fails, we can continue moving on because we only use
      // PIO mode at boot time. DMA modes are used by certain kind of OS booting
      //
      if (mSupportedModes.UdmaMode.Valid) {
        TransferMode.ModeCategory = EFI_ATA_MODE_UDMA;
        TransferMode.ModeNumber = (UINT8) (mSupportedModes.UdmaMode.Mode);
      } else if (mSupportedModes.MultiWordDmaMode.Valid) {
        TransferMode.ModeCategory = EFI_ATA_MODE_MDMA;
        TransferMode.ModeNumber = (UINT8) mSupportedModes.MultiWordDmaMode.Mode;
      }

      Status = AhciDeviceSetFeature (AhciRegisters, Port, 0, 0x03, (UINT32)(*(UINT8 *)&TransferMode));
      DEBUG ((EFI_D_INFO, "Set transfer Mode 0x%x, status = %r\n", TransferMode, Status));

      if (EFI_ERROR (Status)) {
        continue;
      }

      //
      // Found a ATA or ATAPI device, add it into the device list.
      //
      CreateNewDeviceInfo (Instance, Port, 0xFFFF, DeviceType, &Buffer);
      //if (DeviceType == EfiIdeHarddisk) {
      //  DEBUG ((EFI_D_INFO, "CreateNewDeviceInfo  \n"));
      //}
    }
  }

  DEBUG ((EFI_D_INFO, "AhciModeInitialization: end\n"));

  return EFI_SUCCESS;
}


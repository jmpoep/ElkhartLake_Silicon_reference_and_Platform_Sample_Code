/** @file
  NvmExpressPei PEIM intends to provide NvmExpressPassThru PPI and VirtualBlockIo PPI of NVME device in PEI phase.

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

@par Specification Reference:

**/

#include "NvmExpressPeim.h"

#define ALIGN(v, a)                         (UINTN)((((v) - 1) | ((a) - 1)) + 1)

///
/// NVME Host controller registers operation
///
#define NVME_GET_CAP(NBar, Cap)             NvmeMmioRead  (Cap, NBar + NVME_CAP_OFFSET, sizeof (NVME_CAP))
#define NVME_GET_CC(NBar, Cc)               NvmeMmioRead  (Cc, NBar + NVME_CC_OFFSET, sizeof (NVME_CC))
#define NVME_SET_CC(NBar, Cc)               NvmeMmioWrite (NBar + NVME_CC_OFFSET, Cc, sizeof (NVME_CC))
#define NVME_GET_CSTS(NBar, Csts)           NvmeMmioRead  (Csts, NBar + NVME_CSTS_OFFSET, sizeof (NVME_CSTS))
#define NVME_GET_AQA(NBar, Aqa)             NvmeMmioRead  (Aqa, NBar + NVME_AQA_OFFSET, sizeof (NVME_AQA))
#define NVME_SET_AQA(NBar, Aqa)             NvmeMmioWrite (NBar + NVME_AQA_OFFSET, Aqa, sizeof (NVME_AQA))
#define NVME_GET_ASQ(NBar, Asq)             NvmeMmioRead  (Asq, NBar + NVME_ASQ_OFFSET, sizeof (NVME_ASQ))
#define NVME_SET_ASQ(NBar, Asq)             NvmeMmioWrite (NBar + NVME_ASQ_OFFSET, Asq, sizeof (NVME_ASQ))
#define NVME_GET_ACQ(NBar, Acq)             NvmeMmioRead  (Acq, NBar + NVME_ACQ_OFFSET, sizeof (NVME_ACQ))
#define NVME_SET_ACQ(NBar, Acq)             NvmeMmioWrite (NBar + NVME_ACQ_OFFSET, Acq, sizeof (NVME_ACQ))
#define NVME_GET_VER(NBar, Ver)             NvmeMmioRead  (Ver, NBar + NVME_VER_OFFSET, sizeof (NVME_VER))
#define NVME_SET_SQTDBL(NBar, Qid, Dstrd, Sqtdbl)  NvmeMmioWrite (NBar + NVME_SQTDBL_OFFSET(Qid, Dstrd), Sqtdbl, sizeof (NVME_SQTDBL))
#define NVME_SET_CQHDBL(NBar, Qid, Dstrd, Cqhdbl)  NvmeMmioWrite (NBar + NVME_CQHDBL_OFFSET(Qid, Dstrd), Cqhdbl, sizeof (NVME_CQHDBL))

///
/// Base memory address
///
enum {
  BASEMEM_CONTROLLER_DATA,
  BASEMEM_IDENTIFY_DATA,
  BASEMEM_ASQ,
  BASEMEM_ACQ,
  BASEMEM_SQ,
  BASEMEM_CQ,
  BASEMEM_PRP,
  BASEMEM_SECURITY,
  MAX_BASEMEM_COUNT
};

#define NVME_MEM_MAX_PAGE \
  ( \
  1                                         /* Controller Data */ +  \
  1                                         /* Identify Data */   +  \
  1                                         /* ASQ */             +  \
  1                                         /* ACQ */             +  \
  1                                         /* SQs */             +  \
  1                                         /* CQs */             +  \
  NVME_PRP_SIZE * NVME_CSQ_DEPTH)            /* PRPs */

///
/// All of base memories are 4K(0x1000) alignment
///
#define NVME_MEM_BASE(Nvme)                 ((UINT32)(UINTN)Nvme->Buffer)
#define NVME_CONTROL_DATA_BASE(Nvme)        (ALIGN (NVME_MEM_BASE(Nvme) + ((NvmeGetBaseMemPages (BASEMEM_CONTROLLER_DATA))                        * EFI_PAGE_SIZE), EFI_PAGE_SIZE))
#define NVME_NAMESPACE_DATA_BASE(Nvme)      (ALIGN (NVME_MEM_BASE(Nvme) + ((NvmeGetBaseMemPages (BASEMEM_IDENTIFY_DATA))                          * EFI_PAGE_SIZE), EFI_PAGE_SIZE))
#define NVME_ASQ_BASE(Nvme)                 (ALIGN (NVME_MEM_BASE(Nvme) + ((NvmeGetBaseMemPages (BASEMEM_ASQ))                                    * EFI_PAGE_SIZE), EFI_PAGE_SIZE))
#define NVME_ACQ_BASE(Nvme)                 (ALIGN (NVME_MEM_BASE(Nvme) + ((NvmeGetBaseMemPages (BASEMEM_ACQ))                                    * EFI_PAGE_SIZE), EFI_PAGE_SIZE))
#define NVME_SQ_BASE(Nvme, index)           (ALIGN (NVME_MEM_BASE(Nvme) + ((NvmeGetBaseMemPages (BASEMEM_SQ) + ((index)*(NVME_MAX_IO_QUEUES-1)))  * EFI_PAGE_SIZE), EFI_PAGE_SIZE))
#define NVME_CQ_BASE(Nvme, index)           (ALIGN (NVME_MEM_BASE(Nvme) + ((NvmeGetBaseMemPages (BASEMEM_CQ) + ((index)*(NVME_MAX_IO_QUEUES-1)))  * EFI_PAGE_SIZE), EFI_PAGE_SIZE))
#define NVME_PRP_BASE(Nvme, index)          (ALIGN (NVME_MEM_BASE(Nvme) + ((NvmeGetBaseMemPages (BASEMEM_PRP) + ((index)*NVME_PRP_SIZE))          * EFI_PAGE_SIZE), EFI_PAGE_SIZE))
#define NVME_SEC_BASE(Nvme)                 (ALIGN (NVME_MEM_BASE(Nvme) + ((NvmeGetBaseMemPages (BASEMEM_SECURITY))                               * EFI_PAGE_SIZE), EFI_PAGE_SIZE))

//
// Template for NVM Express Pass Thru Mode data structure.
//
PEI_NVM_EXPRESS_PASS_THRU_MODE gEfiNvmExpressPassThruMode = {
  EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_PHYSICAL | EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_LOGICAL | EFI_NVM_EXPRESS_PASS_THRU_ATTRIBUTES_CMD_SET_NVM,
  sizeof (UINTN),
  0x10100
};

/**
  Transfer MMIO Data to memory.

  @param[in,out] MemBuffer          Destination: Memory address
  @param[in]     MmioAddr           Source: MMIO address
  @param[in]     Size               Size for read

  @retval        EFI_SUCCESS        MMIO read sucessfully

**/
EFI_STATUS
NvmeMmioRead (
  IN OUT VOID *MemBuffer,
  IN     UINTN MmioAddr,
  IN     UINTN Size
  )
{
  UINTN  Offset;
  UINT8  Data;
  UINT8  *Ptr;

  switch (Size) {
    case 4:
      *((UINT32 *)MemBuffer) = MmioRead32 (MmioAddr);
      break;

    case 8:
      *((UINT64 *)MemBuffer) = MmioRead64 (MmioAddr);
      break;

    case 2:
      *((UINT16 *)MemBuffer) = MmioRead16 (MmioAddr);
      break;

    case 1:
      *((UINT8 *)MemBuffer) = MmioRead8 (MmioAddr);
      break;

    default:
      Ptr = (UINT8 *)MemBuffer;
      for (Offset = 0; Offset < Size; Offset += 1) {
        Data = MmioRead8 (MmioAddr + Offset);
        Ptr[Offset] = Data;
      }
      break;
  }

  return EFI_SUCCESS;
}

/**
  Transfer memory data to MMIO.

  @param[in,out] MmioAddr              Destination: MMIO address
  @param[in]     MemBuffer             Source: Memory address
  @param[in]     Size                  Size for write

  @retval        EFI_SUCCESS           MMIO write sucessfully

**/
EFI_STATUS
NvmeMmioWrite (
  IN OUT UINTN MmioAddr,
  IN     VOID *MemBuffer,
  IN     UINTN Size
  )
{
  UINTN  Offset;
  UINT8  Data;
  UINT8  *Ptr;

  switch (Size) {
    case 4:
      MmioWrite32 (MmioAddr, *((UINT32 *)MemBuffer));
      break;

    case 8:
      MmioWrite64 (MmioAddr, *((UINT64 *)MemBuffer));
      break;

    case 2:
      MmioWrite16 (MmioAddr, *((UINT16 *)MemBuffer));
      break;

    case 1:
      MmioWrite8 (MmioAddr, *((UINT8 *)MemBuffer));
      break;

    default:
      Ptr = (UINT8 *)MemBuffer;
      for (Offset = 0; Offset < Size; Offset += 1) {
        Data = Ptr[Offset];
        MmioWrite8 (MmioAddr + Offset, Data);
      }
      break;
  }

  return EFI_SUCCESS;
}

/**
  Get total pages for specific NVME based memory.

  @param[in] BaseMemIndex      The Index of BaseMem (0-based).

  @retval    UINT32            The page count for specific BaseMem Index

**/
UINT32
NvmeGetBaseMemPages (
  IN UINTN              BaseMemIndex
  )
{
  UINT32                Pages;
  UINTN                 Index;
  UINT32                PageSizeList[8];

  PageSizeList[0] = 1;  /* Controller Data */
  PageSizeList[1] = 1;  /* Identify Data */
  PageSizeList[2] = 1;  /* ASQ */
  PageSizeList[3] = 1;  /* ACQ */
  PageSizeList[4] = 1;  /* SQs */
  PageSizeList[5] = 1;  /* CQs */
  PageSizeList[6] = NVME_PRP_SIZE * NVME_CSQ_DEPTH;  /* PRPs */
  PageSizeList[7] = 1;  /* Security Commands */

  if (BaseMemIndex > MAX_BASEMEM_COUNT) {
    ASSERT (FALSE);
    return 0;
  }

  Pages = 0;
  for (Index = 0; Index < BaseMemIndex; Index++) {
    Pages += PageSizeList[Index];
  }

  return Pages;
}

/**
  Dump the execution status from a given completion queue entry.

  @param[in]     Cq               A pointer to the NVME_CQ item.

**/
VOID
NvmeDumpStatus (
  IN NVME_CQ             *Cq
  )
{
  DEBUG ((DEBUG_INFO, "Dump NVMe Completion Entry Status from [0x%x]:\n", Cq));

  DEBUG ((DEBUG_INFO, "  SQ Identifier : [0x%x], Phase Tag : [%d], Cmd Identifier : [0x%x]\n", Cq->Sqid, Cq->Pt, Cq->Cid));

  DEBUG ((DEBUG_INFO, "  NVMe Cmd Execution Result - "));

  DEBUG ((DEBUG_INFO, "  Cq->Sct=%x, Cq->Sc=%x - ", Cq->Sct, Cq->Sc));

  switch (Cq->Sct) {
    case 0x0:
      switch (Cq->Sc) {
        case 0x0:
          DEBUG ((DEBUG_INFO, "Successful Completion\n"));
          break;
        case 0x1:
          DEBUG ((DEBUG_ERROR, "Invalid Command Opcode\n"));
          break;
        case 0x2:
          DEBUG ((DEBUG_ERROR, "Invalid Field in Command\n"));
          break;
        case 0x3:
          DEBUG ((DEBUG_ERROR, "Command ID Conflict\n"));
          break;
        case 0x4:
          DEBUG ((DEBUG_ERROR, "Data Transfer Error\n"));
          break;
        case 0x5:
          DEBUG ((DEBUG_ERROR, "Commands Aborted due to Power Loss Notification\n"));
          break;
        case 0x6:
          DEBUG ((DEBUG_ERROR, "Internal Device Error\n"));
          break;
        case 0x7:
          DEBUG ((DEBUG_ERROR, "Command Abort Requested\n"));
          break;
        case 0x8:
          DEBUG ((DEBUG_ERROR, "Command Aborted due to SQ Deletion\n"));
          break;
        case 0x9:
          DEBUG ((DEBUG_ERROR, "Command Aborted due to Failed Fused Command\n"));
          break;
        case 0xA:
          DEBUG ((DEBUG_ERROR, "Command Aborted due to Missing Fused Command\n"));
          break;
        case 0xB:
          DEBUG ((DEBUG_ERROR, "Invalid Namespace or Format\n"));
          break;
        case 0xC:
          DEBUG ((DEBUG_ERROR, "Command Sequence Error\n"));
          break;
        case 0xD:
          DEBUG ((DEBUG_ERROR, "Invalid SGL Last Segment Descriptor\n"));
          break;
        case 0xE:
          DEBUG ((DEBUG_ERROR, "Invalid Number of SGL Descriptors\n"));
          break;
        case 0xF:
          DEBUG ((DEBUG_ERROR, "Data SGL Length Invalid\n"));
          break;
        case 0x10:
          DEBUG ((DEBUG_ERROR, "Metadata SGL Length Invalid\n"));
          break;
        case 0x11:
          DEBUG ((DEBUG_ERROR, "SGL Descriptor Type Invalid\n"));
          break;
        case 0x80:
          DEBUG ((DEBUG_ERROR, "LBA Out of Range\n"));
          break;
        case 0x81:
          DEBUG ((DEBUG_ERROR, "Capacity Exceeded\n"));
          break;
        case 0x82:
          DEBUG ((DEBUG_ERROR, "Namespace Not Ready\n"));
          break;
        case 0x83:
          DEBUG ((DEBUG_ERROR, "Reservation Conflict\n"));
          break;
      }
      break;

    case 0x1:
      switch (Cq->Sc) {
        case 0x0:
          DEBUG ((DEBUG_ERROR, "Completion Queue Invalid\n"));
          break;
        case 0x1:
          DEBUG ((DEBUG_ERROR, "Invalid Queue Identifier\n"));
          break;
        case 0x2:
          DEBUG ((DEBUG_ERROR, "Maximum Queue Size Exceeded\n"));
          break;
        case 0x3:
          DEBUG ((DEBUG_ERROR, "Abort Command Limit Exceeded\n"));
          break;
        case 0x5:
          DEBUG ((DEBUG_ERROR, "Asynchronous Event Request Limit Exceeded\n"));
          break;
        case 0x6:
          DEBUG ((DEBUG_ERROR, "Invalid Firmware Slot\n"));
          break;
        case 0x7:
          DEBUG ((DEBUG_ERROR, "Invalid Firmware Image\n"));
          break;
        case 0x8:
          DEBUG ((DEBUG_ERROR, "Invalid Interrupt Vector\n"));
          break;
        case 0x9:
          DEBUG ((DEBUG_ERROR, "Invalid Log Page\n"));
          break;
        case 0xA:
          DEBUG ((DEBUG_ERROR, "Invalid Format\n"));
          break;
        case 0xB:
          DEBUG ((DEBUG_ERROR, "Firmware Application Requires Conventional Reset\n"));
          break;
        case 0xC:
          DEBUG ((DEBUG_ERROR, "Invalid Queue Deletion\n"));
          break;
        case 0xD:
          DEBUG ((DEBUG_ERROR, "Feature Identifier Not Saveable\n"));
          break;
        case 0xE:
          DEBUG ((DEBUG_ERROR, "Feature Not Changeable\n"));
          break;
        case 0xF:
          DEBUG ((DEBUG_ERROR, "Feature Not Namespace Specific\n"));
          break;
        case 0x10:
          DEBUG ((DEBUG_ERROR, "Firmware Application Requires NVM Subsystem Reset\n"));
          break;
        case 0x80:
          DEBUG ((DEBUG_ERROR, "Conflicting Attributes\n"));
          break;
        case 0x81:
          DEBUG ((DEBUG_ERROR, "Invalid Protection Information\n"));
          break;
        case 0x82:
          DEBUG ((DEBUG_ERROR, "Attempted Write to Read Only Range\n"));
          break;
      }
      break;

    case 0x2:
      switch (Cq->Sc) {
        case 0x80:
          DEBUG ((DEBUG_ERROR, "Write Fault\n"));
          break;
        case 0x81:
          DEBUG ((DEBUG_ERROR, "Unrecovered Read Error\n"));
          break;
        case 0x82:
          DEBUG ((DEBUG_ERROR, "End-to-end Guard Check Error\n"));
          break;
        case 0x83:
          DEBUG ((DEBUG_ERROR, "End-to-end Application Tag Check Error\n"));
          break;
        case 0x84:
          DEBUG ((DEBUG_ERROR, "End-to-end Reference Tag Check Error\n"));
          break;
        case 0x85:
          DEBUG ((DEBUG_ERROR, "Compare Failure\n"));
          break;
        case 0x86:
          DEBUG ((DEBUG_ERROR, "Access Denied\n"));
          break;
      }
      break;

    default:
      break;
  }
}

/**
  Read some sectors from the device.

  @param[in]  Device                 The pointer to the PEI_NVME_DEVICE_PRIVATE_DATA data structure.
  @param[in]  Buffer                 The buffer used to store the data read from the device.
  @param[in]  Lba                    The start block number.
  @param[in]  Blocks                 Total block number to be read.

  @retval     EFI_SUCCESS            Datum are read from the device.
  @retval     Others                 Fail to read all the datum.

**/
EFI_STATUS
ReadSectors (
  IN PEI_NVME_DEVICE_PRIVATE_DATA       *Device,
  IN UINT64                             Buffer,
  IN UINTN                              Lba,
  IN UINT32                             Blocks
  )
{
  PEI_NVME_CONTROLLER_PRIVATE_DATA         *Private;
  UINT32                                   Bytes;
  EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET CommandPacket;
  EFI_NVM_EXPRESS_COMMAND                  Command;
  EFI_NVM_EXPRESS_COMPLETION               Completion;
  EFI_STATUS                               Status;
  UINT32                                   BlockSize;

  Private    = Device->Controller;
  BlockSize  = Device->Media.BlockSize;
  Bytes      = Blocks * BlockSize;

  ZeroMem (&CommandPacket, sizeof(EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Command, sizeof(EFI_NVM_EXPRESS_COMMAND));
  ZeroMem (&Completion, sizeof(EFI_NVM_EXPRESS_COMPLETION));

  CommandPacket.NvmeCmd        = &Command;
  CommandPacket.NvmeCompletion = &Completion;

  CommandPacket.NvmeCmd->Cdw0.Opcode = NVME_IO_READ_OPC;
  CommandPacket.NvmeCmd->Nsid        = Device->NamespaceId;
  CommandPacket.TransferBuffer       = (VOID *)(UINTN)Buffer;

  CommandPacket.TransferLength = Bytes;
  CommandPacket.CommandTimeout = NVME_GENERIC_TIMEOUT;
  CommandPacket.QueueType      = NVME_IO_QUEUE;

  CommandPacket.NvmeCmd->Cdw10 = (UINT32)Lba;
  CommandPacket.NvmeCmd->Cdw11 = 0; //(UINT32)(Lba >> 32);
  CommandPacket.NvmeCmd->Cdw12 = (Blocks - 1) & 0xFFFF;

  CommandPacket.NvmeCmd->Flags = CDW10_VALID | CDW11_VALID | CDW12_VALID;

  Status = Private->Passthru.PassThru (
                               &Private->Passthru,
                               Device->NamespaceId,
                               &CommandPacket
                               );

  return Status;
}

/**
  Read some blocks from the device.

  @param[in]  Device                 The pointer to the PEI_NVME_DEVICE_PRIVATE_DATA data structure.
  @param[in]  Buffer                 The buffer used to store the data read from the device.
  @param[in]  Lba                    The start block number.
  @param[in]  Blocks                 Total block number to be read.

  @retval     EFI_SUCCESS            Datum are read from the device.
  @retval     Others                 Fail to read all the datum.

**/
EFI_STATUS
NvmeRead (
  IN     PEI_NVME_DEVICE_PRIVATE_DATA   *Device,
     OUT VOID                           *Buffer,
  IN     UINTN                          Lba,
  IN     UINTN                          Blocks
  )
{
  EFI_STATUS                           Status;
  UINT32                               BlockSize;
  PEI_NVME_CONTROLLER_PRIVATE_DATA     *Private;
  UINT32                               MaxTransferBlocks;

  Status        = EFI_SUCCESS;
  Private       = Device->Controller;
  BlockSize     = Device->Media.BlockSize;

  if (Private->ControllerData->Mdts != 0) {
    MaxTransferBlocks = (1 << (Private->ControllerData->Mdts)) * (1 << (Private->Cap.Mpsmin + 12)) / BlockSize;
  } else {
    MaxTransferBlocks = 1024;
  }

  while (Blocks > 0) {
    if (Blocks > MaxTransferBlocks) {
      Status = ReadSectors (Device, (UINT64)(UINTN)Buffer, Lba, MaxTransferBlocks);

      Blocks -= MaxTransferBlocks;
      Buffer  = (VOID *)(UINTN)((UINT64)(UINTN)Buffer + MaxTransferBlocks * BlockSize);
      Lba    += MaxTransferBlocks;
    } else {
      Status = ReadSectors (Device, (UINT64)(UINTN)Buffer, Lba, (UINT32)Blocks);
      Blocks = 0;
    }

    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "NvmeRead() from Lba 0x%08x with 0x%x blocks got error status %r\n", Lba, BlockSize, Status));
      break;
    }
  }

  return Status;
}

/**
  Get specified identify namespace data.

  @param[in]  Private          The pointer to the PEI_NVME_CONTROLLER_PRIVATE_DATA data structure.
  @param[in]  NamespaceId      The specified namespace identifier.
  @param[in]  Buffer           The buffer used to store the identify namespace data.

  @return EFI_SUCCESS          Successfully get the identify namespace data.
  @return EFI_DEVICE_ERROR     Fail to get the identify namespace data.

**/
EFI_STATUS
NvmeIdentifyNamespace (
  IN PEI_NVME_CONTROLLER_PRIVATE_DATA      *Private,
  IN UINT32                                NamespaceId,
  IN VOID                                  *Buffer
  )
{
  EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET CommandPacket;
  EFI_NVM_EXPRESS_COMMAND                  Command;
  EFI_NVM_EXPRESS_COMPLETION               Completion;
  EFI_STATUS                               Status;

  ZeroMem (&CommandPacket, sizeof(EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Command, sizeof(EFI_NVM_EXPRESS_COMMAND));
  ZeroMem (&Completion, sizeof(EFI_NVM_EXPRESS_COMPLETION));

  CommandPacket.NvmeCmd        = &Command;
  CommandPacket.NvmeCompletion = &Completion;

  Command.Cdw0.Opcode = NVME_ADMIN_IDENTIFY_CMD;
  Command.Nsid        = NamespaceId;
  CommandPacket.TransferBuffer = Buffer;
  CommandPacket.TransferLength = sizeof (NVME_ADMIN_NAMESPACE_DATA);
  CommandPacket.CommandTimeout = NVME_GENERIC_TIMEOUT;
  CommandPacket.QueueType      = NVME_ADMIN_QUEUE;
  //
  // Set bit 0 (Cns bit) to 1 to identify a namespace
  //
  CommandPacket.NvmeCmd->Cdw10 = 0;
  CommandPacket.NvmeCmd->Flags = CDW10_VALID;

  Status = Private->Passthru.PassThru (
                               &Private->Passthru,
                               NamespaceId,
                               &CommandPacket
                               );

  return Status;
}

/**
  Create PRP lists for data transfer which is larger than 2 memory pages.
  Note here we calcuate the number of required PRP lists and allocate them at one time.

  @param[in]     Private             The pointer to the PEI_NVME_DEVICE_PRIVATE_DATA data structure.
  @param[in]     SqId                The SQ index for this PRP.
  @param[in]     PhysicalAddr        The physical base address of data buffer.
  @param[in]     Pages               The number of pages to be transfered.
  @param[out]    PrpListHost         The host base address of PRP lists.
  @param[in,out] PrpListNo           The number of PRP List.

  @retval        The pointer to the first PRP List of the PRP lists.

**/
VOID*
NvmeCreatePrpList (
  IN     PEI_NVME_CONTROLLER_PRIVATE_DATA            *Private,
  IN     UINT16                                      SqId,
  IN     EFI_PHYSICAL_ADDRESS                        PhysicalAddr,
  IN     UINTN                                       Pages,
     OUT VOID                                        **PrpListHost,
  IN OUT UINTN                                       *PrpListNo
  )
{
  UINTN                       PrpEntryNo;
  UINT64                      PrpListBase;
  UINTN                       PrpListIndex;
  UINTN                       PrpEntryIndex;
  UINT64                      Remainder;
  EFI_PHYSICAL_ADDRESS        PrpListPhyAddr;
  UINTN                       Bytes;

  //
  // The number of Prp Entry in a memory page.
  //
  PrpEntryNo = EFI_PAGE_SIZE / sizeof (UINT64);

  //
  // Calculate total PrpList number.
  //
  *PrpListNo = (UINTN) DivU64x64Remainder ((UINT64)Pages, (UINT64)PrpEntryNo - 1, &Remainder);
  if (*PrpListNo == 0) {
    *PrpListNo = 1;
  } else if ((Remainder != 0) && (Remainder != 1)) {
    *PrpListNo += 1;
  } else if (Remainder == 1) {
    Remainder = PrpEntryNo;
  } else if (Remainder == 0) {
    Remainder = PrpEntryNo - 1;
  }

  if (*PrpListNo > NVME_PRP_SIZE) {
    DEBUG ((DEBUG_INFO, "NvmeCreatePrpList (PhysicalAddr: %lx, Pages: %x) PrpEntryNo: %x\n",
      PhysicalAddr, Pages, PrpEntryNo));
    DEBUG ((DEBUG_INFO, "*PrpListNo: %x, Remainder: %lx", *PrpListNo, Remainder));
    ASSERT (FALSE);
  }
  *PrpListHost = (VOID *)(UINTN) NVME_PRP_BASE (Private, SqId);

  Bytes = EFI_PAGES_TO_SIZE (*PrpListNo);
  PrpListPhyAddr = (UINT64)(UINTN)(*PrpListHost);

  //
  // Fill all PRP lists except of last one.
  //
  ZeroMem (*PrpListHost, Bytes);
  for (PrpListIndex = 0; PrpListIndex < *PrpListNo - 1; ++PrpListIndex) {
    PrpListBase = *(UINT64*)PrpListHost + PrpListIndex * EFI_PAGE_SIZE;

    for (PrpEntryIndex = 0; PrpEntryIndex < PrpEntryNo; ++PrpEntryIndex) {
      if (PrpEntryIndex != PrpEntryNo - 1) {
        //
        // Fill all PRP entries except of last one.
        //
        *((UINT64*)(UINTN)PrpListBase + PrpEntryIndex) = PhysicalAddr;
        PhysicalAddr += EFI_PAGE_SIZE;
      } else {
        //
        // Fill last PRP entries with next PRP List pointer.
        //
        *((UINT64*)(UINTN)PrpListBase + PrpEntryIndex) = PrpListPhyAddr + (PrpListIndex + 1) * EFI_PAGE_SIZE;
      }
    }
  }
  //
  // Fill last PRP list.
  //
  PrpListBase = *(UINT64*)PrpListHost + PrpListIndex * EFI_PAGE_SIZE;
  for (PrpEntryIndex = 0; PrpEntryIndex < Remainder; ++PrpEntryIndex) {
    *((UINT64*)(UINTN)PrpListBase + PrpEntryIndex) = PhysicalAddr;
    PhysicalAddr += EFI_PAGE_SIZE;
  }

  return (VOID*)(UINTN) PrpListPhyAddr;
}

/**
  Get identify controller data.

  @param[in]  Private              The pointer to the PEI_NVME_CONTROLLER_PRIVATE_DATA data structure.
  @param[in]  Buffer               The buffer used to store the identify controller data.

  @retval     EFI_SUCCESS          Successfully get the identify controller data.
  @retval     EFI_DEVICE_ERROR     Fail to get the identify controller data.

**/
EFI_STATUS
NvmeIdentifyController (
  IN PEI_NVME_CONTROLLER_PRIVATE_DATA       *Private,
  IN VOID                                   *Buffer
  )
{
  EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET CommandPacket;
  EFI_NVM_EXPRESS_COMMAND                  Command;
  EFI_NVM_EXPRESS_COMPLETION               Completion;
  EFI_STATUS                               Status;

  ZeroMem (&CommandPacket, sizeof (EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Command, sizeof (EFI_NVM_EXPRESS_COMMAND));
  ZeroMem (&Completion, sizeof (EFI_NVM_EXPRESS_COMPLETION));

  Command.Cdw0.Opcode = NVME_ADMIN_IDENTIFY_CMD;

  //
  // According to Nvm Express 1.1 spec Figure 38, When not used, the field shall be cleared to 0h.
  // For the Identify command, the Namespace Identifier is only used for the Namespace data structure.
  //
  Command.Nsid        = 0;

  CommandPacket.NvmeCmd        = &Command;
  CommandPacket.NvmeCompletion = &Completion;
  CommandPacket.TransferBuffer = Buffer;
  CommandPacket.TransferLength = sizeof (NVME_ADMIN_CONTROLLER_DATA);
  CommandPacket.CommandTimeout = NVME_GENERIC_TIMEOUT;
  CommandPacket.QueueType      = NVME_ADMIN_QUEUE;
  //
  // Set bit 0 (Cns bit) to 1 to identify a controller
  //
  Command.Cdw10                = 1;
  Command.Flags                = CDW10_VALID;

  Status = Private->Passthru.PassThru (
                               &Private->Passthru,
                               0,
                               &CommandPacket
                               );

  DEBUG ((DEBUG_INFO, "NvmeIdentifyController status:%r\n", Status));
  return Status;
}

/**
  Create io completion queue.

  @param[in]  Private              The pointer to the PEI_NVME_CONTROLLER_PRIVATE_DATA data structure.

  @retval     EFI_SUCCESS          Successfully create io completion queue.
  @retval     EFI_DEVICE_ERROR     Fail to create io completion queue.

**/
EFI_STATUS
NvmeCreateIoCompletionQueue (
  IN PEI_NVME_CONTROLLER_PRIVATE_DATA      *Private
  )
{
  EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET CommandPacket;
  EFI_NVM_EXPRESS_COMMAND                  Command;
  EFI_NVM_EXPRESS_COMPLETION               Completion;
  EFI_STATUS                               Status;
  NVME_ADMIN_CRIOCQ                        CrIoCq;

  ZeroMem (&CommandPacket, sizeof (EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Command, sizeof (EFI_NVM_EXPRESS_COMMAND));
  ZeroMem (&Completion, sizeof (EFI_NVM_EXPRESS_COMPLETION));
  ZeroMem (&CrIoCq, sizeof (NVME_ADMIN_CRIOCQ));

  CommandPacket.NvmeCmd        = &Command;
  CommandPacket.NvmeCompletion = &Completion;

  Command.Cdw0.Opcode = NVME_ADMIN_CRIOCQ_CMD;
  CommandPacket.TransferBuffer = Private->CqBuffer[1];
  CommandPacket.TransferLength = EFI_PAGE_SIZE;
  CommandPacket.CommandTimeout = NVME_GENERIC_TIMEOUT;
  CommandPacket.QueueType      = NVME_ADMIN_QUEUE;

  CrIoCq.Qid   = NVME_IO_QUEUE;
  CrIoCq.Qsize = NVME_CCQ_SIZE;
  CrIoCq.Pc    = 1;
  CopyMem (&CommandPacket.NvmeCmd->Cdw10, &CrIoCq, sizeof (NVME_ADMIN_CRIOCQ));
  CommandPacket.NvmeCmd->Flags = CDW10_VALID | CDW11_VALID;

  Status = Private->Passthru.PassThru (
                               &Private->Passthru,
                               0,
                               &CommandPacket
                               );

  return Status;
}

/**
  Create io submission queue.

  @param[in]  Private              The pointer to the PEI_NVME_CONTROLLER_PRIVATE_DATA data structure.

  @retval     EFI_SUCCESS          Successfully create io submission queue.
  @retval     EFI_DEVICE_ERROR     Fail to create io submission queue.

**/
EFI_STATUS
NvmeCreateIoSubmissionQueue (
  IN PEI_NVME_CONTROLLER_PRIVATE_DATA      *Private
  )
{
  EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET CommandPacket;
  EFI_NVM_EXPRESS_COMMAND                  Command;
  EFI_NVM_EXPRESS_COMPLETION               Completion;
  EFI_STATUS                               Status;
  NVME_ADMIN_CRIOSQ                        CrIoSq;

  ZeroMem (&CommandPacket, sizeof(EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET));
  ZeroMem (&Command, sizeof(EFI_NVM_EXPRESS_COMMAND));
  ZeroMem (&Completion, sizeof(EFI_NVM_EXPRESS_COMPLETION));
  ZeroMem (&CrIoSq, sizeof(NVME_ADMIN_CRIOSQ));

  CommandPacket.NvmeCmd        = &Command;
  CommandPacket.NvmeCompletion = &Completion;

  Command.Cdw0.Opcode = NVME_ADMIN_CRIOSQ_CMD;
  CommandPacket.TransferBuffer = Private->SqBuffer[1];
  CommandPacket.TransferLength = EFI_PAGE_SIZE;
  CommandPacket.CommandTimeout = NVME_GENERIC_TIMEOUT;
  CommandPacket.QueueType      = NVME_ADMIN_QUEUE;

  CrIoSq.Qid   = NVME_IO_QUEUE;
  CrIoSq.Qsize = NVME_CSQ_SIZE;
  CrIoSq.Pc    = 1;
  CrIoSq.Cqid  = NVME_IO_QUEUE;
  CrIoSq.Qprio = 0;
  CopyMem (&CommandPacket.NvmeCmd->Cdw10, &CrIoSq, sizeof (NVME_ADMIN_CRIOSQ));
  CommandPacket.NvmeCmd->Flags = CDW10_VALID | CDW11_VALID;

  Status = Private->Passthru.PassThru (
                               &Private->Passthru,
                               0,
                               &CommandPacket
                               );

  return Status;
}

/**
  Wait for NVME controller status to be ready or not.

  @param[in] Private                The pointer to PEI_NVME_CONTROLLER_PRIVATE_DATA data structure.
  @param[in] WaitReady              Flag for waitting status ready or not

  @retval    EFI_SUCCESS            Successfully to wait specific status.
  @retval    others                 Fail to wait for specific controller status.

**/
STATIC
EFI_STATUS
NvmeWaitController (
  IN PEI_NVME_CONTROLLER_PRIVATE_DATA     *Private,
  IN BOOLEAN                              WaitReady
  )
{
  NVME_CSTS              Csts;
  EFI_STATUS             Status;
  UINT32                 Index;
  UINT8                  Timeout;

  //
  // Cap.To specifies max delay time in 500ms increments for Csts.Rdy to transition from 1 to 0 after
  // Cc.Enable transition from 1 to 0. Loop produces a 1 millisecond delay per itteration, up to 500 * Cap.To.
  //
  if (Private->Cap.To == 0) {
    Timeout = 1;
  } else {
    Timeout = Private->Cap.To;
  }

  Status = EFI_SUCCESS;
  for (Index = (Timeout * 500); Index != 0; --Index) {
    MicroSecondDelay (1000);

    //
    // Check if the controller is initialized
    //
    Status = NVME_GET_CSTS (Private->MmioBase, &Csts);
    if (EFI_ERROR(Status)) {
      DEBUG ((DEBUG_ERROR, "NVME_GET_CSTS fail, Status = %r\n", Status));
      return Status;
    }

    if ((BOOLEAN) Csts.Rdy == WaitReady) {
      break;
    }
  }

  if (Index == 0) {
    Status = EFI_TIMEOUT;
  }

  DEBUG ((DEBUG_INFO, "NVMe controller is disabled with status [%r].\n", Status));
  return Status;
}

/**
  Disable the Nvm Express controller.

  @param[in]  Private              The pointer to the NVME_CONTROLLER_PRIVATE_DATA data structure.

  @retval     EFI_SUCCESS          Successfully disable the controller.
  @retval     EFI_DEVICE_ERROR     Fail to disable the controller.

**/
EFI_STATUS
NvmeDisableController (
  IN PEI_NVME_CONTROLLER_PRIVATE_DATA     *Private
  )
{
  EFI_STATUS             Status;
  NVME_CC                Cc;
  NVME_CSTS              Csts;
  UINTN                  NBar;

  Status = EFI_SUCCESS;

  NBar = Private->MmioBase;

  Status = NVME_GET_CSTS (NBar, &Csts);

  //
  // Read Controller Configuration Register.
  //
  Status = NVME_GET_CC (NBar, &Cc);
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "NVME_GET_CC fail, Status = %r\n", Status));
    goto Done;
  }

  Cc.En = 0;
  //
  // Disable the controller.
  //
  Status = NVME_SET_CC (NBar, &Cc);
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "NVME_SET_CC fail, Status = %r\n", Status));
    goto Done;
  }

  Status = NvmeWaitController (Private, FALSE);
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "NvmeWaitController fail, Status = %r\n", Status));
    goto Done;
  }

Done:

  return Status;
}

/**
  Enable the Nvm Express controller.

  @param[in]  Private              The pointer to the PEI_NVME_CONTROLLER_PRIVATE_DATA data structure.

  @retval     EFI_SUCCESS          Successfully enable the controller.
  @retval     EFI_DEVICE_ERROR     Fail to enable the controller.
  @retval     EFI_TIMEOUT          Fail to enable the controller in given time slot.

**/
EFI_STATUS
NvmeEnableController (
  IN PEI_NVME_CONTROLLER_PRIVATE_DATA     *Private
  )
{
  NVME_CC                Cc;
  EFI_STATUS             Status;
  UINTN                  NBar;

  NBar = Private->MmioBase;

  //
  // Enable the controller.
  // CC.AMS, CC.MPS and CC.CSS are all set to 0.
  //
  ZeroMem (&Cc, sizeof (NVME_CC));
  Cc.En     = 1;
  Cc.Iosqes = 6;
  Cc.Iocqes = 4;

  Status = NVME_SET_CC (NBar, &Cc);
  if (EFI_ERROR(Status)) {
    DEBUG ((DEBUG_ERROR, "NVME_SET_CC fail, Status = %r\n", Status));
    return Status;
  }

  Status = NvmeWaitController (Private, TRUE);

  DEBUG ((DEBUG_INFO, "NVMe controller is enabled with status [%r].\n", Status));
  return Status;
}

/**
  Initialize the Nvm Express controller.

  @param[in] Private                   The pointer to the PEI_NVME_CONTROLLER_PRIVATE_DATA Data structure.

  @retval    EFI_SUCCESS               The NVM Express Controller is initialized successfully.
  @retval    Others                    A device error occurred while initializing the controller.

**/
EFI_STATUS
NvmeControllerInit (
  IN PEI_NVME_CONTROLLER_PRIVATE_DATA       *Private
  )
{
  EFI_STATUS            Status;
  NVME_AQA              Aqa;
  NVME_ASQ              Asq;
  NVME_ACQ              Acq;
  NVME_VER              Ver;
  UINTN                 NBar;

  NBar = Private->MmioBase;

  // Version
  NVME_GET_VER (Private->MmioBase, &Ver);
  DEBUG ((DEBUG_INFO, "NVME Version: %d.%d\n", Ver.Mnr, Ver.Mjr));

  //
  // Read the Controller Capabilities register and verify that the NVM command set is supported
  //
  Status = NVME_GET_CAP (NBar, &Private->Cap);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "NVME_GET_CAP fail, Status: %r\n", Status));
    return Status;
  }

  if (Private->Cap.Css != 0x01) {
    DEBUG ((DEBUG_INFO, "PEI NvmeControllerInit: the controller doesn't support NVMe command set\n"));
    return EFI_UNSUPPORTED;
  }

  //
  // Currently the driver only supports 4k page size.
  //
  if ((Private->Cap.Mpsmin + 12) > EFI_PAGE_SHIFT) {
    DEBUG ((DEBUG_ERROR, "NvmeControllerInit fail: only supports 4k page Size\n"));
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  Private->Cid[0] = 0;
  Private->Cid[1] = 0;

  Status = NvmeDisableController (Private);
  DEBUG ((DEBUG_INFO, "NvmeDisableController status: %r\n", Status));

  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // set number of entries admin submission & completion queues.
  //
  Aqa.Asqs  = NVME_ASQ_SIZE;
  Aqa.Rsvd1 = 0;
  Aqa.Acqs  = NVME_ACQ_SIZE;
  Aqa.Rsvd2 = 0;

  //
  // Address of admin submission queue.
  //
  Asq.Rsvd1 = 0;
  Asq.Asqb  = (UINT64)(UINTN)(NVME_ASQ_BASE (Private)) >> 12;

  //
  // Address of admin completion queue.
  //
  Acq.Rsvd1 = 0;
  Acq.Acqb  = (UINT64)(UINTN)(NVME_ACQ_BASE (Private)) >> 12;

  //
  // Address of I/O submission & completion queue.
  //
  Private->SqBuffer[0] = (NVME_SQ *)(UINTN) NVME_ASQ_BASE (Private);   // NVME_ADMIN_QUEUE
  Private->CqBuffer[0] = (NVME_CQ *)(UINTN) NVME_ACQ_BASE (Private);   // NVME_ADMIN_QUEUE
  Private->SqBuffer[1] = (NVME_SQ *)(UINTN) NVME_SQ_BASE (Private, 0); // NVME_IO_QUEUE
  Private->CqBuffer[1] = (NVME_CQ *)(UINTN) NVME_CQ_BASE (Private, 0); // NVME_IO_QUEUE

  DEBUG ((DEBUG_INFO, "Private->Buffer = [%016X]\n", (UINT64)(UINTN)Private->Buffer));
  DEBUG ((DEBUG_INFO, "Admin Submission Queue size (Aqa.Asqs) = [%08X]\n", Aqa.Asqs));
  DEBUG ((DEBUG_INFO, "Admin Completion Queue size (Aqa.Acqs) = [%08X]\n", Aqa.Acqs));
  DEBUG ((DEBUG_INFO, "Admin Submission Queue (SqBuffer[0]) = [%016X]\n", Private->SqBuffer[0]));
  DEBUG ((DEBUG_INFO, "Admin Completion Queue (CqBuffer[0]) = [%016X]\n", Private->CqBuffer[0]));
  DEBUG ((DEBUG_INFO, "I/O   Submission Queue (SqBuffer[1]) = [%016X]\n", Private->SqBuffer[1]));
  DEBUG ((DEBUG_INFO, "I/O   Completion Queue (CqBuffer[1]) = [%016X]\n", Private->CqBuffer[1]));

  //
  // Program admin queue attributes.
  //
  Status = NVME_SET_AQA (NBar, &Aqa);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Program admin submission queue address.
  //
  Status = NVME_SET_ASQ (NBar, &Asq);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Program admin completion queue address.
  //
  Status = NVME_SET_ACQ (NBar, &Acq);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  Status = NvmeEnableController (Private);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Assign buffer for Identify Controller data
  //
  Private->ControllerData = (NVME_ADMIN_CONTROLLER_DATA *)(UINTN) NVME_CONTROL_DATA_BASE (Private);

  //
  // Get current Identify Controller Data
  //
  Status = NvmeIdentifyController (Private, Private->ControllerData);

  if (EFI_ERROR (Status)) {
    Private->ControllerData = NULL;
    DEBUG ((DEBUG_ERROR, "NvmeIdentifyController status: %r\n", Status));
    return EFI_NOT_FOUND;
  }

  //
  // Dump NvmExpress Identify Controller Data
  //
  Private->ControllerData->Sn[19] = 0;
  Private->ControllerData->Mn[39] = 0;
  DEBUG ((DEBUG_INFO, " == NVME IDENTIFY CONTROLLER DATA ==\n"));
  DEBUG ((DEBUG_INFO, "    PCI VID   : 0x%x\n", Private->ControllerData->Vid));
  DEBUG ((DEBUG_INFO, "    PCI SSVID : 0x%x\n", Private->ControllerData->Ssvid));
  DEBUG ((DEBUG_INFO, "    SN        : %a\n",   (CHAR8 *)(Private->ControllerData->Sn)));
  DEBUG ((DEBUG_INFO, "    MN        : %a\n",   (CHAR8 *)(Private->ControllerData->Mn)));
  DEBUG ((DEBUG_INFO, "    FR        : 0x%x\n", *((UINT64*)Private->ControllerData->Fr)));
  DEBUG ((DEBUG_INFO, "    RAB       : 0x%x\n", Private->ControllerData->Rab));
  DEBUG ((DEBUG_INFO, "    IEEE      : 0x%x\n", *(UINT32*)Private->ControllerData->Ieee_oui));
  DEBUG ((DEBUG_INFO, "    AERL      : 0x%x\n", Private->ControllerData->Aerl));
  DEBUG ((DEBUG_INFO, "    SQES      : 0x%x\n", Private->ControllerData->Sqes));
  DEBUG ((DEBUG_INFO, "    CQES      : 0x%x\n", Private->ControllerData->Cqes));
  DEBUG ((DEBUG_INFO, "    NN        : 0x%x\n", Private->ControllerData->Nn));

  //
  // Create one I/O completion queue.
  //
  Status = NvmeCreateIoCompletionQueue (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "NvmeCreateIoCompletionQueue status: %r\n", Status));
    return Status;
  }

  //
  // Create one I/O Submission queue.
  //
  Status = NvmeCreateIoSubmissionQueue (Private);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "NvmeCreateIoSubmissionQueue status: %r\n", Status));
    return Status;
  }
  return Status;
}

/**
  Gets the count of block I/O devices that one specific block driver detects.

  This function is used for getting the count of block I/O devices that one
  specific block driver detects. If no device is detected,
  then the function will return zero.

  @param[in]  PeiServices          General-purpose services that are available
                                   to every PEIM.
  @param[in]  This                 Indicates the EFI_PEI_RECOVERY_BLOCK_IO_PPI
                                   instance.
  @param[out] NumberBlockDevices   The number of block I/O devices discovered.

  @retval     EFI_SUCCESS          The operation performed successfully.

**/
EFI_STATUS
EFIAPI
NvmeGetNumberOfBlockDevices (
  IN   EFI_PEI_SERVICES                  **PeiServices,
  IN   EFI_PEI_RECOVERY_BLOCK_IO_PPI     *This,
  OUT  UINTN                             *NumberBlockDevices
  )
{

  *NumberBlockDevices = 1;

  return EFI_SUCCESS;
}

/**
  Gets a block device's media information.

  This function will provide the caller with the specified block device's media
  information. If the media changes, calling this function will update the media
  information accordingly.

  @param[in]  PeiServices   General-purpose services that are available to every
                            PEIM
  @param[in]  This          Indicates the EFI_PEI_RECOVERY_BLOCK_IO_PPI instance.
  @param[in]  DeviceIndex   Specifies the block device to which the function wants
                            to talk. Because the driver that implements Block I/O
                            PPIs will manage multiple block devices, the PPIs that
                            want to talk to a single device must specify the
                            device index that was assigned during the enumeration
                            process. This index is a number from one to
                            NumberBlockDevices.
  @param[out] MediaInfo     The media information of the specified block media.
                            The caller is responsible for the ownership of this
                            data structure.

  @retval EFI_SUCCESS       Media information about the specified block device
                            was obtained successfully.
  @retval Others            Other failure occurs.

**/
EFI_STATUS
EFIAPI
NvmeGetBlockDeviceMediaInfo (
  IN   EFI_PEI_SERVICES                     **PeiServices,
  IN   EFI_PEI_RECOVERY_BLOCK_IO_PPI        *This,
  IN   UINTN                                DeviceIndex,
  OUT  EFI_PEI_BLOCK_IO_MEDIA               *MediaInfo
  )
{
  PEI_NVME_DEVICE_PRIVATE_DATA      *Device;

  if (This == NULL || MediaInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Device = PEI_NVME_DEVICE_PRIVATE_DATA_FROM_BLOCK_IO (This);
  CopyMem (MediaInfo, &Device->Media, sizeof (EFI_PEI_BLOCK_IO_MEDIA));

  return EFI_SUCCESS;
}

/**
  Reads the requested number of blocks from NVME block device.

  The function reads the requested number of blocks from the device. All the
  blocks are read, or an error is returned. If there is no media in the device,
  the function returns EFI_NO_MEDIA.

  @param[in]  PeiServices   General-purpose services that are available to
                            every PEIM.
  @param[in]  This          Indicates the EFI_PEI_RECOVERY_BLOCK_IO_PPI instance.
  @param[in]  DeviceIndex   Specifies the block device to which the function wants
                            to talk. Because the driver that implements Block I/O
                            PPIs will manage multiple block devices, PPIs that
                            want to talk to a single device must specify the device
                            index that was assigned during the enumeration process.
                            This index is a number from one to NumberBlockDevices.
  @param[in]  StartLBA      The starting logical block address (LBA) to read from
                            on the device
  @param[in]  BufferSize    The size of the Buffer in bytes. This number must be
                            a multiple of the intrinsic block size of the device.
  @param[out] Buffer        A pointer to the destination buffer for the data.
                            The caller is responsible for the ownership of the
                            buffer.

  @retval EFI_SUCCESS             The data was read correctly from the device.
  @retval EFI_DEVICE_ERROR        The device reported an error while attempting
                                  to perform the read operation.
  @retval EFI_INVALID_PARAMETER   The read request contains LBAs that are not
                                  valid, or the buffer is not properly aligned.
  @retval EFI_NO_MEDIA            There is no media in the device.
  @retval EFI_BAD_BUFFER_SIZE     The BufferSize parameter is not a multiple of
                                  the intrinsic block size of the device.

**/
EFI_STATUS
EFIAPI
NvmeBlockIoRead (
  IN  EFI_PEI_SERVICES               **PeiServices,
  IN  EFI_PEI_RECOVERY_BLOCK_IO_PPI  *This,
  IN  UINTN                          DeviceIndex,
  IN  EFI_PEI_LBA                    StartLBA,
  IN  UINTN                          BufferSize,
  OUT VOID                           *Buffer
  )
{
  PEI_NVME_DEVICE_PRIVATE_DATA      *Device;
  UINTN                             BlockSize;
  UINTN                             NumberOfBlocks;

  //
  // Check parameters.
  //
  if (This == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (Buffer == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  if (BufferSize == 0) {
    return EFI_SUCCESS;
  }

  Device = PEI_NVME_DEVICE_PRIVATE_DATA_FROM_BLOCK_IO (This);

  BlockSize = Device->Media.BlockSize;
  if ((BufferSize % BlockSize) != 0) {
    DEBUG ((DEBUG_ERROR, "EFI_BAD_BUFFER_SIZr\n"));
    return EFI_BAD_BUFFER_SIZE;
  }

  NumberOfBlocks  = BufferSize / BlockSize;
  if ((StartLBA + NumberOfBlocks - 1) > Device->Media.LastBlock) {
    DEBUG ((DEBUG_ERROR, "out of range\n"));
    return EFI_INVALID_PARAMETER;
  }

  return NvmeRead (Device, Buffer, (UINTN)StartLBA, NumberOfBlocks);
}

/**
  Gets the count of block I/O devices that one specific block driver detects.

  This function is used for getting the count of block I/O devices that one
  specific block driver detects. If no device is detected, then the function
  will return zero.

  @param[in]  PeiServices          General-purpose services that are available
                                   to every PEIM.
  @param[in]  This                 Indicates the EFI_PEI_RECOVERY_BLOCK_IO2_PPI
                                   instance.
  @param[out] NumberBlockDevices   The number of block I/O devices discovered.

  @retval     EFI_SUCCESS          The operation performed successfully.

**/
EFI_STATUS
EFIAPI
NvmeGetNumberOfBlockDevices2 (
  IN   EFI_PEI_SERVICES                  **PeiServices,
  IN   EFI_PEI_RECOVERY_BLOCK_IO2_PPI    *This,
  OUT  UINTN                             *NumberBlockDevices
  )
{
  *NumberBlockDevices = 1;

  return EFI_SUCCESS;
}

/**
  Gets a block device's media information.

  This function will provide the caller with the specified block device's media
  information. If the media changes, calling this function will update the media
  information accordingly.

  @param[in]  PeiServices   General-purpose services that are available to every
                            PEIM
  @param[in]  This          Indicates the EFI_PEI_RECOVERY_BLOCK_IO2_PPI instance.
  @param[in]  DeviceIndex   Specifies the block device to which the function wants
                            to talk. Because the driver that implements Block I/O
                            PPIs will manage multiple block devices, the PPIs that
                            want to talk to a single device must specify the
                            device index that was assigned during the enumeration
                            process. This index is a number from one to
                            NumberBlockDevices.
  @param[out] MediaInfo     The media information of the specified block media.
                            The caller is responsible for the ownership of this
                            data structure.

  @retval EFI_SUCCESS       Media information about the specified block device
                            was obtained successfully.
  @retval Others            Other failure occurs.

**/
EFI_STATUS
EFIAPI
NvmeGetBlockDeviceMediaInfo2 (
  IN   EFI_PEI_SERVICES                     **PeiServices,
  IN   EFI_PEI_RECOVERY_BLOCK_IO2_PPI       *This,
  IN   UINTN                                DeviceIndex,
  OUT  EFI_PEI_BLOCK_IO2_MEDIA              *MediaInfo
  )
{
  PEI_NVME_DEVICE_PRIVATE_DATA      *Device;

  if (This == NULL || MediaInfo == NULL) {
    return EFI_INVALID_PARAMETER;
  }

  Device = PEI_NVME_DEVICE_PRIVATE_DATA_FROM_BLOCK_IO2 (This);
  CopyMem (MediaInfo, &Device->Media2, sizeof (EFI_PEI_BLOCK_IO2_MEDIA));

  return EFI_SUCCESS;
}

/**
  Reads the requested number of blocks from NVME block device.

  The function reads the requested number of blocks from the device. All the
  blocks are read, or an error is returned. If there is no media in the device,
  the function returns EFI_NO_MEDIA.

  @param[in]  PeiServices   General-purpose services that are available to
                            every PEIM.
  @param[in]  This          Indicates the EFI_PEI_RECOVERY_BLOCK_IO2_PPI instance.
  @param[in]  DeviceIndex   Specifies the block device to which the function wants
                            to talk. Because the driver that implements Block I/O
                            PPIs will manage multiple block devices, PPIs that
                            want to talk to a single device must specify the device
                            index that was assigned during the enumeration process.
                            This index is a number from one to NumberBlockDevices.
  @param[in]  StartLBA      The starting logical block address (LBA) to read from
                            on the device
  @param[in]  BufferSize    The size of the Buffer in bytes. This number must be
                            a multiple of the intrinsic block size of the device.
  @param[out] Buffer        A pointer to the destination buffer for the data.
                            The caller is responsible for the ownership of the
                            buffer.

  @retval EFI_SUCCESS             The data was read correctly from the device.
  @retval EFI_DEVICE_ERROR        The device reported an error while attempting
                                  to perform the read operation.
  @retval EFI_INVALID_PARAMETER   The read request contains LBAs that are not
                                  valid, or the buffer is not properly aligned.
  @retval EFI_NO_MEDIA            There is no media in the device.
  @retval EFI_BAD_BUFFER_SIZE     The BufferSize parameter is not a multiple of
                                  the intrinsic block size of the device.

**/
EFI_STATUS
EFIAPI
NvmeBlockIo2Read (
  IN  EFI_PEI_SERVICES               **PeiServices,
  IN  EFI_PEI_RECOVERY_BLOCK_IO2_PPI *This,
  IN  UINTN                          DeviceIndex,
  IN  EFI_PEI_LBA                    StartLBA,
  IN  UINTN                          BufferSize,
  OUT VOID                           *Buffer
  )
{
  PEI_NVME_DEVICE_PRIVATE_DATA      *Device;
  EFI_STATUS                        Status;

  Device = PEI_NVME_DEVICE_PRIVATE_DATA_FROM_BLOCK_IO2 (This);

  Status = NvmeBlockIoRead (
             PeiServices,
             &Device->BlockIoPpi,
             DeviceIndex,
             StartLBA,
             BufferSize,
             Buffer
             );

  return Status;
}

/**
  Check if the specified Nvm Express device namespace is valid and active.
  If yes, install VirtualBlockIo/VirtualBlockIo2 PPIs for the namespace.

  @param[in] Private         The pointer to the NVME_CONTROLLER_PRIVATE_DATA data structure.
  @param[in] NamespaceId     The NVM Express namespace ID.

  @retval    EFI_SUCCESS     The namespace of specified NamespaceId in the device is successfully enumerated.
  @return    Others          Some error occurs when enumerating the namespace.

**/
EFI_STATUS
EnumerateNvmeDevNamespace (
  IN PEI_NVME_CONTROLLER_PRIVATE_DATA       *Private,
  UINT32                                    NamespaceId
  )
{
  NVME_ADMIN_NAMESPACE_DATA             *NamespaceData;
  PEI_NVME_DEVICE_PRIVATE_DATA          *Device;
  EFI_STATUS                            Status;
  UINT32                                Lbads;
  UINT32                                Flbas;
  UINT32                                LbaFmtIdx;

  DEBUG ((DEBUG_INFO, "Start to enumerate namespace %d\n", NamespaceId));

  Device = NULL;

  NamespaceData = (NVME_ADMIN_NAMESPACE_DATA *) NVME_NAMESPACE_DATA_BASE (Private);
  ZeroMem ((VOID *) NamespaceData, sizeof (NVME_ADMIN_NAMESPACE_DATA));

  //
  // Identify Namespace
  //
  Status = NvmeIdentifyNamespace (
             Private,
             NamespaceId,
             (VOID *) NamespaceData
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "NvmeIdentifyNamespace failed: %r\n", Status));
    goto Exit;
  }

  //
  // Validate Namespace
  //
  if (NamespaceData->Ncap == 0) {
    DEBUG ((DEBUG_INFO, "Ncap = 0\n"));
    Status = EFI_DEVICE_ERROR;
  } else {
    //
    // Dump NvmExpress Identify Namespace Data
    //
    DEBUG ((DEBUG_INFO, " == NVME IDENTIFY NAMESPACE [%d] DATA ==\n", NamespaceId));
    DEBUG ((DEBUG_INFO, "    NSZE        : 0x%x\n", NamespaceData->Nsze));
    DEBUG ((DEBUG_INFO, "    NCAP        : 0x%x\n", NamespaceData->Ncap));
    DEBUG ((DEBUG_INFO, "    NUSE        : 0x%x\n", NamespaceData->Nuse));
    DEBUG ((DEBUG_INFO, "    LBAF0.LBADS : 0x%x\n", (NamespaceData->LbaFormat[0].Lbads)));

    //
    // allocate device private data for each discovered namespace
    //
    Device = (PEI_NVME_DEVICE_PRIVATE_DATA *) AllocateZeroPool (sizeof (PEI_NVME_DEVICE_PRIVATE_DATA));
    if (Device == NULL) {
      DEBUG ((DEBUG_ERROR, "Failed to allocate memory for PEI_NVME_DEVICE_PRIVATE_DATA! \n"));
      goto Exit;
    }

    //
    // Initialize SSD namespace instance data
    //
    Device->Signature          = PEI_NVME_DEVICE_PRIVATE_DATA_SIGNATURE;
    Device->NamespaceId        = NamespaceId;
    Device->NamespaceUuid      = NamespaceData->Eui64;

    Device->Controller         = Private;

    //
    // Build BlockIo media structure
    //
    Device->Media.MediaPresent = TRUE;
    Device->Media.DeviceType   = MaxDeviceType; // no match type defined in BlockIo.h

    Flbas     = NamespaceData->Flbas;
    LbaFmtIdx = Flbas & 0xF;
    Lbads     = NamespaceData->LbaFormat[LbaFmtIdx].Lbads;
    Device->Media.BlockSize = (UINT32) 1 << Lbads;

    Device->Media.LastBlock     = (UINTN) NamespaceData->Nsze - 1;
    DEBUG ((DEBUG_INFO, "Device->Media.BlockSize: 0x%x\n", Device->Media.BlockSize));
    DEBUG ((DEBUG_INFO, "Device->Media.LastBlock: 0x%x\n", Device->Media.LastBlock));

    //
    // Create BlockIo Protocol instance
    //
    Device->BlockIoPpi.GetBlockDeviceMediaInfo = NvmeGetBlockDeviceMediaInfo;
    Device->BlockIoPpi.GetNumberOfBlockDevices = NvmeGetNumberOfBlockDevices;
    Device->BlockIoPpi.ReadBlocks              = NvmeBlockIoRead;

    Device->BlockIoPpiDescriptor.Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
    Device->BlockIoPpiDescriptor.Guid  = &gEfiPeiVirtualBlockIoPpiGuid;
    Device->BlockIoPpiDescriptor.Ppi   = &Device->BlockIoPpi;

    Status = PeiServicesInstallPpi (&Device->BlockIoPpiDescriptor);
    ASSERT_EFI_ERROR (Status);

    //
    // Build BlockIo2 media structure
    //
    Device->Media2.InterfaceType  = MSG_NVME_NAMESPACE_DP;
    Device->Media2.MediaPresent   = TRUE;
    Device->Media2.ReadOnly       = FALSE;
    Device->Media2.RemovableMedia = FALSE;
    Device->Media2.BlockSize      = Device->Media.BlockSize;
    Device->Media2.LastBlock      = Device->Media.LastBlock;

    //
    // Create BlockIo2 Protocol instance
    //
    Device->BlockIo2Ppi.Revision = EFI_PEI_RECOVERY_BLOCK_IO2_PPI_REVISION;
    Device->BlockIo2Ppi.GetBlockDeviceMediaInfo = NvmeGetBlockDeviceMediaInfo2;
    Device->BlockIo2Ppi.GetNumberOfBlockDevices = NvmeGetNumberOfBlockDevices2;
    Device->BlockIo2Ppi.ReadBlocks              = NvmeBlockIo2Read;

    Device->BlockIo2PpiDescriptor.Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
    Device->BlockIo2PpiDescriptor.Guid  = &gEfiPeiVirtualBlockIo2PpiGuid;
    Device->BlockIo2PpiDescriptor.Ppi   = &Device->BlockIo2Ppi;

    Status = PeiServicesInstallPpi (&Device->BlockIo2PpiDescriptor);
    ASSERT_EFI_ERROR (Status);

  }

Exit:

  return Status;
}

/**
  Sends an NVM Express Command Packet to an NVM Express controller or namespace.

  @param[in]     This                A pointer to the NVM_EXPRESS_PASS_THRU_PPI instance.
  @param[in]     NamespaceId         A 32 bit namespace ID as defined in the NVMe specification to which the NVM Express Command
                                     Packet will be sent.  A value of 0 denotes the NVM Express controller, a value of all 0xFF's
                                     (all bytes are 0xFF) in the namespace ID specifies that the command packet should be sent to
                                     all valid namespaces.
  @param[in,out] Packet              A pointer to the NVM Express Command Packet.

  @retval EFI_SUCCESS                The NVM Express Command Packet was sent by the host. TransferLength bytes were transferred
                                     to, or from DataBuffer.
  @retval EFI_DEVICE_ERROR           A device error occurred while attempting to send the NVM Express Command Packet.
  @retval EFI_INVALID_PARAMETER      NamespaceId or the contents of EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET are invalid. The NVM
                                     Express Command Packet was not sent, so no additional status information is available.
  @retval EFI_UNSUPPORTED            The command described by the NVM Express Command Packet is not supported by the NVM Express
                                     controller. The NVM Express Command Packet was not sent so no additional status information
                                     is available.
  @retval EFI_TIMEOUT                A timeout occurred while waiting for the NVM Express Command Packet to execute.

**/
EFI_STATUS
EFIAPI
NvmExpressPassThru (
  IN     NVM_EXPRESS_PASS_THRU_PPI                   *This,
  IN     UINT32                                      NamespaceId,
  IN OUT EFI_NVM_EXPRESS_PASS_THRU_COMMAND_PACKET    *Packet
  )
{
  PEI_NVME_CONTROLLER_PRIVATE_DATA       *Private;
  EFI_STATUS                             Status;
  NVME_SQ                                *Sq;
  NVME_CQ                                *Cq;
  UINT8                                  QueueType;
  UINT32                                 Bytes;
  UINT16                                 Offset;
  EFI_PHYSICAL_ADDRESS                   PhyAddr;
  UINT64                                 *Prp;
  VOID                                   *PrpListHost;
  UINTN                                  PrpListNo;
  UINT32                                 Data;
  UINT32                                 Timer;

  //
  // check the data fields in Packet parameter.
  //
  if ((This == NULL) || (Packet == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if ((Packet->NvmeCmd == NULL) || (Packet->NvmeCompletion == NULL)) {
    return EFI_INVALID_PARAMETER;
  }

  if (Packet->QueueType != NVME_ADMIN_QUEUE && Packet->QueueType != NVME_IO_QUEUE) {
    return EFI_INVALID_PARAMETER;
  }

  Private     = PEI_NVME_CONTROLLER_PRIVATE_DATA_FROM_PASS_THRU (This);
  PrpListHost = NULL;
  PrpListNo   = 0;
  Prp         = NULL;
  Status      = EFI_SUCCESS;

  QueueType = Packet->QueueType;
  Sq  = Private->SqBuffer[QueueType] + Private->SqTdbl[QueueType].Sqt;
  Cq  = Private->CqBuffer[QueueType] + Private->CqHdbl[QueueType].Cqh;

  if (Packet->NvmeCmd->Nsid != NamespaceId) {
    DEBUG ((DEBUG_ERROR, "NvmePassThru: Nsid mismatch (%x, %x)\n", Packet->NvmeCmd->Nsid, NamespaceId));
    return EFI_INVALID_PARAMETER;
  }

  ZeroMem (Sq, sizeof (NVME_SQ));
  Sq->Opc  = (UINT8)Packet->NvmeCmd->Cdw0.Opcode;
  Sq->Fuse = (UINT8)Packet->NvmeCmd->Cdw0.FusedOperation;
  Sq->Cid  = Private->Cid[QueueType]++;
  Sq->Nsid = Packet->NvmeCmd->Nsid;

  //
  // Currently we only support PRP for data transfer, SGL is NOT supported.
  //
  ASSERT (Sq->Psdt == 0);
  if (Sq->Psdt != 0) {
    DEBUG ((DEBUG_ERROR, "NvmExpressPassThru: doesn't support SGL mechanism\n"));
    return EFI_UNSUPPORTED;
  }

  Sq->Prp[0] = (UINT64)(UINTN)Packet->TransferBuffer;
  Sq->Prp[1] = 0;

  if (Packet->MetadataBuffer != NULL) {
    Sq->Mptr = (UINT64)(UINTN)Packet->MetadataBuffer;
  }

  //
  // If the buffer size spans more than two memory pages (page size as defined in CC.Mps),
  // then build a PRP list in the second PRP submission queue entry.
  //
  Offset = ((UINT16)Sq->Prp[0]) & (EFI_PAGE_SIZE - 1);
  Bytes  = Packet->TransferLength;

  if ((Offset + Bytes) > (EFI_PAGE_SIZE * 2)) {
    //
    // Create PrpList for remaining data buffer.
    //
    PhyAddr = (Sq->Prp[0] + EFI_PAGE_SIZE) & ~(EFI_PAGE_SIZE - 1);
    Prp = NvmeCreatePrpList (Private, Private->SqTdbl[QueueType].Sqt, PhyAddr, EFI_SIZE_TO_PAGES (Offset + Bytes) - 1, &PrpListHost, &PrpListNo);

    if (Prp == NULL) {
      DEBUG ((DEBUG_ERROR, "NvmExpressPassThru: NvmeCreatePrpList results a NULL pointer\n"));
      return EFI_OUT_OF_RESOURCES;
    }
    Sq->Prp[1] = (UINT64)(UINTN)Prp;
  } else if ((Offset + Bytes) > EFI_PAGE_SIZE) {
    Sq->Prp[1] = (Sq->Prp[0] + EFI_PAGE_SIZE) & ~(EFI_PAGE_SIZE - 1);
  }

  if(Packet->NvmeCmd->Flags & CDW2_VALID) {
    Sq->Rsvd2 = (UINT64)Packet->NvmeCmd->Cdw2;
  }
  if(Packet->NvmeCmd->Flags & CDW3_VALID) {
    Sq->Rsvd2 |= LShiftU64 ((UINT64)Packet->NvmeCmd->Cdw3, 32);
  }
  if(Packet->NvmeCmd->Flags & CDW10_VALID) {
    Sq->Payload.Raw.Cdw10 = Packet->NvmeCmd->Cdw10;
  }
  if(Packet->NvmeCmd->Flags & CDW11_VALID) {
    Sq->Payload.Raw.Cdw11 = Packet->NvmeCmd->Cdw11;
  }
  if(Packet->NvmeCmd->Flags & CDW12_VALID) {
    Sq->Payload.Raw.Cdw12 = Packet->NvmeCmd->Cdw12;
  }
  if(Packet->NvmeCmd->Flags & CDW13_VALID) {
    Sq->Payload.Raw.Cdw13 = Packet->NvmeCmd->Cdw13;
  }
  if(Packet->NvmeCmd->Flags & CDW14_VALID) {
    Sq->Payload.Raw.Cdw14 = Packet->NvmeCmd->Cdw14;
  }
  if(Packet->NvmeCmd->Flags & CDW15_VALID) {
    Sq->Payload.Raw.Cdw15 = Packet->NvmeCmd->Cdw15;
  }

  //
  // Ring the submission queue doorbell.
  //
  Private->SqTdbl[QueueType].Sqt ^= 1;
  Data = ReadUnaligned32 ((UINT32*)&Private->SqTdbl[QueueType]);
  Status = NVME_SET_SQTDBL (Private->MmioBase, QueueType, Private->Cap.Dstrd, &Data);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "NVME_SET_SQTDBL fail, Status: %r\n", Status));
    return Status;
  }

  //
  // Wait for completion queue to get filled in.
  //
  Status = EFI_TIMEOUT;
  Timer  = 0;
  while (Timer < NVME_CMD_TIMEOUT) {
    if (Cq->Pt != Private->Pt[QueueType]) {
      Status = EFI_SUCCESS;
      break;
    }

    MicroSecondDelay (NVME_CMD_WAIT);
    Timer += NVME_CMD_WAIT;
  }

  //
  // Check the NVMe cmd execution result
  //
  if (Status != EFI_TIMEOUT) {
    if ((Cq->Sct == 0) && (Cq->Sc == 0)) {
      Status = EFI_SUCCESS;
    } else {
      DEBUG ((DEBUG_ERROR, "NvmExpressPassThru: cmd completion: EFI_DEVICE_ERROR\n"));
      Status = EFI_DEVICE_ERROR;
      //
      // Copy the Respose Queue entry for this command to the callers response buffer
      //
      CopyMem (Packet->NvmeCompletion, Cq, sizeof(EFI_NVM_EXPRESS_COMPLETION));

      //
      // Dump every completion entry status for debugging.
      //
      DEBUG_CODE_BEGIN ();
        NvmeDumpStatus (Cq);
      DEBUG_CODE_END ();
    }
  } else {
    DEBUG ((DEBUG_ERROR, "NvmExpressPassThru: Wait for completion queue timeout\n"));
  }

  if ((Private->CqHdbl[QueueType].Cqh ^= 1) == 0) {
    Private->Pt[QueueType] ^= 1;
  }

  Data = ReadUnaligned32 ((UINT32*)&Private->CqHdbl[QueueType]);
  NVME_SET_CQHDBL (Private->MmioBase, QueueType, Private->Cap.Dstrd, &Data);

  return Status;
}

/**
  The entry point for Nvm Express PEIM, used to install Nvm Express Passthru and Virtual BlockIO PPIS.

  @param[in] FileHandle     Handle of the file being invoked.
  @param[in] PeiServices    Describes the list of possible PEI Services.

  @retval    EFI_SUCCESS    PPI successfully installed.

**/
EFI_STATUS
EFIAPI
NvmExpressPeimEntry (
  IN EFI_PEI_FILE_HANDLE    FileHandle,
  IN CONST EFI_PEI_SERVICES **PeiServices
  )
{
  EFI_STATUS                             Status;
  PEI_NVME_CONTROLLER_PPI                *NvmeControllerPpi;
  UINT8                                  Index;
  UINTN                                  BaseAddress;
  PEI_NVME_CONTROLLER_PRIVATE_DATA       *Private;
  UINT8                                  *DmaBuffer;
  UINT32                                 NamespaceId;

  DEBUG ((DEBUG_INFO, "NvmExpressPeim Entry.\n"));

  //
  // Shadow this PEIM to run from memory.
  //
  if (!EFI_ERROR (PeiServicesRegisterForShadow (FileHandle))) {
    return EFI_SUCCESS;
  }

  DEBUG ((DEBUG_INFO, "NvmExpressPeim in shadow.\n"));

  Status = PeiServicesLocatePpi (
             &gPeiNvmExpressControllerPpiGuid,
             0,
             NULL,
             (VOID **) &NvmeControllerPpi
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "NvmExpressPeim failed to locate NvmeControllerPpi.\n"));
    return EFI_UNSUPPORTED;
  }

  Index = 0;
  while (TRUE) {
    Status = NvmeControllerPpi->GetNvmeControllerInfo (
                                  (EFI_PEI_SERVICES **) PeiServices,
                                  NvmeControllerPpi,
                                  Index,
                                  &BaseAddress
                                  );
    //
    // When status is error, it means no controller is found.
    //
    if (EFI_ERROR (Status)) {
      break;
    }

    DEBUG ((DEBUG_INFO, "NvmExpressPeim gets ControllerId %x with MmioBase 0x%x\n", Index, BaseAddress));

    Private = NULL;
    Private = (PEI_NVME_CONTROLLER_PRIVATE_DATA *) AllocateZeroPool (sizeof (PEI_NVME_CONTROLLER_PRIVATE_DATA));
    if (Private == NULL) {
      DEBUG ((DEBUG_ERROR, "No available memory resource for NvmExpressPeim\n"));
      return EFI_OUT_OF_RESOURCES;
    }

    //
    // Allocate pages of memory, then map it for bus master read and write.
    //
    DmaBuffer = NULL;
    DmaBuffer = AllocatePages (NVME_MEM_MAX_PAGE);
    if (DmaBuffer == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    DEBUG ((DEBUG_INFO, "Allocated DMA Buffer: 0x%x\n", DmaBuffer));
    ZeroMem ((VOID *) DmaBuffer, EFI_PAGES_TO_SIZE (NVME_MEM_MAX_PAGE));

    Private->Signature                 = PEI_NVME_CONTROLLER_PRIVATE_DATA_SIGNATURE;
    Private->Buffer                    = DmaBuffer;
    Private->MmioBase                  = BaseAddress;
    Private->Passthru.Mode             = &Private->PassThruMode;
    Private->Passthru.PassThru         = NvmExpressPassThru;
    CopyMem (&Private->PassThruMode, &gEfiNvmExpressPassThruMode, sizeof (PEI_NVM_EXPRESS_PASS_THRU_MODE));

    Status = NvmeControllerInit (Private);
    if (EFI_ERROR (Status)) {
      DEBUG ((DEBUG_ERROR, "NvmExpressPeim ControllerInit failed (%r) on ControllerId %d\n", Status, Index));
      continue;
    }

    //
    // enumerate all namespaces
    //
    for (NamespaceId = 1; NamespaceId <= Private->ControllerData->Nn; NamespaceId++) {
      Status = EnumerateNvmeDevNamespace (Private, NamespaceId);
      if (EFI_ERROR (Status)) {
        DEBUG ((DEBUG_ERROR, "EnumerateNvmeDevNamespace failed (%r) on Namespace %d\n", Status, NamespaceId));
      }
    }

    Private->PassthruPpiDescriptor.Flags = (EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST);
    Private->PassthruPpiDescriptor.Guid  = &gPeiNvmExpressPassThruPpiGuid;
    Private->PassthruPpiDescriptor.Ppi   = &Private->Passthru;

    PeiServicesInstallPpi (&Private->PassthruPpiDescriptor);

    Index++;
  }

  return EFI_SUCCESS;
}

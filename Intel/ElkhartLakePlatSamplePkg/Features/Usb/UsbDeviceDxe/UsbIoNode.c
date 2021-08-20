/** @file
  Header file for XDCI memory node.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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


#include "UsbDeviceDxe.h"


/**
  The SearchNode function search a memory address for record the driver allocate
  memory region and the node to the head link list.

  @param[in]  This              A pointer to the EFI_USBFN_IO_PROTOCOL instance.
  @param[in]  Buffer            The driver alocate memory address.
  @param[out] Node              The match node record of the driver aloocate
                                memory region.
  @param[out] PNode             The pervious match node record of the driver
                                aloocate memory region.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_NOT_FOUND         The memory buffer didn't find.
**/
EFI_STATUS
SearchNode (
  IN  EFI_USBFN_IO_PROTOCOL    *This,
  IN  VOID                     *Buffer,
  OUT USB_MEM_NODE             **Node,
  OUT USB_MEM_NODE             **PNode
  )
{
  USB_XDCI_DEV_CONTEXT *UsbFuncIoDevPtr;
  USB_MEM_NODE         *NodeL;
  USB_MEM_NODE         *PNodeL;
  EFI_STATUS           Status;

  DEBUG ((USB_DEBUG_MEM_NODE_INFO, "SearchNode - Entry\n"));

  UsbFuncIoDevPtr = USBFUIO_CONTEXT_FROM_PROTOCOL(This);
  NodeL = UsbFuncIoDevPtr->FirstNodePtr;
  PNodeL = NULL;
  Status = EFI_NOT_FOUND;

  while (Node != NULL) {
    if (NodeL->AllocatePtr == Buffer) {
      break;
    }

    PNodeL = NodeL;
    NodeL = NodeL->NextPtr;
  }

  if (NodeL != NULL && Node != NULL) {
    *Node = NodeL;
    *PNode = PNodeL;
    Status = EFI_SUCCESS;
  }

  DEBUG ((USB_DEBUG_MEM_NODE_INFO, "SearchNode - Exit %r\n", Status));
  return Status;
}

/**
  The RemoveNode function remove a memory for record the driver allocate
  memory region and the node to the head link list.

  @param[in]  This              A pointer to the EFI_USBFN_IO_PROTOCOL instance.
  @param[in]  Buffer            The driver alocate memory address.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_NOT_FOUND         The memory buffer didn't find.
**/
EFI_STATUS
RemoveNode (
  IN  EFI_USBFN_IO_PROTOCOL    *This,
  IN  VOID                     *Buffer
  )
{
  USB_XDCI_DEV_CONTEXT *UsbFuncIoDevPtr;
  USB_MEM_NODE         *Node;
  USB_MEM_NODE         *PNode;
  EFI_STATUS           Status;

  DEBUG ((USB_DEBUG_MEM_NODE_INFO, "RemoveNode - Entry\n"));

  UsbFuncIoDevPtr = USBFUIO_CONTEXT_FROM_PROTOCOL (This);

  Status = SearchNode (This, Buffer, &Node, &PNode);

  if (EFI_ERROR(Status) || PNode == NULL) {
    DEBUG ((USB_DEBUG_MEM_NODE_ERROR, "RemoveNode - Node Not Found\n"));
    return EFI_NOT_FOUND;
  }

  if (Node != UsbFuncIoDevPtr->FirstNodePtr) {
    PNode->NextPtr = Node->NextPtr;
  } else {
    UsbFuncIoDevPtr->FirstNodePtr = Node->NextPtr;
  }

  FreePool (Node->AllocatePtr);
  FreePool (Node);
  DEBUG ((USB_DEBUG_MEM_NODE_INFO, "RemoveNode - Exit\n"));
  return EFI_SUCCESS;
}

/**
  The InsertNewNodeToHead function allocates a memory for record the driver allocate
  memory region and insert the node to the head link list.

  @param[in]  This              A pointer to the EFI_USBFN_IO_PROTOCOL instance.
  @param[out] USB_MEM_NODE      return the new node address.

  @retval EFI_SUCCESS           The operation completed successfully.
  @retval EFI_INVALID_PARAMETER A parameter is invalid.
  @retval EFI_OUT_OF_RESOURCES  The requested transfer buffer could not be allocated.

**/
EFI_STATUS
InsertNewNodeToHead (
  IN  EFI_USBFN_IO_PROTOCOL    *This,
  OUT USB_MEM_NODE             **Node
  )
{
  USB_MEM_NODE         *NewNodePtr;
  USB_MEM_NODE         *CurrentNodePtr;
  USB_XDCI_DEV_CONTEXT *UsbFuncIoDevPtr;
  EFI_STATUS           Status;

  DEBUG ((USB_DEBUG_MEM_NODE_INFO, "CreateNewNode - Entry\n"));

  if (This == NULL) {
    Status = EFI_INVALID_PARAMETER;
    goto ErrorExit;
  }

  UsbFuncIoDevPtr = USBFUIO_CONTEXT_FROM_PROTOCOL(This);

  //
  // Create the new node
  //
  NewNodePtr = AllocateZeroPool (sizeof(USB_MEM_NODE));
  DEBUG ((USB_DEBUG_MEM_NODE_INFO, "NewNodePtr - Addr = 0x%08x\n",(UINTN)NewNodePtr));

  if (NewNodePtr == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto ErrorExit;
  }

  //
  // insert the new node
  //
  CurrentNodePtr = UsbFuncIoDevPtr->FirstNodePtr;
  UsbFuncIoDevPtr->FirstNodePtr = NewNodePtr;

  if (CurrentNodePtr != NULL) {
    NewNodePtr->NextPtr = CurrentNodePtr;
  }

  *Node = NewNodePtr;

  DEBUG ((USB_DEBUG_MEM_NODE_INFO, "CreateNewNode - Exit\n"));
  return EFI_SUCCESS;

ErrorExit:

  DEBUG ((USB_DEBUG_MEM_NODE_ERROR, "CreateNewNode - error %r\n",Status));
  return Status;
}


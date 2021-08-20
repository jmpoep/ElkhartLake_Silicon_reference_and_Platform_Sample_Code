/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include "PlatformInitAdvancedSmm.h"
#include "PcieDockSmi.h"

//Assign resources to saddlestring downstream bridges
VOID
AssignSaddleStringResources (
  VOID
  )
{

  UINT32  VenDev_id1;
  UINT32  VenDev_id2;
  UINT16  IoBaseLimit;
  UINT16  BaseLimit16;
  UINT32  MemBaseLimit;
  UINT32  PfmBaseLimit;
  UINT32  BaseLimit32;
  UINT32  PfmBaseLimit32;
  UINT32  BusNumber32;
  UINT32  SecBusNum;
  UINT32  SecBusNum1;
  UINT32  SecBusNum2;
  UINT32  EndBusNum;
  UINT32  EndBusNum2;
  UINTN   DevIndex;
  UINT8   Command8;
  UINT8   BusWidth8;
  UINT16  Dev_id;
  UINT32  i;
  UINT64  PCIControlBase;

  BusWidth8 = 1;

  //
  // Check if PEG (0,1,0) is populated
  //
  VenDev_id2 = 0;
  if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0x1, 0, 0)) != 0xFFFF) {
    //
    // Checking for the Turbo dock. Turbo dock has PLX 8547 for the PEG. 8547 sits on the Bus 0, dev1, fun 0.
    //
    BusNumber32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0x1, 0, 0x18));

    SecBusNum1 = (BusNumber32 >> 8) & 0xFF;                // Get Secondary Bus Number

    // Read the vendor id to check for the PLX8547 on Secbusnum, dev 0 and func 0
    VenDev_id2 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, SecBusNum1, 0, 0, 0));


    // Read the bus numbers for the PLX8547 device
    BusNumber32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, SecBusNum1, 0, 0, 0x18));
    SecBusNum2 = (BusNumber32 >> 8) & 0xFF;                // Get Secondary Bus Number
    EndBusNum2 = (BusNumber32 >> 16) & 0xFF;               // Get Subordinary Bus Number

    // Fix for the PLX8547 NVidia.
    // Enable only VC0 in the PCI reg 0x114 if NVidia card.
    if (VenDev_id2 == TURBODOCK_PLX_DEVID) { //if there is Turbo dock device
      for (i=SecBusNum2; i<=EndBusNum2; i++) {
        Dev_id = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (0, i, 0, 0, 2));
        if (Dev_id == 0x0191) { //If dev id is for NVidia card.
          PCIControlBase = PCI_SEGMENT_LIB_ADDRESS (0, i, 0, 0, 0x114);
          PciSegmentWrite32 (PCIControlBase, 0x80000001);
        }
      }
    }
  }

  //
  // Get PCIe Root Port 7 Bus Number Register
  //
  BusNumber32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0x1C, 6, 0x18));

  SecBusNum = (BusNumber32 >> 8) & 0xFF;                // Get Secondary Bus Number
  EndBusNum = (BusNumber32 >> 16) & 0xFF;               // Get Subordinary Bus Number

  // Turbo dock - 7 or more buses will execute resource allocation
  if(VenDev_id2 == TURBODOCK_PLX_DEVID) {
    if (EndBusNum - SecBusNum < 7) {                    // If bus width not enough
      return;                                           // Skip Resource Setting
    }
  } else {  // Saddle string - 6 or more buses will execute resource allocation
    if (EndBusNum - SecBusNum < 6) {                    // If bus width not enough
      return;                                           // Skip Resource Setting
    }
  }

  VenDev_id1 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, SecBusNum, 0, 0, 0));

  if ((VenDev_id1 != SADDLESTRINGS_PLX_DEVID) && (VenDev_id2 != TURBODOCK_PLX_DEVID)) { //if there is no saddlestring or Turbo dock device, return
    return;
  }

  //
  // Set PCIe dock first level Bridge Bus Number Register
  //
  BusNumber32 = SecBusNum + ((SecBusNum + 1) << 8) + (EndBusNum << 16);
  PciSegmentAndThenOr32 (PCI_SEGMENT_LIB_ADDRESS (0, SecBusNum, 0, 0, 0x18), 0, BusNumber32);

  //
  // Get PCIe Root Port 7 I/O Base & Limit Register
  //
  IoBaseLimit = PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0x1C, 6, 0x1C));

  //
  // Set PCIe dock first level Bridge I/O Base & Limit Register
  //
  PciSegmentAndThenOr16 (PCI_SEGMENT_LIB_ADDRESS (0, SecBusNum, 0, 0, 0x1C), 0, IoBaseLimit);
  PciSegmentAndThenOr32 (PCI_SEGMENT_LIB_ADDRESS (0, SecBusNum, 0, 0, 0x30), 0, 0);  // I/O Base/Limit Upper 16 Bits Regs

  //
  // Get PCIe Root Port 7 MEM Base & Limit Register
  //
  MemBaseLimit = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0x1C, 6, 0x20));

  //
  // Set PCIe dock first level Bridge MEM BAR0
  //
  BaseLimit32 = (MemBaseLimit & 0xFFFF0000);            // Set top 1M MEM for BAR0
  PciSegmentAndThenOr32 (PCI_SEGMENT_LIB_ADDRESS (0, SecBusNum, 0, 0, 0x10), 0, BaseLimit32);

  //
  // Set PCIe dock first level Bridge MEM Base & Limit Register
  //
  MemBaseLimit -= 0x100000;                             // Exclude the top 1M MEM Range
  PciSegmentAndThenOr32 (PCI_SEGMENT_LIB_ADDRESS (0, SecBusNum, 0, 0, 0x20), 0, MemBaseLimit);

  //
  // Get PCIe Root Port 7 Prefetchable MEM Base & Limit Register
  //
  PfmBaseLimit = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 0x1C, 6, 0x24));

  //
  // Set PCIe dock first level Bridge Prefetchable MEM Base & Limit Register
  //
  PciSegmentAndThenOr32 (PCI_SEGMENT_LIB_ADDRESS (0, SecBusNum, 0, 0, 0x24), 0, PfmBaseLimit);

  //
  // Set PCIe dock first level Bridge Command Register
  //
  Command8 = 7;
  PciSegmentAndThenOr8 (PCI_SEGMENT_LIB_ADDRESS (0, SecBusNum, 0, 0, 0x04), 0, Command8);

  //
  // Set resource for PCIe dock 2nd level Bridge
  //
  if(VenDev_id2 == TURBODOCK_PLX_DEVID) {
    //
    // Turbo dock dev 1 & dev 2 has 2 buses each.
    //
    BusNumber32 = (BusNumber32 & 0xFFFF) + 0x0001 + ((SecBusNum + 2) << 16);
    BusWidth8 = 2;
  } else if ((VenDev_id2 != TURBODOCK_PLX_DEVID) && (VenDev_id1 == SADDLESTRINGS_PLX_DEVID)) {
    BusNumber32 = (BusNumber32 & 0xFFFF) + 0x0001 + ((SecBusNum + 1) << 16);
    BusWidth8 = 1;
  }

  BaseLimit16 = IoBaseLimit & 0x00FF;                   // Get RP1 I/O Base Register
  BaseLimit16 += BaseLimit16 << 8;                      // Set first 4K I/O Range

  BaseLimit32 = MemBaseLimit & 0x0000FFFF;              // Get RP1 MEM Base Register
  BaseLimit32 += (BaseLimit32 << 16) + 0x300000;        // Set first 4M MEM Range

  PfmBaseLimit32 = PfmBaseLimit & 0x0000FFFF;           // Get RP1 Prefetchable MEM Base Register
  PfmBaseLimit32 += (PfmBaseLimit32 << 16) + 0x300000;  // Set first 4M Prefetchable MEM Range

  for (DevIndex = 0; DevIndex <= 9; DevIndex ++) {
    //
    // Check if the 2nd level Bridges exist
    //
    if (PciSegmentRead16 (PCI_SEGMENT_LIB_ADDRESS (0, (SecBusNum + 1), (UINT32)DevIndex, 0, 0x00)) != 0xFFFF) {
      //
      // I/O Base & Limit Register
      //
      PciSegmentAndThenOr16 (PCI_SEGMENT_LIB_ADDRESS (0, (SecBusNum + 1), (UINT32)DevIndex, 0, 0x1C), 0, BaseLimit16);
      //
      // I/O Base/Limit Upper 16 Bits Register
      //
      PciSegmentAndThenOr32 (PCI_SEGMENT_LIB_ADDRESS (0, (SecBusNum + 1), (UINT32)DevIndex, 0, 0x30), 0, 0);
      //
      // Set next 4K I/O Range
      //
      if (BaseLimit16 < IoBaseLimit) {
        BaseLimit16 += 0x01010;
      }

      //
      // MEM Base & Limit Register
      //
      PciSegmentAndThenOr32 (PCI_SEGMENT_LIB_ADDRESS (0, (SecBusNum + 1), (UINT32)DevIndex, 0, 0x20), 0, BaseLimit32);
      //
      // Set next 4M MEM Range
      //
      if (BaseLimit32 + 0x400000 < MemBaseLimit) {
        BaseLimit32 += 0x00400040;
      } else {
        //
        // Last remained MEM Range
        //
        BaseLimit32 = ((BaseLimit32 + 0x40) & 0xFFFF) + (MemBaseLimit & 0xFFFF0000);
      }

      //
      // Prefetchable MEM Base & Limit register
      //
      PciSegmentAndThenOr32 (PCI_SEGMENT_LIB_ADDRESS (0, (SecBusNum + 1), (UINT32)DevIndex, 0, 0x24), 0, PfmBaseLimit32);
      //
      // Set next 4M Prefetchable MEM Range
      //
      if (PfmBaseLimit32 + 0x400000 < PfmBaseLimit) {
        PfmBaseLimit32 += 0x00400040;
      } else {
        //
        // Last remained MEM Range
        //
        PfmBaseLimit32 = ((BaseLimit32 + 0x40) & 0xFFFF) + (PfmBaseLimit & 0xFFFF0000);
      }

      //
      // Secondary Bus Range
      //
      BusNumber32 += (BusWidth8 << 8);
      if (VenDev_id2 == TURBODOCK_PLX_DEVID) {
        //
        // in case of turbo dock, device 1& 2 has 2 buses
        //
        BusWidth8 = (DevIndex >= 2)? 1 : 2;
      } else if ((VenDev_id2 != TURBODOCK_PLX_DEVID) && (VenDev_id1 == SADDLESTRINGS_PLX_DEVID)) {
        //
        // in case of Saddle string, Only 3rd downstream gets 2
        //
        BusWidth8 = (DevIndex == 7)? 2 : 1;
      }
      //
      // Set Subordinate Bus Number
      //
      BusNumber32 += (BusWidth8 << 16);
      //
      // Set Bus Number Register
      //
      PciSegmentAndThenOr32 (PCI_SEGMENT_LIB_ADDRESS (0, (SecBusNum + 1), (UINT32)DevIndex, 0, 0x18), 0, BusNumber32);

      //
      // Set Command Register
      //
      PciSegmentAndThenOr8 (PCI_SEGMENT_LIB_ADDRESS (0, (SecBusNum + 1), (UINT32)DevIndex, 0, 0x04), 0, Command8);
    }
  }

  IoWrite32 (0x80, 0x4DCE);  // Display port 80h with value 4DCEh
}

EFI_STATUS
EFIAPI
PcieDockSmiCallback (
  IN  EFI_HANDLE                             DispatchHandle,
  IN  CONST VOID                             *DispatchContext,
  IN  OUT VOID                               *CommBuffer  OPTIONAL,
  IN  UINTN                                  *CommBufferSize  OPTIONAL
  )
/*++

Routine Description:

  Dispatch function for a PCIe Dock Bridge Resource Patch SMI handler.

Arguments:

  DispatchHandle  - Handle of this dispatch function
  DispatchContext - Pointer to the dispatch function's context.
                    The DispatchContext fields are filled in by the dispatching driver
                    prior to invoke this dispatch function

Returns:

  None

--*/
{
  AssignSaddleStringResources();

  return EFI_SUCCESS;
}

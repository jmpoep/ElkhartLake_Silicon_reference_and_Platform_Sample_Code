/** @file
  This file contains Protocol definitions for IrqBoardInfo.

 @copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2016 Intel Corporation.

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

  This file contains 'Framework Code' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may not be 
  modified, except as allowed by additional terms of your license agreement.

@par Specification Reference:

**/

#ifndef _IRQ_BOARD_INFO_H_
#define _IRQ_BOARD_INFO_H_

#pragma pack(push, 1)

//
// Describe PCI IRQ Router Register and available IRQ MASK.
//
typedef struct {
  UINT8   ChipsetReg;
  UINT16  IrqMask;
} PCI_PIC_IRQ_DATA;

//
// Describe Legacy (PIC) IRQ Routing Information.
//
typedef struct {
  UINT8             PciBusNumber;
  UINT8             DeviceNumber; // Vaild in upper 5 bits
  PCI_PIC_IRQ_DATA  PciIrq[4];
  UINT8             SlotNum;
  UINT8             Reserved;
} PCI_IRQ_PIC_ROUTE;

//
// Describe (APIC) IRQ Routing DATA.
//
typedef struct {
  UINT8   IoApicIntIn;
  UINT8   IoApicId;
} PCI_APIC_IRQ_DATA;

//
// Describe Extended (IO/APIC) IRQ Routing 
//
typedef struct {
  UINT8             PciBusNumber;
  UINT8             DeviceNumber; // Valid in lower 5 bits
  PCI_APIC_IRQ_DATA IntIn[4];
  UINT8             Reserved;
} PCI_IRQ_APIC_ROUTE;

//
// PCI Device Function Package.
//
typedef  union {
  UINT8       DevFunc;
  struct {
    UINT8     Fun : 3;
    UINT8     Dev : 5;
  } Bits;
} PCI_DEV_FUN;

//
// Describe bus translation from build time assginment to runtime assignment
//
typedef struct {
  //
  // PCI Bus# Assigned at BIOS build time
  //
  UINT8          BusBuild;
  //
  // PCI Bus# Assigned at run time
  //
  UINT8          BusRun;
  //
  // bridges chain
  //
//  PCI_DEV_FUN    Bridge[];
//  UINT8          Terminator==0xFF;    
} PCI_BUS_XLAT_HDR;

//
// IoApic address
//
typedef union {
  UINT32          Address;
  struct {
    UINT32      Func    : 8;
    UINT32      Dev     : 8;  
    UINT32      Bus     : 8;
    UINT32      Seg     : 8;
  } Bits;
} IRQ_IOAPIC_ADDRESS;

//
// Describe IO/APIC Information
//
typedef struct {
  IRQ_IOAPIC_ADDRESS      ApicAddress;
  //
  // IoApic ID at build time
  //
  UINT8                   ApicIdBuild;
  //
  // IoApic ID at run time
  //
  UINT8                   ApicIdRun;
} IRQ_APIC_INFO;

#pragma pack(pop)

//
// Definition of IRQ Board Info Protocol.
//
typedef struct _IRQ_BOARD_INFO_PROTOCOL {
  BOOLEAN                    Updated;
  UINT16                     PciDedicatedIrqs;
  PCI_BUS_XLAT_HDR           *BusXlatTable;
  UINTN                      BusXlatLength;
  PCI_IRQ_PIC_ROUTE          *PicRoutTable;
  UINTN                      PicRoutLength;
  PCI_IRQ_APIC_ROUTE         *ApicRoutTable;
  UINTN                      ApicRoutLength;
  IRQ_APIC_INFO              *ApicInfoTable;
  UINTN                      ApicInfoLength;
} IRQ_BOARD_INFO_PROTOCOL;

#endif //IRQ_BOARD_INFO_H_

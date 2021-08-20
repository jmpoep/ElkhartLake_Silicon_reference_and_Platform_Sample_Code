/** @file
  Header file for IDE mode of ATA host controller.

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
#ifndef __ATA_HC_IDE_MODE_H__
#define __ATA_HC_IDE_MODE_H__

typedef enum {
  EfiIdePrimary    = 0,
  EfiIdeSecondary  = 1,
  EfiIdeMaxChannel = 2
} EFI_IDE_CHANNEL;

typedef enum {
  EfiIdeMaster    = 0,
  EfiIdeSlave     = 1,
  EfiIdeMaxDevice = 2
} EFI_IDE_DEVICE;

///
/// PIO mode definition
///
typedef enum {
  EfiAtaPioModeBelow2,
  EfiAtaPioMode2,
  EfiAtaPioMode3,
  EfiAtaPioMode4
} EFI_ATA_PIO_MODE;

//
// Multi word DMA definition
//
typedef enum {
  EfiAtaMdmaMode0,
  EfiAtaMdmaMode1,
  EfiAtaMdmaMode2
} EFI_ATA_MDMA_MODE;

//
// UDMA mode definition
//
typedef enum {
  EfiAtaUdmaMode0,
  EfiAtaUdmaMode1,
  EfiAtaUdmaMode2,
  EfiAtaUdmaMode3,
  EfiAtaUdmaMode4,
  EfiAtaUdmaMode5
} EFI_ATA_UDMA_MODE;

//
// Bus Master Reg
//
#define BMIC_NREAD      BIT3
#define BMIC_START      BIT0
#define BMIS_INTERRUPT  BIT2
#define BMIS_ERROR      BIT1

#define BMIC_OFFSET    0x00
#define BMIS_OFFSET    0x02
#define BMID_OFFSET    0x04

//
// IDE transfer mode
//
#define EFI_ATA_MODE_DEFAULT_PIO 0x00
#define EFI_ATA_MODE_FLOW_PIO    0x01
#define EFI_ATA_MODE_MDMA        0x04
#define EFI_ATA_MODE_UDMA        0x08

typedef struct {
  UINT32  RegionBaseAddr;
  UINT16  ByteCount;
  UINT16  EndOfTable;
} EFI_ATA_DMA_PRD;

typedef struct {
  UINT8 ModeNumber   : 3;
  UINT8 ModeCategory : 5;
} EFI_ATA_TRANSFER_MODE;

typedef struct {
  UINT8 Sector;
  UINT8 Heads;
  UINT8 MultipleSector;
} EFI_ATA_DRIVE_PARMS;

//
// IDE registers set
//
typedef struct {
  UINT16                          Data;
  UINT16                          ErrOrFeature;
  UINT16                          SectorCount;
  UINT16                          SectorNumber;
  UINT16                          CylinderLsb;
  UINT16                          CylinderMsb;
  UINT16                          Head;
  UINT16                          CmdOrStatus;
  UINT16                          AltOrDev;

  UINT16                          BusMasterBaseAddr;
} EFI_IDE_REGISTERS;

//
// Bit definitions in Programming Interface byte of the Class Code field
// in PCI IDE controller's Configuration Space
//
#define IDE_PRIMARY_OPERATING_MODE            BIT0
#define IDE_PRIMARY_PROGRAMMABLE_INDICATOR    BIT1
#define IDE_SECONDARY_OPERATING_MODE          BIT2
#define IDE_SECONDARY_PROGRAMMABLE_INDICATOR  BIT3


#endif


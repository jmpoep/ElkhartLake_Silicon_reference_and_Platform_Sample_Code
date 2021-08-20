/** @file
  This is part of the implementation of an Intel Graphics drivers OpRegion /
  Software SCI interface between system BIOS, ASL code, and Graphics drivers.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
  - OpRegion / Software SCI SPEC
**/
#ifndef _DXE_IGD_OPREGION_INIT_LIB_H_
#define _DXE_IGD_OPREGION_INIT_LIB_H_

///
/// Statements that include other header files.
///
#include <Uefi.h>
#include <Uefi/UefiBaseType.h>
#include <Library/UefiBootServicesTableLib.h>
#include <IndustryStandard/Pci.h>
#include <Library/ConfigBlockLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/HobLib.h>
#include <Library/UefiLib.h>
#include <Library/S3BootScriptLib.h>
#include <Register/IgdRegs.h>
#include <SiConfigHob.h>
///
/// Driver Consumed Protocol Prototypes
///
#include <Protocol/PciIo.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/SaPolicy.h>
#include <Protocol/SaNvsArea.h>
///
/// Driver Produced Protocol Prototypes
///
#include <Protocol/IgdOpRegion.h>

#pragma pack(push, 1)
///
///
/// OpRegion (Miscellaneous) defines.
///
/// OpRegion Header defines.
///
typedef UINT16  STRING_REF;
#define HEADER_SIGNATURE            "IntelGraphicsMem"
#define HEADER_SIZE                 0x2000
#define HEADER_OPREGION_REV         0x00
#define HEADER_MBOX_SUPPORT         (HD_MBOX5 + HD_MBOX4 + HD_MBOX3 + HD_MBOX2 + HD_MBOX1)
#define HD_MBOX1                    BIT0
#define HD_MBOX2                    BIT1
#define HD_MBOX3                    BIT2
#define HD_MBOX4                    BIT3
#define HD_MBOX5                    BIT4
#define SVER_SIZE                   32

///
/// OpRegion Mailbox 1 EQUates.
///
/// OpRegion Mailbox 3 EQUates.
///
#define ALS_ENABLE            BIT0
#define BACKLIGHT_BRIGHTNESS  0xFF
#define FIELD_VALID_BIT       BIT31
#define PFIT_ENABLE           BIT2
#define PFIT_OPRN_AUTO        0x00000000
#define PFIT_OPRN_SCALING     0x00000007
#define PFIT_OPRN_OFF         0x00000000
#define PFIT_SETUP_AUTO       0
#define PFIT_SETUP_SCALING    1
#define PFIT_SETUP_OFF        2
#define INIT_BRIGHT_LEVEL     0x64
#define PFIT_STRETCH          6

///
/// Video BIOS / VBT defines
///
#define OPTION_ROM_SIGNATURE    0xAA55
#define VBIOS_LOCATION_PRIMARY  0xC0000

#define VBT_SIGNATURE           SIGNATURE_32 ('$', 'V', 'B', 'T')
///
/// Typedef stuctures
///
typedef struct {
  UINT16  Signature;  /// 0xAA55
  UINT8   Size512;
  UINT8   Reserved[21];
  UINT16  PcirOffset;
  UINT16  VbtOffset;
} INTEL_VBIOS_OPTION_ROM_HEADER;

typedef struct {
  UINT32  Signature;  /// "PCIR"
  UINT16  VendorId;   /// 0x8086
  UINT16  DeviceId;
  UINT16  Reserved0;
  UINT16  Length;
  UINT8   Revision;
  UINT8   ClassCode[3];
  UINT16  ImageLength;
  UINT16  CodeRevision;
  UINT8   CodeType;
  UINT8   Indicator;
  UINT16  Reserved1;
} INTEL_VBIOS_PCIR_STRUCTURE;

typedef struct {
  UINT8   HeaderSignature[20];
  UINT16  HeaderVersion;
  UINT16  HeaderSize;
  UINT16  HeaderVbtSize;
  UINT8   HeaderVbtCheckSum;
  UINT8   HeaderReserved;
  UINT32  HeaderOffsetVbtDataBlock;
  UINT32  HeaderOffsetAim1;
  UINT32  HeaderOffsetAim2;
  UINT32  HeaderOffsetAim3;
  UINT32  HeaderOffsetAim4;
  UINT8   DataHeaderSignature[16];
  UINT16  DataHeaderVersion;
  UINT16  DataHeaderSize;
  UINT16  DataHeaderDataBlockSize;
  UINT8   CoreBlockId;
  UINT16  CoreBlockSize;
  UINT16  CoreBlockBiosSize;
  UINT8   CoreBlockBiosType;
  UINT8   CoreBlockReleaseStatus;
  UINT8   CoreBlockHWSupported;
  UINT8   CoreBlockIntegratedHW;
  UINT8   CoreBlockBiosBuild[4];
  UINT8   CoreBlockBiosSignOn[155];
} VBIOS_VBT_STRUCTURE;
#pragma pack(pop)
///
/// Driver Private Function definitions
///

/**
  Graphics OpRegion / Software SCI driver installation function.

  @retval EFI_SUCCESS     - The driver installed without error.
  @retval EFI_ABORTED     - The driver encountered an error and could not complete
                            installation of the ACPI tables.
**/
EFI_STATUS
IgdOpRegionInit (
  VOID
  );

/**
  Get Intel video BIOS VBT information (i.e. Pointer to VBT and VBT size).
  The VBT (Video BIOS Table) is a block of customizable data that is built
  within the video BIOS and edited by customers.

  @retval EFI_SUCCESS            - Video BIOS VBT information returned.
  @exception EFI_UNSUPPORTED     - Could not find VBT information (*VBiosVbtPtr = NULL).
**/
EFI_STATUS
GetVBiosVbtEndOfDxe (
  VOID
  );

/**
  Update Graphics OpRegion after PCI enumeration.

  @retval EFI_SUCCESS     - The function completed successfully.
**/
EFI_STATUS
UpdateIgdOpRegionEndOfDxe (
  VOID
  );
#endif

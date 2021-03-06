/** @file
  Policy details for miscellaneous configuration in System Agent

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#ifndef _SA_MISC_PEI_PREMEM_CONFIG_H_
#define _SA_MISC_PEI_PREMEM_CONFIG_H_

#pragma pack(push, 1)

#ifndef MEM_CFG_MAX_SOCKETS
#define MEM_CFG_MAX_SOCKETS 16
#endif

#define SA_MISC_PEI_PREMEM_CONFIG_REVISION 1

/**
  This configuration block is to configure SA Miscellaneous variables during PEI Pre-Mem phase like programming
  different System Agent BARs, TsegSize, IedSize, MmioSize required etc.
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER  Header;               ///< Offset 0-27 Config Block Header
  /**
    Offset 28 Memory DIMMs' SPD address for reading SPD data.
    TGL Mapping
      0 - Controller 0 Channel 0 Dimm 0 - DDR4 - DDR5 - LPDDR4 - LPDDR5
      1 - Controller 0 Channel 0 Dimm 1 - DDR4
      2 - Controller 0 Channel 1 Dimm 0 -------- DDR5 - LPDDR4 - LPDDR5
      3 - Controller 0 Channel 1 Dimm 1 -------- DDR5 2DPC
      4 - Controller 0 Channel 2 Dimm 0 --------------- LPDDR4 - LPDDR5
      6 - Controller 0 Channel 3 Dimm 0 --------------- LPDDR4 - LPDDR5
      8 - Controller 1 Channel 0 Dimm 0 - DDR4 - DDR5 - LPDDR4 - LPDDR5
      9 - Controller 1 Channel 0 Dimm 1 - DDR4
     10 - Controller 1 Channel 1 Dimm 0 -------- DDR5 - LPDDR4 - LPDDR5
     11 - Controller 1 Channel 1 Dimm 1 -------- DDR5 2DPC
     12 - Controller 1 Channel 2 Dimm 0 --------------- LPDDR4 - LPDDR5
     14 - Controller 1 Channel 3 Dimm 0 --------------- LPDDR4 - LPDDR5
  **/
  UINT8   SpdAddressTable[MEM_CFG_MAX_SOCKETS];
  VOID    *S3DataPtr;                        ///< Offset 44 Memory data save pointer for S3 resume. The memory space should be allocated and filled with proper S3 resume data on a resume path
  UINT32  MchBar;                            ///< Offset 48 Address of System Agent MCHBAR: <b>0xFEDC0000</b>
  UINT32  DmiBar;                            ///< Offset 52 Address of System Agent DMIBAR: <b>0xFED18000</b>
  UINT32  EpBar;                             ///< Offset 56 Address of System Agent EPBAR: <b>0xFED19000</b>
  UINT32  SmbusBar;                          ///< Offset 60 Address of System Agent SMBUS BAR: <b>0xEFA0</b>
  UINT32  RegBar;                            ///< Offset 64 Address of System Agent REGBAR , CNL needs 256KB while ICL requires 16MB: <b>0xFC000000(CNL)/0xFB000000(ICL)</b>
  /**
    Offset 68 Size of TSEG in bytes. (Must be power of 2)
    <b>0x400000</b>: 4MB for Release build (When IED enabled, it will be 8MB)
    0x1000000      : 16MB for Debug build (Regardless IED enabled or disabled)
  **/
  UINT32  TsegSize;
  UINT32  EdramBar;                          ///< Offset 72 Address of System Agent EDRAMBAR: <b>0xFED80000</b>
  /**
    Offset 76
    <b>(Test)</b> Size of IED region in bytes.
    <b>0</b> : IED Disabled (no memory occupied)
    0x400000 : 4MB SMM memory occupied by IED (Part of TSEG)
    <b>Note: Enabling IED may also enlarge TsegSize together.</b>
  **/
  UINT32  IedSize;
  UINT8   UserBd;                            ///< Offset 80 <b>0=Mobile/Mobile Halo</b>, 1=Desktop/DT Halo, 5=ULT/ULX/Mobile Halo, 7=UP Server
  UINT32  SkipExtGfxScan:1;                  ///< <b>(Test)</b> OFfset 81:0 :1=Skip External Gfx Device Scan; <b>0=Scan for external graphics devices</b>. Set this policy to skip External Graphics card scanning if the platform uses Internal Graphics only.
  UINT32  BdatEnable:1;                      ///< Offset 81:1 :This field enables the generation of the BIOS DATA ACPI Tables: <b>0=FALSE</b>, 1=TRUE.
  UINT32  TxtImplemented:1;                  ///< OFfset 81:2 :This field currently is used to tell MRC if it should run after TXT initializatoin completed: <b>0=Run without waiting for TXT</b>, 1=Run after TXT initialization by callback
  /**
   Offset 81:3 :
   <b>(Test)</b> Scan External Discrete Graphics Devices for Legacy Only VGA OpROMs

   When enabled, if the primary graphics device is an external discrete graphics device, Si will scan the
   graphics device for legacy only VGA OpROMs.  If the primary graphics device only implements legacy VBIOS, then the
   LegacyOnlyVgaOpRomDetected field in the SA_DATA_HOB will be set to 1.

   This is intended to ease the implementation of a BIOS feature to automatically enable CSM if the Primary Gfx device
   only supports Legacy VBIOS (No UEFI GOP Present).  Otherwise disabling CSM won't result in no video being displayed.
   This is useful for platforms that implement PCIe slots that allow the end user to install an arbitrary Gfx device.

   This setting will only take effect if SkipExtGfxScan == 0.  It is ignored otherwise.

  - Disabled (0x0)         : Don't Scan for Legacy Only VGA OpROMs (Default)
  - <b>Enabled</b>  (0x1)  : Scan External Gfx for Legacy Only VGA OpROM
  **/
  UINT32  ScanExtGfxForLegacyOpRom:1;
  UINT32  EnableAbove4GBMmio:1;              ///< Offset 81:4  Enable/disable above 4GB MMIO resource support: 0=Disable, <b>1=Enable</b>
  UINT32  RsvdBits0  :27;                    ///< Offset 81:5 :Reserved for future use
  UINT8   LockPTMregs;                       ///< <b>(Test)</b> Offset 85 Lock PCU Thermal Management registers: 0=FALSE, <b>1=TRUE</b>
  UINT8   BdatTestType;                      ///< Offset 86 When BdatEnable is set to TRUE, this option selects the type of data which will be populated in the BIOS Data ACPI Tables: <b>0=RMT</b>, 1=RMT Per Bit, 2=Margin 2D.
  UINT8   CridEnable;                        ///< Offset 87 For Platforms supporting Intel(R) SIPP, this policy is use control enable/disable Compatibility Revision ID (CRID) feature: <b>0=FALSE</b>, 1=TRUE
  /**
    Offset 88 :
    Size of reserved MMIO space for PCI devices\n
    <b>0=AUTO</b>, 512=512MB, 768=768MB, 1024=1024MB, 1280=1280MB, 1536=1536MB, 1792=1792MB,
    2048=2048MB, 2304=2304MB, 2560=2560MB, 2816=2816MB, 3072=3072MB\n
    When AUTO mode selected, the MMIO size will be calculated by required MMIO size from PCIe devices detected.
  **/
  UINT16  MmioSize;
  INT16   MmioSizeAdjustment;                ///< Offset 90 Increase (given positive value) or Decrease (given negative value) the Reserved MMIO size when Dynamic Tolud/AUTO mode enabled (in MBs): <b>0=no adjustment</b>
  UINT64  AcpiReservedMemoryBase;            ///< Offset 92 The Base address of a Reserved memory buffer allocated in previous boot for S3 resume used. Originally it is retrieved from AcpiVariableCompatibility variable.
  UINT64  SystemMemoryLength;                ///< Offset 100 Total system memory length from previous boot, this is required for S3 resume. Originally it is retrieved from AcpiVariableCompatibility variable.
  UINT32  AcpiReservedMemorySize;            ///< Offset 108 The Size of a Reserved memory buffer allocated in previous boot for S3 resume used. Originally it is retrieved from AcpiVariableCompatibility variable.
  UINT32  OpRomScanTempMmioBar;              ///< <b>(Test)</b> Offset 112 Temporary address to MMIO map OpROMs during VGA scanning.  Used for ScanExtGfxForLegacyOpRom feature.  MUST BE 16MB ALIGNED!
  UINT32  OpRomScanTempMmioLimit;            ///< <b>(Test)</b> Offset 116 Limit address for OpROM MMIO range.  Used for ScanExtGfxForLegacyOpRom feature. (OpROMScanTempMmioLimit - OpRomScanTempMmioBar) MUST BE >= 16MB!



  // Since the biggest element is UINT64, this structure should be aligned with 64 bits.
  UINT8   Rsvd[4];                           ///< Reserved for config block alignment.


} SA_MISC_PEI_PREMEM_CONFIG;
#pragma pack(pop)

#endif // _SA_MISC_PEI_PREMEM_CONFIG_H_

/** @file
  SPI library for abstraction of SPI HW registers accesses

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

#include <Base.h>
#include <Uefi/UefiBaseType.h>
#include <IndustryStandard/Pci22.h>
#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/SpiAccessLib.h>
#include <Register/SpiRegs.h>
#include <Register/FlashRegs.h>
#include <Register/PchRegs.h>

#define MAX_SPI_COMPONENT_NUMBER 2    // Max supported components under SPI

/**
  Returns PCH SPI PCI Config Space base address

  @retval  UINT64  PCH SPI Config Space base address
**/
UINT64
SpiGetPciCfgAddress (
  VOID
  )
{
  return PCI_SEGMENT_LIB_ADDRESS (
           DEFAULT_PCI_SEGMENT_NUMBER_PCH,
           DEFAULT_PCI_BUS_NUMBER_PCH,
           PCI_DEVICE_NUMBER_PCH_SPI,
           PCI_FUNCTION_NUMBER_PCH_SPI,
           0
           );
}

/**
  Checks if PCH SPI Controler is present and available

  @retval TRUE    PCH SPI controller is avaialable
  @retval FALSE   PCH SPI controller is not available
**/
BOOLEAN
SpiIsControllerAvailable (
  VOID
  )
{
  //
  // Checks for SPI controller
  //
  return (PciSegmentRead16 (SpiGetPciCfgAddress () + PCI_VENDOR_ID_OFFSET) != 0xFFFF);
}

/**
  Returns PCH SPI BAR0 value

  @retval  UINT32  PCH SPI BAR0 value
**/
UINT32
SpiGetBar0 (
  VOID
  )
{
  UINT32  SpiBar0;

  ASSERT (SpiIsControllerAvailable ());
  SpiBar0 = PciSegmentRead32 (SpiGetPciCfgAddress () + R_SPI_CFG_BAR0) & ~B_SPI_CFG_BAR0_MASK;
  ASSERT (SpiBar0 != 0);

  return SpiBar0;
}

/**
  Returns PCH SPI Device number

  @retval UINT8   PCH SPI Device number
**/
UINT8
SpiDeviceNumber (
  VOID
  )
{
  return PCI_DEVICE_NUMBER_PCH_SPI;
}

/**
  Returns PCH SPI Function number

  @retval UINT8   PCH SPI Function number
**/
UINT8
SpiFunctionNumber (
  VOID
  )
{
  return PCI_FUNCTION_NUMBER_PCH_SPI;
}

/**
  Reads given descriptor section and returns value

  @param[in] UINT16   Descriptor section
  @param[in] UINT16   Offset

  @retval UINT32      Read value from a section under given offset
**/
STATIC
UINT32
SpiReadDescriptor (
  IN  UINT16  DescriptorSection,
  IN  UINT16  Offset
  )
{
  UINT32  SpiBar0;
  SpiBar0 = SpiGetBar0 ();

  MmioWrite32 (SpiBar0 + R_SPI_MEM_FDOC, (DescriptorSection | Offset));
  return MmioRead32 (SpiBar0 + R_SPI_MEM_FDOD);
}

/**
  Returns descriptor signature

  @retval UINT32    Descriptor signature
**/
UINT32
SpiGetDescriptorSignature (
  VOID
  )
{
  //
  // Read Descriptor offset 0x10 - To get Descriptor Signature
  // Signature section 0x0000 + offset 0x0 which points to Descriptor offset 0x10
  //
  return SpiReadDescriptor (V_SPI_MEM_FDOC_FDSS_FSDM, 0x0);
}

/**
  Returns supported features and R/W frequencies of Flash Component

  @retval UINT32    Flash Component features descriptor
**/
UINT32
SpiGetFlashComponentDescription (
  VOID
  )
{
  //
  // Read Descriptor offset 0x30 - To get supported features and R/W frequencies
  // Component section 0x1000 + offset 0x0 which points to Descriptor offset 0x30
  //
  return SpiReadDescriptor (V_SPI_MEM_FDOC_FDSS_COMP, 0x0);
}

/**
  Returns number of Flash Components

  @retval UINT32    Flash components number
**/
UINT32
SpiGetFlashComponentsNumber (
  VOID
  )
{
  //
  // Read Descriptor offset 0x14 - To get number of components
  // Signature section 0x0000 + offset 0x4 which points to Descriptor offset 0x14
  //
  return SpiReadDescriptor (V_SPI_MEM_FDOC_FDSS_FSDM, 0x4);
}

/**
  Returns total Flash size with regards to number of flash components

  @retval UINT32    Total Flash Memory size
**/
UINT32
SpiGetTotalFlashSize (
  VOID
  )
{
  UINT32  Data32;
  UINT32  ComponentsNumber;
  UINT32  TotalFlashSize;

  Data32 = SpiGetFlashComponentDescription ();
  ComponentsNumber = SpiGetFlashComponentsNumber ();

  TotalFlashSize = (V_FLASH_FLCOMP_COMP_512KB << ((UINT8) (Data32 & B_FLASH_FLCOMP_COMP0_MASK)));
  if (ComponentsNumber == 1) {
    TotalFlashSize += (V_FLASH_FLCOMP_COMP_512KB << ((UINT8) ((Data32 & B_FLASH_FLCOMP_COMP1_MASK) >> 4)));
  }

  return TotalFlashSize;
}

/**
  Checks BIOS lock bits for proper value and checks if write protection is enabled
  Expected vales are: LE bit set, EISS bit set and WPD bit cleared

  @retval  TRUE    All protection bits are set correctly
  @retval  FALSE   Not all protection bits had exepcted values
**/
BOOLEAN
SpiIsWriteProtectionEnabled (
  VOID
  )
{
  UINT32  BiosControl;
  BiosControl = PciSegmentRead32 (SpiGetPciCfgAddress () + R_SPI_CFG_BC);

  DEBUG ((DEBUG_INFO, "SPI BIOS CONTROL LE: %x\n", (BiosControl & B_SPI_CFG_BC_LE) != 0 ));
  DEBUG ((DEBUG_INFO, "SPI BIOS CONTROL WPD: %x\n", (BiosControl & B_SPI_CFG_BC_WPD) != 0 ));
  DEBUG ((DEBUG_INFO, "SPI BIOS CONTROL EISS: %x\n", (BiosControl & B_SPI_CFG_BC_EISS) != 0 ));

  return (((BiosControl & B_SPI_CFG_BC_LE) != 0) &&
          ((BiosControl & B_SPI_CFG_BC_WPD) == 0) &&
          ((BiosControl & B_SPI_CFG_BC_EISS) != 0));
}

/**
  Returns status of BIOS Interface Lockdown

  @retval TRUE  BIOS Interface Lockdown is enabled
  @retval FALSE BIOS Interface Lockdown is disabled
**/
BOOLEAN
SpiIsBiosInterfaceLockdownEnabled (
  VOID
  )
{
  return !!(PciSegmentRead32 (SpiGetPciCfgAddress () + R_SPI_CFG_BC) & B_SPI_CFG_BC_BILD);
}

/**
  Returns Flash Descriptor Override Pin Strap status

  @retval TRUE     Flash Descriptor override is enabled
  @retval FALSE    Flash Descriptor override is disabled
**/
BOOLEAN
SpiIsFlashDescriptorOverrideEnabled (
  VOID
  )
{
  UINT32  SpiBar0;
  SpiBar0 = SpiGetBar0 ();

  return !!(MmioRead16 (SpiBar0 + R_SPI_MEM_HSFSC) & B_SPI_MEM_HSFSC_FDOPSS);
}

/**
  Returns Flash Configuration Lock Down bit status

  @retval TRUE    Flash Configuration Lock Down bit is set
  @retval FALSE   Flash Configuration Lock Down bit is not set
**/
BOOLEAN
SpiIsFlashConfigurationLockDownEnabled (
  VOID
  )
{
  UINT32  SpiBar0;
  SpiBar0 = SpiGetBar0 ();

  return !!(MmioRead16 (SpiBar0 + R_SPI_MEM_HSFSC) & B_SPI_MEM_HSFSC_FLOCKDN);
}

/**
  Returns Top Swap functionality enable state

  @retval TRUE    Top Swap is enabled
  @retval FALSE   Top Swap is disabled
**/
BOOLEAN
SpiIsTopSwapEnabled (
  VOID
  )
{
  return !!(PciSegmentRead32 (SpiGetPciCfgAddress () + R_SPI_CFG_BC) & B_SPI_CFG_BC_TSS);
}

/**
  Return Component Property Parameter Table for a given component number

  @param[in]  ComponentNumber   SPI Component number
  @param[out] CppTable          Component Poperty Parameter Table value

  @retval TRUE  Vendor Specific Component Capabilities Register value was read
  @reval  FALSE Vendor Specific Component Capabilities Register value was not present
**/
BOOLEAN
SpiGetComponentPropertyParameterTable (
  IN  UINT8  ComponentNumber,
  OUT UINT32 *CppTable
  )
{
  UINT32 SpiBar0;
  UINT32 Data32;
  SpiBar0 = SpiGetBar0 ();

  //
  // More than 2 components not supported
  //
  switch (ComponentNumber) {
    case 0:
      *CppTable = MmioRead32 (SpiBar0 + R_SPI_MEM_SFDP0_VSCC0);
      return TRUE;
    case 1:
      Data32    = SpiReadDescriptor (V_SPI_MEM_FDOC_FDSS_FSDM, 0x14);
      *CppTable = MmioRead32 (SpiBar0 + R_SPI_MEM_SFDP1_VSCC1);
      return !!(Data32 & BIT8);
    default:
      return FALSE;
  }
}

/**
  Returns valid bit status in given Component Property Parameter Table

  @param[in] CppTable          Component Poperty Parameter Table value

  @retval TRUE    Valid bit is set
  @reval  FALSE   Valid bit is not set
**/
BOOLEAN
SpiIsCppValidBitSet (
  IN UINT32  CppTable
  )
{
  return !!(CppTable & B_SPI_MEM_SFDPX_VSCCX_CPPTV);
}

/**
  Checks if Flash Descriptor is valid

  @retval TRUE  Flash Descriptor is valid
  @retval FALSE Flash Descriptor is invalid
**/
BOOLEAN
SpiIsFlashDescriptorValid (
  VOID
  )
{
  UINT32 SpiBar0;
  SpiBar0 = SpiGetBar0 ();

  return !!(MmioRead32 (SpiBar0 + R_SPI_MEM_HSFSC) & B_SPI_MEM_HSFSC_FDV);
}

/**
  Returns BIOS region accesses value

  @retval UINT32  Flash BIOS region accesses
**/
STATIC
UINT32
SpiGetFlashAccessesValue (
  VOID
  )
{
  return SpiReadDescriptor (V_SPI_MEM_FDOC_FDSS_MSTR, 0);
}

/**
  Returns masked BIOS Region Flash Write Access value

  @retval UINT32    Already masked BIOS Regsion Flash Write access
**/
UINT32
SpiGetBiosRegionFlashWriteAccess (
  VOID
  )
{
  UINT32 FlashAccess;
  FlashAccess = SpiGetFlashAccessesValue () & B_SPI_MEM_FMRWA_MASK;

  DEBUG ((DEBUG_INFO, "BIOS Region Master Write Access 0x%x\n", FlashAccess));

  return FlashAccess;
}

/**
  Returns masked BIOS Region Flash Read Access value

  @retval UINT32    Already masked BIOS Region Flash Read access
**/
UINT32
SpiGetBiosRegionFlashReadAccess (
  VOID
  )
{
  UINT32 FlashAccess;
  FlashAccess = SpiGetFlashAccessesValue () & B_SPI_MEM_FMRRA_MASK;

  DEBUG ((DEBUG_INFO, "BIOS Region Master Read Access 0x%x\n", FlashAccess));

  return FlashAccess;
}

/**
  Reads and returns value from Flash Region Access Permissions Register (FRAP)

  @retval UINT32  Flash Region Access Permissions Register value
**/
STATIC
UINT32
SpiGetFlashRegionAccessPermissions (
  VOID
  )
{
  return MmioRead32 (SpiGetBar0 () + R_SPI_MEM_FRAP);
}

/**
  Returns masked BIOS Master Read Access

  @retval UINT32    Already masked BIOS Master Read Access
**/
UINT32
SpiGetMasterReadAccess (
  VOID
  )
{
  UINT32 Data32;
  Data32 = SpiGetFlashRegionAccessPermissions () & B_SPI_MEM_FRAP_BMRAG_MASK;
  DEBUG ((DEBUG_INFO, "BMRAG 0x%x\n", Data32));

  return Data32;
}

/**
  Returns masked BIOS Master Write Access

  @retval UINT32    Already masked BIOS Master Write Access
**/
UINT32
SpiGetMasterWriteAccess (
  VOID
  )
{
  UINT32 Data32;
  Data32 = SpiGetFlashRegionAccessPermissions () & B_SPI_MEM_FRAP_BMWAG_MASK;
  DEBUG ((DEBUG_INFO, "BMWAG 0x%x\n", Data32));

  return Data32;
}

/**
  Returns GbE Region Access rights

  @retval UINT32    GbE Region access rights
**/
UINT32
SpiGetGbeRegionAccess (
  VOID
  )
{
  UINT32 Data32;

  Data32 = SpiReadDescriptor (V_SPI_MEM_FDOC_FDSS_MSTR, 0x8);
  DEBUG ((DEBUG_INFO, "GbE Region Access 0x%x\n", Data32));

  return Data32;
}

/**
  Returns CSME region access rights

  @retval UINT32    CSME Region Access rights
**/
UINT32
SpiGetCsmeRegionAccess (
  VOID
  )
{
  UINT32 Data32;

  Data32 = SpiReadDescriptor (V_SPI_MEM_FDOC_FDSS_MSTR, 0x4);
  DEBUG ((DEBUG_INFO, "CSME Region Access 0x%x\n", Data32));

  return Data32;
}

/**
  Returns EC region access right

  @retval UINT32     EC Region access rights
**/
UINT32
SpiGetEcRegionAccess (
  VOID
  )
{
  UINT32 Data32;

  Data32 = SpiReadDescriptor (V_SPI_MEM_FDOC_FDSS_MSTR, 0x10);
  DEBUG ((DEBUG_INFO, "EC Region Access 0x%x\n", Data32));

  return Data32;
}

/**
  Checks if Slave Attached Flash (SAF) mode is active

  @retval TRUE    SAF mode is active
  @retval FALSE   SAF mode is not active
**/
BOOLEAN
SpiIsSafModeActive (
  VOID
  )
{
  UINT32 SpiBar0;
  SpiBar0 = SpiGetBar0 ();

  return !!(MmioRead32 (SpiBar0 + R_SPI_MEM_HSFSC) & B_SPI_MEM_HSFSC_SAF_MODE_ACTIVE);
}

/**
  Checks validity of GbE region

  @retval TRUE    GbE region is valid
  @retval FALSE   GbE regios in invalid
**/
BOOLEAN
SpiIsGbeRegionValid (
  VOID
  )
{
  UINT32  SpiBar0;
  SpiBar0 = SpiGetBar0 ();

  if (MmioRead32 (SpiBar0 + R_SPI_MEM_FREG3_GBE) != B_SPI_MEM_FREGX_BASE_MASK) {
    return TRUE;
  }
  return FALSE;
}

/**
  Returns TRUE if BIOS Boot Strap is set to SPI

  @retval TRUE    BIOS Boot strap is set to SPI
  @retval FALSE   BIOS Boot strap is set to LPC/eSPI
**/
BOOLEAN
SpiIsBiosBootFromSpi (
  VOID
  )
{
  return !!(((PciSegmentRead8 (SpiGetPciCfgAddress () + R_SPI_CFG_BC) & B_SPI_CFG_BC_BBS) >> N_SPI_CFG_BC_BBS) == V_SPI_CFG_BC_BBS_SPI);
}

/**
  Check SPI write status disable is set

  @retval TRUE    Write status disable is set
  @retval FALSE   Write status disable is not set
**/
BOOLEAN
SpiIsWriteStatusDisable (
  VOID
  )
{
  return !!(MmioRead32 (SpiGetBar0 () + R_SPI_MEM_HSFSC) & B_SPI_MEM_HSFSC_WRSDIS);
}

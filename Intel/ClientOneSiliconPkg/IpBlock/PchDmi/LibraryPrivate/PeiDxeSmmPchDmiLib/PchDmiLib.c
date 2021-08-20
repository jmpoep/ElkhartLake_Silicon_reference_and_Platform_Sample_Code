/** @file
  PCH DMI library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchPcrLib.h>
#include <Library/PchDmiLib.h>
#include <Library/PchCycleDecodingLib.h>
#include <Library/PsfLib.h>
#include <Register/PchPcrRegs.h>
#include <Register/PchDmiRegs.h>
#include <Register/PchRegsLpc.h>

#include "PchDmi14.h"
#include "PchDmi15.h"

/**
  This function checks if DMI Secured Register Lock (SRL) is set

  @retval SRL state
**/
BOOLEAN
IsPchDmiLocked (
  VOID
  )
{
  if (IsPchWithPdmi ()) {
    return IsPchDmi15Locked ();
  } else {
    return IsPchDmi14Locked ();
  }
}

/**
  Backward DMI library API compatibility
  ACPI base address programming is done in PSF

  @param[in] Address                    Address for ACPI base.

  @retval EFI_UNSUPPORTED               NOT supported programming.
**/
EFI_STATUS
PchDmiSetAcpiBase (
  IN  UINT16                            Address
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Backward DMI library API compatibility
  PWRMBASE is a standard BAR and doesn't require
  additional DMI base decoding programming

  @param[in] Address                    Address for PWRM base.

  @retval EFI_UNSUPPORTED               NOT supported programming.
**/
EFI_STATUS
PchDmiSetPwrmBase (
  IN  UINT32                            Address
  )
{
  return EFI_UNSUPPORTED;
}

/**
  Set PCH TCO base address decoding in DMI

  @param[in] Address                    Address for TCO base address.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_INVALID_PARAMETER         Invalid base address passed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
PchDmiSetTcoBase (
  IN  UINT16                            Address
  )
{
  if (IsPchDmiLocked ()) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  //
  // Program "TCO Base Address" PCR[DMI] + 2778h[15:5, 1] to [SMBUS PCI offset 50h[15:5], 1].
  //
  PchPcrWrite16 (
    PID_DMI, R_PCH_DMI_PCR_TCOBASE,
    (Address | BIT1)
    );

  return EFI_SUCCESS;
}

/**
  Get PCH TCO base address.

  @retval Address                   Address of TCO base address.
**/
UINT16
PchDmiGetTcoBase (
  VOID
  )
{
  //
  // Read "TCO Base Address" PCR[DMI] + 2778h[15:5]
  //
  return (PchPcrRead16 (PID_DMI, R_PCH_DMI_PCR_TCOBASE) & B_PCH_DMI_PCR_TCOBASE_TCOBA);
}

/**
  Set PCH LPC/eSPI generic IO range decoding in DMI

  @param[in] Address                    Address for generic IO range base address.
  @param[in] Length                     Length of generic IO range.
  @param[in] RangeIndex                 Index of choosen range

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
PchDmiSetLpcGenIoRange (
  IN  UINT32                            Address,
  IN  UINT32                            Length,
  IN  UINT32                            RangeIndex
  )
{
  UINT32                                Data32;
  //
  // This cycle decoding is only allowed to set when DMIC.SRL is 0.
  //
  if (IsPchDmiLocked ()) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  Data32 =  (UINT32) (((Length - 1) << 16) & B_LPC_CFG_GENX_DEC_ADDR_MASK);
  Data32 |= (UINT32) Address;
  Data32 |= B_LPC_CFG_GENX_DEC_EN;

  //
  // Program LPC Generic IO Range #, PCR[DMI] + 2730h ~ 273Fh to the same value programmed in LPC/eSPI PCI Offset 84h~93h.
  //
  PchPcrWrite32 (
    PID_DMI, (UINT16) (R_PCH_DMI_PCR_LPCLGIR1 + RangeIndex * 4),
    Data32
    );

  return EFI_SUCCESS;
}

/**
  Set PCH eSPI eSPI CS1# generic IO range decoding in DMI

  @param[in] Address                    Address for generic IO range base address.
  @param[in] Length                     Length of generic IO range.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
PchDmiSetEspiCs1GenIoRange (
  IN  UINT32                            Address,
  IN  UINT32                            Length
  )
{
  UINT32                                Data32;
  //
  // This cycle decoding is only allowed to set when DMIC.SRL is 0.
  //
  if (IsPchDmiLocked ()) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  Data32 =  (UINT32) (((Length - 1) << N_LPC_CFG_GENX_DEC_ADDR_MASK) & B_LPC_CFG_GENX_DEC_ADDR_MASK);
  Data32 |= (UINT32) ((Address << N_LPC_CFG_GENX_DEC_ADDR) & B_LPC_CFG_GENX_DEC_ADDR);
  Data32 |= B_LPC_CFG_GENX_DEC_EN;

  //
  // Program eSPI Generic IO Range #, PCR[DMI] + 27BCh to the same value programmed in eSPI PCI Offset A4h.
  //
  PchPcrWrite32 (PID_DMI, R_PCH_DMI_PCR_SEGIR, Data32);

  return EFI_SUCCESS;
}

/**
  Clear PCH LPC/eSPI generic IO range decoding in DMI

  @param[in] RangeIndex                 Index of chosen range

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
PchDmiClearLpcGenIoRange (
  IN  UINTN                             RangeIndex
  )
{
  //
  // This cycle decoding is only allowed to set when DMIC.SRL is 0.
  //
  if (IsPchDmiLocked ()) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  //
  // Program LPC Generic IO Range #, PCR[DMI] + 2730h ~ 273Fh to the same value programmed in LPC/eSPI PCI Offset 84h~93h.
  //
  PchPcrWrite32 (
    PID_DMI, (UINT16) (R_PCH_DMI_PCR_LPCLGIR1 + RangeIndex * 4),
    0
    );

  return EFI_SUCCESS;
}

/**
  Clear PCH eSPI CS1# generic IO range decoding in DMI

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
PchDmiClearEspiCs1GenIoRange (
  VOID
  )
{
  //
  // This cycle decoding is only allowed to set when DMIC.SRL is 0.
  //
  if (IsPchDmiLocked ()) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }
  //
  // Program LPC Generic IO Range #, PCR[DMI] + 27BCh to the same value programmed in eSPI PCI Offset A4h.
  //
  PchPcrWrite32 (PID_DMI, R_PCH_DMI_PCR_SEGIR, 0);

  return EFI_SUCCESS;
}

/**
  Set PCH LPC/eSPI memory range decoding in DMI

  @param[in] Address                    Address for memory base address.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
PchDmiSetLpcMemRange (
  IN  UINT32                            Address
  )
{
  if (IsPchDmiLocked ()) {
    DEBUG ((DEBUG_ERROR, "%a Error. DMI is locked.\n", __FUNCTION__));
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  //
  // Program LPC Memory Range, PCR[DMI] + 2740h to the same value programmed in LPC/eSPI PCI Offset 98h.
  //
  PchPcrWrite32 (
    PID_DMI, R_PCH_DMI_PCR_LPCGMR,
    (Address | B_LPC_CFG_LGMR_LMRD_EN)
    );

  return EFI_SUCCESS;
}

/**
  Set PCH eSPI CS1# memory range decoding in DMI

  @param[in] Address                    Address for memory base address.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
PchDmiSetEspiCs1MemRange (
  IN  UINT32                            Address
  )
{
  if (IsPchDmiLocked ()) {
    DEBUG ((DEBUG_ERROR, "%a Error. DMI is locked.\n", __FUNCTION__));
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  //
  // Program LPC Memory Range, PCR[DMI] + 27C0h to the same value programmed in eSPI PCI Offset A8h.
  //
  PchPcrWrite32 (
    PID_DMI, R_PCH_DMI_PCR_SEGMR,
    (Address | B_LPC_CFG_LGMR_LMRD_EN)
    );

  return EFI_SUCCESS;
}

/**
  Check if Boot BIOS Strap is set for SPI.

  @retval TRUE                Boot BIOS Strap set for SPI
  @retval FALSE               Boot BIOS Strap set for LPC/eSPI
**/
BOOLEAN
PchDmiIsBootBiosStrapSetForSpi (
  VOID
  )
{
  //
  // Check General Control and Status (GCS) [10]
  // '0': SPI
  // '1': LPC/eSPI
  //
  return ((PchPcrRead32 (PID_DMI, R_PCH_DMI_PCR_GCS) & B_PCH_DMI_PCR_BBS) != B_PCH_DMI_PCR_BBS);
}

/**
  Set PCH BIOS range decoding in DMI
  Please check EDS for detail of BiosDecodeEnable bit definition.
    bit 15: F8-FF Enable
    bit 14: F0-F8 Enable
    bit 13: E8-EF Enable
    bit 12: E0-E8 Enable
    bit 11: D8-DF Enable
    bit 10: D0-D7 Enable
    bit  9: C8-CF Enable
    bit  8: C0-C7 Enable
    bit  7: Legacy F Segment Enable
    bit  6: Legacy E Segment Enable
    bit  5: Reserved
    bit  4: Reserved
    bit  3: 70-7F Enable
    bit  2: 60-6F Enable
    bit  1: 50-5F Enable
    bit  0: 40-4F Enable

  @param[in] BiosDecodeEnable           Bios decode enable setting.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
PchDmiSetBiosDecodeEnable (
  IN  UINT16                            BiosDecodeEnable
  )
{
  if (IsPchDmiLocked ()) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  //
  // program LPC BIOS Decode Enable, PCR[DMI] + 2744h to the same value programmed in LPC or SPI Offset D8h.
  //
  PchPcrWrite16 (PID_DMI, R_PCH_DMI_PCR_LPCBDE, BiosDecodeEnable);
  return EFI_SUCCESS;
}

/**
  Set PCH LPC/eSPI IO decode ranges in DMI
  Please check EDS for detail of LPC/eSPI IO decode ranges bit definition.
  Bit  12: FDD range
  Bit 9:8: LPT range
  Bit 6:4: ComB range
  Bit 2:0: ComA range

  @param[in] LpcIoDecodeRanges          LPC/eSPI IO decode ranges bit settings.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
PchDmiSetLpcIoDecodeRanges (
  IN  UINT16                            LpcIoDecodeRanges
  )
{
  //
  // This cycle decoding is only allowed to set when DMI is not locked.
  //
  if (IsPchDmiLocked ()) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  //
  // program LPC I/O Decode Ranges, PCR[DMI] + 2770h[15:0] to the same value programmed in LPC/eSPI PCI offset 80h.
  //
  PchPcrWrite16 (PID_DMI, R_PCH_DMI_PCR_LPCIOD, LpcIoDecodeRanges);
  return EFI_SUCCESS;
}

/**
  Set PCH LPC/eSPI IO enable decoding in DMI

  @param[in] LpcIoEnableDecoding        LPC/eSPI IO enable decoding bit settings.

  @retval EFI_SUCCESS                   Successfully completed.
  @retval EFI_UNSUPPORTED               DMIC.SRL is set.
**/
EFI_STATUS
PchDmiSetLpcIoEnable (
  IN  UINT16                            LpcIoEnableDecoding
  )
{
  //
  // This cycle decoding is only allowed to set when DMI is not locked.
  //
  if (IsPchDmiLocked ()) {
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  //
  // program LPC I/O Decode Ranges, PCR[DMI] + 2774h[15:0] to the same value programmed in LPC/eSPI PCI offset 82h.
  //
  PchPcrWrite16 (PID_DMI, R_PCH_DMI_PCR_LPCIOE, LpcIoEnableDecoding);
  return EFI_SUCCESS;
}


/**
  Set PCH IO port 80h cycle decoding to PCIE root port in DMI

  @param[in] RpNumber                   PCIE root port physical number.

  @retval EFI_SUCCESS                   Successfully completed.
**/
EFI_STATUS
PchDmiSetIoPort80Decode (
  IN  UINTN                             RpNumber
  )
{
  UINT16            DmiRpDestinationId;
  PSF_PORT_DEST_ID  PsfRpDestinationId;

  if (IsPchDmiLocked ()) {
    DEBUG ((DEBUG_ERROR, "PchIoPort80DecodeSet Error. DMI is locked.\n"));
    ASSERT (FALSE);
    return EFI_UNSUPPORTED;
  }

  ///
  /// IO port 80h is typically used by decoder/LED hardware for debug purposes.
  /// By default PCH will forward IO port 80h cycles to LPC bus. The Reserved Page Route (RPR) bit
  /// of General Control and Status register, located at PCR[DMI] + 274Ch[11] , allows software to
  /// re-direct IO port 80h cycles to PCIe bus so that a target (for example, a debug card) on
  /// PCIe bus can receive and claim these cycles.
  /// The "RPR Destination ID", PCR[DMI] + 274Ch[31:16] need to be set accordingly to point
  /// to the root port that decode this range. Reading from Port 80h may not return valid values
  /// if the POST-card itself do not shadow the writes. Unlike LPC, PCIe does not shadow the Port 80 writes.
  ///
  PsfRpDestinationId = PsfPcieDestinationId ((UINT32)RpNumber);

  DmiRpDestinationId = (UINT16)((0x2 << 12) |
                                (PsfRpDestinationId.Fields.PsfId << 8) |
                                (PsfRpDestinationId.Fields.PortGroupId << 7) |
                                (PsfRpDestinationId.Fields.PortId << 3) |
                                 PsfRpDestinationId.Fields.ChannelId);

  //
  // Program "RPR Destination ID", PCR[DMI] + 274Ch[31:16] to the Dest ID of RP.
  //
  PchPcrWrite16 (PID_DMI, R_PCH_DMI_PCR_GCS + 2, DmiRpDestinationId);
  //
  // Program "Reserved Page Route", PCR[DMI] + 274Ch[11] to '1'.
  // Use byte write on GCS+1 and leave the BILD bit which is RWO.
  //
  PchPcrAndThenOr8 (PID_DMI, R_PCH_DMI_PCR_GCS + 1, 0xFF, (B_PCH_DMI_PCR_RPR >> 8));

  return EFI_SUCCESS;
}

/**
  Set DMI thermal throttling to recommended configuration.
  It's intended only for DMI (PCH-H).
**/
VOID
PchDmiSetRecommendedThermalThrottling (
  VOID
  )
{
  if (IsPchWithPdmi ()) {
    PchDmi15SetRecommendedThermalThrottling ();
  }
}

/**
  Set DMI thermal throttling to custom configuration.
  This function will configure Thermal Sensor 0/1/2/3 TargetWidth and set
  DMI Thermal Sensor Autonomous Width Enable.
  It's intended only for DMI (PCH-H).

  @param[in] PchDmiThermalThrottling        DMI Thermal Throttling structure.
**/
VOID
PchDmiSetCustomThermalThrottling (
  IN PCH_DMI_THERMAL_THROTTLING      PchDmiThermalThrottling
  )
{
  if (IsPchWithPdmi ()) {
    PchDmi15SetCustomThermalThrottling (PchDmiThermalThrottling);
  }
}

/**
  Determines where to send the reserved page registers
  Accesses to the I/O ranges 80h - 8Fh will be forwarded to PCIe Root Port
  with the destination ID specified in GCS.RPRDID using DMI source decode.
**/
VOID
PchDmiSetReservedPageRegToPcieRootPort (
  VOID
  )
{
  PchPcrAndThenOr8 (
    PID_DMI, R_PCH_DMI_PCR_GCS + 1,
    (UINT8) ~0,
    (UINT8) (B_PCH_DMI_PCR_RPR >> 8)
    );
}

/**
  Determines where to send the reserved page registers
  DMI will not perform source decode on the I/O ranges 80h - 8Fh. The cycles hitting these ranges will
  end up in P2SB which will then forward the cycle to LPC or eSPI through IOSF Sideband.
**/
VOID
PchDmiSetReservedPageRegToLpc (
  VOID
  )
{
  PchPcrAndThenOr8 (
    PID_DMI, R_PCH_DMI_PCR_GCS + 1,
    (UINT8) (~(B_PCH_DMI_PCR_RPR >> 8)),
    0
    );
}

/**
  uCode Patch Region Enable (UPRE). Enables memory access targeting the uCode patch region (0xFEF00000 to 0xFEFFFFFF)
  to be forwarded to SPI Flash. This can only be set if the boot flash is on SPI.
**/
VOID
PchDmiEnableUCodePatchRegion (
  VOID
  )
{
  ///
  /// Setup "uCode Patch Region Enable", PCR [DMI] + 2748h[0] to '0b'
  ///
  PchPcrAndThenOr32 (PID_DMI, R_PCH_DMI_PCR_UCPR, (UINT32) ~B_PCH_DMI_PCR_UCPR_UPRE, 0);
}

/**
  Enable PCIe Relaxed Order
**/
VOID
PchDmiEnablePcieRelaxedOrder (
  VOID
  )
{
  //
  // Enable Forced Relaxed Ordering to always allow downstream completions to pass posted writes.
  // Set Completion Relaxed Ordering Attribute Override Value
  // and Completion Relaxed Ordering Attribute Override Enable
  //
  if (IsPchWithPdmi ()) {
    PchDmi15EnablePcieRelaxedOrder ();
  } else {
    PchDmi14EnablePcieRelaxedOrder ();
  }
}

/**
  This function will switch SAI value to be driven to IOSF Primary Fabric
  for cycles with Core BDF from HOSTIA_BOOT_SAI to HOSTIA_POSTBOOT_SAI.
  To be used when PCH is paired with CFL CPU.
**/
VOID
PchDmiEnablePostBootSai (
  VOID
  )
{
  if (IsPchWithPdmi ()) {
    PchDmi15EnablePostBootSai ();
  } else {
    PchDmi14EnablePostBootSai ();
  }
}

/**
  This function will do necessary configuration after platform
  should have switched to POSTBOOT_SAI. It needs to be called even if
  POSTBOOT_SAI was not set.
**/
VOID
PchDmiConfigAfterPostBootSai (
  VOID
  )
{
  if (IsPchWithPdmi ()) {
    PchDmi15ConfigAfterPostBootSai ();
  }
}

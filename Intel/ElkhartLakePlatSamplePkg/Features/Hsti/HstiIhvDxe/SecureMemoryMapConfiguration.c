/** @file
  This file contains the tests for the SecureMemoryMapConfiguration bit

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

@par Specification
**/

#include "HstiIhvDxe.h"
#include <Library/SpiAccessLib.h>
#include <Library/BootMediaLib.h>
#include <Register/CpuPcieRegs.h>
#include "CpuPcieInfo.h"

#define B_VENDOR_ID_MASK               (0xFFFF)
#define B_PEG_MEMORY_BAR_MASK          (0xF)
#define B_PEG_MEMORY_RANGE_MASK        (0xFFF0)
#define B_REGBAR_BAR_MASK              (0x7FFFFFF000)
// BIOS always keeps Below BAR address below 4G
#define B_VTD_BAR_MASK                 (0xFFFFF000)
#define B_EDRAMBAR_BAR_MASK            (0xFFFFC000)
#define B_GTTMMADR_MASK                (0x7FFF000000)
#define B_GMADR_MASK                   (0x7FF8000000)
#define B_TMBAR_BAR_MASK               (0xFFFF8000)

typedef struct {
  UINT64   Base;
  UINT64   End;
} MEMORY_RANGE;

typedef enum {
  LockableMemoryRangeLtSpace,
  LockableMemoryRangeHighBios,
  LockableMemoryRangeLowDram,
  LockableMemoryRangeHighDram,
  LockableMemoryRangeMchBar,
  LockableMemoryRangeDmiBar,
  LockableMemoryRangePxpEpBar,
  LockableMemoryRangeGfxVtBar,
  LockableMemoryRangeIPUVtBar,
  LockableMemoryRangeVtdPvc0Bar,
  LockableMemoryRangeRegBar,
  LockableMemoryRangeEdramBar,
  LockableMemoryRangeCpuRsvd1Bar,
  LockableMemoryRangeCpuRsvd2Bar,
  LockableMemoryRangeMax,
} LOCKABLE_MEMORY_RANGE;

MEMORY_RANGE  mLockableMemoryRange[LockableMemoryRangeMax] = {
  // 0. LT space (0xFED20000 - 0xFED7FFFF)
  {0xFED20000, 0xFED7FFFF},
  // 1. High BIOS
  {0x0, SIZE_4GB - 1},
  // 2. Low DRAM (0 - TOLUD)
  {0x0, 0},
  // 3. High DRAM (4GB - TOUUD)
  {SIZE_4GB, 0},
  // 4. MCHBAR
  {0, 0},
  // 5. DMIBAR
  {0, 0},
  // 6. PXPEPBAR
  {0, 0},
  // 7. GFXVTBAR
  {0, 0},
  // 8. IPUVTBAR
  {0, 0},
  // 9. VTDPVC0BAR
  {0, 0},
  // 10. REGBAR
  {0, 0},
  // 11. EDRAMBAR (MCHBAR + 0x5408)
  {0, 0},
  // 12. CPU Reserved space: 0xFEB00000 to 0xFEB0FFFF
  {0xFEB00000, 0xFEB0FFFF},
  // 13. CPU Reserved space: 0xFEB80000 to 0xFEB8FFFF
  {0xFEB80000, 0xFEB8FFFF},
};

typedef enum {
  NonLockableMemoryRangeMBASE0,
  NonLockableMemoryRangePMBASE0,
  NonLockableMemoryRangeMBASE1,
  NonLockableMemoryRangePMBASE1,
  NonLockableMemoryRangeMBASE2,
  NonLockableMemoryRangePMBASE2,
  NonLockableMemoryRangeMBASE3,
  NonLockableMemoryRangePMBASE3,
  NonLockableMemoryRangeGTTMMADR,
  NonLockableMemoryRangeGMADR,
  NonLockableMemoryRangeTMBAR,
  NonLockableMemoryRangeABAR,
  NonLockableMemoryRangeSBREG_BAR,
  NonLockableMemoryRangePWRMBASE,
  NonLockableMemoryRangeSPI_BAR0,
  NonLockableMemoryRangeMax,
} NONLOCKABLE_MEMORY_RANGE;

typedef union {
  struct {
    UINT32  Low;
    UINT32  High;
  } Data32;
  UINT64 Data;
} UINT64_STRUCT;

MEMORY_RANGE  mNonLockableMemoryRange[NonLockableMemoryRangeMax] = {
  //     Local Apic for each CPU thread (IA32_APICBASE MSR 0x1B)
  // 0.  MBASE0,  (PEG) BDF 0:1:0  + 0x20
  // 1.  PMBASE0, (PEG) BDF 0:1:0  + 0x24 LOW
  //                    BDF 0:1:0  + 0x28 HIGH
  {0, 0},
  {0, 0},
  // 2.  MBASE1,  (PEG) BDF 0:1:1  + 0x20
  // 3.  PMBASE1, (PEG) BDF 0:1:1  + 0x24 LOW
  //                    BDF 0:1:1  + 0x28 HIGH
  {0, 0},
  {0, 0},
  // 4.  MBASE2,  (PEG) BDF 0:1:2  + 0x20
  // 5.  PMBASE2, (PEG) BDF 0:1:2  + 0x24 LOW
  //                    BDF 0:1:2  + 0x28 HIGH
  {0, 0},
  {0, 0},
  // 6.  MBASE3,  (PEG) BDF 0:6:0  + 0x20
  // 7.  PMBASE3, (PEG) BDF 0:6:0  + 0x24 LOW
  //                    BDF 0:6:0  + 0x28 HIGH
  {0, 0},
  {0, 0},
  // 8.  GTTMMADR,      BDF 0:2:0  + 0x10
  {0, 0},
  // 9.  GMADR,         BDF 0:2:0  + 0x18 (Need to account for MSAC)
  {0, 0},
  // 10. TMBAR,         BDF 0:4:0  + 0x10 (if Device 4 is enabled in PCI MC 0:0:0 + 0x54[7])
  {0, 0},
  // 11. ABAR,          BDF 0:23:0 + 0x24 (AHCI Base Address)
  {0, 0},
  // 12. SBREG_BAR (BDF 0:31:1 + 0x10)
  {PCH_PCR_BASE_ADDRESS, PCH_PCR_BASE_ADDRESS + PCH_PCR_MMIO_SIZE-1},
  // 13. PWRMBASE (BDF 0:31:2 + 0x48)
  {0, 0},
  // 14. SPI_BAR0 (BDF 0:31:5 + 0x10)
  {0, 0},
};

PCH_SPI_PROTOCOL       *mSpiProtocol;

/**
  Check for overlaps in single range array

  @param[in] Range     - Pointer to Range array
  @param[in] Count     - Number of Enties

  @retval BOOLEAN - Overlap Exists
**/
BOOLEAN
CheckOverlap (
  IN MEMORY_RANGE *Range,
  IN UINTN        Count
  )
{
  UINTN  Index;
  UINTN  SubIndex;

  for (Index = 0; Index < Count - 1; Index++) {
    if ((Range[Index].Base == 0) && (Range[Index].End == 0)) {
      continue;
    }
    for (SubIndex = Index + 1; SubIndex < Count; SubIndex++) {
      if ((Range[SubIndex].Base == 0) && (Range[SubIndex].End == 0)) {
        continue;
      }
      if (((Range[Index].Base >= Range[SubIndex].Base) && (Range[Index].Base <= Range[SubIndex].End)) ||
          ((Range[SubIndex].Base >= Range[Index].Base) && (Range[SubIndex].Base <= Range[Index].End))) {
        DEBUG ((DEBUG_ERROR, "        OVERLAP: \n"));
        DEBUG ((DEBUG_ERROR, "          0x%016lx - 0x%016lx\n", Range[Index].Base, Range[Index].End));
        DEBUG ((DEBUG_ERROR, "          0x%016lx - 0x%016lx\n", Range[SubIndex].Base, Range[SubIndex].End));
        return TRUE;
      }
    }
  }

  DEBUG ((DEBUG_INFO, "        CheckOverlap: PASS\n"));
  return FALSE;
}

/**
  Check for overlaps between two arrays of memory ranges

  @param[in] Range1     - Pointer to Range1 array
  @param[in] Count1     - Number of Enties
  @param[in] Range2     - Pointer to Range2 array
  @param[in] Count2     - Number of Enties

  @retval BOOLEAN - Overlap Exists
**/
BOOLEAN
CheckOverlap2 (
  IN MEMORY_RANGE *Range1,
  IN UINTN        Count1,
  IN MEMORY_RANGE *Range2,
  IN UINTN        Count2
  )
{
  UINTN  Index1;
  UINTN  Index2;

  for (Index1 = 0; Index1 < Count1; Index1++) {
    if ((Range1[Index1].Base == 0) && (Range1[Index1].End == 0)) {
      continue;
    }
    for (Index2 = 0; Index2 < Count2; Index2++) {
      if ((Range2[Index2].Base == 0) && (Range2[Index2].End == 0)) {
        continue;
      }
      if (((Range1[Index1].Base >= Range2[Index2].Base) && (Range1[Index1].Base <= Range2[Index2].End)) ||
          ((Range2[Index2].Base >= Range1[Index1].Base) && (Range2[Index2].Base <= Range1[Index1].End))) {
        DEBUG ((DEBUG_ERROR, "        OVERLAP2: \n"));
        DEBUG ((DEBUG_ERROR, "          0x%016lx - 0x%016lx\n", Range1[Index1].Base, Range1[Index1].End));
        DEBUG ((DEBUG_ERROR, "          0x%016lx - 0x%016lx\n", Range2[Index2].Base, Range2[Index2].End));
        return TRUE;
      }
    }
  }

  DEBUG ((DEBUG_INFO, "        CheckOverlap2: PASS\n"));
  return FALSE;
}

/**
  Dumps Ranges to Serial

  @param[in] Range     - Pointer to Range array
  @param[in] Count     - Number of Enties

**/
VOID
DumpRange (
  IN MEMORY_RANGE *Range,
  IN UINTN        Count
  )
{
  UINTN  Index;

  for (Index = 0; Index < Count; Index ++) {
    DEBUG ((DEBUG_INFO, "        [%02d] 0x%016lx - 0x%016lx\n", Index, Range[Index].Base, Range[Index].End));
  }
}

/**
  Run tests for SecureMemoryMapConfiguration bit
**/
VOID
CheckSecureMemoryMapConfiguration (
  VOID
  )
{
  EFI_STATUS        Status;
  BOOLEAN           Result;
  UINT32            BarRead;
  UINT16            VendorIdRead;
  UINT32            PwrmBase;
  UINTN             PchSpiBase;
  UINT32            SaMchBar;
  UINT64_STRUCT     Data64;
  UINT32            Data32;
  UINT64            McD0BaseAddress;
  UINT64            McD2BaseAddress;
  UINT32            ApertureSize;
  UINT8             Msac;
  UINT64            PegBaseAddress;
  UINT32            BaseAddr;
  UINT32            BiosRegionSize;


  if ((mFeatureImplemented[1] & HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION) == 0) {
    return;
  }

  Result = TRUE;

  SaMchBar        = PciSegmentRead32(
                      PCI_SEGMENT_LIB_ADDRESS(
                        SA_SEG_NUM,
                        SA_MC_BUS,
                        SA_MC_DEV,
                        SA_MC_FUN,
                        R_SA_MCHBAR)
                      ) & ~BIT0;

  McD0BaseAddress = PCI_SEGMENT_LIB_ADDRESS (
                      SA_SEG_NUM,
                      SA_MC_BUS,
                      SA_MC_DEV,
                      SA_MC_FUN,
                      0
                      );

  DEBUG ((DEBUG_INFO, "      SaMchBar =  0x%016lx\n", SaMchBar));
  DEBUG ((DEBUG_INFO, "      Lockable/Fixed Memory Ranges Overlap Test\n"));
  //
  // LT Space Fixed Memory Range
  //

  if (BootMediaIsSpi ()) {
    //
    // Locate the SPI protocol.
    //
    Status = gBS->LocateProtocol (
                      &gPchSpiProtocolGuid,
                      NULL,
                      (VOID **) &mSpiProtocol
                      );

    if (EFI_ERROR (Status)) {
      ASSERT_EFI_ERROR (Status);
      DEBUG ((DEBUG_ERROR,"  Failed to locate gPchSpiProtocolGuid Protocol\n"));
      DEBUG ((DEBUG_ERROR,"    Unable to compute High BIOS Memory Size [3], it may incorrectly overlap\n"));
      BiosRegionSize = 0;
    } else {
      mSpiProtocol->GetRegionAddress (mSpiProtocol, FlashRegionBios, &BaseAddr, &BiosRegionSize);
    }
  } else {
    DEBUG ((DEBUG_INFO, " Use PCD to determine Bios Size when boot Media is UFS\n"));
    BiosRegionSize = PcdGet32 (PcdBiosSize);
  }

  //
  // High BIOS Memory & Low DRAM Memory Range
  //
  DEBUG ((DEBUG_INFO, "        High BIOS Flash Region Size = 0x%x\n", BiosRegionSize));
  mLockableMemoryRange[LockableMemoryRangeHighBios].Base  = SIZE_4GB - BiosRegionSize;
  mLockableMemoryRange[LockableMemoryRangeLowDram].End = (PciSegmentRead32 (McD0BaseAddress + R_SA_TOLUD) &
                                                         B_SA_TOLUD_TOLUD_MASK) - 1;

  //
  // High DRAM Memory Range
  //
  Data64.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_TOUUD + 4);
  Data64.Data32.Low  = PciSegmentRead32 (McD0BaseAddress + R_SA_TOUUD);
  mLockableMemoryRange[LockableMemoryRangeHighDram].End = (Data64.Data & B_SA_TOUUD_TOUUD_MASK) - 1;

  //
  // MCHBAR (SA) Memory Range
  //
  mLockableMemoryRange[LockableMemoryRangeMchBar].Base = SaMchBar;
  mLockableMemoryRange[LockableMemoryRangeMchBar].End  = mLockableMemoryRange[LockableMemoryRangeMchBar].Base + SIZE_32KB - 1;

  //
  // DMIBAR Memory Range
  //
  Data64.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_DMIBAR + 4);
  Data64.Data32.Low  = PciSegmentRead32 (McD0BaseAddress + R_SA_DMIBAR);
  mLockableMemoryRange[LockableMemoryRangeDmiBar].Base = Data64.Data & B_SA_DMIBAR_DMIBAR_MASK;
  mLockableMemoryRange[LockableMemoryRangeDmiBar].End  = mLockableMemoryRange[LockableMemoryRangeDmiBar].Base + SIZE_4KB - 1;

  //
  // PXPEPBAR
  //
  Data64.Data32.High = PciSegmentRead32 (McD0BaseAddress + R_SA_PXPEPBAR + 4);
  Data64.Data32.Low  = PciSegmentRead32 (McD0BaseAddress +  R_SA_PXPEPBAR);
  mLockableMemoryRange[LockableMemoryRangePxpEpBar].Base = Data64.Data & B_SA_PXPEPBAR_PXPEPBAR_MASK;
  mLockableMemoryRange[LockableMemoryRangePxpEpBar].End  = mLockableMemoryRange[LockableMemoryRangePxpEpBar].Base + SIZE_4KB - 1;

  //
  // VTD1 Engine Memory Range (GFXVTBAR)
  //
  Data32 = MmioRead32 (SaMchBar + R_MCHBAR_VTD1_OFFSET);
  if ((Data32 & BIT0) != 0) {
    mLockableMemoryRange[LockableMemoryRangeGfxVtBar].Base = Data32 & B_VTD_BAR_MASK;
    mLockableMemoryRange[LockableMemoryRangeGfxVtBar].End  = mLockableMemoryRange[LockableMemoryRangeGfxVtBar].Base + 0x1000 - 1;
  }

  //
  // VTD2 Engine Memroy Range (IPUVTBAR)
  //
  Data32 = MmioRead32 (SaMchBar + R_MCHBAR_VTD2_LOW_OFFSET);
  if ((Data32 & BIT0) != 0) {
    mLockableMemoryRange[LockableMemoryRangeIPUVtBar].Base = Data32 & B_VTD_BAR_MASK;
    mLockableMemoryRange[LockableMemoryRangeIPUVtBar].End  = mLockableMemoryRange[LockableMemoryRangeIPUVtBar].Base + 0x1000 - 1;
  }
  //
  // VTD9 Engine Memory Range (VTDPVC0BAR)
  //
  Data32 = MmioRead32 (SaMchBar + R_MCHBAR_VTD3_OFFSET);
  if ((Data32 & BIT0) != 0) {
    mLockableMemoryRange[LockableMemoryRangeVtdPvc0Bar].Base = Data32 & B_VTD_BAR_MASK;
    mLockableMemoryRange[LockableMemoryRangeVtdPvc0Bar].End  = mLockableMemoryRange[LockableMemoryRangeVtdPvc0Bar].Base + 0x1000 - 1;
  }

  //
  // REGBAR Memory Range
  //
  Data64.Data = (UINT64)(MmioRead32 (SaMchBar + R_SA_MCHBAR_REGBAR_OFFSET)) +
                LShiftU64((UINT64)MmioRead32 (SaMchBar + R_SA_MCHBAR_REGBAR_OFFSET + 4), 32);
  if ((Data64.Data & BIT0) != 0) {
    mLockableMemoryRange[LockableMemoryRangeRegBar].Base = Data64.Data & B_REGBAR_BAR_MASK;
    mLockableMemoryRange[LockableMemoryRangeRegBar].End  = mLockableMemoryRange[LockableMemoryRangeRegBar].Base + 0x1000 - 1;
  }

  //
  //EDRAMBAR Memory Range
  //
  Data32 = MmioRead32 (SaMchBar + R_SA_MCHBAR_EDRAMBAR_OFFSET);

  if ((Data32 & BIT0) != 0) {
    mLockableMemoryRange[LockableMemoryRangeEdramBar].Base = Data32 & B_EDRAMBAR_BAR_MASK;
    mLockableMemoryRange[LockableMemoryRangeEdramBar].End  = mLockableMemoryRange[LockableMemoryRangeEdramBar].Base + 0x4000 - 1;
  }

  //
  // CPU Reserved Fixed Memory Range Spaces
  //
  DEBUG ((DEBUG_INFO, "        INFO: Lockable Memory Ranges:\n"));
  DumpRange (mLockableMemoryRange, LockableMemoryRangeMax);
  if (CheckOverlap (mLockableMemoryRange, LockableMemoryRangeMax)) {
  DEBUG((DEBUG_INFO, "        Unexpected Status: Fixed MMIO Regions Overlap\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_UNEXP_STATUS_CODE_2,
      HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_UNEXP_STATUS_STRING_2
      );
    Result = FALSE;
  }

  DEBUG((DEBUG_INFO, "      Non Lockable Memory Ranges Overlap Test\n"));
  //
  // Check if PEG is Present
  //
  PegBaseAddress  = PCI_SEGMENT_LIB_ADDRESS (
                      SA_SEG_NUM,
                      SA_PEG_BUS_NUM,
                      SA_PEG_DEV_NUM,
                      SA_PEG0_FUN_NUM,
                      PCI_VENDOR_ID_OFFSET
                      );

  if (PciSegmentRead16 (PegBaseAddress) != B_VENDOR_ID_MASK) {
    //
    // Check 0:1:0 (PEG10) is enabled
    // MBASE & MLIMIT
    //
    if (PciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN) & B_SA_DEVEN_D1F0EN_MASK) {
      mNonLockableMemoryRange[NonLockableMemoryRangeMBASE0].Base = LShiftU64 ((UINT64)(
                                                                     PciSegmentRead16 (
                                                                       PCI_SEGMENT_LIB_ADDRESS (
                                                                         SA_SEG_NUM,
                                                                         SA_PEG_BUS_NUM,
                                                                         SA_PEG0_DEV_NUM,
                                                                         SA_PEG0_FUN_NUM,
                                                                         0x20)) &
                                                                       B_PEG_MEMORY_RANGE_MASK),
                                                                     16
                                                                     );
      mNonLockableMemoryRange[NonLockableMemoryRangeMBASE0].End = LShiftU64 ((UINT64)(
                                                                    PciSegmentRead16 (
                                                                      PCI_SEGMENT_LIB_ADDRESS (
                                                                        SA_SEG_NUM,
                                                                        SA_PEG_BUS_NUM,
                                                                        SA_PEG0_DEV_NUM,
                                                                        SA_PEG0_FUN_NUM,
                                                                        0x22)) &
                                                                      B_PEG_MEMORY_RANGE_MASK),
                                                                    16
                                                                    );
      //
      // PMBASE
      //
      BarRead = PciSegmentRead16 (
                  PCI_SEGMENT_LIB_ADDRESS (
                    SA_SEG_NUM,
                    SA_PEG_BUS_NUM,
                    SA_PEG0_DEV_NUM,
                    SA_PEG0_FUN_NUM,
                    0x24)
                  );
      //
      // PMBASEU
      //
      if ((BarRead & B_PEG_MEMORY_BAR_MASK) != 0) {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].Base = LShiftU64 ((BarRead & B_PEG_MEMORY_RANGE_MASK), 16) +
                                                                      LShiftU64 (
                                                                        (UINT64)PciSegmentRead32 (
                                                                                  PCI_SEGMENT_LIB_ADDRESS (
                                                                                    SA_SEG_NUM,
                                                                                    SA_PEG_BUS_NUM,
                                                                                    SA_PEG0_DEV_NUM,
                                                                                    SA_PEG0_FUN_NUM,
                                                                                    0x28)),
                                                                                  32
                                                                                  );
      } else {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].Base = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16);
      }
      //
      // PMLIMIT
      //
      BarRead = PciSegmentRead16 (
                  PCI_SEGMENT_LIB_ADDRESS (
                    SA_SEG_NUM,
                    SA_PEG_BUS_NUM,
                    SA_PEG0_DEV_NUM,
                    SA_PEG0_FUN_NUM,
                    0x26)
                  );
      if ((BarRead & B_PEG_MEMORY_BAR_MASK) != 0) {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].End = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16) +
                                                                     LShiftU64 (
                                                                       (UINT64)PciSegmentRead32 (
                                                                                 PCI_SEGMENT_LIB_ADDRESS (
                                                                                   0,
                                                                                   SA_PEG_BUS_NUM,
                                                                                   SA_PEG0_DEV_NUM,
                                                                                   SA_PEG0_FUN_NUM,
                                                                                   0x2C)),
                                                                                 32
                                                                                 );
      } else {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE0].End = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16);
      }
    }

    //
    // Check 0:1:1 (PEG11) is enabled
    //
    if (PciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN) & B_SA_DEVEN_D1F1EN_MASK) {
      //
      // MBASE & MLIMIT
      //
      mNonLockableMemoryRange[NonLockableMemoryRangeMBASE1].Base = LShiftU64 (
                                                                     (UINT64)(PciSegmentRead16 (
                                                                                PCI_SEGMENT_LIB_ADDRESS (
                                                                                SA_SEG_NUM,
                                                                                SA_PEG_BUS_NUM,
                                                                                SA_PEG1_DEV_NUM,
                                                                                SA_PEG1_FUN_NUM,
                                                                                0x20)) &
                                                                              B_PEG_MEMORY_RANGE_MASK),
                                                                            16
                                                                            );
      mNonLockableMemoryRange[NonLockableMemoryRangeMBASE1].End  = LShiftU64 (
                                                                     (UINT64)(PciSegmentRead16 (
                                                                                PCI_SEGMENT_LIB_ADDRESS (
                                                                                SA_SEG_NUM,
                                                                                SA_PEG_BUS_NUM,
                                                                                SA_PEG1_DEV_NUM,
                                                                                SA_PEG1_FUN_NUM,
                                                                                0x22)) &
                                                                              B_PEG_MEMORY_RANGE_MASK),
                                                                            16
                                                                            );
      //
      // PMBASE
      //
      BarRead = PciSegmentRead16 (
                  PCI_SEGMENT_LIB_ADDRESS (
                    SA_SEG_NUM,
                    SA_PEG_BUS_NUM,
                    SA_PEG1_DEV_NUM,
                    SA_PEG1_FUN_NUM,
                    0x24)
                  );
      //
      // PMBASEU
      //
      if ((BarRead & B_PEG_MEMORY_BAR_MASK) != 0) {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].Base = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK), 16) +
                                                                      LShiftU64 (
                                                                        (UINT64)PciSegmentRead16 (
                                                                                  PCI_SEGMENT_LIB_ADDRESS (
                                                                                  SA_SEG_NUM,
                                                                                  SA_PEG_BUS_NUM,
                                                                                  SA_PEG1_FUN_NUM,
                                                                                  SA_PEG1_FUN_NUM,
                                                                                  0x28)),
                                                                                32
                                                                                );
      } else {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].Base = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16);
      }
      //
      // PMLIMIT
      //
      BarRead = PciSegmentRead16 (
                  PCI_SEGMENT_LIB_ADDRESS (
                    SA_SEG_NUM,
                    SA_PEG_BUS_NUM,
                    SA_PEG1_FUN_NUM,
                    SA_PEG1_FUN_NUM,
                    0x26)
                  );
      if ((BarRead & B_PEG_MEMORY_BAR_MASK) != 0) {
        //
        // PMLIMITU
        //
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].End = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK), 16) +
                                                                     LShiftU64 (
                                                                       (UINT64)PciSegmentRead16 (
                                                                                 PCI_SEGMENT_LIB_ADDRESS (
                                                                                 SA_SEG_NUM,
                                                                                 SA_PEG_BUS_NUM,
                                                                                 SA_PEG1_FUN_NUM,
                                                                                 SA_PEG1_FUN_NUM,
                                                                                 0x2C)),
                                                                               32
                                                                               );
      } else {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE1].End = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16);
      }
    }
    //
    // Check Device 0:1:2 (PEG12) is enabled
    //
    if (PciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN) & B_SA_DEVEN_D1F2EN_MASK) {
      //
      // MBASE & MLIMIT
      //
      mNonLockableMemoryRange[NonLockableMemoryRangeMBASE2].Base = LShiftU64 (
                                                                     (UINT64)(PciSegmentRead16 (
                                                                                PCI_SEGMENT_LIB_ADDRESS (
                                                                                SA_SEG_NUM,
                                                                                SA_PEG_BUS_NUM,
                                                                                SA_PEG2_DEV_NUM,
                                                                                SA_PEG2_FUN_NUM,
                                                                                0x20)) &
                                                                                B_PEG_MEMORY_RANGE_MASK),
                                                                              16
                                                                              );
      mNonLockableMemoryRange[NonLockableMemoryRangeMBASE2].End = LShiftU64 (
                                                                    (UINT64)(PciSegmentRead16 (
                                                                               PCI_SEGMENT_LIB_ADDRESS (
                                                                               SA_SEG_NUM,
                                                                               SA_PEG_BUS_NUM,
                                                                               SA_PEG2_DEV_NUM,
                                                                               SA_PEG2_FUN_NUM,
                                                                               0x22)) &
                                                                               B_PEG_MEMORY_RANGE_MASK),
                                                                             16
                                                                             );
      //
      // PMBASE
      //
      BarRead = PciSegmentRead16 (
                  PCI_SEGMENT_LIB_ADDRESS (
                    SA_SEG_NUM,
                    SA_PEG_BUS_NUM,
                    SA_PEG2_DEV_NUM,
                    SA_PEG2_FUN_NUM,
                    0x24)
                  );
      if ((BarRead & B_PEG_MEMORY_BAR_MASK) != 0) {
        //
        // PMBASEU
        //
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].Base = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16) +
                                                                      LShiftU64 (
                                                                        (UINT64)PciSegmentRead16 (
                                                                                  PCI_SEGMENT_LIB_ADDRESS (
                                                                                  SA_SEG_NUM,
                                                                                  SA_PEG_BUS_NUM,
                                                                                  SA_PEG2_DEV_NUM,
                                                                                  SA_PEG2_FUN_NUM,
                                                                                  0x28)),
                                                                                32
                                                                                );
      } else {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].Base = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16);
      }
      //
      // PMLIMIT
      //
      BarRead = PciSegmentRead16 (
                  PCI_SEGMENT_LIB_ADDRESS (
                    SA_SEG_NUM,
                    SA_PEG_BUS_NUM,
                    SA_PEG2_DEV_NUM,
                    SA_PEG2_FUN_NUM,
                    0x26)
                  );

      if ((BarRead & B_PEG_MEMORY_BAR_MASK) != 0) {
        //
        // PMLIMITU
        //
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].End = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16) +
                                                                     LShiftU64 (
                                                                       (UINT64)PciSegmentRead16 (
                                                                         PCI_SEGMENT_LIB_ADDRESS (
                                                                           SA_SEG_NUM,
                                                                           SA_PEG_BUS_NUM,
                                                                           SA_PEG2_DEV_NUM,
                                                                           SA_PEG2_FUN_NUM,
                                                                           0x2C)),
                                                                         32
                                                                         );
      } else {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE2].End = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16);
      }
    }
    //
    // Check 0:6:0 (PEG3) is enabled
    //
    if (PciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN) & B_SA_DEVEN_D6EN_MASK) {
      //
      // MBASE & MLIMIT
      //
      mNonLockableMemoryRange[NonLockableMemoryRangeMBASE3].Base = LShiftU64 (
                                                                     (UINT64)(PciSegmentRead16 (
                                                                                PCI_SEGMENT_LIB_ADDRESS (
                                                                                SA_SEG_NUM,
                                                                                SA_PEG_BUS_NUM,
                                                                                SA_PEG3_DEV_NUM,
                                                                                SA_PEG3_FUN_NUM,
                                                                                0x20)) &
                                                                                B_PEG_MEMORY_RANGE_MASK),
                                                                              16
                                                                              );
      mNonLockableMemoryRange[NonLockableMemoryRangeMBASE3].End  = LShiftU64 (
                                                                     (UINT64)(PciSegmentRead16 (
                                                                                PCI_SEGMENT_LIB_ADDRESS (
                                                                                SA_SEG_NUM,
                                                                                SA_PEG_BUS_NUM,
                                                                                SA_PEG3_DEV_NUM,
                                                                                SA_PEG3_FUN_NUM,
                                                                                0x22)) &
                                                                                B_PEG_MEMORY_RANGE_MASK),
                                                                              16
                                                                              );
      //
      // PMBASE
      //
      BarRead = PciSegmentRead16 (
                  PCI_SEGMENT_LIB_ADDRESS (
                    SA_SEG_NUM,
                    SA_PEG_BUS_NUM,
                    SA_PEG3_DEV_NUM,
                    SA_PEG3_FUN_NUM,
                    0x24)
                  );
      if ((BarRead & B_PEG_MEMORY_BAR_MASK) != 0) {
        //
        // PMBASEU
        //
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE3].Base = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16) +
                                                                      LShiftU64 (
                                                                        (UINT64)PciSegmentRead16 (
                                                                                  PCI_SEGMENT_LIB_ADDRESS (
                                                                                    SA_SEG_NUM,
                                                                                    SA_PEG_BUS_NUM,
                                                                                    SA_PEG3_DEV_NUM,
                                                                                    SA_PEG3_FUN_NUM,
                                                                                    0x28)),
                                                                                  32
                                                                                  );
      } else {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE3].Base = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16);
      }
      //
      // PMLIMIT
      //
      BarRead = PciSegmentRead16 (
                  PCI_SEGMENT_LIB_ADDRESS (
                    SA_SEG_NUM,
                    SA_PEG_BUS_NUM,
                    SA_PEG3_DEV_NUM,
                    SA_PEG3_FUN_NUM,
                    0x26)
                  );

      if ((BarRead & B_PEG_MEMORY_BAR_MASK) != 0) {
        //
        // PMLIMITU
        //
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE3].End = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16) +
                                                                     LShiftU64 (
                                                                       (UINT64)PciSegmentRead16 (
                                                                                 PCI_SEGMENT_LIB_ADDRESS (
                                                                                 SA_SEG_NUM,
                                                                                 SA_PEG_BUS_NUM,
                                                                                 SA_PEG3_DEV_NUM,
                                                                                 SA_PEG3_FUN_NUM,
                                                                                 0x2C)),
                                                                               32
                                                                               );
      } else {
        mNonLockableMemoryRange[NonLockableMemoryRangePMBASE3].End = LShiftU64 ((UINT64)(BarRead & B_PEG_MEMORY_RANGE_MASK),16);
      }
    }
  }

  McD2BaseAddress = PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_IGD_BUS, SA_IGD_DEV, SA_IGD_FUN_0, 0);
  if (PciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN) & B_SA_DEVEN_D2EN_MASK) {
    //
    // GTTMMADR Memory Range
    //
    Data64.Data32.High = PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR + 4);
    Data64.Data32.Low  = PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GTTMMADR);

    mNonLockableMemoryRange[NonLockableMemoryRangeGTTMMADR].Base = Data64.Data & B_GTTMMADR_MASK;
    mNonLockableMemoryRange[NonLockableMemoryRangeGTTMMADR].End  = mNonLockableMemoryRange[NonLockableMemoryRangeGTTMMADR].Base + SIZE_16MB - 1;

    //
    // GMADR Memory Range
    //
    Data64.Data32.High = PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GMADR + 4);
    Data64.Data32.Low  = PciSegmentRead32 (McD2BaseAddress + R_SA_IGD_GMADR);

    Msac = PciSegmentRead8 (McD2BaseAddress + R_SA_IGD_MSAC_OFFSET);
    ApertureSize = ((Msac & (BIT20 | BIT19 | BIT18 | BIT17 | BIT16)) + 1) * SIZE_128MB;
    mNonLockableMemoryRange[NonLockableMemoryRangeGMADR].Base = Data64.Data & B_GMADR_MASK;
    mNonLockableMemoryRange[NonLockableMemoryRangeGMADR].End  = mNonLockableMemoryRange[NonLockableMemoryRangeGMADR].Base + ApertureSize - 1;
  }

  if (PciSegmentRead32 (McD0BaseAddress + R_SA_DEVEN) & B_SA_DEVEN_D4EN_MASK) {
    //
    // TMBAR Memory Range
    //
    Data32 = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (0, 0, 4, 0, 0x10));

    mNonLockableMemoryRange[NonLockableMemoryRangeTMBAR].Base = Data32 & B_TMBAR_BAR_MASK;
    mNonLockableMemoryRange[NonLockableMemoryRangeTMBAR].End  = mNonLockableMemoryRange[NonLockableMemoryRangeTMBAR].Base + SIZE_32KB-1;
  }

  //
  // ABAR Memory Range
  //
  VendorIdRead   = PciSegmentRead16 (SataRegBase (SATA_1_CONTROLLER_INDEX));
  DEBUG ((DEBUG_INFO, "      INFO: VendorIdRead SATA: %x\n", VendorIdRead));

  if (VendorIdRead != B_VENDOR_ID_MASK) {
    if (SataControllerFunctionDisableStatus (SATA_1_CONTROLLER_INDEX) == 0 ) {
      mNonLockableMemoryRange[NonLockableMemoryRangeABAR].Base = GetSataAhciBase (SATA_1_CONTROLLER_INDEX);

      mNonLockableMemoryRange[NonLockableMemoryRangeABAR].End  = mNonLockableMemoryRange[NonLockableMemoryRangeABAR].Base +
                                                                 GetSataAbarSize (SATA_1_CONTROLLER_INDEX) - 1;
    }
  }

  //
  // SBREG_BAR Memory Range Fixed
  //

  //
  // PWRMBASE Memory Range
  //
  PwrmBase = PmcGetPwrmBase ();
  mNonLockableMemoryRange[NonLockableMemoryRangePWRMBASE].Base = PwrmBase;
  mNonLockableMemoryRange[NonLockableMemoryRangePWRMBASE].End  = PwrmBase + PCH_PWRM_MMIO_SIZE-1;

  //
  // SPI_BAR0 Memory Range
  //
  PchSpiBase = SpiGetBar0 ();
  mNonLockableMemoryRange[NonLockableMemoryRangeSPI_BAR0].Base = PchSpiBase;
  mNonLockableMemoryRange[NonLockableMemoryRangeSPI_BAR0].End  = PchSpiBase + SIZE_4KB-1;

  DEBUG ((DEBUG_INFO, "        INFO: Non Lockable Memory Ranges:\n"));
  DumpRange (mNonLockableMemoryRange, NonLockableMemoryRangeMax);
  if (CheckOverlap (mNonLockableMemoryRange, NonLockableMemoryRangeMax) ||
      CheckOverlap2 (mLockableMemoryRange, LockableMemoryRangeMax, mNonLockableMemoryRange, NonLockableMemoryRangeMax)) {
    DEBUG((DEBUG_INFO, "        Unexpected Status: Non Lockable MMIO Ranges Overlap Other Critical Regions\n"));

    BuildAndAppendHstiStatusString (
      HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_UNEXP_STATUS_CODE_3,
      HSTI_MEMORY_MAP_SECURITY_CONFIGURATION,
      HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION_UNEXP_STATUS_STRING_3
      );
    Result = FALSE;
  }

  //
  // ALL PASS
  //
  if (Result) {
    Status = HstiLibSetFeaturesVerified (
               PLATFORM_SECURITY_ROLE_PLATFORM_REFERENCE,
               NULL,
               1,
               HSTI_BYTE1_SECURE_MEMORY_MAP_CONFIGURATION
               );
    CheckStatusForHstiLibSet (Status);
  }

  return;
}

/** @file
  This file contains P States and Turbo Power Management configuration functions for
  processors.

  <b>Acronyms:</b>
     - PPM:  Processor Power Management
     - TM:   Thermal Monitor
     - IST:  Intel(R) Speedstep technology
     - HT:   Hyper-Threading Technology

@copyright
  INTEL CONFIDENTIAL
  Copyright 2012 - 2017 Intel Corporation.

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

#include "PowerMgmtInit.h"


/**
  Configures the Interrupt Redirection Mode Selection for Logical Interrupts
**/
VOID
InitPpmIrmConfiguration (
  VOID
  )
{
  UINTN  MchBar;

  ///
  /// Get the MCH space base address and program MMIO register MCHBAR+0x5418 to enable specific routing algorithm.
  ///
  MchBar = PciSegmentRead32 (PCI_SEGMENT_LIB_ADDRESS (SA_SEG_NUM, SA_MC_BUS, SA_MC_DEV, SA_MC_FUN, R_SA_MCHBAR)) & ~BIT0;
  S3BootScriptSaveMemWrite (
    S3BootScriptWidthUint32,
    (UINTN) (MchBar + 0x5418),
    1,
    (VOID *) (UINTN) (MchBar + 0x5418)
    );
}

//
// Update ACPI PerfomanceStates tables
//

/**
  Patch the native _PSS package with the EIST values
  Uses ratio/VID values from the FVID table to fix up the control values in the _PSS.

  (1) Find _PSS package:
    (1.1) Find the _PR_CPU0 scope.
    (1.2) Save a pointer to the package length.
    (1.3) Find the _PSS AML name object.
  (2) Resize the _PSS package.
  (3) Fix up the _PSS package entries
    (3.1) Check Turbo mode support.
    (3.2) Check Dynamic FSB support.
  (4) Fix up the Processor block and \_PR_CPU0 Scope length.
  (5) Update SSDT Header with new length.

  @retval EFI_SUCCESS   - on success
  @retval EFI_NOT_FOUND - if _PR_.CPU0 scope is not foud in the ACPI tables
**/
EFI_STATUS
AcpiPatchPss (
  VOID
  )
{
  UINT8              *CurrPtr;
  UINT8              *EndOfTable;
  UINT8              Index;
  UINT16             NewPackageLength;
  UINT16             LpssMaxPackageLength;
  UINT16             TpssMaxPackageLength;
  UINT16             Temp;
  UINT16             *PackageLength;
  UINT16             *ScopePackageLengthPtr;
  UINT32             *Signature;
  PSS_PACKAGE_LAYOUT *PssPackage;
  MSR_REGISTER        TempMsr;
  UINT16              MaximumEfficiencyRatio;
  UINT16              MaximumNonTurboRatio;
  UINT16              PnPercent;

  ScopePackageLengthPtr = NULL;
  PssPackage            = NULL;

  //
  // Get Maximum Efficiency bus ratio (LFM) from Platform Info MSR Bits[47:40]
  // Get Maximum Non Turbo bus ratio from Platform Info MSR Bits[15:8]
  //
  TempMsr.Qword = AsmReadMsr64 (MSR_PLATFORM_INFO);
  MaximumEfficiencyRatio = TempMsr.Bytes.SixthByte;
  MaximumNonTurboRatio = TempMsr.Bytes.SecondByte;
  mNumberOfStates = mFvidPointer[0].FvidHeader.EistStates;

  ///
  /// Calculate new package length
  ///
  NewPackageLength      = Temp = (UINT16) (mNumberOfStates * sizeof (PSS_PACKAGE_LAYOUT) + 3);
  LpssMaxPackageLength  = (UINT16) (LPSS_FVID_MAX_STATES * sizeof (PSS_PACKAGE_LAYOUT) + 3);
  TpssMaxPackageLength  = (UINT16) (TPSS_FVID_MAX_STATES * sizeof (PSS_PACKAGE_LAYOUT) + 3);
  ///
  /// Locate the SSDT package in the IST table
  ///
  CurrPtr     = (UINT8 *) mCpu0IstTable;
  EndOfTable  = (UINT8 *) (CurrPtr + mCpu0IstTable->Length);
  for (CurrPtr = (UINT8 *) mCpu0IstTable; CurrPtr <= EndOfTable; CurrPtr++) {
    Signature = (UINT32 *) (CurrPtr + 1);
    ///
    /// If we find the _SB_PR00 scope, save a pointer to the package length
    ///
    if ((*CurrPtr == AML_SCOPE_OP) &&
        (*(Signature + 1) == SIGNATURE_32 ('_', 'S', 'B', '_')) &&
        (*(Signature + 2) == SIGNATURE_32 ('P', 'R', '0', '0'))
        ) {
      ScopePackageLengthPtr = (UINT16 *) (CurrPtr + 1);
    }
    ///
    /// Patch the LPSS package with 16 P-states for _PSS Method
    ///
    if ((*CurrPtr == AML_NAME_OP) && (*Signature == SIGNATURE_32 ('L', 'P', 'S', 'S'))) {
      /*
        Check table dimensions.
        PSS package reserve space for LPSS_FVID_MAX_STATES number of P-states so check if the
        current number of P- states is more than LPSS_FVID_MAX_STATES. Also need to update the SSDT contents
        if the current number of P-states is less than LPSS_FVID_MAX_STATES.
      */
      PackageLength  = (UINT16 *) (CurrPtr + 6);

      if (mNumberOfStates > LPSS_FVID_MAX_STATES) {
        *(CurrPtr + 8)  = (UINT8) LPSS_FVID_MAX_STATES;
        ///
        /// Update the Package length in AML package length format
        ///
        *PackageLength = ((LpssMaxPackageLength & 0x0F) | 0x40) | ((LpssMaxPackageLength << 4) & 0x0FF00);
      } else {
        *(CurrPtr + 8)  = (UINT8) mNumberOfStates;
        ///
        /// Update the Package length in AML package length format
        ///
        *PackageLength = ((NewPackageLength & 0x0F) | 0x40) | ((Temp << 4) & 0x0FF00);
        ///
        /// Move SSDT contents
        ///
        CopyMem ((CurrPtr + NewPackageLength), (CurrPtr + LpssMaxPackageLength), EndOfTable - (CurrPtr + LpssMaxPackageLength));

        ///
        /// Save the new end of the SSDT
        ///
        EndOfTable = EndOfTable - (LpssMaxPackageLength - NewPackageLength);
      }

      PssPackage = (PSS_PACKAGE_LAYOUT *) (CurrPtr + 9);
      if (mNumberOfStates > LPSS_FVID_MAX_STATES) {
        for (Index = 1; Index <= LPSS_FVID_MAX_STATES; Index++) {
          ///
          /// Update the _PSS table. If Turbo mode is supported, add one to the Max Non-Turbo frequency
          ///
          if ((gCpuNvsAreaProtocol->Area->PpmFlags & PPM_TURBO) && (Index == 1)) {
            PssPackage->CoreFrequency = (UINT32) ((mFvidPointer[Index + 1].FvidState.Limit16BusRatio)* 100) + 1;
          } else if (mFvidPointer[Index].FvidState.Limit16BusRatio < MaximumEfficiencyRatio) {
            //
            // If cTDP Down Ratio == LFM, set it to 1% lower than LFM.
            //
            PnPercent = (MaximumEfficiencyRatio * 100) / MaximumNonTurboRatio;
            PssPackage->CoreFrequency = (MaximumNonTurboRatio * (PnPercent - 1)); // Simplified Calculation.
          } else {
            PssPackage->CoreFrequency = (UINT32) (mFvidPointer[Index].FvidState.Limit16BusRatio) * 100;
          }
          PssPackage->Power = (UINT32) mFvidPointer[Index].FvidState.Limit16Power;
          ///
          /// If it's PSS table, Control is the PERF_CTL value.
          /// Status entry is the same as control entry.
          /// TransLatency uses 10
          ///
          PssPackage->TransLatency  = NATIVE_PSTATE_LATENCY;
          PssPackage->Control       = (UINT32) LShiftU64 (mFvidPointer[Index].FvidState.Limit16BusRatio, 8);
          //
          // Ensure any future OS would not look for the IA32_PERF_STATUS MSR to check if the value matches
          //
          if (mFvidPointer[Index].FvidState.Limit16BusRatio < MaximumEfficiencyRatio) {
            PssPackage->Status        = (UINT32) LShiftU64 (MaximumEfficiencyRatio, 8);
          } else {
            PssPackage->Status        = (UINT32) LShiftU64 (mFvidPointer[Index].FvidState.Limit16BusRatio, 8);
          }
          PssPackage->BmLatency     = PSTATE_BM_LATENCY;
          PssPackage++;
        }
      } else {
        for (Index = 1; Index <= mNumberOfStates; Index++) {
          ///
          /// Update the _PSS table. If Turbo mode is supported, add one to the Max Non-Turbo frequency
          ///
          if ((gCpuNvsAreaProtocol->Area->PpmFlags & PPM_TURBO) && (Index == 1)) {
            PssPackage->CoreFrequency = (UINT32) ((mFvidPointer[Index + 1].FvidState.BusRatio)* 100) + 1;
          } else if (mFvidPointer[Index].FvidState.BusRatio < MaximumEfficiencyRatio) {
            //
            // If cTDP Down Ratio == LFM, set it to 1% lower than LFM.
            //
            PnPercent = (MaximumEfficiencyRatio * 100) / MaximumNonTurboRatio;
            PssPackage->CoreFrequency = (MaximumNonTurboRatio * (PnPercent - 1)); // Simplified Calculation.
          } else {
            PssPackage->CoreFrequency = (UINT32) (mFvidPointer[Index].FvidState.BusRatio) * 100;
          }
          PssPackage->Power = (UINT32) mFvidPointer[Index].FvidState.Power;
          ///
          /// If it's PSS table, Control is the PERF_CTL value.
          /// Status entry is the same as control entry.
          /// TransLatency uses 10
          ///
          PssPackage->TransLatency  = NATIVE_PSTATE_LATENCY;
          PssPackage->Control       = (UINT32) LShiftU64 (mFvidPointer[Index].FvidState.BusRatio, 8);
          //
          // Ensure any future OS would not look for the IA32_PERF_STATUS MSR to check if the value matches
          //
          if (mFvidPointer[Index].FvidState.BusRatio < MaximumEfficiencyRatio) {
            PssPackage->Status        = (UINT32) LShiftU64 (MaximumEfficiencyRatio, 8);
          } else {
            PssPackage->Status        = (UINT32) LShiftU64 (mFvidPointer[Index].FvidState.BusRatio, 8);
          }
          PssPackage->BmLatency     = PSTATE_BM_LATENCY;
          PssPackage++;
        }
      }
    }

    ///
    /// Patch the TPSS package with no limit P-states for _PSS Method
    ///
    if ((*CurrPtr == AML_NAME_OP) && (*Signature == SIGNATURE_32 ('T', 'P', 'S', 'S'))) {
      ASSERT (mNumberOfStates <= TPSS_FVID_MAX_STATES);
      if (mNumberOfStates <= TPSS_FVID_MAX_STATES) {

        *(CurrPtr + 8)  = (UINT8) mNumberOfStates;
        PackageLength   = (UINT16 *) (CurrPtr + 6);
        ///
        /// Update the Package length in AML package length format
        ///
        *PackageLength = ((NewPackageLength & 0x0F) | 0x40) | ((Temp << 4) & 0x0FF00);
        ///
        /// Move SSDT contents
        ///
        CopyMem ((CurrPtr + NewPackageLength), (CurrPtr + TpssMaxPackageLength), EndOfTable - (CurrPtr + TpssMaxPackageLength));
        ///
        /// Save the new end of the SSDT
        ///
        EndOfTable = EndOfTable - (TpssMaxPackageLength - NewPackageLength);
      }

      PssPackage = (PSS_PACKAGE_LAYOUT *) (CurrPtr + 9);
      for (Index = 1; Index <= mNumberOfStates; Index++) {
        ///
        /// Update the _PSS table. If Turbo mode is supported, add one to the Max Non-Turbo frequency
        ///
        if ((gCpuNvsAreaProtocol->Area->PpmFlags & PPM_TURBO) && (Index == 1)) {
          PssPackage->CoreFrequency = (UINT32) ((mFvidPointer[Index + 1].FvidState.BusRatio)* 100) + 1;
        } else if (mFvidPointer[Index].FvidState.BusRatio < MaximumEfficiencyRatio) {
          //
          // If cTDP Down Ratio == LFM, set it to 1% lower than LFM.
          //
          PnPercent = (MaximumEfficiencyRatio * 100) / MaximumNonTurboRatio;
          PssPackage->CoreFrequency = (MaximumNonTurboRatio * (PnPercent - 1)); // Simplified Calculation.
        } else {
          PssPackage->CoreFrequency = (UINT32) (mFvidPointer[Index].FvidState.BusRatio) * 100;
        }
        PssPackage->Power = (UINT32) mFvidPointer[Index].FvidState.Power;
        ///
        /// If it's PSS table, Control is the PERF_CTL value.
        /// Status entry is the same as control entry.
        /// TransLatency uses 10
        ///
        PssPackage->TransLatency  = NATIVE_PSTATE_LATENCY;
        PssPackage->Control       = (UINT32) LShiftU64 (mFvidPointer[Index].FvidState.BusRatio, 8);
        //
        // Ensure any future OS would not look for the IA32_PERF_STATUS MSR to check if the value matches
        //
        if (mFvidPointer[Index].FvidState.BusRatio < MaximumEfficiencyRatio) {
          PssPackage->Status        = (UINT32) LShiftU64 (MaximumEfficiencyRatio, 8);
        } else {
          PssPackage->Status        = (UINT32) LShiftU64 (mFvidPointer[Index].FvidState.BusRatio, 8);
        }
        PssPackage->BmLatency     = PSTATE_BM_LATENCY;
        PssPackage++;
      }
    }
  }
  ASSERT (ScopePackageLengthPtr != NULL);
  if (ScopePackageLengthPtr == NULL) {
    return EFI_NOT_FOUND;
  }
  ///
  /// Update the Package length in AML package length format
  ///
  CurrPtr                 = (UINT8 *) ScopePackageLengthPtr;
  NewPackageLength        = Temp = (UINT16) (EndOfTable - CurrPtr);
  *ScopePackageLengthPtr  = ((NewPackageLength & 0x0F) | 0x40) | ((Temp << 4) & 0x0FF00);
  mCpu0IstTable->Length   = (UINT32) (EndOfTable - (UINT8 *) mCpu0IstTable);

  return EFI_SUCCESS;
}




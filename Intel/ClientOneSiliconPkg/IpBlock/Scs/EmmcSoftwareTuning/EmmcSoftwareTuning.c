/** @file
  This module performs eMMC software tuning procedure.

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
#include <Uefi.h>
#include <Uefi/UefiMultiPhase.h>
#include <Pi/PiMultiPhase.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/ScsLocationLib.h>
#include <Library/S3BootScriptLib.h>
#include <Protocol/PchPolicy.h>
#include <Protocol/ScsEmmcSoftwareTuning.h>

#include "EmmcSoftwareTuning.h"

//
// Expected passing DLL values and boundary values
//
#define RX_DLL1_TAP_MAX_RANGE          39
#define RX_DLL1_TAP_MIN_RANGE           0
#define RX_DLL1_TAP_MIN_MEPT            5
#define RX_DLL1_TAP_MAX_MEPT           16

#define TX_DLL_TAP_MAX_RANGE           79
#define TX_DLL_TAP_MIN_RANGE            0
#define TX_DLL_TAP_MIN_MEPT             4
#define TX_DLL_TAP_MAX_MEPT            22

typedef struct _EMMC_TUNE_TEST EMMC_TUNE_TEST;

typedef
BOOLEAN
(*TEST_FUNCTION) (
  EMMC_TUNE_TEST  *This,
  UINT8           DllValue
  );

struct _EMMC_TUNE_TEST {
  UINT32              EmmcMmio;
  EFI_LBA             TuningLba;
  UINT32              BufferSize;
  VOID                *Buffer;
  TEST_FUNCTION       TestParameter;
};

/**
  Search for the passing window boundary.

  Search algorithm:
  1. Set starting point and test whether test result is positive
  2. If positive then we are starting the search in the passing window
     Go to 4. for searching for maximum and to 6. for searching for minimum.
  3. If negative then we are starting the search in the failing window

  -- First test positive - search in passing region
  4. If we are searching for maximum perform ascending search as expected max value is below the real one.
  5. As soon as test starts failing adjust the boundary value to the last passing and return
  6. If we are searching for minimum perform descending search as expected minimum value is below the real one.
  7. As soon as test starts failing adjust the boundary value to the last passing and return.

  -- First test negative - search in the failing region
  8. If we are searching for the maximum we assume that the expected passing value was overestimated and the
     real one is below. Perform descending search.
  9. As soon as the test returns positive return.
  10. If we are searching for the minimum we assume that the expected passing value was underestimated and the
      real one is above. Perform ascending search.
  11. As soon as the test returns positive return.

  @param[in]  StartingPoint        Search starting point
  @param[in]  SearchForMax         Flag indicating whether we are searching for maximum value
  @param[in]  SearchLowerBoundary  Lower boundary for the search
  @param[in]  SearchUpperBoundary  Upper boundary for the search
  @param[in]  Test                 Test to perform during search
  @param[out] BoundaryDll          BoundaryDll value found

  @retval TRUE   Search completed successfuly, BoundaryDll value contains valid value
  @retval FALSE  Search didn't complete successfuly, BoundaryDll value is not valid
**/
STATIC
BOOLEAN
EmmcSearchForBoundary (
  IN  UINT8            StartingPoint,
  IN  UINT8            SearchForMax,
  IN  UINT8            SearchLowerBoundary,
  IN  UINT8            SearchUpperBoundary,
  IN  EMMC_TUNE_TEST   *Test,
  OUT UINT8            *BoundaryDll
  )
{
  BOOLEAN  TestResult;
  BOOLEAN  AscendingSearch;
  BOOLEAN  SearchInInvalidRegion;

  DEBUG ((DEBUG_INFO, "EmmcTune: Starting with: %d\n", StartingPoint));
  *BoundaryDll = StartingPoint;
  TestResult = Test->TestParameter (Test, *BoundaryDll);

  if (TestResult) {
    SearchInInvalidRegion = FALSE;
    if (SearchForMax) {
      AscendingSearch = TRUE;
    } else {
      AscendingSearch = FALSE;
    }
  } else {
    SearchInInvalidRegion = TRUE;
    if (SearchForMax) {
      AscendingSearch = FALSE;
    } else {
      AscendingSearch = TRUE;
    }
  }

  while (*BoundaryDll > SearchLowerBoundary && *BoundaryDll < SearchUpperBoundary) {
    if (AscendingSearch) {
      *BoundaryDll = *BoundaryDll + 1;
    } else {
      *BoundaryDll = *BoundaryDll - 1;
    }
    DEBUG ((DEBUG_INFO, "EmmcTune: Testing: %d DLL value\n", *BoundaryDll));
    TestResult = Test->TestParameter (Test, *BoundaryDll);
    if (TestResult && SearchInInvalidRegion) {
      return TRUE;
    } else if (!TestResult && !SearchInInvalidRegion) {
      //
      // Compensate for overshot.
      //
      if (AscendingSearch) {
        *BoundaryDll = *BoundaryDll - 1;
      } else {
        *BoundaryDll = *BoundaryDll + 1;
      }
      return TRUE;
    } else {
      continue;
    }
  }

  return TestResult;
}

/**
  Set Rx DLL value.

  @param[in] EmmcMmio  eMMC MMIO address
  @param[in] DllValue  Value of the DLL
**/
STATIC
VOID
EmmcSetRxDll (
  IN UINT32  EmmcMmio,
  IN UINT8   DllValue
  )
{
  MmioWrite8 (EmmcMmio + (R_SCS_MEM_RX_STROBE_DLL_CNTL + 1), DllValue);
  MmioWrite8 (EmmcMmio + R_SCS_MEM_RX_STROBE_DLL_CNTL, DllValue);
}

/**
  Function that performs read test.

  @param[in]  This  Instance of the test case

  @retval TRUE  Read successful
  @retval FALSE Read failed
**/
STATIC
BOOLEAN
EmmcTestRead (
  IN EMMC_TUNE_TEST  *This,
  IN UINT8           DllValue
  )
{
  EFI_STATUS  Status;

  EmmcSetRxDll (This->EmmcMmio, DllValue);
  Status = EmmcReadSingleBlock (
             This->EmmcMmio,
             This->TuningLba,
             This->BufferSize,
             This->Buffer
             );
  return !EFI_ERROR (Status);
}

/**
  Searches for the optimal Rx DLL value

  @param[in]  EmmcMmio    eMMC MMIO address
  @param[in]  TuningLba   LBA address of the tuning block
  @param[in]  BufferSize  Buffer size
  @param[in]  Buffer      Pointer to the allocated buffer for block io
  @param[out] TunedRxDll  Value of the tuned Rx DLL

  @retval TRUE   Search found optimal value. TunedRxDll is valid
  @retval FALSE  Search failed. TunedRxDll is not valid
**/
STATIC
BOOLEAN
EmmcFindOptimalRxValue (
  IN UINT32   EmmcMmio,
  IN EFI_LBA  TuningLba,
  IN UINT32   BufferSize,
  IN VOID     *Buffer,
  OUT UINT8   *TunedRxDll
  )
{
  EMMC_TUNE_TEST   EmmcReadTest;
  BOOLEAN          SearchStatus;
  UINT8            LowerBound;
  UINT8            UpperBound;
  UINT8            OptimalValue;

  DEBUG ((DEBUG_INFO, "EmmcTune: Start Rx tuning\n"));

  DEBUG ((DEBUG_INFO, "EmmcTune: Find lower bound on the passing window\n"));

  EmmcReadTest.EmmcMmio = EmmcMmio;
  EmmcReadTest.TuningLba = TuningLba;
  EmmcReadTest.BufferSize = BufferSize;
  EmmcReadTest.Buffer = Buffer;
  EmmcReadTest.TestParameter = EmmcTestRead;

  SearchStatus = EmmcSearchForBoundary (
                   RX_DLL1_TAP_MIN_MEPT,
                   FALSE,
                   RX_DLL1_TAP_MIN_RANGE,
                   RX_DLL1_TAP_MAX_RANGE,
                   &EmmcReadTest,
                   &LowerBound
                   );

  if (!SearchStatus) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to find lower bound on passing window\n"));
    return FALSE;
  }

  DEBUG ((DEBUG_INFO, "EmmcTune: Rx lower bound = %d\n", LowerBound));

  DEBUG ((DEBUG_INFO, "EmmcTune: find the upper bound on the passing window\n"));
  SearchStatus = EmmcSearchForBoundary (
                   RX_DLL1_TAP_MAX_MEPT,
                   TRUE,
                   RX_DLL1_TAP_MIN_RANGE,
                   RX_DLL1_TAP_MAX_RANGE,
                   &EmmcReadTest,
                   &UpperBound
                   );

  if (!SearchStatus) {
    DEBUG ((DEBUG_INFO, "EmmcTune: Failed to find upper bound on passing window\n"));
    return FALSE;
  }

  DEBUG ((DEBUG_INFO, "EmmcTune: Rx upper bound = %d\n", UpperBound));

  ASSERT (UpperBound - LowerBound > 0);
  //
  // Optimal DLL value is at the middle of the passing window
  //
  OptimalValue = ((UpperBound - LowerBound) / 2) + LowerBound;
  DEBUG ((DEBUG_INFO, "EmmcTune: Rx optimal DLL = %d\n", OptimalValue));

  //
  // Program the optimal DLL values for Rx lane
  //
  EmmcSetRxDll (EmmcMmio, OptimalValue);
  *TunedRxDll = OptimalValue;
  return TRUE;
}

/**
  Set Tx DLL value.

  @param[in] EmmcMmio  eMMC MMIO address
  @param[in] DllValue  Value of the Tx DLL
**/
STATIC
VOID
EmmcSetTxDll (
  IN UINT32  EmmcMmio,
  IN UINT8   DllValue
  )
{
  MmioWrite8 (EmmcMmio + (R_SCS_MEM_TX_DATA_DLL_CNTL1 + 1), DllValue);
}

/**
  Function that performs write test.

  @param[in] This  Test case instance

  @retval TRUE   Write passed
  @retval FALSE  Write failed
**/
STATIC
BOOLEAN
EmmcTestWrite (
  IN EMMC_TUNE_TEST  *This,
  IN UINT8           DllValue
  )
{
  EFI_STATUS  Status;

  EmmcSetTxDll (This->EmmcMmio, DllValue);
  Status = EmmcWriteSingleBlock (
             This->EmmcMmio,
             This->TuningLba,
             This->BufferSize,
             This->Buffer
             );

  return !EFI_ERROR (Status);
}

/**
  Search for the optimal Tx DLL value.

  @param[in]  EmmcMmio    eMMC MMIO address
  @param[in]  TuningLba   Tuning block address
  @param[in]  BufferSize  Size of the buffer
  @param[in]  Buffer      Caller allocated buffer for block io
  @param[out] TunedTxDll  Value of the tuned Tx DLL

  @retval TRUE  Search found optimal value. TunedTxDll is valid
  @retval FALSE Search found optimal value. TunedTxDll is invalid
**/
STATIC
BOOLEAN
EmmcFindOptimalTxValue (
  IN UINT32   EmmcMmio,
  IN EFI_LBA  TuningLba,
  IN UINT32   BufferSize,
  IN VOID     *Buffer,
  OUT UINT8   *TunedTxDll
  )
{
  EMMC_TUNE_TEST  EmmcWriteTest;
  EFI_STATUS      Status;
  BOOLEAN         SearchStatus;
  UINT8           LowerBoundary;
  UINT8           UpperBoundary;
  UINT8           OptimalValue;

  DEBUG ((DEBUG_INFO, "EmmcTune: Start Tx tuning\n"));
  //
  // Read Tuning Block that used at Rx HS400 Tuning
  //
  Status = EmmcReadSingleBlock (
             EmmcMmio,
             TuningLba,
             BufferSize,
             Buffer
             );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_INFO, "EmmcTune: Failed to read tuning block during Tx tuning!\n"));
    return FALSE;
  }

  DEBUG ((DEBUG_INFO, "EmmcTune: Search for Tx lower bound\n"));

  EmmcWriteTest.EmmcMmio = EmmcMmio;
  EmmcWriteTest.TuningLba = TuningLba;
  EmmcWriteTest.BufferSize = BufferSize;
  EmmcWriteTest.Buffer = Buffer;
  EmmcWriteTest.TestParameter = EmmcTestWrite;

  SearchStatus = EmmcSearchForBoundary (
                   TX_DLL_TAP_MIN_MEPT,
                   FALSE,
                   TX_DLL_TAP_MIN_RANGE,
                   TX_DLL_TAP_MAX_RANGE,
                   &EmmcWriteTest,
                   &LowerBoundary
                   );

  if (!SearchStatus) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to get lower bound on Tx DLL\n"));
    return FALSE;
  }

  DEBUG ((DEBUG_INFO, "EmmcTune: Lower Tx boundary = %d\n", LowerBoundary));

  DEBUG ((DEBUG_INFO, "EmmcTune: Search for Tx upper bound\n"));

  SearchStatus = EmmcSearchForBoundary (
                   TX_DLL_TAP_MAX_MEPT,
                   TRUE,
                   TX_DLL_TAP_MIN_RANGE,
                   TX_DLL_TAP_MAX_RANGE,
                   &EmmcWriteTest,
                   &UpperBoundary
                   );

  if (!SearchStatus) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to get upper bound on Tx DLL\n"));
    return FALSE;
  }

  DEBUG ((DEBUG_INFO, "EmmcTune: Upper Tx boundary = %d\n", UpperBoundary));
  ASSERT (UpperBoundary - LowerBoundary > 0);
  //
  // Optimal value is in the middle of the passing window
  //
  OptimalValue = ((UpperBoundary - LowerBoundary) / 2) + LowerBoundary;
  DEBUG ((DEBUG_INFO, "EmmcTune: Optimal Tx Dll =%d\n", OptimalValue));

  //
  // Program the optimal DLL value.
  //
  EmmcSetTxDll (EmmcMmio, OptimalValue);
  *TunedTxDll  = OptimalValue;
  return TRUE;
}

/**
  Search for optimal DLL values for Rx and Tx.

  @param[in]  EmmcMmio   eMMC MMIO address
  @param[in]  TuningLba  Address of the tuning block
  @param[out] TunedDll   Structure containing tuned DLL values

  @retval TRUE   Search completed successfuly.
  @retval FALSE  Search failed.
**/
STATIC
BOOLEAN
EmmcFindOptimalDlls (
  IN UINT32                             EmmcMmio,
  IN EFI_LBA                            TuningLba,
  OUT SCS_EMMC_SOFTWARE_TUNING_RESULTS  *TuningResults
  )
{
  BOOLEAN  TuningStatus;
  UINT8    TunedRxValue;
  UINT8    TunedTxValue;
  UINT8    Buffer[BLOCK_LENGTH];

  TuningResults->TuningSuccessful = FALSE;
  TuningStatus = EmmcFindOptimalRxValue (EmmcMmio, TuningLba, BLOCK_LENGTH, (VOID*) Buffer, &TunedRxValue);
  if (!TuningStatus) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to tune Rx lane\n"));
    return FALSE;
  }
  TuningResults->Hs400RxValue = TunedRxValue;
  TuningStatus = EmmcFindOptimalTxValue (EmmcMmio, TuningLba, BLOCK_LENGTH, (VOID*) Buffer, &TunedTxValue);
  if (!TuningStatus) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to tune Tx lane\n"));
    return FALSE;
  }
  TuningResults->Hs400TxValue = TunedTxValue;
  TuningResults->TuningSuccessful = TRUE;
  return TRUE;
}

/**
  Start HS400 software tuning.

 @param[in]  EmmcMmio        eMMC MMIO address
 @param[in]  TuningLba       Address of the tuning block
 @param[in]  DriverStrength  Driver strength to be used in HS400
 @param[out] TunedDll        Structure containing tuned DLL values

  @return Status of the tuning.
**/
STATIC
EFI_STATUS
EmmcTuneHs400 (
  IN UINT32                             EmmcMmio,
  IN EFI_LBA                            TuningLba,
  IN SCS_EMMC_DRIVER_STRENGTH           DriverStrength,
  OUT SCS_EMMC_SOFTWARE_TUNING_RESULTS  *TuningResults
  )
{
  EFI_STATUS  Status;

  Status = EmmcInitializeBus (EmmcMmio);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to initialize bus\n"));
    return Status;
  }

  Status = EmmcInitializeCard (EmmcMmio, DriverStrength);
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to initialize card\n"));
    return Status;
  }

  if (EmmcIsBlockWriteProtected (EmmcMmio, TuningLba)) {
    return EFI_UNSUPPORTED;
  }

  if (!EmmcFindOptimalDlls (EmmcMmio, TuningLba, TuningResults)) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: Failed to find optimal DLLs\n"));
    return EFI_UNSUPPORTED;
  }

  return Status;
}

GLOBAL_REMOVE_IF_UNREFERENCED  SCS_EMMC_SOFTWARE_TUNING_PROTOCOL  mSoftwareTuningProtocol;

/**
  Publishes results of this software tuning to be saved by platform code.

  @param[in] TuningResutls  Structure containing the result of the tuning.
**/
STATIC
VOID
EmmcPublishTuningResults (
  IN SCS_EMMC_SOFTWARE_TUNING_RESULTS  *TuningResults
  )
{
  EFI_STATUS  Status;
  EFI_HANDLE  ProtocolHandle;

  CopyMem (&mSoftwareTuningProtocol.TuningResults, TuningResults, sizeof (SCS_EMMC_SOFTWARE_TUNING_RESULTS));

  ProtocolHandle = NULL;
  Status = gBS->InstallProtocolInterface (
                  &ProtocolHandle,
                  &gScsEmmcSoftwareTuningProtocolGuid,
                  EFI_NATIVE_INTERFACE,
                  (VOID*)&mSoftwareTuningProtocol
                  );
  if (EFI_ERROR (Status)) {
    DEBUG ((DEBUG_ERROR, "Failed to install eMMC software tuning protocol!\n"));
  }
}

/**
  This function sets up the boot script that is required to execute
  on S3 resume flow to restore tuning programming in eMMC controller.

  @param[in] EmmcMmio       eMMC MMIO base address. This will be programmed on S3 resume to BAR.
  @param[in] TuningRestults structure containing results of the tuning.
**/
STATIC
VOID
EmmcTuningSetUpBootScript (
  IN UINT32                            EmmcMmio,
  IN SCS_EMMC_SOFTWARE_TUNING_RESULTS  *TuningResults
  )
{
  UINT32  DataAnd32;
  UINT32  DataOr32;
  UINT32  Data32;
  UINT16  DataAnd16;
  UINT16  DataOr16;
  UINT8   Data8;
  UINT64  EmmcBootScriptPciConfig;
  UINT8   DeviceNumber;
  UINT8   FunctionNumber;

  ScsGetEmmcBdf (&DeviceNumber, &FunctionNumber);
  EmmcBootScriptPciConfig = S3_BOOT_SCRIPT_LIB_PCI_ADDRESS (
                              DEFAULT_PCI_BUS_NUMBER_PCH,
                              DeviceNumber,
                              FunctionNumber,
                              0
                              );

  //
  // Boot script sequence:
  // 1. Enable MMIO access to eMMC. We use the same MMIO address as we used during tuning.
  // 2. If tuning was successful program DLL registers with tuned values
  // 3. If tuning failed disable HS400 capability
  // 4. Disable MMIO access to eMMC and clear BAR
  //
  DataOr16 = 0;
  DataAnd16 = (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE;
  S3BootScriptSavePciCfgReadWrite (S3BootScriptWidthUint16, EmmcBootScriptPciConfig + PCI_COMMAND_OFFSET, (VOID*) &DataOr16, (VOID*) &DataAnd16);
  Data32 = EmmcMmio;
  S3BootScriptSavePciCfgWrite (S3BootScriptWidthUint32, EmmcBootScriptPciConfig + PCI_BASE_ADDRESSREG_OFFSET, 1, (VOID*) &Data32);
  Data32 = 0;
  S3BootScriptSavePciCfgWrite (S3BootScriptWidthUint32, EmmcBootScriptPciConfig + PCI_BASE_ADDRESSREG_OFFSET + 4, 1, (VOID*) &Data32);
  DataOr16 = (UINT16) EFI_PCI_COMMAND_MEMORY_SPACE;
  DataAnd16 = 0xFFFF;
  S3BootScriptSavePciCfgReadWrite (S3BootScriptWidthUint16, EmmcBootScriptPciConfig + PCI_COMMAND_OFFSET, (VOID*) &DataOr16, (VOID*) &DataAnd16);
  if (TuningResults->TuningSuccessful) {
    Data8 = (UINT8)TuningResults->Hs400RxValue;
    S3BootScriptSaveMemWrite (S3BootScriptWidthUint8, EmmcMmio + R_SCS_MEM_RX_STROBE_DLL_CNTL + 1, 1, (VOID*) &Data8);
    S3BootScriptSaveMemWrite (S3BootScriptWidthUint8, EmmcMmio + R_SCS_MEM_RX_STROBE_DLL_CNTL, 1, (VOID*) &Data8);
    Data8 = (UINT8)TuningResults->Hs400TxValue;
    S3BootScriptSaveMemWrite (S3BootScriptWidthUint8, EmmcMmio + R_SCS_MEM_TX_DATA_DLL_CNTL1, 1, (VOID*) &Data8);
  } else {
    DataOr32 = 0;
    DataAnd32 = (UINT32) ~B_SCS_MEM_CAP_BYPASS_REG1_HS400;
    S3BootScriptSaveMemReadWrite (S3BootScriptWidthUint32, EmmcMmio + R_SCS_MEM_CAP_BYPASS_REG1, (VOID*) &DataOr32, (VOID*) &DataAnd32);
  }
  DataOr16 = 0;
  DataAnd16 = (UINT16) ~EFI_PCI_COMMAND_MEMORY_SPACE;
  S3BootScriptSavePciCfgReadWrite (S3BootScriptWidthUint16, EmmcBootScriptPciConfig + PCI_COMMAND_OFFSET, (VOID*) &DataOr16, (VOID*) &DataAnd16);
  Data32 = 0;
  S3BootScriptSavePciCfgWrite (S3BootScriptWidthUint32, EmmcBootScriptPciConfig + PCI_BASE_ADDRESSREG_OFFSET, 1, (VOID*) &Data32);
}

/**
  This function should be called at the end of tuning or if
  the tuning in the previous boot was successfull. It will set the tuned values
  from tuning results and it will setup boot script to restore them during S3 resume.

  @param[in] EmmcMmio       eMMC MMIO base address
  @param[in] TuningResults  Results of the tuning.
**/
STATIC
VOID
EmmcSetTunedDllWithS3BootScript (
  IN UINT32                            EmmcMmio,
  IN SCS_EMMC_SOFTWARE_TUNING_RESULTS  *TuningResults
  )
{
  if (TuningResults->TuningSuccessful) {
    //
    // If we are after tuning run then those registers are already
    // programmed correctly but it doesn't hurt to progam them second time
    // and it allows us to have common code for case with tuning in current
    // boot and for case when we restore programming from tuning in previous boot.
    //
    EmmcSetRxDll (EmmcMmio, (UINT8)TuningResults->Hs400RxValue);
    EmmcSetTxDll (EmmcMmio, (UINT8)TuningResults->Hs400TxValue);
  } else {
    //
    // If we failed the HS400 tuning and it was requested in policy
    // we have to disable the HS400 capability in host controller.
    //
    MmioAnd32 (EmmcMmio + R_SCS_MEM_CAP_BYPASS_REG1, (UINT32) ~B_SCS_MEM_CAP_BYPASS_REG1_HS400);
  }

  EmmcTuningSetUpBootScript (EmmcMmio, TuningResults);
}

/**
  Integrated eMMC software tuning entry point.

  @param[in] ImageHandle  Handle of this image
  @param[in] SystemTable  System table pointer

  @return Status of the software tuning
**/
EFI_STATUS
EFIAPI
EmmcSoftwareTuningEntryPoint (
  IN EFI_HANDLE         ImageHandle,
  IN EFI_SYSTEM_TABLE   *SystemTable
  )
{
  UINT64                            EmmcPciConfig;
  UINT32                            TempMmioBase;
  EFI_STATUS                        Status;
  PCH_POLICY_PROTOCOL               *PchPolicy;
  SCS_EMMC_DXE_CONFIG               *EmmcDxeConfig;
  UINT8                             DeviceNumber;
  UINT8                             FunctionNumber;
  SCS_EMMC_SOFTWARE_TUNING_RESULTS  TuningResults;

  DEBUG ((DEBUG_INFO, "EmmcTune: Start\n"));

  Status = gBS->LocateProtocol (&gPchPolicyProtocolGuid, NULL, (VOID**)&PchPolicy);
  ASSERT_EFI_ERROR (Status);

  Status = GetConfigBlock ((VOID*) PchPolicy, &gEmmcDxeConfigGuid, (VOID*)&EmmcDxeConfig);
  ASSERT_EFI_ERROR (Status);

  if (!EmmcDxeConfig->EnableSoftwareHs400Tuning) {
    DEBUG ((DEBUG_INFO, "EmmcTune: Software tuning disabled\n"));
    return EFI_UNSUPPORTED;
  }

  ScsGetEmmcBdf (&DeviceNumber, &FunctionNumber);
  EmmcPciConfig = PCI_SEGMENT_LIB_ADDRESS (
                    DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                    DEFAULT_PCI_BUS_NUMBER_PCH,
                    DeviceNumber,
                    FunctionNumber,
                    0
                    );

  if (PciSegmentRead16 (EmmcPciConfig + PCI_VENDOR_ID_OFFSET) == 0xFFFF) {
    DEBUG ((DEBUG_ERROR, "EmmcTune: eMMC Host Controller Unavailable!\n"));
    return EFI_UNSUPPORTED;
  }

  TempMmioBase = PcdGet32 (PcdSiliconInitTempMemBaseAddr);

  //
  // We assume that this module will be run before PCI enumeration
  // and before MMIO ranges are allocated. We clear the temporary MMIO
  // address at the end of tuning.
  //
  EmmcEnableMmio (EmmcPciConfig, TempMmioBase);
  //
  // Enable bus master on integrated eMMC to allow for SDMA transfers.
  //
  PciSegmentOr16 (EmmcPciConfig + PCI_COMMAND_OFFSET, (UINT16) BIT2);

  if (EmmcDxeConfig->PreviousTuningResults.TuningSuccessful) {
    DEBUG ((DEBUG_INFO, "EmmcTune: Previous tuning was a success, reusing DLL values\n"));
    EmmcSetTunedDllWithS3BootScript (TempMmioBase, &EmmcDxeConfig->PreviousTuningResults);
  } else {
    Status = EmmcTuneHs400 (TempMmioBase, EmmcDxeConfig->TuningLba, EmmcDxeConfig->DriverStrength, &TuningResults);
    if (!EFI_ERROR (Status)) {
      EmmcPublishTuningResults (&TuningResults);
    }
    EmmcSetTunedDllWithS3BootScript (TempMmioBase, &TuningResults);
  }

  PciSegmentAnd16 (EmmcPciConfig + PCI_COMMAND_OFFSET, (UINT16) ~BIT2);
  EmmcDisableMmio (EmmcPciConfig);

  DEBUG ((DEBUG_INFO, "EmmcTune: Finished\n"));

  return EFI_SUCCESS;
}


/** @file
  Pei HSIO common Library

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 - 2019 Intel Corporation.

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
#include <Library/PeiServicesLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/DebugLib.h>
#include <Library/PchInfoLib.h>
#include <Library/PchSbiAccessLib.h>
#include <Library/PeiHsioLib.h>
#include <PchHsio.h>
#include <Register/PchPcrRegs.h>


/**
  Intializes the HSIO ChipsetInit SUS Table Data Structure

  @param[in out] PchHsioChipsetInitSusTblData        Pointer to HSIO ChipsetInit SUS table Data

  @retval EFI_SUCCESS                 Located SUS Table PPI
  @retval EFI_OUT_OF_RESOURCES        Unable to allocate memory for SUS Table PPI
**/
EFI_STATUS
HsioGetChipsetInitSusTblData (
  PCH_HSIO_CHIPSETINIT_SUS_TBL_PPI   **PchHsioChipsetInitSusTblData
  )
{
  EFI_PEI_PPI_DESCRIPTOR                    *PchHsioChipsetInitSusTblDataPpiDesc;
  STATIC PCH_HSIO_CHIPSETINIT_SUS_TBL_PPI   *mPchHsioChipsetInitSusTblDataPtr;
  PCH_HSIO_CHIPSETINIT_SUS_TBL_PPI          *PchHsioChipsetInitSusTblDataPtr;
  EFI_STATUS                                Status;

  if (mPchHsioChipsetInitSusTblDataPtr != NULL) {
    *PchHsioChipsetInitSusTblData = mPchHsioChipsetInitSusTblDataPtr;
    return EFI_SUCCESS;
  }

  PchHsioChipsetInitSusTblDataPtr = NULL;

  Status = PeiServicesLocatePpi (
             &gPchHsioChipsetInitSusTblDataPpiGuid,
             0,
             NULL,
             (VOID **) &PchHsioChipsetInitSusTblDataPtr
             );
  if (Status == EFI_NOT_FOUND) {
    PchHsioChipsetInitSusTblDataPtr = (PCH_HSIO_CHIPSETINIT_SUS_TBL_PPI *) AllocateZeroPool (sizeof (PCH_HSIO_CHIPSETINIT_SUS_TBL_PPI));
    if (PchHsioChipsetInitSusTblDataPtr == NULL) {
      ASSERT (FALSE);
      return EFI_OUT_OF_RESOURCES;
    }

    PchHsioChipsetInitSusTblDataPpiDesc = (EFI_PEI_PPI_DESCRIPTOR *) AllocateZeroPool (sizeof (EFI_PEI_PPI_DESCRIPTOR));
    if (PchHsioChipsetInitSusTblDataPpiDesc == NULL) {
      ASSERT (FALSE);
      return EFI_OUT_OF_RESOURCES;
    }
    PchHsioChipsetInitSusTblDataPpiDesc->Flags = EFI_PEI_PPI_DESCRIPTOR_PPI | EFI_PEI_PPI_DESCRIPTOR_TERMINATE_LIST;
    PchHsioChipsetInitSusTblDataPpiDesc->Guid = &gPchHsioChipsetInitSusTblDataPpiGuid;
    PchHsioChipsetInitSusTblDataPpiDesc->Ppi = PchHsioChipsetInitSusTblDataPtr;
    DEBUG ((DEBUG_INFO, "Installing HSIO ChipsetInit SUS Table Data PPI\n"));
    Status = PeiServicesInstallPpi (PchHsioChipsetInitSusTblDataPpiDesc);
    ASSERT_EFI_ERROR (Status);
  }

  *PchHsioChipsetInitSusTblData = PchHsioChipsetInitSusTblDataPtr;
  mPchHsioChipsetInitSusTblDataPtr = PchHsioChipsetInitSusTblDataPtr;
  return Status;
}

/**
  Writes PHY Tuning values to the ChipsetInit SUS Table

  @param[in] Pid         Sideband ID
  @param[in] Offset      PCR offset
  @param[in] Data32      DWORD Value
  @param[in] CrcAndMask  AND Mask to be used for CRC calculation
  @param[in] CrcOrMask   OR Mask to be used for CRC calculation

  @retval EFI_SUCCESS             Copy to SUS Table was successful
  @retval EFI_DEVICE_ERROR        Unable to save writes to SUS Table
**/
EFI_STATUS
HsioChipsetInitSusWrite32 (
  PCH_SBI_PID  Pid,
  UINT32       Offset,
  UINT32       Data32,
  UINT32       CrcAndMask,
  UINT32       CrcOrMask
  )
{
  PCH_HSIO_CHIPSETINIT_SUS_TBL_PPI  *PchHsioChipsetInitSusTblData;
  PCH_HSIO_DATA_CMD                 PchHsioCmdTblEntry;
  UINT32                            *DestPtr;
  UINT32                            CrcIndex;
  EFI_STATUS                        Status;

  PchHsioCmdTblEntry.CommandField.Command = PhyCmdSendPosted;
  PchHsioCmdTblEntry.CommandField.Size    = PMC_DATA_CMD_SIZE;
  PchHsioCmdTblEntry.Pid                  = Pid;
  PchHsioCmdTblEntry.Bar                  = 0;
  PchHsioCmdTblEntry.OpCode               = PrivateControlWrite;
  PchHsioCmdTblEntry.Fbe                  = 0x0F;
  PchHsioCmdTblEntry.Fid                  = 0x00;
  PchHsioCmdTblEntry.Offset               = (UINT16) Offset;
  PchHsioCmdTblEntry.Value                = Data32;

  PchHsioChipsetInitSusTblData = NULL;
  Status = HsioGetChipsetInitSusTblData (&PchHsioChipsetInitSusTblData);
  ASSERT_EFI_ERROR (Status);
  if (PchHsioChipsetInitSusTblData == NULL) {
    return EFI_DEVICE_ERROR;
  }

  CrcIndex = PchHsioChipsetInitSusTblData->PchHsioSusUsb2TuningCount + PchHsioChipsetInitSusTblData->PchHsioSusModPhyTuningCount;
  if(CrcIndex < PCH_HSIO_CHIPSETINIT_CRC_SUS_MAX_SIZE) {
    PchHsioChipsetInitSusTblData->PchHsioSusCrc[CrcIndex].AndData = CrcAndMask;
    PchHsioChipsetInitSusTblData->PchHsioSusCrc[CrcIndex].OrData  = CrcOrMask;
  } else {
    ASSERT (FALSE); //CrcIndex invalid
    return EFI_DEVICE_ERROR;
  }

  if (Pid == PID_USB2) {
    DestPtr = PchHsioChipsetInitSusTblData->PchHsioSusUsb2Tuning + ((PchHsioChipsetInitSusTblData->PchHsioSusUsb2TuningCount * sizeof (PCH_HSIO_DATA_CMD)) / sizeof (UINT32));
    PchHsioChipsetInitSusTblData->PchHsioSusUsb2TuningCount++;
    if (((PchHsioChipsetInitSusTblData->PchHsioSusUsb2TuningCount * sizeof (PCH_HSIO_DATA_CMD)) / sizeof (UINT32)) > PCH_HSIO_CHIPSETINIT_USB2_SUS_MAX_SIZE) {
      ASSERT (FALSE); //USB2 SUS Table size exceed allocated buffer size
      return EFI_DEVICE_ERROR;
    }
  } else {
    DestPtr = PchHsioChipsetInitSusTblData->PchHsioSusModPhyTuning + ((PchHsioChipsetInitSusTblData->PchHsioSusModPhyTuningCount * sizeof (PCH_HSIO_DATA_CMD)) / sizeof (UINT32));
    PchHsioChipsetInitSusTblData->PchHsioSusModPhyTuningCount++;
    if (((PchHsioChipsetInitSusTblData->PchHsioSusModPhyTuningCount * sizeof (PCH_HSIO_DATA_CMD)) / sizeof (UINT32))  > PCH_HSIO_CHIPSETINIT_MODPHY_SUS_MAX_SIZE) {
      ASSERT (FALSE); //ModPHY Tuning SUS Table size exceed allocated buffer size
      return EFI_DEVICE_ERROR;
    }
  }
  CopyMem (DestPtr, (VOID *) &PchHsioCmdTblEntry, sizeof (PCH_HSIO_DATA_CMD));
  return EFI_SUCCESS;
}

/**
  Modify HSIO lane DWORD and update ChipsetInit SUS Table.

  @param[in] HsioLane   HSIO Lane
  @param[in] Offset     PCR offset
  @param[in] AndMask    Mask to be ANDed with original value.
  @param[in] OrMask     Mask to be ORed with original value.
**/
VOID
HsioLaneAndThenOr32WithSusWrite (
  CONST HSIO_LANE *HsioLane,
  UINT32    Offset,
  UINT32    AndMask,
  UINT32    OrMask
  )
{
  HsioLaneAndThenOr32 (HsioLane, Offset, AndMask, OrMask);
  HsioChipsetInitSusWrite32 (
    HsioLane->Pid,
    HsioLane->Base + Offset,
    HsioLaneRead32 (HsioLane, Offset),
    AndMask,
    OrMask
    );
}

/**
  Write PCR register and update ChipsetInit SUS Table.
  It programs PCR register and size in 4bytes then update ChipsetInit SUS Table..
  The Offset should not exceed 0xFFFF and must be aligned with size.

  @param[in]  Pid      Port ID
  @param[in]  Offset   Register offset of Port ID.
  @param[in]  AndData  AND Data. Must be the same size as Size parameter.
  @param[in]  OrData   OR Data. Must be the same size as Size parameter.

**/
VOID
PchPcrAndThenOr32WithSusWrite (
  IN  PCH_SBI_PID                       Pid,
  IN  UINT32                            Offset,
  IN  UINT32                            AndData,
  IN  UINT32                            OrData
  )
{
  PchPcrAndThenOr32 (Pid, Offset, AndData, OrData);
  HsioChipsetInitSusWrite32 (
    Pid,
    Offset,
    PchPcrRead32 (Pid, Offset),
    AndData,
    OrData
    );
}

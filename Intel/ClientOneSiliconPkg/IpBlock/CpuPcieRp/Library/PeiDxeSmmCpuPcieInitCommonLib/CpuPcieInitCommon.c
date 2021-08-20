/** @file
 common library for CPU PCIe INIT PEI/DXE/SMM modules

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

@par Specification Reference:
**/

#include <Uefi/UefiBaseType.h>
#include <Library/DebugLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/IoLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/CpuPcieRpLib.h>
#include <Library/CpuSbiAccessLib.h>
#include <Register/CpuPcieRegs.h>
#include <Library/CpuPcieInitCommon.h>
#include <CpuSbInfo.h>

/**
  This function returns PID according to PCIe controller index

  @param[in] ControllerIndex     PCIe controller index

  @retval CPU_SB_DEVICE_PID    Returns PID for SBI Access
**/
CPU_SB_DEVICE_PID
GetCpuPcieControllerSbiPid (
  IN  UINT32  ControllerIndex
  )
{
//
// Note : PEG060 will be treated as controller 0 for all SKUs to maintain uniform coding and avoid CpuFamily check in all functions
//
  switch(ControllerIndex){
    case 0:
      return CPU_SB_PID_PEG60;
    case 1:
      return CPU_SB_PID_PEG10;
    case 2:
      return CPU_SB_PID_PEG11_12;
    default:
      ASSERT(FALSE);
      return CPU_SB_PID_PEG60;
  }
}

/**
  This function returns PID according to Root Port Number

  @param[in] RpIndex     Root Port Index (0-based)

  @retval CPU_SB_DEVICE_PID    Returns PID for SBI Access
**/
CPU_SB_DEVICE_PID
GetCpuPcieRpSbiPid (
  IN  UINTN  RpIndex
  )
{
//
// Note : PEG060 will be treated as controller 0 for all SKUs to maintain uniform coding and avoid CpuFamily check in all functions
//
  switch(RpIndex){
    case 0:
      return CPU_SB_PID_PEG60;
    case 1:
      return CPU_SB_PID_PEG10;
    case 2:
    case 3:
      return CPU_SB_PID_PEG11_12;
    default:
      ASSERT(FALSE);
      return CPU_SB_PID_PEG60;
  }
}

/**
  This function reads PCI Config register via SBI Access or through IOM mailbox

  @param[in]  RpIndex             Root Port Index (0-based)
  @param[in]  Offset              Offset of Config register
  @param[out] *Data32             Value of Config register

  @retval EFI_SUCCESS             SBI Read successful.
**/
EFI_STATUS
CpuPcieRpSbiRead32 (
  IN    UINT32  RpIndex,
  IN    UINT32  Offset,
  OUT   UINT32  *Data32
  )
{
  EFI_STATUS    Status;
  UINT8         Response;
  UINT16        Fid;

//
// ICL-R does not support FID manipulation
// @TODO : Modify this function to use IOM mailbox command in the case of ICL-R
//

  //
  // Fid = 1 only for PEG12 which according to our design will always be RpIndex 3
  //
  if(RpIndex == 3){
    Fid = 1;
  } else {
    Fid = 0;
  }

  Status = CpuSbiExecutionEx (
             GetCpuPcieRpSbiPid (RpIndex),
             Offset,
             PciConfigRead,
             FALSE,
             0xF,
             0,
             Fid,
             Data32,
             &Response
             );
  if (Status != EFI_SUCCESS) {
    DEBUG((DEBUG_ERROR,"Sideband Read Failed of RpIndex %d Offset 0x%x. Fid = 0x%x\n",RpIndex, Offset, Fid));
    ASSERT (FALSE);
  }
  return Status;
}

/**
  This function And then Or Pci Config register via SBI Access

  @param[in]  RpIndex             Root Port Index (0-based)
  @param[in]  Offset              Offset of Config register
  @param[in]  Data32And           Value of Config register to be And-ed
  @param[in]  Data32AOr           Value of Config register to be Or-ed

  @retval EFI_SUCCESS             SBI Read and Write successful.
**/
EFI_STATUS
CpuPcieRpSbiAndThenOr32 (
  IN  UINT32  RpIndex,
  IN  UINT32  Offset,
  IN  UINT32  Data32And,
  IN  UINT32  Data32Or
  )
{
  EFI_STATUS  Status;
  UINT32      Data32;
  UINT8       Response;
  UINT16      Fid;

//
// ICL-R does not support FID manipulation
// @TODO : Modify this function to use IOM mailbox command in the case of ICL-R
//

  // Fid = 1 only for PEG12 which according to our design will always be RpIndex 3
  if(RpIndex == 3){
    Fid = 1;
  } else {
    Fid = 0;
  }

  Status = CpuPcieRpSbiRead32 (RpIndex, Offset, &Data32);
  if (Status == EFI_SUCCESS) {
    Data32 &= Data32And;
    Data32 |= Data32Or;
    Status = CpuSbiExecutionEx (
               GetCpuPcieRpSbiPid (RpIndex),
               Offset,
               PciConfigWrite,
               FALSE,
               0xF,
               0,
               Fid,
               &Data32,
               &Response
               );
    if (Status != EFI_SUCCESS) {
      DEBUG((DEBUG_ERROR,"Sideband Write Failed of RpIndex %d Offset 0x%x. Fid = 0x%x\n",RpIndex, Offset, Fid));
      ASSERT (FALSE);
    }
  } else {
    ASSERT (FALSE);
  }
  return Status;
}

/**
  Print registers value

  @param[in] PrintMmioBase       Mmio base address
  @param[in] PrintSize           Number of registers
  @param[in] OffsetFromBase      Offset from mmio base address

  @retval None
**/
VOID
SaPrintRegisters (
  IN  UINTN        PrintMmioBase,
  IN  UINT32       PrintSize,
  IN  UINT32       OffsetFromBase
  )
{
  UINT32  Offset;
  DEBUG ((DEBUG_VERBOSE, "       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"));
  for (Offset = 0; Offset < PrintSize; Offset++) {
    if ((Offset % 16) == 0) {
      DEBUG ((DEBUG_VERBOSE, "\n %04X: ", (Offset + OffsetFromBase) & 0xFFF0));
    }
    DEBUG ((DEBUG_VERBOSE, "%02X ", MmioRead8 (PrintMmioBase + Offset)));
  }
  DEBUG ((DEBUG_VERBOSE, "\n"));
}

/**
  Print registers value

  @param[in] PrintPciSegmentBase Pci segment base address
  @param[in] PrintSize           Number of registers
  @param[in] OffsetFromBase      Offset from mmio base address

  @retval None
**/
VOID
SaPrintPciRegisters (
  IN  UINT64       PrintPciSegmentBase,
  IN  UINT32       PrintSize,
  IN  UINT32       OffsetFromBase
  )
{
  UINT32  Offset;
  DEBUG ((DEBUG_VERBOSE, "       00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"));
  for (Offset = 0; Offset < PrintSize; Offset++) {
    if ((Offset % 16) == 0) {
      DEBUG ((DEBUG_VERBOSE, "\n %04X: ", (Offset + OffsetFromBase) & 0xFFF0));
    }
    DEBUG ((DEBUG_VERBOSE, "%02X ", PciSegmentRead8 (PrintPciSegmentBase + Offset)));
  }
  DEBUG ((DEBUG_VERBOSE, "\n"));
}

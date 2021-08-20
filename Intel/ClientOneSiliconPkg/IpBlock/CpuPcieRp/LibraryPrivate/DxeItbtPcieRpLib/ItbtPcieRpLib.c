/** @file
  ITBT PCIE root port library.
  All function in this library is available for PEI, DXE, and SMM.
  This library has a dependency with TcssHob.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2019 Intel Corporation.

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
#include <Library/PciSegmentLib.h>
#include <Library/ItbtPcieRpLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED ITBT_PCIE_RP_INFO mIbtbPcieRpInfo[] = {
//
// Segment       Bus                  Device                 Function                 Enable
//
  { 0,     SA_ITBT_PCIE_BUS_NUM, SA_ITBT_PCIE_DEV_NUM, SA_ITBT_PCIE_0_DEFAULT_FUN_NUM, TRUE },  // Itbt Pcie Rp 1
  { 0,     SA_ITBT_PCIE_BUS_NUM, SA_ITBT_PCIE_DEV_NUM, SA_ITBT_PCIE_1_DEFAULT_FUN_NUM, TRUE },  // Itbt Pcie Rp 2
  { 0,     SA_ITBT_PCIE_BUS_NUM, SA_ITBT_PCIE_DEV_NUM, SA_ITBT_PCIE_2_DEFAULT_FUN_NUM, FALSE }, // Itbt Pcie Rp 3
  { 0,     SA_ITBT_PCIE_BUS_NUM, SA_ITBT_PCIE_DEV_NUM, SA_ITBT_PCIE_3_DEFAULT_FUN_NUM, FALSE }  // Itbt Pcie Rp 4
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT32 mItbtPcieRpCount = sizeof (mIbtbPcieRpInfo) / sizeof (mIbtbPcieRpInfo[0]);

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN mItbtPcieRpInfoUpdated = FALSE;

/**
  Get ITBT Pcie Root Port Segment Bus Device and Function Number by Port Index

  @param[in]  PortIndex             Root port index. (0-based)
  @param[out] Segment               Return corresponding root port segment number.
  @param[out] Bus                   Return corresponding root port bus number.
  @param[out] Device                Return corresponding root port device number.
  @param[out] Function              Return corresponding root port function number.

  @retval     EFI_SUCCESS           Root port Info is retrieved
  @retval     EFI_UNSUPPORTED       PortIndex is invalid/disabled, or TcssHob is not existed when mItbtPcieRpInfoUpdated is FALSE.
**/
EFI_STATUS
EFIAPI
GetItbtPcieRpInfo (
  IN   UINTN    PortIndex,
  OUT  UINTN    *Segment,
  OUT  UINTN    *Bus,
  OUT  UINTN    *Device,
  OUT  UINTN    *Function
  )
{
  TCSS_DATA_HOB            *TcssHob;
  UINT32                   PcieSegMap;
  UINT32                   PcieFuncMap;

  TcssHob   = NULL;
  PcieSegMap  = 0;
  PcieFuncMap = 0;

  //
  // Iniatialize the Segment, Bus, Device, Function
  //
  *Segment  = 0;
  *Bus      = 0;
  *Device   = 0;
  *Function = 0;

  if(PortIndex >= MAX_ITBT_PCIE_PORT) {
    DEBUG ((DEBUG_ERROR, "Invalid PortIndex %x", PortIndex));
    return EFI_UNSUPPORTED;
  }

  if (mItbtPcieRpInfoUpdated == TRUE) {
    if (mIbtbPcieRpInfo[PortIndex].Enable == TRUE) {
      *Segment  = mIbtbPcieRpInfo[PortIndex].Segment;
      *Bus      = mIbtbPcieRpInfo[PortIndex].Bus;
      *Device   = mIbtbPcieRpInfo[PortIndex].Device;
      *Function = mIbtbPcieRpInfo[PortIndex].Function;
      return EFI_SUCCESS;
    }
  } else {
    TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
    if (TcssHob != NULL) {
      PcieSegMap = TcssHob->TcssData.ItbtPcieSegMap;
      PcieFuncMap= TcssHob->TcssData.ItbtPcieFuncMap;
      //
      // Update the Segment/Function pointers based on PcieSegMap & PcieFuncMap when Port enabled
      //
      if (TcssHob->TcssData.ItbtPcieRpEn[PortIndex]) {
        *Segment  = (PcieSegMap >> (4 * PortIndex) ) & 0xF;
        *Bus      = mIbtbPcieRpInfo[PortIndex].Bus;
        *Device   = mIbtbPcieRpInfo[PortIndex].Device;
        *Function = (PcieFuncMap >> (3 * PortIndex) ) & 0x7;
        return EFI_SUCCESS;
      }
    }
  }

  return EFI_UNSUPPORTED;
}

/**
  Get ITBT PCIE Root Port Index by ITBT PCIE Root Port Segment Bus Device and Function Number

  @param[in]  Segment             Root port segment number.
  @param[in]  Bus                 Root port Bus.
  @param[in]  Device              Root port Device.
  @param[in]  Function            Root port Function.
  @param[out] PortIndex           Return corresponding Root Port index (0-based)

  @retval     EFI_SUCCESS           PortIndex is retrieved
  @retval     EFI_UNSUPPORTED       PortIndex is invalid/disabled or TcssHob is not existed when mItbtPcieRpInfoUpdated is FALSE.
**/
EFI_STATUS
EFIAPI
GetItbtPciePortIndex (
  IN   UINTN    Segment,
  IN   UINTN    Bus,
  IN   UINTN    Device,
  IN   UINTN    Function,
  OUT  UINTN    *PortIndex
  )
{
  UINTN                    Index;
  TCSS_DATA_HOB              *TcssHob;
  UINT32                   PcieSegMap;
  UINT32                   PcieFuncMap;
  UINT8                    Seg;
  UINT8                    Func;

  TcssHob   = NULL;
  PcieSegMap  = 0;
  PcieFuncMap = 0;
  Seg         = 0;
  Func        = 0;

  for (Index = 0; Index < mItbtPcieRpCount; Index++) {
    if (mItbtPcieRpInfoUpdated == TRUE) {
      if (mIbtbPcieRpInfo[Index].Segment == Segment && mIbtbPcieRpInfo[Index].Bus == Bus && mIbtbPcieRpInfo[Index].Device == Device && mIbtbPcieRpInfo[Index].Function == Function) {
        if (mIbtbPcieRpInfo[Index].Enable == TRUE) {
          *PortIndex = Index;
          return EFI_SUCCESS;
        }
      }
    } else {
      TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);
      if (TcssHob != NULL) {
        PcieSegMap = TcssHob->TcssData.ItbtPcieSegMap;
        PcieFuncMap= TcssHob->TcssData.ItbtPcieFuncMap;
        Seg  = (PcieSegMap >> (4 * Index) ) & 0xF;
        Func = (PcieFuncMap >> (3 * Index) ) & 0x7;

        if (Seg == Segment && mIbtbPcieRpInfo[Index].Bus == Bus && mIbtbPcieRpInfo[Index].Device == Device && Func == Function) {
          *PortIndex = Index;
          return EFI_SUCCESS;
        }
      }
    }
  }
  return EFI_UNSUPPORTED;
}

/**
  This constructor performs initialization for TBT Device Info Internal Structure.
**/
EFI_STATUS
EFIAPI
ITbtPcieRpLibConstructor (
  VOID
  )
{
  TCSS_DATA_HOB              *TcssHob;
  UINT32                   PcieFuncMap;
  UINT32                   PcieSegMap;
  UINTN                    Index;
  UINT8                    Segment;
  UINT8                    Function;

  DEBUG ((DEBUG_INFO, "ITbtPcieRpLibConstructor - Start\n"));

  TcssHob = NULL;
  TcssHob = (TCSS_DATA_HOB *) GetFirstGuidHob (&gTcssHobGuid);

  if ((TcssHob != NULL) && (TcssHob->TcssData.IOMReady == TRUE)) {
    PcieSegMap  = TcssHob->TcssData.ItbtPcieSegMap;
    PcieFuncMap = TcssHob->TcssData.ItbtPcieFuncMap;

    for(Index = 0; Index < mItbtPcieRpCount; Index++) {
      Function = (PcieFuncMap >> (3 * Index) ) & 0x7;
      Segment  = (PcieSegMap >> (4 * Index) ) & 0xF;

      DEBUG ((DEBUG_INFO, "iTBT PCIE RP%d Segment %d Function %d \n",Index,Segment, Function));
      mIbtbPcieRpInfo[Index].Function = (UINT8)Function;
      mIbtbPcieRpInfo[Index].Segment  = (UINT8)Segment;
      //
      //  Update the Enable Status based on iTBT Pcie RP Status
      //
      if (TcssHob->TcssData.ItbtPcieRpEn[Index]) {
        mIbtbPcieRpInfo[Index].Enable = TRUE;
      } else {
        mIbtbPcieRpInfo[Index].Enable = FALSE;
      }
    }
    //
    // Update the global flag indicating iTBT PCIE RP Info Table Updated
    //
    mItbtPcieRpInfoUpdated = TRUE;
  }
  DEBUG ((DEBUG_INFO, " ITbtPcieRpLibConstructor - End\n"));

  return EFI_SUCCESS;
}

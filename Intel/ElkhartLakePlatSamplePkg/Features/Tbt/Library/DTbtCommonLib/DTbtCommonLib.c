/** @file
  PeiTbtInit library implementition with empty functions.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification
**/

#include <Library/DebugLib.h>
#include <Uefi/UefiBaseType.h>
#include <Library/PchPcieRpLib.h>
#include <Library/DTbtCommonLib.h>
#include <Library/TbtCommonLib.h>
#include <Library/PciSegmentLib.h>
#include <Library/TimerLib.h>
#include <Library/BaseLib.h>
#include <Library/GpioLib.h>
#include <DTbtDefinition.h>

/**
Based on the Security Mode Selection, BIOS drives FORCE_PWR.

@param[in]  GpioNumber
@param[in]  Value
**/
VOID
ForceDtbtPower(
   IN  UINT32         GpioNumber,
   IN  BOOLEAN        Value
)
{
   GpioSetOutputValue(GpioNumber, (UINT32)Value);
}

/**
  Get Pch/Peg Pcie Root Port Device and Function Number for TBT by Root Port physical Number

  @param[in]  Type                  TYPE_PCH (0x01) or TYPE_PEG (0x02)
  @param[in]  RpNumber              Root port physical number. (0-based)
  @param[out] RpDev                 Return corresponding root port device number.
  @param[out] RpFun                 Return corresponding root port function number.

  @retval     EFI_SUCCESS           Root port device and function is retrieved
  @retval     EFI_INVALID_PARAMETER If Invalid Root Port Number or TYPE is Passed
**/
EFI_STATUS
EFIAPI
GetDTbtRpDevFun (
  IN  UINT8   Type,
  IN  UINTN   RpNumber,
  OUT UINTN   *RpDev,
  OUT UINTN   *RpFunc
  )
{
  EFI_STATUS            Status;
  UINTN                 TbtRpDev;
  UINTN                 TbtRpFunc;

  Status = EFI_INVALID_PARAMETER; // Update the Status to EFI_SUCCESS if valid input found.
  //
  // PCH-H can support up to 24 root ports. PEG0,PEG1 and PEG2 will be
  // with device number 0x1 and Function number 0,1 and 2 respectively.
  //
  if (Type == TYPE_PEG)
  {
    //
    //  PEG Rootport
    //
    if (RpNumber <= 2) {
      *RpDev  =   0x01;
      *RpFunc =   RpNumber;
      Status  =   EFI_SUCCESS;
    }
    //
    // If PEG3 supported, it will have Device number 0x06 and Function Number 0x0.
    //
    if (RpNumber == 0x03) {
      *RpDev  =   0x06;
      *RpFunc =   0x0;
      Status  =   EFI_SUCCESS;
    }
  }
  if (Type == TYPE_PCH)
  {
    //
    //  PCH Rootport
    //
    if (RpNumber <= 23) {
      Status  = GetPchPcieRpDevFun (RpNumber, &TbtRpDev, &TbtRpFunc);
      *RpDev  = TbtRpDev;
      *RpFunc = TbtRpFunc;
    }
  }

  ASSERT_EFI_ERROR (Status);
  return Status;
}

BOOLEAN
IsTbtHostRouter (
  IN    UINT16  DeviceID
  )
{
  switch (DeviceID) {
  case AR_HR_2C:
  case AR_HR_4C:
  case AR_HR_LP:
  case AR_HR_C0_2C:
  case AR_HR_C0_4C:
  case TR_HR_2C:
  case TR_HR_4C:
    return TRUE;
  }

  return FALSE;
} // IsTbtHostRouter

/**
  BIOS sends the "Get_Security_Level" mailbox command to verify that the required security level is set to HR

  @param[in]  Tbt2PcieOffset            TBT2PCIE Register Offset
  @param[in]  Pcie2TbtOffset            PCIE2TBT Register Offset
  @param[in]  Bus                       Bus number for Host Router (DTBT)
  @param[in]  Device                    Device number for Host Router (DTBT)
  @param[in]  Function                  Function number for Host Router (DTBT)
  @param[in]  Timeout                   Time out with 100 ms garnularity
**/
UINT8
GetSecLevel (
  IN  UINT16                            Tbt2PcieOffset,
  IN  UINT16                            Pcie2TbtOffset,
  IN  UINT8                             Bus,
  IN  UINT8                             Device,
  IN  UINT8                             Function,
  IN  UINT8                             Command,
  IN  UINT32                            Timeout
  )
{
  UINT64                                Pcie2Tbt;
  UINT64                                Tbt2Pcie;
  UINT32                                RegisterValue;
  UINT8                                 ReturnFlag;

  ReturnFlag           = 0xFF;

  DEBUG ((DEBUG_INFO, "[TBT] GetSecLevel() \n"));

  Tbt2Pcie = PCI_SEGMENT_LIB_ADDRESS(0, Bus, Device, Function, Tbt2PcieOffset);
  Pcie2Tbt = PCI_SEGMENT_LIB_ADDRESS(0, Bus, Device, Function, Pcie2TbtOffset);

  PciSegmentWrite32 (Pcie2Tbt, Command | PCIE2TBT_VLD_B);

  if(InternalWaitforCommandCompletion (Tbt2Pcie, Timeout, TRUE, &RegisterValue)) {
    ReturnFlag     = (UINT8) (0xFF & (RegisterValue >> 8));
  }

  PciSegmentWrite32 (Pcie2Tbt, 0);

  InternalWaitforCommandCompletion (Tbt2Pcie, Timeout, FALSE, &RegisterValue);
  DEBUG ((DEBUG_INFO, "Security Level configured to %x \n", ReturnFlag));

  return ReturnFlag;
}

/**
  BIOS initiates the "Set_Security_Level" mailbox command with the required security level to HR

  @param[in]  Data                      Security State
  @param[in]  Tbt2PcieOffset            TBT2PCIE Register Offset
  @param[in]  Pcie2TbtOffset            PCIE2TBT Register Offset
  @param[in]  Bus                       Bus number for Host Router (DTBT)
  @param[in]  Device                    Device number for Host Router (DTBT)
  @param[in]  Function                  Function number for Host Router (DTBT)
  @param[in]  Timeout                   Time out with 100 ms garnularity
**/
BOOLEAN
SetSecLevel (
  IN    UINT8                           Data,
  IN    UINT16                          Tbt2PcieOffset,
  IN    UINT16                          Pcie2TbtOffset,
  IN    UINT8                           Bus,
  IN    UINT8                           Device,
  IN    UINT8                           Function,
  IN    UINT8                           Command,
  IN    UINT32                          Timeout
  )
{
  UINT64                                Pcie2Tbt;
  UINT64                                Tbt2Pcie;
  UINT32                                RegisterValue;
  BOOLEAN                               ReturnFlag;

  ReturnFlag   = FALSE;

  DEBUG ((DEBUG_INFO, "[TBT] SetSecLevel() \n"));

  Tbt2Pcie = PCI_SEGMENT_LIB_ADDRESS(0, Bus, Device, Function, Tbt2PcieOffset);
  Pcie2Tbt = PCI_SEGMENT_LIB_ADDRESS(0, Bus, Device, Function, Pcie2TbtOffset);

  PciSegmentWrite32 (Pcie2Tbt, (Data << 8) | Command | PCIE2TBT_VLD_B);

  ReturnFlag = InternalWaitforCommandCompletion (Tbt2Pcie, Timeout, TRUE, &RegisterValue);
  DEBUG ((DEBUG_INFO, "RegisterValue %x \n", RegisterValue));
  PciSegmentWrite32 (Pcie2Tbt, 0);

  InternalWaitforCommandCompletion (Tbt2Pcie, Timeout, FALSE, &RegisterValue);
  DEBUG ((DEBUG_INFO, "Return value %x \n", ReturnFlag));
  return ReturnFlag;
}

/**
  Send command to notify CM to exit Sx and the system went to sleep with attached devices previously

  @param[in]  Controller                Controller number. (0-based)
  @param[out] Segment                   Return corresponding Tbt HIA Segment number.
  @param[out] Bus                       Return corresponding Tbt HIA Bus number.
  @param[out] Device                    Return corresponding Tbt HIA device number.
  @param[out] Function                  Return corresponding Tbt HIA function number.

  @retval     EFI_SUCCESS                 Root port device and function is retrieved
**/
VOID
TbtSetSxMode(
  IN UINT16                             Tbt2PcieOffset,
  IN UINT16                             Pcie2TbtOffset,
  IN UINT8                              Bus,
  IN UINT8                              Device,
  IN UINT8                              Function
)
{
  UINT64  TbtUsDevId;
  UINT64  Tbt2Pcie;
  UINT32  RegVal;
  UINT32  MaxLoopCount;
  UINTN   Delay;
  UINT8   RetCode;

  TbtUsDevId = PCI_SEGMENT_LIB_ADDRESS (0, Bus, Device, Function, 0);
  Tbt2Pcie = PCI_SEGMENT_LIB_ADDRESS (0, Bus, Device, Function, Tbt2PcieOffset);

  MaxLoopCount = 150;  // Wait 15 sec
  Delay = 100 * 1000;
  RetCode = 0x62;

  if (!TbtSetPcie2TbtCommand (PCIE2TBT_SX_EXIT_TBT_CONNECTED, Tbt2PcieOffset, Pcie2TbtOffset, Bus, Device, Function, MaxLoopCount)) {
    //
    // Nothing to wait, HR is not responsive
    //
    return;
  }

  DEBUG((DEBUG_INFO, "Wait for Dev ID != 0xFF\n"));

  while (MaxLoopCount-- > 0) {
    //
    // Check what HR still here
    //
    RegVal = PciSegmentRead32 (Tbt2Pcie);
    if (0xFFFFFFFF == RegVal) {
      RetCode = 0x6F;
      break;
    }
    //
    // Check completion of TBT link
    //
    RegVal = PciSegmentRead32 (TbtUsDevId);
    if (0xFFFFFFFF != RegVal) {
      RetCode = 0x61;
      break;
    }

    MicroSecondDelay(Delay);
  }

  DEBUG((DEBUG_INFO, "Return code = 0x%x\n", RetCode));
}

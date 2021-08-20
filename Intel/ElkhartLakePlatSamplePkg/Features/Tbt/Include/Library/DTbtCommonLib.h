/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2018 Intel Corporation.

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

@par Specification Reference:

**/
#ifndef _DTBT_COMMON_LIB_H_
#define _DTBT_COMMON_LIB_H_

#include <Library/BaseLib.h>

#define TBT_5S_TIMEOUT                    50
#define TBT_1S_TIMEOUT                    10

//
//Thunder Bolt Device IDs
//

//
// Alpine Ridge HR device IDs
//
#define AR_HR_2C  0x1576
#define AR_HR_4C  0x1578
#define AR_XHC    0x15B5
#define AR_XHC_4C 0x15B6
#define AR_HR_LP  0x15C0
//
// Alpine Ridge C0 HR device IDs
//
#define AR_HR_C0_2C  0x15DA
#define AR_HR_C0_4C  0x15D3
//
// Titan Ridge HR device IDs
//
#define TR_HR_2C  0x15E7
#define TR_HR_4C  0x15EA
//
//End of Thunderbolt(TM) Device IDs
//

//@todo Seems to only be used by Platform/TBT/Smm/TbtSmm.inf
//@todo should refactor this to only be present in that driver
//@todo also definitions like this should never be in a .h file anyway
//@todo this is a quick hack to get things compiling for now
#ifdef __GNUC__
#pragma GCC diagnostic warning "-Wunused-variable"
#endif

/**
Based on the Security Mode Selection, BIOS drives FORCE_PWR.

@param[in]  GpioNumber
@param[in]  Value
**/
VOID
ForceDtbtPower(
  IN  UINT32         GpioNumber,
  IN  BOOLEAN        Value
);

/**
  Check connected TBT controller is supported or not by DeviceID

  @param[in]  DeviceID              DeviceID of of TBT controller


  @retval     TRUE                  Valid DeviceID
  @retval     FALSE                 Invalid DeviceID
**/

BOOLEAN
IsTbtHostRouter (
  IN    UINT16  DeviceID
  );

/**
  Get Pch/Peg Pcie Root Port Device and Function Number for TBT by Root Port physical Number

  @param[in]  Type                  TYPE_PCH (0x01) or TYPE_PEG (0x02)
  @param[in]  RpNumber              Root port physical number. (0-based)
  @param[out] RpDev                 Return corresponding root port device number.
  @param[out] RpFun                 Return corresponding root port function number.

  @retval     EFI_SUCCESS           Root port device and function is retrieved
**/
EFI_STATUS
EFIAPI
GetDTbtRpDevFun(
  IN  UINT8   Type,
  IN  UINTN   RpNumber,
  OUT UINTN   *RpDev,
  OUT UINTN   *RpFunc
  );

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
  );

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
  );

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
);

#endif

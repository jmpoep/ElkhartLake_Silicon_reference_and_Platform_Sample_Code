/** @file
  Pch information library for ICL.

  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#include "MrcOemPlatform.h"
#include <Library/PchInfoLib.h>
#include <Register/PchRegsLpcIcl.h>
//#include "PchInfoLibPrivate.h"
//#include <Private/Library/PmcPrivateLib.h>
#include <Register/PchRegsLpc.h>

/**
  Determine Pch Series based on Device Id

  @param[in] LpcDeviceId      Lpc Device Id

  @retval PCH_SERIES          Pch Series
**/
PCH_SERIES
PchSeriesFromLpcDid (
  IN UINT16 LpcDeviceId
  )
{
  switch (LpcDeviceId & B_LPC_CFG_DID) {

    case V_LPC_CFG_DID_ICL_H:
      return PCH_H;

    case V_LPC_CFG_DID_ICL_LP:
      return PCH_LP;

    case V_LPC_CFG_DID_ICL_N:
      return PCH_N;

    default:
      return PCH_UNKNOWN_SERIES;
  }
}

/**
  Return Pch Generation

  @retval PCH_GENERATION      Pch Generation
**/
PCH_GENERATION
PchGeneration (
  VOID
  )
{
  return ICL_PCH;
}

/**
  Check if this is Server PCH

  @retval TRUE                It's a Server PCH
  @retval FALSE               It's not a Server PCH
**/
BOOLEAN
IsPchServer (
  VOID
  )
{
  return FALSE;
}

#ifndef MRC_MINIBIOS_BUILD
/**
  Check if this is PCH N series

  @retval TRUE                It's PCH N series
  @retval FALSE               It's not PCH N series
**/
BOOLEAN
IsPchN (
  VOID
  )
{
  return (PchSeries () == PCH_N);
}

#endif // MRC_MINIBIOS_BUILD

#ifndef MRC_MINIBIOS_BUILD
/**
  Get RST mode supported by the silicon

  @retval RST_MODE    RST mode supported by silicon
**/
RST_MODE
PchGetSupportedRstMode (
  VOID
  )
{
  UINT16    LpcDeviceId;

  LpcDeviceId = PchGetLpcDid ();

  switch (LpcDeviceId) {
    case V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_1:
    case V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_2:
    case V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_4:
    case V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_6:
    case V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_7:
    case V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_4:
    case V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_5:
    case V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_6:
    case V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_9:
    case V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_12:
    case V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_13:
    case V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_14:
      return RstPremium;
      break;
    case V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_8:
      return RstOptane;
      break;
    default:
      return RstUnsupported;
      break;
  }
}
#endif // MRC_MINIBIOS_BUILD

/**
  Check if this is Server SKU

  @retval TRUE                It's PCH Server SKU
  @retval FALSE               It's not PCH Server SKU
**/
BOOLEAN
IsPchServerSku (
  VOID
  )
{
  return FALSE;
}

/**
  Get PCH series ASCII string.

  @retval PCH Series string
**/
CHAR8*
PchGetSeriesStr (
  VOID
  )
{
  switch (PchSeries ()) {

    case PCH_LP:
      return "ICL PCH-LP";

    case PCH_H:
      return "ICL PCH-H";

    case PCH_N:
      return "ICL PCH-N";

    default:
      return NULL;
  }
}

#ifndef MRC_MINIBIOS_BUILD
//GLOBAL_REMOVE_IF_UNREFERENCED
struct PCH_SKU_STRING mSkuStrs[] = {
  //
  // ICL PCH LP Mobile LPC Device IDs
  //
  {V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_0,   "ICP-LP SKU 0"},
  {V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_1,   "ICP-LP U Super SKU (SSKU)"},
  {V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_2,   "ICP-LP U Premium"},
  {V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_3,   "ICP-LP U Base/Mainstream"},
  {V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_4,   "ICP-LP SKU 4"},
  {V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_5,   "ICP-LP SKU 5"},
  {V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_6,   "ICP-LP Y Super SKU (SSKU)"},
  {V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_7,   "ICP-LP Y Premium"},
  {V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_10,  "ICP-LP U IOT SuperSKU (IoT_SSKU-U)"},
  {V_ICL_PCH_LP_LPC_CFG_DEVICE_ID_MB_11,  "ICP-LP U IOT Premium (IoT_Prem_U)"},
  //
  // ICL PCH N LPC Device IDs
  //
  {V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_0,    "ICP-N SKU 0"},
  {V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_1,    "ICP-N U Super SKU (SSKU)"},
  {V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_2,    "ICP-N U Premium"},
  {V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_3,    "ICP-N U Base/Mainstream"},
  {V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_6,    "ICP-N Y Super SKU (SSKU)"},
  {V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_7,    "ICP-N Y Premium"},
  {V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_10,   "ICP-N H Super SKU (SSKU)"},
  {V_ICL_PCH_N_LPC_CFG_DEVICE_ID_MB_11,   "ICP-N H Premium"},
  //
  // ICL PCH H LPC Device IDs
  //
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_0,    "ICP-H SKU 0"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_1,    "ICP-H Client Super SKU (SSKU) Unlocked"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_3,    "ICP-H H410"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_4,    "ICP-H H470"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_5,    "ICP-H Z470"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_6,    "ICP-H Q470"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_8,    "ICP-H B460"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_9,    "ICP-H C256"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_10,   "ICP-H C252"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_11,   "ICP-H X599"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_12,   "ICP-H QM470"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_13,   "ICP-H HM370"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_14,   "ICP-H CM256"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_16,   "ICP-H Server Super SKU (SSKU) Unlocked"},
  {V_ICL_PCH_H_LPC_CFG_DEVICE_ID_MB_20,   "ICP-H Internal Production (PSKU)"},
  {0xFFFF, NULL}
};
#endif // MRC_MINIBIOS_BUILD

/**
  Get Pch Maximum Type C Port Number

  @retval Pch Maximum Type C Port Number
**/
UINT8
GetPchMaxTypeCPortNum (
  VOID
  )
{
  switch (PchSeries ()) {
    case PCH_LP:
      return 4;
    case PCH_N:
      return 6;
    case PCH_H:
      return 4;
    default:
      return 0;
  }
}

/**
  Check whether integrated LAN controller is supported by PCH Series.

  @retval TRUE                    GbE is supported in current PCH
  @retval FALSE                   GbE is not supported on current PCH
**/
BOOLEAN
PchIsGbeSupported (
  VOID
  )
{
  if (IsPchN ()) {
    return FALSE;
  }
  return TRUE;
}

/**
  Check whether ISH is supported by PCH Series.

  @retval TRUE                    ISH is supported in current PCH
  @retval FALSE                   ISH is not supported on current PCH
**/
BOOLEAN
PchIsIshSupported (
  VOID
  )
{
  if (IsPchN ()) {
    return FALSE;
  }
  return TRUE;
}

/**
  Get Pch Maximum Pcie Root Port Number

  @retval Pch Maximum Pcie Root Port Number
**/
UINT8
GetPchMaxPciePortNum (
  VOID
  )
{
  switch (PchSeries ()) {
    case PCH_LP:
      return 16;
    case PCH_N:
      return 8;
    case PCH_H:
      return 24;
    default:
      return 0;
  }
}

/**
  Get Pch Usb2 Maximum Physical Port Number

  @retval Pch Usb2 Maximum Physical Port Number
**/
UINT8
GetPchUsb2MaxPhysicalPortNum (
  VOID
  )
{
  switch (PchSeries ()) {
    case PCH_LP:
      return 10;
    case PCH_N:
      return 8;
    case PCH_H:
      return 14;
    default:
      return 0;
  }
}

/**
  Get Pch Maximum Usb2 Port Number of XHCI Controller

  @retval Pch Maximum Usb2 Port Number of XHCI Controller
**/
UINT8
GetPchXhciMaxUsb2PortNum (
  VOID
  )
{
  switch (PchSeries ()) {
    case PCH_LP:
      return 12;
    case PCH_N:
      return 10;
    case PCH_H:
      return 16;
    default:
      return 0;
  }
}

/**
  Get Pch Maximum Usb3 Port Number of XHCI Controller

  @retval Pch Maximum Usb3 Port Number of XHCI Controller
**/
UINT8
GetPchXhciMaxUsb3PortNum (
  VOID
  )
{
  switch (PchSeries ()) {
    case PCH_LP:
      return 6;
    case PCH_N:
      return 6;
    case PCH_H:
      return 10;
    default:
      return 0;
  }
}

#ifndef MRC_MINIBIOS_BUILD
/**
  Check if given Audio Interface is supported

  @param[in] AudioLinkType  Link type support to be checked

  @retval    TRUE           Link supported
  @retval    FALSE          Link not supported
**/
BOOLEAN
IsAudioInterfaceSupported (
  IN PCH_HDAUDIO_LINK_TYPE AudioLinkType
  )
{

  //
  // Interfaces support per PCH Generation/Series:
  // 1. HDA Link (SDI0/SDI1) - ICP-LP/H/N
  // 2. Display Audio Link (SDI2) - ICP-LP/H/N
  // 3. SSP[0-2] - ICP-LP/H/N
  //    SSP[3-5] - ICP-LP
  // 4. SNDW[1] - ICP-LP/H/N
  //    SNDW[2-4] - ICP-LP/H
  //
  switch (AudioLinkType) {
    case PchHdaLink:
    case PchHdaIDispLink:
      return TRUE;
    case PchHdaDmic0:
    case PchHdaDmic1:
      return TRUE;
    case PchHdaSsp0:
    case PchHdaSsp1:
    case PchHdaSsp2:
      return TRUE;
    case PchHdaSsp3:
    case PchHdaSsp4:
    case PchHdaSsp5:
      return IsPchLp ();
    case PchHdaSndw1:
      return TRUE;
    case PchHdaSndw2:
    case PchHdaSndw3:
    case PchHdaSndw4:
      return !IsPchN ();
    default:
      return FALSE;
  }
}

/**
  Check if given Display Audio Link T-Mode is supported

  @param[in] Tmode          T-mode support to be checked

  @retval    TRUE           T-mode supported
  @retval    FALSE          T-mode not supported
**/
BOOLEAN
IsAudioIDispTmodeSupported (
  IN PCH_HDAUDIO_IDISP_TMODE Tmode
  )
{
  //
  // iDisplay Audio Link T-mode support per PCH Generation/Series:
  // 1. 2T  - ICP-LP/H/N
  // 2. 4T  - ICP-LP (default), ICP-H, ICP-N
  // 3. 8T  - ICP-H, ICP-N (default)
  // 4. 16T - ICP-H, ICP-N (not-POR)
  //
  switch (Tmode) {
    case PchHdaIDispMode1T:
      return FALSE;
    case PchHdaIDispMode2T:
    case PchHdaIDispMode4T:
      return TRUE;
    case PchHdaIDispMode8T:
    case PchHdaIDispMode16T:
      return (IsPchH () || IsPchN ());
    default:
      return FALSE;
  }
}
#endif MRC_MINIBIOS_BUILD

/**
  Gets the maximum number of UFS controller supported by this chipset.

  @return Number of supported UFS controllers
**/
UINT8
PchGetMaxUfsNum (
  VOID
  )
{
  if (IsPchLp () || IsPchN ()) {
    return 1;
  } else {
    return 0;
  }
}

/**
  Check if this chipset supports eMMC controller

  @retval BOOLEAN  TRUE if supported, FALSE otherwise
**/
BOOLEAN
IsPchEmmcSupported (
  VOID
  )
{
  if (IsPchLp ()) {
    return TRUE;
  }

  return FALSE;
}

/**
  Check if this chipset supports SD controller

  @retval BOOLEAN  TRUE if supported, FALSE otherwise
**/
BOOLEAN
IsPchSdCardSupported (
  VOID
  )
{
  return TRUE;
}

/**
  Check if this chipset supports UFS controller

  @retval BOOLEAN  TRUE if supported, FALSE otherwise
**/
BOOLEAN
IsPchUfsSupported (
  VOID
  )
{
  if (IsPchLp () || IsPchN ()) {
    return TRUE;
  }

  return FALSE;
}

/**
  Check if link between PCH and CPU is an P-DMI

  @retval    TRUE           P-DMI link
  @retval    FALSE          Not an P-DMI link
**/
BOOLEAN
IsPchWithPdmi (
  VOID
  )
{
  return IsPchH ();
}

/**
  Check if link between PCH and CPU is an OP-DMI

  @retval    TRUE           OP-DMI link
  @retval    FALSE          Not an OP-DMI link
**/
BOOLEAN
IsPchWithOpdmi (
  VOID
  )
{
  return !IsPchH ();
}

/**
  Check if link between PCH and CPU is an F-DMI

  @retval    TRUE           F-DMI link
  @retval    FALSE          Not an F-DMI link
**/
BOOLEAN
IsPchWithFdmi (
  VOID
  )
{
  return FALSE;
}

/**
  Return Pch Series

  @retval PCH_SERIES                Pch Series
**/
PCH_SERIES
PchSeries (
  VOID
  )
{
  return MrcGetPchSeries ();
}

/**
  Get Pch Maximum Serial IO controllers number

  @retval Pch Maximum Serial IO controllers number
**/
UINT8
GetPchMaxSerialIoControllersNum (
  VOID
  )
{
  return 12;
}

/**
  Get Pch Maximum Serial IO SPI controllers number

  @retval Pch Maximum Serial IO SPI controllers number
**/
UINT8
GetPchMaxSerialIoSpiControllersNum (
  VOID
  )
{
  return 3;
}

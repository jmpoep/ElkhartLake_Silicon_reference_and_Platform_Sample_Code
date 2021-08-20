/** @file
  Pch information library for EHL.

  All function in this library is available for PEI, DXE, and SMM,
  But do not support UEFI RUNTIME environment call.

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

#include <Uefi/UefiBaseType.h>
#include <Library/PchInfoLib.h>
#include <Register/PchRegsLpcEhl.h>
#include "PchInfoLibPrivate.h"
#include <Library/PmcPrivateLib.h>
#include <Library/PrintLib.h>
#include <Register/PchRegsLpc.h>
#include <Register/PchRegsSciEhl.h>
#include <Register/PchRegs.h>
#include <Library/PciSegmentLib.h>
#include <Library/BaseLib.h>

#define PCH_A0             0x00

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

    case V_LPC_CFG_DID_EHL:
      return PCH_LP;

    default:
      return PCH_UNKNOWN_SERIES;
  }
}

/**
  Determine Pch Stepping based on Revision ID

  @param[in] RevId            Pch Revision Id

  @retval PCH_STEPPING        Pch Stepping
**/
PCH_STEPPING
PchSteppingFromRevId (
  IN UINT8 RevId
  )
{
  PCH_STEPPING PchStepping;

  switch (RevId) {
    case PCH_A0:
      PchStepping = PCH_A0;
      break;
    default:
      PchStepping = RevId;
  }
  return PchStepping;
}

/**
  Print Pch Stepping String

  @param[out] Buffer         Output buffer of string
  @param[in]  BufferSize     Buffer Size
  @param[in]  PchStep        Pch Stepping Type

  @retval VOID
**/
VOID
PchPrintSteppingStr (
  OUT CHAR8        *Buffer,
  IN  UINT32       BufferSize,
  IN  PCH_STEPPING PchStep
  )
{
  AsciiSPrint (Buffer, BufferSize, "%c%c", 'A' + (PchStep >> 4), '0' + (PchStep & 0xF));
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
  return EHL_PCH;
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
  return FALSE;
}

/**
  Get RST mode supported by the silicon

  @retval RST_MODE    RST mode supported by silicon
**/
RST_MODE
PchGetSupportedRstMode (
  VOID
  )
{
  return RstUnsupported;
}

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
  return "EHL PCH";
}

GLOBAL_REMOVE_IF_UNREFERENCED
struct PCH_SKU_STRING mSkuStrs[] = {
  //
  // EHL PCH Mobile LPC Device IDs
  //
  {V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_0,   "MCC SKU 0"},
  {V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_1,   "Super SKU (SSKU)"},
  {V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_2,   "Premium"},
  {V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_3,   "Base/Mainstream"},
  {V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_4,   "MCC SKU 4"},
  {V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_5,   "MCC SKU 5"},
  {V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_6,   "Super SKU (SSKU)"},
  {V_EHL_PCH_LPC_CFG_DEVICE_ID_MB_7,   "Premium"},
  {0xFFFF, NULL}
};

/**
  Get Pch Maximum Pcie Clock Number

  @retval Pch Maximum Pcie Clock Number
**/
UINT8
GetPchMaxPcieClockNum (
  VOID
  )
{
  return 6;
}

/**
  Get Pch Maximum Type C Port Number

  @retval Pch Maximum Type C Port Number
**/
UINT8
GetPchMaxTypeCPortNum (
  VOID
  )
{
  return 1;
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
  return FALSE;
}

/**
  Check whether integrated TSN is supported by PCH Series.

  @retval TRUE                    TSN is supported in current PCH
  @retval FALSE                   TSN is not supported on current PCH
**/
BOOLEAN
PchIsTsnSupported (
  VOID
  )
{
  return TRUE;
}

/*
  Get the number of TSN GBE ports.

  @retval The total number of TSN GBE ports
**/
UINT8
GetNumTsnPorts (
  VOID
  )
{
  return 3;
}

/**
  Check whether PSE is supported by PCH Series.

  @retval TRUE                    PSE is supported in current PCH
  @retval FALSE                   PSE is not supported on current PCH
**/
BOOLEAN
PchIsPseSupported (
  VOID
  )
{
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
  return FALSE;
}

/**
  Check whether Sycamore Island (SCI) is supported by PCH Series.

  @retval TRUE                    SCI is supported in current PCH
  @retval FALSE                   SCI is not supported on current PCH
**/
BOOLEAN
PchIsSciSupported (
  VOID
  )
{
  UINT64  SciAddress;
  SciAddress = PCI_SEGMENT_LIB_ADDRESS (
                     DEFAULT_PCI_SEGMENT_NUMBER_PCH,
                     DEFAULT_PCI_BUS_NUMBER_PCH,
                     PCI_DEVICE_NUMBER_PCH_SCI,
                     PCI_FUNCTION_NUMBER_PCH_SCI,
                     R_SCI_CFG_DEVICE_ID
                     );
  if (PciSegmentRead16 (SciAddress) != 0xFFFF) {
    return TRUE;
  } else {
    return FALSE;
  }
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
  return 7;
}

/**
  Get Pch Maximum MultiVC Root Port Number

  @retval Pch Maximum MultiVC Root Port Number
**/
UINT8
GetPchMaxMultiVCPciePortNum (
  VOID
  )
{
  return 3;
}

/**
  Get Pch Maximum Hda Dmic Link

  @retval Pch Maximum Hda Dmic Link
**/
UINT8
GetPchHdaMaxDmicLinkNum (
  VOID
  )
{
  return 2;
}

/**
  Get Pch Maximum Hda Sdi

  @retval Pch Maximum Hda Sdi
**/
UINT8
GetPchHdaMaxSdiNum (
  VOID
  )
{
  return 2;
}

/**
  Get Pch Maximum Hda Sndw Link

  @retval Pch Maximum Hda Sndw Link
**/
UINT8
GetPchHdaMaxSndwLinkNum (
  VOID
  )
{
  return 4;
}

/**
  Get Pch Maximum Hda Ssp Link

  @retval Pch Maximum Hda Ssp Link
**/
UINT8
GetPchHdaMaxSspLinkNum (
  VOID
  )
{
  return 6;
}

/**
  Check if given Audio Interface is supported

  @param[in] AudioLinkType   Link type support to be checked
  @param[in] AudioLinkIndex  Link number

  @retval    TRUE           Link supported
  @retval    FALSE          Link not supported
**/
BOOLEAN
IsAudioInterfaceSupported (
  IN HDAUDIO_LINK_TYPE     AudioLinkType,
  IN UINT32                AudioLinkIndex
  )
{
  //
  // Interfaces supported:
  // 1. HDA Link (SDI0/SDI1)
  // 2. Display Audio Link (SDI2)
  // 3. SSP[0-5]
  // 4. SNDW[1-4]
  //
  switch (AudioLinkType) {
    case HdaLink:
    case HdaIDispLink:
      return TRUE;
    case HdaDmic:
      if (AudioLinkIndex < 2) {
        return TRUE;
      } else {
        return FALSE;
      }
    case HdaSsp:
      if (AudioLinkIndex < 3) {
        return TRUE;
      } else if (AudioLinkIndex < 6) {
        return IsPchLp ();
      } else {
        return FALSE;
      }
    case HdaSndw:
      if (AudioLinkIndex < 1) {
        return TRUE;
      } else if (AudioLinkIndex < 4) {
        return TRUE;
      } else {
        return FALSE;
      }
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
  IN HDAUDIO_IDISP_TMODE Tmode
  )
{
  //
  // iDisplay Audio Link T-mode support per PCH Generation/Series:
  // 1. 2T  - EHL-LP/H/N
  // 2. 4T  - EHL-LP (default), EHL-H, EHL-N
  // 3. 8T  - EHL-H, EHL-N (default)
  // 4. 16T - EHL-H, EHL-N (not-POR)
  //
  switch (Tmode) {
    case HdaIDispMode1T:
      return FALSE;
    case HdaIDispMode2T:
    case HdaIDispMode4T:
    case HdaIDispMode8T:
      return TRUE;

    case HdaIDispMode16T:
      return (IsPchH ());
    default:
      return FALSE;
  }
}

/**
Get Pch Usb2 Maximum Physical Port Number

@retval Pch Usb2 Maximum Physical Port Number
**/
UINT8
GetPchUsb2MaxPhysicalPortNum(
  VOID
  )
{
  return 10;
}

/**
Get Pch Maximum Usb2 Port Number of XHCI Controller

@retval Pch Maximum Usb2 Port Number of XHCI Controller
**/
UINT8
GetPchXhciMaxUsb2PortNum(
  VOID
  )
{
  return 12;
}

/**
Get Pch Maximum Usb3 Port Number of XHCI Controller

@retval Pch Maximum Usb3 Port Number of XHCI Controller
**/
UINT8
GetPchXhciMaxUsb3PortNum(
  VOID
  )
{
  return 4;
}

/**
  Gets the maximum number of UFS controller supported by this chipset.

  @return Number of supported UFS controllers
**/
UINT8
PchGetMaxUfsNum (
  VOID
  )
{
  return 2;
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
  return TRUE;
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
  return TRUE;
}

/**
  Check if this chipset supports THC controller

  @retval BOOLEAN  TRUE if supported, FALSE otherwise
**/
BOOLEAN
IsPchThcSupported (
  VOID
  )
{
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
  return FALSE;
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
  return TRUE;
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
  Get Pch Maximum ISH UART Controller number

  @retval Pch Maximum ISH UART controllers number
**/
UINT8
GetPchMaxIshUartControllersNum (
  VOID
  )
{
  return 0;
}

/**
  Get Pch Maximum ISH I2C Controller number

  @retval Pch Maximum ISH I2C controllers number
**/
UINT8
GetPchMaxIshI2cControllersNum (
  VOID
  )
{
  return 0;
}

/**
  Get Pch Maximum ISH I3C Controller number

  @retval Pch Maximum ISH I3C controllers number
**/
UINT8
GetPchMaxIshI3cControllersNum (
  VOID
  )
{
  return 0;
}

/**
  Get Pch Maximum ISH SPI Controller number

  @retval Pch Maximum ISH SPI controllers number
**/
UINT8
GetPchMaxIshSpiControllersNum (
  VOID
  )
{
  return 0;
}

/**
  Get Pch Maximum ISH SPI Controller Cs pins number

  @retval Pch Maximum ISH SPI controller Cs pins number
**/
UINT8
GetPchMaxIshSpiControllerCsPinsNum (
  VOID
  )
{
  return 0;
}

/**
  Get Pch Maximum ISH GP number

  @retval Pch Maximum ISH GP number
**/
UINT8
GetPchMaxIshGpNum (
  VOID
  )
{
  return 0;
}

/**
  Get Pch Maximum PSE I2S Controller number

  @retval Pch Maximum PSE I2S Controller number
**/
UINT8
GetPchMaxPseI2sControllersNum (
  VOID
)
{
  return 2;
}

/**
  Get Pch Maximum PSE UART Controller number

  @retval Pch Maximum PSE UART Controller number
**/
UINT8
GetPchMaxPseUartControllersNum (
  VOID
)
{
  return 6;
}

/**
  Get Pch Maximum PSE HSUART Controller number

  @retval Pch Maximum PSE HSUART Controller number
**/
UINT8
GetPchMaxPseHsuartControllersNum (
  VOID
)
{
  return 4;
}

/**
  Get Pch Maximum PSE QEP Controller number

  @retval Pch Maximum PSE QEP Controller number
**/
UINT8
GetPchMaxPseQepControllersNum (
  VOID
)
{
  return 4;
}

/**
  Get Pch Maximum PSE I2C Controller number

  @retval Pch Maximum PSE I2C Controller number
**/
UINT8
GetPchMaxPseI2cControllersNum (
  VOID
)
{
  return 8;
}

/**
  Get Pch Maximum PSE SPI Controller number

  @retval Pch Maximum PSE SPI Controller number
**/
UINT8
GetPchMaxPseSpiControllersNum (
  VOID
)
{
  return 4;
}

/**
  Get Pch Maximum PSE DMA Controller number

  @retval Pch Maximum PSE DMA Controller number
**/
UINT8
GetPchMaxPseDmaControllersNum (
  VOID
)
{
  return 3;
}

/**
  Get Pch Maximum PSE GBE Controller number

  @retval Pch Maximum PSE GBE Controller number
**/
UINT8
GetPchMaxPseGbeControllersNum (
  VOID
)
{
  return 2;
}

/**
  Get Pch Maximum PSE SPI Controller Cs pins number

  @retval Pch Maximum PSE SPI controller Cs pins number
**/
UINT8
GetPchMaxPseSpiControllerCsPinsNum (
  VOID
)
{
  return 1;
}

/**
  Get Pch Maximum PSE CAN Controller number

  @retval Pch Maximum PSE CAN Controller number
**/
UINT8
GetPchMaxPseCanControllersNum (
  VOID
)
{
  return 2;
}

/**
  Get Pch Maximum PSE Timed GPIO Controller number

  @retval Pch Maximum PSE Timed GPIO Controller number
**/
UINT8
GetPchMaxPseTimedGpioControllersNum (
  VOID
)
{
  return 2;
}

/**
  Get Pch Maximum Total PSE Timed GPIO Pins number

  @retval Pch Maximum Total PSE Timed GPIO Controller Pins number
**/
UINT8
GetPchMaxPseTimdedGpioPinsNum (
  VOID
)
{
  return 60;
}

/**
  Get Pch Maximum PSE TRACE Controller number

  @retval Pch Maximum PSE TRACE Controller number
**/
UINT8
GetPchMaxPseTraceControllersNum (
  VOID
)
{
  return 4;
}

/**
  Get Pch Maximum PSE PWM Controller Pin number

  @retval Pch Maximum PSE PWM Controller Pin number
**/
UINT8
GetPchMaxPsePwmControllerPinsNum (
  VOID
)
{
  return 16;
}

/**
  Get Pch Maximum PSE ADC Controller PIN number

  @retval Pch Maximum PSE ADC Controller PIN number
**/
UINT8
GetPchMaxPseAdcControllerPinsNum (
  VOID
)
{
  return 16;
}

/**
  Get Pch Maximum Pse IO controllers number

  @retval Pch Maximum Pse IO controllers number
**/
UINT8
GetPchMaxPseIoControllersNum (
  VOID
  )
{
  return 36;
}

/**
  Get Pch Maximum Serial IO I2C controllers number

  @retval Pch Maximum Serial IO I2C controllers number
**/
UINT8
GetPchMaxSerialIoI2cControllersNum (
  VOID
  )
{
  return 8;
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

/**
  Get Pch Maximum Serial IO UART controllers number

  @retval Pch Maximum Serial IO UART controllers number
**/
UINT8
GetPchMaxSerialIoUartControllersNum (
  VOID
  )
{
  return 3;
}

/**
  Get Pch Maximum Serial IO SPI Chip Selects count

  @retval Pch Maximum Serial IO SPI Chip Selects number
**/
UINT8
GetPchMaxSerialIoSpiChipSelectsNum (
  VOID
  )
{
  return 2;
}

/**
  Get Pch Maximum ME Applet count

  @retval Pch Maximum ME Applet number
**/
UINT8
GetPchMaxMeAppletCount (
  VOID
  )
{
  return 31;
}

/**
  Get Pch Maximum ME Session count

  @retval Pch Maximum ME Sesion number
**/
UINT8
GetPchMaxMeSessionCount (
  VOID
  )
{
  return 16;
}

/**
  Get Pch Maximum THC count

  @retval Pch Maximum THC count number
**/
UINT8
GetPchMaxThcCount (
  VOID
  )
{
  return 2;
}

/**
  Returns a frequency of the sosc_clk signal.
  All SATA controllers on the system are assumed to
  work on the same sosc_clk frequency.

  @retval Frequency of the sosc_clk signal.
**/
SATA_SOSC_CLK_FREQ
GetSataSoscClkFreq (
  VOID
  )
{
  return SataSosc100Mhz;
}

/**
  Check if SATA support should be awake after function disable

  @retval    TRUE
  @retval    FALSE
**/
BOOLEAN
IsSataSupportWakeAfterFunctionDisable (
  VOID
  )
{
  return TRUE;
}

/**
  Returns USB2 PHY Reference Clock frequency value used by PCH
  This defines what electrical tuning parameters shall be used
  during USB2 PHY initialization programming

  @retval Frequency reference clock for USB2 PHY
**/
USB2_PHY_REF_FREQ
GetUsb2PhyRefFreq (
  VOID
  )
{
  return FREQ_19_2;
}

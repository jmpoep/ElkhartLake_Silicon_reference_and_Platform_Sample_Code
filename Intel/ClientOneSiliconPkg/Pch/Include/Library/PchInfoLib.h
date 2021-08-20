/** @file
  Header file for PchInfoLib.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2019 Intel Corporation.

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
#ifndef _PCH_INFO_LIB_H_
#define _PCH_INFO_LIB_H_

#include <Hda.h>
#include <Uefi/UefiBaseType.h>

typedef UINT8 PCH_STEPPING;

#define PCH_A0                0x00
#define PCH_A1                0x01
#define PCH_B0                0x10
#define PCH_B1                0x11
#define PCH_C0                0x20
#define PCH_C1                0x21
#define PCH_D0                0x30
#define PCH_D1                0x31
#define PCH_Z0                0xF0
#define PCH_Z1                0xF1
#define PCH_STEPPING_MAX      0xFF

typedef UINT8 PCH_SERIES;
#define PCH_H                   1
#define PCH_LP                  2
#define PCH_N                   3
#define PCH_SERVER              0x80
#define PCH_UNKNOWN_SERIES      0xFF

typedef UINT8 PCH_GENERATION;
#define CNL_PCH                 3
#define ICL_PCH                 4
#define TGL_PCH                 5
#define JSL_PCH                 6
#define EHL_PCH                 7
#define CDF_PCH                 0x80
#define EBG_PCH                 0x81
#define PCH_UNKNOWN_GENERATION  0xFF

typedef enum {
  RstUnsupported  = 0,
  RstPremium,
  RstOptane,
  RstMaxMode
} RST_MODE;

/**
  Return LPC Device Id

  @retval PCH_LPC_DEVICE_ID         PCH Lpc Device ID
**/
UINT16
PchGetLpcDid (
  VOID
  );

/**
  Return Pch stepping type

  @retval PCH_STEPPING            Pch stepping type
**/
PCH_STEPPING
PchStepping (
  VOID
  );

/**
  Determine if PCH is supported

  @retval TRUE                    PCH is supported
  @retval FALSE                   PCH is not supported
**/
BOOLEAN
IsPchSupported (
  VOID
  );

/**
  Return Pch Series

  @retval PCH_SERIES                Pch Series
**/
PCH_SERIES
PchSeries (
  VOID
  );

/**
  Check if this is PCH LP series

  @retval TRUE                It's PCH LP series
  @retval FALSE               It's not PCH LP series
**/
BOOLEAN
IsPchLp (
  VOID
  );

/**
  Check if this is PCH H series

  @retval TRUE                It's PCH H series
  @retval FALSE               It's not PCH H series
**/
BOOLEAN
IsPchH (
  VOID
  );

/**
  Check if this is PCH N series

  @retval TRUE                It's PCH N series
  @retval FALSE               It's not PCH N series
**/
BOOLEAN
IsPchN (
  VOID
  );

/**
  Check if this is Server PCH

  @retval TRUE                It's a Server PCH
  @retval FALSE               It's not a Server PCH
**/
BOOLEAN
IsPchServer (
  VOID
  );

/**
  Return Pch Generation

  @retval PCH_GENERATION            Pch Generation
**/
PCH_GENERATION
PchGeneration (
  VOID
  );

/**
  Check if this is CDF PCH generation

  @retval TRUE                It's CDF PCH
  @retval FALSE               It's not CDF PCH
**/
BOOLEAN
IsCdfPch (
  VOID
  );

/**
  Check if this is EBG PCH generation

  @retval TRUE                It's EBG PCH
  @retval FALSE               It's not EBG PCH
**/
BOOLEAN
IsEbgPch (
  VOID
  );

/**
  Check if this is CNL PCH generation

  @retval TRUE                It's CNL PCH
  @retval FALSE               It's not CNL PCH
**/
BOOLEAN
IsCnlPch (
  VOID
  );

/**
  Check if this is ICL PCH generation

  @retval TRUE                It's ICL PCH
  @retval FALSE               It's not ICL PCH
**/
BOOLEAN
IsIclPch (
  VOID
  );

/**
  Check if this is TGL PCH generation

  @retval TRUE                It's TGL PCH
  @retval FALSE               It's not TGL PCH
**/
BOOLEAN
IsTglPch (
  VOID
  );

/**
  Check if this is JSL PCH generation

  @retval TRUE                It's JSL PCH
  @retval FALSE               It's not JSL PCH
**/
BOOLEAN
IsJslPch (
  VOID
  );

/**
  Check if this is Server SKU

  @retval TRUE                It's PCH Server SKU
  @retval FALSE               It's not PCH Server SKU
**/
BOOLEAN
IsPchServerSku (
  VOID
  );

/**
  Get Pch Maximum Pcie Root Port Number

  @retval PcieMaxRootPort         Pch Maximum Pcie Root Port Number
**/
UINT8
GetPchMaxPciePortNum (
  VOID
  );

/**
  Get Pch Maximum Pcie Controller Number

  @retval Pch Maximum Pcie Controller Number
**/
UINT8
GetPchMaxPcieControllerNum (
  VOID
  );

/**
  Get Pch Maximum MultiVC PCIe Root Port Number

  @retval Pch Maximum MultiVC PCIe Root Port Number
**/
UINT8
GetPchMaxMultiVCPciePortNum (
  VOID
  );

/**
  Get Pch Maximum MultiVC PCIe Controller Number

  @retval Maximum MultiVC Pcie Controller Number
**/
UINT8
GetPchMaxMultiVCPcieControllerNum (
  VOID
  );

/**
  Return the Controller index base on Root Port Index. This is to take care of situation where the Root Port Number is not symetrical across controller

  @param[in] RpIndex Root Port Number (0-based)

  @return  Controller Index
**/
UINT8
GetControllerIndex (
  IN  UINT32                   RpIndex
  );

/**
  Obtain the Root Port Index within its own Controller. This is to take care of situation where the Root Port Number is not symetrical across controller

  @param[in] RpIndex Root Port Number (0-based)

  @return  Root Port Index within its Controller
**/
UINT8
GetControllerRpIndex (
  IN  UINT32                   RpIndex
  );

/**
  Obtain the first Root Port Index (0 based) of given Controller. This is to take care of situation where the Root Port Number is not symetrical across controller

  @param[in] ControllerIndex Pcie Controller Number (0-based)

  @return  first Root Port Index of given Controller
**/
UINT8
GetControllerFirstRpIndex (
  IN  UINT32                   ControllerIndex
  );

/**
  Obtain the Maximum Root Port of given Controller.

  @param[in] ControllerIndex Pcie Controller Number (0-based)

  @return  Number of Root Ports of given Controller
**/
UINT8
GetControllerMaxRp (
  IN  UINT8                   ControllerIndex
  );

/**
  Check if a given Root Port is Multi VC

  @param[in] RpIndex (0-based)

  @return  TRUE if it is Multi VC
**/
BOOLEAN
IsRpMultiVC (
  IN  UINT32                   RpIndex
  );

/**
  Check if a given PCIe Controller is Multi VC

  @param[in] CtrlIndex (0-based)

  @return  TRUE if it is from Multi VC
**/
BOOLEAN
IsCtrlMultiVC (
  IN  UINT32                   CtrlIndex
  );

/**
  Get Pch Maximum Pcie Clock Number

  @retval Pch Maximum Pcie Clock Number
**/
UINT8
GetPchMaxPcieClockNum (
  VOID
  );

/**
  Get Pch Usb2 Maximum Physical Port Number

  @retval Pch Usb2 Maximum Physical Port Number
**/
UINT8
GetPchUsb2MaxPhysicalPortNum (
  VOID
  );

/**
  Get Pch Maximum Usb2 Port Number of XHCI Controller

  @retval Pch Maximum Usb2 Port Number of XHCI Controller
**/
UINT8
GetPchXhciMaxUsb2PortNum (
  VOID
  );

/**
  Get Pch Usb3 Maximum Physical Port Number

  @retval Pch Usb3 Maximum Physical Port Number
**/
UINT8
GetPchUsb3MaxPhysicalPortNum (
  VOID
  );

/**
  Get Pch Maximum Usb3 Port Number of XHCI Controller

  @retval Pch Maximum Usb3 Port Number of XHCI Controller
**/
UINT8
GetPchXhciMaxUsb3PortNum (
  VOID
  );

/**
  Get Pch Maximum Pse IO controllers number

  @retval Pch Maximum Pse IO controllers number
**/
UINT8
GetPchMaxPseIoControllersNum (
  VOID
  );
/**
  Get Pch Maximum Serial IO I2C controllers number

  @retval Pch Maximum Serial IO I2C controllers number
**/
UINT8
GetPchMaxSerialIoI2cControllersNum (
  VOID
  );

/**
  Get Pch Maximum Serial IO SPI controllers number

  @retval Pch Maximum Serial IO SPI controllers number
**/
UINT8
GetPchMaxSerialIoSpiControllersNum (
  VOID
  );

/**
  Get Pch Maximum Serial IO UART controllers number

  @retval Pch Maximum Serial IO UART controllers number
**/
UINT8
GetPchMaxSerialIoUartControllersNum (
  VOID
  );

/**
  Get Pch Maximum Serial IO SPI Chip Selects count

  @retval Pch Maximum Serial IO SPI Chip Selects nu,ber
**/
UINT8
GetPchMaxSerialIoSpiChipSelectsNum (
  VOID
  );

/**
  Get Pch Maximum ISH UART Controller number

  @retval Pch Maximum ISH UART controllers number
**/
UINT8
GetPchMaxIshUartControllersNum (
  VOID
  );

/**
  Get Pch Maximum ISH I2C Controller number

  @retval Pch Maximum ISH I2C controllers number
**/
UINT8
GetPchMaxIshI2cControllersNum (
  VOID
  );

/**
  Get Pch Maximum ISH I3C Controller number

  @retval Pch Maximum ISH I3C controllers number
**/
UINT8
GetPchMaxIshI3cControllersNum (
  VOID
  );

/**
  Get Pch Maximum ISH SPI Controller number

  @retval Pch Maximum ISH SPI controllers number
**/
UINT8
GetPchMaxIshSpiControllersNum (
  VOID
  );

/**
  Get Pch Maximum ISH SPI Controller Cs pins number

  @retval Pch Maximum ISH SPI controller Cs pins number
**/
UINT8
GetPchMaxIshSpiControllerCsPinsNum (
  VOID
  );

/**
  Get Pch Maximum ISH GP number

  @retval Pch Maximum ISH GP number
**/
UINT8
GetPchMaxIshGpNum (
  VOID
  );

/**
  Get Pch Maximum PSE I2S Controller number

  @retval Pch Maximum PSE I2S Controller number
**/
UINT8
GetPchMaxPseI2sControllersNum (
  VOID
  );

/**
  Get Pch Maximum PSE PWM Controller Pin number

  @retval Pch Maximum PSE PWM Controller Pin number
**/
UINT8
GetPchMaxPsePwmControllerPinsNum (
  VOID
  );

/**
  Get Pch Maximum PSE UART Controller number

  @retval Pch Maximum PSE UART Controller number
**/
UINT8
GetPchMaxPseUartControllersNum (
  VOID
  );

/**
  Get Pch Maximum PSE HSUART Controller number

  @retval Pch Maximum PSE HSUART Controller number
**/
UINT8
GetPchMaxPseHsuartControllersNum (
  VOID
  );

/**
  Get Pch Maximum PSE QEP Controller number

  @retval Pch Maximum PSE QEP Controller number
**/
UINT8
GetPchMaxPseQepControllersNum (
  VOID
  );

/**
  Get Pch Maximum PSE I2C Controller number

  @retval Pch Maximum PSE I2C Controller number
**/
UINT8
GetPchMaxPseI2cControllersNum (
  VOID
  );

/**
  Get Pch Maximum PSE SPI Controller number

  @retval Pch Maximum PSE SPI Controller number
**/
UINT8
GetPchMaxPseSpiControllersNum (
  VOID
  );

/**
  Get Pch Maximum PSE DMA Controller number

  @retval Pch Maximum PSE DMA Controller number
**/
UINT8
GetPchMaxPseDmaControllersNum (
  VOID
  );

/**
  Get Pch Maximum PSE GBE Controller number

  @retval Pch Maximum PSE GBE Controller number
**/
UINT8
GetPchMaxPseGbeControllersNum (
  VOID
  );

/**
  Get Pch Maximum PSE SPI Controller Cs pins number

  @retval Pch Maximum PSE SPI controller Cs pins number
**/
UINT8
GetPchMaxPseSpiControllerCsPinsNum (
  VOID
  );

/**
  Get Pch Maximum PSE ADC Controller PIN number

  @retval Pch Maximum PSE ADC Controller PIN number
**/
UINT8
GetPchMaxPseAdcControllerPinsNum (
  VOID
  );

/**
  Get Pch Maximum PSE CAN Controller number

  @retval Pch Maximum PSE CAN Controller number
**/
UINT8
GetPchMaxPseCanControllersNum (
  VOID
  );

/**
  Get Pch Maximum PSE TRACE Controller number

  @retval Pch Maximum PSE TRACE Controller number
**/
UINT8
GetPchMaxPseTraceControllersNum (
  VOID
  );

/**
  Get Pch Maximum PSE Timed GPIO Controller number

  @retval Pch Maximum PSE Timed GPIO Controller number
**/
UINT8
GetPchMaxPseTimedGpioControllersNum (
  VOID
  );

/**
  Get Pch Maximum Total PSE Timed GPIO Pins number

  @retval Pch Maximum Total PSE Timed GPIO Controller Pins number
**/
UINT8
GetPchMaxPseTimdedGpioPinsNum (
  VOID
  );

/**
  Get Pch Maximum ME Applet count

  @retval Pch Maximum ME Applet number
**/
UINT8
GetPchMaxMeAppletCount (
  VOID
  );

/**
Get Pch Maximum ME Session count

@retval Pch Maximum ME Sesion number
**/
UINT8
GetPchMaxMeSessionCount(
  VOID
);

/**
  Get Pch Maximum Type C Port Number

  @retval Pch Maximum Type C Port Number
**/
UINT8
GetPchMaxTypeCPortNum (
  VOID
  );

#define PCH_STEPPING_STR_LENGTH_MAX 3

/**
  Get PCH stepping ASCII string.
  Function determines major and minor stepping versions and writes them into a buffer.
  The return string is zero terminated

  @param [out]     Buffer               Output buffer of string
  @param [in]      BufferSize           Buffer size.
                                        Must not be less then PCH_STEPPING_STR_LENGTH_MAX

  @retval EFI_SUCCESS                   String copied successfully
  @retval EFI_INVALID_PARAMETER         The stepping is not supported, or parameters are NULL
  @retval EFI_BUFFER_TOO_SMALL          Input buffer size is too small
**/
EFI_STATUS
PchGetSteppingStr (
  OUT    CHAR8                          *Buffer,
  IN     UINT32                         BufferSize
  );

/**
  Get PCH series ASCII string.
  The return string is zero terminated.

  @retval Static ASCII string of PCH Series
**/
CHAR8*
PchGetSeriesStr (
  );

/**
  Get PCH Sku ASCII string
  The return string is zero terminated.

  @retval Static ASCII string of PCH Sku
**/
CHAR8*
PchGetSkuStr (
  VOID
  );

/**
  Check if this chipset supports eMMC controller

  @retval BOOLEAN  TRUE if supported, FALSE otherwise
**/
BOOLEAN
IsPchEmmcSupported (
  VOID
  );

/**
  Check if this chipset supports SD controller

  @retval BOOLEAN  TRUE if supported, FALSE otherwise
**/
BOOLEAN
IsPchSdCardSupported (
  VOID
  );

/**
  Check if this chipset supports UFS controller

  @retval BOOLEAN  TRUE if supported, FALSE otherwise
**/
BOOLEAN
IsPchUfsSupported  (
  VOID
  );

/**
  Check if this chipset supports THC controller

  @retval BOOLEAN  TRUE if supported, FALSE otherwise
**/
BOOLEAN
IsPchThcSupported (
  VOID
  );

/**
  Gets the maximum number of UFS controller supported by this chipset.

  @return Number of supported UFS controllers
**/
UINT8
PchGetMaxUfsNum (
  VOID
  );

/**
  Get RST mode supported by the silicon

  @retval RST_MODE    RST mode supported by silicon
**/
RST_MODE
PchGetSupportedRstMode (
  VOID
  );

/**
  Check whether integrated LAN controller is supported.

  @retval TRUE                    GbE is supported in PCH
  @retval FALSE                   GbE is not supported by PCH
**/
BOOLEAN
PchIsGbeSupported (
  VOID
  );

/**
  Check whether integrated TSN is supported.

  @retval TRUE                    TSN is supported in current PCH
  @retval FALSE                   TSN is not supported on current PCH
**/
BOOLEAN
PchIsTsnSupported (
  VOID
  );

/*
  Get the number of TSN GBE ports.

  @retval The total number of TSN GBE ports
**/
UINT8
GetNumTsnPorts (
  VOID
  );

/**
  Check whether PSE is supported.

  @retval TRUE                    PSE is supported in PCH
  @retval FALSE                   PSE is not supported by PCH
**/
BOOLEAN
PchIsPseSupported (
  VOID
  );

/**
  Check whether Sycamore Island (SCI) is supported by PCH Series.

  @retval TRUE                    SCI is supported in current PCH
  @retval FALSE                   SCI is not supported on current PCH
**/
BOOLEAN
PchIsSciSupported (
  VOID
  );

/**
  Check whether ISH is supported.

  @retval TRUE                    ISH is supported in PCH
  @retval FALSE                   ISH is not supported by PCH
**/
BOOLEAN
PchIsIshSupported (
  VOID
  );

/**
  Get Pch Maximum Hda Sndw Link

  @retval Pch Maximum Hda Sndw Link
**/
UINT8
GetPchHdaMaxSndwLinkNum (
  VOID
  );

/**
  Get Pch Maximum Hda Ssp Link

  @retval Pch Maximum Hda Ssp Link
**/
UINT8
GetPchHdaMaxSspLinkNum (
  VOID
  );

/**
  Get Pch Maximum Hda Ssp Link

  @retval Pch Maximum Hda Ssp Link
**/
UINT8
GetPchHdaMaxSdiNum (
  VOID
  );

/**
  Get Pch Maximum Hda Dmic Link

  @retval Pch Maximum Hda Dmic Link
**/
UINT8
GetPchHdaMaxDmicLinkNum (
  VOID
  );

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
  );

/**
  Check if given Display Audio Link T-Mode is supported

  @param[in] Tmode          T-mode support to be checked

  @retval    TRUE           T-mode supported
  @retval    FALSE          T-mode not supported
**/
BOOLEAN
IsAudioIDispTmodeSupported (
  IN HDAUDIO_IDISP_TMODE Tmode
  );

/**
  Check if link between PCH and CPU is an P-DMI

  @retval    TRUE           P-DMI link
  @retval    FALSE          Not an P-DMI link
**/
BOOLEAN
IsPchWithPdmi (
  VOID
  );

/**
  Check if link between PCH and CPU is an OP-DMI

  @retval    TRUE           OP-DMI link
  @retval    FALSE          Not an OP-DMI link
**/
BOOLEAN
IsPchWithOpdmi (
  VOID
  );

/**
  Check if link between PCH and CPU is an F-DMI

  @retval    TRUE           F-DMI link
  @retval    FALSE          Not an F-DMI link
**/
BOOLEAN
IsPchWithFdmi (
  VOID
  );

/**
  Get Pch Maximum THC count

  @retval Pch Maximum THC count number
**/
UINT8
GetPchMaxThcCount (
  VOID
  );

typedef enum {
  SataSosc125Mhz = 0,
  SataSosc120Mhz,
  SataSosc100Mhz,
  SataSosc25Mhz,
  SataSosc19p2Mhz,
  SataSoscUnsupported
} SATA_SOSC_CLK_FREQ;

/**
  Returns a frequency of the sosc_clk signal.
  All SATA controllers on the system are assumed to
  work on the same sosc_clk frequency.

  @retval Frequency of the sosc_clk signal.
**/
SATA_SOSC_CLK_FREQ
GetSataSoscClkFreq (
  VOID
  );

/**
  Check if SATA support should be awake after function disable

  @retval    TRUE
  @retval    FALSE
**/
BOOLEAN
IsSataSupportWakeAfterFunctionDisable (
  VOID
  );

//
// USB2 PHY reference frequencies values (MHz)
//
typedef enum {
  FREQ_19_2 = 0u,
  FREQ_24_0,
  FREQ_96_0,
  FREQ_MAX
} USB2_PHY_REF_FREQ;

/**
  Returns USB2 PHY Reference Clock frequency value used by PCH
  This defines what electrical tuning parameters shall be used
  during USB2 PHY initialization programming

  @retval Frequency reference clock for USB2 PHY
**/
USB2_PHY_REF_FREQ
GetUsb2PhyRefFreq (
  VOID
  );

#endif // _PCH_INFO_LIB_H_

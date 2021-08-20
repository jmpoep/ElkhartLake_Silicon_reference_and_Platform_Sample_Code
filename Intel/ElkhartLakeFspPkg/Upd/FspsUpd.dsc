## @file
#  Platform description.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2017 - 2020 Intel Corporation.
#
#  The source code contained or described herein and all documents related to the
#  source code ("Material") are owned by Intel Corporation or its suppliers or
#  licensors. Title to the Material remains with Intel Corporation or its suppliers
#  and licensors. The Material may contain trade secrets and proprietary and
#  confidential information of Intel Corporation and its suppliers and licensors,
#  and is protected by worldwide copyright and trade secret laws and treaty
#  provisions. No part of the Material may be used, copied, reproduced, modified,
#  published, uploaded, posted, transmitted, distributed, or disclosed in any way
#  without Intel's prior express written permission.
#
#  No license under any patent, copyright, trade secret or other intellectual
#  property right is granted to or conferred upon you by disclosure or delivery
#  of the Materials, either expressly, by implication, inducement, estoppel or
#  otherwise. Any license under such intellectual property rights must be
#  express and approved by Intel in writing.
#
#  Unless otherwise agreed by Intel in writing, you may not remove or alter
#  this notice or any other notice embedded in Materials by Intel or
#  Intel's suppliers or licensors in any way.
#
#  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
#  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
#  the terms of your license agreement with Intel or your vendor. This file may
#  be modified by the user, subject to additional terms of the license agreement.
#
# @par Specification
##

  ################################################################################
  #
  # UPDs consumed in FspSiliconInit Api
  #
  ################################################################################
  # !BSF FIND:{EHLUPD_S}
  # !HDR COMMENT:{FSP_UPD_HEADER:FSP UPD Header}
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:START}
  # FspsUpdSignature: {EHLUPD_S}
  gPlatformFspPkgTokenSpaceGuid.Signature                   | * | 0x08 | 0x535F4450554C4845
  # !BSF NAME:{FspsUpdRevision}  TYPE:{None}
  gPlatformFspPkgTokenSpaceGuid.Revision                    | * | 0x01 | 0x00
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:END}
  gPlatformFspPkgTokenSpaceGuid.Reserved                    | * | 0x17 | {0x00}

  # !HDR COMMENT:{FSP_S_CONFIG:Fsp S Configuration}
  # !HDR EMBED:{FSP_S_CONFIG:FspsConfig:START}
  # !BSF PAGE:{EHL}
  # !BSF NAME:{Logo Pointer}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Points to PEI Display Logo Image}
  gPlatformFspPkgTokenSpaceGuid.LogoPtr                     | * | 0x04 | 0x00000000

  # !BSF NAME:{Logo Size}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Size of PEI Display Logo Image}
  gPlatformFspPkgTokenSpaceGuid.LogoSize                    | * | 0x04 | 0x00000000

  # !BSF NAME:{Blt Buffer Address}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Address of Blt buffer}
  gPlatformFspPkgTokenSpaceGuid.BltBufferAddress            | * | 0x04 | 0x00000000

  # !BSF NAME:{Blt Buffer Size}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Size of Blt Buffer, is equal to PixelWidth * PixelHeight * 4 bytes (the size of EFI_GRAPHICS_OUTPUT_BLT_PIXEL)}
  gPlatformFspPkgTokenSpaceGuid.BltBufferSize               | * | 0x04 | 0x00000000

  # !BSF NAME:{Graphics Configuration Ptr}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Points to VBT}
  gPlatformFspPkgTokenSpaceGuid.GraphicsConfigPtr           | * | 0x04 | 0x00000000

  # !BSF NAME:{Enable Device 4}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable Device 4}
  gPlatformFspPkgTokenSpaceGuid.Device4Enable               | * | 0x01 | 0x00

  # !BSF PAGE:{PCH2}
  # !BSF NAME:{Enable eMMC Controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable eMMC Controller.}
  gPlatformFspPkgTokenSpaceGuid.ScsEmmcEnabled              | * | 0x01 | 0x01

  # !BSF NAME:{Enable eMMC HS400 Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable eMMC HS400 Mode.}
  gPlatformFspPkgTokenSpaceGuid.ScsEmmcHs400Enabled         | * | 0x01 | 0x01

  # !BSF NAME:{Use DLL values from policy} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set if FSP should use HS400 DLL values from policy}
  gPlatformFspPkgTokenSpaceGuid.EmmcUseCustomDlls  | * | 0x01 | 0x0

  # !BSF NAME:{Emmc Tx CMD Delay control register value} TYPE:{EditNum, HEX, (0x0, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Tx CMD Delay Control register definition for help}
  gPlatformFspPkgTokenSpaceGuid.EmmcTxCmdDelayRegValue  | * | 0x04 | 0x0

  # !BSF NAME:{Emmc Tx DATA Delay control 1 register value} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Tx DATA Delay control 1 register definition for help}
  gPlatformFspPkgTokenSpaceGuid.EmmcTxDataDelay1RegValue  | * | 0x04 | 0x0

  # !BSF NAME:{Emmc Tx DATA Delay control 2 register value} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Tx DATA Delay control 2 register definition for help}
  gPlatformFspPkgTokenSpaceGuid.EmmcTxDataDelay2RegValue  | * | 0x04 | 0x0

  # !BSF NAME:{Emmc Rx CMD + DATA Delay control 1 register value} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Rx CMD + DATA Delay control 1 register definition for help}
  gPlatformFspPkgTokenSpaceGuid.EmmcRxCmdDataDelay1RegValue  | * | 0x04 | 0x0

  # !BSF NAME:{Emmc Rx CMD + DATA Delay control 2 register value} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Rx CMD + DATA Delay control 2 register definition for help}
  gPlatformFspPkgTokenSpaceGuid.EmmcRxCmdDataDelay2RegValue  | * | 0x04 | 0x0

  # !BSF NAME:{Emmc Rx Strobe Delay control register value} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Rx Strobe Delay control register definition for help}
  gPlatformFspPkgTokenSpaceGuid.EmmcRxStrobeDelayRegValue  | * | 0x04 | 0x0

  # !BSF NAME:{Enable SdCard Controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SD Card Controller.}
  gPlatformFspPkgTokenSpaceGuid.ScsSdCardEnabled            | * | 0x01 | 0x01

  # !BSF NAME:{SdCard power enable polarity} TYPE:{Combo} OPTION:{0: Active low, 1: Active high}
  # !BSF HELP:{Choose SD_PWREN# polarity}
  gPlatformFspPkgTokenSpaceGuid.SdCardPowerEnableActiveHigh | * | 0x01 | 0x01

  # !BSF NAME:{Use tuned DLL values from policy} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set if FSP should use HS400 DLL values from policy}
  gPlatformFspPkgTokenSpaceGuid.SdCardUseCustomDlls  | * | 0x01 | 0x0

  # !BSF NAME:{SdCard Tx CMD Delay control register value} TYPE:{EditNum, HEX, (0x0, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Tx CMD Delay Control register definition for help}
  gPlatformFspPkgTokenSpaceGuid.SdCardTxCmdDelayRegValue  | * | 0x04 | 0x0

  # !BSF NAME:{SdCard Tx DATA Delay control 1 register value} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Tx DATA Delay control 1 register definition for help}
  gPlatformFspPkgTokenSpaceGuid.SdCardTxDataDelay1RegValue  | * | 0x04 | 0x0

  # !BSF NAME:{SdCard Tx DATA Delay control 2 register value} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Tx DATA Delay control 2 register definition for help}
  gPlatformFspPkgTokenSpaceGuid.SdCardTxDataDelay2RegValue  | * | 0x04 | 0x0

  # !BSF NAME:{SdCard Rx CMD + DATA Delay control 1 register value} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Rx CMD + DATA Delay control 1 register definition for help}
  gPlatformFspPkgTokenSpaceGuid.SdCardRxCmdDataDelay1RegValue  | * | 0x04 | 0x0

  # !BSF NAME:{SdCard Rx CMD + DATA Delay control 2 register value} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Please see Rx CMD + DATA Delay control 2 register definition for help}
  gPlatformFspPkgTokenSpaceGuid.SdCardRxCmdDataDelay2RegValue  | * | 0x04 | 0x0
  # !BSF NAME:{SdCard Power Enable Pin Mux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select Power Enable pin muxing. Refer to GPIO_*_MUXING_SDCARD_PWR_EN* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioPrwEnBPinMux              | * | 0x04 | 0x0

  # !BSF NAME:{SdCard Power Enable Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioPrwEnBPadTermination      | * | 0x01 | 0x0

  # !BSF NAME:{SdCard Command Pin Mux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select Command pin muxing. Refer to GPIO_*_MUXING_SDCARD_CMD* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioCmdPinMux                 | * | 0x04 | 0x0

  # !BSF NAME:{SdCard Command Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioCmdPadTermination         | * | 0x01 | 0x0

  # !BSF NAME:{SdCard Data Pin Mux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select Data pin muxing. Refer to GPIO_*_MUXING_SDCARD_DATAx_* for possible values. One UINT32 for each data pin [0-4]}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioDataPinMux                | * | 0x10 | { 0x0, 0x0, 0x0, 0x0 }

  # !BSF NAME:{SdCard Data Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up. One byte for each data pin [0-4]}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioDataPadTermination        | * | 0x04 | { 0x0, 0x0, 0x0, 0x0 }

  # !BSF NAME:{SdCard Cdb Pin Mux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select Cdb pin muxing. Refer to GPIO_*_MUXING_SDCARD_CDB* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioCdbPinMux                 | * | 0x04 | 0x0

  # !BSF NAME:{SdCard Cdb Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioCdbPadTermination         | * | 0x01 | 0x0

  # !BSF NAME:{SdCard Clock Pin Mux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select Clock pin muxing. Refer to GPIO_*_MUXING_SDCARD_CLK* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioClkPinMux                 | * | 0x04 | 0x0

  # !BSF NAME:{SdCard Clock Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioClkPadTermination         | * | 0x01 | 0x0

  # !BSF NAME:{SdCard Wp PinMux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select Wp pin muxing. Refer to GPIO_*_MUXING_SDCARD_WP* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioWpPinMux                  | * | 0x04 | 0x0

  # !BSF NAME:{SdCard Wp Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioWpPadTermination          | * | 0x01 | 0x0

  # !BSF NAME:{SdCard Clock Feedback Pin Mux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select  pin muxing. Refer to GPIO_*_MUXING_SDCARD_CLK_FB* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioClkFbPinMux               | * | 0x04 | 0x0

  # !BSF NAME:{SdCard Clock Feedback Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.SdCardGpioClkFbPadTermination       | * | 0x01 | 0x0

  # !BSF NAME:{Emmc Command Pin Mux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select  pin muxing. Refer to GPIO_*_MUXING_EMMC_CMD* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioCmdPinMux                   | * | 0x04 | 0x0

  # !BSF NAME:{Emmc Command Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioCmdPadTermination           | * | 0x01 | 0x0

  # !BSF NAME:{Emmc Data Pin Mux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT{UINT32}
  # !BSF HELP:{Select  pin muxing. Refer to GPIO_*_MUXING_EMMC_DATA_x* for possible values. One UINT32 for each data pin [0-8]}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioDataPinMux                  | * | 0x20 | { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }

  # !BSF NAME:{Emmc Data Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT{UINT8}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up. One byte for each data pin [0-8]}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioDataPadTermination          | * | 0x08 | { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 }

  # !BSF NAME:{Emmc Rclk PinMux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select Rclk pin muxing. Refer to GPIO_*_MUXING_EMMC_RCLK* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioRclkPinMux                  | * | 0x04 | 0x0

  # !BSF NAME:{Emmc Rclk Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioRclkPadTermination          | * | 0x01 | 0x0

  # !BSF NAME:{Emmc Clock Pin Mux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select Clock pin muxing. Refer to GPIO_*_MUXING_EMMC_CLK* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioClkPinMux                   | * | 0x04 | 0x0

  # !BSF NAME:{Emmc Clock Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioClkPadTermination           | * | 0x01 | 0x0

  # !BSF NAME:{Emmc Resetb PinMux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select Resetb pin muxing. Refer to GPIO_*_MUXING_EMMC_RESETB* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioResetbPinMux                | * | 0x04 | 0x0

  # !BSF NAME:{Emmc Resetb Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioResetbPadTermination        | * | 0x01 | 0x0

#ifdef PCH_EHL
  # !BSF NAME:{Emmc HipMon PinMux} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Select HipMon pin muxing. Refer to GPIO_*_MUXING_EMMC_HIP_MON* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioHipMonPinMux                | * | 0x04 | 0x0

  # !BSF NAME:{Emmc HipMon Pad Termination} TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up}
  gPlatformFspPkgTokenSpaceGuid.EmmcGpioHipMonPadTermination        | * | 0x01 | 0x0
#endif

  # !BSF PAGE:{PCH2}
  # !BSF NAME:{Show SPI controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable to show SPI controller.}
  gPlatformFspPkgTokenSpaceGuid.ShowSpiController           | * | 0x01 | 0x00

  # !BSF PAGE:{SA2}
  # !BSF NAME:{MicrocodeRegionBase} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Memory Base of Microcode Updates}
  gPlatformFspPkgTokenSpaceGuid.MicrocodeRegionBase         | * | 0x04 | 0x0

  # !BSF NAME:{MicrocodeRegionSize} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Size of Microcode Updates}
  gPlatformFspPkgTokenSpaceGuid.MicrocodeRegionSize         | * | 0x04 | 0x0

  # !BSF NAME:{SiipRegionBase} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Memory Base of Siip Firmware}
  gPlatformFspPkgTokenSpaceGuid.SiipRegionBase              | * | 0x04 | 0x0

  # !BSF NAME:{SiipRegionSize} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Size of Siip Firmware}
  gPlatformFspPkgTokenSpaceGuid.SiipRegionSize              | * | 0x04 | 0x0

  # !BSF NAME:{Turbo Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable Turbo mode. 0: disable, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.TurboMode                   | * | 0x01 | 0x1

  # !BSF PAGE:{PCH2}
  # !BSF NAME:{Enable SATA SALP Support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SATA Aggressive Link Power Management.}
  gPlatformFspPkgTokenSpaceGuid.SataSalpSupport             | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Port Multiplier} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable / Disable SATA Port Multiplier}
  gPlatformFspPkgTokenSpaceGuid.SataPortMultiplier          | * | 0x01 | 0x00

  # !BSF NAME:{Enable SATA ports} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable SATA ports. One byte for each port, byte0 for port0, byte1 for port1, and so on.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsEnable             | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA DEVSLP Feature} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable SATA DEVSLP per port. 0 is disable, 1 is enable. One byte for each port, byte0 for port0, byte1 for port1, and so on.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsDevSlp             | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable USB2 ports} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable per USB2 ports. One byte for each port, byte0 for port0, byte1 for port1, and so on.}
  gPlatformFspPkgTokenSpaceGuid.PortUsb20Enable             | * | 0x10 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Enable USB2 ports OTG} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Selectively Enable/Disable USB2 OTG Mode. One byte for each port, byte0 for port0, byte1 for port1, and so on.}
  gPlatformFspPkgTokenSpaceGuid.USB20Otg           | * | 0x10 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable USB3 ports OTG} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Selectively Enable/Disable USB3 OTG Mode. One byte for each port, byte0 for port0, byte1 for port1, and so on.}
  gPlatformFspPkgTokenSpaceGuid.USB30Otg           | * | 0xA | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable USB3 ports} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable per USB3 ports. One byte for each port, byte0 for port0, byte1 for port1, and so on.}
  gPlatformFspPkgTokenSpaceGuid.PortUsb30Enable             | * | 0x0A | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable xDCI controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable to xDCI controller.}
  gPlatformFspPkgTokenSpaceGuid.XdciEnable                  | * | 0x01 | 0x00

  # !BSF NAME:{Address of PCH_DEVICE_INTERRUPT_CONFIG table.} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{The address of the table of PCH_DEVICE_INTERRUPT_CONFIG.}
  gPlatformFspPkgTokenSpaceGuid.DevIntConfigPtr             | * | 0x04 | 0x00

  # !BSF NAME:{Number of DevIntConfig Entry} TYPE:{EditNum, HEX, (0x00,0x40)}
  # !BSF HELP:{Number of Device Interrupt Configuration Entry. If this is not zero, the DevIntConfigPtr must not be NULL.}
  gPlatformFspPkgTokenSpaceGuid.NumOfDevIntConfig           | * | 0x01 | 0x00

  # !BSF NAME:{PIRQx to IRQx Map Config} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PIRQx to IRQx mapping. The valid value is 0x00 to 0x0F for each. First byte is for PIRQA, second byte is for PIRQB, and so on. The setting is only available in Legacy 8259 PCI mode.}
  gPlatformFspPkgTokenSpaceGuid.PxRcConfig                  | * | 0x08 | { 0x0B, 0x0A, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B}

  # !BSF NAME:{Select GPIO IRQ Route}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x0F)}
  # !BSF HELP:{GPIO IRQ Select. The valid value is 14 or 15.}
  gPlatformFspPkgTokenSpaceGuid.GpioIrqRoute                | * | 0x01 | 0x0E

  # !BSF NAME:{Select SciIrqSelect}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x17)}
  # !BSF HELP:{SCI IRQ Select. The valid value is 9, 10, 11, and 20, 21, 22, 23 for APIC only.}
  gPlatformFspPkgTokenSpaceGuid.SciIrqSelect                | * | 0x01 | 0x09

  # !BSF NAME:{Select TcoIrqSelect}
  # !BSF TYPE:{EditNum, HEX, (0x00,0x17)}
  # !BSF HELP:{TCO IRQ Select. The valid value is 9, 10, 11, 20, 21, 22, 23.}
  gPlatformFspPkgTokenSpaceGuid.TcoIrqSelect                | * | 0x01 | 0x09

  # !BSF NAME:{Enable/Disable Tco IRQ}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}}
  # !BSF HELP:{Enable/disable TCO IRQ}
  gPlatformFspPkgTokenSpaceGuid.TcoIrqEnable                | * | 0x01 | 0x00

  # !BSF NAME:{PCH HDA Verb Table Entry Number} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Number of Entries in Verb Table.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaVerbTableEntryNum     | * | 1 | 0

  # !BSF NAME:{PCH HDA Verb Table Pointer} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Pointer to Array of pointers to Verb Table.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaVerbTablePtr          | * | 4 | 0

  # !BSF NAME:{PCH HDA Codec Sx Wake Capability} TYPE:{$EN_DIS}
  # !BSF HELP:{Capability to detect wake initiated by a codec in Sx}
  gPlatformFspPkgTokenSpaceGuid.PchHdaCodecSxWakeCapability | * | 0x01 | 0x00

  # !BSF NAME:{Enable SATA} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SATA controller.}
  gPlatformFspPkgTokenSpaceGuid.SataEnable                  | * | 0x01 | 0x01

  # !BSF NAME:{SATA Mode} TYPE:{Combo}
  # !BSF OPTION:{0:AHCI, 1:RAID}
  # !BSF HELP:{Select SATA controller working mode.}
  gPlatformFspPkgTokenSpaceGuid.SataMode                    | * | 0x01 | 0x00

  # !BSF NAME:{SPIn Device Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Selects SPI operation mode. N represents controller index: SPI0, SPI1, ... Available modes: 0:SerialIoSpiDisabled, 1:SerialIoSpiPci, 2:SerialIoSpiHidden}
  gPlatformFspPkgTokenSpaceGuid.SerialIoSpiMode             | * | 0x07 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{SPI<N> Chip Select Polarity} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Sets polarity for each chip Select. Available options: 0:SerialIoSpiCsActiveLow, 1:SerialIoSpiCsActiveHigh}
  gPlatformFspPkgTokenSpaceGuid.SerialIoSpiCsPolarity       | * | 0x0E | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{SPI<N> Chip Select Enable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0:Disabled, 1:Enabled. Enables GPIO for CS0 or CS1 if it is Enabled}
  gPlatformFspPkgTokenSpaceGuid.SerialIoSpiCsEnable         | * | 0x0E | { 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00}

  # !BSF NAME:{SPIn Default Chip Select Output} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Sets Default CS as Output. N represents controller index: SPI0, SPI1, ... Available options: 0:CS0, 1:CS1}
  gPlatformFspPkgTokenSpaceGuid.SerialIoSpiDefaultCsOutput  | * | 0x07 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{SPIn Default Chip Select Mode HW/SW} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Sets Default CS Mode Hardware or Software. N represents controller index: SPI0, SPI1, ... Available options: 0:HW, 1:SW}
  gPlatformFspPkgTokenSpaceGuid.SerialIoSpiCsMode           | * | 0x07 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{SPIn Default Chip Select State Low/High} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Sets Default CS State Low or High. N represents controller index: SPI0, SPI1, ... Available options: 0:Low, 1:High}
  gPlatformFspPkgTokenSpaceGuid.SerialIoSpiCsState          | * | 0x07 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{SPIn Master Input Slave Output Enable/Disable} TYPE:{EditNum, HEX, (0x000000, 0xFFFFFF)}
  # !BSF HELP:{0:Disabled, 1:Enabled. Sets Native Mode for SPIx MISO GPIO if it is Enabled}
  gPlatformFspPkgTokenSpaceGuid.SerialIoSpiMisoEnable       | * | 0x03 | {0x01, 0x01, 0x01}

  # !BSF NAME:{UARTn Device Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Selects Uart operation mode. N represents controller index: Uart0, Uart1, ... Available modes: 0:SerialIoUartDisabled, 1:SerialIoUartPci, 2:SerialIoUartHidden, 3:SerialIoUartCom, 4:SerialIoUartSkipInit}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartMode            | * | 0x07 | { 0x00, 0x00, 0x02, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{Default BaudRate for each Serial IO UART} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Set default BaudRate Supported from 0 - default to 6000000}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartBaudRate        | * | 0x1C | { 115200, 115200, 115200, 115200, 115200, 115200, 115200 }

  # !BSF NAME:{Default ParityType for each Serial IO UART} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set default Parity. 0: DefaultParity, 1: NoParity, 2: EvenParity, 3: OddParity}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartParity          | * | 0x07 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{Default DataBits for each Serial IO UART} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set default word length. 0: Default, 5,6,7,8}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartDataBits        | * | 0x07 | { 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08 }

  # !BSF NAME:{Default StopBits for each Serial IO UART} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set default stop bits. 0: DefaultStopBits, 1: OneStopBit, 2: OneFiveStopBits, 3: TwoStopBits}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartStopBits        | * | 0x07 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{Power Gating mode for each Serial IO UART that works in COM mode} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set Power Gating. 0: Disabled, 1: Enabled, 2: Auto}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartPowerGating     | * | 0x07 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{Enable Dma for each Serial IO UART that supports it} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set DMA/PIO mode. 0: Disabled, 1: Enabled}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartDmaEnable       | * | 0x07 | { 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00 }

  # !BSF NAME:{Enables UART hardware flow control, CTS and RTS lines} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enables UART hardware flow control, CTS and RTS lines.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartAutoFlow        | * | 0x07 | { 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00 }

  # !BSF NAME:{SerialIoUartRtsPinMuxPolicy} TYPE:{EditNum, HEX, (0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select SerialIo Uart Rts pin muxing. Refer to GPIO_*_MUXING_SERIALIO_UARTx_RTS* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartRtsPinMuxPolicy | * | 0x1C | { 0, 0, 0, 0, 0, 0, 0 }

  # !BSF NAME:{SerialIoUartCtsPinMuxPolicy} TYPE:{EditNum, HEX, (0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select SerialIo Uart Cts pin muxing. Refer to GPIO_*_MUXING_SERIALIO_UARTx_CTS* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartCtsPinMuxPolicy | * | 0x1C | { 0, 0, 0, 0, 0, 0, 0 }

  # !BSF NAME:{SerialIoUartRxPinMuxPolicy} TYPE:{EditNum, HEX, (0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select SerialIo Uart Rx pin muxing. Refer to GPIO_*_MUXING_SERIALIO_UARTx_RX* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartRxPinMuxPolicy  | * | 0x1C | { 0, 0, 0, 0, 0, 0, 0 }

  # !BSF NAME:{SerialIoUartTxPinMuxPolicy} TYPE:{EditNum, HEX, (0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select SerialIo Uart Tx pin muxing. Refer to GPIO_*_MUXING_SERIALIO_UARTx_TX* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartTxPinMuxPolicy  | * | 0x1C | { 0, 0, 0, 0, 0, 0, 0 }

  # !BSF NAME:{UART Number For Debug Purpose} TYPE:{Combo} OPTION:{ 0:UART0, 1:UART1, 2:UART2, 3:UART3, 4:UART4, 5:UART5, 6:UART6 }
  # !BSF HELP:{UART number for debug purpose. 0:UART0, 1:UART1, 2:UART2, 3:UART3, 4:UART4, 5:UART5, 6:UART6. Note: If UART0 is selected as CNVi BT Core interface, it cannot be used for debug purpose.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoDebugUartNumber     | * | 0x01 | 0x02

  # !BSF NAME:{Serial IO UART DBG2 table} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable or disable Serial Io UART DBG2 table, default is Disable; <b>0: Disable;</b> 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.SerialIoUartDbg2            | * | 0x07 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{I2Cn Device Mode} TYPE:{EditNum, HEX,  (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Selects I2c operation mode. N represents controller index: I2c0, I2c1, ... Available modes: 0:SerialIoI2cDisabled, 1:SerialIoI2cPci, 2:SerialIoI2cHidden}
  gPlatformFspPkgTokenSpaceGuid.SerialIoI2cMode             | * | 0x08 | { 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Serial IO I2C SDA Pin Muxing} TYPE:{EditNum, HEX, (0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select SerialIo I2c Sda pin muxing. Refer to GPIO_*_MUXING_SERIALIO_I2Cx_SDA* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchSerialIoI2cSdaPinMux     | * | 0x20 | { 0, 0, 0, 0, 0, 0, 0, 0 }

  # !BSF NAME:{Serial IO I2C SCL Pin Muxing} TYPE:{EditNum, HEX, (0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select SerialIo I2c Scl pin muxing. Refer to GPIO_*_MUXING_SERIALIO_I2Cx_SCL* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchSerialIoI2cSclPinMux     | * | 0x20 | { 0, 0, 0, 0, 0, 0, 0, 0 }

  # !BSF NAME:{PCH SerialIo I2C Pads Termination} TYPE:{Combo} OPTION:{0x1:None, 0x13:1kOhm WPU, 0x15:5kOhm WPU, 0x19:20kOhm WPU}
  # !BSF HELP:{0x0: Hardware default, 0x1: None, 0x13: 1kOhm weak pull-up, 0x15: 5kOhm weak pull-up, 0x19: 20kOhm weak pull-up - Enable/disable SerialIo I2C0,I2C1,... pads termination respectively. One byte for each controller, byte0 for I2C0, byte1 for I2C1, and so on.}
  gPlatformFspPkgTokenSpaceGuid.PchSerialIoI2cPadsTermination | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  }

  # !BSF NAME:{USB Per Port HS Preemphasis Bias} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB Per Port HS Preemphasis Bias. 000b-0mV, 001b-11.25mV, 010b-16.9mV, 011b-28.15mV, 100b-28.15mV, 101b-39.35mV, 110b-45mV, 111b-56.3mV. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb2PhyPetxiset             | * | 0x10 | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{USB Per Port HS Transmitter Bias} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB Per Port HS Transmitter Bias. 000b-0mV, 001b-11.25mV, 010b-16.9mV, 011b-28.15mV, 100b-28.15mV, 101b-39.35mV, 110b-45mV, 111b-56.3mV, One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb2PhyTxiset               | * | 0x10 | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{USB Per Port HS Transmitter Emphasis} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB Per Port HS Transmitter Emphasis. 00b - Emphasis OFF, 01b - De-emphasis ON, 10b - Pre-emphasis ON, 11b - Pre-emphasis & De-emphasis ON. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb2PhyPredeemp             | * | 0x10 | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{USB Per Port Half Bit Pre-emphasis} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB Per Port Half Bit Pre-emphasis. 1b - half-bit pre-emphasis, 0b - full-bit pre-emphasis. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb2PhyPehalfbit            | * | 0x10 | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable the write to USB 3.0 TX Output -3.5dB De-Emphasis Adjustment} TYPE:{EditNum, HEX, (0x00,0x01010101010101010101)}
  # !BSF HELP:{Enable the write to USB 3.0 TX Output -3.5dB De-Emphasis Adjustment. Each value in arrary can be between 0-1. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxDeEmphEnable      | * | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{USB 3.0 TX Output -3.5dB De-Emphasis Adjustment Setting} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB 3.0 TX Output -3.5dB De-Emphasis Adjustment Setting, HSIO_TX_DWORD5[21:16], <b>Default = 29h</b> (approximately -3.5dB De-Emphasis). One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxDeEmph            | * | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable the write to USB 3.0 TX Output Downscale Amplitude Adjustment} TYPE:{EditNum, HEX, (0x00,0x01010101010101010101)}
  # !BSF HELP:{Enable the write to USB 3.0 TX Output Downscale Amplitude Adjustment, Each value in arrary can be between 0-1. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxDownscaleAmpEnable  | * | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{USB 3.0 TX Output Downscale Amplitude Adjustment} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB 3.0 TX Output Downscale Amplitude Adjustment, HSIO_TX_DWORD8[21:16], <b>Default = 00h</b>. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxDownscaleAmp      | * | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME: {USB 3.0 adapted linear equalization parameters programming enable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP: {After enabling BIOS will program adapter linear equalization parameters <b>Default = 0h</b>.}
  gPlatformFspPkgTokenSpaceGuid.PchUsb3HsioCtrlAdaptOffsetCfgEnable   | * | 0xA | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME: {USB 3.0 LFPS sensitivity levels parameter programming enable N} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP: {Enabling this option will enable LFPS parameters programming<b>Default = 0h</b>.}
  gPlatformFspPkgTokenSpaceGuid.PchUsb3HsioFilterSelNEnable   | * | 0xA | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME: {USB 3.0 LFPS sensitivity levels parameter programming enable P} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP: {Enabling this option will enable LFPS parameters programming<b>Default = 0h</b>.}
  gPlatformFspPkgTokenSpaceGuid.PchUsb3HsioFilterSelPEnable   | * | 0xA | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME: {USB 3.0 input offset control enable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP: {Enables programming of input offset parameter, <b>Default = 0h</b>.}
  gPlatformFspPkgTokenSpaceGuid.PchUsb3HsioOlfpsCfgPullUpDwnResEnable   | * | 0xA | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME: {USB 3.0 adapted linear equalization parameters value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP: {This will change the actual adapted linear equalization value CTLE_ADAPT, <b>Default = 0h</b>.}
  gPlatformFspPkgTokenSpaceGuid.PchUsb3HsioCtrlAdaptOffsetCfg   | * | 0xA | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME: {USB 3.0 Controls the input offset} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP: {Controls the input offset, works in conjunction with LFPS sensitivity level, <b>Default = 3h</b>.}
  gPlatformFspPkgTokenSpaceGuid.PchUsb3HsioOlfpsCfgPullUpDwnRes   | * | 0xA | {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03}

  # !BSF NAME: {USB 3.0 LFPS sensitivity level for N} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP: {Sensitivity level for LFPS circuitry, <b>Default = 0h</b>.}
  gPlatformFspPkgTokenSpaceGuid.PchUsb3HsioFilterSelN   | * | 0xA | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME: {USB 3.0 LFPS sensitivity level for P} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP: {Sensitivity level for LFPS circuitry, <b>Default = 0h</b>.}
  gPlatformFspPkgTokenSpaceGuid.PchUsb3HsioFilterSelP   | * | 0xA | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable LAN} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable LAN controller.}
  gPlatformFspPkgTokenSpaceGuid.PchLanEnable                | * | 0x01 | 0x01

  # !BSF NAME:{Enable PCH TSN} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable TSN on the PCH.}
  gPlatformFspPkgTokenSpaceGuid.PchTsnEnable                | * | 0x01 | 0x01

  # !BSF NAME:{PCH TSN Multi VC Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable PCH TSN GBE Multiple Virtual Channel}
  gPlatformFspPkgTokenSpaceGuid.PchTsnGbeMultiVcEnable        | * | 0x01 | 0x00

  # !BSF NAME:{PCH TSN Link Speed} TYPE:{Combo} OPTION:{0: 24Mhz 2.5Gbps, 1: 24Mhz 1Gbps, 2: 38.4Mhz 2.5Gbps, 3: 38.4Mhz 1Gbps}
  # !BSF HELP:{Set PCH TSN Link Speed.}
  gPlatformFspPkgTokenSpaceGuid.PchTsnGbeLinkSpeed             | * | 0x01 | 0x02

  # !BSF NAME:{PCH TSN SGMII Support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SGMII support}
  gPlatformFspPkgTokenSpaceGuid.PchTsnGbeSgmiiEnable          | * | 0x01 | 0x00

  # !BSF NAME:{PSE TSN Multi VC Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable PSE TSN GBE Multiple Virtual Channel}
  gPlatformFspPkgTokenSpaceGuid.PseTsnGbeMultiVcEnable        | * | 0x02 | {0x00, 0x0}

  # !BSF NAME:{PSE TSN Link Speed} TYPE:{Combo} OPTION:{0: 24Mhz 2.5Gbps, 1: 24Mhz 1Gbps, 2: 38.4Mhz 2.5Gbps, 3: 38.4Mhz 1Gbps}
  # !BSF HELP:{Set TSN Link Speed.}
  gPlatformFspPkgTokenSpaceGuid.PseTsnGbeLinkSpeed             | * | 0x02 | {0x03, 0x3}

  # !BSF NAME:{PSE TSN SGMII Support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable SGMII support}
  gPlatformFspPkgTokenSpaceGuid.PseTsnGbeSgmiiEnable          | * | 0x02 | {0x00, 0x0}

  # !BSF NAME:{Tsn Mac Address Sub Region Base} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Base address of TSN MAC Address Sub Region}
  gPlatformFspPkgTokenSpaceGuid.TsnMacAddrBase              | * | 0x04 | 0x00000000

  # !BSF NAME:{Tsn Mac Address Sub Region Size} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Size of TSN MAC Address Sub Region}
  gPlatformFspPkgTokenSpaceGuid.TsnMacAddrSize              | * | 0x04 | 0x00000000

  # !BSF NAME:{PSE Tsn Ip Config Sub Region Base} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Base address of PSE TSN IP Config Sub Region}
  gPlatformFspPkgTokenSpaceGuid.PseTsnIpConfigBase          | * | 0x04 | 0x00000000

  # !BSF NAME:{PSE Tsn Ip Config Sub Region Size} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Size of PSE TSN IP Config Sub Region}
  gPlatformFspPkgTokenSpaceGuid.PseTsnIpConfigSize          | * | 0x04 | 0x00000000

  # !BSF NAME:{Tsn Config Sub Region Base} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Base address of TSN Config Sub Region}
  gPlatformFspPkgTokenSpaceGuid.TsnConfigBase               | * | 0x04 | 0x00000000

  # !BSF NAME:{Tsn Config Sub Region Size} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Size of TSN Config Sub Region}
  gPlatformFspPkgTokenSpaceGuid.TsnConfigSize               | * | 0x04 | 0x00000000

  # !BSF NAME:{PCIe PTM enable/disable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable Precision Time Measurement for PCIE Root Ports.}
  gPlatformFspPkgTokenSpaceGuid.PciePtm                    | * | 0x18 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIe DPC enable/disable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable Downstream Port Containment for PCIE Root Ports.}
  gPlatformFspPkgTokenSpaceGuid.PcieDpc                    | * | 0x18 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIe DPC extensions enable/disable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/disable Downstream Port Containment Extensions for PCIE Root Ports.}
  gPlatformFspPkgTokenSpaceGuid.PcieEdpc                   | * | 0x18 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{USB PDO Programming} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable PDO programming for USB in PEI phase. Disabling will allow for programming during later phase. 1: enable, 0: disable}
  gPlatformFspPkgTokenSpaceGuid.UsbPdoProgramming                   | * | 0x01 | 0x01

  # !BSF NAME:{Power button debounce configuration} TYPE:{EditNum, HEX, (0x00,0x009C4000)}
  # !BSF HELP:{Debounce time for PWRBTN in microseconds. For values not supported by HW, they will be rounded down to closest supported on. 0: disable, 250-1024000us: supported range}
  gPlatformFspPkgTokenSpaceGuid.PmcPowerButtonDebounce              | * | 0x04 | 0x00

  # !BSF NAME:{PCH eSPI Master and Slave BME enabled} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{PCH eSPI Master and Slave BME enabled}
  gPlatformFspPkgTokenSpaceGuid.PchEspiBmeMasterSlaveEnabled        | * | 0x01 | 0x01

  # !BSF NAME:{PCH SATA use RST Legacy OROM} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Use PCH SATA RST Legacy OROM when CSM is Enabled}
  gPlatformFspPkgTokenSpaceGuid.SataRstLegacyOrom                   | * | 0x01 | 0x00

  # !BSF NAME:{Mask to enable the usage of external V1p05 VR rail in specific S0ix or Sx states} TYPE:{EditNum, HEX, (0x00,0x1F)}
  # !BSF HELP:{Enable External V1P05 Rail in: BIT0:S0i1/S0i2, BIT1:S0i3, BIT2:S3, BIT3:S4, BIT5:S5}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtV1p05RailEnabledStates    | * | 0x1 | 0x0

  # !BSF NAME:{Mask to enable the platform configuration of external V1p05 VR rail} TYPE:{EditNum, HEX, (0x00,0x0F)}
  # !BSF HELP:{External V1P05 Rail Supported Configuration}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtV1p05RailSupportedVoltageStates  | * | 0x1 | 0x0

  # !BSF NAME:{External V1P05 Voltage Value that will be used in S0i2/S0i3 states} TYPE:{EditNum, HEX, (0x0,0x07FF)}
  # !BSF HELP:{Value is given in 2.5mV increments (0=0mV, 1=2.5mV, 2=5mV...)}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtV1p05RailVoltage          | * | 0x2 | 0x01A4

  # !BSF NAME:{External V1P05 Icc Max Value} TYPE:{EditNum, HEX, (0x0,0xC8)}
  # !BSF HELP:{Granularity of this setting is 1mA and maximal possible value is 200mA}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtV1p05RailIccMax           | * | 0x1 | 0x64

  # !BSF NAME:{Mask to enable the usage of external Vnn VR rail in specific S0ix or Sx states} TYPE:{EditNum, HEX, (0x00,0x1F)}
  # !BSF HELP:{Enable External Vnn Rail in: BIT0:S0i1/S0i2, BIT1:S0i3, BIT2:S3, BIT3:S4, BIT5:S5}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtVnnRailEnabledStates      | * | 0x1 | 0x0

  # !BSF NAME:{Mask to enable the platform configuration of external Vnn VR rail} TYPE:{EditNum, HEX, (0x00,0x0F)}
  # !BSF HELP:{External Vnn Rail Supported Configuration}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtVnnRailSupportedVoltageStates  | * | 0x1 | 0x0

  # !BSF NAME:{External Vnn Voltage Value that will be used in S0ix/Sx states} TYPE:{EditNum, HEX, (0x0,0x07FF)}
  # !BSF HELP:{Value is given in 2.5mV increments (0=0mV, 1=2.5mV, 2=5mV...), Default is set to 420}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtVnnRailVoltage            | * | 0x2 | 0x01A4

  # !BSF NAME:{External Vnn Icc Max Value that will be used in S0ix/Sx states} TYPE:{EditNum, HEX, (0x0,0xC8)}
  # !BSF HELP:{Granularity of this setting is 1mA and maximal possible value is 200mA}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtVnnRailIccMax             | * | 0x1 | 0xC8

  # !BSF NAME:{Mask to enable the usage of external Vnn VR rail in Sx states} TYPE:{EditNum, HEX, (0x00,0x1F)}
  # !BSF HELP:{Use only if Ext Vnn Rail config is different in Sx. Enable External Vnn Rail in Sx: BIT0-1:Reserved, BIT2:S3, BIT3:S4, BIT5:S5}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtVnnRailSxEnabledStates    | * | 0x1 | 0x0

  # !BSF NAME:{External Vnn Voltage Value that will be used in Sx states} TYPE:{EditNum, HEX, (0x0,0x07FF)}
  # !BSF HELP:{Use only if Ext Vnn Rail config is different in Sx. Value is given in 2.5mV increments (0=0mV, 1=2.5mV, 2=5mV...)}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtVnnRailSxVoltage          | * | 0x2 | 0x01A4

  # !BSF NAME:{External Vnn Icc Max Value that will be used in Sx states} TYPE:{EditNum, HEX, (0x0,0xC8)}
  # !BSF HELP:{Use only if Ext Vnn Rail config is different in Sx. Granularity of this setting is 1mA and maximal possible value is 200mA}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtVnnRailSxIccMax           | * | 0x1 | 0xC8

  # !BSF NAME:{Transition time in microseconds from Low Current Mode Voltage to High Current Mode Voltage} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{This field has 1us resolution. When value is 0 PCH will not transition VCCIN_AUX to low current mode voltage.}
  gPlatformFspPkgTokenSpaceGuid.PchFivrVccinAuxLowToHighCurModeVolTranTime  | * | 0x1 | 0x0

  # !BSF NAME:{Transition time in microseconds from Retention Mode Voltage to High Current Mode Voltage} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{This field has 1us resolution. When value is 0 PCH will not transition VCCIN_AUX to retention mode voltage.}
  gPlatformFspPkgTokenSpaceGuid.PchFivrVccinAuxRetToHighCurModeVolTranTime  | * | 0x1 | 0x0

  # !BSF NAME:{Transition time in microseconds from Retention Mode Voltage to Low Current Mode Voltage} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{This field has 1us resolution. When value is 0 PCH will not transition VCCIN_AUX to retention mode voltage.}
  gPlatformFspPkgTokenSpaceGuid.PchFivrVccinAuxRetToLowCurModeVolTranTime   | * | 0x1 | 0x0

  # !BSF NAME:{Transition time in microseconds from Off (0V) to High Current Mode Voltage} TYPE:{EditNum, HEX, (0x0,0x7FF)}
  # !BSF HELP:{This field has 1us resolution. When value is 0 Transition to 0V is disabled.}
  gPlatformFspPkgTokenSpaceGuid.PchFivrVccinAuxOffToHighCurModeVolTranTime  | * | 0x2 | 0x005A
  #
  # !BSF NAME:{Trace Hub Memory Base} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{If Trace Hub is enabled and trace to memory is desired, BootLoader needs to allocate trace hub memory as reserved and uncacheable, set the base to ensure Trace Hub memory is configured properly.}
  gPlatformFspPkgTokenSpaceGuid.TraceHubMemBase                             | * | 0x04 | 0x00000000

  # !BSF NAME:{PMC Debug Message Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When Enabled, PMC HW will send debug messages to trace hub; When Disabled, PMC HW will never send debug meesages to trace hub. Noted: When Enabled, may not enter S0ix}
  gPlatformFspPkgTokenSpaceGuid.PmcDbgMsgEn                                 | * | 0x01 | 0x00

  # !BSF NAME:{Pointer of ChipsetInit Binary} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{ChipsetInit Binary Pointer.}
  gPlatformFspPkgTokenSpaceGuid.ChipsetInitBinPtr           | * | 0x04 | 0x00000000

  # !BSF NAME:{Length of ChipsetInit Binary} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{ChipsetInit Binary Length.}
  gPlatformFspPkgTokenSpaceGuid.ChipsetInitBinLen           | * | 0x04 | 0x00000000

  # !BSF NAME:{FIA Lane Reversal Enable/Disable config mask} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable or disable Lane Reversal. If Enabled, the x2 FIA Lane will be flipped}
  gPlatformFspPkgTokenSpaceGuid.FiaLaneReversalEnable       | * | 0x02 | 0x00

  # !BSF NAME:{FIVR Dynamic Power Management} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable FIVR Dynamic Power Management.}
  gPlatformFspPkgTokenSpaceGuid.PchFivrDynPm                                | * | 0x01 | 0x01

  # !BSF NAME:{PchPostMemRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for PCH Post-Mem}
  gPlatformFspPkgTokenSpaceGuid.PchPostMemRsvd                  | * | 0x10 | {0x00}

  # !BSF NAME:{CNVi Configuration} TYPE:{Combo} OPTION:{0:Disable, 1:Auto}
  # !BSF HELP:{This option allows for automatic detection of Connectivity Solution. [Auto Detection] assumes that CNVi will be enabled when available, [Disable] allows for disabling CNVi.}
  gPlatformFspPkgTokenSpaceGuid.CnviMode                    | * | 0x01 | 0x01

  # !BSF NAME:{CNVi BT Core} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable CNVi BT Core, Default is ENABLE. 0: DISABLE, 1: ENABLE}
  gPlatformFspPkgTokenSpaceGuid.CnviBtCore                  | * | 0x01 | 0x01

  # !BSF NAME:{CNVi BT Audio Offload} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable BT Audio Offload, Default is DISABLE. 0: DISABLE, 1: ENABLE}
  gPlatformFspPkgTokenSpaceGuid.CnviBtAudioOffload          | * | 0x01 | 0x00

  # !BSF NAME:{CNVi RF_RESET pin muxing} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select CNVi RF_RESET# pin depending on board routing. TGP-LP: GPP_A8 = 0x2942E408(default) or GPP_F4 = 0x194BE404. TGP-H: 0. TGP-K: 0. Refer to GPIO_*_MUXING_CNVI_RF_RESET_* in GpioPins*.h.}
  gPlatformFspPkgTokenSpaceGuid.CnviRfResetPinMux           | * | 0x04 | 0x0

  # !BSF NAME:{CNVi CLKREQ pin muxing} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select CNVi CLKREQ pin depending on board routing. TGP-LP: GPP_A9 = 0x3942E609(default) or GPP_F5 = 0x394BE605. TGP-H: 0. TGP-K: 0. Refer to GPIO_*_MUXING_CNVI_MODEM_CLKREQ_* in GpioPins*.h.}
  gPlatformFspPkgTokenSpaceGuid.CnviClkreqPinMux            | * | 0x04 | 0x0

  # !BSF NAME:{Enable Host C10 reporting through eSPI} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable Host C10 reporting to Slave via eSPI Virtual Wire.}
  gPlatformFspPkgTokenSpaceGuid.PchEspiHostC10ReportEnable  | * | 0x01 | 0x0

  # !BSF NAME:{PCH USB2 PHY Power Gating enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1: Will enable USB2 PHY SUS Well Power Gating, 0: Will not enable PG of USB2 PHY Sus Well PG}
  gPlatformFspPkgTokenSpaceGuid.PmcUsb2PhySusPgEnable       | * | 0x01 | 0x01

  # !BSF NAME:{PCH USB OverCurrent mapping enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{1: Will program USB OC pin mapping in xHCI controller memory, 0: Will clear OC pin mapping allow for NOA usage of OC pins}
  gPlatformFspPkgTokenSpaceGuid.PchUsbOverCurrentEnable     | * | 0x01 | 0x01

  # !BSF NAME:{Espi Lgmr Memory Range decode } TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This option enables or disables espi lgmr }
  gPlatformFspPkgTokenSpaceGuid.PchEspiLgmrEnable           | * | 0x01 | 0x01

  # !BSF NAME:{External V1P05 Control Ramp Timer value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Hold off time to be used when changing the v1p05_ctrl for external bypass value in us}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtV1p05RailCtrlRampTmr           | * | 0x1 | 0x1

  # !BSF NAME:{External VNN Control Ramp Timer value} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Hold off time to be used when changing the vnn_ctrl for external bypass value in us}
  gPlatformFspPkgTokenSpaceGuid.PchFivrExtVnnRailCtrlRampTmr           | * | 0x1 | 0x1

  #
  # ME
  #
  # !BSF NAME:{HECI3 state} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{The HECI3 state from Mbp for reference in S3 path or when MbpHob is not installed. 0: disable, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.Heci3Enabled                | * | 0x01 | 0x0

  #
  # PCH
  #

  #
  # !BSF NAME:{PCHHOT# pin} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable PCHHOT# pin assertion when temperature is higher than PchHotLevel. 0: disable, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.PchHotEnable                | * | 0x01 | 0x00

  #
  # !BSF NAME:{SATA LED} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{SATA LED indicating SATA controller activity. 0: disable, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.SataLedEnable               | * | 0x01 | 0x00

  #
  # !BSF NAME:{VRAlert# Pin} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When VRAlert# feature pin is enabled and its state is '0', the PMC requests throttling to a T3 Tstate to the PCH throttling unit.. 0: disable, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.PchPmVrAlert                | * | 0x01 | 0x00

  #
  # AMT
  #
  # !BSF NAME:{AMT Switch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable or disable AMT functionality.}
  gPlatformFspPkgTokenSpaceGuid.AmtEnabled                  | * | 0x01 | 0x01

  # !BSF NAME:{WatchDog Timer Switch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable or disable WatchDog timer. Setting is invalid if AmtEnabled is 0.}
  gPlatformFspPkgTokenSpaceGuid.WatchDogEnabled             | * | 0x01 | 0x0

  # !BSF NAME:{Manageability Mode set by Mebx} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable or disable Manageability Mode.}
  gPlatformFspPkgTokenSpaceGuid.ManageabilityMode           | * | 0x01 | 0x0

  # !BSF NAME:{PET Progress} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Enable/Disable PET Events Progress to receive PET Events. Setting is invalid if AmtEnabled is 0.}
  gPlatformFspPkgTokenSpaceGuid.FwProgress                  | * | 0x01 | 0x0

  # !BSF NAME:{SOL Switch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Serial Over Lan enable/disable state by Mebx. Setting is invalid if AmtEnabled is 0.}
  gPlatformFspPkgTokenSpaceGuid.AmtSolEnabled               | * | 0x01 | 0x0

  # !BSF NAME:{OS Timer} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !BSF HELP:{16 bits Value, Set OS watchdog timer. Setting is invalid if AmtEnabled is 0.}
  gPlatformFspPkgTokenSpaceGuid.WatchDogTimerOs             | * | 0x02 | 0x0

  # !BSF NAME:{BIOS Timer} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !BSF HELP:{16 bits Value, Set BIOS watchdog timer. Setting is invalid if AmtEnabled is 0.}
  gPlatformFspPkgTokenSpaceGuid.WatchDogTimerBios           | * | 0x02 | 0x0

  # !BSF NAME:{Remote Assistance Trigger Availablilty} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, Remote Assistance enable/disable state by Mebx.}
  gPlatformFspPkgTokenSpaceGuid.RemoteAssistance            | * | 0x01 | 0x0

  # !BSF NAME:{KVM Switch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, KVM enable/disable state by Mebx. Setting is invalid if AmtEnabled is 0.}
  gPlatformFspPkgTokenSpaceGuid.AmtKvmEnabled               | * | 0x01 | 0x0

  # !BSF NAME:{KVM Switch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable. 0: Disable, 1: enable, KVM enable/disable state by Mebx.}
  gPlatformFspPkgTokenSpaceGuid.ForcMebxSyncUp              | * | 0x01 | 0x0

  # !BSF NAME:{PCH PCIe root port connection type} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: built-in device, 1:slot}
  gPlatformFspPkgTokenSpaceGuid.PcieRpSlotImplemented       | * | 0x18 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Access Control Services Extended Capability} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable PCIE RP Access Control Services Extended Capability}
  gPlatformFspPkgTokenSpaceGuid.PcieRpAcsEnabled           | * | 0x18 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Clock Power Management} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable PCIE RP Clock Power Management, even if disabled, CLKREQ# signal can still be controlled by L1 PM substates mechanism}
  gPlatformFspPkgTokenSpaceGuid.PcieRpEnableCpm            | * | 0x18 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Multi VC Enabled} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable PCIE RP Multiple Virtual Channels}
  gPlatformFspPkgTokenSpaceGuid.PcieRpMultiVcEnabled       | * | 0x18 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Detect Timeout Ms} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{The number of milliseconds within 0~65535 in reference code will wait for link to exit Detect state for enabled ports before assuming there is no device and potentially disabling the port.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpDetectTimeoutMs      | * | 0x30 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{ModPHY SUS Power Domain Dynamic Gating} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable ModPHY SUS Power Domain Dynamic Gating. Setting not supported on PCH-H. 0: disable, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.PmcModPhySusPgEnable       | * | 0x01 | 0x01

  # !BSF NAME:{V1p05-PHY supply external FET control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable control using EXT_PWR_GATE# pin of external FET to power gate v1p05-PHY supply. 0: disable, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.PmcV1p05PhyExtFetControlEn | * | 0x01 | 0x00

  # !BSF NAME:{V1p05-IS supply external FET control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable control using EXT_PWR_GATE2# pin of external FET to power gate v1p05-IS supply. 0: disable, 1: enable}
  gPlatformFspPkgTokenSpaceGuid.PmcV1p05IsExtFetControlEn  | * | 0x01 | 0x00

  #
  # SA Post-Mem Production Block Start
  #

  # !BSF NAME:{Enable/Disable PavpEnable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable PavpEnable, Disable: Disable PavpEnable}
  gPlatformFspPkgTokenSpaceGuid.PavpEnable                  | * | 0x01 | 0x1

  # !BSF NAME:{CdClock Frequency selection} TYPE:{Combo}
  # !BSF OPTION:{0xFF: Auto (Max based on reference clock frequency), 0: 307.2, 1: 312 Mhz, 2: 552 Mhz, 3: 556.8 Mhz, 4: 648 Mhz, 5: 652.8 Mhz}
  # !BSF HELP:{0 (Default) Auto (Max based on reference clock frequency), 0: 307.2, 1: 312 Mhz, 2: 552 Mhz, 3: 556.8 Mhz, 4: 648 Mhz, 5: 652.8 Mhz}
  gPlatformFspPkgTokenSpaceGuid.CdClock                     | * | 0x1 | 0xFF

  # !BSF NAME:{Enable/Disable PeiGraphicsPeimInit} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable PeiGraphicsPeimInit, Disable: Disable PeiGraphicsPeimInit}
  gPlatformFspPkgTokenSpaceGuid.PeiGraphicsPeimInit         | * | 0x01 | 0x1

  # !BSF NAME:{Enable D3 Hot in TCSS } TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This policy will enable/disable D3 hot support in IOM}
  gPlatformFspPkgTokenSpaceGuid.D3HotEnable                 | * | 0x01 | 0x00

  # !BSF NAME:{Enable or disable GNA device} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.GnaEnable                   | * | 0x1 | 0x1

  # !BSF NAME:{Enable or disable HPD of DDI port-A device} TYPE:{Combo}
  # !BSF OPTION:{0:Disabled, 1:eDP, 2:MIPI DSI}
  # !BSF HELP:{0=Disabled,1(Default)=eDP, 2=MIPI DSI, }
  gPlatformFspPkgTokenSpaceGuid.DdiPortAConfig              | * | 0x1 | 0x1

  # !BSF NAME:{Enable or disable HPD of DDI port-B device} TYPE:{Combo}
  # !BSF OPTION:{1:DP, 2:MIPI DSI, 3:HDMI}
  # !BSF HELP:{1(Default)=DP, 2=MIPI DSI, 3=HDMI}
  gPlatformFspPkgTokenSpaceGuid.DdiPortBConfig              | * | 0x1 | 0x1

  # !BSF NAME:{Enable or disable HPD of DDI port-C device} TYPE:{Combo}
  # !BSF OPTION:{1:HDMI, 2:DP}
  # !BSF HELP:{1(Default)= HDMI, 2=DP}
  gPlatformFspPkgTokenSpaceGuid.DdiPortCConfig              | * | 0x1 | 0x1

  # !BSF NAME:{Enable or disable HPD of DDI port A} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.DdiPortAHpd                 | * | 0x1 | 0x1

  # !BSF NAME:{Enable or disable HPD of DDI port B} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.DdiPortBHpd                 | * | 0x1 | 0x1

  # !BSF NAME:{Enable or disable HPD of DDI port C} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.DdiPortCHpd                 | * | 0x1 | 0x0

  # !BSF NAME:{Enable or disable HPD of DDI port 1} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.DdiPort1Hpd                 | * | 0x1 | 0x0

  # !BSF NAME:{Enable or disable HPD of DDI port 2} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.DdiPort2Hpd                 | * | 0x1 | 0x0

  # !BSF NAME:{Enable or disable HPD of DDI port 3} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.DdiPort3Hpd                 | * | 0x1 | 0x0

  # !BSF NAME:{Enable or disable HPD of DDI port 4} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.DdiPort4Hpd                 | * | 0x1 | 0x0

  # !BSF NAME:{Enable or disable DDC of DDI port A} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.DdiPortADdc                 | * | 0x1 | 0x1

  # !BSF NAME:{Enable or disable DDC of DDI port B} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.DdiPortBDdc                 | * | 0x1 | 0x1

  # !BSF NAME:{Enable or disable DDC of DDI port C} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0=Disable, 1(Default)=Enable}
  gPlatformFspPkgTokenSpaceGuid.DdiPortCDdc                 | * | 0x1 | 0x0

  # !BSF NAME:{Enable DDC setting of DDI Port 1} TYPE:{Combo}
  # !BSF OPTION:{0: Disable, 1: DDC}
  # !BSF HELP:{0=Disable, 1=DDC(Default)}
  gPlatformFspPkgTokenSpaceGuid.DdiPort1Ddc                 | * | 0x1 | 0x0

  # !BSF NAME:{Enable DDC setting of DDI Port 2} TYPE:{Combo}
  # !BSF OPTION:{0: Disable, 1: DDC}
  # !BSF HELP:{0=Disable, 1=DDC(Default)}
  gPlatformFspPkgTokenSpaceGuid.DdiPort2Ddc                 | * | 0x1 | 0x0

  # !BSF NAME:{Enable DDC setting of DDI Port 3} TYPE:{Combo}
  # !BSF OPTION:{0: Disable, 1: DDC}
  # !BSF HELP:{0=Disable, 1=DDC(Default)}
  gPlatformFspPkgTokenSpaceGuid.DdiPort3Ddc                 | * | 0x1 | 0x0

  # !BSF NAME:{Enable DDC setting of DDI Port 4} TYPE:{Combo}
  # !BSF OPTION:{0: Disable, 1: DDC}
  # !BSF HELP:{0=Disable, 1=DDC(Default)}
  gPlatformFspPkgTokenSpaceGuid.DdiPort4Ddc                 | * | 0x1 | 0x0

  # !BSF NAME:{TypeC port GPIO setting} TYPE:{EditNum, HEX, (0, 0xFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{GPIO Ping number for Type C Aux Oritation setting, use the GpioPad that is defined in GpioPinsXXXH.h and GpioPinsXXXLp.h as argument.(XXX is platform name, Ex: Ehl = ElkhartLake)}
  gPlatformFspPkgTokenSpaceGuid.IomTypeCPortPadCfg          | * | 0x20 | {0x00000000,0x00000000, 0x06040000, 0x06040011, 0x00000000, 0x00000000, 0x00000000, 0x00000000}

  # !BSF NAME:{CPU USB3 Port Over Current Pin} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Describe the specific over current pin number of USBC Port N.}
  gPlatformFspPkgTokenSpaceGuid.CpuUsb3OverCurrentPin       | * | 0x8 | { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }

  # !BSF NAME:{Enable D3 Cold in TCSS } TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This policy will enable/disable D3 cold support in IOM}
  gPlatformFspPkgTokenSpaceGuid.D3ColdEnable                | * | 0x01 | 0x00

  # !BSF NAME:{PchPostMemRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for PCH Post-Mem}
  gPlatformFspPkgTokenSpaceGuid.SaPostMemRsvd               | * | 0x8 | {0x00}

  #
  #VMD post-mem config
  #
  # !BSF NAME:{Enable VMD controller} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable to VMD controller.0: Disable(Default); 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.VmdEnable                 | * | 0x01 | 0x00

  # !BSF NAME:{Enable VMD portA Support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable to VMD portA Support.}
  gPlatformFspPkgTokenSpaceGuid.VmdPortA                  | * | 0x01 | 0x00

  # !BSF NAME:{Enable VMD portB Support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable to VMD portB Support.}
  gPlatformFspPkgTokenSpaceGuid.VmdPortB                  | * | 0x01 | 0x00

  # !BSF NAME:{Enable VMD portC Support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable to VMD portC Support.}
  gPlatformFspPkgTokenSpaceGuid.VmdPortC                  | * | 0x01 | 0x00

  # !BSF NAME:{Enable VMD portD Support} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/disable to VMD portD Support.}
  gPlatformFspPkgTokenSpaceGuid.VmdPortD                  | * | 0x01 | 0x00

  # !BSF NAME:{VMD Config Bar size} TYPE:{EditNum, DEC, (20,28)}
  # !BSF HELP:{Set The VMD Config Bar Size.}
  gPlatformFspPkgTokenSpaceGuid.VmdCfgBarSz               | * | 0x01 | 0x00

  # !BSF NAME:{VMD Config Bar Attributes} TYPE:{Combo}
  # !BSF OPTION:{0: VMD_32BIT_NONPREFETCH, 1: VMD_64BIT_NONPREFETCH, 2: VMD_64BIT_PREFETCH}
  # !BSF HELP:{0: VMD_32BIT_NONPREFETCH, 1: VMD_64BIT_NONPREFETCH, 2: VMD_64BIT_PREFETCH(Default)}
  gPlatformFspPkgTokenSpaceGuid.VmdCfgBarAttr             | * | 0x01 | 0x00

  # !BSF NAME:{VMD Mem Bar1 size} TYPE:{EditNum, DEC, (12,47)}
  # !BSF HELP:{Set The VMD Mem Bar1 Size.}
  gPlatformFspPkgTokenSpaceGuid.VmdMemBarSz1              | * | 0x01 | 0x00

  # !BSF NAME:{VMD Mem Bar1 Attributes} TYPE:{Combo}
  # !BSF OPTION:{0: VMD_32BIT_NONPREFETCH, 1: VMD_64BIT_NONPREFETCH, 2: VMD_64BIT_PREFETCH}
  # !BSF HELP:{0: VMD_32BIT_NONPREFETCH(Default), 1: VMD_64BIT_NONPREFETCH, 2: VMD_64BIT_PREFETCH}
  gPlatformFspPkgTokenSpaceGuid.VmdMemBar1Attr            | * | 0x01 | 0x00

  # !BSF NAME:{VMD Mem Bar2 size} TYPE:{EditNum, DEC, (12,47)}
  # !BSF HELP:{Set The VMD Mem Bar2 Size.}
  gPlatformFspPkgTokenSpaceGuid.VmdMemBarSz2              | * | 0x01 | 0x00

  # !BSF NAME:{VMD Mem Bar2 Attributes} TYPE:{Combo}
  # !BSF OPTION:{0: VMD_32BIT_NONPREFETCH, 1: VMD_64BIT_NONPREFETCH, 2: VMD_64BIT_PREFETCH}
  # !BSF HELP:{0: VMD_32BIT_NONPREFETCH, 1: VMD_64BIT_NONPREFETCH(Default), 2: VMD_64BIT_PREFETCH}
  gPlatformFspPkgTokenSpaceGuid.VmdMemBar2Attr            | * | 0x01 | 0x00

  # !BSF NAME:{Enable/Disable PMC-PD Solution } TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This policy will enable/disable PMC-PD Solution vs EC-TCPC Solution}
  gPlatformFspPkgTokenSpaceGuid.PmcPdEnable               | * | 0x01 | 0x01

  # !BSF NAME:{TCSS Aux Orientation Override Enable} TYPE:{EditNum, HEX, (0x0,0x0FFF)}
  # !BSF HELP:{Bits 0, 2, ... 10 control override enables, bits 1, 3, ... 11 control overrides}
  gPlatformFspPkgTokenSpaceGuid.TcssAuxOri                  | * | 0x02 | 0x0000

  # !BSF NAME:{TCSS HSL Orientation Override Enable} TYPE:{EditNum, HEX, (0x0,0x0FFF)}
  # !BSF HELP:{Bits 0, 2, ... 10 control override enables, bits 1, 3, ... 11 control overrides}
  gPlatformFspPkgTokenSpaceGuid.TcssHslOri                  | * | 0x02 | 0x0000

  # !BSF NAME:{USB override in IOM } TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This policy will enable/disable USB Connect override in IOM}
  gPlatformFspPkgTokenSpaceGuid.UsbOverride                 | * | 0x01 | 0x00

  # !BSF NAME:{TCSS USB Port Enable} TYPE:{EditNum, HEX, (0x0,0x000F)}
  # !BSF HELP:{Bits 0, 1, ... max Type C port control enables}
  gPlatformFspPkgTokenSpaceGuid.UsbTcPortEn                 | * | 0x01 | 0x00

  # !BSF NAME:{ITBT Root Port Enable} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFF)}
  # !BSF OPTION:{0:Disable, 1:Enable}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{ITBT Root Port Enable, 0:Disable, 1:Enable}
  gPlatformFspPkgTokenSpaceGuid.ITbtPcieRootPortEn          | * | 0x4 | {0, 0, 0, 0}

  # !BSF NAME:{ITBTForcePowerOn Timeout value} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !BSF HELP:{ITBTForcePowerOn value. Specified increment values in miliseconds. Range is 0-1000. 100 = 100 ms.}
  gPlatformFspPkgTokenSpaceGuid.ITbtForcePowerOnTimeoutInMs | * | 0x02 | 0x1F4

  # !BSF NAME:{ITbtConnectTopology Timeout value} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !BSF HELP:{ITbtConnectTopologyTimeout value. Specified increment values in miliseconds. Range is 0-10000. 100 = 100 ms.}
  gPlatformFspPkgTokenSpaceGuid.ITbtConnectTopologyTimeoutInMs  | * | 0x02 | 0x1388

  # !BSF NAME:{VCCST request for IOM } TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This policy will enable/disable VCCST and also decides if message would be replayed in S4/S5}
  gPlatformFspPkgTokenSpaceGuid.VccSt                       | * | 0x01 | 0x00

  # !BSF NAME:{ITBT DMA LTR}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{TCSS DMA1, DMA2 LTR value}
  gPlatformFspPkgTokenSpaceGuid.ITbtDmaLtr                     | * | 0x04 | {0x97FF, 0x97FF}


  # !BSF NAME:{Enable/Disable CrashLog} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable CPU CrashLog, Disable: Disable CPU CrashLog}
  gPlatformFspPkgTokenSpaceGuid.CpuCrashLogEnable           | * | 0x01 | 0x1

  #
  # Itbt PCIe RootPort Configuration
  #
  # !BSF NAME:{Enable/Disable PTM} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This policy will enable/disable Precision Time Measurement for TCSS PCIe Root Ports}
  gPlatformFspPkgTokenSpaceGuid.PtmEnabled                     | * | 0x04 | {0, 0, 0, 0}

  # !BSF NAME:{PCIE RP Ltr Enable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting Mechanism.}
  gPlatformFspPkgTokenSpaceGuid.SaPcieItbtRpLtrEnable                         | * | 0x4 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Mode.}
  gPlatformFspPkgTokenSpaceGuid.SaPcieItbtRpSnoopLatencyOverrideMode          | * | 0x4 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Multiplier} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Multiplier.}
  gPlatformFspPkgTokenSpaceGuid.SaPcieItbtRpSnoopLatencyOverrideMultiplier    | * | 0x4 | { 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Value.}
  gPlatformFspPkgTokenSpaceGuid.SaPcieItbtRpSnoopLatencyOverrideValue         | * | 0x8 | { 0x00C8, 0x00C8, 0x003C, 0x00C8 }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Mode.}
  gPlatformFspPkgTokenSpaceGuid.SaPcieItbtRpNonSnoopLatencyOverrideMode       | * | 0x4 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Multiplier} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Multiplier.}
  gPlatformFspPkgTokenSpaceGuid.SaPcieItbtRpNonSnoopLatencyOverrideMultiplier | * | 0x4 | { 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Value.}
  gPlatformFspPkgTokenSpaceGuid.SaPcieItbtRpNonSnoopLatencyOverrideValue      | * | 0x8 | { 0x00C8, 0x00C8, 0x00C8, 0x00C8 }

  # !BSF NAME:{Force LTR Override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Force LTR Override.}
  gPlatformFspPkgTokenSpaceGuid.SaPcieItbtRpForceLtrOverride   | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Ltr Config Lock} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.SaPcieItbtRpLtrConfigLock      | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  #
  # SA Post-Mem Production Block End
  #

  #
  # CPU Post-Mem Production Block Start
  #
  # !BSF NAME:{Advanced Encryption Standard (AES) feature} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Advanced Encryption Standard (AES) feature; </b>0: Disable; <b>1: Enable}
  gPlatformFspPkgTokenSpaceGuid.AesEnable                   | * | 0x01 | 0x01

  # !BSF NAME:{Power State 3 enable/disable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Power State 3 enable/disable; 0: Disable; <b>1: Enable</b>. For all VR Indexes}
  gPlatformFspPkgTokenSpaceGuid.Psi3Enable                  | * | 0x05 | {0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Power State 4 enable/disable}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Power State 4 enable/disable; 0: Disable; <b>1: Enable</b>.For all VR Indexes}
  gPlatformFspPkgTokenSpaceGuid.Psi4Enable                  | * | 0x05 | {0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Imon slope correction}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: Imon slope correction. Specified in 1/100 increment values. Range is 0-200. 125 = 1.25. <b>0: Auto</b>.For all VR Indexes}
  gPlatformFspPkgTokenSpaceGuid.ImonSlope                   | * | 0x0A | {0x0, 0x0, 0x0, 0x0, 0x0}

  # !BSF NAME:{Imon offset correction}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: Imon offset correction. Value is a 2's complement signed integer. Units 1/1000, Range 0-63999. For an offset = 12.580, use 12580. <b>0: Auto</b>}
  gPlatformFspPkgTokenSpaceGuid.ImonOffset                  | * | 0x0A | {0x0, 0x0, 0x0, 0x0, 0x0}

  # !BSF NAME:{Enable/Disable BIOS configuration of VR}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable BIOS configuration of VR; <b>0: Disable</b>; 1: Enable.For all VR Indexes}
  gPlatformFspPkgTokenSpaceGuid.VrConfigEnable              | * | 0x05 | {0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Thermal Design Current enable/disable}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Thermal Design Current enable/disable; <b>0: Disable</b>; 1: Enable.For all VR Indexes}
  gPlatformFspPkgTokenSpaceGuid.TdcEnable                   | * | 0x05 | {0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{HECI3 state} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Thermal Design Current time window. Defined in milli seconds. Valid Values 1 - 1ms , 2 - 2ms , 3 - 3ms , 4 - 4ms , 5 - 5ms , 6 - 6ms , 7 - 7ms , 8 - 8ms , 10 - 10ms.For all VR Indexe}
  gPlatformFspPkgTokenSpaceGuid.TdcTimeWindow               | * | 0x05 | {0x01, 0x01, 0x01, 0x01, 0x01}

  # !BSF NAME:{Thermal Design Current Lock}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Thermal Design Current Lock; <b>0: Disable</b>; 1: Enable.For all VR Indexes}
  gPlatformFspPkgTokenSpaceGuid.TdcLock                     | * | 0x05 | {0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Platform Psys slope correction}
  # !BSF TYPE:{EditNum, HEX, (0x00,0xC8)}
  # !BSF HELP:{PCODE MMIO Mailbox: Platform Psys slope correction. <b>0 - Auto</b> Specified in 1/100 increment values. Range is 0-200. 125 = 1.25}
  gPlatformFspPkgTokenSpaceGuid.PsysSlope                   | * | 0x01 | 0x00

  # !BSF NAME:{Platform Psys offset correction}
  # !BSF TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Platform Psys offset correction. <b>0 - Auto</b> Units 1/4, Range 0-255. Value of 100 = 100/4 = 25 offset}
  gPlatformFspPkgTokenSpaceGuid.PsysOffset                  | * | 0x01 | 0x00

  # !BSF NAME:{Acoustic Noise Mitigation feature}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Acoustic Noise Mitigation feature. <b>0: Disabled</b>; 1: Enabled}
  gPlatformFspPkgTokenSpaceGuid.AcousticNoiseMitigation     | * | 0x01 | 0x00

  # !BSF NAME:{Disable Fast Slew Rate for Deep Package C States for VR IA domain}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable Fast Slew Rate for Deep Package C States based on Acoustic Noise Mitigation feature enabled. <b>0: False</b>; 1: True}
  gPlatformFspPkgTokenSpaceGuid.FastPkgCRampDisableIa       | * | 0x01 | 0x00

  # !BSF NAME:{Slew Rate configuration for Deep Package C States for VR IA domain}
  # !BSF TYPE:{Combo} OPTION:{0: Fast/2, 1: Fast/4, 2: Fast/8, 3: Fast/16}
  # !BSF HELP:{Slew Rate configuration for Deep Package C States for VR IA domain based on Acoustic Noise Mitigation feature enabled. <b>0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16}
  gPlatformFspPkgTokenSpaceGuid.SlowSlewRateForIa           | * | 0x01 | 0x00

  # !BSF NAME:{Slew Rate configuration for Deep Package C States for VR GT domain}
  # !BSF TYPE:{Combo} OPTION:{0: Fast/2, 1: Fast/4, 2: Fast/8, 3: Fast/16}
  # !BSF HELP:{Slew Rate configuration for Deep Package C States for VR GT domain based on Acoustic Noise Mitigation feature enabled. <b>0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16}
  gPlatformFspPkgTokenSpaceGuid.SlowSlewRateForGt           | * | 0x01 | 0x00

  # !BSF NAME:{Slew Rate configuration for Deep Package C States for VR SA domain}
  # !BSF TYPE:{Combo} OPTION:{0: Fast/2, 1: Fast/4, 2: Fast/8, 3: Fast/16}
  # !BSF HELP:{Slew Rate configuration for Deep Package C States for VR SA domain based on Acoustic Noise Mitigation feature enabled. <b>0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16}
  gPlatformFspPkgTokenSpaceGuid.SlowSlewRateForSa           | * | 0x01 | 0x00

  # !BSF NAME:{Thermal Design Current current limit} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: Thermal Design Current current limit. Specified in 1/8A units. Range is 0-4095. 1000 = 125A. <b>0: Auto</b>. For all VR Indexes}
  gPlatformFspPkgTokenSpaceGuid.TdcCurrentLimit             | * | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{AcLoadline}TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: AcLoadline in 1/100 mOhms (ie. 1250 = 12.50 mOhm); Range is 0-6249. <b>Intel Recommended Defaults vary by domain and SKU.}
  gPlatformFspPkgTokenSpaceGuid.AcLoadline                  | * | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{DcLoadline} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: DcLoadline in 1/100 mOhms (ie. 1250 = 12.50 mOhm); Range is 0-6249.<b>Intel Recommended Defaults vary by domain and SKU.</b>}
  gPlatformFspPkgTokenSpaceGuid.DcLoadline                  | * | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{Power State 1 Threshold current} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: Power State 1 current cuttof in 1/4 Amp increments. Range is 0-128A.}
  gPlatformFspPkgTokenSpaceGuid.Psi1Threshold               | * | 0xA | { 80, 80, 80, 80, 80 }

  # !BSF NAME:{Power State 2 Threshold current} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: Power State 2 current cuttof in 1/4 Amp increments. Range is 0-128A.}
  gPlatformFspPkgTokenSpaceGuid.Psi2Threshold               | * | 0xA | { 20, 20, 20, 20, 20 }

  # !BSF NAME:{Power State 3 Threshold current} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: Power State 3 current cuttof in 1/4 Amp increments. Range is 0-128A.}
  gPlatformFspPkgTokenSpaceGuid.Psi3Threshold               | * | 0xA | { 4, 4, 4, 4, 4 }

  # !BSF NAME:{Icc Max limit} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: VR Icc Max limit. 0-255A in 1/4 A units. 400 = 100A}
  gPlatformFspPkgTokenSpaceGuid.IccMax                      | * | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{VR Voltage Limit} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{PCODE MMIO Mailbox: VR Voltage Limit. Range is 0-7999mV.}
  gPlatformFspPkgTokenSpaceGuid.VrVoltageLimit              | * | 0xA | {0x0 , 0x0, 0x0 , 0x0 , 0x0}

  # !BSF NAME:{Disable Fast Slew Rate for Deep Package C States for VR GT domain}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable Fast Slew Rate for Deep Package C States based on Acoustic Noise Mitigation feature enabled. <b>0: False</b>; 1: True}
  gPlatformFspPkgTokenSpaceGuid.FastPkgCRampDisableGt       | * | 0x01 | 0x00

  # !BSF NAME:{Disable Fast Slew Rate for Deep Package C States for VR SA domain}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable Fast Slew Rate for Deep Package C States based on Acoustic Noise Mitigation feature enabled. <b>0: False</b>; 1: True}
  gPlatformFspPkgTokenSpaceGuid.FastPkgCRampDisableSa       | * | 0x01 | 0x00

  # !BSF NAME:{Enable VR specific mailbox command} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{VR specific mailbox commands. <b>00b - no VR specific command sent.</b>  01b - A VR mailbox command specifically for the MPS IMPV8 VR will be sent. 10b - VR specific command sent for PS4 exit issue. 11b - Reserved.}
  gPlatformFspPkgTokenSpaceGuid.SendVrMbxCmd                | * | 0x01 | 0x00

  # !BSF NAME:{Reserved} TYPE:{NULL}
  # !BSF HELP:{Reserved}
  gPlatformFspPkgTokenSpaceGuid.Reserved2                   | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable TXT} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable TXT; 0: Disable; <b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.TxtEnable                   | * | 0x01 | 0

  # !BSF NAME:{Skip Multi-Processor Initialization} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When this is skipped, boot loader must initialize processors before SilicionInit API. </b>0: Initialize; <b>1: Skip}
  gPlatformFspPkgTokenSpaceGuid.SkipMpInit                  | * | 0x01 | 0x00

  # !BSF NAME:{FIVR RFI Frequency}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Set the desired RFI frequency, in increments of 100KHz. <b>0: Auto</b>. Range varies based on XTAL clock: 0-1918 (Up to 191.8HMz) for 24MHz clock; 0-1535 (Up to 153.5MHz) for 19MHz clock.}
  gPlatformFspPkgTokenSpaceGuid.FivrRfiFrequency            | * | 0x02 | 0x00

  # !BSF NAME:{FIVR RFI Spread Spectrum}
  # !BSF TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{PCODE MMIO Mailbox: FIVR RFI Spread Spectrum, in 0.1% increments. <b>0: 0%</b>; Range: 0.0% to 10.0% (0-100).}
  gPlatformFspPkgTokenSpaceGuid.FivrSpreadSpectrum          | * | 0x01 | 0x00

  # !BSF NAME:{Disable Fast Slew Rate for Deep Package C States for VR FIVR domain}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable Fast Slew Rate for Deep Package C States based on Acoustic Noise Mitigation feature enabled. <b>0: False</b>; 1: True}
  gPlatformFspPkgTokenSpaceGuid.FastPkgCRampDisableFivr     | * | 0x01 | 0x00

  # !BSF NAME:{Slew Rate configuration for Deep Package C States for VR FIVR domain}
  # !BSF TYPE:{Combo} OPTION:{0: Fast/2, 1: Fast/4, 2: Fast/8, 3: Fast/16}
  # !BSF HELP:{Slew Rate configuration for Deep Package C States for VR FIVR domain based on Acoustic Noise Mitigation feature enabled. <b>0: Fast/2</b>; 1: Fast/4; 2: Fast/8; 3: Fast/16}
  gPlatformFspPkgTokenSpaceGuid.SlowSlewRateForFivr         | * | 0x01 | 0x00

  # !BSF NAME:{ UFS Soft Strap Start Address}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{ UFS Soft Strap Start Address, Value will be based on the CSE IFWI Layout}
  gPlatformFspPkgTokenSpaceGuid.UfsStrapAddress             | * | 0x04 | 0x00000000

  # !BSF NAME:{CpuBistData} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Pointer CPU BIST Data}
  gPlatformFspPkgTokenSpaceGuid.CpuBistData                 | * | 0x4 | 0

  # !BSF NAME:{CpuMpPpi} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Pointer for CpuMpPpi}
  gPlatformFspPkgTokenSpaceGuid.CpuMpPpi                     | * | 0x4 | 0

  # !BSF NAME:{CpuMpHob} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Pointer for CpuMpHob. This is optional data buffer for CpuMpPpi usage.}
  gPlatformFspPkgTokenSpaceGuid.CpuMpHob                     | * | 0x4 | 0

  gPlatformFspPkgTokenSpaceGuid.CpuPostMemRsvd                | * | 0x10 | {0x00}

  # !BSF NAME:{PpinSupport to view Protected Processor Inventory Number}
  # !BSF TYPE:{Combo} OPTION:{0: Disable, 1: Enable, 2: Auto}
  # !BSF HELP:{Enable or Disable or Auto (Based on End of Manufacturing flag. Disabled if this flag is set) for PPIN Support}
  gPlatformFspPkgTokenSpaceGuid.PpinSupport                 | * | 0x1 | 0x00

  # !BSF NAME:{Enable or Disable Minimum Voltage Override} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or disable Minimum Voltage overrides ; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.EnableMinVoltageOverride    | * | 0x01 | 0x0

  # !BSF NAME:{Min Voltage for Runtime }
  # !BSF TYPE:{EditNum, HEX, (0x00,0x7CF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Minimum voltage for runtime. Valid if EnableMinVoltageOverride = 1. Range 0 to 1999mV. <b> 0: 0mV </b>}
  gPlatformFspPkgTokenSpaceGuid.MinVoltageRuntime           | * | 0x02 | 0x00

  # !BSF NAME:{Base of memory region allocated for Processor Trace}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Base address of memory region allocated for Processor Trace. Processor Trace requires 2^N alignment and size in bytes per thread, from 4KB to 128MB. <b>0: Disable</b>}
  gPlatformFspPkgTokenSpaceGuid.ProcessorTraceMemBase       | * | 0x08 | 0x0000000000000000

  # !BSF NAME:{Memory region allocation for Processor Trace}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Length in bytes of memory region allocated for Processor Trace. Processor Trace requires 2^N alignment and size in bytes per thread, from 4KB to 128MB. <b>0: Disable</b>}
  gPlatformFspPkgTokenSpaceGuid.ProcessorTraceMemLength     | * | 0x04 | 0x00000000

  # !BSF NAME:{Min Voltage for C8 }
  # !BSF TYPE:{EditNum, HEX, (0x00,0x7CF)}
  # !BSF HELP:{PCODE MMIO Mailbox: Minimum voltage for C8. Valid if EnableMinVoltageOverride = 1. Range 0 to 1999mV. <b> 0: 0mV </b>}
  gPlatformFspPkgTokenSpaceGuid.MinVoltageC8                | * | 0x02 | 0x00

  # !BSF NAME:{ReservedCpuPostMemProduction} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for CPU Post-Mem Production}
  gPlatformFspPkgTokenSpaceGuid.ReservedCpuPostMemProduction | * | 0x8 | {0x00}

  # !BSF NAME:{AC Split Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable #AC check on split lock. <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.AcSplitLock                  | * | 0x1 | 0x0

  #
  # CPU Post-Mem Production Block End
  #

  #
  #  PCH Silicon Offset start
  #
  # !BSF NAME:{PCH Master Clock Gating Control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Provide a master control for clock gating for all PCH devices, 0: Disabled; 1: Default}
  gPlatformFspPkgTokenSpaceGuid.PchMasterClockGating        | * | 0x01 | 0x00

  # !BSF NAME:{PCH Master Power Gating Control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Provide a master control for pwoer gating for all PCH devices, 0: Disabled; 1: Default}
  gPlatformFspPkgTokenSpaceGuid.PchMasterPowerGating        | * | 0x01 | 0x00

  # !BSF NAME:{Sci Pin Mux Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable Sci Gpio Pin Mux. <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.SciPinMuxEnable             | * | 0x01 | 0x00


  # !BSF PAGE:{PCH2}
  # !BSF NAME:{Enable Power Optimizer} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable DMI Power Optimizer on PCH side.}
  gPlatformFspPkgTokenSpaceGuid.PchPwrOptEnable             | * | 0x01 | 0x00

  # !BSF NAME:{PCH Flash Protection Ranges Write Enble} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{Write or erase is blocked by hardware.}
  gPlatformFspPkgTokenSpaceGuid.PchWriteProtectionEnable    | * | 0x05 | { 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH Flash Protection Ranges Read Enble} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{Read is blocked by hardware.}
  gPlatformFspPkgTokenSpaceGuid.PchReadProtectionEnable     | * | 0x05 | { 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH Protect Range Limit} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Left shifted address by 12 bits with address bits 11:0 are assumed to be FFFh for limit comparison.}
  gPlatformFspPkgTokenSpaceGuid.PchProtectedRangeLimit      | * | 0x0A | { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{PCH Protect Range Base} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Left shifted address by 12 bits with address bits 11:0 are assumed to be 0.}
  gPlatformFspPkgTokenSpaceGuid.PchProtectedRangeBase       | * | 0x0A | { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{Enable Pme} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable Azalia wake-on-ring.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaPme                   | * | 0x01 | 0x00

  # !BSF NAME:{HD Audio Link Frequency} TYPE:{Combo} OPTION:{0: 6MHz, 1: 12MHz, 2: 24MHz}
  # !BSF HELP:{HDA Link Freq (PCH_HDAUDIO_LINK_FREQUENCY enum): 0: 6MHz, 1: 12MHz, 2: 24MHz.}
  gPlatformFspPkgTokenSpaceGuid.PchHdaLinkFrequency         | * | 0x01 | 0x02

  # !BSF NAME:{PchPostMemRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for PCH Post-Mem}
  gPlatformFspPkgTokenSpaceGuid.PchPostMemRsvd4              | * | 0x3 | {0x00}

  # !BSF NAME:{Enable PCH Io Apic Entry 24-119} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchIoApicEntry24_119        | * | 0x01 | 0x01

  # !BSF NAME:{PCH Io Apic ID} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{This member determines IOAPIC ID. Default is 0x02.}
  gPlatformFspPkgTokenSpaceGuid.PchIoApicId                 | * | 0x01 | 0x02

  # !BSF NAME:{PCH PSE Log Output Channel} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Set PSE Log Output Channel. 0: internal memory; 1-6: UART channels; Other: shut down}
  gPlatformFspPkgTokenSpaceGuid.PchPseLogOutputChannel      | * | 0x04 | 0x00000000

  # !BSF NAME:{PCH PSE Log Output Size} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Set PSE Log Output Size}
  gPlatformFspPkgTokenSpaceGuid.PchPseLogOutputSize         | * | 0x02 | 0x0000

  # !BSF NAME:{PCH PSE Log Output Offset} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Set PSE Log Output Offset}
  gPlatformFspPkgTokenSpaceGuid.PchPseLogOutputOffset       | * | 0x02 | 0x0000

  # !BSF NAME:{Enable PCH PSE I2S pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Set if PSE I2S native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseI2sEnable             | * | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{PchPseI2sTxPinMux} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select PSE I2S Tx pin muxing. Refer to GPIO_*_MUXING_PSE_I2Sx_TXD* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseI2sTxPinMux           | * | 0x08 | { 0x00000000, 0x00000000 }

  # !BSF NAME:{PchPseI2sRxPinMux} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select PSE I2S Rx pin muxing. Refer to GPIO_*_MUXING_PSE_I2Sx_RXD* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseI2sRxPinMux           | * | 0x08 | { 0x00000000, 0x00000000 }

  # !BSF NAME:{PchPseI2sSfrmPinMux} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select PSE I2S Sfrm pin muxing. Refer to GPIO_*_MUXING_PSE_I2Sx_SFRM* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseI2sSfrmPinMux           | * | 0x08 | { 0x00000000, 0x00000000 }

  # !BSF NAME:{PchPseI2sSclkPinMux} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select PSE I2S Sclk pin muxing. Refer to GPIO_*_MUXING_PSE_I2Sx_SCLK* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseI2sSclkPinMux           | * | 0x08 | { 0x00000000, 0x00000000 }

  # !BSF NAME:{Enable PCH PSE PWM pins assigned} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Set if PSE PWM native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPsePwmEnable             | * | 0x01 | 0x00

  # !BSF NAME:{PchPsePwmPinEnable} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Set PWM pin to PSE PWM native function. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPsePwmPinEnable          | * | 0x10 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{PchPsePwmPinMux} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select PSE Pwm pin muxing start from PWM0 to PWM15. Refer to GPIO_*_MUXING_PSE_PWM* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPsePwmPinMux             | * | 0x40 | { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}

  # !BSF NAME:{Enable PCH PSE UART pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFF)}
  # !BSF HELP:{Set if PSE UART native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseUartEnable            | * | 0x06 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE HSUART pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Set if PSE HSUART native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseHsuartEnable          | * | 0x04 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE QEP pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Set if PSE QEP native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseQepEnable             | * | 0x04 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE DMA pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFFFF)}
  # !BSF HELP:{Set if PSE DMA native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseDmaEnable             | * | 0x03 | { 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE GBE pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Set if PSE GBE native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseGbeEnable             | * | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE I2C pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set if PSE I2C native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseI2cEnable             | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE SPI pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Set if PSE SPI native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseSpiEnable             | * | 0x04 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE SPI CS0 pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Set if PSE SPI CS0 pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseSpiCs0Enable          | * | 0x04 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE SPI CS1 pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Set if PSE SPI CS1 pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseSpiCs1Enable          | * | 0x04 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PchPseSpiMosiPinMux} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select PSE Spi Mosi pin muxing. Refer to GPIO_*_MUXING_PSE_SPIx_MOSI* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseSpiMosiPinMux           | * | 0x10 | { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }

  # !BSF NAME:{PchPseSpiMisoPinMux} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select PSE Spi Miso pin muxing. Refer to GPIO_*_MUXING_PSE_SPIx_MISO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseSpiMisoPinMux           | * | 0x10 | { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }

  # !BSF NAME:{PchPseSpiClkPinMux} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select PSE Spi Clk pin muxing. Refer to GPIO_*_MUXING_PSE_SPIx_SCLK* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseSpiClkPinMux           | * | 0x10 | { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }

  # !BSF NAME:{PchPseSpiCs0PinMux} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select PSE Spi Cs pin muxing. Refer to GPIO_*_MUXING_PSE_SPIx_Cs* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseSpiCs0PinMux           | * | 0x10 | { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }

  # !BSF NAME:{PchPseSpiCs1PinMux} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT32}
  # !BSF HELP:{Select PSE Spi Cs pin muxing. Refer to GPIO_*_MUXING_PSE_SPIx_Cs* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseSpiCs1PinMux           | * | 0x10 | { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }

  # !BSF NAME:{Enable PCH PSE ADC pins assigned} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Set if PSE ADC native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseAdcEnable             | * | 0x01 | 0x00

  # !BSF NAME:{Enable PCH PSE CAN pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Set if PSE CAN native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseCanEnable             | * | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE I2S sideband interrupt} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Set if PSE I2S are to be set to sideband interrupt. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseI2sSbInterruptEnable  | * | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE PWM sideband interrupt} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Set if PSE PWM are to be set to sideband interrupt. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPsePwmSbInterruptEnable  | * | 0x01 | 0x00

  # !BSF NAME:{Enable PCH PSE UART sideband interrupt} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFF)}
  # !BSF HELP:{Set if PSE UART are to be set to sideband interrupt. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseUartSbInterruptEnable  | * | 0x06 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE QEP sideband interrupt} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Set if PSE QEP are to be set to sideband interrupt. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseQepSbInterruptEnable  | * | 0x04 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE DMA sideband interrupt} TYPE:{EditNum, HEX, (0x0,0xFFFFFF)}
  # !BSF HELP:{Set if PSE DMA are to be set to sideband interrupt. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseDmaSbInterruptEnable  | * | 0x03 | { 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable PCH PSE I2C sideband interrupt} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set if PSE I2C are to be set to sideband interrupt. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseI2cSbInterruptEnable  | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE SPI sideband interrupt} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Set if PSE SPI are to be set to sideband interrupt. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseSpiSbInterruptEnable  | * | 0x04 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE ADC sideband interrupt} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Set if PSE ADC are to be set to sideband interrupt. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseAdcSbInterruptEnable  | * | 0x01 | 0x00

  # !BSF NAME:{Enable PCH PSE LH2OSE sideband interrupt} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Set if PSE LH2OSE are to be set to sideband interrupt. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseLh2PseSbInterruptEnable  | * | 0x01 | 0x01

  # !BSF NAME:{Enable PCH PSE CAN sideband interrupt} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Set if PSE CAN are to be set to sideband interrupt. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseCanSbInterruptEnable  | * | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE Timed GPIO pins assigned} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Set if PSE Timed GPIO native pins and ownership are to be enabled by BIOS. 0: Disable/pins are not owned by PSE/host; 1: Pins are muxed to PSE IP, the IO is owned by PSE; 2: Pins are muxed to PSE IP, the IO is owned by host;}
  gPlatformFspPkgTokenSpaceGuid.PchPseTimedGpioEnable       | * | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Enable PCH PSE Timed GPIO 20 pins allocation} TYPE:{EditNum, HEX, (0x0,0xFFFF)}
  # !BSF HELP:{Allocate 20 pins for PCH PSE Timed GPIO. 0: Top 20 pins; 1: Mid 20 pins; 2: Lower 20 pins.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTimedGpioPinAllocation  | * | 0x02 | { 0x03, 0x03 }

  # !BSF NAME:{Enable PCH PSE Timed GPIO Pin to PSE TGPIO native function} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Set TGPIO pin to PSE TGPIO native function. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTimedGpioPinEnable  | * | 0x3C | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Pch Pse Tgpio6 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio6PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio7 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio7PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio8 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio8PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio9 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio9PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio10 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio10PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio11 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio11PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio12 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio12PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio13 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio13PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio14 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio14PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio15 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio15PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio16 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio16PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio17 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio17PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio18 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio18PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Pch Pse Tgpio19 Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select PSE Timed Gpio pin muxing. Refer to GPIO_*_MUXING_PSE_TGPIO* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PchPseTgpio19PinMux          | * | 0x04 | 0x00000000

  # !BSF NAME:{Enable PCH Lan LTR capabilty of PCH internal LAN} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchLanLtrEnable             | * | 0x01 | 0x01

  # !BSF NAME:{Enable LOCKDOWN BIOS LOCK} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable the BIOS Lock feature and set EISS bit (D31:F5:RegDCh[5]) for the BIOS region protection.}
  gPlatformFspPkgTokenSpaceGuid.PchLockDownBiosLock         | * | 0x01 | 0x00

  # !BSF NAME:{PCH Compatibility Revision ID} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This member describes whether or not the CRID feature of PCH should be enabled.}
  gPlatformFspPkgTokenSpaceGuid.PchCrid                     | * | 0x01 | 0x00

  # !BSF NAME:{RTC BIOS Interface Lock}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable RTC BIOS interface lock. When set, prevents RTC TS (BUC.TS) from being changed.}
  gPlatformFspPkgTokenSpaceGuid.RtcBiosInterfaceLock        | * | 0x01 | 0x01

  # !BSF NAME:{RTC Cmos Memory Lock}
  # !BSF TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable RTC lower and upper 128 byte Lock bits to lock Bytes 38h-3Fh in the upper and and lower 128-byte bank of RTC RAM.}
  gPlatformFspPkgTokenSpaceGuid.RtcMemoryLock               | * | 0x01 | 0x01

  # !BSF NAME:{Enable PCIE RP HotPlug} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the root port is hot plug available.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpHotPlug               | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCIE RP Pm Sci} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the root port power manager SCI is enabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpPmSci                 | * | 0x18 | { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{Enable PCIE RP Transmitter Half Swing} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Transmitter Half Swing is enabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpTransmitterHalfSwing  | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCIE RP Clk Req Detect} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Probe CLKREQ# signal before enabling CLKREQ# based power management.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpClkReqDetect          | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Advanced Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Advanced Error Reporting is enabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpAdvancedErrorReporting   | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Unsupported Request Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Unsupported Request Report is enabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpUnsupportedRequestReport | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Fatal Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Fatal Error Report is enabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpFatalErrorReport      | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP No Fatal Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the No Fatal Error Report is enabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpNoFatalErrorReport    | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Correctable Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Correctable Error Report is enabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpCorrectableErrorReport   | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP System Error On Fatal Error} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the System Error on Fatal Error is enabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpSystemErrorOnFatalError  | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP System Error On Non Fatal Error} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the System Error on Non Fatal Error is enabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpSystemErrorOnNonFatalError | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP System Error On Correctable Error} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the System Error on Correctable Error is enabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpSystemErrorOnCorrectableError | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Max Payload} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Max Payload Size supported, Default 128B, see enum PCH_PCIE_MAX_PAYLOAD.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpMaxPayload            | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Touch Host Controller Port 0 Assignment} TYPE:{Combo} OPTION:{0x0:ThcAssignmentNone, 0x1:ThcAssignmentThc0}
  # !BSF HELP:{Assign THC Port 0}
  gPlatformFspPkgTokenSpaceGuid.ThcPort0Assignment          | * | 0x01 | 0x1

  # !BSF NAME:{THC Port 0 Interrupt Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Set THC Port 0 Pin Muxing Value if signal can be enabled on multiple pads. Refer to GPIO_*_MUXING_THC_SPIx_INTB_* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.ThcPort0InterruptPinMuxing  | * | 0x04 | 0x0

  # !BSF NAME:{Touch Host Controller Port 1 Assignment} TYPE:{Combo} OPTION:{0x0:ThcAssignmentNone, 0x1:ThcPort1AssignmentThc0, 0x2:ThcAssignmentThc1}
  # !BSF HELP:{Assign THC Port 1}
  gPlatformFspPkgTokenSpaceGuid.ThcPort1Assignment          | * | 0x01 | 0x2

  # !BSF NAME:{Touch Host Controller Port 1 ReadFrequency} TYPE:{Combo} OPTION:{0:2p1MHz,1:2p5Mz,2:3Mz,3:3p75Mz,4:5MHz,5:7p5MHz,6:15MHz,7:17MHz,8:20MHz,9:24MHz,10:30MHz}
  # !BSF HELP:{Set THC Port 1 Read Frequency (THC_PORT_FREQUENCY enum): 0:2p1MHz,1:2p5Mz,2:3Mz,3:3p75Mz,4:5MHz,5:7p5MHz,6:15MHz,7:17MHz,8:20MHz,9:24MHz,10:30MHz}
  gPlatformFspPkgTokenSpaceGuid.ThcPort1ReadFrequency       | * | 0x01 | 0x08

  # !BSF NAME:{Touch Host Controller Port 1 WriteFrequency} TYPE:{Combo} OPTION:{0:2p1MHz,1:2p5Mz,2:3Mz,3:3p75Mz,4:5MHz,5:7p5MHz,6:15MHz,7:17MHz,8:20MHz,9:24MHz,10:30MHz}
  # !BSF HELP:{Set THC Port 1 Write Frequency (THC_PORT_FREQUENCY enum): 0:2p1MHz,1:2p5Mz,2:3Mz,3:3p75Mz,4:5MHz,5:7p5MHz,6:15MHz,7:17MHz,8:20MHz,9:24MHz,10:30MHz}
  gPlatformFspPkgTokenSpaceGuid.ThcPort1WriteFrequency      | * | 0x01 | 0x08

  # !BSF NAME:{THC Port 1 Interrupt Pin Mux} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Set THC Port 1 Pin Muxing Value if signal can be enabled on multiple pads. Refer to GPIO_*_MUXING_THC_SPIx_INTB_* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.ThcPort1InterruptPinMuxing  | * | 0x04 | 0x0

  # !BSF NAME:{PCIE RP Pcie Speed} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Determines each PCIE Port speed capability. 0: Auto; 1: Gen1; 2: Gen2; 3: Gen3 (see: PCH_PCIE_SPEED).}
  gPlatformFspPkgTokenSpaceGuid.PcieRpPcieSpeed             | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Physical Slot Number} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicates the slot number for the root port. Default is the value as root port index.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpPhysicalSlotNumber    | * | 0x18 | { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17 }

  # !BSF NAME:{PCIE RP Completion Timeout} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{The root port completion timeout(see: PCH_PCIE_COMPLETION_TIMEOUT). Default is PchPcieCompletionTO_Default.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpCompletionTimeout     | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Aspm} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{The ASPM configuration of the root port (see: PCH_PCIE_ASPM_CONTROL). Default is PchPcieAspmAutoConfig.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpAspm                  | * | 0x18 | { 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 }

  # !BSF NAME:{PCIE RP L1 Substates} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{The L1 Substates configuration of the root port (see: PCH_PCIE_L1SUBSTATES_CONTROL). Default is PchPcieL1SubstatesL1_1_2.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpL1Substates           | * | 0x18 | { 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 }

  # !BSF NAME:{PCIE RP Ltr Enable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting Mechanism.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpLtrEnable             | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Ltr Config Lock} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpLtrConfigLock         | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIe override default settings for EQ} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Choose PCIe EQ method}
  gPlatformFspPkgTokenSpaceGuid.PcieEqOverrideDefault       | * | 0x1 | 0x00

  # !BSF NAME:{PCIe choose EQ method} TYPE:{Combo} OPTION:{0: HardwareEq, 1: FixedEq}
  # !BSF HELP:{Choose PCIe EQ method}
  gPlatformFspPkgTokenSpaceGuid.PcieEqMethod                | * | 0x1 | 0x00

  # !BSF NAME:{PCIe choose EQ mode} TYPE:{Combo} OPTION:{0: PresetEq, 1: CoefficientEq}
  # !BSF HELP:{Choose PCIe EQ mode}
  gPlatformFspPkgTokenSpaceGuid.PcieEqMode                  | * | 0x1 | 0x00

  # !BSF NAME:{PCIe EQ local transmitter override} Type:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable local transmitter override}
  gPlatformFspPkgTokenSpaceGuid.PcieEqLocalTransmitterOverrideEnable | * | 0x1 | 0x00

  # !BSF NAME:{PCIe number of valid list entries} TYPE:{EditNum, HEX, (0, 11)}
  # !BSF HELP:{Select number of presets or coefficients depending on the mode}
  gPlatformFspPkgTokenSpaceGuid.PcieEqPh3NumberOfPresetsOrCoefficients | * | 0x1 | 0x00

  # !BSF NAME:{PCIe pre-cursor coefficient list} TYPE:{EditNum, HEX, (0x0, 0x3F3F3F3F3F3F3F3F3F3F)}
  # !BSF HELP:{Provide a list of pre-cursor coefficients to be used during phase 3 EQ}
  gPlatformFspPkgTokenSpaceGuid.PcieEqPh3PreCursorList         | * | 0xA | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{PCIe post-cursor coefficient list} TYPE:{EditNum, HEX, (0, 0x3F3F3F3F3F3F3F3F3F3F)}
  # !BSF HELP:{Provide a list of post-cursor coefficients to be used during phase 3 EQ}
  gPlatformFspPkgTokenSpaceGuid.PcieEqPh3PostCursorList        | * | 0xA | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{PCIe preset list} TYPE:{EditNum, HEX, (0, 0x3F3F3F3F3F3F3F3F3F3F3F)}
  # !BSF HELP:{Provide a list of presets to be used during phase 3 EQ}
  gPlatformFspPkgTokenSpaceGuid.PcieEqPh3PresetList        | * | 0xB | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{PCIe EQ phase 1 downstream transmitter port preset} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Allows to select the downstream port preset value that will be used during phase 1 of equalization}
  gPlatformFspPkgTokenSpaceGuid.PcieEqPh1DownstreamPortTransmitterPreset  | * | 0x4 | 0x0

  # !BSF NAME:{PCIe EQ phase 1 upstream tranmitter port preset} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Allows to select the upstream port preset value that will be used during phase 1 of equalization}
  gPlatformFspPkgTokenSpaceGuid.PcieEqPh1UpstreamPortTransmitterPreset    | * | 0x4 | 0x0

  # !BSF NAME:{PCIe EQ phase 2 local transmitter override preset} Type:{EditNum, DEC, (0, 10)}
  # !BSF HELP:{Allows to select the value of the preset used during phase 2 local transmitter override}
  gPlatformFspPkgTokenSpaceGuid.PcieEqPh2LocalTransmitterOverridePreset | * | 0x1 | 0x0

  # !BSF NAME:{PCIE Enable Peer Memory Write} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This member describes whether Peer Memory Writes are enabled on the platform.}
  gPlatformFspPkgTokenSpaceGuid.PcieEnablePeerMemoryWrite   | * | 0x01 | 0x00

  # !BSF NAME:{PCIE Compliance Test Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Compliance Test Mode shall be enabled when using Compliance Load Board.}
  gPlatformFspPkgTokenSpaceGuid.PcieComplianceTestMode      | * | 0x01 | 0x00

  # !BSF NAME:{PCI Express Clock Gating} TYPE:{Combo}
  # !BSF OPTION:{0: POR, 1: Force Enable, 2: Force Disable}
  # !BSF HELP:{Enable/Disable Clock Gating, 0: PLATFORM_POR, 1: FORCE_ENABLE, 2: FORCE_DISABLE.}
  gPlatformFspPkgTokenSpaceGuid.TestPcieClockGating    | * | 0x01 | 0x00

  # !BSF NAME:{PCIE Rp Function Swap} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Allows BIOS to use root port function number swapping when root port of function 0 is disabled.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpFunctionSwap          | * | 0x01 | 0x01

  # !BSF NAME:{Enable/Disable PEG GEN3 Static EQ Phase1 programming} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Program Gen3 EQ Phase1 Static Presets. Disabled(0x0): Disable EQ Phase1 Static Presets Programming, Enabled(0x1)(Default): Enable  EQ Phase1 Static Presets Programming}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieGen3ProgramStaticEq      | * | 0x01 | 0x1

  # !BSF NAME:{Enable/Disable GEN4 Static EQ Phase1 programming} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Program Gen4 EQ Phase1 Static Presets. Disabled(0x0): Disable EQ Phase1 Static Presets Programming, Enabled(0x1)(Default): Enable  EQ Phase1 Static Presets Programming}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieGen4ProgramStaticEq      | * | 0x01 | 0x1

  # !BSF NAME:{PCH Pm PME_B0_S5_DIS} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When cleared (default), wake events from PME_B0_STS are allowed in S5 if PME_B0_EN = 1.}
  gPlatformFspPkgTokenSpaceGuid.PchPmPmeB0S5Dis             | * | 0x01 | 0x00

  # !BSF NAME:{PCIE IMR} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables Isolated Memory Region for PCIe.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpImrEnabled           | * | 0x01 | 0x01

  # !BSF NAME:{PCIE IMR port number} TYPE:{EditNum, HEX, (0x0,23)}
  # !BSF HELP:{Selects PCIE root port number for IMR feature.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpImrSelection         | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Wol Enable Override} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Corresponds to the WOL Enable Override bit in the General PM Configuration B (GEN_PMCON_B) register.}
  gPlatformFspPkgTokenSpaceGuid.PchPmWolEnableOverride      | * | 0x01 | 0x01

  # !BSF NAME:{PCH Pm Pcie Wake From DeepSx} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determine if enable PCIe to wake from deep Sx.}
  gPlatformFspPkgTokenSpaceGuid.PchPmPcieWakeFromDeepSx     | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm WoW lan Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determine if WLAN wake from Sx, corresponds to the HOST_WLAN_PP_EN bit in the PWRM_CFG3 register.}
  gPlatformFspPkgTokenSpaceGuid.PchPmWoWlanEnable           | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm WoW lan DeepSx Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determine if WLAN wake from DeepSx, corresponds to the DSX_WLAN_PP_EN bit in the PWRM_CFG3 register.}
  gPlatformFspPkgTokenSpaceGuid.PchPmWoWlanDeepSxEnable     | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Lan Wake From DeepSx} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Determine if enable LAN to wake from deep Sx.}
  gPlatformFspPkgTokenSpaceGuid.PchPmLanWakeFromDeepSx      | * | 0x01 | 0x01

  # !BSF NAME:{PCH Pm Deep Sx Pol} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Deep Sx Policy.}
  gPlatformFspPkgTokenSpaceGuid.PchPmDeepSxPol              | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Slp S3 Min Assert} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{SLP_S3 Minimum Assertion Width Policy. Default is PchSlpS350ms.}
  gPlatformFspPkgTokenSpaceGuid.PchPmSlpS3MinAssert         | * | 0x01 | 0x03

  # !BSF NAME:{PCH Pm Slp S4 Min Assert} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{SLP_S4 Minimum Assertion Width Policy. Default is PchSlpS44s.}
  gPlatformFspPkgTokenSpaceGuid.PchPmSlpS4MinAssert         | * | 0x01 | 0x01

  # !BSF NAME:{PCH Pm Slp Sus Min Assert} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{SLP_SUS Minimum Assertion Width Policy. Default is PchSlpSus4s.}
  gPlatformFspPkgTokenSpaceGuid.PchPmSlpSusMinAssert        | * | 0x01 | 0x04

  # !BSF NAME:{PCH Pm Slp A Min Assert} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{SLP_A Minimum Assertion Width Policy. Default is PchSlpA2s.}
  gPlatformFspPkgTokenSpaceGuid.PchPmSlpAMinAssert          | * | 0x01 | 0x04

  # !BSF NAME:{USB Overcurrent Override for DbC} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This option overrides USB Over Current enablement state that USB OC will be disabled after enabling this option. Enable when DbC is used to avoid signaling conflicts.}
  gPlatformFspPkgTokenSpaceGuid.PchEnableDbcObs             | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Slp Strch Sus Up} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable SLP_X Stretching After SUS Well Power Up.}
  gPlatformFspPkgTokenSpaceGuid.PchPmSlpStrchSusUp          | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Slp Lan Low Dc} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable SLP_LAN# Low on DC Power.}
  gPlatformFspPkgTokenSpaceGuid.PchPmSlpLanLowDc            | * | 0x01 | 0x01

  # !BSF NAME:{PCH Pm Pwr Btn Override Period} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{PCH power button override period. 000b-4s, 001b-6s, 010b-8s, 011b-10s, 100b-12s, 101b-14s.}
  gPlatformFspPkgTokenSpaceGuid.PchPmPwrBtnOverridePeriod   | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Disable Dsx Ac Present Pulldown} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When Disable, PCH will internal pull down AC_PRESENT in deep SX and during G3 exit.}
  gPlatformFspPkgTokenSpaceGuid.PchPmDisableDsxAcPresentPulldown  | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Disable Native Power Button} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Power button native mode disable.}
  gPlatformFspPkgTokenSpaceGuid.PchPmDisableNativePowerButton  | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm ME_WAKE_STS} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Clear the ME_WAKE_STS bit in the Power and Reset Status (PRSTS) register.}
  gPlatformFspPkgTokenSpaceGuid.PchPmMeWakeSts              | * | 0x01 | 0x01

  # !BSF NAME:{PCH Pm WOL_OVR_WK_STS} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Clear the WOL_OVR_WK_STS bit in the Power and Reset Status (PRSTS) register.}
  gPlatformFspPkgTokenSpaceGuid.PchPmWolOvrWkSts            | * | 0x01 | 0x01

  # !BSF NAME:{PCH Pm Reset Power Cycle Duration} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Could be customized in the unit of second. Please refer to EDS for all support settings. 0 is default, 1 is 1 second, 2 is 2 seconds, ...}
  gPlatformFspPkgTokenSpaceGuid.PchPmPwrCycDur              | * | 0x01 | 0x00

  # !BSF NAME:{PCH Pm Pcie Pll Ssc} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Specifies the Pcie Pll Spread Spectrum Percentage. The default is 0xFF: AUTO - No BIOS override.}
  gPlatformFspPkgTokenSpaceGuid.PchPmPciePllSsc             | * | 0x01 | 0xFF

  # !BSF NAME:{PCH Legacy IO Low Latency Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set to enable low latency of legacy IO. <b>0: Disable</b>, 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.PchLegacyIoLowLatency       | * | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Pwr Opt Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{SATA Power Optimizer on PCH side.}
  gPlatformFspPkgTokenSpaceGuid.SataPwrOptEnable            | * | 0x01 | 0x00

  # !BSF NAME:{PCH Sata eSATA Speed Limit} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When enabled, BIOS will configure the PxSCTL.SPD to 2 to limit the eSATA port speed.}
  gPlatformFspPkgTokenSpaceGuid.EsataSpeedLimit             | * | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Speed Limit} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Indicates the maximum speed the SATA controller can support 0h: PchSataSpeedDefault.}
  gPlatformFspPkgTokenSpaceGuid.SataSpeedLimit              | * | 0x01 | 0x00

  # !BSF NAME:{Enable SATA Port HotPlug} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable SATA Port HotPlug.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsHotPlug            | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port Interlock Sw} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable SATA Port Interlock Sw.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsInterlockSw        | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port External} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable SATA Port External.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsExternal           | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port SpinUp} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable the COMRESET initialization Sequence to the device.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsSpinUp             | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port Solid State Drive} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: HDD; 1: SSD.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsSolidStateDrive    | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port Enable Dito Config} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable DEVSLP Idle Timeout settings (DmVal, DitoVal).}
  gPlatformFspPkgTokenSpaceGuid.SataPortsEnableDitoConfig   | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port DmVal} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{DITO multiplier. Default is 15.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsDmVal              | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port DmVal} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{DEVSLP Idle Timeout (DITO), Default is 625.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsDitoVal            | * | 0x10 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port ZpOdd} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Support zero power ODD.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsZpOdd              | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{Enable SATA Port RxPolarity} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Reverse RxPolarity.}
  gPlatformFspPkgTokenSpaceGuid.SataPortsRxPolarity         | * | 0x08 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{PCH Sata Rst Raid Alternate Id} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable RAID Alternate ID.}
  gPlatformFspPkgTokenSpaceGuid.SataRstRaidDeviceId         | * | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Rst Raid0} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RAID0.}
  gPlatformFspPkgTokenSpaceGuid.SataRstRaid0                | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Raid1} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RAID1.}
  gPlatformFspPkgTokenSpaceGuid.SataRstRaid1                | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Raid10} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RAID10.}
  gPlatformFspPkgTokenSpaceGuid.SataRstRaid10               | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Raid5} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RAID5.}
  gPlatformFspPkgTokenSpaceGuid.SataRstRaid5                | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Irrt} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Intel Rapid Recovery Technology.}
  gPlatformFspPkgTokenSpaceGuid.SataRstIrrt                 | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Orom Ui Banner} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{OROM UI and BANNER.}
  gPlatformFspPkgTokenSpaceGuid.SataRstOromUiBanner         | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Orom Ui Delay} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{00b: 2 secs; 01b: 4 secs; 10b: 6 secs; 11: 8 secs (see: PCH_SATA_OROM_DELAY).}
  gPlatformFspPkgTokenSpaceGuid.SataRstOromUiDelay          | * | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Rst Hdd Unlock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Indicates that the HDD password unlock in the OS is enabled.}
  gPlatformFspPkgTokenSpaceGuid.SataRstHddUnlock            | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Led Locate} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Indicates that the LED/SGPIO hardware is attached and ping to locate feature is enabled on the OS.}
  gPlatformFspPkgTokenSpaceGuid.SataRstLedLocate            | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Irrt Only} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Allow only IRRT drives to span internal and external ports.}
  gPlatformFspPkgTokenSpaceGuid.SataRstIrrtOnly             | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Smart Storage} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{RST Smart Storage caching Bit.}
  gPlatformFspPkgTokenSpaceGuid.SataRstSmartStorage         | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Pcie Storage Remap enable} TYPE:{EditNum, HEX, (0x00,0xFFFFFF)}
  # !BSF HELP:{Enable Intel RST for PCIe Storage remapping.}
  gPlatformFspPkgTokenSpaceGuid.SataRstPcieEnable           | * | 0x03 | { 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH Sata Rst Pcie Storage Port} TYPE:{EditNum, HEX, (0x00,0xFFFFFF)}
  # !BSF HELP:{Intel RST for PCIe Storage remapping - PCIe Port Selection (1-based, 0 = autodetect).}
  gPlatformFspPkgTokenSpaceGuid.SataRstPcieStoragePort      | * | 0x03 | { 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCH Sata Rst Pcie Device Reset Delay} TYPE:{EditNum, HEX, (0x00,0xFFFFFF)}
  # !BSF HELP:{PCIe Storage Device Reset Delay in milliseconds. Default value is 100ms}
  gPlatformFspPkgTokenSpaceGuid.SataRstPcieDeviceResetDelay | * | 0x03 | { 100, 100, 100 }

  # !BSF NAME:{UFS enable/disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF_HELP:{Enable/Disable UFS controller}
  gPlatformFspPkgTokenSpaceGuid.UfsEnable                   | * | 0x02 | {0, 0}

  # !BSF NAME:{IEH Mode} TYPE:{Combo} OPTION:{0: Bypass, 1:Enable}
  # !BSF HELP:{Integrated Error Handler Mode, 0: Bypass, 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.IehMode | * | 0x01 | 0x00

  # !BSF NAME:{PSF Tcc} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Psf Tcc (Time Coordinated Computing) Enable will decrease psf transaction latency by disable some psf power management features, 0: Disable, 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.PsfTccEnable | * | 0x01 | 0x00

  # !BSF NAME:{Tcc Tuning enable/disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Tcc (Time Coordinated Computing) Tuning Enabled}
  gPlatformFspPkgTokenSpaceGuid.TccTuningEnable | * | 0x01 | 0x00

  # !BSF NAME:{Tcc Register File Base Address} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Tcc (Time Coordinated Computing) Register File Base Address}
  gPlatformFspPkgTokenSpaceGuid.TccConfigBase | * | 0x04 | 0x00000000

  # !BSF NAME:{Tcc Register File Size} TYPE:{EditNum, HEX, (0x0,0xFFFFFFFF)}
  # !BSF HELP:{Tcc (Time Coordinated Computing) Register File Size}
  gPlatformFspPkgTokenSpaceGuid.TccConfigSize | * | 0x04 | 0x00000000

  # !BSF NAME:{Fusa Display Configuration} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Fusa (Functional Safety) Enable Fusa Feature on Display, 0: Disable, 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.DisplayFusaConfigEnable     | * | 0x01 | 0x01

  # !BSF NAME:{Fusa Graphics Configuration} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Fusa (Functional Safety) Enable Fusa Feature on Graphics, 0: Disable, 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.GraphicFusaConfigEnable     | * | 0x01 | 0x01

  # !BSF NAME:{Fusa Opio Configuration} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Fusa (Functional Safety) Enable Fusa Feature on Opio, 0: Disable, 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.OpioFusaConfigEnable        | * | 0x01 | 0x01

  # !BSF NAME:{Fusa Psf Configuration} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Fusa (Functional Safety) Enable Fusa Feature on Psf, 0: Disable, 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.PsfFusaConfigEnable         | * | 0x01 | 0x01

  # !BSF NAME:{Thermal Throttling Custimized T0Level Value} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Custimized T0Level value.}
  gPlatformFspPkgTokenSpaceGuid.PchT0Level                  | * | 0x02 | 0x0000

  # !BSF NAME:{Thermal Throttling Custimized T1Level Value} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Custimized T1Level value.}
  gPlatformFspPkgTokenSpaceGuid.PchT1Level                  | * | 0x02 | 0x0000

  # !BSF NAME:{Thermal Throttling Custimized T2Level Value} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Custimized T2Level value.}
  gPlatformFspPkgTokenSpaceGuid.PchT2Level                  | * | 0x02 | 0x0000

  # !BSF NAME:{Enable The Thermal Throttle} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable the thermal throttle function.}
  gPlatformFspPkgTokenSpaceGuid.PchTTEnable                 | * | 0x01 | 0x00

  # !BSF NAME:{PMSync State 13} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When set to 1 and the programmed GPIO pin is a 1, then PMSync state 13 will force at least T2 state.}
  gPlatformFspPkgTokenSpaceGuid.PchTTState13Enable          | * | 0x01 | 0x00

  # !BSF NAME:{Thermal Throttle Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Thermal Throttle Lock.}
  gPlatformFspPkgTokenSpaceGuid.PchTTLock                   | * | 0x01 | 0x00

  # !BSF NAME:{Thermal Throttling Suggested Setting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Thermal Throttling Suggested Setting.}
  gPlatformFspPkgTokenSpaceGuid.TTSuggestedSetting          | * | 0x01 | 0x01

  # !BSF NAME:{Enable PCH Cross Throttling} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable PCH Cross Throttling}
  gPlatformFspPkgTokenSpaceGuid.TTCrossThrottling           | * | 0x01 | 0x01

  # !BSF NAME:{DMI Thermal Sensor Autonomous Width Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{DMI Thermal Sensor Autonomous Width Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchDmiTsawEn                | * | 0x01 | 0x00

  # !BSF NAME:{DMI Thermal Sensor Suggested Setting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{DMT thermal sensor suggested representative values.}
  gPlatformFspPkgTokenSpaceGuid.DmiSuggestedSetting         | * | 0x01 | 0x01

  # !BSF NAME:{Thermal Sensor 0 Target Width} TYPE:{Combo}
  # !BSF OPTION:{0:x1, 1:x2, 2:x4, 3:x8, 4:x16}
  # !BSF HELP:{Thermal Sensor 0 Target Width.}
  gPlatformFspPkgTokenSpaceGuid.DmiTS0TW                    | * | 0x01 | 0x00

  # !BSF NAME:{Thermal Sensor 1 Target Width} TYPE:{Combo}
  # !BSF OPTION:{0:x1, 1:x2, 2:x4, 3:x8, 4:x16}
  # !BSF HELP:{Thermal Sensor 1 Target Width.}
  gPlatformFspPkgTokenSpaceGuid.DmiTS1TW                    | * | 0x01 | 0x00

  # !BSF NAME:{Thermal Sensor 2 Target Width} TYPE:{Combo}
  # !BSF OPTION:{0:x1, 1:x2, 2:x4, 3:x8, 4:x16}
  # !BSF HELP:{Thermal Sensor 2 Target Width.}
  gPlatformFspPkgTokenSpaceGuid.DmiTS2TW                    | * | 0x01 | 0x00

  # !BSF NAME:{Thermal Sensor 3 Target Width} TYPE:{Combo}
  # !BSF OPTION:{0:x1, 1:x2, 2:x4, 3:x8, 4:x16}
  # !BSF HELP:{Thermal Sensor 3 Target Width.}
  gPlatformFspPkgTokenSpaceGuid.DmiTS3TW                    | * | 0x01 | 0x00

  # !BSF NAME:{Port 0 T1 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 0 T1 Multipler.}
  gPlatformFspPkgTokenSpaceGuid.SataP0T1M                   | * | 0x01 | 0x01

  # !BSF NAME:{Port 0 T2 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 0 T2 Multipler.}
  gPlatformFspPkgTokenSpaceGuid.SataP0T2M                   | * | 0x01 | 0x02

  # !BSF NAME:{Port 0 T3 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 0 T3 Multipler.}
  gPlatformFspPkgTokenSpaceGuid.SataP0T3M                   | * | 0x01 | 0x03

  # !BSF NAME:{Port 0 Tdispatch} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 0 Tdispatch.}
  gPlatformFspPkgTokenSpaceGuid.SataP0TDisp                 | * | 0x01 | 0x00

  # !BSF NAME:{Port 1 T1 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 1 T1 Multipler.}
  gPlatformFspPkgTokenSpaceGuid.SataP1T1M                   | * | 0x01 | 0x01

  # !BSF NAME:{Port 1 T2 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 1 T2 Multipler.}
  gPlatformFspPkgTokenSpaceGuid.SataP1T2M                   | * | 0x01 | 0x02

  # !BSF NAME:{Port 1 T3 Multipler} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 1 T3 Multipler.}
  gPlatformFspPkgTokenSpaceGuid.SataP1T3M                   | * | 0x01 | 0x03

  # !BSF NAME:{Port 1 Tdispatch} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 1 Tdispatch.}
  gPlatformFspPkgTokenSpaceGuid.SataP1TDisp                 | * | 0x01 | 0x00

  # !BSF NAME:{Port 0 Tinactive} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 0 Tinactive.}
  gPlatformFspPkgTokenSpaceGuid.SataP0Tinact                | * | 0x01 | 0x00

  # !BSF NAME:{Port 0 Alternate Fast Init Tdispatch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Port 0 Alternate Fast Init Tdispatch.}
  gPlatformFspPkgTokenSpaceGuid.SataP0TDispFinit            | * | 0x01 | 0x00

  # !BSF NAME:{Port 1 Tinactive} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Port 1 Tinactive.}
  gPlatformFspPkgTokenSpaceGuid.SataP1Tinact                | * | 0x01 | 0x00

  # !BSF NAME:{Port 1 Alternate Fast Init Tdispatch} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Port 1 Alternate Fast Init Tdispatch.}
  gPlatformFspPkgTokenSpaceGuid.SataP1TDispFinit            | * | 0x01 | 0x00

  # !BSF NAME:{Sata Thermal Throttling Suggested Setting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Sata Thermal Throttling Suggested Setting.}
  gPlatformFspPkgTokenSpaceGuid.SataThermalSuggestedSetting | * | 0x01 | 0x01

  # !BSF NAME:{Enable Memory Thermal Throttling} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable Memory Thermal Throttling.}
  gPlatformFspPkgTokenSpaceGuid.PchMemoryThrottlingEnable   | * | 0x01 | 0x00

  # !BSF NAME:{Memory Thermal Throttling} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable Memory Thermal Throttling.}
  gPlatformFspPkgTokenSpaceGuid.PchMemoryPmsyncEnable       | * | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Enable Memory Thermal Throttling} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable Memory Thermal Throttling.}
  gPlatformFspPkgTokenSpaceGuid.PchMemoryC0TransmitEnable   | * | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Enable Memory Thermal Throttling} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Enable Memory Thermal Throttling.}
  gPlatformFspPkgTokenSpaceGuid.PchMemoryPinSelection       | * | 0x02 | { 0x00, 0x00 }

  # !BSF NAME:{Thermal Device Temperature} TYPE:{EditNum, HEX, (0x00,0xFFFF)}
  # !BSF HELP:{Decides the temperature.}
  gPlatformFspPkgTokenSpaceGuid.PchTemperatureHotLevel      | * | 0x02 | 0x0073

  # !BSF NAME:{Enable xHCI Compliance Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Compliance Mode can be enabled for testing through this option but this is disabled by default.}
  gPlatformFspPkgTokenSpaceGuid.PchEnableComplianceMode     | * | 0x01 | 0x00

  # !BSF NAME:{USB2 Port Over Current Pin} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Describe the specific over current pin number of USB 2.0 Port N.}
  gPlatformFspPkgTokenSpaceGuid.Usb2OverCurrentPin          | * | 0x10 | { 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x07, 0x07 }

  # !BSF NAME:{USB3 Port Over Current Pin} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Describe the specific over current pin number of USB 3.0 Port N.}
  gPlatformFspPkgTokenSpaceGuid.Usb3OverCurrentPin          | * | 0x0A | { 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04 }

  # !BSF NAME:{Enable xHCI LTR override} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enables override of recommended LTR values for xHCI}
  gPlatformFspPkgTokenSpaceGuid.PchUsbLtrOverrideEnable         | * | 0x01 | 0x00

  # !BSF NAME:{USB Clock Gating Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or disable USB clock gating}
  gPlatformFspPkgTokenSpaceGuid.UsbClockGatingEnable         | * | 0x01 | 0x00

  # !BSF NAME:{USB Power Gating Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or disable USB power gating}
  gPlatformFspPkgTokenSpaceGuid.UsbPowerGatingEnable         | * | 0x01 | 0x00

  # !BSF NAME:{USB3 LINK SPEED} TYPE:{Combo} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Set USB3 LINK SPEED=0 for GEN2, Set USB3 LINK SPEED=1 for GEN1}
  gPlatformFspPkgTokenSpaceGuid.USB3LinkSpeed         | * | 0x01 | 0x00

  # !BSF NAME:{xHCI High Idle Time LTR override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Value used for overriding LTR recommendation for xHCI High Idle Time LTR setting}
  gPlatformFspPkgTokenSpaceGuid.PchUsbLtrHighIdleTimeOverride   | * | 0x04 | 0x00000000

  # !BSF NAME:{xHCI Medium Idle Time LTR override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Value used for overriding LTR recommendation for xHCI Medium Idle Time LTR setting}
  gPlatformFspPkgTokenSpaceGuid.PchUsbLtrMediumIdleTimeOverride | * | 0x04 | 0x00000000

  # !BSF NAME:{xHCI Low Idle Time LTR override} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Value used for overriding LTR recommendation for xHCI Low Idle Time LTR setting}
  gPlatformFspPkgTokenSpaceGuid.PchUsbLtrLowIdleTimeOverride    | * | 0x04 | 0x00000000

  # !BSF NAME:{Enable 8254 Static Clock Gating} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set 8254CGE=1 is required for SLP_S0 support. However, set 8254CGE=1 in POST time might fail to boot legacy OS using 8254 timer. Make sure it is disabled to support legacy OS using 8254 timer. Also enable this while S0ix is enabled.}
  gPlatformFspPkgTokenSpaceGuid.Enable8254ClockGating       | * | 0x01 | 0x01

  # !BSF NAME:{Enable 8254 Static Clock Gating On S3} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This is only applicable when Enable8254ClockGating is disabled. FSP will do the 8254 CGE programming on S3 resume when Enable8254ClockGatingOnS3 is enabled. This avoids the SMI requirement for the programming.}
  gPlatformFspPkgTokenSpaceGuid.Enable8254ClockGatingOnS3   | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst Optane Memory} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Optane Memory}
  gPlatformFspPkgTokenSpaceGuid.SataRstOptaneMemory         | * | 0x01 | 0x01

  # !BSF NAME:{PCH Sata Rst CPU Attached Storage} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{CPU Attached Storage}
  gPlatformFspPkgTokenSpaceGuid.SataRstCpuAttachedStorage   | * | 0x01 | 0x01

  # !BSF NAME:{Enable TCO timer.} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When FALSE, it disables PCH ACPI timer, and stops TCO timer. NOTE: This will have huge power impact when it's enabled. If TCO timer is disabled, uCode ACPI timer emulation must be enabled, and WDAT table must not be exposed to the OS.}
  gPlatformFspPkgTokenSpaceGuid.EnableTcoTimer              | * | 0x01 | 0x00

  # !BSF NAME:{Enable Timed GPIO 0.} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When FALSE, it disables Timed GPIO 0.}
  gPlatformFspPkgTokenSpaceGuid.EnableTimedGpio0            | * | 0x01 | 0x00

  # !BSF NAME:{Enable Timed GPIO 1.} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When FALSE, it disables Timed GPIO 1.}
  gPlatformFspPkgTokenSpaceGuid.EnableTimedGpio1            | * | 0x01 | 0x00

  #
  #  PCH Silicon Offset End
  #

  ###########Security Production Policies Start ###########################################

  # Bios Guard
  # !BSF PAGE:{SA2}
  # !BSF NAME:{BgpdtHash[4]} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT64}
  # !BSF HELP:{BgpdtHash values}
  gPlatformFspPkgTokenSpaceGuid.BgpdtHash                   | * | 0x20 | {0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000}

  # !BSF NAME:{BiosGuardAttr} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{BiosGuardAttr default values}
  gPlatformFspPkgTokenSpaceGuid.BiosGuardAttr               | * | 0x4 | 0xFFFFFFFF

  # !BSF NAME:{BiosGuardModulePtr} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{BiosGuardModulePtr default values}
  gPlatformFspPkgTokenSpaceGuid.BiosGuardModulePtr          | * | 0x8 | 0xFFFFFFFFFFFFFFFF

  # !BSF NAME:{SendEcCmd} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{SendEcCmd function pointer. \n @code typedef EFI_STATUS (EFIAPI *PLATFORM_SEND_EC_COMMAND) (IN EC_COMMAND_TYPE  EcCmdType, IN UINT8  EcCmd, IN UINT8  SendData, IN OUT UINT8  *ReceiveData); @endcode}
  gPlatformFspPkgTokenSpaceGuid.SendEcCmd                   | * | 0x8 | 0xFFFFFFFFFFFFFFFF

  # !BSF NAME:{EcCmdProvisionEav} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Ephemeral Authorization Value default values. Provisions an ephemeral shared secret to the EC}
  gPlatformFspPkgTokenSpaceGuid.EcCmdProvisionEav           | * | 0x1 | 0xFF

  # !BSF NAME:{EcCmdLock} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{EcCmdLock default values. Locks Ephemeral Authorization Value sent previously}
  gPlatformFspPkgTokenSpaceGuid.EcCmdLock                   | * | 0x1 | 0xFF

  # SGX

  # !BSF NAME:{SgxEpoch0} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{SgxEpoch0 default values}
  #TODO: Just a place holder - feature owner to change the default value
  gPlatformFspPkgTokenSpaceGuid.SgxEpoch0                   | * | 0x8 | 0xFFFFFFFFFFFFFFFF

  # !BSF NAME:{SgxEpoch1} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{SgxEpoch1 default values}
  #TODO: Just a place holder - feature owner to change the default value
  gPlatformFspPkgTokenSpaceGuid.SgxEpoch1                   | * | 0x8 | 0xFFFFFFFFFFFFFFFF

  # !BSF NAME:{SgxSinitNvsData} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{SgxSinitNvsData default values}
  gPlatformFspPkgTokenSpaceGuid.SgxSinitNvsData             | * | 0x1 | 0xFF

  # !BSF NAME:{SgxLCP} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{SgxLCP default values}
  gPlatformFspPkgTokenSpaceGuid.SgxLCP                      | * | 0x1 | 0x00

  # !BSF NAME:{EpcLength} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{EpcLength default values}
  gPlatformFspPkgTokenSpaceGuid.SgxLEPubKeyHash0            | * | 0x8 | 0x0000000000000000

  # !BSF NAME:{EpcLength} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{EpcLength default values}
  gPlatformFspPkgTokenSpaceGuid.SgxLEPubKeyHash1            | * | 0x8 | 0x0000000000000000

  # !BSF NAME:{EpcLength} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{EpcLength default values}
  gPlatformFspPkgTokenSpaceGuid.SgxLEPubKeyHash2            | * | 0x8 | 0x0000000000000000

  # !BSF NAME:{EpcLength} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{EpcLength default values}
  gPlatformFspPkgTokenSpaceGuid.SgxLEPubKeyHash3            | * | 0x8 | 0x0000000000000000

  ###########Security Production Policies End ###########################################

  #
  #  SiConfig Silicon Policies Start
  #
  # !BSF NAME:{Si Config CSM Flag.} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Platform specific common policies that used by several silicon components. CSM status flag.}
  gPlatformFspPkgTokenSpaceGuid.SiCsmFlag                   | * | 0x01 | 0x00

  # !BSF NAME:{Skip Ssid Programming.} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When set to TRUE, silicon code will not do any SSID programming and platform code needs to handle that by itself properly.}
  gPlatformFspPkgTokenSpaceGuid.SiSkipSsidProgramming    | * | 0x01 | 0x00

  # !BSF NAME:{Change Default SVID} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !BSF HELP:{Change the default SVID used in FSP to programming internal devices. This is only valid when SkipSsidProgramming is FALSE.}
  gPlatformFspPkgTokenSpaceGuid.SiCustomizedSvid    | * | 0x02 | 0x0000

  # !BSF NAME:{Change Default SSID} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !BSF HELP:{Change the default SSID used in FSP to programming internal devices. This is only valid when SkipSsidProgramming is FALSE.}
  gPlatformFspPkgTokenSpaceGuid.SiCustomizedSsid    | * | 0x02 | 0x0000

  #
  # typedef struct {
  #   UINT16  SubSystemVendorId; // If giving 0, FSP will program default for the device.
  #   UINT16  SubSystemId;       // If giving 0, FSP will program default for the device.
  # } SVID_SID_VALUE;
  #
  # typedef struct {
  #   union {
  #     struct {
  #       UINT64  Register:12;   // SSID register offset
  #       UINT64  Function:3;
  #       UINT64  Device:5;
  #       UINT64  Bus:8;
  #       UINT64  Reserved1:4;
  #       UINT64  Segment:16;
  #       UINT64  Reserved2:16;
  #     } Bits;
  #     UINT64    SegBusDevFuncRegister;
  #   } Address;
  #   SVID_SID_VALUE SvidSidValue;
  #   UINT32 Reserved;
  # } SVID_SID_INIT_ENTRY;
  #
  # Example table structure:
  # SVID_SID_INIT_ENTRY mSsidTablePtr[] = {
  #   {{{Register, Function, Device, Bus, Reserved1, Segment, Reserved2}}, {SubSystemVendorId, SubSystemId}, Reserved},
  #   {{{       0,        5,     31,   0,         0,       0,         0}}, {           0x1234,      0x5678}        ,0}
  # }
  #
  # Note:
  # In the table, only Device, Function, SubSystemVendorId and SubSystemId fields are required.
  # When both SiSsidTablePtr and SiNumberOfSsidTableEntry are non-zero, FSP will follow the table to program SSID for corresponding devices (either given value or default value).
  #
  # !BSF NAME:{SVID SDID table Poniter.} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{The address of the table of SVID SDID to customize each SVID SDID entry. This is only valid when SkipSsidProgramming is FALSE.}
  gPlatformFspPkgTokenSpaceGuid.SiSsidTablePtr              | * | 0x04 | 0x00000000

  # !BSF NAME:{Number of ssid table.} TYPE:{EditNum, HEX, (0x00, 0xFFFF)}
  # !BSF HELP:{SiNumberOfSsidTableEntry should match the table entries created in SiSsidTablePtr. This is only valid when SkipSsidProgramming is FALSE.}
  gPlatformFspPkgTokenSpaceGuid.SiNumberOfSsidTableEntry    | * | 0x02 | 0x0000
  gPlatformFspPkgTokenSpaceGuid.SiPostMemRsvd               | * | 0x10 | {0x00}

  # !BSF NAME:{SATA RST Interrupt Mode} TYPE:{Combo} OPTION:{0:Msix, 1:Msi, 2:Legacy}
  # !BSF HELP:{Allowes to choose which interrupts will be implemented by SATA controller in RAID mode.}
  gPlatformFspPkgTokenSpaceGuid.SataRstInterrupt            | * | 0x01 | 0x00
  #
  #  SiConfig Silicon Policies End
  #

  #
  # ME Post-Mem Production Block Start
  #
  # !BSF PAGE:{PCH2}
  # !BSF NAME:{ME Unconfig on RTC clear}
  # !BSF TYPE:{Combo} OPTION:{0: Disable ME Unconfig On Rtc Clear, 1: Enable ME Unconfig On Rtc Clear, 2: Cmos is clear, 3: Reserved}
  # !BSF HELP:{0: Disable ME Unconfig On Rtc Clear. <b>1: Enable ME Unconfig On Rtc Clear</b>. 2: Cmos is clear, status unkonwn. 3: Reserved}
  gPlatformFspPkgTokenSpaceGuid.MeUnconfigOnRtcClear        | * | 0x01 | 0x01
  #
  # ME Post-Mem Production Block End
  #

  # !BSF NAME:{Enable PS_ON.} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{PS_ON is a new C10 state from the CPU on desktop SKUs that enables a lower power target that will be required by the California Energy Commission (CEC). When FALSE, PS_ON is to be disabled.}
  gPlatformFspPkgTokenSpaceGuid.PsOnEnable                  | * | 0x01 | 0x00

  # !BSF NAME:{Pmc Cpu C10 Gate Pin Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable platform support for CPU_C10_GATE# pin to control gating of CPU VccIO and VccSTG rails instead of SLP_S0# pin.}
  gPlatformFspPkgTokenSpaceGuid.PmcCpuC10GatePinEnable      | * | 0x01 | 0x01

  # !BSF NAME:{Pch Dmi Aspm Ctrl} TYPE:{Combo}
  # !BSF OPTION:{0:Disabled, 1:L0s, 2:L1, 3:L0sL1, 4:Auto}
  # !BSF HELP:{ASPM configuration on the PCH side of the DMI/OPI Link. Default is <b>PchPcieAspmAutoConfig</b>}
  gPlatformFspPkgTokenSpaceGuid.PchDmiAspmCtrl              | * | 0x01 | 0x04

  # !BSF NAME:{PchDmiCwbEnable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Central Write Buffer feature configurable and disabled by default}
  gPlatformFspPkgTokenSpaceGuid.PchDmiCwbEnable             | * | 0x1 | 0x00

  # !BSF NAME:{OS IDLE Mode Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable OS Idle Mode}
  gPlatformFspPkgTokenSpaceGuid.PmcOsIdleEnable             | * | 0x01 | 0x01

  # !BSF NAME:{S0ix Auto-Demotion} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable the Low Power Mode Auto-Demotion Host Control feature.}
  gPlatformFspPkgTokenSpaceGuid.PchS0ixAutoDemotion         | * | 0x01 | 0x01

  # !BSF NAME:{Global Reset TSC Enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable PMC Global Reset Three Strike Counter feature. If enabled, PMC will keep the platform in S5 after the third consecutive type 7 global reset occurs during boot flow}
  gPlatformFspPkgTokenSpaceGuid.PmcGrTscEnable              | * | 0x01 | 0x00

  # !BSF NAME:{Latch Events C10 Exit} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{When this bit is set to 1, SLP_S0# entry events in SLP_S0_DEBUG_REGx registers are captured on C10 exit (instead of C10 entry which is default)}
  gPlatformFspPkgTokenSpaceGuid.PchPmLatchEventsC10Exit     | * | 0x01 | 0x00

  #
  # SA Post-Mem PCIE Policies Start
  #
  # !BSF PAGE:{SA2}
  # !BSF NAME:{PCIE Eq Ph3 Lane Param Cm} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{CPU_PCIE_EQ_LANE_PARAM. Coefficient C-1.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieEqPh3LaneParamCm        | * | 0x20 | { 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06 }

  # !BSF NAME:{PCIE Eq Ph3 Lane Param Cp} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{CPU_PCIE_EQ_LANE_PARAM. Coefficient C+1.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieEqPh3LaneParamCp        | * | 0x20 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE Hw Eq Gen3 CoeffList Cm} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{CPU_PCIE_EQ_PARAM. Coefficient C-1.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieHwEqGen3CoeffListCm         | * | 0x05 | { 0x00, 0x04, 0x07, 0x09, 0x00 }

  # !BSF NAME:{PCIE Hw Eq Gen3 CoeffList Cp} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{CPU_PCIE_EQ_PARAM. Coefficient C+1.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieHwEqGen3CoeffListCp         | * | 0x05 | { 0x01, 0x05, 0x08, 0x00, 0x00 }

  # !BSF NAME:{PCIE Hw Eq Gen4 CoeffList Cm} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{CPU_PCIE_EQ_PARAM. Coefficient C-1.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieHwEqGen4CoeffListCm         | * | 0x05 | { 0x00, 0x04, 0x07, 0x09, 0x00 }

  # !BSF NAME:{PCIE Hw Eq Gen4 CoeffList Cp} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFF)}
  # !BSF HELP:{CPU_PCIE_EQ_PARAM. Coefficient C+1.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieHwEqGen4CoeffListCp         | * | 0x05 | { 0x01, 0x05, 0x08, 0x00, 0x00 }

  # !BSF NAME:{Gen3 Root port preset values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming Pcie Gen3 preset values per lane. Range: 0-9, 8 is default for each lane}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieGen3RootPortPreset       | * | 0x14 | {0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7}

  # !BSF NAME:{Pcie Gen4 Root port preset values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming Pcie Gen4 preset values per lane. Range: 0-9, 8 is default for each lane}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieGen4RootPortPreset       | * | 0x14 | {0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7}

  # !BSF NAME:{Pcie Gen3 End port preset values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming Pcie Gen3 preset values per lane. Range: 0-9, 7 is default for each lane}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieGen3EndPointPreset       | * | 0x14 | {0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7}

  # !BSF NAME:{Pcie Gen4 End port preset values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming Pcie Gen4 preset values per lane. Range: 0-9, 7 is default for each lane}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieGen4EndPointPreset       | * | 0x14 | {0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7, 0x7}

  # !BSF NAME:{Pcie Gen3 End port Hint values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming Pcie Gen3 Hint values per lane. Range: 0-6, 2 is default for each lane}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieGen3EndPointHint         | * | 0x14 | {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2}

  # !BSF NAME:{Pcie Gen4 End port Hint values per lane} TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{Used for programming Pcie Gen4 Hint values per lane. Range: 0-6, 2 is default for each lane}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieGen4EndPointHint         | * | 0x14 | {0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2}

  # !BSF NAME:{Skip Cpu Fia Programming} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Skip Fia configuration and lock if enable. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieSkipCpuFiaProgramming | * | 0x01 | 0x00

  # !BSF NAME:{PCIE Disable RootPort Clock Gating} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Describes whether the PCI Express Clock Gating for each root port is enabled by platform modules. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieDisableRootPortClockGating | * | 0x01 | 0x00

  # !BSF NAME:{PCIE Disable RootPort Power Gating} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Describes whether the PCI Express Power Gating for each root port is enabled by platform modules. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieDisableRootPortPowerGating | * | 0x01 | 0x00

  # !BSF NAME:{PCIE Compliance Test Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Compliance Test Mode shall be enabled when using Compliance Load Board.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieComplianceTestMode      | * | 0x01 | 0x00

  # !BSF NAME:{PCIE Secure Register Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Describes whether Secure Register Lock is enaled or disabled. When it will be enbaled, load CpuPcieRpSetSecuredRegisterLock recipe. 0: Disable(Default); 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieSetSecuredRegisterLock  | * | 0x01 | 0x00

  # !BSF NAME:{PCIE Enable Peer Memory Write} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This member describes whether Peer Memory Writes are enabled on the platform.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieEnablePeerMemoryWrite   | * | 0x01 | 0x00

  # !BSF NAME:{PCIE Rp Function Swap} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Allows BIOS to use root port function number swapping when root port of function 0 is disabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpFunctionSwap          | * | 0x01 | 0x00

  # !BSF NAME:{Pch PCIE device override table pointer} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{The PCIe device table is being used to override PCIe device ASPM settings. This is a pointer points to a 32bit address. And it's only used in PostMem phase. Please refer to CPU_PCIE_DEVICE_OVERRIDE structure for the table. Last entry VendorId must be 0.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieDeviceOverrideTablePtr  | * | 0x04 | 0x00000000

  # !BSF NAME:{Enable PCIE RP HotPlug} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the root port is hot plug available.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpHotPlug               | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{Enable PCIE RP Pm Sci} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the root port power manager SCI is enabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpPmSci                 | * | 0x4 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{Enable PCIE RP Transmitter Half Swing} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Transmitter Half Swing is enabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpTransmitterHalfSwing  | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Access Control Services Extended Capability} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Enable/Disable PCIE RP Access Control Services Extended Capability}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpAcsEnabled           | * | 0x4 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Clock Power Management} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Enable/Disable PCIE RP Clock Power Management, even if disabled, CLKREQ# signal can still be controlled by L1 PM substates mechanism}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpEnableCpm            | * | 0x04 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Advanced Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Advanced Error Reporting is enabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpAdvancedErrorReporting   | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Unsupported Request Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Unsupported Request Report is enabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpUnsupportedRequestReport | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Fatal Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Fatal Error Report is enabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpFatalErrorReport      | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP No Fatal Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the No Fatal Error Report is enabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpNoFatalErrorReport    | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Correctable Error Report} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the Correctable Error Report is enabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpCorrectableErrorReport   | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP System Error On Fatal Error} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the System Error on Fatal Error is enabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpSystemErrorOnFatalError  | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP System Error On Non Fatal Error} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the System Error on Non Fatal Error is enabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpSystemErrorOnNonFatalError | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP System Error On Correctable Error} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicate whether the System Error on Correctable Error is enabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpSystemErrorOnCorrectableError | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Max Payload} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Max Payload Size supported, Default 128B, see enum PCH_PCIE_MAX_PAYLOAD.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpMaxPayload            | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{DPC for PCIE RP Mask} TYPE:{EditNum, HEX, (0x00,0x00FFFFFF)}
  # !BSF HELP:{Enable/disable Downstream Port Containment for PCIE Root Ports. 0: disable, 1: enable. One bit for each port, bit0 for port1, bit1 for port2, and so on.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpDpcEnabled               | * | 0x04 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{DPC Extensions PCIE RP Mask} TYPE:{EditNum, HEX, (0x00,0x00FFFFFF)}
  # !BSF HELP:{Enable/disable DPC Extensions for PCIE Root Ports. 0: disable, 1: enable. One bit for each port, bit0 for port1, bit1 for port2, and so on.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpDpcExtensionsEnabled     | * | 0x04 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCH PCIe root port connection type} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: built-in device, 1:slot}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpSlotImplemented       | * | 0x4 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Gen3 Equalization Phase Method} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCIe Gen3 Eq Ph3 Method (see CPU_PCIE_EQ_METHOD). 0: DEPRECATED, hardware equalization; 1: hardware equalization; 4: Fixed Coeficients.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpGen3EqPh3Method       | * | 0x4 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Gen4 Equalization Phase Method} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{PCIe Gen4 Eq Ph3 Method (see CPU_PCIE_EQ_METHOD). 0: DEPRECATED, hardware equalization; 1: hardware equalization; 4: Fixed Coeficients.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpGen4EqPh3Method       | * | 0x4 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{Phase3 RP Gen3 EQ enable} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:Auto}
  # !BSF HELP:{Phase3 Gen3 EQ enable. Disabled(0x0): Disable phase 3, Enabled(0x1): Enable phase 3, Auto(0x2)(Default): Use the current default method}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpGen3EqPh3Enable         | * | 0x04 | { 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{Phase3 RP Gen4 EQ enable} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:Auto}
  # !BSF HELP:{Phase3 Gen4 EQ enable. Disabled(0x0): Disable phase 3, Enabled(0x1): Enable phase 3, Auto(0x2)(Default): Use the current default method}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpGen4EqPh3Enable         | * | 0x04 | { 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{Phase2-3 RP Gen3 EQ enable} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:Auto}
  # !BSF HELP:{Phase2-3 Gen3 EQ enable. Disabled(0x0): Disable Phase2-3, Enabled(0x1): Enable Phase2-3, Auto(0x2)(Default): Use the current default method}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpGen3EqPh23Enable         | * | 0x04 | { 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{Phase2-3 RP Gen4 EQ enable} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable, 2:Auto}
  # !BSF HELP:{Phase2-3 Gen4 EQ enable. Disabled(0x0): Disable Phase2-3, Enabled(0x1): Enable Phase2-3, Auto(0x2)(Default): Use the current default method}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpGen4EqPh23Enable         | * | 0x04 | { 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCET Timer} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Preset/Coefficient Evaluation Timeout. See CPU_PCIE_PCET. Default is 0x4}
  gPlatformFspPkgTokenSpaceGuid.CpuPciePcetTimer                 | * | 0x04 | { 0x04, 0x04, 0x04, 0x04 }

  # !BSF NAME:{Gen3 Preset/Coeffiecient List Count} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Select Gen3 Hardware Autonomous Preset/Coefficient Count. See Gen3 CPU_PCIE_PRESETCOEFF_LIST. Default is 0x3}
  gPlatformFspPkgTokenSpaceGuid.Gen3CpuPciePresetCoeffList                 | * | 0x04 | { 0x03, 0x03, 0x03, 0x03 }

  # !BSF NAME:{Gen4 Preset/Coeffiecient List Count} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Select Gen4 Hardware Autonomous Preset/Coefficient Count. See CPU_PCIE_PRESETCOEFF_LIST. Default is 0x3}
  gPlatformFspPkgTokenSpaceGuid.Gen4CpuPciePresetCoeffList                 | * | 0x04 | { 0x03, 0x03, 0x03, 0x03 }

  # !BSF NAME:{Presets/Coefficients Evaluation for Gen3} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{8.0GT/s Training Sequence Wait Latency For Presets/Coefficients Evaluation. See CPU_PCIE_PX8GTSWLPCE. Default is 0x3}
  gPlatformFspPkgTokenSpaceGuid.CpuPciePx8gtswlpce                     | * | 0x04 | { 0x03, 0x03, 0x03, 0x03 }

  # !BSF NAME:{Presets/Coefficients Evaluation for Gen4} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{16.0GT/s Training Sequence Wait Latency For Presets/Coefficients Evaluation. See CPU_PCIE_PX16GTSWLPCE. Default is 0x4}
  gPlatformFspPkgTokenSpaceGuid.CpuPciePx16gtswlpce                    | * | 0x04 | { 0x04, 0x04, 0x04, 0x04 }

  # !BSF NAME:{PCIE RP Physical Slot Number} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Indicates the slot number for the root port. Default is the value as root port index.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpPhysicalSlotNumber    | * | 0x4 | { 0x00, 0x01, 0x02, 0x03 }

  # !BSF NAME:{PCIE RP Aspm} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{The ASPM configuration of the root port (see: CPU_PCIE_ASPM_CONTROL). Default is CpuPcieAspmAutoConfig.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpAspm                  | * | 0x4 | { 0x04, 0x04, 0x04, 0x04 }

  # !BSF NAME:{PCIE RP L1 Substates} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{The L1 Substates configuration of the root port (see: CPU_PCIE_L1SUBSTATES_CONTROL). Default is CpuPcieL1SubstatesDisabled.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpL1Substates           | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Ltr Enable} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting Mechanism.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpLtrEnable             | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Ltr Config Lock} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpLtrConfigLock         | * | 0x4 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PTM for PCIE RP Mask} TYPE:{EditNum, HEX, (0x00,0x00FFFFFF)}
  # !BSF HELP:{Enable/disable Precision Time Measurement for PCIE Root Ports. 0: disable, 1: enable. One bit for each port, bit0 for port1, bit1 for port2, and so on.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpPtmEnabled            | * | 0x04 | { 0x01, 0x01, 0x01, 0x01 }

  # !BSF NAME:{PCIE RP Detect Timeout Ms} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{The number of milliseconds within 0~65535 in reference code will wait for link to exit Detect state for enabled ports before assuming there is no device and potentially disabling the port.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpDetectTimeoutMs      | * | 0x8 | { 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{VC for PCIE RP Mask} TYPE:{EditNum, HEX, (0x00,0x00FFFFFF)}
  # !BSF HELP:{Enable/disable Virtual Channel for PCIE Root Ports. 0: disable, 1: enable. One bit for each port, bit0 for port1, bit1 for port2, and so on.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpVcEnabled            | * | 0x04 | { 0x01, 0x01, 0x01, 0x01 }
  #
  # SA Post-Mem PCIE Policies End
  #

  # !BSF PAGE:{PCH2}
  # !BSF NAME:{Enable the write to USB 3.0 TX Output Unique Transition Bit Mode for rate 3} TYPE:{EditNum, HEX, (0x00,0x01010101010101010101)}
  # !BSF HELP:{Enable the write to USB 3.0 TX Output Unique Transition Bit Mode for rate 3, Each value in array can be between 0-1. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxRate3UniqTranEnable  | * | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{USB 3.0 TX Output Unique Transition Bit Scale for rate 3} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB 3.0 TX Output Unique Transition Bit Scale for rate 3, HSIO_TX_DWORD9[6:0], <b>Default = 4Ch</b>. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxRate3UniqTran      | * | 0x0A | {0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C}

  # !BSF NAME:{Enable the write to USB 3.0 TX Output Unique Transition Bit Mode for rate 2} TYPE:{EditNum, HEX, (0x00,0x01010101010101010101)}
  # !BSF HELP:{Enable the write to USB 3.0 TX Output Unique Transition Bit Mode for rate 2, Each value in array can be between 0-1. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxRate2UniqTranEnable  | * | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{USB 3.0 TX Output Unique Transition Bit Scale for rate 2} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB 3.0 TX Output Unique Transition Bit Scale for rate 2, HSIO_TX_DWORD9[14:8], <b>Default = 4Ch</b>. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxRate2UniqTran      | * | 0x0A | {0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C}

  # !BSF NAME:{Enable the write to USB 3.0 TX Output Unique Transition Bit Mode for rate 1} TYPE:{EditNum, HEX, (0x00,0x01010101010101010101)}
  # !BSF HELP:{Enable the write to USB 3.0 TX Output Unique Transition Bit Mode for rate 1, Each value in array can be between 0-1. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxRate1UniqTranEnable  | * | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{USB 3.0 TX Output Unique Transition Bit Scale for rate 1} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB 3.0 TX Output Unique Transition Bit Scale for rate 1, HSIO_TX_DWORD9[22:16], <b>Default = 4Ch</b>. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxRate1UniqTran      | * | 0x0A | {0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C}

  # !BSF NAME:{Enable the write to USB 3.0 TX Output Unique Transition Bit Mode for rate 0} TYPE:{EditNum, HEX, (0x00,0x01010101010101010101)}
  # !BSF HELP:{Enable the write to USB 3.0 TX Output Unique Transition Bit Mode for rate 0, Each value in array can be between 0-1. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxRate0UniqTranEnable  | * | 0x0A | {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}

  # !BSF NAME:{USB 3.0 TX Output Unique Transition Bit Scale for rate 0} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{USB 3.0 TX Output Unique Transition Bit Scale for rate 0, HSIO_TX_DWORD9[30:24], <b>Default = 4Ch</b>. One byte for each port.}
  gPlatformFspPkgTokenSpaceGuid.Usb3HsioTxRate0UniqTran      | * | 0x0A | {0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C, 0x4C}

  #
  # SA Post-Mem Block Start
  #
!if gSiPkgTokenSpaceGuid.PcdCflCpuEnable == TRUE
  # !BSF PAGE:{SA2}
  # !BSF NAME:{Enable/Disable Device 7 } TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Device  7 enabled, Disable (Default): Device 7 disabled}
  gPlatformFspPkgTokenSpaceGuid.ChapDeviceEnable            | * | 0x01 | 0x0
!endif

  # !BSF PAGE:{SA2}
  # !BSF NAME:{Skip PAM regsiter lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: PAM register will not be locked by RC, platform code should lock it, Disable(Default): PAM registers will be locked by RC}
  gPlatformFspPkgTokenSpaceGuid.SkipPamLock                 | * | 0x01 | 0x0

  # !BSF NAME:{EDRAM Test Mode} TYPE:{Combo}
  # !BSF OPTION:{0: EDRAM SW disable, 1: EDRAM SW Enable, 2: EDRAM HW mode}
  gPlatformFspPkgTokenSpaceGuid.EdramTestMode               | * | 0x01 | 0x2

  # !BSF NAME:{Enable/Disable IGFX RenderStandby} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable IGFX RenderStandby, Disable: Disable IGFX RenderStandby}
  gPlatformFspPkgTokenSpaceGuid.RenderStandby               | * | 0x01 | 0x1

  # !BSF NAME:{Enable/Disable IGFX PmSupport} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable IGFX PmSupport, Disable: Disable IGFX PmSupport}
  gPlatformFspPkgTokenSpaceGuid.PmSupport                   | * | 0x01 | 0x1

!if gSiPkgTokenSpaceGuid.PcdCflCpuEnable == TRUE
  # !BSF NAME:{Enable/Disable CdynmaxClamp} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable(Default): Enable CdynmaxClamp, Disable: Disable CdynmaxClamp}
  gPlatformFspPkgTokenSpaceGuid.CdynmaxClampEnable          | * | 0x01 | 0x1
!else
  # !BSF NAME:{Enable/Disable CdynmaxClamp} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Enable CdynmaxClamp, Disable(Default): Disable CdynmaxClamp}
  gPlatformFspPkgTokenSpaceGuid.CdynmaxClampEnable          | * | 0x01 | 0x0
!endif

  # !BSF NAME:{GT Frequency Limit} TYPE:{Combo}
  # !BSF OPTION:{0xFF: Auto(Default), 2: 100 Mhz, 3: 150 Mhz, 4: 200 Mhz, 5: 250 Mhz, 6: 300 Mhz, 7: 350 Mhz, 8: 400 Mhz, 9: 450 Mhz, 0xA: 500 Mhz, 0xB: 550 Mhz, 0xC: 600 Mhz, 0xD: 650 Mhz, 0xE: 700 Mhz, 0xF: 750 Mhz, 0x10: 800 Mhz, 0x11: 850 Mhz, 0x12:900 Mhz, 0x13: 950 Mhz, 0x14: 1000 Mhz, 0x15: 1050 Mhz, 0x16: 1100 Mhz, 0x17: 1150 Mhz, 0x18: 1200 Mhz}
  # !BSF HELP:{0xFF: Auto(Default), 2: 100 Mhz, 3: 150 Mhz, 4: 200 Mhz, 5: 250 Mhz, 6: 300 Mhz, 7: 350 Mhz, 8: 400 Mhz, 9: 450 Mhz, 0xA: 500 Mhz, 0xB: 550 Mhz, 0xC: 600 Mhz, 0xD: 650 Mhz, 0xE: 700 Mhz, 0xF: 750 Mhz, 0x10: 800 Mhz, 0x11: 850 Mhz, 0x12:900 Mhz, 0x13: 950 Mhz, 0x14: 1000 Mhz, 0x15: 1050 Mhz, 0x16: 1100 Mhz, 0x17: 1150 Mhz, 0x18: 1200 Mhz}
  gPlatformFspPkgTokenSpaceGuid.GtFreqMax                   | * | 0x1 | 0xFF

  # !BSF NAME:{Disable Turbo GT} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{ 0=Disable: GT frequency is not limited, 1=Enable: Disables Turbo GT frequency}
  gPlatformFspPkgTokenSpaceGuid.DisableTurboGt              | * | 0x1 | 0x0

  # !BSF NAME:{Enable/Disable CdClock Init} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable: Skip Full CD clock initializaton, Disable(Default): Initialize the full CD clock if not initialized by Gfx PEIM}
  gPlatformFspPkgTokenSpaceGuid.SkipCdClockInit             | * | 0x01 | 0x0

  # !BSF NAME:{SaPostMemTestRsvd} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for SA Post-Mem Test}
  gPlatformFspPkgTokenSpaceGuid.SaPostMemTestRsvd           | * | 0xE | {0x00}

  #
  # SA Post-Mem Block End
  #

  #
  # CPU Post-Mem Block Start
  #

  # !BSF NAME:{RSR feature} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable RSR feature; 0: Disable; <b>1: Enable </b>}
  gPlatformFspPkgTokenSpaceGuid.EnableRsr                   | * | 0x01 | 0x01

  # !BSF NAME:{1-Core Ratio Limit}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x53)}
  # !BSF HELP:{1-Core Ratio Limit: For XE part: LFM to 255, For overclocking part: LFM to Fused 1-Core Ratio Limit + OC Bins.This 1-Core Ratio Limit Must be greater than or equal to 2-Core Ratio Limit, 3-Core Ratio Limit, 4-Core Ratio Limit. Range is 0 to 83}
  gPlatformFspPkgTokenSpaceGuid.OneCoreRatioLimit           | * | 0x01 | 0x00

  # !BSF NAME:{2-Core Ratio Limit}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x53)}
  # !BSF HELP:{2-Core Ratio Limit: For XE part: LFM to 255, For overclocking part: LFM to Fused 2-Core Ratio Limit + OC Bins.This 2-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 83}
  gPlatformFspPkgTokenSpaceGuid.TwoCoreRatioLimit           | * | 0x01 | 0x00

  # !BSF NAME:{3-Core Ratio Limit}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x53)}
  # !BSF HELP:{3-Core Ratio Limit: For XE part: LFM to 255, For overclocking part: LFM to Fused 3-Core Ratio Limit + OC Bins.This 3-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 83}
  gPlatformFspPkgTokenSpaceGuid.ThreeCoreRatioLimit         | * | 0x01 | 0x00

  # !BSF NAME:{4-Core Ratio Limit}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x53)}
  # !BSF HELP:{4-Core Ratio Limit: For XE part: LFM to 255, For overclocking part: LFM to Fused 4-Core Ratio Limit + OC Bins.This 4-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 83}
  gPlatformFspPkgTokenSpaceGuid.FourCoreRatioLimit          | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable HWP} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable HWP(Hardware P states) Support. 0: Disable; <b>1: Enable;</b> 2-3:Reserved}
  gPlatformFspPkgTokenSpaceGuid.Hwp                         | * | 0x01 | 0x01

  # !BSF NAME:{Hardware Duty Cycle Control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Hardware Duty Cycle Control configuration. 0: Disabled; <b>1: Enabled</b> 2-3:Reserved}
  gPlatformFspPkgTokenSpaceGuid.HdcControl                  | * | 0x01 | 0x01

  # !BSF NAME:{Package Long duration turbo mode time}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x80)}
  # !BSF HELP:{Package Long duration turbo mode time window in seconds. Valid values(Unit in seconds) 0 to 8 , 10 , 12 ,14 , 16 , 20 , 24 , 28 , 32 , 40 , 48 , 56 , 64 , 80 , 96 , 112 , 128}
  gPlatformFspPkgTokenSpaceGuid.PowerLimit1Time             | * | 0x01 | 0x00

  # !BSF NAME:{Short Duration Turbo Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable short duration Turbo Mode. </b>0 : Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.PowerLimit2                 | * | 0x01 | 0x01

  # !BSF NAME:{Turbo settings Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Lock all Turbo settings Enable/Disable; <b>0: Disable , </b> 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.TurboPowerLimitLock         | * | 0x01 | 0x00

  # !BSF NAME:{Package PL3 time window}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Package PL3 time window range for this policy from 0 to 64ms}
  gPlatformFspPkgTokenSpaceGuid.PowerLimit3Time             | * | 0x01 | 0x00

  # !BSF NAME:{Package PL3 Duty Cycle}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x64)}
  # !BSF HELP:{Package PL3 Duty Cycle; Valid Range is 0 to 100}
  gPlatformFspPkgTokenSpaceGuid.PowerLimit3DutyCycle        | * | 0x01 | 0x00

  # !BSF NAME:{Package PL3 Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Package PL3 Lock Enable/Disable; <b>0: Disable ; <b> 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.PowerLimit3Lock             | * | 0x01 | 0x01

  # !BSF NAME:{Package PL4 Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Package PL4 Lock Enable/Disable; <b>0: Disable ; <b>1: Enable}
  gPlatformFspPkgTokenSpaceGuid.PowerLimit4Lock             | * | 0x01 | 0x00

  # !BSF NAME:{TCC Activation Offset}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{TCC Activation Offset. Offset from factory set TCC activation temperature at which the Thermal Control Circuit must be activated. TCC will be activated at TCC Activation Temperature, in volts.For SKL Y SKU, the recommended default for this policy is  <b>10</b>, For all other SKUs the recommended default are <b>0</b>}
  gPlatformFspPkgTokenSpaceGuid.TccActivationOffset         | * | 0x01 | 0x0A

  # !BSF NAME:{Tcc Offset Clamp Enable/Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Tcc Offset Clamp for Runtime Average Temperature Limit (RATL) allows CPU to throttle below P1.For SKL Y SKU, the recommended default for this policy is <b>1: Enabled</b>, For all other SKUs the recommended default are  <b>0: Disabled</b>.}
  gPlatformFspPkgTokenSpaceGuid.TccOffsetClamp              | * | 0x01 | 0x01

  # !BSF NAME:{Tcc Offset Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Tcc Offset Lock for Runtime Average Temperature Limit (RATL) to lock temperature target; <b>0: Disabled</b>; 1: Enabled.}
  gPlatformFspPkgTokenSpaceGuid.TccOffsetLock               | * | 0x01 | 0x00

  # !BSF NAME:{Custom Ratio State Entries}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x28)}
  # !BSF HELP:{The number of custom ratio state entries, ranges from 0 to 40 for a valid custom ratio table.Sets the number of custom P-states. At least 2 states must be present}
  gPlatformFspPkgTokenSpaceGuid.NumberOfEntries             | * | 0x01 | 0x00

  # !BSF NAME:{Custom Short term Power Limit time window}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x80)}
  # !BSF HELP:{Short term Power Limit time window value for custom CTDP level 1. Valid Range 0 to 128}
  gPlatformFspPkgTokenSpaceGuid.Custom1PowerLimit1Time      | * | 0x01 | 0x1C

  # !BSF NAME:{Custom Turbo Activation Ratio}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Turbo Activation Ratio for custom cTDP level 1. Valid Range 0 to 255}
  gPlatformFspPkgTokenSpaceGuid.Custom1TurboActivationRatio | * | 0x01 | 0x14

  # !BSF NAME:{Custom Config Tdp Control}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x2)}
  # !BSF HELP:{Config Tdp Control (0/1/2) value for custom cTDP level 1. Valid Range is 0 to 2}
  gPlatformFspPkgTokenSpaceGuid.Custom1ConfigTdpControl     | * | 0x01 | 0x00

  # !BSF NAME:{Custom Short term Power Limit time window}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x80)}
  # !BSF HELP:{Short term Power Limit time window value for custom CTDP level 2. Valid Range 0 to 128}
  gPlatformFspPkgTokenSpaceGuid.Custom2PowerLimit1Time      | * | 0x01 | 0x1C

  # !BSF NAME:{Custom Turbo Activation Ratio}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Turbo Activation Ratio for custom cTDP level 2. Valid Range 0 to 255}
  gPlatformFspPkgTokenSpaceGuid.Custom2TurboActivationRatio | * | 0x01 | 0x14

  # !BSF NAME:{Custom Config Tdp Control}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x2)}
  # !BSF HELP:{Config Tdp Control (0/1/2) value for custom cTDP level 1. Valid Range is 0 to 2}
  gPlatformFspPkgTokenSpaceGuid.Custom2ConfigTdpControl     | * | 0x01 | 0x00

  # !BSF NAME:{Custom Short term Power Limit time window}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x80)}
  # !BSF HELP:{Short term Power Limit time window value for custom CTDP level 3. Valid Range 0 to 128}
  gPlatformFspPkgTokenSpaceGuid.Custom3PowerLimit1Time      | * | 0x01 | 0x1C

  # !BSF NAME:{Custom Turbo Activation Ratio}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Turbo Activation Ratio for custom cTDP level 3. Valid Range 0 to 255}
  gPlatformFspPkgTokenSpaceGuid.Custom3TurboActivationRatio | * | 0x01 | 0x14

  # !BSF NAME:{Custom Config Tdp Control}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x2)}
  # !BSF HELP:{Config Tdp Control (0/1/2) value for custom cTDP level 1. Valid Range is 0 to 2}
  gPlatformFspPkgTokenSpaceGuid.Custom3ConfigTdpControl     | * | 0x01 | 0x00

  # !BSF NAME:{ConfigTdp mode settings Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Lock the ConfigTdp mode settings from runtime changes; <b>0: Disable</b>; 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.ConfigTdpLock               | * | 0x01 | 0x00

  # !BSF NAME:{Load Configurable TDP SSDT} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Configure whether to load Configurable TDP SSDT; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.ConfigTdpBios               | * | 0x01 | 0x00

  # !BSF NAME:{PL1 Enable value} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{PL1 Enable value to limit average platform power. <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PsysPowerLimit1             | * | 0x01 | 0x00

  # !BSF NAME:{PL1 timewindow}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x80)}
  # !BSF HELP:{PL1 timewindow in seconds.Valid values(Unit in seconds) 0 to 8 , 10 , 12 ,14 , 16 , 20 , 24 , 28 , 32 , 40 , 48 , 56 , 64 , 80 , 96 , 112 , 128}
  gPlatformFspPkgTokenSpaceGuid.PsysPowerLimit1Time         | * | 0x01 | 0x00

  # !BSF NAME:{PL2 Enable Value} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{PL2 Enable activates the PL2 value to limit average platform power.<b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PsysPowerLimit2             | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable MLC Streamer Prefetcher} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable MLC Streamer Prefetcher; 0: Disable; <b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.MlcStreamerPrefetcher       | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable MLC Spatial Prefetcher} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable MLC Spatial Prefetcher; 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.MlcSpatialPrefetcher        | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Monitor /MWAIT instructions} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Monitor /MWAIT instructions; 0: Disable; <b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.MonitorMwaitEnable          | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable initialization of machine check registers} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable initialization of machine check registers; 0: Disable; <b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.MachineCheckEnable          | * | 0x01 | 0x01

#ifdef CPU_EHL
  # !BSF NAME:{Check if FUSA is supported} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Check if FUSA is supported; 0: Disable; <b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.IsFusaSupported            | * | 0x01 | 0x00

#endif

  # !BSF NAME:{AP Idle Manner of waiting for SIPI}
  # !BSF TYPE:{Combo} OPTION:{1: HALT loop, 2: MWAIT loop, 3: RUN loop}
  # !BSF HELP:{AP Idle Manner of waiting for SIPI; 1: HALT loop; <b>2: MWAIT loop</b>; 3: RUN loop.}
  gPlatformFspPkgTokenSpaceGuid.ApIdleManner                | * | 0x01 | 0x02

  # !BSF NAME:{Control on Processor Trace output scheme}
  # !BSF TYPE:{Combo} OPTION:{0: Single Range Output, 1: ToPA Output}
  # !BSF HELP:{Control on Processor Trace output scheme; <b>0: Single Range Output</b>; 1: ToPA Output.}
  gPlatformFspPkgTokenSpaceGuid.ProcessorTraceOutputScheme  | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable Processor Trace feature} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Processor Trace feature; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.ProcessorTraceEnable        | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable Voltage Optimization feature} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Voltage Optimization feature 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.VoltageOptimization         | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Intel SpeedStep Technology} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Intel SpeedStep Technology. 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.Eist                        | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Energy Efficient P-state} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Energy Efficient P-state will be applied in Turbo mode. Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.EnergyEfficientPState       | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Energy Efficient Turbo} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Energy Efficient Turbo, will be applied in Turbo mode. Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.EnergyEfficientTurbo        | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable T states} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable T states; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.TStates                     | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Bi-Directional PROCHOT#} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Bi-Directional PROCHOT#; 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.BiProcHot                   | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable PROCHOT# signal being driven externally} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable PROCHOT# signal being driven externally; 0: Disable; <b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.DisableProcHotOut           | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable PROCHOT# Response} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable PROCHOT# Response; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.ProcHotResponse             | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable VR Thermal Alert} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable VR Thermal Alert; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.DisableVrThermalAlert       | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable Thermal Reporting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Thermal Reporting through ACPI tables; 0: Disable; <b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.EnableAllThermalFunctions        | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable Thermal Monitor} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Thermal Monitor; 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.ThermalMonitor              | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable CPU power states (C-states)} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable CPU power states (C-states). 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.Cx                          | * | 0x01 | 0x00

  # !BSF NAME:{Configure C-State Configuration Lock} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Configure C-State Configuration Lock; 0: Disable; <b>1: Enable</b>.}
  gPlatformFspPkgTokenSpaceGuid.PmgCstCfgCtrlLock           | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Enhanced C-states} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Enhanced C-states. 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.C1e                         | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Package Cstate Demotion} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Package Cstate Demotion. 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.PkgCStateDemotion           | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable Package Cstate UnDemotion} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Package Cstate UnDemotion. 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.PkgCStateUnDemotion         | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable CState-Pre wake} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable CState-Pre wake. 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.CStatePreWake               | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable TimedMwait Support.} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable TimedMwait Support. <b>0: Disable</b>; 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.TimedMwait                  | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable IO to MWAIT redirection} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable IO to MWAIT redirection; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.CstCfgCtrIoMwaitRedirection | * | 0x01 | 0x00

  # !BSF NAME:{Set the Max Pkg Cstate}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Set the Max Pkg Cstate. Default set to Auto which limits the Max Pkg Cstate to deep C-state. Valid values 0 - C0/C1 , 1 - C2 , 2 - C3 , 3 - C6 , 4 - C7 , 5 - C7S , 6 - C8 , 7 - C9 , 8 - C10 , 254 - CPU Default , 255 - Auto}
  gPlatformFspPkgTokenSpaceGuid.PkgCStateLimit              | * | 0x01 | 0x08

  # !BSF NAME:{TimeUnit for C-State Latency Control0}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control0; Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl0TimeUnit   | * | 0x01 | 0x02

  # !BSF NAME:{TimeUnit for C-State Latency Control1}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control1;Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl1TimeUnit   | * | 0x01 | 0x02

  # !BSF NAME:{TimeUnit for C-State Latency Control2}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control2;Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl2TimeUnit   | * | 0x01 | 0x02

  # !BSF NAME:{TimeUnit for C-State Latency Control3}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control3;Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl3TimeUnit   | * | 0x01 | 0x02

  # !BSF NAME:{TimeUnit for C-State Latency Control4}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{Time - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl4TimeUnit   | * | 0x01 | 0x02

  # !BSF NAME:{TimeUnit for C-State Latency Control5}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x5)}
  # !BSF HELP:{TimeUnit for C-State Latency Control5;Valid values 0 - 1ns , 1 - 32ns , 2 - 1024ns , 3 - 32768ns , 4 - 1048576ns , 5 - 33554432ns}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl5TimeUnit   | * | 0x01 | 0x02

  # !BSF NAME:{Interrupt Redirection Mode Select}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x7)}
!if gSiPkgTokenSpaceGuid.PcdCflCpuEnable == TRUE
  # !BSF HELP:{Interrupt Redirection Mode Select.0: Fixed priority; 1: Round robin;2: Hash vector;4: PAIR with fixed priority;5: PAIR with round robin;6: PAIR with hash vector;7: No change.}
  gPlatformFspPkgTokenSpaceGuid.PpmIrmSetting               | * | 0x01 | 0x04
!else
  # !BSF HELP:{Interrupt Redirection Mode Select.0: Fixed priority; 1: Round robin;2: Hash vector;7: No change.}
  gPlatformFspPkgTokenSpaceGuid.PpmIrmSetting               | * | 0x01 | 0x00
!endif

  # !BSF NAME:{Lock prochot configuration} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Lock prochot configuration Enable/Disable; <b>0: Disable</b>; 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.ProcHotLock                 | * | 0x01 | 0x00

  # !BSF NAME:{Configuration for boot TDP selection}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFF)}
  # !BSF HELP:{Configuration for boot TDP selection; <b>0: TDP Nominal</b>; 1: TDP Down; 2: TDP Up;0xFF : Deactivate}
  gPlatformFspPkgTokenSpaceGuid.ConfigTdpLevel              | * | 0x01 | 0x00

  # !BSF NAME:{Max P-State Ratio}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x7F)}
  # !BSF HELP:{Max P-State Ratio, Valid Range 0 to 0x7F}
  gPlatformFspPkgTokenSpaceGuid.MaxRatio                    | * | 0x01 | 0x00

  # !BSF NAME:{P-state ratios for custom P-state table} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{P-state ratios for custom P-state table. NumberOfEntries has valid range between 0 to 40. For no. of P-States supported(NumberOfEntries) , StateRatio[NumberOfEntries] are configurable. Valid Range of each entry is 0 to 0x7F}
  gPlatformFspPkgTokenSpaceGuid.StateRatio                  | * | 0x28 | {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}

  # !BSF NAME:{P-state ratios for max 16 version of custom P-state table} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT8}
  # !BSF HELP:{P-state ratios for max 16 version of custom P-state table. This table is used for OS versions limited to a max of 16 P-States. If the first entry of this table is 0, or if Number of Entries is 16 or less, then this table will be ignored, and up to the top 16 values of the StateRatio table will be used instead. Valid Range of each entry is 0 to 0x7F}
  gPlatformFspPkgTokenSpaceGuid.StateRatioMax16             | * | 0x10 | {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}

  # !BSF NAME:{Platform Power Pmax}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x400)}
  # !BSF HELP:{PCODE MMIO Mailbox: Platform Power Pmax. <b>0 - Auto</b> Specified in 1/8 Watt increments. Range 0-1024 Watts. Value of 800 = 100W}
  gPlatformFspPkgTokenSpaceGuid.PsysPmax                    | * | 0x02 | 0xAC

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol1}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol1.Range of value 0 to 0x3FF}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl1Irtl   | * | 0x02 | 0x76

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol2}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol2.Range of value 0 to 0x3FF}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl2Irtl   | * | 0x02 | 0x94

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol3}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol3.Range of value 0 to 0x3FF}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl3Irtl   | * | 0x02 | 0xFA

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol4}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol4.Range of value 0 to 0x3FF}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl4Irtl   | * | 0x02 | 0x14C

  # !BSF NAME:{Interrupt Response Time Limit of C-State LatencyContol5}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3FF)}
  # !BSF HELP:{Interrupt Response Time Limit of C-State LatencyContol5.Range of value 0 to 0x3FF}
  gPlatformFspPkgTokenSpaceGuid.CstateLatencyControl5Irtl   | * | 0x02 | 0x3F2

  # !BSF NAME:{Package Long duration turbo mode power limit}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Package Long duration turbo mode power limit. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit. Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.PowerLimit1                 | * | 0x04 | 0x0

  # !BSF NAME:{Package Short duration turbo mode power limit}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Package Short duration turbo mode power limit. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.PowerLimit2Power            | * | 0x04 | 0x0

  # !BSF NAME:{Package PL3 power limit}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Package PL3 power limit. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.PowerLimit3                 | * | 0x04 | 0x0

  # !BSF NAME:{Package PL4 power limit}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Package PL4 power limit. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.PowerLimit4                 | * | 0x04 | 0x0

  # !BSF NAME:{Tcc Offset Time Window for RATL}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0xFFFFFFFF)}
  # !BSF HELP:{Tcc Offset Time Window can range from 5ms to 448000ms for Runtime Average Temperature Limit (RATL).For SKL Y SKU, the recommended default for this policy is <b>5000: 5 seconds</b>, For all other SKUs the recommended default are <b>0: Disabled</b>
  # 0: Disabled,5: 5ms , 10:10ms , 55:55ms , 156:156ms , 375:375ms , 500:500ms,750:750ms ,1000:1s,2000:2s,3000:3s,4000:4s,5000:5s,6000:6s,7000:7s,8000:8s,10000:10s,12000:12s,14000:14s,16000:16s,20000:20s,24000:24s,28000:28s,32000:32s,40000:40s,48000:48s,56000:56s,64000:64s,80000:80s,96000:96s,112000:112s,128000:128s,160000:160s,192000:192s,224000:224s,256000:256s,320000:320s,384000:384s,448000:448s}
  gPlatformFspPkgTokenSpaceGuid.TccOffsetTimeWindowForRatl  | * | 0x04 | 0x00

  # !BSF NAME:{Short term Power Limit value for custom cTDP level 1}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Short term Power Limit value for custom cTDP level 1. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.Custom1PowerLimit1          | * | 0x04 | 0x9C40

  # !BSF NAME:{Long term Power Limit value for custom cTDP level 1}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Long term Power Limit value for custom cTDP level 1. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.Custom1PowerLimit2          | * | 0x04 | 0xC350


  # !BSF NAME:{Short term Power Limit value for custom cTDP level 2}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Short term Power Limit value for custom cTDP level 2. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.Custom2PowerLimit1          | * | 0x04 | 0x9C40

  # !BSF NAME:{Long term Power Limit value for custom cTDP level 2}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Long term Power Limit value for custom cTDP level 2. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.Custom2PowerLimit2          | * | 0x04 | 0xC350

  # !BSF NAME:{Short term Power Limit value for custom cTDP level 3}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Short term Power Limit value for custom cTDP level 3. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.Custom3PowerLimit1          | * | 0x04 | 0x9C40

  # !BSF NAME:{Long term Power Limit value for custom cTDP level 3}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Long term Power Limit value for custom cTDP level 3. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.Custom3PowerLimit2          | * | 0x04 | 0xC350

  # !BSF NAME:{Platform PL1 power}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Platform PL1 power. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.PsysPowerLimit1Power        | * | 0x04 | 0x00

  # !BSF NAME:{Platform PL2 power}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x3E7F83)}
  # !BSF HELP:{Platform PL2 power. Units are based on POWER_MGMT_CONFIG.CustomPowerUnit.Valid Range 0 to 4095875 in Step size of 125}
  gPlatformFspPkgTokenSpaceGuid.PsysPowerLimit2Power        | * | 0x04 | 0x00

  # !BSF NAME:{Race To Halt} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable/Disable Race To Halt feature. RTH will dynamically increase CPU frequency in order to enter pkg C-State faster to reduce overall power. (RTH is controlled through MSR 1FC bit 20)Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.RaceToHalt                  | * | 0x01 | 0x01

  # !BSF NAME:{Set Three Strike Counter Disable} TYPE:{Combo} OPTION:{0: False, 1: True}
  # !BSF HELP:{False (default): Three Strike counter will be incremented and True: Prevents Three Strike counter from incrementing; <b>0: False</b>; 1: True.}
  gPlatformFspPkgTokenSpaceGuid.ThreeStrikeCounterDisable   | * | 0x01 | 0x00

  # !BSF NAME:{Set HW P-State Interrupts Enabled for for MISC_PWR_MGMT} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Set HW P-State Interrupts Enabled for for MISC_PWR_MGMT; <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.HwpInterruptControl         | * | 0x01 | 0x01

  # !BSF NAME:{5-Core Ratio Limit}
  # !BSF OPTION:{0x0:0xFF}
  # !BSF HELP:{5-Core Ratio Limit: For XE part: LFM to 255, For overclocking part: LFM to Fused 5-Core Ratio Limit + OC Bins.This 5-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 83}
  gPlatformFspPkgTokenSpaceGuid.FiveCoreRatioLimit          | * | 0x01 | 0x00

  # !BSF NAME:{6-Core Ratio Limit}
  # !BSF OPTION:{0x0:0xFF}
  # !BSF HELP:{6-Core Ratio Limit: For XE part: LFM to 255, For overclocking part: LFM to Fused 6-Core Ratio Limit + OC Bins.This 6-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 83}
  gPlatformFspPkgTokenSpaceGuid.SixCoreRatioLimit           | * | 0x01 | 0x00

  # !BSF NAME:{7-Core Ratio Limit}
  # !BSF OPTION:{0x0:0xFF}
  # !BSF HELP:{7-Core Ratio Limit: For XE part: LFM to 255, For overclocking part: LFM to Fused 7-Core Ratio Limit + OC Bins.This 7-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 83}
  gPlatformFspPkgTokenSpaceGuid.SevenCoreRatioLimit         | * | 0x01 | 0x00

  # !BSF NAME:{8-Core Ratio Limit}
  # !BSF OPTION:{0x0:0xFF}
  # !BSF HELP:{8-Core Ratio Limit: For XE part: LFM to 255, For overclocking part: LFM to Fused 8-Core Ratio Limit + OC Bins.This 8-Core Ratio Limit Must be Less than or equal to 1-Core Ratio Limit.Range is 0 to 83}
  gPlatformFspPkgTokenSpaceGuid.EightCoreRatioLimit         | * | 0x01 | 0x00

  # !BSF NAME:{Intel Turbo Boost Max Technology 3.0} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Intel Turbo Boost Max Technology 3.0. 0: Disabled; <b>1: Enabled</b>}
  gPlatformFspPkgTokenSpaceGuid.EnableItbm                   | * | 0x01 | 0x01

  # !BSF NAME:{Intel Turbo Boost Max Technology 3.0 Driver} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Intel Turbo Boost Max Technology 3.0 Driver <b>0: Disabled</b>; 1: Enabled}
  gPlatformFspPkgTokenSpaceGuid.EnableItbmDriver             | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable C1 Cstate Demotion} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable C1 Cstate Demotion. Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.C1StateAutoDemotion           | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable C1 Cstate UnDemotion} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable C1 Cstate UnDemotion. Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.C1StateUnDemotion         | * | 0x01 | 0x01

  # !BSF NAME:{Minimum Ring ratio limit override}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x53)}
  # !BSF HELP:{Minimum Ring ratio limit override. <b>0: Hardware defaults.</b> Range: 0 - Max turbo ratio limit}
  gPlatformFspPkgTokenSpaceGuid.MinRingRatioLimit           | * | 0x01 | 0x00

  # !BSF NAME:{Maximum Ring ratio limit override}
  # !BSF TYPE:{EditNum, HEX, (0x00, 0x53)}
  # !BSF HELP:{Maximum Ring ratio limit override. <b>0: Hardware defaults.</b> Range: 0 - Max turbo ratio limit}
  gPlatformFspPkgTokenSpaceGuid.MaxRingRatioLimit           | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable Per Core P State OS control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Per Core P State OS control. 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.EnablePerCorePState        | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable HwP Autonomous Per Core P State OS control} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable HwP Autonomous Per Core P State OS control. 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.EnableHwpAutoPerCorePstate | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable HwP Autonomous EPP Grouping} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable HwP Autonomous EPP Grouping. 0: Disable; <b>1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.EnableHwpAutoEppGrouping | * | 0x01 | 0x01

  # !BSF NAME:{Enable or Disable EPB override over PECI} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable EPB override over PECI. <b>0: Disable;</b> 1: Enable}
  gPlatformFspPkgTokenSpaceGuid.EnableEpbPeciOverride      | * | 0x01 | 0x00

  # !BSF NAME:{Enable or Disable Fast MSR for IA32_HWP_REQUEST} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable or Disable Fast MSR for IA32_HWP_REQUEST. 0: Disable;<b> 1: Enable</b>}
  gPlatformFspPkgTokenSpaceGuid.EnableFastMsrHwpReq        | * | 0x01 | 0x01

  # !BSF NAME:{ReservedCpuPostMemTest} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Reserved for CPU Post-Mem Test}
  gPlatformFspPkgTokenSpaceGuid.ReservedCpuPostMemTest      | * | 0x11 | {0x00}

  #
  # CPU Post-Mem Block End
  #

  ###########Security Test Policies Start ###########################################
  # !BSF NAME:{SgxSinitDataFromTpm} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{SgxSinitDataFromTpm default values}
  gPlatformFspPkgTokenSpaceGuid.SgxSinitDataFromTpm         | * | 0x01 | 0x00

  gPlatformFspPkgTokenSpaceGuid.SecurityPostMemRsvd         | * | 0x10 | {0x00}
  ###########Security Test Policies End ###########################################

  #
  # ME Post-Mem Block Begin
  #

  # !BSF NAME:{D0I3 Setting for HECI Disable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, 0: disable, 1: enable, Setting this option disables setting D0I3 bit for all HECI devices}
  gPlatformFspPkgTokenSpaceGuid.DisableD0I3SettingForHeci   | * | 0x01 | 0x0
  #
  # ME Post-Mem Block End
  #

  #
  #  PCH Silicon Policies start
  #

  # !BSF NAME:{Enable LOCKDOWN SMI} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable SMI_LOCK bit to prevent writes to the Global SMI Enable bit.}
  gPlatformFspPkgTokenSpaceGuid.PchLockDownGlobalSmi        | * | 0x01 | 0x01

  # !BSF NAME:{Enable LOCKDOWN BIOS Interface} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Enable BIOS Interface Lock Down bit to prevent writes to the Backup Control Register.}
  gPlatformFspPkgTokenSpaceGuid.PchLockDownBiosInterface    | * | 0x01 | 0x01

  # !BSF NAME:{Unlock all GPIO pads} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Force all GPIO pads to be unlocked for debug purpose.}
  gPlatformFspPkgTokenSpaceGuid.PchUnlockGpioPads           | * | 0x01 | 0x00

  # !BSF NAME:{PCH Unlock SideBand access} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{The SideBand PortID mask for certain end point (e.g. PSFx) will be locked before 3rd party code execution. 0: Lock SideBand access; 1: Unlock SideBand access.}
  gPlatformFspPkgTokenSpaceGuid.PchSbAccessUnlock           | * | 0x01 | 0x00

  # !BSF NAME:{PCIE RP Ltr Max Snoop Latency} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Max Snoop Latency.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpLtrMaxSnoopLatency    | * | 0x30 | { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{PCIE RP Ltr Max No Snoop Latency} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Max Non-Snoop Latency.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpLtrMaxNoSnoopLatency  | * | 0x30 | { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Mode.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpSnoopLatencyOverrideMode          | * | 0x18 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Multiplier} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Multiplier.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpSnoopLatencyOverrideMultiplier    | * | 0x18 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Value.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpSnoopLatencyOverrideValue         | * | 0x30 | { 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Mode.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpNonSnoopLatencyOverrideMode       | * | 0x18 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Multiplier} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Multiplier.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpNonSnoopLatencyOverrideMultiplier | * | 0x18 | { 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Value.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpNonSnoopLatencyOverrideValue      | * | 0x30 | { 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C, 0x003C }

  # !BSF NAME:{PCIE RP Slot Power Limit Scale} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Specifies scale used for slot power limit value. Leave as 0 to set to default.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpSlotPowerLimitScale   | * | 0x18 | { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

  # !BSF NAME:{PCIE RP Slot Power Limit Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Specifies upper limit on power supplie by slot. Leave as 0 to set to default.}
  gPlatformFspPkgTokenSpaceGuid.PcieRpSlotPowerLimitValue   | * | 0x30 | { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{PCIE RP Enable Port8xh Decode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{This member describes whether PCIE root port Port 8xh Decode is enabled. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PcieEnablePort8xhDecode     | * | 0x01 | 0x00

  # !BSF NAME:{PCIE Port8xh Decode Port Index} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{The Index of PCIe Port that is selected for Port8xh Decode (0 Based).}
  gPlatformFspPkgTokenSpaceGuid.PchPciePort8xhDecodePortIndex  | * | 0x01 | 0x00

  # !BSF NAME:{PCH Energy Reporting} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Disable/Enable PCH to CPU energy report feature.}
  gPlatformFspPkgTokenSpaceGuid.PchPmDisableEnergyReport    | * | 0x01 | 0x00

  # !BSF NAME:{PCH Sata Test Mode} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Allow entrance to the PCH SATA test modes.}
  gPlatformFspPkgTokenSpaceGuid.SataTestMode                | * | 0x01 | 0x00

  # !BSF NAME:{PCH USB OverCurrent mapping lock enable} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{If this policy option is enabled then BIOS will program OCCFDONE bit in xHCI meaning that OC mapping data will be consumed by xHCI and OC mapping registers will be locked.}
  gPlatformFspPkgTokenSpaceGuid.PchXhciOcLock               | * | 0x01 | 0x01

  # !BSF NAME:{Low Power Mode Enable/Disable config mask} TYPE:{EditNum, HEX, (0x00,0xFF)}
  # !BSF HELP:{Configure if respective S0i2/3 sub-states are to be supported. Each bit corresponds to one sub-state (LPMx - BITx): LPM0-s0i2.0, LPM1-s0i2.1, LPM2-s0i2.2, LPM3-s0i3.0, LPM4-s0i3.1, LPM5-s0i3.2, LPM6-s0i3.3, LPM7-s0i3.4.}
  gPlatformFspPkgTokenSpaceGuid.PmcLpmS0ixSubStateEnableMask | * | 0x01 | 0xFF

  #
  #  PCH Silicon Policies End
  #
#--!endif

  # !BSF NAME:{Mctp Broadcast Cycle} TYPE:{Combo} OPTION:{$EN_DIS}
  # !BSF HELP:{Test, Determine if MCTP Broadcast is enabled <b>0: Disable</b>; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.MctpBroadcastCycle          | * | 0x01 | 0x0

  #
  #  SA Post-Mem PCIE Policies start
  #
  # !BSF PAGE:{SA2}
  # !BSF NAME:{PCIE RP Ltr Max Snoop Latency} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Max Snoop Latency.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpLtrMaxSnoopLatency    | * | 0x8 | { 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{PCIE RP Ltr Max No Snoop Latency} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Max Non-Snoop Latency.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpLtrMaxNoSnoopLatency  | * | 0x8 | { 0x0000, 0x0000, 0x0000, 0x0000 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Mode.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpSnoopLatencyOverrideMode          | * | 0x4 | { 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Multiplier} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Multiplier.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpSnoopLatencyOverrideMultiplier    | * | 0x4 | { 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Snoop Latency Override Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Snoop Latency Override Value.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpSnoopLatencyOverrideValue         | * | 0x8 | { 0x003C, 0x003C, 0x003C, 0x003C }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Mode} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Mode.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpNonSnoopLatencyOverrideMode       | * | 0x4 | { 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Multiplier} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Multiplier.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpNonSnoopLatencyOverrideMultiplier | * | 0x4 | { 0x02, 0x02, 0x02, 0x02 }

  # !BSF NAME:{PCIE RP Non Snoop Latency Override Value} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !HDR STRUCT:{UINT16}
  # !BSF HELP:{Latency Tolerance Reporting, Non-Snoop Latency Override Value.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpNonSnoopLatencyOverrideValue      | * | 0x8 | { 0x003C, 0x003C, 0x003C, 0x003C }

  # !BSF NAME:{PCIE RP Upstream Port Transmiter Preset} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Used during Gen3 Link Equalization. Used for all lanes.  Default is 7.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpGen3Uptp                  | * | 0x4 | { 0x07, 0x07, 0x07, 0x07 }

  # !BSF NAME:{PCIE RP Downstream Port Transmiter Preset} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Used during Gen3 Link Equalization. Used for all lanes.  Default is 7.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpGen3Dptp                  | * | 0x4 | { 0x07, 0x07, 0x07, 0x07 }

  # !BSF NAME:{PCIE RP Upstream Port Transmiter Preset} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Used during Gen3 Link Equalization. Used for all lanes.  Default is 7.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpGen4Uptp                  | * | 0x4 | { 0x07, 0x07, 0x07, 0x07 }

  # !BSF NAME:{PCIE RP Downstream Port Transmiter Preset} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)}
  # !BSF HELP:{Used during Gen3 Link Equalization. Used for all lanes.  Default is 7.}
  gPlatformFspPkgTokenSpaceGuid.CpuPcieRpGen4Dptp                  | * | 0x4 | { 0x07, 0x07, 0x07, 0x07 }

  # !BSF NAME:{Enable PSE JTAG debug option} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{Set if to enable JTAG debug feature for PSE. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseJtagEnabled                  | * | 0x01 | 0x00

  # !BSF NAME:{Enable PSE JTAG pin option} TYPE:{EditNum, HEX, (0x0,0xFF)}
  # !BSF HELP:{This option is used to enable or disable PSE JTAG pin pad mode. 0: Disable; 1: Enable.}
  gPlatformFspPkgTokenSpaceGuid.PchPseJtagPinMux                   | * | 0x01 | 0x00

  #
  #  SA Post-Mem PCIE Policies End
  #

  # !HDR EMBED:{FSP_S_CONFIG:FspsConfig:END}
  gPlatformFspPkgTokenSpaceGuid.ReservedFspsUpd             | * | 0xD | {0x00}


  # Note please keep "UpdTerminator" at the end of each UPD region.
  # The tool will use this field to determine the actual end of the UPD data
  # structure.

  gPlatformFspPkgTokenSpaceGuid.UpdTerminator               | * | 0x02 | 0x55AA

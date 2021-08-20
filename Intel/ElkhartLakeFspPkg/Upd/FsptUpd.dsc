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

  #
  # Comments with !BSF will be used to generate BSF file
  # Comments with !HDR will be used to generate H header file
  #

  # Global definitions in BSF
  # !BSF PAGES:{EHL:"ElkhartLake System Agent", MRC:"Memory Reference Code", MCC:"ElkhartLake PCH"}
  # !BSF BLOCK:{NAME:"ElkhartLake Platform", VER:"0.1"}

  # !BSF FIND:{EHLUPD_T}
  # !HDR COMMENT:{FSP_UPD_HEADER:FSP UPD Header}
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:START}
  # FsptUpdSignature: {EHLUPD_T}
  gPlatformFspPkgTokenSpaceGuid.Signature                   | * | 0x08 | 0x545F4450554C4845
  # !BSF NAME:{FsptUpdRevision}  TYPE:{None}
  gPlatformFspPkgTokenSpaceGuid.Revision                    | * | 0x01 | 0x00
  # !HDR EMBED:{FSP_UPD_HEADER:FspUpdHeader:END}
  gPlatformFspPkgTokenSpaceGuid.Reserved                    | * | 0x17 | {0x00}

  # !HDR COMMENT:{FSPT_CORE_UPD:Fsp T Core UPD}
  # !HDR EMBED:{FSPT_CORE_UPD:FsptCoreUpd:START}
  # Base address of the microcode region.
  gPlatformFspPkgTokenSpaceGuid.MicrocodeRegionBase         | * | 0x04 | 0x00000000

  # Length of the microcode region.
  gPlatformFspPkgTokenSpaceGuid.MicrocodeRegionSize         | * | 0x04 | 0x00000000

  # Base address of the cacheable flash region.
  gPlatformFspPkgTokenSpaceGuid.CodeRegionBase              | * | 0x04 | 0x00000000

  # Length of the cacheable flash region.
  gPlatformFspPkgTokenSpaceGuid.CodeRegionSize              | * | 0x04 | 0x00000000

  # !HDR EMBED:{FSPT_CORE_UPD:FsptCoreUpd:END}
  gPlatformFspPkgTokenSpaceGuid.Reserved                    | * | 0x10 | {0x00}

  # !HDR COMMENT:{FSP_T_CONFIG:Fsp T Configuration}
  # !HDR EMBED:{FSP_T_CONFIG:FsptConfig:START}

  # !BSF PAGE:{ICP}
  # !BSF NAME:{PcdSerialIoUartDebugEnable} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable and Initialize, 2:Enable without Initializing}
  # !BSF HELP:{Enable SerialIo Uart debug library with/without initializing SerialIo Uart device in FSP. }
!if $(TARGET) == DEBUG
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartDebugEnable           | * | 0x01 | 0x01
!else
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartDebugEnable           | * | 0x01 | 0x00
!endif

  # !BSF NAME:{PcdSerialIoUartNumber} TYPE:{Combo}
  # !BSF OPTION:{0:SerialIoUart0, 1:SerialIoUart1, 2:SerialIoUart2}
  # !BSF HELP:{Select SerialIo Uart Controller for debug. Note: If UART0 is selected as CNVi BT Core interface, it cannot be used for debug purpose.}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartNumber                | * | 0x01 | 0x02

  # !BSF NAME:{PcdSerialIoUartMode - FSPT} TYPE:{Combo}
  # !BSF OPTION:{0:SerialIoUartDisabled, 1:SerialIoUartPci, 2:SerialIoUartHidden, 3:SerialIoUartCom, 4:SerialIoUartSkipInit}
  # !BSF HELP:{Select SerialIo Uart Controller mode}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartMode                  | * | 0x01 | 0x02

  # !BSF NAME:{PcdSerialIoUartBaudRate - FSPT} TYPE:{EditNum, DEC, (0,6000000)}
  # !BSF HELP:{Set default BaudRate Supported from 0 - default to 6000000}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartBaudRate              | * | 0x4 | 115200

  #
  # NOTE: If offset for PcdPciExpressBaseAddress & PcdPciExpressRegion is changed,
  # then please change offset accordingly in SecSaInit in SecSaLib.asm & SecSaLibGcc.S
  #

  # !BSF NAME:{Pci Express Base Address}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Base address to be programmed for Pci Express }
  gPlatformFspPkgTokenSpaceGuid.PcdPciExpressBaseAddress             | * | 0x08 | 0xC0000000

  # !BSF NAME:{Pci Express Region Length}  TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Region Length to be programmed for Pci Express }
  gPlatformFspPkgTokenSpaceGuid.PcdPciExpressRegionLength            | * | 0x04 | 0x10000000

  # !BSF NAME:{PcdSerialIoUartParity - FSPT} TYPE:{Combo}
  # !BSF OPTION:{0: DefaultParity, 1: NoParity, 2: EvenParity, 3: OddParity}
  # !BSF HELP:{Set default Parity.}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartParity                | * | 0x01 | 0x1

  # !BSF NAME:{PcdSerialIoUartDataBits - FSPT} TYPE:{EditNum, HEX, (0x0,0x08)}
  # !BSF HELP:{Set default word length. 0: Default, 5,6,7,8}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartDataBits              | * | 0x01 | 0x08

  # !BSF NAME:{PcdSerialIoUartStopBits - FSPT} TYPE:{Combo}
  # !BSF OPTION:{0: DefaultStopBits, 1: OneStopBit, 2: OneFiveStopBits, 3: TwoStopBits}
  # !BSF HELP:{Set default stop bits.}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartStopBits              | * | 0x01 | 0x01

  # !BSF NAME:{PcdSerialIoUartAutoFlow - FSPT} TYPE:{Combo}
  # !BSF OPTION:{0: Disable, 1:Enable}
  # !BSF HELP:{Enables UART hardware flow control, CTS and RTS lines.}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartAutoFlow              | * | 0x01 | 0x0

  # !BSF NAME:{PcdSerialIoUartRxPinMux - FSPT} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Select RX pin muxing for SerialIo UART used for debug}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartRxPinMux              | * | 0x04 | 0x0

  # !BSF NAME:{PcdSerialIoUartTxPinMux - FSPT} TYPE:{EditNum, HEX, (0x00,0xFFFFFFFF)}
  # !BSF HELP:{Select TX pin muxing for SerialIo UART used for debug}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartTxPinMux              | * | 0x04 | 0x0

  # !BSF NAME:{PcdSerialIoUartRtsPinMux - FSPT} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select SerialIo Uart used for debug Rts pin muxing. Refer to GPIO_*_MUXING_SERIALIO_UARTx_RTS* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartRtsPinMux             | * | 0x04 | 0x0

  # !BSF NAME:{PcdSerialIoUartCtsPinMux - FSPT} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select SerialIo Uart used for debug Cts pin muxing. Refer to GPIO_*_MUXING_SERIALIO_UARTx_CTS* for possible values.}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartCtsPinMux             | * | 0x04 | 0x0

  # !BSF NAME:{PcdSerialIoUartDebugMmioBase - FSPT} TYPE:{EditNum, HEX, (0,0xFFFFFFFF)}
  # !BSF HELP:{Select SerialIo Uart default MMIO resource in SEC/PEI phase when PcdSerialIoUartMode = SerialIoUartPci.}
  gPlatformFspPkgTokenSpaceGuid.PcdSerialIoUartDebugMmioBase         | * | 0x04 | 0xFE042000

  # !BSF NAME:{PcdLpcUartDebugEnable} TYPE:{Combo}
  # !BSF OPTION:{0:Disable, 1:Enable}
  # !BSF HELP:{Enable to initialize LPC Uart device in FSP.}
!if $(TARGET) == DEBUG
  gPlatformFspPkgTokenSpaceGuid.PcdLpcUartDebugEnable                | * | 0x01 | 0x01
!else
  gPlatformFspPkgTokenSpaceGuid.PcdLpcUartDebugEnable                | * | 0x01 | 0x00
!endif

  # !HDR EMBED:{FSP_T_CONFIG:FsptConfig:END}
  gPlatformFspPkgTokenSpaceGuid.ReservedFsptUpd1                     | * | 0x14 | {0x00}



  # Note please keep "UpdTerminator" at the end of each UPD region.
  # The tool will use this field to determine the actual end of the UPD data
  # structure.
  gPlatformFspPkgTokenSpaceGuid.UpdTerminator               | * | 0x02 | 0x55AA
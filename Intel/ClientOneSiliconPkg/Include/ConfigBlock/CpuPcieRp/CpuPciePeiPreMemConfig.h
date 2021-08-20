/** @file
  Policy definition for PCIe Config Block in pre-mem phase

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2019 Intel Corporation.

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
#ifndef _PCIE_PEI_PREMEM_CONFIG_H_
#define _PCIE_PEI_PREMEM_CONFIG_H_

#include <Library/GpioLib.h>
#include <Register/CpuPcieRegs.h>
#include <Library/CpuPcieInfoLib.h>

#pragma pack(push, 1)

#define CPU_PCIE_PEI_PREMEM_CONFIG_REVISION 1
#define CPU_PCIE_RP_PREMEM_CONFIG_REVISION  1




/**
 PCI Express and DMI controller configuration\n
 @note <b>Optional.</b> These policies will be ignored if there is no PEG port present on board.
  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER    Header;                                      ///< Offset 0-27 Config Block Header
  /**
   Offset 28:0 :
   <b>(Test)</b> DMI Link Speed Control
  - <b>Auto</b> (0x0)  : Maximum possible link speed (Default)
  - Gen1        (0x1)  : Limit Link to Gen1 Speed
  - Gen2        (0x2)  : Limit Link to Gen2 Speed
  - Gen3        (0x3)  : Limit Link to Gen3 Speed
  **/
  UINT32                 DmiMaxLinkSpeed                 :  2;
  /**
   Offset 28:2 :
   <b>(Test)</b> DMI Equalization Phase 2 Enable Control
  - Disabled       (0x0) : Disable phase 2
  - Enabled        (0x1) : Enable phase 2
  - <b>Auto</b>    (0x2) : Use the current default method (Default)
  **/
  UINT32                 DmiGen3EqPh2Enable              :  2;
  /**
   Offset 28:4 :
   <b>(Test)</b> Selects the method for performing Phase3 of Gen3 Equalization on DMI
  - <b>Auto</b> (0x0)  : Use the current default method (Default)
  - HwEq        (0x1)  : Use Adaptive Hardware Equalization
  - SwEq        (0x2)  : Use Adaptive Software Equalization (Implemented in BIOS Reference Code)
  - Static      (0x3)  : Use the Static EQs provided in DmiGen3EndPointPreset array for Phase1 AND Phase3 (Instead of just Phase1)
  - Disabled    (0x4)  : Bypass Equalization Phase 3
  **/
  UINT32                 DmiGen3EqPh3Method              :  3;
  /**
   Offset 28:7 :
   <b>(Test)</b> Program DMI Gen3 EQ Phase1 Static Presets
  - Disabled        (0x0)  : Disable EQ Phase1 Static Presets Programming
  - <b>Enabled</b>  (0x1)  : Enable  EQ Phase1 Static Presets Programming (Default)
  **/
  UINT32                 DmiGen3ProgramStaticEq          :  1;
  UINT32                 RsvdBits0                       :  24;        ///< Offset 28:8 :Reserved for future use

  /**
  Offset 32:0 :
  Select when PCIe ASPM programming will happen in relation to the Oprom
  - <b>Before</b> (0x0) : Do PCIe ASPM programming before Oprom. (Default)
  - After         (0x1) : Do PCIe ASPM programming after Oprom. This will require an SMI handler to save/restore ASPM settings.
  **/
  UINT32                 InitPcieAspmAfterOprom : 1;
  UINT32                 RsvdBits1 : 31;        ///< Offset 32:1 :Reserved for future use

  UINT8                  DmiGen3RootPortPreset[SA_DMI_MAX_LANE];      ///< Offset 36 Used for programming DMI Gen3 preset values per lane. Range: 0-9, 8 is default for each lane
  UINT8                  DmiGen3EndPointPreset[SA_DMI_MAX_LANE];      ///< Offset 40/44 Used for programming DMI Gen3 preset values per lane. Range: 0-9, 7 is default for each lane
  UINT8                  DmiGen3EndPointHint[SA_DMI_MAX_LANE];        ///< Offset 44/52 Hint value per lane for the DMI Gen3 End Point. Range: 0-6, 2 is default for each lane
  /**
   Offset 48/60 :
   DMI Gen3 RxCTLEp per-Bundle control. The range of the setting is (0-15). This setting
   has to be specified based upon platform design and must follow the guideline. Default is 12.
  **/

  UINT8                  DmiGen3RxCtlePeaking[SA_DMI_MAX_BUNDLE];

  UINT8                  DmiDeEmphasis;                               ///< Offset 50/64 This field is used to describe the DeEmphasis control for DMI (-6 dB and -3.5 dB are the options)
  UINT8                  Rsvd0[3];                                    ///< Offset 65
} PCIE_PEI_PREMEM_CONFIG;



typedef struct {
  CONFIG_BLOCK_HEADER   Header;                                ///< Config Block Header
  /**
  Root Port enabling mask.
  Bit0 presents RP1, Bit1 presents RP2, and so on.
  0: Disable; <b>1: Enable</b>.
  **/
  UINT32                RpEnabledMask;
  /**
  Assertion on Link Down GPIOs
  - <b>Disabled</b> (0x0) : Disable assertion on Link Down GPIOs(Default)
  - Enabled         (0x1) : Enable assertion on Link Down GPIOs
  **/
  UINT8                 LinkDownGpios;
  /**
  Enable ClockReq Messaging
  - <b>Disabled</> (0x0) : Disable ClockReq Messaging(Default)
  - Enabled        (0x1) : Enable ClockReq Messaging
  **/
  UINT8                 ClkReqMsgEnable;
  UINT8                 Rsvd0[2];
  /**
  Determines each PCIE Port speed capability.
  <b>0: Auto</b>; 1: Gen1; 2: Gen2; 3: Gen3; 4: Gen4 (see: CPU_PCIE_SPEED)
  **/
  UINT8                 PcieSpeed[CPU_PCIE_MAX_ROOT_PORTS];

} CPU_PCIE_RP_PREMEM_CONFIG;

#pragma pack(pop)

#endif // _PCIE_PEI_PREMEM_CONFIG_H_

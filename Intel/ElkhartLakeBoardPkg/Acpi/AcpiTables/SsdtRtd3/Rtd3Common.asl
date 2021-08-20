/** @file
  ACPI RTD3 SSDT table

@copyright
  INTEL CONFIDENTIAL
  Copyright 2011 - 2019 Intel Corporation.

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

External(\_SB.OSCO)
External(\_SB.PC00,DeviceObj)
External(\_SB.PC00.SAT0, DeviceObj)
External(\_SB.PC00.SAT0.PRT0, DeviceObj)
External(\_SB.PC00.SAT0.PRT1, DeviceObj)
External(\_SB.PC00.SAT0.PRT2, DeviceObj)
External(\_SB.PC00.SAT0.PRT3, DeviceObj)
External(\_SB.PC00.SAT0.PRT4, DeviceObj)
External(\_SB.PC00.SAT0.PRT5, DeviceObj)

External(\_SB.PC00.RP01, DeviceObj)
External(\_SB.PC00.RP02, DeviceObj)
External(\_SB.PC00.RP03, DeviceObj)
External(\_SB.PC00.RP04, DeviceObj)
External(\_SB.PC00.RP05, DeviceObj)
External(\_SB.PC00.RP06, DeviceObj)
External(\_SB.PC00.RP07, DeviceObj)
External(\_SB.PC00.RP08, DeviceObj)
External(\_SB.PC00.RP09, DeviceObj)
External(\_SB.PC00.RP10, DeviceObj)
External(\_SB.PC00.RP11, DeviceObj)
External(\_SB.PC00.RP12, DeviceObj)
External(\_SB.PC00.RP13, DeviceObj)
External(\_SB.PC00.RP14, DeviceObj)
External(\_SB.PC00.RP15, DeviceObj)
External(\_SB.PC00.RP16, DeviceObj)
External(\_SB.PC00.RP17, DeviceObj)
External(\_SB.PC00.RP18, DeviceObj)
External(\_SB.PC00.RP19, DeviceObj)
External(\_SB.PC00.RP20, DeviceObj)
External(\_SB.PC00.RP21, DeviceObj)
External(\_SB.PC00.RP22, DeviceObj)
External(\_SB.PC00.RP23, DeviceObj)
External(\_SB.PC00.RP24, DeviceObj)

External(\_SB.PC00.RP01.VDID)
External(\_SB.PC00.RP02.VDID)
External(\_SB.PC00.RP03.VDID)
External(\_SB.PC00.RP04.VDID)
External(\_SB.PC00.RP05.VDID)
External(\_SB.PC00.RP06.VDID)
External(\_SB.PC00.RP07.VDID)
External(\_SB.PC00.RP08.VDID)
External(\_SB.PC00.RP09.VDID)
External(\_SB.PC00.RP10.VDID)
External(\_SB.PC00.RP11.VDID)
External(\_SB.PC00.RP12.VDID)
External(\_SB.PC00.RP13.VDID)
External(\_SB.PC00.RP14.VDID)
External(\_SB.PC00.RP15.VDID)
External(\_SB.PC00.RP16.VDID)
External(\_SB.PC00.RP17.VDID)
External(\_SB.PC00.RP18.VDID)
External(\_SB.PC00.RP19.VDID)
External(\_SB.PC00.RP20.VDID)
External(\_SB.PC00.RP21.VDID)
External(\_SB.PC00.RP22.VDID)
External(\_SB.PC00.RP23.VDID)
External(\_SB.PC00.RP24.VDID)

External(\_SB.PC00.RP01.SLOT)
External(\_SB.PC00.RP02.SLOT)
External(\_SB.PC00.RP03.SLOT)
External(\_SB.PC00.RP04.SLOT)
External(\_SB.PC00.RP05.SLOT)
External(\_SB.PC00.RP06.SLOT)
External(\_SB.PC00.RP07.SLOT)
External(\_SB.PC00.RP08.SLOT)
External(\_SB.PC00.RP09.SLOT)
External(\_SB.PC00.RP10.SLOT)
External(\_SB.PC00.RP11.SLOT)
External(\_SB.PC00.RP12.SLOT)
External(\_SB.PC00.RP13.SLOT)
External(\_SB.PC00.RP14.SLOT)
External(\_SB.PC00.RP15.SLOT)
External(\_SB.PC00.RP16.SLOT)
External(\_SB.PC00.RP17.SLOT)
External(\_SB.PC00.RP18.SLOT)
External(\_SB.PC00.RP19.SLOT)
External(\_SB.PC00.RP20.SLOT)
External(\_SB.PC00.RP21.SLOT)
External(\_SB.PC00.RP22.SLOT)
External(\_SB.PC00.RP23.SLOT)
External(\_SB.PC00.RP24.SLOT)

External(\_SB.PC00.RP01.L23D, MethodObj)
External(\_SB.PC00.RP02.L23D, MethodObj)
External(\_SB.PC00.RP03.L23D, MethodObj)
External(\_SB.PC00.RP04.L23D, MethodObj)
External(\_SB.PC00.RP05.L23D, MethodObj)
External(\_SB.PC00.RP06.L23D, MethodObj)
External(\_SB.PC00.RP07.L23D, MethodObj)
External(\_SB.PC00.RP08.L23D, MethodObj)
External(\_SB.PC00.RP09.L23D, MethodObj)
External(\_SB.PC00.RP10.L23D, MethodObj)
External(\_SB.PC00.RP11.L23D, MethodObj)
External(\_SB.PC00.RP12.L23D, MethodObj)
External(\_SB.PC00.RP13.L23D, MethodObj)
External(\_SB.PC00.RP14.L23D, MethodObj)
External(\_SB.PC00.RP15.L23D, MethodObj)
External(\_SB.PC00.RP16.L23D, MethodObj)
External(\_SB.PC00.RP17.L23D, MethodObj)
External(\_SB.PC00.RP18.L23D, MethodObj)
External(\_SB.PC00.RP19.L23D, MethodObj)
External(\_SB.PC00.RP20.L23D, MethodObj)
External(\_SB.PC00.RP21.L23D, MethodObj)
External(\_SB.PC00.RP22.L23D, MethodObj)
External(\_SB.PC00.RP23.L23D, MethodObj)
External(\_SB.PC00.RP24.L23D, MethodObj)

External(\_SB.PC00.RP01.DL23, MethodObj)
External(\_SB.PC00.RP02.DL23, MethodObj)
External(\_SB.PC00.RP03.DL23, MethodObj)
External(\_SB.PC00.RP04.DL23, MethodObj)
External(\_SB.PC00.RP05.DL23, MethodObj)
External(\_SB.PC00.RP06.DL23, MethodObj)
External(\_SB.PC00.RP07.DL23, MethodObj)
External(\_SB.PC00.RP08.DL23, MethodObj)
External(\_SB.PC00.RP09.DL23, MethodObj)
External(\_SB.PC00.RP10.DL23, MethodObj)
External(\_SB.PC00.RP11.DL23, MethodObj)
External(\_SB.PC00.RP12.DL23, MethodObj)
External(\_SB.PC00.RP13.DL23, MethodObj)
External(\_SB.PC00.RP14.DL23, MethodObj)
External(\_SB.PC00.RP15.DL23, MethodObj)
External(\_SB.PC00.RP16.DL23, MethodObj)
External(\_SB.PC00.RP17.DL23, MethodObj)
External(\_SB.PC00.RP18.DL23, MethodObj)
External(\_SB.PC00.RP19.DL23, MethodObj)
External(\_SB.PC00.RP20.DL23, MethodObj)
External(\_SB.PC00.RP21.DL23, MethodObj)
External(\_SB.PC00.RP22.DL23, MethodObj)
External(\_SB.PC00.RP23.DL23, MethodObj)
External(\_SB.PC00.RP24.DL23, MethodObj)

External(\_SB.PC00.XHCI, DeviceObj)
External(\_SB.PC00.XDCI, DeviceObj)
External(GBES)
If (LNotEqual(GBES,0)) {
  External(\_SB.PC00.GLAN, DeviceObj)
}
External(\_SB.PC00.XHCI.MEMB)
External(\_SB.PC00.XDCI.D0I3)
External(\_SB.PC00.XDCI.XDCB)
External(\GBEP)
External(\_SB.PC00.XHCI.RHUB, DeviceObj)
External(\_SB.PC00.XHCI.RHUB.SS01, DeviceObj)
External(\_SB.PC00.XHCI.RHUB.SS02, DeviceObj)
External(\_SB.PC00.XHCI.RHUB.HS01, DeviceObj) //xHCI HSP port 1
External(\_SB.PC00.XHCI.RHUB.HS02, DeviceObj) //xHCI HSP port 2

External(PEP0)
External(XHPR)
External(RCG0, IntObj)     // RTD3 Config Setting0(BIT0:Reserved, BIT1:Reserved, BIT6:Card Reader, BIT7:WWAN, BIT8:WSB SIP FAB1 Card reader)
External(RCG1, IntObj)     // RTD3 Config Setting1(BIT0:Sata Port0, BIT1:Sata Port1, BIT2:Sata Port2, BIT3:Sata Port3)
External(\GPRW, MethodObj)
External(P8XH, MethodObj)
External(XDST, IntObj)
External(\SPST, IntObj)
//
// Externs common to ULT0RTD3.asl and FFRDRTD3.asl and exclude for BRRTD3.asl
//

// GPIO methods
External(\_SB.SPMV, MethodObj)
External(\_SB.SGRA, MethodObj)
External(\_SB.SGWP, MethodObj)
External(\_SB.GGIV, MethodObj)
External(\_SB.GGOV, MethodObj)
External(\_SB.SGOV, MethodObj)
External(\_SB.SGII, MethodObj)
External(\_SB.CAGS, MethodObj)
External(\_SB.ISME, MethodObj)


// RTD3 devices and variables
External(\_SB.PC00.I2C0, DeviceObj) //I2C0 Controller
External(\_SB.PC00.I2C0.TPD0, DeviceObj) // Touch pad
External(\_SB.PC00.I2C1, DeviceObj) //I2C1 Controller
External(\_SB.PC00.I2C1.TPL1, DeviceObj) // Touch panel
#ifdef EC_SUPPORT
External(\_SB.PC00.LPCB.H_EC.SPT2)            // SATA_CABLE_PWR_EN bit in EC
External(\_SB.PC00.LPCB.H_EC.ECMD, MethodObj) // EC Command method
External(\_SB.PC00.LPCB.H_EC.ECAV, IntObj)    // EC Driver loaded flag
External(\_SB.PC00.LPCB.H_EC.ECRD, MethodObj) // EC Read Method
External(\_SB.PC00.LPCB.H_EC.ECWT, MethodObj) // EC Write Method
#endif
External(\UAMS)
External(SDS0,FieldUnitObj)
External(SDS1,FieldUnitObj)
External(AUDD,FieldUnitObj)
External(SHSB,FieldUnitObj)
External(VRRD,FieldUnitObj)

External(SPCO,MethodObj)

External(\_SB.CSD0, MethodObj)
External(\_SB.CSD3, MethodObj)
External(DVID)

include("GpioAcpiDefinesVer1.h")
include("GpioAcpiDefinesVer2.h")
include("HsioDefine.asl")

#define RCG1_RTD3_PRT0_ENABLED 0x01
#define RCG1_RTD3_PRT1_ENABLED 0x02
#define RCG1_RTD3_PRT2_ENABLED 0x04
#define RCG1_RTD3_PRT3_ENABLED 0x08
#define RCG1_RTD3_PRT4_ENABLED 0x10
#define RCG1_RTD3_PRT5_ENABLED 0x20
#define RCG1_RTD3_NVM1_ENABLED 0x40
#define RCG1_RTD3_NVM2_ENABLED 0x80
#define RCG1_RTD3_NVM3_ENABLED 0x100

//
// GPIO states mapping
//
#define PIN_GPIO_ACTIVE_LOW 0
#define PIN_GPIO_ACTIVE_HIGH 1

//
// Touch panel bus speed
//
#define TCH_PNL_BUS_SPEED_400K  1
#define TCH_PNL_BUS_SPEED_1M    2

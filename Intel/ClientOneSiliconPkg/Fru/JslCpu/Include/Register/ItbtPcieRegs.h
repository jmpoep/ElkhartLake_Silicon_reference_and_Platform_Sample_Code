/** @file
  Header file for ITBT PCIE IP specific defines.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#ifndef _SA_REGS_ITBT_PCIE_H_
#define _SA_REGS_ITBT_PCIE_H_

#define MAX_ITBT_PCIE_PORT                   0x4
#define SA_ITBT_PCIE_BUS_NUM                 0x0 // Bus      #0
#define SA_ITBT_PCIE_DEV_NUM                 0x7 // Device   #7
#define SA_ITBT_PCIE_0_DEFAULT_FUN_NUM       0x0 // Function #0
#define SA_ITBT_PCIE_1_DEFAULT_FUN_NUM       0x1 // Function #1
#define SA_ITBT_PCIE_2_DEFAULT_FUN_NUM       0x2 // Function #2
#define SA_ITBT_PCIE_3_DEFAULT_FUN_NUM       0x3 // Function #3

#define R_SA_TCSS_PCIE_CFG_MPC               0xD8
#define S_SA_TCSS_PCIE_CFG_MPC               4
#define B_SA_TCSS_PCIE_CFG_MPC_SRL           BIT23

#define R_SA_VTD_ITBT_PCIE_UBAR              0x58C
#define R_SA_VTD_ITBT_PCIE_LBAR              0x590
//
// PCIE PCRs
//
#define R_TCSS_PCIEX_PCD                     0x3E00                  ///< Port Configuration and Disable (PCD)
#define B_TCSS_PCIEX_PCD_RP0FN               (BIT2 | BIT1 | BIT0)    ///< Port 0 Function Number
#define B_TCSS_PCIEX_PCD_RP0CH               BIT3                    ///< Port 0 config hide

#define R_TCSS_PCIEX_SRL                     0x3E24                  ///< Secured Register Lock (SRL)
#define B_TCSS_PCIEX_SRL                     BIT0                    ///< Secured Register Lock BIT (SRL)
#endif

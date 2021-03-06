/** @file

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 Intel Corporation.

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

//
// Automatically generated by ACE ver 1.63 PIRQTRANS
// Please DO NOT modify !!!
//

#define BUS_NUMBER_TRANSLATOR_DATA { \
/* Bus#(Build), Bus#(RUN), BridgeDevFun#, BridgeDevFun#, ..., -1 */ \
/* --------------------------------------------------------------------------- */ \
  0x00, 0, 0x00, (UINT8)-1,  /* Host Bridge*/ \
  0x01, 0, 0x00, 0x08, (UINT8)-1,  /* P.E.G. Root Port D1F0 -> Host Bridge*/ \
  0x02, 0, 0x00, 0x09, (UINT8)-1,  /* P.E.G. Root Port D1F1 -> Host Bridge*/ \
  0x03, 0, 0x00, 0x0A, (UINT8)-1,  /* P.E.G. Root Port D1F2 -> Host Bridge*/ \
  0x04, 0, 0x00, 0xD8, (UINT8)-1,  /* PCIE Root Port #17 -> Host Bridge*/ \
  0x05, 0, 0x00, 0xD9, (UINT8)-1,  /* PCIE Root Port #18 -> Host Bridge*/ \
  0x06, 0, 0x00, 0xDA, (UINT8)-1,  /* PCIE Root Port #19 -> Host Bridge*/ \
  0x07, 0, 0x00, 0xDB, (UINT8)-1,  /* PCIE Root Port #20 -> Host Bridge*/ \
  0x08, 0, 0x00, 0xE0, (UINT8)-1,  /* PCIE Root Port #1 -> Host Bridge*/ \
  0x09, 0, 0x00, 0xE1, (UINT8)-1,  /* PCIE Root Port #2 -> Host Bridge*/ \
  0x0a, 0, 0x00, 0xE2, (UINT8)-1,  /* PCIE Root Port #3 -> Host Bridge*/ \
  0x0b, 0, 0x00, 0xE3, (UINT8)-1,  /* PCIE Root Port #4 -> Host Bridge*/ \
  0x0c, 0, 0x00, 0xE4, (UINT8)-1,  /* PCIE Root Port #5 -> Host Bridge*/ \
  0x0d, 0, 0x00, 0xE5, (UINT8)-1,  /* PCIE Root Port #6 -> Host Bridge*/ \
  0x0e, 0, 0x00, 0xE6, (UINT8)-1,  /* PCIE Root Port #7 -> Host Bridge*/ \
  0x0f, 0, 0x00, 0xE7, (UINT8)-1,  /* PCIE Root Port #8 -> Host Bridge*/ \
  0x10, 0, 0x00, 0xE8, (UINT8)-1,  /* PCIE Root Port #9 -> Host Bridge*/ \
  0x11, 0, 0x00, 0xE9, (UINT8)-1,  /* PCIE Root Port #10 -> Host Bridge*/ \
  0x12, 0, 0x00, 0xEA, (UINT8)-1,  /* PCIE Root Port #11 -> Host Bridge*/ \
  0x13, 0, 0x00, 0xEB, (UINT8)-1,  /* PCIE Root Port #12 -> Host Bridge*/ \
  0x14, 0, 0x00, 0xEC, (UINT8)-1,  /* PCIE Root Port #13 -> Host Bridge*/ \
  0x15, 0, 0x00, 0xED, (UINT8)-1,  /* PCIE Root Port #14 -> Host Bridge*/ \
  0x16, 0, 0x00, 0xEE, (UINT8)-1,  /* PCIE Root Port #15 -> Host Bridge*/ \
  0x17, 0, 0x00, 0xEF, (UINT8)-1,  /* PCIE Root Port #16 -> Host Bridge*/ \
/* NOTE: Bus#(RUN) is filled by IrqBoardInfo code after enumerating all PCI devices */ \
/* and reassigning the bus numbers in IRQ routing table. */ \
}

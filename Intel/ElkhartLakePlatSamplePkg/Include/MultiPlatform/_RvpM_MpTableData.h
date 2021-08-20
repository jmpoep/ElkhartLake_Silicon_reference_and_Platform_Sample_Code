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

#define MP_TABLE_IRQ_DATA { \
/*+-------------------+----------------+----------------+----------------+----------------+*/ \
/*| Device Location   | Int A Pin      | Int B Pin      | Int C Pin      | Int D Pin      |*/ \
/*+-------------------+----------------+----------------+----------------+----------------+-----------+*/ \
/*| PCI Bus  Device   | APIC    IO APIC| APIC    IO APIC| APIC    IO APIC| APIC    IO APIC| Reserved  |*/ \
/*| Number   Number   | Input#  ID#    | Input#  ID#    | Input#  ID#    | Input#  ID#    | must be 0 |*/ \
/*+-------------------+----------------+----------------+----------------+----------------+-----------+*/ \
  { 0x00,    0x01,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x01 :Pin0: P.E.G. Root Port D1F0 ( Fn# 0x00) :Pin1: P.E.G. Root Port D1F0 ( Fn# 0x00) :Pin2: P.E.G. Root Port D1F0 ( Fn# 0x00) :Pin3: P.E.G. Root Port D1F0 ( Fn# 0x00)*/ \
  { 0x01,    0x00,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x00, Slot 16 */ \
  { 0x02,    0x00,   {{ 17,     0x02}, { 18,     0x02}, { 19,     0x02}, { 16,     0x02}},  0 }, /* Device #0x00, Slot 17 */ \
  { 0x03,    0x00,   {{ 18,     0x02}, { 19,     0x02}, { 16,     0x02}, { 17,     0x02}},  0 }, /* Device #0x00, Slot 18 */ \
  { 0x00,    0x02,   {{ 16,     0x02}, { 00,     0x00}, { 00,     0x00}, { 00,     0x00}},  0 }, /* Device #0x02 :Pin0: I.G.D. ( Fn# 0x00)*/ \
  { 0x00,    0x03,   {{ 16,     0x02}, { 00,     0x00}, { 00,     0x00}, { 00,     0x00}},  0 }, /* Device #0x03 :Pin0: SA Audio Device ( Fn# 0x00)*/ \
  { 0x00,    0x04,   {{ 16,     0x02}, { 00,     0x00}, { 00,     0x00}, { 00,     0x00}},  0 }, /* Device #0x04 :Pin0: SA Thermal Device ( Fn# 0x00)*/ \
  { 0x00,    0x07,   {{ 16,     0x02}, { 00,     0x00}, { 00,     0x00}, { 00,     0x00}},  0 }, /* Device #0x07 :Pin0: SA Chap Device ( Fn# 0x00)*/ \
  { 0x00,    0x08,   {{ 16,     0x02}, { 00,     0x00}, { 00,     0x00}, { 00,     0x00}},  0 }, /* Device #0x08 :Pin0: SA GNA Device ( Fn# 0x00)*/ \
  { 0x00,    0x0D,   {{ 16,     0x02}, { 00,     0x00}, { 00,     0x00}, { 00,     0x00}},  0 }, /* Device #0x0D :Pin0: SA XHCI Device ( Fn# 0x00)*/ \
  { 0x00,    0x13,   {{ 20,     0x02}, { 00,     0x00}, { 00,     0x00}, { 00,     0x00}},  0 }, /* Device #0x13 :Pin0: Integrated Sensor Hub(ISH) ( Fn# 0x00)*/ \
  { 0x00,    0x14,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x14 :Pin0: USB 3.0 xHCI Controller ( Fn# 0x00) :Pin1: USB 3.0 xHCI Controller ( Fn# 0x00) :Pin2: USB 3.0 xHCI Controller ( Fn# 0x00) :Pin3: USB 3.0 xHCI Controller ( Fn# 0x00)*/ \
  { 0x00,    0x16,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x16 :Pin0: ME ( Fn# 0x00) :Pin1: ME ( Fn# 0x00) :Pin2: ME ( Fn# 0x00) :Pin3: ME ( Fn# 0x00)*/ \
  { 0x00,    0x17,   {{ 16,     0x02}, { 00,     0x00}, { 00,     0x00}, { 00,     0x00}},  0 }, /* Device #0x17 :Pin0: SATA Controller ( Fn# 0x00)*/ \
  { 0x00,    0x1B,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x1B :Pin0: PCIE Root Port #17 ( Fn# 0x00) :Pin1: PCIE Root Port #17 ( Fn# 0x00) :Pin2: PCIE Root Port #17 ( Fn# 0x00) :Pin3: PCIE Root Port #17 ( Fn# 0x00)*/ \
  { 0x04,    0x00,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x05,    0x00,   {{ 17,     0x02}, { 18,     0x02}, { 19,     0x02}, { 16,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x06,    0x00,   {{ 18,     0x02}, { 19,     0x02}, { 16,     0x02}, { 17,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x07,    0x00,   {{ 19,     0x02}, { 16,     0x02}, { 17,     0x02}, { 18,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x00,    0x1C,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x1C :Pin0: PCIE Root Port #1 ( Fn# 0x00) :Pin1: PCIE Root Port #1 ( Fn# 0x00) :Pin2: PCIE Root Port #1 ( Fn# 0x00) :Pin3: PCIE Root Port #1 ( Fn# 0x00)*/ \
  { 0x08,    0x00,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x00, Slot 33 */ \
  { 0x09,    0x00,   {{ 17,     0x02}, { 18,     0x02}, { 19,     0x02}, { 16,     0x02}},  0 }, /* Device #0x00, Slot 34 */ \
  { 0x0A,    0x00,   {{ 18,     0x02}, { 19,     0x02}, { 16,     0x02}, { 17,     0x02}},  0 }, /* Device #0x00, Slot 08 */ \
  { 0x0B,    0x00,   {{ 19,     0x02}, { 16,     0x02}, { 17,     0x02}, { 18,     0x02}},  0 }, /* Device #0x00, Slot 09 */ \
  { 0x0C,    0x00,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x00, Slot 10 */ \
  { 0x0D,    0x00,   {{ 17,     0x02}, { 18,     0x02}, { 19,     0x02}, { 16,     0x02}},  0 }, /* Device #0x00, Slot 16 */ \
  { 0x0E,    0x00,   {{ 18,     0x02}, { 19,     0x02}, { 16,     0x02}, { 17,     0x02}},  0 }, /* Device #0x00, Slot 17 */ \
  { 0x0F,    0x00,   {{ 19,     0x02}, { 16,     0x02}, { 17,     0x02}, { 18,     0x02}},  0 }, /* Device #0x00, Slot 18 */ \
  { 0x00,    0x1D,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x1D :Pin0: PCIE Root Port #9 ( Fn# 0x00) :Pin1: PCIE Root Port #9 ( Fn# 0x00) :Pin2: PCIE Root Port #9 ( Fn# 0x00) :Pin3: PCIE Root Port #9 ( Fn# 0x00)*/ \
  { 0x10,    0x00,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x11,    0x00,   {{ 17,     0x02}, { 18,     0x02}, { 19,     0x02}, { 16,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x12,    0x00,   {{ 18,     0x02}, { 19,     0x02}, { 16,     0x02}, { 17,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x13,    0x00,   {{ 19,     0x02}, { 16,     0x02}, { 17,     0x02}, { 18,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x14,    0x00,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x15,    0x00,   {{ 17,     0x02}, { 18,     0x02}, { 19,     0x02}, { 16,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x16,    0x00,   {{ 18,     0x02}, { 19,     0x02}, { 16,     0x02}, { 17,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x17,    0x00,   {{ 19,     0x02}, { 16,     0x02}, { 17,     0x02}, { 18,     0x02}},  0 }, /* Device #0x00, Slot 00 */ \
  { 0x00,    0x1F,   {{ 16,     0x02}, { 17,     0x02}, { 18,     0x02}, { 19,     0x02}},  0 }, /* Device #0x1F :Pin0: LPC Bridge ( Fn# 0x00) :Pin1: LPC Bridge ( Fn# 0x00) :Pin2: LPC Bridge ( Fn# 0x00) :Pin3: LPC Bridge ( Fn# 0x00)*/ \
}

#define MP_TABLE_APIC_DATA { \
/*+----------------------+----------+*/ \
/*| IO APIC     IO APIC  | IO APIC  |*/ \
/*| Address     ID(BUILD)| ID(POST) |*/ \
/*+----------------------+----------+*/ \
  {{ 0xFEC00000}, 0x02, 0x00}, /* 000 : Int vector base. IO APIC to serve Legacy Interrupts */ \
}

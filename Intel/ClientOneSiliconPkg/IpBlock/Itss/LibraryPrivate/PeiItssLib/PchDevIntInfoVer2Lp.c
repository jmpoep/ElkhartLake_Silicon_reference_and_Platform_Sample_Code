/** @file
  PCH Genereation Specific interrupts.

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

#include "ItssLibInternal.h"

//
// mPchTypeDeviceInterruptInfo consist of information for whole range of devices related to PCH. This table must cover
// all possible device and function number (even if they are not a valid device or do not generate an interrupt).
// Data in table must be arranged in asceding order to be correctly consumed by functions which use it.
//
GLOBAL_REMOVE_IF_UNREFERENCED CONST PCH_DEV_INT_INFO mPchLpDeviceInterruptInfo[] = {
  {16, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: I2C #6
  {16, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: I2C #7
  {16, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // BT CNVi
  {16, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_ISH }, // FPAK
  {16, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {16, 5, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // IEH
  {16, 6, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // THC #0
  {16, 7, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // THC #1
  {17, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: UART #3
  {17, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: UART #4
  {17, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: UART #5
  {17, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: UART #6
  {17, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {17, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {17, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {17, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {18, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_ISH }, // Integrated Sensor Hub
  {18, 1, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {18, 2, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // CSME: PMT,  desn't use interrupts
  {18, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {18, 4, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // CSME: fTPM DMA
  {18, 5, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SCS }, // SCS: UFS #0
  {18, 6, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: SPI #2
  {18, 7, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SCS }, // SCS: UFS #1
  {19, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: SPI #3
  {19, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: SPI #4
  {19, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: SPI #5
  {19, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: SPI #6
  {19, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {19, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {19, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {19, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {20, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // USB 3.0 xHCI Controller
  {20, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_OTG }, // USB Device Controller (OTG)
  {20, 2, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // Share SRAM
  {20, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CNVi WiFi
  {20, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // TraceHub Phantom (ACPI) Function
  {20, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {20, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {20, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {21, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #0
  {21, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #1
  {21, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #2
  {21, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #3
  {21, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {21, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {21, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {21, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {22, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: HECI #1
  {22, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: HECI #2
  {22, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: IDE-Redirection (IDE-R)
  {22, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: Keyboard and Text (KT) Redirection
  {22, 4, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: HECI #3
  {22, 5, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // CSME: HECI #4
  {22, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {22, 7, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // CSME: WLAN
  {23, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_MUST_SET, IRQ_UNIQUE_NO  }, // SATA Controller
  {23, 1, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 2, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {23, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 0, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Reserved (used by RST PCIe Storage Cycle Router)
  {24, 1, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 2, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {24, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {25, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #4
  {25, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo I2C Controller #5
  {25, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo UART Controller #2
  {25, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {25, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {25, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {25, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {25, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 0, VALID_DEV_NO,  0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 1, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 2, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {26, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {27, 0, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {27, 1, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {27, 2, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {27, 3, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {27, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {27, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {27, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {27, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {28, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // PCI Express Port 1
  {28, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTB , IRQ_UNIQUE_NO  }, // PCI Express Port 2
  {28, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTC , IRQ_UNIQUE_NO  }, // PCI Express Port 3
  {28, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTD , IRQ_UNIQUE_NO  }, // PCI Express Port 4
  {28, 4, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // PCI Express Port 5
  {28, 5, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTB , IRQ_UNIQUE_NO  }, // PCI Express Port 6
  {28, 6, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTC , IRQ_UNIQUE_NO  }, // PCI Express Port 7
  {28, 7, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTD , IRQ_UNIQUE_NO  }, // PCI Express Port 8
  {29, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // PCI Express Port 9
  {29, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTB , IRQ_UNIQUE_NO  }, // PCI Express Port 10
  {29, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTC , IRQ_UNIQUE_NO  }, // PCI Express Port 11
  {29, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTD , IRQ_UNIQUE_NO  }, // PCI Express Port 12
  {29, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {29, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {29, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {29, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  {30, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // SerialIo: UART #0
#else
  {30, 0, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: UART #0
#endif
  {30, 1, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: UART #1
  {30, 2, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: SPI #0
  {30, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_NO , INTP_NO_REQ  , IRQ_UNIQUE_SERIALIO}, // SerialIo: SPI #1
#if FixedPcdGet8(PcdEmbeddedEnable) == 0x1
  {30, 4, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }, // TSN Controller
#else
  {30, 4, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
#endif
  {30, 5, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {30, 6, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {30, 7, VALID_DEV_NO , 0            , 0            , 0            , 0              }, // Not a valid PCH device
  {31, 0, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // LPC/eSPI Interface, desn't use interrupts
  {31, 1, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // P2SB, desn't use interrupts
  {31, 2, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // PMC , desn't use interrupts
  {31, 3, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_NO_REQ  , IRQ_UNIQUE_NO  }, // cAVS(Audio, Voice, Speach)
  {31, 4, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_MUST_SET, IRQ_UNIQUE_NO  }, // SMBus Controller
  {31, 5, VALID_DEV_YES, INTERRUPT_NO , 0            , 0            , 0              }, // SPI , desn't use interrupts
  {31, 6, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_MUST_SET, IRQ_UNIQUE_NO  }, // GbE Controller
  {31, 7, VALID_DEV_YES, INTERRUPT_YES, USES_PIRQ_YES, INTP_IS_INTA , IRQ_UNIQUE_NO  }  // TraceHub
};

GLOBAL_REMOVE_IF_UNREFERENCED UINT32 mPchLpDeviceInterruptInfoSize = ARRAY_SIZE (mPchLpDeviceInterruptInfo);

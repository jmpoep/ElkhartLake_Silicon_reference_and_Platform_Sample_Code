/**@file

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2016 Intel Corporation.

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

#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#define EFI_NON_DEVICE_CLASS              0x00
#define EFI_DISK_DEVICE_CLASS             0x01
#define EFI_VIDEO_DEVICE_CLASS            0x02
#define EFI_NETWORK_DEVICE_CLASS          0x04
#define EFI_INPUT_DEVICE_CLASS            0x08
#define EFI_ON_BOARD_DEVICE_CLASS         0x10
#define EFI_OTHER_DEVICE_CLASS            0x20

#define CONFIGURATION_DISABLED            0x0
#define CONFIGURATION_ENABLED             0x1
#define CONFIGURATION_AUTO                0x1

#define SETUP_HD_INTERFACE_IDE            0x0
#define SETUP_HD_INTERFACE_AHCI           0x1
#define SETUP_HD_INTERFACE_RAID           0x2

#define IGD_DISPLAY_DEVICE_IGD            0x0
#define IGD_DISPLAY_DEVICE_PEG            0x1
#define IGD_DISPLAY_DEVICE_PCI            0x2

//
// B7 = LFP2 B6 = EFP2 B5 = TV2 B4 = CRT2 B3 = LFP B2 = EFP B1 = TV B0 = CRT
//
#define IGD_BT_CRT                        0x01
#define IGD_BT_TV                         0x02
#define IGD_BT_EFP                        0x04
#define IGD_BT_LFP                        0x08
#define IGD_BT_CRT2                       0x10
#define IGD_BT_TV2                        0x20
#define IGD_BT_EFP2                       0x40
#define IGD_BT_LFP2                       0x80

#define IGD_BT_CRT_LFP                    0x09
#define IGD_BT_VBIOS_DEFAULT              0
#define IGD_BT_LFPSDVO                    IGD_BT_LFP2
#define IGD_BT_TVSDVO                     IGD_BT_TV2
#define IGD_BT_CRT_LFPSDVO                0x81
#define IGD_BT_CRT_EFP                    0x05
#define IGD_BT_CRT_TV_LFP                 0x0B

#define IGD_GMS_FIXED                     0x0
#define IGD_GMS_DVMT                      0x1

#define STOLEN_MEMORY_1M                  0x0
#define STOLEN_MEMORY_8M                  0x1
//
// Memory labels
//
#define MEMORY_SLOT1_SPEED          0x0200
#define MEMORY_SLOT2_SPEED          0x0201
#define MEMORY_SLOT3_SPEED          0x0202
#define MEMORY_SLOT4_SPEED          0x0203
#define END_MEMORY_SLOT_SPEED       0x020F
#define MEMORY_TCL_DDR2             0x0300
#define MEMORY_TCL_DDR              0x0301
#define MEMORY_TCL_END              0x030F

//
// DVMT5.0 Graphic Memory labels
//
#define DVMT50_MODE                   0x0301

#define DVMT50_PRE_ALLOC              0x0302



//
// GMCH SKUs
//
#define GMCH_CHIPSETTYPE_945GM      0
#define GMCH_CHIPSETTYPE_945PM      1
#define GMCH_CHIPSETTYPE_945GMS     2
#define GMCH_CHIPSETTYPE_945GML     3
#define GMCH_CHIPSETTYPE_945GT      4

#define OPR_SCI                        0x00
#define OPR_SMI                        0x01

#endif

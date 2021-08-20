/** @file
Defines Platform BoardIds

@copyright
  "INTEL CONFIDENTIAL
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
  Intel's suppliers or licensors in any way."

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef _PLATFORM_BOARD_ID_H_
#define _PLATFORM_BOARD_ID_H_

#define FlavorUnknown                       0x0
#define FlavorMobile                        0x1
#define FlavorDesktop                       0x2
#define FlavorWorkstation                   0x3
#define FlavorUpServer                      0x4
#define FlavorEmbedded                      0x5
#define FlavorPlatformMax                   0x6

#define TypeUnknown                         0x0
#define TypeTrad                            0x1
#define TypeUltUlx                          0x2


//
// IceLake Board Id 0x00 - 0x1F
//

// BoardId Reserved for PCD Default SkuId usage
#define BoardIdReserved                  0x00

// TigerLake Board Id 0x01
#define BoardIdTglUDdr4                   0x01
#define BomIdTglUDdr4Main                 0x00
#define BomIdTglUDdr4Ppv                  0x01

// TigerLake Board Id 0x02
#define BoardIdTglUDdr4Sv                 0x02
#define BomIdTglUDdr4SvMain               0x00

// TigerLake Board Id 0x03
#define BoardIdTglULp4Type4               0x03
#define BomIdTglULp4Type4Socketed         0x00
#define BomIdTglULp4Type4SolderDown       0x01

// TigerLake Board Id 0x04
#define BoardIdTglULp5Type4               0x04
#define BomIdTglULp5Type4Socketed         0x00
#define BomIdTglULp5Type4SolderDown       0x01

// TigerLake Board Id 0x05
#define BoardIdTglYLp4Type4Erb            0x05
#define BomIdTglYLp4Type4ErbSocketed      0x00

// TigerLake Board Id 0x06
#define BoardIdTglYLp4Type4               0x06
#define BomIdTglYLp4Type4RvpSocketed      0x00
#define BomIdTglYLp4Type4SolderDown       0x01

// TigerLake Board Id 0x07
#define BoardIdTglYLp4Type4Crb            0x07
#define BomIdTglYLp4SvSocketed            0x00

// TigerLake Board Id 0x0A
#define BoardIdTglUDdr4Erb                0x0A
#define BomIdTglUDdr4Main                 0x00

// TigerLake Board Id 0x0C
#define BoardIdTglULp4Aep                 0x0C

// IceLake Board Id 0x0F
// Making SDS ERB Board ID as 0xF so that it doesn't conflict with any other Board ID
// Actually, for ICL U SDS & ICL U ERB, we are sharing same board with Board ID 0xA
#define BoardIdIclUSdsErb              0x0F
#define BomIdIclUSdsHda                0x00
#define BomIdIclUSdsSndw               0x01

// IceLake Board Id 0x0A
#define BoardIdIclUSds                 0x0A

// IceLake Board Id 0x0C - 0x1F
// Reserved

//
// Simics Boards
//

#define BoardIdUnknown1                     0xffff
#define BoardIdPlatformMax                  0xff
#define BOARD_ID_MASK_5BIT                  0x1f
#define BOARD_ID_MASK_8BIT                  0xff
#define FAB_ID_MASK                         0x7
#define BOM_ID_MASK                         0x7
#define GENERATION_MASK                     0x100

#endif

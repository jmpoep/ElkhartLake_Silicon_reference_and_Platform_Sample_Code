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
// ElkhartLake Board Id 0x00 - 0x3F
//

// BoardId Reserved for PCD Default SkuId usage
#define BoardIdReserved                   0x00

// ElkhartLake Board Id 0x01
#define BoardIdEhlLp4xType4Erb           0x01
#define BomIdEhlLp4xType4Main            0x00

// ElkhartLake Board Id 0x02 - With JSL Silicon
#define BoardIdJslLp4xType4Rvp1          0x02

// ElkhartLake Board Id 0x03
#define BoardIdEhlLp4xType4Rvp1          0x03
#define BomIdEhlLp4xType4Main            0x00
#define BomIdEhlLp4xType4Socketed        0x01
#define BomIdEhlLp4xType4Sv              0x02
#define BomIdEhlLp4xType4Pnp             0x03
#define BomIdEhlLp4xType4Ppv             0x1F

// ElkhartLake Board Id 0x04
#define BoardIdEhlDdr4Type3Rvp2          0x04
#define BomIdEhlDdr4Type3Main            0x00
#define BomIdEhlDdr4Type3Ppv             0x1F

// ElkhartLake Board Id 0x05
#define BoardIdEhlLp4xType3Crb           0x05
#define BomIdEhlLp4xType3Main            0x00

// JasperLake Board Id 0x03
#define BoardIdJslLp4xErb                0x06 // 0x03 change to value 0x06 as it duplicate with EHL

#define BoardIdUnknown1                   0xFFFF

#endif

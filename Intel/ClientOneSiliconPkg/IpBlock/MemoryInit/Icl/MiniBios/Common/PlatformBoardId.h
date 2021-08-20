/** @file
Defines Platform BoardIds
This file is a local MRC copy of Intel\IceLakePlatSamplePkg\Include\PlatformBoardId.h

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

// IceLake Board Id 0x00
#define BoardIdIclUX0Ddr4                 0x00

// IceLake Board Id 0x01
#define BoardIdIclUDdr4Erb                0x01

// IceLake Board Id 0x02 - refer 0x08 [0x02 EOL]
#define BoardIdIclUDdr4                   0x02
#define BomIdIclUDdr4Main                 0x00
#define BomIdIclUDdr4Sv                   0x01
#define BomIdIclUDdr4Ppv                  0x07

// IceLake Board Id 0x03 - refer 0x09 [0x03 will be EOL soon]
#define BoardIdIclULp4Type4               0x03
#define BomIdIclULp4Type4Socketed         0x00
#define BomIdIclULp4Type4SolderDown       0x01
// This BOM ID applies to all ICL-U/Y LPDDR4 RVPs
#define BomIdIclLp4SolderDownLp4x         0x04

// IceLake Board Id 0x04
#define BoardIdIclULp4Type3               0x04
#define BomIdIclULp4Type3Socketed         0x00
#define BomIdIclULp4Type3SolderDown       0x01

// This BOM ID applies to all ICL- U DDR4/LPDDR4 RVPs
#define BomIdIclUDdr4Lp4LegacyDp          0x03

// This BOM ID applies to ICL- EPS SKUs
#define BomIdIclDdr4Lp4Eps                0x02

// IceLake Board Id 0x05
#define BoardIdIclYLp4Erb                 0x05

// IceLake Board Id 0x06
#define BoardIdIclYLp4Type4               0x06
#define BomIdIclYLp4Type4Socketed         0x00
#define BomIdIclYLp4Type4SolderDown       0x01
#define BomIdIclYLp4Type4Ppv              0x07

// IceLake Board Id 0x07
#define BoardIdIclYLp4PnpType4            0x07
#define BomIdIclYLp4PnpType4Socketed      0x00
#define BomIdIclYLp4PnpType4SolderDown    0x01

// IceLake Board Id 0x08 - [Next Rev to 0x02]
#define BoardIdIclUDdr4Type3Tcpd          0x08
#define BomIdIclUDdr4Type3TcpdMain        0x00
#define BomIdIclUDdr4Type3TcpdSv          0x01
#define BomIdIclUDdr4Type3TcpdPpv         0x07

//virtual bom id for BoardIdIclUDdr4Type3Tcpd mdvp setup
#define BomIdIclUDdr4Type3MdvpCfgA        0x11
#define BomIdIclUDdr4Type3MdvpCfgB        0x21
#define BomIdIclUDdr4Type3MdvpCfgC        0x31
#define BomIdIclUDdr4Type3MdvpCfgD        0x41

// IceLake Board Id 0x09 - [Next Rev to 0x03]
#define BoardIdIclULp4Type4Tcpd           0x09
#define BomIdIclULp4Type4TcpdSocketed     0x00
#define BomIdIclULp4Type4TcpdSolderDown   0x01
#define BomIdIclULp4Type4TcpdBomId6       0x06
#define FabIdIclULp4Type4TcpdFabId1       0x01

// IceLake Board Id 0x0B
#define BoardIdIclURvpC                   0x0B
#define BomIdIclURvpCHda                  0x00
#define BomIdIclURvpSndw                  0x01

// IceLake Board Id 0x0C
#define BoardIdIclUSds                    0x0C
#define BomIdIclUSdsHda                   0x02
#define BomIdIclUSdsSndw                  0x03
#define FabIdIclUSdsLp4xFabId2            0x02
#define FabIdIclUSdsLp4xFabId3            0x03

// IceLake Board Id 0x0D
#define BoardIdIclYRvpC                   0x0D
#define BomIdIclYRvpCHda                  0x00
#define BomIdIclYRvpSndw                  0x01

// KeystoneLake Board ID 0x10
#define BoardIdKslILp4Type4Rvp            0x10

// IceLake Board Id 0x12
#define BoardIdIclUDdr4Type3TcpdTlc       0x12
#define BomIdIclUDdr4Type3TcpdTlcMain     0x00
#define BomIdIclUDdr4Type3TcpdTlcSv       0x01
#define BomIdIclUDdr4Type3TcpdTlcRetExp   0x05
#define BomIdIclUDdr4Type3TcpdTlcPpv      0x07

// IceLake Board Id 0x16
#define BoardIdIclYLp4Type4Tlc            0x16
#define BoardIdIclYLp4Type4TlcRetExp      0x05
#define FabIdIclYLp4Type4TlcFabId3        0x03

// IceLake Board Id 0x17
#define BoardIdIclYLp4PnpType4Tlc         0x17
#define BomIdIclYLp4PnpType4TlcSocketed   0x00
#define BomIdIclYLp4PnpType4TlcSolderDown 0x01

// IceLake Board Id 0x18
#define BoardIdIclYNRvp                   0x18
#define FabIdIclYNRvpFabId1               0x01

// IceLake Board Id 0x19
#define BoardIdIclUNRvp                   0x19
#define FabIdIclUNRvpFabId1               0x01
#define BomIdIclUNLp4xSingleRank          0x07

// IceLake Board Id 0x1B
#define BoardIdIclYLp4Type4TlcEv          0x1b


// IceLake Board Id 0x20
#define BoardIdIclHDdr4Erb                0x20

// IceLake Board Id 0x21
#define BoardIdIclHDdr4                   0x21

// IceLake Board Id 0x22
#define BoardIdIclHLp4Type4Erb            0x22

// IceLake Board Id 0x23
#define BoardIdIclHLp4Type4               0x23





// LceLake Board Id 0x30
#define BoardIdIclSUDimmErb               0x30

// Icelake Board Id 0x31
#define BoardIdIclSSodimmErb              0x31

// Icelake Board Id 0x32
#define BoardIdIclSUdimmOcErb             0x32

// Icelake Board Id 0x34
#define BoardIdIclSUdimm                  0x34

// Icelake Board Id 0x35
#define BoardIdIclSSodimm                 0x35

// Icelake Board Id 0x36
#define BoardIdIclSUdimmOc                0x36

//#define BoardIdIclHSODimmErb              0x20  //Icelake H SO-DIMM ERB


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

#define BoardIdUnknown1                     0xffff

#endif

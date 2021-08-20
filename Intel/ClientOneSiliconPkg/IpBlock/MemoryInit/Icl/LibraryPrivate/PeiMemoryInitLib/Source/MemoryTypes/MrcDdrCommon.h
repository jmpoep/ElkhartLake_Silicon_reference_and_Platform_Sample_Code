/** @file
  Defines functions and constants that are used to interact with various
  DDR technologies.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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
#ifndef _MRC_DDR_COMMON_H_
#define _MRC_DDR_COMMON_H_

///
/// Defines and Enumeration
///
typedef enum {
  MRC_ZQ_INIT,  ///< DDR4: ZQCL with tZQinit, LPDDR4: Not used
  MRC_ZQ_LONG,  ///< DDR4: ZQCL with tZQoper, LPDDR4: Not used
  MRC_ZQ_SHORT, ///< DDR4: ZQCS with tZQCS,   LPDDR4: Not used
  MRC_ZQ_RESET, ///< DDR4: Not used,          LPDDR4: ZQ Reset with tZQReset
  MRC_ZQ_CAL,   ///< DDR4: Not used,          LPDDR4: ZQ Cal and ZQ Latch (tZQCAL, tZQLAT)
  MRC_ZQ_MAX
} MrcZqType;

typedef enum {
  oi1DPC1R  = 0,
  oi1DPC2R,
  oi2DPC1R1R,
  oi2DPC1R2R,
  oi2DPC2R1R,
  oi2DPC2R2R,
  oiNotValid
} TOdtIndex;

///
/// Structs
///
typedef union {
  UINT8 Lp3MrNum;
  struct {
    UINT8 MrNum       : 6;  ///< Bits 0:5
    UINT8 Spare       : 1;  ///< Bits 6
    UINT8 Erh34Select : 1;  ///< Bits 7
  } Lp4MrrMrw;
  struct {
    UINT8 MpcOp       : 7;  ///< Bits 0:6
    UINT8 Erh34Select : 1;  ///< Bits 7
  } Lp4Mpc;
  struct {
    UINT8 MrNum       : 3;  ///< Bits 0:2
    UINT8 MA12To8     : 5;  ///< Bits 3:7
  } Ddr3Ddr4Mrs;
  struct {
    UINT8 MprPage     : 2;  ///< Bits 0:1
    UINT8 MprNum      : 2;  ///< Bits 2:3
    UINT8 Spare       : 4;  ///< Bits 4:7
  } DdrMprRdWr;
  UINT8 Data8;
} MRC_MRH_ADDRESS_TYPE;

///
/// Function Declarations
///
/**
  This function executes the MRH (Mode Register Handler).

  @param[in] MrcData    - Include all MRC global data.
  @param[in] Channel    - the channel to work on
  @param[in] SubChannel - the sub-channel to work on
  @param[in] Rank       - the rank to work on
  @param[in] Address    - MRW address
  @param[in] Data       - MRW Data
  @param[in] MrhCmd     - MRH command, see MRC_MRH_CMD_xxx defines

  @retval mrcSuccess    - MRW was sent successfully
  @retval mrcDeviceBusy - timed out waiting for MRH
**/
MrcStatus
MrcRunMrh (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                SubChannel,
  IN  UINT32                Rank,
  IN  UINT32                Address,
  IN  UINT32                Data,
  IN  UINT8                 MrhCmd
  );
#endif // _MRC_DDR_COMMON_H_


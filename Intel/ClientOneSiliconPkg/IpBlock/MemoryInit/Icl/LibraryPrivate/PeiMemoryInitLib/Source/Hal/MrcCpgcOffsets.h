/** @file
  This file contains functions to get CPGC Offsets
  used memory training.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2017 Intel Corporation.

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
#ifndef _MRC_CPGC_OFFSETS_H_
#define _MRC_CPGC_OFFSETS_H_

typedef enum {
  MrcClMuxRd,
  MrcClMuxWr,
  MrcClMuxMax
} MRC_CL_MUX_DIR;

/**
  This function returns the offset of the error status register.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Channel - 0-based index specifying which channel control to program.
  @param[in]  Subchannel - 0-based index specifying which subchannel (of the big channel) control to program.

  @retval - MCHBAR Register Offset.
**/
UINT32
MrcGetTestErrStatOffset (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                Subchannel
  );

/**
  This function returns the offset of the error control register.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Channel - 0-based index specifying which channel control to program.
  @param[in]  Subchannel - 0-based index specifying which subchannel (of the big channel) control to program.

  @retval - MCHBAR Register Offset.
**/
UINT32
MrcGetTestErrCtlOffset (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                Subchannel
  );

/**
  This function returns the offset of the disabling errors per bit in byte 0-3 register.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Channel - 0-based index specifying which channel control to program.
  @param[in]  Subchannel - 0-based index specifying which subchannel (of the big channel) control to program.

  @retval - MCHBAR Register Offset.
**/
UINT32
MrcGetCpgcErrCheckingLowOffset (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                Subchannel
  );

/**
  This function returns the offset of the disabling errors per bit in byte 4-7 register for DDR4.  Same register offset is used as Chunk check Enabler for LPDDR4.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Channel - 0-based index specifying which channel control to program.
  @param[in]  Subchannel - 0-based index specifying which subchannel (of the big channel) control to program.

  @retval - MCHBAR Register Offset.
**/
UINT32
MrcGetCpgcErrCheckingHighOffset (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Channel,
  IN  UINT32                Subchannel
  );

/**
  This function returns the register offset for the ECC error mask and Rank error mask register.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Channel - 0-based index specifying which channel control to program.
  @param[in]  Subchannel - 0-based index specifying which subchannel (of the big channel) control to program.

  @retval - MCHBAR Register Offset.
**/
UINT32
MrcGetEccErrMskRankErrMskOffset (
  IN  MrcParameters *const  MrcData,
  IN  UINT32        const   Channel,
  IN  UINT32                Subchannel
  );

/**
  This function returns the register offset for the CPGC seq config register.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Channel - 0-based index specifying which channel control to program.
  @param[in]  Subchannel - 0-based index specifying which subchannel (of the big channel) control to program.

  @retval - MCHBAR Register Offset.
**/
UINT32
MrcGetCpgcSeqCfgOffset (
  IN  MrcParameters *const  MrcData,
  IN  UINT32        const   Channel,
  IN  UINT32                Subchannel
  );

/**
  This returns the read or write offset for the Cacheline Mux Pattern Buffer.

  @param[in]  MrcData   - Pointer to global MRC data.
  @param[in]  Direction - Specifies which traffic Mux to program.
  @param[in]  Index     - 0-based index specifying which Mux to program.

  @retval - MCHBAR Register Offset.

UINT32
MrcGetClMuxPbOffset (
  IN  MrcParameters   *const  MrcData,
  IN  MRC_CL_MUX_DIR  const   Direction,
  IN  UINT32          const   Index
  );
*/
#endif //_MRC_CPGC_OFFSETS_H_


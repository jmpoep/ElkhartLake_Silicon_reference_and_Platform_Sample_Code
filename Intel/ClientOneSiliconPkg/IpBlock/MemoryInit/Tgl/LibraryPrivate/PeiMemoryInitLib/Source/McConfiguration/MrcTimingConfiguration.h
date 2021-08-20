/** @file
  This module configures the memory controller timing parameters.

@copyright
  INTEL CONFIDENTIAL
  Copyright 1999 - 2019 Intel Corporation.

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
#ifndef _MrcTimingConfiguration_h_
#define _MrcTimingConfiguration_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "McAddress.h"
#include "MrcCommon.h"
#include "MrcCrosser.h"
#include "MrcDdr3.h"
#include "MrcGlobal.h"
#if SUPPORT_SODIMM == SUPPORT
#include "MrcSpdProcessing.h"
#endif //SUPPORT_SODIMM == SUPPORT

///
/// HW limits of timing parameters
///
#define TAT_SAFE_VALUE  32
#define tRP_MIN         4   ///< minimum tRP (and tRCD) supported in tCK/wCK
#define tRP_MAX         60  ///< maximum tRP (and tRCD) supported in tCK/wCK

#define tRAS_MIN        9   ///< minimum tRAS (ACT->PRE) supported in tCK/wCK
#define tRAS_MAX        136 ///< maximum tRAS (ACT->PRE) supported in tCK/wCK

#define tRDPRE_MIN      4   ///< minimum tRDPRE (Read->PRE) supported in tCK/wCK
#define tRDPRE_MAX      32  ///< maximum tRDPRE (Read->PRE) supported in tCK/wCK

#define tPPD_MIN        4   ///< minimum tPPD (PRE[A]->PRE[A] same rank) supported in tCK/wCK
#define tPPD_MAX        8   ///< maximum tPPD (PRE[A]->PRE[A] same rank) supported in tCK/wCK

#define tWRPRE_MIN      18  ///< minimum tWRPRE (Write->PRE) supported in tCK/wCK
#define tWRPRE_MAX      200 ///< maximum tWRPRE (Write->PRE) supported in tCK/wCK

#define tFAW_MIN        16
#define tFAW_MAX        128

#define tRRD_MIN        4
#define tRRD_SG_DG_MAX  32

#define tCL_MIN         4
#define tCL_MAX         72

#define tCWL_MIN_LP4    4
#define tCWL_MIN_DDR4   5
#define tCWL_MIN        2
#define tCWL_MAX        64

#define tCKE_MIN        4
#define tCKE_MAX        24

#define tXP_MIN         4
#define tXP_MAX         26

#define tXPDLL_MIN      4
#define tXPDLL_MAX      63

#define tRDPDEN_MIN     4
#define tRDPDEN_MAX     96

#define tWRPDEN_MIN     4
#define tWRPDEN_MAX     204

#define tRDRD_MIN       4
#define tRDRD_MAX       54
#define tRDWR_MIN       4
#define tRDWR_MAX       54
#define tWRRD_MIN       4
#define tWRRD_MAX       54
#define tRDRD_DR_MIN    12
#define tWRRD_DG_MAX    65
#define tWRRD_SG_MAX    145
#define tWRWR_MIN       4
#define tWRWR_MAX       54

#define tPRPDEN_MIN         0
#define tPRPDEN_MAX         3
#define MRC_tPRPDEN_LP4_MIN 4
#define MRC_tPRPDEN_LP5_MIN 8

///
/// tCCD values.
///
#define TCCD_ALL_FREQ     (4) ///< tCCD is = 4 tCK for all frequencies up to 1600.
///
/// tWPRE values.
///
#define TWPRE_ALL_FREQ      (1) ///< tWPRE is = 1 tCK for all frequencies up to 1600.
#define TWPRE_ALL_FREQ_LP4  (2) ///< LPDDR4 requires 2tCK Write Preamble

///
/// tCKE values.
///
#define TCKE_800  (3)
#define TCKE_1067 (3)
#define TCKE_1333 (4)
#define TCKE_1600 (4)
#define TCKE_1867 (5)
#define TCKE_2133 (6)
#define TCKE_2400 (6)
#define TCKE_2667 (7)
#define TCKE_2800 (7)
#define TCKE_2933 (8)
#define TCKE_3000 (8)
#define TCKE_3200 (8)

///
/// tXP value for LPDDR4/5: max(7.5ns, (Lpddr5) ? 3nCK : 5nCK)
///
#define tXP_LPDDR_FS  7500000

///
/// tXP values for DDR4: max(6ns, 4nCK)
///
#define tXP_DDR4_FS   6000000

///
/// tXPDLL values for DDR3: 24ns for all frequencies
///
#define tXPDLL_FS   24000000

///
/// tAONPD values for DDR4: 9ns for all frequencies
///
#define tAONPD_FS 9000000

///
/// tODTon / tODToff values, in [ps]
///
#define tODT_ON_MIN   1750
#define tODT_ON_MAX   3500
#define tODT_OFF_MIN  1750
#define tODT_OFF_MAX  3500

///
/// Specified in PI-Ticks.  64 == 1 QClk
///
#define tDQSCK_DRIFT  64

///
/// tVrefDQ in [ps] - delay between each MR6 in DDR4 PDA mode
///
#define tVREF_DQ_PS      150000

///
/// LPDDR4 De-rate Timing addition 1.875ns
///
#define DERATE_TIMING_PS 1875

/**
  This function configures the memory controller timings.

  @param[in] MrcData - Include all MRC global data.

  @retval Nothing.
**/
extern
void
MrcTimingConfiguration (
  IN MrcParameters *const MrcData
  );

/**
  This function returns the tXP value for the specified frequency in tCK.

  @param[in] DdrType   - DDR type
  @param[in] tCK       - Clock period in femtoseconds.

  @retval The tXP value for the specified frequency.
**/
UINT32
tXPValue (
  IN  MrcDdrType  DdrType,
  IN  UINT32      tCK
  );

/**
  This function sets up the Read ODTD values based on RawCard types and adjusts the tDRRD2RD, tDDRD2RD, tDRRD2WR and tDDRD2WR

  @param[in, out] MrcData - Include all MRC global data.

  @retval Nothing.
**/
extern
void
RdOdtStretch (
  IN OUT MrcParameters *const MrcData
  );

/**
  This function adjusts the relevant TAT when changing Read or Write ODT duration.
  TAT list rdOdt = { drrd2rd, ddrd2rd, drrd2wr, ddrd2wr, srrd2wr_sg, srrd2wr_dg };
  TAT list wrOdt = { drwr2wr, ddwr2wr, drwr2rd, ddwr2rd, srwr2rd_sg, srwr2rd_dg };

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Controller  - Controller to update.
  @param[in]      Channel     - Channel to update.
  @param[in]      OdtType     - rdodtd or wrodtd
  @param[in]      Offset      - signed offset
  @param[in]      UpdateHost  - Switch to update the host struct with the new value.

  @retval Nothing.
**/
void
MrcTatStretch (
  IN OUT MrcParameters *const MrcData,
  IN UINT32                   Controller,
  IN UINT32                   Channel,
  IN UINT8                    OdtType,
  IN INT8                     Offset,
  IN BOOLEAN                  UpdateHost
  );


/**
  Update XARB_TC_BUBBLE_INJ for the given channel according to the current turnaround values.

  @param[in, out] MrcData     - Include all MRC global data.
  @param[in]      Controller  - 0-based index to select the Controller.
  @param[in]      Channel     - 0-based index to select the Channel.

  @retval Nothing.
**/
extern
void
SetTcBubbleInjector (
  IN OUT MrcParameters *const MrcData,
  IN     const UINT32         Controller,
  IN     const UINT32         Channel
  );

#endif // _MrcTimingConfiguration_h_


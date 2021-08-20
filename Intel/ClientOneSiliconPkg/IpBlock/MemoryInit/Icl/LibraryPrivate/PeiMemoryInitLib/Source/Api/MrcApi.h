/** @file
  Mrc definition of supported features.

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
#ifndef _MrcApi_h_
#define _MrcApi_h_

#include "MrcTypes.h"
#include "MrcInterface.h"

#define MRC_TIMER_1NS     (1)
#define MRC_TIMER_1US     (1000)
#define MRC_TIMER_1MS     (1000 * 1000)
#define MRC_TIMER_1S      (1000 * 1000 * 1000)

#define START_TEST_DELAY  (60)
#define IO_RESET_DELAY    (60)

// Max Possible Vrefs
#define MAX_RX_VREF_OFFSET           62      ///< Maximum possible Rx Vref Offset
#define MAX_DDR4_CMD_VREF_OFFSET     63      ///< Maximum possible Vref Offset for DDR4 Cmd
#define MAX_POSSIBLE_DDR4_WRITE_VREF 36      ///< Maximum possible margin for DDR4 Write Vref
#define MAX_POSSIBLE_RX_VREF_MARGIN  31      ///< Maximum possible Rx margin for Vref
// Max Possible Timing
#define MAX_POSSIBLE_TIME           31      ///< Maximum possible margin for time
#define MAX_POSSIBLE_TIME_G2        63      ///< Maximum possible margin for time in Gear2

#define COMP_INT                    0x0A    ///< For 10ms
#define MID_INT_VREF                192     ///< Middle of InternalVref Range TxVref/CaVref
#define TXEQFULLDRV                 (0x30)  ///< SKL - 15 Emphasize legs (not trained)
#define DIMMRON                     (ODIC_RZQ_6)

///
/// Compile time configuration parameters - START.
/// The user must set these values for the system.
///
#define DIMMSIZEMIN            512         ///< The minimum size of DIMM, in MBytes.
#define DIMMSIZEMAX            (32 * 1024) ///< The maximum size of DIMM, in MBytes.

#define FREQMIN                f1067       ///< The minimum valid frequency.


#define DDR4_VREF_STEP_SIZE          7800  // in micro volt
#define DDR4_VREF_MIDDLE_RANGE       820   // DDR4 middle range in milli volt

#define SUPPORT_FORCE          UNSUPPORT   ///< SUPPORT means to force tAA, tRCD, tRP to the same value.
#define SUPPORT_ALLDIMMS       UNSUPPORT   ///< SUPPORT means all timings across all DIMMs in the system.
                                           ///< UNSUPPORT means all timings across each memory channel's DIMMs.
#define SUPPORT_ECC            SUPPORT     ///< SUPPORT means ECC is suppported, else UNSUPPORT.
#define SUPPORT_UDIMM          SUPPORT     ///< SUPPORT means that unbuffered DIMMs are supported, else UNSUPPORT.
#define SUPPORT_SODIMM         SUPPORT     ///< SUPPORT means that SO-DIMMs are supported, else UNSUPPORT.
#define SUPPORT_RDIMM          UNSUPPORT   ///< SUPPORT means that registered DIMMs are supported, else UNSUPPORT.
#define SUPPORT_PRIWIDTH_8     UNSUPPORT   ///< SUPPORT means that SDRAM primary bus width of 8 is supported by the system.
#define SUPPORT_PRIWIDTH_16    UNSUPPORT   ///< SUPPORT means that SDRAM primary bus width of 16 is supported by the system.
#define SUPPORT_PRIWIDTH_32    SUPPORT     ///< SUPPORT means that SDRAM primary bus width of 32 is supported by the system.
#define SUPPORT_PRIWIDTH_64    SUPPORT     ///< SUPPORT means that SDRAM primary bus width of 64 is supported by the system.

#define SUPPORT_ROW_12         SUPPORT     ///< SUPPORT means that 12 bit size is supported by the system.
#define SUPPORT_ROW_13         SUPPORT     ///< SUPPORT means that 13 bit size is supported by the system.
#define SUPPORT_ROW_14         SUPPORT     ///< SUPPORT means that 14 bit size is supported by the system.
#define SUPPORT_ROW_15         SUPPORT     ///< SUPPORT means that 15 bit size is supported by the system.
#define SUPPORT_ROW_16         SUPPORT     ///< SUPPORT means that 16 bit size is supported by the system.
#define SUPPORT_ROW_17         SUPPORT     ///< SUPPORT means that 17 bit size is supported by the system.
#define SUPPORT_ROW_18         UNSUPPORT   ///< SUPPORT means that 18 bit size is supported by the system.

#define SUPPORT_BANK_4         SUPPORT     ///< SUPPORT means that 4 banks is supported by the system.
#define SUPPORT_BANK_8         SUPPORT     ///< SUPPORT means that 8 banks is supported by the system.
#define SUPPORT_BANK_16        UNSUPPORT   ///< SUPPORT means that 16 banks is supported by the system.
#define SUPPORT_BANK_32        UNSUPPORT   ///< SUPPORT means that 32 banks is supported by the system.
#define SUPPORT_BANK_64        UNSUPPORT   ///< SUPPORT means that 64 banks is supported by the system.

#define TAAMINPOSSIBLE         4           ///< tAAmin possible range, in number of tCK cycles.
#define TAAMAXPOSSIBLE         24
#define TWRMINPOSSIBLE         5           ///< tWRmin possible range, in number of tCK cycles.
#define TWRMAXPOSSIBLE         16          ///< tWRmin values of 9, 11, 13 ,15 are not valid for DDR3.
#define TRCDMINPOSSIBLE        4           ///< tRCDmin possible range, in number of tCK cycles.
#define TRCDMAXPOSSIBLE        20
#define TRRDMINPOSSIBLE        4           ///< tRRDmin possible range, in number of tCK cycles.
#define TRRDSMINPOSSIBLE       4           ///< tRRD_Smin possible range, in number of tCK cycles.
#define TRRDSMAXPOSSIBLE       10
#define TRRDLMINPOSSIBLE       4           ///< tRRD_Lmin possible range, in number of tCK cycles.
#define TRRDLMAXPOSSIBLE       15
#define TRPMINPOSSIBLE         4           ///< tRPmin possible range, in number of tCK cycles.
#define TRPABMINPOSSIBLE       4           ///< tRPabmin possible range, in number of tCK cycles.
#define TRASMINPOSSIBLE        10          ///< tRASmin possible range, in number of tCK cycles.
#define TRASMAXPOSSIBLE        40
#define TRCMINPOSSIBLE         1           ///< tRCmin possible range, in number of tCK cycles.
#define TRCMAXPOSSIBLE         4095
#define TRFCMINPOSSIBLE        1           ///< tRFCmin possible range, in number of tCK cycles.
#define TRFCMAXPOSSIBLE        1023
#define TWTRMINPOSSIBLE        4           ///< tWTRmin possible range, in number of tCK cycles.
#define TWTRMAXPOSSIBLE        10
#define TWTRSMINPOSSIBLE       2           ///< tWTR_S possible range, in number of tCK cycles.
#define TWTRSMAXPOSSIBLE       4
#define TWTRLMINPOSSIBLE       4           ///< tWTR_L possible range, in number of tCK cycles.
#define TWTRLMAXPOSSIBLE       11
#define TRTPMINPOSSIBLE        4           ///< tRTPmin possible range, in number of tCK cycles.
#define TRTPMAXPOSSIBLE        15
#define TFAWMINPOSSIBLE        10          ///< tFAWmin possible range, in number of tCK cycles.
#define TFAWMAXPOSSIBLE        54
#define TCWLMINPOSSIBLE        5           ///< tCWLmin possible range, in number of tCK cycles.
#define TCWLMAXPOSSIBLE        12
#define TREFIMINPOSSIBLE       1           ///< tREFImin possible range, in number of tCK cycles.
#define TREFIMAXPOSSIBLE       65535
#define NMODEMINPOSSIBLE       1           ///< Command rate mode min possible range, in number of tCK cycles.
#define NMODEMAXPOSSIBLE       3

#define DDR4_TRTPMINPOSSIBLE   5           ///< tRTPmin possible range, in number of tCK cycles.
#define DDR4_TRTPMAXPOSSIBLE   12          ///< tRTPmin value of 11 is not valid for DDR4.
#define DDR4_TWRMINPOSSIBLE    10          ///< tWRmin possible range, in number of tCK cycles.
#define DDR4_TWRMAXPOSSIBLE    24          ///< tWRmin values of odd numbers and 22 not valid for DDR4.
#define DDR4_TCWLMINPOSSIBLE   9           ///< tCWLmin possible range, in number of tCK cycles.
#define DDR4_TCWLMAXPOSSIBLE   18

#define LPDDR3_TRTPMINPOSSIBLE  4           ///< tRTPmin possible range, in number of tCK cycles.
#define LPDDR3_TCWLMINPOSSIBLE  3           ///< tCWLmin possible range, in number of tCK cycles.
#define LPDDR3_TCWLMAXPOSSIBLE  13
#define LPDDR4_TRTPMINPOSSIBLE  8           ///< tRTPmin possible range, in number of tCK cycles.
#define LPDDR4_TCWLMINPOSSIBLE  4           ///< tCWLmin possible range, in number of tCK cycles.
#define LPDDR4_TCWLMAXPOSSIBLE
#define LPDDR_TWRMINPOSSIBLE    4           ///< tWRminpossible range, in number of tCK cycles.

#define HOST_BRIDGE_BUS        0           ///< The host bridge bus number.
#define HOST_BRIDGE_DEVICE     0           ///< The host bridge device number.
#define HOST_BRIDGE_FUNCTION   0           ///< The host bridge function number.
#define HOST_BRIDGE_DEVID      0           ///< The host bridge device id offset.
#define HOST_BRIDGE_REVID      8           ///< The host bridge revision id offset.

#define MEMORY_RATIO_MIN       0           ///< The minimum DDR ratio value that the hardware supports.
#define MEMORY_RATIO_MAX       255         ///< The maximum DDR ratio value that the hardware supports.

///
/// Compile time configuration parameters - END.
///
#define EYE_MARGIN_SUPPORT       0       ///< Include code to plot 2D eye diagrams
#define DATA_EYE_MARGIN_SUPPORT  0       ///<  plot 2D data eye diagrams in RMT
#define CMD_EYE_MARGIN_SUPPORT   0       ///<  plot 2D cmd eye diagrams in RMT

///
/// Exit mode
///
typedef enum {
  emSlow      = 0,
  emFast      = 1,
  emAuto      = 0xFF,
} MrcExitMode;

///
/// System definitions
///
///
/// Register default values
///
#define MRC_DIMM_RANK_INTERLEAVE      (1)
#define MRC_ENHANCED_INTERLEAVE_MODE  (1)

///
///  CPU Mailbox Related Definitions
///
#define MAILBOX_TYPE_PCODE              0x00000001
#define MAILBOX_TYPE_OC                 0x00000002
#define PCODE_MAILBOX_INTERFACE_OFFSET  BIOS_MAILBOX_INTERFACE_PCU_REG
#define PCODE_MAILBOX_DATA_OFFSET       BIOS_MAILBOX_DATA_PCU_REG
#define OC_MAILBOX_MSR                  0x00000150

//
// CPU Mailbox Commands
//
#define CPU_MAILBOX_CMD_SAGV_SET_POLICY         0x00000122
#define SET_EPG_BIOS_POWER_OVERHEAD_0_CMD       0x00000020
#define SET_EPG_BIOS_POWER_OVERHEAD_1_CMD       0x00000120
#define MAILBOX_BIOS_CMD_READ_BIOS_MC_REQ_ERROR 0x00000009  ///< Allows reading the error indication for DDR checks where the memory does not lock.
#define MC_REQ_ERROR_DDR_CHECKS_DDR_CHECKS_PASSED             0
#define MC_REQ_ERROR_DDR_CHECKS_ILLEGAL_BASE_FREQ             1
#define MC_REQ_ERROR_DDR_CHECKS_FAILED_LT_CONDITIONS          2
#define MC_REQ_ERROR_DDR_CHECKS_DDR_FREQ_BELOW_MIN            3
#define MC_REQ_ERROR_DDR_CHECKS_DDR_FREQ_ABOVE_OC_LIMIT       4
#define MC_REQ_ERROR_DDR_CHECKS_DDR_FREQ_ABOVE_DMFC_LIMIT     5
#define MC_REQ_ERROR_DDR_CHECKS_DDR_FREQ_100_REF_IS_DISABLED  8
//
// CPU Mailbox Completion Codes
//
#define PCODE_MAILBOX_CC_SUCCESS            0

#define PCU_CR_PLATFORM_INFO (0xCE)

#pragma pack (push, 1)
typedef union {
  struct {
    UINT32                         : 8;
    UINT32 MAX_NON_TURBO_LIM_RATIO : 8;
    UINT32                         : 16;
    UINT32                         : 32;
  } Bits;
  UINT64 Data;
  UINT32 Data32[2];
  UINT16 Data16[4];
  UINT8  Data8[8];
} PCU_CR_PLATFORM_INFO_STRUCT;

#pragma pack (pop)

#endif

/** @file
  By passing in a SPD data structure and platform support values, an output
  structure is populated with DIMM configuration information.

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
#include "MrcSpdProcessing.h"
#include "MrcCommonTypes.h"
#include "MrcMaintenance.h"

#ifdef MRC_DEBUG_PRINT
const char  UnknownString[]    = "unknown";
const char  Ddr4String[]       = "DDR4";
const char  RdimmString[]      = "RDIMM";
const char  UdimmString[]      = "UDIMM";
const char  SodimmString[]     = "SO-DIMM";
const char  Sodimm72String[]   = "72 bit SO-DIMM";
const char  StdString[]        = "Standard";
const char  Xmp1String[]       = "XMP1";
const char  Xmp2String[]       = "XMP2";
const char  XpString[]         = "  XMP profile %u is %sabled and recommended channel config: %u DIMM per channel\n";
const char  ErrorString[]      = "ERROR: Unsupported ";
const char  SpdValString[]     = "SPD value: ";
const char  IsSupString[]      = " is supported";
const char  NotSupString[]     = " is not supported";
const char  TimeBaseString[]   = "Timebase (MTB/FTB)";
const char  tAAString[]        = "CAS Latency Time (tAAmin)";
const char  tCKString[]        = "SDRAM Cycle Time (tCKmin)";
const char  tWRString[]        = "Write recovery time (tWRmin)";
const char  tRCDString[]       = "RAS# to CAS# delay time (tRCDmin)";
const char  tRRDString[]       = "Row active to row active delay time (tRRDmin)";
const char  tRPString[]        = "Row precharge delay time (tRPmin)";
const char  Lpddr4String[]     = "LPDDR4";
const char  Lpddr4xString[]    = "LPDDR4X";
const char  LpDimmString[]     = "LP-DIMM";
const char  MemoryDownString[] = "Memory Down";
const char  tRPabString[]      = "Row precharge delay time for all banks (tRPab)";
const char  tRASString[]       = "Active to precharge delay time (tRASmin)";
const char  tRCString[]        = "Active to active/refresh delay time (tRCmin)";
const char  tRFCString[]       = "Refresh recovery delay time (tRFCmin)";
const char  tRFCpbString[]     = "Per Bank refresh recovery delay time (tRFCpb)";
const char  tWTRString[]       = "Internal write to read command delay time (tWTRmin)";
const char  tRTPString[]       = "Internal read to precharge delay time (tRTPmin)";
const char  tFAWString[]       = "Active to active/refresh delay time (tFAWmin)";
const char  tREFIString[]      = "Average Periodic Refresh Interval (tREFImin)";
const char  tCWLString[]       = "CAS Write Latency (tCWLmin)";
const char  NmodeString[]      = "Command rate mode (Nmode)";
const char  VddString[]        = "Module voltage VDD (mVolts)";
const char  BestCaseString[]   = "Best case value for profiles 0-";
const char  ProfileString[]    = "Profile";
const char  HeaderString[]     = "Profile Controller Channel Dimm Value";
const char  tRRDSString[]      = "Row active to row active delay time (tRRD_Smin)";
const char  tRRDLString[]      = "Row active to row active delay time (tRRD_Lmin)";
const char  tRFC2String[]      = "Refresh recovery delay time (tRFC2min)";
const char  tRFC4String[]      = "Refresh recovery delay time (tRFC4min)";
const char  tWTRLString[]      = "Internal write to read command delay time (tWTR_L)";
const char  tWTRSString[]      = "Internal write to read command delay time (tWTR_S)";
const char  tCCDLSString[]     = "CAS to CAS delay for same bank group (tCCD_L)";
const char  ChannelsPerDieStr[] = "Channels per Die";

const char  RrcString[][3]     = {
                                     " A", " B", " C", " D", " E", " F", " G", " H", " J", " K",
                                     " L", " M", " N", " P", " R", " T", " U", " V", " W", " Y",
                                     "AA", "AB", "AC", "AD", "AE", "AF", "AG", "AH", "AJ", "AK",
                                     "AL", "ZZ", "AM", "AN", "AP", "AR", "AT", "AU", "AV", "AW",
                                     "AY", "BA", "BB", "BC", "BD", "BE", "BF", "BG", "BH", "BJ",
                                     "BK", "BL", "BM", "BN", "BP", "BR", "BT", "BU", "BV", "BW",
                                     "BY", "CA", "CB", "ZZ"};
#endif // MRC_DEBUG_PRINT

GLOBAL_REMOVE_IF_UNREFERENCED const UINT32 SdramCapacityTable[] = {
  (256 / 8), (512 / 8), (1024 / 8), (2048 / 8),
  (4096 / 8), (8192 / 8), (16384 / 8), (32768 / 8),
  (12288 / 8), (24576 / 8), (3072 / 8), (6144 / 8),
  (18432 / 8)
};
                                                                   // Ratio | Ratio
                                                                   // 133   | 100
GLOBAL_REMOVE_IF_UNREFERENCED const TRangeTable FreqTable[] = {
  { 0xFFFFFFFF,            fInvalid, MRC_FREQ_INVALID           }, //----------------
  { MRC_DDR_800_TCK_MIN,  f800,     MRC_FREQ_133 | MRC_FREQ_100 }, //   6   |   8
  { MRC_DDR_1000_TCK_MIN, f1000,                   MRC_FREQ_100 }, //       |  10
  { MRC_DDR_1067_TCK_MIN, f1067,    MRC_FREQ_133                }, //   8   |
  { MRC_DDR_1100_TCK_MIN, f1100,                   MRC_FREQ_100 }, //       |  11
  { MRC_DDR_1200_TCK_MIN, f1200,    MRC_FREQ_133 | MRC_FREQ_100 }, //   9   |  12
  { MRC_DDR_1300_TCK_MIN, f1300,                   MRC_FREQ_100 }, //       |  13
  { MRC_DDR_1333_TCK_MIN, f1333,    MRC_FREQ_133                }, //  10   |
  { MRC_DDR_1400_TCK_MIN, f1400,                   MRC_FREQ_100 }, //       |  14
  { MRC_DDR_1467_TCK_MIN, f1467,    MRC_FREQ_133                }, //  11   |
  { MRC_DDR_1500_TCK_MIN, f1500,                   MRC_FREQ_100 }, //       |  15
  { MRC_DDR_1600_TCK_MIN, f1600,    MRC_FREQ_133 | MRC_FREQ_100 }, //  12   |  16
  { MRC_DDR_1700_TCK_MIN, f1700,                   MRC_FREQ_100 }, //       |  17
  { MRC_DDR_1733_TCK_MIN, f1733,    MRC_FREQ_133                }, //  13   |
  { MRC_DDR_1800_TCK_MIN, f1800,                   MRC_FREQ_100 }, //       |  18
  { MRC_DDR_1867_TCK_MIN, f1867,    MRC_FREQ_133                }, //  14   |
  { MRC_DDR_1900_TCK_MIN, f1900,                   MRC_FREQ_100 }, //       |  19
  { MRC_DDR_2000_TCK_MIN, f2000,    MRC_FREQ_133 | MRC_FREQ_100 }, //  15   |  20
  { MRC_DDR_2100_TCK_MIN, f2100,                   MRC_FREQ_100 }, //       |  21
  { MRC_DDR_2133_TCK_MIN, f2133,    MRC_FREQ_133                }, //  16   |
  { MRC_DDR_2200_TCK_MIN, f2200,                   MRC_FREQ_100 }, //       |  22
  { MRC_DDR_2267_TCK_MIN, f2267,    MRC_FREQ_133                }, //  17   |
  { MRC_DDR_2300_TCK_MIN, f2300,                   MRC_FREQ_100 }, //       |  23
  { MRC_DDR_2400_TCK_MIN, f2400,    MRC_FREQ_133 | MRC_FREQ_100 }, //  18   |  24
  { MRC_DDR_2500_TCK_MIN, f2500,                   MRC_FREQ_100 }, //       |  25
  { MRC_DDR_2533_TCK_MIN, f2533,    MRC_FREQ_133                }, //  19   |
  { MRC_DDR_2600_TCK_MIN, f2600,                   MRC_FREQ_100 }, //       |  26
  { MRC_DDR_2667_TCK_MIN, f2667,    MRC_FREQ_133                }, //  20   |
  { MRC_DDR_2700_TCK_MIN, f2700,                   MRC_FREQ_100 }, //       |  27
  { MRC_DDR_2800_TCK_MIN, f2800,    MRC_FREQ_133 | MRC_FREQ_100 }, //  21   |  28
  { MRC_DDR_2900_TCK_MIN, f2900,                   MRC_FREQ_100 }, //       |  29
  { MRC_DDR_2933_TCK_MIN, f2933,    MRC_FREQ_133                }, //  22   |
  { MRC_DDR_3000_TCK_MIN, f3000,                   MRC_FREQ_100 }, //       |  30
  { MRC_DDR_3067_TCK_MIN, f3067,    MRC_FREQ_133                }, //  23   |
  { MRC_DDR_3100_TCK_MIN, f3100,                   MRC_FREQ_100 }, //       |  31
  { MRC_DDR_3200_TCK_MIN, f3200,    MRC_FREQ_133 | MRC_FREQ_100 }, //  24   |  32
  { MRC_DDR_3300_TCK_MIN, f3300,                   MRC_FREQ_100 }, //       |  33
  { MRC_DDR_3333_TCK_MIN, f3333,    MRC_FREQ_133                }, //  25   |
  { MRC_DDR_3400_TCK_MIN, f3400,                   MRC_FREQ_100 }, //       |  34
  { MRC_DDR_3467_TCK_MIN, f3467,    MRC_FREQ_133                }, //  26   |
  { MRC_DDR_3500_TCK_MIN, f3500,                   MRC_FREQ_100 }, //       |  35
  { MRC_DDR_3600_TCK_MIN, f3600,    MRC_FREQ_133 | MRC_FREQ_100 }, //  27   |  36
  { MRC_DDR_3700_TCK_MIN, f3700,                   MRC_FREQ_100 }, //       |  37
  { MRC_DDR_3733_TCK_MIN, f3733,    MRC_FREQ_133                }, //  28   |
  { MRC_DDR_3800_TCK_MIN, f3800,                   MRC_FREQ_100 }, //       |  38
  { MRC_DDR_3867_TCK_MIN, f3867,    MRC_FREQ_133                }, //  29   |
  { MRC_DDR_3900_TCK_MIN, f3900,                   MRC_FREQ_100 }, //       |  39
  { MRC_DDR_4000_TCK_MIN, f4000,    MRC_FREQ_133 | MRC_FREQ_100 }, //  30   |  40
  { MRC_DDR_4100_TCK_MIN, f4100,                   MRC_FREQ_100 }, //       |  41
  { MRC_DDR_4133_TCK_MIN, f4133,    MRC_FREQ_133                }, //  31   |
  { MRC_DDR_4200_TCK_MIN, f4200,                   MRC_FREQ_100 }, //       |  42
  { MRC_DDR_4267_TCK_MIN, f4267,    MRC_FREQ_133                }, //  32   |
  { MRC_DDR_4300_TCK_MIN, f4300,                   MRC_FREQ_100 }, //       |  43
  { MRC_DDR_4400_TCK_MIN, f4400,    MRC_FREQ_133 | MRC_FREQ_100 }, //  33   |  44
  { MRC_DDR_4500_TCK_MIN, f4500,                   MRC_FREQ_100 }, //       |  45
  { MRC_DDR_4533_TCK_MIN, f4533,    MRC_FREQ_133                }, //  34   |
  { MRC_DDR_4600_TCK_MIN, f4600,                   MRC_FREQ_100 }, //       |  46
  { MRC_DDR_4667_TCK_MIN, f4667,    MRC_FREQ_133                }, //  35   |
  { MRC_DDR_4700_TCK_MIN, f4700,                   MRC_FREQ_100 }, //       |  47
  { MRC_DDR_4800_TCK_MIN, f4800,    MRC_FREQ_133 | MRC_FREQ_100 }, //  36   |  48
  { MRC_DDR_4900_TCK_MIN, f4900,                   MRC_FREQ_100 }, //       |  49
  { MRC_DDR_4933_TCK_MIN, f4933,    MRC_FREQ_133                }, //  37   |
  { MRC_DDR_5000_TCK_MIN, f5000,                   MRC_FREQ_100 }, //       |  50
  { MRC_DDR_5067_TCK_MIN, f5067,    MRC_FREQ_133                }, //  38   |
  { MRC_DDR_5100_TCK_MIN, f5100,                   MRC_FREQ_100 }, //       |  51
  { MRC_DDR_5200_TCK_MIN, f5200,    MRC_FREQ_133 | MRC_FREQ_100 }, //  39   |  52
  { MRC_DDR_5300_TCK_MIN, f5300,                   MRC_FREQ_100 }, //       |  53
  { MRC_DDR_5333_TCK_MIN, f5333,    MRC_FREQ_133                }, //  40   |
  { MRC_DDR_5400_TCK_MIN, f5400,                   MRC_FREQ_100 }, //       |  54
  { MRC_DDR_5467_TCK_MIN, f5467,    MRC_FREQ_133                }, //  41   |
  { MRC_DDR_5500_TCK_MIN, f5500,                   MRC_FREQ_100 }, //       |  55
  { MRC_DDR_5600_TCK_MIN, f5600,    MRC_FREQ_133 | MRC_FREQ_100 }, //  42   |  56
  { MRC_DDR_5700_TCK_MIN, f5700,                   MRC_FREQ_100 }, //       |  57
  { MRC_DDR_5733_TCK_MIN, f5733,    MRC_FREQ_133                }, //  43   |
  { MRC_DDR_5800_TCK_MIN, f5800,                   MRC_FREQ_100 }, //       |  58
  { MRC_DDR_5867_TCK_MIN, f5867,    MRC_FREQ_133                }, //  44   |
  { MRC_DDR_5900_TCK_MIN, f5900,                   MRC_FREQ_100 }, //       |  59
  { MRC_DDR_6000_TCK_MIN, f6000,    MRC_FREQ_133 | MRC_FREQ_100 }, //  45   |  60
  { MRC_DDR_6100_TCK_MIN, f6100,                   MRC_FREQ_100 }, //       |  61
  { MRC_DDR_6133_TCK_MIN, f6133,    MRC_FREQ_133                }, //  46   |
  { MRC_DDR_6200_TCK_MIN, f6200,                   MRC_FREQ_100 }, //       |  62
  { MRC_DDR_6267_TCK_MIN, f6267,    MRC_FREQ_133                }, //  47   |
  { MRC_DDR_6300_TCK_MIN, f6300,                   MRC_FREQ_100 }, //       |  63
  { MRC_DDR_6400_TCK_MIN, f6400,    MRC_FREQ_133 | MRC_FREQ_100 }, //  48   |  64
  { MRC_DDR_6500_TCK_MIN, f6500,                   MRC_FREQ_100 }, //       |  65
  { MRC_DDR_6533_TCK_MIN, f6533,    MRC_FREQ_133                }, //  49   |
  { MRC_DDR_6600_TCK_MIN, f6600,                   MRC_FREQ_100 }, //       |  66
  { MRC_DDR_6667_TCK_MIN, f6667,    MRC_FREQ_133                }, //  50   |
  { MRC_DDR_6700_TCK_MIN, f6700,                   MRC_FREQ_100 }, //       |  67
  { MRC_DDR_6800_TCK_MIN, f6800,    MRC_FREQ_133 | MRC_FREQ_100 }, //  51   |  68
  { MRC_DDR_6900_TCK_MIN, f6900,                   MRC_FREQ_100 }, //       |  69
  { MRC_DDR_6933_TCK_MIN, f6933,    MRC_FREQ_133                }, //  52   |
  { MRC_DDR_7000_TCK_MIN, f7000,                   MRC_FREQ_100 }, //       |  70
  { MRC_DDR_7067_TCK_MIN, f7067,    MRC_FREQ_133                }, //  53   |
  { MRC_DDR_7100_TCK_MIN, f7100,                   MRC_FREQ_100 }, //       |  71
  { MRC_DDR_7200_TCK_MIN, f7200,    MRC_FREQ_133 | MRC_FREQ_100 }, //  54   |  72
  { MRC_DDR_7300_TCK_MIN, f7300,                   MRC_FREQ_100 }, //       |  73
  { MRC_DDR_7333_TCK_MIN, f7333,    MRC_FREQ_133                }, //  55   |
  { MRC_DDR_7400_TCK_MIN, f7400,                   MRC_FREQ_100 }, //       |  74
  { MRC_DDR_7467_TCK_MIN, f7467,    MRC_FREQ_133                }, //  56   |
  { MRC_DDR_7500_TCK_MIN, f7500,                   MRC_FREQ_100 }, //       |  75
  { MRC_DDR_7600_TCK_MIN, f7600,    MRC_FREQ_133 | MRC_FREQ_100 }, //  57   |  76
  { MRC_DDR_7700_TCK_MIN, f7700,                   MRC_FREQ_100 }, //       |  77
  { MRC_DDR_7733_TCK_MIN, f7733,    MRC_FREQ_133                }, //  58   |
  { MRC_DDR_7800_TCK_MIN, f7800,                   MRC_FREQ_100 }, //       |  78
  { MRC_DDR_7867_TCK_MIN, f7867,    MRC_FREQ_133                }, //  59   |
  { MRC_DDR_7900_TCK_MIN, f7900,                   MRC_FREQ_100 }, //       |  79
  { MRC_DDR_8000_TCK_MIN, f8000,    MRC_FREQ_133 | MRC_FREQ_100 }, //  60   |  80
  { MRC_DDR_8100_TCK_MIN, f8100,                   MRC_FREQ_100 }, //       |  81
  { MRC_DDR_8133_TCK_MIN, f8133,    MRC_FREQ_133                }, //  61   |
  { MRC_DDR_8200_TCK_MIN, f8200,                   MRC_FREQ_100 }, //       |  82
  { MRC_DDR_8267_TCK_MIN, f8267,    MRC_FREQ_133                }, //  62   |
  { MRC_DDR_8400_TCK_MIN, f8400,    MRC_FREQ_133 | MRC_FREQ_100 }, //  63   |  84
  { 0,                    fNoInit,  MRC_FREQ_INVALID           }
};

// This table defines the subset of SPD bytes that MRC will read from the DIMM.
// We only read the required SPD bytes, per boot mode, to save time (SMBus reads are slow)
// In Warm flow we don't read anything as DIMM should not be changed.
// In Fast flow we only read Module Manufacturing ID and Serial Number, to detect a DIMM change.
// DDR4 XMP section is only read on XMP DIMMs.
// NOTE: If you change number of rows here, need to update array size in MrcSpdProcessing.h as well.
const MrcSpdOffsetTable MrcSpdDdr4Table[] = {
  {   0,               1,               (1 << bmCold)                  },
  {   2,               2,               (1 << bmCold) | (1 << bmFast)  }, // DRAM Type
  {   3,              45,               (1 << bmCold)                  },
  { 117,             131,               (1 << bmCold)                  },
  { SPD4_MANUF_START, SPD4_MANUF_END,   (1 << bmCold) | (1 << bmFast)  }, // Module manuf. details and serial number
  { 329,             348,               (1 << bmCold)                  }, // Module Part Number
  { 384,             389,               (1 << bmCold)                  }, // XMP
  { 393,             431,               (1 << bmCold)                  }, // XMP
  { 440,             478,               (1 << bmCold)                  }, // XMP
};
const MrcSpdOffsetTable MrcSpdLpddrTable[] = {
  {   0,               1,               (1 << bmCold)                  },
  {   2,               2,               (1 << bmCold) | (1 << bmFast)  },
  {   3,              32,               (1 << bmCold)                  },
  { 120,             130,               (1 << bmCold)                  },
  { SPDLP_MANUF_START, SPDLP_MANUF_END, (1 << bmCold) | (1 << bmFast)  },
  { 329,             383,               (1 << bmCold)                  }
};
/**
    Calculate the memory clock value from the current memory frequency.

    @param[in, out] MrcData     - Pointer to MrcData data structure.
    @param[in]      Frequency   - Memory frequency to convert.

    @retval Returns the tCK value in [fs] for the given frequency.
**/
UINT32
ConvertFreq2Clock (
  IN OUT MrcParameters *const MrcData,
  IN     const MrcFrequency   Frequency
  )
{
  UINT32 tCKminActual;
  UINT32 Index;

  tCKminActual = MRC_DDR_800_TCK_MIN;
  for (Index = 0; Index < ARRAY_COUNT (FreqTable); Index++) {
    if (Frequency == FreqTable[Index].Frequency) {
      tCKminActual = FreqTable[Index].tCK;
      break;
    }
  }
  return tCKminActual;
}

/**
  Calculate the memory frequency from the memory clock value.

    @param[in, out] MrcData     - Pointer to MrcData data structure.
    @param[in]      RefClk      - The memory reference clock.
    @param[in]      tCKmin      - The tCKmin value in [fs] to convert.
    @param[out]     tCKminIndex - Pointer to the chosen table index.

    @retval Returns the frequency that matches the given tCK.
**/
static
UINT32
ConvertClock2Freq (
  IN OUT MrcParameters *const  MrcData,
  IN     const MrcRefClkSelect RefClk,
  IN     const UINT32          tCKmin,
  OUT    INT32         *const  tCKminIndex
  )
{
  MrcFrequency  Frequency;
  UINT32        Index;
  UINT32        tCKminPs;
  UINT32        FreqPs;
  UINT32        NextFreqPs;
  UINT8         FreqFlag;
  MrcOutput     *Outputs;
  Outputs = &MrcData->Outputs;

  //
  // Convert tCK value to the nearest frequency value.
  // Then find slowest valid frequency for the given reference clock.
  // Round to the [ps] resolution, because SPD FineTimeBase is 1ps.
  //
  Frequency = fNoInit;
  for (Index = 0; Index < ARRAY_COUNT (FreqTable) - 1; Index++) {
    tCKminPs    = UDIVIDEROUND (tCKmin, 1000);
    FreqPs      = UDIVIDEROUND (FreqTable[Index].tCK, 1000);
    NextFreqPs  = UDIVIDEROUND (FreqTable[Index + 1].tCK, 1000);
    if ((tCKminPs <= FreqPs) && (tCKminPs > NextFreqPs)) {
      Frequency = FreqTable[Index].Frequency;
      break;
    }
  }

  while (Index) {
    FreqFlag = FreqTable[Index].FreqFlag;
    if ((FreqFlag & (1 << RefClk)) != 0) {
      if (!Outputs->Gear2) {
        break; // We can have this frequency at the given refclk
      } else {
        // In Gear2 make sure the frequency is a multiple of (2 * RefClk):
        //  133: multiples of 266, which has FreqTable index = 3, 7, 11, 15, 19 etc.
        //  100: multiples of 200, which has FreqTable index = 2, 5, 8, 11, 14, 17 etc.
        if ((RefClk == MRC_REF_CLOCK_133) && ((Index % 4) == 3)) {
          break;
        }
        if ((RefClk == MRC_REF_CLOCK_100) && ((Index % 3) == 2)) {
          break;
        }
      }
    }
    Frequency = FreqTable[--Index].Frequency;
  }

  if (tCKminIndex != NULL) {
    *tCKminIndex = Index;
  }
  return Frequency;
}

/**
  Determine if the DIMM slot is filled.
  If a valid DRAM device type and valid module package are found then a DIMM is present.

    @param[in] MrcData - Pointer to MrcData data structure.
    @param[in] Spd     - Pointer to Spd data structure.

    @retval TRUE on valid value, otherwise FALSE and the value is set to zero.
**/
MrcDimmSts
DimmPresence (
  IN MrcDebug      *const Debug,
  IN const MrcSpd  *const Spd
  )
{
  UINT8         DramType;
  UINT8         ModuleType;

  //
  // The following code will more closely identify memory instead of just searching for non-zero data.
  //

  //
  // Check for valid DRAM device type and valid module package
  //
  DramType = Spd->Ddr3.General.DramDeviceType.Bits.Type;
  ModuleType = Spd->Ddr3.General.ModuleType.Bits.ModuleType;
  switch (DramType) {
    case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
      switch (ModuleType) {
        case UDimmMemoryPackage:
        case SoDimmMemoryPackage:
        case SoUDimmEccMemoryPackageDdr4:
          return DIMM_PRESENT;

        case RDimmMemoryPackage:
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "  ERROR: RDIMM is not supported !\n");

        default:
          break;
      }
      break;

    case MRC_SPD_LPDDR4_SDRAM_TYPE_NUMBER:
    case MRC_SPD_LPDDR4X_SDRAM_TYPE_NUMBER:
      switch (ModuleType) {
        case LpDimmMemoryPackage:
        case NonDimmMemoryPackage:
          return DIMM_PRESENT;

        default:
          break;
      }
      break;

    default:
      break;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "  No DIMM detected in slot\n");
  return DIMM_NOT_PRESENT;
}

/**
  Determine if the DIMM is valid and supported.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE.
**/
static
BOOLEAN
ValidDimm (
  IN OUT MrcParameters *const MrcData,
  IN     const MrcSpd  *const Spd,
  IN OUT MrcDimmOut    *const DimmOut
  )
{
  MrcOutput                                    *Outputs;
  BOOLEAN                                      Ddr4;
  BOOLEAN                                      Lpddr;
  BOOLEAN                                      DimmValid;
  UINT8                                        DeviceType;
  MrcProfile                                   MemProfile;
  const SPD_EXTREME_MEMORY_PROFILE_HEADER_2_0  *Header4;
#ifdef MRC_DEBUG_PRINT
  static const UINT16                          BytesUsedConst[] = {0, 128, 176, 256};
  MrcDebug                                     *Debug;
  const char                                   *DramTypeString;
  const char                                   *ModuleTypeString;
  const char                                   *ProfileStr;
  SPD_REVISION_STRUCT                          Revision;
  UINT16                                       BytesUsed;
  UINT16                                       BytesTotal;
  UINT16                                       CrcCoverage;

  Debug = &MrcData->Outputs.Debug;
  ModuleTypeString = UnknownString;
#endif // MRC_DEBUG_PRINT

  Outputs    = &MrcData->Outputs;
  DimmValid  = TRUE;
  Ddr4       = FALSE;
  Lpddr      = FALSE;
  MemProfile = MrcData->Inputs.MemoryProfile;
  Header4    = &Spd->Ddr4.EndUser.Xmp.Header;

  //
  // The dram device type is at the same SPD offset for all types.
  //
  DeviceType = Spd->Ddr3.General.DramDeviceType.Bits.Type;
  switch (DeviceType) {
    case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
      DimmOut->DdrType    = MRC_DDR_TYPE_DDR4;
      DimmOut->ModuleType = Spd->Ddr4.Base.ModuleType.Bits.ModuleType;
      Ddr4                = TRUE;
      break;

    case MRC_SPD_LPDDR4_SDRAM_TYPE_NUMBER:
    case MRC_SPD_LPDDR4X_SDRAM_TYPE_NUMBER:
      DimmOut->DdrType    = MRC_DDR_TYPE_LPDDR4;
      DimmOut->ModuleType = Spd->Lpddr.Base.ModuleType.Bits.ModuleType;
      Lpddr               = TRUE;
      if (DeviceType == MRC_SPD_LPDDR4X_SDRAM_TYPE_NUMBER) {
        // Set Lp4x flag to handle small differences between LPDDR4 and LPDDR4X
        Outputs->Lp4x = TRUE;
      }

      break;

    default:
      DimmOut->DdrType    = MRC_DDR_TYPE_UNKNOWN;
      DimmOut->ModuleType = 0;
      DimmValid           = FALSE;
      break;
  }

  if (DimmValid) {
    switch (DimmOut->ModuleType) {
#if (SUPPORT_RDIMM == SUPPORT)
      case RDimmMemoryPackage:
#ifdef MRC_DEBUG_PRINT
        ModuleTypeString = RdimmString;
#endif // MRC_DEBUG_PRINT
        break;
#endif

#if (SUPPORT_UDIMM == SUPPORT)
      case UDimmMemoryPackage:
#ifdef MRC_DEBUG_PRINT
        ModuleTypeString = UdimmString;
#endif // MRC_DEBUG_PRINT
        break;
#endif

#if (SUPPORT_SODIMM == SUPPORT)
      case SoDimmMemoryPackage:
#ifdef MRC_DEBUG_PRINT
        ModuleTypeString = SodimmString;
#endif // MRC_DEBUG_PRINT
        break;

      case SoUDimmEccMemoryPackageDdr4:
        if (Ddr4) {
#ifdef MRC_DEBUG_PRINT
          ModuleTypeString = SodimmString;
#endif // MRC_DEBUG_PRINT
        } else {
          DimmValid = FALSE;
        }
        break;
#endif // SUPPORT_SODIMM

      case LpDimmMemoryPackage:
        if (Lpddr) {
#ifdef MRC_DEBUG_PRINT
          ModuleTypeString = LpDimmString;
#endif // MRC_DEBUG_PRINT
        } else {
          DimmValid = FALSE;
        }
        break;

      case NonDimmMemoryPackage:
        if (Lpddr) {
#ifdef MRC_DEBUG_PRINT
          ModuleTypeString = MemoryDownString;
#endif // MRC_DEBUG_PRINT
        } else {
          DimmValid = FALSE;
        }
        break;

      default:
        DimmValid = FALSE;
        break;
    }
  }

  DimmOut->XmpSupport = 0;
  if (DimmValid) {
    if (Ddr4) {
      if ((XMP_ID_STRING != Header4->XmpId) ||
        ((MemProfile == XMP_PROFILE1) && (Header4->XmpOrgConf.Bits.ProfileEnable1 == 0)) ||
        ((MemProfile == XMP_PROFILE2) && (Header4->XmpOrgConf.Bits.ProfileEnable2 == 0))) {
          if ((MemProfile == XMP_PROFILE1) || (MemProfile == XMP_PROFILE2)) {
            DimmValid = FALSE;
          }
      } else {
        Outputs->XmpProfileEnable |= 1;
      }
      if (XMP_ID_STRING == Header4->XmpId) {
        if (0x20 == (Header4->XmpRevision.Data)) {
          DimmOut->XmpRevision = Header4->XmpRevision.Data;
        }
        if (Header4->XmpOrgConf.Bits.ProfileEnable1 != 0) {
          DimmOut->XmpSupport |= 1;
        }
        if (Header4->XmpOrgConf.Bits.ProfileEnable2 != 0) {
          DimmOut->XmpSupport |= 2;
        }
      }
    }
  }

#ifdef MRC_DEBUG_PRINT
  switch (MemProfile) {
      case STD_PROFILE:
      case USER_PROFILE:
      default:
        ProfileStr = StdString;
        break;
      case XMP_PROFILE1:
        ProfileStr = Xmp1String;
        break;
      case XMP_PROFILE2:
        ProfileStr = Xmp2String;
        break;
  }

  switch (DeviceType) {
    case MRC_SPD_DDR4_SDRAM_TYPE_NUMBER:
      DramTypeString = Ddr4String;
      BytesTotal     = 256 * Spd->Ddr4.Base.Description.Bits.BytesTotal;
      BytesUsed      = BytesUsedConst[1] * Spd->Ddr4.Base.Description.Bits.BytesUsed;
      CrcCoverage    = 125;
      Revision.Data  = Spd->Ddr4.Base.Revision.Data;
      break;

    case MRC_SPD_LPDDR4_SDRAM_TYPE_NUMBER:
    case MRC_SPD_LPDDR4X_SDRAM_TYPE_NUMBER:
      if (DeviceType == MRC_SPD_LPDDR4_SDRAM_TYPE_NUMBER) {
        DramTypeString = Lpddr4String;
      } else {
        DramTypeString = Lpddr4xString;
      }
      BytesTotal     = 256 * Spd->Lpddr.Base.Description.Bits.BytesTotal;
      BytesUsed      = BytesUsedConst[1] * Spd->Lpddr.Base.Description.Bits.BytesUsed;
      CrcCoverage    = 125;
      Revision.Data  = Spd->Lpddr.Base.Revision.Data;
      break;

    default:
      DramTypeString = UnknownString;
      BytesTotal     = 0;
      BytesUsed      = 0;
      CrcCoverage    = 0;
      Revision.Data  = 0;
      break;
  }

  if (DimmValid) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "  %s %s detected, Rev: %u.%u, Size: %u used/%u total, CRC coverage: 0 - %u\n",
      DramTypeString,
      ModuleTypeString,
      Revision.Bits.Major,
      Revision.Bits.Minor,
      BytesUsed,
      BytesTotal,
      CrcCoverage
      );
  } else {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "  %s %s detected, SPD Dram type %Xh, module type %Xh\n",
      DramTypeString,
      ModuleTypeString,
      DeviceType,
      DimmOut->ModuleType
      );
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  DIMM profile %s selected\n", ProfileStr);
  if (Ddr4) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "  XMP String: %Xh\n",
      Header4->XmpId
    );
    if (XMP_ID_STRING == Header4->XmpId) {
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "  XMP Revision: %u.%u\n",
        Header4->XmpRevision.Bits.Major,
        Header4->XmpRevision.Bits.Minor
      );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        XpString,
        1,
        Header4->XmpOrgConf.Bits.ProfileEnable1 ? "en" : "dis",
        Header4->XmpOrgConf.Bits.ProfileConfig1 + 1
      );
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        XpString,
        2,
        Header4->XmpOrgConf.Bits.ProfileEnable2 ? "en" : "dis",
        Header4->XmpOrgConf.Bits.ProfileConfig2 + 1
      );
    }
  }

#endif // MRC_DEBUG_PRINT

  return DimmValid;
}

/**
  Determine if the DIMM SDRAM device width is valid and return the value.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
ValidSdramDeviceWidth (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug    *Debug;
  MrcOutput   *Outputs;
  MrcDdrType  DdrType;
  BOOLEAN     Lpddr;
  UINT8       ChannelsPerDie;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  DdrType = DimmOut->DdrType;
  Lpddr   = (DdrType == MRC_DDR_TYPE_LPDDR4);
  ChannelsPerDie = MRC_SPD_CH_PER_SDRAM_PKG_RSVD;

  if (MRC_DDR_TYPE_DDR4 == DdrType) {
    DimmOut->SdramWidthIndex = Spd->Ddr4.Base.ModuleOrganization.Bits.SdramDeviceWidth;
  } else {
    DimmOut->SdramWidthIndex = Spd->Lpddr.Base.ModuleOrganization.Bits.SdramDeviceWidth;
    DimmOut->DiePerSdramPackage = Spd->Lpddr.Base.SdramPackageType.Bits.DiePerSdramPackage + 1;
    // We use Byte 6 bits [3:2] as "Channels per die"
    ChannelsPerDie = Spd->Lpddr.Base.SdramPackageType.Bits.ChannelsPerPackage;
  }

  switch (DimmOut->SdramWidthIndex) {
    case MRC_SPD_SDRAM_DEVICE_WIDTH_8:
      DimmOut->SdramWidth = 8;
      break;

    case MRC_SPD_SDRAM_DEVICE_WIDTH_16:
      DimmOut->SdramWidth = 16;
      break;

    case MRC_SPD_SDRAM_DEVICE_WIDTH_32:
      DimmOut->SdramWidth = 32;
      break;

    default:
      DimmOut->SdramWidth = 0;
      MRC_DEBUG_MSG (Debug,
        MSG_LEVEL_ERROR,
        "%sSDRAM device width, %s%Xh\n",
        ErrorString,
        SpdValString,
        DimmOut->SdramWidthIndex
        );
      return FALSE;
  }

  if (Lpddr) {
    if ((DimmOut->SdramWidth == 8) || (Spd->Lpddr.Base.ModuleOrganization.Bits.ByteMode == 1)) {
      Outputs->Lp4x8 = TRUE;

      if (DimmOut->SdramWidth == 16) {
        // This is a Byte Mode DRAM with SdramWidth = 16.
        // SPD value is "SDRAM width per channel", which combines two x8 devices in Byte Mode.
        // In DIMM size calculations we use SdramWidth as a width of one channel per individual device, hence use 8 here.
        DimmOut->SdramWidth = 8;
      }
    }
    switch (ChannelsPerDie) {
      case MRC_SPD_CH_PER_SDRAM_PKG_1:
        ChannelsPerDie = 1;
        break;

      case MRC_SPD_CH_PER_SDRAM_PKG_2:
        ChannelsPerDie = 2;
        break;

      case MRC_SPD_CH_PER_SDRAM_PKG_4:
        ChannelsPerDie = 4;
        break;

      default:
      case MRC_SPD_CH_PER_SDRAM_PKG_RSVD:
        ChannelsPerDie = 0;
        MRC_DEBUG_MSG (
          Debug,
          MSG_LEVEL_ERROR,
          "%s%s, %s%Xh\n",
          ErrorString,
          ChannelsPerDieStr,
          SpdValString,
          ChannelsPerDie
          );
        return FALSE;
    }
    DimmOut->ChannelsPerDie = ChannelsPerDie;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Die per SDRAM Package: %u\n", DimmOut->DiePerSdramPackage);
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s: %u\n", ChannelsPerDieStr, ChannelsPerDie);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  SDRAM device width: %u%s\n", DimmOut->SdramWidth, (Lpddr && Outputs->Lp4x8) ? " (Byte Mode)" : "");

  return TRUE;
}

/**
  Determine if the DIMM SDRAM row address size is valid and return the value.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE if the row address size is valid, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
ValidRowSize (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  UINT8        RowBits;
  UINT8        RowAddress;
  MrcDebug        *Debug;

  Debug = &MrcData->Outputs.Debug;
  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    RowAddress = Spd->Ddr4.Base.SdramAddressing.Bits.RowAddress;
  } else {
    RowAddress = Spd->Lpddr.Base.SdramAddressing.Bits.RowAddress;
  }

  switch (RowAddress) {
#if (SUPPORT_ROW_12 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_12:
      DimmOut->RowSize = MRC_BIT12;
      RowBits          = 12;
      break;
#endif
#if (SUPPORT_ROW_13 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_13:
      DimmOut->RowSize = MRC_BIT13;
      RowBits          = 13;
      break;
#endif
#if (SUPPORT_ROW_14 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_14:
      DimmOut->RowSize = MRC_BIT14;
      RowBits          = 14;
      break;
#endif
#if (SUPPORT_ROW_15 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_15:
      DimmOut->RowSize = MRC_BIT15;
      RowBits          = 15;
      break;
#endif
#if (SUPPORT_ROW_16 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_16:
      DimmOut->RowSize = MRC_BIT16;
      RowBits          = 16;
      break;
#endif
#if (SUPPORT_ROW_17 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_17:
      DimmOut->RowSize = MRC_BIT17;
      RowBits          = 17;
      break;
#endif
#if (SUPPORT_ROW_18 == SUPPORT)
    case MRC_SPD_SDRAM_ROW_18:
      DimmOut->RowSize = MRC_BIT18;
      RowBits          = 18;
      break;
#endif
    default:
      DimmOut->RowSize = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%sSDRAM row size, %s%Xh\n", ErrorString, SpdValString, RowAddress);
      return FALSE;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Row bits: %u\n", RowBits);
  return TRUE;
}

/**
  Determine if the DIMM SDRAM column address size is valid and return the value.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE if the column address size is valid, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
ValidColumnSize (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug     *Debug;
  UINT8        ColumnBits;
  UINT8        ColumnAddress;

  Debug    = &MrcData->Outputs.Debug;
  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    ColumnAddress = Spd->Ddr4.Base.SdramAddressing.Bits.ColumnAddress;
  } else {
    ColumnAddress = Spd->Lpddr.Base.SdramAddressing.Bits.ColumnAddress;
  }

  switch (ColumnAddress) {
    case MRC_SPD_SDRAM_COLUMN_9:
      ColumnBits = 9;
      break;
    case MRC_SPD_SDRAM_COLUMN_10:
      ColumnBits = 10;
      break;
    case MRC_SPD_SDRAM_COLUMN_11:
      ColumnBits = 11;
      break;
    case MRC_SPD_SDRAM_COLUMN_12:
      ColumnBits = 12;
      break;
    default:
      DimmOut->ColumnSize = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%sSDRAM column size, %s%Xh\n", ErrorString, SpdValString, ColumnAddress);
      return FALSE;
  }
  DimmOut->ColumnSize = 1 << ColumnBits;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Column bits: %u\n", ColumnBits);
  return TRUE;
}

/**
  Determine if the DIMM SDRAM primary bus width is valid and return the value.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
ValidPrimaryWidth (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug  *Debug;
  MrcOutput *Outputs;
  UINT8     Width;
  UINT8     NumberOfChannels;
  BOOLEAN   Lpddr;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Lpddr   = FALSE;
  NumberOfChannels = 0;

  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    Width = Spd->Ddr4.Base.ModuleMemoryBusWidth.Bits.PrimaryBusWidth;
  } else { // LPDDR4
    Lpddr = TRUE;
    NumberOfChannels = Spd->Lpddr.Base.ModuleMemoryBusWidth.Bits.NumberOfChannels + 1;
    Width = Spd->Lpddr.Base.ModuleMemoryBusWidth.Bits.PrimaryBusWidth;
    // We will check for mixed width case later in MrcSpdProcessing()
    if (Width == MRC_SPD_PRIMARY_BUS_WIDTH_32) {
      Outputs->EnhancedChannelMode = TRUE;
    }
  }

  switch (Width) {
#if (SUPPORT_PRIWIDTH_8 == SUPPORT)
    case MRC_SPD_PRIMARY_BUS_WIDTH_8:
      DimmOut->PrimaryBusWidth = 8;
      break;
#endif
#if (SUPPORT_PRIWIDTH_16 == SUPPORT)
    case MRC_SPD_PRIMARY_BUS_WIDTH_16:
      DimmOut->PrimaryBusWidth = 16;
      break;
#endif
#if (SUPPORT_PRIWIDTH_32 == SUPPORT)
    case MRC_SPD_PRIMARY_BUS_WIDTH_32:
      DimmOut->PrimaryBusWidth = 32;
      break;
#endif
#if (SUPPORT_PRIWIDTH_64 == SUPPORT)
    case MRC_SPD_PRIMARY_BUS_WIDTH_64:
      DimmOut->PrimaryBusWidth = 64;
      break;
#endif
    default:
      DimmOut->PrimaryBusWidth = 0;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%sSDRAM primary bus width, %s%Xh\n", ErrorString, SpdValString, Width);
      return FALSE;
      break;
  }
  if (Lpddr) {
    DimmOut->NumLpSysChannel = NumberOfChannels;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Number of channels: %u\n", NumberOfChannels);
    if (MrcData->Inputs.ForceSingleSubchannel) {
      DimmOut->NumLpSysChannel = 1;
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Forcing to Single Subch because ForceSingleSubchannel is 1\n" );
    }

  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Primary bus width: %u\n", DimmOut->PrimaryBusWidth);
  return TRUE;
}

/**
  Determines if the number of Bank are valid.
  Determines if the number of Bank Groups are valid.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE.
**/
static
BOOLEAN
ValidBank (
  IN OUT MrcParameters  *const MrcData,
  IN const MrcSpd       *const Spd,
  IN OUT MrcDimmOut     *const DimmOut
  )
{
  MrcDebug     *Debug;
  UINT8        BankAddress;
  UINT8        BankGroup;
  UINT8        ValidCheck;

  Debug       = &MrcData->Outputs.Debug;
  ValidCheck  = TRUE;

  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    DimmOut->DensityIndex = Spd->Ddr4.Base.SdramDensityAndBanks.Bits.Density;
    BankAddress           = Spd->Ddr4.Base.SdramDensityAndBanks.Bits.BankAddress;
    BankGroup             = Spd->Ddr4.Base.SdramDensityAndBanks.Bits.BankGroup;
  } else {
    DimmOut->DensityIndex = Spd->Lpddr.Base.SdramDensityAndBanks.Bits.Density;
    BankAddress           = Spd->Lpddr.Base.SdramDensityAndBanks.Bits.BankAddress;
    BankGroup             = Spd->Lpddr.Base.SdramDensityAndBanks.Bits.BankGroup;
  }

  switch (BankAddress) {
#if (SUPPORT_BANK_4 == SUPPORT)
    case MRC_SPD_DDR4_SDRAM_BANK_4:
#endif
#if (SUPPORT_BANK_8 == SUPPORT)
    case MRC_SPD_DDR4_SDRAM_BANK_8:
#endif
#if ((SUPPORT_BANK_4 == SUPPORT) || (SUPPORT_BANK_8 == SUPPORT))
      DimmOut->Banks      = MRC_BIT2 << BankAddress;
      break;
#endif

    default:
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "%sSDRAM number of banks, %s%Xh\n",
        ErrorString,
        SpdValString,
        BankAddress
        );
      ValidCheck = FALSE;
  }

  if ((MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) && (BankGroup == MRC_SPD_DDR4_SDRAM_BANK_GROUPS_0)) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "%sSDRAM number of bank groups, %s%Xh\n",
      ErrorString,
      SpdValString,
      BankGroup
      );
    ValidCheck = FALSE;
  } else {
    DimmOut->BankGroups = MRC_BIT0 << BankGroup;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    (TRUE == ValidCheck) ? "  %u Banks in %u groups\n" : "",
    DimmOut->Banks,
    DimmOut->BankGroups
    );

  if (DimmOut->DensityIndex < ARRAY_COUNT (SdramCapacityTable)) {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "  SDRAM Capacity: %u Mb\n",
      SdramCapacityTable[DimmOut->DensityIndex] * 8
      );
  } else {
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "  ERROR: SDRAM Capacity is reserved value: 0x%02X\n",
      DimmOut->DensityIndex
      );
  }

  return ValidCheck;
}

/**
  Determine if the number of ranks in the DIMM is valid and return the value.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
GetRankCount (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug     *Debug;
  UINT8        RankCount;

  Debug = &MrcData->Outputs.Debug;
  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    RankCount = Spd->Ddr4.Base.ModuleOrganization.Bits.RankCount;
  } else {
    RankCount = Spd->Lpddr.Base.ModuleOrganization.Bits.RankCount;
  }

  DimmOut->RankInDimm = RankCount + 1;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Ranks: %u\n", DimmOut->RankInDimm);

  if (MrcData->Inputs.ForceSingleRank) {
    DimmOut->RankInDimm = 1;
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Forcing to Single Rank because ForceSingleRank is 1\n" );
  }

  if (DimmOut->RankInDimm > MAX_RANK_IN_DIMM) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%snumber of ranks, %s%Xh\n", ErrorString, SpdValString, RankCount);
    DimmOut->RankInDimm = 0;
    return FALSE;
  }

  return TRUE;
}

/**
  Calculate the size of the DIMM, in MBytes.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval TRUE on valid value, otherwise FALSE and the value is set to zero.
**/
static
BOOLEAN
GetDimmSize (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug       *Debug;
  UINT32         DimmSize;
  UINT8          DensityIndex;
  BOOLEAN   Lpddr4;

  Debug = &MrcData->Outputs.Debug;
  DensityIndex = DimmOut->DensityIndex;
  Lpddr4 = (DimmOut->DdrType == MRC_DDR_TYPE_LPDDR4);

  if ((DimmOut->SdramWidth > 0) && (DensityIndex < ARRAY_COUNT (SdramCapacityTable))) {
    if (Lpddr4) {
      DimmSize = (((SdramCapacityTable[DensityIndex] * DimmOut->PrimaryBusWidth) / DimmOut->SdramWidth) * DimmOut->NumLpSysChannel * DimmOut->RankInDimm / DimmOut->ChannelsPerDie);
    } else {
      DimmSize = (((SdramCapacityTable[DensityIndex] * DimmOut->PrimaryBusWidth) / DimmOut->SdramWidth) * DimmOut->RankInDimm);
    }
    if ((DimmSize >= DIMMSIZEMIN) && (DimmSize <= DIMMSIZEMAX)) {
      if (DimmSize != 0) {
        DimmOut->DimmCapacity = DimmSize;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  DIMM size: %u MByte\n", DimmSize);
        return TRUE;
      }
    }
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_ERROR,
      "%sDIMM size: %u MB, valid range %u - %u MB ",
      ErrorString,
      DimmSize,
      DIMMSIZEMIN,
      DIMMSIZEMAX
      );
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_ERROR,
    "SDRAM capacity %s%Xh\n",
    SpdValString,
    DensityIndex
    );
  DimmOut->DimmCapacity = 0;
  return FALSE;
}

/**
  Obtain ECC support Status for this DIMM.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval Returns TRUE.
**/
static
BOOLEAN
ValidEccSupport (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
#if (SUPPORT_ECC == SUPPORT)
  UINT8        BusWidthExtension;
#endif // SUPPORT_ECC
  MrcDebug        *Debug;

  Debug = &MrcData->Outputs.Debug;

#if (SUPPORT_ECC == SUPPORT)
  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    BusWidthExtension = Spd->Ddr4.Base.ModuleMemoryBusWidth.Bits.BusWidthExtension;
  } else {
    BusWidthExtension = Spd->Lpddr.Base.ModuleMemoryBusWidth.Bits.BusWidthExtension;
  }
  if (MRC_SPD_BUS_WIDTH_EXTENSION_8 == BusWidthExtension) {
    DimmOut->EccSupport = TRUE;
  } else
#endif // SUPPORT_ECC
  {
    DimmOut->EccSupport = FALSE;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  ECC is %ssupported\n", (DimmOut->EccSupport == FALSE) ? "not " : "");
  return TRUE;
}

/**
  Obtain address mirroring Status for this DIMM.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval Returns TRUE.
**/
static
BOOLEAN
GetAddressMirror (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug  *Debug;
  UINT8  MappingRank1;

  Debug = &MrcData->Outputs.Debug;
  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    MappingRank1 = Spd->Ddr4.Module.Unbuffered.AddressMappingEdgeConn.Bits.MappingRank1;
  } else {
    MappingRank1 = 0;
  }

  DimmOut->AddressMirrored = (MappingRank1 != 0) ? TRUE : FALSE;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  DIMM has %saddress mirroring\n", (DimmOut->AddressMirrored == FALSE) ? "no " : "");
  return TRUE;
}

/**
  Obtain thermal and refresh support for this DIMM.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval Returns TRUE.
**/
static
BOOLEAN
GetThermalRefreshSupport (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug        *Debug;
  const MrcInput  *Inputs;

  Inputs = &MrcData->Inputs;
  Debug  = &MrcData->Outputs.Debug;

  DimmOut->PartialSelfRefresh    = 0;
  DimmOut->OnDieThermalSensor    = (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) ? 0 : Spd->Lpddr.Base.ModuleThermalSensor.Bits.ThermalSensorPresence;
  DimmOut->AutoSelfRefresh       = 0;
  DimmOut->ExtendedTemperRefresh = 0;
  DimmOut->ExtendedTemperRange   = 0;

  DimmOut->SelfRefreshTemp = ((!DimmOut->AutoSelfRefresh) && (DimmOut->ExtendedTemperRange) && (Inputs->ExtTemperatureSupport)) ? TRUE : FALSE;

  MRC_DEBUG_MSG (Debug,
    MSG_LEVEL_NOTE,
    "  Partial Array Self Refresh%s\n",
    DimmOut->PartialSelfRefresh ? IsSupString : NotSupString);
  MRC_DEBUG_MSG (Debug,
    MSG_LEVEL_NOTE,
    "  On-Die Thermal Sensor Readout%s\n",
    DimmOut->OnDieThermalSensor ? IsSupString : NotSupString);
  MRC_DEBUG_MSG (Debug,
    MSG_LEVEL_NOTE,
    "  Auto Self Refresh%s\n",
    DimmOut->AutoSelfRefresh ? IsSupString : NotSupString);
  MRC_DEBUG_MSG (Debug,
    MSG_LEVEL_NOTE,
    "  Extended Temperature Refresh Rate%s\n",
    DimmOut->ExtendedTemperRefresh ? IsSupString : NotSupString);
  MRC_DEBUG_MSG (Debug,
    MSG_LEVEL_NOTE,
    "  Extended Temperature Range%s\n",
    DimmOut->ExtendedTemperRange ? IsSupString : NotSupString);
  return TRUE;
}

/**
  Obtain Pseudo TRR support for this DIMM.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval Returns TRUE.
**/
static
BOOLEAN
GetpTRRsupport (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug        *Debug;
  MrcOutput       *Outputs;
  UINT32          tMAC;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    tMAC = Spd->Ddr4.Base.pTRRsupport.Bits.tMACencoding;
  } else {
    tMAC = Spd->Lpddr.Base.pTRRsupport.Bits.tMACencoding;
  }

  switch (tMAC) {
    case MRC_TMAC_UNTESTED:
      DimmOut->tMAC = MRC_TMAC_UNTESTED;
      break;
    case MRC_TMAC_200K:
      DimmOut->tMAC = 2;
      break;
    case MRC_TMAC_300K:
      DimmOut->tMAC = 3;
      break;
    case MRC_TMAC_400K:
      DimmOut->tMAC = 4;
      break;
    case MRC_TMAC_500K:
      DimmOut->tMAC = 5;
      break;
    case MRC_TMAC_600K:
      DimmOut->tMAC = 6;
      break;
    case MRC_TMAC_700K:
      DimmOut->tMAC = 7;
      break;
    case MRC_TMAC_UNLIMITED:
      DimmOut->tMAC = MRC_TMAC_UNLIMITED;
      break;
    default:
      DimmOut->tMAC = 0;
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_ERROR,
        "%stMAC value, %s%Xh\n",
        ErrorString,
        SpdValString,
        tMAC
        );
      return FALSE;
  }

  if (DimmOut->tMAC == MRC_TMAC_UNTESTED) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  tMAC is untested\n");
  } else if (DimmOut->tMAC == MRC_TMAC_UNLIMITED) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  tMAC is unlimited\n");
  } else {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  tMAC: %d00K\n", DimmOut->tMAC);
  }

  return TRUE;
}

/**
  Obtain which JEDEC reference design raw card was used as the basis for the DIMM assembly.

    @param[in, out] MrcData - Pointer to MrcData data structure.
    @param[in]      Spd     - Pointer to Spd data structure.
    @param[in, out] DimmOut - Pointer to structure containing DIMM information.

    @retval Returns TRUE.
**/
static
BOOLEAN
GetReferenceRawCardSupport (
  IN OUT MrcParameters   *const MrcData,
  IN const MrcSpd        *const Spd,
  IN OUT MrcDimmOut      *const DimmOut
  )
{
  MrcDebug  *Debug;

  Debug = &MrcData->Outputs.Debug;
  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
    DimmOut->ReferenceRawCard = (Spd->Ddr4.Module.Unbuffered.ReferenceRawCardUsed.Bits.Extension << MRC_SPD_REF_RAW_CARD_SIZE) |
    Spd->Ddr4.Module.Unbuffered.ReferenceRawCardUsed.Bits.Card;
  } else {
    DimmOut->ReferenceRawCard = (Spd->Lpddr.Module.LpDimm.ReferenceRawCardUsed.Bits.Extension << MRC_SPD_REF_RAW_CARD_SIZE) |
    Spd->Lpddr.Module.LpDimm.ReferenceRawCardUsed.Bits.Card;
  }

  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "  Reference raw card: %u '%s'\n",
    DimmOut->ReferenceRawCard,
    (DimmOut->ReferenceRawCard < (sizeof (RrcString) / sizeof (RrcString[0]))) ?
    RrcString[DimmOut->ReferenceRawCard] : UnknownString
  );
  return TRUE;
}

/**
  Calculate the CRC16 of the provided SPD data. CRC16 formula is the same
    one that is used for calculating the CRC16 stored at SPD bytes 126-127.
    This can be used to detect DIMM change.

    @param[in]  Buffer - Pointer to the start of the data.
    @param[in]  Size   - Amount of data in the buffer, in bytes.
    @param[out] Crc    - Pointer to location to write the calculated CRC16 value.

    @retval Returns TRUE.
**/
BOOLEAN
GetDimmCrc (
  IN  const UINT8 *const Buffer,
  IN  const UINT32       Size,
  OUT UINT16 *const      Crc
  )
{
  const UINT8 *Data;
  UINT32      Value;
  UINT32      Byte;
  UINT8       Bit;

  Data  = Buffer;
  Value = CRC_SEED;
  for (Byte = 0; Byte < Size; Byte++) {
    Value ^= (UINT32) *Data++ << 8;
    for (Bit = 0; Bit < 8; Bit++) {
      Value = (Value & MRC_BIT15) ? (Value << 1) ^ CRC_XOR_MASK : Value << 1;
    }
  }

  *Crc = (UINT16) Value;
  return TRUE;
}

/**
  Calculate the medium and fine timebases, using integer math.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if medium timebase is valid, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmTimeBase (
  IN OUT MrcParameters  *const MrcData
  )
{
  const MrcInput            *Inputs;
  const MrcControllerIn     *ControllerIn;
  const MrcChannelIn        *ChannelIn;
  const MrcDimmIn           *DimmIn;
  const MrcSpd              *Spd;
  MrcDebug                  *Debug;
  MrcOutput                 *Outputs;
  MrcControllerOut          *ControllerOut;
  MrcChannelOut             *ChannelOut;
  MrcDimmOut                *DimmOut;
  MrcTimeBase               *TimeBase;
  MrcProfile                Profile;
  UINT8                     Controller;
  UINT8                     Channel;
  UINT8                     Dimm;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", TimeBaseString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd      = &DimmIn->Spd.Data;
            TimeBase = &ChannelOut->TimeBase[Dimm][Profile];
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  switch (Spd->Ddr4.Base.Timebase.Bits.Medium) {
                    case 0:
                      TimeBase->Mtb = 125000;
                      break;
                    default:
                      TimeBase->Mtb = 0;
                      break;
                  }
                  switch (Spd->Ddr4.Base.Timebase.Bits.Fine) {
                    case 0:
                      TimeBase->Ftb = 1000;
                      break;
                    default:
                      TimeBase->Ftb = 0;
                      break;
                  }
                } else {
                  TimeBase->Ftb = 0;
                  TimeBase->Mtb = 0;
                }
                break;
              case USER_PROFILE:
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  switch (Spd->Ddr4.Base.Timebase.Bits.Medium) {
                    case 0:
                      TimeBase->Mtb = 125000;
                      break;
                    default:
                      TimeBase->Mtb = 0;
                      break;
                  }
                  switch (Spd->Ddr4.Base.Timebase.Bits.Fine) {
                    case 0:
                      TimeBase->Ftb = 1000;
                      break;
                    default:
                      TimeBase->Ftb = 0;
                      break;
                  }
                } else {
                  switch (Spd->Lpddr.Base.Timebase.Bits.Medium) {
                    case 0:
                      TimeBase->Mtb = 125000;
                      break;
                    default:
                      TimeBase->Mtb = 0;
                      break;
                  }
                  switch (Spd->Lpddr.Base.Timebase.Bits.Fine) {
                    case 0:
                      TimeBase->Ftb = 1000;
                      break;
                    default:
                      TimeBase->Ftb = 0;
                      break;
                  }
                }
                break;
            } //switch

            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u % 6u %u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              TimeBase->Mtb,
              TimeBase->Ftb
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  return TRUE;
}

/**
  Calculate the SDRAM minimum cycle time (tCKmin) that this DIMM supports.
    Then use the lookup table to obtain the frequency closest to the clock multiple.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if the DIMM frequency is supported, otherwise FALSE and the frequency is set to fInvalid.
**/
static
BOOLEAN
GetChannelDimmtCK (
  IN OUT MrcParameters  *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  INT32                 tCKminMtb;
  INT32                 tCKminFine;
  INT32                 tCKminIndex;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                DimmCalculated;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s (fs)\n", tCKString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = fNoInit;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            Calculated     = 0;
            DimmCalculated = 0;
            if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
              tCKminMtb   = Spd->Ddr4.Base.tCKmin.Bits.tCKmin;
              tCKminFine  = Spd->Ddr4.Base.tCKminFine.Bits.tCKminFine;
            } else {
              tCKminMtb   = Spd->Lpddr.Base.tCKmin.Bits.tCKmin;
              tCKminFine  = Spd->Lpddr.Base.tCKminFine.Bits.tCKminFine;
            }
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Data = &Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1];
                  tCKminMtb  = Data->tCKAVGmin.Bits.tCKmin;
                  tCKminFine = Data->tCKAVGminFine.Bits.tCKminFine;
                  DimmCalculated = (MediumTimebase * tCKminMtb) + (FineTimebase * tCKminFine);
                  Calculated = MAX (Outputs->MemoryClockMax, DimmCalculated);
                } else {
                  Calculated = 0;
                }
                break;
              case USER_PROFILE:
                if (Inputs->Ratio > 0) {
                  DimmCalculated = (MediumTimebase * tCKminMtb) + (FineTimebase * tCKminFine);
                  Calculated = MrcRatioToClock (MrcData, Inputs->Ratio, Outputs->RefClk, Inputs->BClkFrequency);
                  Calculated = MAX (Outputs->MemoryClockMax, Calculated);
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                DimmCalculated = (MediumTimebase * tCKminMtb) + (FineTimebase * tCKminFine);
                Calculated = MAX (Outputs->MemoryClockMax, DimmCalculated);
                break;
            } //switch
            Actual[Profile] = MAX (Actual[Profile], Calculated);

            // Find the closest tCK in the table
            ConvertClock2Freq (MrcData, Outputs->RefClk, Actual[Profile], &tCKminIndex);
            Actual[Profile] = FreqTable[tCKminIndex].tCK;
            if (Profile == Inputs->MemoryProfile) {
              DimmOut->Speed = ConvertClock2Freq (MrcData, Outputs->RefClk, DimmCalculated, NULL);
            }

            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u % 6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tCK    = Actual[Profile];
          ChannelOut->Timing[Profile].tCK = Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  Outputs->MemoryClock = Actual[Inputs->MemoryProfile];

  return TRUE;
}

/**
  Determine if the calculated CAS Latency is within the supported CAS Latency Mask

    @param[in] tAA         - the calculated CAS Latency in tCKs.
    @param[in] DdrType     - the SDRAM type number.
    @param[in] tCLMask     - the supported CAS Latency mask.
    @param[in] tCLLimitMin - the minimum supported CAS Latency
    @param[in] SdramWidth  - SDRAM width (8 or 16)

    @retval TRUE if the CAS latency has been found in supported mask, otherwise FALSE.
**/
static
BOOLEAN
ValidtCL (
  IN const UINT32     tAA,
  IN const MrcDdrType DdrType,
  IN const UINT32     tCLMask,
  IN const UINT32     tCLLimitMin,
  IN const UINT8      SdramWidth
  )
{
  BOOLEAN Valid;
  Valid = FALSE;

  switch (DdrType) {
    case MRC_DDR_TYPE_DDR4:
    default:
      Valid = ((tCLMask >> (tAA - tCLLimitMin)) & 1);
      break;

    // Fall through for other tAA values
    case MRC_DDR_TYPE_LPDDR4:
      if (DdrType == MRC_DDR_TYPE_LPDDR4) {
        if (SdramWidth == 16) {
          // Only allow legal RL values for x16 devices
          if ((tAA != 10) && (tAA != 14) && (tAA != 20) && (tAA != 24) && (tAA != 28) && (tAA != 32) && (tAA != 36)) {
            break;
          }
        } else {
          // Only allow legal RL values for x8 devices
          if ((tAA != 10) && (tAA != 16) && (tAA != 22) && (tAA != 26) && (tAA != 32) && (tAA != 36) && (tAA != 40)) {
            break;
          }
        }
      }

      // Check the CAS bitmask
      if ((tAA >= 12) && ((tAA % 2) == 0)) {
        Valid = ((tCLMask >> (tAA / 2)) & 1);
      } else if (tAA >= 8) {
        Valid = ((tCLMask >> (tAA - 6)) & 1);
      } else if ((tAA == 6) || (tAA == 3)) {
        Valid = ((tCLMask >> ((tAA / 3) - 1)) & 1);
      }
      break;
  }
  return Valid;
}

/**
  Calculate the tCL value for LPDDR4.
  JEDEC Spec x8/x16 RL values:
    Lower Clk   Upper Clk      x16    x8
    Freq Limit  Freq Limit     RL     RL
    --------------------------------------
    10            266          6      6
    266           533          10     10
    533           800          14     16
    800           1066         20     22
    1066          1333         24     26
    1333          1600         28     32
    1600          1866         32     36
    1866          2133         36     40

    @param[in] tCK         - the memory tCK in femtoseconds.
    @param[in] SdramWidth  - SDRAM width (8 or 16)

    @retval LPDDR4 tCL in tCK units
**/
static
UINT32
GetLpddr4tCL (
  IN const UINT32     tCK,
  IN UINT8            SdramWidth
  )
{
  UINT32 tCL;

  tCL = 0;
  if (tCK > 0) {
    if (SdramWidth == 8) {
      if (tCK < MRC_DDR_3733_TCK_MIN) {
        tCL = 40;
      } else if (tCK < MRC_DDR_3200_TCK_MIN) {
        tCL = 36;
      } else if (tCK < MRC_DDR_2667_TCK_MIN) {
        tCL = 32;
      } else if (tCK < MRC_DDR_2133_TCK_MIN) {
        tCL = 26;
      } else if (tCK < MRC_DDR_1600_TCK_MIN) {
        tCL = 22;
      } else if (tCK < MRC_DDR_1067_TCK_MIN) {
        tCL = 16;
      } else if (tCK < MRC_DDR_533_TCK_MIN) {
        tCL = 10;
      } else {
        tCL = 6;
      }
    } else { // x16
      if (tCK < MRC_DDR_3733_TCK_MIN) {
        tCL = 36;
      } else if (tCK < MRC_DDR_3200_TCK_MIN) {
        tCL = 32;
      } else if (tCK < MRC_DDR_2667_TCK_MIN) {
        tCL = 28;
      } else if (tCK < MRC_DDR_2133_TCK_MIN) {
        tCL = 24;
      } else if (tCK < MRC_DDR_1600_TCK_MIN) {
        tCL = 20;
      } else if (tCK < MRC_DDR_1067_TCK_MIN) {
        tCL = 14;
      } else if (tCK < MRC_DDR_533_TCK_MIN) {
        tCL = 10;
      } else {
        tCL = 6;
      }
    }
  } // tCK > 0
  return tCL;
}

/**
  Calculate the Minimum CAS Latency Time (tAAmin) for the given DIMMs.
      Step 1: Determine the common set of supported CAS Latency values for all modules
              on the memory channel using the CAS Latencies Supported in SPD.
      Step 2: Determine tAAmin(all) which is the largest tAAmin value for all modules on the memory channel.
      Step 3: Determine tCK(all) which is the largest tCKmin value for all
              the modules on the memory channel (Done in function GetChannelDimmtCK).
      Step 4: For a proposed tCK value between tCKmin and tCKmax, determine the desired CAS Latency.
              If tCKproposed is not a standard JEDEC value then tCKproposed must be adjusted to the
              next lower standard tCK value for calculating CLdesired.
      Step 5: Chose an actual CAS Latency that is greater than or equal to CLdesired and is
              supported by all modules on the memory channel as determined in step 1. If no such value exists,
              choose a higher tCKproposed value and repeat steps 4 and 5 until a solution is found.
      Step 6: Once the calculation of CLactual is completed, the BIOS must also verify that this CAS
              Latency value does not exceed tAAmax, which is 20 ns for all DDR3 speed grades.
              If not, choose a lower CL value and repeat steps 5 and 6 until a solution is found.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if the CAS latency has been calculated, otherwise FALSE and the returned value is set to zero.
**/
static
BOOLEAN
GetChannelDimmtAA (
  IN OUT MrcParameters  *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  BOOLEAN               Found[MAX_PROFILE];
  BOOLEAN               UserProfile;
  BOOLEAN               tCLOverride;
  BOOLEAN               Status;
  INT32                 MediumTimeBase;
  INT32                 FineTimeBase;
  INT32                 tCKminIndex;
  INT32                 tCKmin100;
  INT32                 tCKminIndexSave;
  INT32                 TimingFTB;
  UINT32                TimingMTB;
  UINT32                tCKmin;
  UINT32                CommonCasMask[MAX_PROFILE];
  UINT32                CasMask;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tCLLimitMin;
  UINT32                tCLLimitMax;
  UINT32                tAAmax;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT8                 SdramWidth;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data;
  UINT32                                     Index;

  Inputs         = &MrcData->Inputs;
  Outputs        = &MrcData->Outputs;
  Debug          = &Outputs->Debug;
  tCKmin         = 0;
  Calculated     = 0;
  Status         = FALSE;
  tCLOverride    = FALSE;
  MediumTimeBase = 0;
  FineTimeBase   = 0;
  TimingMTB      = 0;
  TimingFTB      = 0;
  SdramWidth     = 0;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s tCL Mask\n", tAAString, HeaderString);

  if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
    tAAmax = MRC_tAA_MAX_DDR4;
  } else {
    tAAmax = MRC_UINT32_MAX; // tAA_max is not defined for LPDDR4
  }
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    UserProfile            = (Profile == USER_PROFILE) && (Inputs->MemoryProfile == USER_PROFILE);
    CommonCasMask[Profile] = MRC_UINT32_MAX;
    Actual[Profile]        = 0;
    tCLLimitMin            = 4;
    tCLLimitMax            = 18;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            tCKmin         = ChannelOut->Dimm[Dimm].Timing[Profile].tCK;
            MediumTimeBase = ChannelOut->TimeBase[Dimm][Profile].Mtb;
            FineTimeBase   = ChannelOut->TimeBase[Dimm][Profile].Ftb;
            CasMask        = 0;
            SdramWidth     = DimmOut->SdramWidth;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Index = Profile - XMP_PROFILE1;
                  Data        = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                  tCLLimitMin = 7;
                  tCLLimitMax = 24;
                  TimingMTB   = Data->tAAmin.Bits.tAAmin;
                  TimingFTB   = Data->tAAminFine.Bits.tAAminFine;
                  CasMask     = Data->CasLatencies.Data & MRC_SPD_DDR4_CL_SUPPORTED_MASK;
                  Calculated  = (tCKmin == 0) ? 0 : ((MediumTimeBase * TimingMTB) + (FineTimeBase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;

              case USER_PROFILE:
                if (DimmIn->Timing.tCL > 0) {
                  CasMask         = MRC_UINT32_MAX;
                  Calculated      = DimmIn->Timing.tCL;
                  tCLOverride     = TRUE;
                  if (DimmOut->DdrType == MRC_DDR_TYPE_DDR4) {
                    tCLLimitMin = 7;
                    tCLLimitMax = 24;
                  }
                  break;
                } else {
                  // In AUTO mode, so no break.
                }

              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  tCLLimitMin = 7;
                  tCLLimitMax = 24;
                  TimingMTB   = Spd->Ddr4.Base.tAAmin.Bits.tAAmin;
                  TimingFTB   = Spd->Ddr4.Base.tAAminFine.Bits.tAAminFine;
                  CasMask     = Spd->Ddr4.Base.CasLatencies.Data & MRC_SPD_DDR4_CL_SUPPORTED_MASK;
                } else {
                  tCLLimitMin = 3;
                  tCLLimitMax = 40;
                  TimingMTB   = Spd->Lpddr.Base.tAAmin.Bits.tAAmin;
                  TimingFTB   = Spd->Lpddr.Base.tAAminFine.Bits.tAAminFine;
                  CasMask     = Spd->Lpddr.Base.CasLatencies.Data & MRC_SPD_LPDDR_CL_SUPPORTED_MASK;
                }
                if (DimmOut->DdrType == MRC_DDR_TYPE_LPDDR4) {
                  Calculated  = GetLpddr4tCL (tCKmin, SdramWidth);
                } else { // DDR4
                  // Using 2.5% rounding here according to the latest JEDEC SPD spec
                  // @todo Update all other timings to use 2.5% instead of 1%
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimeBase * TimingMTB) + (FineTimeBase * TimingFTB) - (tCKmin * 25 / 1000) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //end switch

            if (DimmOut->DdrType == MRC_DDR_TYPE_DDR4) {
              if (Calculated == 23) {
                Calculated = 24;                // 23 is not a valid DDR4 CAS value, use 24
              }
              if (UserProfile) {
                Calculated = MIN (Calculated, tCLLimitMax); // Enforce maximum allowed CAS value in User profile
              }
            }
            Actual[Profile] = MAX (Actual[Profile], Calculated);
            CommonCasMask[Profile] &= CasMask;
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u % 8Xh\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated,
              CasMask
              );
          } //if DimmOut->Status
        } //for Dimm
      } //for Channel
    } //for Controller

    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Profile %u common set of supported CAS Latency values = %Xh\n", Profile, CommonCasMask[Profile]);

    if ((Profile >= XMP_PROFILE1) && (tCKmin == 0)) {
      continue;
    }

    Found[Profile] = FALSE;
    ConvertClock2Freq (MrcData, Outputs->RefClk, tCKmin, &tCKminIndex);
    if ((Profile >= XMP_PROFILE1) && (Outputs->RefClk == MRC_REF_CLOCK_133) && (Outputs->Capable100)) {
      ConvertClock2Freq (MrcData, MRC_REF_CLOCK_100, tCKmin, &tCKmin100);
      if (tCKmin100 > tCKminIndex) {
        tCKminIndex = tCKmin100;
        if (Inputs->MemoryProfile == Profile) {
          Outputs->RefClk = MRC_REF_CLOCK_100;
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  Profile%u is RefClk 100 capable, switching to RefClk 100\n", Profile);
      }
    }
    do {
      for (; !Found[Profile] && (Actual[Profile] <= tCLLimitMax); Actual[Profile]++) {
        if (UserProfile) {
          Found[Profile] = TRUE;
        } else if ((Actual[Profile] * tCKmin) <= tAAmax) {
          Found[Profile] = ValidtCL (
                            Actual[Profile],
                            Outputs->DdrType,
                            CommonCasMask[Profile],
                            tCLLimitMin,
                            SdramWidth
                            );
        } // if
        if (Found[Profile]) {
          if (Profile == Inputs->MemoryProfile) {
            Outputs->MemoryClock = tCKmin;
            Status = TRUE;
          }
          for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
            ControllerOut = &Outputs->Controller[Controller];
            for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
              ChannelOut = &ControllerOut->Channel[Channel];
              for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
                DimmOut = &ChannelOut->Dimm[Dimm];
                if (DIMM_PRESENT == DimmOut->Status) {
                  DimmOut->Timing[Profile].tCL    = (UINT16) Actual[Profile];
                  ChannelOut->Timing[Profile].tCL = (UINT16) Actual[Profile];
                  DimmOut->Timing[Profile].tCK    = tCKmin;
                  ChannelOut->Timing[Profile].tCK = tCKmin;
                } //if
              } //for Dimm
            } //for Channel
          } //for Controller
          break;
        } //if
      } //for Actual[Profile]
      if (!Found[Profile]) {
        if (UserProfile && ((Inputs->Ratio > 0) || (tCLOverride == TRUE))) {
          break;
        } else {
          tCKminIndexSave = tCKminIndex;
          while (--tCKminIndex > 0) {
            if (((FreqTable[tCKminIndex].FreqFlag & (1 << Outputs->RefClk)) != 0)) {
              tCKmin = FreqTable[tCKminIndex].tCK;
              ConvertClock2Freq (MrcData, Outputs->RefClk, tCKmin, &tCKminIndex);
              Actual[Profile] = (tCKmin == 0) ? 0 : ((MediumTimeBase * TimingMTB) + (FineTimeBase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
              MRC_DEBUG_MSG (Debug,
                MSG_LEVEL_WARNING,
                "Warning: The memory frequency is being downgraded on profile %u, from %u to %u and the new tCL is %u\n",
                Profile,
                FreqTable[tCKminIndexSave].Frequency,
                FreqTable[tCKminIndex].Frequency,
                Actual[Profile]);
              break;
            }
          }
        }
      }
    } while (!Found[Profile] && (tCKminIndex > 0));
  } //for Profile

  Outputs->Frequency = ConvertClock2Freq (MrcData, Outputs->RefClk, Outputs->MemoryClock, NULL);
  Outputs->HighFrequency = Outputs->Frequency;

#ifdef MRC_DEBUG_PRINT
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Found[Profile] ? Actual[Profile] : 0);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n  Memory clock = %ufs\n  Memory Frequency = %u\n", Outputs->MemoryClock, Outputs->Frequency);
#endif

  return (Status);
}

/**
  Calculate the tCWL value for DDR4.
  JEDEC Spec:
                    Set A   Set B
   --------------------------------
   1600 and below:  9       11
   1867:            10      12
   2133:            11      14
   2400:            12      16
   2667:            14      18
   2933:            16      20
   3200:            16      20

    @param[in] tCK - the memory DCLK in femtoseconds.
    @param[in] tCL - current tCL in DCLKs.

    @retval DDR4 tCWL in DCLK units
**/
static
UINT32
GetDdr4tCWL (
  IN const UINT32 tCK,
  IN const UINT32 tCL
  )
{
  UINT32 tCWL;

  //
  // We pick up tCWL from the JEDEC list per frequency,
  // so that it will be closest to tCL, for performance reasons.
  //
  if (tCK >= MRC_DDR_1333_TCK_MIN) {
    tCWL = 9;
  } else if (tCK >= MRC_DDR_1600_TCK_MIN) {
    tCWL = (tCL >= 11) ? 11 : 9;
  } else if (tCK >= MRC_DDR_1867_TCK_MIN) {
    tCWL = 12;
  } else if (tCK >= MRC_DDR_2133_TCK_MIN) {
    tCWL = 14;
  } else if (tCK >= MRC_DDR_2400_TCK_MIN) {
    tCWL = (tCL >= 16) ? 16 : 12;
  } else if (tCK >= MRC_DDR_2667_TCK_MIN) {
    tCWL = (tCL >= 18) ? 18 : 14;
  } else if (tCK >= MRC_DDR_2933_TCK_MIN) {
    tCWL = (tCL >= 20) ? 20 : 16;
  } else {
    tCWL = 20;
  }

  return tCWL;
}

/**
  Calculate the tCWL value for LPDDR4.

  JEDEC Spec x8/x16 WL values:
    Lower Clk   Upper Clk      SetA   SetB
    Freq Limit  Freq Limit     WL     WL
    --------------------------------------
    10            266          4      4
    266           533          6      8
    533           800          8      12
    800           1066         10     18
    1066          1333         12     22
    1333          1600         14     26
    1600          1866         16     30
    1866          2133         18     34

  @param[in] tCK        - the memory DCLK in femtoseconds.

@retval LpDDR4 tCWL Value
**/
static
UINT32
GetLpddr4tCWL (
  IN UINT32 tCKmin
)
{
  UINT32 tCWL;

  tCWL = 0;
  //
  // Using WL Set B values from table 4.12 of LPDDR4 JEDEC Spec.
  // Adding 1 to take tDQSS into account.
  // We will subtract this 1 when programming TC_ODT.tCWL.
  //
  if (tCKmin < MRC_DDR_3733_TCK_MIN) {
    tCWL = 35;
  } else if (tCKmin < MRC_DDR_3200_TCK_MIN) {
    tCWL = 31;
  } else if (tCKmin < MRC_DDR_2667_TCK_MIN) {
    tCWL = 27;
  } else if (tCKmin < MRC_DDR_2133_TCK_MIN) {
    tCWL = 23;
  } else if (tCKmin < MRC_DDR_1600_TCK_MIN) {
    tCWL = 19;
  } else if (tCKmin < MRC_DDR_1067_TCK_MIN) {
    tCWL = 13;
  } else if (tCKmin < MRC_DDR_533_TCK_MIN) {
    tCWL = 9;
  } else {
    tCWL = 5;
  }

  return tCWL;
}

/**
  Calculate the minimum tCWL timing value for the given memory frequency.
    We calculate timings for all profiles so that this information can be passed out of MRC.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtCWL (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                Actual[MAX_PROFILE];
  UINT32                NewCL[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                tCL;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tCWLString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    NewCL[Profile]  = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            tCKmin         = DimmOut->Timing[Profile].tCK;
            tCL            = DimmOut->Timing[Profile].tCL;
            Calculated     = 0;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                    if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                      // DDR4 XMP spec doesn't have tCWL, so use JEDEC formulas
                      Calculated = GetDdr4tCWL (tCKmin, tCL);
                    }
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tCWL > 0) {
                  Calculated = DimmIn->Timing.tCWL;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (DimmOut->DdrType == MRC_DDR_TYPE_LPDDR4) {
                  Calculated  = GetLpddr4tCWL (tCKmin);
                } else if (DimmOut->DdrType == MRC_DDR_TYPE_DDR4) {
                  Calculated = GetDdr4tCWL (tCKmin, tCL);
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tCWL    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tCWL = (UINT16) Actual[Profile];
          if (NewCL[Profile] != 0) {
            //
            // Update tCL as well
            //
            DimmOut->Timing[Profile].tCL    = (UINT16) NewCL[Profile];
            ChannelOut->Timing[Profile].tCL = (UINT16) NewCL[Profile];
          }
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    if (NewCL[Profile] != 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Profile  %u: tCL was updated to %u\n", Profile, NewCL[Profile]);
    }
  }

  return TRUE;
}


/**
  Calculate the minimum tFAW timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtFAW (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tFAWString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Data = &Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1];
                  TimingMTB  = ((UINT32) (Data->tFAWMinUpper.Bits.tFAWminUpper) << 8) | (UINT32) (Data->tFAWmin.Bits.tFAWmin);
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tFAW > 0) {
                  Calculated = DimmIn->Timing.tFAW;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  TimingMTB = ((UINT32) (Spd->Ddr4.Base.tFAWMinUpper.Bits.tFAWminUpper) << 8) | (UINT32) (Spd->Ddr4.Base.tFAWmin.Bits.tFAWmin);
                  if (DimmOut->DdrType == MRC_DDR_TYPE_LPDDR4) {
                    Calculated = DIVIDECEIL ((40000000 - (tCKmin / 100)), tCKmin); // 40ns
                  } else {
                    Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tFAW    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tFAW = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRAS timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRAS (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data;
  UINT32                                     Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRASString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Index       = Profile - XMP_PROFILE1;
                  Data        = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                  TimingMTB   = ((UINT32) (Data->tRASMintRCMinUpper.Bits.tRASminUpper) << 8) | (UINT32) (Data->tRASmin.Bits.tRASmin);
                  Calculated  = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRAS > 0) {
                  Calculated = DimmIn->Timing.tRAS;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  TimingMTB = ((UINT32) (Spd->Ddr4.Base.tRASMintRCMinUpper.Bits.tRASminUpper) << 8) | (UINT32) (Spd->Ddr4.Base.tRASmin.Bits.tRASmin);
                  if (MRC_DDR_TYPE_LPDDR4 == DimmOut->DdrType) {
                    Calculated = DIVIDECEIL ((42000000 - (tCKmin / 100)), tCKmin); // 42ns
                  } else {
                    Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRAS    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRAS = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRC timing value for the given memory frequency.
  SKL MC doesn't have a register for tRC, it uses (tRAS + tRP).
  Print the tRC values for each profile and issue a warning if tRC > (tRAS + tRP).

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRC (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data;
  UINT32                                     Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRCString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Index       = Profile - XMP_PROFILE1;
                  Data        = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                  TimingMTB   = ((UINT32) (Data->tRASMintRCMinUpper.Bits.tRCminUpper) << 8) | (UINT32) (Data->tRCmin.Bits.tRCmin);
                  TimingFTB   = Data->tRCminFine.Bits.tRCminFine;
                  Calculated  = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
              case USER_PROFILE:
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  TimingMTB = ((UINT32) (Spd->Ddr4.Base.tRASMintRCMinUpper.Bits.tRCminUpper) << 8) | (UINT32) (Spd->Ddr4.Base.tRCmin.Bits.tRCmin);
                  TimingFTB = Spd->Ddr4.Base.tRCminFine.Bits.tRCminFine;
                  if (MRC_DDR_TYPE_LPDDR4 == DimmOut->DdrType) {
                    TimingMTB = (UINT32) (Spd->Lpddr.Base.tRPpb.Bits.tRPpb);
                    TimingFTB = Spd->Lpddr.Base.tRPpbFine.Bits.tRPpbFine;
                    Calculated = DIVIDECEIL (((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) + 42000000 - (tCKmin / 100)), tCKmin); // tRC = tRAS + tRPpb (tRAS is 42ns)
                  } else {
                    Calculated = ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        if (ChannelOut->Timing[Profile].tRAS + ChannelOut->Timing[Profile].tRCDtRP < (UINT16) Actual[Profile]) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "\nWARNING: tRC is bigger than tRAS+tRP !\n");
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRCD timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRCD (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data;
  UINT32                                      Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRCDString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Index       = Profile - XMP_PROFILE1;
                  Data        = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                  TimingMTB   = Data->tRCDmin.Bits.tRCDmin;
                  TimingFTB   = Data->tRCDminFine.Bits.tRCDminFine;
                  Calculated  = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRCDtRP > 0) {
                  Calculated = DimmIn->Timing.tRCDtRP;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                    TimingMTB = Spd->Ddr4.Base.tRCDmin.Bits.tRCDmin;
                    TimingFTB = Spd->Ddr4.Base.tRCDminFine.Bits.tRCDminFine;
                  } else {
                    TimingMTB = Spd->Lpddr.Base.tRCDmin.Bits.tRCDmin;
                    TimingFTB = Spd->Lpddr.Base.tRCDminFine.Bits.tRCDminFine;
                  }
                  Calculated = ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRCDtRP    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRCDtRP = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tREFI timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtREFI (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                TimingMTB;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tREFIString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  TimingMTB = TREFIMIN_DDR4;
                  Calculated = (tCKmin == 0) ? 0 : ((TimingMTB + ((tCKmin / 1000) - 1)) / (tCKmin / 1000));
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tREFI > 0) {
                  Calculated = DimmIn->Timing.tREFI;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  switch (DimmOut->DdrType)
                  {
                    default:
                    case MRC_DDR_TYPE_DDR4:
                      TimingMTB = TREFIMIN_DDR4;
                      break;
                    case MRC_DDR_TYPE_LPDDR4:
                      TimingMTB = TREFIMIN_LPDDR4;
                      break;
                  }
                  Calculated = ((TimingMTB + ((tCKmin / 1000) - 1)) / (tCKmin / 1000));
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tREFI    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tREFI = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRFC timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRFC (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRFCString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Index = Profile - XMP_PROFILE1;
                  TimingMTB = Spd->Ddr4.EndUser.Xmp.Data[Index].tRFC1min.Bits.tRFCmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRFC > 0) {
                  Calculated = DimmIn->Timing.tRFC;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                    TimingMTB = Spd->Ddr4.Base.tRFC1min.Bits.tRFCmin;
                  } else {
                    TimingMTB = Spd->Lpddr.Base.tRFCab.Bits.tRFCab;
                  }
                  // @todo: Temp w/a for 8GB dimms
                  Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRFC    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRFC = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRFCpb timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRFCpb (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRFCpbString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                // LPDDR timing.  LPDDR does not have XMP.
                Calculated = 0;
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRFCpb > 0) {
                  Calculated = DimmIn->Timing.tRFCpb;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (MRC_DDR_TYPE_LPDDR4 == DimmOut->DdrType) {
                    TimingMTB = Spd->Lpddr.Base.tRFCpb.Bits.tRFCpb;
                    Calculated = ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                  } else {
                    // This timing does not exist in non-LPDDR technologies.
                    Calculated = 0;
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRFCpb    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRFCpb = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRFC2 timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRFC2 (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRFC2String, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB = Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1].tRFC2min.Bits.tRFCmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRFC2 > 0) {
                  Calculated = DimmIn->Timing.tRFC2;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB  = Spd->Ddr4.Base.tRFC2min.Bits.tRFCmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRFC2    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRFC2 = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRFC4 timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRFC4 (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRFC4String, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB = Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1].tRFC4min.Bits.tRFCmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRFC4 > 0) {
                  Calculated = DimmIn->Timing.tRFC4;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB  = Spd->Ddr4.Base.tRFC4min.Bits.tRFCmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRFC4    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRFC4 = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRP timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRP (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data;
  UINT32                                      Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRPString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Index       = Profile - XMP_PROFILE1;
                  Data        = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                  TimingMTB   = Data->tRPmin.Bits.tRPmin;
                  TimingFTB   = Data->tRPminFine.Bits.tRPminFine;
                  Calculated  = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRCDtRP > 0) {
                  Calculated = DimmIn->Timing.tRCDtRP;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                    TimingMTB = Spd->Ddr4.Base.tRPmin.Bits.tRPmin;
                    TimingFTB = Spd->Ddr4.Base.tRPminFine.Bits.tRPminFine;
                  } else {
                    TimingMTB = Spd->Lpddr.Base.tRPpb.Bits.tRPpb;
                    TimingFTB = Spd->Lpddr.Base.tRPpbFine.Bits.tRPpbFine;
                  }
                  Calculated = ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            //
            // Take MAX of tRCD and tRP if they are different in SPD.
            // This assumes that GetChannelDimmtRCD() was already called.
            //
            Actual[Profile] = MAX (Actual[Profile], DimmOut->Timing[Profile].tRCDtRP);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRCDtRP    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRCDtRP = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRPab timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRPab (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  BOOLEAN               Flag;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Flag    = FALSE;

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if ((DIMM_PRESENT == DimmOut->Status) && (DimmOut->DdrType == MRC_DDR_TYPE_LPDDR4)) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            if (tCKmin > 0) {
              TimingMTB  = Spd->Lpddr.Base.tRPab.Bits.tRPab;
              TimingFTB  = Spd->Lpddr.Base.tRPabFine.Bits.tRPabFine;
              Calculated = ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
            }

            if (Calculated >= TRPABMINPOSSIBLE) {
              Actual[Profile] = MAX (Actual[Profile], Calculated);
            }
            if (!Flag) {
              Flag = TRUE;
              MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRPabString, HeaderString);
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_NOTE,
                "  % 7u % 10u % 8u % 5u %6u\n",
                Profile,
                Controller,
                Channel,
                Dimm,
                Calculated
                );
            } //Flag
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  if (Flag) {
    //
    // Set the best case timing for all controllers/channels/dimms, for each profile.
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
    for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
      if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
        continue;
      }
      for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
        ControllerOut = &Outputs->Controller[Controller];
        for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
          ChannelOut = &ControllerOut->Channel[Channel];
          for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
            DimmOut = &ChannelOut->Dimm[Dimm];
            DimmOut->Timing[Profile].tRPab    = (UINT16) Actual[Profile];
            ChannelOut->Timing[Profile].tRPab = (UINT16) Actual[Profile];
          }
        }
      }
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  }

  return TRUE;

}

/**
  Calculate the minimum tRRD timing value for the given memory frequency.
    MRC should not set tRRD below 4nCK for all frequencies.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE
**/
static
BOOLEAN
GetChannelDimmtRRD (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 MediumTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                Index;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRRDString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Index = Profile - XMP_PROFILE1;
                  TimingMTB = Spd->Ddr3.Xmp.Data[Index].tRRDmin.Bits.tRRDmin;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRRD > 0) {
                  Calculated = DimmIn->Timing.tRRD;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                    Calculated = 0; // tRRD isn't used for DDR4
                  } else {
                    Calculated = DIVIDECEIL ((10000000 - (tCKmin / 100)), tCKmin); // 10ns
                  }
                }
                break;
            } //switch

            Calculated = MAX (Calculated, TRRDMINPOSSIBLE);  // Make sure tRRD is at least 4 tCK
            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRRD    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRRD = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRRD same bank group timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRRD_L (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRRDLString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Data        = &Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1];
                  TimingMTB   = Data->tRRD_Lmin.Bits.tRRDmin;
                  TimingFTB   = Data->tRRD_LminFine.Bits.tRRDminFine;
                  Calculated  = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRRD_L > 0) {
                  Calculated = DimmIn->Timing.tRRD_L;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB = Spd->Ddr4.Base.tRRD_Lmin.Bits.tRRDmin;
                  TimingFTB = Spd->Ddr4.Base.tRRD_LminFine.Bits.tRRDminFine;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRRD_L    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRRD_L = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tRRD different bank group timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRRD_S (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRRDSString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Data        = &Spd->Ddr4.EndUser.Xmp.Data[Profile - XMP_PROFILE1];
                  TimingMTB   = Data->tRRD_Smin.Bits.tRRDmin;
                  TimingFTB   = Data->tRRD_SminFine.Bits.tRRDminFine;
                  Calculated  = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                } else {
                  Calculated = 0;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRRD_S > 0) {
                  Calculated = DimmIn->Timing.tRRD_S;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB = (UINT32) Spd->Ddr4.Base.tRRD_Smin.Bits.tRRDmin;
                  TimingFTB = (INT32) Spd->Ddr4.Base.tRRD_SminFine.Bits.tRRDminFine;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRRD_S    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRRD_S = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the tRTP value for DDR4.
  JEDEC Spec: tRTP = max (4nCK, 7.5ns)

    @param[in] tCK - the memory DCLK in femtoseconds.

    @retval DDR4 tRTP in DCLK units
**/
static
UINT32
GetDdr4tRTP (
  IN const UINT32 tCK
  )
{
  UINT32 tRTP;

  tRTP = (tCK == 0) ? 0 : DIVIDECEIL ((7500000 - (tCK / 100)), tCK); // 7.5ns
  tRTP = RANGE (tRTP, DDR4_TRTPMINPOSSIBLE, DDR4_TRTPMAXPOSSIBLE);   // JEDEC limits
  if (tRTP == 11) {
    tRTP++;         // 11 is not a valid value, use 12
  }
  return tRTP;
}

/**
  Calculate the tWR value for DDR4.
  JEDEC Spec: tWR = 15ns

    @param[in] tCK - the memory DCLK in femtoseconds.

    @retval DDR4 tWR in DCLK units
**/
static
UINT32
GetDdr4tWR (
  IN const UINT32 tCK
  )
{
  UINT32 tWR;

  tWR = (tCK == 0) ? 0 : DIVIDECEIL ((15000000 - (tCK / 100)), tCK); // 15ns
  if (tWR % 2) {
    tWR++;          // Calculated tWR is odd number, round up to next even number
  }
  tWR = RANGE (tWR, DDR4_TWRMINPOSSIBLE, DDR4_TWRMAXPOSSIBLE);  // JEDEC limits
  if (tWR == 22) {
    tWR = 24;       // tWR of 22 is not a valid value, use the next one
  }
  return tWR;
}

/**
  Calculate the tCCD_L value for DDR4.
  JEDEC Spec:
   1333 and below:  4 nCK
   1600:            max(5 nCK, 6.250 ns)
   1867:            max(5 nCK, 5.355 ns)
   2133:            max(5 nCK, 5.355 ns)
   2400 and above:  max(5 nCK, 5 ns)

    @param[in] tCK - the memory DCLK in femtoseconds.

    @retval DDR4 tCCD_L in DCLK units
**/
static
UINT32
GetDdr4tCCDL (
  IN const UINT32 tCK
  )
{
  UINT32 tCCD_L;

  if (tCK >= MRC_DDR_1333_TCK_MIN) {
    tCCD_L = tCCD_L_1333_AND_LOWER;
  } else if (tCK >= MRC_DDR_1600_TCK_MIN) {
    tCCD_L = DIVIDECEIL (tCCD_L_1600_FS - (tCK / 100), tCK);      // 6.250 ns
  } else if (tCK >= MRC_DDR_2133_TCK_MIN) {
    tCCD_L = DIVIDECEIL (tCCD_L_1867_2133_FS - (tCK / 100), tCK); // 5.355 ns
  } else {
    tCCD_L = DIVIDECEIL (tCCD_L_2400_FS - (tCK / 100), tCK);      // 5 ns
  }

  if (tCK < MRC_DDR_1333_TCK_MIN) {
    tCCD_L = MAX (tCCD_L, 5);
  }

  return tCCD_L;
}

/**
  Calculate the tWR value for LPDDR
  JEDEC Spec: tWR = 18ns for LPDDR4 x16, 20ns for LPDDR4 x8

    @param[in] tCK        - the memory DCLK in femtoseconds.
    @param[in] SdramWidth - 8 or 16

    @retval LPDDR4 tWR in DCLK units
**/
static
UINT32
GetLpddrtWR (
  IN const UINT32     tCK,
  IN UINT8            SdramWidth
  )
{
  UINT32 tWR;

  tWR = 0;
  if (tCK > 0) {
    if (SdramWidth == 8) {
      tWR = DIVIDECEIL ((20000000 - (tCK / 100)), tCK); // 20ns
      if (tWR <= 6) {
        tWR = 6;
      } else if (tWR <= 12) {
        tWR = 12;
      } else if (tWR <= 16) {
        tWR = 16;
      } else if (tWR <= 22) {
        tWR = 22;
      } else if (tWR <= 28) {
        tWR = 28;
      } else if (tWR <= 32) {
        tWR = 32;
      } else if (tWR <= 38) {
        tWR = 38;
      } else {
        tWR = 44;
      }
    } else { // x16
      tWR = DIVIDECEIL ((18000000 - (tCK / 100)), tCK); // 18ns
      if (tWR <= 6) {
        tWR = 6;
      } else if (tWR <= 10) {
        tWR = 10;
      } else if (tWR <= 16) {
        tWR = 16;
      } else if (tWR <= 20) {
        tWR = 20;
      } else if (tWR <= 24) {
        tWR = 24;
      } else if (tWR <= 30) {
        tWR = 30;
      } else if (tWR <= 34) {
        tWR = 34;
      } else {
        tWR = 40;
      }
    }
  } // tCK > 0
  return tWR;
}

/**
  Calculate the minimum tRTP timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtRTP (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tRTPString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Calculated = GetDdr4tRTP (tCKmin);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tRTP > 0) {
                  Calculated = DimmIn->Timing.tRTP;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (DimmOut->DdrType == MRC_DDR_TYPE_DDR4) {
                    Calculated = GetDdr4tRTP (tCKmin);
                  } else { // LPDDR4
                    Calculated = DIVIDECEIL ((7500000 - (tCKmin / 100)), tCKmin); // 7.5ns
                    if (Calculated < LPDDR4_TRTPMINPOSSIBLE) {
                      Calculated = LPDDR4_TRTPMINPOSSIBLE;
                    }
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tRTP    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tRTP = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tWR timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtWR (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  Inputs      = &MrcData->Inputs;
  Outputs     = &MrcData->Outputs;
  Debug       = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tWRString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Calculated = GetDdr4tWR (tCKmin);
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tWR > 0) {
                  Calculated = DimmIn->Timing.tWR;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (DimmOut->DdrType == MRC_DDR_TYPE_DDR4) {
                    Calculated = GetDdr4tWR (tCKmin);
                  } else { // LPDDR4
                    Calculated = GetLpddrtWR (tCKmin, DimmOut->SdramWidth);
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tWR    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tWR = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum tWTR timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtWTR (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                DataRateMinWtR;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tWTRString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tWTR > 0) {
                  Calculated = DimmIn->Timing.tWTR;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (tCKmin > 0) {
                  if (MRC_DDR_TYPE_LPDDR4 == DimmOut->DdrType) {
                    if (DimmOut->SdramWidth == 8) {
                      DataRateMinWtR = 12000000;  // 12ns
                    } else {
                      DataRateMinWtR = 10000000;  // 10ns
                    }
                    Calculated = DIVIDECEIL ((DataRateMinWtR - (tCKmin / 100)), tCKmin);
                    //Check max 8nCK
                    Calculated = MAX (Calculated, 8);
                  }
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tWTR    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tWTR = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the tWTR_L timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtWTR_L (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tWTRLString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  Calculated = (tCKmin == 0) ? 0 : (7500000 - (tCKmin / 100) + tCKmin - 1) / tCKmin; // 7.5ns
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tWTR_L > 0) {
                  Calculated = DimmIn->Timing.tWTR_L;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  Calculated = (tCKmin == 0) ? 0 : (7500000 - (tCKmin / 100) + tCKmin - 1) / tCKmin; // 7.5ns
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tWTR_L    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tWTR_L = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the tWTR_S timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtWTR_S (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tWTRSString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            switch (Profile) {
              case USER_PROFILE:
                if (DimmIn->Timing.tWTR_S > 0) {
                  Calculated = DimmIn->Timing.tWTR_S;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case XMP_PROFILE1:
              case XMP_PROFILE2:
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  Calculated = (tCKmin == 0) ? 0 : (2500000 - (tCKmin / 100) + tCKmin - 1) / tCKmin; // 2.5ns
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tWTR_S    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tWTR_S = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the tCCD_L timing value for the given memory frequency.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmtCCD_L (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  const MrcSpd          *Spd;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcTimeBase           *TimeBase;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                tCKmin;
  UINT32                TimingMTB;
  INT32                 TimingFTB;
  INT32                 MediumTimebase;
  INT32                 FineTimebase;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;
  UINT32                JedecValue;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", tCCDLSString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd            = &DimmIn->Spd.Data;
            Calculated     = 0;
            tCKmin         = DimmOut->Timing[Profile].tCK;
            TimeBase       = &ChannelOut->TimeBase[Dimm][Profile];
            MediumTimebase = TimeBase->Mtb;
            FineTimebase   = TimeBase->Ftb;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  // DDR4 XMP spec doesn't have tCCD_L, so use JEDEC formulas
                  Calculated = GetDdr4tCCDL (tCKmin);
                } else {
                  Calculated = 0;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.tCCD_L > 0) {
                  Calculated = DimmIn->Timing.tCCD_L;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_DDR4 == DimmOut->DdrType) {
                  TimingMTB = (UINT32) Spd->Ddr4.Base.tCCD_Lmin.Bits.tCCDLmin;
                  TimingFTB =  (INT32) Spd->Ddr4.Base.tCCD_LminFine.Bits.tCCDLminFine;
                  Calculated = (tCKmin == 0) ? 0 : ((MediumTimebase * TimingMTB) + (FineTimebase * TimingFTB) - (tCKmin / 100) + (tCKmin - 1)) / tCKmin;

                  // Avoid JEDEC violation when downclocking (i.e. running a 2400 DIMM at 1600)
                  // Allow SPD value to be more relaxed than JEDEC spec, but not more tight
                  JedecValue = GetDdr4tCCDL (tCKmin);
                  Calculated = MAX (Calculated, JedecValue);
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].tCCD_L     = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].tCCD_L  = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the minimum command rate mode value for the given channel.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmNmode (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput        *Inputs;
  const MrcControllerIn *ControllerIn;
  const MrcChannelIn    *ChannelIn;
  const MrcDimmIn       *DimmIn;
  MrcDebug              *Debug;
  MrcOutput             *Outputs;
  MrcControllerOut      *ControllerOut;
  MrcChannelOut         *ChannelOut;
  MrcDimmOut            *DimmOut;
  MrcProfile            Profile;
  UINT8                 Controller;
  UINT8                 Channel;
  UINT8                 Dimm;
  UINT32                Actual[MAX_PROFILE];
  UINT32                Calculated;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", NmodeString, HeaderString);

  //
  // Find the smallest timing value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = (Profile < XMP_PROFILE1) ? NMODEMINPOSSIBLE : 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Calculated     = 2;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Calculated = NMODEMINPOSSIBLE;
                }
                break;
              case USER_PROFILE:
                if (DimmIn->Timing.NMode > 0) {
                  Calculated = DimmIn->Timing.NMode;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                Calculated = NMODEMINPOSSIBLE;
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %6u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case timing for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          DimmOut->Timing[Profile].NMode    = (UINT16) Actual[Profile];
          ChannelOut->Timing[Profile].NMode = (UINT16) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Calculate the VDD voltage value for the given channel.

    @param[in, out] MrcData - Pointer to MrcData data structure.

    @retval TRUE if there are DIMMs present, otherwise FALSE.
**/
static
BOOLEAN
GetChannelDimmVdd (
  IN OUT MrcParameters *const MrcData
  )
{
  const MrcInput                        *Inputs;
  const MrcControllerIn                 *ControllerIn;
  const MrcChannelIn                    *ChannelIn;
  const MrcDimmIn                       *DimmIn;
  const MrcSpd                          *Spd;
  MrcDebug                              *Debug;
  MrcOutput                             *Outputs;
  MrcControllerOut                      *ControllerOut;
  MrcChannelOut                         *ChannelOut;
  MrcDimmOut                            *DimmOut;
  MrcProfile                            Profile;
  MrcDdrType                            DdrType;
  UINT32                                Actual[MAX_PROFILE];
  UINT32                                Calculated;
  UINT8                                 Controller;
  UINT8                                 Channel;
  UINT8                                 Dimm;

  const SPD_EXTREME_MEMORY_PROFILE_DATA_2_0  *Data;
  UINT32                                      Index;

  Inputs   = &MrcData->Inputs;
  Outputs  = &MrcData->Outputs;
  Debug    = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "  %s:\n  %s\n", VddString, HeaderString);

  //
  // Find the best case voltage value for all the given DIMMs, for all the profiles.
  //
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    Actual[Profile] = (Profile < XMP_PROFILE1) ? VDD_0_60 : 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerIn  = &Inputs->Controller[Controller];
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelIn   = &ControllerIn->Channel[Channel];
        ChannelOut  = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmIn  = &ChannelIn->Dimm[Dimm];
          DimmOut = &ChannelOut->Dimm[Dimm];
          DdrType = DimmOut->DdrType;
          if (DIMM_PRESENT == DimmOut->Status) {
            Spd        = &DimmIn->Spd.Data;
            Calculated = VDD_1_50;
            switch (Profile) {
              case XMP_PROFILE1:
              case XMP_PROFILE2:
                Calculated = 0;
                if (((Profile == XMP_PROFILE1) && ((DimmOut->XmpSupport & 1) != 0)) ||
                    ((Profile == XMP_PROFILE2) && ((DimmOut->XmpSupport & 2) != 0))) {
                  Index       = Profile - XMP_PROFILE1;
                  Data        = &Spd->Ddr4.EndUser.Xmp.Data[Index];
                  Calculated  = XMP_VDD_INCREMENT_2 * Data->Vdd.Bits.Decimal;
                  Calculated  = MIN (Calculated, XMP_VDD_INTEGER - 1);
                  Calculated += (XMP_VDD_INTEGER * Data->Vdd.Bits.Integer);
                  Calculated  = MAX (Calculated, XMP_VDD_MIN_POSSIBLE);
                  Calculated  = MIN (Calculated, XMP_VDD_MAX_POSSIBLE);
                }
                break;
              case USER_PROFILE:
                if (Inputs->VddVoltage > 0) {
                  Calculated = Inputs->VddVoltage;
                  break;
                } else {
                  // In AUTO mode, so no break.
                }
              case STD_PROFILE:
              default:
                if (MRC_DDR_TYPE_LPDDR4 == DdrType) {
                  if (Outputs->Lp4x) {
                    Calculated = VDD_0_60;
                  } else {
                    Calculated = VDD_1_10;
                  }
                } else { // DDR4
                  Calculated = VDD_1_20;
                }
                break;
            } //switch

            Actual[Profile] = MAX (Actual[Profile], Calculated);
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "  % 7u % 10u % 8u % 5u %4u\n",
              Profile,
              Controller,
              Channel,
              Dimm,
              Calculated
            );
          } //DimmOut->Status
        } //Dimm
      } //Channel
    } //Controller
  } //Profile

  //
  // Set the best case voltage for all controllers/channels/dimms, for each profile.
  //
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "    %s%u:", BestCaseString, MAX_PROFILE - 1);
  for (Profile = STD_PROFILE; Profile < MAX_PROFILE; Profile++) {
    if (((Profile == XMP_PROFILE1) || (Profile == XMP_PROFILE2)) && (!(Outputs->XmpProfileEnable))) {
      continue;
    }
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      ControllerOut = &Outputs->Controller[Controller];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          Outputs->VddVoltage[Profile] = (MrcVddSelect) Actual[Profile];
          DimmOut->VddVoltage[Profile] = (MrcVddSelect) Actual[Profile];
        }
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %u", Actual[Profile]);
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");

  return TRUE;
}

/**
  Analyze the given DIMM SPD data to determine DIMM presence and configuration.

    @param[in, out] MrcData - Pointer to MRC global data structure.
    @param[in] Controller   - Current controller number.
    @param[in] Channel      - Current channel number.
    @param[in] Dimm         - Current DIMM number.

    @retval mrcSuccess if DIMM is present otherwise mrcDimmNotExist.
**/
static
MrcStatus
SpdDimmRecognition (
  IN OUT MrcParameters *const MrcData,
  IN  const UINT8          Controller,
  IN  UINT8                Channel,
  IN  UINT8                Dimm
  )
{
  static const SpdRecogCallTable CallTable[] = {
    {ValidDimm},
    {ValidSdramDeviceWidth},
    {ValidPrimaryWidth},
    {GetRankCount},
    {ValidBank},
    {GetDimmSize},
    {ValidRowSize},
    {ValidColumnSize},
    {ValidEccSupport},
    {GetAddressMirror},
    {GetThermalRefreshSupport},
    {GetpTRRsupport},
    {GetReferenceRawCardSupport}
  };
  const MrcSpd *Spd;
  const UINT8  *CrcStart;
  MrcDimmOut   *DimmOut;
  MrcDimmIn    *DimmIn;
  BOOLEAN      Status;
  UINT32       CrcSize;
  UINT8        Index;

  DimmIn  = &MrcData->Inputs.Controller[Controller].Channel[Channel].Dimm[Dimm];
  Spd     = &DimmIn->Spd.Data;
  DimmOut = &MrcData->Outputs.Controller[Controller].Channel[Channel].Dimm[Dimm];
  DimmOut->Status = DIMM_NOT_PRESENT;
  if (DIMM_PRESENT == DimmPresence (&MrcData->Outputs.Debug, Spd)) {
    Status = TRUE;
    for (Index = 0; (Status == TRUE) && (Index < ARRAY_COUNT (CallTable)); Index++) {
      Status &= CallTable[Index].mrc_task (MrcData, Spd, DimmOut);
    }
    if (Status == FALSE) {
      DimmOut->Status = DIMM_DISABLED;
      return mrcDimmNotExist;
    }
    DimmOut->Status = DIMM_PRESENT;
    CrcStart = MrcSpdCrcArea (MrcData, Controller, Channel, Dimm, &CrcSize);
    GetDimmCrc ((const UINT8*const) CrcStart, CrcSize, &DimmOut->Crc);
  } else {
    return mrcDimmNotExist;
  }

  if (DIMM_DISABLED == DimmIn->Status) {
    DimmOut->Status = DIMM_DISABLED;
    DimmOut->Crc    = 0;              // Clear the CRC for Disabled DIMMs so that we don't break Fast flow in MrcFastBootPermitted()
  }

  return mrcSuccess;
}

/**
  Calculate the timing of all DIMMs on all channels.

    @param[in, out] MrcData - The MRC "global data".

    @retval mrcSuccess on success, mrcDimmNotExist if no DIMMs found.
**/
static
MrcStatus
SpdTimingCalculation (
  IN OUT MrcParameters *const MrcData
  )
{
  static const SpdTimeCallTable CallTable[] = {
    {GetChannelDimmTimeBase}, // Note: This must be done first as all other calculations are based on this.
    {GetChannelDimmtCK},      // Note: This must be done second as all other calculations are based on this.
    {GetChannelDimmtAA},
    {GetChannelDimmtCWL},
    {GetChannelDimmtRAS},
    {GetChannelDimmtRCD},
    {GetChannelDimmtRC},      // Note: This must be done after GetChannelDimmtRAS and GetChannelDimmtRCD
    {GetChannelDimmtREFI},
    {GetChannelDimmtRFC},
    {GetChannelDimmtRFCpb},
    {GetChannelDimmtRP},      // Note: This must be done after GetChannelDimmtRCD
    {GetChannelDimmtRPab},    // Note: This must be done after GetChannelDimmtRP
    {GetChannelDimmtFAW},
    {GetChannelDimmtRRD},
    {GetChannelDimmtRTP},
    {GetChannelDimmtWR},
    {GetChannelDimmtWTR},
    {GetChannelDimmtRFC2},
    {GetChannelDimmtRFC4},
    {GetChannelDimmtRRD_L},
    {GetChannelDimmtRRD_S},
    {GetChannelDimmtWTR_L},
    {GetChannelDimmtWTR_S},
    {GetChannelDimmtCCD_L},
    {GetChannelDimmNmode},
    {GetChannelDimmVdd}
  };
  BOOLEAN    Status;
  UINT8      Index;
#if (SUPPORT_FORCE == SUPPORT)
  MrcChannelOut *ChannelOut;
  MrcDimmOut    *DimmOut;
  UINT16     Value;
  UINT8      Controller;
  UINT8      Channel;
  UINT8      Dimm;
#endif

  //
  // Find the "least common denominator" timing across the DIMMs.
  // tAA must be done first before any other timings are calculated.
  //
  Status = TRUE;
  for (Index = 0; (Status == TRUE) && (Index < (sizeof (CallTable) / sizeof (SpdTimeCallTable))); Index++) {
    Status &= CallTable[Index].mrc_task (MrcData);
  }

#if (SUPPORT_FORCE == SUPPORT)
  if (Status == TRUE) {
    //
    // Force tCLmin, tRCDmin, tRPmin to be the same "least common denominator" value.
    //
    Value = 0;
    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &Outputs->Controller[Controller].Channel[Channel].Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            Value = MAX (Value, DimmOut->Timing.tRCDtRP);
            Value = MAX (Value, DimmOut->Timing.tCL);
          }
        }
      }
    }

    for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          if (DIMM_PRESENT == DimmOut->Status) {
            ChannelOut->Timing.tRCDtRP = Value;
            ChannelOut->Timing.tCL     = Value;
            DimmOut->Timing.tRCDtRP = Value;
            DimmOut->Timing.tCL     = Value;
          }
        }
      }
    }
  }
#endif
  return (Status == FALSE) ? mrcDimmNotExist : mrcSuccess;
}

/**
  Determine the starting address and size of the SPD area to generate a CRC.

    @param[in, out] MrcData    - The MRC "global data".
    @param[in]      Controller - Controller index.
    @param[in]      Channel    - Channel index.
    @param[in]      Dimm       - Dimm index.
    @param[out]     CrcSize    - Location to write CRC block size.

    @retval The starting address of the CRC block.
**/
const UINT8 *
MrcSpdCrcArea (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8                Controller,
  IN     UINT8                Channel,
  IN     UINT8                Dimm,
  OUT    UINT32        *const CrcSize
  )
{
  const MrcDimmIn   *DimmIn;
  const UINT8       *CrcStart;
  UINT8             DdrType;

  DimmIn  = &MrcData->Inputs.Controller[Controller].Channel[Channel].Dimm[Dimm];
  DdrType = DimmIn->Spd.Data.Ddr3.General.DramDeviceType.Bits.Type;
  if (MRC_SPD_DDR4_SDRAM_TYPE_NUMBER == DdrType) {
    CrcStart = (void *) &DimmIn->Spd.Data.Ddr4.ManufactureInfo;
    *CrcSize = SPD4_MANUF_SIZE;
  } else if ((MRC_SPD_LPDDR4_SDRAM_TYPE_NUMBER == DdrType) || (MRC_SPD_LPDDR4X_SDRAM_TYPE_NUMBER == DdrType)) {
    CrcStart = (void *) &DimmIn->Spd.Data.Lpddr.ManufactureInfo;
    *CrcSize = SPDLP_MANUF_SIZE;
  } else {
    CrcStart = NULL;
    *CrcSize = 0;
  }
  return (CrcStart);
}

/**
  Check that DqsMapCpu2Dram has valid values.

  @param[in, out] MrcData - The MRC "global data".

  @retval mrcSuccess on success, mrcWrongInputParameter if these tables have invalid values.
**/
MrcStatus
MrcCheckLpddrMapping (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug        *Debug;
  MrcInput        *Inputs;
  MrcChannelIn    *ChannelIn;
  MrcStatus       Status;
  MrcOutput       *Outputs;
  UINT8           CpuByte;
  UINT8           DramByte;
  UINT8           Channel;
  UINT8           *DqsMapCpu2Dram;
  UINT8           DqsMap;
  BOOLEAN         DqsMapCpu2DramGood;
  BOOLEAN         Lpddr4;

  Status  = mrcSuccess;
  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Lpddr4  = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  DqsMapCpu2DramGood = TRUE;

  if (!Lpddr4) {
    return mrcSuccess;
  }

  for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
    if (!MrcChannelExist (Outputs, Channel)) {
      continue;
    }
    ChannelIn = &Inputs->Controller[0].Channel[Channel];
    DqsMapCpu2Dram = ChannelIn->DqsMapCpu2Dram;
    DqsMap = 0;

    for (CpuByte = 0; CpuByte < 8; CpuByte++) {
      DramByte = DqsMapCpu2Dram[CpuByte];
      if (DramByte < 8) {
        DqsMap |= (1 << DramByte);
      }
    } // for CpuByte
    if (DqsMap != 0xFF) {
      DqsMapCpu2DramGood = FALSE;
    }
  } // for Channel

  if (!DqsMapCpu2DramGood) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR,"%s input array %s has invalid values !\n", gErrString, "DqsMapCpu2Dram");
    Status = mrcWrongInputParameter;
  }

  return Status;
}

/**
  Check that some MRC input parameters make sense for the current DDR type.

  @param[in] MrcData - The MRC "global data".

  @retval mrcSuccess on success, mrcWrongInputParameter if parameters have invalid values.
**/
MrcStatus
MrcCheckInputParams (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcStatus             Status;

  Status = MrcCheckLpddrMapping (MrcData);

  return Status;
}

/**
  Process the SPD information for all DIMMs on all channels.

    @param[in, out] MrcData - The MRC "global data".

    @retval mrcSuccess on success, mrcDimmNotExist if no DIMMs found.
**/
MrcStatus
MrcSpdProcessing (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcDebug                      *Debug;
  const MrcInput                *Inputs;
  const MrcControllerIn         *ControllerIn;
  const MrcChannelIn            *ChannelIn;
  const MrcDimmIn               *DimmIn;
  const MrcSpd                  *SpdIn;
  MrcStatus                     Status;
  MrcOutput                     *Outputs;
  MrcControllerOut              *ControllerOut;
  MrcChannelOut                 *ChannelOut;
  MrcDimmOut                    *DimmOut;
  UINT8                         Controller;
  UINT8                         Channel;
  UINT8                         Dimm;
  UINT32                        DimmCount;
  UINT8                         ValidRankBitMask;
  UINT8                         ExpectedWidth;
  UINT16                        DateCode;
  const SPD4_MANUFACTURING_DATA *ManufactureData;
  UINT8                         DensityIndex;
  UINT8                         SdramWidthIndex;
  UINT8                         DimmPartNumber;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;
  Status  = mrcDimmNotExist;

  Outputs->DdrType = MRC_DDR_TYPE_UNKNOWN;
  Outputs->tMAC    = MRC_TMAC_UNLIMITED;

  //
  // Scan thru each DIMM to see if it is a valid DIMM and to get its configuration.
  //
  DimmCount  = 0;
  for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
    ControllerIn  = &Inputs->Controller[Controller];
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      ChannelIn   = &ControllerIn->Channel[Channel];
      ChannelOut  = &ControllerOut->Channel[Channel];
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        DimmIn  = &ChannelIn->Dimm[Dimm];
        DimmOut = &ChannelOut->Dimm[Dimm];
        if (DimmIn->Status == DIMM_ENABLED || DimmIn->Status == DIMM_DISABLED) {
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "SPD Dimm recognition, %s %u/%u/%u\n",
            CcdString,
            Controller,
            Channel,
            Dimm
            );
          if (mrcSuccess == SpdDimmRecognition (MrcData, Controller, Channel, Dimm)) {
            DimmCount++;
            if (MRC_DDR_TYPE_UNKNOWN == Outputs->DdrType) {
              Outputs->DdrType = DimmOut->DdrType;
            } else if (Outputs->DdrType != DimmOut->DdrType) {
              Status = mrcMixedDimmSystem;
            }
            if (Status == mrcMixedDimmSystem) {
              MRC_DEBUG_MSG (
                Debug,
                MSG_LEVEL_ERROR,
                "%s configuration, system contains a mix of memory types\n",
                ErrorString
                );
              return (Status);
            }
          }
        }
      }
    }
  }

  // Check for mixed PrimaryBusWidth - for LP3 and LP4 only
  if (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) {
    ExpectedWidth = Outputs->EnhancedChannelMode ? MRC_SPD_PRIMARY_BUS_WIDTH_32 : MRC_SPD_PRIMARY_BUS_WIDTH_64;
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
        if (Outputs->Controller[0].Channel[Channel].Dimm[Dimm].Status == DIMM_PRESENT) {
          SpdIn = &Inputs->Controller[0].Channel[Channel].Dimm[Dimm].Spd.Data;
          if (SpdIn->Lpddr.Base.ModuleMemoryBusWidth.Bits.PrimaryBusWidth != ExpectedWidth) {
            Status = mrcMixedDimmSystem;
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Mixed PrimaryBusWidth across DRAMs!\n", gErrString);
            return (Status);
          }
        }
      }
    }
  }

  //
  // Get the maximum allowed frequency / refclk
  //
  MrcMcCapabilityPreSpd (MrcData);

  if (DimmCount > 0) {
    Outputs->BurstLength = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4) ? 8 : 4;  // BL in DCLKs
    Outputs->TCRSensitiveHynixDDR4  = FALSE;
    Outputs->TCRSensitiveMicronDDR4 = FALSE;
    //
    // Scan thru each channel to see if it is a valid channel and to get its configuration.
    //
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SPD Dimm timing calculation\n");
    if (mrcSuccess == SpdTimingCalculation (MrcData)) {
      Outputs->EccSupport = TRUE;

      //
      // Count up the number of valid DIMMs.
      //
      ControllerOut = &Outputs->Controller[0];
      for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
        ChannelOut = &ControllerOut->Channel[Channel];
        ChannelOut->DimmCount = 0;
        for (Dimm = 0; Dimm < MAX_DIMMS_IN_CHANNEL; Dimm++) {
          DimmOut = &ChannelOut->Dimm[Dimm];
          if ((DIMM_PRESENT == DimmOut->Status) || (DIMM_DISABLED == DimmOut->Status)) {
            ChannelOut->DimmCount++;
            if ((Outputs->DdrType == MRC_DDR_TYPE_DDR4) && (Outputs->TCRSensitiveHynixDDR4 == FALSE) && (Outputs->TCRSensitiveMicronDDR4 == FALSE)) {
              SpdIn = &Inputs->Controller[0].Channel[Channel].Dimm[Dimm].Spd.Data;
              ManufactureData = &SpdIn->Ddr4.ManufactureInfo;
              if ((ManufactureData->DramIdCode.Data == 0xAD80) ||
                  (ManufactureData->ModuleId.IdCode.Data == 0xAD80)) { // Hynix
                DateCode = (ManufactureData->ModuleId.Date.Year << 8) | ManufactureData->ModuleId.Date.Week;
                if (DateCode < 0x1512) {
                  Outputs->TCRSensitiveHynixDDR4 = TRUE;
                }
              }
              else if ((ManufactureData->DramIdCode.Data == 0x2C80) ||
                       (ManufactureData->ModuleId.IdCode.Data == 0x2C80)) { // Micron
                DensityIndex = SpdIn->Ddr4.Base.SdramDensityAndBanks.Bits.Density;
                SdramWidthIndex = SpdIn->Ddr4.Base.ModuleOrganization.Bits.SdramDeviceWidth;
                if ((DensityIndex == MRC_SPD_SDRAM_DENSITY_4Gb) &&
                    (SdramWidthIndex == MRC_SPD_SDRAM_DEVICE_WIDTH_8)) { // DRAM Density = 4Gb and DRAM Width = x8
                  DimmPartNumber = ManufactureData->ModulePartNumber.ModulePartNumber[15];
                  if (DimmPartNumber == 0x41) { // DIMM Part# Byte[15] = A-Die
                    Outputs->TCRSensitiveMicronDDR4 = TRUE;
                  }
                }
              }
            }
          }
          if (DIMM_PRESENT == DimmOut->Status) {
#if (MAX_RANK_IN_CHANNEL > 8)
#error The next switch statement and ValidRankBitMask needs updated to support additional ranks.
#endif
            switch (DimmOut->RankInDimm) {
              case 1:
                ValidRankBitMask = 1;
                break;
#if (MAX_RANK_IN_DIMM > 1)

              case 2:
                ValidRankBitMask = 3;
                break;
#endif
#if (MAX_RANK_IN_DIMM > 2)

              case 3:
                ValidRankBitMask = 7;
                break;
#endif
#if (MAX_RANK_IN_DIMM > 3)

              case 4:
                ValidRankBitMask = 15;
                break;
#endif

              default:
                ValidRankBitMask = 0;
                break;
            }

            ChannelOut->ValidRankBitMask |= ValidRankBitMask << (Dimm * MAX_RANK_IN_DIMM);
            if (Outputs->EnhancedChannelMode && (DimmOut->NumLpSysChannel == 1)) {
              ChannelOut->ValidSubChBitMask = 1;
            } else {
              ChannelOut->ValidSubChBitMask = 3; // Keep both bits set for non-ECHM mode
            }

            Outputs->EccSupport  &= DimmOut->EccSupport;
            Outputs->tMAC         = MIN (Outputs->tMAC, DimmOut->tMAC);
          } // DIMM_PRESENT
        } // Dimm

        if ((ChannelOut->DimmCount > 0) && (ChannelOut->ValidRankBitMask > 0)) {
          ControllerOut->ChannelCount++;
          ControllerOut->Channel[Channel].Status = CHANNEL_PRESENT;
        }
      }

      for (Controller = 0; Controller < MAX_CONTROLLERS; Controller++) {
        ControllerOut = &Outputs->Controller[Controller];
        if (ControllerOut->ChannelCount > 0) {
          ControllerOut->Status = CONTROLLER_PRESENT;
          Status                = mrcSuccess;
        }
      }
    }
  }

  if (Status != mrcSuccess) {
    return Status;
  }

  Status = MrcCheckInputParams (MrcData);

  return Status;
}

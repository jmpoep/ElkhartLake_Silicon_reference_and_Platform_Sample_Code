/** @file
  SPD processing header file.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2010 - 2018 Intel Corporation.

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
#ifndef _MrcSpdProcessing_h_
#define _MrcSpdProcessing_h_

#include "MrcTypes.h"
#include "MrcApi.h"
#include "MrcGlobal.h"
#include "MrcCommon.h"
#include "MrcGeneral.h"
#include "MrcDebugPrint.h"

#pragma pack (push, 1)

///
/// Local definitions
///
#define CRC_SEED                  0
#define CRC_XOR_MASK              0x1021
#define TREFIMIN_LPDDR4           3904000   /// Average periodic refresh interval, in picoseconds (3.904 us for LPDDR4)
#define TREFIMIN_DDR4             7800000   /// Average periodic refresh interval, in picoseconds (7.8 us for DDR4)
#define TREFIMULTIPLIER           1000      /// tREFI value defined in XMP 1.3 spec is actually in thousands of MTB units.
#define MRC_tAA_MAX_DDR4          18000000  /// tAA_Max is 18ns for DDR4

#define MRC_FREQUENCY_MTB_OFFSET  1000000
#define MRC_FREQUENCY_FTB_OFFSET  1000

///
/// SPD field definitions
///
#define MRC_SPD_DDR4_SDRAM_TYPE_NUMBER      (0x0C)
#define MRC_SPD_DDR4_CL_SUPPORTED_MASK      (0x3FFFF)
#define MRC_SPD_LPDDR4_SDRAM_TYPE_NUMBER    (0x10)
#define MRC_SPD_LPDDR4X_SDRAM_TYPE_NUMBER   (0x11)
#define MRC_SPD_LPDDR_CL_SUPPORTED_MASK     (0x157DFF)

#define MRC_SPD_RDIMM_TYPE_NUMBER           (0x01)
#define MRC_SPD_UDIMM_TYPE_NUMBER           (0x02)
#define MRC_SPD_SODIMM_TYPE_NUMBER          (0x03)

#define MRC_SPD_DDR4_SDRAM_BANK_4           (0x00)
#define MRC_SPD_DDR4_SDRAM_BANK_8           (0x01)

#define MRC_SPD_DDR4_SDRAM_BANK_GROUPS_0    (0x00)
#define MRC_SPD_DDR4_SDRAM_BANK_GROUPS_2    (0x01)
#define MRC_SPD_DDR4_SDRAM_BANK_GROUPS_4    (0x02)

#define MRC_SPD_SDRAM_DENSITY_256Mb         (0x00)
#define MRC_SPD_SDRAM_DENSITY_512Mb         (0x01)
#define MRC_SPD_SDRAM_DENSITY_1Gb           (0x02)
#define MRC_SPD_SDRAM_DENSITY_2Gb           (0x03)
#define MRC_SPD_SDRAM_DENSITY_4Gb           (0x04)
#define MRC_SPD_SDRAM_DENSITY_8Gb           (0x05)
#define MRC_SPD_SDRAM_DENSITY_16Gb          (0x06)
#define MRC_SPD_SDRAM_DENSITY_32Gb          (0x07)

#define MRC_SPD_LPDDR_SDRAM_DENSITY_12Gb    (0x08)
#define MRC_SPD_LPDDR_SDRAM_DENSITY_24Gb    (0x09)
#define MRC_SPD_LPDDR_SDRAM_DENSITY_3Gb     (0x0A)
#define MRC_SPD_LPDDR_SDRAM_DENSITY_6Gb     (0x0B)
#define MRC_SPD_LPDDR_SDRAM_DENSITY_18Gb    (0x0C)

#define MRC_SPD_SDRAM_ROW_12                (0x00)
#define MRC_SPD_SDRAM_ROW_13                (0x01)
#define MRC_SPD_SDRAM_ROW_14                (0x02)
#define MRC_SPD_SDRAM_ROW_15                (0x03)
#define MRC_SPD_SDRAM_ROW_16                (0x04)
#define MRC_SPD_SDRAM_ROW_17                (0x05)

#define MRC_SPD_SDRAM_COLUMN_9              (0x00)
#define MRC_SPD_SDRAM_COLUMN_10             (0x01)
#define MRC_SPD_SDRAM_COLUMN_11             (0x02)
#define MRC_SPD_SDRAM_COLUMN_12             (0x03)

#define MRC_SPD_SDRAM_DEVICE_WIDTH_4        (0x00)
#define MRC_SPD_SDRAM_DEVICE_WIDTH_8        (0x01)
#define MRC_SPD_SDRAM_DEVICE_WIDTH_16       (0x02)
#define MRC_SPD_SDRAM_DEVICE_WIDTH_32       (0x03)

#define MRC_SPD_PRIMARY_BUS_WIDTH_8         (0x00)
#define MRC_SPD_PRIMARY_BUS_WIDTH_16        (0x01)
#define MRC_SPD_PRIMARY_BUS_WIDTH_32        (0x02)
#define MRC_SPD_PRIMARY_BUS_WIDTH_64        (0x03)

#define MRC_SPD_BUS_WIDTH_EXTENSION_0       (0x00)
#define MRC_SPD_BUS_WIDTH_EXTENSION_8       (0x01)

#define MRC_SPD_CH_PER_SDRAM_PKG_1          (0x0)
#define MRC_SPD_CH_PER_SDRAM_PKG_2          (0x1)
#define MRC_SPD_CH_PER_SDRAM_PKG_4          (0x2)
#define MRC_SPD_CH_PER_SDRAM_PKG_RSVD       (0x3)

#define MRC_SPD_CL_SUPPORTED_MASK           (0x7FFF)

#define XMP_VDD_INTEGER                     (1000)
#define XMP_VDD_INCREMENT                   (50)
#define XMP_VDD_INCREMENT_2                 (10)
#define XMP_VDD_MIN_POSSIBLE                (1000)
#define XMP_VDD_MAX_POSSIBLE                (2000)

#define MRC_TMAC_UNTESTED                   (0x0)
#define MRC_TMAC_700K                       (0x1)
#define MRC_TMAC_600K                       (0x2)
#define MRC_TMAC_500K                       (0x3)
#define MRC_TMAC_400K                       (0x4)
#define MRC_TMAC_300K                       (0x5)
#define MRC_TMAC_200K                       (0x6)
#define MRC_TMAC_UNLIMITED                  (0x8)

#define MRC_SPD_REF_RAW_CARD_SIZE           (5)
#define MRC_SPD_REF_RAW_CARD_EXT_OFFSET     (7)

#define XMP_ID_STRING                       (0x4A0C)

extern const UINT32 SdramCapacityTable[];
extern const MrcSpdOffsetTable MrcSpdDdr4Table[9];
extern const MrcSpdOffsetTable MrcSpdLpddrTable[6];

typedef struct {
  UINT32        tCK;
  MrcFrequency  Frequency;
  UINT8         FreqFlag;  // Bitmask of flags from MrcFreqFlag enum
} TRangeTable;

typedef struct {
  BOOLEAN (*mrc_task) (MrcParameters * const MrcData);
} SpdTimeCallTable;

typedef struct {
  BOOLEAN (*mrc_task) (MrcParameters * const MrcData, const MrcSpd * const Spd, MrcDimmOut * const DimmOut);
} SpdRecogCallTable;

typedef union {
  struct {
    UINT8 Vdd1_10 : 1;
    UINT8 Vdd1_20 : 1;
    UINT8 Vdd1_25 : 1;
    UINT8 Vdd1_35 : 1;
    UINT8 Vdd1_50 : 1;
    UINT8         : 3;
  } Bits;
  UINT8 Data;
} SpdVddFlag;

/**
    Calculate the memory clock value from the current memory frequency.

    @param[in, out] MrcData     - Pointer to MrcData data structure.
    @param[in]      Frequency   - Memory frequency to convert.

    @retval Returns the tCK value in [fs] for the given frequency.
**/
extern
UINT32
ConvertFreq2Clock (
  IN OUT MrcParameters *const MrcData,
  IN     const MrcFrequency   Frequency
);

/**
  Calculate the CRC16 of the provided SPD data. CRC16 formula is the same
  one that is used for calculating the CRC16 stored at SPD bytes 126-127.
  This can be used to detect DIMM change.

  @param[in]  Buffer - Pointer to the start of the data.
  @param[in]  Size   - Amount of data in the buffer, in bytes.
  @param[out] Crc    - Pointer to location to write the calculated CRC16 value.

  @retval Returns TRUE.
**/
extern
BOOLEAN
GetDimmCrc (
  IN  const UINT8 *const Buffer,
  IN  const UINT32       Size,
  OUT UINT16      *const Crc
  );

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
  );

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
  );

/**
  Process the SPD information for all DIMMs on all channels.

  @param[in, out] MrcData - The MRC "global data".

  @retval mrcSuccess on success, mrcDimmNotExist if no DIMMs found.
**/
extern
MrcStatus
MrcSpdProcessing (
  IN OUT MrcParameters *const MrcData
  );

#pragma pack (pop)
#endif // _MrcSpdProcessing_h_

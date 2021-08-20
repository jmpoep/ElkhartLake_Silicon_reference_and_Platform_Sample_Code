/** @file
  This file implements functions for setting up the Pattern
  Generators for CPGC 2.0.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2018 Intel Corporation.

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
#ifndef _CPGC_20_PATTERNS_H_
#define _CPGC_20_PATTERNS_H_
///
/// Defintions
///
#define CPGC_20_NUM_DATA_PGS     (4)
#define CPGC_20_NUM_DPAT_EXTBUF (16)

#define CADB_20_NUM_DSEL_UNISEQ (3)

/*
#define CPGC_15_MAX_CHUNKS    (8)
#define CPGC_15_NUM_CMD_PGS   (2)
#define CPGC_15_MAX_PGS       (CPGC_15_NUM_CMD_PGS + CPGC_15_NUM_DATA_PGS)
*/
/**
CADB Select Override Mapping:

CADB_BUF bit    CADB_BUF.field bit    DDR4            LPDDR4 Select   LPDDR4 DeSelect
=====================================================================================
[41]            CADB_BUF.CA [23]                      CA_4th[5]
[40]            CADB_BUF.CA [22]      ACT_n           CA_4th[4]
[39]            CADB_BUF.CA [21]      BG1             CA_4th[3]
[38]            CADB_BUF.CA [20]      BG0             CA_4th[2]
[37]            CADB_BUF.CA [19]      BA1             CA_4th[1]
[36]            CADB_BUF.CA [18]      BA0             CA_4th[0]
[35]            CADB_BUF.CA [17]                      CA_3rd[5]
[34]            CADB_BUF.CA [16]      MA[16]/RAS_n    CA_3rd[4]
[33]            CADB_BUF.CA [15]      MA[15]/CAS_n    CA_3rd[3]
[32]            CADB_BUF.CA [14]      MA[14]/WE_n     CA_3rd[2]
[31]            CADB_BUF.CA [13]      MA[13]          CA_3rd[1]
[30]            CADB_BUF.CA [12]      MA[12]          CA_3rd[0]
[29]            CADB_BUF.CA [11]      MA[11]          CA_2nd[5]
[28]            CADB_BUF.CA [10]      MA[10]          CA_2nd[4]
[27]            CADB_BUF.CA [9]       MA[9]           CA_2nd[3]
[26]            CADB_BUF.CA [8]       MA[8]           CA_2nd[2]
[25]            CADB_BUF.CA [7]       MA[7]           CA_2nd[1]
[24]            CADB_BUF.CA [6]       MA[6]           CA_2nd[0]
[23]            CADB_BUF.CA [5]       MA[5]           CA_1st[5]       CA[5]_subch0
[22]            CADB_BUF.CA [4]       MA[4]           CA_1st[4]       CA[4]_subch0
[21]            CADB_BUF.CA [3]       MA[3]           CA_1st[3]       CA[3]_subch0
[20]            CADB_BUF.CA [2]       MA[2]           CA_1st[2]       CA[2]_subch0
[19]            CADB_BUF.CA [1]       MA[1]           CA_1st[1]       CA[1]_subch0
[18]            CADB_BUF.CA [0]       MA[0]           CA_1st[0]       CA[0]_subch0
[17]            CADB_BUF.PAR          PAR
[16]            CADB_BUF.VAL          Set for all the non-tri-stated CADB chunks!
[15]
[14]            CADB_BUF.CKE [3]      CKE[3]                          CKE[1]_subch1
[13]            CADB_BUF.CKE [2]      CKE[2]                          CKE[0]_subch1
[12]            CADB_BUF.CKE [1]      CKE[1]                          CKE[1]_subch0
[11]            CADB_BUF.CKE [0]      CKE[0]                          CKE[0]_subch0
[10]            CADB_BUF.ODT [3]      ODT[3]                          CS[3]_subch1
[9]             CADB_BUF.ODT [2]      ODT[2]                          CS[2]_subch1
[8]             CADB_BUF.ODT [1]      ODT[1]                          CS[3]_subch0
[7]             CADB_BUF.ODT [0]      ODT[0]                          CS[2]_subch0
[6]
[5]
[4]
[3]             CADB_BUF.CS [3]       CSb[3]                          CS[1]_subch1
[2]             CADB_BUF.CS [2]       CSb[2]                          CS[0]_subch1
[1]             CADB_BUF.CS [1]       CSb[1]                          CS[1]_subch0
[0]             CADB_BUF.CS [0]       CSb[0]                          CS[0]_subch0
**/
///CADB Mapping Defines
/// DDR4
#define CADB_DDR4_MA_0_16_OFF (18)
#define CADB_DDR4_MA_0_16_MSK (0x1FFFF)
#define CADB_DDR4_WE_N_OFF    (32)
#define CADB_DDR4_CAS_N_OFF   (33)
#define CADB_DDR4_RAS_N_OFF   (34)
#define CADB_DDR4_BA_OFF      (36)
#define CADB_DDR4_BA_MSK      (0x3)
#define CADB_DDR4_BG_OFF      (38)
#define CADB_DDR4_BG_MSK      (0x3)
#define CADB_DDR4_ACT_N_OFF   (40)
#define CADB_DDR4_PAR_OFF     (17)
#define CADB_DDR4_CKE_OFF     (11)
#define CADB_DDR4_CS_B_OFF    (0)
#define CADB_DDR4_ODT_OFF     (7)
#define CADB_DDR4_CKE_CTL_MSK (0xF)
/// LPDDR4
#define CADB_LPDDR4_CA_OFF          (18)
#define CADB_LPDDR4_CA_MSK          (0x3F)
#define CADB_LPDDR4_CS_0_1_SC0_OFF  (0)
#define CADB_LPDDR4_CS_0_1_SC1_OFF  (2)
#define CADB_LPDDR4_CS_2_3_SC0_OFF  (7)
#define CADB_LPDDR4_CS_2_3_SC1_OFF  (9)
#define CADB_LPDDR4_CKE_SC0_OFF     (11)
#define CADB_LPDDR4_CKE_SC1_OFF     (13)
#define CADB_LPDDR4_CS_CKE_MSK      (0x3)

#define CADB_BUF_VAL_OFF            (16)

// Polynomial tap values for address PRBS generation
#define CPGC_PRBS_2   (0x0003)
#define CPGC_PRBS_3   (0x0006)
#define CPGC_PRBS_4   (0x000C)
#define CPGC_PRBS_5   (0x0014)
#define CPGC_PRBS_6   (0x0036)
#define CPGC_PRBS_7   (0x0072)
#define CPGC_PRBS_8   (0x00B2)
#define CPGC_PRBS_9   (0x0152)
#define CPGC_PRBS_10  (0x035A)
#define CPGC_PRBS_11  (0x06E4)
#define CPGC_PRBS_12  (0x0B52)
#define CPGC_PRBS_13  (0x1592)
#define CPGC_PRBS_14  (0x25A4)
#define CPGC_PRBS_15  (0x49A4)
#define CPGC_PRBS_16  (0x9924)
#define CPGC_PRBS_17  (0x12924)
#define CPGC_PRBS_18  (0x25694)

typedef enum {
  Cpgc20InvertMode,
  Cpgc20DcMode,
  Cpgc20InvertDcModeMax,
  Cpgc20InvertDcModeDelim = INT32_MAX
} CPGC20_INVERT_DC_MODE;

typedef enum {
  MrcLfsr8,
  MrcLfsr15,
  MrcLfsr31,
  MrcLfsr23b, //x23 + x18
  MrcLfsr7,
  MrcLfsr16,
  MrcLfsr23a, //x23 + x21 + x18 + x15 + x7 + x2
  MrcLfsr32,
  MrcLfsrTypeMax
} MRC_PG_LFSR_TYPE;

/// CPGC/CADB Mux Control Mode
typedef enum {
  MrcPgMuxLmn,
  MrcPgMuxPatBuffer,
  MrcPgMuxLfsr,
  MrcPgMuxNa2,
  MrcPgMuxMax
} MRC_PG_UNISEQ_TYPE;

/**
  This function configures the rotation rate for the PG (per MrcIntData->ChSubChMaskEnable).
  If the RotateRate is 0, the hardware rotation is disabled.

  @param[in]  MrcData       - Pointer to MRC global data.
  @param[in]  RotateRate    - Log2 count of how many transactions (SubSequence or Cacheline) before we rotate the PG.

  @retval Nothing.
**/
void
Cpgc20ConfigPgRotation (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                RotateRate
  );

/**
  This function takes in a generic mapping of CS, CKE, ODT, and Command/Address
  signals and converts them to the expected layout of the hardware engine.

  @param[in]  MrcData - Pointer to global data structure.
  @param[in]  CmdAddr - Union of Command/Address signals per each supported memory technology
  @param[in]  Cke     - Bit Mask of Clock Enable signals per sub-channel.
  @param[in]  Cs      - Bit Mask of Chip Select signals per sub-channel.
  @param[in]  Odt     - Bit Mask of On Die Termination signals.

  @retval - MrcStatus: mrcSuccess if successful, otherwise an error status.
**/
MrcStatus
CpgcConvertDdrToCadb (
  IN  MrcParameters     *const  MrcData,
  IN  MRC_CA_MAP_TYPE   *const  CmdAddr,
  IN  UINT8                     Cke[2],
  IN  UINT8                     Cs[2],
  IN  UINT8                     Odt,
  OUT UINT64_STRUCT     *const  CadbVal
  );

/**
  This function converts the data/command channel masks to the CPGC encoding.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  DataChMask  - Bit mask of Channels to select: 0x1 - Channel 0 Enhanced Channel 0 & 1, 0x2 - Channel 1 Enhanced Channel 0 & 1.
  @param[in]  CmdChMask   - Bit mask of channels to select: 0x1 - Channel 0, 0x2 - Channel 1.
  @param[in]  SubChMask   - Bit mask of SubChannels to select: 0x1 - Subchannel 0, 0x2 - Subchannel 1, rest - all Subchannels

  @retval - MrcStatus: mrcSuccess if ChSubChMaskEnable are non-zero, mrcFail if ChSubChMaskEnable = 0.
**/
MrcStatus
Cpgc20SelectEngines (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                DataChMask,
  IN  UINT32                CmdChMask,
  IN  UINT32                SubChMask
  );

/**
  This function sets up the CPGC data pattern configuration per MrcIntData->ChSubChMaskEnable.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  CmdPat      - [0: PatWrRd (Standard Write/Read Loopback),
                            1: PatWr (Write Only),
                            2: PatRd (Read Only),
                            3: PatRdWrTA (ReadWrite Turnarounds),
                            4: PatWrRdTA (WriteRead Turnarounds),
                            5: PatODTTA (ODT Turnaround]
  @param[in]  PatCtlPtr   - Structure that stores start, Stop, IncRate and Dqpat for pattern.

  @retval - MrcStatus: mrcSuccess if ChSubChMaskEnable are non-zero, mrcFail if ChSubChMaskEnable = 0.
**/
MrcStatus
Cpgc20DPatCfg (
  IN  MrcParameters *const   MrcData,
  IN  const UINT8            CmdPat,
  IN  MRC_PATTERN_CTL *const PatCtlPtr
  );

/**
  This function sets up the CPGC LFSR configuration per MrcIntData->ChSubChMaskEnable.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  LfsrPoly    - LFSR Polynominal applied to all UNISEQs
  @param[in]  LaneRotate  - Lane Rotate Rate, should be log2(CPGC2_BASE_REPEATS.Base_Repeats+1) for BasicVA

  @retval - MrcStatus: mrcSuccess if ChSubChMaskEnable are non-zero, mrcFail if ChSubChMaskEnable = 0.
**/
MrcStatus
Cpgc20LfsrCfg (
  IN  MrcParameters *const   MrcData,
  IN  MRC_PG_LFSR_TYPE       LfsrPoly,
  IN  UINT8                  LaneRotate
  );

/**
  This function sets up the CPGC LFSR configuration per MrcIntData->ChSubChMaskEnable.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  Seed        - Seed to program
  @param[in]  Index       - Which UNISEQx to program seed to

  @retval - MrcStatus: mrcSuccess if ChSubChMaskEnable are non-zero, mrcFail if ChSubChMaskEnable = 0.
**/
MrcStatus
Cpgc20LfsrSeed (
  IN  MrcParameters *const   MrcData,
  IN  const UINT32           Seed,
  IN  const UINT8            Index
  );

/**
  This function sets the Pattern Generators' Invert/DC configuration (per MrcIntData->ChSubChMaskEnable).
  The invert mode inverts the selected lanes' values.  The DC mode sets the
  selected lanes to a DC value.

  When rotation is enabled, once the rotation rate is met, the LaneMask is rotated from
  LSb to MSb.  Bit 63 of data is rotated into bit 0 of ECC, and bit 7 of ECC is rotated
  to Bit 0 of data.

  @param[in]  MrcData             - Pointer to global MRC data.
  @param[in]  Mode                - Selects Invert or DC mode.
  @param[in]  DcPolarity          - 0 = DC low. 1 = DC high.
  @param[in]  EnableRotate        - Enables the rotation feature for the Bit Enable Masks of ECC and Data.
  @param[in]  RotateRateExponent  - Programs the counter to rotate every 2^(RotateRateExponenet).
  @param[in]  BytegroupMapping    - Selects between 2 bytes of DPAT pattern generator to be applied to each DQ byte group.  MSB is the ECC byte group.

  @retval Nothing.
**/
void
Cpgc20SetPgInvDcCfg (
  IN  MrcParameters *const  MrcData,
  IN  CPGC20_INVERT_DC_MODE Mode,
  IN  UINT8                 DcPolarity,
  IN  BOOLEAN               EnableRotate,
  IN  UINT8                 RotateRateExponent,
  IN  UINT16                BytegroupMapping
  );

/**
  This function sets the Pattern Generators' Dpat Buffer Control. Useful for static pattern setup.

  @param[in]  MrcData             - Pointer to global MRC data.
  @param[in]  IncScale            - Exponential/Linear
  @param[in]  IncRate             - Pattern Generator's "lines" advancement rate
  @param[in]  Start               - Lane to start from
  @param[in]  Stop                - Lane to wrap ("stop") on

  @retval Nothing.
**/
void
Cpgc20SetDpatBufCtl (
  IN  MrcParameters *const  MrcData,
  IN  UINT16                IncScale,
  IN  UINT16                IncRate,
  IN  UINT8                 Start,
  IN  UINT8                 Stop
  );

/**
  This function sets the Data and ECC Lane Mask Enables (per MrcIntData->ChSubChMaskEnable).
  If all bits in DataLaneMask and EccLaneMask are 0, then the DC/Invert feature is disabled.

  @param[in]  MrcData       - Pointer to global MRC data.
  @param[in]  DataLaneMask  - Bit-Mask of lanes to enable in this PG.
  @param[in]  EccLaneMask   - Bit-Mask of lanes to enable for ECC in this PG.

  @retval Nothing.
**/
void
Cpgc20SetPgInvDcEn (
  IN  MrcParameters *const  MrcData,
  IN  UINT64                DataLaneMask,
  IN  UINT8                 EccLaneMask
  );

/**
  This function will program the Pattern Buffers in the CADB Pattern Generators for
    the specific Generator/Chunk for all enabled CADB engines (per MrcIntData->ChSubChMaskEnable).
  This function can be used to select what Pattern Buffers to target by passing setting
    NumChunks == ChunkStart.

  @param[in]  MrcData       - Pointer to global MRC Data.
  @param[in]  ChunkStart    - 0-based index of which chunk will receive the pattern.
  @param[in]  NumChunks     - 0-based index of how many chunks to write.  Pattern array must have this many entries.
  @param[in]  Pattern       - Pointer to an array of patterns to program to the selected generator[s].

  @retval - MrcStatus: mrcSuccess if ChSubChMaskEnable are non-zero, mrcFail if ChSubChMaskEnable = 0.
**/
MrcStatus
Cadb20ProgramPatGen (
  IN  MrcParameters     *const  MrcData,
  IN  UINT32                    ChunkStart,
  IN  UINT32                    NumChunks,
  IN  UINT64_STRUCT             Pattern[CADB_20_MAX_CHUNKS]
  );

/**
  This function sets up the CADB DSEL Uniseq configuration per MrcIntData->ChSubChMaskEnable.

  @param[in]  MrcData      - Pointer to global MRC data.
  @param[in]  UniseqMode   - Uniseq mode to program to all UniseqCfg.
  @param[in]  LfsrPolySize - LFSR Polynomial Size to program, note that this only has meaning when UniseqMode = MrcPgMuxLfsr.

  @retval - MrcStatus: mrcSuccess if ChSubChMaskEnable are non-zero, mrcFail if ChSubChMaskEnable = 0.
**/
MrcStatus
Cadb20UniseqCfg (
  IN  MrcParameters *const   MrcData,
  IN  MRC_PG_UNISEQ_TYPE     UniseqMode,
  IN  MRC_PG_LFSR_TYPE       LfsrPolySize
  );

/**
  This function sets up the CADB LFSR configuration per MrcIntData->ChSubChMaskEnable.

  @param[in]  MrcData     - Pointer to global MRC data.
  @param[in]  Seed        - Seed to program
  @param[in]  Index       - Which UNISEQx to program seed to

  @retval - MrcStatus: mrcSuccess if ChSubChMaskEnable are non-zero, mrcFail if ChSubChMaskEnable = 0.
**/
MrcStatus
Cadb20LfsrSeed (
  IN  MrcParameters *const   MrcData,
  IN  const UINT32           Seed,
  IN  const UINT8            Index
  );

#endif  //_CPGC_20_PATTERNS_H_

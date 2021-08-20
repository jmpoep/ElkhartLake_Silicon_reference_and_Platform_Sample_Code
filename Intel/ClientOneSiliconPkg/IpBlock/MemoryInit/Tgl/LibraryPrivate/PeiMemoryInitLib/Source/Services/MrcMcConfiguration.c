/** @file
  The functions in this file implement the memory controller registers that
  are not training specific. After these functions are executed, the
  memory controller will be ready to execute the timing training sequences.

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
//
// Include files
//
#include "MrcMcConfiguration.h"
#include "MrcMaintenance.h"
#include "MrcDdrIoOffsets.h"
#include "MrcMemoryApi.h"
#include "MrcLpddr4.h"
#include "MrcDdr4.h"
#include "MrcCommon.h"
#include "Cpgc20.h"
#include "MrcCpgcOffsets.h"
#include "MrcCpgcApi.h"
#include "MrcDdrIoApi.h"
#include "MrcDdrIoApiInt.h"
#include "MrcChipApi.h"

///
/// Structs and Types
///

/// CCC Enable Mappings.
/// The numbers after the Ccc union define which CCC instance this mapping should be applied.
typedef union {
  union {
    struct {
      UINT16      : 5; ///< Bits 0:4
      UINT16 Clk0 : 2; ///< Bits 5:6 Clock is a 2 bit enable for P & N
      UINT16      : 9; ///< Bits 7:15
    } Ccc04;
    struct {
      UINT16      : 1;  ///< Bit 0
      UINT16 Odt1 : 1;  ///< Bit 1
      UINT16 Cs1  : 1;  ///< Bit 2
      UINT16 Cs0  : 1;  ///< Bit 3
      UINT16 Odt0 : 1;  ///< Bit 4
      UINT16      : 11; ///< Bits 5:15
    } Ccc15;
    struct {
      UINT16      : 10; ///< Bits 0:9
      UINT16 Cke1 : 1;  ///< Bit  10
      UINT16      : 1;  ///< Bit  11
      UINT16 Cke0 : 1;  ///< Bit  12
      UINT16      : 3;  ///< Bits 13:15
    } Ccc26;
    struct {
      UINT16      : 5; ///< Bits 0:4
      UINT16 Clk1 : 2; ///< Bits 5:6 Clock is a 2 bit enable for P & N
      UINT16      : 9; ///< Bits 7:15
    } Ccc37;
  } Ddr4;
  union {
    struct {
      UINT16      : 2; ///< Bits  0:1
      UINT16 Cs1  : 1; ///< Bit   2
      UINT16      : 1; ///< Bit   3
      UINT16 Cs0  : 1; ///< Bit   4
      UINT16 Clk  : 2; ///< Bits  5:6 Clock is a 2 bit enable for P & N
      UINT16 Cke  : 2; ///< Bits  7:8
      UINT16      : 7; ///< Bits  9:15
    } Ccc023467;
    struct {
      UINT16 Cs1  : 1; ///< Bit   0
      UINT16      : 3; ///< Bits  0:3
      UINT16 Cs0  : 1; ///< Bit   4
      UINT16 Clk  : 2; ///< Bits  5:6 Clock is a 2 bit enable for P & N
      UINT16 Cke  : 2; ///< Bits  7:8
      UINT16      : 7; ///< Bits  9:15
    } Ccc15;
  } Lp4;
  union {
    struct {
      UINT16      : 2; ///< Bits  0:1
      UINT16 Cs   : 2; ///< Bits  2:3
      UINT16      : 1; ///< Bit   4
      UINT16 Clk  : 2; ///< Bits  5:6 Clock is a 2 bit enable for P & N
      UINT16 Wck  : 2; ///< Bits  7:8 Clock is a 2 bit enable for P & N
      UINT16      : 7; ///< Bits  9:15
    } Ccc023467;
    struct {
      UINT16 Cs0  : 1; ///< Bits  0
      UINT16      : 2; ///< Bits  1:2
      UINT16 Cs1  : 1; ///< Bit   3
      UINT16      : 1; ///< Bit   4
      UINT16 Clk  : 2; ///< Bits  5:6 Clock is a 2 bit enable for P & N
      UINT16 Wck  : 2; ///< Bits  7:8 Clock is a 2 bit enable for P & N
      UINT16      : 7; ///< Bits  9:15
    } Ccc15;
  } Lp5A;
  union {
    struct {
      UINT16      : 5; ///< Bit   0:4
      UINT16 Clk  : 2; ///< Bits  5:6 Clock is a 2 bit enable for P & N
      UINT16 Wck  : 2; ///< Bits  7:8 Clock is a 2 bit enable for P & N
      UINT16      : 1; ///< Bits  9
      UINT16 Cs   : 2; ///< Bits  10:11
      UINT16      : 4; ///< Bits  12:15
    } Ccc0145;
    struct {
      UINT16      : 5; ///< Bit   0:4
      UINT16 Clk  : 2; ///< Bits  5:6 Clock is a 2 bit enable for P & N
      UINT16 Wck  : 2; ///< Bits  7:8 Clock is a 2 bit enable for P & N
      UINT16 Cs0  : 1; ///< Bits  9
      UINT16      : 1; ///< Bits  10
      UINT16 Cs1  : 1; ///< Bits  11
      UINT16      : 4; ///< Bits  12:15
    } Ccc2367;
  } Lp5D;
  struct {
    UINT16        : 5; ///< Bit   0:4
    UINT16 Clk    : 2; ///< Bits  5:6 Clock is a 2 bit enable for P & N
    UINT16 CkeWck : 2; ///< Bits  7:8 Clock is a 2 bit enable for P & N
    UINT16        : 7; ///< Bits  9:15
  } CccCommon; ///< Clk is common for all technologies.  Cke/Wck are the same across all fubs for Lp4/Lp5.
  UINT16  Data16;
} CCC_TX_EN_TYPE;

/// Defines
#define MRC_NUM_BYTE_GROUPS    (8)

/// CCC Command TxEn Bits
#define MRC_CCC023467_LP4_CA_MSK  (0x1E03)
#define MRC_CCC15_LP4_CA_MSK      (0x1E06)
#define MRC_CCC023467_LP5A_CA_MSK (0x1E13)
#define MRC_CCC15_LP5A_CA_MSK     (0x1E16)
#define MRC_CCC0145_LP5D_CA_MSK   (0x121F)
#define MRC_CCC2367_LP5D_CA_MSK   (0x141F)
#define MRC_CCC04_DDR4_CA_MSK     (0x1E1C)
#define MRC_CCC15_DDR4_CA_MSK     (0x1E01)
#define MRC_CCC26_DDR4_CA_MSK     (0xA0F)
#define MRC_CCC37_DDR4_CA_MSK     (0x1F)
#define PANICV0                   (25)   // mV
#define PANICV1                   (40)   // mV
#define VCCANA_EH                 (1800) // mV
#define MRC_VCCDLL_TARGET         (850)  // mV
#define MRC_VCCBG                 (1000) // mV
#define CA_VOLT_SEL               (0)
#define CLK_VOLT_SEL              (0)

///
/// Global Constants
///
const UINT8 CompParamList[] = { RdOdt, WrDS, WrDSCmd, WrDSCtl, WrDSClk };
const UINT8 ByteStagger[] = {1, 4, 1, 5, 2, 6, 3, 7, 8};  // Increased Byte Stagger for byte0
const UINT8 MinCycleStageDelay[] = {46, 70, 70, 46};      // Avoid corner case

/// 8 banks case (x8 or x16):
/// Logical Bank:         0  1  2  3  4  5  6  7
///                       ----------------------
/// Physical Bank:        0  0  1  1  2  2  3  3
/// Physical Bank Group:  0  1  0  1  0  1  0  1
static MRC_BG_BANK_PAIR Ddr4BankMap[MAX_DDR4_x16_BANKS] = {
  {0,0}, {1,0}, {0,1}, {1,1}, {0,2}, {1,2}, {0,3}, {1,3}
};


/**
  This function calculates the two numbers that get you closest to the slope.

  @param[in]  MrcData - Pointer to global MRC data.
  @param[in]  Slope   - Targeted slope (multiplied by 1000 for integer math)

  @retval Returns the Slope Index to be programmed for VtSlope in terms of the CR.
**/
UINT8
MrcCalcVtSlopeCode (
  IN  MrcParameters * const MrcData,
  IN  const UINT16 Slope
  )
{
  static const INT16 Coding[] = {0, -250, -125, -62, 500, 250, 125, 62}; // 0: 0, 1: -1/4, 2: -1/8, 3: -1/16, 4: +1/2, 5: +1/4, 6: +1/8, 7: +1/16
  INT16       Error;
  INT16       BestError;
  UINT8       BestI;
  UINT8       BestJ;
  UINT8       i;
  UINT8       j;

  BestError = 1000;
  BestI     = 0;
  BestJ     = 0;
  for (i = 0; i < (sizeof (Coding) / sizeof (Coding[0])); i++) {
    for (j = 0; j < (sizeof (Coding) / sizeof (Coding[0])); j++) {
      Error = Slope - (Coding[i] + Coding[j]);
      if (Error < 0) {
        Error = -Error;
      }

      if (BestError > Error) {
        BestError = Error;
        BestI     = i;
        BestJ     = j;
      }
    }
  }

  return (BestI << 3) + BestJ;
}

/**
  This function configures the BCLK RFI frequency for each SAGV point.

  @param[in, out] MrcData - MRC global data.

  @retval VOID
**/
VOID
MrcBclkRfiConfiguration (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput          *Inputs;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  UINT32            *BclkRfiFreqInput;
  UINT32              MailboxCommand;
  UINT32              MailboxData;
  UINT32              MailboxStatus;
  UINT32              MinBclkRfiFreq;
  MrcIntOutput        *MrcIntData;
  const MRC_FUNCTION  *MrcCall;


  MrcIntData        = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  MrcCall           = Inputs->Call.Func;
  BclkRfiFreqInput  = &MrcData->Inputs.BclkRfiFreq[MrcIntData->SaGvPoint];

  // Configure BCLK RFI frequency if needed for this SAGV point
  if (*BclkRfiFreqInput != 0) {
    // Get Min BCLK RFI range
    MailboxCommand = CPU_MAILBOX_BCLK_CONFIG_CMD |
                    (CPU_MAILBOX_BCLK_CONFIG_READ_BCLK_RFI_RANGE_SUBCOMMAND << CPU_MAILBOX_CMD_PARAM_1_OFFSET);
    MrcCall->MrcCpuMailboxRead (MAILBOX_TYPE_PCODE, MailboxCommand, &MailboxData, &MailboxStatus);
    if (MailboxStatus != PCODE_MAILBOX_CC_SUCCESS) {
      MinBclkRfiFreq = BCLK_DEFAULT;
    } else {
      // Mailbox format is in 7.3 MHz, need to convert to Hz.
      // 1,000,000 / (2^3) = 125,000
      MinBclkRfiFreq = (MailboxData & CPU_MAILBOX_BCLK_CONFIG_READ_BCLK_RFI_RANGE_MIN_MASK) * BCLK_RFI_FREQ_CONVERSION;
    }
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "CPU_MAILBOX_BCLK_CONFIG_CMD %s. MailboxStatus = %Xh\n",
      (MailboxStatus == PCODE_MAILBOX_CC_SUCCESS) ? "success" : "failed",
      MailboxStatus
      );

    // Verify BCLK RFI input range
    *BclkRfiFreqInput = RANGE(*BclkRfiFreqInput, MinBclkRfiFreq, BCLK_DEFAULT);

    // Update BCLK RFI frequency
    MailboxCommand = CPU_MAILBOX_BCLK_CONFIG_CMD |
                    (CPU_MAILBOX_BCLK_CONFIG_SET_BCLK_RFI_FREQ_SUBCOMMAND << CPU_MAILBOX_CMD_PARAM_1_OFFSET) |
                    (MrcIntData->SaGvPoint << CPU_MAILBOX_CMD_PARAM_2_OFFSET);
    // Mailbox format is in 7.3 Mhz, BclkRfiFreq is in Hz.
    // Mailbox format = BclkRfiFreq * (2^3) / 1,000,000.
    // (2^3)/1,000,000 = 1/125,000
    MailboxData = *BclkRfiFreqInput / BCLK_RFI_FREQ_CONVERSION;
    MrcCall->MrcCpuMailboxWrite (MAILBOX_TYPE_PCODE, MailboxCommand, MailboxData, &MailboxStatus);
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "CPU_MAILBOX_BCLK_CONFIG_SET_BCLK_RFI_FREQ_SUBCOMMAND %s. MailboxStatus = %Xh\n",
      (MailboxStatus == PCODE_MAILBOX_CC_SUCCESS) ? "success" : "failed",
      MailboxStatus
      );
  }
}

/**
  This function locks the DDR frequency requested from SPD or User.
  It will update the frequency related members in the output structure.

  @param[in, out] MrcData - MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcFrequencyLock (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput          *Inputs;
  MrcOutput         *Outputs;
  MrcDebug          *Debug;
  MrcChannelOut     *ChannelOut;
  MrcStatus         Status;
  MrcProfile        Profile;
  UINT32            Channel;
  UINT32            Controller;
  MrcIntOutput      *MrcIntData;

  MrcIntData        = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  Profile           = Inputs->MemoryProfile;
  // Make sure tCL-tCWL <= 4
  // This is needed to support ODT properly for 2DPC case
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (MrcData, Controller, (UINT8) Channel)) {
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        if (ChannelOut->DimmCount == 2) {
          if ((ChannelOut->Timing[Profile].tCL - ChannelOut->Timing[Profile].tCWL) > 4) {
            ChannelOut->Timing[Profile].tCWL = ChannelOut->Timing[Profile].tCL - 4;
            MRC_DEBUG_MSG (
              Debug,
              MSG_LEVEL_NOTE,
              "(tCL-tCWL) > 4, Mc%u.Ch%u - tCWL has been updated to %u\n",
              Controller,
              Channel,
              ChannelOut->Timing[Profile].tCWL
              );
          }
        }
      }
    }
  }

  // For LPDDR4/5, we need to do the first lock at the low frequency for ECT flow.
  // If we are disabling ECT or frequency switching, we need to lock at the intended frequency.
  if ((Outputs->Lpddr) &&
      (Inputs->LpFreqSwitch == TRUE) &&
      (Inputs->TrainingEnables.ECT == 1)) {
    Outputs->Frequency = f1067;
    MRC_DEBUG_MSG (
      Debug,
      MSG_LEVEL_NOTE,
      "Locking at low(%d) first.  Will switch to high(%d) after ECT\n",
      Outputs->Frequency,
      Outputs->HighFrequency
      );
  }

  // Configure BCLK RFI frequency
  MrcBclkRfiConfiguration(MrcData);

  // We don't always use MrcFrequencySwitch because of LPDDR4 Self-Refresh is command based.
  // On first execution of the frequency, Command has not been training and Self-Refresh may fail.
  if ((MrcData->Inputs.SaGv != MrcSaGvEnabled) || (MrcIntData->SaGvPoint == MrcSaGvPoint1)) {
    Status = McFrequencySet (MrcData, MRC_PRINTS_ON);
  } else {
    Status = MrcFrequencySwitch (MrcData, Outputs->Frequency, MRC_PRINTS_ON);
  }
  if (Status != mrcSuccess) {
    return Status;
  }
  MrcInternalCheckPoint (MrcData, OemFrequencySetDone, NULL);

  // Save MRC Version into CR
  MrcSetMrcVersion (MrcData);

  return Status;
}

/**
  This function initializes the Memory Controller: Scheduler, Timings, Address Decode,
  Odt Control, and refresh settings.

  @param[in, out] MrcData - MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status.
**/
MrcStatus
MrcMcConfiguration (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcOutput *Outputs;
  MrcDebug  *Debug;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Timing Config\n");
  MrcTimingConfiguration (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Refresh Config\n");
  MrcRefreshConfiguration (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Scheduler parameters\n");
  MrcSchedulerParametersConfig (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Address Decoding Config\n");
  MrcAdConfiguration (MrcData);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Maintenance Configuration\n");
  MrcMaintenanceConfig (MrcData);

  return mrcSuccess;
}

/**
  This function initializes memory subsystem registers that are not specific to MC or DDRIO.

  @param[in, out] MrcData - Pointer to the global MRC data.

  @retval MrcStatus - mrcSuccess if successful or an error status.
**/
MrcStatus
MrcMemorySsInit (
  IN OUT  MrcParameters *const MrcData
  )
{
  UINT32                  Offset;
  CMF_GLOBAL_CFG_1_STRUCT CmfGlobalCfg1;

  // Clear CMF_GLOBAL_CFG.FORCE_ISM_ACTIVE: MCHBAR + 0x6428,  bit [0]
  Offset = CMF_GLOBAL_CFG_1_REG;
  CmfGlobalCfg1.Data = MrcReadCR (MrcData, Offset);
  CmfGlobalCfg1.Bits.FORCE_ISM_ACTIVE = 0;
  MrcWriteCR (MrcData, Offset, CmfGlobalCfg1.Data);

  ControllerZoneConfiguration (MrcData);

  return mrcSuccess;
}

/**
  This function initializes the following type of ddrio registers.

  @param[in, out] MrcData - MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status.
**/
MrcStatus
MrcDdrioCrRestore (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcStatus         Status;

  UINT32 i;

  static UINT32 const AddUnder3000 [] = {DDRVREF_CR_DDRRCOMPDATA_REG, DDRPHY_COMP_CR_DDRCOMPDATA_REG, DDRVSSHIAFEA_CR_DDRRCOMPDATA_REG, DDRPHY_COMP_CR_DDRCRVSXHICOMPDATA_REG,
                                         DDRPHY_COMP_CR_DDRCRCOMPTEMP_REG, DDRVSSHIAFEA_CR_DDRCRVSSHICOMPOFFSET_REG, DDRPHY_COMP_CR_DDRCRCLKCOMP_REG, DDRPHY_COMP_CR_DDRCRCTLCOMP_REG,
                                         DDRPHY_COMP_CR_DDRCRDATACOMPVTT_REG, DDRPHY_COMP_CR_DDRCRCOMPDVFSRCOMP_REG, DDRPHY_COMP_CR_VCCDLLCOMPDATACCC_REG, MCMISCS_DDRWCKCONTROL_REG,
                                         DDRPHY_COMP_CR_VSXHIFFCOMPREF0_REG, DDRPHY_COMP_CR_VSXHIFFCOMPREF1_REG, DDRPHY_COMP_CR_DDRCRCOMPOVR0_REG, DDRPHY_COMP_CR_DDRCRCOMPOVR1_REG,
                                         DDRPHY_COMP_CR_DDRCRCACOMP_REG};

  static UINT32 const FllRegs [] = {FLL_DYNAMIC_CFG_REG_REG, FLL_EXTIP_STAT_REG_REG, FLL_DIAG_STAT_REG_REG, FLL_DIAG_STAT_1_REG_REG, FLL_DIAG_STAT_2_REG_REG, FLL_DEBUG_CFG_REG_REG};

  static UINT32 const MulticastAddresses [] = {DDRVTT_CR_DDRCRVTTCOMPOFFSET2_REG, DDRVTT_CR_DDRCRVTTCOMPOFFSET_REG, CCC_CR_DDRCRCLKCOMP_REG, CCC_CR_DDRCRCACOMP_REG,
                                               CCC_CR_DDRCRCTLCACOMPOFFSET_REG, DATA_CR_DATACOMPVTT_REG, DDRVCCDLL_CR_DDRCRVCCDLLCOMPDLL_REG, DLLDDR_CR_DDRCRVCCDLLCOMPDLL_REG,
                                               DDRVCCDLL_CR_DDRCRVCCDLLVOLTAGES_REG, CCC_CR_DDRCRCCCPERBITDESKEWPRISENFALL_REG, CCC_CR_DDRCRCCCPERBITDESKEWPFALLNRISE_REG,
                                               DATA_CR_DCCLANETARGET_REG, DATA_CR_DCCPILUT0_REG, DATA_CR_DCCPILUT1_REG, DATA_CR_DCCPILUT2_REG, DATA_CR_DCCPILUT3_REG,
                                               CCC_CR_DDRCRPERBITTCO0_REG, CCC_CR_DDRCRPERBITTCO1_REG, CCC_CR_DDRCRPERBITTCO2_REG, CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG,
                                               DLLDDR_CR_PITUNE_REG, DLLDDR_CR_DDRCRVCCDLLCOMPOFFSET_REG, DATA_CR_DDRCRDATACONTROL2_REG, DATA_CR_DDRCRWRRETRAINRANK0_REG,
                                               DATA_CR_DDRCRWRRETRAINRANK1_REG, DATA_CR_DDRCRWRRETRAINRANK2_REG, DATA_CR_DDRCRWRRETRAINRANK3_REG};

  static UINT32 const MulticastReadModifyWrite[] = {CCC_CR_DDRCRCCCPICODING0_REG, CCC_CR_DDRCRCCCPICODING1_REG, DATA_CR_TXCONTROL0RANK0_REG, DATA_CR_TXCONTROL0RANK1_REG,
                                                    DATA_CR_TXCONTROL0RANK2_REG, DATA_CR_TXCONTROL0RANK3_REG};

  static UINT32 const ReadModifyWrite[] = {CH0CCC_CR_DDRCRCCCPICODING0_REG, CH0CCC_CR_DDRCRCCCPICODING1_REG, DATA0CH0_CR_TXCONTROL0RANK0_REG, DATA0CH0_CR_TXCONTROL0RANK1_REG,
                                            DATA0CH0_CR_TXCONTROL0RANK2_REG, DATA0CH0_CR_TXCONTROL0RANK3_REG};
  static UINT32 const CompRmw[] = {DDRPHY_COMP_CR_DDRCRCOMPCTL0_REG, DDRPHY_COMP_CR_DDRCRCOMPCTL1_REG, DDRPHY_COMP_CR_DDRCRCOMPCTL2_REG, DDRPHY_COMP_CR_DDRCRCOMPCTL3_REG};

  Status = mrcSuccess;

  for (i = 0; i < ARRAY_COUNT (AddUnder3000); i++) {
    MrcWriteCR (MrcData, AddUnder3000[i], 0);
  }

  for (i = 0; i < ARRAY_COUNT (MulticastAddresses); i++) {
    MrcWriteCrMulticast (MrcData, MulticastAddresses[i], 0);
  }

  for (i = 0; i < ARRAY_COUNT (MulticastReadModifyWrite); i++) {
    MrcWriteCrMulticast (MrcData, MulticastReadModifyWrite[i], MrcReadCR (MrcData, ReadModifyWrite[i]));
  }

  // Do DdrCrCompCtl0-3
  for (i = 0; i < ARRAY_COUNT (CompRmw); i++) {
    MrcWriteCR (MrcData, CompRmw[i], MrcReadCR (MrcData, CompRmw[i]));
  }

  for (i = 0; i < 29; i = i + 4) {
    MrcWriteCrMulticast (MrcData, (DATA_CR_DDRDATADQRANK0LANE0_REG + i), MrcReadCR (MrcData, (DATA0CH0_CR_DDRDATADQRANK0LANE0_REG + i)));
    MrcWriteCrMulticast (MrcData, (DATA_CR_DDRDATADQRANK1LANE0_REG + i), MrcReadCR (MrcData, (DATA0CH0_CR_DDRDATADQRANK1LANE0_REG + i)));
    MrcWriteCrMulticast (MrcData, (DATA_CR_DDRDATADQRANK2LANE0_REG + i), MrcReadCR (MrcData, (DATA0CH0_CR_DDRDATADQRANK2LANE0_REG + i)));
    MrcWriteCrMulticast (MrcData, (DATA_CR_DDRDATADQRANK3LANE0_REG + i), MrcReadCR (MrcData, (DATA0CH0_CR_DDRDATADQRANK3LANE0_REG + i)));
  }

  for (i= 0; i < ARRAY_COUNT (FllRegs); i++) {
    MrcWriteCR (MrcData, FllRegs[i], 0);
  }

  return Status;
}

/**
  This function will setup registers for DCC for PhyInitComplete

  @params[in] MrcData   - Pointer to MRC global data.

  @retval Success
**/
MrcStatus
MrcDccSetup (
  IN  MrcParameters * const MrcData
  )
{
  MrcChannelOut *ChannelOut;
  UINT32 Byte;
  UINT32 Gear2;
  UINT32 ByteEnd;
  UINT32 ByteStart;
  UINT32 Channel;
  UINT32 Controller;
  UINT32 Offset;
  MrcOutput *Outputs;
  MrcInput  *Inputs;
  UINT32    TempVar1;
  UINT32    tPBDMinFm;
  UINT32    DccStepSize;
  UINT32    Index;
  UINT16    Safe;
  UINT8     RankMask;
  DATA0CH0_CR_DCCFSMCONTROL_STRUCT  DccFsmCtl;
  CH0CCC_CR_DCCFSMCONTROL_STRUCT    CCCDccFsmCtl;
  DATA0CH0_CR_DCCCALCCONTROL_STRUCT DccCalCtl;
  CH0CCC_CR_DCCCALCCONTROL_STRUCT   CCCDccCalCtl;

  Outputs = &MrcData->Outputs;
  DccFsmCtl.Data = 0; //Initialize to avoid "potentially uninitialized variables
  DccCalCtl.Data = 0;
  ByteStart = 0;
  ByteEnd = Outputs->SdramCount;
  Inputs = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Gear2 = (Outputs->Gear2) ? 1 : 0;
  Safe = 0;
  tPBDMinFm = 1750; // in fs
  if (Inputs->SafeMode) {
    Safe = 0xFFFF;
  }
  TempVar1 = ((1000000000 / 322581) / 2) * ((Outputs->Qclkps * 1000) / 312500);  // scale to fs
  TempVar1 = MrcLog2 (TempVar1) - 12;
  // Basic DCC register configuration needed for DDRIO Init Complete
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        RankMask = ChannelOut->ValidRankBitMask;
        if (MrcData->Outputs.Lpddr) {
          ByteStart = (MAX_BYTE_IN_LP_CHANNEL * Channel);
          ByteEnd = ByteStart + MAX_BYTE_IN_LP_CHANNEL;
        }
        for (Byte = ByteStart; Byte < ByteEnd; Byte++) {
          Offset = DATA0CH0_CR_DCCFSMCONTROL_REG +
            ((DATA0CH1_CR_DCCFSMCONTROL_REG - DATA0CH0_CR_DCCFSMCONTROL_REG) * Controller) +
            ((DATA1CH0_CR_DCCFSMCONTROL_REG - DATA0CH0_CR_DCCFSMCONTROL_REG) * Byte);
          DccFsmCtl.Data = MrcReadCR (MrcData, Offset);
          DccFsmCtl.Bits.RankEn = (Inputs->TrainingEnables2.DCC) ? RankMask : 0;
          DccFsmCtl.Bits.LaneEn = 0x2FF;
          DccFsmCtl.Bits.RankMap = (RankMask > 3) ? 2 : (RankMask == 2) ? 1 : 0;
          DccFsmCtl.Bits.DccSamples = MIN (TempVar1, 4);
          DccFsmCtl.Bits.EnRankOvrd = Safe ? 0 : 1;
          DccFsmCtl.Bits.WaitForUpdate = 1;
          DccFsmCtl.Bits.rsvd = 1;
          Offset = DATA0CH0_CR_DCCCALCCONTROL_REG +
            ((DATA0CH1_CR_DCCCALCCONTROL_REG - DATA0CH0_CR_DCCCALCCONTROL_REG) * Controller) +
            ((DATA1CH0_CR_DCCCALCCONTROL_REG - DATA0CH0_CR_DCCCALCCONTROL_REG) * Byte);
          DccCalCtl.Data = MrcReadCR (MrcData, Offset);
          DccStepSize = (32000 * Outputs->Qclkps) / 512; // scale to fs, therefore 32000 instead of 32
          DccStepSize = DIVIDEROUND (DccStepSize, tPBDMinFm);
          DccCalCtl.Bits.DccStepSize = DccStepSize;
          DccCalCtl.Bits.LargeChange = 3;
          //Exit for loops by setting conditions to exit
          Byte = ByteEnd;
          Channel = MAX_CHANNEL;
          Controller = MAX_CONTROLLER;
        }
      }
    }
  }
  MrcWriteCrMulticast (MrcData, DATA_CR_DCCFSMCONTROL_REG, DccFsmCtl.Data);
  MrcWriteCrMulticast (MrcData, DATA_CR_DCCCALCCONTROL_REG, DccCalCtl.Data);

  CCCDccCalCtl.Data = MrcReadCR (MrcData, CH0CCC_CR_DCCCALCCONTROL_REG);
  CCCDccCalCtl.Bits.LargeChange = 3;
  MrcWriteCrMulticast (MrcData, CCC_CR_DCCCALCCONTROL_REG, CCCDccCalCtl.Data);

  for (Index = 0; Index < MRC_NUM_CCC_INSTANCES; Index++) {
    Offset = OFFSET_CALC_CH (CH0CCC_CR_DCCFSMCONTROL_REG, CH1CCC_CR_DCCFSMCONTROL_REG, Index);
    CCCDccFsmCtl.Data = 0;
    CCCDccFsmCtl.Bits.DccSamples = DccFsmCtl.Bits.DccSamples;
    CCCDccFsmCtl.Bits.WaitForUpdate = DccFsmCtl.Bits.WaitForUpdate;
    CCCDccFsmCtl.Bits.UpdateTcoComp = 0;
    CCCDccFsmCtl.Bits.LaneEn = (Gear2) ? 0x2FF : 4;
    MrcWriteCR (MrcData, Offset, CCCDccFsmCtl.Data);
  }

  return mrcSuccess;
}

/**
  This function initializes the Memory Controller IO.
  Occupancy and Scrambler registers are initialized.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrIoPreInit (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput          *Inputs;
  MrcIntOutput      *MrcIntData;
  MrcStatus         Status;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcDebug          *Debug;
  MrcDdrType        DdrType;
  INT64             GetSetVal;
  INT64             GetSetEn;
  INT64             GetSetDis;
  UINT32            Offset;
  UINT32            Data;
  UINT32            Controller;
  UINT32            Index;
  UINT32            RefClkPs;
  UINT32            Delay;
  UINT32            McIndex;
  UINT32            ChIndex;
  UINT32            TimerXXClk;
  UINT32            KeepXXClkOn;
  UINT16            TxEn;
  UINT8             Gear1;
  UINT8             IoChNotPop;
  UINT8             RankPresent;
  UINT8             Rank0Present;
  UINT8             Rank1Present;
  UINT8             CccMux;
  UINT8             MaxChannel;
  BOOLEAN           Lpddr;
  BOOLEAN           Lpddr4;
  BOOLEAN           Lpddr5;
  BOOLEAN           Ddr4;
  BOOLEAN           DqPinsInterleaved;
  GSM_GT            Group;
  CCC_TX_EN_TYPE    CccTxEn;
  CH0CCC_CR_DDRCRPINSUSED_STRUCT      CccPinsUsed;
  CH2CCC_CR_DDRCRPINSUSED_P0_STRUCT   CccPinsUsedP0;

  Inputs = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  Debug = &Outputs->Debug;
  MrcIntData = ((MrcIntOutput *) (MrcData->IntOutputs.Internal));
  Status = mrcSuccess;
  DdrType = Outputs->DdrType;
  Lpddr4 = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Ddr4 = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr5 = (DdrType == MRC_DDR_TYPE_LPDDR5);
  Lpddr = Outputs->Lpddr;
  MaxChannel = Outputs->MaxChannels;
  GetSetEn = 1;
  GetSetDis = 0;
  DqPinsInterleaved = (Inputs->DqPinsInterleaved != 0);
  MrcIntData->ClkDccInit = FALSE;
  MrcIntData->DqsDccInit = FALSE;
  RefClkPs = (Outputs->RefClk == MRC_REF_CLOCK_133) ? 7500 : 10000; // Reference Clock Period in pS

  MrcDdrioCrRestore (MrcData);

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    ControllerOut->DeviceId = (UINT16) (MrcPciRead32 (MrcData, HOST_BRIDGE_BUS, HOST_BRIDGE_DEVICE, HOST_BRIDGE_FUNCTION, HOST_BRIDGE_DEVID) >> 16);
    ControllerOut->RevisionId = (UINT8) (MrcPciRead32 (MrcData, HOST_BRIDGE_BUS, HOST_BRIDGE_DEVICE, HOST_BRIDGE_FUNCTION, HOST_BRIDGE_REVID));
  }

  // Select the interleaving mode of DQ/DQS pins
  // This must be the first DDR IO register to be programmed on ULT
  GetSetVal = (DqPinsInterleaved) ? 0 : 1;
  MrcGetSetNoScope (MrcData, GsmIocNoDqInterleave, WriteToCache | PrintValue, &GetSetVal);
  //MrcWeaklockEnDis (MrcData, MRC_DISABLE);

  if (Lpddr) {
    MrcGetSetNoScope (MrcData, GsmIocScramLpMode, WriteToCache | PrintValue, &GetSetEn);
  }
  MrcGetSetNoScope (MrcData, GsmIocScramOvrdPeriodicToDvfsComp, WriteToCache, &GetSetDis);

  switch (DdrType) {
    case MRC_DDR_TYPE_DDR4:
      Group = GsmIocScramDdr4Mode;
      break;

    case MRC_DDR_TYPE_LPDDR4:
      Group = GsmIocScramLp4Mode;
      break;

    case MRC_DDR_TYPE_DDR5:
      Group = GsmIocScramDdr5Mode;
      break;

    case MRC_DDR_TYPE_LPDDR5:
      Group = GsmIocScramLp5Mode;
      break;

    default:
      Group = GsmGtMax;
      break;
  }
  if (Group == GsmGtMax) {
    Status = mrcUnsupportedTechnology;
  } else {
    MrcGetSetNoScope (MrcData, Group, WriteToCache | PrintValue, &GetSetEn);
  }

  IoChNotPop = 0;
  for (Index = 0; Index < MRC_NUM_CCC_INSTANCES; Index++) {
    CccTxEn.Data16 = 0;
    // For DDR4, CCC[0:3] maps to Mc0 Ch0 and CCC[4:7] maps to Mc1 Ch0
    // For DDR5, CCC[0:1] maps to Mc0 Ch0
    // LPDDR is 1:1
    McIndex = Index / MAX_CHANNEL;
    if (Ddr4) {
      ChIndex = 0;
    } else {
      ChIndex = Index % MaxChannel;
    }
    RankPresent = Outputs->Controller[McIndex].Channel[ChIndex].ValidRankBitMask;
    Rank0Present = (0x1 & RankPresent);
    Rank1Present = ((RankPresent >> 1) & 0x1);
    if (RankPresent == 0) {
      IoChNotPop |= (1 << Index);
    }
    // Configure non-common enables:
    // LPDDR - Command, CS
    // DDR   - ODT, CKE, CS
    if (Lpddr4) {
      switch (Index) {
        case 0:
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
          CccTxEn.Data16 = MRC_CCC023467_LP4_CA_MSK;
          CccTxEn.Lp4.Ccc023467.Cs0 = Rank0Present;
          CccTxEn.Lp4.Ccc023467.Cs1 = Rank1Present;
          break;

        case 1:
        case 5:
          CccTxEn.Data16 = MRC_CCC15_LP4_CA_MSK;
          CccTxEn.Lp4.Ccc15.Cs0 = Rank0Present;
          CccTxEn.Lp4.Ccc15.Cs1 = Rank1Present;
          break;

        default:
          break;
      }
    } else if (Lpddr5) {
      if (Inputs->Lp5CccConfig & (1 << Index)) {
        // Descending Configuration
        switch (Index) {
          case 0:
          case 1:
          case 4:
          case 5:
            CccTxEn.Data16 = MRC_CCC0145_LP5D_CA_MSK;
            CccTxEn.Lp5D.Ccc0145.Cs = RankPresent;
            break;

          case 2:
          case 3:
          case 6:
          case 7:
            CccTxEn.Data16 = MRC_CCC2367_LP5D_CA_MSK;
            CccTxEn.Lp5D.Ccc2367.Cs0 = Rank0Present;
            CccTxEn.Lp5D.Ccc2367.Cs1 = Rank1Present;
            break;

          default:
            // Do nothing.  Will catch 0 in this as a failure below the DdrType Ladder.
            break;
        }
      } else {
        // Ascending Configuration
        switch (Index) {
          case 0:
          case 2:
          case 3:
          case 4:
          case 6:
          case 7:
            CccTxEn.Data16 = MRC_CCC023467_LP5A_CA_MSK;
            CccTxEn.Lp5A.Ccc023467.Cs = RankPresent;
            break;

          case 1:
          case 5:
            CccTxEn.Data16 = MRC_CCC15_LP5A_CA_MSK;
            CccTxEn.Lp5A.Ccc15.Cs0 = Rank0Present;
            CccTxEn.Lp5A.Ccc15.Cs1 = Rank1Present;
            break;

          default:
            // Do nothing.  Will catch 0 in this as a failure below the DdrType Ladder.
            break;
        }
      }
    } else {
      // DDR4
      switch (Index % 4) {
        case 0:
          CccTxEn.Data16 = MRC_CCC04_DDR4_CA_MSK;
          if (Rank0Present) {
            CccTxEn.Ddr4.Ccc04.Clk0 = 0x3;
          }
          break;

        case 1:
          CccTxEn.Data16 = MRC_CCC15_DDR4_CA_MSK;
          CccTxEn.Ddr4.Ccc15.Cs0  = Rank0Present;
          CccTxEn.Ddr4.Ccc15.Cs1  = Rank1Present;
          CccTxEn.Ddr4.Ccc15.Odt0 = Rank0Present;
          CccTxEn.Ddr4.Ccc15.Odt1 = Rank1Present;
          break;

        case 2:
          CccTxEn.Data16 = MRC_CCC26_DDR4_CA_MSK;
          CccTxEn.Ddr4.Ccc26.Cke0 = Rank0Present;
          CccTxEn.Ddr4.Ccc26.Cke1 = Rank1Present;
          break;

        case 3:
          CccTxEn.Data16 = MRC_CCC37_DDR4_CA_MSK;
          if (Rank1Present) {
            CccTxEn.Ddr4.Ccc37.Clk1 = 0x3;
          }
          break;

        default:
          // Do nothing.  Will catch 0 in this as a failure below the DdrType Ladder.
          break;
      }
    }
    if (CccTxEn.Data16 == 0) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "%s Ccc %d TxEn not initialized properly\n", Index);
      if (Inputs->ExitOnFailure) {
        return mrcFail;
      }
    }

    // Handle LP4/5 Clock and CKE/WCK since it is common.
    if (Lpddr) {
      CccTxEn.CccCommon.Clk = 0x3;
      CccTxEn.CccCommon.CkeWck = (Lpddr4) ? RankPresent : 0x3;
    }

    TxEn = CccTxEn.Data16;
    switch (DdrType) {
      case MRC_DDR_TYPE_DDR4:
        CccMux = 0;
        break;
      case MRC_DDR_TYPE_LPDDR4:
        CccMux = 1;
        break;

      case MRC_DDR_TYPE_LPDDR5:
        CccMux = ((Inputs->Lp5CccConfig >> Index) & 0x1) ? 3 : 2;
        break;

      case MRC_DDR_TYPE_DDR5:
      default:
        // DDR5 @todo
        CccMux = 0;
        break;
    }
    Gear1 = (Outputs->Gear2) ? 0 : 1;
    KeepXXClkOn = (Ddr4) ? 1 : 0;
    Delay = ((40 + Inputs->RcompTarget[RdOdt]) * 10) / 2; //@todo - Create a variable for DDR Init.
    Delay = Delay * 1000; // Scale to pS
    Delay = DIVIDEROUND (Delay, RefClkPs);
    Delay = MrcLog2 (Delay) - 2;
    TimerXXClk = RANGE (Delay, 0, 7);
    Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRPINSUSED_REG, CH1CCC_CR_DDRCRPINSUSED_REG, Index);
    Data = 0;
    if (Inputs->UlxUlt) {
      CccPinsUsed.Data = Data;
      CccPinsUsed.Bits.TxEn = TxEn;
      CccPinsUsed.Bits.CCCMuxSelect = CccMux;
      CccPinsUsed.Bits.PiEn = 0;
      CccPinsUsed.Bits.PiEnOvrd = 0;
      CccPinsUsed.Bits.Gear1 = Gear1;
      CccPinsUsed.Bits.KeepXXClkOn = KeepXXClkOn;
      CccPinsUsed.Bits.TimerXXClk = TimerXXClk;
      Data = CccPinsUsed.Data;
    } else {
      CccPinsUsedP0.Data = Data;
      CccPinsUsedP0.P0Bits.TxEn = TxEn;
      CccPinsUsedP0.P0Bits.CCCMuxSelect = CccMux;
      CccPinsUsedP0.P0Bits.PiEn = 0;
      CccPinsUsedP0.P0Bits.PiEnOvrd = 0;
      CccPinsUsedP0.P0Bits.Gear1 = Gear1;
      CccPinsUsedP0.P0Bits.KeepXXClkOn = KeepXXClkOn;
      CccPinsUsedP0.P0Bits.TimerXXClk = TimerXXClk;
      Data = CccPinsUsedP0.Data;
    }
    MrcWriteCR (MrcData, Offset, Data);
  } // CCC Instance
  GetSetVal = IoChNotPop;
  MrcGetSetNoScope (MrcData, GsmIocChNotPop, WriteCached | PrintValue, &GetSetVal);

  //if (Outputs->EccSupport) {
  //  MrcGetSetDdrIoGroupController0 (MrcData, GsmIocEccEn, WriteToCache, &GetSetEn);
  //}

  MrcFlushRegisterCachedData (MrcData);

  Status |= MrcDccSetup (MrcData);

  return Status;
}

#define TXEQ_CONSTATNTZ    (1 << 4)
#define TXEQ_NODEEMPHASIS   0xC

/**
  This function initializes the Memory Controller Phy.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrIoInit (
  IN OUT MrcParameters *const MrcData
  )
{
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  MrcIntOutput      *IntOutputs;
  MrcIntCmdTimingOut *IntCmdTiming;
  MrcStatus         Status;
  MrcOutput         *Outputs;
  MrcChannelOut     *ChannelOut;
  MrcControllerOut  *ControllerOut;
  MrcTiming         *TimingProfile;
  MrcProfile        Profile;
  MrcVddSelect      Vdd;
  MrcVddSelect      DramVdd;
  MrcFrequency      DdrFrequency;
  MrcDdrType        DdrType;
  INT64             GetSetVal;
  INT64             GetSetVal2;
  INT64             GetSetVal3;
  INT64             GetSetVal4;
  INT64             GetSetVal5;
  INT64             MaxVal;
  INT64             MinVal;
  INT64             Roundtrip;
  INT64             GetSetEn;
  INT64             RXDeskewForceOn;
  INT64             GetSetDis;
  INT64             RcvEnPi[MAX_CONTROLLER][MAX_CHANNEL];
  INT64             tCL4RcvEn;
  INT64             tCL4RxDqFifoRdEn;
  INT64             tCWL4TxDqFifoWrEn;
  INT64             tCWL4TxDqFifoRdEn;
  INT64             RxDqFifoRdEnRankDel;
  INT64             RxDqsPPi;
  INT64             RxDqsNPi;
  INT64             RxEqInit;
  INT64             RxCInit;
  INT64             RxRInit;
  INT64             RxTap0Init;
  INT64             RxTap1Init;
  INT64             RxDqBitPi;
  INT64             TxEqInit;
  INT64             TxDqPi;
  INT64             TxDqsPi;
  INT64             TxDqBitPi;
  INT64             RxDataValidDclk;
  INT64             RxDataValidQclk;
  INT32             TdqsckMin;
  INT32             tCL;
  INT32             tCWL;
  UINT32            Data;
  UINT32            Controller;
  UINT32            Offset;
  UINT32            Data32;
  UINT32            Itarget;
  UINT32            IcompUp;
  UINT32            IcompDn;
  UINT32            EffPullUp;
  UINT32            Gear2;
  UINT32            Voh;
  UINT32            VccIoMv;
  UINT32            PuDeltaV;
  UINT32            Index;
  UINT32            IpChannel;
  UINT32            PiToQclk;
  UINT32            RefClkMhz;
  UINT32            RefClkPs;
  UINT32            QclktoFreq;
  UINT32            TempVar1;
  UINT32            TempVar2;
  UINT32            TempVar3;
  UINT32            TempVar4;
  UINT32            AddTcwl;
  UINT32            DecTcwl;
  UINT32            Byte;
  UINT32            CCCBlock;
  UINT32            PBDStepSize;
  UINT32            RExternal;
  UINT32            CaRonDrvDn;
  UINT32            CaRonDrvUp;
  UINT32            TargetV0;
  UINT32            VttTargetV;
  UINT32            TargetVsxHi;
  UINT32            Tdqs2dqMinFs;
  UINT32            TxDqPUpPreDrvVccddq;
  UINT32            DisVddqPathWithVddq;
  UINT32            VssHiBypassVddqMode;
  UINT32            VssHiBypassVdd2Mode;
  INT32             VsxHiTargetV;
  INT32             SignedTempVar;
  INT32             SignedTempVar1;
  UINT32            OdtTarget;
  UINT32            Vdd2Mv;
  UINT32            CCCPredrvUseVcciog;
  UINT32            SevenPercentOfVccIoMv;
  UINT32            CBTune0;
  UINT32            ByteStart;
  UINT32            ByteEnd;
  UINT32            FirstController;
  UINT32            FirstChannel;
  UINT32            FirstByte;
  UINT32            VtOffset;
  UINT32            VtSlope;
  UINT16            ClkPiDelay;
  UINT16            CtlPiDelay;
  UINT16            CmdPiDelay;
  UINT16            ClkDelay;
  UINT16            WckPiDelay;
  UINT16            NMode;
  UINT16            VssHiSwingTarget;
  UINT16            SAFE;
  UINT16            VssHi;  // Target VssHi Voltage
  UINT16            VssHiMax;
  UINT16            VccddqMv;
  UINT16            Rodt;
  UINT16            RonCtlTarget;
  UINT16            QclkPs;
  UINT8             delta;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             ResetNumPre;
  UINT8             NumToggles;
  UINT8             MaxChannels;
  UINT8             RcvEnWaveShape;
  UINT8             PassRcvEn;
  UINT8             Rup;
  UINT8             RightShift;
  UINT8             DataInvertNibble;
  UINT8             TargetNUI;
  UINT8             CtlVoltSel;
  UINT8             EnDqsNRcvEnSet;
  BOOLEAN           ObeyDDQBypassB0;
  BOOLEAN           ObeyDDQBypassA0;
  BOOLEAN           Lpddr;
  BOOLEAN           Ddr;
  BOOLEAN           Lpddr4;
  BOOLEAN           Lpddr5;
  BOOLEAN           Ddr4;
  BOOLEAN           Ddr5;
  BOOLEAN           UlxUlt;
  BOOLEAN           BreakOut;
  MRC_RX_MODE_TYPE  RxMode;
  BOOLEAN           Is2DPC;
  BOOLEAN           UnMatched;
  BOOLEAN           NPath;
  BOOLEAN           StaticOdtDis;
  BOOLEAN           EnDqsOdtParkMode;
  MCMISCS_DDRWCKCONTROL_STRUCT                    WckControl;
  DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER_STRUCT        VssHiSampler;
  DDRVREF_CR_DDRCRVREFCONTROL_STRUCT              VrefControl;
  DDRVREF_CR_DDRCRVREFADJUST1_STRUCT              VrefAdj1;
  DDRVREF_CR_DDRCRVREFADJUST2_STRUCT              VrefAdj2;
  DLLDDRDATA0_CR_DDRCRVCCDLLFFCONTROL_STRUCT      VccDllFFControl;
  DLLDDRDATA0_CR_DDRCRVCCDLLFFNBIAS_STRUCT        VccDllFFNBias;
  DDRVCCDLL0_CR_DDRCRVCCDLLCONTROL_STRUCT         VccDllControl;
  DDRVCCDLL0_CR_DDRCRVCCDLLSAMPLER_STRUCT         VccDllSampler;
  DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_STRUCT        VccDllVsxHiFF;
  DLLDDRDATA0_CR_DDRCRVCCDLLCOMPDATACCC_STRUCT    VccDllCompDataCCC;
  DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_STRUCT    VccDllCouplingCap;
  DLLDDRDATA0_CR_DDRCRVCCDLLCOMPDLL_STRUCT        VccDllCompDll;
  DDRPHY_COMP_CR_DDRCRCOMPTEMP_STRUCT             CompTemp;
  DDRPHY_COMP_CR_DDRCRCOMPCTL0_STRUCT             CompCtl0;
  DDRPHY_COMP_CR_DDRCRCOMPCTL1_STRUCT             CompCtl1;
  DDRPHY_COMP_CR_DDRCRCOMPCTL2_STRUCT             CompCtl2;
  DDRPHY_COMP_CR_DDRCRCOMPCTL4_STRUCT             CompCtl4;
  DDRPHY_COMP_CR_VSSHIPANIC_STRUCT                VssHiPanic;
  DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_STRUCT        CompDvfsRload;
  DATA0CH0_CR_DDRCRDATACONTROL0_STRUCT            DataControl0;
  DATA0CH0_CR_DDRCRDATACONTROL2_STRUCT            DataControl2;
  DATA0CH0_CR_DDRCRDATACONTROL3_STRUCT            DataControl3;
  DATA0CH0_CR_DDRCRDATACONTROL5_STRUCT            DataControl5;
  DATA0CH0_CR_DDRCRDATACONTROL6_STRUCT            DataControl6;
  DATA0CH0_CR_DDRDATADQSRANK0_STRUCT              DataDqsRankX;
  DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_STRUCT  WrRetrainControlStatus;
  DATA0CH0_CR_DDRCRMARGINMODECONTROL0_STRUCT      MarginModeControl;
  DDRPHY_COMP_CR_VSSHITARGET_STRUCT               VssHiTarget;
  DDRPHY_COMP_CR_VCCDLLTARGET_STRUCT              VccDLLTarget;
  DDRVTT0_CR_DDRCRVTTCOMPOFFSET2_STRUCT           VttCompOffset2;
  DDRVTT0_CR_DDRCRVTTCOMPOFFSET_STRUCT            VttCompOffset;
  CH0CCC_CR_DDRCRCCCPERBITDESKEW0_STRUCT          CCCPerBitDeskew0; // @todo deskewcal-Program after SAComp
  CH0CCC_CR_DDRCRCCCPERBITDESKEW1_STRUCT          CCCPerBitDeskew1; //@todo uncomment after TurnOnDelay value is provided
  CH0CCC_CR_DDRCRCCCPERBITDESKEW2_STRUCT          CCCPerBitDeskew2;
  CH0CCC_CR_DDRCRCCCCLKCONTROLS_STRUCT            CCCClkControls;
  CH0CCC_CR_DDRCRBSCANDATA_STRUCT                 CCCBscanData;
  CH0CCC_CR_DDRCRBSCANDATA_P0_STRUCT              CCCBscanDataP0;
  CH0CCC_CR_DDRCRMISR_STRUCT                      CCCMisr;
  DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_STRUCT        VssHiCtl;
  DDRSCRAM_CR_DDRMISCCONTROL1_STRUCT              MiscControl1;
  DDRSCRAM_CR_DDRMISCCONTROL2_STRUCT              MiscControl2;
  DDRSCRAM_CR_DDRMISCCONTROL7_STRUCT              MiscControl7;
  M_COMP_PCU_STRUCT                               CrMCompPcu;
  MC0_CH0_CR_SC_WR_DELAY_STRUCT                   ScWrDelay;
  DLLDDRDATA0_CR_DLLPITESTANDADC_STRUCT           DataDllPiTestAndAdc;
  DDRPHY_COMP_CR_VCCDLLREPLICACTRL0_STRUCT        VccDllReplicaCtrl0;
  DDRPHY_COMP_CR_VCCDLLREPLICACTRL1_STRUCT        VccDllReplicaCtrl1;
  DDRPHY_COMP_CR_VCCDLLDQSDELAY_STRUCT            VccDllDqsDelay;
  CH0CCC_CR_DDRCRCCCVOLTAGEUSED_STRUCT            CCCVoltageUsed;
  DDRVTT0_CR_DDRCRVTTGENCONTROL_STRUCT            VttGenControl;
  DDRPHY_COMP_CR_DDRCRALERT_STRUCT                CompAlert;
  MCMISCS_SPINEGATING_STRUCT                      McMiscSpineGating;
  DDRSCRAM_CR_DDRSCRAMBLECH0_STRUCT               DdrScramCh0;
  DDRSCRAM_CR_DDRSCRAMBLECH1_STRUCT               DdrScramCh1;
  DDRSCRAM_CR_DDRSCRAMBLECH2_STRUCT               DdrScramCh2;
  FLL_CMD_CFG_REG_STRUCT                          FllCmdCfg;
  FLL_STATIC_CFG_0_REG_STRUCT                     FllStaticCfg0;
  FLL_STATIC_CFG_1_REG_STRUCT                     FllStaticCfg1;
  DDRPHY_COMP_CR_DDRCRFLLWIRED_STRUCT             FllWired;
  DATA0CH0_CR_DCCPILUT4_STRUCT                    PiLut4;
  DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_STRUCT        VccDllReplicaCtrl2;
  DDRPHY_COMP_CR_DDRCRVIEWCTL_STRUCT              ViewCtl;
  DDRPHY_COMP_CR_DDRCRDATACOMP0_STRUCT            RcompData0;
  DDRPHY_COMP_CR_DDRCRDATACOMP1_STRUCT            RcompData1;
#ifdef MRC_DEBUG_PRINT
  DDRPHY_COMP_CR_DDRCRDATACOMPVTT_STRUCT  DataCompVtt;
#endif //MRC_DEBUG_PRINT

  Inputs            = &MrcData->Inputs;
  Outputs           = &MrcData->Outputs;
  Debug             = &Outputs->Debug;
  IntOutputs        = (MrcIntOutput *) (MrcData->IntOutputs.Internal);
  Profile           = Inputs->MemoryProfile;
  DdrType           = Outputs->DdrType;
  Status            = mrcSuccess;
  Vdd               = (Outputs->Lp4x) ? VDD_1_10 : Outputs->VddVoltage[Profile];
  Lpddr4            = (DdrType == MRC_DDR_TYPE_LPDDR4);
  Lpddr5            = (DdrType == MRC_DDR_TYPE_LPDDR5);
  Ddr4              = (DdrType == MRC_DDR_TYPE_DDR4);
  Ddr5              = (DdrType == MRC_DDR_TYPE_DDR5);
  Lpddr             = (Lpddr4 || Lpddr5);
  Ddr               = (Ddr4 || Ddr5);
  RxMode            = Outputs->RxMode;
  QclkPs            = Outputs->Qclkps;
  GetSetEn          = 1;
  GetSetDis         = 0;
  SAFE              = 0;
  VssHiSwingTarget  = 950;  // VssHi target voltage in mV
  delta             = 20;   // VssHi change voltage during panic, in mV
  VccddqMv          = Outputs->VccddqVoltage;
  VccIoMv           = Inputs->VccIomV;
  Vdd2Mv            = Outputs->Vdd2Mv;
  //Vss               = (Outputs->OdtMode == MrcOdtModeVss);
  //DqPinsInterleaved = (Inputs->DqPinsInterleaved != 0);
  DdrFrequency      = (Lpddr && Inputs->LpFreqSwitch) ? Outputs->HighFrequency : Outputs->Frequency;
  //EnVttOdt          = (Outputs->OdtMode == MrcOdtModeVtt);
  //CbenVal           = 3;
  UlxUlt            = Inputs->UlxUlt;
//  DtHalo            = Inputs->DtHalo;
  Gear2             = Outputs->Gear2 ? 1 : 0; // Used to add extra clock(s) in Gear2 mode
  MaxChannels       = Outputs->MaxChannels;
  PiToQclk          = 64 * (1 + Gear2);
  NMode             = 0;
  tCL               = 0;
  tCWL              = 0;
  VsxHiTargetV      = Vdd2Mv - VccIoMv;
  VttTargetV        = Ddr5 ? (Vdd2Mv / 2) : 150; //150mV
  CaRonDrvDn        = Inputs->RcompTarget[WrDSCmd];
  Itarget           = CDIEVSSHI * delta / Outputs->UIps; // Target Current.  pF * mV / pS -> mA
  CaRonDrvUp        = Inputs->RcompTarget[WrDSCmd]; // @todo whats the difference between Up and Dn
  BreakOut          = FALSE;
  DataInvertNibble  = 0;
//  Vcm = 5;
//  TxPwrMuxSelVddq = 0; //@todo find value
//  TurnOnDelay = 5;
//  Ron = Inputs->RcompTarget[WrDS];
  Rodt = Inputs->RcompTarget[RdOdt];
  RonCtlTarget = Inputs->RcompTarget[WrDSCtl];
//  Vtester = 5;
  Rup = 47;

  // Temporary Variables init
  TempVar1 = 0;
  TempVar2 = 0;
  TempVar3 = 0;
  TempVar4 = 0;
  SignedTempVar = 0;
  SignedTempVar1 = 0;
  RXDeskewForceOn = 1;
  // The following 3 variables have to be initialized here before their
  // assignment in the conditional for loop block. Otherwise GCC throws warning as
  // variable uninitialized
  TimingProfile = 0;
  GetSetVal = 0;
  CBTune0 = 0;
  PBDStepSize = 5;
  RExternal = Inputs->RcompResistor; //100 ohms
  RefClkMhz = Outputs->RefClk;
  ByteStart = 0;
  ByteEnd = Outputs->SdramCount;
  QclktoFreq = 1000000 / QclkPs;
  SignedTempVar1 = VccIoMv - (UINT32) VccddqMv;
  SevenPercentOfVccIoMv = (7 * VccIoMv) / 100;
  TempVar1 = ABS (SignedTempVar1);
  TxDqPUpPreDrvVccddq = (TempVar1 != 0) ? (TempVar1 <= SevenPercentOfVccIoMv) : 1; // Set default value of DataControl5.TxDqPUpPreDrvVccddq if VccIoMv < VccddqMv
  TargetVsxHi = Vdd2Mv - VccddqMv;
  DisVddqPathWithVddq = (TargetVsxHi < ((7 * Vdd2Mv) / 100));
  VssHiBypassVddqMode = (VccddqMv >= VDD_1_20) ? 0 : (VccddqMv >= VDD_1_10) ? (DdrFrequency >= f4500) : (VccddqMv >= VDD_1_05) ? (DdrFrequency >= f2800) : 1;
  VssHiBypassVdd2Mode = (Vdd2Mv >= VDD_1_20) ? 0 : (Vdd2Mv >= VDD_1_10) ? (DdrFrequency >= f6400) : (Vdd2Mv >= VDD_1_05) ? (DdrFrequency >= f4500) : 1;
  CtlVoltSel = Lpddr4 ? 1 : Lpddr5 ? (VccddqMv < VDD_0_75) : 0;
  // Default RefClk = 100 MHz so RefClkPs = 1/100 MHz = 10ns or 10,000ps
  // If RefClk = 100 MHz then RefClkPs = 10000ps , If RefClk = 133 MHz then RefClkPs = 7500ps
  RefClkPs  = (RefClkMhz == MRC_REF_CLOCK_133) ? 7500 : 10000; // Reference Clock Period in pS
  OdtTarget = Inputs->RcompTarget[RdOdt];
  StaticOdtDis = (OdtTarget > 120);
  if (Inputs->SafeMode) {
    SAFE = 0xFFFF;
  }
  UnMatched = ((RxMode == MrcRxModeUnmatchedRxWRload) || (RxMode == MrcRxModeUnmatchedRxWPpath));
  NPath     = (RxMode == MrcRxModeMatchedN);

  Outputs->ValidMcBitMask = 0;
  Outputs->ValidChBitMask = 0;
  Outputs->ValidRankMask  = 0;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (MrcControllerExist (MrcData, Controller)) {
      ControllerOut = &Outputs->Controller[Controller];
      Outputs->ValidMcBitMask |= (1 << Controller);
      ControllerOut->FirstPopCh = MAX_CHANNEL;
      for (Channel = 0; Channel < MaxChannels; Channel++) {
        if (MrcChannelExist (MrcData, Controller, Channel)) {
          ChannelOut = &ControllerOut->Channel[Channel];
          // Initialize ValidChBitMask and ValidRankMask used during all training steps
          // Program various Rank Occupancy / RanksUsed bits.
          ControllerOut->ValidChBitMask |= (1 << Channel);
          ControllerOut->FirstPopCh = MIN (Channel, ControllerOut->FirstPopCh);
          Outputs->ValidChBitMask |= (ControllerOut->ValidChBitMask << (Controller * Outputs->MaxChannels));
          Outputs->ValidRankMask  |= ChannelOut->ValidRankBitMask;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "Mc%u.C%u: ValidRankBitMask=0x%x, Overall ValidRankMask=0x%x\n",
            Controller,
            Channel,
            ChannelOut->ValidRankBitMask,
            Outputs->ValidRankMask
            );
          // Determine NMode.  Constraint is timing must be the same in MC/CH
          NMode = ChannelOut->Timing[Profile].NMode;
        } // MrcChannelExist
      } // Channel
      MRC_DEBUG_MSG (
        Debug,
        MSG_LEVEL_NOTE,
        "Mc%u: ValidChBitMask=0x%x\n",
        Controller,
        ControllerOut->ValidChBitMask
        );
    } // MrcControllerExists
  } // Controller
  MRC_DEBUG_MSG (
    Debug,
    MSG_LEVEL_NOTE,
    "ValidMcBitMask=0x%x, Overall ValidChBitMask=0x%x\n",
    Outputs->ValidMcBitMask,
    Outputs->ValidChBitMask
    );

  FirstController = (MrcControllerExist (MrcData, cCONTROLLER0)) ? 0 : 1;
  FirstChannel = Outputs->Controller[FirstController].FirstPopCh;
  FirstByte = (MAX_BYTE_IN_LP_CHANNEL * FirstChannel);

  // Read the first existing register
  // @todo Remove the following for loops and use the "FirstController and First Channel"
  for (Controller = 0; (Controller < MAX_CONTROLLER) && (BreakOut == FALSE); Controller++) {
    for (Channel = 0; (Channel < MAX_CHANNEL) && (BreakOut == FALSE); Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        CCCBlock = ((MAX_CCC_PER_CHANNEL * Controller) + Channel);
        Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCCCPERBITDESKEW2_REG, CH1CCC_CR_DDRCRCCCPERBITDESKEW2_REG, CCCBlock);
        CCCPerBitDeskew2.Data = MrcReadCR (MrcData, Offset);
        Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRMISR_REG, CH1CCC_CR_DDRCRMISR_REG, CCCBlock);
        CCCMisr.Data = MrcReadCR (MrcData, Offset);
        Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRBSCANDATA_REG, CH1CCC_CR_DDRCRBSCANDATA_REG, CCCBlock);
        if (Inputs->UlxUlt) {
          CCCBscanData.Data = MrcReadCR (MrcData, Offset);
        } else {
          CCCBscanDataP0.Data = MrcReadCR (MrcData, Offset);
        }
        if (MrcData->Outputs.Lpddr) {
          Byte = (MAX_BYTE_IN_LP_CHANNEL * Channel); //@todo : For DDR5 MAX_BYTE_IN_CHANNEL != 2 so add that
        } else {
          Byte = 0; // By default if Channel is present then first byte will be present
        }
        Offset = DataControl3Offset (Controller, Byte);
        DataControl3.Data = MrcReadCR (MrcData, Offset);
        Offset = DataControl5Offset (Controller, Byte);
        DataControl5.Data = MrcReadCR (MrcData, Offset);
        Offset = DataControl2Offset (Controller, Byte);
        DataControl2.Data = MrcReadCR (MrcData, Offset);
        Offset = CBTune0Offset (CCCBlock);
        CBTune0 = MrcReadCR (MrcData, Offset);
        BreakOut = TRUE;
      } // Channel Exist
    } // Channel
  } // Controller

  PiLut4.Data = 0;
  PiLut4.Bits.LUTHalfStep = (QclktoFreq >= 2100) ? 1 : 0;
  MrcWriteCrMulticast (MrcData, DATA_CR_DCCPILUT4_REG, PiLut4.Data);

  // Set CCC PI values.  Will be consumed and configured below in various stages
  if (Ddr4) {
    // 3N Timing
    CtlPiDelay = 64;
    ClkPiDelay = 128;
    CmdPiDelay = 128;
  } else if (Lpddr5) {
    ClkPiDelay = 384;
    CmdPiDelay = 256;
    CtlPiDelay = 128;
  } else if (Lpddr4) {
    ClkPiDelay = 160;
    CmdPiDelay = 128;
    CtlPiDelay = 128;
  } else {
    if (NMode == 2) {
      ClkPiDelay = 192;
      CmdPiDelay = 128;
      CtlPiDelay = 149;
    } else {
      // 2N
    ClkPiDelay = 192;
    CmdPiDelay = 128;
    CtlPiDelay = 128;
    }
  }
  // Only programmed in LP5.  Just initializing here to avoid compile issues and make code smaller instead of if-ladder
  WckPiDelay = 384;

  VssHiCtl.Data = MrcReadCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG);
  Data32 = 128 * VsxHiTargetV;
  Data32 = DIVIDEROUND(Data32, VccIoMv);
  VssHiCtl.Bits.Target = Data32;
  VssHiCtl.Bits.BWError = 1;
  VssHiCtl.Bits.PanicEn = 1;
  VssHiCtl.Bits.EnDacPM = ((Inputs->A0) || SAFE) ? 0 : 2;
  VssHiCtl.Bits.EnCkePanic = ((Inputs->A0) || SAFE) ? 1 : 0;
  VssHiCtl.Bits.GainBoost = 1;
  VssHiCtl.Bits.SelCode = 1;
  VssHiCtl.Bits.UseMax = 1;
  if (Inputs->A0) {
    VssHiCtl.Bits.SampleDivider = 0;
  }
  VssHiCtl.Bits.LoBWDivider = 0;
  MrcWriteCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG, VssHiCtl.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DdrCrVsshiControl: 0x%X\n", Data32);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init Dimm Vref CRs\n");
  VssHiSampler.Data = 0;
  TempVar1 = 382 * VsxHiTargetV;
  TempVar2 = DIVIDEROUND (TempVar1, Vdd2Mv) - 32;
  VssHiSampler.Bits.Target = TempVar2;
  TempVar1 = 382 * PANICV0;
  TempVar2 = UDIVIDEROUND (TempVar1 , Vdd2Mv);
  VssHiSampler.Bits.Panic = TempVar2;
  VssHiSampler.Bits.PanicLoUsePmos     = ((VsxHiTargetV + PANICV0) < 375);
  VssHiSampler.Bits.VssHiTargetUsePmos = ((VsxHiTargetV + PANICV0) < 375);
  VssHiSampler.Bits.PanicHiUsePmos     = ((VsxHiTargetV + PANICV0) < 375);
  TempVar1 = VssHiCtl.Bits.SampleDivider + 3;
  TempVar2 = 1 << TempVar1;
  TempVar3 = DIVIDEROUND (20000, QclkPs); // Scale 20ns to ps
  TempVar4 = DIVIDEROUND (TempVar3, TempVar2);
  if (TempVar4 > 0) {
    TempVar4--;
  }
  TempVar4 = MAX (TempVar4, 7);
  VssHiSampler.Bits.WakeUpDelay = TempVar4;
  TempVar1 = 120000 / RefClkPs;
  TempVar2 = MrcLog2 (TempVar1);
  if (TempVar2 > 0) {
    TempVar2--;
  }
  TempVar2 = MAX (TempVar2, 3);
  VssHiSampler.Bits.LockTimer = TempVar2;
  VssHiSampler.Bits.AckOffset = 1;
  MrcWriteCR (MrcData, DDRVSSHIAFEA_CR_DDRCRVSSHISAMPLER_REG, VssHiSampler.Data);

  ViewCtl.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRVIEWCTL_REG);
  ViewCtl.Bits.TcoComp0 = 0x20;
  ViewCtl.Bits.TcoComp1 = 0x20;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRVIEWCTL_REG, ViewCtl.Data);

  DataControl0.Data = 0;
  if (SAFE) {
    DataControl0.Bits.local_gate_d0tx = 1;
    DataControl0.Bits.InternalClocksOn = 1;
    DataControl0.Bits.tx_clock_on_with_txanalogen = 1;
    DataControl0.Bits.RepeaterClocksOn = 1;
    DataControl0.Bits.TxDeskewForceOn = 1;
    DataControl0.Bits.EnDqOdtParkMode = 1;
    DataControl0.Bits.ForceRxOn = 1;
    DataControl0.Bits.TxPiOn = 1;
    DataControl0.Bits.EnDqsOdtParkMode = 1;
    DataControl0.Bits.BiasPMCtrl = 0;
    DataControl0.Bits.VrefPMCtrl = 0;
  } else {
    DataControl0.Bits.EnDqsOdtParkMode = (Lpddr4) ? 2 : (Lpddr5 ? 3 : 0); //DDR4 sets 0 and DDR5 sets ???
    DataControl0.Bits.BiasPMCtrl = (!Lpddr && Inputs->A0) ? 2 : 3;
    DataControl0.Bits.VrefPMCtrl = 1; // HVM (IOLB w/ CKE power down) experiments try 0x2 and measure EH
  }
  DataControl0.Bits.WlLongDelEn = 1;
  EnDqsOdtParkMode = ((DataControl0.Bits.EnDqsOdtParkMode == 1) || (DataControl0.Bits.EnDqsOdtParkMode == 2));
  DataControl0.Bits.DqsNParkLowVoh = (EnDqsOdtParkMode && Lpddr && (VccddqMv > VDD_0_75)) ? 1 : 0;
  // DataControl0.Bits.DisableOdtStatic = (OdtTarget > 120); // GetSet Programming down below
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRCRDATACONTROL0_REG, DataControl0.Data);
  DataControl5.Bits.TxDqPUpPreDrvVccddq = TxDqPUpPreDrvVccddq;
  DataControl5.Bits.TxBypassVssHi = VssHiBypassVddqMode;
  DataControl5.Bits.DataInvertNibble = (UINT32) DataInvertNibble;
  //DataControl5.Bits.BiasBypassVsxHi = 0 ;
  DataControl5.Bits.TxDqPDnPreDrvVccddq = TxDqPUpPreDrvVccddq  & VssHiBypassVddqMode;
  TempVar1 = DataControl5.Bits.BiasPwrMuxSelVdd2 ? Vdd2Mv : VccIoMv;
  TempVar2 = 200000000 - (TempVar1 * 125000); //Scale it to nV
  TempVar3 = TempVar2/TempVar1;
  TempVar4 = DIVIDEROUND(TempVar3, 31250);
  DataControl5.Bits.BiasRloadVref = RANGE(TempVar4, 0, 7);
  // Need to program the bias for the matched receiver in unmatched when using DQS-N for ReceiveEnable.
  // It is ignore otherwise, so no harm to keep at 0xA always.
  DataControl5.Bits.BiasIrefAdj =  ((Ddr && NPath) || UnMatched) ? 0xA : 0x7;
  //DataControl5.Bits.BiasPwrMuxSelVdd2 = 0; // @todo : needs training
  DataControl5.Bits.BiasCasAdj = 2;
  DataControl5.Bits.ODTSingleSegEn = (OdtTarget > 55);
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRCRDATACONTROL5_REG, DataControl5.Data);

  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRXDeskewForceOn, WriteCached, &RXDeskewForceOn);
  // @todo- where do we find RxDqsPiOffset ? Is this in a register ?  Whats unmatched ? Any MRC parameter for this one ?
  // FinalDqsPPICode  = RxDqsNDelayPi(Train) + RxDqsPiOffset(CR) + (Unmatched ? (Comp.RxDqsDelayN - 64*(DDRCOMP_CR_DDRCRDATACOMP0_0_0_0_MCHBAR.DqsNOffsetNUI+DDRDATA_CR_DDRCRDATAOFFSETTRAIN_0_0_0_MCHBAR.RxDqsPiUIOffset)) : 0)
//-----------------------------VccDLL CRs----------------------------------------------
  VccDllControl.Data = 0;

  TempVar1 = (MRC_VCCDLL_TARGET * 382);
  TempVar2 = DIVIDEROUND (TempVar1, MRC_VCCBG) - 256;
  VccDllControl.Bits.Target = RANGE (TempVar2, 0, 126);
  VccDllControl.Bits.HiBWDivider = 0; //TBD
  VccDllControl.Bits.LoBWDivider = 0; //TBD;
  TempVar2 = (2500 / QclkPs); // considering numerator 2.5 ns
  TempVar2 /= 2;
  TempVar3 = MrcLog2 (TempVar2);
  VccDllControl.Bits.SampleDivider = TempVar3;
  VccDllControl.Bits.EnRemoteSense = 1;
  VccDllControl.Bits.SelCode = 1;
  if (Inputs->A0) {
    VccDllControl.Bits.SampleDivider = 3;
    VccDllControl.Bits.HiBWDivider = 2;
  }
  VccDllControl.Bits.Bypass = (SAFE) ? 1 : 0;
  MrcWriteCrMulticast (MrcData, DDRVCCDLL_CR_DDRCRVCCDLLCONTROL_REG, VccDllControl.Data);

  VccDllFFNBias.Data = 0;

  VccDllFFNBias.Bits.NbTarget = VccDllControl.Bits.Target;
  TempVar1 = QclktoFreq * 10;
  TempVar2 = DIVIDEROUND (QclktoFreq, 575) + 65;
  VccDllFFNBias.Bits.NbiasLoad = DIVIDEROUND (TempVar2, 10);
  TempVar1 = (800000 / RefClkPs) - 5;
  TempVar2 = MrcLog2 (TempVar1);
  VccDllFFNBias.Bits.NbiasTimer0 = TempVar2;
  TempVar1 = (250000 / RefClkPs) - 4;
  TempVar2 = MrcLog2 (TempVar1);
  VccDllFFNBias.Bits.NbiasTimer1 = TempVar2;
  VccDllFFNBias.Bits.NbiasCPVccIOG = (VccIoMv >= 850);
  VccDllFFNBias.Bits.NbiasEnLeaker = 2;
  // @todo : This field needs to be programmed after Scomp execution
//  VccDllFFNBias.Bits.SideClkPulse = 0;
  VccDllFFNBias.Bits.NbiasFastStartup = 1;
  MrcWriteCrMulticast (MrcData, DLLDDR_CR_DDRCRVCCDLLFFNBIAS_REG, VccDllFFNBias.Data);

  VccDllSampler.Data = MrcReadCR (MrcData, DDRVCCDLL0_CR_DDRCRVCCDLLSAMPLER_REG);
  // VccDllSampler.Bits.PullDownSlope = 2; // MRC: RestrictedConted Field doesnt exist in A0
  VccDllSampler.Bits.FBOverlap = 2;
  TempVar1 = 382 * PANICV0;
  TempVar2 = DIVIDEROUND (TempVar1, Vdd2Mv);
  VccDllSampler.Bits.Panic = RANGE (TempVar2, 0, 31);
  VccDllSampler.Bits.GainBoost = 2;
  TempVar1 = MRC_VCCDLL_TARGET - 600;
  TempVar2 = DIVIDEFLOOR (TempVar1, 50);
  VccDllSampler.Bits.NSalCMCap = RANGE (TempVar2, 0, 7);
  TempVar1 = VssHiCtl.Bits.SampleDivider + 3;
  TempVar2 = 1 << TempVar1;
  TempVar3 = 28000 / QclkPs; // Scale 16ns to ps
  TempVar4 = DIVIDEROUND (TempVar3, TempVar2) - 1;
  VccDllSampler.Bits.WakeUpDelay = RANGE (TempVar4, 0, 7);
  TempVar1 = (1000000 / RefClkPs);
  TempVar1 -= 5;
  TempVar2 = MrcLog2 (TempVar1);
  VccDllSampler.Bits.LockTimer = TempVar2;
  VccDllSampler.Bits.CodeReset = 6;
  VccDllSampler.Bits.AckOffset = 1;
  if (Inputs->A0) {
    VccDllSampler.Bits.LoBWDividerLP = VccDllControl.Bits.LoBWDivider;
  }
  MrcWriteCrMulticast (MrcData, DDRVCCDLL_CR_DDRCRVCCDLLSAMPLER_REG, VccDllSampler.Data);

  VccDllCompDll.Data = 0;
  SignedTempVar = Gear2 ? (DdrFrequency / 2) : DdrFrequency;
  VccDllCompDll.Bits.FFCodeIdle = (-SignedTempVar / 130) + 53;
  VccDllCompDll.Bits.FFCodePI   = (-SignedTempVar / 110) + 58;
  MrcWriteCrMulticast (MrcData, DDRVCCDLL_CR_DDRCRVCCDLLCOMPDLL_REG, VccDllCompDll.Data);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLCOMPDLL_REG, VccDllCompDll.Data);

  VccDllCompDataCCC.Data = 0;
  VccDllCompDataCCC.Bits.FFCodeCCCDist = (DdrFrequency / 100) + 11;
  VccDllCompDataCCC.Bits.FFCodePBD = (DdrFrequency / 60) - 2;
  // @todo : Original condition was MatchedPath. Does that corrospond to both P and N matched or either of them matched
  VccDllCompDataCCC.Bits.FFCodeRead = ((RxMode == MrcRxModeMatchedP) || (RxMode == MrcRxModeMatchedN)) ? ((DdrFrequency / 120) + 25) : ((DdrFrequency / 210) + 21);
  VccDllCompDataCCC.Bits.FFCodeWrite = (DdrFrequency / 530) + 38;
  MrcWriteCrMulticast (MrcData, DLLDDR_CR_DDRCRVCCDLLCOMPDATACCC_REG, VccDllCompDataCCC.Data);

  VccDllVsxHiFF.Data = 0;
  TempVar1 = 36 + (2 * VccDllCompDataCCC.Bits.FFCodePBD);
  TempVar2 = DIVIDEROUND (TempVar1, 7);
  VccDllVsxHiFF.Bits.VsxHiFFCodePBD = TempVar2;
  TempVar1 = 800 + (20 * VccDllCompDataCCC.Bits.FFCodeRead);
  TempVar2 = DIVIDEROUND (TempVar1, 20);
  VccDllVsxHiFF.Bits.VsxHiFFCodeRead = TempVar2;
  TempVar1 = 700 + (15 * VccDllCompDataCCC.Bits.FFCodeWrite);
  TempVar2 = DIVIDEROUND (TempVar1, 20);
  VccDllVsxHiFF.Bits.VsxHiFFCodeWrite = TempVar2;
  TempVar1 = 35 + (1 * VccDllCompDll.Bits.FFCodePI);
  TempVar2 = DIVIDEROUND (TempVar1, 13);
  VccDllVsxHiFF.Bits.VsxHiFFCodePi = TempVar2;
  TempVar1 = 184 + (6 * VccDllCompDll.Bits.FFCodeIdle);
  TempVar2 = DIVIDEROUND (TempVar1, 18);
  VccDllVsxHiFF.Bits.VsxHiFFCodeIdle = TempVar2;
  MrcWriteCrMulticast (MrcData, DLLDDR_CR_DDRCRVCCDLLVSXHIFF_REG, VccDllVsxHiFF.Data);

  VccDllCouplingCap.Data = 0;
  TempVar1 = 36 + (2 * VccDllCompDataCCC.Bits.FFCodePBD);
  TempVar2 = DIVIDEROUND (TempVar1, 33);
  VccDllCouplingCap.Bits.CapCancelCodePBD = TempVar2;
  TempVar1 = 800 + (20 * VccDllCompDataCCC.Bits.FFCodeRead);
  TempVar2 = DIVIDEROUND (TempVar1, 33);
  VccDllCouplingCap.Bits.CapCancelCodeRead = TempVar2;
  TempVar1 = 700 + (15 * VccDllCompDataCCC.Bits.FFCodeWrite);
  TempVar2 = DIVIDEROUND (TempVar1, 33);
  VccDllCouplingCap.Bits.CapCancelCodeWrite = TempVar2;
  TempVar1 = 35 + (1 * VccDllCompDll.Bits.FFCodePI);
  TempVar2 = DIVIDEROUND (TempVar1, 33);
  VccDllCouplingCap.Bits.CapCancelCodePi = TempVar2;
  TempVar1 = 184 + (6 * VccDllCompDll.Bits.FFCodeIdle);
  TempVar2 = DIVIDEROUND (TempVar1, 33);
  VccDllCouplingCap.Bits.CapCancelCodeIdle = TempVar2;
  MrcWriteCrMulticast (MrcData, DLLDDR_CR_DDRCRVCCDLLCOUPLINGCAP_REG, VccDllCouplingCap.Data); // Multicast offset used

  CompTemp.Data = 0;
  CompTemp.Bits.FFCodeDqsDelay = (DdrFrequency / 360) + 35;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPTEMP_REG, CompTemp.Data);

  CompCtl0.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL0_REG);
  CompCtl0.Bits.DQPredrvUseVcciog = (TxDqPUpPreDrvVccddq == 0);
  CompCtl0.Bits.DisVddqPathWithVddq = DisVddqPathWithVddq;
  CompCtl0.Bits.CCCVssHiBypassVdd2Mode = VssHiBypassVdd2Mode;
  CompCtl0.Bits.CCCVssHiBypassVddqMode = VssHiBypassVddqMode;
  CompCtl0.Bits.CtlVoltageSelect = CtlVoltSel;
  CompCtl0.Bits.ClkVoltageSelect = CLK_VOLT_SEL;
  CompCtl0.Bits.CaVoltageSelect = CA_VOLT_SEL;
  TempVar1 = (VccIoMv > VccddqMv) ? (VccIoMv - VccddqMv) : 0;
  CCCPredrvUseVcciog = (TempVar1 != 0) ? (TempVar1 > SevenPercentOfVccIoMv) : 0; // Program default if VccIoMv < VccddqMv
  CompCtl0.Bits.CCCPredrvUseVcciog = CCCPredrvUseVcciog;
  CompCtl0.Bits.CCCStaticLegCtl = 1;
  CompCtl0.Bits.DQVssHiBypassVddqMode = VssHiBypassVddqMode;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL0_REG, CompCtl0.Data);

  // Following register is needed for CompCtl4 so program this first

  VssHiPanic.Data = 0;
  if (SAFE) {
    VssHiPanic.Bits.PanicCCCPU = (VsxHiTargetV > 350) ? 0 : 2;
  } else {
    VssHiPanic.Bits.PanicCCCPU = (VsxHiTargetV > 350) ? 1 : 3;
  }
  TempVar1 = (191 * (VsxHiTargetV - PANICV0)) / VccIoMv;
  VssHiPanic.Bits.VsxHiPanicUpVref = MAX (TempVar1, 127);
  if (TempVar1 > 127) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Clamping VsxHiPanicUpVref: %d\n",TempVar1);
  }
  TempVar2 = 191 * (VsxHiTargetV + PANICV0);
  TempVar3 = CA_VOLT_SEL ? Vdd2Mv : VccddqMv;
  VssHiPanic.Bits.VsxHiPanicDnVref = DIVIDEROUND (TempVar2, TempVar3);

  TempVar1 = (1 + VssHiPanic.Bits.PanicCCCPU) >> 1;
  TempVar2 = DIVIDEROUND (CaRonDrvDn, TempVar1);
  TempVar3 = VsxHiTargetV - PANICV0;
  IcompUp = DIVIDEROUND (TempVar3, TempVar2);
  TempVar4 = DIVIDEROUND (Itarget, IcompUp);
  VssHiPanic.Bits.VsxHiPanicCompUpMult = TempVar4;
  TempVar1 = (CA_VOLT_SEL ? Vdd2Mv : VccddqMv) - VsxHiTargetV - PANICV0;
  IcompDn = DIVIDEROUND (TempVar1, CaRonDrvUp);

  TempVar2 = IcompDn * (1 + VssHiPanic.Bits.PanicPDn2xStep);
  TempVar3 = DIVIDEROUND (Itarget, TempVar2);
  VssHiPanic.Bits.VsxHiPanicCompDnMult = TempVar3;

  // Run initial compensation with 0 (1x).  If HVM Test or (PanicDrvDn/VsxHiPanicCompDnMult) > 40, then switch to 1 (2x)
  // Very similar to the flow for CCCStaticLegCtl.  Start with 0 and run compensation.  If (PanicDrvDn/VsxHiPanicCompDnMult) > 40, then switch to 1 (2x)
  VssHiPanic.Bits.PanicPDn2xStep = 0;
  VssHiPanic.Bits.PanicCCCPUVssHiBypass = SAFE ? 0 : 1; // (DVFS == Enabled)  (Assume this will be off for SAFE config)
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSSHIPANIC_REG, VssHiPanic.Data);

  CompDvfsRload.Data = 0;
  TempVar2 = RANGE (VsxHiTargetV, 100, 450);
  TargetV0 = (Vdd2Mv + (4 * TempVar2)) / 5;
  TempVar3 = ((TargetV0 * 382) / Vdd2Mv) - 32;
  CompDvfsRload.Bits.VsxHiLVRTargetNormal = TempVar3;
  TempVar1 = Vdd2Mv - (VccddqMv - (VssHiBypassVddqMode ? 0 : VsxHiTargetV));
  TempVar2 = RANGE (TempVar1, 100, 450);
  TargetV0 = (Vdd2Mv + (4 * TempVar2)) / 5;
  TempVar3 = ((TargetV0 * 382) / Vdd2Mv) - 32;
  CompDvfsRload.Bits.VsxHiLVRTargetDvfs = TempVar3;
  CompDvfsRload.Bits.VsxHiLVRBias = 22; //0x16
  CompDvfsRload.Bits.DvfsRcompNormalOp = (SAFE || Inputs->A0) ? 0 : 1;
  CompDvfsRload.Bits.DisableVsxHiLVR = (SAFE || Ddr) ? 1 : 0;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPDVFSRLOAD_REG, CompDvfsRload.Data);

  CompCtl1.Data = 0;
  CompCtl1.Bits.En200ohmVsshiPncUp = (VssHiPanic.Bits.VsxHiPanicUpVref > 350);
  CompCtl1.Bits.DisableCompRotate = SAFE ? 1 : 0;
  CompCtl1.Bits.SelCompIntVrefSupply = DisVddqPathWithVddq;
  CompCtl1.Bits.DisableQuickComp = SAFE ? 1 : 0;
  CompCtl1.Bits.DisableOdtStatic = DataControl0.Bits.DisableOdtStatic;
  CompCtl1.Bits.CompClkOn = SAFE ? 1 : 0;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL1_REG, CompCtl1.Data);

  CompCtl2.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL2_REG);
  CompCtl2.Bits.Cmd200VrefDn = (191 * 100) / (100 + Inputs->RcompTarget[WrDSCmd]);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL2_REG, CompCtl2.Data);

  VssHiTarget.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG);
  TempVar1 = VsxHiTargetV * 382;
  TempVar2 = DIVIDEROUND (TempVar1, Vdd2Mv);
  SignedTempVar = TempVar2 - 32;
  VssHiTarget.Bits.CompVTarget = MAX (SignedTempVar, 0); // This is to protect that CompVTarget doesnt get a -ve value
  VssHiTarget.Bits.DataPattern = 1;
  VssHiTarget.Bits.EnPeriodicComp = 1;
  VssHiTarget.Bits.vtnslope = 22;
  TempVar1 = VccIoMv/64;
  SignedTempVar = TempVar1;
  SignedTempVar1 = DIVIDEROUND (-239, SignedTempVar);
  VssHiTarget.Bits.vtnoffset = MAX (SignedTempVar1, -32);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VSSHITARGET_REG, VssHiTarget.Data);

  VccDLLTarget.Data = 0;
  VccDLLTarget.Bits.CompVTarget = VccDllControl.Bits.Target;
  VccDLLTarget.Bits.OffsetBinSearch = SAFE ? 3 : 2;
  TempVar1 = 21 * (Vdd2Mv / 382);
  TempVar2 = VccIoMv / 128;
  TempVar3 = DIVIDEROUND (TempVar1, TempVar2);
  VccDLLTarget.Bits.VtpSlope = TempVar3;
  SignedTempVar = (Vdd2Mv / 96);
  SignedTempVar1 = DIVIDEROUND (-180, SignedTempVar);
  VccDLLTarget.Bits.VtpOffset = RANGE (SignedTempVar1, -32, 31);
  // @todo need more info on VccDLLTarget.Bits.CodeLeakSearch
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLTARGET_REG, VccDLLTarget.Data);

  VccDllReplicaCtrl0.Data = 0;
  VccDllReplicaCtrl0.Bits.TxPBDCode = 63;
  VccDllReplicaCtrl0.Bits.RxPBDCode = 63;
  VccDllReplicaCtrl0.Bits.SlaveRxPiCodeP = 8;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLREPLICACTRL0_REG, VccDllReplicaCtrl0.Data);

  MrcGetSetNoScope (MrcData, CmdDrvVrefUp, ReadCached, &GetSetVal);

  VccDllReplicaCtrl1.Data = 0;
  // VccDllReplicaCtrl1.Bits.CCCPBDCode = 63; //0x3F
  VccDllReplicaCtrl1.Bits.DisableDataPBDDLGating = 1;
  if (QclktoFreq <= 3200) {
    SignedTempVar = 105 -((DdrFrequency * 100) / 7100); // 1.05 scaled to 105
  }
  SignedTempVar1 = (SignedTempVar * 32) - 16;
  SignedTempVar1 /= 100; // Scale it back down
  VccDllReplicaCtrl1.Bits.ScaleIdle2Weak = RANGE (SignedTempVar1, -8, 7);
  VccDllReplicaCtrl1.Bits.MatchedPath = (!UnMatched) ? 1 : 0;
  VccDllReplicaCtrl1.Bits.LocalVsxHiBypass = VssHiBypassVddqMode;
  VccDllReplicaCtrl1.Bits.RloadVref = (UINT32) GetSetVal;
  VccDllReplicaCtrl1.Bits.RloadInstances = DIVIDEROUND (700, RExternal);
  // TempVar1 = BiasPwrMuxSelVdd2 ? VccIoMv : Vdd2Mv; // DataControl5.Bits.BiasPwrMuxSelVdd2 needs training so its 0 in ddrioint
  TempVar2 = 250 / Vdd2Mv;
  TempVar3 = ((TempVar2 * 1000000) - 125000); // scale it to nV
  TempVar4 = DIVIDEROUND (TempVar3, 31250);
  VccDllReplicaCtrl1.Bits.RxBiasVref = RANGE (TempVar4, 0, 7);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLREPLICACTRL1_REG, VccDllReplicaCtrl1.Data);

  VccDllDqsDelay.Data = 0;
  VccDllDqsDelay.Bits.RxClkDisRep = 2;
  VccDllDqsDelay.Bits.RxDqsSlope = 3;
  VccDllDqsDelay.Bits.RxDqsVref = 7;
  VccDllDqsDelay.Bits.DriftLimitLocal = (36 * 9) / ( (QclkPs >> Gear2) * 10);

  VccDllDqsDelay.Bits.TrainTargetOffsetUI = 1;
  VccDllDqsDelay.Bits.RxPBDCode = DIVIDEROUND (50, PBDStepSize);
  VccDllDqsDelay.Bits.DriftLimitGlobal = 15 / (QclkPs >> Gear2);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLDQSDELAY_REG, VccDllDqsDelay.Data);

  CCCVoltageUsed.Data = 0;
  CCCVoltageUsed.Bits.PredrvUseVcciog = CCCPredrvUseVcciog;
  CCCVoltageUsed.Bits.VssHiBypassVddqMode = VssHiBypassVddqMode;
  TempVar1 = (!CCCVoltageUsed.Bits.PredrvUseVcciog) & VssHiBypassVddqMode;
  CCCVoltageUsed.Bits.CaPDPreDrvVccddq  = TempVar1 & !CA_VOLT_SEL;
  CCCVoltageUsed.Bits.CtlPDPreDrvVccddq = TempVar1 & !CtlVoltSel;
  CCCVoltageUsed.Bits.ClkPDPreDrvVccddq = TempVar1 & !CLK_VOLT_SEL;
  CCCVoltageUsed.Bits.CaVoltageSelect = CA_VOLT_SEL;
  CCCVoltageUsed.Bits.CtlVoltageSelect = CtlVoltSel;
  CCCVoltageUsed.Bits.ClkVoltageSelect = CLK_VOLT_SEL;
  CCCVoltageUsed.Bits.VssHiBypassVdd2Mode = VssHiBypassVdd2Mode;
  CCCVoltageUsed.Bits.CkUseCtlComp = Lpddr5 ? 1 : 0;
  CCCVoltageUsed.Bits.CsUseCaComp = Lpddr4 ? 1 : 0;
  CCCVoltageUsed.Bits.CccStaticLegCtrl = 1;
  CCCVoltageUsed.Bits.DisVddqPathWithVddq = DisVddqPathWithVddq;
  //CCCVoltageUsed.Bits.XoverAdjustmentRsvd = 0;
  CCCVoltageUsed.Bits.XoverMinDelayCtl = 1;
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCCCVOLTAGEUSED_REG, CCCVoltageUsed.Data); // Multicast used

//---------------------------------------Vtt CRs----------------------------------------------------------------------------
  VttGenControl.Data = 0;
  TempVar1 = (382 * VttTargetV);
  TempVar2 = DIVIDEROUND (TempVar1, Vdd2Mv) - 32;
  // Assumes VttTargetV in LPDDR is 150mV based on the system studies.
  VttGenControl.Bits.Target = TempVar2;
  TempVar1 = (382 * PANICV0);
  TempVar2 = DIVIDEROUND (TempVar1, Vdd2Mv);
  VttGenControl.Bits.Panic0 = TempVar2;
  TempVar1 = (382 * PANICV1);
  TempVar2 = DIVIDEROUND (TempVar1, Vdd2Mv);
  VttGenControl.Bits.Panic1 = TempVar2;
  VttGenControl.Bits.Spare1 = SAFE ? 1 : 0;
  // VttGenControl.Bits.DisSensorPwrDn = SAFE ? 1 : 0; // Field no longer exists
  VttGenControl.Bits.EnDacPM = (Inputs->A0 || SAFE) ? 0 : 2;
  VttGenControl.Bits.DdrCRForceODTOn = (DataControl0.Bits.OdtForceQDrvEn || DataControl0.Bits.DdrCRForceODTOn) && VttGenControl.Bits.EnVttOdt;
  //This field is programmed in SetVtt function
 // VttGenControl.Bits.EnVttOdt = (DataControl0.OdtMode == 2 * Vtt);   // (DDRControl5.OdtMode == 2 (VTT))
  TempVar1 = (Ddr4 || Ddr5) ? 10 : 16; // MaxMin( RndUp( (DDR4or5?10nS:16nS)/tQCLK/8 )-1, 0, 7)
  TempVar2 = DIVIDEROUND (TempVar1, QclkPs);
  TempVar3 = DIVIDEROUND (TempVar2, 8) - 1;
  VttGenControl.Bits.WakeUpDelay = TempVar3;
  TempVar1 = (60 / RefClkPs) - 1;
  TempVar2 = MrcLog2(TempVar1);
  VttGenControl.Bits.LockTimer = TempVar2;
  VttGenControl.Bits.AckOffset = 1;
  VttGenControl.Bits.EnVttOdt = 1;
  MrcWriteCrMulticast (MrcData, DDRVTT_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data);

  VttGenControl.Bits.EnDacPM = 0;
  MrcWriteCR (MrcData, DDRVTT2_CR_DDRCRVTTGENCONTROL_REG, VttGenControl.Data); // 0x2A00 is VTTComb2 in TGL UY

  VttCompOffset.Data = MrcReadCR (MrcData, DDRVTT0_CR_DDRCRVTTCOMPOFFSET_REG);
  VttCompOffset2.Data = 0;
  VttCompOffset2.Bits.PanicLo0UsePmos = (VsxHiTargetV + (-PANICV0) + VttCompOffset.Bits.PanicLo0CompOfst) < 375;
  VttCompOffset2.Bits.PanicLo1UsePmos = (VsxHiTargetV + (-PANICV1) + VttCompOffset.Bits.PanicLo1CompOfst) < 375;
  VttCompOffset2.Bits.PanicHi0UsePmos = (VsxHiTargetV + (PANICV0) + VttCompOffset.Bits.PanicHi0CompOfst)  < 375;
  VttCompOffset2.Bits.PanicHi1UsePmos = (VsxHiTargetV + (PANICV1) + VttCompOffset.Bits.PanicHi1CompOfst)  < 375;
  MrcWriteCrMulticast (MrcData, DDRVTT_CR_DDRCRVTTCOMPOFFSET2_REG, VttCompOffset2.Data);
//---------------------End of Early Init---------------------------------------------------
//---------------------Start of Late Init--------------------------------------------------
  DataControl6.Data = 0;
  // Depends on Read Postamble number of toggles.  Since unmatched is only LPDDR5, we have 4 toggles.
  // RcvEnPre is allowed at assert when (0: RxDqs is low, 1: RxDqs falling edge).  PassRcvenOnDqsFall = Unmatched Path
  if (UnMatched) {
    PassRcvEn = 1;
    if (Lpddr4) {
      RcvEnWaveShape = 1;
      NumToggles = 0;
      ResetNumPre = 0;
    } else {
      // LPDDR5
      NumToggles = 1;
      ResetNumPre = 4;
      RcvEnWaveShape = (Gear2) ? 2 : 3;
    }
  } else {
    // Matched path
    RcvEnWaveShape = 0;
    NumToggles = 0;
    PassRcvEn = 0;
    ResetNumPre = 0;
  }

  if (QclktoFreq >= 3200) {
    RightShift = 28;
  } else if (QclktoFreq >= 2667) {
    RightShift = 24;
  } else if (QclktoFreq >= 2400) {
    RightShift = 20;
  } else if (QclktoFreq >= 2133) {
    RightShift = 16;
  } else if (QclktoFreq >= 1867) {
    RightShift = 12;
  } else if (QclktoFreq >= 1600) {
    RightShift = 8;
  } else if (QclktoFreq >= 1333) {
    RightShift = 4;
  } else {
    RightShift = 0;
  }
  TempVar1 = CBTune0 >> RightShift;
  TempVar1 &= 0xF;
  DataControl6.Bits.sdllbwctrl = TempVar1;
  MrcGetSetChStrb (MrcData, FirstController, FirstChannel, FirstByte, RxCben, ReadCached | PrintValue, &GetSetVal);
  DataControl6.Bits.sdll_picb = (UINT32) GetSetVal;
  DataControl6.Bits.rxd0picb = (UINT32) GetSetVal;
  DataControl6.Bits.rxd0bwctrl = TempVar1;
  DataControl6.Bits.UseDefaultRdPtrCalc = 1;
  DataControl6.Bits.RstNumPre = ResetNumPre;
  DataControl6.Bits.PassRcvenOnDqsFall = PassRcvEn;
  DataControl6.Bits.RXTogglePreAmble = NumToggles; //in tCK
  DataControl6.Bits.RcvEnWaveShape = RcvEnWaveShape;
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRCRDATACONTROL6_REG, DataControl6.Data);

  VccDllReplicaCtrl2.Data = 0;
  VccDllReplicaCtrl2.Bits.DisableTxDqs = Lpddr5;
  SignedTempVar = ((-333 * Vdd2Mv) + 42) / 10000; // PBiasCalibration is 3 bits field therefore Vdd2 must be considered in V. Multiply and divide by 10 to convert 33.3
  VccDllReplicaCtrl2.Bits.PbiasCalibration = (UINT32) SignedTempVar;
  VccDllReplicaCtrl2.Bits.SdllPiCB = DataControl6.Bits.sdll_picb;
  VccDllReplicaCtrl2.Bits.LeakScale = VccDllReplicaCtrl2.Bits.SdllPiCB; //Fixed Value (TBD based on tester silicon measurements.PreSilicon sims indicate 0x7 but believe this is too high)
  VccDllReplicaCtrl2.Bits.SdllBwCtrl = DataControl6.Bits.sdllbwctrl;
  VccDllReplicaCtrl2.Bits.RxD0BWCtrl = DataControl6.Bits.rxd0bwctrl;
  VccDllReplicaCtrl2.Bits.RxD0BWCtrl = DataControl6.Bits.rxd0picb;
  //VccDllReplicaCtrl2.Bits.RxPwrMuxSelVdd2 = DataControl3.Bits.RxPwrMuxSelVdd2; //DataControl3.Bits.RxPwrMuxSelVdd2 needs training
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_REG, VccDllReplicaCtrl2.Data);


  DataControl3.Bits.VrefBypassVssHi = ((VccddqMv - VsxHiTargetV) < VDD_0_75) ? 1 : 0;
  DataControl3.Bits.RxPwrMuxSelVdd2 = DataControl5.Bits.BiasPwrMuxSelVdd2;
  DataControl3.Bits.VrefPwrMuxSelVdd2 = (TargetVsxHi >= ((7 * Vdd2Mv) / 100));
  DataControl3.Bits.RxSALTailCtrl = 2; //   Adjust based on Vtp or (VccIoMv-Vtp)?
  DataControl3.Bits.wrpreamble = Lpddr4 ? 1 : 0;
  DataControl3.Bits.QualifySdlWithRcvEn = UnMatched ? 0 : 1;
  DataControl3.Bits.rxfoldcs = NPath ? 3 : 0;
  DataControl3.Bits.dqspadmuxselvdd2 = DataControl5.Bits.BiasPwrMuxSelVdd2;
  // DataControl3.Bits.TxDqsRankMuxDelay_2nd_stage_offset = 0 ;
  DataControl3.Bits.DisableTxDqs = Lpddr5;
  DataControl3.Bits.RxPBDCalibration = VccDllReplicaCtrl2.Bits.RxDeskewCal; // RxDeskewCal needs CAScomp training
  // DataControl3.Bits.TxRankMuxDelay_2nd_stage_offset = 0 ;
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRCRDATACONTROL3_REG, DataControl3.Data);

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    ControllerOut = &Outputs->Controller[Controller];
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        ChannelOut = &ControllerOut->Channel[Channel];
        Is2DPC = (ChannelOut->DimmCount == 2);
        if (Lpddr) {
          ByteStart = (MAX_BYTE_IN_LP_CHANNEL * Channel);
          ByteEnd = ByteStart + MAX_BYTE_IN_LP_CHANNEL;
        }
        for (Byte = ByteStart; Byte < ByteEnd; Byte++) {
          DataControl2.Bits.DqSlewDlyByPass = !(Ddr && Is2DPC);
          //DataControl2.Bits.RxVrefVddqProgMFC = 0;//  @todo : field requires training
          //DataControl2.Bits.RxVrefVttProgMFC = 0;//  @todo : field requires training
          // @todo : CRC isnt currently supported
          TempVar1 = DataControl3.Bits.QualifySdlWithRcvEn ? 5500 : 6800;
          TempVar2 = UnMatched ? TempVar1 : 11000;
          TempVar3 = DataControl3.Bits.QualifySdlWithRcvEn ? 1200 : 1900;
          TempVar4 = UnMatched ? TempVar3 : 2500;
          EnDqsNRcvEnSet = Lpddr && ((DdrFrequency > (Lpddr4 ? TempVar4 : TempVar2)));
          DataControl2.Bits.EnDqsNRcvEn = EnDqsNRcvEnSet;
          //DataControl2.Bits.xover_mindelay_ctl = 0;
          //DataControl2.Bits.xover_adjustment_rsvd = 0;
          DataControl2.Bits.DisableDqsOdtStatic = (OdtTarget > 120);
          DataControl2.Bits.TxPBDCalibration = VccDllReplicaCtrl2.Bits.TxDeskewCal; //@ Program after CA Scomp training
          DataControl2.Bits.EnConstZEqTx = 1;
          //DataControl2.Bits.TxEqDis = 0;
          Offset = DataControl2Offset (Controller, Byte);
          MrcWriteCR (MrcData, Offset, DataControl2.Data);
        }
      } // ChannelExist
    }
  } // Controller

  TargetNUI = (Gear2) ? 1 : 0;
  RcompData0.Data = 0;
  RcompData0.Bits.DqsNTargetNUI = TargetNUI;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP0_REG, RcompData0.Data);
  RcompData1.Data = 0;
  RcompData1.Bits.DqsPTargetNUI = TargetNUI;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMP1_REG, RcompData1.Data);

  MarginModeControl.Data = 0;
  MarginModeControl.Bits.MinWidth = 0x4;
  MarginModeControl.Bits.CalcCenter = 1;
  MarginModeControl.Bits.IOLBCycles = 0xA;
  // MarginModeControl.Bits.IOLBCpgcMode = 1;
  // MarginModeControl.Bits.MisrRunOvrd = 1;
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRCRMARGINMODECONTROL0_REG, MarginModeControl.Data);

  DataDqsRankX.Data = 0;
  DataDqsRankX.Bits.DqsPfNrTcoDelay = 16;
  DataDqsRankX.Bits.DqsPrNfTcoDelay = 16;
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRDATADQSRANK0_REG,DataDqsRankX.Data);
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRDATADQSRANK1_REG, DataDqsRankX.Data);
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRDATADQSRANK2_REG, DataDqsRankX.Data);
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRDATADQSRANK3_REG, DataDqsRankX.Data);

//-----------------------------------CCC Registers----------------------------------------------------------------------------------
  CCCClkControls.Data = 0;
  if (SAFE) {
    CCCClkControls.Bits.ClkGateDisable = 1;
    CCCClkControls.Bits.IntCkOn = 1;
    CCCClkControls.Bits.CkeIdlePiGateDisable = 1;
    CCCClkControls.Bits.CaValidPiGateDisable = 1;
  } else {
    CCCClkControls.Bits.DefDrvEnLow = Ddr4 ? 3 : 2; // Initial value (Ddr4 ? 0x3 : 0x2) but power training can try 0x1 for Ddr4 or weak Rodt.
  }
  CCCClkControls.Bits.RTO = Ddr5 ? 1 : 0;
  CCCClkControls.Bits.BlockTrainRst = 1;
  CCCClkControls.Bits.CtlSRDrv = (SAFE || (!Ddr4)) ? 0 : 2;
  CCCClkControls.Bits.c3segsel_b_for_cke = (SAFE || Ddr5) ? 1 : 0;
  if (Ddr4) {
    CCCClkControls.Bits.CaTxEq  = TXEQ_NODEEMPHASIS;
    CCCClkControls.Bits.CtlTxEq = TXEQ_NODEEMPHASIS;
    CCCClkControls.Bits.ClkTxEq = TXEQ_NODEEMPHASIS;
  } else {
    CCCClkControls.Bits.CaTxEq  = (TXEQ_NODEEMPHASIS | TXEQ_CONSTATNTZ);
    CCCClkControls.Bits.CtlTxEq = (TXEQ_NODEEMPHASIS | TXEQ_CONSTATNTZ);
    if (Lpddr && !Inputs->A0) {
      CCCClkControls.Bits.ClkTxEq = 0x6;
    } else {
      CCCClkControls.Bits.ClkTxEq = (TXEQ_NODEEMPHASIS | TXEQ_CONSTATNTZ);
    }
  }


  //Only important for Ddr4.  All others can use `0 since termination is off or to Vss.
  CCCClkControls.Bits.CtlSRDrv = Ddr4 ? 2 : 0;
 // Only important for Ddr4.  All others can use `0 since termination is off or to Vss.
  if (Ddr) {
    //CCCClkControls.Bits.Spare             = 125 > ((Vdd2Mv * Rodt) / (2 * (3 * (RonCtlTarget + Rodt)))) ? 0 : 1;
    CCCClkControls.Bits.RxVref            = 150 > ((Vdd2Mv * Rodt) / (2 * (3 * (RonCtlTarget + Rodt)))) ? 1 : 2;
  }
  CCCClkControls.Bits.c3segsel_b_for_cke = ~(Ddr4);
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCCCCLKCONTROLS_REG, CCCClkControls.Data);

 // @todo : Program after SAComp
  CCCPerBitDeskew0.Data = 0;
  CCCPerBitDeskew0.Bits.deskewcal = VccDllReplicaCtrl2.Bits.CCCDeskewCal;
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCCCPERBITDESKEW0_REG, CCCPerBitDeskew0.Data);

 // @todo : Uncomment when the value of TurnOnDelay is provided
 // TempVar1 = 5 * QclkPs;
 // TempVar2 = 10 * TurnOnDelay;
 // TempVar3 = DIVIDEROUND (TempVar2, TempVar1);
 //CCCPerBitDeskew1.Bits.FFPBDDelay = RANGE(TempVar3, 0, 2);
  CCCPerBitDeskew1.Data = 0;
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCCCPERBITDESKEW1_REG, CCCPerBitDeskew1.Data);

  CCCPerBitDeskew2.Bits.txdeskewpoweren = 1;
  MrcWriteCrMulticast (MrcData, CCC_CR_DDRCRCCCPERBITDESKEW2_REG, CCCPerBitDeskew2.Data);

  for (Channel = 0; Channel < MRC_NUM_CCC_INSTANCES; Channel++) {
    CCCMisr.Bits.EnLFSR = 1;
    Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRMISR_REG, CH1CCC_CR_DDRCRMISR_REG, Channel);
    MrcWriteCR (MrcData, Offset, CCCMisr.Data);
  }

    // Use SAFE for DLLPITESTANDADC settings
  DataDllPiTestAndAdc.Data = 0;
  DataDllPiTestAndAdc.Bits.PhaseDrvPwrSavOn = 1;
  // Multicast all DLLPITESTANDADC.  Each Fub has same CR layout.
  MrcWriteCrMulticast (MrcData, DLLDDR_CR_DLLPITESTANDADC_REG, DataDllPiTestAndAdc.Data);

  VccDllFFControl.Data = 0;
  VccDllFFControl.Bits.Bypass = SAFE ? 1 : 0;
  VccDllFFControl.Bits.LocalVsxHiBypass = VssHiBypassVddqMode;
  VccDllFFControl.Bits.VccdllPwrMuxSel = ((VccIoMv - MRC_VCCDLL_TARGET) < SevenPercentOfVccIoMv);
  DataDllPiTestAndAdc.Data = MrcReadCR(MrcData, DLLDDRDATA0_CR_DLLPITESTANDADC_REG);
  VccDllFFControl.Bits.VccdllMdllPwrSave   = (DataDllPiTestAndAdc.Bits.PhaseDrvPwrSavOn == 1);
  VccDllFFControl.Bits.VccdllPiPwrSave     = (DataDllPiTestAndAdc.Bits.PhaseDrvPwrSavOn == 1);
  MrcWriteCrMulticast (MrcData, DLLDDR_CR_DDRCRVCCDLLFFCONTROL_REG, VccDllFFControl.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SdramCount: 0x%X\n",Outputs->SdramCount );

//--------------------------------------Comp CRs----------------------------------------------------------------------------
  CompAlert.Data = 0;
  CompAlert.Bits.AlertVref = (192 / 2) * ((34 + Rup + 34) / (34 + Rup));
  CompAlert.Bits.AlertEn = (Ddr4 || Ddr5);
  TempVar1 = (((CompAlert.Bits.AlertVref / 191) * VccddqMv) - 600);
  TempVar2 = DIVIDEROUND (TempVar1, 50);
  CompAlert.Bits.AlertCMCap = RANGE (TempVar2, 0, 7);

  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRALERT_REG, CompAlert.Data);

// --------------------- CLOCK and MCMISCS CRs - Added in MAS_80----------------------------------------------------------------------
  McMiscSpineGating.Data = 0;
  TempVar1 = DIVIDEROUND (160000, QclkPs);
  if ((TempVar1 > 128) && (TempVar1 <= 192)) {
    TempVar2 = 1;
  } else if ((TempVar1 > 192) && (TempVar1 <= 256)) {
    TempVar2 = 2;
  } else if ((TempVar1 > 256) && (TempVar1 <= 384)) {
    TempVar2 = 3;
  } else if ((TempVar1 > 384) && (TempVar1 <= 512)) {
    TempVar2 = 4;
  } else if ((TempVar1 > 512) && (TempVar1 <= 768)) {
    TempVar2 = 5;
  } else if ((TempVar1 > 768) && (TempVar1 <= 1024)) {
    TempVar2 = 6;
  } else if ((TempVar1 > 1024) && (TempVar1 <= 1536)) {
    TempVar2 = 7;
  } else {
    TempVar2 = 0;
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Condition didnt meet any of the allowed Sleepcycles values, default SleepCycles = %d\n", TempVar2);

  McMiscSpineGating.Bits.SleepCycles = TempVar2;
  McMiscSpineGating.Bits.AwakeCycles = 2;
  McMiscSpineGating.Bits.EnHiPhase = 2;
  McMiscSpineGating.Bits.GraceLimitEntry = SAFE ? 7 : 3;
  MrcWriteCR (MrcData, MCMISCS_SPINEGATING_REG, McMiscSpineGating.Data);

  DdrScramCh0.Data = MrcReadCR (MrcData, DDRSCRAM_CR_DDRSCRAMBLECH0_REG);
  DdrScramCh0.Bits.dis_cmdanalogen = SAFE ? 0 : 1;
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRSCRAMBLECH0_REG, DdrScramCh0.Data);

  DdrScramCh1.Data = MrcReadCR (MrcData, DDRSCRAM_CR_DDRSCRAMBLECH1_REG);
  DdrScramCh1.Bits.Spare = SAFE ? 0 : 1;
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRSCRAMBLECH1_REG, DdrScramCh1.Data);

  DdrScramCh2.Data = MrcReadCR (MrcData, DDRSCRAM_CR_DDRSCRAMBLECH2_REG);
  DdrScramCh2.Bits.Spare = SAFE ? 0 : 1;
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRSCRAMBLECH2_REG, DdrScramCh2.Data);

  MiscControl1.Data = MrcReadCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL1_REG);
  MiscControl1.Bits.CompAndDeltaDqsUpdateClkGateDisable = SAFE ? 1 : 0;
  MiscControl1.Bits.BGBiasTrim = 4;
  MiscControl1.Bits.BGAgshTrim = ((VCCANA_EH > 1800) ? 3 : ((VCCANA_EH > 1550) ? 0 : ((VCCANA_EH > 1300) ? 1 : 2)));
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL1_REG, MiscControl1.Data);

  MiscControl2.Data = MrcReadCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL2_REG);
  MiscControl2.Bits.rx_analogen_grace_cnt = DDRSCRAM_CR_DDRMISCCONTROL2_rx_analogen_grace_cnt_MAX;
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL2_REG, MiscControl2.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DDRMISCCONTROL2 = 0x%X\n", MiscControl2.Data);

  MiscControl7.Data = 0;
  // MRC tracks BurstLength in tCK, which is DCLK for LP4/DDR4.
  //LP5 is not Dclk due to 4:1 scaling.  WCK is the equivalent to DCLK.  Thus we multiply by 4.
  Data32 = Outputs->BurstLength;
  if (Lpddr5) {
    Data32 *= 4;
  }
  MiscControl7.Bits.RxBurstLen = Data32;
  MiscControl7.Bits.TxBurstLen = Data32;
  MiscControl7.Bits.Cas2FSWCk = (MrcGetWckEnlFs (MrcData) * 4) + ((Gear2) ? -1 : 1);
  MiscControl7.Bits.CmdDuration = Ddr4 ? 0 : Lpddr5 ? 7 : 3;
  MiscControl7.Bits.Run1stComp = (Inputs->TrainingEnables2.DCC) ? 1 : 0;
  MiscControl7.Bits.DataInvertNibble = DataInvertNibble;
  MiscControl7.Bits.TrainWCkSyncRatio = 2;
  MrcWriteCR (MrcData, DDRSCRAM_CR_DDRMISCCONTROL7_REG, MiscControl7.Data);
  // Select the DDRIO ODT Mode. This also programs default RxVref.
  MrcSetIoOdtMode (MrcData, Outputs->OdtMode);

  CompCtl4.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL4_REG);
  TempVar2 = DIVIDEROUND (22000, QclkPs); //Scaled 22ns to 22000ps
  TempVar3 = DIVIDEROUND (TempVar2, 8);
  CompCtl4.Bits.CompInitDelay = SAFE ? 7 : (TempVar3 - 2);
  CompCtl4.Bits.CompCodeSwitch = CompCtl4.Bits.CompInitDelay;
  CompCtl4.Bits.SWCapUseVdd2 = SAFE ? 1 : (VccIoMv < 950);
  TempVar1 = (!CCCPredrvUseVcciog) && VssHiBypassVddqMode;
  CompCtl4.Bits.CaPDPreDrvCVccddq = CCCVoltageUsed.Bits.CaPDPreDrvVccddq;
  CompCtl4.Bits.CtlPDPreDrvCVccddq = CCCVoltageUsed.Bits.CtlPDPreDrvVccddq;
  CompCtl4.Bits.ClkPDPreDrvCVccddq = CCCVoltageUsed.Bits.ClkPDPreDrvVccddq;
  CompCtl4.Bits.DqPDPreDrvCVccddq = (TxDqPUpPreDrvVccddq && VssHiBypassVddqMode);
  if ((TargetVsxHi > 450) || (TargetVsxHi < 100)) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "TargetVsxHi is out of range: %d, it should be within 100mV to 450mV\n",TargetVsxHi);
  }
  TempVar1 = RANGE (TargetVsxHi, 100, 450);
  SignedTempVar  = VccddqMv - Vdd2Mv;
  SignedTempVar1 = VccddqMv - (Vdd2Mv - TempVar1);
  ObeyDDQBypassB0 = (ABS (SignedTempVar) < ABS (SignedTempVar1));
  ObeyDDQBypassA0 = (ObeyDDQBypassB0 && VssHiBypassVddqMode && VssHiBypassVddqMode);
  CompCtl4.Bits.ObeyDDQBypass = Inputs->A0 ? ObeyDDQBypassA0 : ObeyDDQBypassB0;
  TempVar1 = (CA_VOLT_SEL) ? 80000 : 22000;
  TempVar2 = DIVIDEROUND (TempVar1, QclkPs);
  CompCtl4.Bits.CompStage2Switch = TempVar2;
  TempVar1 = CLK_VOLT_SEL ? 80000 : 22000;
  TempVar2 = DIVIDEROUND (TempVar1, QclkPs);
  CompCtl4.Bits.CompStage3Switch = TempVar2;
  TempVar1 = ((CLK_VOLT_SEL != CtlVoltSel) | (CA_VOLT_SEL != CLK_VOLT_SEL)) ? 80000 : 22000;
  TempVar2 = DIVIDEROUND (TempVar1, QclkPs);
  CompCtl4.Bits.CompStage4Switch = TempVar2;
  TempVar1 = ((CompCtl0.Bits.EnVttOdt | CompCtl0.Bits.EnVddqOdt) & (CtlVoltSel)) ? 80000 : 22000;
  TempVar2 = DIVIDEROUND (TempVar1, QclkPs);
  CompCtl4.Bits.CompStage5Switch = TempVar2;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL4_REG, CompCtl4.Data);

  // Configure Strobe
  MrcSetWritePreamble (MrcData);

  //---------------------------------Initialize FLL CRs------------------------------------------------------------------------
  FllCmdCfg.Data = MrcReadCR (MrcData, FLL_CMD_CFG_REG_REG);
  TempVar1 = (RefClkMhz == MRC_REF_CLOCK_133) ? 66 : 100;
  FllCmdCfg.Bits.FLL_RATIO = 3133 / TempVar1;

  MrcWriteCR (MrcData, FLL_CMD_CFG_REG_REG, FllCmdCfg.Data);

  FllStaticCfg0.Data = MrcReadCR (MrcData, FLL_STATIC_CFG_0_REG_REG);
  FllStaticCfg0.Bits.LDO_VREFSEL = ((Vdd2Mv >= 1075) && (Vdd2Mv <= 1150)) ? 3 : 4;
  FllStaticCfg0.Bits.FAST_CAL_WINDOW_VAL = 0x0;
  FllStaticCfg0.Bits.SLOW_CAL_WINDOW_VAL = 0x2;
  MrcWriteCR (MrcData, FLL_STATIC_CFG_0_REG_REG,  FllStaticCfg0.Data);

  FllStaticCfg1.Data = MrcReadCR (MrcData, FLL_STATIC_CFG_1_REG_REG);
  FllStaticCfg1.Bits.REFCLK_DIVIDE_RATIO_SEL = (RefClkMhz == MRC_REF_CLOCK_133) ? 2 : 1;
  FllStaticCfg1.Bits.COARSECAL_CNTR_EN = 0xF;
  FllStaticCfg1.Bits.FINECAL_CNTR_EN = 0x2;
  if (Vdd2Mv > 1150) {
    FllStaticCfg1.Bits.VSUPPLY_CFG = 1;
  }
  MrcWriteCR (MrcData, FLL_STATIC_CFG_1_REG_REG,  FllStaticCfg1.Data);

  MrcWriteCR (MrcData, FLL_STATIC_CFG_2_REG_REG, MrcReadCR (MrcData, FLL_STATIC_CFG_2_REG_REG));

  FllWired.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRFLLWIRED_REG);
  FllWired.Bits.FllWireRatio = (FllStaticCfg1.Bits.REFCLK_DIVIDE_RATIO_SEL == 2) ? 47 : 31;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRFLLWIRED_REG, FllWired.Data);
  //-----------------------------------------------------------------------------------------------------------------------------

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init Data CRs\n");
  // Initialize the Receive Enable Delay Fields, RX FIFO Delays, and Roundtrip Latency.
  // Even though Roundtrip Latency is in the MC domain, it depends on RX IO delays, so we will init it here.
  // Cached fields sits in cache until later flush call.
  // DdrIoInit above was done with CR multicast.  Cache may have some other values in it causing register corruption.
  // Invalidate cache here to cause GetSet to RMW.
  InitializeRegisterCache (MrcData);

  if (Lpddr4) {
    TdqsckMin = tDQSCK_MIN_LP4;
  } else {
    TdqsckMin = 0;
  }
  TdqsckMin = DIVIDECEIL (TdqsckMin, QclkPs);
  GetSetVal2 = 0; // RxFlybyDelay(Dclk)
  RxDataValidDclk = Gear2 ? 14 : 7;  // RTL constant
  RxDataValidQclk = 0;  // RTL constant

  // initial CLK/CTL PI
  ClkDelay = CtlPiDelay / 64; // Convert PI to QCLKs

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      TimingProfile = &Outputs->Controller[Controller].Channel[Channel].Timing[Profile];
      tCL = (UINT8) TimingProfile->tCL;
      if (Lpddr5) {
        // Scale to WCK which matches QCLK in the IO.
        tCL *= 4;
      }
      RcvEnPi[Controller][Channel] = (Lpddr5 ? 0 : 128) + (Gear2 ? 0 : CtlPiDelay) + (Ddr4 ? 32 : 0);  // Start from CTL PI value
      Data32 = (tCL * (2 - Gear2)) + TdqsckMin;
      Data32 = Data32 - ((Gear2) ? 10 : 15);
      Data32 -= (Controller ? 4 : 0); // Adjust delay for MC1
      if (!Gear2) {
        RcvEnPi[Controller][Channel] += ((Data32 % 2) * 64);   // If odd number of QCLKs, add one 1 QCLK to RcvEnPi
      } else if (Lpddr4) {
        Data32 -= 1;
      } else if (Lpddr5) {
        Data32 -= 8;
      }
      tCL4RcvEn = Data32 / (2 - Gear2); // RxIoTclDelay (tCK)

      tCL4RxDqFifoRdEn = tCL4RcvEn;
      tCL4RxDqFifoRdEn += RxFifoChDelay[DdrType][Gear2][(Controller * MaxChannels) + Channel];
      RxDqFifoRdEnRankDel = DIVIDECEIL ((UINT32) RcvEnPi[Controller][Channel], PiToQclk);
      RxDqFifoRdEnRankDel += ClkDelay;
      Data32 = (UINT32) ((((UINT32) tCL4RxDqFifoRdEn) * (2 - Gear2)) + RxDqFifoRdEnRankDel);
      Data32 += 10 + 2;
      if (Gear2) {
        // DDR4 or LP4 or LP5
        Data32 += (Ddr4) ? 10 : (Lpddr4) ? 11 : 16;
      } else {
        // DDR4 or LP4/5
        Data32 += (Ddr4) ? 16 : 18;
      }
      Roundtrip = Data32;
      MrcGetSetMcCh (MrcData, Controller, Channel, RxIoTclDelay,           WriteToCache | PrintValue, &tCL4RcvEn);
      MrcGetSetMcCh (MrcData, Controller, Channel, RxFifoRdEnTclDelay,     WriteToCache | PrintValue, &tCL4RxDqFifoRdEn);
      MrcGetSetMcCh (MrcData, Controller, Channel, RxDqDataValidDclkDelay, WriteToCache | PrintValue, &RxDataValidDclk);
      MrcGetSetMcCh (MrcData, Controller, Channel, RxDqDataValidQclkDelay, WriteToCache | PrintValue, &RxDataValidQclk);
      MrcGetSetMcChRnk (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, RxFlybyDelay,         WriteToCache | PrintValue, &GetSetVal2);
      MrcGetSetMcChRnk (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, RxFifoRdEnFlybyDelay, WriteToCache | PrintValue, &RxDqFifoRdEnRankDel);
      MrcGetSetMcChRnk (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, RoundTripDelay,       WriteNoCache | PrintValue, &Roundtrip);
    } // Channel
  } // Controller

  // Initialize TX FIFO
  // Cached fields sits in cache until later flush call.
  GetSetVal3  = 0; // TxDqFifoRdEnFlybyDelay(Dclk), RptChRepClkOn, TxDqFifoRdEnPerRankDelDis
  GetSetVal4  = 7; // CmdAnlgEnGraceCnt
  GetSetVal5  = MCMISCS_WRITECFGCH0_TxAnlgEnGraceCnt_MAX; // TxAnlgEnGraceCnt
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      IpChannel = LP_IP_CH (Lpddr, Channel);
      TimingProfile = &Outputs->Controller[Controller].Channel[Channel].Timing[Profile];
      tCWL = TimingProfile->tCWL;
      if (Lpddr5) {
        // Scale to WCK which aligns to QCLK in the IO.
        tCWL *= 4;
      }

      ScWrDelay.Data = 0; // @todo: GetSet
      AddTcwl = 0;
      DecTcwl = 2;
      DecTcwl = MIN (DecTcwl, (UINT8) tCWL + AddTcwl - 2);
      DecTcwl += (Controller ? 2 : 0); // Adjust delay for MC1
      ScWrDelay.Bits.Add_tCWL = AddTcwl;
      ScWrDelay.Bits.Dec_tCWL = DecTcwl;

      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_WR_DELAY_REG, MC1_CH0_CR_SC_WR_DELAY_REG, Controller, MC0_CH1_CR_SC_WR_DELAY_REG, IpChannel);
      MrcWriteCR (MrcData, Offset, ScWrDelay.Data);
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Mc%d C%d Dec_tCWL: %d\n", Controller, Channel, ScWrDelay.Bits.Dec_tCWL);

      if (Gear2) {
        tCWL4TxDqFifoWrEn = tCWL - (2 * DecTcwl) - (Lpddr ? 1 : 3) + (tCWL % 2) - 2 * Lpddr * (tCWL % 2);
        if (Lpddr5) {
          tCWL4TxDqFifoWrEn -= 8;
        }
      } else {
        tCWL4TxDqFifoWrEn  = tCWL - DecTcwl + AddTcwl - 2; // TxDqFifoWrEnTcwlDelay(DClk)
      }
      tCWL4TxDqFifoRdEn  = tCWL4TxDqFifoWrEn - 1; // TxDqFifoRdEnTcwlDelay(DCLK)
      tCWL4TxDqFifoRdEn -= 1; // txdqs_section_rep is 7
      if (Lpddr4) {
        tCWL4TxDqFifoRdEn -= (Gear2 ? 2 : 1);  // On LP4 subtract 1 due to 2tCK WRPRE
      } else if (Lpddr5) {
        tCWL4TxDqFifoRdEn -= 1;
      }
      MrcGetSetMcCh (MrcData, Controller, Channel, TxDqFifoWrEnTcwlDelay,           WriteToCache | PrintValue, &tCWL4TxDqFifoWrEn);
      MrcGetSetMcCh (MrcData, Controller, Channel, TxDqFifoRdEnTcwlDelay,           WriteToCache | PrintValue, &tCWL4TxDqFifoRdEn);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmIocRptChRepClkOn,             WriteToCache | PrintValue, &GetSetVal3);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmIocTxDqFifoRdEnPerRankDelDis, WriteToCache | PrintValue, &GetSetVal3);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmIocCmdAnlgEnGraceCnt,         WriteToCache | PrintValue, &GetSetVal4);
      MrcGetSetMcCh (MrcData, Controller, Channel, GsmIocTxAnlgEnGraceCnt,          WriteToCache | PrintValue, &GetSetVal5);
      MrcGetSetMcChRnk (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, TxDqFifoRdEnFlybyDelay, WriteToCache | PrintValue, &GetSetVal3);
    } // Channel
  } // Controller

  // Initialize Rx and Tx Data CRs
  // RxDqsN/P_Pi = 32, RcvEn = 64
  RxDqsPPi    = 32;
  RxDqsNPi    = 32;
  RxEqInit    = 0xA;
  RxCInit     = 0x1;
  RxRInit     = 0x1;
  RxTap0Init  = 0xA;
  RxTap1Init  = 0x5;
  RxDqBitPi   = 0;  // Program to center (0 offset)

  // Set TxEq to full strength, TxDqs = 0 and TxDq = 32,
  TxEqInit    = 0xA; // Full Drive
  TxDqsPi     = 64;
  TxDqPi      = TxDqsPi + (Gear2 ? 96 : 32);
  TxDqBitPi = 0;
  // Rx Amplifier voltage offset {0: Most negative offset,... 15: zero offset, ... 30: Most positive offset}
  MrcGetSetLimits (MrcData, RxVoc, &MinVal, &MaxVal, NULL);
  GetSetVal = ((UINT32) (MaxVal - MinVal)) / 2;
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      // RxGroup
      if (Outputs->RxMode == MrcRxModeUnmatchedRxWRload || Outputs->RxMode == MrcRxModeUnmatchedRxWPpath) {
        MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxTap0, WriteToCache | PrintValue, &RxTap0Init);
        MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxTap1, WriteToCache | PrintValue, &RxTap1Init);
      } else {
        MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxEq, WriteToCache | PrintValue, &RxEqInit);
        MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxC, WriteToCache | PrintValue, &RxCInit);
        MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxR, WriteToCache | PrintValue, &RxRInit);
      }
      MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsNDelay, WriteToCache | PrintValue, &RxDqsNPi);
      MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsPDelay, WriteToCache | PrintValue, &RxDqsPPi);
      MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RecEnDelay,  WriteToCache | PrintValue, &RcvEnPi[Controller][Channel]);
      MrcGetSetBit (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, RxDqBitDelay,    WriteToCache | GSM_UPDATE_HOST | PrintValue, &RxDqBitPi);
      MrcGetSetBit (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, RxVoc,           WriteToCache | PrintValue, &GetSetVal);
      MrcGetSetBit (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, RxVocUnmatched,  WriteToCache | PrintValue, &GetSetVal);
      MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, RxDqsAmpOffset,         WriteToCache | PrintValue, &GetSetVal);
      // TxGroup
      MrcGetSetBit (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, TxDqsBitDelay, WriteToCache | GSM_UPDATE_HOST | PrintValue, &TxDqBitPi);
      MrcGetSetBit (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, MAX_BITS, TxDqBitDelay, WriteToCache | GSM_UPDATE_HOST | PrintValue, &TxDqBitPi);
      MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, TxEq,        WriteToCache | PrintValue, &TxEqInit);
      MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, TxDqDelay,   WriteToCache | PrintValue, &TxDqPi);
      MrcGetSetStrobe (MrcData, Controller, Channel, MAX_RANK_IN_CHANNEL, MAX_SDRAM_IN_DIMM, TxDqsDelay,  WriteToCache | PrintValue, &TxDqsPi);
    } // Channel
  } // Controller
  // Set Rx/Tx per-bit deskew step size to Single Step (x1)
  MrcGetSetNoScope (MrcData, GsmIocVccDllRxDeskewCal, WriteToCache, &GetSetDis);
  MrcGetSetNoScope (MrcData, GsmIocVccDllTxDeskewCal, WriteToCache, &GetSetDis);
  MrcFlushRegisterCachedData (MrcData);

  // Initial value to corresponding 0.
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRCRDATAOFFSETTRAIN_REG, 0x0);
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRCRDATAOFFSETCOMP_REG, 0x0);

  // Initialize DataControl0:6
  GetSetVal = SAFE ? 1 : (Lpddr) ? 1 : 0;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataDqOdtParkMode, WriteToCache, &GetSetVal);
  GetSetVal = (Lpddr4) ? 2 : (Lpddr5) ? 3 : 0; // DDR4 is the last case
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataDqsOdtParkMode, WriteToCache, &GetSetVal);
  GetSetVal = RxMode;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxVocMode,  WriteToCache, &GetSetVal);
  GetSetVal = StaticOdtDis;
  MrcGetSetNoScope (MrcData, GsmIocCompOdtStaticDis, WriteToCache | PrintValue, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataOdtStaticDis, WriteToCache | PrintValue, &GetSetVal);
  GetSetVal = 1;  // 2 qclk DLL mask
  MrcGetSetChStrb (MrcData, 0, 0, MAX_SDRAM_IN_DIMM, GsmIocDllMask,  WriteToCache | PrintValue, &GetSetVal);
  //MRC:RestricteContent - See DATA0CH0_CR_DDRCRDATACONTROL1_STRUCT
  //MrcGetSetLimits (MrcData, SenseAmpDelay, &GetSetVal, NULL, NULL); // SenseAmpDelay, McOdtDelay are the same.
  GetSetVal = 0;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, McOdtDelay,        WriteToCache | PrintValue, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, SenseAmpDelay,     WriteToCache | PrintValue, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, DqsOdtDelay,       WriteToCache | PrintValue, &GetSetVal);
  MrcGetSetLimits (MrcData, SenseAmpDuration, NULL, &GetSetVal, NULL); // SenseAmpDuration, McOdtDuration are the same.
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, SenseAmpDuration,  WriteToCache | PrintValue, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, McOdtDuration,     WriteToCache | PrintValue, &GetSetVal);
  MrcGetSetLimits (MrcData, DqsOdtDuration, NULL, &GetSetVal, NULL);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, DqsOdtDuration,    WriteToCache | PrintValue, &GetSetVal);
  GetSetVal = (Lpddr) ? 3 : 1;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocDataRxBurstLen, WriteToCache | PrintValue, &GetSetVal);
  MrcGetSetLimits (MrcData, GsmIocRxClkStg, NULL, &GetSetVal, NULL);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocRxClkStg, WriteToCache | PrintValue, &GetSetVal);
  GetSetVal = 1;
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocConstZTxEqEn, WriteToCache | PrintValue, &GetSetVal);
  // Pick RxBias value according to DDR frequency
  if (DdrFrequency >= f1867) {
    GetSetVal = (Lpddr4) ? 15 : 8;
  } else if (DdrFrequency >= f1600) {
    GetSetVal = 10;
  } else if (DdrFrequency >= f1333) {
    GetSetVal = 13;
  } else {
    GetSetVal = 15;
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      // Rx Vref Config for LPDDR
      if (Lpddr) {
        DramVdd = Outputs->VddVoltage[Profile];
        // @todo: This is tied to the Pull Up Calibration selected in LPDDR4 MR.
        Voh =  ((Lpddr5) ? DramVdd / 2 : ((Outputs->Lp4x) ? 360 : 440));  // mV
        PuDeltaV = DramVdd - Voh;
        EffPullUp = PuDeltaV * Inputs->RcompTarget[RdOdt];
        EffPullUp = DIVIDEROUND (EffPullUp, Voh);
        MrcSetIdealRxVref (MrcData, Controller, Channel, EffPullUp, 40, Inputs->RcompTarget[RdOdt], TRUE);
      }

      ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
      for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
        // These CRs do a lot of RMW.
        ChannelOut->DataCompOffset[Byte]  = 0;
      }
    } // Channel
  } // Controller

  if (Ddr4) {
    MrcSetDefaultRxVrefDdr4 (MrcData, TRUE, TRUE);
  }

  // @todo : InvalidateCache is called at line 2090, so investigate the correct place for it.
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        for (Byte = 0; Byte < Outputs->SdramCount; Byte++) {
          MrcGetSetChStrb (MrcData, Controller, Channel, Byte, GsmIocDataCtlGear1, ReadCached, &GetSetDis);
        }
      }
    }
  }

  // Initialize VssHi CRs @todo update for TGL
  // VssHi:
  //   For Y/U: Max {Vccddq-0.95V, 0.3V}
  //   For H/S: Max {Vccddq-0.95V, 0.25V}
  VssHi = ((UINT16) Vdd - VssHiSwingTarget);
  VssHiMax = UlxUlt ? 300 : 250;
  VssHi = MAX (VssHi, VssHiMax);

  if (Inputs->UlxUlt) {
    CCCBscanData.Bits.BiasRloadVref = DataControl5.Bits.BiasRloadVref;
    CCCBscanData.Bits.BiasIrefAdj   = DataControl5.Bits.BiasIrefAdj;
    CCCBscanData.Bits.BiasCasAdj    = 2 ;
    Data = CCCBscanData.Data;
  } else {
    CCCBscanDataP0.P0Bits.BiasRloadVref = DataControl5.Bits.BiasRloadVref;
    CCCBscanDataP0.P0Bits.BiasIrefAdj   = DataControl5.Bits.BiasIrefAdj;
    CCCBscanDataP0.P0Bits.BiasCasAdj    = 2 ;
    Data = CCCBscanDataP0.Data;
  }
  for (Channel = 0; Channel < MRC_NUM_CCC_INSTANCES; Channel++) {
    Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRBSCANDATA_REG, CH1CCC_CR_DDRCRBSCANDATA_REG, Channel);
    MrcWriteCR (MrcData, Offset, Data);
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init Dimm Vref CRs\n");
  // Initialize Dimm Vref CRs
  VrefControl.Data = 0;

  // @todo: Select correct target based on CPU SKU. Target = 42 mV which has different precision for different ULTs. ICL code
  TempVar1 = DIVIDEROUND (VccIoMv, 128);
  TempVar2 = 2 * Vdd2Mv;
  TempVar3 = DIVIDEROUND (TempVar2, 382);
  TempVar4 = DIVIDEROUND (TempVar3, TempVar1);
  VtSlope = TempVar4;
  TempVar1 = DIVIDEROUND (Vdd2Mv, 96);
  SignedTempVar = DIVIDEROUND (42, TempVar1);
  VtOffset = RANGE (SignedTempVar, -16, 15);
  if (Inputs->UlxUlt) {
    VrefControl.Bits.HiBWEnable = 1;
    VrefControl.Bits.VtSlope = VtSlope;
    VrefControl.Bits.VtOffset = VtOffset;
    VrefControl.Bits.SelCode = 1;
    VrefControl.Bits.SampleDivider = 1;

  } else {
    VrefControl.P0Bits.HiBWEnable = 1;
    VrefControl.P0Bits.VtSlope = VtSlope;
    VrefControl.P0Bits.VtOffset = VtOffset;
    VrefControl.P0Bits.SelCode = 1;
    VrefControl.P0Bits.SampleDivider = 1;

  }

  MrcWriteCR (MrcData, DDRVREF_CR_DDRCRVREFCONTROL_REG, VrefControl.Data);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "DdrCrVrefControl: 0x%X\n", VrefControl.Data);

  // Enable all DimmVref and VddHi based on VddVoltage
  VrefAdj1.Data = 0;
  // Only DDR4 uses these Vrefs.  Only enable if the DDR4 Controller exists.
  // Set Vref fields to 1/2 VDD.
  if (Ddr4) {
    if (Outputs->ValidMcBitMask & 1) {
      VrefAdj1.Bits.enCA0Vref = 1;
    }
    if (Outputs->ValidMcBitMask & 2) {
      VrefAdj1.Bits.enCA1Vref = 1;
    }
  }
  VrefAdj1.Bits.SAGVOpenLoopEn = 1;

  MrcWriteCR (MrcData, DDRVREF_CR_DDRCRVREFADJUST1_REG, VrefAdj1.Data);
  if (Ddr4) {
    ChangeMargin (MrcData, CmdV, MID_INT_VREF, 0, 1, 0, 0, 0, 0, 0, 1, 0);
  }

  VrefAdj2.Data = 0;
  VrefAdj2.Bits.HiZTimerCtrl  = DDRVREF_CR_DDRCRVREFADJUST2_HiZTimerCtrl_MAX;
  VrefAdj2.Bits.LockOvrd = SAFE ? 0 : 1;
  TempVar1 = (/*TBDns*/1000 / RefClkPs) - 4;
  TempVar2 = MrcLog2(TempVar1);
  VrefAdj2.Bits.LockTimer    = RANGE(TempVar2, 0, 7);
  TempVar1 = /*TBD*/ /* * */(Vdd2Mv / 382);
  TempVar2 = VccIoMv / 128;
  TempVar3 = DIVIDEROUND(TempVar1, TempVar2);
  //MaxMin( Rnd(TBD*(VccDD2/382) / (VccIO/128)), 0, 31
  VrefAdj2.Bits.VtSlopeSAGV = RANGE(TempVar3, 0, 31);
  SignedTempVar1 = /*TBD*/ /* /*/(Vdd2Mv / 96);
  // MaxMin( Rnd(TBD mV / (VccDD2/96) ), -16, 15).
  VrefAdj2.Bits.VtOffsetSAGV = RANGE(SignedTempVar1, -16, 15);
  VrefAdj2.Bits.SagvVtCtl   = 1;
  VrefAdj2.Bits.GateICinDVFS = SAFE ? 1 : 0;
  MrcWriteCR (MrcData, DDRVREF_CR_DDRCRVREFADJUST2_REG, VrefAdj2.Data);

  MrcGetTdqs2dq (MrcData, TRUE, &Tdqs2dqMinFs);
  TempVar1 = 150 / (QclkPs / (Gear2 ? 128 : 64));

  // This register config has been moved here because TimingProfile is assigned above.
  // Expectation : tCK should be same across all populated instances MC/CH/DIMM
  WrRetrainControlStatus.Data = 0;
  WrRetrainControlStatus.Bits.InitTrain = 0;
  WrRetrainControlStatus.Bits.Duration = ((4096 - 1) * 2 * Tdqs2dqMinFs) / (16 * ((UINT8)TimingProfile->tCK));
  WrRetrainControlStatus.Bits.LargeChangeDelta = MrcLog2 (TempVar1);
  MrcWriteCrMulticast (MrcData, DATA_CR_DDRCRWRRETRAINCONTROLSTATUS_REG, WrRetrainControlStatus.Data);

  // WCK Configuration
  WckControl.Data = 0;
  if (Lpddr5) {
    if (Inputs->UlxUlt) {
      // Lp5Mode bit field does not exist on TGL P0
      WckControl.Bits.Lp5Mode = 1;
    }
    Data32 = MrcGetWckPreStatic (MrcData);
    WckControl.Bits.tWckPre = Data32 * ((Gear2) ? 4 : 2) + 1;
    WckControl.Bits.tWckHalfRate = 2 + ((Gear2) ? 0 : 1);
    Data32 = MrcGetWckPreWrTotal (MrcData);
    //WckControl.Bits.cas2wrwck = Data32 * ((Gear2) ? 4 : 2);
    // JEDEC Spec Table 26. WCK2CK Sync AC Parameters for Write operation
    // tCWL was scaled to QCLK/WCK above.
    WckControl.Bits.cas2wrwck = tCWL + 4 - (Data32 * 4) + ((Gear2) ? -1 : 1);
    Data32 = MrcGetWckPreRdTotal (MrcData);
    // tCL was scaled to QCLK/WCK above.
    WckControl.Bits.cas2rdwck = tCL + 4 - (Data32 * 4) + ((Gear2) ? -1 : 1);
    MrcGetSetNoScope (MrcData, GsmIocLp5Wck2CkRatio, WriteToCache, &GetSetEn);
  }
  MrcWriteCR (MrcData, MCMISCS_DDRWCKCONTROL_REG, WckControl.Data);

  // Initialize CCC Non-training parameters
  // @todo: Defining init dummies to be completed later.
  for (Index = 0; Index < MRC_NUM_CCC_INSTANCES; Index++) {
    Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCCCVOLTAGEUSED_REG, CH1CCC_CR_DDRCRCCCVOLTAGEUSED_REG, Index);
    Data32 = MrcReadCR (MrcData, Offset);
    MrcWriteCR (MrcData, Offset, Data32);

    // TxEq, CtlSRDrv, PiGate, LpddrMode
    Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG, CH1CCC_CR_DDRCRCCCCLKCONTROLS_REG, Index);
    Data32 = MrcReadCR (MrcData, Offset);
    MrcWriteCR (MrcData, Offset, Data32);
  }

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MaxChannels; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        ChannelOut = &Outputs->Controller[Controller].Channel[Channel];
        IntCmdTiming = &IntOutputs->Controller[Controller].CmdTiming[Channel];

        // Initialize CRs shared between CKE/CTL/CMD/CLK
        GetSetVal2 = CmdPiDelay;
        //@todo - DDR5 support.
        Offset = (Ddr4) ? MRC_DDR4_CMD_GRP_MAX : 1;
        for (Index = 0; Index < Offset; Index++) {
          MrcGetSetCcc (MrcData, Controller, Channel, MRC_IGNORE_ARG, Index, CmdGrpPi, WriteToCache | PrintValue, &GetSetVal2);
          IntCmdTiming->CmdPiCode[Index] = (UINT16) GetSetVal2;
        }
        GetSetVal  = ClkPiDelay;
        GetSetVal2 = CtlPiDelay;
        GetSetVal3 = WckPiDelay;

        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
            continue;
          }
          MrcGetSetCcc (MrcData, Controller, Channel, Rank, 0, CtlGrpPi, WriteToCache | PrintValue, &GetSetVal2);
          IntCmdTiming->CtlPiCode[Rank] = (UINT16) GetSetVal2;
          if (Ddr4) {
            MrcGetSetCcc (MrcData, Controller, Channel, Rank, 0, ClkGrpPi, WriteToCache | PrintValue, &GetSetVal);
            IntCmdTiming->ClkPiCode[Rank] = (UINT16) GetSetVal;
            MrcGetSetCcc (MrcData, Controller, Channel, Rank, 0, CkeGrpPi, WriteToCache | PrintValue, &GetSetVal2);
            IntCmdTiming->CkePiCode[Rank] = (UINT16) GetSetVal2;
          }
        }
        // Clk/Cke/Wck are per-channel for LPDDR
        if (Lpddr) {
          MrcGetSetCcc (MrcData, Controller, Channel, MRC_IGNORE_ARG, 0, ClkGrpPi, WriteToCache | PrintValue, &GetSetVal);
          IntCmdTiming->ClkPiCode[0] = (UINT16) GetSetVal;
        }
        if (Lpddr4) {
          MrcGetSetCcc (MrcData, Controller, Channel, MRC_IGNORE_ARG, 0, CkeGrpPi, WriteToCache | PrintValue, &GetSetVal2);
          IntCmdTiming->CkePiCode[0] = (UINT16) GetSetVal2;
        } else if (Lpddr5) {
          MrcGetSetCcc (MrcData, Controller, Channel, MRC_IGNORE_ARG, 0, WckGrpPi, WriteToCache | PrintValue, &GetSetVal3);
          IntCmdTiming->WckPiCode = (UINT16) GetSetVal3;
        }
      }
    } // Channel
  } // Controller
  MrcFlushRegisterCachedData (MrcData);

  // Disable Periodic RComp
  // Set periodic comp = (10uS * 2^COMP_INT)
  CrMCompPcu.Data               = 0;
  CrMCompPcu.Bits.COMP_DISABLE  = 1;
  CrMCompPcu.Bits.COMP_INTERVAL = COMP_INT;  // Set COMP_INT to happen every 10mS
  MrcWriteCR (MrcData, M_COMP_PCU_REG, CrMCompPcu.Data);

  // Initialize COMP CRs for DqOdt, DqDrv, CmdDrv, CtlDrv, ClkDrv
  GetSetVal = SAFE ? 1 : 0; // Override PwrDn in Safe Mode
  MrcGetSetNoScope (MrcData, GsmIocCompClkOn, WriteCached, &GetSetVal);

  MrcSetupVtt (MrcData, TRUE);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init MISC CRs\n");
  // Initialize MISC CRs
  for (Index = 0; Index < MRC_NUM_BYTE_GROUPS; Index++) {
    GetSetVal = 3; // 8 QCLKs
    MrcGetSetChStrb (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, GsmIocWlWakeCyc, WriteCached, &GetSetVal);
    TempVar1 = DIVIDEROUND (20000, QclkPs);
    GetSetVal = (MrcLog2 (TempVar1)) - 2;
    MrcGetSetChStrb (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, GsmIocWlSleepCyclesAct, WriteCached, &GetSetVal);
    if (!UlxUlt) {
      TempVar1 = DIVIDEROUND (160000, QclkPs);
      GetSetVal = (MrcLog2 (TempVar1)) - 2;
      MrcGetSetChStrb (MrcData, MRC_IGNORE_ARG, MRC_IGNORE_ARG, Index, GsmIocWlSleepCyclesLp, WriteCached, &GetSetVal);
    }
  }

  // Keep scrambling disabled for training
  for (Channel = 0; Channel < MRC_NUM_CCC_INSTANCES; Channel++) {
    Offset = OFFSET_CALC_CH (DDRSCRAM_CR_DDRSCRAMBLECH0_REG, DDRSCRAM_CR_DDRSCRAMBLECH1_REG, Channel);
    MrcWriteCR (MrcData, Offset, 0);
  }

  // Set the DDR voltage in PCU
  MrcSetPcuDdrVoltage (MrcData, Vdd);

  if (Inputs->BootMode == bmCold) {
    // Must be the last register written for basic init (Must be after MC Init).
    MrcWriteCR (MrcData, DDRSCRAM_CR_DDRLASTCR_REG, 1);
  }

  // First RCOMP happens in this function.
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Init COMP CRs\n");
  // Walk backwards here because RdOdt depends on WrDS.
  for (Index = (sizeof (CompParamList) / sizeof (CompParamList[0])); Index > 0; Index--) {
    UpdateCompTargetValue (MrcData, CompParamList[Index - 1], Inputs->RcompTarget, TRUE);
  }

  MrcVssHiRegulatorOffsetCorrection (MrcData, TRUE);

#ifdef MRC_DEBUG_PRINT
  DataCompVtt.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRDATACOMPVTT_REG);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "final panicvttup%d = 0x%X\n", 0, DataCompVtt.Bits.PanicVttUp0);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "final panicvttup%d = 0x%X\n", 1, DataCompVtt.Bits.PanicVttUp1);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "final panicvttdn%d = 0x%X\n", 0, DataCompVtt.Bits.PanicVttDn0);
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "final panicvttdn%d = 0x%X\n", 1, DataCompVtt.Bits.PanicVttDn1);
#endif //MRC_DEBUG_PRINT

  MrcBlockTrainResetToggle (MrcData, FALSE);
  IoReset (MrcData);
  MrcBlockTrainResetToggle (MrcData, TRUE);

  return Status;
}

/**
  This function checks for Scomp Training or Bypass mode.

  @param[in, out] MrcData - Include all MRC global data.

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrScomp (
  IN OUT MrcParameters *const MrcData
  )
{
  static const UINT8  ScompParam[4] = {SCompDq, SCompCmd, SCompCtl, SCompClk};
  MrcInput           *Inputs;
  MrcStatus          Status;
  MrcOutput          *Outputs;
  UINT8              ScompIndex;
  UINT8              ScompInitMax;
  BOOLEAN            Lpddr;
  UINT8              ScompBypassBitMask;

  Inputs             = &MrcData->Inputs;
  Outputs            = &MrcData->Outputs;
  Lpddr              = Outputs->Lpddr;
  ScompInitMax       = ARRAY_COUNT (ScompParam);
  Status             = mrcSuccess;
  ScompBypassBitMask = 0;

  for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
    if (Lpddr && Inputs->ScompBypass[ScompIndex]) {
      ScompBypassBitMask |= (1 << ScompIndex);
    }
  }

  // Skip MrcDdrScompInit if all ScompBypass is set
  if (ScompBypassBitMask < 0xF) {
    Status = MrcDdrScompInit(MrcData, ScompBypassBitMask);
  }
  MrcDdrScompBypass(MrcData, ScompBypassBitMask);

  return Status;
}

/**
This function bypass the Slew Rate Delay Cells of the give Scomp Type.

  @param[in, out] MrcData    - Include all MRC global data.
  @param[in]      ScompIndex - Scomp Type

**/
VOID
MrcDdrScompBypass (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8         ScompBypassBitMask
  )
{
  static const UINT8  ScompParam[4]  = { SCompDq, SCompCmd, SCompCtl, SCompClk };
  static const GSM_GT SCompBypass[4] = { SCompBypassDq, SCompBypassCmd, SCompBypassCtl, SCompBypassClk };
  static const GSM_GT SCompCells[4]  = {TxSlewRate, CmdSlewRate, CtlSlewRate, ClkSlewRate};
  static const GSM_GT SCompCode[4]   = { SCompCodeDq, SCompCodeCmd, SCompCodeCtl, SCompCodeClk };
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  UINT32            Offset;
  UINT32            Data;
  UINT32            Byte;
  UINT32            Index;
  UINT32            DdrCaSlwDlyBypass;
  UINT8             ScompIndex;
  UINT8             ScompInitMax;
  UINT8             Controller;
  UINT8             Channel;
  UINT8             MaxChannels;
  UINT8             byte;
  INT64             GetSetVal;
  BOOLEAN           Lpddr;
  BOOLEAN           BreakOut;
  DDRPHY_COMP_CR_DDRCRCOMPOVR0_STRUCT  DdrCrCompOvr;
  DATA0CH0_CR_DDRCRDATACONTROL2_STRUCT DataControl2;
  CH0CCC_CR_DDRCRPINSUSED_STRUCT       CccPinsUsed;
  CH0CCC_CR_DDRCRPINSUSED_P0_STRUCT    CccPinsUsedP0;
  DATA0CH0_CR_RCOMPDATA0_STRUCT        CompData0;

  Inputs  = &MrcData->Inputs;
  Outputs = &MrcData->Outputs;
  MaxChannels = Outputs->MaxChannels;
  Debug = &Outputs->Debug;
  ScompInitMax = ARRAY_COUNT(ScompParam);
  DataControl2.Data = MrcReadCR (MrcData, DATA_CR_DDRCRDATACONTROL2_REG);
  Lpddr = Outputs->Lpddr;
  DdrCrCompOvr.Data = MrcReadCR(MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR0_REG);
  BreakOut = FALSE;

  // Read the first populated RCOMPDATA register
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; (Channel < MaxChannels) && (BreakOut == FALSE); Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        for (byte = 0; (byte < Outputs->SdramCount) && (BreakOut == FALSE); byte++) {
          if (Lpddr) {
            Byte = (MAX_BYTE_IN_LP_CHANNEL * Channel); //@todo : For DDR5 MAX_BYTE_IN_CHANNEL != 2 so add that
          } else {
            Byte = 0; // By default if Channel is present then first byte will be present
          }
          Offset = DATA0CH0_CR_RCOMPDATA0_REG;
          Offset += (DATA0CH1_CR_RCOMPDATA0_REG - DATA0CH0_CR_RCOMPDATA0_REG) * Controller +
            (DATA1CH0_CR_RCOMPDATA0_REG - DATA0CH0_CR_RCOMPDATA0_REG) * Byte;
          CompData0.Data = MrcReadCR (MrcData, Offset);
          BreakOut = TRUE;
        }
      }
    }
  }
  for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
    if ((ScompBypassBitMask >> ScompIndex) & 1) {
      // Set Bypass for the given Scomp Type
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Bypass %s\n", CompGlobalOffsetParamStr[ScompParam[ScompIndex]]);
      GetSetVal = 1;
      if (SCompBypass[ScompIndex] == SCompBypassDq) {
        MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, SCompBypass[ScompIndex], WriteToCache, &GetSetVal);
      } else {
        MrcGetSetCcc (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MRC_IGNORE_ARG, MAX_SYS_CHANNEL, SCompBypass[ScompIndex], WriteCached, &GetSetVal);
      }
      // Set SComp Override
      if (DataControl2.Bits.DqSlewDlyByPass || Lpddr) {
        DdrCrCompOvr.Bits.DqSR = 1;
      }
      GetSetVal = 0;
      MrcGetSetNoScope (MrcData, SCompCode[ScompIndex], WriteCached, &GetSetVal);
      // Set Scomp Cells to 0
      MrcGetSetNoScope (MrcData, SCompCells[ScompIndex], WriteCached, &GetSetVal);
    }
  }
  if (DataControl2.Bits.DqSlewDlyByPass) {
    CompData0.Bits.SlewRateComp = 0;
  }
  MrcWriteCrMulticast (MrcData, DATA_CR_RCOMPDATA0_REG, CompData0.Data);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR0_REG, DdrCrCompOvr.Data);

  DdrCaSlwDlyBypass = (Outputs->DdrType != MRC_DDR_TYPE_DDR4);
  for (Index = 0; Index < MRC_NUM_CCC_INSTANCES; Index++) {
    Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRPINSUSED_REG, CH1CCC_CR_DDRCRPINSUSED_REG, Index);
    if (Inputs->UlxUlt) {
      CccPinsUsed.Data = MrcReadCR (MrcData, Offset);
      CccPinsUsed.Bits.DdrClkSlwDlyBypass = 1;
      CccPinsUsed.Bits.DdrCtlSlwDlyBypass = 1;//(Outputs->DdrType == MRC_DDR_TYPE_DDR5);
      CccPinsUsed.Bits.DdrCaSlwDlyBypass = DdrCaSlwDlyBypass;
      Data = CccPinsUsed.Data;
    } else {
      CccPinsUsedP0.Data = MrcReadCR (MrcData, Offset);
      CccPinsUsedP0.P0Bits.DdrClkSlwDlyBypass = 1;
      CccPinsUsedP0.P0Bits.DdrCtlSlwDlyBypass = 1;//(Outputs->DdrType == MRC_DDR_TYPE_DDR5);
      CccPinsUsedP0.P0Bits.DdrCaSlwDlyBypass = DdrCaSlwDlyBypass;
      Data = CccPinsUsedP0.Data;
    }
    MrcWriteCR (MrcData, Offset, Data);
  }
}

/**
  This function initializes the Slew Rate of DQ, CMD, CTL and CLK buffers in DDRIO.

  @param[in, out] MrcData    - Include all MRC global data.
  @param[in]      ScompIndex - Scomp Type

  @retval MrcStatus - mrcSuccess if successful or an error status
**/
MrcStatus
MrcDdrScompInit (
  IN OUT MrcParameters *const MrcData,
  IN     UINT8         ScompBypassBitMask
  )
{
  static const GSM_GT SCompCells[4]           = {TxSlewRate, CmdSlewRate, CtlSlewRate, ClkSlewRate};
  static const GSM_GT SCompPC[4]              = {DqScompPC, CmdScompPC, CtlScompPC, ClkScompPC};
  static const GSM_GT SCompCode[4]            = {SCompCodeDq, SCompCodeCmd, SCompCodeCtl, SCompCodeClk};
  //static const UINT8  DesiredSlewRateUDdr4[4] = {45, 32, 30, 45};  // units of [mV/ps] and multiplied by 10 for integer math precision in DesiredBufferSegmentDelay calculation below.
  static const UINT8  DesiredSlewRateUDdr4[4] = {45, 35, 35, 40};  // units of [mV/ps] and multiplied by 10 for integer math precision in DesiredBufferSegmentDelay calculation below.
  static const UINT8  DesiredSlewRateHDdr4[4] = {45, 30, 30, 50};  // units of [mV/ps] and multiplied by 10 for integer math precision in DesiredBufferSegmentDelay calculation below.
  static const UINT8  DesiredSlewRateLpdr4[4] = {55, 35, 35, 45};  // units of [mV/ps] and multiplied by 10 for integer math precision in DesiredBufferSegmentDelay calculation below.
  static const UINT8  RcompParam[4]           = {WrDS, WrDSCmd, WrDSCtl, WrDSClk};
  static const UINT8  ScompParam[4]           = {SCompDq, SCompCmd, SCompCtl, SCompClk};
#ifdef MRC_DEBUG_PRINT
  static const char   *ScompHeader[4]         = { "Dq", "Cmd", "Ctl", "Clk" };
#endif
  MrcInput          *Inputs;
  MrcDebug          *Debug;
  const MRC_FUNCTION *MrcCall;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  UINT8 const       *DesiredSlewRate;
  MrcVddSelect      Vdd;
  INT64             GetSetVal;
  UINT32            OdtWr;
  UINT32            OdtNom;
  UINT32            DelayCells;
  UINT32            DesiredBufferSegmentDelay[4];
  UINT32            MinChainLength;
  UINT32            MaxChainLength;
  UINT32            VSwing;
  UINT32            VHigh;
  UINT32            VLow;
  UINT32            Voh;
  UINT32            Vtt;
  UINT32            VccIo;
  UINT32            Rtt;
  UINT32            Divisor;
  UINT32            Dividend;
  UINT32            OdtValue;
  UINT32            OdtPark;
  UINT32            Data32;
  UINT32            Controller;
  UINT16            CpuRon;
  UINT8             ScompIndex;
  UINT8             ScompInitMax;
  UINT8             CellIndex;
  UINT8             Max;
  UINT8             Channel;
  UINT8             Rank;
  UINT8             Dimm;
  UINT8             SCompResult[4][SCOMP_CELLS_MAX + 1];
  UINT8             SCompCount[4];
  UINT8             NCells[4][MAX_EDGES];
  UINT8             ChannelsPopulated;
  UINT8             DimmSerialResistor;
  UINT8             SegmentsPerBuffer;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr4;
  BOOLEAN           Is2DPC;
  BOOLEAN           Is2RDimm;
  DDRPHY_COMP_CR_DDRCRCOMPOVR0_STRUCT DdrCrCompOvr;

  Inputs            = &MrcData->Inputs;
  MrcCall           = Inputs->Call.Func;
  Outputs           = &MrcData->Outputs;
  ControllerOut     = &Outputs->Controller[0];
  Debug             = &Outputs->Debug;
  Ddr4              = (Outputs->DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr4            = (Outputs->DdrType == MRC_DDR_TYPE_LPDDR4);
  Vdd               = Outputs->VddVoltage[Inputs->MemoryProfile];
  VccIo             = Inputs->VccIomV;
  ScompInitMax      = ARRAY_COUNT (ScompParam);
  Dividend          = 0;

  // Determine slew rate targets according to CPU Sku and DDR type
  if (Inputs->UlxUlt) {
    if (Lpddr4) {
      DesiredSlewRate = DesiredSlewRateLpdr4;
    } else {
      DesiredSlewRate = DesiredSlewRateUDdr4;
    }
  } else {
    // DT/Halo
    DesiredSlewRate = DesiredSlewRateHDdr4;
  }

  for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
    if (((ScompBypassBitMask >> ScompIndex) & 1) != 1) {
      // Setup of DQ, CMD, CTL, CLK SCompPC
      GetSetVal = 1; // Cycle lock
      MrcGetSetNoScope(MrcData, SCompPC[ScompIndex], WriteCached, &GetSetVal);
    }
  }

  MrcCall->MrcSetMem (SCompResult[0], sizeof (SCompResult), 0);
  MrcCall->MrcSetMem (SCompCount, sizeof (SCompCount), 0);
  MrcCall->MrcSetMem ((UINT8 *) NCells, sizeof (NCells), 0);
  // Gather results for 3-15 ScompCells
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t\tScompCode\n\t");
  for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
    if (((ScompBypassBitMask >> ScompIndex) & 1) != 1) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%s", ScompHeader[ScompIndex]);
    }
  }
  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nScompCells\n");
  for (CellIndex = SCOMP_CELLS_MIN; CellIndex <= SCOMP_CELLS_MAX; CellIndex++) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\t%d\t", CellIndex);
    for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
      if (((ScompBypassBitMask >> ScompIndex) & 1) != 1) {
        // Setup of DQ, CMD, CTL, CLK ScompCells
        GetSetVal = CellIndex;
        MrcGetSetNoScope (MrcData, SCompCells[ScompIndex], WriteCached, &GetSetVal);
      }
    }

    // Force Comp Cycle
    ForceRcomp (MrcData);

    // Read the SCOMP results
    for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
      if (((ScompBypassBitMask >> ScompIndex) & 1) != 1) {
        MrcGetSetNoScope (MrcData, SCompCode[ScompIndex], ReadUncached, &GetSetVal);
        SCompResult[ScompIndex][CellIndex] = (UINT8) GetSetVal;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", SCompResult[ScompIndex][CellIndex]);
      }
    }
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\n");
  }

  DdrCrCompOvr.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR0_REG);

  // Compare results
  for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
    if (((ScompBypassBitMask >> ScompIndex) & 1) != 1) {
      if (ScompParam[ScompIndex] != SCompDq) {
        Max = 62;
      } else {
        Max = 29;
      }
      // DQ, CMD, CTL, CLK ScompCells
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s ", CompGlobalOffsetParamStr[ScompParam[ScompIndex]]);
      if (SCompResult[ScompIndex][SCOMP_CELLS_MIN] <= 1) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Setting Slew Rate Compensation Override\n");
        DdrCrCompOvr.Data |= (1 << (ScompIndex + 10));
      } else {
        for (CellIndex = SCOMP_CELLS_MIN; CellIndex <= SCOMP_CELLS_MAX; CellIndex++) {
          // Find Minimum usable chain length with unsaturated COMP code value, and at least 2 ticks of margin.
          if ((NCells[ScompIndex][0] == 0) && (SCompResult[ScompIndex][CellIndex] >= 2) && (SCompResult[ScompIndex][CellIndex] < Max)) {
            NCells[ScompIndex][0] = CellIndex;
          }
          if (SCompResult[ScompIndex][CellIndex] > Max) {
            //Exceeds upper limit.
            continue;
          }
          NCells[ScompIndex][1] = CellIndex;
          if (CellIndex == SCOMP_CELLS_MIN) {
            // Skip first index for determining Harmonic lock.
            continue;
          }
          if (SCompResult[ScompIndex][CellIndex] > SCompResult[ScompIndex][CellIndex - 1]) {
            // Harmonic lock occurred.
            MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Harmonic Lock Occured - ");
            NCells[ScompIndex][1] = CellIndex - 1;
            break;
          }
        }
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "SCompCellsMin = %d, SCompCellsMax = %d\n", NCells[ScompIndex][0], NCells[ScompIndex][1]);
      }
    }
  }
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPOVR0_REG, DdrCrCompOvr.Data);

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "\nScompType\tVSwing\tBufferSegDelay\tSCompPC \tSCompCells\n");
  for (ScompIndex = 0; ScompIndex < ScompInitMax; ScompIndex++) {
    if (((ScompBypassBitMask >> ScompIndex) & 1) != 1) {
      MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, " %s\t", CompGlobalOffsetParamStr[ScompParam[ScompIndex]]);
      // Determine Vtt and Voh based on partition being calculated, Dram Type, and source mux
      if (ScompParam[ScompIndex] == SCompDq) {
        Voh = (Lpddr4 && Inputs->LowSupplyEnData) ? VccIo : Vdd;
        Vtt = (Lpddr4) ? 0 : Vdd;
        SegmentsPerBuffer = 2;
      } else {
        Voh = (Lpddr4 && Inputs->LowSupplyEnCcc && (ScompParam[ScompIndex] != SCompCtl)) ? VccIo : Vdd;
        Vtt = (Lpddr4) ? 0 : Vdd / 2;
        SegmentsPerBuffer = (ScompParam[ScompIndex] == SCompClk) ? 2 : 3;
      }
      if ((NCells[ScompIndex][0] == 0) && (NCells[ScompIndex][1] == 0)) {
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "Slew Rate Compensation Override Set\n");
        GetSetVal = 0;
      } else {
        VSwing = 0;
        MinChainLength = MAX (SCOMP_CELLS_MIN, NCells[ScompIndex][0]);
        MaxChainLength = MIN (SCOMP_CELLS_MAX, NCells[ScompIndex][1]);
        ChannelsPopulated = 0;
        CpuRon = Inputs->RcompTarget[RcompParam[ScompIndex]];
        for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
          for (Channel = 0; Channel < Outputs->MaxChannels; Channel++) {
            if (MrcChannelExist (MrcData, Controller, Channel)) {
              ChannelOut = &ControllerOut->Channel[Channel];
              ChannelsPopulated++;
              Is2DPC =  (ChannelOut->DimmCount == 2);
              DimmSerialResistor = 15;
              OdtValue = 0;
              if (ScompParam[ScompIndex] == SCompDq) {
                if (!Outputs->DramDqOdtEn) {
                  VSwing += Voh;
                  continue;
                }
              }
              for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += MAX_RANK_IN_DIMM) {
                if (MrcRankExist (MrcData, Controller, Channel, Rank)) {
                  Dimm = RANK_TO_DIMM_NUMBER (Rank);
                  Is2RDimm = (ChannelOut->Dimm[Dimm].RankInDimm == 1);
                  if ((DimmSerialResistor != 0) && (ChannelOut->Dimm[Dimm].ModuleType == NonDimmMemoryPackage)) {
                    DimmSerialResistor = 0;
                  }
                  switch (ScompParam[ScompIndex]) {
                    case SCompDq:
                      OdtWr = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmOdtWr, FALSE, 0, TRUE);
                      if (Ddr4) {
                        OdtNom = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmOdtNom, FALSE, 0, TRUE);
                        OdtPark = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmOdtPark, FALSE, 0, TRUE);
                        OdtPark = (Is2RDimm) ? OdtPark : 0xFFFF;
                        if (Is2DPC) {
                          // OdtValue = OdtWr || (1st Dimm is 2 rank) ? OdtPark : 0xFFFF) || OdtNom || (2nd Dimm is 2 rank) ? OdtPark : 0xFFFF
                          if (Dimm == 0) {
                            Dividend = OdtWr * OdtPark;
                            Divisor = OdtWr + OdtPark;
                            OdtValue = DIVIDEROUND (Dividend, Divisor);
                          } else {
                            Dividend = OdtNom * OdtPark;
                            Divisor = OdtNom + OdtPark;
                            Data32 = DIVIDEROUND (Dividend, Divisor);
                            Dividend = Data32 * OdtValue;
                            Divisor = Data32 + OdtValue;
                            OdtValue = DIVIDEROUND (Dividend, Divisor);
                          }
                        } else {
                          // OdtValue = OdtWr || (Dimm is 2 rank) ? OdtPark : 0xFFFF
                          Dividend = OdtWr * OdtPark;
                          Divisor = OdtWr + OdtPark;
                          OdtValue = DIVIDEROUND (Dividend, Divisor);
                        }
                      } else { // Lpddr3 || Lpddr4
                        OdtValue = OdtWr;
                      }
                      break;

                    case SCompCmd:
                      if (Ddr4) {
                        if (Is2DPC) {
                          Dividend = 55 * 55;
                          Divisor = 55 + 55;
                          OdtValue = DIVIDEROUND (Dividend, Divisor);
                        } else {
                          OdtValue = 55;
                        }
                      } else { // Lpddr4
                        OdtValue = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmOdtCA, FALSE, 0, TRUE);
                      }
                      break;

                    case SCompCtl:
                      if (Ddr4) {
                        if (Is2DPC) {
                          Dividend = 55 * 55;
                          Divisor = 55 + 55;
                          OdtValue = DIVIDEROUND (Dividend, Divisor);
                        } else {
                          OdtValue = 55;
                        }
                      } else { // Lpddr4
                        OdtValue = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmOdtCA, FALSE, 0, TRUE);
                      }
                      break;

                    case SCompClk:
                      if (Ddr4) {
                        if (Is2DPC) {
                          Dividend = 93 * 93;
                          Divisor = 93 + 93;
                          OdtValue = DIVIDEROUND (Dividend, Divisor);
                        } else {
                          OdtValue = 93;
                        }
                      } else { // Lpddr4
                        OdtValue = CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmOdtCA, FALSE, 0, TRUE);
                      }
                      break;

                    default:
                      break;
                  } // Switch ScompType
                } // RankExist
              } // For Rank
              Rtt = DimmSerialResistor + OdtValue;
              Divisor = Rtt + CpuRon;
              if (Divisor == 0) {
                MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s - ODT, CPU Impedance and Dimm Resistor values are zero\n", gErrString, CompGlobalOffsetParamStr[ScompParam[ScompIndex]]);
                return mrcFail;
              }
              //VHigh = Vtt + ((Voh - Vtt) * Rtt / (CpuRon + Rtt));
              //VLow = Vtt * (CpuRon / (CpuRon + Rtt));
              VHigh = Vtt + (((Voh - Vtt) * Rtt) / (Divisor));
              VLow = (Vtt * CpuRon) / Divisor;
              VSwing += (VHigh - VLow);
            } // ChannelExist
          } // For Channel
        } // Controller
        VSwing /= (ChannelsPopulated == 0) ? 1 : ChannelsPopulated;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t", VSwing);

        // Derating value is 0.8, but because DesiredSlewRate is multiplied by 10 for precision, value of 8 is used here.
        DesiredBufferSegmentDelay[ScompIndex] = (VSwing * 8) / (DesiredSlewRate[ScompIndex] * SegmentsPerBuffer);
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\t\t", DesiredBufferSegmentDelay[ScompIndex]);
        if (DesiredBufferSegmentDelay[ScompIndex] == 0) {
          MRC_DEBUG_MSG (Debug, MSG_LEVEL_ERROR, "\n%s BufferSegDelay value is zero\n", gErrString);
          return mrcFail;
        }
        DelayCells = DIVIDEROUND (Outputs->Qclkps, DesiredBufferSegmentDelay[ScompIndex]);
        if (DelayCells > (MaxChainLength + 1)) {
          // Calculated value is larger than maximum chain length.
          DelayCells = DIVIDEROUND (Outputs->Qclkps, 2 * DesiredBufferSegmentDelay[ScompIndex]);
          GetSetVal = 0; // Phase Lock
        } else {
          GetSetVal = 1; // Cycle Lock
        }

        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%s\t\t", (GetSetVal == 0) ? "Phase" : "Cycle");
        MrcGetSetNoScope (MrcData, SCompPC[ScompIndex], WriteCached, &GetSetVal);
        DelayCells = RANGE (DelayCells - 1, MinChainLength, MaxChainLength);
        GetSetVal = DelayCells;
        MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "%d\n", DelayCells);
      }
      MrcGetSetNoScope (MrcData, SCompCells[ScompIndex], WriteCached, &GetSetVal);
    }
  }
  MRC_DEBUG_MSG(Debug, MSG_LEVEL_NOTE, "\n");

  return mrcSuccess;
}

/**
  This function initializes all the necessary registers for basic training by
  Activating and initializing CPGC Engine
  Cleaning out MRs for programming

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess
**/
MrcStatus
MrcPreTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcDebug          *Debug;
  MrcInput          *Inputs;
  MrcOutput         *Outputs;
  MrcControllerOut  *ControllerOut;
  MrcChannelOut     *ChannelOut;
  MrcDdrType        DdrType;
  UINT32            Channel;
  UINT32            IpChannel;
  UINT32            ChannelLoopIncrement;
  UINT32            Controller;
  UINT32            Offset;
  UINT32            Rank;
  UINT32            RankMod2;
  UINT8             ChannelMask;
  BOOLEAN           Ddr4;
  BOOLEAN           Lpddr;
  MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_STRUCT Cpgc2AddrSize;

  MC0_REQ0_CR_CPGC_SEQ_CFG_A_STRUCT   CpgcSeqCfgA;
  MC0_CR_CPGC2_CREDIT_CFG_STRUCT      Cpgc20Credits;

  Inputs        = &MrcData->Inputs;
  Outputs       = &MrcData->Outputs;
  Debug         = &Outputs->Debug;
  DdrType       = Outputs->DdrType;
  Ddr4          = (DdrType == MRC_DDR_TYPE_DDR4);
  Lpddr         = Outputs->Lpddr;

  ChannelLoopIncrement = (Lpddr) ? 2 : 1;
  // @todo - Update for 1 TE per controller.
  MrcSetNormalMode (MrcData, FALSE); // Go to CPGC mode

  // Assign channel to its serial number
  // Activate CPGC Engines on populated channels and subchannels.
  CpgcSeqCfgA.Data = 0;

  Cpgc2AddrSize.Data = 0;
  Cpgc2AddrSize.Bits.Block_Size_Max_Bank  = (Ddr4) ? MAX_DDR4_x16_BANKS - 1 : 0;
  Cpgc2AddrSize.Bits.Region_Size_Max_Bank = Cpgc2AddrSize.Bits.Block_Size_Max_Bank;
  Cpgc2AddrSize.Bits.Block_Size_Bits_Row  = 0;
  Cpgc2AddrSize.Bits.Block_Size_Bits_Col  = (Ddr4) ? 4 : 5;
  Cpgc2AddrSize.Bits.Region_Size_Bits_Row = Cpgc2AddrSize.Bits.Block_Size_Bits_Row;
  Cpgc2AddrSize.Bits.Region_Size_Bits_Col = Cpgc2AddrSize.Bits.Block_Size_Bits_Col;
  Cpgc2AddrSize.Bits.REQUEST_DATA_SIZE    = 1;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    if (!MrcControllerExist (MrcData, Controller)) {
      continue;
    }
    ControllerOut = &Outputs->Controller[Controller];
    Outputs->McChBitMask |= ControllerOut->ValidChBitMask << (Controller * Outputs->MaxChannels);
    CpgcSeqCfgA.Data = 0;
    for (Channel = 0; Channel < Outputs->MaxChannels; Channel += ChannelLoopIncrement) {
      if (!MrcChannelExist (MrcData, Controller, Channel)) {
        continue;
      }
      ChannelMask = (Lpddr) ? ((ControllerOut->ValidChBitMask >> Channel) & 0x3) : 0x1;
      ChannelOut = &ControllerOut->Channel[Channel];
      IpChannel = LP_IP_CH (Lpddr, Channel);

      Offset = OFFSET_CALC_CH (MC0_CR_CPGC2_CREDIT_CFG_REG, MC1_CR_CPGC2_CREDIT_CFG_REG, Controller);
      Cpgc20Credits.Data = MrcReadCR (MrcData, Offset);
      if (Inputs->A0) {
        Cpgc20Credits.A0Bits.RD_CPL_CREDITS_INIT = 0x14;
        Cpgc20Credits.A0Bits.CREDITS_CONFIG_DONE = 1;
      } else {
        Cpgc20Credits.Bits.RD_CPL_CREDITS_INIT = 0x14;
        Cpgc20Credits.Bits.CREDITS_CONFIG_DONE = 1;
      }
      MrcWriteCR (MrcData, Offset, Cpgc20Credits.Data);

      CpgcSeqCfgA.Bits.CHANNEL_ASSIGN      = (ChannelMask << Channel);
      ChannelOut->CpgcChAssign             = (UINT8) CpgcSeqCfgA.Bits.CHANNEL_ASSIGN;
      CpgcSeqCfgA.Bits.INITIALIZATION_MODE = CPGC20_ACTIVE_MODE;
      Offset = MrcGetCpgcSeqCfgOffset (MrcData, Controller, Channel / ChannelLoopIncrement);
      MrcWriteCR (MrcData, Offset, CpgcSeqCfgA.Data);

      if (Ddr4) {
        // Setup Bank Logical to Physical mapping
        MrcGetSetBankSequence (
          MrcData,
          Controller,
          Channel,
          Ddr4BankMap,
          MAX_DDR4_x16_BANKS,
          MRC_SET
        );
      }
      Offset = OFFSET_CALC_MC_CH (
        MC0_REQ0_CR_CPGC2_ADDRESS_SIZE_REG,
        MC1_REQ0_CR_CPGC2_ADDRESS_SIZE_REG, Controller,
        MC0_REQ1_CR_CPGC2_ADDRESS_SIZE_REG, IpChannel);
      MrcWriteCR64 (MrcData, Offset, Cpgc2AddrSize.Data);

      // Dump the MR registers for DDR4
      // LPDDR3/4 Jedec Init is done after Early Command Training
      if (Ddr4) {
        for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank++) {
          if (!(MrcRankExist (MrcData, Controller, Channel, Rank))) {
            continue;
          }
          RankMod2 = Rank % 2;
          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "MrcSetMR0  Mc %u Channel %u Rank %u = 0x%X\n",
            Controller,
            Channel,
            Rank,
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR0]
            );

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "MrcSetMR1  Mc %u Channel %u Rank %u = 0x%X\n",
            Controller,
            Channel,
            Rank,
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR1]
            );

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "MrcSetMR2  Mc %u Channel %u Rank %u = 0x%X\n",
            Controller,
            Channel,
            Rank,
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR2]
            );

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "MrcSetMR3  Mc %u Channel %u Rank %u = 0x%X\n",
            Controller,
            Channel,
            Rank,
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR3]
            );

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "MR4 Mc %u Channel %u Rank %u = 0x%X\n",
            Controller,
            Channel,
            Rank,
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR4]
            );

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "MR5 Mc %u Channel %u Rank %u = 0x%X\n",
            Controller,
            Channel,
            Rank,
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR5]
            );

          MRC_DEBUG_MSG (
            Debug,
            MSG_LEVEL_NOTE,
            "MR6 Mc %u Channel %u Rank %u = 0x%X\n",
            Controller,
            Channel,
            Rank,
            ChannelOut->Dimm[RANK_TO_DIMM_NUMBER (Rank)].Rank[RankMod2].MR[mrMR6]
            );
        } // Rank
      } // if DDR4
    } // Channel
  } // Controller

  return mrcSuccess;
}

/**
  This function initializes all the necessary registers after main training steps but before LCT.

  @param[in] MrcData - Include all MRC global data.

  @retval mrcSuccess

**/
MrcStatus
MrcPostTraining (
  IN MrcParameters *const MrcData
  )
{
  MrcOutput *Outputs;
  MrcTiming *Timing;
  UINT32    Channel;
  UINT32    Controller;

  Outputs = &MrcData->Outputs;

  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      if (MrcChannelExist (MrcData, Controller, Channel)) {
        Timing = &Outputs->Controller[Controller].Channel[Channel].Timing[MrcData->Inputs.MemoryProfile];
        // Update CmdN timing, Round Trip Latency and tXP
        // OldN = 3N (Gear1) or 2N (Gear2), NewN = 1N or 2N
        UpdateCmdNTiming (
          MrcData,
          Controller,
          Channel,
          Outputs->Gear2 ? (2 * 1) : (2 * 2),
          (Timing->NMode == 2) ? 2 : 0
          );
      }
    }
  }

  return mrcSuccess;
}

/**
  Program PCU_CR_DDR_VOLTAGE register.

  @param[in] MrcData    - Include all MRC global data.
  @param[in] VddVoltage - Current DDR voltage.

**/
void
MrcSetPcuDdrVoltage (
  IN OUT MrcParameters *MrcData,
  IN     MrcVddSelect  VddVoltage
  )
{
  MrcOutput                     *Outputs;
  MrcDebug                      *Debug;
  UINT8                         Data8;
  DDR_VOLTAGE_PCU_STRUCT        DdrVoltage;

  Outputs = &MrcData->Outputs;
  Debug   = &Outputs->Debug;

  switch (VddVoltage) {
    case VDD_1_35:
      Data8 = 1;
      break;

    case VDD_1_20:
      Data8 = 3;
      if (Outputs->DdrType == MRC_DDR_TYPE_DDR4) {
        Data8 = 7;
      }
      break;

    case VDD_1_10:
      Data8 = 6;
      break;

    default:
      Data8 = 0;
  }

  MRC_DEBUG_MSG (Debug, MSG_LEVEL_NOTE, "PCU_CR_DDR_VOLTAGE = 0x%02X\n", Data8);
  DdrVoltage.Data = 0;
  DdrVoltage.Bits.DDR_VOLTAGE = Data8;
  MrcWriteCR (MrcData, DDR_VOLTAGE_PCU_REG, DdrVoltage.Data);
}

/**
  This function sets up the Vtt termination.

  @param[in] MrcData  - Include all MRC global data.
  @param[in] DebugMsg - Whether to display debug messages

**/
void
MrcSetupVtt (
  IN MrcParameters *const MrcData,
  IN BOOLEAN              DebugMsg
  )
{
  const MrcInput    *Inputs;
  MrcDebug          *Debug;
  MrcOutput         *Outputs;
  INT64             GetSetVal;
  UINT32            Channel;
  UINT32            Controller;
  UINT32            Rank;
  UINT32            Itarget;
  UINT32            IcompUp;
  UINT32            IcompDn;
  UINT32            RonDimm;
  UINT32            TotalRon;
  UINT32            CmdTarget;
  UINT32            CaRonDrvDn;
  UINT32            VttTargetV;
  UINT32            Vdd2Mv;
  UINT32            VccIoMv;
  UINT32            IttcompUp;
  UINT32            TempVar1;
  UINT32            TempVar2;
  UINT32            TempVar3;
  UINT32            TempVar4;
  UINT32            PanicV;
  UINT32            PanicCCCPU;
  UINT16            RodtCpu;
  UINT8             TotalDimms;
  BOOLEAN           CaVoltageSel;
  MrcDebugMsgLevel  DebugLevel;
  DDRPHY_COMP_CR_DDRCRCOMPCTL1_STRUCT       CompCtl1;
  DDRPHY_COMP_CR_DDRCRCOMPCTL0_STRUCT       CompCtl0;
  DDRPHY_COMP_CR_VSSHIPANIC_STRUCT          VssHiPanic;
  DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_STRUCT   CompVttPanic;
  DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_STRUCT  CompVttPanic2;
  DDRVTT0_CR_DDRCRVTTGENCONTROL_STRUCT      VttGenControl;

  Inputs              = &MrcData->Inputs;
  Outputs             = &MrcData->Outputs;
  Debug               = &Outputs->Debug;
  TotalRon            = 0;
  TotalDimms          = 0;
  CaRonDrvDn          = Inputs->RcompTarget[WrDSCmd]; // @todo Check the difference between DrvUp and DrvDn
  Vdd2Mv              = Outputs->Vdd2Mv;
  VccIoMv             = Inputs->VccIomV;
  Itarget             = 10; // Up0=Up1=Dn0=Dn1=10mA

  VssHiPanic.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_VSSHIPANIC_REG);
  CompCtl0.Data   = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL0_REG);
  VttGenControl.Data = MrcReadCR (MrcData, DDRVTT0_CR_DDRCRVTTGENCONTROL_REG); // All VttGenControl are programmed to same in ddrioint
  VttTargetV = (Outputs->DdrType == MRC_DDR_TYPE_DDR5) ? (Vdd2Mv / 2) : 150;
  PanicCCCPU = VssHiPanic.Bits.PanicCCCPU;
  DebugLevel = (DebugMsg) ? MSG_LEVEL_NOTE : MSG_LEVEL_NEVER;
//  GsmMode    = (DebugMsg) ? PrintValue : 0;

  // Calculate RodtCPU
  // @todo: in power training this might vary between different bytes so need to avg
  RodtCpu = Inputs->RcompTarget[RdOdt];
  // Calculate RonDimm Per Dimm (assuming)
  for (Controller = 0; Controller < MAX_CONTROLLER; Controller++) {
    for (Channel = 0; Channel < MAX_CHANNEL; Channel++) {
      for (Rank = 0; Rank < MAX_RANK_IN_CHANNEL; Rank += 2) {
        if (!MrcRankExist (MrcData, Controller, Channel, Rank)) {
          continue;
        }
        TotalDimms++;
        TotalRon += CalcDimmImpedance (MrcData, Controller, Channel, Rank, OptDimmRon, TRUE, INIT_DIMM_RON_34, FALSE);
      } // Rank exist
    } // Channel
  } // Controller

  if (TotalDimms == 0) {
    TotalDimms++;
  }
  RonDimm = TotalRon / TotalDimms;

  MRC_DEBUG_MSG (Debug, DebugLevel, "MrcSetupVtt: RodtCpu=%u ohm, RonDimm=%u ohm\n", RodtCpu, RonDimm);
  MRC_DEBUG_MSG (Debug, DebugLevel, "Itarget=%u uA,\n", Itarget);

  CaVoltageSel    = (CompCtl0.Bits.CaVoltageSelect == 1);

  // Configure VTT Panic Comp Command Ron Vref
  CmdTarget = Inputs->RcompTarget[WrDSCmd];

  // IcompUp and Dn should equal to 10mA
  PanicV = VttGenControl.Bits.Panic0;
  IcompUp = ((VttTargetV - PanicV) / CmdTarget) / (1 + (PanicCCCPU >> 1));

  TempVar1 = CaVoltageSel ? Vdd2Mv : Outputs->VccddqVoltage;
  TempVar2 = TempVar1 - VttTargetV - PanicV;
  IcompDn = TempVar2 / CmdTarget;

  MRC_DEBUG_MSG (Debug, DebugLevel, "IcompDn=%u uA, IcompUp=%u uA\n", IcompDn, IcompUp);

  CompVttPanic.Data = 0;

 //LPDDR Vtt target may be adjusted based on panic count feedback and margin results
  TempVar1 = 191 * (VttTargetV - PanicV);
  //VccIoG is gated version of VccIo
  TempVar2 = DIVIDEROUND (TempVar1, VccIoMv);
  if (TempVar2 > 127) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Clamping VttPanicUpVref: %d\n",TempVar2);
  }
  CompVttPanic.Bits.VttPanicUpVref = MAX (TempVar2, 127);
  TempVar1 = 191 * (VttTargetV + PanicV);
  TempVar2 = CaVoltageSel ? Vdd2Mv : Outputs->VccddqVoltage;
  CompVttPanic.Bits.VttPanicDnVref = DIVIDEROUND (TempVar1, TempVar2);
  TempVar1 = (VttTargetV - PanicV) / CaRonDrvDn;
  TempVar2 = 1 + (PanicCCCPU >> 1);
  IttcompUp = TempVar1 / TempVar2;
  TempVar3 = (2 * Itarget);
  TempVar4 = DIVIDEROUND (TempVar3, IttcompUp);
  CompVttPanic.Bits.VttPanicCompUp0Mult = TempVar4;
  CompVttPanic.Bits.VttPanicCompUp1Mult = TempVar4;
  TempVar1 = 2 * Itarget;
  TempVar2 = TempVar1 / IcompDn;
  TempVar3 = (1 + VssHiPanic.Bits.PanicPDn2xStep);
  TempVar4 = TempVar2 * TempVar3;
  if (TempVar4 > 15) {
    MRC_DEBUG_MSG (Debug, MSG_LEVEL_WARNING, "Clamping VttPanicCompDn0Mult: %d\n",TempVar4);
  }
  TempVar4 = RANGE (TempVar4, 0, 15);
  CompVttPanic.Bits.VttPanicCompDn0Mult = TempVar4;
  CompVttPanic.Bits.VttPanicCompDn1Mult = TempVar4;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_REG, CompVttPanic.Data);

  CompVttPanic2.Data = 0;
  CompVttPanic2.Bits.PanicCCCPU = PanicCCCPU;
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_REG, CompVttPanic2.Data);
  GetSetVal = 0;
  MrcGetSetNoScope (MrcData, GsmIocVttPanicCompUpMult, WriteOffsetCached, &GetSetVal);
  MrcGetSetChStrb (MrcData, MAX_CONTROLLER, MAX_CHANNEL, MAX_SDRAM_IN_DIMM, GsmIocVttPanicCompUpMult, WriteOffsetCached, &GetSetVal);

  CompCtl1.Data = MrcReadCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL1_REG);
  TempVar1 = (350 * 191) / VccIoMv; // Converting mV to ticks
  CompCtl1.Bits.En200ohmVttPncUp = (CompVttPanic.Bits.VttPanicUpVref > TempVar1);
  MrcWriteCR (MrcData, DDRPHY_COMP_CR_DDRCRCOMPCTL1_REG, CompCtl1.Data);

  ForceRcomp (MrcData);
}


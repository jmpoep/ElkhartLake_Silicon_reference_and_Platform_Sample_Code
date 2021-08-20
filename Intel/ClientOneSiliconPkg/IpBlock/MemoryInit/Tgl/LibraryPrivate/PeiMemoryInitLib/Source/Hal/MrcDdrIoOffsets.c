/** @file
  This file contains functions to get DDR IO Data Offsets
  used memory training.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2019 Intel Corporation.

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

#include "McAddress.h"
#include "MrcInterface.h"
#include "MrcDdrIoOffsets.h"
#include "MrcHalRegisterAccess.h"
#include "MrcCommon.h"

///
/// Local Functions
///
/**
  This function returns the offset to access specific Strobe of DllWeakLock.

  @params[in]  Strobe - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
**/
static
UINT32
DllWeakLockOffset (
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  Offset  = DLLDDRDATA0_CR_DLLWEAKLOCK_REG;
  Offset += (DLLDDRDATA1_CR_DLLWEAKLOCK_REG - DLLDDRDATA0_CR_DLLWEAKLOCK_REG) * Strobe;

  return Offset;
}

/*

  This function returns the offset to access specific Channel/Strobe of DdrCrCmdBusTrain.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
*/
static
UINT32
CmdBusTrainOffset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  Offset  = DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG;
  Offset += (DATA0CH1_CR_DDRCRCMDBUSTRAIN_REG - DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG) * Channel +
            (DATA1CH0_CR_DDRCRCMDBUSTRAIN_REG - DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG) * Strobe;

  return Offset;
}

/*

  This function returns the offset to access specific Channel/Strobe of DataTrainFeedback.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
*/
static
UINT32
DataTrainFeedbackOffset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  Offset  = DATA0CH0_CR_DATATRAINFEEDBACK_REG;
  Offset += (DATA0CH1_CR_DATATRAINFEEDBACK_REG - DATA0CH0_CR_DATATRAINFEEDBACK_REG) * Channel +
            (DATA1CH0_CR_DATATRAINFEEDBACK_REG - DATA0CH0_CR_DATATRAINFEEDBACK_REG) * Strobe;

  return Offset;
}

/**
  This function returns the offset to access specific Channel/Strobe of DataControl0.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
**/
UINT32
DataControl0Offset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  Offset  = DATA0CH0_CR_DDRCRDATACONTROL0_REG;
  Offset += (DATA0CH1_CR_DDRCRDATACONTROL0_REG - DATA0CH0_CR_DDRCRDATACONTROL0_REG) * Channel +
            (DATA1CH0_CR_DDRCRDATACONTROL0_REG - DATA0CH0_CR_DDRCRDATACONTROL0_REG) * Strobe;

  return Offset;
}

/**
  This function returns the offset to access specific Channel/Strobe of DataControl1.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
**/
UINT32
DataControl1Offset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  Offset  = DATA0CH0_CR_DDRCRDATACONTROL1_REG;
  Offset += (DATA0CH1_CR_DDRCRDATACONTROL1_REG - DATA0CH0_CR_DDRCRDATACONTROL1_REG) * Channel +
            (DATA1CH0_CR_DDRCRDATACONTROL1_REG - DATA0CH0_CR_DDRCRDATACONTROL1_REG) * Strobe;

  return Offset;
}

/**
  This function returns the offset to access specific Channel/Strobe of DataControl2.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
**/
UINT32
DataControl2Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  Offset  = DATA0CH0_CR_DDRCRDATACONTROL2_REG;
  Offset += (DATA0CH1_CR_DDRCRDATACONTROL2_REG - DATA0CH0_CR_DDRCRDATACONTROL2_REG) * Channel +
            (DATA1CH0_CR_DDRCRDATACONTROL2_REG - DATA0CH0_CR_DDRCRDATACONTROL2_REG) * Strobe;

  return Offset;
}

/**
  This function returns the offset to access specific Channel/Strobe of DataControl3.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
**/
UINT32
DataControl3Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  Offset = DATA0CH0_CR_DDRCRDATACONTROL3_REG;
  Offset += (DATA0CH1_CR_DDRCRDATACONTROL3_REG - DATA0CH0_CR_DDRCRDATACONTROL3_REG) * Channel +
            (DATA1CH0_CR_DDRCRDATACONTROL3_REG - DATA0CH0_CR_DDRCRDATACONTROL3_REG) * Strobe;

  return Offset;
}

/**
  This function returns the offset to access specific Channel/Strobe of DataControl4.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
**/

UINT32
DataControl4Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  Offset  = DATA0CH0_CR_DDRCRDATACONTROL4_REG;
  Offset += (DATA0CH1_CR_DDRCRDATACONTROL4_REG - DATA0CH0_CR_DDRCRDATACONTROL4_REG) * Channel +
            (DATA1CH0_CR_DDRCRDATACONTROL4_REG - DATA0CH0_CR_DDRCRDATACONTROL4_REG) * Strobe;

  return Offset;
}

/**
  This function returns the offset to access specific Channel/Strobe of DataControl5.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
**/

UINT32
DataControl5Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  Offset  = DATA0CH0_CR_DDRCRDATACONTROL5_REG;
  Offset += (DATA0CH1_CR_DDRCRDATACONTROL5_REG - DATA0CH0_CR_DDRCRDATACONTROL5_REG) * Channel +
            (DATA1CH0_CR_DDRCRDATACONTROL5_REG - DATA0CH0_CR_DDRCRDATACONTROL5_REG) * Strobe;

  return Offset;
}

/*
  This function returns the offset to access specific Channel/Rank/Strobe of DataDqs.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Rank    - 0-based index of Rank to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
*/
static
UINT32
DataDqsOffset (
  IN  UINT32  const Channel,
  IN  UINT32  const Rank,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  Offset  = DATA0CH0_CR_DDRDATADQSRANK0_REG;
  Offset += (DATA0CH1_CR_DDRDATADQSRANK0_REG - DATA0CH0_CR_DDRDATADQSRANK0_REG) * Channel +
            (DATA0CH0_CR_DDRDATADQSRANK1_REG - DATA0CH0_CR_DDRDATADQSRANK0_REG) * Rank +
            (DATA1CH0_CR_DDRDATADQSRANK0_REG - DATA0CH0_CR_DDRDATADQSRANK0_REG) * Strobe;

  return Offset;
}

/*
  This function returns the offset to access specific Channel/Strobe of DataControl6.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
*/

UINT32
DataControl6Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  Offset = DATA0CH0_CR_DDRCRDATACONTROL6_REG;
  Offset += (DATA0CH1_CR_DDRCRDATACONTROL6_REG - DATA0CH0_CR_DDRCRDATACONTROL6_REG) * Channel +
    (DATA1CH0_CR_DDRCRDATACONTROL6_REG - DATA0CH0_CR_DDRCRDATACONTROL6_REG) * Strobe;

  return Offset;
}


/*
  This function returns the offset to access specific Channel/Strobe of DataControl7.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
*/
/*static
UINT32
DataControl7Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DATA_CR_DDRCRDATACONTROL7_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = DATACH0_CR_DDRCRDATACONTROL7_REG;
    Offset += (DATACH1_CR_DDRCRDATACONTROL7_REG - DATACH0_CR_DDRCRDATACONTROL7_REG) * Channel;
  } else {
    Offset = DATA0CH0_CR_DDRCRDATACONTROL7_REG;
    Offset += (DATA0CH1_CR_DDRCRDATACONTROL7_REG - DATA0CH0_CR_DDRCRDATACONTROL7_REG) * Channel +
      (DATA1CH0_CR_DDRCRDATACONTROL7_REG - DATA0CH0_CR_DDRCRDATACONTROL7_REG) * Strobe;
  }

  return Offset;
}*/

/*
  This function returns the offset to access specific Channel/Strobe of DataControl8.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
*/
/*static
UINT32
DataControl8Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DATA_CR_DDRCRDATACONTROL8_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = DATACH0_CR_DDRCRDATACONTROL8_REG;
    Offset += (DATACH1_CR_DDRCRDATACONTROL8_REG - DATACH0_CR_DDRCRDATACONTROL8_REG) * Channel;
  } else {
    Offset = DATA0CH0_CR_DDRCRDATACONTROL8_REG;
    Offset += (DATA0CH1_CR_DDRCRDATACONTROL8_REG - DATA0CH0_CR_DDRCRDATACONTROL8_REG) * Channel +
      (DATA1CH0_CR_DDRCRDATACONTROL8_REG - DATA0CH0_CR_DDRCRDATACONTROL8_REG) * Strobe;
  }

  return Offset;
}*/

/*
  This function returns the offset to access specific Channel/Rank/Strobe/Bit of DataDqRankXLaneY.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Rank    - 0-based index of Rank to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.
  @params[in]  Bit     - 0-based index of Bit to access.

  @retval UINT32 - CR offset
*/
static
UINT32
DataDqRankXLaneYOffset (
  IN  UINT32  const Channel,
  IN  UINT32  const Rank,
  IN  UINT32  const Strobe,
  IN  UINT32  const Bit
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DATA_CR_DDRDATADQRANK0LANE0_REG;
    Offset += (DATA_CR_DDRDATADQRANK1LANE0_REG - DATA_CR_DDRDATADQRANK0LANE0_REG) * Rank +
      (DATA_CR_DDRDATADQRANK0LANE1_REG - DATA_CR_DDRDATADQRANK0LANE0_REG) * Bit;
  } else {
    Offset = DATA0CH0_CR_DDRDATADQRANK0LANE0_REG;
    Offset += (DATA0CH1_CR_DDRDATADQRANK0LANE0_REG - DATA0CH0_CR_DDRDATADQRANK0LANE0_REG) * Channel +
      (DATA0CH0_CR_DDRDATADQRANK1LANE0_REG - DATA0CH0_CR_DDRDATADQRANK0LANE0_REG) * Rank +
      (DATA1CH0_CR_DDRDATADQRANK0LANE0_REG - DATA0CH0_CR_DDRDATADQRANK0LANE0_REG) * Strobe +
      (DATA0CH0_CR_DDRDATADQRANK0LANE1_REG - DATA0CH0_CR_DDRDATADQRANK0LANE0_REG) * Bit;
  }

  return Offset;
}

static
UINT32
WriteConfigOffset (
  IN  UINT32  const Channel
  )
{
  UINT32 Offset;

  Offset  = MCMISCS_WRITECFGCH0_REG;
  Offset += (MCMISCS_WRITECFGCH1_REG - MCMISCS_WRITECFGCH0_REG) * Channel;

  return Offset;
}

/**
  Function used to get the CR Offset for DATATCOCONTROL0/1.

  @param[in]  Channel - DDR Channel Number within the processor socket (0-based).
  @param[in]  Strobe  - DQS data group within the channel (0-based).
  @param[in]  Bit     - Bit within the strobe (0-based).

  @retval CR Offset.
**/
static
UINT32
GetDdrIoDataTcoControl(
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe,
  IN  UINT32  const   Bit
)
{
  UINT32 Offset;

  Offset = DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG;
  Offset += (DATA0CH1_CR_DDRCRDATATCOCONTROL0_REG - DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG) * Channel +
    (DATA1CH0_CR_DDRCRDATATCOCONTROL0_REG - DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG) * Strobe;

  if (Bit > 4) {
    Offset += (DATA0CH0_CR_DDRCRDATATCOCONTROL1_REG - DATA0CH0_CR_DDRCRDATATCOCONTROL0_REG);
  }

  return Offset;
}

/**
  Function used to get the CR Offset for Data Read Groups.

  @param[in]  Group       - DDRIO group being accessed.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Controller  - Memory controller in the processor socket (0-based).
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank        - Rank index in the channel. (0-based).
  @param[in]  Strobe      - Dqs data group within the rank (0-based).
  @param[in]  Bit         - Bit index within the data group (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
GetDdrIoDataReadOffsets (
  IN  MrcParameters   *MrcData,
  IN  GSM_GT          Group,
  IN  UINT32          Socket,
  IN  UINT32          Controller,
  IN  UINT32          Channel,
  IN  UINT32          Rank,
  IN  UINT32          Strobe,
  IN  UINT32          Bit,
  IN  UINT32          FreqIndex
  )
{
  UINT32  Offset;

  Offset  = MRC_UINT32_MAX;

  switch (Group) {
    case DqsOdtCompOffset:
    case RxBiasCtl:
    case RxVref:
      Offset = DataControl5Offset (Channel, Strobe);
      break;

    case RecEnDelay:
    case RxDqsPDelay:
    case RxDqsNDelay:
      Offset = DATA0CH0_CR_RXCONTROL0RANK0_REG +
        ((DATA0CH1_CR_RXCONTROL0RANK0_REG - DATA0CH0_CR_RXCONTROL0RANK0_REG) * Channel) +
        ((DATA0CH0_CR_RXCONTROL0RANK1_REG - DATA0CH0_CR_RXCONTROL0RANK0_REG) * Rank) +
        ((DATA1CH0_CR_RXCONTROL0RANK0_REG - DATA0CH0_CR_RXCONTROL0RANK0_REG) * Strobe);
      break;

    case RxPerBitDeskewCal:
      Offset = DataControl3Offset(Channel, Strobe);
      break;

    case RxTap0:
    case RxTap1:
    case RxC:
    case RxR:
    case RxEq:
      Offset = DataControl4Offset (Channel, Strobe);
      break;

    case RxDqBitDelay:
    case RxDqBitOffset:
    case RxVoc:
    case RxVocUnmatched:
      Offset = DataDqRankXLaneYOffset (Channel, Rank, Strobe, Bit);
      break;

    case RoundTripDelay:
      Offset = OFFSET_CALC_MC_CH (MC0_CH0_CR_SC_ROUNDTRIP_LATENCY_REG, MC1_CH0_CR_SC_ROUNDTRIP_LATENCY_REG, Controller, MC0_CH1_CR_SC_ROUNDTRIP_LATENCY_REG, (Channel / 2));
      break;

    case RxFlybyDelay:
      Offset  = MCMISCS_READCFGCH01_REG;
      Offset += (MCMISCS_READCFGCH23_REG - MCMISCS_READCFGCH01_REG) * (Channel / 2);
      break;

    case RxFifoRdEnFlybyDelay:
      Offset  = MCMISCS_RXDQFIFORDENCH01_REG;
      Offset += (MCMISCS_RXDQFIFORDENCH23_REG - MCMISCS_RXDQFIFORDENCH01_REG) * (Channel / 2);
      break;

    case RxIoTclDelay:
    case RxFifoRdEnTclDelay:
    case RxDqDataValidDclkDelay:
    case RxDqDataValidQclkDelay:
      Offset  = MCMISCS_READCFGCH0_REG;
      Offset += (MCMISCS_READCFGCH1_REG - MCMISCS_READCFGCH0_REG) * Channel;
      break;

    case SenseAmpDelay:
    case SenseAmpDuration:
    case McOdtDelay:
    case McOdtDuration:
    case DqsOdtDelay:
    case DqsOdtDuration:
      Offset = DataControl1Offset (Channel, Strobe);
      break;

    case RxVrefVttDecap:
    case RxVrefVddqDecap:
    case RxRankMuxDelay:
      Offset = DataControl2Offset (Channel, Strobe);
      break;

    case RxDqsAmpOffset:
    case RxDqsUnmatchedAmpOffset:
      Offset = DataDqsOffset (Channel, Rank, Strobe);
      break;

    case DataRxD0PiCb:
    case DataSDllPiCb:
      Offset = DataControl6Offset(Channel, Strobe);
      break;

    case VccDllRxD0PiCb:
    case VccDllSDllPiCb:
      Offset = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_REG;
      break;

    case RxCben:
      Offset = DLLDDRDATA0_CR_PITUNE_REG +
        ((DLLDDRDATA1_CR_PITUNE_REG - DLLDDRDATA0_CR_PITUNE_REG) * Strobe);
      break;

    case RloadDqsDn:
      Offset = DDRVCCDLL0_CR_DDRCRVCCDLLCOMPDLL_REG;
      break;

    case DqOdtVrefUp:
    case DqOdtVrefDn:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL0_REG;
      break;

    case CompRcompOdtUp:
    case CompRcompOdtDn:
      Offset = DDRPHY_COMP_CR_DDRCRDATACOMP1_REG;
      break;

    case PanicVttDnLp:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC2_REG;
      break;

    case VttGenStatusSelCount:
    case VttGenStatusCount:
      Offset = DDRVTT0_CR_DDRCRVTTGENSTATUS_REG +
        ((DDRVTT1_CR_DDRCRVTTGENSTATUS_REG - DDRVTT0_CR_DDRCRVTTGENSTATUS_REG) * Strobe);
      break;

    default:
      break;
  }

  return Offset;
}

/**
  Function used to get the CR Offset for Write Data Groups.

  @param[in]  Group       - DDRIO group being accessed.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank        - Rank index in the channel. (0-based).
  @param[in]  Strobe      - Dqs data group within the rank (0-based).
  @param[in]  Bit         - Bit index within the data group (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Core MRC)

  @retval CR Offset.
**/
UINT32
GetDdrIoDataWriteOffsets (
  IN  MrcParameters   *MrcData,
  IN  GSM_GT          Group,
  IN  UINT32          Socket,
  IN  UINT32          Channel,
  IN  UINT32          Rank,
  IN  UINT32          Strobe,
  IN  UINT32          Bit,
  IN  UINT32          FreqIndex
  )
{
  UINT32 Offset;

  Offset = MRC_UINT32_MAX;

  switch (Group) {
    case TxRankMuxDelay:
      Offset = DataControl0Offset (Channel, Strobe);
      break;

    case TxDqsRankMuxDelay:
      Offset = DataControl3Offset (Channel, Strobe);
      break;

    case TxDqsDelay:
    case TxDqDelay:
    case TxEq:
      Offset = DATA0CH0_CR_TXCONTROL0RANK0_REG +
        ((DATA0CH1_CR_TXCONTROL0RANK0_REG - DATA0CH0_CR_TXCONTROL0RANK0_REG) * Channel) +
        ((DATA0CH0_CR_TXCONTROL0RANK1_REG - DATA0CH0_CR_TXCONTROL0RANK0_REG) * Rank) +
        ((DATA1CH0_CR_TXCONTROL0RANK0_REG - DATA0CH0_CR_TXCONTROL0RANK0_REG) * Strobe);
      break;

    case TxDqBitDelay:
      Offset = DataDqRankXLaneYOffset (Channel, Rank, Strobe, Bit);
      break;

    case TxDqFifoRdEnFlybyDelay:
      Offset  = MCMISCS_WRITECFGCH01_REG;
      Offset += (MCMISCS_WRITECFGCH23_REG - MCMISCS_WRITECFGCH01_REG) * (Channel / 2);
      break;

    case TxDqFifoWrEnTcwlDelay:
    case TxDqFifoRdEnTcwlDelay:
      Offset = WriteConfigOffset (Channel);
      break;

    case TxRonUp:
    case TxRonDn:
    case SCompCodeDq:
      Offset = DDRPHY_COMP_CR_DDRCRDATACOMP0_REG;
      break;

    case TxTco:
      Offset = GetDdrIoDataTcoControl (Channel, Strobe, Bit);
      break;

    case TxDqsTco:
    case TxDqsBitDelay:
      Offset = DataDqsOffset (Channel, Rank, Strobe);
      break;

    case DqDrvVrefUp:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL4_REG;
      break;

    case DqDrvVrefDn:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL3_REG;
      break;

    case TxPerBitDeskewCal:
    case SCompBypassDq:
      Offset = DataControl2Offset (Channel, Strobe);
      break;

    case DqScompPC:
    case TxSlewRate:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL1_REG;
      break;

    default:
      break;
    }

  return Offset;
}

/**
  Function used to get the CR Offset for training offset and comp offset Groups.

  @param[in]  MrcData   - Global MRC data structure.
  @param[in]  Group     - DDRIO group being accessed.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  Rank      - Rank index in the channel. (0-based).
  @param[in]  Strobe    - Dqs data group within the rank (0-based).
  @param[in]  Bit       - Bit index within the data group (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
GetDdrIoDataTrainOffsets (
  IN MrcParameters    *MrcData,
  IN  GSM_GT          Group,
  IN  UINT32          Socket,
  IN  UINT32          Channel,
  IN  UINT32          Rank,
  IN  UINT32          Strobe,
  IN  UINT32          Bit,
  IN  UINT32          FreqIndex
  )
{
  UINT32 Offset;

  Offset = MRC_UINT32_MAX;

  switch (Group) {
    case RecEnOffset:
    case RxDqsOffset:
    case RxVrefOffset:
    case TxDqsOffset:
    case TxDqOffset:
      Offset = DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG +
        ((DATA0CH1_CR_DDRCRDATAOFFSETTRAIN_REG - DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Channel) +
        ((DATA1CH0_CR_DDRCRDATAOFFSETTRAIN_REG - DATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Strobe);
      break;

    case CompOffsetAll:
    case CompOffsetVssHiFF:
      Offset = DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG +
        ((DATA0CH1_CR_DDRCRDATAOFFSETCOMP_REG - DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG) * Channel) +
        ((DATA1CH0_CR_DDRCRDATAOFFSETCOMP_REG - DATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG) * Strobe);
      break;

    default:
      break;
  }

  return Offset;
}

/**
  Function used to get the CR Offset for DDR IO Configuration settings.

  @param[in]  MrcData     - Global MRC data structure.
  @param[in]  Group       - DDRIO group being accessed.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel     - DDR Channel within the Memory Controller Number(0-based).
  @param[in]  Rank        - Rank index in the channel. (0-based).
  @param[in]  Strobe      - Dqs data group within the rank (0-based).
  @param[in]  Bit         - Bit index within the data group (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
MrcGetDdrIoConfigOffsets (
  IN MrcParameters    *MrcData,
  IN  GSM_GT          Group,
  IN  UINT32          Socket,
  IN  UINT32          Channel,
  IN  UINT32          Rank,
  IN  UINT32          Strobe,
  IN  UINT32          Bit,
  IN  UINT32          FreqIndex
  )
{
  UINT32 Offset;

  Offset = MRC_UINT32_MAX;

  switch (Group) {
    case GsmIocWlWakeCyc:
    case GsmIocWlSleepCyclesAct:
    case GsmIocWlSleepCyclesLp:
    case GsmIocDllMask:
    case GsmIocDllWeakLock:
    case GsmIocDllWeakLock1:
      Offset = DllWeakLockOffset (Strobe);
      break;

    case GsmIocForceCmpUpdt:
//    case GsmIocWlLatency: // @todo No TGL version found
    case GsmIocNoDqInterleave:
    case GsmIocScramLpMode:
    case GsmIocScramDdr4Mode:
    case GsmIocScramDdr5Mode:
    case GsmIocScramGear1:
    case GsmIocDisClkGate:
    case GsmIocDisDataIdlClkGate:
    case GsmIocScramLp4Mode:
    case GsmIocScramLp5Mode:
    case GsmIocScramOvrdPeriodicToDvfsComp:
    case GsmIocChNotPop:
    case GsmIocDisIosfSbClkGate:
    case GsmIocLp5Wck2CkRatio:
    case GsmIocEccEn:
      Offset = DDRSCRAM_CR_DDRMISCCONTROL0_REG;
      break;

    case GsmIocVccDllRxDeskewCal:
    case GsmIocVccDllTxDeskewCal:
    case GsmIocVccDllCccDeskewCal:
      Offset = DDRPHY_COMP_CR_VCCDLLREPLICACTRL2_REG;
      break;

    case GsmIocVccDllControlBypass_V:
    case GsmIocVccDllControlSelCode_V:
    case GsmIocVccDllControlTarget_V:
    case GsmIocVccDllControlOpenLoop_V:
      Offset = (Strobe) ? DDRVCCDLL1_CR_DDRCRVCCDLLCONTROL_REG : DDRVCCDLL0_CR_DDRCRVCCDLLCONTROL_REG;
      break;

    case GsmIocVsxHiControlSelCode_V:
    case GsmIocVsxHiControlOpenLoop_V:
      Offset = DDRVSSHIAFEA_CR_DDRCRVSSHICONTROL_REG;
      break;

    case GsmIocCccPiEn:
    case GsmIocCccPiEnOverride:
      Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRPINSUSED_REG, CH1CCC_CR_DDRCRPINSUSED_REG, Channel);
      break;

    case GsmIocVccDllGear1:
      Offset = DDRPHY_COMP_CR_VCCDLLDQSDELAY_REG;
      break;

    case GsmIocIoReset:
      Offset = DDRSCRAM_CR_DDRMISCCONTROL1_REG;
      break;

    case GsmIocReadDqDqsMode:
    case GsmIocSenseAmpMode:
    case GsmIocCaTrainingMode:
    case GsmIocWriteLevelMode:
    case GsmIocReadLevelMode:
    case GsmIocRankOverrideEn:
    case GsmIocRankOverrideVal:
    case GsmIocDataTrainFeedback:
    case GsmIocRxAmpOffsetEn:
      Offset = DataTrainFeedbackOffset (Channel, Strobe);
      break;

    case GsmIocForceRxAmpOn:
    case GsmIocForceOdtOn:
    case GsmIocDataOdtStaticDis:
    case GsmIocTxPiPwrDnDis:
    case GsmIocTxDisable:
    case GsmIocInternalClocksOn:
    case GsmIocTxOn:
    case GsmIocRxDisable:
    case GsmIocWlLongDelEn:
    case GsmIocBiasPMCtrl:
    case GsmIocDataOdtMode:
    case GsmIocRxVocMode:
    case GsmIocDataDqsOdtParkMode:
    case GsmIocDataDqOdtParkMode:
    case GsmIocDataDqsNParkLow:
      Offset = DataControl0Offset (Channel, Strobe);
      break;

    case GsmIocSdllSegmentDisable:
    case GsmIocRXDeskewForceOn:
      Offset = DataControl1Offset (Channel, Strobe);
      break;

    case GsmIocDataCtlGear1:
    case GsmIocDataWrPreamble:
      Offset = DataControl3Offset (Channel, Strobe);
      break;

//    case GsmIocLeakerComp: // @todo No TGL version found
//    case GsmIocRxTypeSelect: // @todo No TGL version found
//    case GsmIocRxPathBiasRcomp: // @todo No TGL version found
//    case GsmIocRxPathBiasSel: // @todo No TGL version found
//      Offset = DataControl4Offset (Channel, Strobe);
//      break;

    case GsmIocStrobeOdtStaticDis:
    case GsmIocDqSlewDlyByPass:
    case GsmIocRxVrefMFC:
    case GsmIocTxEqDis:
    case GsmIocConstZTxEqEn:
//    case GsmIocVrefPwrDnEn: // @todo No TGL version found
    case GsmIocRxClkStg:
    case GsmIocDataRxBurstLen:
    case GsmIocEnDqsNRcvEn:
      Offset = DataControl2Offset (Channel, Strobe);
      break;

    case GsmIocDqsMaskPulseCnt:
    case GsmIocDqsPulseCnt:
    case GsmIocDqOverrideData:
    case GsmIocDqOverrideEn:
      Offset = CmdBusTrainOffset (Channel, Strobe);
      break;

    case GsmIocFFCodeIdleOffset:
    case GsmIocFFCodeWeakOffset:
    case GsmIocFFCodePiOffset:
    case GsmIocFFCodeWriteOffset:
    case GsmIocFFCodeReadOffset:
    case GsmIocFFCodePBDOffset:
    case GsmIocFFCodeCCCDistOffset:
        Offset = VccDllDataCCCCompOffset (Channel, Strobe);
        break;

    case GsmIocDataODTSingleSegEn:
    case GsmIocRxPiPwrDnDis:
    case GsmIocDataInvertNibble:
      Offset = DataControl5Offset (Channel, Strobe);
      break;

    case GsmIocCapCancelCodeIdle:
    case GsmIocCapCancelCodePBD:
    case GsmIocCapCancelCodeWrite:
    case GsmIocCapCancelCodeRead:
    case GsmIocCapCancelCodePi:
      Offset = CouplingCapOffset (Channel, Strobe);
      break;

    case GsmIocVssHiFFCodeIdle:
    case GsmIocVssHiFFCodeWrite:
    case GsmIocVssHiFFCodeRead:
    case GsmIocVssHiFFCodePBD:
    case GsmIocVssHiFFCodePi:
      Offset = VssHiFFOffset (Channel, Strobe);
      break;

    case GsmIocEnableSpineGate:
      Offset = MCMISCS_SPINEGATING_REG;
      break;

    case GsmIocCmdVrefConverge:
      Offset = DDRVREF_CR_DDRCRVREFADJUST2_REG;
      break;

    case GsmIocCompVddqOdtEn:
    case GsmIocCompVttOdtEn:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL0_REG;
      break;

    case GsmIocCompOdtStaticDis:
    case GsmIocCompClkOn:
    case GsmIocDisableQuickComp:
    case GsmIocSinStep:
    case GsmIocSinStepAdv:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL1_REG;
      break;

    case GsmIocVttPanicCompUpMult:
    case GsmIocVttPanicCompDnMult:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPVTTPANIC_REG;
      break;

    case GsmIocCmdDrvVref200ohm:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL2_REG;
      break;

    case GsmIocRptChRepClkOn:
    case GsmIocCmdAnlgEnGraceCnt:
    case GsmIocTxAnlgEnGraceCnt:
    case GsmIocTxDqFifoRdEnPerRankDelDis:
      Offset = WriteConfigOffset (Channel);
      break;

    default:
      break;
    }

  return Offset;
}

/**
  Function used to get the CR Offset for DDR IO Command Groups.

  @param[in]  MrcData     - Global MRC data structure.
  @param[in]  Group       - DDRIO group being accessed.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  GroupIndex  - Index for command group types that specify indicies (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
GetDdrIoCommandOffsets (
  IN MrcParameters    *MrcData,
  IN  GSM_GT          Group,
  IN  UINT32          Socket,
  IN  UINT32          Channel,
  IN  UINT32          GroupIndex,
  IN  UINT32          FreqIndex
  )
{
  UINT32  Offset;
  BOOLEAN Ddr4;

  Offset  = MRC_UINT32_MAX;
  Ddr4    = (MrcData->Outputs.DdrType == MRC_DDR_TYPE_DDR4);

  switch (Group) {
    case CmdGrpPi:
    case CtlGrpPi:
      Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCCCPICODING0_REG, CH1CCC_CR_DDRCRCCCPICODING0_REG, Channel);
      break;

    case CkeGrpPi:
      if (Ddr4) {
        Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCCCPICODING0_REG, CH1CCC_CR_DDRCRCCCPICODING0_REG, Channel);
        break;
      }
      /*FALLTHROUGH*/
      //fall through for LPDDR
    case ClkGrpPi:
    case WckGrpPi:
      Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCCCPICODING1_REG, CH1CCC_CR_DDRCRCCCPICODING1_REG, Channel);
      break;

    case CmdVref:
      Offset = DDRVREF_CR_DDRCRVREFADJUST1_REG;
      break;

    case CmdSCompOffset:
    case CmdRCompDrvDownOffset:
    case CmdRCompDrvUpOffset:
    case CkeSCompOffset:
    case CkeRCompDrvDownOffset:
    case CkeRCompDrvUpOffset:
    case CtlSCompOffset:
    case CtlRCompDrvDownOffset:
    case CtlRCompDrvUpOffset:
      Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCTLCACOMPOFFSET_REG, CH1CCC_CR_DDRCRCTLCACOMPOFFSET_REG, Channel);
      break;

    case VsxHiClkFFOffset:
    case VsxHiCaFFOffset:
    case VsxHiCtlFFOffset:
    case ClkSCompOffset:
    case ClkRCompDrvDownOffset:
    case ClkRCompDrvUpOffset:
      Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG, CH1CCC_CR_DDRCRVSSHICLKCOMPOFFSET_REG, Channel);
      break;

    case CmdTxEq:
    case CtlTxEq:
      Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCCCCLKCONTROLS_REG, CH1CCC_CR_DDRCRCCCCLKCONTROLS_REG, Channel);
      break;

    case WrDSCodeUpCmd:
    case WrDSCodeDnCmd:
    case SCompCodeCmd:
    case TcoCompCodeCmd:
      Offset = DDRPHY_COMP_CR_DDRCRCACOMP_REG;
      break;

    case SCompBypassCmd:
    case SCompBypassCtl:
    case SCompBypassClk:
      Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRPINSUSED_REG, CH1CCC_CR_DDRCRPINSUSED_REG, Channel);
      break;

    case WrDSCodeUpCtl:
    case WrDSCodeDnCtl:
    case SCompCodeCtl:
    case TcoCompCodeCtl:
      Offset = DDRPHY_COMP_CR_DDRCRCTLCOMP_REG;
      break;

    case WrDSCodeUpClk:
    case WrDSCodeDnClk:
    case SCompCodeClk:
    case TcoCompCodeClk:
      Offset = DDRPHY_COMP_CR_DDRCRCLKCOMP_REG;
      break;

    case CmdDrvVrefUp:
    case CtlDrvVrefUp:
    case ClkDrvVrefUp:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL2_REG;
      break;

    case CmdDrvVrefDn:
    case CtlDrvVrefDn:
    case ClkDrvVrefDn:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL3_REG;
      break;

    case CmdSlewRate:
    case CmdScompPC:
    case CtlSlewRate:
    case CtlScompPC:
    case ClkSlewRate:
    case ClkScompPC:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL1_REG;
      break;

    case CccPerBitDeskewCal:
      Offset = OFFSET_CALC_CH (CH0CCC_CR_DDRCRCCCPERBITDESKEW0_REG, CH1CCC_CR_DDRCRCCCPERBITDESKEW0_REG, Channel);
      break;

    case CtlGrp0:
    case CtlGrp1:
    case CtlGrp2:
    case CtlGrp3:
    case CtlGrp4:
    case CmdGrp0:
    case CmdGrp1:
    case CmdGrp2:
    case CkAll:
    case CmdAll:
    case CtlAll:
    default:
      break;
    }

  return Offset;
}

/**
  This function handles getting the register offset for the requested parameter.
  It will determine multicast by the parameter exceeding the MAX of the
  Socket/Channel/Rank/Strobe/Bit.

  @param[in]  MrcData     - Pointer to global data.
  @param[in]  Group       - DDRIO group to access.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Controller  - Memory controller in the processor socket (0-based).
  @param[in]  Channel     - DDR Channel Number within the memory controller (0-based).
  @param[in]  Rank        - Rank number within a channel (0-based).
  @param[in]  Strobe      - Dqs data group within the rank (0-based).
  @param[in]  Bit         - Bit index within the data group (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset
**/
UINT32
MrcGetDdrIoRegOffset (
  IN  MrcParameters *const  MrcData,
  IN  GSM_GT  const         Group,
  IN  UINT32  const         Socket,
  IN  UINT32  const         Controller,
  IN  UINT32  const         Channel,
  IN  UINT32  const         Rank,
  IN  UINT32  const         Strobe,
  IN  UINT32  const         Bit,
  IN  UINT32  const         FreqIndex
  )
{
  UINT32 Offset = MRC_UINT32_MAX;

  switch (Group) {
    case PanicVttDnLp:
    case VttGenStatusSelCount:
    case VttGenStatusCount:
    case RxVrefVttDecap:
    case RxVrefVddqDecap:
    case DqsOdtCompOffset:
    case DqOdtVrefUp:
    case DqOdtVrefDn:
    case CompRcompOdtUp:
    case CompRcompOdtDn:
    case RecEnDelay:
    case RxDqsPDelay:
    case RxDqsNDelay:
    case RxVref:
    case RxTap0:
    case RxTap1:
    case RxC:
    case RxR:
    case RxEq:
    case RxDqBitDelay:
    case RxDqBitOffset:
    case RoundTripDelay:
    case RxFlybyDelay:
    case RxIoTclDelay:
    case RxFifoRdEnFlybyDelay:
    case RxFifoRdEnTclDelay:
    case RxDqDataValidDclkDelay:
    case RxDqDataValidQclkDelay:
    case SenseAmpDelay:
    case SenseAmpDuration:
    case McOdtDelay:
    case McOdtDuration:
    case DqsOdtDelay:
    case DqsOdtDuration:
    case RxBiasCtl:
    case RxDqsAmpOffset:
    case RxDqsUnmatchedAmpOffset:
    case VccDllRxD0PiCb:
    case VccDllSDllPiCb:
    case DataRxD0PiCb:
    case DataSDllPiCb:
    case RxCben:
    case RloadDqsDn:
    case RxVoc:
    case RxVocUnmatched:
    case RxRankMuxDelay:
    case RxPerBitDeskewCal:
      Offset = GetDdrIoDataReadOffsets (MrcData, Group, Socket, Controller, Channel, Rank, Strobe, Bit, FreqIndex);
      break;

    case DqScompPC:
    case TxSlewRate:
    case TxTco:
    case TxDqsTco:
    case TxDqsBitDelay:
    case DqDrvVrefUp:
    case DqDrvVrefDn:
    case SCompCodeDq:
    case SCompBypassDq:
    case TxRonUp:
    case TxRonDn:
    case TxDqsDelay:
    case TxDqDelay:
    case TxEq:
    case TxRankMuxDelay:
    case TxDqsRankMuxDelay:
    case TxDqBitDelay:
    case TxDqFifoWrEnTcwlDelay:
    case TxDqFifoRdEnTcwlDelay:
    case TxDqFifoRdEnFlybyDelay:
    case TxPerBitDeskewCal:
      Offset = GetDdrIoDataWriteOffsets (MrcData, Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex);
      break;

    case RecEnOffset:
    case RxDqsOffset:
    case RxVrefOffset:
    case TxDqsOffset:
    case TxDqOffset:
    case CompOffsetVssHiFF:
      Offset = GetDdrIoDataTrainOffsets (MrcData, Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex);
      break;

    case SCompCodeCmd:
    case TcoCompCodeCmd:
    case SCompBypassCmd:
    case SCompBypassCtl:
    case SCompBypassClk:
    case SCompCodeCtl:
    case TcoCompCodeCtl:
    case SCompCodeClk:
    case TcoCompCodeClk:
    case CmdDrvVrefUp:
    case CmdDrvVrefDn:
    case CtlDrvVrefUp:
    case CtlDrvVrefDn:
    case ClkDrvVrefUp:
    case ClkDrvVrefDn:
    case CmdSlewRate:
    case CmdScompPC:
    case CtlSlewRate:
    case CtlScompPC:
    case ClkSlewRate:
    case ClkScompPC:
    case CtlGrpPi:
    case CkeGrpPi:
    case CmdGrpPi:
    case ClkGrpPi:
    case WckGrpPi:
    case CmdVref:
    case CmdRCompDrvDownOffset:
    case CmdRCompDrvUpOffset:
    case CmdSCompOffset:
    case CtlRCompDrvDownOffset:
    case CtlRCompDrvUpOffset:
    case CtlSCompOffset:
    case ClkRCompDrvDownOffset:
    case ClkRCompDrvUpOffset:
    case ClkSCompOffset:
//    case ClkCompOnTheFlyUpdtEn:
    case CkeRCompDrvDownOffset:
    case CkeRCompDrvUpOffset:
    case CkeSCompOffset:
    case CmdTxEq:
    case CtlTxEq:
    case VsxHiClkFFOffset:
    case VsxHiCaFFOffset:
    case VsxHiCtlFFOffset:
      Offset = GetDdrIoCommandOffsets (MrcData, Group, Socket, Channel, Strobe, FreqIndex);
      break;

    case WrDSCodeUpCmd:
    case WrDSCodeDnCmd:
    case WrDSCodeUpCtl:
    case WrDSCodeDnCtl:
    case WrDSCodeUpClk:
    case WrDSCodeDnClk:
    case CccPerBitDeskewCal:
      Offset = GetDdrIoCommandOffsets (MrcData, Group, Socket, Channel, Strobe, FreqIndex);
      break;

    default:
      break;
  }

  return Offset;
}

// These functions are called in DdrioInit()
/**
  This function returns the offset to access specific Channel/Strobe of Cbt.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval CR Offset
**/

UINT32
CbtOffset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DATA_CR_DDRCRCMDBUSTRAIN_REG;
  } else {
    Offset = DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG;
    Offset += (DATA0CH1_CR_DDRCRCMDBUSTRAIN_REG - DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG) * Channel +
      (DATA1CH0_CR_DDRCRCMDBUSTRAIN_REG - DATA0CH0_CR_DDRCRCMDBUSTRAIN_REG) * Strobe;
  }
  return Offset;
}

/**
  This function returns the offset to access specific Channel/Strobe of CbtTune0.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval CR Offset
**/

UINT32
CBTune0Offset (
  IN  UINT32  const   DllBlock
  )
{
  UINT32 Offset;
    Offset = DLLDDRDATA0_CR_CBTUNE0_REG;
    Offset += (DLLDDRDATA1_CR_CBTUNE0_REG - DLLDDRDATA0_CR_CBTUNE0_REG) * DllBlock;
  return Offset;
}

/**
  This function returns the offset to access specific Channel/Strobe of CbtTune1.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval CR Offset
**/

UINT32
CBTune1Offset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
  // Overall Broadcast
    Offset = DLLDDR_CR_CBTUNE1_REG;
  } else {
    Offset = DLLDDRDATA0_CR_CBTUNE1_REG;
    Offset += (DLLDDRDATA1_CR_CBTUNE1_REG - DLLDDRDATA0_CR_CBTUNE1_REG) * Strobe;
  }
  return Offset;
}

/**
  This function returns the offset to access specific Channel/Strobe of WrRetrainControlStatus.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval CR Offset
**/

UINT32
WrRetrainControlStatusOffset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset =  DATA_CR_DDRCRWRRETRAINCONTROLSTATUS_REG;
  } else {
    Offset = DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG;
    Offset += (DATA0CH1_CR_DDRCRWRRETRAINCONTROLSTATUS_REG - DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG) * Channel +
      (DATA1CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG - DATA0CH0_CR_DDRCRWRRETRAINCONTROLSTATUS_REG) * Strobe;
  }
  return Offset;
}

/**
  This function returns the offset to access specific Channel/Strobe of MarginModeControl.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval CR Offset
**/

UINT32
MarginModeControlOffset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DATA_CR_DDRCRMARGINMODECONTROL0_REG;
  } else {
    Offset = DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG;
    Offset += (DATA0CH1_CR_DDRCRMARGINMODECONTROL0_REG - DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG) * Channel +
      (DATA1CH0_CR_DDRCRMARGINMODECONTROL0_REG - DATA0CH0_CR_DDRCRMARGINMODECONTROL0_REG) * Strobe;
  }
  return Offset;
}

/**
  This function returns the offset to access specific VccDllComp register.
  There are 12 VccDll partitions, 8 for data and 4 for CCC

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval CR Offset
**/
UINT32
VccDllDataCCCCompOffset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;
  if (Channel != MRC_IGNORE_ARG) {
    Offset = OFFSET_CALC_CH (DLLDDRCCC0_CR_DDRCRVCCDLLCOMPOFFSET_REG, DLLDDRCCC1_CR_DDRCRVCCDLLCOMPOFFSET_REG, Channel);
  } else {
    Offset = DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_REG;
    Offset += (DLLDDRDATA1_CR_DDRCRVCCDLLCOMPOFFSET_REG - DLLDDRDATA0_CR_DDRCRVCCDLLCOMPOFFSET_REG) * Strobe;
  }
  return Offset;
}

/**
  This function returns the offset to access specific VccDllCouplingCap registers.
  There are 12 VccDll partitions, 8 for data and 4 for CCC

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval CR Offset
**/
UINT32
CouplingCapOffset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;
  if (Channel != MRC_IGNORE_ARG) {
    Offset = OFFSET_CALC_CH (DLLDDRCCC0_CR_DDRCRVCCDLLCOUPLINGCAP_REG, DLLDDRCCC1_CR_DDRCRVCCDLLCOUPLINGCAP_REG, Channel);
  } else {
    Offset = DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_REG;
    Offset += (DLLDDRDATA1_CR_DDRCRVCCDLLCOUPLINGCAP_REG - DLLDDRDATA0_CR_DDRCRVCCDLLCOUPLINGCAP_REG) * Strobe;
  }
  return Offset;
}

/**
  This function returns the offset to access specific VccDllVssHiFF (VsxHi is used interchangeably for VssHi) registers.
  There are 12 VccDll partitions, 8 for data and 4 for CCC. Since VccDll injects alot of current to VssHi rail therefore
  MRC needs to run VssHi compensation for feedforward legs.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval CR Offset
**/
UINT32
VssHiFFOffset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;
  if (Channel != MRC_IGNORE_ARG) {
    Offset = OFFSET_CALC_CH (DLLDDRCCC0_CR_DDRCRVCCDLLVSXHIFF_REG, DLLDDRCCC1_CR_DDRCRVCCDLLVSXHIFF_REG, Channel);
  } else {
    Offset = DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_REG;
    Offset += (DLLDDRDATA1_CR_DDRCRVCCDLLVSXHIFF_REG - DLLDDRDATA0_CR_DDRCRVCCDLLVSXHIFF_REG) * Strobe;
  }
  return Offset;
}
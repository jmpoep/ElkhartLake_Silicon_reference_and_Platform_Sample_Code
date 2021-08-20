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

#include "MrcCommon.h"
#include "McAddress.h"
#include "MrcInterface.h"
#include "MrcDdrIoOffsets.h"
#include "MrcHalRegisterAccess.h"
///
/// Local Functions
///

/*

  This function returns the offset to access specific Channel/Strobe of DataControl0.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Byte    - 0-based index of Byte to access.

  @retval UINT32 - CR offset
*/
static
UINT32
DataControl0Offset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DDRCRDATACONTROL0_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = DDRDATACH0_CR_DDRCRDATACONTROL0_REG;
    Offset += (DDRDATACH1_CR_DDRCRDATACONTROL0_REG - DDRDATACH0_CR_DDRCRDATACONTROL0_REG) * Channel;
  } else {
    Offset = DDRDATA0CH0_CR_DDRCRDATACONTROL0_REG;
    Offset += (DDRDATA0CH1_CR_DDRCRDATACONTROL0_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL0_REG) * Channel +
              (DDRDATA1CH0_CR_DDRCRDATACONTROL0_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL0_REG) * Strobe;
  }

  return Offset;
}

/*

  This function returns the offset to access specific Channel/Strobe of DataControl1.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Byte    - 0-based index of Byte to access.

  @retval UINT32 - CR offset
*/
static
UINT32
DataControl1Offset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DDRCRDATACONTROL1_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset  = DDRDATACH0_CR_DDRCRDATACONTROL1_REG;
    Offset += (DDRDATACH1_CR_DDRCRDATACONTROL1_REG - DDRDATACH0_CR_DDRCRDATACONTROL1_REG) * Channel;
  } else {
    Offset  = DDRDATA0CH0_CR_DDRCRDATACONTROL1_REG;
    Offset += (DDRDATA0CH1_CR_DDRCRDATACONTROL1_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL1_REG) * Channel +
              (DDRDATA1CH0_CR_DDRCRDATACONTROL1_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL1_REG) * Strobe;
  }

  return Offset;
}

/*
  This function returns the offset to access specific Channel/Strobe of DataControl2.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Byte    - 0-based index of Byte to access.

  @retval UINT32 - CR offset
*/
static
UINT32
DataControl2Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DDRCRDATACONTROL2_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset  = DDRDATACH0_CR_DDRCRDATACONTROL2_REG;
    Offset += (DDRDATACH1_CR_DDRCRDATACONTROL2_REG - DDRDATACH0_CR_DDRCRDATACONTROL2_REG) * Channel;
  } else {
    Offset  = DDRDATA0CH0_CR_DDRCRDATACONTROL2_REG;
    Offset += (DDRDATA0CH1_CR_DDRCRDATACONTROL2_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL2_REG) * Channel +
              (DDRDATA1CH0_CR_DDRCRDATACONTROL2_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL2_REG) * Strobe;
  }

  return Offset;
}

/*
  This function returns the offset to access specific Channel/Strobe of DataControl3.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Byte    - 0-based index of Byte to access.

  @retval UINT32 - CR offset
*/
static
UINT32
DataControl3Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DDRCRDATACONTROL3_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = DDRDATACH0_CR_DDRCRDATACONTROL3_REG;
    Offset += (DDRDATACH1_CR_DDRCRDATACONTROL3_REG - DDRDATACH0_CR_DDRCRDATACONTROL3_REG) * Channel;
  } else {
    Offset = DDRDATA0CH0_CR_DDRCRDATACONTROL3_REG;
    Offset += (DDRDATA0CH1_CR_DDRCRDATACONTROL3_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL3_REG) * Channel +
              (DDRDATA1CH0_CR_DDRCRDATACONTROL3_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL3_REG) * Strobe;
  }

  return Offset;
}

/*
  This function returns the offset to access specific Channel/Strobe of DataControl4.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Byte    - 0-based index of Byte to access.

  @retval UINT32 - CR offset
*/
static
UINT32
DataControl4Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DDRCRDATACONTROL4_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = DDRDATACH0_CR_DDRCRDATACONTROL4_REG +
              (DDRDATACH1_CR_DDRCRDATACONTROL4_REG - DDRDATACH0_CR_DDRCRDATACONTROL4_REG) * Channel;
  } else {
    Offset  = DDRDATA0CH0_CR_DDRCRDATACONTROL4_REG;
    Offset += (DDRDATA0CH1_CR_DDRCRDATACONTROL4_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL4_REG) * Channel +
              (DDRDATA1CH0_CR_DDRCRDATACONTROL4_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL4_REG) * Strobe;
  }

  return Offset;
}

static
UINT32
DataControl5Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DDRCRDATACONTROL5_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = DDRDATACH0_CR_DDRCRDATACONTROL5_REG +
              (DDRDATACH1_CR_DDRCRDATACONTROL5_REG - DDRDATACH0_CR_DDRCRDATACONTROL5_REG) * Channel;
  } else {
    Offset  = DDRDATA0CH0_CR_DDRCRDATACONTROL5_REG;
    Offset += (DDRDATA0CH1_CR_DDRCRDATACONTROL5_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL5_REG) * Channel +
              (DDRDATA1CH0_CR_DDRCRDATACONTROL5_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL5_REG) * Strobe;
  }

  return Offset;
}

static
UINT32
DataControl6Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DDRCRDATACONTROL6_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = DDRDATACH0_CR_DDRCRDATACONTROL6_REG +
      (DDRDATACH1_CR_DDRCRDATACONTROL6_REG - DDRDATACH0_CR_DDRCRDATACONTROL6_REG) * Channel;
  } else {
    Offset = DDRDATA0CH0_CR_DDRCRDATACONTROL6_REG;
    Offset += (DDRDATA0CH1_CR_DDRCRDATACONTROL6_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL6_REG) * Channel +
              (DDRDATA1CH0_CR_DDRCRDATACONTROL6_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL6_REG) * Strobe;
  }

  return Offset;
}

static
UINT32
DataControl7Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DDRCRDATACONTROL7_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = DDRDATACH0_CR_DDRCRDATACONTROL7_REG +
      (DDRDATACH1_CR_DDRCRDATACONTROL7_REG - DDRDATACH0_CR_DDRCRDATACONTROL7_REG) * Channel;
  } else {
    Offset = DDRDATA0CH0_CR_DDRCRDATACONTROL7_REG;
    Offset += (DDRDATA0CH1_CR_DDRCRDATACONTROL7_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL7_REG) * Channel +
              (DDRDATA1CH0_CR_DDRCRDATACONTROL7_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL7_REG) * Strobe;
  }

  return Offset;
}

static
UINT32
DataControl8Offset (
  IN  UINT32  const Channel,
  IN  UINT32  const Strobe
  )
{
  UINT32 Offset;

  if (Channel >= MAX_CHANNEL) {
    // Overall Broadcast
    Offset = DDRDATA_CR_DDRCRDATACONTROL8_REG;
  } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
    // Channel Broadcast
    Offset = OFFSET_CALC_CH (DDRDATACH0_CR_DDRCRDATACONTROL8_REG, DDRDATACH1_CR_DDRCRDATACONTROL8_REG, Channel);
  } else {
    Offset = DDRDATA0CH0_CR_DDRCRDATACONTROL8_REG;
    Offset += (DDRDATA0CH1_CR_DDRCRDATACONTROL8_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL8_REG) * Channel +
              (DDRDATA1CH0_CR_DDRCRDATACONTROL8_REG - DDRDATA0CH0_CR_DDRCRDATACONTROL8_REG) * Strobe;
  }
  return Offset;
}

static
UINT32
WriteConfigOffset (
  IN  UINT32  const Channel,
  IN  UINT32  const SubCh
  )
{
  UINT32 Offset;

  Offset  = MCMISCS_WRITECFGCH0_REG;
  Offset += ((MCMISCS_WRITECFGCH1_REG - MCMISCS_WRITECFGCH0_REG) * SubCh) +
            ((MCMISCS_WRITECFGCH2_REG - MCMISCS_WRITECFGCH0_REG) * Channel);

  return Offset;
}

/**
  Function used to get the CR Offset for Data Read Groups.

  @param[in]  Group       - DDRIO group being accessed.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  SubChannel  - DDR SubChannel Number (0-based).
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
  IN  UINT32          Channel,
  IN  UINT32          SubChannel,
  IN  UINT32          Rank,
  IN  UINT32          Strobe,
  IN  UINT32          Bit,
  IN  UINT32          FreqIndex
  )
{
  UINT32  Offset;

  Offset  = MRC_UINT32_MAX;

  switch (Group) {
    case RxVref:
      Offset = DataControl5Offset (Channel, Strobe);
      break;

    case RecEnDelay:
    case RxDqsPDelay:
    case RxDqsNDelay:
    case RxEq:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        Offset = DDRDATA_CR_RXCONTROL0RANK0_REG;
        Offset += ((DDRDATA_CR_RXCONTROL0RANK1_REG - DDRDATA_CR_RXCONTROL0RANK0_REG) * Rank);
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Rank Broadcast
        Offset = DDRDATACH0_CR_RXCONTROL0RANK0_REG;
        Offset += ((DDRDATACH1_CR_RXCONTROL0RANK0_REG - DDRDATACH0_CR_RXCONTROL0RANK0_REG) * Channel) +
          ((DDRDATACH0_CR_RXCONTROL0RANK1_REG - DDRDATACH0_CR_RXCONTROL0RANK0_REG) * Rank);
      } else {
        Offset = DDRDATA0CH0_CR_RXCONTROL0RANK0_REG +
          ((DDRDATA0CH1_CR_RXCONTROL0RANK0_REG - DDRDATA0CH0_CR_RXCONTROL0RANK0_REG) * Channel) +
          ((DDRDATA0CH0_CR_RXCONTROL0RANK1_REG - DDRDATA0CH0_CR_RXCONTROL0RANK0_REG) * Rank) +
          ((DDRDATA1CH0_CR_RXCONTROL0RANK0_REG - DDRDATA0CH0_CR_RXCONTROL0RANK0_REG) * Strobe);
      }
      break;

    case RxDqBitDelay:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        if (Bit <= 3) {
          Offset = DDRDATA_CR_RXCONTROL1RANK0_REG; // Bits 0, 1, 2, 3
        } else if (Bit <= 5) {
          Offset = DDRDATA_CR_RXCONTROL2RANK0_REG; // Bits 4, 5
        } else {
          Offset = DDRDATA_CR_RXCONTROL3RANK0_REG; // Bits 6, 7
        }
        Offset += ((DDRDATA_CR_RXCONTROL1RANK1_REG - DDRDATA_CR_RXCONTROL1RANK0_REG) * Rank);
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Rank Broadcast
        if (Bit <= 3) {
          Offset = DDRDATACH0_CR_RXCONTROL1RANK0_REG; // Bits 0, 1, 2, 3
        } else if (Bit <= 5) {
          Offset = DDRDATACH0_CR_RXCONTROL2RANK0_REG; // Bits 4, 5
        } else {
          Offset = DDRDATACH0_CR_RXCONTROL3RANK0_REG; // Bits 6, 7
        }
        Offset += ((DDRDATACH1_CR_RXCONTROL1RANK0_REG - DDRDATACH0_CR_RXCONTROL1RANK0_REG) * Channel) +
                  ((DDRDATACH0_CR_RXCONTROL1RANK1_REG - DDRDATACH0_CR_RXCONTROL1RANK0_REG) * Rank);
      } else {
        if (Bit <= 3) {
          Offset = DDRDATA0CH0_CR_RXCONTROL1RANK0_REG; // Bits 0, 1, 2, 3
        } else if (Bit <= 5) {
          Offset = DDRDATA0CH0_CR_RXCONTROL2RANK0_REG; // Bits 4, 5
        } else {
          Offset = DDRDATA0CH0_CR_RXCONTROL3RANK0_REG; // Bits 6, 7
        }
        Offset += ((DDRDATA0CH1_CR_RXCONTROL1RANK0_REG - DDRDATA0CH0_CR_RXCONTROL1RANK0_REG) * Channel) +
                  ((DDRDATA0CH0_CR_RXCONTROL1RANK1_REG - DDRDATA0CH0_CR_RXCONTROL1RANK0_REG) * Rank) +
                  ((DDRDATA1CH0_CR_RXCONTROL1RANK0_REG - DDRDATA0CH0_CR_RXCONTROL1RANK0_REG) * Strobe);
      }
      break;

    case RoundTripDelay:
      Offset = CH0_CR_SC_ROUNDTRIP_LATENCY_REG +
        ((CH1_CR_SC_ROUNDTRIP_LATENCY_REG - CH0_CR_SC_ROUNDTRIP_LATENCY_REG) * Channel);
      break;

    case RxFlybyDelay:
      Offset  = MCMISCS_READCFGCHACHB0_REG;
      Offset += (MCMISCS_READCFGCHACHB1_REG - MCMISCS_READCFGCHACHB0_REG) * Channel;
      break;

    case RxFifoRdEnTclDelay:
      Offset  = MCMISCS_READCFGCH0_REG;
      Offset += ((MCMISCS_READCFGCH1_REG - MCMISCS_READCFGCH0_REG) * SubChannel) +
                ((MCMISCS_READCFGCH2_REG - MCMISCS_READCFGCH0_REG) * Channel);
      break;

    case RxFifoRdEnFlybyDelay:
      Offset  = MCMISCS_RXDQFIFORDENCHACHB0_REG;
      Offset += (MCMISCS_RXDQFIFORDENCHACHB1_REG - MCMISCS_RXDQFIFORDENCHACHB0_REG) * Channel;
      break;

    case RxIoTclDelay:
    case RxDqDataValidDclkDelay:
    case RxDqDataValidQclkDelay:
      Offset  = MCMISCS_READCFGCH0_REG;
      Offset += ((MCMISCS_READCFGCH1_REG - MCMISCS_READCFGCH0_REG) * SubChannel) +
                ((MCMISCS_READCFGCH2_REG - MCMISCS_READCFGCH0_REG) * Channel);
      break;

    case SenseAmpDelay:
    case SenseAmpDuration:
    case McOdtDelay:
    case McOdtDuration:
    case RxBiasIComp:
      Offset = DataControl1Offset (Channel, Strobe);
      break;

    case RxCben:
    case RxRankMuxDelay:
      Offset = DataControl2Offset (Channel, Strobe);
      break;

    case RxBiasRCompLsb:
      Offset = DataControl4Offset (Channel, Strobe);
      break;

    case RxDqsAmpOffset:
    case RxBiasRCompMsb:
    case SdllPiCb:
    case D0PiCb:
      Offset = DataControl6Offset (Channel, Strobe);
      break;

    case SdllBwCtrl:
    case D0BwCtrl:
      Offset = DataControl7Offset (Channel, Strobe);
      break;

    case CBEnAmp1:
    case McDqsOdtDelay:
    case McDqsOdtDuration:
      Offset = DataControl3Offset (Channel, Strobe);
      break;

    case RxVoc:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        Offset = DDRDATA_CR_RXCONTROL2RANK0_REG;
        Offset += ((DDRDATA_CR_RXCONTROL2RANK1_REG - DDRDATA_CR_RXCONTROL2RANK0_REG) * Rank) +
                  ((DDRDATA_CR_RXCONTROL3RANK0_REG - DDRDATA_CR_RXCONTROL2RANK0_REG) * (Bit / RX_OFFSET_VDQ));
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Rank Broadcast
        Offset = DDRDATACH0_CR_RXCONTROL2RANK0_REG;
        Offset += ((DDRDATACH1_CR_RXCONTROL2RANK0_REG - DDRDATACH0_CR_RXCONTROL2RANK0_REG) * Channel) +
                  ((DDRDATACH0_CR_RXCONTROL2RANK1_REG - DDRDATACH0_CR_RXCONTROL2RANK0_REG) * Rank) +
                  ((DDRDATACH0_CR_RXCONTROL3RANK0_REG - DDRDATACH0_CR_RXCONTROL2RANK0_REG) * (Bit / RX_OFFSET_VDQ));
      } else {
        Offset = DDRDATA0CH0_CR_RXCONTROL2RANK0_REG +
               ((DDRDATA0CH1_CR_RXCONTROL2RANK0_REG - DDRDATA0CH0_CR_RXCONTROL2RANK0_REG) * Channel) +
               ((DDRDATA0CH0_CR_RXCONTROL2RANK1_REG - DDRDATA0CH0_CR_RXCONTROL2RANK0_REG) * Rank) +
               ((DDRDATA1CH0_CR_RXCONTROL2RANK0_REG - DDRDATA0CH0_CR_RXCONTROL2RANK0_REG) * Strobe) +
               ((DDRDATA0CH0_CR_RXCONTROL3RANK0_REG - DDRDATA0CH0_CR_RXCONTROL2RANK0_REG) * (Bit / RX_OFFSET_VDQ));
      }
      break;


    case DqDfeEnable:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        Offset = DDRDATA_CR_DDRCRDATADFECONTROL0RANK0_REG;
        Offset += ((DDRDATA_CR_DDRCRDATADFECONTROL0RANK1_REG - DDRDATA_CR_DDRCRDATADFECONTROL0RANK0_REG) * Rank);
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Rank Broadcast
        Offset = DDRDATACH0_CR_DDRCRDATADFECONTROL0RANK0_REG;
        Offset += ((DDRDATACH1_CR_DDRCRDATADFECONTROL0RANK0_REG - DDRDATACH0_CR_DDRCRDATADFECONTROL0RANK0_REG) * Channel) +
          ((DDRDATACH0_CR_DDRCRDATADFECONTROL0RANK1_REG - DDRDATACH0_CR_DDRCRDATADFECONTROL0RANK0_REG) * Rank);
      } else {
        Offset = DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_REG +
          ((DDRDATA0CH1_CR_DDRCRDATADFECONTROL0RANK0_REG - DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_REG) * Channel) +
          ((DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK1_REG - DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_REG) * Rank) +
          ((DDRDATA1CH0_CR_DDRCRDATADFECONTROL0RANK0_REG - DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_REG) * Strobe);
      }
      break;

    case DqDfeDelayMode:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        Offset = DDRDATA_CR_DDRCRDATADFECONTROL1RANK01_REG;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Rank Broadcast
        Offset = DDRDATACH0_CR_DDRCRDATADFECONTROL1RANK01_REG +
               ((DDRDATACH1_CR_DDRCRDATADFECONTROL1RANK01_REG - DDRDATACH0_CR_DDRCRDATADFECONTROL1RANK01_REG) * Channel);
      } else {
        Offset = DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_REG +
               ((DDRDATA0CH1_CR_DDRCRDATADFECONTROL1RANK01_REG - DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_REG) * Channel) +
               ((DDRDATA1CH0_CR_DDRCRDATADFECONTROL1RANK01_REG - DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_REG) * Strobe);
      }
      break;

    case DqDfeCoeff:
      Offset = DataControl8Offset (Channel, Strobe);
      break;

    case DqDfeDelay:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        if (Bit == 0) {
          Offset = DDRDATA_CR_RXCONTROL1RANK0_REG; // Bits 0
          Offset += ((DDRDATA_CR_RXCONTROL1RANK1_REG - DDRDATA_CR_RXCONTROL1RANK0_REG) * Rank);
        } else if (Bit <= 5) {
          Offset = DDRDATA_CR_DDRCRDATADFECONTROL0RANK0_REG; // Bits 1, 2, 3, 4, 5
          Offset += ((DDRDATA_CR_DDRCRDATADFECONTROL0RANK1_REG - DDRDATA_CR_DDRCRDATADFECONTROL0RANK0_REG) * Rank);
        } else {
          if (Rank < 2) {                           //Rank 0 and 1
            Offset = DDRDATA_CR_DDRCRDATADFECONTROL1RANK01_REG; // Bits 6, 7
          } else if (Rank < MAX_RANK_IN_CHANNEL) {  //Rank 2 and 3
            Offset = DDRDATA_CR_DDRCRDATADFECONTROL1RANK23_REG; // Bits 6, 7
          }
        }
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Rank Broadcast
        if (Bit == 0) {
          Offset = DDRDATACH0_CR_RXCONTROL1RANK0_REG; // Bits 0
          Offset += ((DDRDATACH1_CR_RXCONTROL1RANK0_REG - DDRDATACH0_CR_RXCONTROL1RANK0_REG) * Channel) +
                    ((DDRDATACH0_CR_RXCONTROL1RANK1_REG - DDRDATACH0_CR_RXCONTROL1RANK0_REG) * Rank);
        } else if (Bit <= 5) {
          Offset = DDRDATACH0_CR_DDRCRDATADFECONTROL0RANK0_REG; // Bits 1, 2, 3, 4, 5
          Offset += ((DDRDATACH1_CR_DDRCRDATADFECONTROL0RANK0_REG - DDRDATACH0_CR_DDRCRDATADFECONTROL0RANK0_REG) * Channel) +
                    ((DDRDATACH0_CR_DDRCRDATADFECONTROL0RANK1_REG - DDRDATACH0_CR_DDRCRDATADFECONTROL0RANK0_REG) * Rank);
        } else {
          if (Rank < 2) {                           //Rank 0 and 1
            Offset = DDRDATACH0_CR_DDRCRDATADFECONTROL1RANK01_REG; // Bits 6, 7
          } else if (Rank < MAX_RANK_IN_CHANNEL) {  //Rank 2 and 3
            Offset = DDRDATACH0_CR_DDRCRDATADFECONTROL1RANK23_REG; // Bits 6, 7
          }
          Offset += ((DDRDATACH1_CR_DDRCRDATADFECONTROL1RANK01_REG - DDRDATACH0_CR_DDRCRDATADFECONTROL1RANK01_REG) * Channel);
        }
      } else {
        // Unicast
        if (Bit == 0) {
          Offset = DDRDATA0CH0_CR_RXCONTROL1RANK0_REG; // Bits 0
          Offset += ((DDRDATA0CH1_CR_RXCONTROL1RANK0_REG - DDRDATA0CH0_CR_RXCONTROL1RANK0_REG) * Channel) +
                    ((DDRDATA0CH0_CR_RXCONTROL1RANK1_REG - DDRDATA0CH0_CR_RXCONTROL1RANK0_REG) * Rank) +
                    ((DDRDATA1CH0_CR_RXCONTROL1RANK0_REG - DDRDATA0CH0_CR_RXCONTROL1RANK0_REG) * Strobe);
        } else if (Bit <= 5) {
          Offset = DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_REG; // Bits 1, 2, 3, 4, 5
          Offset += ((DDRDATA0CH1_CR_DDRCRDATADFECONTROL0RANK0_REG - DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_REG) * Channel) +
                    ((DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK1_REG - DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_REG) * Rank) +
                    ((DDRDATA1CH0_CR_DDRCRDATADFECONTROL0RANK0_REG - DDRDATA0CH0_CR_DDRCRDATADFECONTROL0RANK0_REG) * Strobe);
        } else {
          if (Rank < 2) {                           //Rank 0 and 1
            Offset = DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_REG; // Bits 6, 7
          } else if (Rank < MAX_RANK_IN_CHANNEL) {  //Rank 2 and 3
            Offset = DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK23_REG; // Bits 6, 7
          }
          Offset += ((DDRDATA0CH1_CR_DDRCRDATADFECONTROL1RANK01_REG - DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_REG) * Channel) +
                    ((DDRDATA1CH0_CR_DDRCRDATADFECONTROL1RANK01_REG - DDRDATA0CH0_CR_DDRCRDATADFECONTROL1RANK01_REG) * Strobe);
        }
      }
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
  @param[in]  SubChannel  - DDR SubChannel Number in the channel(0-based).
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
  IN  UINT32          SubChannel,
  IN  UINT32          Rank,
  IN  UINT32          Strobe,
  IN  UINT32          Bit,
  IN  UINT32          FreqIndex
  )
{
  UINT32 Offset;

  Offset = MRC_UINT32_MAX;

  switch (Group) {
    case TxDqsDelay:
    case TxDqDelay:
    case TxEq:
    case TxRankMuxDelay:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        Offset = DDRDATA_CR_TXTRAINRANK0_REG;
        Offset += ((DDRDATA_CR_TXTRAINRANK1_REG - DDRDATA_CR_TXTRAINRANK0_REG) * Rank);
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Rank Broadcast
        Offset = DDRDATACH0_CR_TXTRAINRANK0_REG;
        Offset += ((DDRDATACH1_CR_TXTRAINRANK0_REG - DDRDATACH0_CR_TXTRAINRANK0_REG) * Channel) +
          ((DDRDATACH0_CR_TXTRAINRANK1_REG - DDRDATACH0_CR_TXTRAINRANK0_REG) * Rank);
      } else {
        Offset = DDRDATA0CH0_CR_TXTRAINRANK0_REG +
          ((DDRDATA0CH1_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Channel) +
          ((DDRDATA0CH0_CR_TXTRAINRANK1_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Rank) +
          ((DDRDATA1CH0_CR_TXTRAINRANK0_REG - DDRDATA0CH0_CR_TXTRAINRANK0_REG) * Strobe);
      }
      break;

    case TxDqBitDelay:
      if (Channel >= MAX_CHANNEL) {
        // Channel/Strobe Broadcast
        Offset = DDRDATA_CR_TXPERBITLOWRANK0_REG;
        Offset += ((DDRDATA_CR_TXPERBITLOWRANK1_REG - DDRDATA_CR_TXPERBITLOWRANK0_REG) * Rank) +
          ((DDRDATA_CR_TXPERBITHIRANK0_REG - DDRDATA_CR_TXPERBITLOWRANK0_REG) * (Bit / TX_PER_BIT_DESKEW));
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Rank Broadcast
        Offset = DDRDATACH0_CR_TXPERBITLOWRANK0_REG;
        Offset += ((DDRDATACH1_CR_TXPERBITLOWRANK0_REG - DDRDATACH0_CR_TXPERBITLOWRANK0_REG) * Channel) +
          ((DDRDATACH0_CR_TXPERBITLOWRANK1_REG - DDRDATACH0_CR_TXPERBITLOWRANK0_REG) * Rank) +
          ((DDRDATACH0_CR_TXPERBITHIRANK0_REG - DDRDATACH0_CR_TXPERBITLOWRANK0_REG) * (Bit / TX_PER_BIT_DESKEW));
      } else {
        Offset = DDRDATA0CH0_CR_TXPERBITLOWRANK0_REG +
          ((DDRDATA0CH1_CR_TXPERBITLOWRANK0_REG - DDRDATA0CH0_CR_TXPERBITLOWRANK0_REG) * Channel) +
          ((DDRDATA0CH0_CR_TXPERBITLOWRANK1_REG - DDRDATA0CH0_CR_TXPERBITLOWRANK0_REG) * Rank) +
          ((DDRDATA1CH0_CR_TXPERBITLOWRANK0_REG - DDRDATA0CH0_CR_TXPERBITLOWRANK0_REG) * Strobe) +
          ((DDRDATA0CH0_CR_TXPERBITHIRANK0_REG - DDRDATA0CH0_CR_TXPERBITLOWRANK0_REG) * (Bit / TX_PER_BIT_DESKEW));
      }
      break;

    case TxVref:
      // @todo Can remove when ICL A0 support is dropped
      Offset = DDRVREF_CR_DDRCRVREFADJUST1_REG;
      break;
    case TxTco:
      if (Channel >= MAX_CHANNEL) {
        // Channel Broadcast
        Offset = DDRDATA_CR_DDRCRDATATCOCONTROL0_REG;
        Offset += ((DDRDATA0CH0_CR_DDRCRDATATCOCONTROL1_REG - DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_REG) * (Bit / TX_PER_BIT_DESKEW));
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Byte Broadcast
        Offset = DDRDATACH0_CR_DDRCRDATATCOCONTROL0_REG;
        Offset += ((DDRDATACH1_CR_DDRCRDATATCOCONTROL0_REG - DDRDATACH0_CR_DDRCRDATATCOCONTROL0_REG) * Channel) +
          ((DDRDATACH0_CR_DDRCRDATATCOCONTROL1_REG - DDRDATACH0_CR_DDRCRDATATCOCONTROL0_REG) * (Bit / TX_PER_BIT_DESKEW));
      } else {
        Offset = DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_REG +
          ((DDRDATA0CH1_CR_DDRCRDATATCOCONTROL0_REG - DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_REG) * Channel) +
          ((DDRDATA1CH0_CR_DDRCRDATATCOCONTROL0_REG - DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_REG) * Strobe) +
          ((DDRDATA0CH0_CR_DDRCRDATATCOCONTROL1_REG - DDRDATA0CH0_CR_DDRCRDATATCOCONTROL0_REG) * (Bit / TX_PER_BIT_DESKEW));
      }
      break;

    case TxTcoDqsN:
    case TxTcoByPass:
      Offset = DataControl0Offset(Channel, Strobe);
      break;

    case TxTcoDqsP:
      Offset = DataControl1Offset(Channel, Strobe);
      break;

    case TxDqFifoRdEnFlybyDelay:
      Offset  = MCMISCS_WRITECFGCHACHB0_REG;
      Offset += (MCMISCS_WRITECFGCHACHB1_REG - MCMISCS_WRITECFGCHACHB0_REG) * Channel;
      break;

    case TxDqsRankMuxDelay:
      Offset = DataControl3Offset (Channel, Strobe);
      break;

    case TxDqFifoWrEnTcwlDelay:
    case TxDqFifoRdEnTcwlDelay:
      Offset = WriteConfigOffset (Channel, SubChannel);
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
      if (Channel >= MAX_CHANNEL) {
        // Overall Broadcast
        Offset = DDRDATA_CR_DDRCRDATAOFFSETTRAIN_REG;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Rank Broadcast
        Offset = DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_REG;
        Offset += ((DDRDATACH1_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATACH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Channel);
      } else {
        // Specific Channel and Strobe
        Offset = DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG +
          ((DDRDATA0CH1_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Channel) +
          ((DDRDATA1CH0_CR_DDRCRDATAOFFSETTRAIN_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETTRAIN_REG) * Strobe);
      }
      break;

    case CompOffsetAll:
      if (Channel >= MAX_CHANNEL) {
        // Controller Broadcast
        Offset = DDRDATA_CR_DDRCRDATAOFFSETCOMP_REG;
      } else if (Strobe >= MAX_SDRAM_IN_DIMM) {
        // Rank Broadcast
        Offset  = DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_REG;
        Offset += ((DDRDATACH1_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATACH0_CR_DDRCRDATAOFFSETCOMP_REG) * Channel);
      } else {
        // Specific Channel and Strobe
        Offset = DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG +
          ((DDRDATA0CH1_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG) * Channel) +
          ((DDRDATA1CH0_CR_DDRCRDATAOFFSETCOMP_REG - DDRDATA0CH0_CR_DDRCRDATAOFFSETCOMP_REG) * Strobe);
      }
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
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  SubChannel  - DDR SubChannel within the channel Number(0-based).
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
  IN  UINT32          SubChannel,
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
    case GsmIocWlSleepCyc:
    case GsmIocWlLatency:
    case GsmIocLpRcvenCtrl:
    case GsmIocNoDqInterleave:
    case GsmIocScramLpMode:
    case GsmIocScramDdr4Mode:
    case GsmIocDdrCentric:
    case GsmIocScramGear1:
    case GsmIocDisClkGate:
    case GsmIocDllWlEn:
    case GsmIocDisDataIdlClkGate:
    case GsmIoc4ChMode:
    case GsmIocScramLp4Mode:
    case GsmIocChNotPop:
    case GsmIocDisIosfSbClkGate:
    case GsmIocEccEn:
      Offset = DDRSCRAM_CR_DDRMISCCONTROL0_REG;
      break;

    case GsmIocIoReset:
    case GsmIocForceCmpUpdt:
      Offset = DDRSCRAM_CR_DDRMISCCONTROL1_REG;
      break;

    case GsmIocLpEarlyRLeak:
    case GsmIocOdtSampExtEn:
    case GsmIocForceOdtOn:
    case GsmIocDataOdtStaticDis:
    case GsmIocReadDqDqsMode:
    case GsmIocRxPiPwrDnDis:
    case GsmIocTxPiPwrDnDis:
    case GsmIocTxDisable:
    case GsmIocInternalClocksOn:
    case GsmIocLowSupEnDqDqs:
    case GsmIocDataCtlLpMode:
    case GsmIocTxOn:
    case GsmIocSenseAmpMode:
    case GsmIocWriteLevelMode:
    case GsmIocReadLevelMode:
    case GsmIocXoverMinDelayCtl:
      Offset = DataControl0Offset (Channel, Strobe);
      break;

    case GsmIocDllMask:
    case GsmIocSdllSegmentDisable:
    case GsmIocDllWeakLock:
      Offset = DataControl1Offset (Channel, Strobe);
      break;

    case GsmIocDqsOdtSampExtEn:
    case GsmIocStrongWeakLeaker:
    case GsmIocLeakerComp:
    case GsmIocStrong2WeakOnDqsOdt:
    case GsmIocForceDqsOnQuickOdtOff:
    case GsmIocRcvenFourCycleFill:
    case GsmIocRxClkStgNumMsb:
      Offset = DataControl3Offset (Channel, Strobe);
      break;

    case GsmIocLongWrPreambleLp4:
    case GsmIocDataCtlLp4Mode:
    case GsmIocVssOdtEn:
    case GsmIocRxTypeSelect:
    case GsmIocRxBiasSel:
    case GsmIocRxDeskewCal:
    case GsmIocTxDeskewCal:
    case GsmIocLeakerWithTxAnalogEn:
    case GsmIocGlobalClkEn:
      Offset = DataControl4Offset (Channel, Strobe);
      break;

    case GsmIocDqSlewDlyByPass:
    case GsmIocRxDeskewDis:
    case GsmIocTxDeskewDis:
    case GsmIocRxVrefMFC:
    case GsmIocTxEqDis:
    case GsmIocConstZTxEqEn:
    case GsmIocDataVttOdtEn:
    case GsmIocDataVddqOdtEn:
    case GsmIocDataCtlDdr4Mode:
    case GsmIocVrefPwrDnEn:
    case GsmIocWlLongDelEn:
    case GsmIocRxClkStg:
    case GsmIocLpLongOdtEn:
    case GsmIocForceRxAmpOn:
    case GsmIocForceBiasOn:
    case GsmIocRxStaggerCtl:
      Offset = DataControl2Offset (Channel, Strobe);
      break;

    case GsmIocLp4DqsMaskPulseCnt:
    case GsmIocLp4DqsPulseCnt:
    case GsmIocLp4DqsPulseEn:
    case GsmIocLp4DqOverrideData:
    case GsmIocLp4DqOverrideEn:
      Offset = DataControl5Offset (Channel, Strobe);
      break;

    case GsmIocEnRcvenPreZeroFill:
      Offset = DataControl8Offset (Channel, Strobe);
      break;

    case GsmIocRankOverrideEn:
    case GsmIocRankOverrideVal:
    case GsmIocDataCtlGear1:
    case GsmIocLp4ForceDqsPOn:
    case GsmIocLp4ForceDqsNOn:
    case GsmIocLp4ForceDqsPOnWithLeaker:
    case GsmIocLp4ForceDqsNOnWithLeaker:
    case GsmIocStrongWeakLeakerMsb:
      Offset = DataControl6Offset (Channel, Strobe);
      break;

    case GsmIocTxVrefConverge:  // @todo Can remove when ICL A0 support is dropped
    case GsmIocCmdVrefConverge:
      Offset = DDRVREF_CR_DDRCRVREFADJUST2_REG;
      break;

    case GsmIocCompOdtStaticDis:
    case GsmIocDqOdtUpDnOff:
    case GsmIocFixOdtD:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL0_REG;
      break;

    case GsmIocCompClkOn:
    case GsmIocCompVccddqLo:
    case GsmIocDisableQuickComp:
    case GsmIocSinStep:
    case GsmIocSinStepAdv:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL1_REG;
      break;

    case GsmIocCompVddqOdtEn:
    case GsmIocCompVttOdtEn:
    case GsmIocVttPanicCompUpMult:
    case GsmIocVttPanicCompDnMult:
    case GsmIocPanicDrvUpVref:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL2_REG;
      break;

    case GsmIocCmdDrvVref200ohm:
      Offset = DDRPHY_COMP_CR_DDRCRDATACOMP2_REG;
      break;

    case GsmIocOdtOverride:
    case GsmIocOdtOn:
    case GsmIocMprTrainDdrOn:
      if (Channel >= MAX_CHANNEL) {
        // Overall Broadcast
        Offset = BC_CR_REUT_CH_MISC_ODT_CTRL_REG;
      } else {
        // Channel
        Offset = (Channel) ? CH1_CR_REUT_CH_MISC_ODT_CTRL_REG : CH0_CR_REUT_CH_MISC_ODT_CTRL_REG;
      }
      break;

    case GsmIocCkeOverride:
    case GsmIocCkeOn:
      if (Channel >= MAX_CHANNEL) {
        // Overall Broadcast
        Offset = BC_CR_REUT_CH_MISC_CKE_CTRL_REG;
      } else {
        // Channel
        Offset = (Channel) ? CH1_CR_REUT_CH_MISC_CKE_CTRL_REG : CH0_CR_REUT_CH_MISC_CKE_CTRL_REG;
      }
      break;

    case GsmIocRptChRepClkOn:
    case GsmIocCmdAnlgEnGraceCnt:
    case GsmIocTxAnlgEnGraceCnt:
    case GsmIocTxDqFifoRdEnPerRankDelDis:
      Offset = WriteConfigOffset (Channel, SubChannel);
      break;

    case GsmIocDccTrainingMode:
    case GsmIocDccTrainingDone:
    case GsmIocDccDrain:
    case GsmIocDccDcoLfsrDis:
      Offset = MCMISCS_DCCCONTROL0_REG;
      break;

    case GsmIocDccActiveClks:
    case GsmIocDccActiveBytes:
    case GsmIocDccDcoCompEn:
    case GsmIocDccPeriodicDis:
      Offset = MCMISCS_DCCMAINFSMCONTROL0_REG;
      break;

    case GsmIocDccClkTrainVal:
      Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKTRAINVAL0_REG, DDRCLKCH1_CR_DCCCLKTRAINVAL0_REG, Channel);
      break;

    case GsmIocDccDataTrainDqsVal:
    case GsmIocDccDqsReplica:
    case GsmIocDccAipCbDqs:
      Offset = DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_REG +
              (DDRDATA0CH1_CR_DCCDATATRAINVAL1RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_REG) * Channel +
              (DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK1_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_REG) * Rank +
              (DDRDATA1CH0_CR_DCCDATATRAINVAL1RANK0_REG - DDRDATA0CH0_CR_DCCDATATRAINVAL1RANK0_REG) * Strobe;
      break;

    case GsmIocDccAipCb:
      if (Strobe == 0) {
        Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKCONTROL1_REG, DDRCLKCH1_CR_DCCCLKCONTROL1_REG, Channel);
      } else if (Strobe == 1) {
        Offset = OFFSET_CALC_CH (DDRCLKCH0_CR_DCCCLKTRAINVAL0_REG, DDRCLKCH1_CR_DCCCLKTRAINVAL0_REG, Channel);
      } else if (Strobe == 2) {
        Offset = OFFSET_CALC_CH (DDRCTLCLKCKE0_CR_DCCCLKCONTROL1_REG, DDRCTLCLKCKE1_CR_DCCCLKCONTROL1_REG, Channel);
      } else if (Strobe == 3) {
        Offset = OFFSET_CALC_CH (DDRCTLCLKCKE0_CR_DCCCLKTRAINVAL0_REG, DDRCTLCLKCKE1_CR_DCCCLKTRAINVAL0_REG, Channel);
      }
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
  @param[in]  Rank        - Rank index in the channel. (0-based).
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
  IN  UINT32          Rank,
  IN  UINT32          GroupIndex,
  IN  UINT32          FreqIndex
  )
{
  UINT32 Offset;

  static const UINT32 CtlGrpBase[MRC_CTL_GRP_MAX] = {
    DDRCTLCH0_CR_DDRCRCTLPICODING_REG, DDRCTLCH0_CR_DDRCRCTLPICODING_REG,
    DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_REG, DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_REG};
  static const UINT32 CkeGrpBase[MRC_CTL_GRP_MAX] = {
    DDRCKECH0_CR_DDRCRCTLPICODING_REG, DDRCKECH0_CR_DDRCRCTLPICODING_REG,
    DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_REG, DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_REG};
  static const UINT32 CmdGrpBase[MRC_CMD_GRP_MAX] = {
    DDRCMDACH0_CR_DDRCRCMDPICODING_REG, DDRCMDACH0_CR_DDRCRCMDPICODING_REG,
    DDRCMDBCH0_CR_DDRCRCMDPICODING_REG, DDRCMDBCH0_CR_DDRCRCMDPICODING_REG,
    DDRCKECH0_CR_DDRCRCTLPICODING_REG};
  static const UINT32 CmdGrpControlBase[MRC_CMD_GRP_MAX] = {
    DDRCMDACH0_CR_DDRCRCMDTCOCONTROL0_REG, DDRCMDACH0_CR_DDRCRCMDTCOCONTROL0_REG,
    DDRCMDBCH0_CR_DDRCRCMDTCOCONTROL0_REG, DDRCMDBCH0_CR_DDRCRCMDTCOCONTROL0_REG,
    DDRCKECH0_CR_DDRCRCMDTCOCONTROL0_REG};
  static const UINT32 ClkGrpBase[MRC_CLK_GRP_MAX] = {
    DDRCTLCH0_CR_DDRCRCTLPICODING_REG, DDRCTLCH0_CR_DDRCRCTLPICODING_REG,
    DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_REG, DDRCTLCLKCKE0_CR_DDRCRCTLPICODING_REG};
  static const UINT32 CmdCompOffset[MAX_SUB_CHANNEL] = {
    DDRCMDACH0_CR_DDRCRCMDCOMPOFFSET_REG, DDRCMDBCH0_CR_DDRCRCMDCOMPOFFSET_REG};
  static const UINT32 CmdTxEqGrpBase[MRC_CMDTXEQ_GRP_MAX] = {
    DDRCMDACH0_CR_DDRCRCMDCONTROLS_REG, DDRCMDBCH0_CR_DDRCRCMDCONTROLS_REG,
    DDRCKECH0_CR_DDRCRCTLCONTROLS_REG};

  static const UINT32 CtlCkeInc  = DDRCTLCH1_CR_DDRCRCTLPICODING_REG - DDRCTLCH0_CR_DDRCRCTLPICODING_REG;
  static const UINT32 CmdInc     = DDRCMDACH1_CR_DDRCRCMDPICODING_REG - DDRCMDACH0_CR_DDRCRCMDPICODING_REG;
  static const UINT32 CmdCompInc = DDRCMDACH1_CR_DDRCRCMDCOMPOFFSET_REG - DDRCMDACH0_CR_DDRCRCMDCOMPOFFSET_REG;
  static const UINT32 CmdTxEqInc  = DDRCMDACH1_CR_DDRCRCMDCONTROLS_REG - DDRCMDACH0_CR_DDRCRCMDCONTROLS_REG;


  Offset = MRC_UINT32_MAX;

  switch (Group) {
    case CtlGrpPi:
      if (GroupIndex < MRC_CTL_GRP_MAX) {
        Offset = CtlGrpBase[GroupIndex] + (CtlCkeInc * Channel);
      }
      break;

    case CkeGrpPi:
      if (GroupIndex < MRC_CKE_GRP_MAX) {
        Offset = CkeGrpBase[GroupIndex] + (CtlCkeInc * Channel);
      }
      break;

    case CmdGrpPi:
      if (GroupIndex < MRC_CMD_GRP_MAX) {
        Offset = CmdGrpBase[GroupIndex];
        if (Offset == DDRCKECH0_CR_DDRCRCTLPICODING_REG) {
          Offset += (CtlCkeInc * Channel);
        } else {
          Offset += (CmdInc * Channel);
        }
      }
      break;

    case ClkGrpPi:
      if (GroupIndex < MRC_CLK_GRP_MAX) {
        Offset  = ClkGrpBase[GroupIndex];
        Offset += (CtlCkeInc * Channel);
      }
      break;

    case CmdVref:
      if (MrcData->Inputs.IclA0) {
        Offset = DDRVREF_CR_DDRCRVREFADJUST1_REG;
      } else {
        // Ch1 Dimm1 is in VrefAdjust3, the rest are in VrefAdjust1
        Offset = ((Channel == 1) && (Rank >= 2)) ? DDRVREF_CR_DDRCRVREFADJUST3_REG : DDRVREF_CR_DDRCRVREFADJUST1_REG;
      }
      break;

    case CmdRCompDrvDownOffset:
    case CmdRCompDrvUpOffset:
    case CmdSCompOffset:
      // Cmd Comp Offset to a specific Channel and Sub-Channel
      if (GroupIndex < MAX_SUB_CHANNEL) {
        Offset = CmdCompOffset[GroupIndex];
        Offset += (CmdCompInc * Channel);
      }
      break;

    case CtlRCompDrvDownOffset:
    case CtlRCompDrvUpOffset:
    case CtlSCompOffset:
      // Ctl Comp Offset to a specific Channel
      Offset = DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_REG +
        ((DDRCTLCH1_CR_DDRCRCTLCOMPOFFSET_REG - DDRCTLCH0_CR_DDRCRCTLCOMPOFFSET_REG) * Channel);
      break;

    case CkeRCompDrvDownOffset:
    case CkeRCompDrvUpOffset:
    case CkeSCompOffset:
      // Cke Comp Offset to a specific Channel
      Offset = DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_REG +
        ((DDRCKECH1_CR_DDRCRCTLCOMPOFFSET_REG - DDRCKECH0_CR_DDRCRCTLCOMPOFFSET_REG) * Channel);
      break;

    case ClkRCompDrvDownOffset:
    case ClkRCompDrvUpOffset:
    case ClkSCompOffset:
    case ClkCompOnTheFlyUpdtEn:
      // Clk Comp Offset Specific Channel
      Offset = DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_REG +
        ((DDRCLKCH1_CR_DDRCRCLKCOMPOFFSET_REG - DDRCLKCH0_CR_DDRCRCLKCOMPOFFSET_REG) * Channel);
      break;

    case TcoCompCodeClk:
      if (Channel >= MAX_CHANNEL) {
        // Channel Broadcast
        Offset = DDRCLKCH0CH1_CR_DDRCRCLKTCOCONTROL0_REG;
      } else {
        Offset = DDRCLKCH0_CR_DDRCRCLKTCOCONTROL0_REG;
        Offset += ((DDRCLKCH1_CR_DDRCRCLKTCOCONTROL0_REG - DDRCLKCH0_CR_DDRCRCLKTCOCONTROL0_REG) * Channel);
      }
      break;

    case TcoCompCodeCtl:
      Offset = DDRCTLCH0_CR_DDRCRCTLTCOCONTROL0_REG;
      Offset += ((DDRCTLCH1_CR_DDRCRCTLTCOCONTROL0_REG - DDRCTLCH0_CR_DDRCRCTLTCOCONTROL0_REG) * Channel);
      break;

    case TcoCompCodeCmd:
      if (Channel >= MAX_CHANNEL) {
        // Channel Broadcast
        Offset = DDRCMD_CR_DDRCRCMDTCOCONTROL0_REG;
      } else if(GroupIndex > MRC_CMD_GRP_MAX){
        // Group Broadcast
        Offset = DDRCMDCH0_CR_DDRCRCMDTCOCONTROL0_REG;
        Offset += ((DDRCMDCH1_CR_DDRCRCMDTCOCONTROL0_REG - DDRCMDCH0_CR_DDRCRCMDTCOCONTROL0_REG) * Channel);
      } else if (GroupIndex < MRC_CMD_GRP_MAX) {
        Offset = CmdGrpControlBase[GroupIndex];
        Offset += CmdInc * Channel;
      }
      break;

    case CmdTxEq:
      if (GroupIndex < MRC_CMDTXEQ_GRP_MAX){
        Offset = CmdTxEqGrpBase[GroupIndex] + (CmdTxEqInc * Channel);
      }
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
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  SubChannel  - DDR SubChannel Number(0-based).
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
  IN  UINT32  const         Channel,
  IN  UINT32  const         SubChannel,
  IN  UINT32  const         Rank,
  IN  UINT32  const         Strobe,
  IN  UINT32  const         Bit,
  IN  UINT32  const         FreqIndex
  )
{
  UINT32          Offset = MRC_UINT32_MAX;

  switch (Group) {
    case RecEnDelay:
    case RxDqsPDelay:
    case RxDqsNDelay:
    case RxVref:
    case RxEq:
    case RxDqBitDelay:
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
    case McDqsOdtDelay:
    case McDqsOdtDuration:
    case RxBiasIComp:
    case RxBiasRCompMsb:
    case RxBiasRCompLsb:
    case RxDqsAmpOffset:
    case SdllPiCb:
    case D0PiCb:
    case SdllBwCtrl:
    case D0BwCtrl:
    case RxCben:
    case RxVoc:
    case CBEnAmp1:
    case RxRankMuxDelay:
    case DqDfeEnable:
    case DqDfeDelayMode:
    case DqDfeCoeff:
    case DqDfeDelay:
      Offset = GetDdrIoDataReadOffsets (MrcData, Group, Socket, Channel, SubChannel, Rank, Strobe, Bit, FreqIndex);
      break;

    case TxDqsDelay:
    case TxDqDelay:
    case TxEq:
    case TxRankMuxDelay:
    case TxDqsRankMuxDelay:
    case TxDqBitDelay:
    case TxVref:                // @todo Can remove when ICL A0 support is dropped
    case TxDqFifoWrEnTcwlDelay:
    case TxDqFifoRdEnTcwlDelay:
    case TxDqFifoRdEnFlybyDelay:
    case TxTco:
    case TxTcoDqsN:
    case TxTcoDqsP:
    case TxTcoByPass:
      Offset = GetDdrIoDataWriteOffsets (MrcData, Group, Socket, Channel, SubChannel, Rank, Strobe, Bit, FreqIndex);
      break;

    case RecEnOffset:
    case RxDqsOffset:
    case RxVrefOffset:
    case TxDqsOffset:
    case TxDqOffset:
      Offset = GetDdrIoDataTrainOffsets (MrcData, Group, Socket, Channel, Rank, Strobe, Bit, FreqIndex);
      break;

    case CtlGrpPi:
    case CkeGrpPi:
    case CmdGrpPi:
    case ClkGrpPi:
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
    case ClkCompOnTheFlyUpdtEn:
    case CkeRCompDrvDownOffset:
    case CkeRCompDrvUpOffset:
    case CkeSCompOffset:
    case CmdTxEq:
    case TcoCompCodeCmd:
    case TcoCompCodeCtl:
    case TcoCompCodeClk:
      Offset = GetDdrIoCommandOffsets (MrcData, Group, Socket, Channel, Rank, Strobe, FreqIndex);
      break;

    case TxSlewRate:
    case DqScompPC:
    case CmdSlewRate:
    case CmdScompPC:
    case CtlSlewRate:
    case CtlScompPC:
    case ClkSlewRate:
    case ClkScompPC:
    case DqRcompStatLegs:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL1_REG;
      break;

    case TxRonUp:
    case TxRonDn:
    case SCompCodeDq:
      Offset = DDRPHY_COMP_CR_DDRCRDATACOMP0_REG;
      break;

    case WrDSCodeUpCmd:
    case WrDSCodeDnCmd:
    case SCompCodeCmd:
      Offset = DDRPHY_COMP_CR_DDRCRCMDCOMP_REG;
      break;

    case WrDSCodeUpCtl:
    case WrDSCodeDnCtl:
    case SCompCodeCtl:
      Offset = DDRPHY_COMP_CR_DDRCRCTLCOMP_REG;
      break;

    case WrDSCodeUpClk:
    case WrDSCodeDnClk:
    case SCompCodeClk:
      Offset = DDRPHY_COMP_CR_DDRCRCLKCOMP_REG;
      break;

    case DqDrvVref:
    case DqOdtVref:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL0_REG;
      break;

    case CmdDrvVref:
    case CtlDrvVref:
    case ClkDrvVref:
      Offset = DDRPHY_COMP_CR_DDRCRCOMPCTL3_REG;
      break;

    case CompRcompOdtUp:
    case CompRcompOdtDn:
      Offset = DDRPHY_COMP_CR_DDRCRDATACOMP1_REG;
      break;

    default:
      break;
  }

  return Offset;
}

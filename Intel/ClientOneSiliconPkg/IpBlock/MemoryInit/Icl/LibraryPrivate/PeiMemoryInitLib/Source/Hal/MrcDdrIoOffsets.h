/** @file
  This file contains functions to get DDR IO Data Offsets
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

#ifndef _MRC_DDR_IO_OFFSETS_H_
#define _MRC_DDR_IO_OFFSETS_H_
#include "MrcInterface.h"
#include "MrcRegisterCache.h"
#include "MrcDdrIoDefines.h"

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
  );

/**
  Function used to get the CR Offset for Write Data Groups.

  @param[in]  MrcData     - Global MRC data structure.
  @param[in]  Group       - DDRIO group being accessed.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  SubChannel  - DDR SubChannel Number in the channel(0-based).
  @param[in]  Rank        - Rank index in the channel. (0-based).
  @param[in]  Strobe      - Dqs data group within the rank (0-based).
  @param[in]  Bit         - Bit index within the data group (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)

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
  );

/**
  Function used to get the CR Offset for training offset Groups.

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
  );

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
  IN MrcParameters *MrcData,
  IN  GSM_GT  Group,
  IN  UINT32  Socket,
  IN  UINT32  Channel,
  IN  UINT32  SubChannel,
  IN  UINT32  Rank,
  IN  UINT32  Strobe,
  IN  UINT32  Bit,
  IN  UINT32  FreqIndex
  );

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
  );

#endif // _MRC_DDR_IO_OFFSETS_H_


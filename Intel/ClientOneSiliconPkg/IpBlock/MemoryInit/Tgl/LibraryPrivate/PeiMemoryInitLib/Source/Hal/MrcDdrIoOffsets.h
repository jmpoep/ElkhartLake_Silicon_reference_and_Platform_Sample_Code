/** @file
  This file contains functions to get DDR IO Data Offsets
  used memory training.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2013 - 2018 Intel Corporation.

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

typedef enum { //0: Off, 1: DDR4/LP4 WL, 2: DDR5 WL, 3: LP5 WL
  MrcWriteLevelOff,
  MrcWriteLevelDdr4Lpddr4,
  MrcWriteLevelDdr5,
  MrcWriteLevelLpddr5,
  MrcWriteLevelMax   ///< This must be the last entry in the enum.
} MrcWriteLevelingTrainMode;

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
  );

/**
  Function used to get the CR Offset for Write Data Groups.

  @param[in]  MrcData     - Global MRC data structure.
  @param[in]  Group       - DDRIO group being accessed.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel    - DDR Channel Number within the memory controller (0-based).
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
  @param[in]  Channel     - DDR Channel Number within the memory controller (0-based).
  @param[in]  Rank        - Rank index in the channel. (0-based).
  @param[in]  Strobe      - Dqs data group within the rank (0-based).
  @param[in]  Bit         - Bit index within the data group (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval CR Offset.
**/
UINT32
MrcGetDdrIoConfigOffsets (
  IN MrcParameters *MrcData,
  IN  GSM_GT       Group,
  IN  UINT32       Socket,
  IN  UINT32       Channel,
  IN  UINT32       Rank,
  IN  UINT32       Strobe,
  IN  UINT32       Bit,
  IN  UINT32       FreqIndex
  );

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
  );

// These functions are called in DdrioInit()
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
);

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
);

/**
  This function returns the offset to access specific Channel/Strobe of DataControl2.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
**/
UINT32
DataControl2Offset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
);

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
);

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
);

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
);

/**
  This function returns the offset to access specific Channel/Strobe of DataControl6.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval UINT32 - CR offset
**/
UINT32
DataControl6Offset (
  IN  UINT32  const   Channel,
  IN  UINT32  const   Strobe
);

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
);

/**
  This function returns the offset to access specific Channel/Strobe of CbtTune0.

  @params[in]  Channel - 0-based index of Channel to access.
  @params[in]  Strobe  - 0-based index of Strobe to access.

  @retval CR Offset
**/
UINT32
CBTune0Offset (
  IN  UINT32  const   DllBlock
);

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
);

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
);

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
);

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
);

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
);

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
);
#endif // _MRC_DDR_IO_OFFSETS_H_


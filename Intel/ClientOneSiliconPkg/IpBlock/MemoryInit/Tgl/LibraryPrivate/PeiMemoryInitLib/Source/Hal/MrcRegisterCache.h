/** @file
  This file contains functions to access the register cacheing information.

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
#ifndef _MrcRegisterCache_h_
#define _MrcRegisterCache_h_
#include "McAddress.h"
#include "MrcInterface.h"

#pragma pack (push, 1)
#if 0
// This code is kept for future persuit of multicasting with caching.
/**
Multicast Type definitions:
  Socket              Channel           Rank            Strobe          Bit         Cast Type
Start   End       Start    End        Start End     Start   End       Start End
Socket  Socket    Channel  Channel    Rank  Rank    Strobe  Strobe    Bit   Bit     Unicast
Socket  Socket    Channel  Channel    Rank  Rank    Strobe  Strobe    0     Max     Strobe
Socket  Socket    Channel  Channel    Rank  Rank    0       Max       X     X       Rank
Socket  Socket    Channel  Channel    0     Max     0       Max       X     X       Channel
Socket  Socket    0         Max       0     Max     0       Max       X     X       Socket
0       Max       0         Max       0     Max     0       Max       X     X       System
Socket  Socket    0         Max       Rank  Rank    0       Max       X     X       ChannelStrobe
0       Max       Channel   Channel   Rank  Rank    0       Max       X     X       SocketStrobe
Socket  Socket    0         Max       0     Max     Strobe  Strobe    X     X       ChannelRank
0       Max       Channel   Channel   0     Max     Strobe  Strobe    X     X       SocketRank
0       Max       0         Max       Rank  Rank    0       Max       X     X       SocketChannelStrobe
**/

typedef enum {
  MrcBcastUnicast,
  MrcBcastStrobe,
  MrcBcastRank,
  MrcBcastChannel,
  MrcBcastSocket,
  MrcBcastSystem,
  MrcBcastChannelStrobe,
  MrcBcastSocketStrobe,
  MrcBcastChannelRank,
  MrcBcastSocketRank,
  MrcBcastSocketChannelStrobe,
  MrcBcastMax,
  MrcBcastDelimiter = 0x7FFFFFFF
} MRC_BCAST_TYPES;

// @todo: Fix Names.
typedef struct {
  MRC_BCAST_TYPES BCastType;
  UINT32          BOffset;
  UINT32          COffset;
  UINT32          ROffset;
  UINT32          SOffset;
} MRC_REG_OFFSETS;
#endif

/**
  Invalidate the specified data in the register cache.

  @param[in]  MrcData - Pointer to MRC global data.
  @param[in]  Offset  - MCHBAR register offset.

  @retval mrcSuccess if found in the cache, otherwise mrcFail.
**/
extern
MrcStatus
InvalidateRegisterCache (
  MrcParameters *const MrcData,
  const UINT32  Offset
  );

/**
  Initialize the register cache.

  @param[in] MrcData - Pointer to MRC global data.

  @retval mrcSuccess.
**/
extern
MrcStatus
InitializeRegisterCache (
  MrcParameters *const MrcData
  );

/**
  Flush the register data cache entries marked pending to hardware.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval mrcSuccess.
**/
extern
MrcStatus
MrcFlushRegisterCachedData (
  MrcParameters *const MrcData
  );

#if 0 // This code is used for register cache debug only.
#ifdef MRC_DEBUG_PRINT
/**
  Print the entire register data cache.

  @param[in]  MrcData - Pointer to MRC global data.

  @retval mrcSuccess.
**/
extern
MrcStatus
PrintRegisterCachedData (
  MrcParameters *const MrcData
  );
#endif
#endif

/**
  This function sets the current register value and updates corresponding cache location if update cache is enabled.

  @param[in] MrcData - Pointer to global data.
  @param[in] Offset  - Register offset.
  @param[in] RegSize - TRUE if Offset points to a 64-bit register, FALSE if Offset points to a 32-bit register.
  @param[in] Mode    - Bit-field flags controlling cache access.
  @param[in] Delay   - Delay in microseconds to invoke after hardware register write.
  @param[in] Value   - New register value.

  @retval mrcSuccess or mrcWrongInputParameter if cache update is enabled and there is no cache entry.
**/
extern
MrcStatus
MrcCrCacheWrite (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const BOOLEAN RegSize,
  IN const UINT32  Mode,
  IN const UINT32  Delay,
  IN const UINT64  Value
  );

/**
  This function gets the current register value, either from the cache or from hardware if either cache reads are disabled or doesn't exist.

  @param[in] MrcData - Pointer to global data.
  @param[in] Offset  - Register offset.
  @param[in] RegSize - TRUE if Offset points to a 64-bit register, FALSE if Offset points to a 32-bit register.
  @param[in] Mode    - Bit-field flags controlling cache access.

  @retval The current register value, either from the cache or from hardware if either cache reads are disabled or doesn't exist.
**/
extern
UINT64
MrcCrCacheRead (
  IN MrcParameters *const MrcData,
  IN const UINT32  Offset,
  IN const BOOLEAN RegSize,
  IN const UINT32  Mode
  );
#pragma pack (pop)
#endif


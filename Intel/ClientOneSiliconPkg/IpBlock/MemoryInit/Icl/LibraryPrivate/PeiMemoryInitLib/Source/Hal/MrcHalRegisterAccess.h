/** @file
  Header file associated with the memory controller hardware abstraction layer.

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

#ifndef _MrcHalRegisterAccess_h_
#define _MrcHalRegisterAccess_h_
#pragma pack (push, 1)

#include "McAddress.h"
#include "MrcInterface.h"
#include "MrcDebugPrint.h"
#include "MrcRegisterCache.h"
#include "MrcDdrIoDefines.h"

///
/// Mode Parameters for MrcGetSet...()
///
#define GSM_READ_CSR      MRC_BIT0  ///< Set to force the read from hardware. Clear to read from cache.
#define GSM_READ_ONLY     MRC_BIT1  ///< Set to skip the write flow.
#define GSM_WRITE_OFFSET  MRC_BIT2  ///< Set to use the "value" input as an offset. Set to use the "value" input as an absolute.
#define GSM_FORCE_WRITE   MRC_BIT3  ///< Set to force a write even if the data to be written matches the cached value.
#define GSM_UPDATE_CACHE  MRC_BIT4  ///< Set to update cached value with the read or write value
#define GSM_COMBINE_EDGES MRC_BIT5  ///< Set to use value1 as left/low side edge and value2 as right/high side edge
                                    ///   Clear to use value1 as center and don't use value2
#define GSM_CACHE_ONLY    MRC_BIT6  ///< Set to update cached value only, clear updates both cache and hardware.
#define GSM_PRINT_VAL     MRC_BIT7  ///< Set this mode to have the HAL print the final Value before returning.
#define GSM_UPDATE_HOST   MRC_BIT8  ///< Set to update the MRC Host Data.
                                    ///   Uses MRC_DEBUG_NOTE level

#define ReadUncached              GSM_READ_CSR | GSM_READ_ONLY        ///< Force Register Field Read.
#define ReadNoCache               GSM_READ_CSR | GSM_READ_ONLY        ///< Force Register Field Read. No Cache Space is allocated.
#define ReadCached                ReadUncached | GSM_UPDATE_CACHE     ///< Force Register Field Read. Cache is updated.
#define ReadFromCache             GSM_READ_ONLY                       ///< Read Cached Value only.
#define ForceWriteUncached        GSM_FORCE_WRITE                     ///< Force Register Field write. Cache is not updated.
#define ForceWriteNoCache         GSM_FORCE_WRITE                     ///< Force Register Field write. No Cache Space is allocated.
#define WriteCached               GSM_UPDATE_CACHE                    ///< Updates Cache value to Input value.  Assumes cache coherency. Register Field is updated if Cached value differs from Input value.
#define WriteToCache              GSM_CACHE_ONLY | GSM_UPDATE_CACHE   ///< Updates the Cache Value only.
#define WriteUncached             0                                   ///< See MrcGlobal.h for the list of cached registers
#define ForceWriteCached          GSM_FORCE_WRITE | GSM_UPDATE_CACHE  ///< Force Register Field write. Cache is updated.
#define WriteOffsetUncached       GSM_WRITE_OFFSET                    ///< Add Input value to Cache value. Cache is not updated. Register Field is updated if offset value is non-zero.
#define ForceWriteOffsetCached    ForceWriteCached | GSM_WRITE_OFFSET ///< Add Input value to Cache value then Force Register Field write. Cache is updated.
#define ForceWriteOffsetUncached  GSM_WRITE_OFFSET | GSM_FORCE_WRITE  ///< Add Input value to Cache value then Force Register Field write. Cache is not updated.
#define WriteOffsetCached         GSM_WRITE_OFFSET | GSM_UPDATE_CACHE ///< Add Input value to Cache value. Cache is updated. Register Field is updated if offset value is non-zero.
#define WriteOffsetToCache        WriteOffsetCached | GSM_CACHE_ONLY  ///< Add Input value to Cache value. Cache is updated. No write to register.
#define ReadForceWriteNoCache     GSM_READ_CSR | GSM_FORCE_WRITE      ///< Read Register Field value and rewrite to it.
#define WriteNoCache              GSM_READ_CSR                        ///< Forces Read From Register (to preserver other register fields), updates the specific field, and writes the value to the register if update value is different from the Cached Value.
#define PrintValue                GSM_PRINT_VAL                       ///< GetSet will print the value after the Read/Write flow to the MRC log.

#ifdef MRC_DEBUG_PRINT
#define MRC_PRINT_DDR_IO_GROUP(MrcData, Socket, Channel, Rank, Strobe, Bit, FreqIndex, Group)\
  MrcPrintDdrIoGroup (MrcData, Socket, Channel, Rank, Strobe, Bit, FreqIndex, Group )
#else
#define MRC_PRINT_DDR_IO_GROUP( MrcData, Socket, Channel, Rank, Strobe, Bit, FreqIndex, Group)
#endif
///
/// Hash structure used by GetSet
///
#ifndef MRC_HASH_STRUCT
#define MRC_HASH_STRUCT
typedef union {
  struct {
    UINT32 Offset   :  16; // Bits 15:0
    UINT32 BfOffset :   6; // Bits 21:16
    UINT32          :   2; // Bits 23:22
    UINT32 BfWidth  :   6; // Bits 29:24
    UINT32 RegSize  :   1; // Bits 30:30
    UINT32 BfSign   :   1; // Bits 31:31
  } Bits;
  UINT32 Data;
  UINT16 Data16[2];
  UINT8  Data8[4];
} MRC_REGISTER_HASH_STRUCT;

#define MRC_REGISTER_HASH_Offset_OFF                                 ( 0)
#define MRC_REGISTER_HASH_Offset_WID                                 (16)
#define MRC_REGISTER_HASH_Offset_MSK                                 (0x0000FFFF)
#define MRC_REGISTER_HASH_Offset_MIN                                 (0)
#define MRC_REGISTER_HASH_Offset_MAX                                 (65535) // 0x0000FFFF
#define MRC_REGISTER_HASH_Offset_DEF                                 (0x00000000)

#define MRC_REGISTER_HASH_BfOffset_OFF                               (16)
#define MRC_REGISTER_HASH_BfOffset_WID                               ( 6)
#define MRC_REGISTER_HASH_BfOffset_MSK                               (0x003F0000)
#define MRC_REGISTER_HASH_BfOffset_MIN                               (0)
#define MRC_REGISTER_HASH_BfOffset_MAX                               (63) // 0x0000003F
#define MRC_REGISTER_HASH_BfOffset_DEF                               (0x00000000)

#define MRC_REGISTER_HASH_BfWidth_OFF                                (24)
#define MRC_REGISTER_HASH_BfWidth_WID                                ( 6)
#define MRC_REGISTER_HASH_BfWidth_MSK                                (0x3F000000)
#define MRC_REGISTER_HASH_BfWidth_MIN                                (0)
#define MRC_REGISTER_HASH_BfWidth_MAX                                (63) // 0x0000003F
#define MRC_REGISTER_HASH_BfWidth_DEF                                (0x00000000)

#define MRC_REGISTER_HASH_RegSize_OFF                                (30)
#define MRC_REGISTER_HASH_RegSize_WID                                ( 1)
#define MRC_REGISTER_HASH_RegSize_MSK                                (0x40000000)
#define MRC_REGISTER_HASH_RegSize_MIN                                (0)
#define MRC_REGISTER_HASH_RegSize_MAX                                (1) // 0x00000001
#define MRC_REGISTER_HASH_RegSize_DEF                                (0x00000000)

#define MRC_REGISTER_HASH_BfSign_OFF                                 (31)
#define MRC_REGISTER_HASH_BfSign_WID                                 ( 1)
#define MRC_REGISTER_HASH_BfSign_MSK                                 (0x80000000)
#define MRC_REGISTER_HASH_BfSign_MIN                                 (0)
#define MRC_REGISTER_HASH_BfSign_MAX                                 (1) // 0x00000001
#define MRC_REGISTER_HASH_BfSign_DEF                                 (0x00000000)
#endif // MRC_HASH_STRUCT

#define GSM_SAFE_STR_ACC(index)  MAX ((index), (sizeof (GsmGtDebugStrings) / sizeof (GsmGtDebugStrings[0]))

#define MRC_CLK_GRP_MAX         (4)
#define MRC_CTL_GRP_MAX         (4)
#define MRC_CKE_GRP_MAX         (4)
#define MRC_U_Y_CCC_GRP_MAX     (2)
#define MRC_H_S_CCC_GRP_MAX     (4)
#define MRC_CMD_GRP_MAX         (5)
#define MRC_CMDTXEQ_GRP_MAX     (3)

///
/// Shared Constants
///
extern const CHAR8* GsmGtDebugStrings[GsmGtMax + 4];
/**
  This function sets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetBitField32 (
  IN const UINT32 HashIn,
  IN const UINT32 BitfieldValue,
  IN const UINT32 RegisterValue
  );

/**
  This function sets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT32
MrcHalSetBitFieldS32 (
  IN const UINT32 HashIn,
  IN const INT32  BitfieldValue,
  IN const UINT32 RegisterValue
  );

/**
  This function gets the specified register bit field.

  @param[in] Group         - DDRIO group to access.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
INT32
MrcHalGsmGetBitField32 (
  IN const GSM_GT Group,
  IN const UINT32 HashIn,
  IN const UINT32 RegisterValue
);

/**
  This function gets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
UINT32
MrcHalGetBitField32 (
  IN const UINT32 HashIn,
  IN const UINT32 RegisterValue
  );

/**
  This function gets the specified register bit field.

  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
INT32
MrcHalGetBitFieldS32 (
  IN const UINT32 HashIn,
  IN const UINT32 RegisterValue
  );

/**
  This function sets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalSetBitField64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  BitfieldValue,
  IN const UINT64  RegisterValue
  );

/**
  This function sets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] BitFieldValue - The bit field value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalSetBitFieldS64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const INT64   BitfieldValue,
  IN const UINT64  RegisterValue
  );

/**
  This function gets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
UINT64
MrcHalGetBitField64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  RegisterValue
  );

/**
  This function gets the specified register bit field.

  @param[in] MrcData       - Include all MRC global data.
  @param[in] HashIn        - The bit field hash value.
  @param[in] RegisterValue - The register value to write.

  @retval The value written to the register.
**/
extern
INT64
MrcHalGetBitFieldS64 (
  IN MrcParameters *const MrcData,
  IN const UINT32  HashIn,
  IN const UINT64  RegisterValue
  );

/**
  CPU specific function when encodes Vref (mV) for the GSM_GT RxVref.

  @param[in]  MrcData       - Pointer to global data.
  @param[in]  Vref          - Vref value to encode, in mV.
  @param[out] VrefEncoding  - Register value of the Vref to program.
**/
VOID
MrcEncodeRxVref (
  IN  MrcParameters *const  MrcData,
  IN  UINT32                Vref,
  OUT INT64                 *VrefEncoded
  );

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  Only one setting for the whole controller, so Channel, Rank, Strobe, and Bit index is dropped.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupController0 (
  IN      MrcParameters *const  MrcData,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  This function is used to access indexed Command/Control/Clock groups.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Index     - Group index to Get/Set.
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoCmdGroup (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Index,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  The lowest scope of access is Channel, so Rank, Strobe, and Bit index is dropped.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupChannel (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  This function is for those registers that are only per Channel per Rank granularity.
  The lowest scope of access is Rank, so Strobe, and Bit index is dropped.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Rank      - Rank within the DDR Channel (0-based).
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupChannelRank (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  This function is for those registers that are only per Strobe per Channel granularity.
  The lowest scope of access is Strobe, so the Bit index is dropped.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Strobe    - Dqs data group within the rank (0-based).
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupChannelStrobe (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Strobe,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.
  In addition, the Bit index is dropped.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Rank      - Rank number within a channel (0-based).
  @param[in]      Strobe    - Dqs data group within the rank (0-based).
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupStrobe (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      Rank      - Rank number within a channel (0-based).
  @param[in]      Strobe    - Dqs data group within the rank (0-based).
  @param[in]      Bit       - Bit index within the data group (0-based).
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupSocket0 (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket, Channel, DIMM, Rank, Strobe, Bit, and Level.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      FreqIndex - Index supporting multiple operating frequencies.
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupFreqIndex (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   FreqIndex,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
    Socket Index, DIMM index, FreqIndex, and Level.

  @param[in]      MrcData   - Pointer to global data structure.
  @param[in]      Channel   - DDR Channel Number within the processor socket (0-based)
  @param[in]      SubChannel  - DDR SubChannel number within a Channel (0-Based).
  @param[in]      Rank      - Rank number within a channel (0-based).
  @param[in]      Strobe    - Dqs data group within the rank (0-based).
  @param[in]      Bit       - Bit index within the data group (0-based).
  @param[in]      Group     - DDRIO group to access.
  @param[in]      Mode      - Bit-field flags controlling Get/Set.
  @param[in,out]  Value     - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupSocket0Sch (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   SubChannel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      SubChannel  - DDR SubChannel number within a Channel (0-Based).
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupChSchRnk (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   SubChannel,
  IN      UINT32        const   Rank,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
  This function ignores unused parameters in Core MRC to reduce code space.
    Socket Index, DIMM index, FreqIndex, and Level.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      SubChannel  - DDR SubChannel number within a Channel (0-Based).
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroupChSch (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   SubChannel,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  Top level function used to interact with DDRIO parameters.
  The flow is as follows:
    Get the GSM_GT bit shift instruction, CR offset, and Multicasting offsets.

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based)
  @param[in]      SubChannel  - DDR SubChannel Number.
  @param[in]      Dimm        - DIMM Number within the DDR Channel (0-based). Ignored as Rank is rank number in the channel.
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Strobe      - Dqs data group within the rank (0-based).
  @param[in]      Bit         - Bit index within the data group (0-based).
  @param[in]      FreqIndex   - Index supporting multiple operating frequencies.
  @param[in]      Level       - DDRIO level to access.
  @param[in]      Group       - DDRIO group to access.
  @param[in]      Mode        - Bit-field flags controlling Get/Set.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

  @retval MrcStatus
**/
MrcStatus
MrcGetSetDdrIoGroup (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Socket,
  IN      UINT32        const   Channel,
  IN      UINT32        const   SubChannel,
  IN      UINT32        const   Dimm,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      UINT32        const   FreqIndex,
  IN      GSM_LT        const   Level,
  IN      GSM_GT        const   Group,
  IN      UINT32                Mode,
  IN OUT  INT64         *const  Value
  );

/**
  This function is the interface for the core of the MRC to get the limits of a
  specific GSM_GT parameter.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - DDRIO group to access.
  @param[out] MinVal    - Return pointer for Minimum Value supported.
  @param[out] MaxVal    - Return pointer for Maximum Value supported.
  @param[out] WaitTime  - Return pointer for settle time required in microseconds.

  @retval MrcStatus - mrcSuccess if the parameter is found, otherwise mrcFail.
**/
MrcStatus
MrcGetSetLimits (
  IN  MrcParameters *const MrcData,
  IN  GSM_GT  const   Group,
  OUT INT64   *const  MinVal,
  OUT INT64   *const  MaxVal,
  OUT UINT32  *const  WaitTime
  );

/**
  This function generates the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData     - Pointer to global data.
  @param[in]  Group       - DDRIO group to access.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  SubChannel  - DDR SubChannel within the channel Number(0-based).
  @param[in]  Rank        - Rank number within a channel (0-based).
  @param[in]  Strobe      - Dqs data group within the rank (0-based).
  @param[in]  Bit         - Bit index within the data group (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] HashVal     - Pointer to return the MMIO access instruction.

  @retval MrcStatus
**/
MrcStatus
MrcGetDdrIoHash (
  IN  MrcParameters   *const  MrcData,
  IN  GSM_GT          const   Group,
  IN  UINT32          const   Socket,
  IN  UINT32          const   Channel,
  IN  UINT32          const   SubChannel,
  IN  UINT32          const   Rank,
  IN  UINT32          const   Strobe,
  IN  UINT32          const   Bit,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  );

/**
  This function generates the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData     - Pointer to global data.
  @param[in]  Group       - DDRIO group to access.
  @param[in]  Socket      - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]  SubChannel  - DDR SubChannel within the channel Number(0-based).
  @param[in]  Rank        - Rank number within a channel (0-based).
  @param[in]  Strobe      - Dqs data group within the rank (0-based).
  @param[in]  Bit         - Bit index within the data group (0-based).
  @param[in]  FreqIndex   - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] HashVal     - Pointer to return the MMIO access instruction.

  @retval MrcStatus
**/
MrcStatus
MrcGetDdrIoCfgHash (
  IN  MrcParameters   *const  MrcData,
  IN  GSM_GT          const   Group,
  IN  UINT32          const   Socket,
  IN  UINT32          const   Channel,
  IN  UINT32          const   SubChannel,
  IN  UINT32          const   Rank,
  IN  UINT32          const   Strobe,
  IN  UINT32          const   Bit,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  );

/**
  This function generates the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - MC Timing group to access.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[out] HashVal   - Pointer to return the MMIO access instruction.

  @retval MrcStatus
**/
MrcStatus
MrcGetMcTimingHash (
  IN  MrcParameters   *const  MrcData,
  IN  GSM_GT          const   Group,
  IN  UINT32          const   Socket,
  IN  UINT32          const   Channel,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  );

/**
  This function returns the hash used to execute the Get/Set function.
  The hash consists of: Register Offset, BitField start bit, BitField length.

  @param[in]  MrcData   - Pointer to global data.
  @param[in]  Group     - MC Timing group to access.
  @param[in]  Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in]  Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in]  FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)
  @param[out] HashVal   - Pointer to return the MMIO access instruction.

  @retval MrcStatus
**/
MrcStatus
MrcGetMcConfigHash (
  IN  MrcParameters   *const  MrcData,
  IN  GSM_GT          const   Group,
  IN  UINT32          const   Socket,
  IN  UINT32          const   Channel,
  IN  UINT32          const   FreqIndex,
  OUT UINT32          *const  HashVal
  );

/**
  Get the corresponding register group and channel (register field) for a given VrefType and Channel
  based on Inputs->CaVrefConfig parameter.
  CaVrefConfig must be configured correctly for the DRAM Type
  See MrcCheckInputParams() for details.

  @param[in, out] MrcData  - Include all MRC global data.
  @param[in]      Channel  - Channel to search in.
  @param[in]      VrefType - TxVref of CmdVref
  @param[in, out] Group     - The corresponding register group
  @param[in, out] GetSetCh  - The corresponding channel in terms of register field
**/

void
GetChGroupTxVCmdV (
  IN     MrcParameters *const MrcData,
  IN     UINT8                Channel,
  IN     UINT8                VrefType,
  IN OUT GSM_GT*              Group,
  IN OUT UINT8*               GetSetCh
  );

#ifdef MRC_DEBUG_PRINT
/**
  This function outputs the specified group values to the debug print device.

  @param[in] MrcData   - Pointer to global data.
  @param[in] Group     - DDRIO group to access.
  @param[in] Socket    - Processor socket in the system (0-based).  Not used in Core MRC.
  @param[in] Channel   - DDR Channel Number within the processor socket (0-based).
  @param[in] Rank      - Rank number within a channel (0-based).
  @param[in] Strobe    - Dqs data group within the rank (0-based).
  @param[in] Bit       - Bit index within the data group (0-based).
  @param[in] FreqIndex - Index supporting multiple operating frequencies. (Not used in Client CPU's)

  @retval MrcStatus
**/
extern
MrcStatus
MrcPrintDdrIoGroup (
  IN MrcParameters *const  MrcData,
  IN UINT32  const Socket,
  IN UINT32  const Channel,
  IN UINT32  const Rank,
  IN UINT32  const Strobe,
  IN UINT32  const Bit,
  IN UINT32  const FreqIndex,
  IN GSM_GT  const Group
  );
#endif

/**
  Update MRC Host Data Structure when GSM_UPDATE_HOST is set.
  Currently only used for RxDqBitDelay and TxDqBitDelay

  @param[in]      MrcData     - Pointer to global data structure.
  @param[in]      Channel     - DDR Channel Number within the processor socket (0-based).
  @param[in]      Rank        - Rank number within a channel (0-based).
  @param[in]      Strobe      - If Group is a CMD/CTL/CLK Index type, this is the index for that signal.  Otherwise, Dqs data group within the rank (0-based).
  @param[in]      Bit         - Bit index within the data group (0-based).
  @param[in]      Group       - DDRIO group to access.
  @param[in,out]  Value       - Pointer to value for Get/Set to operate on.  Can be offset or absolute value based on mode.

**/
void
MrcGetSetUpdateHost (
  IN      MrcParameters *const  MrcData,
  IN      UINT32        const   Channel,
  IN      UINT32        const   Rank,
  IN      UINT32        const   Strobe,
  IN      UINT32        const   Bit,
  IN      GSM_GT        const   Group,
  IN      INT64         const   Value
  );

#pragma pack (pop)
#endif

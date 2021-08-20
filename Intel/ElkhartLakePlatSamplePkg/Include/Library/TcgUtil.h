/** @file
 Provides TCG high-level API to perform common TCG actions on a TCG data packet.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2016 Intel Corporation.

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

  This file contains a 'Sample Driver' and is licensed as such under the terms
  of your license agreement with Intel or your vendor. This file may be modified
  by the user, subject to the additional terms of the license agreement.

@par Specification Reference:

**/

/**
* @file
* TCG Core utility public interface header
*/

#ifndef _TCG_UTIL_H_
#define _TCG_UTIL_H_

#include <Library/TcgCore.h>
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _MSC_VER
#pragma warning ( push )
#pragma warning(disable: 4200)
#endif

#pragma pack(push, 1)

/**
* @defgroup commonCreate Common Create TCG Utility Functions
*
* These functions encode a data stream consisting of TCG ComPackets, Packets, SubPackets, and tokens
* as defined in the TCG Storage Architecture Core Specification.
*
* @{
*/

/**
*
* Adds start Method Call to the data structure using invoking id and method Id provided.
*/
TcgResult TCG_CALL tcgStartMethodCall(
    /**
    * [in/out] Structure used to add the method call
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] Invoking ID for the method call
    */
    TcgUid invokingId,

    /**
    * [in] Method ID for the method call
    */
    TcgUid methodId
);

/**
*
* Adds start parameters (STARTLIST) to the data structure.
*/
TcgResult TCG_CALL tcgStartParameters(
    /**
    * [in/out] Structure used to add the start parameters
    */
    TcgCreateStruct* createStruct
);

/**
*
* Adds end parameters (ENDLIST) to the data structure.
*/
TcgResult TCG_CALL tcgEndParameters(
    /**
    * [in/out] Structure used to add the end parameters
    */
    TcgCreateStruct* createStruct
);

/**
*
* Adds end method call (ENDDATA) to the data structure in addition to the method status list
*/
TcgResult TCG_CALL tcgEndMethodCall(
    /**
    * [in/out] Structure used to add the method call
    */
    TcgCreateStruct* createStruct
);



/**
*
* Adds Start Session call to the data structure.  This creates the entire ComPacket structure and
* returns the size of the entire compacket in the size parameter.
*/
TcgResult TCG_CALL tcgCreateStartSession(
    /**
    * [in/out] Structure used to add the start session call
    */
    TcgCreateStruct* createStruct,

    /**
    * [in/out] Describes the size of the entire ComPacket (header and payload). Filled out by function.
    */
    UINT32* size,

    /**
    * [in] ComID for the ComPacket
    */
    UINT16 comId,

    /**
    * [in] Extended ComID for the ComPacket
    */
    UINT16 comIdExtension,

    /**
    * [in] Host Session ID
    */
    UINT32 hostSessionId,

    /**
    * [in] Security Provider to start session with
    */
    TcgUid spId,

    /**
    * [in] Write option for start session.  TRUE = start session requests write access
    */
    BOOLEAN write,

    /**
    * [in] Length of the host challenge.  Length should be 0 if hostChallenge is NULL
    */
    UINT32 hostChallengeLength,

    /**
    * [in] Host challenge for Host Signing Authority.  If NULL, then no Host Challenge shall be sent.
    */
    const void* hostChallenge,

    /**
    * [in] Host Signing Authority used for start session.  If NULL, then no Host Signing Authority shall be sent.
    */
    TcgUid HostSigningAuthority
);

/**
*
* Creates ComPacket with a Method call that sets the PIN column for the row specified.
* This assumes a start session has already been opened with the desired SP.
*/
TcgResult TCG_CALL tcgCreateSetCPin(

    /**
    * [in/out] Structure used to add method call
    */
    TcgCreateStruct* createStruct,

    /**
    * [in/out] Describes the size of the entire ComPacket (header and payload). Filled out by function.
    */
    UINT32* size,

    /**
    * [in] ComID for the ComPacket
    */
    UINT16 comId,

    /**
    * [in] Extended ComID for the ComPacket
    */
    UINT16 comIdExtension,

    /**
    * [in] Tper Session ID for the Packet
    */
    UINT32 tperSession,

    /**
    * [in] Host Session ID for the Packet
    */
    UINT32 hostSession,

    /**
    * [in] UID of row of current SP to set PIN column
    */
    TcgUid sidRow,

    /**
    * [in] value of PIN to set
    */
    const void* password,

    /**
    * [in] Size of PIN
    */
    UINT32 passwordSize
);

/**
*
* Creates ComPacket with a Method call that sets the "Enabled" column for the row specified using the value specified.
* This assumes a start session has already been opened with the desired SP.
*/
TcgResult TCG_CALL tcgSetAuthorityEnabled(

    /**
    * [in/out] Structure used to add method call
    */
    TcgCreateStruct* createStruct,

    /**
    * [in/out] Describes the size of the entire ComPacket (header and payload). Filled out by function.
    */
    UINT32* size,

    /**
    * [in] ComID for the ComPacket
    */
    UINT16 comId,

    /**
    * [in] Extended ComID for the ComPacket
    */
    UINT16 comIdExtension,

    /**
    * [in] Tper Session ID for the Packet
    */
    UINT32 tperSession,

    /**
    * [in] Host Session ID for the Packet
    */
    UINT32 hostSession,

    /**
    * [in] Authority UID to modify the "Enabled" column for
    */
    TcgUid authorityUid,

    /**
    * [in] Value to set the "Enabled" column to
    */
    BOOLEAN enabled
);

/**
*
* Creates ComPacket with EndSession.
* This assumes a start session has already been opened.
*/
TcgResult TCG_CALL tcgCreateEndSession(
    /**
    * [in/out] Structure used to add Endsession
    */
    TcgCreateStruct* createStruct,

    /**
    * [in/out] Describes the size of the entire ComPacket (header and payload). Filled out by function.
    */
    UINT32* size,

    /**
    * [in] ComID for the ComPacket
    */
    UINT16 comId,

    /**
    * [in] Extended ComID for the ComPacket
    */
    UINT16 comIdExtension,

    /**
    * [in] Host Session ID for the Packet
    */
    UINT32 hostSession,

    /**
    * [in] Tper Session ID for the Packet
    */
    UINT32 tpSessionId
);



/** @} */ // end of createCommon


/**
* @defgroup parseCommon Parse TCG ComPacket Utility Functions
*
* These functions decode a data stream consisting of TCG ComPackets, Packets, SubPackets, and tokens
* as defined in the TCG Storage Architecture Core Specification.
*
* @{
*/

/**
*
* Retrieves human-readable token type name.
*/
const char* TCG_CALL tcgTokenTypeString(
    /**
    * [in] Token type to retrieve
    */
    TcgTokenType type
);


/**
*
* Returns the method status of the current subpacket.  Does not affect the current position
* in the ComPacket.  In other words, it can be called whenever you have a valid SubPacket.
*/
TcgResult TCG_CALL tcgGetMethodStatus(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    const TcgParseStruct* parseStruct,

    /**
    * [in/out] Method status retrieved of the current SubPacket
    */
    UINT8* methodStatus
);


/**
* Returns a human-readable string representing a method status return code.
*/
const char* TCG_CALL tcgMethodStatusString(
    /**
    * [in] Method status to translate to a string
    */
    UINT8 methodStatus
);


/**
* Retrieves the comID and Extended comID of the ComPacket in the Tcg response.
* It is intended to be used to confirm the received Tcg response is intended for user that received it.
*/
TcgResult TCG_CALL tcgGetComIds(
    /**
    * [in] Structure used to parse received TCG response
    */
    const TcgParseStruct* parseStruct,

    /**
    * [in/out] comID retrieved from received ComPacket
    */
    UINT16* comId,

    /**
    * [in/out] Extended comID retrieved from received ComPacket
    */
    UINT16* comIdExtension
);


/**
* Checks if the ComIDs of the response match the expected values.
*/
TcgResult TCG_CALL tcgCheckComIds(
    /**
    * [in] Structure used to parse received TCG response
    */
    const TcgParseStruct* parseStruct,

    /**
    * [in] Expected comID
    */
    UINT16 expectedComId,

    /**
    * [in] Expected extended comID
    */
    UINT16 expectedComIdExtension
);

/**
* Parses the Sync Session response contained in the parseStruct to retrieve Tper session ID.  If the Sync Session response
* parameters do not match the comID, extended ComID and host session ID then a failure is returned.
*/
TcgResult TCG_CALL tcgParseSyncSession(
    /**
    * [in/out] Structure used to parse received TCG response, contains Sync Session response.
    */
    const TcgParseStruct* parseStruct,

    /**
    * [in] Expected ComID that is compared to actual ComID of response
    */
    UINT16 comId,

    /**
    * [in] Expected Extended ComID that is compared to actual Extended ComID of response
    */
    UINT16 comIdExtension,

    /**
    * [in] Expected Host Session ID that is compared to actual  Host Session ID of response
    */
    UINT32 hostSessionId,

    /**
    * [in/out] Tper Session ID retrieved from the Sync Session response.
    */
    UINT32* tperSessionId
);


TcgResult TCG_CALL tcgCreateSetAce(
    TcgCreateStruct* createStruct,
    UINT32* size,
    UINT16 comId,
    UINT16 comIdExtension,
    UINT32 tperSession,
    UINT32 hostSession,
    TcgUid aceRow,
    TcgUid authority1,
    BOOLEAN logicalOperator,
    TcgUid authority2
);


typedef BOOLEAN(TCG_CALL* TcgLevel0EnumCallback)(
    const TCG_LEVEL0_DISCOVERY_HEADER* discoveryHeader,
    TCG_LEVEL0_FEATURE_DESCRIPTOR_HEADER* feature,
    UINTN featureSize, // includes header
    void* context
);

BOOLEAN TCG_CALL tcgEnumLevel0Discovery(
    const TCG_LEVEL0_DISCOVERY_HEADER* discoveryHeader,
    TcgLevel0EnumCallback callback,
    void* context
);

const TCG_LEVEL0_FEATURE_DESCRIPTOR_HEADER* TCG_CALL tcgGetFeature(
    const TCG_LEVEL0_DISCOVERY_HEADER* discoveryHeader,
    UINT16 featureCode,
    UINTN* featureSize
);

/**
*
* Determines if the protocol provided is part of the provided supported protocol list.
*
* @return TRUE = protocol is supported, FALSE = protocol is not supported
*/
BOOLEAN TCG_CALL tcgIsProtocolSupported(
    /**
    * [in] Supported protocol list to investigate
    */
    const TCG_SUPPORTED_SECURITY_PROTOCOLS* protocolList,

    /**
    * [in] Protocol value to determine if supported
    */
    UINT16 protocol
);

/**
*
* Determines if the Locking Feature "Locked" bit is set in the level 0 discovery response
*
* @return TRUE = Locked is set, FALSE = Locked is false
*/
BOOLEAN TCG_CALL tcgIsLocked(

    /**
    * [in] Level 0 discovery response
    */
    const TCG_LEVEL0_DISCOVERY_HEADER* discovery
);

/** @} */ // end of parseCommon functions

#pragma pack(pop)

#ifdef _MSC_VER
#pragma warning(pop)    // C4200 zero-sized array
#endif

#ifdef __cplusplus
}
#endif

#endif // _TCG_UTIL_H_

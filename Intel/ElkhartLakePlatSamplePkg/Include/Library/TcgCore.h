/** @file
 Public API for the Tcg Core library to perform the lowest level TCG data encoding.

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
* TCG Core public interface header
*/

#ifndef _TCG_CORE_H_
#define _TCG_CORE_H_

#include <Library/Tcg.h>
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef _MSC_VER
#define TCG_CALL __stdcall
#else
#define TCG_CALL
#endif

#ifdef _MSC_VER
#pragma warning ( push )
#pragma warning(disable: 4200)
#endif

#pragma pack(push, 1)

/**
* Tcg result codes.
*
* The result code indicates if the Tcg function call was successful or not
*/
typedef enum {
    /**
    * This is the return result upon successful completion of a Tcg function call
    */
    TcgResult_Success,

    /**
    * This is the return "catchall" result for the failure of a Tcg function call
    */
    TcgResult_Failure,

    /**
    * This is the return result if a required parameter was Null for a Tcg function call
    */
    TcgResult_Failure_NullPointer,

    /**
    * This is the return result if a required buffersize was 0 for a Tcg function call
    */
    TcgResult_Failure_ZeroSize,

    /**
    * This is the return result if a Tcg function call was executed out of order.
    * For instance, starting a Tcg subpacket before starting its Tcg packet.
    */
    TcgResult_Failure_InvalidAction,

    /**
    * This is the return result if the buffersize provided is not big enough to add a requested Tcg encoded item.
    */
    TcgResult_Failure_BufferTooSmall,

    /**
    * This is the return result for a Tcg parse function if the end of the parsed buffer is reached, yet data is still attempted to be retrieved.
    * For instance, attempting to retrieve another Tcg token from the buffer after it has reached the end of the Tcg subpacket payload.
    */
    TcgResult_Failure_EndBuffer,

    /**
    * This is the return result for a Tcg parse function if the Tcg Token item requested is not the expected type.
    * For instance, the caller requested to receive an integer and the Tcg token was a byte sequence.
    */
    TcgResult_Failure_InvalidType,
} TcgResult;


/**
* @defgroup create Create TCG ComPacket Functions
*
* These functions encode a data stream consisting of TCG ComPackets, Packets, SubPackets, and tokens
* as defined in the TCG Storage Architecture Core Specification.
*
* @{
*/


/**
* Structure that is used to build the Tcg ComPacket.  It contains the start buffer pointer and the current position of the
* Tcg ComPacket, current Tcg Packet and Tcg SubPacket. This structure must be initialized
* by calling tcgInitTcgCreateStruct before it is used as parameter to any other Tcg function.
* This structure should NOT be directly modified by the client of this library.
*
*  NOTE:  WE MAY MAKE THIS AN ABSTRACT STRUCTURE WITH A DEFINED SIZE AND KEEP THE VARIABLES
*         INTERNAL AND ONLY KNOWN TO THE TCG LIBRARY
*
* @sa tcgInitTcgCreateStruct
*/
typedef struct _TcgCreateStruct {
    /**
    * Buffer allocated and freed by the client of the Tcg library.
    * This is the buffer that shall contain the final Tcg encoded compacket.
    */
    void*           buffer;

    /**
    * Size of the buffer provided.
    */
    UINT32          bufferSize;

    /**
    * Pointer to the start of the Tcg ComPacket.  It should point to a location within buffer.
    */
    TcgComPacket*   comPacket;

    /**
    * Current Tcg Packet that is being created.  It should point to a location within buffer.
    */
    TcgPacket*      curPacket;

    /**
    * Current Tcg SubPacket that is being created.  It should point to a location within buffer.
    */
    TcgSubPacket*   curSubPacket;

    /**
    * Flag used to indicate if the buffer of the structure should be filled out.
    * This is intended to be used to support a use-case where the client of library
    * can perform all the desired tcg calls to determine what the actual size of the final compacket will be.
    * Then the client can allocate the required buffer size and re-run the tcg calls.
    * THIS MAY NOT BE IMPLEMENTED... REQUIRES MORE THOUGHT BECAUSE YOU CANNOT SOLVE ISSUE FOR RECEIVE
    */
    BOOLEAN         dryRun;
} TcgCreateStruct;


/**
*
* Required to be called before calling any other Tcg functions with the TcgCreateStruct.
* Initializes the packet variables to NULL.  Additionally, the buffer will be memset.
*/
TcgResult TCG_CALL tcgInitTcgCreateStruct(

    /**
    * [in/out] Structure to initialize
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] Buffer allocated by client of library.  It will contain the Tcg encoded packet.  This cannot be null.
    */
    void* buffer,

    /**
    * [in] Size of buffer provided.  It cannot be 0.
    */
    UINT32 bufferSize
);


/**
*
* Encodes the ComPacket header to the data structure.
*/
TcgResult TCG_CALL tcgStartComPacket(
    /**
    * [in/out] Structure used to build Tcg Compacket
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] ComID of the Tcg ComPacket.
    */
    UINT16 comId,

    /**
    * [in] ComID Extension of the Tcg ComPacket.
    */
    UINT16 comIdExtension
);


/**
*
* Starts a new ComPacket in the data structure.
*/
TcgResult TCG_CALL tcgStartPacket(
    /**
    * [in/out] Structure used to add Tcg Packet
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] Packet Tper session number
    */
    UINT32 tsn,

    /**
    * [in] Packet Host session number
    */
    UINT32 hsn,

    /**
    * [in] Packet Sequence Number
    */
    UINT32 seqNumber,

    /**
    * [in] Packet Acknowledge Type
    */
    UINT16 ackType,

    /**
    * [in] Packet Acknowledge
    */
    UINT32 ack
);


/**
*
* Starts a new SubPacket in the data structure.
*/
TcgResult TCG_CALL tcgStartSubPacket(
    /**
    * [in/out] Structure used to start Tcg SubPacket
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] SubPacket kind
    */
    UINT16 kind
);


/**
*
* Ends the current SubPacket in the data structure.  This function will also perform the 4-byte padding
* required for Subpackets.
*/
TcgResult TCG_CALL tcgEndSubPacket(
    /**
    * [in/out] Structure used to end the current Tcg SubPacket
    */
    TcgCreateStruct* createStruct
);


/**
*
* Ends the current Packet in the data structure.
*/
TcgResult TCG_CALL tcgEndPacket(
    /**
    * [in/out] Structure used to end the current Tcg Packet
    */
    TcgCreateStruct* createStruct
);


/**
*
* Ends the ComPacket in the data structure and ret
*/
TcgResult TCG_CALL tcgEndComPacket(
    /**
    * [in/out] Structure used to end the Tcg ComPacket
    */
    TcgCreateStruct* createStruct,

    /**
    * [in/out] Describes the size of the entire ComPacket (header and payload). Filled out by function.
    */
    UINT32* size
);


/**
* @defgroup createSubPacket Create TCG SubPacket Functions
*
* These functions encode tokens contained in a SubPacket
* as defined in the TCG Storage Architecture Core Specification.
*
* @{
*/



/**
* @defgroup createAtom Create TCG Atom Functions
*
* These functions encode simple atom tokens contained in a SubPacket
* as defined in the TCG Storage Architecture Core Specification.
*
* @{
*/

/**
*
* Adds a single raw token byte to the data structure.
*/
TcgResult TCG_CALL tcgAddRawByte(
    /**
    * [in/out] Structure used to add the byte
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] Byte to add
    */
    UINT8 byte
);


/**
*
* Adds the data parameter as a byte sequence to the data structure.
*/
TcgResult TCG_CALL tcgAddByteSequence(
    /**
    * [in/out] Structure used to add the byte sequence
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] Byte sequence that will be encoded and copied into data structure
    */
    const void* data,

    /**
    * [in] Length of data provided
    */
    UINT32 dataSize,

    /**
    * [in] TRUE if byte sequence is continued or
    *      FALSE if the data contains the entire byte sequence to be encoded
    */
    BOOLEAN continued
);


/**
*
* Adds an arbitrary-length integer to the data structure.
*
* The integer will be encoded using the shortest possible atom.
*/
TcgResult TCG_CALL tcgAddInteger(
    /**
    * [in/out] Structure used to add the integer
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] Integer in host byte order that will be encoded and copied into data structure
    */
    const void* data,

    /**
    * [in] Length in bytes of the data provided
    */
    UINT32 dataSize,

    /**
    * [in] TRUE if the integer is signed or FALSE if the integer is unsigned
    */
    BOOLEAN signedInteger
);


/**
*
* Adds an 8-bit unsigned integer to the data structure.
*/
TcgResult TCG_CALL tcgAddUINT8(
    /**
    * [in/out] Structure used to add the integer
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] Integer value to add
    */
    UINT8 value
);


/**
*
* Adds a 16-bit unsigned integer to the data structure.
*/
TcgResult TCG_CALL tcgAddUINT16(
    /**
    * [in/out] Structure used to add the integer
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] Integer value to add
    */
    UINT16 value
);


/**
*
* Adds a 32-bit unsigned integer to the data structure.
*/
TcgResult TCG_CALL tcgAddUINT32(
    /**
    * [in/out] Structure used to add the integer
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] Integer value to add
    */
    UINT32 value
);


/**
 *
 * Adds a 64-bit unsigned integer to the data structure.
 */
TcgResult TCG_CALL tcgAddUINT64(
    /**
     * [in/out] Structure used to add the integer
     */
    TcgCreateStruct* createStruct,

    /**
    * [in] Integer value to add
    */
    UINT64 value
);


/**
*
* Adds a BOOLEAN to the data structure.
*/
TcgResult TCG_CALL tcgAddBOOLEAN(
    /**
    * [in/out] Structure used to add the integer
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] BOOLEAN value to add
    */
    BOOLEAN value
);


/**
*
* Adds a TcgUid to the data structure.
*/
TcgResult TCG_CALL tcgAddTcgUid(
    /**
    * [in/out] Structure used to add the TcgUid
    */
    TcgCreateStruct* createStruct,

    /**
    * [in] TcgUid value to add
    */
    TcgUid uid
);


/** @} */ // end of atom functions


/**
* @defgroup createSequenceTokens Create TCG Sequence Token Functions
*
* These functions encode sequence tokens contained in a SubPacket
* as defined in the TCG Storage Architecture Core Specification.
*
* @{
*/

/**
*
* Adds a Start List token to the data structure.
*/
TcgResult TCG_CALL tcgAddStartList(
    /**
    * [in/out] Structure used to add the token
    */
    TcgCreateStruct* createStruct
);


/**
*
* Adds an End List token to the data structure.
*/
TcgResult TCG_CALL tcgAddEndList(
    /**
    * [in/out] Structure used to add the token
    */
    TcgCreateStruct* createStruct
);


/**
*
* Adds a Start Name token to the data structure.
*/
TcgResult TCG_CALL tcgAddStartName(
    /**
    * [in/out] Structure used to add the token
    */
    TcgCreateStruct* createStruct
);


/**
*
* Adds an End Name token to the data structure.
*/
TcgResult TCG_CALL tcgAddEndName(
    /**
    * [in/out] Structure used to add the token
    */
    TcgCreateStruct* createStruct
);


/** @} */ // end of sequence token functions


/**
* @defgroup createControlTokens Create TCG Control Token Functions
*
* These functions encode sequence tokens contained in a SubPacket
* as defined in the TCG Storage Architecture Core Specification.
*
* @{
*/

/**
*
* Adds a Call token to the data structure.
*/
TcgResult TCG_CALL tcgAddCall(
    /**
    * [in/out] Structure used to add the token
    */
    TcgCreateStruct* createStruct
);


/**
*
* Adds an End of Data token to the data structure.
*/
TcgResult TCG_CALL tcgAddEndOfData(
    /**
    * [in/out] Structure used to add the token
    */
    TcgCreateStruct* createStruct
);


/**
*
* Adds an End of Session token to the data structure.
*/
TcgResult TCG_CALL tcgAddEndOfSession(
    /**
    * [in/out] Structure used to add the token
    */
    TcgCreateStruct* createStruct
);


/**
*
* Adds a Start Transaction token to the data structure.
*/
TcgResult TCG_CALL tcgAddStartTransaction(
    /**
    * [in/out] Structure used to add the token
    */
    TcgCreateStruct* createStruct
);


/**
*
* Adds an End Transaction token to the data structure.
*/
TcgResult TCG_CALL tcgAddEndTransaction(
    /**
    * [in/out] Structure used to add the token
    */
    TcgCreateStruct* createStruct
);

/** @} */ // end of control token functions

/** @} */ // end of createSubPacket functions

/** @} */ // end of create functions



/**
* @defgroup parse Parse TCG ComPacket Functions
*
* These functions decode a data stream consisting of TCG ComPackets, Packets, SubPackets, and tokens
* as defined in the TCG Storage Architecture Core Specification.
*
* @{
*/


/**
* Structure that is used to parse the Tcg response received.  It contains the response buffer pointer
* and the current position of the Tcg ComPacket, current Tcg Packet and Tcg SubPacket being parsed.
* This structure must be initialized by calling tcgInitTcgParseStruct before it is used as parameter to any other Tcg parse function.
* This structure should NOT be directly modified by the client of this library.
*
*  NOTE:  WE MAY MAKE THIS AN ABSTRACT STRUCTURE WITH A DEFINED SIZE AND KEEP THE VARIABLES
*         INTERNAL AND ONLY KNOWN TO THE TCG LIBRARY
*
* @sa tcgInitTcgParseStruct
*/
typedef struct _TcgParseStruct {
    /**
    * Buffer allocated and freed by the client of the Tcg library.
    * This is the buffer that contains the Tcg response to decode/parse.
    */
    const void*         buffer;

    /**
    * Size of the buffer provided.
    */
    UINT32              bufferSize;

    /**
    * Pointer to the start of the Tcg ComPacket.  It should point to a location within buffer.
    */
    const TcgComPacket* comPacket;

    /**
    * Current Tcg Packet that is being created.  It should point to a location within buffer.
    */
    const TcgPacket*    curPacket;

    /**
    * Current Tcg SubPacket that is being created.  It should point to a location within buffer.
    */
    const TcgSubPacket* curSubPacket;

    /**
    * Current pointer within the current subpacket payload.
    */
    const UINT8*        curPtr;
} TcgParseStruct;


/**
* Structure that is used to represent a Tcg Token that is retrieved by Tcg parse functions.
*/
typedef struct _TcgToken {
    /**
    * Describes the type of Tcg token the hdr start points to.
    */
    TcgTokenType   type;

    /**
    * Pointer to the beginning of the header of the Tcg token
    */
    const UINT8*   hdrStart;
} TcgToken;


/**
*
* Intializes the parsing structure used to parse the Tcg response.  This must be called before using the
* parseStruct with any other function.
*/
TcgResult TCG_CALL tcgInitTcgParseStruct(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct,

    /**
    * [in] Buffer containing TCG response
    */
    const void* buffer,

    /**
    * [in] Size of buffer containing TCG response
    */
    UINT32 bufferSize
);


/**
*
* Retrieves next Tcg Token from the current subpacket payload.  The first time it is called on a parse structure
* it starts at the first Subpacket of the first Packet.
*/
TcgResult TCG_CALL tcgGetNextToken(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct,

    /**
    * [in/out] Tcg Token that was found.  Buffer was verified to guarantee the entire Token can be accessed by caller.
    */
    TcgToken* tcgToken
);


/**
* Retrieves the next TCG token from the current subpacket payload.
* If the token is not of the specified type, an error is returned.
*
* This function is intended for use with sequence and control tokens that have no payload,
* since it does not return the token contents.
*/
TcgResult TCG_CALL tcgGetNextTokenType(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct,

    /**
    * [in] Expected TCG token type
    */
    TcgTokenType type
);


/**
*
* Retrieves information about a simple token containing an atom.
*/
TcgResult TCG_CALL tcgGetAtomInfo(
    /**
    * [in/out] TCG token containing simple token atom to retrieve
    */
    const TcgToken* tcgToken,

    /**
    * [out] Length of token header.
    *
    * This is the number of bytes from the start of the token up to the beginning of the data.
    */
    UINT32* headerLength,

    /**
    * [out] Length of data.
    *
    * This is the size of the byte or integer data following the token header.
    */
    UINT32* dataLength,

    /**
    * [out] Flag indicating whether the atom is a byte sequence (TCG_ATOM_TYPE_BYTE) or integer (TCG_ATOM_TYPE_INTEGER).
    */
    UINT8* byteOrInt,

    /**
    * [out] Flag indicating whether an integer atom is a signed integer or whether a byte sequence atom is continued.
    */
    UINT8* signOrCont
);


/**
*
* Retrieves byte sequence from the Tcg Token provided.
*
* @return NULL if failure occurs, otherwise pointer to beginning of byte sequence.
*/
const UINT8* TCG_CALL tcgGetTokenByteSequence(
    /**
    * [in/out] Tcg Token containing byte sequence value to retrieve
    */
    const TcgToken* tcgToken,

    /**
    * [out] Length of the byte sequence retrieved
    */
    UINT32* length
);


/**
*
* Retrieves Integer value up to 64-bits in size from the Tcg Token provided.
*/
TcgResult TCG_CALL tcgGetTokenUINT64(
    /**
    * [in/out] Tcg Token containing integer value to retrieve
    */
    const TcgToken* tcgToken,

    /**
    * [in/out] Integer value retrieved
    */
    UINT64* value
);


/**
*
* Retrieves next token in the current payload.  If it is not a UINT8 then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextUINT8(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct,

    /**
    * [in/out] UINT8 value retrieved from current payload
    */
    UINT8* value
);


/**
*
* Retrieves next token in the current payload.  If it is not a UINT16 then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextUINT16(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct,

    /**
    * [in/out] UINT16 value retrieved from current payload
    */
    UINT16* value
);


/**
*
* Retrieves next token in the current payload.  If it not a UINT32 then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextUINT32(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct,

    /**
    * [in/out] UINT32 value retrieved from current payload
    */
    UINT32* value
);


/**
*
* Retrieves next token in the current payload.  If it is not a UINT64 then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextUINT64(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct,

    /**
    * [in/out] UINT64 value retrieved from current payload
    */
    UINT64* value
);


/**
*
* Retrieves next token in the current payload.  If it not a BOOLEAN then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextBOOLEAN(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct,

    /**
    * [in/out] BOOLEAN value retrieved from current payload
    */
    BOOLEAN* value
);

/**
*
* Retrieves next token in the current payload.  If it is not a TcgUid then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextTcgUid(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct,

    /**
    * [out] TcgUid value retrieved from current payload
    */
    TcgUid* uid
);


/**
*
* Retrieves next token in the current payload.  If it is not a byte sequence, then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextByteSequence(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct,

    /**
    * [out] Pointer to the beginning of the byte sequence
    */
    const void** data,

    /**
     * [out] Length of the retrieved byte sequence in bytes
     */
    UINT32* length
);


/**
*
* Retrieves next token in the current payload.  If it is not a Start List token, then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextStartList(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct
);


/**
*
* Retrieves next token in the current payload.  If it is not an End List token, then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextEndList(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct
);


/**
*
* Retrieves next token in the current payload.  If it is not a Start Name token, then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextStartName(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct
);


/**
*
* Retrieves next token in the current payload.  If it is not an End Name token, then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextEndName(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct
);


/**
*
* Retrieves next token in the current payload.  If it is not a Call token, then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextCall(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct
);


/**
*
* Retrieves next token in the current payload.  If it is not an End of Data token, then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextEndOfData(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct
);


/**
*
* Retrieves next token in the current payload.  If it is not an End of Session token, then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextEndOfSession(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct
);


/**
*
* Retrieves next token in the current payload.  If it is not a Start Transaction token, then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextStartTransaction(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct
);


/**
*
* Retrieves next token in the current payload.  If it is not an End Transaction token, then a failure is reported.
*/
TcgResult TCG_CALL tcgGetNextEndTransaction(
    /**
    * [in/out] Structure used to parse received TCG response
    */
    TcgParseStruct* parseStruct
);

/** @} */ // end of parse functions


#pragma pack(pop)
#ifdef _MSC_VER
#pragma warning(pop)    // C4200 zero-sized array
#endif

#ifdef __cplusplus
}
#endif

#endif // _TCG_CORE_H_

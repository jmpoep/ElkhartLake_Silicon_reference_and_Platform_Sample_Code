/** @file
  Adaptation layer for parsing Vendor Specific HCI commands and calling
  respective APIs and generating VS HCI events.

Copyright (c) 2017, Intel Mobile Communications GmbH. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

/** @brief The callback function define the format for reporting Event generated in response of the Vendor Specific HCI iLE Command to the Host.
 *		  @param op_code   : op_code of data sent
 *		  @param len	   : Length of data sent
 *		  @param UINT8Hcidata : Data sent using Vendor Specific HCI format
 *							Callee must not free the pointer or alter the information.
 *							 Pointer shall be removed after the callee exits.
 *
 * @typedef hci2ile_Event_Dispatch_cb_t
 */
typedef void (*hci2ile_Event_Dispatch_cb_t)(UINT16 op_code , UINT8 len , UINT8 * hcidata);

/** @brief The callback function define the format for reporting Status of the Vendor Specific HCI iLE Command to the Host.
 *		  This callback is mapped to the corresponding Command sent from host.
 *		  The Status callback is generally mapped to Command complete event.
 *		  @param op_code   : op_code of data sent
 *		  @param len	   : Length of data sent
 *		  @param UINT8Hcidata : Data sent using Vendor Specific HCI format
 *							 Callee must not free the pointer or alter the information.
 *							 Pointer shall be removed after the callee exits.
 *
 * @typedef hci2ile_Status_Dispatch_cb_t
 */
typedef void (*hci2ile_Status_Dispatch_cb_t)(UINT16 op_code , UINT8 len , UINT8 * hcidata);

/** @brief: This function is used to initialze the adaptation layer and register the callback required to send Status and Event
*		   to the host. This function must be called before calling hci2ile_Command_Dispatch_Req.
*
*Function: hci2ile_Initialize:
*			The function initialize the HCI2ILE Adaptation layer. Its registers the callback required for Adaptation to send
*		   the Status and Events back to the Host.
*			@param hci2ile_Status_cb : Callback function required to send the Status message.
*			@paramt hci2ile_Event_cb : Callack function required to send Events.
*			the mapping of the same is done in hci2ile_adaptation.c
*/

void hci2ile_initialize(hci2ile_Status_Dispatch_cb_t hci2ile_Status_cb, hci2ile_Event_Dispatch_cb_t hci2ile_Event_cb);

/** @brief The transport thread of the controller calls this function if the op_code matches our op_code ( 0xFC80)
 *
 * Function: hci2ile_Command_Dispatch_Req
 *		This function will parse the hci command and pass on the parameters are required by the various APIs.
 *
 *
 * 			@param op_code   : opcode
 * 			@param len	   : length of hci command
 * 			@param UINT8Hcidata : Pointer to incoming Vendor Specific HCI ILE command buffer after the length field
 *							 Callee must not free the pointer or alter the information.
 *							 Pointer shall be removed after the callee exits.
 *
 */
void hci2ile_command_dispatch_req(UINT16 op_code, UINT8 len, UINT8 *hcidata);
//extern void hci2ile_Command_Dispatch_Req(UINT16 op_code, UINT8 len, UINT8 *hcidata);
/*end of file*/

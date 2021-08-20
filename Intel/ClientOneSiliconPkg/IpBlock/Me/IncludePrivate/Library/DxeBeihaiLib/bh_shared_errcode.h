/** @file
  This file declares the error code (integer value) across different
  Beihai components in host and firmware.

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

  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
  the terms of your license agreement with Intel or your vendor. This file may
  be modified by the user, subject to additional terms of the license agreement.

@par Specification Reference:
**/

#ifndef __BH_SHARED_ERRCODE_H
#define __BH_SHARED_ERRCODE_H


typedef int BH_RET; //BH_RET should have values defined following

//Following are error code number(integer value) across Beihai host and firmware.

#define BH_SUCCESS                              0x0

/////BHP specific error code section:           0x000
#define BPE_NOT_INIT                            0x001
#define BPE_SERVICE_UNAVAILABLE                 0x002
#define BPE_INTERNAL_ERROR                      0x003
#define BPE_COMMS_ERROR                         0x004
#define BPE_OUT_OF_MEMORY                       0x005
#define BPE_INVALID_PARAMS                      0x006
#define BPE_MESSAGE_TOO_SHORT                   0x007
#define BPE_MESSAGE_ILLEGAL                     0x008
#define BPE_NO_CONNECTION_TO_FIRMWARE           0x009
#define BPE_NOT_IMPLEMENT                       0x00A
#define BPE_OUT_OF_RESOURCE                     0x00B
#define BPE_INITIALIZED_ALREADY                 0x00C
#define BPE_CONNECT_FAILED                      0x00D
//////////////////////////////////////////////////

//General error code section for Beihai on FW:  0x100
#define BHE_OUT_OF_MEMORY                       0x101
/* Bad parameters to native */
#define BHE_BAD_PARAMETER                       0x102
#define BHE_INSUFFICIENT_BUFFER                 0x103
#define BHE_MUTEX_INIT_FAIL                     0x104
#define BHE_COND_INIT_FAIL                      0x105
/* Watchdog time out */
#define BHE_WD_TIMEOUT                          0x106
#define BHE_FAILED                              0x107
#define BHE_INVALID_HANDLE                      0x108
/* IPC error code */
#define BHE_IPC_ERR_DEFAULT                     0x109
#define BHE_IPC_ERR_PLATFORM                    0x10A
#define BHE_IPC_SRV_INIT_FAIL                   0x10B
//////////////////////////////////////////////////

//VM communication error code section:          0x200
#define BHE_MAILBOX_NOT_FOUND                   0x201
#define BHE_APPLET_CRASHED                      BHE_MAILBOX_NOT_FOUND
#define BHE_MSG_QUEUE_IS_FULL                   0x202
/* Mailbox is denied by firewall */
#define BHE_MAILBOX_DENIED                      0x203
//////////////////////////////////////////////////

//VM InternalAppletCommunication error          0x240
#define BHE_IAC_INTERNAL_SESSION_NUM_EXCEED     0x241
#define BHE_IAC_CLIENT_SLOT_FULL                0x242
#define BHE_IAC_SERVICETA_EXITED                0x243
#define BHE_IAC_EXIST_INTERNAL_SESSION          0x244
#define BHE_IAC_SERVICETA_UNCAUGHT_EXCEPTION    0x245
#define BHE_IAC_SERVICE_SESSION_NOT_FOUND       0x246
#define BHE_IAC_SERVICE_HOST_SESSION_NUM_EXCEED 0x247
//////////////////////////////////////////////////

//Firmware thread/mutex error code section:     0x280
#define BHE_THREAD_ERROR                        0x281
#define BHE_THREAD_TIMED_OUT                    0x282
//////////////////////////////////////////////////

//Applet manager error code section:            0x300
/* JEFF file load fail, OOM or file format error not distinct by VM*/
#define BHE_LOAD_JEFF_FAIL                      0x303
/* Request operation on a package, but it does not exist.*/
#define BHE_PACKAGE_NOT_FOUND                   0x304
/* Uninstall package fail because of live session exist.*/
#define BHE_EXIST_LIVE_SESSION                  0x305
/* VM instance init fail when create session.*/
#define BHE_VM_INSTANCE_INIT_FAIL               0x306
/* Query applet property that Beihai does not support.*/
#define BHE_QUERY_PROP_NOT_SUPPORT              0x307
/* Incorrect Beihai package format */
#define BHE_INVALID_BPK_FILE                    0x308
/* Download a package which has already exists in app manager*/
#define BHE_PACKAGE_EXIST                       0x309
/* VM instance not found */
#define BHE_VM_INSTNACE_NOT_FOUND               0x312
/* JDWP agent starting fail */
#define BHE_STARTING_JDWP_FAIL                  0x313
/* Group access checking fail*/
#define BHE_GROUP_CHECK_FAIL                    0x314
/* package SDID dose not equal to the effective one in app manager*/
#define BHE_SDID_UNMATCH                        0x315
#define BHE_APPPACK_UNINITED                    0x316
#define BHE_SESSION_NUM_EXCEED                  0x317
/* TA package verify failure */
#define BHE_TA_PACKAGE_HASH_VERIFY_FAIL         0x318
/*SDID has not been reset to invalid one
#define BHE_SDID_NOT_RESET                      0x316
*/
/* Switch SD for IVM*/
#define BHE_SWITCH_ISD                          0x319
//////////////////////////////////////////////////

//VM Applet instance error code section:        0x400
#define BHE_APPLET_GENERIC                      0x400
#define BHE_UNCAUGHT_EXCEPTION                  0x401
/* Bad parameters to applet */
#define BHE_APPLET_BAD_PARAMETER                0x402
/* Small response buffer */
#define BHE_APPLET_SMALL_BUFFER                 0x403
/* Bad state */
#define BHE_BAD_STATE                           0x404
//////////////////////////////////////////////////

/*TODO: Should be removed these UI error code when integrate with ME 9 */
#define BHE_UI_EXCEPTION                        0x501
#define BHE_UI_ILLEGAL_USE                      0x502
#define BHE_UI_ILLEGAL_PARAMETER                0x503
#define BHE_UI_NOT_INITIALIZED                  0x504
#define BHE_UI_NOT_SUPPORTED                    0x505
#define BHE_UI_OUT_OF_RESOURCES                 0x506
//////////////////////////////////////////////////

//BeiHai VMInternalError code section:          0x600
#define BHE_UNKOWN                              0x602
#define BHE_MAGIC_UNMATCH                       0x603
#define BHE_UNIMPLEMENTED                       0x604
#define BHE_INTR                                0x605
#define BHE_CLOSED                              0x606
#define BHE_BUFFER_OVERFLOW                     0x607   /* TODO: no used error, should remove*/
#define BHE_NOT_SUPPORTED                       0x608
#define BHE_WEAR_OUT_VIOLATION                  0x609
#define BHE_NOT_FOUND                           0x610
#define BHE_INVALID_PARAMS                      0x611
#define BHE_ACCESS_DENIED                       0x612
#define BHE_INVALID                             0x614
#define BHE_TIMEOUT                             0x615
//////////////////////////////////////////////////

//SDM specific error code section:              0x800
#define BHE_SDM_FAILED                          0x800
#define BHE_SDM_NOT_FOUND                       0x801
#define BHE_SDM_ALREADY_EXIST                   0x803
#define BHE_SDM_TATYPE_MISMATCH                 0x804
#define BHE_SDM_TA_NUMBER_LIMIT                 0x805
#define BHE_SDM_SIGNAGURE_VERIFY_FAIL           0x806
#define BHE_SDM_PERMGROUP_CHECK_FAIL            0x807
#define BHE_SDM_INSTALL_CONDITION_FAIL          0x808
#define BHE_SDM_SVN_CHECK_FAIL                  0x809
#define BHE_SDM_TA_DB_NO_FREE_SLOT              0x80A
#define BHE_SDM_SD_DB_NO_FREE_SLOT              0x80B
#define BHE_SDM_SVL_DB_NO_FREE_SLOT             0x80C
#define BHE_SDM_SVL_CHECK_FAIL                  0x80D
#define BHE_SDM_DB_READ_FAIL                    0x80E
#define BHE_SDM_DB_WRITE_FAIL                   0x80F
// ......
//////////////////////////////////////////////////

//Launcher specific error code section:         0x900
#define BHE_LAUNCHER_INIT_FAILED                0x901
#define BHE_SD_NOT_INSTALLED                    0x902
#define BHE_NTA_NOT_INSTALLED                   0x903
#define BHE_PROCESS_SPAWN_FAILED                0x904
#define BHE_PROCESS_KILL_FAILED                 0x905
#define BHE_PROCESS_ALREADY_RUNNING             0x906
#define BHE_PROCESS_IN_TERMINATING              0x907
#define BHE_PROCESS_NOT_EXIST                   0x908
#define BHE_PLATFORM_API_ERR                    0x909
#define BHE_PROCESS_NUM_EXCEED                  0x09A
//////////////////////////////////////////////////

//BeihaiHAL Layer error code section: 0x1000,0x2000
//  .... reserved here, defined in CSG BeihaiStatusHAL.h
//////////////////////////////////////////////////

#endif

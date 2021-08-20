## @file
#  SecCore constants and macros
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 1999 - 2017 Intel Corporation.
#
#  The source code contained or described herein and all documents related to the
#  source code ("Material") are owned by Intel Corporation or its suppliers or
#  licensors. Title to the Material remains with Intel Corporation or its suppliers
#  and licensors. The Material may contain trade secrets and proprietary and
#  confidential information of Intel Corporation and its suppliers and licensors,
#  and is protected by worldwide copyright and trade secret laws and treaty
#  provisions. No part of the Material may be used, copied, reproduced, modified,
#  published, uploaded, posted, transmitted, distributed, or disclosed in any way
#  without Intel's prior express written permission.
#
#  No license under any patent, copyright, trade secret or other intellectual
#  property right is granted to or conferred upon you by disclosure or delivery
#  of the Materials, either expressly, by implication, inducement, estoppel or
#  otherwise. Any license under such intellectual property rights must be
#  express and approved by Intel in writing.
#
#  Unless otherwise agreed by Intel in writing, you may not remove or alter
#  this notice or any other notice embedded in Materials by Intel or
#  Intel's suppliers or licensors in any way.
#
#  This file contains a 'Sample Driver' and is licensed as such under the terms
#  of your license agreement with Intel or your vendor. This file may be modified
#  by the user, subject to the additional terms of the license agreement.
#
# @par Specification
##

#
# Set to 1 to enable debug
#
.equ  NO_EVICTION_MODE_DEBUG,       1


.macro STATUS_CODE   status
.ifdef NO_EVICTION_MODE_DEBUG
  movb  \status, %al
  out   %al, $0x80
.endif
.endm

.equ  FVHEADER_LEN_OFF,             0x30
.equ  FFSHEADER_LEN,                0x18

.equ  IMAGE_BASE_ADDRESS,           0x0FFFF0000

#
# Set to 1 to enable debug support for "Deterministic BSP selection"
#
.equ  AP_ENTRY_DELAY,               0x10
.equ  AP_EXECUTION_DELA,            0x1000

#
# Define the segment used for AP start-up
# It should be on the top of the recovery FV
# Seg  = 0100h - (BlockNumber of Recovery FV)
# Here 0FCh = 0100h - 04h
#
.equ  AP_SEG,                       0x0FF

#
# Commands defined in the AP SIPI code
#
.equ  AP_SIPI_COLLECT_MAX_RATIO,    0x01
.equ  AP_SIPI_PROGRAM_MAX_RATIO,    0x02
.equ  AP_SIPI_SWITCH_BSP,           0x03






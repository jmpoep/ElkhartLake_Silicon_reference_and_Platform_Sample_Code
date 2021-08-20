## @file
#
#  Chipset constants and macros
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

.equ  PCIEX_BAR_REG,        0x80000060        # B0:D0:F0:R60

#
# HPET REG address
#
.equ  PCH_HPET_REG,         0x000F9060        # PCH Register B0:D1F:F1:R60
.equ  PCH_HPET_AE,          0x80              # [7] Address Enable

#
# HPET compare register
#
.equ  HPET_COMP_1,          0xFED00108
.equ  HPET_COMP_2,          0xFED0010C

#
# PCI registers
#
.equ  MCHBAR_REG,           0x48


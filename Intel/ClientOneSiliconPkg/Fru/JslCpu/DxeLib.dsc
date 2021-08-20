# @file
#  Component description file for the JasperLake CPU DXE FRU libraries.
#
# @copyright
#  INTEL CONFIDENTIAL
#  Copyright 2018 - 2019 Intel Corporation.
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
#  This file contains an 'Intel Peripheral Driver' and is uniquely identified as
#  "Intel Reference Module" and is licensed for Intel CPUs and chipsets under
#  the terms of your license agreement with Intel or your vendor. This file may
#  be modified by the user, subject to additional terms of the license agreement.
#
#@par Specification Reference:
#
##

DxeGraphicsPolicyLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/DxeGraphicsPolicyLib/DxeGraphicsPolicyLib.inf
DxeGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/DxeGraphicsInitLib/DxeGraphicsInitLib.inf
DxeIgdOpRegionInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Graphics/LibraryPrivate/DxeIgdOpRegionInitLib/DxeIgdOpRegionInitLib.inf
DxeVtdInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Vtd/LibraryPrivate/DxeVtdInitLib/DxeVtdInitLib.inf
!if gSiPkgTokenSpaceGuid.PcdHgEnable == TRUE
  DxeHybridGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/HybridGraphics/LibraryPrivate/DxeHybridGraphicsInitLib/DxeHybridGraphicsInitLib.inf
!else
  DxeHybridGraphicsInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/HybridGraphics/LibraryPrivate/DxeHybridGraphicsInitLibNull/DxeHybridGraphicsInitLibNull.inf
!endif

DxeTcssInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Tcss/LibraryPrivate/DxeTcssInitLibNull/DxeTcssInitLibNull.inf

#
# TraceHub and IPU
#
DxeTraceHubInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/TraceHub/LibraryPrivate/DxeTraceHubInitLib/DxeTraceHubInitLib.inf
DxeIpuInitLib|$(PLATFORM_SI_PACKAGE)/IpBlock/Ipu/LibraryPrivate/DxeIpuInitLib/DxeIpuInitLib.inf
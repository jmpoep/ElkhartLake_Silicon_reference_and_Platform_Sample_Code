/** @file
  TBT DXE Common Definition

@copyright
  INTEL CONFIDENTIAL
  Copyright 2017 - 2018 Intel Corporation.

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

#ifndef _DXE_TBT_COMMON_DEFINITION_H_
#define _DXE_TBT_COMMON_DEFINITION_H_

//
// TBT Common Data Structure
//
typedef struct _TBT_COMMON_CONFIG{
  /**
    Trigger SW SMI to perform TBT hierarchy enumeration which is used to enable BIOS based enumeration in legacy mode. For iTBT is not supported yet
    <b>0: Disabled</b>, 1: Enabled
  **/
  UINT32   TbtHotSMI          : 1;
  /**
    Notify PCIe RP after Hot-Plug/Hot-Unplug occurred in ACPI OS
    <b>0: Disabled</b>, 1: Enabled
  **/
  UINT32   TbtHotNotify       : 1;
  /**
    CLK REQ for all the PCIe device in TBT daisy chain.
    <b>0: Disabled</b>, 1: Enabled
  **/
  UINT32   TbtSetClkReq       : 1;
  /**
    ASPM setting for all the PCIe device in TBT daisy chain.
    <b>0: Disabled</b>, 1: L0s, 2: L1, 3: L0sL1
  **/
  UINT32   TbtAspm            : 2;
  /**
    L1 SubState for for all the PCIe device in TBT daisy chain.
    <b>0: Disabled</b>, 1: L1.1, 2: L1.1 & L1.2
  **/
  UINT32   TbtL1SubStates     : 2;
  /**
    LTR for for all the PCIe device in TBT daisy chain.
    <b>0: Disabled</b>, 1: Enabled
  **/
  UINT32   TbtLtr             : 1;
  /**
    PTM for for all the PCIe device in TBT daisy chain.
    <b>0: Disabled</b>, 1: Enabled
  **/
  UINT32   TbtPtm             : 1;
  /**
    Tbt Vtd Base Security for disable BME from TBT tree.
    <b>0: Disabled</b>, 1: Enabled
  **/
  UINT32   TbtVtdBaseSecurity : 1;
  UINT32   Rsvd0              : 22; ///< Reserved bits
} TBT_COMMON_CONFIG;

//
// TBT Resource Data Structure
//
typedef struct _TBT_RESOURCE_CONFIG{
  UINT8  TbtPcieExtraBusRsvd;           ///< Preserve Bus resource for PCIe RP
  UINT16 TbtPcieMemRsvd;                ///< Preserve MEM resource for PCIe RP
  UINT8  TbtPcieMemAddrRngMax;          ///< Alignment of Preserve MEM resource for PCIe RP
  UINT16 TbtPciePMemRsvd;               ///< Preserve PMEM resource for PCIe RP
  UINT8  TbtPciePMemAddrRngMax;         ///< Alignment of Preserve PMEM resource for PCIe RP
  UINT8  Reserved[1];                   ///< Reserved for DWORD alignment
} TBT_RESOURCE_CONFIG;

#endif

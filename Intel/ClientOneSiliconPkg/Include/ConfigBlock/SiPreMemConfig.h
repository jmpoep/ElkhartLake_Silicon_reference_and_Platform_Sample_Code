/** @file
  Si Config Block PreMem

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
#ifndef _SI_PREMEM_CONFIG_H_
#define _SI_PREMEM_CONFIG_H_

#define SI_PREMEM_CONFIG_REVISION  1

extern EFI_GUID gSiPreMemConfigGuid;

typedef enum {
  ProbeTypeDisabled    = 0x00,
  ProbeTypeDciOob      = 0x02,
  ProbeTypeUsb3Dbc     = 0x03,
  ProbeTypeXdp3        = 0x04,
  ProbeTypeUsb2Dbc     = 0x05,
  ProbeType2WireDciOob = 0x06,
  ProbeTypeManual      = 0x07,
  ProbeTypeMax
} PLATFORM_DEBUG_CONSENT_PROBE_TYPE;

#pragma pack (push,1)
/**
  The Silicon PreMem Policy allows the platform code to publish a set of configuration
  information that the RC drivers will use to configure the silicon hardware.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;  ///< Offset 0 - 27 Config Block Header
  /**
    Platform Debug Consent
    As a master switch to enable platform debug capability and relevant settings with specified probe type.
    Manual: Do not use Platform Debug Consent to override other debug-relevant policies, but the user must set each debug option manually, aimed at advanced users.

    PDC-dependent policies are listed:
    DciPreMemConfig->DciEn
    DciPreMemConfig->DciDbcMode
    CpuTraceHubConfig->EnableMode
    CpuTraceHubConfig->CpuTraceHubMemReg0Size
    CpuTraceHubConfig->CpuTraceHubMemReg1Size
    PchTraceHubPreMemConfig->EnableMode
    PchTraceHubPreMemConfig->MemReg0Size
    PchTraceHubPreMemConfig->MemReg1Size

    Note: DCI OOB (aka BSSB) uses CCA probe.
    Refer to definition of PLATFORM_DEBUG_CONSENT_PROBE_TYPE
    <b>0:Disabled</b>; 2:DCI OOB; 3:USB3 DbC; 4:XDP3/MIPI60 5:USB2 DbC; 6:2-wire DCI OOB; 7:Manual
  **/
  UINT32    PlatformDebugConsent  :  4;
  UINT32    RsvdBits              : 28;
} SI_PREMEM_CONFIG;

#pragma pack (pop)
#endif // _SI_PREMEM_CONFIG_H_

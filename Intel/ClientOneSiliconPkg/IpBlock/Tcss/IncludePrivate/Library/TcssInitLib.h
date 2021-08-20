/** @file
  Header file for TCSS Init Lib in PEI.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2016 - 2019 Intel Corporation.

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
#ifndef _TCSS_INIT_LIB_H_
#define _TCSS_INIT_LIB_H_

#include <TcssPeiPreMemConfig.h>
#include <TcssPeiConfig.h>
#include <SaPolicyCommon.h>
#include <Ppi/SiPolicy.h>

/**
  IomReadyCheck - This function performs IOM ready state

  This function does the following steps:
  (1) Examines IOM_READY (Register IOM_TYPEC_STATUS_1, bit 30)
  (2) If 0, retry in IOM_READY_TIMEOUT ms (1ms timeout)
  (3) Save success/failure in Tcss HOB
  (4) Print success/failure
**/
EFI_STATUS
EFIAPI
IomReadyCheck (
  VOID
  );

/**
  This function performs basic initialization for TCSS in PEI phase after Policy produced at Pre-Mem phase.

  @param[in]  TcssConfig              Pointer to TCSS config block
  @param[in]  MiscSaPeiPreMemConfig   Pointer to SA miscellaneous config block
**/
VOID
EFIAPI
TcssPreMemInit (
  IN TCSS_PEI_PREMEM_CONFIG      *TcssPeiPreMemConfig,
  IN SA_MISC_PEI_PREMEM_CONFIG   *MiscSaPeiPreMemConfig
  );

/**
  Entrypoint to perform basic initialization for TCSS in PEI phase after Policy produced at Post-Mem phase.

  This function does the following steps:
  (1) Check IOM Ready bit.
  (2) If IOM is ready, then programs VCCST, REPLAY and CONNECTION_OVERRIDE setting.
  (3) If IOM is ready, then programs AUX/HSL orientation support per platform design
  (4) Do iTBT PCIE RP programming
  (5) Start iTBT specific BIOS support
  (6) Init TCSS USB controllers (xHCI and xDCI)
  (7) Handshake with PMC if PMC handshaking support is enabled

  @param[in] SiPolicy             The SI Policy PPI instance
  @param[in] TcssPeiPreMemConfig  Pointer to config block
  @param[in] TcssConfig           Pointer to config block
**/
VOID
EFIAPI
TcssInit (
  IN  SI_POLICY_PPI               *SiPolicy,
  IN  TCSS_PEI_PREMEM_CONFIG      *TcssPeiPreMemConfig,
  IN  TCSS_PEI_CONFIG             *TcssPeiConfig
  );


#endif

/** @file
  This file contains PEI PCH DMI methods

@copyright
  INTEL CONFIDENTIAL
  Copyright 2018 Intel Corporation.

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

#ifndef _PEI_PCH_DMI_LIB_H_
#define _PEI_PCH_DMI_LIB_H_

#include <Ppi/SiPolicy.h>

//
// Data structure definitions
//
typedef enum {
  PchDmiVcTypeVc0,
  PchDmiVcTypeVc1,
  PchDmiVcTypeVcm,
  PchDmiVcTypeMax
} PCH_DMI_VC_TYPE;

/**
  The data structure to describe DMI TC configuration setting
**/
typedef struct {
  PCH_DMI_VC_TYPE       Vc;       ///< The Virtual Channel to which the TC is mapped
  UINT8                 TcId;     ///< Tc ID Encoding
} PCH_DMI_TC_CONFIG;

/**
  The data structure to describe DMI VC configuration setting
**/
typedef struct {
  BOOLEAN               Enable;   ///< 0: Disable; 1: Enable
  UINT8                 VcId;     ///< Vc ID Encoding for the Virtual Channel
} PCH_DMI_VC_CONFIG;

#define PchDmiTcTypeMax  3

/**
  PCH_DMI_TC_VC_MAP Structure Definition
  Note: The default DMI TC/VC mapping will be used if it's not initialized
**/
typedef struct {
  PCH_DMI_TC_CONFIG DmiTc[PchDmiTcTypeMax];  ///< Configures PCH DMI Traffic class mapping.
  PCH_DMI_VC_CONFIG DmiVc[PchDmiVcTypeMax];  ///< Configures PCH DMI Virtual Channel setting.
} PCH_DMI_TC_VC_MAP;

/**
  Get PCH default TC VC Mapping settings. This funciton returns the default PCH setting
  System Agent can update the settings according to polices.

  @param[in, out] PchDmiTcVcMap         Buffer for PCH_DMI_TC_VC_MAP instance.

**/
VOID
PchDmiTcVcMapInit (
  IN OUT  PCH_DMI_TC_VC_MAP             *PchDmiTcVcMap
  );

/**
  The function performing TC/VC mapping program, and poll all PCH Virtual Channel
  until negotiation completion.

  @param[in] PchDmiTcVcMap              Buffer for PCH_DMI_TC_VC_MAP instance.

  @retval EFI_SUCCESS                   The function completed successfully
  @retval Others                        All other error conditions encountered result in an ASSERT.
**/
EFI_STATUS
PchDmiTcVcProgPoll (
  IN  PCH_DMI_TC_VC_MAP                 *PchDmiTcVcMap
  );

/**
  The function set the Target Link Speed in PCH to DMI GEN 3.

  @param[in] TargetLinkSpeed        Target Link Speed
                                    2: GEN2
                                    3: GEN3
**/
VOID
PchDmiSetTargetLinkSpeed (
  IN  UINT8                 TargetLinkSpeed
  );

/**
  This function configures DMI SIP14.

  @param[in] SiPolicyPpi The PCH Policy PPI instance
**/
VOID
PchDmi14Init (
  IN  SI_POLICY_PPI  *SiPolicyPpi
  );

/**
  This function performs early PCH-H DMI SIP15 init.
  It must be called before any upstream bus master transactions are enabled
**/
VOID
PchDmi15EarlyInit (
  VOID
  );

/**
  This function configures DMI SIP15.

  @param[in] SiPolicyPpi The PCH Policy PPI instance
**/
VOID
PchDmi15Init (
  IN  SI_POLICY_PPI  *SiPolicyPpi
  );

#endif

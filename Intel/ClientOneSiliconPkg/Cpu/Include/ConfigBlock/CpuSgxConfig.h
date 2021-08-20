/** @file
  CPU SGX Config Block.

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
#ifndef _CPU_SGX_CONFIG_H_
#define _CPU_SGX_CONFIG_H_

#define CPU_SGX_CONFIG_REVISION 1                 ///< SGX Configuration Revision

extern EFI_GUID gCpuSgxConfigGuid;                ///< SGX Configuration GUID

#pragma pack (push,1)

/**
  CPU SGX Configuration Structure.
  @note <b>Optional.</b> These policies will be ignored if CPU_SECURITY_PREMEM_CONFIG -> EnableSgx is disabled, or BaseSoftwareGuardLibNull is used.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Offset 0-27  Config Block Header
  UINT8  SgxSinitNvsData;                         ///< Offset 28    SGX NVS data from Flash passed during previous boot using CPU_INFO_PROTOCOL.SGX_INFO; <b>0: Pass value of zero if there is not data saved or when SGX is disabled.</b>
  UINT8  SgxSinitDataFromTpm;                     ///< Offset 29    SGX SVN data from TPM; <b>0: when SGX is disabled or TPM is not present or no data is present in TPM.</b>
  UINT8  Rsvd[2];                                 ///< Offset 30-31 Reserved for future use and config block alignment
  UINT64 SgxEpoch0;                               ///< Offset 32-39 SGX EPOCH0 value <b>0: Minimum</b>, 0xFFFFFFFFFFFFFFFF: Maximum
  UINT64 SgxEpoch1;                               ///< Offset 40-47 SGX EPOCH1 value <b>0: Minimum</b>, 0xFFFFFFFFFFFFFFFF: Maximum
  UINT8  SgxLCP;                                  ///< Offset 48    SGX Launch Control Policy; <b>0: Locked</b>, 1: Unlocked
  UINT64 SgxLEPubKeyHash0;                        ///< Offset 49-56 SGX Launch Enclave Public Key Hash 0; <b>0x0</b> 0: Minimum, 0xFFFFFFFFFFFFFFFF: Maximum
  UINT64 SgxLEPubKeyHash1;                        ///< Offset 57-64 SGX Launch Enclave Public Key Hash 1; <b>0x0</b> 0: Minimum, 0xFFFFFFFFFFFFFFFF: Maximum
  UINT64 SgxLEPubKeyHash2;                        ///< Offset 65-72 SGX Launch Enclave Public Key Hash 2; <b>0x0</b> 0: Minimum, 0xFFFFFFFFFFFFFFFF: Maximum
  UINT64 SgxLEPubKeyHash3;                        ///< Offset 73-80 SGX Launch Enclave Public Key Hash 3; <b>0x0</b> 0: Minimum, 0xFFFFFFFFFFFFFFFF: Maximum
  UINT8  Rsvd1[3];                                ///< Offset 81-83 Reserved for future use and config block alignment
} CPU_SGX_CONFIG;

#pragma pack (pop)

#endif // _CPU_SGX_CONFIG_H_

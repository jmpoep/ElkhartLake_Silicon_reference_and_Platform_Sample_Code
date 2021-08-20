/** @file
  CPU BIOS Guard Config Block.

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
#ifndef _BIOS_GUARD_CONFIG_H_
#define _BIOS_GUARD_CONFIG_H_

#define BIOS_GUARD_CONFIG_REVISION 1              ///< BIOS Guard Configuration Revision

extern EFI_GUID gBiosGuardConfigGuid;             ///< BIOS Guard Configuration GUID

#pragma pack (push,1)

/**
  BIOS Guard Configuration Structure.
  Platform policies for BIOS Guard Configuration for all processor security features configuration.
  Platform code can pass relevant configuration data through this structure.
  @note <b>Optional.</b> These policies will be ignored if CPU_SECURITY_PREMEM_CONFIG -> BiosGuard is disabled, or PeiBiosGuardLibNull is used.

  <b>Revision 1</b>:
  - Initial version.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;                   ///< Config Block Header
  BIOSGUARD_ATTRIBUTES  BiosGuardAttr;            ///< BIT1 - EC Present, BIT2 - EC BIOS Guard protection, BIT3 - Descriptor Override policy, BIT4 - Flash wearout protection, BIT5 - FTU enable
  UINT64                BgpdtHash[4];             ///< Hash of the BGPDT that will be programmed to PLAT_FRMW_PROT_HASH_0/1/2/3 MSR.
  EFI_PHYSICAL_ADDRESS  BiosGuardModulePtr;       ///< Pointer to the BIOS Guard Module.
  EFI_PHYSICAL_ADDRESS  SendEcCmd;                ///< Platform code can provide interface to communicate with EC through this function.
  UINT8                 EcCmdProvisionEav;        ///< EC Command Provision Eav.
  UINT8                 EcCmdLock;                ///< EC Command Lock.

  // Since the biggest element is UINT64, this structure should be aligned with 64 bits.
  UINT8                 Reserved[6];              ///< Reserved for future use and config block alignment.
} BIOS_GUARD_CONFIG;
#pragma pack (pop)

///
/// Enums for EC Command Type
///
typedef enum {
  SendEcCmds = 1,
  SendEcValue,
  ReceiveEcValue,
  EcCmdMax
} EC_COMMAND_TYPE;

/**
  This function is for platform code to provide EC Commands since different BIOS might have different EC.
  Platform code need to provide a function for CPU code to call to communicate with EC.

  @param[in] EcCmdType      - EC Command Type.
  @param[in] EcCmd          - EC Command Byte to send.
  @param[in] SendData       - EC Data Byte to send.
  @param[in] ReceiveData    - EC Data Byte received.

  @retval EFI_SUCCESS          Command Read/ Write Success.
  @retval EFI_DEVICE_ERROR     Command Read/ Write Error.
  @retval EFI_OUT_OF_RESOURCES No enough resources (such as out of memory).
**/
typedef
EFI_STATUS
(EFIAPI *PLATFORM_SEND_EC_COMMAND) (
  IN EC_COMMAND_TYPE   EcCmdType,
  IN UINT8             EcCmd,
  IN UINT8             SendData,
  IN OUT UINT8         *ReceiveData
  );

#endif // _BIOS_GUARD_CONFIG_H_

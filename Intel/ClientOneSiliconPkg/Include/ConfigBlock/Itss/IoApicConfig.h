/** @file
  IoApic policy

@copyright
  INTEL CONFIDENTIAL
  Copyright 2015 - 2018 Intel Corporation.

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
#ifndef _IOAPIC_CONFIG_H_
#define _IOAPIC_CONFIG_H_

#define IOAPIC_CONFIG_REVISION 1
extern EFI_GUID gIoApicConfigGuid;

#pragma pack (push,1)

/**
  The PCH_IOAPIC_CONFIG block describes the expected configuration of the PCH
  IO APIC, it's optional and PCH code would ignore it if the BdfValid bit is
  not TRUE. Bus:device:function fields will be programmed to the register
  P2SB IBDF(P2SB PCI offset R6Ch-6Dh), it's using for the following purpose:
  As the Requester ID when initiating Interrupt Messages to the processor.
  As the Completer ID when responding to the reads targeting the IOxAPI's
  Memory-Mapped I/O registers.
  This field defaults to Bus 0: Device 31: Function 0 after reset. BIOS can
  program this field to provide a unique Bus:Device:Function number for the
  internal IOxAPIC.
  The address resource range of IOAPIC must be reserved in E820 and ACPI as
  system resource.
**/
typedef struct {
  CONFIG_BLOCK_HEADER   Header;         ///< Config Block Header
  UINT32  IoApicEntry24_119     :  1;   ///< 0: Disable; <b>1: Enable</b> IOAPIC Entry 24-119
  /**
    Enable 8254 Static Clock Gating during early POST time. 0: Disable, <b>1: Enable</b>
    Setting 8254CGE is required to support SLP_S0.
    Enable this if 8254 timer is not used.
    However, set 8254CGE=1 in POST time might fail to boot legacy OS using 8254 timer.
    Make sure it is disabled to support legacy OS using 8254 timer.
    @note:
    For some OS environment that it needs to set 8254CGE in late state it should
    set this policy to FALSE and use ItssSet8254ClockGateState  (TRUE) in SMM later.
    This is also required during S3 resume.
    To avoid SMI requirement in S3 reusme path, it can enable the Enable8254ClockGatingOnS3
    and RC will do 8254 CGE programming in PEI during S3 resume with BOOT_SAI.
    PCH:RestrictedBegin
    The Linux bootloader Grub might still use 8254 timer. It should not set 8254CGE
    in early phase and set 8254CGE in ACPI enable SMI callback.
    https://hsdes.intel.com/appstore/article/#/1805947479
    PCH:RestrictedEnd
  **/
  UINT32  Enable8254ClockGating :  1;
  /**
    Enable 8254 Static Clock Gating on S3 resume path. 0: Disable, <b>1: Enable</b>
    This is only applicable when Enable8254ClockGating is disabled.
    If Enable8254ClockGating is enabled, RC will do the 8254 CGE programming on
    S3 resume path as well.
  **/
  UINT32  Enable8254ClockGatingOnS3 :  1;
  UINT32  RsvdBits1             : 29;   ///< Reserved bits
  UINT8   IoApicId;                     ///< This member determines IOAPIC ID. Default is <b>0x02</b>.
  UINT8   Rsvd0[3];                     ///< Reserved bytes
} PCH_IOAPIC_CONFIG;

#pragma pack (pop)

#endif // _IOAPIC_CONFIG_H_

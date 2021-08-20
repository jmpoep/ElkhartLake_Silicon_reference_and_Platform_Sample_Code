/** @file
  Prototype of the SmbiosMemory library.

@copyright
  INTEL CONFIDENTIAL
  Copyright 2014 - 2016 Intel Corporation.

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
  System Management BIOS (SMBIOS) Reference Specification v2.8.0
  dated 2013-Mar-28 (DSP0134)
  http://www.dmtf.org/sites/default/files/standards/documents/DSP0134_2.8.0.pdf
**/
#ifndef _SMBIOS_MEMORY_LIB_H_
#define _SMBIOS_MEMORY_LIB_H_

/**
  <b> SMBIOS Memory Information </b>
  This function will determine memory configuration information from the chipset and memory and install SMBIOS table types 16, 17, and 19.
  @note Type 20 is optional as per SMBIOS specification v2.5 and above.
  - <b>Introduction</b> \n
    This module publishes the SMBIOS information.  This module reads the System Agent configuration registers to determine memory configuration, creates the SMBIOS structures and (Native Mode) adds them using the SMBIOS protocol, or (ECP Mode) logs them to the data hub. The data hub structures are later retrieved by the SMBIOS thunk driver for publishing the SMBIOS tables in memory.
    This module is required for systems supporting SMBIOS tables.

  - @pre
    - EFI_SMBUS_HC_PROTOCOL
    - EFI_PCI_ROOT_BRIDGE_IO_PROTOCOL (See UEFI Spec, v2.0)
    - DXE_PLATFORM_SA_POLICY_PROTOCOL
    - MEM_INFO_PROTOCOL
    - EFI_SMBIOS_PROTOCOL

  - @result
    Publishes SMBIOS data structures related to the System Agent.
     - Publishes using EFI_SMBIOS_PROTOCOL.

  - @warning
    Any modification of this module should ensure properly formatted structures are produced.
    Properly formatted SMBIOS table structures
    It is recommended that all SMBIOS information produced for your platform is reviewed for accuracy.
    No recommendation is provided on how to address issues if any are encountered in the memory structures provided by this module.

  @param[in] SmbiosProtocol     - Instance of Smbios Protocol

  @retval EFI_SUCCESS           - if the data is successfully reported.
  @retval EFI_OUT_OF_RESOURCES  - if not able to get resources.
  @retval EFI_INVALID_PARAMETER - if a required parameter in a subfunction is NULL.
**/
EFI_STATUS
EFIAPI
SmbiosMemory (
  IN  EFI_SMBIOS_PROTOCOL *SmbiosProtocol
  );
#endif // _DXE_SMBIOS_MEMORY_LIB_H_
